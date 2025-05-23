#include <algorithm>
#include <string>

#include "Machine.h"
#include "Loader.h"
#include "PdpTypes.h"
#include "Operand.h"
#include "Machine.h"
#include "Command.h"

const AddCommand    ADD;
const MovCommand    MOV;
const MovbCommand   MOVb;
const SobCommand    SOB;
const HaltCommand   HALT;
const ClrCommand    CLR;
const BrCommand     BR;
const BeqCommand    BEQ;
const TestCommand   TEST;
const TestbCommand  TESTb;
const BplCommand    BPL;
const JsrCommand    JSR;
const RtsCommand    RTS;
const IncCommand    INC;
const RolCommand    ROL;
const AshCommand    ASH;
const BicCommand    BIC;
const AslCommand    ASL;

const std::vector<const Command*> Machine::commands = {
  &ADD, &MOV, &MOVb, &SOB, &HALT, &CLR, &BR, &BEQ, &TEST, &TESTb, &BPL, &JSR, &RTS, &INC, &ROL, &ASH, &BIC, &ASL
};

Machine::Machine()
    : loader_(&mem_)
    , regs{ 0, 0, 0, 0, 0, 0, 0, 0 }
{
    devices_.push_back(std::make_unique<Monitor>(&mem_, &logger_));
}

PdpWord& Machine::pc() {
    return regs[7];
}

PdpWord& Machine::sp() {
    return regs[6];
}

const Command* findCommand(int opcode) {
    auto begin = Machine::commands.begin();
    auto end = Machine::commands.end();
    auto pred = [opcode](const Command* cmd) { return cmd->match(opcode); };
    auto it = std::find_if(begin, end, pred);
    if (it == end) {
        return nullptr;
    }
    return *it;
}

void Machine::run(std::istream& is) {
    loader_.load(is);
    pc() = 01000;
    const Command* cmd = nullptr;
    do {
        int opcode = mem_.getWord(pc());
        pc()++;
        cmd = findCommand(opcode);
        if (cmd == nullptr) {
            std::stringstream ss;
            ss << "invalid opcode: 0o" << std::oct << opcode;
            throw std::invalid_argument(ss.str());
        }
        cmd->exec(opcode, *this);
    } while (cmd != &HALT);
    logger().lazyDebug([this](Logger::OStreamWrapper& w) {
        w << "\nR0" << ':' << std::oct << regs[0].toUnsigned();
        for (int i = 1; i < 8; i++) {
            w << " R" << i << ':' << std::oct << regs[i].toUnsigned();
        }
        w << '\n' << "Z:" << psw.zeroBit << " N:" << psw.negBit << " C:" << psw.carryBit << '\n';
    });
}

PdpByte Machine::getByte(PdpAddr addr) {
    return mem_.getByte(addr);
}

PdpWord Machine::getWord(PdpAddr addr) {
    return mem_.getWord(addr);
}


const DevicePtr *Machine::findOwningDevice(PdpWord addr) {
    auto owns = [addr](DevicePtr& d) { return d->owns(addr); };
    auto it = std::find_if(devices_.begin(), devices_.end(), owns);
    return it == devices_.end() ? nullptr : &(*it);
}

void Machine::setByte(PdpAddr addr, PdpByte value) {
    auto device = findOwningDevice(addr);
    if (device) {
        (*device)->enqueue(value);
    } else {
        mem_.setByte(addr, value);
    }
}

void Machine::setWord(PdpAddr addr, PdpWord value) {
    auto device = findOwningDevice(addr);
    if (device) {
        (*device)->enqueue(value.low());
    } else {
        mem_.setWord(addr, value);
    }
}
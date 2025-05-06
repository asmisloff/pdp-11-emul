#include <algorithm>
#include <string>

#include "Machine.h"
#include "Loader.h"
#include "PdpTypes.h"
#include "Operand.h"
#include "Machine.h"
#include "commands/all.h"

static const AddCommand  ADD;
static const MovCommand  MOV;
static const MovbCommand  MOVb;
static const SobCommand  SOB;
static const HaltCommand HALT;
static const ClrCommand  CLR;
static const BrCommand BR;
static const BeqCommand BEQ;
static const TestbCommand TESTb;
static const BplCommand BPL;
static const JsrCommand JSR;
static const RtsCommand RTS;

const std::vector<const Command*> Machine::commands = {
  &ADD, &MOV, &MOVb, &SOB, &HALT, &CLR, &BR, &BEQ, &TESTb, &BPL, &JSR, &RTS
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
        logger().debug() << pc() << ": ";
        pc()++;
        cmd = findCommand(opcode);
        if (cmd == nullptr) {
            throw std::invalid_argument("invalid opcode: " + std::to_string(opcode));
        }
        cmd->exec(opcode, *this);
    } while (cmd != &HALT);
    logger().debug([this](Logger::OStreamWrapper& w) {
        for (int i = 0; i < 7; i++) {
            w << 'R' << i << ':' << std::oct << regs[i].toUnsigned() << ' ';
        }
        w << 'R' << 7 << ':' << std::oct << regs[7].toUnsigned() << '\n';
        w << "Z:" << psw.zeroBit << " N:" << psw.negBit << " C:" << psw.carryBit << '\n';
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
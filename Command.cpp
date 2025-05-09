#include "Command.h"
#include "Machine.h"
#include "Operand.h"

Command::Command(std::string&& name, int mask, int prefix)
    : name_(name)
    , mask_(mask)
    , prefix_(prefix)
{}

const std::string& Command::name() const {
    return name_;
}

bool Command::match(int opcode) const {
    return (opcode & mask_) == prefix_;
}

void Command::logDebug(Machine& m) const {
    m.logger().debug() << '\n' << (m.pc() - 2) << ": " << name() << ' ';
}


AddCommand::AddCommand    () : Command("ADD",   0170000, 0060000) {}
BeqCommand::BeqCommand    () : Command("BEQ",   0177400, 0001400) {}
BplCommand::BplCommand    () : Command("BPL",   0177400, 0100000) {}
BrCommand::BrCommand      () : Command("BR",    0177400, 0000400) {}
ClrCommand::ClrCommand    () : Command("CLR",   0177700, 0005000) {}
HaltCommand::HaltCommand  () : Command("HALT",  0177777, 0000000) {}
JsrCommand::JsrCommand    () : Command("JSR",   0777000, 0004000) {}
MovbCommand::MovbCommand  () : Command("MOVb",  0170000, 0110000) {}
MovCommand::MovCommand    () : Command("MOV",   0170000, 0010000) {}
RtsCommand::RtsCommand    () : Command("RTS",   0777770, 0000200) {}
SobCommand::SobCommand    () : Command("SOB",   0177000, 0077000) {}
TestCommand::TestCommand  () : Command("TEST",  0177700, 0005700) {}
TestbCommand::TestbCommand() : Command("TESTb", 0177700, 0105700) {}
IncCommand::IncCommand    () : Command("INC",   0177700, 0005200) {}
RolCommand::RolCommand    () : Command("ROL",   0107700, 0006100) {}

void AddCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand ss = Operand::SS(opcode, CommandMode::WORD);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    PdpRef sRef = ss.eval(m);
    PdpRef dRef = dd.eval(m);
    PdpWord v1 = sRef.getWord();
    PdpWord v2 = dRef.getWord();
    PdpWord sum = v1 + v2;
    int ref = v1.toSigned() + v2.toSigned();
    m.psw = { .zeroBit = (sum == 0), .negBit = (sum.toSigned() < 0), .carryBit = (ref > 0xffff) };
    dRef.setWord(sum);
}

void BeqCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    char offset = char(opcode);
    if (m.psw.zeroBit) {
        m.pc() += 2 * offset;
    }
    m.logger().debug() << "goto " << m.pc();
}

void BplCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    if (!m.psw.negBit) {
        m.pc() += 2 * char(opcode);
    }
    m.logger().debug() << "goto " << ' ' << m.pc();
}

void BrCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    char offset = char(opcode);
    m.pc() += 2 * offset;
    m.logger().debug() << "goto " << m.pc();
}

void ClrCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    dd.eval(m).setWord(0);
    m.psw = { .zeroBit = 1, .negBit = 0, .carryBit = 0 };
}

void HaltCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    (void)opcode;
}

void JsrCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    int regIdx = (opcode & 0000700) >> 6;
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    PdpAddr addr = dd.eval(m).addr();
    m.setWord(--m.sp(), m.reg(regIdx));
    m.reg(regIdx) = m.pc();
    m.pc() = addr;
    m.logger().debug() << "proc " << m.pc() << " ret " << m.getWord(m.sp());
}

void MovbCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand ss = Operand::SS(opcode, CommandMode::BYTE);
    Operand dd = Operand::DD(opcode, CommandMode::BYTE);
    PdpByte byte = ss.eval(m).getByte();
    dd.eval(m).setByte(byte);
    m.psw.zeroBit = (byte == 0);
    m.psw.negBit = (int8_t(byte) < 0);
}

void MovCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand ss = Operand::SS(opcode, CommandMode::WORD);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    PdpWord word = ss.eval(m).getWord();
    m.psw.negBit = (word.toSigned() < 0);
    m.psw.zeroBit = (word == 0);
    dd.eval(m).setWord(word);
}

void RtsCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    int regIdx = opcode & 0000007;
    m.pc() = m.reg(regIdx);
    m.reg(regIdx) = m.getWord(m.sp()++);
    m.logger().debug() << 'R' << regIdx << ' ' << m.pc();
}

void SobCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    int i = (opcode & 0000700) >> 6;
    PdpWord& reg = m.reg(i);
    int offset = (opcode & 0000077) * 2;
    reg -= 1;
    if (reg.toUnsigned() > 0) {
        m.pc() -= offset;
    }
    m.logger().debug() << 'R' << i << " goto " << m.pc();
}

void TestCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    PdpWord word = dd.eval(m).getWord();
    m.psw = { .zeroBit = (word == 0), .negBit = word.toSigned() < 0, .carryBit = false };
    m.logger().debug() << ' ' << "Z:" << m.psw.zeroBit << ' ' << "N:" << m.psw.negBit;
}

void TestbCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand dd = Operand::DD(opcode, CommandMode::BYTE);
    PdpByte byte = dd.eval(m).getByte();
    m.psw = { .zeroBit = (byte == 0), .negBit = int8_t(byte) < 0, .carryBit = false };
    m.logger().debug() << ' ' << "Z:" << m.psw.zeroBit << ' ' << "N:" << m.psw.negBit;
}

void IncCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    PdpRef ref = dd.eval(m);
    int16_t newValue = ref.getWord().toSigned() + 1;
    ref.setWord(newValue);
    m.psw.zeroBit = (newValue == 0);
    m.psw.negBit = (newValue < 0);
}

void RolCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    PdpRef ref = dd.eval(m);
    int16_t val = ref.getWord().toSigned();
    int16_t newVal = (val << 1) | m.psw.carryBit;
    ref.setWord(newVal);
    m.psw = { .zeroBit = (newVal == 0),.negBit = (newVal < 0), .carryBit = (val < 0) };
    m.logger().debug() << PdpWord(val) << " -> " << PdpWord(newVal) << " C:" << m.psw.carryBit;
}
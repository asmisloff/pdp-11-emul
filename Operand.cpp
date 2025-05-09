#include <functional>

#include "Operand.h"

Operand::Operand(char mode, char reg, CommandMode cmdMode)
    : mode_{mode},
    regIdx_{reg},
    cmdMode_{reg < 6 ? cmdMode : CommandMode::WORD}
{}

Operand Operand::SS(int opcode, CommandMode cmdMode) {
    const int mode = (opcode & 0007000) >> 9;
    const int reg = (opcode & 0000700) >> 6;
    return Operand(mode, reg, cmdMode);
}

Operand Operand::DD(int opcode, CommandMode cmdMode) {
    const int mode = (opcode & 0000070) >> 3;
    const int reg = opcode & 0000007;
    return Operand(mode, reg, cmdMode);
}

PdpRef evalMode0(const Operand* op, Machine* m) {
    int i = op->regIdx();
    m->logger().debug() << "R" << i << ' ';
    return PdpRef(m, PdpRef::REG, i);
}

PdpRef evalMode1(const Operand* op, Machine* m) {
    int i = op->regIdx();
    m->logger().debug() << "(R" <<i << ") ";
    return PdpRef(m, PdpRef::MEM, m->reg(i));
}

PdpRef evalMode2(const Operand* op, Machine* m) {
    int i = op->regIdx();
    m->logger().debug() << "(R" << i << ")+ ";
    PdpWord addr = m->reg(i);
    op->incReg(*m);
    return PdpRef(m, PdpRef::MEM, addr);
}

PdpRef evalMode3(const Operand* op, Machine* m) {
    int i = op->regIdx();
    m->logger().debug() << "@(R" << i << ") ";
    PdpAddr addrOfAddr = m->reg(i)++;
    PdpAddr addr = m->getWord(addrOfAddr);
    return PdpRef(m, PdpRef::MEM, addr);
}

PdpRef evalMode4(const Operand* op, Machine* m) {
    int i = op->regIdx();
    m->logger().debug() << "-(R" << i << ") ";
    op->decReg(*m);
    PdpAddr addr = m->reg(i);
    return PdpRef(m, PdpRef::MEM, addr);
}

PdpRef evalMode5(const Operand* op, Machine* m) {
    int i = op->regIdx();
    m->logger().debug() << "@-(R" << i << ") ";
    PdpAddr addrOfAddr = --m->reg(i);
    PdpAddr addr = m->getWord(addrOfAddr);
    return PdpRef(m, PdpRef::MEM, addr);
}

PdpRef evalMode6(const Operand* op, Machine* m) {
    PdpAddr offsetAddr = m->pc()++;
    int16_t offset = m->getWord(offsetAddr).toSigned();
    int i = op->regIdx();
    m->logger().debug() << offset << "(R" << i << ") ";
    PdpAddr addr = m->reg(i).toUnsigned() + offset;
    return PdpRef(m, PdpRef::MEM, addr);
}

PdpRef evalMode7(const Operand* op, Machine* m) {
    PdpAddr offsetAddr = m->pc()++;
    int16_t offset = m->getWord(offsetAddr).toSigned();
    int i = op->regIdx();
    m->logger().debug() << '@' << offset << "(R" << i << ") ";
    PdpAddr addrOfAddr = m->reg(i).toUnsigned() + offset;
    PdpAddr addr = m->getWord(addrOfAddr);
    return PdpRef(m, PdpRef::MEM, addr);
}

std::array<std::function<PdpRef(const Operand*, Machine*)>, 8> evaluators {
    evalMode0, evalMode1, evalMode2, evalMode3, evalMode4, evalMode5, evalMode6, evalMode7
};

PdpRef Operand::eval(Machine& m) const {
    return evaluators[mode_](this, &m);
}

void Operand::incReg(Machine& m) const {
    int amount = (cmdMode_ == BYTE) ? 1 : 2;
    m.reg(regIdx_) += amount;
}

void Operand::decReg(Machine& m) const {
    int amount = (cmdMode_ == BYTE) ? 1 : 2;
    m.reg(regIdx_) -= amount;
}

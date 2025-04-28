#include "MovCommand.h"

static const std::string MOV = "MOV";

const std::string& MovCommand::name() const { return MOV; }

bool MovCommand::match(int opcode) const {
    return (0170000 & opcode) == 0010000;
}

void MovCommand::exec(int opcode, Machine& m) const {
    auto [ss, dd] = getOperands(opcode, m);
    PdpWord value = ss.read(m);
    int16_t sv = value.toSigned();
    m.psw.negBit = (sv < 0);
    m.psw.zeroBit = (sv == 0);
    dd.write(m, value);
}

std::pair<Operand, Operand> MovCommand::getOperands(int opcode, Machine& m) const {
    Operand ss = Operand::SS(opcode);
    Operand dd = Operand::DD(opcode);
    m.logger().debug([this, &ss, &dd, &m](Logger::OStreamWrapper& w) {
        w << name() << ' ' << ss.toStr(m) << ' ' << dd.toStr(m) << '\n';
    });
    return { ss, dd };
}
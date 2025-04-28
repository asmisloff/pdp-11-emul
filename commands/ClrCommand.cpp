#include "ClrCommand.h"
#include "../Operand.h"

static const std::string CLR = "CLR";

const std::string& ClrCommand::name() const {
    return CLR;
}

bool ClrCommand::match(int opcode) const {
    return (0177700 & opcode) == 005000;
}

void ClrCommand::exec(int opcode, Machine& m) const {
    Operand dd = Operand::DD(opcode);
    m.logger().debug([this, &m, &dd](Logger::OStreamWrapper& w) {
        w << name() << ' ' << dd.toStr(m) << '\n';
    });
    dd.write(m, 0);
    m.psw = { .zeroBit = 1, .negBit = 0, .carryBit = 0 };
}
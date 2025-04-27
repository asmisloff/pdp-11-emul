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
    Logger& logger = m.logger();
    if (logger.level >= Logger::Level::DEBUG) {
        const char* cmd_name = name().c_str();
        std::string dd_str = dd.toStr(m);
        logger.debug() << cmd_name << ' ' << dd_str.c_str() << '\n';
    }
    dd.write(m, 0);
    m.psw = { .zeroBit = 1, .negBit = 0, .carryBit = 0 };
}
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
    logDebug(m);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    dd.eval(m).setWord(0);
    m.psw = { .zeroBit = 1, .negBit = 0, .carryBit = 0 };
}
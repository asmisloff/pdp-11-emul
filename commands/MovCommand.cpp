#include "MovCommand.h"

static const std::string MOV = "MOV";

const std::string& MovCommand::name() const { return MOV; }

bool MovCommand::match(int opcode) const {
    return (0170000 & opcode) == 0010000;
}

void MovCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    Operand ss = Operand::SS(opcode, CommandMode::WORD);
    Operand dd = Operand::DD(opcode, CommandMode::WORD);
    PdpWord value = ss.eval(m).getWord();
    int16_t sv = value.toSigned();
    m.psw.negBit = (sv < 0);
    m.psw.zeroBit = (sv == 0);
    dd.eval(m).setWord(value);
}

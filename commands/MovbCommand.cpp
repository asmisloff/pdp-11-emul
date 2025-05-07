#include "MovbCommand.h"

static const std::string MOVb = "MOVb";

const std::string& MovbCommand::name() const {
    return MOVb;
}

bool MovbCommand::match(int opcode) const {
    return (0170000 & opcode) == 0110000;
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
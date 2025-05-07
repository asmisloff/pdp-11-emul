#include "AddCommand.h"
#include "../Operand.h"

static const std::string ADD = "ADD";

const std::string& AddCommand::name() const {
    return ADD;
}

bool AddCommand::match(int opcode) const {
    return (0170000 & opcode) == 060000;
}

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
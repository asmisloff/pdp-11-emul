#include "TestbCommand.h"
#include "../Operand.h"
#include "../Machine.h"

static std::string TESTB("TESTb");

const std::string &TestbCommand::name() const {
    return TESTB;
}

bool TestbCommand::match(int opcode) const {
    return (opcode & 0177700) == 0105700;
}

void TestbCommand::exec(int opcode, Machine &m) const {
    logDebug(m);
    Operand dd = Operand::DD(opcode, CommandMode::BYTE);
    PdpByte byte = dd.eval(m).getByte();
    m.logger().debug() << ' ' << "Z:" << m.psw.zeroBit << ' ' << "N:" << m.psw.negBit;
    m.psw.zeroBit = (byte == 0);
    m.psw.negBit = int8_t(byte) < 0;
}

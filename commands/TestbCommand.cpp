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
    Operand dd = Operand::DD(opcode);
    PdpWord w = dd.readb(m);
    m.psw.zeroBit = w.low() == 0;
    m.psw.negBit = int8_t(w.low()) < 0;
    m.logger().debug([this, &dd, &m](Logger::OStreamWrapper& w) {
        w << name() << ' ' << dd.toStr(m) << ' ' << "Z:" << m.psw.zeroBit << ' ' << "N:" << m.psw.negBit << '\n';
    });
}

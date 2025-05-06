#include "JsrCommand.h"
#include "../Operand.h"

static std::string NAME = "JSR";

std::string& JsrCommand::name() const {
    return NAME;
}

bool JsrCommand::match(int opcode) const {
    return (opcode & 0777000) == 0004000;
}

void JsrCommand::exec(int opcode, Machine& m) const {
    int regIdx = (opcode & 0000700) >> 6;
    Operand dd = Operand::DD(opcode);
    PdpAddr addr = dd.readNoDeref(m);
    m.setWord(--m.sp(), m.reg(regIdx));
    m.reg(regIdx) = m.pc();
    m.pc() = addr;
    m.logger().debug([this, &dd, &m](Logger::OStreamWrapper& w) {
        w << name() << " proc " << m.pc() << " ret " << m.getWord(m.sp()) << '\n';
    });
}

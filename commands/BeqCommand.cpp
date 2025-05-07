#include "BeqCommand.h"
#include "../Machine.h"

static std::string BEQ("BEQ");

const std::string& BeqCommand::name() const {
    return BEQ;
}

bool BeqCommand::match(int opcode) const {
    return (0177400 & opcode) == 0001400;
}

void BeqCommand::exec(int opcode, Machine& m) const {
    logDebug(m);
    char offset = char(opcode);
    if (m.psw.zeroBit) {
        m.pc() += 2 * offset;
    }
    m.logger().debug() << "goto " << m.pc();
}

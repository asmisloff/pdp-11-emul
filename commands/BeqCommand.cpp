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
    char offset = char(opcode);
    if (m.psw.zeroBit) {
        m.pc() += 2 * offset;
    }
    Logger& logger = m.logger();
    if (logger.level >= Logger::Level::DEBUG) {
        logger.debug() << name() << ' ' << m.pc() << '\n';
    }
}

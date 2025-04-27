#include "BrCommand.h"
#include "../Machine.h"

static std::string BR("BR");

const std::string& BrCommand::name() const {
    return BR;
}

bool BrCommand::match(int opcode) const {
    return (0177400 & opcode) == 0000400;
}

void BrCommand::exec(int opcode, Machine& m) const {
    char offset = char(opcode);
    m.pc() += 2 * offset;
    Logger& logger = m.logger();
    if (logger.level >= Logger::Level::DEBUG) {
        logger.debug() << name() << ' ' << m.pc() << '\n';
    }
}
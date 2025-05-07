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
    logDebug(m);
    char offset = char(opcode);
    m.pc() += 2 * offset;
    m.logger().debug() << "goto " << m.pc();
}
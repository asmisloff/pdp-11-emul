#include "BplCommand.h"
#include "../Operand.h"

static const std::string BPL("BPL");

const std::string &BplCommand::name() const {
    return BPL;
}

bool BplCommand::match(int opcode) const {
    return (0177400 & opcode) == 0100000;
}

void BplCommand::exec(int opcode, Machine &m) const {
    logDebug(m);
    if (!m.psw.negBit) {
        m.pc() += 2 * char(opcode);
    }
    m.logger().debug() << "goto " << ' ' << m.pc();
}

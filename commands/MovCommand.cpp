#include "MovCommand.h"

static const std::string MOV = "MOV";

const std::string& MovCommand::name() const { return MOV; }

bool MovCommand::match(int opcode) const {
    return (0170000 & opcode) == 0010000;
}

void MovCommand::exec(int opcode, Machine& m) const {
    auto [ss, dd] = getOperands(opcode, m);
    PdpWord value = ss.read(m);
    dd.write(m, value);
}

std::pair<Operand, Operand> MovCommand::getOperands(int opcode, Machine& m) const {
    Operand ss = Operand::SS(opcode);
    Operand dd = Operand::DD(opcode);
    Logger& logger = m.logger();
    if (logger.level >= Logger::Level::DEBUG) {
        logger.debug() << name() << ' ' << ss.toStr(m) << ' ' << dd.toStr(m) << '\n';
    }
    return { ss, dd };
}
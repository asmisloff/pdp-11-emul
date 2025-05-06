#include "RtsCommand.h"
#include "../Machine.h"

static std::string NAME = "RTS";

const std::string& RtsCommand::name() const {
    return NAME;
}

bool RtsCommand::match(int opcode) const {
    return (opcode & 0777770) == 0000200;
}

void RtsCommand::exec(int opcode, Machine& m) const {
    int regIdx = opcode & 0000007;
    m.pc() = m.reg(regIdx);
    m.reg(regIdx) = m.getWord(m.sp()++);
    m.logger().debug([this, &regIdx, &m](Logger::OStreamWrapper& w) {
        w << name() << " R" << regIdx << ' ' << m.pc() << '\n';
    });
}

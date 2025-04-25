#include "MovbCommand.h"

static const std::string MOVb = "MOVb";

const std::string& MovbCommand::name() const {
    return MOVb;
}

bool MovbCommand::match(int opcode) const {
    return (0170000 & opcode) == 0110000;
}

void MovbCommand::exec(int opcode, Machine& m) const {
    auto [ss, dd] = getOperands(opcode, m);
    PdpWord value = ss.readb(m);
    dd.writeb(m, value.low());
}
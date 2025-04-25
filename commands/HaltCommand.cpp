#include "HaltCommand.h"
#include "../Machine.h"

static const std::string HALT = "HALT";

const std::string& HaltCommand::name() const { 
    return HALT; 
}

bool HaltCommand::match(int opcode) const {
    return (0177777 & opcode) == 0;
}

void HaltCommand::exec(int opcode, Machine& m) const {
    (void)opcode;
    m.logger().debug() << name().c_str() << '\n';
}
#ifndef BR_COMMAND_H
#define BR_COMMAND_H

#include "Command.h"

class BrCommand : public Command {
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const override;
};

#endif
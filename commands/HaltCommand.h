#ifndef HALT_COMMAND_H
#define HALT_COMMAND_H

#include "Command.h"

class HaltCommand : public Command {
public:
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const override;
};

#endif
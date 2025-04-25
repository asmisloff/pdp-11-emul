#ifndef CLR_COMMAND_H
#define CLR_COMMAND_H

#include "Command.h"

class ClrCommand : public Command {
public:
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const override;
};

#endif
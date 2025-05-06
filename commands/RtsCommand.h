#ifndef RTS_COMMAND_H
#define RTS_COMMAND_H

#include "Command.h"

class RtsCommand : public Command {
public:
    virtual const std::string& name() const override;
    virtual bool match(int opcode) const override;
    virtual void exec(int opcode, Machine& m) const override;
};

#endif
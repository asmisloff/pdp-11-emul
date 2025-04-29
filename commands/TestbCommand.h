#ifndef TESTB_COMMAND_H
#define TESTB_COMMAND_H

#include "Command.h"

class TestbCommand : public Command {
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const override;
};

#endif
#ifndef MOVBCOMMAND_H
#define MOVBCOMMAND_H

#include "./Command.h"
#include "./MovCommand.h"

class MovbCommand : public Command {
public:
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const;
};

#endif
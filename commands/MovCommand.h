#ifndef MOVCOMMAND_H
#define MOVCOMMAND_H

#include "Command.h"
#include "../Operand.h"

class MovCommand : public Command {
public:
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const override;
protected:
    std::pair<Operand, Operand> getOperands(int opcode, Machine& m) const;
};

#endif
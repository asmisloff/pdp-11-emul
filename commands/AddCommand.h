#ifndef _ADDCOMMAND_H
#define _ADDCOMMAND_H

#include "Command.h"

class AddCommand : public Command {
public:
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const override;
};

#endif
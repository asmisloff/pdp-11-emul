#ifndef JsrCommand_H
#define JsrCommand_H

#include "Command.h"

class JsrCommand : public Command {
public:
    virtual std::string& name() const override;
    virtual bool match(int opcode) const override;
    virtual void exec(int opcode, Machine& m) const override;
};

#endif
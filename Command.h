#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "PdpTypes.h"

class Machine;

class Command {
public:
    Command(std::string&& name, int mask, int prefix);
    virtual ~Command() {}
    const std::string& name() const;
    bool match(int opcode) const;
    virtual void exec(int opcode, Machine& m) const = 0;
protected:
    const std::string name_;
    const int mask_;
    const int prefix_;
    void logDebug(Machine& m) const;
};

struct AddCommand : public Command {
    AddCommand();
    void exec(int opcode, Machine& m) const override;
};

struct BeqCommand : public Command {
    BeqCommand();
    void exec(int opcode, Machine& m) const override;
};

struct BplCommand : public Command {
    BplCommand();
    void exec(int opcode, Machine& m) const override;
};

struct BrCommand : public Command {
    BrCommand();
    void exec(int opcode, Machine& m) const override;
};

struct ClrCommand : public Command {
    ClrCommand();
    void exec(int opcode, Machine& m) const override;
};

struct HaltCommand : public Command {
    HaltCommand();
    void exec(int opcode, Machine& m) const override;
};

struct JsrCommand : public Command {
    JsrCommand();
    void exec(int opcode, Machine& m) const override;
};

struct MovCommand : public Command {
    MovCommand();
    void exec(int opcode, Machine& m) const override;
};

struct MovbCommand : public Command {
    MovbCommand();
    void exec(int opcode, Machine& m) const override;
};

struct RtsCommand : public Command {
    RtsCommand();
    void exec(int opcode, Machine& m) const override;
};

struct SobCommand : public Command {
    SobCommand();
    void exec(int opcode, Machine& m) const override;
};

struct TestCommand : public Command {
    TestCommand();
    void exec(int opcode, Machine& m) const override;
};

struct TestbCommand : public Command {
    TestbCommand();
    void exec(int opcode, Machine& m) const override;
};

struct IncCommand : public Command {
    IncCommand();
    void exec(int opcode, Machine& m) const override;
};

struct RolCommand : public Command {
    RolCommand();
    void exec(int opcode, Machine& m) const override;
};

struct AshCommand : public Command {
    AshCommand();
    void exec(int opcode, Machine& m) const override;
};

struct BicCommand : public Command {
    BicCommand();
    void exec(int opcode, Machine& m) const override;
};

struct AslCommand : public Command {
    AslCommand();
    void exec(int opcode, Machine& m) const override;
};

#endif
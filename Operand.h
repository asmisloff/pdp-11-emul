#ifndef OPERAND_H
#define OPERAND_H

#include "Machine.h"
#include "PdpRef.h"

enum CommandMode { WORD, BYTE };

class Operand {
public:
    static Operand SS(int opcode, CommandMode cmdMode);
    static Operand DD(int opcode, CommandMode cmdMode);
    int mode() const { return mode_; }
    int regIdx() const { return regIdx_; }
    PdpRef eval(Machine& m) const;
    void incReg(Machine& m) const;
    void decReg(Machine& m) const;
private:
    Operand() = delete;
    Operand(char mode, char reg, CommandMode cmdMode);
    char mode_;
    char regIdx_;
    CommandMode cmdMode_;
};

#endif // OPERAND_H
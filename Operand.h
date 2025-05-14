#ifndef OPERAND_H
#define OPERAND_H

#include "Machine.h"
#include "PdpRef.h"

/** Режим команды. */
enum CommandMode { WORD, BYTE };

/** Операнд команды. */
class Operand {
public:
    
    static Operand SS(int opcode, CommandMode cmdMode);
    
    static Operand DD(int opcode, CommandMode cmdMode);
    
    /** Мода. */
    int mode() const { return mode_; }

    /** Индекс регистра. */
    int regIdx() const { return regIdx_; }

    /** Вычислить операнд и вернуть ссылку на ресурс (ячейку памяти или регистр). */
    PdpRef eval(Machine& m) const;

    /** Инкрементировать значение в регистре. На 1 или 2 в зависимости от командного режима. */
    void incReg(Machine& m) const;

    /** Декрементировать значение в регистре. На 1 или 2 в зависимости от командного режима. */
    void decReg(Machine& m) const;
    
private:
    Operand() = delete;
    Operand(char mode, char reg, CommandMode cmdMode);
    char mode_;
    char regIdx_;
    CommandMode cmdMode_;
};

#endif // OPERAND_H
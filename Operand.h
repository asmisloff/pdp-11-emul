#ifndef OPERAND_H
#define OPERAND_H

#include "./Machine.h"

class Operand {
 public:
  static Operand SS(int opcode);
  static Operand DD(int opcode);
  int getMode() const { return mode; }
  int getReg() const { return reg; }
  PdpWord read(Machine& m);
  void write(Machine& m, PdpWord word);

 private:
  Operand();
  Operand(char mode, char reg) : mode{mode}, reg{reg}
    {};
  char mode;
  char reg;
};

#endif // OPERAND_H
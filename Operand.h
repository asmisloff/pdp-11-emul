#ifndef OPERAND_H
#define OPERAND_H

#include "./Machine.h"

class Operand {
 public:
  static Operand SS(int opcode);
  static Operand DD(int opcode);
  int mode() const { return mode_; }
  int reg() const { return reg_; }
  std::string to_string(Machine& m) const;
  PdpWord read(Machine& m);
  PdpWord readb(Machine& m);
  void write(Machine& m, PdpWord word);
  void writeb(Machine& m, PdpByte byte);

 private:
  Operand();
  Operand(char mode, char reg) : mode_{mode}, reg_{reg}
    {};
  char mode_;
  char reg_;
};

#endif // OPERAND_H
#include "./Operand.h"

Operand Operand::SS(int opcode) {
  const int mode = (opcode & 0007000) >> 9;
  const int reg = (opcode & 0000700) >> 6;
  return Operand(mode, reg);
}

Operand Operand::DD(int opcode) {
  const int mode = (opcode & 0000070) >> 3;
  const int reg = opcode & 0000007;
  return Operand(mode, reg);
}

PdpWord Operand::read(Machine& m) {
  switch (mode) {
    case 0:
      return m.reg(reg);
    case 1:
      return m.getMemory().getWord(m.reg(reg));
    case 2:
      return m.getMemory().getWord(m.reg(reg)++);
    default:
      throw std::logic_error("Unsupported mode");
  }
}

void Operand::write(Machine& m, PdpWord word) {
  switch (mode) {
    case 0: 
      m.reg(reg) = word;
      break;
    case 1:
      m.getMemory().setWord(m.reg(reg), word);
      break;
    case 2: 
      m.getMemory().setWord(m.reg(reg)++, word);
      break;
    default:
      throw std::logic_error("Unsupported mode");
  }
}
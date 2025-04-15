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
  switch (mode_) {
    case 0:
      return m.reg(reg_);
    case 1:
      return m.mem().getWord(m.reg(reg_));
    case 2:
      return m.mem().getWord(m.reg(reg_)++);
    default:
      throw std::logic_error("Unsupported mode");
  }
}

void Operand::write(Machine& m, PdpWord word) {
  switch (mode_) {
    case 0: 
      m.reg(reg_) = word;
      break;
    case 1:
      m.mem().setWord(m.reg(reg_), word);
      break;
    case 2: 
      m.mem().setWord(m.reg(reg_)++, word);
      break;
    default:
      throw std::logic_error("Unsupported mode");
  }
}

std::string Operand::to_string(Machine& m) const {
  switch (mode_) {
    case 0:
      return "R" + std::to_string(reg_);
    case 1: case 2: {
      PdpWord ptr = m.reg(reg_);
      PdpWord word = m.mem().getWord(ptr);
      return "#" + std::to_string(word.intValue());
    }
    default:
      throw std::logic_error("Unsopported mode");      
  }   
}
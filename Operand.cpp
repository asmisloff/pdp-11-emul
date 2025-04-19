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
    case 3: {
      PdpWord ptrArrd = m.reg(reg_)++;
      PdpWord addr = m.mem().getWord(ptrArrd);
      return m.mem().getWord(addr);
    }
    case 4: {
      return m.mem().getWord(--m.reg(reg_));
    }
    default:
      throw std::logic_error("Unsupported mode -- Operand::read");
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
    case 3: {
      PdpWord ptrArrd = m.reg(reg_)++;
      PdpWord addr = m.mem().getWord(ptrArrd);
      m.mem().setWord(addr, word);
      break;
    }
    case 4: {
      m.mem().setWord(--m.reg(reg_), word);
      break;
    }
    default:
      throw std::logic_error("Unsupported mode -- Operand::write");
  }
}

std::string Operand::to_string(Machine& m) const {
  std::stringstream ss;
  switch (mode_) {
    case 0:
      ss << "R" << static_cast<int>(reg_);
      break;
    case 1: case 2: {
      if (reg_ == 7) { // Операнд в оперативной памяти - показать его значение.
        PdpWord ptr = m.reg(reg_);
        ss << "#" << std::oct << m.mem().getWord(ptr).intValue();
      } else { // Если другой регистр, то его номер в скобках.
        ss << "(R" << static_cast<int>(reg_) << ")";
      }
      break;
    }
    case 3: {
      if (reg_ == 7) {
        PdpWord ptr = m.reg(reg_);
        ss << "@#" << std::oct << m.mem().getWord(ptr).intValue();
      } else {
        ss << "@(R" << static_cast<int>(reg_) << ")";
      }
      break;
    }
    case 4: {
      ss << "-(R" << static_cast<int>(reg_) << ")";
      break;
    }
    default:
      throw std::logic_error("Unsupported mode -- Operand::to_strig");      
  }
  return ss.str();
}
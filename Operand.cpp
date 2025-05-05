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

/* TODO: устранить дублирование.
         - Вар.: разложить функции getValue по индексам мод.
         - Перенести отладочное логирование в getValue. */
PdpWord Operand::read(Machine& m) {
  switch (mode_) {
    case 0:
      return m.reg(reg_);
    case 1:
      return m.getWord(m.reg(reg_));
    case 2:
      return m.getWord(m.reg(reg_)++);
    case 3: {
      PdpWord addrOfAddr = m.reg(reg_)++;
      PdpWord addr = m.getWord(addrOfAddr);
      return m.getWord(addr);
    }
    case 4: {
      return m.getWord(--m.reg(reg_));
    }
    case 5: {
      PdpWord addrOfAddr = --m.reg(reg_);
      PdpWord addr = m.getWord(addrOfAddr);
      return m.getWord(addr);
    }
    case 6: {
      int16_t offset = m.getWord(m.pc()++).toSigned();
      PdpAddr addr = m.reg(reg_).toUnsigned() + offset;
      return m.getWord(addr);
    }
    case 7: {
      int16_t offset = m.getWord(m.pc()++).toSigned();
      PdpAddr addrOfAddr = m.reg(reg_).toUnsigned() + offset;
      PdpAddr addr = m.getWord(addrOfAddr);
      return m.getWord(addr);
    }
    default:
      throw std::logic_error("Unsupported mode -- Operand::read");
  }
}

PdpWord Operand::readb(Machine& m) {
  if (reg_ > 5) {
    return read(m);
  }
  if (mode_ == 2) {
    PdpWord addr = m.reg(reg_);
    m.reg(reg_) += 1;
    return PdpWord::fromByte(m.getByte(addr));
  }
  if (mode_ == 4) {
    PdpWord& addr = m.reg(reg_);
    addr -= 1;
    return PdpWord::fromByte(m.getByte(addr));
  }
  return PdpWord::fromByte(read(m).low());
}

void Operand::write(Machine& m, PdpWord word) {
  switch (mode_) {
    case 0: 
      m.reg(reg_) = word;
      break;
    case 1:
      m.setWord(m.reg(reg_), word);
      break;
    case 2: 
      m.setWord(m.reg(reg_)++, word);
      break;
    case 3: {
      PdpWord addrOfAddr = m.reg(reg_)++;
      PdpWord addr = m.getWord(addrOfAddr);
      m.setWord(addr, word);
      break;
    }
    case 4: {
      m.setWord(--m.reg(reg_), word);
      break;
    }
    case 5: {
      PdpWord ptrArrd = --m.reg(reg_);
      PdpWord addr = m.getWord(ptrArrd);
      m.setWord(addr, word);
      break;
    }
    case 6: {
      PdpWord offset = m.getWord(m.pc()++);
      PdpAddr addr = m.reg(reg_).toUnsigned() + offset.toSigned();
      m.setWord(addr, word);
      break;
    }
    case 7: {
      int16_t offset = m.getWord(m.pc()++).toSigned();
      PdpAddr addrOfAddr = m.reg(reg_).toUnsigned() + offset;
      PdpAddr addr = m.getWord(addrOfAddr);
      m.setWord(addr, word);
      break;
    }
    default:
      throw std::logic_error("Unsupported mode -- Operand::write");
  }
}

void Operand::writeb(Machine& m, PdpByte byte) {
  if (reg_ > 5 || mode_ == 0) {
    return write(m, PdpWord::fromByte(byte));
  }
  switch (mode_) {
    case 1: {
      m.setByte(m.reg(reg_), byte);
      break;
    }
    case 2: {
      PdpWord addr = m.reg(reg_);
      m.reg(reg_) += 1;
      m.setByte(addr, byte);
      break;
    }
    case 3: {
      PdpWord addrOfAddr = m.reg(reg_)++;
      PdpWord addr = m.getWord(addrOfAddr);
      m.setByte(addr, byte);
      break;
    }
    case 4: {
      PdpWord& addr = m.reg(reg_);
      addr -= 1;
      m.setByte(addr, byte);
      break;
    }
    case 5: {
      PdpWord ptrArrd = --m.reg(reg_);
      PdpWord addr = m.getWord(ptrArrd);
      m.setByte(addr, byte);
      break;
    }
    case 6: {
      PdpWord offset = m.getWord(m.pc()++);
      PdpAddr addr = m.reg(reg_).toUnsigned() + offset.toSigned();
      m.setByte(addr, byte);
      break;
    }
    case 7: {
      int16_t offset = m.getWord(m.pc()++).toSigned();
      PdpAddr addrOfAddr = m.reg(reg_).toUnsigned() + offset;
      PdpAddr addr = m.getWord(addrOfAddr);
      m.setByte(addr, byte);
      break;
    }
    default: {
      throw std::logic_error("Operand::writeb -- Unsupported mode: " + std::to_string(mode_));
    }
  }
}

std::string Operand::toStr(Machine& m) const {
  std::stringstream ss;
  switch (mode_) {
    case 0:
      ss << "R" << static_cast<int>(reg_);
      break;
    case 1: {
      if (reg_ == 7) { // Операнд в оперативной памяти - показать его значение.
        PdpWord ptr = m.reg(reg_);
        ss << "#" << std::oct << m.getWord(ptr).toUnsigned();
      } else { // Если другой регистр, то его номер в скобках.
        ss << "(R" << static_cast<int>(reg_) << ")";
      }
      break;
    }
    case 2: {
      if (reg_ == 7) { // Операнд в оперативной памяти - показать его значение.
        PdpWord ptr = m.reg(reg_);
        ss << "#" << std::oct << m.getWord(ptr).toUnsigned();
      } else { // Если другой регистр, то его номер в скобках.
        ss << "(R" << static_cast<int>(reg_) << ")+";
      }
      break;
    }
    case 3: {
      if (reg_ == 7) {
        PdpWord ptr = m.reg(reg_);
        ss << "@#" << std::oct << m.getWord(ptr).toUnsigned();
      } else {
        ss << "@(R" << static_cast<int>(reg_) << ")";
      }
      break;
    }
    case 4: {
      ss << "-(R" << static_cast<int>(reg_) << ")";
      break;
    }
    case 5: {
      ss << "@-(R" << static_cast<int>(reg_) << ")";
      break;
    }
    case 6: {
      int16_t offset = m.getWord(m.pc()).toSigned();
      ss << offset << "(R" << static_cast<int>(reg_) << ")";
      break;
    }
    case 7: {
      int16_t offset = m.getWord(m.pc()).toSigned();
      ss << '@' << offset << "(R" << static_cast<int>(reg_) << ")";
      break;
    }
    default:
      throw std::logic_error("Unsupported mode -- Operand::to_string");      
  }
  return ss.str();
}
#include "AddCommand.h"
#include "../Operand.h"

static const std::string ADD = "ADD";

const std::string& AddCommand::name() const { 
    return ADD; 
}

bool AddCommand::match(int opcode) const { 
    return (0170000 & opcode) == 060000; 
}

void AddCommand::exec(int opcode, Machine& m) const {
  Operand ss = Operand::SS(opcode);
  Operand dd = Operand::DD(opcode);
  Logger& logger = m.logger();
  if (logger.level >= Logger::Level::DEBUG) {
    logger.debug() << name() << ' ' << ss.toStr(m) << ' ' << dd.toStr(m) << '\n';
  }
  PdpWord v1 = ss.read(m);
  PdpWord v2 = dd.read(m);
  PdpWord sum = v1 + v2;
  int ref = v1.toSigned() + v2.toSigned();
  m.psw = { .zeroBit = (sum == 0), .negBit = (sum.toSigned() < 0), .carryBit = (ref > 0xffff) };
  dd.write(m, sum);
}
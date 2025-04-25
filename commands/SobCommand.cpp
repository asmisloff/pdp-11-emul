#include "SobCommand.h"
#include "../Logger.h"
#include "../Machine.h"

static const std::string SOB = "SOB";

const std::string& SobCommand::name() const { 
    return SOB; 
}

bool SobCommand::match(int opcode) const { 
    return (0177000 & opcode) == 0077000; 
}

void SobCommand::exec(int opcode, Machine& m) const {
  int regIndex = (opcode & 0000700) >> 6;
  PdpWord& reg = m.reg(regIndex);
  int offset = (opcode & 0000077) * 2;
  reg -= 1;
  if (reg.intValue() > 0) {
    m.pc() -= offset;
  }
  if (m.logger().level >= Logger::Level::DEBUG) {
    m.logger().debug() << name().c_str() << ' ' << 'R' << regIndex << ' '
                       << PdpWord(m.pc().intValue() - offset) << '\n';
  }
}
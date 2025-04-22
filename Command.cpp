#include "./Command.h"
#include "./Machine.h"
#include "./Logger.h"
#include "./Operand.h"

static const std::string MOV = "MOV";
static const std::string MOVb = "MOVb";
static const std::string ADD = "ADD";
static const std::string HALT = "HALT";
static const std::string SOB = "SOB";
static const std::string CLR = "CLR";

const std::string& MovCommand::name() const { return MOV; }
bool MovCommand::match(int opcode) const { return (0170000 & opcode) == 0010000; }
std::pair<Operand, Operand> MovCommand::getOperands(int opcode, Machine& m) const {
  Operand ss = Operand::SS(opcode);
  Operand dd = Operand::DD(opcode);
  Logger& logger = m.logger();
  if (logger.level >= Logger::Level::DEBUG) {
    const char *cmd_name = name().c_str();
    std::string ss_str = ss.to_string(m);
    std::string dd_str = dd.to_string(m);
    logger.debug() << cmd_name << ' ' << ss_str.c_str() << ' ' << dd_str.c_str() << '\n';
  }
  return { ss, dd };
}

void MovCommand::exec(int opcode, Machine& m) const {
  auto [ss, dd] = getOperands(opcode, m);
  PdpWord value = ss.read(m);
  dd.write(m, value);
}


const std::string& MovbCommand::name() const { return MOVb; }
bool MovbCommand::match(int opcode) const { return (0170000 & opcode) == 0110000; }
void MovbCommand::exec(int opcode, Machine& m) const {
  auto [ss, dd] = getOperands(opcode, m);
  PdpWord value = ss.readb(m);
  dd.writeb(m, value.low());
}


const std::string& AddCommand::name() const { return ADD; }
bool AddCommand::match(int opcode) const { return (0170000 & opcode) == 060000; }
void AddCommand::exec(int opcode, Machine& m) const {
  Operand ss = Operand::SS(opcode);
  Operand dd = Operand::DD(opcode);
  Logger& logger = m.logger();
  if (logger.level >= Logger::Level::DEBUG) {
    const char *cmd_name = name().c_str();
    std::string ss_str = ss.to_string(m);
    std::string dd_str = dd.to_string(m);
    logger.debug() << cmd_name << ' ' << ss_str.c_str() << ' ' << dd_str.c_str() << '\n';
  }
  PdpWord v1 = ss.read(m);
  PdpWord v2 = dd.read(m);
  dd.write(m, v1 + v2);
}


const std::string& SobCommand::name() const { return SOB; }
bool SobCommand::match(int opcode) const { return (0177000 & opcode) == 0077000; }
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


const std::string& ClrCommand::name() const { return CLR; }
bool ClrCommand::match(int opcode) const { return (0177700 & opcode) == 005000; }
void ClrCommand::exec(int opcode, Machine& m) const {
  Operand dd = Operand::DD(opcode);
  Logger& logger = m.logger();
  if (logger.level >= Logger::Level::DEBUG) {
    const char *cmd_name = name().c_str();
    std::string dd_str = dd.to_string(m);
    logger.debug() << cmd_name << ' ' << dd_str.c_str() << '\n';
  }
  dd.write(m, 0);
}


const std::string& HaltCommand::name() const { return HALT; }
bool HaltCommand::match(int opcode) const { return (0177777 & opcode) == 0; }
void HaltCommand::exec(int opcode, Machine& m) const {
  (void)opcode;
  m.logger().debug() << name().c_str() << '\n';
}

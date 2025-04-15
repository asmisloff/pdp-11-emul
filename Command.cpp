#include "./Command.h"
#include "./Machine.h"
#include "./Logger.h"
#include "./Operand.h"

static const std::string MOV = "MOV";
static const std::string ADD = "ADD";
static const std::string HALT = "HALT";

const std::string& MovCommand::name() const { return MOV; }

bool MovCommand::match(int opcode) const {
  return (0170000 & opcode) == 010000;
}

void MovCommand::exec(int opcode, Machine& m) const {
  Operand ss = Operand::SS(opcode);
  Operand dd = Operand::DD(opcode);
  Logger& logger = m.logger();
  if (logger.level >= Logger::Level::DEBUG) {
    const char *cmd_name = name().c_str();
    std::string ss_str = ss.to_string(m);
    std::string dd_str = dd.to_string(m);
    logger.debug << cmd_name << ' ' << ss_str.c_str() << ' ' << dd_str.c_str() << '\n';
  }
  PdpWord value = ss.read(m);
  dd.write(m, value);
}

const std::string& AddCommand::name() const { return ADD; }

bool AddCommand::match(int opcode) const {
  return (0170000 & opcode) == 060000;
}

void AddCommand::exec(int opcode, Machine& m) const {
  Operand ss = Operand::SS(opcode);
  Operand dd = Operand::DD(opcode);
  Logger& logger = m.logger();
  if (logger.level >= Logger::Level::DEBUG) {
    const char *cmd_name = name().c_str();
    std::string ss_str = ss.to_string(m);
    std::string dd_str = dd.to_string(m);
    logger.debug << cmd_name << ' ' << ss_str.c_str() << ' ' << dd_str.c_str() << '\n';
  }
  PdpWord v1 = ss.read(m);
  PdpWord v2 = dd.read(m);
  dd.write(m, v1 + v2);
}

const std::string& HaltCommand::name() const { return HALT; }

bool HaltCommand::match(int opcode) const { return (0177777 & opcode) == 0; }

void HaltCommand::exec(int opcode, Machine& m) const {
  (void)opcode;
  m.logger().debug << name().c_str() << '\n';
}

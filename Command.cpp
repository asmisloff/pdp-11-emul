#include "./Command.h"
#include "./Machine.h"
#include "./Logger.h"
#include "./Operand.h"

#include <ios>
#include <iostream>
#include <sstream>

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
  PdpWord value = ss.read(m);
  dd.write(m, value);
  if (m.getLogger().getLevel() >= DEBUG) {
    std::stringstream ss;
    ss << name() << ' ' << value << ' ' << dd.getReg();
    m.getLogger().debug("%s\n", ss.str().c_str());
  }
}

const std::string& AddCommand::name() const { return ADD; }

bool AddCommand::match(int opcode) const {
  return (0170000 & opcode) == 060000;
}

void AddCommand::exec(int opcode, Machine& m) const {
  const int s_mode = (opcode & 0007000) >> 9;
  const int s_reg = (opcode & 0000700) >> 6;
  const int d_mode = (opcode & 0000070) >> 3;
  const int d_reg = opcode & 0000007;
  m.getLogger().debug("%s %d %d %d %d\n", name().c_str(), s_mode, s_reg, d_mode, d_reg);
}

const std::string& HaltCommand::name() const { return HALT; }

bool HaltCommand::match(int opcode) const { return (0177777 & opcode) == 0; }

void HaltCommand::exec(int opcode, Machine& m) const {
  (void)opcode;
  m.getLogger().debug("%s\n", name().c_str());
}
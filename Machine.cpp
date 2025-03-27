#include <algorithm>
#include <string>

#include "./Machine.h"
#include "./Loader.h"
#include "./PdpTypes.h"
#include "Command.h"

const AddCommand  Machine::ADD;
const MovCommand  Machine::MOV;
const HaltCommand Machine::HALT;

const std::vector<const Command*> Machine::commands = {
  &Machine::ADD, 
  &Machine::MOV,
  &Machine::HALT
};

Machine::Machine() 
  : loader{Loader(&mem)}
  , regs{0, 0, 0, 0, 0, 0, 0, 0}
{}

PdpWord& Machine::pc() { 
  return regs[7];
}

const Command* getCommand(int opcode) {
  auto begin = Machine::commands.begin();
  auto end = Machine::commands.end();
  auto pred = [opcode](const Command* cmd) { return cmd->match(opcode); };
  auto it = std::find_if(begin, end, pred);
  if (it == end) {
    return nullptr;
  }
  return *it;
}

void Machine::run(std::istream& is) {
  loader.load(is);
  pc() = 01000;
  const Command *cmd = nullptr;
  do {
    int value = mem.getWord(pc()++);
    cmd = getCommand(value);
    // todo
  } while (cmd != &HALT);
  std::cout << "THE END!\n";
  exit(0);
}

void Machine::trace_commands(std::istream& is) {
  loader.load(is);
  pc() = 01000;
  const Command *cmd = nullptr;
  setLoggingLevel(DEBUG);
  do {
    int opcode = mem.getWord(pc()++);
    cmd = getCommand(opcode);
    cmd->exec(opcode, *this);
    // logger.trace("%06o %06o: %s\n", address, opcode, cmd->to_string(opcode, *this));
  } while (cmd != &HALT);
  std::cout << "THE END!\n";
  exit(0);
}

void Machine::setLoggingLevel(LoggingLevel level) {
  logger.setLevel(level);
}
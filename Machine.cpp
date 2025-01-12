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
  &ADD, 
  &MOV,
  &HALT
};

Machine::Machine() 
  : loader{Loader(&mem)}
  , regs{0, 0, 0, 0, 0, 0, 0, 0}
{}

PdpWord Machine::pc() { 
  return regs[7];
}

void Machine::pc(PdpWord w) {
  regs[7] = w;
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
  pc(01000);
  PdpWord w(0);
  const Command *cmd = nullptr;
  do {
    uint16_t address = pc().intValue();
    int value = mem.getWord(address).intValue();
    cmd = getCommand(value);
    auto name = (cmd == nullptr) ? "UNKNOWN" : cmd->name();
    logger.trace("%06o %06o: %s\n", address, value, name.c_str());
    pc(address + 2);
  } while (cmd != &HALT);
  std::cout << "THE END!\n";
  exit(0);
}

void Machine::setLoggingLevel(LoggingLevel level) {
  logger.setLevel(level);
}
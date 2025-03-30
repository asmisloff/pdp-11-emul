#include <algorithm>
#include <string>

#include "./Machine.h"
#include "./Loader.h"
#include "./PdpTypes.h"
#include "./Command.h"
#include "./Operand.h"

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
    int opcode = mem.getWord(pc());
    logger.debug("%06o %06o: ", pc().intValue(), opcode);
    pc()++;
    cmd = getCommand(opcode);
    cmd->exec(opcode, *this);
  } while (cmd != &HALT);
  if (logger.getLevel() == DEBUG) {
    for (int i = 0; i < 8; i++) {
      logger.debug("R%d:%o ", i, regs[i].intValue());
    }
    std::cout << std::endl;
  }
}

void Machine::setLoggingLevel(LoggingLevel level) {
  logger.setLevel(level);
}

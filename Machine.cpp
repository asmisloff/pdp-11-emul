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
  : loader_{Loader(&mem_)}
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
  loader_.load(is);
  pc() = 01000;
  const Command *cmd = nullptr;
  do {
    int opcode = mem_.getWord(pc());
    logger().debug() << pc() << ' ' << std::oct << PdpWord(opcode) << '\n';
    pc()++;
    cmd = getCommand(opcode);
    cmd->exec(opcode, *this);
  } while (cmd != &HALT);
  if (logger_.level == Logger::Level::DEBUG) {
    for (int i = 0; i < 8; i++) {
      logger().debug() << 'R' << i << ':' << std::oct << regs[i].intValue() << ' ';
    }
    std::cout << std::endl;
  }
}

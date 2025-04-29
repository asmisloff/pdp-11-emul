#include <algorithm>
#include <string>

#include "Machine.h"
#include "Loader.h"
#include "PdpTypes.h"
#include "Operand.h"
#include "Machine.h"
#include "commands/all.h"

static const AddCommand  ADD;
static const MovCommand  MOV;
static const MovbCommand  MOVb;
static const SobCommand  SOB;
static const HaltCommand HALT;
static const ClrCommand  CLR;
static const BrCommand BR;
static const BeqCommand BEQ;
static const TestbCommand TESTb;
static const BplCommand BPL;

const std::vector<const Command*> Machine::commands = {
  &ADD, &MOV, &MOVb, &SOB, &HALT, &CLR, &BR, &BEQ, &TESTb, &BPL
};

Machine::Machine() 
  : loader_{Loader(&mem_)}
  , regs{0, 0, 0, 0, 0, 0, 0, 0}
{}

PdpWord &Machine::pc() {
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
    logger().debug() << pc() << ": ";
    pc()++;
    cmd = getCommand(opcode);
    if (cmd == nullptr) {
      throw std::invalid_argument("invalid opcode: " + std::to_string(opcode));
    }
    cmd->exec(opcode, *this);
  } while (cmd != &HALT);
  logger().debug([this](Logger::OStreamWrapper& w) {
    for (int i = 0; i < 7; i++) {
      w << 'R' << i << ':' << std::oct << regs[i].toUnsigned() << ' ';
    }
    w << 'R' << 7 << ':' << std::oct << regs[7].toUnsigned() << '\n';
    w << "Z:" << psw.zeroBit << " N:" << psw.negBit << " C:" << psw.carryBit << '\n';
  });
}

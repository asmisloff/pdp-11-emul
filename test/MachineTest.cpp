#include <cassert>
#include <cstring>
#include <fstream>

#include "../Machine.h"

void testMachineCommands() {
  std::cout << "Machine commands: ";
  Machine m;
  auto commands = m.commands;
  assert(commands[0]->name() == "ADD");
  assert(commands[1]->name() == "MOV");
  assert(commands[2]->name() == "HALT");
  std::cout << "PASSED\n";
}

void testMachineRun() {
  std::cout << "Run: \n";
  Machine m;
  std::ifstream fs("./e2e/01_sum/01_sum.pdp.o");
  m.setLoggingLevel(DEBUG);
  m.run(fs);
  std::cout << "PASSED\n";
}

int main() {
  testMachineCommands();
  testMachineRun();
  return 0;
}
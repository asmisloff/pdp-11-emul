#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>

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

void testEmptyProgram() {
  std::cout << "Empty program: ";
  Machine m;
  m.logger().level = Logger::Level::DEBUG;
  m.logger().debug().setStream(std::make_unique<std::stringstream>());
  std::stringstream ss;
  ss << "200 2\n"
     << "0\n"
     << "0\n";
  m.run(ss);
  std::cout << static_cast<std::stringstream*>(m.logger().debug().stream())->str() << '\n';
  std::cout << "PASSED\n";
}

void testMachineRun() {
  std::cout << "Run: \n";
  Machine m;
  std::ifstream fs("./e2e/01_sum/01_sum.pdp.o");
  m.logger().level = Logger::Level::DEBUG;
  m.run(fs);
  std::cout << "PASSED\n";
}

int main() {
  testMachineCommands();
  testEmptyProgram();
  testMachineRun();
  return 0;
}
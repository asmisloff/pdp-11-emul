#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>

#include "../Machine.h"

std::string read(std::string path) {
  std::ifstream file(path);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void setupLogger(Machine& m) {
  m.logger().level = Logger::Level::DEBUG;
  m.logger().debug().setStream(std::make_unique<std::stringstream>());
}

std::string fromLoggerStringStream(Machine& m) {
  return static_cast<std::stringstream*>(m.logger().debug().stream())->str();
}

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
  setupLogger(m);
  std::stringstream ss;
  ss << "200 2\n"
     << "0\n"
     << "0\n";
  m.run(ss);
  std::string expected =  "001000 000000\n"
                          "HALT\n"
                          "R0:0 R1:0 R2:0 R3:0 R4:0 R5:0 R6:0 R7:1002\n";
  std::string actual = fromLoggerStringStream(m);
  assert(expected.compare(actual) == 0);
  std::cout << "PASSED\n";
}

void test_e2e_cases() {
  std::vector<std::string> names = { 
    "01_sum",
    "01_sum_mode1",
    "01_sum_mode1_big"
  };

  for (size_t i = 0; i < names.size(); ++i) {
    std::cout << names[i] << ": ";
    std::ifstream fs("./e2e/" + names[i] + "/" + names[i] + ".pdp.o");
    Machine m;
    setupLogger(m);
    m.run(fs);
    auto expected = read("./data/" + names[i] + "_expected.txt");
    auto actual = fromLoggerStringStream(m);
    assert(expected == actual);
    std::cout << "PASSED\n";
  }
}

int main() {
  testMachineCommands();
  testEmptyProgram();
  test_e2e_cases();
  return 0;
}

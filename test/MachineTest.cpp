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
  std::vector<std::string> expected = {"ADD", "MOV", "MOVb", "SOB", "HALT", "CLR"};
  assert(commands.size() == expected.size());
  for (size_t i = 0; i < commands.size(); ++i) {
    assert(commands[i]->name() == expected[i]);
  }
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
    "01_sum_mode1_big",
    "01_sum_neg",
    "02_sob",
    "02_sob_byte",
    "02_sob_mode3"
  };
  for (size_t i = 0; i < names.size(); ++i) {
    std::cout << names[i] << ": ";
    std::ifstream fs("./e2e/" + names[i] + "/" + names[i] + ".pdp.o");
    Machine m;
    setupLogger(m);
    m.run(fs);
    auto expected = read("./data/" + names[i] + "_expected.txt");
    auto actual = fromLoggerStringStream(m);
    // std::cout << actual << std::endl;
    assert(expected == actual);
    std::cout << "PASSED\n";
  }
}

void test_04_mode4() {
  std::cout << "04_mode4: ";
  std::ifstream ifs("./e2e/04_mode4/04_mode4.pdp.o");
  Machine m;
  setupLogger(m);
  try {
    m.run(ifs);
  } catch (std::out_of_range& e) {
    assert(strcmp(e.what(), "Illegal address: 0") == 0);
    for (PdpAddr addr = 02; addr < 01000; addr += 02) {
      assert(m.mem().getWord(addr).intValue() == 0014747);
    }
    std::cout << "PASSED\n";
  }
}

int main() {
  testMachineCommands();
  testEmptyProgram();
  test_e2e_cases();
  test_04_mode4();
  return 0;
}

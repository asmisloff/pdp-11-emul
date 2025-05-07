#include <iostream>
#include <cassert>

#include "../Operand.h"
#include "../Machine.h"

void testReadMode0() {
  std::cout << "testReadMode0: ";
  Machine m;
  PdpWord word = 012345;
  m.reg(2) = word;
  Operand op = Operand::SS(010200, WORD);
  assert(op.eval(m).getWord() == word);
  std::cout << "PASSED\n";
}

void testReadMode1() {
  std::cout << "testReadMode1: ";
  Machine m;
  PdpAddr addr = 012346;
  PdpWord expected = 013000;
  m.reg(2) = addr;
  m.setWord(addr, expected);
  Operand op = Operand::SS(011200, WORD);
  PdpWord actual = op.eval(m).getWord();
  assert(actual == expected);
  std::cout << "PASSED\n";
}

void testReadMode2() {
  std::cout << "testReadMode2: ";
  Machine m;
  PdpAddr addr = 012346;
  PdpWord expected = 013000;
  m.pc() = addr;
  m.setWord(addr, expected);
  Operand op = Operand::SS(012700, WORD);
  PdpWord actual = op.eval(m).getWord();
  assert(actual == expected);
  assert(m.pc() == PdpWord(addr + 2));
  std::cout << "PASSED\n";
}

int main() {
  testReadMode0();
  testReadMode1();
  testReadMode2();
}
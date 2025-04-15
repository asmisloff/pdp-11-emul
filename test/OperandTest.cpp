#include <iostream>
#include <cassert>

#include "../Operand.h"
#include "../Machine.h"

void testReadMode0() {
  Machine m;
  PdpWord word = 012345;
  m.reg(2) = word;
  Operand op = Operand::SS(010200);
  assert(op.read(m) == word);
  std::cout << "testReadMode0 passed\n";
}

void testReadMode1() {
  Machine m;
  PdpAddr addr = 012346;
  PdpWord expected = 013000;
  m.reg(2) = addr;
  m.mem().setWord(addr, expected);
  Operand op = Operand::SS(011200);
  PdpWord actual = op.read(m);
  assert(actual == expected);
  std::cout << "testReadMode1 passed\n";
}

void testReadMode2() {
  Machine m;
  PdpAddr addr = 012346;
  PdpWord expected = 013000;
  m.pc() = addr;
  m.mem().setWord(addr, expected);
  Operand op = Operand::SS(012700);
  PdpWord actual = op.read(m);
  assert(actual == expected);
  assert(m.pc() == PdpWord(addr + 2));
  std::cout << "testReadMode2 passed\n";
}

int main() {
  testReadMode0();
  testReadMode1();
  testReadMode2();
}
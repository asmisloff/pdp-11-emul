#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>

#include "../Memory.h"

void testGetAndSetByte() {
  Memory mem;
  PdpAddr addr = 13;
  PdpByte byte = 0x1A;
  assert(mem.getByte(addr) != byte);
  mem.setByte(addr, byte);
  assert(mem.getByte(addr) == byte);
}

void testGetAndSetWord() {
  Memory mem;
  PdpAddr addr = 12;
  PdpWord word(0xABCD);
  assert(mem.getWord(addr) != word);
  mem.setWord(addr, word);
  assert(mem.getWord(addr) == word);
  assert(mem.getByte(addr) == word.low());
  assert(mem.getByte(addr + 1) == word.high());
}

void testCheckWordAddr() {
  Memory mem;
  PdpAddr addr = 13;
  try {
    mem.getWord(addr);
    throw std::runtime_error(
        "Out of range exception expected, but nothing was thrown");
  } catch (std::out_of_range &e) {
    /* pass */
  }
}

void testDump() {
  Memory mem;
  PdpAddr begin = 14;
  PdpAddr end = 25;
  for (int addr = begin; addr < end; addr += 2) {
    mem.setWord(addr, PdpWord(addr));
  }
  std::string expected =
      "000016: 000016 000e\n"
      "000020: 000020 0010\n"
      "000022: 000022 0012\n"
      "000024: 000024 0014\n"
      "000026: 000026 0016\n"
      "000030: 000030 0018\n";
  std::stringstream ss;
  mem.dump(begin, end, ss);
  std::string actual = ss.str();
  assert(expected.compare(actual) == 0);
}

int main() {
  testGetAndSetByte();
  testGetAndSetWord();
  testCheckWordAddr();
  testDump();
  return 0;
}
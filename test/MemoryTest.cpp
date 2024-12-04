#include <cassert>
#include <stdexcept>

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
    throw std::runtime_error("Out of range exception expected, but nothing was thrown");
  } catch (std::out_of_range &e) {
    /* pass */
  }
}

int main() {
  testGetAndSetByte();
  testGetAndSetWord();
  testCheckWordAddr();
  return 0;
}
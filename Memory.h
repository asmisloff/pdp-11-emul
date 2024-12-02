#include <vector>
#include <cstddef>
#include <exception>
#include <stdexcept>

#include "./PdpTypes.h"

#ifndef RAM_H
#define RAM_H

constexpr int MEM_SIZE = 64 * 1024;

class Memory {
 public:
  Memory() : mem{std::vector<PdpByte>(MEM_SIZE)}
    {}

  PdpWord getWord(PdpAddr addr) const { 
    checkWordAddr(addr);
    PdpByte low = mem[addr];
    PdpByte high = mem[addr + 1];
    return PdpWord(low, high);
  }

  void setWord(PdpAddr addr, PdpWord word) {
    checkWordAddr(addr);
    mem[addr] = word.low();
    mem[addr + 1] = word.high();
  }

  PdpByte getByte(PdpAddr addr) const {
    return mem[addr];
  }

  void setByte(PdpAddr addr, PdpByte byte) { mem[addr] = byte; }

 private:
  void checkWordAddr(PdpAddr addr) const {
    if (addr % 2 != 0) {
      throw std::out_of_range("Illegal address");
    }
  }

  std::vector<PdpByte> mem;
};

#endif
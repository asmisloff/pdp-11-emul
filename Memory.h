#include <iostream>
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
  Memory();
  PdpWord getWord(PdpAddr addr) const;
  void setWord(PdpAddr addr, PdpWord word);
  PdpByte getByte(PdpAddr addr) const;
  void setByte(PdpAddr addr, PdpByte byte);
  void dump(PdpAddr begin, PdpAddr end, std::ostream &out = std::cout);

 private:
  void checkWordAddr(PdpAddr addr) const;
  std::vector<PdpByte> mem;
};

#endif
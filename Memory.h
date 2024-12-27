#include <iostream>
#include <vector>
#include <cstddef>
#include <exception>

#include "./PdpTypes.h"

#ifndef RAM_H
#define RAM_H

class Memory {
 public:
  Memory();
  PdpWord getWord(PdpAddr addr) const;
  void setWord(PdpAddr addr, PdpWord word);
  PdpByte getByte(PdpAddr addr) const;
  void setByte(PdpAddr addr, PdpByte byte);
  void fill(PdpByte val, PdpAddr begin = 0, PdpAddr end = lastAddress);
  void dump(PdpAddr begin, PdpAddr end, std::ostream &out = std::cout);
  static const PdpAddr lastAddress;
  static const unsigned int size;

 private:
  void checkWordAddr(PdpAddr addr) const;
  std::vector<PdpByte> mem;
};

#endif
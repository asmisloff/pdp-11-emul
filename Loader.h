#include <istream>
#include <string>

#include "./Memory.h"

#ifndef LOADER_H
#define LOADER_H

class Loader {
 public:
  Loader(Memory *mem);
  void load(std::istream &is);
  void load(const std::string &filePath);

 private:
  Memory *mem;
  PdpAddr addr;
  PdpAddr end;
  std::string line;
  void parseBlockHeader(std::istream &is);
  void readData(std::istream &is);
};

#endif
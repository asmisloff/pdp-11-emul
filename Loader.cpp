#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "Loader.h"

Loader::Loader(Memory *mem) 
  : mem {mem}
  , offset {0}
  , cnt {0}
  , line {std::string(10, '\0')}
  {}

void Loader::load(std::istream &is) {
  while (is) {
    parseBlockHeader(is);
    readData(is);
  }
}

void Loader::load(const std::string &filePath) {
  std::ifstream fs;
  fs.open(filePath);
  if (!fs) {
    throw std::invalid_argument("Couldn't open file " + filePath);
  }
  load(fs);
}

void Loader::parseBlockHeader(std::istream &is) {
  if (std::getline(is, line)) {
    std::istringstream ss(line);
    ss  >> std::hex >> offset
        >> std::hex >> cnt;
    if (!ss) {
      throw std::invalid_argument("Malformed word: " + line);
    }
    std::cout << "0x" << std::setw(4) << std::setfill('0') << std::hex << offset << ' '
              << "0x" << std::setw(4) << std::setfill('0') << std::hex << cnt
              << '\n';
  }
}

void Loader::readData(std::istream &is) {
  for (; cnt > 0; --cnt, offset += 2) {
    if (std::getline(is, line)) {
      size_t pos = 0;
      int n = std::stoi(line, &pos, 16);
      std::cout << std::hex << n << '\n';
      while (pos < line.size() && std::isspace(line[pos])) {
        ++pos;
      }
      if (pos < line.size()) {
        throw std::invalid_argument("Malformed block header: " + line);
      }
    } else {
      throw std::invalid_argument("Too short list of words in the block. Missed: " + std::to_string(cnt));
    }
  }
}
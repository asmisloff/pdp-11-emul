#include <istream>
#include <fstream>
#include <iostream>
#include <ios>
#include <iomanip>
#include <string>
#include <sstream>
#include <exception>
#include <cctype>

#include "./Memory.h"

#ifndef LOADER_H
#define LOADER_H

class Loader {
 public:
  Loader(Memory *mem) : mem{mem}
    {}
  
  void load(std::istream &is) {
    while (is) {
      parseBlockHeader(is);
      readData(is);
    }
  }

  void load(const std::string &filePath) {
    std::ifstream fs;
    fs.open(filePath);
    if (!fs) {
      throw std::invalid_argument("Couldn't open file " + filePath);
    }
    load(fs);
  }

 private:
  Memory *mem;
  unsigned int offset;
  unsigned int cnt;
  std::string line;

  void parseBlockHeader(std::istream &is) {
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

  void readData(std::istream &is) {
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
};

#endif
#ifndef MACHINE_H
#define MACHINE_H

#include <istream>
#include <memory>

#include "./Loader.h"
#include "./Memory.h"
#include "./Logger.h"
#include "./Command.h"

struct PSW {
  bool zeroBit = false;
  bool negBit = false;
  bool carryBit = false;
};

class Machine {
 public:
  Machine();
  PdpWord& pc();
  void run(std::istream& is);
  Logger& logger() { return logger_; }
  Memory& mem() { return mem_; }
  PdpWord& reg(int index) { return regs[index]; }
  PSW psw;
  static const std::vector<const Command*> commands;
  
  private:
  Memory mem_;
  Loader loader_;
  Logger logger_;
  PdpWord regs[8];
};

#endif
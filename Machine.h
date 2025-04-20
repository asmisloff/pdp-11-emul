#ifndef MACHINE_H
#define MACHINE_H

#include <istream>
#include <memory>

#include "./Loader.h"
#include "./Memory.h"
#include "./Logger.h"
#include "./Command.h"

class Machine {
 public:
  Machine();
  PdpWord& pc();
  void run(std::istream& is);
  Logger& logger() { return logger_; }
  Memory& mem() { return mem_; }
  PdpWord& reg(int index) { return regs[index]; }
  static const std::vector<const Command*> commands;

 private:
  Memory mem_;
  Loader loader_;
  Logger logger_;
  PdpWord regs[8];
  static const AddCommand ADD;
  static const MovCommand MOV;
  static const SobCommand SOB;
  static const HaltCommand HALT;
  static const ClrCommand CLR;
};

#endif
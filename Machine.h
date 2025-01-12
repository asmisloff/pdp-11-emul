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
  PdpWord pc();
  void pc(PdpWord w);
  void run(std::istream& is);
  static const std::vector<const Command*> commands;
  void setLoggingLevel(LoggingLevel level);

 private:
  Memory mem;
  Loader loader;
  Logger logger;
  PdpWord regs[8];
  static const AddCommand ADD;
  static const MovCommand MOV;
  static const HaltCommand HALT;
};

#endif
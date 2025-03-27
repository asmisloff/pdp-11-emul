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
  void trace_commands(std::istream& is);
  void setLoggingLevel(LoggingLevel level);
  const Logger& getLogger() const { return logger; }
  Memory& getMemory() { return mem; }
  PdpWord& reg(int index) { return regs[index]; }
  static const std::vector<const Command*> commands;

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
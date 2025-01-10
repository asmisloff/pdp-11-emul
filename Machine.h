#include <istream>

#include "./Loader.h"
#include "./Memory.h"
#include "./Logger.h"

#ifndef MACHINE_H
#define MACHINE_H

class Machine {
 public:
  Machine();
  PdpWord pc();
  void pc(PdpWord w);
  void run(std::istream& is);
  const Memory& memory();

 private:
  Memory mem;
  Loader loader;
  Logger logger;
  PdpWord regs[8];
};

#endif
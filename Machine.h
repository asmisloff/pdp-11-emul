#include "./Memory.h"
#include "./Loader.h"

#ifndef MACHINE_H
#define MACHINE_H

class Machine {
 private:
  Memory mem;
  Loader loader;
  PdpWord regs[8];
};

#endif
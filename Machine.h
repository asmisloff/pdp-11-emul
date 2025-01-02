#include "./Memory.h"

#ifndef MACHINE_H
#define MACHINE_H

class Machine {
 private:
  Memory mem;
  PdpWord regs[8];
};

#endif
#include <cstdlib>

#include "./Machine.h"
#include "./Loader.h"
#include "./PdpTypes.h"

Machine::Machine() 
  : loader{Loader(&mem)}
  , regs{0, 0, 0, 0, 0, 0, 0, 0} 
{}

PdpWord Machine::pc() { 
  return regs[7];
}

void Machine::pc(PdpWord w) {
  regs[7] = w;
}

const Memory& Machine::memory() {
  return mem;
}

void Machine::run(std::istream& is) {
  loader.load(is);
  pc(01000);
  PdpWord w(0);
  do {
    PdpWord w = mem.getWord(pc().intValue());
    logger.trace("%06o %06o: \n", pc().intValue(), w.intValue());
  } while (w.intValue() != 0);
  logger.trace("halt");
  exit(0);
}
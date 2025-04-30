#ifndef MACHINE_H
#define MACHINE_H

#include <istream>
#include <memory>
#include <array>

#include "Loader.h"
#include "Memory.h"
#include "Logger.h"
#include "commands/Command.h"
#include "devices/Monitor.h"

struct PSW {
  bool zeroBit = false;
  bool negBit = false;
  bool carryBit = false;
};

typedef std::unique_ptr<Device> DevicePtr;

class Machine {
public:
  Machine();
  PdpWord& pc();
  void run(std::istream& is);
  PdpByte getByte(PdpAddr addr);
  PdpWord getWord(PdpAddr addr);
  void setByte(PdpAddr addr, PdpByte value);
  void setWord(PdpAddr addr, PdpWord value);
  Logger& logger() { return logger_; }
  PdpWord& reg(int index) { return regs[index]; }
  PSW psw;
  static const std::vector<const Command*> commands;
  
  private:
  Memory mem_;
  Loader loader_;
  Logger logger_;
  PdpWord regs[8];
  const DevicePtr *findOwningDevice(PdpWord addr);
  std::vector<DevicePtr> devices_;
};

#endif
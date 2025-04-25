#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "../PdpTypes.h"

class Machine;

class Command {
 public:
  virtual const std::string& name() const = 0;
  virtual bool match(int opcode) const = 0;
  virtual void exec(int opcode, Machine& m) const = 0;
};

#endif
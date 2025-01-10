#ifndef COMMAND_H
#define COMMAND_H

#include "./PdpTypes.h"
#include "./Machine.h"

class Command {
 public:
  virtual bool match(PdpWord opcode) const;
  virtual void exec(PdpWord opcode, const Machine& m) const;
};

class MovCommand : public Command {
 public:
  bool match(PdpWord opcode) const override;
  void exec(PdpWord opcode, const Machine& m) const override;
};

#endif
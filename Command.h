#ifndef COMMAND_H
#define COMMAND_H

#include "./PdpTypes.h"
#include <string>

class Machine;

static const std::string MOV = "MOV";
static const std::string ADD = "ADD";
static const std::string HALT = "HALT";

class Command {
 public:
  virtual const std::string& name() const = 0;
  virtual bool match(int opcode) const = 0;
  virtual void exec(int opcode, const Machine& m) const = 0;
};

class MovCommand : public Command {
 public:
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, const Machine& m) const override;
};

class AddCommand : public Command {
 public:
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, const Machine& m) const override;
};

class HaltCommand : public Command {
 public:
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, const Machine& m) const override;
};

#endif
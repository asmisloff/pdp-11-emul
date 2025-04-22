#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "./PdpTypes.h"

class Machine;
class Operand;

class Command {
 public:
  virtual const std::string& name() const = 0;
  virtual bool match(int opcode) const = 0;
  virtual void exec(int opcode, Machine& m) const = 0;
};

class MovCommand : public Command {
 public:
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, Machine& m) const override;
 protected:
  std::pair<Operand, Operand> getOperands(int opcode, Machine& m) const;
};

class MovbCommand : public MovCommand {
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, Machine& m) const override;
};

class AddCommand : public Command {
 public:
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, Machine& m) const override;
};

class SobCommand : public Command {
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, Machine& m) const override;
};

class HaltCommand : public Command {
 public:
  const std::string& name() const override;
  bool match(int opcode) const override;
  void exec(int opcode, Machine& m) const override;
};

class ClrCommand : public Command {
  public:
    const std::string& name() const override;
    bool match(int opcode) const override;
    void exec(int opcode, Machine& m) const override;
};

#endif
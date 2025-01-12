#include "./Command.h"

#include <ios>
#include <iostream>

const std::string& MovCommand::name() const { return MOV; }

bool MovCommand::match(int opcode) const {
  return (0170000 & opcode) == 010000;
}

void MovCommand::exec(int opcode, const Machine& m) const {
  (void)m;
  std::cout << name() << ", opcode: " << std::oct << opcode << '\n';
}

const std::string& AddCommand::name() const { return ADD; }

bool AddCommand::match(int opcode) const {
  return (0170000 & opcode) == 060000;
}

void AddCommand::exec(int opcode, const Machine& m) const {
  (void)m;
  std::cout << name() << ", opcode: " << std::oct << opcode << '\n';
}

const std::string& HaltCommand::name() const { return HALT; }

bool HaltCommand::match(int opcode) const { return (0177777 & opcode) == 0; }

void HaltCommand::exec(int opcode, const Machine& m) const {
  (void)m;
  std::cout << name() << ", opcode: " << std::oct << opcode << '\n';
}
#include <exception>

#include "./Command.h"

bool MovCommand::match(PdpWord opcode) const {
    return (0170000 & opcode.intValue()) == 0010000;
}

void MovCommand::exec(PdpWord opcode, const Machine& m) const {
    throw std::runtime_error("Command::exec is pure virtual");
}
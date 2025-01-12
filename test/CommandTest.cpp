#include <cassert>
#include <cstring>
#include <iostream>

#include "../Command.h"

void testMov() {
    std::cout << "MOV: ";
    MovCommand mov;
    const Command *cmd = &mov;
    assert(cmd->match(012701));
    std::cout << "PASSED\n";
}

void testAdd() {
    std::cout << "ADD: ";
    AddCommand add;
    const Command *cmd = &add;
    assert(cmd->match(060001));
    std::cout << "PASSED\n";
}

void testHalt() {
    std::cout << "HALT: ";
    HaltCommand halt;
    const Command *cmd = &halt;
    assert(cmd->match(0));
    std::cout << "PASSED\n";
}

int main() {
    testMov();
    testAdd();
    testHalt();
    return 0;
}
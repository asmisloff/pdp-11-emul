#include <cassert>

#include "../Command.h"

void testMov() {
    MovCommand mov;
    const Command *cmd = &mov;
    assert(cmd->match(012700));
}

int main() {
    testMov();

    return 0;
}
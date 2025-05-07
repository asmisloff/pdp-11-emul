#include "Command.h"
#include "../Machine.h"

// TODO: перенести сюда определения методов exec для всех команд.

void Command::logDebug(Machine& m) const {
    m.logger().debug() << '\n' << (m.pc() - 2) << ": " << name() << ' ';
}
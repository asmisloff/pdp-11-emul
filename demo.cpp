#include <fstream>
#include "Machine.h"

int main() {
    Machine m;
    m.run(std::cin);
    auto& info = m.logger().info();
    info << "\nDone";
    info << "\nState:";
    for (int i = 0; i < 8; ++i) {
        info << 'R' << i << ":" << m.reg(i) << ' ';
    }
    info << "\nZ:" << m.psw.zeroBit << " N:" << m.psw.negBit << " C:" << m.psw.carryBit << '\n';
    return 0;
}
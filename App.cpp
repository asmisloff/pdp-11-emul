#include <fstream>
#include "Machine.h"

int main(int argc, const char **argv) {
    Machine m;
    std::ifstream fs(argv[1]);
    m.run(fs);
    return 0;
}
#include "../devices/Monitor.h"

constexpr PdpAddr STATE_ADDR = 0177564;

void test() {
    Memory mem;
    Logger logger;
    Monitor m(&mem, &logger);
    std::string hello = "Hello world!";
    for (unsigned char c : hello) {
        while (char(mem.getByte(STATE_ADDR)) >= 0) {};
        m.enqueue(c);
    }
}


int main() {
    test();
    return 0;
}
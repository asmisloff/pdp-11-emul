#include <cassert>

#include "../PdpRef.h"
#include "../Machine.h"

Machine m;

void testGetWordFromRam() {
    std::cout << "testGetWordFromRam: ";
    PdpAddr addr = 0123456;
    PdpWord w = 013;
    m.setWord(addr, w);
    PdpRef ref(&m, PdpRef::RAM, addr);
    assert(ref.getWord() == w);
    std::cout << "PASSED\n";
}

void testGetWordFromReg() {
    std::cout << "testGetWordFromReg: ";
    PdpAddr addr = 3;
    PdpWord w = 013;
    m.reg(addr) = w;
    PdpRef ref(&m, PdpRef::REG, addr);
    assert(ref.getWord() == w);
    std::cout << "PASSED\n";
}

void testGetByteFromRam() {
    std::cout << "testGetByteFromRam: ";
    PdpAddr addr = 0123456;
    PdpByte b = 013;
    m.setByte(addr, b);
    PdpRef ref(&m, PdpRef::RAM, addr);
    assert(ref.getByte() == b);
    std::cout << "PASSED\n";
}

void testGetByteFromReg() {
    std::cout << "testGetByteFromReg: ";
    PdpAddr addr = 3;
    PdpByte b = 013;
    m.reg(addr) = b;
    PdpRef ref(&m, PdpRef::REG, addr);
    assert(ref.getByte() == b);
    std::cout << "PASSED\n";
}

void testSetWordToRam() {
    std::cout << "testSetWordToRam: ";
    PdpAddr addr = 0123456;
    PdpWord w = 013;
    PdpRef ref(&m, PdpRef::RAM, addr);
    ref.setWord(w);
    assert(m.getWord(addr) == w);
    std::cout << "PASSED\n";
}

void testSetWordToReg() {
    std::cout << "testSetWordToReg: ";
    PdpAddr addr = 3;
    PdpWord w = 013;
    PdpRef ref(&m, PdpRef::REG, addr);
    ref.setWord(w);
    assert(m.reg(addr) == w);
    std::cout << "PASSED\n";
}

int main() {
    testGetWordFromRam();
    testGetWordFromReg();
    testGetByteFromRam();
    testGetByteFromReg();
    testSetWordToRam();
    testSetWordToReg();
    return 0;
}
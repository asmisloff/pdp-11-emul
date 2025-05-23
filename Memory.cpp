#include "Memory.h"
#include <cstdio>
#include <iomanip>
#include <ios>
#include <algorithm>

const PdpAddr Memory::lastAddress = 0xFFFF;
const unsigned int Memory::size = Memory::lastAddress + 1;

Memory::Memory()
    : mem{ std::vector<PdpByte>(size) }
{}

void checkWordAddr(PdpAddr addr) {
    if (addr % 2 != 0) {
        throw std::out_of_range("Illegal address: " + std::to_string(addr) + ". Must be even.");
    }
    if (addr == 0) {
        throw std::out_of_range("Illegal address: " + std::to_string(addr));
    }
}

PdpWord Memory::getWord(PdpAddr addr) const {
    checkWordAddr(addr);
    PdpByte low = mem.at(addr);
    PdpByte high = mem.at(addr + 1);
    return PdpWord(low, high);
}

void Memory::setWord(PdpAddr addr, PdpWord word) {
    checkWordAddr(addr);
    mem.at(addr) = word.low();
    mem.at(addr + 1) = word.high();
}

PdpByte Memory::getByte(PdpAddr addr) const {
    if (addr == 0) throw std::out_of_range("Illegal address: " + std::to_string(addr));
    return mem.at(addr);
}

void Memory::setByte(PdpAddr addr, PdpByte byte) {
    if (addr == 0) throw std::out_of_range("Illegal address: " + std::to_string(addr));
    mem.at(addr) = byte;
}

void Memory::fill(PdpByte val, PdpAddr begin, PdpAddr end) {
    std::fill(mem.begin() + begin, mem.begin() + end, val);
}

void Memory::dump(PdpAddr begin, PdpAddr end, std::ostream& out) {
    for (; begin < end; begin += 2) {
        int val = getWord(begin).toUnsigned();
        out << std::oct << std::setw(6) << std::setfill('0') << begin << ": "
            << std::oct << std::setw(6) << std::setfill('0') << val << ' '
            << std::hex << std::setw(4) << std::setfill('0') << val << '\n';
    }
}
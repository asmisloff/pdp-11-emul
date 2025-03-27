#include <cstdint>

#ifndef PDP_TYPES_H
#define PDP_TYPES_H

constexpr int PDP_BYTE_SIZE = 8;

typedef uint8_t PdpByte;
typedef uint16_t PdpAddr;

class PdpWord {
 public:
  PdpWord(uint16_t w) { word = swapBytes(w); }

  PdpWord(PdpByte low, PdpByte high) {
    word = low;
    word <<= PDP_BYTE_SIZE;
    word |= high;
  }

  inline bool operator==(const PdpWord &other) const { return word == other.word; }
  inline bool operator!=(const PdpWord &other) const { return word != other.word; }
  inline PdpByte low() const { return word >> PDP_BYTE_SIZE; }
  inline PdpByte high() const { return (PdpByte)word; }
  inline uint16_t intValue() const { return swapBytes(word); }
  inline PdpWord operator+(int amount) { return PdpWord(intValue() + amount); }
  inline void operator+=(int amount) { word = swapBytes(swapBytes(word) + amount); }
  inline PdpWord operator++(int) {
    PdpWord copy = *this;
    *this += 2; 
    return copy;
  }
  inline operator PdpAddr() const { return intValue(); }

 private:
  uint16_t word;

  inline uint16_t swapBytes(uint16_t w) const {
    return (w >> PDP_BYTE_SIZE) | (w << PDP_BYTE_SIZE);
  }
};

#endif
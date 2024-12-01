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

  bool operator==(const PdpWord &other) const { return word == other.word; }

  bool operator!=(const PdpWord &other) const { return word != other.word; }

  PdpByte low() const { return word >> PDP_BYTE_SIZE; }

  PdpByte high() const { return (PdpByte)word; }

  uint16_t toNativeWord() const { return swapBytes(word); }

 private:
  uint16_t word;

  uint16_t swapBytes(uint16_t w) const {
    return (w >> PDP_BYTE_SIZE) | (w << PDP_BYTE_SIZE);
  }
};

#endif
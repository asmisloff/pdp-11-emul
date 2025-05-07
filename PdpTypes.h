#ifndef PDP_TYPES_H
#define PDP_TYPES_H

#include <cstdint>
#include <iostream>
#include <iomanip>

constexpr int PDP_BYTE_SIZE = 8;

typedef uint8_t PdpByte;
typedef uint16_t PdpAddr;

class PdpWord {
 public:
  PdpWord(uint16_t w) : lo_{uint8_t(w)}, hi_{uint8_t(w >> 8)}
  {}

  PdpWord(PdpByte low, PdpByte high) : lo_(low), hi_(high)
  {}

  static PdpWord fromByte(int8_t lo) {
    PdpByte hi = lo < 0 ? 0xff : 0;
    return PdpWord(lo, hi);
  }

  PdpByte low() const { return lo_; }
  PdpByte high() const { return hi_; }
  uint16_t toUnsigned() const { return (uint16_t(hi_) << 8) | uint16_t(lo_); }
  int16_t toSigned() const { return int16_t(toUnsigned()); }
  PdpWord operator+(const PdpWord &other) const { return PdpWord(toUnsigned() + other.toUnsigned()); }
  PdpWord operator-(const PdpWord &other) const { return PdpWord(toUnsigned() - other.toUnsigned()); }
  PdpWord operator-(int amount) const { return PdpWord(toUnsigned() - amount); }
  void operator+=(int amount) { assign(toUnsigned() + amount); }
  void operator-=(int amount) { assign(toUnsigned() - amount); }
  PdpWord operator++(int);
  PdpWord& operator--();
  operator PdpAddr() const { return toUnsigned(); }

 private:
  uint8_t lo_;
  uint8_t hi_;
  void assign(uint16_t word) { lo_ = uint8_t(word), hi_ = uint8_t(word >> 8); }
};

inline std::ostream& operator<<(std::ostream &out, const PdpWord &word) {
  return out << std::oct << std::setfill('0') << std::setw(6)
             << word.toUnsigned() << std::dec;
}

inline PdpWord PdpWord::operator++(int)  {
  PdpWord copy = *this;
  *this += 2; 
  return copy;
}

inline PdpWord& PdpWord::operator--() {
  *this -= 2;
  return *this;
}

#endif
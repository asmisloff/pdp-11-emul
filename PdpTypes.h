#include <cstdint>
#include <iostream>
#include <iomanip>

#ifndef PDP_TYPES_H
#define PDP_TYPES_H

constexpr int PDP_BYTE_SIZE = 8;

typedef uint8_t PdpByte;
typedef uint16_t PdpAddr;

class PdpWord {
 public:
  PdpWord(uint16_t w) : lo_{uint8_t(w)}, hi_{uint8_t(w >> 8)}
  {}

  PdpWord(PdpByte low, PdpByte high) : lo_(low), hi_(high)
  {}

  bool operator==(const PdpWord &other) const { return lo_ == other.lo_ && hi_ == other.hi_; }
  bool operator!=(const PdpWord &other) const { return !(*this == other); }
  PdpByte low() const { return lo_; }
  PdpByte high() const { return hi_; }
  uint16_t intValue() const { return (uint16_t(hi_) << 8) | uint16_t(lo_); }
  PdpWord operator+(const PdpWord &other) const { return PdpWord(intValue() + other.intValue()); }
  PdpWord operator-(const PdpWord &other) const { return PdpWord(intValue() - other.intValue()); }
  void operator+=(int amount) { assign(intValue() + amount); }
  void operator-=(int amount) { assign(intValue() - amount); }
  PdpWord operator++(int);
  PdpWord& operator--();
  operator PdpAddr() const { return intValue(); }

 private:
  uint8_t lo_;
  uint8_t hi_;
  void assign(uint16_t word) { lo_ = uint8_t(word), hi_ = uint8_t(word >> 8); }
};

inline std::ostream& operator<<(std::ostream &out, const PdpWord &word) {
  return out << std::oct << std::setfill('0') << std::setw(6)
             << word.intValue();
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
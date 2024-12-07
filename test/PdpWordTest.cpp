#include <cassert>

#include "../PdpTypes.h"

void testNativeWordToPdpWordConstructor() {
  PdpWord word(0x00FF);
  assert(word.low() == 0xFF);
  assert(word.high() == 0x00);
  assert(word.intValue() == 0x00FF);
}

void testTwoPdpBytesToPdpWordConstructor() {
  PdpWord word(0xAB, 0xCD);
  assert(word.intValue() == 0xCDAB);
  assert(word.low() == 0xAB);
  assert(word.high() == 0xCD);
}

int main() {
  testNativeWordToPdpWordConstructor();
  testTwoPdpBytesToPdpWordConstructor();
  return 0;
}
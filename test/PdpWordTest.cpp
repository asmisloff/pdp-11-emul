#include <cassert>

#include "../PdpTypes.h"
#include <iostream>

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

void testStreamOperator() {
  std::cout << "opertor<<: ";
  PdpWord word(01234);
  std::stringstream ss;
  ss << word;
  assert(ss.str() == "001234");
  std::cout << "PASSED\n";
}

int main() {
  testNativeWordToPdpWordConstructor();
  testTwoPdpBytesToPdpWordConstructor();
  testStreamOperator();
  return 0;
}
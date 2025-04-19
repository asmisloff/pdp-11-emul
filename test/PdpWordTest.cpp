#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "../PdpTypes.h"

void testNativeWordToPdpWordConstructor() {
  std::cout << "nativeWordToPdpWordConstructor: ";
  PdpWord word(0x00FF);
  assert(word.low() == 0xFF);
  assert(word.high() == 0x00);
  assert(word.intValue() == 0x00FF);
  std::cout << "PASSED\n";
}

void testTwoPdpBytesToPdpWordConstructor() {
  std::cout << "twoPdpBytesToPdpWordConstructor: ";
  PdpWord word(0xAB, 0xCD);
  assert(word.intValue() == 0xCDAB);
  assert(word.low() == 0xAB);
  assert(word.high() == 0xCD);
  std::cout << "PASSED\n";
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
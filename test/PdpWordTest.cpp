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
  assert(word.toUnsigned() == 0x00FF);
  std::cout << "PASSED\n";
}

void testFromByte() {
  std::cout << "fromByte: ";
  PdpWord word = PdpWord::fromByte(13);
  assert(word.low() == 13);
  assert(word.high() == 0);
  word = PdpWord::fromByte(-13);
  assert(word.low() == uint8_t(-13));
  assert(word.high() == 0xFF);
  word = PdpWord::fromByte(255);
  assert(int8_t(word.low()) == -1);
  assert(word.high() == 0xFF);
  std::cout << "PASSED\n";
}

void testTwoPdpBytesToPdpWordConstructor() {
  std::cout << "twoPdpBytesToPdpWordConstructor: ";
  PdpWord word(0xAB, 0xCD);
  assert(word.toUnsigned() == 0xCDAB);
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
  testFromByte();
  testTwoPdpBytesToPdpWordConstructor();
  testStreamOperator();
  return 0;
}
#include <memory>
#include <iostream>
#include <sstream>
#include "../Logger.h"

void test() {
  Logger logger;
  int a = 2, b = 3;
  logger.level = Logger::Level::DEBUG;
  logger.debug().setStream(std::make_unique<std::stringstream>());
  logger.debug() << a << " + " << b << " = " << (a + b) << '\n';
  std::cout << "DEBUG: " << static_cast<std::stringstream*>(logger.debug().stream())->str();
  logger.debug().setStream(nullptr);
  logger.error() << a << " + " << b << " = " << (a + b) << '\n';
}

int main() {
  test();
  return 0;
}
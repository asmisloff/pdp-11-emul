#include <iostream>
#include <fstream>

#include "../Loader.h"

int main() {
  Loader loader(nullptr);
  loader.load("./data/Loader_given_1.txt");
  return 0;
}
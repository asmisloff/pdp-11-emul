#include <cassert>
#include <complex.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../Loader.h"
#include "../Memory.h"

int main() {
  Memory mem;
  Loader loader(&mem);
  std::string expected;
  std::string actual;
  std::stringstream ssActual;
  for (int i = 1; i <= 5; ++i) {
    std::cout << "test #" << i << ": ";
    std::string num = std::to_string(i);
    loader.load("./data/Loader_given_" + num + ".txt");
    std::ifstream es("./data/Loader_expected_" + num + ".txt");
    mem.dump(0x40, 0x40 + 20, ssActual);
    ssActual << '\n';
    mem.dump(0x200, 0x200 + 0x26, ssActual);
    while (std::getline(ssActual, actual) && std::getline(es, expected)) {
      assert(expected.compare(actual) == 0);
    }
    assert(ssActual.eof() && es.eof());
    mem.fill(0);
    std::cout << "PASSED" << '\n';
    ssActual.clear();
  }
  return 0;
}
#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include <type_traits>

#include "../Machine.h"
#include "testUtil.h"

std::string read(std::string path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void setupLoggerForDebug(Machine& m) {
    m.logger().level = Logger::Level::DEBUG;
    m.logger().debug().setStream(std::make_unique<std::stringstream>());
}

std::string fromLoggerDebugStream(Machine& m) {
    auto ss = dynamic_cast<std::stringstream*>(m.logger().debug().stream());
    if (ss == nullptr) {
        throw std::runtime_error("Failed to cast logger's DEBUG stream to std::stringstream");
    }
    return ss->str();
}

std::string fromLoggerInfoStream(Machine& m) {
    auto ss = static_cast<std::stringstream*>(m.logger().info().stream());
    if (ss == nullptr) {
        throw std::runtime_error("Failed to cast logger's INFO stream to std::stringstream");
    }
    return ss->str();
}

void testEmptyProgram() {
    std::cout << "Empty program: ";
    Machine m;
    setupLoggerForDebug(m);
    std::stringstream ss;
    ss << "200 2\n"
        << "0\n"
        << "0\n";
    m.run(ss);
    std::string expected = "\n001000: HALT"
        "\nR0:0 R1:0 R2:0 R3:0 R4:0 R5:0 R6:0 R7:1002"
        "\nZ:0 N:0 C:0\n";
    std::string actual = fromLoggerDebugStream(m);
    // std::cout << actual;
    assert(eq(expected, actual));
    std::cout << "PASSED\n";
}

void test_e2e_cases() {
    std::vector<std::string> testNames = {
        "01_sum",
        "01_sum_mode1",
        "01_sum_mode1_big",
        "01_sum_neg",
        "02_sob",
        "02_sob_byte",
        "02_sob_mode3",
        "03_arr0",
        "03_arr0_byte",
        "10_jsr_sum",
        "10_jsr_sum_r5"
    };
    for (auto testName : testNames) {
        std::cout << testName << ": ";
        std::ifstream fs("./e2e/" + testName + "/" + testName + ".pdp.o");
        Machine m;
        setupLoggerForDebug(m);
        m.run(fs);
        auto expected = read("./data/" + testName + "_expected.txt");
        auto actual = fromLoggerDebugStream(m);
        // std::cout << actual;
        assert(eq(expected, actual));
        std::cout << "PASSED\n";
    }
}

void test_04_mode4() {
    std::cout << "04_mode4: ";
    std::ifstream ifs("./e2e/04_mode4/04_mode4.pdp.o");
    Machine m;
    setupLoggerForDebug(m);
    try {
        m.run(ifs);
    }
    catch (std::out_of_range& e) {
        assert(strcmp(e.what(), "Illegal address: 0") == 0);
        for (PdpAddr addr = 02; addr < 01000; addr += 02) {
            assert(m.getWord(addr).toUnsigned() == 0014747);
        }
        std::cout << "PASSED\n";
    }
}

void doTestMonitorCase(
    const std::string& pathPrefix,
    const std::string& testName,
    const std::string& expected
) {
    std::cout << testName << ": ";
    auto ssPtr = std::make_unique<std::stringstream>();
    *ssPtr << pathPrefix << '/' << testName << ".pdp.o";
    std::ifstream fs(ssPtr->str());
    Machine m;
    ssPtr->str("");
    m.logger().info().setStream(std::move(ssPtr));
    m.run(fs);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Дождаться вывода последнего символа
    auto actual = fromLoggerInfoStream(m);
    // std::cout << actual << " -- ";
    assert(eq(expected, actual));
    std::cout << "PASSED\n";
}

void testMonitorCases() {
    std::map<std::string, std::string> testCases{
        {"07_putchar", "*"},
        {"08_hello", "Hello, world!"},
        {"09_mode6_minus", "c"},
        {"09_mode6_plus", "e"},
        {"09_mode67", "*"},
        {"10_jsr_rts", "Hello, world!"}
    };
    for (auto [testName, expected] : testCases) {
        doTestMonitorCase("./e2e/" + testName, testName, expected);
    }
}

void zachet() {
    std::vector<std::tuple<std::string, std::string, std::string>> testCases {
        {"./e2e/zachet/putbin", "putbin", "./e2e/zachet/putbin/out.txt"},
        {"./e2e/zachet/putbin", "putbin1", "./e2e/zachet/putbin/out1.txt"},
        {"./e2e/zachet/putbin_plane", "putbin_plane", "./e2e/zachet/putbin_plane/out.txt"},
        {"./e2e/zachet/putbin_plane", "putbin_plane1", "./e2e/zachet/putbin_plane/out1.txt"},
        {"./e2e/zachet/puthex", "puthex", "./e2e/zachet/puthex/out.txt"},
        {"./e2e/zachet/puthex", "puthex1", "./e2e/zachet/puthex/out1.txt"},
    };
    for (auto [root, testName, expected] : testCases) {
        doTestMonitorCase(root, testName, read(expected));
    }
}

int main() {
    testEmptyProgram();
    test_e2e_cases();
    test_04_mode4();
    testMonitorCases();
    zachet();
    return 0;
}

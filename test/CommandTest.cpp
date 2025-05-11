#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>

#include "../Command.h"
#include "../Machine.h"

void testMov() {
    std::cout << "MOV: ";
    MovCommand mov;
    const Command* cmd = &mov;
    assert(cmd->match(012701));
    std::cout << "PASSED\n";
}

void testAdd() {
    std::cout << "ADD: ";
    AddCommand add;
    const Command* cmd = &add;
    assert(cmd->match(060001));
    std::cout << "PASSED\n";
}

void testHalt() {
    std::cout << "HALT: ";
    HaltCommand halt;
    const Command* cmd = &halt;
    assert(cmd->match(0));
    std::cout << "PASSED\n";
}

void testJsr(Machine* mPtr = nullptr) {
    if (!mPtr) std::cout << "JSR: ";
    std::unique_ptr<Machine> defaultMPtr = !mPtr ? std::make_unique<Machine>() : nullptr;
    Machine& m = mPtr ? *mPtr : *defaultMPtr;
    m.sp() = 01000;
    m.pc() = 01002;
    m.setWord(01002, 014); // Смещение до ячейки с адресом процедуры
    JsrCommand jsr;
    Command& cmd = jsr;
    int opcode = 004767;
    assert(cmd.match(opcode));
    cmd.exec(opcode, m);
    assert(m.sp() == 00776); // Указатель стека сместился на слово назад
    assert(m.getWord(m.sp()) == 01004); // На вершине стека лежит правильный адрес возврата
    assert(m.pc() == 01020); // Указатель команд стоит в начале процедуры
    if (!mPtr) std::cout << "PASSED\n";
}

void testRts() {
    std::cout << "RTS: ";
    Machine m;
    testJsr(&m);
    RtsCommand rts;
    Command& cmd = rts;
    int opcode = 000207;
    cmd.exec(opcode, m);
    assert(m.sp() == 01000); // Указатель стека вернулся в начальное положение
    assert(m.pc() == 01004); // Указатель команд вернулся в начальное положение
    std::cout << "PASSED\n";
}

void testRol() {
    std::cout << "testRol: ";
    Machine m;
    std::unique_ptr<Command> cmd = std::make_unique<RolCommand>();
    int opcode = 0006101;
    m.reg(1) = 0123456;
    cmd->exec(opcode, m);
    assert(m.reg(1) == 047134);
    assert(m.psw.carryBit == true);
    cmd->exec(opcode, m);
    assert(m.reg(1) == 0116271);
    assert(m.psw.carryBit == false);
    std::cout << "PASSED\n";
}

void testAsh() {
    std::cout << "testAsh: ";
    Machine m;
    std::unique_ptr<Command> cmd = std::make_unique<AshCommand>();
    assert(cmd->match(072003));
    struct TestData {
        PdpWord initialValue;
        int shift;
        bool expectedCarryBit;
        PdpWord expectedValue;
    };
    auto testCase = [&m, &cmd](TestData&& td) {
        m.reg(1) = td.initialValue;
        cmd->exec(00720100 | (td.shift & 077), m);
        assert(m.psw.carryBit == td.expectedCarryBit);
        assert(m.psw.negBit == (td.expectedValue.toSigned() < 0));
        assert(m.reg(1) == td.expectedValue);
    };
    testCase({ 
        .initialValue = 0123456, .shift = 2, .expectedCarryBit = false, .expectedValue = 0116270
    });
    testCase({ 
        .initialValue = 0012346, .shift = -2, .expectedCarryBit = true, .expectedValue = 0002471
    });
    testCase({ 
        .initialValue = 0123455, .shift = -2, .expectedCarryBit = false, .expectedValue = 0164713
    });
    testCase({ 
        .initialValue = 0123455, .shift = -3, .expectedCarryBit = true, .expectedValue = 0172345
    });
    std::cout << "PASSED\n";
}

int main() {
    testMov();
    testAdd();
    testHalt();
    testJsr();
    testRts();
    testRol();
    testAsh();
    return 0;
}
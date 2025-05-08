#include <cassert>
#include <cstring>
#include <iostream>

#include "../Command.h"
#include "../Machine.h"

void testMov() {
    std::cout << "MOV: ";
    MovCommand mov;
    const Command *cmd = &mov;
    assert(cmd->match(012701));
    std::cout << "PASSED\n";
}

void testAdd() {
    std::cout << "ADD: ";
    AddCommand add;
    const Command *cmd = &add;
    assert(cmd->match(060001));
    std::cout << "PASSED\n";
}

void testHalt() {
    std::cout << "HALT: ";
    HaltCommand halt;
    const Command *cmd = &halt;
    assert(cmd->match(0));
    std::cout << "PASSED\n";
}

void testJsr(Machine *mPtr = nullptr) {
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

int main() {
    testMov();
    testAdd();
    testHalt();
    testJsr();
    testRts();
    return 0;
}
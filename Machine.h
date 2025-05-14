#ifndef MACHINE_H
#define MACHINE_H

#include <istream>
#include <memory>
#include <array>

#include "Loader.h"
#include "Memory.h"
#include "Logger.h"
#include "Command.h"
#include "devices/Monitor.h"

/** Регистр флагов состояния (processor status word). */
struct PSW {
  bool zeroBit = false;
  bool negBit = false;
  bool carryBit = false;
};

typedef std::unique_ptr<Device> DevicePtr;

/** Модель вычислительной машины PDP-11. */
class Machine {
public:

  Machine();

  /** Адрес текущей исполняемой инстукции (program counter). */
  PdpWord& pc();
  
  /** Адрес вершины стека. */
  PdpWord& sp();
  
  /** Запуск исполнения кода из входного потока. */
  void run(std::istream& is);
  
  /** Чтение байта из памяти. Непосредственно либо через внешнее устройство - в зависимости от адреса. */
  PdpByte getByte(PdpAddr addr);
  
  /** Чтение слова из памяти. Непосредственно либо через внешнее устройство - в зависимости от адреса. */
  PdpWord getWord(PdpAddr addr);
  
  /** Запись байта в память. Непосредственно либо через внешнее устройство - в зависимости от адреса. */
  void setByte(PdpAddr addr, PdpByte value);

  /** Запись слова в память. Непосредственно либо через внешнее устройство - в зависимости от адреса. */
  void setWord(PdpAddr addr, PdpWord value);

  /** Логгер. */
  Logger& logger() { return logger_; }

  /** Взвращает ссылку на регистр. */
  PdpWord& reg(int index) { return regs.at(index); }

  /** Регистр флагов состояния. */
  PSW psw;

  /** Команды машины. */
  static const std::vector<const Command*> commands;

private:
  Memory mem_;
  Loader loader_;
  Logger logger_;
  std::array<PdpWord, 8> regs;
  const DevicePtr* findOwningDevice(PdpWord addr);
  std::vector<DevicePtr> devices_;
};

#endif
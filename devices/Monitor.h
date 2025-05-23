#ifndef MONITOR_H
#define MONITOR_H

#include <thread>
#include "Device.h"
#include "../PdpTypes.h"
#include "../Memory.h"
#include "../Logger.h"

/** Монитор (экран). */
class Monitor : public Device {
public:
    explicit Monitor(Memory *const mem, Logger *const logger);
    Monitor() = delete;
    Monitor(const Monitor&) = delete;
    Monitor(Monitor&&) = delete;
    Monitor& operator=(const Monitor&) = delete;
    virtual ~Monitor() override;
    bool owns(PdpAddr addr) const override;
    void enqueue(const PdpByte byte) override;
private:
    /** Старт потока и запуск в нем цикла проверки изменений в выделенной монитору области памяти. */
    static void run(const Monitor* instance);
    Memory* mem_;
    Logger* logger_;
    std::thread thread_;
    bool shutdown_ = false;
};

#endif // MONITOR_H
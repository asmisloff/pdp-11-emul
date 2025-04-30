#ifndef MONITOR_H
#define MONITOR_H

#include <thread>
#include "Device.h"
#include "../PdpTypes.h"
#include "../Memory.h"
#include "../Logger.h"

class Monitor : public Device {
public:
    explicit Monitor(Memory *const mem, Logger * const logger);
    Monitor() = delete;
    Monitor(const Monitor&) = delete;
    Monitor(Monitor&&) = delete;
    Monitor& operator=(const Monitor&) = delete;
    ~Monitor();
    bool owns(PdpAddr addr) const override;
    void enqueue(const PdpByte byte) override;
private:
    static void run(const Monitor* instance);
    Memory * mem_;
    Logger * logger_;
    std::thread thread_;
};

#endif // MONITOR_H
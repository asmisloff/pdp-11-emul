#ifndef MONITOR_H
#define MONITOR_H

#include <thread>
#include "../PdpTypes.h"

class Monitor {
public:
    Monitor(PdpByte * const state, PdpByte * const data);
    Monitor(const Monitor&) = delete;
    Monitor(Monitor&&) = delete;
    Monitor& operator=(const Monitor&) = delete;
    ~Monitor();
    void enqueue(const PdpByte byte);
private:
    void run();
    PdpByte * const state_;
    PdpByte * const data_;
    bool shutdown_;
    std::thread thread_;
};

#endif // MONITOR_H
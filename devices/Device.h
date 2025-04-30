#ifndef DEVICE_H
#define DEVICE_H

#include "../PdpTypes.h"

class Device {
public:
    virtual bool owns(PdpAddr addr) const = 0;
    virtual void enqueue(const PdpByte byte) = 0;
    virtual ~Device() {};
};

#endif
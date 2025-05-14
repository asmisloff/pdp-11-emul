#ifndef DEVICE_H
#define DEVICE_H

#include "../PdpTypes.h"

/** Базовый интерфейс подключаемого устройства. */
class Device {
public:
    
    /** @returns true, если устройство владеет указанным адресом в памяти. */
    virtual bool owns(PdpAddr addr) const = 0;

    /**
     * Поместить байт в очередь для обработки.
     * Технически это должно означать: записать байт в выделенную для данного устройства
     * ячейку памяти и установить флаг готовности.
     */
    virtual void enqueue(const PdpByte byte) = 0;
    
    virtual ~Device() {};
};

#endif
#include "Monitor.h"

constexpr PdpByte READY = 0x80;
constexpr PdpByte WORKS = 0x00;
constexpr std::chrono::milliseconds LATENCY(50);
constexpr PdpAddr STATE_ADDR = 0177564;
constexpr PdpAddr DATA_ADDR = 0177566;

Monitor::Monitor(Memory * const mem, Logger * const logger)
    : mem_{mem}
    , logger_{logger}
    , thread_(Monitor::run, this) 
{
    mem_->setByte(DATA_ADDR, 0);
    mem_->setByte(STATE_ADDR, READY);
}

Monitor::~Monitor() {
    mem_ = nullptr;
    logger_ = nullptr;
    thread_.join();
}

bool Monitor::owns(PdpAddr addr) const {
    return addr == STATE_ADDR || addr == DATA_ADDR;
}

void Monitor::enqueue(const PdpByte byte) {
    mem_->setByte(STATE_ADDR, WORKS);
    mem_->setByte(DATA_ADDR, byte);
}

void Monitor::run(const Monitor *instance) {
    while (instance->mem_) {
        if (instance->mem_->getByte(STATE_ADDR) == WORKS) {
            auto byte = instance->mem_->getByte(DATA_ADDR);
            instance->logger_->info() << byte << std::flush;
            instance->mem_->setByte(DATA_ADDR, 0);
            instance->mem_->setByte(STATE_ADDR, READY);
        }
        std::this_thread::sleep_for(LATENCY);
    }
}
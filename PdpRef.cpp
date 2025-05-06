#include "PdpRef.h"
#include "Machine.h"

PdpRef::PdpRef(Machine *m, PdpRef::Storage storage, PdpAddr addr) 
    : m_{m}
    , storage_{storage}
    , addr_{addr}
{}

PdpRef::Storage PdpRef::storage() const {
    return storage_;
}

PdpAddr PdpRef::addr() const {
    return addr_;
}

PdpWord PdpRef::getWord() const {
    if (storage_ == REG) {
        return m_->reg(addr_);
    }
    return m_->getWord(addr_);
}

PdpByte PdpRef::getByte() const {
    if (storage_ == REG) {
        return m_->reg(addr_).low();
    }
    return m_->getByte(addr_);
}

void PdpRef::setWord(PdpWord word) {
    if (storage_ == REG) {
        m_->reg(addr_) = word;
    } else {
        m_->setWord(addr_, word);
    }
}

void PdpRef::setByte(PdpByte byte) {
    if (storage_ == REG) {
        m_->reg(addr_) = PdpWord::fromByte(byte);
    } else {
        m_->setByte(addr_, byte);
    }
}

#ifndef PDP_REF_H
#define PDP_REF_H

#include "PdpTypes.h"

class Machine;

class PdpRef {
public:
    enum Storage { REG, MEM };
    PdpRef() = delete;
    PdpRef(Machine* m, Storage storage_, PdpAddr addr);
    Storage storage() const;
    PdpAddr addr() const;
    PdpWord getWord() const;
    PdpByte getByte() const;
    void setWord(PdpWord word);
    void setByte(PdpByte byte);
private:
    Machine *m_;
    Storage storage_;
    PdpAddr addr_;
};

#endif
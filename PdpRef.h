#ifndef PDP_REF_H
#define PDP_REF_H

#include "PdpTypes.h"

class Machine;

/** Ссылка на ресурс (регистр или ячейку памяти). */
class PdpRef {
public:

    /** Тип ресурса: регистровая или основная память. */
    enum Storage { REG, MEM };

    PdpRef(Machine* m, Storage storage_, PdpAddr addr);
    PdpRef() = delete;
    
    /** @return тип ресурса. */
    Storage storage() const;

    /** @return адрес ресурса. */
    PdpAddr addr() const;

    /** Прочитать слово по ссылке. */
    PdpWord getWord() const;

    /** Прочитать байт по ссылке. */
    PdpByte getByte() const;

    /** Записать слово по ссылке. */
    void setWord(PdpWord word);

    /** Записать байт по ссылке. */
    void setByte(PdpByte byte);

private:
    Machine *m_;
    Storage storage_;
    PdpAddr addr_;
};

#endif
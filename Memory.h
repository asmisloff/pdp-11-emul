#include <iostream>
#include <vector>
#include <cstddef>
#include <exception>

#include "./PdpTypes.h"

#ifndef RAM_H
#define RAM_H

/** RAM. */
class Memory {
public:

    Memory();

    /** 
     * Прочитать слово по заданному адресу.
     * @throws std::out_of_range, если адрес нулевой, нечетный или не существует.
     */
    PdpWord getWord(PdpAddr addr) const;

    /** 
     * Записать слово по заданному адресу.
     * @throws std::out_of_range, если адрес нулевой, нечетный или не существует.
     */
    void setWord(PdpAddr addr, PdpWord word);

    /** 
     * Прочитать слово по заданному адресу.
     * @throws std::out_of_range, если адрес нулевой или не существует.
     */
    PdpByte getByte(PdpAddr addr) const;
    
    /** 
     * Записать слово по заданному адресу.
     * @throws std::out_of_range, если адрес нулевой или не существует.
     */
    void setByte(PdpAddr addr, PdpByte byte);

    /**
     * Заполнить диапазон памяти заданным значением.
     * @param val заданное значение.
     * @param begin начальный адрес.
     * @param end конечный адрес (не включая).
     */
    void fill(PdpByte val, PdpAddr begin = 0, PdpAddr end = lastAddress);

    /**
     * Вывести дамп памяти.
     * @param begin начальный адрес.
     * @param end конечный адрес (не включая).
     * @param out поток вывода.
     */
    void dump(PdpAddr begin, PdpAddr end, std::ostream& out = std::cout);

    /** Максимально доступный адрес. */
    static const PdpAddr lastAddress;

    /** Объем памяти в байтах. */
    static const unsigned int size;

private:
    std::vector<PdpByte> mem;
};

#endif
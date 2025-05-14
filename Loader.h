#include <istream>
#include <string>

#include "./Memory.h"

#ifndef LOADER_H
#define LOADER_H

/** Загрузчик программ. */
class Loader {
public:

    Loader(Memory* mem);

    /** Загрузить код программы из входного потока. */
    void load(std::istream& is);

    /** Загрузить код программы из текстового файла. */
    void load(const std::string& filePath);

private:
    Memory* mem;
    PdpAddr addr;
    PdpAddr end;
    std::string line;
    void parseBlockHeader(std::istream& is);
    void readData(std::istream& is);
};

#endif
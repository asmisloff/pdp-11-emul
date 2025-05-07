#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <string>

static char nextChar(std::string::const_iterator& it, const std::string::const_iterator& end) {
    while (it < end && std::isspace(*it)) {
        ++it;
    }
    if (it >= end) {
        return '\0';
    }
    return *it++;
}

/** Сравнить строки без учета начальных и конечных пробельных символов. */
inline bool eq(const std::string& a, const std::string& b) {
    auto ita = a.begin();
    auto itb = b.begin();
    auto enda = a.end();
    auto endb = b.end();
    while (ita < a.end() || itb < b.end()) {
        if (nextChar(ita, enda) != nextChar(itb, endb)) {
            return false;
        }
    }
    return true;
}

#endif
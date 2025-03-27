#include <cstdio>

#include "./Logger.h"

Logger::Logger() : level{INFO}
    {}

LoggingLevel Logger::getLevel() const {
    return level;
}

void Logger::setLevel(LoggingLevel level) {
    this->level = level;
}
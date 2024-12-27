#include <cstdio>

#include "./Logger.h"

Logger::Logger() : level{INFO}
    {}

void Logger::setLevel(LoggingLevel level) {
    this->level = level;
}
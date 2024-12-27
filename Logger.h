#include <cstdio>

#ifndef LOGGER_H
#define LOGGER_H

enum LoggingLevel { ERROR, INFO, TRACE, DEBUG };

class Logger {
 public:
  Logger();

  void setLevel(LoggingLevel level);
  
  LoggingLevel getLevel() const;
  
  template<class... Args>
  inline void log(LoggingLevel level, const char *fmt, Args... args) const;
  
  template<class... Args>
  inline void error(const char *fmt, Args... args) const;
  
  template<class... Args>
  inline void info(const char *fmt, Args... args) const;

  template<class... Args>
  inline void trace(const char *fmt, Args... args) const;

  template<class... Args>
  inline void debug(const char *fmt, Args... args) const;

 private:
  LoggingLevel level;
};

template<class... Args>
void Logger::log(LoggingLevel level, const char *fmt, Args... args) const {
  if (level <= this->level) {
      std::printf(fmt, args...);
  }
}

template<class... Args>
void Logger::error(const char *fmt, Args... args) const {
  log(ERROR, fmt, args...);
}

template<class... Args>
void Logger::info(const char *fmt, Args... args) const {
  log(INFO, fmt, args...);
}

template<class... Args>
void Logger::trace(const char *fmt, Args... args) const {
  log(TRACE, fmt, args...);
}

template<class... Args>
void Logger::debug(const char *fmt, Args... args) const {
  log(DEBUG, fmt, args...);
}

#endif
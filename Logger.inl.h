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
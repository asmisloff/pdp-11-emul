#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <memory>

class Logger {
 public:
  enum Level { ERROR, INFO, TRACE, DEBUG };

  class OStreamWrapper {
    public:
      friend class Logger;
      std::ostream *stream() const;
      void setStream(std::unique_ptr<std::ostream>&& stream);
    private:
      explicit OStreamWrapper(
        Logger* parent,
        Level level,
        std::unique_ptr<std::ostream> customStream = nullptr
      ) 
        : parent{parent}
        , level{level}
        , cs{std::move(customStream)}
      {}
      Logger* parent;
      Level level;
      std::unique_ptr<std::ostream> cs;
  };
  
  Level level = Level::ERROR;
  OStreamWrapper error = OStreamWrapper(this, Level::ERROR);
  OStreamWrapper info = OStreamWrapper(this, Level::INFO);
  OStreamWrapper trace = OStreamWrapper(this, Level::TRACE);
  OStreamWrapper debug = OStreamWrapper(this, Level::DEBUG);
};


inline std::ostream *Logger::OStreamWrapper::stream() const { 
  if (parent->level < this->level) return nullptr;
  if (cs.get() == nullptr) return &std::cout;
  return cs.get();
}

inline void Logger::OStreamWrapper::setStream(std::unique_ptr<std::ostream>&& stream) {
  this->cs = std::move(stream);
}

template<class T>
inline Logger::OStreamWrapper& operator<<(Logger::OStreamWrapper& w, T arg) {
  std::ostream* s = w.stream();
  if (s != nullptr) {
    *s << arg;
  }
  return w;
}

#endif
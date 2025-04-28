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
        void setStream(std::unique_ptr<std::ostream> stream);
      private:
        explicit OStreamWrapper(Logger* parent, Level level);
        Logger* parent;
        Level level;
        std::unique_ptr<std::ostream> customStreamPtr;
        void operator=(const OStreamWrapper&) = delete;
    };

    explicit Logger();
    Level level = Level::ERROR;
    OStreamWrapper& error() { return error_; }
    OStreamWrapper& trace() { return trace_; }
    OStreamWrapper& info()  { return info_;  }
    OStreamWrapper& debug() { return debug_; }
    template<class F> void debug(F f) { if (level >= this->level) f(debug_); }

  private:
    OStreamWrapper error_;
    OStreamWrapper info_ ;
    OStreamWrapper trace_;
    OStreamWrapper debug_;
};

inline Logger::Logger()
  : error_{this, Level::ERROR}
  , info_{this, Level::INFO}
  , trace_{this, Level::TRACE}
  , debug_{this, Level::DEBUG}
{}

inline Logger::OStreamWrapper::OStreamWrapper(Logger* parent, Level level)
  : parent{parent}
  , level{level}
{}

inline std::ostream *Logger::OStreamWrapper::stream() const { 
  if (parent->level < this->level) return nullptr;
  if (customStreamPtr.get() == nullptr) return &std::cout;
  return customStreamPtr.get();
}

inline void Logger::OStreamWrapper::setStream(std::unique_ptr<std::ostream> stream) {
  this->customStreamPtr = std::move(stream);
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
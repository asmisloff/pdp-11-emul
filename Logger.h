#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <memory>

/** Логгер. */
class Logger {
  public:

    /** Уровень логирования. */
    enum Level { ERROR, INFO, TRACE, DEBUG };

    /** 
     * Декоратор стандартного потока вывода.
     * Управляет выводом в фактический поток в зависимости установленного уровня логирования.
     * Позволяет заменить фактический поток вывода.
     */
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

    /** Уровень логирования. */
    Level level = Level::INFO;
    /** Поток уровня ERROR. */
    OStreamWrapper& error() { return error_; }
    /** Поток уровня TRACE. */
    OStreamWrapper& trace() { return trace_; }
    /** Поток уровня INFO. */
    OStreamWrapper& info()  { return info_;  }
    /** Поток уровня DEBUG. */
    OStreamWrapper& debug() { return debug_; }

    /** 
     * Отложенный вывод в поток уровня DEBUG.
     * @param f функция, выполняющая вывод в поток. Будет вызвана только, если уровень логгера установлен в DEBUG.
     */
    template<class F> void lazyDebug(F f) { if (level >= this->level) f(debug_); }

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

/** Специализация для стандартных манипуляторов. */
inline Logger::OStreamWrapper& operator<<(Logger::OStreamWrapper& w, std::ostream& (*manipulator)(std::ostream&)) {
  std::ostream* s = w.stream();
  if (s != nullptr) {
    *s << manipulator;
  }
  return w;
}

#endif
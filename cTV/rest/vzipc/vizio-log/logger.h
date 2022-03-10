/*
   logger.h
   © 2020 Vizio Services, All Rights Reserved

   Logger.h provides the api to log messages of various severities. logger.h uses fmt library to format the message supplied by the 
   developer.fmt is an open-source formatting library providing a fast and safe alternative to C stdio and C++ iostreams.
   https://fmt.dev/latest/api.html

   Available log types:
   FATAL: Program crash, abort, or fault imminent, or system-level instability present. Example: out of memory
   ERROR: A serious problem occurred that the application cannot recover from or work around. Example: could not open A/V pipeline
   WARNING: A problem occurred that may affect functionality now or in the future, but the application was largely able to work around the issue. Example: missing config file, using defaults
   INFO: Data that provides meaningful run-time information for aggregate or analytical purposes. Example: new Bluetooth remote paired
   DEBUG: Information that is only useful to developers. Example: a code checkpoint was reached, or the value of a variable is printed
   TRACE: For printing the entrance and exit of an closing scope via the TRACE() macro; not for general use logging.

   VIZIO logger's definition of log levels:
   FATAL = 0
   ERROR = 1
   WARNING = 2
   INFO = 3
   DEBUG = 4
   TRACE = 5
*/

#pragma once
#include <fmt/format.h>
#include <fmt/ostream.h>
#include "log_writer.h"
#include "log_manager.h"

// Log levels. These can be set at compile time via the COMPILE_TIME_LOG_LEVEL, and adjusted (to
// a value no greater than COMPILE_TIME_LOG_LEVEL) by modifying Logger::runtimeLevel.

#define LOGGING_DISABLED -1 //This is generally used to set run time log level on release builds
#define _FATAL_   0
#define _ERROR_   1
#define _WARNING_ 2
#define _INFO_    3
#define _DEBUG_   4
#define _TRACE_   5

#ifndef COMPILE_TIME_LOG_LEVEL
#define COMPILE_TIME_LOG_LEVEL _DEBUG_
#endif

// Use this macro to create a logger, ideally as a member of an enclosing class.
#define CREATE_LOGGER(MODULE,...) Logger _logger(MODULE,##__VA_ARGS__)

// Use these macros to log at the given level.
#if COMPILE_TIME_LOG_LEVEL >= _FATAL_
#define FATAL(CODE, MSG, ...) LOG("[" #CODE "] " MSG, FATAL, __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define FATAL(...)
#endif

#if COMPILE_TIME_LOG_LEVEL >= _ERROR_
#define ERROR(CODE, MSG, ...) LOG("[" #CODE "] " MSG, ERROR, __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define ERROR(...)
#endif

#if COMPILE_TIME_LOG_LEVEL >= _WARNING_
#define WARNING(MSG, ...) LOG(MSG, WARNING,  __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define WARNING(...)
#endif

#if COMPILE_TIME_LOG_LEVEL >= _INFO_
#define INFO(MSG, ...) LOG(MSG, INFO, __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define INFO(...)
#endif

#if COMPILE_TIME_LOG_LEVEL >= _DEBUG_
#define DEBUG(MSG, ...) LOG(MSG, DEBUG, __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define DEBUG(...)
#endif

// Use this macro to enabling tracing of entry and exit from an enclosing block.
#if COMPILE_TIME_LOG_LEVEL >= _TRACE_
#define TRACE() Tracer _tracer(_logger, __FILE__, __LINE__)
#else
#define TRACE()
#endif


// Macro implementation - generally there is no need to use this directly.
#define LOG(MSG, LEVEL, FILE, LINE, ...) \
if (_logger.get_runtime_level() >= _##LEVEL##_) { \
   using namespace std::chrono; \
   auto now = high_resolution_clock::now().time_since_epoch(); \
   _logger.log(fmt::format("{}:{}:" #LEVEL ": " MSG "\n", \
      FILE, LINE, ##__VA_ARGS__), \
      _##LEVEL##_,now); \
}


// Logger class that caches some of the standard information present in each log message.
// Generally there is no need to use this class directly.
class Logger
{
   public:
      Logger()
      : Logger("",_TRACE_)
      {}

      Logger(std::string module, int runtimeLevel = _TRACE_)
      :module(module)
      {
         LogManager& log_manager = LogManager::get_instance();
         log_manager.add_module(module,runtimeLevel);
      }

      void log(std::string message,int level,std::chrono::high_resolution_clock::duration now)
      {
         (void)level;
         LogWriter& log_writer = LogWriter::get_instance();
         log_writer.write_log_to_logwrapper(module, (fmt::format("{}:{}:{}", getpid(), getppid(), message)).c_str(), now, _WARNING_);
         //Need to figure out to remove duplicates for logcat logs (Module name, pid and timestamp)
      }

      int get_runtime_level()
      {
         LogManager& log_manager = LogManager::get_instance();
         return log_manager.get_runtime_log_level(module);
      }

      std::string get_module()
      {
         return module;
      }

      private:
      std::string module;
};

class Tracer
{
   public:
      Tracer(Logger & logger, const char * file, long line) : file(file),
         line(line), _logger(logger), _start(std::chrono::high_resolution_clock::now())
      {
         LOG("Tracer entry", TRACE, file, line);
      }

      ~Tracer()
      {
         using namespace std::chrono;
         const auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - _start);
         LOG("Tracer exit.  Elapsed time: {} µsecs", TRACE, file, line, elapsed.count());
      }

      const char * file;
      long line;

   private:
      Logger & _logger;
      std::chrono::high_resolution_clock::time_point _start;
};

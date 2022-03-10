# vizio-log
Implementation of vizio logging.
Use vizio log api to write logs to logcat and to send critical logs to Sentry server for analytics. Log levels FATAL, ERROR and WARNING are treated as critical logs.


# Available MACROS
FATAL(ERROR_NUMBER, LOG_MSG)

ERROR(ERROR_NUMBER, LOG_MSG)

WARNING(LOG_MSG)

INFO(LOG_MSG)

DEBUG(LOG_MSG)

TRACE()

# Description
Logger.h provides the api to log messages of various severities. logger.h uses fmt library to format the message supplied by the 
developer.fmt is an open-source formatting library providing a fast and safe alternative to C stdio and C++ iostreams.
https://fmt.dev/latest/api.html

| Level | When To Use |
|:-----:|-------------|
| FATAL | Program crash, abort, or fault imminent, or system-level instability present. Example: out of memory. |
| ERROR | A serious problem occurred that the application cannot recover from or work around. Example: could not open A/V pipeline. |
|WARNING| A problem occurred that may affect functionality now or in the future, but the application was largely able to work around the issue. Example: missing config file, using defaults. |
| INFO  | Data that provides meaningful run-time information for aggregate or analytical purposes. Example: new Bluetooth remote paired. |
| DEBUG | Information that is only useful to developers. Example: a code checkpoint was reached, or the value of a variable is printed. |
| TRACE | For printing the entrance and exit of an closing scope via the TRACE() macro; not for general use logging. |

# Create Logger for a module and set runtime log level

    CREATE_LOGGER(MODULE_NAME,RUNTIME_LEVEL);
    CREATE_LOGGER(MODULE_NAME); //Here default RUNTIME_LEVEL trace is set

# BUILD variables

    #define COMPILE_TIME_LOG_LEVEL
        Available levels
        0 - Sets Log FATAL
        1 - Sets Logs ERROR and above.
        2 - Sets Logs WARN and above.
        3 - Sets Logs INFO and above.
        4 - Sets Logs DEBUG and above.
        5 - Sets Logs TRACE and above.
    By default level 4 is set.

    Even though compile time logs are set, RUNTIME_LEVEL is used to change logs levels at runtime.
        Available levels
        0 - Sets print level FATAL.
        1 - Sets print level ERROR and above.
        2 - Sets print level WARN and above.
        3 - Sets print level INFO and above.
        4 - Sets print level DEBUG and above.
        5 - Sets print level TRACE and above.
    By default level 5 is set.


# Fields 
Timestamp: Microseconds since epoch time
#
PID: Process ID

PPID: Parent process ID

File name: Name of the source file.

Line number: Line number of the log message. 

Module name: Name of the log's module.

Log type: Severity of the log. Ex: Fatal, Error, Warning, Info, Debug, Trace.

Log message: log message set by the user.

# Example

    CREATE_LOGGER("ViziOS",_TRACE_);

    void some_func()
    {
       FATAL(CODE RED, "Fatal message test");
       ERROR(007, "Error message test: {}", 42);
       WARNING("Warning message test: {}", "42");
       INFO("Info message test: {}", std::string("42"));
       DEBUG("Debug message test: {}", 42.0);
    }

# Sample output:

1741929983402270:ViziOS:95076:62394:test.cpp:18:TRACE: Tracer entry
1741929983683141:ViziOS:95076:62394:test.cpp:22:FATAL: [CODE RED] Fatal message test
1741929983753517:ViziOS:95076:62394:test.cpp:23:ERROR: [007] Error message test: 42
1741929983814069:ViziOS:95076:62394:test.cpp:24:WARNING: Warning message test: 42
1741929983870888:ViziOS:95076:62394:test.cpp:25:INFO: Info message test: 42
1741929983927825:ViziOS:95076:62394:test.cpp:26:DEBUG: Debug message test: 42.0
1741929983996580:ViziOS:95076:62394:test.cpp:29:TRACE: Tracer entry
1741929984053316:ViziOS:95076:62394:test.cpp:29:TRACE: Tracer exit.  Elapsed time: 56 µsecs
1741929984113424:ViziOS:95076:62394:test.cpp:18:TRACE: Tracer exit.  Elapsed time: 711 µsecs




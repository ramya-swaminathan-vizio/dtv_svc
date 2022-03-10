#include "log.h"

#include <stdio.h>
#include <stdarg.h>


#ifdef __cplusplus
extern "C" {
#endif

extern void logger(const char* fmt, va_list args);

#ifdef __cplusplus
}
#endif

void vzlog::Log::log(int level, const std::string & tag, const std::string & format, ...)
{
	if (level >= vzlog::Log::level)
	{
		va_list args;
		va_start(args, format);

		std::string fmt = tag;
		fmt.append(" : ").append(format);

		logger(fmt.c_str(), args);
		va_end(args);
	}

	return;
}


vzlog::Log::Log()
{

}



void vzlog::Log::setLevel(int level) {
	if(level > LEVEL_FATAL && level < LEVEL_DEBUG) {
		return ;
	}

	vzlog::Log::level = level;
}

int vzlog::Log::level = 0;

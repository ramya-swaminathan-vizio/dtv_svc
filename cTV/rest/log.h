#ifndef Log_h
#define Log_h

#include <string>

namespace vzlog {
	class Log {
	public:
		static void log(int level, const std::string & tag, const std::string & format, ...);

		static void setLevel(int level=1);

	public:
		static const int LEVEL_DEBUG = 1;
		static const int LEVEL_INFO = 2;
		static const int LEVEL_WARNING = 3;
		static const int LEVEL_ERROR = 4;
		static const int LEVEL_FATAL = 5;



	private:
		Log();
		static int level;
	};
};

#endif


#include "c_os.h"
#include "c_dbg.h"

void logger(const char* fmt, va_list args)
{

	char buf[1024] = {0};

	/* Create debug statement string and send it to output device. */
	int ret = c_vsnprintf (buf, 1024, fmt, args);

	if (ret > 0)
	{
		DBG_LOG_PRINT(("%s \n", buf));
	}

	return;
}


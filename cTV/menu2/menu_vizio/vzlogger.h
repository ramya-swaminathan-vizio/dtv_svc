/****************************************************************************************************************/
//                      VIZIO 
//  From FUR-5.0 releases ViziOS has implemented the journald logging.  Logdw no longer exists and all 
//  the logs to logd are directed to /dev/null.

/****************************************************************************************************************/

#ifndef __VZLOGGER_H_
#define __VZLOGGER_H_

int write_buffer(const char* tag, int log_level, const char* buffer, ssize_t count);

//INFO
#define LOGGING_DISABLED -1 //This is generally used to set run time log level on release builds
#define _FATAL_   0
#define _ERROR_   1
#define _WARNING_ 2
#define _INFO_    3
#define _DEBUG_   4
#define _TRACE_   5

#define LOG(TAG, LEVEL, MSG, ...) \
do {                              \
    char fmt_buf[4096] = {0};     \
    snprintf(fmt_buf, sizeof(fmt_buf), MSG, ##__VA_ARGS__); \
    write_buffer(TAG, LEVEL, fmt_buf, strlen(fmt_buf)+1);   \
} while (0)

// #define VZ_DBG_LOG(msg, ...) LOG("btui", _DEBUG_, msg, ##__VA_ARGS__)
// #define VZ_ERR_LOG(msg, ...) LOG("btui", _ERROR_, msg, ##__VA_ARGS__)

#define VZ_DBG_LOG(msg, ...) do {char fmt_buf[4096] = {0}; snprintf(fmt_buf, sizeof(fmt_buf), msg, ##__VA_ARGS__);write_buffer("btui", _DEBUG_, fmt_buf, strlen(fmt_buf)+1);} while (0)
#define VZ_ERR_LOG(msg, ...) do {char fmt_buf[4096] = {0}; snprintf(fmt_buf, sizeof(fmt_buf), msg, ##__VA_ARGS__);write_buffer("btui", _ERROR_, fmt_buf, strlen(fmt_buf)+1);} while (0)

#define VZ_MENU_LOG_ON_FAIL(_ret)  \
do{ \
    INT32 ret = _ret;   \
    if (ret < 0)   \
    {   \
        VZ_ERR_LOG("<MENU> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret); \
    }   \
}while(FALSE)

#endif /* __LOGGER_H_ */
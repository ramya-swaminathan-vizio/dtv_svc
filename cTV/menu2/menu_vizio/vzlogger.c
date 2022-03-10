/****************************************************************************************************************/
//                      VIZIO 
//  From FUR-5.0 releases ViziOS has implemented the journald logging.  Logdw no longer exists and all 
//  the logs to logd are directed to /dev/null.

/****************************************************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "vzlogger.h"

#define LOGSOCKET   "/cast_root/dev/socket/logdw"

#define sizeof_log_id_t sizeof(typeof_log_id_t)
#define typeof_log_id_t unsigned char
typedef struct log_time {
  uint32_t tv_sec;
  uint32_t tv_nsec;
} __attribute__((__packed__)) log_time;

typedef struct __attribute__((__packed__)) {
  typeof_log_id_t id;
  uint16_t tid;
  log_time realtime;
} android_log_header_t;

int logd_fd = -1;

static void _init_logd()
{
    logd_fd = socket(PF_UNIX, SOCK_DGRAM | SOCK_CLOEXEC | SOCK_NONBLOCK, 0);
    if (logd_fd >= 0) {
        struct sockaddr_un un;
        memset(&un, 0, sizeof(struct sockaddr_un));
        un.sun_family = AF_UNIX;
        strcpy(un.sun_path,LOGSOCKET);
        if(connect(logd_fd, (struct sockaddr*)&un, sizeof(struct sockaddr_un)) < 0) {
            close(logd_fd);
            logd_fd = -1;
        }
    } else {
        logd_fd = -1;
    }
}

int write_buffer(const char* tag, int log_level, const char* buffer, ssize_t count)
{
    int ret = 0;

    static android_log_header_t header;
    struct iovec vec[4] = { { .iov_base = (unsigned char*)&header, .iov_len = sizeof(header) } };

    struct timeval tv;
    static int isInitialyzed = 0;

    if(!isInitialyzed)
    {
        isInitialyzed = 1;
        memset(&header, 0, sizeof(android_log_header_t));
        header.id = 0;
        header.tid = (uint16_t)getpid();
    }

    gettimeofday(&tv, NULL);
    header.realtime.tv_sec = (uint32_t)tv.tv_sec;
    header.realtime.tv_nsec = (uint32_t)tv.tv_usec * 1000;

    vec[1].iov_base = (unsigned char *) &log_level;
    vec[1].iov_len  = 1;
    vec[2].iov_base = (void *) tag;
    vec[2].iov_len  = strlen(tag) + 1;
    vec[3].iov_base = (void *) buffer;
    vec[3].iov_len = (size_t)count;

    if (logd_fd == -1)
    {
        _init_logd();
    }
    
    if (logd_fd > 0)
    {
        ret = writev(logd_fd, vec, sizeof(vec)/sizeof(vec[0]));
        switch (ret)
        {
            case -ENOTCONN:
            case -ECONNREFUSED:
            case -ENOENT:
                close(logd_fd);
                _init_logd();
                if (logd_fd > 0)
                {
                    writev(logd_fd, vec, 4);
                }
                break;
            default:
                break;
        }
    }
    return ret;
}

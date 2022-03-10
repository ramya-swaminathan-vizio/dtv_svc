/*
   log_writer.h
   © 2020 Vizio Services, All Rights Reserved
   log_writer.h is used to write the logs to a desired location.
   For non-production TVs all the logs will be directed to logdw socket of logwrapper.
   For production TVs only FATAL, ERROR and WARNING logs will be sent to Sentry.
*/

#pragma once
#include <chrono>
#include <fcntl.h>
#include <fstream>
#include <mutex>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <string>
#include <unistd.h>
#include <iostream>

#define log_id_t unsigned char

typedef struct log_time
{
  uint32_t tv_sec;
  uint32_t tv_nsec;
} __attribute__((__packed__)) log_time;

typedef struct __attribute__((__packed__))
{
  log_id_t id;
  uint16_t pid;
  log_time realtime;
} vizio_log_header_t;

// Need this class to write the logs to a desired location. Currently our aim is to write the logs
// to logdw socket from which logcat reads the logs.
class LogWriter
{
  private:
  LogWriter()
  {
    set_socket = set_logdw_socket();
  }

  ~LogWriter()
  {
  }

  LogWriter(LogWriter &&) = delete;

  const char *LOG_SOCKET = "/dev/log/main";
  bool set_socket = false;
  bool mtk_socket = false;

  int logd_fd = -1;
  std::mutex log_writer_mutex;

  bool file_exists(const char *filename)
  {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
  }

  bool set_logdw_socket()
  {
    if(file_exists("/system/bin/sigma_mount")) {
      LOG_SOCKET = "/dev/log/main";
      mtk_socket = false;
      return true;
      } else if (file_exists("/vendor/cast_root/dev/socket/logdw")) {
        LOG_SOCKET = "/vendor/cast_root/dev/socket/logdw";
        mtk_socket = true;
        return true;
      } else if (file_exists("/vendor/dev/socket/logdw")) {
        LOG_SOCKET = "/vendor/dev/socket/logdw";
        mtk_socket = true;
        return true;
      } else if (file_exists("/cast_root/dev/socket/logdw")) {
        LOG_SOCKET = "/cast_root/dev/socket/logdw";
        mtk_socket = true;
        return true;
      } else if (file_exists("/dev/socket/logdw")) {
        LOG_SOCKET = "/dev/socket/logdw";
        mtk_socket = true;
        return true;
      }
      return false;
  }

  void init_logwrapper_socket()
  {
    if(!set_socket)
    {
      return;
    }

    std::unique_lock<std::mutex> lock(log_writer_mutex);

    if (mtk_socket)
    {
      logd_fd = socket(PF_UNIX, SOCK_DGRAM, 0);

      if (logd_fd >= 0)
      {
        struct sockaddr_un un;
        memset(&un, 0, sizeof(struct sockaddr_un));
        un.sun_family = AF_UNIX;
        strcpy(un.sun_path, LOG_SOCKET);

        if (connect(logd_fd, (struct sockaddr *)&un, sizeof(struct sockaddr_un)) < 0)
        {
          close(logd_fd);
          logd_fd = -1;
        }
      }
    }

    else
    {
      logd_fd = open(LOG_SOCKET, O_WRONLY);
    }
    lock.unlock();
  }

public:
  static LogWriter& get_instance()
  {
    static LogWriter instance;
    return instance;
  }

  void write_log_to_logwrapper(const std::string module, const char *buffer, std::chrono::high_resolution_clock::duration now, int log_level)
  {
    if(!set_socket)
    {
      set_socket = set_logdw_socket();
    }

    if (logd_fd == -1)
    {
      init_logwrapper_socket();
    }

    if(logd_fd == -1)
    {
      std::cout<<"Failed writing to logdw socket, module : "<<module<<": "<<buffer<<std::endl;
      return;
    }

    ssize_t count = strlen(buffer) + 1;

    if(mtk_socket)
    {
      vizio_log_header_t header;
      struct iovec vec[4];
      memset(&header, 0, sizeof(vizio_log_header_t));
      header.id = 0;
      header.pid = (uint16_t)getpid();
      using namespace std::chrono;
      header.realtime.tv_sec = (uint32_t)duration_cast<seconds>(now).count();
      header.realtime.tv_nsec = (uint32_t)duration_cast<nanoseconds>(now).count();
      vec[0].iov_base = (unsigned char *)&header;
      vec[0].iov_len  = sizeof(header);
      vec[1].iov_base = (unsigned char *) &log_level;
      vec[1].iov_len  = 1;
      vec[2].iov_base = (void *) module.c_str();
      vec[2].iov_len  = module.size() + 1;
      vec[3].iov_base = (void *) buffer;
      vec[3].iov_len = (size_t)count;
      if(logd_fd > 0) { if (writev(logd_fd, vec, sizeof(vec) / sizeof(vec[0]))) { /* suppress -Wunused-result */ } }
    }
    else
    {
      struct iovec vec[3];
      vec[0].iov_base = (unsigned char *) &log_level;
      vec[0].iov_len  = 1;
      vec[1].iov_base = (void *) module.c_str();
      vec[1].iov_len  = module.size() + 1;
      vec[2].iov_base = (void *) buffer;
      vec[2].iov_len = (size_t)count;
      if(logd_fd > 0) { if (writev(logd_fd, vec, sizeof(vec) / sizeof(vec[0]))) { /* suppress -Wunused-result */ } }
    }
  }
};
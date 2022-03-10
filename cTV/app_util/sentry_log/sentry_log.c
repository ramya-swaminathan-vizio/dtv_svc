/**
 * @file sentry_log.c
 * @author maksym.shestirko (maksym.shestirko@vizio.com)
 * @brief
 * @version 0.1
 * @date 2021-12-27
 *
 * © 2021 Vizio Services, All Rights Reserved
 *
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "c_common.h"
#include "c_dbg.h"

#include "rest/vzipc/vzIpcServer.h"

void DtvLogToSentry(const char *message, ...)
{
    char sentry_buffer[256] = {0};
    va_list args;
    va_start(args, message);
    snprintf(sentry_buffer, sizeof(sentry_buffer), message, args);
    va_end(args);
    SendReqBTAUDIO_Q(COMMON_DTV_TO_SENTRY, sentry_buffer);
    DBG_LOG_PRINT(("dtv sentry_buffer = %s ", sentry_buffer));
}

void VzLogToSentry(const char *message, ...)
{
    char sentry_buffer[256] = {0};
    va_list args;
    va_start(args, message);
    snprintf(sentry_buffer, sizeof(sentry_buffer), message, args);
    va_end(args);
    SendReqBTAUDIO_Q(BTAPI_SEND_TO_SENTRY, sentry_buffer);
    DBG_LOG_PRINT(("BT_HEADPHONES : sentry_buffer = %s ", sentry_buffer));
}

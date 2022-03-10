/**
 * @file sentry_log.h
 * @author maksym.shestirko (maksym.shestirko@vizio.com)
 * @brief
 * @version 0.1
 * @date 2021-12-27
 *
 * © 2021 Vizio Services, All Rights Reserved
 *
 */
#ifndef __SENTRY_LOG_H__
#define __SENTRY_LOG_H__

/**
 * @brief
 *
 * @param message
 * @param ...
 */
void DtvLogToSentry(const char *message, ...);

/**
 * @brief
 *
 * @param message
 * @param ...
 */
void VzLogToSentry(const char *message, ...);

#endif /* __SENTRY_LOG_H__ */

//
// tts_status.h
// © 2021 Vizio Services, All Rights Reserved
//
#ifndef TTS_STATUS_H
#define TTS_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

  typedef enum _TtsStatus
  {
    TtsStatusOn,
    TtsStatusOff,
    TtsStatusUnknown
  }TtsStatus;

  bool initializeTtsStatus();
  void setTtsStatus(TtsStatus state);
  void deinitializeTtsStatus();

#ifdef __cplusplus
}
#endif

#endif // TTS_STATUS_H 

//
// systemui_visibility.h
// © 2021 Vizio Services, All Rights Reserved
//
#ifndef SYSTEMUI_VISIBILITY_H
#define SYSTEMUI_VISIBILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

  typedef enum _SystemUIState
  {
    SystemUIStateVisible,
    SystemUIStateInvisible,
    SystemUIStateUnknown
  }SystemUIState; 

  typedef void (*FUNC_PTR_SYSTEMUISTATE)(SystemUIState);

  bool initializeSystemUIState();
  SystemUIState getCurrentSystemUIState();
  bool onSystemUIStateChange(FUNC_PTR_SYSTEMUISTATE callback);
  bool deinitializeSystemUIState();

#ifdef __cplusplus
}
#endif

#endif // SYSTEMUI_VISIBILITY_H



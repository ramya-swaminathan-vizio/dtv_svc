//
// sidebarmenu_visibility.h
// © 2021 Vizio Services, All Rights Reserved
//
#ifndef SIDEBARMENU_VISIBILITY_H
#define SIDEBARMENU_VISIBILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

  typedef enum _MenuUIState
  {
    MenuUIStateVisible,
    MenuUIStateInvisible,
    MenuUIStateUnknown
  }MenuUIState;

  bool initializeMenuUIState();
  void setMenuUIState(MenuUIState state);
  void deinitializeMenuUIState();

#ifdef __cplusplus
}
#endif

#endif // SIDEBARMENU_VISIBILITY_H 
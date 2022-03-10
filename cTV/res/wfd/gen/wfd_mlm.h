/*-----------------------------------------------------------------------------
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 * 
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: mlmgen_renderer.c,v $
 * $Revision: #1 $
 * $Date:   
 * $Author: 
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *     This file is generated by mlmgen, which is provided by MediaTek, Inc. 
 *---------------------------------------------------------------------------*/
#ifndef _wfd_mlm_h_
#define _wfd_mlm_h_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define MLM_WFD_TEXT(lang, key) mlm_wfd_get_text(lang, key)

#define MLM_WFD_NUM_LANG 3
#define MLM_WFD_NUM_KEY 67

#define MLM_WFD_KEY_BTN_FIND_DEVICE 0
#define MLM_WFD_KEY_BTN_DISCONNECTION 1
#define MLM_WFD_KEY_BTN_BACK 2
#define MLM_WFD_KEY_BTN_PBC 3
#define MLM_WFD_KEY_BTN_ENTER_PIN 4
#define MLM_WFD_KEY_BTN_SHOW_PIN 5
#define MLM_WFD_KEY_WFD_TITLE 6
#define MLM_WFD_KEY_SELECT_CONNECTION_TITLE 7
#define MLM_WFD_KEY_ENTER_PIN_NOTIFY 8
#define MLM_WFD_KEY_CANCEL 9
#define MLM_WFD_KEY_CLEAR 10
#define MLM_WFD_KEY_ENTER 11
#define MLM_WFD_KEY_ENABLE_WFD_FAILED 12
#define MLM_WFD_KEY_CONNEC_STATE_TITLE 13
#define MLM_WFD_KEY_P2P_CONNECT_FAIL 14
#define MLM_WFD_KEY_P2P_CONNECT_SUCCESS 15
#define MLM_WFD_KEY_BTN_RESTART_RTSP 16
#define MLM_WFD_KEY_START_RTSP 17
#define MLM_WFD_KEY_RTSP_FAIL 18
#define MLM_WFD_KEY_RTSP_SUCCESS 19
#define MLM_WFD_KEY_IP_STR 20
#define MLM_WFD_KEY_PORT_STR 21
#define MLM_WFD_KEY_IP_GET_FAIL 22
#define MLM_WFD_KEY_CONNECT_STR 23
#define MLM_WFD_KEY_ENABLE_WFD 24
#define MLM_WFD_KEY_DISABLE_WFD 25
#define MLM_WFD_KEY_DEVICE_NAME 26
#define MLM_WFD_KEY_DEVICE_TYPE 27
#define MLM_WFD_KEY_MAC_STR 28
#define MLM_WFD_KEY_BTN_EXIT 29
#define MLM_WFD_KEY_FIND_NO_DEVICE 30
#define MLM_WFD_KEY_DO_AGAIN 31
#define MLM_WFD_KEY_TRY_TO_ENABLE 32
#define MLM_WFD_KEY_CUT_RTSP_CONNECT 33
#define MLM_WFD_KEY_WIFI_SESSION 34
#define MLM_WFD_KEY_BTN_YES 35
#define MLM_WFD_KEY_START_RTSP_CONNECT 36
#define MLM_WFD_KEY_START_P2P_CONNECT 37
#define MLM_WFD_KEY_STOP_RTSP_CONNECT 38
#define MLM_WFD_KEY_STOP_P2P_CONNECT 39
#define MLM_WFD_KEY_CUT_P2P_CONNECT 40
#define MLM_WFD_KEY_INPUT_STR 41
#define MLM_WFD_KEY_REQ_CONNECT 42
#define MLM_WFD_KEY_SHOW_PIN_TITLE 43
#define MLM_WFD_KEY_PIN_WRONG 44
#define MLM_WFD_KEY_FIND_ING 45
#define MLM_WFD_KEY_REFRESH 46
#define MLM_WFD_KEY_ENABLE_ING 47
#define MLM_WFD_KEY_DISABLE_ING 48
#define MLM_WFD_KEY_VOLUME_UP 49
#define MLM_WFD_KEY_VOLUME_DOWN 50
#define MLM_WFD_KEY_WFD_STOP 51
#define MLM_WFD_KEY_RESUME 52
#define MLM_WFD_KEY_CONNECT_TIME_COUNT 53
#define MLM_WFD_KEY_CONNECT_TIME_OUT 54
#define MLM_WFD_KEY_BACK_TO_MAIN 55
#define MLM_WFD_KEY_RESUME_NOTE 56
#define MLM_WFD_KEY_DISCONNECT_NOTE 57
#define MLM_WFD_KEY_P2P_CONNECTION 58
#define MLM_WFD_KEY_P2P_DISCONNECT 59
#define MLM_WFD_KEY_PRESS_CANCEL_TO_MAIN 60
#define MLM_WFD_KEY_ENTER_VALID_PIN1 61
#define MLM_WFD_KEY_DGTS8_VALID_PIN2 62
#define MLM_WFD_KEY_WFD_VIZIO_TITLE 63
#define MLM_WFD_KEY_WFD_VIZIO_MSG1 64
#define MLM_WFD_KEY_WFD_VIZIO_MSG2 65
#define MLM_WFD_KEY_WFD_VIZIO_RESCAN 66

#define MLM_WFD_LANG_ENG 0
#define MLM_WFD_LANG_SPA 1
#define MLM_WFD_LANG_FRE 2

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
-----------------------------------------------------------------------------*/
extern UTF16_T* mlm_wfd_get_text(UINT16 ui2_lang, UINT16 ui2_key);
extern UINT16 mlm_wfd_s639_to_langidx(ISO_639_LANG_T s639_lang);
extern VOID mlm_wfd_langidx_to_s639(UINT16 ui2_lang,ISO_639_LANG_T s639_lang);

#endif /* _wfd_mlm_h_ */

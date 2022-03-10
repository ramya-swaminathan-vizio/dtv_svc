/*-----------------------------------------------------------------------------
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 * 
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: mlmgen_renderer.c,v $
 * $Revision: #21 $
 * $Date:   
 * $Author: 
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *     This file is generated by mlmgen V1.46, which is provided by MediaTek, Inc. 
 *---------------------------------------------------------------------------*/
#ifndef _nav_cec_view_mlm_h_
#define _nav_cec_view_mlm_h_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define MLM_CEC_TEXT(lang, key) mlm_cec_get_text(lang, key)

#define MLM_CEC_NUM_LANG 3
#define MLM_CEC_NUM_KEY 60

#define MLM_CEC_KEY_TITLE 0
#define MLM_CEC_KEY_STANDBY 1
#define MLM_CEC_KEY_PLAY 2
#define MLM_CEC_KEY_DECK_CTRL 3
#define MLM_CEC_KEY_RECORD 4
#define MLM_CEC_KEY_MENU 5
#define MLM_CEC_KEY_STOP 6
#define MLM_CEC_KEY_SAC_ON 7
#define MLM_CEC_KEY_SAC_OFF 8
#define MLM_CEC_KEY_ON 9
#define MLM_CEC_KEY_OFF 10
#define MLM_CEC_KEY_ENTER_MENU 11
#define MLM_CEC_KEY_LEAVE_MENU 12
#define MLM_CEC_KEY_FUNC_ON 13
#define MLM_CEC_KEY_FUNC_OFF 14
#define MLM_CEC_KEY_AUTO_OFF_ON 15
#define MLM_CEC_KEY_AUTO_OFF_OFF 16
#define MLM_CEC_KEY_DEV_REC_1 17
#define MLM_CEC_KEY_DEV_REC_2 18
#define MLM_CEC_KEY_DEV_REC_3 19
#define MLM_CEC_KEY_DEV_TUNER_1 20
#define MLM_CEC_KEY_DEV_TUNER_2 21
#define MLM_CEC_KEY_DEV_TUNER_3 22
#define MLM_CEC_KEY_DEV_TUNER_4 23
#define MLM_CEC_KEY_DEV_PLAY_1 24
#define MLM_CEC_KEY_DEV_PLAY_2 25
#define MLM_CEC_KEY_DEV_PLAY_3 26
#define MLM_CEC_KEY_DEV_AUDIO 27
#define MLM_CEC_KEY_DEV_SETUP 28
#define MLM_CEC_KEY_STS_MSG_NO_RSP 29
#define MLM_CEC_KEY_STS_MSG_NO_SUPPORT 30
#define MLM_CEC_KEY_MANUAL_DEV_SCAN 31
#define MLM_CEC_KEY_POWER_ON 32
#define MLM_CEC_KEY_REC_STS_MSG_REC_CUR_SELECTED_SRC 33
#define MLM_CEC_KEY_REC_STS_MSG_REC_DIG_SRC 34
#define MLM_CEC_KEY_REC_STS_MSG_REC_ANA_SRC 35
#define MLM_CEC_KEY_REC_STS_MSG_REC_EXT_INPUT 36
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_UNABLE_TO_REC_DIG_SRC 37
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_UNABLE_TO_REC_ANA_SRC 38
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_UNABLE_TO_REC_SELECT_REQ_SRC 39
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_INV_EXT_PLUG_NUM 40
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_INV_EXT_PHY_ADDR 41
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_CA_SYS_NOT_SUPPORTED 42
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_NO_OR_INSUFF_CA_ENTITLEMENTS 43
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_NOT_ALLOWED_TO_COPY_SRC 44
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_NOT_FURTHER_COPIES_ALLOWED 45
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_NO_MEDIA 46
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_PLAYING 47
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_ALREADY_REC 48
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_MEDIA_PROTECTED 49
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_NO_SRC_SIGNAL 50
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_MEDIA_PROBLEM 51
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_NOT_ENOUGH_SPACE_AVAL 52
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_PARENTAL_LOCK_ON 53
#define MLM_CEC_KEY_REC_STS_MSG_REC_TERMINATED_NORMALLY 54
#define MLM_CEC_KEY_REC_STS_MSG_REC_HAS_ALREADY_TERMINATED 55
#define MLM_CEC_KEY_REC_STS_MSG_NO_REC_OTHER_REASON 56
#define MLM_CEC_KEY_ERR_MSG_CAN_NOT_PROVIDE_SRC 57
#define MLM_CEC_KEY_DEV_MHL 58
#define MLM_CEC_KEY_STS_MSG_WAIT_PWR_ON 59

#define MLM_CEC_LANG_ENG 0
#define MLM_CEC_LANG_FRE 1
#define MLM_CEC_LANG_SPA 2

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
-----------------------------------------------------------------------------*/
extern UTF16_T* mlm_cec_get_text(UINT16 ui2_lang, UINT16 ui2_key);
extern UINT16 mlm_cec_s639_to_langidx(ISO_639_LANG_T s639_lang);
extern VOID mlm_cec_langidx_to_s639(UINT16 ui2_lang,ISO_639_LANG_T s639_lang);

#endif /* _nav_cec_view_mlm_h_ */

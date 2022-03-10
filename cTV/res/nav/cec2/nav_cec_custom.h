/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation ("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright (C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights (including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation ("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights (including without limitation, patent, copyright, and      *
 * trade secrets) in and to any modifications and derivatives to MediaTek     *
 * Software, whoever made, shall also remain the exclusive property of        *
 * MediaTek Inc.  Nothing herein shall be construed as any transfer of any    *
 * title to any intellectual property right in MediaTek Software to Receiver. *
 *                                                                            *
 *   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its *
 * representatives is provided to Receiver on an "AS IS" basis only.          *
 * MediaTek Inc. expressly disclaims all warranties, expressed or implied,    *
 * including but not limited to any implied warranties of merchantability,    *
 * non-infringement and fitness for a particular purpose and any warranties   *
 * arising out of course of performance, course of dealing or usage of trade. *
 * MediaTek Inc. does not provide any warranty whatsoever with respect to the *
 * software of any third party which may be used by, incorporated in, or      *
 * supplied with the MediaTek Software, and Receiver agrees to look only to   *
 * such third parties for any warranty claim relating thereto.  Receiver      *
 * expressly acknowledges that it is Receiver's sole responsibility to obtain *
 * from any third party all proper licenses contained in or delivered with    *
 * MediaTek Software.  MediaTek is not responsible for any MediaTek Software  *
 * releases made to Receiver's specifications or to conform to a particular   *
 * standard or open forum.                                                    *
 *                                                                            *
 *   3)Receiver further acknowledge that Receiver may, either presently       *
 * and/or in the future, instruct MediaTek Inc. to assist it in the           *
 * development and the implementation, in accordance with Receiver's designs, *
 * of certain softwares relating to Receiver's product(s) (the "Services").   *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MediaTek Inc. with respect  *
 * to the Services provided, and the Services are provided on an "AS IS"      *
 * basis. Receiver further acknowledges that the Services may contain errors  *
 * that testing is important and it is solely responsible for fully testing   *
 * the Services and/or derivatives thereof before they are used, sublicensed  *
 * or distributed. Should there be any third party action brought against     *
 * MediaTek Inc. arising out of or relating to the Services, Receiver agree   *
 * to fully indemnify and hold MediaTek Inc. harmless.  If the parties        *
 * mutually agree to enter into or continue a business relationship or other  *
 * arrangement, the terms and conditions set forth herein shall remain        *
 * effective and, unless explicitly stated otherwise, shall prevail in the    *
 * event of a conflict in the terms in any agreements entered into between    *
 * the parties.                                                               *
 *                                                                            *
 *   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and    *
 * cumulative liability with respect to MediaTek Software released hereunder  *
 * will be, at MediaTek Inc.'s sole discretion, to replace or revise the      *
 * MediaTek Software at issue.                                                *
 *                                                                            *
 *   5)The transaction contemplated hereunder shall be construed in           *
 * accordance with the laws of Singapore, excluding its conflict of laws      *
 * principles.  Any disputes, controversies or claims arising thereof and     *
 * related thereto shall be settled via arbitration in Singapore, under the   *
 * then current rules of the International Chamber of Commerce (ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * $RCSfile: nav_cec_custom.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *         This header file contains customization part of the CEC implementation.
 *---------------------------------------------------------------------------*/

#ifndef _NAV_CEC_CUSTOM_H_
#define _NAV_CEC_CUSTOM_H_

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "res/nav/nav_img_rc.h"
#include "nav/cec2/nav_cec.h"

#ifndef NAV_CEC_LOG_ON_ERR
#define NAV_CEC_LOG_ON_ERR(_expr)  \
{ \
    INT32 expr = _expr; \
    if(expr != 0)\
    {\
        DBG_LOG_PRINT(("[NAV_CEC] ERR: file: %s, function: %s, line: %d, ret: %d\n\r", __FILE__, __FUNCTION__, __LINE__, expr)); \
    } \
}
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/**
 * @brief This enum lists all available CEC commands for the CEC devices.
 *        Command code listed here are used in the command list.
 */
typedef enum
{
    /* Commands that will send to CEC deivce. */
    CEC_CMD_NONE = 0,
    CEC_CMD_STANDBY,                /* System standby. */
    CEC_CMD_MENU,                   /* Device menu control. */
    CEC_CMD_PLAY,                   /* Routing control. */
    CEC_CMD_DECK_CTRL,              /* Deck control. */
    CEC_CMD_RECORD,                 /* Recording device. */
    CEC_CMD_SAC_ON,                 /* Audio system. */
    CEC_CMD_SAC_OFF,                /* Audio system. */
    CEC_CMD_SAC_SWITCH,             /* Audio system. */
    CEC_CMD_POWER_ON,               /* Give device power status. */
    /* TV internal commands. */
    CEC_CMD_CEC_FUNC_ON,            /* CEC function enable/disable. */
    CEC_CMD_CEC_FUNC_OFF,           /* CEC function enable/disable. */
    CEC_CMD_AUTO_OFF_ON,            /* Auto turn off. */
    CEC_CMD_AUTO_OFF_OFF,           /* Auto turn off. */
    CEC_CMD_MANUAL_DEV_SCAN,        /* Manual device scan. */
    CEC_CMD_LAST_ENTRY
} NAV_CEC_CMD_T;

typedef enum
{
    NAV_CEC_DECK_VIEW_EJECT = 0,
    NAV_CEC_DECK_VIEW_PLAY,
    NAV_CEC_DECK_VIEW_PAUSE,
    NAV_CEC_DECK_VIEW_STOP,
    NAV_CEC_DECK_VIEW_FAST_REVERSE,
    NAV_CEC_DECK_VIEW_FAST_FORWARD,
    NAV_CEC_DECK_VIEW_SKIP_REVERSE,
    NAV_CEC_DECK_VIEW_SKIP_FORWARD,
    NAV_CEC_DECK_VIEW_LAST_ENTRY
} NAV_CEC_VIEW_DECK_ITEM_T;

/**
 * @brief This enum lists all CEC command codes.
 *        Command listed here are used in the command queue.
 */
typedef enum
{
    CEC_CMD_CODE_NONE = 0,          /**< Init value. */
    CEC_CMD_CODE_POWER_ON,          /**< Perform the power on sequence for a CEC device. */
    CEC_CMD_CODE_SET_STRM_PATH,     /**< Corresponding to CECM_OPCODE_SET_STREAM_PATH. */
    CEC_CMD_CODE_STANDBY,           /**< Corresponding to CECM_OPCODE_STANDBY. */
    CEC_CMD_CODE_MENU,           /**< Corresponding to CECM_OPCODE_MENU_REQ. */
    CEC_CMD_CODE_RECORD,           /**< Corresponding to CECM_OPCODE_REC_ON. */
    CEC_CMD_CODE_USER_CTRL_PRESSED, /**< Corresponding to CECM_OPCODE_USER_CTRL_PRESSED. */
    CEC_CMD_CODE_USER_CTRL_RELEASED,/**< Corresponding to CECM_OPCODE_USER_CTRL_RELEASED. */
    CEC_CMD_CODE_DEV_DISCOVERY,     /**< Perform device discovery. */
    CEC_CMD_CODE_SYS_AUD_MOD_REQ,   /**< Corresponding to CECM_OPCODE_SYS_AUD_MOD_REQ. */
    CEC_CMD_CODE_LAST_ENTRY
} NAV_CEC_CMD_CODE_T;

/* Pre-defined values. */
#define NAV_CEC_DEV_DISCOVERY_INTERVAL      (0)    /* Seconds. 0 means manual scan. */

//#define NAV_CEC_VNDR_ID                     (0x006D746B)    /* 'm' 't' 'k' */
#define NAV_CEC_VNDR_ID                     (0x0000199D)    /* Vizio */

#define NAV_CEC_VNDR_CMD_WITH_ID_AMP        (0x4F495A4956)  /* Vizio Sound Bar*/
#define NAV_CEC_VNDR_CMD_WITH_ID_AMP_SIZE   ((SIZE_T)  5)   /* Device vendor commond with ID Size for Sound bar */

#define NAV_CEC_VER_ID                      (CECM_CEC_VER_1_4A)
#define NAV_CEC_SAC_KEY_INTERVAL            (210)   /* ms. */
#define NAV_CEC_CUSTOM_ARC_HDLR
#define NAV_CEC_CUSTOM_ROUTING_CTRL_MW_OPCODE_HDLR

/* Known vender IDs. */
#define NAV_CEC_VNDR_ID_SHARP               (0x08001F)

/* Features. */
#define NAV_CEC_STORE_STANDBY_IN_ACFG       (1)
#define NAV_CEC_ENABLE_VIEW                 (1)

#define NAV_CEC_SUPPORT_ARC_PORT_ID         (0)

#ifdef APP_ARC_ONLY
extern BOOL	b_g_is_amp_plug_dlg_show;
#endif

typedef VOID (*cec_mw_nfy_fct)(
                    CECM_NFY_T*                 pv_nfy_data,
                    VOID*                       pv_tag,
                    UINT32                      ui4_data
                    );


extern BOOL b_SoundBarDbgLevel;

#define NAV_SB_DBG_MSG(x) do { \
    if( b_SoundBarDbgLevel ) \
    {\
        x ; \
    }\
} while(0)


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
BOOL nav_cec_custom_is_activation_allowed (NAV_CEC_FEATURE_ID_T e_cur_id, NAV_CEC_FEATURE_ID_T e_next_id);
INT32 nav_cec_custom_init (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);
INT32 nav_cec_custom_deinit (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);
INT32 nav_cec_custom_get_cmd_str (NAV_CEC_CMD_T e_cec_cmd, UTF16_T** ppw2s_str);
INT32 nav_cec_custom_get_menu_cmd_str (BOOL b_menu_active, UTF16_T** ppw2s_str);
INT32 nav_cec_custom_get_rec_cmd_str (BOOL b_is_recording, UTF16_T** ppw2s_str);
BOOL nav_cec_dmc_custom_is_digital_key_forward(VOID);
BOOL nav_cec_custom_is_ignore_one_touch_play (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);
VOID nav_cec_custom_notify_input_changed_by_otp (ISL_REC_T* pt_isl_rec);
BOOL nav_cec_custom_is_ignore_one_touch_record (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);
BOOL nav_cec_custom_is_ignore_sys_aud_ctrl(VOID);
BOOL nav_cec_custom_allow_changing_tv_speaker_status (VOID);
UINT32 nav_cec_custom_key_code_translation (UINT32 ui4_key_code, CECM_LOG_ADDR_T e_dev_la);
BOOL nav_cec_custom_is_cast_source_active(VOID);
CECM_OPCODE_T nav_cec_custom_get_opcode_by_cmd (NAV_CEC_CMD_T e_cec_cmd);

extern INT32 nav_cec_custom_routing_ctrl_mw_opcode_hdlr (
                CECM_OPCODE_T   e_opcode,
                CECM_NFY_T*     pt_cecm_nfy,
                BOOL*           pb_process);

INT32 nav_cec_custom_mw_nfy_pre_hdlr (
            NAV_CEC_UDPATE_INFO_NFY_T* pt_update_info,
            VOID* pv_tag,
            UINT32 ui4_data,
            BOOL* pb_skip
            );

INT32 nav_cec_custom_pre_init(cec_mw_nfy_fct* ppf_nfy_fct,
                              cec_mw_nfy_fct  pf_def_nfy_fct);
INT32 nav_cec_custom_power_on_handler(VOID);
VOID nav_cec_custom_power_on_flag_set(VOID);
INT32 nav_cec_custom_bgm_handler(BOOL b_bgm);
extern BOOL cec_custom_allow_visible (VOID);

#define CEC_SETTINGS_TEXT(key)   MLM_SETTINGS_TEXT(cec_get_mlm_settings_lang_id(), (key))
extern UINT8 cec_get_mlm_settings_lang_id(VOID);

#ifdef APP_ARC_ONLY
extern INT32 nav_cec_custom_amp_plug_dlg_show(VOID);
extern BOOL nav_cec_custom_amp_plug_dlg_is_need_show();
extern BOOL _nav_cec_custom_block_volume_key_forward (VOID);
extern VOID nav_cec_custom_amp_nfy();
#endif /* APP_ARC_ONLY */

#ifdef APP_WIZARD_CUSTOM_SUPPORT
extern INT32 nav_cec_custom_is_mute_under_wzd(VOID);
#endif
extern INT32 nav_cec_sac_drv_set_dts_enable(BOOL b_enable);
extern INT32 a_tv_nav_cec_set_arc_spdif_mute(BOOL b_mute);

BOOL acfg_custom_get_enable_soundbarsettings(VOID);
BOOL nav_cec_custom_get_soundbarsettings_ready(VOID);
BOOL nav_cec_custom_get_enable_eq(VOID);
BOOL nav_cec_custom_get_enable_bass(VOID);
BOOL nav_cec_custom_get_enable_treble(VOID);
BOOL nav_cec_custom_get_enable_dialogue(VOID);
BOOL nav_cec_custom_get_enable_subwoofer(VOID);
BOOL nav_cec_custom_get_enable_nightmode(VOID);
BOOL nav_cec_custom_get_enable_virtual(VOID);

BOOL nav_cec_custom_get_eq_mode_enable_music(VOID);
BOOL nav_cec_custom_get_eq_mode_enable_movie(VOID);
BOOL nav_cec_custom_get_eq_mode_enable_game(VOID);
BOOL nav_cec_custom_get_eq_mode_enable_direct(VOID);
BOOL nav_cec_custom_get_eq_mode_enable_dialogue(VOID);

UINT8 nav_cec_custom_get_enable_eq_mode_type(VOID);
VOID nav_cec_custom_set_enable_eq_mode_type(UINT8 eq_mode_type);
UINT8 nav_cec_custom_get_enable_eq_mode_valid_num(VOID);

UINT8 nav_cec_custom_get_enable_bass_type(VOID);
UINT8 nav_cec_custom_get_enable_treble_type(VOID);
UINT8 nav_cec_custom_get_enable_dialogue_type(VOID);
UINT8 nav_cec_custom_get_enable_subwoofer_type(VOID);
UINT8 nav_cec_custom_get_enable_nightmode_type(VOID);
UINT8 nav_cec_custom_get_enable_virtualx_type(VOID);

INT32 nav_cec_custom_set_eq_mode(INT32 i4_val);
INT32 nav_cec_custom_set_bass_val(INT32 i4_val);
INT32 nav_cec_custom_set_treble_val(INT32 i4_val);
INT32 nav_cec_custom_set_dialogue_val(INT32 i4_val);
INT32 nav_cec_custom_set_subwoofer_val(INT32 i4_val);
INT32 nav_cec_custom_set_nightmode_val(INT32 i4_val);
INT32 nav_cec_custom_set_virtualx_val(INT32 i4_val);

INT32 nav_cec_custom_set_speakertest_val(INT32 i4_val);
INT32 nav_cec_custom_set_info_val(INT32 i4_val);


#endif /* APP_CEC2_SUPPORT */
#endif /* APP_CEC_SUPPORT */
#endif /* _NAV_CEC_CUSTOM_H_ */


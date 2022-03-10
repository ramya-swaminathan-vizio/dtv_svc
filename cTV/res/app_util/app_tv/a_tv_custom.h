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
 * $RCSfile: ui_custom.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the custom layer header file for UI
 *---------------------------------------------------------------------------*/


#ifndef _A_TV_CUSTOM_H_
#define _A_TV_CUSTOM_H_

#include "u_common.h"
/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/

typedef enum
{
	IR_MODE_TV = 0,
	IR_MODE_PD,
	IR_MODE_3RD,
	IR_MODE_DOCK,
	IR_MODE_MENU,
	IR_MODE_FAKE
}IR_MODE_E;

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
#ifdef APP_IPCC_SUPPORT
typedef struct
{
	BOOL b_running;
}APP_TV_NET_IPCC_PROPERTY;
#endif

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
#ifdef LINUX_TURNKEY_SOLUTION
extern INT32 a_tv_custom_set_viewing_data_accepted(BOOL b_accept);
extern BOOL a_tv_custom_get_viewing_data_accepted(VOID);
INT32 a_tv_custom_set_viewing_data_accepted_by_oobe_menu(BOOL b_accept);
BOOL a_tv_custom_get_viewing_data_accepted_by_oobe_menu(VOID);

INT32 a_tv_custom_set_model_name (VOID);
INT32 a_tv_custom_set_version (VOID);
INT32 a_tv_custom_set_serial_number (VOID);
INT32 a_tv_custom_set_tos (BOOL b_accept);
INT32 a_tv_custom_set_privacy (BOOL b_accept);
BOOL a_tv_custom_get_tos (VOID);
BOOL a_tv_custom_get_privacy (VOID);
INT32 a_tv_custom_set_conn_type (BOOL b_wired);
VOID a_tv_custom_set_lang(UINT16 ui2_lang);
VOID a_tv_custom_set_country(UINT16 ui2_country);
INT32 a_tv_custom_set_3rd_app_info(VOID);
BOOL a_tv_custom_get_viewing_data_show (VOID);
INT32 a_tv_custom_set_viewing_data_show (BOOL b_showed);

extern INT32 a_tv_custom_set_http_url_status (BOOL b_accept);
extern INT32 a_tv_custom_get_http_url_status (BOOL* pb_accept);
extern VOID a_tv_custom_clear_http_url_status(VOID);

#if 1 // APP_YAHOO6
BOOL a_tv_custom_get_y_fake_ui_status(VOID);
VOID a_tv_custom_set_y_fake_ui_status(BOOL b_show);
BOOL a_tv_custom_handle_widget_key(VOID);
#endif
#endif /* LINUX_TURNKEY_SOLUTION */

BOOL    a_tv_custom_is_3D_mode_playing(VOID);

#ifdef APP_CUSTOMER_DEF_LOCK_CHK_LOGIC
BOOL a_tv_custom_is_temp_unlock(VOID);
#endif

VOID a_tv_net_set_overscan_enable(BOOL b_overscan_enable);
BOOL a_tv_net_get_overscan_enable(VOID);

extern INT32 a_tv_net_custom_set_codeset(CHAR* s_codeset);
extern VOID  a_tv_net_custom_set_ir_mode(IR_MODE_E e_ir_mode);
extern VOID  a_tv_net_custom_update_ir_mode(VOID);
extern VOID  a_tv_net_custom_set_soundbar_flag(BOOL b_enable);
extern INT32 a_tv_net_custom_set_soundbar_codeset(CHAR* s_codeset);


#ifdef APP_TV_NET_CUSTOM_SET_OSD_STATUS
extern VOID a_tv_net_custom_set_OSD_status(UINT32  ui4_osd_status);
extern INT32 a_tv_net_custom_get_OSD_status (VOID);
#endif

#if defined(LINUX_TURNKEY_SOLUTION) && defined(TVIS_SUPPORT)
extern INT32 a_tv_custom_reload_tvis_wrapper(VOID);
#endif

/* set info banner visiable allow flag */
extern BOOL a_tv_custom_get_banner_visiable_allow(VOID);
extern VOID a_tv_custom_set_banner_visiable_allow(BOOL b_allow);

extern VOID a_tv_custom_clear_tos_version(VOID);
extern INT32 a_tv_custom_set_tos_version(VOID);

extern VOID a_tv_custom_stop_tvis();
extern VOID a_tv_custom_resume_tvis();

extern BOOL a_tv_custom_is_3rd_rw_ready(VOID);
extern INT32 a_tv_custom_launch_retail_mode_by_hotkey(VOID);
extern INT32 a_tv_custom_launch_link_by_hotkey(VOID);
extern INT32 a_tv_custom_launch_input_and_voldown_hotkey(VOID);
extern INT32 a_tv_rest_version(CHAR * restVerStr);
extern INT32 a_tv_exit_oobe(VOID);
#ifdef APP_IPCC_SUPPORT
extern INT32 a_tv_net_get_ipcc_property(APP_TV_NET_IPCC_PROPERTY* pt_ipcc);
#endif

//#ifdef APP_HOTKEY_WAKEUP_SUPPORT
#define         TV_HOTKEY_WAKEUP_START_AP_NONE        0x00
#define         TV_HOTKEY_WAKEUP_START_AP_WZD         0x01
#define         TV_HOTKEY_WAKEUP_START_AP_RETAILMODE  0x02

typedef enum
{
	WAKEUP_AP_NONE = 0,
	WAKEUP_AP_RETAILMODE_SET,
	WAKEUP_AP_RETAILMODE_CLEAN,
	WAKEUP_AP_WZD_SET,
    WAKEUP_AP_WZD_CLEAN,
}WAKEUP_START_AP_STATUS;

extern VOID a_tv_custom_set_hotkey_wakeup_active(WAKEUP_START_AP_STATUS e_ap_status);
extern VOID a_tv_custom_get_hotkey_wakeup_active(UINT8* pui1_ap_status);
extern BOOL a_tv_custom_is_YAHOO_hotkey(UINT32 ui4_key_code);
extern VOID a_tv_custom_hotkey_wakeup(UINT32 ui4_key_code);
extern VOID a_tv_custom_reset_hotkey_parameter();

typedef enum
{
	HOTKEY_NATIVE_APP = 0,
	HOTKEY_HTML5_APP,
	HOTKEY_YAHOO_APP,
	HOTKEY_UNKNOWN_APP,
	HOTKEY_INVALID,
}HOTKEY_APP_TYPE;

typedef struct
{
    HOTKEY_APP_TYPE     e_hotkey_app_type;
    CHAR*               s_launch_args;
}HOTKEY_APP_LAUNCH_INFO;

extern HOTKEY_APP_LAUNCH_INFO* a_tv_custom_get_APP_info_from_yahoo_XML(UINT32 ui4_key_code);
extern INT32 a_tv_custom_set_yahoo_hotkey_timer(BOOL      b_set_timer);
extern INT32 a_tv_custom_start_send_hotkey_Q_timer(UINT32 ui4_keycode);
extern BOOL a_tv_custom_get_yahoo_hotkey_timer(VOID);
extern INT32 a_tv_net_send_cmd(CHAR* ps_cmd);
extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);

#ifdef TVIS_SUPPORT
typedef enum _TVIS_MAIN_STATE_T
{
    TVIS_MAIN_STATE_NOT_STARTED = 0,
    TVIS_MAIN_STATE_STARTED,
    TVIS_MAIN_STATE_CRASHED,
}TVIS_MAIN_STATE_T;
extern TVIS_MAIN_STATE_T a_tv_custom_get_tvis_state(VOID);
extern VOID a_tv_custom_set_tvis_state(TVIS_MAIN_STATE_T e_state);
#endif
extern INT32 a_tv_set_env_to_mpool(CHAR* ps_name, CHAR* ps_value);
//#endif

//================================================================================================
typedef void TypParseFileSetVar(const char* pcVarName, unsigned int uiVal);
int AppTV_ParseDgbFile( char* pcFullFileName, TypParseFileSetVar* pFuncParseFileSetVar );

//================================================================================================
#define DBG_PRINT_CUR_LINE() do { \
    DBG_LOG_PRINT(("[xxx]{%s: %s: %d}\n", __FILE__, __FUNCTION__,__LINE__)); \
} while(0)
//================================================================================================
extern void a_tv_custom_pause( const char* pcStr, int iNum );
//================================================================================================


#endif /* _A_TV_CUSTOM_H_ */

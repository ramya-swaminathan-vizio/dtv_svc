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
 * $RCSfile: nav_cec_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the customization part of the CEC function.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT

#include "nav/nav_common.h"
#include "res/nav/nav_img.h"
#include "res/nav/cec2/nav_cec_view_rc.h"
#include "res/nav/cec2/nav_cec_view_mlm.h"
#include "res/app_util/config/a_cfg_custom.h"
//#include "wizard/a_wzd.h"
#include "wizard_anim/a_wzd.h"
#include "amb/a_amb.h"
#include "am/a_am.h"
#include "app_util/a_icl.h"
#include "bgm/a_bgm.h"
#include "c_os.h"
#include "menu2/menu_page_tree.h"

#include "nav/cec2/nav_cec.h"
#include "nav/cec2/otp/nav_cec_otp.h"
#include "nav/cec2/view/nav_cec_view.h"
#include "nav/cec2/osd_display/nav_cec_osd_display.h"
#include "nav/cec2/sys_standby/nav_cec_sys_standby.h"
#include "nav/cec2/deck_ctrl/nav_cec_deck_ctrl.h"
#include "nav/cec2/dmc/nav_cec_dmc.h"
#include "nav/cec2/otr/nav_cec_otr.h"
#include "nav/cec2/gdps/nav_cec_gdps.h"
#include "nav/cec2/routing_ctrl/nav_cec_routing_ctrl.h"
#include "nav/cec2/sys_info/nav_cec_sys_info.h"
#include "nav/cec2/pass_through/nav_cec_pass_through.h"
#include "nav/cec2/sac/nav_cec_sac.h"
#include "nav/cec2/arc/nav_cec_arc.h"
#include "nav/cec2/misc/nav_cec_misc.h"
#include "nav/input_src/input_src.h"
#include "nav/retail_mode/nav_retail_mode.h"

//#ifdef APP_ARC_ONLY
#include "nav/dialog/nav_dialog.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/nav/nav_mlm.h"
#include <unistd.h>
#include "wizard/wzd_view.h"
#include "c_cecm.h"
#include "c_os.h"
#include "x_os.h"
//#endif
#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#endif

#ifdef APP_WIZARD_CUSTOM_SUPPORT
#include "res/app_util/app_tv/a_tv_custom.h"
#include "wizard2/wzd.h"
#endif
#include "wdk/widget/wdk_widget.h"

#include "u_drv_cust.h"
#include "c_rm.h"

#include "app_util/a_cec.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "nav/revolt_info/revolt_info.h"
#include "nav/pwd_dlg/pwd_dlg.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "rest/a_rest_event.h"
#include "menu2/menu_device/menu_page_device_setting_no_wifi_remote.h"
#include "menu2/menu_device/menu_device.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/menu_common.h"
#ifdef SYS_TVAP_RPCAPI_3RD_SUPPORT
#include "app_util/a_icl_common.h"
#endif
#include "res/app_util/app_tv/a_tv_custom.h"

#include "res/nav/nav_dbg.h"
#ifdef SYS_MTKTVAPI_SUPPORT
#include "app_util/mtktvapi/a_mtktvapi_volctrl.h"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifdef APP_ARC_ONLY
typedef struct _NAV_CEC_CUSTOM_AMP_DLG_T
{
    HANDLE_T                h_dialog;
    HANDLE_T                h_canvas;
    HANDLE_T                h_hide_timer;
    HANDLE_T                h_show_timer;
    HANDLE_T                h_mute_timer;//delay mute TV Speaker.
    UINT32                  ui4_time_delay;
    UINT32                  ui4_mute_delay;//delay mute TV Speaker time.
    BOOL                    b_is_show;
    NAV_DIALOG_ID_T         e_dialog_id;

    UINT16                  ui2_icl_amp_nfy;
    UINT16                  ui2_icl_arc_only_nfy;
    UINT16                  ui2_icl_sac_status_nfy;
    UINT16                  ui2_cfg_tv_speaker_auto_nfy;
    UINT16                  ui2_cfg_digital_aud_out_nfy;

    UINT16                  ui2_icl_dev_pb1_nfy;
    UINT16                  ui2_icl_dev_pb2_nfy;
    UINT16                  ui2_icl_dev_pb3_nfy;
    UINT16                  ui2_icl_dev_rd1_nfy;
    UINT16                  ui2_icl_dev_rd2_nfy;
    UINT16                  ui2_icl_dev_rd3_nfy;
    UINT16                  ui2_icl_dev_tuner1_nfy;
    UINT16                  ui2_icl_dev_tuner2_nfy;
    UINT16                  ui2_icl_dev_tuner3_nfy;
    UINT16                  ui2_icl_dev_tuner4_nfy;
    UINT16                  ui2_aud_out_mask;
} NAV_CEC_CUSTOM_AMP_DLG_T;

#define NAV_CEC_AMP_PLUG_DLG_TIMER_DELAY     5000
#define NAV_CEC_CUSTOM_BRAND_NAME            "VIZIO"
#define NAV_CEC_GET_DEV_INFO_MAX_RETRY_CNT   1000
#define NAV_CEC_AMP_PLUG_MUTE_TV_DELAY       6000
#define NAV_CEC_AMP_PLUG_PROMOTE_MSG_SHOW    (2*60*1000)

#ifdef APP_TTS_SUPPORT
#define AUD_SPDIF_AUDIO_OUT_CUSTOM_PCM        (1)
static  UINT16  ui2_cfg_tts_switch = APP_CFG_NOTIFY_NULL_ID;
#endif
#ifndef APP_CUSTOMER_DEF_SOLE_HP_VOL
#define a_tv_set_mute_custom(p1)        TVR_NOT_EXIST
#define a_tv_get_mute_custom(p1)        TVR_NOT_EXIST
#endif

#define AUD_SPDIF_AUDIO_OUT_CUSTOM_AUTO         (0)
#define AUD_SPDIF_AUDIO_OUT_CUSTOM_DIGITAL      (2)

#ifndef RET_ON_ERR
#define RET_ON_ERR(_expr)  \
{ \
    INT32 expr = _expr; \
    if(expr != 0)\
    {\
        DBG_ERROR (("<NAV_CEC_CUSTOM> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
        return expr;\
    } \
}
#endif

#define NAV_CEC_AMP_PLUG_DLG_OFFSET_X         0

BOOL    b_edid_change_mute_process = FALSE;
BOOL	b_g_is_amp_plug_dlg_show = TRUE;
BOOL    b_last_5v_status = FALSE;
#endif


enum{
    NAV_CEC_BUF_IDX_ACT_SRC = 0,
    NAV_CEC_BUF_IDX_VIEW_ON,
    NAV_CEC_BUF_IDX_OTP,
    NAV_CEC_BUF_IDX_RT_CHG,
    NAV_CEC_BUF_IDX_RT_INFO,
    NAV_CEC_BUF_IDX_MAX
};

typedef struct _NAV_CEC_BGM_BUF_T
{
    HANDLE_T     h_nfy_mtx;                         /**< Buffer mutex. */
    UINT32       ui4_last_id;                       /**< Index for use in AP only. */
    CECM_NFY_T   at_nfy[NAV_CEC_BUF_IDX_MAX];       /**< A pair of buffer entry array. */
    UINT32       aui4_nfy_id[NAV_CEC_BUF_IDX_MAX];  /**< Determine whether a buffer is used. */
    BOOL         b_reved_get_menu_lang;
} NAV_CEC_BGM_BUF_T;

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

static NAV_CEC_BGM_BUF_T t_nav_cec_bgm_buf;
static cec_mw_nfy_fct pf_dispatch_nfy_fct;
static cec_mw_nfy_fct pf_default_nfy_fct;

static BOOL g_b_tv_speaker_auto = FALSE;
static BOOL g_b_icl_sac_val     = FALSE;
static BOOL g_b_tv_speaker_off  = FALSE;
static BOOL g_b_amp_nfy_show    = FALSE;
static BOOL g_b_power_on        = FALSE;
static BOOL g_b_msg_before_power_on = FALSE;
static BOOL amp_info_show_flag   = FALSE;
static BOOL not_arc_port_show_flag  = FALSE;

static WDK_TOAST_T     g_t_toast = {0};
UTF16_T         g_w2s_str_hdmiport[256] = {0};

BOOL g_b_toggle_play_pause = FALSE;
static HANDLE_T        h_hdmi_plug_timer;
static BOOL b_last_dts_support = FALSE;

static UINT8 g_b_digital_aud_val = 0;

#ifdef APP_TTS_SUPPORT
static BOOL g_b_acfg_tts_switch_val = FALSE;
#endif

static PASS_THROUGH_KEY_CODE_T _at_custom_pass_through_key_code_def [] = {
        {BTN_CUSTOM_1,      CECM_USER_CTRL_SELECT},         /* KEY_GROUP_CURSOR. */
        {BTN_CURSOR_UP,     CECM_USER_CTRL_UP},
        {BTN_CURSOR_DOWN,   CECM_USER_CTRL_DOWN},
        {BTN_CURSOR_LEFT,   CECM_USER_CTRL_LEFT},
        {BTN_CURSOR_RIGHT,  CECM_USER_CTRL_RIGHT},
        {BTN_SELECT,        CECM_USER_CTRL_SELECT},
        {BTN_EXIT,          CECM_USER_CTRL_EXIT},
        {BTN_RETURN,        CECM_USER_CTRL_EXIT},
        {BTN_STOP,          CECM_USER_CTRL_STOP},
        {BTN_PLAY,          CECM_USER_CTRL_PLAY},
        {BTN_PAUSE,         CECM_USER_CTRL_PAUSE},
        {BTN_PLAY_PAUSE,    CECM_USER_CTRL_PAUSE},
        {BTN_FR,            CECM_USER_CTRL_REWIND},
        {BTN_FF,            CECM_USER_CTRL_FAST_FORDWARD},
        {BTN_SF,            CECM_USER_CTRL_FORWARD},
        {BTN_SR,            CECM_USER_CTRL_BACKWARD},
        {BTN_RECORD,        CECM_USER_CTRL_RECORD},
};

NAV_CEC_PASS_THROUGH_CUSTOM_T t_pass_through_custom;
static INT32 _nav_cec_set_mute (BOOL b_mute);
static VOID _hdmi_plug_timer_nfy(HANDLE_T  h_timer, VOID*  pv_tag);

extern INT32 nav_cec_set_earc_status(BOOL b_arcStatus);

extern void _cec_hot_plug_dev_status_update(UINT16  ui2_port_id, BOOL  b_5v_status);

extern BOOL rest_notify_flag;

extern CEC_SB_VNDR_INFO amp_vndr_info;

#ifdef APP_ARC_ONLY
static NAV_CEC_CUSTOM_AMP_DLG_T       t_g_nav_cec_custom_amp_dlg = {0};
static INT32 _nav_cec_custom_amp_plug_dlg_init(VOID);
static VOID a_tv_set_mute_fct(VOID*  pv_tag1, VOID*  pv_tag2, VOID*  pv_tag3);
#endif

// for new feature Sound Bar Control (MVP-2686, MVV-6233, MVD-197)
BOOL b_SoundBarDbgLevel = FALSE;

static UINT8  spd_info_port0 [30] = {0};
static UINT8  spd_info_port1 [30] = {0};
static UINT8  spd_info_port2 [30] = {0};
static UINT8  spd_info_port3 [30] = {0};
static UINT8  spd_info_first [30] = {0};

//
//****************************************************************************************
//

#define NAV_CEC_HDMI1    1
#define NAV_CEC_HDMI2    2
#define NAV_CEC_HDMI3    3
#define NAV_CEC_HDMI4    4

/*-----------------------------------------------------------------------------
                    private function implementation
 ----------------------------------------------------------------------------*/

static VOID _nav_cec_custom_Dbg_init(VOID)
{
    char acFilePath[128] = "/data/tkSB.print";

    // Check file should exist...
    if ( access(acFilePath, F_OK) == 0 )
    {
        //printf("File(%s) exit \n", acFilePath);
        DBG_LOG_PRINT(("File(%s) exit: Turn on Sound-Bar Debug \n", acFilePath));
        b_SoundBarDbgLevel = 1;
    }
    else
    {
        //printf("File(%s) Not exit!\n", acFilePath);
    }
}


#ifdef APP_ARC_ONLY
 /*-----------------------------------------------------------------------------
  * Name:
  * 	 _nav_cec_custom_amp_plug_dlg_hide
  * Description:
  * 	 hide UI.
  * Input arguments:
  * 	 None
  * Output arguments
  * 	 None
  * Returns
  * 	 NAVR_OK	 Successful
  * 	 Others 	 Fail
  *---------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_amp_plug_dlg_hide (VOID)
{
    INT32					  		i4_ret = NAVR_OK;
    NAV_CEC_CUSTOM_AMP_DLG_T*	    pt_this = &t_g_nav_cec_custom_amp_dlg;

    if (pt_this->b_is_show == FALSE)
    {
        return NAVR_NO_ACTION;
    }

    i4_ret = nav_dialog_hide();
    RET_ON_ERR(i4_ret);

    pt_this->b_is_show = FALSE;
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);

    nav_return_activation(NAV_COMP_ID_DIALOG);

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
  * Name:
  * 	 _nav_cec_custom_amp_plug_dlg_hide_timer_fct
  * Description:
  * 	 nav amp/audio plugin detection dialog hide timer notify
  * Input arguments:
  * 	 h_timer
  * 	 pv_tag
  * Output arguments:
  * 	 None
  * Returns:
  * 	 None
  *---------------------------------------------------------------------------*/
static VOID _nav_cec_custom_amp_plug_dlg_hide_timer_fct(VOID*    pv_tag1,
                                                        VOID*    pv_tag2,
                                                        VOID*    pv_tag3)
{
    NAV_CEC_CUSTOM_AMP_DLG_T*    pt_this = &t_g_nav_cec_custom_amp_dlg;

    nav_hide_component(NAV_COMP_ID_DIALOG);

    _nav_cec_custom_amp_plug_dlg_hide();
    c_timer_stop(pt_this->h_hide_timer);
    return;
}
 /*-----------------------------------------------------------------------------
  * Name:
  * 	 _nav_cec_custom_amp_plug_dlg_hide_timer_nfy
  * Description:
  * 	 nav usb plugin detection dialog hide timer notify
  * Input arguments:
  * 	 h_timer
  * 	 pv_tag
  * Output arguments:
  * 	 None
  * Returns:
  * 	 None
  *---------------------------------------------------------------------------*/
static VOID _nav_cec_custom_amp_plug_dlg_hide_timer_nfy(HANDLE_T    h_timer,
                                                        VOID*       pv_tag)
{
    nav_request_context_switch(_nav_cec_custom_amp_plug_dlg_hide_timer_fct, NULL, NULL, NULL);

    return;
}
 /*-----------------------------------------------------------------------------
  * Name:
  * 	 _nav_cec_custom_amp_plug_dlg_hide_timer_start
  * Description:
  * 	 start nav amp/audio plugin detection dialog timer
  * Input arguments:
  * 	 None
  * Output arguments:
  * 	 None
  * Returns:
  * 	 NAVR_OK	Successful
  * 	 Others 	 Fail
  *---------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_amp_plug_dlg_hide_timer_start(VOID)
{
    INT32						 i4_ret = NAVR_OK;
    NAV_CEC_CUSTOM_AMP_DLG_T*		 pt_this = &t_g_nav_cec_custom_amp_dlg;

    if (NULL_HANDLE != pt_this->h_hide_timer)
    {
        i4_ret = c_timer_start(pt_this->h_hide_timer,
                               pt_this->ui4_time_delay,
                               X_TIMER_FLAG_ONCE,
                               _nav_cec_custom_amp_plug_dlg_hide_timer_nfy,
                               NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
  * Name:
  * 	 _nav_cec_custom_amp_plug_dlg_default_msg_proc
  * Description:
  *
  * Input arguments:
  * 	 None
  * Output arguments:
  * 	 None
  * Returns:
  * 	 NAVR_OK	 Successful
  * 	 Others 	 Fail
  *---------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_amp_plug_dlg_default_msg_proc(HANDLE_T  h_widget,
                                                           UINT32    ui4_msg,
                                                           VOID*     pv_param1,
                                                           VOID*     pv_param2)
{
    INT32  i4_ret = NAVR_OK;

    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            i4_ret = _nav_cec_custom_amp_plug_dlg_hide_timer_start();
            RET_ON_ERR(i4_ret);

            switch(ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                case BTN_SELECT:
                    break;

                case BTN_EXIT:
                {
                    nav_hide_component(NAV_COMP_ID_DIALOG);
                    _nav_cec_custom_amp_plug_dlg_hide();
                    break;
                }

                default:
                    nav_rcu_key_handler(ui4_keycode);
                    return NAVR_OK;
            }
            break;
        }

        default:
            break;
    }

    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               pv_param1,
                                               pv_param2);
}
  /*----------------------------------------------------------------------------
  * Name: nav_cec_custom_amp_plug_dlg_is_need_show
  *
  * Description:
  *
  * Inputs:
  *
  * Outputs:
  *
  * Returns:
  *
  ----------------------------------------------------------------------------*/
  BOOL nav_cec_custom_amp_plug_dlg_is_need_show()
  {
     INT32                           i4_ret = NAVR_OK;
     CECM_CTRL_T                     t_cecmCtrl;
     CECM_DEV_T                      t_devInfo;
     UINT32                          ui4_retry_cnt = 0;
     UINT16                          ui2_aud_sys_pa;
     UINT8                           ui1_port_id;

     ui2_aud_sys_pa = c_cecm_get_pa_by_la(nav_cec_get_mw_handle (),CECM_LOG_ADDR_AUD_SYS);
     if ((ui2_aud_sys_pa==CECM_INV_PA) || (ui2_aud_sys_pa==CECM_LOG_ADDR_MAX))
     {
        DBG_ERROR(("\r\n[####Cannot get PA of AMP:%s:%s:%d:ui2_aud_sys_pa=%d]\r\n", __FILE__, __FUNCTION__, __LINE__, ui2_aud_sys_pa));
        return FALSE;
     }
     ui1_port_id =(UINT8)((ui2_aud_sys_pa>>12) -1);

     if (ui1_port_id != NAV_CEC_SUPPORT_ARC_PORT_ID)
     {
         DBG_ERROR(("\r\n[#### NOT NAV_CEC_SUPPORT_ARC_PORT_ID:%s:%s:%d:ui1_port_id=%d]\r\n", __FILE__, __FUNCTION__, __LINE__, ui1_port_id));
         return FALSE;
     }

     for(ui4_retry_cnt=0;ui4_retry_cnt<NAV_CEC_GET_DEV_INFO_MAX_RETRY_CNT;ui4_retry_cnt++)
     {
         c_memset ((void*)&t_devInfo, 0, sizeof (CECM_DEV_T));
         t_cecmCtrl.b_sync = FALSE;

         i4_ret = c_cecm_get_dev_info_by_la (
                                     nav_cec_get_mw_handle(),
                                     CECM_LOG_ADDR_AUD_SYS,
                                     &t_cecmCtrl,
                                     &t_devInfo);

         if (i4_ret != CECMR_OK)
         {
             DBG_ERROR(("\r\n[####Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
             return FALSE;
         }
         else
         {
             if(c_uc_w2s_strlen(t_devInfo.aw2_osd_name) > 0)
             {
                 return TRUE;
             }
             else
             {
                 c_thread_delay(10);
                 continue;
             }
         }

     }

     return FALSE;
 }
 /*----------------------------------------------------------------------------
 * Name: nav_cec_custom_amp_plug_dlg_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 INT32 nav_cec_custom_amp_plug_dlg_show()
{
    INT32   						i4_ret = NAVR_OK;
    GL_POINT_T 						t_begin_offset = {NAV_CEC_AMP_PLUG_DLG_OFFSET_X, 0};
	NAV_CEC_CUSTOM_AMP_DLG_T*		pt_this = &t_g_nav_cec_custom_amp_dlg;
	CECM_CTRL_T 					t_cecmCtrl;
	CECM_DEV_T 						t_devInfo;
	CHAR							s_osd_name[CECM_OSD_NAME_SIZE] = {0};
	UINT32							ui4_retry_cnt = 0;
	UINT16                     		ui2_msg_key = MLM_NAV_KEY_CEC_AUDIO_PLUG_PROMOTE_MSG;

    i4_ret = _nav_cec_custom_amp_plug_dlg_init();
	RET_ON_ERR(i4_ret);

	for(ui4_retry_cnt=0;ui4_retry_cnt<NAV_CEC_GET_DEV_INFO_MAX_RETRY_CNT;ui4_retry_cnt++)
	{
		c_memset ((void*)&t_devInfo, 0, sizeof (CECM_DEV_T));
		t_cecmCtrl.b_sync = FALSE;

		i4_ret = c_cecm_get_dev_info_by_la (
									nav_cec_get_mw_handle(),
									CECM_LOG_ADDR_AUD_SYS,
									&t_cecmCtrl,
									&t_devInfo);

		if (i4_ret != CECMR_OK)
		{
			DBG_ERROR(("\r\n[####Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
		}
		else
		{
			if(c_uc_w2s_strlen(t_devInfo.aw2_osd_name) > 0)
			{
				c_uc_w2s_to_ps(t_devInfo.aw2_osd_name,s_osd_name,CECM_OSD_NAME_SIZE);
				DBG_INFO(("\r\n[#####:%s:%s:%d:s_osd_name=%s]\r\n", __FILE__, __FUNCTION__, __LINE__,s_osd_name));

				if(c_strstr(s_osd_name,NAV_CEC_CUSTOM_BRAND_NAME)!=NULL)
				{
					ui2_msg_key = MLM_NAV_KEY_CEC_AMP_PLUG_PROMOTE_MSG;
				}
				else
				{
					ui2_msg_key = MLM_NAV_KEY_CEC_AUDIO_PLUG_PROMOTE_MSG;
				}

				break;
			}
			else
			{
				c_thread_delay(10);
				continue;
			}
		}

	}
    /* show disconnected dialog */
    i4_ret = nav_dialog_prompt_only_msg_dialog(
                        NAV_DIALOG_ID_AMP_PLG_DLG,
						MLM_NAV_TEXT(nav_get_mlm_lang_id(), ui2_msg_key),
                        NULL,
                        &t_begin_offset,
                        _nav_cec_custom_amp_plug_dlg_default_msg_proc);
    RET_ON_ERR(i4_ret);

	b_g_is_amp_plug_dlg_show = TRUE;

    i4_ret = nav_dialog_stop_hide_timer();
    RET_ON_ERR(i4_ret);

    i4_ret = _nav_cec_custom_amp_plug_dlg_hide_timer_start();
    RET_ON_ERR(i4_ret);

	pt_this->b_is_show = TRUE;

	return NAVR_OK;
}
 /*-----------------------------------------------------------------------------
 * Name
 *      _nav_cec_custom_amp_plug_dlg_init
 * Description:
 *      amp/audio plugin detection view initialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_amp_plug_dlg_init(VOID)
{
    INT32                          i4_ret = NAVR_OK;
    NAV_CEC_CUSTOM_AMP_DLG_T*      pt_this = &t_g_nav_cec_custom_amp_dlg;

    i4_ret = c_timer_create(&pt_this->h_hide_timer);
    RET_ON_ERR(i4_ret);

    pt_this->ui4_time_delay = NAV_CEC_AMP_PLUG_DLG_TIMER_DELAY;
    pt_this->b_is_show = FALSE;

    return NAVR_OK;
}

 /*----------------------------------------------------------------------------
  * Name: _nav_cec_custom_arc_only_setting_nfy_hdlr
  *
  * Description:_nav_cec_custom_arc_only_setting_nfy_hdlr
  *
  * Inputs:
  *
  * Outputs:
  *
  * Returns:
  *
  ----------------------------------------------------------------------------*/
 static VOID _nav_cec_custom_arc_only_setting_nfy_hdlr(VOID*                pv_tag1,
                                         VOID*                       pv_tag2,
                                         VOID*                       pv_tag3)
 {
     if(nav_cec_custom_amp_plug_dlg_is_need_show())
     {
         DBG_INFO(("\n####%s(%d)nav_cec_custom_amp_plug_dlg_is_need_show\n",__FUNCTION__,__LINE__));
         //nav_cec_custom_amp_plug_dlg_show();
     }
 }
 /*----------------------------------------------------------------------------
  * Name: _nav_cec_custom_arc_only_setting_nfy_func
  *
  * Description:
  *
  * Inputs:
  *
  * Outputs:
  *
  * Returns:
  *
  ----------------------------------------------------------------------------*/
 static INT32 _nav_cec_custom_arc_only_setting_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
 {
     ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
     ICL_RECID_TYPE  e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);
     SIZE_T         z_size ;
     INT32          i4_ret = NAVR_OK;
     UINT8          ui1_icl_mask;
     UINT8          ui1_arc_only_status;

     if (e_grp_id != ICL_GRPID_CEC)
     {
         return NAVR_OK;
     }
     if(e_rec_id != ICL_RECID_CEC_ARC_ONLY)
     {
         return NAVR_OK;
     }
     DBG_INFO(("\n####%s(%d)--<CEC> _nav_cec_custom_arc_only_setting_nfy_func --\n",__FUNCTION__,__LINE__));
     ui1_icl_mask = ICL_RECID_CEC_ARC_ONLY;
     z_size = ICL_RECID_CEC_ARC_ONLY_SIZE;

     i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CEC, ui1_icl_mask),
                        &ui1_arc_only_status,
                        &z_size);

     if (i4_ret != ICLR_OK)
     {
         return NAVR_OK;
     }

     if(1 == ui1_arc_only_status)
     {
         nav_request_context_switch(_nav_cec_custom_arc_only_setting_nfy_hdlr,NULL,NULL,NULL);
     }

     return i4_ret;
 }

static VOID _do_show_cec_toast_view_timer(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    NAV_CEC_CUSTOM_AMP_DLG_T*		 pt_this = &t_g_nav_cec_custom_amp_dlg;

    g_b_amp_nfy_show = FALSE;

    c_timer_stop(pt_this->h_show_timer);
    c_timer_delete(pt_this->h_show_timer);
    pt_this->h_show_timer = NULL_HANDLE;
    a_tv_custom_set_banner_visiable_allow(TRUE);

}

static VOID _timer_show_cec_toast_view_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    nav_request_context_switch(_do_show_cec_toast_view_timer,pv_tag, NULL,NULL);
}

static INT32 _cec_info_send_string_to_nav(WDK_TOAST_T *pt_toast)
{
    WDK_TOAST_T* pt_toast_cpy = NULL;
    UTF16_T* p_w2s_str = (UTF16_T*)pt_toast->style.style_4.w2s_str;

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));

    if (NULL == pt_toast_cpy)
    {
        DBG_INFO(("NULL == pt_toast_cpy!!\n"));
        return -1;
    }

    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)pt_toast, sizeof(WDK_TOAST_T));

    if (pt_toast->e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[128]  = {0};
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 127);

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;

        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)pt_toast->style.style_4.w2s_str, len);
    }

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);
#ifdef APP_TTS_SUPPORT
    a_app_tts_play(p_w2s_str, c_uc_w2s_strlen(p_w2s_str));
#endif
    return NAVR_OK;
}

UINT8 cec_get_mlm_settings_lang_id(VOID)
{
    ISO_639_LANG_T s639_lang;
    UINT8          ui1_lang_id = 0;
    INT32          i4_ret;

    ui1_lang_id = 0;

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if (i4_ret == 0)
    {
        ui1_lang_id = mlm_settings_s639_to_langidx(s639_lang);
    }

    return ui1_lang_id;
}

static INT32 _nav_cec_custom_w2s_str_replace(
                UTF16_T*  w2s_dst,
                SIZE_T    t_dst_len,
                UTF16_T*  w2s_src[],
                UINT32    ui4_src_sz
                )
{
    if (w2s_dst == NULL ||
        t_dst_len == 0 ||
        w2s_src == NULL ||
        ui4_src_sz == 0
        )
    {
        DBG_LOG_PRINT(("{%s,%d} parameters err. \r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    UTF16_T* buffer = c_mem_alloc(sizeof(UTF16_T)*t_dst_len);
    if (buffer == NULL) {
        DBG_LOG_PRINT(("{%s,%d} c_mem_alloc() failed. \r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }
    c_memset(buffer, 0, sizeof(UTF16_T)*t_dst_len);

    UTF16_T*    p_w2s_dst = w2s_dst;
    UTF16_T     w2s_pattern[] = L"%s";
    SIZE_T      t_pattern_len = c_uc_w2s_strlen(w2s_pattern);
    SIZE_T      t_rest_len = t_dst_len-1;

    for (UINT32 ui4_src_idx = 0; ui4_src_idx < ui4_src_sz; ++ui4_src_idx)
    {
        UTF16_T*    p_w2s_pattern = &w2s_pattern[0];
        INT32       i4_idx = 0;

        while (*(p_w2s_dst+i4_idx) != *p_w2s_pattern)
        {
            if (*(p_w2s_dst+i4_idx) == 0)
                break;
            i4_idx++;
        }
        while (*(p_w2s_dst+i4_idx) == *p_w2s_pattern)
        {
            if (*(p_w2s_dst+i4_idx) ==0)
                break;
            p_w2s_pattern++;
            i4_idx++;
        }

        if (*p_w2s_pattern == 0)  // find  pattern string from  dst string
        {
            if ((i4_idx - t_pattern_len) > 0)
            {
                if ((i4_idx - t_pattern_len) > t_rest_len) {
                    c_mem_free(buffer);
                    return NAVR_FAIL;
                }
                c_uc_w2s_strncat(buffer, p_w2s_dst, i4_idx - t_pattern_len);
                t_rest_len -= (i4_idx - t_pattern_len);
            }

            p_w2s_dst += i4_idx;

            SIZE_T  t_src_len = c_uc_w2s_strlen(w2s_src[ui4_src_idx]);
            if (t_src_len > t_rest_len) {
                c_mem_free(buffer);
                return NAVR_FAIL;
            }
            c_uc_w2s_strncat(buffer, w2s_src[ui4_src_idx], t_src_len);
            t_rest_len -= t_src_len;
        }
    }

    if (p_w2s_dst != w2s_dst)
    {
        SIZE_T  t_dst_r_len = c_uc_w2s_strlen(p_w2s_dst);
        if (t_dst_r_len > t_rest_len) {
            c_mem_free(buffer);
            return NAVR_FAIL;
        }
        c_uc_w2s_strncat(buffer, p_w2s_dst, t_dst_r_len);
        c_uc_w2s_strcpy(w2s_dst, buffer);
        c_mem_free(buffer);
        return NAVR_OK;
    }
    else
    {
        c_mem_free(buffer);
        return NAVR_FAIL;
    }

}

static VOID _nav_cec_custom_dev_toast_cb_fct(
    WDK_TOAST_CB_EVENT  cb_event,
    WDK_TOAST_CB_REASON cb_reason,
    VOID* pv_data
    )
{
    if (cb_event == TOAST_EVENT_KEY &&
        cb_reason == TOAST_REASON_KEY_DOWN)
    {
        nav_hide_component(NAV_COMP_ID_REVOLT_INFO);
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_cec_custom_dev_nfy_func
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_dev_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE  e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);
    SIZE_T          z_size ;
    INT32           i4_ret = NAVR_OK;
    UINT8           ui1_dev_status = 0;
    UINT8           ui1_ces_func = 0;
    WDK_TOAST_T     t_toast = {0};
    CEC_DEV_LST_T   t_lst;
    CHAR            dev_osdname[64+1]={0};
    CHAR            dev_hdmiport[64+1]={0};
    UTF16_T         w2s_str_hdmiport[256] = {0};
    UTF16_T         w2s_string[64+1]  = {0};
    BOOL            b_allow_to_show = FALSE;
    CEC_DEV_INFO_T* pt_cec_dev_info = NULL;
    UINT8           ui1_la;

    if (e_grp_id != ICL_GRPID_CEC)
    {
        DBG_INFO(("%s,%d #### <CEC> get e_grp_id fail  \r\n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }
    if(e_rec_id != ICL_RECID_CEC_PB1_PLUG && e_rec_id != ICL_RECID_CEC_PB2_PLUG &&
       e_rec_id != ICL_RECID_CEC_PB3_PLUG && e_rec_id != ICL_RECID_CEC_RD1_PLUG &&
       e_rec_id != ICL_RECID_CEC_RD2_PLUG && e_rec_id != ICL_RECID_CEC_RD3_PLUG &&
       e_rec_id != ICL_RECID_CEC_TUNER1_PLUG && e_rec_id != ICL_RECID_CEC_TUNER2_PLUG &&
        e_rec_id != ICL_RECID_CEC_TUNER3_PLUG && e_rec_id != ICL_RECID_CEC_TUNER4_PLUG &&
        e_rec_id != ICL_RECID_CEC_AUD_PLUG)

    {
        DBG_INFO(("%s,%d #### <CEC> get e_rec_id fail \r\n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }

    z_size = ICL_RECID_CEC_DEV_PLUG_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CEC, e_rec_id),
                       &ui1_dev_status,
                       &z_size);

    if (i4_ret != ICLR_OK)
    {
        DBG_INFO(("%s,%d #### icl get fail \r\n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }

    switch (e_rec_id)
    {
        case ICL_RECID_CEC_RD1_PLUG :
            ui1_la = CECM_LOG_ADDR_REC_DEV_1;
            break;
        case ICL_RECID_CEC_RD2_PLUG :
            ui1_la = CECM_LOG_ADDR_REC_DEV_2;
            break;
        case ICL_RECID_CEC_TUNER1_PLUG :
            ui1_la = CECM_LOG_ADDR_TUNER_1;
            break;
        case ICL_RECID_CEC_PB1_PLUG :
            ui1_la = CECM_LOG_ADDR_PLAYBACK_DEV_1;
            break;
        case ICL_RECID_CEC_TUNER2_PLUG :
            ui1_la = CECM_LOG_ADDR_TUNER_2;
            break;
        case ICL_RECID_CEC_TUNER3_PLUG :
            ui1_la = CECM_LOG_ADDR_TUNER_3;
            break;
        case ICL_RECID_CEC_PB2_PLUG :
            ui1_la = CECM_LOG_ADDR_PLAYBACK_DEV_2;
            break;
        case ICL_RECID_CEC_RD3_PLUG :
            ui1_la = CECM_LOG_ADDR_REC_DEV_3;
            break;
        case ICL_RECID_CEC_TUNER4_PLUG :
            ui1_la = CECM_LOG_ADDR_TUNER_4;
            break;
        case ICL_RECID_CEC_PB3_PLUG :
            ui1_la = CECM_LOG_ADDR_PLAYBACK_DEV_3;
            break;
        case ICL_RECID_CEC_AUD_PLUG:
            ui1_la = CECM_LOG_ADDR_AUD_SYS;
            break;
        default:
            break;
    }

    a_cfg_get_cec_func (&ui1_ces_func);
    b_allow_to_show = cec_custom_allow_visible();
    DBG_LOG_PRINT(("#### %s(%d) func=%d status=%d allow=%d \n", __FILE__, __LINE__ ,ui1_ces_func, ui1_dev_status, b_allow_to_show));

    if ((ui1_dev_status == ICL_CEC_DEV_PLUG)&&
       ((ui1_ces_func == APP_CFG_CEC_ARC_ONLY) || (ui1_ces_func == APP_CFG_CEC_ON)))
    {
        c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
        a_cec_get_dev_list(nav_cec_get_mw_handle(), &t_lst, CEC_SORT_TYPE_DEFAULT);

        if (t_lst.ui1_dev_num != 0)
        {
            for (UINT8 ui1_idx = 0; ui1_idx < t_lst.ui1_dev_num; ++ui1_idx)
            {
                if (t_lst.at_dev_info[ui1_idx].e_la == ui1_la) {
                    pt_cec_dev_info = &t_lst.at_dev_info[ui1_idx];
                    break;
                }
            }

            if (pt_cec_dev_info == NULL)
            {
                DBG_INFO(("%s,%d #### <CEC> cann't get cec dev info \r\n",__FUNCTION__,__LINE__));
                return NAVR_FAIL;
            }

            c_uc_w2s_to_ps(pt_cec_dev_info->pw2s_hdmi_port, dev_hdmiport, 32);
            DBG_LOG_PRINT(("%s,%d #### <CEC> hdmi= %s \r\n",__FUNCTION__,__LINE__,dev_hdmiport));

            if(TRUE == rest_notify_flag)
            {
                rest_notify_flag = FALSE;

                if(c_strncmp(dev_hdmiport, "HDMI-1", 6) == 0)
                {
                    rest_event_notify("system/input/name", 1,"hdmi1");
                    c_thread_delay(300);
                    rest_event_notify("system/input/cec", 0, "hdmi1");
                    c_thread_delay(300);
                    rest_event_notify("system/input/enable", 1, "hdmi1");
                }
                else if(c_strncmp(dev_hdmiport, "HDMI-2", 6) == 0)
                {
                    rest_event_notify("system/input/name", 1,"hdmi2");
                    c_thread_delay(300);
                    rest_event_notify("system/input/cec", 0, "hdmi2");
                    c_thread_delay(300);
                    rest_event_notify("system/input/enable", 1, "hdmi2");
                }
                else if(c_strncmp(dev_hdmiport, "HDMI-3", 6) == 0)
                {
                    rest_event_notify("system/input/name", 1,"hdmi3");
                    c_thread_delay(300);
                    rest_event_notify("system/input/cec", 0, "hdmi3");
                    c_thread_delay(300);
                    rest_event_notify("system/input/enable", 1, "hdmi3");
                }
                else if(c_strncmp(dev_hdmiport, "HDMI-4", 6) == 0)
                {
                    rest_event_notify("system/input/name", 1,"hdmi4");
                    c_thread_delay(300);
                    rest_event_notify("system/input/cec", 0, "hdmi4");
                    c_thread_delay(300);
                    rest_event_notify("system/input/enable", 1, "hdmi4");
                }
            }

            if(TRUE == not_arc_port_show_flag)
            {
                NAV_CEC_LOG_I("not arc port have showed \r\n");
                return NAVR_OK;
            }
            else
            {
                not_arc_port_show_flag = TRUE;
            }

            if (pt_cec_dev_info->e_la == CECM_LOG_ADDR_AUD_SYS)
            {
                if(((pt_cec_dev_info->ui2_pa >> 12)-1) != NAV_CEC_SUPPORT_ARC_PORT_ID)
                {
                    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
                    t_toast.e_toast_style  = WDK_WARNING_TOAST;
                    t_toast.e_string_style = WDK_STRING_STRING;
                    UTF16_T* w2s_src[] = {pt_cec_dev_info->pw2s_hdmi_port, pt_cec_dev_info->aw2_osd_name};
                    c_uc_w2s_strncpy(w2s_str_hdmiport,
                                     MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_NO_ARC_HDMI_PORT_MSG),
                                     256);
                    i4_ret = _nav_cec_custom_w2s_str_replace(w2s_str_hdmiport,256,w2s_src,2);
                    NAV_CHK_FAIL(i4_ret);

                    a_revolt_info_set_timeout(NAV_CEC_AMP_PLUG_PROMOTE_MSG_SHOW);
                    t_toast.pf_cb = _nav_cec_custom_dev_toast_cb_fct;
                    t_toast.style.style_4.w2s_str = (VOID*)w2s_str_hdmiport;
                    DBG_LOG_PRINT(("#### %s(%d) g_b_power_on=%d \n", __FILE__, __LINE__, g_b_power_on ));

                    if(!g_b_power_on || !b_allow_to_show)
                    {
                        DBG_LOG_PRINT(("#### %s(%d) delay show amp info \n", __FILE__, __LINE__ ));
                        g_b_msg_before_power_on = TRUE;
                        c_memset((VOID*)&g_t_toast, 0x0, sizeof(WDK_TOAST_T));
                        c_uc_w2s_strncpy(g_w2s_str_hdmiport, w2s_str_hdmiport, 256);
                        return i4_ret;
                    }
                    _cec_info_send_string_to_nav(&t_toast);
                }

            }
        }
    }
    return i4_ret;
}


static VOID _nav_cec_custom_amp_toast_cb_fct(
    WDK_TOAST_CB_EVENT  cb_event,
    WDK_TOAST_CB_REASON cb_reason,
    VOID* pv_data
    )
{
    NAV_CEC_CUSTOM_AMP_DLG_T* pt_this = &t_g_nav_cec_custom_amp_dlg;

    if (cb_event == TOAST_EVENT_KEY &&
        cb_reason == TOAST_REASON_KEY_DOWN)
    {
        nav_hide_component(NAV_COMP_ID_REVOLT_INFO);
        g_b_amp_nfy_show = FALSE;
        a_tv_custom_set_banner_visiable_allow(TRUE);

    }
    else if (cb_event == TOAST_EVENT_HIDE)
    {
        if (pt_this->h_show_timer != NULL_HANDLE)
        {
            c_timer_stop(pt_this->h_show_timer);
            c_timer_delete(pt_this->h_show_timer);
            pt_this->h_show_timer = NULL_HANDLE;
        }
        g_b_amp_nfy_show = FALSE;
        a_tv_custom_set_banner_visiable_allow(TRUE);
    }

}

static VOID _nav_cec_custom_amp_nfy_fct(
    VOID* pv_tag1,
    VOID* pv_tag2,
    VOID* pv_tag3
    )
{
    INT32           i4_ret;
    WDK_TOAST_T     t_toast = {0};
	UTF16_T         w2s_tmp_str[256] = {0};
    UINT16          ui2_msg_key = MLM_NAV_KEY_CEC_AUDIO_PLUG_PROMOTE_MSG;
    NAV_CEC_CUSTOM_AMP_DLG_T*  pt_this = &t_g_nav_cec_custom_amp_dlg;

    do {
        CECM_DEV_T  t_dev_info;
        CECM_CTRL_T t_cecm_ctrl;
        CHAR		s_osd_name[CECM_OSD_NAME_SIZE] = {0};

        c_memset(&t_dev_info, 0, sizeof(CECM_DEV_T));
        t_cecm_ctrl.b_sync = FALSE;

        i4_ret = c_cecm_get_dev_info_by_la(nav_cec_get_mw_handle(),
                                  CECM_LOG_ADDR_AUD_SYS,
                                  &t_cecm_ctrl,
                                  &t_dev_info);

        if (i4_ret == CECR_OK && c_uc_w2s_strlen(t_dev_info.aw2_osd_name) > 0)
        {
            c_uc_w2s_to_ps(t_dev_info.aw2_osd_name, s_osd_name, CECM_OSD_NAME_SIZE);

            if(c_strstr(s_osd_name, NAV_CEC_CUSTOM_BRAND_NAME) != NULL) {
                ui2_msg_key = MLM_NAV_KEY_CEC_AMP_PLUG_PROMOTE_MSG;
            } else {
                ui2_msg_key = MLM_NAV_KEY_CEC_AUDIO_PLUG_PROMOTE_MSG;
            }
        }
    }while(0);

    c_uc_w2s_strcpy(w2s_tmp_str, MLM_NAV_TEXT(nav_get_mlm_lang_id(), ui2_msg_key));
    c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_WARNING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.pf_cb = _nav_cec_custom_amp_toast_cb_fct;
    t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;
    a_revolt_info_set_timeout(NAV_CEC_AMP_PLUG_PROMOTE_MSG_SHOW);
    DBG_LOG_PRINT(("#### %s(%d) g_b_power_on=%d \n", __FILE__, __LINE__, g_b_power_on ));

    if(!g_b_power_on || !cec_custom_allow_visible())
    {
        DBG_LOG_PRINT(("#### %s(%d) delay show amp info \n", __FILE__, __LINE__ ));
        g_b_msg_before_power_on = TRUE;
        c_memset((VOID*)&g_t_toast, 0x0, sizeof(WDK_TOAST_T));
        c_uc_w2s_strncpy(g_w2s_str_hdmiport, w2s_tmp_str, 256);
        return;
    }

    if(!g_b_amp_nfy_show)
    {
        _cec_info_send_string_to_nav(&t_toast);
        g_b_amp_nfy_show = TRUE;
        a_tv_custom_set_banner_visiable_allow(FALSE);

        if (pt_this->h_show_timer == NULL_HANDLE && c_timer_create(&pt_this->h_show_timer) == OSR_OK)
        {
            c_timer_start(pt_this->h_show_timer,
                       NAV_CEC_AMP_PLUG_PROMOTE_MSG_SHOW,
                       X_TIMER_FLAG_ONCE,
                       _timer_show_cec_toast_view_fct,
                       NULL);
        }
        else
        {
            g_b_amp_nfy_show = FALSE;
            a_tv_custom_set_banner_visiable_allow(TRUE);
        }
    }
}

VOID nav_cec_custom_amp_nfy()
{
    nav_request_context_switch(_nav_cec_custom_amp_nfy_fct,NULL,NULL,NULL);
}

static VOID _nav_cec_custom_amp_nfy_thread (VOID*  pv_arg)
{
    INT32 i4_ret;
    CECM_DEV_T  t_dev_info;
    CECM_CTRL_T t_cecm_ctrl;

    for (INT32 iterator=0; iterator < 6; ++iterator)
    {
        c_memset(&t_dev_info, 0, sizeof(CECM_DEV_T));
        t_cecm_ctrl.b_sync = FALSE;
        c_thread_delay(500);

        i4_ret = c_cecm_get_dev_info_by_la(nav_cec_get_mw_handle(),
                                  CECM_LOG_ADDR_AUD_SYS,
                                  &t_cecm_ctrl,
                                  &t_dev_info);

        if ((i4_ret == CECR_OK && c_uc_w2s_strlen(t_dev_info.aw2_osd_name) > 0) ||
            (iterator == 5))
        {
            DBG_LOG_PRINT(("\n#### <CEC> {%s %d} -- iterator=%d --\n",__FUNCTION__,__LINE__,iterator));
            nav_request_context_switch(_nav_cec_custom_amp_nfy_fct,NULL,NULL,NULL);
            break;
        }
    }

    x_thread_exit();
}

/*----------------------------------------------------------------------------
 * Name: _nav_cec_custom_amp_nfy_func
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_amp_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
	ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE  e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);
    SIZE_T         z_size ;
    INT32          i4_ret = NAVR_OK;
    UINT8          ui1_icl_mask;
    UINT8          ui1_sac_status;
	UINT8 		   ui1_ces_func = 0;
	CHAR		   s_active_app[APP_NAME_MAX_LEN + 1] = {0};
	BOOL           b_allow_to_show = FALSE;
    NAV_CEC_CUSTOM_AMP_DLG_T*  pt_this = &t_g_nav_cec_custom_amp_dlg;

    if (ui2_nfy_id != pt_this->ui2_icl_amp_nfy)
    {
        return NAVR_OK;
    }
    if (e_grp_id != ICL_GRPID_CEC)
    {
        return NAVR_OK;
    }
	if(e_rec_id != ICL_RECID_CEC_AMP_PLUG)
	{
	    return NAVR_OK;
	}
    DBG_INFO(("\n####%s(%d)--<CEC> _nav_cec_custom_amp_nfy_func --\n",__FUNCTION__,__LINE__));
    ui1_icl_mask = ICL_RECID_CEC_AMP_PLUG;
    z_size = ICL_RECID_CEC_AMP_PLUG_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CEC, ui1_icl_mask),
                       &ui1_sac_status,
                       &z_size);

    if (i4_ret != ICLR_OK)
    {
        return NAVR_OK;
    }

    a_cfg_get_cec_func (&ui1_ces_func);

    b_allow_to_show = cec_custom_allow_visible();
    DBG_LOG_PRINT(("#### %s(%d) b_allow_to_show=%d \n", __FILE__, __LINE__, b_allow_to_show));

    if(b_allow_to_show)
    {
        if ((ui1_sac_status == ICL_CEC_AMP_PLUG) &&
            ((ui1_ces_func == APP_CFG_CEC_ARC_ONLY) || (ui1_ces_func == APP_CFG_CEC_ON)))
        {
            DBG_INFO(("\n####%s(%d)--<CEC> _nav_cec_custom_amp_nfy_func b_last_5v_status %d--\n",__FUNCTION__,__LINE__,b_last_5v_status));
            if(b_last_5v_status)  //if power cycle not show message every time
            {
                return NAVR_OK;
            }
            else
            {
                b_last_5v_status = TRUE;
            }
            DBG_INFO(("\n####%s(%d)--<CEC> ICL_CEC_AMP_PLUG --\n",__FUNCTION__,__LINE__));

    		a_am_get_active_app (s_active_app);

    		if(c_strcmp(s_active_app, WZD_NAME) == 0)
    		{
    			b_g_is_amp_plug_dlg_show = FALSE;
    			return NAVR_OK;
    		}

            if(TRUE == amp_info_show_flag)
            {
                NAV_CEC_LOG_I("amp info have showed \r\n");
                return NAVR_OK;
            }
            else
            {
                amp_info_show_flag = TRUE;
            }

            DBG_LOG_PRINT(("#### %s(%d) show info thread \n", __FILE__, __LINE__ ));
            HANDLE_T  h_amp_nfy_thread = NULL_HANDLE;
            i4_ret = x_thread_create(&h_amp_nfy_thread,
                             "h_amp_nfy_thread",
                             8192,
                             128,
                             _nav_cec_custom_amp_nfy_thread,
                             0,
                             NULL);
            NAV_LOG_ON_FAIL(i4_ret);
        }
    }
    return i4_ret;
}

#ifdef APP_TTS_SUPPORT
static INT32 _nav_cec_custom_set_spdif(VOID)
{
    UINT16         ui2_spdif = 0;
    INT32          i4_ret = NAVR_OK;
    SCC_AUD_SPDIF_FMT_T e_spdif = SCC_AUD_SPDIF_FMT_PCM_24;

    if((g_b_icl_sac_val && g_b_tv_speaker_auto && g_b_acfg_tts_switch_val) ||
       (g_b_tv_speaker_off && g_b_acfg_tts_switch_val))
    {
        i4_ret = a_cfg_custom_get_digital_audio(&ui2_spdif);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("%%s,%d get digital audio fail \r\n",__FUNCTION__,__LINE__));
            return NAVR_FAIL;
        }

        if(AUD_SPDIF_AUDIO_OUT_CUSTOM_PCM != ui2_spdif)
        {
            UTF16_T        *pw2s_text = NULL;
            WDK_TOAST_T    t_toast = {0};
            UTF16_T        w2s_tmp_str[512] = {0};

            e_spdif = SCC_AUD_SPDIF_FMT_PCM_24;
            a_cfg_custom_set_digital_audio(AUD_SPDIF_AUDIO_OUT_CUSTOM_PCM); //PCM

            /* Set the SPDIF to config immediately */
            a_cfg_set_spdif_type(e_spdif);
            a_cfg_update_spdif_type();

            pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_DIGITAL_AUD_CHA_TO_PCM);

            c_uc_w2s_strcpy(w2s_tmp_str, pw2s_text);

            c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_WARNING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;

            _cec_info_send_string_to_nav(&t_toast);
        }
    }

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name:    a_tv_set_mute
 * Description: Mute/Unmute audio.
 * Input:   b_mute      Determine whether to mute audio or not.
 * Output:  -
 * Returns  TVR_OK      This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
static INT32 _nav_cec_set_mute (BOOL b_mute)
{
    INT32 i4_ret = NAVR_OK;
    HANDLE_T                 h_aud_scc_comp = NULL_HANDLE;
    SM_COMMAND_T    at_sm_cmds[5];
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out_pre;
    a_cfg_custom_get_ana_audio_out(&e_aud_out_pre);

//    b_edid_change_mute_process = TRUE;

    /* 1, Prepare*/
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open (at_sm_cmds, &h_aud_scc_comp);
    if (i4_ret != NAVR_OK)
    {
        DBG_LOG_PRINT(("[ DC_ON +++][%s,%d],return :%d!,open fail.\n",__FUNCTION__,__LINE__,i4_ret));
        return i4_ret;
    }

    /* 2, mute/Unmute spdif */
    {
        if(b_mute)
        {
            i4_ret = c_scc_aud_set_output_port(h_aud_scc_comp,SCC_AUD_OUT_PORT_SPDIF, FALSE);
        }
        else
        {
            i4_ret = c_scc_aud_set_output_port(h_aud_scc_comp,SCC_AUD_OUT_PORT_SPDIF, TRUE);
        }

        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[ DC_ON +++][%s,%d],return :%d!,open fail.\n",__FUNCTION__,__LINE__,i4_ret));
            goto SCC_OPEN_FAIL;
        }
    }
    /* 2, mute/Unmute AMP */
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
    //set sac mute
    {
        NAV_CEC_EX_CTRL_PARAM_T t_param;
        NAV_CEC_EX_CTRL_RESULT_T t_result;
        /* Perform Mute. */
        t_param.e_cmd = NAV_CEC_EX_CTRL_CMD_SET_MUTE;
        t_param.u_param.t_mute.b_mute = b_mute;

        i4_ret = a_nav_cec_do_ex_ctrl (&t_param, &t_result);
        if ((i4_ret != NAVR_OK) || (t_result.e_cmd != NAV_CEC_EX_CTRL_CMD_SET_MUTE))
        {
            DBG_LOG_PRINT(("[ DC_ON +++][%s,%d],return :%d!,open fail.\n",__FUNCTION__,__LINE__,i4_ret));
            //return TVR_FAIL;
            goto SCC_OPEN_FAIL;
        }
    }
#else
    {
        i4_ret = a_nav_cec_sac_set_mute (b_mute);
        if (i4_ret != TVR_OK)
        {
            //return TVR_FAIL;
            DBG_LOG_PRINT(("[ DC_ON +++][%s,%d],return :%d!,open fail.\n",__FUNCTION__,__LINE__,i4_ret));
            goto SCC_OPEN_FAIL;
        }
    }
#endif /* APP_CEC2_SUPPORT */
#endif /* APP_CEC_SUPPORT */

    /* 3, Mute/Unmute speaker & lineout */

    i4_ret = a_tv_set_mute_custom (b_mute);
    if (i4_ret != TVR_NO_EXIST)
    {
        DBG_LOG_PRINT(("[ DC_ON +++][%s,%d],return :%d!,open fail.\n",__FUNCTION__,__LINE__,i4_ret));
        //return i4_ret;
        goto SCC_OPEN_FAIL;
    }

    /*i4_ret = a_tv_set_audio_mute (TV_AUDIO_MUTE_MASK_FORCE, b_mute);
    if (i4_ret != TVR_OK)
    {
        return TVR_FAIL;
    }*/

    if(!b_mute)
    {
         e_aud_out = e_aud_out_pre;
         i4_ret = c_scc_aud_set_output_port_adj (h_aud_scc_comp, SCC_AUD_OUT_PORT_2_CH, (e_aud_out == A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED) ? TRUE: FALSE);
         //RET_ON_ERR(i4_ret);//Set lineout Fixed/viarable as previous
        if (i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT(("[ DC_ON +++][%s,%d],return :%d!,open fail.\n",__FUNCTION__,__LINE__,i4_ret));
            goto SCC_OPEN_FAIL;
        }
    }

SCC_OPEN_FAIL:
    i4_ret = c_scc_comp_close(h_aud_scc_comp);
    if (i4_ret != NAVR_OK)
    {
        DBG_LOG_PRINT(("[ DC_ON +++][%s,%d],return :%d!,close fail.\n",__FUNCTION__,__LINE__,i4_ret));
    }

    return i4_ret;
}


static VOID _hdmi_plug_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
     nav_request_context_switch( a_tv_set_mute_fct, NULL, NULL, NULL);

}
static VOID a_tv_set_mute_fct(VOID*        pv_tag1,
                                                     VOID*        pv_tag2,
                                                     VOID*        pv_tag3)
{
    _nav_cec_set_mute(FALSE);
}
INT32 a_tv_nav_cec_set_arc_spdif_mute(BOOL b_mute)
{
    INT32 i4_ret = NAVR_OK;
    i4_ret = _nav_cec_set_mute(b_mute);
    if(i4_ret != NAVR_OK)
    {
        DBG_LOG_PRINT(("[mute spdif +++] {%s %s() %d}. b_mute = %d,failed:%d!!!\n",__FILE__, __FUNCTION__, __LINE__,b_mute,i4_ret));
    }
    return i4_ret;
}
static VOID _nav_cec_custom_init_sac_status(VOID)
{
    UINT16          ui2_idx = 0;
    INT32           i4_ret = 0;
    UINT8           ui1_icl_val;
    SIZE_T          z_size = sizeof(UINT8);
    UINT16          ui2_spdif = 0;


    i4_ret = a_cfg_custom_get_digital_audio(&ui2_spdif);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_INFO(("%s,%d [cec custom] get acfg digital aud out fail \r\n",__FUNCTION__,__LINE__));
    }

    //digital aud out is auto or bitstream
    g_b_digital_aud_val = ui2_spdif;
    NAV_CEC_LOG_I("g_b_digital_aud_val=%d\n",g_b_digital_aud_val);



    // get is or not cec device connected
    z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if(i4_ret != ICLR_OK)
    {
        DBG_INFO((" [cec custom] get sac status icl fail \n"));
    }

    if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val)
    {
        g_b_icl_sac_val = TRUE;
    }
    else
    {
        g_b_icl_sac_val = FALSE;
    }

    a_cfg_custom_get_speakers_out(&ui2_idx);
    if(ui2_idx == APP_CFG_AUD_AD_SPEAKER_AUTO) //TV speaker are Auto
    {
        g_b_tv_speaker_auto = TRUE;
        g_b_tv_speaker_off = FALSE;
    }
    else if(ui2_idx == APP_CFG_AUD_AD_SPEAKER_OFF)//TV speaker are Auto
    {
        g_b_tv_speaker_off = TRUE;
        g_b_tv_speaker_auto = FALSE;
    }
    else
    {
        g_b_tv_speaker_auto = FALSE;
        g_b_tv_speaker_off = FALSE;
    }

}
/*----------------------------------------------------------------------------
 * Name: _nav_cec_custom_tv_speaker_nfy_func
 *
 * Description: tv speaker acfg notify
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_cec_custom_tv_speaker_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, UINT16 ui2_id)
{
    UINT16   ui2_idx = 0;
    UINT16   ui2_rec_id = CFG_GET_SETTING(ui2_id);
	NAV_CEC_CUSTOM_AMP_DLG_T*		 pt_this = &t_g_nav_cec_custom_amp_dlg;

    if(pt_this->ui2_cfg_tv_speaker_auto_nfy != ui2_nfy_id || ui2_rec_id != APP_CFG_RECID_CUST_RSEV_UI1_EX_5)
	{
		return;
	}

    a_cfg_custom_get_speakers_out(&ui2_idx);
    if(ui2_idx == APP_CFG_AUD_AD_SPEAKER_AUTO) //TV speaker are Auto
    {
        g_b_tv_speaker_auto = TRUE;
        g_b_tv_speaker_off = FALSE;
    }
    else if(ui2_idx == APP_CFG_AUD_AD_SPEAKER_OFF)//TV speaker are Auto
    {
        g_b_tv_speaker_off = TRUE;
        g_b_tv_speaker_auto = FALSE;
    }
    else
    {
        g_b_tv_speaker_auto = FALSE;
        g_b_tv_speaker_off = FALSE;
    }

#ifdef APP_TTS_SUPPORT
    _nav_cec_custom_set_spdif();
#endif
    return ;
}

/*----------------------------------------------------------------------------
 * Name: _nav_cec_custom_digital_aud_out_func
 *
 * Description: digital aud out acfg notify
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_cec_custom_digital_aud_out_func (UINT16 ui2_nfy_id, VOID* pv_tag, UINT16 ui2_id)
{
    UINT16   ui2_spdif = 0;
    INT32    i4_ret = 0;

	NAV_CEC_CUSTOM_AMP_DLG_T*		 pt_this = &t_g_nav_cec_custom_amp_dlg;
	UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);

    if(pt_this->ui2_cfg_digital_aud_out_nfy != ui2_nfy_id || ui2_rec_id != APP_CFG_RECID_CUST_RSEV_UI1_EX_6)
	{
		return;
	}

    i4_ret = a_cfg_custom_get_digital_audio(&ui2_spdif);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_INFO(("%s,%d [cec custom] get acfg digital aud out fail \r\n",__FUNCTION__,__LINE__));
    }

    //digital aud out is auto or bitstream
    g_b_digital_aud_val = ui2_spdif;
    NAV_CEC_LOG_I("g_b_digital_aud_val=%d\n",g_b_digital_aud_val);

    return ;
}

#ifdef APP_TTS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _nav_cec_custom_tts_switch_nfy_func
 *
 * Description: tts acfg notify
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_cec_custom_tts_switch_nfy_func(UINT16 ui2_nfy_id, VOID* pv_tag, UINT16 ui2_id)
{
    UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);
    UINT8   ui1_idx = 0;

    if (ui2_cfg_tts_switch != ui2_nfy_id || ui2_rec_id != APP_CFG_RECID_TTS_SWITCH)
    {
        return;
    }

    a_cfg_get_tts_switch_status(&ui1_idx);
    if(ui1_idx == APP_CFG_TTS_SWITCH_ON)
    {
        g_b_acfg_tts_switch_val = TRUE;
    }
    else
    {
        g_b_acfg_tts_switch_val = FALSE;
    }

#ifdef APP_TTS_SUPPORT
    _nav_cec_custom_set_spdif();
#endif

    return ;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_cec_custom_amp_plug_mute_tv_timer_fct
 * Description:
 *      nav amp/audio plugin mute TV Speaker timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_cec_custom_amp_plug_mute_tv_timer_fct(VOID*        pv_tag1,
                                            VOID*        pv_tag2,
                                            VOID*        pv_tag3)
{
    NAV_CEC_CUSTOM_AMP_DLG_T*     pt_this = &t_g_nav_cec_custom_amp_dlg;
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);

    a_cfg_av_set(ui2_id, (INT16)(pt_this->ui2_aud_out_mask));
    a_cfg_av_update(ui2_id);
    c_timer_stop(pt_this->h_mute_timer);

    return;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_cec_custom_amp_plug_mute_tv_timer_nfy
 * Description:
 *      nav usb plugin detection mute TV Speaker timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_cec_custom_amp_plug_mute_tv_timer_nfy(HANDLE_T        h_timer,
                                            VOID*           pv_tag)
{
    nav_request_context_switch(_nav_cec_custom_amp_plug_mute_tv_timer_fct, NULL, NULL, NULL);

    return;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_cec_custom_amp_plug_mute_tv_timer_reset
 * Description:
 *      start nav amp/audio plugin mute TV Speaker timer
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_amp_plug_mute_tv_timer_reset(VOID)
{
    INT32                       i4_ret = NAVR_OK;
    NAV_CEC_CUSTOM_AMP_DLG_T*       pt_this = &t_g_nav_cec_custom_amp_dlg;

    c_timer_stop(pt_this->h_mute_timer);
    if (NULL_HANDLE != pt_this->h_mute_timer)
    {
        i4_ret = c_timer_start(pt_this->h_mute_timer,
                               pt_this->ui4_mute_delay,
                               X_TIMER_FLAG_ONCE,
                               _nav_cec_custom_amp_plug_mute_tv_timer_nfy,
                               NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _nav_cec_custom_sac_nfy_func
 *
 * Description: to mute or unmute tv speaker
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_sac_staus_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)

{
    INT32           i4_ret = 0;
    UINT8           ui1_icl_val;
    UINT16          i2_speaker_val = 0;
    SIZE_T          z_size = sizeof(UINT8);
    UINT16          ui2_aud_out_mask;
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    INT16           i2_val;

    ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE  e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);

    if (e_grp_id != ICL_GRPID_CEC)
    {
        return NAVR_OK;
    }
	if(e_rec_id != ICL_RECID_CEC_SAC_STATUS)
	{
	    return NAVR_OK;
	}

    // get is or not cec device connected
    z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if(i4_ret != ICLR_OK)
    {
        DBG_INFO((" [cec custom] get sac status icl fail \n"));
    }

    if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val)
    {
        g_b_icl_sac_val = TRUE;
    }
    else
    {
        g_b_icl_sac_val = FALSE;
    }

#ifdef APP_TTS_SUPPORT
    _nav_cec_custom_set_spdif();
#endif
    a_cfg_update_spdif_type();

    /* Get current tv speaker setting */
    i4_ret = a_cfg_av_get(ui2_id, &i2_val);
    RET_ON_ERR(i4_ret);
    ui2_aud_out_mask = (UINT16)i2_val;

    a_cfg_custom_get_speakers_out(&i2_speaker_val);
    DBG_LOG_PRINT(("%s,%d [cec custom]tv_speaker_val= %d ,icl_val= %d, speaker_status= %d \r\n",
            __FUNCTION__,__LINE__,i2_speaker_val,ui1_icl_val,(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER)));

    if(i2_speaker_val == APP_CFG_AUD_AD_SPEAKER_AUTO) //tv speaker are auto now
    {
        if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val) //connected cec device
        {
            if(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) //tv speaker are on now
            {
                ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER); // mute tv speaker
            }
            else
            {
                return NAVR_OK;
            }
        }
        else
        {
            if(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER)
            {
                return NAVR_OK;
            }
            else
            {
                ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER); //unmute tv speaker
            }
        }
    }
    else
    {
        //do nothing, unplug AMP HDMI cabe, tv speaker are off all the time if the current tv speaker are off
    }

#ifdef APP_TTS_SUPPORT
    UINT8          ui1_tts_idx = 0;

    i4_ret = a_cfg_get_tts_switch_status(&ui1_tts_idx);
    if(i4_ret != APP_CFGR_OK){
        DBG_LOG_PRINT(("%%s,%d get tts switch fail \r\n",__FUNCTION__,__LINE__));
    }
    if((ICL_CEC_SAC_STATUS_ON == ui1_icl_val) && (ui1_tts_idx == APP_CFG_TTS_SWITCH_ON)) //connected cec device and tts is on.
    {
        DBG_INFO((" [cec custom] delay mute tv speaker.\n"));
        t_g_nav_cec_custom_amp_dlg.ui2_aud_out_mask = ui2_aud_out_mask;
        _nav_cec_custom_amp_plug_mute_tv_timer_reset();
    }
    else
#endif
    {
    	a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
        a_cfg_av_update(ui2_id);
    }

    return NAVR_OK;
}
static UINT16                  ui2_icl_dobly_atmos_nfy = 0;
static INT32 _nav_cec_custom_dobly_atmos_device_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    UINT32  i4_ret          = 0;
    UINT8   ui1_ddp_status  = 0;
    UINT8   ui1_icl_val     = 0;
    UINT8   ui1_doblyatmos  = 0;

    ICL_GRPID_TYPE  e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE  e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);

    #define DOBLY_ATMOS_SUPPORT         ((UINT8)    1)
    #define DOBLY_ATMOS_UNSUPPORT       ((UINT8)    0)

    if (e_grp_id != ICL_GRPID_CEC)
    {
        DBG_LOG_PRINT(("\n\n[ MENU +++ ] {%s %s() %d}. enter. \n\n",__FILE__, __FUNCTION__, __LINE__));
        return NAVR_OK;
    }

    if(e_rec_id != ICL_RECID_CEC_SAC_SAD)
    {
        if (e_rec_id == ICL_RECID_CEC_SAC_DDP)
        {
            DBG_LOG_PRINT(("\n\n[ MENU +++ ] {%s %s() %d}. enter. \n\n",__FILE__, __FUNCTION__, __LINE__));
        }
        else
        {
            DBG_LOG_PRINT(("\n\n[ MENU +++ ] {%s %s() %d}. enter. e_rec_id = %d\n\n",__FILE__, __FUNCTION__, __LINE__,e_rec_id));
            return NAVR_OK;
        }
    }

    /* ui1_icl_val */
    {
        SIZE_T   z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
        i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                           &ui1_icl_val,
                           &z_size);
        RET_ON_ERR(i4_ret);
    }

    /* pt_ddp_support */
    {
        SIZE_T   z_size = ICL_RECID_CEC_SAC_DDP_SIZE;
        i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CEC, ICL_RECID_CEC_SAC_DDP),
                           &ui1_ddp_status,
                           &z_size);
        RET_ON_ERR(i4_ret);
    }

    if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val &&
       ICL_CEC_DDP_STATUS_ON == ui1_ddp_status) // have cec device connected
    {
        ui1_doblyatmos = DOBLY_ATMOS_SUPPORT;    /* DOLBY D */
    }
    else
    {
        ui1_doblyatmos = DOBLY_ATMOS_UNSUPPORT;    /* DOLBY D */
    }

    DBG_LOG_PRINT(("\n\n[ MENU +++ ] {%s %s() %d}. ui1_doblyatmos = %d,ui1_icl_val = %d,ui1_ddp_status = %d\n\n",
                    __FILE__, __FUNCTION__, __LINE__,ui1_doblyatmos,ui1_icl_val,ui1_ddp_status));
#ifdef SYS_MTKTVAPI_SUPPORT
    a_mtktvapi_volctrl_dobly_atmos_device_event_status(ui1_doblyatmos);
#endif
    return ui1_doblyatmos;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_cec_custom_amp_plug_dlg_deinit
 * Description:
 *      amp/audio plugin detection view deinitialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_cec_custom_amp_plug_dlg_deinit (VOID)
{
    INT32                    i4_ret = NAVR_OK;
    NAV_CEC_CUSTOM_AMP_DLG_T*      pt_this = &t_g_nav_cec_custom_amp_dlg;

    if (NULL_HANDLE != pt_this->h_hide_timer)
    {
        i4_ret = c_timer_delete(pt_this->h_hide_timer);
        RET_ON_ERR(i4_ret);
    }
    if (NULL_HANDLE != pt_this->h_mute_timer)
    {
        i4_ret = c_timer_delete(pt_this->h_mute_timer);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_cec_custom_block_volume_key_forward.
 * Description:
 *      judge whether the key need to be forwarded to CEC bus
 * Input arguments:
 *      UINT32  ui4_key_code- BTN ket code
 * Output arguments:
 *      None
 * Returns:
 *      True - the key is needless to be forwarded
 *      False - the key can pass
 *---------------------------------------------------------------------------*/
BOOL _nav_cec_custom_block_volume_key_forward ()
{
    NAV_RETAIL_MODE_STATUS_T retail_status;
    a_nav_retail_mode_get_status(&retail_status);
    if((a_wzd_is_oobe_mode() == TRUE)&&(retail_status!=NAV_RETAIL_MODE_RUNNING))
    {
        DBG_LOG_PRINT(("%s,%d [cec] don't send amp volume key in oobe status \r\n",__FUNCTION__,__LINE__));

        return TRUE;
    }

    if(pwd_dlg_view_is_show_box())
    {
        DBG_LOG_PRINT(("\n####%s(%d)don't deal with iom key when pwd pin dlg show \n",__FUNCTION__,__LINE__));

        return TRUE;
    }

    return FALSE;
}
#endif
/**
 * @brief   This function performs initialization in the custom part.
 * @param   pv_param1 [in] Not use now.
 * @param   pv_param2 [in] Not use now.
 * @param   pv_param3 [in] Not use now.
 * @param   pv_param4 [in] Not use now.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_init (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    INT32 i4_ret;
	#ifdef APP_ARC_ONLY
	NAV_CEC_CUSTOM_AMP_DLG_T*		 pt_this = &t_g_nav_cec_custom_amp_dlg;
	#endif

    /* Register View. */
    /*i4_ret = nav_cec_view_reg (NULL, NULL, NULL, NULL);
    IS_CECR_OK (i4_ret);
    */

    /* Register One Touch Play. */
    i4_ret = nav_cec_otp_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* Pass through. */
    t_pass_through_custom.ui1_custom_key_code_tbl_size = sizeof (_at_custom_pass_through_key_code_def) / sizeof (_at_custom_pass_through_key_code_def[0]);
    t_pass_through_custom.pt_custom_key_code_tbl = _at_custom_pass_through_key_code_def;
    t_pass_through_custom.ui1_vndr_key_list_size = 0;
    t_pass_through_custom.pui4_vndr_key_list = NULL;
    t_pass_through_custom.b_auto_start = TRUE;
    i4_ret = nav_cec_pass_through_reg ((VOID*)&t_pass_through_custom, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* Register System Standby. */
    i4_ret = nav_cec_sys_standby_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* Register Give Device Power Status. */
    i4_ret = nav_cec_gdps_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* Register Routing Control. */
    i4_ret = nav_cec_routing_ctrl_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* Register System Information. */
    i4_ret = nav_cec_sys_info_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* misc. */
    i4_ret = nav_cec_misc_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* sac. */
    i4_ret = nav_cec_sac_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);

    /* arc. */
    i4_ret = nav_cec_arc_reg (NULL, NULL, NULL, NULL);
    NAV_CEC_LOG_ON_ERR (i4_ret);
/*
    i4_ret = nav_cec_sac_drv_set_dts_enable(TRUE);
    NAV_CEC_LOG_ON_ERR (i4_ret);
*/
    DBG_LOG_PRINT(("#### %s(%d) \n", __FILE__, __LINE__ ));
    nav_cec_set_earc_status(FALSE);

#ifdef APP_ARC_ONLY
    /*create mute tv timer when amp plug.*/
    i4_ret = c_timer_create(&pt_this->h_mute_timer);
    RET_ON_ERR(i4_ret);
    pt_this->ui4_mute_delay = NAV_CEC_AMP_PLUG_MUTE_TV_DELAY;

	i4_ret = c_timer_create(&h_hdmi_plug_timer);
    RET_ON_ERR(i4_ret);
	i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_RECID_CEC_AMP_PLUG,
                              NULL,
                              NULL,
                              _nav_cec_custom_amp_nfy_func,
                              &pt_this->ui2_icl_amp_nfy);
	NAV_CEC_LOG_ON_ERR (i4_ret);

	i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_RECID_CEC_ARC_ONLY,
                              NULL,
                              NULL,
                              _nav_cec_custom_arc_only_setting_nfy_func,
                              &pt_this->ui2_icl_arc_only_nfy);
	NAV_CEC_LOG_ON_ERR (i4_ret);

    _nav_cec_custom_init_sac_status();
	i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_RECID_CEC_SAC_STATUS,
                              NULL,
                              NULL,
                              _nav_cec_custom_sac_staus_nfy_func,
                              &pt_this->ui2_icl_sac_status_nfy);
	NAV_CEC_LOG_ON_ERR (i4_ret);

    i4_ret = a_cfg_notify_reg (APP_CFG_GRPID_CUSTOM_BASE,
                               NULL,
                               _nav_cec_custom_tv_speaker_nfy_func,
                               &pt_this->ui2_cfg_tv_speaker_auto_nfy);
    if(APP_CFGR_OK != i4_ret)
    {
        pt_this->ui2_cfg_tv_speaker_auto_nfy = APP_CFG_NOTIFY_NULL_ID;
        DBG_LOG_PRINT(("[cec custom] Can't a_cfg_notify_reg APP_CFG_GRPID_CUSTOM_BASE"));
    }

    i4_ret = a_cfg_notify_reg (APP_CFG_GRPID_CUSTOM_BASE,
                               NULL,
                               _nav_cec_custom_digital_aud_out_func,
                               &pt_this->ui2_cfg_digital_aud_out_nfy);
    if(APP_CFGR_OK != i4_ret)
    {
        pt_this->ui2_cfg_digital_aud_out_nfy = APP_CFG_NOTIFY_NULL_ID;
        DBG_LOG_PRINT(("[cec custom] Can't a_cfg_notify_reg APP_CFG_GRPID_CUSTOM_BASE"));
    }

#ifdef APP_TTS_SUPPORT
    i4_ret = a_cfg_notify_reg (APP_CFG_GRPID_MISC,
                               NULL,
                               _nav_cec_custom_tts_switch_nfy_func,
                               &ui2_cfg_tts_switch);
    if(APP_CFGR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[cec custom] Can't a_cfg_notify_reg APP_CFG_GRPID_MISC"));
    }
#endif

    /* monitor: ICL_RECID_CEC_PB1_PLUG
       *          ICL_RECID_CEC_PB2_PLUG
       *          ICL_RECID_CEC_PB3_PLUG
       *          ICL_RECID_CEC_RD1_PLUG
       *          ICL_RECID_CEC_RD2_PLUG
       *          ICL_RECID_CEC_AUD_PLUG
       *          ICL_RECID_CEC_RD3_PLUG
       *          ICL_RECID_CEC_TUNER1_PLUG
       *          ICL_RECID_CEC_TUNER2_PLUG
       *          ICL_RECID_CEC_TUNER3_PLUG
       *          ICL_RECID_CEC_TUNER4_PLUG,
       *          register one CEC ICL record is enough.
       */
    i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_RECID_CEC_PB1_PLUG,
                              NULL,
                              NULL,
                              _nav_cec_custom_dev_nfy_func,
                              &pt_this->ui2_icl_dev_pb1_nfy);
	NAV_CEC_LOG_ON_ERR (i4_ret);
    b_last_5v_status = FALSE;

#endif // #ifdef APP_ARC_ONLY

    /*register callback to notify dobly atmos*/
    i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_RECID_CEC_SAC_SAD,
                              NULL,
                              NULL,
                              _nav_cec_custom_dobly_atmos_device_nfy_func,
                              &ui2_icl_dobly_atmos_nfy);
    IS_CECR_OK (i4_ret);

    _nav_cec_custom_Dbg_init();

    return NAVR_OK;
}
/**
 * @brief   This function performs de-initialization in the custom part.
 * @param   pv_param1 [in] Not use now.
 * @param   pv_param2 [in] Not use now.
 * @param   pv_param3 [in] Not use now.
 * @param   pv_param4 [in] Not use now.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_deinit (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
#ifdef APP_ARC_ONLY
	_nav_cec_custom_amp_plug_dlg_deinit();
#endif
    return NAVR_OK;
}
/**
 * @brief   This function determines whether the activation request is allowed or not.
 * @param   e_cur_id [in]   Current activated feature id.
 * @param   e_next_id [in]  Next activated feature id.
 * @retval  TRUE    The request is allowed.
 * @retval  FALSE   The request is forbad.
 */
BOOL nav_cec_custom_is_activation_allowed (NAV_CEC_FEATURE_ID_T e_cur_id, NAV_CEC_FEATURE_ID_T e_next_id)
{
    return TRUE;
}

/**
 * @brief   Forward digital key or use it to switch channel
 * @retval  TRUE        Forward digital key to CEC device.
 * @retval  FALSE       Do not forward digital key.
 */
BOOL nav_cec_dmc_custom_is_digital_key_forward(VOID)
{
    return TRUE;
}
/**
 * @brief   This function gets MW's opcode according to user pressed command.
 * @param   e_cec_cmd [in]  User pressed CEC commands.
 * @retval  CECM_OPCODE_NONE    No proper opcode is found.
 * @retval  Otherwise           The corresponding MW opcode.
 */
CECM_OPCODE_T nav_cec_custom_get_opcode_by_cmd (NAV_CEC_CMD_T e_cec_cmd)
{
    switch (e_cec_cmd)
    {
    case CEC_CMD_STANDBY:
        return CECM_OPCODE_STANDBY;
    case CEC_CMD_MENU:
        return CECM_OPCODE_MENU_REQ;
    case CEC_CMD_PLAY:
        return CECM_OPCODE_SET_STREAM_PATH;
    case CEC_CMD_POWER_ON:
        return CECM_OPCODE_USER_CTRL_RELEASED;
    case CEC_CMD_SAC_ON:
    case CEC_CMD_SAC_OFF:
        return CECM_OPCODE_SYS_AUD_MOD_REQ;
    default:
        NAV_CEC_DBG_MSG (e_cec_cmd);
        return CECM_OPCODE_NONE;
    }
}
/**
 * @brief   This function gets command strings by device type.
 * @param   e_cec_cmd [in]  CEC commands.
 * @param   ppw2s_str [out] A pointer to the corresponding string.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_get_cmd_str (NAV_CEC_CMD_T e_cec_cmd, UTF16_T** ppw2s_str)
{
    switch (e_cec_cmd)
    {
    case CEC_CMD_STANDBY:       /* System Standby. */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_STANDBY);
        break;
    case CEC_CMD_MENU:          /* Device menu control. */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_MENU);
        break;
    case CEC_CMD_DECK_CTRL:          /* Routing control. */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_DECK_CTRL);
        break;
    case CEC_CMD_RECORD:        /* Recording device. */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_RECORD);
        break;
    case CEC_CMD_SAC_ON:            /* Audio system. */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_ON);
        break;
    case CEC_CMD_SAC_OFF:           /* Audio system. */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_OFF);
        break;
    case CEC_CMD_CEC_FUNC_ON:
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_FUNC_ON);
        break;
    case CEC_CMD_CEC_FUNC_OFF:
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_FUNC_OFF);
        break;
    case CEC_CMD_AUTO_OFF_ON:
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_AUTO_OFF_ON);
        break;
    case CEC_CMD_AUTO_OFF_OFF:
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_AUTO_OFF_OFF);
        break;
    case CEC_CMD_MANUAL_DEV_SCAN:
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_MANUAL_DEV_SCAN);
        break;
    case CEC_CMD_POWER_ON:
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_POWER_ON);
        break;
    default:
        NAV_CEC_DBG_MSG (e_cec_cmd);
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/**
 * @brief   This function gets command strings of device menu ctrl.
 * @param   b_menu_active [in]  Device menu status.
 * @param   ppw2s_str     [out] A pointer to the corresponding string.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_get_menu_cmd_str (BOOL b_menu_active, UTF16_T** ppw2s_str)
{
    if (b_menu_active)
    {
        /* It's active source, show: "Leave Menu" */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_LEAVE_MENU);
    }
    else
    {
        /* It's not active source, show: "Enter Menu" */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_ENTER_MENU);
    }

    return NAVR_OK;
}

/**
 * @brief   This function gets command strings of one touch record.
 * @param   b_is_recording [in]  Whether recorder is recording.
 * @param   ppw2s_str      [out] A pointer to the corresponding string.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_get_rec_cmd_str (BOOL b_is_recording, UTF16_T** ppw2s_str)
{
    if (! b_is_recording)
    {
        /* The recorder is not recording now */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_RECORD);
    }
    else
    {
        /* The recorder is recording now */
        *ppw2s_str = MLM_CEC_TEXT(nav_get_mlm_lang_id(), MLM_CEC_KEY_STOP);
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:    nav_cec_custom_is_ignore_ont_touch_play
 * Description: Determine whether to ignore one touch play in some conditions.
 * Input:   -
 * Output:  -
 * Returns: TRUE    Ignore current one touch play message.
 *          FALSE   DO NOT ignore current one touch play message.
 *---------------------------------------------------------------------------*/
BOOL nav_cec_custom_is_ignore_one_touch_play (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    INT32 i4_ret;
    CHAR s_app_name[APP_NAME_MAX_LEN + 1];
    NAV_EXTERNAL_CTRL_TYPE_T e_nav_ctrl_type;

    /* Scan. */
    if (nav_is_channel_scan_active () == TRUE)
    {
        return TRUE;
    }
    /* Running Wizard. */
    i4_ret = a_am_get_active_app (s_app_name);
    if (i4_ret != 0)
    {
        return FALSE;
    }
    if (c_strcmp ((CHAR*)s_app_name, (CHAR*)WZD_NAME) == 0)
    {
        return TRUE;
    }

    if(a_wzd_is_oobe_mode())
    {
        return TRUE;
    }
    /* Running EAS. */
    i4_ret = nav_get_ex_ctrl_type (&e_nav_ctrl_type);
    if (i4_ret != 0)
    {
        DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }
    if (e_nav_ctrl_type == NAV_EXTERNAL_CTRL_TYPE_EAS)
    {
        return TRUE;
    }

#ifdef LINUX_TURNKEY_SOLUTION
    BOOL b_is_skype_fullscreen = FALSE;
    CHAR ui1_ch;
    FILE * fl = fopen ("/tmp/FULLSCREEN","r");

    if (fl == NULL)
    {
        return FALSE;
    }

    if (fread(&ui1_ch, sizeof(CHAR), 1, fl) == 1)
    {
        if (ui1_ch == '1')
        {
            b_is_skype_fullscreen = TRUE;
        }
    }

    fclose (fl);

    if (b_is_skype_fullscreen == TRUE)
    {
        return TRUE;
    }
#endif

#if 0//def APP_MJC_SUPPORT
    {
        UINT32 ui4_demo_status = 0;

        i4_ret = a_cfg_get_demo_status (&ui4_demo_status);
        if (i4_ret != 0)
        {
            return FALSE;
        }
        if (ui4_demo_status != APP_CFG_DEMO_MODE_OFF)
        {
            return TRUE;
        }
    }
#endif

    return FALSE;
}

VOID nav_cec_custom_notify_input_changed_by_otp (ISL_REC_T* pt_isl_rec)
{
    if (INP_SRC_TYPE_TV == pt_isl_rec->e_src_type)
    {
        rest_event_notify_current_input("tuner");
    }
    else if (INP_SRC_TYPE_AV == pt_isl_rec->e_src_type)
    {
        if (DEV_AVC_HDMI == pt_isl_rec->t_avc_info.e_video_type)
        {
            if (pt_isl_rec->ui1_internal_id == 0) {
                rest_event_notify_current_input("hdmi1");
            } else if (pt_isl_rec->ui1_internal_id == 1) {
                rest_event_notify_current_input("hdmi2");
            } else if (pt_isl_rec->ui1_internal_id == 2) {
                rest_event_notify_current_input("hdmi3");
            } else if (pt_isl_rec->ui1_internal_id == 3) {
                rest_event_notify_current_input("hdmi4");
            }
        }
        else if (DEV_AVC_COMBI == pt_isl_rec->t_avc_info.e_video_type)
        {
            rest_event_notify_current_input("comp");
        }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name:    nav_cec_custom_is_ignore_ont_touch_record
 * Description: Determine whether to ignore one touch record in some conditions.
 * Input:   -
 * Output:  -
 * Returns: TRUE    Ignore current one touch record message.
 *          FALSE   DO NOT ignore current one touch record message.
 *---------------------------------------------------------------------------*/
BOOL nav_cec_custom_is_ignore_one_touch_record (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    INT32 i4_ret;
    CHAR s_app_name[APP_NAME_MAX_LEN + 1];

    /* Scan. */
    if (nav_is_channel_scan_active () == TRUE)
    {
        return TRUE;
    }
    /* Running Wizard. */
    i4_ret = a_am_get_active_app (s_app_name);
    if (i4_ret != 0)
    {
        return FALSE;
    }
    if (c_strcmp (s_app_name, WZD_NAME) == 0)
    {
        return TRUE;
    }

    return FALSE;
}

INT32 nav_cec_custom_routing_ctrl_mw_opcode_hdlr (CECM_OPCODE_T e_opcode, CECM_NFY_T* pt_cecm_nfy, BOOL* pb_process)
{
    switch (e_opcode)
    {
	    /* Routing control. */
	    case CECM_OPCODE_ROUTING_INFO:
	    {
	        if (a_nav_input_is_cec_processed() == TRUE)
	        {
	        	*pb_process = TRUE;
			}
			break;
		}
	    default:
	    {
	    	*pb_process = FALSE;
	        break;
	    }
	}
    return NAVR_OK;
}

BOOL nav_cec_custom_is_cast_source_active (VOID)
{
    UINT8 ui1_cast_state = ICL_RECID_CAST_SRC_STATUS_FALSE;
    a_icl_custom_get_cast_src_status(&ui1_cast_state);
    if (ui1_cast_state) {
        return TRUE;
    } else {
        return FALSE;
    }
}

INT32 nav_cec_custom_mw_nfy_pre_hdlr (
            NAV_CEC_UDPATE_INFO_NFY_T* pt_update_info,
            VOID* pv_tag,
            UINT32 ui4_data,
            BOOL* pb_skip
            )
{
    INT32 i4_ret = NAVR_OK;
    CECM_NFY_T* pt_cecm_nfy = &pt_update_info->t_cecm_nfy;

    *pb_skip = FALSE;

    if (pt_cecm_nfy->e_nfy_type == CECM_NFY_TYPE_OPCODE)
    {
        /* Skip all <user control pressed>. */
        if (pt_cecm_nfy->u_code.e_opcode == CECM_OPCODE_USER_CTRL_PRESSED)
        {
            *pb_skip = TRUE;
        }
    }
    else if (pt_cecm_nfy->e_nfy_type == CECM_NFY_TYPE_MSGCODE)
    {
        *pb_skip = FALSE;
    }
    else
    {
        NAV_CEC_DBG_MSG (pt_cecm_nfy->e_nfy_type);
        i4_ret = NAVR_INV_ARG;
    }
    return i4_ret;
}

/**
 * @brief   This function determines whether to ignore system audio control in some conditions.
 * @retval  TRUE    <Set System Audio Mode> opcode should be ignored.
 * @retval  FALSE   <Set System Audio Mode> opcode should be handled.
 */
BOOL nav_cec_custom_is_ignore_sys_aud_ctrl (VOID)
{
    INT32   i4_ret;
    UINT8   ui1_cec_sac_func = APP_CFG_CEC_ON;
    CHAR    s_app_name[APP_NAME_MAX_LEN + 1];
    UINT8   ui1_usb_sts;
    SIZE_T  z_size;
    NAV_EXTERNAL_CTRL_TYPE_T    e_nav_ctrl_type;

    /* Sys. Aud. Ctrl. setting */
    i4_ret = a_cfg_get_cec_sac_func(&ui1_cec_sac_func);
    if (i4_ret == APP_CFGR_OK &&
        ui1_cec_sac_func == APP_CFG_CEC_OFF)
    {
        NAV_CEC_LOG_I("sac_func = %d \n\r", ui1_cec_sac_func);
        return TRUE;
    }

    /* BGM/Semi-Standby */
    if (TRUE == nav_is_in_power_off())
    {
        NAV_CEC_LOG_I("Standby\n\r");
        return TRUE;
    }

    /* Scan. */
    if (a_am_is_channel_scan_active () == TRUE)
    {
        NAV_CEC_LOG_I("Scan\n\r");
        return TRUE;
    }

    /* Running Wizard. */
    i4_ret = a_am_get_active_app (s_app_name);
    if (i4_ret == 0 &&
        c_strcmp (s_app_name, WZD_NAME) == OSR_OK)
    {
        NAV_CEC_LOG_I("Wizard\n\r");
        return TRUE;
    }

    /* Running EAS. */
    i4_ret = nav_get_ex_ctrl_type (&e_nav_ctrl_type);
    if (i4_ret == 0 &&
        e_nav_ctrl_type == NAV_EXTERNAL_CTRL_TYPE_EAS)
    {
        NAV_CEC_LOG_I("EAS\n\r");
        return TRUE;
    }

    /* USB */
    i4_ret = a_icl_get (ICL_MAKE_ID(ICL_GRPID_USB_UPGRADE, ICL_RECID_USB_UPGRADE_STATUS),
                        (VOID*)&ui1_usb_sts, &z_size);
    if (i4_ret == 0 &&
        ui1_usb_sts == ICL_USB_UPGRADE_STATUS_RUNNING)
    {
        NAV_CEC_LOG_I("USB\n\r");
        return TRUE;
    }

    return FALSE;
}

BOOL nav_cec_custom_allow_changing_tv_speaker_status (VOID)
{
    return FALSE;
}

BOOL nav_cec_custom_is_chromecast (CECM_LOG_ADDR_T e_dev_la)
{
    INT32       i4_ret;
    CECM_DEV_T  t_dev_info;
    CECM_CTRL_T t_cecm_ctrl;
    t_cecm_ctrl.b_sync = FALSE;

    i4_ret = c_cecm_get_dev_info_by_la (
                                    nav_cec_get_mw_handle (),
                                    e_dev_la,
                                    &t_cecm_ctrl,
                                    &t_dev_info);
    if ((i4_ret == CECMR_CEC_FCT_DISABLED) || (i4_ret == CECMR_DEV_NOT_AVIL)) {
        return FALSE;
    }
    if (i4_ret != CECMR_OK) {
        DBG_LOG_PRINT(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }
    //DBG_LOG_PRINT(("nav_cec_custom_is_chromecast- vndr_id = 0x%x%x%x\n\r", t_dev_info.t_dev_vndr_id[0],
    //                                         t_dev_info.t_dev_vndr_id[1],
    //                                         t_dev_info.t_dev_vndr_id[2]));
    if (t_dev_info.t_dev_vndr_id[0] == 0x00
        && t_dev_info.t_dev_vndr_id[1] == 0x1a
        && t_dev_info.t_dev_vndr_id[2] == 0x11)
    {
        DBG_LOG_PRINT(("nav_cec_custom_is_chromecast- It's Chromecast\n\r"));
        return TRUE;
    } else {
        return FALSE;
    }
}

UINT32 nav_cec_custom_key_code_translation (UINT32 ui4_key_code, CECM_LOG_ADDR_T e_dev_la)
{
    switch (ui4_key_code)
    {
        #if 0
        case BTN_CURSOR_LEFT:
            ui4_key_code = BTN_SR;
            DBG_LOG_PRINT(("tranlate BTN_CURSOR_LEFT(%d) to BTN_SR(%d)\n\r", BTN_CURSOR_LEFT, ui4_key_code));
            break;
        case BTN_CURSOR_RIGHT:
            ui4_key_code = BTN_SF;
            DBG_LOG_PRINT(("tranlate BTN_CURSOR_RIGHT(%d) to BTN_SF(%d)\n\r", BTN_CURSOR_RIGHT, ui4_key_code));
            break;
        case BTN_SELECT:
            if (nav_cec_custom_is_chromecast(e_dev_la)) {
                if (g_b_toggle_play_pause) {
                    ui4_key_code = BTN_PLAY;
                } else {
                    ui4_key_code = BTN_PAUSE;
                }
                g_b_toggle_play_pause ^= 1;
            } else {
                ui4_key_code = BTN_PLAY_PAUSE;
            }
            DBG_LOG_PRINT(("tranlate BTN_SELECT(%d) to BTN_PLAY_PAUSE(%d)\n\r", BTN_SELECT, ui4_key_code));
            break;
        #endif
        case BTN_PLAY:
            DBG_LOG_PRINT(("no tranlate BTN_PLAY(%d)\n\r", BTN_PLAY));
            break;
        case BTN_PAUSE:
            DBG_LOG_PRINT(("no tranlate BTN_PAUSE(%d)\n\r", BTN_PAUSE));
            break;
        case BTN_PLAY_PAUSE:
            DBG_LOG_PRINT(("no tranlate BTN_PLAY_PAUSE(%d)\n\r", BTN_PLAY_PAUSE));
            break;
        default:
            //DBG_LOG_PRINT(("no keycode (%d) matched to be translated\n\r", ui4_key_code));
            break;
    }

    return ui4_key_code;
}

/**
 * @brief   _nav_cec_bgm_buf_add
 */
static VOID _nav_cec_bgm_buf_add (
                    UINT8               ui1_buf_idx,
                    CECM_NFY_T*         pv_nfy_data
                    )
{
    NAV_CEC_BGM_BUF_T*  pt_cec_buf = &t_nav_cec_bgm_buf;

    pt_cec_buf->ui4_last_id++;
    c_memcpy (&pt_cec_buf->at_nfy[ui1_buf_idx], pv_nfy_data, sizeof(CECM_NFY_T));
    pt_cec_buf->aui4_nfy_id[ui1_buf_idx] = pt_cec_buf->ui4_last_id;
}

/**
 * @brief   _nav_cec_bgm_buf_remove
 */
static VOID _nav_cec_bgm_buf_remove (
                    UINT8               ui1_buf_idx
                    )
{
    NAV_CEC_BGM_BUF_T*  pt_cec_buf = &t_nav_cec_bgm_buf;

    c_memset(&pt_cec_buf->at_nfy[ui1_buf_idx], 0, sizeof(CECM_NFY_T));
    pt_cec_buf->aui4_nfy_id[ui1_buf_idx] = 0;
}

/**
 * @brief   _nav_cec_bgm_buf_get
 */
static UINT16 _nav_cec_bgm_buf_get(
                    CECM_NFY_T*         pv_nfy_data
                    )
{
    NAV_CEC_BGM_BUF_T*  pt_cec_buf = &t_nav_cec_bgm_buf;
    UINT8               ui1_idx;
    UINT8               ui1_target_idx = NAV_CEC_BUF_IDX_MAX;
    UINT32              ui4_smallest_id;

    if (pt_cec_buf->ui4_last_id == 0){
        return NAVR_NO_ACTION;
    }
    else
    {
        ui4_smallest_id = pt_cec_buf->ui4_last_id+1;
    }

    for (ui1_idx = 0; ui1_idx < NAV_CEC_BUF_IDX_MAX; ui1_idx++)
    {
        if (pt_cec_buf->aui4_nfy_id[ui1_idx] != 0 &&
            pt_cec_buf->aui4_nfy_id[ui1_idx] < ui4_smallest_id)
        {
            ui4_smallest_id = pt_cec_buf->aui4_nfy_id[ui1_idx];
            ui1_target_idx = ui1_idx;
        }
    }
    if (ui1_target_idx == NAV_CEC_BUF_IDX_MAX)
    {
        return NAVR_NO_ACTION;
    }
    else
    {
        c_memcpy(pv_nfy_data, &pt_cec_buf->at_nfy[ui1_target_idx], sizeof(CECM_NFY_T));
        pt_cec_buf->aui4_nfy_id[ui1_target_idx] = 0;
        return NAVR_OK;
    }
}

/**
 * @brief   Event process function that handles MW NFY events.
 * @param   pv_tag1 [in]    Not used now.
 * @param   pv_tag2 [in]    Not used now.
 * @param   pv_tag3 [in]    Not used now.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
static VOID _nav_cec_bgm_power_on_tv (
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3
                    )
{
    UINT32  ui4_sub_reason = 0;
    if (a_am_is_power_on() == FALSE)
    {
        c_pcl_set_wakeup_reason(PCL_WAKE_UP_REASON_HDMI, &ui4_sub_reason);
        a_amb_power_on(TRUE);
    }
}

/**
 * @brief   Event process function that handles MW NFY events.
 * @param   pv_tag1 [in]    Not used now.
 * @param   pv_tag2 [in]    Not used now.
 * @param   pv_tag3 [in]    Not used now.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
static VOID _nav_cec_bgm_feature_abort (
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3
                    )
{
    CECM_FEATURE_ABORT_T    t_abort;
    CECM_LOG_ADDR_T         e_la;

    e_la = (CECM_LOG_ADDR_T)((UINT32)pv_tag1);
    t_abort.e_opcode = (CECM_OPCODE_T)((UINT32)pv_tag2);
    t_abort.e_abort_reason = (CECM_ABORT_REASON_T)((UINT32)pv_tag3);

    c_cecm_set_feature_abort(nav_cec_get_mw_handle(), e_la, &t_abort);
}

/**
 * @brief   This function will be called by MW if there is notification available.
 *          This function may be called by CLI test function.
 * @param   pv_nfy_data [in]    A pointer to CECM_NFY_T.
 * @param   pv_tag [in]         A private tag value.
 * @param   ui4_data [in]       Not used now.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
static VOID _nav_cec_custom_nfy_fct (
                    CECM_NFY_T*   pv_nfy_data,
                    VOID*         pv_tag,
                    UINT32        ui4_data)
{
    NAV_CEC_BGM_BUF_T* pt_nav_cec_bgm_buf = &t_nav_cec_bgm_buf;

    c_sema_lock (pt_nav_cec_bgm_buf->h_nfy_mtx, X_SEMA_OPTION_WAIT);
    pf_dispatch_nfy_fct(pv_nfy_data, pv_tag, ui4_data);
    c_sema_unlock (pt_nav_cec_bgm_buf->h_nfy_mtx);
}

/**
 * @brief   This function will be called by MW if there is notification available in
 *          the BGM mode
 * @param   pv_nfy_data [in]    A pointer to CECM_NFY_T.
 * @param   pv_tag [in]         A private tag value.
 * @param   ui4_data [in]       Not used now.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
static VOID _nav_cec_bgm_nfy_fct (
                CECM_NFY_T*             pv_nfy_data,
                VOID*                   pv_tag,
                UINT32                  ui4_data
                )
{
    NAV_CEC_BGM_BUF_T*  pt_cec_buf = &t_nav_cec_bgm_buf;
    BOOL                b_power_on_tv = FALSE;
    BOOL                b_abort_opcode = FALSE;
    CECM_ABORT_REASON_T e_abort_reason;

    if (pv_nfy_data->e_nfy_type == CECM_NFY_TYPE_MSGCODE)
    {
        if (pv_nfy_data->u_code.e_msgcode != CECM_MSGCODE_ONE_TOUCH_PLAY){
            return;
        }
        _nav_cec_bgm_buf_add(NAV_CEC_BUF_IDX_OTP, pv_nfy_data);
    }
    else if (pv_nfy_data->e_nfy_type == CECM_NFY_TYPE_OPCODE)
    {
        switch(pv_nfy_data->u_code.e_opcode)
        {
        case CECM_OPCODE_INACT_SRC:
            _nav_cec_bgm_buf_remove(NAV_CEC_BUF_IDX_ACT_SRC);
        case CECM_OPCODE_ACT_SRC:
            _nav_cec_bgm_buf_add(NAV_CEC_BUF_IDX_ACT_SRC, pv_nfy_data);
            _nav_cec_bgm_buf_remove(NAV_CEC_BUF_IDX_RT_CHG);
            _nav_cec_bgm_buf_remove(NAV_CEC_BUF_IDX_RT_INFO);
            break;

        case CECM_OPCODE_IMG_VIEW_ON:
        case CECM_OPCODE_TXT_VIEW_ON:
        {
            UINT8 ui1_auto_on = APP_CFG_CEC_OFF;

            _nav_cec_bgm_buf_add(NAV_CEC_BUF_IDX_VIEW_ON, pv_nfy_data);

            a_cfg_get_cec_auto_on(&ui1_auto_on);
            if (ui1_auto_on == APP_CFG_CEC_ON)
            {
                b_power_on_tv = TRUE;
                DBG_LOG_PRINT (("[%s][%d] NAV_CEC_BUF_IDX_VIEW_ON(%X) \r\n", __FUNCTION__, __LINE__, ui1_auto_on));
            }
            break;
        }

        case CECM_OPCODE_ROUTING_CHG:
            _nav_cec_bgm_buf_add(NAV_CEC_BUF_IDX_RT_CHG, pv_nfy_data);
            break;
        case CECM_OPCODE_ROUTING_INFO:
            _nav_cec_bgm_buf_add(NAV_CEC_BUF_IDX_RT_INFO, pv_nfy_data);
            break;
        case CECM_OPCODE_GET_MENU_LANG:
            pt_cec_buf->b_reved_get_menu_lang = TRUE;
            if (pv_nfy_data->e_brdcst_type != CECM_BRDCST_TYPE_BRDCST){
                e_abort_reason = CECM_ABORT_REASON_REFUSED;
                b_abort_opcode = TRUE;
            }
            break;

        case CECM_OPCODE_USER_CTRL_PRESSED:
            if (pv_nfy_data->u_data.e_usr_ctrl == CECM_USER_CTRL_POWER ||
                pv_nfy_data->u_data.e_usr_ctrl == CECM_USER_CTRL_PWR_TOGGLE_FUNC ||
                pv_nfy_data->u_data.e_usr_ctrl == CECM_USER_CTRL_PWR_ON_FUNC)
            {
                b_power_on_tv = TRUE;
            }
            break;
        case CECM_OPCODE_REC_OFF:
        case CECM_OPCODE_REC_ON:
        case CECM_OPCODE_REC_STS:
        case CECM_OPCODE_REC_TV_SCREEN:
        case CECM_OPCODE_DECK_CTRL:
        case CECM_OPCODE_DECK_STS:
        case CECM_OPCODE_GIVE_DECK_STS:
        case CECM_OPCODE_PLAY:
        case CECM_OPCODE_GIVE_TUNER_DEV_STS:
        case CECM_OPCODE_SELECT_DIG_SVC:
        case CECM_OPCODE_TUNER_DEV_STS:
        case CECM_OPCODE_TUNER_STEP_DECR:
        case CECM_OPCODE_TUNER_STEP_INCR:
        case CECM_OPCODE_MENU_REQ:
        case CECM_OPCODE_MENU_STS:
        case CECM_OPCODE_SET_ANA_TIMER:
        case CECM_OPCODE_CLR_ANA_TIMER:
        case CECM_OPCODE_SET_DIG_TIMER:
        case CECM_OPCODE_CLR_DIG_TIMER:
        case CECM_OPCODE_SET_EXT_TIMER:
        case CECM_OPCODE_CLR_EXT_TIMER:
        case CECM_OPCODE_SET_TIMER_PROG_TITLE:
        case CECM_OPCODE_TIMER_CLRED_STS:
        case CECM_OPCODE_TIMER_STS:
        case CECM_OPCODE_CEC_VER:
        case CECM_OPCODE_SELECT_ANA_SVC:
        case CECM_OPCODE_GIVE_SYS_AUD_MOD_STS:
        case CECM_OPCODE_SYS_AUD_MOD_REQ:
        case CECM_OPCODE_GIVE_AUD_STS:
        case CECM_OPCODE_SET_AUD_RATE:
            if (pv_nfy_data->e_brdcst_type == CECM_BRDCST_TYPE_BRDCST){
                return;
            }
            e_abort_reason = CECM_ABORT_REASON_UNRECOGNIZED;
            b_abort_opcode = TRUE;
        default:
            return;
        }
    }

    if (b_power_on_tv == TRUE &&
        a_am_is_power_on() == FALSE)
    {
        DBG_LOG_PRINT (("[%s][%d] _nav_cec_bgm_power_on_tv \r\n",__FUNCTION__,__LINE__));
        nav_request_context_switch (_nav_cec_bgm_power_on_tv, NULL, NULL, NULL);
    }
    if (b_abort_opcode == TRUE)
    {
        nav_request_context_switch (_nav_cec_bgm_feature_abort,
                                    (VOID*)((UINT32)pv_nfy_data->e_sent_la),
                                    (VOID*)((UINT32)pv_nfy_data->e_sent_opcode),
                                    (VOID*)((UINT32)e_abort_reason));
    }
}


/**
 * @brief   Execute when received NAV_UI_MSG_POWER_ON
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_pre_init(
                cec_mw_nfy_fct* ppf_nfy_fct,
                cec_mw_nfy_fct  pf_def_nfy_fct
                )
{
    INT32                   i4_ret;
    PCL_WAKE_UP_REASON_T    e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
    UINT32                  ui4_wakeup_sub_reason;

    /* BGM Nfy buffer initialization. */
    c_memset (&t_nav_cec_bgm_buf, 0, sizeof (NAV_CEC_BGM_BUF_T));
    i4_ret = c_sema_create(&t_nav_cec_bgm_buf.h_nfy_mtx,
                           X_SEMA_TYPE_MUTEX,
                           X_SEMA_STATE_UNLOCK);
    if(i4_ret != OSR_OK)
    {
        NAV_CEC_DBG_LOG ("<CEC>Can't create mutex\n", i4_ret);
        return NAVR_FAIL;
    }

    *ppf_nfy_fct = _nav_cec_custom_nfy_fct;
    pf_default_nfy_fct = pf_def_nfy_fct;

    i4_ret = c_pcl_get_wakeup_reason (&e_wakeup_reason,
                                      &ui4_wakeup_sub_reason);
    if (i4_ret == PCLR_OK
        && e_wakeup_reason == PCL_WAKE_UP_REASON_RTC
        && (ui4_wakeup_sub_reason & PCL_WAKE_UP_SUB_REASON_QUIET_BOOT) != 0)
    {
        pf_dispatch_nfy_fct = _nav_cec_bgm_nfy_fct;
    }
    else
    {
        pf_dispatch_nfy_fct = pf_default_nfy_fct;
    }

    c_cecm_set_support_cec_ver(nav_cec_get_mw_handle(),NAV_CEC_VER_ID);
    return NAVR_OK;
}

/**
 * @brief   Execute when received NAV_UI_MSG_POWER_ON
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_power_on_handler(
                    VOID
                    )
{
    NAV_CEC_BGM_BUF_T* pt_nav_cec_bgm_buf = &t_nav_cec_bgm_buf;
    CECM_NFY_T t_nfy_data;

    c_sema_lock (pt_nav_cec_bgm_buf->h_nfy_mtx, X_SEMA_OPTION_WAIT);
    while(_nav_cec_bgm_buf_get(&t_nfy_data) == NAVR_OK)
    {
        c_sema_unlock(pt_nav_cec_bgm_buf->h_nfy_mtx);
        pf_default_nfy_fct(&t_nfy_data, NULL, 0);
    }

    pf_dispatch_nfy_fct = pf_default_nfy_fct;
    c_sema_unlock(pt_nav_cec_bgm_buf->h_nfy_mtx);
    DBG_LOG_PRINT(("<CEC AP> nav_cec_custom_power_on_handler call nav_cec_perform_cec_onoff_operation\n\r"));
    nav_cec_perform_cec_onoff_operation (TRUE);

    return NAVR_OK;
}

#if 0
static UINT32 _nav_cec_custom_get_amp_5v(UINT8 *pui1_5v_status)  //ke_vizio_20160929 add
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(pui1_5v_status);


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_5V_STATUS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}

#else

static UINT32 _nav_cec_custom_get_hdmi_5v(UINT8    hdmi_port,
                                          UINT8   *pui1_5v_status)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info = {0};
    DRV_CUSTOM_CUST_SPEC_TYPE_T  get_hdmi_flag;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(pui1_5v_status);

    switch (hdmi_port)
    {
        default:
            DBG_ERROR(("[%s] wrong hdmi_port : %d\n", __FUNCTION__, hdmi_port));
            return CECR_FAIL;

        case NAV_CEC_HDMI1:
            get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_5V_STATUS;
            break;

        case NAV_CEC_HDMI2:
            get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI2_5V_STATUS;
            break;

        case NAV_CEC_HDMI3:
            get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI3_5V_STATUS;
            break;

        case NAV_CEC_HDMI4:
            get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI4_5V_STATUS;
            break;
    }


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = get_hdmi_flag;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("[%s] i4_ret : %d\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}
#endif

VOID nav_cec_custom_power_on_flag_set(VOID)
{
    UINT8   ui1_5v_status = 0;

    DBG_LOG_PRINT (("[%s][%d] \n", __FUNCTION__, __LINE__));

    a_cfg_cust_set_hide_from_input(0);
    g_b_power_on = TRUE;

    if(g_b_msg_before_power_on)
    {
        a_revolt_info_get_timeout();
        g_t_toast.e_toast_style  = WDK_WARNING_TOAST;
        g_t_toast.e_string_style = WDK_STRING_STRING;
        g_t_toast.pf_cb = _nav_cec_custom_dev_toast_cb_fct;
        g_t_toast.style.style_4.w2s_str = (VOID*)g_w2s_str_hdmiport;
        _cec_info_send_string_to_nav(&g_t_toast);
        g_b_msg_before_power_on = FALSE;
    }

    _nav_cec_custom_get_hdmi_5v(NAV_CEC_HDMI1, &ui1_5v_status);
    if(ui1_5v_status == 1) {
        _cec_hot_plug_dev_status_update(NAV_CEC_HDMI1, ui1_5v_status);
    }
    else {
        b_last_5v_status = FALSE;
    }

    _nav_cec_custom_get_hdmi_5v(NAV_CEC_HDMI2, &ui1_5v_status);
    if(ui1_5v_status == 1) {
        _cec_hot_plug_dev_status_update(NAV_CEC_HDMI2, ui1_5v_status);
    }

    _nav_cec_custom_get_hdmi_5v(NAV_CEC_HDMI3, &ui1_5v_status);
    if(ui1_5v_status == 1) {
        _cec_hot_plug_dev_status_update(NAV_CEC_HDMI3, ui1_5v_status);
    }

    _nav_cec_custom_get_hdmi_5v(NAV_CEC_HDMI4, &ui1_5v_status);
    if(ui1_5v_status == 1) {
        _cec_hot_plug_dev_status_update(NAV_CEC_HDMI4, ui1_5v_status);
    }

}

BOOL cec_custom_allow_visible (VOID)
{
    do
    {
        if(a_wzd_is_oobe_mode() == TRUE)
        {
            DBG_INFO(("%s,%d [cec] don't show dialog in oobe status \r\n",__FUNCTION__,__LINE__));
            break ;
        }
        else if(a_slogo_is_show())
        {
            DBG_INFO(("%s,%d [cec] don't show dialog while vlogo showing \r\n",__FUNCTION__,__LINE__));
            break;
        }
        else if(a_am_is_power_on() == FALSE)
        {
            DBG_INFO(("%s,%d [cec] don't show dialog while TV is not power on \r\n",__FUNCTION__,__LINE__));
            break;
        }
        else if (g_b_amp_nfy_show)
        {
            DBG_INFO(("%s,%d [cec] don't show dialog while amp nfy exist \r\n",__FUNCTION__,__LINE__));
            break;
        }

        return TRUE;

    }while(0);

    return FALSE;
}

/**
 * @brief   Execute when received NAV_UI_MSG_BACKGROUND_MODE
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_bgm_handler(
                    BOOL        b_bgm
                    )
{
    if (b_bgm == TRUE)
    {
        pf_dispatch_nfy_fct = _nav_cec_bgm_nfy_fct;
    }
    return NAVR_OK;
}


/******************************************************************************/
/**
 * @brief   This function get get_device_connect_status
 * @same    same as _nav_cec_sac_get_sam_status
 * @param   pb_sam_on [in] The status of SAM mode.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
INT32 nav_cec_custom_get_device_connect_status (BOOL* connect_status)
{
    UINT8 ui1_icl_val;
    SIZE_T z_size = sizeof(UINT8);
    INT32 i4_ret;

    NAV_CEC_LOG_I("Enter\n\r");

    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    IS_CECR_OK (i4_ret);

    NAV_CEC_LOG_I("ui1_icl_val=%d\n\r", ui1_icl_val);

    if (ui1_icl_val == ICL_CEC_SAC_STATUS_ON)
    {
        *connect_status = TRUE;
    }
    else
    {
        *connect_status = FALSE;
    }

    return NAVR_OK;
}


#ifdef APP_WIZARD_CUSTOM_SUPPORT

/**
 * @brief   Execute when received message CECM_MSGCODE_5V_PWR ,FALSE
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_cec_custom_is_mute_under_wzd(VOID)
{
    CHAR  s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;

    a_am_get_active_app (s_active_app) ;

    /* if the page is show or the current active app is wizard should mute tvSpeaker*/
    if (c_strcmp(s_active_app, WZD_NAME) == 0)
    {
        DBG_LOG_PRINT(("\n####%s(%d)  current active app is WZD.\n",__FUNCTION__,__LINE__));
        if (a_wzd_is_keep_mute()==FALSE)
        {
            DBG_LOG_PRINT(("\n####%s(%d)  a_wzd_is_keep_mute return FALSE.\n",__FUNCTION__,__LINE__));
            return NAVR_OK;
        }
    }
    else
    {
        DBG_LOG_PRINT(("\n####%s(%d)  current active app is not WZD.\n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }
    return NAVR_NO_ACTION;
}

#endif // #ifdef APP_WIZARD_CUSTOM_SUPPORT


// change EDID to support or not DTS through d-interface
INT32 nav_cec_sac_drv_set_dts_enable(BOOL b_enable)
{
    DBG_LOG_PRINT(("{nav_cec_custom} _nav_cec_sac_drv_set_dts_enable %d\n\r",b_enable));

    INT32 i4_ret = NAVR_OK;
    DRV_CUST_OPERATION_INFO_T t_op_info;
    UINT8 ui1_dts_enable = b_enable == TRUE ? 1 : 0;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_misc_set_info.e_misc_type = DRV_CUSTOM_CUST_SPEC_SET_DTS_ENABLE;
    t_op_info.u.t_misc_set_info.pv_set_info = (VOID*)&ui1_dts_enable;
    t_op_info.u.t_misc_set_info.z_size = sizeof(UINT8);
    t_op_info.u.t_misc_set_info.b_store = TRUE;

    i4_ret = c_rm_set_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    sizeof(DRV_CUST_OPERATION_INFO_T));
    return i4_ret;
}

UINT32 nav_cec_custom_get_spd_info(UINT8 port, UINT8* description, UINT8 u8BufSize)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT8                        spd_info[30] = {0};
    SIZE_T                       z_size = sizeof(spd_info);

    //DBG_LOG_PRINT(("[NAV][CEC][%s] port:%d \n", __FUNCTION__, port ));

    if ( (description == NULL)
       ||(u8BufSize < 18) )
    {
        return NAVR_FAIL;
    }

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    if(0 == port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_SPD_INFO;
    }
    else if(1 == port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI2_SPD_INFO;
    }
    else if(2 == port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI3_SPD_INFO;
    }
    else if(3 == port)
    {
        t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI4_SPD_INFO;
    }
    else
    {
        DBG_LOG_PRINT(("[NAV][CEC][%s] Warning: Invalid port=%d \n", __FUNCTION__, port ));
        return NAVR_FAIL;
    }

    //DBG_LOG_PRINT(("[NAV][CEC] e_cust_spec_type:0x%X \n", __FUNCTION__, t_op_info.u.t_cust_spec_get_info.e_cust_spec_type ));

    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)spd_info;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != NAVR_OK)
    {
        DBG_ERROR(("[%s][%d] i4_ret : %d \n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    c_memcpy(description, spd_info+8, 17);
    
    // Fix for Xbox Spd info when VRR on
    if( 0 != c_strlen((char*)description) )
    {
        if(0 == port)
        {
            c_memcpy(spd_info_port0, description, 17);
        }
        else if(1 == port)
        {
            c_memcpy(spd_info_port1, description, 17);
        }
        else if(2 == port)
        {
            c_memcpy(spd_info_port2, description, 17);
        }
        else if(3 == port)
        {
            c_memcpy(spd_info_port3, description, 17);
        }
     }

    UINT8   ui1_5v_status = 0; 
    _nav_cec_custom_get_hdmi_5v(port + 1, &ui1_5v_status);
    switch (port)
    {   
        case 0:
            c_memcpy(spd_info_first, spd_info_port0, 17);
            if (ui1_5v_status == 0)
                c_strcpy(spd_info_port0, "");
            break;
        case 1:
            c_memcpy(spd_info_first, spd_info_port1, 17);
            if (ui1_5v_status == 0)
                c_strcpy(spd_info_port1, "");
            break;  
        case 2:
            c_memcpy(spd_info_first, spd_info_port2, 17);
            if (ui1_5v_status == 0)
                c_strcpy(spd_info_port2, "");
            break;
        case 3:
            c_memcpy(spd_info_first, spd_info_port3, 17);
            if (ui1_5v_status == 0)
                c_strcpy(spd_info_port3, "");
            break;
        default:
            DBG_LOG_PRINT(("[NAV][CEC][%s] Warning: Invalid port=%d \n", __FUNCTION__, port ));
            return NAVR_FAIL;
    }
    
    BOOL b_is_driver_detect_VRR = FALSE;
    b_is_driver_detect_VRR = a_cfg_cust_is_VRR_enable_and_driver_detect_VRR();
    UINT8   strlen_first= c_strlen((char*)spd_info_first);
    if(b_is_driver_detect_VRR == TRUE && 0 != strlen_first)
    {
        c_memcpy(description, spd_info_first, 17);
        DBG_LOG_PRINT(("{%s,%d} b_is_driver_detect_VRR=%d,description=%s\n",__FUNCTION__, __LINE__, b_is_driver_detect_VRR,(char*)description));
    } 

    DBG_LOG_PRINT(("[NAV][CEC]nav_cec_custom_get_spd_info[%d] = {%s}\n", port, (char*)description));

    return NAVR_OK;
}

INT32 cli_nav_get_spd_info(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 description[30] = {0};
    int port = atoi(pps_argv[1]);

    nav_cec_custom_get_spd_info(port, description, sizeof(description));

    return NAVR_OK;
}

//==============================================================
BOOL nav_cec_custom_get_enable_soundbarsettings(VOID)
{
    return amp_vndr_info.items_enable.soundbarsettings;
}

BOOL nav_cec_custom_get_soundbarsettings_ready(VOID)
{
    return amp_vndr_info.sb_is_ready;
}

BOOL nav_cec_custom_get_enable_eq(VOID)
{
    return amp_vndr_info.items_enable.eq;
}

BOOL nav_cec_custom_get_enable_bass(VOID)
{
    return amp_vndr_info.items_enable.bass;
}

BOOL nav_cec_custom_get_enable_treble(VOID)
{
    return amp_vndr_info.items_enable.treble;
}

BOOL nav_cec_custom_get_enable_dialogue(VOID)
{
    return amp_vndr_info.items_enable.dialogue;
}

BOOL nav_cec_custom_get_enable_subwoofer(VOID)
{
    return amp_vndr_info.items_enable.subwoofer;
}

BOOL nav_cec_custom_get_enable_nightmode(VOID)
{
    return amp_vndr_info.items_enable.nightmode;
}

BOOL nav_cec_custom_get_enable_virtual(VOID)
{
    return amp_vndr_info.items_enable.virtul;
}

BOOL nav_cec_custom_get_eq_mode_enable_music(VOID)
{
    return amp_vndr_info.eq_mode_type_enable.music;
}

BOOL nav_cec_custom_get_eq_mode_enable_movie(VOID)
{
    return amp_vndr_info.eq_mode_type_enable.movie;
}

BOOL nav_cec_custom_get_eq_mode_enable_game(VOID)
{
    return amp_vndr_info.eq_mode_type_enable.game;
}

BOOL nav_cec_custom_get_eq_mode_enable_direct(VOID)
{
    return amp_vndr_info.eq_mode_type_enable.direct;
}

BOOL nav_cec_custom_get_eq_mode_enable_dialogue(VOID)
{
    return amp_vndr_info.eq_mode_type_enable.dialogue;
}

UINT8 nav_cec_custom_get_enable_eq_mode_type(VOID)
{
    return amp_vndr_info.items_type.eq;
}

VOID nav_cec_custom_set_enable_eq_mode_type(UINT8 eq_mode_type)
{
    amp_vndr_info.items_type.eq = eq_mode_type;
}

UINT8 nav_cec_custom_get_enable_eq_mode_valid_num(VOID)
{
    return amp_vndr_info.eq_mode_valid_num;
}

UINT8 nav_cec_custom_get_enable_bass_type(VOID)
{
    return amp_vndr_info.items_type.bass;
}

UINT8 nav_cec_custom_get_enable_treble_type(VOID)
{
    return amp_vndr_info.items_type.treble;
}

UINT8 nav_cec_custom_get_enable_dialogue_type(VOID)
{
    return amp_vndr_info.items_type.dialogue;
}

UINT8 nav_cec_custom_get_enable_subwoofer_type(VOID)
{
    return amp_vndr_info.items_type.subwoofer;
}

UINT8 nav_cec_custom_get_enable_nightmode_type(VOID)
{
    return amp_vndr_info.items_type.nightmode;   
}

UINT8 nav_cec_custom_get_enable_virtualx_type(VOID)
{
    return amp_vndr_info.items_type.virtulx;
}

//======================================================================
INT32 nav_cec_custom_set_eq_mode(INT32 i4_val)
{    
    INT32 i4_ret = CECMR_OK;
    i4_ret = nav_cec_sac_set_EQ_mode(i4_val);
    
    if(i4_ret == CECMR_OK)
    amp_vndr_info.items_type.eq = (UINT8) i4_val;
    
    return i4_ret;
}

INT32 nav_cec_custom_set_bass_val(INT32 i4_val)
{
    INT32 i4_ret = CECMR_OK;
    i4_ret = nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_BASS, i4_val);

    if(i4_ret == CECMR_OK)
    amp_vndr_info.items_type.bass = (UINT8)i4_val;
    
    return i4_ret;
}

INT32 nav_cec_custom_set_treble_val(INT32 i4_val)
{
    INT32 i4_ret = CECMR_OK;
    i4_ret = nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_TREBLE, i4_val);

    if(i4_ret == CECMR_OK)
    amp_vndr_info.items_type.treble = (UINT8)i4_val;
    
    return i4_ret;
}

INT32 nav_cec_custom_set_dialogue_val(INT32 i4_val)
{
    INT32 i4_ret = CECMR_OK;
    i4_ret = nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_DIALOGUE, i4_val);

    if(i4_ret == CECMR_OK)
    amp_vndr_info.items_type.dialogue = (UINT8)i4_val;
    
    return i4_ret;
}

INT32 nav_cec_custom_set_subwoofer_val(INT32 i4_val)
{
    INT32 i4_ret = CECMR_OK;
    i4_ret = nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_SUBWOOFER, i4_val);

    if(i4_ret == CECMR_OK)
    amp_vndr_info.items_type.subwoofer = (UINT8)i4_val;

    return i4_ret;
}

INT32 nav_cec_custom_set_nightmode_val(INT32 i4_val)
{
    INT32 i4_ret = CECMR_OK;
    i4_ret = nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_NIGHTMODE, i4_val);

    if(i4_ret == CECMR_OK)
    amp_vndr_info.items_type.nightmode = (UINT8)i4_val;
    
    return i4_ret;
}

INT32 nav_cec_custom_set_virtualx_val(INT32 i4_val)
{
    INT32 i4_ret = CECMR_OK;
    i4_ret = nav_cec_sac_set_AQ_status(SOUNDBAR_AQ_SETTING_VIRTUALX, i4_val);

    if(i4_ret == CECMR_OK)
    amp_vndr_info.items_type.virtulx = (UINT8)i4_val;
    
    return i4_ret;
}

INT32 nav_cec_custom_set_speakertest_val(INT32 i4_val)
{
     INT32 i4_ret = CECMR_OK;
     i4_ret = nav_cec_sac_set_SpeakerTest();

     if(i4_ret == CECMR_OK)
     amp_vndr_info.items_type.speakerTest = (UINT8)i4_val;
     return i4_ret;
}

INT32 nav_cec_custom_set_info_val(INT32 i4_val)
{
     INT32 i4_ret = CECMR_OK;
     i4_ret = nav_cec_sac_set_Info();

     if(i4_ret == CECMR_OK)
     amp_vndr_info.items_type.info = (UINT8)i4_val;
     return i4_ret;
}

#endif /* APP_CEC2_SUPPORT */

#endif /* APP_CEC_SUPPORT */


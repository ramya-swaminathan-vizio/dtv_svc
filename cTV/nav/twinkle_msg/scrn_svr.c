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
 * $RCSfile: scrn_svr.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_sb.h"
#include "u_sb_atsc_eng.h"
#include "u_pcl.h"

#include "c_wgl.h"
#include "c_handle.h"
#include "c_svl.h"
#include "c_svctx.h"
#include "c_evctx.h"
#include "c_uc_str.h"
#include "c_os.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_network.h"
#include "app_util/a_cfg.h"
#include "mmp/a_mmp.h"

#include "msgconvert/a_msgconvert.h"
#include "res/msgconvert/msgconvert_custom.h"
#include "res/menu2/menu_custom.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif

#include "app_client.h"
#include "wizard_anim/a_wzd.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/simple_logo/a_simple_logo.h"
#include "res/menu2/menu_custom.h"
#include "nav/twinkle_msg/scrn_svr.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/retail_mode_view.h"
#endif

#include "am/a_am.h"

#include "res/app_util/config/acfg_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifndef SCRN_SVR_NEXT_MOVE_TIMEOUT
#define SCRN_SVR_NEXT_MOVE_TIMEOUT                  (200) /* in ms */
#endif

#ifndef SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT
#define SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT          (200) /* in ms */
#endif

#ifndef SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT_APP_XNG
#define SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT_APP_XNG  (200) /* in ms */
#endif

#ifndef SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT_CAST
#define SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT_CAST     (30*1000) /* 30 sec */
#endif

#define _MSG_SET_MSG_ID(_tv_win_id, _msg_id)                                   \
{                                                                              \
    DBG_LOG_PRINT(("[SCRN_SVR] [%s][%d] msg_id[%d]: %X \n", __FUNCTION__, __LINE__, _tv_win_id, _msg_id));    \
    t_g_scrn_svr.t_msgs[_tv_win_id].e_type        = SCRN_SVR_MSG_TYPE_MSG_ID;  \
    t_g_scrn_svr.t_msgs[_tv_win_id].u.e_msg_id    = _msg_id;                   \
}

#define _MSG_SET_MLM_KEY(_tv_win_id, _mlm_key)                                 \
{                                                                              \
    DBG_INFO(("[SCRN_SVR] [%s][%d] mlm_key[%d]: %X \n", __FUNCTION__, __LINE__, _tv_win_id, _mlm_key));   \
    t_g_scrn_svr.t_msgs[_tv_win_id].e_type        = SCRN_SVR_MSG_TYPE_MLM_KEY; \
    t_g_scrn_svr.t_msgs[_tv_win_id].u.ui2_mlm_key = _mlm_key;                  \
}

#define _MSG_SET_UNKNOWN(_tv_win_id)                                           \
{                                                                              \
    DBG_INFO(("[SCRN_SVR] [%s][%d] SCRN_SVR_MSG_TYPE_UNKNOWN\n", __FUNCTION__, __LINE__));  \
    t_g_scrn_svr.t_msgs[_tv_win_id].e_type = SCRN_SVR_MSG_TYPE_UNKNOWN;        \
}

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
SCRN_SVR_T  t_g_scrn_svr;
static HANDLE_T     h_temp_timer;//For some temporary status,will not need pop up the screen message

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_handle_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static INT32 _scrn_svr_check_to_activate(
                    SCRN_SVR_T*                 pt_this,
                    BOOL                        b_from_timeout
                    );
static BOOL _scrn_svr_is_cast_source(VOID);
static INT32 _scrn_svr_get_crnt_isl(ISL_REC_T* pt_isl_rec);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_is_rgb_inputs
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _scrn_svr_is_rgb_inputs(VOID)
{
    INT32                       i4_ret = -1;
    ISL_REC_T                   t_isl_rec;
    ISL_REC_T*                  pt_isl_rec = &t_isl_rec;

    i4_ret = nav_get_isl_rec( TV_WIN_ID_MAIN, pt_isl_rec );
    if(i4_ret != NAVR_OK)
    {
        DBG_ERROR(("nav_get_isl_rec get isl error! line =%d\n",__LINE__));
        return FALSE;
    }

    if( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_VGA )
    {
        return TRUE;
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_show_crnt_err_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_show_crnt_err_msg(
                    VOID
                    )
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;
    if (pt_this->b_enable == FALSE)
    {
        return NAVR_OK;
    }

    if (_scrn_svr_is_cast_source())
    {
        return NAVR_OK;
    }

    UTF16_T*    pw2s_string = nav_get_crnt_err_msg();
    if (!pw2s_string || 0 == c_uc_w2s_strlen(pw2s_string))
    {
        DBG_INFO(("[SCRN_SVR] crnt err msg is empty in %s\r\n", __FUNCTION__));

        if (pt_this->b_is_on)
        {
            nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
        }

        return NAVR_FAIL;
    }

#ifdef APP_RETAIL_MODE_SUPPORT
    if(retail_mode_view_logo_is_show()== TRUE)
    {
        DBG_INFO(("[SCRN_SVR] retail mode logo is showing in %s\r\n", __FUNCTION__));
        nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
        return NAVR_FAIL;
    }
#endif

    if(a_slogo_is_show())
    {
        DBG_LOG_PRINT(("LOGO is showing\n"));
        nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
        return NAVR_FAIL;
    }
    pt_this->b_is_on = TRUE;

    return scrn_svr_view_show(
                    &(pt_this->t_view),
                    pw2s_string,
                    pt_this->e_toast_style
                    );
}

static VOID _scrn_svr_set_err_title(
                    UTF16_T*                    pw2s_err_title
                    )
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;

    if (pw2s_err_title != NULL)
    {
        c_uc_w2s_strncpy(pt_this->t_view.w2s_err_title, pw2s_err_title, MAX_ERR_MSG_SIZE);
        pt_this->t_view.w2s_err_title[MAX_ERR_MSG_SIZE] = 0;
    }
    else
    {
        pt_this->t_view.w2s_err_title[0] = 0;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_set_err_msg_id
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_set_err_msg_id(SCRN_SVR_MSG_T*  pt_msg)
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;

    DBG_LOG_PRINT(("[SCRN_SVR][%s %d] pt_msg->e_type = %d \r\n", __FUNCTION__,__LINE__, pt_msg->e_type));

    switch (pt_msg->e_type)
    {
        case SCRN_SVR_MSG_TYPE_MSG_ID:
            DBG_LOG_PRINT(("[%s][%d] (e_msg_id: %d) \n", __FUNCTION__, __LINE__, pt_msg->u.e_msg_id));
            if (MSG_STR_ID_NO_SIGNAL == pt_msg->u.e_msg_id)
            {
                pt_this->e_toast_style = TOAST_STYLE_NO_SIGNAL_1;
            }
            else if (MSG_STR_ID_ACQUIRE_SIGNAL == pt_msg->u.e_msg_id)
            {
                pt_this->e_toast_style = TOAST_STYLE_SIGNAL_ACQUIRE;
            }
            else if (MSG_STR_ID_NO_CH_IN_LIST == pt_msg->u.e_msg_id)
            {
                pt_this->e_toast_style = TOAST_STYLE_MSG;
            }
            else if ( (MSG_STR_ID_AUDIO_PROG == pt_msg->u.e_msg_id)
                    ||(MSG_STR_ID_HD_VIDEO_NOT_SUPPORT== pt_msg->u.e_msg_id)
                    ||(MSG_STR_ID_NO_AUDIO_VIDEO== pt_msg->u.e_msg_id) )
            {
                pt_this->e_toast_style = TOAST_STYLE_CENTER_DIALOG;
            }
            else
            {
               break;
            }
            nav_set_crnt_err_msg_id(pt_msg->u.e_msg_id);
            break;

        case SCRN_SVR_MSG_TYPE_MLM_KEY:
            DBG_LOG_PRINT(("[SCRN_SVR][%d] ui2_mlm_key = 0x%X \r\n", __LINE__, pt_msg->u.ui2_mlm_key));
            if (pt_msg->u.ui2_mlm_key < MLM_NAV_NUM_KEY)
            {
                if (MLM_NAV_KEY_MSG_NO_SIGNAL == pt_msg->u.ui2_mlm_key)
                {
                    pt_this->e_toast_style = TOAST_STYLE_NO_SIGNAL_1;
                }
                else if (MLM_NAV_KEY_MSG_NO_CH_LIST == pt_msg->u.ui2_mlm_key)
                {
                    pt_this->e_toast_style = TOAST_STYLE_MSG;
                }
                else if (MLM_NAV_KEY_NW_CONNECTION_LOST_MSG == pt_msg->u.ui2_mlm_key ||
                         MLM_NAV_KEY_CAST_NOT_SETUP_MSG == pt_msg->u.ui2_mlm_key)
                {
                    pt_this->e_toast_style = TOAST_STYLE_MSG_WITH_TITLE_CONTENT;
                    _scrn_svr_set_err_title(MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_msg->u.ui2_mlm_key-1));
                }
                else if(MLM_NAV_KEY_NAV_SCRAMBLED_VIDEO == pt_msg->u.ui2_mlm_key)
                {
                    pt_this->e_toast_style = TOAST_STYLE_CENTER_DIALOG;
                }
                else
                {
                    break;
                }

                nav_set_crnt_err_msg(
                        MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_msg->u.ui2_mlm_key)
                        );
            }
            break;

        default:
            break;
    }

    DBG_LOG_PRINT(("[SCRN_SVR] << [%s][%d] (e_toast_style: %X) \n", __FUNCTION__, __LINE__, pt_this->e_toast_style));
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_set_crnt_err_msg_id
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_set_crnt_err_msg_id(
                    TV_MODE_T                       e_tv_mode,
                    TV_WIN_ID_T                     e_crnt_tv_win_id,
                    TV_WIN_ID_T                     e_focus_tv_win_id,
                    SCRN_SVR_MSG_T*                 pt_msg
                    )
{
    if (e_tv_mode != TV_MODE_TYPE_NORMAL) {
        return NAVR_OK;
    }

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return NAVR_OK;
    }

    if (e_crnt_tv_win_id == e_focus_tv_win_id)
    {
        _scrn_svr_set_err_msg_id(pt_msg);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svctx_nfy_fct
 * Description
 *  Do some dirty trick
 *  - hide screen saver in service context's thread to avoid
 *    video and OSD not controlled in the same thread
 *  6/29/2007 Weider Chang (wait better solution to replace this)
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svctx_nfy_handler(
    VOID*                       pv_tag1,
    VOID*                       pv_tag2,
    VOID*                       pv_tag3)
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;
    SVCTX_NTFY_CODE_T e_code = (SVCTX_NTFY_CODE_T)(UINT32)pv_tag1;

    switch(e_code)
    {
        case SVCTX_NTFY_CODE_STOPPED:
        case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
            if (e_code == SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE)
            {
                VSH_SRC_RESOLUTION_INFO_T t_res;
                INT32                     i4_ret;
                DBG_INFO(("[SCRN_SVR][%s %d] SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE\r\n", __FUNCTION__,__LINE__));
                c_memset (&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T)) ;
                i4_ret = nav_get_crnt_video_res_info(TV_WIN_ID_MAIN, &t_res);
                if (i4_ret == NAVR_OK && (t_res.ui4_width == 0 || t_res.ui4_height == 0 || VSH_SRC_TIMING_NOT_SUPPORT == t_res.e_timing_type )) {
                    /* invalid resolution */
                     DBG_INFO(("[SCRN_SVR][%s %d] invalid resolution or timing\r\n", __FUNCTION__,__LINE__));
                    break;
                }
            }
            else if(SVCTX_NTFY_CODE_STOPPED == e_code )
            {
                CHAR                        s_disp_name[33] = {0};
                UINT8                       ui1_input_id = 0;
                ISL_REC_T                   t_isl_rec;

                a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                a_cfg_get_input_src(s_disp_name, &ui1_input_id);
                a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
                if (t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL)
                    break;
            }
            DBG_INFO(("[SCRN_SVR][%s %d] e_toast_style = %d \n",__FUNCTION__,__LINE__,pt_this->e_toast_style));
           scrn_svr_view_hide(&(pt_this->t_view), pt_this->e_toast_style);
            break;
        default:
            break;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svctx_nfy_fct
 * Description
 *  Do some dirty trick
 *  - hide screen saver in service context's thread to avoid
 *    video and OSD not controlled in the same thread
 *  6/29/2007 Weider Chang (wait better solution to replace this)
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svctx_nfy_fct(
                    HANDLE_T                        h_svctx,
                    SVCTX_COND_T                    e_nfy_cond,
                    SVCTX_NTFY_CODE_T               e_code,
                    STREAM_TYPE_T                   e_stream_type,
                    VOID*                           pv_nfy_tag
                    )
{
    nav_request_context_switch(_scrn_svctx_nfy_handler, (VOID* )e_code, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_store_demo_is_on
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _scrn_svr_store_demo_is_on(VOID)
{
    ACFG_RETAIL_MODE_T      t_retail_mode   = ACFG_RETAIL_MODE_HOME;

#ifdef APP_RETAIL_MODE_SUPPORT
    INT32                   i4_ret          = 0;
    i4_ret = a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (APP_CFGR_OK != i4_ret)
    {
        DBG_INFO(("[SCRN_SVR] acfg get_retail_mode_setting failed !!!!\n"));
        return FALSE;
    }
#endif

    if (t_retail_mode == ACFG_RETAIL_MODE_NORMAL ||
        t_retail_mode == ACFG_RETAIL_MODE_NO_PLAYING)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_is_cast_source
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _scrn_svr_is_cast_source(VOID)
{
    INT32                       i4_ret = 0;
    TV_WIN_ID_T                 e_focus_id = TV_WIN_ID_MAIN;
    ISL_REC_T                   t_isl_rec;

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    NAV_LOG_ON_FAIL(i4_ret);

    if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type &&
        DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _scrn_svr_nw_notify_handler
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _scrn_svr_nw_notify_handler(
    VOID*          pv_tag1,
    VOID*          pv_tag2,
    VOID*          pv_tag3
)
{
    SCRN_SVR_T*         pt_this = &t_g_scrn_svr;
    NW_NFY_ID_T         e_nfy_id = (NW_NFY_ID_T)((UINT32)pv_tag2);
    WLAN_NOTIFY_MSG_T   e_wlan_msg = (WLAN_NOTIFY_MSG_T)((UINT32)pv_tag3);
    TV_WIN_ID_T         e_win_id = TV_WIN_ID_MAIN;

    switch (e_nfy_id)
    {
        case NW_NFY_ID_ETHERNET_PLUGIN:
        {
            DBG_INFO(("\n[SVR] %s,%d,NW_NFY_ID_ETHERNET_PLUGIN\n", __FUNCTION__, __LINE__));

            _MSG_SET_MSG_ID(e_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
            _scrn_svr_set_err_msg_id(&(pt_this->t_msgs[e_win_id]));

            nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
            break;
        }
        case NW_NFY_ID_ETHERNET_UNPLUG:
        {
            DBG_INFO(("\n[SVR] %s,%d,NW_NFY_ID_ETHERNET_UNPLUG\n", __FUNCTION__, __LINE__));
            break;
        }
#ifdef APP_NETWORK_WIFI_SUPPORT
        case NW_NFY_ID_WLAN_START_IND:
        {
            DBG_INFO(("\n[SVR] %s,%d,NW_NFY_ID_WLAN_START_IND\n", __FUNCTION__, __LINE__));

            if (a_nw_is_ethernet_plugin())
            {
                break;
            }

            break;
        }
        case NW_NFY_ID_WLAN_ASSOCIATE:
        case NW_NFY_ID_WLAN_WPS_ASSOCIATE:
        {
            if (a_nw_is_ethernet_plugin())
            {
                break;
            }

            if (e_wlan_msg == WLAN_NFY_MSG_OK)
            {
                DBG_INFO(("\n[SVR] %s,%d,NW_NFY_ID_WLAN_ASSOCIATE success\n", __FUNCTION__, __LINE__));

                _MSG_SET_MSG_ID(e_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
                _scrn_svr_set_err_msg_id(&(pt_this->t_msgs[e_win_id]));

                nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
            }
            else
            {
                DBG_INFO(("\n[SVR] %s,%d,NW_NFY_ID_WLAN_ASSOCIATE msg: %u\n",
                                __FUNCTION__, __LINE__, e_wlan_msg));
            }

            break;
        }
#endif

        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _scrn_svr_nw_notify_callback
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _scrn_svr_nw_notify_callback(
    VOID*          pv_tag,
    NW_NFY_ID_T    e_nfy_id,
    VOID*          pv_nfy_param
)
{
    if (TRUE == _scrn_svr_is_cast_source() || a_c4tv_apron_check_cast_state())
    {
        nav_request_context_switch(_scrn_svr_nw_notify_handler,
                              (VOID*)pv_tag,
                              (VOID*)e_nfy_id,
                              (VOID*)pv_nfy_param);
    }
}

/*----------------------------------------------------------------------------
 * Name: _scrn_svr_icl_msg_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _scrn_svr_icl_msg_hdlr(
                    VOID*           pv_unused1,
                    VOID*           pv_unused2,
                    VOID*           pv_unused3
                    )
{
    SCRN_SVR_T*         pt_this = &t_g_scrn_svr;
    INT32               i4_ret  = NAVR_OK;
    UINT8               ui1_status = ICL_RECID_CAST_SRC_STATUS_FALSE;
    SIZE_T              z_size = ICL_RECID_CAST_SRC_STATUS_SIZE;
    TV_WIN_ID_T         e_win_id = TV_WIN_ID_MAIN;

    /* get icl flag change status */
    i4_ret = a_icl_get (ICL_MAKE_ID(ICL_GRPID_CAST_SRC_STATUS, ICL_RECID_CAST_SRC_STATUS), &ui1_status, &z_size);
    if (ICLR_OK != i4_ret)
    {
        return;
    }

    DBG_INFO(("[SCRN_SVR] icl cast status = %d.\n", ui1_status));

    /* chg source to cast, need check warning msg */
    if (ICL_RECID_CAST_SRC_STATUS_FALSE == ui1_status)
    {
        pt_this->b_need_delay_show_network_lost = FALSE;

        if ((SCRN_SVR_MSG_TYPE_MLM_KEY == pt_this->t_msgs[e_win_id].e_type) &&
            (MLM_NAV_KEY_NW_CONNECTION_LOST_MSG == pt_this->t_msgs[e_win_id].u.ui2_mlm_key ||
             MLM_NAV_KEY_CAST_NOT_SETUP_MSG == pt_this->t_msgs[e_win_id].u.ui2_mlm_key))
        {
            _MSG_SET_MSG_ID(e_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
            _scrn_svr_set_err_msg_id(&(pt_this->t_msgs[e_win_id]));
            return;
        }
    }
    else
    {
        _MSG_SET_MSG_ID(e_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
        nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
        return;
    }
}

static VOID _icl_mmp_msg_hdlr(
                    VOID*           pv_unused1,
                    VOID*           pv_unused2,
                    VOID*           pv_unused3
                    )
{
    SCRN_SVR_T*         pt_this = &t_g_scrn_svr;
    INT32               i4_ret  = NAVR_OK;
    UINT8               ui1_status = ICL_RECID_CAST_SRC_STATUS_FALSE;
    SIZE_T              z_size = ICL_RECID_CAST_SRC_STATUS_SIZE;

    /* get icl flag  change status */
    i4_ret = a_icl_get (ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_MEDIA_PLAY_STATUS), &ui1_status, &z_size);
    if (ICLR_OK != i4_ret)
    {
        return;
    }

    DBG_INFO(("[SCRN_SVR] icl mmp status = %d.\n", ui1_status));

    if (ICL_MMP_MEDIA_PLAY_STATUS_ON == ui1_status)
    {
        if (TRUE == pt_this->b_is_on)
        {
            scrn_svr_view_hide(&(pt_this->t_view), pt_this->e_toast_style);
        }

        pt_this->b_enable = FALSE;
    }

    else
    {
        pt_this->b_enable = TRUE;
    }

   return ;
}
/*----------------------------------------------------------------------------
 * Name: _scrn_svr_icl_nfy_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _scrn_svr_icl_nfy_cb(UINT16                ui2_nfy_id,
                                  VOID*                 pv_tag,
                                  ICL_NOTIFY_DATA_T*    pt_notify_data)
{
    ICL_GRPID_TYPE      e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);

    if (e_grp_id != ICL_GRPID_CAST_SRC_STATUS)
    {
        return NAVR_OK;
    }

    nav_request_context_switch(_scrn_svr_icl_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);
    return NAVR_OK;
}

static INT32 _icl_mmp_nfy_cb(UINT16                 ui2_nfy_id,
                                 VOID*              pv_tag,
                                  ICL_NOTIFY_DATA_T*    pt_notify_data)
{
    ICL_GRPID_TYPE      e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);

    if (e_grp_id != ICL_GRPID_MMP)
    {
        return NAVR_OK;
    }

    nav_request_context_switch(_icl_mmp_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _scrn_svr_comp_state_trans_nfy
 *
 * Description: This callback function will be called when the comp switches.
 *
 * Inputs:  e_cond          Contains the transition condition.
 *          ui4_evt_code    Contains the event code.
 *          e_from_comp_id  Current comp ID.
 *          e_to_comp_id    Next comp ID.
 *          ui4_data        Contains information related to the event.
 *          pv_tag          A private tag.
 *
 * Outputs: -
 *
 * Returns: NAVR_OK         This function succeeded.
 *          Otherwise       This function failed.
 ----------------------------------------------------------------------------*/
static INT32 _scrn_svr_comp_state_trans_nfy (NAV_COMP_STATE_TRANS_COND_T e_cond,
                                             NAV_COMP_ID_T  e_from_comp_id,
                                             NAV_COMP_ID_T  e_to_comp_id,
                                             UINT32         ui4_data,
                                             VOID*          pv_tag)
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;

    if (!nav_is_active() || nav_is_pausing())
    {
        return NAVR_OK;
    }

    if (e_cond == NAV_COMP_STATE_TRANS_BEFORE_ACTIVATION_CHANGE)
    {
        /* do nothing */
    }
    else if (e_cond == NAV_COMP_STATE_TRANS_AFTER_ACTIVATION_CHANGE)
    {
        _scrn_svr_check_to_activate(pt_this, FALSE);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;
    INT32       i4_ret  = NAVR_OK;

    pt_this->ui4_timeout                   = SCRN_SVR_NEXT_MOVE_TIMEOUT;
    pt_this->b_is_on                       = FALSE;
    pt_this->b_msg_visible                 = FALSE;
    pt_this->b_delay_to_activate           = FALSE;
    pt_this->t_msgs[TV_WIN_ID_MAIN].e_type = SCRN_SVR_MSG_TYPE_UNKNOWN;
    pt_this->t_msgs[TV_WIN_ID_SUB].e_type  = SCRN_SVR_MSG_TYPE_UNKNOWN;
    pt_this->h_main_svctx                  = NULL_HANDLE;
    pt_this->b_enable                      = TRUE;
    pt_this->b_need_delay_show_network_lost  = TRUE;
    pt_this->e_toast_style                 = TOAST_STYLE_NO_SIGNAL;

    /* Register comp transition nfy. */
    i4_ret = nav_register_comp_state_trans_nty_fct (NAV_COMP_ID_SCREEN_SAVER,
                                                    _scrn_svr_comp_state_trans_nfy,
                                                    NULL);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_create(&pt_this->h_timer);
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_timer_create(&h_temp_timer);
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_open(
                    SVCTX_NAME_MAIN,
                    _scrn_svctx_nfy_fct,
                    NULL,
                    &pt_this->h_main_svctx
                    );
    if(i4_ret != TVR_OK){
        return NAVR_FAIL;
    }

    /* register to network utility */
    i4_ret = a_nw_register (_scrn_svr_nw_notify_callback,
                            NULL,
                            &(pt_this->ui4_nw_nfy_id));
    if (NWR_OK != i4_ret)
    {
        DBG_ERROR(("[scrn_svr]a_nw_register failed"));
        pt_this->ui4_nw_nfy_id = 0;
        return NAVR_FAIL;
    }

    i4_ret = a_icl_notify_reg(ICL_GRPID_CAST_SRC_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _scrn_svr_icl_nfy_cb,
                              &(pt_this->ui2_icl_nfy_id));
    if (ICLR_OK != i4_ret)
    {
        pt_this->ui2_icl_nfy_id = 0;
        return NAVR_FAIL;
    }

    i4_ret = a_icl_notify_reg(ICL_GRPID_MMP,
                              ICL_GROUP_ID_CUSTOM_START,
                              NULL,
                              NULL,
                              _icl_mmp_nfy_cb,
                              &(pt_this->ui2_icl_nfy_id_mmp));
    if (ICLR_OK != i4_ret)
    {
        pt_this->ui2_icl_nfy_id_mmp = 0;
        return NAVR_FAIL;
    }

    i4_ret = scrn_svr_view_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    pt_ctx->t_gui_res.e_color_type
                    );
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_deinit(
                    VOID
                    )
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;
    INT32       i4_ret = NAVR_OK;

    if (c_handle_valid(pt_this->h_timer) == TRUE) {
        c_timer_delete(pt_this->h_timer);
        pt_this->h_timer = NULL_HANDLE;
    }
    if (c_handle_valid(h_temp_timer) == TRUE) {
        c_timer_delete(h_temp_timer);
        h_temp_timer = NULL_HANDLE;
    }

    i4_ret = scrn_svr_view_deinit(&pt_this->t_view);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->ui4_timeout         = 0;
    pt_this->b_is_on             = FALSE;
    pt_this->b_msg_visible       = FALSE;
    pt_this->b_delay_to_activate = FALSE;
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_is_subtitle_comp_playing
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _scrn_svr_is_subtitle_comp_playing(
                    TV_WIN_ID_T                 e_tv_win_id
                    )
{
#ifdef APP_DVBT_SUPPORT
  #ifndef APP_SCRN_SVR_NO_VIDEO_IMPLY_NO_SUBTITLE
    STREAM_COMP_ID_T t_comp_id;
    SCDB_REC_T       t_scdb_rec;
    INT32            i4_ret;
    UINT32           ui4_scrambled_strm = 0;

    i4_ret = nav_get_ca_status(
                    e_tv_win_id,
                    &ui4_scrambled_strm
                    );
    if (i4_ret == NAVR_OK) {
        if ((ui4_scrambled_strm & ST_MASK_SUBTITLE) > 0) {
            return FALSE;
        }
    #ifdef APP_SCRAMBLED_VIDEO_IMPLY_NO_SUBTITLE
        if ((ui4_scrambled_strm & ST_MASK_VIDEO) > 0) {
            return FALSE;
        }
    #endif
    }

    i4_ret = nav_get_using_strm_data(
                    e_tv_win_id,
                    ST_SUBTITLE,
                    &t_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        return TRUE;
    }
  #endif
#endif
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_is_able_to_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 nav_retail_mode_is_show_dialog(VOID);

static INT32 _scrn_svr_is_able_to_activate(SCRN_SVR_T* pt_this)
{
    TV_MODE_T       e_tv_mode     = TV_MODE_TYPE_LAST_VALID_ENTRY;
    INT32           i4_ret        = NAVR_NOT_ALLOW;
    NAV_AV_STATUS_T nav_av_status = nav_get_av_status(pt_this->e_focus_tv_win_id);

#if 0 // dbg for status checking
    DBG_LOG_PRINT (("\033[45m [%s][%d] \033[0m \n", __FUNCTION__, __LINE__));
    DBG_LOG_PRINT((" nav_is_active(): %X \n", nav_is_active()));
    DBG_LOG_PRINT((" nav_is_running(): %X \n", nav_is_running(pt_this->e_focus_tv_win_id)));
    DBG_LOG_PRINT((" a_nav_is_signal_loss(): %X \n", a_nav_is_signal_loss()));
    DBG_LOG_PRINT((" nav_is_signal_loss(): %X \n", nav_is_signal_loss(pt_this->e_focus_tv_win_id)));
    DBG_LOG_PRINT((" nav_get_av_status(): %X \n", nav_get_av_status(pt_this->e_focus_tv_win_id)));
    DBG_LOG_PRINT((" nav_get_tv_mode(): %X \n", nav_get_tv_mode(&e_tv_mode)));
    DBG_LOG_PRINT((" nav_any_component_visible(): %X \n", nav_any_component_visible()));
    DBG_LOG_PRINT((" nav_get_active_component(): %X \n", nav_get_active_component()));
    DBG_LOG_PRINT((" nav_is_video_content_playing(): %X \n", nav_is_video_content_playing(pt_this->e_focus_tv_win_id) ));
    DBG_LOG_PRINT((" nav_is_audio_content_playing(): %X \n", nav_is_audio_content_playing(pt_this->e_focus_tv_win_id)));
    DBG_LOG_PRINT((" nav_is_audio_comp_playing(): %X \n", nav_is_audio_comp_playing(pt_this->e_focus_tv_win_id)));
    DBG_LOG_PRINT((" nav_get_locked_status(): %X \n", nav_get_locked_status(pt_this->e_focus_tv_win_id)));
#endif

    do {

        if ( (!a_nav_is_signal_loss()) && (nav_av_status == NAV_AV_STATUS_UNKNOWN) )
        {
            DBG_LOG_PRINT(("[SCRN_SVR] [%s][%d] a_nav_is_signal_loss (%X), pt_this->e_toast_style = %d \n", __FUNCTION__, __LINE__, nav_av_status, pt_this->e_toast_style));
            if(pt_this->e_toast_style != TOAST_STYLE_SIGNAL_ACQUIRE)
            {
                break;
            }
        }

        if (a_wzd_is_oobe_mode() == TRUE && !a_nav_retail_mode_get_start_from_oobe()) {
            DBG_INFO(("[SCRN_SVR] [%s][%d] OOBE \n", __FUNCTION__, __LINE__));
            break;
        }

        if(nav_is_active() == FALSE) {
            DBG_INFO(("[SCRN_SVR] [%s][%d] nav is not active \n", __FUNCTION__, __LINE__));
            break;
        }

        if (nav_get_tv_mode(&e_tv_mode) != NAVR_OK || e_tv_mode != TV_MODE_TYPE_NORMAL) {
            DBG_INFO(("[SCRN_SVR] [%s][%d] nav is not nav_get_tv_mode \n", __FUNCTION__, __LINE__));
            break;
        }

        if (nav_any_component_visible() == TRUE && nav_get_active_component() != NAV_COMP_ID_LAST_VALID_ENTRY) {
            DBG_INFO(("[SCRN_SVR] [%s][%d] other nav component visible current active component is %d\n", __FUNCTION__, __LINE__,nav_get_active_component()));
            break;
        }

        if (nav_get_focus_id(&pt_this->e_focus_tv_win_id) != NAVR_OK) {
            DBG_INFO(("[SCRN_SVR] [%s][%d] failed to get focus \n", __FUNCTION__, __LINE__));
            break;
        }

        if ((nav_is_video_content_playing(pt_this->e_focus_tv_win_id) == TRUE)) {
            DBG_INFO(("[SCRN_SVR] [%s][%d] video playing \n", __FUNCTION__, __LINE__));
            break;
        }

        if (_scrn_svr_is_subtitle_comp_playing(pt_this->e_focus_tv_win_id) == TRUE) {
            DBG_INFO(("[SCRN_SVR] [%s][%d] subtitle playing \n", __FUNCTION__, __LINE__));
            break;
        }

        if (nav_retail_mode_is_show_dialog() == TRUE)
        {
            DBG_INFO(("[SCRN_SVR] [%s][%d] demo mode dialog showing \n", __FUNCTION__, __LINE__));
            break;
        }

        i4_ret = NAVR_OK;
    } while (0);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_is_able_to_activate_in_cast
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_is_able_to_activate_in_cast(
                    SCRN_SVR_T*                 pt_this
                    )
{
    TV_MODE_T e_tv_mode = TV_MODE_TYPE_LAST_VALID_ENTRY;
    INT32     i4_ret    = NAVR_NOT_ALLOW;

    do {
        if ((SCRN_SVR_MSG_TYPE_MLM_KEY != pt_this->t_msgs[TV_WIN_ID_MAIN].e_type) ||
            (MLM_NAV_KEY_NW_CONNECTION_LOST_MSG != pt_this->t_msgs[TV_WIN_ID_MAIN].u.ui2_mlm_key &&
             MLM_NAV_KEY_CAST_NOT_SETUP_MSG != pt_this->t_msgs[TV_WIN_ID_MAIN].u.ui2_mlm_key))
        {
            break;
        }

        if (a_wzd_is_oobe_mode() == TRUE) {
            break;
        }

        if (_scrn_svr_store_demo_is_on() == TRUE) {
            break;
        }

        if(nav_is_active() == FALSE) {
            break;
        }

        if (nav_get_tv_mode(&e_tv_mode) != NAVR_OK) {
            break;
        }

        if (e_tv_mode != TV_MODE_TYPE_NORMAL) {
            break;
        }

        if (nav_any_component_visible() == TRUE && FALSE == nav_is_component_visible(NAV_COMP_ID_C4TV_APRON)) {
            break;
        }

        if (nav_is_component_visible(NAV_COMP_ID_BANNER) ||
            nav_is_component_visible(NAV_COMP_ID_REVOLT_INFO)||
            nav_is_component_visible(NAV_COMP_ID_UPDATER) ||
            nav_is_component_visible(NAV_COMP_ID_LINK))
        {
            break;
        }

        i4_ret = NAVR_OK;
    } while (0);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_scrn_svr_handle_timeout, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_stop_timer(
                    SCRN_SVR_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop scrn_svr::h_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_reset_timer(
                    SCRN_SVR_T*                 pt_this
                    )
{
    INT32 i4_ret;

    _scrn_svr_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _scrn_svr_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start scrn_svr::h_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static  INT32 _scrn_svr_hide( VOID)
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;
    INT32       i4_ret = NAVR_OK;

    DBG_INFO(("[NAV][%s %d] b_is_on = %d,style = %d\n",__FUNCTION__,__LINE__,pt_this->b_is_on,pt_this->e_toast_style));

    if (pt_this->b_is_on == FALSE) {
        return NAVR_OK;
    }

#ifdef APP_CAST_TV_MMP
    /* active app is mmp  && parse null mp4 file not hide */
    CHAR    s_active_app[APP_NAME_MAX_LEN + 1] = {0};
    a_am_get_active_app (s_active_app);

    if ((c_strcmp(s_active_app, MMP_NAME) == 0)&&
         a_mmp_get_is_parse_null_ff_state())
    {
         return NAVR_OK;
    }
#endif
    _scrn_svr_stop_timer(pt_this);

    TV_WIN_ID_T e_tv_win_id = TV_WIN_ID_MAIN;
    i4_ret = nav_get_focus_id(&e_tv_win_id);
    if(nav_is_video_content_playing(e_tv_win_id) == TRUE)
        {
            nav_return_activation(NAV_COMP_ID_SCREEN_SAVER);
        }

    if (TOAST_STYLE_SIGNAL_ACQUIRE != pt_this->e_toast_style)
    {
        NAV_CHK_FAIL( scrn_svr_view_hide(&(pt_this->t_view), pt_this->e_toast_style));
    }
    pt_this->b_is_on             = FALSE;
    pt_this->b_msg_visible       = FALSE;
    pt_this->b_delay_to_activate = FALSE;
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_handle_av_status_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_handle_av_status_msg(
                    SCRN_SVR_T*             pt_this,
                    TV_WIN_ID_T             e_tv_win_id
                    )
{
    NAV_AV_STATUS_T nav_av_status = nav_get_av_status(e_tv_win_id);

    DBG_INFO(("[SCRN_SVR] [%s][%d] e_tv_win_id: %X nav_av_status: %X \033[0m \n", __FUNCTION__, __LINE__, e_tv_win_id, nav_av_status));

    if ( nav_is_hidden_ch(e_tv_win_id) == TRUE
       &&NAV_AV_STATUS_UNKNOWN != nav_av_status)
    {
        _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_HIDDEN_CH);
        return;
    }

    switch (nav_av_status)
    {
    case NAV_AV_STATUS_AUDIO_ONLY:
    case NAV_AV_STATUS_SCRAMBLED_VIDEO_CLEAR_AUDIO:
        if (nav_is_video_hd_not_support(e_tv_win_id))
        {
            _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_HD_VIDEO_NOT_SUPPORT);
        }
        else if (nav_is_video_codec_not_support(e_tv_win_id))
        {
            //_MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_VIDEO_NOT_SUPPORT);
            _MSG_SET_MLM_KEY(e_tv_win_id, MLM_NAV_KEY_NAV_SCRAMBLED_VIDEO);
        }
        else
        {
            _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_AUDIO_PROG);
        }
        break;

    case NAV_AV_STATUS_VIDEO_ONLY:
    case NAV_AV_STATUS_AUDIO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_CLEAR_VIDEO:
        _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
        break;

#if 0
    case NAV_AV_STATUS_NO_AUDIO_VIDEO:
        if (nav_is_video_hd_not_support(e_tv_win_id))
        {
            _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_HD_VIDEO_NOT_SUPPORT);
        }
        else if (nav_is_video_codec_not_support(e_tv_win_id))
        {
            //_MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_VIDEO_NOT_SUPPORT);
            _MSG_SET_MLM_KEY(e_tv_win_id, MLM_NAV_KEY_NAV_SCRAMBLED_VIDEO);
        }
        else
        {
            _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_NO_AUDIO_VIDEO);
        }
        break;
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_NO_VIDEO:
        //_MSG_SET_MLM_KEY(e_tv_win_id, MLM_NAV_KEY_MSG_SCRAMBLED);
        _MSG_SET_MLM_KEY(e_tv_win_id, MLM_NAV_KEY_MSG_SCRAMBLED);
        break;
    case NAV_AV_STATUS_SCRAMBLED_VIDEO_NO_AUDIO:
        if (nav_is_video_hd_not_support(e_tv_win_id))
        {
            _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_HD_VIDEO_NOT_SUPPORT);
        }
        else if (nav_is_video_codec_not_support(e_tv_win_id))
        {
            _MSG_SET_MSG_ID(e_tv_win_id, MSG_STR_ID_VIDEO_NOT_SUPPORT);
        }
        else
        {
            _MSG_SET_MLM_KEY(e_tv_win_id, MLM_NAV_KEY_MSG_SCRAMBLED);
        }
        break;
#else

    case NAV_AV_STATUS_NO_AUDIO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_NO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_VIDEO_NO_AUDIO:
         _MSG_SET_MLM_KEY(e_tv_win_id, MLM_NAV_KEY_NAV_SCRAMBLED_VIDEO);
        break;
#endif

    default:
        _MSG_SET_UNKNOWN(e_tv_win_id);
        break;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_update_err_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_update_err_msg(
                    SCRN_SVR_T*                 pt_this,
                    TV_MODE_T                   e_tv_mode
                    )
{
    INT32 i4_ret;

    if (e_tv_mode != TV_MODE_TYPE_NORMAL) {
        return NAVR_OK;
    }

    if (pt_this->b_is_on == FALSE) {
        return _scrn_svr_check_to_activate(pt_this, FALSE);
    }

    i4_ret = _scrn_svr_show_crnt_err_msg();
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pt_this->b_msg_visible = TRUE;
    return NAVR_OK;
}

static VOID _scrn_svr_timer_msg_handler(
    VOID*                           pv_msg_id,
    VOID*                           pv_tag2,
    VOID*                           pv_tag3
   )
{
       MSG_STR_ID_T msg_id = (MSG_STR_ID_T)(INT32)pv_msg_id;
       SCRN_SVR_T* pt_this   = &t_g_scrn_svr;
       TV_MODE_T   e_tv_mode = TV_MODE_TYPE_LAST_VALID_ENTRY;

    DBG_INFO(("[SCRN_SVR] [%s][%d] msg_id:%d e_msg_id:%d \n", __FUNCTION__, __LINE__, msg_id,t_g_scrn_svr.t_msgs[TV_WIN_ID_MAIN].u.e_msg_id));

       if(msg_id == t_g_scrn_svr.t_msgs[TV_WIN_ID_MAIN].u.e_msg_id)
       {
               nav_get_tv_mode(&e_tv_mode);

       _scrn_svr_update_err_msg(pt_this, e_tv_mode);
       }
}

static VOID _scrn_svr_timer_cb(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag)
{
    /* execute in timer's thread context */
    nav_request_context_switch(_scrn_svr_timer_msg_handler,
                                pv_tag,
                                NULL,
                                NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    SCRN_SVR_T* pt_this   = &t_g_scrn_svr;
    TV_MODE_T   e_tv_mode = TV_MODE_TYPE_LAST_VALID_ENTRY;
    UINT32      ui4_drv_eco = ICL_CUSTOM_POWER_MODE_ECO;
    INT32       i4_ret    = NAVR_OK;
    TV_WIN_ID_T e_crnt_tv_win_id;
    TV_WIN_ID_T e_focus_tv_win_id;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    e_crnt_tv_win_id  = pt_ui_msg->e_tv_win_id;
    e_focus_tv_win_id = pt_this->e_focus_tv_win_id = pt_ctx->t_svc_res.e_focus_tv_win_id;

    printf("%s %d pt_ui_msg->e_id = %d\n", __FUNCTION__, __LINE__, pt_ui_msg->e_id);

    switch (pt_ui_msg->e_id) {

    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
       nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
       pt_this->e_toast_style = TOAST_STYLE_MAX_NUM;
       return NAVR_OK;
    case NAV_UI_MSG_STREAM_NOTIFY:
      {
        NAV_STREAM_NOTIFY_DATA_T* pt_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;

            DBG_INFO(("[SCRN_SVR] [%s][%d] e_strm_type: %X, e_type: %X, \n",
             __FUNCTION__, __LINE__, pt_data->e_strm_type, pt_data->e_type));

        if (pt_data->e_strm_type == ST_VIDEO) {
            switch(pt_data->e_type) {
            case NAV_SNT_STREAM_UPDATED:
                if (e_tv_mode == TV_MODE_TYPE_NORMAL
                        && nav_is_video_content_playing(e_crnt_tv_win_id) == TRUE) {
                    nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
                }
                return NAVR_OK;
            case NAV_SNT_STREAM_NOT_SUPPORT:
                _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_VIDEO_NOT_SUPPORT);
                break;
            default:
                return NAVR_OK;
            }
        } else if (pt_data->e_strm_type == ST_SUBTITLE) {
            switch(pt_data->e_type) {
            case NAV_SNT_STREAM_STARTED:
                if (e_tv_mode == TV_MODE_TYPE_NORMAL
                        && _scrn_svr_is_subtitle_comp_playing(e_crnt_tv_win_id) == TRUE) {
                    nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
                }
                return NAVR_OK;
            case NAV_SNT_STREAM_STOPPED:
                _scrn_svr_check_to_activate(pt_this, FALSE);
                return NAVR_OK;
            default:
                return NAVR_OK;
            }
        } else {
            return NAVR_OK;
        }
        break;
      }

    case NAV_UI_MSG_OTHER_APP_RESUMED:
        {
            if ((c_strcmp ((CHAR*)pv_arg1, (CHAR*)MMP_NAME) == 0)||
                (c_strcmp ((CHAR*)pv_arg1, "mscvt") == 0 && APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status()))
            {
                DBG_INFO(("[SCRN_SVR][%s %d] mmp/3rd resumed, stop no-sginal blankscreen\n",__FUNCTION__,__LINE__));
                if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_NO_SIGNAL)
                {
                    menu_blank_oled_scrn_timer_stop();
                }
            }
        }
        break;
    case NAV_UI_MSG_WITH_SIGNAL:
        if (nav_is_digital_tv(e_crnt_tv_win_id) == TRUE||
            nav_get_locked_status(e_crnt_tv_win_id) != LOCKED_STATUS_NONE)
        {
            return NAVR_OK;
        }
        /* analog source */
        _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
        break;
    case NAV_UI_MSG_START_QUERY_EVENT:
        if (nav_get_locked_status(e_crnt_tv_win_id) != LOCKED_STATUS_NONE)
        {
            break;
        }

        switch(nav_get_av_status(e_crnt_tv_win_id))
        {
            case NAV_AV_STATUS_AUDIO_ONLY:
            case NAV_AV_STATUS_NO_AUDIO_VIDEO:
            case NAV_AV_STATUS_SCRAMBLED_AUDIO_VIDEO:
            case NAV_AV_STATUS_SCRAMBLED_AUDIO_NO_VIDEO:
            case NAV_AV_STATUS_SCRAMBLED_VIDEO_CLEAR_AUDIO:
            case NAV_AV_STATUS_SCRAMBLED_VIDEO_NO_AUDIO:
                /* no video, so don't handle START_QUERY_EVENT event */
                return NAVR_OK;
            default:
                break;
        }

        if (nav_is_hidden_ch(e_crnt_tv_win_id) == TRUE && NAV_AV_STATUS_UNKNOWN != nav_get_av_status(e_crnt_tv_win_id)) {
            _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_HIDDEN_CH);
        } else {
            if (nav_is_digital_tv(e_crnt_tv_win_id) == TRUE){
                 return NAVR_OK;
                }
            }
        break;
    case NAV_UI_MSG_AV_STATUS_NOTIFY:
    case NAV_UI_MSG_HIDDEN_CH:
    case NAV_UI_MSG_CA:
        _scrn_svr_handle_av_status_msg(pt_this, e_crnt_tv_win_id);
        break;
    case NAV_UI_MSG_EMPTY_SVL:
        if (nav_is_loading_svl() == TRUE) {
            _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_PLS_WAIT);
        } else {

            UINT8 ui1_scan_progress = -1;

            a_cfg_cust_get_ch_scan_progress(&ui1_scan_progress);

            if (ui1_scan_progress == 0)
            {
                _MSG_SET_MLM_KEY(e_crnt_tv_win_id, MLM_NAV_KEY_MSG_NO_CH_LIST);
            }
            else
            {
                nav_dispatch_msg_to_component(NAV_COMP_ID_SCREEN_SAVER,
                                              NAV_UI_MSG_NO_SIGNAL,
                                              NULL);
            }
        }
        break;

    case NAV_UI_MSG_NO_SIGNAL:
        DBG_LOG_PRINT(("[SCRN_SVR] [%s][%d] receive NAV_UI_MSG_NO_SIGNAL \n", __FUNCTION__, __LINE__));
        if (INP_SRC_TYPE_TV == nav_get_src_type(TV_WIN_ID_MAIN) && nav_is_channel_scan_active() == TRUE) {
          return NAVR_OK;
        }
        else
        {
        #ifdef APP_SUPPORT_ANALOG_CH_SHOW_SNOW_AS_NO_SIGNAL
            if (nav_is_analog_tv(e_crnt_tv_win_id) == TRUE)
            {
                _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
            }
            else
            {
                _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_NO_SIGNAL);
            }
        #else
            if (INP_SRC_TYPE_TV == nav_get_src_type(TV_WIN_ID_MAIN))
            {
                _MSG_SET_MLM_KEY(e_crnt_tv_win_id, MLM_NAV_KEY_MSG_NO_SIGNAL);
            }
            else if (_scrn_svr_is_rgb_inputs())
            {
                UINT8     ui1_val = 0;
                BOOL      b_auto_power_enable = TRUE;

                i4_ret = a_icl_get_app_status(&ui1_val);
                if(NAVR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"%s(): Fail to get icl rec. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
                }

                if(2 == ui1_val || 3 == ui1_val)/* 2---APP_STATUS_YH_DOCK, 3---APP_STATUS_YH_SIDEBAR a_icl.h*/
                {
                    b_auto_power_enable = FALSE;
                }

                if(b_auto_power_enable)
                {
                    i4_ret = a_icl_get_net_tv_svc_status(&ui1_val);
                    if(NAVR_OK != i4_ret)
                    {
                        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get icl rec. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
                    }

                    if(0 == ui1_val) /*APP_STATUS_NET_TV_SVC_RESUMED a_icl.h*/
                    {
                        b_auto_power_enable = FALSE;
                    }
                }

                if(b_auto_power_enable)
                {
                    _MSG_SET_MLM_KEY(e_crnt_tv_win_id, MLM_NAV_KEY_PWR_VIEW_NO_VGA);

                    i4_ret = acfg_custom_odm_update_smart_dimming(FALSE);
                    if(NAVR_OK != i4_ret)
                    {
                        DBG_ERROR((_ERROR_HEADER"%s(): Fail to update smart dimming. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
                    }
                }
                else
                {
                    _MSG_SET_MLM_KEY(e_crnt_tv_win_id, MLM_NAV_KEY_PWR_VIEW_T_VGA);
                    i4_ret = acfg_custom_odm_update_smart_dimming(FALSE);
                    if(NAVR_OK != i4_ret)
                    {
                        DBG_ERROR((_ERROR_HEADER"%s(): Fail to update smart dimming. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
                    }
                }
            }
            else
            {
                _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_NO_SIGNAL);
                i4_ret = acfg_custom_odm_update_smart_dimming(FALSE);
                if(NAVR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"%s(): Fail to update smart dimming. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
                }
            }
        #endif
        }
        break;

#ifdef APP_ISDB_SUPPORT
    case NAV_UI_MSG_NON_BRDCSTING:
        _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_NON_BRDCSTING);
        break;
#endif

    case NAV_UI_MSG_LOCKED_INP:
        _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_LOCKED_INP);
        break;
    case NAV_UI_MSG_LOCKED_CH:
        _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_LOCKED_CH);
        break;
    case NAV_UI_MSG_LOCKED_PROG:
        _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_LOCKED_PROG);
        break;
    case NAV_UI_MSG_UNLOCKED:
        /* after unlock, in some cases (digital TV),
         * the content maybe without video or cannot decode it
         * as soon as possible, so in the meanwhile, show
         * "Retrieving Data"...
         */
#if 0
        if (nav_is_digital_tv(e_crnt_tv_win_id) == TRUE) {
            _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_GETTING_DATA);
        } else {
            _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
        }
        break;
#else
   return NAVR_OK;
#endif

    case NAV_UI_MSG_EXTERNAL_CTRL_END:
    case NAV_UI_MSG_EXTERNAL_CTRL_BEGIN:
        _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_LAST_VALID_ENTRY);
        break;

    case NAV_UI_MSG_GUI_LANG_CHANGED:
        DBG_INFO(("[SCRN_SVR] [%s][%d] NAV_UI_MSG_GUI_LANG_CHANGED.\n", __FUNCTION__, __LINE__));
        break;

    case NAV_UI_MSG_ERR_MSG_UPDATE:
        if(t_g_scrn_svr.t_msgs[e_focus_tv_win_id].u.e_msg_id == MSG_STR_ID_VIDEO_NOT_SUPPORT)
        {
            i4_ret = c_timer_stop(h_temp_timer);
            i4_ret = c_timer_start(
                            h_temp_timer,
                            2000,
                            X_TIMER_FLAG_ONCE,
                            _scrn_svr_timer_cb,
                            (VOID*)MSG_STR_ID_VIDEO_NOT_SUPPORT
                            );
            return NAVR_OK;
        }
        return _scrn_svr_update_err_msg(pt_this, e_tv_mode);

    case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        if (e_tv_mode != TV_MODE_TYPE_NORMAL) {
            return NAVR_OK;
        }

        e_crnt_tv_win_id = e_focus_tv_win_id = TV_WIN_ID_MAIN;
        break;

    case NAV_UI_MSG_ENABLE_SCRN_SAVER:
        a_scrn_svr_set_enable((BOOL)(UINT32)pv_arg1);
        return NAVR_OK;

    case NAV_UI_MSG_AS_APP_PAUSED:
        if (pt_ui_msg->e_id_as_paused == NAV_UI_MSG_NO_SIGNAL)
        {
            _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_NO_SIGNAL);
            break;
        }
        else
        {
            return NAVR_OK;
        }
    //case NAV_UI_MSG_SYS_PRE_SUSPEND_EXIT:
    case NAV_UI_MSG_APP_RESUMED:
    {
        BOOL b_power_on = FALSE;
        UINT32 ui4_power_mode = 0;
        PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;

        b_power_on = (BOOL)(UINT32)pv_arg1;//NAV_UI_MSG_APP_RESUMED,   /* pv_arg1's type = BOOL.  TRUE: Under power on state.  FALSE: Not under power on state. */
        a_cfg_custom_get_drv_eco_mode(&ui4_power_mode);
        c_pcl_get_wakeup_reason(&e_wakeup_reason,NULL);

        DBG_LOG_PRINT(("\n[SCRN_SVR] [%s][%d]NAV_UI_MSG_APP_RESUMED b_power_on = %d, power_mode = %d, wakeup_reason = %d\n", __FUNCTION__, __LINE__, b_power_on, ui4_power_mode, e_wakeup_reason));

        if(b_power_on == TRUE && ui4_power_mode == 0 && PCL_WAKE_UP_REASON_IRRC == e_wakeup_reason)
        {
            _MSG_SET_MSG_ID(e_crnt_tv_win_id, MSG_STR_ID_ACQUIRE_SIGNAL);
            break;
        }
        else
        {
            return NAVR_OK;
        }
    }
    case NAV_UI_MSG_APP_PRE_RESUME:
        {
            break;
        }

    case NAV_UI_MSG_CH_SCANNING:
        if (nav_is_channel_scan_active())
        {
            break;
        }
    case NAV_UI_MSG_PRE_POWER_OFF:
        DBG_INFO(("\n[SCRN_SVR] [%s][%d] NAV_UI_MSG_PRE_POWER_OFF.\n", __FUNCTION__, __LINE__));
        TOAST_STYLE_T e_temp_toast_style = TOAST_STYLE_SIGNAL_ACQUIRE;
        NAV_CHK_FAIL( scrn_svr_view_hide(&(pt_this->t_view), e_temp_toast_style));
        _scrn_svr_hide();
        nav_hide_components (NAV_COMP_ID_SCREEN_SAVER);
        return NAVR_OK;
    case NAV_UI_MSG_POWER_ON:
        /* quick start mode do NOT need delay anymore */
        a_cfg_custom_get_drv_eco_mode(&ui4_drv_eco);
        if (ICL_CUSTOM_POWER_MODE_QUICK_START == ui4_drv_eco)
        {
            pt_this->b_need_delay_show_network_lost = FALSE;
        }
        else if (ICL_CUSTOM_POWER_MODE_ECO == ui4_drv_eco)
        {
            pt_this->b_need_delay_show_network_lost = TRUE;
        }
        DBG_INFO(("\n[SCRN_SVR] [%s][%d] NAV_UI_MSG_POWER_ON, POWER_MODE: %d.\n", __FUNCTION__, __LINE__, ui4_drv_eco));

    default:
        return NAVR_OK;
    }

    _scrn_svr_set_crnt_err_msg_id(
                    e_tv_mode,
                    e_crnt_tv_win_id,
                    e_focus_tv_win_id,
                    &(pt_this->t_msgs[e_crnt_tv_win_id])
                    );

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_handle_delay_to_activate_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_handle_delay_to_activate_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    t_g_scrn_svr.b_need_delay_show_network_lost = FALSE;

    _scrn_svr_check_to_activate(&t_g_scrn_svr, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_handle_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_handle_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    SCRN_SVR_T* pt_this = (SCRN_SVR_T*)pv_tag;
    INT32       i4_ret;

    if (pt_this->b_is_on == FALSE) {
        return;
    }

#ifdef APP_MOVABLE_SCREEN_SAVER
    i4_ret = scrn_svr_view_move(
                    &pt_this->t_view,
                    FALSE,
                    TRUE
                    );
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"scrn_svr_view_move() failed, ret = %d\r\n", i4_ret));
    }
#else
    if (pt_this->b_msg_visible == TRUE) {
        i4_ret = scrn_svr_view_hide(
                    &(pt_this->t_view),
                    pt_this->e_toast_style
                    );
        if (i4_ret == NAVR_OK) {
            pt_this->b_msg_visible = FALSE;
        }
    } else {
        i4_ret = _scrn_svr_show_crnt_err_msg();
        if (i4_ret == NAVR_OK) {
            pt_this->b_msg_visible = TRUE;
        }
    }
#endif

    _scrn_svr_reset_timer(pt_this);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_delay_to_activate_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_delay_to_activate_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_scrn_svr_handle_delay_to_activate_timeout, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_reset_delay_to_activate_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _scrn_svr_reset_delay_to_activate_timer(
                    SCRN_SVR_T*                 pt_this
                    )
{
    INT32  i4_ret;
    UINT32 ui4_delay;

    _scrn_svr_stop_timer(pt_this);

    if ((pt_this->b_need_delay_show_network_lost) &&
        (SCRN_SVR_MSG_TYPE_MLM_KEY == pt_this->t_msgs[TV_WIN_ID_MAIN].e_type) &&
        (MLM_NAV_KEY_NW_CONNECTION_LOST_MSG == pt_this->t_msgs[TV_WIN_ID_MAIN].u.ui2_mlm_key))
    {
        ui4_delay = SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT_CAST;
    }
    else
    {
        ui4_delay = SCRN_SVR_DELAY_TO_ACTIVATE_TIMEOUT;
    }

    i4_ret = c_timer_start(
                    pt_this->h_timer,
                    ui4_delay,
                    X_TIMER_FLAG_ONCE,
                    _scrn_svr_delay_to_activate_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start scrn_svr::h_timer failed!"));
    }
}

extern BOOL nav_updater_view_warm_msg_is_showing(VOID);
extern BOOL a_oled_compensation_is_running();

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_check_to_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_check_to_activate(
                    SCRN_SVR_T*                 pt_this,
                    BOOL                        b_from_timeout
                    )
{
    INT32 i4_ret = NAVR_OK;
    UINT8 ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

//    DBG_LOG_PRINT(("[SCRN_SVR] [%s][%d] enable: %d, show: %d!\n", __FUNCTION__, __LINE__, pt_this->b_enable, pt_this->b_is_on));

    if (pt_this->b_enable == FALSE) {
        return NAVR_NO_ACTION;
    }

    if (pt_this->b_is_on == TRUE) {
        return NAVR_OK;
    }

    if(FALSE == a_am_is_power_on())
    {
        DBG_LOG_PRINT(("TV is not power on, should not to active\n"));
        return NAVR_OK;
    }

    if(a_oled_compensation_is_running())
    {
        DBG_LOG_PRINT(("oled compensation is running, should not to active\n"));
        return NAVR_OK;
    }
    if(menu_custom_is_blank_screen() && menu_custom_get_blank_scrn_mode() == BLK_SCRN_NORMAL)
    {
        DBG_LOG_PRINT(("oled compensation blank screen from menu, should not to active\n"));
        return NAVR_OK;
    }

    if(a_slogo_is_show())
    {
        DBG_LOG_PRINT(("VLOGO is showing, should not to active\n"));
        pt_this->b_delay_to_activate = TRUE;
        _scrn_svr_reset_delay_to_activate_timer(pt_this);
        return NAVR_OK;
    }

    if (_scrn_svr_is_cast_source() || a_c4tv_apron_check_cast_state())
    {
        i4_ret = _scrn_svr_is_able_to_activate_in_cast(pt_this);
    }
    else
    {
        i4_ret = _scrn_svr_is_able_to_activate(pt_this);
    }

    if (i4_ret != NAVR_OK)
    {
         pt_this->b_delay_to_activate = FALSE;
         DBG_LOG_PRINT(("[SCRN_SVR] [%s][%d] not enable to active\n", __FUNCTION__, __LINE__));
         return i4_ret;
    }

    a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
    DBG_INFO(("[SCRN_SVR] [%s][%d] b_delay_to_activate = %d, b_from_timeout = %d, ui1_zoom_mode = %d\n",
                   __FUNCTION__,__LINE__,
                   pt_this->b_delay_to_activate,
                   b_from_timeout,
                   ui1_zoom_mode));

    if (pt_this->b_delay_to_activate == FALSE ||
        b_from_timeout == FALSE ||
        nav_updater_view_warm_msg_is_showing() ||
        msg_convert_custom_system_ui_showing() ||
        (nav_is_component_visible(NAV_COMP_ID_BANNER) && ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON))
    {
        pt_this->b_delay_to_activate = TRUE;
        _scrn_svr_reset_delay_to_activate_timer(pt_this);
        return NAVR_DELAY_ACTION;
    }

    if(acfg_signal_loss_count_get() > 0)
    {
        if(pt_this->e_toast_style != TOAST_STYLE_SIGNAL_ACQUIRE)
        {
            DBG_LOG_PRINT(("[SCRN_SVR] [%s][%d] acfg signal loss count > 0\n", __FUNCTION__, __LINE__));

            pt_this->b_delay_to_activate = TRUE;
            _scrn_svr_reset_delay_to_activate_timer(pt_this);
            return NAVR_DELAY_ACTION;
        }
    }

    pt_this->b_delay_to_activate = FALSE;

#ifdef APP_MOVABLE_SCREEN_SAVER
    i4_ret = scrn_svr_view_move(&pt_this->t_view, TRUE, FALSE);
    if (i4_ret != NAVR_OK) {
        DBG_INFO(("[SCRN_SVR] [%s][%d] failed to move  scrn svr\n", __FUNCTION__, __LINE__));
        return i4_ret;
    }
#endif

    //fix show no channels scaned when nav scan complete after fac_reset
    UTF16_T*    pw2s_string = nav_get_crnt_err_msg();
    UINT32      ui4_crnt_channel_id = INVALID_CHANNEL_ID;
    ISL_REC_T   t_isl_rec = {0};

    a_cfg_get_crnt_channel_id(&ui4_crnt_channel_id);
    _scrn_svr_get_crnt_isl(&t_isl_rec);

    //CHAR str_ttt[128] = {0};
    //c_uc_w2s_to_ps(pw2s_string,str_ttt,sizeof(str_ttt));
    //DBG_INFO(("[scan complete] ui4_crnt_channel_id=%d,msg:%s\n",ui4_crnt_channel_id,str_ttt));
    //DBG_INFO(("[scan complete] cmp:%d id:%d\n",!c_uc_w2s_strcmp(pw2s_string,MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_MSG_NO_CH_LIST)),ui4_crnt_channel_id != INVALID_CHANNEL_ID ));
    if(!c_uc_w2s_strcmp(pw2s_string,MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_MSG_NO_CH_LIST))
        && (ui4_crnt_channel_id != INVALID_CHANNEL_ID || t_isl_rec.e_src_type != INP_SRC_TYPE_TV))
    {
        DBG_INFO(("[%s][%d] channel scan has completed already\n", __FUNCTION__, __LINE__));
        return NAVR_OK;
    }

    i4_ret = _scrn_svr_show_crnt_err_msg();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR(("[SCRN_SVR] ERROR failed to show current error msg\n"));
        return i4_ret;
    }
    {
        CHAR sz_ps[128] = {0};
        c_uc_w2s_to_ps(pw2s_string,sz_ps,127);
        DBG_LOG_PRINT(("[SCRN_SVR] show screen saver:\"%s\"\n",sz_ps));
    }
    nav_set_component_visible(NAV_COMP_ID_SCREEN_SAVER);
    pt_this->b_msg_visible = TRUE;
    _scrn_svr_reset_timer(pt_this);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _scrn_svr_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _scrn_svr_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return _scrn_svr_check_to_activate(&t_g_scrn_svr, FALSE);
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_scrn_svr_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_scrn_svr_register(
                    VOID
                    )
{
    NAV_COMP_T t_comp;
    INT32      i4_ret;

    c_memset(& t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_SCREEN_SAVER */
    t_comp.pf_init           = _scrn_svr_init;
    t_comp.pf_deinit         = _scrn_svr_deinit;
    t_comp.pf_is_key_handler = NULL;
    t_comp.pf_activate       = _scrn_svr_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _scrn_svr_hide;
    t_comp.pf_handle_msg     = _scrn_svr_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_SCREEN_SAVER, &t_comp, NAV_NO_ANY_COMP_ID_BIT_MASK);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_SCREEN_SAVER) failed\r\n"));
        return i4_ret;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_scrn_svr_set_enable
 * Description
 *      The API is used to diable or enable screen saver. Please
 *      be aware, once it is disabled by someone, the someone
 *      need to enable it again. Otherwise, this screen saver
 *      will disappear.
 * Input arguments
 *      b_enable            To enable or disable
 * Output arguments
 *      none
 * Returns
 *      NAVR_OK             The routine is successfully.
 *      NAVR_NO_ACTION      The input parameters is the same as current one.
 *      NAVR_NO_FAIL        The routine is failed
 *---------------------------------------------------------------------------*/
INT32 a_scrn_svr_set_enable(
                    BOOL                        b_enable
                    )
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;
    INT32       i4_ret  = NAVR_OK;

    DBG_INFO(("a_scrn_svr_set_enable b_enable=%d \n",b_enable));

    pt_this->b_enable = b_enable;

    if (pt_this->b_enable == FALSE) {
        nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
    } else {
        TV_MODE_T e_tv_mode;

        i4_ret = nav_get_tv_mode(&e_tv_mode);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        DBG_INFO(("a_scrn_svr_set_enable b_enable=%d \n",b_enable));

        i4_ret = _scrn_svr_update_err_msg(pt_this, e_tv_mode);

        if(i4_ret !=NAVR_OK && i4_ret != NAVR_DELAY_ACTION && i4_ret != NAVR_NOT_ALLOW)
        {
            pt_this->b_enable = FALSE;
        }
    }

    return i4_ret;
}

#ifdef SYS_MTKTVAPI_SUPPORT
#define     SCRN_SVR_MSG_STR_ID_EMPTY                           (0)
#define     SCRN_SVR_MSG_STR_ID_NO_SIGNAL                       (1)
#define     SCRN_SVR_MSG_STR_ID_SCAN_CH                         (2)
#define     SCRN_SVR_MSG_STR_ID_GETTING_DATA                    (3)
#define     SCRN_SVR_MSG_STR_ID_LOCKED_CH                       (4)
#define     SCRN_SVR_MSG_STR_ID_LOCKED_PROG                     (5)
#define     SCRN_SVR_MSG_STR_ID_LOCKED_INP                      (6)
#define     SCRN_SVR_MSG_STR_ID_NO_EVN_TILE                     (7)
#define     SCRN_SVR_MSG_STR_ID_HIDDEN_CH                       (8)
#define     SCRN_SVR_MSG_STR_ID_AUDIO_PROG                      (9)
#define     SCRN_SVR_MSG_STR_ID_NO_AUDIO_VIDEO                  (10)
#define     SCRN_SVR_MSG_STR_ID_NO_EVN_DTIL                     (11)
#define     SCRN_SVR_MSG_STR_ID_NO_CH_DTIL                      (12)
#define     SCRN_SVR_MSG_STR_ID_NO_AUDIO_STRM                   (13)
#define     SCRN_SVR_MSG_STR_ID_NO_VIDEO_STRM                   (14)
#define     SCRN_SVR_MSG_STR_ID_PLS_WAIT                        (15)
#define     SCRN_SVR_MSG_STR_ID_VIDEO_NOT_SUPPORT               (16)
#define     SCRN_SVR_MSG_STR_ID_HD_VIDEO_NOT_SUPPORT            (17)
#define     SCRN_SVR_MSG_STR_ID_NON_BRDCSTING                   (18)
#define     SCRN_SVR_MSG_STR_ID_NO_CH_IN_LIST                   (19)
#define     SCRN_SVR_MSG_STR_ID_TTX_SBTI_X_RATED_BLOCKED        (20)
#define     SCRN_SVR_MSG_STR_ID_SCRAMBLED                       (21)
#define     SCRN_SVR_MSG_STR_ID_LAST_VALID_ENTRY                (255)

static INT32 _scrn_svr_msg_id_mapping(VOID)
{
    UTF16_T*    w2s_str         = NULL;
    UTF16_T*    w2s_tmp         = NULL;
    UINT8       ui1_lang_idx    = 0;

    w2s_str         = nav_get_crnt_err_msg();
    ui1_lang_idx    = nav_get_mlm_lang_id();

    if(NULL == w2s_str)
    {
        return SCRN_SVR_MSG_STR_ID_LAST_VALID_ENTRY;
    }

    if(0 == w2s_str[0])
    {
        /*MSG_STR_ID_EMPTY*/
        return SCRN_SVR_MSG_STR_ID_EMPTY;
    }

#ifdef MLM_NAV_KEY_MSG_NO_SIGNAL
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_SIGNAL);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_NO_SIGNAL;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_SCAN_CH
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_SCAN_CH);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_SCAN_CH;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_LOCKED_CH
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_LOCKED_CH);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_LOCKED_CH;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_LOCKED_PROG
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_LOCKED_PROG);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_LOCKED_PROG;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_LOCKED_INP
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_LOCKED_INP);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_LOCKED_INP;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_HIDDEN_CH
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_HIDDEN_CH);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_HIDDEN_CH;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_AUDIO_PROG
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_AUDIO_PROG);

#ifndef APP_NAV_VIEW_NO_MUSIC_NOTE
/* with music note, unicode is 0x266A*/
    UTF16_T     w2s_audio[64] = {0};

    w2s_audio[0] = 0x266A;
    w2s_audio[1] = 0x20;

    c_uc_w2s_strncat(w2s_audio, w2s_tmp, 2 + c_uc_w2s_strlen(w2s_tmp));
    if(0 == c_uc_w2s_strncmp(w2s_audio, w2s_str, 2 + c_uc_w2s_strlen(w2s_tmp)))
    {
        return SCRN_SVR_MSG_STR_ID_AUDIO_PROG;
    }
#else
/* without music note */
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_AUDIO_PROG;
    }
#endif
#endif

#ifdef MLM_NAV_KEY_MSG_GET_DATA
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_GET_DATA);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_GETTING_DATA;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_NO_AV
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_AV);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_NO_AUDIO_VIDEO;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_PLS_WAIT
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_PLS_WAIT);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_PLS_WAIT;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_NOT_SUPPORT
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NOT_SUPPORT);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_VIDEO_NOT_SUPPORT;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_HD_VIDEO_NOT_SUPPORT
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_HD_VIDEO_NOT_SUPPORT);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_HD_VIDEO_NOT_SUPPORT;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_NO_CH
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_CH);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_NO_CH_IN_LIST;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_NON_BRDCSTING
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NON_BRDCSTING);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_NON_BRDCSTING;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_SCRAMBLED
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx,MLM_NAV_KEY_MSG_SCRAMBLED);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_SCRAMBLED;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_TTX_SBTI_X_RATED_BLOCKED
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_TTX_SBTI_X_RATED_BLOCKED);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_TTX_SBTI_X_RATED_BLOCKED;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_NO_AUDIO
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_AUDIO);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_NO_AUDIO_STRM;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_NO_VIDEO
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_VIDEO);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return SCRN_SVR_MSG_STR_ID_NO_VIDEO_STRM;
    }
#endif

#ifdef MLM_NAV_KEY_MSG_NO_EVN_TILE
        w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_EVN_TILE);
        if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
        {
            return SCRN_SVR_MSG_STR_ID_NO_EVN_TILE;
        }
#endif

#ifdef MLM_NAV_KEY_MSG_NO_EVN_DTIL
        w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_EVN_DTIL);
        if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
        {
            return SCRN_SVR_MSG_STR_ID_NO_EVN_DTIL;
        }
#endif

#ifdef MLM_NAV_KEY_MSG_NO_CH_DTIL
        w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_MSG_NO_CH_DTIL);
        if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
        {
            return SCRN_SVR_MSG_STR_ID_NO_CH_DTIL;
    }
#endif

    return SCRN_SVR_MSG_STR_ID_LAST_VALID_ENTRY;
}
#endif


INT32 a_scrn_svr_get_msgID(INT32*   pi4_msgID)
{
#ifdef SYS_MTKTVAPI_SUPPORT
#if 0
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;
    TV_WIN_ID_T e_tv_win_id = TV_WIN_ID_MAIN;

    nav_get_focus_id(&e_tv_win_id);

    *pi4_msgID = (INT32)(pt_this->t_msgs[e_tv_win_id].u.e_msg_id);

    /* TODO: for mlm msg id */
#else
    *pi4_msgID = _scrn_svr_msg_id_mapping();
#endif
#endif

    return NAVR_OK;
}

TOAST_STYLE_T a_scrn_svr_get_style()
{
    return t_g_scrn_svr.e_toast_style ;
}

INT32 a_scrn_svr_hide_NO_SIGNAL_1(VOID)
{
    SCRN_SVR_T*         pt_this             = &t_g_scrn_svr;
    TOAST_STYLE_T       t_e_g_toast_style   = TOAST_STYLE_MAX_NUM;
    INT32               i4_ret              = TOASTR_FAIL;

    SCRN_SVR_VIEW_T*    pt_view = &(pt_this->t_view);
    t_e_g_toast_style = pt_this->e_toast_style;

    DBG_INFO(("[SCRN_SVR] [%s][%d]t_g_scrn_svr.e_toast_style=%d\n", __FUNCTION__, __LINE__, t_g_scrn_svr.e_toast_style));

    if (TOAST_STYLE_NO_SIGNAL_1 == t_e_g_toast_style)
    {
        i4_ret = a_toast_hide(pt_view->h_toast_no_signal);
    }

    NAV_LOG_ON_FAIL(i4_ret);
    t_e_g_toast_style = TOAST_STYLE_MAX_NUM;

    return i4_ret;
}

INT32 a_scrn_svr_hide_NO_SIGNAL_2(VOID)
{
    SCRN_SVR_T*         pt_this             = &t_g_scrn_svr;
    TOAST_STYLE_T       t_e_g_toast_style   = TOAST_STYLE_MAX_NUM;
    INT32               i4_ret              = TOASTR_FAIL;

    SCRN_SVR_VIEW_T*    pt_view = &(pt_this->t_view);
    t_e_g_toast_style = pt_this->e_toast_style;

    DBG_INFO(("[SCRN_SVR] [%s][%d]t_g_scrn_svr.e_toast_style=%d\n", __FUNCTION__, __LINE__, t_g_scrn_svr.e_toast_style));

    if (TOAST_STYLE_NO_SIGNAL_2 == t_e_g_toast_style)
    {
        i4_ret = a_toast_hide(pt_view->h_toast_no_signal_2);
    }

    NAV_LOG_ON_FAIL(i4_ret);
    t_e_g_toast_style = TOAST_STYLE_MAX_NUM;

    return i4_ret;
}


VOID a_reset_err_msg_id(VOID)
{
    SCRN_SVR_T* pt_this = &t_g_scrn_svr;

    _MSG_SET_MSG_ID(TV_WIN_ID_MAIN, MSG_STR_ID_LAST_VALID_ENTRY);

    //_MSG_SET_MLM_KEY
    _scrn_svr_set_err_msg_id(&(pt_this->t_msgs[TV_WIN_ID_MAIN]));
}


BOOL a_scrn_svr_check_err_msg_for_format_not_support(VOID)
{
    UTF16_T*    w2s_str         = NULL;
    UTF16_T*    w2s_tmp         = NULL;
    UINT8       ui1_lang_idx    = 0;

    w2s_str         = nav_get_crnt_err_msg();
    ui1_lang_idx    = nav_get_mlm_lang_id();

    if(NULL == w2s_str)
    {
        return FALSE;
    }

    if(0 == w2s_str[0])
    {
        return FALSE;
    }

#ifdef MLM_NAV_KEY_NAV_SCRAMBLED_VIDEO
    w2s_tmp = MLM_NAV_TEXT(ui1_lang_idx,MLM_NAV_KEY_NAV_SCRAMBLED_VIDEO);
    if(0 == c_uc_w2s_strncmp(w2s_str, w2s_tmp, MAX_ERR_MSG_SIZE))
    {
        return TRUE;
    }
#endif

    return FALSE;

}

static INT32 _scrn_svr_get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32           i4_ret      =   NAVR_FAIL;
    TV_WIN_ID_T     t_win_id    =   TV_WIN_ID_MAIN;

    i4_ret = a_tv_get_focus_win(&t_win_id);
   NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id, pt_isl_rec);
    NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

INT32 scrn_svr_set_str_id_to_empty(VOID)
{
    TV_WIN_ID_T e_focus_win_id = TV_WIN_ID_LAST_VALID_ENTRY;
    nav_get_focus_id (&e_focus_win_id);

    //check window ID
    if(e_focus_win_id >= TV_WIN_ID_LAST_VALID_ENTRY)
    {
        return NAVR_FAIL;
    }

    if(t_g_scrn_svr.t_msgs[e_focus_win_id].e_type == SCRN_SVR_MSG_TYPE_MSG_ID)
    {
       t_g_scrn_svr.t_msgs[e_focus_win_id].u.e_msg_id = MSG_STR_ID_EMPTY;
    }

    return NAVR_OK;
}



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
 * $RCSfile: nav_zoom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Zoom mode is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_ZOOM_MODE_SUPPORT

#include "u_common.h"
#include "u_gl.h"
#include "u_irrc_btn_def.h"

#include "c_handle.h"
#include "c_gl.h"
#include "c_iom.h"
#include "c_wgl.h"

#include "app_util/a_zoom_mode.h"

#include "nav/zoom/a_nav_zoom.h"
#include "nav/zoom/nav_zoom.h"
#include "nav/zoom/nav_zoom_view.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/a_custom_log.h"
#include "res/nav/nav_variant.h"
#include "res/nav/zoom/nav_zoom_custom.h"
#include "app_util/zoom_mode/zoom_mode.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct __NAV_ZOOM_MEMBER_T
{
    BOOL                        b_enabled;                          /* This component is enabled or not */
    BOOL                        b_is_normal;                        /* TV_NORMAL or PIP/POP */
} _NAV_ZOOM_MEMBER_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _NAV_ZOOM_MEMBER_T       t_g_zoom;

extern ZOOM_INDICATE_T          indicate_view;
extern BOOL                     a_nav_zoom_mode_get_msg_show_status();

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

static INT32 _nav_zoom_deinit(VOID);

static INT32 _nav_zoom_handle_msg(
                NAV_CONTEXT_T*      pt_ctx,
                NAV_UI_MSG_T*       pt_ui_msg,
                VOID*               pv_arg1);

//static INT32 _nav_zoom_mode_indicate_view_init(VOID);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _nav_zoom_comp_state_trans_nfy
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
static INT32 _nav_zoom_comp_state_trans_nfy (NAV_COMP_STATE_TRANS_COND_T e_cond,
                                             NAV_COMP_ID_T  e_from_comp_id,
                                             NAV_COMP_ID_T  e_to_comp_id,
                                             UINT32         ui4_data,
                                             VOID*          pv_tag)
{
    INT32                   i4_ret;

    /* customize this message */
    i4_ret = nav_zoom_cust_comp_state_trans_nfy(e_cond, e_from_comp_id, e_to_comp_id);
    if (i4_ret != NAVR_NOT_IMPLEMENT)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_init(
    NAV_CONTEXT_T*          pt_ctx)
{
    _NAV_ZOOM_MEMBER_T*     pt_this = &t_g_zoom;
    INT32                   i4_ret;

    do
    {
        /*init data member*/
        pt_this->b_enabled   = TRUE;

        i4_ret = a_zoom_mode_init();
        if (ZMR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_zoom_mode init failed.\n\r");
            break;
        }

        i4_ret = nav_zoom_cust_init();
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_cust_init failed.\n\r");
            break;
        }

        /* Register comp transition nfy. */
        i4_ret = nav_register_comp_state_trans_nty_fct (
                                    NAV_COMP_ID_ZOOM,
                                    _nav_zoom_comp_state_trans_nfy,
                                    NULL);
        if (i4_ret != NAVR_OK)
        {
            return NAVR_FAIL;
        }

        /* should enable/disable zoom mode after receive power on msg */

        /* init the nav zoom sector notifaction widgets */
        i4_ret = nav_zoom_mode_indicate_view_init();
        if (i4_ret != NAVR_OK)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "indicate_view_init failed.\n\r");
            return NAVR_FAIL;
        }
        i4_ret = nav_zoom_mode_msg_view_init();
        if (i4_ret != NAVR_OK)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "msg_view_init failed.\n\r");
            return NAVR_FAIL;
        }

    #if 0
        UINT8 ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;

        i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);
        if (APP_CFGR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_cfg_cust get_zoom_mode failed.\n\r");
            break;
        }

        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "current_zoom_mode: %u.\n\r", ui1_zoom_mode);

        if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            nav_zoom_mode_enable();
        }
        else
        {
            nav_zoom_mode_disable();
        }
    #endif

        return NAVR_OK;

    } while(0);

    /* free resoruce */
    _nav_zoom_deinit();

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_deinit(VOID)
{
    _NAV_ZOOM_MEMBER_T*       pt_this = &t_g_zoom;

    /*zero memory*/
    c_memset(pt_this, 0, sizeof(_NAV_ZOOM_MEMBER_T));

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_hide_zoom_indicate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_hide_zoom_indicate(VOID)
{
    INT32                           i4_ret;

    i4_ret = c_wgl_set_visibility(indicate_view.h_frame_sector, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"_nav_zoom_hide_zoom_indicate,hide zoom sector indicate fail.\r\n"));
    }
    i4_ret = c_wgl_repaint(indicate_view.h_frame_msg, NULL, TRUE);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"_nav_zoom_hide_zoom_indicate,repaint zoom sector indicate fail.\r\n"));
    }

    i4_ret = c_wgl_set_visibility(indicate_view.h_frame_msg, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"_nav_zoom_hide_zoom_indicate,hide zoom msg box fail.\r\n"));
    }
    i4_ret = c_wgl_repaint(indicate_view.h_frame_msg, NULL, TRUE);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"_nav_zoom_hide_zoom_indicate,repaint zoom msg box fail.\r\n"));
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_handle_msg(
    NAV_CONTEXT_T*                 pt_ctx,
    NAV_UI_MSG_T*                  pt_ui_msg,
    VOID*                          pv_arg1)
{
    INT32                           i4_ret;

    /*Hide zoom mode indicate when RC off. For don't show the zoom mode msg box when the RC on and the zoom mode is on. */
    if (pt_ui_msg->e_id == NAV_UI_MSG_POWER_OFF)
    {
        _nav_zoom_hide_zoom_indicate();
    }
    /* customize this message */
    i4_ret = nav_zoom_cust_handle_msg (pt_ui_msg, pv_arg1);
    if (i4_ret != NAVR_NOT_IMPLEMENT)
    {
        return i4_ret;
    }

    switch(pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        {
            NAV_XNG_SRC_TRGT_T*     pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;

            NAV_ASSERT(pt_xng_info);

            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] NAV_UI_MSG_BEFORE_SVC_CHANGE  %d \n", pt_xng_info->e_type));
        }
        break;

    case NAV_UI_MSG_OTHER_APP_RESUMED:
        {
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] NAV_UI_MSG_OTHER_APP_RESUMED, APP: %s \n", (CHAR*)pv_arg1));
        }
        break;

    case NAV_UI_MSG_APP_RESUMED:
        {
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] NAV_UI_MSG_APP_RESUMED.\n"));
        }
        break;

    case NAV_UI_MSG_FOCUS_CHANGED:
        {
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] NAV_UI_MSG_FOCUS_CHANGED.\n"));
        }
        break;

    case NAV_UI_MSG_APP_PAUSING:
        {
             DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] NAV_UI_MSG_APP_PAUSING.\n"));
        }
        break;

    case NAV_UI_MSG_POWER_ON:
        {
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] NAV_UI_MSG_POWER_ON.\n"));
        }
        break;

    case NAV_UI_MSG_POWER_OFF:
        {
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] NAV_UI_MSG_POWER_OFF.\n"));
        }
        break;

    default:
        break;
    }

    return NAVR_OK;
}

static BOOL _nav_zoom_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    if (a_nav_zoom_mode_get_msg_show_status()
        && APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status()
        && BTN_EXIT == ui4_key_code)
    {
        nav_zoom_mode_msg_hide();
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_zoom_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_zoom_register(VOID)
{
    NAV_COMP_T                        t_comp;
    INT32                             i4_ret;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _nav_zoom_init;
    t_comp.pf_deinit         = _nav_zoom_deinit;
    t_comp.pf_is_key_handler = _nav_zoom_is_key_handler;
    t_comp.pf_activate       = NULL;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = NULL;
    t_comp.pf_handle_msg     = _nav_zoom_handle_msg;

    DBG_LOG_PRINT(("%s:%d,zoom_id:%d,zoom_set:%x.=======================\r\n",__FILE__,__LINE__,
        NAV_COMP_ID_ZOOM,COMP_EXEC_SET_ZOOM));
    i4_ret = nav_register_component(NAV_COMP_ID_ZOOM, &t_comp, COMP_EXEC_SET_ZOOM);
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_ZOOM) failed. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

    return NAVR_OK;
}

BOOL a_nav_zoom_get_num_pad_navi_status (VOID)
{
    return a_nav_zoom_cust_get_num_pad_navi_status();
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_enable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_enable(VOID)
{
    INT32                       i4_ret;

    i4_ret = a_zoom_mode_enable();
    if (ZMR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_zoom_mode enable failed, i4_ret=%d.\n\r", i4_ret);
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_disable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_disable(VOID)
{
    INT32                       i4_ret;
    /* hide the indecate icon  */
    nav_zoom_mode_indicate_icon_hide(NULL, NULL, NULL);

    i4_ret = a_zoom_mode_disable();
    if (ZMR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_zoom_mode disable failed, i4_ret=%d.\n\r", i4_ret);
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
//#ifdef VIZIO_FUSION_SUPPORT

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_mode_enlarge_sector
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_mode_enlarge_sector(
    GL_OSD_ZOOM_SECTOR_T    at_zoom_sector[],
    UINT32                  ui4_zoom_sector_count
    )
{
    INT32                       i4_ret;

    i4_ret = a_zoom_mode_enlarge_sector(at_zoom_sector, ui4_zoom_sector_count);
    if (ZMR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_zoom_mode enlarge_sector failed.\n\r");
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
//#endif


#endif /*APP_ZOOM_MODE_SUPPORT*/

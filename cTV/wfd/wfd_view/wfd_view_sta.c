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
 * $RCSfile: wfd_view.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: cheng.shen $
 * $MD5HEX: 8ebc2c7a2c0fc209f18ef9bd3ccc4afd $
 *
 * Description:
 *         This header file contains public interfaces, constant and type
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
#include "wfd_view_sta.h"
#include "../wfd_rtsp_conn.h"
#include "../wfd_p2p_conn.h"
#define WFD_VIEW_STA_ELEM_NUM 5

UINT32 ui4_g_progress = 0;
WFD_VIEW_STA_T e_wfd_sta = WFD_VIEW_STA_END;
static VOID _wfd_sta_timer_nfy_fct (HANDLE_T h_timer, VOID* pv_tag);

static BOOL  wfd_view_sta_is_current_view(VOID)
{
    if(wfd_view_get_current_view() == WFD_VIEW_STATUS)
        return TRUE;

    return FALSE;
}


INT32 wfd_view_sta_update_icon(UINT32 ui4_progress)
{
    HANDLE_T h_handle = NULL_HANDLE;
    WGL_IMG_INFO_T    t_img_info;
    INT32 i4_ret;
    switch(ui4_progress)
    {
    case 1:
        h_handle = h_g_wfd_load_1_img;
        break;
    case 2:
        h_handle = h_g_wfd_load_2_img;
        break;
    case 3:
        h_handle = h_g_wfd_load_3_img;
        break;
    case 4:
        h_handle = h_g_wfd_load_4_img;
        break;
    case 5:
        h_handle = h_g_wfd_load_5_img;
        break;
    case 6:
        h_handle = h_g_wfd_load_6_img;
        break;
    case 7:
        h_handle = h_g_wfd_load_7_img;
        break;
    default:
        h_handle = h_g_wfd_load_8_img;
        break;
    }

    /* set title icon image buffer*/
    t_img_info.e_type                         = WGL_IMG_SET_BASIC;
    t_img_info.u_img_data.t_basic.t_enable    = h_handle;
    t_img_info.u_img_data.t_basic.t_disable   = h_handle;

    i4_ret = c_wgl_do_cmd(t_g_wfd_view_main.h_status_load,
                  WGL_CMD_GL_SET_IMAGE,
                  WGL_PACK(WGL_IMG_BK),
                  WGL_PACK(&t_img_info));

    WFD_DBG_ERR_EX(i4_ret,WGLR_OK);

    return WFDR_OK;
}

static VOID _wfd_sta_notify_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3,VOID* pv_tag4)
{
    if(!wfd_view_sta_is_current_view())
    {
        c_timer_stop(t_g_wfd_view_main.h_timer_sta_load);
        return;
    }
    WFD_VIEW_CMD_T e_cmd = (WFD_VIEW_CMD_T)(UINT32)pv_tag1;
    UTF16_T pw2s_text[32] = L"";
    CHAR p_timeout[32] = {0};
    INT32 i4_timeout = -1;
    if(e_cmd == WFD_VIEW_CMD_STA_LOAD)
    {
        if(e_wfd_sta == WFD_VIEW_STA_P2P_START)
        {
            i4_timeout = wfd_app_get_timeout();
            if(i4_timeout < 0)
            {
                WFD_DBG_LOG_EX("ERROR time out",i4_timeout);
            }
            else
            {
                c_sprintf(p_timeout,"Connection time:%d seconds",i4_timeout);
                c_uc_ps_to_w2s(p_timeout, pw2s_text, 32);
                c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2(4,0),
                     WGL_PACK(pw2s_text));
                c_wgl_repaint(t_g_wfd_view_main.h_status_show, NULL,FALSE);
            }
        }
        else
        {
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(4,0),
                 NULL);
            c_wgl_repaint(t_g_wfd_view_main.h_status_show, NULL,FALSE);

        }

        if(e_wfd_sta == WFD_VIEW_STA_P2P_START || e_wfd_sta == WFD_VIEW_STA_RTSP_START || e_wfd_sta == WFD_VIEW_STA_P2P_DISCONNECT)
        {

            UINT32 ui4_temp;
            ui4_temp = (ui4_g_progress++)%8 ;

            WFD_RET_VOID_ON_ERR(wfd_view_sta_update_icon(ui4_temp));

            c_wgl_repaint(t_g_wfd_view_main.h_status_load, NULL,FALSE);

            c_timer_start (t_g_wfd_view_main.h_timer_sta_load,
                          WFD_VIEW_STA_LOADING_UPD,
                          X_TIMER_FLAG_ONCE,
                          _wfd_sta_timer_nfy_fct,
                          NULL);
        }
        else
        {
            WFD_DBG_LOG_EX("sta",e_cmd);
            c_timer_stop(t_g_wfd_view_main.h_timer_sta_load);
            c_wgl_show(t_g_wfd_view_main.h_status_load, WGL_SW_HIDE);
        }
    }

    return;
}

static VOID _wfd_sta_timer_nfy_fct (HANDLE_T h_timer, VOID* pv_tag)
{
    if (h_timer == t_g_wfd_view_main.h_timer_sta_load)
    {
        wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_sta_notify_hdlr, (VOID*)(UINT32)WFD_VIEW_CMD_STA_LOAD,
                        NULL,NULL,NULL);
    }

    return;
}

INT32 wfd_view_sta_do_msg(WFD_MSG_T e_msg,VOID* pv_param)
{
    WFD_DBG_LOG(e_msg);
    switch(e_msg)
    {
        case WFD_MSG_VIEW_CONNECTED_TO_STA:
        {
            e_wfd_sta = WFD_VIEW_STA_IN_CONNECT;
            wfd_view_sta_update_text(TRUE);
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            wfd_view_sta_show_icon(FALSE);
            break;
        }

        case WFD_MSG_VIEW_TO_STA:
        {
            e_wfd_sta = WFD_VIEW_STA_P2P_START;
            wfd_view_sta_update_text(TRUE);
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            wfd_view_sta_show_icon(TRUE);
            c_timer_stop(t_g_wfd_view_main.h_timer_sta_load);
            c_timer_start (t_g_wfd_view_main.h_timer_sta_load,
                                      WFD_VIEW_STA_LOADING_UPD,
                                      X_TIMER_FLAG_ONCE,
                                      _wfd_sta_timer_nfy_fct,
                                      NULL);
            break;
        }
        case WFD_MSG_VIEW_DISCONNECT_P2P_OK:
        {
            e_wfd_sta = WFD_VIEW_STA_P2P_DISCONNECT_OK;
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            wfd_view_sta_show_icon(FALSE);
            c_timer_stop(t_g_wfd_view_main.h_timer_sta_load);
            break;
        }
        case WFD_MSG_VIEW_DISCONNECT_P2P:
        {
            e_wfd_sta = WFD_VIEW_STA_P2P_DISCONNECT;
            wfd_view_sta_update_text(TRUE);
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            wfd_view_sta_show_icon(TRUE);
            c_timer_stop(t_g_wfd_view_main.h_timer_sta_load);
            c_timer_start (t_g_wfd_view_main.h_timer_sta_load,
                          WFD_VIEW_STA_LOADING_UPD,
                          X_TIMER_FLAG_ONCE,
                          _wfd_sta_timer_nfy_fct,
                          NULL);
            break;
        }


        case WFD_MSG_VIEW_DISCONNECT_P2P_FAIL:
        {
            e_wfd_sta = WFD_VIEW_STA_P2P_DISCONNECT_FAIL;
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            wfd_view_sta_show_icon(FALSE);
            c_timer_stop(t_g_wfd_view_main.h_timer_sta_load);
            break;
        }

        /*case WFD_MSG_P2P_GROUP_REMOVED:*/
        case WFD_MSG_AP_STA_DISCONNECTED:
        {
            if(wfd_view_get_current_view()!= WFD_VIEW_STATUS)
            {
                wfd_main_send_msg_to_view(WFD_MSG_P2P_GROUP_DISAPPEAR,NULL);
                return WFDR_OK;
            }
            e_wfd_sta = WFD_VIEW_STA_P2P_DISCONNECT_OK;
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            wfd_view_sta_show_icon(FALSE);
            break;
        }

        /*case WFD_MSG_P2P_GROUP_START:*/
        case WFD_MSG_AP_STA_CONNECTED:
        {
            e_wfd_sta = WFD_VIEW_STA_START_P2P_OK;
            wfd_view_sta_update_text(FALSE);
            break;
        }

        case WFD_MSG_VIEW_START_RTSP:
        {
            e_wfd_sta = WFD_VIEW_STA_RTSP_START;
            wfd_view_sta_update_text(TRUE);
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            break;
        }

        case WFD_MSG_VIEW_START_RTSP_OK:
        {
            e_wfd_sta = WFD_VIEW_STA_START_RTSP_OK;
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_toggle_show(FALSE);
            wfd_main_send_msg_to_view(WFD_MSG_VIEW_TO_PLAY,NULL);

            return WFDR_OK;
        }

        case WFD_MSG_VIEW_START_RTSP_FAIL:
        {
            e_wfd_sta = WFD_VIEW_STA_START_RTSP_FAIL;
            wfd_view_sta_update_text(FALSE);

            wfd_view_sta_update_button();
            break;
        }

        case WFD_MSG_VIEW_STOP_RTSP:
        {
            e_wfd_sta = WFD_VIEW_STA_STOP_RTSP;
            wfd_view_sta_update_text(TRUE);
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            break;
        }

        case WFD_MSG_VIEW_STOP_RTSP_OK:
        {
            e_wfd_sta = WFD_VIEW_STA_STOP_RTSP_OK;
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            break;
        }

        case WFD_MSG_VIEW_STOP_RTSP_FAIL:
        {
            e_wfd_sta = WFD_VIEW_STA_STOP_RTSP_FAIL;
            wfd_view_sta_update_text(FALSE);
            wfd_view_sta_update_button();
            break;
        }

        default:
            break;
    }
    wfd_view_sta_toggle_show(TRUE);
    return WFDR_OK;
}

INT32 wfd_view_sta_update_text(BOOL b_clean)
{
    UTF16_T pw2s_text[32] = L"";
    if(b_clean)
    {
        for(UINT32 ui4_i = 0; ui4_i < WFD_VIEW_STA_ELEM_NUM; ui4_i++)
        {
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2(ui4_i, 0),
                  WGL_PACK(pw2s_text));
        }
        return WFDR_OK;
    }
    UINT16 ui2_mlm_id;
    switch (e_wfd_sta)
    {
        case WFD_VIEW_STA_P2P_DISCONNECT:
        {
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_STOP_P2P_CONNECT;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(0,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;
        }

        case WFD_VIEW_STA_P2P_DISCONNECT_OK:
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_P2P_DISCONNECT;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(1,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;
        case WFD_VIEW_STA_P2P_DISCONNECT_FAIL:
            c_uc_ps_to_w2s("P2P Disconnect failed", pw2s_text, 32);
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(1,0),
                 WGL_PACK(pw2s_text));
            break;

        case WFD_VIEW_STA_START_P2P_FAIL :
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_P2P_CONNECT_FAIL;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(1,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;
        case WFD_VIEW_STA_START_RTSP_FAIL :
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_RTSP_FAIL;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(3,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;
        case WFD_VIEW_STA_START_P2P_OK :
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_P2P_CONNECT_SUCCESS;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(1,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;
        case WFD_VIEW_STA_START_RTSP_OK :
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_RTSP_SUCCESS;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(3,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;
        case WFD_VIEW_STA_P2P_START :
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_START_P2P_CONNECT;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(0,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;

        case WFD_VIEW_STA_RTSP_START :
            c_uc_ps_to_w2s("Start Wi-Fi Display Session", pw2s_text, 32);
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(2,0),
                 WGL_PACK(pw2s_text));
            break;
        case WFD_VIEW_STA_STOP_RTSP :
            c_uc_ps_to_w2s("Wi-Fi Display Session is stopping", pw2s_text, 32);
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(2,0),
                 WGL_PACK(pw2s_text));
            break;
        case WFD_VIEW_STA_STOP_RTSP_FAIL :
            c_uc_ps_to_w2s("Stop RTSP Fail", pw2s_text, 32);
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(2,0),
                 WGL_PACK(pw2s_text));
            break;
        case WFD_VIEW_STA_IN_CONNECT :
        case WFD_VIEW_STA_STOP_RTSP_OK:
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_WFD_STOP;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(2,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            ui2_mlm_id = (UINT16)MLM_WFD_KEY_RESUME_NOTE;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(3,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));

            ui2_mlm_id = (UINT16)MLM_WFD_KEY_DISCONNECT_NOTE;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_show,
                 WGL_CMD_LB_SET_ITEM_TEXT,
                 WGL_PACK_2(4,0),
                 WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
            break;

        default:
            break;
    }
    return WFDR_OK;
}

INT32 wfd_view_sta_show_icon(BOOL b_show)
{
    if(b_show)
    {
        WGL_IMG_INFO_T    t_img_info;
        HANDLE_T h_handle;
        h_handle = h_g_wfd_load_1_img;
        t_img_info.e_type                         = WGL_IMG_SET_BASIC;
        t_img_info.u_img_data.t_basic.t_enable    = h_handle;
        t_img_info.u_img_data.t_basic.t_disable   = h_handle;

        c_wgl_do_cmd(t_g_wfd_view_main.h_status_load,
                      WGL_CMD_GL_SET_IMAGE,
                      WGL_PACK(WGL_IMG_BK),
                      WGL_PACK(&t_img_info));
        c_wgl_set_visibility(t_g_wfd_view_main.h_status_load, WGL_SW_NORMAL);
    }
    else
    {
        c_wgl_set_visibility(t_g_wfd_view_main.h_status_load, WGL_SW_HIDE);
    }

    return WFDR_OK;
}

INT32 wfd_view_sta_update_button(VOID)
{
    UINT16 ui2_mlm_id;
    BOOL b_1 = FALSE;
    BOOL b_2 = FALSE;
    BOOL b_back= FALSE;
    c_wgl_enable(t_g_wfd_view_main.h_status_btn1,FALSE);
    c_wgl_set_visibility(t_g_wfd_view_main.h_status_btn1, WGL_SW_HIDE);

    c_wgl_enable(t_g_wfd_view_main.h_status_btn2,FALSE);
    c_wgl_set_visibility(t_g_wfd_view_main.h_status_btn2, WGL_SW_HIDE);

    c_wgl_enable(t_g_wfd_view_main.h_status_back,FALSE);
    c_wgl_set_visibility(t_g_wfd_view_main.h_status_back, WGL_SW_HIDE);
    WFD_DBG_LOG(e_wfd_sta);
    switch (e_wfd_sta)
    {
        case WFD_VIEW_STA_P2P_DISCONNECT_FAIL:
            b_back = TRUE;
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_CANCEL;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_back,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                     WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));
            b_1 = TRUE;
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_DO_AGAIN;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_btn1,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                     WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));
            break;

        case WFD_VIEW_STA_STOP_RTSP:
        case WFD_VIEW_STA_STOP_RTSP_OK:
        case WFD_VIEW_STA_IN_CONNECT:
        case WFD_VIEW_STA_START_RTSP_FAIL:
            b_back = TRUE;
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_BTN_BACK;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_back,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                     WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));
            b_1 = TRUE;
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_BTN_DISCONNECTION;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_btn1,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                     WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));
            b_2 = TRUE;
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_RESUME;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_btn2,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                     WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));
            break;
        case WFD_VIEW_STA_START_P2P_FAIL :
        case WFD_VIEW_STA_P2P_DISCONNECT_OK:
        case WFD_VIEW_STA_STOP_RTSP_FAIL:
        case WFD_VIEW_STA_P2P_START:
            b_back = TRUE;
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_CANCEL;
            c_wgl_do_cmd(t_g_wfd_view_main.h_status_back,
                     WGL_CMD_BTN_SET_TEXT,
                     WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                     WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));
              break;
       case WFD_VIEW_STA_P2P_DISCONNECT:
           b_back = TRUE;
           ui2_mlm_id = (UINT16) MLM_WFD_KEY_BTN_BACK;
           c_wgl_do_cmd(t_g_wfd_view_main.h_status_back,
                   WGL_CMD_BTN_SET_TEXT,
                   WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                   WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));

           break;
      case  WFD_VIEW_STA_RTSP_START:

            break;
        default:
            break;
    }

    WFD_DBG_LOG(b_1);

    WFD_DBG_LOG(b_2);
    WFD_DBG_LOG(b_back);
    if(b_1)
    {
        c_wgl_enable(t_g_wfd_view_main.h_status_btn1,TRUE);
        c_wgl_set_visibility(t_g_wfd_view_main.h_status_btn1, WGL_SW_NORMAL);
    }
    if(b_2)
    {
        c_wgl_enable(t_g_wfd_view_main.h_status_btn2,TRUE);
        c_wgl_set_visibility(t_g_wfd_view_main.h_status_btn2, WGL_SW_NORMAL);
    }

    if(b_back)
    {
        c_wgl_enable(t_g_wfd_view_main.h_status_back,TRUE);
        c_wgl_set_visibility(t_g_wfd_view_main.h_status_back, WGL_SW_NORMAL);
    }
    return WFDR_OK;
}


INT32 wfd_view_sta_set_bk(VOID)
{
    int i4_ret = WFDR_FAIL;
    WGL_IMG_INFO_T   t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wfd_bg_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wfd_bg_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wfd_bg_img;

    i4_ret = c_wgl_do_cmd(
                    t_g_wfd_view_main.h_status_frm,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    WFD_DBG_LOG_EX("return",i4_ret);

    WFD_DBG_LOG_EX("the handle",t_img_info.u_img_data.t_standard.t_enable);
    return i4_ret;
}

INT32 wfd_view_sta_get_bk(VOID)
{
    int i4_ret = WFDR_FAIL;
    WGL_IMG_INFO_T   t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(
                    t_g_wfd_view_main.h_status_frm,
                    WGL_CMD_GL_GET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );

    WFD_DBG_LOG_EX("return",i4_ret);

    WFD_DBG_LOG_EX("the handle",t_img_info.u_img_data.t_standard.t_enable);
    return i4_ret;
}

INT32 wfd_view_sta_toggle_show(BOOL b_show)
{
    if(b_show)
    {
        wfd_view_set_current_view(WFD_VIEW_STATUS);
        c_wgl_set_focus(t_g_wfd_view_main.h_status_back,FALSE);
        c_wgl_show(t_g_wfd_view_main.h_status_frm,WGL_SW_NORMAL);
    }
    else
    {
        if(!wfd_view_sta_is_current_view())
        {
            return WFDR_OK;
        }
        wfd_view_set_current_view(WFD_VIEW_END);
        c_wgl_show(t_g_wfd_view_main.h_status_frm,WGL_SW_HIDE);
    }
    return WFDR_OK;
}

INT32 wfd_view_sta_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2)
{
    HANDLE_T           h_wgt_src;
    WGL_NOTIFY_DATA_T* pt_nfy_data;
    switch (ui4_msg)
    {
        case WGL_MSG_NOTIFY:
        {
            if(!wfd_view_sta_is_current_view())
            {
               break;
            }

            h_wgt_src = (HANDLE_T) pv_param1;
            pt_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

            if (WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code)
            {
                if(h_wgt_src == t_g_wfd_view_main.h_status_back)
                {
                    if(e_wfd_sta == WFD_VIEW_STA_RTSP_START)
                    {
                        WFD_CMD_CONT_T t_cmd;
                        t_cmd.e_cmd = WFD_CMD_STOP_RTSP;
                        t_cmd.pv_param = NULL;
                        wfd_view_send_cmd(t_cmd);
                        wfd_view_sta_toggle_show(FALSE);
                        break;
                    }
                    else if(e_wfd_sta == WFD_VIEW_STA_STOP_RTSP_FAIL)
                    {
                        WFD_CMD_CONT_T t_cmd;
                        t_cmd.e_cmd = WFD_CMD_STOP_TIMER;
                        t_cmd.pv_param = NULL;
                        wfd_view_send_cmd(t_cmd);
                    }
                    else if(e_wfd_sta == WFD_VIEW_STA_P2P_START )
                    {
                        WFD_CMD_CONT_T t_cmd;
                        t_cmd.e_cmd = WFD_CMD_CANCEL_CONNECT;
                        t_cmd.pv_param = NULL;
                        wfd_view_send_cmd(t_cmd);
                        wfd_view_sta_toggle_show(FALSE);
                        break;
                    }
                    else if(e_wfd_sta == WFD_VIEW_STA_START_P2P_OK)
                    {
                        WFD_CMD_CONT_T t_cmd;
                        t_cmd.e_cmd = WFD_CMD_STOP_TIMER;
                        t_cmd.pv_param = NULL;
                        wfd_view_send_cmd(t_cmd);

                        t_cmd.e_cmd = WFD_CMD_DISCONNECT_P2P;
                        t_cmd.pv_param = NULL;
                        wfd_view_send_cmd(t_cmd);
                        wfd_view_sta_toggle_show(FALSE);
                        break;
                    }
                    wfd_view_sta_toggle_show(FALSE);
                    wfd_view_main_toggle_show(TRUE,TRUE);
                    break;
                }
                else if(h_wgt_src == t_g_wfd_view_main.h_status_btn1)
                {
                    if(WFD_VIEW_STA_P2P_DISCONNECT_FAIL == e_wfd_sta
                      || WFD_VIEW_STA_STOP_RTSP == e_wfd_sta
                      || WFD_VIEW_STA_STOP_RTSP_OK == e_wfd_sta
                      || WFD_VIEW_STA_IN_CONNECT == e_wfd_sta
                      || WFD_VIEW_STA_START_RTSP_FAIL == e_wfd_sta)
                    {
                        wfd_main_send_msg_to_view(WFD_MSG_VIEW_CONFIRM_DIS_P2P, NULL);
                        return WFDR_OK;
                    }
                    else if(WFD_VIEW_STA_STOP_RTSP_FAIL == e_wfd_sta)
                    {
                        WFD_CMD_CONT_T t_cmd;
                        t_cmd.e_cmd = WFD_CMD_STOP_RTSP;
                        t_cmd.pv_param = NULL;
                        wfd_view_send_cmd(t_cmd);
                    }
                }
                else if(h_wgt_src == t_g_wfd_view_main.h_status_btn2)
                {
                    WFD_CMD_CONT_T t_cmd;
                    t_cmd.e_cmd = WFD_CMD_START_RTSP;
                    t_cmd.pv_param = NULL;
                    wfd_view_send_cmd(t_cmd);
                }
                break;
            }
        }
        default:
            break;
    }

    WFD_RET_ON_ERR_EX(c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2),WGLR_OK);
    return WFDR_OK;
}



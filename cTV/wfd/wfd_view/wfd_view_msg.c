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
#include "wfd_view.h"
#include "res/app_util/config/acfg_cust_odm.h"

WFD_VIEW_MSG_T e_view_msg = WFD_VIEW_MSG_END;

static BOOL  wfd_view_msg_is_current_view(VOID)
{
    if(wfd_view_get_current_view() == WFD_VIEW_MSG)
        return TRUE;

    return FALSE;
}

INT32 wfd_view_msg_do_msg(WFD_MSG_T e_msg,VOID* pv_param)
{

    WFD_DBG_LOG(e_msg);
    INT32 i4_ret;

    c_wgl_enable(t_g_wfd_view_main.h_msg_cancel , TRUE);
    c_wgl_enable(t_g_wfd_view_main.h_msg_yes , TRUE);
    c_wgl_set_visibility(t_g_wfd_view_main.h_msg_frm, WGL_SW_RECURSIVE);
    UTF16_T     pw2s_text_one[32] = {0};
    UTF16_T     pw2s_text_two[32] = {0};
    UINT16      ui2_mlm_id = 0;
    UINT16      ui2_mlm_id_2 = 0;
    BOOL        b_text = FALSE;
    switch(e_msg)
    {
        case WFD_MSG_DIRECT_ON:
        {
            c_uc_ps_to_w2s(" Wifi Direct is Enable", pw2s_text_one, 32);
            c_uc_ps_to_w2s(" Please Disable ", pw2s_text_two, 32);
            b_text = TRUE;
            c_wgl_enable(t_g_wfd_view_main.h_msg_cancel , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_cancel, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_yes, FALSE);
            e_view_msg = WFD_VIEW_MSG_DIRECT_ON;
            break;
        }

        case WFD_MSG_CONN_TIME_OUT:
        {
            wfd_view_toggle_show_view(wfd_view_get_current_view(),FALSE,FALSE);

            c_uc_ps_to_w2s(" Connection timeout", pw2s_text_one, 32);
            c_uc_ps_to_w2s(" Back to main menu", pw2s_text_two, 32);
            b_text = TRUE;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_CONN_TIME_OUT;
            break;
        }

        case WFD_MSG_MAIN_EXIT:
        {
            c_uc_ps_to_w2s(" Are you sure to exit?", pw2s_text_one, 32);
            c_uc_ps_to_w2s(" Please Confirm ", pw2s_text_two, 32);
            b_text = TRUE;
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_EXIT_WFD;
            break;
        }
        case WFD_MSG_DEVICE_PLUG:
        {
            c_uc_ps_to_w2s(" Wifi Dongle Connect", pw2s_text_one, 32);
            c_uc_ps_to_w2s("", pw2s_text_two, 32);
            b_text = TRUE;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_PLUG;
            break;
        }// wait for enhance
        case WFD_MSG_DEVICE_REMOVE:
        {
            c_uc_ps_to_w2s(" Wifi Dongle Disconnect", pw2s_text_one, 32);
            c_uc_ps_to_w2s("", pw2s_text_two, 32);
            b_text = TRUE;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_REMOVE;
            break;
        }
        case WFD_MSG_VIEW_CONFIRM_DIS_P2P:
        {
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_CUT_P2P_CONNECT;
            ui2_mlm_id_2 = (UINT16) MLM_WFD_KEY_P2P_CONNECTION;
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_P2P_DISCONNECT;
            break;
        }
        case WFD_MSG_VIEW_CONFIRM_DIS_RTSP:
        {
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_CUT_RTSP_CONNECT;
            ui2_mlm_id_2 = (UINT16) MLM_WFD_KEY_WIFI_SESSION;
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_RTSP_DISCONNECT;
            break;
        }

        case WFD_MSG_AP_STA_DISCONNECTED:
        {
            c_uc_ps_to_w2s("P2P is disconnected", pw2s_text_one, 32);
            c_uc_ps_to_w2s("", pw2s_text_two, 32);
            b_text = TRUE;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_GO_REMOVE;
            break;
        }

        case WFD_MSG_VIEW_MSG_TRY_CONN_FAIL:
        {
            c_uc_ps_to_w2s("Can't Connect", pw2s_text_one, 32);
            c_uc_ps_to_w2s("Please Try Again", pw2s_text_two, 32);
            b_text = TRUE;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_TRY_CONN_FAIL;
            break;
        }
        case WFD_MSG_P2P_GROUP_DISAPPEAR:
        {
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_WFD_STOP;
            ui2_mlm_id_2 = (UINT16) MLM_WFD_KEY_PRESS_CANCEL_TO_MAIN;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_GROUP_REMOVE;
            break;
        }
        case WFD_MSG_VIEW_INVALID_PIN:
        {
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_ENTER_VALID_PIN1;
            ui2_mlm_id_2 = (UINT16) MLM_WFD_KEY_DGTS8_VALID_PIN2;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes, FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_INVALID_PIN;
            break;
        }

        case WFD_MSG_RTSP_TEARDOWN:
        {
            ui2_mlm_id = (UINT16) MLM_WFD_KEY_WFD_STOP;
            ui2_mlm_id_2 = (UINT16) MLM_WFD_KEY_PRESS_CANCEL_TO_MAIN;
            c_wgl_enable(t_g_wfd_view_main.h_msg_yes , FALSE);
            c_wgl_set_visibility(t_g_wfd_view_main.h_msg_yes, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_wfd_view_main.h_msg_cancel, FALSE);
            e_view_msg = WFD_VIEW_MSG_RTSP_TEARDOWN;
            break;
        }
        default:
            break;
    }
    if(b_text)
    {
        i4_ret = c_wgl_do_cmd(t_g_wfd_view_main.h_msg_cont1,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK(pw2s_text_one),
                      WGL_PACK(c_uc_w2s_strlen(pw2s_text_one))
                      );

        WFD_DBG_ERR(i4_ret);

        i4_ret = c_wgl_do_cmd(t_g_wfd_view_main.h_msg_cont2,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK(pw2s_text_two),
                      WGL_PACK(c_uc_w2s_strlen(pw2s_text_two))
                      );

        WFD_DBG_ERR(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_do_cmd(t_g_wfd_view_main.h_msg_cont1,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                      WGL_PACK(c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)))
                      );

        WFD_DBG_ERR(i4_ret);

        i4_ret = c_wgl_do_cmd(t_g_wfd_view_main.h_msg_cont2,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id_2)),
                      WGL_PACK(c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id_2)))
                      );
        WFD_DBG_ERR(i4_ret);

    }
    WFD_RET_ON_ERR(wfd_view_msg_toggle_show(TRUE));
    return WFDR_OK;
}

INT32 wfd_view_msg_toggle_show(BOOL b_show)
{
    if(b_show)
    {
        if(wfd_view_msg_is_current_view())
        {
            return WFDR_OK;
        }
        wfd_view_set_current_view(WFD_VIEW_MSG);
        c_wgl_show(t_g_wfd_view_main.h_msg_frm,WGL_SW_NORMAL);
    }
    else
    {
        if(!wfd_view_msg_is_current_view())
        {
            return WFDR_OK;
        }
        wfd_view_set_current_view(WFD_VIEW_END);
        c_wgl_show(t_g_wfd_view_main.h_msg_frm,WGL_SW_HIDE);
    }
    return WFDR_OK;
}

INT32 wfd_view_msg_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2)
{
    HANDLE_T           h_wgt_src;
    WGL_NOTIFY_DATA_T* pt_nfy_data;
    WFD_VIEW_FRM_T     e_view;

    switch (ui4_msg)
    {
        case WGL_MSG_NOTIFY:
        {
            h_wgt_src = (HANDLE_T) pv_param1;
            pt_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

            if (WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code &&
                h_wgt_src == t_g_wfd_view_main.h_msg_cancel)
            {
                if(e_view_msg == WFD_VIEW_MSG_EXIT_WFD
//                    || e_view_msg == WFD_VIEW_MSG_PLUG
                    || e_view_msg == WFD_VIEW_MSG_P2P_DISCONNECT
                    || e_view_msg == WFD_VIEW_MSG_RTSP_DISCONNECT)
                {
                    e_view = wfd_view_get_last_view();
                    wfd_view_msg_toggle_show(FALSE);
                    wfd_view_toggle_show_view(e_view,TRUE,TRUE);
                    break;
                }
                else if(e_view_msg == WFD_VIEW_MSG_TRY_CONN_FAIL || e_view_msg == WFD_VIEW_MSG_CONN_TIME_OUT)
                {
                    wfd_view_msg_toggle_show(FALSE);
                    wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE);

                }else if(e_view_msg == WFD_VIEW_MSG_REMOVE)
                {
                    wfd_view_msg_toggle_show(FALSE);
                    wfd_view_main_set_refind(TRUE);
                    wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE);
                    break;
                }
                else if(e_view_msg == WFD_VIEW_MSG_GROUP_REMOVE)
                {
                    wfd_view_main_set_refind(TRUE);
                    wfd_view_msg_toggle_show(FALSE);
                    wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE);
                }
                else if(e_view_msg == WFD_VIEW_MSG_RTSP_TEARDOWN)
                {
                    wfd_view_main_set_refind(TRUE);
                    wfd_view_msg_toggle_show(FALSE);
                    wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE);
                }
                else if(e_view_msg == WFD_VIEW_MSG_INVALID_PIN)
                {
                    wfd_view_msg_toggle_show(FALSE);
                    wfd_view_toggle_show_view(WFD_VIEW_PIN,TRUE,TRUE);
                }
            }
            if (WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code &&
                h_wgt_src == t_g_wfd_view_main.h_msg_yes)
            {
                if(e_view_msg == WFD_VIEW_MSG_EXIT_WFD || e_view_msg == WFD_VIEW_MSG_DIRECT_ON)
                {
                    wfd_view_msg_toggle_show(FALSE);
                    wfd_view_main_set_refind(TRUE);
                    WFD_CMD_CONT_T t_cmd;
                    t_cmd.e_cmd = WFD_CMD_PAUSE;

                    if (a_cfg_custom_get_wifi_remote_support())
                    {
                        t_cmd.pv_param = (VOID*)(UINT32)e_view_msg;
                    }
                    else
                    {
                        t_cmd.pv_param = NULL;
                    }
                    wfd_view_send_cmd(t_cmd);
                    return WFDR_OK;
                }
                else if(e_view_msg == WFD_VIEW_MSG_P2P_DISCONNECT)
                {
                    wfd_view_msg_toggle_show(FALSE);

                    wfd_view_main_set_refind(TRUE);
                    WFD_CMD_CONT_T t_cmd;
                    t_cmd.e_cmd = WFD_CMD_DISCONNECT_P2P;
                    t_cmd.pv_param = NULL;
                    wfd_view_send_cmd(t_cmd);
                    return WFDR_OK;
                }
                else if(e_view_msg == WFD_VIEW_MSG_RTSP_DISCONNECT)
                {
                    wfd_view_msg_toggle_show(FALSE);

                    WFD_CMD_CONT_T t_cmd;
                    t_cmd.e_cmd = WFD_CMD_STOP_RTSP;
                    t_cmd.pv_param = NULL;
                    wfd_view_send_cmd(t_cmd);
                    return WFDR_OK;
                }
            }
        }
        default:
            break;
    }

    WFD_RET_ON_ERR_EX(c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2),WGLR_OK);
    return WFDR_OK;
}


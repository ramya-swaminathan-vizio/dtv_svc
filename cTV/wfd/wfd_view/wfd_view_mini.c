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
#include "wfd_view_mini.h"
#include "../wfd_p2p_conn.h"

static INT32 req_index = -1;
CHAR* ps_pin;
CHAR  ps_name[32] = {0};
WFD_VIEW_MINI_T e_mini = WFD_VIEW_MINI_END;
static BOOL  wfd_view_mini_is_current_view(VOID)
{
    if(wfd_view_get_current_view() == WFD_VIEW_MINI)
        return TRUE;

    return FALSE;
}

INT32 wfd_view_mini_do_msg(WFD_MSG_T e_msg,VOID* pv_param)
{
    WFD_DBG_LOG(e_msg);
    if(wfd_view_get_current_view()!= WFD_VIEW_MAIN)
        return WFDR_OK;

    if(((req_index = wfd_p2p_get_req_index()) < 0) || (wfd_p2p_get_req_name(ps_name) != WFDR_OK))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_OK;
    }
    wfd_view_toggle_show_view(WFD_VIEW_MAIN, FALSE, FALSE);

    switch(e_msg)
    {
       case WFD_MSG_P2P_NEG_REQ:
       case WFD_MSG_P2P_PBC_REQ:
        {
            e_mini = WFD_VIEW_MINI_NEG_REQ;
            break;
        }
        case WFD_MSG_P2P_ENTER_PIN_REQ:
        {

            e_mini = WFD_VIEW_MINI_ENTER_PIN_REQ;
            break;
        }
        case WFD_MSG_P2P_SHOW_PIN_REQ:
        {

            e_mini = WFD_VIEW_MINI_SHOW_PIN_REQ;
            ps_pin = (CHAR*)pv_param;
            break;
        }
        default:
            break;
    }
    WFD_RET_ON_ERR(wfd_view_mini_toggle_show(TRUE));
    return WFDR_OK;
}


INT32 wfd_view_mini_toggle_show(BOOL b_show)
{
    UTF16_T     pw2s_text[32];
    if(b_show)
    {
        if(wfd_view_mini_is_current_view())
        {
            return WFDR_OK;
        }
        wfd_view_set_current_view(WFD_VIEW_MINI);
        c_uc_ps_to_w2s(ps_name, pw2s_text, 32);
        c_wgl_do_cmd( t_g_wfd_view_main.h_mini_cont,
              WGL_CMD_TEXT_SET_TEXT,
              WGL_PACK(pw2s_text),
              WGL_PACK(c_uc_w2s_strlen(pw2s_text))
              );
        c_wgl_set_focus(t_g_wfd_view_main.h_mini_exit,FALSE);
        c_wgl_show(t_g_wfd_view_main.h_mini_frm,WGL_SW_NORMAL);
    }
    else
    {
        if(!wfd_view_mini_is_current_view())
        {
            return WFDR_OK;
        }
        wfd_view_set_current_view(WFD_VIEW_END);
        c_wgl_show(t_g_wfd_view_main.h_mini_frm,WGL_SW_HIDE);
    }
    return WFDR_OK;
}

INT32 wfd_view_mini_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2)
{
    HANDLE_T           h_wgt_src;
    WGL_NOTIFY_DATA_T* pt_nfy_data;
    if(ui4_msg == WGL_MSG_NOTIFY)
    {
        h_wgt_src = (HANDLE_T) pv_param1;
        pt_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

        if (WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code)
        {
            wfd_view_mini_toggle_show(FALSE);
            if(h_wgt_src == t_g_wfd_view_main.h_mini_yes)
            {
                wfd_view_main_set_hl_pos((UINT16)req_index);
                if(e_mini == WFD_VIEW_MINI_NEG_REQ)
                {
                    WFD_CMD_CONT_T t_cmd;
                    t_cmd.e_cmd = WFD_CMD_PBC_ACCEPT;
                    t_cmd.pv_param = NULL;
                    wfd_view_send_cmd(t_cmd);
                }
                else if(e_mini == WFD_VIEW_MINI_SHOW_PIN_REQ)
                {
                    wfd_app_pin_display_accept();
                    wfd_main_send_msg_to_view(WFD_MSG_VIEW_SHOW_TO_PIN_REQ,(VOID*) ps_pin);
                }
                else if(e_mini == WFD_VIEW_MINI_ENTER_PIN_REQ)
                {
                    wfd_main_send_msg_to_view(WFD_MSG_VIEW_ENTER_TO_PIN_REQ,NULL);
                }
            }
            else if (h_wgt_src == t_g_wfd_view_main.h_mini_exit)
            {
                wfd_view_main_toggle_show(TRUE, TRUE);
            }
        }
    }

    WFD_RET_ON_ERR_EX(c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2),WGLR_OK);
    return WFDR_OK;
}


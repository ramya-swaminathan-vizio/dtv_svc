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
#include "wfd_view_pin.h"

WFD_VIEW_PIN_T e_pin = WFD_VIEW_PIN_END;
CHAR ps_enter_pin[32] = {0};
CHAR* ps_pin = NULL;

INT32 wfd_view_pin_update_text(VOID);

static INT32 wfd_view_pin_get_pineb_val(VOID)
{
    UTF16_T            w2s_security[32] = L"";

    c_wgl_do_cmd(t_g_wfd_view_main.h_pin_box,
                     WGL_CMD_EB_GET_TEXT,
                     WGL_PACK(w2s_security),
                     WGL_PACK(32));
        c_uc_w2s_to_ps(w2s_security, ps_enter_pin, 32);
        if(c_strlen(ps_enter_pin) < 8)
        {
            c_memset(ps_enter_pin, 0, sizeof(ps_enter_pin));
            c_memset(w2s_security, 0, sizeof(w2s_security));
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_box,
                    WGL_CMD_EB_SET_TEXT,
                    NULL,
                    NULL);
            wfd_view_toggle_show_view(WFD_VIEW_PIN,FALSE,FALSE);
            wfd_view_msg_do_msg(WFD_MSG_VIEW_INVALID_PIN,NULL);
            return WFDR_FAIL;
        }
        WFD_CMD_CONT_T t_cmd;
        t_cmd.e_cmd = WFD_CMD_PIN_CONNECT;
        t_cmd.pv_param = ps_enter_pin;
        wfd_view_toggle_show_view(WFD_VIEW_PIN,FALSE,FALSE);
        wfd_view_send_cmd(t_cmd);
        return WFDR_OK;
}

static BOOL  wfd_view_pin_is_current_view(VOID)
{
    if(wfd_view_get_current_view() == WFD_VIEW_PIN)
        return TRUE;

    return FALSE;
}

INT32 wfd_view_pin_do_msg(WFD_MSG_T e_msg,VOID* pv_param)
{
    WFD_DBG_LOG_EX("pin do",e_msg);
    switch(e_msg)
    {
        case WFD_MSG_VIEW_SHOW_TO_PIN:
        {
            e_pin = WFD_VIEW_PIN_SHOW;
            break;
        }

        case  WFD_MSG_VIEW_ENTER_TO_PIN:
        {
            e_pin = WFD_VIEW_PIN_ENTER;
            break;
        }

        case WFD_MSG_P2P_SHOW_PIN:
        {
            if(!wfd_view_pin_is_current_view())
                return WFDR_OK;

            e_pin = WFD_VIEW_PIN_GET;
            ps_pin = (char*)pv_param;
            WFD_DBG_LOG_EX(ps_pin,e_pin);
            break;
        }

        case WFD_MSG_P2P_ENTER_PIN:
        {
            if(!wfd_view_pin_is_current_view())
                return WFDR_OK;
            e_pin = WFD_VIEW_PIN_KEYPAD_AS;
            break;
        }
        case WFD_MSG_VIEW_ENTER_TO_PIN_REQ:
        {
            e_pin = WFD_VIEW_PIN_KEYPAD_AS;
            break;
        }

        case WFD_MSG_VIEW_SHOW_TO_PIN_REQ:
        {
            e_pin = WFD_VIEW_PIN_GET;
            ps_pin = (char*)pv_param;
            WFD_DBG_LOG_EX(ps_pin,e_pin);
            break;
        }
        default:
            break;
    }

    wfd_view_pin_update_text();
    wfd_view_pin_toggle_show(TRUE);

    return WFDR_OK;
}

INT32 wfd_view_pin_update_text(VOID)
{
    UTF16_T pw2s_text[32] = L"";

    c_wgl_do_cmd(
            t_g_wfd_view_main.h_pin_box,
            WGL_CMD_EB_SET_TEXT,
            (VOID*)NULL,
            (VOID*)0
            );
    switch(e_pin)
    {
        case WFD_VIEW_PIN_SHOW:
        {
            c_uc_ps_to_w2s("Wait Pin", pw2s_text, 32);
            c_wgl_enable( t_g_wfd_view_main.h_pin_box,FALSE);
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_box,
                    WGL_CMD_EB_SET_TEXT,
                    WGL_PACK(pw2s_text),
                    WGL_PACK(c_uc_w2s_strlen(pw2s_text))
                    );
            break;
        }

        case WFD_VIEW_PIN_ENTER:
        {
            c_uc_ps_to_w2s("Wait", pw2s_text, 32);
            c_wgl_enable( t_g_wfd_view_main.h_pin_box,FALSE);
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_box,
                    WGL_CMD_EB_SET_TEXT,
                    WGL_PACK(pw2s_text),
                    WGL_PACK(c_uc_w2s_strlen(pw2s_text))
                    );
            break;
        }

        case WFD_VIEW_PIN_KEYPAD_AS:
        {
            c_wgl_enable( t_g_wfd_view_main.h_pin_box,TRUE);
            c_uc_ps_to_w2s("Enter", pw2s_text, 32);
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_btn,
                    WGL_CMD_BTN_SET_TEXT,
                    WGL_PACK(pw2s_text),
                    WGL_PACK(c_uc_w2s_strlen(pw2s_text))
                    );
            c_uc_ps_to_w2s("Cancel", pw2s_text, 32);
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_btn_1,
                    WGL_CMD_BTN_SET_TEXT,
                    WGL_PACK(pw2s_text),
                    WGL_PACK(c_uc_w2s_strlen(pw2s_text))
                    );
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_box,
                    WGL_CMD_EB_SET_TEXT,
                    NULL,
                    NULL);
            wfd_view_pin_toggle_show(TRUE);
            break;
        }

        case WFD_VIEW_PIN_GET:
        {
            c_uc_ps_to_w2s(ps_pin, pw2s_text, 32);
            c_wgl_enable( t_g_wfd_view_main.h_pin_box,FALSE);
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_box,
                    WGL_CMD_EB_SET_TEXT,
                    WGL_PACK(pw2s_text),
                    WGL_PACK(c_uc_w2s_strlen(pw2s_text))
                    );

            c_uc_ps_to_w2s("Enter", pw2s_text, 32);
            c_wgl_do_cmd(
                    t_g_wfd_view_main.h_pin_btn,
                    WGL_CMD_BTN_SET_TEXT,
                    WGL_PACK(pw2s_text),
                    WGL_PACK(c_uc_w2s_strlen(pw2s_text))
                    );
            wfd_view_pin_toggle_show(TRUE);
            break;
        }
        default:
            break;
    }
    return WFDR_OK;
}

INT32 wfd_view_pin_toggle_show(BOOL b_show)
{
    if(b_show)
    {
        wfd_view_set_current_view(WFD_VIEW_PIN);
        if(e_pin != WFD_VIEW_PIN_KEYPAD_AS)
        {
            c_wgl_set_focus(t_g_wfd_view_main.h_pin_btn,FALSE);
        }
        else
        {
            c_wgl_set_focus(t_g_wfd_view_main.h_pin_box,FALSE);
        }
        c_wgl_show(t_g_wfd_view_main.h_pin_frm,WGL_SW_NORMAL);
    }
    else
    {
        if(!wfd_view_pin_is_current_view())
        {
            return WFDR_OK;
        }
        wfd_view_set_current_view(WFD_VIEW_END);
        c_wgl_show(t_g_wfd_view_main.h_pin_frm,WGL_SW_HIDE);
    }
    return WFDR_OK;
}

INT32 wfd_view_pin_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2)
{
    HANDLE_T   h_wgt_src;
    WGL_NOTIFY_DATA_T* pt_nfy_data;
    UINT32             ui4_key_code;
    INT32              i4Ret = WFDR_OK;

    switch (ui4_msg)
    {
        case WGL_MSG_NOTIFY:
        {
            h_wgt_src = (HANDLE_T) pv_param1;
            pt_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;
            WFD_DBG_LOG_EX("pin proc", pt_nfy_data->ui4_nc_code);
            if (WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code)
            {
                if(h_wgt_src == t_g_wfd_view_main.h_pin_btn)
                {
                    if(e_pin == WFD_VIEW_PIN_KEYPAD_AS)
                    {
                        i4Ret = wfd_view_pin_get_pineb_val();
                        if(i4Ret == WFDR_FAIL)
                            return WFDR_FAIL;
                    }
                    else if(e_pin == WFD_VIEW_PIN_GET)
                    {
                        wfd_view_toggle_show_view(WFD_VIEW_PIN,FALSE,FALSE);
                        //wfd_view_sta_do_msg(WFD_MSG_VIEW_TO_STA,NULL);
                        WFD_CMD_CONT_T t_cmd;
                        t_cmd.e_cmd = WFD_CMD_PIN_GET;
                        wfd_view_send_cmd(t_cmd);
                    }
                    else
                    {
                        wfd_view_toggle_show_view(WFD_VIEW_PIN,FALSE,FALSE);
                        wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE);
                    }
                }
                else if (h_wgt_src == t_g_wfd_view_main.h_pin_btn_1)
                {
                    c_wgl_do_cmd(
                            t_g_wfd_view_main.h_pin_box,
                            WGL_CMD_EB_SET_TEXT,
                            NULL,
                            NULL);
                    wfd_view_toggle_show_view(WFD_VIEW_PIN,FALSE,FALSE);
                    wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE);
                }
            }
            else if((WGL_NC_GL_KEY_DOWN == pt_nfy_data->ui4_nc_code)
                 ||(WGL_NC_GL_KEY_REPEAT == pt_nfy_data->ui4_nc_code))
            {
                ui4_key_code = pt_nfy_data->u.t_key.ui4_key_code;
               if(ui4_key_code == BTN_ENTER || ui4_key_code == BTN_SELECT)
               {
                    i4Ret = wfd_view_pin_get_pineb_val();
                    if(i4Ret == WFDR_FAIL)
                        return WFDR_FAIL;
               }
               else if(ui4_key_code == BTN_EXIT)
               {
                   wfd_view_toggle_show_view(WFD_VIEW_PIN,FALSE,FALSE);
                   wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE);
               }
            }
            break;
        }
        default:
            break;
    }

    WFD_RET_ON_ERR_EX(c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2),WGLR_OK);
    return WFDR_OK;
}



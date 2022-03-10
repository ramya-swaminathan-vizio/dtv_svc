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
#include "wfd_view_main.h"
#include "../wfd_p2p_conn.h"

UINT32 ui4_g_last_device_num = 0;
UINT16 ui2_hl_pos = 0;

BOOL b_should_refind = FALSE;

static BOOL  wfd_view_main_is_current_view(VOID);

UINT16 wfd_view_main_get_hl_pos(VOID)
{
    return ui2_hl_pos;
}

VOID wfd_view_main_set_hl_pos(INT32 num)
{
     ui2_hl_pos = num;
     return;
}


VOID wfd_view_main_set_refind(BOOL b_value)
{
     b_should_refind = b_value;
     return;
}

static INT32 wfd_view_main_update_list(BOOL b_clean)
{
    UINT32              ui4_device_num;
    UTF16_T             pw2s_text[32];
    WFD_DEVICE_INFO_T   t_info;
    CHAR                ps_port[10] = {0};
    UINT32              ui4_i = 0;
    HANDLE_T            h_focus = NULL_HANDLE;

    WFD_DBG_LOG(ui4_g_last_device_num);
    if(ui4_g_last_device_num > 0)
    {
        for (ui4_i = 0;ui4_i < ui4_g_last_device_num; ui4_i++ )
        {
            c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(ui4_i, 0),
                      NULL);

            c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(ui4_i, 1),
                      NULL);


            c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(ui4_i, 2),
                      NULL);

            c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(ui4_i, 3),
                      NULL);
        }
    }
    ui4_g_last_device_num = 0;

    c_wgl_do_cmd(
        t_g_wfd_view_main.h_main_device_list,
        WGL_CMD_LB_GET_HLT_INDEX,
        WGL_PACK(&ui2_hl_pos),
        NULL);

    if(ui2_hl_pos >= 0)
    {
        c_wgl_do_cmd(
                    t_g_wfd_view_main.h_main_device_list,
                    WGL_CMD_LB_UNHLT_ELEM,
                    WGL_PACK(ui2_hl_pos),
                    WGL_PACK(TRUE));
    }
    if(b_clean)
    {
        return WFDR_OK;
    }
    ui4_device_num = wfd_p2p_get_devicenumber();

    WFD_DBG_LOG(ui4_device_num);

    if(ui4_device_num <= 0)
    {
        return WFDR_OK;
    }
    for (ui4_i = 0; ui4_i < ui4_device_num && ui4_i < WFD_MAX_DEVICE_NUM; ui4_i++ )
    {
        c_memset(&t_info, 0, sizeof(WFD_DEVICE_INFO_T));
        WFD_RET_ON_ERR(wfd_app_get_device_info(&t_info,ui4_i));

        c_memset(pw2s_text, 0, sizeof(pw2s_text));
        c_uc_ps_to_w2s(t_info.ps_device_name, pw2s_text, 32);
        c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2(ui4_i, 0),
                  WGL_PACK(pw2s_text));

        c_memset(pw2s_text, 0, sizeof(pw2s_text));
        c_uc_ps_to_w2s(t_info.ps_device_type, pw2s_text, 32);
        c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2(ui4_i, 1),
                  NULL);//WGL_PACK(pw2s_text));


        c_memset(pw2s_text, 0, sizeof(pw2s_text));
        c_uc_ps_to_w2s(t_info.ps_device_mac, pw2s_text, 32);
        c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2(ui4_i, 2),
                  NULL);//WGL_PACK(pw2s_text));

        c_sprintf(ps_port,"%d",t_info.i4_device_port);
        c_uc_ps_to_w2s(ps_port, pw2s_text, 32);
        c_wgl_do_cmd(t_g_wfd_view_main.h_main_device_list,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2(ui4_i, 3),
                  NULL);//WGL_PACK(pw2s_text));
    }
    WFD_DBG_LOG(ui4_g_last_device_num);
    ui4_g_last_device_num = ui4_i;

    WFD_DBG_LOG(c_wgl_get_focus(&h_focus));
    if(h_focus == t_g_wfd_view_main.h_main_device_list)
    {
        c_wgl_do_cmd(
                    t_g_wfd_view_main.h_main_device_list,
                    WGL_CMD_LB_HLT_ELEM,
                    WGL_PACK(0),
                    NULL);
    }

    return WFDR_OK;
}

static INT32 wfd_view_main_update_sta(VOID)
{
    UTF16_T     pw2s_text[32];
    WFD_DEVICE_INFO_T t_info;

    c_memset(&t_info, 0, sizeof(WFD_DEVICE_INFO_T));
    c_memset(pw2s_text, 0, sizeof(pw2s_text));
    if(wfd_app_get_p2p_conn_sta() != WFD_P2P_CONN_CONNECTED)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    WFD_RET_ON_ERR(wfd_app_get_conn_device_info(&t_info));

#if 0 /* DTV00535431 */
    UINT16              ui2_mlm_id;
    CHAR                ps_port[10] = {0};
    ui2_mlm_id = (UINT16) MLM_WFD_KEY_CONNECT_STR;
    c_wgl_do_cmd(t_g_wfd_view_main.h_main_show_sta,
              WGL_CMD_LB_SET_ITEM_TEXT,
        WGL_PACK_2(0, 0),
        WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));

    c_memset(pw2s_text, 0, sizeof(pw2s_text));
    c_uc_ps_to_w2s(t_info.ps_device_name, pw2s_text, 32);
    c_wgl_do_cmd(t_g_wfd_view_main.h_main_show_sta,
              WGL_CMD_LB_SET_ITEM_TEXT,
              WGL_PACK_2(0, 1),
              WGL_PACK(pw2s_text));

    ui2_mlm_id = (UINT16) MLM_WFD_KEY_IP_STR;
    c_wgl_do_cmd(t_g_wfd_view_main.h_main_show_sta,
              WGL_CMD_LB_SET_ITEM_TEXT,
        WGL_PACK_2(0, 2),
        WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));

    c_memset(pw2s_text, 0, sizeof(pw2s_text));
    c_uc_ps_to_w2s(t_info.ps_device_ip, pw2s_text, 32);
    c_wgl_do_cmd(t_g_wfd_view_main.h_main_show_sta,
              WGL_CMD_LB_SET_ITEM_TEXT,
              WGL_PACK_2(0, 3),
              WGL_PACK(pw2s_text));

    ui2_mlm_id = (UINT16) MLM_WFD_KEY_PORT_STR;
    c_wgl_do_cmd(t_g_wfd_view_main.h_main_show_sta,
              WGL_CMD_LB_SET_ITEM_TEXT,
        WGL_PACK_2(0, 4),
        WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));

    c_memset(pw2s_text, 0, sizeof(pw2s_text));
    c_sprintf(ps_port,"%d",t_info.i4_device_port);
    c_uc_ps_to_w2s(ps_port, pw2s_text, 32);
    c_wgl_do_cmd(t_g_wfd_view_main.h_main_show_sta,
              WGL_CMD_LB_SET_ITEM_TEXT,
              WGL_PACK_2(0, 5),
              WGL_PACK(pw2s_text));
#endif
    return WFDR_OK;
}

static INT32 wfd_view_main_update_info(BOOL b_repaint)
{
    c_wgl_set_visibility(t_g_wfd_view_main.h_main_frm, WGL_SW_RECURSIVE);

    WFD_RET_ON_ERR(wfd_view_main_update_list(FALSE));

    #if 0
    if(wfd_view_main_update_sta() != WFDR_OK)  /* DTV00535431 */
    {
        c_wgl_set_visibility(t_g_wfd_view_main.h_main_show_sta, WGL_SW_HIDE);
    }
    #endif
    if(b_repaint)
    {
        c_wgl_repaint(t_g_wfd_view_main.h_main_frm,NULL,FALSE);
    }
    return WFDR_OK;
}

INT32 wfd_view_main_toggle_show(BOOL b_show, BOOL b_update)
{
    WFD_DBG_LOG(b_show);
    if(b_show)
    {
        if(b_should_refind)
        {
            b_should_refind = FALSE;
            if(wfd_app_get_p2p_sta() == WFD_P2P_ENABLED)
            {
                wfd_view_main_update_list(TRUE);
                WFD_CMD_CONT_T t_cmd;
                t_cmd.e_cmd = WFD_CMD_FIND;
                t_cmd.pv_param = NULL;
                wfd_view_send_cmd(t_cmd);
            }
        }

        if(wfd_view_main_is_current_view())
        {

            return WFDR_OK;
        }

        wfd_view_set_current_view(WFD_VIEW_MAIN);

        if(wfd_app_get_p2p_sta() != WFD_P2P_ENABLED)
        {
            WFD_CMD_CONT_T t_cmd;
            t_cmd.e_cmd = WFD_CMD_ENABLE;
            t_cmd.pv_param = NULL;
            wfd_view_send_cmd(t_cmd);
        }

        if(b_update)
        {
            wfd_view_main_update_info(FALSE);
        }
/*        if(ui4_g_last_device_num > 0 && ui2_hl_pos < ui4_g_last_device_num)
        {
            c_wgl_set_focus(t_g_wfd_view_main.h_main_device_list,FALSE);
            c_wgl_do_cmd(
                         t_g_wfd_view_main.h_main_device_list,
                         WGL_CMD_LB_HLT_ELEM,
                         WGL_PACK(ui2_hl_pos),
                         NULL);
        }
        else
        {
            c_wgl_set_focus(t_g_wfd_view_main.h_main_find,FALSE);
        }  */ //paint hlt before txt render

        c_wgl_set_focus(t_g_wfd_view_main.h_main_find,FALSE);
        c_wgl_set_visibility(t_g_wfd_view_main.h_main_frm, WGL_SW_NORMAL);
    }
    else
    {
        if(!wfd_view_main_is_current_view())
        {
            return WFDR_OK;
        }

        wfd_view_set_current_view(WFD_VIEW_END);
        c_wgl_set_visibility(t_g_wfd_view_main.h_main_frm, WGL_SW_HIDE);
    }
    c_wgl_repaint(t_g_wfd_view_main.h_main_frm,NULL,FALSE);

    return WFDR_OK;
}

INT32 wfd_view_main_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2)
{
    HANDLE_T           h_wgt_src;
    WGL_NOTIFY_DATA_T* pt_nfy_data;
    UINT32 ui4_keycode;

    switch(ui4_msg)
    {
        case WGL_MSG_NOTIFY:
    {
        h_wgt_src = (HANDLE_T) pv_param1;
        pt_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;
        WFD_DBG_LOG(pt_nfy_data->ui4_nc_code);

        if (WGL_NC_BTN_PUSHED == pt_nfy_data->ui4_nc_code)
        {
            if(h_wgt_src == t_g_wfd_view_main.h_main_find)
            {
                if(wfd_app_get_p2p_sta() != WFD_P2P_ENABLED)
                    return WFDR_OK;
                    WFD_CMD_CONT_T t_cmd;
                    t_cmd.e_cmd = WFD_CMD_FIND;
                    t_cmd.pv_param = NULL;
                    wfd_view_send_cmd(t_cmd);
                    break;
            }
        }
        else if((WGL_NC_GL_KEY_DOWN == pt_nfy_data->ui4_nc_code)
                    ||(WGL_NC_GL_KEY_REPEAT== pt_nfy_data->ui4_nc_code))
        {
           ui4_keycode = pt_nfy_data->u.t_key.ui4_key_code;

           if((ui4_keycode == BTN_EXIT)
               ||(ui4_keycode == BTN_RETURN))
           {
               wfd_view_main_toggle_show(FALSE,FALSE);
               wfd_main_send_msg_to_view(WFD_MSG_MAIN_EXIT,NULL);
               return WFDR_OK;
           }

           if(h_wgt_src == t_g_wfd_view_main.h_main_find)
           {
               WFD_DBG_LOG(ui4_keycode);

               if(ui4_keycode == BTN_CURSOR_UP)
               {
                   WFD_DBG_LOG_EX("device num",ui4_g_last_device_num);
                   WFD_DBG_LOG_EX("highlt_pos",ui2_hl_pos);

                   if(ui4_g_last_device_num == 0)
                   {
                       return WFDR_OK;
                   }
                   else
                   {
                       c_wgl_set_focus(t_g_wfd_view_main.h_main_device_list, FALSE);
                       c_wgl_do_cmd(
                                   t_g_wfd_view_main.h_main_device_list,
                                   WGL_CMD_LB_HLT_ELEM,
                                   WGL_PACK(0),
                                   NULL);
                       c_wgl_repaint(t_g_wfd_view_main.h_main_frm,NULL,FALSE);
                   }
               }
           }
        }
    }
        break;
        default:
            break;

    }

    WFD_RET_ON_ERR_EX(c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2),WGLR_OK);
    return WFDR_OK;
}

static BOOL  wfd_view_main_is_current_view(VOID)
{
    if(wfd_view_get_current_view() == WFD_VIEW_MAIN)
        return TRUE;
    return FALSE;
}

INT32 wfd_view_main_do_msg(WFD_MSG_T e_msg,VOID* pv_param)
{
    WFD_DBG_LOG(e_msg);
    switch (e_msg)
    {
        case WFD_MSG_FIND:
        {
            wfd_view_main_update_list(FALSE);
            break;
        }
        case WFD_MSG_STOP_FIND:
        {
            if(!wfd_view_main_is_current_view())
                return WFDR_OK;
            break;
        }
        case WFD_MSG_P2P_START_ENABLE:
        case WFD_MSG_P2P_START_DISABLE:
        case WFD_MSG_P2P_ENABLED:
        {
            break;
        }
        case WFD_MSG_P2P_DISABLED:
        {
            wfd_view_main_update_list(TRUE);
            #if 0 /* DTV00535431 */
            if(wfd_view_main_update_sta() != WFDR_OK)
            {
                c_wgl_set_visibility(t_g_wfd_view_main.h_main_show_sta, WGL_SW_HIDE);
            }
            #endif
            break;
        }
        case WFD_MSG_P2P_DEVICE_FOUND:
        {
            wfd_view_main_update_list(FALSE);
            break;
        }
        case WFD_MSG_P2P_DEVICE_LOST:
        {
            wfd_view_main_update_list(FALSE);
            break;
        }
        case WFD_MSG_P2P_ENABLE_FAILED:
        {
            break;
        }
        case WFD_MSG_P2P_ENABLE_OK:
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
            WFD_CMD_CONT_T t_cmd;
            t_cmd.e_cmd = WFD_CMD_FIND;
            t_cmd.pv_param = NULL;
            wfd_view_send_cmd(t_cmd);
            break;
        }
        case WFD_MSG_P2P_GROUP_DISAPPEAR:
        {
           if(!wfd_view_main_is_current_view())
                return WFDR_OK;
           wfd_view_main_update_sta();
            break;
        }
        default:
            break;
    }
    c_wgl_repaint(t_g_wfd_view_main.h_main_frm,NULL,FALSE);
    return WFDR_OK;
}

INT32 wfd_view_main_list_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32     i4_ret;
    if(ui4_msg ==  WGL_MSG_KEY_DOWN || ui4_msg ==  WGL_MSG_KEY_REPEAT)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

         c_wgl_do_cmd(
             t_g_wfd_view_main.h_main_device_list,
             WGL_CMD_LB_GET_HLT_INDEX,
             WGL_PACK(&ui2_hl_pos),
             NULL);

         WFD_DBG_LOG(ui2_hl_pos);
         switch (ui4_keycode)
         {
             case BTN_CURSOR_UP:
             {
                 if(ui2_hl_pos == 0 )
                 {
                     c_wgl_do_cmd(
                                 t_g_wfd_view_main.h_main_device_list,
                                 WGL_CMD_LB_UNHLT_ELEM,
                                 WGL_PACK(ui2_hl_pos),
                                 WGL_PACK(TRUE));
                     c_wgl_set_focus(t_g_wfd_view_main.h_main_find, TRUE);

                     c_wgl_repaint(t_g_wfd_view_main.h_main_frm,NULL,FALSE);
                     return WFDR_OK;
                 }
                 break;
             }
             case BTN_CURSOR_DOWN:
             {
                 if(ui2_hl_pos == (ui4_g_last_device_num-1))
                 {
                     c_wgl_do_cmd(
                                 t_g_wfd_view_main.h_main_device_list,
                                 WGL_CMD_LB_UNHLT_ELEM,
                                 WGL_PACK(ui2_hl_pos),
                                 WGL_PACK(TRUE));
                     c_wgl_set_focus(t_g_wfd_view_main.h_main_find, TRUE);
                     c_wgl_repaint(t_g_wfd_view_main.h_main_frm,NULL,FALSE);
                     return WFDR_OK;
                 }
                 break;
             }
             case BTN_SELECT:
             case BTN_ENTER:
             {
                 DBG_LOG_PRINT(("\n%s,%s,%d,conn_status=%d,ui2_hl_pos=%d,conn_idx=%d\n",
                             __FILE__, __FUNCTION__, __LINE__,
                             wfd_app_get_p2p_conn_sta(),
                             ui2_hl_pos,
                             wfd_app_get_conn_idx()));
                 if(wfd_app_get_p2p_conn_sta() == WFD_P2P_CONN_CONNECTED)
                 {
                     if( ui2_hl_pos == wfd_app_get_conn_idx())
                     {
                         wfd_view_main_toggle_show(FALSE,FALSE);
                         wfd_main_send_msg_to_view(WFD_MSG_VIEW_CONNECTED_TO_STA, NULL);
                         return WFDR_OK;
                     }
                     else
                     {
                         wfd_view_main_toggle_show(FALSE,FALSE);
                         wfd_main_send_msg_to_view(WFD_MSG_VIEW_CONFIRM_DIS_P2P , NULL);

                         return WFDR_OK;
                     }
                 }
                 else
                 {
                     wfd_view_main_toggle_show(FALSE,FALSE);

                     /* set PBC type */
                     {
                         wfd_view_main_set_refind(TRUE);

                         WFD_CMD_CONT_T t_cmd;
                         t_cmd.e_cmd = WFD_CMD_PBC;
                         t_cmd.pv_param = NULL;
                         wfd_view_send_cmd(t_cmd);
                     }

                     return WFDR_OK;
                 }
                 break;
             }
             default:
             break;
         }
    }
    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    return i4_ret;
}


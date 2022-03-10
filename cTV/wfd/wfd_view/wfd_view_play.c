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
#include "wfd_view_play.h"
#include "../wfd_dev_list.h"

static WFD_VIEW_PLAY_T e_g_view_play_status = WFD_VIEW_PLAY_STOP;

INT32 wfd_view_play_update_info(VOID);
static VOID wfd_view_play_upd_mute_timer_nfy_func(HANDLE_T h_timer, VOID* pv_tag);

static BOOL  wfd_view_play_is_current_view(VOID)
{
    if(wfd_view_get_current_view() == WFD_VIEW_PLAY)
        return TRUE;

    return FALSE;
}

static VOID _wfd_play_notify_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3, VOID* pv_tag4)
{
    WFD_DBG_LOG(0);
    if(!wfd_view_play_is_current_view())
        return;
    WFD_DBG_LOG(0);
    WFD_VIEW_CMD_T e_cmd = (WFD_VIEW_CMD_T)(UINT32)pv_tag1;
    if(e_cmd == WFD_VIEW_CMD_PLAY_HIDE_VOL_TXT)
    {
        c_wgl_show(t_g_wfd_view_main.h_play_vol_txt, WGL_SW_HIDE);
    }
    else if(e_cmd == WFD_VIEW_CMD_PLAY_HIDE)
    {
        WFD_DBG_ERR(wfd_view_play_toggle_show(FALSE));
    }
    return;
}

static VOID _wfd_play_timer_nfy_fct (HANDLE_T h_timer, VOID* pv_tag)
{

    WFD_DBG_LOG(0);
    if (h_timer == t_g_wfd_view_main.h_timer_cec_sac)
    {
        wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_play_notify_hdlr, (VOID*)(UINT32)WFD_VIEW_CMD_PLAY_HIDE_VOL_TXT,
                        NULL,NULL,NULL);
    }
    else if (h_timer == t_g_wfd_view_main.h_timer_play_hide)
    {
        wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_play_notify_hdlr, (VOID*)(UINT32)WFD_VIEW_CMD_PLAY_HIDE,
                        NULL,NULL,NULL);
    }

    return;
}


INT32 wfd_view_play_do_msg(WFD_MSG_T e_msg,VOID* pv_param)
{
    c_wgl_set_visibility(t_g_wfd_view_main.h_play_vol_txt, WGL_SW_HIDE);
    c_timer_stop(t_g_wfd_view_main.h_timer_cec_sac);

    #if 0 /* DTV00535421 */
    WGL_HIMG_TPL_T      h_img;
    WGL_IMG_INFO_T      t_img_info;
    #endif

    switch(e_msg)
    {
        case WFD_MSG_VOL_CHG:
        {
            if(!wfd_view_play_is_current_view())
                return WFDR_OK;

            WFD_DBG_LOG(0);
            WFD_VOL_UPD_INFO_T* pt_vol_info = (WFD_VOL_UPD_INFO_T*) pv_param;
            UINT16 ui2_mlm_id;
            if (NULL != pt_vol_info && pt_vol_info->b_cec_sac)
            {
              //if (NULL != pt_vol_info && (pt_vol_info->b_volume_up || pt_vol_info->b_volume_down))
                if (pt_vol_info->b_volume_up || pt_vol_info->b_volume_down)
                {
                    ui2_mlm_id = pt_vol_info->b_volume_up ? (UINT16) MLM_WFD_KEY_VOLUME_UP:
                                        (UINT16)MLM_WFD_KEY_VOLUME_DOWN;

                    c_wgl_do_cmd(t_g_wfd_view_main.h_play_vol_txt,
                             WGL_CMD_TEXT_SET_TEXT,
                             WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)),
                             WGL_PACK((UINT16)c_uc_w2s_strlen(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id))));

                    c_wgl_set_visibility(t_g_wfd_view_main.h_play_vol_txt, WGL_SW_NORMAL);

                    c_timer_start (t_g_wfd_view_main.h_timer_cec_sac,
                                   WFD_PLAY_TIMER_CEC_SAC_VOL,
                                   X_TIMER_FLAG_ONCE,
                                   _wfd_play_timer_nfy_fct,
                                   NULL);
                }
            }

            wfd_view_play_toggle_show(TRUE);
            c_timer_start(t_g_wfd_view_main.h_timer_update_mute,
                       50,
                       X_TIMER_FLAG_ONCE,
                       wfd_view_play_upd_mute_timer_nfy_func,
                       NULL);
            break;
        }
        case WFD_MSG_VIEW_TO_PLAY:
        {
            e_g_view_play_status = WFD_VIEW_PLAY_PLAY;
            wfd_view_play_toggle_show(TRUE);
            break;
        }

        case WFD_MSG_VIEW_MSG_PAUSED:
        {
            #if 0 /* DTV00535421 */
            h_img = h_g_wfd_play_img;

            t_img_info.e_type = WGL_IMG_SET_BASIC;
            t_img_info.u_img_data.t_standard.t_enable =    h_img;
            t_img_info.u_img_data.t_standard.t_disable =   h_img;
            c_wgl_do_cmd(t_g_wfd_view_main.h_play_pause,
                         WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK),
                         WGL_PACK(&t_img_info));
            #endif
            e_g_view_play_status = WFD_VIEW_PLAY_PAUSE;
            wfd_view_play_toggle_show(TRUE);
            break;
        }
        case WFD_MSG_VIEW_MSG_PAUSE_FAIL:
        {
            //
            break;
        }

        case WFD_MSG_VIEW_MSG_PLAYD:
        {
            #if 0 /* DTV00535421 */
            h_img = h_g_wfd_pause_img;

            t_img_info.e_type = WGL_IMG_SET_BASIC;
            t_img_info.u_img_data.t_standard.t_enable =    h_img;
            t_img_info.u_img_data.t_standard.t_disable =   h_img;
            c_wgl_do_cmd(t_g_wfd_view_main.h_play_pause,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_BK),
                         WGL_PACK(&t_img_info));
            #endif
            e_g_view_play_status = WFD_VIEW_PLAY_PLAY;
            wfd_view_play_toggle_show(TRUE);
            break;
        }
        case WFD_MSG_VIEW_MSG_PLAY_FAIL:
        {
            //
            break;
        }
        case WFD_MSG_P2P_GROUP_DISAPPEAR:
        {
            e_g_view_play_status = WFD_VIEW_PLAY_STOP;
            if(!wfd_view_play_is_current_view())
                 return WFDR_OK;
            wfd_view_play_toggle_show(FALSE);
            wfd_view_set_current_view(WFD_VIEW_END);
            wfd_main_send_msg_to_view(WFD_MSG_P2P_GROUP_DISAPPEAR,(VOID*)(UINT32)WFD_VIEW_MSG);
        }

        case WFD_MSG_RTSP_TEARDOWN:
        {
            e_g_view_play_status = WFD_VIEW_PLAY_STOP;
            if(!wfd_view_play_is_current_view())
                 return WFDR_OK;
            wfd_view_play_toggle_show(FALSE);
            wfd_view_set_current_view(WFD_VIEW_END);
            wfd_main_send_msg_to_view(WFD_MSG_RTSP_TEARDOWN,(VOID*)(UINT32)WFD_VIEW_MSG);
        }
        default:
            break;

    }
    return WFDR_OK;
}

INT32 wfd_view_play_update_info(VOID)
{
    WGL_HIMG_TPL_T      h_img;
    WGL_IMG_INFO_T      t_img_info;
    BOOL                b_cec_sac = FALSE;
    UINT8               ui1_icl_val;
    UINT16              i2_vol, ui2_mlm_id;
    SIZE_T              z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    INT32               i4_ret;
    BOOL                b_mute = a_tv_get_mute();//wait for enhance
    /*Check CEC SAC status*/

    WFD_DBG_LOG(b_mute);
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if (ICLR_OK == i4_ret && ui1_icl_val == ICL_CEC_SAC_STATUS_ON)
    {
        b_cec_sac = TRUE;
    }

    if(b_cec_sac)
    {
        c_wgl_set_visibility(t_g_wfd_view_main.h_play_vol_bar,WGL_SW_HIDE);
    }
    else
    {
        a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                     (INT16*)&i2_vol);
        c_wgl_do_cmd(t_g_wfd_view_main.h_play_vol_bar,
                     WGL_CMD_PG_SET_POS,
                     WGL_PACK((INT32)i2_vol),
                     NULL);
        c_wgl_set_visibility(t_g_wfd_view_main.h_play_vol_bar,
                             b_mute ? WGL_SW_HIDE : WGL_SW_NORMAL);
    }
    c_wgl_set_visibility(t_g_wfd_view_main.h_play_vol_txt, WGL_SW_HIDE);

    h_img = b_mute? h_g_wfd_icon_mute_img : h_g_wfd_icon_vol_img;

    t_img_info.e_type = WGL_IMG_SET_BASIC;
    t_img_info.u_img_data.t_standard.t_enable =    h_img;
    t_img_info.u_img_data.t_standard.t_disable =   h_img;
    c_wgl_do_cmd(t_g_wfd_view_main.h_play_vol_icon,
                 WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK),
                 WGL_PACK(&t_img_info));


    UTF16_T     pw2s_text[32];
    WFD_DEVICE_INFO_T t_info;
    CHAR      ps_port[10] = {0};

    c_memset(&t_info, 0, sizeof(WFD_DEVICE_INFO_T));
    c_memset(pw2s_text, 0, sizeof(pw2s_text));
    if(wfd_app_get_p2p_conn_sta() != WFD_P2P_CONN_CONNECTED)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    WFD_RET_ON_ERR(wfd_app_get_conn_device_info(&t_info));

    /* keep the current connect device information */
    a_wfd_device_info_store_new_device(&t_info);

    c_uc_ps_to_w2s(t_info.ps_device_name, pw2s_text, 32);
    c_wgl_do_cmd(t_g_wfd_view_main.h_play_status,
              WGL_CMD_LB_SET_ITEM_TEXT,
              WGL_PACK_2(0, 1),
              WGL_PACK(pw2s_text));

    c_memset(pw2s_text, 0, sizeof(pw2s_text));

    c_uc_ps_to_w2s(t_info.ps_device_ip, pw2s_text, 32);
    c_wgl_do_cmd(t_g_wfd_view_main.h_play_status,
              WGL_CMD_LB_SET_ITEM_TEXT,
              WGL_PACK_2(0, 3),
              WGL_PACK(pw2s_text));

    c_sprintf(ps_port,"%d",t_info.i4_device_port);
    c_uc_ps_to_w2s(ps_port, pw2s_text, 32);
    c_wgl_do_cmd(t_g_wfd_view_main.h_play_status,
              WGL_CMD_LB_SET_ITEM_TEXT,
              WGL_PACK_2(0, 5),
              WGL_PACK(pw2s_text));

    ui2_mlm_id = (UINT16) MLM_WFD_KEY_CONNECT_STR;
    c_wgl_do_cmd(t_g_wfd_view_main.h_play_status,
              WGL_CMD_LB_SET_ITEM_TEXT,
        WGL_PACK_2(0, 0),
        WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));


    ui2_mlm_id = (UINT16) MLM_WFD_KEY_IP_STR;
    c_wgl_do_cmd(t_g_wfd_view_main.h_play_status,
              WGL_CMD_LB_SET_ITEM_TEXT,
        WGL_PACK_2(0, 2),
        WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));

    ui2_mlm_id = (UINT16) MLM_WFD_KEY_PORT_STR;
    c_wgl_do_cmd(t_g_wfd_view_main.h_play_status,
              WGL_CMD_LB_SET_ITEM_TEXT,
        WGL_PACK_2(0, 4),
            WGL_PACK(MLM_WFD_TEXT(t_g_wfd_view_main.ui2_lang_id, ui2_mlm_id)));
    return WFDR_OK;
}


INT32 wfd_view_play_toggle_show(BOOL b_show)
{
    WFD_DBG_LOG(b_show);
    if(b_show)
    {
        WFD_RET_ON_ERR(wfd_view_play_update_info());
        c_wgl_set_focus(t_g_wfd_view_main.h_play_frm, FALSE);
        c_timer_stop(t_g_wfd_view_main.h_timer_play_hide);
        c_timer_start (t_g_wfd_view_main.h_timer_play_hide,
                      WFD_PLAY_TIMER_VIERER_HIDE,
                      X_TIMER_FLAG_ONCE,
                      _wfd_play_timer_nfy_fct,
                      NULL);
        wfd_view_set_current_view(WFD_VIEW_PLAY);
        c_wgl_set_visibility(t_g_wfd_view_main.h_play_frm, WGL_SW_NORMAL);
        c_wgl_repaint(t_g_wfd_view_main.h_play_frm,NULL,FALSE);
        return WFDR_OK;
    }
    else
    {
        c_timer_stop(t_g_wfd_view_main.h_timer_cec_sac);
        c_timer_stop(t_g_wfd_view_main.h_timer_play_hide);
        c_wgl_set_visibility(t_g_wfd_view_main.h_play_frm, WGL_SW_HIDE);
        c_wgl_repaint(t_g_wfd_view_main.h_play_frm,NULL,FALSE);
    }
    return WFDR_OK;
}

INT32 wfd_view_play_proc_fct(HANDLE_T h_widget,UINT32 ui4_msg,VOID* pv_param1,VOID* pv_param2)
{
    UINT32 ui4_key_code;
    WFD_DBG_LOG(ui4_msg);

    if (ui4_msg == WGL_MSG_KEY_DOWN || ui4_msg == WGL_MSG_KEY_REPEAT)
    {
        wfd_view_play_toggle_show(TRUE);
        ui4_key_code = (UINT32)pv_param1;
        WFD_DBG_LOG(ui4_key_code);
       switch (ui4_key_code)
       {
           case BTN_FAVORITE://play/pause
           {
             if(e_g_view_play_status == WFD_VIEW_PLAY_PAUSE)
             {
                 WFD_CMD_CONT_T t_cmd;
                 t_cmd.e_cmd = WFD_CMD_PLAY;
                 t_cmd.pv_param = NULL;
                 wfd_view_send_cmd(t_cmd);
             }
             else if(e_g_view_play_status == WFD_VIEW_PLAY_PLAY)
             {
                 WFD_CMD_CONT_T t_cmd;
                 t_cmd.e_cmd = WFD_CMD_PAUSE_RTSP;
                 t_cmd.pv_param = NULL;
                 wfd_view_send_cmd(t_cmd);
             }
             break;
           }
           case BTN_FAV_CH://stop
           {
               wfd_view_play_toggle_show(FALSE);
               wfd_view_set_current_view(WFD_VIEW_END);
               wfd_main_send_msg_to_view(WFD_MSG_VIEW_CONFIRM_DIS_RTSP,NULL);
               return WFDR_OK;
           }
       }
    }

    WFD_RET_ON_ERR_EX(c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2),WGLR_OK);
    return WFDR_OK;
}

static VOID _wfd_view_play_upd_mute_nfy_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3, VOID* pv_tag4)
{
      wfd_view_play_toggle_show(TRUE);
     return;
}

//use to let finding move
static VOID wfd_view_play_upd_mute_timer_nfy_func(HANDLE_T h_timer, VOID* pv_tag)
{
    wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_view_play_upd_mute_nfy_hdlr, pv_tag, NULL,NULL,NULL);
    return;
}



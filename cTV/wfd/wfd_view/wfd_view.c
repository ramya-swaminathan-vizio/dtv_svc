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
 * $RCSfile: wfd_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: hs_mingmingzhang $
 * $MD5HEX: 8ebc2c7a2c0fc209f18ef9bd3ccc4afd $
 *
 * Description:
 *         This header file contains public interfaces, constant and type
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
#include "wfd_view.h"

WFD_OSD_CONTENT_T t_g_wfd_view_main;

WFD_VIEW_FRM_T wfd_view_get_current_view(VOID)
{
    return t_g_wfd_view_main.e_curr_view;
}

WFD_VIEW_FRM_T wfd_view_get_last_view(VOID)
{
    WFD_DBG_LOG( t_g_wfd_view_main.e_last_view);
    return t_g_wfd_view_main.e_last_view;
}

INT32 wfd_view_toggle_show_view(WFD_VIEW_FRM_T e_view,BOOL b_show,BOOL b_update)
{
    WFD_DBG_LOG(e_view);
    UINT32 i4_ret = -1;
    switch(e_view)
    {
        case WFD_VIEW_MAIN:
                i4_ret = wfd_view_main_toggle_show(b_show,b_update);
            break;
        case WFD_VIEW_CONN:
                i4_ret = wfd_view_conn_toggle_show(b_show);
            break;
        case WFD_VIEW_MINI:
                i4_ret = wfd_view_mini_toggle_show(b_show);
            break;
        case WFD_VIEW_PIN:
                i4_ret = wfd_view_pin_toggle_show(b_show);
            break;
        case WFD_VIEW_STATUS:
                i4_ret = wfd_view_sta_toggle_show(b_show);
            break;
        case WFD_VIEW_PLAY:
                i4_ret = wfd_view_play_toggle_show(b_show);
            break;
        case WFD_VIEW_MSG:
                i4_ret = wfd_view_msg_toggle_show(b_show);
            break;
        default:
            break;
    }
     return WFDR_OK;
}

VOID wfd_view_set_current_view(WFD_VIEW_FRM_T e_view)
{
    WFD_DBG_LOG(e_view);
    if(t_g_wfd_view_main.e_curr_view != e_view)
    {
        if(t_g_wfd_view_main.e_curr_view != WFD_VIEW_END)
        {
            //WFD_DBG_LOG(t_g_wfd_view_main.e_curr_view);
            t_g_wfd_view_main.e_last_view = t_g_wfd_view_main.e_curr_view;
            //WFD_DBG_LOG(t_g_wfd_view_main.e_last_view);
        }
        t_g_wfd_view_main.e_curr_view = e_view;
    }
    return;
}

static UINT16 wfd_get_mlm_lang_id(VOID)
{
    INT32                       i4_ret;
    ISO_639_LANG_T              s639_lang;
    UINT16                      ui2_lang_id = 0; /*MLM_WFD_LANG_ENG*/

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("a_cfg_get_gui_lang() fail. i4_ret = %d.\r\n", i4_ret));
        ui2_lang_id =0;
    }
    else
    {
        ui2_lang_id = mlm_wfd_s639_to_langidx(s639_lang);
    }

    return ui2_lang_id;
}

static INT32 _wfd_init_canvas (VOID)
{
    INT32            i4_ret;
    GL_HSCREEN_T     h_screen = NULL_HANDLE;     /* screen handle */
    GL_HPLANE_T      h_plane = NULL_HANDLE;
    /*Open the screen */
    i4_ret = c_gl_screen_open (SN_PRES_MAIN_DISPLAY,
                               NULL,
                               NULL,
                               & h_screen);
    if (GL_FAILED(i4_ret))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }

    /*Open the plane */
    i4_ret = c_gl_plane_open (h_screen,
                              1,
                              &h_plane);
    if (GL_FAILED(i4_ret))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        c_handle_free(h_screen);
        return WFDR_FAIL;
    }

    /*Link the plane*/
    i4_ret = c_gl_plane_link (h_plane, h_screen, TRUE);
    if (GL_FAILED(i4_ret))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        c_handle_free(h_screen);
        c_handle_free(h_plane);
        return WFDR_FAIL;
    }

    /*Open the canvas */
    i4_ret = c_wgl_get_canvas(h_plane,
                               &t_g_wfd_view_main.h_canvas);
    if (GL_FAILED(i4_ret))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        c_handle_free(h_screen);
        c_handle_free(h_plane);
        return WFDR_FAIL;
    }


    i4_ret = c_wgl_get_canvas_size(t_g_wfd_view_main.h_canvas,
                                   &t_g_wfd_view_main.ui4_canvas_width,
                                   &t_g_wfd_view_main.ui4_canvas_height);
    if (GL_FAILED(i4_ret))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
    }


    if(h_screen)
    {
       WFD_RET_ON_ERR_EX(c_gl_obj_free(h_screen), GLR_OK);
    }

    if(h_plane)
    {
       WFD_RET_ON_ERR_EX(c_gl_obj_free(h_plane), GLR_OK);
    }
    return WFDR_OK;
}

INT32 wfd_view_hide_frm(WFD_VIEW_FRM_T e_view)
{
    switch (e_view)
    {
        case  WFD_VIEW_MAIN:
            WFD_RET_ON_ERR_EX(c_wgl_set_visibility(t_g_wfd_view_main.h_main_frm, WGL_SW_HIDE),WGLR_OK);
            break;

        case  WFD_VIEW_CONN:
            WFD_RET_ON_ERR_EX(c_wgl_set_visibility(t_g_wfd_view_main.h_conn_frm, WGL_SW_HIDE),WGLR_OK);
            break;

        case  WFD_VIEW_MINI:
            WFD_RET_ON_ERR_EX(c_wgl_set_visibility(t_g_wfd_view_main.h_mini_frm, WGL_SW_HIDE),WGLR_OK);
            break;

        case  WFD_VIEW_PIN:
            WFD_RET_ON_ERR_EX(c_wgl_set_visibility(t_g_wfd_view_main.h_pin_frm, WGL_SW_HIDE),WGLR_OK);
            break;

        case  WFD_VIEW_STATUS:
            WFD_RET_ON_ERR_EX(c_wgl_set_visibility(t_g_wfd_view_main.h_status_frm, WGL_SW_HIDE),WGLR_OK);
            break;

        case  WFD_VIEW_PLAY:
            WFD_RET_ON_ERR_EX(c_wgl_set_visibility(t_g_wfd_view_main.h_play_frm, WGL_SW_HIDE),WGLR_OK);
            break;

        case  WFD_VIEW_MSG:
            WFD_RET_ON_ERR_EX(c_wgl_set_visibility(t_g_wfd_view_main.h_msg_frm, WGL_SW_HIDE),WGLR_OK);
            break;

        default:
            break;
    }

    return WFDR_OK;
}

static INT32 wfd_view_set_widget(VOID)
{
    WGL_KEY_LINK_T          at_link[4];
    //main
    t_g_wfd_view_main.h_main_frm = wfd_wfd_main_get_wgt_hdl(WID_WFD_WFD_MAIN_FRM_MAIN_FRM);
    #if 0 /* DTV00535431 */
    t_g_wfd_view_main.h_main_show_sta = wfd_wfd_main_get_wgt_hdl(WID_WFD_WFD_MAIN_LB_STA_SHOW);
    #endif
    t_g_wfd_view_main.h_main_device_list = wfd_wfd_main_get_wgt_hdl(WID_WFD_WFD_MAIN_LB_DEVICE_LIST);
    t_g_wfd_view_main.h_main_find = wfd_wfd_main_get_wgt_hdl(WID_WFD_WFD_MAIN_BTN_FIND_DEV);

    //connect main
    t_g_wfd_view_main.h_conn_frm = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_FRM_CONNECT_MAIN);
    t_g_wfd_view_main.h_conn_pbc = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_BTN_PBC);
    t_g_wfd_view_main.h_conn_show_pin = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_BTN_SHOW_PIN);
    t_g_wfd_view_main.h_conn_enter_pin = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_BTN_ENTER_PIN);

    //conn main pbc
    at_link[0].ui4_key  = BTN_CURSOR_DOWN;
    at_link[0].h_widget = t_g_wfd_view_main.h_conn_show_pin;
    WFD_RET_ON_ERR_EX( c_wgl_set_navigation( t_g_wfd_view_main.h_conn_pbc,1,at_link), WGLR_OK);
    //conn main  show pin
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[0].h_widget = t_g_wfd_view_main.h_conn_pbc;
    at_link[1].ui4_key  = BTN_CURSOR_DOWN;
    at_link[1].h_widget = t_g_wfd_view_main.h_conn_enter_pin;
    WFD_RET_ON_ERR_EX( c_wgl_set_navigation( t_g_wfd_view_main.h_conn_show_pin,2,at_link), WGLR_OK);
    //conn main enter pin
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[0].h_widget = t_g_wfd_view_main.h_conn_show_pin;
    WFD_RET_ON_ERR_EX( c_wgl_set_navigation( t_g_wfd_view_main.h_conn_enter_pin,1,at_link), WGLR_OK);

    //mini conn
    t_g_wfd_view_main.h_mini_frm = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_FRM_REQ_BAR);
    t_g_wfd_view_main.h_mini_cont = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_TXT_REQ_NAME);

    t_g_wfd_view_main.h_mini_yes = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_BTN_REQ_YES);
    t_g_wfd_view_main.h_mini_exit = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_BTN_REQ_EXIT);

    //mini conn yes
    at_link[0].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[0].h_widget = t_g_wfd_view_main.h_mini_exit;
    WFD_RET_ON_ERR_EX(c_wgl_set_navigation( t_g_wfd_view_main.h_mini_yes,1,at_link), WGLR_OK);
    // mini conn exit
    at_link[0].ui4_key  = BTN_CURSOR_LEFT;
    at_link[0].h_widget = t_g_wfd_view_main.h_mini_yes;
    WFD_RET_ON_ERR_EX(c_wgl_set_navigation( t_g_wfd_view_main.h_mini_exit,1,at_link), WGLR_OK);

    //pin
    t_g_wfd_view_main.h_pin_frm = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_FRM_PIN_WIN);
    t_g_wfd_view_main.h_pin_btn = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_BTN_PIN_BTN);
    t_g_wfd_view_main.h_pin_box = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_EDIT_PIN_BOX);
    t_g_wfd_view_main.h_pin_btn_1 = wfd_wfd_connect_get_wgt_hdl(WID_WFD_WFD_CONNECT_BTN_PIN_BTN_1);

    //pin_box
    at_link[0].ui4_key  = BTN_CURSOR_DOWN;
    at_link[0].h_widget = t_g_wfd_view_main.h_pin_btn;
    WFD_RET_ON_ERR_EX(c_wgl_set_navigation( t_g_wfd_view_main.h_pin_box,1,at_link), WGLR_OK);
    //pin_btn
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[0].h_widget = t_g_wfd_view_main.h_pin_box;
    at_link[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[1].h_widget = t_g_wfd_view_main.h_pin_btn_1;
    WFD_RET_ON_ERR_EX(c_wgl_set_navigation( t_g_wfd_view_main.h_pin_btn,2,at_link), WGLR_OK);
    //pin_btn_1
    at_link[0].ui4_key  = BTN_CURSOR_UP;
    at_link[0].h_widget = t_g_wfd_view_main.h_pin_box;
    at_link[1].ui4_key  = BTN_CURSOR_LEFT;
    at_link[1].h_widget = t_g_wfd_view_main.h_pin_btn;
    WFD_RET_ON_ERR_EX(c_wgl_set_navigation( t_g_wfd_view_main.h_pin_btn_1,2,at_link), WGLR_OK);

    //status
    t_g_wfd_view_main.h_status_frm = wfd_wfd_status_get_wgt_hdl(WID_WFD_WFD_STATUS_FRM_STA_MAIN);
    t_g_wfd_view_main.h_status_show = wfd_wfd_status_get_wgt_hdl(WID_WFD_WFD_STATUS_LB_STA_SHOW);
    t_g_wfd_view_main.h_status_load = wfd_wfd_status_get_wgt_hdl(WID_WFD_WFD_STATUS_ICON_STA_LOAD);

    t_g_wfd_view_main.h_status_btn1 = wfd_wfd_status_get_wgt_hdl(WID_WFD_WFD_STATUS_BTN_STA_ENABLE);
    t_g_wfd_view_main.h_status_btn2 = wfd_wfd_status_get_wgt_hdl(WID_WFD_WFD_STATUS_BTN_STA_ENABLE_2);
    t_g_wfd_view_main.h_status_back = wfd_wfd_status_get_wgt_hdl(WID_WFD_WFD_STATUS_BTN_BACK_TO_MAIN);
    //sta 1
    at_link[0].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[0].h_widget = t_g_wfd_view_main.h_status_btn2;
    WFD_RET_ON_ERR_EX( c_wgl_set_navigation( t_g_wfd_view_main.h_status_btn1,1,at_link), WGLR_OK);
    //sta 2
    at_link[0].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[0].h_widget = t_g_wfd_view_main.h_status_back;
    at_link[1].ui4_key  = BTN_CURSOR_LEFT;
    at_link[1].h_widget = t_g_wfd_view_main.h_status_btn1;
    WFD_RET_ON_ERR_EX( c_wgl_set_navigation( t_g_wfd_view_main.h_status_btn2,2,at_link), WGLR_OK);
    //sta back
    at_link[0].ui4_key  = BTN_CURSOR_LEFT;
    at_link[0].h_widget = t_g_wfd_view_main.h_status_btn2;
    WFD_RET_ON_ERR_EX( c_wgl_set_navigation( t_g_wfd_view_main.h_status_back,1,at_link), WGLR_OK);

    //play
    t_g_wfd_view_main.h_play_frm = wfd_wfd_play_get_wgt_hdl(WID_WFD_WFD_PLAY_FRM_PLAY_MAIN);
    t_g_wfd_view_main.h_play_vol_icon = wfd_wfd_play_get_wgt_hdl(WID_WFD_WFD_PLAY_ICON_VOL_ICON);
    t_g_wfd_view_main.h_play_vol_bar = wfd_wfd_play_get_wgt_hdl(WID_WFD_WFD_PLAY_PB_VOL_BAR);
    t_g_wfd_view_main.h_play_status = wfd_wfd_play_get_wgt_hdl(WID_WFD_WFD_PLAY_LB_PL_STA_SHOW);
    t_g_wfd_view_main.h_play_vol_txt = wfd_wfd_play_get_wgt_hdl(WID_WFD_WFD_PLAY_TXT_VOL_TXT);
    t_g_wfd_view_main.h_play_pause = NULL_HANDLE; //wfd_wfd_play_get_wgt_hdl(WID_WFD_WFD_PLAY_ICON_PLAY_ICON); /* DTV00535421 */
    t_g_wfd_view_main.h_play_stop = NULL_HANDLE; //wfd_wfd_play_get_wgt_hdl(WID_WFD_WFD_PLAY_ICON_STOP_ICON);  /* DTV00535421 */

    //msg
    t_g_wfd_view_main.h_msg_frm = wfd_wfd_msg_get_wgt_hdl(WID_WFD_WFD_MSG_FRM_MSG_BOX);
    t_g_wfd_view_main.h_msg_cont1 = wfd_wfd_msg_get_wgt_hdl(WID_WFD_WFD_MSG_TXT_MSG_1);
    t_g_wfd_view_main.h_msg_cont2 = wfd_wfd_msg_get_wgt_hdl(WID_WFD_WFD_MSG_TXT_MSG_2);

    t_g_wfd_view_main.h_msg_yes = wfd_wfd_msg_get_wgt_hdl(WID_WFD_WFD_MSG_BTN_MSG_YES);
    t_g_wfd_view_main.h_msg_cancel = wfd_wfd_msg_get_wgt_hdl(WID_WFD_WFD_MSG_BTN_MSG_CANCEL);

    //mini conn yes
    at_link[0].ui4_key  = BTN_CURSOR_RIGHT;
    at_link[0].h_widget = t_g_wfd_view_main.h_msg_cancel;
    WFD_RET_ON_ERR_EX(c_wgl_set_navigation( t_g_wfd_view_main.h_msg_yes,1,at_link), WGLR_OK);
    // mini conn exit
    at_link[0].ui4_key  = BTN_CURSOR_LEFT;
    at_link[0].h_widget = t_g_wfd_view_main.h_msg_yes;
    WFD_RET_ON_ERR_EX(c_wgl_set_navigation( t_g_wfd_view_main.h_msg_cancel,1,at_link), WGLR_OK);

    return WFDR_OK;
}

INT32 wfd_view_init(VOID)
{
    INT32 i4_ret;
    WGL_EB_KEY_MAP_T    t_eb_key_map;
    c_memset(&t_g_wfd_view_main,0,sizeof(WFD_OSD_CONTENT_T));
     t_g_wfd_view_main.e_curr_view = WFD_VIEW_END;
     t_g_wfd_view_main.e_last_view = WFD_VIEW_END;

    WFD_RET_ON_ERR(_wfd_init_canvas());

    WFD_RET_ON_ERR(wfd_gen_init_color());
    WFD_RET_ON_ERR(wfd_gen_init_font_info());
    WFD_RET_ON_ERR(wfd_gen_init_image());

    wfd_wfd_connect_reg_wgt_cb(WID_WFD_WFD_CONNECT_FRM_PIN_WIN, wfd_view_pin_proc_fct);
    wfd_wfd_connect_reg_wgt_cb(WID_WFD_WFD_CONNECT_FRM_REQ_BAR, wfd_view_mini_proc_fct);
    wfd_wfd_connect_reg_wgt_cb(WID_WFD_WFD_CONNECT_FRM_CONNECT_MAIN, wfd_view_conn_proc_fct);
    wfd_wfd_main_reg_wgt_cb(WID_WFD_WFD_MAIN_FRM_MAIN_FRM, wfd_view_main_proc_fct);
    wfd_wfd_main_reg_wgt_cb(WID_WFD_WFD_MAIN_LB_DEVICE_LIST, wfd_view_main_list_proc_fct);
    wfd_wfd_status_reg_wgt_cb(WID_WFD_WFD_STATUS_FRM_STA_MAIN, wfd_view_sta_proc_fct);
    wfd_wfd_play_reg_wgt_cb(WID_WFD_WFD_PLAY_FRM_PLAY_MAIN, wfd_view_play_proc_fct);
    wfd_wfd_msg_reg_wgt_cb(WID_WFD_WFD_MSG_FRM_MSG_BOX, wfd_view_msg_proc_fct);

    WFD_RET_ON_ERR(wfd_wfd_main_create_ui(t_g_wfd_view_main.h_canvas));
    WFD_RET_ON_ERR(wfd_wfd_connect_create_ui(t_g_wfd_view_main.h_canvas));
    WFD_RET_ON_ERR(wfd_wfd_status_create_ui(t_g_wfd_view_main.h_canvas));
    WFD_RET_ON_ERR(wfd_wfd_play_create_ui(t_g_wfd_view_main.h_canvas));
    WFD_RET_ON_ERR(wfd_wfd_msg_create_ui(t_g_wfd_view_main.h_canvas));

    t_g_wfd_view_main.ui2_lang_id = wfd_get_mlm_lang_id();
    WFD_RET_ON_ERR(wfd_wfd_connect_update_text(t_g_wfd_view_main.ui2_lang_id ));
    WFD_RET_ON_ERR(wfd_wfd_main_update_text(t_g_wfd_view_main.ui2_lang_id ));
    WFD_RET_ON_ERR(wfd_wfd_status_update_text(t_g_wfd_view_main.ui2_lang_id ));
    WFD_RET_ON_ERR(wfd_wfd_play_update_text(t_g_wfd_view_main.ui2_lang_id ));
    WFD_RET_ON_ERR(wfd_wfd_msg_update_text(t_g_wfd_view_main.ui2_lang_id ));

    WFD_RET_ON_ERR(wfd_view_set_widget());

    WFD_RET_ON_ERR(wfd_view_hide_frm(WFD_VIEW_MAIN));
    WFD_RET_ON_ERR(wfd_view_hide_frm(WFD_VIEW_CONN));
    WFD_RET_ON_ERR(wfd_view_hide_frm(WFD_VIEW_MINI));
    WFD_RET_ON_ERR(wfd_view_hide_frm(WFD_VIEW_PIN));
    WFD_RET_ON_ERR(wfd_view_hide_frm(WFD_VIEW_STATUS));
    WFD_RET_ON_ERR(wfd_view_hide_frm(WFD_VIEW_PLAY));
    WFD_RET_ON_ERR(wfd_view_hide_frm(WFD_VIEW_MSG));

    /*CEC SAC volume text hide timer*/
    i4_ret = c_timer_create(&t_g_wfd_view_main.h_timer_cec_sac);
    WFD_DBG_ERR_EX(i4_ret,OSR_OK);

    i4_ret = c_timer_create(&t_g_wfd_view_main.h_timer_play_hide);
    WFD_DBG_ERR_EX(i4_ret,OSR_OK);

    i4_ret = c_timer_create(&t_g_wfd_view_main.h_timer_sta_load);
    WFD_DBG_ERR_EX(i4_ret,OSR_OK);

    i4_ret = c_timer_create(&t_g_wfd_view_main.h_timer_time_out);
    WFD_DBG_ERR_EX(i4_ret,OSR_OK);

    i4_ret = c_timer_create(&t_g_wfd_view_main.h_timer_update_mute);
    WFD_DBG_ERR_EX(i4_ret,OSR_OK);

    WFD_RET_ON_ERR_EX(c_wgl_repaint(t_g_wfd_view_main.h_canvas,NULL,FALSE),WGLR_OK);

    i4_ret = c_wgl_do_cmd(t_g_wfd_view_main.h_pin_box,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),  /*Attr mask*/
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING)); /*Attr value*/
    WFD_DBG_LOG(i4_ret);
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));

    t_eb_key_map.ui4_backsapce = BTN_CURSOR_LEFT;
    i4_ret = c_wgl_do_cmd(t_g_wfd_view_main.h_pin_box,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    WFD_DBG_LOG(i4_ret);

    return WFDR_OK;
}

INT32 wfd_view_deinit(VOID)
{
    WFD_RET_ON_ERR(wfd_gen_deinit_image());

    WFD_RET_ON_ERR(wfd_wfd_main_destroy_ui());
    WFD_RET_ON_ERR(wfd_wfd_connect_destroy_ui());
    WFD_RET_ON_ERR(wfd_wfd_status_destroy_ui());
    WFD_RET_ON_ERR(wfd_wfd_play_destroy_ui());
    WFD_RET_ON_ERR(wfd_wfd_msg_destroy_ui());

    WFD_RET_ON_ERR_EX(c_wgl_repaint(t_g_wfd_view_main.h_canvas,NULL,TRUE),WGLR_OK);
    if(t_g_wfd_view_main.h_timer_cec_sac)
        c_timer_delete(t_g_wfd_view_main.h_timer_cec_sac);

    if(t_g_wfd_view_main.h_timer_play_hide)
        c_timer_delete(t_g_wfd_view_main.h_timer_play_hide);

    if(t_g_wfd_view_main.h_timer_sta_load)
        c_timer_delete(t_g_wfd_view_main.h_timer_sta_load);

    if(t_g_wfd_view_main.h_timer_sta_load)
        c_timer_delete(t_g_wfd_view_main.h_timer_time_out);

    if(t_g_wfd_view_main.h_timer_sta_load)
        c_timer_delete(t_g_wfd_view_main.h_timer_update_mute);


    c_memset(&t_g_wfd_view_main,0,sizeof(WFD_OSD_CONTENT_T));

    return WFDR_OK;
}

//call from wfd main to response msg
VOID _wfd_view_do_msg(VOID* param1, VOID* pv_msg_param,VOID* param2,VOID* param3)
{
    WFD_MSG_T e_wfd_msg = (WFD_MSG_T)(UINT32) param1;
    WFD_DBG_LOG(e_wfd_msg);
    if((!wfd_app_is_active()) &&
       (((WFD_MSG_P2P_NEG_REQ != e_wfd_msg) && (WFD_MSG_P2P_PBC_REQ != e_wfd_msg)) &&
        (WFD_MSG_P2P_ENABLE_OK != e_wfd_msg)))
    {
        return;
    }
    switch (e_wfd_msg)
    {
        case WFD_MSG_VOL_CHG:
        {
            wfd_view_play_do_msg(e_wfd_msg,pv_msg_param);
            break;
        }

        case WFD_MSG_FIND:
        case WFD_MSG_STOP_FIND:
        case WFD_MSG_P2P_ENABLED:
        case WFD_MSG_P2P_DISABLED:
        case WFD_MSG_P2P_ENABLE_FAILED:
        case WFD_MSG_P2P_ENABLE_OK:
        case WFD_MSG_P2P_DEVICE_FOUND:
        case WFD_MSG_P2P_DEVICE_LOST:
        case WFD_MSG_P2P_START_ENABLE:
        case WFD_MSG_P2P_START_DISABLE:
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
            wfd_view_main_do_msg(e_wfd_msg,pv_msg_param);
            break;
        }
        case WFD_MSG_DEVICE_REMOVE:
        {
            wfd_view_toggle_show_view(wfd_view_get_current_view(),FALSE,FALSE);
        }
        case WFD_MSG_MAIN_EXIT:
        case WFD_MSG_DIRECT_ON:
      //case WFD_MSG_DEVICE_PLUG:
        case WFD_MSG_VIEW_CONFIRM_DIS_P2P:
        case WFD_MSG_VIEW_CONFIRM_DIS_RTSP:
        case WFD_MSG_VIEW_MSG_TRY_CONN_FAIL:
        case WFD_MSG_CONN_TIME_OUT:
        {
            wfd_view_msg_do_msg(e_wfd_msg,pv_msg_param);
            break;
        }
        case WFD_MSG_VIEW_TO_CONN:
        {
             wfd_view_conn_do_msg(e_wfd_msg,pv_msg_param);
             break;
        }
        case WFD_MSG_P2P_ENTER_PIN:
        case WFD_MSG_P2P_SHOW_PIN:
        case WFD_MSG_VIEW_SHOW_TO_PIN:
        case WFD_MSG_VIEW_ENTER_TO_PIN:
        case WFD_MSG_VIEW_ENTER_TO_PIN_REQ:
        case WFD_MSG_VIEW_SHOW_TO_PIN_REQ:
        {
            wfd_view_pin_do_msg(e_wfd_msg,pv_msg_param);
            break;
        }
        case WFD_MSG_VIEW_STOP_RTSP:
        case WFD_MSG_VIEW_STOP_RTSP_OK:
        case WFD_MSG_VIEW_STOP_RTSP_FAIL:
        case WFD_MSG_VIEW_TO_STA:
        case WFD_MSG_VIEW_CONNECTED_TO_STA:
        /*case WFD_MSG_P2P_GROUP_REMOVED:*/
        case WFD_MSG_AP_STA_DISCONNECTED:
        case WFD_MSG_VIEW_START_RTSP:
        case WFD_MSG_VIEW_START_RTSP_OK:
        case WFD_MSG_VIEW_START_RTSP_FAIL:
        case WFD_MSG_VIEW_DISCONNECT_P2P:
        case WFD_MSG_VIEW_DISCONNECT_P2P_OK:
        case WFD_MSG_VIEW_DISCONNECT_P2P_FAIL:
        {
            wfd_view_sta_do_msg(e_wfd_msg,pv_msg_param);
            break;
        }
        case WFD_MSG_AP_STA_CONNECTED:
        {
            if(wfd_view_get_current_view() != WFD_VIEW_STATUS)
            {
                wfd_view_toggle_show_view(wfd_view_get_current_view(),FALSE,FALSE);
                wfd_view_sta_do_msg(WFD_MSG_VIEW_TO_STA,pv_msg_param);
                wfd_view_sta_do_msg(WFD_MSG_AP_STA_CONNECTED,pv_msg_param);
            }
            else
            {
                wfd_view_sta_do_msg(e_wfd_msg,pv_msg_param);
            }
            break;
        }
        case WFD_MSG_VIEW_MSG_PLAYD:
        case WFD_MSG_VIEW_MSG_PLAY_FAIL:
        case WFD_MSG_VIEW_MSG_PAUSED:
        case WFD_MSG_VIEW_MSG_PAUSE_FAIL:
        case WFD_MSG_VIEW_TO_PLAY:
        case WFD_MSG_RTSP_TEARDOWN:
        {
            if((WFD_VIEW_FRM_T)(UINT32)pv_msg_param == WFD_VIEW_MSG)
            {
                wfd_view_msg_do_msg(WFD_MSG_RTSP_TEARDOWN,pv_msg_param);
                break;
            }
            wfd_view_play_do_msg(e_wfd_msg,pv_msg_param);
            break;
        }
        case WFD_MSG_P2P_PBC_REQ:
        case WFD_MSG_P2P_NEG_REQ:
        case WFD_MSG_P2P_ENTER_PIN_REQ:
        case WFD_MSG_P2P_SHOW_PIN_REQ:
        {
            wfd_view_mini_do_msg(e_wfd_msg,pv_msg_param);
            break;
        }
        case WFD_MSG_P2P_GROUP_DISAPPEAR:
        {
            if(pv_msg_param == NULL)
            {
                wfd_view_main_do_msg(e_wfd_msg,pv_msg_param);
                wfd_view_play_do_msg(WFD_MSG_P2P_GROUP_DISAPPEAR,pv_msg_param);
            }
            else if((WFD_VIEW_FRM_T)(UINT32)pv_msg_param  == WFD_VIEW_MSG)
            {
                wfd_view_msg_do_msg(WFD_MSG_P2P_GROUP_DISAPPEAR,pv_msg_param);
            }
           break;
        }
        default:
            break;
    }
    return;
}

INT32 wfd_view_send_cmd(WFD_CMD_CONT_T t_cmd)
{
    WFD_DBG_LOG(t_cmd.e_cmd);
    wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE, wfd_main_cmd_do, (VOID* )(UINT32)t_cmd.e_cmd,  t_cmd.pv_param, NULL,
    NULL);
    return WFDR_OK;
}
INT32 wfd_view_return_connect_idx(VOID)
{
   return  (INT32)wfd_view_main_get_hl_pos();
}


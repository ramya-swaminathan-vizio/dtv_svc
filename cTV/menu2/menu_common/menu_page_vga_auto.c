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
 * $RCSfile: menu_page_vga_auto.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_fe.h"

#include "u_sm_video_hdlr.h"
#include "c_svctx.h"

#include "app_util/a_ui.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_dbg.h"


#ifdef COMMON_VGA_AUTO_ENABLE

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define COMMON_VGA_AUTO_TIMEOUT         15000
#define COMMON_VGA_AUTO_ANIMATION_STEP  4

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_vga_auto;

static  BOOL        b_created = FALSE;
static  UINT32      ui4_start_time  = 0;
static  HANDLE_T    h_simple_dialog = NULL_HANDLE;
static  HANDLE_T    h_svctx         = NULL_HANDLE;
static  HANDLE_T    h_timer         = NULL_HANDLE;
static  HANDLE_T    h_g_font         = NULL_HANDLE;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static INT32 _vga_sync_hv_size(VOID)
{
    INT32 i4_ret = MENUR_OK;
    UINT16 ui2_h_size = 0;
    UINT16 ui2_v_size = 0;

    i4_ret = acfg_set(IDX_CUSTOM_VGA_H_SIZE, &ui2_h_size, sizeof(UINT16));
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = acfg_set(IDX_CUSTOM_VGA_V_SIZE, &ui2_v_size, sizeof(UINT16));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
    MENU_LOG_ON_FAIL(i4_ret);


    return i4_ret;
}
static INT32 _vga_auto_create(VOID)
{
    INT32                              i4_ret              = MENUR_FAIL;
    HANDLE_T                           h_frm_root;
    UI_SIMPLE_DIALOG_INIT_T            t_simple_dialog_init;

    i4_ret = menu_pm_get_root_frm(&h_frm_root);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    /* Initial the UI Simple Dialog */
    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY;
    t_simple_dialog_init.h_parent                       = h_frm_root;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = NULL;
    t_simple_dialog_init.pf_wdgt_proc                   = NULL;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &h_simple_dialog);
    MENU_CHK_FAIL(i4_ret);

    b_created = TRUE;

    return MENUR_OK;
}

static VOID _do_auto_done(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    BOOL*   pb_success = (BOOL*)pv_data;

    if(*pb_success)
    {
        _vga_sync_hv_size();
        a_cfg_vga_sync_clk_phs_pos();
        menu_nav_back();
    }
    else
    {
        a_amb_pause_app(MENU_NAME);
    }
}

static VOID _svctx_notify_fct(
    HANDLE_T            h_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if(e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS ||
       e_code == SVCTX_NTFY_CODE_INTERRUPTED)
    {
        BOOL    b_success = FALSE;

        menu_async_invoke(_do_auto_done, &b_success, sizeof(BOOL), TRUE);
    }

    if(e_code == SVCTX_NTFY_CODE_VIDEO_AUTO_CLK_POS_PHS_DONE)
    {
        BOOL    b_success = TRUE;

        AUTO_CLK_POS_PHS_COND_T     e_cond;
        SIZE_T                      z_size = sizeof(AUTO_CLK_POS_PHS_COND_T);
        if(c_svctx_get(h_svctx,
                       SVCTX_COMMON_GET_AUTO_CLK_POS_PHS_COND,
                       &e_cond,
                       &z_size) < 0)
        {
            b_success = FALSE;
        }
        else
        {
            if(e_cond == AUTO_CLK_POS_PHS_COND_SUCCESS)
            {
                b_success = TRUE;
            }
            else
            {
                b_success = FALSE;
            }
        }


        menu_async_invoke(_do_auto_done, &b_success, sizeof(BOOL), TRUE);
    }
}

static VOID _do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    UINT32  ui4_curr_time;
    ui4_curr_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

    if(ui4_curr_time - ui4_start_time > COMMON_VGA_AUTO_TIMEOUT)
    {
        BOOL    b_success = FALSE;

        DBG_INFO(("<MENU>AUTO: timeout!!\n"));
        menu_async_invoke(_do_auto_done, &b_success, sizeof(BOOL), TRUE);
    }
    else
    {
        UTF16_T w2s_msg[128],w2s_str[512];
        SIZE_T  z_len;
        UINT16  ui1_ani_step;
        UINT16  ui2_i;
        GL_RECT_T   t_rect;
        INT32 i4_w,i4_h,i4_i,i4_j,i4_len=512;

        if(COMMON_VGA_AUTO_ANIMATION_STEP > 0)
        {
            ui1_ani_step = (UINT8)((ui4_curr_time - ui4_start_time)/ 1000 % COMMON_VGA_AUTO_ANIMATION_STEP);
        }
        else
        {
            ui1_ani_step = 0;
        }

        c_memset(w2s_msg, 0, sizeof(w2s_msg));
        c_memset(w2s_str, 0, sizeof(w2s_str));

        c_uc_w2s_strncpy(w2s_msg,
                         MENU_TEXT(MLM_MENU_KEY_VGA_AUTO_MSG),
                         sizeof(w2s_msg) - COMMON_VGA_AUTO_ANIMATION_STEP);
                         /* preserve space to store the last 4 char "***\0" */
        z_len = c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_VGA_AUTO_MSG));

        for(ui2_i = 0 ;
            ui2_i < COMMON_VGA_AUTO_ANIMATION_STEP;
            ui2_i ++)
        {
            if(ui2_i < ui1_ani_step)
            {
                w2s_msg[z_len + ui2_i] = (UTF16_T)'.';
            }
            else
            {
                w2s_msg[z_len + ui2_i] = (UTF16_T)' ';
            }
        }
        w2s_msg[z_len + ui2_i] = 0;

        /*For CR 136367,msg move issue*/
        c_wgl_get_coords(h_simple_dialog,
                         WGL_COORDS_SCREEN,
                         &t_rect);

        c_fe_get_string_size(h_g_font,
                             w2s_msg,
                             (INT32)z_len,
                             &i4_w,
                             &i4_h);

        i4_j = ((t_rect.i4_right-t_rect.i4_left)-i4_w)/2;

        for(i4_i = 0 ;
            i4_i < i4_j-200&&i4_i<i4_len;
            i4_i ++)
        {
            w2s_str[i4_i] = (UTF16_T)' ';
        }

        c_uc_w2s_strncat(w2s_str, w2s_msg,
                         (UINT32)(i4_len - c_uc_w2s_strlen(w2s_str)));

        a_ui_simple_dialog_set_text(h_simple_dialog, w2s_str);
        a_ui_simple_dialog_set_text_align(h_simple_dialog, WGL_AS_CENTER_CENTER);
        a_ui_simple_dialog_repaint(h_simple_dialog);
    }
}

static VOID _timer_notify_fct(
    HANDLE_T  pt_tm_handle,
    VOID*     pv_tag)
{
    menu_async_invoke(_do_timer_nfy, NULL, 0, FALSE);
}


/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32 i4_ret;
    if(!b_g_menu_lazy_init_support)
    {
        i4_ret = _vga_auto_create();
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32   i4_ret;
    if(!b_created)
    {
        i4_ret = _vga_auto_create();
        MENU_CHK_FAIL(i4_ret);
    }

    /* Hide the main menu */
    menu_main_set_visibility(FALSE);

    /* Show the dialog */
    a_ui_simple_dialog_show(h_simple_dialog);

    /* Disable channel change */
    t_g_menu_enable_channel_change = FALSE;

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    /* Show the main menu */
    menu_main_set_visibility(TRUE);

    /* Hide the dialog */
    a_ui_simple_dialog_hide(h_simple_dialog);

    /* Enable channel change */
    t_g_menu_enable_channel_change = TRUE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32   i4_ret;
    CHAR    s_disp_name[SYS_NAME_LEN + 1];

    ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

    a_ui_simple_dialog_set_focus(h_simple_dialog, FALSE);

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));

    if(c_strcmp(s_disp_name, SN_PRES_SUB_DISPLAY) == 0)
    {
        i4_ret = c_svctx_open(SVCTX_NAME_SUB, &h_svctx);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_svctx);
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = c_svctx_set_listener(h_svctx,
                                  _svctx_notify_fct,
                                  NULL);
    MENU_CHK_FAIL(i4_ret);


    i4_ret = c_svctx_set_stream_attr(h_svctx,
                                     ST_VIDEO,
                                     SM_VSH_SET_TYPE_AUTO_CLK_PHS_POS,
                                     (VOID*)NULL,
                                     (SIZE_T)NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_timer);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_timer_start(h_timer, 1000, X_TIMER_FLAG_REPEAT, _timer_notify_fct, NULL);
    MENU_CHK_FAIL(i4_ret);

    _do_timer_nfy(NULL, 0);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    if(h_svctx != NULL_HANDLE)
    {
        c_svctx_close(h_svctx);
        h_svctx = NULL_HANDLE;
    }

    if(h_timer != NULL_HANDLE)
    {
        c_timer_delete(h_timer);
        h_timer = NULL_HANDLE;
    }

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

INT32 menu_common_page_vga_auto_init(VOID)
{
    INT32 i4_ret;

    t_g_menu_common_page_vga_auto.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_vga_auto.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_vga_auto.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_vga_auto.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_vga_auto.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_vga_auto.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_vga_auto.pf_menu_page_update=     _on_page_update;

    i4_ret=c_fe_create_font(SN_FONT_DEFAULT,
                    FE_FNT_SIZE_MEDIUM,
                    FE_FNT_STYLE_REGULAR,
                    FE_CMAP_ENC_UNICODE,
                    &h_g_font);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
#endif /* COMMON_VGA_AUTO_ENABLE */


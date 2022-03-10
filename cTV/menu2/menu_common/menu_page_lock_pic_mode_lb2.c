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
 * $RCSfile: menu_page_inp_lst.c,v $
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
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_isl.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/tts/a_tts_custom.h"
#include "app_util/a_screen_mode.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T     t_g_menu_page_lock_pic_lb2;
static HANDLE_T         h_lock_pic_lb2;
static BOOL             b_from_backbar;
UINT8                   ui1_g_edit_tpye      = ICL_PICTURE_EDIT_LOCK_PIC;

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    );

static BOOL _lock_pic_mode_check_is_set_sys_pin(VOID)
{
    UTF16_T    u2s_pwd_exist[5] = {0};
    CHAR       str_pwd[5] = {0};
    CHAR       str_pwd_default[5] = {0};
    UINT8      ui1_idx = 0;

    for(ui1_idx=0; ui1_idx < 5; ui1_idx++)
    {
        str_pwd_default[ui1_idx] = '0';
    }

    a_cfg_get_password(u2s_pwd_exist, 5);
    c_uc_w2s_to_ps(u2s_pwd_exist,
                   str_pwd,
                   5);
    DBG_INFO(("\n%s,%d,system pin:%s\n",__FUNCTION__,__LINE__,str_pwd));

    if (c_strncmp(str_pwd, str_pwd_default, 4) == 0)
    {
        return FALSE;
    }

    return TRUE;
}

INT32 _picture_mode_get_pic_name(INT16 i2_idx, CHAR* s_name,UINT8 ui1_len)
{
    if (i2_idx < ACFG_PRE_SET_PIC_MODE_NUM)
    {
        c_uc_w2s_to_ps( MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_ITEM_VIVID+i2_idx), s_name, ui1_len);
    }
    else
    {
        BOOL    b_is_exist = FALSE;

        a_cfg_cust_get_cust_pic_mode_exist_status(i2_idx,&b_is_exist);

        if(b_is_exist)
        {
            a_cfg_cust_get_cust_pic_mode_name(i2_idx, s_name,ui1_len);
        }
    }

    return MENUR_OK;

}

INT32 _copy_picture_mode_toast_view(INT16 i2_from_pic,INT16 i2_to_pic)
{
    WDK_TOAST_T*   pt_toast_cpy = NULL;
    UTF16_T        w2s_tmp_str[128] = {0};
    CHAR           s_str[128] = {0};
    CHAR           s_tmp_str[128] = {0};
    CHAR           s_pic_from[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = {0};
    CHAR           s_pic_to[MENU_CUST_PIC_MODE_NAME_MAX_LEN+1] = {0};
    UINT16         ui2_len = 0;
    c_uc_w2s_to_ps( MENU_TEXT(MLM_MENU_KEY_VID_COPY_PIC_MODE_HINT), s_tmp_str, sizeof(s_tmp_str));

    _picture_mode_get_pic_name(i2_from_pic,s_pic_from,MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);
    _picture_mode_get_pic_name(i2_to_pic,s_pic_to,MENU_CUST_PIC_MODE_NAME_MAX_LEN+1);

    c_sprintf(s_str, s_tmp_str, s_pic_from,s_pic_to);

    c_uc_ps_to_w2s(s_str, w2s_tmp_str, sizeof(w2s_tmp_str));

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));
    if (NULL == pt_toast_cpy)
    {
        DBG_LOG_PRINT(("NULL == c_mem_alloc pt_toast_cpy!!\n"));
        return MENUR_FAIL;
    }
    c_memset((VOID*)pt_toast_cpy, 0x0, sizeof(WDK_TOAST_T));

    pt_toast_cpy->e_toast_style = WDK_STRING_TOAST;
    pt_toast_cpy->e_string_style = WDK_STRING_STRING;

    ui2_len = (c_uc_w2s_strlen(w2s_tmp_str) + 1)*2;

    DBG_LOG_PRINT(("[menu] hint :%s, alloc_mem length:%d, %s,%d\r\n",s_str,ui2_len,__FUNCTION__,__LINE__));

    pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(ui2_len);

    if (pt_toast_cpy->style.style_4.w2s_str == NULL)
    {
        DBG_LOG_PRINT(("NULL == c_mem_alloc w2s_str!!\n"));

        // Fix coverity-4664840 Resource leak.
        c_mem_free(pt_toast_cpy);

        return MENUR_FAIL;
    }

    c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, ui2_len);

    c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)w2s_tmp_str, ui2_len);

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);

    return MENUR_OK;
}

static INT32 _copy_cus_pic_mode_to_preset_pic_mode(INT16 i2_to_pic)
{
    INT16                       i2_from_pic = 0;
    INT32                       i4_ret = 0;

    /* Set modify flag*/
    a_cfg_set_preset_pic_mode_chg_status_ex(i2_to_pic,TRUE);

    /*get current picture mode*/
    a_cfg_av_get(
           CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
           &i2_from_pic);

    DBG_LOG_PRINT(("[MENU]copy picture mode from :%d to %d, %s,%d\r\n",i2_from_pic,i2_to_pic,__FUNCTION__,__LINE__));
    i4_ret = a_cfg_cust_copy_pic_mode_to_pic_mode(i2_from_pic,i2_to_pic);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _copy_picture_mode_toast_view(i2_from_pic,i2_to_pic);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_refresh();

    return i4_ret;
}

INT32 menu_copy_cus_pic_mode_to_preset_pic_mode(INT16 i2_to_pic)
{
    return _copy_cus_pic_mode_to_preset_pic_mode(i2_to_pic);
}

static INT32 _copy_pic_mode_lb2_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32 i4_ret = 0;
    UINT16  ui2_crnt_ht = 0;

    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        i4_ret=c_wgl_do_cmd(h_widget,
                            WGL_CMD_LB_HLT_ELEM,
                            WGL_PACK(0),
                            NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_VID_COPY_PIC_MODE_HELP));
        menu_pm_repaint();
    }
    else if (ui4_msg == WGL_MSG_KEY_DOWN ||
             ui4_msg == WGL_MSG_KEY_REPEAT)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
            {
                _copy_cus_pic_mode_to_preset_pic_mode(ui2_crnt_ht);

                i4_ret = menu_nav_back();
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;
            case BTN_CURSOR_UP:
            if (ui2_crnt_ht == 0)
            {
                i4_ret = c_wgl_do_cmd(h_widget,
                                      WGL_CMD_LB_UNHLT_ELEM,
                                      WGL_PACK(ui2_crnt_ht),
                                      NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_set_focus_on_backbar(FALSE);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }
                break;

            case BTN_RETURN:
            {
                i4_ret = c_wgl_set_visibility(h_widget, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_nav_back();
                break;
            }
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP==ui4_msg)
    {
        UINT32  ui4_crnt_page;
        UTF16_T*  pt_w2s = NULL;

        i4_ret = menu_nav_get_crnt_page(&ui4_crnt_page);
        MENU_CHK_FAIL(i4_ret);

        if (ui4_crnt_page == ui4_g_menu_custom_page_lock_pic_lb2)
        {
            i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_w2s = MENU_TEXT( MLM_MENU_KEY_VID_PIC_MODE_ITEM_VIVID + ui2_crnt_ht);

            a_app_tts_play(pt_w2s, c_uc_w2s_strlen(pt_w2s));
        }
    }
#endif

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _lock_pic_mode_lb2_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32 i4_ret = 0;
    BOOL b_is_confirmed = FALSE;
    BOOL b_is_lock_status = FALSE;
    UINT16  ui2_crnt_ht = 0;

    if(ui1_g_edit_tpye == ICL_PICTURE_EDIT_COPY_PIC)
    {
         return _copy_pic_mode_lb2_proc_fct(h_widget, ui4_msg, pv_param1, pv_param2);
    }

    i4_ret = a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
    MENU_LOG_ON_FAIL(i4_ret);


    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        i4_ret=c_wgl_do_cmd(h_widget,
                            WGL_CMD_LB_HLT_ELEM,
                            WGL_PACK(b_from_backbar ? 0 : (b_is_lock_status ? 1 : 0)),
                            NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        b_from_backbar = FALSE;

        menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_LOCK_PIC_MODE));
        menu_pm_repaint();
    }
    else if (ui4_msg == WGL_MSG_KEY_DOWN ||
             ui4_msg == WGL_MSG_KEY_REPEAT)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
            {
                extern int a_get_is_pin_confirmed(BOOL*);
                a_get_is_pin_confirmed(&b_is_confirmed);

                ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[MENU][SYS_PIN]{%s,%d} b_is_confirmed:%d \n", __FUNCTION__, __LINE__, b_is_confirmed )););

                if (!b_is_confirmed)
                {
                    if (!_lock_pic_mode_check_is_set_sys_pin() && !b_is_lock_status)
                    {
                        ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[MENU][SYS_PIN]{%s,%d} goto page_lock_pic_mode\n", __FUNCTION__, __LINE__ )););
                        /* create system pin */
                        i4_ret = menu_nav_go(ui4_g_menu_custom_page_lock_pic_mode,NULL);
                    }
                    else
                    {
                        ACFG_DEBUG_SYS_PIN(DBG_LOG_PRINT(("[MENU][SYS_PIN]{%s,%d} goto page_unlock_pic_mode\n", __FUNCTION__, __LINE__ )););
                        /* confirmed system pin */
                        if (ui2_crnt_ht == 0)
                        {
                            a_menu_set_picture_mode_tmp_lock_status(FALSE);
                        }
                        else
                        {
                            a_menu_set_picture_mode_tmp_lock_status(TRUE);
                        }
                        i4_ret = menu_nav_go(ui4_g_menu_custom_page_unlock_pic_mode,NULL);
                    }
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    if (ui2_crnt_ht == 0)
                    {
                        b_is_lock_status = FALSE;
                    }
                    else
                    {
                        b_is_lock_status = TRUE;
                    }
                    i4_ret = a_cfg_cust_set_cust_pic_mode_lock_status(b_is_lock_status);
                    MENU_LOG_ON_FAIL(i4_ret);

                    set_delay_lock_cust_pic_mode_status(b_is_lock_status);
                    menu_pic_energy_change_sepcial_page_set_status(TRUE);

                    i4_ret = menu_nav_back();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
                break;
            case BTN_CURSOR_UP:
            {
                if (ui2_crnt_ht == 0)
                {
                    i4_ret = c_wgl_do_cmd(h_widget,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_set_focus_on_backbar(FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
                break;
            case BTN_CURSOR_DOWN:
            {
            }
                break;
            case BTN_RETURN:
                i4_ret = c_wgl_set_visibility(h_widget, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_nav_back();
                break;
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP==ui4_msg)
    {
        UINT32  ui4_crnt_page;
        UTF16_T*  pt_w2s = NULL;

        i4_ret = menu_nav_get_crnt_page(&ui4_crnt_page);
        MENU_CHK_FAIL(i4_ret);

        if (ui4_crnt_page == ui4_g_menu_custom_page_lock_pic_lb2)
        {
            i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_w2s = MENU_TEXT((ui2_crnt_ht == 0) ? MLM_MENU_KEY_OFF : MLM_MENU_KEY_ON);

            a_app_tts_play(pt_w2s, c_uc_w2s_strlen(pt_w2s));
        }
    }
#endif

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _lock_pic_mode_lb2_create(HANDLE_T h_parent, HANDLE_T* pt_wgt)
{
    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_parent,
                               &t_rect,
                               _lock_pic_mode_lb2_proc_fct,
                               &t_lb_init,
                               NULL,
                               pt_wgt);
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*pt_wgt,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(&t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(*pt_wgt,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret=  MENUR_OK;
    HANDLE_T    h_cnt_frm = NULL_HANDLE;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _lock_pic_mode_lb2_create(h_cnt_frm, &h_lock_pic_lb2);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    INT32 i4_ret = c_wgl_destroy_widget(h_lock_pic_lb2);
    MENU_LOG_ON_FAIL(i4_ret);

    h_lock_pic_lb2 = NULL_HANDLE;

    return MENUR_OK;
}
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32 i4_ret;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
        menu_pm_repaint();
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
            case BTN_RETURN :
            case BTN_SELECT :
            {
                menu_nav_back();
                break;
            }
            case BTN_CURSOR_DOWN:
            {
                b_from_backbar = TRUE;
                i4_ret = c_wgl_set_focus(h_lock_pic_lb2, WGL_NO_AUTO_REPAINT);
                MENU_CHK_FAIL(i4_ret);
                break;
            }
            default :
                break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static VOID _lock_pic_lb2_move_help_tip(UINT8 ui1_row_num)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T  h_last_shadow_item;

    /* move help tip text */
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui1_row_num + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32  i4_ret = 0;

    UINT8       ui1_val      = ICL_PICTURE_EDIT_LOCK_PIC;
    UINT16      ui2_elem_num = 0;
    UINT16      ui2_i = 0;

    a_icl_get_picture_edit_type_status(&ui1_val);
    ui1_g_edit_tpye = ui1_val;

    if(ui1_g_edit_tpye == ICL_PICTURE_EDIT_LOCK_PIC)
    {
        menu_main_set_title(MLM_MENU_KEY_MENU_ITEM_LOCK_PIC_MODE);

        ui2_elem_num = MLM_MENU_KEY_ON - MLM_MENU_KEY_OFF + 1;

        i4_ret=c_wgl_do_cmd(h_lock_pic_lb2,
                            WGL_CMD_LB_SET_ELEM_NUM,
                            WGL_PACK(ui2_elem_num),
                            NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        for( ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
        {
            i4_ret = c_wgl_do_cmd(h_lock_pic_lb2,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (ui2_i, 0),
                            WGL_PACK(MENU_TEXT(MLM_MENU_KEY_OFF + ui2_i)));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        menu_main_set_title(MLM_MENU_KEY_VID_COPY_PIC_MODE);

        ui2_elem_num = MLM_MENU_KEY_VID_PIC_MODE_ITEM_SPORT - MLM_MENU_KEY_VID_PIC_MODE_ITEM_VIVID + 1;

        i4_ret=c_wgl_do_cmd(h_lock_pic_lb2,
                            WGL_CMD_LB_SET_ELEM_NUM,
                            WGL_PACK(ui2_elem_num),
                            NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
        {
            i4_ret = c_wgl_do_cmd(h_lock_pic_lb2,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (ui2_i, 0),
                            WGL_PACK(MENU_TEXT(MLM_MENU_KEY_VID_PIC_MODE_ITEM_VIVID + ui2_i)));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    _lock_pic_lb2_move_help_tip(ui2_elem_num);

    i4_ret = c_wgl_set_visibility(h_lock_pic_lb2, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(h_lock_pic_lb2, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct);

    menu_pm_repaint();

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32 i4_ret = c_wgl_set_visibility(h_lock_pic_lb2, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
    ui1_g_edit_tpye = ICL_PICTURE_EDIT_LOCK_PIC;
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}
extern INT32 menu_page_lock_pic_mode_lb2_init(VOID)
{
    t_g_menu_page_lock_pic_lb2.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_lock_pic_lb2.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_lock_pic_lb2.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_lock_pic_lb2.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_lock_pic_lb2.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_lock_pic_lb2.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_lock_pic_lb2.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}



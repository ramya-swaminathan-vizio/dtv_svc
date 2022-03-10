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
 * $RCSfile: menu_page_pwd.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/9 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 9cd3c20f32467f383f0d47c1431bb92b $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_wgl_rect.h"
#include "app_util/a_cfg.h"

#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#include "res/app_util/config/a_cfg_custom.h"
#include "res/menu2/menu_custom.h"
#endif
#include "menu2/menu_dbg.h"

#ifdef COMMON_PWD_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define CLEAR_MEMORY_PWD_FRAME_W   (275)
#define CLEAR_MEMORY_PWD_FRAME_H   (190)

#define CLEAR_MEMORY_PWD_TITLE_X        (12)
#define CLEAR_MEMORY_PWD_TITLE_Y        (6)
#define CLEAR_MEMORY_PWD_TITLE_W        (CLEAR_MEMORY_PWD_FRAME_W - CLEAR_MEMORY_PWD_TITLE_X )
#define CLEAR_MEMORY_PWD_TITLE_H        (22)

#define CLEAR_MEMORY_PWD_ERROR_INFO_X         (13)
#define CLEAR_MEMORY_PWD_ERROR_INFO_Y         (30)
#define CLEAR_MEMORY_PWD_ERROR_INFO_W         (CLEAR_MEMORY_PWD_FRAME_W - (CLEAR_MEMORY_PWD_ERROR_INFO_X)*2)
#define CLEAR_MEMORY_PWD_ERROR_INFO_H         (64)

#define CLEAR_MEMORY_PWD_BUTTON_X   (11)
#define CLEAR_MEMORY_PWD_BUTTON_Y   (113)
#define CLEAR_MEMORY_PWD_BUTTON_W   (55)
#define CLEAR_MEMORY_PWD_BUTTON_H   (61)
#define CLEAR_MEMORY_PWD_BUTTON_DIS (11)

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#define COUNTRY_CODE_IDX_CA        (0)
#define COUNTRY_CODE_IDX_MEX       (1)
#define COUNTRY_CODE_IDX_US        (2)
#define COUNTRY_CODE_IDX_LAST      (3)
#endif

typedef enum
{
  BUTTON_1 = 0,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  BUTTON_LAST_ENTRY
} CLEAR_MEMORY_PWD_BUTTIONS;

typedef struct _CLEAR_MEMORY_PWD_T
{
    HANDLE_T h_root_frm;
    HANDLE_T h_main_frm;
    HANDLE_T h_button[BUTTON_LAST_ENTRY];
    HANDLE_T h_error_info;
    HANDLE_T h_title;
}CLEAR_MEMORY_PWD_T;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T                 t_g_menu_clear_memory_pwd;
static CLEAR_MEMORY_PWD_T           t_g_clear_memory_pwd;
static CLEAR_MEMORY_PWD_BUTTIONS    e_current_button = BUTTON_1;
static UTF16_T                      w2s_g_str[BUTTON_LAST_ENTRY + 1] = {0};
static UINT32                       ui4_g_page_id = 0;
static UINT32                       ui4_g_page_id_pass = 0;
static BOOL                         g_b_pwd_dialog_show = FALSE;
static UINT32                       ui4_cust_page_id_pass = 0;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _on_page_show(UINT32 ui4_page_id);

/*----------------------------------------------------------------------------
 * Name: _set_error_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _update_error_info(UTF16_T* w2s_str)
{
    INT32   i4_ret = 0;

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    BOOL    b_page_from_tls = FALSE;
    WGL_FONT_INFO_T     t_fnt_info;

    menu_custom_page_get_clear_memory_page_status(&b_page_from_tls);
    if (b_page_from_tls)
    {
        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (t_g_clear_memory_pwd.h_error_info,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (t_g_clear_memory_pwd.h_error_info,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        MENU_CHK_FAIL(i4_ret);
    }
#endif

    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_error_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(0xFF));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _button_update_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _button_update_info(HANDLE_T h_widget,BOOL b_have_pwd)
{
    INT32               i4_ret = 0;
    WGL_IMG_INFO_T      t_img_info;

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;

    if(b_have_pwd)
    {
        t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_clrmem_pwd_unempty;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_clrmem_pwd_unempty;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_clrmem_pwd_unempty_hlt;
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_clrmem_pwd_empty_hlt;
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;


}

/*----------------------------------------------------------------------------
 * Name: _button_repaint
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _button_repaint(BOOL b_is_repaint_all,HANDLE_T h_first_widget, HANDLE_T h_last_widget)
{
    INT32  i4_ret = -1;
    GL_RECT_T   t_rect_1;
    GL_RECT_T   t_rect_2;
    GL_RECT_T   t_rect_union;
    GL_RECT_T*  pt_rect = NULL;

    if(b_is_repaint_all == FALSE)
    {
        i4_ret = c_wgl_get_coords(h_first_widget,
                         WGL_COORDS_PARENT,
                         &t_rect_1);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_get_coords(h_last_widget,
                         WGL_COORDS_PARENT,
                         &t_rect_2);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_rect_union(&t_rect_union, &t_rect_1, &t_rect_2);
        MENU_CHK_FAIL(i4_ret);

        pt_rect = &t_rect_union;
    }

    i4_ret = c_wgl_repaint(t_g_clear_memory_pwd.h_main_frm,pt_rect,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _button_store_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _button_store_info(UINT8 ui1_input)
{
    INT32   i4_ret;
    CHAR    s_buf[2] = {0};
    UTF16_T w2s_str_temp[2] = {0};

    if(ui1_input > 9)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_sprintf(s_buf, "%d",  ui1_input);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_uc_ps_to_w2s(s_buf, w2s_str_temp, 1);
    MENU_CHK_FAIL(i4_ret);

    if(BUTTON_LAST_ENTRY > c_uc_w2s_strlen(w2s_g_str))
    {
        c_uc_w2s_strcat(w2s_g_str,w2s_str_temp);
    }
    else
    {
        return MENUR_INV_STATE;
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _proc_fct(HANDLE_T    h_widget,
                       UINT32      ui4_msg,
                       VOID*       param1,
                       VOID*       param2)
{
    UINT32 ui4_keycode = (UINT32)param1;
    BOOL   b_pass = FALSE;

#if 0 //def APP_ADD_COUNTRY_CODE_SUPPORT
	ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_HOME;
#endif
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch(ui4_keycode)
            {
                case BTN_KB_BACKSPACE:
                case BTN_CURSOR_LEFT:
                {
                    if(e_current_button != BUTTON_1)
                    {
                        e_current_button --;
                        if (e_current_button >= BUTTON_LAST_ENTRY) {
                            // should not go here, e_current_button overflow
                            return MENUR_INV_STATE;
                        }
                        w2s_g_str[e_current_button] = 0;

                        _button_update_info(t_g_clear_memory_pwd.h_button[e_current_button],FALSE);

                        c_wgl_set_focus(t_g_clear_memory_pwd.h_button[e_current_button],WGL_NO_AUTO_REPAINT);

                        _button_repaint(FALSE,t_g_clear_memory_pwd.h_button[e_current_button],h_widget);
                    }
                    else
                    {
                        menu_nav_back();
                    }

                    return MENUR_OK;
                }
                case BTN_SELECT:
                    break;

                case BTN_RETURN:
                {
                    menu_nav_back();
                    return MENUR_OK;
                }
                case BTN_DIGIT_0:
                case BTN_DIGIT_1:
                case BTN_DIGIT_2:
                case BTN_DIGIT_3:
                case BTN_DIGIT_4:
                case BTN_DIGIT_5:
                case BTN_DIGIT_6:
                case BTN_DIGIT_7:
                case BTN_DIGIT_8:
                case BTN_DIGIT_9:
                case BTN_KB_0:
                case BTN_KB_1:
                case BTN_KB_2:
                case BTN_KB_3:
                case BTN_KB_4:
                case BTN_KB_5:
                case BTN_KB_6:
                case BTN_KB_7:
                case BTN_KB_8:
                case BTN_KB_9:
                {
                    if(e_current_button != BUTTON_4)
                    {
                        _button_store_info(ui4_keycode - BTN_DIGIT_0);

                        _button_update_info(t_g_clear_memory_pwd.h_button[e_current_button],TRUE);

                        e_current_button++;
                        c_wgl_set_focus(t_g_clear_memory_pwd.h_button[e_current_button],WGL_NO_AUTO_REPAINT);

                        _button_repaint(FALSE,t_g_clear_memory_pwd.h_button[e_current_button],h_widget);
                    }
                    else
                    {
                        _button_store_info(ui4_keycode - BTN_DIGIT_0);
                        a_cfg_chk_password(w2s_g_str, &b_pass);

                        if (b_pass)
                        {
                            if (ui4_cust_page_id_pass != 0
                                && ui4_cust_page_id_pass != ui4_g_page_clear_memory_dialog)
                            {
                                menu_nav_back_ex(FALSE);
                                MENU_LOG_ON_FAIL(menu_set_page_hide(TRUE));

                                menu_nav_go(ui4_cust_page_id_pass, NULL);
                                ui4_cust_page_id_pass = 0;
                                return MENUR_OK;
                            }

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
                            UINT16 t_country;
                            BOOL   b_page_from_tls = FALSE;

                            menu_custom_page_get_tmp_country_code(&t_country);
                            menu_custom_page_get_clear_memory_page_status(&b_page_from_tls);;

                            if (b_page_from_tls)
                            {
                                t_country = (t_country < COUNTRY_CODE_IDX_CA || t_country >= COUNTRY_CODE_IDX_LAST)
                                            ? COUNTRY_CODE_IDX_CA : t_country;

                                switch (t_country)
                                {
                                    case COUNTRY_CODE_IDX_US:
                                        a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_US);
                                        break;

                                    case COUNTRY_CODE_IDX_CA:
                                        a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_CA);
                                        break;

                                    case COUNTRY_CODE_IDX_MEX:
                                        a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_MEX);
                                        break;

                                    //case COUNTRY_CODE_IDX_UNKNOWN:
                                    default:
                                        a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_CA);
                                        break;
                                }
                                menu_nav_back();
                            }
                            else
                            {
							#if 0 //def APP_RETAIL_MODE_SUPPORT
								a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
								if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
								{
									menu_nav_back();
									clear_memory();
								}
								else
								{
									menu_nav_back_and_go(ui4_g_page_id_pass, NULL);
								}
							#else
								menu_nav_back_and_go(ui4_g_page_id_pass, NULL);
							#endif


                            }

#else
                    #if 0 //def APP_RETAIL_MODE_SUPPORT
                            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
							if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
							{
								clear_memory();
								menu_nav_back();
							}
							else
							{
								menu_nav_back_and_go(ui4_g_page_id_pass, NULL);
							}
					#else
							menu_nav_back_and_go(ui4_g_page_id_pass, NULL);
					#endif
#endif
                        }
                        else
                        {
                            _update_error_info(MENU_TEXT(MLM_MENU_KEY_CLR_MEM_ERROR_INFO));

                            _on_page_show(0);

                            _button_repaint(TRUE,NULL_HANDLE,NULL_HANDLE);

                        }
                    }
                    return MENUR_OK;
                }
                default :
                    break;
            }
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _clear_memory_pwd_main_frm_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _clear_memory_pwd_main_frm_create(VOID)
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style;
    WGL_IMG_INFO_T    t_img_info;

    ui4_style = 0;

    c_memset(&t_rect, 0x0, sizeof(GL_RECT_T));

    SET_RECT_BY_SIZE( &t_rect,
                      ((SCREEN_W - CLEAR_MEMORY_PWD_FRAME_W)/2),
                      ((SCREEN_H - CLEAR_MEMORY_PWD_FRAME_H)/2),
                      CLEAR_MEMORY_PWD_FRAME_W,
                      CLEAR_MEMORY_PWD_FRAME_H );


    i4_ret = c_wgl_create_widget(t_g_clear_memory_pwd.h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &t_g_clear_memory_pwd.h_main_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_clear_memory_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_clear_memory_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_clear_memory_bk;

    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_main_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _clear_memory_pwd_button_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _clear_memory_pwd_button_create(HANDLE_T    h_parent,
                                                    HANDLE_T*   ph_widget,
                                                    UINT8       ui1_idx)
{
    INT32               i4_ret;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = 0;

    c_memset(&t_rect, 0x0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     (CLEAR_MEMORY_PWD_BUTTON_X+ ((CLEAR_MEMORY_PWD_BUTTON_DIS+ CLEAR_MEMORY_PWD_BUTTON_W)*ui1_idx)),
                     CLEAR_MEMORY_PWD_BUTTON_Y,
                     CLEAR_MEMORY_PWD_BUTTON_W,
                     CLEAR_MEMORY_PWD_BUTTON_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _proc_fct,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_inset, 0x0, sizeof(WGL_INSET_T));

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_INSET,
                           &t_inset,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable             = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_menu_color_white;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    /* Set Image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;/*h_g_menu_img_clrmem_pwd_empty;*/
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;/*h_g_menu_img_clrmem_pwd_empty;*/
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_clrmem_pwd_empty_hlt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _clear_memory_pwd_title_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _clear_memory_pwd_title_create(VOID)
{
    INT32               i4_ret;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = WGL_STL_GL_NO_IMG_UI;

    SET_RECT_BY_SIZE(&t_rect,
                     CLEAR_MEMORY_PWD_TITLE_X,
                     CLEAR_MEMORY_PWD_TITLE_Y,
                     CLEAR_MEMORY_PWD_TITLE_W,
                     CLEAR_MEMORY_PWD_TITLE_H);

    i4_ret = c_wgl_create_widget(t_g_clear_memory_pwd.h_main_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &t_g_clear_memory_pwd.h_title);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_title,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (t_g_clear_memory_pwd.h_title,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _clear_memory_pwd_error_info_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _clear_memory_pwd_error_info_create(VOID)
{
    INT32               i4_ret;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MAX_128
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     CLEAR_MEMORY_PWD_ERROR_INFO_X,
                     CLEAR_MEMORY_PWD_ERROR_INFO_Y,
                     CLEAR_MEMORY_PWD_ERROR_INFO_W,
                     CLEAR_MEMORY_PWD_ERROR_INFO_H);

    i4_ret = c_wgl_create_widget(t_g_clear_memory_pwd.h_main_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &t_g_clear_memory_pwd.h_error_info);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_error_info,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (t_g_clear_memory_pwd.h_error_info,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_error_info,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_error_info,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32                i4_ret;
    UINT8                ui1_btn_idx = 0;

    c_memset(&t_g_clear_memory_pwd, 0, sizeof(CLEAR_MEMORY_PWD_T));

    ui4_g_page_id = ui4_page_id;

    ui4_g_page_id_pass = (UINT32)pv_create_data;

    i4_ret = menu_pm_get_root_frm(&t_g_clear_memory_pwd.h_root_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _clear_memory_pwd_main_frm_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _clear_memory_pwd_title_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _clear_memory_pwd_error_info_create();
    MENU_CHK_FAIL(i4_ret);

    for(ui1_btn_idx = 0; ui1_btn_idx < BUTTON_LAST_ENTRY; ui1_btn_idx++)
    {
        i4_ret = _clear_memory_pwd_button_create(t_g_clear_memory_pwd.h_main_frm,
                                                    &t_g_clear_memory_pwd.h_button[ui1_btn_idx],
                                                    ui1_btn_idx);
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(t_g_clear_memory_pwd.h_main_frm,WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_g_clear_memory_pwd.h_main_frm, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32    i4_ret;
    UINT8    ui1_loop = 0;
    UTF16_T  w2s_title[64] = {0};
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    ACFG_COUNTRY_CODE_T t_country;
    BOOL                b_page_from_tls = FALSE;
#endif

    c_memset(w2s_title, 0, sizeof(w2s_title));
    c_uc_w2s_toupper(w2s_title, 63, MENU_TEXT(MLM_MENU_KEY_CLRMEM_PWD_TITLE), NULL);

    c_wgl_float(t_g_clear_memory_pwd.h_main_frm, TRUE, FALSE);

    i4_ret = c_wgl_set_visibility(t_g_clear_memory_pwd.h_main_frm,WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    for(ui1_loop = 0; ui1_loop < BUTTON_LAST_ENTRY; ui1_loop++)
    {
        _button_update_info(t_g_clear_memory_pwd.h_button[ui1_loop],FALSE);
    }
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    menu_custom_page_get_clear_memory_page_status(&b_page_from_tls);
    if (b_page_from_tls)
    {
        a_cfg_custom_get_country_code(&t_country);
        if (t_country == ACFG_COUNTRY_CODE_MEX)
        {
            i4_ret = _update_error_info(MENU_TEXT(MLM_MENU_KEY_MEXICO_CHG_COUNTRY));
            if(i4_ret != WGLR_OK)
            {
                return MENUR_FAIL;
            }
        }
        else if (t_country == ACFG_COUNTRY_CODE_CA)
        {
            i4_ret = _update_error_info(MENU_TEXT(MLM_MENU_KEY_CANADA_CHG_COUNTRY));
            if(i4_ret != WGLR_OK)
            {
                return MENUR_FAIL;
            }
        }
        else if (t_country == ACFG_COUNTRY_CODE_US)
        {
            i4_ret = _update_error_info(MENU_TEXT(MLM_MENU_KEY_USA_CHG_COUNTRY));
            if(i4_ret != WGLR_OK)
            {
                return MENUR_FAIL;
            }
        }

        i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_title,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COUNTRY)),
                              WGL_PACK(0xFF));
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _update_error_info(MENU_TEXT(MLM_MENU_KEY_CLRMEM_PWD_HELP_INFO));
        if(i4_ret != WGLR_OK)
        {
            return MENUR_FAIL;
        }
        i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_title,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK(w2s_title),
                              WGL_PACK(0xFF));
        MENU_CHK_FAIL(i4_ret);
    }
#else
    i4_ret = _update_error_info(MENU_TEXT(MLM_MENU_KEY_CLR_MEM_HELP_INFO));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_clear_memory_pwd.h_title,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_title),
                            WGL_PACK(0xFF));
    MENU_CHK_FAIL(i4_ret);
#endif



    c_memset(w2s_g_str,0,sizeof(w2s_g_str));

    i4_ret = c_wgl_set_focus(t_g_clear_memory_pwd.h_button[BUTTON_1],WGL_NO_AUTO_REPAINT );
    MENU_CHK_FAIL(i4_ret);

    e_current_button = BUTTON_1;

    g_b_pwd_dialog_show = TRUE;
    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32 i4_ret;

    c_wgl_float(t_g_clear_memory_pwd.h_main_frm, FALSE, FALSE);

    i4_ret = c_wgl_set_visibility(t_g_clear_memory_pwd.h_main_frm,
                                    WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    g_b_pwd_dialog_show = FALSE;
    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{

    return MENUR_OK;
}

BOOL menu_clear_memory_pwd_is_show(VOID)
{
    return g_b_pwd_dialog_show;
}

extern INT32 menu_clear_memory_pwd_init(VOID)
{
    t_g_menu_clear_memory_pwd.pf_menu_page_create =    _on_page_create;
    t_g_menu_clear_memory_pwd.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_clear_memory_pwd.pf_menu_page_show=       _on_page_show;
    t_g_menu_clear_memory_pwd.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_clear_memory_pwd.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_clear_memory_pwd.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_clear_memory_pwd.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

VOID menu_clear_memory_set_cust_page_id_pass(UINT32 ui4_page_id)
{
    ui4_cust_page_id_pass = ui4_page_id;
}

#endif /* COMMON_PWD_ENABLE */

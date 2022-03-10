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
 * $RCSfile: help_tip.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/19 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 7ed3c11a9ed90eba15305b24039bcab7 $
 *
 * Description:
 *      This file contains the implementation of channel lists.
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_tools.h"
#include "u_irrc_btn_def.h"

#include "c_os.h"
#include "c_handle.h"
#include "c_fe.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_sets.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "a_help_tip.h"
#include "app_util/a_common.h"

#if defined(APP_COLOR_MODE_PALLET)
#include "res/a_pallet_defs.h"
#endif

#include "res/app_util/help_tip/help_tip_img_2013.i"

#define NEW_TIP  1
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct __HELP_TIP_T
{
    HANDLE_T                h_frame;
    HANDLE_T                h_text;
    HANDLE_T                h_timer;
    CHAR*                   font_name;

#if NEW_TIP
    HANDLE_T                h_icon_blue;
    HANDLE_T                h_icon_red;
	HANDLE_T                h_icon_green;
    UINT8                   ui1_focus_icon_idx;

#endif

    x_os_timer_cb_fct     pf_timeout_notify;
}_HELP_TIP_T;

#define HELP_TIP_TXT_INSET_L  (8)
#define HELP_TIP_TXT_INSET_R  (8)
#define HELP_TIP_TXT_INSET_T  (8)
#define HELP_TIP_TXT_INSET_B  (8)

#define HELP_TIP_TXT_ALLIGN   WGL_AS_LEFT_TOP

#define HELP_TIP_TIMEOUT      (1000)

WGL_HIMG_TPL_T  h_g_img_help_tip_bk    = NULL_HANDLE;

#if defined(APP_COLOR_MODE_PALLET)
    GL_COLOR_T      t_g_help_tip_txt_color = {255, {0}, {0}, {27}};
    GL_COLOR_T      t_g_help_tip_bk_color  = {  0, {0}, {0}, {2}};
#else
    GL_COLOR_T      t_g_help_tip_txt_color = { 255, { 253 }, { 253 }, { 255 }};
    GL_COLOR_T      t_g_help_tip_bk_color  = {  0, {0}, {0}, {0} };
#endif

GL_COLOR_T      t_g_help_tip_txt_color_oled = { 255, { 191 }, { 191 }, { 191 }};


#if NEW_TIP
WGL_HIMG_TPL_T  h_g_img_help_tip_blue    	= NULL_HANDLE;
WGL_HIMG_TPL_T  h_g_img_help_tip_blue_h 	= NULL_HANDLE;

#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
WGL_HIMG_TPL_T  h_g_img_help_tip_blue_g 	= NULL_HANDLE;
#endif
WGL_HIMG_TPL_T  h_g_img_help_tip_red     	= NULL_HANDLE;
WGL_HIMG_TPL_T  h_g_img_help_tip_red_h   	= NULL_HANDLE;

WGL_HIMG_TPL_T  h_g_img_help_tip_green   	= NULL_HANDLE;
WGL_HIMG_TPL_T  h_g_img_help_tip_green_h 	= NULL_HANDLE;
WGL_HIMG_TPL_T  h_g_img_help_tip_green_gray = NULL_HANDLE;





#define HELP_TIP_ICON_YELLOW_LEFT   (9)
#define HELP_TIP_ICON_YELLOW_RIGHT  (HELP_TIP_ICON_YELLOW_LEFT +70)
#define HELP_TIP_ICON_BLUE_LEFT     (HELP_TIP_ICON_YELLOW_RIGHT + 13)
#define HELP_TIP_ICON_BLUE_RIGHT    (HELP_TIP_ICON_BLUE_LEFT+70)
#define HELP_TIP_ICON_GREEN_RIGHT   (405-16)
#define HELP_TIP_ICON_GREEN_LEFT    (HELP_TIP_ICON_GREEN_RIGHT - 70)
#define HELP_TIP_ICON_RED_RIGHT     (HELP_TIP_ICON_GREEN_LEFT-13)
#define HELP_TIP_ICON_RED_LEFT      (HELP_TIP_ICON_RED_RIGHT-70)
#endif

static HANDLE_T h_handle_last=NULL_HANDLE;
static UTF16_T  w2s_help_txt_last[HELP_TIP_LAST_TXT_LEN+1] = {0};

/*-----------------------------------------------------------------------------
                    private function declarations
 ----------------------------------------------------------------------------*/
static INT32 _help_tip_set_theme(HANDLE_T  h_help_tip);
/*-----------------------------------------------------------------------------
                    private function definition
 ----------------------------------------------------------------------------*/

static INT32 _btn_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                c_wgl_set_focus(h_handle_last,WGL_SYNC_AUTO_REPAINT);
                break;
            case BTN_SELECT:
                /* Exit the menu  */
                menu_leave(FALSE,0);

            break;

            default:
                /* do nothing */
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _help_tip_text_add_dot
 *
 * Description: Add a dot to the end of string
 *
 * Inputs: pw2s_text
 *
 * Outputs: None
 *
 * Returns: TRUE:Need add dot; FALSE: not add dot
 *
 ----------------------------------------------------------------------------*/
static BOOL _help_tip_text_add_dot(HANDLE_T h_text, UTF16_T *pw2s_text)
{
    BOOL    b_not_set = FALSE;
    INT32   i4_ret = HELP_TIPR_OK;
    SIZE_T  t_len = 0;
    SIZE_T  t_idx = 0;
    static UTF16_T w2s_text[512] = {0};

    if (NULL_HANDLE == h_text
        || NULL == pw2s_text
        || (t_len = c_uc_w2s_strlen(pw2s_text)) == 0)
    {
        return FALSE;
    }

    c_memset(w2s_text, 0, sizeof(w2s_text));
    c_uc_w2s_strcpy(w2s_text, pw2s_text);

    //t_idx = t_len > 0 ? t_len - 1 : 0;  --> "t_len" must be greater than 0 ,CID:4491669
    t_idx = t_len - 1;
    do{
        if (w2s_text[t_idx] == L' ')
        {
            /* Do nothing */
        }
        else if (w2s_text[t_idx] == L'.')
        {
            b_not_set = FALSE;
            break;
        }
        else
        {
            if (t_idx < 511)
            {
                w2s_text[t_idx+1] = L'.';

                /* set text */
                i4_ret = c_wgl_do_cmd(h_text,
                                      WGL_CMD_TEXT_SET_TEXT,
                                      (VOID*)w2s_text,
                                      (VOID*)512);
                if(i4_ret < 0)
                {
                    b_not_set = FALSE;
                }
                b_not_set = TRUE;
            }

            break;
        }

    }while (t_idx-- != 0);

    return b_not_set;
}


/*----------------------------------------------------------------------------
 * Name: _help_tip_set_theme
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
static INT32 _help_tip_set_theme(HANDLE_T  h_help_tip)
{
    //WGL_IMG_INFO_T      t_img_info;
    WGL_INSET_T         t_inset;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;
    INT32               i4_ret;
    _HELP_TIP_T*        pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* set text inset */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = HELP_TIP_TXT_INSET_T;
    t_inset.i4_bottom   = HELP_TIP_TXT_INSET_B;

    i4_ret = c_wgl_do_cmd(pt_help_tip->h_text,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* set text font*/
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    if(pt_help_tip->font_name != NULL)
    {
        c_strcpy(t_fnt_info.a_c_font_name, pt_help_tip->font_name);
    }
    else
    {
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    }

    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (pt_help_tip->h_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* set text color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    =t_g_help_tip_txt_color;
    t_clr_info.u_color_data.t_standard.t_highlight =t_g_help_tip_txt_color;
    t_clr_info.u_color_data.t_standard.t_disable   =t_g_help_tip_txt_color;
    i4_ret = c_wgl_do_cmd(pt_help_tip->h_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    =t_g_help_tip_bk_color;
    t_clr_info.u_color_data.t_standard.t_highlight =t_g_help_tip_bk_color;
    t_clr_info.u_color_data.t_standard.t_disable   =t_g_help_tip_bk_color;
    i4_ret = c_wgl_do_cmd(pt_help_tip->h_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* set text allignment */
    i4_ret = c_wgl_do_cmd(pt_help_tip->h_text,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(HELP_TIP_TXT_ALLIGN),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* Set the correct visibility for child widgets */
    c_wgl_set_visibility(pt_help_tip->h_text, WGL_SW_HIDE);

    /* Hide the main frame at initial time */
    c_wgl_set_visibility(pt_help_tip->h_frame, WGL_SW_HIDE);

    return HELP_TIPR_OK;



}

/*-----------------------------------------------------------------------------
                    public function definition
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: a_help_tip_init
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
INT32 a_help_tip_init(HELP_TIP_INIT_T*  pt_help_tip_init,   /* Input  */
                      HANDLE_T*         ph_help_tip)        /* Output */

{
    INT32           i4_ret;
    GL_RECT_T       t_rect = {0};
    _HELP_TIP_T*    pt_help_tip;
    if (a_is_oled_compensation_support())
    {
        t_g_help_tip_txt_color = t_g_help_tip_txt_color_oled;
    }
    pt_help_tip =(_HELP_TIP_T*)c_mem_alloc(sizeof(_HELP_TIP_T));

    if(pt_help_tip == NULL)
    {
        return HELP_TIPR_OUT_OF_MEM;
    }
    c_memset(pt_help_tip,0 , sizeof(_HELP_TIP_T));

    do {
        /* create frm */
        i4_ret = c_wgl_create_widget(pt_help_tip_init->h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     &pt_help_tip_init->t_frame_rect,
                                     NULL,
                                     255,
                                     (VOID*)0,
                                     NULL,
                                     &pt_help_tip->h_frame);
        if(i4_ret < 0)
        {
            break;
        }

        /* create multiline text controler */
        t_rect.i4_top    = 0;
        t_rect.i4_left   = FRAME_LEFT_RIGHT_INTV;
        t_rect.i4_right  = HELP_TIP_FRAME_W-FRAME_LEFT_RIGHT_INTV;
        t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

        i4_ret = c_wgl_create_widget(pt_help_tip->h_frame,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE|WGL_STL_TEXT_MAX_512),
                                     NULL,
                                     &pt_help_tip->h_text);
        if(i4_ret < 0)
        {
            break;
        }


#if NEW_TIP

        INT32 i4_icon_top = pt_help_tip_init->t_frame_rect.i4_bottom - pt_help_tip_init->t_frame_rect.i4_top - 40;
        INT32 i4_icon_bottom = i4_icon_top + 34;

        t_rect.i4_left   = HELP_TIP_ICON_BLUE_LEFT;
        t_rect.i4_top    = i4_icon_top;
        t_rect.i4_right  = HELP_TIP_ICON_BLUE_RIGHT;
        t_rect.i4_bottom = i4_icon_bottom;

        i4_ret = c_wgl_create_widget(pt_help_tip->h_frame,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(0),
                                     NULL,
                                     &pt_help_tip->h_icon_blue);
        if(i4_ret < 0)
        {
            break;
        }


        t_rect.i4_left   = HELP_TIP_ICON_RED_LEFT;
        t_rect.i4_top    = i4_icon_top;
        t_rect.i4_right  = HELP_TIP_ICON_RED_RIGHT;
        t_rect.i4_bottom = i4_icon_bottom;

        i4_ret = c_wgl_create_widget(pt_help_tip->h_frame,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(0),
                                     NULL,
                                     &pt_help_tip->h_icon_green);
        if(i4_ret < 0)
        {
            break;
        }

#endif


        /* create a timer */
        i4_ret = c_timer_create(&pt_help_tip->h_timer);
        if(i4_ret < 0)
        {
            break;
        }
    }while(0);

    /* release the resource if create fail */
    if(i4_ret < 0)
    {
        /* destroy timer */
        if(pt_help_tip->h_timer != NULL_HANDLE)
        {
            c_timer_delete(pt_help_tip->h_timer);
        }

#if NEW_TIP
        /* destroy Icons */
        if(pt_help_tip->h_icon_blue != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_help_tip->h_icon_blue);
        }

        if(pt_help_tip->h_icon_green != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_help_tip->h_icon_green);
        }


#endif
        /* destroy text controler */
        if(pt_help_tip->h_text != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_help_tip->h_text);
        }

        /* destroy frm */
        if(pt_help_tip->h_frame!= NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_help_tip->h_frame);
        }

        c_mem_free(pt_help_tip);

        return HELP_TIPR_FAIL;
    }

    /* init other data */
    pt_help_tip->font_name = pt_help_tip_init->font_name;
    pt_help_tip->pf_timeout_notify = pt_help_tip_init->pf_timeout_notify;

    i4_ret = c_wgl_do_cmd(pt_help_tip->h_frame,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* set help tip theme */
    i4_ret = _help_tip_set_theme(pt_help_tip->h_frame);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    *ph_help_tip = pt_help_tip->h_frame;

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_deinit
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
INT32 a_help_tip_deinit(HANDLE_T  h_help_tip)
{

    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* destroy timer */
    if(pt_help_tip->h_timer != NULL_HANDLE)
    {
        c_timer_delete(pt_help_tip->h_timer);
    }

    /* destroy text controler */
    if(pt_help_tip->h_text != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_help_tip->h_text);
    }

    /* destroy frm */
    if(pt_help_tip->h_frame!= NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_help_tip->h_frame);
    }

    c_mem_free(pt_help_tip);

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_set_info
 *
 * Description: set help infomation and trigger help tip timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_help_tip_set_info(HANDLE_T    h_help_tip,
                          UTF16_T*    w2s_text)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* set text */
    c_memset(w2s_help_txt_last, 0, sizeof(w2s_help_txt_last));

    i4_ret = c_wgl_do_cmd(pt_help_tip->h_text,
                          WGL_CMD_TEXT_GET_TEXT,
                          (VOID*)w2s_help_txt_last,
                          (VOID*)HELP_TIP_LAST_TXT_LEN);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    if (_help_tip_text_add_dot(pt_help_tip->h_text, w2s_text))
    {
        return HELP_TIPR_OK;
    }

	/* Set Font */
	WGL_FONT_INFO_T 	t_fnt_info;
	c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
	c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
	t_fnt_info.e_font_size	= TITLE_FONT_SIZE;
	t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	t_fnt_info.e_font_cmap	= FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size = 17;

	i4_ret = c_wgl_do_cmd (pt_help_tip->h_text,
					   WGL_CMD_GL_SET_FONT,
					   WGL_PACK(&t_fnt_info),
					   NULL);

    if(i4_ret < 0)
    {
		DBG_LOG_PRINT(("Set Help Tip font size fail i4_ret: %d\r\n", i4_ret));
    }
    /* set text */
    i4_ret = c_wgl_do_cmd(pt_help_tip->h_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)w2s_text,
                          (VOID*)512);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_trigger
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
INT32 a_help_tip_trigger(HANDLE_T h_help_tip)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* start timer */
    c_timer_start(pt_help_tip->h_timer,
                  HELP_TIP_TIMEOUT,
                  X_TIMER_FLAG_ONCE,
                  pt_help_tip->pf_timeout_notify,
                  NULL);

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_show
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
INT32 a_help_tip_show(HANDLE_T    h_help_tip)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_help_tip->h_text, WGL_SW_NORMAL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* show help tip */
    i4_ret = c_wgl_set_visibility(pt_help_tip->h_frame, WGL_SW_NORMAL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_help_tip->h_frame, NULL, TRUE);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_hide
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
INT32 a_help_tip_hide(HANDLE_T h_help_tip)
{

#if NEW_TIP

    /* for menu anamation help tip should be hidden with menu.*/
    return HELP_TIPR_OK;

#else

    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;



    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

     /* hide help tip */
    i4_ret = c_wgl_set_visibility(pt_help_tip->h_frame, WGL_SW_HIDE);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_help_tip->h_frame, NULL, TRUE);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_timer_stop(pt_help_tip->h_timer);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    return HELP_TIPR_OK;

#endif

}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_move
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
INT32 a_help_tip_move (
    HANDLE_T            h_help_tip ,
    GL_RECT_T*          pt_rect,
    BOOL                b_repaint
    )
{
    INT32                 i4_ret;
    _HELP_TIP_T*          pt_help_tip;


    if (!pt_rect)
    {
        return HELP_TIPR_FAIL ;
    }

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL) ;
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* move frame */
    i4_ret = c_wgl_move(pt_help_tip->h_frame, pt_rect, FALSE) ;
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* move text */
    pt_rect->i4_right  = pt_rect->i4_right  - pt_rect->i4_left;
    pt_rect->i4_bottom = pt_rect->i4_bottom - pt_rect->i4_top ;
    pt_rect->i4_left   = 0 ;
    pt_rect->i4_top    = 0 ;
    i4_ret = c_wgl_move(pt_help_tip->h_text , pt_rect, b_repaint) ;
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_show_help
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
INT32 a_help_tip_show_help(HANDLE_T    h_help_tip)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }
    c_wgl_set_visibility(pt_help_tip->h_frame,WGL_SW_NORMAL);
    /* show help tip */
    i4_ret = c_wgl_set_visibility(pt_help_tip->h_text, WGL_SW_NORMAL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_help_tip->h_text, NULL, TRUE);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_hide_help
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
INT32 a_help_tip_hide_help(HANDLE_T h_help_tip)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }
    c_wgl_set_visibility(pt_help_tip->h_frame,WGL_SW_HIDE);
    /* hide help tip text */
    i4_ret = c_wgl_set_visibility(pt_help_tip->h_text, WGL_SW_HIDE);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_help_tip->h_text, NULL, TRUE);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_timer_stop(pt_help_tip->h_timer);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_keytip_show
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
INT32 a_help_tip_set_focus(HANDLE_T h_help_tip,
                        HANDLE_T h_focus,
                        UINT16 ui2_idx,
                        BOOL b_repaint)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_help_tip->h_frame,FALSE);
    HELP_TIP_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_help_tip->h_frame, NULL, TRUE);
        HELP_TIP_LOG_ON_FAIL(i4_ret);
    }

#if NEW_TIP
    switch (ui2_idx)
    {
        case 2:
            if(NULL_HANDLE==h_focus)
            {
                h_handle_last  = pt_help_tip->h_icon_blue;
            }
            else
            {
                h_handle_last=h_focus;
            }
            i4_ret = c_wgl_set_focus(pt_help_tip->h_icon_blue,FALSE);
            pt_help_tip->ui1_focus_icon_idx = 2;
            if(i4_ret < 0)
            {
                return HELP_TIPR_FAIL;
            }
            break;

        case 3:
        default:
            if(NULL_HANDLE==h_focus)
            {
                h_handle_last  = pt_help_tip->h_icon_blue;
            }
            else
            {
                h_handle_last=h_focus;
            }
            i4_ret = c_wgl_set_focus(pt_help_tip->h_icon_blue,FALSE);
            pt_help_tip->ui1_focus_icon_idx = 2;

            if(i4_ret < 0)
            {
                return HELP_TIPR_FAIL;
            }
            break;
    }


    if(b_repaint)
    {

        i4_ret = c_wgl_repaint(pt_help_tip->h_icon_blue, NULL, TRUE);
        if(i4_ret < 0)
        {
            return HELP_TIPR_FAIL;
        }


        i4_ret = c_wgl_repaint(pt_help_tip->h_icon_green, NULL, TRUE);
        if(i4_ret < 0)
        {
            return HELP_TIPR_FAIL;
        }

    }

#endif

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_set_proc
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
INT32 a_help_tip_set_proc(HANDLE_T h_help_tip,
                       wgl_widget_proc_fct pf_proc_1,
                       wgl_widget_proc_fct pf_proc_2)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    if(NULL_HANDLE==h_help_tip)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

#if NEW_TIP

    if(NULL==pf_proc_1)
    {
        i4_ret = c_wgl_set_widget_proc(pt_help_tip->h_icon_blue, _btn_proc_fct);
        i4_ret = c_wgl_set_widget_proc(pt_help_tip->h_icon_green, _btn_proc_fct);
    }
    else
    {
        i4_ret = c_wgl_set_widget_proc(pt_help_tip->h_icon_blue, pf_proc_1);
        i4_ret = c_wgl_set_widget_proc(pt_help_tip->h_icon_green, pf_proc_1);
    }
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }


#endif

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_keytip_show
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
INT32 a_help_tip_keytip_show(HANDLE_T h_help_tip, BOOL b_show)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }


    return HELP_TIPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: a_help_tip_change_lang
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
INT32 a_help_tip_change_lang(HANDLE_T    h_help_tip,
                             UTF16_T*    w2s_last,
                             UTF16_T*    w2s_exit)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_show
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
INT32 a_help_tip_visible(HANDLE_T h_help_tip)
{
    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    /* show help tip */
    i4_ret = c_wgl_set_visibility(pt_help_tip->h_frame, WGL_SW_NORMAL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    i4_ret = c_timer_stop(pt_help_tip->h_timer);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }
#if 0
    pt_help_tip->b_showed = TRUE;
#endif
    return HELP_TIPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_help_tip_get_focus_icon_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:   0:error, 1: yellow_icon, 2:blue_icon, 3:green_icon,4:red_icon,
 *
 ----------------------------------------------------------------------------*/
UINT8 a_help_tip_get_focus_icon_idx(HANDLE_T h_help_tip)
{

    INT32                   i4_ret;
    _HELP_TIP_T*            pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return 0;
    }

    return pt_help_tip->ui1_focus_icon_idx;

}
/*----------------------------------------------------------------------------
 * Name: a_help_tip_get_focus_last
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
HANDLE_T a_help_tip_get_focus_last(VOID)
{
    return h_handle_last;
}

VOID a_help_tip_set_last_txt(const UTF16_T * w2s_src)
{
    c_memset(w2s_help_txt_last, 0, sizeof(w2s_help_txt_last));
    c_uc_w2s_strncpy(w2s_help_txt_last, w2s_src, HELP_TIP_LAST_TXT_LEN);
}

UTF16_T * a_help_tip_get_last_txt(VOID)
{
    return w2s_help_txt_last;
}

BOOL a_help_tip_get_focus(HANDLE_T h_help_tip)
{
    INT32       i4_ret = HELP_TIPR_OK;
    HANDLE_T    h_focus = NULL_HANDLE;
    _HELP_TIP_T* pt_help_tip;

    i4_ret = c_wgl_get_focus(&h_focus);
    if (i4_ret != WGLR_OK)
    {
        return FALSE;
    }

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return FALSE;
    }

    if (h_focus == pt_help_tip->h_frame
        || h_focus == pt_help_tip->h_icon_blue
        || h_focus == pt_help_tip->h_icon_green
        || h_focus == pt_help_tip->h_icon_red
        || h_focus == pt_help_tip->h_text)
    {
        return TRUE;
    }

    return FALSE;
}

#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
INT32 a_menu_set_help_tip_enable_status(HANDLE_T h_help_tip, BOOL b_status)
{
    INT32       i4_ret = HELP_TIPR_OK;
    _HELP_TIP_T* pt_help_tip;

    i4_ret = c_wgl_do_cmd(h_help_tip,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_help_tip),
                          NULL);
    if(i4_ret < 0)
    {
        return HELP_TIPR_FAIL;
    }

    c_wgl_enable( pt_help_tip->h_icon_blue,b_status);

    return HELP_TIPR_OK;
}
#endif

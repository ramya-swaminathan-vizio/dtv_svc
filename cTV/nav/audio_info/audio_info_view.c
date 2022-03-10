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
 * $RCSfile: audio_info_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "res/nav/nav_variant.h"

#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "nav/audio_info/audio_info.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/audio_info/audio_info_view_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                          TRUE

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
AUDIO_INFO_VIEW_T t_g_audio_info_view;
static WGL_FONT_INFO_T   t_font_info    = {FE_FNT_SIZE_MEDIUM,  FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
static GL_COLOR_T        t_g_text_color = AUDIO_INFO_FG_COLOR;
#ifdef APP_NAV_AI_MONO_COMBINED_STEREO_SUPPORT
static UTF16_T*          pw2s_g_plus                                    = (UTF16_T*) L"+";
#endif
static UTF16_T           w2s_g_space[]                                  = {0x0020, 0};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_frame_skin(
                    APP_COLOR_TYPE_T            e_color_type
                    );
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name:
 * Description: create image handle
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_info_view_create_image(VOID)
{
    INT32    i4_ret;
    AUDIO_INFO_VIEW_T* pt_view = &t_g_audio_info_view;

    /* dialog background image */
    i4_ret = nav_audio_info_view_custom_create_image(&pt_view->h_img_bk);

    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _audio_info_frame_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_frame_skin(
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    AUDIO_INFO_VIEW_T* pt_view = &t_g_audio_info_view;
    WGL_COLOR_INFO_T t_clr_info;
    INT32            i4_ret;
    WGL_IMG_INFO_T   t_img_info;

    /* Frame's background */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_img_bk;

    i4_ret = c_wgl_do_cmd (pt_view->h_frame,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    if (WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set message color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_text_color;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_text_color;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_text_color;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set title font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* set title align*/
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _audio_info_view_get_crnt_lang_str
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static UTF16_T* _audio_info_view_get_crnt_lang_str(
                    SCDB_REC_T*         pt_scdb_rec,
                    UTF16_T*            w2s_lang_string,
                    SIZE_T              z_str_len,
                    BOOL*               pb_fake_stereo
                    )

{
    INT32       i4_ret;
    CHAR*       ps_audio_lang   = pt_scdb_rec->u.t_audio_mpeg.s_lang;
    UTF16_T*    pw2s_audio_lang = nav_get_display_lang((const ISO_639_LANG_T*)ps_audio_lang);
#ifdef APP_NAV_AI_MONO_COMBINED_STEREO_SUPPORT
    UTF16_T             w2s_lang_buf[3+1] = {0};
    TV_WIN_ID_T         e_tv_win_id;
    HANDLE_T            h_svctx;
    UTF16_T*            pw2s_dual_1_lang = NULL;
    UTF16_T*            pw2s_dual_2_lang = NULL;
    SIZE_T              z_dual_1_lang = 0;
    SIZE_T              z_dual_2_lang = 0;
    NAV_AUD_COMBINED_STEREO_INFO_T  t_aud_lang_info = {0};
#endif

    *pb_fake_stereo = FALSE;

#ifdef APP_NAV_AI_MONO_COMBINED_STEREO_SUPPORT
    do {
        if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG &&
            pt_scdb_rec->u.t_audio_mpeg.ui1_index == 2 &&  /* index of fake stereo */
            pt_scdb_rec->u.t_audio_mpeg.e_aud_fmt == AUD_FMT_DUAL_MONO &&
            pt_scdb_rec->u.t_audio_mpeg.s_lang[0] == '\0')
        {
            *pb_fake_stereo = TRUE;

            i4_ret = nav_get_focus_id(&e_tv_win_id);
            if (NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s():nav_get_focus_id(), ret = %d\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
            if (NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s():nav_get_svctx_handle(), ret = %d\r\n", __FUNCTION__, i4_ret));
                break;
            }

            t_aud_lang_info.pt_scdb_rec = pt_scdb_rec;
            i4_ret = audio_info_get_combined_stereo_info(&t_aud_lang_info);
            if (NAVR_OK != i4_ret)
            {
                DBG_ERROR((_ERROR_HEADER"%s():c_svctx_get_stream_comp_id(), ret = %d\r\n", __FUNCTION__, i4_ret));
                break;
            }

            /* Get Dual mono 1 audio lang unicode string */
            if (t_aud_lang_info.b_dual_1_valid == TRUE)
            {
                pw2s_dual_1_lang = nav_get_display_lang((const ISO_639_LANG_T*)t_aud_lang_info.s_dual_1_lang);
                z_dual_1_lang = c_uc_w2s_strlen(pw2s_dual_1_lang);
            }

            /* clean string buffer */
            c_memset(w2s_lang_string, 0, z_str_len);

            /* Merge dual1+dual2 lang string */
            /* Dual1 lang string */
            if(0 != z_dual_1_lang)
            {
                c_uc_w2s_strncat(w2s_lang_string, pw2s_dual_1_lang, z_dual_1_lang);
            }

            /* Get Dual mono 2 audio lang unicode string */
            if (t_aud_lang_info.b_dual_2_valid == TRUE &&
                c_strcmp(t_aud_lang_info.s_dual_1_lang ,t_aud_lang_info.s_dual_2_lang) != 0)
            {
                pw2s_dual_2_lang = nav_get_display_lang((const ISO_639_LANG_T*)t_aud_lang_info.s_dual_2_lang);
                z_dual_2_lang = c_uc_w2s_strlen(pw2s_dual_2_lang);
            }

            /* '+' character */
            if (z_dual_1_lang != 0 && z_dual_2_lang != 0)
            {
                c_uc_w2s_strcat(w2s_lang_string, pw2s_g_plus);
                z_dual_1_lang++;
            }
            /* Dual2 lang string */
            if(0 != z_dual_2_lang)
            {
                c_uc_w2s_strncat(w2s_lang_string,
                                 pw2s_dual_2_lang,
                                 z_str_len - z_dual_1_lang);
            }
            else if ('\0' != t_aud_lang_info.s_dual_2_lang[0] &&
                     c_strcmp(t_aud_lang_info.s_dual_1_lang ,t_aud_lang_info.s_dual_2_lang) != 0)
            {
                i4_ret = c_uc_ps_to_w2s(t_aud_lang_info.s_dual_2_lang, w2s_lang_buf, 3);
                if(UCR_OK == i4_ret)
                {
                    c_uc_w2s_strncat(w2s_lang_string,
                                     w2s_lang_buf,
                                     z_str_len - z_dual_1_lang);
                }
            }

            return w2s_lang_string;
        }
    } while (0);
#endif /* APP_NAV_AI_MONO_COMBINED_STEREO_SUPPORT */

    if(NULL != pw2s_audio_lang)
    {
        return pw2s_audio_lang;
    }
    else if (ps_audio_lang[0] != '\0' &&
             (ps_audio_lang[0] != ' ' ||
              ps_audio_lang[1] != ' ' ||
              ps_audio_lang[2] != ' ' ))
    {
        i4_ret = c_uc_ps_to_w2s(ps_audio_lang, w2s_lang_string, z_str_len);
        if(UCR_OK == i4_ret)
        {
            return w2s_lang_string;
        }
    }

    return NULL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_draw_audio_info_on_widget
 * Description
 *      It is not valid for Analog Audio
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 _audio_info_draw_digital_info_on_widget(
                    HANDLE_T                    h_widget,
                    ASH_AUDIO_INFO_T*           p_audio_info,
                    SCDB_REC_T*                 pt_scdb_rec,
                    UINT16                      ui2_order,
                    UINT16                      ui2_total_amount,
                    UINT32                      ui4_scrambled_strm
                    )
{
    UTF16_T     w2s_string[65]  = {0};
    UTF16_T     w2s_order_string[11+1] = {0};
    UTF16_T     w2s_lang_string[33] = {0};
    UTF16_T     *pw2s_lang = NULL, *pw2s_order = NULL;
    INT32       i4_ret;
    BOOL        b_fake_stereo;

    if(pt_scdb_rec == NULL || pt_scdb_rec->e_rec_type != SCDB_REC_TYPE_AUDIO_MPEG)
    {
        return NAVR_INV_ARG;
    }

    if(ui2_order > 0 && ui2_total_amount > 1)
    {
        CHAR    s_order_string[11+1]   = {0};

        if(ui2_total_amount < 100)
        {
            c_sprintf(s_order_string, AUD_ORDER_FMT_LONG, ui2_order, ui2_total_amount);
        }
        else
        {
            c_sprintf(s_order_string, AUD_ORDER_FMT_SHORT, ui2_order, ui2_total_amount);
        }

        i4_ret = c_uc_ps_to_w2s(s_order_string, w2s_order_string, 11);
        if(UCR_OK == i4_ret)
        {
            pw2s_order = w2s_order_string;
        }
    }

    pw2s_lang = _audio_info_view_get_crnt_lang_str(
                                        pt_scdb_rec,
                                        w2s_lang_string,
                                        sizeof(w2s_lang_string),
                                        &b_fake_stereo);

    /*audio order*/
    if(pw2s_order)
    {
        c_uc_w2s_strcat(w2s_string, pw2s_order);
        c_uc_w2s_strcat(w2s_string, w2s_g_space);
    }

    /*audio language*/
    if ((ui4_scrambled_strm & MAKE_BIT_MASK_32(ST_AUDIO)) > 0)
    {
        c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_ASCRAMBLED));
    }
    else
    {
        if(pw2s_lang != NULL && pw2s_lang[0] != L'\0')
        {
            c_uc_w2s_strcat(w2s_string, pw2s_lang);
        }
        else
        {
            c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_AUD_MTS_UNK));
        }
    }

    i4_ret = c_wgl_do_cmd(h_widget, WGL_CMD_TEXT_SET_TEXT, (VOID*)w2s_string, (VOID*)0xFFFF);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _audio_info_view_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _audio_info_view_frame_nfy_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    AUDIO_INFO_VIEW_T*  pt_view = &t_g_audio_info_view;
    INT32               i4_ret;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        UINT32      ui4_key_code = (UINT32) pv_param1;
        TV_WIN_ID_T e_tv_win_id  = TV_WIN_ID_MAIN;

        switch(ui4_key_code) {
        case BTN_MTS:
            /*[DTV00131133] [5362B] Pressing "MTS/Audio" causes system can't output audio.*/
            nav_enable_key_traffic_auto_ctrl(100);

            nav_get_focus_id(&e_tv_win_id);

            audio_info_key_handler(
                            pt_view->pt_ctrl,
                            e_tv_win_id,
                            ui4_key_code);
            break;
        default:
            nav_rcu_key_handler(ui4_key_code);
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
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_init(
                    AUDIO_INFO_T*               pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    AUDIO_INFO_VIEW_T* pt_view = &t_g_audio_info_view;
    INT32              i4_ret;
    GL_RECT_T          t_rect;

    pt_view->pt_ctrl = pt_this;

    /* create image */
    _audio_info_view_create_image();

    /* create frame */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    i4_frame_x_offset + AUDIO_INFO_FRAME_LEFT,
                    i4_frame_y_offset + AUDIO_INFO_FRAME_TOP,
                    AUDIO_INFO_FRAME_WIDTH,
                    AUDIO_INFO_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _audio_info_view_frame_nfy_fct,
                    DEFAULT_BK_ALPHA,
                    NULL,
                    NULL,
                    &(pt_view->h_frame)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* create message */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    AUDIO_INFO_MSG_LEFT,
                    AUDIO_INFO_MSG_TOP,
                    AUDIO_INFO_MSG_WIDTH,
                    AUDIO_INFO_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32
                          | WGL_STL_TEXT_SMART_CUT
                          | WGL_STL_GL_NO_IMG_UI
                          | WGL_STL_GL_NO_BK),
                    NULL,
                    &(pt_view->h_msg)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = _audio_info_frame_skin(
                    e_color_type
                    );
    if(NAVR_FAIL == i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_show(
                    pt_view->h_frame,
                    WGL_SW_HIDE
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_deinit(
                    VOID
                    )
{
    AUDIO_INFO_VIEW_T* pt_view = &t_g_audio_info_view;

    c_wgl_destroy_widget(pt_view->h_msg);
    c_wgl_destroy_widget(pt_view->h_frame);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_draw_digital
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_draw_digital(
                    ASH_AUDIO_INFO_T*           pt_audio_info,
                    SCDB_REC_T*                 pt_scdb_rec,
                    UINT16                      ui2_total_amount,
                    UINT16                      ui2_order,
                    UINT32                      ui4_scrambled_strm
                    )
{
    AUDIO_INFO_VIEW_T* pt_view = &t_g_audio_info_view;
    INT32 i4_ret;

    if (pt_scdb_rec == NULL){
        return NAVR_FAIL;
    }

    i4_ret = _audio_info_draw_digital_info_on_widget(
                    pt_view->h_msg,
                    pt_audio_info,
                    pt_scdb_rec,
                    ui2_order,
                    ui2_total_amount,
                    ui4_scrambled_strm
                    );

    return (i4_ret == NAVR_OK ? NAVR_OK : NAVR_FAIL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_draw_analog
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_draw_analog(
                    SCC_AUD_MTS_T               e_mts
                    )
{
    AUDIO_INFO_VIEW_T*  pt_view = &t_g_audio_info_view;
    INT32               i4_ret;
    UTF16_T*            pw2s_audio;

    /*audio mts*/
    pw2s_audio = nav_get_audio_mts_str(pt_view->pt_ctrl->e_crnt_mts);

    /*update widget*/
    i4_ret = c_wgl_do_cmd(pt_view->h_msg,
                      WGL_CMD_TEXT_SET_TEXT,
                      (VOID*)pw2s_audio,
                      (VOID*)0xFFFF);

    return (i4_ret == NAVR_OK ? NAVR_OK : NAVR_FAIL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_draw_no_feature
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_draw_no_feature(
                    VOID
                    )
{
    AUDIO_INFO_VIEW_T*  pt_view = &t_g_audio_info_view;
    INT32               i4_ret;

    /*update widget*/
    i4_ret = c_wgl_do_cmd(pt_view->h_msg,
                      WGL_CMD_TEXT_SET_TEXT,
                      (VOID*)MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                          MLM_NAV_KEY_MSG_NO_FEATURE),
                      (VOID*)0xFFFF);

    return (i4_ret == NAVR_OK ? NAVR_OK : NAVR_FAIL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_clean_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_clean_msg(
                    VOID
                    )
{
    AUDIO_INFO_VIEW_T*  pt_view = &t_g_audio_info_view;
    INT32               i4_ret;
    UTF16_T             w2s_empty[]={0};

    /*update widget*/
    i4_ret = c_wgl_do_cmd(pt_view->h_msg,
                      WGL_CMD_TEXT_SET_TEXT,
                      (VOID*)w2s_empty,
                      (VOID*)0xFFFF);

    return (i4_ret == NAVR_OK ? NAVR_OK : NAVR_FAIL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_show(
                    VOID
                    )
{
    AUDIO_INFO_VIEW_T* pt_view = &t_g_audio_info_view;
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_RECURSIVE
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_view->h_frame, FALSE);
    if (WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    nav_set_component_visible(NAV_COMP_ID_AUDIO_SEL);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      audio_info_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 audio_info_view_hide(
                    VOID
                    )
{
    AUDIO_INFO_VIEW_T* pt_view = &t_g_audio_info_view;
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_HIDE
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(
                    pt_view->h_frame,
                    NULL,
                    IS_SYNC_REPAINT
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

INT32 a_audio_info_get_audio_language(UTF16_T* pw2s_lang_string,UINT32 ui4_len)
{
    HANDLE_T         h_svctx = NULL_HANDLE;
    TV_WIN_ID_T      e_tv_win_id;
    SCDB_REC_T       t_scdb_rec;
    ASH_AUDIO_INFO_T t_audio_info;
    INT32            i4_ret;
    UINT16           ui2_total_amount;
    UINT16           ui2_order;
    //SI_SET_INFO_T    t_set_info;
    //STRM_REQ_TYPE_T  e_strm_req_type;
    UINT32           ui4_scrambled_strm = 0;
    SVL_REC_T        t_svl_rec;
    BOOL             b_is_digital = FALSE;
    //ASH_AUDIO_INFO_T            t_audio_ash;
    AUDIO_INFO_T*   pt_ctrl = t_g_audio_info_view.pt_ctrl;
    //ASH_CHANNELS_T             e_audio_channel = ASH_CHANNELS_UNKNOWN;



    c_memset(&t_scdb_rec, 0, sizeof(SCDB_REC_T));
    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));
    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    //c_memset(& t_audio_ash, 0, sizeof(ASH_AUDIO_INFO_T));

    if(pw2s_lang_string == NULL || ui4_len == 0)
    {
        return NAVR_FAIL;
    }

    //digital or ananlog

    i4_ret = nav_get_focus_id(&e_tv_win_id);
    if (NAVR_OK != i4_ret){
        DBG_WARN((_ERROR_HEADER"%s():nav_get_focus_id(), ret = %d\r\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

    i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
    if (NAVR_OK != i4_ret){
        DBG_WARN((_ERROR_HEADER"%s():nav_get_svctx_handle(), ret = %d\r\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

     /*update current svl info*/
    i4_ret= nav_get_svl_rec(e_tv_win_id, &t_svl_rec);
    if (NAVR_OK != i4_ret){
        DBG_WARN((_ERROR_HEADER"%s():nav_get_svl_rec(), ret = %d\r\n", __FUNCTION__, i4_ret));
        return i4_ret;
    }

    if(BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
    {
        b_is_digital = TRUE;
        DBG_WARN(("{audio_info} this is a digital channel\r\n"));
    }
    else
    {
        b_is_digital = FALSE;
        DBG_WARN(("{audio_info} this is a analog channel\r\n"));
    }

    if(pt_ctrl->at_grp[e_tv_win_id].b_is_digital != b_is_digital)
    {
        DBG_WARN(("{audio_info} digital or analog,it is not right..T-T\r\n"));
    }

    if(b_is_digital)
    {
        //get current scdb
        i4_ret = nav_get_crnt_audio_info(
                            e_tv_win_id,
                            &t_audio_info,
                            &t_scdb_rec,
                            &ui2_total_amount,
                            &ui2_order
                            );
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        i4_ret = nav_get_ca_status(e_tv_win_id, &ui4_scrambled_strm);
        if (i4_ret != NAVR_OK) {
            ui4_scrambled_strm = 0;
        }


        if( t_scdb_rec.e_rec_type != SCDB_REC_TYPE_AUDIO_MPEG)
        {
            return NAVR_INV_ARG;
        }

        UTF16_T     w2s_string[65]  = {0};//
        UTF16_T     w2s_order_string[11+1] = {0};//
        UTF16_T     w2s_lang_string[33] = {0};//
        UTF16_T     *pw2s_lang = NULL, *pw2s_order = NULL;
        BOOL        b_fake_stereo;

        if(ui2_order > 0 && ui2_total_amount > 1)
        {
            CHAR    s_order_string[11+1]   = {0};

            if(ui2_total_amount < 100)
            {
                c_sprintf(s_order_string, AUD_ORDER_FMT_LONG, ui2_order, ui2_total_amount);
            }
            else
            {
                c_sprintf(s_order_string, AUD_ORDER_FMT_SHORT, ui2_order, ui2_total_amount);
            }

            i4_ret = c_uc_ps_to_w2s(s_order_string, w2s_order_string, 11);
            if(UCR_OK == i4_ret)
            {
                pw2s_order = w2s_order_string;
            }
        }

        pw2s_lang = _audio_info_view_get_crnt_lang_str(
                                            &t_scdb_rec,
                                            w2s_lang_string,
                                            sizeof(w2s_lang_string),
                                            &b_fake_stereo);

        /*audio order*/
        if(pw2s_order)
        {
            c_uc_w2s_strcat(w2s_string, pw2s_order);
            c_uc_w2s_strcat(w2s_string, w2s_g_space);
        }

        /*audio language*/
        if ((ui4_scrambled_strm & MAKE_BIT_MASK_32(ST_AUDIO)) > 0)
        {
            c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_ASCRAMBLED));
        }
        else
        {
            if(pw2s_lang != NULL && pw2s_lang[0] != L'\0')
            {
                c_uc_w2s_strcat(w2s_string, pw2s_lang);
#if defined (HEARING_IMPARED_PROMPT_STR) && defined (VISUAL_IMPARED_PROMPT_STR)

                if(a_aud_is_hearing_impaired_audio(t_scdb_rec.u.t_audio_mpeg))
                {

                    UTF16_T     w2s_hi_string[7] = HEARING_IMPARED_PROMPT_STR;
                    DBG_INFO(("{audio info}  AUD_TYPE_HEARING_IMPAIRED...................\r\n"));
                    c_uc_w2s_strcat(w2s_string, w2s_hi_string);
                }
                else if(a_aud_is_visual_impaired_audio(t_scdb_rec.u.t_audio_mpeg))
                {

                    UTF16_T     w2s_vi_string[7] = VISUAL_IMPARED_PROMPT_STR;
                    DBG_INFO(("{audio info}  visual_impaired.................\r\n"));
                    c_uc_w2s_strcat(w2s_string, w2s_vi_string);
                }
#endif
            }
            else
            {
                c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_AUD_MTS_UNK));
            }
        }

        c_uc_w2s_strncpy(pw2s_lang_string,w2s_string,ui4_len);

    }
    else
    {
        UTF16_T*            pw2s_audio_temp ;
        SCC_AUD_MTS_T       e_crnt_mts = SCC_AUD_MTS_UNKNOWN;
        /*audio mts*/
        //pw2s_audio_temp = nav_get_audio_mts_str(pt_ctrl->e_crnt_mts);
    #ifdef VIZIO_PORTING
        c_scc_aud_get_mts(pt_ctrl->at_grp[TV_WIN_ID_MAIN].h_mts, &e_crnt_mts);
    #endif
        pw2s_audio_temp = nav_get_audio_mts_str(e_crnt_mts);
        c_uc_w2s_strncpy(pw2s_lang_string,pw2s_audio_temp,ui4_len);
    }

    return NAVR_OK;
}

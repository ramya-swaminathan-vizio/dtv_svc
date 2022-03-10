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
 * $RCSfile: menu_page_vchip.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/15 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 61cb1377f1f69246c9ac07177bb76767 $
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

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "u_sb_atsc_eng.h"

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_dbg.h"

#ifdef ATSC_VCHIP_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#if (GRID_H == CONTENT_H/10)
    #define     GRID_Y_OFFSET  (0)         /* For the content frame that has 10 rows */
#else
    #define     GRID_Y_OFFSET  (-1)        /* For the content frame that has lower than 10 rows */
#endif

#define     VCHIP_IDX_BL 0
#define     VCHIP_IDX_MR 1
#define     VCHIP_IDX_TR 2
#define     VCHIP_IDX_BU 9
#define     VCHIP_ITEM_NUM 10

#define     VCHIP_ELEM_BL  5
#define     VCHIP_ELEM_MR  7
#define     VCHIP_ELEM_BU  2

/* TV Rating */
#define     COL_A   0
#define     COL_D   1
#define     COL_L   2
#define     COL_S   3
#define     COL_V   4
#define     COL_FV  5

#define     ROW_Y   0
#define     ROW_Y7  1
#define     ROW_G   2
#define     ROW_PG  3
#define     ROW_14  4
#define     ROW_MA  5

#define     TV_GRID_X_A     4
#define     TV_GRID_X_D     5
#define     TV_GRID_X_L     6
#define     TV_GRID_X_S     7
#define     TV_GRID_X_V     8
#define     TV_GRID_X_FV    9

#define     TV_GRID_Y_A     1
#define     TV_GRID_Y_D     1
#define     TV_GRID_Y_L     1
#define     TV_GRID_Y_S     1
#define     TV_GRID_Y_V     1
#define     TV_GRID_Y_FV    1

#define     TV_GRID_X_TV_Y      1
#define     TV_GRID_X_TV_Y7     1
#define     TV_GRID_X_TV_G      1
#define     TV_GRID_X_TV_PG     1
#define     TV_GRID_X_TV_14     1
#define     TV_GRID_X_TV_MA     1
#define     TV_GRID_X_TV_NONE   1

#define     TV_GRID_Y_TV_Y      2
#define     TV_GRID_Y_TV_Y7     3
#define     TV_GRID_Y_TV_G      4
#define     TV_GRID_Y_TV_PG     5
#define     TV_GRID_Y_TV_14     6
#define     TV_GRID_Y_TV_MA     7
#define     TV_GRID_Y_TV_NONE   8
/* --------- */

/* MPAA Rating */
#define     COL_MPAA         0

#define     ROW_MPAA_G       0
#define     ROW_MPAA_PG      1
#define     ROW_MPAA_PG_13   2
#define     ROW_MPAA_R       3
#define     ROW_MPAA_NC_17   4
#define     ROW_MPAA_X       5

#define     TV_GRID_X_MPAA   13
#define     TV_GRID_Y_MPAA   1

#define     TV_GRID_X_G      11
#define     TV_GRID_X_PG     11
#define     TV_GRID_X_PG_13  11
#define     TV_GRID_X_R      11
#define     TV_GRID_X_NC_17  11
#define     TV_GRID_X_X      11
#define     TV_GRID_X_NONE   11

#define     TV_GRID_Y_G      2
#define     TV_GRID_Y_PG     3
#define     TV_GRID_Y_PG_13  4
#define     TV_GRID_Y_R      5
#define     TV_GRID_Y_NC_17  6
#define     TV_GRID_Y_X      7
#define     TV_GRID_Y_NONE   8

/* ----------- */

#define     TV_CB_START_X      4
#define     TV_CB_START_Y      2
#define     MPAA_CB_START_X    13
#define     MPAA_CB_START_Y    2


#define     H_CB_TV_Y      aah_cb_tr[0][0]
#define     H_CB_TV_Y7     aah_cb_tr[1][0]
#define     H_CB_TV_Y7_FV  aah_cb_tr[1][5]

#define     H_CB_TV_G      aah_cb_tr[2][0]
#define     H_CB_TV_PG     aah_cb_tr[3][0]
#define     H_CB_TV_PG_D   aah_cb_tr[3][1]
#define     H_CB_TV_PG_L   aah_cb_tr[3][2]
#define     H_CB_TV_PG_S   aah_cb_tr[3][3]
#define     H_CB_TV_PG_V   aah_cb_tr[3][4]

#define     H_CB_TV_14     aah_cb_tr[4][0]
#define     H_CB_TV_14_D   aah_cb_tr[4][1]
#define     H_CB_TV_14_L   aah_cb_tr[4][2]
#define     H_CB_TV_14_S   aah_cb_tr[4][3]
#define     H_CB_TV_14_V   aah_cb_tr[4][4]

#define     H_CB_TV_MA     aah_cb_tr[5][0]
#define     H_CB_TV_MA_L   aah_cb_tr[5][2]
#define     H_CB_TV_MA_S   aah_cb_tr[5][3]
#define     H_CB_TV_MA_V   aah_cb_tr[5][4]

#define     H_CB_TV_NONE   aah_cb_tr[6][0]


#define     H_CB_MPAA_G      ah_cb_mpaa[0]
#define     H_CB_MPAA_PG     ah_cb_mpaa[1]
#define     H_CB_MPAA_PG_13  ah_cb_mpaa[2]
#define     H_CB_MPAA_R      ah_cb_mpaa[3]
#define     H_CB_MPAA_NC_17  ah_cb_mpaa[4]
#define     H_CB_MPAA_X      ah_cb_mpaa[5]
#define     H_CB_MPAA_NONE   ah_cb_mpaa[6]

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip;

static UTF16_T w2s_col_0[] = {0x0041, 0};          /* A */
static UTF16_T w2s_col_1[] = {0x0044, 0};          /* D */
static UTF16_T w2s_col_2[] = {0x004C, 0};          /* L */
static UTF16_T w2s_col_3[] = {0x0053, 0};          /* S */
static UTF16_T w2s_col_4[] = {0x0056, 0};          /* V */
static UTF16_T w2s_col_5[] = {0x0046, 0x0056, 0};  /* FV */

static UTF16_T w2s_row_0[] = {0x0054, 0x0056, 0x002D, 0x0059, 0};              /* TV-Y  */
static UTF16_T w2s_row_1[] = {0x0054, 0x0056, 0x002D, 0x0059, 0x0037, 0};      /* TV-Y7 */
static UTF16_T w2s_row_2[] = {0x0054, 0x0056, 0x002D, 0x0047, 0};              /* TV-G  */
static UTF16_T w2s_row_3[] = {0x0054, 0x0056, 0x002D, 0x0050, 0x0047, 0};      /* TV-PG */
static UTF16_T w2s_row_4[] = {0x0054, 0x0056, 0x002D, 0x0031, 0x0034, 0};      /* TV-14 */
static UTF16_T w2s_row_5[] = {0x0054, 0x0056, 0x002D, 0x004D, 0x0041, 0};      /* TV-MA */
static UTF16_T w2s_row_6[] = {0x0054, 0x0056, 0x002D, 0x004E, 0x004F, 0x004E, 0x0045, 0};   /* TV-NONE */

static UTF16_T w2s_col_0_mpaa[] = {0x004D, 0x0050, 0x0041, 0x0041, 0};         /* MPAA */

static UTF16_T w2s_row_0_mpaa[] = {0x0047, 0};                                 /* G */
static UTF16_T w2s_row_1_mpaa[] = {0x0050, 0x0047, 0};                         /* PG */
static UTF16_T w2s_row_2_mpaa[] = {0x0050, 0x0047, 0x002D, 0x0031, 0x0033, 0}; /* PG-13 */
static UTF16_T w2s_row_3_mpaa[] = {0x0052, 0};                                 /* R */
static UTF16_T w2s_row_4_mpaa[] = {0x004E, 0x0043, 0x002D, 0x0031, 0x0037, 0}; /* NC-17 */
static UTF16_T w2s_row_5_mpaa[] = {0x0058, 0};                                 /* X */
static UTF16_T w2s_row_6_mpaa[] = {0x004E, 0x002F, 0x0052, 0};                 /* N/R */


static HANDLE_T    h_cnt_frm;
static HANDLE_T    ah_txt_col[6];       /* For TV Rating */
static HANDLE_T    ah_txt_row[7];       /* For TV Rating */

static HANDLE_T    ah_txt_col_mpaa[1];  /* For MPAA */
static HANDLE_T    ah_txt_row_mpaa[7];  /* For MPAA */

static HANDLE_T    aah_cb_tr[7][7];
static BOOL        aab_locked[7][7];

static HANDLE_T    ah_cb_mpaa[7];           /* For MPAA */
static BOOL        ab_locked_mpaa[7];       /* For MPAA */

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _frm_proc_fct(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       param1,
                           VOID*       param2);

static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2);

/*----------------------------------------------------------------------------
 * Name: _create_col_title
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
static INT32 _create_col_title(INT32       i4_x_index,
                               INT32       i4_y_index,
                               INT32       i4_width,
                               UTF16_T*    w2s_str,
                               HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_txt;
    WGL_COLOR_INFO_T    t_clr_bk;
    WGL_FONT_INFO_T             t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     GRID_W * i4_x_index,
                     GRID_H * (i4_y_index+GRID_Y_OFFSET),
                     GRID_W * i4_width,
                     GRID_H);


    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_str,
                          (VOID*)c_uc_w2s_strlen(w2s_str));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_txt.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_txt.u_color_data.t_standard.t_enable       =t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_disable      =t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_bk.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_bk.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1;
    t_clr_bk.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_bk ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_row_title
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
static INT32 _create_row_title(INT32       i4_x_index,
                               INT32       i4_y_index,
                               INT32       i4_width,
                               UTF16_T*    w2s_str,
                               HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_FONT_INFO_T t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_txt;
    WGL_COLOR_INFO_T    t_clr_bk;

    SET_RECT_BY_SIZE(&t_rect,
                     GRID_W * i4_x_index,
                     GRID_H * (i4_y_index + GRID_Y_OFFSET),
                     GRID_W * i4_width,
                     GRID_H);

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_str,
                          (VOID*)c_uc_w2s_strlen(w2s_str));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set color */
    t_clr_txt.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_txt.u_color_data.t_standard.t_enable       =t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_disable      =t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
    MENU_CHK_FAIL(i4_ret);


    t_clr_bk.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_bk.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1;
    t_clr_bk.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_bk ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_cb
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
static INT32 _create_cb(INT32       i4_x,
                        INT32       i4_y,
                        INT32       i4_start_x,
                        INT32       i4_start_y,
                        HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_IMG_INFO_T  t_img_info;
    WGL_COLOR_INFO_T    t_clr_bk;

    SET_RECT_BY_SIZE(&t_rect,
                     GRID_W * (i4_start_x + i4_x),
                     GRID_H * (i4_start_y + i4_y + GRID_Y_OFFSET) ,
                     GRID_W,
                     GRID_H);

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _widgets_proc_fct,
                                 255,
                                 (void*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_BTN_CHECKBOX),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set color */
    t_clr_bk.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_bk.u_color_data.t_extend.t_enable     =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_extend.t_disable    =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_extend.t_highlight  =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_extend.t_highlight_inactive =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_extend.t_push               =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_extend.t_push_unhighlight   =t_g_menu_color_transp;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_bk ));
    MENU_CHK_FAIL(i4_ret);


    /* set image */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable = h_g_menu_img_unlock;
    t_img_info.u_img_data.t_extend.t_disable = h_g_menu_img_unlock;
    t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_img_unlock_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_unlock_hlt;
    t_img_info.u_img_data.t_extend.t_push = h_g_menu_img_lock_hlt;
    t_img_info.u_img_data.t_extend.t_push_unhighlight = h_g_menu_img_lock;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) );
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _set_nav
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
static INT32 _set_nav(VOID)
{
    WGL_KEY_LINK_T        at_key_lnk[4];
    INT32                i4_ret;
    INT32               i4_map_len = 12;
    INT32               i4_i = 0;
    INT32               i4_j = 0;
    INT32               i4_k = 0;
    HANDLE_T            aah_map[12][5]; /* used for micro control */

    /*
    ah_chain[i4_chain_len++] = h_lb_bl;
    ah_chain[i4_chain_len++] = h_lb_mr;
    ah_chain[i4_chain_len++] = H_CB_TV_Y;
    ah_chain[i4_chain_len++] = H_CB_TV_MA;
    ah_chain[i4_chain_len++] = h_lb_bu;
    */

    /* Set the navigation of main widgets of V-Chip page*/
    /*
    for (i4_i = 0; i4_i < i4_chain_len; i4_i++)
    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = ah_chain[i4_i == 0 ? i4_chain_len-1: i4_i-1];
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = ah_chain[i4_i == i4_chain_len-1 ? 0: i4_i+1];
        i4_ret = c_wgl_set_navigation(ah_chain[i4_i], 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);
    }
    */

    /* Set the navigation of tv rating*/
    for (i4_i = 0; i4_i < 6; i4_i++)
    {
        for (i4_j = 0; i4_j < 6; i4_j++)
        {
            if (aah_cb_tr[i4_i][i4_j] != NULL_HANDLE)
            {
                /* cursor up */
                for (i4_k = i4_i-1;
                    i4_k != -1 && aah_cb_tr[i4_k][i4_j]
                    == NULL_HANDLE;
                    i4_k = i4_k-1)
                {
                }
                if (i4_k == -1)
                {
                    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
                    at_key_lnk[0].h_widget = NULL_HANDLE;  /* h_lb_mr ==> NULL_HANDLE */
                }
                else
                {
                    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
                    at_key_lnk[0].h_widget = aah_cb_tr[i4_k][i4_j];
                }
                /* cursor down */
                for (i4_k = i4_i+1;
                    i4_k != 6 && aah_cb_tr[i4_k][i4_j]
                    == NULL_HANDLE;
                    i4_k = i4_k+1)
                {
                }
                if (i4_k == 6)
                {
                    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
                    at_key_lnk[1].h_widget = NULL_HANDLE;   /* h_lb_bu ==> NULL_HANDLE */
                }
                else
                {
                    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
                    at_key_lnk[1].h_widget = aah_cb_tr[i4_k][i4_j];
                }
                /* cursor left */
                for (i4_k = (i4_j-1 == -1 ? 5 : i4_j-1);
                    aah_cb_tr[i4_i][i4_k] == NULL_HANDLE;
                    i4_k = (i4_k-1 == -1 ? 5 : i4_k-1))
                {
                }
                at_key_lnk[2].ui4_key = BTN_CURSOR_LEFT;
                at_key_lnk[2].h_widget = aah_cb_tr[i4_i][i4_k];
                /* cursor right */
                for (i4_k = (i4_j+1 == 6 ? 0 : i4_j+1);
                    aah_cb_tr[i4_i][i4_k] == NULL_HANDLE;
                    i4_k = (i4_k+1 == 6 ? 0 : i4_k+1))
                {
                }
                at_key_lnk[3].ui4_key = BTN_CURSOR_RIGHT;
                at_key_lnk[3].h_widget = aah_cb_tr[i4_i][i4_k];
                /* Set navigation key */
                i4_ret = c_wgl_set_navigation(
                                             aah_cb_tr[i4_i][i4_j],
                                             4,
                                             at_key_lnk);
                MENU_CHK_FAIL(i4_ret);
            }
        }
    }


    /* Fine tune the navigation of tv rating*/
    i4_map_len = 6;
    aah_map[0][0] = H_CB_TV_PG_D;   /* widget to set navigation */
    aah_map[0][1] = H_CB_TV_Y7_FV;  /* up */
    aah_map[0][2] = H_CB_TV_14_D;   /* down */
    aah_map[0][3] = H_CB_TV_PG;     /* left */
    aah_map[0][4] = H_CB_TV_PG_L;   /* right */

    aah_map[1][0] = H_CB_TV_14_D;
    aah_map[1][1] = H_CB_TV_PG_D;
    aah_map[1][2] = H_CB_TV_MA;
    aah_map[1][3] = H_CB_TV_14;
    aah_map[1][4] = H_CB_TV_14_L;

    aah_map[2][0] = H_CB_TV_PG_L;
    aah_map[2][1] = H_CB_TV_Y7_FV;
    aah_map[2][2] = H_CB_TV_14_L;
    aah_map[2][3] = H_CB_TV_PG_D;
    aah_map[2][4] = H_CB_TV_PG_S;

    aah_map[3][0] = H_CB_TV_PG_S;
    aah_map[3][1] = H_CB_TV_Y7_FV;
    aah_map[3][2] = H_CB_TV_14_S;
    aah_map[3][3] = H_CB_TV_PG_L;
    aah_map[3][4] = H_CB_TV_PG_V;

    aah_map[4][0] = H_CB_TV_PG_V;
    aah_map[4][1] = H_CB_TV_Y7_FV;
    aah_map[4][2] = H_CB_TV_14_V;
    aah_map[4][3] = H_CB_TV_PG_S;
    aah_map[4][4] = H_CB_TV_PG;

    aah_map[5][0] = H_CB_TV_Y7_FV;
    aah_map[5][1] = H_CB_TV_Y;
    aah_map[5][2] = H_CB_TV_PG_V;
    aah_map[5][3] = H_CB_TV_Y7;
    aah_map[5][4] = H_CB_TV_Y7;

    for (i4_i = 0; i4_i < i4_map_len; i4_i++)
    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = aah_map[i4_i][1];
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = aah_map[i4_i][2];
        at_key_lnk[2].ui4_key = BTN_CURSOR_LEFT;
        at_key_lnk[2].h_widget = aah_map[i4_i][3];
        at_key_lnk[3].ui4_key = BTN_CURSOR_RIGHT;
        at_key_lnk[3].h_widget = aah_map[i4_i][4];
        i4_ret = c_wgl_set_navigation(aah_map[i4_i][0], 4, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);
    }

    /* Add additional navigation map (for supporting MPAA) */
    i4_map_len = 11;
    aah_map[0][0] = H_CB_TV_Y;      /* widget to set navigation */
    aah_map[0][1] = H_CB_TV_NONE;   /* up */
    aah_map[0][2] = H_CB_TV_Y7;     /* down */
    aah_map[0][3] = H_CB_MPAA_G;    /* left */
    aah_map[0][4] = H_CB_MPAA_G;    /* right */

    aah_map[1][0] = H_CB_TV_Y7;
    aah_map[1][1] = H_CB_TV_Y;
    aah_map[1][2] = H_CB_TV_G;
    aah_map[1][3] = H_CB_MPAA_PG;
    aah_map[1][4] = H_CB_TV_Y7_FV;

    aah_map[2][0] = H_CB_TV_Y7_FV;
    aah_map[2][1] = H_CB_TV_Y;
    aah_map[2][2] = H_CB_TV_G;
    aah_map[2][3] = H_CB_TV_Y7;
    aah_map[2][4] = H_CB_MPAA_PG;

    aah_map[3][0] = H_CB_TV_G;
    aah_map[3][1] = H_CB_TV_Y7;
    aah_map[3][2] = H_CB_TV_PG;
    aah_map[3][3] = H_CB_MPAA_PG_13;
    aah_map[3][4] = H_CB_MPAA_PG_13;

    aah_map[4][0] = H_CB_TV_PG;
    aah_map[4][1] = H_CB_TV_G;
    aah_map[4][2] = H_CB_TV_14;
    aah_map[4][3] = H_CB_MPAA_R;
    aah_map[4][4] = H_CB_TV_PG_D;

    aah_map[5][0] = H_CB_TV_14;
    aah_map[5][1] = H_CB_TV_PG;
    aah_map[5][2] = H_CB_TV_MA;
    aah_map[5][3] = H_CB_MPAA_NC_17;
    aah_map[5][4] = H_CB_TV_14_D;

    aah_map[6][0] = H_CB_TV_MA;
    aah_map[6][1] = H_CB_TV_14;
    aah_map[6][2] = H_CB_TV_NONE;
    aah_map[6][3] = H_CB_MPAA_X;
    aah_map[6][4] = H_CB_TV_MA_L;

    aah_map[7][0] = H_CB_TV_NONE;
    aah_map[7][1] = H_CB_TV_MA;
    aah_map[7][2] = H_CB_TV_Y;
    aah_map[7][3] = H_CB_MPAA_NONE;
    aah_map[7][4] = H_CB_MPAA_NONE;

    aah_map[8][0] = H_CB_TV_PG_V;
    aah_map[8][1] = H_CB_TV_Y7_FV;
    aah_map[8][2] = H_CB_TV_14_V;
    aah_map[8][3] = H_CB_TV_PG_S;
    aah_map[8][4] = H_CB_MPAA_R;

    aah_map[9][0] = H_CB_TV_14_V;
    aah_map[9][1] = H_CB_TV_PG_V;
    aah_map[9][2] = H_CB_TV_MA_V;
    aah_map[9][3] = H_CB_TV_14_S;
    aah_map[9][4] = H_CB_MPAA_NC_17;

    aah_map[10][0] = H_CB_TV_MA_V;
    aah_map[10][1] = H_CB_TV_14_V;
    aah_map[10][2] = H_CB_TV_NONE;
    aah_map[10][3] = H_CB_TV_MA_S;
    aah_map[10][4] = H_CB_MPAA_X;

    for (i4_i = 0; i4_i < i4_map_len; i4_i++)
    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = aah_map[i4_i][1];
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = aah_map[i4_i][2];
        at_key_lnk[2].ui4_key = BTN_CURSOR_LEFT;
        at_key_lnk[2].h_widget = aah_map[i4_i][3];
        at_key_lnk[3].ui4_key = BTN_CURSOR_RIGHT;
        at_key_lnk[3].h_widget = aah_map[i4_i][4];
        i4_ret = c_wgl_set_navigation(aah_map[i4_i][0], 4, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);
    }

    /* Add additional navigation map (for supporting MPAA) */
    i4_map_len = 9;
    aah_map[0][0] = H_CB_MPAA_G;      /* widget to set navigation */
    aah_map[0][1] = H_CB_MPAA_NONE;   /* up */
    aah_map[0][2] = H_CB_MPAA_PG;     /* down */
    aah_map[0][3] = H_CB_TV_Y;    /* left */
    aah_map[0][4] = H_CB_TV_Y;    /* right */

    aah_map[1][0] = H_CB_MPAA_PG;
    aah_map[1][1] = H_CB_MPAA_G;
    aah_map[1][2] = H_CB_MPAA_PG_13;
    aah_map[1][3] = H_CB_TV_Y7_FV;
    aah_map[1][4] = H_CB_TV_Y7;

    aah_map[2][0] = H_CB_MPAA_PG_13;
    aah_map[2][1] = H_CB_MPAA_PG;
    aah_map[2][2] = H_CB_MPAA_R;
    aah_map[2][3] = H_CB_TV_G;
    aah_map[2][4] = H_CB_TV_G;

    aah_map[3][0] = H_CB_MPAA_R;
    aah_map[3][1] = H_CB_MPAA_PG_13;
    aah_map[3][2] = H_CB_MPAA_NC_17;
    aah_map[3][3] = H_CB_TV_PG_V;
    aah_map[3][4] = H_CB_TV_PG;

    aah_map[4][0] = H_CB_MPAA_NC_17;
    aah_map[4][1] = H_CB_MPAA_R;
    aah_map[4][2] = H_CB_MPAA_X;
    aah_map[4][3] = H_CB_TV_14_V;
    aah_map[4][4] = H_CB_TV_14;

    aah_map[5][0] = H_CB_MPAA_X;
    aah_map[5][1] = H_CB_MPAA_NC_17;
    aah_map[5][2] = H_CB_MPAA_NONE;
    aah_map[5][3] = H_CB_TV_MA_V;
    aah_map[5][4] = H_CB_TV_MA;

    aah_map[6][0] = H_CB_MPAA_NONE;
    aah_map[6][1] = H_CB_MPAA_X;
    aah_map[6][2] = H_CB_MPAA_G;
    aah_map[6][3] = H_CB_TV_NONE;
    aah_map[6][4] = H_CB_TV_NONE;

    aah_map[7][0] = H_CB_TV_MA_L;
    aah_map[7][1] = H_CB_TV_14_L;
    aah_map[7][2] = H_CB_TV_NONE;
    aah_map[7][3] = H_CB_TV_MA;
    aah_map[7][4] = H_CB_TV_MA_S;

    aah_map[8][0] = H_CB_TV_MA_S;
    aah_map[8][1] = H_CB_TV_14_S;
    aah_map[8][2] = H_CB_TV_NONE;
    aah_map[8][3] = H_CB_TV_MA_L;
    aah_map[8][4] = H_CB_TV_MA_V;


    for (i4_i = 0; i4_i < i4_map_len; i4_i++)
    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = aah_map[i4_i][1];
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = aah_map[i4_i][2];
        at_key_lnk[2].ui4_key = BTN_CURSOR_LEFT;
        at_key_lnk[2].h_widget = aah_map[i4_i][3];
        at_key_lnk[3].ui4_key = BTN_CURSOR_RIGHT;
        at_key_lnk[3].h_widget = aah_map[i4_i][4];
        i4_ret = c_wgl_set_navigation(aah_map[i4_i][0], 4, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _chg_lang
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
static INT32 _chg_lang()
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lock_cb
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
static INT32 _lock_cb(UINT16 ui2_row,
                     UINT16 ui2_col,
                     BOOL b_lock)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(aah_cb_tr[ui2_row][ui2_col],
                          WGL_CMD_BTN_SET_PUSHED,
                          WGL_PACK(b_lock),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    aab_locked[ui2_row][ui2_col] = b_lock;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lock_cb
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
static INT32 _lock_mpaa_cb(UINT16 ui2_row,
                     BOOL b_lock)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(ah_cb_mpaa[ui2_row],
                          WGL_CMD_BTN_SET_PUSHED,
                          WGL_PACK(b_lock),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    ab_locked_mpaa[ui2_row] = b_lock;

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _unlock_age_based
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
static INT32 _unlock_age_based(UINT16 ui2_idx)
{
    INT32 i4_ret;
    UINT16 ui2_i = 0;
    UINT16 ui2_j = 0;

    for (ui2_i = 0; ui2_i <= ui2_idx; ui2_i++)
    {
        for (ui2_j = 0; ui2_j < 6; ui2_j++)
        {
            if (aah_cb_tr[ui2_i][ui2_j] != NULL_HANDLE &&
                aab_locked[ui2_i][ui2_j] == TRUE)
            {
                i4_ret = _lock_cb(ui2_i, ui2_j, FALSE);
                MENU_CHK_FAIL(i4_ret);
            }
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lock_age_based
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
static INT32 _lock_age_based(UINT16 ui2_idx)
{
    INT32 i4_ret;
    UINT16 ui2_i;
    UINT16 ui2_j;
    for (ui2_i = ui2_idx; ui2_i < 6; ui2_i++)
    {
        for (ui2_j = 0; ui2_j < 6; ui2_j++)
        {
            if (aah_cb_tr[ui2_i][ui2_j] != NULL_HANDLE &&
                aab_locked[ui2_i][ui2_j] == FALSE)
            {
                i4_ret = _lock_cb(ui2_i, ui2_j, TRUE);
                MENU_CHK_FAIL(i4_ret);
            }
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _unlock_age_based_mpaa
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
static INT32 _unlock_age_based_mpaa(UINT16 ui2_idx)
{
    INT32 i4_ret;
    UINT16 ui2_i = 0;

    for (ui2_i = 0; ui2_i <= ui2_idx; ui2_i++)
    {
        if (ah_cb_mpaa[ui2_i] != NULL_HANDLE &&
            ab_locked_mpaa[ui2_i] == TRUE)
        {
            i4_ret = _lock_mpaa_cb(ui2_i, FALSE);
            MENU_CHK_FAIL(i4_ret);
        }
    }

    return MENUR_OK;
}



/*----------------------------------------------------------------------------
 * Name: _lock_age_based_mpaa
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
static INT32 _lock_age_based_mpaa(UINT16 ui2_idx)
{
    INT32 i4_ret;
    UINT16 ui2_i;
    for (ui2_i = ui2_idx; ui2_i < 6; ui2_i++)
    {
        if (ah_cb_mpaa[ui2_i] != NULL_HANDLE &&
            ab_locked_mpaa[ui2_i] == FALSE)
        {
            i4_ret = _lock_mpaa_cb(ui2_i, TRUE);
            MENU_CHK_FAIL(i4_ret);
        }

    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _unlock_cnt_based
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
static INT32 _unlock_cnt_based(UINT16 ui2_row,
                              UINT16 ui2_col)
{
    INT32 i4_ret;
    UINT16 ui2_i;
    for (ui2_i = 0; ui2_i <= ui2_row; ui2_i++)
    {
        if (aah_cb_tr[ui2_i][ui2_col] != NULL_HANDLE &&
            aab_locked[ui2_i][ui2_col] == TRUE)
        {
            i4_ret = _lock_cb(ui2_i, ui2_col, FALSE);
            MENU_CHK_FAIL(i4_ret);
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lock_cnt_based
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
static INT32 _lock_cnt_based(UINT16 ui2_row,
                             UINT16 ui2_col)
{
    INT32 i4_ret;
    UINT16 ui2_i;
    for (ui2_i = ui2_row; ui2_i < 6; ui2_i++)
    {
        if (aah_cb_tr[ui2_i][ui2_col] != NULL_HANDLE &&
            aab_locked[ui2_i][ui2_col] == FALSE)
        {
            i4_ret = _lock_cb(ui2_i, ui2_col, TRUE);
            MENU_CHK_FAIL(i4_ret);
        }
    }
    return MENUR_OK;
}

static INT32 _set_vchip_settings()
{
    INT32   i4_ret;
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age = 0;
    UINT64  ui8_tv_cnt_map = 0;
    BOOL    b_bu_tr;
    BOOL    b_bu_mpaa;
    UINT8   ui1_i;

    /* MPAA's CB */
    ui1_mpaa = 0;
    if (  (ab_locked_mpaa[0] == FALSE) &&
          (ab_locked_mpaa[1] == FALSE) &&
          (ab_locked_mpaa[2] == FALSE) &&
          (ab_locked_mpaa[3] == FALSE) &&
          (ab_locked_mpaa[4] == FALSE) &&
          (ab_locked_mpaa[5] == FALSE) )
    {
       ui1_mpaa = APP_CFG_VCHIP_US_MPAA_OFF;
    }
    else
    {
       for(ui1_i = 0; ui1_i < 6; ui1_i++)
       {
           if(ab_locked_mpaa[ui1_i] == TRUE)
           {
               ui1_mpaa = ui1_i;
               break;  /* No further check */
           }
       }
    }


    /* TV AGE */
    for (ui1_i = 0;
        ui1_i < 6;
        ui1_i ++)
    {
        if (aab_locked[ui1_i][0])
        {
            ui1_tv_age = ui1_i;
            break;
        }
    }

    if (ui1_i == 6)
    {
        ui1_tv_age = APP_CFG_VCHIP_US_AGE_OFF;
    }

    /* TV CNT */
    if (aab_locked[ROW_Y7][COL_FV])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_Y7_FV;
    }

    if (aab_locked[ROW_PG][COL_D])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_D;
    }

    if (aab_locked[ROW_PG][COL_L])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_L;
    }

    if (aab_locked[ROW_PG][COL_S])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_S;
    }

    if (aab_locked[ROW_PG][COL_V])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_V;
    }

    if (aab_locked[ROW_14][COL_D])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_D;
    }

    if (aab_locked[ROW_14][COL_L])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_L;
    }

    if (aab_locked[ROW_14][COL_S])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_S;
    }

    if (aab_locked[ROW_14][COL_V])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_V;
    }

    if (aab_locked[ROW_MA][COL_L])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_L;
    }

    if (aab_locked[ROW_MA][COL_S])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_S;
    }

    if (aab_locked[ROW_MA][COL_V])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_V;
    }


    /* Block Unrated for TV Rating */
    b_bu_tr= aab_locked[6][0];

    /* Block Unrated for TV MPAA */
    b_bu_mpaa = ab_locked_mpaa[6];

    i4_ret = a_cfg_set_vchip_us(ui1_mpaa,
                                ui1_tv_age,
                                ui8_tv_cnt_map,
                                b_bu_mpaa,
                                b_bu_tr);
    if(i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }

    /*
    i4_ret = a_cfg_set_vchip_unrated(b_bu);
    if(i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }
    */

    return MENUR_OK;
}

static INT32 _get_vchip_settings()
{
    INT32   i4_ret;
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;
    BOOL    b_lock;
    UINT8   ui1_i;

    i4_ret = a_cfg_get_vchip_us(&ui1_mpaa,
                                &ui1_tv_age,
                                &ui8_tv_cnt_map,
                                &b_mpaa_bu,
                                &b_tv_bu);
    if(i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }

    /* MPAA's CB */
    if(ui1_mpaa == APP_CFG_VCHIP_US_MPAA_OFF) /* No block for everything */
    {
        for(ui1_i = 0 ; ui1_i < 6; ui1_i++)
        {
            _lock_mpaa_cb(ui1_i, FALSE);
        }
    }
    else
    {
        for(ui1_i = 0 ; ui1_i < 6; ui1_i++)   /* Block greater than setting */
        {
            if( ui1_i >= ui1_mpaa )
            {
                _lock_mpaa_cb(ui1_i, TRUE);
            }
            else
            {
                _lock_mpaa_cb(ui1_i, FALSE);
            }
        }
    }

    /* TV AGE */
    for (ui1_i = 0;
        ui1_i < 6;
        ui1_i ++)
    {
        if(ui1_i < ui1_tv_age)
        {
            _lock_cb(ui1_i, COL_A, FALSE);
        }
        else
        {
            _lock_cb(ui1_i, COL_A, TRUE);
        }
    }

    /* TV CNT */
    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_Y7_FV) != 0);
    _lock_cb(ROW_Y7, COL_FV, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_D) != 0);
    _lock_cb(ROW_PG, COL_D, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_L) != 0);
    _lock_cb(ROW_PG, COL_L, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_S) != 0);
    _lock_cb(ROW_PG, COL_S, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_V) != 0);
    _lock_cb(ROW_PG, COL_V, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_D) != 0);
    _lock_cb(ROW_14, COL_D, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_L) != 0);
    _lock_cb(ROW_14, COL_L, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_S) != 0);
    _lock_cb(ROW_14, COL_S, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_V) != 0);
    _lock_cb(ROW_14, COL_V, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_L) != 0);
    _lock_cb(ROW_MA, COL_L, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_S) != 0);
    _lock_cb(ROW_MA, COL_S, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_V) != 0);
    _lock_cb(ROW_MA, COL_V, b_lock);

    /* Block Unrated for MPAA */
    if(b_mpaa_bu)
    {
        _lock_mpaa_cb(6, TRUE);
    }
    else
    {
        _lock_mpaa_cb(6, FALSE);
    }

    /* Block Unrated for TV Rating */
    if(b_tv_bu)
    {
        _lock_cb(6, 0, TRUE);
    }
    else
    {
        _lock_cb(6, 0, FALSE);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _frm_proc_fct
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
static INT32 _frm_proc_fct(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       param1,
                           VOID*       param2)
{
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _widgets_proc_fct
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
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;
            case BTN_SELECT:
                {
                    UINT16 ui2_i = 0;
                    UINT16 ui2_j = 0;

                    /* In the MPAA's CB */
                    if( (h_widget == H_CB_MPAA_G)     ||
                        (h_widget == H_CB_MPAA_PG)    ||
                        (h_widget == H_CB_MPAA_PG_13) ||
                        (h_widget == H_CB_MPAA_R)     ||
                        (h_widget == H_CB_MPAA_NC_17) ||
                        (h_widget == H_CB_MPAA_X)     )

                    {
                        /* Search Widget Index */
                        for(ui2_i = 0 ; ui2_i < 6 ; ui2_i++)
                        {
                           if(ah_cb_mpaa[ui2_i] == h_widget)
                           {
                               if(ab_locked_mpaa[ui2_i] == TRUE)
                               {
                                   _unlock_age_based_mpaa(ui2_i);
                               }
                               else
                               {
                                   _lock_age_based_mpaa(ui2_i);
                               }
                           }
                        }
                        c_wgl_repaint(h_cnt_frm,NULL, TRUE);
                        _set_vchip_settings();
                        return WMPR_DONE;
                    }

                    /* In the MPAA's CB, [N/A] */
                    if( (h_widget == H_CB_MPAA_NONE) )
                    {
                        if(ab_locked_mpaa[6] == TRUE)
                        {
                            _lock_mpaa_cb(6, FALSE);    /* True to False */
                        }
                        else
                        {
                            _lock_mpaa_cb(6, TRUE);     /* False to True */
                        }

                        c_wgl_repaint(h_cnt_frm,NULL, TRUE);
                        _set_vchip_settings();
                        return WMPR_DONE;
                    }

                    /* In the TV's CB,   [NONE] */
                    if( (h_widget == H_CB_TV_NONE) )
                    {
                        if(aab_locked[6][0] == TRUE)
                        {
                            _lock_cb(6, 0, FALSE);    /* True to False */
                        }
                        else
                        {
                            _lock_cb(6, 0, TRUE);     /* False to True */
                        }

                        c_wgl_repaint(h_cnt_frm,NULL, TRUE);
                        _set_vchip_settings();
                        return WMPR_DONE;
                    }

                    /* In the TV Rating's CB */
                    for (ui2_i = 0; ui2_i < 6; ui2_i++)
                    {
                        for (ui2_j = 0; ui2_j < 6; ui2_j++)
                        {
                            if (aah_cb_tr[ui2_i][ui2_j] == h_widget)
                            {
                                if (ui2_j == 0)
                                {
                                    if (aab_locked[ui2_i][ui2_j])
                                    {
                                        _unlock_age_based(ui2_i);
                                    }
                                    else
                                    {
                                        _lock_age_based(ui2_i);
                                    }
                                }
                                else
                                {
                                    if (aab_locked[ui2_i][ui2_j])
                                    {
                                        _unlock_cnt_based(ui2_i, ui2_j);
                                    }
                                    else
                                    {
                                        _lock_cnt_based(ui2_i, ui2_j);
                                    }
                                }
                                /* change the block level to CUSTOM */
                                /*_set_bl_index(4); */

                                /* repaint */
                                c_wgl_repaint(h_cnt_frm,
                                              NULL, TRUE);

                                /* set the vchip setting to configuration
                                   manager. */
                                _set_vchip_settings();

                                return WMPR_DONE;
                            }
                        }
                    }
                }
            default:
                break;
            }
        }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    /* TV Rating */

    i4_ret = _create_col_title(TV_GRID_X_A,  TV_GRID_Y_A, 1, w2s_col_0, &ah_txt_col[0]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(TV_GRID_X_D,  TV_GRID_Y_D, 1, w2s_col_1, &ah_txt_col[1]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(TV_GRID_X_L,  TV_GRID_Y_L, 1, w2s_col_2, &ah_txt_col[2]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(TV_GRID_X_S,  TV_GRID_Y_S, 1, w2s_col_3, &ah_txt_col[3]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(TV_GRID_X_V,  TV_GRID_Y_V, 1, w2s_col_4, &ah_txt_col[4]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(TV_GRID_X_FV, TV_GRID_Y_FV,1, w2s_col_5, &ah_txt_col[5]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_TV_Y,    TV_GRID_Y_TV_Y,   3,w2s_row_0, &ah_txt_row[0]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_TV_Y7,   TV_GRID_Y_TV_Y7,  3,w2s_row_1, &ah_txt_row[1]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_TV_G,    TV_GRID_Y_TV_G,   3,w2s_row_2, &ah_txt_row[2]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_TV_PG,   TV_GRID_Y_TV_PG,  3,w2s_row_3, &ah_txt_row[3]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_TV_14,   TV_GRID_Y_TV_14,  3,w2s_row_4, &ah_txt_row[4]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_TV_MA,   TV_GRID_Y_TV_MA,  3,w2s_row_5, &ah_txt_row[5]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_TV_NONE, TV_GRID_Y_TV_NONE,3,w2s_row_6, &ah_txt_row[6]);

    MENU_CHK_FAIL(i4_ret);

    /* MPAA */

    i4_ret = _create_col_title(TV_GRID_X_MPAA, TV_GRID_Y_MPAA, 2,w2s_col_0_mpaa, &ah_txt_col_mpaa[0]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_G,    TV_GRID_Y_G,    2,w2s_row_0_mpaa, &ah_txt_row_mpaa[0]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_PG,   TV_GRID_Y_PG,   2,w2s_row_1_mpaa, &ah_txt_row_mpaa[1]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_PG_13,TV_GRID_Y_PG_13,2,w2s_row_2_mpaa, &ah_txt_row_mpaa[2]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_R,    TV_GRID_Y_R,    2,w2s_row_3_mpaa, &ah_txt_row_mpaa[3]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_NC_17,TV_GRID_Y_NC_17,2,w2s_row_4_mpaa, &ah_txt_row_mpaa[4]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_X,    TV_GRID_Y_X,    2,w2s_row_5_mpaa, &ah_txt_row_mpaa[5]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(TV_GRID_X_NONE, TV_GRID_Y_NONE, 2,w2s_row_6_mpaa, &ah_txt_row_mpaa[6]);
    MENU_CHK_FAIL(i4_ret);


    /* TV Rating */

    i4_ret = _create_cb(0, 0, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_Y  );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 1, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_Y7  );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(5, 1, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_Y7_FV);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 2, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_G );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 3, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_PG );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(1, 3, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_PG_D );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(2, 3, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_PG_L );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(3, 3, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_PG_S );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(4, 3, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_PG_V );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 4, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_14 );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(1, 4, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_14_D );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(2, 4, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_14_L );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(3, 4, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_14_S );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(4, 4, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_14_V );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 5, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_MA );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(2, 5, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_MA_L );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(3, 5, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_MA_S );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(4, 5, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_MA_V );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 6, TV_CB_START_X, TV_CB_START_Y, &H_CB_TV_NONE);
    MENU_CHK_FAIL(i4_ret);


    /* MPAA */

    i4_ret = _create_cb(0, 0, MPAA_CB_START_X, MPAA_CB_START_Y, &H_CB_MPAA_G);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 1, MPAA_CB_START_X, MPAA_CB_START_Y, &H_CB_MPAA_PG);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 2, MPAA_CB_START_X, MPAA_CB_START_Y, &H_CB_MPAA_PG_13);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 3, MPAA_CB_START_X, MPAA_CB_START_Y, &H_CB_MPAA_R);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 4, MPAA_CB_START_X, MPAA_CB_START_Y, &H_CB_MPAA_NC_17);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 5, MPAA_CB_START_X, MPAA_CB_START_Y, &H_CB_MPAA_X);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 6, MPAA_CB_START_X, MPAA_CB_START_Y, &H_CB_MPAA_NONE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _set_nav();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _chg_lang();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _frm_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    _get_vchip_settings();

    /* Hide tabs */
    /*
    menu_item_titles_chg_focus(h_lb_titles,
                               0xFFFF,
                               FALSE);
    */

    menu_main_set_title(MLM_MENU_KEY_US_VCHIP);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{

    /* Focus on the first CB  */
    c_wgl_set_focus(H_CB_TV_Y, WGL_NO_AUTO_REPAINT);

    menu_common_help_show_select_back();

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret = _chg_lang();
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

extern INT32 menu_atsc_page_vchip_init(VOID)
{
    t_g_menu_atsc_page_vchip.pf_menu_page_create =    _on_page_create;
    t_g_menu_atsc_page_vchip.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_atsc_page_vchip.pf_menu_page_show=       _on_page_show;
    t_g_menu_atsc_page_vchip.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_atsc_page_vchip.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_atsc_page_vchip.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_atsc_page_vchip.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#endif /* ATSC_VCHIP_ENABLE */


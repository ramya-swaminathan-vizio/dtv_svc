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
 * $RCSfile: menu_page_ver_info.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
#ifdef APP_MENU_VCT_RAW_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "u_atsc_si_eng.h"
#include "c_atsc_si_eng.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/nav/nav_colors.h"
#include "menu_rm_parse.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define VCT_RAW_TXT_X       (800)
#define VCT_RAW_TXT_Y       (100)
#define VCT_RAW_TXT_W       (350)
#define VCT_RAW_TXT_H       (500)

#define VCT_TREE_TXT_X      (250)
#define VCT_TREE_TXT_Y      (100)
#define VCT_TREE_TXT_W      (350)
#define VCT_TREE_TXT_H      (500)

#define VCT_CRNT_CH_TXT_X      (0)
#define VCT_CRNT_CH_TXT_Y      (100)
#define VCT_CRNT_CH_TXT_W      (230)
#define VCT_CRNT_CH_TXT_H      (30)

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))
#define ADDED_CNT_PER_ROW   (4 + 0 + 1 + 8*3 + 1 + 1) /* 0x0000: 00 01 02 03 04 05 06 07\n */
#define DATA_PER_ROW   (8)
#define ADDR_LEN    (8+1)
#define PAYLOAD_LEN (9+8*2+1)

#define VCT_TSID_LEN            (5 + 1 + 6 + 1)  /* TSID: 0xAAAA\n */
#define VCT_VER_LEN             (8 + 1 + 4 + 1)  /* VCT Ver: 0xAA\n */

#define VCT_CH_NUM_LEN          (7 + 1 + 11 + 1)  /* CH Num: XXXXX.YYYYY\n */
#define VCT_SHORT_NAME          (10 + 1 + 7 + 1)  /* Shortname: XXXXXXX\n */
#define VCT_MAJOR_NUM           (10 + 1 + 6 + 1)  /* Major Num: 0xXXXX\n */
#define VCT_MINOR_NUM           (10 + 1 + 6 + 1)  /* Minor Num: 0xXXXX\n */
#define VCT_MOD                 (11 + 1 + 4 + 1)  /* Modulation: 0xXX\n */
#define VCT_FREQ                (5 + 1 + 10 + 1)  /* Freq: Dec\n */
#define VCT_CH_TSID             (8 + 1 + 6 + 1)  /* CH TSID: 0xAAAA\n */
#define VCT_PROG_NUM            (9 + 1 + 4 + 1)  /* Prog Num: 0xAA\n */
#define VCT_SRC_ID              (7 + 1 + 4 + 1)  /* Src ID: 0xAA\n */
#define VCT_SVC_TYPE            (9 + 1 + 3 + 1)  /* Svc Type: 0xA\n */
#define VCT_DESCRIPTORS_OFFSET  (18 + 1 + 6 + 1)  /* Descr Offset Addr: 0xAAAA\n */
#define VCT_DESCR_LEN           (10 + 1 + 5 + 1 + 5 + 1 + 1 + 6 + 1 + 1)  /* Descr Len: XXXXX bytes (0xAAAA)\n */

#define VCT_TREE_COMMON_SIZE    (VCT_TSID_LEN + VCT_VER_LEN)
#define VCT_TREE_CHANNEL_SIZE   (VCT_CH_NUM_LEN + \
                                 VCT_SHORT_NAME + \
                                 VCT_MAJOR_NUM + \
                                 VCT_MINOR_NUM + \
                                 VCT_MOD + \
                                 VCT_FREQ + \
                                 VCT_CH_TSID + \
                                 VCT_PROG_NUM + \
                                 VCT_SRC_ID + \
                                 VCT_SVC_TYPE + \
                                 VCT_DESCRIPTORS_OFFSET + \
                                 VCT_DESCR_LEN)
#define VCT_TREE_TAB_SIZE       (1)
#define VCT_TREE_INDENT_FIELD_NUM   (11)    /* Fields of channel except for "CH Num:". */
#ifndef  COMMON_VER_INFO_X
    #define COMMON_VER_INFO_X                   (0)
    #define COMMON_VER_INFO_Y                   MENU_ITEM_Y
    #define COMMON_VER_INFO_W                   (CONTENT_W)
    #define COMMON_VER_INFO_H                   (CONTENT_H)
#endif

#ifndef COMMON_VER_INFO_CNT_INSET_L
    #define COMMON_VER_INFO_CNT_INSET_L         (8)
    #define COMMON_VER_INFO_CNT_INSET_R         (8)
#endif

#ifndef COMMON_VER_INFO_TITLE_W
    #define COMMON_VER_INFO_TITLE_W             (5 * GRID_W)
    #define COMMON_VER_INFO_TITLE_ALIGN         (WGL_AS_LEFT_CENTER)
    #define COMMON_VER_INFO_VALUE_W             (CONTENT_W - COMMON_VER_INFO_TITLE_W)
    #define COMMON_VER_INFO_VALUE_ALIGN         (WGL_AS_LEFT_CENTER)
#endif

#ifndef COMMON_VER_INFO_FONT_SIZE
    #define COMMON_VER_INFO_FONT_SIZE            FE_FNT_SIZE_SMALL
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct
{
    ATSC_SI_RM_NFY_T    e_nfy_type;
    atsc_si_rm_copy_fct pf_copy;
    UINT32              ui4_data;
} SI_ENG_NFY_DATA_T;
typedef struct
{
    BOOL b_is_one_part;             /**< Determine whether ch number is one part. */
    UINT16 ui2_major_ch_num;        /**< Major channel number. */
    UINT16 ui2_minor_ch_num;        /**< Minor channel number. */
    UINT8* pui1_raw;                /**< Buffer to store raw data. */
    UINT32 ui4_raw_len;             /**< Raw length. */
    UTF16_T* pw2s;                  /**< Points a UTF16_T string that stores RAW formatted string. */
    UTF16_T* pw2s_tree;             /**< Points a UTF16_T string that stores Tree formatted string. */
    CH_LIST_T* pt_ch_list;
} VCT_RAW_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_vct_raw;

static HANDLE_T     h_root_frm;
static HANDLE_T     h_txt_crnt_ch_num;
static HANDLE_T     h_txt_vct_raw;
static HANDLE_T     h_txt_vct_tree;

static VCT_RAW_T t_vct_raw;
static GL_COLOR_T t_g_vct_raw_color_bk           = { 255, {  0 }, {  0 }, {  255 }};

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _txt_widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2);
static INT32 _vct_raw_display_data (VOID);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static VOID _vct_raw_si_eng_hdlr (
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    INT32 i4_ret;
    VCT_RAW_T* pt_this = &t_vct_raw;
    SI_ENG_NFY_DATA_T* pt_nfy_data = (SI_ENG_NFY_DATA_T*) pv_data;

    if ((pt_nfy_data->e_nfy_type == ATSC_SI_RM_NFY_AVAIL) && (pt_nfy_data->pf_copy))
    {
        pt_this->ui4_raw_len = pt_nfy_data->ui4_data;
        /* Allocate memory. */
        if (pt_this->pui1_raw == NULL)
        {
            pt_this->pui1_raw = c_mem_alloc (pt_this->ui4_raw_len * sizeof (UINT8));
            if (pt_this->pui1_raw == NULL)
            {
                DBG_ERROR (("Out of mem ! %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
                return;
            }
            c_memset (pt_this->pui1_raw, 0, pt_this->ui4_raw_len * sizeof (UINT8));
        }
        /* Copy data from MW. */
        i4_ret = pt_nfy_data->pf_copy (pt_this->pui1_raw, (SIZE_T*)&pt_this->ui4_raw_len);
        if (i4_ret != 0)
        {
            DBG_ERROR(("Fail to copy ! %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            c_mem_free (pt_this->pui1_raw);
            pt_this->pui1_raw = NULL;
            return;
        }
        /* Invoke parse function. */
        i4_ret = menu_rm_parse (pt_this->pui1_raw, pt_this->ui4_raw_len, &pt_this->pt_ch_list);
        if (i4_ret != 0)
        {
            DBG_ERROR(("Fail to parse ! %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            return;
        }
        /* Display data. */
        _vct_raw_display_data ();
    }

}
static INT32 ap_rm_nfy (ATSC_SI_RM_NFY_T    e_nfy_type,
                  atsc_si_rm_copy_fct pf_copy,
                  UINT32              ui4_data)
{
    SI_ENG_NFY_DATA_T t_nfy_data;

    if (e_nfy_type == ATSC_SI_RM_NFY_AVAIL)
    {
        /* ui4_data is the buffer size when e_nfy_type == ATSC_SI_RM_NFY_AVAIL */
        t_nfy_data.e_nfy_type = e_nfy_type;
        t_nfy_data.pf_copy = pf_copy;
        t_nfy_data.ui4_data = ui4_data;

        menu_async_invoke(_vct_raw_si_eng_hdlr,
                          (VOID*) &t_nfy_data,
                          sizeof (SI_ENG_NFY_DATA_T),
                          FALSE);
    }

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _init_version
 *
 * Description:
 *      The version component show the version information.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _txt_vct_raw_create(
    HANDLE_T    h_parent,
    GL_RECT_T*  pt_rect,
    UINT32      ui4_style,
    HANDLE_T*   ph_widget
)
{
    INT32 i4_ret;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_color_info;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 _txt_widgets_proc_fct,
                                 200,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if(WGLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = COMMON_VER_INFO_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.i2_width = 9;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL);
    if(WGLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_LEFT_TOP),
                              NULL);
    if(WGLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }
    /* set content inset */
    t_inset.i4_left   = 10;
    t_inset.i4_right  = 10;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL);
    if(WGLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }
    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_vct_raw_color_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_vct_raw_color_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_vct_raw_color_bk);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info));
    if(WGLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_menu_color_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_menu_color_title_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_menu_color_alarm_txt);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info));
    if(WGLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }

    return MENUR_OK;
}

static VOID _make_addr_str (UINT32 ui4_row_idx, CHAR* s_addr, UINT8 ui1_len)
{
    c_memset (s_addr, 0, ui1_len);

    if (ui4_row_idx < 0x10000)
    {
        c_sprintf(s_addr, "%04x:",  ui4_row_idx*8);
    }
    else
    {
        c_sprintf(s_addr, "%05x",  ui4_row_idx*8);
    }
}
static VOID _make_payload_str (
    UINT32 ui4_row_idx,
    CHAR* s_payload,
    UINT8 ui1_len,
    UINT32 ui4_payload_cnt,
    UINT8* pui1_payload,
    UINT32 ui4_total_row_cnt)
{
    UINT32 ui4_idx = 0;

    c_memset (s_payload, 0, ui1_len);

    ui4_idx  = ui4_row_idx * DATA_PER_ROW;
    if ((ui4_row_idx + 1) < ui4_total_row_cnt)
    {
        c_sprintf(s_payload, "%02x %02x %02x %02x %02x %02x %02x %02x\n",
            pui1_payload[ui4_idx ], pui1_payload[ui4_idx +1], pui1_payload[ui4_idx +2],
            pui1_payload[ui4_idx +3], pui1_payload[ui4_idx +4], pui1_payload[ui4_idx +5],
            pui1_payload[ui4_idx +6], pui1_payload[ui4_idx +7]);
    }
    else
    {
        UINT8 ui1_left_cnt = ui4_payload_cnt % DATA_PER_ROW;

        switch (ui1_left_cnt)
        {
        case 0:
            c_sprintf(s_payload, "%02x %02x %02x %02x %02x %02x %02x %02x\n",
                pui1_payload[ui4_idx ], pui1_payload[ui4_idx +1], pui1_payload[ui4_idx +2],
                pui1_payload[ui4_idx +3], pui1_payload[ui4_idx +4], pui1_payload[ui4_idx +5],
                pui1_payload[ui4_idx +6], pui1_payload[ui4_idx +7]);
            break;
        case 1:
            c_sprintf(s_payload, "%02x\n",
                pui1_payload[ui4_idx]);
            break;
        case 2:
            c_sprintf(s_payload, "%02x %02x\n",
                pui1_payload[ui4_idx], pui1_payload[ui4_idx+1]);
            break;
        case 3:
            c_sprintf(s_payload, "%02x %02x %02x\n",
                pui1_payload[ui4_idx], pui1_payload[ui4_idx+1], pui1_payload[ui4_idx+2]);
            break;
        case 4:
            c_sprintf(s_payload, "%02x %02x %02x %02x\n",
                pui1_payload[ui4_idx], pui1_payload[ui4_idx+1], pui1_payload[ui4_idx+2],
                pui1_payload[ui4_idx+3]);
            break;
        case 5:
            c_sprintf(s_payload, "%02x %02x %02x %02x %02x\n",
                pui1_payload[ui4_idx], pui1_payload[ui4_idx+1], pui1_payload[ui4_idx+2],
                pui1_payload[ui4_idx+3], pui1_payload[ui4_idx+4]);
            break;
        case 6:
            c_sprintf(s_payload, "%02x %02x %02x %02x %02x %02x\n",
                pui1_payload[ui4_idx], pui1_payload[ui4_idx+1], pui1_payload[ui4_idx+2],
                pui1_payload[ui4_idx+3], pui1_payload[ui4_idx+4], pui1_payload[ui4_idx+5]);
            break;
        case 7:
            c_sprintf(s_payload, "%02x %02x %02x %02x %02x %02x %02x\n",
                pui1_payload[ui4_idx], pui1_payload[ui4_idx+1], pui1_payload[ui4_idx+2],
                pui1_payload[ui4_idx+3], pui1_payload[ui4_idx+4], pui1_payload[ui4_idx+5],
                pui1_payload[ui4_idx+6]);
            break;
        }
    }
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
static INT32 _txt_widgets_proc_fct(HANDLE_T    h_widget,
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
        case BTN_CURSOR_LEFT:
            if (h_widget == h_txt_vct_raw)
            {
                c_wgl_set_focus (h_txt_vct_tree, TRUE);
            }
            return WMPR_DONE;
        case BTN_CURSOR_RIGHT:
            if (h_widget == h_txt_vct_tree)
            {
                c_wgl_set_focus (h_txt_vct_raw, TRUE);
            }
            return WMPR_DONE;
        case BTN_RETURN:
            menu_nav_back();
            return WMPR_DONE;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
static INT32 _vct_raw_make_tree_txt (VCT_RAW_T* pt_this)
{
    UINT16 ui2_idx;
    CHAR s_row [100] = {0}, s_ch_num_major[30] = {0}, s_ch_num_minor[10] = {0};
    UTF16_T w2s_row_tmp[100] = {0};
    CH_LIST_T* pt_ch_list = pt_this->pt_ch_list;
    UINT32 ui4_w2s_tree_len = VCT_TREE_COMMON_SIZE + pt_ch_list->ui2_num_channels * VCT_TREE_CHANNEL_SIZE
        + pt_ch_list->ui2_num_channels * VCT_TREE_INDENT_FIELD_NUM * VCT_TREE_TAB_SIZE+ 100;

    /* Allocate memory to store Tree formatted string. */
    if (pt_this->pw2s_tree == NULL)
    {
        pt_this->pw2s_tree = c_mem_alloc (ui4_w2s_tree_len * sizeof (UTF16_T));
        if (pt_this->pw2s_tree == NULL)
        {
            return MENUR_OUT_OF_MEMORY;
        }
        c_memset (pt_this->pw2s_tree, 0, ui4_w2s_tree_len * sizeof (UTF16_T));
    }
    /* Make TSID & VCT Ver. */
    c_sprintf (s_row, "TSID: 0x%04x\nVCT Ver: 0x%02x\n", pt_ch_list->ui2_ts_id, pt_ch_list->ui2_ver);
    c_uc_ps_to_w2s (s_row, pt_this->pw2s_tree, ui4_w2s_tree_len);
    c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
    /* Make Channel. */
    for (ui2_idx = 0;ui2_idx < pt_ch_list->ui2_num_channels;ui2_idx++)
    {
        if ((pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num & 0x3f0) == 0x3f0)
        {
            /* one part. */
            UINT16 ui2_major = ((pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num & 0xf) << 10) | (pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_minor_ch_num & 0x3ff);

            if (ui2_major == pt_this->ui2_major_ch_num)
            {
                c_sprintf (s_row, "*CH Num: ");
                /* This is current viewing channel. */
                c_sprintf (s_ch_num_major, "%d\n", ui2_major);
            }
            else
            {
                c_sprintf (s_row, "CH Num: ");
                c_sprintf (s_ch_num_major, "%d\n", ui2_major);
            }
        }
        else
        {
            /* two part. */
            UINT16 ui2_major = pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num;
            UINT16 ui2_minor = pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_minor_ch_num;

            if ((ui2_major == pt_this->ui2_major_ch_num) && (ui2_minor == pt_this->ui2_minor_ch_num))
            {
                /* This is current viewing channel. */
                c_sprintf (s_row, "*CH Num: ");
                c_sprintf (s_ch_num_major, "%d.", ui2_major);
                c_sprintf (s_ch_num_minor, "%d\n", ui2_minor);
            }
            else
            {
                c_sprintf (s_row, "CH Num: ");
                c_sprintf (s_ch_num_major, "%d.", ui2_major);
                c_sprintf (s_ch_num_minor, "%d\n", ui2_minor);
            }
            c_strcat (s_ch_num_major, s_ch_num_minor);
        }
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);

        c_uc_ps_to_w2s (s_ch_num_major, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);

        c_sprintf (s_row, " Shortname: ");
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_uc_w2s_strcat (pt_this->pw2s_tree, pt_ch_list->pt_ch_info[ui2_idx].w2s_ch_name);
        c_sprintf (s_row, "\n Major Num: 0x%02x\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_major_ch_num);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Minor Num: 0x%02x\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_minor_ch_num);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Modulation: 0x%02x\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui1_mod_mode);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Freq: %u\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui4_freq);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " CH TSID: 0x%04x\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_ts_id);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Prog Num: 0x%02x\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_svc_id);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Src ID: 0x%02x\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui2_src_id);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Svc Type: 0x%01x\n", pt_ch_list->pt_ch_info[ui2_idx].t_info.ui1_svc_type);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Descr Offset Addr: 0x%04x\n", pt_ch_list->pt_ch_info[ui2_idx].pv_descrs_offset);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
        c_sprintf (s_row, " Descr Len: %d bytes (0x%x)\n", pt_ch_list->pt_ch_info[ui2_idx].z_descrs_len, pt_ch_list->pt_ch_info[ui2_idx].z_descrs_len);
        c_uc_ps_to_w2s (s_row, w2s_row_tmp, 100);
        c_uc_w2s_strcat (pt_this->pw2s_tree, w2s_row_tmp);
    }

    /* c_dbg_secure_stmt ("tree len = %d\n", c_uc_w2s_strlen (pt_this->pw2s_tree));*/

    return MENUR_OK;
}
static INT32 _vct_raw_make_raw_txt (VCT_RAW_T* pt_this)
{
    INT32 i4_ret;
    UINT32 ui4_i = 0,ui4_w2s_cnt = 0, ui4_row_cnt = 0;
    CHAR s_addr[ADDR_LEN] = {0};
    CHAR s_payload[PAYLOAD_LEN] = {0};
    CHAR s_row[ADDR_LEN+PAYLOAD_LEN+1] = {0};
    UTF16_T w2s_tmp[ADDR_LEN+PAYLOAD_LEN+1];

    i4_ret = c_wgl_set_focus(h_txt_vct_raw, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL (i4_ret);
    /* For RAW text. */
    ui4_row_cnt = pt_this->ui4_raw_len / DATA_PER_ROW;
    if ((pt_this->ui4_raw_len % DATA_PER_ROW) != 0)
    {
        ui4_row_cnt++;
    }
    ui4_w2s_cnt = ADDED_CNT_PER_ROW * ui4_row_cnt;
    if (pt_this->pw2s == NULL)
    {
        pt_this->pw2s = c_mem_alloc (ui4_w2s_cnt * sizeof (UTF16_T));
        if (pt_this->pw2s == NULL)
        {
            c_mem_free (pt_this->pui1_raw);
            return MENUR_OUT_OF_MEMORY;
        }
    }
    c_memset (pt_this->pw2s, 0, (ui4_w2s_cnt * sizeof (UTF16_T)));
    /* Make formated string. */
    for (ui4_i = 0;ui4_i < ui4_row_cnt;ui4_i++)
    {
        c_memset (s_row, 0, sizeof (CHAR) * (ADDR_LEN+PAYLOAD_LEN+1));
        c_memset (w2s_tmp, 0, sizeof (UTF16_T) * (ADDR_LEN+PAYLOAD_LEN+1));
        _make_addr_str (ui4_i, s_addr, ADDR_LEN);
        _make_payload_str (ui4_i, s_payload, PAYLOAD_LEN, pt_this->ui4_raw_len, pt_this->pui1_raw,
            ui4_row_cnt);
        c_strcpy (s_row, s_addr);
        c_strcat (s_row, s_payload);

        c_uc_ps_to_w2s ((CHAR*)s_row, w2s_tmp, (ADDR_LEN+PAYLOAD_LEN+1));
        c_uc_w2s_strcat (pt_this->pw2s, w2s_tmp);
    }
    /* c_dbg_secure_stmt ("raw len = %d\n", c_uc_w2s_strlen (pt_this->pw2s)); */

    return MENUR_OK;
}
static VOID _vct_raw_free_resource (VOID)
{
    VCT_RAW_T* pt_this = &t_vct_raw;

    if (pt_this->pui1_raw)
    {
        c_mem_free (pt_this->pui1_raw);
        pt_this->pui1_raw = NULL;
    }
    pt_this->ui4_raw_len = 0;
    if (pt_this->pw2s)
    {
        c_mem_free (pt_this->pw2s);
        pt_this->pw2s = NULL;
    }
    if (pt_this->pw2s_tree)
    {
        c_mem_free (pt_this->pw2s_tree);
        pt_this->pw2s_tree = NULL;
    }
    if (pt_this->pt_ch_list)
    {
        c_mem_free (pt_this->pt_ch_list);
        pt_this->pt_ch_list = NULL;
    }
}
static INT32 _vct_raw_make_crnt_ch_num_txt (VCT_RAW_T* pt_this, UTF16_T* pw2s_ch_num, UINT8 ui2_len)
{
    BOOL b_found = FALSE;
    SVL_REC_T t_svl_rec;
    INT32 i4_ret = MENUR_OK;
    UINT16 ui2_major = 0, ui2_minor = 0;
    CHAR s_ch_num[50] = {0};

    do
    {
        i4_ret = menu_get_crnt_svl_rec (&t_svl_rec, &b_found);
        if ((i4_ret != MENUR_OK) || (!b_found))
        {
            break;
        }
        pt_this->b_is_one_part = SB_ATSC_IS_ONE_PART_CHANNEL_ID(t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
        if (pt_this->b_is_one_part)
        {
            ui2_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM (t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
            c_sprintf (s_ch_num, "Current CH num: %d", ui2_major);
        }
        else
        {
            ui2_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM (t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
            ui2_minor = SB_ATSC_GET_MINOR_CHANNEL_NUM (t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);
            c_sprintf (s_ch_num, "Current CH num: %d.%d", ui2_major, ui2_minor);
        }
        pt_this->ui2_major_ch_num = ui2_major;
        pt_this->ui2_minor_ch_num = ui2_minor;
        c_uc_ps_to_w2s (s_ch_num, pw2s_ch_num, ui2_len);

        return MENUR_OK;
    } while (0);

    return i4_ret;
}
static INT32 _vct_raw_display_data (VOID)
{
    INT32 i4_ret = MENUR_OK;
    VCT_RAW_T* pt_this = &t_vct_raw;

    do
    {
        UTF16_T w2s_crnt_ch_num[50] = {0};

        /* This statement must be first called. */
        i4_ret = _vct_raw_make_crnt_ch_num_txt (pt_this, w2s_crnt_ch_num, 50);
        if (i4_ret != MENUR_OK)
        {
            break;
        }
        i4_ret = c_wgl_do_cmd (h_txt_crnt_ch_num,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK(w2s_crnt_ch_num),
                                  WGL_PACK(c_uc_w2s_strlen (w2s_crnt_ch_num)));
        if (i4_ret != MENUR_OK)
        {
            break;
        }
        i4_ret = _vct_raw_make_raw_txt (pt_this);
        if (i4_ret != MENUR_OK)
        {
            break;
        }
        /* set text. */
        i4_ret = c_wgl_do_cmd (h_txt_vct_raw,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK(pt_this->pw2s),
                                  WGL_PACK(c_uc_w2s_strlen (pt_this->pw2s)));
        if (i4_ret != MENUR_OK)
        {
            break;
        }
        /* For Tree text. */
        i4_ret = _vct_raw_make_tree_txt (pt_this);
        if (i4_ret != MENUR_OK)
        {
            break;
        }
        i4_ret = c_wgl_do_cmd (h_txt_vct_tree,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK(pt_this->pw2s_tree),
                                  WGL_PACK(c_uc_w2s_strlen (pt_this->pw2s_tree)));
        if (i4_ret != MENUR_OK)
        {
            break;
        }
        menu_main_set_visibility (FALSE);
        c_wgl_set_visibility (h_txt_crnt_ch_num, WGL_SW_NORMAL);
        c_wgl_set_visibility (h_txt_vct_raw, WGL_SW_NORMAL);
        c_wgl_set_visibility (h_txt_vct_tree, WGL_SW_NORMAL);

        menu_pm_repaint ();

        return MENUR_OK;
    } while (0);

    _vct_raw_free_resource ();
    return MENUR_FAIL;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret;
    VCT_RAW_T* pt_this = &t_vct_raw;
    GL_RECT_T t_rect;
    UINT32 ui4_style;

    c_memset (pt_this, 0, sizeof (VCT_RAW_T));

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      VCT_RAW_TXT_X,
                      VCT_RAW_TXT_Y,
                      VCT_RAW_TXT_W,
                      VCT_RAW_TXT_H);
    ui4_style = (WGL_STL_TEXT_MAX_DIS_40_LINE | WGL_STL_TEXT_MAX_32768 | WGL_STL_TEXT_MULTILINE | WGL_STL_GL_NO_IMG_UI);
    i4_ret = _txt_vct_raw_create(h_root_frm, &t_rect, ui4_style, &h_txt_vct_raw);
    MENU_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      VCT_TREE_TXT_X,
                      VCT_TREE_TXT_Y,
                      VCT_TREE_TXT_W,
                      VCT_TREE_TXT_H);
    ui4_style = (WGL_STL_TEXT_MAX_DIS_40_LINE | WGL_STL_TEXT_MAX_32768 | WGL_STL_TEXT_MULTILINE | WGL_STL_GL_NO_IMG_UI);
    i4_ret = _txt_vct_raw_create(h_root_frm, &t_rect, ui4_style, &h_txt_vct_tree);
    MENU_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      VCT_CRNT_CH_TXT_X,
                      VCT_CRNT_CH_TXT_Y,
                      VCT_CRNT_CH_TXT_W,
                      VCT_CRNT_CH_TXT_H);
    ui4_style = (WGL_STL_TEXT_MAX_DIS_40_LINE | WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_MULTILINE | WGL_STL_GL_NO_IMG_UI);
    i4_ret = _txt_vct_raw_create(h_root_frm, &t_rect, ui4_style, &h_txt_crnt_ch_num);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _txt_widgets_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility (h_txt_crnt_ch_num, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_txt_vct_raw, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_txt_vct_tree, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    /* Register callback. */
    i4_ret = c_atsc_si_reg_raw_mem_nfy (ap_rm_nfy);
    MENU_CHK_FAIL(i4_ret);

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
    /* disable the menu timer */
    menu_timer_enable(FALSE);
    menu_timer_stop();
	/* users activate the OSD for raw memory dump */
    c_atsc_si_raw_mem_set (ATSC_SI_RM_SET_INIT); /* it will call the ap_rm_nfy (ATSC_SI_RM_NFY_AVAIL) if raw memory data is ready */

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    /* enable the menu timer */
    menu_timer_enable(TRUE);
    menu_timer_start();
    c_wgl_set_visibility (h_txt_crnt_ch_num, WGL_SW_HIDE);
    c_wgl_set_visibility (h_txt_vct_raw, WGL_SW_HIDE);
    c_wgl_set_visibility (h_txt_vct_tree, WGL_SW_HIDE);
    menu_main_set_visibility (TRUE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    menu_common_help_show_back();

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    _vct_raw_free_resource ();
    c_atsc_si_raw_mem_set (ATSC_SI_RM_SET_STOP);

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

extern INT32 menu_page_vct_raw_init(VOID)
{
    t_g_menu_page_vct_raw.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_vct_raw.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_vct_raw.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_vct_raw.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_vct_raw.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_vct_raw.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_vct_raw.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif


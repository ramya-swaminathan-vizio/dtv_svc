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
 * Copyright (c) 2005, CrystalMedia Technology, Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_cli.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"

#include "menu2/menu_util2.h"
#include "menu2/menu_atsc/menu_atsc.h"

/* channel scan status */
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef TIME_MEASUREMENT
#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#endif
#include "menu2/menu_dbg.h"

#ifdef ATSC_ADV_SCAN_RNG_ENABLE
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)
#define _SET_SCANE(start, end) ( ((start) << 16) | (end))

#define PHY_TRSTRL_CH_NUM_MIN             ((UINT16)    2)
#define PHY_TRSTRL_CH_NUM_MAX             ((UINT16)   69)

#define PHY_CABLE_CH_NUM_MIN              ((UINT16)    SB_CQAM_SCAN_FIRST_CHANNEL)
#define PHY_CABLE_CH_NUM_MAX              ((UINT16)    SB_CQAM_SCAN_LAST_CHANNEL)

#define INPUT_RESET_DELAY                 ((UINT32) 1500)

typedef struct _ADV_SCAN_NFY_T {
    HANDLE_T    h_builder;
    UINT32      ui4_nfy_reason;
    INT32       i4_nfy_data;
    VOID*       pv_nfy_tag;
} ADV_SCAN_NFY_T;

typedef struct _ADV_SCAN_INFO_T {
    HANDLE_T    h_builder;
    INT32       i4_vir_ch_num;
    INT32       i4_phy_ch_num;
    INT32       i4_phy_ch_ttl;
    BOOL        b_done;         /* if b_done is TRUE, it means that the builder has
                                   sent a SB_REASON_COMPLETE, SB_REASON_CANCEL,
                                   SB_REASON_ABORT message */
} ADV_SCAN_INFO_T;

typedef enum {
    _HELP_TIP_TYPE_HOMEBAR = 0,
    _HELP_TIP_TYPE_BACKBAR,
    _HELP_TIP_TYPE_MODE,
    _HELP_TIP_TYPE_FROM,
    _HELP_TIP_TYPE_TO,
    _HELP_TIP_TYPE_BTN_START,
    _HELP_TIP_TYPE_BTN_CANCEL,
    _HELP_TIP_TYPE_BTN_DONE,
    _HELP_TIP_TYPE_BTN_LB_MODE_EX,
    _HELP_TIP_TYPE_LAST_ENTRY

} _HELP_TIP_TYPE_T ;

typedef enum{
    RANG_SCAN_VIEW_INIT = 0,
    RANG_SCAN_VIEW_SCAN,
    RANG_SCAN_VIEW_LB_MODE_EX,
    RANG_SCAN_VIEW_LAST_ENTRY
}RANG_SCAN_VIEW_TYPE_T;

static  RANG_SCAN_VIEW_TYPE_T e_scan_view_type=RANG_SCAN_VIEW_INIT;

#define SCAN_MODE_ATV           (UINT16)0x01
#define SCAN_MODE_DTV           (UINT16)0x02
#define SCAN_MODE_ATV_DTV       (UINT16)(SCAN_MODE_ATV | SCAN_MODE_DTV)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_adv_scan_rng;

static HANDLE_T    h_cnt_frm;
static HANDLE_T    h_timer_ani;
static HANDLE_T    h_lb_mode;
static HANDLE_T    h_eb_from;
static HANDLE_T    h_eb_to;

static HANDLE_T    h_lb_btn;
static HANDLE_T    h_txt_info_2;

static HANDLE_T    h_lb_mode_ex;

typedef struct _SCAN_COMMON_ITEM_T {
    HANDLE_T   h_frm;
    HANDLE_T   h_txt;
} SCAN_COMMON_ITEM_T;

typedef enum{
    SCAN_COMMON_ITEM_CH_FOUND=0,
    SCAN_COMMON_ITEM_DIG_CH,
    SCAN_COMMON_ITEM_ANALOG_CH,
    SCAN_COMMON_ITEM_NUM
} SCAN_COMMON_ITEM_TYPE_T;

static SCAN_COMMON_ITEM_T t_scan_common_item[SCAN_COMMON_ITEM_NUM];

typedef struct _RANGE_ITEM_T {
    HANDLE_T   h_frm;
    HANDLE_T   h_range;
    HANDLE_T   h_txt_prog;
    HANDLE_T   h_txt_complete;
} RANGE_ITEM_T;
static RANGE_ITEM_T t_range_item;

static UINT32      ui4_page_id;
static UINT16      ui2_crnt_svl_id;
static BOOL        b_scan         = FALSE;
static BOOL        b_scaned       = FALSE;
static UINT16      ui2_scan_mode = SCAN_MODE_DTV;

static ADV_SCAN_INFO_T   t_scan_info_atv;
static ADV_SCAN_INFO_T   t_scan_info_dtv;

static UINT16       ui2_phy_ch_min = 0;
static UINT16       ui2_phy_ch_max = 0;

static HANDLE_T            h_homebar = NULL_HANDLE;
static HANDLE_T            h_backbar = NULL_HANDLE;

static UTF16_T*             apw2s_help_tip[_HELP_TIP_TYPE_LAST_ENTRY] = {0};


#ifdef CLI_SUPPORT
    static HANDLE_T    h_sema_bin;
#endif
static  UINT16 ui2_lst_last_hlt= 0xFFFF;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2);

static VOID _scan_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag);

static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag);

static INT32 _eb_from_to_set_value(HANDLE_T    h_widget,
                                   UINT16      u2_value,
                                   BOOL        b_input);

static UINT16 _eb_from_to_get_value(HANDLE_T    h_widget);

static INT32 _change_view(RANG_SCAN_VIEW_TYPE_T  e_view_type);

static INT32 _show_lb_mode_ex_view(BOOL b_repaint);
static INT32 a_menu_channel_partial_scan_reset_svl_by_mask(UINT16      ui2_start_channel,
                                                           UINT16      ui2_end_channel);
/*----------------------------------------------------------------------------
                        Pseudo Builder
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _itoa
 *
 * Description: Interger to string utility function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _itoa(UTF16_T* w2s_dst,
                  INT32 i4_src,
                  UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}

/*-----------------------------------------------------------------------------
 * Name: _get_freq_plan
 *
 * Description: Get the frequency plan setting and return correct parameter
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_freq_plan(UINT8*  pui1_freq,
                            UINT32* pui4_mod)
{

    INT32  i4_ret;
    UINT8  ui1_idx;

    i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_PLN, &ui1_idx);
    if (i4_ret == APP_CFGR_OK)
    {
        switch (ui1_idx)
        {
        case APP_CFG_BS_PLN_AUTO:
    #ifdef APP_DCR_SUPPORT
            (*pui1_freq) = SB_OOB_FREQ_PLAN_AUTO;
    #else
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_AUTO;
    #endif
            i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_VSB, &ui1_idx);
            if (i4_ret == APP_CFGR_OK)
            {
                switch (ui1_idx)
                {
                case APP_CFG_BS_VSB_DETECT:
                    (*pui4_mod)  = MENU_SB_CQAM_DEF_MOD_MASK;
                    break;
                case APP_CFG_BS_VSB_IGNORE:
                    (*pui4_mod)  = MENU_SB_CQAM_QAM_MOD_MASK;
                    break;
                default:
                    DBG_ERROR(("<MENU>Wrong 8vsb mode: %d\r\n", ui1_idx));
                    return MENUR_FAIL;
                }
            }
            else
            {
                DBG_ERROR(("<MENU>Cannot get 8vsb mode\r\n"));
                return MENUR_FAIL;
            }
            break;
        case APP_CFG_BS_PLN_STD:
    #ifdef APP_DCR_SUPPORT
            (*pui1_freq) = SB_OOB_FREQ_PLAN_STD;
    #else
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_STD;
    #endif
            (*pui4_mod)  = MENU_SB_CQAM_QAM_MOD_MASK;
            break;
        case APP_CFG_BS_PLN_IRC:
    #ifdef APP_DCR_SUPPORT
            (*pui1_freq) = SB_OOB_FREQ_PLAN_IRC;
    #else
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_IRC;
    #endif
            (*pui4_mod)  = MENU_SB_CQAM_QAM_MOD_MASK;
            break;
        case APP_CFG_BS_PLN_HRC:
    #ifdef APP_DCR_SUPPORT
            (*pui1_freq) = SB_OOB_FREQ_PLAN_HRC;
    #else
            (*pui1_freq) = SB_CQAM_FREQ_PLAN_HRC;
    #endif
            (*pui4_mod)  = MENU_SB_CQAM_QAM_MOD_MASK;
            break;
        default:
            DBG_ERROR(("<MENU>Wrong frequency plan mode: %d\r\n", ui1_idx));
            return MENUR_FAIL;
        }
    }
    else
    {
        DBG_ERROR(("<MENU>Cannot get frequency plan mode\r\n"));
        return MENUR_FAIL;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _calc_progress
 *
 * Description:
 *  Calculate the progress.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _calc_progress(VOID)
{
    if(ui2_scan_mode == SCAN_MODE_ATV)
    {
        return t_scan_info_atv.i4_phy_ch_num * 100 / t_scan_info_atv.i4_phy_ch_ttl;
    }
    else if(ui2_scan_mode == SCAN_MODE_DTV)
    {
        return t_scan_info_dtv.i4_phy_ch_num * 100 / t_scan_info_dtv.i4_phy_ch_ttl;
    }
    else
    {
        return (t_scan_info_atv.i4_phy_ch_num + t_scan_info_dtv.i4_phy_ch_num) * 100 /
               (t_scan_info_atv.i4_phy_ch_ttl + t_scan_info_dtv.i4_phy_ch_ttl);
    }
}
/*----------------------------------------------------------------------------
 * Name: _pb_create
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
static INT32 _pb_create(
    HANDLE_T    h_parent,
    GL_RECT_T   *pt_rect,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;
    WGL_IMG_INFO_T      t_img_info;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)(0),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Display mode */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_DISPLAY_MODE,
                          WGL_PACK(WGL_PG_DM_HIDE_IDR),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Default Range */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK((INT32)0),
                           WGL_PACK((INT32)100));
    MENU_CHK_FAIL(i4_ret);


    /* Set Default Levels */
    t_pg_levels.a_boundary[0] = 100;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_BAR_MIN_SIZE,
                           WGL_PACK(0),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set progressbar's BK Image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_pb_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_pb_bk;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pb_bar;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bar;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pb_bar;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _txt_create
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
static INT32 _txt_create(
    HANDLE_T    h_parent,
    GL_RECT_T   *pt_rect,
    UINT8        ui1_align,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;

    ui4_style = WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)(ui4_style),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)(UINT32)ui1_align,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
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

    /* txt info */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_bk2_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_bk2_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_white/*&t_g_menu_color_bk2_txt_disable*/);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bk2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bk2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bk2;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _eb_from_to_set_value_left
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
static INT32 _eb_from_to_set_value_left(HANDLE_T    h_widget,
                                   UINT16      u2_value)
{
    INT32 i4_ret;
    UTF16_T w2s_buf[10];

    c_memset(w2s_buf, 0, 10*sizeof(UTF16_T));

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(u2_value),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(0!=u2_value)
    {
        _itoa(w2s_buf, (INT32)u2_value, 10);
    }

    c_uc_w2s_strncat(w2s_buf, _TEXT("_"),
                     10 - c_uc_w2s_strlen(w2s_buf));

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_from_to_set_value_lose_focus
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
static INT32 _eb_from_to_set_value_lose_focus(HANDLE_T    h_widget,
                                         UINT16      ui2_value,
                                         BOOL        b_change)
{
    INT32 i4_ret;
    UTF16_T w2s_buf[10];
    SIZE_T  t_size=0;

    c_memset(w2s_buf,0,10*sizeof(UTF16_T));

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(ui2_value),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_change)
    {
        _itoa(w2s_buf, (INT32)ui2_value, 10);
    }
    else /*Value not change just remove '_'*/
    {
        i4_ret=c_wgl_do_cmd(h_widget,
                     WGL_CMD_EB_GET_TEXT,
                     (VOID*)w2s_buf,
                     (VOID*)10);
        MENU_LOG_ON_FAIL(i4_ret);

        /*Remove char '_'*/
        t_size=c_uc_w2s_strlen(w2s_buf);
        if (t_size > 0 && t_size <= sizeof(w2s_buf)/sizeof(UTF16_T))
            w2s_buf[t_size-1] = 0;
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_from_to_set_value_get_focus
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
static INT32 _eb_from_to_set_value_get_focus(HANDLE_T    h_widget)
{
    INT32 i4_ret;
    UTF16_T w2s_buf[10];

    c_memset(w2s_buf, 0, 10*sizeof(UTF16_T));

    i4_ret=c_wgl_do_cmd(h_widget,
                 WGL_CMD_EB_GET_TEXT,
                 (VOID*)w2s_buf,
                 (VOID*)10);
    MENU_LOG_ON_FAIL(i4_ret);


#ifdef APP_TTS_SUPPORT
    UTF16_T     w2s_msg[128+1] = {0};

    c_memset(w2s_msg, 0, sizeof(UTF16_T)*(128+1));

    if (h_eb_from == h_widget)
    {
        c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_FROM));
    }
    else if (h_eb_to == h_widget)
    {
        c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_TO));
    }
    c_uc_w2s_strcat(w2s_msg, _TEXT(" "));
    c_uc_w2s_strcat(w2s_msg, w2s_buf);

    a_app_tts_play(w2s_msg, c_uc_w2s_strlen(w2s_msg));
#endif

    c_uc_w2s_strncat(w2s_buf, _TEXT("_"),
                     10 - c_uc_w2s_strlen(w2s_buf));

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_check_channel_to_value
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
static INT32 _eb_check_channel_to_value(BOOL *pb_same)
{
    INT32 i4_ret;
    UINT16 ui2_from_value,ui2_to_value;
    UTF16_T w2s_buf[10]={0};

    c_memset(w2s_buf, 0, 10*sizeof(UTF16_T));

    ui2_from_value = _eb_from_to_get_value(h_eb_from);
    ui2_to_value= _eb_from_to_get_value(h_eb_to);

    if(ui2_to_value<=ui2_from_value)
    {
        *pb_same = TRUE;
        ui2_to_value = ui2_from_value;

        i4_ret = c_wgl_do_cmd(h_eb_to,
                              WGL_CMD_GL_SET_ATTACH_DATA,
                              WGL_PACK(ui2_to_value),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=c_wgl_do_cmd(h_eb_from,
                     WGL_CMD_EB_GET_TEXT,
                     (VOID*)w2s_buf,
                     (VOID*)10);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(h_eb_to,
                              WGL_CMD_EB_SET_TEXT,
                              WGL_PACK(w2s_buf),
                              WGL_PACK(0xFF));
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        *pb_same = FALSE;
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _eb_from_to_set_value
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
static INT32 _eb_from_to_set_value(HANDLE_T    h_widget,
                                UINT16      u2_value,
                                BOOL        b_input)
{
    INT32 i4_ret;
    UTF16_T w2s_buf[10];
    UTF16_T w2s_old[10];
    SIZE_T  t_size=0,t_size_2=0,t_size_3=0;
    UINT16  ui2_old_value;

    ui2_old_value=_eb_from_to_get_value(h_widget);

    c_memset(w2s_buf, 0, 10*sizeof(UTF16_T));
    c_memset(w2s_old, 0, 10*sizeof(UTF16_T));

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(u2_value),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /*For Effect 0,00*/
    if(b_input &&
       0==ui2_old_value)
    {
        i4_ret=c_wgl_do_cmd(h_widget,
                     WGL_CMD_EB_GET_TEXT,
                     (VOID*)w2s_old,
                     (VOID*)10);
        MENU_LOG_ON_FAIL(i4_ret);

        /*Remove char '_'*/
        t_size=c_uc_w2s_strlen(w2s_old);
        if (t_size > 0 && t_size <= sizeof(w2s_old)/sizeof(UTF16_T))
            w2s_old[t_size-1] = 0;

        t_size_2 = c_uc_w2s_strlen(_TEXT("00_"));
        t_size_3 = c_uc_w2s_strlen(_TEXT("000_"));

        /*Two num*/
        if(ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
        {
            /*Reinput*/
            if(t_size>=t_size_2)
            {
                c_memset(w2s_old, 0, 10*sizeof(UTF16_T));
            }
        }
        else
        {
            /*Reinput*/
            if(t_size>=t_size_3)
            {
                c_memset(w2s_old, 0, 10*sizeof(UTF16_T));
            }
        }

    }

    _itoa(w2s_buf, (INT32)u2_value, 10);

    c_uc_w2s_strncat(w2s_old, w2s_buf,
                     10 - c_uc_w2s_strlen(w2s_old));

    if(b_input)
    {
        c_uc_w2s_strncat(w2s_old, _TEXT("_"),
                         10 - c_uc_w2s_strlen(w2s_buf));
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_old),
                          WGL_PACK(0xFF));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_from_to_get_value
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
static UINT16 _eb_from_to_get_value(HANDLE_T    h_widget)
{
    UINT32      u4_value;
    c_wgl_do_cmd(h_widget,
                 WGL_CMD_GL_GET_ATTACH_DATA,
                 WGL_PACK(&u4_value),
                 NULL);

    return (UINT16)u4_value;
}
/*----------------------------------------------------------------------------
 * Name: _set_nav
 *
 * Description: Set the navigation
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
    INT32   i4_ret = 0;
    WGL_KEY_LINK_T      at_key_lnk[2];

    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_backbar;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_eb_from;
        i4_ret = c_wgl_set_navigation(h_lb_mode, 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_lb_mode;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_eb_to;
        i4_ret = c_wgl_set_navigation(h_eb_from, 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_eb_from;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
         at_key_lnk[1].h_widget = h_lb_btn;
        i4_ret = c_wgl_set_navigation(h_eb_to, 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_start_scan_fail
 *
 * Description:
 *  if start to scan unsuccessfully, it will show "scan error" message, and
 * callback the notify to CLI (if any).
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_start_scan_fail(VOID)
{
    INT32 i4_ret;

    i4_ret =_change_view(RANG_SCAN_VIEW_INIT);
    MENU_LOG_ON_FAIL(i4_ret);

    #ifdef CLI_SUPPORT
        /* notify the CLI command */
        c_sema_unlock(h_sema_bin);
    #endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _txt_info_animate_update
 *
 * Description:
 *
 * Inputs:
 *      b_step - if go to the next animation step
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _txt_info_animate_update(BOOL b_repaint)
{
    INT32 i4_ret;
    UTF16_T w2s_str[128];
    UTF16_T w2s_num[10];
    UINT32  ui4_len;

    if (b_scan)
    {
        /* Append Analog Channels */
		if(ui2_scan_mode & SCAN_MODE_ATV)
        {
            ui4_len = 128;
            c_memset(w2s_str, 0, sizeof(w2s_str));
            c_memset(w2s_num, 0, sizeof(w2s_num));

            c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_SCAN_ANLG_CH),
                             ui4_len - c_uc_w2s_strlen(w2s_str));

	        c_uc_w2s_strncat(w2s_str, _TEXT("  "),
	                         ui4_len - c_uc_w2s_strlen(w2s_str));

	        _itoa(w2s_num, t_scan_info_atv.i4_vir_ch_num, 9);

	        c_uc_w2s_strncat(w2s_str, w2s_num,
	                         ui4_len - c_uc_w2s_strlen(w2s_str));

            i4_ret = c_wgl_do_cmd(t_scan_common_item[SCAN_COMMON_ITEM_ANALOG_CH].h_txt,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK(w2s_str),
                                  (VOID*)0xFFFF);
            MENU_LOG_ON_FAIL(i4_ret);

            if(b_repaint)
            {
                i4_ret=c_wgl_repaint(t_scan_common_item[SCAN_COMMON_ITEM_ANALOG_CH].h_frm,
                                     NULL,
                                     TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
		}


        /* Append Digital Channels */
		if(ui2_scan_mode & SCAN_MODE_DTV)
        {
            ui4_len = 128;
            c_memset(w2s_str, 0, sizeof(w2s_str));
            c_memset(w2s_num, 0, sizeof(w2s_num));

            c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_SCAN_DIG_CH),
                             ui4_len - c_uc_w2s_strlen(w2s_str));

	        c_uc_w2s_strncat(w2s_str, _TEXT("  "),
	                         ui4_len - c_uc_w2s_strlen(w2s_str));

	        _itoa(w2s_num, t_scan_info_dtv.i4_vir_ch_num, 9);

	        c_uc_w2s_strncat(w2s_str, w2s_num,
	                         ui4_len - c_uc_w2s_strlen(w2s_str));

            i4_ret = c_wgl_do_cmd(t_scan_common_item[SCAN_COMMON_ITEM_DIG_CH].h_txt,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK(w2s_str),
                                  (VOID*)0xFFFF);
            MENU_LOG_ON_FAIL(i4_ret);

            if(b_repaint)
            {
                i4_ret=c_wgl_repaint(t_scan_common_item[SCAN_COMMON_ITEM_DIG_CH].h_frm,
                                     NULL,
                                     TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
		}

    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_scan_stop
 *
 * Description:
 *      _on_scan_stop function is always invoked by the first message processing
 *  procedure when the scan completes. It could be the scan completion event from
 *  svl builder, abort event from user, or cancel event from user. It will set
 *  the b_scan variable to FALSE so that the following message processing procedure
 *  could realize the scan session is finished. However, it doesn't guarantee that
 *  the svl builder is in the AVAILABLE state. It should wait for both builder send
 *  one of the SB_REASON_COMPLETE, SB_REASON_ABORT, SB_REASON_CANCEL message.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_scan_stop(UTF16_T* w2s_message)
{
    INT32 i4_ret;
    UTF16_T w2s_str[128];
    UTF16_T w2s_num[10];
    UINT32  ui4_len;

    b_scan = FALSE;
    /* Menu is not in scanning status */
    t_g_menu_is_scanning = FALSE;

    /* Broadcast the message to enable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to enable the EAS.\r\n"));
    a_amb_channel_scan_active(FALSE);

    /* change the info in help list */
    menu_atsc_help_show_scan();

    ui4_len = 128;
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(w2s_num, 0, sizeof(w2s_num));
    /* Copy message */
    c_uc_w2s_strncpy(w2s_str,MENU_TEXT(MLM_MENU_KEY_SCAN_ANLG_CH),
                     ui4_len - c_uc_w2s_strlen(w2s_str));
    c_uc_w2s_strncat(w2s_str, _TEXT("  "),
                     ui4_len - c_uc_w2s_strlen(w2s_str));

    /* Append Analog Channels */
    _itoa(w2s_num, t_scan_info_atv.i4_vir_ch_num, 9);

    c_uc_w2s_strncat(w2s_str, w2s_num,
                     ui4_len - c_uc_w2s_strlen(w2s_str));

    i4_ret = c_wgl_do_cmd(t_scan_common_item[SCAN_COMMON_ITEM_ANALOG_CH].h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          (VOID*)0xFFFF);
    MENU_LOG_ON_FAIL(i4_ret);
    /* Append Digital Channels */
    ui4_len = 128;
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(w2s_num, 0, sizeof(w2s_num));

    /* Copy message */
    c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_SCAN_DIG_CH),
                     ui4_len - c_uc_w2s_strlen(w2s_str));
    c_uc_w2s_strncat(w2s_str, _TEXT("  "),
                     ui4_len - c_uc_w2s_strlen(w2s_str));

    _itoa(w2s_num, t_scan_info_dtv.i4_vir_ch_num, 9);

    c_uc_w2s_strncat(w2s_str, w2s_num,
                     ui4_len - c_uc_w2s_strlen(w2s_str));

    i4_ret = c_wgl_do_cmd(t_scan_common_item[SCAN_COMMON_ITEM_DIG_CH].h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          (VOID*)0xFFFF);
    MENU_LOG_ON_FAIL(i4_ret);

    /* disable the animation timer */
    c_timer_stop(h_timer_ani);

    i4_ret = c_wgl_do_cmd(h_txt_info_2,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SCAN_DONE)),
                          (VOID*)0xFFFF);
    MENU_CHK_FAIL(i4_ret);

    i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BTN_DONE]);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE)));
#endif

    /* enable the menu timer */
    menu_timer_enable(TRUE);
    menu_timer_start();

    DBG_INFO(("<MENU>Finish to scan\r\n"));

#ifdef CLI_SUPPORT
    /* notify the CLI command */
    c_sema_unlock(h_sema_bin);
#endif

    /* channel scan status */
    a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _start_scan
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
static INT32 _start_scan(VOID)
{
    INT32       i4_ret;
    SB_COND_T   e_cond;
    UINT16      ui2_start;
    UINT16      ui2_end;
    BOOL        b_fix = FALSE;

    if (b_scan)
    {
        DBG_ERROR(("<MENU> It's scanning!\n"));
        return MENUR_FAIL;
    }

    i4_ret =_change_view(RANG_SCAN_VIEW_SCAN);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BTN_CANCEL]);
    MENU_LOG_ON_FAIL(i4_ret);

    /* find the start and end physical frequency */
    ui2_start = _eb_from_to_get_value(h_eb_from);
    ui2_end   = _eb_from_to_get_value(h_eb_to);

    if (ui2_start > ui2_end)
    {
        UINT16 ui2_temp;
        ui2_temp = ui2_start;
        ui2_start = ui2_end;
        ui2_end = ui2_temp;
        b_fix = TRUE;
    }

    if (ui2_start < ui2_phy_ch_min)
    {
        ui2_start = ui2_phy_ch_min;
        b_fix = TRUE;
    }

    if (ui2_start > ui2_phy_ch_max)
    {
        ui2_start =  ui2_phy_ch_max;
        b_fix = TRUE;
    }

    if (ui2_end < ui2_phy_ch_min)
    {
        ui2_end = ui2_phy_ch_min;
        b_fix = TRUE;
    }

    if (ui2_end > ui2_phy_ch_max)
    {
        ui2_end =  ui2_phy_ch_max;
        b_fix = TRUE;
    }

    if (b_fix)
    {
        _eb_from_to_set_value(h_eb_from, ui2_start,FALSE);
        _eb_from_to_set_value(h_eb_to, ui2_end,FALSE);
        i4_ret = c_wgl_repaint(h_eb_from, NULL, TRUE);
        MENU_CHK_FAIL(i4_ret);
        i4_ret = c_wgl_repaint(h_eb_to, NULL, TRUE);
        MENU_CHK_FAIL(i4_ret);
    }

    /*reset digital channels's mask*/
    i4_ret = a_menu_channel_partial_scan_reset_svl_by_mask(ui2_start,ui2_end);
    MENU_CHK_FAIL(i4_ret);

    /* close service context */
    i4_ret = c_svctx_sync_stop_svc(menu_get_crnt_svctx(),
                                   DEFAULT_STOP_SVC_TIMEOUT);
    if (i4_ret == SVCTXR_TIMEOUT)
    {
        DBG_ERROR(("<MENU>Cannot close service context timeout. \r\n"));
        _on_start_scan_fail();
        return MENUR_FAIL;
    }
    else if (i4_ret != SVCTXR_OK && i4_ret != SVCTXR_ALREADY_STOPPED)
    {
        DBG_ERROR(("<MENU>Cannot close service context. %d\r\n", i4_ret));
        _on_start_scan_fail();
        return MENUR_FAIL;
    }

    /* Start scan the ATV channels*/
    if(ui2_scan_mode & SCAN_MODE_ATV)
    {
        t_scan_info_atv.b_done = FALSE;
        if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
        {
            SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

            DBG_INFO(("<MENU>Scan Mode: NTSC/AIR\r\n"));

            /* udpate the sink name to builder */
            menu_atsc_update_sb_snk_name(t_g_menu_atsc.h_sb_anlg_air,
                                         menu_get_crnt_svctx());

            /* start scan */
            c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

            t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_TER_FREQ_PLAN;
            t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_ntsc_scan_data.ui2_start_idx = ui2_start;
            t_ntsc_scan_data.ui2_end_idx   = ui2_end;

            t_scan_info_atv.h_builder = t_g_menu_atsc.h_sb_anlg_air;

            i4_ret = c_sb_start_scan(t_g_menu_atsc.h_sb_anlg_air,
                                     &t_ntsc_scan_data,
                                     &t_scan_info_atv,
                                     _scan_nfy_fct,
                                     &e_cond);
        }
        else
        {
            SB_NTSC_SCAN_DATA_T t_ntsc_scan_data;

            DBG_INFO(("<MENU>Scan Mode: NTSC/CABLE\r\n"));

            /* udpate the sink name to builder */
            menu_atsc_update_sb_snk_name(t_g_menu_atsc.h_sb_anlg_cable,
                                         menu_get_crnt_svctx());

            /* start scan */
            c_memset(&t_ntsc_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

            t_ntsc_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
            t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_ntsc_scan_data.ui2_start_idx = ui2_start;
            t_ntsc_scan_data.ui2_end_idx   = ui2_end;

            t_scan_info_atv.h_builder = t_g_menu_atsc.h_sb_anlg_cable;

            i4_ret = c_sb_start_scan(t_g_menu_atsc.h_sb_anlg_cable,
                                     &t_ntsc_scan_data,
                                     &t_scan_info_atv,
                                     _scan_nfy_fct,
                                     &e_cond);
        }

        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Can't start scan\r\n"));
            _on_start_scan_fail();
            return MENUR_FAIL;
        }
    }
    else
    {
        /* No ATV scan request */
        t_scan_info_atv.b_done = TRUE;
    }

    /* Start scan the DTV channels*/
    if(ui2_scan_mode & SCAN_MODE_DTV)
    {
        t_scan_info_dtv.b_done = FALSE;

        if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
        {
            SB_ATSC_SCAN_DATA_T t_atsc_scan_data;

            DBG_INFO(("<MENU>Scan Mode: ATSC/AIR\r\n"));
            c_memset(&t_atsc_scan_data, 0, sizeof(SB_ATSC_SCAN_DATA_T));
            t_atsc_scan_data.e_scan_type   = SB_ATSC_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_atsc_scan_data.ui4_scan_info = _SET_SCANE(ui2_start, ui2_end);

            t_scan_info_dtv.h_builder = t_g_menu_atsc.h_sb_dig_air;

            i4_ret = c_sb_start_scan(t_g_menu_atsc.h_sb_dig_air,
                                     &t_atsc_scan_data,
                                     &t_scan_info_dtv,
                                     _scan_nfy_fct,
                                     &e_cond);
        }
        else
        {
            SB_CQAM_SCAN_DATA_T t_cqam_scan_data;
            UINT8               ui1_freq;
            UINT32              ui4_mod;

            DBG_INFO(("<MENU>Scan Mode: ATSC/CABLE\r\n"));

            i4_ret = _get_freq_plan(&ui1_freq, &ui4_mod);
            if (i4_ret != MENUR_OK)
            {
                DBG_ERROR(("<MENU>Wrong frequency plan mode\r\n"));
                _on_start_scan_fail();
                return MENUR_FAIL;
            }

            DBG_INFO(("<MENU>Use CQAM mode to start scan\r\n"));
            c_memset(&t_cqam_scan_data, 0, sizeof(SB_CQAM_SCAN_DATA_T));
            t_cqam_scan_data.e_scan_type   = SB_CQAM_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_cqam_scan_data.ui4_scan_info = _SET_SCANE(ui2_start, ui2_end);
            t_cqam_scan_data.ui1_freq_plan = ui1_freq;
            t_cqam_scan_data.ui4_mod_mask  = ui4_mod;

            t_scan_info_dtv.h_builder = t_g_menu_atsc.h_sb_dig_cable;

            i4_ret = c_sb_start_scan(t_g_menu_atsc.h_sb_dig_cable,
                                     &t_cqam_scan_data,
                                     &t_scan_info_dtv,
                                     _scan_nfy_fct,
                                     &e_cond);
        }
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Can't start scan\r\n"));
            _on_start_scan_fail();
            return MENUR_FAIL;
        }
    }
    else
    {
        /* No DTV scan request */
        t_scan_info_dtv.b_done = TRUE;
    }

    /* set up the dirty flags for storing SVL and TSL */
    if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
    {
        t_g_menu_common.b_svl_air_dirty = TRUE;
        t_g_menu_common.b_tsl_air_dirty = TRUE;
    }
    else
    {
        t_g_menu_common.b_svl_cable_dirty = TRUE;
        t_g_menu_common.b_tsl_cable_dirty = TRUE;
    }

    /* Init the scan relative data */
    b_scan = TRUE;
    b_scaned = TRUE;
    /* Menu is in scanning status */
    t_g_menu_is_scanning = TRUE;
    /* Broadcast the message to disable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to disable the EAS.\r\n"));
    a_amb_channel_scan_active(TRUE);

    t_scan_info_atv.i4_vir_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_ttl = 200;  /* assign a big enough value */
    t_scan_info_dtv.i4_vir_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_ttl = 200;  /* assign a big enough value */

    /* set the corresponding widget */
    i4_ret = _txt_info_animate_update(FALSE);
    if(i4_ret < 0)
    {
       DBG_ERROR(("<MENU> Can't change scan text\r\n"));
    }

    i4_ret=c_wgl_do_cmd(t_range_item.h_range,
                 WGL_CMD_PG_SET_POS,
                 WGL_PACK((INT32)0),
                 NULL);
   MENU_LOG_ON_FAIL(i4_ret);

   i4_ret = c_wgl_do_cmd(t_range_item.h_txt_prog,
                         WGL_CMD_TEXT_SET_TEXT,
                         WGL_PACK(_TEXT("0 %")),
                         (VOID*)0xFFFF);
   MENU_LOG_ON_FAIL(i4_ret);

    /* change the info in help list */
    menu_atsc_help_show_scanning();

    i4_ret = c_wgl_set_focus(h_lb_btn,WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_repaint();
    if(i4_ret < 0)
    {
       DBG_ERROR(("<MENU> Can't repaint\r\n"));
    }

    /* enable the animation timer */
    i4_ret = c_timer_start(h_timer_ani,
                           1000,
                           X_TIMER_FLAG_REPEAT,
                           _timer_animation_fct,
                           NULL);
    if(i4_ret < 0)
    {
       DBG_ERROR(("<MENU> Can't start animation timer \r\n"));
    }

    /* disable the menu timer */
    menu_timer_enable(FALSE);
    menu_timer_stop();

    DBG_INFO(("<MENU>Start to scan\r\n"));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _cancel_scan
 *
 * Description:
 *    This API is called when the user cancel the process by remote controller,
 * or the menu is paused somewhere.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cancel_scan(VOID)
{
    INT32 i4_ret;

    if(b_scan)
    {
        if(t_scan_info_atv.b_done == FALSE)
        {
            if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
            {
                i4_ret = c_sb_cancel_scan(t_g_menu_atsc.h_sb_anlg_air);
            }
            else
            {
                i4_ret = c_sb_cancel_scan(t_g_menu_atsc.h_sb_anlg_cable);
            }
            if (i4_ret < 0)
            {
                DBG_ERROR(("<MENU>Can't cancel analog scan\r\n"));
            }
        }

        if(t_scan_info_dtv.b_done == FALSE)
        {
            if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
            {
                i4_ret = c_sb_cancel_scan(t_g_menu_atsc.h_sb_dig_air);
            }
            else
            {
                i4_ret = c_sb_cancel_scan(t_g_menu_atsc.h_sb_dig_cable);
            }
            if (i4_ret < 0)
            {
                DBG_ERROR(("<MENU>Can't cancel scan\r\n"));
                return MENUR_FAIL;
            }
        }

        _on_scan_stop(MENU_TEXT(MLM_MENU_KEY_SCAN_START));
    }

    i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BTN_DONE]);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static VOID _do_scan_nfy(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    INT32 i4_ret;
    ADV_SCAN_NFY_T* pt_scan_nfy = (ADV_SCAN_NFY_T*)pv_data;
    ADV_SCAN_INFO_T* pt_scan_info = (ADV_SCAN_INFO_T*)pt_scan_nfy->pv_nfy_tag;
    INT32   i4_progress;
    CHAR    ac_str[20]={0};
    UTF16_T w2s_dst[40]={0};

    /* one notify one progress */
    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_PROGRESS)
    {
        if (b_scan)
        {
            BOOL b_paint_info = (_GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data) > 0);

            pt_scan_info->i4_phy_ch_ttl  = _GET_PHY_CH_NUM(pt_scan_nfy->i4_nfy_data);
            pt_scan_info->i4_vir_ch_num += _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data);
            pt_scan_info->i4_phy_ch_num += 1;

            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                DBG_ERROR(("<MENU>ph_ch_num > ph_ch_ttl!:%d,%d\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl));
                pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
            }

            i4_progress = _calc_progress();

            i4_ret=c_wgl_do_cmd(t_range_item.h_range,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK((INT32) i4_progress),
                         NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_sprintf(ac_str,"%d %%",(UINT8)i4_progress);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_uc_ps_to_w2s(ac_str,w2s_dst,40);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(t_range_item.h_txt_prog,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  (VOID*)w2s_dst,
                                  (VOID*)0xFFFF);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_wgl_repaint(t_range_item.h_frm,
                          NULL,
                          FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            if (b_paint_info)
            {
                _txt_info_animate_update(TRUE);
            }
            else
            {

            }

            DBG_INFO(("<MENU>Scan %d/%d: %d channels found.\r\n",
                      pt_scan_info->i4_phy_ch_num, pt_scan_info->i4_phy_ch_ttl, pt_scan_info->i4_vir_ch_num));
        }
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE)
    {
        pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_CANCEL)
    {
        /* do nothing */
    }

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_ABORT)
    {
        if(b_scan)
        {
            /* Abort is always triggered by svl-builder internal */
            _on_scan_stop(MENU_TEXT(MLM_MENU_KEY_SCAN_START));

            if(pt_scan_info == &t_scan_info_atv)
            {
                /* cancel the DTV one */
                c_sb_cancel_scan(t_scan_info_dtv.h_builder);
            }
            else
            {
                /* cancel the ATV one */
                c_sb_cancel_scan(t_scan_info_atv.h_builder);
            }

            menu_pm_repaint();
        }
    }


    /* Check if the builder reach "AVAILABLE" condition */
    if(pt_scan_nfy->ui4_nfy_reason & SB_REASON_COMPLETE ||
       pt_scan_nfy->ui4_nfy_reason & SB_REASON_CANCEL   ||
       pt_scan_nfy->ui4_nfy_reason & SB_REASON_ABORT    )
    {
        pt_scan_info->b_done = TRUE;

        /* make sure that both ATV/DTV scan complete */
        if(t_scan_info_atv.b_done == TRUE &&
           t_scan_info_dtv.b_done == TRUE)
        {
            if(b_scan)
            {
                /* Only when the reason is complete does the code process */
                _on_scan_stop(MENU_TEXT(MLM_MENU_KEY_SCAN_COMPLETE));
            }
            c_memset(ac_str,0,sizeof(ac_str));
            c_memset(w2s_dst,0,sizeof(w2s_dst));

            i4_progress =100;
            i4_ret=c_wgl_do_cmd(t_range_item.h_range,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK((INT32) i4_progress),
                         NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_sprintf(ac_str,"%d %%",(UINT8)i4_progress);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_uc_ps_to_w2s(ac_str,w2s_dst,40);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(t_range_item.h_txt_prog,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  (VOID*)w2s_dst,
                                  (VOID*)0xFFFF);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=c_wgl_repaint(t_range_item.h_frm,
                          NULL,
                          FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            /* Re-open SVL */
            if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID &&
                t_g_menu_common.h_svl_air == NULL_HANDLE)
            {
                i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID,
                                    NULL,
                                    NULL,
                                    &t_g_menu_common.h_svl_air);
                if (i4_ret != SVLR_OK)
                {
                    DBG_ERROR(("<MENU>Can't open SVL\r\n"));
                    t_g_menu_common.h_svl_air = NULL_HANDLE;
                }
            }
            else if (ui2_crnt_svl_id == ATSC_CABLE_SVL_ID &&
                     t_g_menu_common.h_svl_cable == NULL_HANDLE)
            {
                i4_ret = c_svl_open(ATSC_CABLE_SVL_ID,
                                    NULL,
                                    NULL,
                                    &t_g_menu_common.h_svl_cable);
                if (i4_ret != SVLR_OK)
                {
                    DBG_ERROR(("<MENU>Can't open SVL\r\n"));
                    t_g_menu_common.h_svl_cable = NULL_HANDLE;
                }
            }

            /* Select service if menu is active */
            if(menu_get_cond() == MENU_COND_HIDE ||
               menu_get_cond() == MENU_COND_SHOW)
            {
                menu_adjust_vplane();
            }

            menu_pm_repaint();
        }
    }

#ifdef TIME_MEASUREMENT
    if(pt_scan_info == &t_scan_info_atv)
    {
        TMS_END(TMS_ANA_CHL_SCAN_TIME);
    }
    else
    {
        TMS_END(TMS_DIG_CHL_SCAN_TIME);
    }
#endif
}

/*----------------------------------------------------------------------------
 * Name: _do_animation_timer
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
static VOID _do_animation_timer(VOID* pv_data,
                                SIZE_T  z_data_size)
{
    _txt_info_animate_update(TRUE);
}


/*----------------------------------------------------------------------------
 * Name: _scan_nfy_fct
 *
 * Description: The callback function of SVL Builder.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _scan_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag)
{
    INT32   i4_ret;
    ADV_SCAN_NFY_T t_scan_nfy;

    if(ui4_nfy_reason & SB_REASON_ABORT)
    {
        DBG_ERROR(("ERROR\n"));
    }

    if (menu_get_cond() != MENU_COND_NOT_INIT)
    {
        t_scan_nfy.h_builder = h_builder;
        t_scan_nfy.ui4_nfy_reason = ui4_nfy_reason;
        t_scan_nfy.i4_nfy_data = i4_nfy_data;
        t_scan_nfy.pv_nfy_tag = pv_nfy_tag;

        i4_ret = menu_async_invoke(_do_scan_nfy,
                                   &t_scan_nfy,
                                   sizeof(ADV_SCAN_NFY_T),
                                   TRUE);
        if(i4_ret < 0){
            DBG_ERROR(("<MENU>Cannot send scan notify message!\r\n"));
        }
    }
}

static INT32 _btn_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32 i4_ret;
	GL_RECT_T     t_rect = {0};
	GL_RECT_T     t_rect1 = {0};
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if(b_scaned)
        {
            i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BTN_DONE]);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BTN_START]);
            MENU_LOG_ON_FAIL(i4_ret);
        }

#ifdef APP_TTS_SUPPORT
    if (RANG_SCAN_VIEW_INIT == e_scan_view_type)
    {
        a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_START), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_START)));
    }
    else if (RANG_SCAN_VIEW_SCAN == e_scan_view_type)
    {
        if (b_scaned)
        {
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE)));
        }
    }
    else
    {
        //DO NOTHING
    }
#endif
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
            case BTN_CUSTOM_1:
            case BTN_SELECT:
            {
                if (b_scan)
                {
                    i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BTN_CANCEL]);
                    MENU_LOG_ON_FAIL(i4_ret);

                    _cancel_scan();

					/*Adjust last shadow position*/
					c_wgl_get_coords(h_txt_info_2,WGL_COORDS_SCREEN,&t_rect1);
					t_rect.i4_top = t_rect1.i4_bottom;
					t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
					t_rect.i4_left = CONTENT_X;
					t_rect.i4_right = CONTENT_X + CONTENT_H;

					menu_pm_get_last_shadow_item(&h_last_shadow_item);
					i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
					MENU_LOG_ON_FAIL(i4_ret);
					i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
					MENU_LOG_ON_FAIL(i4_ret);

                    menu_pm_repaint();
                }
                else if(b_scaned)
                {
                    menu_nav_back();
                }
                else
                {
                	/*Adjust last shadow position*/
					c_wgl_get_coords(h_txt_info_2,WGL_COORDS_SCREEN,&t_rect1);
					t_rect.i4_top = t_rect1.i4_bottom;
					t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
					t_rect.i4_left = CONTENT_X;
					t_rect.i4_right = CONTENT_X + CONTENT_H;

					menu_pm_get_last_shadow_item(&h_last_shadow_item);
					i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
					MENU_LOG_ON_FAIL(i4_ret);
					i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
					MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret=_start_scan();
                    MENU_LOG_ON_FAIL(i4_ret);
                }

            }
            return WMPR_DONE;

            case BTN_CURSOR_UP:
            {
                if(b_scaned)
                {
                    i4_ret=c_wgl_set_focus(h_backbar,WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else if(!b_scan)
                {
                    i4_ret=c_wgl_set_focus(h_eb_to,WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                i4_ret=menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_CURSOR_DOWN:
            {
                if(!b_scan)
                {
                    i4_ret=menu_help_tip_keytip_set_focus(h_lb_btn,0,TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                i4_ret=menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_RETURN :
            {
                menu_nav_back();
            }
            break;

            default:
            {
            }
            break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _widgets_proc_fct
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
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32  i4_ret;

    switch (ui4_msg)
   {
        case WGL_MSG_GET_FOCUS:
        {
           if(h_widget == h_lb_mode)
           {
               i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_MODE]);
               MENU_LOG_ON_FAIL(i4_ret);
           }
           else if(h_widget == h_eb_from)
           {
               i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_FROM]);
               MENU_LOG_ON_FAIL(i4_ret);
           }
           else if(h_widget == h_eb_to)
           {
               i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_TO]);
               MENU_LOG_ON_FAIL(i4_ret);
           }
        }
        break;

        case WGL_MSG_LOSE_FOCUS:
        {
           if(h_widget == h_lb_mode)
           {
               i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BACKBAR]);
               MENU_LOG_ON_FAIL(i4_ret);
           }
        }
        break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    if(b_scan)
                    {
                        _cancel_scan();
                        menu_pm_repaint();

                        return WMPR_DONE;
                    }
                    else if(b_scaned)
                    {
                        menu_nav_back();
                    }
                    else if(h_lb_mode==h_widget)
                    {
                        i4_ret = _change_view(RANG_SCAN_VIEW_LB_MODE_EX);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else if(h_eb_from==h_widget)
                    {
                        i4_ret = c_wgl_set_focus(h_eb_to,WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else if(h_eb_to==h_widget)
                    {
                        i4_ret = c_wgl_set_focus(h_lb_btn,WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                }
                break;

                case BTN_RETURN :
                {
                    if(!b_scan)
                    menu_nav_back();
                }
                break;
            }

        }
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _get_idx_by_scan_mode
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_idx_by_scan_mode(UINT16 ui2_scan_mode,
                                 UINT16 *pui2_idx)
{
    switch(ui2_scan_mode)
    {
        case SCAN_MODE_ATV_DTV:
        {
            *pui2_idx = 0;
        }
        break;

        case SCAN_MODE_ATV:
        {
            *pui2_idx = 1;
        }
        break;

        case SCAN_MODE_DTV:
        {
            *pui2_idx = 2;
        }
        break;

        default:
        {
            *pui2_idx = 0;
        }
        break;
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _get_scan_mode_by_idx
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _set_scan_mode_by_idx(UINT16 ui2_idx)
{
    switch(ui2_idx)
    {
        case 0:
        {
            ui2_scan_mode = SCAN_MODE_ATV_DTV;
        }
        break;

        case 1:
        {
            ui2_scan_mode = SCAN_MODE_ATV;
        }
        break;

        case 2:
        {
            ui2_scan_mode = SCAN_MODE_DTV;
        }
        break;

        default:
        {
            ui2_scan_mode = SCAN_MODE_ATV_DTV;
        }
        break;
    }


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_from_to_proc_fct
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
static INT32 _lb_mode_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        i4_ret=_get_idx_by_scan_mode(ui2_scan_mode,
                                    &ui2_idx);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=menu_list_set_idx(h_widget, ui2_idx);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=menu_list_adjust_rect(h_lb_mode);
        MENU_LOG_ON_FAIL(i4_ret);

        c_wgl_repaint(h_widget, NULL, TRUE);

    #ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_msg[64] = {0};

        c_memset(w2s_msg, 0, sizeof(UTF16_T)*(64));
        c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE));
        c_uc_w2s_strcat(w2s_msg, _TEXT("."));
        c_uc_w2s_strcat(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE_0+ui2_idx));

        a_app_tts_play(w2s_msg, c_uc_w2s_strlen(w2s_msg));
    #endif
    }

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        {
            switch(ui2_scan_mode)
            {
            case SCAN_MODE_ATV_DTV:
                ui2_scan_mode = SCAN_MODE_DTV;
                ui2_idx = 2;
                break;
            case SCAN_MODE_ATV:
                ui2_scan_mode = SCAN_MODE_ATV_DTV;
                ui2_idx = 0;
                break;
            case SCAN_MODE_DTV:
                ui2_scan_mode = SCAN_MODE_ATV;
                ui2_idx = 1;
                break;
            default:
                ui2_scan_mode = SCAN_MODE_ATV_DTV;
                ui2_idx = 0;
                break;
            }
            menu_list_set_idx(h_widget, ui2_idx);

            i4_ret=menu_list_adjust_rect(h_lb_mode);
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(h_widget, NULL, TRUE);

        #ifdef APP_TTS_SUPPORT
            UTF16_T     w2s_msg[64] = {0};

            c_memset(w2s_msg, 0, sizeof(UTF16_T)*(64));
            c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE_0+ui2_idx));

            a_app_tts_play(w2s_msg, c_uc_w2s_strlen(w2s_msg));
        #endif

            return  WGLR_OK;
        }
        case BTN_CURSOR_RIGHT:
        {
            switch(ui2_scan_mode)
            {
            case SCAN_MODE_ATV_DTV:
                ui2_scan_mode = SCAN_MODE_ATV;
                ui2_idx = 1;
                break;
            case SCAN_MODE_ATV:
                ui2_scan_mode = SCAN_MODE_DTV;
                ui2_idx = 2;
                break;
            case SCAN_MODE_DTV:
                ui2_scan_mode = SCAN_MODE_ATV_DTV;
                ui2_idx = 0;
                break;
            default:
                ui2_scan_mode = SCAN_MODE_ATV_DTV;
                ui2_idx = 0;
                break;
            }
            menu_list_set_idx(h_widget, ui2_idx);

            i4_ret=menu_list_adjust_rect(h_lb_mode);
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(h_widget, NULL, TRUE);

        #ifdef APP_TTS_SUPPORT
            UTF16_T     w2s_msg[64] = {0};

            c_memset(w2s_msg, 0, sizeof(UTF16_T)*(64));
            c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE_0+ui2_idx));

            a_app_tts_play(w2s_msg, c_uc_w2s_strlen(w2s_msg));
        #endif

            return  WGLR_OK;
        }
        default:
            break;
        }
    }
    default:
        break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _eb_from_to_proc_fct
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
static INT32 _eb_from_to_proc_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    INT32 i4_ret;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            _eb_from_to_set_value_get_focus(h_widget);
            c_wgl_repaint(h_widget, NULL, TRUE);
        }
        break;

        case WGL_MSG_LOSE_FOCUS:
        {
            BOOL b_same=FALSE;
            BOOL b_change=FALSE;
            UINT16 ui2_value = _eb_from_to_get_value(h_widget);

            if(ui2_value<ui2_phy_ch_min)
            {
                b_change = TRUE;
                ui2_value = ui2_phy_ch_min;
            }

            if(h_eb_to==h_widget)
            {
                i4_ret=_eb_check_channel_to_value(&b_same);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            if(!b_same)
            {
                i4_ret=_eb_from_to_set_value_lose_focus(h_widget,
                                                        ui2_value,
                                                        b_change);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            c_wgl_repaint(h_widget, NULL, TRUE);
        }
        break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            UINT16   z_len=0;
            switch (ui4_keycode)
            {
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
            {
                UINT16 ui2_input = (UINT16)(ui4_keycode - BTN_DIGIT_0);
                UINT16 ui2_value = _eb_from_to_get_value(h_widget);

                ui2_value = (UINT16)(ui2_value * 10 + ui2_input);

                i4_ret=c_wgl_do_cmd(h_widget,
                                    WGL_CMD_EB_GET_TEXT_LENGTH,
                                    WGL_PACK (&z_len),
                                    NULL);

                MENU_LOG_ON_FAIL(i4_ret);

                if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
                {
                    if(z_len>2)
                    {
                        ui2_value = ui2_input;
                    }
                    if((ui2_value >ui2_phy_ch_max)&&(z_len==2))
                    {
                        ui2_value=ui2_phy_ch_max;
                    }

                }
                else
                {
                    if(z_len>3)
                    {
                        ui2_value = ui2_input;
                    }

                    if((ui2_value >ui2_phy_ch_max)&&(z_len==3))
                    {
                        ui2_value=ui2_phy_ch_max;
                    }
                }
                _eb_from_to_set_value(h_widget,ui2_value,TRUE);
                c_wgl_repaint(h_widget, NULL, TRUE);

                return WMPR_DONE;
            }

            case BTN_CURSOR_LEFT:
            {
                UINT16 ui2_value = _eb_from_to_get_value(h_widget);
                UINT16 ui_i,ui_j;

                ui_i = ui2_value/100;
                ui_j = (ui2_value%100)/10;

                if(ui_j>0 || ui_i>0)
                {
                    ui2_value = ui_i*10+ui_j;
                }
                else
                {
                    ui2_value = 0;
                }

                i4_ret=_eb_from_to_set_value_left(h_widget, ui2_value);
                MENU_LOG_ON_FAIL(i4_ret);

                c_wgl_repaint(h_widget, NULL, TRUE);

                return WGLR_OK;
            }

            default:
                break;
            }
        }
    default:
        break;
    }
    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _timer_animation_fct
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
static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    menu_async_invoke(_do_animation_timer, NULL, 0, FALSE);
}

/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            MENU_CHK_FAIL (menu_nav_go_home_menu ()) ;
            return MENUR_OK ;

        case BTN_CURSOR_UP:
            /* in scan processing ,dose no allow browse channel list */
            if (b_scan)
            {
                return WMPR_DONE ;
            }
            break ;

        case BTN_CURSOR_DOWN :
            /* in scan processing ,dose no allow browse channel list */
            if (b_scan)
            {
                return WMPR_DONE ;
            }

            menu_set_focus_on_backbar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));

            break ;

         case BTN_RETURN :
         {
             menu_nav_back();
         }
         break;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
	GL_RECT_T     t_rect = {0};
	GL_RECT_T     t_rect1 = {0};
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;
	INT32			i4_ret  = 0;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[128] = {0};
        c_uc_ps_to_w2s("backbar", w2s_str, 128);
        a_app_tts_play(w2s_str, 128);
    #endif
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_RETURN :
        case BTN_SELECT :
        {
            if (b_scan)
            {
                return WMPR_DONE ;
            }

            if(RANG_SCAN_VIEW_LB_MODE_EX==e_scan_view_type)
            {
            	/*Adjust last shadow position*/
				c_wgl_get_coords(h_txt_info_2,WGL_COORDS_SCREEN,&t_rect1);
				t_rect.i4_top = t_rect1.i4_bottom;
				t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
				t_rect.i4_left = CONTENT_X;
				t_rect.i4_right = CONTENT_X + CONTENT_H;

				menu_pm_get_last_shadow_item(&h_last_shadow_item);
				i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
				MENU_LOG_ON_FAIL(i4_ret);
				i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
				MENU_LOG_ON_FAIL(i4_ret);

                MENU_LOG_ON_FAIL(_change_view(RANG_SCAN_VIEW_INIT));
            }
            else
            {
                MENU_CHK_FAIL (menu_nav_back(););
            }

            menu_pm_repaint();
            return MENUR_OK ;
        }
        case BTN_CURSOR_DOWN:
            /* in scan processing ,dose no allow browse channel list */
            if (b_scan)
            {
                return WMPR_DONE ;
            }

            if(RANG_SCAN_VIEW_INIT==e_scan_view_type)
            {
                MENU_CHK_FAIL (c_wgl_set_focus (h_lb_mode, WGL_SYNC_AUTO_REPAINT));
            }

            else if(RANG_SCAN_VIEW_LB_MODE_EX==e_scan_view_type)
            {
                MENU_LOG_ON_FAIL (c_wgl_set_focus (h_lb_mode_ex, WGL_SYNC_AUTO_REPAINT));
            }

            else
            {
                MENU_LOG_ON_FAIL (c_wgl_set_focus (h_lb_btn, WGL_SYNC_AUTO_REPAINT));
            }

            menu_pm_repaint();

            /* update help tip */
            break ;

        case BTN_CURSOR_UP :
            MENU_CHK_FAIL (menu_set_focus_on_homebar (TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));

            break ;
        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _show_init_view
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
static INT32 _show_init_view(BOOL b_repaint)
{
    INT32        i4_ret;
    GL_RECT_T    t_rect;
    INT32        i4_y;
    UINT8        ui1_align;
    UINT8        ui1_i;
	GL_RECT_T     t_rect1 = {0};
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(h_txt_info_2,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SCAN_START)),
                           (VOID*)0xFFFF);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_mode,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i=0;ui1_i<(UINT8)SCAN_COMMON_ITEM_NUM;ui1_i++)
    {
        i4_ret = c_wgl_set_visibility(t_scan_common_item[ui1_i].h_frm,WGL_SW_HIDE_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_enable(t_scan_common_item[ui1_i].h_txt,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(h_eb_from,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_to,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_range_item.h_frm,WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_enable(t_range_item.h_txt_complete,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_enable(t_range_item.h_txt_prog,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_y = ATSC_ADV_SCAN_RNG_BTN_IDX;

    ui1_align = WGL_AS_LEFT_CENTER;


    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*i4_y,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_move(h_lb_btn,&t_rect,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_btn,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_TXT_INFO_X,
                     MENU_ITEM_V_HEIGHT*i4_y,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_move(h_txt_info_2,&t_rect,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_txt_info_2,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)(UINT32)ui1_align,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_txt_info_2,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_mode_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret= c_wgl_set_focus(h_lb_mode,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

	/*Adjust last shadow position*/
	c_wgl_get_coords(h_txt_info_2,WGL_COORDS_SCREEN,&t_rect1);
	t_rect.i4_top = t_rect1.i4_bottom;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
	t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
	MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _show_scan_view
 *
 * Description:
 *  if start to scan unsuccessfully, it will show "scan error" message, and
 * callback the notify to CLI (if any).
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _show_scan_view(BOOL b_repaint)
{
    INT32        i4_ret;
    GL_RECT_T    t_rect;
    INT32        i4_y;
    UINT8        ui1_align;
    UINT8        ui1_i;
	GL_RECT_T     t_rect1 = {0};
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(h_txt_info_2,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CNCL)),
                          (VOID*)0xFFFF);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_mode,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i=0;ui1_i<(UINT8)SCAN_COMMON_ITEM_NUM;ui1_i++)
    {
        i4_ret = c_wgl_set_visibility(t_scan_common_item[ui1_i].h_frm,WGL_SW_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_enable(t_scan_common_item[ui1_i].h_txt,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(h_eb_from,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_to,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_range_item.h_frm,WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_enable(t_range_item.h_txt_complete,FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_enable(t_range_item.h_txt_prog,FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_y = ATSC_ADV_SCAN_RNG_BTN_IDX+1;

    ui1_align = WGL_AS_CENTER_CENTER;


    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*i4_y,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_move(h_lb_btn,&t_rect,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_btn,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_TXT_INFO_X-10,
                     MENU_ITEM_V_HEIGHT*i4_y,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_move(h_txt_info_2,&t_rect,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_txt_info_2,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)(UINT32)ui1_align,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_txt_info_2,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_mode_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret= c_wgl_set_focus(h_lb_btn,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

	/*Adjust last shadow position*/
	c_wgl_get_coords(h_txt_info_2,WGL_COORDS_SCREEN,&t_rect1);
	t_rect.i4_top = t_rect1.i4_bottom;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
	t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
	MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_CNCL), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_CNCL)));
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _change_view
 *
 * Description:
 *  if start to scan unsuccessfully, it will show "scan error" message, and
 * callback the notify to CLI (if any).
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _change_view(RANG_SCAN_VIEW_TYPE_T  e_view_type)
{
    INT32        i4_ret;


    e_scan_view_type = e_view_type;

    switch(e_view_type)
    {
        case RANG_SCAN_VIEW_INIT:
        {
            i4_ret=_show_init_view(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;

        case RANG_SCAN_VIEW_SCAN:
        {
            i4_ret=_show_scan_view(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;

        case RANG_SCAN_VIEW_LB_MODE_EX:
        {
            i4_ret=_show_lb_mode_ex_view(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;

        default:
        {
        }
        break;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_frm
 *
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _create_frm(HANDLE_T   h_parent,
                       GL_RECT_T *pt_rect,
                       wgl_widget_proc_fct pf_wdgt_proc,
                       HANDLE_T   *ph_handle)
{
    INT32           i4_ret;
    WGL_IMG_INFO_T  t_img_info;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)(0),
                                 (VOID*)0,
                                 ph_handle);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_handle,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret=c_wgl_set_visibility(*ph_handle,
                         WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _create_range_scan_common_item(VOID)
{
    INT32  i4_ret = 0;
    GL_RECT_T t_rect;

    /*Channel found*/
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*ATSC_ADV_SCAN_RNG_LB_MODE_IDX,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret=_create_frm(h_cnt_frm,
                       &t_rect,
                       _widgets_proc_fct,
                       &t_scan_common_item[SCAN_COMMON_ITEM_CH_FOUND].h_frm);
    MENU_LOG_ON_FAIL(i4_ret);


    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_TXT_INFO_X,
                     ATSC_ADV_SCAN_TXT_INFO_Y,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = _txt_create(t_scan_common_item[SCAN_COMMON_ITEM_CH_FOUND].h_frm,
                         &t_rect,
                         WGL_AS_LEFT_CENTER,
                         NULL,
                         &t_scan_common_item[SCAN_COMMON_ITEM_CH_FOUND].h_txt);
    MENU_CHK_FAIL(i4_ret);

    /*Dig CH*/
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*ATSC_ADV_SCAN_RNG_EB_FROM_IDX,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret=_create_frm(h_cnt_frm,
                       &t_rect,
                       _widgets_proc_fct,
                       &t_scan_common_item[SCAN_COMMON_ITEM_DIG_CH].h_frm);
    MENU_LOG_ON_FAIL(i4_ret);


    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_TXT_INFO_X,
                     ATSC_ADV_SCAN_TXT_INFO_Y,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = _txt_create(t_scan_common_item[SCAN_COMMON_ITEM_DIG_CH].h_frm,
                         &t_rect,
                         WGL_AS_LEFT_CENTER,
                         NULL,
                         &t_scan_common_item[SCAN_COMMON_ITEM_DIG_CH].h_txt);
    MENU_CHK_FAIL(i4_ret);

    /*Dig CH*/
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*ATSC_ADV_SCAN_RNG_EB_TO_IDX,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret=_create_frm(h_cnt_frm,
                       &t_rect,
                       _widgets_proc_fct,
                       &t_scan_common_item[SCAN_COMMON_ITEM_ANALOG_CH].h_frm);
    MENU_LOG_ON_FAIL(i4_ret);


    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_TXT_INFO_X,
                     ATSC_ADV_SCAN_TXT_INFO_Y,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = _txt_create(t_scan_common_item[SCAN_COMMON_ITEM_ANALOG_CH].h_frm,
                         &t_rect,
                         WGL_AS_LEFT_CENTER,
                         NULL,
                         &t_scan_common_item[SCAN_COMMON_ITEM_ANALOG_CH].h_txt);
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}

static INT32 _create_range_item(VOID)
{
    INT32  i4_ret = 0,i4_x=0;
    GL_RECT_T t_rect;
    WGL_FONT_INFO_T     t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*ATSC_ADV_SCAN_RNG_BTN_IDX,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret=_create_frm(h_cnt_frm,
                       &t_rect,
                       _widgets_proc_fct,
                       &t_range_item.h_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_x = ATSC_ADV_SCAN_RNG_PROG_TXT_W_1
           +ATSC_ADV_SCAN_RNG_PROG_TXT_DIS
           +ATSC_ADV_SCAN_RNG_PROG_TXT_W_2;

    SET_RECT_BY_SIZE(&t_rect,
                     i4_x,
                     ATSC_ADV_SCAN_RNG_PB_Y,
                     ATSC_ADV_SCAN_RNG_PB_W,
                     ATSC_ADV_SCAN_RNG_PB_H);
    /* scan progress */
    i4_ret = _pb_create(t_range_item.h_frm,
                        &t_rect,
                        NULL,
                        &t_range_item.h_range);
    MENU_CHK_FAIL(i4_ret);

    /*PB Text*/
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_SCAN_PB_CNT_INSET_L,
                     ATSC_ADV_SCAN_TXT_INFO_Y,
                     MENU_SCAN_PB_VAL_W,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = _txt_create(t_range_item.h_frm,
                         &t_rect,
                         WGL_AS_LEFT_CENTER,
                         NULL,
                         &t_range_item.h_txt_prog);
    MENU_CHK_FAIL(i4_ret);

    /*Compltet Text*/
    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_RNG_PROG_TXT_W_1,
                     ATSC_ADV_SCAN_TXT_INFO_Y,
                     ATSC_ADV_SCAN_RNG_PROG_TXT_W_2,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = _txt_create(t_range_item.h_frm,
                         &t_rect,
                         WGL_AS_LEFT_CENTER,
                         NULL,
                         &t_range_item.h_txt_complete);
    MENU_CHK_FAIL(i4_ret);

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (t_range_item.h_txt_prog,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (t_range_item.h_txt_complete,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}

static INT32 _change_lang(VOID)
{
    INT32  i4_ret = 0;
    UINT8  ui1_i;
    UINT16  ui2_i;
    UINT16  ui2_elem_num=0;
    UINT16 aui2_mlm[]={MLM_MENU_KEY_SCAN_CH_FOUND_2,
                       MLM_MENU_KEY_SCAN_DIG_CH,
                       MLM_MENU_KEY_SCAN_ANLG_CH};

    i4_ret=menu_list_chg_lang(h_lb_mode,
                       MLM_MENU_KEY_ATSC_ASR_MODE,
                       MLM_MENU_KEY_ATSC_ASR_MODE_0,
                       MLM_MENU_KEY_ATSC_ASR_MODE_2);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i=0;ui1_i<(UINT8)SCAN_COMMON_ITEM_NUM;ui1_i++)
    {
        i4_ret = c_wgl_do_cmd(t_scan_common_item[ui1_i].h_txt,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK(MENU_TEXT(aui2_mlm[ui1_i])),
                              (VOID*)0xFFFF);
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret=menu_edit_chg_lang(h_eb_from, MLM_MENU_KEY_ATSC_ASR_FROM);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_edit_chg_lang(h_eb_to, MLM_MENU_KEY_ATSC_ASR_TO);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_list_chg_lang(h_lb_btn,
                       MLM_MENU_KEY_EMPTY,
                       MLM_MENU_KEY_EMPTY,
                       MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_txt_info_2,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SCAN_START)),
                          (VOID*)0xFFFF);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_range_item.h_txt_complete,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SCAN_COMPLETE)),
                          (VOID*)0xFFFF);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_range_item.h_txt_complete,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SCAN_COMPLETE)),
                          (VOID*)0xFFFF);
    MENU_CHK_FAIL(i4_ret);

    i4_ret=menu_change_help_tip_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_elem_num = MLM_MENU_KEY_ATSC_ASR_MODE_2 -MLM_MENU_KEY_ATSC_ASR_MODE_0 ;
    ui2_elem_num ++;
    i4_ret=c_wgl_do_cmd(h_lb_mode_ex,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_elem_num),
                 NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_i=0;ui2_i<ui2_elem_num;ui2_i++)
    {
        i4_ret=c_wgl_do_cmd(h_lb_mode_ex,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2 (ui2_i, 0),
                     WGL_PACK(MENU_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE_0+ui2_i)));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        global functions implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _show_lb_mode_ex_view
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _show_lb_mode_ex_view(BOOL b_repaint)
{
    INT32    i4_ret;
    UINT16   ui2_i;
    UINT16   ui2_crnt_ht;
	GL_RECT_T     t_rect = {0};
	GL_RECT_T     t_rect1 = {0};
	HANDLE_T		 h_last_shadow_item = NULL_HANDLE;

    i4_ret = c_wgl_set_visibility(h_lb_mode,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_i=0;ui2_i<(UINT8)SCAN_COMMON_ITEM_NUM;ui2_i++)
    {
        i4_ret = c_wgl_set_visibility(t_scan_common_item[ui2_i].h_frm,WGL_SW_HIDE_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(h_eb_from,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_to,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_range_item.h_frm,WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_mode,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_btn,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_txt_info_2,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_lb_mode,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_crnt_ht),
                         NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_lb_mode_ex,
                      WGL_CMD_LB_HLT_ELEM_VISIBLE,
                      WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                      WGL_PACK(ui2_crnt_ht));    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_mode_ex,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret= c_wgl_set_focus(h_lb_mode_ex,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

	/*Adjust last shadow position*/
	c_wgl_get_coords(h_txt_info_2,WGL_COORDS_SCREEN,&t_rect1);
	t_rect.i4_top = GRID_H * 3 + FRAME_Y + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
	t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
	MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _lb_mode_ex_proc_fct(HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       param1,
                                VOID*       param2)
{
    INT32 i4_ret;
    UINT16 ui2_crnt_ht;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if (0xffff != ui2_lst_last_hlt)
        {
            i4_ret=c_wgl_do_cmd(h_lb_mode_ex,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(ui2_lst_last_hlt),
                             WGL_PACK(TRUE));
            MENU_LOG_ON_FAIL(i4_ret);

            ui2_lst_last_hlt = 0xffff;

            c_wgl_repaint(h_lb_mode_ex, NULL, TRUE);

        }

       i4_ret=menu_set_and_show_help_tip(apw2s_help_tip[_HELP_TIP_TYPE_BTN_LB_MODE_EX]);
       MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
       i4_ret = c_wgl_do_cmd(h_lb_mode_ex,
                             WGL_CMD_LB_GET_HLT_INDEX,
                             WGL_PACK(&ui2_crnt_ht),
                             NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        UTF16_T     w2s_msg[64] = {0};

        c_memset(w2s_msg, 0, sizeof(UTF16_T)*(64));
        c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE_0+ui2_crnt_ht));

        a_app_tts_play(w2s_msg, c_uc_w2s_strlen(w2s_msg));
    #endif
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
            case BTN_CUSTOM_1:
            case BTN_SELECT:
            {
                i4_ret = c_wgl_do_cmd(h_lb_mode_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret=_set_scan_mode_by_idx(ui2_crnt_ht);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = _change_view(RANG_SCAN_VIEW_INIT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_RETURN :
            {
                i4_ret = _change_view(RANG_SCAN_VIEW_INIT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_CURSOR_UP:
            {
                i4_ret = c_wgl_do_cmd(h_lb_mode_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if(0==ui2_crnt_ht)
                {
                    ui2_lst_last_hlt =ui2_crnt_ht;
                    i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd(h_lb_mode_ex,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }

            #ifdef APP_TTS_SUPPORT
                UTF16_T     w2s_msg[64] = {0};

                c_memset(w2s_msg, 0, sizeof(UTF16_T)*(64));
                c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE_0+ui2_crnt_ht-1));

                a_app_tts_play(w2s_msg, c_uc_w2s_strlen(w2s_msg));
            #endif

            }
            break;

            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_do_cmd(h_lb_mode_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if(2==ui2_crnt_ht)
                {
                    ui2_lst_last_hlt =ui2_crnt_ht;
                    i4_ret=menu_help_tip_keytip_set_focus(h_lb_mode_ex,0,TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    #ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT //fix DTV00607321
                    if (MENUR_INV_STATE == i4_ret)
                    {
                        return MENUR_OK;
                    }
                    #endif
                    i4_ret = c_wgl_do_cmd(h_lb_mode_ex,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                    return MENUR_OK;
                }

            #ifdef APP_TTS_SUPPORT
                UTF16_T     w2s_msg[64] = {0};

                c_memset(w2s_msg, 0, sizeof(UTF16_T)*(64));
                c_uc_w2s_strcpy(w2s_msg, MENU_TTS_TEXT(MLM_MENU_KEY_ATSC_ASR_MODE_0+ui2_crnt_ht+1));

                a_app_tts_play(w2s_msg, c_uc_w2s_strlen(w2s_msg));
            #endif
            }
            break;

            default:
            {
            }
            break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        global functions implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _creat_lb_mode_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _creat_lb_mode_ex(VOID)
{
    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_cnt_frm,
                               &t_rect,
                               _lb_mode_ex_proc_fct,
                               &t_lb_init,
                               NULL,
                               &h_lb_mode_ex);
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (h_lb_mode_ex,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 _ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;
    GL_RECT_T t_rect;

    ui4_page_id = _ui4_page_id;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret=menu_get_homebar_handle(&h_homebar);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_get_backbar_handle(&h_backbar);
    MENU_LOG_ON_FAIL(i4_ret);
    /* lb mode */
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_ADV_SCAN_RNG_LB_MODE_IDX,
                              3,
                              _lb_mode_proc_fct,
                              &h_lb_mode);
    MENU_CHK_FAIL(i4_ret);

    /* Channel Found */
    i4_ret=_create_range_scan_common_item();
    MENU_LOG_ON_FAIL(i4_ret);

    /* eb from/to */
    i4_ret = menu_edit_create_ex(h_cnt_frm,
                              ATSC_ADV_SCAN_RNG_EB_FROM_IDX,
                              _eb_from_to_proc_fct,
                              &h_eb_from);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_edit_create_ex(h_cnt_frm,
                              ATSC_ADV_SCAN_RNG_EB_TO_IDX,
                              _eb_from_to_proc_fct,
                              &h_eb_to);
    MENU_CHK_FAIL(i4_ret);

    /*h_range*/
    i4_ret=_create_range_item();
    MENU_CHK_FAIL(i4_ret);

    /*Btn*/
    i4_ret = menu_list_create_ex(h_cnt_frm,
                              ATSC_ADV_SCAN_RNG_BTN_IDX,
                              1,
                              _btn_proc_fct,
                              &h_lb_btn);
    MENU_CHK_FAIL(i4_ret);

    /*Text On btn*/
    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_TXT_INFO_X,
                     MENU_ITEM_V_HEIGHT * ATSC_ADV_SCAN_RNG_BTN_IDX,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = _txt_create(h_cnt_frm,
                         &t_rect,
                         WGL_AS_CENTER_CENTER,
                         NULL,
                         &h_txt_info_2);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_txt_info_2,WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_insert(
                    h_txt_info_2,
                    NULL_HANDLE,
                    WGL_INSERT_TOPMOST,
                    WGL_NO_AUTO_REPAINT
                    );
    MENU_CHK_FAIL(i4_ret);

    i4_ret=_creat_lb_mode_ex();
    MENU_CHK_FAIL(i4_ret);

    /* navigation */
    i4_ret = _set_nav();
    MENU_CHK_FAIL(i4_ret);

    /* timer */
    i4_ret = c_timer_create(&h_timer_ani);
    MENU_CHK_FAIL(i4_ret);

#ifdef CLI_SUPPORT
    /* semaphore */
    i4_ret = c_sema_create(&h_sema_bin,
                           X_SEMA_TYPE_BINARY,
                           X_SEMA_STATE_LOCK);
    MENU_CHK_FAIL(i4_ret);
#endif

    /* set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    apw2s_help_tip[_HELP_TIP_TYPE_HOMEBAR] = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR);
    apw2s_help_tip[_HELP_TIP_TYPE_BACKBAR] = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR);
    apw2s_help_tip[_HELP_TIP_TYPE_MODE] = MENU_TEXT(MLM_MENU_KEY_SCAN_MODE_HELP);
    apw2s_help_tip[_HELP_TIP_TYPE_FROM] = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_SCAN_RNG_START);
    apw2s_help_tip[_HELP_TIP_TYPE_TO] = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_SCAN_RNG_END);
    apw2s_help_tip[_HELP_TIP_TYPE_BTN_START] = MENU_TEXT(MLM_MENU_KEY_HELP_TIP_SCAN_START);
    apw2s_help_tip[_HELP_TIP_TYPE_BTN_CANCEL] = MENU_TEXT(MLM_MENU_KEY_SCAN_BTN_HELP_2);
    apw2s_help_tip[_HELP_TIP_TYPE_BTN_DONE] = MENU_TEXT(MLM_MENU_KEY_SCAN_BTN_HELP_1);
    apw2s_help_tip[_HELP_TIP_TYPE_BTN_LB_MODE_EX] = MENU_TEXT(MLM_MENU_KEY_SCAN_MODE_HELP);
    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32 i4_ret;
	GL_RECT_T     t_rect = {0};
	GL_RECT_T     t_rect1 = {0};
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;

    ui2_scan_mode = SCAN_MODE_ATV_DTV;

    i4_ret = menu_show_homebar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_show_backbar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    /* reset values */
    a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);

    /* title */
    menu_main_set_title(MLM_MENU_KEY_ATSC_ASR);

    /* change the info in help list */
    menu_atsc_help_show_scan();

    /* lb mode */
    menu_list_set_idx(h_lb_mode, 0);

    /* eb from/to */
    if(ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
    {
        ui2_phy_ch_min  = PHY_TRSTRL_CH_NUM_MIN;
        ui2_phy_ch_max  = PHY_TRSTRL_CH_NUM_MAX;
    }
    else
    {
        ui2_phy_ch_min  = PHY_CABLE_CH_NUM_MIN;
        ui2_phy_ch_max  = PHY_CABLE_CH_NUM_MAX;
    }

    _eb_from_to_set_value(h_eb_from,
                          ui2_phy_ch_min,
                          FALSE);

    _eb_from_to_set_value(h_eb_to,
                          ui2_phy_ch_max,
                          FALSE);

    /* pb progress */
    i4_ret=c_wgl_do_cmd(t_range_item.h_range,
                 WGL_CMD_PG_SET_POS,
                 WGL_PACK((INT32)0),
                 NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(t_range_item.h_txt_prog,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(_TEXT("0 %")),
                          (VOID*)0xFFFF);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =_change_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_list_adjust_rect(h_lb_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =_change_view(RANG_SCAN_VIEW_INIT);
    MENU_LOG_ON_FAIL(i4_ret);

	/*Adjust last shadow position*/
	c_wgl_get_coords(h_txt_info_2,WGL_COORDS_SCREEN,&t_rect1);
	t_rect.i4_top = t_rect1.i4_bottom;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
	t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_help_tip_keytip_show(FALSE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32  i4_ret = 0;
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;

    /* Menu is not in scanning status */
    t_g_menu_is_scanning = FALSE;

    /* Broadcast the message to enable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to enable the EAS.\r\n"));
    a_amb_channel_scan_active(FALSE);

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_help_tip_keytip_show(TRUE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    //INT32 i4_ret;
    b_scan = FALSE;
    b_scaned = FALSE;

    /* set callback function for homebar */
    menu_set_homebar_proc (_homebar_proc_fct) ;

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    //c_wgl_set_focus(h_lb_mode, WGL_NO_AUTO_REPAINT);

    //i4_ret=menu_list_adjust_rect(h_lb_mode);
    //MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    if (b_scan)
    {
        _cancel_scan();
    }

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret =_change_lang();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

extern INT32 menu_atsc_page_adv_scan_rng_init(VOID)
{
    t_g_menu_atsc_page_adv_scan_rng.pf_menu_page_create =    _on_page_create;
    t_g_menu_atsc_page_adv_scan_rng.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_atsc_page_adv_scan_rng.pf_menu_page_show=       _on_page_show;
    t_g_menu_atsc_page_adv_scan_rng.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_atsc_page_adv_scan_rng.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_atsc_page_adv_scan_rng.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_atsc_page_adv_scan_rng.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

static INT32 a_menu_channel_partial_scan_reset_svl_by_mask(UINT16 ui2_start_channel,
                                                           UINT16 ui2_end_channel)
{
    INT32       i4_result = 0;
    INT32       i4_ret = APP_CFGR_OK;
    UINT32      ui4_lst_mask = SB_VNET_ALL;
    UINT16      ui2_idx = 0;
    UINT16      ui2_rec_num = 0;
    UINT16*     aui2_rec_id;
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    SVL_REC_T   t_svl_rec = {0};
    UINT32      ui4_channel_id = 0;
    UINT16      ui2_major = 0;
    HANDLE_T    h_svl = menu_get_crnt_svl ();

    /* lock SVL */
    i4_result = c_svl_lock(h_svl);

    if(i4_result != SVLR_OK)
    {
        i4_ret = APP_CFGR_INTERNAL_ERR;
        DBG_ERROR(("<MENU> Can't lock SVL.\r\n"));
    }
    else
    {
        i4_result = c_svl_get_num_rec_by_brdcst_type(h_svl,
                                                     BRDCST_TYPE_UNKNOWN,
                                                     ui4_lst_mask,
                                                     &ui2_rec_num,
                                                     &ui4_ver_id);
        if(i4_result != SVLR_OK)
        {
            DBG_ERROR(("<MENU> Can't get record number.\r\n"));
            i4_ret = APP_CFGR_INTERNAL_ERR;
        }
        else
        {
           /* Due to the bug in SVL, we use the two iteration work-around
            solution. In the first iteration, we store the svl record to
            an array; and the second iteration, we make use of these ids
            to update records. */
            aui2_rec_id = (UINT16*) c_mem_alloc(ui2_rec_num * sizeof(UINT16));
            if(aui2_rec_id == NULL)
            {
                i4_ret = APP_CFGR_INTERNAL_ERR;
            }
            else
            {
                /* Iter 1: Get all record id. (readonly iteration) */
                for(ui2_idx=0; ui2_idx<ui2_rec_num; ui2_idx++)
                {
                    i4_result = c_svl_get_rec_by_brdcst_type(h_svl,
                                                             BRDCST_TYPE_UNKNOWN,
                                                             ui4_lst_mask,
                                                             ui2_idx,
                                                             &t_svl_rec,
                                                             &ui4_ver_id);
                     if(i4_result != SVLR_OK)
                     {
                         i4_ret = APP_CFGR_INTERNAL_ERR;
                         DBG_ERROR(("<MENU> Can't iterate service list at idx=%d.\r\n",
                                     ui2_idx));
                         break;
                      }
                         aui2_rec_id[ui2_idx] = t_svl_rec.ui2_svl_rec_id;
                 }

                 /* Iter 2: Get the record by record id and update it */
                 for (ui2_idx=0;
                      ui2_idx<ui2_rec_num && i4_ret == APP_CFGR_OK;
                      ui2_idx++)
                 {
                     i4_result = c_svl_get_rec(h_svl,
                                               aui2_rec_id[ui2_idx],
                                               &t_svl_rec,
                                               &ui4_ver_id);
                     if(i4_result != SVLR_OK)
                     {
                         i4_ret = APP_CFGR_INTERNAL_ERR;
                         DBG_ERROR(("<MENU> Can't get record %d.\r\n",
                                    aui2_rec_id[ui2_idx]));
                         break;
                      }

                      if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
                      {
                          continue;
                      }

                      ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
                      ui2_major = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
                      if ((ui2_major >= ui2_start_channel)&&
                          ( ui2_major<= ui2_end_channel))
                    {

                        if ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE) == 0)
                        {
                            t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_VISIBLE;

                            i4_result = c_svl_update_rec(h_svl,
                                                        &t_svl_rec,
                                                        TRUE);
                            if (i4_result != SVLR_OK)
                            {
                                DBG_ERROR(("<MENU> Can't update record: %d < %d.\r\n",
                                t_svl_rec.ui2_svl_rec_id));
                            }

                        }

                    }
                } /* end of Iteration  */

            c_mem_free(aui2_rec_id);
            } /* c_mem_alloc */
        }
        c_svl_unlock(h_svl);
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
                    CLI relative fucntion
 ----------------------------------------------------------------------------*/
#ifdef CLI_SUPPORT

typedef struct _CMD_START_SCAN_T
{
    UINT16  ui2_ch_from;
    UINT16  ui2_ch_to;
    UINT16  ui2_scan_mode;
}   CMD_START_SCAN_T;


static VOID _do_cli_rscan_start(VOID* pv_data,
                                SIZE_T  z_data_size)
{
    CMD_START_SCAN_T*   pt_scan_cmd = (CMD_START_SCAN_T*)pv_data;
    MENU_PAGE_STATE_T   e_state;


    if(menu_get_cond() != MENU_COND_SHOW)
    {
        return;
    }

    menu_page_get_state(ui4_page_id, &e_state);
    if(e_state != MENU_PAGE_STATE_FOCUS)
    {
        /* navigate to range scan page */
        menu_nav_go(ui4_page_id, NULL);
    }

    _eb_from_to_set_value(h_eb_from, pt_scan_cmd->ui2_ch_from,FALSE);
    _eb_from_to_set_value(h_eb_to, pt_scan_cmd->ui2_ch_to,FALSE);
    ui2_scan_mode = pt_scan_cmd->ui2_scan_mode;
    if(ui2_scan_mode == SCAN_MODE_ATV_DTV)
    {
        menu_list_set_idx(h_lb_mode, 0);
    }
    else if(ui2_scan_mode == SCAN_MODE_ATV)
    {
        menu_list_set_idx(h_lb_mode, 1);
    }
    else
    {
        menu_list_set_idx(h_lb_mode, 2);
    }
    menu_pm_repaint();

    _start_scan();
}

INT32 menu_atsc_cli_rscan(INT32        i4_argc,
                          const CHAR** pps_argv)
{
    const UINT32        ui4_cli_wait_max = 60 * 60 * 1000; /* 1HR */

    INT32               i4_ret;
    CMD_START_SCAN_T    t_scan_cmd;
    CHAR*               ps_help = "rscan (ad/a/d) (from) (to) (loop) (wait)\n";
    UINT32              ui4_value;
    UINT16              ui2_loop;
    UINT32              ui4_wait;
    UINT16              ui2_i;

    UINT32              ui4_ts_start;
    UINT32              ui4_ts_end;
    UINT32              ui4_ts_dur;

    if(i4_argc != 6)
    {
        DBG_LOG_PRINT((ps_help));
        return -1;
    }

    /* scan mode */
    if(c_strcmp(pps_argv[1], "ad") == 0)
    {
        t_scan_cmd.ui2_scan_mode = SCAN_MODE_ATV_DTV;
    }
    else if(c_strcmp(pps_argv[1], "a") == 0)
    {
        t_scan_cmd.ui2_scan_mode = SCAN_MODE_ATV;
    }
    else if(c_strcmp(pps_argv[1], "d") == 0)
    {
        t_scan_cmd.ui2_scan_mode = SCAN_MODE_DTV;
    }
    else
    {
        DBG_LOG_PRINT((ps_help));
        return -1;
    }

    /* from, to */
    ui4_value = (UINT32)c_strtoull(pps_argv[2], NULL, 10);
    t_scan_cmd.ui2_ch_from  = (UINT16)ui4_value;

    ui4_value = (UINT32)c_strtoull(pps_argv[3], NULL, 10);
    t_scan_cmd.ui2_ch_to    = (UINT16)ui4_value;

    /* loop */
    ui4_value = (UINT32)c_strtoull(pps_argv[4], NULL, 10);
    ui2_loop = (UINT16)ui4_value;

    /* wait */
    ui4_value = (UINT32)c_strtoull(pps_argv[5], NULL, 10);
    ui4_wait = ui4_value;

    for(ui2_i = 0; ui2_i<ui2_loop; ui2_i++)
    {
        DBG_INFO(("[MENU_CLI] Scan %d/%d\n", ui2_i+1, ui2_loop));
        if(menu_get_cond() != MENU_COND_SHOW)
        {
            break;
        }

        ui4_ts_start = c_os_get_sys_tick();

        menu_async_invoke(_do_cli_rscan_start,
                          &t_scan_cmd,
                          sizeof(CMD_START_SCAN_T),
                          TRUE);

        i4_ret = c_sema_lock_timeout(h_sema_bin,
                                     ui4_cli_wait_max);
        if(i4_ret == OSR_TIMEOUT)
        {
            DBG_ERROR(("[MENU_CLI] Scan timeout at %d/%d\n", ui2_i+1, ui2_loop));
            DBG_ABORT(0);
            break;
        }

        ui4_ts_end = c_os_get_sys_tick();
        ui4_ts_dur = (ui4_ts_end - ui4_ts_start) * c_os_get_sys_tick_period();

        DBG_INFO(("[MENU_CLI]Duration = %dm%ds\n", ui4_ts_dur / 60000, ui4_ts_dur % 60000 / 1000));

        c_thread_delay(ui4_wait);
    }

    DBG_LOG_PRINT(("[MENU_CLI] Scan Finish\n"));

    return CLIR_OK;
}
#endif /* CLI_SUPPORT */

#endif /* ATSC_ADV_SCAN_RNG_ENABLE */

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
 * $RCSfile: menu_page_adv_scan_sgl.c,v $
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
#include "app_util/a_tv.h"

#include "menu2/menu_util2.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_dbg.h"

#ifdef ATSC_ADV_SCAN_SGL_ENABLE
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#ifndef ATSC_ADV_SCAN_SGL_TXT_INFO_X
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_X        (20)
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_Y        (1 * GRID_H)
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_W        (CONTENT_W - 40)
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_H        (5 * GRID_H - 20)
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_T        (10)
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_B        (10)
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_L        (30)
    #define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_R        (30)
    #define ATSC_ADV_SCAN_SGL_TXT_TUNER_X       (CONTENT_W / 2)
    #define ATSC_ADV_SCAN_SGL_TXT_TUNER_Y       (1  * GRID_H + 10)
    #define ATSC_ADV_SCAN_SGL_TXT_TUNER_W       (CONTENT_W - ATSC_ADV_SCAN_SGL_TXT_TUNER_X - 50)
    #define ATSC_ADV_SCAN_SGL_TXT_TUNER_H       (1  * GRID_H)
    #define ATSC_ADV_SCAN_SGL_TXT_TUNER_ALIGN   (WGL_AS_RIGHT_TOP)
    #define ATSC_ADV_SCAN_SGL_PB_X              (50)
    #define ATSC_ADV_SCAN_SGL_PB_Y              (GRID_H * 4)
    #define ATSC_ADV_SCAN_SGL_PB_W              (CONTENT_W - ATSC_ADV_SCAN_SGL_PB_X * 2)
    #define ATSC_ADV_SCAN_SGL_PB_H              (GRID_H * 1)
    #define ATSC_ADV_SCAN_SGL_PB_VAL_W          (80)
    #define ATSC_ADV_SCAN_SGL_PB_CNT_INSET_T    (8)
    #define ATSC_ADV_SCAN_SGL_PB_CNT_INSET_B    (7)
    #define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_L    (2)
    #define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_R    (2)
    #define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_T    (2)
    #define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_B    (2)
    #define ATSC_ADV_SCAN_SGL_EB_CH_IDX         (6)
    #define ATSC_ADV_SCAN_SGL_LB_PLN_IDX        (7)
    #define ATSC_ADV_SCAN_SGL_LB_MOD_IDX        (8)
    #define ATSC_ADV_SCAN_SGL_PB_SIG_IDX        (9)
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)
#define _SET_SCAN_RANGE(start, end) ( ((start) << 16) | (end))

#define PHY_TRSTRL_CH_NUM_MIN             ((UINT16)    2)
#define PHY_TRSTRL_CH_NUM_MAX             ((UINT16)   69)

#define PHY_CABLE_CH_NUM_MIN              ((UINT16)    SB_CQAM_SCAN_FIRST_CHANNEL)
#define PHY_CABLE_CH_NUM_MAX              ((UINT16)    SB_CQAM_SCAN_LAST_CHANNEL)

#define INPUT_RESET_DELAY                 ((UINT32) 1500)
#define SIG_LVL_REFRESH_RATE              ((UINT32) 1000)

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

#define SCAN_MODE_ATV_DTV       ((UINT8) 0)
#define SCAN_MODE_ATV           ((UINT8) 1)
#define SCAN_MODE_DTV           ((UINT8) 2)

#define FRQ_PLN_STD             ((UINT8) 0)
#define FRQ_PLN_IRC             ((UINT8) 1)
#define FRQ_PLN_HRC             ((UINT8) 2)

#define MOD_Q64                 ((UINT8) 0)
#define MOD_Q256                ((UINT8) 1)
#define SYM_RATE_Q64            ((UINT32) 5056941)
#define SYM_RATE_Q256           ((UINT32) 5360537)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_adv_scan_sgl;

static HANDLE_T    h_cnt_frm;
static HANDLE_T    h_txt_info;
static HANDLE_T    h_pb;
static HANDLE_T    h_timer_ani;
static HANDLE_T    h_txt_tuner;
static HANDLE_T    h_eb_ch;
static HANDLE_T    h_lb_pln;
static HANDLE_T    h_lb_mod;
static HANDLE_T    h_pb_signal;
static HANDLE_T    h_signal_timer;

static UINT32      ui4_page_id;
static UINT16      ui2_crnt_svl_id;
static UINT16      ui2_crnt_tsl_id;
static UINT8       ui1_scan_mode;   /* scan mode, this value is always SCAN_MODE_DTV because ATV is not enabled */
static UINT8       ui1_frq_pln;     /* frequency plan */
static UINT8       ui1_modulation;         /* modulation mode */

static BOOL        b_scan;          /* is scanning */

static ADV_SCAN_INFO_T   t_scan_info_atv;
static ADV_SCAN_INFO_T   t_scan_info_dtv;

static UINT16      ui2_phy_ch_min = 0;
static UINT16      ui2_phy_ch_max = 0;
static UINT16      ui2_rf_ch = 0;

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
 * Description: Get the frequency plan setting and modulation mask
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _get_freq_plan(
    UINT8*  pui1_freq_plan,
    UINT32* pui4_mod_mask)
{
    UINT8   ui1_freq_plan;
    UINT32  ui4_mod_mask;

#ifdef APP_DCR_SUPPORT
    switch (ui1_frq_pln)
    {
      case FRQ_PLN_STD:
        ui1_freq_plan = SB_OOB_FREQ_PLAN_STD;
        break;
    case FRQ_PLN_IRC:
        ui1_freq_plan = SB_OOB_FREQ_PLAN_IRC;
        break;
    case FRQ_PLN_HRC:
        ui1_freq_plan = SB_OOB_FREQ_PLAN_HRC;
        break;
    default:
        DBG_ERROR(("<MENU>Wrong frequency plan mode: %d\r\n", ui1_frq_pln));
        return MENUR_FAIL;
    }
#else
    switch (ui1_frq_pln)
    {
    case FRQ_PLN_STD:
        ui1_freq_plan = SB_CQAM_FREQ_PLAN_STD;
        break;
    case FRQ_PLN_IRC:
        ui1_freq_plan = SB_CQAM_FREQ_PLAN_IRC;
        break;
    case FRQ_PLN_HRC:
        ui1_freq_plan = SB_CQAM_FREQ_PLAN_HRC;
        break;
    default:
        DBG_ERROR(("<MENU>Wrong frequency plan mode: %d\r\n", ui1_frq_pln));
        return MENUR_FAIL;
    }
#endif


    switch (ui1_modulation)
    {
    case MOD_Q64:
        ui4_mod_mask = MENU_MAKE_MOD_BIT_MASK(MOD_QAM_64);
        break;
    case MOD_Q256:
        ui4_mod_mask = MENU_MAKE_MOD_BIT_MASK(MOD_QAM_256);
        break;
    default:
        DBG_ERROR(("<MENU>Wrong modulation mode: %d\r\n", ui1_modulation));
        return MENUR_FAIL;
    }

    *pui1_freq_plan = ui1_freq_plan;
    *pui4_mod_mask = ui4_mod_mask;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _update_rf_ch_by_crnt_ch
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
static INT32 _update_rf_ch_by_crnt_ch()
{
    INT32   i4_ret;
    UINT32  ui4_channel_id;
    SVL_REC_T   t_svl_rec;
    UINT32  ui4_ver_id;
    HANDLE_T    h_svl;

    h_svl = menu_get_crnt_svl();

    if(h_svl == NULL_HANDLE)
    {
        ui2_rf_ch = ui2_phy_ch_min;
    }
    else
    {
        i4_ret = a_cfg_get_crnt_channel_id(&ui4_channel_id);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_svl_get_rec_by_channel(h_svl,
                                          ui4_channel_id,
                                          SB_VNET_ALL,
                                          0,
                                          &t_svl_rec,
                                          &ui4_ver_id);
        if(i4_ret == SVLR_OK)
        {
            if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
            {
                /* For analog channels, The RF channel id is the major channel id */
                ui2_rf_ch =
                    SB_ATSC_GET_MAJOR_CHANNEL_NUM(t_svl_rec.uheader.t_rec_hdr.ui4_channel_id);

            }
            else
            {
                /* For digital channels, the RF channel id is TSL record id. */
                ui2_rf_ch = SB_TSL_GET_PTC_FROM_RECID(t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id);
            }
        }
        else
        {
            ui2_rf_ch = ui2_phy_ch_min;
        }
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _atsc_cal_freq
 *
 * Description: the function to calculate the frequency according to
 *              the specified RF cannel.
 *
 * Inputs:  ui2_rf_ch    The RF channel
 *
 * Outputs: -
 *
 * Returns: 0           ui1_rf_ch exceeds the boundary.
 *          Non-zero    The frequency corresponding to the scan index.
 *
 ----------------------------------------------------------------------------*/
static UINT32 _atsc_cal_freq(UINT16 ui2_rf_ch)
{
    UINT32 ui4_freq = 0;
    /* 0 is returned if ui1_rf_ch exceeds the boundary. */

    if (ui2_rf_ch < PHY_TRSTRL_CH_NUM_MIN || ui2_rf_ch > PHY_TRSTRL_CH_NUM_MAX)
    {
        return 0;
    }
    else if (ui2_rf_ch < 5)
    {
        ui4_freq = (UINT32)ui2_rf_ch * 6 + 45 /* MHz */;
    }
    else if (ui2_rf_ch == 5)
    {
        ui4_freq = 79 /* MHz */;
    }
    else if (ui2_rf_ch == 6)
    {
        ui4_freq = 85 /* MHz */;
    }
    else if (ui2_rf_ch < 14)
    {
        ui4_freq = (UINT32)ui2_rf_ch * 6 + 135 /* MHz */;
    }
    else if (ui2_rf_ch <= PHY_TRSTRL_CH_NUM_MAX)
    {
        ui4_freq = (UINT32)ui2_rf_ch * 6 + 389 /* MHz */;
    }

    return ui4_freq * 1000000 /* Hz */;
}

/*-----------------------------------------------------------------------------
 * Name: _cqam_cal_freq
 *
 * Description: the function to calculate the frequency according to
 *              the specified scan index.
 *
 * Inputs:  ui2_rf_ch    The rf channel.
 *
 * Outputs: -
 *
 * Returns: 0           ui2_scan_idx exceeds the boundary.
 *          Non-zero    The frequency corresponding to the scan index.
 *
 ----------------------------------------------------------------------------*/
static UINT32 _cqam_calc_freq(
    UINT16 ui2_rf_ch)
{
    #define BAND_WIDTH_STD      ((UINT32) 6000000)
    #define BAND_WIDTH_IRC      BAND_WIDTH_STD
    #define BAND_WIDTH_HRC      ((UINT32) 6000300)

    switch (ui1_frq_pln)
    {
        case FRQ_PLN_STD:
            if (ui2_rf_ch == 1)
            {
                return 0;
            }
            else if (ui2_rf_ch == 5)
            {
                return 79000000;
            }
            else if (ui2_rf_ch == 6)
            {
                return 85000000;
            }

        case FRQ_PLN_IRC:
            if (ui2_rf_ch == 1)
            {
                return 75000000;
            }
            else if (ui2_rf_ch == 5)
            {
                return 81000000;
            }
            else if (ui2_rf_ch == 6)
            {
                return 87000000;
            }
            else if (ui2_rf_ch < 5)
            {
                return ((UINT32) ui2_rf_ch * BAND_WIDTH_IRC + 45000000);
            }
            else if (ui2_rf_ch < 14)
            {
                return ((UINT32) ui2_rf_ch * BAND_WIDTH_IRC + 135000000);
            }
            else if (ui2_rf_ch < 23)
            {
                return ((UINT32) ui2_rf_ch * BAND_WIDTH_IRC + 39000000);
            }
            else if (ui2_rf_ch < 95)
            {
                return ((UINT32) ui2_rf_ch * BAND_WIDTH_IRC + 81000000);
            }
            else if (ui2_rf_ch < 100)
            {
                return ((UINT32) (ui2_rf_ch - 95) * BAND_WIDTH_IRC + 93000000);
            }
            else if (ui2_rf_ch <= SB_CQAM_SCAN_LAST_CHANNEL)
            {
                return ((UINT32) ui2_rf_ch * BAND_WIDTH_IRC + 51000000);
            }
            break;

        case FRQ_PLN_HRC:
            if (ui2_rf_ch == 1)
            {
                return 73753750;
            }
            else if (ui2_rf_ch == 5)
            {
                return 79754050;
            }
            else if (ui2_rf_ch == 6)
            {
                return 85754350;
            }
            else if (ui2_rf_ch < 5)
            {
                return (((UINT32) ui2_rf_ch + 7) * BAND_WIDTH_HRC + 1750150);
            }
            else if (ui2_rf_ch < 14)
            {
                return (((UINT32) ui2_rf_ch + 22) * BAND_WIDTH_HRC + 1750150);
            }
            else if (ui2_rf_ch < 23)
            {
                return (((UINT32) ui2_rf_ch + 6) * BAND_WIDTH_HRC + 1750150);
            }
            else if (ui2_rf_ch < 95)
            {
                return (((UINT32) ui2_rf_ch + 13) * BAND_WIDTH_HRC + 1750150);
            }
            else if (ui2_rf_ch < 100)
            {
                return (((UINT32) ui2_rf_ch - 80) * BAND_WIDTH_HRC + 1750150);
            }
            else if (ui2_rf_ch <= SB_CQAM_SCAN_LAST_CHANNEL)
            {
                return (((UINT32) ui2_rf_ch + 8) * BAND_WIDTH_HRC + 1750150);
            }
            break;

        default:
            return 0;
    }

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _tune_by_rf_ch
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
static INT32 _tune_by_rf_ch(UINT16 ui2_rf_ch)
{
    INT32       i4_ret;
    SVL_REC_T   t_svl_rec;
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    HANDLE_T    h_svl;
    BOOL        b_sel_by_rec;

    h_svl = menu_get_crnt_svl();

    /* in current desing, rf_ch mode just is available in ATSC TRSTRL mode.*/
    if(h_svl == NULL_HANDLE)
    {
        b_sel_by_rec = FALSE;
    }

    ui4_ver_id = SVL_NULL_VER_ID;
    /* Find the first svl record as the selecting record (RF Channel assigned)*/

    /* Try to get digital SVL record first */
    i4_ret = c_svl_get_rec_by_ts(h_svl,
                                 ui2_crnt_tsl_id,
                                 ui2_rf_ch,
                                 SB_VNET_ALL,
                                 0,
                                 &t_svl_rec,
                                 &ui4_ver_id);

    if(i4_ret == SVLR_OK)
    {
        b_sel_by_rec = TRUE;
    }
    else
    {
        b_sel_by_rec = FALSE;
    }

    if(b_sel_by_rec)
    {
        /* select service by svl record */
        UINT32  ui4_crnt_ch;
        UINT32  ui4_last_ch;
        UINT32  ui4_tmp_ch;

        i4_ret = a_tv_change_channel(menu_get_crnt_svctx(),
                                 SVCTX_STRM_MODE_AS_LAST,
                                 t_svl_rec.uheader.t_rec_hdr.ui4_channel_id,
                                 NULL);
        MENU_CHK_FAIL(i4_ret);

        /* set back the crnt/last channel id */
        a_cfg_get_crnt_channel_id(&ui4_tmp_ch);
        ui4_last_ch = ui4_tmp_ch;
        ui4_crnt_ch = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;

        a_cfg_set_crnt_channel_id(ui4_crnt_ch);
        a_cfg_set_last_channel_id(ui4_last_ch);
    }
    else
    {
        /* select service by frequency*/
        UINT32 ui4_freq;
        UINT32 ui4_sym_rate;
        TUNER_MODULATION_T  e_mod;

        SRC_DESC_T t_src_desc;
        c_memset(&t_src_desc, 0, sizeof(SRC_DESC_T));

        if(ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
        {
            ui4_freq = _atsc_cal_freq(ui2_rf_ch);

            t_src_desc.e_type           = SRC_TYPE_BRDCST_FREQ;
            t_src_desc.ps_conn_src_type = BRDCST_HANDLER_DEFAULT_NAME;
            t_src_desc.ps_conn_src_name = ATSC_TRSTRL_TUNER_NAME;
            t_src_desc.u_info.t_freq.e_type = FREQ_INFO_TYPE_DIG_TER;
            t_src_desc.u_info.t_freq.u_data.t_dig_ter.ui4_freq = ui4_freq;
            t_src_desc.u_info.t_freq.u_data.t_dig_ter.e_mod    = MOD_VSB_8;
        }
        else
        {
            ui4_freq = _cqam_calc_freq(ui2_rf_ch);

            if(ui1_modulation == MOD_Q64)
            {
                e_mod = MOD_QAM_64;
                ui4_sym_rate = SYM_RATE_Q64;
            }
            else
            {
                e_mod = MOD_QAM_256;
                ui4_sym_rate = SYM_RATE_Q256;
            }

            t_src_desc.e_type           = SRC_TYPE_BRDCST_FREQ;
            t_src_desc.ps_conn_src_type = BRDCST_HANDLER_DEFAULT_NAME;
            t_src_desc.ps_conn_src_name = SN_MAIN_TUNER_CAB_DIG;
            t_src_desc.u_info.t_freq.e_type = FREQ_INFO_TYPE_DIG_CAB;
            t_src_desc.u_info.t_freq.u_data.t_dig_cab.ui4_freq = ui4_freq;
            t_src_desc.u_info.t_freq.u_data.t_dig_cab.e_mod    = e_mod;
            t_src_desc.u_info.t_freq.u_data.t_dig_cab.ui4_sym_rate = ui4_sym_rate;
        }

        i4_ret = c_svctx_select_svc(menu_get_crnt_svctx(),
                                    0,
                                    &t_src_desc,
                                    NULL,
                                    NULL,
                                    NULL);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _stop_analog_service
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
static VOID _stop_analog_service(VOID)
{
    INT32       i4_ret;
    SVL_REC_T   t_svl_rec;
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;

    i4_ret = c_svl_get_rec_by_channel(menu_get_crnt_svl(),
                                      a_util_cnfg_get_crnt_channel_id(),
                                      SB_VNET_ALL,
                                      0,
                                      &t_svl_rec,
                                      &ui4_ver_id);

    MENU_LOG_ON_FAIL(i4_ret);

    if(i4_ret == SVLR_REC_NOT_FOUND)
    {
        return;
    }

    if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
    {
        a_tv_stop(menu_get_crnt_svctx());
    }

}

/*----------------------------------------------------------------------------
 * Name: _get_curr_sig_lvl
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
static INT32 _get_curr_sig_lvl(UINT16* pui2_sig_lvl)
{
    INT32       i4_ret=0;
    UINT8       ui1_sig_lvl_tmp=0;

    *pui2_sig_lvl = 0;

     i4_ret = c_svctx_get_signal_level(menu_get_crnt_svctx(), &ui1_sig_lvl_tmp);

     *pui2_sig_lvl = ui1_sig_lvl_tmp;

     MENU_CHK_FAIL(i4_ret);

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
#if 0
    INT32 i4_prog_atv;
    INT32 i4_prog_dtv;

    if(t_scan_info_atv.b_done)
    {
        i4_prog_atv = 100;
    }
    else
    {
        i4_prog_atv = t_scan_info_atv.i4_phy_ch_num * 100 / t_scan_info_atv.i4_phy_ch_ttl;
    }

    if(t_scan_info_dtv.b_done)
    {
        i4_prog_dtv = 100;
    }
    else
    {
        i4_prog_dtv = t_scan_info_dtv.i4_phy_ch_num * 100 / t_scan_info_dtv.i4_phy_ch_ttl;
    }

    return i4_prog_atv < i4_prog_dtv ? i4_prog_atv : i4_prog_dtv;
#else
    return t_scan_info_dtv.i4_phy_ch_num * 100 / t_scan_info_dtv.i4_phy_ch_ttl;
#endif
}

static VOID _do_update_signal_level(VOID* pv_data,
                                    SIZE_T  z_data_size)
{
    INT32  i4_ret;
    UINT16 ui2_lvl;

    if(b_scan == FALSE)
    {
        i4_ret = _get_curr_sig_lvl(&ui2_lvl);
        if(i4_ret != MENUR_OK)
        {
            ui2_lvl = 0;
        }

        c_wgl_do_cmd(h_pb_signal,
                     WGL_CMD_PG_SET_POS,
                     WGL_PACK(ui2_lvl),
                     NULL);

        c_wgl_repaint(h_pb_signal,
                      NULL,
                      TRUE);
    }
}

static VOID _timer_signal_nfy_fct(HANDLE_T  h_timer,
                                  VOID*     pv_tag)
{
    menu_async_invoke(_do_update_signal_level, NULL, 0, FALSE);
}

static VOID _timer_signal_start(VOID)
{
    c_timer_start(h_signal_timer,
                  SIG_LVL_REFRESH_RATE,
                  X_TIMER_FLAG_REPEAT,
                  _timer_signal_nfy_fct,
                  NULL);
}

static VOID _timer_signal_stop(VOID)
{
    c_timer_stop(h_signal_timer);
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
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;
    WGL_PG_IDR_LOC_T      t_pg_idr_loc;


    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_SGL_PB_X,
                     ATSC_ADV_SCAN_SGL_PB_Y,
                     ATSC_ADV_SCAN_SGL_PB_W,
                     ATSC_ADV_SCAN_SGL_PB_H);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));

    t_inset.i4_left     = 0;
    t_inset.i4_right    = ATSC_ADV_SCAN_SGL_PB_VAL_W;
    t_inset.i4_top      = ATSC_ADV_SCAN_SGL_PB_CNT_INSET_T;
    t_inset.i4_bottom   = ATSC_ADV_SCAN_SGL_PB_CNT_INSET_B;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = ATSC_ADV_SCAN_SGL_PB_BAR_INSET_L;
    t_inset.i4_right    = ATSC_ADV_SCAN_SGL_PB_BAR_INSET_R;
    t_inset.i4_top      = ATSC_ADV_SCAN_SGL_PB_BAR_INSET_T;
    t_inset.i4_bottom   = ATSC_ADV_SCAN_SGL_PB_BAR_INSET_B;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_BAR_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Range */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK((INT32)0),
                           WGL_PACK((INT32)100));
    MENU_CHK_FAIL(i4_ret);

    /* Set Levels */
    t_pg_levels.a_boundary[0] = 100;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Display Modes */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_DISPLAY_MODE,
                           WGL_PACK(WGL_PG_DM_PERCENT),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Indicator */
    SET_RECT_BY_SIZE(&t_pg_idr_loc.t_loc_rect,
                     ATSC_ADV_SCAN_SGL_PB_W - ATSC_ADV_SCAN_SGL_PB_VAL_W,
                     0,
                     ATSC_ADV_SCAN_SGL_PB_VAL_W,
                     ATSC_ADV_SCAN_SGL_PB_H);
    t_pg_idr_loc.ui1_align = WGL_AS_RIGHT_CENTER;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_IDR_LOC,
                           WGL_PACK(WGL_PG_CNT_ILT_POS),
                           WGL_PACK(&t_pg_idr_loc));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _txt_info_create
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
static INT32 _txt_info_create(
    HANDLE_T    h_parent,
    INT32       i4_x,
    INT32       i4_y,
    INT32       i4_w,
    INT32       i4_h,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T         t_inset;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT32              ui4_style;

#ifdef APP_MENU_IMG_UI
    ui4_style = WGL_STL_TEXT_MAX_512
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;
#else
    ui4_style = WGL_STL_GL_NO_IMG_UI
                | WGL_STL_TEXT_MAX_512
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;
#endif

    SET_RECT_BY_SIZE(&t_rect, i4_x, i4_y, i4_w, i4_h);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
#ifdef APP_MENU_IMG_UI
                                 WGL_BORDER_NULL,
#else
                                 WGL_BORDER_UNIFORM,
#endif
                                 &t_rect,
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
                          (VOID*)WGL_AS_LEFT_TOP,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
#ifdef APP_MENU_IMG_UI
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
#else
    t_inset.i4_left     = 3;
    t_inset.i4_right    = 3;
    t_inset.i4_top      = 3;
    t_inset.i4_bottom   = 3;
#endif
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_L;
    t_inset.i4_right    = ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_R;
    t_inset.i4_top      = ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_T;
    t_inset.i4_bottom   = ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_B;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _txt_info_set_text
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
static INT32 _txt_info_set_text(UTF16_T* w2s_str)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_txt_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_str,
                          (VOID*)c_uc_w2s_strlen(w2s_str));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _txt_info_set_text
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
static INT32 _txt_info_animate_update(BOOL b_step)
{
    static UINT8 ui1_step=0;
    UTF16_T w2s_str[128];
    UTF16_T w2s_num[10];
    UINT32  ui4_len = 128;

    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(w2s_num, 0, sizeof(w2s_num));

    if (b_scan)
    {
        /* Copy message */
        c_uc_w2s_strncpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_SCAN_STATUS_SCANNING),
                         ui4_len - c_uc_w2s_strlen(w2s_str));

        /* Append animation */
        if(ui1_step == 0)
        {
            c_uc_w2s_strncat(w2s_str, _TEXT("."),
                             ui4_len - c_uc_w2s_strlen(w2s_str));
        }
        else if(ui1_step == 1)
        {
            c_uc_w2s_strncat(w2s_str, _TEXT(".."),
                             ui4_len - c_uc_w2s_strlen(w2s_str));
        }
        else
        {
            c_uc_w2s_strncat(w2s_str, _TEXT("..."),
                             ui4_len - c_uc_w2s_strlen(w2s_str));
        }

        _itoa(w2s_num, t_scan_info_dtv.i4_vir_ch_num, 9);
        c_uc_w2s_strncat(w2s_str, _TEXT("\n"),
                         ui4_len - c_uc_w2s_strlen(w2s_str));
        c_uc_w2s_strncat(w2s_str, MENU_TEXT(MLM_MENU_KEY_SCAN_DIG_CH),
                         ui4_len - c_uc_w2s_strlen(w2s_str));
        c_uc_w2s_strncat(w2s_str, w2s_num,
                         ui4_len - c_uc_w2s_strlen(w2s_str));

        if(b_step)
        {
            ui1_step = (UINT8)((ui1_step + 1)%3);
        }

        _txt_info_set_text(w2s_str);
    }

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
    INT32       i4_x,
    INT32       i4_y,
    INT32       i4_w,
    INT32       i4_h,
    UINT8       ui1_align,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;


    ui4_style = WGL_STL_TEXT_MAX_32 | WGL_STL_GL_NO_BK;

    SET_RECT_BY_SIZE(&t_rect, i4_x, i4_y, i4_w, i4_h);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
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

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
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

    /* txt info */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_bk2_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_bk2_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_bk2_txt);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _eb_ch_set_value
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
static INT32 _eb_ch_set_value(HANDLE_T    h_widget,
                                   UINT16      u2_value)
{
    INT32 i4_ret;
    UTF16_T w2s_buf[5];

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(u2_value),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    c_memset(w2s_buf, 0, 5);
    _itoa(w2s_buf, (INT32)u2_value, 5);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_ch_get_value
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
static UINT16 _eb_ch_get_value(HANDLE_T    h_widget)
{
    UINT32      ui4_value;
    c_wgl_do_cmd(h_widget,
                 WGL_CMD_GL_GET_ATTACH_DATA,
                 WGL_PACK(&ui4_value),
                 NULL);

    return (UINT16)ui4_value;
}

/*----------------------------------------------------------------------------
 * Name: _chg_theme
 *
 * Description: This function is called when the theme is changed
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _chg_theme(VOID)
{
    INT32 i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    /* pb progress */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_scan_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_scan_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_scan_txt);
    i4_ret = c_wgl_do_cmd(h_pb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pb_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pb_bk;
    i4_ret = c_wgl_do_cmd(h_pb,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_BODY),
                          WGL_PACK(&t_img_info ));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pb_bar;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bar;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pb_bar;
    i4_ret = c_wgl_do_cmd(h_pb,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info ));
    MENU_CHK_FAIL(i4_ret);


    /* txt info */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_bk2_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_bk2_txt);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_bk2_txt);
    i4_ret = c_wgl_do_cmd(h_txt_info,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);


#ifdef APP_MENU_IMG_UI
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bk2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bk2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bk2;
    i4_ret = c_wgl_do_cmd(h_txt_info,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);
#else
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_bk2);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_bk2);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_bk2);
    i4_ret = c_wgl_do_cmd(h_txt_info,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_bdr);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_bdr);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_bdr);
    i4_ret = c_wgl_do_cmd(h_txt_info,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_FG),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(h_txt_info,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);
#endif


    return MENUR_OK;
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

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_lb_mod;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_lb_pln;
    i4_ret = c_wgl_set_navigation(h_eb_ch, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_eb_ch;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_lb_mod;
    i4_ret = c_wgl_set_navigation(h_lb_pln, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_lb_pln;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = h_eb_ch;
    i4_ret = c_wgl_set_navigation(h_lb_mod, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

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
    i4_ret = _txt_info_set_text(MENU_TEXT(MLM_MENU_KEY_SCAN_STATUS_ERROR));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_txt_info,
                           NULL,
                           FALSE);
    MENU_CHK_FAIL(i4_ret);

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
    UTF16_T w2s_str[128];
    UTF16_T w2s_num[10];
    UINT32  ui4_len = 128;

    b_scan = FALSE;

    /* change the info in help list */
    menu_atsc_help_show_scan();

    /* show the message */
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(w2s_num, 0, sizeof(w2s_num));

    /* Copy message */
    c_uc_w2s_strncpy(w2s_str, w2s_message,
                     ui4_len - c_uc_w2s_strlen(w2s_str));


    /* Append Digital Channels */
    _itoa(w2s_num, t_scan_info_dtv.i4_vir_ch_num, 9);
    c_uc_w2s_strncat(w2s_str, _TEXT("\n"),
                     ui4_len - c_uc_w2s_strlen(w2s_str));
    c_uc_w2s_strncat(w2s_str, MENU_TEXT(MLM_MENU_KEY_SCAN_DIG_CH),
                     ui4_len - c_uc_w2s_strlen(w2s_str));
    c_uc_w2s_strncat(w2s_str, w2s_num,
                     ui4_len - c_uc_w2s_strlen(w2s_str));

    _txt_info_set_text(w2s_str);

    /* set focus to lb mode */
    c_wgl_set_focus(h_eb_ch, WGL_NO_AUTO_REPAINT);

    /* disable the animation timer */
    c_timer_stop(h_timer_ani);

    /* enable the signal timer */
    _timer_signal_start();

    /* enable the menu timer */
    menu_timer_enable(TRUE);
    menu_timer_start();

    DBG_INFO(("<MENU>Finish to scan\r\n"));


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
    UINT16      ui2_ch;
    BOOL        b_fix = FALSE;

    if (b_scan)
    {
        DBG_ERROR(("<MENU> It's scanning!\n"));
        return MENUR_FAIL;
    }

    /* find the physical frequency */
    ui2_ch = _eb_ch_get_value(h_eb_ch);

    if (ui2_ch < ui2_phy_ch_min)
    {
        ui2_ch = ui2_phy_ch_min;
        b_fix = TRUE;
    }

    if (ui2_ch > ui2_phy_ch_max)
    {
        ui2_ch =  ui2_phy_ch_max;
        b_fix = TRUE;
    }

    if (b_fix)
    {
        _eb_ch_set_value(h_eb_ch, ui2_ch);
        i4_ret = c_wgl_repaint(h_eb_ch, NULL, TRUE);
        MENU_CHK_FAIL(i4_ret);
    }

    /* close service context */
    i4_ret = c_svctx_sync_stop_svc(menu_get_crnt_svctx(),
                                   DEFAULT_STOP_SVC_TIMEOUT);
    if (i4_ret == SVCTXR_TIMEOUT)
    {
        DBG_ERROR(("<MENU>Cannot close service context timeout. \r\n"));
        _on_start_scan_fail();
        return MENUR_FAIL;
    }
    else if (i4_ret < SVCTXR_OK)
    {
        DBG_ERROR(("<MENU>Cannot close service context. %d\r\n", i4_ret));
        _on_start_scan_fail();
        return MENUR_FAIL;
    }

    /* Start scan the ATV channels*/
    if( ui1_scan_mode == SCAN_MODE_ATV_DTV ||
        ui1_scan_mode == SCAN_MODE_ATV)
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
            t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
            t_ntsc_scan_data.ui2_start_idx = ui2_ch;
            t_ntsc_scan_data.ui2_end_idx   = ui2_ch;

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
            t_ntsc_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_SINGLE_RF_CHANNEL;
            t_ntsc_scan_data.ui2_start_idx = ui2_ch;
            t_ntsc_scan_data.ui2_end_idx   = ui2_ch;

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
    if( ui1_scan_mode == SCAN_MODE_ATV_DTV ||
        ui1_scan_mode == SCAN_MODE_DTV)
    {
        t_scan_info_dtv.b_done = FALSE;

        if (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
        {
            SB_ATSC_SCAN_DATA_T t_atsc_scan_data;

            DBG_INFO(("<MENU>Scan Mode: ATSC/AIR\r\n"));
            c_memset(&t_atsc_scan_data, 0, sizeof(SB_ATSC_SCAN_DATA_T));
            t_atsc_scan_data.e_scan_type   = SB_ATSC_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_atsc_scan_data.ui4_scan_info = _SET_SCAN_RANGE(ui2_ch, ui2_ch);

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
            UINT8               ui1_freq = 0;
            UINT32              ui4_mod_mask = 0;

            DBG_INFO(("<MENU>Scan Mode: ATSC/CABLE\r\n"));

            i4_ret = _get_freq_plan(&ui1_freq, &ui4_mod_mask);
            if (i4_ret != MENUR_OK)
            {
                DBG_ERROR(("<MENU>Wrong frequency plan mode\r\n"));
                _on_start_scan_fail();
                return MENUR_FAIL;
            }

            DBG_INFO(("<MENU>Use CQAM mode to start scan\r\n"));
            c_memset(&t_cqam_scan_data, 0, sizeof(SB_CQAM_SCAN_DATA_T));
            t_cqam_scan_data.e_scan_type   = SB_CQAM_SCAN_TYPE_RANGE_RF_CHANNEL;
            t_cqam_scan_data.ui4_scan_info = _SET_SCAN_RANGE(ui2_ch, ui2_ch);
            t_cqam_scan_data.ui1_freq_plan = ui1_freq;
            t_cqam_scan_data.ui4_mod_mask  = ui4_mod_mask;

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

    /* set focus to txt info */
    c_wgl_set_focus(h_txt_info, WGL_NO_AUTO_REPAINT);

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
    t_scan_info_atv.i4_vir_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_ttl = 1;
    t_scan_info_dtv.i4_vir_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_ttl = 1;

    /* set the corresponding widget */
    i4_ret = _txt_info_animate_update(FALSE);
    if(i4_ret < 0)
    {
       DBG_ERROR(("<MENU> Can't change scan text\r\n"));
    }

    c_wgl_do_cmd(h_pb,
                 WGL_CMD_PG_SET_POS,
                 WGL_PACK((INT32)0),
                 NULL);

    c_wgl_do_cmd(h_pb_signal,
                 WGL_CMD_PG_SET_POS,
                 WGL_PACK((INT32)0),
                 NULL);

    /* change the info in help list */
    menu_atsc_help_show_scanning();

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

    /* disable the signal timer */
    _timer_signal_stop();

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

        _on_scan_stop(MENU_TEXT(MLM_MENU_KEY_SCAN_STATUS_CANCEL));
    }

    return MENUR_OK;
}

static VOID _do_scan_nfy(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    INT32 i4_ret;
    ADV_SCAN_NFY_T* pt_scan_nfy = (ADV_SCAN_NFY_T*)pv_data;
    ADV_SCAN_INFO_T* pt_scan_info = (ADV_SCAN_INFO_T*)pt_scan_nfy->pv_nfy_tag;
    INT32   i4_progress;

    if (pt_scan_nfy->ui4_nfy_reason & SB_REASON_PROGRESS)
    {
        if (b_scan)
        {
            BOOL b_paint_info = (_GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data) > 0);

            pt_scan_info->i4_vir_ch_num += _GET_VIR_CH_NUM(pt_scan_nfy->i4_nfy_data);
            pt_scan_info->i4_phy_ch_num += 1;
            pt_scan_info->i4_phy_ch_ttl  = _GET_PHY_CH_NUM(pt_scan_nfy->i4_nfy_data);

            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                DBG_ERROR(("<MENU>ph_ch_num > ph_ch_ttl!:%d,%d\n",
                           pt_scan_info->i4_phy_ch_num,
                           pt_scan_info->i4_phy_ch_ttl));
                pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
            }

            i4_progress = _calc_progress();

            c_wgl_do_cmd(h_pb,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK((INT32) i4_progress),
                         NULL);

            if (b_paint_info)
            {
                _txt_info_animate_update(FALSE);

                c_wgl_repaint(h_txt_info,
                              NULL,
                              FALSE);
            }
            else
            {
                c_wgl_repaint(h_pb,
                              NULL,
                              FALSE);
            }
            DBG_INFO(("<MENU>%s: Scan %d/%d: %d channels found.\r\n",
                      pt_scan_info == &t_scan_info_atv ? "ATV" : "DTV",
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
            _on_scan_stop(MENU_TEXT(MLM_MENU_KEY_SCAN_STATUS_ERROR));

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
                /* Good, the scan complete correctly */
                c_wgl_do_cmd(h_pb,
                             WGL_CMD_PG_SET_POS,
                             WGL_PACK(100),
                             NULL);

                _on_scan_stop(MENU_TEXT(MLM_MENU_KEY_SCAN_STATUS_COMPLETE));
            }

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
                _tune_by_rf_ch(ui2_rf_ch);
            }

            menu_pm_repaint();
        }
    }
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
    c_wgl_repaint(h_txt_info, NULL, FALSE);
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
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        if (b_scan)
        {
            switch (ui4_keycode)
            {
            case BTN_EXIT:
                _cancel_scan();
                menu_pm_repaint();
                return WMPR_DONE;
            }
        }
        else
        {
            switch (ui4_keycode)
            {
            case BTN_SELECT:
                _start_scan();
                return WMPR_DONE;
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;
            default:
                break;
            }
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _lb_pln_proc_fct
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
static INT32 _lb_pln_proc_fct(HANDLE_T    h_widget,
                              UINT32      ui4_msg,
                              VOID*       param1,
                              VOID*       param2)
{
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
            ui1_frq_pln = (UINT8)(ui1_frq_pln == 0 ? 2 : ui1_frq_pln - 1);
            menu_list_set_idx(h_lb_pln, ui1_frq_pln);

            c_wgl_do_cmd(h_pb_signal,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK(0),
                         NULL);

            c_wgl_repaint(h_lb_pln,
                          NULL,
                          TRUE);

            c_wgl_repaint(h_pb_signal,
                          NULL,
                          TRUE);

            if(ui2_rf_ch >= ui2_phy_ch_min &&
               ui2_rf_ch <= ui2_phy_ch_max)
            {
                _tune_by_rf_ch(ui2_rf_ch);
            }
            else
            {
                c_svctx_stop_svc(menu_get_crnt_svctx());
            }

            return  WGLR_OK;
        }
        case BTN_CURSOR_RIGHT:
        {
            ui1_frq_pln = (UINT8)(ui1_frq_pln == 2 ? 0 : ui1_frq_pln + 1);
            menu_list_set_idx(h_lb_pln, ui1_frq_pln);

            c_wgl_do_cmd(h_pb_signal,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK(0),
                         NULL);

            c_wgl_repaint(h_lb_pln,
                          NULL,
                          TRUE);

            c_wgl_repaint(h_pb_signal,
                          NULL,
                          TRUE);

            if(ui2_rf_ch >= ui2_phy_ch_min &&
               ui2_rf_ch <= ui2_phy_ch_max)
            {
                _tune_by_rf_ch(ui2_rf_ch);
            }
            else
            {
                c_svctx_stop_svc(menu_get_crnt_svctx());
            }

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
 * Name: _lb_mode_proc_fct
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
static INT32 _lb_mod_proc_fct(HANDLE_T    h_widget,
                              UINT32      ui4_msg,
                              VOID*       param1,
                              VOID*       param2)
{
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
            ui1_modulation = (UINT8)(ui1_modulation == 0 ? 1 : ui1_modulation - 1);
            menu_list_set_idx(h_lb_mod, ui1_modulation);

            c_wgl_do_cmd(h_pb_signal,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK(0),
                         NULL);

            c_wgl_repaint(h_lb_mod,
                          NULL,
                          TRUE);

            c_wgl_repaint(h_pb_signal,
                          NULL,
                          TRUE);

            if(ui2_rf_ch >= ui2_phy_ch_min &&
               ui2_rf_ch <= ui2_phy_ch_max)
            {
                _tune_by_rf_ch(ui2_rf_ch);
            }
            else
            {
                c_svctx_stop_svc(menu_get_crnt_svctx());
            }

            return  WGLR_OK;
        }
        case BTN_CURSOR_RIGHT:
        {
            ui1_modulation = (UINT8)(ui1_modulation == 1 ? 0 : ui1_modulation + 1);
            menu_list_set_idx(h_lb_mod, ui1_modulation);

            c_wgl_do_cmd(h_pb_signal,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK(0),
                         NULL);

            c_wgl_repaint(h_lb_mod,
                          NULL,
                          TRUE);

            c_wgl_repaint(h_pb_signal,
                          NULL,
                          TRUE);

            if(ui2_rf_ch >= ui2_phy_ch_min &&
               ui2_rf_ch <= ui2_phy_ch_max)
            {
                _tune_by_rf_ch(ui2_rf_ch);
            }
            else
            {
                c_svctx_stop_svc(menu_get_crnt_svctx());
            }

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
 * Name: _eb_ch_proc_fct
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
static INT32 _eb_ch_proc_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
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
            static UINT32 ui4_tick_last=0;

            UINT16 ui2_input = (UINT16)(ui4_keycode - BTN_DIGIT_0);
            UINT32 ui4_tick_curr = c_os_get_sys_tick();

            if((ui4_tick_curr - ui4_tick_last) * c_os_get_sys_tick_period() <
               INPUT_RESET_DELAY)
            {
                ui2_rf_ch = (UINT16)(ui2_rf_ch * 10 + ui2_input);
            }
            else
            {
                ui2_rf_ch = ui2_input;
            }
            ui4_tick_last = ui4_tick_curr;


            while(ui2_rf_ch > ui2_phy_ch_max)
            {
                if(ui2_rf_ch >= 100)
                {
                    ui2_rf_ch = ui2_rf_ch % 100;
                }
                else
                {
                    ui2_rf_ch = ui2_rf_ch % 10;
                }
            }


            _eb_ch_set_value(h_eb_ch, ui2_rf_ch);

            if(ui2_rf_ch >= ui2_phy_ch_min &&
               ui2_rf_ch <= ui2_phy_ch_max)
            {
                _tune_by_rf_ch(ui2_rf_ch);
            }
            else
            {
                c_svctx_stop_svc(menu_get_crnt_svctx());
            }

            c_wgl_do_cmd(h_pb_signal,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK(0),
                         NULL);

            c_wgl_repaint(h_eb_ch,
                          NULL,
                          TRUE);

            c_wgl_repaint(h_pb_signal,
                          NULL,
                          TRUE);

            _timer_signal_start();

            return WMPR_DONE;
        }
        case BTN_CURSOR_LEFT:
            ui2_rf_ch = (UINT16)(ui2_rf_ch - 1) < ui2_phy_ch_min ?
                        ui2_phy_ch_max :
                        (UINT16)(ui2_rf_ch - 1);

            _eb_ch_set_value(h_eb_ch, ui2_rf_ch);

            _tune_by_rf_ch(ui2_rf_ch);

            c_wgl_do_cmd(h_pb_signal,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK(0),
                         NULL);

            c_wgl_repaint(h_eb_ch,
                          NULL,
                          TRUE);

            c_wgl_repaint(h_pb_signal,
                          NULL,
                          TRUE);

            _timer_signal_start();

            return WGLR_OK;
        case BTN_CURSOR_RIGHT:
            ui2_rf_ch = (UINT16)(ui2_rf_ch + 1) > ui2_phy_ch_max ?
                        ui2_phy_ch_min :
                        (UINT16)(ui2_rf_ch + 1);

            _eb_ch_set_value(h_eb_ch, ui2_rf_ch);

            _tune_by_rf_ch(ui2_rf_ch);

            c_wgl_do_cmd(h_pb_signal,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK(0),
                         NULL);

            c_wgl_repaint(h_eb_ch,
                          NULL,
                          TRUE);

            c_wgl_repaint(h_pb_signal,
                          NULL,
                          TRUE);

            _timer_signal_start();

            return WGLR_OK;

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




/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 _ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;

    ui4_page_id = _ui4_page_id;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    /* scan progress */
    i4_ret = _pb_create(h_cnt_frm,
                        NULL,
                        &h_pb);
    MENU_CHK_FAIL(i4_ret);

    /* tuner info */
    i4_ret = _txt_create(h_cnt_frm,
                         ATSC_ADV_SCAN_SGL_TXT_TUNER_X,
                         ATSC_ADV_SCAN_SGL_TXT_TUNER_Y,
                         ATSC_ADV_SCAN_SGL_TXT_TUNER_W,
                         ATSC_ADV_SCAN_SGL_TXT_TUNER_H,
                         ATSC_ADV_SCAN_SGL_TXT_TUNER_ALIGN,
                         NULL,
                         &h_txt_tuner);
    MENU_CHK_FAIL(i4_ret);

    /* text info */
    i4_ret = _txt_info_create(h_cnt_frm,
                            ATSC_ADV_SCAN_SGL_TXT_INFO_X,
                            ATSC_ADV_SCAN_SGL_TXT_INFO_Y,
                            ATSC_ADV_SCAN_SGL_TXT_INFO_W,
                            ATSC_ADV_SCAN_SGL_TXT_INFO_H,
                            _widgets_proc_fct,
                            &h_txt_info);
    MENU_CHK_FAIL(i4_ret);

    /* lb pln */
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_ADV_SCAN_SGL_LB_PLN_IDX,
                              3,
                              _lb_pln_proc_fct,
                              &h_lb_pln);
    MENU_CHK_FAIL(i4_ret);

    menu_list_chg_lang(h_lb_pln,
                       MLM_MENU_KEY_ATSC_ASS_PLN,
                       MLM_MENU_KEY_ATSC_ASS_PLN_STD,
                       MLM_MENU_KEY_ATSC_ASS_PLN_HRC);

    /* lb mod */
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_ADV_SCAN_SGL_LB_MOD_IDX,
                              2,
                              _lb_mod_proc_fct,
                              &h_lb_mod);
    MENU_CHK_FAIL(i4_ret);

    menu_list_chg_lang(h_lb_mod,
                       MLM_MENU_KEY_ATSC_ASS_MOD,
                       MLM_MENU_KEY_ATSC_ASS_MOD_Q64,
                       MLM_MENU_KEY_ATSC_ASS_MOD_Q256);

    /* eb ch */
    i4_ret = menu_edit_create(h_cnt_frm,
                              ATSC_ADV_SCAN_SGL_EB_CH_IDX,
                              FALSE,
                              _eb_ch_proc_fct,
                              &h_eb_ch);
    MENU_CHK_FAIL(i4_ret);

    menu_edit_chg_lang(h_eb_ch, MLM_MENU_KEY_ATSC_ASS_RF_CH);

    /* pb signal */
    i4_ret = menu_range_create(h_cnt_frm,
                               ATSC_ADV_SCAN_SGL_PB_SIG_IDX,
                               0,
                               100,
                               MENU_RANGE_STYLE_BAR,
                               NULL,
                               &h_pb_signal);
    MENU_CHK_FAIL(i4_ret);

    menu_range_chg_lang(h_pb_signal, MLM_MENU_KEY_ATSC_ASS_SIG);

    /* navigation */
    i4_ret = _set_nav();
    MENU_CHK_FAIL(i4_ret);

    /* timer */
    i4_ret = c_timer_create(&h_timer_ani);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_signal_timer);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _chg_theme();
    MENU_CHK_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    const UTF16_T*  w2s_str;

    /* reset values */
    a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    ui1_scan_mode = SCAN_MODE_DTV;
    ui1_frq_pln = FRQ_PLN_STD;
    ui1_modulation = MOD_Q256;
    ui2_crnt_tsl_id = (UINT16)(ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID ?
                       ATSC_TRSTRL_TSL_ID : ATSC_CABLE_SVL_ID);

    /* title */
    menu_main_set_title(MLM_MENU_KEY_ATSC_ASS);

    /* change the info in help list */
    menu_atsc_help_show_scan();

    /* txt tuner */
    w2s_str = (ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID ?
               MENU_TEXT(MLM_MENU_KEY_AIR) :
               MENU_TEXT(MLM_MENU_KEY_CABLE));

    i4_ret = c_wgl_do_cmd(h_txt_tuner,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(c_uc_w2s_strlen(w2s_str)));
    MENU_CHK_FAIL(i4_ret);

    /* txt info */
    _txt_info_set_text(MENU_TEXT(MLM_MENU_KEY_ATSC_ASS_DESC));

    /* lb pln, mod */
    menu_list_set_idx(h_lb_pln, ui1_frq_pln);
    menu_list_set_idx(h_lb_mod, ui1_modulation);

    if(ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID)
    {
        c_wgl_enable(h_lb_pln, FALSE);
        c_wgl_enable(h_lb_mod, FALSE);
    }
    else
    {
        c_wgl_enable(h_lb_pln, TRUE);
        c_wgl_enable(h_lb_mod, TRUE);
    }

    /* eb ch */
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

    _update_rf_ch_by_crnt_ch();
    _eb_ch_set_value(h_eb_ch, ui2_rf_ch);

    /* pb sig */
    menu_range_set_val(h_pb_signal, 0);

    /* pb progress */
    c_wgl_do_cmd(h_pb,
                 WGL_CMD_PG_SET_POS,
                 WGL_PACK((INT32)0),
                 NULL);

    /* signal timer */
    _timer_signal_start();

    /* stop the service first if current playing service is analog channel */
    _stop_analog_service();

    /* Menu is in scanning status */
    t_g_menu_is_scanning = TRUE;

    /* Broadcast the message to disable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to disable the EAS.\r\n"));
    a_amb_channel_scan_active(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    if (b_scan)
    {
        _cancel_scan();
    }
    else
    {
        menu_adjust_vplane();
    }

    _timer_signal_stop();

    /* Menu is not in scanning status */
    t_g_menu_is_scanning = FALSE;

    /* Broadcast the message to enable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to enable the EAS.\r\n"));
    a_amb_channel_scan_active(FALSE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    b_scan = FALSE;

    c_wgl_set_focus(h_eb_ch, WGL_NO_AUTO_REPAINT);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        menu_list_chg_lang(h_lb_pln,
                           MLM_MENU_KEY_ATSC_ASS_PLN,
                           MLM_MENU_KEY_ATSC_ASS_PLN_STD,
                           MLM_MENU_KEY_ATSC_ASS_PLN_HRC);

        menu_list_chg_lang(h_lb_mod,
                           MLM_MENU_KEY_ATSC_ASS_MOD,
                           MLM_MENU_KEY_ATSC_ASS_MOD_Q64,
                           MLM_MENU_KEY_ATSC_ASS_MOD_Q256);

        menu_edit_chg_lang(h_eb_ch, MLM_MENU_KEY_ATSC_ASS_RF_CH);
    }

    return MENUR_OK;
}

extern INT32 menu_atsc_page_adv_scan_sgl_init(VOID)
{
    t_g_menu_atsc_page_adv_scan_sgl.pf_menu_page_create =    _on_page_create;
    t_g_menu_atsc_page_adv_scan_sgl.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_atsc_page_adv_scan_sgl.pf_menu_page_show=       _on_page_show;
    t_g_menu_atsc_page_adv_scan_sgl.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_atsc_page_adv_scan_sgl.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_atsc_page_adv_scan_sgl.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_atsc_page_adv_scan_sgl.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#endif /* ATSC_ADV_SCAN_SGL_ENABLE */


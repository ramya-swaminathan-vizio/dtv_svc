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
 * $RCSfile: menu_page_vchip_us_tv.c,v $
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
#include <stdio.h>
#include <string.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_drv_cust.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_rm.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "am/a_am.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/a_menu_page_color_tuner.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_page.h"
#include "res/menu2/menu_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/msgconvert/msgconvert_custom.h"
#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#include "res/app_util/icl/a_icl_custom.h"
#include "nav/test_pattern/test_pattern.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "res/menu2/menu_custom.h"

#include "menu2/menu_dbg.h"
#include "app_util/splayer/splayer.h"
#include "nav/input_src/a_input_src.h"
#ifdef SYS_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif

#include "mi_common.h"
#include "mi_mm.h"
#include "mi_aout.h"
#include "mi_disp.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"

#include "nav/cc_info/cc_info.h"
#include "nav/banner2/a_banner.h"

//--------------------------------------------------------------------------------------------
#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
extern BOOL menu_page_color_calibration_is_CaliTestMode(void);
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define MENU_CT_DEBUG(x) x

//------------------------------------------------------------------------------------
#define APP_CAST_TEST_PATTERN_FLAT
#define APP_AND_DRV_OFFSET_MID_VALUE        128
#define APP_VALUE_LEN                        5

typedef enum
{
    PAGE_COLOR_TUNER_PAGE,
    PAGE_SMPTE_TEST_PATTERN,
    PAGE_FLAT_TEST_PATTERN,
    PAGE_RAMP_TEST_PATTERN,
    PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN,
    PAGE_FACTORY_TEST_PATTERN,
} EnuColorTunerSubPage;

static EnuColorTunerSubPage s_eCurSubPage;
#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
static EnuColorTunerSubPage s_eCurSubPage_TestPattern = PAGE_SMPTE_TEST_PATTERN;
#endif

#define ACFG_ODM_FIX_ADR_BEGIN  0x1A000
#define ACFG_ODM_FIX_ADR_END    0x1B000
#define BE_LEFT                     FALSE
#define BE_RIGHT                    TRUE

 /*Color Tuner Page*/
#define     RGB_OFF     0
#define     RGB_ON      1

#define     COL_RED     0
#define     COL_GREEN   1
#define     COL_BLUE    2
#define     COL_CYAN    3
#define     COL_MAGENTA 4
#define     COL_YELLOW  5

#define     ROW_HUE         0
#define     ROW_SATURATION  1
#define     ROW_BRIGHTNESS  2
#define     ROW_OFFSET      3
#define     ROW_GAIN        4

#define MENU_COLOR_TUNER_UNIT_INSRT_X       (0)
#define MENU_COLOR_TUNER_UNIT_INSRT_Y       (0)
#define MENU_COLOR_TUNER_UNIT_INSRT_W       (0)
#define MENU_COLOR_TUNER_UNIT_INSRT_H       (0)

#define MENU_COLOR_TUNER_FRAME_X            ((1920 - 887)/2)
#define MENU_COLOR_TUNER_FRAME_Y            (1080 - MENU_COLOR_TUNER_FARME_H)
#define MENU_COLOR_TUNER_FRAME_W            (887 + MENU_COLOR_TUNER_UNIT_INSRT_X)
#define MENU_COLOR_TUNER_FARME_H            (360 + MENU_COLOR_TUNER_UNIT_INSRT_Y)
#define MENU_COLOR_TUNER_GRID_H             (290 + MENU_COLOR_TUNER_UNIT_INSRT_Y)
#define MENU_COLOR_TUNER_GRID_Y             (MENU_COLOR_TUNER_BAR_Y + MENU_COLOR_TUNER_BAR_H)

#define MENU_COLOR_TUNER_BAR_X              (0)
#define MENU_COLOR_TUNER_BAR_Y              (1)
#define MENU_COLOR_TUNER_BAR_W              (887)
#define MENU_COLOR_TUNER_BAR_H              (MENU_COLOR_TUNER_FARME_H - MENU_COLOR_TUNER_GRID_H + 1)

#define MENU_COLOR_TUNER_BAR_LFET_BTN_X     (MENU_COLOR_TUNER_BAR_X)
#define MENU_COLOR_TUNER_BAR_LFET_BTN_Y     (MENU_COLOR_TUNER_BAR_Y)
#define MENU_COLOR_TUNER_BAR_LFET_BTN_W     (67)
#define MENU_COLOR_TUNER_BAR_LFET_BTN_H     (MENU_COLOR_TUNER_BAR_W - MENU_COLOR_TUNER_BAR_H)
#define MENU_COLOR_TUNER_BAR_RIGHT_BTN_X    (MENU_COLOR_TUNER_BAR_W - MENU_COLOR_TUNER_BAR_LFET_BTN_W)
#define MENU_COLOR_TUNER_BAR_RIGHT_BTN_Y    (MENU_COLOR_TUNER_BAR_LFET_BTN_Y)
#define MENU_COLOR_TUNER_BAR_RIGHT_BTN_W    (MENU_COLOR_TUNER_BAR_LFET_BTN_W)
#define MENU_COLOR_TUNER_BAR_RIGHT_BTN_H    (MENU_COLOR_TUNER_BAR_LFET_BTN_H)

#define MENU_COLOR_TUNER_ROW_X              (0)
#define MENU_COLOR_TUNER_ROW_Y              (MENU_COLOR_TUNER_COL_Y + MENU_COLOR_TUNER_COL_H)
#define MENU_COLOR_TUNER_ROW_W              (155)
#define MENU_COLOR_TUNER_ROW_H              (46)

#define MENU_COLOR_TUNER_COL_X              (MENU_COLOR_TUNER_ROW_X + MENU_COLOR_TUNER_ROW_W)
#define MENU_COLOR_TUNER_COL_Y              (0)
#define MENU_COLOR_TUNER_COL_W              (120)
#define MENU_COLOR_TUNER_COL_H              (48)
#define MENU_COLOR_TUNER_COL_Y_OFFSET       (22)

#define MENU_COLOR_TUNER_UNIT_X             (MENU_COLOR_TUNER_ROW_X + MENU_COLOR_TUNER_ROW_W)
#define MENU_COLOR_TUNER_UNIT_Y             (MENU_COLOR_TUNER_ROW_Y)
#define MENU_COLOR_TUNER_UNIT_W             (121)
#define MENU_COLOR_TUNER_UNIT_H             (47)

#define RED_ON_OFF_BTN_LINE              (2)
#define RED_ON_OFF_BTN_X                    (MENU_COLOR_TUNER_COL_X)
#define RED_ON_OFF_BTN_Y                    (MENU_COLOR_TUNER_COL_Y)
#define RED_ON_OFF_BTN_W                    (MENU_COLOR_TUNER_COL_W)
#define RED_ON_OFF_BTN_H                    (MENU_COLOR_TUNER_COL_H)
#define RED_ON_OFF_BTN_MOV_OFFSET           (MENU_COLOR_TUNER_COL_W+RED_ON_OFF_BTN_LINE)

#define RED_ON_OFF_HLT_MOVE_BTN_W           (MENU_COLOR_TUNER_COL_W)
#define RED_ON_OFF_HLT_MOVE_BTN_H           (MENU_COLOR_TUNER_UNIT_H)
#define RED_ON_OFF_HLT_MOVE_BTN_X           (MENU_COLOR_TUNER_COL_X)
#define RED_ON_OFF_HLT_MOVE_BTN_Y           (MENU_COLOR_TUNER_COL_Y)
#define RED_ON_OFF_HLT_MOVE_BTN_X_OFFSET    (MENU_COLOR_TUNER_COL_W)



#define     H_HUE_RED      t_color_tuner.aah_cb_tr[0][0]
#define     H_SATU_RED     t_color_tuner.aah_cb_tr[1][0]
#define     H_BRIGHT_RED   t_color_tuner.aah_cb_tr[2][0]
#define     H_OFFSET_RED   t_color_tuner.aah_cb_tr[3][0]
#define     H_GAIN_RED     t_color_tuner.aah_cb_tr[4][0]

#define     H_HUE_GREEN    t_color_tuner.aah_cb_tr[0][1]
#define     H_SATU_GREEN   t_color_tuner.aah_cb_tr[1][1]
#define     H_BRIGHT_GREEN t_color_tuner.aah_cb_tr[2][1]
#define     H_OFFSET_GREEN t_color_tuner.aah_cb_tr[3][1]
#define     H_GAIN_GREEN   t_color_tuner.aah_cb_tr[4][1]

#define     H_HUE_BLUE     t_color_tuner.aah_cb_tr[0][2]
#define     H_SATU_BLUE    t_color_tuner.aah_cb_tr[1][2]
#define     H_BRIGHT_BLUE  t_color_tuner.aah_cb_tr[2][2]
#define     H_OFFSET_BLUE  t_color_tuner.aah_cb_tr[3][2]
#define     H_GAIN_BLUE    t_color_tuner.aah_cb_tr[4][2]

#define     H_HUE_CYAN     t_color_tuner.aah_cb_tr[0][3]
#define     H_SATU_CYAN    t_color_tuner.aah_cb_tr[1][3]
#define     H_BRIGHT_CYAN  t_color_tuner.aah_cb_tr[2][3]

#define     H_HUE_MAGENTA     t_color_tuner.aah_cb_tr[0][4]
#define     H_SATU_MAGENTA    t_color_tuner.aah_cb_tr[1][4]
#define     H_BRIGHT_MAGENTA  t_color_tuner.aah_cb_tr[2][4]

#define     H_HUE_YELLOW     t_color_tuner.aah_cb_tr[0][5]
#define     H_SATU_YELLOW    t_color_tuner.aah_cb_tr[1][5]
#define     H_BRIGHT_YELLOW  t_color_tuner.aah_cb_tr[2][5]

#define COLOR_TUNER_PQ_MAP2_DRV_COLOR(_ui1_hlt_col, _ui1_color) \
{                                                               \
    switch(_ui1_hlt_col)                                      \
    {                                                           \
    case COL_RED:                                             \
        (_ui1_color) = 1;                                   \
        break;                                                  \
    case COL_GREEN:                                          \
        (_ui1_color) = 3;                                   \
        break;                                                  \
    case COL_BLUE:                                           \
        (_ui1_color) = 5;                                       \
        break;                                                   \
    case COL_CYAN:                                             \
        (_ui1_color) = 4;                                         \
        break;                                                     \
    case COL_MAGENTA:                                           \
        (_ui1_color) = 0;                                           \
        break;                                                      \
    case COL_YELLOW:                                             \
        (_ui1_color) = 2;                                       \
    default:                                                        \
           break;                                                   \
    }                                                               \
}

// driver module  map---> 0: lume   1: hue   2:sat
#define COLOR_TUNER_PQ_MAP2_DRV_MODULE(_ui1_hlt_row, _ui1_module) \
{                                                               \
    switch(_ui1_hlt_row)                                      \
    {                                                           \
    case ROW_HUE:                                             \
        (_ui1_module) = 1;                                      \
        break;                                                  \
    case ROW_SATURATION:                                    \
        (_ui1_module) = 2;                                      \
        break;                                                  \
    case ROW_BRIGHTNESS:                                    \
        (_ui1_module) = 0;                                      \
        break;                                                   \
    default:                                                      \
           break;                                                 \
    }                                                             \
}



/*Flat Test Patterns*/
#define MENU_FLAT_TEST_PATTERN_X                    (0)
#define MENU_FLAT_TEST_PATTERN_Y                    (0)
#define MENU_FLAT_TEST_PATTERN_W                    (0)
#define MENU_FLAT_TEST_PATTERN_H                    (0)

#define MENU_FLAT_TEST_PATTERN_BTN_W                (120*3)
#define MENU_FLAT_TEST_PATTERN_BTN_H                (46)
#define MENU_FLAT_TEST_PATTERN_BTN_X                ((MENU_COLOR_TUNER_FRAME_W - MENU_FLAT_TEST_PATTERN_BTN_W)/2)
#define MENU_FLAT_TEST_PATTERN_BTN_Y                (50)//(MENU_COLOR_TUNER_GRID_Y+MENU_FLAT_TEST_PATTERN_BTN_H)

#define MENU_COLOR_TUNER_L_ARROW_X              (MENU_FLAT_TEST_PATTERN_BTN_X+23)

#define MENU_COLOR_TUNER_L_ARROW_Y              (MENU_COLOR_TUNER_GRID_Y+MENU_FLAT_TEST_PATTERN_BTN_Y+20)

#define MENU_COLOR_TUNER_L_ARROW_W              (10)
#define MENU_COLOR_TUNER_L_ARROW_H              (MENU_FLAT_TEST_PATTERN_BTN_H)
#define MENU_COLOR_TUNER_R_ARROW_X              (MENU_FLAT_TEST_PATTERN_BTN_X+MENU_FLAT_TEST_PATTERN_BTN_W-33)

#define MENU_COLOR_TUNER_R_ARROW_Y              (MENU_COLOR_TUNER_GRID_Y+MENU_FLAT_TEST_PATTERN_BTN_Y+20)

#define MENU_COLOR_TUNER_R_ARROW_W              (10)
#define MENU_COLOR_TUNER_R_ARROW_H              (MENU_FLAT_TEST_PATTERN_BTN_H)

#define MENU_COLOR_TUNER_WARING_INFO_X          (0)
#define MENU_COLOR_TUNER_WARING_INFO_Y          (MENU_FLAT_TEST_PATTERN_BTN_Y+MENU_FLAT_TEST_PATTERN_BTN_H+MENU_FLAT_TEST_PATTERN_BTN_H)
#define MENU_COLOR_TUNER_WARING_INFO_W          (MENU_COLOR_TUNER_FRAME_W)
#define MENU_COLOR_TUNER_WARING_INFO_H          (MENU_COLOR_TUNER_FARME_H-MENU_COLOR_TUNER_WARING_INFO_Y)

/******************************************************************************/

#define DBG_LOG  1

typedef struct _COLOR_TUNER
{
    UINT8       ui1_hlt_row;
    UINT8       ui1_hlt_col;
    HANDLE_T    h_cnt_frm;
    HANDLE_T    ah_col[6];
    HANDLE_T    ah_txt_row[5];
    HANDLE_T    aah_cb_tr[5][6];
    HANDLE_T    h_on_off_btn[3];
    HANDLE_T    h_col_hlt_mov_btn;
}COLOR_TUNER;


typedef struct _SMPTE_TEST_PATTERN
{
    HANDLE_T    h_smpte_test_cnt_frm;
    HANDLE_T    h_smpte_test_num_btn;
    UINT16      ui2_val;
}SMPTE_TEST_PATTERN;

typedef struct _FLAT_TEST_PATTERN
{
    HANDLE_T    h_flat_test_cnt_frm;
    HANDLE_T    h_flat_test_num_btn;
    UINT16      ui2_val;
}FLAT_TEST_PATTERN;

typedef struct _RAMP_TEST_PATTERN
{
    HANDLE_T    h_ramp_test_cnt_frm;
    HANDLE_T    h_ramp_test_color_btn;
    UINT16      ui2_val;
}RAMP_TEST_PATTERN;

typedef struct _UNIFORMITY_ANALYZER_TEST_PATTERN
{
    HANDLE_T    h_unif_test_cnt_frm;
    HANDLE_T    h_unif_test_num_btn;
    UINT16      ui2_val;
}UNIFORMITY_ANALYZER_TEST_PATTERN;

typedef struct _FACTORY_TEST_PATTERN
{
    HANDLE_T    h_factory_test_cnt_frm;
    HANDLE_T    h_factory_test_num_btn;
    UINT16      ui2_val;
}FACTORY_TEST_PATTERN;

typedef enum
{
    E_PAT_MODE_OFF = 0,
    E_PAT_MODE_COLOR_BAR_100 = 1,
    E_PAT_MODE_COLOR_BAR_75 = 2,
    E_PAT_MODE_GRAY_BAR = 4
}APP_CUSTOM_PRE_PAT_MODE;

typedef enum
{
    MENU_COOL_CLR_TEMP = 0,
    MENU_NORMAL_CLR_TEMP,
    MENU_COMPUTER_CLR_TEMP,
    MENU_CLR_TEMP_CNT,
}MENU_CLR_TEMP;

typedef enum
{
    MENU_R_USER_SETTING = 0,
    MENU_G_USER_SETTING,
    MENU_B_USER_SETTING,
    MENU_RGB_CNT,
}MENU_RGB_USER_SETTING;
#define  RGB_GAIN_OFFSET_MIN     -100
#define  RGB_GAIN_OFFSET_MAX     100

static HANDLE_T             h_timer_tts;
static UINT32               ui4_g_ver=0;
static UINT32               ui4_g_ver_tmp=0;
static UTF16_T              w2s_g_tts[96] = {0};

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
#ifdef NEVER
static UINT8    ui1_rgb_offset_times[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM] =
                                {
                                    {0,1,2},
                                    {3,4,5},
                                    {6,7,8}
                                };
#endif /* NEVER */

/*Color Tuner*/
static UINT16 aui2_str_dims[] =
{
    MLM_MENU_KEY_COLOR_TUNER_COL_RED,
    MLM_MENU_KEY_COLOR_TUNER_COL_GREEN,
    MLM_MENU_KEY_COLOR_TUNER_COL_BLUE,
    MLM_MENU_KEY_COLOR_TUNER_COL_CYAN,
    MLM_MENU_KEY_COLOR_TUNER_COL_MAGENTA,
    MLM_MENU_KEY_COLOR_TUNER_COL_YELLOW
};

static UINT16 aui2_str_ages[] =
{
    MLM_MENU_KEY_COLOR_TUNER_ROW_HUE,
    MLM_MENU_KEY_COLOR_TUNER_ROW_SATURATION,
    MLM_MENU_KEY_COLOR_TUENR_ROW_BRIGHTNESS,
    MLM_MENU_KEY_COLOR_TUENR_ROW_OFFSET,
    MLM_MENU_KEY_COLOR_TUNER_ROW_GAIN
};



static HANDLE_T    h_base_fram;
static HANDLE_T    ah_bar;
//static HANDLE_T    ah_bar_left_btn;
//static HANDLE_T    ah_bar_right_btn;
//static BOOL          b_right;
static HANDLE_T    h_warning_info;

static BOOL b_page_show = FALSE;
#ifdef NEVER
static BOOL b_show_first = TRUE;
#endif /* NEVER */
static INT16 i2_scrn_mode = 0;
static BOOL b_warning_show = FALSE;

static HANDLE_T     h_left_arrow = NULL_HANDLE;
static HANDLE_T     h_right_arrow = NULL_HANDLE;

MENU_PAGE_FCT_TBL_T t_g_menu_common_page_pic_quality;

COLOR_TUNER           t_color_tuner;
SMPTE_TEST_PATTERN    t_smpte_test_pattern;
FLAT_TEST_PATTERN     t_flast_test_pattern;
RAMP_TEST_PATTERN     t_ramp_test_pattern;
FACTORY_TEST_PATTERN  t_factory_test_pattern;

UNIFORMITY_ANALYZER_TEST_PATTERN t_uniformity_analyzer_test_pattern;

static UINT16         ui2_yahoo_state_nfy = 0;
//static UINT16         ui2_menu_color_tuner_nfy = 0;

/*record the user setting for RGB options(by clor temp)for recovery it after ramp est pattern turn off and power off*/
/*cool(RGB)/normal(RGB)/computer(RGB)/custom(RGB)*/
static INT16          i2_user_RGB_setting[MENU_CLR_TEMP_CNT+1][MENU_RGB_CNT]={{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
//static UINT32         ui4_dynamic_address = 0;


#define MI_MM_NAME_MODEL_1            "MI_PARSE_MM_IDX_0"
#define MI_MM_PATTERN_HANDLE          "MI_MM_HANDLE_IDX_1"
#define MI_MM_DISP_HANDLE             "MI_DISP_HD0"

static MI_HANDLE               h_g_Mm         = MI_HANDLE_NULL;

/*-----------------------------------------------------------------------------
                    Global function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    Private function declarations
 ----------------------------------------------------------------------------*/
static INT32 _set_on_off_btn_attr(HANDLE_T h_widget,HANDLE_T h_col_widget, BOOL b_on,UINT8 ui1_index);

#ifdef NEVER
static INT32 _smpte_test_pattern_reset(VOID);
#endif /* NEVER */
static INT32 _smpte_test_pattern_set_value_by_id(UINT16 ui2_val);
static INT32 _smpte_test_pattern_update_txt(BOOL b_repaint);
#ifdef NEVER

static INT32 _flat_test_pattern_reset(VOID);
#endif /* NEVER */
static INT32 _flat_test_pattern_set_value_by_id(UINT16 ui2_val);
static INT32 _flat_test_pattern_update_txt(BOOL b_repaint);

#ifdef NEVER
static INT32 _ramp_test_pattern_reset(VOID);
#endif /* NEVER */
static INT32 _ramp_test_pattern_set_value_by_id(UINT16 ui2_val);
static INT32 _ramp_test_pattern_update_txt(BOOL b_repaint);

static INT32 _test_pattern_left_right_arrow_show(BOOL b_show);
static INT32 _test_pattern_left_right_arrow_create(VOID);
#ifndef APP_CAST_TEST_PATTERN_FLAT
static VOID _change_screen_mode(VOID);
#endif
static INT32 _test_pattern_warning_info_visiable(BOOL b_visiable, BOOL b_repaint);
static BOOL _test_pattern_enable(VOID);
#ifdef NEVER
static INT32 _11_point_page_update_values(VOID);
#endif /* NEVER */
static INT32 _color_tuner_get_rgb_cfg_value_with_id(UINT16 ui2_id);
static INT32 _uniformity_analyzer_test_pattern_update_txt(BOOL b_repaint);
static INT32 _smpte_test_pattern_curnt_tts_play(VOID);
static INT32 _flat_test_pattern_curnt_tts_play(VOID);
static INT32 _ramp_test_pattern_curnt_tts_play(VOID);
static INT32 _uniformity_analyzer_test_pattern_curnt_tts_play(VOID);
static INT32 _color_tuner_rollback_svc(VOID);
static INT32 _test_pattern_set_value_by_id(UINT8 ui1_type,UINT16 ui2_val);
static INT32 _menu_test_pattern_play(const CHAR* p_path ,UINT8 ui1_len);
static INT32 _menu_test_pattern_stop(VOID);
static BOOL _menu_color_tuner_is_hdmi_source(VOID);

static BOOL _menu_page_color_tuner_IsCurSrcSupportTestPattern(void);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static VOID _color_tuner_tts_play_hdlr (
    VOID* pv_ver,
    SIZE_T  z_data_size)
{
#ifdef APP_TTS_SUPPORT
   CHAR   s_buf[96] = {0};
   UINT32 ui4_ver   = 0;

   ui4_ver = *(UINT32*)pv_ver;
   if(ui4_ver != ui4_g_ver)
   {
       DBG_LOG_PRINT(("[Menu]msg exp ui4_ver:%d, ui4_g_ver:%d,%s,%d\r\n",ui4_ver,ui4_g_ver,__FUNCTION__,__LINE__));
       return;
   }

   c_uc_w2s_to_ps(w2s_g_tts,s_buf,sizeof(s_buf)-1);
   DBG_LOG_PRINT(("[Menu]tts string:%s,%s,%d\r\n",s_buf,__FUNCTION__,__LINE__));
   a_app_tts_play(w2s_g_tts,c_uc_w2s_strlen (w2s_g_tts));
#endif

}

static VOID _color_tuner_tts_play_cb(
    HANDLE_T                  h_timer,
    VOID*                     pv_ver)
{
    menu_async_invoke(_color_tuner_tts_play_hdlr, pv_ver, sizeof(UINT32), FALSE);
}

static INT32 _color_tuner_tts_play(VOID)
{
    INT32  i4_ret  = 0 ;
    i4_ret = c_timer_stop(h_timer_tts);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_ver = ui4_g_ver + 1 ;
    ui4_g_ver_tmp   = ui4_g_ver;

    i4_ret = c_timer_start(h_timer_tts,
                           100,
                           X_TIMER_FLAG_ONCE,
                           _color_tuner_tts_play_cb,
                           (VOID*)&ui4_g_ver_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#define MENU_DEBUG_TEST_PATTERN(x)  // x

static INT32 _menu_test_pattern_play_prepare(VOID)
{
    UINT8  ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    DBG_LOG_PRINT(("[MENU][TEST_PATTERN]_menu_test_pattern_play_prepare()\n" ));

    a_icl_custom_get_test_pattern_status(&ui1_val);
    DBG_LOG_PRINT(("[MENU][TEST_PATTERN] ui1_val:%d, %s,%d\r\n",ui1_val,__FUNCTION__,__LINE__));

    if (ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ != ui1_val)
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE);
        a_tv_stop_wait_for_proper(h_g_acfg_svctx_main);
        DBG_LOG_PRINT(("[MENU][TEST_PATTERN] a_tv_stop_wait_for_proper,delay 500ms \r\n"));

        if (_menu_color_tuner_is_hdmi_source ())
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] Disable game mode ,%s,%d\r\n",__FUNCTION__,__LINE__));
            a_cfg_cust_drv_set_game_mode(FALSE);
        }

        c_thread_delay(500);
    }

    a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE);

    return MENUR_OK;
}

static BOOL _color_tuner_get_disp_handle(MI_HANDLE *phDisp)
{
    char szWinName[32] = {0};
    MI_DISP_QueryHandleParams_t stDispQueryHandleParams = {0};
    MI_DISP_OpenParams_t stDispOpenParams = {E_MI_DISP_VIDWIN_HD, 0};

    c_snprintf(szWinName, sizeof(szWinName), MI_MM_DISP_HANDLE);

    stDispQueryHandleParams.pszName = (MI_U8*)szWinName;

    if(MI_DISP_GetHandle(&stDispQueryHandleParams, phDisp) != MI_OK)
    {
        stDispOpenParams.pszName = (MI_U8*)szWinName;

        MI_RESULT eMI_Result = MI_DISP_Open(&stDispOpenParams, phDisp);
        if( eMI_Result != MI_OK )
        {
            //SPLAYER_DBG_ERROR("Leave, MI_DISP_Open error\n");
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] {%s,%d} Error: MI_DISP_Open() fail => %d \n", __FUNCTION__,__LINE__, eMI_Result ));
            return FALSE;
        }
    }

    MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN] %s => handle:0x%X \n", stDispQueryHandleParams.pszName, (unsigned int)*phDisp )); );

    return TRUE;
}

static INT32 _menu_test_pattern_show(const CHAR *filePath)
{
    MI_MM_OpenParams_t      stOpenParams;
    CHAR                    szMmName[32] = {0};
    MI_HANDLE               hDisp = MI_HANDLE_NULL;
    MI_RESULT               eRet = MI_ERR_FAILED;


    if(filePath==NULL)
    {
        return -1;
    }

    DBG_LOG_PRINT(("[MENU][TEST_PATTERN] filePath :%s,%s,%d\r\n",(CHAR*)filePath,__FUNCTION__,__LINE__));

    if(!a_appl_splayer_init())
    {
        DBG_LOG_PRINT(("[MENU][TEST_PATTERN][%d][%s] MM init check \n", __LINE__, __FUNCTION__));
    }

    if(h_g_Mm != MI_HANDLE_NULL)
    {
        DBG_LOG_PRINT(("[MENU][TEST_PATTERN] stop first %s,%d\r\n",__FUNCTION__,__LINE__));
        _menu_test_pattern_stop();
    }

    do
    {
        // get disp handle
        if (_color_tuner_get_disp_handle(&hDisp) == FALSE  )
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] Fail _appl_splayer_get_disp_handle \r\n"));
            break;
        }

        eRet = MI_DISP_SetMute(hDisp,E_MI_DISP_MUTE_FLAG_FORCE);
        MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_DISP_SetMute, eRet = %d \n",eRet)); );
        if(eRet >= MI_ERR_FAILED)
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_DISP_SetMute failed,eRet = %d \n",eRet));
        }

        // open MI_MM
        c_memset(&stOpenParams, 0 ,sizeof(stOpenParams));
        c_snprintf(szMmName, sizeof(szMmName), MI_MM_NAME_MODEL_1);

        stOpenParams.pszName = (MI_U8 *)szMmName;
        stOpenParams.eMediaType = E_MI_MM_MEDIA_PHOTO;

        if(MI_OK != MI_MM_Open(&stOpenParams, &h_g_Mm))
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] Fail MI_MM_Open \r\n"));
            break;
        }

        // set AP mode
        MI_MM_ApTypeParams_t stApParams;
        c_memset(&stApParams, 0, sizeof(stApParams));
        stApParams.eApType = E_MI_MM_AP_TYPE_NORMAL;

        eRet = MI_MM_SetAttr(h_g_Mm, E_MI_MM_ATTR_TYPE_SET_AP_TYPE, (VOID *)&stApParams);
        if(eRet >= MI_ERR_FAILED)
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] Fail MI_MM_SetAttr \r\n"));
            break;
        }

        MI_MM_StartParams_t stStartParams;
        memset(&stStartParams, 0, sizeof(stStartParams));
        stStartParams.bInitOnly=FALSE;
        stStartParams.bIsLowLatencyMode = FALSE;
        stStartParams.bPreviewEnable=FALSE;
        stStartParams.pu8DirMemInputBuf =(MI_U8 *)0;  //from dram display
        stStartParams.u32DirMemInputBufLen = 0;
        stStartParams.stPreviewSetting.eMode=E_MI_MM_PREVIEW_NORMAL_MODE ;
        stStartParams.stPreviewSetting.u32VideoPauseTime=0;
        stStartParams.eFileOption=E_MI_MM_FILE_MODE;
        stStartParams.pszFileName=(MI_U8*)filePath;///--------------------------------open file pathname
        stStartParams.hDisplay = hDisp;
        //5. start display(decode) file
        eRet = MI_MM_Start(h_g_Mm, &stStartParams);
        if(eRet >= MI_ERR_FAILED)
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_MM_Start failed,eRet = %d \n",eRet));
        }

#ifdef NEVER
        //decode statue
        MI_MM_PhotoDecoderStatus_e ePhotoDecoderStatus;
        eRet= MI_MM_GetPhotoDecoderStatus(hDisp, &ePhotoDecoderStatus);
        if(eRet != MI_OK || ePhotoDecoderStatus != E_MI_MM_PHOTO_DECODE_OK)
        {
            DBG_LOG_PRINT(("-------------------------------------------!!\r\n"));
            return FALSE;
        }
#endif /* NEVER */

        //6. display related setting

        eRet = MI_MM_SetupPhotoDisplay(h_g_Mm);
        if(eRet >= MI_ERR_FAILED)
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_MM_SetupPhotoDisplay failed,eRet = %d \n",eRet));
        }


        eRet = MI_MM_ClearPhoto(h_g_Mm);
        if(eRet >= MI_ERR_FAILED)
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_MM_ClearPhoto failed,eRet = %d \n",eRet));
        }

        //7. draws the photo to display buffer
        eRet = MI_MM_DrawPhoto(h_g_Mm,0);
        if(eRet >= MI_ERR_FAILED)
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_MM_DrawPhoto failed,eRet = %d \n",eRet));
        }
        c_thread_delay(300);

        eRet = MI_DISP_SetUnMute(hDisp, E_MI_DISP_MUTE_FLAG_FORCE);
        MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_DISP_SetUnMute, eRet = %d \n",eRet)); );
        if(eRet >= MI_ERR_FAILED)
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_DISP_SetUnMute failed,eRet = %d \n",eRet));
        }

        DBG_LOG_PRINT(("[menu][TEST_PATTERN] %s,%d  ----- OK\r\n",__FUNCTION__,__LINE__));

        return MENUR_OK;
    }while(0);


    DBG_LOG_PRINT(("[menu][TEST_PATTERN] %s,%d  ----- NG\r\n",__FUNCTION__,__LINE__));

    return MENUR_FAIL;
}

#ifdef NEVER
static VOID _menu_test_pattern_fct (
    VOID* pv_data,
    SIZE_T  z_data_size)
{
   _menu_test_pattern_show((CHAR*)pv_data);

   DBG_LOG_PRINT(("[TEST_PATTERN] p_path :%s,z_data_size:%d,%s,%d\r\n",(CHAR*)pv_data,z_data_size,__FUNCTION__,__LINE__));

}
#endif /* NEVER */

static BOOL _menu_color_tuner_is_hdmi_source(VOID)
{
    ISL_REC_T                   t_isl_rec;

    c_memset (&t_isl_rec, 0, sizeof(ISL_REC_T));
    menu_get_crnt_isl(&t_isl_rec);

    //only for hdmi source
    if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
        t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
    {
        return FALSE;
    }

    return TRUE;
}
static INT32 _menu_test_pattern_play(const CHAR* p_path ,UINT8 ui1_len)
{
    if(p_path==NULL)
    {
        return -1;
    }

    DBG_LOG_PRINT(("[MENU][TEST_PATTERN]_menu_test_pattern_play(p_path :%s)\r\n", p_path ));

    _menu_test_pattern_stop();

    _menu_test_pattern_play_prepare();

    _menu_test_pattern_show(p_path);

#ifdef NEVER
    menu_async_invoke(_menu_test_pattern_fct, (VOID*)p_path, ui1_len, FALSE);
#endif /* NEVER */


    return MENUR_OK;
}

#ifdef NEVER
static VOID _menu_reload_current_input(VOID* param0, VOID* param1, VOID *param2)
{
    ISL_REC_T  t_isl_rec = {0};
    nav_get_isl_rec(TV_WIN_ID_MAIN, &t_isl_rec);
    DBG_LOG_PRINT(("[TEST_PATTERN] %s,%d\r\n",__FUNCTION__,__LINE__));
    nav_change_av_inp_by_id(TV_WIN_ID_MAIN, t_isl_rec.ui1_id, NULL);
}
#endif /* NEVER */

static INT32 _color_tuner_rollback_svc(VOID)
{
    CHAR       s_active_app[APP_NAME_MAX_LEN + 1] = {0};
    UINT8      ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    a_icl_custom_get_test_pattern_status(&ui1_val);
    DBG_LOG_PRINT(("[menu] ui1_val :%d,%s,%d\r\n",ui1_val,__FUNCTION__,__LINE__));

    if (ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ != ui1_val)
    {
        a_am_get_active_app (s_active_app);
        if (c_strcmp(s_active_app, MMP_NAME) != 0)
        {
            a_tv_start(h_g_acfg_svctx_main,FALSE);
        }
    }
    return MENUR_OK;
}

static INT32 _menu_test_pattern_stop(VOID)
{
    MI_HANDLE               hDisp       = MI_HANDLE_NULL;
    MI_RESULT               eRet = MI_ERR_FAILED;

    DBG_LOG_PRINT(("[MENU][TEST_PATTERN]_menu_test_pattern_stop()\n" ));

    if(h_g_Mm != MI_HANDLE_NULL)
    {
        // get disp handle
        if (_color_tuner_get_disp_handle(&hDisp) == FALSE  )
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] Fail _appl_splayer_get_disp_handle \r\n"));
        }
        else
        {
            eRet = MI_DISP_SetMute(hDisp,E_MI_DISP_MUTE_FLAG_VIDEO);
            if(eRet >= MI_ERR_FAILED)
            {
                DBG_LOG_PRINT(("[MENU][TEST_PATTERN] call MI_DISP_SetMute failed,eRet = %d \n",eRet));
            }
        }

        if(MI_OK != MI_MM_Stop(h_g_Mm))
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] MI_MM_Stop failed \n" ));
        }

        if(MI_OK != MI_MM_Close(h_g_Mm))
        {
            DBG_LOG_PRINT(("[MENU][TEST_PATTERN] MI_MM_Close failed \n" ));
        }
    }
    h_g_Mm = MI_HANDLE_NULL;

    return MENUR_OK;
}

VOID _menu_show_test_pattern(COLOR_CALIBRA_TEST_PATTERN_T type)
{
    INT32   i4_ret = 0;
    CHAR    s_file_path[64+1] = {0};

    DBG_LOG_PRINT(("[MENU][TEST_PATTERN] %s,type :%d\r\n",__FUNCTION__,type));

    if (SMPTE_TEST_PATTERN_ONOFF == type)
    {
        c_strncpy(s_file_path,"/data/pattern/smpte.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_10 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_10.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_20 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_20.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_30 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_30.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_40 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_40.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_50 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_50.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_60 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_60.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_70 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_70.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_80 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_80.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_90 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_90.jpg",64);
    }
    else if (FLAT_TEST_PATTERN_100 == type)
    {
        c_strncpy(s_file_path,"/data/pattern/flat_100.jpg",64);
    }
    else if (RAMP_TEST_PATTERN_BLUE == type)
    {
        c_strncpy(s_file_path,"/data/pattern/ramp_blue.png",64);
    }
    else if (RAMP_TEST_PATTERN_GREEN == type)
    {
        c_strncpy(s_file_path,"/data/pattern/ramp_green.png",64);
    }
    else if (RAMP_TEST_PATTERN_RED == type)
    {
        c_strncpy(s_file_path,"/data/pattern/ramp_red.png",64);
    }
    else if (RAMP_TEST_PATTERN_WHITE== type)
    {
        c_strncpy(s_file_path,"/data/pattern/ramp_white.png",64);
    }
    else if (UNIFORMITY_TEST_PATTERN == type)
    {
        c_strncpy(s_file_path,"/data/pattern/uniformity.jpg",64);
    }
    else if (COLOR_8_TEST_PATTERN == type)
    {
        c_strncpy(s_file_path,"/data/pattern/color_8.jpg",64);
    }
    else if (GRAY_32_TEST_PATTERN == type)
    {
        c_strncpy(s_file_path,"/data/pattern/gray_32.bmp",64);
    }
    else
    {
        DBG_LOG_PRINT(("[MENU][TEST_PATTERN] Invalid type %s,%d\r\n",__FUNCTION__,__LINE__));
        return;
    }

    i4_ret = _menu_test_pattern_play(s_file_path,sizeof(s_file_path));
    MENU_LOG_ON_FAIL(i4_ret);

}

/**********************************Color Tuner Page************************************************************************/

/*----------------------------------------------------------------------------
 * Name: _color_tuner_update_rgb_on_off_value
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
static INT32 _color_tuner_update_rgb_on_off_value(VOID)
{
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    INT16  i2GOnOff = 0;
    INT16  i2BOnOff = 0;
    BOOL   b_on = TRUE;
    INT32  i4_ret = 0;

    /*Red*/
    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    i4_ret = a_cfg_av_get( ui2_id, &i2ROnOff);
#if DBG_LOG
    DBG_INFO(("\n==[color:RED]==[on/off:%d],[ui2_id:APP_CFG_RECID_FILESYS_RED],[i4_ret:%d]=[line:%d]===\n",i2ROnOff , i4_ret,__LINE__));
#endif

    b_on = i2ROnOff == 0 ? FALSE : TRUE;

    i4_ret = _set_on_off_btn_attr(t_color_tuner.h_on_off_btn[COL_RED],
                                          t_color_tuner.ah_col[COL_RED],
                                           b_on,
                                           COL_RED);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Green*/
    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
    i4_ret = a_cfg_av_get( ui2_id, &i2GOnOff);
#if DBG_LOG
    DBG_INFO(("\n==[color:Green]==[on/off:%d],[ui2_id:APP_CFG_RECID_FILESYS_GREEN],[i4_ret:%d]=[line:%d]===\n",i2GOnOff, i4_ret,__LINE__));
#endif


    b_on = i2GOnOff == 0 ? FALSE : TRUE;

    i4_ret = _set_on_off_btn_attr(t_color_tuner.h_on_off_btn[COL_GREEN],
                                          t_color_tuner.ah_col[COL_GREEN],
                                           b_on,
                                           COL_GREEN);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Blue*/

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
    i4_ret = a_cfg_av_get( ui2_id, &i2BOnOff);
#if DBG_LOG
    DBG_INFO(("\n==[color:Blue]==[on/off:%d],[ui2_id:APP_CFG_RECID_FILESYS_BLUE],[i4_ret:%d]=[line:%d]===\n",i2ROnOff,i4_ret,__LINE__));
#endif

    b_on = i2BOnOff == 0 ? FALSE : TRUE;

    i4_ret = _set_on_off_btn_attr(t_color_tuner.h_on_off_btn[COL_BLUE],
                                          t_color_tuner.ah_col[COL_BLUE],
                                           b_on,
                                           COL_BLUE);
    MENU_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
    i4_ret = a_cfg_custom_set_rgb_on_off((UINT8)i2ROnOff,(UINT8)i2GOnOff,(UINT8)i2BOnOff);
    MENU_LOG_ON_FAIL(i4_ret);
#endif /* NEVER */

    return i4_ret;

}

/*----------------------------------------------------------------------------
 * Name: _color_tuner_update_unit_value
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
static INT32 _color_tuner_update_unit_value(VOID)
{
    UINT8       ui1_row = 0;
    UINT8       ui1_colume = 0;
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16       i2_vid_eq_val = 0;
    CHAR        s_buf[APP_VALUE_LEN]={0};
    UTF16_T     ws_buf[APP_VALUE_LEN]={0};

    for (ui1_row=0; ui1_row<=ROW_GAIN; ui1_row++)
    {
        for (ui1_colume=0; ui1_colume<=COL_YELLOW; ui1_colume++)
        {
            if(ui1_row == ROW_HUE)
            {
                if(ui1_colume == COL_RED)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R);
                }
                else if(ui1_colume == COL_GREEN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G);
                }
                else if(ui1_colume == COL_BLUE)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B);
                }
                else if(ui1_colume == COL_CYAN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C);
                }
                else if(ui1_colume == COL_MAGENTA)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M);
                }
                else
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y);
                }

                a_cfg_av_get( ui2_id, &i2_vid_eq_val);
                c_sprintf(s_buf, "%d",i2_vid_eq_val);
            }
            else if(ui1_row == ROW_SATURATION)
            {
                if(ui1_colume == COL_RED)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R);
                }
                else if(ui1_colume == COL_GREEN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G);
                }
                else if(ui1_colume == COL_BLUE)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B);
                }
                else if(ui1_colume == COL_CYAN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C);
                }
                else if(ui1_colume == COL_MAGENTA)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M);
                }
                else
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y);
                }

                a_cfg_av_get( ui2_id, &i2_vid_eq_val);
                c_sprintf(s_buf, "%d",i2_vid_eq_val);
            }

            else if(ui1_row == ROW_BRIGHTNESS)
            {
                if(ui1_colume == COL_RED)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R);
                }
                else if(ui1_colume == COL_GREEN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G);
                }
                else if(ui1_colume == COL_BLUE)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B);
                }
                else if(ui1_colume == COL_CYAN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C);
                }
                else if(ui1_colume == COL_MAGENTA)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M);
                }
                else
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y);
                }

                a_cfg_av_get( ui2_id, &i2_vid_eq_val);
                c_sprintf(s_buf, "%d",i2_vid_eq_val);
            }

            else if(ui1_row == ROW_OFFSET)
            {
                if(ui1_colume == COL_RED)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R);
                }
                else if(ui1_colume == COL_GREEN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G);
                }
                else if(ui1_colume == COL_BLUE)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B);
                }

                a_cfg_av_get( ui2_id, &i2_vid_eq_val);

                c_sprintf(s_buf, "%d",i2_vid_eq_val);
            }

            else if(ui1_row == ROW_GAIN)
            {
                if(ui1_colume == COL_RED)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R);
                }
                else if(ui1_colume == COL_GREEN)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_G);
                }
                else if(ui1_colume == COL_BLUE)
                {
                    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_B);
                }

                a_cfg_av_get( ui2_id, &i2_vid_eq_val);

                c_sprintf(s_buf, "%d",i2_vid_eq_val);
            }

            c_uc_ps_to_w2s(s_buf, ws_buf, APP_VALUE_LEN);

            c_wgl_do_cmd(t_color_tuner.aah_cb_tr[ui1_row][ui1_colume],
                               WGL_CMD_BTN_SET_TEXT,
                               WGL_PACK (ws_buf),
                               WGL_PACK (c_uc_w2s_strlen (ws_buf)));
        }
    }

    return MENUR_OK;
}
#ifdef NEVER

/*----------------------------------------------------------------------------
 * Name: _color_tuner_rgb_update
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
static INT32 _color_tuner_rgb_update(VOID)
{
    INT16       i2ROnOff = 0;
    INT16       i2GOnOff = 0;
    INT16       i2BOnOff = 0;
    INT32       i4_ret   = 0;
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    i4_ret = a_cfg_av_get( ui2_id, &i2ROnOff);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
    i4_ret = a_cfg_av_get( ui2_id, &i2GOnOff);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
    i4_ret = a_cfg_av_get( ui2_id, &i2BOnOff);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_rgb_on_off((UINT8)i2ROnOff,(UINT8)i2GOnOff,(UINT8)i2BOnOff);
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;

}
#endif /* NEVER */

INT32 a_color_tuner_update_ui(VOID)
{
    _color_tuner_update_rgb_on_off_value();
    _color_tuner_update_unit_value();
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_color_tuner_update_value
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
INT32 a_color_tuner_update_value(VOID)
{
    INT32 i4_ret = 0;

    //update r g b
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED));
    MENU_LOG_ON_FAIL(i4_ret);

    //update  hsb
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R));
    MENU_LOG_ON_FAIL(i4_ret);

    //update  2p wb
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 a_menu_exit_test_patterns_by_power(VOID)
{
    DBG_LOG_PRINT(("[menu] %s,%d\r\n",__FUNCTION__,__LINE__));
    a_menu_test_patterns_turn_off();

#ifdef NEVER
    if (t_smpte_test_pattern.ui2_val != 0)
    {
        t_smpte_test_pattern.ui2_val = 0;
        _smpte_test_pattern_update_txt(FALSE);
    }

    if (t_flast_test_pattern.ui2_val != 0)
    {
        t_flast_test_pattern.ui2_val = 0;
        _flat_test_pattern_update_txt(FALSE);
    }

    if (t_ramp_test_pattern.ui2_val != 0)
    {
        t_ramp_test_pattern.ui2_val = 0;
        _ramp_test_pattern_update_txt(FALSE);
    }

    if (t_uniformity_analyzer_test_pattern.ui2_val != 0)
    {
        t_uniformity_analyzer_test_pattern.ui2_val = 0;
        _uniformity_analyzer_test_pattern_update_txt(FALSE);
    }
#endif /* NEVER */

    return MENUR_OK;
}

VOID a_menu_test_patterns_clean_warming_msg(VOID)
{
      _test_pattern_warning_info_visiable(FALSE, TRUE);
}


BOOL a_menu_test_patterns_is_show(VOID)
{
    BOOL is_show = TRUE;
    if(t_smpte_test_pattern.ui2_val == 0 &&
       t_flast_test_pattern.ui2_val == 0 &&
       t_ramp_test_pattern.ui2_val == 0 &&
       t_uniformity_analyzer_test_pattern.ui2_val == 0 &&
       t_factory_test_pattern.ui2_val == 0)
    {
        is_show =  FALSE;
    }

    return is_show;
}
/*----------------------------------------------------------------------------
 * Name: a_test_patterns_update_value
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
INT32 a_menu_test_patterns_turn_off(VOID)
{
    if(t_smpte_test_pattern.ui2_val == 0 &&
       t_flast_test_pattern.ui2_val == 0 &&
       t_ramp_test_pattern.ui2_val == 0 &&
       t_uniformity_analyzer_test_pattern.ui2_val == 0 &&
       t_factory_test_pattern.ui2_val == 0)
    {
        return MENUR_OK;
    }
    DBG_LOG_PRINT(("[menu] %s,%d\r\n",__FUNCTION__,__LINE__));

    if((t_smpte_test_pattern.ui2_val != 0) ||
        (t_ramp_test_pattern.ui2_val != 0) ||
        (t_flast_test_pattern.ui2_val != 0) ||
        (t_uniformity_analyzer_test_pattern.ui2_val != 0) ||
        (t_factory_test_pattern.ui2_val != 0))
    {
        banner_view_set_b_ctrl_show_flag(TRUE);
        _menu_test_pattern_stop();
        t_smpte_test_pattern.ui2_val = 0;
        t_flast_test_pattern.ui2_val = 0;
        t_ramp_test_pattern.ui2_val = 0;
        t_uniformity_analyzer_test_pattern.ui2_val = 0;
        t_factory_test_pattern.ui2_val = 0;

        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_DISABLE);

        c_thread_delay(100);
    }

#ifdef NEVER
    UINT16 ui2_page_index = 0;
    UINT32 ui4_cur_page_id = 0xFFFFFFFF;
    extern UINT32 ui4_g_menu_custom_page_pic_quality;
    menu_nav_get_crnt_page(&ui4_cur_page_id);

    if (ui4_cur_page_id != ui4_g_menu_custom_page_pic_quality)
    {
        return MENUR_OK;
    }

    if (t_smpte_test_pattern.ui2_val != 0)
    {
        t_smpte_test_pattern.ui2_val = 0;
        _smpte_test_pattern_update_txt(FALSE);
    }

    if (t_flast_test_pattern.ui2_val != 0)
    {
        t_flast_test_pattern.ui2_val = 0;
        _flat_test_pattern_update_txt(FALSE);
    }

    if (t_ramp_test_pattern.ui2_val != 0)
    {
        t_ramp_test_pattern.ui2_val = 0;
        _ramp_test_pattern_update_txt(FALSE);
    }

    if (t_uniformity_analyzer_test_pattern.ui2_val != 0)
    {
        t_uniformity_analyzer_test_pattern.ui2_val = 0;
        _uniformity_analyzer_test_pattern_update_txt(FALSE);
    }
    _test_pattern_warning_info_visiable(TRUE, TRUE);

    a_cfg_custom_get_pic_quality_page(&ui2_page_index);
    DBG_LOG_PRINT(("[MENU][%s %d],ui2_page_index = %d,enable = %d\n",__FUNCTION__,__LINE__,ui2_page_index,_test_pattern_enable()));
    switch (ui2_page_index)
    {
        case PAGE_SMPTE_TEST_PATTERN:
        case PAGE_FLAT_TEST_PATTERN:
        case PAGE_RAMP_TEST_PATTERN:
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
        {
            if (_test_pattern_enable() == FALSE)
            {
                _test_pattern_warning_info_visiable(FALSE, TRUE);
                if (b_page_show)
                {
                    c_wgl_set_focus(ah_bar, WGL_SYNC_AUTO_REPAINT);
                }
            }
            else
            {
                _test_pattern_warning_info_visiable(TRUE, TRUE);
            }
            break;
        }
        default:
            break;
    }
#endif /* NEVER */

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _set_on_off_btn_attr
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
 static INT32 _set_on_off_btn_attr(HANDLE_T h_widget,HANDLE_T h_col_widget, BOOL b_on,UINT8 ui1_index)
{
    INT32                   i4_ret = MENUR_OK;
    WGL_COLOR_INFO_T   t_clr_info;
    WGL_IMG_INFO_T      t_img_info;

    if(!b_on)
    {
         /* Set Image */
         t_img_info.e_type = WGL_COLOR_SET_EXTEND;
         t_img_info.u_img_data.t_extend.t_disable   = h_g_menu_ColorTuner_ColorOff;
         t_img_info.u_img_data.t_extend.t_enable      = h_g_menu_ColorTuner_ColorOff;
         t_img_info.u_img_data.t_extend.t_disable   = h_g_menu_ColorTuner_ColorOff;
         t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_ColorTuner_ColorOff;
         t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_ColorTuner_ColorOff;
         t_img_info.u_img_data.t_extend.t_push = h_g_menu_ColorTuner_ColorOff;
         t_img_info.u_img_data.t_extend.t_push_unhighlight = h_g_menu_ColorTuner_ColorOff;

         i4_ret = c_wgl_do_cmd(h_widget,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_BK),
                               WGL_PACK(&t_img_info));

         MENU_LOG_ON_FAIL(i4_ret);

         /* Set Alignment */
         i4_ret = c_wgl_do_cmd(h_widget,
                               WGL_CMD_BTN_SET_ALIGN,
                               WGL_PACK(WGL_AS_CENTER_CENTER),
                               NULL);
         MENU_LOG_ON_FAIL(i4_ret);
         #if DBG_LOG
         DBG_INFO(("\n=====_set_on_off_btn_attr========[b_on: %d]==[line:%d],[i4_ret:%d]\n",b_on,i4_ret,__LINE__));
         #endif
         /* Set Color */
         t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
         t_clr_info.u_color_data.t_extend.t_enable             = t_g_menu_color_bk1_txt_disable;
         t_clr_info.u_color_data.t_extend.t_disable            = t_g_menu_color_bk1_txt_disable;
         t_clr_info.u_color_data.t_extend.t_highlight          = t_g_menu_color_bk1_txt_disable;
         t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_bk1_txt_disable;
         t_clr_info.u_color_data.t_extend.t_push               = t_g_menu_color_bk1_txt_disable;
         t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_menu_color_bk1_txt_disable;
         i4_ret = c_wgl_do_cmd(h_col_widget,
                               WGL_CMD_GL_SET_COLOR,
                               WGL_PACK(WGL_CLR_TEXT),
                               WGL_PACK(&t_clr_info ));
         MENU_LOG_ON_FAIL(i4_ret);
         #if DBG_LOG
         DBG_INFO(("\n=====_set_on_off_btn_attr========[b_on: %d]==[line:%d],[i4_ret:%d]\n",b_on,i4_ret,__LINE__));
         #endif
    }

    else
    {
         /* Set Image */
         t_img_info.e_type = WGL_COLOR_SET_EXTEND;
         t_img_info.u_img_data.t_extend.t_disable   = NULL_HANDLE;
         t_img_info.u_img_data.t_extend.t_enable      = NULL_HANDLE;
         t_img_info.u_img_data.t_extend.t_disable   = NULL_HANDLE;
         t_img_info.u_img_data.t_extend.t_highlight = NULL_HANDLE;
         t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
         t_img_info.u_img_data.t_extend.t_push = NULL_HANDLE;
         t_img_info.u_img_data.t_extend.t_push_unhighlight = NULL_HANDLE;

         i4_ret = c_wgl_do_cmd(h_widget,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_BK),
                               WGL_PACK(&t_img_info));
         MENU_LOG_ON_FAIL(i4_ret);

         /* Set Alignment */
         i4_ret = c_wgl_do_cmd(h_widget,
                               WGL_CMD_BTN_SET_ALIGN,
                               WGL_PACK(WGL_AS_CENTER_CENTER),
                               NULL);
         MENU_LOG_ON_FAIL(i4_ret);
         #if DBG_LOG
         DBG_INFO(("\n=====_set_on_off_btn_attr========[b_on: %d]==[line:%d],[i4_ret:%d]\n",b_on,i4_ret,__LINE__));
         #endif
         /* Set Color */
         t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
         t_clr_info.u_color_data.t_extend.t_enable             = t_g_menu_color_black;
         t_clr_info.u_color_data.t_extend.t_disable            = t_g_menu_color_black;
         t_clr_info.u_color_data.t_extend.t_highlight          = t_g_menu_color_black;
         t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_black;
         t_clr_info.u_color_data.t_extend.t_push               = t_g_menu_color_black;
         t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_menu_color_black;
         i4_ret = c_wgl_do_cmd(h_col_widget,
                               WGL_CMD_GL_SET_COLOR,
                               WGL_PACK(WGL_CLR_TEXT),
                               WGL_PACK(&t_clr_info ));
         MENU_LOG_ON_FAIL(i4_ret);
         #if DBG_LOG
         DBG_INFO(("\n=====_set_on_off_btn_attr========[b_on: %d]==[line:%d],[i4_ret:%d]\n",b_on,i4_ret,__LINE__));
         #endif
    }

    c_wgl_repaint(t_color_tuner.h_cnt_frm,NULL,TRUE);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
* Name: _color_tuner_page_unit_proc_fct
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
static INT32 _btn_rgb_on_off_proc(VOID)
{
    INT32  i4_ret = MENUR_OK;
    UINT16 ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    INT16  i2GOnOff = 0;
    INT16  i2BOnOff = 0;
    INT16  i2_new_ROnOff = 0;
    INT16  i2_new_GOnOff = 0;
    INT16  i2_new_BOnOff = 0;
    INT16  i2_val = 1;
    INT16  i2_pic_mode = 0;
    UTF16_T     w2s_str[256] = {0};


    if( t_color_tuner.ui1_hlt_col >= 6 )
    {
        return MENUR_FAIL;
    }


    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    i4_ret = a_cfg_av_get( ui2_id, &i2ROnOff);
    MENU_LOG_ON_FAIL(i4_ret);
    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
    i4_ret = a_cfg_av_get( ui2_id, &i2GOnOff);
    MENU_LOG_ON_FAIL(i4_ret);
    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
    i4_ret = a_cfg_av_get( ui2_id, &i2BOnOff);
    MENU_LOG_ON_FAIL(i4_ret);

    i2_new_ROnOff = i2ROnOff;
    i2_new_GOnOff = i2GOnOff;
    i2_new_BOnOff = i2BOnOff;

    if(COL_RED == t_color_tuner.ui1_hlt_col)
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
        i2_val = i2ROnOff == RGB_OFF ?  RGB_ON : RGB_OFF;
        i2_new_ROnOff = i2_val;
    }
    else if(COL_GREEN == t_color_tuner.ui1_hlt_col)
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
        i2_val = i2GOnOff == RGB_OFF ?  RGB_ON : RGB_OFF;
        i2_new_GOnOff = i2_val;
    }
    else if(COL_BLUE == t_color_tuner.ui1_hlt_col)
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
        i2_val = i2BOnOff == RGB_OFF ?  RGB_ON : RGB_OFF;
        i2_new_BOnOff = i2_val;
    }

    if((i2ROnOff + i2GOnOff + i2BOnOff) == 1)// don't allow the case RGB:000
    {
        if(i2_val == 0)
        {
            return i4_ret;
        }
    }

    i4_ret=a_cfg_av_set(ui2_id, i2_val);
    _color_tuner_get_rgb_cfg_value_with_id(ui2_id);

    i4_ret = a_cfg_custom_set_rgb_on_off((UINT8)i2_new_ROnOff,(UINT8)i2_new_GOnOff,(UINT8)i2_new_BOnOff);
    MENU_LOG_ON_FAIL(i4_ret);


    // Fix-Coverity: 4491229:Negative array index read
    if( t_color_tuner.ui1_hlt_col >= 3 )
    {
        DBG_LOG_PRINT(("[MENU][ColorTuner] {%s,%d} Error: t_color_tuner.ui1_hlt_col:%d >= 3\n",__FUNCTION__,__LINE__, t_color_tuner.ui1_hlt_col ));
    }
    else
    {
        i4_ret=_set_on_off_btn_attr( t_color_tuner.h_on_off_btn[t_color_tuner.ui1_hlt_col],
                                     t_color_tuner.ah_col[t_color_tuner.ui1_hlt_col],
                                     i2_val,
                                     t_color_tuner.ui1_hlt_col);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
    MENU_CHK_FAIL(i4_ret);

    a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode, TRUE);

    if((t_color_tuner.ui1_hlt_col>=COL_RED)&&(t_color_tuner.ui1_hlt_col<=COL_BLUE))
    {
        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(aui2_str_dims[t_color_tuner.ui1_hlt_col]));
        c_uc_w2s_strcat(w2s_str, _TEXT("."));
        if(i2_val == 1)
        {
            c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_ON));
        }
        else
        {
            c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
        }

        c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
        c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
        _color_tuner_tts_play();
    }

    menu_pic_energy_change_sepcial_page_set_status(TRUE);

    return i4_ret;
}

static INT16 _get_current_test_pattern_value(UINT16 ui2_page_type)
{
    INT16 ui2_val = 0;

    switch (ui2_page_type)
    {
    case PAGE_SMPTE_TEST_PATTERN:
        ui2_val = t_smpte_test_pattern.ui2_val;
        break;
    case PAGE_FLAT_TEST_PATTERN:
        ui2_val = t_flast_test_pattern.ui2_val;
        break;
    case PAGE_RAMP_TEST_PATTERN:
        ui2_val = t_ramp_test_pattern.ui2_val;
        break;
    case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
        ui2_val = t_uniformity_analyzer_test_pattern.ui2_val;
        break;
    case PAGE_FACTORY_TEST_PATTERN:
        ui2_val = t_factory_test_pattern.ui2_val;
        break;
    default:
        ui2_val = 0;
        break;
    }

    return ui2_val;
}

INT16 menu_get_current_smpte_test_pattern_value(VOID)
{
    return _get_current_test_pattern_value(PAGE_SMPTE_TEST_PATTERN);
}

INT16 menu_get_current_uniformity_analyzer_test_pattern_value(VOID)
{
    return _get_current_test_pattern_value(PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN);
}
/*----------------------------------------------------------------------------
 * Name: _color_tuner_page_curnt_unit_tts_play
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
static INT32 _color_tuner_page_curnt_unit_tts_play(UINT8 ui1_hlt_row, INT8 ui1_hlt_col)
{
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16       i2_vid_eq_val = 0;
    CHAR        s_buf[32]     ={0};
    UTF16_T     ws_buf[32]={0};
    UINT16      ui2_msgid_title_v = 0;
    UINT16      ui2_msgid_title_h = 0;
    UTF16_T     w2s_str[256] = {0};

    if(ui1_hlt_row == ROW_HUE)
    {
        ui2_msgid_title_h = MLM_MENU_KEY_COLOR_TUNER_COL_RED;
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B);
        }
        else if(ui1_hlt_col == COL_CYAN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C);
        }
        else if(ui1_hlt_col == COL_MAGENTA)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M);
        }
        else
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y);
        }
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);
        //c_sprintf(s_buf, "%s %d",i2_vid_eq_val < 0 ? "dash" : "" ,ABS(i2_vid_eq_val));
    }
    else if(ui1_hlt_row == ROW_SATURATION)
    {
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B);
        }
        else if(ui1_hlt_col == COL_CYAN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C);
        }
        else if(ui1_hlt_col == COL_MAGENTA)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M);
        }
        else
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y);
        }
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);
        //c_sprintf(s_buf, "%s %d",i2_vid_eq_val < 0 ? "dash":"" ,ABS(i2_vid_eq_val));
    }
    else if(ui1_hlt_row == ROW_BRIGHTNESS)
    {
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B);
        }
        else if(ui1_hlt_col == COL_CYAN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C);
        }
        else if(ui1_hlt_col == COL_MAGENTA)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M);
        }
        else
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y);
        }
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);
        //c_sprintf(s_buf, "%s %d",i2_vid_eq_val < 0 ? "dash ":"" ,ABS(i2_vid_eq_val));
    }
#if 0
    else if(ui1_hlt_row == ROW_OFFSET)
    {
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B);
        }
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);
        //c_sprintf(s_buf, "%s %d",i2_vid_eq_val < 0 ? "dash":"" ,ABS(i2_vid_eq_val));
    }
    else if(ui1_hlt_row == ROW_GAIN)
    {
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_B);
        }
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);
        //c_sprintf(s_buf, "%s %d",i2_vid_eq_val < 0 ? "dash":"" ,ABS(i2_vid_eq_val));

    }
#endif

    if(i2_vid_eq_val >= 0)
    {
        c_sprintf(s_buf, "%d",i2_vid_eq_val);
    }
    else
    {
        c_sprintf(s_buf, "minus %d",ABS(i2_vid_eq_val));
    }

    if((ui1_hlt_row>=ROW_HUE)&&(ui1_hlt_row<=ROW_GAIN))
    {
        ui2_msgid_title_v = aui2_str_ages[ui1_hlt_row];
        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(ui2_msgid_title_v));
        c_uc_w2s_strcat(w2s_str, _TEXT("."));
    }

    if((ui1_hlt_col>=COL_RED)&&(ui1_hlt_col<=COL_YELLOW))
    {
        ui2_msgid_title_h = aui2_str_dims[ui1_hlt_col];
        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(ui2_msgid_title_h));
        c_uc_w2s_strcat(w2s_str, _TEXT("."));
    }
    c_uc_ps_to_w2s(s_buf, ws_buf, c_strlen(s_buf));
    c_uc_w2s_strcat(w2s_str, ws_buf);
    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
    _color_tuner_tts_play();

    return MENUR_OK;
}

 /*----------------------------------------------------------------------------
  * Name: _color_tuner_col_title_proc
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
 static INT32 _color_tuner_col_title_proc(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    UINT32          ui4_keycode = (UINT32)pv_param1;
    //INT32         i4_ret = MENUR_OK;
    GL_RECT_T       t_rect = {0};
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    UTF16_T w2s_str[256] = {0};

    switch (ui4_msg)
    {
          case WGL_MSG_KEY_DOWN:
          {
              switch (ui4_keycode)
              {
                  case BTN_CURSOR_UP:
                     c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn,WGL_SW_HIDE);
                     c_wgl_repaint(t_color_tuner.h_col_hlt_mov_btn,NULL,TRUE);
                     c_wgl_set_focus(ah_bar,TRUE);
                     c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                     c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE));
                     _color_tuner_tts_play();
                      break;
                  case BTN_CURSOR_DOWN:
                     t_color_tuner.ui1_hlt_row = ROW_HUE;
                     c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn,WGL_SW_HIDE);
                     c_wgl_repaint(t_color_tuner.h_col_hlt_mov_btn,NULL,TRUE);
                     c_wgl_set_focus(t_color_tuner.aah_cb_tr[t_color_tuner.ui1_hlt_row][t_color_tuner.ui1_hlt_col],TRUE);
                     _color_tuner_page_curnt_unit_tts_play(t_color_tuner.ui1_hlt_row,t_color_tuner.ui1_hlt_col);
                      break;
                  case BTN_CURSOR_LEFT:
                      t_color_tuner.ui1_hlt_col = (t_color_tuner.ui1_hlt_col + 3 - 1)%3;
                      c_wgl_set_focus(t_color_tuner.ah_col[t_color_tuner.ui1_hlt_col],TRUE);
                      c_wgl_get_coords(t_color_tuner.h_col_hlt_mov_btn,WGL_COORDS_PARENT,&t_rect);
                      t_rect.i4_left  = RED_ON_OFF_HLT_MOVE_BTN_X + (RED_ON_OFF_HLT_MOVE_BTN_X_OFFSET + RED_ON_OFF_BTN_LINE)*t_color_tuner.ui1_hlt_col;
                      t_rect.i4_right  = t_rect.i4_left + RED_ON_OFF_HLT_MOVE_BTN_W;
                      c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn,WGL_SW_NORMAL);
                      c_wgl_move(t_color_tuner.h_col_hlt_mov_btn,&t_rect,TRUE);

                      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, (APP_CFG_RECID_VID_RED+t_color_tuner.ui1_hlt_col));
                      a_cfg_av_get( ui2_id, &i2ROnOff);
                      c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(aui2_str_dims[t_color_tuner.ui1_hlt_col]));
                      c_uc_w2s_strcat(w2s_str, _TEXT("."));
                      if(i2ROnOff == 1)
                      {
                        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_ON));
                      }
                      else
                      {
                        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
                      }
                      c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                      c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
                      _color_tuner_tts_play();

                      break;

                  case BTN_CURSOR_RIGHT:
                      t_color_tuner.ui1_hlt_col = (t_color_tuner.ui1_hlt_col + 1)%3;
                      c_wgl_set_focus(t_color_tuner.ah_col[t_color_tuner.ui1_hlt_col],TRUE);
                      c_wgl_get_coords(t_color_tuner.h_col_hlt_mov_btn,WGL_COORDS_PARENT,&t_rect);
                      t_rect.i4_left  = RED_ON_OFF_HLT_MOVE_BTN_X + (RED_ON_OFF_HLT_MOVE_BTN_X_OFFSET +RED_ON_OFF_BTN_LINE)*t_color_tuner.ui1_hlt_col;
                      t_rect.i4_right  = t_rect.i4_left + RED_ON_OFF_HLT_MOVE_BTN_W;
                      c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn,WGL_SW_NORMAL);
                      c_wgl_move(t_color_tuner.h_col_hlt_mov_btn,&t_rect,TRUE);
                      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, (APP_CFG_RECID_VID_RED+t_color_tuner.ui1_hlt_col));
                      a_cfg_av_get( ui2_id, &i2ROnOff);
                      c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(aui2_str_dims[t_color_tuner.ui1_hlt_col]));
                      c_uc_w2s_strcat(w2s_str, _TEXT("."));
                      if(i2ROnOff == 1)
                      {
                        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_ON));
                      }
                      else
                      {
                        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
                      }

                        c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));

                        c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
                        _color_tuner_tts_play();

                      break;

                  case BTN_RETURN:
                      /* Let the menu show */
                      c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
                      c_wgl_repaint(h_base_fram,NULL,TRUE);
                      menu_main_set_visibility(TRUE);
                      menu_nav_back();

                      break;
                 case BTN_SELECT:
                     if(t_color_tuner.ui1_hlt_col > COL_BLUE)
                     {
                        break;
                     }
                     else
                     {
                        _btn_rgb_on_off_proc();
                        break;
                     }

                  default:
                      break;
              }
          }
          default:
              break;
      }
      return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

}


/*----------------------------------------------------------------------------
 * Name: _color_tuner_page_unit_proc_fct
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
 static INT32 _color_tuner_page_unit_proc_fct(VOID*  pv_param1,UINT8 ui1_hlt_row, INT8 ui1_hlt_col)
{
    UINT32      ui4_keycode = (UINT32)pv_param1;
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16       i2_vid_eq_val = 0;
    INT16       i2_min, i2_max;
    CHAR        s_buf[32]={0};
    UTF16_T     ws_buf[32]={0};
    INT32       i4_ret = MENUR_OK;
    UINT8       ui1_color = 0;
    INT16       i2_clr_temp = 0;
    INT16       i2_pic_mode = 0;

    if(ui1_hlt_row == ROW_HUE)
    {
        ui1_color = ui1_hlt_col;

        if(ui1_color == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R);
        }
        else if(ui1_color == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G);
        }
        else if(ui1_color == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B);
        }
        else if(ui1_color == COL_CYAN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C);
        }
        else if(ui1_color == COL_MAGENTA)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M);
        }
        else
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y);
        }

        a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);

        if(ui4_keycode == BTN_CURSOR_LEFT)
        {
            i2_vid_eq_val --;
            if (i2_vid_eq_val < i2_min)
            {
                i2_vid_eq_val = i2_min;
            }
        }
        if(ui4_keycode == BTN_CURSOR_RIGHT)
        {
            i2_vid_eq_val ++;
            if (i2_vid_eq_val > i2_max)
            {
                i2_vid_eq_val = i2_max;
            }
        }
        a_cfg_av_set(ui2_id, i2_vid_eq_val);

        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_HUE);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
        MENU_CHK_FAIL(i4_ret);
        a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode, TRUE);
    }
    else if(ui1_hlt_row == ROW_SATURATION)
    {
        ui1_color = ui1_hlt_col;
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B);
        }
        else if(ui1_hlt_col == COL_CYAN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C);
        }
        else if(ui1_hlt_col == COL_MAGENTA)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M);
        }
        else
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y);
        }

        a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);
        if(ui4_keycode == BTN_CURSOR_LEFT)
        {
            i2_vid_eq_val--;
            if(i2_vid_eq_val < i2_min)
            {
                i2_vid_eq_val = i2_min;
            }
        }
        if(ui4_keycode == BTN_CURSOR_RIGHT)
        {
            i2_vid_eq_val++;
            if(i2_vid_eq_val > i2_max)
            {
                i2_vid_eq_val = i2_max;
            }
        }
        a_cfg_av_set( ui2_id, i2_vid_eq_val);
        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_SAT);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
        MENU_CHK_FAIL(i4_ret);
        a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode, TRUE);
    }
    else if(ui1_hlt_row == ROW_BRIGHTNESS)
    {
        ui1_color = ui1_hlt_col;
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B);
        }
        else if(ui1_hlt_col == COL_CYAN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C);
        }
        else if(ui1_hlt_col == COL_MAGENTA)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M);
        }
        else
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y);
        }

        a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);
        if(ui4_keycode == BTN_CURSOR_LEFT)
        {
            i2_vid_eq_val--;
            if(i2_vid_eq_val < i2_min)
            {
                i2_vid_eq_val = i2_min;
            }
        }
        if(ui4_keycode == BTN_CURSOR_RIGHT)
        {
            i2_vid_eq_val++;
            if(i2_vid_eq_val > i2_max)
            {
                i2_vid_eq_val = i2_max;
            }
        }
        a_cfg_av_set( ui2_id, i2_vid_eq_val);
        a_cfg_cust_user_set_color_tuner_hsb(ACFG_COLOR_TUNER_BRI);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), &i2_pic_mode);
        MENU_CHK_FAIL(i4_ret);
        a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode, TRUE);
    }

    else if(ui1_hlt_row == ROW_OFFSET)
    {
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B);
        }

        a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);

        if(ui4_keycode == BTN_CURSOR_LEFT)
        {
            if (i2_vid_eq_val <= ACFG_CUST_CLR_GAIN_OFFSET_MIN)
            {
                /* do nothing*/
            }
            else
            {
                i2_vid_eq_val = i2_vid_eq_val - 1;
            }
        }
        else if(ui4_keycode == BTN_CURSOR_RIGHT)
        {
            if (i2_vid_eq_val >= ACFG_CUST_CLR_GAIN_OFFSET_MAX)
            {
                /* do nothing*/
            }
            else
            {
                i2_vid_eq_val = i2_vid_eq_val + 1;
            }
        }

        a_cfg_av_set(ui2_id, i2_vid_eq_val);
        a_cfg_av_update(ui2_id);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
        MENU_CHK_FAIL(i4_ret);

        a_cfg_set_clr_temp_chg_status(i2_clr_temp,TRUE);

    }

    else if(ui1_hlt_row == ROW_GAIN)
    {
        if(ui1_hlt_col == COL_RED)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R);
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_G);
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_B);
        }

        a_cfg_av_get_min_max( ui2_id, &i2_min, &i2_max);
        a_cfg_av_get( ui2_id, &i2_vid_eq_val);

        if(ui4_keycode == BTN_CURSOR_LEFT)
        {
            if (i2_vid_eq_val <= ACFG_CUST_CLR_GAIN_OFFSET_MIN)
            {
                /* do nothing*/
            }
            else
            {
                i2_vid_eq_val = i2_vid_eq_val - 1;
            }
        }
        else if(ui4_keycode == BTN_CURSOR_RIGHT)
        {
            if (i2_vid_eq_val >= ACFG_CUST_CLR_GAIN_OFFSET_MAX)
            {
                /* do nothing*/
            }
            else
            {
                i2_vid_eq_val = i2_vid_eq_val + 1;
            }
        }

        a_cfg_av_set(ui2_id, i2_vid_eq_val);

        a_cfg_av_update(ui2_id);

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
        MENU_CHK_FAIL(i4_ret);

        a_cfg_set_clr_temp_chg_status(i2_clr_temp,TRUE);

    }

    c_sprintf(s_buf, "%d",i2_vid_eq_val);
    c_uc_ps_to_w2s(s_buf, ws_buf, 31);

    i4_ret = c_wgl_do_cmd(t_color_tuner.aah_cb_tr[ui1_hlt_row][ui1_hlt_col],
                           WGL_CMD_BTN_SET_TEXT,
                           WGL_PACK (ws_buf),
                           WGL_PACK (c_uc_w2s_strlen (ws_buf)));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(s_buf, 0, sizeof(s_buf));
    if(i2_vid_eq_val >= 0)
    {
        c_sprintf(s_buf, "%d",i2_vid_eq_val);
    }
    else
    {
        c_sprintf(s_buf, "minus %d",ABS(i2_vid_eq_val));
    }

    c_uc_ps_to_w2s(s_buf, ws_buf, 31);

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,ws_buf);
    _color_tuner_tts_play();

    i4_ret = c_wgl_repaint(t_color_tuner.aah_cb_tr[ui1_hlt_row][ui1_hlt_col],
                           NULL,
                           TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pic_energy_change_sepcial_page_set_status(TRUE);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _color_tuner_page_proc_fct
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
 static INT32 _color_tuner_page_proc_fct(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    UINT32      ui4_keycode = (UINT32)pv_param1;
    INT32       i4_ret = MENUR_OK;
    GL_RECT_T   t_rect = {0};
    BOOL       b_btn_pushed = FALSE;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    UTF16_T w2s_str[256] = {0};

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                            WGL_CMD_BTN_GET_PUSHED,
                            WGL_PACK(&b_btn_pushed),
                            WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                if(b_btn_pushed == FALSE)
                {
                    if(t_color_tuner.ui1_hlt_row == ROW_HUE)
                    {
                        if(t_color_tuner.ui1_hlt_col <= COL_BLUE)
                        {
                            c_wgl_set_focus(t_color_tuner.ah_col[t_color_tuner.ui1_hlt_col],TRUE);
                            c_wgl_get_coords(t_color_tuner.h_col_hlt_mov_btn,WGL_COORDS_PARENT,&t_rect);
                            t_rect.i4_left  = RED_ON_OFF_HLT_MOVE_BTN_X + (RED_ON_OFF_HLT_MOVE_BTN_X_OFFSET +RED_ON_OFF_BTN_LINE)*t_color_tuner.ui1_hlt_col;
                            t_rect.i4_right  = t_rect.i4_left + RED_ON_OFF_HLT_MOVE_BTN_W;
                            c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn,WGL_SW_NORMAL);
                            c_wgl_move(t_color_tuner.h_col_hlt_mov_btn,&t_rect,TRUE);
                            c_wgl_repaint(t_color_tuner.h_cnt_frm,NULL,TRUE);

                            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, (APP_CFG_RECID_VID_RED+t_color_tuner.ui1_hlt_col));
                            a_cfg_av_get( ui2_id, &i2ROnOff);
                            c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(aui2_str_dims[t_color_tuner.ui1_hlt_col]));
                            c_uc_w2s_strcat(w2s_str, _TEXT("."));
                            if(i2ROnOff == 1)
                            {
                              c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_ON));
                            }
                            else
                            {
                              c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
                            }

                              c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                              c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
                              _color_tuner_tts_play();

                        }
                        else
                        {
                            c_wgl_set_focus(ah_bar,TRUE);
                            c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                            c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE));
                            _color_tuner_tts_play();
                        }
                        break;
                    }

                    if((t_color_tuner.ui1_hlt_row > ROW_HUE) &&(t_color_tuner.ui1_hlt_row <= ROW_BRIGHTNESS))
                    {
                        t_color_tuner.ui1_hlt_row--;
                        c_wgl_set_focus(t_color_tuner.aah_cb_tr[t_color_tuner.ui1_hlt_row][t_color_tuner.ui1_hlt_col],TRUE);
                        _color_tuner_page_curnt_unit_tts_play(t_color_tuner.ui1_hlt_row,t_color_tuner.ui1_hlt_col);
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }



            case BTN_CURSOR_DOWN:
                if(b_btn_pushed == FALSE)
                {
                    if((t_color_tuner.ui1_hlt_row >= ROW_HUE) &&(t_color_tuner.ui1_hlt_row <ROW_BRIGHTNESS))
                    {
                        t_color_tuner.ui1_hlt_row++;
                        c_wgl_set_focus(t_color_tuner.aah_cb_tr[t_color_tuner.ui1_hlt_row][t_color_tuner.ui1_hlt_col],TRUE);
                        _color_tuner_page_curnt_unit_tts_play(t_color_tuner.ui1_hlt_row,t_color_tuner.ui1_hlt_col);
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }

            case BTN_CURSOR_LEFT:

                if(b_btn_pushed == FALSE)
                {
                    if(t_color_tuner.ui1_hlt_row <= ROW_BRIGHTNESS)
                    {
                        t_color_tuner.ui1_hlt_col = (t_color_tuner.ui1_hlt_col + 6-1)%6;
                        c_wgl_set_focus(t_color_tuner.aah_cb_tr[t_color_tuner.ui1_hlt_row][t_color_tuner.ui1_hlt_col],TRUE);
                        _color_tuner_page_curnt_unit_tts_play(t_color_tuner.ui1_hlt_row,t_color_tuner.ui1_hlt_col);
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                     i4_ret =  _color_tuner_page_unit_proc_fct(pv_param1,
                                                              t_color_tuner.ui1_hlt_row,
                                                              t_color_tuner.ui1_hlt_col);
                     MENU_LOG_ON_FAIL(i4_ret);
                    #if DBG_LOG
                    DBG_INFO(("\n ======_color_tuner_page_unit_proc_fct====%d,%d\n",t_color_tuner.ui1_hlt_col,__LINE__));
                    #endif
                    break;
                }

            case BTN_CURSOR_RIGHT:
                if(b_btn_pushed == FALSE)
                {
                    if(t_color_tuner.ui1_hlt_row <= ROW_BRIGHTNESS)
                    {
                        t_color_tuner.ui1_hlt_col = (t_color_tuner.ui1_hlt_col + 1)%6;
                        c_wgl_set_focus(t_color_tuner.aah_cb_tr[t_color_tuner.ui1_hlt_row][t_color_tuner.ui1_hlt_col],TRUE);
                        _color_tuner_page_curnt_unit_tts_play(t_color_tuner.ui1_hlt_row,t_color_tuner.ui1_hlt_col);
                        break;
                    }
                    else
                    {
                        break;
                    }

                }
                else
                {
                     i4_ret =  _color_tuner_page_unit_proc_fct(pv_param1,
                                                              t_color_tuner.ui1_hlt_row,
                                                              t_color_tuner.ui1_hlt_col);
                     MENU_LOG_ON_FAIL(i4_ret);
                    #if DBG_LOG
                    DBG_INFO(("\n ======_color_tuner_page_unit_proc_fct====%d,%d\n",t_color_tuner.ui1_hlt_col,__LINE__));
                    #endif
                    break;
                }

            case BTN_RETURN:
                /* Let the menu show */
                i4_ret = c_wgl_do_cmd(h_widget,
                                        WGL_CMD_BTN_SET_PUSHED,
                                        WGL_PACK(FALSE),
                                        WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);

                c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
                c_wgl_repaint(h_base_fram,NULL,TRUE);
                menu_main_set_visibility(TRUE);
                menu_nav_back();

                /* trigger help tip */
               // i4_ret=menu_set_and_show_help_tip(MENU_TEXT(pt_page_tree_item->t_menuitem.ui2_msgid_desc));
                //MENU_LOG_ON_FAIL(i4_ret);
                break;
            case BTN_SELECT:
                break;
            default:
                break;
        }



    }
    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

}


static INT32 _create_on_off_btn(UINT8 ui1_index, BOOL b_on, HANDLE_T* ph_widget)
{
   INT32                   i4_ret = MENUR_OK;
   UINT32                  ui4_style;
   GL_RECT_T               t_rect;

    ui4_style = 0;
    c_memset(&t_rect, 0x0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                    (INT32)RED_ON_OFF_BTN_X + (RED_ON_OFF_BTN_MOV_OFFSET)* (ui1_index),
                    (INT32)RED_ON_OFF_BTN_Y,
                    (INT32)RED_ON_OFF_BTN_W,
                    (INT32)RED_ON_OFF_BTN_H);

    i4_ret = c_wgl_create_widget(t_color_tuner.h_cnt_frm,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)ui4_style,
                                NULL,
                                ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

   return MENUR_OK;
}


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
static INT32 _create_col_title(HANDLE_T  h_parent,
                               INT32       i4_index,
                               UTF16_T*    w2s_str,
                               HANDLE_T*   ph_widget,
                               GL_RECT_T* pt_rect)
{
    INT32           i4_ret;
    WGL_COLOR_INFO_T    t_clr_txt;
    WGL_FONT_INFO_T             t_fnt_info;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 _color_tuner_col_title_proc,
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
    t_clr_txt.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_txt.u_color_data.t_extend.t_enable = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_disable = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_highlight = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_push = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_push_unhighlight = t_g_menu_color_black;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
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
static INT32 _create_row_title(INT32       i4_index,
                               UTF16_T*    w2s_str,
                               HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_FONT_INFO_T t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_txt;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_COLOR_TUNER_ROW_X,
                     MENU_COLOR_TUNER_ROW_Y + (MENU_COLOR_TUNER_ROW_H +RED_ON_OFF_BTN_LINE) * i4_index,
                     MENU_COLOR_TUNER_ROW_W,
                     MENU_COLOR_TUNER_ROW_H);

    i4_ret = c_wgl_create_widget(t_color_tuner.h_cnt_frm,
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
    t_clr_txt.u_color_data.t_standard.t_enable       =t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_standard.t_disable      =t_g_menu_color_bk0_txt_hlt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}



/*----------------------------------------------------------------------------
 * Name: _create_unit
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
static INT32 _create_unit(INT32       i4_x,
                        INT32       i4_y,
                        HANDLE_T*   ph_widget)
{

    WGL_IMG_INFO_T              t_img_info;
    INT32                       i4_ret = MENUR_OK;
    GL_RECT_T                   t_rect;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                 MENU_COLOR_TUNER_UNIT_X + (MENU_COLOR_TUNER_COL_W+RED_ON_OFF_BTN_LINE)*i4_y,
                 MENU_COLOR_TUNER_UNIT_Y + (MENU_COLOR_TUNER_ROW_H+RED_ON_OFF_BTN_LINE)*i4_x,
                 MENU_COLOR_TUNER_UNIT_W,
                 MENU_COLOR_TUNER_UNIT_H);

    i4_ret = c_wgl_create_widget(t_color_tuner.h_cnt_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _color_tuner_page_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_BTN_CHECKBOX),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set txt colors */
    t_lb_color.t_normal = t_g_menu_color_bk0_txt_hlt;
    t_lb_color.t_disable = t_g_menu_color_bk0_txt_hlt;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_white;

    c_wgl_do_cmd(*ph_widget,
                    WGL_CMD_GL_SET_COLOR,
                    WGL_PACK(WGL_CLR_TEXT),
                    WGL_PACK(&t_lb_color));

    /* Set align */

    c_wgl_do_cmd(*ph_widget,
                    WGL_CMD_BTN_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL);

    c_memset(&t_inset, 0, sizeof(t_inset));

    /*content inset*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                               WGL_CMD_BTN_SET_CNT_INSET,
                               WGL_PACK(&t_inset),
                               NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                                WGL_CMD_GL_SET_FONT,
                                (VOID*)(&t_fnt_info),
                                NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* background image */
    t_img_info.e_type                                             = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable               = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_enable                = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight            = h_g_menu_ColorTuner_digit_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_ColorTuner_digit_hlt;
    t_img_info.u_img_data.t_extend.t_push                   = h_g_menu_ColorTuner_digit_hlt_arrows;
    t_img_info.u_img_data.t_extend.t_push_unhighlight    = h_g_menu_ColorTuner_digit_hlt_arrows;

    i4_ret =  c_wgl_do_cmd(*ph_widget,
                                 WGL_CMD_GL_SET_IMAGE,
                                 WGL_PACK(WGL_IMG_BK),
                                 WGL_PACK(&t_img_info));
    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _color_tuner_page_create
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
static INT32 _color_tuner_page_create(VOID)
{
    INT32   i4_ret;
    GL_RECT_T   t_rect = {0};
    INT8        i1_index = 0;
    WGL_IMG_INFO_T   t_img_info;
    UINT32                 ui4_style = 0;

    menu_range_chg_lang(ah_bar, MLM_MENU_KEY_COLOR_TUNER_TITLE);

    i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE))));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                 0,
                 MENU_COLOR_TUNER_GRID_Y,
                 MENU_COLOR_TUNER_FRAME_W,
                 MENU_COLOR_TUNER_GRID_H);

    i4_ret = c_wgl_create_widget(h_base_fram,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &t_color_tuner.h_cnt_frm);

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set cnt  background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_g_menu_ColorTuner_grid;
    t_img_info.u_img_data.t_standard.t_highlight    = h_g_menu_ColorTuner_grid;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_menu_ColorTuner_grid;

    i4_ret = c_wgl_do_cmd(t_color_tuner.h_cnt_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /*create on/off button*/
    i4_ret = _create_on_off_btn(COL_RED,TRUE,&t_color_tuner.h_on_off_btn[COL_RED]);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_on_off_btn(COL_GREEN,FALSE,&t_color_tuner.h_on_off_btn[COL_GREEN]);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_on_off_btn(COL_BLUE,TRUE,&t_color_tuner.h_on_off_btn[COL_BLUE]);
    MENU_CHK_FAIL(i4_ret);

    /*create col */
    for(i1_index =COL_RED; i1_index <= COL_YELLOW; i1_index++)
    {

        SET_RECT_BY_SIZE(&t_rect,
                         MENU_COLOR_TUNER_COL_X + (MENU_COLOR_TUNER_COL_W + RED_ON_OFF_BTN_LINE)* (i1_index),
                         MENU_COLOR_TUNER_COL_Y,
                         MENU_COLOR_TUNER_COL_W,
                         MENU_COLOR_TUNER_COL_H);


        i4_ret = _create_col_title(t_color_tuner.h_cnt_frm,
                                          i1_index,
                                          MENU_TEXT(aui2_str_dims[i1_index]),
                                          &t_color_tuner.ah_col[i1_index],
                                          &t_rect);
        MENU_CHK_FAIL(i4_ret);
    }


    i4_ret = _create_row_title(0, MENU_TEXT(aui2_str_ages[0]), &t_color_tuner.ah_txt_row[0]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(1, MENU_TEXT(aui2_str_ages[1]), &t_color_tuner.ah_txt_row[1]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(2, MENU_TEXT(aui2_str_ages[2]), &t_color_tuner.ah_txt_row[2]);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_unit(0,0,&H_HUE_RED);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(1,0,&H_SATU_RED);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(2,0,&H_BRIGHT_RED);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_unit(0,1,&H_HUE_GREEN);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(1,1,&H_SATU_GREEN);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(2,1,&H_BRIGHT_GREEN);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_unit(0,2,&H_HUE_BLUE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(1,2,&H_SATU_BLUE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(2,2,&H_BRIGHT_BLUE);
    MENU_CHK_FAIL(i4_ret);


    i4_ret = _create_unit(0,3,&H_HUE_CYAN);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(1,3,&H_SATU_CYAN);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(2,3,&H_BRIGHT_CYAN);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_unit(0,4,&H_HUE_MAGENTA);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(1,4,&H_SATU_MAGENTA);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(2,4,&H_BRIGHT_MAGENTA);

    i4_ret = _create_unit(0,5,&H_HUE_YELLOW);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(1,5,&H_SATU_YELLOW);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_unit(2,5,&H_BRIGHT_YELLOW);
    MENU_CHK_FAIL(i4_ret);


    /*create hlt move btn*/

    SET_RECT_BY_SIZE(&t_rect,
                   (INT32)RED_ON_OFF_HLT_MOVE_BTN_X,
                   (INT32)RED_ON_OFF_HLT_MOVE_BTN_Y,
                   (INT32)RED_ON_OFF_HLT_MOVE_BTN_W,
                   (INT32)RED_ON_OFF_HLT_MOVE_BTN_H);

    i4_ret = c_wgl_create_widget(t_color_tuner.h_cnt_frm,
                              HT_WGL_WIDGET_BUTTON,
                              WGL_CONTENT_BUTTON_DEF,
                              WGL_BORDER_NULL,
                              &t_rect,
                              NULL,
                              255,
                              (VOID*)ui4_style,
                              NULL,
                              &t_color_tuner.h_col_hlt_mov_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_COLOR_SET_BASIC;
    t_img_info.u_img_data.t_basic.t_disable     = h_g_menu_ColorTuner_digit_hlt;
    t_img_info.u_img_data.t_basic.t_enable      = h_g_menu_ColorTuner_digit_hlt;

    i4_ret = c_wgl_do_cmd(t_color_tuner.h_col_hlt_mov_btn,
                       WGL_CMD_GL_SET_IMAGE,
                       WGL_PACK(WGL_IMG_BK),
                       WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(t_color_tuner.h_col_hlt_mov_btn,
                           WGL_CMD_BTN_SET_ALIGN,
                           WGL_PACK(WGL_AS_CENTER_CENTER),
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_wgl_insert(t_color_tuner.h_col_hlt_mov_btn,
                              NULL_HANDLE,
                              WGL_INSERT_BOTTOMMOST,
                              FALSE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}





#ifdef NEVER
/**********************************SMPTE Test Pattern Page************************************************************************/
static INT32 _smpte_test_pattern_reset(VOID)
{
    INT32       i4_ret = MENUR_OK;

    if (0 != t_smpte_test_pattern.ui2_val)
    {
        t_smpte_test_pattern.ui2_val = 0;
        _smpte_test_pattern_set_value_by_id(t_smpte_test_pattern.ui2_val);
    }

    /* get values from acfg */
    _smpte_test_pattern_update_txt(FALSE);

    return i4_ret;
}
#endif /* NEVER */

static UINT32 ui4_g_last_time = 0;

static BOOL _set_delay_show_test_pattern(VOID)
{
    UINT32 ui4_currt_time = c_os_get_sys_tick()* c_os_get_sys_tick_period();
    if(ui4_currt_time - ui4_g_last_time >= 1000)
    {
        ui4_g_last_time = ui4_currt_time;
        return FALSE;
    }
    return TRUE;
}

static INT32 _test_pattern_set_value_by_id(UINT8 ui1_type,UINT16 ui2_val)
{
    DBG_LOG_PRINT(("[MENU][TEST_PATTERN]{%s,%d} ui1_type: %d, ui2_val:%d, \r\n", __FUNCTION__,__LINE__, ui1_type, ui2_val ));

    if(ui2_val != 0)
    {
        banner_view_set_b_ctrl_show_flag(FALSE);
        switch (ui1_type)
        {
            case PAGE_SMPTE_TEST_PATTERN:
               {
                   t_ramp_test_pattern.ui2_val = 0;
                   t_uniformity_analyzer_test_pattern.ui2_val = 0;
                   t_flast_test_pattern.ui2_val = 0;
                   t_factory_test_pattern.ui2_val = 0;

                   _menu_show_test_pattern(SMPTE_TEST_PATTERN_ONOFF);
                   break;
               }
            case PAGE_RAMP_TEST_PATTERN:
               {
                   t_smpte_test_pattern.ui2_val = 0;
                   t_uniformity_analyzer_test_pattern.ui2_val = 0;
                   t_flast_test_pattern.ui2_val = 0;
                   t_factory_test_pattern.ui2_val = 0;

                   _menu_show_test_pattern((COLOR_CALIBRA_TEST_PATTERN_T)(FLAT_TEST_PATTERN_100+ui2_val));
                   break;
               }
            case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
               {
                   t_smpte_test_pattern.ui2_val = 0;
                   t_ramp_test_pattern.ui2_val = 0;
                   t_flast_test_pattern.ui2_val = 0;
                   t_factory_test_pattern.ui2_val = 0;

                   _menu_show_test_pattern(UNIFORMITY_TEST_PATTERN);
                   break;
               }

            case PAGE_FLAT_TEST_PATTERN:
               {
                   t_ramp_test_pattern.ui2_val = 0;
                   t_uniformity_analyzer_test_pattern.ui2_val = 0;
                   t_smpte_test_pattern.ui2_val = 0;
                   t_factory_test_pattern.ui2_val = 0;

                   _menu_show_test_pattern((COLOR_CALIBRA_TEST_PATTERN_T)(SMPTE_TEST_PATTERN_ONOFF+ui2_val));
                   break;
               }
            case PAGE_FACTORY_TEST_PATTERN:
               {
                   t_ramp_test_pattern.ui2_val = 0;
                   t_uniformity_analyzer_test_pattern.ui2_val = 0;
                   t_smpte_test_pattern.ui2_val = 0;
                   t_flast_test_pattern.ui2_val = 0;

                   _menu_show_test_pattern((COLOR_CALIBRA_TEST_PATTERN_T)(ui2_val));
                   break;
               }
            default:

           break;
        }
    }
    else
    {
        banner_view_set_b_ctrl_show_flag(TRUE);

        _menu_test_pattern_stop();
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_DISABLE);

        // Fix DTV03035130: menu auto exit when switch page "color tuner -> SMPTE test"
        if( _menu_page_color_tuner_IsCurSrcSupportTestPattern()
          //&&_test_pattern_enable()
          )
        {
            _color_tuner_rollback_svc();
        }
    }

    return MENUR_OK;

}

static INT32 _smpte_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN]{%s,%d} ui2_val:%d, \r\n", __FUNCTION__,__LINE__, ui2_val )); );

    if ((0 != ui2_val) &&
        ((0 != t_ramp_test_pattern.ui2_val)  ||
         (0 != t_flast_test_pattern.ui2_val)||
         (0 != t_uniformity_analyzer_test_pattern.ui2_val)||
         (0 != t_factory_test_pattern.ui2_val)))
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
    }

    _test_pattern_set_value_by_id(PAGE_SMPTE_TEST_PATTERN,ui2_val);
    t_smpte_test_pattern.ui2_val = ui2_val;

    return MENUR_OK;
}

INT32 menu_smpte_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    return _smpte_test_pattern_set_value_by_id(ui2_val);
}

static INT32 _smpte_test_pattern_update_txt(BOOL b_repaint)
{
    INT32       i4_ret = MENUR_OK;
    UTF16_T     w2s_val[32] = {0};
    UINT16      aui2_smpte_patten[2] = {
                                        MLM_MENU_KEY_MENU_COMMON_OFF,
                                        MLM_MENU_KEY_MENU_COMMON_ON
                                      };
    /* set values to acfg */

    if (t_smpte_test_pattern.ui2_val > 1)
    {
        t_smpte_test_pattern.ui2_val = 1;
    }

    c_uc_w2s_strcpy(w2s_val, MENU_TEXT(aui2_smpte_patten[t_smpte_test_pattern.ui2_val]));

    i4_ret = c_wgl_do_cmd(t_smpte_test_pattern.h_smpte_test_num_btn,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK (w2s_val),
                            WGL_PACK (c_uc_w2s_strlen (w2s_val)));
    MENU_LOG_ON_FAIL(i4_ret);

    _smpte_test_pattern_curnt_tts_play();

    if (b_repaint)
    {
        MENU_LOG_ON_FAIL(c_wgl_repaint(t_smpte_test_pattern.h_smpte_test_num_btn, NULL, TRUE));
    }

    return i4_ret;
}

INT32 menu_smpte_test_pattern_update_txt(BOOL b_repaint)
{
    return _smpte_test_pattern_update_txt(b_repaint);
}

static INT32 _smpte_test_pattern_curnt_tts_play(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UTF16_T     w2s_str[32] = {0};

    if(t_smpte_test_pattern.ui2_val == 0)
    {
        c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_ON));
    }

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
    _color_tuner_tts_play();

    return i4_ret;
}

static INT32 _smpte_test_pattern_proc_fct(
                            HANDLE_T    h_widget,
                            UINT32      ui4_msg,
                            VOID*       pv_param1,
                            VOID*       pv_param2)
{
    UINT32      ui4_keycode = (UINT32)pv_param1;
    UINT16      ui2_new_val = t_smpte_test_pattern.ui2_val;

    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        _test_pattern_left_right_arrow_show(TRUE);
    }
    else if (ui4_msg == WGL_MSG_LOSE_FOCUS)
    {
        _test_pattern_left_right_arrow_show(FALSE);
    }

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                c_wgl_set_focus(ah_bar,TRUE);
                c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_SMPTE_TEST_PATTERN));
                _color_tuner_tts_play();
                break;
            case BTN_CURSOR_DOWN:
                break;
            case BTN_CURSOR_LEFT:
                ui2_new_val = ui2_new_val == 0 ? 1 : 0;
                if(ui2_new_val != t_smpte_test_pattern.ui2_val)
                {
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                    _smpte_test_pattern_set_value_by_id(ui2_new_val);
                    t_smpte_test_pattern.ui2_val = ui2_new_val;
                    _smpte_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_smpte_test_pattern.h_smpte_test_cnt_frm, NULL, TRUE);
                }
                break;
            case BTN_CURSOR_RIGHT:
                ui2_new_val = ui2_new_val == 1 ? 0 : 1;
                if(ui2_new_val != t_smpte_test_pattern.ui2_val)
                {
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                    _smpte_test_pattern_set_value_by_id(ui2_new_val);
                    t_smpte_test_pattern.ui2_val = ui2_new_val;
                    _smpte_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_smpte_test_pattern.h_smpte_test_cnt_frm, NULL, TRUE);
                }
                break;
            case BTN_RETURN:
                /* Not turn off flat test pattern */
                //_flat_test_pattern_get_value();

                /* Let the menu show */
                c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
                c_wgl_repaint(h_base_fram,NULL,TRUE);
                menu_main_set_visibility(TRUE);
                menu_nav_back();
                break;
            default:
                break;
        }
    }

    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _ramp_test_pattern_page_create
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
static INT32 _smpte_test_pattern_page_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_COLOR_INFO_T            t_clr_txt = {0};
    WGL_FONT_INFO_T             t_fnt_info = {0};

    menu_range_chg_lang(ah_bar, MLM_MENU_KEY_SMPTE_TEST_PATTERN);

     SET_RECT_BY_SIZE(&t_rect,
              0,
              MENU_COLOR_TUNER_GRID_Y,
              MENU_COLOR_TUNER_FRAME_W,
              MENU_COLOR_TUNER_GRID_H);

     i4_ret = c_wgl_create_widget(h_base_fram,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)0,
                                  NULL,
                                  &t_smpte_test_pattern.h_smpte_test_cnt_frm);

     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     SET_RECT_BY_SIZE(&t_rect,
                 MENU_FLAT_TEST_PATTERN_BTN_X,
                 MENU_FLAT_TEST_PATTERN_BTN_Y,
                 MENU_FLAT_TEST_PATTERN_BTN_W,
                 MENU_FLAT_TEST_PATTERN_BTN_H);

     i4_ret = c_wgl_create_widget(t_smpte_test_pattern.h_smpte_test_cnt_frm,
                             HT_WGL_WIDGET_BUTTON,
                             WGL_CONTENT_BUTTON_DEF,
                             WGL_BORDER_NULL,
                             &t_rect,
                             _smpte_test_pattern_proc_fct,
                             255,
                             (VOID*)0,
                             NULL,
                             &t_smpte_test_pattern.h_smpte_test_num_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set BTN colors */
    t_clr_txt.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_txt.u_color_data.t_extend.t_enable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_disable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_highlight = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push_unhighlight = t_g_menu_color_white;

    c_wgl_do_cmd(t_smpte_test_pattern.h_smpte_test_num_btn,
                    WGL_CMD_GL_SET_COLOR,
                    WGL_PACK(WGL_CLR_TEXT),
                    WGL_PACK(&t_clr_txt));

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_smpte_test_pattern.h_smpte_test_num_btn,
                                WGL_CMD_GL_SET_FONT,
                                (VOID*)(&t_fnt_info),
                                NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set align */
    c_wgl_do_cmd(t_smpte_test_pattern.h_smpte_test_num_btn,
                    WGL_CMD_BTN_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL);

    /* background image */
    t_img_info.e_type                                       = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable                = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_enable                 = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_highlight              = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive     = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push                   = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight       = h_g_menu_img_item_hlt_bk;

    i4_ret =  c_wgl_do_cmd(t_smpte_test_pattern.h_smpte_test_num_btn,
                                 WGL_CMD_GL_SET_IMAGE,
                                 WGL_PACK(WGL_IMG_BK),
                                 WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
#ifdef NEVER

/**********************************Flat Test Pattern Page************************************************************************/
static INT32 _flat_test_pattern_reset(VOID)
{
    INT32       i4_ret = MENUR_OK;

    if (0 != t_flast_test_pattern.ui2_val)
    {
        t_flast_test_pattern.ui2_val = 0;
        _flat_test_pattern_set_value_by_id(t_flast_test_pattern.ui2_val);

        _flat_test_pattern_update_txt(FALSE);
    }
    else
    {
        return i4_ret;
    }

    return i4_ret;
}
#endif /* NEVER */

static INT32 _flat_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN]{%s,%d} ui2_val:%d, \r\n", __FUNCTION__,__LINE__, ui2_val )); );

    if ((0 != ui2_val) &&
        ((0 != t_smpte_test_pattern.ui2_val)  ||
         (0 != t_ramp_test_pattern.ui2_val)||
         (0 != t_uniformity_analyzer_test_pattern.ui2_val)||
         (0 != t_factory_test_pattern.ui2_val)))
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
    }

    _test_pattern_set_value_by_id(PAGE_FLAT_TEST_PATTERN,ui2_val);
    t_flast_test_pattern.ui2_val = ui2_val;

    return MENUR_OK;
}

static INT32 _flat_test_pattern_update_txt(BOOL b_repaint)
{
    INT32       i4_ret = MENUR_OK;
    CHAR        ac_val[32] = {0};
    UTF16_T     w2s_val[32] = {0};

    /* set values to acfg */

    if (t_flast_test_pattern.ui2_val == 0)
    {
        c_uc_w2s_strcpy(w2s_val, MENU_TEXT(MLM_MENU_KEY_OFF));
    }
    else
    {
        snprintf(ac_val, 7, "%d", t_flast_test_pattern.ui2_val*10);
        c_uc_ps_to_w2s(ac_val, w2s_val, 7);
        c_uc_w2s_strcat(w2s_val, L"%");
    }

    i4_ret = c_wgl_do_cmd(t_flast_test_pattern.h_flat_test_num_btn,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK (w2s_val),
                            WGL_PACK (c_uc_w2s_strlen (w2s_val)));
    MENU_LOG_ON_FAIL(i4_ret);

    _flat_test_pattern_curnt_tts_play();

    if (b_repaint)
    {
        MENU_LOG_ON_FAIL(c_wgl_repaint(t_flast_test_pattern.h_flat_test_num_btn, NULL, TRUE));
    }

    return i4_ret;
}

static INT32 _flat_test_pattern_curnt_tts_play(VOID)
{
    INT32       i4_ret = MENUR_OK;
    CHAR        ac_val[32] = {0};
    UTF16_T     w2s_val[32] = {0};

    if (t_flast_test_pattern.ui2_val == 0)
    {
        c_uc_w2s_strcpy(w2s_val, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
    }
    else
    {
        snprintf(ac_val, 7, "%d", t_flast_test_pattern.ui2_val*10);
        c_uc_ps_to_w2s(ac_val, w2s_val, 7);
        c_uc_w2s_strcat(w2s_val, L"%");
    }

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,w2s_val);
    _color_tuner_tts_play();

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _flat_test_pattern_page_proc_fct
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
static INT32 _flat_test_pattern_page_proc_fct(HANDLE_T    h_widget,
                                               UINT32      ui4_msg,
                                               VOID*       pv_param1,
                                               VOID*       pv_param2)
{
    UINT32      ui4_keycode = (UINT32)pv_param1;
    UINT16      ui2_new_val = t_flast_test_pattern.ui2_val;

    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        _test_pattern_left_right_arrow_show(TRUE);
    }
    else if (ui4_msg == WGL_MSG_LOSE_FOCUS)
    {
        _test_pattern_left_right_arrow_show(FALSE);
    }

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                c_wgl_set_focus(ah_bar,TRUE);
                c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_FLAT_TEST_PATTERN));
                _color_tuner_tts_play();
                break;
            case BTN_CURSOR_DOWN:
                break;
            case BTN_CURSOR_LEFT:
                ui2_new_val = ui2_new_val == 0 ? 10 : ui2_new_val - 1;
                if(ui2_new_val != t_flast_test_pattern.ui2_val)
                {
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                    _flat_test_pattern_set_value_by_id(ui2_new_val);
                    t_flast_test_pattern.ui2_val = ui2_new_val;
                    _flat_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_flast_test_pattern.h_flat_test_cnt_frm, NULL, TRUE);
                }
                break;
            case BTN_CURSOR_RIGHT:
                ui2_new_val = ui2_new_val == 10 ? 0 : ui2_new_val + 1;
                if(ui2_new_val != t_flast_test_pattern.ui2_val)
                {
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                    _flat_test_pattern_set_value_by_id(ui2_new_val);
                    t_flast_test_pattern.ui2_val = ui2_new_val;
                    _flat_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_flast_test_pattern.h_flat_test_cnt_frm, NULL, TRUE);
                }
                break;
            case BTN_RETURN:
                /* Not turn off flat test pattern */
                //_flat_test_pattern_get_value();

                /* Let the menu show */
                c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
                c_wgl_repaint(h_base_fram,NULL,TRUE);
                menu_main_set_visibility(TRUE);
                menu_nav_back();

                break;
            default:
                break;
        }

        //DTV019978985 ++++++++++++++++
        //Flat test pattern set on don't need show cc info
        if(ui4_keycode == BTN_CURSOR_LEFT || ui4_keycode == BTN_CURSOR_RIGHT)
        {
            NAV_CI_EXEC_COND_T e_cond = NAV_CI_EC_OFF;
            nav_ci_get_exec_cond(&e_cond);
            //DBG_LOG_PRINT(("[cccccccccccccccccccc ] nav_ci_get_exec_cond ret:%d ui2_new_val:%d\r\n",e_cond,ui2_new_val));
            if(e_cond == NAV_CI_EC_ON)
            {
                nav_ci_set_visible((ui2_new_val == 0)?TRUE:FALSE);
            }
        }

    }

    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _flat_test_pattern_page_create
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
static INT32 _flat_test_pattern_page_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect = {0};
    WGL_COLOR_INFO_T            t_clr_txt = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T             t_fnt_info = {0};

    menu_range_chg_lang(ah_bar, MLM_MENU_KEY_FLAT_TEST_PATTERN);

     SET_RECT_BY_SIZE(&t_rect,
              0,
              MENU_COLOR_TUNER_GRID_Y,
              MENU_COLOR_TUNER_FRAME_W,
              MENU_COLOR_TUNER_GRID_H);

     i4_ret = c_wgl_create_widget(h_base_fram,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)0,
                                  NULL,
                                  &t_flast_test_pattern.h_flat_test_cnt_frm);

     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     SET_RECT_BY_SIZE(&t_rect,
                 MENU_FLAT_TEST_PATTERN_BTN_X,
                 MENU_FLAT_TEST_PATTERN_BTN_Y,
                 MENU_FLAT_TEST_PATTERN_BTN_W,
                 MENU_FLAT_TEST_PATTERN_BTN_H);

     i4_ret = c_wgl_create_widget(t_flast_test_pattern.h_flat_test_cnt_frm,
                             HT_WGL_WIDGET_BUTTON,
                             WGL_CONTENT_BUTTON_DEF,
                             WGL_BORDER_NULL,
                             &t_rect,
                             _flat_test_pattern_page_proc_fct,
                             255,
                             (VOID*)0,
                             NULL,
                             &t_flast_test_pattern.h_flat_test_num_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set BTN colors */
    t_clr_txt.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_txt.u_color_data.t_extend.t_enable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_disable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_highlight = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push_unhighlight = t_g_menu_color_white;

    c_wgl_do_cmd(t_flast_test_pattern.h_flat_test_num_btn,
                    WGL_CMD_GL_SET_COLOR,
                    WGL_PACK(WGL_CLR_TEXT),
                    WGL_PACK(&t_clr_txt));

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_flast_test_pattern.h_flat_test_num_btn,
                                WGL_CMD_GL_SET_FONT,
                                (VOID*)(&t_fnt_info),
                                NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set align */
    c_wgl_do_cmd(t_flast_test_pattern.h_flat_test_num_btn,
                    WGL_CMD_BTN_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL);

    /* background image */
    t_img_info.e_type                                       = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable                = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_enable                 = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_highlight              = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive     = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push                   = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight       = h_g_menu_img_item_hlt_bk;

    i4_ret =  c_wgl_do_cmd(t_flast_test_pattern.h_flat_test_num_btn,
                                 WGL_CMD_GL_SET_IMAGE,
                                 WGL_PACK(WGL_IMG_BK),
                                 WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

#ifdef NEVER
/**********************************ramp Test Pattern Page************************************************************************/
static INT32 _ramp_test_pattern_reset(VOID)
{
    INT32       i4_ret = MENUR_OK;

    if (0 != t_ramp_test_pattern.ui2_val)
    {
        _ramp_test_pattern_set_value_by_id(0);
    }

    /* get values from acfg */
    _ramp_test_pattern_update_txt(FALSE);

    return i4_ret;
}
#endif /* NEVER */

////////////////////////////////////////////////////////////////////////////////////////

static INT32 _ramp_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN]{%s,%d} ui2_val:%d, \r\n", __FUNCTION__,__LINE__, ui2_val )); );

    if ((0 != ui2_val) &&
        ((0 != t_smpte_test_pattern.ui2_val)  ||
         (0 != t_flast_test_pattern.ui2_val)||
         (0 != t_uniformity_analyzer_test_pattern.ui2_val)||
         (0 != t_factory_test_pattern.ui2_val)))
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
    }

    _test_pattern_set_value_by_id(PAGE_RAMP_TEST_PATTERN,ui2_val);
    t_ramp_test_pattern.ui2_val = ui2_val;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ramp_test_pattern_is_on
 *
 * Description: return ramp test pattern is on/off.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
BOOL a_ramp_test_pattern_is_on(VOID)
{

    if (t_ramp_test_pattern.ui2_val != 0)
    {
        return TRUE;
    }
    else
    {

        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: color_tuner_get_rgb_cfg_value
 *
 * Description: in order to recover the RGB cfg value,
 *          get the RGB cfg value when the page first show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 color_tuner_get_rgb_cfg_value(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16       i2_clr_temp = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    i4_ret = a_cfg_av_get( ui2_id, &i2_user_RGB_setting[i2_clr_temp][MENU_R_USER_SETTING]);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
    i4_ret = a_cfg_av_get( ui2_id, &i2_user_RGB_setting[i2_clr_temp][MENU_G_USER_SETTING]);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
    i4_ret = a_cfg_av_get( ui2_id, &i2_user_RGB_setting[i2_clr_temp][MENU_B_USER_SETTING]);
    MENU_LOG_ON_FAIL(i4_ret);

    /*for debug*/
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3;j++)
        {
            DBG_INFO(("\n####%s(%d)i2_user_RGB_setting[%d][%d]=%d,\n",__FUNCTION__,__LINE__,i,j,i2_user_RGB_setting[i][j]));
        }
    }
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _color_tuner_get_rgb_cfg_value_with_id(UINT16 ui2_id)
 *
 * Description: in order to recover the RGB cfg value,
 *          get the RGB cfg value when the user change the RGB setting in the color tuner page.
 *          only update the R/G/B cfg value which is  user adjusted.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _color_tuner_get_rgb_cfg_value_with_id(UINT16 ui2_id)
{
    INT32       i4_ret = MENUR_OK;
    INT16       i2_clr_temp = 0;

    if (t_ramp_test_pattern.ui2_val != 0)
    {
        color_tuner_get_rgb_cfg_value();
    }
    else
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
        MENU_LOG_ON_FAIL(i4_ret);

        if(ui2_id == CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED))
        {
            i4_ret = a_cfg_av_get( ui2_id, &i2_user_RGB_setting[i2_clr_temp][MENU_R_USER_SETTING]);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else if(ui2_id == CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN))
        {
            i4_ret = a_cfg_av_get( ui2_id, &i2_user_RGB_setting[i2_clr_temp][MENU_G_USER_SETTING]);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else if(ui2_id == CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE))
        {
            i4_ret = a_cfg_av_get( ui2_id, &i2_user_RGB_setting[i2_clr_temp][MENU_B_USER_SETTING]);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /*for debug*/
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3;j++)
        {
            DBG_INFO(("\n####%s(%d)i2_user_RGB_setting[%d][%d]=%d,\n",__FUNCTION__,__LINE__,i,j,i2_user_RGB_setting[i][j]));
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_color_tuner_recover_rgb_cfg_value
 *
 * Description:rampt test pattern options(RGB)will influence the color tuner page RGB options;
 *          but, expect to recover the RGB cfg value(before influence) when turn off ramp test pattern.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_color_tuner_recover_rgb_cfg_value(VOID)
{
    UINT16      ui2_id = 0;
    INT32       i4_ret = MENUR_OK;
    INT16       i2_clr_temp = 0;

    /*for debug*/
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3;j++)
        {
            DBG_INFO(("\n####%s(%d)i2_user_RGB_setting[%d][%d]=%d,\n",__FUNCTION__,__LINE__,i,j,i2_user_RGB_setting[i][j]));
        }
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    i4_ret = a_cfg_av_set( ui2_id, i2_user_RGB_setting[i2_clr_temp][MENU_R_USER_SETTING]);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN);
    i4_ret = a_cfg_av_set( ui2_id, i2_user_RGB_setting[i2_clr_temp][MENU_G_USER_SETTING]);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE);
    i4_ret = a_cfg_av_set( ui2_id, i2_user_RGB_setting[i2_clr_temp][MENU_B_USER_SETTING]);

    return MENUR_OK;
}

static INT32 _ramp_test_pattern_update_txt(BOOL b_repaint)
{
    INT32       i4_ret = MENUR_OK;
    UTF16_T     w2s_val[32] = {0};
    UINT16      aui2_ramp_patten[5] = {
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_OFF,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_WHITE,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_RED,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_GREEN,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_BLUE,
                                      };

    /* set values to acfg */

    c_uc_w2s_strcpy(w2s_val, MENU_TEXT(aui2_ramp_patten[t_ramp_test_pattern.ui2_val]));

    i4_ret = c_wgl_do_cmd(t_ramp_test_pattern.h_ramp_test_color_btn,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK (w2s_val),
                            WGL_PACK (c_uc_w2s_strlen (w2s_val)));
    MENU_LOG_ON_FAIL(i4_ret);

    _ramp_test_pattern_curnt_tts_play();

    if (b_repaint)
    {
        MENU_LOG_ON_FAIL(c_wgl_repaint(t_ramp_test_pattern.h_ramp_test_color_btn, NULL, TRUE));
    }

    return i4_ret;
}

static INT32 _ramp_test_pattern_curnt_tts_play(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UTF16_T     w2s_val[32] = {0};
    UINT16      aui2_ramp_patten[5] = {
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_OFF,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_WHITE,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_RED,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_GREEN,
                                        MLM_MENU_KEY_RAMP_TEST_PATTERN_BLUE,
                                      };

    c_uc_w2s_strcpy(w2s_val, MENU_TTS_TEXT(aui2_ramp_patten[t_ramp_test_pattern.ui2_val]));

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,w2s_val);
    _color_tuner_tts_play();

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _ramp_test_pattern_page_create
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
static INT32 _ramp_test_pattern_proc_fct(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    UINT32      ui4_keycode = (UINT32)pv_param1;
    UINT16      ui2_new_val = t_ramp_test_pattern.ui2_val;

    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        _test_pattern_left_right_arrow_show(TRUE);
    }
    else if (ui4_msg == WGL_MSG_LOSE_FOCUS)
    {
        _test_pattern_left_right_arrow_show(FALSE);
    }

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                c_wgl_set_focus(ah_bar,TRUE);
                c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_RAMP_TEST_PATTERN_TITLE));
                _color_tuner_tts_play();
                break;
            case BTN_CURSOR_DOWN:
                break;
            case BTN_CURSOR_LEFT:
                ui2_new_val = ui2_new_val == 0 ? 4 : ui2_new_val - 1;
                if(ui2_new_val != t_ramp_test_pattern.ui2_val)
                {
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                    _ramp_test_pattern_set_value_by_id(ui2_new_val);
                    t_ramp_test_pattern.ui2_val = ui2_new_val;
                    _ramp_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_ramp_test_pattern.h_ramp_test_color_btn, NULL, TRUE);
                }
                break;
            case BTN_CURSOR_RIGHT:
                ui2_new_val = ui2_new_val == 4 ? 0 : ui2_new_val + 1;
                if(ui2_new_val != t_ramp_test_pattern.ui2_val)
                {
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                    _ramp_test_pattern_set_value_by_id(ui2_new_val);
                    t_ramp_test_pattern.ui2_val = ui2_new_val;
                    _ramp_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_ramp_test_pattern.h_ramp_test_color_btn, NULL, TRUE);
                }
                break;
            case BTN_RETURN:
                /* Not turn off ramp test pattern */
                //_ramp_test_pattern_get_value();

                /* Let the menu show */
                c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
                c_wgl_repaint(h_base_fram,NULL,TRUE);
                menu_main_set_visibility(TRUE);
                menu_nav_back();
                break;
            default:
                break;
        }
    }

    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _ramp_test_pattern_page_create
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
static INT32 _ramp_test_pattern_page_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_COLOR_INFO_T            t_clr_txt = {0};
    WGL_FONT_INFO_T             t_fnt_info = {0};

    menu_range_chg_lang(ah_bar, MLM_MENU_KEY_RAMP_TEST_PATTERN_TITLE);

     SET_RECT_BY_SIZE(&t_rect,
              0,
              MENU_COLOR_TUNER_GRID_Y,
              MENU_COLOR_TUNER_FRAME_W,
              MENU_COLOR_TUNER_GRID_H);

     i4_ret = c_wgl_create_widget(h_base_fram,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)0,
                                  NULL,
                                  &t_ramp_test_pattern.h_ramp_test_cnt_frm);

     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     SET_RECT_BY_SIZE(&t_rect,
                 MENU_FLAT_TEST_PATTERN_BTN_X,
                 MENU_FLAT_TEST_PATTERN_BTN_Y,
                 MENU_FLAT_TEST_PATTERN_BTN_W,
                 MENU_FLAT_TEST_PATTERN_BTN_H);

     i4_ret = c_wgl_create_widget(t_ramp_test_pattern.h_ramp_test_cnt_frm,
                             HT_WGL_WIDGET_BUTTON,
                             WGL_CONTENT_BUTTON_DEF,
                             WGL_BORDER_NULL,
                             &t_rect,
                             _ramp_test_pattern_proc_fct,
                             255,
                             (VOID*)0,
                             NULL,
                             &t_ramp_test_pattern.h_ramp_test_color_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set BTN colors */
    t_clr_txt.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_txt.u_color_data.t_extend.t_enable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_disable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_highlight = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push_unhighlight = t_g_menu_color_white;
    c_wgl_do_cmd(t_ramp_test_pattern.h_ramp_test_color_btn,
                    WGL_CMD_GL_SET_COLOR,
                    WGL_PACK(WGL_CLR_TEXT),
                    WGL_PACK(&t_clr_txt));

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_ramp_test_pattern.h_ramp_test_color_btn,
                                WGL_CMD_GL_SET_FONT,
                                (VOID*)(&t_fnt_info),
                                NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set align */
    c_wgl_do_cmd(t_ramp_test_pattern.h_ramp_test_color_btn,
                    WGL_CMD_BTN_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL);

    /* background image */
    t_img_info.e_type                                       = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable                = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_enable                 = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_highlight              = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive     = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push                   = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight       = h_g_menu_img_item_hlt_bk;

    i4_ret =  c_wgl_do_cmd(t_ramp_test_pattern.h_ramp_test_color_btn,
                                 WGL_CMD_GL_SET_IMAGE,
                                 WGL_PACK(WGL_IMG_BK),
                                 WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;

}

static INT32 _uniformity_analyzer_test_pattern_set_title_font_size(BOOL b_change)
{
    INT32               i4_ret = MENUR_OK;
    WGL_FONT_INFO_T     t_fnt_info = {0};

    ISO_639_LANG_T      s639_lang;
    UINT16              ui2_lang = 0;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != MENUR_OK)
    {
        ui2_lang = 0;
    }
    else
    {
        ui2_lang = mlm_menu_s639_to_langidx(s639_lang);
    }
     /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));

    if(b_change && (2 == ui2_lang)) /* SPA */
    {
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.ui1_custom_size = 23;
    }
    else
    {
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    }
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(ah_bar,
                                WGL_CMD_GL_SET_FONT,
                                (VOID*)(&t_fnt_info),
                                NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _uniformity_analyzer_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN]{%s,%d} ui2_val:%d, \r\n", __FUNCTION__,__LINE__, ui2_val )); );

    if ((0 != ui2_val) &&
        ((0 != t_smpte_test_pattern.ui2_val)  ||
         (0 != t_ramp_test_pattern.ui2_val)||
         (0 != t_flast_test_pattern.ui2_val)||
         (0 != t_factory_test_pattern.ui2_val)))
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
    }

    _test_pattern_set_value_by_id(PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN,ui2_val);
    t_uniformity_analyzer_test_pattern.ui2_val = ui2_val;

    return MENUR_OK;
}

INT32 menu_uniformity_analyzer_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    return _uniformity_analyzer_test_pattern_set_value_by_id(ui2_val);
}

static INT32 _uniformity_analyzer_test_pattern_curnt_tts_play(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UTF16_T     w2s_str[32] = {0};

    if (t_uniformity_analyzer_test_pattern.ui2_val == 0)
    {
        c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_ON));
    }

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
    _color_tuner_tts_play();

    return i4_ret;
}

static INT32 _uniformity_analyzer_test_pattern_update_txt(BOOL b_repaint)
{
    INT32       i4_ret = MENUR_OK;
    UTF16_T     w2s_val[32] = {0};

    UINT16      aui2_unif_patten[2] = {
                                        MLM_MENU_KEY_MENU_COMMON_OFF,
                                        MLM_MENU_KEY_MENU_COMMON_ON
                                      };
    /* set values to acfg */

    if (t_uniformity_analyzer_test_pattern.ui2_val > 1)
    {
        t_uniformity_analyzer_test_pattern.ui2_val = 1;
    }
    _uniformity_analyzer_test_pattern_set_title_font_size(TRUE);
    c_uc_w2s_strcpy(w2s_val, MENU_TEXT(aui2_unif_patten[t_uniformity_analyzer_test_pattern.ui2_val]));

    i4_ret = c_wgl_do_cmd(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK (w2s_val),
                            WGL_PACK (c_uc_w2s_strlen (w2s_val)));
    MENU_LOG_ON_FAIL(i4_ret);

    _uniformity_analyzer_test_pattern_curnt_tts_play();

    if (b_repaint)
    {
        MENU_LOG_ON_FAIL(c_wgl_repaint(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn, NULL, TRUE));
    }

    return i4_ret;
}

INT32 menu_uniformity_analyzer_test_pattern_update_txt(BOOL b_repaint)
{
    return _uniformity_analyzer_test_pattern_update_txt(b_repaint);
}

static INT32 _uniformity_analyzer_test_pattern_proc_fct(
                            HANDLE_T    h_widget,
                            UINT32      ui4_msg,
                            VOID*       pv_param1,
                            VOID*       pv_param2)
{
    UINT32      ui4_keycode = (UINT32)pv_param1;
    UINT16      ui2_new_val = t_uniformity_analyzer_test_pattern.ui2_val;

    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        _test_pattern_left_right_arrow_show(TRUE);
    }
    else if (ui4_msg == WGL_MSG_LOSE_FOCUS)
    {
        _test_pattern_left_right_arrow_show(FALSE);
    }

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                _uniformity_analyzer_test_pattern_set_title_font_size(FALSE);
                c_wgl_set_focus(ah_bar,TRUE);
                c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_UNIFANA_TEST_PATTERN));
                _color_tuner_tts_play();
                break;
            case BTN_CURSOR_DOWN:
                break;
            case BTN_CURSOR_LEFT:
                ui2_new_val = ui2_new_val == 0 ? 1 : 0;
                if(ui2_new_val != t_uniformity_analyzer_test_pattern.ui2_val)
                {
                    _uniformity_analyzer_test_pattern_set_title_font_size(TRUE);
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                     _test_pattern_warning_info_visiable(FALSE,TRUE);

                    _uniformity_analyzer_test_pattern_set_value_by_id(ui2_new_val);
                    t_uniformity_analyzer_test_pattern.ui2_val = ui2_new_val;
                    _uniformity_analyzer_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn, NULL, TRUE);
                }
                break;
            case BTN_CURSOR_RIGHT:
                ui2_new_val = ui2_new_val == 1 ? 0 : 1;
                if(ui2_new_val != t_uniformity_analyzer_test_pattern.ui2_val)
                {
                    _uniformity_analyzer_test_pattern_set_title_font_size(TRUE);
                    if(_set_delay_show_test_pattern())
                    {
                        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
                    }
                     _test_pattern_warning_info_visiable(FALSE,TRUE);

                    _uniformity_analyzer_test_pattern_set_value_by_id(ui2_new_val);
                    t_uniformity_analyzer_test_pattern.ui2_val = ui2_new_val;
                    _uniformity_analyzer_test_pattern_update_txt(FALSE);
                    c_wgl_repaint(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn, NULL, TRUE);
                }
                break;
            case BTN_RETURN:
                /* Not turn off flat test pattern */
                //_flat_test_pattern_get_value();

                /* Let the menu show */
                c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
                c_wgl_repaint(h_base_fram,NULL,TRUE);
                menu_main_set_visibility(TRUE);
                menu_nav_back();

                break;
            default:
                break;
        }
    }

    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _uniformity_analyzer_test_pattern_page_create
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
static INT32 _uniformity_analyzer_test_pattern_page_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_COLOR_INFO_T            t_clr_txt = {0};
    WGL_FONT_INFO_T             t_fnt_info = {0};

    menu_range_chg_lang(ah_bar, MLM_MENU_KEY_UNIFANA_TEST_PATTERN);

    SET_RECT_BY_SIZE(&t_rect,
              0,
              MENU_COLOR_TUNER_GRID_Y,
              MENU_COLOR_TUNER_FRAME_W,
              MENU_COLOR_TUNER_GRID_H);

    i4_ret = c_wgl_create_widget(h_base_fram,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)0,
                                  NULL,
                                  &t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm);

    if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     SET_RECT_BY_SIZE(&t_rect,
                 MENU_FLAT_TEST_PATTERN_BTN_X,
                 MENU_FLAT_TEST_PATTERN_BTN_Y,
                 MENU_FLAT_TEST_PATTERN_BTN_W,
                 MENU_FLAT_TEST_PATTERN_BTN_H);

     i4_ret = c_wgl_create_widget(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,
                             HT_WGL_WIDGET_BUTTON,
                             WGL_CONTENT_BUTTON_DEF,
                             WGL_BORDER_NULL,
                             &t_rect,
                             _uniformity_analyzer_test_pattern_proc_fct,
                             255,
                             (VOID*)0,
                             NULL,
                             &t_uniformity_analyzer_test_pattern.h_unif_test_num_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set BTN colors */
    t_clr_txt.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_txt.u_color_data.t_extend.t_enable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_disable = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_extend.t_highlight = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_highlight_inactive = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push = t_g_menu_color_white;
    t_clr_txt.u_color_data.t_extend.t_push_unhighlight = t_g_menu_color_white;

    c_wgl_do_cmd(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn,
                    WGL_CMD_GL_SET_COLOR,
                    WGL_PACK(WGL_CLR_TEXT),
                    WGL_PACK(&t_clr_txt));

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn,
                                WGL_CMD_GL_SET_FONT,
                                (VOID*)(&t_fnt_info),
                                NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set align */
    c_wgl_do_cmd(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn,
                    WGL_CMD_BTN_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL);

    /* background image */
    t_img_info.e_type                                       = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable                = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_enable                 = h_g_menu_img_item_bk;//h_g_menu_ColorTuner_digit_arrows;
    t_img_info.u_img_data.t_extend.t_highlight              = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive     = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push                   = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight       = h_g_menu_img_item_hlt_bk;

    i4_ret =  c_wgl_do_cmd(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn,
                                 WGL_CMD_GL_SET_IMAGE,
                                 WGL_PACK(WGL_IMG_BK),
                                 WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

#ifndef APP_CAST_TEST_PATTERN_FLAT
/**********************************Common Page************************************************************************/
static VOID _change_screen_mode(VOID)
{
        UINT8   ui1_val = 1;
        if (i2_scrn_mode == ACFG_TEST_PATTERN_SCRN_MODE_NONE)
        {
            CHAR                        s_disp_name[ACFG_MAX_DISP_NAME + 1];
            VSH_SRC_RESOLUTION_INFO_T   t_timing = {0};

            /* Get current timing */
            a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            a_cfg_av_get_timing(s_disp_name, &t_timing);
            if((1070<=t_timing.ui4_height && t_timing.ui4_height<=1090)
               || (710<=t_timing.ui4_height && t_timing.ui4_height<=730))
            {
                i2_scrn_mode = ACFG_TEST_PATTERN_SCRN_MODE_NORMAL;
            }
            else
            {
                i2_scrn_mode = ACFG_TEST_PATTERN_SCRN_MODE_WIDE;
            }

            /* Set aspect ratio as 16:9 */
            ui1_val = i2_scrn_mode;
            a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                     (VOID *) &ui1_val,
                     ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE);
        }
        else
        {
            if (i2_scrn_mode != 0)
            {
                i2_scrn_mode = 0;
                ui1_val = 0;
                a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_COLOR_TUNER, ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE),
                         (VOID *) &ui1_val,
                         ICL_RECID_CUSTOM_COLOR_TUNER_SCREEN_MODE_SIZE);
            }
        }

        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
}
#endif

static BOOL _color_tuner_is_test_pattern_page(UINT8 u8Page)
{
    switch(u8Page)
    {
        case PAGE_SMPTE_TEST_PATTERN:
        case PAGE_FLAT_TEST_PATTERN:
        case PAGE_RAMP_TEST_PATTERN:
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}

static UINT8 _color_tuner_get_current_sub_page(void)
{
    UINT8 u8CurSubPage;


#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    if( menu_page_color_calibration_is_CaliTestMode() )
    {
        if( FALSE == _color_tuner_is_test_pattern_page(s_eCurSubPage_TestPattern) )
        {
            DBG_LOG_PRINT(("[MENU]{%s,%d} Error: s_eCurSubPage_TestPattern:%d is not test pattern\n",  __FUNCTION__,__LINE__, s_eCurSubPage_TestPattern ));
            DBG_LOG_PRINT(("[MENU]{%s,%d} Force s_eCurSubPage_TestPattern = SMPTE_TEST_PATTERN\n",  __FUNCTION__,__LINE__ ));
            s_eCurSubPage_TestPattern = PAGE_SMPTE_TEST_PATTERN;
        }

        u8CurSubPage = s_eCurSubPage_TestPattern;
    }
    else
    {
        // always goto color_tuner
        if( s_eCurSubPage != PAGE_COLOR_TUNER_PAGE )
        {
            DBG_LOG_PRINT(("[MENU]{%s,%d} Force s_eCurSubPage = PAGE_COLOR_TUNER_PAGE\n",  __FUNCTION__,__LINE__ ));
            s_eCurSubPage = PAGE_COLOR_TUNER_PAGE;
        }
        u8CurSubPage = s_eCurSubPage;
    }
#else
    //a_cfg_custom_get_pic_quality_page(&ui2_page);
    u8CurSubPage = s_eCurSubPage;
#endif

    return u8CurSubPage;
}

static BOOL _color_tuner_set_current_sub_page(EnuColorTunerSubPage eSubPage)
{
    MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} (eSubPage:%d) \n",  __FUNCTION__,__LINE__, eSubPage )); );

#if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
    if( menu_page_color_calibration_is_CaliTestMode() )
    {
        if( FALSE == _color_tuner_is_test_pattern_page(eSubPage) )
        {
            DBG_LOG_PRINT(("[MENU]{%s,%d} Error: eSubPage:%d is not test pattern\n",  __FUNCTION__,__LINE__, eSubPage ));
            return FALSE;
        }

        s_eCurSubPage_TestPattern = eSubPage;
        MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} Set s_eCurSubPage_TestPattern=%d\n",  __FUNCTION__,__LINE__, s_eCurSubPage_TestPattern )); );
    }
    else
    {
        if( eSubPage != PAGE_COLOR_TUNER_PAGE )
        {
            DBG_LOG_PRINT(("[MENU]{%s,%d} Error: eSubPage != PAGE_COLOR_TUNER_PAGE\n",  __FUNCTION__,__LINE__ ));
            return FALSE;
        }

        // always goto color_tuner
        s_eCurSubPage = eSubPage;
        MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} Set s_eCurSubPage=%d\n",  __FUNCTION__,__LINE__, s_eCurSubPage )); );
    }
#else

    //a_cfg_custom_set_pic_quality_page(ui2_next_page_index);
    s_eCurSubPage = eSubPage;
    MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} Set s_eCurSubPage=%d\n",  __FUNCTION__,__LINE__, s_eCurSubPage )); );

#endif

    return TRUE;
}

static VOID _color_tuner_change_lang(VOID)
{
    INT8    i1_index = 0;
    UINT16  ui2_page = 0;
    UTF16_T *pw2s_str = NULL;


    ui2_page = _color_tuner_get_current_sub_page();


    switch (ui2_page)
    {
        case PAGE_COLOR_TUNER_PAGE:
            for(i1_index =COL_RED; i1_index <= COL_YELLOW; i1_index++)
            {
                c_wgl_do_cmd(t_color_tuner.ah_col[i1_index],
                              WGL_CMD_TEXT_SET_TEXT,
                              MENU_TEXT(aui2_str_dims[i1_index]),
                              (VOID*)c_uc_w2s_strlen(MENU_TEXT(aui2_str_dims[i1_index])));
            }

            for(i1_index = ROW_HUE; i1_index <= ROW_GAIN; i1_index++)
            {
                c_wgl_do_cmd(t_color_tuner.ah_txt_row[i1_index],
                             WGL_CMD_TEXT_SET_TEXT,
                             MENU_TEXT(aui2_str_ages[i1_index]),
                             (VOID*)c_uc_w2s_strlen(MENU_TEXT(aui2_str_ages[i1_index])));
            }
            pw2s_str = MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE);
            break;
        case PAGE_SMPTE_TEST_PATTERN:
            pw2s_str = MENU_TEXT(MLM_MENU_KEY_SMPTE_TEST_PATTERN);
            break;
        case PAGE_FLAT_TEST_PATTERN:
            pw2s_str = MENU_TEXT(MLM_MENU_KEY_FLAT_TEST_PATTERN);
            break;
        case PAGE_RAMP_TEST_PATTERN:
            pw2s_str = MENU_TEXT(MLM_MENU_KEY_RAMP_TEST_PATTERN_TITLE);
            break;
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            pw2s_str = MENU_TEXT(MLM_MENU_KEY_UNIFANA_TEST_PATTERN);
            break;
        default:
            pw2s_str = MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE);
            break;
    }

    c_wgl_do_cmd(ah_bar,
                  WGL_CMD_BTN_SET_TEXT,
                  WGL_PACK(pw2s_str),
                  WGL_PACK(c_uc_w2s_strlen(pw2s_str)));
}

/*----------------------------------------------------------------------------
 * Name: _change_page
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
 static VOID _change_page(UINT16 ui2_page_index,BOOL b_next)
{
    UINT16 ui2_next_page_index = ui2_page_index;
    INT32   i4_ret = 0;
    BOOL    b_pattern_off = FALSE;


    MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} ui2_page_index:%d, b_next:%d \n",  __FUNCTION__,__LINE__, ui2_page_index, b_next)); );

    if(b_next)
    {
        // goto next item ...
        switch(ui2_page_index)
        {
            case PAGE_COLOR_TUNER_PAGE:
            #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                // Cannot goto other pattern
            #else
                ui2_next_page_index = PAGE_SMPTE_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_SMPTE_TEST_PATTERN) == 0 ? TRUE : FALSE;
            #endif
                break;
            case PAGE_SMPTE_TEST_PATTERN:
                ui2_next_page_index = PAGE_FLAT_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_FLAT_TEST_PATTERN) == 0 ? TRUE : FALSE;
                //_smpte_test_pattern_get_value();
                break;
            case PAGE_FLAT_TEST_PATTERN:
                ui2_next_page_index = PAGE_RAMP_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_RAMP_TEST_PATTERN) == 0 ? TRUE : FALSE;
                //_flat_test_pattern_get_value();
                break;
            case PAGE_RAMP_TEST_PATTERN:
                ui2_next_page_index = PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN) == 0 ? TRUE : FALSE;
                break;
            case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                // goto 1st test pattern
                ui2_next_page_index = PAGE_SMPTE_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_SMPTE_TEST_PATTERN) == 0 ? TRUE : FALSE;
            #else
                ui2_next_page_index = PAGE_COLOR_TUNER_PAGE;
            #endif
                break;
            default:
                break;
        }
    }
    else
    { // goto prev item ...
        switch(ui2_page_index)
        {
            case PAGE_COLOR_TUNER_PAGE:
              #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                // Cannot goto other pattern
              #else
                ui2_next_page_index = PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN) == 0 ? TRUE : FALSE;
              #endif
                break;
            case PAGE_SMPTE_TEST_PATTERN:
             #if(MENU_COLOR_CALI_ENABLE_CALI_TEST)
                ui2_next_page_index = PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN) == 0 ? TRUE : FALSE;
             #else
                ui2_next_page_index = PAGE_COLOR_TUNER_PAGE;
             #endif
                break;
            case PAGE_FLAT_TEST_PATTERN:
                ui2_next_page_index = PAGE_SMPTE_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_SMPTE_TEST_PATTERN) == 0 ? TRUE : FALSE;
                //_flat_test_pattern_get_value();
                break;
            case PAGE_RAMP_TEST_PATTERN:
                ui2_next_page_index = PAGE_FLAT_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_FLAT_TEST_PATTERN) == 0 ? TRUE : FALSE;
                //_ramp_test_pattern_get_value();
                break;
            case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
                ui2_next_page_index = PAGE_RAMP_TEST_PATTERN;
                b_pattern_off = _get_current_test_pattern_value(PAGE_RAMP_TEST_PATTERN) == 0 ? TRUE : FALSE;
                //_ramp_test_pattern_get_value();
                break;
            default:
                break;
        }
    }


    /* Not update while new page is the same as old page */
    if (ui2_next_page_index == ui2_page_index)
    {
        MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} Page no changed~\n",  __FUNCTION__,__LINE__ )); );

    #if DBG_LOG
        DBG_INFO(("\n%s() Line %d: Need not update page.\n",__FUNCTION__, __LINE__));
    #endif

        return;
    }

    MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} ==> ui2_page_index:%d \n",  __FUNCTION__,__LINE__, ui2_page_index )); );

    _test_pattern_warning_info_visiable(FALSE, FALSE);

    //a_cfg_custom_set_pic_quality_page(ui2_next_page_index);
    if( FALSE == _color_tuner_set_current_sub_page((EnuColorTunerSubPage)ui2_next_page_index) )
    {
        DBG_LOG_PRINT(("[MENU]{%s,%d} Error: Set eSubPage=%d fail!!\n",  __FUNCTION__,__LINE__, ui2_next_page_index ));
        return;
    }


#if DBG_LOG
    DBG_INFO(("\n=================_change_page==========ui2_next_page_index=%d======%d\n",ui2_next_page_index,__LINE__));
#endif

    switch(ui2_next_page_index)
    {
        case PAGE_COLOR_TUNER_PAGE:
            a_color_tuner_update_ui();
            c_wgl_set_visibility(t_color_tuner.h_cnt_frm,WGL_SW_RECURSIVE);
            c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn, WGL_SW_HIDE);
            c_wgl_set_visibility(t_smpte_test_pattern.h_smpte_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_flast_test_pattern.h_flat_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_ramp_test_pattern.h_ramp_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);

            i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE))));
            MENU_LOG_ON_FAIL(i4_ret);
            c_wgl_repaint(h_base_fram,NULL,TRUE);
            c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
            c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE));
            _color_tuner_tts_play();
            break;
        case PAGE_SMPTE_TEST_PATTERN:
            _smpte_test_pattern_update_txt(FALSE);
            if (!b_pattern_off)
            {
                _smpte_test_pattern_set_value_by_id(t_smpte_test_pattern.ui2_val);
#ifdef NEVER
                _color_tuner_rgb_update();
#endif /* NEVER */
            }

            c_wgl_set_visibility(t_color_tuner.h_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_smpte_test_pattern.h_smpte_test_cnt_frm,WGL_SW_RECURSIVE);
            c_wgl_set_visibility(t_flast_test_pattern.h_flat_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_ramp_test_pattern.h_ramp_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);

            i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SMPTE_TEST_PATTERN)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_SMPTE_TEST_PATTERN))));
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(h_base_fram,NULL,TRUE);
            c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
            c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_SMPTE_TEST_PATTERN));
            _color_tuner_tts_play();
            break;
        case PAGE_FLAT_TEST_PATTERN:
            _flat_test_pattern_update_txt(FALSE);
            if (!b_pattern_off)
            {
                _flat_test_pattern_set_value_by_id(t_flast_test_pattern.ui2_val);
#ifdef NEVER
                _color_tuner_rgb_update();
#endif /* NEVER */
            }

            c_wgl_set_visibility(t_color_tuner.h_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_smpte_test_pattern.h_smpte_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_flast_test_pattern.h_flat_test_cnt_frm,WGL_SW_RECURSIVE);
            c_wgl_set_visibility(t_ramp_test_pattern.h_ramp_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);

            i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_FLAT_TEST_PATTERN)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_FLAT_TEST_PATTERN))));
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(h_base_fram,NULL,TRUE);
            c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
            c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_FLAT_TEST_PATTERN));
            _color_tuner_tts_play();
            break;
        case PAGE_RAMP_TEST_PATTERN:
            _ramp_test_pattern_update_txt(FALSE);
            if (!b_pattern_off)
            {
                _ramp_test_pattern_set_value_by_id(t_ramp_test_pattern.ui2_val);
                //_color_tuner_rgb_update();
            }

            c_wgl_set_visibility(t_color_tuner.h_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_smpte_test_pattern.h_smpte_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_flast_test_pattern.h_flat_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_ramp_test_pattern.h_ramp_test_cnt_frm,WGL_SW_RECURSIVE);
            c_wgl_set_visibility(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);

            i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_RAMP_TEST_PATTERN_TITLE)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_RAMP_TEST_PATTERN_TITLE))));
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(h_base_fram,NULL,TRUE);
            c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
            c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_RAMP_TEST_PATTERN_TITLE));
            _color_tuner_tts_play();
            break;
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            _uniformity_analyzer_test_pattern_update_txt(FALSE);
            if (!b_pattern_off)
            {
                _uniformity_analyzer_test_pattern_set_value_by_id(t_uniformity_analyzer_test_pattern.ui2_val);
            }

            c_wgl_set_visibility(t_color_tuner.h_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_smpte_test_pattern.h_smpte_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_flast_test_pattern.h_flat_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_ramp_test_pattern.h_ramp_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,WGL_SW_RECURSIVE);

            i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_UNIFANA_TEST_PATTERN)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_UNIFANA_TEST_PATTERN))));
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(h_base_fram,NULL,TRUE);
            c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
            c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_UNIFANA_TEST_PATTERN));
            _color_tuner_tts_play();
            break;

        default:
            c_wgl_set_visibility(t_color_tuner.h_cnt_frm,WGL_SW_RECURSIVE);
            c_wgl_set_visibility(t_smpte_test_pattern.h_smpte_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_flast_test_pattern.h_flat_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_ramp_test_pattern.h_ramp_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_set_visibility(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,WGL_SW_HIDE_RECURSIVE);

            i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE))));
            MENU_LOG_ON_FAIL(i4_ret);

            c_wgl_repaint(h_base_fram,NULL,TRUE);
            c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
            c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE));
            _color_tuner_tts_play();

            break;
    }
}

static INT32 _test_pattern_left_right_arrow_show(BOOL b_show)
{
    INT32 i4_ret = MENUR_OK;
    WGL_SW_CMD_T e_sw_cmd = b_show ? WGL_SW_NORMAL : WGL_SW_HIDE;

    i4_ret = c_wgl_set_visibility(h_left_arrow, e_sw_cmd);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_right_arrow, e_sw_cmd);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_float(h_left_arrow, b_show, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_float(h_right_arrow, b_show, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _test_pattern_left_right_arrow_create(VOID)
{
    INT32                           i4_ret = MENUR_OK;
    GL_RECT_T                       t_rect;
    WGL_IMG_INFO_T                  t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                      MENU_COLOR_TUNER_L_ARROW_X,
                      MENU_COLOR_TUNER_L_ARROW_Y,
                      MENU_COLOR_TUNER_L_ARROW_W,
                      MENU_COLOR_TUNER_L_ARROW_H);
    i4_ret = c_wgl_create_widget(h_base_fram,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &h_left_arrow);

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_COLOR_TUNER_R_ARROW_X,
                     MENU_COLOR_TUNER_R_ARROW_Y,
                     MENU_COLOR_TUNER_R_ARROW_W,
                     MENU_COLOR_TUNER_R_ARROW_H);

    i4_ret = c_wgl_create_widget(h_base_fram,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &h_right_arrow);

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(h_left_arrow,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_right_arrow,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Image */
    c_memset(&t_img_info, 0, sizeof(t_img_info));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_extend.t_disable    = h_g_menu_img_list_item_leftarrow;
    t_img_info.u_img_data.t_extend.t_enable     = h_g_menu_img_list_item_leftarrow;
    t_img_info.u_img_data.t_extend.t_highlight  = h_g_menu_img_list_item_leftarrow;

    i4_ret = c_wgl_do_cmd(h_left_arrow,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(t_img_info));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_extend.t_disable    = h_g_menu_img_list_item_rightarrow;
    t_img_info.u_img_data.t_extend.t_enable     = h_g_menu_img_list_item_rightarrow;
    t_img_info.u_img_data.t_extend.t_highlight  = h_g_menu_img_list_item_rightarrow;

    i4_ret = c_wgl_do_cmd(h_right_arrow,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    _test_pattern_left_right_arrow_show(FALSE);

    return MENUR_OK;
}

static INT32 _test_pattern_warning_info_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect = {0};
    WGL_COLOR_INFO_T    t_clr_txt = {0};
    WGL_FONT_INFO_T     t_fnt_info = {0};
    UINT32              ui4_style;

    ui4_style = WGL_STL_GL_NO_IMG_UI
                | WGL_STL_TEXT_MAX_128
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_COLOR_TUNER_WARING_INFO_X,
                     MENU_COLOR_TUNER_WARING_INFO_Y,
                     MENU_COLOR_TUNER_WARING_INFO_W,
                     MENU_COLOR_TUNER_WARING_INFO_H);

    i4_ret = c_wgl_create_widget(h_base_fram,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_warning_info);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    WGL_INSET_T t_inset = {
        30,
        30,
        0,
        0};

    i4_ret = c_wgl_do_cmd(h_warning_info,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_warning_info,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (h_warning_info,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set txt color */
    t_clr_txt.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_txt.u_color_data.t_standard.t_enable    = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_standard.t_highlight = t_g_menu_color_bk0_txt_hlt;
    t_clr_txt.u_color_data.t_standard.t_disable   = t_g_menu_color_bk0_txt_hlt;
    i4_ret = c_wgl_do_cmd(h_warning_info,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_warning_info, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}

static INT32 _test_pattern_warning_info_visiable(BOOL b_visiable, BOOL b_repaint)
{
    INT32 i4_ret = MENUR_OK;
    WGL_SW_CMD_T e_sw_cmd = WGL_SW_HIDE;

    DBG_INFO(("%s(%d, %d) Line %d: b_warning_show = %d\n", __FUNCTION__, __LINE__,
                                                    b_visiable,
                                                    b_repaint,
                                                    b_warning_show));

    if (b_warning_show == b_visiable
        && !b_repaint)
    {
        return MENUR_OK;
    }

    b_warning_show = b_visiable;

    e_sw_cmd = (b_visiable == TRUE) ? WGL_SW_NORMAL : WGL_SW_HIDE;

    if (b_visiable)
    {
        i4_ret = c_wgl_do_cmd(h_warning_info,
                             WGL_CMD_TEXT_SET_TEXT,
                             WGL_PACK(MENU_TEXT(MLM_MENU_KEY_PIC_MODE_PATTERN_CAST_MSG)),
                             WGL_PACK(0xFF));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(h_warning_info,e_sw_cmd);
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(h_base_fram, NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;

}

static BOOL _test_pattern_enable(VOID)
{
    TV_WIN_ID_T     e_focus_id = TV_WIN_ID_MAIN;
    ISL_REC_T       t_isl_rec = {0};
    BOOL            b_enable = TRUE;
    CHAR            s_active_app[APP_NAME_MAX_LEN + 1] = {0};

    /*If previous source is CastTV, exit it */
    a_tv_get_focus_win(&e_focus_id);

    a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);

    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
        b_enable = FALSE;
    }
    else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        b_enable = FALSE;
    }
    else if(menu_is_signal_loss()&&(!(t_flast_test_pattern.ui2_val ||
                t_ramp_test_pattern.ui2_val ||
                t_uniformity_analyzer_test_pattern.ui2_val||
                t_smpte_test_pattern.ui2_val)))
    {
        b_enable = FALSE;
    }

    a_am_get_active_app (s_active_app);
    if (c_strcmp(s_active_app, MMP_NAME) == 0)
    {
        b_enable = FALSE;
    }
    DBG_LOG_PRINT(("[Menu] b_enable :%d,%s,%d\r\n",b_enable,__FUNCTION__,__LINE__));

    return b_enable;

}

static BOOL _menu_page_color_tuner_IsCurSrcSupportTestPattern(void)
{
    BOOL bSupportTestPattern = FALSE;

    ISL_REC_T  t_isl_rec;
    c_memset(&t_isl_rec, 0, sizeof(t_isl_rec) );


    //DBG_LOG_PRINT(("[MENU][ColorTuner]{%s: %s: %d}\n", __FILE__, __FUNCTION__,__LINE__));

    /* Get the input source on FOCUSED WIN */
    INT32 i32Rtn = menu_get_crnt_isl(&t_isl_rec);
    if( i32Rtn != MENUR_OK )
    {
        DBG_LOG_PRINT(("[MENU][ColorTuner] Error: Can't get cur source! {%s: %s: %d}\n", __FILE__, __FUNCTION__,__LINE__));
        return FALSE;
    }

    //DBG_LOG_PRINT(("[MENU][ColorTuner]{%s: %s: %d} t_isl_rec.e_src_type=%d\n", __FILE__, __FUNCTION__,__LINE__, t_isl_rec.e_src_type ));

    // Only TV/AV support color tuner...
    // SmartCast is INP_SRC_TYPE_VTRL
    if( (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
      ||(t_isl_rec.e_src_type == INP_SRC_TYPE_AV) // HDMI
      )
    {
        bSupportTestPattern = TRUE;
    }

    return bSupportTestPattern;
}

/*----------------------------------------------------------------------------
 * Name: _bar_proc_fct
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
 static INT32 _bar_proc_fct(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    UINT32 ui4_key_code = (UINT32)pv_param1;
    GL_RECT_T                       t_rect;
    UINT16                          ui2_page = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff = 0;
    UTF16_T w2s_str[256] = {0};

    //a_cfg_custom_get_pic_quality_page(&ui2_page);
    ui2_page = _color_tuner_get_current_sub_page();


    switch (ui4_msg)
    {
        case WGL_MSG_LOSE_FOCUS:
            break;
        case WGL_MSG_GET_FOCUS:
            //b_right = (ah_bar_right_btn == h_widget) ? TRUE : FALSE;
            break;
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch (ui4_key_code)
            {
                case BTN_CURSOR_UP:
                    break;
                case BTN_CURSOR_DOWN:
                    /* lock custom pic mode can show color tuner item  ,but can't change the vlaue */
                    if(a_menu_is_cust_pic_mode_and_locked())
                    {
                        break;
                    }
                     _uniformity_analyzer_test_pattern_set_title_font_size(FALSE);
                    if(ui2_page == PAGE_COLOR_TUNER_PAGE)
                    {
                        t_color_tuner.ui1_hlt_col = COL_RED;
                        c_wgl_set_focus(t_color_tuner.ah_col[t_color_tuner.ui1_hlt_col],TRUE);
                        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, (APP_CFG_RECID_VID_RED+t_color_tuner.ui1_hlt_col));
                        a_cfg_av_get( ui2_id, &i2ROnOff);
                        c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(aui2_str_dims[t_color_tuner.ui1_hlt_col]));
                        c_uc_w2s_strcat(w2s_str, _TEXT("."));
                        if(i2ROnOff == 1)
                        {
                          c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_ON));
                        }
                        else
                        {
                          c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_OFF));
                        }
                        c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                        c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
                        _color_tuner_tts_play();

                        c_wgl_get_coords(t_color_tuner.h_col_hlt_mov_btn,WGL_COORDS_PARENT,&t_rect);
                        t_rect.i4_left  = RED_ON_OFF_HLT_MOVE_BTN_X;
                        t_rect.i4_right  = t_rect.i4_left + RED_ON_OFF_HLT_MOVE_BTN_W;
                        c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn,WGL_SW_NORMAL);
                        c_wgl_move(t_color_tuner.h_col_hlt_mov_btn,&t_rect,TRUE);
                        c_wgl_repaint(t_color_tuner.h_cnt_frm,NULL,TRUE);


                    }
                    else if(ui2_page == PAGE_SMPTE_TEST_PATTERN)
                    {
                        if (_test_pattern_enable())
                        {
                            _test_pattern_warning_info_visiable(FALSE, FALSE);
                            c_wgl_set_focus(t_smpte_test_pattern.h_smpte_test_num_btn,TRUE);
                        }
                        else
                        {
                            _test_pattern_warning_info_visiable(TRUE, TRUE);
                        }

                        _smpte_test_pattern_curnt_tts_play();
                    }
                    else if(ui2_page == PAGE_FLAT_TEST_PATTERN)
                    {
                        if (_test_pattern_enable())
                        {
                            _test_pattern_warning_info_visiable(FALSE, FALSE);
                            c_wgl_set_focus(t_flast_test_pattern.h_flat_test_num_btn,TRUE);
                        }
                        else
                        {
                            _test_pattern_warning_info_visiable(TRUE, TRUE);
                        }

                        _flat_test_pattern_curnt_tts_play();
                    }
                    else if(ui2_page == PAGE_RAMP_TEST_PATTERN)
                    {
                        if (_test_pattern_enable())
                        {
                            _test_pattern_warning_info_visiable(FALSE, FALSE);
                            c_wgl_set_focus(t_ramp_test_pattern.h_ramp_test_color_btn,TRUE);
                        }
                        else
                        {
                            _test_pattern_warning_info_visiable(TRUE, TRUE);
                        }

                        _ramp_test_pattern_curnt_tts_play();
                    }
                    else if(ui2_page == PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN)
                    {
                        _uniformity_analyzer_test_pattern_set_title_font_size(TRUE);
                        if (_test_pattern_enable())
                        {
                            _test_pattern_warning_info_visiable(FALSE, FALSE);
                            c_wgl_set_focus(t_uniformity_analyzer_test_pattern.h_unif_test_num_btn,TRUE);
                        }
                        else
                        {
                            _test_pattern_warning_info_visiable(TRUE, TRUE);
                        }

                        _uniformity_analyzer_test_pattern_curnt_tts_play();

                    }
                    break;
                case BTN_CURSOR_LEFT:
                     _uniformity_analyzer_test_pattern_set_title_font_size(FALSE);
                    _change_page(ui2_page,FALSE);
                    break;
                case BTN_CURSOR_RIGHT:
                     _uniformity_analyzer_test_pattern_set_title_font_size(FALSE);
                    _change_page(ui2_page,TRUE);
                    break;
                case BTN_SELECT:
                    break;
                case BTN_RETURN:
                     _uniformity_analyzer_test_pattern_set_title_font_size(FALSE);
                     /* Let the menu show */
                     c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
                     c_wgl_repaint(h_base_fram,NULL,TRUE);
                     menu_main_set_visibility(TRUE);
                     menu_nav_back();
                    break;
                default:
                    break;
            }

        }

        default:
            break;
    }
    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

}

/*----------------------------------------------------------------------------
 * Name: _create_bar_title
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
static INT32 _create_bar_title(HANDLE_T*   ph_widget)
{
    INT32                           i4_ret = MENUR_OK;
    GL_RECT_T                       t_rect;
    WGL_LB_COLOR_ELEM_SET_T   t_lb_color;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                   MENU_COLOR_TUNER_BAR_X,
                   MENU_COLOR_TUNER_BAR_Y,
                   MENU_COLOR_TUNER_BAR_W,
                   MENU_COLOR_TUNER_BAR_H);


    i4_ret = c_wgl_create_widget(h_base_fram,
                                         HT_WGL_WIDGET_BUTTON,
                                         WGL_CONTENT_BUTTON_DEF,
                                         WGL_BORDER_NULL,
                                         &t_rect,
                                         _bar_proc_fct,
                                         255,
                                         (VOID*)0,
                                         NULL,
                                         &ah_bar);

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }
     /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_BIG);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;


    i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

     /* Set colors */
    t_lb_color.t_normal             = t_g_menu_color_bk0_txt_hlt;
    t_lb_color.t_disable            = t_g_menu_color_bk0_txt_hlt;
    t_lb_color.t_highlight          = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus  = t_g_menu_color_white;
    t_lb_color.t_pushed             = t_g_menu_color_white;
    t_lb_color.t_selected           = t_g_menu_color_white;
    t_lb_color.t_selected_disable   = t_g_menu_color_white;

     i4_ret = c_wgl_do_cmd(ah_bar,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(& t_lb_color));
     MENU_LOG_ON_FAIL(i4_ret);

    /* Set Image */
    c_memset(&t_img_info, 0, sizeof(t_img_info));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable            = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_pic_color_tuner_top_highlight_ex_v2;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_pic_color_tuner_top_highlight_ex_v2;
    t_img_info.u_img_data.t_extend.t_push               = h_g_pic_color_tuner_top_highlight_ex_v2;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_pic_color_tuner_top_highlight_ex_v2;

    i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_base_frm_create
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
static INT32 _menu_base_frm_create(HANDLE_T h_parent)
{
    GL_RECT_T               t_rect = {0};
    INT32                   i4_ret = 0;
    WGL_IMG_INFO_T      t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                 MENU_COLOR_TUNER_FRAME_X,
                 MENU_COLOR_TUNER_FRAME_Y,
                 MENU_COLOR_TUNER_FRAME_W,
                 MENU_COLOR_TUNER_FARME_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &h_base_fram);

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_g_menu_ColorTuner_with_rgb_back;
    t_img_info.u_img_data.t_standard.t_highlight    = h_g_menu_ColorTuner_with_rgb_back;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_menu_ColorTuner_with_rgb_back;

    i4_ret = c_wgl_do_cmd(h_base_fram,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}


static INT32 _title_curnt_tts_play(VOID)
{
    INT32       i4_ret = 0;
    UINT16  ui2_page = 0;
    UTF16_T *pw2s_str = NULL;

    //a_cfg_custom_get_pic_quality_page(&ui2_page);
    ui2_page = _color_tuner_get_current_sub_page();

    switch (ui2_page)
    {
        case PAGE_COLOR_TUNER_PAGE:
            pw2s_str = MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE);
            break;
        case PAGE_SMPTE_TEST_PATTERN:
            pw2s_str = MENU_TTS_TEXT(MLM_MENU_KEY_SMPTE_TEST_PATTERN);
            break;
        case PAGE_FLAT_TEST_PATTERN:
            pw2s_str = MENU_TTS_TEXT(MLM_MENU_KEY_FLAT_TEST_PATTERN);
            break;
        case PAGE_RAMP_TEST_PATTERN:
            pw2s_str = MENU_TTS_TEXT(MLM_MENU_KEY_RAMP_TEST_PATTERN_TITLE);
            break;
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            pw2s_str = MENU_TTS_TEXT(MLM_MENU_KEY_UNIFANA_TEST_PATTERN);
            break;
        default:
            pw2s_str = MENU_TTS_TEXT(MLM_MENU_KEY_COLOR_TUNER_TITLE);
            break;
    }

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,pw2s_str);
     _color_tuner_tts_play();

    return i4_ret;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret = 0;
    HANDLE_T    h_root_frm =NULL_HANDLE;
    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_base_frm_create(h_root_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_bar_title(&ah_bar);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _color_tuner_page_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _smpte_test_pattern_page_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _flat_test_pattern_page_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _ramp_test_pattern_page_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _uniformity_analyzer_test_pattern_page_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _test_pattern_left_right_arrow_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _test_pattern_warning_info_create();
    MENU_CHK_FAIL(i4_ret);


    i4_ret = c_timer_create(&h_timer_tts);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;;

}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = a_icl_notify_unreg(ui2_yahoo_state_nfy);
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32   i4_ret = 0;
    //UINT16  ui2_val = 0;

#ifdef VIEWPORT_SUPPORT
    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_WIDE_MODE);
    a_cfg_update_viewport ();
#endif

    i4_ret = menu_main_set_visibility(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);


#ifdef NEVER
    if (TRUE == b_show_first)
    {
        //color_tuner_get_rgb_cfg_value();
        _smpte_test_pattern_reset();
        _flat_test_pattern_reset();
        _ramp_test_pattern_reset();
    }
#endif /* NEVER */


    //a_cfg_custom_get_pic_quality_page(&ui2_val);
    UINT8 u8CurSubPage = _color_tuner_get_current_sub_page();
    MENU_CT_DEBUG( DBG_LOG_PRINT(("[MENU]{%s,%d} u8CurSubPage:%d\n",  __FUNCTION__,__LINE__,u8CurSubPage )); );

  #if DBG_LOG
    DBG_INFO(("\n================_on_page_show==========================%d,%d\n",u8CurSubPage,__LINE__));
  #endif


    switch(u8CurSubPage)
    {
        case PAGE_COLOR_TUNER_PAGE:
            a_color_tuner_update_ui();
            i4_ret = c_wgl_set_visibility(h_base_fram,WGL_SW_HIDE_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = c_wgl_set_visibility(t_color_tuner.h_cnt_frm,WGL_SW_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = c_wgl_set_visibility(t_color_tuner.h_col_hlt_mov_btn,WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        case PAGE_SMPTE_TEST_PATTERN:
            _smpte_test_pattern_update_txt(FALSE);
            if(t_smpte_test_pattern.ui2_val)
            {
                _smpte_test_pattern_set_value_by_id(t_smpte_test_pattern.ui2_val);
            }

            i4_ret = c_wgl_set_visibility(h_base_fram,WGL_SW_HIDE_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = c_wgl_set_visibility(t_smpte_test_pattern.h_smpte_test_cnt_frm,WGL_SW_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        case PAGE_FLAT_TEST_PATTERN:
            _flat_test_pattern_update_txt(FALSE);
            if(t_flast_test_pattern.ui2_val)
            {
                _flat_test_pattern_set_value_by_id(t_flast_test_pattern.ui2_val);
            }

            i4_ret = c_wgl_set_visibility(h_base_fram,WGL_SW_HIDE_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = c_wgl_set_visibility(t_flast_test_pattern.h_flat_test_cnt_frm,WGL_SW_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        case PAGE_RAMP_TEST_PATTERN:
            if(t_ramp_test_pattern.ui2_val)
            {
                _ramp_test_pattern_set_value_by_id(t_ramp_test_pattern.ui2_val);
            }
            _ramp_test_pattern_update_txt(FALSE);

            i4_ret = c_wgl_set_visibility(h_base_fram,WGL_SW_HIDE_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = c_wgl_set_visibility(t_ramp_test_pattern.h_ramp_test_cnt_frm,WGL_SW_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
              break;
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            if(t_uniformity_analyzer_test_pattern.ui2_val)
            {
                _uniformity_analyzer_test_pattern_set_value_by_id(t_uniformity_analyzer_test_pattern.ui2_val);
            }
            _uniformity_analyzer_test_pattern_update_txt(FALSE);

            i4_ret = c_wgl_set_visibility(h_base_fram,WGL_SW_HIDE_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = c_wgl_set_visibility(t_uniformity_analyzer_test_pattern.h_unif_test_cnt_frm,WGL_SW_RECURSIVE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;

    }

    _color_tuner_change_lang();
    _title_curnt_tts_play();

    i4_ret = c_wgl_set_visibility(ah_bar, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_base_fram, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    _test_pattern_warning_info_visiable(FALSE, FALSE);
    //Fix Cverity ID : 4524482 Unchecked return value
    i4_ret = c_wgl_insert(h_base_fram, NULL_HANDLE, WGL_INSERT_TOPMOST, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
    c_wgl_repaint(h_base_fram,NULL,TRUE);
#ifdef NEVER
    b_show_first = FALSE;
#endif /* NEVER */
    b_page_show = TRUE;
    return MENUR_OK;
}
static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32   i4_ret = 0;
    //UINT8   ui1_i = 0;

    /* NOT Turn off flat test pattern */
    //_flat_test_pattern_get_value();

    /* NOT Turn off flat test pattern */
    //_ramp_test_pattern_get_value();
    b_page_show = FALSE;

    if ((0 == t_ramp_test_pattern.ui2_val)  &&
        (0 == t_smpte_test_pattern.ui2_val) &&
        (0 == t_flast_test_pattern.ui2_val) &&
        (0 == t_uniformity_analyzer_test_pattern.ui2_val))
    {
        banner_view_set_b_ctrl_show_flag(TRUE);
    }

#ifdef NEVER
if ((0 != t_ramp_test_pattern.ui2_val)  ||
    (0 != t_smpte_test_pattern.ui2_val) ||
    (0 != t_flast_test_pattern.ui2_val)||
    (0 != t_uniformity_analyzer_test_pattern.ui2_val)
    )
    {
        _menu_test_pattern_stop();
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_DISABLE);
        _color_tuner_rollback_svc();
        t_ramp_test_pattern.ui2_val = 0;
        t_smpte_test_pattern.ui2_val = 0;
        t_flast_test_pattern.ui2_val = 0;
        t_uniformity_analyzer_test_pattern.ui2_val = 0;

        c_thread_delay(2000);
        DBG_LOG_PRINT(("[menu] c_thread_delay(2000) %s,%d \r\n",__FUNCTION__,__LINE__));
    }
#endif /* NEVER */

    i4_ret = c_wgl_do_cmd(t_color_tuner.aah_cb_tr[t_color_tuner.ui1_hlt_row][t_color_tuner.ui1_hlt_col],
                            WGL_CMD_BTN_SET_PUSHED,
                            WGL_PACK(FALSE),
                            WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);


    _test_pattern_warning_info_visiable(FALSE, FALSE);

#ifdef VIEWPORT_SUPPORT
    if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
    {
        a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
    }

#ifdef APP_MENU_MMP_COEXIST
    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        MMP_BE_BROWSER_STATUS_T  e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;
        e_mmp_browser_status = a_mmp_be_get_browser_status();
        if ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING != e_mmp_browser_status)
            && (MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING != e_mmp_browser_status)
            && (MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING != e_mmp_browser_status)
            && (MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING != e_mmp_browser_status))
        {
            //No need to update viewport
        }
        else
        {
            a_cfg_update_viewport ();
        }
    }
    else
    {
        a_cfg_update_viewport ();
    }
#endif
#endif

    i4_ret = c_wgl_set_visibility(h_base_fram, WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);
    //c_wgl_repaint(h_base_fram,NULL,TRUE);

    //i2_scrn_mode = 0;
    return MENUR_OK;

}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    c_wgl_set_focus(ah_bar,TRUE);
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
    if (ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG)
    {
        _color_tuner_change_lang();
    }
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _test_pattern_yahoo_stat_proc
 *
 * Description: turn off test pattern when lanuch yahoo dock
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _test_pattern_yahoo_stat_proc(VOID*                pv_tag1,
                                        VOID*                       pv_tag2,
                                        VOID*                       pv_tag3)
{
    a_menu_test_patterns_turn_off();
    a_color_tuner_update_value();
    DBG_INFO(("\n####%s(%d)turn off test patterns when lanuch yahoo dock\n",__FUNCTION__,__LINE__));
}

/*----------------------------------------------------------------------------
 * Name: _test_pattern_yahoo_state_nfy_func
 *
 * Description: turn off test pattern when lanuch yahoo dock
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _test_pattern_yahoo_state_nfy_func(UINT16 ui2_nfy_id,
                                            VOID* pv_tag,
                                            ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32  i4_ret;
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    SIZE_T z_size ;
    UINT8      ui1_icl_mask,ui1_info_status;

    if (e_grp_id != ICL_GRPID_CUSTOM_NW_WIDGET)
    {
        return MENUR_OK;
    }

    ui1_icl_mask = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS;
    z_size = ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_NW_WIDGET, ui1_icl_mask),
                       &ui1_info_status,
                       &z_size);

    MENU_CHK_FAIL(i4_ret);

    DBG_INFO(("%s(%d) ui4_yahoo_stat = %d\n", __FUNCTION__,__LINE__, ui1_info_status));

    if(ui1_info_status == NW_APP_STATUS_FULLSCREEN)
    {
        menu_request_context_switch(_test_pattern_yahoo_stat_proc, NULL, NULL, NULL);
    }

    return MENUR_OK;
}
INT32 menu_common_page_picture_quality_init(VOID)
{
    INT32       i4_ret = MENUR_OK;
    t_g_menu_common_page_pic_quality.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_pic_quality.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_pic_quality.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_pic_quality.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_pic_quality.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_pic_quality.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_pic_quality.pf_menu_page_update=     _on_page_update;
    i4_ret = a_icl_notify_reg(ICL_GRPID_CUSTOM_NW_WIDGET,
                              ICL_RECID_CUSTOM_NW_WIDGET_DOCK_STATUS,
                              NULL,
                              NULL,
                              _test_pattern_yahoo_state_nfy_func,
                              &ui2_yahoo_state_nfy);

    MENU_CHK_FAIL(i4_ret);
    i4_ret = color_tuner_get_rgb_cfg_value();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_color_tuner_adjust_test_pattern
 *
 * Description:This api is use for test pattern adjust
 *
 * Inputs:           ui1_scrn_page                                               ui1_test_pattern
 *          PAGE_COLOR_TUNER_PAGE       0
             PAGE_SMPTE_TEST_PATTERN   1
             PAGE_FLAT_TEST_PATTERN      2
             PAGE_RAMP_TEST_PATTERN     3
             PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN  4
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

INT32 menu_page_color_tuner_adjust_test_pattern(UINT16 ui2_test_page,UINT16 ui2_test_pattern)
{
    INT32   i4_ret = 0;
    DBG_LOG_PRINT(("[MENU] ui2_test_page:%d,ui2_test_pattern :%d,%s,%d\r\n",ui2_test_page,ui2_test_pattern,__FUNCTION__,__LINE__));

    if(_test_pattern_enable() == FALSE )
    {
        DBG_LOG_PRINT(("[MENU][%s]:[%d]_test_pattern_enable : FALSE \n",__FILE__,__LINE__));
        return i4_ret;

    }

    if(ui2_test_pattern == 0)
    {
        banner_view_set_b_ctrl_show_flag(TRUE);
    }
    else
    {
        banner_view_set_b_ctrl_show_flag(FALSE);
    }

    switch(ui2_test_page)
    {
        case PAGE_SMPTE_TEST_PATTERN:
            if((ui2_test_pattern == 0)||(ui2_test_pattern == 1))
            {
                t_smpte_test_pattern.ui2_val = ui2_test_pattern;
                _smpte_test_pattern_set_value_by_id(ui2_test_pattern);
            }
            break;
        case PAGE_FLAT_TEST_PATTERN:
            if((ui2_test_pattern>=SMPTE_TEST_PATTERN_ONOFF)&&(ui2_test_pattern<=FLAT_TEST_PATTERN_100))
            {
                 t_flast_test_pattern.ui2_val = ui2_test_pattern;
                _flat_test_pattern_set_value_by_id(ui2_test_pattern);
            }
            break;
        case PAGE_RAMP_TEST_PATTERN:
            if((ui2_test_pattern >= 0)&&(ui2_test_pattern <=4))
            {
                t_ramp_test_pattern.ui2_val = ui2_test_pattern;
                _ramp_test_pattern_set_value_by_id(ui2_test_pattern);
            }
            break;
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            if((ui2_test_pattern == 0)||(ui2_test_pattern == 1))
            {
                t_uniformity_analyzer_test_pattern.ui2_val = ui2_test_pattern;
                _uniformity_analyzer_test_pattern_set_value_by_id(ui2_test_pattern);

            }
            break;
        default:
            break;
    }
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: menu_page_color_tuner_get_test_pattern
 *
 * Description:This api is use for test pattern adjust
 *
 * Inputs:           ui1_scrn_page
 *          PAGE_COLOR_TUNER_PAGE       0
             PAGE_SMPTE_TEST_PATTERN   1
             PAGE_FLAT_TEST_PATTERN      2
             PAGE_RAMP_TEST_PATTERN     3
             PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN  4
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

UINT16 menu_page_color_tuner_get_test_pattern(UINT16 ui2_scrn_page)
{
    UINT16   ui2_current_test_pattern = 0;
    switch(ui2_scrn_page)
    {
        case PAGE_SMPTE_TEST_PATTERN:
              ui2_current_test_pattern = t_smpte_test_pattern.ui2_val;
            break;
        case PAGE_FLAT_TEST_PATTERN:
              ui2_current_test_pattern =  t_flast_test_pattern.ui2_val;
            break;
        case PAGE_RAMP_TEST_PATTERN:
            ui2_current_test_pattern = t_ramp_test_pattern.ui2_val;
            break;
        case PAGE_UNIFORMITY_ANALYZER_TEST_PATTERN:
            ui2_current_test_pattern =  t_uniformity_analyzer_test_pattern.ui2_val;
            break;
        default:
            break;
    }

    return ui2_current_test_pattern;
}

INT32 menu_page_color_tuner_is_scrn_mode(VOID)
{
    INT32   i4_ret = 0;

    switch(i2_scrn_mode)
    {
        case ACFG_TEST_PATTERN_SCRN_MODE_NONE:
            break;
        case ACFG_TEST_PATTERN_SCRN_MODE_WIDE:
        {
            i4_ret = ACFG_TEST_PATTERN_SCRN_MODE_WIDE;
            break;
        }
        case ACFG_TEST_PATTERN_SCRN_MODE_NORMAL:
        {
            i4_ret = ACFG_TEST_PATTERN_SCRN_MODE_NORMAL;
            break;
        }
        default:
            break;

    }
    return i4_ret;
}

static INT32 _factory_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    MENU_DEBUG_TEST_PATTERN( DBG_LOG_PRINT(("[MENU][TEST_PATTERN]{%s,%d} ui2_val:%d, \r\n", __FUNCTION__,__LINE__, ui2_val )); );

    if ((0 != ui2_val) &&
        ((0 != t_smpte_test_pattern.ui2_val)  ||
         (0 != t_ramp_test_pattern.ui2_val) ||
         (0 != t_flast_test_pattern.ui2_val) ||
         (0 != t_uniformity_analyzer_test_pattern.ui2_val)))
    {
        a_icl_custom_set_test_pattern_status(ICL_RECID_TEST_PATTERN_STATUS_ENABLE_SEQ);
    }

    _test_pattern_set_value_by_id(PAGE_FACTORY_TEST_PATTERN, ui2_val);
    t_factory_test_pattern.ui2_val = ui2_val;

    return MENUR_OK;
}

INT32 menu_factory_test_pattern_set_value_by_id(UINT16 ui2_val)
{
    return _factory_test_pattern_set_value_by_id(ui2_val);
}


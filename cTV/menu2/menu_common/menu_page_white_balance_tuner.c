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

#include "nav/cc_info/cc_info.h"
#include "nav/banner2/a_banner.h"


//=================================================================================

#define M_WB_T_TAG  "[WB_T] "

#if 0 // Debug
    #define WB_T_CUR_LINE()     DBG_LOG_PRINT(( M_WB_T_TAG "%s: %s: %d\n", __FILE__, __FUNCTION__,__LINE__))

#define WB_T_DEBUG_FLOW(x) do { \
        WB_T_CUR_LINE(); \
        x ; \
    } while(0)

#define WB_T_DEBUG_VAL(x) do { \
    WB_T_CUR_LINE(); \
    x ; \
} while(0)

#define WB_T_DEBUG_UI(x) do { \
    WB_T_CUR_LINE(); \
    x ; \
} while(0)

#else
    #define WB_T_CUR_LINE()

    #define WB_T_DEBUG_FLOW(x)
    #define WB_T_DEBUG_VAL(x)
    #define WB_T_DEBUG_UI(x)
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define APP_VALUE_LEN                       10


#define COL_IRE                             0
#define COL_RED                             1
#define COL_GREEN                           2
#define COL_BLUE                            3
#define COL_MAX                             4

//white balance tuner
#define ROW_IRE                             0
#define ROW_OFFSET                          1
#define ROW_GAIN                            2
#define ROW_MAX                             3


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

#define MENU_COLOR_TUNER_ROW_X              (0)
#define MENU_COLOR_TUNER_ROW_Y              (MENU_COLOR_TUNER_COL_Y + MENU_COLOR_TUNER_COL_H)
#define MENU_COLOR_TUNER_ROW_W              (155)
#define MENU_COLOR_TUNER_ROW_H              (46)


#define MENU_COLOR_TUNER_COL_X              (MENU_COLOR_TUNER_ROW_X + MENU_COLOR_TUNER_ROW_W)
#define MENU_COLOR_TUNER_COL_Y              (0)
#define MENU_COLOR_TUNER_COL_W              (120)
#define MENU_COLOR_TUNER_COL_H              (48)
#define MENU_COLOR_TUNER_COL_Y_OFFSET       (22)


#define RED_ON_OFF_BTN_LINE                 (2)
#define RED_ON_OFF_BTN_X                    (MENU_COLOR_TUNER_COL_X)
#define RED_ON_OFF_BTN_Y                    (MENU_COLOR_TUNER_COL_Y)
#define RED_ON_OFF_BTN_W                    (MENU_COLOR_TUNER_COL_W)
#define RED_ON_OFF_BTN_H                    (MENU_COLOR_TUNER_COL_H)
#define RED_ON_OFF_BTN_MOV_OFFSET           (MENU_COLOR_TUNER_COL_W+RED_ON_OFF_BTN_LINE)



#define MENU_11_POINT_CONTANT_X                 ((MENU_COLOR_TUNER_BAR_W - 490)/2)
#define MENU_11_POINT_CONTANT_Y                 (MENU_COLOR_TUNER_GRID_Y)
#define MENU_11_POINT_CONTANT_W                 (490)
#define MENU_11_POINT_CONTANT_H                 (194)


#define MENU_11_POINT_GAIN_COL_X                (0)
#define MENU_11_POINT_GAIN_COL_Y                (0)
#define MENU_11_POINT_GAIN_COL_W                (120)
#define MENU_11_POINT_GAIN_COL_H                (46)

#define MENU_11_POINT_GAIN_UINT_X               (MENU_11_POINT_GAIN_COL_X)
#define MENU_11_POINT_GAIN_UINT_Y               (MENU_11_POINT_GAIN_COL_Y + MENU_11_POINT_GAIN_COL_H )
#define MENU_11_POINT_GAIN_UINT_W               (MENU_11_POINT_GAIN_COL_W)
#define MENU_11_POINT_GAIN_UINT_H               (MENU_11_POINT_GAIN_COL_H)


#define MENU_FLAT_TEST_PATTERN_BTN_W            (120*3)
#define MENU_FLAT_TEST_PATTERN_BTN_H            (46)
#define MENU_FLAT_TEST_PATTERN_BTN_X            ((MENU_COLOR_TUNER_FRAME_W - MENU_FLAT_TEST_PATTERN_BTN_W)/2)
#define MENU_FLAT_TEST_PATTERN_BTN_Y            (50)//(MENU_COLOR_TUNER_GRID_Y+MENU_FLAT_TEST_PATTERN_BTN_H)

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


typedef struct _WHITE_BALANCE_TUNER
{
    UINT8       ui1_hlt_row;
    UINT8       ui1_hlt_col;
    HANDLE_T    ah_unit_col[4];
    HANDLE_T    ah_unit_row[3];
    HANDLE_T    aah_cb_tr[3][4];
    HANDLE_T    h_cnt_frm;
    INT16       ai2_20_point_rgb_values[3][APP_CFG_11_POINT_GAIN_NUM];
    UINT8       ui1_20_point_gain_num;
}WHITE_BALANCE_TUNER;



static HANDLE_T             h_timer_tts;
static UINT32               ui4_g_ver=0;
static UINT32               ui4_g_ver_tmp=0;
static UTF16_T              w2s_g_tts[96] = {0};

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/


/*White Balance Tuner*/
static UINT16 aui2_str_dims[] =
{
    0,//IRE
    MLM_MENU_KEY_COLOR_TUNER_COL_RED,
    MLM_MENU_KEY_COLOR_TUNER_COL_GREEN,
    MLM_MENU_KEY_COLOR_TUNER_COL_BLUE,
};

static UINT16 aui2_str_ages[] =
{
    0,//IRE
    MLM_MENU_KEY_COLOR_TUENR_ROW_OFFSET,
    MLM_MENU_KEY_COLOR_TUNER_ROW_GAIN
};


static HANDLE_T    h_base_fram;
static HANDLE_T    ah_bar;
static HANDLE_T    h_warning_info;

static BOOL b_page_show = FALSE;

static BOOL b_warning_show = FALSE;

static HANDLE_T     h_left_arrow = NULL_HANDLE;
static HANDLE_T     h_right_arrow = NULL_HANDLE;

MENU_PAGE_FCT_TBL_T t_g_menu_common_page_white_balance_tuner;

WHITE_BALANCE_TUNER   t_white_balance_tuner;

static INT16          i2_acfg_gain_num = 0;
static INT16          i2_acfg_gain_r = 0;
static INT16          i2_acfg_gain_g = 0;
static INT16          i2_acfg_gain_b = 0;

static UINT32         ui4_dynamic_address = 0;

#define MI_MM_NAME_MODEL_1            "MI_PARSE_MM_IDX_0"
#define MI_MM_PATTERN_HANDLE          "MI_MM_HANDLE_IDX_1"
#define MI_MM_DISP_HANDLE             "MI_DISP_HD0"


/*-----------------------------------------------------------------------------
                    Global function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    Private function declarations
 ----------------------------------------------------------------------------*/
static INT32 _white_balance_tuner_row_ire_set_values(VOID);
static INT32 _white_balance_page_get_row_ire_unit_values(VOID);
static INT32 _white_balance_tuner_update_unit_value(BOOL b_repaint);
static INT32 _test_pattern_left_right_arrow_show(BOOL b_show);
static INT32 _test_pattern_left_right_arrow_create(VOID);
static INT32 _test_pattern_warning_info_visiable(BOOL b_visiable, BOOL b_repaint);



/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static VOID _white_balance_tuner_tts_play_hdlr (
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

static VOID _white_balance_tuner_tts_play_cb(
    HANDLE_T                  h_timer,
    VOID*                     pv_ver)
{
    menu_async_invoke(_white_balance_tuner_tts_play_hdlr, pv_ver, sizeof(UINT32), FALSE);
}

static INT32 _white_balance_tuner_tts_play(VOID)
{
    INT32  i4_ret  = 0 ;
    i4_ret = c_timer_stop(h_timer_tts);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_ver = ui4_g_ver + 1 ;
    ui4_g_ver_tmp   = ui4_g_ver;

    i4_ret = c_timer_start(h_timer_tts,
                           100,
                           X_TIMER_FLAG_ONCE,
                           _white_balance_tuner_tts_play_cb,
                           (VOID*)&ui4_g_ver_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}




INT32 a_menu_11_point_gain_update(VOID)
{
    return a_cfg_cust_drv_set_20_p_wb();
}

static void _white_balance_tuner_page_redraw_IRE_data(void)
{
    INT16  i2_vid_eq_val = 0;
    CHAR        s_buf[32]={0};
    UTF16_T     ws_buf[32]={0};
    UINT8 u8DrawCol = 0;
    INT32       i4_ret = MENUR_OK;

    for( u8DrawCol = 1; u8DrawCol <= 3; u8DrawCol += 1 )
    {
        i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[u8DrawCol-1][t_white_balance_tuner.ui1_20_point_gain_num];
        c_sprintf(s_buf, "%d",i2_vid_eq_val);
        c_uc_ps_to_w2s(s_buf, ws_buf, 31);

        WB_T_DEBUG_UI( DBG_LOG_PRINT(("[WB_T] SetText:row=%d, col=%d\n", 0, u8DrawCol )); );
        i4_ret = c_wgl_do_cmd(t_white_balance_tuner.aah_cb_tr[0][u8DrawCol],
                       WGL_CMD_BTN_SET_TEXT,
                       WGL_PACK (ws_buf),
                       WGL_PACK (c_uc_w2s_strlen (ws_buf)));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(t_white_balance_tuner.aah_cb_tr[0][u8DrawCol],
                               NULL,
                               TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

/*----------------------------------------------------------------------------
 * Name: _white_balance_tuner_page_unit_proc_fct
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
 static INT32 _white_balance_tuner_page_unit_proc_fct(VOID*  pv_param1,UINT8 ui1_hlt_row, INT8 ui1_hlt_col)
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


    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T] row=%d, col=%d\n", ui1_hlt_row, ui1_hlt_col )); );

    if(ui1_hlt_row == ROW_IRE)
    {
        if(ui1_hlt_col == COL_IRE)
        {
            i2_min = 0;
            i2_max = 19; //20 piont white balance
            i2_vid_eq_val = t_white_balance_tuner.ui1_20_point_gain_num;
        }
        else
        {
            i2_min = -50;
            i2_max = 50;
            i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[ui1_hlt_col-1][t_white_balance_tuner.ui1_20_point_gain_num];
        }

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

        WB_T_DEBUG_VAL( DBG_LOG_PRINT(("[WB_T] i2_vid_eq_val=%d\n", i2_vid_eq_val )); );

        if(ui1_hlt_col == COL_IRE)
        {
            t_white_balance_tuner.ui1_20_point_gain_num = i2_vid_eq_val;
            WB_T_DEBUG_VAL( DBG_LOG_PRINT(("[WB_T] t_white_balance_tuner.ui1_20_point_gain_num=%d\n", t_white_balance_tuner.ui1_20_point_gain_num )); );
        }
        else
        {
            // Check array range ...
            if( t_white_balance_tuner.ui1_20_point_gain_num >= 20 )
            {
                // Error
                WB_T_DEBUG_VAL( DBG_LOG_PRINT(("[WB_T][Error] t_white_balance_tuner.ui1_20_point_gain_num=%d\n", t_white_balance_tuner.ui1_20_point_gain_num )); );
                return MENUR_FAIL;
            }

            t_white_balance_tuner.ai2_20_point_rgb_values[ui1_hlt_col-1][t_white_balance_tuner.ui1_20_point_gain_num] = i2_vid_eq_val;
            WB_T_DEBUG_VAL( DBG_LOG_PRINT(("[WB_T] Set rgb[%d][%d]=%d\n", ui1_hlt_col-1, t_white_balance_tuner.ui1_20_point_gain_num, i2_vid_eq_val )); );
        }

        _white_balance_tuner_row_ire_set_values();

        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
        MENU_CHK_FAIL(i4_ret);

        a_cfg_set_clr_temp_chg_status(i2_clr_temp,TRUE);

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


    char bRedrawIreData = 0;

    if(ui1_hlt_row == ROW_IRE && ui1_hlt_col == COL_IRE)
    {
        snprintf(s_buf, 10, "IRE%% %d", ( i2_vid_eq_val +1 ) * 5);
        c_uc_ps_to_w2s(s_buf, ws_buf, 10);
        bRedrawIreData = TRUE;
    }
    else
    {
        c_sprintf(s_buf, "%d",i2_vid_eq_val);
        c_uc_ps_to_w2s(s_buf, ws_buf, 31);
    }

    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T] SetText:row=%d, col=%d\n", ui1_hlt_row, ui1_hlt_col )); );
    i4_ret = c_wgl_do_cmd(t_white_balance_tuner.aah_cb_tr[ui1_hlt_row][ui1_hlt_col],
                           WGL_CMD_BTN_SET_TEXT,
                           WGL_PACK (ws_buf),
                           WGL_PACK (c_uc_w2s_strlen (ws_buf)));
    MENU_LOG_ON_FAIL(i4_ret);

    // if IRE change, need to redraw value ...
    if( bRedrawIreData )
    {
        _white_balance_tuner_page_redraw_IRE_data();
    }

    c_memset(s_buf, 0, sizeof(s_buf));
    if(i2_vid_eq_val >= 0)
    {
        if(ui1_hlt_row == ROW_IRE && ui1_hlt_col == COL_IRE)
        {
            snprintf(s_buf, 10, "IRE%% %d", ( i2_vid_eq_val +1 ) * 5);
            c_uc_ps_to_w2s(s_buf, ws_buf, 10);
        }
        else
        {
            c_sprintf(s_buf, "%d",i2_vid_eq_val);

        }
    }
    else
    {
        c_sprintf(s_buf, "minus %d",ABS(i2_vid_eq_val));
    }

    c_uc_ps_to_w2s(s_buf, ws_buf, 31);

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,ws_buf);
    _white_balance_tuner_tts_play();

    i4_ret = c_wgl_repaint(t_white_balance_tuner.aah_cb_tr[ui1_hlt_row][ui1_hlt_col],
                           NULL,
                           TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pic_energy_change_sepcial_page_set_status(TRUE);

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
static INT32 _create_row_title(HANDLE_T  h_parent,
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
    t_clr_txt.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_txt.u_color_data.t_extend.t_enable                = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_disable               = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_highlight             = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_highlight_inactive    = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_push                  = t_g_menu_color_black;
    t_clr_txt.u_color_data.t_extend.t_push_unhighlight      = t_g_menu_color_black;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _white_balance_tuner_update_unit_value
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
static INT32 _white_balance_tuner_update_unit_value(BOOL b_repaint)
{
    UINT8       ui1_row = 0;
    UINT8       ui1_colume = 0;
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16       i2_vid_eq_val = 0;
    CHAR        s_buf[APP_VALUE_LEN]={0};
    UTF16_T     ws_buf[APP_VALUE_LEN]={0};


    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T] b_repaint:%d\n", b_repaint )); );


    // Get ire data from acfg.(Only need one time)
    _white_balance_page_get_row_ire_unit_values();//row = IRE

    for (ui1_row=ROW_IRE; ui1_row<=ROW_GAIN; ui1_row++)
    {
        for (ui1_colume=COL_IRE; ui1_colume<=COL_BLUE; ui1_colume++)
        {
            if(ui1_row != ROW_IRE && ui1_colume == COL_IRE)
            {
                continue;
            }

            if(ui1_row == ROW_IRE)
            {
                //_white_balance_page_get_row_ire_unit_values();//row = IRE

                if(ui1_colume == COL_IRE)
                {
                    i2_vid_eq_val = (t_white_balance_tuner.ui1_20_point_gain_num + 1) * 5;
                    c_sprintf(s_buf, "IRE%% %d",i2_vid_eq_val);
                }
                else if(ui1_colume == COL_RED)
                {
                    i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[COL_RED  -1][t_white_balance_tuner.ui1_20_point_gain_num];
                    c_sprintf(s_buf, "%d",i2_vid_eq_val);
                }
                else if(ui1_colume == COL_GREEN)
                {
                    i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[COL_GREEN-1][t_white_balance_tuner.ui1_20_point_gain_num];
                    c_sprintf(s_buf, "%d",i2_vid_eq_val);
                }
                else if(ui1_colume == COL_BLUE)
                {
                    i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[COL_BLUE -1][t_white_balance_tuner.ui1_20_point_gain_num];
                    c_sprintf(s_buf, "%d",i2_vid_eq_val);
                }

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

            WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T] SetText:row=%d, col=%d\n", ui1_row, ui1_colume )); );

            c_wgl_do_cmd(t_white_balance_tuner.aah_cb_tr[ui1_row][ui1_colume],
                               WGL_CMD_BTN_SET_TEXT,
                               WGL_PACK (ws_buf),
                               WGL_PACK (c_uc_w2s_strlen (ws_buf)));
        }
    }

    if (b_repaint)
    {
        MENU_LOG_ON_FAIL(c_wgl_repaint(t_white_balance_tuner.h_cnt_frm, NULL, TRUE));
    }

    return MENUR_OK;
}


INT32 a_menu_11_point_page_update_txt(BOOL b_repaint)
{
    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T] b_repaint:%d, Call _white_balance_tuner_update_unit_value(%d)\n", b_repaint, b_repaint )); );

    return _white_balance_tuner_update_unit_value(b_repaint);
}

void _white_balance_page_dump_20_point_rgb_values(void)
{
    UINT8       ui1_i = 0, ui1_j = 0;
    char acDebugLog[256] = {0};

    DBG_LOG_PRINT(("[WB_T] Dump ai2_20_point_rgb_values[3][%d]\n", APP_CFG_11_POINT_GAIN_NUM ));

    for (ui1_i = COL_IRE; ui1_i < COL_BLUE; ui1_i++)
    {
        DBG_LOG_PRINT(("ai2_20_point_rgb_values[ui1_i]=\n", ui1_i ));
        memset( acDebugLog, 0, sizeof(acDebugLog) );
        for (ui1_j = 0; ui1_j < APP_CFG_11_POINT_GAIN_NUM; ui1_j++)
        {
            c_sprintf(acDebugLog + strlen(acDebugLog), " %3d", t_white_balance_tuner.ai2_20_point_rgb_values[ui1_i][ui1_j]);
        }
        DBG_LOG_PRINT(("%s\n", acDebugLog ));
    }

    DBG_LOG_PRINT((" ui1_20_point_gain_num=%d\n", t_white_balance_tuner.ui1_20_point_gain_num ));
}

static INT32 _white_balance_page_get_row_ire_unit_values(VOID)
{
    UINT8       ui1_i = 0, ui1_j = 0;
    INT16       i2_gain_num = 0;

    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T]\n" )); );

    /* get acfg values to t_white_balance_tuner.ai2_20_point_rgb_values */
    t_white_balance_tuner.ui1_20_point_gain_num = 0;

    for (ui1_i = COL_IRE; ui1_i < COL_BLUE; ui1_i++)
    {
        for (ui1_j = 0; ui1_j < APP_CFG_11_POINT_GAIN_NUM; ui1_j++)
        {
            t_white_balance_tuner.ai2_20_point_rgb_values[ui1_i][ui1_j] = 0;
        }
    }

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), &i2_gain_num);
    t_white_balance_tuner.ui1_20_point_gain_num = i2_gain_num;

    /*get all 11 point values*/

    /* layout by src*clr_temp*11_point_gain, and will use the global one*/
    UINT16                      ui2_ipt = a_acfg_cust_get_dynamic_range();
    INT16                       i2_clr_tmp = 0;
    UINT16                      ui2_elem_idx;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_tmp);
    for(ui1_j = 0; ui1_j < APP_CFG_11_POINT_GAIN_NUM; ui1_j++)
    {
        ui2_elem_idx = ui2_ipt * ACFG_CLR_TEMP_NUM*APP_CFG_11_POINT_GAIN_NUM + i2_clr_tmp*APP_CFG_11_POINT_GAIN_NUM + ui1_j;
        MENU_LOG_ON_FAIL(acfg_get_int16_by_idx(IDX_11_POINT_GAIN_RED,  ui2_elem_idx, &t_white_balance_tuner.ai2_20_point_rgb_values[COL_RED  -1][ui1_j]));
        MENU_LOG_ON_FAIL(acfg_get_int16_by_idx(IDX_11_POINT_GAIN_GREEN,ui2_elem_idx, &t_white_balance_tuner.ai2_20_point_rgb_values[COL_GREEN-1][ui1_j]));
        MENU_LOG_ON_FAIL(acfg_get_int16_by_idx(IDX_11_POINT_GAIN_BLUE, ui2_elem_idx, &t_white_balance_tuner.ai2_20_point_rgb_values[COL_BLUE -1][ui1_j]));
    }


    // dump all data...
    WB_T_DEBUG_VAL( _white_balance_page_dump_20_point_rgb_values(); );


    return MENUR_OK;
}

static INT32 _white_balance_tuner_row_ire_set_values(VOID)
{
    INT16       i2_gain_num = 0;
    INT16       i2_gain_r = 0;
    INT16       i2_gain_g = 0;
    INT16       i2_gain_b = 0;
    INT16       i2_tmp_val = 0;


    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T] \n" )); );


    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_tmp_val);

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN), t_white_balance_tuner.ui1_20_point_gain_num);

#if 0
    if(t_white_balance_tuner.ui1_hlt_row == ROW_IRE)
    {
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_RED),   &t_white_balance_tuner.ai2_20_point_rgb_values[COL_RED  -1][t_white_balance_tuner.ui1_20_point_gain_num]);
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_GREEN), &t_white_balance_tuner.ai2_20_point_rgb_values[COL_GREEN-1][t_white_balance_tuner.ui1_20_point_gain_num]);
        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_BLUE),  &t_white_balance_tuner.ai2_20_point_rgb_values[COL_BLUE -1][t_white_balance_tuner.ui1_20_point_gain_num]);
    }
#endif

    /* set acfg values */
    i2_gain_num = t_white_balance_tuner.ui1_20_point_gain_num;
    i2_gain_r   = t_white_balance_tuner.ai2_20_point_rgb_values[COL_RED  -1][i2_gain_num];
    i2_gain_g   = t_white_balance_tuner.ai2_20_point_rgb_values[COL_GREEN-1][i2_gain_num];
    i2_gain_b   = t_white_balance_tuner.ai2_20_point_rgb_values[COL_BLUE -1][i2_gain_num];

    if (i2_acfg_gain_num != i2_gain_num
        || i2_acfg_gain_r != i2_gain_r
        || i2_acfg_gain_g != i2_gain_g
        || i2_acfg_gain_b != i2_gain_b)
    {
        i2_acfg_gain_num = i2_gain_num;
        i2_acfg_gain_r   = i2_gain_r;
        i2_acfg_gain_g   = i2_gain_g;
        i2_acfg_gain_b   = i2_gain_b;

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_RED),   i2_gain_r);
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_GREEN), i2_gain_g);
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN_BLUE),  i2_gain_b);

    }

    /* update */
    //a_cfg_update_20_point((VOID*)i4_GammactrlPts, sizeof(i4_GammactrlPts));
    a_cfg_cust_drv_set_20_p_wb();

    menu_pic_energy_change_sepcial_page_set_status(TRUE);
    return MENUR_OK;
}




/*----------------------------------------------------------------------------
 * Name: _white_balance_page_curnt_unit_tts_play
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
static INT32 _white_balance_page_curnt_unit_tts_play(UINT8 ui1_hlt_row, INT8 ui1_hlt_col)
{
    UINT16      ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R);
    INT16       i2_vid_gain_val = 0;
    INT16       i2_vid_eq_val = 0;
    CHAR        s_buf_ire[32] ={0};
    CHAR        s_buf[32]   ={0};
    UTF16_T     ws_buf[32]={0};
    UINT16      ui2_msgid_title_v = 0;
    UINT16      ui2_msgid_title_h = 0;
    UTF16_T     w2s_str_1[256] = {0};
    UTF16_T     w2s_str[256] = {0};

    if(ui1_hlt_row == ROW_IRE)
    {
        if(ui1_hlt_col == COL_RED)
        {
            i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[COL_RED  -1][t_white_balance_tuner.ui1_20_point_gain_num];
        }
        else if(ui1_hlt_col == COL_GREEN)
        {
            i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[COL_GREEN-1][t_white_balance_tuner.ui1_20_point_gain_num];
        }
        else if(ui1_hlt_col == COL_BLUE)
        {
            i2_vid_eq_val = t_white_balance_tuner.ai2_20_point_rgb_values[COL_BLUE -1][t_white_balance_tuner.ui1_20_point_gain_num];
        }
        //c_sprintf(s_buf, "%s %d",i2_vid_eq_val < 0 ? "dash":"" ,ABS(i2_vid_eq_val));

        i2_vid_gain_val = t_white_balance_tuner.ui1_20_point_gain_num;
        snprintf(s_buf_ire, 10, "IRE%% %d", ( i2_vid_gain_val +1 ) * 5);
        c_uc_ps_to_w2s(s_buf_ire, ws_buf, 10);
        c_uc_w2s_strcat(w2s_str, ws_buf);

        if(ui1_hlt_col >= COL_RED && ui1_hlt_col <= COL_BLUE)
        {
            c_uc_w2s_strcat(w2s_str, _TEXT("."));

            if(i2_vid_eq_val >= 0)
            {
                c_sprintf(s_buf, "%d",i2_vid_eq_val);
            }
            else
            {
                c_sprintf(s_buf, "minus %d",ABS(i2_vid_eq_val));
            }


            ui2_msgid_title_h = aui2_str_dims[ui1_hlt_col];
            c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(ui2_msgid_title_h));
            c_uc_w2s_strcat(w2s_str, _TEXT("."));

            c_memset(ws_buf, 0, sizeof(ws_buf));
            c_uc_ps_to_w2s(s_buf, ws_buf, c_strlen(s_buf));
            c_uc_w2s_strcat(w2s_str, ws_buf);
        }

    }
    else if(ui1_hlt_row == ROW_OFFSET || ui1_hlt_row == ROW_GAIN)
    {
        if(ui1_hlt_row == ROW_OFFSET)
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
        else
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

        if(i2_vid_eq_val >= 0)
        {
            c_sprintf(s_buf, "%d",i2_vid_eq_val);
        }
        else
        {
            c_sprintf(s_buf, "minus %d",ABS(i2_vid_eq_val));
        }

        ui2_msgid_title_v = aui2_str_ages[ui1_hlt_row];
        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(ui2_msgid_title_v));
        c_uc_w2s_strcat(w2s_str, _TEXT("."));

        ui2_msgid_title_h = aui2_str_dims[ui1_hlt_col];
        c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(ui2_msgid_title_h));
        c_uc_w2s_strcat(w2s_str, _TEXT("."));

        c_memset(ws_buf, 0, sizeof(ws_buf));
        c_uc_ps_to_w2s(s_buf, ws_buf, c_strlen(s_buf));
        c_uc_w2s_strcat(w2s_str, ws_buf);

    }


    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,w2s_str);
    _white_balance_tuner_tts_play();

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _white_balance_page_unit_proc_fct
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
 static INT32 _white_balance_page_unit_proc_fct(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    INT32           i4_ret = MENUR_OK;
    UINT32          ui4_keycode = (UINT32)pv_param1;
    BOOL            b_btn_pushed = FALSE;
    INT16           i2_tmp_val = 0;
    INT16           i2_clr_temp = 0;

    if (ui4_msg == WGL_MSG_GET_FOCUS)
    {
        MENU_LOG_ON_FAIL(c_wgl_float(h_widget, TRUE, FALSE));
    }
    else if (ui4_msg == WGL_MSG_LOSE_FOCUS)
    {
        MENU_LOG_ON_FAIL(c_wgl_float(h_widget, FALSE, FALSE));
    }
    else if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                            WGL_CMD_BTN_GET_PUSHED,
                            WGL_PACK(&b_btn_pushed),
                            WGL_PACK(NULL));
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
                i4_ret = c_wgl_do_cmd(h_widget,
                                        WGL_CMD_BTN_SET_PUSHED,
                                        WGL_PACK(FALSE),
                                        WGL_PACK(NULL));
                MENU_LOG_ON_FAIL(i4_ret);

                if(b_btn_pushed == FALSE)
                {
                    if((t_white_balance_tuner.ui1_hlt_row > ROW_IRE) && (t_white_balance_tuner.ui1_hlt_row <= ROW_GAIN))
                    {
                        t_white_balance_tuner.ui1_hlt_row--;
                        c_wgl_set_focus(t_white_balance_tuner.aah_cb_tr[t_white_balance_tuner.ui1_hlt_row][t_white_balance_tuner.ui1_hlt_col],TRUE);
                        _white_balance_page_curnt_unit_tts_play(t_white_balance_tuner.ui1_hlt_row,t_white_balance_tuner.ui1_hlt_col);
                        break;
                    }
                    else if(t_white_balance_tuner.ui1_hlt_row == ROW_IRE)
                    {
                        c_wgl_set_focus(ah_bar,TRUE);
                        c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
                        c_uc_w2s_strcpy(w2s_g_tts,MENU_TTS_TEXT(MLM_MENU_KEY_VID_WB_TUNER));
                        _white_balance_tuner_tts_play();
                    }
                }
                break;

            case BTN_CURSOR_DOWN:
                if(b_btn_pushed == FALSE)
                {
                    if((t_white_balance_tuner.ui1_hlt_col != COL_IRE) && (t_white_balance_tuner.ui1_hlt_row >= ROW_IRE) && (t_white_balance_tuner.ui1_hlt_row <ROW_GAIN))
                    {
                        t_white_balance_tuner.ui1_hlt_row++;
                        c_wgl_set_focus(t_white_balance_tuner.aah_cb_tr[t_white_balance_tuner.ui1_hlt_row][t_white_balance_tuner.ui1_hlt_col],TRUE);
                        _white_balance_page_curnt_unit_tts_play(t_white_balance_tuner.ui1_hlt_row,t_white_balance_tuner.ui1_hlt_col);
                        break;
                    }
                    else if(t_white_balance_tuner.ui1_hlt_col == COL_IRE && t_white_balance_tuner.ui1_hlt_row == ROW_IRE)
                    {
                        c_wgl_set_focus(t_white_balance_tuner.aah_cb_tr[t_white_balance_tuner.ui1_hlt_row][t_white_balance_tuner.ui1_hlt_col],TRUE);
                        _white_balance_page_curnt_unit_tts_play(t_white_balance_tuner.ui1_hlt_row,t_white_balance_tuner.ui1_hlt_col);
                        break;
                    }
                }

                break;

            case BTN_CURSOR_LEFT:
            {
                if (!b_btn_pushed)
                {
                    if((t_white_balance_tuner.ui1_hlt_row == ROW_IRE) && ((t_white_balance_tuner.ui1_hlt_col <= COL_IRE)||(t_white_balance_tuner.ui1_hlt_col >COL_BLUE)))
                    {
                        break;
                    }
                    if((t_white_balance_tuner.ui1_hlt_row != ROW_IRE) && ((t_white_balance_tuner.ui1_hlt_col <= COL_RED)||(t_white_balance_tuner.ui1_hlt_col >COL_BLUE)))
                    {
                        break;
                    }
                    t_white_balance_tuner.ui1_hlt_col--;
                    c_wgl_set_focus(t_white_balance_tuner.aah_cb_tr[t_white_balance_tuner.ui1_hlt_row][t_white_balance_tuner.ui1_hlt_col],TRUE);

                    _white_balance_page_curnt_unit_tts_play(t_white_balance_tuner.ui1_hlt_row,t_white_balance_tuner.ui1_hlt_col);
                }
                else
                {

                    i4_ret =  _white_balance_tuner_page_unit_proc_fct(pv_param1,
                                                                      t_white_balance_tuner.ui1_hlt_row,
                                                                      t_white_balance_tuner.ui1_hlt_col);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                break;
            }
            case BTN_CURSOR_RIGHT:
            {
                if (!b_btn_pushed)
                {
                    if((t_white_balance_tuner.ui1_hlt_row == ROW_IRE) && ((t_white_balance_tuner.ui1_hlt_col < COL_IRE)||(t_white_balance_tuner.ui1_hlt_col >=COL_BLUE)))
                    {
                        break;
                    }
                    if((t_white_balance_tuner.ui1_hlt_row != ROW_IRE) && ((t_white_balance_tuner.ui1_hlt_col < COL_RED)||(t_white_balance_tuner.ui1_hlt_col >=COL_BLUE)))
                    {
                        break;
                    }
                    t_white_balance_tuner.ui1_hlt_col++;
                    c_wgl_set_focus(t_white_balance_tuner.aah_cb_tr[t_white_balance_tuner.ui1_hlt_row][t_white_balance_tuner.ui1_hlt_col],TRUE);
                    _white_balance_page_curnt_unit_tts_play(t_white_balance_tuner.ui1_hlt_row,t_white_balance_tuner.ui1_hlt_col);
                }
                else
                {

                    i4_ret =  _white_balance_tuner_page_unit_proc_fct(pv_param1,
                                                                      t_white_balance_tuner.ui1_hlt_row,
                                                                      t_white_balance_tuner.ui1_hlt_col);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                break;

            }

                break;
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
                break;
            case BTN_SELECT:
                break;
            default:
                break;
        }


    }

    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

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
static INT32 _create_unit(INT32 i4_x, INT32 i4_y, HANDLE_T*    ph_widget)
{

    WGL_IMG_INFO_T              t_img_info;
    INT32                       i4_ret = MENUR_OK;
    GL_RECT_T                   t_rect;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                 MENU_11_POINT_GAIN_UINT_X  + 1 +(MENU_11_POINT_GAIN_COL_W + RED_ON_OFF_BTN_LINE)*i4_y,
                 MENU_11_POINT_GAIN_UINT_Y  + 4 +(MENU_11_POINT_GAIN_COL_H + RED_ON_OFF_BTN_LINE)*i4_x,
                 MENU_11_POINT_GAIN_UINT_W,
                 MENU_11_POINT_GAIN_UINT_H );

    i4_ret = c_wgl_create_widget(t_white_balance_tuner.h_cnt_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _white_balance_page_unit_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_BTN_CHECKBOX),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set LB colors */
    t_lb_color.t_normal             = t_g_menu_color_bk0_txt_hlt;
    t_lb_color.t_disable            = t_g_menu_color_bk0_txt_hlt;
    t_lb_color.t_highlight          = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus  = t_g_menu_color_white;
    t_lb_color.t_pushed             = t_g_menu_color_white;
    t_lb_color.t_selected           = t_g_menu_color_white;
    t_lb_color.t_selected_disable   = t_g_menu_color_white;
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
    t_img_info.e_type                                      = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable               = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_enable                = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight             = h_g_menu_ColorTuner_digit_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive    = h_g_menu_ColorTuner_digit_hlt;
    t_img_info.u_img_data.t_extend.t_push                  = h_g_menu_ColorTuner_digit_hlt_arrows;
    t_img_info.u_img_data.t_extend.t_push_unhighlight      = h_g_menu_ColorTuner_digit_hlt_arrows;

    i4_ret =  c_wgl_do_cmd(*ph_widget,
                                 WGL_CMD_GL_SET_IMAGE,
                                 WGL_PACK(WGL_IMG_BK),
                                 WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _11_point_gain_page_create
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
static INT32 _white_balance_tuner_page_create(VOID)
{
    INT32   i4_ret;
    GL_RECT_T   t_rect = {0};
    INT8        i1_index = 0;
    WGL_IMG_INFO_T  t_img_info;
    INT8 ui1_row = 0;
    INT8 ui1_col = 0;

    a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);

    DBG_INFO(("[TEST][%s]:[%d]ui4_dynamic_address=%d\n",__FILE__,__LINE__,ui4_dynamic_address));

    menu_range_chg_lang(ah_bar, MLM_MENU_KEY_VID_WB_TUNER);

    i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER))));
    MENU_LOG_ON_FAIL(i4_ret);


    SET_RECT_BY_SIZE(&t_rect,
                  MENU_11_POINT_CONTANT_X,
                  MENU_11_POINT_CONTANT_Y,
                  MENU_11_POINT_CONTANT_W,
                  MENU_11_POINT_CONTANT_H);

    i4_ret = c_wgl_create_widget(h_base_fram,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)0,
                                  NULL,
                                  &t_white_balance_tuner.h_cnt_frm);

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set cnt  background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_g_menu_img_WhiteBalanceTuner_grid;
    t_img_info.u_img_data.t_standard.t_highlight    = h_g_menu_img_WhiteBalanceTuner_grid;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_menu_img_WhiteBalanceTuner_grid;

    i4_ret = c_wgl_do_cmd(t_white_balance_tuner.h_cnt_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);




    //col_title     Red      Green     Blue
    for(i1_index = COL_RED; i1_index <= COL_BLUE; i1_index++)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_11_POINT_GAIN_COL_X + (MENU_11_POINT_GAIN_COL_W +RED_ON_OFF_BTN_LINE)* (i1_index),
                         MENU_11_POINT_GAIN_COL_Y,
                         MENU_11_POINT_GAIN_COL_W,
                         MENU_11_POINT_GAIN_COL_H);

        i4_ret = _create_col_title(t_white_balance_tuner.h_cnt_frm,
                                        i1_index,
                                        MENU_TEXT(aui2_str_dims[i1_index]),
                                        &t_white_balance_tuner.ah_unit_col[i1_index],
                                        &t_rect);
        MENU_CHK_FAIL(i4_ret);
    }
    //row_title    offset   gain
    for(i1_index = ROW_OFFSET; i1_index <= ROW_GAIN; i1_index++)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_11_POINT_GAIN_COL_X,
                         MENU_11_POINT_GAIN_COL_Y + (MENU_11_POINT_GAIN_COL_H +RED_ON_OFF_BTN_LINE)* (i1_index+1),
                         MENU_11_POINT_GAIN_COL_W,
                         MENU_11_POINT_GAIN_COL_H);

        i4_ret = _create_row_title(t_white_balance_tuner.h_cnt_frm,
                                        i1_index,
                                        MENU_TEXT(aui2_str_ages[i1_index]),
                                        &t_white_balance_tuner.ah_unit_row[i1_index],
                                        &t_rect);
        MENU_CHK_FAIL(i4_ret);
    }


    // ---------crate row_col unit----------
    // IRE%0   R    G     B
    //         R    G     B
    //         R    G     B
    for (ui1_row = ROW_IRE; ui1_row < ROW_MAX; ui1_row++)
    {
        for(ui1_col = COL_IRE; ui1_col < COL_MAX; ui1_col++)
        {
            if(ui1_row != ROW_IRE && ui1_col == COL_IRE) //row == ROW_IRE    IRE%0 R G B
            {
                continue;
            }
            i4_ret = _create_unit(ui1_row, ui1_col,&t_white_balance_tuner.aah_cb_tr[ui1_row][ui1_col]);
            MENU_CHK_FAIL(i4_ret);
        }

    }



    return MENUR_OK;
}

static INT32 _while_balance_change_lang(VOID)
{
    INT32   i4_ret = MENUR_OK;
    INT8    i1_index = 0;


    WB_T_DEBUG_FLOW( DBG_LOG_PRINT((M_WB_T_TAG " _while_balance_change_lang() -- start\n" )); );

    // change the text of title
    i4_ret = c_wgl_do_cmd(ah_bar,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_VID_WB_TUNER))));
    MENU_CHK_FAIL(i4_ret);


    //col_title     Red      Green     Blue
    for(i1_index = COL_RED; i1_index <= COL_BLUE; i1_index++)
    {
        i4_ret = c_wgl_do_cmd(t_white_balance_tuner.ah_unit_col[i1_index],
                            WGL_CMD_TEXT_SET_TEXT,
                            MENU_TEXT(aui2_str_dims[i1_index]),
                            (VOID*)c_uc_w2s_strlen(MENU_TEXT(aui2_str_dims[i1_index])));
         MENU_CHK_FAIL(i4_ret);
    }

    // Change the text of Offset/Gain...
    //row_title    offset   gain
    for(i1_index = ROW_OFFSET; i1_index <= ROW_GAIN; i1_index++)
    {
        i4_ret = c_wgl_do_cmd(t_white_balance_tuner.ah_unit_row[i1_index],
                             WGL_CMD_TEXT_SET_TEXT,
                             MENU_TEXT(aui2_str_ages[i1_index]),
                             (VOID*)c_uc_w2s_strlen(MENU_TEXT(aui2_str_ages[i1_index])));
        MENU_CHK_FAIL(i4_ret);
    }

    WB_T_DEBUG_FLOW( DBG_LOG_PRINT((M_WB_T_TAG " _while_balance_change_lang() -- end\n" )); );

    return i4_ret;
}

////////////////////////////////////////////////////////////////////////////////////////

static INT32 _test_pattern_set_title_font_size(BOOL b_change)
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
    GL_RECT_T t_rect;
    UINT16  ui2_id      = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED);
    INT16  i2ROnOff     = 0;
    UTF16_T w2s_str[256]= {0};


    switch (ui4_msg)
    {
        case WGL_MSG_LOSE_FOCUS:
            break;
        case WGL_MSG_GET_FOCUS:
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
                     _test_pattern_set_title_font_size(FALSE);

                    t_white_balance_tuner.ui1_hlt_row = ROW_IRE;
                    t_white_balance_tuner.ui1_hlt_col = COL_IRE;
                    c_wgl_set_focus(t_white_balance_tuner.aah_cb_tr[ROW_IRE][COL_IRE],TRUE);
                    _white_balance_page_curnt_unit_tts_play(t_white_balance_tuner.ui1_hlt_row,t_white_balance_tuner.ui1_hlt_col);

                    break;
                case BTN_CURSOR_LEFT:
                    break;
                case BTN_CURSOR_RIGHT:
                    break;
                case BTN_SELECT:
                    break;
                case BTN_RETURN:
                     _test_pattern_set_title_font_size(FALSE);
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

    pw2s_str = MENU_TTS_TEXT(MLM_MENU_KEY_VID_WB_TUNER);

    c_memset(w2s_g_tts, 0, sizeof(w2s_g_tts));
    c_uc_w2s_strcpy(w2s_g_tts,pw2s_str);
    _white_balance_tuner_tts_play();

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

    i4_ret = _white_balance_tuner_page_create();
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

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32   i4_ret = 0;
    UINT16  ui2_val = 0;


    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T]\n" )); );

#ifdef VIEWPORT_SUPPORT
    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_WIDE_MODE);
    a_cfg_update_viewport ();
#endif

    i4_ret = menu_main_set_visibility(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    WB_T_DEBUG_FLOW( DBG_LOG_PRINT(("[WB_T] Call _white_balance_tuner_update_unit_value(FALSE)\n")); );
    _white_balance_tuner_update_unit_value(FALSE);

    t_white_balance_tuner.ui1_hlt_row = ROW_IRE;
    t_white_balance_tuner.ui1_hlt_col = COL_IRE;

    i4_ret = c_wgl_set_visibility(h_base_fram,WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_white_balance_tuner.h_cnt_frm,WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);


    // Redraw text for multi lang...
    i4_ret = _while_balance_change_lang();
    MENU_LOG_ON_FAIL(i4_ret);


    _title_curnt_tts_play();

    i4_ret = c_wgl_set_visibility(ah_bar, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_base_fram, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    _test_pattern_warning_info_visiable(FALSE, FALSE);
    //Fix Coverity ID : 4524482 Unchecked return value
    i4_ret = c_wgl_insert(h_base_fram, NULL_HANDLE, WGL_INSERT_TOPMOST, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
    c_wgl_repaint(h_base_fram,NULL,TRUE);

    b_page_show = TRUE;
    return MENUR_OK;
}
static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32   i4_ret = 0;
    UINT8   ui1_i = 0;
    UINT8   ui1_j = 0;

    b_page_show = FALSE;


    i4_ret = c_wgl_do_cmd(t_white_balance_tuner.aah_cb_tr[t_white_balance_tuner.ui1_hlt_row][t_white_balance_tuner.ui1_hlt_col],
                            WGL_CMD_BTN_SET_PUSHED,
                            WGL_PACK(FALSE),
                            WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);


    for (ui1_i = ROW_IRE; ui1_i < ROW_MAX; ui1_i++)
    {
        for(ui1_j = COL_IRE; ui1_j < COL_MAX; ui1_j++)
        {
            if(ui1_i != ROW_IRE && ui1_j == COL_IRE)
            {
                continue;
            }
            c_wgl_do_cmd(t_white_balance_tuner.aah_cb_tr[ui1_i][ui1_j],
                        WGL_CMD_BTN_SET_PUSHED,
                        WGL_PACK(FALSE),
                        WGL_PACK(NULL));
        }

    }

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
    return MENUR_OK;
}



INT32 menu_common_page_white_balance_tuner_init(VOID)
{
    INT32       i4_ret = MENUR_OK;
    t_g_menu_common_page_white_balance_tuner.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_white_balance_tuner.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_white_balance_tuner.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_white_balance_tuner.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_white_balance_tuner.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_white_balance_tuner.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_white_balance_tuner.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}




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
 * $RCSfile: menu_page_auto_scan2.c,v $
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
#include "u_sb_ntsc_eng.h"
#include "u_sb_cqam_eng.h"
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
#include "am/a_am.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_atsc/menu_atsc.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef TIME_MEASUREMENT
#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#endif
#include "nav/input_src/input_src.h"
#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#endif

/* channel scan status */
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#ifdef LINUX_AUTO_TEST
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

#define atsc_scan_file  "/tmp/autotest/test_atsc_auto_scan_with_signal_ok"
#define cable_scan_file  "/tmp/autotest/test_cable_auto_scan_with_signal_ok"
#endif

#include "nav/tuner_setup/a_tuner_setup.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "res/app_util/icl/a_icl_custom.h"


#include "menu2/menu_dbg.h"

#ifdef ATSC_AUTO_SCAN2_ENABLE

#if defined(CLI_SUPPORT) || defined(CLI_STRESS_MODE)
    #define __CLI_SUPPORT__
#endif

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#ifndef  ATSC_AUTO_SCAN2_TXT_INFO_X
    #define ATSC_AUTO_SCAN2_TXT_INFO_X      (20)
    #define ATSC_AUTO_SCAN2_TXT_INFO_Y      (1 * GRID_H)
    #define ATSC_AUTO_SCAN2_TXT_INFO_W      (CONTENT_W - 40)
    #define ATSC_AUTO_SCAN2_TXT_INFO_H      (5 * GRID_H - 20)
    #define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_T        (10)
    #define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_B        (10)
    #define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_L        (30)
    #define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_R        (30)
    #define ATSC_AUTO_SCAN2_TXT_TUNER_X     (CONTENT_W / 2)
    #define ATSC_AUTO_SCAN2_TXT_TUNER_Y     (1  * GRID_H + 10)
    #define ATSC_AUTO_SCAN2_TXT_TUNER_W     (CONTENT_W - ATSC_AUTO_SCAN2_TXT_TUNER_X - 50)
    #define ATSC_AUTO_SCAN2_TXT_TUNER_H     (1  * GRID_H)
    #define ATSC_AUTO_SCAN2_TXT_TUNER_ALIGN   (WGL_AS_RIGHT_TOP)
    #define ATSC_AUTO_SCAN2_PB_X            (50)
    #define ATSC_AUTO_SCAN2_PB_Y            (GRID_H * 4)
    #define ATSC_AUTO_SCAN2_PB_W            (CONTENT_W - ATSC_AUTO_SCAN2_PB_X * 2)
    #define ATSC_AUTO_SCAN2_PB_H            (GRID_H * 1)
    #define ATSC_AUTO_SCAN2_PB_VAL_W        (80)
    #define ATSC_AUTO_SCAN2_PB_CNT_INSET_T  (8)
    #define ATSC_AUTO_SCAN2_PB_CNT_INSET_B  (7)
    #define ATSC_AUTO_SCAN2_PB_BAR_INSET_L  (2)
    #define ATSC_AUTO_SCAN2_PB_BAR_INSET_R  (2)
    #define ATSC_AUTO_SCAN2_PB_BAR_INSET_T  (2)
    #define ATSC_AUTO_SCAN2_PB_BAR_INSET_B  (2)
#endif

#define _SB_VNET_CUST_CH_TOUCHED    (SB_VNET_USER_INDEX_BGN+1)    /* FIXME_MIN */

#define _CH_LST_X                   0
#define _CH_LST_Y                   (5 * GRID_H)
#define _CH_LST_W                   (CONTENT_W)
#define _CH_LST_H                   (5 * GRID_H)

#define _CH_LST_COL0_W              (55)
#define _CH_LST_COL1_W              (20)
#define _CH_LST_COL2_W              (_CH_LST_W - _CH_LST_COL0_W - _CH_LST_COL1_W - _CH_LST_COL3_W \
                                     - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R)
#define _CH_LST_COL3_W              (35)
#define _CH_LST_ELEM_H              GRID_H
#define _CH_LST_COL0_ALIGN          WGL_AS_LEFT_CENTER
#define _CH_LST_COL1_ALIGN          WGL_AS_LEFT_CENTER
#define _CH_LST_COL2_ALIGN          WGL_AS_LEFT_CENTER
#define _CH_LST_COL3_ALIGN          WGL_AS_RIGHT_CENTER

#define _MAX_CH_NAME_LEN            (48)
#define _MAX_CH_TYPE_LEN            (16)
#define _MAX_CH_NUM_LEN             (8)

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)

#define MAX_CH_NUM          512

/*
#define TMS_NAME_AUTO_SCAN   "~~AUTO_SCAN"
*/

typedef struct _AS_SCAN_NFY_T {
    HANDLE_T    h_builder;
    UINT32      ui4_nfy_reason;
    INT32       i4_nfy_data;
    VOID*       pv_nfy_tag;
} AS_SCAN_NFY_T;

typedef struct _AS_SCAN_INFO_T {
    HANDLE_T    h_builder;
    HANDLE_T    h_san_pb;
    INT32       i4_vir_ch_num;
    INT32       i4_phy_ch_num;
    INT32       i4_phy_ch_ttl;
    BOOL        b_done;         /* if b_done is TRUE, it means that the builder has
                                   sent a SB_REASON_COMPLETE, SB_REASON_CANCEL,
                                   SB_REASON_ABORT message */
} AS_SCAN_INFO_T;

typedef enum {
    _HELP_TIP_TYPE_CH_LST = 0 ,
    _HELP_TIP_TYPE_CANCEL_DONE,
    _HELP_TIP_TYPE_COMPELETE,
    _HELP_TIP_TYPE_HOMEBAR ,
    _HELP_TIP_TYPE_BACKBAR ,
    _HELP_TIP_TYPE_LAST_ENTRY

} _HELP_TIP_TYPE_T ;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_auto_scan2;

static HANDLE_T    h_cnt_frm;
static HANDLE_T    h_txt;
static HANDLE_T    h_channel_found   = NULL_HANDLE;
static HANDLE_T    h_digital_channel = NULL_HANDLE;
static HANDLE_T    h_analog_channel  = NULL_HANDLE;
static HANDLE_T    h_cancel_done     = NULL_HANDLE;
static HANDLE_T    h_timer_ani       = NULL_HANDLE;

static UINT32      ui4_page_id;
static UINT16      ui2_crnt_svl_id;
static BOOL        b_scan            = FALSE;
static BOOL        b_g_menu_is_show_in_scanning            = FALSE;

static AS_SCAN_INFO_T   t_scan_info_atv;
static AS_SCAN_INFO_T   t_scan_info_dtv;

/* clean the SVL, TSL lists before scanning */
static BOOL             b_clean_lists = FALSE;

static BOOL             b_page_leaving = FALSE;

static UINT16 ui2_g_icl_nfy_id = 0;

static MENU_SCAN_PB_ITEM_T t_scan_pb={0};

static INT32 _help_tip_update (
    _HELP_TIP_TYPE_T            e_help_tip_type
    ) ;

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
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_RETURN :
        case BTN_CURSOR_LEFT :
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
            /* focus backbar */
            MENU_CHK_FAIL (menu_set_focus_on_backbar (TRUE)) ;

            /* update help tip */
            MENU_CHK_FAIL (_help_tip_update (_HELP_TIP_TYPE_BACKBAR));
            break ;

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
    if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_RETURN :
        case BTN_CURSOR_LEFT :
        case BTN_SELECT :
            MENU_CHK_FAIL (menu_nav_back ()) ;
            return MENUR_OK ;

        case BTN_CURSOR_DOWN:
            /* in scan processing ,dose no allow browse channel list */
            if (b_scan)
            {
                return WMPR_DONE ;
            }
            MENU_CHK_FAIL (c_wgl_set_focus(h_cancel_done, WGL_SYNC_AUTO_REPAINT));
            MENU_CHK_FAIL (_help_tip_update (_HELP_TIP_TYPE_COMPELETE));
            break ;

        case BTN_CURSOR_UP :
            MENU_CHK_FAIL (menu_set_focus_on_homebar (TRUE)) ;

            /* update help tip */
            MENU_CHK_FAIL (_help_tip_update (_HELP_TIP_TYPE_HOMEBAR));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _help_tip_update
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
static INT32 _help_tip_update (
    _HELP_TIP_TYPE_T            e_help_tip_type
    )
{
    switch (e_help_tip_type)
    {
    case _HELP_TIP_TYPE_CANCEL_DONE:
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_SCAN_BTN_HELP_2));
        break;
    case _HELP_TIP_TYPE_COMPELETE:
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_SCAN_BTN_HELP_1));
        break;
    case _HELP_TIP_TYPE_HOMEBAR :
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
        break ;
    case _HELP_TIP_TYPE_BACKBAR :
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
        break ;
    default :
        MENU_CHK_FAIL (MENUR_INV_ARG) ;
    }

    return MENUR_OK ;
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
static INT32 _scan_info_update(VOID)
{
    INT32   i4_ret = 0;
    INT32   i4_digital_num = 0;
    INT32   i4_analog_num = 0;
    static INT32   i4_digital_num_static = -1;
    static INT32   i4_analog_num_static = -1;
    UINT8   ui1_progress = 0;
    UINT32  ui4_len = 50;
    UTF16_T w2s_str_digital[50] = {0};
    UTF16_T w2s_num_digital[5] = {0};
    UTF16_T w2s_str_analog[50] = {0};
    UTF16_T w2s_num_analog[5] = {0};

    tuner_setup_scan_digital_get_val(&i4_digital_num);
    tuner_setup_scan_analog_get_val(&i4_analog_num);

    if(i4_digital_num == 0 || i4_analog_num == 0)
    {
        i4_digital_num_static = -1;
        i4_analog_num_static = -1;
    }

    if (b_scan)
    {
        /* Append Digital Channels */
        _itoa(w2s_num_digital, i4_digital_num, 4);

        c_uc_w2s_strncpy(w2s_str_digital, MENU_TEXT(MLM_MENU_KEY_SCAN_DIG_CH),
                         ui4_len - c_uc_w2s_strlen(w2s_str_digital));
        c_uc_w2s_strncat(w2s_str_digital, w2s_num_digital,
                         ui4_len - c_uc_w2s_strlen(w2s_str_digital));

        i4_ret = c_wgl_do_cmd(h_digital_channel,
                              WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                              WGL_PACK(w2s_str_digital),
                              WGL_PACK(c_uc_w2s_strlen(w2s_str_digital)));
        MENU_CHK_FAIL(i4_ret);


        /* Append Analog Channels */
        _itoa(w2s_num_analog, i4_analog_num, 4);

        c_uc_w2s_strncpy(w2s_str_analog, MENU_TEXT(MLM_MENU_KEY_SCAN_ANLG_CH),
                         ui4_len - c_uc_w2s_strlen(w2s_str_analog));
        c_uc_w2s_strncat(w2s_str_analog, w2s_num_analog,
                         ui4_len - c_uc_w2s_strlen(w2s_str_analog));
        i4_ret = c_wgl_do_cmd(h_analog_channel,
                              WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                              WGL_PACK(w2s_str_analog),
                              WGL_PACK(c_uc_w2s_strlen(w2s_str_analog)));
        MENU_CHK_FAIL(i4_ret);

        /* scan progress */
        a_cfg_cust_get_ch_scan_progress(&ui1_progress);

        i4_ret=c_wgl_do_cmd(t_scan_pb.h_bar,
                         WGL_CMD_PG_SET_POS,
                         WGL_PACK((INT32) ui1_progress),
                         NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        c_wgl_repaint(t_scan_pb.h_frm, NULL, TRUE);

        DBG_LOG_PRINT(("[tuner] dig:(%d>>%d) ana:(%d>>%d) pro:%d\n",i4_digital_num_static,i4_digital_num,i4_analog_num_static,i4_analog_num,ui1_progress));
        if(i4_digital_num_static != i4_digital_num || i4_analog_num_static != i4_analog_num)
        {

            c_wgl_repaint(h_digital_channel, NULL, TRUE);
            c_wgl_repaint(h_analog_channel, NULL, TRUE);
        }

        i4_digital_num_static   =   i4_digital_num;
        i4_analog_num_static    =   i4_analog_num;

        if(100 == ui1_progress)
        {
            b_scan = FALSE;

            menu_action_chg_lang(h_cancel_done,
                                 MLM_MENU_KEY_SCAN_DONE,
                                 MLM_MENU_KEY_EMPTY);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_SCAN_BTN_HELP_1));

            i4_ret = c_wgl_repaint(h_cancel_done,
                       NULL,
                       FALSE);

        #ifdef APP_TTS_SUPPORT
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE)));
        #endif

            /* disable the animation timer */
            c_timer_stop(h_timer_ani);
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _do_animation_timer_update_info
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
static VOID _do_animation_timer_update_info(VOID* pv_data,
                                SIZE_T  z_data_size)
{

    _scan_info_update();
    //menu_pm_repaint();
}

/*----------------------------------------------------------------------------
 * Name: _cancel_scan_channel
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
static VOID _cancel_scan_channel()
{

    b_scan = FALSE;

    menu_action_chg_lang(h_cancel_done,
                                 MLM_MENU_KEY_SCAN_DONE,
                                 MLM_MENU_KEY_EMPTY);
    c_wgl_repaint(h_cancel_done,
                       NULL,
                       FALSE);

    c_wgl_repaint(h_digital_channel, NULL, TRUE);
    c_wgl_repaint(h_analog_channel, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
    if(a_am_is_power_on())
    {
        a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE)));
    }
#endif

    /* disable the animation timer */
    c_timer_stop(h_timer_ani);

    a_nav_tuner_setup_cancel_scan_channel();
}

/*----------------------------------------------------------------------------
 * Name: _start_scan_channel
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
static VOID _start_scan_channel()
{
    INT32 i4_ret = 0;

    b_scan = TRUE;

    a_cfg_cust_set_ch_scan_progress(0);
    a_nav_tuner_setup_set_scan_new_channel(FALSE);
    a_nav_tuner_setup_start_scan_channel();

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
}

/*----------------------------------------------------------------------------
 * Name: _scan_channel_icl_nfy_fct
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
static VOID _scan_channel_icl_nfy(VOID* pv_data,
                         SIZE_T  z_data_size)
{
    UINT8             ui1_scan_status = ICL_RECID_TUNER_SETUP_STATUS_COMPLETE;
    ICL_GRPID_TYPE    e_grp_id = ICL_GET_GROUP (((ICL_NOTIFY_DATA_T*)pv_data)->pe_id[0]);

    if (e_grp_id != ICL_GRPID_TUNER_SETUP_STATUS)
    {
        return ;
    }

    a_icl_custom_get_tuner_setup_status(&ui1_scan_status);
    switch(ui1_scan_status)
    {
        case ICL_RECID_TUNER_SETUP_STATUS_COMPLETE:
        {
            break;
        }
        case ICL_RECID_TUNER_SETUP_STATUS_PROGRESS:
            break;
        case ICL_RECID_TUNER_SETUP_STATUS_CANCEL:
        case ICL_RECID_TUNER_SETUP_STATUS_ABORT:
        {
            _cancel_scan_channel();
            break;
        }
        default:
            break;
    }

}


/*----------------------------------------------------------------------------
 * Name: _scan_channel_icl_nfy_fct
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
static INT32 _scan_channel_icl_nfy_fct(
                UINT16              ui2_nfy_id,
                VOID*               pv_tag,
                ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    if(FALSE == b_g_menu_is_show_in_scanning)
    {
        return MENUR_OK;
    }
    menu_async_invoke(_scan_channel_icl_nfy,
                        (VOID*)pt_notify_data,
                        sizeof(ICL_NOTIFY_DATA_T),
                        TRUE);

    return MENUR_OK;
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
    menu_async_invoke(_do_animation_timer_update_info, NULL, 0, FALSE);
}

/*----------------------------------------------------------------------------
 * Name: _cancel_proc_fct
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
static INT32 _cancel_proc_fct(HANDLE_T    h_widget,
                                 UINT32      ui4_msg,
                                 VOID*       param1,
                                 VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
    #ifdef APP_TTS_SUPPORT
        if (b_scan)
        {
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_CNCL), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_CNCL)));
        }
        else
        {
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_SCAN_DONE)));
        }
    #endif

        break;
    }
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        if(b_scan)
        {
            if(ui4_keycode == BTN_SELECT)
            {
                _cancel_scan_channel();
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_SCAN_BTN_HELP_1));
            }
            return MENUR_OK;
        }

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
            MENU_CHK_FAIL (menu_set_focus_on_backbar(FALSE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            menu_pm_repaint();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            MENU_CHK_FAIL (menu_help_tip_keytip_set_focus(h_cancel_done,0,FALSE));
            menu_pm_repaint();
            return MENUR_OK;
        case BTN_RETURN :
        case BTN_CURSOR_RIGHT:
        case BTN_SELECT:
        case BTN_CURSOR_LEFT:
        case BTN_PREV_PRG:
            menu_nav_back();
            return WGLR_OK;
        default :
            break;
        }
    }
    break;
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 _ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect_border_title;
    WGL_COLOR_INFO_T            t_clr_info;
    GL_RECT_T                   t_rect;
    UINT32                      ui4_style;

    ui4_page_id = _ui4_page_id;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_action_create(h_cnt_frm,
                                0,
                                NULL,
                                &h_channel_found);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_clr_info, 0x0, sizeof(WGL_COLOR_INFO_T));
    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;

    i4_ret = c_wgl_do_cmd(h_channel_found,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_CHK_FAIL(i4_ret);


    i4_ret = menu_action_create(h_cnt_frm,
                                1,
                                NULL,
                                &h_digital_channel);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(h_digital_channel,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_action_create(h_cnt_frm,
                                2,
                                NULL,
                                &h_analog_channel);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_analog_channel,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_scan_pb_create(h_cnt_frm,3,NULL,&t_scan_pb);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_action_create(h_cnt_frm,
                                4,
                                _cancel_proc_fct,
                                &h_cancel_done);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_cancel_done,
                          WGL_CMD_LB_SET_COL_WIDTH,
                          WGL_PACK((UINT8)0),
                          WGL_PACK(((UINT16)0)));
    MENU_CHK_FAIL(i4_ret);

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    c_memset(&t_rect_border_title, 0, sizeof(GL_RECT_T));
    t_rect_border_title.i4_left   = 8;
    t_rect_border_title.i4_top    = 6;
    t_rect_border_title.i4_right  = MENU_ITEM_V_WIDE;
    t_rect_border_title.i4_bottom = MENU_ITEM_V_HEIGHT;

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_CENTER_CENTER;
    i4_ret = c_wgl_do_cmd(h_cancel_done,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    ui4_style = WGL_STL_TEXT_MAX_128;

    SET_RECT_BY_SIZE(&t_rect,
                     ATSC_ADV_SCAN_RNG_PROG_TXT_W_1-9,
                     MENU_ITEM_V_HEIGHT * 3 + 2,
                     ATSC_ADV_SCAN_RNG_PROG_TXT_W_2+9,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = menu_util_create_txt(h_cnt_frm,
                                  ui4_style,
                                  &t_rect,
                                  WGL_AS_LEFT_CENTER,
                                  &h_txt);

     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret =menu_scan_pb_set_satus(h_txt,TRUE);
     MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_timer_ani);
    MENU_CHK_FAIL(i4_ret);

    if (ICLR_OK != a_icl_notify_reg(
                        ICL_GRPID_TUNER_SETUP_STATUS,
                        ICL_PRIORITY_DEFAULT,
                        NULL,
                        NULL,
                        _scan_channel_icl_nfy_fct,
                        &ui2_g_icl_nfy_id))
    {
        DBG_LOG_PRINT(("[menu] {%s,%d} a_icl_notify_reg fail.\r\n", __FUNCTION__, __LINE__));
        ui2_g_icl_nfy_id = 0;
    }

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
    if(h_timer_ani != NULL_HANDLE)
    {
        c_timer_delete(h_timer_ani);
        h_timer_ani = NULL_HANDLE;
    }

    a_icl_notify_unreg(ui2_g_icl_nfy_id);
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32           i4_ret;
	GL_RECT_T     t_rect = {0};
	GL_RECT_T     t_rect1 = {0};
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;

    MENU_CHK_FAIL (a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL));


    b_clean_lists = TRUE;
    b_g_menu_is_show_in_scanning=TRUE;

    /* Menu is in scanning status */
    t_g_menu_is_scanning = TRUE;

    /* Broadcast the message to disable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to disable the EAS.\r\n"));
    menu_set_scan_type (MENU_SCAN_TYPE_FULL_MODE);

    MENU_LOG_ON_FAIL (menu_main_set_title(MLM_MENU_KEY_SCAN_AUTO_CHANNEL));

    i4_ret = menu_action_chg_lang(h_channel_found,
                                 MLM_MENU_KEY_SCAN_CH_FOUND_2,
                                 MLM_MENU_KEY_EMPTY);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(h_digital_channel,
                                 MLM_MENU_KEY_SCAN_DIG_CH,
                                 MLM_MENU_KEY_EMPTY);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(h_analog_channel,
                                 MLM_MENU_KEY_SCAN_ANLG_CH,
                                 MLM_MENU_KEY_EMPTY);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(h_cancel_done,
                                 MLM_MENU_KEY_CNCL,
                                 MLM_MENU_KEY_EMPTY);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_SCAN_COMPLETE)),
                          (VOID*)0xFFFF);
    MENU_LOG_ON_FAIL(i4_ret);

    UINT8                 ui1_align=0;
    ui1_align = (UINT8)WGL_NO_AUTO_REPAINT;
    i4_ret = c_wgl_insert (h_txt,
                NULL_HANDLE,
                WGL_INSERT_TOPMOST,
                ui1_align);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_wgl_do_cmd(t_scan_pb.h_bar,
                 WGL_CMD_PG_SET_POS,
                 WGL_PACK((INT32) 0),
                 NULL);
    MENU_LOG_ON_FAIL(i4_ret);

	/*Adjust last shadow position*/
	c_wgl_get_coords(h_cancel_done,WGL_COORDS_SCREEN,&t_rect1);
	t_rect.i4_top = t_rect1.i4_bottom;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;
	t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
	MENU_LOG_ON_FAIL(i4_ret);

    /* change the info in help list */
    menu_atsc_help_show_scan();

#if 0
    i4_ret = menu_help_tip_keytip_show(FALSE);
    MENU_CHK_FAIL(i4_ret);
#endif
    i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_SCAN_BTN_HELP_2));
    MENU_CHK_FAIL(i4_ret);

    a_amb_channel_scan_active(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
	HANDLE_T			  h_last_shadow_item = NULL_HANDLE;
	INT32				  i4_ret  = 0;

    /* Menu is not in scanning status */
    t_g_menu_is_scanning = FALSE;
    b_g_menu_is_show_in_scanning=FALSE;

    /* Broadcast the message to enable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to enable the EAS.\r\n"));
    MENU_CHK_FAIL (menu_help_tip_keytip_show(TRUE));

	menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
	MENU_LOG_ON_FAIL(i4_ret);

    a_amb_channel_scan_active(FALSE);
    menu_set_scan_type (MENU_SCAN_TYPE_UNKNOWN);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    b_scan = FALSE;

    t_scan_info_atv.i4_vir_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_num  = 0;
    t_scan_info_atv.i4_phy_ch_ttl  = 0;

    t_scan_info_dtv.i4_vir_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_num  = 0;
    t_scan_info_dtv.i4_phy_ch_ttl  = 0;
    
	a_tuner_setup_view_change_source_to_tv();

    /* update help tip */
    MENU_CHK_FAIL (_help_tip_update (_HELP_TIP_TYPE_CANCEL_DONE));

    /* set callback function for homebar */
    menu_set_homebar_proc (_homebar_proc_fct) ;

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    _start_scan_channel();

    /* set focuse on cancel */
    MENU_CHK_FAIL (c_wgl_set_focus(h_cancel_done,WGL_NO_AUTO_REPAINT)) ;

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    b_page_leaving = TRUE;

    /* clean callback function of backbar & homebar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;
    MENU_LOG_ON_FAIL (menu_set_homebar_proc (NULL)) ;

    if (b_scan)
    {
        _cancel_scan_channel();
    }
    b_page_leaving = FALSE;

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* do_nothing */
    }

    return MENUR_OK;
}

extern INT32 menu_atsc_page_auto_scan2_init(VOID)
{
    t_g_menu_atsc_page_auto_scan2.pf_menu_page_create =    _on_page_create;
    t_g_menu_atsc_page_auto_scan2.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_atsc_page_auto_scan2.pf_menu_page_show=       _on_page_show;
    t_g_menu_atsc_page_auto_scan2.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_atsc_page_auto_scan2.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_atsc_page_auto_scan2.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_atsc_page_auto_scan2.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                    CLI relative fucntion
 ----------------------------------------------------------------------------*/
#ifdef __CLI_SUPPORT__

INT32 menu_atsc_cli_scan(INT32        i4_argc,
                         const CHAR** pps_argv)
{
    return CLIR_OK;
}
#endif /* __CLI_SUPPORT__ */


#endif /* ATSC_AUTO_SCAN2_ENABLE */


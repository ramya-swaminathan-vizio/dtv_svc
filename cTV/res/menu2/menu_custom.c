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
 * $RCSfile: menu_custom.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/21 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 1433fe1fd8b5fe1dfc2a58820b53a685 $
 *
 * Description:
 *         This file contains all the customizable code in menu.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include "u_iom.h"
#include "u_pcl.h"

#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_cfg.h"
#include "c_fe.h"
#include "c_svctx.h"
#include "c_wgl.h"
#include "c_scc.h"
#include "c_rm.h"
#include "c_pcl.h"


#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"

#include "mmp/a_mmp.h"

#include "fonts/fontdata.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_device/menu_device.h"
#include "menu2/menu_network_phase1/menu_network.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "menu2/menu_util2.h"

#include "menu2/menu_common/menu_common.h"

#include "res/menu2/a_menu_custom.h"
#include "res/menu2/menu_config.h"
#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_custom_dialog.h"
#include "res/menu2/menu_cust_define.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#ifdef APP_USE_BDF_FONT
#include "res/fonts/a_font_tiresias.h"
#endif

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include "msgconvert/a_msgconvert.h"
#endif
#include "am/a_am.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/model/model.h"
#if 1//Cedric
#include "nav/banner2/banner_common.h"
#include "nav/input_src/input_src_list.h"
#include "nav/scrn_blank/a_nav_scrn_blank.h"
#endif
#include "nav/sleep/a_sleep.h"
#include "nav/cc_info/cc_info.h"
#include "nav/power/a_nav_power.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "app_util/a_cfg.h"
#include "app_client.h"
#include "nav/power/nav_power.h"
#include "res/app_util/config/acfg_cust_video.h"

#include "app_util/toast_widget/a_toast.h"

#include "wizard2/wzd_util.h"
//#include "wizard2/a_wzd.h"
#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#endif
#include "app_util/mtktvapi/a_mtktvapi_cec.h"
#include "wizard_anim/a_wzd.h"
#include "fcntl.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define     DELAY_UNDEF_KEY                    (0xFFFFFFFF)
#define     DELAY_INPUT_KEY                    (BTN_INPUT_SRC)
#define     DELAY_ASPECT_KEY                   (BTN_ASPECT)

#define     MENU_PAGE_REFRESH_BY_AV_CHG_DELAY  (UINT32)1000
#define     MENU_PAGE_FILE_FLAG_DELAY          (UINT32)500
#define     MENU_BLANK_SCREEN_FILE_FLAG_DELAY          (UINT32)800
#define     OLED_AUTO_PWR_OFF_1                (10 * 60 * 1000) // oled auto power off timer for protect screen when auto power off is on
#define     OLED_AUTO_PWR_OFF_2                (60 * 60 * 1000) // oled auto power off timer for protect screen when auto power off is OFF
#define     OLED_AUDIO_CHECK_REPEAT            (1 * 60 * 1000)  // check audio for OLED protected;
#define     OLED_TOAST_CHECK_TIME              (1000)  // check audio for OLED protected;

UINT32      ui4_g_delay_proc_input_key = DELAY_UNDEF_KEY;
extern INT32 update_color_calibration_ui(VOID);
typedef struct __SVCTX_NFY_DATA_T{
    HANDLE_T            h_svctx;
    SVCTX_COND_T        e_nfy_cond;
    SVCTX_NTFY_CODE_T   e_code;
    STREAM_TYPE_T       e_stream_type;
}   _SVCTX_NFY_DATA_T;
/*-----------------------------------------------------------------------------
                           data declaraions
 ----------------------------------------------------------------------------*/
MENU_CUSTOM_T        t_g_menu_custom;

#if 0//(MENU_SUPPORT_HOT_KEY_PIC)
BOOL g_menu_b_support_hot_key_PIC = 1;
#endif

#if (MENU_SUPPORT_HOT_KEY_ASPECT_RATIO)
UINT16 g_menu_u16_item_id_PICTURE_ASPECT_RATIO;
#endif

//#ifdef APP_EMANUAL_SUPPORT
static BOOL                   b_g_start_user_manual = FALSE;
//#endif

#ifdef APP_MMP_SUPPORT
static BOOL                   b_g_resuming_mmp = FALSE;
#endif

#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
extern INT32 a_menu_set_help_tip_blue_button_enable_status (BOOL b_status);
#endif
static BOOL                 b_is_under_blank = FALSE;
static MENU_CUSTOM_BLK_SCRN_MODE t_blk_crn_mode = BLK_SCRN_NORMAL;

static UINT8                ui1_old_led_ctrl = 0;
static BOOL                 b_old_ipcc_visible = TRUE;
static ACFG_RETAIL_MODE_T   t_g_retail_mode = ACFG_RETAIL_MODE_HOME;

static BOOL                 g_b_need_delay = FALSE;
static HANDLE_T             h_file_flag_timer = NULL_HANDLE;
static HANDLE_T             h_blank_screen_flag_timer = NULL_HANDLE;
static HANDLE_T             h_blank_oled_screen_timer;
static HANDLE_T             ui4_blank_oled_scrn_delay = 1000 * 60;
static BOOL                 b_oled = FALSE;
static BOOL                 h_blank_oled_screen_timer_start = FALSE;

static HANDLE_T             h_oled_pro_auto_pwr_off_timer;
static HANDLE_T             h_oled_pro_audio_check_timer;

static WDK_TOAST_PARAM_T    tg_toast_param;
static WDK_OSD_TOAST_T      t_g_wdk_view = {0};
static HANDLE_T             h_timer_show = NULL_HANDLE;
static BOOL                 b_menu_pp_pause_flag = FALSE;
static HANDLE_T             h_sema_blank_screen_mtx;
static UINT32               ui4_m_tmp_keycode=0;
static HANDLE_T             h_timer_repaint;
static UINT32               ui4_g_ver=0;
static UINT32               ui4_g_ver_tmp=0;
static UINT32               ui4_g_last_hdr=0;

#ifdef APP_NETWORK_SUPPORT
extern UINT32 ui4_g_menu_page_network_main;
#endif

static BOOL                 b_oled_pro_auto_pwr_off_timer_start = FALSE;
static BOOL                 b_oled_pro_audio_check_timer_start = FALSE;
static BOOL                 b_blank_screen_block_pwr_off = TRUE;
static BOOL                 b_audio_sync_flag = FALSE;

static HANDLE_T             _h_blank_oled_toast_timer;
static HANDLE_T             _h_toast_blank_scrn;
static BOOL                 _b_blank_oled_toast_create = FALSE;
static BOOL                 _b_blank_oled_toast_show = FALSE;
static BOOL                 _b_blank_oled_toast_timer_start = FALSE;
static UINT32               _ui4_blank_oled_toast_show_time = 0;

/*-----------------------------------------------------------------------------
                       press +/- not refresh
 ----------------------------------------------------------------------------*/
extern BOOL vol_banber_is_show_state(VOID);
INT32 nav_cec_custom_get_device_connect_status (BOOL* connect_status);


/*-----------------------------------------------------------------------------
                        function implementation
 ----------------------------------------------------------------------------*/

VOID menu_custom_pp_set_pause_flag(BOOL b_menu_pause)
{
    b_menu_pp_pause_flag = b_menu_pause;
}

BOOL menu_custom_pp_get_pause_flag(VOID)
{
    return b_menu_pp_pause_flag;
}

static VOID _menu_allow_airplay_get_rc_key(HANDLE_T h_timer, VOID *pv_tag);

/*----------------------------------------------------------------------------
 *      Language Change notify
 ----------------------------------------------------------------------------*/
static VOID _do_chg_lang(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    //if(menu_get_cond() != MENU_COND_SHOW)
    {
        menu_custom_chg_lang();
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _do_tv_page
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _do_tv_page(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    BOOL    b_sleep_timer_page = FALSE;
    INT32    i4_ret = 0;
    UINT32            ui4_page_id = 0;

    if(menu_get_cond() == MENU_COND_SHOW &&
       t_g_menu_is_scanning == FALSE)
    {
        i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
        MENU_LOG_ON_FAIL(i4_ret);
        if(ui4_page_id == ui4_g_menu_page_slp)
        {
            b_sleep_timer_page = menu_focus_item_is_the_assign_item(MLM_MENU_KEY_TITLE_SLEEP_TIMER);
            if(FALSE == b_sleep_timer_page)
            {
                menu_pm_repaint();
                menu_pm_refresh();
            }
        }
        else
        {
            menu_pm_repaint();
            menu_pm_refresh();
        }

    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _get_3d_setting_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _get_3d_setting_mode(VOID)
{
    BOOL        b_3D_support = FALSE;

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        INT32   i4_ret;
        i4_ret = a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
        DBG_INFO(("\n------get 3D support , ret:%d , support: %d\n", i4_ret, b_3D_support? 1:0));
    }

    return b_3D_support;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _cfg_gui_lang_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static  VOID _cfg_gui_lang_nfy_fct(
    UINT16     ui2_nfy_id,
    VOID*      pv_tag,
    UINT16     ui2_id)
{
    menu_async_invoke(_do_chg_lang, (VOID*)NULL, 0, FALSE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _cfg_chk_tv_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static  VOID _cfg_chk_tv_nfy_fct(
    UINT16     ui2_nfy_id,
    VOID*      pv_tag,
    UINT16     ui2_id)
{

    UINT16      ui2_inp_main  = CFG_MAKE_ID(APP_CFG_GRPID_NAV, APP_CFG_RECID_INPUT_MAIN);
    UINT16      ui2_inp_src   = CFG_MAKE_ID(APP_CFG_GRPID_INPUT_SRC, APP_CFG_RECID_INPUT_SRC_BLOCK);

    if (ui2_inp_main == ui2_id ||
        ui2_inp_src  == ui2_id)
    {
        menu_async_invoke(_do_tv_page, (VOID*)NULL, 0, FALSE);
    }
}
extern BOOL menu_page_is_network_manual_setup_page(UINT32 ui4_page_id);
/*-----------------------------------------------------------------------------
 * Name: _exit_pic_size_and_pos_page
 *
 * Description:
 *          This FUNC is used to exit picture size and position page.
 *          When timing changes from 60Hz to 120Hz, pause MENU.
 * Inputs:  VOID
 *
 * Outputs: VOID
 *
 * Returns: MENUR_OK
            MENUR_FAIL
 *-----------------------------------------------------------------------------*/
static INT32 _exit_pic_size_and_pos_page(VOID)
{
    INT32   i4_ret = MENUR_OK;

    a_amb_pause_app(MENU_NAME);
    return i4_ret;
}

static BOOL _is_need_refresh_page(UINT16 ui2_nfy_id, UINT16 ui2_id)
{
    BOOL    b_refresh = TRUE;
    UINT16  ui2_grp_id = CFG_GET_GROUP(ui2_id);
    UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);

    do {
        if (g_b_need_delay)
        {
            b_refresh = FALSE;
            break;
        }
        if(menu_page_is_network_manual_setup_page(menu_get_current_page_id()))
        {
            b_refresh = FALSE;
            break;
        }

        if (menu_get_toast_range_flag())
        {
            b_refresh = FALSE;
            break;
        }


        if (menu_get_cond() != MENU_COND_SHOW)
        {
            b_refresh = FALSE;
            break;
        }

        if (ui2_grp_id != APP_CFG_GRPID_VIDEO
            && ui2_grp_id != APP_CFG_GRPID_DISP
            && ui2_grp_id != APP_CFG_GRPID_AUDIO
            && ui2_grp_id != APP_CFG_GRPID_CC
            && ui2_grp_id != APP_CFG_GRPID_DCS
            && ui2_grp_id != APP_CFG_GRPID_CUSTOM_BASE)
        {
            b_refresh = FALSE;
            break;
        }

        if (ui2_grp_id == APP_CFG_GRPID_AUDIO
            && ui2_rec_id == APP_CFG_RECID_VOLUME_ALL
            && vol_banber_is_show_state() == TRUE)
        {
             b_refresh = FALSE;
             break;
        }
        if(ui2_grp_id == APP_CFG_GRPID_CUSTOM_BASE)
        {
            if(ui2_rec_id != APP_CFG_RECID_CUSTOM_ANALOG_AUD_OUT)
            {
                b_refresh = FALSE;
                break;
            }
        }
    } while(FALSE);
    DBG_INFO(("[MENU][%s %d]ui2_grp_id = %d ui2_rec_id = %d\n",__FUNCTION__,__LINE__,ui2_grp_id,ui2_rec_id));
    return b_refresh;
}

extern BOOL menu_get_factory_reset_status(VOID);

static VOID repaint_timer_func (
    VOID* pv_ver,
    SIZE_T  z_data_size)
{
   UINT32 ui4_ver = 0;
   ui4_ver = *(UINT32*)pv_ver;

   if(ui4_ver != ui4_g_ver)
   {
       DBG_LOG_PRINT(("[Menu]msg exp ui4_ver:%d, ui4_g_ver:%d,%s,%d\r\n",ui4_ver,ui4_g_ver,__FUNCTION__,__LINE__));
       return;
   }

   menu_pm_refresh();
   menu_pm_repaint();
}

static VOID _menu_repaint_timer_cb(
    HANDLE_T                  h_timer,
    VOID*                     pv_ver)
{
    menu_async_invoke(repaint_timer_func, pv_ver, sizeof(UINT32), FALSE);
}

static VOID _cfg_av_chg_nfy_fct(
    UINT16     ui2_nfy_id,
    VOID*      pv_tag,
    UINT16     ui2_id)
{
    INT32 i4_ret = 0;

    if(menu_get_factory_reset_status() ||
       !_is_need_refresh_page(ui2_nfy_id, ui2_id))
    {
        return;
    }

    i4_ret = c_timer_stop(h_timer_repaint);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_ver = ui4_g_ver + 1 ;
    ui4_g_ver_tmp   = ui4_g_ver;

    i4_ret = c_timer_start(h_timer_repaint,
                           100,
                           X_TIMER_FLAG_ONCE,
                           _menu_repaint_timer_cb,
                           (VOID*)&ui4_g_ver_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

}

/*----------------------------------------------------------------------------
 *      SVCTX Notify
 ----------------------------------------------------------------------------*/
static VOID _do_svctx_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    CHAR        s_disp_name[SYS_NAME_LEN + 1];
    ISL_REC_T   t_isl_rec;
    BOOL                b_sleep_timer_page = FALSE;
    INT32            i4_ret = 0;
    UINT32            ui4_page_id = 0;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_tv_get_crnt_isl_rec(s_disp_name, &t_isl_rec);

    if(menu_get_cond() != MENU_COND_SHOW)
    {
        return;
    }

    if(!t_g_menu_is_scanning)
    {
        _SVCTX_NFY_DATA_T*  pt_svctx_nfy = (_SVCTX_NFY_DATA_T*)pv_data;

        switch(pt_svctx_nfy->e_code)
        {
        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
        case SVCTX_NTFY_CODE_SIGNAL_LOSS:
        case SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE:
            i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
            MENU_LOG_ON_FAIL(i4_ret);

            if (ui4_g_menu_page_pic_size == ui4_page_id
                || ui4_g_menu_page_pic_postion ==ui4_page_id)
            {
                if (SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE == pt_svctx_nfy->e_code)
                {
                    i4_ret = _exit_pic_size_and_pos_page();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
            else if(ui4_g_menu_custom_page_color_calibration == ui4_page_id)
            {
                if ((SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE == pt_svctx_nfy->e_code) ||
                    (SVCTX_NTFY_CODE_SIGNAL_LOSS == pt_svctx_nfy->e_code))
                {
                    /* update color calibration page UI when timming chanes */
                    i4_ret = update_color_calibration_ui();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
            else if(ui4_g_menu_page_slp == ui4_page_id)
            {
                b_sleep_timer_page = menu_focus_item_is_the_assign_item(MLM_MENU_KEY_TITLE_SLEEP_TIMER);
                if(FALSE == b_sleep_timer_page)
                {
                    menu_pm_repaint();
                    menu_pm_refresh();
                }
            }
            else
            {
                if((SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE == pt_svctx_nfy->e_code) ||
                    (SVCTX_NTFY_CODE_SIGNAL_LOSS == pt_svctx_nfy->e_code))
                {
                #ifndef APP_CAST_TEST_PATTERN
                    a_menu_test_patterns_turn_off();
                #endif
                }
            }

        #if 0
            /*phase1 no use*/
            main_menu_update_3D_item_status();
        #endif
            break;
        case SVCTX_NTFY_CODE_STOPPED:
        #ifndef APP_CAST_TEST_PATTERN
            a_menu_test_patterns_turn_off();
        #endif
            a_color_tuner_update_value();
            DBG_INFO(("\n####%s(%d)turn off test patterns when video stop\n",__FUNCTION__,__LINE__));
    #ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
            a_menu_set_help_tip_blue_button_enable_status(FALSE);

    #endif
            break;
        case SVCTX_NTFY_CODE_SERVICE_BLOCKED:
        #ifndef APP_CAST_TEST_PATTERN
            a_menu_test_patterns_turn_off();
        #endif
            DBG_INFO(("\n####%s(%d)turn off test patterns when channel locked\n",__FUNCTION__,__LINE__));
            break;
        case SVCTX_NTFY_CODE_SERVICE_UNBLOCKED:
            break;
        default:
            break;
        }
    }
}

static VOID _svctx_notify_fct(
    HANDLE_T            h_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    _SVCTX_NFY_DATA_T   t_svctx_nfy;

    if(menu_get_cond() != MENU_COND_SHOW)
    {
        return;
    }

    switch (e_code)
    {
    /* timing change */
    case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
    case SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE:
    /* auto done */
    case SVCTX_NTFY_CODE_VIDEO_AUTO_CLK_POS_PHS_DONE:
    /* signal status change */
    case SVCTX_NTFY_CODE_SERVICE_BLOCKED:
    case SVCTX_NTFY_CODE_SERVICE_UNBLOCKED:
    case SVCTX_NTFY_CODE_SIGNAL_LOSS:
    case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
    case SVCTX_NTFY_CODE_STREAM_STARTED:
    case SVCTX_NTFY_CODE_STOPPED:
        t_svctx_nfy.h_svctx         = h_svctx;
        t_svctx_nfy.e_nfy_cond      = e_nfy_cond;
        t_svctx_nfy.e_code          = e_code;
        t_svctx_nfy.e_stream_type   = e_stream_type;

        menu_async_invoke(_do_svctx_nfy, &t_svctx_nfy, sizeof(_SVCTX_NFY_DATA_T), FALSE);
        break;
    default:
        break;
    }
}
/*----------------------------------------------------------------------------
 * Name: _aud_page_cec_nfy_hdlr
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
static VOID _aud_page_cec_nfy_hdlr (VOID* pv_data, SIZE_T  z_data_size)
{
    menu_pm_repaint();
    menu_pm_refresh();
}
/*----------------------------------------------------------------------------
 * Name: menu_custom_set_aud_spdif
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
INT32 menu_custom_set_aud_spdif(UINT16 ui2_idx)
{
    INT32                   i4_ret = 0;

/*2K20 dts can be decode by speaker*/
#if 0
    BOOL                    connect_status = FALSE;

    if(ui2_idx == AUD_SPDIF_AUDIO_OUT_PCM
        #if HIDE_SPDIF_AUDIO_OUT_BITSTREAM
            )
        #else
            || ui2_idx == AUD_SPDIF_AUDIO_OUT_DOLBY_D )
        #endif
    {
        ASH_AUDIO_INFO_T        t_audio_info;

        /* t_audio_info */
        {
            c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

            i4_ret = c_svctx_get_audio_info(menu_get_crnt_svctx(), &t_audio_info);
            MENU_CHK_FAIL(i4_ret == SVCTXR_OK ? MENUR_OK : i4_ret );
        }

        i4_ret = nav_cec_custom_get_device_connect_status(&connect_status);
        DBG_LOG_PRINT(("ddddddd  %s()  line %d ret=%d\n", __FILE__, __LINE__ , i4_ret));

        //throw error message
        if(FALSE == connect_status && ASH_AUDIO_FMT_DTS == t_audio_info.e_aud_fmt)
        {
            WDK_TOAST_T    t_toast = {0};
            UTF16_T        w2s_tmp_str[512] = {0};
            UTF16_T        *pw2s_text = NULL;

            pw2s_text = MENU_TEXT(MLM_MENU_KEY_MENU_DIGITAL_AUD_OUT_THROW_INFO);
            c_uc_w2s_strcpy(w2s_tmp_str, pw2s_text);
            c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_WARNING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;
            t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;
            menu_send_string_to_nav_toast(&t_toast);
        }
    }
#endif

    i4_ret = a_cfg_custom_set_digital_audio(ui2_idx);
    MENU_CHK_FAIL(i4_ret == APP_CFGR_OK ? MENUR_OK : i4_ret);
    i4_ret = a_cfg_update_spdif_type();
    MENU_CHK_FAIL(i4_ret == APP_CFGR_OK ? MENUR_OK : i4_ret);
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _cec_aud_nfy_func
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
static INT32 _cec_aud_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32  i4_ret;
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);
    MENU_PAGE_STATE_T  e_page_state;

    if (e_grp_id != ICL_GRPID_CEC)
    {
        return MENUR_OK;
    }

    /*CEC Status Change */
    i4_ret=menu_page_get_state(ui4_g_menu_page_aud,&e_page_state);
    MENU_CHK_FAIL(i4_ret);

    if(MENU_PAGE_STATE_FOCUS==e_page_state||
       MENU_PAGE_STATE_SHOW==e_page_state)
    {
        menu_async_invoke (_aud_page_cec_nfy_hdlr, (VOID*)NULL, 0, FALSE);
    }

    if(e_rec_id != ICL_RECID_CEC_SAC_STATUS)
    {
        return MENUR_OK;
    }

    i4_ret = a_cfg_update_spdif_type();
    MENU_CHK_FAIL(i4_ret == APP_CFGR_OK ? MENUR_OK : i4_ret);

    return MENUR_OK;
}

static INT32 _cec_ddp_nfy_func (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);
    INT32          i4_ret = 0;

    if (e_grp_id != ICL_GRPID_CEC)
    {
        return MENUR_OK;
    }

    if(e_rec_id != ICL_RECID_CEC_SAC_DDP)
    {
        return MENUR_OK;
    }

    i4_ret = a_cfg_update_spdif_type();
    MENU_CHK_FAIL(i4_ret == APP_CFGR_OK ? MENUR_OK : i4_ret);

    return MENUR_OK;
}

static INT32 _menu_tv_name_change_fct (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    menu_pm_update_all(MENU_PAGE_UMASK_CHG_LANG);
    menu_pm_repaint();
    menu_pm_refresh();
    return MENUR_OK;
}

static INT32 _menu_hdr_change_fct (UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    UINT32     ui4_type = a_cfg_get_hdr_type();
    DBG_LOG_PRINT(("[menu]hdr_type change from %d to %d, %s,%d\r\n",ui4_g_last_hdr,ui4_type,__FUNCTION__,__LINE__));

    if(ui4_g_last_hdr != ui4_type)
    {
        CHAR       s_app_name[APP_NAME_MAX_LEN];
        INT32      i4_ret   = 0;

        /*update pq related page data */
        menu_pm_update(ui4_g_menu_page_vid, MENU_PAGE_UMASK_REFRESH);
        menu_pm_update(ui4_page_vid_more_adv_pic, MENU_PAGE_UMASK_REFRESH);

        i4_ret = a_am_get_active_app(s_app_name);
        if (AMR_OK == i4_ret && 0 == c_strcmp (s_app_name, MENU_NAME))
        {
            menu_pm_refresh();
            menu_pm_repaint();
        }
    }

    ui4_g_last_hdr = ui4_type;
    return MENUR_OK;
}

static INT32 _menu_hot_key_register(VOID)
{
    INT32                       i4_ret;
    MENU_HOT_KEY_REG_T          t_hot_key_reg;

    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

#if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
    MENU_DEBUG_KEY_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][KEY][ASPECT_RATIO]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
    t_hot_key_reg.ui4_key_code = BTN_ASPECT;
    t_hot_key_reg.ui4_page_idx = ui4_g_menu_page_aspect_ratio;
    i4_ret = menu_reg_hot_key(&t_hot_key_reg);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef KK_SCREEN_MODE
    t_hot_key_reg.ui4_key_code = BTN_ASPECT;
    t_hot_key_reg.ui4_page_idx = ui4_g_menu_page_scr_mode;
    i4_ret = menu_reg_hot_key(&t_hot_key_reg);
    MENU_CHK_FAIL(i4_ret);
#endif

    if(_get_3d_setting_mode() == TRUE)
    {
        t_hot_key_reg.ui4_key_code = BTN_3D;
        t_hot_key_reg.ui4_page_idx = ui4_g_menu_page_3D_setting;
        i4_ret = menu_reg_hot_key(&t_hot_key_reg);
        MENU_CHK_FAIL(i4_ret);
    }

    t_hot_key_reg.ui4_key_code = BTN_NETWORK;
    t_hot_key_reg.ui4_page_idx = ui4_g_menu_page_network_main;
    i4_ret = menu_reg_hot_key(&t_hot_key_reg);
    MENU_CHK_FAIL(i4_ret);

    t_hot_key_reg.ui4_key_code = BTN_BLANK_SCREEN;
    t_hot_key_reg.ui4_page_idx = ui4_g_menu_page_blank_scrn;
    i4_ret = menu_reg_hot_key(&t_hot_key_reg);
    MENU_CHK_FAIL(i4_ret);


#if( MENU_SUPPORT_HOT_KEY_PIC )
    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
    t_hot_key_reg.ui4_key_code = BTN_P_EFFECT;
    t_hot_key_reg.ui4_page_idx = ui4_g_menu_custom_page_pic_mode;
    i4_ret = menu_reg_hot_key(&t_hot_key_reg);
    MENU_CHK_FAIL(i4_ret);
#endif

#ifdef APP_SUPPORT_PIC_HOT_KEY
    t_hot_key_reg.ui4_key_code = BTN_P_EFFECT;
    t_hot_key_reg.ui4_page_idx = ui4_g_menu_page_vid;
    i4_ret = menu_reg_hot_key(&t_hot_key_reg);
    MENU_CHK_FAIL(i4_ret);
#endif

    return MENUR_OK;
}

static INT32 _menu_hot_key_unregister(VOID)
{
#if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO || defined(KK_SCREEN_MODE) )
    menu_unreg_hot_key(BTN_ASPECT);
#endif

    if(_get_3d_setting_mode() == TRUE)
    {
        menu_unreg_hot_key(BTN_3D);
    }

    menu_unreg_hot_key(BTN_NETWORK);
    menu_unreg_hot_key(BTN_BLANK_SCREEN);

#if( MENU_SUPPORT_HOT_KEY_PIC|| defined(APP_SUPPORT_PIC_HOT_KEY) )
    menu_unreg_hot_key(BTN_P_EFFECT);
#endif

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _menu_custom_system_key_handler_fct
 * Description:
 *      menu custom system key buttton menu handle function
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _menu_custom_system_key_menu_fct(VOID*        pv_data,
                                             SIZE_T       z_data_size)
{
    INT32       i4_ret = MENUR_OK;
    UINT32      ui4_cnt_page = 0;

    i4_ret = menu_nav_get_crnt_page(&ui4_cnt_page);
    MENU_LOG_ON_FAIL(i4_ret);

    if((ui4_g_menu_page_mmp_dev_list == ui4_cnt_page)||
       (ui4_g_menu_page_mmp_media_type == ui4_cnt_page))
    {
        i4_ret = menu_nav_anim_go(ui4_g_menu_page_main_menu, NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return;
}

INT32 menu_custom_exit_menu_actions(VOID)
{
    /*hide add channel dialog*/
    a_analog_channel_fail_dlg_hide();
    a_create_pic_mode_warn_dlg_hide();
    a_menu_test_page_osd_hide();
    set_delay_lock_cust_pic_mode_status(TRUE);

#if 0
#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
    if (a_c4tv_apron_check_cast_state())
    {
        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);
    }
#endif
#endif

#ifdef APP_TTS_SUPPORT
    a_menu_tts_stop();
#endif


    return MENUR_OK;
}


static VOID menu_custom_set_blank_scrn(BOOL b_blank)
{
    //c_sema_lock(h_sema_blank_screen_mtx,X_SEMA_OPTION_WAIT);  //dolphin not lock here ,modify 20190430

    b_is_under_blank = b_blank;

    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} b_is_under_blank=%d\n",
            __FUNCTION__,__LINE__, b_is_under_blank ));
    );

    //c_sema_unlock(h_sema_blank_screen_mtx);
}

BOOL menu_custom_is_blank_screen(VOID)
{
    return b_is_under_blank;
}

VOID set_temporary_key_code(UINT32 ui4_keycode)
{
    ui4_m_tmp_keycode = ui4_keycode;
}
UINT32 get_temporary_key_code(void)
{
    return ui4_m_tmp_keycode;
}

//dolphin 20190517 prevent airplay from getting any rcu key
VOID _menu_prevent_airplay_get_rc_key(void)
{
    /*
      * dolphin 20190517: when in blank screen ,chromium and menu will get key at the same time
      * which leading problem:  when system in blank screen , user press RCU key 'EXIT' both menu and
      * airplay will get exit ,leading to airplay exit and unblank screen ,but in fact user just only want to
      * unblank screen ,so we use this flag to prevent chromium from getting RCU key
      */

  #if 1 // Fix coverity-4491323: Argument cannot be negative
    int iFileHandle = open("/tmp/blank_screen_on", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if( iFileHandle < 0 )
    {
        return;
    }
    close(iFileHandle);
  #else
    close(open("/tmp/blank_screen_on", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
  #endif
}

//dolphin 20190517 allow airplay getting rcu key
VOID _menu_allow_airplay_get_rc_key(HANDLE_T h_timer, VOID *pv_tag)
{
    unlink("/tmp/blank_screen_on");
}

extern BOOL a_is_oled_compensation_support();
extern BOOL a_oled_compensation_is_running();
BOOL menu_custom_set_audio_sync(BOOL b_flag)
{
    b_audio_sync_flag = b_flag;

    // Fix coverity-4731103: Missing return statement
    return TRUE;
}

extern BOOL acfg_cust_Is_CurSrcHDMI(void);
static BOOL _menu_custom_check_audio_sync(VOID)
{
	ACFG_MI_MM_INFO_T    t_mi_mm_info_t  = {0};
	BOOL         b_interlace             = FALSE;
	UINT32         ui4_decoder           = 0;
	INT32         i4_ret                 = 0;
    b_audio_sync_flag = FALSE;
    if((menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_STILL_IMAGE) && acfg_cust_Is_CurSrcHDMI())
    {
        return b_audio_sync_flag;
    }
	if(MENUR_OK == a_cfg_mi_mm_querry_ex(&t_mi_mm_info_t,&b_interlace))
	{
		DBG_LOG_PRINT(("[OLED PROTECT] %s %d eAudioCodec = %d\n",__FUNCTION__,__LINE__, t_mi_mm_info_t.eAudioCodec));
		if(t_mi_mm_info_t.eAudioCodec > 0)
		{
			b_audio_sync_flag = TRUE;
		}
	}

    i4_ret = a_cfg_aud_get_decoder_support_capbility(&ui4_decoder);
    if(i4_ret != MENUR_OK)
    {
        DBG_LOG_PRINT(("[OLED PROTECT] %s %d,get decoder failed !!! \n",__FUNCTION__,__LINE__));
    }
    else
    {
        b_audio_sync_flag = ui4_decoder ? TRUE:FALSE;
    }

    DBG_LOG_PRINT(("[OLED PROTECT] %s %d b_audio_sync_flag = %d,ui4_decoder = %d\n",__FUNCTION__,__LINE__, b_audio_sync_flag,ui4_decoder));
    return b_audio_sync_flag;
}

INT32 menu_custom_blank_screen(VOID)
{
    UINT32  i4_ret = MENUR_OK;
    BOOL b_dpms;
    MENU_CUSTOM_BLK_SCRN_MODE t_blk_mode = menu_custom_get_blank_scrn_mode();

    //DBG_LOG_PRINT(("[MENU][BLANK_SCREEN] menu_custom_blank_screen() \n" ));

    if(a_is_oled_compensation_support() && a_oled_compensation_is_running())
    {
        DBG_LOG_PRINT(("[MENU]TV is under screen reflash skip this\n"));
        return MENUR_OK;
    }

    c_sema_lock(h_sema_blank_screen_mtx,X_SEMA_OPTION_WAIT);

    if (!menu_custom_is_blank_screen())
    {
        DBG_LOG_PRINT(("[MENU][BLANK_SCREEN][%s %d]\n", __FUNCTION__,__LINE__));
        menu_custom_set_blank_scrn(TRUE);
        if(a_menu_is_resume())
        {
            menu_leave(FALSE,0);
        }

#ifdef APP_RETAIL_MODE_SUPPORT
        a_cfg_custom_get_retail_mode_setting(&t_g_retail_mode);

        if (ACFG_RETAIL_MODE_NORMAL == t_g_retail_mode)
        {
            a_nav_retail_mode_pause_demo();
        }
#endif
        a_tv_net_send_cmd("\n:am,am,:disable_keyroute\n");
        a_amb_enable_system_key(FALSE);
        //c_sema_lock(h_sema_blank_screen_mtx,X_SEMA_OPTION_WAIT);
        MENU_LOG_ON_FAIL(a_cfg_cust_blank_screen());

        a_nav_power_set_component_enable(TRUE);

        #ifdef APP_LED_LOGO_CTRL
        ui1_old_led_ctrl = a_cfg_custom_get_led_logo_ctrl();
        a_cfg_custom_set_led_logo_ctrl_to_drv(1);
        #endif

        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
        MENU_LOG_ON_FAIL(i4_ret);

        DBG_LOG_PRINT(("blank screen ,prevent airplay from receiving key\n"));
        _menu_prevent_airplay_get_rc_key(); //dolphin 20190516 CR-ID: DTV01566212

        if (!b_oled)
        {
            DBG_LOG_PRINT(("[MENU][BLANK_SCREEN][%s %d]mute video for blank screen\n", __FUNCTION__,__LINE__));
            //APPTV_DEBUG_WHO_CALL_MUTE(0, TV_VIDEO_MUTE_MASK_RESET, TRUE);
            A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_MENU, h_g_acfg_svctx_main, TV_VIDEO_MUTE_MASK_RESET, TRUE);

            //APPTV_DEBUG_WHO_CALL_MUTE(1, TV_VIDEO_MUTE_MASK_RESET, TRUE);
            A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_MENU, h_g_acfg_svctx_sub, TV_VIDEO_MUTE_MASK_RESET, TRUE);
        }

		a_cfg_get_dpms(&b_dpms);
        if (t_blk_mode == BLK_SCRN_OLED_STILL_IMAGE
            || (BLK_SCRN_OLED_NO_SIGNAL == t_blk_mode && b_dpms == FALSE)
            || BLK_SCRN_OLED_SMART_UI == t_blk_mode)
        {
            if (_menu_custom_check_audio_sync() == FALSE)
            {
                menu_oled_pro_auto_pwr_off_timer_start();
            }
            menu_oled_pro_audio_check_timer_start();
        }
    }
    else
    {
        DBG_INFO(("[MENU][BLANK_SCREEN][%s %d]it is under blank_screen,ignore!!!\n", __FUNCTION__,__LINE__));
    }

    c_sema_unlock(h_sema_blank_screen_mtx);

    return i4_ret;
}

VOID menu_custom_set_blank_scrn_mode(MENU_CUSTOM_BLK_SCRN_MODE t_mode)
{
    t_blk_crn_mode = t_mode;
}

MENU_CUSTOM_BLK_SCRN_MODE menu_custom_get_blank_scrn_mode(VOID)
{
    return t_blk_crn_mode;
}



static VOID _menu_custom_oled_pro_audio_check_timer_nfy_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    DBG_LOG_PRINT(("[OLED PROTECT] %s %d\n",__FUNCTION__,__LINE__));
    if (_menu_custom_check_audio_sync())
    {
        if (b_oled_pro_auto_pwr_off_timer_start == TRUE)
        {
            menu_oled_pro_auto_pwr_off_timer_stop();
        }
    }
    else
    {
        if (b_oled_pro_auto_pwr_off_timer_start == FALSE)
        {
            menu_oled_pro_auto_pwr_off_timer_start();
        }
    }
}

static VOID _menu_custom_oled_pro_audio_check_timer_nfy_cb(
    HANDLE_T                  h_timer,
    VOID*                     pv_ver)
{
    menu_async_invoke(_menu_custom_oled_pro_audio_check_timer_nfy_fct, NULL, 0, FALSE);
}




static VOID _menu_custom_oled_pro_auto_pwr_off_timer_nfy_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    DBG_LOG_PRINT(("[OLED PROTECT] %s %d start\n",__FUNCTION__,__LINE__));
    /*Power down only*/
	a_cfg_custom_set_drv_bgmupdate_flag(1);
    AP_SYSTEM_CALL("reboot");
    DBG_LOG_PRINT(("[OLED PROTECT] %s % end\n",__FUNCTION__,__LINE__));
    b_oled_pro_auto_pwr_off_timer_start = FALSE;
}
static VOID _menu_custom_oled_pro_auto_pwr_off_timer_nfy_cb(
    HANDLE_T                  h_timer,
    VOID*                     pv_ver)
{
    menu_async_invoke(_menu_custom_oled_pro_auto_pwr_off_timer_nfy_fct, NULL, 0, FALSE);
}

VOID menu_custom_blank_screen_set_block_power_off(BOOL b_flag)
{
    b_blank_screen_block_pwr_off = b_flag;
}

BOOL menu_custom_blank_screen_get_block_power_off(VOID)
{
    return b_blank_screen_block_pwr_off;
}

BOOL menu_custom_blank_screen_is_oled_toast_show(VOID)
{
    UINT32 t = c_os_get_sys_tick() * c_os_get_sys_tick_period();

    DBG_LOG_PRINT(("[OLED PROTECT] %s ms = %d - %d\n",__FUNCTION__, (UINT32)t, (UINT32)_ui4_blank_oled_toast_show_time));

    return (t - _ui4_blank_oled_toast_show_time < OLED_TOAST_CHECK_TIME);
}

static BOOL _menu_custom_is_factory_mode_on(VOID)
{
    UINT8              ui1_factory_mode = 0;
    MENU_LOG_ON_FAIL(a_cfg_get_factory_mode (& ui1_factory_mode));
    return (APP_CFG_FAC_MODE_BURNING_MASK & ui1_factory_mode) != 0;
}

static VOID _menu_custom_blank_scrn_timer_nfy_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    static ACFG_RETAIL_MODE_T   t_retail_mode = ACFG_RETAIL_MODE_HOME;

    h_blank_oled_screen_timer_start = FALSE;

    if (_menu_custom_is_factory_mode_on())
    {
        DBG_LOG_PRINT(("[OLED PROTECT]  %s %d burning mode is on, not allow\n",__FUNCTION__,__LINE__));
        return MENUR_OK;
    }

    DBG_LOG_PRINT(("[OLED PROTECT] %s %d\n",__FUNCTION__,__LINE__));

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (nav_is_channel_scan_active() || ACFG_RETAIL_MODE_NORMAL == t_retail_mode
#ifndef LINUX_TURNKEY_SOLUTION
        || nav_is_component_visible(NAV_COMP_ID_UPG)
#else
        ||nav_is_component_visible(NAV_COMP_ID_UPDATER)
#endif
        )
    {
        DBG_INFO(("[blank screen]%s %d channel_scan_active or demo mode running, do nothing\n",__FUNCTION__,__LINE__));
        menu_custom_set_blank_scrn_mode(BLK_SCRN_NORMAL);
        return;
    }

    a_menu_hot_key_handler(BTN_BLANK_SCREEN,
                           WGL_MSG_KEY_DOWN,
                           NULL);

}
static VOID _menu_custom_blank_scrn_timer_nfy_cb(
    HANDLE_T                  h_timer,
    VOID*                     pv_ver)
{
    menu_async_invoke(_menu_custom_blank_scrn_timer_nfy_fct, NULL, 0, FALSE);
}

static VOID _menu_custom_blank_scrn_toast_timer_nfy_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    static ACFG_RETAIL_MODE_T   t_retail_mode = ACFG_RETAIL_MODE_HOME;

    _b_blank_oled_toast_timer_start = FALSE;

    if (_menu_custom_is_factory_mode_on())
    {
        return;
    }
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (nav_is_channel_scan_active() || ACFG_RETAIL_MODE_NORMAL == t_retail_mode
#ifndef LINUX_TURNKEY_SOLUTION
        || nav_is_component_visible(NAV_COMP_ID_UPG)
#else
        ||nav_is_component_visible(NAV_COMP_ID_UPDATER)
#endif
        )
    {
        return;
    }
    HANDLE_T h_canvas;

    if(!_b_blank_oled_toast_create && (menu_pm_get_canvas(&h_canvas) == MENUR_OK))
    {
        TOAST_INIT_PARAM_T t_toast_init;
        c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
        t_toast_init.e_toast_style = TOAST_STYLE_MSG;
        t_toast_init.h_canvas = h_canvas;
        t_toast_init.t_custom_setting.u.t_msg_init.e_msg_type = TOAST_MSG_TYPE_WITH_WARNING_ICON;

        if(a_toast_create(&t_toast_init, &_h_toast_blank_scrn) == TOASTR_OK)
        {
            _b_blank_oled_toast_create = TRUE;
        }
    }
    if(_b_blank_oled_toast_create)
    {
        UTF16_T w2s_tmp_str[128] = {0};
        c_uc_w2s_strcpy(w2s_tmp_str,MENU_TEXT(MLM_MENU_KEY_OLED_SCREEN_BLANK_NOTIFY));

        TOAST_CUSTOMIZATION_DATA_T t_custom_data;
        c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));

        t_custom_data.u.t_msg_init.w2s_msg_str = w2s_tmp_str;

        _b_blank_oled_toast_show = TRUE;

        _ui4_blank_oled_toast_show_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

        DBG_LOG_PRINT(("[OLED PROTECT] %s ms=%d\n",__FUNCTION__, (UINT32)_ui4_blank_oled_toast_show_time));

        a_toast_show(_h_toast_blank_scrn, &t_custom_data);
    }
}

static VOID _menu_custom_blank_scrn_toast_timer_nfy_cb(
    HANDLE_T                  h_timer,
    VOID*                     pv_ver)
{
    menu_async_invoke(_menu_custom_blank_scrn_toast_timer_nfy_fct, NULL, 0, FALSE);
}

static BOOL _menu_custom_oobe_mode(VOID)
{
    INT32   i4_ret = 0;
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    i4_ret = a_cfg_get_wzd_status(&ui2_status);
    if (APP_CFGR_OK != i4_ret)
    {
        return FALSE;
    }
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    if(WZD_STATE_RESUME_C4TV == ui1_state)
    {
        menu_custom_set_blank_scrn_mode(BLK_SCRN_NORMAL);
        return TRUE;
    }
    return FALSE;
}

extern void a_cfg_custom_oled_bypass_img_still(BOOL bBypass);

INT32 menu_blank_oled_scrn_timer_start(VOID)
{

    if (b_oled == FALSE) return MENUR_OK;
    if (_menu_custom_is_factory_mode_on())
    {
        DBG_LOG_PRINT(("[OLED PROTECT]  %s %d burning mode is on, not allow\n",__FUNCTION__,__LINE__));
        return MENUR_OK;
    }
    if (h_blank_oled_screen_timer_start)
    {
        MENU_LOG_ON_FAIL(c_timer_stop(h_blank_oled_screen_timer));
    }
    else
    {
        h_blank_oled_screen_timer_start = TRUE;
    }
    if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_NO_SIGNAL)
    {
        ui4_blank_oled_scrn_delay = BLK_SCRN_OLED_NO_SIGNAL_DELAY;
        DBG_LOG_PRINT(("[OLED PROTECT]  %s %d BLK_SCRN_OLED_NO_SIGNAL ui4_blank_oled_scrn_delay = %d\n",__FUNCTION__,__LINE__, ui4_blank_oled_scrn_delay));
    }
    else if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_STILL_IMAGE)
    {
        ui4_blank_oled_scrn_delay = BLK_SCRN_OLED_STILL_IMAGE_DELAY;
        DBG_LOG_PRINT(("[OLED PROTECT]  %s %d BLK_SCRN_OLED_STILL_IMAGE ui4_blank_oled_scrn_delay = %d\n",__FUNCTION__,__LINE__, ui4_blank_oled_scrn_delay));
    }
    else if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_OLED_SMART_UI)
    {
        ui4_blank_oled_scrn_delay = BLK_SCRN_OLED_SMART_UI_DELAY;
        DBG_LOG_PRINT(("[OLED PROTECT] %s %d BLK_SCRN_OLED_SMART_UI ui4_blank_oled_scrn_delay = %d\n",__FUNCTION__,__LINE__, ui4_blank_oled_scrn_delay));
    }

    if(_b_blank_oled_toast_show)
    {
        a_toast_hide(_h_toast_blank_scrn);

        _b_blank_oled_toast_show = FALSE;
    }
    if (_b_blank_oled_toast_timer_start)
    {
        if(c_timer_stop(_h_blank_oled_toast_timer) == OSR_OK)
        {
            _b_blank_oled_toast_timer_start = FALSE;
        }
    }
    if(ui4_blank_oled_scrn_delay > BLK_SCRN_OLED_TOAST_NTY)
    {
        if( c_timer_start(_h_blank_oled_toast_timer,
                           ui4_blank_oled_scrn_delay - BLK_SCRN_OLED_TOAST_NTY,
                           X_TIMER_FLAG_ONCE,
                           _menu_custom_blank_scrn_toast_timer_nfy_cb,
                           NULL) == OSR_OK)
        {
            _b_blank_oled_toast_timer_start = TRUE;
        }
    }
    // ui4_blank_oled_scrn_delay = ui4_blank_oled_scrn_delay / 5;
    return c_timer_start(h_blank_oled_screen_timer,
                           ui4_blank_oled_scrn_delay,
                           X_TIMER_FLAG_ONCE,
                           _menu_custom_blank_scrn_timer_nfy_cb,
                           NULL);
}

INT32 menu_blank_oled_scrn_timer_refresh(VOID)
{
    if (b_oled == FALSE || h_blank_oled_screen_timer_start == FALSE) return MENUR_OK;
    if(_b_blank_oled_toast_show)
    {
        a_toast_hide(_h_toast_blank_scrn);

        _b_blank_oled_toast_show = FALSE;
    }
    if (_b_blank_oled_toast_timer_start)
    {
        if(c_timer_stop(_h_blank_oled_toast_timer) == OSR_OK)
        {
            _b_blank_oled_toast_timer_start = FALSE;
        }
    }
    if(ui4_blank_oled_scrn_delay > BLK_SCRN_OLED_TOAST_NTY)
    {
        if( c_timer_start(_h_blank_oled_toast_timer,
                           ui4_blank_oled_scrn_delay - BLK_SCRN_OLED_TOAST_NTY,
                           X_TIMER_FLAG_ONCE,
                           _menu_custom_blank_scrn_toast_timer_nfy_cb,
                           NULL) == OSR_OK)
        {
            _b_blank_oled_toast_timer_start = TRUE;
        }
    }
    a_cfg_custom_oled_bypass_img_still(FALSE);
    MENU_LOG_ON_FAIL(c_timer_stop(h_blank_oled_screen_timer));
    DBG_LOG_PRINT(("[OLED PROTECT] %s %d modo = %d\n",__FUNCTION__,__LINE__,
        menu_custom_get_blank_scrn_mode()));
    return c_timer_start(h_blank_oled_screen_timer,
                           ui4_blank_oled_scrn_delay,
                           X_TIMER_FLAG_ONCE,
                           _menu_custom_blank_scrn_timer_nfy_cb,
                           NULL);
}

BOOL menu_custom_blank_oled_scrn_timer_is_start(VOID)
{
    return h_blank_oled_screen_timer_start;
}

INT32 menu_blank_oled_scrn_timer_stop(VOID)
{
    if (b_oled == FALSE) return MENUR_OK;

    if(_b_blank_oled_toast_show)
    {
        a_toast_hide(_h_toast_blank_scrn);

        _b_blank_oled_toast_show = FALSE;
    }
    if (_b_blank_oled_toast_timer_start)
    {
        if(c_timer_stop(_h_blank_oled_toast_timer) == OSR_OK)
        {
            _b_blank_oled_toast_timer_start = FALSE;
        }
    }
    DBG_LOG_PRINT(("[OLED PROTECT] %s %d\n",__FUNCTION__,__LINE__));
    h_blank_oled_screen_timer_start = FALSE;
    a_cfg_custom_oled_bypass_img_still(FALSE);
    menu_custom_set_blank_scrn_mode(BLK_SCRN_NORMAL);

    return c_timer_stop(h_blank_oled_screen_timer);
}

INT32 menu_oled_pro_auto_pwr_off_timer_start(VOID)
{
    UINT32 ui4_timer_delay = OLED_AUTO_PWR_OFF_2;
    if (b_oled == FALSE) return MENUR_OK;
    if (b_oled_pro_auto_pwr_off_timer_start)
    {
        c_timer_stop(h_oled_pro_auto_pwr_off_timer);
    }
    else
    {
        b_oled_pro_auto_pwr_off_timer_start = TRUE;
    }

    // ui4_timer_delay = ui4_timer_delay / 10;
    DBG_LOG_PRINT(("[OLED PROTECT] %s %d dur = %d\n",__FUNCTION__,__LINE__, ui4_timer_delay));
    return c_timer_start(h_oled_pro_auto_pwr_off_timer,
                           ui4_timer_delay,
                           X_TIMER_FLAG_ONCE,
                           _menu_custom_oled_pro_auto_pwr_off_timer_nfy_cb,
                           NULL);
}

INT32 menu_oled_pro_audio_check_timer_stop(VOID)
{
    if (b_oled == FALSE) return MENUR_OK;

    DBG_LOG_PRINT(("[OLED PROTECT] %s %d\n",__FUNCTION__,__LINE__));
    b_oled_pro_audio_check_timer_start = FALSE;

    return c_timer_stop(h_oled_pro_audio_check_timer);
}


INT32 menu_oled_pro_audio_check_timer_start(VOID)
{
    if (b_oled == FALSE) return MENUR_OK;
    if (b_oled_pro_audio_check_timer_start)
    {
        c_timer_stop(h_oled_pro_audio_check_timer);
    }
    else
    {
        b_oled_pro_audio_check_timer_start = TRUE;
    }
    DBG_LOG_PRINT(("[OLED PROTECT] %s %d\n",__FUNCTION__,__LINE__));

    return c_timer_start(h_oled_pro_audio_check_timer,
                           OLED_AUDIO_CHECK_REPEAT,
                           X_TIMER_FLAG_REPEAT,
                           _menu_custom_oled_pro_audio_check_timer_nfy_cb,
                           NULL);
}



INT32 menu_oled_pro_auto_pwr_off_timer_stop(VOID)
{
    if (b_oled == FALSE) return MENUR_OK;

    DBG_LOG_PRINT(("[OLED PROTECT] %s %d\n",__FUNCTION__,__LINE__));
    b_oled_pro_auto_pwr_off_timer_start = FALSE;

    return c_timer_stop(h_oled_pro_auto_pwr_off_timer);
}

BOOL menu_oled_pro_auto_pwr_off_timer_is_start(VOID)
{
    return b_oled && b_oled_pro_auto_pwr_off_timer_start;
}


INT32 menu_custom_unblank_screen(UINT32 ui4_keycode)
{
    UINT32  i4_ret = MENUR_OK;
    extern BOOL a_am_is_system_key_enable (VOID);


    //DBG_LOG_PRINT(("[MENU][BLANK_SCREEN] menu_custom_unblank_screen(ui4_keycode=0x%X)---- \n",ui4_keycode ));

    if(ui4_keycode==BTN_BLANK_SCREEN)
    {
        DBG_INFO(("[MENU] Get Keycode %d(BTN_BLANK_SCREEN) ,ignore \n",ui4_keycode));
        return MENUR_OK;
    }

    c_sema_lock(h_sema_blank_screen_mtx,X_SEMA_OPTION_WAIT);

    if (menu_custom_is_blank_screen())
    {
        if(_b_blank_oled_toast_show)
        {
            a_toast_hide(_h_toast_blank_scrn);

            _b_blank_oled_toast_show = FALSE;
        }
       CHAR s_active_app[64] = {0};
       DBG_LOG_PRINT(("[MENU][BLANK_SCRRENT][%s %d]\n", __FUNCTION__,__LINE__));
       if(a_is_oled_compensation_support() && a_oled_compensation_is_running())
       {
           DBG_LOG_PRINT(("[MENU]TV is under screen reflash skip this\n"));
           return MENUR_OK;
       }

        menu_custom_set_blank_scrn(FALSE);

        a_tv_net_send_cmd("\n:am,am,:enable_keyroute\n");
        if (!_menu_custom_oobe_mode())
        {
            DBG_INFO(("[blank screen]%s %d in oobe, do not enable system key\n",__FUNCTION__,__LINE__));
            a_amb_enable_system_key(TRUE);
        }
        //c_sema_lock(h_sema_blank_screen_mtx,X_SEMA_OPTION_WAIT);
        MENU_LOG_ON_FAIL(a_cfg_cust_unblank_screen());
        a_am_get_active_app(s_active_app);
        if(c_strlen(s_active_app) > 0 && 0 == c_strcmp(s_active_app,"menu"))
            a_amb_pause_app("menu");
        //c_sema_unlock(h_sema_blank_screen_mtx);
        a_nav_power_set_component_enable(TRUE);

        #ifdef APP_LED_LOGO_CTRL
        a_cfg_custom_update_led_logo_ctrl();

        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));
        MENU_LOG_ON_FAIL(i4_ret);
        #endif
        menu_oled_pro_audio_check_timer_stop();
        menu_oled_pro_auto_pwr_off_timer_stop();

#ifdef APP_RETAIL_MODE_SUPPORT
        if (ACFG_RETAIL_MODE_NORMAL == t_g_retail_mode)
        {
            a_nav_retail_mode_resume_demo(FALSE);
        }
#endif

        DBG_INFO(("unblank ,allow airplay to get rc key\n"));
        if (h_file_flag_timer != NULL_HANDLE)
        {
            c_timer_start(h_blank_screen_flag_timer,
                      MENU_BLANK_SCREEN_FILE_FLAG_DELAY,
                      X_TIMER_FLAG_ONCE ,
                      _menu_allow_airplay_get_rc_key , /* menu&airplay will call key at the same time ,so we need to delay to wait for key disapear */
                      NULL);
        }

        if (a_acfg_get_still_image_status() == ACFG_OLED_ERR_EVENT_GSP_IMG_STILL)
        {
            menu_custom_set_blank_scrn_mode(BLK_SCRN_OLED_STILL_IMAGE);
            menu_blank_oled_scrn_timer_start();
        }
        else
        {
            menu_custom_set_blank_scrn_mode(BLK_SCRN_NORMAL);
        }
        if (!b_oled)
        {
            DBG_LOG_PRINT(("[MENU][BLANK_SCREEN][%s %d]unmute video for unblank screen\n", __FUNCTION__,__LINE__));
            //APPTV_DEBUG_WHO_CALL_MUTE(0, TV_VIDEO_MUTE_MASK_RESET, FALSE);
            A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_MENU, h_g_acfg_svctx_main, TV_VIDEO_MUTE_MASK_RESET, FALSE);

            //APPTV_DEBUG_WHO_CALL_MUTE(1, TV_VIDEO_MUTE_MASK_RESET, FALSE);
            A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_MENU, h_g_acfg_svctx_sub, TV_VIDEO_MUTE_MASK_RESET, FALSE);
        }
    }
    else
    {
        DBG_INFO(("[MENU][BLANK_SCREEN][%s %d]it is unblank_screen,ignore!!!\n", __FUNCTION__,__LINE__));
    }

    c_sema_unlock(h_sema_blank_screen_mtx);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_system_key_cb
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
BOOL menu_custom_system_key_cb (UINT32 ui4_evt_code)
{
    UINT32  ui4_key_code = IOM_GET_EVT_GRP_ID(ui4_evt_code);
    INT32              i4_rc;
    #ifndef APP_EPG_SUPPORT
    //TV_WIN_ID_T        e_focus_wnd;
    //ISL_REC_T          t_isl_rec;
    #endif
    BOOL               b_is_main_menu_visible = TRUE;
    HANDLE_T           h_main_frm;

    UINT32             ui4_pageid;
    BOOL               b_sleep_dlg_show = FALSE;

#ifdef APP_CAST_TEST_PATTERN
    UINT8  ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    a_icl_custom_get_test_pattern_status(&ui1_val);

    if(ui1_val != ICL_RECID_TEST_PATTERN_STATUS_DISABLE)
    {
        if (BTN_POWER == ui4_key_code || BTN_POWER_OFF == ui4_key_code)
        {
            /* exit pattern can't select svctx when in menu by power off/on*/
            a_menu_exit_test_patterns_by_power();
        }
        else if(BTN_MENU == ui4_key_code)
        {
            a_menu_test_patterns_turn_off();
        }
    }
#endif

    DBG_INFO(("[MENU][%s %d] ui4_evt_code = 0x%x\n",__FUNCTION__,__LINE__,ui4_evt_code));
    a_nav_get_sleep_prompt_dlg_status(&b_sleep_dlg_show);
    menu_blank_oled_scrn_timer_refresh();

    if (menu_custom_is_blank_screen())
    {

        if ((BTN_POWER == ui4_key_code || BTN_POWER_OFF == ui4_key_code)
            && ((IOM_GET_EVT_SRC(ui4_evt_code) == KEY_SRC_FRONT_PANEL)
            || b_sleep_dlg_show
            || nav_is_component_visible(NAV_COMP_ID_POWER)))
        {
            return TRUE;
        }


        menu_nav_get_crnt_page(&ui4_pageid);

        menu_custom_unblank_screen(ui4_evt_code);

        if (ui4_pageid == ui4_g_menu_page_blank_scrn)
        {
            menu_nav_back();
        }

        return FALSE;
    }
#ifndef APP_EPG_SUPPORT
    if (ui4_key_code == BTN_EPG)
    {
        #ifdef APP_MENU_MMP_COEXIST
            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                return FALSE;
            }
        #endif
        ui4_key_code = BTN_PRG_INFO;

        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
        return TRUE;
    }
#endif
    /**************************************************************/
#ifdef APP_MENU_MMP_COEXIST
    menu_pm_get_main_frm(&h_main_frm);
    i4_rc = c_wgl_get_visibility(h_main_frm, &b_is_main_menu_visible);
    if (i4_rc != WGLR_OK)
    {
        b_is_main_menu_visible = TRUE;
    }

    if  ((BTN_MENU == ui4_key_code) &&
         (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()) &&
         (b_is_main_menu_visible == TRUE))
    {
        /* Multimedia */
        a_amb_resume_app(MMP_NAME);
        return FALSE;
    }
#endif
    if (ui4_key_code == BTN_MENU)
    {
        UINT32    ui4_cnt_page = 0;
        menu_nav_get_crnt_page(&ui4_cnt_page);
        if (ui4_cnt_page == ui4_g_menu_page_scr_mode)
        {
            if (t_g_menu_common.b_is_hot_key_enter == TRUE)
            {
                menu_pm_hide();
                t_g_menu_common.b_is_hot_key_enter = FALSE;
                #ifdef LINUX_TURNKEY_SOLUTION
                a_msg_convert_resume_tv_sidebar();
                #endif
                menu_pm_show();

                a_cfg_set_app_status(APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
                a_cfg_update_viewport();

                return FALSE;
            }
            else
            {
                if ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == a_mmp_be_get_browser_status())
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status()))
                {
                    a_amb_resume_app(MMP_NAME);
                    return FALSE;
                }
            }

        }
        else if (ui4_cnt_page == ui4_g_menu_page_3D_setting)
        {
            if (t_g_menu_common.b_is_hot_key_enter == TRUE)
            {
                menu_pm_hide();
                t_g_menu_common.b_is_hot_key_enter = FALSE;
                menu_pm_show();

                a_cfg_set_app_status(APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
                a_cfg_update_viewport();

                return FALSE;
            }
            else
            {
                if ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == a_mmp_be_get_browser_status())
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status()))
                {
                    a_amb_resume_app(MMP_NAME);
                    return FALSE;
                }
            }
        }
        else if((ui4_g_menu_page_mmp_dev_list == ui4_cnt_page)||
                (ui4_g_menu_page_mmp_media_type == ui4_cnt_page))
        {
            menu_async_invoke(_menu_custom_system_key_menu_fct, NULL, 0, TRUE);
            return FALSE;
        }
        else if (ui4_cnt_page == ui4_g_menu_page_cust_setting)
        {
            if (t_g_menu_common.b_is_hot_key_enter == TRUE)
            {
                menu_pm_hide();
                t_g_menu_common.b_is_hot_key_enter = FALSE;
                menu_pm_show();

                a_cfg_set_app_status(APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
                a_cfg_update_viewport();

                return FALSE;
            }
        }
        else if (ui4_cnt_page == ui4_g_menu_page_vid)
        {
            if (t_g_menu_common.b_is_hot_key_enter == TRUE)
            {
                t_g_menu_common.b_is_hot_key_enter = FALSE;
                return FALSE;
            }
            else
            {
            #ifdef APP_MENU_MMP_COEXIST
                if ((BTN_MENU == ui4_key_code) &&
                     (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()))
                {
                    /* Multimedia */
                    a_amb_resume_app(MMP_NAME);
                    return FALSE;
                }
            #endif

            }
        }
        else
        {
        #ifdef APP_MENU_MMP_COEXIST
            if ((BTN_MENU == ui4_key_code) &&
                 (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()))
            {
                /* Multimedia */
                a_amb_resume_app(MMP_NAME);
                return FALSE;
            }
        #endif
        }
    }

    return TRUE;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_pre_init
 *
 * Description:
 *      This function is called before the most the menu components init. It can
 *  put the resource, colors, images, fonts, and etc.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_custom_pre_init(VOID)
{
    #define MENU_FONT_NAME  APP_FONT_MENU_NAME

    /* init font */
    INT32 i4_ret;

    if(!c_fe_has_font(MENU_FONT_NAME, FE_FNT_STYLE_UNIFORM))
    {
#if !defined(APP_USE_BDF_FONT)
         i4_ret = c_fe_add_mem_font(MENU_FONT_NAME,
                                    &(font_file_default [4]),
                                    GET_UINT32_FROM_PTR_BIG_END (&(font_file_default [0])),
                                    FONT_SIZE_SMALL,
                                    FONT_SIZE_MEDIUM,
                                    FONT_SIZE_LARGE);
#else
        i4_ret = c_fe_add_combine_bmp_mem_font(MENU_FONT_NAME,
                                       &(font_file_tiresias_bdf_18 [4]),
                                       GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_18 [0])),
                                       &(font_file_tiresias_bdf_18 [4]),
                                       GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_18 [0])),
                                       &(font_file_tiresias_bdf_22 [4]),
                                       GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_22 [0])));
#endif
        if(i4_ret != FER_OK)
        {
            DBG_ERROR(("<MENU>Can't init font\n"));
            return MENUR_FAIL;
        }
    }

    menu_set_font_name(MENU_FONT_NAME);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_init
 *
 * Description:
 *      This function is called after menu core-layer init. Call all the custom
 *  components init here. And init the solution-specific layer init here.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_custom_init(VOID)
{
    INT32       i4_ret;

    i4_ret = menu_common_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_atsc_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_device_init();
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_NETWORK_SUPPORT
    i4_ret = menu_network_init();
    MENU_CHK_FAIL(i4_ret);
#endif

    i4_ret = menu_custom_page_3D_setting_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_vid_position_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_vid_size_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_custom_page_mmp_dev_list_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_custom_page_mmp_media_type_init();
    MENU_CHK_FAIL(i4_ret);

    #ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
    i4_ret =   menu_custom_page_time_local_setting_auto_dst_init();
    MENU_CHK_FAIL(i4_ret);
    #else
    i4_ret =   menu_custom_page_time_local_setting_init();
    MENU_CHK_FAIL(i4_ret);
    #endif

    i4_ret = menu_custom_settings_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_custom_hierarchy_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_custom_dialog_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_GUI_LANG,
                              NULL,
                              _cfg_gui_lang_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_gl_nfy);
    MENU_CHK_FAIL(i4_ret);

    _do_chg_lang(NULL, 0);

    i4_ret = c_svctx_set_listener(t_g_menu_common.h_svctx,
                                  _svctx_notify_fct,
                                  NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_svctx_set_listener(t_g_menu_common.h_svctx_sub,
                                  _svctx_notify_fct,
                                  NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_INPUT_SRC,
                              NULL,
                              _cfg_chk_tv_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_inp_src_nfy);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_NAV,
                              NULL,
                              _cfg_chk_tv_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_nav_nfy);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_AUDIO,
                              NULL,
                              _cfg_av_chg_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_audio_nfy);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_VIDEO,
                              NULL,
                              _cfg_av_chg_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_video_nfy);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_DISP,
                              NULL,
                              _cfg_av_chg_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_disp_nfy);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_CC,
                              NULL,
                              _cfg_av_chg_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_cc_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_DCS,
                              NULL,
                              _cfg_av_chg_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_cc_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_CUSTOM_BASE,
                              NULL,
                              _cfg_av_chg_nfy_fct,
                              &t_g_menu_custom.ui2_acfg_custom_base_nfy);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_RECID_CEC_SAC_STATUS,
                              NULL,
                              NULL,
                              _cec_aud_nfy_func,
                              &t_g_menu_custom.ui2_icl_aud_nfy);

    MENU_CHK_FAIL(i4_ret);
    i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_RECID_CEC_SAC_DDP,
                              NULL,
                              NULL,
                              _cec_ddp_nfy_func,
                              &t_g_menu_custom.ui2_icl_ddp_nfy);

    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_icl_notify_reg(APP_CFG_GRPID_CUST_MISC_BASE,
                              APP_CFG_RECID_CUST_TV_NAME,
                              NULL,
                              NULL,
                              _menu_tv_name_change_fct,
                              &t_g_menu_custom.ui2_acfg_tv_name_nfy);

    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_icl_notify_reg(ICL_GRPID_HDR_TYPE_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _menu_hdr_change_fct,
                              &t_g_menu_custom.ui2_acfg_hdr_nfy);

    MENU_CHK_FAIL(i4_ret);

    if(!a_appl_splayer_init())
    {
        DBG_LOG_PRINT(("[MENU] [%d][%s] MM init FAIL \n", __LINE__, __FUNCTION__));
    }

    i4_ret = _menu_hot_key_register();
    MENU_CHK_FAIL(i4_ret);

    c_timer_create(&h_file_flag_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    c_timer_create(&h_blank_screen_flag_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_timer_repaint);
    MENU_LOG_ON_FAIL(i4_ret);

    if(h_timer_show == NULL_HANDLE)
    {
        c_timer_create(&h_timer_show);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    MENU_LOG_ON_FAIL(c_sema_create(&h_sema_blank_screen_mtx,
                           X_SEMA_TYPE_MUTEX,
                           X_SEMA_STATE_UNLOCK));

    b_oled = a_is_oled_compensation_support();

    if (b_oled == TRUE)
    {
        i4_ret = c_timer_create(&h_blank_oled_screen_timer);
        if(i4_ret != OSR_OK)
        {
            DBG_ERROR(("<MENU>Can't create timer\r\n"));
        }
		i4_ret = c_timer_create(&h_oled_pro_auto_pwr_off_timer);
        if(i4_ret != OSR_OK)
        {
            DBG_ERROR(("<MENU>Can't create timer\r\n"));
        }
        i4_ret = c_timer_create(&h_oled_pro_audio_check_timer);
        if(i4_ret != OSR_OK)
        {
            DBG_ERROR(("<MENU>Can't create timer\r\n"));
        }
        i4_ret = c_timer_create(&_h_blank_oled_toast_timer);
        if(i4_ret != OSR_OK)
        {
            DBG_ERROR(("<MENU>Can't create timer\r\n"));
        }
    }
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_custom_update_the_old_display_region_after_change_source_tv
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
INT32 menu_custom_update_the_old_display_region_after_change_source_tv(VOID)
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_resume
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
INT32 menu_custom_resume(VOID)
{
    INT32       i4_ret;
    UINT8       ui1_status = 0;

    //b_old_ipcc_visible = nav_ci_get_ipcc_visible();
    nav_ci_set_ipcc_visible(FALSE);

#ifdef APP_MENU_MMP_COEXIST
    MSGCVT_VIEWPORT_T t_viewport;

    if (a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_status) == ICLR_OK
        && (YAHOO_STATUS_DOCK_UP & ui1_status) != 0
        && t_g_menu_common.b_is_hot_key_enter
        && t_g_menu_common.ui4_key_code == BTN_ASPECT)
    {
        /* do nothing */
    }
    else
    {
        a_msg_convert_get_viewport(&t_viewport);
        a_cfg_custom_recover_viewport_by_tv(t_viewport.i_viewportmode);
    }
#endif
    menu_doly_vision_logo_show(FALSE);

    i4_ret = menu_common_resume();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_atsc_resume();
    MENU_CHK_FAIL(i4_ret);
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);
    close(open("/tmp/sidebar_menu_show", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));

    return MENUR_OK;
}
#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _connection_is_ok
 *
 * Description: check the connection is ok or not
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 1: connection is ok
 *            other wise: connection is not ok
 ----------------------------------------------------------------------------*/
BOOL menu_manual_in_flash(VOID)
{
    BOOL b_is_manual_in_flash = FALSE;

    b_is_manual_in_flash = (access("/data/e_manual/test_manual/index.htm", 0) == 0 ? TRUE : FALSE);

    return b_is_manual_in_flash;
}
#endif
#endif

static VOID _menu_file_flag_timer_nty(HANDLE_T h_timer, VOID *pv_tag)
{
    unlink("/tmp/sidebar_menu_show");
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_pause
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
INT32 menu_custom_pause(VOID)
{
    INT32   i4_ret = MENUR_OK;

    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);
    //menu_custom_unblank_screen();
    a_icl_set_picture_edit_type_status(ICL_PICTURE_EDIT_INVALID);

    i4_ret = menu_common_pause();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_atsc_pause();
    MENU_LOG_ON_FAIL(i4_ret);

    nav_ci_set_ipcc_visible(b_old_ipcc_visible);

#ifdef APP_MENU_MMP_COEXIST
    MMP_MAIN_AP_STATUS_T    e_mmp_status = MMP_MAIN_AP_STATUS_DEINITED;

    /*adjust MMP is or not active in the backgroud*/
    e_mmp_status = a_mmp_get_ap_status();

    if((MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status) || (MMP_MAIN_AP_STATUS_PAUSING == e_mmp_status))
    {
        if((MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status))
        {
            RMV_DEV_CHECK_RESULT_T e_check_result = a_rmv_dev_check_device();

            if ((RMV_DEV_FOUND_USB_DEVICE == e_check_result)||(RMV_DEV_FOUND_DLNA_DEVICE == e_check_result))
            {
                  /* if start user manual pause mmp */
                  if(menu_get_start_user_manual_flag())
                  {
                      a_mmp_pause_background_mmp();

                      HANDLE_T    h_frm_main = NULL_HANDLE;
                      i4_ret = menu_pm_get_main_frm(&h_frm_main);
                      MENU_LOG_ON_FAIL(i4_ret);

                      i4_ret = c_wgl_float(h_frm_main, FALSE, FALSE);
                      MENU_LOG_ON_FAIL(i4_ret);
                  }
                  else if(a_wzd_is_oobe_mode())
                  {
                      /* DTV00869742 not reusme mmp when mmp & menu to launch OOBE */
                      a_mmp_pause_background_mmp();
                  }
                 else if(BTN_NETFLIX      != ui4_g_delay_proc_input_key &&
                         BTN_VUDU         != ui4_g_delay_proc_input_key &&
                         BTN_MGO          != ui4_g_delay_proc_input_key &&
                         BTN_IHEART_RADIO != ui4_g_delay_proc_input_key &&
                         BTN_WATCHFREE    != ui4_g_delay_proc_input_key &&
                         BTN_REDBOX       != ui4_g_delay_proc_input_key &&
                         BTN_HAYSTACK     != ui4_g_delay_proc_input_key &&
                         BTN_WIDGET       != ui4_g_delay_proc_input_key &&
                         BTN_AMAZON       != ui4_g_delay_proc_input_key &&
                         BTN_XUMO         != ui4_g_delay_proc_input_key &&
                         BTN_CRACKLE      != ui4_g_delay_proc_input_key &&
                         BTN_HULU         != ui4_g_delay_proc_input_key)
                  { /*hot key with case mmp menu exist  should not luanch mmp*/

                      a_amb_resume_app(MMP_NAME);
                  }
            }
        }
        else if((MMP_MAIN_AP_STATUS_PAUSING == e_mmp_status))
        {
              HANDLE_T    h_frm_main = NULL_HANDLE;
              i4_ret = menu_pm_get_main_frm(&h_frm_main);
              MENU_LOG_ON_FAIL(i4_ret);

              i4_ret = c_wgl_float(h_frm_main, FALSE, FALSE);
              MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        i4_ret = menu_hide_help_tip();
        MENU_LOG_ON_FAIL(i4_ret);
    }

#else
    i4_ret = menu_hide_help_tip();
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    if (menu_get_start_user_manual_flag())
    {
        menu_set_start_user_manual_flag(FALSE);
    }
    menu_show_hide_enger_start_icon(FALSE, FALSE);

    menu_doly_vision_logo_show(FALSE);

    menu_page_tree_set_list_state(FALSE);

    menu_custom_pp_set_pause_flag(TRUE);

    if (h_file_flag_timer != NULL_HANDLE)
    {
        c_timer_start(h_file_flag_timer,
                  MENU_PAGE_FILE_FLAG_DELAY,
                  X_TIMER_FLAG_ONCE ,
                  _menu_file_flag_timer_nty ,
                  NULL);
    }

#ifdef APP_CAST_TEST_PATTERN
    //DTV02164133
    //when oled wait test pattern more than 5 mim, test pattern and ui will turn off
    //when DUT recive AUDIO only signel for svc, also can turn off test pattern and ui
    UINT8  ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;
    a_icl_custom_get_test_pattern_status(&ui1_val);
    if(ui1_val != ICL_RECID_TEST_PATTERN_STATUS_DISABLE)
    {
        a_menu_test_patterns_turn_off();
    }
#endif

    MENU_LOG_ON_FAIL(menu_scrl_title_timer_stop());

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_exit
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
INT32 menu_custom_exit(VOID)
{
    INT32 i4_ret;

    i4_ret = menu_common_exit();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_atsc_exit();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_icl_notify_unreg(t_g_menu_custom.ui2_icl_aud_nfy);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_icl_notify_unreg(t_g_menu_custom.ui2_icl_ddp_nfy);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_MENU_CUSTOM_FACTORY_TREE
    i4_ret = menu_cust_fact_exit();
    MENU_CHK_FAIL(i4_ret);
#endif
    _menu_hot_key_unregister();

    if (h_timer_show != NULL_HANDLE)
    {
        i4_ret = c_timer_delete(h_timer_show);
        MENU_CHK_FAIL(i4_ret);

        h_timer_show = NULL_HANDLE;
    }

    return MENUR_OK;
}
static VOID _menu_custom_update_color_tune_fct(
                                    VOID*                       pv_tag1,
                                    VOID*                       pv_tag2,
                                    VOID*                       pv_tag3)
{
    a_color_tuner_update_value();
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_process_msg
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
INT32 menu_custom_process_msg (
            UINT32       ui4_type,
            const VOID*  pv_msg,
            SIZE_T       z_msg_len,
            BOOL*        pb_processed)
{
    INT32 i4_ret = MENUR_OK;
    BOOL b_processed;
    ACFG_RETAIL_MODE_T    t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    BOOL b_is_wide_mode;

#ifdef APP_MENU_MMP_COEXIST
    MMP_MAIN_AP_STATUS_T    e_mmp_status = MMP_MAIN_AP_STATUS_DEINITED;
#endif

    /* custom */
    b_processed = FALSE;
    switch (ui4_type)
    {
    case MENU_MSG_WGL_NOTIFY:
        {
            MENU_MSG_WGL_NOTIFY_T* pt_msg_wgl_notify = (MENU_MSG_WGL_NOTIFY_T*)pv_msg;

            if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN ||
                pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_REPEAT)
            {
                UINT32 ui4_keycode = (UINT32)pt_msg_wgl_notify->pv_param1;
                ui4_keycode = IOM_GET_EVT_GRP_ID (ui4_keycode);
                UINT32 ui4_pageid = 0;

                MENU_DEBUG_KEY(
                    DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_keycode:0x%X\n", __FUNCTION__, __LINE__, ui4_keycode )); );


                menu_blank_oled_scrn_timer_refresh();

                if (menu_custom_is_blank_screen()
                    && ui4_keycode != BTN_VOL_UP
                    && ui4_keycode != BTN_VOL_DOWN
                    && ui4_keycode != BTN_MUTE)
                {
                    menu_nav_get_crnt_page(&ui4_pageid);

                    if (ui4_pageid == ui4_g_menu_page_blank_scrn)
                    {
                        if(ui4_keycode == BTN_WIDGET
                            || ui4_keycode == BTN_VUDU
                            || ui4_keycode == BTN_AMAZON
                            || ui4_keycode == BTN_XUMO
                            || ui4_keycode == BTN_CRACKLE
                            || ui4_keycode == BTN_HULU
                            || ui4_keycode == BTN_IHEART_RADIO
                            || ui4_keycode == BTN_NETFLIX
                            || ui4_keycode == BTN_WATCHFREE
                            || ui4_keycode == BTN_REDBOX
                            || ui4_keycode == BTN_HAYSTACK
                            || ui4_keycode == BTN_DISNEY
                            || ui4_keycode == BTN_PARTNER_2 // Peacock
                            || ui4_keycode == BTN_PARTNER_3 // Tubi
                            || ui4_keycode == BTN_PARTNER_4 // Pluto
                            || ui4_keycode == BTN_PARTNER_5)// HBOMAX
                        {
                             menu_nav_back();
                            *pb_processed = TRUE;   //eat hot key but not handle it, add for DTV00937675
                        }
                        else
                        {
                            *pb_processed = FALSE;
                        }
                    }
                    else
                    {
                        menu_custom_unblank_screen(ui4_keycode);
                        *pb_processed = TRUE;
                    }

                    return MENUR_OK;
                }

#ifdef APP_MENU_MMP_COEXIST
                if (BTN_PREV_PRG == ui4_keycode)
                {
                    e_mmp_status = a_mmp_get_ap_status();
                    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status)
                    {
                        ui4_keycode = BTN_EXIT;
                    }
                }

                if (FALSE == b_g_menu_mmp_coexist_allow_key)
                {
                    *pb_processed = TRUE;
                    return MENUR_OK;
                }
#endif

                switch (ui4_keycode)
                {
                case BTN_EXIT_MENU:
                case BTN_EXIT:
                    a_menu_test_patterns_turn_off();
                    a_color_tuner_update_value();

                    /*update 11 point: gain num,R,G,B*/
                    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN));
                    MENU_LOG_ON_FAIL(i4_ret);

                    DBG_INFO(("\n####%s(%d)turn off test patterns when exit\n",__FUNCTION__,__LINE__));
                    menu_custom_exit_menu_actions();
#ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        /* Multimedia */
                        a_amb_resume_app(MMP_NAME);
                    }
                    else
#endif
                    {
                        /* Always exit menu when user press EXIT */
                        menu_leave(TRUE, MENU_PM_HIDE_DELAY);
                    }
                    *pb_processed = TRUE;
                    return MENUR_OK;
                case BTN_3D:
                {
                    UINT32      ui4_cnt_page = 0;

                    if(_get_3d_setting_mode() == FALSE)
                    {
                        return MENUR_OK;
                    }
                    else
                    {
                        if(a_menu_3d_setting_is_able_to_enable() == FALSE)
                        {
                            return MENUR_OK;
                        }

                        i4_ret = menu_nav_get_crnt_page(&ui4_cnt_page);
                        if (i4_ret==MENUR_OK)
                        {
                            /*in osd secren */
                            if (ui4_cnt_page == ui4_g_menu_page_3D_setting)
                            {
                                break;
                            }
                            else
                            {
                                //menu_leave (TRUE, MENU_PM_HIDE_DELAY);
                                //a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                                if (ui4_cnt_page == ui4_g_menu_page_scr_mode)
                                {
                                    menu_nav_back_and_go(ui4_g_menu_page_3D_setting, NULL);
                                }
                                else
                                {
                                    menu_nav_go(ui4_g_menu_page_3D_setting, NULL);
                                }
                                return MENUR_OK;
                            }
                        }
                    }
                    return MENUR_OK;
                }

                case BTN_BLUE:
                {
#ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT
                    BOOL     b_blue_button_enable_status= FALSE;
                    a_cfg_custom_get_wide_mode_enable_change(&b_blue_button_enable_status);

                    if ( b_blue_button_enable_status == FALSE)
                    {
                        /* disable blue button key */
                        return MENUR_OK;
                    }
                    else
#endif
                    {
                        BOOL        b_is_main_menu_visible = TRUE;
                        HANDLE_T    h_main_frm;

                        menu_pm_get_main_frm(&h_main_frm);
                        i4_ret = c_wgl_get_visibility(h_main_frm, &b_is_main_menu_visible);

                        if (i4_ret != WGLR_OK)
                        {
                            b_is_main_menu_visible = TRUE;
                        }

                        if (b_is_main_menu_visible == TRUE)
                        {
                            UINT8 ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;

                            if (!a_cfg_is_able_to_apply_viewport ())
                            {
                                ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;
                                i4_ret = a_icl_set (
                                    ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                                    (VOID *) &ui1_sts,
                                    ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);
                            }
                            else
                            {
                                ui1_sts = ICL_VIEWPORT_LAST_REQ_SUCCEED;
                                i4_ret = a_icl_set (
                                    ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                                    (VOID *) &ui1_sts,
                                    ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);

                                a_cfg_set_next_viewport ();
                                a_cfg_update_viewport ();
                                menu_pm_repaint();
                                menu_pm_refresh();
                            }
                            b_processed = TRUE;
                        }
                        else
                        {
                            return MENUR_OK;
                        }
                    }
                    break;
                }

                case BTN_PREV_PRG:
                {
                #ifdef APP_MENU_MMP_COEXIST
                    e_mmp_status = a_mmp_get_ap_status();
                    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status)
                    {
                        *pb_processed = TRUE;
                        return MENUR_OK;
                    }
                    else
                #endif
                        break;
                }

                case BTN_CUSTOM_11:
                {
                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        a_amb_resume_app(MMP_NAME);
                    }
                #endif

                    /* msgconvert handle this key */
                    *pb_processed = FALSE;
                    return MENUR_OK;
                }

                case BTN_NETFLIX:
                case BTN_AMAZON:
                case BTN_VUDU:
                case BTN_MGO:
                case BTN_IHEART_RADIO:
                case BTN_WATCHFREE:
                case BTN_REDBOX:
                case BTN_HAYSTACK:
                {
                    /*trun off test patterns when press NETFLIX/AMAZON/MGO*/
                    a_menu_test_patterns_turn_off();
                    menu_request_context_switch(_menu_custom_update_color_tune_fct,
                           NULL,
                           NULL,
                           NULL);
                    DBG_INFO(("\n####%s(%d)turn off test patterns\n",__FUNCTION__,__LINE__));
                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        ui4_g_delay_proc_input_key = ui4_keycode;
                        a_amb_resume_app(MMP_NAME);
                        *pb_processed = FALSE;
                        return MENUR_OK;
                    }
                    else
                #endif
                    {
                        menu_leave(TRUE, MENU_PM_HIDE_DELAY);

                        if (!a_msg_convert_is_yahoo_started())
                        {
                            a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);

                            *pb_processed = TRUE;
                            return MENUR_OK;
                        }
                        else
                        {
                            *pb_processed = FALSE;
                            return MENUR_OK;
                        }
                    }
                }

                case BTN_WIDGET:
                {
                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        ui4_g_delay_proc_input_key = ui4_keycode;
                        a_amb_resume_app(MMP_NAME);
                        *pb_processed = FALSE;
                        return MENUR_OK;
                    }
                    else
                #endif
                    if (!t_g_menu_is_scanning)
                    {
                        if (!a_msg_convert_is_yahoo_started())
                        {
                            menu_leave(FALSE, MENU_PM_HIDE_DELAY);

                            a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);

                            *pb_processed = TRUE;
                            return MENUR_OK;
                        }
                        else
                        {
                            menu_leave(FALSE, MENU_PM_HIDE_DELAY);

                            DBG_INFO(("\n======Widget key down handler in menu.\n"));
                            a_tv_custom_handle_widget_key();
                        }
                    }

                    *pb_processed = TRUE;
                    return MENUR_OK;
                }

                case BTN_INPUT_SRC:
                case BTN_PANEL_POWER_INPUT:
                {
                    MENU_DEBUG_KEY_INPUT_SRC(
                        DBG_LOG_PRINT(("[MENU][KEY][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

                    a_menu_test_patterns_turn_off();

                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        *pb_processed = TRUE;
                        //menu_leave(FALSE, MENU_PM_HIDE_DELAY);
                        a_amb_resume_app(MMP_NAME);

                        // wait for MMP resume
                        c_thread_delay(100);
                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);

                        return MENUR_OK;
                    }
                    else
                #endif
                    {
                        ui4_g_delay_proc_input_key = DELAY_UNDEF_KEY;
                        menu_leave(FALSE, MENU_PM_HIDE_DELAY);

                        #ifdef APP_RETAIL_MODE_SUPPORT
                        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
                        #endif

                        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
                        {
                            /* Wating for retail mode started */
                            ui4_g_delay_proc_input_key = BTN_INPUT_SRC;
                        }
                        else
                        {
                            a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                        }
                        return MENUR_OK;
                    }
                }

                case BTN_P_EFFECT:
                {
                    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][KEY][PIC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

            #if( MENU_SUPPORT_HOT_KEY_PIC )

                    *pb_processed = TRUE;
                    return MENUR_OK;
            #else // MENU_SUPPORT_HOT_KEY_PIC

                    a_menu_test_patterns_turn_off();

                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        *pb_processed = TRUE;

                        //menu_leave(FALSE, MENU_PM_HIDE_DELAY);
                        a_amb_resume_app(MMP_NAME);

                        // wait for MMP resume
                        c_thread_delay(100);
                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                        return MENUR_OK;
                    }
                    else
                #endif
                    {
                        menu_leave(FALSE, MENU_PM_HIDE_DELAY);
                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                        return MENUR_OK;
                    }
            #endif // MENU_SUPPORT_HOT_KEY_PIC

                    break;
                }

                case BTN_ASPECT:
                {
                    MENU_DEBUG_KEY_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][KEY][ASPECT]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

            #if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )

                    *pb_processed = TRUE;
                    return MENUR_OK;
            #else // MENU_SUPPORT_HOT_KEY_ASPECT_RATIO

                    a_menu_test_patterns_turn_off();

                    UINT32    ui4_cnt_page;
                    if (a_tv_custom_is_3D_mode_playing() == FALSE)
                    {
                        i4_ret = menu_nav_get_crnt_page(&ui4_cnt_page);
                        if (i4_ret==MENUR_OK)
                        {
                            /*in osd secren */
                            if (ui4_cnt_page == ui4_g_menu_page_scr_mode)
                            {
                                break;
                            }
                            else
                            {
                                ui4_g_delay_proc_input_key = DELAY_UNDEF_KEY;

                            #ifdef APP_MENU_MMP_COEXIST
                                if  ((a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING) ||
                                    (a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING)  ||
                                    (a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING) ||
                                    (a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING))
                                {
                                    a_amb_resume_app(MMP_NAME);
                                    a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                                }
                                else if (a_mmp_get_ap_status() != MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
                            #endif
                                {
                                    menu_leave (TRUE, MENU_PM_HIDE_DELAY);

                                    #ifdef APP_RETAIL_MODE_SUPPORT
                                    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
                                    #endif

                                    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
                                    {
                                        /* Wating for retail mode started */
                                        ui4_g_delay_proc_input_key = BTN_ASPECT;
                                    }
                                    else
                                    {
                                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                                    }
                                }
                                return MENUR_OK;
                            }
                        }
                    }
            #endif // MENU_SUPPORT_HOT_KEY_ASPECT_RATIO

                    return MENUR_OK;
                }

                case BTN_PRG_INFO:
                {
                    b_is_wide_mode = menu_scr_mode_show();
                    if(!b_is_wide_mode)
                    {
                        if (/*(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state) ||*/
                            (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()))
                        {
                            return MENUR_OK;
                        }
                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                        return MENUR_OK;
                    }else
                    {
                        menu_leave(TRUE, MENU_PM_HIDE_DELAY);
                    }
                    break;
                }

                case BTN_BLANK_SCREEN:
                {
                    UINT32      ui4_cnt_page = 0;
                #ifdef APP_MENU_DLG_COEXIST
                    //BOOL        b_hide = FALSE;
                #endif
                    *pb_processed = TRUE;
                    i4_ret = menu_nav_get_crnt_page(&ui4_cnt_page);
                    if (i4_ret==MENUR_OK)
                    {
                        /*in osd secren */
                        if (ui4_cnt_page == ui4_g_menu_page_blank_scrn)
                        {
                            break;
                        }
                        else
                        {
                            /* force blank screen, and cannot unblank screen when call menu_custome_unblank_screen,
                            *  could call menu_custome_blank_screen again to let menu_custome_unblank_screen enable
                            */
                            menu_custom_blank_screen();

                            #ifdef APP_MENU_MMP_COEXIST
                            if  ((a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING) ||
                                (a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING)  ||
                                (a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING) ||
                                (a_mmp_be_get_browser_status()==MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING) ||
                                (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC))
                            {
                                a_amb_resume_app(MMP_NAME);
                                c_thread_delay(100);

                                a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                                a_scrn_blank_reset();
                            }
                            else if (a_mmp_get_ap_status() != MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
                            #endif
                            {

                                menu_leave(TRUE, MENU_PM_HIDE_DELAY);
                                a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)BTN_BLANK_SCREEN, NULL);
                                a_scrn_blank_reset();
                            }
                            return MENUR_OK;
                        }
                    }
                    return MENUR_OK;
                }

                default:
                    break;
                }
            }
            /* translate the front panel key to irrc key */
            if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN ||
                pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_REPEAT ||
                pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_UP )
            {
                UINT32 ui4_key = (UINT32)pt_msg_wgl_notify->pv_param1;
                if(ui4_key & KEY_SRC_FRONT_PANEL)
                {
                    ui4_key = ui4_key & ~KEY_SRC_FRONT_PANEL;
                    switch(ui4_key)
                    {
                    case BTN_PRG_UP:
                        ui4_key = BTN_CURSOR_UP;
                        break;
                    case BTN_PRG_DOWN:
                        ui4_key = BTN_CURSOR_DOWN;
                       break;
                   case BTN_VOL_UP:
                        //ui4_key = BTN_CURSOR_RIGHT;
                        break;
                    case BTN_VOL_DOWN:
                       //ui4_key = BTN_CURSOR_LEFT;
                        break;
                    case BTN_INPUT_SRC:
                    {
                        MENU_DEBUG_KEY_INPUT_SRC(
                            DBG_LOG_PRINT(("[MENU][KEY][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

                        menu_leave(TRUE, MENU_PM_HIDE_DELAY);
                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key, NULL);
                        return MENUR_OK;
                    }
                    case BTN_MENU:
                        ui4_key = BTN_SELECT;
                        break;
                    }
                }

                if (ui4_key == BTN_CUSTOM_1 || ui4_key == BTN_KB_ENTER)
                {
                    ui4_key = BTN_SELECT;
                }

                pt_msg_wgl_notify->pv_param1 = (VOID*)ui4_key;
            }

            /* Process Exit key */
            if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN ||
                pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_REPEAT)
            {
                UINT32  ui4_key = (UINT32)pt_msg_wgl_notify->pv_param1;

                if((ui4_key == BTN_EXIT)||
                   (ui4_key == BTN_RED))
                {
                #ifdef APP_MENU_MMP_COEXIST
                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                    {
                        /* Multimedia */
                        a_amb_resume_app(MMP_NAME);
                    }
                    else
                #endif
                    {
                        /* Always exit menu when user press EXIT */
                        menu_leave(TRUE, MENU_PM_HIDE_DELAY);
                    }
                    *pb_processed = TRUE;
                    return MENUR_OK;
                }
            }


            if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN ||
                pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_REPEAT)
            {
                UINT32  ui4_keycode = (UINT32)pt_msg_wgl_notify->pv_param1;
                ISL_REC_T                   t_isl_rec;

                i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
                DBG_INFO(("<menu> %s,%d,src_type:0x%x,video_type:0x%x,i4_ret:%d\n\r",__FILE__,__LINE__,
                    t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type,i4_ret));

                if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
                {
                    if (ui4_keycode == BTN_PRG_UP ||
                        ui4_keycode == BTN_PRG_DOWN)
                    {
                    	if(t_g_menu_enable_channel_change == FALSE)
                		{
							break;
						}
                        {
                            #ifdef APP_CAST_TEST_PATTERN
                            /* if pattern is on ,exit pattern ,then ch+/- */
                            a_menu_test_patterns_turn_off();
                            #endif
                            menu_leave(TRUE, MENU_PM_HIDE_DELAY);
                            a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_keycode, NULL);
                            return MENUR_OK;
                        }
                    }
                }
            }
        }
        break;
    /* we need process some message from other ap */
    case MENU_MSG_EXTERNAL_REQ_SHOW_USB_POP_DLG:
    {
        /* show usb plugin dialog */
        b_processed = TRUE;
        menu_custom_unblank_screen(ui4_type);
        i4_ret = menu_custom_dialog_show(MENU_CUSTOM_DIALOG_ID_USB_POPUP);
        MENU_LOG_ON_FAIL(i4_ret);
    }
        break;
    case MENU_MSG_EXTERNAL_REQ_HIDE_USB_POP_DLG:
    {
        /* show usb plugin dialog */
        b_processed = TRUE;

        i4_ret = menu_custom_dialog_hide(MENU_CUSTOM_DIALOG_ID_USB_POPUP);
        MENU_LOG_ON_FAIL(i4_ret);
    }
        break;
    default:
        break;
    }
    if(b_processed)
    {
        *pb_processed = TRUE;
        return i4_ret;
    }

    /* common */
    b_processed = FALSE;
    i4_ret = menu_common_process_msg(ui4_type,
                                     pv_msg,
                                     z_msg_len,
                                     &b_processed);
    if(b_processed)
    {
        *pb_processed = TRUE;
        return i4_ret;
    }

    /* atsc */
    b_processed = FALSE;
    i4_ret = menu_atsc_process_msg (ui4_type,
                                    pv_msg,
                                    z_msg_len,
                                    &b_processed);
    if(b_processed)
    {
        *pb_processed = TRUE;
        return i4_ret;
    }

    *pb_processed = FALSE;

    return MENUR_OK;
}

static INT32 _menu_lang_lb_literal_ref(UINT16 ui2_lang)
{
    INT32     i4_ret;
    HANDLE_T* pt_hdr = NULL;
    UINT32    ui4_crnt_page;

    do {
        i4_ret = menu_nav_get_crnt_page(&ui4_crnt_page);
        MENU_LOG_ON_FAIL(i4_ret);

        if (ui4_crnt_page != ui4_g_menu_page_setup)
        {
            break;
        }

        i4_ret = menu_page_tree_get_widget(ui4_crnt_page, MLM_MENU_KEY_OSD_LANG, &pt_hdr);
        if (i4_ret != MENUR_OK)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = menu_list_set_idx(*pt_hdr, ui2_lang);
        MENU_LOG_ON_FAIL(i4_ret);

        menu_pm_refresh();
    }while (0);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: menu_custom_chg_lang
 *
 * Description:
 *  Change language according current gui language.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 menu_custom_chg_lang(VOID)
{
    INT32 i4_ret;
    ISO_639_LANG_T s639_lang;
    UINT16 ui2_lang;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != MENUR_OK)
    {
        ui2_lang = 0;
    }
    else
    {
        ui2_lang = mlm_menu_s639_to_langidx(s639_lang);
    }

    i4_ret = _menu_lang_lb_literal_ref(ui2_lang);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_chg_lang(ui2_lang);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

VOID menu_set_start_user_manual_flag(BOOL b_start)
{
    b_g_start_user_manual = b_start;

#if 0
#ifdef APP_CFG_DIMMING_OFF_IN_EMANUAL
    if (b_start == TRUE)
    {
        UINT8   ui1_val     = ICL_EMANUAL_STATUS_ON;
        SIZE_T  z_size      = ICL_RECID_EMANUAL_STATUS_SIZE;

        a_icl_set(ICL_MAKE_ID(ICL_GRPID_EMANUAL_STATUS, ICL_RECID_EMANUAL_STATUS),
                  &ui1_val, z_size);
    }
#endif
#endif
    return;
}
BOOL menu_get_start_user_manual_flag(VOID)
{
    return b_g_start_user_manual;
}

#ifdef APP_MMP_SUPPORT
VOID a_menu_custom_set_resuming_mmp_flag (BOOL b_resume)
{
    b_g_resuming_mmp = b_resume;
}

BOOL a_menu_custom_is_resuming_mmp (VOID)
{
    return b_g_resuming_mmp;
}
#endif

BOOL menu_custom_power_seq_cb(VOID)
{
    BOOL b_resume = FALSE;
    UINT16 ui2_status = APP_CFG_WZD_STATUS_INIT;
    UINT16 ui2_real_status = APP_CFG_WZD_STATUS_INIT;
    INT32 i4_rc = 0;
    PCL_WAKE_UP_REASON_T    e_wake_up_reason = PCL_WAKE_UP_REASON_UNKNOWN;

    /* Get the wakeup reason/sub-reason */
    i4_rc = c_pcl_get_wakeup_reason (& e_wake_up_reason, NULL);

    DBG_INFO(("<MENU> LINE %d:i4_rc=%d, e_wake_up_reason = %d\n",i4_rc,e_wake_up_reason));

    if (i4_rc != PCLR_OK)
    {
        DBG_ERROR (("<MENU> ERR: c_pcl_get_wakeup_reason failed = %d\n\r", i4_rc));
    }
    else
    {
        DBG_INFO(("<MENU> e_wake_up_reason = %d\n",e_wake_up_reason));
    }

    if (e_wake_up_reason == PCL_WAKE_UP_REASON_CUSTOM_2)
    {
        if (a_cfg_get_wzd_status (&ui2_status) == APP_CFGR_OK)
        {
            ui2_real_status = WZD_UTIL_GET_STATUS_STATE( ui2_status );
            DBG_INFO(( "[MENU][menu_custom_power_seq_cb] ui2_status = %d\n", ui2_status ));

            if (!(ui2_real_status == APP_CFG_WZD_STATUS_INIT
                  || ui2_real_status & WZD_STATE_START_SETUP
                  || APP_CFG_WZD_STATUS_WIFI_UNPAIR == ui2_status))
            {
                b_resume = TRUE;
            }
        }
    }

    return b_resume;
}

/*----------------------------------------------------------------------------
 * Name: _do_show_menu_toast_view_timer
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
static VOID _do_show_menu_toast_view_timer(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    BOOL* pb_show_menu = (BOOL*)pv_data1;

    a_wdk_toast_hide(FALSE,&tg_toast_param,&t_g_wdk_view);

    c_timer_stop(h_timer_show);

    if(*pb_show_menu)
    {
        menu_pm_show();
    }
    else
    {
        menu_pic_erengy_change_toast_reset_status();
    }
}

/*----------------------------------------------------------------------------
 * Name: _menu_timer_show_toast_view_fct
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
static VOID _menu_timer_show_toast_view_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    menu_request_context_switch(_do_show_menu_toast_view_timer,pv_tag, NULL,NULL);
}

/*----------------------------------------------------------------------------
 * Name: menu_setup_string_toast_view
 * Description:
 *  show warning toast
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 menu_setup_string_toast_view(UTF16_T* w2s_txt,BOOL b_show_menu)
{
    INT32           i4_ret;
    HANDLE_T        h_canvas;

    static BOOL b_show_menu_tag;

    b_show_menu_tag = b_show_menu;

    c_memset(&tg_toast_param, 0, sizeof(WDK_TOAST_PARAM_T));
    tg_toast_param.e_toast_style = WDK_STRING_TOAST;
    tg_toast_param.w2s_str       = (VOID*)w2s_txt;
    tg_toast_param.pf_cb         = NULL;

    i4_ret = menu_pm_get_canvas(&h_canvas);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_wdk_toast_init(h_canvas,&tg_toast_param,&t_g_wdk_view);
    MENU_CHK_FAIL(i4_ret);

    tg_toast_param.h_t_focus_handle = t_g_wdk_view.h_base_frm;

    menu_pm_hide();
    i4_ret = a_wdk_toast_activate(FALSE,&tg_toast_param,&t_g_wdk_view);
    MENU_CHK_FAIL(i4_ret);

    /* enable the show timer */
    if (h_timer_show != NULL_HANDLE)
    {
        DBG_INFO(("%s,%d [throw start] \r\n",__FUNCTION__,__LINE__));
        i4_ret = c_timer_start(h_timer_show,
                                5000,
                                X_TIMER_FLAG_ONCE,
                                _menu_timer_show_toast_view_fct,
                                (VOID*)&b_show_menu_tag);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

INT32 menu_send_string_to_nav_toast(WDK_TOAST_T *pt_toast)
{
    WDK_TOAST_T* pt_toast_cpy = NULL;
    UTF16_T* p_w2s_str = (UTF16_T*)pt_toast->style.style_4.w2s_str;

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));

    if (NULL == pt_toast_cpy)
    {
        DBG_INFO(("NULL == pt_toast_cpy!!\n"));
        return -1;
    }

    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)pt_toast, sizeof(WDK_TOAST_T));

    if (pt_toast->e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[128]  = {0};
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 127);

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;
        DBG_INFO(("[MENU][%s %d] str = %s,len = %d\n",__FUNCTION__,__LINE__,str,len));
        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)pt_toast->style.style_4.w2s_str, len);
    }

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              (VOID*) pt_toast_cpy);
    /*the conflicts with toast string, OR TTS will play two times.*/
#if 0
#ifdef APP_TTS_SUPPORT
    a_app_tts_play(p_w2s_str, c_uc_w2s_strlen(p_w2s_str));
#endif
#endif
    return NAVR_OK;
}

static BOOL b_g_is_pic_energy_change = FALSE;
static BOOL b_g_pic_energy_ui_flag = FALSE;


/*----------------------------------------------------------------------------
* Name: menu_pic_erengy_change_toast_view
* Description:
*  show warning toast
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
INT32 menu_pic_energy_change_toast_view(VOID)
{
    if (b_g_is_pic_energy_change
        && !(0 == access("/data/cfg_energy", 0)))
    {
        UTF16_T     w2s_tmp_str[128] = {0};
        c_uc_w2s_strcpy(w2s_tmp_str,MENU_TEXT(MLM_MENU_KEY_PIC_CHANGE_ENERGY_MSG));
        menu_setup_string_toast_view(w2s_tmp_str,FALSE);
        AP_SYSTEM_CALL("touch /data/cfg_energy");
        b_g_pic_energy_ui_flag = TRUE;
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
* Name: menu_pic_erengy_change_toast_reset_status
* Description:
*  show warning toast
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
INT32 menu_pic_erengy_change_toast_reset_status(VOID)
{
    b_g_is_pic_energy_change = FALSE;
    b_g_pic_energy_ui_flag = FALSE;
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
* Name: menu_pic_erengy_change_toast_reset_status
* Description:
*
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/

INT32 menu_pic_energy_change_set_status(VOID)
{
    UINT32 ui4_cur_page_id = 0xFFFFFFFF;

    menu_nav_get_crnt_page(&ui4_cur_page_id);

    if (ui4_cur_page_id == ui4_g_menu_page_vid
        || ui4_cur_page_id == ui4_page_vid_more_adv_pic
        || ui4_cur_page_id == ui4_page_reduce_noise)
    {
        b_g_is_pic_energy_change = TRUE;

    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
* Name: menu_pic_energy_change_sepcial_page_set_status
* Description:
*
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
INT32 menu_pic_energy_change_sepcial_page_set_status(BOOL b_is_change)
{
    b_g_is_pic_energy_change = b_is_change;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
* Name: a_menu_pic_erengy_change_hide_toast_view
* Description:
*  show warning toast
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
INT32 a_menu_pic_erengy_change_hide_toast_view(VOID)
{
    if(b_g_pic_energy_ui_flag)
    {
        b_g_pic_energy_ui_flag = FALSE;

        a_wdk_toast_hide(FALSE,&tg_toast_param,&t_g_wdk_view);

        if(h_timer_show != NULL_HANDLE)
        {
            c_timer_stop(h_timer_show);
        }
        menu_pic_erengy_change_toast_reset_status();
    }

    return MENUR_OK;
}

static VOID _menu_custom_jump_to_acr(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    MENU_PAGE_HINT_T    t_hint = {0};
    UINT8               ui1_hlt_indx = 0;
    UINT32              aui4_page[1] = {0};

    ui1_hlt_indx = (ui2_g_item_id_lst_acr > 0x00FF) ? 0 : ui2_g_item_id_lst_acr;

    t_hint.e_hint_type = MENU_PAGE_HT_CUSTOM;
    t_hint.u.pv_custom_hint = (VOID *)&ui1_hlt_indx;

    aui4_page[0] = ui4_g_menu_page_reset_admin;
    menu_nav_go_direct_ex(0, aui4_page, sizeof(aui4_page)/sizeof(aui4_page[0]), &t_hint);
    menu_pm_repaint();

}
INT32 menu_custom_jump_to_smart_interactivity_setting(VOID)
{
    if (a_menu_is_resume())
    {
        menu_request_context_switch(_menu_custom_jump_to_acr, NULL, NULL, NULL);
    }
    else
    {
        a_menu_shortcut_link(MENU_SHORT_CUT_RESET_ADMIN);
    }
    return MENUR_OK;

}

#if 0//(MENU_SUPPORT_HOT_KEY_PIC)
BOOL menu_custom_is_support_hot_key_PIC(VOID)
{
    //return g_menu_b_support_hot_key_PIC;
    return TRUE;
}
#endif


static char g_menu_ac_tmp_str_buf[256];
char* menu_custom_get_char_string( const UTF16_T* w2s_str )
{
    g_menu_ac_tmp_str_buf[0] = 0;

    SIZE_T w2s_str_len = c_uc_w2s_strlen(w2s_str);

    if( w2s_str_len == 0 )
    {
        c_strncpy(g_menu_ac_tmp_str_buf, "empty", 10);
    }
    else
    {
        c_uc_w2s_to_ps(w2s_str, g_menu_ac_tmp_str_buf, 255);
        g_menu_ac_tmp_str_buf[255] = 0;
    }

    return g_menu_ac_tmp_str_buf;
}


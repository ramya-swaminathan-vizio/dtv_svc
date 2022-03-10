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
 * $RCSfile: menu.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/21 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 1433fe1fd8b5fe1dfc2a58820b53a685 $
 *
 * Description:
 *         This file contains the implementation of the APPLICATION-RELATED
 * functions.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include <stdio.h>
#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_aee.h"
#include "c_appman.h"
#include "c_wgl.h"
#include "c_iom.h"
#include "c_svctx.h"

#include "amb/a_amb.h"
#include "am/a_am.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_rating.h"
#include "app_util/a_ctrl_panel.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_cust_define.h"
#include "res/menu2/menu_custom_dialog.h"
#include "res/menu2/menu_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/nav/nav_variant.h"
#include "res/nav/zoom/nav_zoom_custom.h"
#include "rest/rest.h"
#include "registry/a_registry.h"

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include "msgconvert/a_msgconvert.h"
#endif

#include "nav/scrn_blank/a_nav_scrn_blank.h"
#include "res/msgconvert/msgconvert_custom.h"
#include "menu2/menu_device/menu_page_add_new_device.h"
#include "menu2/menu_dbg.h"
#include "msgconvert/msgconvert.h"

#include <execinfo.h>

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifndef TIMER_DELAY
#define TIMER_DELAY  60000
#endif

#ifndef APP_MENU_TIMER_ENABLE
#define APP_MENU_TIMER_ENABLE
#endif

#ifndef HIDE_DELAY
#define HIDE_DELAY 0
#endif

#define LANGMAP_MAX_SIZE    16

#ifndef MENU_AUTO_KEY_REPEAT
#define MENU_AUTO_KEY_REPEAT    TRUE
#endif

#define     INPUT_KEY_PROC_DELAY                1500
#define     DELAY_UNDEF_KEY                     (0xFFFFFFFF)
#define     DELAY_INPUT_KEY                     (BTN_INPUT_SRC)
#define     DELAY_ASPECT_KEY                    (BTN_ASPECT)

#define     _MENU_MONITOR_MSG_TIME  (5000)

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
BOOL                 b_slave_mode=FALSE;

/* time measurement level */
static UINT16               ui2_menu_tms_level = TMS_INIT_LEVEL;

/* used for loosely couple */
static menu_nfy_fct         pf_menu_nfy = NULL;

/* menu status */
static MENU_COND_T          e_menu_cond = MENU_COND_NOT_INIT;

/* the menu application handle */
static HANDLE_T             h_app_menu = NULL_HANDLE;

/* mutex semaphore for menu */
static HANDLE_T             h_mtx_sema;

/* timer */
static HANDLE_T             h_timer;
static BOOL                 b_timer_enabled;
static BOOL                 b_oled = FALSE;
static UINT32               ui4_timer_delay;

/* IOM */
static HANDLE_T             h_iom;

/* monitor */
static HANDLE_T             h_moni_timer = NULL_HANDLE;

/* Key */
static BOOL                 b_g_auto_key_repeat = MENU_AUTO_KEY_REPEAT;

/* language map */
static MENU_LANGMAP_ENTRY_T at_langmap[LANGMAP_MAX_SIZE];
static UINT16               ui2_langmap_size;

/* stop watch (for time measurement) */
#ifdef APP_MENU_TMS_SUPPORT
static UINT32 ui4_watch = 0;
#endif

BOOL b_g_select_is_menu_key = FALSE;
static BOOL                 b_resume_from_short_cut = FALSE;
static MENU_SHORT_CUT_T     e_cur_short_cut_key = MENU_SHORT_CUT_MAX;
static BOOL b_g_resume_menu = FALSE;
static BOOL         b_g_is_need_power_off_dlg_show = FALSE;
static BOOL         b_freeze_banner = FALSE;

static BOOL         b_is_picture_lock  = FALSE;

extern UINT32   ui4_g_delay_proc_input_key;

UINT32 g_menu_u32_sys_tick_period;

UINT32 g_menu_u32_sys_tick_last = 0;

/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
extern BOOL  menu_custom_system_key_cb (UINT32  ui4_evt_code);
extern INT32 menu_custom_pre_init(VOID);
extern INT32 menu_custom_init(VOID);
extern INT32 menu_custom_resume(VOID);
extern INT32 menu_custom_pause(VOID);
extern INT32 menu_custom_exit(VOID);
extern INT32 menu_custom_process_msg(
    UINT32       ui4_type,
    const VOID*  pv_msg,
    SIZE_T       z_msg_len,
    BOOL*        pb_paused
);

/*Fix bug DTV00797191*/
extern INT32 banner_view_freeze(BOOL b_freeze,UINT32 ui4_proposer_id);
extern INT32 banner_view_refresh (BOOL b_at_once);

static INT32 _menu_app_init_fct (
    const CHAR*  ps_name,
    HANDLE_T     h_app
);
static INT32 _menu_app_resume_fct (
    HANDLE_T  h_app
);
static INT32 _menu_app_pause_fct (
    HANDLE_T  h_app
);
static INT32 _menu_app_exit_fct (
    HANDLE_T         h_app,
    APP_EXIT_MODE_T  e_exit_mode
);
static INT32 _menu_app_process_msg_fct (
    HANDLE_T     h_app,
    UINT32       ui4_type,
    const VOID*  pv_msg,
    SIZE_T       z_msg_len,
    BOOL         b_paused
);
static BOOL _menu_app_system_key_fct (
    UINT32       ui4_evt_code
);
static VOID _change_menu_cond(MENU_COND_T _e_menu_cond);

static VOID _menu_show_power_off_dlg_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3);
/*-----------------------------------------------------------------------------
                    static functions implementation
 ----------------------------------------------------------------------------*/
static VOID _menu_nfy(MENU_COND_T e_cond)
{
}

#ifdef APP_MENU_TIMER_ENABLE
/*----------------------------------------------------------------------------
 * Name: _timer_nfy_fct
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
static VOID _timer_nfy_fct(HANDLE_T  pt_tm_handle,
                           VOID*     pv_tag)
{
    INT32 i4_ret;

    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} call a_amb_pause_app(MENU_NAME)\n",
            __FUNCTION__,__LINE__ ));
    );

    /* this is an asynchronous function */
    i4_ret = a_amb_pause_app(MENU_NAME);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<MENU> Can't send pause request to app manager.\r\n"));
        DBG_LOG_PRINT(("<MENU> Can't send pause request to app manager.\r\n"));
    }
}
#endif
/*----------------------------------------------------------------------------
 * Name: _wgl_callback
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
static INT32 _wgl_callback(UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    MENU_MSG_WGL_NOTIFY_T t_msg_wgl_notify;

    if(e_menu_cond == MENU_COND_NOT_INIT)
    {
        return 0;
    }

    t_msg_wgl_notify.ui4_msg = ui4_msg;
    t_msg_wgl_notify.pv_param1 = pv_param1;
    t_msg_wgl_notify.pv_param2 = pv_param2;
    //Fix Coverity ID : 1391124 Unchecked return value
    if (c_app_send_msg(h_app_menu, MENU_MSG_WGL_NOTIFY,
                   &t_msg_wgl_notify,
                   sizeof(MENU_MSG_WGL_NOTIFY_T), NULL, NULL) != AEER_OK)
    {
        DBG_ERROR(("<MENU> Wgl callback fail, Can't send message.\n"));
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _iom_nfy_fct
 *
 * Description: This callback function will be called by the IO Manager when
 *              system events are triggered from the remote control.
 *
 * Inputs:  pv_nfy_tag      Contains a tag value.
 *          e_nfy_cond      Contains the notify condition.
 *          ui4_evt_code    Contains the event code.
 *          ui4_data        Contains information related to the event.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _iom_nfy_fct (VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data)
{
    INT32   i4_ret;

#ifdef APP_MENU_CUSTOM_IOM_NFY_FCT
    menu_custom_iom_nfy_fct(h_app_menu, e_nfy_cond,ui4_evt_code);
#endif

    if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN &&
       (IOM_GET_EVT_GRP_ID(ui4_evt_code) >= BTN_FACTORY_MODE_1 &&
        IOM_GET_EVT_GRP_ID(ui4_evt_code) <= BTN_FACTORY_MODE_4))
    {
        i4_ret = c_app_send_msg(h_app_menu,
                                MENU_MSG_FACTORY_KEY,
                                &ui4_evt_code,
                                sizeof(UINT32),
                                NULL,
                                NULL);
        if(i4_ret != OSR_OK)
        {
            DBG_ERROR(("<MENU> Can't send factory message.\n"));
        }
    }

    if( e_nfy_cond == IOM_NFY_COND_BTN_DOWN )
    {
        DBG_INFO(("[MENU][%s %d] key = 0x%x\n",__FUNCTION__,__LINE__,ui4_evt_code));
        MENU_DEBUG_KEY(
            DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_evt_code:0x%X\n", __FUNCTION__, __LINE__, ui4_evt_code  ));
        );
    }

    menu_blank_oled_scrn_timer_refresh();

    //menu_set_temporary_key_code(ui4_evt_code);  //dolphin add 20190430 to transport keycode ,dolphin 20190531 not use
    if(menu_custom_is_blank_screen() &&
       e_nfy_cond == IOM_NFY_COND_BTN_DOWN &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_POWER        &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PRG_UP       &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PRG_DOWN     &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_P_EFFECT     &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_ASPECT       &&
 //      IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PREV_PRG     &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_WIDGET       &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_IHEART_RADIO &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_XUMO         &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_AMAZON       &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_HULU         &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_NETFLIX      &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_CRACKLE      &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_VUDU         &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_MGO          &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_WATCHFREE    &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_REDBOX       &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_HAYSTACK     &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PRG_INFO     &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_INPUT_SRC    &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PIP_INPUT_SRC &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_CC           &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_DISNEY       &&
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PARTNER_2    && // Peacock
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PARTNER_3    && // Tubi
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PARTNER_4    && // Pluto
       IOM_GET_EVT_GRP_ID(ui4_evt_code) != BTN_PARTNER_5)      // HBOMAX
    {// vol+ vol-,mute can not unblank screen spec5.0
        // for fix issue some times,can exit mmp,when blank screen status
        if(IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_EXIT)
        {
            CHAR sz_app[127] = {0};

            if(AMR_OK == a_am_get_active_app(sz_app) &&
                0 == c_strcmp(sz_app,"mmp"))
            {
                return;
            }
        }
        if (
            IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_VOL_DOWN     ||
            IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_VOL_UP       ||
            IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_MUTE)
        {
            if (menu_custom_get_blank_scrn_mode() == BLK_SCRN_NORMAL)
            {
                return;
            }
        }
        MENU_LOG_ON_FAIL(menu_custom_unblank_screen(IOM_GET_EVT_GRP_ID(ui4_evt_code) ));
    }
}

static VOID _menu_freeze_banner(BOOL b_freeze)
{
    banner_view_freeze(b_freeze,1);

    if (!b_freeze && b_freeze_banner)
    {
        banner_view_refresh(TRUE);
    }

    b_freeze_banner = b_freeze;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_app_init_fct
 *
 * Description:
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_app_init_fct (
    const CHAR*  ps_name,
    HANDLE_T     h_app)
{
    INT32 i4_ret;
    INT32 i4_result = AEER_FAIL;
    IRRC_SETTING_T  t_irrc_setting;
    BOOL   b_is_lock_status = FALSE;
    UINT32 ui4_oled_support = 0;
    UINT32 ui4_dbg_level = dbg_get_log_level_from_file("menu", "/data/loglevel.txt");

    menu_set_dbg_level((UINT16)ui4_dbg_level);
    DBG_LOG_PRINT(("[%s %s %d] menu_dbg_level %d\n", __FILE__, __func__, __LINE__, ui4_dbg_level));
    DBG_INFO(("<MENU>Init. \n\r"));
    MENU_TMS_RESET("init");

    h_app_menu = h_app;

    a_cfg_cust_drv_get_oled_support_compensation(&ui4_oled_support);
    b_oled = ui4_oled_support > 0 ? TRUE :FALSE;
    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}b_oled:%d\n",
            __FUNCTION__,__LINE__, b_oled ));
    );

    g_menu_u32_sys_tick_period =  c_os_get_sys_tick_period();
    MENU_DEBUG_TIME(
        DBG_LOG_PRINT(("[MENU][TIME]{%s,%d} g_menu_u32_sys_tick_period:%d\n",
            __FUNCTION__,__LINE__, g_menu_u32_sys_tick_period ));
    );


    do
    {
        /* Create the mutex semaphore */
        i4_ret = c_sema_create (&h_mtx_sema,
                                X_SEMA_TYPE_MUTEX,
                                X_SEMA_STATE_UNLOCK);
        if (i4_ret != 0)
        {
            DBG_ERROR(("<MENU>Can't open semaphore\r\n"));
            break;
        }

        /* Create Timer */
        i4_ret = c_timer_create(&h_timer);
        if(i4_ret != OSR_OK)
        {
            DBG_ERROR(("<MENU>Can't create timer\r\n"));
            break;
        }
        b_timer_enabled = FALSE;
        MENU_DEBUG_TIMEOUT(
            DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}b_timer_enabled=%d\n",
                __FUNCTION__,__LINE__, b_timer_enabled ));
        );

        ui4_timer_delay = TIMER_DELAY;

        /* Widget library init */
        i4_ret = c_wgl_register(_wgl_callback);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR(("<MENU>c_wgl_register fail\r\n"));
            break;
        }

        i4_ret = c_wgl_set_delay_tolerance(100);
        if(i4_ret != WGLR_OK)
        {
            DBG_ERROR(("<MENU>c_wgl_set_delay_tolerance fail\r\n"));
            break;
        }

        /* IOM Init */
        c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;//IOM_EVT_GRP_TO_MASK(KEY_GROUP_USER_DEF) | IOM_EVT_GRP_TO_MASK(KEY_GROUP_PRG_CTRL);
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
        i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                             IOM_DEV_ID_ANY,
                             NULL,
                             (VOID*) & t_irrc_setting,
                             NULL,
                             _iom_nfy_fct,
                             &h_iom);

        /* language map init. For the sake of compatibility, the default value
           are set to the following*/
        c_strncpy(at_langmap[0].s639_lang, s639_app_cfg_lang_eng, ISO_639_LANG_LEN);
        c_strncpy(at_langmap[1].s639_lang, s639_app_cfg_lang_esl, ISO_639_LANG_LEN);
        c_strncpy(at_langmap[2].s639_lang, s639_app_cfg_lang_fra, ISO_639_LANG_LEN);
        at_langmap[0].ui2_lang = 0;  /* MLM_MENU_LANG_ENG, preventing from not compiling */
        at_langmap[1].ui2_lang = 1;  /* MLM_MENU_LANG_ESL */
        at_langmap[2].ui2_lang = 2;  /* MLM_MENU_LANG_FRA */
        ui2_langmap_size = (UINT16)(MLM_MENU_NUM_LANG < 3 ? MLM_MENU_NUM_LANG : 3);

        /* custom ore init */
        DBG_INFO(("<MENU>Initing custom (pre). \n\r"));
        MENU_TMS_SPLIT("custom_init");
        i4_ret = menu_custom_pre_init();
        if(i4_ret != MENUR_OK)
        {
            DBG_ERROR(("<MENU>Can't init menu atsc\r\n"));
            break;
        }

        /* init page manager */
        DBG_INFO(("<MENU>Initing pm. \n\r"));
        MENU_TMS_SPLIT("pm_init");
        i4_ret = menu_pm_init();
        if(i4_ret != MENUR_OK)
        {
            DBG_ERROR(("<MENU>Can't init page manager\r\n"));
            break;
        }

        /* init page tree */
        i4_ret = menu_page_tree_init();
        if(i4_ret != MENUR_OK)
        {
            DBG_ERROR(("<MENU>Can't init page tree\r\n"));
            break;
        }

        /* custom init */
        DBG_INFO(("<MENU>Initing custom. \n\r"));
        MENU_TMS_SPLIT("custom_init");
        i4_ret = menu_custom_init();
        if(i4_ret != MENUR_OK)
        {
            DBG_ERROR(("<MENU>Can't init menu atsc\r\n"));
            break;
        }
        a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
        b_is_picture_lock  = b_is_lock_status;

        /* change the lanugage */
        {
            ISO_639_LANG_T  s639_lang;
            UINT16          ui2_lang;
            i4_ret = a_cfg_get_gui_lang(s639_lang);

            if(i4_ret != APP_CFGR_OK)
            {
                DBG_ERROR(("<MENU>Can't init menu lanugage \r\n"));
                break;
            }

            menu_langcode_to_idx(s639_lang, &ui2_lang);

            menu_chg_lang(ui2_lang);
        }

        /* finish the initiate */
        e_menu_cond = MENU_COND_PAUSE;
        i4_result = AEER_OK;
    }while (0);

    if (i4_result != AEER_OK)
    {
        DBG_ERROR(("<MENU>Can't initiate menu. \n\r"));
        return i4_result;
    }
    else
    {
        DBG_INFO(("<MENU>Finish init. \n\r"));
        MENU_TMS_SPLIT("init done");
    }
#ifndef APP_C4TV_SUPPORT
    if (menu_custom_power_seq_cb ())
    {
        a_menu_shortcut_link(MENU_SHORT_CUT_VER_INFO_PAGE);
    }
#endif

    return AEER_OK;
}

static VOID _menu_resume_fct(VOID* arg1,VOID* arg2,VOID* arg3 )
{
    BOOL  b_processed;
    UINT8   ui1_fac_mode = 0;
	MSG_CONVERT_SEND_CMD_T t_send_cmd;
  //  UINT32 tick = c_os_get_sys_tick();
    /* reset flag */
    b_g_is_need_power_off_dlg_show = FALSE;

    b_g_resume_menu = TRUE;

    DBG_LOG_PRINT(("<MENU>Resume\n\r"));
    MENU_TMS_RESET("resume");
    /* MENU resume logic */
    /* Custom-specific resume logic */
    _menu_freeze_banner(TRUE);

    if(MENUR_OK != menu_custom_resume())
    {
        _menu_freeze_banner(FALSE);
        return ;
    }

    /* reset the last stream mode */
    menu_keep_crnt_stream_mode ();

    /* Showing logic. Always put it at the last */
    if (b_slave_mode)
    {
        _change_menu_cond(MENU_COND_HIDE);
    }
    else
    {
        do
        {
            b_timer_enabled = TRUE;
            MENU_DEBUG_TIMEOUT(
                DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}b_timer_enabled=%d\n",
                    __FUNCTION__,__LINE__, b_timer_enabled ));
            );

            menu_timer_start();

            DBG_LOG_PRINT(("<MENU>showing\n\r"));
            MENU_TMS_SPLIT("show");

            /* Custom resume show */
            b_processed = FALSE;

#ifdef APP_MENU_CUSTOM_RESUME_SHOW_SUPPORT
            if(MENUR_OK != menu_custom_resume_show(&b_processed))
                 b_processed = FALSE;
#endif

#if NEVER    //CID:4491224
            if(b_processed)
            {
                break;
            }
#endif
            /* Auto resume. The menu is not resumed by system key but back from
               anther application */
            if(a_am_is_auto_resume())
            {
                if(MENUR_OK != menu_pm_show_by_latest_state())
                {  DBG_ERROR(("<MENU> Can't show latest page.\n"));}
                else
                   break;
            }

            /* Resume Show. Trigger by menu_pm_request_resume_show() */
            if(menu_pm_is_resume_show())
            {
                if(MENUR_OK != menu_pm_resume_show())
                {  DBG_ERROR(("<MENU> Can't Resume show.\n"));}
                else
                    break;
            }

            if(b_resume_from_short_cut)
            {
                MENU_LOG_ON_FAIL(menu_pm_short_cut_show(e_cur_short_cut_key));
                b_resume_from_short_cut = FALSE;
                break;
            }

            /* Go to factory page if it is in factory mode */
            if(MENUR_OK != a_cfg_get_factory_mode(&ui1_fac_mode))
                 return;

            if(( ui1_fac_mode & APP_CFG_FAC_MODE_FACTORY_MASK) && ( FALSE == t_g_menu_common.b_is_hot_key_enter))
            {
                if(MENUR_OK != menu_pm_show_by_factory_page())
                {   DBG_ERROR(("<MENU>Can't show factory page. Factory page may not be set yet. \n"));}
                else
                    break;
            }

            /* Normal Show Logic */
           if(
#if defined(APP_MENU_GO_LATEST_PAGE_WHEN_RESUME)
            menu_pm_show_by_latest_state()
#elif  defined(APP_MENU_GO_LATEST_TAB_WHEN_RESUME)
            menu_pm_show_by_latest_tab()
#else
            menu_pm_show()
#endif
              != MENUR_OK)
            {
                _menu_freeze_banner(FALSE);
                DBG_ERROR(("<MENU>menu_pm_show() fail.\n"));
                return ;
            }
        }while(0);

        _change_menu_cond(MENU_COND_SHOW);
    }
   // DBG_INFO(("[MENU][%s %d] cost %d ms \n",__FUNCTION__,__LINE__,c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick)));

    if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
    {
        DBG_LOG_PRINT(("[RC +++] {%s %s() %d}. @@short press menu disable zoom navigation mode!!\n",__FILE__, __FUNCTION__, __LINE__));
        /*short press menu to disable zoom navigation mode*/
        a_nav_zoom_cust_long_press_menu(FALSE);
    }

    t_send_cmd.s_source = "browser_ctrl";
    t_send_cmd.s_destination = "browser_ctrl";
    t_send_cmd.s_ack = NULL;
    t_send_cmd.s_command = "widget_ui_show=browser_ctrl";
    t_send_cmd.s_parameter = NULL;
    a_msg_convert_send_command(&t_send_cmd);

#ifdef APP_REGISTRY_SUPPORT
    a_registry_set_menu_ui_state(REG_UI_STATE_VISIBLE);
#endif

    DBG_LOG_PRINT(("<MENU>Finsh resume\n"));
    MENU_TMS_SPLIT("resume_done");
}

static VOID _menu_resume()
{
    menu_request_context_switch(_menu_resume_fct,NULL,NULL,NULL);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_app_resume_fct
 *
 * Description:
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_app_resume_fct (
    HANDLE_T  h_app)
{
    _menu_resume();
    return AEER_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _menu_app_pause_fct
 *
 * Description:
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_app_pause_fct (
    HANDLE_T  h_app)
{
    INT32 i4_ret;
   // UINT32 tick =  c_os_get_sys_tick();
    DBG_INFO(("<MENU>Pause\n\r"));

    /* reset the version string */
    menu_version_key_filter(0);
    menu_show_version(FALSE, FALSE);

    do
    {
         /* MENU pause logic */
        t_g_menu_common.b_is_pausing = TRUE;

        i4_ret = menu_custom_dialog_hide_dialog();
        if(i4_ret != MENUR_OK)
        {
                break;
        }

        i4_ret = menu_custom_exit_menu_actions();
        if(i4_ret != MENUR_OK)
        {
                break;
        }

        /* Custom-specific resume logic */
        i4_ret = menu_custom_pause();
        if(i4_ret != MENUR_OK)
        {
                break;
        }

        menu_show_backbar(FALSE, FALSE);

        /* Hiding logic. Always put it at the last */
        if(e_menu_cond == MENU_COND_SHOW)
        {

            DBG_INFO(("<MENU>Hide ATSC\n\r"));
#if 0
            #ifdef APP_ZOOM_MODE_SUPPORT
            a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DEFAULT));
            #endif
#endif
            i4_ret = menu_pm_hide();
            if(i4_ret != MENUR_OK)
            {
                break;
            }

            /* stop the timer */
            b_timer_enabled = FALSE;
            MENU_DEBUG_TIMEOUT(
                DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}b_timer_enabled=%d\n",
                    __FUNCTION__,__LINE__, b_timer_enabled ));
            );

            menu_timer_stop();
        }

        /* Store the channel lists */
        menu_common_store_ch_list();

        _change_menu_cond(MENU_COND_PAUSE);

        DBG_INFO(("<MENU>Finish Hide\n\r"));

        c_wgl_set_highlight_widget(NULL_HANDLE);

        t_g_menu_common.b_is_hot_key_enter = FALSE;
        t_g_menu_common.b_is_pausing = FALSE;
        b_g_resume_menu = FALSE;

#ifdef APP_REGISTRY_SUPPORT
        a_registry_set_menu_ui_state(REG_UI_STATE_INVISIBLE);
#endif
       // DBG_INFO(("[MENU][%s %d] crost %d ms \n",__FUNCTION__,__LINE__,c_os_get_sys_tick_period()* (c_os_get_sys_tick() - tick)));
        return AEER_OK;
    }while(0);

    t_g_menu_common.b_is_pausing = FALSE;

    return AEER_FAIL;
}


/*-----------------------------------------------------------------------------
 * Name: _menu_app_exit_fct
 *
 * Description:
 *
 * Inputs:  h_app               Contains the application handle.
 *          e_exit_mode         Contains the exit mode.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_app_exit_fct (
    HANDLE_T         h_app,
    APP_EXIT_MODE_T  e_exit_mode)
{
    INT32 i4_ret;

    DBG_INFO(("<MENU>Exit\n\r"));

    i4_ret = menu_custom_exit();
    if(i4_ret != AEER_OK)
    {
        return AEER_FAIL;
    }

    _change_menu_cond(MENU_COND_NOT_INIT);

    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_app_process_msg_fct
 *
 * Description:
 *
 * Inputs:  h_app               Contains the application handle.
 *          ui4_type            Contains the type of the data contained in
 *                              pv_msg, or simple a request type. Values are
 *                              defined by the application.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *          b_paused            Sepcifies whether the application is currently
 *                              paused.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
extern BOOL b_g_wps_is_associating;

static VOID _menu_monitor_msg_timeout_nfy_fct(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    MENU_MONOTOR_T* pt_monitor = (MENU_MONOTOR_T*)pv_tag;
    VOID *          pv_fun     = NULL;
    if (NULL == pv_tag)
    {
        return;
    }

    if(MENU_MSG_ASYNC_INVOKE == pt_monitor->ui4_msg_type ||
       MENU_MSG_AM_ASYNC_INVOKE == pt_monitor->ui4_msg_type)
    {
       MENU_MSG_AM_ASYNC_INVOKE_T* pt_async = (MENU_MSG_AM_ASYNC_INVOKE_T*)pt_monitor->pv_msg;
       backtrace_symbols_fd((void *const *)&pt_async->pf_async_func, 1, 1);
    }
    else if(MENU_REQ_CTX_SWITCH_EVENT == pt_monitor->ui4_msg_type)
    {
       MENU_EVN_T*    pt_event = (MENU_EVN_T*)pt_monitor->pv_msg;
       backtrace_symbols_fd((void *const *)(&pt_event->ui4_data1), 1, 1);
    }

    DBG_LOG_PRINT(("%s() monitor menu handle msg type=[%d] over 5s \n",__FUNCTION__,
                                                                    pt_monitor->ui4_msg_type));
}

static INT32 _menu_app_process_msg_fct (
                    HANDLE_T     h_app,
                    UINT32       ui4_type,
                    const VOID*  pv_msg,
                    SIZE_T       z_msg_len,
                    BOOL         b_paused)
{
    INT32   i4_ret = AEER_OK;
    BOOL    b_processed;
    UINT32  ui4_key_code = 0;
    MENU_MONOTOR_T  t_monitor = {0,NULL};

    if (NULL_HANDLE == h_moni_timer)
    {
        (VOID)c_timer_create(&h_moni_timer);
    }
    t_monitor.ui4_msg_type = ui4_type;
    t_monitor.pv_msg       = pv_msg;

    if (NULL_HANDLE != h_moni_timer)
    {
        c_timer_start(h_moni_timer,
                      _MENU_MONITOR_MSG_TIME,
                      X_TIMER_FLAG_ONCE,
                      _menu_monitor_msg_timeout_nfy_fct,
                      (VOID *)&t_monitor);
        DBG_API(("%s()start monitor.\n",__FUNCTION__));
    }

    if (ui4_type == MENU_MSG_WGL_NOTIFY)
    {
        MENU_MSG_WGL_NOTIFY_T* pt_msg_wgl_notify = (MENU_MSG_WGL_NOTIFY_T*)pv_msg;
        if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN ||
            pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_UP ||
            pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_REPEAT)
        {
            /*when zoom mode is on/off,long press menu key to en/disable navigtaion zoom mode,
                       when navigtaion zoom is on/off,and dis/enable direction pad for menu
                       DTV02083281*/
            UINT32  ui4_keycode = (UINT32)pt_msg_wgl_notify->pv_param1;
            if( ui4_keycode == BTN_CURSOR_LEFT  ||
                ui4_keycode == BTN_CURSOR_RIGHT ||
                ui4_keycode == BTN_CURSOR_UP    ||
                ui4_keycode == BTN_CURSOR_DOWN  ||
                ui4_keycode == BTN_SELECT)
            {
              if (b_timer_enabled == TRUE && pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN)
              {
                  menu_timer_start();
              }
              if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
              {
                  DBG_LOG_PRINT(("[RC +++] {%s %s() %d}. @@return navigation zoom mode is on,disable direction pad.!!!; return MENUR_OK; \n",__FILE__, __FUNCTION__, __LINE__));
                  c_timer_stop(h_moni_timer);
                  return MENUR_OK;
              }
            }
            if( ui4_keycode == BTN_EXIT)
            {
                if (b_timer_enabled == TRUE)
                {
                    menu_timer_start();
                }
            }
        }
    }
    if (b_g_wps_is_associating && (ui4_type == MENU_MSG_WGL_NOTIFY))
    {
        MENU_MSG_WGL_NOTIFY_T* pt_msg_wgl_notify_process = (MENU_MSG_WGL_NOTIFY_T*)pv_msg;

        if(pt_msg_wgl_notify_process->ui4_msg == WGL_MSG_KEY_DOWN ||
           pt_msg_wgl_notify_process->ui4_msg == WGL_MSG_KEY_REPEAT ||
           pt_msg_wgl_notify_process->ui4_msg == WGL_MSG_KEY_UP)
        {
            if (BTN_EXIT == (UINT32)pt_msg_wgl_notify_process->pv_param1)
            {
                pt_msg_wgl_notify_process->pv_param1 = (VOID*)BTN_SELECT;
            }
        }
    }

    if (ui4_type == MENU_MSG_WGL_NOTIFY)
    {

        MENU_MSG_WGL_NOTIFY_T* pt_msg_wgl_notify_process = (MENU_MSG_WGL_NOTIFY_T*)pv_msg;
        if(pt_msg_wgl_notify_process->ui4_msg == WGL_MSG_KEY_DOWN ||
           pt_msg_wgl_notify_process->ui4_msg == WGL_MSG_KEY_REPEAT)
        {
            if (BTN_VOL_UP == (UINT32)pt_msg_wgl_notify_process->pv_param1 ||
                BTN_VOL_DOWN == (UINT32)pt_msg_wgl_notify_process->pv_param1)
            {
                DBG_INFO(("<zanchen>---%s: %d\r\n", __func__, __LINE__));
                //a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)(UINT32)pt_msg_wgl_notify_process->pv_param1, NULL);
                a_amb_default_key_handler_ex (WGL_MSG_KEY_DOWN, (VOID*)(UINT32)pt_msg_wgl_notify_process->pv_param1, NULL);
                c_timer_stop(h_moni_timer);
                return i4_ret;
            }
        }
    }

    if ((t_g_menu_is_scanning) && (ui4_type == MENU_MSG_WGL_NOTIFY))
    {
        do
        {
            MENU_MSG_WGL_NOTIFY_T* pt_msg_wgl_notify_process = (MENU_MSG_WGL_NOTIFY_T*)pv_msg;

            if(pt_msg_wgl_notify_process->ui4_msg == WGL_MSG_KEY_DOWN ||
               pt_msg_wgl_notify_process->ui4_msg == WGL_MSG_KEY_REPEAT )
            {
                UINT32  ui4_evt_code = (UINT32)pt_msg_wgl_notify_process->pv_param1;
                if (ui4_evt_code == BTN_SELECT || ui4_evt_code == BTN_CUSTOM_1
                    || (IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_INPUT_SRC
                        && IOM_GET_EVT_SRC(ui4_evt_code) == KEY_SRC_FRONT_PANEL))
                {
                    break;
                }
            }
            c_timer_stop(h_moni_timer);
            return MENUR_OK;
        }
        while(0);
    }

    i4_ret = menu_custom_process_msg(
                    ui4_type,
                    pv_msg,
                    z_msg_len,
                    &b_processed);
    if(b_processed)
    {
        /* the message has been processed in solution-specific message
           processing function */
        c_timer_stop(h_moni_timer);
        return i4_ret;
    }
    else
    {
        /* the mesage hasn't been processed in solution-specific message
           processing function, reset i4_ret */
        i4_ret = AEER_OK;
    }

#ifdef APP_MENU_CUSTOM_IOM_NFY_FCT
    i4_ret = menu_custom_fct_process_msg(
                    ui4_type,
                    pv_msg,
                    z_msg_len,
                    &b_processed);
    if(b_processed)
    {
        /* the message has been processed in solution-specific message
           processing function */
        c_timer_stop(h_moni_timer);
        return i4_ret;
    }
    else
    {
        /* the mesage hasn't been processed in solution-specific message
           processing function, reset i4_ret */
        i4_ret = AEER_OK;
    }
#endif

    /* Menu message */
    switch (ui4_type)
    {
    case MENU_MSG_WGL_NOTIFY:
        {
            BOOL    b_to_fac = FALSE;
            MENU_MSG_WGL_NOTIFY_T* pt_msg_wgl_notify = (MENU_MSG_WGL_NOTIFY_T*)pv_msg;
            UINT32   ui4_evt_code = (UINT32)pt_msg_wgl_notify->pv_param1;

            if(e_menu_cond == MENU_COND_SHOW)
            {
                /* schedule the timer */

                /* Enable auto key repeat */
                if(b_g_auto_key_repeat)
                {
                    if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_REPEAT)
                    {
                        pt_msg_wgl_notify->ui4_msg = WGL_MSG_KEY_DOWN;
                    }
                }

                /*Key down*/
                if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN)
                {

                    b_to_fac = menu_version_key_filter(ui4_evt_code);

                    #ifdef UI_TOGGLE_VIDEO_OUT_FMT
                    if(ui4_evt_code == BTN_ADD_ERASE)
                    {
                        a_ctrl_panel_toggle_output_fmt();
                    }
                    #endif
                    if(BTN_MENU==ui4_evt_code)
                    {
                        menu_leave(FALSE,0);
                    }
                    else if(BTN_EXIT==ui4_evt_code)
                    {
                        if(!t_g_menu_is_scanning)
                        {
                            menu_leave(FALSE,0);
                        }
                    }
                }
#ifdef APP_ZOOM_MODE_SUPPORT
                else if (pt_msg_wgl_notify->ui4_msg == WGL_MSG_NOTIFY_HL_AREA)
                {
                    a_zoom_mode_enlarge_wgl_hl_area(ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DEFAULT), (GL_RECT_T *)(pt_msg_wgl_notify->pv_param2));
                    b_to_fac = TRUE;
                }
#endif
                if(!b_to_fac)
                {
                    c_wgl_dispatch_event(pt_msg_wgl_notify->ui4_msg,
                                         pt_msg_wgl_notify->pv_param1,
                                         pt_msg_wgl_notify->pv_param2);
                }

            }

            break;
        }
    case MENU_MSG_SHOW:
        {
            BOOL b_focus_first_tab = *((BOOL*)pv_msg);
            UINT16 ui2_tab_idx = 0;

            if (e_menu_cond == MENU_COND_HIDE)
            {
                b_timer_enabled = TRUE;
                MENU_DEBUG_TIMEOUT(
                    DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}b_timer_enabled=%d\n",
                        __FUNCTION__,__LINE__, b_timer_enabled ));
                );

                menu_timer_start();

                _change_menu_cond(MENU_COND_SHOW);

                if(b_focus_first_tab == TRUE)
                {
                    ui2_tab_idx = 0;
                }
                else
                {
                    menu_pm_get_tab_num(&ui2_tab_idx);
                    ui2_tab_idx--;
                }

                menu_pm_show_with_tab(ui2_tab_idx);
            }
            break;
        }
    case MENU_MSG_ASYNC_INVOKE:
        {
            MENU_MSG_ASYNC_INVOKE_T* pt_msg_async =
                (MENU_MSG_ASYNC_INVOKE_T*)pv_msg;
            if(z_msg_len <= 4)
            {
                pt_msg_async->pf_async_func(NULL, 0);
            }
            else
            {
                pt_msg_async->pf_async_func(pt_msg_async->aui1_data,
                                            z_msg_len - 4);
            }

            break;
        }
    case MENU_MSG_AM_ASYNC_INVOKE:
        {
            MENU_MSG_AM_ASYNC_INVOKE_T* pt_msg_am_async =
                (MENU_MSG_AM_ASYNC_INVOKE_T*)pv_msg;
            if(z_msg_len <= 4)
            {
                pt_msg_am_async->pf_async_func(NULL, 0);
            }
            else
            {
                pt_msg_am_async->pf_async_func(pt_msg_am_async->aui1_data,
                                               z_msg_len - 4);
            }
            break;
        }
#ifdef APP_IPCC_SUPPORT
    case MENU_MSG_AM_ASYNC_IPCC_CHG:
        {
            UINT8 ui1_enabled = 1;

            ui1_enabled = (a_tv_net_get_IPCC_status() == TRUE) ? 1 : 0;

            DBG_INFO(("%s() menu received msg for ipcc changed to [%d].\n",
                                                    __FUNCTION__, ui1_enabled));

            if (APP_CFGR_OK == a_cfg_set_cc_enabled(ui1_enabled))
            {
                a_cfg_custom_plf_opt_set_cc_onoff(ui1_enabled);
            }

            break;
        }
#endif
    case MENU_MSG_FACTORY_KEY:
        {
            UINT8   ui1_fac_mode = APP_CFG_FAC_MODE_NORMAL;
            a_cfg_get_factory_mode(&ui1_fac_mode);

            if((ui1_fac_mode & APP_CFG_FAC_MODE_FACTORY_MASK) == 0)
            {
                ui1_fac_mode = (UINT8)(ui1_fac_mode | APP_CFG_FAC_MODE_FACTORY_MASK);
                /* If it is not in factory mode, enter factory mode */
                a_cfg_set_factory_mode(ui1_fac_mode);

                a_cfg_update_factory_mode();

                /* flush the settings to storage right away */
                a_cfg_store();
            }

            if(menu_get_cond() == MENU_COND_PAUSE)
            {
                a_amb_resume_app(MENU_NAME);
            }
            else if(menu_get_cond() == MENU_COND_SHOW)
            {
                menu_nav_go_to_factory_page();
            }
        }
        break;

    case MENU_REQ_CTX_SWITCH_EVENT:
    {
        MENU_EVN_T*    pt_event = (MENU_EVN_T*)pv_msg;
        menu_context_switch_nfy_fct pf_fct  = (menu_context_switch_nfy_fct)pt_event->ui4_data1;
        VOID*                      pv_tag  = (VOID*)pt_event->ui4_data2;
        VOID*                      pv_tag2 = (VOID*)pt_event->ui4_data3;
        VOID*                      pv_tag3 = (VOID*)pt_event->ui4_data4;

        if (pf_fct != NULL) {
            pf_fct(pv_tag, pv_tag2, pv_tag3);
        }

        break;
    }

    default:
        i4_ret = AEER_OK;
        break;
    }

    /* AM Messages */
    switch(ui4_type)
    {
    case AM_BRDCST_MSG_SYSTEM_KEY:
        {
            UINT32 ui4_key_code = *((UINT32*)pv_msg);

            /* [DTV00006906] */
            /* Clear the key source, mapping BTN_MENU from Ctrl Panel to IR */
            ui4_key_code = IOM_GET_EVT_GRP_ID(ui4_key_code);

            _wgl_callback(WGL_MSG_KEY_DOWN,
                          (VOID*)ui4_key_code,
                          0);

            break;
        }
    case AM_BRDCST_MSG_CHANNEL_SCAN_ACTIVE:
        {
            t_g_menu_is_scanning = TRUE;
            MENU_DEBUG_TIMEOUT(
                DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} t_g_menu_is_scanning=%d\n",
                    __FUNCTION__,__LINE__, t_g_menu_is_scanning ));
            );

            menu_timer_stop();
            break;
        }
    case AM_BRDCST_MSG_CHANNEL_SCAN_INACTIVE:
        {
            t_g_menu_is_scanning = FALSE;
            MENU_DEBUG_TIMEOUT(
                DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} t_g_menu_is_scanning=%d\n",
                    __FUNCTION__,__LINE__, t_g_menu_is_scanning ));
            );

            if (b_timer_enabled == TRUE)
            {
                menu_timer_start();
            }
            break;
        }
    case AM_BRDCST_MSG_APP_PAUSED:
        {
            const CHAR *ps_name = (const CHAR *)pv_msg;

            if (c_strncmp(ps_name, MENU_NAME, c_strlen(MENU_NAME)) == 0)
            {
                DBG_INFO(("%s() menu pause and reset screen blank.\n",__FUNCTION__);
                nav_request_context_switch(a_scrn_blank_act,
                                            (VOID*)SCRN_BLANK_CONTEXT_SWITCH_4_RESET,
                                            NULL,
                                            NULL));
                menu_pic_energy_change_toast_view();
            }

            switch (ui4_g_delay_proc_input_key)
            {
                case BTN_INPUT_SRC:
                case BTN_ASPECT:
                {
                    ui4_key_code = ui4_g_delay_proc_input_key;
                    ui4_g_delay_proc_input_key = DELAY_UNDEF_KEY;

                    DBG_INFO(("_menu_app_process_msg_fct() key code[0x%x] Delay %dms begin\n",
                                                            ui4_key_code,
                                                            INPUT_KEY_PROC_DELAY));
                    c_thread_delay(INPUT_KEY_PROC_DELAY);

                    DBG_INFO(("_menu_app_process_msg_fct() key code[0x%x] Delay %dms end\n",
                                                            ui4_key_code,
                                                            INPUT_KEY_PROC_DELAY));
                    a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                    break;
                }
                case DELAY_UNDEF_KEY:
                default:
                    break;
            }

            i4_ret = AEER_OK;
            break;
        }
    case AM_BRDCST_MSG_APP_ACTIVE:
        {
            const CHAR *ps_name = (const CHAR *)pv_msg;

            if (c_strncmp(ps_name, MENU_NAME, c_strlen(MENU_NAME)) == 0)
            {
                if (a_scrn_blank_is_acting())
                {
                    DBG_INFO(("%s() menu active and reset screen blank.\n",__FUNCTION__));
                    a_scrn_blank_reset();
                }

                _menu_freeze_banner(FALSE);
            }

            i4_ret = AEER_OK;
            break;
        }
    case AM_BRDCST_MSG_POWER_ON:
        {
             BOOL   b_is_lock_status = FALSE;
             a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);
             b_is_picture_lock  = b_is_lock_status;

             menu_custom_unblank_screen(ui4_type);
        }
        break;
    case AM_BRDCST_MSG_POWER_OFF:
        {
            if(a_ramp_test_pattern_is_on() && (!menu_get_factory_reset_status()))
            {
                DBG_INFO(("%s(%d) AM_BRDCST_MSG_POWER_OFF--a_color_tuner_recover_rgb_cfg_value\n",__FUNCTION__,__LINE__));
                a_color_tuner_recover_rgb_cfg_value();
            }
            menu_pic_erengy_change_toast_reset_status();
        }
        break;
    case MENU_MSG_LONG_KEY_PRESS:
    {
        UINT32 ui4_long_key = *((UINT32 *)pv_msg);

        if(BTN_LONG_CC == ui4_long_key
            || BTN_GFX_ZOOM == ui4_long_key
            || BTN_LONG_P_EFFECT == ui4_long_key)
        {
            if (a_menu_is_resume())
            {
                menu_pm_repaint();
                menu_pm_refresh();
            }
        }

        break;
    }
    default:
        i4_ret = AEER_OK;
        break;
    }

    c_timer_stop(h_moni_timer);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: menu_set_power_off_flag
 *
 * Description: Set show power off warning dialog flag
 *
 * Inputs:  b_show      Need show power off warning dialog
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID menu_set_power_off_flag(BOOL b_show)
{
    b_g_is_need_power_off_dlg_show = b_show;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_show_power_off_dlg_hdlr
 *
 * Description: This callback function is called when end user press tv power button.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _menu_show_power_off_dlg_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
    menu_add_new_device_power_off_warning_dlg_show();
}

/*-----------------------------------------------------------------------------
 * Name: _menu_app_system_key_fct
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _menu_app_system_key_fct (
                    UINT32       ui4_evt_code
)
{
    if (!menu_custom_system_key_cb(ui4_evt_code))
    {
        return FALSE;
    }

    if (t_g_menu_is_scanning == TRUE)
    {
        /* Multimedia */
        UINT32                 ui4_key_code;
        ui4_key_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);
        if (IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_MEM_CARD)
        {
            return FALSE;
        }

        if (ui4_key_code != BTN_POWER
            && ui4_key_code != BTN_POWER_OFF)
        {
            return FALSE;
        }
    }
    /* show power off warning dialog */
    if (BTN_POWER == ui4_evt_code
        && b_g_is_need_power_off_dlg_show)
    {
        menu_request_context_switch(_menu_show_power_off_dlg_hdlr,
                                    NULL,
                                    NULL,
                                    NULL);
        return FALSE;
    }
    return TRUE;
}

static VOID _change_menu_cond(MENU_COND_T _e_menu_cond)
{
    e_menu_cond = _e_menu_cond;
    menu_lock();
    if (pf_menu_nfy != NULL)
    {
        pf_menu_nfy(e_menu_cond);
    }
    menu_unlock();
}


/*-----------------------------------------------------------------------------
                    public functions implementation
 ----------------------------------------------------------------------------*/




/*----------------------------------------------------------------------------
 * Name: menu_start_timer
 *
 * Description:
 *       Start the timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 menu_timer_start(VOID)
{
#ifdef APP_MENU_TIMER_ENABLE

    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}\n",
            __FUNCTION__,__LINE__ ));
    );


    INT32 i4_ret;
    if (!menu_timer_is_enabled())
    {
        return MENUR_OK;
    }

    menu_timer_stop();

    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} call c_timer_start(ui4_timer_delay:%d)\n",
            __FUNCTION__,__LINE__, ui4_timer_delay ));
    );

    i4_ret = c_timer_start(h_timer,
                           ui4_timer_delay,
                           X_TIMER_FLAG_ONCE,
                           _timer_nfy_fct,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    return  MENUR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: menu_stop_timer
 *
 * Description:
 *       Stop the timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_timer_stop(VOID)
{
    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}\n",
            __FUNCTION__,__LINE__ ));
    );

    INT32 i4_ret;
    i4_ret = c_timer_stop(h_timer);
    return i4_ret == OSR_OK ? MENUR_OK : MENUR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: menu_timer_enable
 *
 * Description:
 *       Enable/Disable the timer.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID menu_timer_enable(BOOL b_enable)
{
    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} b_enable:%d\n",
            __FUNCTION__,__LINE__, b_enable ));
    );

    b_timer_enabled = b_enable;

    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}b_timer_enabled=%d\n",
            __FUNCTION__,__LINE__, b_timer_enabled ));
    );
}

/*----------------------------------------------------------------------------
 * Name: menu_timer_is_enabled
 *
 * Description:
 *       If menu timer is enabled.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
BOOL menu_timer_is_enabled(VOID)
{
    BOOL bMenuIsNotScanning = !t_g_menu_is_scanning;
    BOOL b_menu_custom_is_not_blank_screen = !menu_custom_is_blank_screen();


    BOOL bTimer_is_enabled = 0;
    if( b_oled
     && b_timer_enabled
     && bMenuIsNotScanning
     && b_menu_custom_is_not_blank_screen )
    {
        bTimer_is_enabled = 1;
    }


    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} b_oled:%d, b_timer_enabled:%d, bMenuIsNotScanning:%d, b_menu_custom_is_not_blank_screen:%d\n",
            __FUNCTION__,__LINE__, b_oled, b_timer_enabled,
            bMenuIsNotScanning, b_menu_custom_is_not_blank_screen ));
    );


    return bTimer_is_enabled;

    //return b_oled && b_timer_enabled && !t_g_menu_is_scanning && menu_custom_is_blank_screen() == FALSE;
}
/*----------------------------------------------------------------------------
 * Name: menu_timer_set_delay
 *
 * Description:
 *       Set the delay time of menu timeout. The delay value could not be 0.
 *
 * Inputs:
 *      ui4_delay - the delay time
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_timer_set_delay(
    UINT32 ui4_delay)
{
    if(ui4_delay == 0)
    {
        return MENUR_INV_ARG;
    }

    ui4_timer_delay = ui4_delay;

    MENU_DEBUG_TIMEOUT(
        DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d} ui4_timer_delay=%d\n",
            __FUNCTION__,__LINE__, ui4_timer_delay ));
    );

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_lock
 *
 * Description:
 *       Lock the menu mutex semaphore.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID menu_lock(VOID)
{
    c_sema_lock(h_mtx_sema, X_SEMA_OPTION_WAIT);
}

/*----------------------------------------------------------------------------
 * Name: menu_unlock
 *
 * Description:
 *       Unlock the menu mutex semaphore.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID menu_unlock(VOID)
{
    c_sema_unlock(h_mtx_sema);
}

/*----------------------------------------------------------------------------
 * Name: menu_enable_auto_key_repeat
 *
 * Description:
 *  If this option is on, it would remap all WGL_MSG_KEY_REPEAT to WGL_MSG_KEY_DOWN.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_enable_auto_key_repeat(MENU_AUTO_KEY_REPEAT_T  e_auto_key_repeat)
{
    if(e_auto_key_repeat == MENU_AUTO_KEY_REPEAT_ON)
    {
        b_g_auto_key_repeat = TRUE;
    }
    else if(e_auto_key_repeat == MENU_AUTO_KEY_REPEAT_OFF)
    {
        b_g_auto_key_repeat = FALSE;
    }
    else
    {
        b_g_auto_key_repeat = MENU_AUTO_KEY_REPEAT;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_leave
 *
 * Description:
 *       Leave the menu application.
 *
 * Inputs:
 *      BOOL b_back - leave menu by back operation. If menu is in slave mode, it
 *          will not pause menu until the atv menu leaves as well.
 *      ui4_hide_delay - If b_back is true and menu in slave mode, the value
 *          is used to delay the hide operation. It will avoid flicking when
 *          flicking between ATV and DTV menu
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID menu_leave(BOOL b_back, UINT32 ui4_hide_delay)
{
    if(b_back && b_slave_mode == TRUE)
    {
        _change_menu_cond(MENU_COND_HIDE);
        c_thread_delay(ui4_hide_delay);
        menu_pm_hide();

        b_timer_enabled = FALSE;
        MENU_DEBUG_TIMEOUT(
            DBG_LOG_PRINT(("[MENU][TIMEOUT]{%s,%d}b_timer_enabled=%d\n",
                __FUNCTION__,__LINE__, b_timer_enabled ));
        );

        menu_timer_stop();
    }
    else
    {
        a_amb_pause_app(MENU_NAME);
    }

}

/*----------------------------------------------------------------------------
 * Name: menu_async_invoke
 *
 * Description:
 *      Invoke a function in the menu thread context.
 *
 * Inputs:
 *      menu_async_func - The asynchronous function to call
 *      pv_data - The data of the the callback function. This parameter could be
 *                NULL, which is used to send NO data.
 *      z_data_len - The data length of pv_data. If the pv_data is NULL,
 *                   the z_data_len is ignored and the actual data len will be
 *                   zero.
 *      b_retry - Retry or not if message queue is full
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_async_invoke(menu_async_func  pf_async_func,
                        VOID*            pv_data,
                        SIZE_T           z_data_len,
                        BOOL             b_retry)
{
    INT32                   i4_ret;
    MENU_MSG_ASYNC_INVOKE_T t_msg_async;
    UINT16                  ui2_retry;

    if(pf_async_func == NULL)
    {
        return MENUR_INV_ARG;
    }
    if(e_menu_cond == MENU_COND_NOT_INIT){
        DBG_ERROR(("<MENU> L%d Cannot send async invoke message! menu not inited\n", __LINE__));
        return MENUR_FAIL;
    } else if(h_app_menu == NULL_HANDLE){
        DBG_ERROR(("<MENU> L%d Cannot send async invoke message!", __LINE__));
        return MENUR_FAIL;
    }
    if(b_retry)
    {
        ui2_retry = 30;
    }
    else
    {
        ui2_retry = 0;
    }

    c_memset(&t_msg_async, 0, sizeof(MENU_MSG_ASYNC_INVOKE_T));
    t_msg_async.pf_async_func = pf_async_func;
    if(pv_data != NULL)
    {
        if(z_data_len <= MENU_ASYNC_DATA_THRESHOLD)
        {
            c_memcpy(t_msg_async.aui1_data,
                     pv_data,
                     z_data_len);
        }
        else
        {
            DBG_ERROR(("<MENU> Aysnc data size is too big: %d>%d",
                       z_data_len,
                       MENU_ASYNC_DATA_THRESHOLD));
            return MENUR_INV_ARG;
        }
    }

    /* Send the message to the menu message queue. */
    do
    {
        i4_ret = c_app_send_msg(h_app_menu,
                        MENU_MSG_ASYNC_INVOKE,
                        &t_msg_async,
                        z_data_len + 4,
                        NULL,
                        NULL);
        if(i4_ret != AEER_OK)
        {
            if(ui2_retry > 0)
            {
                DBG_ERROR(("<MENU>L%d Cannot send async invoke message! ret:%d, send again!\r\n", __LINE__, i4_ret));
                c_thread_delay(100);
                ui2_retry--;
            }
            else
            {
                DBG_ERROR(("<MENU>L%d Cannot send async invoke message! ret:%d\r\n", __LINE__, i4_ret));
                break;
            }
        }
        else
        {
            break;
        }
    } while (TRUE);

    return i4_ret == AEER_OK ? MENUR_OK : MENUR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: menu_am_async_invoke
 *
 * Description:
 *      Invoke a function in the menu thread context.
 *
 * Inputs:
 *      menu_async_func - The asynchronous function to call
 *      pv_data - The data of the the callback function. This parameter could be
 *                NULL, which is used to send NO data.
 *      z_data_len - The data length of pv_data. If the pv_data is NULL,
 *                   the z_data_len is ignored and the actual data len will be
 *                   zero.
 *      b_retry - Retry or not if message queue is full
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_am_async_invoke(
    menu_async_func  pf_async_func,
    VOID*            pv_data,
    SIZE_T           z_data_len,
    BOOL             b_retry)
{
    INT32                       i4_ret;
    MENU_MSG_AM_ASYNC_INVOKE_T  t_msg_am_async;
    UINT16                      ui2_retry;

    if(pf_async_func == NULL)
    {
        return MENUR_INV_ARG;
    }

    if(b_retry)
    {
        ui2_retry = 30;
    }
    else
    {
        ui2_retry = 0;
    }

    c_memset(&t_msg_am_async, 0, sizeof(MENU_MSG_AM_ASYNC_INVOKE_T));
    t_msg_am_async.pf_async_func = pf_async_func;
    if(pv_data != NULL)
    {
        if(z_data_len <= MENU_AM_ASYNC_DATA_THRESHOLD)
        {
            c_memcpy(t_msg_am_async.aui1_data,
                     pv_data,
                     z_data_len);
        }
        else
        {
            DBG_ERROR(("<MENU> Aysnc data size is too big: %d>%d",
                       z_data_len,
                       MENU_AM_ASYNC_DATA_THRESHOLD));
            return MENUR_INV_ARG;
        }
    }

    /* Send the message to the menu message queue through AM. */
    do
    {
        i4_ret = a_amb_dispatch_msg(MENU_NAME,
                                    MENU_MSG_AM_ASYNC_INVOKE,
                                    &t_msg_am_async,
                                    z_data_len + 4);
        if(i4_ret != AMBR_OK)
        {
            if(ui2_retry > 0)
            {
                DBG_ERROR(("<MENU>Cannot send async invoke message! resend again!\r\n"));
                c_thread_delay(100);
                ui2_retry--;
            }
            else
            {
                DBG_ERROR(("<MENU>Cannot send async invoke message!\r\n"));
                break;
            }
        }
        else
        {
            break;
        }
    } while (TRUE);

    return i4_ret == AEER_OK ? MENUR_OK : MENUR_FAIL;
}

extern MENU_COND_T menu_get_cond()
{
    return e_menu_cond;
}


/*-----------------------------------------------------------------------------
 * Name
 *      menu_request_context_switch
 * Description
 *      The API is used to request a function execution in menu's
 *      thread context.
 * Input arguments
 *      pf_fct          The function to be executed.
 *      pv_tag1         The first argument to pass to pf_fct.
 *      pv_tag2         The second argument to pass to pf_fct.
 *      pv_tag3         The third argument to pass to pf_fct.
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK         the routine is successfully.
 *      NAVR_INV_ARG    The pf_fct is NULL.
 *      NAVR_FAIL       The message queue of Navigator is failed to send message.
 *---------------------------------------------------------------------------*/
INT32 menu_request_context_switch(
                    menu_context_switch_nfy_fct      pf_fct,
                    VOID*                           pv_tag1,
                    VOID*                           pv_tag2,
                    VOID*                           pv_tag3
                    )
{
    MENU_EVN_T t_event;

    UINT32       ui4_retry_count = 0;
    INT32        i4_ret;

    if (pf_fct == NULL) {
        return MENUR_INV_ARG;
    }

    t_event.ui4_data1  = (UINT32)pf_fct;
    t_event.ui4_data2  = (UINT32)pv_tag1;
    t_event.ui4_data3  = (UINT32)pv_tag2;
    t_event.ui4_data4  = (UINT32)pv_tag3;

    while (ui4_retry_count < MENU_MSGQ_RESEND_TIMES) {
        i4_ret = c_app_send_msg (
                    h_app_menu,
                    MENU_REQ_CTX_SWITCH_EVENT,
                    &t_event,
                    sizeof(MENU_EVN_T),
                    NULL,
                    NULL
                    );
        if (i4_ret == AEER_OK) {
            break;
        } else {
            /*c_thread_delay(MSG_RESEND_FAILED_SLEEP_TIME);*/
            ui4_retry_count++;
        }
    }

    if(i4_ret != AEER_OK)
    {
        /*DBG_ERROR((_ERROR_HEADER"c_app_send_msg() failed. i4_ret = %d/r/n.", i4_ret));*/
        DBG_ERROR(("wzd c_app_send_msg(MENU_REQ_CTX_SWITCH_EVENT) failed. i4_ret = %d\n.", i4_ret));
    }

    return i4_ret == AEER_OK ? MENUR_OK : MENUR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: menu_idx_to_langcode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID menu_idx_to_langcode(UINT16 ui2_idx, ISO_639_LANG_T s639_lang)
{
#ifdef APP_MLM_S639_TO_LANGIDX_SUPPORT
    mlm_menu_langidx_to_s639(ui2_idx, s639_lang);
#else
    UINT16 ui2_i;
    for(ui2_i=0; ui2_i < ui2_langmap_size; ui2_i++)
    {
        if(at_langmap[ui2_i].ui2_lang == ui2_idx)
        {
            c_strncpy(s639_lang, at_langmap[ui2_i].s639_lang, ISO_639_LANG_LEN);
            break;
        }
    }

    if(ui2_i == ui2_langmap_size)
    {
        c_strncpy(s639_lang, at_langmap[0].s639_lang, ISO_639_LANG_LEN);
    }
#endif
}

/*----------------------------------------------------------------------------
 * Name: menu_langcode_to_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
VOID menu_langcode_to_idx(ISO_639_LANG_T s639_lang, UINT16* pui2_idx)
{
#ifdef APP_MLM_S639_TO_LANGIDX_SUPPORT
    *pui2_idx = mlm_menu_s639_to_langidx(s639_lang);
#else
    UINT16 ui2_i;
    for(ui2_i=0; ui2_i < ui2_langmap_size; ui2_i++)
    {
        if(c_strncmp(at_langmap[ui2_i].s639_lang,
                     s639_lang,
                     ISO_639_LANG_LEN) == 0)
        {
            *pui2_idx = at_langmap[ui2_i].ui2_lang;
            break;
        }
    }

    if(ui2_i == ui2_langmap_size)
    {
        *pui2_idx = at_langmap[0].ui2_lang;
    }
#endif
}

/*----------------------------------------------------------------------------
 * Name: menu_set_langmap
 *
 * Description:
 *      Language map is to map the ISO Language code to the MLM_MENU_LANG_*.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_set_langmap(
    MENU_LANGMAP_ENTRY_T* pt_langmap,
    UINT16  _ui2_langmap_size)
{
    if(ui2_langmap_size >= LANGMAP_MAX_SIZE ||
       _ui2_langmap_size >= LANGMAP_MAX_SIZE)
    {
        return MENUR_INV_ARG;
    }

    c_memcpy(at_langmap,
             pt_langmap,
             _ui2_langmap_size * sizeof(MENU_LANGMAP_ENTRY_T));

    ui2_langmap_size = _ui2_langmap_size;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_tms_level
 *
 * Description:
 *      Get menu debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 menu_get_tms_level(VOID)
{
    return ui2_menu_tms_level;
}

/*----------------------------------------------------------------------------
 * Name: menu_set_tms_level
 *
 * Description:
 *      Get menu debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID menu_set_tms_level(UINT16 ui2_tms_level)
{
    ui2_menu_tms_level = ui2_tms_level;
}

/*----------------------------------------------------------------------------
 * Name: menu_is_slave_mode
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
BOOL menu_is_slave_mode(VOID)
{
    return b_slave_mode;
}

#ifdef APP_MENU_TMS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: menu_watch_reset
 *
 * Description:
 *      Reset the stopwatch.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_watch_reset(const CHAR* s_str)
{
    ui4_watch = c_os_get_sys_tick();
    DBG_INFO(("[MENU_TIME]%s: 0\n", s_str));
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_watch_split
 *
 * Description:
 *      Split the time of the stopwatch and print it to the debug console.
 *  The stopwatch is still running in the background. It is used to watch the
 *  current running time from the reset time.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_watch_split(const CHAR* s_str)
{
    DBG_INFO(("[MENU_TIME]%s: %d\n", s_str,
               (c_os_get_sys_tick() - ui4_watch) * c_os_get_sys_tick_period()));
    return MENUR_OK;
}
#endif

extern INT32 menu_custom_blank_screen(VOID);

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static BOOL  _menu_am_power_off_evt_cb_fct (AMB_NFY_REASON_T e_reason)
{
    static UINT32 ui4_default_keycode = 1;

    DBG_INFO(("%s_%d \n",__FUNCTION__,__LINE__));
    menu_blank_oled_scrn_timer_refresh();

    //spec 5.0 we should not power off when under blank screen
    if(menu_custom_is_blank_screen()
        && menu_custom_get_blank_scrn_mode() != BLK_SCRN_OLED_NO_SIGNAL
        && menu_custom_get_blank_scrn_mode() != BLK_SCRN_OLED_STILL_IMAGE
        && menu_custom_get_blank_scrn_mode() != BLK_SCRN_OLED_SMART_UI)
    {
        if (menu_custom_blank_screen_get_block_power_off() == FALSE)
        {
            menu_custom_blank_screen_set_block_power_off(TRUE);
            return TRUE;
        }
        menu_custom_unblank_screen(ui4_default_keycode);
        return FALSE;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
                    external functions implementation
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      a_menu_register
 * Description
 *      This API is used to register an application to the application manager.
 *      This API should be invoked after the middleware is
 *      initialized, and invoked from the x_appl_init().
 * Input arguments
 *      pt_cfg       the configuration data passed from x_appl_init() for
 *                   a navigator to configure itself.
 * Output arguments
 *      ppv_dsptchr  the pointer points to the pointer of the created event
 *                   dispatcher that the navigator application is attached to.
 * Returns
 *      APPR_OK            The routine was successful.
 *      APP_NO_RESOURCE    The system's memory is insufficient to process the
 *                      request.
 *      APP_EXIST        The application's name is already existed.
 *      APPR_FAIL        An unclassified error was happened
 -----------------------------------------------------------------------------*/
VOID a_menu_register(AMB_REGISTER_INFO_T*   pt_reg)
{
    DBG_API(("<MENU>menu_register\r\n"));
    c_strcpy(pt_reg->s_name, MENU_NAME);
    pt_reg->t_fct_tbl.pf_init                   = _menu_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit                   = _menu_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause                  = _menu_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume                 = _menu_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg            = _menu_app_process_msg_fct;
    pt_reg->t_desc.ui8_flags                    = ~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = 8 * 1024;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 16;
    pt_reg->t_desc.ui4_app_group_id             = 0;
    pt_reg->t_desc.ui4_app_id                   = 0;
    pt_reg->t_desc.t_max_res.z_min_memory       = 0;
#ifdef APP_MENU_VCT_RAW_SUPPORT
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024 * 128;
#else
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024 * 32;
#endif
    pt_reg->t_desc.t_max_res.ui8_max_files_size = 1024 * 8;
    pt_reg->t_desc.t_max_res.ui2_max_files      = 2;
    pt_reg->t_desc.t_max_res.ui2_max_handles    = 1024;
    pt_reg->t_desc.t_max_res.ui2_max_threads    = 2;
    pt_reg->t_desc.t_max_res.ui2_max_semaphores = 8;
    pt_reg->t_desc.t_max_res.ui2_max_msg_queues = 1;
    pt_reg->t_desc.t_max_res.ui2_max_nb_msgs    = MENU_MAX_MSG_COUNT;
    pt_reg->t_desc.t_max_res.ui2_max_msg_size   = MENU_MAX_MSG_SIZE;
    pt_reg->t_desc.ui2_msg_count                = MENU_MAX_MSG_COUNT;
    pt_reg->t_desc.ui2_max_msg_size             = MENU_MAX_MSG_SIZE;
    pt_reg->at_system_keys[0].ui4_key_code      = BTN_MENU;
#ifdef APP_MENU_BACK_ON_MENU_KEY
    pt_reg->at_system_keys[0].ui2_state_num     = 0;
#else
    pt_reg->at_system_keys[0].ui2_state_num     = 2;
#endif
    pt_reg->ui2_key_num                         = 1;

    /* specific callback provided by AMB */
    pt_reg->pf_system_key_cb                    = _menu_app_system_key_fct;

    pt_reg->pf_power_seq_cb                     = NULL; /*_menu_app_power_seq_fct;*/
    pt_reg->pf_power_off_cb = _menu_am_power_off_evt_cb_fct;

    /**/
    pf_menu_nfy =  _menu_nfy;

    /* Register the command table to CLI */
    menu_cli_attach_cmd_tbl();
}

/*----------------------------------------------------------------------------
 * Name: a_menu_register_nfy
 *
 * Description:
 *      Register the callback function to MENU. This callbakc function
 *  is used when dtv menu is a SLAVE one in the
 *  ATV/DTV integration solution.
 * Inputs:
 *      pf_menu_nfy - the registered callback function
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_menu_register_nfy(menu_nfy_fct _pf_menu_nfy)
{
    DBG_API(("<MENU>menu_register_nfy\r\n"));
    menu_lock();
    pf_menu_nfy = _pf_menu_nfy;
    menu_unlock();

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_menu_set_slave_mode
 *
 * Description:
 *      This function set the menu to a slave mode. When menu in slave mode, it
 * doesn't show the menu instantly until the a_menu_show() is called. This is
 * desigened for integration of ATV menu.
 *
 * Inputs:
 *      b_slave - if the menu is in slave mode
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_menu_set_slave_mode(BOOL    _b_slave_mode)
{
    DBG_API(("<MENU>a_menu_set_slave_mode: %d\r\n", _b_slave_mode));
    b_slave_mode = _b_slave_mode;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_menu_show
 *
 * Description:
 *      Show the menu and focus the first tab. The show operation takes
 *  effect only when the menu is in slave mode and pause state. Otherwise,
 *  it will do NO action.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_menu_show(VOID)
{
    DBG_API(("<MENU>a_menu_show\r\n"));

    return a_menu_show2(TRUE); /* show with the first tab focused*/
}


/*----------------------------------------------------------------------------
 * Name: a_menu_show2
 *
 * Description:
 *      Show the menu and focus the first or last tab. If the b_focus_first_tab
 *  is true, it will focus the first tab; Otherwise, the last one is focused.
 *  The show operation takes effect only when the menu is in slave mode and
 *  pause state. Otherwise, it will do NO action.
 *
 * Inputs:
 *      b_focus_first_tab - TRUE if the first tab focus; Otherwise, the last
 *  one is focused.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_menu_show2(BOOL b_focus_first_tab)
{
    INT32   i4_ret;

    DBG_API(("<MENU>a_menu_show2: %d\r\n", b_focus_first_tab));

    i4_ret = c_app_send_msg(h_app_menu,
                            MENU_MSG_SHOW,
                            &b_focus_first_tab,
                            sizeof(BOOL),
                            NULL,
                            NULL);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<MENU>Cannot send scan show message! resend again!\r\n"));
        return MENUR_FAIL;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_menu_set_osd_offset
 *
 * Description:
 *      Set the OSD offset. It does not repaint the menu.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 a_menu_set_osd_offset(INT32   i4_hoffset,
                                   INT32   i4_voffset
)
{
    return menu_set_osd_offset(i4_hoffset, i4_voffset);
}

/*----------------------------------------------------------------------------
 * Name: a_menu_set_osd_size
 *
 * Description:
 *      Set the OSD size. It does not repaint the menu.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 a_menu_set_osd_size(INT32   i4_width,
                                 INT32   i4_height)
{
    return menu_set_osd_size(i4_width, i4_height);
}

/*----------------------------------------------------------------------------
 * Name: a_menu_set_osd_alpha
 *
 * Description:
 *      Set the OSD alpha. It does not repaint the menu.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern INT32 a_menu_set_osd_alpha(
    UINT8    ui1_alpha
)
{
    menu_set_osd_alpha(ui1_alpha);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_menu_set_timer_delay
 *
 * Description:
 *       Set the delay time of menu timeout. The delay value could not be 0.
 *
 * Inputs:
 *      ui4_delay - the delay time
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 a_menu_set_timer_delay(
    UINT32    ui4_delay
)
{
    return menu_timer_set_delay(ui4_delay);
}

/*----------------------------------------------------------------------------
 * Name: a_menu_get_scan_type
 *
 * Description:
 *      The current scan type.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern MENU_SCAN_TYPE_T a_menu_get_scan_type (VOID)
{
    return menu_get_scan_type();
}
/*----------------------------------------------------------------------------
 * Name: a_menu_is_hot_key
 *
 * Description:
 *      check whether the user pressed key is hot key in menu
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

BOOL  a_menu_is_hot_key(UINT32 ui4_key_code, UINT32 ui4_msg)
{
    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_msg:0x%X\n",
        __FUNCTION__, __LINE__, ui4_key_code, ui4_msg )); );

    return (menu_is_hot_key(ui4_key_code, ui4_msg));
}
/*----------------------------------------------------------------------------
 * Name: a_menu_is_picture_locked
 *
 * Description:
 *      check whether the picture is locked or not,the spec request lock on must be DC OFF/ON,unlock will be work immediately,
 *      so will update this flag when receive AM_BRDCST_MSG_POWER_ON,but when check lock is disable will set the falg to false
 *      means unlcok work immediately,after then only DC off will be update the flag
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

extern BOOL  a_menu_is_picture_locked(VOID)
{
    BOOL   b_is_lock_status = FALSE;
    a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);

    if(!b_is_picture_lock)
    {
        return FALSE;
    }

    if(!b_is_lock_status)
    {
        b_is_picture_lock = FALSE;
        return FALSE;
    }
    return TRUE;
}
/*----------------------------------------------------------------------------
 * Name: a_menu_hot_key_handler
 *
 * Description:
 *       handler the hot key of menu
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

INT32 a_menu_hot_key_handler(UINT32 ui4_key_code, UINT32 ui4_msg, VOID* pv_param)
{
    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_msg:0x%X\n",
            __FUNCTION__, __LINE__, ui4_key_code, ui4_msg )); );

    return (menu_hot_key_handler(ui4_key_code, ui4_msg, pv_param));
}

/*----------------------------------------------------------------------------
 * Name: a_menu_shortcut_link
 *
 * Description:
 *      The current scan type.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 a_menu_shortcut_link(MENU_SHORT_CUT_T e_short_cut_key)
{
    INT32   i4_ret = MENUR_OK;
    e_cur_short_cut_key = e_short_cut_key;

    if (menu_get_cond() == MENU_COND_PAUSE||
        menu_get_cond() == MENU_COND_HIDE)
    {
        b_resume_from_short_cut = TRUE;

        if (MENU_SHORT_CUT_VER_INFO_PAGE == e_short_cut_key)
        {
            /* Only set the short cut flags for power sequence */
        #ifdef LINUX_TURNKEY_SOLUTION
            a_msg_convert_resume_tv_sidebar();
        #endif
            i4_ret = a_amb_resume_app(MENU_NAME);
            MENU_CHK_FAIL(i4_ret);

            return MENUR_OK;
        }

        if (MENU_SHORT_CUT_NETWORK_PAGE == e_short_cut_key)
        {
        #ifdef LINUX_TURNKEY_SOLUTION
            a_msg_convert_resume_tv_sidebar();
        #endif
            i4_ret = a_amb_resume_app(MENU_NAME);
            MENU_CHK_FAIL(i4_ret);

            return MENUR_OK;
        }

        /* this is used for nav or mmp short cut to enter menu special page for mmp
           if you do not full understand below code, please do not to modify */
#ifdef APP_MENU_MMP_COEXIST
        if (MMP_MAIN_AP_STATUS_RESUMED == a_mmp_get_ap_status())
        {
            /* when MMP coexist with MENU, and we want return to menu,
               we should first clean am stack. if not, we can not pasue MMP,
               because of last ap is MENU, so am can not to hide in MMP coexist
               with MENU state. we clean stack to make am can hide MMP */
            i4_ret = a_amb_clean_stack();
            MENU_CHK_FAIL(i4_ret);

            i4_ret = a_amb_pause_app(MMP_NAME);
            MENU_CHK_FAIL(i4_ret);
        }
#endif

#ifdef LINUX_TURNKEY_SOLUTION
        a_msg_convert_resume_tv_sidebar();
#endif
        i4_ret = a_amb_resume_app(MENU_NAME);
        MENU_CHK_FAIL(i4_ret);

        /* when MMP return to MENU we should clean am stack, which make am
           do not to resume last ap MMP but ap NAV after menu exit */
        i4_ret = a_amb_clean_stack();
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

BOOL a_menu_is_resume(VOID)
{
    return b_g_resume_menu;
}

#ifdef APP_2K12_RETAIL_DEMO_MODE
extern MENU_SHORT_CUT_T a_get_cur_short_cur_key(VOID)
{
    if(b_resume_from_short_cut == TRUE)
    {
        return e_cur_short_cut_key;
    }
    else
    {
        return MENU_SHORT_CUT_MAX;
    }
}
#endif

BOOL a_menu_is_pausing(VOID)
{
    return t_g_menu_common.b_is_pausing;
}

BOOL a_menu_is_hdr_dv_content()
{
    CHAR               s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    HANDLE_T           h_scc_comp = NULL_HANDLE;
    SCC_VID_HDR_TYPE_T e_hdr_type = SCC_VID_PQ_SDR;
    SCC_DOVI_INFO_T    t_dolby_vision;

    /* Get SCC handle by display name. */
    MENU_LOG_ON_FAIL(a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name)));
    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                  h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);
    MENU_LOG_ON_FAIL(c_scc_vid_get_hdr_type(h_scc_comp, &e_hdr_type));
    if(e_hdr_type != SCC_VID_PQ_SDR)
    {
        return TRUE;
    }

    c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));
    MENU_LOG_ON_FAIL(c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision));
    if(t_dolby_vision.ui1_is_doviHDR > 0)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL menu_is_picture_mode_item(UINT16 ui2_msgid_txt)
{
   if ( ui2_msgid_txt == MLM_MENU_KEY_VID_PIC_MODE_ITEM ||
        ui2_msgid_txt == MLM_MENU_KEY_VID_PIC_MODE_HDR10_ITEM ||
        ui2_msgid_txt == MLM_MENU_KEY_VID_PIC_MODE_HDR10_PLUS ||
        ui2_msgid_txt == MLM_MENU_KEY_VID_PIC_MODE_HLG_ITEM)
    {
       return TRUE;
    }

   return FALSE;
}

void menu_reset_for_dc_off_on(void)
{
    DBG_LOG_PRINT(("[MENU][POWER]{%s:%d} \n", __FUNCTION__,__LINE__));

    // Reset picture_mode lock status...
    BOOL   b_is_lock_status = FALSE;

    a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_lock_status);

    b_is_picture_lock  = b_is_lock_status;
}


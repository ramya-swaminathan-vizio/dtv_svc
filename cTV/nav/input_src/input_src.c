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
 * $RCSfile: input_src.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT

#include "u_common.h"
#include "u_irrc_btn_def.h"
#include "c_handle.h"
#include "c_cecm.h"
#include "c_fm.h"

#include "app_util/a_common.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_icl_common.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/a_navigator.h"
#include "nav/nav_common.h"
#include "nav/cec2/a_nav_cec.h"
/*removed #include "nav/cc_loop.h"*/
#include "nav/input_src/a_input_src.h"
#include "nav/input_src/input_src.h"
#include "nav/input_src/input_src_view.h"
#include "rest/metrics/bootsc_metrics.h"
#include "res/nav/nav_variant.h"
#include "nav/input_src/input_src_list.h"
#include "nav/tuner_setup/tuner_setup_view.h"

#ifdef APP_CEC_MENU
#include "app_util/a_cec.h"
#include "nav/cec2/a_nav_cec.h"
#include "nav/cec2/nav_cec.h"
#endif

#include "mmp/a_mmp.h"
#include "am/a_am.h"

#include "nav/banner2/a_banner.h"
#include "nav/banner2/banner.h"
#include "nav/input_src/input_src_list.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#include "nav/retail_mode/a_nav_retail_mode.h"

#include "rest/a_rest_api.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "wdk/widget/wdk_widget.h"

#include "nav/link_mode/link_mode.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "app_util/a_cfg.h"
#include "rest/a_rest_event.h"
#include "rest/a_rest.h"
#include "rest/a_rest_api.h"
#include "registry/a_registry.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <math.h>
#include "res/app_util/app_tv/a_tv_custom.h"
#include <unistd.h>

#include "fcntl.h"
#include "res/nav/nav_dbg.h"

#include "u_drv_cust.h"

#include "mi_common.h"
#include "mi_mm.h"
#include "mi_aout.h"
#include "mi_disp.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define _INPUT_SRC_TIMER_DELAY              (800) /* in ms */
#define _NAV_IPTS_GUI_LANG_NULL             ((UINT8)255)
#define _NAV_IPTS_RATING_STATIC_BUF_SIZE    ((UINT32)64)
#define FIRST_KEY_REP_DELAY                 (400)
#define NEXT_KEY_REP_DELAY                  (100)

#define FIRST_KEY_REP_DELAY                 (400)
#define NEXT_KEY_REP_DELAY                  (100)
#define ISL_VTRL_INPUT_SRC_ID_BASE                  ((UINT8)  200)
#define INPUT_SRC_MENU_TO_TV_TIMER_DELAY              (600) /* in ms */
#define HDMI_NO_SIGNAL_SMARTCAST_DELAY_BOOT            (1)  /* in sec */
#define HDMI_NO_SIGNAL_SMARTCAST_DELAY_SWITCH          (15) /* in sec */
#define NAV_HSI_CACHE_EXPIRE                            (60*1000)
#define DELAY_SWITCH_TIMEOUT                            (4 * 1000)
#define VIRTUAL_SWITCH_TIMEOUT                          (3 * 1000)
#define IN_POWER_TIMEOUT                                (30 * 1000)
#define HSI_SYSTEM_PATH "/data/hsi.dat"


typedef enum E_INPUT_SRC_SYS_TYPE_T
{
    E_INPUT_SRC_SYS_UNKNOWN = 0,
    E_INPUT_SRC_SYS_HDMI_1,
    E_INPUT_SRC_SYS_HDMI_2,
    E_INPUT_SRC_SYS_HDMI_3,
    E_INPUT_SRC_SYS_HDMI_4,
    E_INPUT_SRC_SYS_YPBPR,
    E_INPUT_SRC_SYS_CVBS,
    E_INPUT_SRC_SYS_TV,
    E_INPUT_SRC_SYS_MM,
    E_INPUT_SRC_SYS_VTRL,
    E_INPUT_SRC_SYS_1394,

} E_INPUT_SRC_SYS_TYPE;

typedef enum __NAV_IPTS_INFO_TO_UI_T
{
    _NAV_IPTS_INFO_TUI_EMPTY                 = 0,
    _NAV_IPTS_INFO_TUI_SRC_NOT_READY         = 0x00000001,
    _NAV_IPTS_INFO_TUI_SRC_WITHOUT           = 0x00000002,
    _NAV_IPTS_INFO_TUI_SRC_UPDATE            = 0x00000004,
    _NAV_IPTS_INFO_TUI_VIDEO_INFO_NOT_READY  = 0x00000008,
    _NAV_IPTS_INFO_TUI_VIDEO_INFO_QUERY      = 0x00000010,
    _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT    = 0x00000020,
    _NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY = 0x00000040,
    _NAV_IPTS_INFO_TUI_RATING_INFO_QUERY     = 0x00000080,
    _NAV_IPTS_INFO_TUI_RATING_INFO_WITHOUT   = 0x00000100,
    _NAV_IPTS_INFO_TUI_PLAY_MODE             = 0x00000200,
    _NAV_IPTS_INFO_TUI_LOCK_STATUS           = 0x00000400,
    _NAV_IPTS_INFO_TUI_INPUT_CH_NUM_START    = 0x00000800,
    _NAV_IPTS_INFO_TUI_INPUT_CH_NUM_END      = 0x00001000,
} _NAV_IPTS_INFO_TO_UI_T;

typedef enum __NAV_IPTS_VIRTUAL_SWITCH
{
    _NAV_SWITCH_SMARTCAST,
    _NAV_SWITCH_AIRPLAY
} _NAV_IPTS_VIRTUAL_SWITCH;

#define _NAV_IPTS_INFO_TUI_SRC_MASK         (_NAV_IPTS_INFO_TUI_SRC_NOT_READY |             \
                                             _NAV_IPTS_INFO_TUI_SRC_WITHOUT |               \
                                             _NAV_IPTS_INFO_TUI_SRC_UPDATE)

#define _NAV_IPTS_INFO_TUI_VIDEO_INFO_MASK  (_NAV_IPTS_INFO_TUI_VIDEO_INFO_NOT_READY |      \
                                             _NAV_IPTS_INFO_TUI_VIDEO_INFO_QUERY |          \
                                             _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT)

#define _NAV_IPTS_INFO_TUI_RATING_INFO_MASK (_NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY |     \
                                             _NAV_IPTS_INFO_TUI_RATING_INFO_QUERY |         \
                                             _NAV_IPTS_INFO_TUI_RATING_INFO_WITHOUT)

#define _NAV_IPTS_INFO_TUI_INPUT_CH_NUM_MASK (_NAV_IPTS_INFO_TUI_INPUT_CH_NUM_START |     \
                                             _NAV_IPTS_INFO_TUI_INPUT_CH_NUM_END)

typedef struct __NAV_IPTS_GROUP_DATA_T
{
    NAV_IPTS_UI_INFO_T      t_last_notify;    /*keep last notification*/
    HANDLE_T                h_svctx;
    CHAR*                   ps_grp_name;
} _NAV_IPTS_GROUP_DATA_T;

typedef struct __INPUT_SRC_T
{
    _NAV_IPTS_GROUP_DATA_T  at_grp[TV_WIN_ID_LAST_VALID_ENTRY];
    NAV_IPTS_VIEW_HANDLER_T t_view_handler;                                         /*UI handler*/
    SIZE_T                  z_rating_d_buf_size;
    VOID*                   pv_view;                                                /*Input-Src-View's instance*/
    CHAR*                   pac_rating_d_buf;
    CHAR                    ac_rating_s_buf[_NAV_IPTS_RATING_STATIC_BUF_SIZE];
    HANDLE_T                h_iom;
    UINT32                  ui4_rmv_dev_nfy;
    UINT16                  i2_g_log_type ;     /* log information */
} _INPUT_SRC_T;

typedef struct __INPUT_SRC_CHG_SRC_INFO
{
    NAV_IPTS_SWITCH_SRC_METHOD_T        e_method;
    TV_WIN_ID_T                         e_grp;
    UINT32                              ui4_param;
    _NAV_IPTS_INFO_TO_UI_T              e_to_ui;
    ISL_REC_T                           t_next_isl_rec;
}_INPUT_SRC_CHG_SRC_INFO;
typedef struct __VTRL_INPUT_SHOW_T
{
    CHAR    s_cname[24];
    UINT8   ui1_hide;

} __VTRL_INPUT_SHOW_T;
static __VTRL_INPUT_SHOW_T input_src_vtrl_source_info[5];

typedef struct __VTRL_INPUT_DATA_T
{
    CHAR    s_cname[24]; //english name
    BOOL   b_hideable;

} __VTRL_INPUT_DATA_T;

static __VTRL_INPUT_DATA_T input_src_vtrl_input_list[5];
static BOOL                b_input_list_init =  FALSE;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _INPUT_SRC_T t_g_input_src;
static BOOL   b_cec_processed = FALSE;

static BOOL   b_usb_source_show= FALSE;

static BOOL   b_smart_cast_switch_pending = FALSE;

static BOOL   b_has_signal = TRUE;

static BOOL   b_first_input_after_boot = FALSE;

static BOOL   b_powered_off = FALSE;

static BOOL   b_power_on_in_progress = FALSE;

static BOOL   b_airplay_switch_in_progress = FALSE;

static BOOL   b_is_connected = TRUE;

static UINT32   ui4_g_usb_dev_num = 0;

static _INPUT_SRC_CHG_SRC_INFO t_g_chg_src_info;

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
static BOOL                    b_exiting_cast = FALSE;
static UINT16                  ui_cfg_cast_nfy_id = APP_CFG_NOTIFY_NULL_ID;
static BOOL                    t_stop_c4tv_from_link = FALSE;
#endif
static UINT16                  ui2_1th_nfy_id = APP_CFG_NOTIFY_NULL_ID;
static BOOL                    b_is_first_ch_src = TRUE;
HANDLE_T  _h_menu2tv_timer = NULL_HANDLE;
HANDLE_T  _h_hsi_cache_timer = NULL_HANDLE;
HANDLE_T h_no_signal_scrn_svr_timer = NULL_HANDLE;
HANDLE_T h_no_signal_delay_switch_timer = NULL_HANDLE;
BOOL   change_source_way = FALSE;
HANDLE_T h_virtual_power_on_switch_timer = NULL_HANDLE;
message boot_sc_logger = {};

//-----------------------------------------------------
extern UINT16 input_source_vcec_pa ;
extern BOOL b_nav_ipts_lst_set_active_flag;
INT32 g_save_power_on_device = -1;
UINT16 ui2_g_src_dbg_level = 0;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
static VOID _nav_ipts_cast_status_chg_nfy_reg(VOID);
static VOID _nav_ipts_cast_status_chg_sync_to_icl(
                    UINT16     ui2_nfy_id,
                    VOID*      pv_tag,
                    UINT16     ui2_id
                    );
#endif
static VOID _nav_ipts_first_select_av_src_nfy_reg(VOID);

static INT32 _nav_ipts_init(NAV_CONTEXT_T*              pt_ctx);

static INT32 _nav_ipts_deinit(VOID);

static BOOL _nav_ipts_is_key_handler(NAV_CONTEXT_T*     pt_ctx,
                                     UINT32             ui4_key_code);

static INT32 _nav_ipts_activate(NAV_CONTEXT_T*          pt_ctx,
                                UINT32                  ui4_key_code);

static INT32 _nav_ipts_inactivate(NAV_CONTEXT_T*        pt_ctx);

static INT32 _nav_ipts_hide(VOID);

static INT32 _nav_ipts_handle_msg(NAV_CONTEXT_T*        pt_ctx,
                                  NAV_UI_MSG_T*         pt_ui_msg,
                                  VOID*                 pv_arg1);

static INT32 _nav_ipts_stream_nfy_handler(_INPUT_SRC_T*                     pt_this,
                                          TV_WIN_ID_T                       e_grp,
                                          NAV_STREAM_NOTIFY_DATA_T*         pt_nfy);

static INT32 _nav_ipts_app_status_nfy_handler(_INPUT_SRC_T*                 pt_this,
                                              NAV_UI_MSG_ID_T               e_id);

static INT32 _nav_ipts_change_input_src(_INPUT_SRC_T*                       pt_this,
                                        NAV_IPTS_SWITCH_SRC_METHOD_T        e_method,
                                        TV_WIN_ID_T                         e_grp,
                                        UINT32                              ui4_param,
                                        BOOL                                b_apply_same);

static INT32 _nav_ipts_apply_src_selection(_INPUT_SRC_T*                    pt_this,
                                           TV_WIN_ID_T                      e_grp,
                                           _NAV_IPTS_INFO_TO_UI_T           e_to_ui,
                                           const ISL_REC_T*                 pt_new_src);

static INT32 _nav_ipts_reload_current_src(_INPUT_SRC_T*                     pt_this);

static INT32 _nav_ipts_sync_current_src(_INPUT_SRC_T*                       pt_this,
                                        _NAV_IPTS_INFO_TO_UI_T              e_to_ui,
                                        BOOL                                b_delay_notify);

static INT32 _nav_ipts_update_info(_INPUT_SRC_T*                            pt_this,
                                   TV_WIN_ID_T                              e_grp,
                                   _NAV_IPTS_INFO_TO_UI_T                   e_to_ui,
                                   const ISL_REC_T*                         pt_new_src,
                                   BOOL                                     b_delay_notify);

static INT32 _nav_ipts_update_swap_status(_INPUT_SRC_T*                     pt_this,
                                          BOOL                              b_swapping);


static VOID _nav_ipts_delay_ui_notify(VOID*                                 pv_this,
                                      VOID*                                 pv_e_grp,
                                      VOID*                                 pv_e_notify_field);

/*helper*/
static INT32 _nav_ipts_lookup_tv_isl(_INPUT_SRC_T*                          pt_this,
                                     TV_WIN_ID_T                            e_grp,
                                     ISL_REC_T*                             pt_isl_rec);

static BOOL _nav_ipts_is_tshift_svc(VOID);

static VOID _nav_ipts_chg_src_external_nfy(
                                            VOID*                       pv_tv_win_id,
                                            VOID*                       pv_inp_src_id,
                                            VOID*                       pv_unused);

static INT32 _nav_ipts_change_input_src_by_id(_INPUT_SRC_T*                   pt_this,
                                              NAV_IPTS_SWITCH_SRC_METHOD_T    e_method,
                                              TV_WIN_ID_T                     e_grp,
                                              UINT8                           ui1_input_src_id);
static INT32 _nav_ipts_select_virtual_input(const CHAR* s_cname);
static void _nav_ipts_smart_cast_after_n_seconds(UINT32 seconds);
static VOID _nav_delay_switch_inputs(UINT32 index);

extern INT32 vid_update_current_input_src_position_info();
extern INT32 vid_update_current_input_src_pic_size_info();
extern BOOL nav_cec_util_is_hdmi_act_src (VOID);
extern BOOL Get_nav_cec_otp_set_stream_path_flag(VOID);
extern VOID Clean_nav_cec_otp_set_stream_path_flag(VOID);
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      a_input_src_do_cmd
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
extern INT32 a_input_src_do_cmd(
    NAV_IPTS_CMD_T              e_cmd,
    VOID*                       pv_arg1,
    VOID*                       pv_arg2)
{
    _INPUT_SRC_T*               pt_this = &t_g_input_src;
    _NAV_IPTS_GROUP_DATA_T*     pt_grp;
    INT32                       i;

    if(e_cmd >= NAV_IPTS_CMD_VIEW_START) /*view command*/
    {
        if(NULL == pt_this->t_view_handler.pf_data_change)
        {
            return NAVR_NOT_ALLOW;
        }

        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            pt_grp = &pt_this->at_grp[i];
            pt_grp->t_last_notify.e_cmd = e_cmd;
            pt_grp->t_last_notify.pv_cmd_arg1 = pv_arg1;
            pt_grp->t_last_notify.pv_cmd_arg2 = pv_arg2;

            pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                   (TV_WIN_ID_T)i,
                                                   NAV_ITPS_UI_IF_DO_CMD,
                                                   &pt_grp->t_last_notify);
        }
    }
    else /*model command*/
    {
        switch(e_cmd)
        {
        case NAV_IPTS_CMD_CHG_SRC_EXTERNAL:
            return nav_request_context_switch(_nav_ipts_chg_src_external_nfy, pv_arg1, pv_arg2, NULL);
        case NAV_IPTS_CMD_MDL_RELOAD_CRNT_SRC:
            return _nav_ipts_reload_current_src(pt_this);
        default:
            return NAVR_NOT_SUPPORT;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_input_src_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_input_src_register(
    const NAV_IPTS_VIEW_HANDLER_T*    pt_view_handler)
{
    NAV_COMP_T                        t_comp;
    _INPUT_SRC_T*                     pt_this = &t_g_input_src;
    INT32                             i4_ret;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    /*set view handler*/
    if(pt_view_handler)
    {
        pt_this->t_view_handler = *pt_view_handler;
    }
    else
    {
        i4_ret = nav_ipts_get_default_handler(&pt_this->t_view_handler);
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"Fail to get default Input-Src-View handler. i4_ret = %d\r\n", i4_ret));
            return i4_ret;
        }
    }

    if(FALSE == NAV_IPTS_IS_LEGAL_VIEW_HANDLER(&pt_this->t_view_handler))
    {
        DBG_ERROR((_ERROR_HEADER"Input-Src-View handler is illegal.\r\n"));
        return NAVR_FAIL;
    }

    c_memset (&t_comp, 0 ,sizeof (NAV_COMP_T)) ;

    t_comp.pf_init           = _nav_ipts_init;
    t_comp.pf_deinit         = _nav_ipts_deinit;
    t_comp.pf_is_key_handler = _nav_ipts_is_key_handler;
    t_comp.pf_activate       = _nav_ipts_activate;
    t_comp.pf_inactivate     = _nav_ipts_inactivate;
    t_comp.pf_hide           = _nav_ipts_hide;
    t_comp.pf_handle_msg     = _nav_ipts_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_INPUT_SRC, &t_comp, COMP_EXEC_SET_INPUT_SRC);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_INPUT_SRC) failed\r\n"));
        return i4_ret;
    }

    return NAVR_OK;
}

BOOL a_power_state_off()
{
    return b_powered_off;
}

BOOL a_nav_IsPowerOnInputSelect_Automatic(void)
{
    if (get_power_on_device() == E_POWER_ON_INP_AUTOMATIC)
        return TRUE;
    else
        return FALSE;
}

BOOL _nav_is_boot_sc_enabled()
{
    printf("BOOTSC _nav_is_boot_sc_enabled entered\n");
    BOOL result = FALSE;
    FILE* pFile;
    char temp[512];
    pFile = fopen ("/data/app/storage/scpl/scpl.capabilities.json","r");
    if (pFile != NULL) {
        while(fgets(temp, 512, pFile) != NULL) {
            if((strstr(temp, "BootToSC")) != NULL) {
                if((strstr(temp, "true")) != NULL) {
                    result = TRUE;
                }
            }
        }
        fclose(pFile);
    }
    return result;
}

BOOL a_nav_should_display_messaging(VOID)
{
    UINT8   ui1_fac_mask;
    a_cfg_get_factory_mode(&ui1_fac_mask);
    if((ui1_fac_mask & APP_CFG_FAC_MODE_FACTORY_MASK) != 0)
    {
        DBG_LOG_PRINT(("\n%s Line: %d, factory_mode\n", __FUNCTION__, __LINE__));
        return FALSE;
    }
    
    if (_nav_is_boot_sc_enabled() == FALSE)
    {
        return FALSE;
    }
    if (get_power_on_device() == E_POWER_ON_INP_AUTOMATIC)
    {
        return TRUE;
    }
    if (b_first_input_after_boot)
    {
        return FALSE;
    }

    _INPUT_SRC_T* pt_this          = &t_g_input_src;
    _NAV_IPTS_GROUP_DATA_T* pt_grp = &pt_this->at_grp[TV_WIN_ID_MAIN];
    UINT8 current_input_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;

    Enu_POWER_ON_INPUT power_on_input_option = get_power_on_device();
    if ( (current_input_id == 2 && power_on_input_option == E_POWER_ON_INP_HDMI1)
        || (current_input_id == 3 && power_on_input_option == E_POWER_ON_INP_HDMI2)
        || (current_input_id == 4 && power_on_input_option == E_POWER_ON_INP_HDMI3)
        || (current_input_id == 5 && power_on_input_option == E_POWER_ON_INP_HDMI4)
        || (current_input_id == 0 && power_on_input_option == E_POWER_ON_INP_ANTENNA)
        || (current_input_id == 1 && power_on_input_option == E_POWER_ON_INP_COMPOSITE) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL a_nav_should_display_no_signal_indication(VOID)
{
    a_nw_is_network_connected(&b_is_connected);

    if (_nav_is_boot_sc_enabled() == FALSE || b_is_connected == FALSE)
    {
        return TRUE;
    }

    if (get_power_on_device() == E_POWER_ON_INP_AUTOMATIC)
    {
        if (b_first_input_after_boot)
        {
            return FALSE;
        }
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_switch_src
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_switch_src(
    NAV_IPTS_SWITCH_SRC_METHOD_T    e_method,
    TV_WIN_ID_T                     e_grp,
    UINT32                          ui4_param)
{
    _INPUT_SRC_T*                   pt_this = &t_g_input_src;
    INT32                           i4_ret = NAVR_OK;

    i4_ret = _nav_ipts_change_input_src(pt_this, e_method, e_grp, ui4_param, FALSE);
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

VOID* nav_ipts_get_view_context (VOID)
{
    return t_g_input_src.pv_view;
}


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
 static VOID _iom_nfy_fct (VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data)
{
    extern NAV_MODEL_T     t_g_navigator;
    //NAV_EVN_T   t_event = {0};
#if 1
    if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        switch (IOM_GET_EVT_GRP_ID(ui4_evt_code))
        {
            case BTN_INPUT_SRC:
            {
                NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui4_evt_code:0x%X \n", __FUNCTION__, __LINE__, ui4_evt_code )); );

                printf("BOOTSC setting b_first_input_after_boot FALSE(1)\n");
                b_first_input_after_boot = FALSE;
                a_nav_ipts_cancel_smart_cast_after_n_seconds();
                if (a_cfg_custom_get_wifi_remote_support())
                {
                    DBG_INFO(("\n --------- %s, %d wifi remote ------\n", __FUNCTION__, __LINE__));
                    a_tv_net_send_cmd("\n:am,am,:ir_mode=tv\n");
                    a_tv_net_send_cmd("\n:am,am,:codeset=NULL\n");
                }
                b_key_front_pannel = (IOM_GET_EVT_SRC(ui4_evt_code) == KEY_SRC_FRONT_PANEL) ? TRUE : FALSE;
                break;
            }
            case BTN_MENU:
            {
                DBG_INFO(("<INPUT_SRC> _iom_nfy_fct() %d,%d\n",
                    _IS_NAV_COMP_VISIBLE(&t_g_navigator, NAV_COMP_ID_INPUT_SRC),
                    a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP)));

                if (_IS_NAV_COMP_VISIBLE(&t_g_navigator, NAV_COMP_ID_INPUT_SRC)
                    && a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
                {
                    nav_ipts_auto_close();
                }

                break;
            }

            default:
                break;
        }
    }
#endif
    return;
}

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_update_current_src
 * Description
 *      This function is only for DTV00876550 now, because when enter Netflix,
 *  id of current source is still the old one. So this function update it.
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
 VOID nav_ipts_update_current_src(VOID)
 {
    INT32                       i4_ret = NAVR_OK;
    TV_WIN_ID_T                 e_focus_id = {0};
    ISL_REC_T                   t_isl_rec = {0};
    _INPUT_SRC_T*               pt_this = &t_g_input_src;

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_ipts_update_info(pt_this, e_focus_id, _NAV_IPTS_INFO_TUI_SRC_UPDATE, &t_isl_rec, FALSE);
    NAV_LOG_ON_FAIL(i4_ret);
 }

static VOID _nav_ipts_c4tv_apron_nfy_fct
                                (
                                    C4TV_APRON_CAST_STATE    e_cast_state,
                                    VOID*                    pv_param1, /*BOOL,connect or not; True,connect;FALSE,not connect*/
                                    VOID*                    pv_param2, /*UINT8,for ForcedUpdate,it is C4TV_APRON_UPDATE_STATE_T*//* other cast status,it is _C4TV_APRON_CAST_STATUS*/
                                    VOID*                    pv_param3 /*UINT8,for ForcedUpdate,it is ui1_update_progress*/
                                )
{
    INT32                       i4_ret = NAVR_OK;
    TV_WIN_ID_T                 e_focus_id;
    ISL_REC_T                   t_isl_rec;

    if(e_cast_state == C4TV_APRON_CAST_STATE_NotSetUp || e_cast_state == C4TV_APRON_CAST_STATE_Unknown)
    {
        DBG_WARN(("<NAV INPUT> e_cast_state : %d, no need change.\r\n",e_cast_state));
        return;
    }

    if (a_c4tv_apron_check_cast_state() == FALSE)
    {
        DBG_WARN(("<NAV INPUT> e_cast_state : %d, no need change.\r\n",e_cast_state));
        return;
    }

    {
        extern BOOL a_wzd_is_oobe_mode(VOID);

        if (b_exiting_cast || a_wzd_is_oobe_mode())
        {
            DBG_WARN(("<NAV INPUT> Is exiting cast, no need change.\r\n"));
            return;
        }

    }

    {
        i4_ret = a_tv_get_focus_win(&e_focus_id);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
        NAV_LOG_ON_FAIL(i4_ret);


        if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type
            || DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
        {
            DBG_WARN(("<NAV INPUT> current src type is %d,t_isl_rec.t_avc_info.e_video_type : %d , no need change.\r\n",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type));
            return;
        }
    }
#ifdef APP_RETAIL_MODE_SUPPORT
    {
            ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
            i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
            NAV_LOG_ON_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

            if( ACFG_RETAIL_MODE_NORMAL == retm_status
                || ACFG_RETAIL_MODE_NO_PLAYING == retm_status)
            {
                DBG_WARN(("<NAV INPUT> Is retail mode, no need change.\r\n"));
                return;
            }
    }
#endif
    /* Change to CastTV source when PAD do cast in non-Cast Soure*/
    DBG_INFO(("<NAV INPUT> e_cast_state=%d\r\n",e_cast_state));

    i4_ret = _nav_ipts_select_virtual_input("SMARTCAST");
    NAV_LOG_ON_FAIL(i4_ret);

    return;
}

static VOID _nav_ipts_cast_status_chg_sync_to_icl(
                    UINT16     ui2_nfy_id,
                    VOID*      pv_tag,
                    UINT16     ui2_id
                    )
{
    UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);

    if (ui_cfg_cast_nfy_id != ui2_nfy_id)
    {
        return;
    }
#ifdef SYS_C4TV_SUPPORT

    if (APP_CFG_RECID_CAST_TV_STATUS == ui2_rec_id)
    {
        INT32  i4_ret = 0;
        TV_WIN_ID_T  e_focus_id = {0};
        ISL_REC_T  t_isl_rec = {0};
        UINT8  ui1_cast_tv_status = APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE;

        i4_ret = a_tv_get_focus_win(&e_focus_id);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
        NAV_LOG_ON_FAIL(i4_ret);

        a_cfg_get_cast_tv_status(&ui1_cast_tv_status);

        if (APP_CFG_CAST_TV_STATUS_CAST_MODE == ui1_cast_tv_status)
        {
            if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
            {
                i4_ret = a_icl_custom_set_cast_src_status(ICL_RECID_CAST_SRC_STATUS_TRUE_REAL);
                DBG_INFO(("[XXXX] LINE:%d @ %d=%s() val:TRUE_REAL\n", __LINE__, i4_ret, __FUNCTION__));
            }
            else
            {
                i4_ret = a_icl_custom_set_cast_src_status(ICL_RECID_CAST_SRC_STATUS_TRUE);
                DBG_INFO(("[XXXX] LINE:%d @ %d=%s() val:TRUE\n", __LINE__, i4_ret, __FUNCTION__));
            }

            _nav_ipts_update_info(&t_g_input_src, e_focus_id, _NAV_IPTS_INFO_TUI_SRC_UPDATE, &t_isl_rec, FALSE);
        }
        else
        {
            if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
            {
                i4_ret = a_icl_custom_set_cast_src_status(ICL_RECID_CAST_SRC_STATUS_TRUE_VTRL);
                DBG_INFO(("[XXXX] LINE:%d @ %d=%s() val:TRUE_VRTL\n", __LINE__, i4_ret, __FUNCTION__));
            }
            else
            {
                i4_ret = a_icl_custom_set_cast_src_status(ICL_RECID_CAST_SRC_STATUS_FALSE);
                DBG_INFO(("[XXXX] LINE:%d @ %d=%s() val:FALSE\n", __LINE__, i4_ret, __FUNCTION__));
            }
        }
    }
#endif
}

static  VOID _nav_ipts_cast_status_chg_nfy_reg(VOID)
{
    INT32  i4_ret = 0;
    UINT8  ui1_cast_tv_status = APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE;

    a_cfg_get_cast_tv_status(&ui1_cast_tv_status);
    if (APP_CFG_CAST_TV_STATUS_CAST_MODE == ui1_cast_tv_status)
    {
        i4_ret = a_icl_custom_set_cast_src_status(ICL_RECID_CAST_SRC_STATUS_TRUE);
        DBG_INFO(("[XXXX] LINE:%d @ %d=%s() val:TRUE\n", __LINE__, i4_ret, __FUNCTION__));
    }
    else if (APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE == ui1_cast_tv_status)
    {
        i4_ret = a_icl_custom_set_cast_src_status(ICL_RECID_CAST_SRC_STATUS_FALSE);
        DBG_INFO(("[XXXX] LINE:%d @ %d=%s() val:FALSE\n", __LINE__, i4_ret, __FUNCTION__));
    }

    if (APP_CFGR_OK != a_cfg_notify_reg(
                            APP_CFG_GRPID_MISC,
                            NULL,
                            _nav_ipts_cast_status_chg_sync_to_icl,
                            &ui_cfg_cast_nfy_id))
    {
        DBG_ERROR(("[XXXX] register cfg cast nfy fail!\r\n"));
    }
}
#endif

#ifndef LINUX_AUTO_TEST /* disable usb input list in LINUX_AUTO_TEST=true build */
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_ipts_usb_check_for_response
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *
 *---------------------------------------------------------------------------*/
static BOOL _nav_ipts_usb_check_for_response (VOID)
{
    BOOL            b_is_need_response = TRUE;
    INT32           i4_ret = NAVR_OK;
    NAV_COMP_ID_T   e_comp_id;
    UINT32          ui4_mnt_count = 0;
    CHAR            ac_path[128] = {0};
    CHAR            ac_app_name[APP_NAME_MAX_LEN] = {0};
    UINT32          ui4_idx = 0;
    UINT32          ui4_usb_idx = 0;
    SIZE_T          z_size = 128;
    RMV_DEV_DEVICE_STATUS_T  e_dev_status;

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if(i4_ret != 0)
    {
        DBG_ERROR(("<NAV INPUT> file: %s line: %d  %s Fail to get removeable device count, ret = %d\n", __FILE__, __LINE__, __FUNCTION__, i4_ret));
    }

    if (0 == ui4_mnt_count)
    {
        b_is_need_response = FALSE;
    }
    else
    {
        for (ui4_idx = 0; ui4_idx < ui4_mnt_count; ui4_idx++)
        {
            /*query mount point status*/
            i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                        ui4_idx,
                                        &e_dev_status);
            if(NAVR_OK != i4_ret)
            {
                continue;
            }

            if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
                (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
            {
                continue;
            }

            i4_ret = a_rmv_dev_get_mnt_point(ui4_idx,
                                             &z_size,
                                             ac_path);
            if (NAVR_OK != i4_ret)
            {
                continue;
            }

    #ifdef APP_RETAIL_MODE_SUPPORT
            ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
            #ifdef APP_CAST_TV_MMP
                /*check if vizio_demo.txt can't response*/
                if(_nav_custom_ipts_usb_check_demo_file(ac_path))
                {
                    b_is_need_response = FALSE;
                    b_g_is_retail_mode = FALSE;
                }
                else
                {
                    b_g_is_retail_mode = TRUE;
                }
            #endif
            }
    #endif

            /* any way, count the usb device number */
            ui4_usb_idx++;
        }/*end for loop*/

        if (ui4_g_usb_dev_num >= ui4_usb_idx)
        {
            b_is_need_response = FALSE;
        }
#if 0

    #ifdef APP_CAST_TV_MMP
        /* is running OOBE end */
        /*
        a_cfg_get_wzd_status(&ui2_status);
        ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

        if(WZD_STATE_RESUME_C4TV_END != ui1_state)
        {
            b_is_need_response = FALSE;
        }
        */
    #endif

        if (!nav_is_active())
        {
            i4_ret = a_am_get_active_app (ac_app_name);
            if(i4_ret != 0)
            {
                DBG_ERROR(("<NAV INPUT> file: %s line: %d  %s Fail to get active app, ret = %d\n", __FILE__, __LINE__, __FUNCTION__, i4_ret));
            }
        #ifdef APP_RETAIL_MODE_SUPPORT
            ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                b_is_need_response = FALSE;
            }
            /* is running MMP? */
            else if (0 == c_strcmp(ac_app_name, MMP_NAME))
        #else
            /* is running MMP? */
            if (0 == c_strcmp(ac_app_name, MMP_NAME))
        #endif
            {
                b_is_need_response = FALSE;
            }
            /* is MENU & MMP coexist status */
        #ifdef APP_MENU_MMP_COEXIST
            else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                b_is_need_response = FALSE;
            }
        #endif
                    /* is running WIZARD? */
                    /*
            else if (0 == c_strcmp(ac_app_name, WZD_NAME))
            {
                b_is_need_response = FALSE;
            }
            */
        }

        else
        {
            e_comp_id = nav_get_active_component();

#ifdef APP_WR_UPDATER_UI_SUPPORT
            if ((NAV_COMP_ID_UPDATER == e_comp_id)
                || (NAV_COMP_ID_WR_UPDATER == e_comp_id))
#else
            if (NAV_COMP_ID_UPDATER == e_comp_id)
#endif
            {
                b_is_need_response = FALSE;
            }
        }

        /*
        if (_nav_usb_pld_is_skype_FULLSCREEN())
        {
            b_is_need_response = FALSE;
        }
        */

        //scan is running
        if(nav_is_channel_scan_active())
        {
            b_is_need_response = FALSE;
        }
#endif
    }
    ui4_g_usb_dev_num = ui4_usb_idx;

    return b_is_need_response;
}
#endif

INT32 nav_ipts_is_allow_show_usb_src()
{
    return b_usb_source_show;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_ipts_usb_rmv_dev_nfy_handler
 * Description:
 *      Copied from nav_usb_pld.c and changed the name
 * Input arguments:
 *      pv_tag1
 *      pv_tag2
 *      pv_tag3
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_usb_rmv_dev_nfy_handler(
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3)
{
    RMV_DEV_NFY_ID_T e_nfy_id = (RMV_DEV_NFY_ID_T)((UINT32)pv_tag1);

    if (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
    {
#ifndef LINUX_AUTO_TEST /* disable usb input list in LINUX_AUTO_TEST=true build */
        /*allow to show USB in input list*/
        if (TRUE == _nav_ipts_usb_check_for_response())
        {
            DBG_INFO(("<NAV INPUT> file: %s line: %d  %s usb inserted\n", __FILE__, __LINE__, __FUNCTION__));
            b_usb_source_show = TRUE;
            rest_event_notify("system/input/list", 1, "");
            rest_event_notify("system/input/enable", 0, "usb");
        }
#endif
    }
    else if (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id)
    {
        /*not allow to show USB in input list*/
        b_usb_source_show = FALSE;

        ui4_g_usb_dev_num = 0;
        rest_event_notify("system/input/list", 1, "");
        rest_event_notify("system/input/enable", 0, "usb");
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_ipts_usb_rmv_dev_nfy
 * Description:
 *
 * Input arguments:
 *      pv_tag
 *      e_nfy_id
 *      pv_nfy_param
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_usb_rmv_dev_nfy(
                    VOID*               pv_tag,
                    RMV_DEV_NFY_ID_T    e_nfy_id,
                    VOID*               pv_nfy_param)
{
    if ((RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)||
        (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id))
    {
        nav_request_context_switch(
                        _nav_ipts_usb_rmv_dev_nfy_handler,
                        (VOID*)e_nfy_id,
                        NULL,
                        NULL);
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_usb_to_cast_power_on
 * Description  This function now is using when TV power on, if last source
 *              before AC power off is USB source,then change the source to
 *              cast.
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_usb_to_cast_power_on(VOID)
{
    ISL_REC_T    t_isl_rec = {0};
    INT32        i4_ret = NAVR_OK;
    TV_WIN_ID_T  e_focus_id = {0};
    PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;


    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    NAV_CHK_FAIL(i4_ret);
    c_pcl_get_wakeup_reason(&e_wakeup_reason, NULL);

    if(PCL_WAKE_UP_REASON_AIRPLAY == e_wakeup_reason)
    {
        i4_ret = _nav_ipts_select_virtual_input("airplay");
        NAV_CHK_FAIL(i4_ret);
        return NAVR_OK;
    }

    if (a_nav_ipts_is_usb_source(&t_isl_rec) == FALSE
        && a_nav_ipts_is_cast_source(&t_isl_rec) == FALSE)
    {
        /* OK ??? */
        return NAVR_OK;
    }

    /*change to cast source*/
    DBG_INFO(("<NAV INPUT> change to cast when power on\n\r"));
    if (t_isl_rec.ui1_internal_id > 0)
    {
        i4_ret = _nav_ipts_select_virtual_input(t_isl_rec.s_src_name);
    }
    else
    {
        i4_ret = _nav_ipts_select_virtual_input("SMARTCAST");
    }
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

static INT32 _nav_ipts_set_vtrl_inp_hidden()
{
    INT32   i4_ret;
    UINT8   ui1_hide_value = 0;
    UINT16  ui2_i;
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
    SIZE_T  z_size;

    i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);
    NAV_LOG_ON_FAIL(i4_ret == APP_CFGR_OK? NAVR_OK : i4_ret );

    for(ui2_i = 0;ui2_i < 5; ui2_i++)//Find del id
    {
        i4_ret = a_cfg_get_vtrl_name(ui2_i, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        DBG_INFO(("<VTRL INPUT> file: %s line: %d  %s c_strlen(s_inp_name) (%d)s_input_name %s\n", __FILE__, __LINE__, __FUNCTION__,c_strlen(s_inp_name), s_inp_name));
        if(c_strlen(s_inp_name) == 0)
        {
            ui1_hide_value |= ((UINT8)1 << ui2_i);
            DBG_INFO(("<VTRL INPUT> file: %s line: %d  %s ui1_hide_value %d\n", __FILE__, __LINE__, __FUNCTION__,ui1_hide_value));

        }
    }

    DBG_INFO(("<VTRL INPUT> file: %s line: %d  %s set_hide vtrl(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_hide_value));

    i4_ret = acfg_set(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, 1);
    NAV_LOG_ON_FAIL(i4_ret == APP_CFGR_OK? NAVR_OK : i4_ret );

    return i4_ret;

}

extern INT32 a_isl_store_vtrl_input_cname();

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_init(
    NAV_CONTEXT_T*          pt_ctx)
{
    ISL_REC_T               t_isl_rec = {0};
    _INPUT_SRC_T*           pt_this = &t_g_input_src;
    INT32                   i4_ret  = NAVR_OK, i;
    IRRC_SETTING_T          t_irrc_setting;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    /*check init twice*/
    NAV_ASSERT(NULL == pt_this->pac_rating_d_buf);

    do
    {
        b_usb_source_show = FALSE;

        i4_ret = c_timer_create(&_h_menu2tv_timer);

        i4_ret = c_timer_create(&h_no_signal_scrn_svr_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("{%s,%d} c_timer_create() failed, ret=%d\n", __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }


        i4_ret = c_timer_create(&h_no_signal_delay_switch_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("{%s,%d} c_timer_create() failed, ret=%d\n", __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        i4_ret = c_timer_create(&h_virtual_power_on_switch_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("{%s,%d} c_timer_create() failed, ret=%d\n", __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        /*init data member*/
        pt_this->at_grp[TV_WIN_ID_MAIN].ps_grp_name = SN_PRES_MAIN_DISPLAY;
        pt_this->at_grp[TV_WIN_ID_SUB].ps_grp_name = SN_PRES_SUB_DISPLAY;

        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            i4_ret = nav_get_svctx_handle((TV_WIN_ID_T)i, &pt_this->at_grp[i].h_svctx);
            NAV_BREAK_ON_FAIL(i4_ret);

            pt_this->at_grp[i].t_last_notify.ui1_gui_lang_id = _NAV_IPTS_GUI_LANG_NULL;
            pt_this->at_grp[i].t_last_notify.e_app_status = NAV_IPTS_UI_AS_OFF;
            pt_this->at_grp[i].t_last_notify.e_lock_status = LOCKED_STATUS_NONE;
        }
        NAV_BREAK_ON_FAIL(i4_ret);

        /*create Input-Src-View*/
        i4_ret = pt_this->t_view_handler.pf_init(pt_ctx->t_gui_res.h_canvas,
                                                 pt_ctx->t_gui_res.i4_x_offset,
                                                 pt_ctx->t_gui_res.i4_y_offset,
                                                 pt_ctx->t_gui_res.e_color_type,
                                                 &pt_this->pv_view);
        NAV_BREAK_ON_FAIL(i4_ret);

        for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
        {
            /**/
            i4_ret = a_isl_get_num_rec(&pt_this->at_grp[i].t_last_notify.ui1_src_count);
            NAV_BREAK_ON_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret);

            /*notify view*/
            pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                   (TV_WIN_ID_T)i,
                                                   NAV_IPTS_UI_IF_SRC_COUNT,
                                                   &pt_this->at_grp[i].t_last_notify);

            i4_ret = _nav_ipts_lookup_tv_isl(pt_this, (TV_WIN_ID_T)i, &t_isl_rec);
            NAV_BREAK_ON_FAIL(i4_ret);

            /*init src data*/
            _nav_ipts_update_info(pt_this,
                                  (TV_WIN_ID_T)i,
                                  (_NAV_IPTS_INFO_TO_UI_T)(_NAV_IPTS_INFO_TUI_SRC_UPDATE |
                                                          _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT |
                                                          _NAV_IPTS_INFO_TUI_RATING_INFO_WITHOUT),
                                  &t_isl_rec,
                                  FALSE);
        }

        /* register remove device notification function */
        i4_ret = a_rmv_dev_reg_monitor(
                _nav_ipts_usb_rmv_dev_nfy,
                NULL,
                &pt_this->ui4_rmv_dev_nfy);
        NAV_LOG_ON_FAIL(i4_ret);

        /* Open IOM handler. */
        c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));

        t_irrc_setting.ui8_evt_grp_mask         = (KEY_GROUP_TO_MASK(KEY_GROUP_PRG_CTRL) \
                                                    | KEY_GROUP_TO_MASK(KEY_GROUP_FCT_CTRL));
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = (UINT16)(FIRST_KEY_REP_DELAY / 10); /* 10 ms per unit */
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = (UINT16)(NEXT_KEY_REP_DELAY / 10);  /* 10 ms per unit */

        NAV_LOG_ON_FAIL(c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                                IOM_DEV_ID_ANY,
                                NULL,
                                (VOID*) & t_irrc_setting,
                                NULL,
                                _iom_nfy_fct,
                                & t_g_input_src.h_iom));

        if (i < TV_WIN_ID_LAST_VALID_ENTRY)
        {
            break;
        }

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
        if (a_c4tv_apron_register_nfy_cb(_nav_ipts_c4tv_apron_nfy_fct) != C4TV_APRON_OK)
        {
            DBG_WARN(("<INPUT SRC> register c4tv apron nfy fail!\r\n"));
        }
        _nav_ipts_cast_status_chg_nfy_reg();
#endif
        _nav_ipts_first_select_av_src_nfy_reg();

#ifdef CLI_SUPPORT
         ipts_cli_init();
#endif
        //a_nav_ipts_clean_virtual_input();

        _nav_ipts_set_vtrl_inp_hidden();

        i4_ret = a_isl_store_vtrl_input_cname();
        NAV_LOG_ON_FAIL(i4_ret);

        b_input_list_init = TRUE;

        return NAVR_OK;

    } while(0);

    _nav_ipts_deinit();
    return i4_ret;
}

static INT32 _nav_ipts_w2s_str_replace(
                UTF16_T*  w2s_dst,
                SIZE_T    t_dst_len,
                UTF16_T*  w2s_src[],
                UINT32    ui4_src_sz
                )
{
    if (w2s_dst == NULL ||
        t_dst_len == 0 ||
        w2s_src == NULL ||
        ui4_src_sz == 0
        )
    {
        DBG_ERROR(("{%s,%d} parameters err. \r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    UTF16_T* buffer = c_mem_alloc(sizeof(UTF16_T)*t_dst_len);
    if (buffer == NULL) {
        DBG_ERROR(("{%s,%d} c_mem_alloc() failed. \r\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }
    c_memset(buffer, 0, sizeof(UTF16_T)*t_dst_len);

    UTF16_T*    p_w2s_dst = w2s_dst;
    UTF16_T     w2s_pattern[] = L"%s";
    SIZE_T      t_pattern_len = c_uc_w2s_strlen(w2s_pattern);
    SIZE_T      t_rest_len = t_dst_len-1;

    for (UINT32 ui4_src_idx = 0; ui4_src_idx < ui4_src_sz; ++ui4_src_idx)
    {
        UTF16_T*    p_w2s_pattern = &w2s_pattern[0];
        INT32       i4_idx = 0;

        while (*(p_w2s_dst+i4_idx) != *p_w2s_pattern)
        {
            if (*(p_w2s_dst+i4_idx) == 0)
                break;
            i4_idx++;
        }
        while (*(p_w2s_dst+i4_idx) == *p_w2s_pattern)
        {
            if (*(p_w2s_dst+i4_idx) ==0)
                break;
            p_w2s_pattern++;
            i4_idx++;
        }

        if (*p_w2s_pattern == 0)  // find  pattern string from  dst string
        {
            if ((i4_idx - t_pattern_len) > 0)
            {
                if ((i4_idx - t_pattern_len) > t_rest_len) {
                    c_mem_free(buffer);
                    return NAVR_FAIL;
                }
                c_uc_w2s_strncat(buffer, p_w2s_dst, i4_idx - t_pattern_len);
                t_rest_len -= (i4_idx - t_pattern_len);
            }

            p_w2s_dst += i4_idx;

            SIZE_T  t_src_len = c_uc_w2s_strlen(w2s_src[ui4_src_idx]);
            if (t_src_len > t_rest_len) {
                c_mem_free(buffer);
                return NAVR_FAIL;
            }
            c_uc_w2s_strncat(buffer, w2s_src[ui4_src_idx], t_src_len);
            t_rest_len -= t_src_len;
        }
    }

    if (p_w2s_dst != w2s_dst)
    {
        SIZE_T  t_dst_r_len = c_uc_w2s_strlen(p_w2s_dst);
        if (t_dst_r_len > t_rest_len) {
            c_mem_free(buffer);
            return NAVR_FAIL;
        }
        c_uc_w2s_strncat(buffer, p_w2s_dst, t_dst_r_len);
        c_uc_w2s_strcpy(w2s_dst, buffer);
        c_mem_free(buffer);
        return NAVR_OK;
    }
    else
    {
        c_mem_free(buffer);
        return NAVR_FAIL;
    }

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_delay_switch
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

static VOID _nav_delay_switch(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )

{
    UINT32 index = (UINT32)pv_tag1;
    DBG_INFO(("%s() Line %d: index = %d\n\n", __FUNCTION__, __LINE__, index));
    _INPUT_SRC_T*               pt_this = &t_g_input_src;
    _nav_ipts_change_input_src(pt_this,3,0,index,true);

    switch (index) {
        case 0:
            rest_event_notify_current_input("tuner");
        break;
        case 1:
            rest_event_notify_current_input("comp");
        break;
        case 2:
            rest_event_notify_current_input("hdmi1");
        break;

        case 3:
            rest_event_notify_current_input("hdmi2");
        break;

        case 4:
            rest_event_notify_current_input("hdmi3");
        break;

        case 5:
            rest_event_notify_current_input("hdmi4");
        break;

        default:
        break;
    }

}

static VOID _nav_ipts_delay_switch_cb_fct (
                    HANDLE_T  pt_tm_handle,
                    VOID*     pv_tag)
{
    DBG_INFO(("%s() Line %d\n\n", __FUNCTION__, __LINE__));
    nav_request_context_switch(_nav_delay_switch, pv_tag, NULL, NULL);

}

static VOID _nav_switch_to_airplay()
{
    printf("BOOTSC _nav_switch_to_airplay\n");
    rest_event_notify_current_input("CAST:airplay");
}

static VOID _nav_ipts_switch_to_virtual_cb_fct (
                    HANDLE_T  pt_tm_handle,
                    VOID*     pv_tag)
{
    INT32 i4_retry_count = 0;

    _NAV_IPTS_VIRTUAL_SWITCH input = (_NAV_IPTS_VIRTUAL_SWITCH)pv_tag;

    printf("BOOTSC _nav_ipts_switch_to_virtual_cb_fct - input = %d\n",input);
    //Do nothing until we have a session token
    while(1) {
        struct stat buffer;
        if (stat("/tmp/cred.dat", &buffer) != 0) {
            if (i4_retry_count > 50) {
                printf("BOOTSC <rest> err: meet retry count max\n\r");
                break;
            }
            printf("BOOTSC <rest> open /tmp/cred.dat failed, retry %d\n\r", i4_retry_count);
            sleep(1);
            i4_retry_count++;
        } else {
            break;
        }
    }
    printf("BOOTSC token obtained\n");
    a_scrn_svr_hide_NO_SIGNAL_2();

    //Then request change
    switch (input) {
        case _NAV_SWITCH_SMARTCAST:
            printf("BOOTSC switching to smartcast\n");
            rest_event_notify_current_input("CAST:SMARTCAST");
        break;

        case _NAV_SWITCH_AIRPLAY:
            printf("BOOTSC switching to airplay\n");
            bool b_is = false;
            //If airplay is not enabled, we switch to SmartCast
            rest_get_airplay_enabled(&b_is);
            if (!b_is) {
                printf("BOOTSC Airplay not enabled - switching to SmartCast\r\n");
                rest_event_notify_current_input("CAST:SMARTCAST");
            }
            else {
                b_airplay_switch_in_progress = TRUE;
                //Otherwise we switch to Airplay
                printf("BOOTSC Switching to Airplay\r\n");
                nav_request_context_switch(_nav_switch_to_airplay, NULL, NULL, NULL);
                printf("BOOTSC updated 1\n");
                printf("BOOTSC rest_event_notify_current_input airplay 3\n");
            }
        break;

        default:
            printf("BOOTSC no input- should not have reached here\n");
        break;
    }
}

static VOID _nav_power_on_switch_to_virtual_input(_NAV_IPTS_VIRTUAL_SWITCH input, UINT32 ui4_delay)
{
    printf("BOOTSC _nav_power_on_switch_to_virtual_input %d\n",input);
    c_timer_start(
                h_virtual_power_on_switch_timer,
                ui4_delay,
                X_TIMER_FLAG_ONCE,
                _nav_ipts_switch_to_virtual_cb_fct,
                (VOID*)input);
}


static VOID _nav_delay_switch_inputs(UINT32 index)
{
    DBG_INFO(("%s() Line %d: index = %d\n\n", __FUNCTION__, __LINE__, index));
    c_timer_start(
                h_no_signal_delay_switch_timer,
                DELAY_SWITCH_TIMEOUT,
                X_TIMER_FLAG_ONCE,
                _nav_ipts_delay_switch_cb_fct,
                (VOID*)index);
}

static VOID _nav_ipts_first_select_av_src_cb_fct (
                    HANDLE_T  pt_tm_handle,
                    VOID*     pv_tag)
{
    a_banner_set_excl_comp_on(FALSE);
    c_timer_stop(pt_tm_handle);
    c_timer_delete(pt_tm_handle);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_no_signal_scrn_svr_timer_cb_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_no_signal_scrn_svr_timer_cb_fct (
                    HANDLE_T  pt_tm_handle,
                    VOID*     pv_tag)
{
    b_smart_cast_switch_pending= FALSE;

    //If signal has been obtained in the meantime, or if the power is off, don't change to smartcast
    if (b_has_signal == FALSE && b_powered_off == FALSE) {
        _INPUT_SRC_T*                 pt_this = &t_g_input_src;
        _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[0];
        UINT8 ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;
        char str[10];
        sprintf(str, "%d", ui1_old_id);
        boot_sc_logger = setInputFrom(boot_sc_logger, (char*)inputSwitchFromText(ui1_old_id));
        boot_sc_logger = setInputTo(boot_sc_logger, "SMARTCAST");
        boot_sc_logger = setPowerOnInputSetting(boot_sc_logger, (char*)powerOnIndexToText(get_power_on_device()));
        showLog(boot_sc_logger);
        sendLog(boot_sc_logger);
        rest_event_notify_current_input("CAST:SMARTCAST");
    }
}

static VOID _nav_ipts_first_select_av_src_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32           i4_ret = NAVR_OK;
    WDK_TOAST_T*    pt_toast = NULL;
    UTF16_T         w2s_string[256]  = {0};
    UTF16_T         cec_name[128] = {0};
    UTF16_T*        ipts_name = NULL;
    ISL_REC_T       t_isl_rec = {0};
    SIZE_T          strlen = 0;

    pt_toast = c_mem_alloc(sizeof(WDK_TOAST_T));
    c_memset(pt_toast, 0, sizeof(WDK_TOAST_T));
    pt_toast->e_toast_style  = WDK_WARNING_TOAST;
    pt_toast->e_string_style = WDK_STRING_STRING;

    switch ((UINT32)pv_tag1)
    {
        case 0:
            ipts_name = L"HDMI-1";
            break;
        case 1:
            ipts_name = L"HDMI-2";
            break;
        case 2:
            ipts_name = L"HDMI-3";
            break;
        case 3:
            ipts_name = L"COMP";
            break;
        default:
            ipts_name = L"COMP";
            break;
    }

    nav_get_isl_rec(TV_WIN_ID_MAIN, &t_isl_rec);
    a_isl_get_display_name_ex(&t_isl_rec, cec_name, APP_CFG_CUSTOM_INP_NAME_LEN);

    UTF16_T*  w2s_arr[3] = {ipts_name, &cec_name[0], ipts_name};
    c_uc_w2s_strcpy(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_FIRST_SELECT_AV_INPUT));
    if(c_uc_w2s_strncmp(&cec_name[0],ipts_name,256) == 0)//different name means name renamed
    {
        c_memset(w2s_string, 0, 256);
        c_uc_w2s_strcpy(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_FIRST_SELECT_AV_INPUT_NO_DEVICE));
    }
    if (_nav_ipts_w2s_str_replace(w2s_string, 256, w2s_arr, 3) != 0)
    {
        DBG_ERROR(("{%s,%d} _nav_ipts_w2s_str_replace() failed, ret=%d\n", __FUNCTION__, __LINE__, i4_ret));
        return;
    }

    strlen = (c_uc_w2s_strlen(w2s_string)+1)*2;
    pt_toast->style.style_4.w2s_str = c_mem_alloc(strlen);
    c_memset(pt_toast->style.style_4.w2s_str, 0, strlen);
    c_uc_w2s_strncpy((UTF16_T*)pt_toast->style.style_4.w2s_str, w2s_string, c_uc_w2s_strlen(w2s_string));

#ifdef  APP_TTS_SUPPORT
    a_app_tts_play(w2s_string, 256);
#endif

    do
    {
        HANDLE_T  h_timer = NULL_HANDLE;

        i4_ret = c_timer_create(&h_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("{%s,%d} c_timer_create() failed, ret=%d\n", __FUNCTION__, __LINE__, i4_ret));
            return;
        }

        i4_ret = c_timer_start(
                    h_timer,
                    1000,
                    X_TIMER_FLAG_ONCE,
                    _nav_ipts_first_select_av_src_cb_fct,
                    NULL);

        if (OSR_OK != i4_ret)
        {
            DBG_ERROR(("{%s,%d} c_timer_start() failed, ret=%d\n", __FUNCTION__, __LINE__, i4_ret));
            return;
        }

        nav_send_msg_to_component(
                    NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                    NAV_UI_MSG_REST_NOTIFICATION,
                    (VOID*)pt_toast);
    } while(0);

}
static VOID _nav_ipts_first_select_av_src_nfy_func(
                    UINT16     ui2_nfy_id,
                    VOID*      pv_tag,
                    UINT16     ui2_id
                    )
{
    UINT16  ui2_rec_id = CFG_GET_SETTING(ui2_id);
    ISL_REC_T   t_isl_rec;
    UINT32      ui4_ipts_name;
    UINT8       ipts_sel_state;

    if ((ui2_nfy_id != ui2_1th_nfy_id) ||
        (ui2_rec_id != APP_CFG_RECID_INPUT_MAIN))
    {
        return;
    }

    nav_get_isl_rec(TV_WIN_ID_MAIN, &t_isl_rec);
    a_cfg_cust_get_ipts_select_state(&ipts_sel_state);

    if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
    {
        if (0 == t_isl_rec.ui1_internal_id && !(ipts_sel_state & IPTS_SELECT_HDMI1))
        {
            ipts_sel_state |= IPTS_SELECT_HDMI1;
            ui4_ipts_name = 0;
        }
        else if (1 == t_isl_rec.ui1_internal_id && !(ipts_sel_state & IPTS_SELECT_HDMI2))
        {
            ipts_sel_state |= IPTS_SELECT_HDMI2;
            ui4_ipts_name = 1;
        }
        else if (2 == t_isl_rec.ui1_internal_id && !(ipts_sel_state & IPTS_SELECT_HDMI3))
        {
            ipts_sel_state |= IPTS_SELECT_HDMI3;
            ui4_ipts_name = 2;
        }
        else
        {
            return;
        }
    }
    else if (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type && !(ipts_sel_state & IPTS_SELECT_COMP))
    {
         ipts_sel_state |= IPTS_SELECT_COMP;
         ui4_ipts_name = 3;
    }
    else
    {
        return;
    }
    a_cfg_cust_set_ipts_select_state(ipts_sel_state);
    a_banner_set_excl_comp_on(TRUE);

    nav_request_context_switch(_nav_ipts_first_select_av_src_nfy_fct, (VOID*)ui4_ipts_name, NULL, NULL);
}

static VOID _nav_ipts_first_select_av_src_nfy_reg(VOID)
{
    UINT8 ipts_sel_state = 0;

    a_cfg_cust_get_ipts_select_state(&ipts_sel_state);

    if (!(IPTS_SELECT_HDMI1 & ipts_sel_state) ||
        !(IPTS_SELECT_HDMI2 & ipts_sel_state) ||
        !(IPTS_SELECT_HDMI3 & ipts_sel_state) ||
        !(IPTS_SELECT_COMP  & ipts_sel_state))
    {
        if (APP_CFGR_OK != a_cfg_notify_reg(
                                APP_CFG_GRPID_NAV,
                                NULL,
                                _nav_ipts_first_select_av_src_nfy_func,
                                &ui2_1th_nfy_id))
        {
            DBG_ERROR(("<INPUT SRC> register _nav_ipts_1th_hdmi_x_or_comp_nfy fail!\r\n"));
        }
    }
    else
    {
        DBG_INFO(("<INPUT SRC> doesn't 1th select hdmi_x & comp, skip reg !\r\n"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_deinit(VOID)
{
    _INPUT_SRC_T*              pt_this = &t_g_input_src;
    INT32                      i4_ret;

    /* unregister remove device notification function */
    i4_ret = a_rmv_dev_unreg_monitor(pt_this->ui4_rmv_dev_nfy);
    DBG_ERROR((_ERROR_HEADER"%s(): Fail to unregiste, ret = %d\r\n", __FUNCTION__, i4_ret));

    /* Close IOM handler. */
    i4_ret = c_iom_close (pt_this->h_iom);
    NAV_LOG_ON_FAIL(i4_ret);

    /*deinit Input-Src-View*/
    if(pt_this->t_view_handler.pf_deinit)
    {
        i4_ret = pt_this->t_view_handler.pf_deinit(pt_this->pv_view);
    }
    else
    {
        i4_ret = NAVR_OK;
    }

    /*free resource*/
    if(pt_this->pac_rating_d_buf)
    {
        c_mem_free(pt_this->pac_rating_d_buf);
    }

    c_memset(pt_this, 0, sizeof(_INPUT_SRC_T));
    b_input_list_init = FALSE;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_ipts_is_key_handler(
    NAV_CONTEXT_T*                   pt_ctx,
    UINT32                           ui4_key_code)
{
    _INPUT_SRC_T*              pt_this = &t_g_input_src;

    NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_CH_LIST_UI) == TRUE) {
        return FALSE;
    }

    nav_ipts_list_manual_close();

    return pt_this->t_view_handler.pf_is_key_handler(pt_this->pv_view,
                                                     pt_ctx->t_svc_res.e_focus_tv_win_id,
                                                     ui4_key_code);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_activate(
    NAV_CONTEXT_T*              pt_ctx,
    UINT32                      ui4_key_code)
{
    _INPUT_SRC_T*               pt_this = &t_g_input_src;
    INT32                       i;

    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        pt_this->at_grp[i].t_last_notify.b_is_active_comp = TRUE;

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               (TV_WIN_ID_T)i,
                                               NAV_IPTS_UI_IF_ACT_COMP,
                                               &pt_this->at_grp[i].t_last_notify);
    }

	close(open("/tmp/sidebar_menu_show", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));

#ifdef APP_REGISTRY_SUPPORT
    a_registry_set_menu_ui_state(REG_UI_STATE_VISIBLE);
#endif

    /*handle key*/
    return pt_this->t_view_handler.pf_key_handler(pt_this->pv_view,
                                                  pt_ctx->t_svc_res.e_focus_tv_win_id,
                                                  ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_inactivate(
    NAV_CONTEXT_T*                pt_ctx)
{
    _INPUT_SRC_T*                 pt_this = &t_g_input_src;
    INT32                         i;

    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        pt_this->at_grp[i].t_last_notify.b_is_active_comp = FALSE;

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               (TV_WIN_ID_T)i,
                                               NAV_IPTS_UI_IF_ACT_COMP,
                                               &pt_this->at_grp[i].t_last_notify);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_hide(VOID)
{
    _INPUT_SRC_T* pt_this = &t_g_input_src;

    pt_this->t_view_handler.pf_hide(pt_this->pv_view);
	unlink("/tmp/sidebar_menu_show");

#ifdef APP_REGISTRY_SUPPORT
    a_registry_set_menu_ui_state(REG_UI_STATE_INVISIBLE);
#endif
    return NAVR_OK;
}
#ifdef APP_CUSTOM_DYNAMIC_HDMI_SRC_NAME
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_update_info_to_ui_for_hdmi
 * Description
 * Input arguments
 *      pt_this
 *      e_grp
 * Output arguments
 *      pt_isl_rec
 *      pe_to_ui
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_update_info_to_ui_for_hdmi(
    _INPUT_SRC_T*                         pt_this,
    TV_WIN_ID_T                           e_grp,
    ISL_REC_T*                            pt_isl_rec,
    _NAV_IPTS_INFO_TO_UI_T*               pe_to_ui)
{
    INT32 i4_ret;

    /* Only when video connection is connected, middleware::CM can know the
     * connection with audio stream or not (with audio stream = HDMI, without
     * audio stream = DVI). Otherwise, middleware doesn't know the video content
     * is from DVI or HDMI. weider chang 6/9/2007
     */

    i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, pt_isl_rec);
    if (i4_ret == TVR_OK && pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI) {
        (*pe_to_ui) |= _NAV_IPTS_INFO_TUI_SRC_UPDATE;
    }
}
#else
#define _nav_ipts_update_info_to_ui_for_hdmi(p1, p2, p3, p4)
#endif

static UINT8 _nav_ipts_smartcast_index()
{
    ISL_REC_T t_isl_rec = {0};
    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, 0, &t_isl_rec);
    UINT16 hdmi_port_count = (UINT16)t_isl_rec.ui1_iid_count;
    return hdmi_port_count + 3;
}

static UINT8 _nav_ipts_airplay_index()
{
    return _nav_ipts_smartcast_index() + 1;
}

BOOL a_nav_ipts_on_smartcast()
{
    _INPUT_SRC_T*                 pt_this = &t_g_input_src;
    _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[0];

    UINT8 ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;
    printf("BOOTSC ui1_old_id = %d\n",ui1_old_id);

    if (ui1_old_id == _nav_ipts_smartcast_index()) {
        printf("BOOTSC Smartcast TRUE\n");
        return TRUE;
    }
    printf("BOOTSC Smartcast FALSE\n");
    return FALSE;
}

BOOL _nav_ipts_on_virtual_input()
{
    _INPUT_SRC_T*                 pt_this = &t_g_input_src;
    _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[0];
    UINT8 ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;

    if (ui1_old_id >= _nav_ipts_smartcast_index()) {
        printf("BOOTSC Virtual Input TRUE\n");
        return TRUE;
    }
    printf("BOOTSC Virtual Input FALSE\n");
    return FALSE;
}

BOOL _nav_ipts_on_airplay()
{
    _INPUT_SRC_T*                 pt_this = &t_g_input_src;
    _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[0];

    UINT8 ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;
    printf("BOOTSC ui1_old_id = %d\n",ui1_old_id);

    if (ui1_old_id == _nav_ipts_airplay_index()) {
        printf("BOOTSC Airplay TRUE\n");
        return TRUE;
    }
    printf("BOOTSC Airplay FALSE\n");
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_change_input_to_power_on_option
 * Description
 * Input arguments
 *      pt_this
 *      e_grp
 * Output arguments
 *      pt_isl_rec
 *      pe_to_ui
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_change_input_to_power_on_option(_INPUT_SRC_T* pt_this)
{
    DBG_LOG_PRINT(("_nav_ipts_change_input_to_power_on_option\r\n"));
    printf("BOOTSC _nav_ipts_change_input_to_power_on_option\r\n");
    Enu_POWER_ON_INPUT power_on_input_option = get_power_on_device();
    a_nav_ipts_cancel_smart_cast_after_n_seconds();
    BOOL bSendLog = TRUE;
    boot_sc_logger = startBootSCMetricsLog();
    _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[0];
    UINT8 ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;
    char str[10];
    sprintf(str, "%d", ui1_old_id);

    boot_sc_logger = setInputFrom(boot_sc_logger, (char*)inputSwitchFromText(ui1_old_id));
    sprintf(str, "%d", power_on_input_option);

    switch(power_on_input_option)
    {
        case E_POWER_ON_INP_SMARTCAST:
            boot_sc_logger = setInputTo(boot_sc_logger, "SMARTCAST");

            DBG_LOG_PRINT(("E_POWER_ON_INP_SMARTCAST\r\n"));
            printf("BOOTSC E_POWER_ON_INP_SMARTCAST\r\n");
            if (_nav_ipts_on_virtual_input()) {
                _nav_power_on_switch_to_virtual_input(_NAV_SWITCH_SMARTCAST, VIRTUAL_SWITCH_TIMEOUT);
            }
            else {
                _nav_power_on_switch_to_virtual_input(_NAV_SWITCH_SMARTCAST, DELAY_SWITCH_TIMEOUT);
            }
        break;

        case E_POWER_ON_INP_HDMI1:
            boot_sc_logger = setInputTo(boot_sc_logger, "HDMI-1");

            printf("BOOTSC E_POWER_ON_INP_HDMI1\r\n");
            DBG_LOG_PRINT(("E_POWER_ON_INP_HDMI1\r\n"));
               if (_nav_ipts_on_virtual_input()) {
                _nav_delay_switch_inputs(2);
            }
            else {
                _nav_ipts_change_input_src(pt_this,3,0,2,true);
            }
        break;

        case E_POWER_ON_INP_HDMI2:
            boot_sc_logger = setInputTo(boot_sc_logger, "HDMI-2");

            printf("BOOTSC E_POWER_ON_INP_HDMI2\r\n");
            DBG_LOG_PRINT(("E_POWER_ON_INP_HDMI2\r\n"));
               if (_nav_ipts_on_virtual_input()) {
                _nav_delay_switch_inputs(3);
            }
            else {
                _nav_ipts_change_input_src(pt_this,3,0,3,true);
            }
        break;

        case E_POWER_ON_INP_HDMI3:
            boot_sc_logger = setInputTo(boot_sc_logger, "HDMI-3");

            printf("BOOTSC E_POWER_ON_INP_HDMI3\r\n");
            DBG_LOG_PRINT(("E_POWER_ON_INP_HDMI3\r\n"));
               if (_nav_ipts_on_virtual_input()) {
                _nav_delay_switch_inputs(4);
            }
            else {
                _nav_ipts_change_input_src(pt_this,3,0,4,true);
            }
        break;

        case E_POWER_ON_INP_HDMI4:
            boot_sc_logger = setInputTo(boot_sc_logger, "HDMI-4");

            printf("BOOTSC E_POWER_ON_INP_HDMI4\r\n");
            DBG_LOG_PRINT(("E_POWER_ON_INP_HDMI4\r\n"));
               if (_nav_ipts_on_virtual_input()) {
                _nav_delay_switch_inputs(5);
            }
            else {
                _nav_ipts_change_input_src(pt_this,3,0,5,true);
            }
        break;

        case E_POWER_ON_INP_AIRPLAY:
            boot_sc_logger = setInputTo(boot_sc_logger, "AIRPLAY");

            printf("BOOTSC E_POWER_ON_INP_AIRPLAY\r\n");
            if (_nav_ipts_on_virtual_input()) {
                _nav_power_on_switch_to_virtual_input(_NAV_SWITCH_AIRPLAY,VIRTUAL_SWITCH_TIMEOUT);
            }
            else {
                _nav_power_on_switch_to_virtual_input(_NAV_SWITCH_AIRPLAY, DELAY_SWITCH_TIMEOUT);
            }
        break;

        case E_POWER_ON_INP_ANTENNA:
            boot_sc_logger = setInputTo(boot_sc_logger, "ANTENNA");

            DBG_LOG_PRINT(("E_POWER_ON_INP_ANTENNA\r\n"));
               if (_nav_ipts_on_virtual_input()) {
                _nav_delay_switch_inputs(0);
            }
            else {
                _nav_ipts_change_input_src(pt_this,3,0,0,true);
            }
        break;

        case E_POWER_ON_INP_COMPOSITE:
            boot_sc_logger = setInputTo(boot_sc_logger, "COMPOSITE");

            DBG_LOG_PRINT(("E_POWER_ON_INP_COMPOSITE\r\n"));
               if (_nav_ipts_on_virtual_input()) {
                _nav_delay_switch_inputs(1);
            }
            else {
                _nav_ipts_change_input_src(pt_this,3,0,1,true);
            }
        break;

        default: //For Automatic and Previous Input do nothing here
            DBG_LOG_PRINT(("_nav_ipts_change_input_to_power_on_option: DEFAULT (do nothing)\r\n"));
            bSendLog = FALSE;
        break;

    }
    printf("BOOTSC setting b_first_input_after_boot false (1)\n");
    b_first_input_after_boot = FALSE;
    boot_sc_logger = setScenario(boot_sc_logger, "POWER_ON");
    boot_sc_logger = setPowerOnInputSetting(boot_sc_logger, (char*)powerOnIndexToText(get_power_on_device()));
    if (bSendLog) {
        showLog(boot_sc_logger);
        sendLog(boot_sc_logger);
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_handle_msg(
    NAV_CONTEXT_T*                pt_ctx,
    NAV_UI_MSG_T*                 pt_ui_msg,
    VOID*                         pv_arg1)
{
    INT32                         i4_ret = NAVR_OK;
    ISL_REC_T                     t_isl_rec;
    _INPUT_SRC_T*                 pt_this = &t_g_input_src;
    _NAV_IPTS_INFO_TO_UI_T        e_to_ui = _NAV_IPTS_INFO_TUI_EMPTY;
    INT32                         i;
    BOOL                          b_delay_nfy = FALSE;

    _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[0];

    UINT8 ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;

    printf("BOOTSC _nav_ipts_handle_msg pt_ui_msg->e_id = %d\n",pt_ui_msg->e_id);
    /*check message source*/
    switch(pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_STREAM_NOTIFY:
        a_nav_ipts_cancel_smart_cast_after_n_seconds();
    case NAV_UI_MSG_NO_SIGNAL:
    case NAV_UI_MSG_EVENT_READY:
    case NAV_UI_MSG_EVENT_NOT_READY:
    case NAV_UI_MSG_LOCKED_INP:
    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_LOCKED_CH:
    case NAV_UI_MSG_UNLOCKED:
        {
            if(INP_SRC_TYPE_AV != nav_get_src_type(pt_ui_msg->e_tv_win_id))
            {
                return NAVR_OK;
            }
        }
        break;

    default:
        break;
    }


    /* Most messages mean power is on except the following */
    switch(pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_POWER_OFF:
    case NAV_UI_MSG_AS_APP_PAUSED:
    case NAV_UI_MSG_POWER_CUT:
    case NAV_UI_MSG_BACKGROUND_MODE:
        break;

    default:
         b_powered_off = FALSE;
        break;
    }

    switch(pt_ui_msg->e_id)

    {
    case NAV_UI_MSG_SYSTEM_POWER_ON:
        printf("BOOTSC NAV_UI_MSG_SYSTEM_POWER_ON\n");
        printf("BOOTSC hiding no signal 2 at power on\n");
        a_scrn_svr_hide_NO_SIGNAL_2();
        printf("BOOTSC setting b_power_on_in_progress to TRUE %d\n",__LINE__);
        b_power_on_in_progress = TRUE;
        printf("BOOTSC setting b_first_input_after_boot TRUE(1)\n");
        b_first_input_after_boot = TRUE;
    break;

    case NAV_UI_MSG_POWER_ON:
        printf("BOOTSC NAV_UI_MSG_POWER_ON\n");
        DBG_INFO(("%s() Line %d: NAV_UI_MSG_SYSTEM_POWER_ON\n", __FUNCTION__, __LINE__));
        break;

    case NAV_UI_MSG_OTHER_APP_RESUMED:
        DBG_LOG_PRINT(("BOOTSC NAV_UI_MSG_OTHER_APP_RESUMED\n"));
        a_nav_ipts_cancel_smart_cast_after_n_seconds();
        DBG_INFO(("%s() Line %d: NAV_UI_MSG_OTHER_APP_RESUMED\n", __FUNCTION__, __LINE__));
        DBG_LOG_PRINT(("BOOTSC b_power_on_in_progress = %d\n",b_power_on_in_progress));
        DBG_LOG_PRINT(("BOOTSC ui1_old_id = %d\n",ui1_old_id));
        if (b_power_on_in_progress && _nav_ipts_on_virtual_input()) {
            DBG_LOG_PRINT(("BOOTSC NAV_UI_MSG_OTHER_APP_RESUMED 2\n"));
            PCL_WAKEUP_KEY_T    t_wakeup_key = {0};
            c_pcl_get_wakeup_irkey(&t_wakeup_key);
            PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
            c_pcl_get_wakeup_reason(&e_wakeup_reason, NULL);

            if (t_wakeup_key.e_key_type != PCL_WAKEUP_KEY_HOTKEY &&
                e_wakeup_reason != PCL_WAKE_UP_REASON_AIRPLAY &&
                e_wakeup_reason != PCL_WAKE_UP_REASON_HDMI) {
                DBG_LOG_PRINT(("BOOTSC NAV_UI_MSG_OTHER_APP_RESUMED 3\n"));
                b_first_input_after_boot = TRUE;
                    _nav_ipts_change_input_to_power_on_option(pt_this);
                }
            else {
                DBG_LOG_PRINT(("BOOTSC Did not switch at power on because hotkey or airplay or hdmi wakeup\n"));
            }
        }
        else {
            printf("BOOTSC setting b_first_input_after_boot false (2)\n");
            b_first_input_after_boot = FALSE;
        }
        printf("BOOTSC setting b_power_on_in_progress to FALSE %d\n",__LINE__);

        b_power_on_in_progress = FALSE;

    break;
        default:
        break;
    }
    /*handle msg*/
    switch(pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_OTHER_APP_RESUMED:
        {
            /* If next APP is MMP, sync info. */
            if (c_strcmp ((CHAR*)pv_arg1, MMP_NAME) == 0)
            {
                /* update pos info and pic size info */
                vid_update_current_input_src_position_info();
                vid_update_current_input_src_pic_size_info();
                _nav_ipts_sync_current_src(pt_this, _NAV_IPTS_INFO_TUI_PLAY_MODE, FALSE);
            }
        }
        break;
    case NAV_UI_MSG_STREAM_NOTIFY:
        {
            return _nav_ipts_stream_nfy_handler(pt_this, pt_ui_msg->e_tv_win_id, (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1);
        }
    case NAV_UI_MSG_WITH_SIGNAL:
        {
            b_has_signal = true;
            _nav_ipts_update_info_to_ui_for_hdmi(pt_this, pt_ui_msg->e_tv_win_id, &t_isl_rec, &e_to_ui);
            a_nav_ipts_cancel_smart_cast_after_n_seconds();
        }
        break;

    case NAV_UI_MSG_NO_SIGNAL:
        {
            b_has_signal = false;
            e_to_ui = (_NAV_IPTS_INFO_TO_UI_T)(_NAV_IPTS_INFO_TUI_LOCK_STATUS | _NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY | _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT);
            _nav_ipts_update_info_to_ui_for_hdmi(pt_this, pt_ui_msg->e_tv_win_id, &t_isl_rec, &e_to_ui);
            NAV_LOG_ON_FAIL(i4_ret);
        }
        break;
	case NAV_UI_MSG_POWER_ON:
	    b_is_first_ch_src = TRUE;
        NAV_CHK_FAIL(i4_ret);
    case NAV_UI_MSG_POWER_OFF:
        b_powered_off = TRUE;
        a_nav_ipts_cancel_smart_cast_after_n_seconds();
    case NAV_UI_MSG_APP_PAUSING:
        {
            a_nav_ctrl_ipt_set_change_source_enable(TRUE);
            return _nav_ipts_app_status_nfy_handler(pt_this, pt_ui_msg->e_id);
        }
    case NAV_UI_MSG_APP_RESUMED:
        {
#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
            if (a_c4tv_apron_check_cast_state())
            {
                //a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED);
#ifdef SYS_OVERRIDE_DISP_REGION_SUPPORT
                extern VOID sys_asp_ratio_set_net_svc_status (APP_TV_NET_SVC_STATUS e_status);
                sys_asp_ratio_set_net_svc_status(APP_TV_NET_SVC_STATUS_RESUMED);
#endif
            }
#endif
            /* update pos info and pic size info */
            vid_update_current_input_src_position_info();
            vid_update_current_input_src_pic_size_info();
            return _nav_ipts_app_status_nfy_handler(pt_this, pt_ui_msg->e_id);
        }
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        {
            ISL_REC_T               t_isl_crnt_rec;
            NAV_XNG_SRC_TRGT_T*     pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;

            NAV_ASSERT(pt_xng_info);
            /* update pos info and pic size info */
            vid_update_current_input_src_position_info();
            vid_update_current_input_src_pic_size_info();
            if(INP_SRC_TYPE_AV == pt_xng_info->e_type)  /*source change, not channel change*/
            {
                i4_ret = a_isl_get_rec_by_id(pt_xng_info->u.t_av.ui1_trgt_inp_src_id, &t_isl_rec);
                if(ISLR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"%s(), a_isl_get_rec_by_id(%d) failed. i4_ret=%d\r\n", __FUNCTION__, pt_xng_info->u.t_av.ui1_trgt_inp_src_id, i4_ret));
                    return NAVR_FAIL;
                }

                i4_ret = a_isl_get_rec_by_id(pt_xng_info->u.t_av.ui1_crnt_inp_src_id, &t_isl_crnt_rec);
                if(ISLR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"%s(), a_isl_get_rec_by_id(%d) failed. i4_ret=%d\r\n", __FUNCTION__, pt_xng_info->u.t_av.ui1_trgt_inp_src_id, i4_ret));
                    return NAVR_FAIL;
                }

                e_to_ui = (_NAV_IPTS_INFO_TO_UI_T)(_NAV_IPTS_INFO_TUI_SRC_UPDATE | _NAV_IPTS_INFO_TUI_LOCK_STATUS | _NAV_IPTS_INFO_TUI_VIDEO_INFO_NOT_READY | _NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY);
                b_delay_nfy = (INP_SRC_TYPE_AV == t_isl_rec.e_src_type && INP_SRC_TYPE_TV == t_isl_crnt_rec.e_src_type) ? TRUE : FALSE; /*TV to AV*/
            }
        }
        break;

    case NAV_UI_MSG_FREQ_CHANGE:
        {

        }
        break;

    case NAV_UI_MSG_AFTER_SVC_CHANGE:
        {
            DBG_INFO(("%s() Line %d: NAV_UI_MSG_AFTER_SVC_CHANGE\n", __FUNCTION__, __LINE__));
            pt_this->at_grp[TV_WIN_ID_MAIN].t_last_notify.e_cmd = NAV_IPTS_CMD_VIEW_CHG_ACTIVE;
            pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                   TV_WIN_ID_MAIN,
                                                   NAV_ITPS_UI_IF_DO_CMD,
                                                   &pt_this->at_grp[TV_WIN_ID_MAIN].t_last_notify);
        }
        break;

        case NAV_UI_MSG_TV_SRC_CHANGED:
        {
            DBG_INFO(("<UHD color> file: %s line: %d  %s NAV_UI_MSG_TV_SRC_CHANGED\n", __FILE__, __LINE__, __FUNCTION__));
        }
        break;

    case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
        {
            /*update data*/
            NAV_TV_MODE_XNG_INFO_T* pt_mode_info = (NAV_TV_MODE_XNG_INFO_T*)pv_arg1;

            for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
            {
                pt_this->at_grp[i].t_last_notify.e_play_mode = pt_mode_info->e_new_tv_mode;
            }
        }
        break;

    case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        {
            /*sync current input source*/
            _nav_ipts_sync_current_src(pt_this, _NAV_IPTS_INFO_TUI_PLAY_MODE, FALSE);
        }
        break;

    case NAV_UI_MSG_FOCUS_CHANGED:
        {
            for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
            {
                pt_this->at_grp[i].t_last_notify.e_focus = (TV_WIN_ID_T)(INT32)pv_arg1;

                pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                                       (TV_WIN_ID_T)i,
                                                       NAV_IPTS_UI_IF_FOCUS,
                                                       &pt_this->at_grp[i].t_last_notify);
            }
        }
        break;

    case NAV_UI_MSG_EVENT_READY:
    case NAV_UI_MSG_EVENT_NOT_READY:
        {
            e_to_ui = _NAV_IPTS_INFO_TUI_RATING_INFO_QUERY;
        }
        break;

    case NAV_UI_MSG_LOCKED_INP:
    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_LOCKED_CH:
        {
            e_to_ui |= _NAV_IPTS_INFO_TUI_LOCK_STATUS | _NAV_IPTS_INFO_TUI_RATING_INFO_QUERY | _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT;
        }
        break;

    case NAV_UI_MSG_UNLOCKED:
        {
            e_to_ui |= _NAV_IPTS_INFO_TUI_LOCK_STATUS | _NAV_IPTS_INFO_TUI_RATING_INFO_QUERY | _NAV_IPTS_INFO_TUI_VIDEO_INFO_QUERY;
        }
        break;

    case NAV_UI_MSG_BEFORE_SVCS_SWAP:
        {
            _nav_ipts_update_swap_status(pt_this, TRUE);
        }
        break;

    case NAV_UI_MSG_AFTER_SVCS_SWAP:
        {
            /*sync current input source*/
            _nav_ipts_sync_current_src(pt_this, _NAV_IPTS_INFO_TUI_EMPTY, FALSE);

            _nav_ipts_update_swap_status(pt_this, FALSE);
        }
        break;

    case NAV_UI_MSG_CH_NUM_INPUT_START:
        e_to_ui = _NAV_IPTS_INFO_TUI_INPUT_CH_NUM_START;
        break;

    case NAV_UI_MSG_CH_NUM_INPUT_END:
        e_to_ui = _NAV_IPTS_INFO_TUI_INPUT_CH_NUM_END;
        break;

    default:
        return NAVR_OK;
    }

    if(_NAV_IPTS_INFO_TUI_EMPTY != e_to_ui)
    {
        _nav_ipts_update_info(pt_this,
                              pt_ui_msg->e_tv_win_id,
                              e_to_ui,
                              (_NAV_IPTS_INFO_TUI_SRC_UPDATE & e_to_ui) ? &t_isl_rec : NULL,
                              b_delay_nfy);
    }

    return NAVR_OK;
}

VOID a_nav_displaying_no_signal_indication(VOID)
{
    boot_sc_logger = startBootSCMetricsLog();
    printf("BOOTSC a_nav_displaying_no_signal_indication\n");
    a_nw_is_network_connected(&b_is_connected);

    printf("BOOTSC a_nav_displaying_no_signal_indication b_is_connected = %d\n",b_is_connected);
    DBG_INFO(("%s() Line %d\n\n", __FUNCTION__, __LINE__));
    if (b_first_input_after_boot)
    {
        //BAW POWER ON SCENARIO
        boot_sc_logger = setScenario(boot_sc_logger, "POWER_ON");
        PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
        c_pcl_get_wakeup_reason(&e_wakeup_reason, NULL);
        if (get_power_on_device() == E_POWER_ON_INP_AUTOMATIC &&
                    e_wakeup_reason != PCL_WAKE_UP_REASON_HDMI &&
                    b_is_connected)
        {
            DBG_INFO(("%s() Line %d Switching to SmartCast\n\n", __FUNCTION__, __LINE__));
            _INPUT_SRC_T*                 pt_this = &t_g_input_src;
            _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[0];
            UINT8 ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;
            char str[10];
            sprintf(str, "%d", ui1_old_id);

            boot_sc_logger = setInputFrom(boot_sc_logger, (char*)inputSwitchFromText(ui1_old_id));
            boot_sc_logger = setInputTo(boot_sc_logger, "SMARTCAST");
            boot_sc_logger = setPowerOnInputSetting(boot_sc_logger, (char*)powerOnIndexToText(get_power_on_device()));
            showLog(boot_sc_logger);
            sendLog(boot_sc_logger);
            rest_event_notify_current_input("CAST:SMARTCAST");
        }
    }
    else if (b_is_connected && a_nav_should_display_messaging())
    {
        //BAW INPUT SWITCH SCENARIO
        boot_sc_logger = setScenario(boot_sc_logger, "INPUT_SWITCH");
        b_has_signal = FALSE;
        DBG_INFO(("%s() Line %d Delay Switching to SmartCast\n\n", __FUNCTION__, __LINE__));
        _nav_ipts_smart_cast_after_n_seconds(HDMI_NO_SIGNAL_SMARTCAST_DELAY_SWITCH);
    }
}


static void _nav_ipts_smart_cast_after_n_seconds(UINT32 seconds)
{
    INT32                         i4_ret = NAVR_OK;

    b_smart_cast_switch_pending= TRUE;
    i4_ret = c_timer_start(
                    h_no_signal_scrn_svr_timer,
                    seconds * 1000,
                    X_TIMER_FLAG_ONCE,
                    _nav_ipts_no_signal_scrn_svr_timer_cb_fct,
                    NULL);
}

BOOL a_nav_ipts_first_input_after_boot()
{
    return b_first_input_after_boot;
}

BOOL a_smart_cast_switch_pending()
{
    return b_smart_cast_switch_pending;
}


void a_nav_ipts_cancel_smart_cast_after_n_seconds()
{
    printf("BOOTSC a_nav_ipts_cancel_smart_cast_after_n_seconds\n");
   if (b_smart_cast_switch_pending)
    {
        printf("BOOTSC stopping screen saver timer\n");
        c_timer_stop(h_no_signal_scrn_svr_timer);
    }
    b_smart_cast_switch_pending = FALSE;
    printf("BOOTSC hiding NO_SIGNAL_2\n");
    a_scrn_svr_hide_NO_SIGNAL_2();

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_stream_nfy_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_stream_nfy_handler(
    _INPUT_SRC_T*                         pt_this,
    TV_WIN_ID_T                           e_grp,
    NAV_STREAM_NOTIFY_DATA_T*             pt_nfy)
{
    _NAV_IPTS_INFO_TO_UI_T                e_to_ui;

    if(NAV_SNT_STREAM_UPDATED != pt_nfy->e_type &&
       NAV_SNT_STREAM_STOPPED != pt_nfy->e_type &&
       NAV_SNT_STREAM_NOT_SUPPORT != pt_nfy->e_type &&
       NAV_SNT_STREAM_NOT_FOUND != pt_nfy->e_type)
    {
        return NAVR_OK;
    }

    switch(pt_nfy->e_strm_type)
    {
    case ST_VIDEO:
        {
            if(NAV_IPTS_UI_IS_NOT_READY == pt_this->at_grp[e_grp].t_last_notify.t_crnt_video.e_status)
            {
                e_to_ui = (NAV_SNT_STREAM_UPDATED == pt_nfy->e_type) ?
                                _NAV_IPTS_INFO_TUI_VIDEO_INFO_QUERY :
                                ((NAV_SNT_STREAM_NOT_FOUND == pt_nfy->e_type) ? _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT :
                                                                                _NAV_IPTS_INFO_TUI_EMPTY);
            }
            else
            {
                e_to_ui = (NAV_SNT_STREAM_STOPPED == pt_nfy->e_type) ? _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT :
                                                                       (_NAV_IPTS_INFO_TO_UI_T)(_NAV_IPTS_INFO_TUI_VIDEO_INFO_QUERY | _NAV_IPTS_INFO_TUI_RATING_INFO_QUERY);
            }

            if(e_to_ui)
            {
                _nav_ipts_update_info(pt_this, e_grp, e_to_ui, NULL, FALSE);
            }
        }
        break;

    default:
        break;
    }

    return NAVR_OK;
}


static INT32 _nav_ipts_read_IR_KeyCode(UINT32* ui4_databuf)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T	  t_op_info= {0};
    SIZE_T  z_size =  (sizeof(UINT32));
    SIZE_T z_size_drv	= sizeof (DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;


    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_IR_CODE;


    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID*)ui4_databuf;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;


    i4_ret = c_rm_get_comp(
                    DRVT_CUST_DRV,
                    DRV_CUST_COMP_ID,
                    FALSE,
                    ANY_PORT_NUM,
                    0,
                    &t_op_info,
                    &z_size_drv
                );

    return i4_ret;
 }

extern BOOL a_oled_compensation_is_running();

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_app_status_nfy_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_app_status_nfy_handler(
    _INPUT_SRC_T*                             pt_this,
    NAV_UI_MSG_ID_T                           e_id)
{
    NAV_IPTS_UI_APP_STATUS_T                  e_app_status;
    INT32                                     i;
    UINT32                                    keycode = 0;

    switch(e_id)
    {
        case NAV_UI_MSG_POWER_OFF:
        {
            e_app_status = NAV_IPTS_UI_AS_OFF;
        }
        break;

        case NAV_UI_MSG_POWER_ON:
        {
            /*_nav_ipts_change_input_src(pt_this, NAV_IPTS_SMS_TO_TV, TV_WIN_ID_MAIN, 0);*/

            /* NAV_UI_MSG_SYSTEM_POWER_ON ,nav maybe not resume,should check
             * NAV_UI_MSG_SYSTEM_POWER_ON for _nav_ipts_usb_to_cast_power_on too
             */
            _nav_ipts_usb_to_cast_power_on();
            /**/
            e_app_status = (NAV_IPTS_UI_AS_ON_RESUMED == pt_this->at_grp[TV_WIN_ID_MAIN].t_last_notify.e_app_status) ?
                                NAV_IPTS_UI_AS_ON_RESUMED : NAV_IPTS_UI_AS_ON_PAUSED;
        }
        break;

        case NAV_UI_MSG_APP_RESUMED:
        {
            if(a_oled_compensation_is_running())
            {
                break;
            }

        #ifdef APP_C4TV_SUPPORT
            UINT8 ui1_cast_tv_status = 0;
            ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_HOME;
            ISL_REC_T               t_crnt_isl_rec;
            RETAIL_MODE_RUNNING_TYPE_T	t_retail_mode_type = RETAIL_MODE_TYPE_OVERLAY;

            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            t_retail_mode_type = a_nav_retail_mode_get_running_type();

            a_cfg_get_cast_tv_status(&ui1_cast_tv_status);
            DBG_LOG_PRINT(("[NAV_INPUT_SRC] a_cfg_get_cast_tv_status = %d\n", (int)ui1_cast_tv_status));
        #endif

            /*sync current input source*/
            _nav_ipts_sync_current_src(pt_this, _NAV_IPTS_INFO_TUI_EMPTY, FALSE);

            a_isl_get_rec_by_idx(pt_this->at_grp[TV_WIN_ID_MAIN].t_last_notify.t_crnt_input.t_input_src.ui1_id, &t_crnt_isl_rec);

            _nav_ipts_read_IR_KeyCode(&keycode);                        // get the lastest keycode
            DBG_LOG_PRINT(("[hongzhao] _nav_ipts_read_IR_KeyCode get keycode: %d 0x%x\r\n",keycode,keycode));

            /*Note: Nav Controller ignores all stream notifications in paused mode,
                    so this reload operation will trigger SVCTX to resend these notifications*/
            if(_nav_ipts_is_tshift_svc())
            {
                /* If it is tshift mode, the re-select operation is done by
                timeshift component */
                DBG_LOG_PRINT(("[NAV_INPUT_SRC] _nav_ipts_is_tshift_svc is true, don't need to reload source!\r\n"));
            }
        #ifdef APP_C4TV_SUPPORT
            else if(((ui1_cast_tv_status == APP_CFG_CAST_TV_STATUS_CAST_MODE && t_crnt_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST) ||
                    (t_crnt_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_crnt_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST))
                     && ACFG_RETAIL_MODE_NORMAL != t_retail_mode)
            {
                /* Just do not to set audio and video on */
                /* when not in retail mode. */
                DBG_LOG_PRINT(("[NAV_INPUT_SRC] IN CASE MODE OR SOURCE, don't need to reload source!\r\n"));
            }
        #endif
            else if(TRUE == a_wzd_is_oobe_mode())
            {
                DBG_LOG_PRINT(("[NAV_INPUT_SRC] wzd will resume, don't need to reload source!\n"));
            }
            else if (a_nav_cec_nav_resume_by_otp() == TRUE)
            {
                DBG_LOG_PRINT(("[NAV_INPUT_SRC] nav resumed by cec otp, don't need to reload source!\n"));
            }
            else if (keycode == BTN_NETFLIX   || keycode == BTN_AMAZON || keycode == BTN_MGO ||
                     keycode == BTN_VUDU      || keycode == BTN_WIDGET || keycode == BTN_IHEART_RADIO ||
                     keycode == BTN_WATCHFREE || keycode == BTN_REDBOX || keycode == BTN_HAYSTACK)
            {
                DBG_LOG_PRINT(("[NAV_INPUT_SRC] nav resumed by hotkey, don't need to reload source!\n"));
            }
            else if ( (t_retail_mode == ACFG_RETAIL_MODE_NORMAL)
                    &&( (t_retail_mode_type == RETAIL_MODE_TYPE_VIDEO)
                      ||(t_retail_mode_type == RETAIL_MODE_TYPE_VIDEO_INTERNAL) ) )
            {
                DBG_LOG_PRINT(("[NAV_INPUT_SRC] emo video is running, can`t change source!\n"));
            }
            else
            {
                /* when MMP playing,link key second time,MMP pause,then resume NAV
                no need to chg input src,should go to wzd pair page*/
                if (!nav_link_mode_is_on()&&!tuner_setup_during_scan())
                {
                #ifdef APP_CAST_TV_MMP
                    /* mmp->nav parse null mp4 file ,input src no change */
                    if(a_mmp_get_is_parse_null_ff_state())
                    {
                        a_mmp_set_is_parse_null_ff_state(FALSE);
                    }else
                    {
                        _nav_ipts_reload_current_src(pt_this);
                    }
                #else
                    Enu_POWER_ON_INPUT power_on_device = get_power_on_device();
                    BOOL b_power_on_device_changed = g_save_power_on_device != power_on_device;
                    //if g_save_power_on_device == -1, value is not cached
                    if (g_save_power_on_device == -1) {
                        b_power_on_device_changed = FALSE;
                    }

                    PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
                    c_pcl_get_wakeup_reason(&e_wakeup_reason, NULL);

                    BOOL b_source_changed = false;

                    if (e_wakeup_reason == PCL_WAKE_UP_REASON_HDMI) {
                        printf("BOOTSC bypassing power on input because of hdmi wakeup\n");
                        b_source_changed = true;
                    }
                    else if (b_first_input_after_boot) {
                        if (!b_power_on_device_changed &&
                                (power_on_device != E_POWER_ON_INP_AUTOMATIC &&
                                power_on_device != E_POWER_ON_INP_PREVIOUS_INPUT)) {
                            // Jumping to power on device instead of reloading current source

                            PCL_WAKEUP_KEY_T    t_wakeup_key = {0};
                            c_pcl_get_wakeup_irkey(&t_wakeup_key);
                            if (t_wakeup_key.e_key_type != PCL_WAKEUP_KEY_HOTKEY) {
                                printf("BOOTSC calling _nav_ipts_change_input_to_power_on_option(2)\n");
                                _nav_ipts_change_input_to_power_on_option(pt_this);
                                b_source_changed = true;
                            }
                        }
                    }

                    if (!b_source_changed) {
                        printf("BOOTSC reloading current source\n");
                        _nav_ipts_reload_current_src(pt_this);
                    }

                    g_save_power_on_device = power_on_device;
                #endif
                }
            }

            e_app_status = NAV_IPTS_UI_AS_ON_RESUMED;
        }
        break;

        case NAV_UI_MSG_APP_PAUSING:
        {
            CHAR s_active_app[APP_NAME_MAX_LEN] = { 0 };

            a_am_get_next_active_app(s_active_app);

            if(c_strcmp(s_active_app, "mscvt") == 0)
            {
                return NAVR_OK;
            }

            e_app_status = NAV_IPTS_UI_AS_ON_PAUSED;

            nav_hide_component (NAV_COMP_ID_INPUT_SRC);
            return NAVR_OK;
        }
        break;

    default:
        return NAVR_OK;
    }

    /*notify view*/
    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        pt_this->at_grp[i].t_last_notify.e_app_status = e_app_status;

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               (TV_WIN_ID_T)i,
                                               NAV_IPTS_UI_IF_APP_STATUS,
                                               &pt_this->at_grp[i].t_last_notify);
    }

    return NAVR_OK;
}

BOOL a_nav_input_is_cec_processed(VOID)
{
    return b_cec_processed;
}

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
static VOID _nav_ipts_src_c4tv_apron_custom_nfy(
            VOID*    pv_param1, /*BOOL,connect or not; True,connect;FALSE,not connect*/
            VOID*    pv_param2, /*UINT8,for ForcedUpdate,it is C4TV_APRON_UPDATE_STATE_T*/
            VOID*    pv_param3)
{
    DBG_INFO(("<NAV INPUT> Exit CastTV source done.\r\n"));

    b_exiting_cast = FALSE;
    if (t_stop_c4tv_from_link)
    {
        DBG_INFO(("<NAV INPUT>a_c4tv_apron_resume_cast.\r\n"));
        a_c4tv_apron_resume_cast();
        DBG_INFO(("<NAV INPUT>begin enter cast mode after exit link pair.\r\n"));
        a_c4tv_apron_enter_cast_mode();
    }
    t_stop_c4tv_from_link = FALSE;
#if 0  //no need select source again, because c4tv_apron will select current source after it exit
    _nav_ipts_apply_src_selection(&t_g_input_src,
                                    t_g_chg_src_info.e_grp,
                                    t_g_chg_src_info.e_to_ui,
                                    &t_g_chg_src_info.t_next_isl_rec);
#endif
    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_ipts_src_c4tv_apron_custom_nfy
 * Description: Listen cast exit message for other app caused.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID a_nav_ipts_src_c4tv_apron_custom_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    _nav_ipts_src_c4tv_apron_custom_nfy(pv_param1, pv_param2, pv_param3);
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_stop_ipts_src_c4tv_apron_custom_nfy_from_link
 * Description: if a_nav_ipts_src_c4tv_apron_custom_nfy is from link mode
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID a_nav_stop_ipts_src_c4tv_apron_custom_nfy_from_link(BOOL b_from_link)
{
    t_stop_c4tv_from_link = b_from_link;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_ipts_src_set_c4tv_apron_exit_status
 * Description: Set cast exiting state by other app.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID a_nav_ipts_src_set_c4tv_apron_exit_status(BOOL b_exit)
{
    b_exiting_cast = b_exit;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_change_input_src_check_casttv_status
 * Description
 *      return cast state in this case
 * Input arguments
 * Output arguments
 *      FALSE -> C4TV_APRON_STATE_UNKNOWN || C4TV_APRON_STATE_WATCHING_TV
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_ipts_change_input_src_check_casttv_status(VOID)
{
    BOOL         b_cast_state = FALSE;

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
    do
    {
        INT32        i4_ret =NAVR_OK;
        ISL_REC_T    t_select_isl_rec,t_isl_rec;

        /* check current input source */
        {
            /* get current input source */
            {
                TV_WIN_ID_T  e_focus_id;

                i4_ret = a_tv_get_focus_win(&e_focus_id);
                NAV_BREAK_ON_FAIL(i4_ret);

                i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
                NAV_BREAK_ON_FAIL(i4_ret);
            }

            if (INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type \
                || DEV_VTRL_CAST  != t_isl_rec.t_avc_info.e_video_type)
            {
                /* not need */
                NAV_BREAK_ON_FAIL(NAVR_NO_ACTION);
            }
        }

        /* check select input source */
        {
            /* get select input source */
            {
                UINT8 ui1_input_src_id = (UINT8)t_g_chg_src_info.ui4_param;
                i4_ret = a_isl_iterate_rec(ui1_input_src_id, ISL_ITERATE_DIR_THIS, &t_select_isl_rec);
                NAV_BREAK_ON_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);
            }

            if(DEV_VTRL_CAST == t_select_isl_rec.t_avc_info.e_video_type)
            {
                /* not need */
                NAV_BREAK_ON_FAIL(NAVR_NO_ACTION);
            }
        }

        b_cast_state = a_c4tv_apron_check_cast_state();
        DBG_INFO(("<NAV INPUT> b_cast_state = %d \r\n", b_cast_state));

        if (b_cast_state == FALSE && a_rest_app_get_current_app_is_uml() == 0)
        {
            DBG_INFO(("<NAV INPUT> Exit user manual.\r\n"));
            a_c4tv_apron_revoke_exit_cast(_nav_ipts_src_c4tv_apron_custom_nfy);
        }
    }while(0);
#endif
    return b_cast_state;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_change_input_src
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_change_input_src_by_id(_INPUT_SRC_T*                   pt_this,
                                              NAV_IPTS_SWITCH_SRC_METHOD_T    e_method,
                                              TV_WIN_ID_T                     e_grp,
                                              UINT8                           ui1_input_src_id)
{
    printf("BOOTSC _nav_ipts_change_input_src_by_id ui1_input_src_id = %d\n",ui1_input_src_id);
    printf("BOOTSC file: %s line: %d  function: %s\n", __FILE__, __LINE__, __FUNCTION__);
    INT32       i4_ret = NAVR_OK;
    ISL_REC_T   t_select_isl_rec;
    UINT16      ui2_pa_dev2 = CECM_INV_PA;
    UINT8       ui1_cec_func = APP_CFG_CEC_OFF;

    /* get select input source */
    i4_ret = a_isl_iterate_rec(ui1_input_src_id, ISL_ITERATE_DIR_THIS, &t_select_isl_rec);
    NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);
    printf("BOOTSC file: %s line: %d  function: %s\n", __FILE__, __LINE__, __FUNCTION__);

#ifdef APP_CEC_MENU
    {
        UINT8    ui1_num_recs	   = 0;
        UINT16    ui2_hlt_index    = 0;
        UINT8     hdmi_act_src = nav_cec_util_is_hdmi_act_src();

        DBG_LOG_PRINT(("#### is_hdmi_act_src (%d) \n",hdmi_act_src));
        DBG_LOG_PRINT(("#### b_nav_ipts_lst_set_active_flag(0x%0X) input_source_vcec_pa (%X) \n",b_nav_ipts_lst_set_active_flag,input_source_vcec_pa));
        printf("BOOTSC file: %s line: %d  function: %s\n", __FILE__, __LINE__, __FUNCTION__);

        if(input_source_vcec_pa > 0)
        {
            ui2_pa_dev2 = input_source_vcec_pa;
        }
        else
        {
            ui2_pa_dev2 = (UINT16)((t_select_isl_rec.ui1_internal_id+1)<< 12);
        }

        a_cfg_get_cec_func(&ui1_cec_func);
        if (APP_CFG_CEC_ON == ui1_cec_func)
        {
            DBG_LOG_PRINT(("#### %s(%d) %X (%X) (%d)\n", __FILE__, __LINE__ , ui2_pa_dev2,
            t_select_isl_rec.t_avc_info.e_video_type,
            t_select_isl_rec.e_src_type));

            //if(t_select_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI &&
            //t_select_isl_rec.e_src_type == INP_SRC_TYPE_AV)
            if((hdmi_act_src == TRUE) && (t_select_isl_rec.e_src_type == INP_SRC_TYPE_AV))
            {
                if ( (Get_nav_cec_otp_set_stream_path_flag() == TRUE)
                   ||(input_source_vcec_pa > 0 && b_nav_ipts_lst_set_active_flag == TRUE) )
                {
                    c_cecm_set_stream_path_ex(nav_cec_get_mw_handle (), ui2_pa_dev2);
                    Clean_nav_cec_otp_set_stream_path_flag();
                    b_nav_ipts_lst_set_active_flag = FALSE;
                    DBG_LOG_PRINT(("#### %s(%d) @c_cecm_set_stream_path_ex \r\n", __FILE__, __LINE__ ));
                }
            }
        }

        input_source_vcec_pa = 0;
        a_isl_get_num_rec(&ui1_num_recs);
        nav_ipts_get_hlt_full_range_id(&ui2_hlt_index);

        if(b_is_first_ch_src)
        {
            if (t_select_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI)
            {
                b_is_first_ch_src = FALSE;
                return NAVR_OK;
            }
            b_is_first_ch_src = FALSE;
        }
        else if ( (t_select_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI)
                ||(a_nav_ipts_ist_is_select_dev_in_lst() == FALSE) )
        {
            return NAVR_OK;
        }
    }
#endif

    return NAVR_OK;
}

static VOID _nav_ipts_menu_to_tv_cb_fct (HANDLE_T  pt_tm_handle, VOID*     pv_tag)
{
    a_amb_clean_stack();
    DBG_INFO(("_nav_ipts_menu_to_tv_cb_fct timer cb done\n"));
}

static BOOL _nav_check_conjureApp_status(VOID)
{
    BOOL         b_conjure_app_status = TRUE;

    MI_RESULT                   e_ret               = MI_ERR_FAILED;
    MI_HANDLE                   h_MI_MM_Hdl;
    MI_MM_QueryHandleParams_t   stQueryHandleParams;

    UINT32                      ui4_idx             = 0xD431;// %d  =  54321
    CHAR                        szMmName[128]       = {0};

    c_snprintf(szMmName, sizeof(szMmName), "CMA_OVER_MI_MM_%d", ui4_idx);

    DBG_LOG_PRINT(("szMmName:%s.\n",szMmName));

    stQueryHandleParams.pszName = (uint8_t *)szMmName;
    stQueryHandleParams.eMediaType = E_MI_MM_MEDIA_MOVIE;

    e_ret = MI_MM_GetHandle(&stQueryHandleParams,&h_MI_MM_Hdl);
    if(e_ret != MI_OK)
    {
        DBG_LOG_PRINT(("MI_MM_GetHandle fail ret = %d\n", e_ret));
        return FALSE;
    }
    DBG_LOG_PRINT(("<NAV INPUT>MI_MM_GetHandle  = %d\n", h_MI_MM_Hdl));

    return b_conjure_app_status;
}


/*-----------------------------------------------------------------------------
 * Name
 *      get_hdmi1_input_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 get_hdmi1_input_info(ISL_REC_T * t_isl_hdmi1_iterate)
{
    UINT8           ui1_loop = 0;
    UINT8           ui1_isl_num = 0;
    INT32           i4_ret;
    ISL_REC_T       t_isl_iterate = {0};

    i4_ret = a_isl_get_num_rec(&ui1_isl_num);

    for (ui1_loop = 0; ui1_loop < ui1_isl_num; ui1_loop++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_loop, &t_isl_iterate);

        if(t_isl_iterate.e_src_type == INP_SRC_TYPE_AV && t_isl_iterate.t_avc_info.e_video_type == DEV_AVC_HDMI && t_isl_iterate.ui1_internal_id ==0)
        {
            c_memcpy(t_isl_hdmi1_iterate, &t_isl_iterate, sizeof(t_isl_iterate));

            DBG_LOG_PRINT((" get hdmi1 input info\n"));
            return NAVR_OK ;
        }
     }

    return NAVR_OK ;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_change_input_src
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_change_input_src(
    _INPUT_SRC_T*                       pt_this,
    NAV_IPTS_SWITCH_SRC_METHOD_T        e_method,
    TV_WIN_ID_T                         e_grp,
    UINT32                              ui4_param,
    BOOL                                b_apply_same)
{
    ISL_REC_T                           t_next_isl_rec, t_other_isl_rec;
    _NAV_IPTS_GROUP_DATA_T*             pt_grp = &pt_this->at_grp[e_grp];
    _NAV_IPTS_GROUP_DATA_T*             pt_other_grp;
    _NAV_IPTS_INFO_TO_UI_T              e_to_ui;
    INT32                               i4_ret, i;
    UINT8                               ui1_next_id, ui1_old_id;
    BOOL                                b_same_grp;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_method:%d, ui4_param:0x%X\n",
        __FUNCTION__, __LINE__, e_method, ui4_param )); );

    /*check param*/
    NAV_ASSERT((((INT32)e_grp) >= 0) && (e_grp < TV_WIN_ID_LAST_VALID_ENTRY));

    ui1_old_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;

    switch(e_method)
    {
        case NAV_IPTS_SMS_NEXT:
        case NAV_IPTS_SMS_PREV:
        case NAV_IPTS_SMS_NEXT_BY_DEVICE_TYPE:
        {
            if(TV_MODE_TYPE_NORMAL == pt_grp->t_last_notify.e_play_mode)
            {
                /*get next input source*/
                if(NAV_IPTS_SMS_NEXT_BY_DEVICE_TYPE == e_method)
                {
                    /*get next input source*/
                    i4_ret = a_isl_next_rec_by_alike_type(pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id,
                                                          (DEVICE_TYPE_T)ui4_param,
                                                          (DEVICE_TYPE_T)ui4_param,
                                                          &t_next_isl_rec);
                    NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );
                }
                else if(NAV_IPTS_SMS_NEXT == e_method)
                {
                    i4_ret = nav_ipts_lst_update_group(pt_this->pv_view, e_grp);
                    NAV_CHK_FAIL(i4_ret);

                    i4_ret = nav_ipts_get_next_source(ui1_old_id,&t_next_isl_rec);
                    NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );

                    if ( nav_get_skip_virtual_input_state() && t_next_isl_rec.e_src_type == INP_SRC_TYPE_VTRL )
                    {
                        get_hdmi1_input_info(&t_next_isl_rec);
                        nav_set_skip_virtual_input_state(FALSE);
                    }
                }
                else
                {
                    i4_ret = nav_ipts_lst_update_group(pt_this->pv_view, e_grp);
                    NAV_CHK_FAIL(i4_ret);

                    i4_ret = nav_ipts_get_prev_source(ui1_old_id,&t_next_isl_rec);
                    NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );
                }

            }
            else
            {
                pt_other_grp = (TV_WIN_ID_MAIN == e_grp) ? &pt_this->at_grp[TV_WIN_ID_SUB] : &pt_this->at_grp[TV_WIN_ID_MAIN];

                i4_ret = a_isl_get_rec_by_id(pt_other_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id, &t_other_isl_rec);
                NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );

                if(NAV_IPTS_SMS_NEXT_BY_DEVICE_TYPE == e_method)
                {
                    /*get next input source*/
                    i4_ret = a_isl_next_rec_by_alike_type(pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id,
                                                          (DEVICE_TYPE_T)ui4_param,
                                                          (DEVICE_TYPE_T)ui4_param,
                                                          &t_next_isl_rec);
                    NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );


                    i4_ret = a_isl_is_same_group(&t_next_isl_rec, &t_other_isl_rec, &b_same_grp);
                    NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );

                    if(b_same_grp)
                    {
                        DBG_ERROR((_ERROR_HEADER"%s(), Fail to get next isl rec in different group, i4_ret=%d\r\n", __FUNCTION__, i4_ret));
                        return NAVR_FAIL;
                    }
                }
                else
                {
                    ui1_next_id = pt_grp->t_last_notify.t_crnt_input.t_input_src.ui1_id;
                    for(i = 0; i < pt_grp->t_last_notify.ui1_src_count; i++)
                    {
                        /*get next input source*/
                        i4_ret = a_isl_iterate_rec(ui1_next_id,
                                                   ((NAV_IPTS_SMS_NEXT == e_method) ? ISL_ITERATE_DIR_NEXT : ISL_ITERATE_DIR_PREV),
                                                   &t_next_isl_rec);
                        NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );

                        /*check group*/
                        i4_ret = a_isl_is_same_group(&t_next_isl_rec, &t_other_isl_rec, &b_same_grp);
                        NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );

                        if(FALSE == b_same_grp)
                        {
                            break;
                        }

                        ui1_next_id = t_next_isl_rec.ui1_id;
                    }

                    if(i >= pt_grp->t_last_notify.ui1_src_count)
                    {
                        DBG_ERROR((_ERROR_HEADER"%s(), Fail to get next isl rec in different group, i4_ret=%d\r\n", __FUNCTION__, i4_ret));
                        return NAVR_FAIL;
                    }
                }
            }
        }
        break;

        case NAV_IPTS_SMS_BY_ID:
        {
            UINT8       ui1_input_src_id = (UINT8)ui4_param;

            /* get select input source */
            i4_ret = a_isl_iterate_rec(ui1_input_src_id, ISL_ITERATE_DIR_THIS, &t_next_isl_rec);
            NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);

            i4_ret = _nav_ipts_change_input_src_by_id(pt_this,e_method,e_grp,ui1_input_src_id);
            NAV_CHK_FAIL(i4_ret);

        }
        break;

        case NAV_IPTS_SMS_TO_TV:
        {
            i4_ret = _nav_ipts_lookup_tv_isl(pt_this, e_grp, &t_next_isl_rec);
            NAV_CHK_FAIL(i4_ret);
        }
        break;

        case NAV_IPTS_SMS_NONE:
        default:
            return NAVR_OK;
    }

    /*check if the change is necessary*/
    if((FALSE == b_apply_same) && ui1_old_id == t_next_isl_rec.ui1_id)
    {
        return NAVR_OK;
    }

    if(change_source_way == FALSE)
    {
        CHAR ps_name_app[32] = "\0";

        i4_ret = a_nav_ipts_lst_set_current_input_by_rest((void*)pt_this,&t_next_isl_rec);
        NAV_CHK_FAIL(i4_ret);

        a_am_get_active_app(ps_name_app);
        DBG_LOG_PRINT(("[hongzhao] enter _nav_ipts_change_input_src, active app: %s\r\n",ps_name_app));
        if(c_strcmp(ps_name_app, MMP_NAME) == 0)
            a_amb_pause_app(MMP_NAME);
    }

    /*In current implementation, we start a timer to delay the real input source change,
      so we have to notify view here to speed up the UI update.*/
    if(ui1_old_id != t_next_isl_rec.ui1_id)
    {
        e_to_ui = (_NAV_IPTS_INFO_TO_UI_T)((INP_SRC_TYPE_TV == t_next_isl_rec.e_src_type) ?
                                                _NAV_IPTS_INFO_TUI_SRC_UPDATE :
                                                (_NAV_IPTS_INFO_TUI_SRC_UPDATE | _NAV_IPTS_INFO_TUI_VIDEO_INFO_NOT_READY | _NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY));
    }
    else
    {
        e_to_ui = _NAV_IPTS_INFO_TUI_SRC_UPDATE;
    }

    /* update change src info */
    {
        /* set change src info */
        {
            t_g_chg_src_info.e_to_ui = e_to_ui;
            t_g_chg_src_info.e_grp = e_grp;
            t_g_chg_src_info.e_method = e_method;
            t_g_chg_src_info.ui4_param = ui4_param;
            c_memcpy(&t_g_chg_src_info.t_next_isl_rec, &t_next_isl_rec, sizeof(ISL_REC_T));
        }

        /* do action */
        {
            a_nav_ipts_lst_is_select_dev_in_lst(FALSE);

            /* If previous source is CastTV. ps: exit it maybe  do it in common flow */
            if(_nav_ipts_change_input_src_check_casttv_status() == TRUE && e_method == NAV_IPTS_SMS_BY_ID)
            {
                DBG_LOG_PRINT(("<NAV INPUT> Change to non-CastTV source.\r\n"));

                {
                    CHAR         s_disp_name[16+1] = {0};

                    i4_ret =a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                    NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

                    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
                        DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call a_cfg_av_set_input_src()\n", __FUNCTION__,__LINE__ ));
                    );

                    i4_ret =a_cfg_av_set_input_src(s_disp_name, t_g_chg_src_info.t_next_isl_rec.ui1_id);
                    NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

                    i4_ret = _nav_ipts_update_info(pt_this, t_g_chg_src_info.e_grp, _NAV_IPTS_INFO_TUI_SRC_UPDATE, &t_g_chg_src_info.t_next_isl_rec, FALSE);
                    NAV_CHK_FAIL(i4_ret);

                }

                {
                    ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
                    i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
                    NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

                    if (ACFG_RETAIL_MODE_NORMAL != retm_status)
                    {
                        b_exiting_cast = TRUE;
                    }
                    else
                    {
                        b_exiting_cast = FALSE;
                        DBG_LOG_PRINT(("<NAV INPUT> retail mode, no need exit cast.\r\n"));
                    }
                    if(b_exiting_cast&&a_nav_ipts_is_cast_source(&t_g_chg_src_info.t_next_isl_rec))
                    {
                        b_exiting_cast = FALSE;
                        DBG_INFO(("<NAV INPUT> cast app switch to cast.\r\n"));
                    }
                    if(b_exiting_cast == TRUE)
                    {
                        a_c4tv_apron_revoke_exit_cast(_nav_ipts_src_c4tv_apron_custom_nfy);
                        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);
                    }
                 }
            }
            else if(TRUE == a_rest_is_conjure_install() && FALSE == a_nav_ipts_is_cast_source(&t_g_chg_src_info.t_next_isl_rec) && FALSE == change_source_way)
            {
                if (!a_wzd_is_oobe_mode()) {
                    a_tv_net_send_cmd("\n:am,am,:backgm=browser_ctrl\n"); //quit browser_ctrl
                    if(_nav_check_conjureApp_status() == TRUE)
                    {
                        /*wait 3rd-watchfree app exit palying status*/
                        UINT8 count = 20;
                        UINT8 i =0;
                        for(i;i<count;i++)
                        {
                            if(_nav_check_conjureApp_status() == FALSE)
                            {
                                break;
                            }else
                            {
                                DBG_LOG_PRINT(("<NAV INPUT>wait for 150ms,count=%d\n\r",i));
                                c_thread_delay(150);
                            }
                        }
                    }
                    a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);
                    i4_ret = _nav_ipts_apply_src_selection(pt_this, t_g_chg_src_info.e_grp,t_g_chg_src_info.e_to_ui, &t_g_chg_src_info.t_next_isl_rec);
                    NAV_CHK_FAIL(i4_ret);
                    i4_ret = c_timer_start(
                        _h_menu2tv_timer,
                        INPUT_SRC_MENU_TO_TV_TIMER_DELAY,
                        X_TIMER_FLAG_ONCE,
                        _nav_ipts_menu_to_tv_cb_fct, /*clear am stack and reset net flags*/
                        NULL);
                } else {
                    DBG_LOG_PRINT(("%s_%d In OOBE mode. Not puting conjure in background. \n ",__FUNCTION__,__LINE__));
                }
            }
            else if(FALSE == change_source_way)
            {
                i4_ret = _nav_ipts_apply_src_selection(pt_this, t_g_chg_src_info.e_grp,t_g_chg_src_info.e_to_ui, &t_g_chg_src_info.t_next_isl_rec);
                NAV_CHK_FAIL(i4_ret);
            }

            a_cfg_set_fire_nfy_switch(TRUE);
            a_cfg_set_cast_tv_status(APP_CFG_CAST_TV_STATUS_WATCH_TV_MODE);

            //to notify banner,then show it when change to watchfree/airplay
            {
                CHAR        s_vtrl_name[24] = {0};
                UTF16_T     w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

                a_isl_get_display_name_ex(&t_g_chg_src_info.t_next_isl_rec, w2s_alias, 24);
                c_uc_w2s_to_ps(w2s_alias,s_vtrl_name,sizeof(s_vtrl_name));
                DBG_INFO(("[banner] next source type:%s. %d\n",s_vtrl_name,__LINE__));

                //banner final shown name should be ("WatchFree" "AirPlay"),but cast could change it maybe
                if(!c_strcmp(s_vtrl_name,"WatchFree")||!c_strcmp(s_vtrl_name,"Watchfree")||!c_strcmp(s_vtrl_name,"watchfree")||
                   !c_strcmp(s_vtrl_name,"AirPlay")||!c_strcmp(s_vtrl_name,"Airplay")||!c_strcmp(s_vtrl_name,"airplay"))
                {
                    //DBG_LOG_PRINT(("[banner] %s %d next notify banner \n",__FUNCTION__,__LINE__));
                    banner_change_state_to (BANNER_STATE_CH, NEED_SHOW_BANNER_VIEW,UP_TO_VIEW_AT_ONCE);
                }
            }
            change_source_way = FALSE;
        }
    }

    DBG_LOG_PRINT(("[%s][%d] b_nav_ipts_lst_set_active_flag: %d \n", __FUNCTION__, __LINE__, b_nav_ipts_lst_set_active_flag));

    if(b_nav_ipts_lst_set_active_flag == TRUE)
    {
        UINT8 ui1_cec_func = APP_CFG_CEC_OFF;
        ISL_REC_T t_select_isl_rec;
        i4_ret = a_isl_iterate_rec((UINT8)ui4_param, ISL_ITERATE_DIR_THIS, &t_select_isl_rec);
        NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret );

        UINT16 ui2_pa_dev2 = (UINT16)((t_select_isl_rec.ui1_internal_id+1) << 12);

        i4_ret = a_cfg_get_cec_func(&ui1_cec_func);
        NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);

        DBG_LOG_PRINT(("[%s][%d] ui2_pa_dev2(0x%0X) ui1_cec_func(%d) \n", __FUNCTION__, __LINE__,ui2_pa_dev2,ui1_cec_func));

        if(ui1_cec_func == APP_CFG_CEC_ON)
        {
            E_INPUT_SRC_SYS_TYPE c_cur_sys_input_src = a_cfg_av_get_cur_sys_input_src();

             DBG_LOG_PRINT(("[%s][%d] c_cur_sys_input_src(%d)\n", __FUNCTION__, __LINE__, c_cur_sys_input_src));

            if ( c_cur_sys_input_src == E_INPUT_SRC_SYS_HDMI_1 || c_cur_sys_input_src == E_INPUT_SRC_SYS_HDMI_2
               ||c_cur_sys_input_src == E_INPUT_SRC_SYS_HDMI_3 || c_cur_sys_input_src == E_INPUT_SRC_SYS_HDMI_4)
            {
                DBG_LOG_PRINT(("[%s][%d][INPUT_SRC] call c_cecm_set_stream_path_ex \r\n", __FUNCTION__, __LINE__ ));
                c_cecm_set_stream_path_ex(nav_cec_get_mw_handle (), ui2_pa_dev2);
            }
        }
        b_nav_ipts_lst_set_active_flag = FALSE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_apply_src_selection
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_apply_src_selection(
    _INPUT_SRC_T*                          pt_this,
    TV_WIN_ID_T                            e_grp,
    _NAV_IPTS_INFO_TO_UI_T                 e_to_ui,
    const ISL_REC_T*                       pt_new_src)
{
    INT32                                  i4_ret;
    ISL_REC_T                              t_isl_rec = {0};


    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_to_ui:%d, pt_new_src->ui1_id:0x%X\n",
        __FUNCTION__, __LINE__, e_to_ui, pt_new_src->ui1_id )); );

    i4_ret = a_isl_get_rec_by_id(pt_new_src->ui1_id, &t_isl_rec);
    NAV_CHK_FAIL(i4_ret);
    if ( DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type )
    {
        nav_sync_stop_service(TV_WIN_ID_MAIN);
    }

    i4_ret = nav_change_av_inp_by_id(e_grp, pt_new_src->ui1_id, NULL);
    NAV_CHK_FAIL(NAVR_NOT_SUPPORT == i4_ret || NAVR_OK == i4_ret ? NAVR_OK : i4_ret );

    if(NAVR_NOT_SUPPORT == i4_ret)
    {
        e_to_ui |= _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT;
    }
    else if(NAVR_OK == i4_ret)
    {
        if(INP_SRC_TYPE_VTRL == pt_new_src->e_src_type)
        {
            e_to_ui |= _NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT;
            i4_ret = NAVR_DELAY_ACTION;
        }
    }

    if(e_to_ui & _NAV_IPTS_INFO_TUI_SRC_UPDATE)
    {
        NAV_ASSERT(pt_new_src);

        e_to_ui |= (_NAV_IPTS_INFO_TO_UI_T)((INP_SRC_TYPE_TV == pt_new_src->e_src_type) ?
                                                (_NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT | _NAV_IPTS_INFO_TUI_RATING_INFO_WITHOUT) : 0);
    }

    /*notify view*/
    if(e_to_ui)
    {
        _nav_ipts_update_info(pt_this, e_grp, e_to_ui, pt_new_src, FALSE);
    }

    if(INP_SRC_TYPE_TV == pt_new_src->e_src_type)
    {
        /* toggle to TV input source */
        /*nav_return_activation(NAV_COMP_ID_INPUT_SRC);*/       /*this will be modified in the future*/
        /*nav_change_crnt_channel(e_grp);*/
    }
    else
    {
        /* toggle to next AV input source */
        nav_reset_attributes();
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_reload_current_src
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_reload_current_src(
    _INPUT_SRC_T*                         pt_this)
{
    INT32                                 i, i4_ret;

    switch(pt_this->at_grp[TV_WIN_ID_MAIN].t_last_notify.e_play_mode)
    {
        case TV_MODE_TYPE_PIP:
        case TV_MODE_TYPE_POP:
        {
            for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
            {
                i4_ret = _nav_ipts_change_input_src(pt_this,
                                                    NAV_IPTS_SMS_BY_ID,
                                                    (TV_WIN_ID_T)i,
                                                    pt_this->at_grp[i].t_last_notify.t_crnt_input.t_input_src.ui1_id,
                                                    TRUE);
                NAV_CHK_FAIL(i4_ret);
            }
        }
        break;

        case TV_MODE_TYPE_NORMAL:
        default:
        {
            i4_ret = _nav_ipts_change_input_src(pt_this,
                                                NAV_IPTS_SMS_BY_ID,
                                                TV_WIN_ID_MAIN,
                                                pt_this->at_grp[TV_WIN_ID_MAIN].t_last_notify.t_crnt_input.t_input_src.ui1_id,
                                                TRUE);
            NAV_CHK_FAIL(i4_ret);
        }
        break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_sync_current_src
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_sync_current_src(
    _INPUT_SRC_T*                       pt_this,
    _NAV_IPTS_INFO_TO_UI_T              e_to_ui,
    BOOL                                b_delay_notify)
{
    ISL_REC_T                           t_isl_rec;
    INT32                               i4_ret, i;

    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        i4_ret = a_tv_get_isl_rec_by_snk_name(pt_this->at_grp[i].ps_grp_name,
                                              &t_isl_rec);
        if(ISLR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(),  Fail to get current isl rec(grp=%d), i4_ret=%d\r\n", __FUNCTION__, i, i4_ret));
            return NAVR_FAIL;
        }

        _nav_ipts_update_info(pt_this,
                              (TV_WIN_ID_T)i,
                              (_NAV_IPTS_INFO_TO_UI_T)(e_to_ui |
                                                       _NAV_IPTS_INFO_TUI_SRC_UPDATE |
                                                       _NAV_IPTS_INFO_TUI_VIDEO_INFO_QUERY |
                                                       _NAV_IPTS_INFO_TUI_RATING_INFO_QUERY |
                                                       _NAV_IPTS_INFO_TUI_LOCK_STATUS),
                              &t_isl_rec,
                              b_delay_notify);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_update_swap_status
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_update_swap_status(
    _INPUT_SRC_T*                         pt_this,
    BOOL                                  b_swapping)
{
    INT32                                 i;

    for(i = 0; i < TV_WIN_ID_LAST_VALID_ENTRY; i++)
    {
        pt_this->at_grp[i].t_last_notify.b_is_swapping = b_swapping;

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               (TV_WIN_ID_T)i,
                                               NAV_IPTS_UI_IF_SWAP_STATUS,
                                               &pt_this->at_grp[i].t_last_notify);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_delay_ui_notify
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_delay_ui_notify(
    VOID*                             pv_this,
    VOID*                             pv_e_grp,
    VOID*                             pv_e_notify_field)
{
    _INPUT_SRC_T*                     pt_this = (_INPUT_SRC_T*)pv_this;
    NAV_IPTS_UI_INFO_FIELD_T          e_notify_field = (NAV_IPTS_UI_INFO_FIELD_T)(INT32)pv_e_notify_field;
    TV_WIN_ID_T                       e_grp = (TV_WIN_ID_T)(INT32)pv_e_grp;
    UINT8                             ui1_lang_id;

    NAV_ASSERT(pt_this && (e_grp < TV_WIN_ID_LAST_VALID_ENTRY) && (((INT32)e_grp) >= 0));

    /* CR[DTV00211379] Display EAS message in VIDEO source abnormally */
    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_BANNER_UI
        | NAV_EXTERNAL_CTRL_RULE_NO_INP_LIST_UI) == TRUE)
    {
        return ;
    }

    /*notify view*/
    if(e_notify_field)
    {
        /*check gui language*/
        ui1_lang_id = nav_get_mlm_lang_id();

        if(ui1_lang_id != pt_this->at_grp[e_grp].t_last_notify.ui1_gui_lang_id)
        {
            pt_this->at_grp[e_grp].t_last_notify.ui1_gui_lang_id = ui1_lang_id;

            e_notify_field |= NAV_IPTS_UI_IF_GUI_LANG;
        }

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               e_grp,
                                               e_notify_field,
                                               &pt_this->at_grp[e_grp].t_last_notify);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_update_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_update_info(
    _INPUT_SRC_T*                  pt_this,
    TV_WIN_ID_T                    e_grp,
    _NAV_IPTS_INFO_TO_UI_T         e_to_ui,
    const ISL_REC_T*               pt_new_src,
    BOOL                           b_delay_notify)
{
    _NAV_IPTS_GROUP_DATA_T*        pt_grp = &pt_this->at_grp[e_grp];
    NAV_IPTS_UI_INFO_FIELD_T       e_notify_field = NAV_IPTS_UI_IF_EMPTY;
    LOCKED_STATUS_T                e_lock_status;
    INT32                          i4_ret;
    UINT8                          ui1_lang_id;
    BOOL                           b_is_signal_loss, b_not_av;

    /*input source*/
    if(_NAV_IPTS_INFO_TUI_SRC_MASK & e_to_ui)
    {
        NAV_IPTS_UI_INPUT_SRC_INFO_T    t_src_info = {NAV_IPTS_UI_IS_NOT_READY, {INP_SRC_TYPE_UNKNOWN, 0}};

        if(_NAV_IPTS_INFO_TUI_SRC_NOT_READY & e_to_ui)
        {
            t_src_info.e_status = NAV_IPTS_UI_IS_NOT_READY;
        }
        else if(_NAV_IPTS_INFO_TUI_SRC_WITHOUT & e_to_ui)
        {
            t_src_info.e_status = NAV_IPTS_UI_IS_WITHOUT;
        }
        else /*_NAV_IPTS_INFO_TUI_SRC_UPDATE*/
        {
            if(pt_new_src)
            {
                t_src_info.e_status = NAV_IPTS_UI_IS_WITH;

                /*update current source*/
                t_src_info.t_input_src.e_src_group = pt_new_src->e_src_type;
                t_src_info.t_input_src.ui1_id = pt_new_src->ui1_id;
                t_src_info.t_input_src.e_video_type = pt_new_src->t_avc_info.e_video_type;
                t_src_info.t_input_src.w2s_name = a_isl_get_display_name((ISL_REC_T*)pt_new_src);
            }
            else
            {
                t_src_info.e_status = NAV_IPTS_UI_IS_WITHOUT;
            }
        }

        /*diff current detail & last notify*/
        if(t_src_info.e_status != pt_grp->t_last_notify.t_crnt_input.e_status)
        {
            pt_grp->t_last_notify.t_crnt_input = t_src_info;
            e_notify_field |= NAV_IPTS_UI_IF_CRNT_INPUT;
        }
        else if(NAV_IPTS_UI_IS_WITH == t_src_info.e_status)
        {
            /*  Always update input source */
            pt_grp->t_last_notify.t_crnt_input = t_src_info;
            e_notify_field |= NAV_IPTS_UI_IF_CRNT_INPUT;
        }
    }

    /*check signal and locked status*/
    if((_NAV_IPTS_INFO_TUI_VIDEO_INFO_MASK & e_to_ui) || (_NAV_IPTS_INFO_TUI_RATING_INFO_MASK & e_to_ui) || (_NAV_IPTS_INFO_TUI_LOCK_STATUS & e_to_ui))
    {
        b_not_av = (INP_SRC_TYPE_AV != nav_get_src_type(e_grp)) ? TRUE : FALSE;
        b_is_signal_loss = nav_is_signal_loss(e_grp);
        e_lock_status = nav_get_locked_status(e_grp);

        if((_NAV_IPTS_INFO_TUI_VIDEO_INFO_MASK & e_to_ui) || (_NAV_IPTS_INFO_TUI_RATING_INFO_MASK & e_to_ui))
        {
            if(b_is_signal_loss || b_not_av)
            {
                e_to_ui |= (_NAV_IPTS_INFO_TUI_VIDEO_INFO_NOT_READY | _NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY);
            }

            if(LOCKED_STATUS_NONE != e_lock_status)
            {
                e_to_ui |= _NAV_IPTS_INFO_TUI_VIDEO_INFO_NOT_READY;

            #ifdef APP_SHOW_EVENT_RATING_AS_BLOCKED
                /*1. not program rating, don't show rating info
                  2. program rating, show rating info*/
                if(LOCKED_STATUS_PROGRAM_RATING != e_lock_status)
                {
                    e_to_ui |= _NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY;
                }
            #else
                /*don't show rating info for all locked status*/
                e_to_ui |= _NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY;
            #endif
            }
        }

        if(_NAV_IPTS_INFO_TUI_LOCK_STATUS & e_to_ui)
        {
            if((b_is_signal_loss && LOCKED_STATUS_INP_SRC_LOCKED != e_lock_status) || b_not_av)
            {
                e_lock_status = LOCKED_STATUS_NONE;
            }

            if(e_lock_status != pt_grp->t_last_notify.e_lock_status)
            {
                pt_grp->t_last_notify.e_lock_status = e_lock_status;
                e_notify_field |= NAV_IPTS_UI_IF_LOCK_STATUS;
            }
        }
    }

    /*video info*/
    if(_NAV_IPTS_INFO_TUI_VIDEO_INFO_MASK & e_to_ui)
    {
        NAV_IPTS_UI_VIDEO_INFO_T    t_video_info = {NAV_IPTS_UI_IS_NOT_READY, {0}}, t_empty_video = {NAV_IPTS_UI_IS_NOT_READY, {0}};
        NAV_IPTS_UI_VIDEO_INFO_T*   pt_video_info = &t_video_info;

        if(_NAV_IPTS_INFO_TUI_VIDEO_INFO_NOT_READY & e_to_ui)
        {
            pt_video_info->e_status = NAV_IPTS_UI_IS_NOT_READY;
        }
        else if(_NAV_IPTS_INFO_TUI_VIDEO_INFO_WITHOUT & e_to_ui)
        {
            pt_video_info->e_status = NAV_IPTS_UI_IS_WITHOUT;
        }
        else
        {
            i4_ret = nav_get_crnt_video_res_info(e_grp, &pt_video_info->t_res);
            if((NAVR_NOT_EXIST == i4_ret) || (NAVR_OK != i4_ret) || (0 == pt_video_info->t_res.ui4_height) || (VSH_SRC_TIMING_NOT_SUPPORT == pt_video_info->t_res.e_timing_type))
            {
                pt_video_info = &t_empty_video;       /*reset info*/
                pt_video_info->e_status = NAV_IPTS_UI_IS_WITHOUT;
            }
            else
            {
                pt_video_info->e_status = NAV_IPTS_UI_IS_WITH;
            }
        }

        /*diff current video info & last notify*/
        if(pt_video_info->e_status != pt_grp->t_last_notify.t_crnt_video.e_status)
        {
            pt_grp->t_last_notify.t_crnt_video = *pt_video_info;
            e_notify_field |= NAV_IPTS_UI_IF_CRNT_VIDEO;
        }
        else if(NAV_IPTS_UI_IS_WITH == pt_video_info->e_status)
        {
            if((pt_video_info->t_res.ui4_frame_rate != pt_grp->t_last_notify.t_crnt_video.t_res.ui4_frame_rate) ||
               (pt_video_info->t_res.ui4_width != pt_grp->t_last_notify.t_crnt_video.t_res.ui4_width) ||
               (pt_video_info->t_res.ui4_height != pt_grp->t_last_notify.t_crnt_video.t_res.ui4_height) ||
               (pt_video_info->t_res.b_is_progressive != pt_grp->t_last_notify.t_crnt_video.t_res.b_is_progressive) ||
               (pt_video_info->t_res.e_src_asp_ratio != pt_grp->t_last_notify.t_crnt_video.t_res.e_src_asp_ratio) ||
               (pt_video_info->t_res.e_timing_type != pt_grp->t_last_notify.t_crnt_video.t_res.e_timing_type))
            {
                pt_grp->t_last_notify.t_crnt_video = *pt_video_info;
                e_notify_field |= NAV_IPTS_UI_IF_CRNT_VIDEO;
            }
        }
    }

    /*rating info*/
    if(_NAV_IPTS_INFO_TUI_RATING_INFO_MASK & e_to_ui)
    {
        NAV_IPTS_UI_RATING_INFO_T       t_rating_info, t_empty_rating;
        NAV_IPTS_UI_RATING_INFO_T*      pt_rating_info = &t_rating_info;
        ISO_639_LANG_T                  t_639_lang, *pt_lang;
        SIZE_T                          z_len = 0;
        EVCTX_ATSC_RATING_LIST_T*       pt_rating;
        NAV_IPTS_UI_INFO_STATUS_T       e_rating_status;

        /*init variable*/
        NAV_IPTS_UI_RATING_INFO_ZERO(t_rating_info);
        NAV_IPTS_UI_RATING_INFO_ZERO(t_empty_rating);

        if(_NAV_IPTS_INFO_TUI_RATING_INFO_NOT_READY & e_to_ui)
        {
            pt_rating_info->e_status = NAV_IPTS_UI_IS_NOT_READY;
        }
        else if(_NAV_IPTS_INFO_TUI_RATING_INFO_WITHOUT & e_to_ui)
        {
            pt_rating_info->e_status = NAV_IPTS_UI_IS_WITHOUT;
        }
        else
        {
            i4_ret = a_cfg_get_gui_lang(t_639_lang);
            pt_lang = (APP_CFGR_OK == i4_ret) ? &t_639_lang : NULL;

            do
            {
                /*query rating size*/
                i4_ret = c_svctx_get_current_event_info_len(pt_grp->h_svctx,
                                                            EVCTX_KEY_TYPE_RATING,
                                                            (VOID*)pt_lang,
                                                            &z_len);

                /* no rating for this language, try first one */
                if(SVCTXR_EVN_INFO_NOT_FOUND == i4_ret)
                {
                    pt_lang = NULL;
                    i4_ret = c_svctx_get_current_event_info_len(pt_grp->h_svctx,
                                                                EVCTX_KEY_TYPE_RATING,
                                                                (VOID*)NULL,
                                                                &z_len);
                }

                if((SVCTXR_OK != i4_ret) && (SVCTXR_EVN_INFO_NOT_FOUND != i4_ret))
                {
                    pt_rating_info->e_status = NAV_IPTS_UI_IS_NOT_READY;
                    break;
                }
                else if((SVCTXR_EVN_INFO_NOT_FOUND == i4_ret) || (0 == z_len))
                {
                    pt_rating_info->e_status = NAV_IPTS_UI_IS_WITHOUT;
                    break;
                }

                /*alloc resource for rating info*/
                if(_NAV_IPTS_RATING_STATIC_BUF_SIZE >= z_len)   /*use static buffer*/
                {
                    pt_rating = (EVCTX_ATSC_RATING_LIST_T*)pt_this->ac_rating_s_buf;
                }
                else
                {
                    if(pt_this->z_rating_d_buf_size < z_len) /*have to new a memory*/
                    {
                        if(pt_this->pac_rating_d_buf)
                        {
                            c_mem_free(pt_this->pac_rating_d_buf);
                        }

                        pt_this->pac_rating_d_buf = c_mem_alloc(z_len);
                        if(NULL == pt_this->pac_rating_d_buf)
                        {
                            DBG_ERROR((_ERROR_HEADER"%s(): c_mem_alloc failed. (size = %d).\r\n", __FUNCTION__, z_len));
                            pt_rating_info->e_status = NAV_IPTS_UI_IS_WITHOUT;
                            break;
                        }

                        pt_this->z_rating_d_buf_size = z_len;
                    }

                    pt_rating = (EVCTX_ATSC_RATING_LIST_T*)pt_this->pac_rating_d_buf;
                }

                /*get rating info*/
                i4_ret = c_svctx_get_current_event_info(pt_grp->h_svctx,
                                                        EVCTX_KEY_TYPE_RATING,
                                                        (VOID*)pt_lang,
                                                        &z_len,
                                                        pt_rating);
                if(SVCTXR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"[%s] c_svctx_get_current_event_info() failed, ret=%d\r\n", __FUNCTION__, i4_ret));
                    pt_rating_info->e_status = NAV_IPTS_UI_IS_NOT_READY;
                    break;
                }

                i4_ret = a_rating_atsc_get_text(pt_rating, pt_rating_info->ws2_rating, NAV_IPTS_UI_RATING_DESC_LEN);
                if(APP_RATINGR_OK != i4_ret)
                {
                    DBG_ERROR((_ERROR_HEADER"[%s] a_rating_atsc_get_text() failed, ret=%d\r\n", __FUNCTION__, i4_ret));
                    pt_rating_info->e_status = NAV_IPTS_UI_IS_WITHOUT;
                    break;
                }

                pt_rating_info->e_status = NAV_IPTS_UI_IS_WITH;

            } while(0);

            /*check result*/
            if(NAV_IPTS_UI_IS_WITH != pt_rating_info->e_status)
            {
                e_rating_status = pt_rating_info->e_status;
                pt_rating_info = &t_empty_rating;
                pt_rating_info->e_status = e_rating_status;
            }
        }

        /*diff current video info & last notify*/
        if(pt_rating_info->e_status != pt_grp->t_last_notify.t_crnt_rating.e_status)
        {
            pt_grp->t_last_notify.t_crnt_rating = *pt_rating_info;
            e_notify_field |= NAV_IPTS_UI_IF_CRNT_RATING;
        }
        else if(NAV_IPTS_UI_IS_WITH == pt_rating_info->e_status)
        {
            if(0 != c_uc_w2s_strncmp(pt_rating_info->ws2_rating,
                                     pt_grp->t_last_notify.t_crnt_rating.ws2_rating,
                                     NAV_IPTS_UI_RATING_DESC_LEN))
            {
                pt_grp->t_last_notify.t_crnt_rating = *pt_rating_info;
                e_notify_field |= NAV_IPTS_UI_IF_CRNT_RATING;
            }
        }
    }

    /*play mode*/
    if(_NAV_IPTS_INFO_TUI_PLAY_MODE & e_to_ui)
    {
        e_notify_field |= NAV_IPTS_UI_IF_PLAY_MODE;
    }

    /*input ch number*/
    if(_NAV_IPTS_INFO_TUI_INPUT_CH_NUM_MASK & e_to_ui)
    {
        pt_grp->t_last_notify.b_is_ch_num_inputting = (_NAV_IPTS_INFO_TUI_INPUT_CH_NUM_START & e_to_ui) ? TRUE : FALSE;
        e_notify_field |= NAV_IPTS_UI_IF_INPUT_CH_NUM_STATUS;
    }

    /*delay notify*/
    if(b_delay_notify)
    {
        /*post a message to itself*/
        i4_ret = nav_request_context_switch(_nav_ipts_delay_ui_notify, pt_this, (VOID*)e_grp, (VOID*)e_notify_field);
        NAV_LOG_ON_FAIL(i4_ret);

        return i4_ret;
    }

    /*notify view*/
    if(e_notify_field)
    {
        /*check gui language*/
        ui1_lang_id = nav_get_mlm_lang_id();

        if(ui1_lang_id != pt_grp->t_last_notify.ui1_gui_lang_id)
        {
            pt_grp->t_last_notify.ui1_gui_lang_id = ui1_lang_id;

            e_notify_field |= NAV_IPTS_UI_IF_GUI_LANG;
        }

        pt_this->t_view_handler.pf_data_change(pt_this->pv_view,
                                               e_grp,
                                               e_notify_field,
                                               &pt_grp->t_last_notify);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lookup_tv_isl
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lookup_tv_isl(
    _INPUT_SRC_T*                    pt_this,
    TV_WIN_ID_T                      e_grp,
    ISL_REC_T*                       pt_isl_rec)
{
    INT32                            i4_ret;
    UINT8                            ui1_i;
#ifdef APP_SEPARATE_INP_SRC_FOR_ATV_DTV
    UINT8                            ui1_tuner_brdcst_type = APP_CFG_BRDCST_TYPE_DTV;

    /* Get current TV brdcst type (DTV/ATV) */
    a_cfg_get_tuner_brdcst_type (& ui1_tuner_brdcst_type);
#endif /* APP_SEPARATE_INP_SRC_FOR_ATV_DTV */

    for(ui1_i = 0; ui1_i < pt_this->at_grp[e_grp].t_last_notify.ui1_src_count; ui1_i++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_i, pt_isl_rec);
        NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret);

        /*find tv*/
        if(INP_SRC_TYPE_TV == pt_isl_rec->e_src_type)
        {
        #ifdef APP_SEPARATE_INP_SRC_FOR_ATV_DTV
            if (ui1_tuner_brdcst_type == APP_CFG_BRDCST_TYPE_DTV)
            {
                if (pt_isl_rec->ui4_attr_bits & ISL_ATTR_BIT_TV_DIGITAL)
                {
                    return NAVR_OK;
                }
            }
            else if (ui1_tuner_brdcst_type == APP_CFG_BRDCST_TYPE_ATV)
            {
                if (pt_isl_rec->ui4_attr_bits & ISL_ATTR_BIT_TV_ANALOG)
                {
                    return NAVR_OK;
                }
            }
            continue;
        #else /* APP_SEPARATE_INP_SRC_FOR_ATV_DTV */

            return NAVR_OK;
        #endif
        }
    }

    DBG_ERROR((_ERROR_HEADER"[%s] Fail to find isl rec for tv.\r\n", __FUNCTION__));
    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_is_tshift_svc
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static BOOL _nav_ipts_is_tshift_svc(VOID)
{
    INT32           i4_ret;
    _INPUT_SRC_T*   pt_this = (_INPUT_SRC_T*)&t_g_input_src;
    HANDLE_T        h_svctx = pt_this->at_grp[TV_WIN_ID_MAIN].h_svctx;
    BOOL            b_tshift_svc = FALSE;

    i4_ret = a_tv_is_timeshift_svc(h_svctx, &b_tshift_svc);
    NAV_LOG_ON_FAIL(i4_ret);
    if(i4_ret != TVR_OK)
    {
        b_tshift_svc = FALSE;
    }

    return b_tshift_svc;
}

static VOID _nav_ipts_chg_src_external_nfy(
                                            VOID*                       pv_tv_win_id,
                                            VOID*                       pv_inp_src_id,
                                            VOID*                       pv_unused)
{
    INT32       i4_ret = NAVR_OK;
    i4_ret = nav_change_av_inp_by_id((TV_WIN_ID_T)(UINT32)pv_tv_win_id,
                                     (UINT8)(UINT32)pv_inp_src_id,
                                     NULL);
    NAV_LOG_ON_FAIL(i4_ret);
}

#if 0
static INT32 _nav_ipts_clean_airplay_virtual_input(VOID)
{
    INT32   i4_ret;
    UINT16  ui2_i;
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    CHAR    s_original_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    UINT8   ui1_hide_value = 0;
    UINT8   ui1_original_hide_value = 0;
    SIZE_T  z_size;
    INT32 index = 0;
    i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_original_hide_value, &z_size);
    NAV_LOG_ON_FAIL(i4_ret);

    for(ui2_i = 0; ui2_i < 5; ui2_i++)//Find del id
    {
        i4_ret = a_cfg_get_vtrl_name(ui2_i, s_original_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);
        DBG_LOG_PRINT(("<VTRL INPUT> s_original_inp_name:%s  \n",s_original_inp_name));
        if(c_strcmp("airplay", s_original_inp_name) == 0)
        {
            i4_ret = a_cfg_set_vtrl_name(ui2_i, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_set_name_display(1,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_set_name_display(2,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_set_name_display(3,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);
            c_strncpy(input_src_vtrl_input_list[ui2_i].s_cname,"",APP_CFG_CUSTOM_INP_NAME_LEN);
            input_src_vtrl_input_list[ui2_i].b_hideable = 0;
            ui1_hide_value |= ((UINT8)1 << ui2_i );
            break;
        }



    }
    for(index = 0;index<5;index++)
    {
        DBG_LOG_PRINT(("<VTRL INPUT> line: %d  %s orignal(%s) hide:%d \n", __LINE__, __FUNCTION__, input_src_vtrl_source_info[index].s_cname,input_src_vtrl_source_info[index].ui1_hide));
    }
    DBG_LOG_PRINT(("<VTRL INPUT> file: %s line: %d  %s set_hide vtrl(%d)\n", __FILE__, __LINE__, __FUNCTION__, ui1_hide_value));

    i4_ret = acfg_set(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, 1);

    NAV_LOG_ON_FAIL(i4_ret);


    return i4_ret;
}
#endif

INT32 a_nav_ipts_create_virtual_input(TYPE_APP_VTRL_INPUT* pt_vtrl_input)
{
    INT32   i4_ret;
    UINT16  ui2_i;
    UINT16  ui2_set_id;
    CHAR    s_old_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    CHAR    s_inp_dsp_name[3][APP_CFG_CUSTOM_INP_NAME_LEN] ={{0},{0},{0}};
    UINT8   ui1_hide_value = 0;
    UINT8   ui1_hide_value_tmp_1 = 0;
    UINT8   ui1_hide_value_tmp_2 = 0;
    SIZE_T  z_size = 0;
    UINT8   pt_values[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    UINT32  ui4_len = 0;
    UINT8   ui1_new_vtrl_hide = 0;
    UINT8   ui1_src_num = 0;
//    UINT8           ui1_index = 0;
//    ISL_REC_T       t_isl_rec;

    a_isl_get_num_rec(&ui1_src_num);
    DBG_INFO(("<VTRL INPUT>[%s][%d] input:%s \n", __FUNCTION__, __LINE__, pt_vtrl_input->s_cname));

    if(!b_input_list_init)
    {
        DBG_ERROR(("<VTRL INPUT> input list is not init, need wait init done \n"));
        return NAVR_NOT_ALLOW;
    }

    if(c_strcmp("airplay", pt_vtrl_input->s_cname) == 0)
    {
        if(!a_rest_app_check_install_airplay())
        {
        //    _nav_ipts_clean_airplay_virtual_input();
             return NAVR_OK;
        }
        {
            UINT8 airplay_status = 0;
            SIZE_T  z_size;

            acfg_get(IDX_CUSTOM_AIRPLAY_STATE_CTRL, &airplay_status, &z_size);
            DBG_INFO(("<rest> create_virtual_input airplay was set status=%d\n\r", airplay_status));

            if(airplay_status == 1)
            {
                /*52338287*/
                return NAVR_NOT_IMPLEMENT;
            }
        }

    }

    DBG_INFO(("<VTRL INPUT>[%s][%d] name:{%s}\n", __FUNCTION__, __LINE__, pt_vtrl_input->s_cname));

    for(ui2_i=0;ui2_i<5;ui2_i++)//find id
    {
        /*find pt_vtrl_input->s_position_after*/
        i4_ret = a_cfg_get_vtrl_name(ui2_i, s_old_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);
        if(c_strcmp(input_src_vtrl_source_info[ui2_i].s_cname, pt_vtrl_input->s_cname) == 0)
        {
            ui1_new_vtrl_hide = input_src_vtrl_source_info[ui2_i].ui1_hide ;
        }
        if(c_strcmp(s_old_inp_name, pt_vtrl_input->s_position_after) == 0)
        {
            break;
        }
    }
    DBG_INFO(("<VTRL INPUT>[%s][%d] ui1_new_vtrl_hide: %d \n", __FUNCTION__, __LINE__, ui1_new_vtrl_hide));

    if(ui2_i < 5)
    {
        ui2_set_id = ui2_i + 1;// 1,2,3,4,5
    }
    else
    {
        ui2_set_id = 0;//0
    }

    if(ui2_set_id == 5)
    {
        DBG_ERROR(("\n<VTRL INPUT> Virtual input full, please delete first!\n"));
        return NAVR_FAIL;
    }
    DBG_INFO(("<VTRL INPUT>[%s][%d] ui2_set_id: %d\n", __FUNCTION__, __LINE__, ui2_set_id));

    for(ui2_i=1; ui2_i<5-ui2_set_id;ui2_i++)
    {
        /*Set cname old*/
        i4_ret = a_cfg_get_vtrl_name(5-ui2_i, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        if(c_strlen(s_inp_name) != 0)
        {
            DBG_INFO(("<VTRL INPUT>[%s][%d] ui2_i:%d, set cname:{%s} \n", __FUNCTION__, __LINE__, ui2_i, s_inp_name));
            i4_ret = a_cfg_set_vtrl_name(5-ui2_i + 1, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);
        }
        /*Set display name old*/
        i4_ret = a_cfg_get_name_display(1,4 -  ui2_i,s_inp_dsp_name[0],APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        if(c_strlen(s_inp_dsp_name[0]) != 0)
        {
            DBG_INFO(("<VTRL INPUT>[%s][%d] ui2_i:%d, set ENG name:{%s} \n", __FUNCTION__, __LINE__, ui2_i, s_inp_dsp_name[0]));
            i4_ret = a_cfg_set_name_display(1,5 -  ui2_i + 1,s_inp_dsp_name[0],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);
        }

        i4_ret = a_cfg_get_name_display(2,4 -  ui2_i ,s_inp_dsp_name[1],APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        if(c_strlen(s_inp_dsp_name[1]) != 0)
        {
            DBG_INFO(("<VTRL INPUT>[%s][%d] ui2_i:%d, set FR name:{%s} \n", __FUNCTION__, __LINE__, ui2_i, s_inp_dsp_name[1]));
            i4_ret = a_cfg_set_name_display(2,5 -  ui2_i + 1,s_inp_dsp_name[1],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);
        }

        i4_ret = a_cfg_get_name_display(3,4 -  ui2_i ,s_inp_dsp_name[2],APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);
        if(c_strlen(s_inp_dsp_name[2]) != 0)
        {
            DBG_INFO(("<VTRL INPUT>[%s][%d] ui2_i: %d, set spa name:{%s} \n", __FUNCTION__, __LINE__, ui2_i, s_inp_dsp_name[2]));
            i4_ret = a_cfg_set_name_display(3,5 -  ui2_i + 1,s_inp_dsp_name[2],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);
        }
    }

    /* set hideable old*/
    i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);
    NAV_LOG_ON_FAIL(i4_ret);

    ui1_hide_value_tmp_1 = ui1_hide_value >> (ui2_set_id);/*upper  bits */
    DBG_INFO(("[%s][%d] ui1_hide_value_tmp_1: %x \r\n", __FUNCTION__, __LINE__, ui1_hide_value_tmp_1));
    ui1_hide_value_tmp_2 = ui1_hide_value & (UINT8)(pow(2,ui2_set_id)-1);/*below bits */

    DBG_INFO(("[%s][%d] ui1_hide_value_tmp_2: %x \r\n",__FUNCTION__, __LINE__,ui1_hide_value_tmp_2));

    ui1_hide_value = ((ui1_hide_value_tmp_1 << (ui2_set_id + 1))| ui1_hide_value_tmp_2) & 0x1F;
    DBG_INFO(("<VTRL INPUT>[%s][%d] set old hide vtrl: %d\n", __FUNCTION__, __LINE__, ui1_hide_value));

    i4_ret = acfg_set(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, 1);
    NAV_LOG_ON_FAIL(i4_ret);

    /*Set cname*/
    DBG_INFO(("<VTRL INPUT>[%s][%d] set s_cname:{%s} \n", __FUNCTION__, __LINE__,pt_vtrl_input->s_cname));
    i4_ret = a_cfg_set_vtrl_name(ui2_set_id, pt_vtrl_input->s_cname, APP_CFG_CUSTOM_INP_NAME_LEN);
    NAV_LOG_ON_FAIL(i4_ret);

    /*Set display name*/
    DBG_INFO(("<VTRL INPUT>[%s][%d] set ENG name:{%s} \n", __FUNCTION__, __LINE__, pt_vtrl_input->s_name_en[0]));

    ui4_len = c_strlen(pt_vtrl_input->s_name_en[0]);
    if (ui4_len >= APP_CFG_CUSTOM_INP_NAME_LEN)
    {
        DBG_ERROR(("<VTRL INPUT>[%s][%d] set ENG name too long! fail\n", __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    c_strncpy(input_src_vtrl_input_list[ui2_set_id].s_cname,pt_vtrl_input->s_name_en[0],APP_CFG_CUSTOM_INP_NAME_LEN);
    input_src_vtrl_input_list[ui2_set_id].b_hideable = pt_vtrl_input->b_hideable;
    for (ui2_i = 0;ui2_i <= ui4_len; ui2_i ++ )
    {
        pt_values[ui2_i] = pt_vtrl_input->s_name_en[0][ui2_i];
    }
    DBG_INFO(("<VTRL INPUT>[%s][%d] pt_values:{%s} \n", __FUNCTION__, __LINE__,pt_values));
    i4_ret = a_cfg_set_name_display(1,ui2_set_id,(VOID*)pt_vtrl_input->s_name_en[0],APP_CFG_CUSTOM_INP_NAME_LEN);
    NAV_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("<VTRL INPUT>[%s][%d] set FR name:{%s} \n", __FUNCTION__, __LINE__, pt_vtrl_input->s_name_en[1]));
    i4_ret = a_cfg_set_name_display(2,ui2_set_id,(VOID*)pt_vtrl_input->s_name_en[1],APP_CFG_CUSTOM_INP_NAME_LEN);
    NAV_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("<VTRL INPUT>[%s][%d] set SPA name:{%s} \n", __FUNCTION__,  __LINE__, pt_vtrl_input->s_name_en[2]));
    i4_ret = a_cfg_set_name_display(3,ui2_set_id,(VOID*)pt_vtrl_input->s_name_en[2],APP_CFG_CUSTOM_INP_NAME_LEN);
    NAV_LOG_ON_FAIL(i4_ret);

    /* set hideable */
    i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);
    NAV_LOG_ON_FAIL(i4_ret);

    if(pt_vtrl_input->b_hideable== 1)
    {
        /* to do*/
    }
    else if(pt_vtrl_input->b_hideable == 0)
    {
        /* to do*/
    }

    if(ui1_new_vtrl_hide == 0)
    {
        ui1_hide_value &= ~((UINT8)1 << ui2_set_id);
    }
    else
    {
        ui1_hide_value |=  ((UINT8)1 << ui2_set_id);
    }

    DBG_INFO(("<VTRL INPUT>[%s][%d] set_hide vtrl: %d \n", __FUNCTION__, __LINE__, ui1_hide_value));

    i4_ret = acfg_set(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, 1);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_isl_store_vtrl_input_cname();
    NAV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 a_nav_ipts_delete_virtual_input(CHAR* s_cname)
{
    INT32   i4_ret;
    UINT16  ui2_i;
    UINT16  ui2_del_id;
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1] = {0};
    UINT8   ui1_hide_value = 0;
    UINT8   ui1_hide_value_tmp_1 = 0;
    UINT8   ui1_hide_value_tmp_2 = 0;
    SIZE_T  z_size;
    CHAR    s_inp_dsp_name[3][APP_CFG_CUSTOM_INP_NAME_LEN] = {{0},{0},{0}};

    for(ui2_i=0;ui2_i<5;ui2_i++)//Find del id
    {
        i4_ret = a_cfg_get_vtrl_name(ui2_i, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        DBG_INFO(("<VTRL INPUT>[%s][%d] ui2_i:%d, s_inp_name:{%s}, s_cname:{%s} \n",
                    __FUNCTION__, __LINE__, ui2_i, s_inp_name, s_cname));

        if(c_strcmp(s_inp_name, s_cname) == 0)
        {
            break;
        }
    }
    ui2_del_id = ui2_i;

    DBG_INFO(("<VTRL INPUT>[%s][%d] ui2_del_id: %d \n", __FUNCTION__, __LINE__, ui2_del_id));
    if(ui2_del_id >= 5)
    {
        DBG_ERROR(("<VTRL INPUT>[%s][%d] cannot find del cname (%d) \n", __FUNCTION__, __LINE__, ui2_del_id));
    }
    else if(ui2_del_id < 4)//not the last one
    {
        for(ui2_i=0; ui2_i<(4-ui2_del_id); ui2_i++)//move reserved input which after del id forward
        {
            i4_ret = a_cfg_get_vtrl_name(ui2_del_id + ui2_i + 1, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_set_vtrl_name(ui2_del_id + ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_get_name_display(1,ui2_del_id + ui2_i + 1,s_inp_dsp_name[0],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            a_cfg_set_name_display(1,ui2_del_id + ui2_i,s_inp_dsp_name[0],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_get_name_display(2,ui2_del_id + ui2_i + 1,s_inp_dsp_name[1],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_set_name_display(2,ui2_del_id + ui2_i,s_inp_dsp_name[1],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_get_name_display(3,ui2_del_id + ui2_i + 1,s_inp_dsp_name[2],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);

            i4_ret = a_cfg_set_name_display(3,ui2_del_id + ui2_i,s_inp_dsp_name[2],APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_LOG_ON_FAIL(i4_ret);
        }
    }
    /*Clean the last virtual input*/
    c_memset(s_inp_name, 0, sizeof(s_inp_name));

    //i4_ret = acfg_set(IDX_IPTS_VTRL_NAME_5, "\0", APP_CFG_CUSTOM_INP_NAME_LEN);

    i4_ret = a_cfg_set_vtrl_name(5 - 1, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN - 1);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_set_name_display(1,5 - 1,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN - 1);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_set_name_display(2,5 - 1,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN - 1);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_set_name_display(3,5 - 1,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN - 1);
    NAV_LOG_ON_FAIL(i4_ret);

    /* set new hideable */
    i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, &z_size);
    NAV_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("<VTRL INPUT>[%s][%d] get_hide: %d \n", __FUNCTION__, __LINE__, ui1_hide_value));

    ui1_hide_value_tmp_1 = ui1_hide_value >> (ui2_del_id + 1);//previous upper  bits
    DBG_INFO(("<VTRL INPUT>[%s][%d] ui1_hide_value_tmp_1: %d \n", __FUNCTION__, __LINE__, ui1_hide_value_tmp_1));

    ui1_hide_value_tmp_2 = ui1_hide_value & (UINT8)(pow(2, ui2_del_id)-1);//previous below bits
    DBG_INFO(("<VTRL INPUT>[%s][%d] ui1_hide_value_tmp_2: %d \n", __FUNCTION__, __LINE__, ui1_hide_value_tmp_2));

    ui1_hide_value = (ui1_hide_value_tmp_1 << ui2_del_id)&(ui1_hide_value_tmp_2)&0x1F;
    DBG_INFO(("<VTRL INPUT>[%s][%d] ui1_hide_value: %d \n", __FUNCTION__, __LINE__, ui1_hide_value));

    ui1_hide_value |= ((UINT8)1 << 4 );//set the last input to hide

    DBG_INFO(("<VTRL INPUT>[%s][%d] set_hide vtrl: %d \n", __FUNCTION__, __LINE__, ui1_hide_value));

    i4_ret = acfg_set(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, 1);
    NAV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 a_nav_ipts_clean_virtual_input(VOID)
{
    INT32   i4_ret;
    UINT16  ui2_i;
    CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    CHAR    s_original_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    UINT8   ui1_hide_value = 0;
    UINT8   ui1_original_hide_value = 0;
    SIZE_T  z_size;
    INT32 index = 0;

    i4_ret = acfg_get(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_original_hide_value, &z_size);
    NAV_LOG_ON_FAIL(i4_ret);

    for(ui2_i = 0; ui2_i < 5; ui2_i++)//Find del id
    {
        i4_ret = a_cfg_get_vtrl_name(ui2_i, s_original_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);
        c_strncpy(input_src_vtrl_source_info[ui2_i].s_cname,s_original_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        input_src_vtrl_source_info[ui2_i].ui1_hide = (ui1_original_hide_value>>ui2_i)&(0x01);
        i4_ret = a_cfg_set_vtrl_name(ui2_i, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_set_name_display(1,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_set_name_display(2,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_set_name_display(3,ui2_i,s_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
        NAV_LOG_ON_FAIL(i4_ret);
        c_strncpy(input_src_vtrl_input_list[ui2_i].s_cname,"",APP_CFG_CUSTOM_INP_NAME_LEN);
        input_src_vtrl_input_list[ui2_i].b_hideable = 0;

        ui1_hide_value |= ((UINT8)1 << ui2_i );
    }

    for(index = 0;index<5;index++)
    {
        DBG_INFO(("<VTRL INPUT>[%s][%d] orignal:{(%s}, hide:%d \n", __FUNCTION__, __LINE__, input_src_vtrl_source_info[index].s_cname,input_src_vtrl_source_info[index].ui1_hide));
    }
    DBG_INFO(("<VTRL INPUT>[%s][%d] set_hide vtrl: %d \n", __FUNCTION__, __LINE__, ui1_hide_value));

    i4_ret = acfg_set(IDX_IPTS_VTRL_HIDE_MANUAL, &ui1_hide_value, 1);

    NAV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _nav_ipts_select_virtual_input(const CHAR* s_cname)
{
    INT32           i4_ret;
    ISL_REC_T       t_isl_rec;
    BOOL            b_found = FALSE;
    _INPUT_SRC_T  * pt_this = &t_g_input_src;
    TV_WIN_ID_T     e_focus_id;
    BOOL            b_need_stop_svc = TRUE;
    BOOL            b_need_stop_mmp = FALSE;

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
    a_isl_get_rec_by_idx(pt_this->at_grp[e_focus_id].t_last_notify.t_crnt_input.t_input_src.ui1_id,&t_isl_rec);
    DBG_LOG_PRINT(("[%s][%d] ID: %d, e_video_type: 0x%x, source_id: %d\n", __FUNCTION__, __LINE__, t_isl_rec.ui1_id, t_isl_rec.t_avc_info.e_video_type,t_isl_rec.ui1_id));

    if((t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)||(!nav_is_running(e_focus_id)))
    {
        b_need_stop_svc = FALSE;
    }

    if(c_strncmp(s_cname,"SMARTCAST",9) == 0 )
    {
        b_need_stop_svc = TRUE;
    }

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST)
    {
        b_need_stop_mmp = TRUE;
    }

    /* get virtual input by name */
    {
        UINT8           ui1_src_count = 0;
        UINT8           ui1_idx = 0;

        i4_ret = a_isl_get_num_rec(&ui1_src_count);
        NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret);

        if( 0 == ui1_src_count )
        {
            return NAVR_NOT_EXIST;
        }

        for (ui1_idx = 0; ui1_idx < ui1_src_count; ui1_idx++)
        {
            c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));

            i4_ret = a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
            NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret);

            /* find casttv source */
            if(a_nav_ipts_is_cast_source(&t_isl_rec) == FALSE)
            {
                continue;
            }

            if(c_strncmp(s_cname,"SMARTCAST",9) == 0 || c_strcmp(s_cname,t_isl_rec.s_src_name) == 0 )
            {
                b_found = TRUE;
                break;
            }
        }
    }

    if( b_found == FALSE )
    {
        return NAVR_NOT_EXIST;
    }

    if(b_need_stop_svc)
    {
        i4_ret = a_tv_stop_by_win_id(e_focus_id);
        NAV_LOG_ON_FAIL(i4_ret);
    }

    if(b_need_stop_mmp)
    {
        a_amb_pause_app(MMP_NAME);
    }

    /*debug*/
    {
        UTF16_T*     w2s_name;
        CHAR         ac_alias_debug[APP_CFG_CUSTOM_INP_NAME_LEN + 1];

        w2s_name = a_isl_get_display_name(&t_isl_rec);
        c_uc_w2s_to_ps(w2s_name, ac_alias_debug, APP_CFG_CUSTOM_INP_NAME_LEN);

        DBG_LOG_PRINT(("<INPUT SRC>[%s][%d] ui1_id:%d, s_src_name:{%s} \n", __FUNCTION__, __LINE__, t_isl_rec.ui1_id, ac_alias_debug));
    }

    {
       CHAR            s_disp_name[16+1] = {0};

       //DBG_LOG_PRINT(("<INPUT_SRC>[%s][%d] call a_cfg_av_get_disp_name()\n", __FUNCTION__, _LINE__));
       i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
       NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

       i4_ret =  a_cfg_av_set_input_src(s_disp_name, t_isl_rec.ui1_id);
       NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);
    }

    {
        i4_ret = _nav_ipts_update_info(pt_this, e_focus_id, _NAV_IPTS_INFO_TUI_SRC_UPDATE, &t_isl_rec, FALSE);
        NAV_CHK_FAIL(i4_ret);
    }

    return NAVR_OK;
}

INT32 a_nav_ipts_select_virtual_input(const CHAR* s_cname)
{
    INT32           i4_ret = NAVR_OK;
    TV_WIN_ID_T     e_tv_win_id;
    ISL_REC_T       t_isl_rec               = {0};
    UTF16_T         w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    char            src_name[128] = {0};

    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec (e_tv_win_id, &t_isl_rec);
    a_isl_get_display_name_ex(&t_isl_rec, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);
    c_uc_w2s_to_ps(w2s_alias,src_name,sizeof(src_name));
    //DBG_LOG_PRINT(("<INPUT SRC>[%s][%d] name:{%s} \n", __FUNCTION__, __LINE__, src_name));

    if(s_cname == NULL)
    {
        return NAVR_INV_ARG;
    }

    i4_ret = _nav_ipts_select_virtual_input(s_cname);
    NAV_CHK_FAIL(i4_ret);

    if(c_strcmp(s_cname,src_name))
    {
        //DBG_LOG_PRINT(("<INPUT SRC>[%s][%d] clean av items \n", __FUNCTION__, __LINE__));
        nav_show_banner_input_source_msg_hdlr();
    }

    //start mm querry timer if need
    banner_view_mm_update_start_timer();

    return NAVR_OK;
}

INT32 a_nav_ipts_get_crnt_isl_id(UINT8*  pui1_input_src)
{
    INT32       i4_ret = NAVR_OK;
    CHAR        s_disp_name[16+1];

    if(pui1_input_src == NULL)
    {
        return NAVR_INV_ARG;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

    i4_ret = a_cfg_av_get_input_src(s_disp_name, pui1_input_src);
    NAV_CHK_FAIL(APP_CFGR_OK == i4_ret ? NAVR_OK : i4_ret);

    return NAVR_OK;
}

INT32 a_nav_ipts_get_crnt_isl_rec(ISL_REC_T* pt_isl_rec)
{
    INT32       i4_ret = NAVR_OK;
    UINT8       ui1_crnt_input_src  = 0;

    if(pt_isl_rec == NULL)
    {
        return NAVR_INV_ARG;
    }

    i4_ret = a_nav_ipts_get_crnt_isl_id(&ui1_crnt_input_src);
    NAV_CHK_FAIL(i4_ret );

    i4_ret = a_isl_get_rec_by_id(ui1_crnt_input_src,pt_isl_rec);
    NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);

    return NAVR_OK;
}

BOOL a_nav_ipts_is_usb_source(ISL_REC_T* pt_isl_rec)
{
    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }

    if(INP_SRC_TYPE_VTRL  != pt_isl_rec->e_src_type)
    {
        return FALSE;
    }
    if(pt_isl_rec->t_avc_info.e_video_type != DEV_VTRL_MMP)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL a_nav_ipts_is_tv_source(ISL_REC_T* pt_isl_rec)
{
    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }

    if(INP_SRC_TYPE_TV != pt_isl_rec->e_src_type)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL a_nav_ipts_is_cast_source(ISL_REC_T* pt_isl_rec)
{
    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }
    if( pt_isl_rec->e_src_type != INP_SRC_TYPE_VTRL )
    {
        return FALSE;
    }
    if(pt_isl_rec->t_avc_info.e_video_type != DEV_VTRL_CAST)
    {
        return FALSE;
    }
    if(pt_isl_rec->ui1_internal_id < 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL a_nav_ipts_is_hdmi_source(ISL_REC_T* pt_isl_rec)
{
    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }
    if( INP_SRC_TYPE_AV != pt_isl_rec->e_src_type )
    {
        return FALSE;
    }
    if( DEV_AVC_HDMI != pt_isl_rec->t_avc_info.e_video_type )
    {
        return FALSE;
    }
    return TRUE;
}

BOOL a_nav_ipts_is_div_source(ISL_REC_T* pt_isl_rec)
{
    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }
    if( INP_SRC_TYPE_AV != pt_isl_rec->e_src_type )
    {
        return FALSE;
    }
    if( DEV_AVC_DVI != pt_isl_rec->t_avc_info.e_video_type )
    {
        return FALSE;
    }
    return TRUE;
}


BOOL a_nav_ipts_is_comp_source(ISL_REC_T* pt_isl_rec)
{
    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }
    if( INP_SRC_TYPE_AV != pt_isl_rec->e_src_type )
    {
        return FALSE;
    }

    if( DEV_AVC_COMBI == pt_isl_rec->t_avc_info.e_video_type \
        ||  DEV_AVC_COMP_VIDEO == pt_isl_rec->t_avc_info.e_video_type\
        ||  DEV_AVC_Y_PB_PR == pt_isl_rec->t_avc_info.e_video_type )
    {
        return TRUE;
    }

    return FALSE;
}
BOOL a_nav_ipts_is_vga_source(ISL_REC_T* pt_isl_rec)
{
    if(pt_isl_rec == NULL)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return FALSE;
    }
    if( INP_SRC_TYPE_AV != pt_isl_rec->e_src_type )
    {
        return FALSE;
    }

    if( DEV_AVC_VGA != pt_isl_rec->t_avc_info.e_video_type  )
    {
        return FALSE;
    }

    return TRUE;
}



BOOL a_nav_ipts_crnt_input_is_cast_source(VOID)
{
    INT32       i4_ret              = 0;
    ISL_REC_T   t_isl_rec           = {0};

    i4_ret = a_nav_ipts_get_crnt_isl_rec(&t_isl_rec);
    NAV_CHK_FAIL(i4_ret);

    DBG_INFO(("<INPUT SRC>[%s][%d] e_video_type: %d, (DEV_VTRL_CAST=%d) \n", __FUNCTION__, __LINE__, t_isl_rec.t_avc_info.e_video_type, DEV_VTRL_CAST));

    return a_nav_ipts_is_cast_source(&t_isl_rec);
}

BOOL a_nav_ipts_vtrl_input_hideable(CHAR* s_cname)
{
    UINT8 ui1_index = 0;

    DBG_INFO(("[%s][%d] s_cname:{%s} \n", __FUNCTION__, __LINE__, s_cname));

    if(s_cname == NULL)
    {
        return FALSE;
    }

    for (ui1_index = 0;ui1_index<5;ui1_index++)
    {
        DBG_INFO(("[%s][%d] s_cname:{%s}, b_hideable:%d \n", __FUNCTION__,__LINE__,\
        input_src_vtrl_input_list[ui1_index].s_cname, input_src_vtrl_input_list[ui1_index].b_hideable));

        if (c_strncmp(input_src_vtrl_input_list[ui1_index].s_cname,s_cname,9) == 0)
            return input_src_vtrl_input_list[ui1_index].b_hideable;
    }

    return FALSE;
}

BOOL a_nav_ipts_is_show(VOID)
{
    return FALSE;
}

//add for get current hdmi idx
INT32 a_nav_ipts_get_hdmi_comp_idx(VOID)
{
    FILE    *fp;
    UINT8   hdmi_idx = 0;
    CHAR    buf[250] = {0};
    CHAR    *p_buf = NULL, *p_tmp = NULL;
    ISL_REC_T       t_isl_rec = {0};
    SIZE_T  rlen;


    a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    if(a_nav_ipts_is_hdmi_source(&t_isl_rec) != TRUE)
    {
        DBG_LOG_PRINT(("[hongzhao]%s_%d current source is not HDMI\r\n\n",__FUNCTION__,__LINE__));
        return -1;
    }

    fp = fopen("/config/hdmi_map.ini","r");
    if(fp == NULL)
    {
        DBG_LOG_PRINT(("[hongzhao]open /config/hdmi_map.ini error\r\n"));
        return -2;
    }
    rlen = fread(buf,0x1,sizeof(buf),fp);
    fclose(fp);
    if (rlen < 0) {
        DBG_LOG_PRINT(("%s(%d) fread failed with %d \r\n", __func__, __LINE__, errno));
        return -2;
    }
    buf[rlen] = '\0';

    p_buf = buf;
    for(hdmi_idx = 0; hdmi_idx < t_isl_rec.ui1_internal_id+2; hdmi_idx++)
    {
        p_tmp = strstr(p_buf,"=");
        if(p_tmp == NULL)
        {
            DBG_LOG_PRINT(("[hongzhao] HDMI port count error\r\n"));
            return -2;
        }
        p_buf = p_tmp + 1;
    }

    hdmi_idx = atoi(p_tmp+2) - 1;
    if(hdmi_idx > 3)
    {
        DBG_LOG_PRINT(("[hongzhao] hdmi_map.ini error\r\n"));
        return -2;
    }

    DBG_INFO(("[hongzhao]%s_%d get comp idx is %d\r\n",__FUNCTION__,__LINE__,hdmi_idx));

    DBG_LOG_PRINT(("[INPUT_SRC][HDMI]{%s:%d} => hdmi_idx:%d\n",
        __FUNCTION__, __LINE__, hdmi_idx ));

    return hdmi_idx;
}

INT32 a_nav_ipts_set_cec_name (UINT8 ui1_cec_idx, S_HDMI_NAME_T* s_cec_name)
{
    FILE    *fp;
    CHAR    hdmi_cec_name_file[32] = {0};

    c_sprintf(hdmi_cec_name_file, "/data/hdmi%d_cec_name", ui1_cec_idx);
    DBG_LOG_PRINT(("[hongzhao] a_nav_ipts_set_cec_name hdmi_cec_name_file: %s, s_cec_name %s\r\n",hdmi_cec_name_file,s_cec_name->cec_name));

    fp = fopen(hdmi_cec_name_file,"w+");
    if(fp == NULL)
    {
        DBG_ERROR(("[hongzhao]create file %s error\r\n",hdmi_cec_name_file));
        return FALSE;
    }

    fwrite(s_cec_name,sizeof(S_HDMI_NAME_T),1,fp);
    fclose(fp);

    return TRUE;
}

INT32 a_nav_ipts_get_cec_name (UINT8 ui1_cec_idx, S_HDMI_NAME_T* s_cec_name)
{
    FILE    *fp;
    CHAR    hdmi_cec_name_file[32] = {0};

    if(s_cec_name == NULL)
    {
        DBG_ERROR(("[hongzhao] a_nav_ipts_get_cec_name, s_cec_name is NULL\r\n"));
        return FALSE;
    }

    c_sprintf(hdmi_cec_name_file, "/data/hdmi%d_cec_name", ui1_cec_idx);
    fp = fopen(hdmi_cec_name_file,"r");
    if(fp == NULL)
    {
        DBG_ERROR(("[hongzhao]open file %s error\r\n",hdmi_cec_name_file));
        return FALSE;
    }

    fread(s_cec_name,sizeof(S_HDMI_NAME_T),1,fp);
    fclose(fp);

    return TRUE;
}

//get total hdmi ports
INT32 a_nav_ipts_get_hdmi_ports(VOID)
{
    FILE    *fp;
    INT32   hdmiports = 0;

    fp = popen("grep \"count\" /config/hdmi_map.ini | awk -F ' ' '{print $3}'","r");
    if(fp == NULL)
    {
        DBG_ERROR(("[%s %d]open /config/hdmi_map.ini error\r\n",__FUNCTION__,__LINE__));
        return 0;
    }

    if((hdmiports = fgetc(fp)) == EOF)
    {
        DBG_ERROR(("[%s %d]read popen /config/hdmi_map.ini error\r\n",__FUNCTION__,__LINE__));
        pclose(fp);
        return -1;
    }
    pclose(fp);

    return hdmiports - 48;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ipts_enable_this_log
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL ipts_enable_this_log (
    UINT16                      ui2_log_type
    )
{
    _INPUT_SRC_T*           pt_this = &t_g_input_src;
    return ((ui2_log_type & pt_this->i2_g_log_type) == ui2_log_type) ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      ipts_get_log_type
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT16 ipts_get_log_type (VOID)
{
    _INPUT_SRC_T*           pt_this = &t_g_input_src;

    return pt_this->i2_g_log_type ;
}
/*-----------------------------------------------------------------------------
 * Name
 *      ipts_set_log_type
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID ipts_set_log_type (
    UINT16                              ui2_log_type
    )
{
    _INPUT_SRC_T*           pt_this = &t_g_input_src;

    pt_this->i2_g_log_type = ui2_log_type ;
}

UINT16 nav_get_input_src_dbg_level(VOID)
{

    return ui2_g_src_dbg_level;
}

VOID nav_set_input_src_dbg_level(
                    UINT16                      ui2_db_level
                    )
{
    ui2_g_src_dbg_level = ui2_db_level;
}

#endif /*APP_537X_SUPPORT*/

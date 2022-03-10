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
 * $RCSfile: nav_variant.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 7793009dbc122937a0001b34eec5772f $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_device_type.h"
#include "u_gl_nc.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_handle.h"

#include "am/a_am.h"
#include "wizard2/a_wzd.h"

#include "app_util/a_icl.h"

#include "nav/navigator.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_variant_custom.h"
#include "res/nav/nav_view.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "nav/banner2/a_banner.h"
#include "nav/banner2/banner_common.h"
#include "nav/ch_lst/a_ch_lst.h"
#include "nav/video_sel/a_video_sel.h"
#include "nav/audio_info/a_audio_info.h"
#include "nav/pwd_dlg/a_pwd_dlg.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "nav/vol_ctrl/a_vol_ctrl.h"
#include "nav/screen_mode/a_screen_mode.h"
#include "nav/burning_mode/a_burning_mode.h"
#include "nav/zoom_pan/a_zoom_pan.h"
#include "nav/input_src/a_input_src.h"
#include "nav/sleep/a_sleep.h"
#include "nav/nav_common.h"
#include "res/nav/one_channel_list/ocl.h"
#include "nav/tuner_setup/tuner_setup_view.h"

#include "nav/ch_select/ch_select.h"
#include "nav/ch_select/ch_select_view.h"


#ifdef APP_USB_INSTALL_ULPK_SUPPORT
#include "nav/ulpk/a_ulpk.h"
#endif

#ifdef APP_WR_UPDATER_UI_SUPPORT
#include "nav/wr_updater/a_wr_updater.h"
#include "nav/updater/nav_updater.h"
#endif

#include "nav/pop/a_pop.h"
#include "nav/pic_mode/a_pic_mode.h"
#include "nav/sound_effect/a_sound_effect.h"
#include "nav/freeze/a_nav_frz.h"
#include "nav/power/a_nav_power.h"
#include "nav/clock/a_clock.h"
#include "nav/viewport/a_nav_viewport.h"

#ifdef APP_NAV_CAMERA_PLUG_SUPPORT
#include "nav/camera_plug/a_nav_camera_plug.h"
#endif

#ifdef APP_TTX_SUPPORT
#include "nav/teletext/a_nav_teletext.h"
#endif

#ifdef APP_DCR_SUPPORT
#include "nav/dcr/a_nav_dcr.h"
#endif

#ifndef APP_DVBT_SUPPORT
#include "nav/cc_info/a_cc_info.h"
#else
#include "nav/subtitle_info/a_subtitle_info.h"
#endif

#ifdef APP_NAV_SCART_MONITOR
#include "nav/scart_monitor/a_scart_monitor.h"
#endif

#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#endif

#include "nav/link_mode/link_mode.h"
#ifdef APP_NAV_MISC_COMP
#include "nav/misc/a_nav_misc.h"
#endif
#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
#include "c_fe.h"
#include "fonts/fontdata.h"
#endif

#ifdef APP_NAV_SINGLE_RF_SCAN
#include "nav/single_scan/a_single_scan.h"
#endif

#ifdef APP_CEC_SUPPORT
#include "nav/cec2/a_nav_cec.h"
#endif /* APP_NAV_CEC_SUPPORT */

#ifdef APP_USE_BDF_FONT
#include "res/fonts/a_font_tiresias.h"
#endif

#ifdef APP_UPG_SUPPORT
#ifndef LINUX_TURNKEY_SOLUTION
#include "nav/upgrade/a_nav_upg.h"
#else
#include "nav/updater/a_nav_updater.h"
#endif
#endif

#ifdef APP_NAV_FLICKER_SUPPORT
#include "nav/flicker_pattern/a_nav_flicker.h"
#endif

#include "nav/usb_oc/a_nav_usb_oc.h"

#ifdef APP_NAV_REC_SUPPORT
#include "nav/record/a_nav_rec.h"
#endif

#ifdef APP_NAV_AUD_ONLY_SUPPORT
#include "nav/aud_only/a_aud_only.h"
#endif

#ifdef APP_NAV_MMP_LAUNCHER_SUPPORT
#include "nav/mmp_launcher/a_nav_mmlr.h"
#endif

#ifdef APP_NAV_REC_PVR_SCH_SUPPORT
#include "nav/reminder/a_nav_reminder.h"
#endif

#include "nav/sys_info/a_sys_info.h"

#include "nav/info_bar/a_info_bar.h"

#include "nav/usb_pld/a_nav_usb_pld.h"

#include "nav/dialog/a_nav_dialog.h"
#include "nav/3d_setting/a_3d_setting.h"

#ifdef APP_ENTER_FAC_BY_NAV_SECRET_KEY
#include "factory/a_factory.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include "menu2/a_menu.h"
#include "msgconvert/a_msgconvert.h"
#endif

#include "mmp/a_mmp.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "wfd/a_wfd.h"
#include "res/menu2/a_menu_custom.h"
#include "nav/revolt_misc/a_revolt_misc.h"
#include "nav/tuner_setup/a_tuner_setup.h"


#if 1//
#include "nav/input_src/input_src.h"
#endif
#if 1
#include "nav/via_dlg/nav_via_dlg.h"
#endif
#include "nav/scrn_blank/a_nav_scrn_blank.h"

#ifdef APP_NAV_FRZ_SUPPORT
#include "nav/freeze/a_nav_frz.h"
#endif


#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/c4tv_apron.h"
#endif

#ifdef APP_ZOOM_MODE_SUPPORT
#include "nav/zoom/a_nav_zoom.h"
#endif

#include "nav/revolt_info/a_revolt_info.h"
#include "nav/long_press/long_press.h"
#include "res/app_util/config/acfg_custom.h"
#include "app_util/a_icl_common.h"
#include "rest/tv/tv_settings/a_picture_ex.h"
#include "nav/test_pattern/test_pattern.h"

#ifdef TIME_MEASUREMENT
#include "time_msrt/x_time_msrt.h"
#include "time_msrt/u_time_msrt_name.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "res/app_util/config/acfg_cust_factory.h"
#include "nav/pwd_dlg/pwd_dlg.h"
#include "nav/ppp/pic_pw_popup.h"
#include "res/menu2/menu_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define NAV_DEBUG_KEY(x)    //x

#if 1//Cedric
//This file used some .h is not same cTV files
#define PRI_BANNER_STATE_PDCH       (4)//Mapping to BANNER_STATE_PDCH

extern INT32 banner_get_crnt_state(
                    BANNER_STATE_T*             pe_state
                    );
extern VOID banner_custom_set_ch_state (VOID);
#endif

extern VOID a_scrn_blank_act(VOID*                       pv_tag1,
                              VOID*                       pv_tag2,
                              VOID*                       pv_tag3);

typedef struct _DEVICE_DISCARDED_KEY_PAIR_T
{
    DEVICE_TYPE_T       e_video_type;
    UINT32*             pui4_key_codes;
    UINT8               ui1_key_code_size;
} DEVICE_DISCARDED_KEY_PAIR_T;

#ifdef APP_VTRL_INP_SRC_SUPPORT
typedef struct __NAV_RMK_PRV_DATA_T
{
    UINT32                      ui4_keycode;
    NAV_COMP_ID_T               e_handler_id;
} NAV_RMK_PRV_DATA_T;
#endif

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

#ifdef APP_VTRL_INP_SRC_SUPPORT
static VOID * pv_g_rmk_hdlr = NULL;
extern NAV_MODEL_T     t_g_navigator;
#endif

static BOOL     b_disable_panel_key_by_odm = FALSE;
static BOOL     b_resume_for_active_componet = FALSE;
static NAV_COMP_ID_T e_g_comp_id = NAV_COMP_ID_LAST_VALID_ENTRY;
static BOOL     b_up_down_enable = TRUE;
#ifdef LINUX_TURNKEY_SOLUTION
/*
  index 0: Menu
  index 1: MsgConvert
*/
/*coexist table*/
NAV_COEXIST_APP_REC_T at_g_coexist_recs[] =
{
    {
        NAV_COMP_ID_VOL_CTRL,                   /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),                                         /*ap ids*/
        {TRUE}                                   /*coexist*/
    },
    {
        NAV_COMP_ID_SCREEN_MODE,                /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        NAV_COMP_ID_INPUT_SRC,                  /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3),                                          /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        NAV_COMP_ID_SLEEP,                     /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1),    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        NAV_COMP_ID_PICTURE_EFFECT,             /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        NAV_COMP_ID_BANNER,                     /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) ,    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        NAV_COMP_ID_SCREEN_SAVER,               /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3),    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        NAV_COMP_ID_C4TV_APRON,               /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3),    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        /*for default value*/
        NAV_COMP_ID_LAST_VALID_ENTRY,           /*comp id*/
        NAV_COEXIST_EMPYT_APP_ID_BIT_MASK,      /*not used. ap ids*/
        {FALSE}                                 /*coexist*/
    }
};
/*comp resume table*/
NAV_COEXIST_APP_REC_T at_g_comp_recs[] =
{
    {
        NAV_COMP_ID_CH_LIST,                   /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1),    /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_CC_SEL,                  /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),                                          /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_VOL_CTRL,                   /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(2) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4)                                      ,    /*ap ids*/
        {TRUE}                                    /*not resume*/
    },
    {
        NAV_COMP_ID_SCREEN_MODE,                /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),    /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_INPUT_SRC,                  /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),                                          /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_SLEEP,                  /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1),     /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_PICTURE_EFFECT,             /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),    /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_BANNER,                     /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) ,    /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_SCREEN_SAVER,               /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3),    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        NAV_COMP_ID_VIA_DLG,                    /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1),   /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_SCRN_BLANK,                  /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0) | NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1) |
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4),                                          /*ap ids*/
        {TRUE}                                  /*not resume*/
    },
    {
        NAV_COMP_ID_C4TV_APRON,               /*comp id*/
        NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3),    /*ap ids*/
        {TRUE}                                  /*coexist*/
    },
    {
        /*for default value*/
        NAV_COMP_ID_LAST_VALID_ENTRY,           /*comp id*/
        NAV_COEXIST_EMPYT_APP_ID_BIT_MASK,      /*not used. ap ids*/
        {FALSE}                                 /*not resume*/
    }
};
#endif

#ifdef APP_ENTER_FAC_BY_NAV_SECRET_KEY
static UINT32 aui4_fac_menu_key_list[FAC_MENU_KEY_LIST_SIZE] = FAC_MENU_KEY_LIST;
static UINT32 aui4_fac_mode_key_list[FAC_MODE_KEY_LIST_SIZE] = FAC_MODE_KEY_LIST;
#endif

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
 /*-----------------------------------------------------------------------------
 * Name
 *      _nav_get_3d_setting_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_get_3d_setting_mode(VOID)
{
    BOOL        b_3D_support = FALSE;

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        INT32       i4_ret = NAVR_OK;
        i4_ret = a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
        DBG_INFO(("i4_ret = %d\n", i4_ret));
    }
    return b_3D_support;
}

#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: init_custom_fonts
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 *-----------------------------------------------------------------------------*/
static INT32 init_custom_fonts(VOID)
{
    UINT32  ui4_font_size_tiresias          = GET_UINT32_FROM_PTR_BIG_END (&(font_file_default [0]));
    INT32   i4_ret;

    if(!c_fe_has_font(NAV_FONT_SMALL, FE_FNT_STYLE_UNIFORM))
    {
#ifndef APP_USE_BDF_FONT
        i4_ret = c_fe_add_mem_font(NAV_FONT_SMALL,
                                   &(font_file_default [4]),
                                   font_file_default, 22, 26, 32);
#else
        i4_ret = c_fe_add_combine_bmp_mem_font(NAV_FONT_SMALL,
                                   &(font_file_tiresias_bdf_22 [4]),
                                   GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_22 [0])),
                                   &(font_file_tiresias_bdf_26 [4]),
                                   GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_26 [0])),
                                   &(font_file_tiresias_bdf_32 [4]),
                                   GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_32 [0])));

#endif /* APP_USE_BDF_FONT */

        if(FER_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): c_fe_add_mem_font() failed, ret=%d\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}
#endif


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_is_skip_channel
 * Description
 *      is ship channel or not?
 *
 * Input arguments
 *      t_svl_rec    a svl record
 * Output arguments
 *      None
 * Returns
 *      TRUE      Skip channel
 *      FALSE     Not skip channel
 *---------------------------------------------------------------------------*/
static BOOL _nav_is_skip_channel(SVL_REC_T*           pt_svl_rec)
{
    if (pt_svl_rec != NULL && (pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_rcu_channel_key_handler
 * Description
 *      The API is used to handle remote controller key no any UI_COMP want to
 *      handle it
 * Input arguments
 *      ui4_key_code    a remote key code
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK      the routine is successfully
 *      NAVR_FAIL    the routine is failed
 *---------------------------------------------------------------------------*/
static VOID _nav_rcu_channel_key_handler(
                    NAV_MODEL_T*                pt_this,
                    NAV_TV_WIN_T*               pt_tv_win,
                    UINT32                      ui4_key_code
                    )
{
    UINT32    ui4_crnt_channel_id       =  NAV_UTIL_CNFG_GET_CRNT_CHANNEL_ID(pt_tv_win->e_id);
    UINT32    ui4_next_channel_id       = ui4_crnt_channel_id;
     UINT32   ui4_tmp_channel_id        = ui4_crnt_channel_id;
    BOOL      b_is_changed              = FALSE;
    SVL_REC_T           t_svl_rec       = {0};
    OCL_SVL_REC_T       t_ocl_svl_rec   = {0};

    HANDLE_T  h_cable_svl;
    HANDLE_T  h_antenna_svl;
    UINT16    ui2_crnt_svl_id          = ANTENNA_SVL_ID;
    UINT16    ui2_tmp_svl_id           = ui2_crnt_svl_id;

    INT32     i4_ret              = 0;
    ISL_REC_T t_crnt_isl_rec;
    ISL_REC_T t_last_isl_rec;
    TV_MODE_T e_tv_mode           = TV_MODE_TYPE_NORMAL;
    BOOL      b_allow_to_change_channel = TRUE;
    BOOL      b_force_to_change_in_tv_only = FALSE;
    UINT8     ui1_bs_src = 0;

    i4_ret = nav_get_svl_handle_by_id(ANTENNA_SVL_ID, &h_antenna_svl);
    if(NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("<nav variant>get svl handle fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
    }

    i4_ret = nav_get_svl_handle_by_id(CABLE_SVL_ID, &h_cable_svl);
    if(NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("<nav variant>get svl handle fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
    }

#ifdef APP_ISDB_BRA_PRIMARY_SVC_SELECT
    UINT8 ui1_mode = 0;
    i4_ret = a_cfg_get_dig_ch_tuning_mode(&ui1_mode);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("<nav variant>get dig ch tuning mode fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        ui1_mode = APP_CFG_DIG_CH_TUNING_MODE_MAJOR_MINOR;
    }
#endif

    NAV_CLI_MONITOR_KEY_DISPATCH_FLOW(__FUNCTION__,ui4_key_code);

    /* handle other remote controller keys */
    if(TV_MODE_TYPE_NORMAL == pt_this->t_nav_ctx.t_svc_res.e_tv_mode)
    {
        if(BTN_PIP_CH_DOWN == ui4_key_code || BTN_PIP_CH_UP == ui4_key_code)
        {
            DBG_LOG_PRINT(("<nav variant>tv mode is noraml %s,%d\n\r",__FILE__,__LINE__));
            return;
        }
    }
    else
    {
        /* in PIP/POP */
        if (BTN_PIP_CH_DOWN == ui4_key_code || BTN_PIP_CH_UP == ui4_key_code)
        {
            pt_tv_win = &pt_this->t_tv_wins[TV_WIN_ID_SUB];
            if (pt_tv_win->e_src_type != INP_SRC_TYPE_TV)
            {
                DBG_LOG_PRINT(("<nav variant>tv mode is PIP/POP %s,%d\n\r",__FILE__,__LINE__));
                return;
            }
        }
    }

    /* The previous key doesn't handle when PIP/POP and the focus win is not TV mode. */
    if (ui4_key_code == BTN_PREV_PRG)
    {
        if (pt_this->t_nav_ctx.t_svc_res.e_tv_mode == TV_MODE_TYPE_PIP ||
            pt_this->t_nav_ctx.t_svc_res.e_tv_mode == TV_MODE_TYPE_POP)
        {
            if (pt_tv_win->e_src_type != INP_SRC_TYPE_TV)
            {
                DBG_LOG_PRINT(("<nav variant>not tv %s,%d\n\r",__FILE__,__LINE__));
                return;
            }
        }
    }
    menu_blank_oled_scrn_timer_refresh();
    if(menu_custom_is_blank_screen())
    {
        menu_custom_unblank_screen(ui4_key_code);
        DBG_LOG_PRINT(("it is under blank screen %s,%d\n\r",__FILE__,__LINE__));
        return;
    }

    {
        TV_WIN_ID_T e_focus_win;
        ISL_REC_T   t_isl_rec;

        nav_get_focus_id(&e_focus_win);
        nav_get_isl_rec(e_focus_win, &t_isl_rec);
        if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
        {
            DBG_LOG_PRINT(("<nav variant> non TV ,no need handle channel up/down \n"));
            return;
        }
    }

    switch(ui4_key_code) {
    case BTN_CURSOR_DOWN:
    {
        if (!b_up_down_enable)
        {
            break;
        }
    }
    case BTN_PRG_DOWN:
    case BTN_PIP_CH_DOWN:
    {
#if 0
#ifdef APP_TTS_SUPPORT
        UTF16_T w2s_test_str[16] = L"Channel down";
        a_app_tts_play(w2s_test_str,c_uc_w2s_strlen(w2s_test_str));
#endif
#endif
        a_banner_reset_state_timer() ;
        if ((pt_tv_win->e_status & NAV_STATUS_BIT_INP_SRC_BLOCKED) > 0)
        {
            DBG_LOG_PRINT(("<nav variant>src blocked %s,%d\n\r",__FILE__,__LINE__));
            break;
        }

        if (pt_this->b_is_active == FALSE)
        {
            pt_this->b_key_from_other_app = TRUE;
            DBG_LOG_PRINT(("<nav variant>return is not active %s,%d\n\r",__FILE__,__LINE__));
            break;
        }

#ifdef TIME_MEASUREMENT
        TMS_DIFF_EX(TMS_FLAG_CHG_CHL, TMS_CHL_CHE_TIME, "AP_rcu_default_handler_DOWN");
#endif
        i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_bs_src);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>get tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        i4_ret = a_cfg_cust_set_last_channel_tuner_type(ui1_bs_src);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>set last tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        ui2_crnt_svl_id = (ui1_bs_src == APP_CFG_BS_SRC_CABLE ? CABLE_SVL_ID : ANTENNA_SVL_ID);

        ui2_tmp_svl_id     = ui2_crnt_svl_id;
        ui4_tmp_channel_id = ui4_crnt_channel_id;

        do{
            /* get previouse visible channel  */
            i4_ret = ocl_get_prev_svl_by_ch_id(ui2_tmp_svl_id, ui4_tmp_channel_id, &t_svl_rec, &t_ocl_svl_rec);
            ui2_tmp_svl_id     = t_ocl_svl_rec.ui2_svl_id;
            ui4_tmp_channel_id = t_ocl_svl_rec.ui4_channel_id;

        }while(TRUE == _nav_is_skip_channel(&t_svl_rec)
               && OCLR_OK == i4_ret);

        if (OCLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[nav variant] func=[%s],line=[%d],Error:ocl_get_prev_svl_by_ch_id ui2_svl_id=[%d],ui2_next_svl_id=[%d],i4_ret=[%d],ui4_next_channel_id=[%d],ui4_crnt_channel_id=[%d]\n",
                    __FUNCTION__,__LINE__,ui2_crnt_svl_id,t_ocl_svl_rec.ui2_svl_id,i4_ret,t_ocl_svl_rec.ui4_channel_id,ui4_crnt_channel_id));
            break;
        }

        ui4_next_channel_id = t_ocl_svl_rec.ui4_channel_id;

        DBG_LOG_PRINT(("[nav variant] func=[%s],line=[%d],ui2_svl_id=[%d],ui2_next_svl_id=[%d],i4_ret=[%d],ui4_next_channel_id=[%d],ui4_crnt_channel_id=[%d]\n",
                    __FUNCTION__,__LINE__,ui2_crnt_svl_id,t_ocl_svl_rec.ui2_svl_id,i4_ret,ui4_next_channel_id,ui4_crnt_channel_id));

        if(APP_CFG_BS_SRC_AIR == ui1_bs_src
            && t_ocl_svl_rec.ui2_svl_id == CABLE_SVL_ID)
        {
            pt_tv_win->t_tv.h_svl = h_cable_svl;
            i4_ret = a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>set tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }
            b_is_changed = TRUE;
        }
        else if(APP_CFG_BS_SRC_CABLE == ui1_bs_src
                && t_ocl_svl_rec.ui2_svl_id == ANTENNA_SVL_ID)
        {
            pt_tv_win->t_tv.h_svl = h_antenna_svl;
            i4_ret = a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>set tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }
            b_is_changed = TRUE;
        }

        DBG_LOG_PRINT(("[nav variant] func=[%s],line=[%d],b_is_changed=[%d],i4_ret=[%d],ui4_next_channel_id=[%d],ui4_crnt_channel_id=[%d]\n", __FUNCTION__,__LINE__,b_is_changed,i4_ret,ui4_next_channel_id,ui4_crnt_channel_id));

        if (i4_ret == OCLR_OK &&
            ((ui4_next_channel_id != ui4_crnt_channel_id) ||   /* TV source could check the channel */
             (b_is_changed == TRUE) ||
            (pt_tv_win->e_src_type != INP_SRC_TYPE_TV))       /* AV source always acceptable */
            )
        {
            if(pt_tv_win->e_src_type == INP_SRC_TYPE_TV)
            {
                i4_ret = nav_channel_chg_pre_stop_feature(pt_tv_win->e_id);
                if(NAVR_OK != i4_ret)
                {
                    DBG_LOG_PRINT(("<nav variant>ch pre stop fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                }

            }
            DBG_LOG_PRINT(("[nav variant]nav_change_channel_by_rec,id:%d\n\r",t_svl_rec.uheader.t_rec_hdr.ui4_channel_id));

            i4_ret = a_cfg_cust_set_last_channel_id(ui4_crnt_channel_id);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>set last channel id fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }

            i4_ret = nav_change_channel_by_rec(pt_tv_win->e_id, &t_svl_rec, NULL);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>change cahnnel by rec fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }

            /* sync */
            i4_ret = a_cfg_update_dt_sync_mode();
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>update dt sync mode faile  %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }
        }
    }
    break;
    case BTN_CURSOR_UP:
    {
        if (!b_up_down_enable)
        {
            break;
        }
    }
    case BTN_PRG_UP:
    case BTN_PIP_CH_UP:
    {
#if 0
#ifdef APP_TTS_SUPPORT
        UTF16_T w2s_test_str[16] = L"Channel up";
        a_app_tts_play(w2s_test_str,c_uc_w2s_strlen(w2s_test_str));
#endif
#endif
        a_banner_reset_state_timer();
        if ((pt_tv_win->e_status & NAV_STATUS_BIT_INP_SRC_BLOCKED) > 0)
        {
            DBG_LOG_PRINT(("<nav variant>src blocked  %s,%d\n\r",__FILE__,__LINE__));
            break;
        }

        if (pt_this->b_is_active == FALSE)
        {
            pt_this->b_key_from_other_app = TRUE;
            DBG_LOG_PRINT(("<nav variant>not active  %s,%d\n\r",__FILE__,__LINE__));
            break;
        }

#ifdef TIME_MEASUREMENT
        TMS_DIFF_EX(TMS_FLAG_CHG_CHL, TMS_CHL_CHE_TIME, "AP_rcu_default_handler_DOWN");
#endif
        i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_bs_src);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>get tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        i4_ret = a_cfg_cust_set_last_channel_tuner_type(ui1_bs_src);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>set last tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        ui2_crnt_svl_id = (ui1_bs_src == APP_CFG_BS_SRC_CABLE ? CABLE_SVL_ID : ANTENNA_SVL_ID);

        ui2_tmp_svl_id     = ui2_crnt_svl_id;
        ui4_tmp_channel_id = ui4_crnt_channel_id;

        do{
            /* get next visible channel  */
            i4_ret = ocl_get_next_svl_by_ch_id(ui2_tmp_svl_id, ui4_tmp_channel_id, &t_svl_rec, &t_ocl_svl_rec);
            ui2_tmp_svl_id     = t_ocl_svl_rec.ui2_svl_id;
            ui4_tmp_channel_id = t_ocl_svl_rec.ui4_channel_id;

        }while(TRUE == _nav_is_skip_channel(&t_svl_rec)
               && OCLR_OK == i4_ret);

        if (OCLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[nav variant] func=[%s],line=[%d],Error:ocl_get_next_svl_by_ch_id ui2_svl_id=[%d],ui2_next_svl_id=[%d],i4_ret=[%d],ui4_next_channel_id=[%d],ui4_crnt_channel_id=[%d]\n",
                    __FUNCTION__,__LINE__,ui2_crnt_svl_id,t_ocl_svl_rec.ui2_svl_id,i4_ret,t_ocl_svl_rec.ui4_channel_id,ui4_crnt_channel_id));
            break;
        }

        ui4_next_channel_id = t_ocl_svl_rec.ui4_channel_id;

        DBG_LOG_PRINT(("[nav variant] func=[%s],line=[%d],ui2_svl_id=[%d],ui2_next_svl_id=[%d],i4_ret=[%d],ui4_next_channel_id=[%d],ui4_crnt_channel_id=[%d]\n",
                    __FUNCTION__,__LINE__,ui2_crnt_svl_id,t_ocl_svl_rec.ui2_svl_id,i4_ret,ui4_next_channel_id,ui4_crnt_channel_id));

        if(APP_CFG_BS_SRC_AIR == ui1_bs_src
            && t_ocl_svl_rec.ui2_svl_id == CABLE_SVL_ID)
        {
            pt_tv_win->t_tv.h_svl = h_cable_svl;
            i4_ret = a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>set tuner type %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }
            b_is_changed = TRUE;
        }
        else if(APP_CFG_BS_SRC_CABLE == ui1_bs_src
                && t_ocl_svl_rec.ui2_svl_id == ANTENNA_SVL_ID)
        {
            pt_tv_win->t_tv.h_svl = h_antenna_svl;
            i4_ret = a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>set tuner type %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }
            b_is_changed = TRUE;
        }

        DBG_LOG_PRINT(("[nav variant] func=[%s],line=[%d],b_is_changed=[%d],i4_ret=[%d],ui4_next_channel_id=[%d],ui4_crnt_channel_id=[%d]\n", __FUNCTION__,__LINE__,b_is_changed,i4_ret,ui4_next_channel_id,ui4_crnt_channel_id));

        if (i4_ret == OCLR_OK &&
            ((ui4_next_channel_id != ui4_crnt_channel_id) ||   /* TV source could check the channel */
             (b_is_changed == TRUE) ||
            (pt_tv_win->e_src_type != INP_SRC_TYPE_TV))       /* AV source always acceptable */
            )
        {
            if(pt_tv_win->e_src_type == INP_SRC_TYPE_TV)
            {
                i4_ret = nav_channel_chg_pre_stop_feature(pt_tv_win->e_id);
                if(NAVR_OK != i4_ret)
                {
                    DBG_LOG_PRINT(("<nav variant>channel pre stop fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                }
            }
            DBG_LOG_PRINT(("[nav variant]nav_change_channel_by_rec crnt_id:%d,rec_id:%d,next_id:%d\n\r",
                        ui4_crnt_channel_id,t_svl_rec.uheader.t_rec_hdr.ui4_channel_id,ui4_next_channel_id));

            i4_ret = a_cfg_cust_set_last_channel_id(ui4_crnt_channel_id);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>set last channel id fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }

            i4_ret = nav_change_channel_by_rec(pt_tv_win->e_id, &t_svl_rec, NULL);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>change channel by rec fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }

            /* sync */
            i4_ret = a_cfg_update_dt_sync_mode();
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("<nav variant>update dt sync mode fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }
        }
    }
    break;
    case BTN_PREV_PRG:
      {
        UINT32  ui4_prev_last_channel_id;
        UINT8   ui1_last_bs_src = 0;
        UINT8   ui1_crt_bs_src  = 0;

#ifdef APP_TTS_SUPPORT
        a_app_tts_play(L"Previous Channel",c_uc_w2s_strlen(L"Previous Channel"));
#endif

        if ((pt_tv_win->e_status & NAV_STATUS_BIT_INP_SRC_BLOCKED) > 0)
        {
            DBG_LOG_PRINT(("<nav variant> SRC blocked %s,%d\n\r",__FILE__,__LINE__));
            break;
        }

        if (pt_this->b_is_active == FALSE)
        {
            pt_this->b_key_from_other_app = TRUE;
            DBG_LOG_PRINT(("<nav variant> not active %s,%d\n\r",__FILE__,__LINE__));
            break;
        }

#ifdef TIME_MEASUREMENT
        TMS_DIFF_EX(TMS_FLAG_CHG_CHL, TMS_CHL_CHE_TIME, "AP_rcu_default_handler_PREV");
#endif

        //ui4_prev_last_channel_id = NAV_UTIL_CNFG_GET_LAST_CHANNEL_ID(pt_tv_win->e_id);
        i4_ret = a_cfg_cust_get_last_channel_id(&ui4_prev_last_channel_id);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>get last channel id  fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        i4_ret = a_cfg_cust_get_last_channel_tuner_type(&ui1_last_bs_src);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>get last tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        i4_ret = a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_crt_bs_src);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>get tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        /* save the last channel id and tuner type. */
        i4_ret = a_cfg_cust_set_last_channel_tuner_type(ui1_crt_bs_src);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>set last tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        i4_ret = a_cfg_cust_set_last_channel_id(ui4_crnt_channel_id);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>set last channel id  fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        DBG_LOG_PRINT(("<nav variant> line=[%d] ui4_prev_last_channel_id=[%d],ui1_last_bs_src=[%d],ui4_crnt_channel_id=[%d],ui1_crt_bs_src=[%d]\n",
        __LINE__, ui4_prev_last_channel_id, ui1_last_bs_src, ui4_crnt_channel_id, ui1_crt_bs_src));

        /* PREV_PRG supports in TV source only (default). */
        if (a_cfg_ftm_with_feature(APP_CFG_FTM_ID_ALLOW_PREV_PRG_WITHIN_SOURCE) == FALSE)
        {
            if (ui4_crnt_channel_id != ui4_prev_last_channel_id ||
                ui1_crt_bs_src != ui1_last_bs_src)
            {
                /* Normal system behavior */
                if (nav_is_allow_dup_ch_num() == FALSE)
                {
                    b_allow_to_change_channel = TRUE;
                }

                if(ui1_crt_bs_src != ui1_last_bs_src)
                {
                    i4_ret = a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, ui1_last_bs_src);
                    if(APP_CFGR_OK != i4_ret)
                    {
                        DBG_LOG_PRINT(("<nav variant>set tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                    }
              #if 0
                    i4_ret = nav_change_channel_by_id(pt_tv_win->e_id, ui4_prev_last_channel_id, NULL);
                    if(NAVR_OK != i4_ret)
                    {
                        DBG_LOG_PRINT(("<nav variant>change channel by id fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                    }
             #endif
                }

                if (b_allow_to_change_channel)
                {
                    i4_ret = nav_channel_chg_pre_stop_feature(pt_tv_win->e_id);
                    if(APP_CFGR_OK != i4_ret)
                    {
                        DBG_LOG_PRINT(("<nav variant>ch pre stop fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                    }

                    i4_ret = nav_change_channel_by_id(pt_tv_win->e_id, ui4_prev_last_channel_id, NULL);
                    if(NAVR_OK != i4_ret)
                    {
                        DBG_LOG_PRINT(("<nav variant>change channel by id  fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                    }
                }
            }
        }

        /* PREV_PRG supports switch between sources. */
        else
        {
            /* PIP/POP mode is not supported */
            a_tv_get_mode (&e_tv_mode);

            i4_ret = a_tv_get_isl_rec_by_win_id(pt_tv_win->e_id, &t_crnt_isl_rec);

            if (i4_ret != TVR_OK)
            {
                DBG_LOG_PRINT(("<nav variant>get isl fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                break;
            }

            /* In PIP/POP mode, it is not alloed to change anything in AV source. */
            /* In PIP/POP mode, it is allowed to change in TV source only .*/
            /* In normal mode,  it is allowed to change in all source */

            if (e_tv_mode != TV_MODE_TYPE_NORMAL &&                /* PIP/POP */
                t_crnt_isl_rec.e_src_type != INP_SRC_TYPE_TV)     /* AV */
            {
                DBG_LOG_PRINT(("<nav variant>no tv source ,no normal %s,%d\n\r",__FILE__,__LINE__));
                break;
            }

            if (e_tv_mode != TV_MODE_TYPE_NORMAL && t_crnt_isl_rec.e_src_type == INP_SRC_TYPE_TV)
            {
                b_force_to_change_in_tv_only = TRUE;
            }

            i4_ret = a_tv_get_last_isl_rec_by_win_id(pt_tv_win->e_id, &t_last_isl_rec);
            if (i4_ret != TVR_OK)
            {
                DBG_LOG_PRINT(("<nav variant>get last isl fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                break;
            }

            /* TV to TV case or forcely in TV case (PIP/POP)*/
            if (t_last_isl_rec.e_src_type == INP_SRC_TYPE_TV ||
                b_force_to_change_in_tv_only == TRUE)
            {
                if (t_crnt_isl_rec.e_src_type == INP_SRC_TYPE_TV)
                {
                    if (ui4_crnt_channel_id == ui4_prev_last_channel_id
                        && ui1_crt_bs_src == ui1_last_bs_src)
                    {
                        DBG_LOG_PRINT(("<nav variant>the same channel id %s,%d\n\r",__FILE__,__LINE__));
                        return;
                    }
                }
                else
                {
                    ui4_prev_last_channel_id = ui4_crnt_channel_id;
                }

                /* Normal system behavior */
                if (nav_is_allow_dup_ch_num() == FALSE)
                {
                    b_allow_to_change_channel = TRUE;
                }

                if(ui4_crnt_channel_id != ui4_prev_last_channel_id ||
                   ui1_crt_bs_src != ui1_last_bs_src)
                {
                    if(ui1_crt_bs_src != ui1_last_bs_src)
                    {
                        i4_ret = a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, ui1_last_bs_src);
                        if(APP_CFGR_OK != i4_ret)
                        {
                            DBG_LOG_PRINT(("<nav variant>set tuner type fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                        }

                        i4_ret = nav_change_channel_by_id(pt_tv_win->e_id, ui4_prev_last_channel_id, NULL);
                        if(NAVR_OK != i4_ret)
                        {
                            DBG_LOG_PRINT(("<nav variant>change channel bu id fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                        }
                    }
                }

                if (b_allow_to_change_channel)
                {
                    i4_ret = nav_change_channel_by_id(pt_tv_win->e_id, ui4_prev_last_channel_id, NULL);
                    if(NAVR_OK != i4_ret)
                    {
                        DBG_LOG_PRINT(("<nav variant>change channel by id fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                    }
                }
            }
            else
            {
                if (t_last_isl_rec.ui1_id == t_crnt_isl_rec.ui1_id)
                {
                    DBG_LOG_PRINT(("<nav variant>the same isl rec %s,%d\n\r",__FILE__,__LINE__));
                    return;
                }

                i4_ret = nav_change_av_inp_by_rec(pt_tv_win->e_id,&t_last_isl_rec,NULL);
                if(NAVR_OK != i4_ret)
                {
                    DBG_LOG_PRINT(("<nav variant>change av inp by rec fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                }
            }
        }

        /* sync */
        i4_ret = a_cfg_update_dt_sync_mode();
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<nav variant>update dt sync mode fail %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        }

        break;
      }
    default:
        break;
    }
}

#ifndef CC_DISCRETE_REMOTE_CODE
static VOID _rcu_key_default_handler_fct(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win,
    UINT32                  ui4_key_code)
{
    if ( a_cfg_cust_fac_discrete_key_handler_fct(&ui4_key_code) )
    {
        return;
    }

    NAV_DEBUG_KEY( DBG_LOG_PRINT(("[NAV][KEY]{%s,%d} ui4_key_code:0x%X\n", __FUNCTION__, __LINE__, ui4_key_code )); );

    switch(ui4_key_code)
    {
    /* source is tv & channel ,BTN_SELECT not show channel list,show tuner setup UI*/
    #if 0
        case BTN_SELECT:
            #ifdef APP_MMP_SUPPORT
            if (a_menu_custom_is_resuming_mmp() == FALSE)
            #endif
            {
                nav_send_sim_rc_key_event(BTN_CH_LIST);
            }
            return;
    #endif
        case BTN_3D:
            if(_nav_get_3d_setting_mode() == FALSE)
            {
                return;
            }
            if (a_menu_is_hot_key(ui4_key_code, WGL_MSG_KEY_DOWN) && a_menu_3d_setting_is_able_to_enable())
            {
                a_menu_hot_key_handler(ui4_key_code, WGL_MSG_KEY_DOWN, NULL);
            }
            return ;

        case BTN_BLANK_SCREEN:
        case BTN_NETWORK:
    #if( MENU_SUPPORT_HOT_KEY_PIC|| defined(APP_SUPPORT_PIC_HOT_KEY) )
        case BTN_P_EFFECT:
    #endif
    #if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO)
        case BTN_ASPECT:
    #endif
            {
                NAV_DEBUG_KEY( DBG_LOG_PRINT(("[NAV][KEY]{%s,%d} ui4_key_code:0x%X\n", __FUNCTION__, __LINE__, ui4_key_code )); );

                if (a_menu_is_hot_key(ui4_key_code, WGL_MSG_KEY_DOWN))
                {
                    a_menu_hot_key_handler(ui4_key_code, WGL_MSG_KEY_DOWN, NULL);
                }

                return;
            }

    #ifdef APP_3D_RETAIL_DEMO_MODE
        case BTN_INVALID:
            if (a_nav_retail_mode_get_play_video_status())
            {
                return;
            }
            break;
    #endif
        case BTN_PRG_DOWN:
        case BTN_PRG_UP:
        case BTN_CURSOR_UP:
        case BTN_CURSOR_DOWN:
        case BTN_PREV_PRG:
            {
                a_rest_set_test_patterns_turn_off();
                _nav_rcu_channel_key_handler(pt_this,pt_tv_win,ui4_key_code);
            }
            return ;
        default:
            break;
    }

    nav_rcu_key_default_handler(pt_this,
                                pt_tv_win,
                                ui4_key_code);
}
#endif
/*-----------------------------------------------------------------------------
 * static methods implementations
 *---------------------------------------------------------------------------*/
#ifdef CC_DISCRETE_REMOTE_CODE
static VOID _change_next_tv(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win)
{
    ISL_REC_T   t_isl_rec_next;

    a_isl_get_rec_by_type(INP_SRC_TYPE_TV, 0, &t_isl_rec_next);

    nav_change_av_inp_by_rec(pt_tv_win->e_id,
                             &t_isl_rec_next,
                             NULL);

    nav_hide_components(COMP_EXEC_SET_INPUT_SRC);
}

static VOID _change_next_comp(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win)
{
    INT32       i4_ret;
    ISL_REC_T   t_isl_rec_next;
    UINT8       ui1_id_crnt = 0;

    if(pt_tv_win->t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       pt_tv_win->t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI)
    {
        /* If current input source is Y_PB_PR, find next Y_PB_PR source */
        a_isl_iterate_rec(pt_tv_win->t_isl_rec.ui1_id,
                          ISL_ITERATE_DIR_NEXT,
                          &t_isl_rec_next);
    }
    else
    {
        i4_ret = a_isl_iterate_rec(ui1_id_crnt,
                                   ISL_ITERATE_DIR_THIS,
                                   &t_isl_rec_next);
        if(i4_ret != ISLR_OK)
        {
            a_isl_iterate_rec(ui1_id_crnt,
                                   ISL_ITERATE_DIR_FIRST,
                                   &t_isl_rec_next);
        }
    }

    while(t_isl_rec_next.e_src_type != INP_SRC_TYPE_AV ||
          t_isl_rec_next.t_avc_info.e_video_type != DEV_AVC_COMBI)
    {
        /* loop until Y_PB_PR is found */
        a_isl_iterate_rec(t_isl_rec_next.ui1_id,
                          ISL_ITERATE_DIR_NEXT,
                          &t_isl_rec_next);
    }

    /* Change input source */
    nav_change_av_inp_by_rec(pt_tv_win->e_id,
                             &t_isl_rec_next,
                             NULL);

    nav_hide_components(COMP_EXEC_SET_INPUT_SRC);
}

static VOID _change_select_comp(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win,
    UINT8       ui1_select_id)
{
    ISL_REC_T   t_isl_rec_next;

    a_isl_get_rec_by_dev_type(DEV_AVC_Y_PB_PR, ui1_select_id, &t_isl_rec_next);

    nav_change_av_inp_by_rec(pt_tv_win->e_id,
                             &t_isl_rec_next,
                             NULL);

    nav_hide_components(COMP_EXEC_SET_INPUT_SRC);
}

static VOID _change_next_hdmi(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win)
{
    INT32       i4_ret;
    ISL_REC_T   t_isl_rec_next;
    UINT8       ui1_id_crnt = 0;

    if(pt_tv_win->t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       pt_tv_win->t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
    {
        /* If current input source is HDMI, find next HDMI source */
        a_isl_iterate_rec(pt_tv_win->t_isl_rec.ui1_id,
                          ISL_ITERATE_DIR_NEXT,
                          &t_isl_rec_next);
    }
    else
    {
        i4_ret = a_isl_iterate_rec(ui1_id_crnt,
                                   ISL_ITERATE_DIR_THIS,
                                   &t_isl_rec_next);
        if(i4_ret != ISLR_OK)
        {
            a_isl_iterate_rec(ui1_id_crnt,
                                   ISL_ITERATE_DIR_FIRST,
                                   &t_isl_rec_next);
        }
    }

    while(t_isl_rec_next.e_src_type != INP_SRC_TYPE_AV ||
          t_isl_rec_next.t_avc_info.e_video_type != DEV_AVC_HDMI)
    {
        /* loop until HDMI is found */
        a_isl_iterate_rec(t_isl_rec_next.ui1_id,
                          ISL_ITERATE_DIR_NEXT,
                          &t_isl_rec_next);
    }

    /* Change input source */
    nav_change_av_inp_by_rec(pt_tv_win->e_id,
                             &t_isl_rec_next,
                             NULL);

    nav_hide_components(COMP_EXEC_SET_INPUT_SRC);
}


static VOID _change_select_hdmi(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win,
    UINT8       ui1_select_id)
{
    ISL_REC_T   t_isl_rec_next;

    a_isl_get_rec_by_dev_type(DEV_AVC_HDMI, ui1_select_id, &t_isl_rec_next);

    nav_change_av_inp_by_rec(pt_tv_win->e_id,
                             &t_isl_rec_next,
                             NULL);

    nav_hide_components(COMP_EXEC_SET_INPUT_SRC);
}


static VOID _change_next_vga(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win)
{
    ISL_REC_T   t_isl_rec_next;

    a_isl_get_rec_by_dev_type(DEV_AVC_VGA, 0, &t_isl_rec_next);

    nav_change_av_inp_by_rec(pt_tv_win->e_id,
                             &t_isl_rec_next,
                             NULL);

    nav_hide_components(COMP_EXEC_SET_INPUT_SRC);
}

static VOID _discrete_key_handler_fct(
    struct _NAV_MODEL_T*    pt_this,
    NAV_TV_WIN_T*           pt_tv_win,
    UINT32                  ui4_key_code)
{
    NAV_DEBUG_KEY( DBG_LOG_PRINT(("[NAV][KEY]{%s,%d} ui4_key_code:0x%X\n", __FUNCTION__, __LINE__, ui4_key_code )); );

#ifdef APP_3D_RETAIL_DEMO_MODE
    if (a_nav_retail_mode_get_play_video_status())
    {
        if ((BTN_VOL_UP != ui4_key_code)
            &&(BTN_VOL_DOWN != ui4_key_code)
            &&(BTN_POWER != ui4_key_code))
        {
            ui4_key_code = BTN_INVALID;
            return;
        }
    }
#endif

    if( a_cfg_cust_fac_discrete_key_handler_fct( &ui4_key_code))
        return;


    switch(ui4_key_code)
    {
      case BTN_TV:
          _change_next_tv(pt_this,pt_tv_win);
          return;

      case BTN_COMPOSITE:
          _change_next_comp(pt_this,pt_tv_win);
          return;
      case BTN_COMPONENT_1:
      case BTN_COMPONENT:
          _change_next_comp(pt_this,pt_tv_win);
          return;

    case BTN_HDMI:
      _change_next_hdmi(pt_this,pt_tv_win);
      return;

    case BTN_COMPONENT_2:
          _change_select_comp(pt_this,pt_tv_win, (ui4_key_code - BTN_COMPONENT_1));
      return;

        case BTN_HDMI_1:
        case BTN_HDMI_2:
        case BTN_HDMI_3:
        case BTN_HDMI_4:
          _change_select_hdmi(pt_this,pt_tv_win, (ui4_key_code - BTN_HDMI_1));
          return;

        case BTN_VGA:
          _change_next_vga(pt_this,pt_tv_win);
          return;

        case BTN_3D:
            if(_nav_get_3d_setting_mode() == FALSE)
            {
                return;
            }
            if (a_menu_is_hot_key(ui4_key_code, WGL_MSG_KEY_DOWN) && a_menu_3d_setting_is_able_to_enable())
            {
                a_menu_hot_key_handler(ui4_key_code, WGL_MSG_KEY_DOWN, NULL);
            }
            return ;
        case BTN_BLANK_SCREEN:
        case BTN_NETWORK:
    #if( MENU_SUPPORT_HOT_KEY_PIC|| defined(APP_SUPPORT_PIC_HOT_KEY) )
        case BTN_P_EFFECT:
    #endif
    #if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO)
        case BTN_ASPECT:
    #endif
            {
                NAV_DEBUG_KEY( DBG_LOG_PRINT(("[NAV][KEY]{%s,%d} ui4_key_code:0x%X\n", __FUNCTION__, __LINE__, ui4_key_code )); );

                if (a_menu_is_hot_key(ui4_key_code, WGL_MSG_KEY_DOWN))
                {
                    a_menu_hot_key_handler(ui4_key_code, WGL_MSG_KEY_DOWN, NULL);
                }

                return;
            }
    /* source is tv & channel ,BTN_SELECT not show channel list,show tuner setup UI*/
    #if 0
        case BTN_SELECT:
            #ifdef APP_MMP_SUPPORT
            if (a_menu_custom_is_resuming_mmp() == FALSE)
            #endif
            {
                nav_send_sim_rc_key_event(BTN_CH_LIST);
            }
            return;
    #endif
        case BTN_RETURN:
            {
                TV_WIN_ID_T                 e_tv_win_id = TV_WIN_ID_MAIN ;

                nav_get_focus_id (&e_tv_win_id);
                if ((nav_is_active())
                    && (nav_is_component_visible(NAV_COMP_ID_SCREEN_SAVER))
                    && (nav_is_signal_loss(e_tv_win_id)))
                {
                    return;
                }
                else
                {
                    break;
                }
            }
        #if 1
        case BTN_WIDGET:
        {
            if ( pt_this->ui4_key_status == WGL_KEY_STATE_DOWN)
            {
                if (nav_get_active_component() != NAV_COMP_ID_VIA_DLG)
                {
                    nav_rcu_key_handler(BTN_WIDGET);
                }
            }
            return;
        }
        #endif

        case BTN_PRG_DOWN:
        case BTN_PRG_UP:
        case BTN_PREV_PRG:
            {
                TV_WIN_ID_T e_focus_win = TV_WIN_ID_MAIN;
                ISL_REC_T   t_isl_rec = {0};


                nav_get_focus_id(&e_focus_win);
                nav_get_isl_rec(e_focus_win, &t_isl_rec);
                DBG_LOG_PRINT(("<nav variant> %s,%d,type:%d\n\r",__FILE__,__LINE__,t_isl_rec.e_src_type ));
                if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
                {
                    a_rest_set_test_patterns_turn_off();
                    _nav_rcu_channel_key_handler(pt_this,pt_tv_win,ui4_key_code);
                }
            }
            return ;
        default:
            break;

    }

    nav_rcu_key_default_handler(pt_this,
                                pt_tv_win,
                                ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name : _discrete_key_pre_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _discrete_key_pre_handler(UINT32 ui4_keystatus, UINT32* pt_ui4_keycode)
{
    UINT32      ui4_keycode = *pt_ui4_keycode;
    BOOL        b_mute = FALSE;
    HANDLE_T    h_svctx_main;

    if(ui4_keycode == BTN_COMPOSITE_1)
    {
        ui4_keycode = BTN_COMPOSITE;
    }

    nav_get_svctx_handle(TV_WIN_ID_MAIN,&h_svctx_main);

    c_svctx_get_mute(h_svctx_main, &b_mute);
    if(((b_mute == TRUE) && (ui4_keycode == BTN_CUSTOM_5)) ||
       ((b_mute == FALSE) && (ui4_keycode == BTN_CUSTOM_4)))
    {
        ui4_keycode = BTN_MUTE;
    }

    *pt_ui4_keycode = ui4_keycode;
}
#endif

#ifdef APP_C4TV_SUPPORT
static BOOL _nav_c4tv_is_key_to_discard(UINT32  ui4_key_code)
{
    switch(ui4_key_code)
    {
    //case BTN_DIGIT_0:
    //case BTN_DIGIT_1: case BTN_DIGIT_2: case BTN_DIGIT_3:
    //case BTN_DIGIT_4: case BTN_DIGIT_5: case BTN_DIGIT_6:
    //case BTN_DIGIT_7: case BTN_DIGIT_8: case BTN_DIGIT_9:
    //case BTN_DIGIT_DOT:
        //return TRUE;
   // case BTN_SELECT:   /* source is tv & channel ,BTN_SELECT not show channel list,show tuner setup UI*/
    case BTN_RETURN:
    case BTN_KB_RETURN:
        return FALSE;
    case BTN_EXIT:
        return FALSE;
    default:
        return FALSE;
    }

    return FALSE;
}
#endif

/*-----------------------------------------------------------------------------
 * export methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_is_key_to_discard
 * Description
 *      The API is used to check the key is needs to discard
 * Input arguments
 *      pt_this         a pointer points to the Navigator itself.
 *      pt_event        KEY event
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
BOOL nav_is_key_to_discard(
                    NAV_MODEL_T*                pt_this,
                    NAV_EVN_T*                  pt_event
                    )
{
    /* Process EAS external control */
    BOOL        b_discard = FALSE;
    UINT32      ui4_ext_rule = pt_this->t_ex_ctrl_req.ui4_rule;
    UINT32      ui4_key_code = pt_event->ui4_data2;
    INT32       i4_ret;
    UINT8       ui1_icl_val;
    SIZE_T      z_size;
    ISL_REC_T   t_isl_rec;
    CHAR        s_disp_name[SYS_NAME_LEN + 1];

#ifdef APP_C4TV_SUPPORT
    if (_nav_c4tv_is_key_to_discard(ui4_key_code))
    {
        DBG_INFO(("[NAV] discard %d\n", ui4_key_code));
        return TRUE;
    }
#endif

    if (a_tuner_setup_is_key_to_discard(ui4_key_code))
    {
        return TRUE;
    }

    /* for common key */
    if (a_scrn_blank_get_state() == NAV_SCRN_BLANK_STATE_BLANK)
    {
        if ((BTN_VOL_UP != ui4_key_code)
            &&(BTN_VOL_DOWN != ui4_key_code)
            &&(BTN_MUTE != ui4_key_code))
        {
            //nav_grab_activation(NAV_COMP_ID_SCRN_BLANK);
            a_scrn_blank_reset();
            b_discard = TRUE;
            return b_discard;
        }
    }

    if (ui4_ext_rule == NAV_EXTERNAL_CTRL_RULE_ALLOW_NOTHING) /* allow nothing */
    {
        b_discard = TRUE;
    }
    else if (ui4_ext_rule == NAV_EXTERNAL_CTRL_RULE_ALLOW_EVERYTHING) /* allow everything */
    {
        b_discard = FALSE;
    }
    else /* allow something */
    {
        if ((nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_VOLUME_CTRL_UI) == FALSE) && /* allow volume control */
            (ui4_key_code == BTN_VOL_UP   ||
             ui4_key_code == BTN_VOL_DOWN ||
             ui4_key_code == BTN_MUTE))
        {
            b_discard = FALSE; /* allow vol+/- and mute to be processed */
        }
        else if ((nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_CH_CHANGE) == FALSE) && /* allow channel changes */
                 (ui4_key_code == BTN_PRG_UP ||
                  ui4_key_code == BTN_PRG_DOWN))
        {
            b_discard = FALSE; /* allow ch+/- to be processed */
        }
        else
        {
            b_discard = TRUE; /* Ignore all the other key events */
        }
    }

    if (b_discard == FALSE &&
        (pt_event->ui4_data2 == BTN_MUTE ||
         pt_event->ui4_data2 == BTN_VOL_UP ||
         pt_event->ui4_data2 == BTN_VOL_DOWN))
    {
        z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
        i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                           &ui1_icl_val,
                           &z_size);
        if (i4_ret == ICLR_OK && ui1_icl_val == ICL_CEC_SAC_STATUS_ON)
        {
            /* don't discard vol key and send to pwd dlg when pwd pin dlg show,
             * amp connected and amp iom key has been return
            */
            if(pwd_dlg_view_is_show_box())
            {
                b_discard = FALSE;
            }
            else
            {
                b_discard = TRUE;
            }
        }
    }

    if (ui4_key_code == BTN_PREV_PRG)
    {
        i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        if(APP_CFGR_OK != i4_ret)
        {
            return b_discard;
        }

        a_tv_get_isl_rec_by_snk_name(s_disp_name, &t_isl_rec);

        if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV
        #ifdef APP_C4TV_SUPPORT
            || (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type
                && DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
        #endif
          )
        {
            b_discard = FALSE;
        }
        else
        {
            b_discard = TRUE;
        }
    }

#ifdef APP_2K12_RETAIL_DEMO_MODE
    if (a_retail_mode_is_key_to_discard(ui4_key_code))
    {
        return TRUE;
    }
#endif

#ifdef LINUX_TURNKEY_SOLUTION
    if (ui4_key_code == BTN_WIDGET)
    {
        #if 0
        if(( pt_event->ui4_data1 == WGL_MSG_KEY_DOWN))
        {
            DBG_INFO(("[NAV] --- Widget key down handler\n"));

            if (!a_msg_convert_is_yahoo_started())
            {
                /* Yahoo dock is not prepared */
                DBG_INFO(("%s() Yahoo dock is not prepared\n", __FUNCTION__));
                b_discard = FALSE;
            }
            else
            {
                a_tv_custom_handle_widget_key();
                b_discard = TRUE;
            }
        }
        #else
        if(( pt_event->ui4_data1 == WGL_MSG_KEY_DOWN))
        {
        #ifdef APP_YAHOO_LOADING_SPINNER_SUPPORT
            if (!a_msg_convert_is_yahoo_ready())
            {
                /* Yahoo dock is not prepared */
                DBG_INFO(("nav_is_key_to_discard() Yahoo dock is not prepared\n"));
                b_discard = FALSE;
                return b_discard;
            }

            BOOL b_lock = a_nav_via_dlg_get_via_lock();
            DBG_INFO(("[NAV] --- Widget key down handler via_lock = %d\n", b_lock));

            if (b_lock)
            {
                b_discard = TRUE;
                return b_discard;
            }

            if(NAV_COMP_ID_SLEEP == nav_get_active_component())
            {
                nav_return_activation(NAV_COMP_ID_SLEEP);
            }
        #endif

            a_tv_custom_handle_widget_key();
        }
        b_discard = TRUE;
        #endif
    }
#endif

    return b_discard;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_rcu_key_pre_handler
 * Description
 *      The API is used to do something before executing the remote controller
 *       key handler
 * Input arguments
 *      pt_this         a pointer points to the Navigator itself.
 *      pt_event        KEY event
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_rcu_key_pre_handler(
                    NAV_MODEL_T*                pt_this,
                    NAV_EVN_T*                  pt_event
                    )
{
    INT32   i4_ret = NAVR_OK;

    /* Remap the keycode according to the tshift configuration
       This remapping is designed only for MTK turnkey remote controller
    */
    UINT32  ui4_key_event= pt_event->ui4_data1 ;
    UINT32  ui4_key_code = pt_event->ui4_data2 ;

    NAV_DEBUG_KEY( DBG_LOG_PRINT(("[NAV][KEY]{%s,%d} ui4_key_code:0x%X, ui4_key_event:0x%X\n",
            __FUNCTION__, __LINE__, ui4_key_code, ui4_key_event )); );


    /* for hot key */
    if (a_scrn_blank_get_state() == NAV_SCRN_BLANK_STATE_BLANK)
    {
        if ((BTN_VOL_UP != ui4_key_code)
            &&(BTN_VOL_DOWN != ui4_key_code)
            &&(BTN_MUTE != ui4_key_code))
        {
            return;
        }
    }

#ifndef APP_NAV_CUSTOM_RCU_KEY_PRE_HANDLER
    if (a_app_nav_custom_rcu_key_pre_handler())
#endif
    {
        nav_custom_rcu_key_pre_handler(pt_this, pt_event);
    }

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
    INT32   i4_ret;
    APP_CFG_TSHIFT_MODE_T   e_tshift_mode = APP_CFG_TSHIFT_MODE_OFF;

    a_cfg_get_tshift_mode(&e_tshift_mode);
#endif

    /* check CC key */
    if (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
    {
        UINT8   ui1_cc_val  = ICL_CC_ITEM_STATUS_SHOW;
        SIZE_T  z_size      = ICL_RECID_CC_ITEM_STATUS_SIZE;

        a_icl_get(ICL_MAKE_ID(ICL_GRPID_CC_ITEM_STATUS, ICL_RECID_CC_ITEM_STATUS),
                        &ui1_cc_val, &z_size);

        if (BTN_CC == ui4_key_code)
        {
            if(ICL_CC_ITEM_STATUS_HIDE == ui1_cc_val)
            {
                ui1_cc_val  = ICL_CC_ITEM_STATUS_SHOW;
                a_icl_set(ICL_MAKE_ID(ICL_GRPID_CC_ITEM_STATUS, ICL_RECID_CC_ITEM_STATUS),
                        &ui1_cc_val, z_size);

            }
        }
        else
        {
            if(ICL_CC_ITEM_STATUS_SHOW == ui1_cc_val)
            {
                ui1_cc_val = ICL_CC_ITEM_STATUS_HIDE;
                a_icl_set(ICL_MAKE_ID(ICL_GRPID_CC_ITEM_STATUS, ICL_RECID_CC_ITEM_STATUS),
                          &ui1_cc_val, z_size);
            }
        }
    }

#ifdef APP_2K12_RETAIL_DEMO_MODE
    i4_ret = a_retail_mode_rcu_key_pre_handler(pt_event);
    if (NAVR_DO_NOT_CONTINUE == i4_ret)
    {
        return;
    }
#endif

    NAV_DEBUG_KEY( DBG_LOG_PRINT(("[NAV][KEY]{%s,%d} ui4_key_code:0x%X, ui4_key_event:0x%X\n",
            __FUNCTION__, __LINE__, ui4_key_code, ui4_key_event )); );

    /* hot key checking (jump to menu page) */
    if (a_menu_is_hot_key (ui4_key_code, ui4_key_event))
    {
        /* send ICL message to notify listener */
        if (BTN_3D == ui4_key_code)
        {
        #if 1//Cedric
            banner_custom_set_ch_state();
            a_banner_allow_to_show();
        #endif
            return ;
        }
#ifdef APP_CUST_HOT_KEY_EXPAND
        else if (BTN_CUSTOM_27 == ui4_key_code)
        {
            return ;
        }
#endif
        else
        {
            NAV_DEBUG_KEY( DBG_LOG_PRINT(("[NAV][KEY]{%s,%d} call a_menu_hot_key_handler(ui4_key_code:0x%X, ui4_key_event:%d,)\n",
                    __FUNCTION__, __LINE__, ui4_key_code, ui4_key_event )); );

            a_menu_hot_key_handler (ui4_key_code, ui4_key_event, NULL);
        }

        /* ignore this key in NAV as it will jump to MENU page */
        pt_event->ui4_data1 = WGL_MSG_KEY_DOWN ;
        pt_event->ui4_data2 = BTN_INVALID ;
        return ;
    }

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
    switch(ui4_key_code)
    {
    case BTN_FAVORITE:
        if(e_tshift_mode != APP_CFG_TSHIFT_MODE_OFF)
        {
            pt_event->ui4_data2 = BTN_PLAY_PAUSE;
        }
        break;
    case BTN_FAV_CH:
        if(e_tshift_mode != APP_CFG_TSHIFT_MODE_OFF)
        {
            pt_event->ui4_data2 = BTN_STOP;
        }
        break;
    case BTN_REPEAT:
        pt_event->ui4_data2 = BTN_TIMESHIFT;
        break;
    case BTN_FREEZE:
    {
        UINT32      ui4_tshift_status;
        TV_WIN_ID_T e_focus_win;
        SIZE_T      z_size = (SIZE_T)ICL_RECID_REC_TSHIFT_STATUS_SIZE;
        ISL_REC_T   t_isl_rec;
        SVL_REC_T   t_svl_rec;

        /* Check if timeshift is enabled */
        if(e_tshift_mode == APP_CFG_TSHIFT_MODE_OFF)
        {
            break;
        }

        /* Check if timeshift disk is ready */
        i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_REC, ICL_RECID_REC_TSHIFT_STATUS),
                           &ui4_tshift_status,
                           &z_size);
        if(i4_ret != ICLR_OK ||
           (ui4_tshift_status & ICL_RECID_REC_TSHIFT_STATUS_DISK_AVAIL) == 0)
        {
            break;
        }

        /* Check if it is TV source */
        i4_ret = nav_get_focus_id(&e_focus_win);
        if(i4_ret != NAVR_OK)
        {
            break;
        }

        i4_ret = nav_get_isl_rec(e_focus_win, &t_isl_rec);
        if(i4_ret != NAVR_OK)
        {
            break;
        }

        if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
        {
            break;
        }

        /* Check if it is DTV */
        i4_ret = nav_get_svl_rec(e_focus_win, &t_svl_rec);
        if(i4_ret != NAVR_OK ||
           t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
        {
            break;
        }

        /* Remap to timeshift play/pause */
        pt_event->ui4_data2 = BTN_PLAY_PAUSE;
        break;
    }
    default:
        break;
    }
#endif /* APP_NAV_REC_TSHIFT_SUPPORT */

#ifdef APP_NAV_REC_PVR_SUPPORT
    if (BTN_FAV_CH == pt_event->ui4_data2)
    {
        if(a_nav_rec_pvr_is_recording())
        {
            pt_event->ui4_data2 = BTN_STOP;
        }
    }
#endif

  if (pt_event->ui4_data2 == BTN_PRG_UP || pt_event->ui4_data2 == BTN_PRG_DOWN
    || pt_event->ui4_data2 == BTN_CURSOR_UP || pt_event->ui4_data2 == BTN_CURSOR_DOWN)
  {
        b_up_down_enable = TRUE;
        /*
        // up/down doesn't work when any ui is showing, up/down event will handle by menu, so donesn't filte menu
        if ((!((nav_get_active_component() == NAV_COMP_ID_SCREEN_SAVER) && a_scrn_svr_check_err_msg_for_format_not_support())) \
            && nav_any_component_visible())
        {
            b_up_down_enable = FALSE;
        }
        */

        if((nav_is_component_visible(NAV_COMP_ID_PWD_DLG) && nav_get_pwd_dlg_view_cannel_status()) || nav_is_component_visible(NAV_COMP_ID_CH_SELECT))
        {
            DBG_LOG_PRINT(("[nav variant] %s %d pwd:%d select:%d\n",__FUNCTION__,__LINE__,nav_is_component_visible(NAV_COMP_ID_PWD_DLG),nav_is_component_visible(NAV_COMP_ID_CH_SELECT)));
            b_up_down_enable = FALSE;
        }

      /* Check if it is TV source */
    TV_WIN_ID_T e_focus_win;
    ISL_REC_T   t_isl_rec;

      nav_get_focus_id(&e_focus_win);
      nav_get_isl_rec(e_focus_win, &t_isl_rec);
#ifdef APP_C4TV_SUPPORT
      if(INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type
         && DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
      {
          //not change key code
      }
      else
#endif
      if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
      {
        if (pt_event->ui4_data2 == BTN_CURSOR_UP || pt_event->ui4_data2 == BTN_CURSOR_DOWN)
        {
        }
        else
        {
          pt_event->ui4_data2 = BTN_INVALID;
        }
          b_up_down_enable = FALSE;
      }
  }

#ifdef CC_DISCRETE_REMOTE_CODE
    _discrete_key_pre_handler(pt_event->ui4_data1, &pt_event->ui4_data2);
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_rcu_key_post_handler
 * Description
 *      The API is used to do something after executing the remote controller
 *       key handler
 * Input arguments
 *      pt_this         a pointer points to the Navigator itself.
 *      pt_event        KEY event
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID nav_rcu_key_post_handler(
                    NAV_MODEL_T*                pt_this,
                    NAV_EVN_T*                  pt_event
                    )
{
    NAV_COMP_SET_T t_comp_visible_set = pt_this->t_comps_visible_set;

    t_comp_visible_set &= NAV_MAKE_NOT_COMP_ID_BIT_MASK(NAV_COMP_ID_SCRN_BLANK);

    if ((a_scrn_blank_get_state() == NAV_SCRN_BLANK_STATE_TIMER_PHASE1
            || a_scrn_blank_get_state() == NAV_SCRN_BLANK_STATE_TIMER_PHASE2)
        && t_comp_visible_set)
    {
        a_scrn_blank_reset();
    }

}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_pre_resume
 * Description
 *      The API is used to do something before navigator resume
 * Input arguments
 *      pt_this         a pointer points to the Navigator itself.
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK         it is ready to resume
 *      other           failure reason
 *---------------------------------------------------------------------------*/
INT32 nav_pre_resume(
            NAV_MODEL_T*        pt_this)
{
    INT32   i4_ret = NAVR_OK;
    TV_WIN_ID_T         e_focus_id;
    ISL_REC_T  t_isl_rec;
    i4_ret = a_tv_get_focus_win(&e_focus_id);
    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
#if 0
    /* CC performance is very bad on 1280x720 */
    if ((!a_cfg_custom_is_splash_show())&&(INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type))
    {
        i4_ret = c_wgl_flip_canvas(pt_this->t_nav_ctx.t_gui_res.h_cc_plane);
        if (i4_ret != WGLR_OK) {
            return i4_ret;
        }
    }
#endif

#ifdef APP_NAV_CUSTOM_PRE_RESUME
    nav_custom_pre_resume(pt_this);
#endif

    if (b_resume_for_active_componet)
    {
        b_resume_for_active_componet = FALSE;

        i4_ret = nav_grab_activation(e_g_comp_id);
        if (NAVR_OK != i4_ret)
        {
            return i4_ret;
        }
#ifdef  APP_NAV_USB_PLD
        if (NAV_COMP_ID_USB_PLD == e_g_comp_id)
        {
        #ifndef APP_C4TV_SUPPORT
            i4_ret = a_nav_usb_pld_show_uplg_dialog();
        #else
            i4_ret = a_nav_usb_pld_component_active();
        #endif

            if (NAVR_OK != i4_ret)
            {
                return i4_ret;
            }
        }
#endif
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_handle_am_default_key
 * Description
 *      must define APP_SUPPORT_AM_DEFAULT_KEY_HANDLER, then this function will
 *      be invoked
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
BOOL nav_handle_am_default_key(
                    NAV_MODEL_T*                pt_this,
                    BOOL                        b_before_notify_resume,
                    UINT32                      ui4_key
                    )
{
    switch(ui4_key) {
    case BTN_PRG_DOWN:
    case BTN_PRG_UP:
    case BTN_PREV_PRG:
    case BTN_FAV_CH:
    /*case BTN_INPUT_SRC:*//*DTV00433623*/
    case BTN_FAVORITE:
        /* keys related with SVC change should be handled before resume is sent */
        return (b_before_notify_resume == TRUE) ? TRUE : FALSE;
    default:
        /* other keys not related with SVC change should delay until resume is sent */
        return (b_before_notify_resume == TRUE) ? FALSE : TRUE;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_custom_svctx_config_show_snow_as_no_signal
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_custom_svctx_config_show_snow_as_no_signal(
                    VOID
                    )
{
#ifdef APP_SUPPORT_ANALOG_CH_SHOW_SNOW_AS_NO_SIGNAL
    INT32    i4_ret;
    HANDLE_T h_svctx;
    BOOL     b_show_snow_as_no_signal = TRUE;

    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_svctx_set(
                    h_svctx,
                    SVCTX_COMMON_SET_SHOW_SNOW_AS_NO_SIGNAL,
                    (VOID*)&b_show_snow_as_no_signal,
                    sizeof(BOOL)
                    );
    if (i4_ret != SVCTXR_OK) {
        return NAVR_FAIL;
    }

  #if (defined(APP_PIP_POP_CTRL) || defined(APP_VOG_SUPPORT))
    i4_ret = nav_get_svctx_handle(TV_WIN_ID_SUB, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_svctx_set(
                    h_svctx,
                    SVCTX_COMMON_SET_SHOW_SNOW_AS_NO_SIGNAL,
                    (VOID*)&b_show_snow_as_no_signal,
                    sizeof(BOOL)
                    );
    if (i4_ret != SVCTXR_OK) {
        return NAVR_FAIL;
    }
  #endif
#endif
    return NAVR_OK;
}

#ifdef APP_CUSTOMER_DEF_LOCK_CHK_LOGIC
static SVC_BLOCK_COND_T _nav_cust_svctx_block_check_fct(
                    SVC_BLOCK_CHECK_GUDIE_T     e_check_guide,    /* in  */
                    const CHAR*                 ps_src_name,      /* in  */
                    const SVL_REC_T*            pt_svl_rec,       /* in  */
                    const VOID*                 pv_evn_rating     /* in  */
                    )

{
    INT32 i4_ret;
    UINT8 ui1_rating_enable = FALSE;
    UINT8 ui1_val = RATING_ENABLED_STATUS_OFF;
    SIZE_T z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
            &ui1_val, &z_size);

    if (i4_ret != ICLR_OK)
    {
        ui1_val = FALSE;
    }

    i4_ret = a_cfg_get_rating_enabled (&ui1_rating_enable);

    if (i4_ret != APP_CFGR_OK)
    {
        ui1_rating_enable = FALSE;
    }

    if (ui1_val           == RATING_ENABLED_STATUS_OFF ||
        ui1_rating_enable == APP_CFG_RATING_ENABLED_OFF)
    {
        return SVC_BLOCK_COND_PASSED;
    }
    else
    {
        TV_WIN_ID_T         e_focus_id;
        ISL_REC_T           t_isl_rec;

        i4_ret = a_tv_get_focus_win(&e_focus_id);
        i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
        DBG_LOG_PRINT(("[NAV][%s %d] input id => 0x%x,video type => 0x%x\n",
            __FUNCTION__,__LINE__,
            t_isl_rec.e_src_type,
            t_isl_rec.t_avc_info.e_video_type));

        if(INP_SRC_TYPE_TV == t_isl_rec.e_src_type ||
           (INP_SRC_TYPE_AV == t_isl_rec.e_src_type && (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type || t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO )))
        {
           /* only TV  and  compsite  need check block status*/
           return a_tv_default_block_check_fct(e_check_guide,ps_src_name,pt_svl_rec,pv_evn_rating);

        }
        return SVC_BLOCK_COND_PASSED;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cust_svctx_config_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_cust_svctx_config_fct(VOID)
{
    INT32    i4_ret = NAVR_OK;
    HANDLE_T h_svctx = NULL_HANDLE;

    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_svctx);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    i4_ret = c_svctx_set(
                    h_svctx,
                    SVCTX_COMMON_SET_DEFALUT_BLOCK_CHECK_FCT,
                    (VOID*)_nav_cust_svctx_block_check_fct,
                    4
                    );
    if (i4_ret != SVCTXR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_get_svctx_handle(TV_WIN_ID_SUB, &h_svctx);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    i4_ret = c_svctx_set(
                    h_svctx,
                    SVCTX_COMMON_SET_DEFALUT_BLOCK_CHECK_FCT,
                    (VOID*)_nav_cust_svctx_block_check_fct,
                    4
                    );
    if (i4_ret != SVCTXR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_custom_check_inp_locked
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern BOOL nav_custom_check_inp_locked(
                    NAV_MODEL_T*                pt_this,
                    NAV_TV_WIN_T*               pt_tv_win,
                    ISL_REC_T*                  pt_isl_rec
                    )
{
    if(a_tv_custom_is_temp_unlock())
    {
        return FALSE;
    }

    if ((pt_isl_rec->ui4_attr_bits & ISL_ATTR_BIT_BLOCKED) > 0)
    {
        pt_tv_win->e_status |= NAV_STATUS_BIT_INP_SRC_BLOCKED;
        return TRUE;
    }

    if ((pt_tv_win->t_tv.t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED) > 0)
    {
        DBG_LOG_PRINT(("[nav variant] %d NAV_STATUS_BIT_CH_BLOCKED ui4_nw_mask:0x%x\n",\
            __LINE__,pt_tv_win->t_tv.t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask));
        pt_tv_win->e_status |= NAV_STATUS_BIT_CH_BLOCKED;
        return TRUE;
    }

    return FALSE;
}

#endif /* APP_CUSTOMER_DEF_LOCK_CHK_LOGIC */

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_custom_svctx_config
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_custom_svctx_config(
                    VOID
                    )
{
    _nav_custom_svctx_config_show_snow_as_no_signal();

#ifdef APP_CUSTOMER_DEF_LOCK_CHK_LOGIC
    _nav_cust_svctx_config_fct();
#endif

    return NAVR_OK;
}

#ifdef APP_VTRL_INP_SRC_SUPPORT
/*----------------------------------------------------------------------------
 * Name
 *      _nav_rmk_hdlr_init_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_rmk_hdlr_init_fct(VOID* pv_hdlr_usr_data)
{
    NAV_RMK_PRV_DATA_T* pt_this = (NAV_RMK_PRV_DATA_T*)pv_hdlr_usr_data;

    if(NULL == pt_this)
    {
        return RMKR_INV_ARG;
    }
    pt_this->e_handler_id = NAV_COMP_ID_LAST_VALID_ENTRY;
    pt_this->ui4_keycode = 0;

    return RMKR_OK;
}
/*----------------------------------------------------------------------------
 * Name
 *      _nav_rmk_hdlr_deinit_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _nav_rmk_hdlr_deinit_fct(VOID* pv_hdlr_usr_data)
{
    NAV_RMK_PRV_DATA_T* pt_this = (NAV_RMK_PRV_DATA_T*)pv_hdlr_usr_data;

    if(NULL == pt_this)
    {
        return RMKR_INV_ARG;
    }
    pt_this->e_handler_id = NAV_COMP_ID_LAST_VALID_ENTRY;
    pt_this->ui4_keycode = 0;

    return RMKR_OK;
}
/*----------------------------------------------------------------------------
* Name
*      _nav_cust_date_init
* Description
* Input arguments
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
static INT32 _nav_cust_date_init(VOID* pv_tag)
{
    APP_RMK_HDLR_INFO_T t_hdlr_info;
    INT32 i4_ret;

     /*create nav remote key handler*/
    t_hdlr_info.pf_init = _nav_rmk_hdlr_init_fct;
    t_hdlr_info.pf_deinit = _nav_rmk_hdlr_deinit_fct;
    t_hdlr_info.z_usr_data_size = sizeof(NAV_RMK_PRV_DATA_T);

    i4_ret = app_rmk_hdlr_create(&t_hdlr_info,
                                  (VOID**)&pv_g_rmk_hdlr);
    if (i4_ret != RMKR_OK)
    {
        pv_g_rmk_hdlr = NULL;
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
* Name
*      _nav_cust_date_deinit
* Description
* Input arguments
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
static INT32 _nav_cust_date_deinit(VOID* pv_tag)
{
    INT32  i4_ret;

    i4_ret = app_rmk_hdlr_destroy(pv_g_rmk_hdlr);
    pv_g_rmk_hdlr = NULL;

    return i4_ret;
}
#endif

#ifdef LINUX_TURNKEY_SOLUTION
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_cust_get_ap_id
 * Description
 *
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static UINT32 _nav_cust_get_ap_id(
    const char*                 ps_app,
    VOID*                       pv_tag,
    NAV_COEXIST_APP_ID_MSAK_T*  pt_app_id_mask)
{
    if(0 == c_strcmp(ps_app, MENU_NAME))
    {
        *pt_app_id_mask =  NAV_COEXIST_MAKE_APP_ID_BIT_MASK(0);
    }
    else if(0 == c_strcmp(ps_app, MSCVT_NAME))
    {
        *pt_app_id_mask =  NAV_COEXIST_MAKE_APP_ID_BIT_MASK(1);
    }
    else if(0 == c_strcmp(ps_app, WZD_NAME))
    {
        *pt_app_id_mask =  NAV_COEXIST_MAKE_APP_ID_BIT_MASK(2);
    }
    else if(0 == c_strcmp(ps_app, MMP_NAME))
    {
        *pt_app_id_mask =  NAV_COEXIST_MAKE_APP_ID_BIT_MASK(3);
    }
    else if(0 == c_strcmp(ps_app, WFD_NAME))
    {
        *pt_app_id_mask =  NAV_COEXIST_MAKE_APP_ID_BIT_MASK(4);
    }
    else
    {
        *pt_app_id_mask = NAV_COEXIST_EMPYT_APP_ID_BIT_MASK;
    }

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_system_key_cb
 * Description
 *
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static BOOL _nav_system_key_cb (UINT32 ui4_evt_code)
{
    UINT32      ui4_key_code = IOM_GET_EVT_GRP_ID(ui4_evt_code);

    /* for system key */
    if (a_scrn_blank_get_state() == NAV_SCRN_BLANK_STATE_BLANK)
    {
        if (IOM_GET_EVT_SRC (ui4_evt_code) == KEY_SRC_FRONT_PANEL
            && BTN_POWER == ui4_key_code)
        {
            /* Do nothing */
        }
        else
        {
            //nav_grab_activation(NAV_COMP_ID_SCRN_BLANK);
            nav_request_context_switch(a_scrn_blank_act,
                                        NULL,
                                        NULL,
                                        NULL);
            return FALSE;
        }
    }

#ifndef APP_NAV_CUSTOM_RCU_KEY_PRE_HANDLER
    if (a_app_nav_custom_rcu_key_pre_handler())
#endif
    {
        BOOL   b_process = TRUE;
        b_process = nav_custom_system_key_cb(ui4_evt_code);
        if(b_process == FALSE)
        {
            return FALSE;
        }
    }

#ifndef APP_EPG_SUPPORT
    if (BTN_EPG == ui4_key_code)
    {
        NAV_EVN_T t_event;

        t_event.ui4_msg_id = NAV_KEY_EVENT;
        t_event.ui4_data1  = WGL_MSG_KEY_DOWN;
        t_event.ui4_data2  = ((UINT32)BTN_PRG_INFO);
        t_event.ui4_data3  = (UINT32)NULL;
        t_event.ui4_data4  = IOM_GET_EVT_SRC(ui4_evt_code);

        nav_send_msg(&t_event);
        return FALSE;
    }
#endif
    return TRUE;
}

#ifdef APP_ENTER_FAC_BY_NAV_SECRET_KEY
VOID _fac_menu_key_seq_handler(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    fac_menu_key_seq_handler();
}

VOID _fac_mode_key_seq_handler(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    fac_mode_key_seq_handler();
}

VOID _fac_menu_key_sequence_nfy_fct(VOID)
{
    nav_request_context_switch(_fac_menu_key_seq_handler,
                               NULL,
                               NULL,
                               NULL);
}

VOID _fac_menu_key_sequence_nfy_fct(VOID)
{
    nav_request_context_switch(_fac_mode_key_seq_handler,
                               NULL,
                               NULL,
                               NULL);
}
#endif

extern UINT16  ui2_g_audio_stream_idx;
#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      _def_audio_strm_comp_filter
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static BOOL _def_audio_strm_comp_filter (
    UINT16                      ui2_num_recs,
    UINT16                      ui2_idx,
    const STREAM_COMP_ID_T*     pt_comp_id,
    const SCDB_REC_T*           pt_scdb_rec,
    VOID*                       pv_tag)
{
    if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG)
    {
        UINT16 ui2_comp_idx = STRM_COMP_FILTER_GET_COMP_IDX(ui2_idx);
        if (ui2_comp_idx >= NAV_AUDIO_STRM_COMP_MAX_COUNT)
        {
            return FALSE;
        }
        if(ui2_num_recs == ui2_idx)
        {
            /* ui2_g_audio_stream_idx = 0; */
            return TRUE;
        }
        else
        {
            return (ui2_idx == ui2_g_audio_stream_idx) ? TRUE : FALSE;
        }
    }
    else
    {
        /* if not MEPG audio stream, use the first one */
        return TRUE;
    }
}

static BOOL _next_audio_strm_comp_filter(
    UINT16                      ui2_num_recs,
    UINT16                      ui2_idx,
    const STREAM_COMP_ID_T*     pt_comp_id,
    const SCDB_REC_T*           pt_scdb_rec,
    VOID*                       pv_fltr_tag)
{
    /* Note: the following algorithm is under one assumption: ui2_idx is from 0 to (ui2_num_recs-1)*/
    switch(pt_comp_id->e_type) {
    case ST_AUDIO:
        if(ui2_idx == ui2_num_recs)
        {
            ui2_g_audio_stream_idx = 0;
            return TRUE;
        }
        if(ui2_g_audio_stream_idx + 1 >= ui2_num_recs &&
           ui2_idx == 0)
        {
            ui2_g_audio_stream_idx = 0;
            return TRUE;
        }
        else if(ui2_g_audio_stream_idx + 1 == ui2_idx)
        {
            ui2_g_audio_stream_idx = ui2_g_audio_stream_idx + 1;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    case ST_VIDEO:
        break;
    case ST_CLOSED_CAPTION:
        break;
    case ST_TELETEXT:
        break;
    case ST_SUBTITLE:
        break;
    default:
        break;
    }
    return FALSE;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      nav_custom_register_components
 * Description
 *      The API is used to register all components
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 nav_custom_register_components(
                    VOID
                    )
{
    INT32 i4_ret;
#ifdef APP_VTRL_INP_SRC_SUPPORT
    NAV_CSTM_DATA_INFO_T t_cstm_data_info;
#endif

    {
        AMB_REGISTER_INFO_T* pt_reg = a_amb_get_register_info(APP_NAME);

        a_amb_lock();
        pt_reg->pf_system_key_cb = _nav_system_key_cb;
        a_amb_unlock();
    }

    i4_ret = _nav_custom_svctx_config();
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
    i4_ret = init_custom_fonts();
    if(NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
#endif

    /* NAV_COMP_ID_BANNER */
    i4_ret = a_banner_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_banner_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    /* NAV_COMP_ID_BURNING_MODE */
    CH_SELECT_VIEW_T ch_select_view_t;
    a_ch_select_view_build(&ch_select_view_t);

    i4_ret = a_ch_select_register(ch_select_view_t);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_ch_select_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    /* NAV_COMP_ID_CH_LIST */
    i4_ret = a_ch_lst_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_ch_lst_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

#ifdef APP_C4TV_SUPPORT
    i4_ret = a_c4tv_apron_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_c4tv_apron_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifndef APP_NO_PWD_DLG
    /* NAV_COMP_ID_PWD_DLG */
    i4_ret = a_pwd_dlg_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_pwd_dlg_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_VIDEO_SEL
    /* NAV_COMP_ID_VIDEO_SEL */
    i4_ret = a_video_sel_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_video_sel_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_MOVABLE_SCREEN_SAVER
    /* NAV_COMP_ID_SCREEN_SAVER */
    i4_ret = a_scrn_svr_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_scrn_svr_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

    /* NAV_COMP_ID_INPUT_SRC */
    i4_ret = a_input_src_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_input_src_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

#if (defined(APP_PIP_POP_CTRL) || defined(APP_VOG_SUPPORT))
    /* NAV_COMP_ID_PIP_POP */
    i4_ret = a_pop_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_pop_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

    /* NAV_COMP_ID_AUDIO_SEL */
    i4_ret = a_audio_info_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_audio_info_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

#ifndef APP_DVBT_SUPPORT
    /* NAV_COMP_ID_CC_SEL */
    i4_ret = a_cc_info_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_cc_info_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#else
    /* NAV_COMP_ID_CC_SEL */
    i4_ret = a_sbti_register(NULL);
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"a_sbti_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_VOLUME_CTRL
    /* NAV_COMP_ID_VOL_CTRL */
    i4_ret = a_vol_ctrl_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_vol_ctrl_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif



    /* NAV_COMP_ID_BURNING_MODE */
    i4_ret = a_burning_mode_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_burning_mode_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    /* NAV_COMP_ID_ZOOM_PAN */
#if  (!defined(APP_DISABLE_ZOOM))
    i4_ret = a_zoom_pan_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_zoom_pan_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

    /* NAV_COMP_ID_SLEEP */
    i4_ret = a_nav_sleep_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_sleep_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

#ifdef APP_USB_INSTALL_ULPK_SUPPORT
    /* NAV_COMP_ID_ULPK */
    i4_ret = a_nav_ulpk_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_ulpk_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_WR_UPDATER_UI_SUPPORT
    /* NAV_COMP_ID_ULPK */
    i4_ret = a_nav_wr_updater_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_wr_updater_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_FRZ_SUPPORT
    i4_ret = a_nav_frz_info_register(NULL);
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"a_nav_frz_info_register() failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_PWR_SUPPORT
    i4_ret = a_nav_power_register(NULL);
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"a_nav_power_register() failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_DCR_SUPPORT
    /* NAV_COMP_ID_DCR_AGENT */
    i4_ret = a_nav_dcr_register();
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"nav_register_comp(NAV_COMP_ID_DCR_AGENT) failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif
#ifdef APP_TTX_SUPPORT
    /* NAV_COMP_ID_TTX */
    i4_ret = a_nav_teletext_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_teletext_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_SCART_MONITOR
    i4_ret = a_nav_scart_monitor_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_scart_monitor failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_RETAIL_MODE_SUPPORT
    /* NAV_COMP_ID_RETAIL_MODE */
    i4_ret = a_nav_retail_mode_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_retail_mode_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#if 0
    i4_ret = a_nav_3d_setting_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_3d_setting_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef VIEWPORT_SUPPORT
        /* NAV_VIEWPORT_SUPPORT */
        i4_ret = a_nav_viewport_register();
        if (i4_ret != NAVR_OK) {
            DBG_ERROR((_ERROR_HEADER"a_nav_viewport_register failed, ret=%d\r\n", i4_ret));
            return i4_ret;
        }
#endif

#if NAV_SUPPORT_PIC_MODE
    /* NAV_COMP_ID_PICTURE_EFFECT */
    NAV_DEBUG_PIC_MODE( DBG_LOG_PRINT(("[NAV][PIC_MODE]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
    i4_ret = a_nav_pic_mode_register(NULL, NAV_PIC_MODE_STYLE_SINGLE_SELECT_LIST);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_pic_mode_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#if NAV_SUPPORT_ASPECT_RATIO
    /* NAV_COMP_ID_SCREEN_MODE */
    NAV_DEBUG_ASPECT_RADIO( DBG_LOG_PRINT(("[NAV][ASPECT]{%s,%d} \n", __FUNCTION__, __LINE__ )); );
    i4_ret = a_nav_screen_mode_register(NULL, NAV_SCREEN_MODE_STYLE_SINGLE_SELECT_LIST);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_screen_mode_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_CAMERA_PLUG_SUPPORT
       /* NAV_COMP_ID_ULPK */
       i4_ret = a_nav_camera_register ();
       if (i4_ret != NAVR_OK)
       {
           DBG_ERROR((_ERROR_HEADER"a_nav_camera_pld_register failed, ret=%d\r\n", i4_ret));
           return i4_ret;
       }
#endif

    /* NAV_COMP_ID For ODM register */
    nav_custom_register_components_odm();

#ifdef APP_NAV_MISC_COMP
    i4_ret = a_nav_misc_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_misc_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_SINGLE_RF_SCAN
    i4_ret = a_nav_single_scan_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_single_scan_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_CEC_SUPPORT
    /* NAV_COMP_ID_VIDEO_SEL */
    i4_ret = a_nav_cec_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_cec_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif


#ifdef CC_DISCRETE_REMOTE_CODE
    /* Override the default handler */
    nav_set_rcu_key_default_handler(_discrete_key_handler_fct);
#else
    nav_set_rcu_key_default_handler(_rcu_key_default_handler_fct);
#endif

#ifdef APP_AUD_LANUAGE_CUSTOM_SUPPORT
nav_replace_default_strm_filter(TV_WIN_ID_MAIN,
                ST_AUDIO,
                _def_audio_strm_comp_filter,
                NULL);

nav_replace_next_strm_filter(ST_AUDIO,
               _next_audio_strm_comp_filter,
               NULL);
#endif

#ifdef APP_UPG_SUPPORT
#ifndef LINUX_TURNKEY_SOLUTION
    /* NAV_COMP_ID_UPG */
    i4_ret = a_nav_upg_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_upg_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#else
    /* NAV_COMP_ID_UPDATER */
    i4_ret = a_nav_updater_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_updater_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif
#endif

    i4_ret = a_nav_flicker_register ();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_flicker_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    i4_ret = a_nav_dialog_register ();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_dialog_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

#ifdef APP_NAV_USB_PLD
    i4_ret = a_nav_usb_pld_register ();
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"a_nav_usb_pld_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_REC_SUPPORT
    /* NAV_COMP_ID_RECORD */
    i4_ret = a_nav_rec_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_rec_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#ifdef APP_NAV_REC_TSHIFT_SUPPORT
    i4_ret = a_nav_rec_register_subcomp(NAV_REC_SUBCOMP_ID_TIMESHIFT);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_rec_register_subcomp failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
    i4_ret = a_nav_rec_register_subcomp(NAV_REC_SUBCOMP_ID_PVR);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_rec_register_subcomp failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#endif

#ifdef APP_NAV_AUD_ONLY_SUPPORT
        i4_ret = a_nav_aud_only_register(NULL);
        if (i4_ret != NAVR_OK) {
            DBG_ERROR((_ERROR_HEADER"a_nav_aud_only_register failed, ret=%d\r\n", i4_ret));
            return i4_ret;
        }
#endif /*APP_NAV_AUD_ONLY_SUPPORT*/

#ifdef APP_NAV_MMP_LAUNCHER_SUPPORT
        i4_ret = a_nav_mmlr_register();
        if(NAVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"a_nav_mmlr_register failed, ret=%d\r\n", i4_ret));
            return i4_ret;
        }
#endif

#ifdef APP_VTRL_INP_SRC_SUPPORT
    /*register nav custom data info*/
    t_cstm_data_info.pf_cstm_init = _nav_cust_date_init;
    t_cstm_data_info.pf_cstm_deinit = _nav_cust_date_deinit;
    t_cstm_data_info.pv_tag = (VOID*)0;

    i4_ret = nav_reg_custom_data_info(&t_cstm_data_info);
    if(NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
#endif

#ifdef APP_NAV_REC_PVR_SCH_SUPPORT
    /* NAV_COMP_ID_REMINDER */
    i4_ret = a_nav_reminder_register(NULL);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_reminder_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

    i4_ret = a_si_register();
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"a_si_register failed, err =%d\r\n", i4_ret));
        return i4_ret;
    }

#ifdef APP_NAV_COMP_INFO_BAR
    i4_ret = a_info_bar_register();

    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"a_info_bar_register failed, err =%d\r\n", i4_ret));
        return i4_ret;
    }
#endif
#if 1
    i4_ret = a_nav_via_dlg_register();
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"a_info_bar_register failed, err =%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#if 1
    i4_ret = a_scrn_blank_register();
    if(NAVR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"a_scrn_blank_register failed, err =%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

    /* NAV_COMP_ID_REVOLT_INFO */
    DBG_LOG_PRINT(("wff bef a_nav_revolt_info_register \n"));
    i4_ret = a_nav_revolt_info_register(NULL, NAV_REVOLT_INFO_STYLE_LISTBOX);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_revolt_info_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    /* NAV_COMP_ID_LINK */
    i4_ret = a_nav_link_mode_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_link_mode_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    /* NAV_COMP_ID_LONG_PRESS */
    i4_ret = a_nav_long_press_register(); //for long key press(5s)
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_nav_link_mode_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    /* NAV_COMP_ID_TEST_PATTERN */
    i4_ret = a_nav_test_pattern_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_test_pattern_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

    /* NAV_COMP_ID_PPP */
    i4_ret = a_nav_ppp_register();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"a_test_pattern_register failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }

#ifdef APP_ZOOM_MODE_SUPPORT
    /* NAV_COMP_ID_ZOOM */
    i4_ret = a_nav_zoom_register();
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR((_ERROR_HEADER"a_nav_zoom_register() failed, ret=%d\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef LINUX_TURNKEY_SOLUTION
     /*register coexist table and resume table*/
    {
        NAV_COEXIST_APP_TABLE_SET_PARAM_T   t_table_param;

        /*reset set parameter*/
        NAV_COEXIST_APP_TABLE_SET_PARAM_ZERO(t_table_param);

        /*setting for coexist table*/
        NAV_COEXIST_APP_TABLE_SET_FIELD_VALID(t_table_param.t_valid_field, NAV_COEXIST_APP_TABLE_SET_FIELD_COEXIST);
        t_table_param.at_coexist_recs = at_g_coexist_recs;
        t_table_param.ui4_coexist_count = sizeof(at_g_coexist_recs)/sizeof(NAV_COEXIST_APP_REC_T);

        /*setting for component resume table*/
        NAV_COEXIST_APP_TABLE_SET_FIELD_VALID(t_table_param.t_valid_field, NAV_COEXIST_APP_TABLE_SET_FIELD_RESUME);
        t_table_param.at_resume_recs = at_g_comp_recs;
        t_table_param.ui4_resume_count = sizeof(at_g_comp_recs)/sizeof(NAV_COEXIST_APP_REC_T);


        /*setting for callback function*/
        NAV_COEXIST_APP_TABLE_SET_FIELD_VALID(t_table_param.t_valid_field, NAV_COEXIST_APP_TABLE_SET_GET_AP_FCT);
        t_table_param.pf_get_ap_id = _nav_cust_get_ap_id;
        t_table_param.pv_tag = NULL;

        i4_ret = nav_set_coexist_app_table(&t_table_param);
        if(NAVR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif

#ifdef APP_ENTER_FAC_BY_NAV_SECRET_KEY
{
    UINT16  ui2_fac_menu_key_id = 0;
    UINT16  ui2_fac_mode_key_id = 0;

    i4_ret = a_key_seq_reg(aui4_fac_menu_key_list,
                           FAC_MENU_KEY_SIZE,
                           _fac_menu_key_sequence_nfy_fct,
                           NULL,
                           &ui2_fac_menu_key_id);

    i4_ret = a_key_seq_reg(aui4_fac_mode_key_list,
                           FAC_MODE_KEY_SIZE,
                           _fac_menu_mode_key_sequence_nfy_fct,
                           NULL,
                           &ui2_fac_mode_key_id);
}
#endif

    DBG_LOG_PRINT(("<a_nav_revolt_misc_register> file=%s\r\n", __FILE__));
    //NAV_COMP_ID_REVOLT_MISC
    i4_ret = a_nav_revolt_misc_register ();
    if (i4_ret != NAVR_OK)
    {
      DBG_ERROR((_ERROR_HEADER"a_nav_revolt_misc_registers failed, ret=%d\r\n", i4_ret));
      return i4_ret;
    }

    DBG_LOG_PRINT(("<a_nav_tuner_setup_register> file=%s\r\n", __FILE__));
    //NAV_COMP_ID_TUNNER_SETUP
    i4_ret = a_nav_tuner_setup_register ();
    if (i4_ret != NAVR_OK)
    {
      DBG_ERROR((_ERROR_HEADER"a_nav_tuner_setup_register failed, ret=%d\r\n", i4_ret));
      return i4_ret;
    }

    return NAVR_OK;
}

#if defined(APP_CC_WITH_SOLE_OSD_PLANE)
/*-----------------------------------------------------------------------------
 * Name: nav_get_cc_osd_plane_index
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: current channel number
 *-----------------------------------------------------------------------------*/
UINT16 nav_get_cc_osd_plane_index(VOID)
{
    /* use other OSD plane for CC, hard-coded */
#ifndef APP_NAV_MOVE_CC_TO_SECOND_PLANE
    return a_util_get_default_osd_plane_index();
#else /* Move to second plane */
    return 0;
#endif
}
/*-----------------------------------------------------------------------------
 * Name: nav_set_cc_canvas_config
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: current channel number
 *-----------------------------------------------------------------------------*/
extern UINT32 sys_cust_get_cc_width( VOID );
extern UINT32 sys_cust_get_cc_height( VOID );
INT32 nav_set_cc_canvas_config(
                    HANDLE_T                    h_cc_plane,
                    HANDLE_T*                   ph_cc_canvas
                    )
{
    WGL_CANVAS_CFG_T t_cfg = {0};
    INT32            i4_ret;

    if(c_handle_valid(h_cc_plane) == FALSE || ph_cc_canvas == NULL) {
        return NAVR_INV_ARG;
    }

    t_cfg.ui4_flag     = WGL_CANVAS_CFG_AUTOSCALE | WGL_CANVAS_CFG_COLORMODE | WGL_CANVAS_CFG_WIDTH | WGL_CANVAS_CFG_HEIGHT;
    t_cfg.b_auto_scale = TRUE;

#if defined(APP_COLOR_MODE_PALLET)
    t_cfg.e_clr_mode   = GL_COLORMODE_ARGB_CLUT8;
#else
    t_cfg.e_clr_mode   = GL_COLORMODE_ARGB_D8888;
#endif

    t_cfg.ui4_width    = sys_cust_get_cc_width();
    t_cfg.ui4_height   = sys_cust_get_cc_height();

    /* cc canvas is read-only */
    i4_ret = c_wgl_get_canvas_ex(h_cc_plane, &t_cfg, ph_cc_canvas);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

INT32 nav_enable_cc_plane(HANDLE_T h_cc_plane, BOOL b_nav_resume)
{
    CHAR           s_app_name[APP_NAME_MAX_LEN + 1] = {0};
    GL_HPLANE_T    h_cc_canvas = NULL_HANDLE;
    TV_WIN_ID_T         e_focus_id;
    ISL_REC_T           t_isl_rec;

    a_tv_get_focus_win(&e_focus_id);
    a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);

    c_wgl_get_canvas_plane(h_cc_plane, &h_cc_canvas);
    a_am_get_next_active_app(s_app_name);
    DBG_LOG_PRINT((" nav_enable_cc_plane next active app is %s,b_nav_resume = %d,t_isl_rec.e_src_type = %d casting state is %d\n",
        s_app_name,
        b_nav_resume,
        t_isl_rec.e_src_type,
        a_c4tv_apron_get_cast_running_state()));
    if(INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type)
    {
        if(c_strncmp(s_app_name,"menu",strlen("menu")) == 0)
        {
            c_gl_plane_enable(h_cc_canvas, TRUE);
        }
        else
            c_gl_plane_enable(h_cc_canvas, b_nav_resume);
    } else {
        c_gl_plane_clear(h_cc_canvas);
        c_gl_plane_enable(h_cc_canvas, FALSE);
    }
    return 0;
}
#endif /* APP_CC_WITH_SOLE_OSD_PLANE */
#ifdef APP_SUPPORT_SECOND_OSD_PLANE
/*-----------------------------------------------------------------------------
 * Name: nav_custom_get_second_osd_plane_caps
 *
 * Description:
 *      The API is used to provide the desired capability for searching
 *      second OSD plane
 * Inputs:
 *      None
 * Outputs:
 *      pt_desired_pln_caps     The desired plane capability
 * Returns: current channel number
 *      NAVR_OK      the routine is successfully
 *      NAVR_FAIL    the routine is failed
 *-----------------------------------------------------------------------------*/
INT32 nav_custom_get_second_osd_plane_caps(
                    GL_PLANE_CAPS_T*            pt_desired_pln_caps
                    )
{
    INT32 i4_ui_osd_order;
    INT32 i4_ret;

    if (pt_desired_pln_caps == NULL) {
        return NAVR_INV_ARG;
    }

    i4_ret = c_gl_plane_get_order(nav_get_ui_osd_plane(), &i4_ui_osd_order);
    if (i4_ret != GLR_OK) {
        return NAVR_FAIL;
    }

    /* should customize by spec. If not need, please set to 0 */
    /* if (i4_ui_osd_order + 1) over the IC spec ??? */
    pt_desired_pln_caps->ui4_cm_caps   = GL_CMCAP_ARGB_CLUT8;
    pt_desired_pln_caps->ui4_z_mask    = 0x00000001 << (i4_ui_osd_order+1);
    pt_desired_pln_caps->ui4_func_caps = 0; /* don't want to compare */

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: nav_custom_set_second_osd_plane_canvas_config
 *
 * Description:
 *      The API is used to configure the second OSD plane and canvas
 * Inputs
 *      h_second_plane      The second OSD plane
 * Outputs
 *      ph_second_canvas    The resulted canvas
 * Returns
 *      NAVR_OK      the routine is successfully
 *      NAVR_FAIL    the routine is failed
 *-----------------------------------------------------------------------------*/
INT32 nav_custom_set_second_osd_plane_canvas_config(
                    HANDLE_T                    h_second_plane,
                    HANDLE_T*                   ph_second_canvas
                    )
{
    WGL_CANVAS_CFG_T t_cfg = {0};
    INT32            i4_ret;
    INT32            i4_ui_osd_order;
    INT32            i4_second_osd_order;
    GL_COLOR_T       at_null_palette[] = { GL_COLOR_DEF(0, 0, 0, 0), /* palette entry 0 */ };

    if(c_handle_valid(h_second_plane) == FALSE || ph_second_canvas == NULL) {
        return NAVR_INV_ARG;
    }

    /* the following is the sample code for set the second osd plane & canvas's
     * configuration
     *  1. second OSD plane is behind ui OSD plane
     *  2. second OSD plane's canvas is 8bit, 720 x 576, auto-scale
     *
     * this API is invoked by nav core player, as the function is invoked,
     * this UI osd plane is already created.
     */

    /* logic to set second OSD plane's order */
    i4_ret = c_gl_plane_get_order(nav_get_ui_osd_plane(), &i4_ui_osd_order);
    if (i4_ret != GLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_gl_plane_get_order(h_second_plane, &i4_second_osd_order);
    if (i4_ret != GLR_OK) {
        return NAVR_FAIL;
    }

    if (i4_ui_osd_order >= i4_second_osd_order) {
        /* if (i4_ui_osd_order + 1) over the IC spec ??? */
        i4_ret = c_gl_plane_reorder(
                        h_second_plane,
                        GL_REORDER_ABSOLUTE,
                        i4_ui_osd_order + 1
                        );
        if (i4_ret != GLR_OK) {
            return NAVR_FAIL;
        }
    }

    /* Because the canvas_ex of the 2nd OSD plane doesn't contain a default palette,
       associate a dummy one to make sure MHEG5 to work properly. */
    i4_ret = c_gl_palette_create(GL_COLORMODE_ARGB_CLUT8,
                                 1,
                                 at_null_palette,
                                 &t_cfg.h_palette);
    if (i4_ret != GLR_OK) {
        return NAVR_FAIL;
    }


    /* logic to configure second osd plane's canvas */
    t_cfg.ui4_flag     = WGL_CANVAS_CFG_AUTOSCALE
                       | WGL_CANVAS_CFG_COLORMODE
                       | WGL_CANVAS_CFG_WIDTH
                       | WGL_CANVAS_CFG_HEIGHT
                       | WGL_CANVAS_CFG_PALETTE;

    t_cfg.b_auto_scale = TRUE;
    t_cfg.e_clr_mode   = GL_COLORMODE_ARGB_CLUT8;
    t_cfg.ui4_width    = 720;
    t_cfg.ui4_height   = 576;

    /* set the parameter to WGL: this c_wgl_get_canvas_ex() is SET operation */
    i4_ret = c_wgl_get_canvas_ex(h_second_plane, &t_cfg, ph_second_canvas);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif /* APP_SUPPORT_SECOND_OSD_PLANE */

#ifdef APP_VTRL_INP_SRC_SUPPORT
/*----------------------------------------------------------------------------
* Name
*      nav_rmk_hdlr_act_fct
* Description
*
* Input arguments
*      None
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
static INT32 nav_rmk_hdlr_act_fct(VOID* pv_hdlr_usr_data, UINT32 ui4_keycode)
{
    NAV_RMK_PRV_DATA_T* pt_this = (NAV_RMK_PRV_DATA_T*)pv_hdlr_usr_data;
    NAV_COMP_ID_T     e_handler_id;

    if(NULL == pt_this)
    {
        return RMKR_INV_ARG;
    }

    if(nav_rcu_key_handler_ex(ui4_keycode,TRUE,&e_handler_id))
    {
    pt_this->ui4_keycode = ui4_keycode;
    pt_this->e_handler_id = e_handler_id;
        return RMKR_OK;
    }

    return RMKR_NO_ACTION;
}
/*----------------------------------------------------------------------------
* Name
*      nav_rmk_hdlr_deact_fct
* Description
*
* Input arguments
*      None
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
static INT32 nav_rmk_hdlr_deact_fct(VOID* pv_hdlr_usr_data, UINT32 ui4_keycode)
{
    NAV_RMK_PRV_DATA_T* pt_this = (NAV_RMK_PRV_DATA_T*)pv_hdlr_usr_data;

    if(NULL == pv_hdlr_usr_data)
    {
        return NAVR_FAIL;
    }
    if(NAV_COMP_ID_LAST_VALID_ENTRY != pt_this->e_handler_id)
    {
        nav_return_activation(pt_this->e_handler_id);
        nav_hide_component(pt_this->e_handler_id);
    }

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
* Name
*      _nav_rmk_hdlr_is_ret_key
* Description
*
* Input arguments
*      None
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
INT32 nav_rmk_hdlr_is_ret_key(
    UINT32                      ui4_keycode,
    BOOL*                       pb_is_ret,
    HANDLE_T*                   ph_new_focus)
{
    VOID*  pt_this = pv_g_rmk_hdlr;
    INT32                       i4_ret;

    if(NULL == pt_this)
    {
        return NAVR_FAIL;
    }
    if(NULL == pb_is_ret || NULL == ph_new_focus)
    {
        return NAVR_INV_ARG;
    }

    do
    {
        i4_ret = app_rmk_hdlr_is_return_event(pt_this,
                                                      ui4_keycode,
                                                      pb_is_ret,
                                                      ph_new_focus);
        if(RMKR_OK != i4_ret)
        {
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = NAVR_OK;
    } while(0);

    return i4_ret;
}

/*----------------------------------------------------------------------------
* Name
*      nav_rmk_hdlr_ret
* Description
*
* Input arguments
*      None
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
INT32 nav_rmk_hdlr_ret(
    const APP_RMK_RET_INFO_T* pt_info)
{
    VOID*  pt_this = pv_g_rmk_hdlr;
    INT32                       i4_ret;

    if(NULL == pt_this)
    {
        return NAVR_FAIL;
    }

    if(NULL == pt_info)
    {
        return NAVR_INV_ARG;
    }

    do
    {
       i4_ret = app_rmk_hdlr_return_focus(pt_this,pt_info);
       if(RMKR_OK != i4_ret)
       {
           i4_ret = NAVR_FAIL;
           break;
       }

       i4_ret = NAVR_OK;
    } while(0);

    return i4_ret;
}
/*----------------------------------------------------------------------------
* Name
*      _nav_remote_key_canceler
* Description
*
* Input arguments
*      None
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
static VOID nav_remote_key_canceler(
    VOID*                       pv_ui4_keycode,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2)
{
    INT32  i4_ret;
    VOID*  pt_this = pv_g_rmk_hdlr;

    if(NULL == pt_this)
    {
        return;
    }

    do
    {
        i4_ret = app_rmk_hdlr_stop_req(pt_this,
                                            nav_rmk_hdlr_deact_fct);
        if(RMKR_OK != i4_ret)
        {
            break;
        }

    } while(0);

    return;
}
/*----------------------------------------------------------------------------
* Name
*      nav_remote_key_handler
* Description
*
* Input arguments
*      None
* Output arguments
*      None
* Returns
*      None
*----------------------------------------------------------------------------*/
static VOID nav_remote_key_handler(
    VOID*                       pv_ui4_keycode,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2)
{
    VOID*  pt_this = pv_g_rmk_hdlr;
    UINT32                      ui4_keycode = (UINT32)pv_ui4_keycode;
    INT32                       i4_ret;

    if(NULL == pt_this)
    {
        return;
    }

    do
    {
        i4_ret = app_rmk_hdlr_run_req(pt_this,
                                   t_g_navigator.h_app,
                                   ui4_keycode,
                                   nav_rmk_hdlr_act_fct);
        if(i4_ret != RMKR_OK)
        {
            break;
        }

    } while(0);

    return;
}

/*----------------------------------------------------------------------------
 * Name
 *      a_nav_handle_remote_key
 * Description
 *
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
INT32 a_nav_handle_remote_key(
    UINT32                      ui4_keycode,
    const APP_RMK_REQ_INFO_T*   pt_req_info)
{
    VOID*  pt_this = pv_g_rmk_hdlr;
    INT32                       i4_ret;

    if(NULL == pt_this)
    {
        return NAVR_FAIL;
    }

    i4_ret = app_rmk_hdlr_receive_req(pt_this,pt_req_info);
    if(i4_ret != RMKR_OK)
    {
        return NAVR_FAIL;
    }

    nav_request_context_switch(nav_remote_key_handler,
                               (VOID*)ui4_keycode,
                               NULL,
                               NULL);

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name
 *      a_nav_cancel_remote_key
 * Description
 *
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
INT32 a_nav_cancel_remote_key(
    UINT32                      ui4_keycode)
{
    VOID*  pt_this = pv_g_rmk_hdlr;
    BOOL                        b_cancel;
    INT32                       i4_ret;

    if(NULL == pt_this)
    {
        return NAVR_FAIL;
    }

    i4_ret = app_rmk_is_req_received(pt_this,&b_cancel);
    if(RMKR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    if(b_cancel)
    {
        nav_request_context_switch(nav_remote_key_canceler,
                                   (VOID*)ui4_keycode,
                                   NULL,
                                   NULL);
    }

    return NAVR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name
 *      _nav_active_component
 * Description
 *
 * Input arguments
 *      NAV_COMP_ID_T
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK
 *----------------------------------------------------------------------------*/
INT32 _nav_active_component(NAV_COMP_ID_T e_comp_id)
{
    INT32       i4_ret;
    CHAR        s_act_app_name[APP_NAME_MAX_LEN +1] = {0};

    i4_ret = a_am_get_active_app(s_act_app_name);

    if ((i4_ret != AMR_OK) ||
        (c_strcmp(s_act_app_name, WZD_NAME) == 0))
    {
        return NAVR_NO_ACTION;
    }

    if (c_strcmp(s_act_app_name, NAV_NAME) != 0)
    {
        b_resume_for_active_componet = TRUE;
        e_g_comp_id = e_comp_id;
        a_amb_resume_app(NAV_NAME);
    }
    else
    {
        if(nav_get_active_component() != e_comp_id)
        {
            i4_ret = nav_grab_activation(e_comp_id);
            if (NAVR_OK != i4_ret)
            {
                return i4_ret;
            }
        }
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name
 *      a_nav_active_component
 * Description
 *
 * Input arguments
 *      NAV_COMP_ID_T
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK
 *----------------------------------------------------------------------------*/
INT32 a_nav_active_component(NAV_COMP_ID_T e_comp_id)
{
    INT32  i4_ret = NAVR_OK;
    i4_ret = _nav_active_component(e_comp_id);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name
 *      a_nav_disable_panel_key
 * Description
 *
 * Input arguments
 *      b_disable_panel_key
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
VOID a_nav_disable_panel_key_by_odm(BOOL  b_disable_panel_key)
{
    UINT8  ui1_odm_id = 0;

    a_cfg_custom_get_odm_idx(&ui1_odm_id);
    /*
         the meaning of ui1_id is as following:
         0 ---> common;
         1 ---> Amtran;
         2 ---> TPV
         3 ---> Wistron;
         4 ---> Foxconn;
         For Amtran factory will add this api to disable panel key
       */
    if (1 == ui1_odm_id)
    {
        b_disable_panel_key_by_odm = b_disable_panel_key;
        a_am_is_disable_panel_power_key(b_disable_panel_key_by_odm);
    }

}
/*----------------------------------------------------------------------------
 * Name
 *      a_nav_get_panel_key_disable_status
 * Description
 *
 * Input arguments
 *      b_disable_panel_key
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
BOOL a_nav_get_panel_key_disable_status(VOID)
{
  return   b_disable_panel_key_by_odm;
}

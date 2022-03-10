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
 * $RCSfile: nav_variant.h,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/7 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 27bad65f0954f3bdb87f20fd6c804eab $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_VARIANT_H_
#define _NAV_VARIANT_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "nav/navigator.h"
#include "u_sb.h"
#ifdef APP_VTRL_INP_SRC_SUPPORT
#include "app_util/rmk/a_rmk.h"
#endif
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
//=============================================================================
// MVD-1913/MVV-9526:PIC and WIDE key deep links to setting in sidebar
// MENU_SUPPORT_HOT_KEY_PIC
#define NAV_SUPPORT_PIC_MODE        0

// MENU_SUPPORT_HOT_KEY_ASPECT_RATIO
#define NAV_SUPPORT_ASPECT_RATIO    0

// MVD-1801: Change Input Selector to vertical
#define NAV_INPUT_SRC_UI_VERTICAL   1


//=============================================================================

#ifdef APP_NAV_CAMERA_PLUG_SUPPORT
#define NAV_COMP_ID_CAMERA_PLD                  NAV_COMP_ID_CUSTOM_5
#endif
#define CH_CHANGE_TIMER_DELAY                   (3000)  /* in ms */
#define CH_LIST_TIMER_DELAY                     (5000)  /* in ms */
#define FAV_LIST_TIMER_DELAY                    (5000)  /* in ms */
#define INFO_TIMER_DELAY                        (3000)  /* in ms */
#define VOLUME_TIMER_DELAY                      (6000)  /* in ms */
#define PWD_DLG_TIMER_DELAY                     (10000) /* in ms */
#define BANNER_IDLE_DELAY                       (10000) /* in ms */
#define COMP_GENERIC_DELAY                      (5000)  /* in ms */
#define CH_LIST_REACH_TOP_SCROLL_STYLE           NEXT_ITEM_FROM_BOTTOM
#define CH_LIST_REACH_BTOOM_SCROLL_STYLE         NEXT_ITEM_FROM_TOP
#define FAV_LST_MASK_VALUE                      (SB_VNET_FAVORITE1|SB_VNET_FAVORITE2|SB_VNET_FAVORITE3|SB_VNET_FAVORITE4)
#define HDMI_BEFORE_DET_MSG_DELAY               (2000)  /* in ms */
/* compile option */
#ifndef APP_FAV_LST_IN_MENU
  #ifndef APP_FAV_LST_IN_NAV
    #define APP_FAV_LST_IN_NAV
  #endif  /* end of APP_FAV_LST_IN_NAV  */
#endif  /* end of APP_FAV_LST_IN_MENU */

#define APP_CC_DESC_WITH_LANG
#define APP_VOLUME_CTRL
#define APP_VOLUME_CTRL_TV_SPEAKER_OFF
#define APP_MOVABLE_SCREEN_SAVER
#define APP_ONLY_OPERATE_BY_CH_LIST_BTN

#if 0
#define APP_CH_LST_PAGE_UPDN   /*not need for vizio*/
#endif
#if 0
#define APP_NAV_COMP_INFO_BAR
#endif

#define APP_NAV_VIEW_NO_MUSIC_NOTE /* no need music note */

/*banner*/
#define NAV_CTM_BS_CAPTION_ICON_PRI     ((UINT8)128)
#define APP_NAV_DEFAULT_DTVCC_FIRST

/* component exclusive setting */
#define COMP_EXC_SET_CH_LST      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CH_LIST)       \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXC_SET_NAV_FAV_LST (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAV_LIST)      \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXC_SET_PWD_DLG     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PWD_DLG)     \
	                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VOL_CTRL)))

#define COMP_EXC_SET_VIDEO_SEL   (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VIDEO_SEL)     \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXC_SET_AUDIO_SEL   (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_AUDIO_SEL)     \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#if defined(APP_SEPARATED_CC_INFO) || defined(APP_NAV_CI_ONOFF)
#define COMP_EXC_SET_CC_SEL      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CC_SEL)        \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))
#else
#define COMP_EXC_SET_CC_SEL      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CC_SEL)        \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)        \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)))
#endif

#define COMP_EXC_SET_SCREEN_MODE (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCREEN_MODE)))

#define COMP_EXC_SET_ZOOM_PAN    (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_ZOOM_PAN)      \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXC_SET_VOL_CTRL    (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VOL_CTRL)      \
	                               |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PWD_DLG)      \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO)   \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCRN_BLANK)))

#define COMP_EXC_SET_CH_SELECT (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CH_SELECT)))

#define COMP_EXC_SET_DCR_AGENT   (NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PWD_DLG)         \
                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CH_LIST)         \
                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAV_LIST)        \
                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VOL_CTRL)        \
                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCREEN_SAVER))

#define COMP_EXC_SET_DCR_AGENT_FW  (NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)        \
                                   |COMP_EXC_SET_DCR_AGENT)

#if 1
#define COMP_EXEC_SET_INPUT_SRC  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)))

#else
#define COMP_EXEC_SET_INPUT_SRC  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)     \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PIP_POP)))

#define COMP_EXEC_SET_PIP_POP     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)     \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)        \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PIP_POP)))
#endif

#define COMP_EXEC_SET_SLEEP      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SLEEP)))

#define COMP_EXEC_SET_ULPK      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_ULPK)))

#define COMP_EXEC_SET_WR_UPDATER      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_WR_UPDATER)))


#define COMP_EXEC_SET_ON_TIMER_CH  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_ON_TIMER_CH)))

#define COMP_EXEC_SET_PICTURE_EFFECT  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PICTURE_EFFECT) \
                                         |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXEC_SET_SOUND_EFFECT    (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SOUND_EFFECT) \
                                        |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXEC_SET_FREEZE     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FREEZE)      \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXEC_SET_POWER      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_POWER))     \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCRN_BLANK))

#define COMP_EXEC_SET_CLOCK      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CLOCK)       \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXEC_SET_BANNER     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)   \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TUNER_SETUP) \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_MISC) \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FACTORY)     \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_DIALOG)      \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCREEN_SAVER)\
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_USB_PLD)))

#ifdef APP_TTX_SUPPORT
#define COMP_EXEC_TELETEXT      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TTX)))
#endif
/*
#define COMP_EXC_SET_NAV_MISC   (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_MISC)     \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))
*/
#define COMP_EXEC_SET_CEC       (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VIDEO_SEL)     \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#ifndef LINUX_TURNKEY_SOLUTION
#define COMP_EXEC_SET_UPG     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_UPG)))
#else
#define COMP_EXEC_SET_UPDATER     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_UPDATER)))
#endif

#define COMP_EXC_SET_USB_OC     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_USB_OC)      \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))

#define COMP_EXEC_SET_RECORD     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RECORD)))

#define COMP_EXEC_SET_AUD_ONLY    (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_AUD_ONLY)))

#ifdef APP_NAV_MAX_64_COMPS
#define COMP_EXEC_SET_MMP_LAUNCHER  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_MMP_LAUNCHER)))
#endif

#define COMP_EXEC_SET_SI    ((UINT64) 0)

#define COMP_EXEC_SET_REMINDER      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REMINDER)))

#ifdef APP_RETAIL_MODE_SUPPORT
#define COMP_EXEC_SET_RETAIL_MODE     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RETAIL_MODE) \
                                       |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO)))
#endif

//#define COMP_EXEC_SET_3D_SETTING     (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_3D_SETTING)))

#ifdef APP_RETAIL_MODE_SUPPORT
#define COMP_EXEC_SET_DIALOG  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_DIALOG)         \
                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_RETAIL_MODE) \
                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))
#else
#define COMP_EXEC_SET_DIALOG  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_DIALOG) \
                                 |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))
#endif

#ifdef APP_NAV_USB_PLD
#define COMP_EXC_SET_USB_PLD      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_USB_PLD)   \
                                    | NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCRN_BLANK) \
                                    | NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)))
#endif
#ifdef APP_NAV_CAMERA_PLUG_SUPPORT
#define COMP_EXC_SET_CAMERA_PLD      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CAMERA_PLD)))
#endif
#define COMP_EXC_SET_VIEWPORT      (NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PWD_DLG)         \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)      \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_CH_LIST)        \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FAV_LIST)       \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCREEN_SAVER))

#define COMP_EXEC_SET_SFM        (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SFM)))

#define COMP_EXEC_SET_VIA_DLG      (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VIA_DLG))       \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_POWER)           \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)       \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PWD_DLG))

#ifdef APP_C4TV_SUPPORT
#define COMP_EXC_SET_C4TV_APRON  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_C4TV_APRON)   \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)       \
	                               |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_UPDATER) 	  \
                                   |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO)))
#endif

#define COMP_EXEC_SET_REVOLT_MISC   (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_MISC)  \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_BANNER)  \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_C4TV_APRON)))

#define COMP_EXEC_SET_TUNER_SETUP   (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TUNER_SETUP)))

/*Tuner set up and revolt info need to coexist ---DTV00746419 and DTV00745705*/
#define COMP_EXEC_SET_REVOLT_INFO   (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO)   \
                                    |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TUNER_SETUP)))

/*tuner set up and link UI need to coexist---DTV00750890*/
#define COMP_EXEC_SET_LINK          (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_LINK)  \
                                     |NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TUNER_SETUP)))
#define COMP_EXEC_SET_LONG_PRESS    (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_LONG_PRESS)))

#define COMP_EXEC_SET_TEST_PATTERN  (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TEST_PATTERN)))

#ifdef APP_ZOOM_MODE_SUPPORT
#define COMP_EXEC_SET_ZOOM          (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_ZOOM)))
#endif

#define COMP_EXEC_SET_PPP           (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PPP)))

/*-----------------------------------------------------------------------------
                    customization declarations
-----------------------------------------------------------------------------*/
#define NAV_BNR_CUSTOM_GET_CHANGING_FOCUS_TV_STATE(_e_final_state, _e_trgt_state)                       \
{                                                                                                       \
    (_e_trgt_state) = (BANNER_STATE_NONE == (_e_final_state)) ? BANNER_STATE_CH : (_e_final_state);     \
}

#define NAV_INIT_DISPLAY_LANG()                                                     \
{                                                                                   \
    {MLM_NAV_KEY_LANG_ENG, "eng"},         /*english*/                  \
    {MLM_NAV_KEY_LANG_SPA, "esl"},         /*spanish*/                  \
    {MLM_NAV_KEY_LANG_SPA, "spa"},         /*spanish*/                  \
    {MLM_NAV_KEY_LANG_FRE, "fra"},         /*french*/                   \
    {MLM_NAV_KEY_LANG_FRE, "fre"}          /*french*/                   \
}

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern BOOL nav_is_key_to_discard(
                    NAV_MODEL_T*                pt_this,
                    NAV_EVN_T*                  pt_event
                    );
extern VOID nav_rcu_key_pre_handler(
                    NAV_MODEL_T*                pt_this,
                    NAV_EVN_T*                  pt_event
                    );
extern VOID nav_rcu_key_post_handler(
                    NAV_MODEL_T*                pt_this,
                    NAV_EVN_T*                  pt_event
                    );
extern INT32 nav_pre_resume(
                    NAV_MODEL_T*                pt_this
                    );
extern UINT16 nav_get_cc_osd_plane_index(
                    VOID
                    );
extern INT32 nav_set_cc_canvas_config(
                    HANDLE_T                    h_cc_plane,
                    HANDLE_T*                   ph_cc_canvas
                    );
extern INT32 nav_enable_cc_plane(HANDLE_T h_cc_plane, BOOL resume);

extern BOOL nav_handle_am_default_key(
                    NAV_MODEL_T*                pt_this,
                    BOOL                        b_before_notify_resume,
                    UINT32                      ui4_key
                    );
extern INT32 nav_pre_brdcst_msg_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    );

#ifdef APP_VTRL_INP_SRC_SUPPORT
extern INT32 nav_rmk_hdlr_is_ret_key(
                    UINT32                      ui4_keycode,
                    BOOL*                       pb_is_ret,
                    HANDLE_T*                   ph_new_focus);
extern INT32 nav_rmk_hdlr_ret(
                    const APP_RMK_RET_INFO_T* pt_info);
#endif

extern INT32 a_nav_active_component(NAV_COMP_ID_T e_comp_id);

extern BOOL nav_custom_check_inp_locked(
                    NAV_MODEL_T*                pt_this,
                    NAV_TV_WIN_T*               pt_tv_win,
                    ISL_REC_T*                  pt_isl_rec
                    );
extern BOOL a_nav_get_panel_key_disable_status(VOID);
#endif /* _NAV_VARIANT_H_ */

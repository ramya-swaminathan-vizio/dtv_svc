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
 * $RCSfile: vol_ctrl.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _VOL_CTRL_H_
#define _VOL_CTRL_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_scc.h"
#include "u_wgl_image.h"

#include "nav/vol_ctrl/a_vol_ctrl.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"
#ifdef APP_TTS_SUPPORT
#include "u_tts.h"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef APP_CEC_SUPPORT
    #define APP_CEC_SAC_VOL_SUPPORT 1
#else
    #define APP_CEC_SAC_VOL_SUPPORT 0
#endif


#ifndef COMP_VIEW_EXC_SET_VOL_CTRL_MUTE
#define  COMP_VIEW_EXC_SET_VOL_CTRL_MUTE     0
#endif

#ifndef COMP_VIEW_DENY_SET_VOL_CTRL_MUTE
#define  COMP_VIEW_DENY_SET_VOL_CTRL_MUTE    0
#endif

#ifdef APP_TTS_SUPPORT
#define VOL_CTRL_TTS_DELAY_TIME       (450) /* ms */
#endif

struct _VOL_CTRL_T;

typedef INT32 (*vol_ctrl_view_init_fct)(
                    struct _VOL_CTRL_T*         pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset
                    );
typedef INT32 (*vol_ctrl_view_deinit_fct)(
                    VOID
                    );
typedef INT32 (*vol_ctrl_view_show_volume_fct)(
                    UINT8                       ui1_ch_idx,
                    INT16                       i2_min_val,
                    INT16                       i2_max_val,
                    INT16                       i2_volume
                    );
typedef INT32 (*vol_ctrl_view_update_volume_fct)(
                    INT16                       i2_volume
                    );
typedef INT32 (*vol_ctrl_view_hide_volume_fct)(
                    VOID
                    );
typedef INT32 (*vol_ctrl_view_show_mute_fct)(
                    BOOL    b_is_mute
                    );
typedef INT32 (*vol_ctrl_view_hide_mute_fct)(
                    VOID
                    );
typedef BOOL (*vol_ctrl_view_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*vol_ctrl_view_activate_fct)(
                    UINT32                      ui4_key_code
                    );

typedef struct _VOL_CTRL_VIEW_HDLR_T
{
    vol_ctrl_view_init_fct              pf_init;
    vol_ctrl_view_deinit_fct            pf_deinit;
    vol_ctrl_view_show_volume_fct       pf_show_volume;
    vol_ctrl_view_update_volume_fct     pf_update_volume;
    vol_ctrl_view_hide_volume_fct       pf_hide_volume;
    vol_ctrl_view_show_mute_fct         pf_show_mute;
    vol_ctrl_view_hide_mute_fct         pf_hide_mute;
    vol_ctrl_view_is_key_handler_fct    pf_is_key_handler;
    vol_ctrl_view_activate_fct          pf_activate;
} VOL_CTRL_VIEW_HDLR_T;

typedef struct _VOL_CTRL_T
{
    HANDLE_T                h_svctx;
    HANDLE_T                h_hide_timer;
    HANDLE_T                h_mute_hide_timer;
    SCC_AUD_OUT_PORT_T      e_au_out_ports;
    UINT8                   ui1_crnt_au_ch_idx;
    BOOL                    b_is_volume_on;
    BOOL                    b_is_mute_on;
    BOOL                    b_is_volume_visible;
    BOOL                    b_is_bt_headphones_active;
    BOOL                    b_is_volume_event;
    BOOL                    b_is_mute_event;
    BOOL                    b_is_bt_req_in_progress;
    INT16                   i2_volume;

    VOL_CTRL_VIEW_HDLR_T    t_view_hdlr;
#ifndef APP_HIDE_MUTE_AS_PAUSED
    UINT16                  ui2_audio_cfg_nfy;
#endif
#ifdef APP_MUTE_DISP_AS_TEXT
    UINT16                  ui2_gui_lang_cfg_nfy;
#endif
#ifdef APP_CEC_SUPPORT
    UINT16                  ui2_cec_sac_icl_nfy;
    BOOL                    b_is_sam_on;
#endif

//#if APP_CEC_SAC_VOL_SUPPORT
    NAV_VOL_INFO_TYPE_T     e_cec_sac_vol_info;
//#endif
#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
    BOOL                    b_is_need_show_speaker_off;
#endif

#ifdef APP_TTS_SUPPORT
	HANDLE_T                    h_tts_sound;		/* for voice prompt */
	TTS_STRING_T				t_sound_content;	/* store sound content to output. */
	HANDLE_T                    h_tts_timer;        /* for tts timer*/
#endif
    BOOL                    b_is_aud_sys_visible;
} VOL_CTRL_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 vol_ctrl_view_register_default_hdlr(
                    VOL_CTRL_VIEW_HDLR_T*       pt_view_hdlr
                    );
extern INT32 vol_ctrl_next_audio_channel(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 vol_ctrl_prev_audio_channel(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 vol_ctrl_show_volume(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 vol_ctrl_increase_volume(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 vol_ctrl_decrease_volume(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 vol_ctrl_set_mute(
                    VOL_CTRL_T*                 pt_this,
                    BOOL                        b_mute
                    );
extern VOID vol_ctrl_reset_timer(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 vol_ctrl_toggle_mute(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 vol_ctrl_get_vol_cfg_id(
                    UINT8                       ui1_idx,
                    UINT16*                     pui2_cfg_id
                    );
extern INT32 vol_ctrl_next_vol_cfg_id(
                    UINT8*                      pui1_idx,
                    UINT16*                     pui2_cfg_id
                    );
extern INT32 vol_ctrl_prev_vol_cfg_id(
                    UINT8*                      pui1_idx,
                    UINT16*                     pui2_cfg_id
                    );
extern UTF16_T* vol_ctrl_get_vol_ch_display_name(
                    UINT8                       ui1_idx
                    );
extern BOOL vol_ctrl_is_mute_icon_coexist_app(
                    CHAR*                       ps_app_name
                    );

extern INT32 vol_ctrl_custom_set_image(HANDLE_T   h_slider_bar);
extern INT32 vol_ctrl_mute(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 bt_vol_ctrl_increase_volume(
                    VOL_CTRL_T*                 pt_this
                    );
extern INT32 bt_vol_ctrl_decrease_volume(
                    VOL_CTRL_T*                 pt_this
                    );

extern  INT32 vol_ctrl_update_volume(VOL_CTRL_T*	pt_this);

//#if APP_CEC_SAC_VOL_SUPPORT
extern BOOL  vol_ctrl_is_cec_sac_mode(VOID);
//#endif

#ifdef APP_TTS_SUPPORT
VOID nav_vol_ctrl_reset_tts_timer(
                    VOL_CTRL_T*               pt_this,
                    CHAR *ps_str
                    );
#endif

void bt_vol_ctrl_post_bt_event(void *pv_tag1, void *pv_tag2, void *pv_tag3);

extern BOOL a_vol_ctrl_tts_set_mute(BOOL b_mute);
extern BOOL a_vol_ctrl_tts_get_mute(VOID);
#endif /* _VOL_CTRL_H_ */

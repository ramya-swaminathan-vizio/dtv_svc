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
 * $RCSfile: menu_page_eq_setting.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_scc.h"

#include "app_util/a_ui.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"

#include "app_util/a_cfg.h"
#include "menu2/menu_util2.h"
#include "app_util/ui/_ui.h"

#include "res/app_util/config/a_cfg_custom.h"

#include "mmp/a_mmp.h"



#include "res/menu2/menu_custom_dialog.h"
#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "c_tts.h"
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define APP_MENU_EQ_MODE_MAX_NUM    (2)
#define EQ_BAND_NUM                 (5)


#define MENU_EQ_BANDS_FRM_X         ((SCREEN_W-MENU_EQ_BANDS_FRM_W)/2)
#define MENU_EQ_BANDS_FRM_Y         (320)
#define MENU_EQ_BANDS_FRM_W         (633)
#define MENU_EQ_BANDS_FRM_H         (508)

#define MENU_EQ_FRQ_H               (57)

#define MENU_EQ_INDI_H              (75)
#define MENU_EQ_ITEM_W              (114)
#define MENU_EQ_ITEM_H              (MENU_EQ_BANDS_FRM_H)
#define MENU_ITEM_OFFSET            (67)

#define MENU_EQ_AUDIO_MODE_H        (114)


#ifdef APP_TTS_SUPPORT
#define MENU_EQ_FLAT                (0)
#define MENU_EQ_DYNAMIC             (1)
#define MENU_EQ_CENTER              (2)
#define MENU_EQ_BASS_BOOST          (3)
#define MENU_EQ_BRIGHT              (4)
#define MENU_EQ_CUSTOM              (5)

#define MENU_EQ_100HZ               (0)
#define MENU_EQ_300HZ               (1)
#define MENU_EQ_1KHZ                (2)
#define MENU_EQ_3KHZ                (3)
#define MENU_EQ_10KHZ               (4)
#endif

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_new_eq;
static HANDLE_T      h_eq_bands_ind = NULL_HANDLE;
static HANDLE_T      h_txt_ind_value[3] = {0};
static HANDLE_T      h_aud_mode   = NULL_HANDLE;
static HANDLE_T      h_bands_frame= NULL_HANDLE;
static HANDLE_T      ah_bands_frq[EQ_BAND_NUM]  = {0};
static HANDLE_T      ah_bands_frq_txt[EQ_BAND_NUM]  = {0};
static HANDLE_T      h_eq_settings_slider = NULL_HANDLE;
static HANDLE_T      h_eq_aud_mode_txt = NULL_HANDLE;

static HANDLE_T      h_g_root_frm = NULL_HANDLE;
static HANDLE_T      h_g_main_frm = NULL_HANDLE;

static BOOL          b_is_select_state = FALSE;

static UINT32        ui4_g_nfy_id = 1024;
static UINT8         ui1_band_idx = EQ_BAND_NUM;
static UTF16_T*      pw2s_bands_title[EQ_BAND_NUM] = {L"100Hz" ,
                                                        L"300Hz",
                                                        L"1KHz",
                                                        L"3KHz",
                                                        L"10KHz"} ;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _change_state_and_nav(VOID);
static INT32 _menu_eq_bands_get_val (UINT8 ui1_idx);
static INT32 _update_bass_treble_eq(VOID);
extern BOOL is_audio_custom_mode_created(VOID);
static VOID _int_to_w2s(UTF16_T* w2s_dst,INT32 i4_src,UINT32 ui4_dst_len);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
 /*----------------------------------------------------------------------------
* Name: _menu_aud_mode_set
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Returns:
----------------------------------------------------------------------------*/
 static INT32 _menu_aud_mode_set(UINT16 ui2_idx)
 {
    INT32   i4_ret;
#ifdef APP_TTS_SUPPORT
    UTF16_T     w2s_str[32+1] = {0};

    switch (ui2_idx)
    {
    case MENU_EQ_FLAT:
        c_uc_ps_to_w2s("Audio Mode, flat", w2s_str, c_strlen("Audio Mode, flat"));
        break;
    case MENU_EQ_DYNAMIC:
        c_uc_ps_to_w2s("Audio Mode, dynamic", w2s_str, c_strlen("Audio Mode, dynamic"));
        break;
    case MENU_EQ_CENTER:
        c_uc_ps_to_w2s("Audio Mode, center", w2s_str, c_strlen("Audio Mode, center"));
        break;
    case MENU_EQ_BASS_BOOST:
        c_uc_ps_to_w2s("Audio Mode, bass boost", w2s_str, c_strlen("Audio Mode, bass boost"));
        break;
    case MENU_EQ_BRIGHT:
        c_uc_ps_to_w2s("Audio Mode, bright", w2s_str, c_strlen("Audio Mode, bright"));
        break;
    case MENU_EQ_CUSTOM:
        c_uc_ps_to_w2s("Audio Mode, custom", w2s_str, c_strlen("Audio Mode, custom"));
        break;
    default:
        break;
    }
    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                 ui2_idx);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("[MENU][%s %d] ui2_idx =%d\n",__FUNCTION__,__LINE__,ui2_idx));
 //   i4_ret = c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, TRUE);
//    MENU_LOG_ON_FAIL(i4_ret);
#if 0
#ifdef APP_FUSION_TV_SUPPORT
     acfg_fusion_tv_sound_set(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_DTS_SS2_ENABLE), ACFG_SND_DTS_SS2_ENABLE_ON);
#endif
#endif

    acfg_cust_audio_set_dtsVx_off();
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));
    MENU_LOG_ON_FAIL(i4_ret);
    acfg_cust_audio_set_dtsVx_recover();
 //   i4_ret = c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, FALSE);
 //   MENU_LOG_ON_FAIL(i4_ret);

    if (5 == ui2_idx)
    {
        i4_ret = a_cfg_av_set(CFG_MAKE_ID( APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS), 1);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
* Name: _menu_aud_mode_get
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Returns:
----------------------------------------------------------------------------*/
static INT32 _menu_aud_mode_get(UINT16 * pui2_idx)
{
    INT32                       i4_ret = 0 ;
    INT16                       i2_val = 0;

    if (!pui2_idx)
    {
        return MENUR_INV_ARG ;
    }

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), &i2_val);

    if (MENUR_OK == i4_ret)
    {
        *pui2_idx = (UINT16)i2_val ;
    }
    else
    {
        *pui2_idx = 0 ;
    }

    return i4_ret ;
}

/*----------------------------------------------------------------------------
* Name: _menu_aud_mode_set_to_custom
*
* Description: set audio mode to custom and read custom xx(bands val)
*
* Inputs:
*
* Outputs:
*
* Returns:
----------------------------------------------------------------------------*/
static INT32 _menu_aud_mode_set_to_custom(UINT16 ui2_idx)
 {
    INT32   i4_ret;
#ifdef APP_TTS_SUPPORT
    UTF16_T     w2s_str[32+1] = {0};
    UTF16_T     w2s_buf[32+1] = {0};
    INT32       i4_bands_val = MENUR_OK;

    switch (ui2_idx)
    {
    case MENU_EQ_FLAT:
    case MENU_EQ_DYNAMIC:
    case MENU_EQ_CENTER:
    case MENU_EQ_BASS_BOOST:
    case MENU_EQ_BRIGHT:
        break;
    case MENU_EQ_CUSTOM:
        c_uc_ps_to_w2s("Audio Mode, custom", w2s_str, c_strlen("Audio Mode, custom"));
        break;
    default:
        break;
    }

    i4_bands_val = _menu_eq_bands_get_val(ui1_band_idx);

    _int_to_w2s(w2s_buf,i4_bands_val,32);
    c_uc_w2s_strncat(w2s_str,w2s_buf,c_uc_w2s_strlen(w2s_buf));
    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                 ui2_idx);
    MENU_LOG_ON_FAIL(i4_ret);

  //  i4_ret = c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, TRUE);
  //  MENU_LOG_ON_FAIL(i4_ret);
#if 0
#ifdef APP_FUSION_TV_SUPPORT
     acfg_fusion_tv_sound_set(CFG_MAKE_ID(APP_CFG_GRPID_SOUND, APP_CFG_RECID_AUD_DTS_SS2_ENABLE), ACFG_SND_DTS_SS2_ENABLE_ON);
#endif
#endif
    acfg_cust_audio_set_dtsVx_off();
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));
    MENU_LOG_ON_FAIL(i4_ret);
   // i4_ret = c_scc_aud_set_se_sound_mode_start(t_g_menu_common.h_scc_aud, FALSE);
  //  MENU_LOG_ON_FAIL(i4_ret);

    acfg_cust_audio_set_dtsVx_recover();
    if (5 == ui2_idx)
    {
        i4_ret = a_cfg_av_set(CFG_MAKE_ID( APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS), 1);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _audio_mode_change_to_custom(VOID)
{
    menu_list_set_idx(h_aud_mode, 5);
    menu_list_adjust_rect(h_aud_mode);

    _menu_aud_mode_set_to_custom(5);

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _aud_mode_proc_fct
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
static INT32 _aud_mode_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32                    i4_ret = 0;

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
            UINT16  ui2_idx;
            BOOL    b_custom_mode_exist = FALSE;

            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_HLT_PREV_ELEM,
                         WGL_PACK(FALSE),
                         NULL);

            menu_list_adjust_rect(h_widget);

            menu_list_get_idx(h_widget, &ui2_idx);

            b_custom_mode_exist = is_audio_custom_mode_created();

            if (ui2_idx < 5)
            {
                i4_ret = _menu_aud_mode_set(ui2_idx);
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }
            }
            else
            {
                if (b_custom_mode_exist)
                {
                    i4_ret = _menu_aud_mode_set(ui2_idx);
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_PREV_ELEM,
                                 WGL_PACK(FALSE),
                                 NULL);

                    menu_list_adjust_rect(h_widget);

                    i4_ret = _menu_aud_mode_set(ui2_idx-1);
                }
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }
            }

            _update_bass_treble_eq();
            return WGLR_OK;
        }
        case BTN_CURSOR_RIGHT:
        {
            UINT16 ui2_idx;
            BOOL    b_custom_mode_exist = FALSE;

            c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_HLT_NEXT_ELEM,
                          WGL_PACK(FALSE),
                          NULL);

            menu_list_adjust_rect(h_widget);

            menu_list_get_idx(h_widget, &ui2_idx);

            b_custom_mode_exist = is_audio_custom_mode_created();

           // if (ui2_idx < ACFG_FILESYS_PRELOADED_AUD_MODE_NUM)
           if (ui2_idx < 5)
            {
                i4_ret = _menu_aud_mode_set(ui2_idx);
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }
            }
            else
            {
                if (b_custom_mode_exist)
                {
                    i4_ret = _menu_aud_mode_set(5);
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                  WGL_CMD_LB_HLT_NEXT_ELEM,
                                  WGL_PACK(FALSE),
                                  NULL);

                    menu_list_adjust_rect(h_widget);

                    i4_ret = _menu_aud_mode_set(0);
                }
                if(i4_ret != MENUR_OK)
                {
                    return i4_ret;
                }
            }

            _update_bass_treble_eq();
            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            return WGLR_OK;
        }
        case BTN_PREV_PRG:
        case BTN_RETURN:
            c_wgl_set_visibility(h_g_main_frm,
                                 WGL_SW_NORMAL);
            menu_nav_back();
            return WGLR_OK;

        default:
            break;
        }
#ifdef APP_TTS_SUPPORT
    case WGL_MSG_GET_FOCUS:
    {
        UTF16_T     w2s_str[32+1] = {0};
        UINT16      ui2_idx;

        menu_list_get_idx(h_widget, &ui2_idx);
        switch (ui2_idx)
        {
        case MENU_EQ_FLAT:
            c_uc_ps_to_w2s("Audio Mode, flat", w2s_str, c_strlen("Audio Mode, flat"));
            break;
        case MENU_EQ_DYNAMIC:
            c_uc_ps_to_w2s("Audio Mode, dynamic", w2s_str, c_strlen("Audio Mode, dynamic"));
            break;
        case MENU_EQ_CENTER:
            c_uc_ps_to_w2s("Audio Mode, center", w2s_str, c_strlen("Audio Mode, center"));
            break;
        case MENU_EQ_BASS_BOOST:
            c_uc_ps_to_w2s("Audio Mode, bass boost", w2s_str, c_strlen("Audio Mode, bass boost"));
            break;
        case MENU_EQ_BRIGHT:
            c_uc_ps_to_w2s("Audio Mode, bright", w2s_str, c_strlen("Audio Mode, bright"));
            break;
        case MENU_EQ_CUSTOM:
            c_uc_ps_to_w2s("Audio Mode, custom", w2s_str, c_strlen("Audio Mode, custom"));
            break;
        default:
            break;
        }
        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
        break;
    }
#endif

    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_get_val
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
static INT32 _menu_eq_bands_get_val (UINT8 ui1_idx)
{
    INT16   i2_aud_eq = 0;
    INT16   b_eq_bands_vx = 0;
    /*save vx*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), &b_eq_bands_vx);

    /* set 0 => basic => 1 */
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), APP_CFG_DTS_VIRTUAL_X_OFF);

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_idx)), &i2_aud_eq);

    /*resave vx*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_DTS_VIRTUAL_X), b_eq_bands_vx);

    return i2_aud_eq;
}

extern BOOL is_audio_custom_mode_created(VOID)
{
    INT16   i2_aud_mode_usage = 0;
    BOOL    b_ret = FALSE;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS),&i2_aud_mode_usage);

    if (i2_aud_mode_usage == 0)
    {
        b_ret = FALSE;
    }
    else
    {
        b_ret = TRUE;
    }

    DBG_INFO(("%s() Line %d: return %d\n", __FUNCTION__, __LINE__, b_ret));

    return b_ret;
}

VOID menu_delete_audio_mode(VOID)
{
    UINT16 ui2_current_audio_mode = 0;
    UINT8  ui1_loop = 0;

    _menu_aud_mode_get(&ui2_current_audio_mode);
    _menu_aud_mode_set(5);

    for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
    {
        a_cfg_av_set(
                CFG_MAKE_ID(APP_CFG_GRPID_AUDIO,
                (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_loop)), 126);
    }

    /* restore audio mode */
    if (5 == ui2_current_audio_mode)
    {
        _menu_aud_mode_set(0);
    }
    else
    {
        _menu_aud_mode_set(ui2_current_audio_mode);
    }

    a_cfg_av_set(CFG_MAKE_ID( APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS), 0);

}

/*----------------------------------------------------------------------------
 * Name: _menu_eq_reset_value
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
static INT32 _menu_eq_reset_value(VOID)
{
    INT32     i4_ret = 0;
    UINT16    ui2_idx = 0;
    UINT8     ui1_loop = 0;

    i4_ret = _menu_aud_mode_get(&ui2_idx);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_list_set_idx(h_aud_mode, ui2_idx);
    MENU_CHK_FAIL(i4_ret);

    for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
    {
        i4_ret = _menu_eq_bands_get_val(ui1_loop);
        menu_range_set_val(ah_bands_frq[ui1_loop], i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _change_state_and_nav
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
static INT32 _change_state_and_nav(VOID)
{
    INT32                 i4_ret;
    WGL_KEY_LINK_T        at_key_lnk[4];

    c_wgl_set_visibility(h_bands_frame,WGL_SW_RECURSIVE);

    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = NULL_HANDLE;
    at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_bands_frq[0];
    i4_ret = c_wgl_set_navigation(h_aud_mode, 2, at_key_lnk);

    at_key_lnk[0].ui4_key = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_bands_frq[0];
    at_key_lnk[1].ui4_key = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_bands_frq[1];
    i4_ret = c_wgl_set_navigation(ah_bands_frq[0], 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_bands_frq[0];
    at_key_lnk[1].ui4_key = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_bands_frq[2];
    i4_ret = c_wgl_set_navigation(ah_bands_frq[1], 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_bands_frq[1];
    at_key_lnk[1].ui4_key = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_bands_frq[3];
    i4_ret = c_wgl_set_navigation(ah_bands_frq[2], 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_bands_frq[2];
    at_key_lnk[1].ui4_key = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_bands_frq[4];
    i4_ret = c_wgl_set_navigation(ah_bands_frq[3], 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_bands_frq[3];
    at_key_lnk[1].ui4_key = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_bands_frq[4];
    i4_ret = c_wgl_set_navigation(ah_bands_frq[4], 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _change_state_and_nav
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
static INT32 _change_eq_bands_state(HANDLE_T h_widget, BOOL b_select)
{
    WGL_IMG_INFO_T  t_img_info;
    INT32           i4_ret;

    c_memset(&t_img_info,0x0,sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;//h_g_menu_img_eq_item_nor
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_common_item_hlt_v2;//h_g_menu_img_eq_item_hlt
    if(b_select)
    {
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_common_select_hlt_v2;//h_g_menu_img_eq_item_sel
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_common_item_hlt_v2;//h_g_menu_img_eq_item_hlt
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_incr_val
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _menu_eq_bands_incr_val (UINT8 ui1_idx)
{
    INT16   i2_val = 0 ;
    INT32   i4_ret = 0 ;

    i4_ret = a_cfg_av_incr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_idx)), &i2_val);
    if (APP_CFGR_OK != i4_ret)
    {
        i2_val = 0 ;
    }

    return i2_val;
}
/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_decr_val
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _menu_eq_bands_decr_val (UINT8 ui1_idx)
{
    INT16   i2_val = 0 ;
    INT32   i4_ret = 0 ;

    i4_ret = a_cfg_av_decr(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_idx)), &i2_val);
    if (APP_CFGR_OK != i4_ret)
    {
        i2_val = 0 ;
    }

    return i2_val;
}

#ifdef APP_TTS_SUPPORT
static VOID _int_to_w2s(UTF16_T* w2s_dst,
                  INT32 i4_src,
                  UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    if(i4_src >= 0)
    {
        c_sprintf(s_buf, "%d",  i4_src);
    }
    else
    {   
        i4_src = -i4_src;
        c_sprintf(s_buf, "dash%d",  i4_src);
    }
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}
#endif


/*----------------------------------------------------------------------------
 * Name: _eq_bands_pb_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _eq_bands_pb_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
#ifdef APP_TTS_SUPPORT
    UTF16_T     w2s_str[32+1] = {0};
    UTF16_T     w2s_buf[32+1] = {0};
#endif

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        UINT8  ui1_loop = 0;
        for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
        {
            if(ah_bands_frq[ui1_loop] == h_widget)
            {
                ui1_band_idx = ui1_loop;
#ifdef APP_TTS_SUPPORT
                switch (ui1_band_idx)
                {
                case MENU_EQ_100HZ:
                    c_uc_ps_to_w2s("100hz", w2s_str, c_strlen("100hz"));
                    break;
                case MENU_EQ_300HZ:
                    c_uc_ps_to_w2s("300hz", w2s_str, c_strlen("300hz"));
                    break;
                case MENU_EQ_1KHZ:
                    c_uc_ps_to_w2s("1khz", w2s_str, c_strlen("1khz"));
                    break;
                case MENU_EQ_3KHZ:
                    c_uc_ps_to_w2s("3khz", w2s_str, c_strlen("3khz"));
                    break;
                case MENU_EQ_10KHZ:
                    c_uc_ps_to_w2s("10khz", w2s_str, c_strlen("10khz"));
                    break;
                default:
                    break;
                }
                INT32 i4_bands_val = MENUR_OK;

                i4_bands_val = _menu_eq_bands_get_val(ui1_loop);
                _int_to_w2s(w2s_buf,i4_bands_val,32);
                c_uc_w2s_strncat(w2s_str,w2s_buf,c_uc_w2s_strlen(w2s_buf));
                a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
                    break;
            }
        }
        b_is_select_state = FALSE;
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_120HZ));
    }
    break;
    case WGL_MSG_LOSE_FOCUS:
    {
        if(b_is_select_state == TRUE)
        {
                b_is_select_state = FALSE;
                _change_eq_bands_state(h_widget,FALSE);
        }
    }
    break;

    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        static INT32 i4_val = 0;
        UINT16 ui2_current_mode = 0;
        INT8   ai1_band_value[EQ_BAND_NUM] = {0};
        UINT8  ui1_loop = 0;

        _menu_aud_mode_get(&ui2_current_mode);

        for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
        {
            ai1_band_value[ui1_loop] = _menu_eq_bands_get_val(ui1_loop);
        }

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
            if(b_is_select_state == TRUE)
            {
                if(ui1_band_idx < EQ_BAND_NUM)
                {
                    if (5 == ui2_current_mode)
                    {
                        i4_val = _menu_eq_bands_incr_val (ui1_band_idx);
                        menu_range_set_val(h_widget, i4_val);
                        c_wgl_repaint(h_widget, NULL, TRUE);
#ifdef APP_TTS_SUPPORT
                        _int_to_w2s(w2s_str,i4_val,32);
                        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
                    }
                    else
                    {
                        ai1_band_value[ui1_band_idx]++;
                        MENU_LOG_ON_FAIL(a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), 5));

                        for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
                        {
                            menu_range_set_val(ah_bands_frq[ui1_loop], ai1_band_value[ui1_loop]);
                            a_cfg_av_set(
                                CFG_MAKE_ID(APP_CFG_GRPID_AUDIO,
                                (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_loop)), ai1_band_value[ui1_loop]);
                        }

                        _audio_mode_change_to_custom();

                        menu_pm_refresh();
                        menu_pm_repaint();
                    }
                }
            }
            else
            {
                c_wgl_set_focus(h_aud_mode, WGL_SYNC_AUTO_REPAINT);
            }
            return WGLR_OK;
        case BTN_CURSOR_DOWN:
            if(b_is_select_state == TRUE)
            {
                if(ui1_band_idx < EQ_BAND_NUM)
                {
                    if (5 == ui2_current_mode)
                    {
                        i4_val = _menu_eq_bands_decr_val (ui1_band_idx);
                        menu_range_set_val(h_widget, i4_val);
                        c_wgl_repaint(h_widget, NULL, TRUE);
#ifdef APP_TTS_SUPPORT
                        _int_to_w2s(w2s_str,i4_val,32);
                        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif
                    }
                    else
                    {
                        ai1_band_value[ui1_band_idx]--;
                        MENU_LOG_ON_FAIL(a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), 5));

                        for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
                        {
                            menu_range_set_val(ah_bands_frq[ui1_loop], ai1_band_value[ui1_loop]);
                            a_cfg_av_set(
                                CFG_MAKE_ID(APP_CFG_GRPID_AUDIO,
                                (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_loop)), ai1_band_value[ui1_loop]);
                        }

                        _audio_mode_change_to_custom();

                        menu_pm_refresh();
                        menu_pm_repaint();
                    }
                }
            }

            return WGLR_OK;
        case BTN_SELECT:
            if(b_is_select_state == FALSE)
            {
                b_is_select_state = TRUE;
                _change_eq_bands_state(h_widget,TRUE);
                c_wgl_repaint(h_widget, NULL, TRUE);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_120HZ));
            }
            else
            {
                b_is_select_state = FALSE;
                _change_eq_bands_state(h_widget,FALSE);
                c_wgl_repaint(h_widget, NULL, TRUE);
            }

            break;
        case BTN_RETURN:
            c_wgl_set_visibility(h_g_main_frm,
                                 WGL_SW_NORMAL);
            menu_nav_back();
            return WMPR_DONE;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_frame_create
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
static INT32 _menu_eq_bands_frame_create(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    UINT32          ui4_style;

    WGL_IMG_INFO_T  t_img_info;

    ui4_style = 0;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_EQ_BANDS_FRM_X,
                     MENU_EQ_BANDS_FRM_Y,
                     MENU_EQ_BANDS_FRM_W,
                     MENU_EQ_BANDS_FRM_H);

    i4_ret = c_wgl_create_widget(h_g_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_bands_frame);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_common_eq_bk_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_common_eq_bk_v2;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_common_eq_bk_v2;
    i4_ret = c_wgl_do_cmd(h_bands_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_visibility(h_bands_frame,WGL_SW_NORMAL);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_indicate_create
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
static INT32 _menu_eq_ind_value_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    UINT8           ui1_i = 0;
    GL_RECT_T       t_rect;
    UINT32          ui4_style = WGL_STL_TEXT_MAX_32 |
                                   WGL_STL_TEXT_SMART_CUT |
                                   WGL_STL_GL_NO_BK;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    INT32               i4_y[3] = {128, 233, 337};//14 94 174
    //WGL_INSET_T         t_inset;

    for (ui1_i=0; ui1_i<3; ui1_i++)
    {
        SET_RECT_BY_SIZE(&t_rect,
                     20,//0
                     i4_y[ui1_i],
                     25, //22
                     24); //24

        i4_ret = c_wgl_create_widget(h_bands_frame,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &h_txt_ind_value[ui1_i]);
        if (i4_ret < 0)
        {
            DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                        __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return MENUR_CANT_CREATE_WIDGET;
        }

        /* Set Font */
        c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.ui1_custom_size  = 13;

        i4_ret = c_wgl_do_cmd (h_txt_ind_value[ui1_i],
                                WGL_CMD_GL_SET_FONT,
                                WGL_PACK(&t_fnt_info),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

         /* Set Alignment */
         i4_ret = c_wgl_do_cmd(h_txt_ind_value[ui1_i],
                               WGL_CMD_TEXT_SET_ALIGN,
                               (VOID*)WGL_AS_RIGHT_CENTER,
                               NULL);
         MENU_LOG_ON_FAIL(i4_ret);

        /* Set Color */
        c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
        i4_ret = c_wgl_do_cmd(h_txt_ind_value[ui1_i],
                               WGL_CMD_GL_SET_COLOR,
                               WGL_PACK(WGL_CLR_TEXT),
                               WGL_PACK(&t_clr_info));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_do_cmd(h_txt_ind_value[0],
                          WGL_CMD_TEXT_SET_TEXT,
                          L"+12",
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_txt_ind_value[1],
                          WGL_CMD_TEXT_SET_TEXT,
                          L"0",
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_txt_ind_value[2],
                          WGL_CMD_TEXT_SET_TEXT,
                          L"-12",
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(h_eq_bands_ind,WGL_SW_RECURSIVE);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_frq_create
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
static INT32 _menu_eq_bands_frq_create(UINT8  ui1_idx)
{
    INT32               i4_ret = {0};
    GL_RECT_T           t_rect ={0};
    WGL_INSET_T         t_inset = {0};
    WGL_FONT_INFO_T     t_fnt_info;
    UINT32              ui4_style = 0;
    WGL_COLOR_INFO_T    t_clr_info;
    INT32 i4_item_w = MENU_EQ_ITEM_W;
    INT32 i4_item_h = MENU_EQ_FRQ_H;
    INT32 i4_item_l = MENU_ITEM_OFFSET + MENU_EQ_ITEM_W * ui1_idx;
    INT32 i4_item_t = MENU_EQ_ITEM_H - MENU_EQ_FRQ_H - MENU_EQ_INDI_H;

    ui4_style = WGL_STL_GL_NO_IMG_UI ;

    SET_RECT_BY_SIZE(&t_rect, i4_item_l, i4_item_t, i4_item_w, i4_item_h);
    i4_ret = c_wgl_create_widget(h_bands_frame,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(ui4_style),
                                 NULL,
                                 &ah_bands_frq_txt[ui1_idx]);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(ah_bands_frq_txt[ui1_idx],
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(ah_bands_frq_txt[ui1_idx],
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(ah_bands_frq_txt[ui1_idx],
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 18;
    i4_ret = c_wgl_do_cmd (ah_bands_frq_txt[ui1_idx],
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_clr_info,0x0,sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(ah_bands_frq_txt[ui1_idx],
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(ah_bands_frq_txt[ui1_idx],
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_bands_title[ui1_idx]),
                          WGL_PACK(c_uc_w2s_strlen(pw2s_bands_title[ui1_idx])));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (ah_bands_frq_txt[ui1_idx], WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _menu_eq_create_pb
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
static INT32 _menu_eq_create_pb(UINT8  ui1_idx)
{
    INT32               i4_ret;
    UINT32              ui4_style;
    WGL_INSET_T         t_inset;
    GL_RECT_T           t_rect;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;
    WGL_PG_IDR_LOC_T      t_pg_idr_loc;
    INT16 i2_min = 0;
    INT16 i2_max = 0;
    INT32 i4_item_w = MENU_EQ_ITEM_W;
    INT32 i4_item_h = MENU_EQ_ITEM_H - MENU_EQ_AUDIO_MODE_H;
    INT32 i4_item_l = MENU_ITEM_OFFSET + i4_item_w * ui1_idx;
    INT32 i4_item_t = MENU_EQ_AUDIO_MODE_H;

    ui4_style = WGL_STL_PG_VERTICAL_UP;

    /* Create progress bar */
    SET_RECT_BY_SIZE(&t_rect,
                     i4_item_l,
                     i4_item_t,
                     i4_item_w,
                     i4_item_h);
    i4_ret = c_wgl_create_widget(h_bands_frame,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _eq_bands_pb_proc_fct,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &ah_bands_frq[ui1_idx]);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_PG_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 49;
    t_inset.i4_right    = 18;
    t_inset.i4_top      = 26;
    t_inset.i4_bottom   = 156;
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_PG_SET_BAR_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Display mode */
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_PG_SET_DISPLAY_MODE,
                          WGL_PACK(0),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T)); // -12 to +12
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 18;

    i4_ret = c_wgl_do_cmd (ah_bands_frq[ui1_idx],
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_av_get_min_max(
         CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_idx)),
         &i2_min, &i2_max);
    MENU_CHK_FAIL(i4_ret);

    /* Range */
    i4_ret = c_wgl_do_cmd (ah_bands_frq[ui1_idx],
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK(i2_min),
                           WGL_PACK(i2_max));
    MENU_CHK_FAIL(i4_ret);


    /* Min Size */
    i4_ret = c_wgl_do_cmd (ah_bands_frq[ui1_idx],
                           WGL_CMD_PG_SET_BAR_MIN_SIZE,
                           WGL_PACK(0),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Indicator */
    i4_item_l = 0;
    i4_item_t = MENU_EQ_BANDS_FRM_H- MENU_EQ_AUDIO_MODE_H - MENU_EQ_INDI_H;
    i4_item_w = MENU_EQ_ITEM_W;
    i4_item_h = MENU_EQ_INDI_H;
    SET_RECT_BY_SIZE(&t_pg_idr_loc.t_loc_rect,
                     i4_item_l,
                     i4_item_t,
                     i4_item_w,
                     i4_item_h);
    t_pg_idr_loc.ui1_align = WGL_AS_CENTER_CENTER;
    i4_ret = c_wgl_do_cmd (ah_bands_frq[ui1_idx],
                           WGL_CMD_PG_SET_IDR_LOC,
                           WGL_PACK(WGL_PG_CNT_ILT_POS),
                           WGL_PACK(&t_pg_idr_loc));
    MENU_CHK_FAIL(i4_ret);

    /* Levels */
    t_pg_levels.a_boundary[0] = i2_max;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (ah_bands_frq[ui1_idx],
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* pb progress */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;//h_g_menu_img_eq_item_nor
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_common_item_hlt_v2;//h_g_menu_img_eq_item_hlt
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_common_item_hlt_v2;//h_g_menu_img_eq_item_hlt
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_BODY),
                          WGL_PACK(&t_img_info ));
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_common_white_progress_bar_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_common_white_progress_bar_v2;//h_g_menu_common_white_progress_bar_v2
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_common_white_progress_bar_v2;
    i4_ret = c_wgl_do_cmd(ah_bands_frq[ui1_idx],
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info ));
    MENU_CHK_FAIL(i4_ret);


    i4_ret = c_wgl_set_visibility (ah_bands_frq[ui1_idx], WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_pb_create
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
static INT32 _menu_eq_bands_pb_create(VOID)
{
    INT32           i4_ret;
    UINT8           ui1_loop = 0;

    for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
    {
        i4_ret = _menu_eq_bands_frq_create(ui1_loop);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = _menu_eq_create_pb(ui1_loop);
        MENU_CHK_FAIL(i4_ret);
    }

    c_wgl_set_visibility(h_eq_bands_ind,WGL_SW_NORMAL);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_eq_bands_create
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
static INT32 _menu_eq_bands_create(VOID)
{
    INT32  i4_ret = 0;

    i4_ret = _menu_eq_bands_frame_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_eq_ind_value_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_eq_bands_pb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _update_bass_treble_eq(VOID)
{
    INT32 i4_ret = MENUR_OK;
    UINT8 ui1_loop = 0;
    INT16 ui2_bass = 0;
    INT16 ui2_treble = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS), &ui2_bass);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE), &ui2_treble);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
    {
        i4_ret = _menu_eq_bands_get_val(ui1_loop);
        menu_range_set_val(ah_bands_frq[ui1_loop], i4_ret);
    }
    c_wgl_repaint(h_bands_frame,NULL,TRUE);
    return MENUR_OK;
}

static INT32 _menu_eq_audio_mode_text_create()
{
    INT32               i4_ret = MENUR_OK;
    UINT32              ui4_style = 0;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    INT32 i4_item_l = 65;
    INT32 i4_item_t = 0;
    INT32 i4_item_w = MENU_EQ_BANDS_FRM_W/2;
    INT32 i4_item_h = MENU_EQ_AUDIO_MODE_H;

    ui4_style = WGL_STL_GL_NO_IMG_UI ;

    SET_RECT_BY_SIZE(&t_rect,
                  i4_item_l,
                  i4_item_t,
                  i4_item_w,
                  i4_item_h);

    i4_ret = c_wgl_create_widget(h_aud_mode,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_eq_aud_mode_txt);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 35;

    i4_ret = c_wgl_do_cmd(h_eq_aud_mode_txt,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Color */
    c_memset(&t_clr_info,0x0,sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(h_eq_aud_mode_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(h_eq_aud_mode_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));

    /* Set Title Text */
    i4_ret = c_wgl_do_cmd(h_eq_aud_mode_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_AUD_MODE_TITLE)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_AUD_MODE_TITLE))));
    MENU_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_eq_aud_mode_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (h_eq_aud_mode_txt, WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static VOID _loosely_exclusive_callback(VOID* pv_tag, VOID* pv_param)
{
    UINT32 ui4_nfy_id = (UINT32)pv_param;
    INT32  i4_ret = MENUR_OK;

    if (ui4_nfy_id == ui4_g_nfy_id)
    {
        c_wgl_set_visibility(h_g_main_frm,
                             WGL_SW_NORMAL);

        i4_ret = menu_nav_back();
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32   i4_ret = MENUR_FAIL;
    UI_SLIDER_BAR_INIT_T    t_ui_slider_bar_init;
    i4_ret = menu_pm_get_root_frm(&h_g_root_frm);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = menu_pm_get_main_frm(&h_g_main_frm);
    MENU_CHK_FAIL(i4_ret);
    INT16   i2_val_min = 0 ;
    INT16   i2_val_max = 0 ;

    GL_POINT_T t_offset;
    t_offset.i4_x = MENU_SLIDER_BAR_OFFSET_X;
    t_offset.i4_y = MENU_SLIDER_BAR_OFFSET_Y;
    c_memset(&t_ui_slider_bar_init, 0, sizeof(UI_SLIDER_BAR_INIT_T));
    t_ui_slider_bar_init.e_style = UI_SLIDER_BAR_STYLE_BAR;
    t_ui_slider_bar_init.h_parent = h_g_root_frm;
    t_ui_slider_bar_init.pt_begin_offset = &t_offset;
    t_ui_slider_bar_init.pf_wdgt_proc = NULL;
    i4_ret = a_ui_slider_bar_create(&t_ui_slider_bar_init, &h_eq_settings_slider);
    MENU_CHK_FAIL(i4_ret);

    WGL_INSET_T t_inset;
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    a_ui_slider_bar_get_cnt_inset(h_eq_settings_slider, &t_inset);
    t_inset.i4_left = t_inset.i4_left + 8;
    a_ui_slider_bar_set_cnt_inset(h_eq_settings_slider, &t_inset);

    /* Create Bands */
    i4_ret = _menu_eq_bands_create();
    MENU_CHK_FAIL(i4_ret);


    /* Create Audio Model */
    i4_ret = a_cfg_av_get_min_max(
                  CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                  &i2_val_min, &i2_val_max); //min=0,max=5
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_audio_eq_list_create(h_bands_frame,
                                      0,
                                      i2_val_max - i2_val_min + 1,
                                      _aud_mode_proc_fct,
                                      &h_aud_mode);
    MENU_CHK_FAIL(i4_ret);
    c_wgl_set_visibility(h_aud_mode,WGL_SW_HIDE);

    GL_RECT_T           t_rect;
    t_rect.i4_left = 0;
    t_rect.i4_top = 0;
    t_rect.i4_right = MENU_EQ_BANDS_FRM_W;
    t_rect.i4_bottom = MENU_EQ_AUDIO_MODE_H;
    c_wgl_move(h_aud_mode, &t_rect, WGL_NO_AUTO_REPAINT);


   /* Create audio mode text */
    i4_ret = _menu_eq_audio_mode_text_create();
    MENU_CHK_FAIL(i4_ret);


    i4_ret = c_wgl_set_visibility(h_bands_frame,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_g_nfy_id = 1024;

    return i4_ret;
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
    INT16 i2_val_min;
    INT16 i2_val_max;

    if (1024 == ui4_g_nfy_id)
    {
        menu_custom_dialog_loosely_exclusive_set_register(_loosely_exclusive_callback,
            NULL,
            &ui4_g_nfy_id);
    }

#ifdef VIEWPORT_SUPPORT
    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_WIDE_MODE);
    a_cfg_update_viewport ();
#endif

    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        c_wgl_float(h_aud_mode, TRUE, FALSE);
        c_wgl_float(h_bands_frame, TRUE, FALSE);
    }

    i4_ret = c_wgl_set_visibility(h_g_main_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_band_idx = EQ_BAND_NUM;
    b_is_select_state = FALSE;

    i4_ret = a_cfg_av_get_min_max(
                                  CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                                  &i2_val_min, &i2_val_max);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_list_chg_lang(h_aud_mode,
                               MLM_MENU_KEY_EMPTY,
                               MLM_MENU_KEY_AUD_MODE_FLAT,
                               MLM_MENU_KEY_AUD_MODE_FLAT + i2_val_max);
    MENU_LOG_ON_FAIL(i4_ret);

	/* Set Title Text */
    i4_ret = c_wgl_do_cmd(h_eq_aud_mode_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_AUD_MODE_TITLE)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_AUD_MODE_TITLE))));
    MENU_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_eq_aud_mode_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (h_eq_aud_mode_txt, WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_eq_reset_value();
    MENU_CHK_FAIL(i4_ret);

    /* set navigation */
    i4_ret = _change_state_and_nav();
    MENU_CHK_FAIL(i4_ret);
    c_wgl_set_visibility(h_bands_frame,WGL_SW_RECURSIVE);
    c_wgl_repaint(h_bands_frame,NULL,TRUE);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    HANDLE_T        h_last_shadow_item = NULL_HANDLE;
    INT32         i4_ret = 0;

    if (1024 != ui4_g_nfy_id)
    {
        menu_custom_dialog_loosely_exclusive_set_unregister(ui4_g_nfy_id);
        ui4_g_nfy_id = 1024;
    }

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_help_tip_keytip_show(TRUE);

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

    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        c_wgl_float(h_aud_mode, FALSE, FALSE);
        c_wgl_float(h_bands_frame, FALSE, FALSE);
    }

    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_bands_frame,WGL_SW_HIDE_RECURSIVE));
    c_wgl_repaint(h_bands_frame,NULL,TRUE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    menu_list_adjust_rect(h_aud_mode);
    c_wgl_set_focus(h_aud_mode, WGL_SYNC_AUTO_REPAINT);
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
    if((ui4_update_mask & MENU_PAGE_UMASK_REFRESH) != 0)
    {
        _change_state_and_nav();
    }

    return MENUR_OK;
}

INT32 menu_page_new_eq_init(VOID)
{

    t_g_menu_common_page_new_eq.pf_menu_page_create    = _on_page_create;
    t_g_menu_common_page_new_eq.pf_menu_page_destroy   = _on_page_destroy;
    t_g_menu_common_page_new_eq.pf_menu_page_show      = _on_page_show;
    t_g_menu_common_page_new_eq.pf_menu_page_hide      = _on_page_hide;
    t_g_menu_common_page_new_eq.pf_menu_page_get_focus = _on_page_get_focus;
    t_g_menu_common_page_new_eq.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_new_eq.pf_menu_page_update    = _on_page_update;

    return MENUR_OK;
}


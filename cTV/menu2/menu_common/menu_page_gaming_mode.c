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
 * $RCSfile: menu_page_gaming_mode.c,v $
 * $Revision: #1 $
 * $Date: 2021/10/15 $
 * $Author: Du.Jiang $
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
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_cli.h"
#include "u_gl.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_wgl_image.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_dt.h"
#include "x_os.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"

#include "menu2/menu_util2.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "res/menu2/menu_img.h"

#include "menu2/menu_dbg.h"
#include "res/nav/banner2/banner_rc.h"
#include "rest/a_rest_api.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "menu2/menu_common/menu_common.h"
#include "nav/input_src/input_src.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"
#include "res/menu2/menu_mlm.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define LIST_BOX_IDX_GLL                    (0)
#define LIST_BOX_IDX_VRR                    (1)
#define LIST_BOX_IDX_GAME_HDR               (2)
#define LIST_BOX_IDX_HDMI_MODE              (3)
#define LIST_BOX_IDX_MAX                    (4)

#define LIST_BOX_CANNOT_DISPLAY             (254)
#define LIST_BOX_CANNOT_ENABLE              (255)


#define TEXT_GAME_INFO_TITLE                (0)      //Current Gaming Mode
#define TEXT_GAME_INFO_RES                  (1)      //Resolution
#define TEXT_GAME_INFO_FRM_RT               (2)      //Frame Rate
#define TEXT_GAME_INFO_HDR                  (3)      //HDR
#define TEXT_GAME_INFO_VRR                  (4)      //Varialbe Refresh Rate
#define TEXT_GAME_INFO_AUD_OT               (5)      //Audio Out
#define TEXT_GAME_INFO_MAX                  (6)

#define GAME_INFO_V_HEIGHT_OFFSET          (500)
#define GAME_INFO_ITEM_V_HEIGHT            (40)

#define GAME_INFO_PRE_RETRACT               L"        "

typedef struct _GAMING_MODE_LIST_BOX_T
{
    HANDLE_T                h_lb_item;
    HANDLE_T                h_lb_item_ex;
    UINT16                  ui2_msgid_title;
    UINT16                  ui2_msgid_elem_first;
    UINT16                  ui2_msgid_elem_last;
    UINT16                  ui2_msgid_help_tip;
    wgl_widget_proc_fct     lb_item_proc_fct;
    wgl_widget_proc_fct     lb_item_ex_proc_fct;
    BOOL                    b_is_need_show;
    BOOL                    b_is_need_enable;
} GAMING_MODE_LIST_BOX_T;

typedef INT32 (*_game_info_update_fct)(void);
typedef struct _GAME_INFO_TEXT_T
{
    HANDLE_T   h_txt_item;
    _game_info_update_fct _info_update_fct;
} GAME_INFO_TEXT_T;

typedef enum{
    GAMING_MODE_VIEW_INIT = 0,
    GAMING_MODE_VIEW_LB_GLL_EX,
    GAMING_MODE_VIEW_LB_VRR_EX,
    GAMING_MODE_VIEW_LB_GAME_HDR_EX,
    GAMING_MODE_VIEW_LB_HDMI_MODE_EX
}GAMING_MODE_VIEW_TYPE_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_gaming_mode;

static UINT32      ui4_page_id;
static HANDLE_T    h_cnt_frm = NULL_HANDLE;
static HANDLE_T    h_homebar = NULL_HANDLE;
static HANDLE_T    h_backbar = NULL_HANDLE;

static HANDLE_T    h_lb_device_name;

static UINT16      ui2_lst_last_hlt= 0xFFFF;

static GL_RECT_T   g_t_list_tz_rect = {0};

static GAMING_MODE_LIST_BOX_T t_list_box[LIST_BOX_IDX_MAX] = {0};

//Because the displayed list box is variable, so the listbox in the current display needs to be recorded
/*
    ex:current display: GLL & HDMI Mode
       ui1_display_list_box[0] == LIST_BOX_IDX_GLL
       ui1_display_list_box[1] == LIST_BOX_IDX_HDMI_MODE
*/
static UINT8 ui1_display_list_box[LIST_BOX_IDX_MAX] = {0};
static UINT8 ui1_enable_list_box[LIST_BOX_IDX_MAX] = {0};

static GAME_INFO_TEXT_T t_game_info[TEXT_GAME_INFO_MAX] = {0};

static GAMING_MODE_VIEW_TYPE_T e_view_type = GAMING_MODE_VIEW_INIT;

static BOOL bIsSrcHDMI = FALSE;


/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2);

static INT32 _change_view(GAMING_MODE_VIEW_TYPE_T  e_gaming_mode_view_type, UINT8 ui1FocusIdx);

static INT32 _gaming_mode_setting_update_shadow_item_pos(VOID);

static INT32 menu_custom_page_gaming_mode_setting_refresh_item(VOID);
static INT32 _set_nav(VOID);

static INT32 _gaming_mode_list_box_init(VOID);
static INT32 _gaming_mode_list_box_create(VOID);
static INT32 _gaming_mode_list_box_create_ex(VOID);
static INT32 _gaming_mode_game_info_update(VOID);
static INT32 _gaming_mode_game_info_show(VOID);
static INT32 _gaming_mode_game_info_hide(VOID);
static INT32 _device_name_update(VOID);


/*----------------------------------------------------------------------------
                        Pseudo Builder
 ----------------------------------------------------------------------------*/
static BOOL _is_hdmi_mode_enable(VOID)
{
    ISL_REC_T   t_isl_rec;
    MENU_LOG_ON_FAIL(menu_get_crnt_isl(&t_isl_rec));
    return menu_full_color_is_enable(t_isl_rec.ui1_internal_id);
}

static BOOL _is_hdmi_mode_hidden(VOID)
{
    BOOL b_visible = FALSE;
    ISL_REC_T   t_isl_rec;

    MENU_LOG_ON_FAIL(menu_get_crnt_isl(&t_isl_rec));

    if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)     /* HDMI */
    {
        b_visible = menu_full_color_is_enable(t_isl_rec.ui1_internal_id);
    }

    return !b_visible;
}

static BOOL _is_item_game_low_latency_enable(VOID)
{
#if( VZO_DV__GLL_CONTROL_BY_DV_GAME )
    if( a_cfg_get_hdr_type() == SCC_VID_PQ_DOVI )
    {
        DBG_LOG_PRINT(("[MENU][DV][GAME][GLL]{%s, %d} DV => Grey out GLL \n", __FUNCTION__,__LINE__));
        return FALSE;
    }
#endif

    if( a_cfg_cust_is_support_game_low_latency() )
    {
        return TRUE;
    }

    return FALSE;
}

static BOOL _is_item_game_hdr_enable(VOID)
{
    ISL_REC_T  t_isl_rec = {0};
    menu_get_crnt_isl(&t_isl_rec);

    if (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI &&
        t_isl_rec.t_avc_info.e_video_type != DEV_AVC_DVI)
    {
        return FALSE;
    }

    return TRUE;
}

static BOOL _is_game_hdr_hidden(VOID)
{
#ifndef MT5583_MODEL
    return FALSE;
#else
    EnuCusModelSeries s_eCurModelSeries;
    s_eCurModelSeries = a_cfg_cust_get_CurModelSeries();

    if(s_eCurModelSeries == CUS_MODEL_2022_83_2K_D)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
#endif
}

static UINT16 _get_vid_game_low_latency_idx(VOID)
{
    if( a_cfg_cust_is_support_game_low_latency() == FALSE)
    {
        return  ACFG_CUST_GAME_LOW_LATENCY_OFF;
    }

    // Check if need to force value ...
    UINT8 u8_force_GLL_setting = 0;
    if( a_cfg_cust_GLL_get_force_value(&u8_force_GLL_setting) )// if( VZO_DV__SKIP_GLL_WHEN_DV_GAME )
    {
         return u8_force_GLL_setting;
    }

    INT16   i2_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    return (UINT16)i2_val;
}

static VOID _set_vid_game_low_latency_idx(UINT16 ui2_idx)
{
    INT16   i2_pre_gll = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_pre_gll);
    MENU_LOG_ON_FAIL(i4_ret);


    if (i2_pre_gll != ui2_idx)
    {
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), (INT16)ui2_idx);

#if 1
        acfg_cust_video_update_GLL_all(TRUE);
#else
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
        a_acfg_update_gaming_logo();
#endif
        set_preset_pic_mode_chg_status_ex(TRUE);
    }
}

static VOID _set_vid_vss_idx(UINT16 ui2_idx)
{
    INT16 i2_pre_VRR_val = 0;
    UINT16 ui2_AcfgId_VRR = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE);

    a_cfg_av_get(ui2_AcfgId_VRR, &i2_pre_VRR_val);

    if( ui2_idx != i2_pre_VRR_val )
    {
        set_preset_pic_mode_chg_status(TRUE);
    }

    a_cfg_av_set( ui2_AcfgId_VRR, (INT16)ui2_idx);

    a_cfg_av_update(ui2_AcfgId_VRR);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLEAR_ACTION));
}

static UINT16 _get_vid_vss_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_VARIABLE_REFRESH_RATE), &i2_val);
#if 0
    if(a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE && i2_val != 1)//vrr off
    {
        i2_val = 1;//show vrr on
    }
#endif
    return (UINT16)i2_val;
}

static VOID _set_vid_game_hdr_idx(UINT16 ui2_val)
{
    INT16   i2_pre_val = 0;
    INT32   i4_ret  = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR), &i2_pre_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR), (INT16)ui2_val);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR));
    MENU_LOG_ON_FAIL(i4_ret);

    if (i2_pre_val != ui2_val)
    {
        set_preset_pic_mode_chg_status_ex(TRUE);
    }
}

static UINT16 _get_vid_game_hdr_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_HDR), &i2_val);

    return (UINT16)i2_val;
}

static VOID _set_inp_hdmi_mode_idx(UINT16 ui2_val)
{
    UINT8 u8_UI_Hdmi_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    //DBG_LOG_PRINT(("[MENU][HDMI]{%s:%d} Cur HDMI u8PortIdx => %d\n", __FUNCTION__, __LINE__, u8CurSrcHdmiPortIdx ));

    UINT8 u8_acfg_hdmi_idx = acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(u8_UI_Hdmi_Idx);
    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][HDMI]{%s:%d} UI hdmi idx:%d => ACFG hdmi_idx:%d\n",
            __FUNCTION__, __LINE__, u8_UI_Hdmi_Idx, u8_acfg_hdmi_idx ));
    );

#if( ENABLE_HDMI_EDID_NEW_METHOD )
    INT32 i4_hdmi_idx = u8_acfg_hdmi_idx;
#else
    INT32 i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();
#endif
    if( (i4_hdmi_idx < 0) || (i4_hdmi_idx > 3) )
    {
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} Error: Invalid i4_hdmi_idx:%d => skip!\n",
            __FUNCTION__, __LINE__, i4_hdmi_idx ));
        return;
    }

#if( ENABLE_HDMI_EDID_NEW_METHOD )
    // Convert UI edid to ACFG edid index ...
    EnuAcfgEdidIdx e_acfg_edid_idx = acfg_cust_EDID_convert_UI_idx_to_acfg_idx(ui2_val);

    ACFG_DEBUG_HDMI_EDID(
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} ACFG_hdmi_idx:%d, UI_EDID_Idx:%d => e_acfg_edid_idx:%d(%s)\n",
            __FUNCTION__, __LINE__,
            i4_hdmi_idx, ui2_val, e_acfg_edid_idx, acfg_cust_get_acfg_edid_name(e_acfg_edid_idx) ));
    );

    inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, e_acfg_edid_idx);

#else

  #ifdef MT5583_MODEL
    inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, (UINT8)(ui2_val == 0 ? 2 : 0));
  #else
    inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, (UINT8)(2 - ui2_val));
  #endif
#endif
}

static UINT16 _get_inp_hdmi_mode_idx(VOID)
{
    UINT8 u8_UI_Hdmi_Idx = acfg_cust_get_CurSrcHdmi_UI_Idx();
    //DBG_LOG_PRINT(("[MENU][HDMI]{%s:%d} Cur HDMI u8PortIdx => %d\n", __FUNCTION__, __LINE__, u8CurSrcHdmiPortIdx ));

    UINT8 u8_acfg_hdmi_idx = acfg_cust_HDMI_convert_UI_idx_to_ACFG_idx(u8_UI_Hdmi_Idx);

#if( ENABLE_HDMI_EDID_NEW_METHOD )
    INT32 i4_hdmi_idx = u8_acfg_hdmi_idx;
#else
    INT32 i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();
#endif

    if( (i4_hdmi_idx < 0) || (i4_hdmi_idx > 3) )
    {
        DBG_LOG_PRINT(("[MENU][full_uhd_color][HDMI][EDID]{%s,%d} Error: Invalid i4_hdmi_idx:%d => Force to Auto !\n",
            __FUNCTION__, __LINE__, i4_hdmi_idx ));

        return UI_EDID_SEL_AUTO;
    }

    UINT8 ui1_acfg_edid_idx = 0;

    //inp_lst_get_full_uhd_color_by_hdmi_idx( i4_hdmi_idx, &ui1_acfg_edid_idx);
    INT32 i32_rtn = a_cfg_cust_get_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, &ui1_acfg_edid_idx);
    if( i32_rtn != 0 )
    {
        DBG_LOG_PRINT(("[ACFG][full_uhd_color][HDMI][EDID]{%s,%d} i4_hdmi_idx:%d: a_cfg_cust_get_full_uhd_color_by_hdmi_idx() failed!! i32_rtn:%d\n",
            __FUNCTION__, __LINE__, i4_hdmi_idx, i32_rtn ));

        return UI_EDID_SEL_AUTO;
    }


#if( ENABLE_HDMI_EDID_NEW_METHOD )
    // Convert ACFG val to UI val
    UINT8 u8_UI_edid_idx = acfg_cust_EDID_convert_ACFG_idx_to_UI_idx(ui1_acfg_edid_idx);

    return u8_UI_edid_idx;

#else

  inp_lst_get_full_uhd_color_by_hdmi_idx( i4_hdmi_idx, &ui1_acfg_edid_idx);

  #ifdef MT5583_MODEL
    return ui1_acfg_edid_idx == 2 ? 0 : 1;
  #else
    return (UINT16)(2 - ui1_acfg_edid_idx);
  #endif

#endif
}

static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32  i4_ret;
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
                case BTN_RETURN :
                {
                    menu_nav_back();
                }
                break;
                default:
                break;
            }
    }
    default:
    break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


static void _gaming_tts_play(UINT16 title,UINT16 elem_first,UINT8 index)
{
    UTF16_T w2s_str[256] = {0};
    
    c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(title));
    c_uc_w2s_strcat(w2s_str, _TEXT("."));
    c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(elem_first+index));
    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));

    return;

}


static INT32 _lb_gaming_low_latency_proc_fct(HANDLE_T    h_widget,
                                   UINT32      ui4_msg,
                                   VOID*       param1,
                                   VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    ui2_idx = _get_vid_game_low_latency_idx();

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
                    if (ui2_idx > 0)
                    {
                        ui2_idx --;
                    }
                    else
                    {
                        ui2_idx = t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first;
                    }

                    _set_vid_game_low_latency_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GLL].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_repaint(h_widget, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first,ui2_idx);
#endif
                    return  WGLR_OK;
                }
                case BTN_CURSOR_RIGHT:
                {
                    if (ui2_idx < t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first)
                    {
                        ui2_idx ++;
                    }
                    else
                    {
                        ui2_idx = 0;
                    }

                    _set_vid_game_low_latency_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GLL].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_repaint(h_widget, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first,ui2_idx);
#endif
                    return  WGLR_OK;
                }
                case BTN_SELECT:
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_LB_GLL_EX,0);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                default:
                    break;
            }
         
        }
            break;
        case WGL_MSG_GET_FOCUS:
        {
             i4_ret=menu_list_set_idx(h_widget, ui2_idx);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GLL].h_lb_item);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_set_and_show_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_help_tip));
            MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
            _gaming_tts_play(t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_title,
                            t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first,ui2_idx);
#endif
        }
            break;
        default:
            break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_variable_refresh_rate_proc_fct(HANDLE_T    h_widget,
                                   UINT32      ui4_msg,
                                   VOID*       param1,
                                   VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    ui2_idx = _get_vid_vss_idx();
   
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
                    if (ui2_idx > 0)
                    {
                        ui2_idx --;
                    }
                    else
                    {
                        ui2_idx = t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first;
                    }

                    _set_vid_vss_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_VRR].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_repaint(h_widget, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first,ui2_idx);
#endif
                    return  WGLR_OK;
                }
                case BTN_CURSOR_RIGHT:
                {
                    if (ui2_idx < t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first)
                    {
                        ui2_idx ++;
                    }
                    else
                    {
                        ui2_idx = 0;
                    }

                    _set_vid_vss_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_VRR].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_repaint(h_widget, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first,ui2_idx);
#endif

                    return  WGLR_OK;
                }
                case BTN_SELECT:
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_LB_VRR_EX,0);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;

                default:
                    break;
            }
        }
            break;
        case WGL_MSG_GET_FOCUS:
        {
           i4_ret=menu_list_set_idx(h_widget, ui2_idx);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_VRR].h_lb_item);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_set_and_show_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_help_tip));
            MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
            _gaming_tts_play(t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_title,
                             t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first,ui2_idx);
#endif
        }
            break;
        default:
            break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_game_hdr_proc_fct(HANDLE_T    h_widget,
                                   UINT32      ui4_msg,
                                   VOID*       param1,
                                   VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    ui2_idx = _get_vid_game_hdr_idx();

   

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
                    if (ui2_idx > 0)
                    {
                        ui2_idx --;
                    }
                    else
                    {
                        ui2_idx = t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first;
                    }

                    _set_vid_game_hdr_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_repaint(h_widget, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first,ui2_idx);
#endif
                    return  WGLR_OK;
                }
                case BTN_CURSOR_RIGHT:
                {
                    if (ui2_idx < t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first)
                    {
                        ui2_idx ++;
                    }
                    else
                    {
                        ui2_idx = 0;
                    }

                    _set_vid_game_hdr_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first,ui2_idx);
#endif
                    c_wgl_repaint(h_widget, NULL, TRUE);

                    return  WGLR_OK;
                }
                case BTN_SELECT:
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_LB_GAME_HDR_EX,0);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case WGL_MSG_GET_FOCUS:
        {
             i4_ret=menu_list_set_idx(h_widget, ui2_idx);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_set_and_show_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_help_tip));
            MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT            
            _gaming_tts_play(t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_title,
                             t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first,ui2_idx);
#endif
        }
            break;
        default:
            break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_hdmi_mode_proc_fct(HANDLE_T    h_widget,
                                   UINT32      ui4_msg,
                                   VOID*       param1,
                                   VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    ui2_idx = _get_inp_hdmi_mode_idx();

   
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
                    if (ui2_idx > 0)
                    {
                        ui2_idx --;
                    }
                    else
                    {
                        ui2_idx = t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first;
                    }

                    _set_inp_hdmi_mode_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_repaint(h_widget, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first,ui2_idx);
#endif

                    return  WGLR_OK;
                }
                case BTN_CURSOR_RIGHT:
                {
                    if (ui2_idx < t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first)
                    {
                        ui2_idx ++;
                    }
                    else
                    {
                        ui2_idx = 0;
                    }

                     _set_inp_hdmi_mode_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_repaint(h_widget, NULL, TRUE);

#ifdef APP_TTS_SUPPORT
                    _gaming_tts_play(t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_title,
                                     t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first,ui2_idx);
#endif

                    return  WGLR_OK;
                }
                case BTN_SELECT:
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_LB_HDMI_MODE_EX,0);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case WGL_MSG_GET_FOCUS:
        {
            i4_ret=menu_list_set_idx(h_widget, ui2_idx);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=menu_set_and_show_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_help_tip));
            MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT            
             _gaming_tts_play(t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_title,
                              t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first,ui2_idx);
#endif
        }
            break;
        default:
            break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_gaming_low_latency_ex_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;

    switch(ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            if (0xffff != ui2_lst_last_hlt)
            {
                i4_ret=c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex,
                                 WGL_CMD_LB_HLT_ELEM,
                                 WGL_PACK(0),
                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                ui2_lst_last_hlt = 0xffff;
            }

#ifdef APP_TTS_SUPPORT
            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);
             _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
        }
            break;
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_crnt_ht),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    _set_vid_game_low_latency_idx(ui2_crnt_ht);
                }
                case BTN_RETURN :
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_GLL);  // forcus in Game Low Latency
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                case BTN_CURSOR_UP:
                {
                    if(0 == ui2_crnt_ht)
                    {
                        i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex,
                                              WGL_CMD_LB_UNHLT_ELEM,
                                              WGL_PACK(ui2_crnt_ht),
                                              NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret=menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                    

                        return MENUR_OK;
                    }

#ifdef APP_TTS_SUPPORT
                    ui2_crnt_ht--;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;
                case BTN_CURSOR_DOWN:
                {
                    if((t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first) == ui2_crnt_ht)
                    {
                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret = menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);

                        return MENUR_OK;
                    }

#ifdef APP_TTS_SUPPORT
                    ui2_crnt_ht++;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;

                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _lb_variable_refresh_rate_ex_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;

    switch(ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            if (0xffff != ui2_lst_last_hlt)
            {
                i4_ret=c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex,
                                 WGL_CMD_LB_HLT_ELEM,
                                 WGL_PACK(0),
                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                ui2_lst_last_hlt = 0xffff;
            }
            
#ifdef APP_TTS_SUPPORT
            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_crnt_ht),
                                          NULL);
             MENU_LOG_ON_FAIL(i4_ret);
            _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
        }
        break;
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_crnt_ht),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    _set_vid_vss_idx(ui2_crnt_ht);
                }
                case BTN_RETURN :
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_VRR);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                case BTN_CURSOR_UP:
                {
                    if(0 == ui2_crnt_ht)
                    {
                        i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex,
                                              WGL_CMD_LB_UNHLT_ELEM,
                                              WGL_PACK(ui2_crnt_ht),
                                              NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret=menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                   
                        return MENUR_OK;
                    }

#ifdef APP_TTS_SUPPORT              
                    ui2_crnt_ht--;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;
                case BTN_CURSOR_DOWN:
                {
                    if((t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first) == ui2_crnt_ht)
                    {
                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret = menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                     
                        return MENUR_OK;
                    }

#ifdef APP_TTS_SUPPORT
                    ui2_crnt_ht++;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;

                default:
                    break;
            }

        }             
            break;
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _lb_game_hdr_ex_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;

    switch(ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            if (0xffff != ui2_lst_last_hlt)
            {
                i4_ret=c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex,
                                 WGL_CMD_LB_HLT_ELEM,
                                 WGL_PACK(0),
                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                ui2_lst_last_hlt = 0xffff;
            }

#ifdef APP_TTS_SUPPORT
            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_crnt_ht),
                                          NULL);
            MENU_LOG_ON_FAIL(i4_ret);
            _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
        }
            break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_crnt_ht),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    _set_vid_game_hdr_idx(ui2_crnt_ht);
                }
                case BTN_RETURN :
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_GAME_HDR);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                case BTN_CURSOR_UP:
                {
                    if(0 == ui2_crnt_ht)
                    {
                        i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex,
                                              WGL_CMD_LB_UNHLT_ELEM,
                                              WGL_PACK(ui2_crnt_ht),
                                              NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret=menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                        
                        return MENUR_OK;
                    }
                    
#ifdef APP_TTS_SUPPORT
                    ui2_crnt_ht--;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;
                case BTN_CURSOR_DOWN:
                {
                    if((t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first) == ui2_crnt_ht)
                    {
                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret = menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);

                        return MENUR_OK;
                    }
#ifdef APP_TTS_SUPPORT

                    ui2_crnt_ht++;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;

                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _lb_hdmi_mode_ex_proc_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;

    switch(ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            if (0xffff != ui2_lst_last_hlt)
            {
                i4_ret=c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex,
                                 WGL_CMD_LB_HLT_ELEM,
                                 WGL_PACK(0),
                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                ui2_lst_last_hlt = 0xffff;
            }

#ifdef APP_TTS_SUPPORT
            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex,
                                             WGL_CMD_LB_GET_HLT_INDEX,
                                             WGL_PACK(&ui2_crnt_ht),
                                             NULL);
             MENU_LOG_ON_FAIL(i4_ret);
            _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first,ui2_crnt_ht);
        }
#endif
            break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_crnt_ht),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    _set_inp_hdmi_mode_idx(ui2_crnt_ht);
                }
                case BTN_RETURN :
                {
                    i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_HDMI_MODE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                    break;
                case BTN_CURSOR_UP:
                {
                    if(0 == ui2_crnt_ht)
                    {
                        i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                        MENU_LOG_ON_FAIL(i4_ret);

                        i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex,
                                              WGL_CMD_LB_UNHLT_ELEM,
                                              WGL_PACK(ui2_crnt_ht),
                                              NULL);
                        MENU_LOG_ON_FAIL(i4_ret);

                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret=menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);
                        
                        return MENUR_OK;
                    }

#ifdef APP_TTS_SUPPORT
                    ui2_crnt_ht--;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;
                case BTN_CURSOR_DOWN:
                {
                    if((t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first) == ui2_crnt_ht)
                    {
                        ui2_lst_last_hlt = ui2_crnt_ht;

                        i4_ret = menu_pm_repaint();
                        MENU_LOG_ON_FAIL(i4_ret);

                        return MENUR_OK;
                    }

#ifdef APP_TTS_SUPPORT
                    ui2_crnt_ht++;
                    _gaming_tts_play(MLM_MENU_KEY_EMPTY,t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first,ui2_crnt_ht);
#endif
                }
                    break;

                default:
                    break;
            }
        }
        break;
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        /* hide old help tip first*/
        menu_hide_help_tip();
        /* trigger help tip */
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            MENU_CHK_FAIL (menu_nav_go_home_menu ()) ;
            ui2_lst_last_hlt = 0xffff;
            return MENUR_OK ;

        case BTN_CURSOR_UP:
            break ;

        case BTN_CURSOR_DOWN :

            menu_set_focus_on_backbar(TRUE);

            break ;

         case BTN_RETURN :
         {
            if (GAMING_MODE_VIEW_LB_GLL_EX == e_view_type)
            {
                _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_GLL);
                menu_pm_repaint();
            }
            else if(GAMING_MODE_VIEW_LB_VRR_EX == e_view_type)
            {
                _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_VRR);
                menu_pm_repaint();
            }
            else if(GAMING_MODE_VIEW_LB_GAME_HDR_EX == e_view_type)
            {
                _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_GAME_HDR);
                menu_pm_repaint();
            }
            else if(GAMING_MODE_VIEW_LB_HDMI_MODE_EX == e_view_type)
            {
                _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_HDMI_MODE);
                menu_pm_repaint();
            }
            else
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

                MENU_CHK_FAIL (menu_nav_back ()) ;
            }
            ui2_lst_last_hlt = 0xffff;
         }
         break;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32 i4_ret;

    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        #ifdef APP_TTS_SUPPORT
        a_app_tts_play(L"back", c_uc_w2s_strlen(L"back"));
        #endif

        menu_hide_help_tip();
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
        #endif
        case BTN_RETURN :
        case BTN_SELECT :
            if (GAMING_MODE_VIEW_LB_GLL_EX == e_view_type)
            {
                i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_GLL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(GAMING_MODE_VIEW_LB_VRR_EX == e_view_type)
            {
                i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_VRR);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(GAMING_MODE_VIEW_LB_GAME_HDR_EX == e_view_type)
            {
                i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_GAME_HDR);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(GAMING_MODE_VIEW_LB_HDMI_MODE_EX == e_view_type)
            {
                i4_ret = _change_view(GAMING_MODE_VIEW_INIT, LIST_BOX_IDX_HDMI_MODE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

                MENU_CHK_FAIL (menu_nav_back ()) ;
            }
            ui2_lst_last_hlt = 0xffff;
            return MENUR_OK ;

        case BTN_CURSOR_DOWN:
            if(!bIsSrcHDMI)
            {
                break ;
            }
            if(GAMING_MODE_VIEW_INIT == e_view_type)
            {
                MENU_CHK_FAIL (c_wgl_set_focus (t_list_box[ui1_enable_list_box[0]].h_lb_item , WGL_SYNC_AUTO_REPAINT));
            }
            else if (GAMING_MODE_VIEW_LB_GLL_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex, WGL_SYNC_AUTO_REPAINT));
            }
            else if (GAMING_MODE_VIEW_LB_VRR_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex, WGL_SYNC_AUTO_REPAINT));
            }
            else if (GAMING_MODE_VIEW_LB_GAME_HDR_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex, WGL_SYNC_AUTO_REPAINT));
            }
            else if (GAMING_MODE_VIEW_LB_HDMI_MODE_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex, WGL_SYNC_AUTO_REPAINT));
            }

        case BTN_CURSOR_UP :
            MENU_CHK_FAIL (menu_set_focus_on_homebar (TRUE));

            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static INT32 _show_init_view(BOOL b_repaint, UINT8 ui1FocusIdx)
{
    INT32        i4_ret;
    UINT8        ui1_cnt;

    i4_ret = _device_name_update();
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_lb_device_name,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _gaming_mode_game_info_show();
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_cnt = 0; ui1_cnt < LIST_BOX_IDX_MAX; ui1_cnt ++)
    {
        if(!t_list_box[ui1_cnt].b_is_need_show)
        {
            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item, WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        if(ui1_display_list_box[ui1_cnt] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item, WGL_SW_NORMAL);
            MENU_LOG_ON_FAIL(i4_ret);
            if(bIsSrcHDMI && t_list_box[ui1_display_list_box[ui1_cnt]].b_is_need_enable)
            {
                c_wgl_enable(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item, TRUE);
            }
            else
            {
                c_wgl_enable(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item, FALSE);
            }
            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item_ex, WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    if(bIsSrcHDMI)
    {
        if(t_list_box[ui1FocusIdx].b_is_need_show && t_list_box[ui1FocusIdx].b_is_need_enable)
        {
            i4_ret = c_wgl_set_focus(t_list_box[ui1FocusIdx].h_lb_item, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret = c_wgl_set_focus(t_list_box[ui1_enable_list_box[0]].h_lb_item, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        i4_ret = c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _show_lb_gll_ex_view(BOOL b_repaint)
{
    INT32       i4_ret;
    UINT16      ui2_crnt_ht;
    UINT8       ui1_i;

    i4_ret = c_wgl_set_visibility(h_lb_device_name,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _gaming_mode_game_info_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i = 0; ui1_i < LIST_BOX_IDX_MAX; ui1_i ++)
    {
        if(ui1_display_list_box[ui1_i] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item ,WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui1_display_list_box[ui1_i] != LIST_BOX_IDX_GLL)
            {
                i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item_ex ,WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    ui2_crnt_ht = _get_vid_game_low_latency_idx();

    i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex,
                        WGL_CMD_LB_HLT_ELEM,
                        WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                        NULL);    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret= c_wgl_set_focus(t_list_box[LIST_BOX_IDX_GLL].h_lb_item_ex,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _show_lb_vrr_ex_view(BOOL b_repaint)
{
    INT32       i4_ret;
    UINT16      ui2_crnt_ht;
    UINT8       ui1_i;

    i4_ret = c_wgl_set_visibility(h_lb_device_name,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _gaming_mode_game_info_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i = 0; ui1_i < LIST_BOX_IDX_MAX; ui1_i ++)
    {
        if(ui1_display_list_box[ui1_i] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item ,WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui1_display_list_box[ui1_i] != LIST_BOX_IDX_VRR)
            {
                i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item_ex ,WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    ui2_crnt_ht = _get_vid_vss_idx();

    i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex,
                        WGL_CMD_LB_HLT_ELEM,
                        WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                        NULL);    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret= c_wgl_set_focus(t_list_box[LIST_BOX_IDX_VRR].h_lb_item_ex,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _show_lb_game_hdr_ex_view(BOOL b_repaint)
{
    INT32       i4_ret;
    UINT16      ui2_crnt_ht;
    UINT8       ui1_i;

    i4_ret = c_wgl_set_visibility(h_lb_device_name,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _gaming_mode_game_info_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i = 0; ui1_i < LIST_BOX_IDX_MAX; ui1_i ++)
    {
        if(ui1_display_list_box[ui1_i] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item ,WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui1_display_list_box[ui1_i] != LIST_BOX_IDX_GAME_HDR)
            {
                i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item_ex ,WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    ui2_crnt_ht = _get_vid_game_hdr_idx();

    i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex,
                        WGL_CMD_LB_HLT_ELEM,
                        WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                        NULL);    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret= c_wgl_set_focus(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item_ex,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _show_lb_hdmi_mode_ex_view(BOOL b_repaint)
{
    INT32       i4_ret;
    UINT16      ui2_crnt_ht;
    UINT8       ui1_i;

    i4_ret = c_wgl_set_visibility(h_lb_device_name,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _gaming_mode_game_info_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i = 0; ui1_i < LIST_BOX_IDX_MAX; ui1_i ++)
    {
        if(ui1_display_list_box[ui1_i] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item ,WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui1_display_list_box[ui1_i] != LIST_BOX_IDX_HDMI_MODE)
            {
                i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_i]].h_lb_item_ex ,WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }
    ui2_crnt_ht = _get_inp_hdmi_mode_idx();

    i4_ret = c_wgl_do_cmd(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex,
                        WGL_CMD_LB_HLT_ELEM,
                        WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                        NULL);    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret= c_wgl_set_focus(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item_ex,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _change_view(GAMING_MODE_VIEW_TYPE_T e_gaming_mode_view_type, UINT8 ui1FocusIdx)
{
    INT32        i4_ret;
    INT16   i2_index;

    e_view_type = e_gaming_mode_view_type;

    /* tips move */
    _gaming_mode_setting_update_shadow_item_pos();

    switch(e_view_type)
    {
        case GAMING_MODE_VIEW_INIT:
        {
            i4_ret = menu_main_set_title(MLM_MENU_KEY_VID_GAMEING_ENGINE);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret=_show_init_view(FALSE, ui1FocusIdx);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_custom_page_gaming_mode_setting_refresh_item();
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        break;
        case GAMING_MODE_VIEW_LB_GLL_EX:
        {
            if(t_list_box[LIST_BOX_IDX_GLL].b_is_need_show)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                menu_main_set_title(t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_title);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret =_show_lb_gll_ex_view(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }
        }
        break;

        case GAMING_MODE_VIEW_LB_VRR_EX:
        {
            if(t_list_box[LIST_BOX_IDX_VRR].b_is_need_show)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                menu_main_set_title(t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_title);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret =_show_lb_vrr_ex_view(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }
        }
        break;

        case GAMING_MODE_VIEW_LB_GAME_HDR_EX:
        {
            if(t_list_box[LIST_BOX_IDX_GAME_HDR].b_is_need_show)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                menu_main_set_title(t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_title);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret =_show_lb_game_hdr_ex_view(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }
        }
        break;

        case GAMING_MODE_VIEW_LB_HDMI_MODE_EX:
        {
            if(t_list_box[LIST_BOX_IDX_HDMI_MODE].b_is_need_show)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_help_tip));
                MENU_LOG_ON_FAIL(i4_ret);

                menu_main_set_title(t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_title);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret =_show_lb_hdmi_mode_ex_view(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }
        }
        break;
        default:
        break;
    }
    return MENUR_OK;
}

static INT32 _device_name_update(VOID)
{
    INT32   i4_ret;
    ISL_REC_T t_isl_rec;
    UTF16_T w2s_dev_name_str[128] = {0};
    UTF16_T w2s_token [] = L"Skip";
    UTF16_T w2s_usr_inp_name [APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    CHAR s_usr_inp_name [APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
    if( (t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
      &&(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI) )
    {
        bIsSrcHDMI = TRUE;
    }
    else
    {
        bIsSrcHDMI = FALSE;
    }

    if( bIsSrcHDMI )
    {
        i4_ret = a_cfg_custom_get_inp_name_with_cec_name (&t_isl_rec, w2s_usr_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
        if (i4_ret != APP_CFGR_OK)
        {
            return ISLR_FAIL;
        }
        c_uc_w2s_to_ps (w2s_usr_inp_name, s_usr_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    }
    else
    {
        i4_ret = a_cfg_custom_get_inp_name(t_isl_rec.ui1_id, s_usr_inp_name);
        if (i4_ret != APP_CFGR_OK)
        {
             return ISLR_FAIL;
        }
        c_uc_ps_to_w2s(s_usr_inp_name,w2s_usr_inp_name,APP_CFG_CUSTOM_INP_NAME_LEN);
    }
    UTF16_T* pw2s_display_name = a_isl_get_display_name(&t_isl_rec);
    if (a_cfg_custom_is_inp_name_empty (s_usr_inp_name))
    {
        /* No custom input label. Use actual input name instead. */
        c_uc_w2s_strcpy(w2s_dev_name_str, pw2s_display_name);
    }
    else
    {
        UTF16_T w2s_inp_name [50] = {0};
        /* Custom label exists. Check whether it is "Skip". */
        if (c_uc_w2s_strcmp (w2s_token, w2s_usr_inp_name) == 0)
        {
            c_uc_w2s_strcpy (w2s_inp_name, pw2s_display_name);
            c_uc_w2s_strcat (w2s_inp_name, L":Skip");

            c_uc_w2s_strcpy (w2s_dev_name_str, w2s_inp_name);
        }
        else
        {
            c_uc_w2s_strcpy (w2s_dev_name_str, pw2s_display_name);
            c_uc_w2s_strcat(w2s_dev_name_str, L" ");
            c_uc_w2s_strcat (w2s_dev_name_str, w2s_usr_inp_name);
        }
    }
    /* Set Title language */
    i4_ret = c_wgl_do_cmd(h_lb_device_name,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(w2s_dev_name_str),
                          WGL_PACK(c_uc_w2s_strlen(w2s_dev_name_str)));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
static INT32 _change_lang(VOID)
{
    INT32  i4_ret = 0;
    UINT8  ui2_i = 0;
    UINT16 ui2_elem_num=0;
    UINT8  ui1_cnt;

    for(ui1_cnt = 0; ui1_cnt < LIST_BOX_IDX_MAX; ui1_cnt ++)
    {
        if(ui1_display_list_box[ui1_cnt] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret=menu_list_chg_lang(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item,
                                      t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_title,
                                      t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_elem_first,
                                      t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_elem_last);
            MENU_LOG_ON_FAIL(i4_ret);
            menu_list_adjust_rect(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item);

            ui2_elem_num = t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_elem_last - t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_elem_first + 1;

            i4_ret=c_wgl_do_cmd(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item_ex,
                    WGL_CMD_LB_SET_ELEM_NUM,
                    WGL_PACK(ui2_elem_num),
                    NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
            {
                i4_ret = c_wgl_do_cmd(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item_ex,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2 (ui2_i, 0),
                                WGL_PACK(MENU_TEXT(t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_elem_first + ui2_i)));
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }


    i4_ret=menu_change_help_tip_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _gaming_mode_setting_update_shadow_item_pos(VOID)
{
    INT32               i4_ret = 0;
    INT32               i4_item_idx = 0;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);
    switch (e_view_type)
    {
        case GAMING_MODE_VIEW_INIT:
        {
            i4_item_idx = 11;
            break;
        }
        case GAMING_MODE_VIEW_LB_GLL_EX:
        {
            i4_item_idx = t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first + 1;
            break;
        }
        case GAMING_MODE_VIEW_LB_VRR_EX:
        {
            i4_item_idx = t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first + 1;
            break;
        }
        case GAMING_MODE_VIEW_LB_GAME_HDR_EX:
        {
            i4_item_idx = t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first + 1;
            break;
        }
        case GAMING_MODE_VIEW_LB_HDMI_MODE_EX:
        {
            i4_item_idx = t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_last - t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first + 1;
            break;
        }
        default:
            break;
    }
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * i4_item_idx + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
static INT32 _gaming_mode_list_box_status_update(VOID)
{
    UINT8 ui8_i = 0;
    UINT8 ui8_j = 0;
    UINT8 ui8_k = 0;

    t_list_box[LIST_BOX_IDX_GLL].b_is_need_show = TRUE;
    t_list_box[LIST_BOX_IDX_GLL].b_is_need_enable = _is_item_game_low_latency_enable();

    t_list_box[LIST_BOX_IDX_GAME_HDR].b_is_need_show = !_is_game_hdr_hidden();
    t_list_box[LIST_BOX_IDX_GAME_HDR].b_is_need_enable = _is_item_game_hdr_enable();

    for(ui8_i = 0; ui8_i < LIST_BOX_IDX_MAX; ui8_i++)
    {
        ui1_display_list_box[ui8_i] = LIST_BOX_CANNOT_DISPLAY;
        ui1_enable_list_box[ui8_i] = LIST_BOX_CANNOT_ENABLE;
        if(t_list_box[ui8_i].b_is_need_show == TRUE)
        {
            ui1_display_list_box[ui8_j] = ui8_i;
            ui8_j++;
            if(t_list_box[ui8_i].b_is_need_enable== TRUE)
            {
                ui1_enable_list_box[ui8_k] = ui8_i;
                ui8_k++;
            }
        }

    }
    return MENUR_OK;
}

static INT32 _gaming_mode_list_box_init(VOID)
{
    UINT8 ui8_i,ui8_j = 0;
    UINT8 ui8_k = 0;

    /* Gaming Low Latency */
    t_list_box[LIST_BOX_IDX_GLL].b_is_need_show = TRUE;
    t_list_box[LIST_BOX_IDX_GLL].b_is_need_enable = _is_item_game_low_latency_enable();
    t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_title = MLM_MENU_KEY_VID_GAME_LOW_LATENCY;
    t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_first = MLM_MENU_KEY_VID_GLL_AUTO;
    t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_elem_last = MLM_MENU_KEY_VID_GLL_ON;
    t_list_box[LIST_BOX_IDX_GLL].ui2_msgid_help_tip =  MLM_MENU_KEY_TAB_HELP_GAME_MODE;
    t_list_box[LIST_BOX_IDX_GLL].lb_item_proc_fct = _lb_gaming_low_latency_proc_fct;
    t_list_box[LIST_BOX_IDX_GLL].lb_item_ex_proc_fct= _lb_gaming_low_latency_ex_proc_fct;

    /* Variable Refresh Rate */
    t_list_box[LIST_BOX_IDX_VRR].b_is_need_show = a_cfg_cust_is_variable_refresh_rate_support();
    t_list_box[LIST_BOX_IDX_VRR].b_is_need_enable= a_cfg_cust_is_variable_refresh_rate_support();
    t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_title = MLM_MENU_KEY_VID_VARIABLE_REFRESH_RATE;
    t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_first = MLM_MENU_KEY_MENU_COMMON_OFF;
    t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_elem_last = MLM_MENU_KEY_MENU_COMMON_ON;
    t_list_box[LIST_BOX_IDX_VRR].ui2_msgid_help_tip =  MLM_MENU_KEY_VID_VARIABLE_REFRESH_RATE_TIP;
    t_list_box[LIST_BOX_IDX_VRR].lb_item_proc_fct = _lb_variable_refresh_rate_proc_fct;
    t_list_box[LIST_BOX_IDX_VRR].lb_item_ex_proc_fct= _lb_variable_refresh_rate_ex_proc_fct;

    /* Game HDR */
    t_list_box[LIST_BOX_IDX_GAME_HDR].b_is_need_show = !_is_game_hdr_hidden();
    t_list_box[LIST_BOX_IDX_GAME_HDR].b_is_need_enable = _is_item_game_hdr_enable();

    t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_title = MLM_MENU_KEY_VID_GAME_HDR;
    t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_first = MLM_MENU_KEY_MENU_COMMON_OFF;
    t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_elem_last = MLM_MENU_KEY_MENU_COMMON_ON;
    t_list_box[LIST_BOX_IDX_GAME_HDR].ui2_msgid_help_tip =  MLM_MENU_KEY_VID_GAME_HDR_TIP;
    t_list_box[LIST_BOX_IDX_GAME_HDR].lb_item_proc_fct = _lb_game_hdr_proc_fct;
    t_list_box[LIST_BOX_IDX_GAME_HDR].lb_item_ex_proc_fct= _lb_game_hdr_ex_proc_fct;

    /* HDMI Mode */
    t_list_box[LIST_BOX_IDX_HDMI_MODE].b_is_need_show = TRUE;
    t_list_box[LIST_BOX_IDX_HDMI_MODE].b_is_need_enable = _is_hdmi_mode_enable();
    t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_title = MLM_MENU_KEY_VID_HDMI_MODE;
#ifndef MT5583_MODEL
    t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first = MLM_MENU_KEY_HDMI_MODE_AUTO;
    t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_last = MLM_MENU_KEY_HDMI_MODE_1_4;
    t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_help_tip =  MLM_MENU_KEY_HDMI_MODE_TIP;
#else
    t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_first = MLM_MENU_KEY_HDMI_MODE_SCDS_AUTO;
    t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_elem_last = MLM_MENU_KEY_HDMI_MODE_SCDS_1_4;
    t_list_box[LIST_BOX_IDX_HDMI_MODE].ui2_msgid_help_tip =  MLM_MENU_KEY_HDMI_MODE_SCDS_TIP;
#endif
    t_list_box[LIST_BOX_IDX_HDMI_MODE].lb_item_proc_fct = _lb_hdmi_mode_proc_fct;
    t_list_box[LIST_BOX_IDX_HDMI_MODE].lb_item_ex_proc_fct= _lb_hdmi_mode_ex_proc_fct;

    /* Record the listbox index in display*/
    for(ui8_i = 0; ui8_i < LIST_BOX_IDX_MAX; ui8_i ++)
    {
        ui1_display_list_box[ui8_i] = LIST_BOX_CANNOT_DISPLAY;
        ui1_enable_list_box[ui8_i] = LIST_BOX_CANNOT_ENABLE;
        if(t_list_box[ui8_i].b_is_need_show == TRUE)
        {
            ui1_display_list_box[ui8_j] = ui8_i;
            ui8_j ++;
            if(t_list_box[ui8_i].b_is_need_enable== TRUE)
            {
                ui1_enable_list_box[ui8_k] = ui8_i;
                ui8_k++;
            }
        }
    }
    return MENUR_OK;
}

static INT32 _gaming_mode_list_box_create(VOID)
{
    INT32 i4_ret;
    UINT8 ui1_cnt;

    for(ui1_cnt = 0; ui1_cnt < LIST_BOX_IDX_MAX; ui1_cnt ++)
    {
        if(ui1_display_list_box[ui1_cnt] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret = menu_list_create(h_cnt_frm,
                                      ui1_cnt + 1,
                                      (t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_elem_last - t_list_box[ui1_display_list_box[ui1_cnt]].ui2_msgid_elem_first) + 1,
                                      t_list_box[ui1_display_list_box[ui1_cnt]].lb_item_proc_fct,
                                      &t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item);
            MENU_CHK_FAIL(i4_ret);
        }
    }
    return MENUR_OK;
}

static INT32 _gaming_mode_list_box_create_ex(VOID)
{
    INT32  i4_ret;
    UINT8  ui1_cnt;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    for(ui1_cnt = 0; ui1_cnt < LIST_BOX_IDX_MAX; ui1_cnt ++)
    {
        if(ui1_display_list_box[ui1_cnt] != LIST_BOX_CANNOT_DISPLAY)
        {
            i4_ret = menu_list2_create(h_cnt_frm,
                                       &t_rect,
                                       t_list_box[ui1_display_list_box[ui1_cnt]].lb_item_ex_proc_fct,
                                       &t_lb_init,
                                       NULL,
                                       &t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item_ex);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd (t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item_ex,
                                       WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                                       WGL_PACK(& t_img_elem),
                                       NULL);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item_ex,
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(0, WGL_CLR_TEXT),
                                  WGL_PACK(&t_lb_color) );
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(t_list_box[ui1_display_list_box[ui1_cnt]].h_lb_item_ex,
                                          WGL_SW_HIDE);
            MENU_CHK_FAIL(i4_ret);
        }
    }
    return MENUR_OK;
}
static INT32 _update_game_info_title(VOID)
{
    INT32  i4_ret;
    UTF16_T w2s_res_str[64]={0};

    c_uc_w2s_strcpy (w2s_res_str,MENU_TEXT(MLM_MENU_KEY_GAMING_MODE_INFO_TITLE));

    i4_ret = c_wgl_do_cmd(t_game_info[TEXT_GAME_INFO_TITLE].h_txt_item,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_res_str),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_res_str)));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _update_game_info_resolution(VOID)
{
    INT32  i4_ret;
    CHAR    res_str[64] = {0};
    UTF16_T w2s_res_str[64] = {0};
    UTF16_T w2s_str_tmp[64]={0};

    c_uc_w2s_strcpy (w2s_res_str, GAME_INFO_PRE_RETRACT);
    c_uc_w2s_strcat (w2s_res_str, MENU_TEXT(MLM_MENU_KEY_GAMING_MODE_INFO_RES));
    c_uc_w2s_strcat (w2s_res_str, L": ");

    i4_ret = menu_ver_info_get_resolution(res_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_ps_to_w2s(res_str, w2s_str_tmp, sizeof(w2s_str_tmp));

    c_uc_w2s_strcat(w2s_res_str, w2s_str_tmp);

    i4_ret = c_wgl_do_cmd(t_game_info[TEXT_GAME_INFO_RES].h_txt_item,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_res_str),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_res_str)));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _update_game_info_frame_rate(VOID)
{
    INT32  i4_ret;
    CHAR    frm_rt_str[64] = {0};
    UTF16_T w2s_frm_rt_str[64] = {0};
    UTF16_T w2s_str_tmp[64] = {0};

    c_uc_w2s_strcpy (w2s_frm_rt_str, GAME_INFO_PRE_RETRACT);
    c_uc_w2s_strcat (w2s_frm_rt_str, MENU_TEXT(MLM_MENU_KEY_GAMING_MODE_INFO_FRM_RT));
    c_uc_w2s_strcat (w2s_frm_rt_str, L": ");

    i4_ret = menu_ver_info_get_frame_rate(frm_rt_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_ps_to_w2s(frm_rt_str, w2s_str_tmp, sizeof(w2s_str_tmp));

    c_uc_w2s_strcat(w2s_frm_rt_str, w2s_str_tmp);

    i4_ret = c_wgl_do_cmd(t_game_info[TEXT_GAME_INFO_FRM_RT].h_txt_item,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_frm_rt_str),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_frm_rt_str)));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _update_game_info_hdr(VOID)
{
    INT32   i4_ret;
    CHAR    hdr_str[64] = {0};
    UTF16_T w2s_hdr_str[64] = {0};
    UTF16_T w2s_str_tmp[64] = {0};

    c_uc_w2s_strcpy (w2s_hdr_str, GAME_INFO_PRE_RETRACT);
    c_uc_w2s_strcat (w2s_hdr_str, MENU_TEXT(MLM_MENU_KEY_GAMING_MODE_INFO_HDR));
    c_uc_w2s_strcat (w2s_hdr_str, L": ");

    i4_ret = ver_info_get_hdr_type(hdr_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_ps_to_w2s(hdr_str, w2s_str_tmp, sizeof(w2s_str_tmp));

    c_uc_w2s_strcat(w2s_hdr_str, w2s_str_tmp);

    i4_ret = c_wgl_do_cmd(t_game_info[TEXT_GAME_INFO_HDR].h_txt_item,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_hdr_str),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_hdr_str)));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _update_game_info_vrr(VOID)
{
    INT32   i4_ret;
    UTF16_T w2s_vrr_str[64] = {0};
    UTF16_T w2s_str_tmp[64] = {0};
    BOOL b_vrr_apply = FALSE;

    c_uc_w2s_strcpy (w2s_vrr_str, GAME_INFO_PRE_RETRACT);
    c_uc_w2s_strcat (w2s_vrr_str, MENU_TEXT(MLM_MENU_KEY_GAMING_MODE_INFO_VRR));
    c_uc_w2s_strcat (w2s_vrr_str, L": ");

    b_vrr_apply = a_cfg_cust_drv_get_vrr_status();

    if(b_vrr_apply)
    {
        c_uc_w2s_strcpy(w2s_str_tmp, L"YES");
    }
    else
    {
        c_uc_w2s_strcpy(w2s_str_tmp, L"NO");
    }

    c_uc_w2s_strcat(w2s_vrr_str, w2s_str_tmp);

    i4_ret = c_wgl_do_cmd(t_game_info[TEXT_GAME_INFO_VRR].h_txt_item,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_vrr_str),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_vrr_str)));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;

}

static INT32 _update_game_info_audio_out(VOID)
{
    INT32  i4_ret;
    CHAR    aud_ot_str[64] = {0};
    UTF16_T w2s_aud_ot_str[64] = {0};
    UTF16_T w2s_str_tmp[64] = {0};

    c_uc_w2s_strcpy (w2s_aud_ot_str, GAME_INFO_PRE_RETRACT);
    c_uc_w2s_strcat (w2s_aud_ot_str, MENU_TEXT(MLM_MENU_KEY_GAMING_MODE_INFO_AUD_OT));
    c_uc_w2s_strcat (w2s_aud_ot_str, L":");

    i4_ret = menu_ver_info_get_audio_out(aud_ot_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_ps_to_w2s(aud_ot_str, w2s_str_tmp, sizeof(w2s_str_tmp));

    c_uc_w2s_strcat(w2s_aud_ot_str, w2s_str_tmp);

    i4_ret = c_wgl_do_cmd(t_game_info[TEXT_GAME_INFO_AUD_OT].h_txt_item,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_aud_ot_str),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_aud_ot_str)));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

static INT32 _gaming_mode_game_info_create(VOID)
{
    INT32                       i4_ret;
    UINT8                       ui1_i;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_INSET_T t_inset = {FRAME_LEFT_RIGHT_INTV,
                           FRAME_LEFT_RIGHT_INTV,
                           3*4/3,
                           0};

    t_game_info[TEXT_GAME_INFO_TITLE]._info_update_fct = _update_game_info_title;
    t_game_info[TEXT_GAME_INFO_RES]._info_update_fct = _update_game_info_resolution;
    t_game_info[TEXT_GAME_INFO_FRM_RT]._info_update_fct = _update_game_info_frame_rate;
    t_game_info[TEXT_GAME_INFO_HDR]._info_update_fct = _update_game_info_hdr;
    t_game_info[TEXT_GAME_INFO_VRR]._info_update_fct = _update_game_info_vrr;
    t_game_info[TEXT_GAME_INFO_AUD_OT]._info_update_fct = _update_game_info_audio_out;

    /* Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    /* Color */
    c_memset(& t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_bk2_txt_disable;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk2_txt_disable;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;

    /* Image */
    c_memset(& t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bar_plain;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bar_plain;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bar_plain;

    for(ui1_i = 0; ui1_i < TEXT_GAME_INFO_MAX; ui1_i++)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_INSET_L,
                         GAME_INFO_V_HEIGHT_OFFSET+GAME_INFO_ITEM_V_HEIGHT*ui1_i,
                         MENU_ITEM_V_WIDE,
                         GAME_INFO_ITEM_V_HEIGHT);

         i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128),
                                 NULL,
                                 &t_game_info[ui1_i].h_txt_item);
        if (i4_ret < 0)
        {
            return MENUR_CANT_CREATE_WIDGET;
        }

        /* Set Insets */
        i4_ret = c_wgl_do_cmd(t_game_info[ui1_i].h_txt_item,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Alignment */
        i4_ret = c_wgl_do_cmd(t_game_info[ui1_i].h_txt_item,
                              WGL_CMD_TEXT_SET_ALIGN,
                              (VOID*)WGL_AS_LEFT_CENTER,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Font */
        i4_ret = c_wgl_do_cmd (t_game_info[ui1_i].h_txt_item,
                               WGL_CMD_GL_SET_FONT,
                               (void*)&t_fnt_info,
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(t_game_info[ui1_i].h_txt_item,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info) );
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(t_game_info[ui1_i].h_txt_item,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(t_game_info[ui1_i].h_txt_item,
                                      WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _gaming_mode_game_info_update(VOID)
{
    INT32                       i4_ret;
    UINT8                       ui1_i;

    for(ui1_i = 0; ui1_i < TEXT_GAME_INFO_MAX; ui1_i++)
    {
        i4_ret = t_game_info[ui1_i]._info_update_fct();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}
static INT32 _gaming_mode_game_info_show(VOID)
{
    INT32                       i4_ret;
    UINT8                       ui1_i;

    i4_ret = _gaming_mode_game_info_update();
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_i = 0; ui1_i < TEXT_GAME_INFO_MAX; ui1_i++)
    {
        i4_ret = c_wgl_set_visibility(t_game_info[ui1_i].h_txt_item, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}
static INT32 _gaming_mode_game_info_hide(VOID)
{
    INT32                       i4_ret;
    UINT8                       ui1_i;

    for(ui1_i = 0; ui1_i < TEXT_GAME_INFO_MAX; ui1_i++)
    {
        i4_ret = c_wgl_set_visibility(t_game_info[ui1_i].h_txt_item, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 menu_custom_page_gaming_mode_setting_refresh_item(VOID)
{
    INT32  i4_ret = MENUR_OK;

    if(t_list_box[LIST_BOX_IDX_GLL].b_is_need_show)
    {
        menu_list_set_idx(t_list_box[LIST_BOX_IDX_GLL].h_lb_item, _get_vid_game_low_latency_idx());
        menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GLL].h_lb_item);
    }

    if(t_list_box[LIST_BOX_IDX_VRR].b_is_need_show)
    {
        menu_list_set_idx(t_list_box[LIST_BOX_IDX_VRR].h_lb_item, _get_vid_vss_idx());
        menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_VRR].h_lb_item);
    }

    if(t_list_box[LIST_BOX_IDX_GAME_HDR].b_is_need_show)
    {
        menu_list_set_idx(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item, _get_vid_game_hdr_idx());
        menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_GAME_HDR].h_lb_item);
    }

    if(t_list_box[LIST_BOX_IDX_HDMI_MODE].b_is_need_show)
    {
        menu_list_set_idx(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item, _get_inp_hdmi_mode_idx());
        menu_list_adjust_rect(t_list_box[LIST_BOX_IDX_HDMI_MODE].h_lb_item);
    }

    /* navigation */
    i4_ret = _set_nav();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _gaming_mode_game_info_update();
    MENU_CHK_FAIL(i4_ret);

    menu_pm_repaint();

    return MENUR_OK;
}
static INT32 _set_nav(VOID)
{
    INT32   i4_ret = 0;
    WGL_KEY_LINK_T      at_key_lnk[2];
    UINT8   ui1_cnt;
    for(ui1_cnt = 0; ui1_cnt < LIST_BOX_IDX_MAX; ui1_cnt ++)
    {
        if(ui1_enable_list_box[ui1_cnt] != LIST_BOX_CANNOT_ENABLE)
        {
            if((ui1_cnt == (LIST_BOX_IDX_MAX-1)) || (ui1_enable_list_box[ui1_cnt+1] == LIST_BOX_CANNOT_ENABLE))
            {
                if(ui1_cnt == 0)
                {
                    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
                    at_key_lnk[0].h_widget = h_backbar;
                }
                else
                {
                    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
                    at_key_lnk[0].h_widget = t_list_box[ui1_enable_list_box[ui1_cnt-1]].h_lb_item;
                }
                i4_ret = c_wgl_set_navigation(t_list_box[ui1_enable_list_box[ui1_cnt]].h_lb_item, 1, at_key_lnk);
                MENU_CHK_FAIL(i4_ret);
            }
            else
            {
                if(ui1_cnt == 0)
                {
                    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
                    at_key_lnk[0].h_widget = h_backbar;
                }
                else
                {
                    at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
                    at_key_lnk[0].h_widget = t_list_box[ui1_enable_list_box[ui1_cnt-1]].h_lb_item;
                }
                at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
                at_key_lnk[1].h_widget = t_list_box[ui1_enable_list_box[ui1_cnt+1]].h_lb_item;
                i4_ret = c_wgl_set_navigation(t_list_box[ui1_enable_list_box[ui1_cnt]].h_lb_item, 2, at_key_lnk);
                MENU_CHK_FAIL(i4_ret);
            }
        }
    }
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 _ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;

    T_HELP_TIP_REG t_help_tip_reg;

    c_memset(&t_help_tip_reg, 0, sizeof(t_help_tip_reg));

    ui4_page_id = _ui4_page_id;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret=menu_get_homebar_handle(&h_homebar);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_get_backbar_handle(&h_backbar);
    MENU_LOG_ON_FAIL(i4_ret);

    /* device name */
    i4_ret = menu_action_create(h_cnt_frm,
                               0,
                               NULL,
                               &h_lb_device_name);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _gaming_mode_list_box_init();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _gaming_mode_list_box_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _gaming_mode_list_box_create_ex();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _gaming_mode_game_info_create();
    MENU_CHK_FAIL(i4_ret);

    /* set visibility */
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
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect = {0};

    i4_ret = menu_show_homebar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_show_backbar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret =_change_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    _gaming_mode_list_box_status_update();

    i4_ret = _change_view(GAMING_MODE_VIEW_INIT, ui1_display_list_box[0]);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32  i4_ret = 0;

    //_change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX);
    _show_init_view(FALSE, ui1_display_list_box[0]);

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32   i4_ret = MENUR_OK;
    /* set callback function for homebar */
    menu_set_homebar_proc (_homebar_proc_fct) ;

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret =_change_lang();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

INT32 menu_page_gaming_mode_init(VOID)
{
    t_g_menu_page_gaming_mode.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_gaming_mode.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_gaming_mode.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_gaming_mode.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_gaming_mode.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_gaming_mode.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_gaming_mode.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}


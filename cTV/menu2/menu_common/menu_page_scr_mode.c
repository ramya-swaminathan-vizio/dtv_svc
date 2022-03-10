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
 * $RCSfile: menu_page_scr_mode.c,v $
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
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_svctx.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "app_util/a_cfg.h"
#include "app_client.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "res/menu2/menu_custom_dialog.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/nav/nav_colors.h"
#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "app_util/a_screen_mode.h"

#include "u_atsc_si_eng.h"
#include "c_atsc_si_eng.h"

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#if 1//Cedric 0416
#include "c_wgl_image.h"
#include "res/nav/nav_img_rc.h"
#include "nav/banner2/banner.h"
#include "nav/banner2/a_banner.h"
#include "amb/a_amb.h"
#include "nav/nav_bnr_state_mgr.h"
#include "res/nav/banner2/banner_rc.h"
#endif
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#if 1//Cedric
#define SCR_MODE_TITLE_X    (0)
#define SCR_MODE_TITLE_Y    (0)
#define SCR_MODE_TITLE_W    (NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W)
#define SCR_MODE_TITLE_H    (NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_H/2)

#define SCR_MODE_BTN_X      (0)
#define SCR_MODE_BTN_Y      (0)
#define SCR_MODE_BTN_W      (NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W)
#define SCR_MODE_BTN_H      (NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_H)

#define SCR_MODE_TXT_X      (0)
#define SCR_MODE_TXT_Y      (0)
#define SCR_MODE_TXT_W      (NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W)
#define SCR_MODE_TXT_H      (NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_H)

#define SCR_SHADOW_ICON_X      (0)
#define SCR_SHADOW_ICON_Y     (0)
#define SCR_SHADOW_ICON_W      (NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_W)
#define SCR_SHADOW_ICON_H      (10)
#else
#define SCR_MODE_TITLE_X    (0)
#define SCR_MODE_TITLE_Y    (2)
#define SCR_MODE_TITLE_W    (SCR_MODE_FRAME_W)
#define SCR_MODE_TITLE_H    (28)

#define SCR_MODE_BTN_X      (3)
#define SCR_MODE_BTN_Y      (30)
#define SCR_MODE_BTN_W      (90)
#define SCR_MODE_BTN_H      (77)

#define SCR_MODE_TXT_X      (3)
#define SCR_MODE_TXT_Y      (77)
#define SCR_MODE_TXT_W      (90)
#define SCR_MODE_TXT_H      (28)
#endif

#if 1//Cedric
#define SCR_MODE_FRAME_X_OFFSET	(-4)

#define SCR_MODE_GAP (92)

#define SCR_MODE_FRAME_W    (SCR_MODE_BTN_W)
#define SCR_MODE_FRAME_H    (SCR_MODE_BTN_H * 4)
#define SCR_MODE_FRAME_X    (NAV_BANNER_ROOT_FRM_WGL_SX + NAV_BANNER_LEVEL_1_ASPECT_FRM_WGL_SX + SCR_MODE_FRAME_X_OFFSET)
#define SCR_MODE_FRAME_Y   (NAV_BANNER_ROOT_FRM_WGL_SY)
#else
#define SCR_MODE_GAP (92)

#define SCR_MODE_FRAME_W    (SCR_MODE_GAP * 4 + 4)
#define SCR_MODE_FRAME_H    (115)
#define SCR_MODE_FRAME_X    ((SCREEN_W - SCR_MODE_FRAME_W)/2)
#define SCR_MODE_FRAME_Y    ((SCREEN_H - SCR_MODE_FRAME_H)/2)
#endif

#define CFG_ID_SCREEN_MODE           CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE)

#define LARGEST_SCR_MODE_NUMBER (4)

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef enum _SCR_MODE_BUTTON_T
{
    SCR_MODE_BUTTON_1 = 0,
    SCR_MODE_BUTTON_2,
    SCR_MODE_BUTTON_3,
    SCR_MODE_BUTTON_4,
    SCR_MODE_BUTTON_LAST

}SCR_MODE_BUTTON_T;

typedef struct _SCR_MODE_VIEW_T
{
    HANDLE_T        h_frame;
    HANDLE_T        h_title;
    HANDLE_T        h_txt[SCR_MODE_BUTTON_LAST];
    HANDLE_T        h_button[SCR_MODE_BUTTON_LAST];
    BOOL            b_show_warn_msg;
}SCR_MODE_VIEW_T;

typedef struct _SCR_MODE_BUTTON_VIEW_T
{
    UTF16_T *               w2s_str;
    HANDLE_T                h_img;
    HANDLE_T                h_img_hlt;
}SCR_MODE_BUTTON_VIEW_T;

typedef enum _SCR_MODE_INPUT_T
{
    SCR_INPUT_TV,
    SCR_INPUT_HDMI,
    SCR_INPUT_PC,
    SCR_INPUT_DVI,
    SCR_INPUT_LAST_ENUM
}SCR_MODE_INPUT_T;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
#if 1//Cedric
WGL_HIMG_TPL_T h_g_nav_button_default_img = NULL_HANDLE;
WGL_HIMG_TPL_T h_g_nav_button_hover_img = NULL_HANDLE;
HANDLE_T        h_shadow_icon = NULL_HANDLE;
UINT8	ui1_CurrentScrMode = 0xFF;

extern BOOL _crnt_svl_is_empty (VOID);
extern BOOL _crnt_source_is_tv (VOID);
#endif
extern INT32 a_vol_ctrl_set_visibility(BOOL b_is_volume_visible);

MENU_PAGE_FCT_TBL_T             t_g_menu_page_screen_mode;

static SCR_MODE_VIEW_T          t_g_scr_mode_view = {0};
static SCR_MODE_BUTTON_VIEW_T   t_g_scr_mode_button_view[SCR_MODE_BUTTON_LAST];
static SCC_VID_SCREEN_MODE_T    e_g_crnt_screen_mode;
static SCR_MODE_INPUT_T         e_cur_input;
static BOOL                     b_wide_page_show = FALSE;
/*---------------------------------------------------------------------------------
*           Function
*---------------------------------------------------------------------------------*/
#if 1//Cedric
static UINT8 scr_mode_item_resort(UINT8 ui1_idx,UINT8 ui1_curt_idx,UINT8 ui1_max)
{
	if(ui1_idx >= ui1_curt_idx)
	{
		return (ui1_idx - ui1_curt_idx);
	}else
	{
		return (ui1_max - ui1_curt_idx + ui1_idx);
	}
}

static INT32 scr_mode_move_wgl(HANDLE_T h_widget,UINT8 ui1_offset)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;

    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X,
                      SCR_MODE_BTN_Y + (ui1_offset * SCR_MODE_BTN_H),
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);

    i4_ret = c_wgl_move(h_widget,
                        &t_rect,
                        WGL_NO_AUTO_REPAINT);

    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}

static INT32 scr_mode_config_icon(HANDLE_T h_icon,
                            WGL_HIMG_TPL_T  h_img,
                            WGL_HIMG_TPL_T  h_img_hlt)
{
    INT32           i4_ret;
    WGL_IMG_INFO_T  t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_extend.t_enable    = h_img;
    t_img_info.u_img_data.t_extend.t_disable   = h_img;
    t_img_info.u_img_data.t_extend.t_highlight = h_img_hlt;

    i4_ret = c_wgl_do_cmd(h_icon,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_BK),
                 WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 scr_mode_create_icon(HANDLE_T    h_parent,
                            HANDLE_T*   h_handle,
                            GL_RECT_T*  t_rect,
                            HANDLE_T    h_img,
                            HANDLE_T    h_img_hlt)
{
    INT32   i4_ret;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 t_rect,
                                 NULL,
                                 255,
                                 NULL,
                                 NULL,
                                 h_handle);
    MENU_CHK_FAIL(i4_ret);

    return scr_mode_config_icon(*h_handle, h_img, h_img_hlt);
}
#endif
static INT32 scr_mode_get_current_input(VOID)
{
    INT32                       i4_ret;
    TV_WIN_ID_T                 e_focus_id;
    ISL_REC_T                   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resolution;

    c_memset(&t_resolution, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_svctx_get_video_src_resolution(menu_get_crnt_svctx(),&t_resolution);
    MENU_CHK_FAIL(i4_ret);

    if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
    {
        e_cur_input = SCR_INPUT_TV;
    }
    else if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type)
    {
        if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
        {
            e_cur_input = SCR_INPUT_HDMI;
            if (VSH_SRC_TIMING_GRAPHIC == t_resolution.e_timing_type)
            {
                e_cur_input = SCR_INPUT_DVI;
            }
        }
        else if(DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type)
        {
            if (VSH_SRC_TIMING_VIDEO == t_resolution.e_timing_type)
            {
                e_cur_input = SCR_INPUT_TV;
            }
            else
            {
                e_cur_input = SCR_INPUT_PC;
            }
        }
        else
        {
            e_cur_input = SCR_INPUT_TV;
        }
    }
    else
    {
        e_cur_input = SCR_INPUT_TV;
    }

    return MENUR_OK;
}

static INT32 scr_mode_get_aspect_ratio(VSH_SRC_ASPECT_RATIO_T* pe_src_asp_ratio)
{
    INT32 i4_ret;
    VSH_SRC_RESOLUTION_INFO_T   t_src_res;
    CHAR                        s_disp_name[SYS_NAME_LEN + 1];

    c_memset(&t_src_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_CHK_FAIL(i4_ret);

    i4_ret =a_cfg_av_get_timing(s_disp_name, &t_src_res);
    MENU_CHK_FAIL(i4_ret);

    *pe_src_asp_ratio = a_sml_get_src_asp_ratio(&t_src_res);
    if (VSH_SRC_ASPECT_RATIO_UNKNOWN == *pe_src_asp_ratio )
    {
        *pe_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
    }

    return MENUR_OK;
}

static INT32 scr_mode_update_disp_icon(UINT8 ui1_idx,
                                            VSH_SRC_ASPECT_RATIO_T    e_src_asp_ratio,
                                            SCC_VID_SCREEN_MODE_T     e_screen_mode)
{
    INT32 i4_ret;

    switch (e_screen_mode)
    {
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:      /* Zoom */
			#if 1//Cedric
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_nav_banner_new_aspect_zoom_lt_img;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt= h_g_nav_banner_new_aspect_zoom_lt_img;
			#else
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_zoom1;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt= h_g_menu_img_wide_zoom1_hlt;
			#endif
            break;

        case SCC_VID_SCREEN_MODE_NORMAL:
            i4_ret = scr_mode_get_current_input();
            MENU_CHK_FAIL(i4_ret);

            if ((SCR_INPUT_PC == e_cur_input) ||
                (SCR_INPUT_DVI == e_cur_input))      /* Normal */
            {
				#if 1//Cedric
                t_g_scr_mode_button_view[ui1_idx].h_img = h_g_nav_banner_new_aspect_normal_lt_img; /*h_g_nav_banner_new_aspect_panoramic_lt_img;*/
                t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_nav_banner_new_aspect_normal_lt_img; /*h_g_nav_banner_new_aspect_panoramic_lt_img;*/
				#else
                t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_pan_scan;/*(VSH_SRC_ASPECT_RATIO_4_3 == e_src_asp_ratio) ?
                                                      h_g_menu_img_wide_pan_scan : h_g_menu_img_wide_43;*/
                t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_menu_img_wide_pan_scan_hlt;/*(VSH_SRC_ASPECT_RATIO_4_3 == e_src_asp_ratio) ?
                                                      h_g_menu_img_wide_pan_scan_hlt: h_g_menu_img_wide_43_hlt;*/
				#endif
            }
            else
            {
            	#if 1//Cedric
                t_g_scr_mode_button_view[ui1_idx].h_img = h_g_nav_banner_new_aspect_normal_lt_img;
                t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_nav_banner_new_aspect_normal_lt_img;
				#else
                t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_43;
                t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_menu_img_wide_43_hlt;
				#endif
            }
            break;

        case SCC_VID_SCREEN_MODE_LETTERBOX:     /* Stretch */
			#if 1//Cedric
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_nav_banner_new_aspect_stretch_lt_img;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_nav_banner_new_aspect_stretch_lt_img;
			#else
           	t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_pan_scan;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt= h_g_menu_img_wide_pan_scan_hlt;
			#endif
            break;

#if 0
        case SCC_VID_SCREEN_MODE_PAN_SCAN:      /* Unused */
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_zoom1;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt= h_g_menu_img_wide_zoom1_hlt;
            break;
#endif
        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:   /* Panoramic */
			#if 1//Cedric
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_nav_banner_new_aspect_panoramic_lt_img;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_nav_banner_new_aspect_panoramic_lt_img;
			#else
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_pan_scan;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_menu_img_wide_pan_scan_hlt;
			#endif
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:    /* Wide */
			#if 1//Cedric
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_nav_banner_new_aspect_wide_lt_img;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt= h_g_nav_banner_new_aspect_wide_lt_img;
			#else
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_169;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt = h_g_menu_img_wide_169_hlt;
			#endif
            break;

        default:
			#if 1//Cedric
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_nav_banner_new_aspect_wide_lt_img;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt= h_g_nav_banner_new_aspect_wide_lt_img;
			#else
            t_g_scr_mode_button_view[ui1_idx].h_img = h_g_menu_img_wide_169;
            t_g_scr_mode_button_view[ui1_idx].h_img_hlt= h_g_menu_img_wide_169_hlt;
			#endif
            break;
    }
    return MENUR_OK;
}

static VOID scr_mode_show_focus(SCC_VID_SCREEN_MODE_T* pe_screen_mode,
                        UINT8   ui1_repaint)
{
    INT32 i4_ret;
    UINT8 ui1_idx;
    UINT8 ui1_num;
    SCR_MODE_VIEW_T*            pt_view = &t_g_scr_mode_view;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;

    i4_ret = scr_mode_get_aspect_ratio(&e_src_asp_ratio);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_sml_get_num_rec(e_src_asp_ratio,&ui1_num);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_sml_iterate_rec(e_src_asp_ratio,
                            SML_ITERATE_DIR_FIRST,
                            pe_screen_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui1_idx = 0; ui1_idx < ui1_num && ui1_idx < SCR_MODE_BUTTON_LAST; ui1_idx ++)
    {
        if (*pe_screen_mode == e_g_crnt_screen_mode)
        {
            c_wgl_set_focus(pt_view->h_button[ui1_idx], ui1_repaint);
            return;
        }

        a_sml_iterate_rec(e_src_asp_ratio,
                            SML_ITERATE_DIR_NEXT,
                            pe_screen_mode);
    }

    c_wgl_set_focus(pt_view->h_button[0], ui1_repaint);
}
static INT32 scr_mode_set_current_focus_idx(SCC_VID_SCREEN_MODE_T e_crnt_screen_mode)
{
    INT32       i4_ret;
    INT16       i2_val;

    i2_val = (INT16)e_crnt_screen_mode;

    i4_ret = a_cfg_av_set(CFG_ID_SCREEN_MODE,i2_val);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_av_update (CFG_ID_SCREEN_MODE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: scr_mode_widgets_proc_fct
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
static INT32 scr_mode_widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32 i4_ret;
    SCC_VID_SCREEN_MODE_T       e_screen_mode;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;

    /* Get ratio */
    i4_ret = scr_mode_get_aspect_ratio(&e_src_asp_ratio);
    MENU_CHK_FAIL(i4_ret);

    e_screen_mode = e_g_crnt_screen_mode;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
			case BTN_CURSOR_UP:
            {
                a_sml_iterate_rec(e_src_asp_ratio,
                                            SML_ITERATE_DIR_PREV,
                                            &e_screen_mode);
                e_g_crnt_screen_mode = e_screen_mode;
                scr_mode_set_current_focus_idx(e_g_crnt_screen_mode);
                scr_mode_show_focus(&e_screen_mode, WGL_SYNC_AUTO_REPAINT);
            }
                break;

			case BTN_CURSOR_DOWN:
            case BTN_ASPECT:
                {
                    a_sml_iterate_rec(e_src_asp_ratio,
                                        SML_ITERATE_DIR_NEXT,
                                        &e_screen_mode);
                    e_g_crnt_screen_mode = e_screen_mode;
                    scr_mode_set_current_focus_idx(e_g_crnt_screen_mode);
                    scr_mode_show_focus(&e_screen_mode, WGL_SYNC_AUTO_REPAINT);
                }
                break;
                case BTN_SELECT:
                case BTN_RETURN:
                {
                    menu_nav_back();

                    if (!t_g_menu_common.b_is_hot_key_enter)
                	{
                    	/* temp show banner aspect  */
                        menu_main_set_visibility(TRUE);
                    	nav_banner_scr_mode_show_itm();
                        menu_pm_repaint();

                    }

                    return MENUR_OK;
                }
                break;

                default:
                break;
            }

			nav_bnr_timer_reload(NULL_HANDLE,0,(NAV_BNR_STATE_TIMER_OPER_TYPE_T)0);

            break;
        }
        default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 scr_mode_config_button(HANDLE_T        h_btn,
                            WGL_HIMG_TPL_T  h_img,
                            WGL_HIMG_TPL_T  h_img_hlt)
{
    INT32  i4_ret;
    WGL_IMG_INFO_T   t_img_info;

    /* set the backgroung of buttom_ok*/
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_img;
    t_img_info.u_img_data.t_extend.t_disable            = h_img;
    t_img_info.u_img_data.t_extend.t_highlight          = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_push               = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_img;

    i4_ret = c_wgl_do_cmd(h_btn,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_FG),
                 WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

#if 1//Cedric test
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_nav_button_default_img;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_nav_button_default_img;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_nav_button_hover_img;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_nav_button_hover_img;
    t_img_info.u_img_data.t_extend.t_push               = h_g_nav_button_default_img;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_nav_button_default_img;

    i4_ret = c_wgl_do_cmd(h_btn,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_BK),
                 WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    GL_RECT_T           t_inset;
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = SCR_MODE_BTN_H/2;

    i4_ret = c_wgl_do_cmd(h_btn,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
     MENU_CHK_FAIL(i4_ret);
#endif

    /* set the alignment */
    i4_ret = c_wgl_do_cmd(h_btn,
                 WGL_CMD_BTN_SET_ALIGN,
				#if 0//Cedric
                WGL_PACK(WGL_AS_CENTER_TOP),
				#else
                 WGL_PACK(WGL_AS_CENTER_CENTER),
              	#endif
                 NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 scr_mode_create_button(HANDLE_T    h_parent,
                            HANDLE_T*   h_handle,
                            GL_RECT_T*  t_rect,
                            HANDLE_T    h_img,
                            HANDLE_T    h_img_hlt)
{
    INT32   i4_ret;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 t_rect,
                                 scr_mode_widgets_proc_fct,
                                 255,
                                 (VOID*)0,
                                 0,
                                 h_handle);
    MENU_CHK_FAIL(i4_ret);

    return scr_mode_config_button(*h_handle, h_img, h_img_hlt);
}

static INT32 scr_mode_config_text(HANDLE_T      h_txt,
                          FE_FNT_SIZE   e_font_size,
                          UINT16        ui2_mlm_id)
{
    INT32  i4_ret;
    WGL_COLOR_INFO_T t_clr_info;
    WGL_INSET_T      t_inset;
    WGL_FONT_INFO_T     t_fnt_info;

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = e_font_size;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd ( h_txt,
                            WGL_CMD_GL_SET_FONT,
                            WGL_PACK(&t_fnt_info),
                            NULL);
    MENU_CHK_FAIL(i4_ret);
    /* Set Text Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /*set text*/
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_mlm_id)),
                          (VOID *)512);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
#if 1//Cedric
    t_inset.i4_top      = SCR_MODE_BTN_H/2;
#else
    t_inset.i4_top      = 0;
#endif
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_txt,
                            WGL_CMD_TEXT_SET_CNT_INSET,
                            &t_inset,
                            NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_insert(h_txt,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 scr_mode_create_text(HANDLE_T      h_parent,
                          HANDLE_T*     ph_handle,
                          GL_RECT_T*    t_rect,
                          FE_FNT_SIZE   e_font_size,
                          UINT16        ui2_mlm_id)
{
    INT32   i4_ret;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32
                                         | WGL_STL_TEXT_SMART_CUT
                                         | WGL_STL_GL_NO_IMG_UI
                                         | WGL_STL_GL_NO_BK),
                                 0,
                                 ph_handle);
    MENU_CHK_FAIL(i4_ret);

    return scr_mode_config_text(*ph_handle, e_font_size, ui2_mlm_id);


}

static INT32 scr_mode_config_frame(HANDLE_T h_frame)
{
    INT32           i4_ret;
    WGL_IMG_INFO_T  t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
#if 1//Cedric
    t_img_info.u_img_data.t_extend.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_disable   = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight = NULL_HANDLE;
#else
    t_img_info.u_img_data.t_extend.t_enable    = h_g_menu_img_bk0_ex;
    t_img_info.u_img_data.t_extend.t_disable   = h_g_menu_img_bk0_ex;
    t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_img_bk0_ex;
#endif

    i4_ret = c_wgl_do_cmd(h_frame,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_BK),
                 WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 scr_mode_create_widget(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_canvas;
    GL_RECT_T   t_rect;

    i4_ret = menu_pm_get_canvas(&h_canvas);
    MENU_CHK_FAIL(i4_ret);

    SCR_MODE_VIEW_T *pt_view = &t_g_scr_mode_view;
    c_memset (pt_view, 0, sizeof (SCR_MODE_VIEW_T));

    /*Create frame*/
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_FRAME_X,
                      SCR_MODE_FRAME_Y,
                      SCR_MODE_FRAME_W,
                      SCR_MODE_FRAME_H);

    i4_ret = c_wgl_create_widget(h_canvas,
                        HT_WGL_WIDGET_FRAME,
                        WGL_CONTENT_FRAME_DEF,
                        WGL_BORDER_NULL,
                        &t_rect,
                        scr_mode_widgets_proc_fct,
                        255,
                        (VOID*)0,
                        NULL,
                        &pt_view->h_frame);
    MENU_CHK_FAIL(i4_ret);

#if 1//Cedric
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_button_default_img,
            &h_g_nav_button_default_img);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
            &t_g_nav_banner_new_input_button_hover_img,
            &h_g_nav_button_hover_img);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = scr_mode_config_frame(pt_view->h_frame);
    MENU_CHK_FAIL(i4_ret);

    /*Select icon*/
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_SHADOW_ICON_X,
                      SCR_SHADOW_ICON_Y,
                      SCR_SHADOW_ICON_W,
                      SCR_SHADOW_ICON_H);
    i4_ret = scr_mode_create_icon(pt_view->h_frame,
                            &h_shadow_icon,
                            &t_rect,
                            h_g_nav_banner_new_lastshadow_img,
                            h_g_nav_banner_new_lastshadow_img);
    MENU_CHK_FAIL(i4_ret);
#endif


#if 0//Cedric
    /*Title*/
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TITLE_X,
                      SCR_MODE_TITLE_Y,
                      SCR_MODE_TITLE_W,
                      SCR_MODE_TITLE_H);

    i4_ret = scr_mode_create_text(pt_view->h_frame,
                          &pt_view->h_title,
                          &t_rect,
                          FE_FNT_SIZE_MEDIUM,
                          MLM_MENU_KEY_MENU_SCREEN_MODE);

    MENU_CHK_FAIL(i4_ret);
#endif
    /*Indicator text for Button 1*/
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TXT_X,
                      SCR_MODE_TXT_Y,
                      SCR_MODE_TXT_W,
                      SCR_MODE_TXT_H);

    i4_ret = scr_mode_create_text(pt_view->h_frame,
                          &pt_view->h_txt[0],
                          &t_rect,
                          FE_FNT_SIZE_SMALL,
                          MLM_MENU_KEY_SCREEN_MODE_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    /*Indicator text for Button 2*/
#if 1//Cedric
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TXT_X,
                      SCR_MODE_TXT_Y + SCR_MODE_TXT_H,
                      SCR_MODE_TXT_W,
                      SCR_MODE_TXT_H);
#else
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TXT_X + SCR_MODE_GAP,
                      SCR_MODE_TXT_Y,
                      SCR_MODE_TXT_W,
                      SCR_MODE_TXT_H);
#endif
    i4_ret = scr_mode_create_text(pt_view->h_frame,
                          &pt_view->h_txt[1],
                          &t_rect,
                          FE_FNT_SIZE_SMALL,
                          MLM_MENU_KEY_SCREEN_MODE_STRETCH);
    MENU_CHK_FAIL(i4_ret);

    /*Indicator text for Button 3*/
#if 1//Cedric
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TXT_X,
                      SCR_MODE_TXT_Y + (SCR_MODE_TXT_H * 2),
                      SCR_MODE_TXT_W,
                      SCR_MODE_TXT_H);
#else
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TXT_X + SCR_MODE_GAP * 2,
                      SCR_MODE_TXT_Y,
                      SCR_MODE_TXT_W,
                      SCR_MODE_TXT_H);
#endif
    i4_ret = scr_mode_create_text(pt_view->h_frame,
                          &pt_view->h_txt[2],
                          &t_rect,
                          FE_FNT_SIZE_SMALL,
                          MLM_MENU_KEY_SCREEN_MODE_STRETCH);
    MENU_CHK_FAIL(i4_ret);

    /*Indicator text for Button 4*/
#if 1//Cedric
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TXT_X,
                      SCR_MODE_TXT_Y + (SCR_MODE_TXT_H * 3),
                      SCR_MODE_TXT_W,
                      SCR_MODE_TXT_H);
#else
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TXT_X + SCR_MODE_GAP * 3,
                      SCR_MODE_TXT_Y,
                      SCR_MODE_TXT_W,
                      SCR_MODE_TXT_H);
#endif
    i4_ret = scr_mode_create_text(pt_view->h_frame,
                          &pt_view->h_txt[3],
                          &t_rect,
                          FE_FNT_SIZE_SMALL,
                          MLM_MENU_KEY_SCREEN_MODE_STRETCH);
    MENU_CHK_FAIL(i4_ret);

    /*Button 1*/
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X,
                      SCR_MODE_BTN_Y,
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);
#if 1//Cedric
    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[0],
                            &t_rect,
                            h_g_nav_banner_new_aspect_wide_lt_img,
                            h_g_nav_banner_new_aspect_wide_lt_img);
#else
    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[0],
                            &t_rect,
                            h_g_menu_img_wide_169,
                            h_g_menu_img_wide_169_hlt);
#endif
    MENU_CHK_FAIL(i4_ret);

    /*Button 2*/
#if 1//Cedric
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X,
                      SCR_MODE_BTN_Y + (SCR_MODE_BTN_H * 1),
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);

    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[1],
                            &t_rect,
                            h_g_nav_banner_new_aspect_zoom_lt_img,
                            h_g_nav_banner_new_aspect_zoom_lt_img);
#else
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X + SCR_MODE_GAP,
                      SCR_MODE_BTN_Y,
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);

    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[1],
                            &t_rect,
                            h_g_menu_img_wide_zoom1,
                            h_g_menu_img_wide_zoom1_hlt);
#endif
    MENU_CHK_FAIL(i4_ret);

    /*Button 3*/
#if 1//Cedric
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X,
                      SCR_MODE_BTN_Y + (SCR_MODE_BTN_H * 2),
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);

    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[2],
                            &t_rect,
                            h_g_nav_banner_new_aspect_normal_lt_img,
                            h_g_nav_banner_new_aspect_normal_lt_img);
#else
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X + SCR_MODE_GAP * 2,
                      SCR_MODE_BTN_Y,
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);

    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[2],
                            &t_rect,
                            h_g_menu_img_wide_43,
                            h_g_menu_img_wide_43_hlt);
#endif
    MENU_CHK_FAIL(i4_ret);

    /*Button 4*/
#if 1//Cedric
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X,
                      SCR_MODE_BTN_Y + (SCR_MODE_BTN_H * 3),
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);

    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[3],
                            &t_rect,
                            h_g_nav_banner_new_aspect_panoramic_lt_img,
                            h_g_nav_banner_new_aspect_panoramic_lt_img);
#else
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_BTN_X + SCR_MODE_GAP * 3,
                      SCR_MODE_BTN_Y,
                      SCR_MODE_BTN_W,
                      SCR_MODE_BTN_H);

    i4_ret = scr_mode_create_button(pt_view->h_frame,
                            &pt_view->h_button[3],
                            &t_rect,
                            h_g_menu_img_wide_pan_scan,
                            h_g_menu_img_wide_pan_scan_hlt);
#endif
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_float(pt_view->h_frame,
                         TRUE,
                         FALSE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: scr_mode_resize
 *
 * Description:
 *      Resize frame and other widgets if neccessary.
 *
 * Inputs: ui1_num : numbers of screen mode waiting to show
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 scr_mode_resize(UINT8 ui1_num)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    UINT32          ui4_width;
    SCR_MODE_VIEW_T*        pt_view = &t_g_scr_mode_view;

#if 1//Cedric
    UINT32          ui4_height;

    ui4_width = SCR_MODE_BTN_W;
    ui4_height = (SCR_MODE_BTN_H * ui1_num) + SCR_SHADOW_ICON_H;

    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_FRAME_X,
                      SCR_MODE_FRAME_Y,
                      ui4_width,
                      ui4_height);
#else
    ui4_width = SCR_MODE_FRAME_W - SCR_MODE_GAP * (LARGEST_SCR_MODE_NUMBER - ui1_num);

    SET_RECT_BY_SIZE (&t_rect,
                      (SCREEN_W - ui4_width)/2,
                      SCR_MODE_FRAME_Y,
                      ui4_width,
                      SCR_MODE_FRAME_H);
#endif

    i4_ret = c_wgl_move(pt_view->h_frame,
                        &t_rect,
                        WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);
#if 1//Cedric
    ui4_width = SCR_SHADOW_ICON_W;
    ui4_height = SCR_SHADOW_ICON_H;

    SET_RECT_BY_SIZE (&t_rect,
                      SCR_SHADOW_ICON_X,
                      SCR_SHADOW_ICON_Y + (SCR_MODE_BTN_H * ui1_num),
                      ui4_width,
                      ui4_height);

    i4_ret = c_wgl_move(h_shadow_icon,
                        &t_rect,
                        WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);
#endif

#if 0//Cedric
    SET_RECT_BY_SIZE (&t_rect,
                      SCR_MODE_TITLE_X,
                      SCR_MODE_TITLE_Y,
                      ui4_width,
                      SCR_MODE_TITLE_H);

    i4_ret = c_wgl_move(pt_view->h_title,
                        &t_rect,
                        WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);
#endif
    return MENUR_OK;
}

static INT32 scr_mode_show_widget(UINT8 ui1_num)
{
    INT32                   i4_ret;
    UINT8                   ui1_idx;
    SCR_MODE_VIEW_T*        pt_view = &t_g_scr_mode_view;

    i4_ret = c_wgl_set_visibility(pt_view->h_frame,WGL_SW_HIDE_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
#if 0//Cedric
    i4_ret = c_wgl_set_visibility(pt_view->h_title,WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);
#endif
    for (ui1_idx = 0; ui1_idx < ui1_num && ui1_idx < SCR_MODE_BUTTON_LAST; ui1_idx ++)
    {
        i4_ret = c_wgl_set_visibility(pt_view->h_txt[ui1_idx],WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_view->h_button[ui1_idx],WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);
    }
#if 1//Cedric
    i4_ret = c_wgl_set_visibility(h_shadow_icon,WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);
#endif
    i4_ret = c_wgl_set_visibility(pt_view->h_frame,WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: scr_mode_update_widget_data
 *
 * Description:
 *      update mlm and img data for buttons.
 *
 * Inputs: ui1_num : numbers of screen mode waiting to show
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 scr_mode_update_widget_data(UINT8 ui1_num)
{
    INT32 i4_ret = 0;
    UINT8 ui1_idx;
    WGL_IMG_INFO_T   t_img_info;
    SCR_MODE_VIEW_T*        pt_view = &t_g_scr_mode_view;
#if 0//Cedric
    i4_ret = c_wgl_do_cmd(pt_view->h_title,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(MENU_TEXT(MLM_MENU_KEY_MENU_SCREEN_MODE)),
                            (VOID *)0xFFFF);
    MENU_CHK_FAIL(i4_ret);
#endif
    for (ui1_idx = 0; ui1_idx < ui1_num && ui1_idx < SCR_MODE_BUTTON_LAST; ui1_idx ++)
    {
        i4_ret = c_wgl_do_cmd(pt_view->h_txt[ui1_idx],
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(t_g_scr_mode_button_view[ui1_idx].w2s_str),
                            (VOID *)0xFFFF);
        MENU_CHK_FAIL(i4_ret);

        /* set the backgroung of buttom_ok*/
        t_img_info.e_type = WGL_IMG_SET_EXTEND;
        t_img_info.u_img_data.t_extend.t_enable             = t_g_scr_mode_button_view[ui1_idx].h_img;
        t_img_info.u_img_data.t_extend.t_disable            = t_g_scr_mode_button_view[ui1_idx].h_img;
        t_img_info.u_img_data.t_extend.t_highlight          = t_g_scr_mode_button_view[ui1_idx].h_img_hlt;
        t_img_info.u_img_data.t_extend.t_highlight_inactive = t_g_scr_mode_button_view[ui1_idx].h_img_hlt;
        t_img_info.u_img_data.t_extend.t_push               = t_g_scr_mode_button_view[ui1_idx].h_img_hlt;
        t_img_info.u_img_data.t_extend.t_push_unhighlight   = t_g_scr_mode_button_view[ui1_idx].h_img;

        i4_ret = c_wgl_do_cmd(pt_view->h_button[ui1_idx],
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_FG),
                 WGL_PACK(&t_img_info));
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static UTF16_T * _scr_mode_get_name(SCC_VID_SCREEN_MODE_T e_screen_mode)
{
    UINT16   ui2_idx = (UINT16)-1;

    switch (e_screen_mode)
    {
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:    /* Zoom */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_ZOOM;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:    /* Wide */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_WIDE;
            break;

        case SCC_VID_SCREEN_MODE_NORMAL:          /* Normal */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_NORMAL;
            break;

        case SCC_VID_SCREEN_MODE_LETTERBOX:       /* Stretch */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_STRETCH;
            break;

        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM: /* Panoramic */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_PANORAMIC;
            break;

        default:                                  /* unknown screen mode? */
            ui2_idx = (UINT16)-1;
            break;
    }

    return (ui2_idx == (UINT16)-1) ? NULL : MENU_TEXT(ui2_idx);
}

static INT32 _menu_scrn_mode_float(BOOL b_float, BOOL b_repaint)
{
    INT32 i4_ret = MENUR_OK;
    UINT8 ui1_cnt_loop = 0;
    UINT8 ui1_num = 0;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;

    /* Get ratio */
    i4_ret = scr_mode_get_aspect_ratio(&e_src_asp_ratio);
    MENU_CHK_FAIL(i4_ret);

    /* Get number of current screen mode */
    i4_ret = a_sml_get_num_rec(e_src_asp_ratio,&ui1_num);
    MENU_CHK_FAIL(i4_ret);
#if 1
    for (ui1_cnt_loop = 0; ui1_cnt_loop < ui1_num && ui1_cnt_loop < SCR_MODE_BUTTON_LAST; ui1_cnt_loop ++)
    {
        c_wgl_float(t_g_scr_mode_view.h_txt[ui1_cnt_loop], b_float, WGL_NO_AUTO_REPAINT);
        c_wgl_float(t_g_scr_mode_view.h_button[ui1_cnt_loop], b_float, WGL_NO_AUTO_REPAINT);
    }

    c_wgl_float(t_g_scr_mode_view.h_frame, b_float, WGL_ASYNC_AUTO_REPAINT);
#else
    c_wgl_float(t_g_scr_mode_view.h_frame, b_float, b_repaint);
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret;

    i4_ret = scr_mode_create_widget();

    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    SCR_MODE_VIEW_T*     pt_view = &t_g_scr_mode_view;

    if(pt_view->h_frame != NULL_HANDLE) {
        c_wgl_destroy_widget(pt_view->h_frame);
    }

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32                       i4_ret;

    UINT8                       ui1_num;
    UINT8                       ui1_idx;
    INT16                       i2_scr_mode;
    SCC_VID_SCREEN_MODE_T       e_screen_mode;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;

	UINT8	ui1_itm_offset,ui1_curt_status;
    BOOL    b_enable = TRUE;
    BOOL    b_mmp_full_screen = FALSE;
    MMP_BE_BROWSER_STATUS_T  e_mmp_browser_status = a_mmp_be_get_browser_status();

    b_mmp_full_screen = a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP)
                        && ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == e_mmp_browser_status)
                      	||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == e_mmp_browser_status)
                        ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == e_mmp_browser_status)
                        ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == e_mmp_browser_status));

    if (!b_mmp_full_screen
        && MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        a_vol_ctrl_set_visibility(FALSE);
    }
    i4_ret = a_cfg_custom_get_wide_mode_enable_change(&b_enable);

    if (APP_CFGR_OK == i4_ret && FALSE == b_enable)
    {
        menu_custom_dialog_show(MENU_CUSTOM_DIALOG_ID_SCREEN_MODE_WARN);
        t_g_scr_mode_view.b_show_warn_msg = TRUE;
    }

    a_vol_ctrl_set_visibility(FALSE);

    /* Hide the main menu */
    menu_main_set_visibility(FALSE);
    menu_hide_help_tip();

    /* Get current screen mode */
    i4_ret = a_cfg_av_get (CFG_ID_SCREEN_MODE, & i2_scr_mode);
    MENU_CHK_FAIL(i4_ret);

    e_screen_mode = (SCC_VID_SCREEN_MODE_T) i2_scr_mode;

    /* Get ratio */
    i4_ret = scr_mode_get_aspect_ratio(&e_src_asp_ratio);
    MENU_CHK_FAIL(i4_ret);

    /* Get number of current screen mode */
    i4_ret = a_sml_get_num_rec(e_src_asp_ratio,&ui1_num);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_sml_iterate_rec(e_src_asp_ratio,
                                SML_ITERATE_DIR_THIS,
                                &e_screen_mode);
    if (i4_ret != MENUR_OK)
    {
        i4_ret = a_sml_iterate_rec(e_src_asp_ratio,
                                SML_ITERATE_DIR_FIRST,
                                &e_screen_mode);
        MENU_CHK_FAIL(i4_ret);

        /* Set the first screen mode to config. */
        i2_scr_mode = (INT16)e_screen_mode;

        i4_ret = a_cfg_av_set(CFG_ID_SCREEN_MODE,i2_scr_mode);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = a_cfg_av_update(CFG_ID_SCREEN_MODE);
        MENU_CHK_FAIL(i4_ret);
    }

    e_g_crnt_screen_mode = e_screen_mode;

    /*Jump to first screen mode to begin traversal all the screen modes*/
    i4_ret = a_sml_iterate_rec(e_src_asp_ratio,
                            SML_ITERATE_DIR_FIRST,
                            &e_screen_mode);
    MENU_CHK_FAIL(i4_ret);

    for (ui1_idx = 0;ui1_idx < ui1_num && ui1_idx < SCR_MODE_BUTTON_LAST; ui1_idx++)
    {
        /*mlm update*/
        t_g_scr_mode_button_view[ui1_idx].w2s_str = _scr_mode_get_name(e_screen_mode);/*a_sml_get_disp_name(e_src_asp_ratio,
                                                                            e_screen_mode);*/
        /*img update*/
        i4_ret = scr_mode_update_disp_icon(ui1_idx,e_src_asp_ratio,e_screen_mode);
        MENU_CHK_FAIL(i4_ret);

        /* Focus on the button which indicates current screen mode */
        if (e_g_crnt_screen_mode == e_screen_mode)
        {
            c_wgl_set_focus(t_g_scr_mode_view.h_button[ui1_idx], WGL_NO_AUTO_REPAINT);
			#if 1//Cedric
			ui1_CurrentScrMode = ui1_idx;
			#endif
        }

        i4_ret = a_sml_iterate_rec(e_src_asp_ratio,
                                SML_ITERATE_DIR_NEXT,
                                &e_screen_mode);
        MENU_CHK_FAIL(i4_ret);
    }
#if 1//Cedric
    for (ui1_idx = 0;ui1_idx < ui1_num && ui1_idx < SCR_MODE_BUTTON_LAST; ui1_idx++)
    {
    		ui1_itm_offset = scr_mode_item_resort(ui1_idx,ui1_CurrentScrMode,(((ui1_num) < (SCR_MODE_BUTTON_LAST)) ? (ui1_num) : (SCR_MODE_BUTTON_LAST)));
		scr_mode_move_wgl(t_g_scr_mode_view.h_button[ui1_idx],ui1_itm_offset);
		scr_mode_move_wgl(t_g_scr_mode_view.h_txt[ui1_idx],ui1_itm_offset);
		#if 0
		if(ui1_idx >= ui1_CurrentScrMode)
		{
			scr_mode_move_wgl(t_g_scr_mode_view.h_button[ui1_idx],ui1_idx - ui1_CurrentScrMode);
			scr_mode_move_wgl(t_g_scr_mode_view.h_txt[ui1_idx],ui1_idx - ui1_CurrentScrMode);
		}else
		{
			scr_mode_move_wgl(t_g_scr_mode_view.h_button[ui1_idx],
								(((ui1_num) < (SCR_MODE_BUTTON_LAST)) ? (ui1_num) : (SCR_MODE_BUTTON_LAST))
								 - ui1_CurrentScrMode + ui1_idx);
			scr_mode_move_wgl(t_g_scr_mode_view.h_txt[ui1_idx],
								(((ui1_num) < (SCR_MODE_BUTTON_LAST)) ? (ui1_num) : (SCR_MODE_BUTTON_LAST))
								 - ui1_CurrentScrMode + ui1_idx);
		}
		#endif
    }
#endif

    i4_ret = scr_mode_update_widget_data(ui1_num);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = scr_mode_resize(ui1_num);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = scr_mode_show_widget(ui1_num);
    MENU_CHK_FAIL(i4_ret);

    b_wide_page_show = TRUE;

    a_tv_net_OSD_appear();

	#if 1//Cedric
	banner_get_crnt_state (&ui1_curt_status);
	if(_crnt_source_is_tv() && _crnt_svl_is_empty())
	{
		#if 0//Cedric 0402
		if(ui1_curt_status != BANNER_STATE_CH)//Special case
			a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)BTN_PRG_INFO, NULL);
		#endif
	}else
	{
		nav_bnr_timer_reload(NULL_HANDLE,0,(NAV_BNR_STATE_TIMER_OPER_TYPE_T)0);
	}
	#endif

#ifdef VIEWPORT_SUPPORT
    UINT8 ui1_val = 0;

    a_icl_custom_get_enter_wide_selection_by_key (&ui1_val);
    if (ui1_val == ICL_NAV_ENTER_WIDE_SELECTION_BY_KEY
        || ui1_val == ICL_NAV_ENTER_WIDE_SELECTION_NOT_BY_KEY)
    {
        a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_WIDE_MODE);
        a_cfg_update_viewport ();
    }

#endif


    return MENUR_OK;
}
static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    SCR_MODE_VIEW_T*            pt_view = &t_g_scr_mode_view;
    INT32 i4_ret = 0;
    UINT8 ui1_val = 0;
    UINT8 ui1_status = 0;

    if (pt_view->b_show_warn_msg)
    {
        menu_custom_dialog_hide(MENU_CUSTOM_DIALOG_ID_SCREEN_MODE_WARN);
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_frame,WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    a_icl_custom_get_enter_wide_selection_by_key (&ui1_val);

    if (ui1_val == ICL_NAV_ENTER_WIDE_SELECTION_BY_KEY)
    {
        /*
         *  This means that user uses WIDE key to enter wide mode OSD and then
         *  press MENU to display main menu. Force to update the APP status.
         */
        DBG_INFO(("\n===_on_page_hide app status %d===\n",a_cfg_get_app_status()));
        if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_LAST_ENTRY)
        {
        #ifdef APP_MENU_MMP_COEXIST
            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                MMP_BE_BROWSER_STATUS_T  e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;
                e_mmp_browser_status = a_mmp_be_get_browser_status();
                if ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == e_mmp_browser_status)
                	||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == e_mmp_browser_status)
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == e_mmp_browser_status)
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == e_mmp_browser_status))
                {
                    a_cfg_set_app_status (APP_CFG_APP_STATUS_MMP_VIDEO_FULL_PLAY);
                }
                else
                {
                    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
                }
            }
            else
        #endif
            {
                a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
            }
        }
    }
    else
    {
        /* Only update AP status when Menu is not exited. */
        if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
        {
        #ifdef APP_MENU_MMP_COEXIST
            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                MMP_BE_BROWSER_STATUS_T  e_mmp_browser_status = MMP_BE_BROWSER_STATUS_NONE;
                e_mmp_browser_status = a_mmp_be_get_browser_status();
                if ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == e_mmp_browser_status)
                	||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == e_mmp_browser_status)
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == e_mmp_browser_status)
                    ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == e_mmp_browser_status))
                {
                    a_cfg_set_app_status (APP_CFG_APP_STATUS_MMP_VIDEO_FULL_PLAY);
                }
                else
                {
                    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
                }
            }
            else
        #endif
            {
                a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
            }
        }
    }

    if (a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_status) == ICLR_OK)
    {
        if ((YAHOO_STATUS_DOCK_UP & ui1_status) != 0)
        {
            a_cfg_set_app_status (APP_CFG_APP_STATUS_YH_DOCK);
        }
        if ((YAHOO_STATUS_SIDEBAR & ui1_status) != 0)
        {
            a_cfg_set_app_status (APP_CFG_APP_STATUS_YH_SIDEBAR);
        }
    }

    a_cfg_update_viewport ();

    _menu_scrn_mode_float(FALSE, FALSE);

    if (ui1_val == ICL_NAV_ENTER_WIDE_SELECTION_BY_KEY)
	{
    	/* temp show banner aspect  */
    	nav_banner_scr_mode_show_itm();
    }

    b_wide_page_show = FALSE;
    a_tv_net_OSD_disapper();

    a_vol_ctrl_set_visibility(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    _menu_scrn_mode_float(TRUE, TRUE);
    a_vol_ctrl_set_visibility(TRUE);
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    if(ui4_update_mask == MENU_PAGE_UMASK_REFRESH)
    {
        /*_on_page_hide(ui4_page_id);*/
        c_wgl_set_visibility(t_g_scr_mode_view.h_frame,WGL_SW_HIDE);
        b_wide_page_show = FALSE;
        a_tv_net_OSD_disapper();

        _on_page_show(ui4_page_id);
        _on_page_get_focus(ui4_page_id, NULL);
    }
    return MENUR_OK;
}

extern INT32 menu_page_screen_mode_init(VOID)
{
    t_g_menu_page_screen_mode.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_screen_mode.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_screen_mode.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_screen_mode.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_screen_mode.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_screen_mode.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_screen_mode.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

BOOL menu_scr_mode_show(VOID)
{
    return b_wide_page_show;
}

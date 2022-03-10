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
 * $RCSfile: nav_flicker.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#if 1//def FXCAPP_NAV_FLICKER_SUPPORT
#include "u_common.h"
#include "u_svctx.h"
#include "c_dbg.h"
#include "c_tsl.h"
#include "c_svl.h"
#include "c_svctx.h"
#include "u_cecm.h"
#include "c_cecm.h"
#include "c_iom.h"
#include "c_pcl.h"
#include "c_gl.h"
#include "c_handle.h"
#include "c_scc.h"

#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "res/nav/nav_variant.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav_flicker.h"
#include "a_nav_flicker.h"
#include "res/nav/flicker_pattern/nav_flicker_custom.h"
#include "mtosd.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define NAV_FLICKER_Z_ORDER     (2)
#define NAV_FLICKER_CLR_MODE    GL_COLORMODE_ARGB_D8888
#ifndef BTN_INVOKE_FLICKER
// #define BTN_FF
#define BTN_INVOKE_FLICKER 0x92
#endif

#ifndef COMP_EXEC_SET_FLICKER
#define COMP_EXEC_SET_FLICKER       (~(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_FLICKER)))
#endif

#if 1//Cedric flicker
#define TOTAL_FLICKER_PATTERN   (8)///nick 20120820
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FLICKER_T t_flicker;

#if 1//Cedric flicker
NAV_FLICKER_VALUE_T		t_flicker_value;
#endif

 void set_flicker_value(UINT8 R, UINT8 G, UINT8 B)
{
      t_flicker_value.ui1_r_gain = R;
	t_flicker_value.ui1_g_gain = G;
	t_flicker_value.ui1_b_gain = B;
}



/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static INT32 _flicker_enable_video (NAV_FLICKER_T* pt_this)
{
    ISL_REC_T t_isl;
    
    /*reset blue mute*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE));

    /*reset NR and 3D_NR*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));
    /* Select select service. */
    nav_get_isl_rec (TV_WIN_ID_MAIN, &t_isl);
    nav_change_av_inp_by_id (TV_WIN_ID_MAIN, t_isl.ui1_id, NULL);
    
    return NAVR_OK;
}
static INT32 _flicker_disable_video (NAV_FLICKER_T* pt_this)
{
    UINT8 ui1_i;
    INT32 i4_ret;
    SM_COMMAND_T at_sm_cmds[4];
    SM_CMD_CODE_T ae_cmd_code[2] = {SCC_CMD_CODE_VIDEO_NR, SCC_CMD_CODE_VIDEO_3D_NR};
    HANDLE_T h_main_svctx = NULL, h_sub_svctx = NULL;
    SVCTX_VIDEO_MUTE_INFO_T     t_video_mute_info;

    i4_ret = nav_get_svctx_handle (TV_WIN_ID_MAIN, &h_main_svctx);
    if(TVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    i4_ret = nav_get_svctx_handle (TV_WIN_ID_SUB, &h_sub_svctx);
    if(TVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    /* Leave PIP/POP mode. */
    i4_ret = a_tv_set_mode(TV_MODE_TYPE_NORMAL);
    if(TVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    /* Disable NR and 3D NR. */
    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].u.ui2_data    = 0;        /*OFF*/
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;
    for(ui1_i = 0; ui1_i < 2; ui1_i++)
    {
        at_sm_cmds[2].e_code    = ae_cmd_code[ui1_i];
        i4_ret = c_scc_comp_grp_set(at_sm_cmds);
        if(SMR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }
    }
    /* Stop video. */
    i4_ret = c_svctx_sync_stop_svc(h_main_svctx, DEFAULT_STOP_SVC_TIMEOUT);
    if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
    {
        DBG_ERROR(("c_svctx_sync_stop_svc(main) failed. i4_ret = %d.\r\n", i4_ret));
        return NAVR_FAIL;
    }

    /* Stop video. */
    if(h_sub_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(h_sub_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_ERROR(("c_svctx_sync_stop_svc(sub) failed. i4_ret = %d.\r\n", i4_ret));
            return NAVR_FAIL;
        }
    }
    /* Disable blue mute. */
    t_video_mute_info.b_enable          = TRUE;
    t_video_mute_info.t_color.ui1_red   = 0;
    t_video_mute_info.t_color.ui1_green = 0;
    t_video_mute_info.t_color.ui1_blue  = 0;

    /* Disable blue mute, main*/
    i4_ret = c_svctx_set(h_main_svctx, SVCTX_COMMON_SET_VIDEO_MUTE, &t_video_mute_info, sizeof(SVCTX_VIDEO_MUTE_INFO_T));
    if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
    {
        DBG_ERROR(("c_svctx_set(main, SVCTX_COMMON_SET_VIDEO_MUTE) failed. i4_ret = %d.\r\n", i4_ret));
        return NAVR_FAIL;
    }

    /* Disable blue mute, sub*/
    if(h_sub_svctx)
    {
        i4_ret = c_svctx_set(h_sub_svctx, SVCTX_COMMON_SET_VIDEO_MUTE, &t_video_mute_info, sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
        {
            DBG_ERROR(("c_svctx_set(sub, SVCTX_COMMON_SET_VIDEO_MUTE) failed. i4_ret = %d.\r\n", i4_ret));
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}
static INT32 _flicker_deinit_plane (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    
    i4_ret = c_gl_obj_free (pt_this->h_plane);
    if(GLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
static INT32 _flicker_init_plane (NAV_FLICKER_T* pt_this)
{
    UINT8 ui1_i;
    INT32 i4_ret;
    UINT16 ui2_plane_count;
    UINT32 ui4_gui_idx;
    GL_HSCREEN_T h_screen;
    GL_SCREEN_STATUS_T t_src_status = {0};
    GL_PLANE_CAPS_T t_plane_caps;

    /* Open screen*/
    i4_ret = c_gl_screen_open(SN_PRES_MAIN_DISPLAY, NULL, NULL, &h_screen);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_screen_open(%s) failed. i4_ret = %d.\r\n", SN_PRES_MAIN_DISPLAY, i4_ret));
        return NAVR_FAIL;
    }
    /* Get screen capability. */
#if 0 //libfactory4.so build error	
    i4_ret = c_gl_screen_get_status(h_screen, &t_src_status);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_screen_get_status() failed. i4_ret = %d.\r\n", i4_ret));
        c_gl_obj_free(h_screen);
        return NAVR_FAIL;
    }
#endif
    pt_this->ui2_screen_w = t_src_status.ui2_width;
    pt_this->ui2_screen_h = t_src_status.ui2_height;
    /* Find a suit plane for image*/
    i4_ret = c_gl_plane_num(&ui2_plane_count);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_plane_num() failed. i4_ret = %d.\r\n", i4_ret));
        c_gl_obj_free(h_screen);
        return NAVR_FAIL;
    }
    ui4_gui_idx = a_util_get_default_osd_plane_index();
    for(ui1_i = 0; ui1_i < ui2_plane_count; ui1_i++)
    {
        /* Skip OSD plane. */
        if(ui1_i == ui4_gui_idx)
        {
            continue;
        }
    
        /* Get plane capability. */
        i4_ret = c_gl_plane_enum(h_screen, ui1_i, &t_plane_caps);
        if(GLR_OK != i4_ret)
        {
            DBG_ERROR(("c_gl_plane_enum(%d) failed. i4_ret = %d.\r\n", ui1_i, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }
    
        /* Check capability. */
        if(((0x00000001 << NAV_FLICKER_CLR_MODE) & t_plane_caps.ui4_cm_caps) && 
            ((0x00000001 << NAV_FLICKER_Z_ORDER) & t_plane_caps.ui4_z_mask))
        {
            /*found*/
            i4_ret = NAVR_OK;
            break;
        }
    }
    
    if(ui1_i >= ui2_plane_count || NAVR_OK != i4_ret)   /*not found or error*/
    {
        c_gl_obj_free(h_screen);
        return NAVR_FAIL;
    }
    
    ui1_i = 3;
    i4_ret = c_gl_plane_open(h_screen, ui1_i, &pt_this->h_plane);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_plane_open(%d) failed. i4_ret = %d.\r\n", ui1_i, i4_ret));
    
        pt_this->h_plane = NULL_HANDLE;
        c_gl_obj_free(h_screen);
        return NAVR_FAIL;
    }
    
    i4_ret = c_gl_plane_link(pt_this->h_plane, h_screen, TRUE);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_plane_link() failed. i4_ret = %d.\r\n", i4_ret));
        c_gl_obj_free(h_screen);
        return NAVR_FAIL;
    }
    else
    {
        i4_ret = NAVR_OK;
    }
    if(h_screen)
    {
        i4_ret = c_gl_obj_free(h_screen);
        return i4_ret;
    }

    return i4_ret;
}
static INT32 _flicker_deinit_view (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    
    /*create view*/
    i4_ret = c_gl_obj_free (pt_this->h_view);
    if(GLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
static INT32 _flicker_init_view (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    
    /*create view*/
    i4_ret = c_gl_view_create(pt_this->ui2_screen_w, pt_this->ui2_screen_h, TRUE/*FALSE*/, &pt_this->h_view);
    if(GLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
static INT32 _flicker_init_disp_res (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    GL_SURFACE_DESC_T           t_surf_descr;
    GL_DISPLAY_OPT_T            t_dsp_opt;
    GL_POINT_T t_screen_offset = {0};

    c_memset(&t_surf_descr, 0, sizeof(GL_SURFACE_DESC_T));
    c_memset(&t_dsp_opt, 0, sizeof(GL_DISPLAY_OPT_T));
    /*set the plane order*/
    i4_ret = c_gl_plane_reorder(pt_this->h_plane, GL_REORDER_ABSOLUTE, 0);
    if(GLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /*surface setting*/
    t_surf_descr.ui4_width  = pt_this->ui2_screen_w;
    t_surf_descr.ui4_height = pt_this->ui2_screen_h;
    t_surf_descr.e_clrmode  = NAV_FLICKER_CLR_MODE;
    
    /*create surface*/
    i4_ret = c_gl_surface_create_from_fbm(&t_surf_descr, &pt_this->h_surf);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_create() failed. i4_ret = %d.\r\n", i4_ret));
    
        pt_this->h_surf = NULL_HANDLE;
        return NAVR_FAIL;
    }
    /*viewport setting*/
    t_dsp_opt.e_flag            = GL_DISP_OPT_POSITION | GL_DISP_OPT_BLEND_OPTION | GL_DISP_OPT_ALPHA;
    t_dsp_opt.e_blend_option    = GL_BLEND_OPT_PIXEL;
    t_dsp_opt.ui1_alpha         = 255;
    t_dsp_opt.t_pos             = t_screen_offset;
    
    /*create viewport*/
    i4_ret = c_gl_view_create_viewport(pt_this->h_view, pt_this->h_surf, &t_dsp_opt, &pt_this->ui4_viewport);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_view_create_viewport() failed. i4_ret = %d.\r\n", i4_ret));
    
        pt_this->ui4_viewport = 0;
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
static INT32 _flicker_deinit_disp_res (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    
    i4_ret = c_gl_view_delete_viewport(pt_this->h_view, pt_this->ui4_viewport);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_view_create_viewport() failed. i4_ret = %d.\r\n", i4_ret));
    
        pt_this->ui4_viewport = 0;
        return NAVR_FAIL;
    }
    i4_ret = c_gl_obj_free (pt_this->h_surf);
    if(GLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }    
    return NAVR_OK;
}
static INT32 _flicker_link_plane_view (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    c_gl_plane_set_alpha(pt_this->h_plane,0xFF);
    i4_ret = c_gl_plane_flip(pt_this->h_plane, pt_this->h_view, TRUE);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_plane_flip() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
static INT32 _flicker_unlink_plane_view (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    
    i4_ret = c_gl_plane_flip(pt_this->h_plane, NULL, TRUE);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_plane_flip() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    c_gl_plane_set_alpha(pt_this->h_plane,0x00);
    c_gl_plane_clear(pt_this->h_plane);
    return NAVR_OK;
}

#if 1//Cedric flicker
static VOID _flicker_set_pattern_idx (NAV_FLICKER_T* pt_this, UINT32 u4_idx)
{
    pt_this->ui4_pattern_idx = u4_idx;
}

static VOID _flicker_set_pattern_rgb (NAV_FLICKER_T* pt_this, UINT32 u4_rgb)
{
    pt_this->ui4_rgblevel = u4_rgb;
}

VOID a_nav_flicker_set_pattern_rgb (UINT32 u4_pattern_rgb)
{
    _flicker_set_pattern_rgb(&t_flicker, u4_pattern_rgb);
}

INT32 _fact_set_internal_patten(UINT32  u4_pattern_id)///nick 20120322
{
UINT32 u4_pattern_rgblevel=0;
        if(u4_pattern_id==6)///vcom internal pattern
{
		u4_pattern_rgblevel=t_flicker_value.ui1_r_gain;///R value
		u4_pattern_rgblevel=u4_pattern_rgblevel<<8;
		u4_pattern_rgblevel=u4_pattern_rgblevel+t_flicker_value.ui1_g_gain;///G value
		u4_pattern_rgblevel=u4_pattern_rgblevel<<8;
		u4_pattern_rgblevel=u4_pattern_rgblevel+t_flicker_value.ui1_b_gain;///B value
		u4_pattern_rgblevel=u4_pattern_rgblevel | 0xFF000000;
		}
    if (0 == u4_pattern_id)
	{
		if (nav_flicker_is_running())
		{
			a_nav_flicker_set_pattern(0);
			a_nav_update_pattern();
		}
	}
    else
	{
        a_nav_flicker_set_pattern(u4_pattern_id);
	 	a_nav_flicker_set_pattern_rgb(u4_pattern_rgblevel);	

		a_nav_update_pattern(); 
                        MTOSD_PLA_Enable(0,0);

                        MTOSD_PLA_Enable(1,0);
                        DBG_ERROR(("\n\n Jim  _fact_set_internal_patten  MTOSD_PLA_Disable  0  \n"));		
	}
	
	return NAVR_OK;
}

static UINT32 _flicker_get_pattern_idx (NAV_FLICKER_T* pt_this)
{
    return pt_this->ui4_pattern_idx;
}
#endif
#if 1//Cedric flicker
static INT32 _flicker_draw_data_flicker (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32 ui4_clr_bits = 0xFF008000;
    UINT32* pui4_fbm = NULL;
    BOOL b_paint_even = TRUE;
    UINT8 ui1_hori_cnt = 1;
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
    for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
    {
        pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
        if (ui4_i != 0)
        {
            if (ui1_hori_cnt == 1)
            {
                if (b_paint_even)
                {
                    b_paint_even = FALSE;
                }
                else
                {
                    b_paint_even = TRUE;
                }
                ui1_hori_cnt = 0;
            }
            else
            {
                ui1_hori_cnt++;
            }
        }
        for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
        {
            if (b_paint_even)
            {
                if ((ui4_j % 2) == 0)
                {
                    pui4_fbm[ui4_j] = ui4_clr_bits;
                }
            }
            else
            {
                if ((ui4_j % 2) == 1)
                {
                    pui4_fbm[ui4_j] = ui4_clr_bits;
                }
            }
        }
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_gradation (NAV_FLICKER_T* pt_this, INT32 u4_direction)
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32* pui4_fbm = NULL;
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

    UINT32 u4_gray=0;
    if(u4_direction == 0 || u4_direction == 1)
    {
        //left to right
        pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
        for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
        {
            pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
            
            for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
            {
                u4_gray = (ui4_j * 256)/pt_this->ui2_screen_w;
                if (u4_gray > 255)
                {
                    u4_gray = 255;
                }
                if (u4_direction == 1)
                {
                    u4_gray = 255 - u4_gray;
                }
                pui4_fbm[ui4_j] = 0xFF000000 | (u4_gray << 16) | (u4_gray << 8) | u4_gray;
            }
  //          if(ui4_i == 0)
   //         {
                //c_dbg_stmt("[] check horizontal: 0x%x, 0x%x\n", pui4_fbm[0], pui4_fbm[pt_this->ui2_screen_w-1]);
//            }
        }
    }
    else
    {
        //top to bottom
        pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
        for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
        {
            pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
            
            u4_gray = (ui4_i * 256)/pt_this->ui2_screen_h;
            if (u4_gray > 255)
            {
                u4_gray = 255;
            }
            if (u4_direction == 3)
            {
                u4_gray = 255 - u4_gray;
            }
            for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
            {
                pui4_fbm[ui4_j] = 0xFF000000 | (u4_gray << 16) | (u4_gray << 8) | u4_gray;
            }
           // if(ui4_i == 0)
           // {
           //     c_dbg_stmt("[] check vertical 0x%x, ", pui4_fbm[0]);
          //  }
          //  else if (ui4_i == pt_this->ui2_screen_h-1)
          //  {
           //     c_dbg_stmt("0x%x\n", pui4_fbm[0]);
           // }
        }
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_subpixel (NAV_FLICKER_T* pt_this,UINT8 index)///nick 20120820
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32 ui4_clr_bits = 0xFF000000;
    UINT32* pui4_fbm = NULL;
    BOOL b_paint_even = TRUE;
    UINT8 ui1_hori_cnt = 1;

    if(index == 1) {ui4_clr_bits=0xFF00FF00;}///Green
    else if(index == 2) {ui4_clr_bits=0xFF0000FF;}///Blue
    else {ui4_clr_bits=0xFFFF0000;}///Red
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
    for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
    {
        pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
        if (ui4_i != 0)
        {
            if (ui1_hori_cnt == 1)
            {
                if (b_paint_even)
                {
                    b_paint_even = FALSE;
                }
                else
                {
                    b_paint_even = TRUE;
                }
                ui1_hori_cnt = 0;
            }
            else
            {
                ui1_hori_cnt++;
            }
        }
        for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
        {
            if (b_paint_even)
            {
                if ((ui4_j % 2) == 0)
                {
                    pui4_fbm[ui4_j] = ui4_clr_bits;
                }
            }
            else
            {
                if ((ui4_j % 2) == 1)
                {
                    pui4_fbm[ui4_j] = ui4_clr_bits;
                }
            }
        }
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_stripe_line (NAV_FLICKER_T* pt_this,UINT8 index)///nick 20120820
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32 ui4_clr_bits = 0xFFFFFFFF; ///White;
    UINT32* pui4_fbm = NULL;
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
    for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
    {
        pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
	if(index==1)
		{
		if(ui4_i%2==0)
			{
        		for (ui4_j = 0;ui4_j < (pt_this->ui2_screen_w);ui4_j++)
        	  	  {
         		   pui4_fbm[ui4_j] = ui4_clr_bits;
       	         }
			}
		}
	else
		{
        	for (ui4_j = 0;ui4_j < (pt_this->ui2_screen_w);ui4_j++)
        	  {
         	  if(ui4_j%2==0)
         		{
         		pui4_fbm[ui4_j] = ui4_clr_bits;
         		}
       	   }
		}	
		
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_squarebox_1 (NAV_FLICKER_T* pt_this,UINT8 index)///nick 20120820
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_COLOR_T t_empty_clr_1 = {255, {255}, {255}, {255}};	
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32* pui4_fbm = NULL;
    UINT32 u4_screen_h=0;
    UINT32 u4_screen_w=0;	
    UINT32 ui4_clr_bits =0;

    if(index == 1)
	{
	ui4_clr_bits=0xFFFFFFFF;
       i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);	
   	}
    else
   	{
	ui4_clr_bits=0xFF000000;
	i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr_1, GL_SYNC);
   	}
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

        pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
	 u4_screen_h = pt_this->ui2_screen_h/20;
	 u4_screen_w = pt_this->ui2_screen_w/20;
        for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
        {
            pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
            if((ui4_i >=(u4_screen_h *7)) && (ui4_i <=(u4_screen_h *13)))
            		{
            		for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
            			{
            			 if((ui4_j >=(u4_screen_w *7)) && (ui4_j <=(u4_screen_w *13)))
            			 	{
                			pui4_fbm[ui4_j] = ui4_clr_bits;
            			 	}
            			}
            		}	
  /*          if(ui4_i == 0)
            {
                c_dbg_stmt("[] check horizontal: 0x%x, 0x%x\n", pui4_fbm[0], pui4_fbm[pt_this->ui2_screen_w-1]);
            } */
        }
    
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_color_pattern (NAV_FLICKER_T* pt_this,UINT8 color)///nick 20120820
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32 ui4_clr_bits =0;
    UINT32* pui4_fbm = NULL;

        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;

    if(color == 1) {ui4_clr_bits=0xFF000000;}///Black
    else if(color == 2) {ui4_clr_bits=0xFFFF0000;}///Red
    else if(color == 3) {ui4_clr_bits=0xFF00FF00;}///Green
    else if(color == 4) {ui4_clr_bits=0xFF0000FF;}///Blue
    else {ui4_clr_bits=0xFFFFFFFF;}///White	
	
    for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
    {
        pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
        for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
        {
                    	pui4_fbm[ui4_j] = ui4_clr_bits;
         }
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_vcom_internal_pattern (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32 ui4_clr_bits = pt_this->ui4_rgblevel;
    UINT32* pui4_fbm = NULL;
    BOOL b_paint_even = TRUE;
    //UINT8 ui1_hori_cnt = 0;///1; nick 20120523
    UINT8 uil_rgb=0;///nick 20120523
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
    for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
    {
        pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
		//if(ui1_hori_cnt==0)
         //   {
		//	ui1_hori_cnt=1;
 /*               if (b_paint_even)
                {
                    b_paint_even = FALSE;
                }
                else
                {
                    b_paint_even = TRUE;
                }
  */      //    }
	//	else if(ui1_hori_cnt==1)
        //    {
	//		ui1_hori_cnt=0;
       // }
		uil_rgb=0;
        for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
        {


		 	
		 	
            if (b_paint_even)
            {
                	if(uil_rgb==0)
                {
                    	pui4_fbm[ui4_j] = ui4_clr_bits & 0xFFFF00FF;//RB
                    	uil_rgb=1;
                		}
					else if(uil_rgb==1)
                {
                    	pui4_fbm[ui4_j] = ui4_clr_bits & 0xFF00FF00;//G
                    	uil_rgb=0;
                }
            }
            else
            {
                	if(uil_rgb==0)
                {
                    	pui4_fbm[ui4_j] = ui4_clr_bits & 0xFF00FF00;//G
                    	uil_rgb=1;
                		}
					else if(uil_rgb==1)
                {
                    	pui4_fbm[ui4_j] = ui4_clr_bits & 0xFFFF00FF;//RB
                    	uil_rgb=0;
                }
            }
        }
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_colorbar (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j, ui4_k;
    UINT32 ui4_clr_bits = 0xFF000000;
    UINT32* pui4_fbm = NULL;
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
    for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
    {
        pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);

	 ui4_clr_bits = 0xFFFFFFFF; ///White	
        for (ui4_j = 0;ui4_j < (pt_this->ui2_screen_w/8);ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }
	 ui4_k=ui4_j;
	 ui4_clr_bits = 0xFFFFFF00; ///Yellow	
        for (ui4_j = ui4_k;ui4_j < (ui4_k+(pt_this->ui2_screen_w/8));ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }		
	 ui4_k=ui4_j;
	 ui4_clr_bits = 0xFF00FFFF; ///Cyan	
        for (ui4_j = ui4_k;ui4_j < (ui4_k+(pt_this->ui2_screen_w/8));ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }	
	 ui4_k=ui4_j;
	 ui4_clr_bits = 0xFF00FF00; ///Green	
        for (ui4_j = ui4_k;ui4_j < (ui4_k+(pt_this->ui2_screen_w/8));ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }	
	 ui4_k=ui4_j;
	 ui4_clr_bits = 0xFFFF00FF; ///Magenta	
        for (ui4_j = ui4_k;ui4_j < (ui4_k+(pt_this->ui2_screen_w/8));ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }
	 ui4_k=ui4_j;
	 ui4_clr_bits = 0xFFFF0000; ///Red	
        for (ui4_j = ui4_k;ui4_j < (ui4_k+(pt_this->ui2_screen_w/8));ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }
	 ui4_k=ui4_j;
	 ui4_clr_bits = 0xFF0000FF; ///Blue	
        for (ui4_j = ui4_k;ui4_j < (ui4_k+(pt_this->ui2_screen_w/8));ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }
	 ui4_k=ui4_j;
	 ui4_clr_bits = 0xFF000000; ///Black
        for (ui4_j = ui4_k;ui4_j < (ui4_k+(pt_this->ui2_screen_w/8));ui4_j++)
        {
         pui4_fbm[ui4_j] = ui4_clr_bits;
        }			
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

static INT32 _flicker_draw_data_squarebox (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32* pui4_fbm = NULL;
    UINT32 u4_screen_h=0;
    UINT32 u4_screen_w=0;	
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }

        pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
	 u4_screen_h = pt_this->ui2_screen_h/20;
	 u4_screen_w = pt_this->ui2_screen_w/20;
        for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
        {
            pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
            if((ui4_i >=(u4_screen_h *9)) && (ui4_i <=(u4_screen_h *11)))///nick 20120607
            		{
            		for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
            			{
            			 if((ui4_j >=(u4_screen_w *9)) && (ui4_j <=(u4_screen_w *11)))///nick 20120607
            			 	{
                			pui4_fbm[ui4_j] = 0xFFFFFFFF;
            			 	}
				else{ pui4_fbm[ui4_j] = 0xFF000000;} 
            			}
            		}	
   /*         if(ui4_i == 0)
            {
                c_dbg_stmt("[] check horizontal: 0x%x, 0x%x\n", pui4_fbm[0], pui4_fbm[pt_this->ui2_screen_w-1]);
            } */
        }
    
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
#endif

#if 0//Cedric flicker
static INT32 _flicker_draw_data (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32 ui4_i, ui4_j;
    UINT32 ui4_clr_bits = (255 << 24) | (0 << 16) | (128 << 8) | (0 << 0);
    UINT32* pui4_fbm = NULL;
    BOOL b_paint_even = TRUE;
    UINT8 ui1_hori_cnt = 1;
        
    i4_ret = c_gl_surface_fill(pt_this->h_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_fill() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    i4_ret = c_gl_surface_lock (pt_this->h_surf, NULL, GL_SYNC, &t_lock_info);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_lock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
    for (ui4_i = 0;ui4_i < pt_this->ui2_screen_h;ui4_i++)
    {
        pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
        if (ui4_i != 0)
        {
            if (ui1_hori_cnt == 1)
            {
                if (b_paint_even)
                {
                    b_paint_even = FALSE;
                }
                else
                {
                    b_paint_even = TRUE;
                }
                ui1_hori_cnt = 0;
            }
            else
            {
                ui1_hori_cnt++;
            }
        }
        for (ui4_j = 0;ui4_j < pt_this->ui2_screen_w;ui4_j++)
        {
            if (b_paint_even)
            {
                if ((ui4_j % 2) == 0)
                {
                    pui4_fbm[ui4_j] = ui4_clr_bits;
                }
            }
            else
            {
                if ((ui4_j % 2) == 1)
                {
                    pui4_fbm[ui4_j] = ui4_clr_bits;
                }
            }
        }
    }
    i4_ret = c_gl_surface_unlock (pt_this->h_surf, NULL);
    if(GLR_OK != i4_ret)
    {
        DBG_ERROR(("c_gl_surface_unlock() failed. i4_ret = %d\r\n", i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name:    _flicker_init
 * Description: Toggle whether input src change is triggered by one touch play.
 * Input:   b_true  Determine whether input src change is triggered by one 
 *                  touch play.
 * Output:  -
 * Returns  TRUE    CEC comp will grab activation.
 *          FALSE   CEC comp will not grab activation.
 *---------------------------------------------------------------------------*/
static INT32 _flicker_init (
                    NAV_CONTEXT_T* pt_ctx
                    )
{
    c_memset (&t_flicker, 0, sizeof (NAV_FLICKER_T));
    
    return NAVR_OK;
}
static INT32 _flicker_deinit (VOID)
{
    return NAVR_OK;
}
BOOL nav_flicker_is_running (VOID)
{
    return t_flicker.b_is_running;
}
static INT32 _flicker_enter (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;

    nav_flicker_custom_pre_init (NULL, NULL, NULL, NULL);
    i4_ret = _flicker_disable_video (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_init_plane (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_init_view (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_init_disp_res (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_link_plane_view (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    nav_flicker_custom_post_init (NULL, NULL, NULL, NULL);
    
    return NAVR_OK;
}
static INT32 _flicker_exit (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    
    nav_flicker_custom_pre_deinit (NULL, NULL, NULL, NULL);

    i4_ret = _flicker_unlink_plane_view (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_deinit_disp_res (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_deinit_view (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_deinit_plane (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_enable_video (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = _flicker_enable_video (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    nav_flicker_custom_post_deinit (NULL, NULL, NULL, NULL);

    return NAVR_OK;
}
#if 1//Cedric flicker
static INT32 _flicker_draw_pattern (NAV_FLICKER_T* pt_this, INT32 u4_pattern)
{
    INT32 i4_ret = 0;

    if (u4_pattern == 1)
    {
        i4_ret = _flicker_draw_data_flicker(pt_this);
    }
    else if (u4_pattern >= 2 && u4_pattern <= 5)
    {
        i4_ret = _flicker_draw_data_gradation(pt_this, u4_pattern-2);
    }
#if 1///20120322 nick add	
    else if (u4_pattern ==6)
    {
     i4_ret = _flicker_draw_data_vcom_internal_pattern(pt_this);
    }
    else if (u4_pattern ==7)
    {
     i4_ret = _flicker_draw_data_colorbar(pt_this);
    }
    else if (u4_pattern ==8)
    {
     i4_ret = _flicker_draw_data_squarebox(pt_this);
    }	
    else if ((u4_pattern ==9) || (u4_pattern ==10) || (u4_pattern ==11) || (u4_pattern ==12)|| (u4_pattern ==13))///nick 20120820
    {
    i4_ret = _flicker_draw_data_color_pattern (pt_this,u4_pattern-9);
    }		
    else if ((u4_pattern ==14) || (u4_pattern ==15))///nick 20120820
    {
     i4_ret = _flicker_draw_data_squarebox_1(pt_this,u4_pattern-14);
    }
    else if ((u4_pattern ==16) || (u4_pattern ==17))///nick 20120820
    {
     i4_ret = _flicker_draw_data_stripe_line(pt_this,u4_pattern-16);
    }
    else if ((u4_pattern ==18) || (u4_pattern ==19) || (u4_pattern ==20))///nick 20120820
    {
     i4_ret = _flicker_draw_data_subpixel(pt_this,u4_pattern-18);
    }

#endif///end 	SUPPORT_TIAN_FACTORY_COMMAND_EU
#if 0 //libfactory4.so build error
    c_gl_surface_flip(pt_this->h_surf, 0);
#endif
    return i4_ret;
}

static VOID _flicker_close_pattern(NAV_FLICKER_T * pt_this)
{
    if (nav_flicker_is_running ())
    {
        _flicker_set_pattern_idx(pt_this, 0);
        if (_flicker_exit (pt_this) == NAVR_OK)
        {
            pt_this->b_is_running = FALSE;
        }
    }
}

static BOOL _flicker_is_key_handler (
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    INT32 i4_ret;
    UINT32 u4_pattern_idx;
    NAV_FLICKER_T* pt_this = &t_flicker;
    
    switch (ui4_key_code)
    {
    #ifdef BTN_INVOKE_FLICKER
    case BTN_INVOKE_FLICKER:
        u4_pattern_idx = _flicker_get_pattern_idx(pt_this);
        DBG_ERROR(("\n\n Jim  _flicker_get_pattern_idx  \n"));
		
        if (nav_flicker_is_running () == FALSE)
        {
            if (u4_pattern_idx > 0 && u4_pattern_idx <= TOTAL_FLICKER_PATTERN)
            {
                i4_ret = _flicker_enter (pt_this);
				
                if (i4_ret != NAVR_OK)
                {
                    return FALSE;
                }
                i4_ret = _flicker_draw_pattern (pt_this, u4_pattern_idx);
                if (i4_ret != NAVR_OK)
                {
                    return FALSE;
                }
                pt_this->b_is_running = TRUE;
            }
        }
        else
        {
            if (u4_pattern_idx == 0 || u4_pattern_idx > TOTAL_FLICKER_PATTERN)
            {
                _flicker_close_pattern(pt_this);
				
                MTOSD_PLA_Enable(0,1);
                MTOSD_PLA_Enable(1,1);	
		    DBG_ERROR(("\n\n Jim  MTOSD_PLA_Enable  0  \n"));		
            }
            else
            {  DBG_ERROR(("\n\n Jim  _flicker_draw_pattern  0  \n"));
                i4_ret = _flicker_draw_pattern (pt_this, u4_pattern_idx);
                MTOSD_PLA_Enable(0,0);
                 MTOSD_PLA_Enable(1,0);
                 DBG_ERROR(("\n\n Jim  MTOSD_PLA_Disable  0  \n"));
				
                if (i4_ret != NAVR_OK)
                {
                    return FALSE;
                }


            }
        }
        break;
    #endif		
    case BTN_FACTORY_MODE_7:
        u4_pattern_idx = 1 + _flicker_get_pattern_idx(pt_this);
        if (u4_pattern_idx > TOTAL_FLICKER_PATTERN)
        {
            u4_pattern_idx = 0;
        }
        _flicker_set_pattern_idx(pt_this, u4_pattern_idx);
        break;
    default:
        //_flicker_close_pattern(pt_this);
        break;
    }
    return FALSE;
}
#else
static INT32 _flicker_draw_pattern (NAV_FLICKER_T* pt_this)
{
    INT32 i4_ret;
    
    i4_ret = _flicker_draw_data (pt_this);
    if (i4_ret != NAVR_OK)
    {
        return FALSE;
    }
    return NAVR_OK;
}

static BOOL _flicker_is_key_handler (
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    INT32 i4_ret;
    NAV_FLICKER_T* pt_this = &t_flicker;
    
    switch (ui4_key_code)
    {
    case BTN_INVOKE_FLICKER:
        if (nav_flicker_is_running () == FALSE)
        {
            i4_ret = _flicker_enter (pt_this);
            if (i4_ret != NAVR_OK)
            {
                return FALSE;
            }
            i4_ret = _flicker_draw_pattern (pt_this);
            if (i4_ret != NAVR_OK)
            {
                return FALSE;
            }
            pt_this->b_is_running = TRUE;
        }
        else
        {
            i4_ret = _flicker_exit (pt_this);
            if (i4_ret != NAVR_OK)
            {
                return FALSE;
            }
            pt_this->b_is_running = FALSE;
        }
        break;
    default:
        if (nav_flicker_is_running ())
        {
            i4_ret = _flicker_exit (pt_this);
            if (i4_ret != NAVR_OK)
            {
                return FALSE;
            }
            pt_this->b_is_running = FALSE;
        }
        break;
    }
    return FALSE;
}
#endif
static INT32 _flicker_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return NAVR_OK;
}
static INT32 _flicker_hide(
                    VOID
                    )
{
    return NAVR_OK;
}
static INT32 _flicker_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}
static INT32 _flicker_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    switch(pt_ui_msg->e_id)
    {
    case NAV_UI_MSG_APP_PAUSING:
        if (nav_flicker_is_running ())
        {
            a_nav_flicker_toggle_pattern ();
        }
        break;
    default:
        break;
    }
    return NAVR_OK;
}
static VOID _flicker_ctx_switch_fct_by_am (
    VOID*                       pv_tag1,
    VOID*                       pv_tag2,
    VOID*                       pv_tag3)
{
    /* Simulate a key is arrived. */
	#ifdef BTN_INVOKE_FLICKER
    _flicker_is_key_handler (NULL, BTN_INVOKE_FLICKER);
	#endif
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:    a_nav_flicker_toggle_pattern
 * Description: Toggle flicker pattern.
 * Input:   -
 * Output:  -
 * Returns  NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 a_nav_flicker_toggle_pattern (VOID)
{
    if (nav_is_active () == FALSE)
    {
        nav_resume_self ();
        nav_request_context_switch_via_am (_flicker_ctx_switch_fct_by_am,
                                           NULL,
                                           NULL,
                                           NULL);
    }
    else
    {
    #ifdef BTN_INVOKE_FLICKER
        _flicker_is_key_handler (NULL, BTN_INVOKE_FLICKER);
    #endif
	}
                                       
    return NAVR_OK;
}

#if 1//Cedric flicker
VOID a_nav_flicker_set_pattern (UINT32 u4_pattern_idx)
{
    _flicker_set_pattern_idx(&t_flicker, u4_pattern_idx);
}

INT32 a_nav_update_pattern (VOID)
{
    if (nav_is_active () == FALSE)
    {
        nav_resume_self ();
        nav_request_context_switch_via_am (_flicker_ctx_switch_fct_by_am,
                                           NULL,
                                           NULL,
                                           NULL);
    }
    else
    {
        nav_request_context_switch_via_am (_flicker_ctx_switch_fct_by_am,
                                           NULL,
                                           NULL,
                                           NULL);
//        _flicker_is_key_handler (NULL, BTN_INVOKE_FLICKER);
    }
                                       
    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name:    a_nav_flicker_register
 * Description: Register flicker component.
 * Input:   pt_flicker_hdlr A pointer to the custom handler.
 * Output:  -
 * Returns  NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 a_nav_flicker_register (FLICKER_HDLR_T* pt_flicker_hdlr)
{
    NAV_COMP_T  t_comp;
    INT32       i4_ret;
    NAV_FLICKER_T* pt_this = &t_flicker;

    c_memset (&t_comp, 0, sizeof (NAV_COMP_T));

    if (pt_flicker_hdlr == NULL)
    {
        pt_this->t_hdlr.pf_init = _flicker_init;
        pt_this->t_hdlr.pf_deinit = _flicker_deinit;
        pt_this->t_hdlr.pf_hide = _flicker_hide;
        pt_this->t_hdlr.pf_is_key_handler= _flicker_is_key_handler;
        pt_this->t_hdlr.pf_activate= _flicker_activate;
    }
    else
    {
        pt_this->t_hdlr = *pt_flicker_hdlr;
    }

    t_comp.pf_init           = pt_this->t_hdlr.pf_init;
    t_comp.pf_deinit         = pt_this->t_hdlr.pf_deinit;
    t_comp.pf_is_key_handler = pt_this->t_hdlr.pf_is_key_handler;
    t_comp.pf_activate       = pt_this->t_hdlr.pf_activate;
    t_comp.pf_inactivate     = _flicker_inactivate;
    t_comp.pf_hide           = pt_this->t_hdlr.pf_hide;
    t_comp.pf_handle_msg     = _flicker_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_FLICKER, &t_comp, COMP_EXEC_SET_FLICKER);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return NAVR_OK;
}
#endif

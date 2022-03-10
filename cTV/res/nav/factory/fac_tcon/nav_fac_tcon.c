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
 * $RCSfile: nav_fac_tcon.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
// For Test Pattern and MAX9668
#include "c_scc.h"
#include "c_common.h"
#include "c_handle_grp.h"
#include "c_wgl.h"
#include "u_gl.h"

#include "c_rm.h"
#include "u_drv_cust.h"
#include "u_rm_dev_types.h"

//For other implement
#include "res/app_util/config/a_cfg_custom.h" //APP_FAC_MENU
#include "app_util/a_cfg.h"
#include "nav/a_navigator.h"
#include "res/nav/nav_variant.h"
#include "nav_fac_tcon.h"
#include "res/nav/factory/a_factory.h"

#include "nav_fac_tcon.h"

#include "BUF08630.h"
#include "maxim_PF78IOS.h"
#include "TI_TPS65168.h"
#include "maxim_MAX9668.h"


/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
//#define TPV_VCOM_IIC_SWITCH_SUPPORT

#define _WAIT_SYNC(h_sema, b_sync)                                        \
		do {															  \
			if (! b_sync)												  \
			{															  \
				b_sync = TRUE;											  \
				c_sema_lock(h_sema, X_SEMA_OPTION_WAIT);				  \
			}															  \
		} while (0)

#define _SIGNAL_SYNC(h_sema, b_sync)                                      \
		do {															  \
			if (b_sync) 												  \
			{															  \
				c_sema_unlock(h_sema);									  \
				b_sync = FALSE; 										  \
			}															  \
		} while (0)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FAC_TCON_T            t_g_nav_fac_tcon  = {0};

/* VCOM adjusting */

static BOOL b_test_pattern_onoff = FALSE;

BOOL    b_VCOM_align_initial = FALSE;

static HANDLE_T   h_g_svctx;
static HANDLE_T   h_g_sub_svctx;

static HANDLE_T   h_g_plane;
static HANDLE_T   h_g_view;
static HANDLE_T   h_g_surf;
static HANDLE_T   h_g_surf_buf;

static UINT16     ui2_screen_w = 0;
static UINT16     ui2_screen_h = 0;
static UINT32     ui4_viewport;

static UINT8      ui1_g_id;

static HANDLE_T              h_g_bin_sema             = NULL_HANDLE;         /* A semaphore to perform sync operation. */
static BOOL                  b_g_sync_op              = FALSE;               /* A flag indicating if sync operation is being performed. */



/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _fac_svctx_nfy_fct(HANDLE_T h_svctx,
                                 SVCTX_COND_T e_nfy_cond,
                                 SVCTX_NTFY_CODE_T e_code,
                                 STREAM_TYPE_T e_stream_type,
                                 VOID * pv_nfy_tag);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_init
 * Description: initialize this component  this component
 * Inputs:  pt_ctx     point the environment of the navigater module requested
 * Outputs: NONE
 * Returns: NAVR_OK    routine is successful
 *          NAVR_FAIL  routine is failed
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_FAC_TCON_T*  pt_this = &t_g_nav_fac_tcon;
    INT32            i4_ret;

    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    pt_ctx->t_gui_res.e_color_type
                    );

    /* Create semaphore. */
    i4_ret = c_sema_create (& h_g_bin_sema,
                            X_SEMA_TYPE_BINARY,
                            X_SEMA_STATE_LOCK /* Lock */);
    if( i4_ret != OSR_OK )
    {
        return i4_ret;
    }

    i4_ret = c_svctx_open(SVCTX_NAME_MAIN,
                          &h_g_svctx);
    if( i4_ret != OSR_OK )
    {
        return i4_ret;
    }

    i4_ret = c_svctx_open(SVCTX_NAME_SUB,
                          &h_g_sub_svctx);
    if( i4_ret != OSR_OK )
    {
        return i4_ret;
    }

    /* Set SVCTX listner. */
    i4_ret = c_svctx_set_listener (h_g_svctx,
                                   _fac_svctx_nfy_fct,
                                   NULL);
    if( i4_ret != SVCTXR_OK )
    {
        return i4_ret;
    }

    b_test_pattern_onoff = FALSE;

    if(nav_fac_BUF08630_tcon_is_existed() && nav_fac_BUF08630_tcon_check_panel())
    {
        DBG_LOG_PRINT(("nav_fac_BUF08630_tcon_is_existed\n"));
        i4_ret = nav_fac_BUF08630_tcon_check_and_set_def_val();
        if( i4_ret != TCON_OK )
        {
            DBG_LOG_PRINT(("nav_fac_BUF08630_tcon_check_and_set_def_val() fail at Line : %d in %s\n", __LINE__, __FILE__));
        }
    }

    if(TPS65168_is_existed())
    {
        DBG_LOG_PRINT(("TPS65168_is_existed\n"));
        i4_ret = TPS65168_check_and_set_def_val();
        if( i4_ret != TCON_OK )
        {
            DBG_LOG_PRINT(("TPS65168_check_and_set_def_val() fail at Line : %d in %s\n", __LINE__, __FILE__));
        }
    }

    #if 0
    if(nav_fac_MAX9668_tcon_is_existed() && nav_fac_MAX9668_tcon_check_panel())
    {
        DBG_LOG_PRINT(("nav_fac_MAX9668_tcon_is_existed\n"));
        i4_ret = nav_fac_MAX9668_tcon_check_and_set_def_val();
        if( i4_ret != TCON_OK )
        {
            DBG_LOG_PRINT(("nav_fac_MAX9668_tcon_check_and_set_def_val() fail at Line : %d in %s\n", __LINE__, __FILE__));
        }
    }
    
    if(PF78IOS_is_existed())
    {
        DBG_LOG_PRINT(("PF78IOS_is_existed\n"));
        i4_ret = PF78IOS_check_and_set_def_val();
        if( i4_ret != TCON_OK )
        {
            DBG_LOG_PRINT(("TPS65168_check_and_set_def_val() fail at Line : %d in %s\n", __LINE__, __FILE__));
        }
    }
    #endif
    
    return TCON_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_deinit
 * Description: uninitialize this component
 * Inputs:  NONE
 * Outputs: NONE
 * Returns: NAVR_OK    routine is successful
 *          NAVR_FAIL  routine is failed
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_deinit(VOID)
{
    NAV_FAC_TCON_T*  pt_this = &t_g_nav_fac_tcon;
    INT32       i4_ret;

    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_is_key_handler
 * Description: judge a key is an hot key of this component
 * Inputs:  pt_ctx        the environment of the navigater module requested
 *          ui4_key_code  the key value
 * Outputs: NONE
 * Returns: TRUE          is the hot key
 *          FALSE         is not the hot key
 ----------------------------------------------------------------------------*/
static BOOL _nav_fac_tcon_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_FAC_TCON_T*  pt_this = &t_g_nav_fac_tcon;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI)) {
        return FALSE;
    }

    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_activate
 * Description: active this component
 * Inputs:  pt_ctx        the environment of the navigater module requested
 *          ui4_key_code  the key value
 * Outputs: NONE
 * Returns: NAVR_NO_ACTION
 *          NAVR_OK
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_FAC_TCON_T*  pt_this = &t_g_nav_fac_tcon;
    INT32       i4_ret;

    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK) {
        DBG_LOG_PRINT(("t_view_hdlr.pf_activate() failed. i4_ret = %d on _nav_fac_tcon_activate() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }

    nav_set_component_visible(NAV_COMP_ID_FAC_TCON);
    pt_this->b_is_on = TRUE;

    fac_initial_vcom( TRUE, NULL );

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_hide
 * Description: hide(inactivate) this component
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_NO_ACTION
 *          NAVR_OK
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_hide(
                    VOID
                    )
{
    INT32 i4_ret;
    NAV_FAC_TCON_T*  pt_this = &t_g_nav_fac_tcon;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    pt_this->t_view_hdlr.pf_hide();
    pt_this->b_is_on = FALSE;

    if(fac_test_ptn_get_status())
    {
        i4_ret = fac_test_ptn_page_hide();
        if( i4_ret != APP_CFGR_OK )
        {
            DBG_LOG_PRINT(("_nav_fac_tcon_view_hide() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        }
        fac_test_ptn_set_status(FALSE);
        fac_vcom_init_set_status(FALSE);
    }
    
    nav_return_activation(NAV_COMP_ID_FAC_TCON);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_handle_msg
 * Description: handle the message from navigater controller
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    return NAVR_OK;
}

/*----------------------------------------------------------------------------
* Name: _init_plane
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _init_plane(VOID)
{
    UINT8              ui1_i;
    INT32              i4_ret;
    UINT16             ui2_plane_count;
    UINT32             ui4_gui_idx;
    GL_HSCREEN_T       h_screen;
    GL_SCREEN_STATUS_T t_src_status;
    GL_PLANE_CAPS_T    t_plane_caps;
 
    /* Open screen*/
    i4_ret = c_gl_screen_open(SN_PRES_MAIN_DISPLAY, NULL, NULL, &h_screen);
    if( i4_ret != GLR_OK )
    {
        DBG_LOG_PRINT(("c_gl_screen_open() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }
 
    /* Get screen capability. */
    i4_ret = c_gl_screen_get_status(h_screen, &t_src_status);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_screen_get_status() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        c_gl_obj_free(h_screen);
        return i4_ret;
    }
 
    ui2_screen_w = t_src_status.ui2_width;
    ui2_screen_h = t_src_status.ui2_height;

    /* Find a suit plane for image*/
    i4_ret = c_gl_plane_num(&ui2_plane_count);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_plane_num() failed. i4_ret = %d. at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        c_gl_obj_free(h_screen);
        return i4_ret;
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
            i4_ret = APP_CFGR_INTERNAL_ERR;
            DBG_LOG_PRINT(("c_gl_plane_enum(%d) failed. i4_ret = %d at line %d of %s.\r\n", ui1_i, i4_ret, __LINE__, __FILE__));
            break;
        }
 
        /* Check capability. */
        if(((0x00000001 << GL_COLORMODE_ARGB_D8888) & t_plane_caps.ui4_cm_caps) &&
        ((0x00000001 << 1) & t_plane_caps.ui4_z_mask))
        {
            /*found*/
            i4_ret = APP_CFGR_OK;
            break;
        }
    }
 
    if(ui1_i >= ui2_plane_count || APP_CFGR_OK != i4_ret)   /*not found or error*/
    {
        c_gl_obj_free(h_screen);
        DBG_LOG_PRINT(("c_gl_obj_free() failed. i4_ret = %d. at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    i4_ret = c_gl_plane_open(h_screen, ui1_i, &h_g_plane);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_plane_open(%d) failed. i4_ret = %d at line %d of %s.\r\n", ui1_i, i4_ret, __LINE__, __FILE__));
        h_g_plane = NULL_HANDLE;
        c_gl_obj_free(h_screen);
        return APP_CFGR_INTERNAL_ERR;
    }

    i4_ret = c_gl_plane_link(h_g_plane, h_screen, TRUE);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_plane_link() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        c_gl_obj_free(h_screen);
        return APP_CFGR_INTERNAL_ERR;
    }
    else
    {
        i4_ret = APP_CFGR_OK;
    }
    
    if(h_screen)
    {
        i4_ret = c_gl_obj_free(h_screen);
        return i4_ret;
    }

    return i4_ret;
    }
 
/*----------------------------------------------------------------------------
* Name: _init_view
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _init_view (VOID)
{
    INT32 i4_ret;

    /*create view*/
    i4_ret = c_gl_view_create(ui2_screen_w,
                             ui2_screen_h,
                             TRUE,
                             &h_g_view);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_view_create() failed. i4_ret = %d. at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return APP_CFGR_INTERNAL_ERR;
    }
    return APP_CFGR_OK;
}
 
/*----------------------------------------------------------------------------
* Name: _init_disp_res
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
static INT32 _init_disp_res (VOID)
{
    INT32                       i4_ret;
    GL_SURFACE_DESC_T           t_surf_descr;
    GL_DISPLAY_OPT_T            t_dsp_opt;
    GL_POINT_T                  t_screen_offset = {0};
 
    c_memset(&t_surf_descr, 0, sizeof(GL_SURFACE_DESC_T));
    c_memset(&t_dsp_opt, 0, sizeof(GL_DISPLAY_OPT_T));

    /*set the plane order*/
    i4_ret = c_gl_plane_reorder(h_g_plane, GL_REORDER_ABSOLUTE, 0);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_plane_reorder() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return APP_CFGR_INTERNAL_ERR;
    }
 
    /*surface setting*/
    t_surf_descr.ui4_width  = ui2_screen_w;
    t_surf_descr.ui4_height = ui2_screen_h;
    t_surf_descr.e_clrmode  = GL_COLORMODE_ARGB_D8888;

    /*create surface*/
    i4_ret = c_gl_surface_create_from_fbm(&t_surf_descr, &h_g_surf);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_surface_create() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));

        h_g_surf = NULL_HANDLE;
        return APP_CFGR_INTERNAL_ERR;
    }
 
    i4_ret = c_gl_surface_create_from_fbm(&t_surf_descr, &h_g_surf_buf);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_surface_create_from_fbm() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));

        h_g_surf_buf = NULL_HANDLE;
        return APP_CFGR_INTERNAL_ERR;
    }
 
    /*viewport setting*/
    t_dsp_opt.e_flag          = GL_DISP_OPT_POSITION | GL_DISP_OPT_BLEND_OPTION | GL_DISP_OPT_ALPHA;
    t_dsp_opt.e_blend_option  = GL_BLEND_OPT_PIXEL;
    t_dsp_opt.ui1_alpha       = 255;
    t_dsp_opt.t_pos           = t_screen_offset;

    /*create viewport*/
    i4_ret = c_gl_view_create_viewport(h_g_view,
                                    h_g_surf,
                                    &t_dsp_opt,
                                    &ui4_viewport);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("c_gl_view_create_viewport() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));

        ui4_viewport = 0;
        return APP_CFGR_INTERNAL_ERR;
    }
    return APP_CFGR_OK;
}
 
/*----------------------------------------------------------------------------
* Name: _link_plane_view
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
 static INT32 _link_plane_view (VOID)
 {
     INT32 i4_ret;
 
     i4_ret = c_gl_plane_flip(h_g_plane, h_g_view, TRUE);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_plane_flip() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
     return APP_CFGR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: _unlink_plane_view
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 static INT32 _unlink_plane_view (VOID)
 {
     INT32 i4_ret;
 
     i4_ret = c_gl_plane_flip(h_g_plane, NULL_HANDLE, TRUE);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_plane_flip() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
     return APP_CFGR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: _deinit_disp_res
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 static INT32 _deinit_disp_res (VOID)
 {
     INT32 i4_ret;
 
     i4_ret = c_gl_view_delete_viewport(h_g_view, ui4_viewport);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_view_create_viewport() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
 
         ui4_viewport = 0;
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = c_gl_obj_free (h_g_surf);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_obj_free(h_g_surf) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = c_gl_obj_free (h_g_surf_buf);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_obj_free(h_g_surf_buf) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     return APP_CFGR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: _deinit_view
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 static INT32 _deinit_view (VOID)
 {
     INT32 i4_ret;
 
     /*create view*/
     i4_ret = c_gl_obj_free (h_g_view);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_obj_free(h_g_view) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
     return APP_CFGR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: _deinit_plane
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 static INT32 _deinit_plane (VOID)
 {
     INT32 i4_ret;
 
     i4_ret = c_gl_obj_free (h_g_plane);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_obj_free(h_g_plane) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     return APP_CFGR_OK;
 }
 
 
 /*-----------------------------------------------------------------------------
  * Name: _calibration_svctx_nfy_fct
  * Description: This callback function will be called by SVCTX.
  * Inputs:  -
  * Outputs: -
  * Returns: 0                      Successful.
  *          Any other values       Failed.
  ----------------------------------------------------------------------------*/
 static VOID _fac_svctx_nfy_fct(
                     HANDLE_T             h_svctx,
                     SVCTX_COND_T         e_nfy_cond,
                     SVCTX_NTFY_CODE_T    e_code,
                     STREAM_TYPE_T        e_stream_type,
                     VOID*                pv_nfy_tag
                     )
 {
     switch (e_code)
     {
         case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
         case SVCTX_NTFY_CODE_SIGNAL_LOSS:
         {
             /* Signal that a sync operation is finished. */
             _SIGNAL_SYNC (h_g_bin_sema, b_g_sync_op);
         }
         break;
 
         default:
             break;
     }
 }
 
 /*----------------------------------------------------------------------------
  * Name: fac_disable_video
  * Description: This function disable the video.
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 INT32 fac_disable_video (VOID)
 {
     UINT8                    ui1_i = 0;
     INT32                    i4_ret = -1;
     SM_COMMAND_T             at_sm_cmds[4];
     ISL_REC_T                t_isl_rec;
     SM_CMD_CODE_T            ae_cmd_code[2] = {SCC_CMD_CODE_VIDEO_NR,
                                                SCC_CMD_CODE_VIDEO_3D_NR};
     SVCTX_VIDEO_MUTE_INFO_T  t_video_mute_info;
#if 0
     /* Set to black mute, or blue mute will block test pattern */
     t_video_mute_info.b_enable          = TRUE;
     t_video_mute_info.t_color.ui1_red   = 0;
     t_video_mute_info.t_color.ui1_green = 0;
     t_video_mute_info.t_color.ui1_blue  = 255;
 
     i4_ret = c_svctx_set(h_g_acfg_svctx_main,
                          SVCTX_COMMON_SET_VIDEO_MUTE,
                          &t_video_mute_info,
                          sizeof(SVCTX_VIDEO_MUTE_INFO_T));
     ACFG_CHK_FAIL(i4_ret, i4_ret);
#endif
     /* Leave PIP/POP mode. */
     i4_ret = a_tv_set_mode(TV_MODE_TYPE_NORMAL);
     if(TVR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("a_tv_set_mode() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return i4_ret;
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
             DBG_LOG_PRINT(("c_scc_comp_grp_set() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
             return i4_ret;
         }
     }
 
     /* Stop video. */
     a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
     ui1_g_id = t_isl_rec.ui1_id;
 
     i4_ret = c_svctx_sync_stop_svc(h_g_svctx, DEFAULT_STOP_SVC_TIMEOUT);
     if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
     {
         DBG_LOG_PRINT(("c_svctx_sync_stop_svc(main) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return i4_ret;
     }
 
     /* Stop video. */
     if(h_g_sub_svctx)
     {
         i4_ret = c_svctx_sync_stop_svc(h_g_sub_svctx, DEFAULT_STOP_SVC_TIMEOUT);
         if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
         {
             DBG_LOG_PRINT(("c_svctx_sync_stop_svc(sub) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
             return i4_ret;
         }
     }
 
     /* Disable blue mute. */
     t_video_mute_info.b_enable            = TRUE;
     t_video_mute_info.t_color.ui1_red    = 0;
     t_video_mute_info.t_color.ui1_green = 0;
     t_video_mute_info.t_color.ui1_blue    = 0;
 
     /* Disable blue mute, main*/
     i4_ret = c_svctx_set(h_g_svctx,
                          SVCTX_COMMON_SET_VIDEO_MUTE,
                          &t_video_mute_info,
                          sizeof(SVCTX_VIDEO_MUTE_INFO_T));
     if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
     {
         DBG_LOG_PRINT(("c_svctx_set(main, SVCTX_COMMON_SET_VIDEO_MUTE) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return i4_ret;
     }
 
     /* Disable blue mute, sub*/
     if(h_g_sub_svctx)
     {
         i4_ret = c_svctx_set(h_g_sub_svctx,
                              SVCTX_COMMON_SET_VIDEO_MUTE,
                              &t_video_mute_info,
                              sizeof(SVCTX_VIDEO_MUTE_INFO_T));
         if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
         {
             DBG_LOG_PRINT(("c_svctx_set(sub, SVCTX_COMMON_SET_VIDEO_MUTE) failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
             return i4_ret;
         }
     }
 
     return SVCTXR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: fac_enable_video
  * Description: This function enable the video.
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 INT32 fac_enable_video (VOID)
 {
     ISL_REC_T       t_isl_rec;
 
     /*reset blue mute*/
     a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE));
 
     /*reset NR and 3D_NR*/
     a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
     a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));
 
     a_isl_get_rec_by_idx(ui1_g_id, &t_isl_rec);
 
     a_tv_change_input_src_by_rec(h_g_svctx,
                                  SVCTX_STRM_MODE_AS_LAST,
                                  &t_isl_rec,
                                  NULL);
 
     return NAVR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: fac_init_second_osd
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 INT32 fac_init_second_osd(VOID)
 {
     INT32   i4_ret = -1;
 
     i4_ret = _init_plane ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_init_plane() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = _init_view ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_init_view() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = _init_disp_res ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_init_disp_res() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = _link_plane_view ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_link_plane_view() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     return APP_CFGR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: fac_deinit_second_osd
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 INT32 fac_deinit_second_osd(VOID)
 {
     INT32   i4_ret = -1;
 
     i4_ret = _unlink_plane_view ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_unlink_plane_view() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = _deinit_disp_res ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_deinit_disp_res() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = _deinit_view ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_deinit_view() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = _deinit_plane ();
     if( i4_ret != APP_CFGR_OK )
     {
         DBG_LOG_PRINT(("_deinit_plane() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     return APP_CFGR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: fac_reorder_plane
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 INT32 fac_reorder_plane(BOOL b_show)
 {
     INT32  i4_ret = -1;
 
     if(b_show)
     {
         i4_ret = c_gl_plane_reorder(h_g_plane, GL_REORDER_ABSOLUTE, 0);
          if( i4_ret != APP_CFGR_OK )
         {
             DBG_LOG_PRINT(("c_gl_plane_reorder() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
             return APP_CFGR_INTERNAL_ERR;
         }
     }
     else
     {
         i4_ret = c_gl_plane_reorder(h_g_plane, GL_REORDER_ABSOLUTE, 1);
         if( i4_ret != APP_CFGR_OK )
         {
             DBG_LOG_PRINT(("c_gl_plane_reorder() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
             return APP_CFGR_INTERNAL_ERR;
         }
     }
 
     return APP_CFGR_OK;
 }
 
 /*----------------------------------------------------------------------------
  * Name: fac_get_surf_data
  * Description:
  * Inputs:
  * Outputs:
  * Returns:
  ----------------------------------------------------------------------------*/
 INT32 fac_get_surf_data(HANDLE_T*  ph_surf,
                      HANDLE_T*  ph_surf_buf,
                      UINT16*    pui2_surf_w,
                      UINT16*    pui2_surf_h)
 {
     if(NULL == ph_surf || NULL == ph_surf_buf ||
     NULL == pui2_surf_h || NULL == pui2_surf_w)
     {
         DBG_LOG_PRINT(("point to NULL on fac_get_surf_data() at line %d of %s.\r\n", __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     *ph_surf     = h_g_surf;
     *ph_surf_buf = h_g_surf_buf;
     *pui2_surf_w = ui2_screen_w;
     *pui2_surf_h = ui2_screen_h;
 
     return APP_CFGR_OK;
 }

/*----------------------------------------------------------------------------
* Name: fac_copy_data_from_buf
* Description:
* Inputs:
* Outputs:
* Returns:
----------------------------------------------------------------------------*/
extern INT32 fac_copy_data_from_buf(HANDLE_T  h_surf, HANDLE_T h_surf_buf)
{
     INT32   i4_ret = -1;
     GL_COLOR_T t_empty_clr = {255, {0}, {0}, {0}};
 
     i4_ret = c_gl_surface_fill(h_g_surf, &t_empty_clr, GL_SYNC);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_surface_fill() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = c_gl_surface_blt(h_surf,
                               h_surf_buf,
                               0,
                               0,
                               0,
                               0,
                               ui2_screen_w,
                               ui2_screen_h,
                               255,
                               GL_SRC_OVER);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_surface_blt() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     return APP_CFGR_OK;
}
 
 /*----------------------------------------------------------------------------
 * Name: fac_draw_frame_data
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
 INT32 fac_draw_frame_data (HANDLE_T h_surf_buf, UINT16 b_ptn_sel)
 {
     INT32          i4_ret;
     GL_COLOR_T     t_empty_clr = {255, {0}, {0}, {0}};
     GL_LOCK_INFO_T t_lock_info;
     UINT32         ui4_i, ui4_j;
     UINT32*        pui4_fbm = NULL;
     BOOL b_col,b_row,b_draw;
 
     i4_ret = c_gl_surface_fill(h_surf_buf, &t_empty_clr, GL_SYNC);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_surface_fill() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     i4_ret = c_gl_surface_lock (h_surf_buf, NULL, GL_SYNC, &t_lock_info);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_surface_lock() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
     pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;
 
 
    switch(b_ptn_sel)
    {
    case 0:
        for (ui4_i = 0; ui4_i < ui2_screen_h; ui4_i++)
        {
            for (ui4_j = 0; ui4_j < ui2_screen_w; ui4_j++)
            {
                if(0 == ui4_i || ui2_screen_h - 1 == ui4_i ||
                0 == ui4_j || ui2_screen_w - 1 == ui4_j)
                {
                    /*Draw frame*/
                    pui4_fbm[ui4_i * (t_lock_info.at_subplane[0].ui4_pitch / 4) + ui4_j] =
                    GL_COLOR_ARGB8888(255, 255, 255, 255);
                }
                else
                {
                    b_col = ui4_j & 1;
                    //              b_row = (ui4_i >> 1 ) & 1; //Denny 2009/11/30 mark
                    b_row = (ui4_i) & 1; //Denny 2009/11/30 mark
                    b_draw =  b_col ^ b_row;
                    /*Draw content*/
                    if( b_draw  )
                    {
                        pui4_fbm[ui4_i * t_lock_info.at_subplane[0].ui4_pitch / 4 + ui4_j] =  GL_COLOR_ARGB8888(255, 0, 127, 0);
                    }
                    else
                    {
                        pui4_fbm[ui4_i * t_lock_info.at_subplane[0].ui4_pitch / 4 + ui4_j] =  GL_COLOR_ARGB8888(255, 0, 0, 0);
                    }
                }
            }
        }
    break;
 
     case 1:
     for (ui4_i = 0; ui4_i < ui2_screen_h; ui4_i++)
     {
         for (ui4_j = 0; ui4_j < ui2_screen_w; ui4_j++)
         {
             if(0 == ui4_i || ui2_screen_h - 1 == ui4_i ||
                0 == ui4_j || ui2_screen_w - 1 == ui4_j)
             {
                 /*Draw frame*/
                 pui4_fbm[ui4_i * (t_lock_info.at_subplane[0].ui4_pitch / 4) + ui4_j] =
                 GL_COLOR_ARGB8888(255, 255, 255, 255);
             }
             else
             {
                 b_col = ui4_j & 1;
                 b_row = (ui4_i >> 1 ) & 1;
                 b_draw =  !(b_col ^ b_row );
                 /*Draw content*/
                 if( b_draw  )
                 {
                     pui4_fbm[ui4_i * t_lock_info.at_subplane[0].ui4_pitch / 4 + ui4_j] =  GL_COLOR_ARGB8888(255, 0, 127, 0);
                 }
                 else
                 {
                     pui4_fbm[ui4_i * t_lock_info.at_subplane[0].ui4_pitch / 4 + ui4_j] =  GL_COLOR_ARGB8888(255, 0, 0, 0);
                 }
 
             }
         }
         }
     break;
         }
 
 
     i4_ret = c_gl_surface_unlock (h_surf_buf, NULL);
     if(GLR_OK != i4_ret)
     {
         DBG_LOG_PRINT(("c_gl_surface_unlock() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
         return APP_CFGR_INTERNAL_ERR;
     }
 
     return APP_CFGR_OK;
 }

/*----------------------------------------------------------------------------
* Name: fac_test_ptn_page_show
* Description: Show Test Pattern for VCom adjusting.
* Inputs:  ptn_sel - select desired pattern (0 : with frame, 1 : without frame)
* Outputs: none
* Returns: APP_CFGR_OK/APP_CFGR_INV_ARG/.....
----------------------------------------------------------------------------*/
INT32 fac_test_ptn_page_show(UINT16 ptn_sel)
{
    INT32              i4_ret = -1;
    UINT16             ui2_g_screen_w;
    UINT16             ui2_g_screen_h;
 
    i4_ret = fac_disable_video();
    if( i4_ret != NAVR_OK)
    {
        DBG_LOG_PRINT(("fac_disable_video() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }
 
    i4_ret = fac_init_second_osd();
    if( i4_ret != NAVR_OK )
    {
        DBG_LOG_PRINT(("fac_init_second_osd() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }
 
    i4_ret = fac_get_surf_data(&h_g_surf,
                             &h_g_surf_buf,
                             &ui2_g_screen_w,
                             &ui2_g_screen_h);
    if( i4_ret != NAVR_OK )
    {
        DBG_LOG_PRINT(("fac_get_surf_data() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }

    i4_ret = fac_draw_frame_data(h_g_surf_buf,ptn_sel);
    if( i4_ret != NAVR_OK )
    {
        DBG_LOG_PRINT(("fac_draw_frame_data() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }

    i4_ret = fac_copy_data_from_buf(h_g_surf, h_g_surf_buf);
    if( i4_ret != NAVR_OK )
    {
        DBG_LOG_PRINT(("fac_copy_data_from_buf() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }


    i4_ret = fac_reorder_plane(FALSE);
    if( i4_ret != NAVR_OK )
    {
        DBG_LOG_PRINT(("fac_reorder_plane() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return i4_ret;
    }

    return NAVR_OK;
}
 
/*----------------------------------------------------------------------------
* Name: fac_test_ptn_page_hide
* Description: Hide Test Pattern for VCom adjusting.
* Inputs:  none
* Outputs: none
* Returns: APP_CFGR_OK/APP_CFGR_INV_ARG/.....
----------------------------------------------------------------------------*/
INT32 fac_test_ptn_page_hide(VOID)
{
    INT32 i4_ret = -1;

    i4_ret = fac_deinit_second_osd();
    if( i4_ret != NAVR_OK )
    {
        DBG_LOG_PRINT(("fac_deinit_second_osd() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    i4_ret = fac_enable_video();
    if( i4_ret != NAVR_OK )
    {
        DBG_LOG_PRINT(("fac_enable_video() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return APP_CFGR_INTERNAL_ERR;
    }

    return NAVR_OK;
}
 
/*----------------------------------------------------------------------------
* Name: fac_test_ptn_get_status
* Description: Get the value of "b_test_pattern_onoff".
* Inputs:  none
* Outputs: none
* Returns: "TRUE"-Test Pattern is ON. "FALSE"-Test Pattern is OFF.
----------------------------------------------------------------------------*/
BOOL fac_test_ptn_get_status(VOID)
{
    return b_test_pattern_onoff;
}
 
/*----------------------------------------------------------------------------
* Name: fac_test_ptn_set_status
* Description: Set the value of "b_test_pattern_onoff".
* Inputs:  bVal
* Outputs: none
* Returns: none
----------------------------------------------------------------------------*/
VOID fac_test_ptn_set_status(BOOL bVal)
{
    b_test_pattern_onoff = bVal;
}
 
/*----------------------------------------------------------------------------
* Name: fac_vcom_init_get_status
* Description: Get the value of "b_VCOM_align_initial".
* Inputs:  none
* Outputs: none
* Returns: "TRUE"-VCom align is initialized. "FALSE"-VCom align is not initialized.
----------------------------------------------------------------------------*/
BOOL fac_vcom_init_get_status(VOID)
{
    return b_VCOM_align_initial;
}

/*----------------------------------------------------------------------------
* Name: fac_vcom_init_set_status
* Description: Set the value of "b_VCOM_align_initial".
* Inputs:  bVal
* Outputs: none
* Returns: none
----------------------------------------------------------------------------*/
VOID fac_vcom_init_set_status(BOOL bVal)
{
    b_VCOM_align_initial = bVal;
}

/*----------------------------------------------------------------------------
* Name: fac_initial_vcom
* Description: Initial function. Get value of Vcom & Gamma, and display Vcom test pattern.
* Inputs: b_interanl_pattern       if display internal pixel on/off pattern
* Outputs: pui2_current_vcom       current VCOM value
* Returns:
----------------------------------------------------------------------------*/
INT32 fac_initial_vcom (BOOL b_interanl_pattern, UINT16 *pui2_current_vcom )
{
    INT32   i4_ret;
    INT32    vcom_ptn_sel=0;

    fac_vcom_init_set_status(FALSE);
    if( pui2_current_vcom != NULL )
    {
        *pui2_current_vcom = 0;
    }
    
#ifdef TPV_VCOM_IIC_SWITCH_SUPPORT
    i4_ret = nav_fac_get_vcom_reg_val(&ui2_VCOM_DAC_value);
    if( i4_ret != TCON_OK )
    {
        DBG_LOG_PRINT(("a_cfg_custom_factory_get_max9668_reg() failed. i4_ret = %d on %s at line %d of %s.\r\n", i4_ret, __LINE__, __func__ ,__FILE__));
        return i4_ret;
    }

    if( pui2_current_vcom != NULL )
    {
        *pui2_current_vcom = ui2_VCOM_DAC_value;
    }
    i4_ret = nav_fac_get_vcom_max_min_val(&ui2_VCOM_DAC_max_value, &ui2_VCOM_DAC_min_value)
    if( i4_ret != TCON_OK )
    {
        DBG_LOG_PRINT(("nav_fac_get_tcon_reg() failed. i4_ret = %d on %s at line %d of %s.\r\n", i4_ret, __LINE__, __func__ ,__FILE__));
        return i4_ret;
    }
#endif //TPV_VCOM_IIC_SWITCH_SUPPORT

    if( b_interanl_pattern )
    {
 //        nav_grab_activation(NAV_COMP_ID_FAC); // This is to prevent from screen saver activating. Assign to a dummy nav component, and not to show it.
        i4_ret = fac_test_ptn_page_show(vcom_ptn_sel);
        if( i4_ret != APP_CFGR_OK )
        {
            DBG_LOG_PRINT(("fac_test_ptn_page_show() failed. i4_ret = %d on %s at line %d of %s.\r\n", i4_ret, __LINE__, __func__ ,__FILE__));
            return APP_CFGR_INTERNAL_ERR;
        }

        fac_test_ptn_set_status(TRUE);
     }
     else
     {
         i4_ret = fac_test_ptn_page_hide();
         if( i4_ret != APP_CFGR_OK )
         {
             DBG_LOG_PRINT(("fac_test_ptn_page_hide() failed. i4_ret = %d on %s at line %d of %s.\r\n", i4_ret, __LINE__, __func__ ,__FILE__));
             return APP_CFGR_INTERNAL_ERR;
         }
         fac_test_ptn_set_status(FALSE);
     }
 
     fac_vcom_init_set_status(TRUE);
     
     return APP_CFGR_OK;
}

/*----------------------------------------------------------------------------
* Name: nav_fac_tcon_load_def
* Description: 
* Inputs:  none
* Outputs: none
* Returns: APP_CFGR_OK/APP_CFGR_INV_ARG/.....
----------------------------------------------------------------------------*/
INT32 nav_fac_tcon_load_def(VOID)
{
    INT32 i4_ret = -1;
    UINT8       ui1_i;	
    
    nav_fac_BUF08630_load_def_vcom_by_panel_id();
    for(ui1_i=0; ui1_i<8; ui1_i++)
    {
        i4_ret = nav_fac_BUF08630_load_def_gamma_by_panel_id(ui1_i);
        if(i4_ret != APP_CFGR_OK) {
            return i4_ret;
        }
    }

    #if 0
    nav_fac_MAX9668_load_def_vcom_by_panel_id();
    for(ui1_i=0; ui1_i<8; ui1_i++)
    {
        i4_ret = nav_fac_MAX9668_load_def_gamma_by_panel_id(ui1_i);
        if(i4_ret != APP_CFGR_OK) {
            return i4_ret;
        }
    }

    i4_ret = TPS65168_load_temp_def();
    if (i4_ret != APP_CFGR_OK){
        DBG_LOG_PRINT(("TPS65168_load_temp_def() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
    }

    i4_ret = PF78IOS_load_temp_def();
    if (i4_ret != APP_CFGR_OK){
        DBG_LOG_PRINT(("PF78IOS_load_temp_def() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
    }
    #endif
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_sif_x_read
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_fac_sif_x_read(UINT8 u1CHannelID, UINT16 u2ClkDiv, UINT8 u1DevAddr, INT8 u1WordAddrNum, 
                                    UINT32 u4WordAddr, UINT8 *pu1Buf, UINT16 u2ByteCnt)
{
#ifdef NEVER
    DRV_CUST_OPERATION_INFO_T t_op_info;
    MISC_TYPE_SIF_ADVANCED_T t_get_info;
    SIZE_T  z_info_size = sizeof(t_op_info);
    SIZE_T  z_size = sizeof(MISC_TYPE_SIF_ADVANCED_T);
    INT32 i4_ret;

    t_get_info.ui1_channel = u1CHannelID;
    t_get_info.ui2_clkdiv = u2ClkDiv;
    t_get_info.ui4_addr = (UINT32)u1DevAddr;
    t_get_info.ui1_offset_len = u1WordAddrNum;
    t_get_info.ui4_offset = u4WordAddr;
    t_get_info.ui1_data_len =(UINT8)u2ByteCnt;
    t_get_info.pui1_data = pu1Buf;

    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_OPERATION_TYPE_SIF_READ;
    t_op_info.u.t_vid_set_info.b_store = FALSE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&t_get_info;
    t_op_info.u.t_vid_set_info.z_size = z_size;

    i4_ret = c_rm_set_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_info_size);

    if ( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_get_comp fail\n", __func__));
        return i4_ret;
    }
#endif /* NEVER */

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_sif_x_write
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_fac_sif_x_write(UINT8 u1CHannelID, UINT16 u2ClkDiv, UINT8 u1DevAddr, INT8 u1WordAddrNum, 
                                    UINT32 u4WordAddr, UINT8 *pu1Buf, UINT16 u2ByteCnt)
{
#ifdef NEVER
    DRV_CUST_OPERATION_INFO_T t_op_info;
    MISC_TYPE_SIF_ADVANCED_T t_get_info;
    SIZE_T  z_info_size = sizeof(t_op_info);
    SIZE_T  z_size = sizeof(MISC_TYPE_SIF_ADVANCED_T);
    INT32 i4_ret;

    t_get_info.ui1_channel = u1CHannelID;
    t_get_info.ui2_clkdiv = u2ClkDiv;
    t_get_info.ui4_addr = (UINT32)u1DevAddr;
    t_get_info.ui1_offset_len = u1WordAddrNum;
    t_get_info.ui4_offset = u4WordAddr;
    t_get_info.ui1_data_len =(UINT8)u2ByteCnt;
    t_get_info.pui1_data = pu1Buf;

    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_OPERATION_TYPE_SIF_WRITE;
    t_op_info.u.t_vid_set_info.b_store = FALSE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&t_get_info;
    t_op_info.u.t_vid_set_info.z_size = z_size;

    i4_ret = c_rm_set_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_info_size);

    if ( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_set_comp fail\n", __func__));
        return i4_ret;
    }
#endif /* NEVER */

    return RMR_OK;
    
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: a_nav_fac_register
 * Description: register this component to navigater module
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 a_nav_fac_tcon_register(
                    NAV_FAC_TCON_VIEW_HDLR_T*       pt_view_hdlr
                    )
{
    NAV_FAC_TCON_T*  pt_this = &t_g_nav_fac_tcon;
    NAV_COMP_T  t_comp;
    INT32       i4_ret;

    c_memset(&t_comp,0,sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_FAC */
    t_comp.pf_init           = _nav_fac_tcon_init;
    t_comp.pf_deinit         = _nav_fac_tcon_deinit;
    t_comp.pf_is_key_handler = _nav_fac_tcon_is_key_handler;
    t_comp.pf_activate       = _nav_fac_tcon_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _nav_fac_tcon_hide;
    t_comp.pf_handle_msg     = _nav_fac_tcon_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_FAC_TCON, &t_comp, COMP_EXC_SET_FAC_TCON);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL) {
        nav_fac_tcon_view_register_default_hdlr(&pt_this->t_view_hdlr);
    } else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }

    return NAVR_OK;
}


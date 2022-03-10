/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2004, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: burning_mode_patgen.c,v $
 * $Revision: #1 $
 * $Date: 2015/10/09 $
 * $Author: dtvbm11 $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Chris Kuo $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_common.h"

#include "u_gl.h"
#include "c_iom.h"

#include "app_util/a_common.h"
#include "nav/burning_mode/burning_mode.h"
#include "nav/burning_mode/burning_mode_patgen.h"
#include "u_drv_cust.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define PATGEN_DBG_HEADER   "[BURNING_MODE_PATGEN] "

typedef struct _BURNING_MODE_PATGAEN_T
{
    BOOL     b_plane_inited;
    BOOL     b_active;

    HANDLE_T h_ptgn_plane;
    HANDLE_T h_ptgn_view;
    HANDLE_T h_ptgn_view_2;
    HANDLE_T h_ptgn_surf;
    HANDLE_T h_ptgn_surf_2;


    UINT16   ui2_ptgn_screen_w;
    UINT16   ui2_ptgn_screen_h;
    UINT32   ui4_ptgn_viewport;
    UINT32   ui4_ptgn_viewport_2;
    UINT8    ui1_ptgn_plane_id;
} BURNING_MODE_PATGAEN_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static BURNING_MODE_PATGAEN_T t_g_burning_mode_ptgn = {0};

static UINT8 ui1_idx = 0;
static UINT8 ui1_counter = 0;

HANDLE_T h_g_burning_mode_rc_iom = NULL_HANDLE;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
INT32 burning_mode_ptgn_rc_key_monitor(VOID);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _burning_mode_init_pat_plane
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
static INT32 _burning_mode_init_pat_plane(VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    UINT8               ui1_i;
    INT32               i4_ret;
    UINT16              ui2_plane_count;
    UINT32              ui4_gui_idx;
    GL_HSCREEN_T        h_screen;
    GL_SCREEN_STATUS_T  t_src_status;
    GL_PLANE_CAPS_T     t_plane_caps;

    /* Open screen*/
    i4_ret = c_gl_screen_open(SN_PRES_MAIN_DISPLAY, NULL, NULL, &h_screen);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_screen_open() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, h_screen = 0x%x.\r\n", __FUNCTION__, h_screen));

    do
    {
        /* Get screen capability. */
        //i4_ret = c_gl_screen_get_status(h_screen, &t_src_status);
        i4_ret = c_gl_screen_get_panel_size(h_screen, &t_src_status.ui2_width, &t_src_status.ui2_height);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_screen_get_status() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }

        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_screen_get_status:ui2_width = %d, ui2_height = %d\r\n", __FUNCTION__, t_src_status.ui2_width, t_src_status.ui2_height));

        #if defined(TPV_2K19_BURNING_MODE) && defined(TPV_BURNING_MODE_4K)
        pt_this->ui2_ptgn_screen_w = t_src_status.ui2_width;
        pt_this->ui2_ptgn_screen_h = t_src_status.ui2_height;
        #else
        pt_this->ui2_ptgn_screen_w = 1920;
        pt_this->ui2_ptgn_screen_h = 1080;
        #endif

        /* Find a suit plane for image*/
        i4_ret = c_gl_plane_num(&ui2_plane_count);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_num() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_num = %d.\r\n", __FUNCTION__, ui2_plane_count));

        ui4_gui_idx = a_util_get_default_osd_plane_index();
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, a_util_get_default_osd_plane_index = %d.\r\n", __FUNCTION__, ui4_gui_idx));
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
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_enum(%d) failed. i4_ret = %d.\r\n", __FUNCTION__, ui1_i, i4_ret));
                i4_ret = NAVR_FAIL;
                break;
            }
                
            /* Check capability. */
            if(((0x00000001 << GL_COLORMODE_ARGB_D8888) & t_plane_caps.ui4_cm_caps) && 
                ((0x00000001 << 1) & t_plane_caps.ui4_z_mask))
            {
                /*found*/
                i4_ret = NAVR_OK;
                break;
            }
        }

        if(ui1_i >= ui2_plane_count || NAVR_OK != i4_ret)   /*not found or error*/
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, Not found suit plane or error.\r\n", __FUNCTION__));
            i4_ret = NAVR_FAIL;
            break;
        }

        //#ifdef APP_SUPPORT_4K2K
        //ui1_i = 3;
        //#endif
        
        i4_ret = c_gl_plane_open(h_screen, ui1_i, &pt_this->h_ptgn_plane);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_open(%d) failed. i4_ret = %d.\r\n", __FUNCTION__, ui1_i, i4_ret));
            pt_this->h_ptgn_plane = NULL_HANDLE;
            i4_ret = NAVR_FAIL;
            break;
        }

        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, burning mode plane = %d.\r\n", __FUNCTION__, ui1_i));

        i4_ret = c_gl_plane_link(pt_this->h_ptgn_plane, h_screen, TRUE);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_link() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = NAVR_OK;

    } while(0);

    if(h_screen)
    {
        i4_ret = c_gl_obj_free(h_screen);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_obj_free() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        }
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _deinit_test_pat_plane
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
static INT32 _burning_mode_deinit_pat_plane (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32 i4_ret = NAVR_OK;

    if (pt_this->h_ptgn_plane)
    {
        i4_ret = c_gl_obj_free(pt_this->h_ptgn_plane);
        if(GLR_OK != i4_ret)
        {
            i4_ret = NAVR_FAIL;
        }
        else
        {
            i4_ret = NAVR_OK;
        }

        pt_this->h_ptgn_plane = NULL_HANDLE;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_init_pat_view
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
static INT32 _burning_mode_init_pat_view (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32 i4_ret = NAVR_OK;

    /* create view */
    i4_ret = c_gl_view_create(pt_this->ui2_ptgn_screen_w,
                              pt_this->ui2_ptgn_screen_h, 
                              TRUE,
                              &pt_this->h_ptgn_view);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_view_create() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        i4_ret = NAVR_FAIL;
    }
    else
    {
        i4_ret = NAVR_OK;
    }

    i4_ret = c_gl_view_create(pt_this->ui2_ptgn_screen_w,
                              pt_this->ui2_ptgn_screen_h, 
                              TRUE,
                              &pt_this->h_ptgn_view_2);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_view_create() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        i4_ret = NAVR_FAIL;
    }
    else
    {
        i4_ret = NAVR_OK;
    }

    DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, ui2_ptgn_screen_w = %d, ui2_ptgn_screen_h = %d\r\n", __FUNCTION__, pt_this->ui2_ptgn_screen_w, pt_this->ui2_ptgn_screen_h));
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_deinit_pat_view
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
static INT32 _burning_mode_deinit_pat_view (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32 i4_ret = NAVR_OK;

    if (pt_this->h_ptgn_view)
    {
        /* free view */
        i4_ret = c_gl_obj_free (pt_this->h_ptgn_view);
        if(GLR_OK != i4_ret)
        {
            i4_ret = NAVR_FAIL;
        }
        else
        {
            i4_ret = NAVR_OK;
        }

        pt_this->h_ptgn_view = NULL_HANDLE;
    }

    if (pt_this->h_ptgn_view_2)
    {
        /* free view */
        i4_ret = c_gl_obj_free (pt_this->h_ptgn_view_2);
        if(GLR_OK != i4_ret)
        {
            i4_ret = NAVR_FAIL;
        }
        else
        {
            i4_ret = NAVR_OK;
        }

        pt_this->h_ptgn_view_2 = NULL_HANDLE;
    }
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_init_pat_disp_res
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
static INT32 _burning_mode_init_pat_disp_res (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32                       i4_ret;
    GL_SURFACE_DESC_T           t_surf_descr;
    GL_DISPLAY_OPT_T            t_dsp_opt;
    GL_POINT_T                  t_screen_offset = {0};

    c_memset(&t_surf_descr, 0, sizeof(GL_SURFACE_DESC_T));
    c_memset(&t_dsp_opt, 0, sizeof(GL_DISPLAY_OPT_T));

    do
    {
        /*set the plane order*/
        i4_ret = c_gl_plane_reorder(pt_this->h_ptgn_plane, GL_REORDER_ABSOLUTE, 0);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_reorder() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, ui2_ptgn_screen_w = %d, ui2_ptgn_screen_h = %d\r\n", __FUNCTION__, pt_this->ui2_ptgn_screen_w, pt_this->ui2_ptgn_screen_h));

        /*surface setting*/
        t_surf_descr.ui4_width  = pt_this->ui2_ptgn_screen_w;
        t_surf_descr.ui4_height = pt_this->ui2_ptgn_screen_h;
        t_surf_descr.e_clrmode  = GL_COLORMODE_ARGB_D8888;

        //t_surf_descr.b_video_only = TRUE;
        /*create surface*/
        i4_ret = c_gl_surface_create_from_fbm(&t_surf_descr, &pt_this->h_ptgn_surf);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_surface_create_from_vdp() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));

            pt_this->h_ptgn_surf = NULL_HANDLE;
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = c_gl_surface_create_from_fbm(&t_surf_descr, &pt_this->h_ptgn_surf_2);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_surface_create_from_vdp() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));

            pt_this->h_ptgn_surf_2 = NULL_HANDLE;
            i4_ret = NAVR_FAIL;
            break;
        }
        

        /*viewport setting*/
        t_dsp_opt.e_flag          = GL_DISP_OPT_POSITION | GL_DISP_OPT_BLEND_OPTION | GL_DISP_OPT_ALPHA;
        t_dsp_opt.e_blend_option  = GL_BLEND_OPT_PIXEL;
        t_dsp_opt.ui1_alpha       = 255;
        t_dsp_opt.t_pos           = t_screen_offset;

        /*create viewport*/
        i4_ret = c_gl_view_create_viewport (pt_this->h_ptgn_view, 
                                            pt_this->h_ptgn_surf, 
                                            &t_dsp_opt,
                                            &pt_this->ui4_ptgn_viewport);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_view_create_viewport() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
    
            pt_this->ui4_ptgn_viewport = 0;
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = c_gl_view_create_viewport (pt_this->h_ptgn_view_2, 
                                            pt_this->h_ptgn_surf_2, 
                                            &t_dsp_opt,
                                            &pt_this->ui4_ptgn_viewport_2);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_view_create_viewport() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
    
            pt_this->ui4_ptgn_viewport = 0;
            i4_ret = NAVR_FAIL;
            break;
        }
        
        i4_ret = NAVR_OK;

    } while (0);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_deinit_pat_disp_res
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
static INT32 _burning_mode_deinit_pat_disp_res (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32 i4_ret = NAVR_OK;

    do
    {
        i4_ret = c_gl_view_delete_viewport(pt_this->h_ptgn_view, pt_this->ui4_ptgn_viewport);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_view_delete_viewport() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
    
            pt_this->ui4_ptgn_viewport = 0;
            i4_ret = NAVR_FAIL;
            break;
        }

        if (pt_this->h_ptgn_surf)
        {
            i4_ret = c_gl_obj_free (pt_this->h_ptgn_surf);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_obj_free(pt_this->h_ptgn_surf) failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                i4_ret = NAVR_FAIL;
                break;
            }

            pt_this->h_ptgn_surf = NULL_HANDLE;
        }

        
        if (pt_this->h_ptgn_surf_2)
        {
            i4_ret = c_gl_obj_free (pt_this->h_ptgn_surf_2);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_obj_free(pt_this->h_ptgn_surf) failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                i4_ret = NAVR_FAIL;
                break;
            }

            pt_this->h_ptgn_surf_2 = NULL_HANDLE;
        }


        i4_ret = NAVR_OK;

    } while (0);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_link_pat_plane_view
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
static INT32 _burning_mode_link_pat_plane_view (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32 i4_ret = NAVR_OK;
    c_gl_plane_set_alpha(pt_this->h_ptgn_plane,0xFF);
    i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_unlink_pat_plane_view
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
static INT32 _burning_mode_unlink_pat_plane_view (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32 i4_ret = NAVR_OK;
    
    i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, (GL_HVIEW_T)NULL, TRUE);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    c_gl_plane_set_alpha(pt_this->h_ptgn_plane,0x00);
    c_gl_plane_clear(pt_this->h_ptgn_plane);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_init_pat_second_osd
 *       
 * Description: 
 *        
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *            
 ----------------------------------------------------------------------------*/
static INT32 _burning_mode_init_pat_second_osd(VOID)
{
    INT32   i4_ret = NAVR_OK;

    do
    {
        i4_ret = _burning_mode_init_pat_plane ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_init_pat_plane() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        i4_ret = _burning_mode_init_pat_view ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_init_pat_view() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        i4_ret = _burning_mode_init_pat_disp_res ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_init_pat_disp_res() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        i4_ret = _burning_mode_link_pat_plane_view ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_link_pat_plane_view() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        i4_ret = NAVR_OK;

    }while(0);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_deinit_pat_second_osd
 *       
 * Description: 
 *        
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *            
 ----------------------------------------------------------------------------*/
static INT32 _burning_mode_deinit_pat_second_osd(VOID)
{
    INT32   i4_ret = NAVR_OK;

    do
    {
        i4_ret = _burning_mode_unlink_pat_plane_view ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_unlink_pat_plane_view() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }  

        i4_ret = _burning_mode_deinit_pat_disp_res ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_deinit_pat_disp_res() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }  
    
        i4_ret = _burning_mode_deinit_pat_view ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_deinit_pat_view() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }  
    
        i4_ret = _burning_mode_deinit_pat_plane ();
        if(i4_ret != NAVR_OK)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"_burning_mode_deinit_pat_plane() failed. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        i4_ret = NAVR_OK;

    }while(0);
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_reorder_pat_plane
 *
 * Description: 
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/ 
#if 0
static INT32 _burning_mode_reorder_pat_plane(BOOL b_show)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32   i4_ret = NAVR_OK;

    if(b_show)
    {
        i4_ret = c_gl_plane_reorder(pt_this->h_ptgn_plane, GL_REORDER_ABSOLUTE, 0);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"c_gl_plane_reorder() failed. i4_ret = %d.\r\n", i4_ret));
            return NAVR_FAIL;
        }  
    }
    else
    {
        i4_ret = c_gl_plane_reorder(pt_this->h_ptgn_plane, GL_REORDER_ABSOLUTE, 1);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"c_gl_plane_reorder() failed. i4_ret = %d.\r\n", i4_ret));
            return NAVR_FAIL;
        } 
    }

    return NAVR_OK;
}
#endif


//extern INT32 factory_view_display_factory_info_char( CHAR* s_text );
//extern INT32 factory_view_show( VOID );
/*----------------------------------------------------------------------------
* Name: _burning_mode_draw_pat_frame_data
*
* Description: set panel pixel buff about pattern number.
*
* Inputs:
*
* Outputs:
*
* Returns: 
*           
----------------------------------------------------------------------------*/
static INT32 _burning_mode_draw_pat_frame_data (HANDLE_T h_surf_buf, BURNING_MODE_PATTERN_T t_ptn_sel)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32          i4_ret = NAVR_OK;
    GL_COLOR_T     t_empty_clr = {255, {0}, {0}, {0}};
    GL_LOCK_INFO_T t_lock_info;
    UINT32         ui4_i, ui4_j;
    UINT32*        pui4_fbm = NULL;

//	GL_HSCREEN_T       h_screen;
//    GL_SCREEN_STATUS_T t_src_status;
	UINT16             ui2_l_screen_w = 0;
	UINT16             ui2_l_screen_h = 0;

#if 0
    /* Open screen*/
    i4_ret = c_gl_screen_open(SN_PRES_MAIN_DISPLAY, NULL, NULL, &h_screen);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_screen_open() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, h_screen = 0x%x.\r\n", __FUNCTION__, h_screen));
#endif

    do
    {
#if 0
        /* Get screen capability. */
        i4_ret = c_gl_screen_get_status(h_screen, &t_src_status);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_screen_get_status() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }
#endif

        ui2_l_screen_w = pt_this->ui2_ptgn_screen_w;
        ui2_l_screen_h = pt_this->ui2_ptgn_screen_h;

        i4_ret = c_gl_surface_fill(h_surf_buf, &t_empty_clr, GL_SYNC);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_surface_fill() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = c_gl_surface_lock (h_surf_buf, NULL, GL_SYNC, &t_lock_info);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_surface_lock() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }

        pui4_fbm = (UINT32*)t_lock_info.at_subplane[0].pv_bits;

        DBG_LOG_PRINT((PATGEN_DBG_HEADER"Screen resulotion: W:%d, H:%d\n", ui2_l_screen_w, ui2_l_screen_h));


        switch(t_ptn_sel)
        {
            case BURNING_MODE_PAT_H_LINE:
            {
                UINT16 ui2_tmp = 0;

                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    ui2_tmp = ui4_i%2;
                    if (ui2_tmp)
                    {
                        ui2_tmp = 255;
                    }
                    else
                    {
                        ui2_tmp = 0;
                    }

                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, ui2_tmp, ui2_tmp, ui2_tmp);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_V_LINE:
            {
                UINT16 ui2_tmp = 0;

                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                	pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        ui2_tmp = ui4_j%2;
                        if (ui2_tmp)
                        {
                            ui2_tmp = 255;
                        }
                        else
                        {
                            ui2_tmp = 0;
                        }
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, ui2_tmp, ui2_tmp, ui2_tmp);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_GREEN:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                	pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 0, 255, 0);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_BLUE:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                	pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] = GL_COLOR_ARGB8888(255, 0, 0, 255);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_RED:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                	pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] = GL_COLOR_ARGB8888(255, 255, 0, 0);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_WHITE:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                	pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 255, 255, 255);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_BLACK:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 0, 0, 0);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_MAGENTA:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 255, 0, 255);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_CYAN:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 0, 255, 255);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_YELLOW:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 255, 255, 0);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_W192G:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 192, 192, 192);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_W128G:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 128, 128, 128);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_W64G:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 64, 64, 64);
                    }
                }
            }
            break;

            case BURNING_MODE_PAT_W32G:
            {
                for (ui4_i = 0; ui4_i < ui2_l_screen_h; ui4_i++)
                {
                    pui4_fbm = (UINT32*)((UINT8*)t_lock_info.at_subplane[0].pv_bits + ui4_i * t_lock_info.at_subplane[0].ui4_pitch);
                    for (ui4_j = 0; ui4_j < ui2_l_screen_w; ui4_j++)
                    {
                        pui4_fbm[ui4_j] =  GL_COLOR_ARGB8888(255, 32, 32, 32);
                    }
                }
            }
            break;
            
            default:
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, Not support pattern:%d \n", __FUNCTION__, t_ptn_sel));
                break;
        }
        i4_ret = c_gl_surface_unlock (h_surf_buf, NULL);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_surface_unlock() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = NAVR_OK;

    } while (0);

#if 0
    if (h_screen)
    {
        i4_ret = c_gl_obj_free(h_screen);
        if(GLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_obj_free() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        }
    }
#endif

    return i4_ret;
}
#if 0
/*----------------------------------------------------------------------------
* Name: _burning_mode_copy_pat_data_from_buf
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
static INT32 _burning_mode_copy_pat_data_from_buf(HANDLE_T  h_surf, HANDLE_T h_surf_buf)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32       i4_ret = NAVR_OK;

#if 0
    GL_COLOR_T  t_empty_clr = {255, {0}, {0}, {0}};

    i4_ret = c_gl_surface_fill(pt_this->h_ptgn_surf, &t_empty_clr, GL_SYNC);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_surface_fill() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif

    i4_ret = c_gl_surface_blt(h_surf,
                              h_surf_buf,
                              0,
                              0,
                              0,
                              0,
                              pt_this->ui2_ptgn_screen_w,
                              pt_this->ui2_ptgn_screen_h,
                              255,
                              GL_SRC_OVER);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_surface_blt() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_init_plane
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
INT32 burning_mode_ptgn_init_plane (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32   i4_ret = NAVR_OK;

    if (TRUE == pt_this->b_plane_inited)
    {
        return NAVR_OK;
    }

    i4_ret = _burning_mode_init_pat_second_osd();
    if (NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_init_pat_second_osd() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
    }
    else
    {
        pt_this->b_plane_inited = TRUE;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_deinit_plane
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
INT32 burning_mode_ptgn_deinit_plane (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;

    INT32   i4_ret = NAVR_OK;

    if (FALSE == pt_this->b_plane_inited)
    {
        return NAVR_OK;
    }

    i4_ret = _burning_mode_deinit_pat_second_osd();
    if (NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_deinit_pat_second_osd() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
    }
    else
    {
        pt_this->b_plane_inited = FALSE;
    }
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_pattern_run
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
INT32 burning_mode_ptgn_pattern_run (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;
    INT32 i4_ret = NAVR_OK;

    if (FALSE == pt_this->b_plane_inited)
    {
        burning_mode_ptgn_init_plane();
    }

    if(ui1_idx == 0)
    {   
        // Timer 2 sec repeat.
        if(ui1_counter>0 && ui1_counter < 10)
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, 0<ui1_counter<10 \n", __FUNCTION__, __LINE__)); 
            ui1_counter++;
            return 0;
        }
        else if(ui1_counter >= 10)
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, pat V-line \n", __FUNCTION__, __LINE__));
            ui1_idx = 1; //next pat V-line
            ui1_counter = 0;
        }
        else //ui1_idx =0; ui1_counter = 0
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, pat H-line \n", __FUNCTION__, __LINE__));
            ui1_counter++;
        }
    }

    do
    {
       // i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, t_ptn_sel);
        if(ui1_idx == 0)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_H_LINE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }
            
            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
       }
       if(ui1_idx == 1)
       {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_V_LINE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 2; //next pat white
        }
        else if(ui1_idx == 2)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_WHITE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
            
            ui1_idx = 3; //next pat black
        }
        else if(ui1_idx == 3)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_BLACK);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 0; // Back to H-pat
        }


 
#if 0 
        i4_ret = _burning_mode_copy_pat_data_from_buf(pt_this->h_ptgn_surf, pt_this->h_ptgn_surf_2);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_copy_pat_data_from_buf() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
#if 0
        i4_ret = _burning_mode_reorder_pat_plane(TRUE);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_reorder_pat_plane() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
        i4_ret = NAVR_OK;

    } while(0);

    //#ifndef APP_SUPPORT_4K2K
    // Due to CC panel on MT5581P, need to enable under "no singal". 
    if(pt_this->b_active == FALSE){
        c_gl_plane_enable(pt_this->h_ptgn_plane, TRUE);
    }
    //#endif
    
    pt_this->b_active = TRUE;
    
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_pattern_stop
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
INT32 burning_mode_ptgn_pattern_stop (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;
    INT32 i4_ret = 0;

    DBG_LOG_PRINT(("\n[TPV_FAC] %s Line: %d, Active:%d\n", __FUNCTION__, __LINE__, pt_this->b_active));
    
    if(pt_this->b_active == FALSE){
        return 0;
    }
    
    i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, (GL_HVIEW_T)NULL, TRUE);
    if(GLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
    
    ui1_idx = 0;
    ui1_counter = 0;

    pt_this->b_active = FALSE;
    
    burning_mode_ptgn_deinit_plane();
    return 0;
}

/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_oled_pattern_run
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
INT32 burning_mode_ptgn_oled_pattern_run (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;
    INT32 i4_ret = NAVR_OK;

    if (FALSE == pt_this->b_plane_inited)
    {
        burning_mode_ptgn_init_plane();
    }

    if(ui1_idx == 0)
    {   
        // Timer 2 sec repeat.
        if(ui1_counter>0 && ui1_counter < 10)
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, 0<ui1_counter<10 \n", __FUNCTION__, __LINE__)); 
            ui1_counter++;
            return 0;
        }
        else if(ui1_counter >= 10)
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, pat CYAN \n", __FUNCTION__, __LINE__));
            ui1_idx = 1; //next pat
            ui1_counter = 0;
        }
        else //ui1_idx =0; ui1_counter = 0
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, pat MAGENTA \n", __FUNCTION__, __LINE__));
            ui1_counter++;
        }
    }

    do
    {
       // i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, t_ptn_sel);
        if(ui1_idx == 0)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_MAGENTA);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }
            
            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
       }
       if(ui1_idx == 1)
       {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_CYAN);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 2; //next pat Yellow
        }
        else if(ui1_idx == 2)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_YELLOW);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
            
            ui1_idx = 3; //next pat white
        }
        else if(ui1_idx == 3)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_WHITE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 4; // next pat black
        }
        else if(ui1_idx == 4)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_BLACK);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 0; // Back to H-pat
        }


 
#if 0 
        i4_ret = _burning_mode_copy_pat_data_from_buf(pt_this->h_ptgn_surf, pt_this->h_ptgn_surf_2);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_copy_pat_data_from_buf() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
#if 0
        i4_ret = _burning_mode_reorder_pat_plane(TRUE);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_reorder_pat_plane() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
        i4_ret = NAVR_OK;

    } while(0);

    //#ifndef APP_SUPPORT_4K2K
    // Due to CC panel on MT5581P, need to enable under "no singal". 
    if(pt_this->b_active == FALSE){
        c_gl_plane_enable(pt_this->h_ptgn_plane, TRUE);
    }
    //#endif
    
    pt_this->b_active = TRUE;
    
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_oled_pattern_run
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
INT32 burning_mode_ptgn_LG_oled_pattern_run (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;
    INT32 i4_ret = NAVR_OK;

    if (FALSE == pt_this->b_plane_inited)
    {
        burning_mode_ptgn_init_plane();
    }


    DBG_LOG_PRINT(("\033[01;31m [BURNING_MODE] \033[m %s next pat: %d\n", __FUNCTION__, ui1_idx));
    DBG_LOG_PRINT(("\033[01;31m [BURNING_MODE] \033[m %s ui1_counter: %d\n", __FUNCTION__, ui1_counter));
    // Timer 5 sec repeat.
    if(ui1_counter > 0)
    {
        ui1_counter--;
        return 0;
    }


    do
    {
       // i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, t_ptn_sel);
        if(ui1_idx == 0)  // W255g / White
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_WHITE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }
            
            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
            ui1_idx = 1; //next pat W192G
            ui1_counter = 1; // 10 sec
       }
       if(ui1_idx == 1) // W192g
       {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_W192G);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 2; //next pat W128G
            ui1_counter = 1; // 10 sec
        }
        else if(ui1_idx == 2) // W128g
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_W128G);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
            
            ui1_idx = 3; //next pat W64G
            ui1_counter = 1; // 10 sec
        }
        else if(ui1_idx == 3) // W64g
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_W64G);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 4; // next pat W32G
            ui1_counter = 1; // 10 sec
        }
        else if(ui1_idx == 4) // W32g
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_W32G);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 5; // next to R255g
            ui1_counter = 1; // 10 sec
        }
        else if(ui1_idx == 5) // R255g
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_RED);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 6; // next to G255g
            ui1_counter = 3; // 20 sec
        }
        else if(ui1_idx == 6) // G255g
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_GREEN);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 7; // next to B255g
            ui1_counter = 0; // 5 sec
        }
        else if(ui1_idx == 7) // B255g
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_BLUE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 8; // next to Y255g
            ui1_counter = 0; // 5 sec
        }
        else if(ui1_idx == 8) // Y255g
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_YELLOW);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 9; // Back to Black
            ui1_counter = 2; // 15 sec
        }
        else if(ui1_idx == 9) // Black
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_BLACK);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 0; // Back to W255g
            ui1_counter = 0; // 5 sec
        }


 
#if 0 
        i4_ret = _burning_mode_copy_pat_data_from_buf(pt_this->h_ptgn_surf, pt_this->h_ptgn_surf_2);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_copy_pat_data_from_buf() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
#if 0
        i4_ret = _burning_mode_reorder_pat_plane(TRUE);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_reorder_pat_plane() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
        i4_ret = NAVR_OK;

    } while(0);

    //#ifndef APP_SUPPORT_4K2K
    // Due to CC panel on MT5581P, need to enable under "no singal". 
    if(pt_this->b_active == FALSE){
        c_gl_plane_enable(pt_this->h_ptgn_plane, TRUE);
    }
    //#endif
    
    pt_this->b_active = TRUE;
    
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_pattern_run_old
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
INT32 burning_mode_ptgn_pattern_run_old (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;
    INT32 i4_ret = NAVR_OK;

    //DBG_LOG_PRINT(("\n[TPV_FAC] %s Line: %d\n", __FUNCTION__, __LINE__));
    
    if (FALSE == pt_this->b_plane_inited)
    {
        burning_mode_ptgn_init_plane();
    }
    
    do
    {
       // i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, t_ptn_sel);
        if(ui1_idx == 0)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_RED);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }
            
            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
            ui1_idx = 1; //next pat Green
       }
       if(ui1_idx == 1)
       {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_GREEN);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 2; //next pat Blue
        }
        else if(ui1_idx == 2)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf, BURNING_MODE_PAT_BLUE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }
            
            ui1_idx = 3; //next pat black
        }
        else if(ui1_idx == 3)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_BLACK);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 4; // next pat White
        }
        else if(ui1_idx == 4)
        {
            i4_ret = _burning_mode_draw_pat_frame_data(pt_this->h_ptgn_surf_2, BURNING_MODE_PAT_WHITE);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_draw_pat_frame_data() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                break;
            }

            i4_ret = c_gl_plane_flip(pt_this->h_ptgn_plane, pt_this->h_ptgn_view_2, TRUE);
            if(GLR_OK != i4_ret)
            {
                DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, c_gl_plane_flip() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
                return NAVR_FAIL;
            }

            ui1_idx = 0; // Back to H-pat
        }


 
#if 0 
        i4_ret = _burning_mode_copy_pat_data_from_buf(pt_this->h_ptgn_surf, pt_this->h_ptgn_surf_2);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_copy_pat_data_from_buf() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
#if 0
        i4_ret = _burning_mode_reorder_pat_plane(TRUE);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT((PATGEN_DBG_HEADER"%s, _burning_mode_reorder_pat_plane() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
            break;
        }
#endif
        i4_ret = NAVR_OK;

    } while(0);

    //#ifndef APP_SUPPORT_4K2K
    // Due to CC panel on MT5581P, need to enable under "no singal". 
    if(pt_this->b_active == FALSE){
        c_gl_plane_enable(pt_this->h_ptgn_plane, TRUE);
    }
    //#endif
    
    pt_this->b_active = TRUE;
    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_vcom_pattern_run
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
INT32 burning_mode_ptgn_vcom_pattern_run (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;
    INT32 i4_ret = NAVR_OK;
    DRV_CUSTOM_VCOM_PATTERN_T t_info;
    BOOL b_support = a_cfg_cust_get_support_local_dimming();
    static BOOL b_rc_monitor_init = FALSE;

    if(b_rc_monitor_init == FALSE)
    {
       i4_ret = burning_mode_ptgn_rc_key_monitor();
       TPV_LOG_ON_FAIL(i4_ret);
       b_rc_monitor_init = TRUE;
    }
    
    c_memset(&t_info, 0, sizeof(t_info));
    
    UINT16 _patttern_white[]=
    {
        1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
        1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
        1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
        1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
    };

    UINT16 _patttern_black[]=
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    UINT16 _patttern_vstri[]=
    {
        1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0,
        1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0,
        1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0,
        1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0, 1023, 1023, 1023, 0, 0, 0,
    };

    UINT16 _patttern_hstri[]=
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
    };
    
    if(ui1_idx == 0)
    {   
        // Timer 2 sec repeat.
        if(ui1_counter>0 && ui1_counter < 10)
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, 0<ui1_counter<10 \n", __FUNCTION__, __LINE__)); 
            ui1_counter++;
            return 0;
        }
        else if(ui1_counter >= 10)
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, pat V-line \n", __FUNCTION__, __LINE__));
            ui1_idx = 1; //next pat V-line
            ui1_counter = 0;
        }
        else //ui1_idx =0; ui1_counter = 0
        {
            DBG_LOG_PRINT(("\n[BURNING_MODE] %s Line: %d, pat H-line \n", __FUNCTION__, __LINE__));
            ui1_counter++;
        }
    }

    if(ui1_idx == 0)
    {
        t_info.bEnable = TRUE;
        c_memcpy(t_info.u2Tbl, _patttern_hstri, sizeof(_patttern_hstri));
    }
    if(ui1_idx == 1)
    {
        t_info.bEnable = TRUE;
        c_memcpy(t_info.u2Tbl, _patttern_vstri, sizeof(_patttern_vstri));

        ui1_idx = 2; //next pat white
    }
    else if(ui1_idx == 2)
    {
        t_info.bEnable = TRUE;
        c_memcpy(t_info.u2Tbl, _patttern_white, sizeof(_patttern_white));

        ui1_idx = 3; //next pat black
    }
    else if(ui1_idx == 3)
    {
        t_info.bEnable = TRUE;
        c_memcpy(t_info.u2Tbl, _patttern_black, sizeof(_patttern_black));

        ui1_idx = 0; // Back to H-pat
    }
    
    pt_this->b_active = TRUE;
        
    if(b_support == TRUE) // off active full array
    {
        i4_ret = VIZIO_EXTREME_BLACK_ENGINE_D_SET((UINT16)0);
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = VIZIO_BACKLIGHT_CONTROL_D_SET((UINT16)0);
        TPV_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = a_cfg_cust_drv_set_vcom_pattern(&t_info,sizeof(t_info));
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_vcom_pattern_stop
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
INT32 burning_mode_ptgn_vcom_pattern_stop (VOID)
{
    BURNING_MODE_PATGAEN_T *pt_this = &t_g_burning_mode_ptgn;
    INT32 i4_ret = NAVR_OK;
    DRV_CUSTOM_VCOM_PATTERN_T t_info;
    BOOL b_support = a_cfg_cust_get_support_local_dimming();
    
    c_memset(&t_info, 0, sizeof(t_info));
    DBG_LOG_PRINT(("\n[TPV_FAC] %s Line: %d\n", __FUNCTION__, __LINE__));
    
    t_info.bEnable = FALSE;
    i4_ret = a_cfg_cust_drv_set_vcom_pattern(&t_info,sizeof(t_info));
    TPV_LOG_ON_FAIL(i4_ret);

    ui1_idx = 0;
    ui1_counter = 0;

    pt_this->b_active = FALSE;

    if(b_support == TRUE) // recover active full array
    {
        /* Smart Dimming */
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
        TPV_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        /* DCR and Lightsensor use the same process, so only update dcr. */
        i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));
        TPV_LOG_ON_FAIL(i4_ret);      
    }

    
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _burning_mode_ptgn_iom_nfy_fct
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
static VOID _burning_mode_ptgn_iom_nfy_fct(
    VOID*               pv_nfy_tag,
    IOM_NFY_COND_T      e_nfy_cond,
    UINT32              ui4_evt_code,
    UINT32              ui4_data)
{
    INT32 i4_ret = 0;
    
    if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        //DBG_LOG_PRINT(("\n[TPV_FAC] %s Line: %d\n", __FUNCTION__, __LINE__));
        if (IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_MUTE
        || IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_VOL_UP
        || IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_VOL_DOWN
        || IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_INPUT_SRC
        || IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_PRG_INFO)
        {
            //DBG_LOG_PRINT(("\n[TPV_FAC] %s Line: %d\n", __FUNCTION__, __LINE__));
            i4_ret = burning_mode_ptgn_vcom_pattern_stop();
            TPV_LOG_ON_FAIL(i4_ret);
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: burning_mode_ptgn_rc_key_monitor
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
INT32 burning_mode_ptgn_rc_key_monitor(VOID)
{
    INT32 i4_ret = 0;

    IRRC_SETTING_T  t_irrc_setting;

    //DBG_LOG_PRINT(("\n[TPV_FAC] %s Line: %d\n", __FUNCTION__, __LINE__));
    
    /* IOM Init */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL ;
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
    t_irrc_setting.b_notify_raw_data        = TRUE;                  /* request to notify anyway. */

    i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                         IOM_DEV_ID_ANY,
                         NULL,
                         (VOID*) & t_irrc_setting,
                         NULL,
                         _burning_mode_ptgn_iom_nfy_fct,
                         &h_g_burning_mode_rc_iom);
    TPV_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}


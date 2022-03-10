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
 * $RCSfile: burning_mode_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Chris Kuo $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_bdr_common.h"

#include "c_wgl.h"

#include "nav/burning_mode/burning_mode.h"
#include "res/nav/burning_mode/burning_mode_custom.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                          TRUE

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static GL_COLOR_T    at_pattern[] = BURNING_MODE_COLOR_TABLE;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
// yuan 2012 0703 vvvvv
extern INT32 a_cfg_custom_set_fac_aging_mode (UINT16*  pui2_val, SIZE_T z_size);
extern INT32 a_cfg_custom_get_fac_aging_mode (UINT16*  pui2_val, SIZE_T z_size);//nicholas@20130304
extern UINT8 _fac_get_burning_mode_flag(void);

//static UINT8 i1_Burning_pattern; 

// yuan 2012 0703 ^^^^^


/*-----------------------------------------------------------------------------
 * Name
 *      burning_mode_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 burning_mode_view_init(
                    BURNING_MODE_T*                     pt_this,
                    HANDLE_T                            h_canvas
                    )
{
    BURNING_MODE_VIEW_T*   pt_view = & pt_this->t_view;
    INT32                  i4_ret;
    GL_RECT_T              t_rect;
    UINT32                 ui4_width;
    UINT32                 ui4_height;

    /* Get canvas size. */
    i4_ret = nav_get_ui_canvas_size (& ui4_width,
                                     & ui4_height);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create frame. */
    SET_RECT_BY_SIZE (& t_rect,
                      0,
                      0,
                      (INT32)ui4_width,
                      (INT32)ui4_height);

    i4_ret = c_wgl_create_widget (h_canvas,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  _burning_mode_frame_nfy_fct,
                                  255,
                                  (VOID*) WGL_STL_GL_NO_IMG_UI,
                                  pt_this,
                                  & pt_view->h_frame);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Set Z-order to top-most. */
    i4_ret = c_wgl_insert (pt_view->h_frame,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Set visibility. */
    i4_ret = c_wgl_set_visibility (pt_view->h_frame,
                                   WGL_SW_HIDE);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Set default pattern index */
    pt_view->ui2_idx = 0;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      burning_mode_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 burning_mode_view_deinit(
                    BURNING_MODE_VIEW_T*         pt_view
                    )
{
    c_wgl_destroy_widget (pt_view->h_frame);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      burning_mode_view_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 burning_mode_view_show(
                    BURNING_MODE_VIEW_T*         pt_view
                    )
{
    INT32 i4_ret;

    /* Set focus. */
    i4_ret = c_wgl_set_focus (pt_view->h_frame,
                              WGL_NO_AUTO_REPAINT);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Set visibility. */
    i4_ret = c_wgl_set_visibility (pt_view->h_frame,
                                   WGL_SW_NORMAL);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Repaint. */
    i4_ret = c_wgl_repaint (pt_view->h_frame,
                            NULL,
                            IS_SYNC_REPAINT);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    nav_set_component_visible (NAV_COMP_ID_BURNING_MODE);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      burning_mode_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 burning_mode_view_hide(
                    BURNING_MODE_VIEW_T*         pt_view
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility (pt_view->h_frame,
                                   WGL_SW_HIDE);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint (pt_view->h_frame,
                            NULL,
                            IS_SYNC_REPAINT);

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      burning_mode_view_update(
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 burning_mode_view_update(              BURNING_MODE_VIEW_T* pt_view )
{
	INT32                   i4_ret;
	WGL_COLOR_INFO_T        t_clr_info;
	SIZE_T                  z_table_size = sizeof(at_pattern) / sizeof(at_pattern[0]);

	if (pt_view->ui2_idx < (UINT16)z_table_size) /* Validate index */
	{
		// FXC_Jim 20180328 vvvvv
//		SIZE_T	z_size	= sizeof(UINT16);  // yuan 2012 0719 
		UINT16  ui2_tmp;
		t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
#if 1 // yuan 2012 0719 
		ui2_tmp = _fac_get_burning_mode_flag();	
		// i1_Burning_pattern = (UINT8) ui2_tmp;
		// DBG_INFO( ("<burning_mode_view_update> _fac_get_burning_mode_flag : %d !\n",ui2_tmp ));
#else
		a_cfg_custom_get_BurningMode(&i1_Burning_pattern);	
#endif
		//Printf("a_cfg_custom_get_BurningMode (%d)\n", i1_Burning_pattern);
		if ( ui2_tmp  == 0x02 )
		{
			t_clr_info.u_color_data.t_standard.t_enable    = at_pattern [3];
			t_clr_info.u_color_data.t_standard.t_disable   = at_pattern [3];
			t_clr_info.u_color_data.t_standard.t_highlight = at_pattern [3];	 
		}
		else
		{
			t_clr_info.u_color_data.t_standard.t_enable    = at_pattern [pt_view->ui2_idx];
			t_clr_info.u_color_data.t_standard.t_disable   = at_pattern [pt_view->ui2_idx];
			t_clr_info.u_color_data.t_standard.t_highlight = at_pattern [pt_view->ui2_idx];
		}
		DBG_INFO( ("<burning_mode_view_update> _fac_get_burning_mode_flag : %d !\n",ui2_tmp ));
		DBG_INFO( ("<burning_mode_view_update> _fac_get_burning_mode_pattern : %d !\n",t_clr_info.u_color_data.t_standard.t_highlight ));
		// FXC_Jim 20180328 ^^^^^
		/* Set background color. */
		i4_ret = c_wgl_do_cmd (pt_view->h_frame,
								WGL_CMD_GL_SET_COLOR,
								WGL_PACK (WGL_CLR_BK),
								WGL_PACK (& t_clr_info));

		if (i4_ret != WGLR_OK)
		{
			return NAVR_FAIL;
		}
	}

	/* Update pattern index. */
	pt_view->ui2_idx = (UINT16)((pt_view->ui2_idx + 1) % z_table_size);

	return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
 * Name
 *      _burning_mode_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _burning_mode_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            /* Call rcu key handler. */
            burning_mode_rcu_key_handler ((UINT32) pv_param1);
        }
        break;

        default:
            break;
    }

    return c_wgl_default_msg_proc (h_widget,
                                   ui4_msg,
                                   pv_param1,
                                   pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name
 *      burning_mode_ext_rc_control_view_update
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 burning_mode_ext_rc_control_view_update(
                    BURNING_MODE_VIEW_T*         pt_view,
                    UINT16 ui2_idex
                    )
{
    INT32                   i4_ret;
    WGL_COLOR_INFO_T        t_clr_info;

    t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
        UINT16  ui2_tmp;

	 ui2_tmp = _fac_get_burning_mode_flag();	


	 if ( ui2_tmp  == 0x02 )
	 {
             t_clr_info.u_color_data.t_standard.t_enable    = at_pattern [3];
             t_clr_info.u_color_data.t_standard.t_disable   = at_pattern [3];
             t_clr_info.u_color_data.t_standard.t_highlight = at_pattern [3];	 
	 }
	 else
	 {	
    t_clr_info.u_color_data.t_standard.t_enable    = at_pattern [ui2_idex];
    t_clr_info.u_color_data.t_standard.t_disable   = at_pattern [ui2_idex];
    t_clr_info.u_color_data.t_standard.t_highlight = at_pattern [ui2_idex];
	 	}
    /* Set background color. */
    i4_ret = c_wgl_do_cmd (pt_view->h_frame,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK),
                           WGL_PACK (& t_clr_info));

    if (i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}



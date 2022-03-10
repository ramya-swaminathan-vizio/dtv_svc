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
 * $RCSfile: video_engine_multimedia.c,v $
 * $Revision: 1$
 * $Date:2017/08/16$
 * $Author:sin_fangyuan$
 *
 * Description:
 *         This is the source file for video engine.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * include files
 *---------------------------------------------------------------------------*/
#include "u_svctx.h"
#include "u_divx_drm.h"
#include "u_minfo.h"
#include "u_sm_sess_gnrc.h"

#include "c_gl.h"
#include "c_img.h"
#include "c_img_tfx.h"
#include "c_fm.h"
#include "c_fm_mfw.h"
#include "c_dt.h"
#include "c_handle.h"
#include "u_wgl_rect.h"
#include "c_wgl.h"
#include "c_scc.h"
#include "c_minfo.h"

#include "_mmp_ve_type.h"

#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "app_util/a_screen_mode.h"

#include "mmp/app/mmp_main.h"
#include "mmp/file_filter/mmp_fid.h"
#include "mmp/thumbnailmode/thumbnailmode.h"
#include "video_engine.h"
#include "video_engine_multimedia.h"


#if 1//#ifdef _MMP_VERC_DIVX
#include "res/mmp/video_engine/mmp_video_engine_rc.h"
#endif
#ifdef APP_NETWORK_SUPPORT
#include "c_fm_dlnafs.h"
#endif

#include "nav/a_navigator.h"

#if	defined(APP_NET_DLNA_SUPPORT)&&defined(APP_DMR_SUPPORT)&&defined(APP_MMP_DMR_SHOW_COVER_PICTURE_SUPPORT)
#include "mmp/dmr/mmp_dmr.h"
#endif

#ifdef APP_MMP_PVR_LAST_MEMORY_SUPPORT
#include "nav/record/a_nav_rec.h"
#include "mmp/pvr/mmp_pvr.h"
#endif

#ifdef APP_IPCC_SUPPORT
VOID video_engine_free_ipcc_path(_MMP_VE_ELMT_INFO_PTR_T pt_elmt)
{
   if (pt_elmt && pt_elmt->ui1_ipcc_num > 0)
   {
   		UINT8 ui1_i;
		for (ui1_i = 0; ui1_i < pt_elmt->ui1_ipcc_num; ui1_i++)
		{
			if (pt_elmt->ps_ipcc_path[ui1_i])
			{
				c_mem_free(pt_elmt->ps_ipcc_path[ui1_i]);
				pt_elmt->ps_ipcc_path[ui1_i] = NULL;
			}
		}
		pt_elmt->ui1_ipcc_num = 0;
   }
}

INT32 video_engine_fill_ipcc_path(_MMP_VE_ELMT_INFO_PTR_T pt_elmt)
{
	INT32               i4_ret;
	CHAR*               ps_file = NULL;
	CHAR*               ps_ext   = NULL;
	CHAR*               ps_sep;
	HANDLE_T            h_dir = NULL_HANDLE;
	FM_DIR_ENTRY_T      t_dir_entry;
	CHAR*               ps_path = NULL;
	UINT32              ui4_path_len = 0;

	if (pt_elmt == NULL || pt_elmt->ps_file_name == NULL)
	{
		return MMPR_INV_ARG;
	}
	video_engine_free_ipcc_path(pt_elmt);
	ui4_path_len = c_strlen(pt_elmt->ps_file_name)+1;
	ps_path = c_mem_alloc(ui4_path_len);
	if (ps_path == NULL)
	{
		return MMPR_BUF_NOT_ENOUGH;
	}

	do
	{
	    c_memcpy(ps_path, pt_elmt->ps_file_name, ui4_path_len);
		ps_path[ui4_path_len-1] = 0;
    	ps_sep  = c_strrchr(ps_path, '/');
	    ps_ext  = c_strrchr(ps_sep, '.');
	    if (ps_sep == NULL || ps_ext == NULL)
	    {
		   i4_ret = MMPR_INV_ARG;
		   break;
    	}
		ps_file = ps_sep+1;
	    *ps_sep = 0;/*sep path and file*/

		i4_ret = c_fm_open_dir(FM_ROOT_HANDLE, ps_path, &h_dir);
		if (i4_ret != FMR_OK || h_dir == NULL_HANDLE)
		{
			break;
		}
		ps_file = mmp_util_trim_path_prefix(ps_path, ps_file);
		ps_ext++;
		c_memset(&t_dir_entry, 0, sizeof(FM_DIR_ENTRY_T));

		while(1)
		{
			UINT32 ui4_dir_num = 0;
			BOOL   b_found = FALSE;
			CHAR*  ps_dot;
			if (pt_elmt->ui1_ipcc_num >= MAX_IPCC_NUM)
			{
				break;
			}
			i4_ret = c_fm_read_dir_entries(h_dir, &t_dir_entry, 1, &ui4_dir_num);
			if (i4_ret != FMR_OK && ui4_dir_num != 1)
			{
				break;
			}
			if (!FM_IS_FILE(t_dir_entry.t_file_info.ui4_mode))
			{
				continue;
			}
			ps_dot = mmp_util_trim_path_prefix(ps_path, t_dir_entry.s_name);
			if (c_strncmp(ps_dot, ps_file, ps_ext-ps_file) == 0)
			{
				ps_dot += ps_ext-ps_file;
				while(ps_dot)
				{
					if (c_strncasecmp(ps_dot,"xml",3) == 0 ||
	           			c_strncasecmp(ps_dot,"m4t",3) == 0 )
					{
						if (*(ps_dot+3) == 0 || *(ps_dot+3) == '.')
						{
							b_found = TRUE;
						}
					}
					ps_dot = c_strchr(ps_dot, '.');
					if (ps_dot)
					{
						ps_dot++;
					}
				}

				if (b_found)
				{
					UINT16 ui2_dir_len = c_strlen(ps_path);
					UINT16 ui2_file_len = c_strlen(t_dir_entry.s_name);
					CHAR*  ps_match = c_mem_alloc(ui2_dir_len+ui2_file_len+2);
					if (ps_match == NULL)
					{
						break;
					}
					c_memcpy(ps_match, ps_path, ui2_dir_len);
					ps_match[ui2_dir_len] = '/';
					c_memcpy(ps_match+ui2_dir_len+1, t_dir_entry.s_name, ui2_file_len+1);
					MMP_DBG_INFO(("{MMP}  match IPCC:%s\n", ps_match));
					pt_elmt->ps_ipcc_path[pt_elmt->ui1_ipcc_num] = ps_match;
					pt_elmt->ui1_ipcc_num++;
				}
			}
		}
	}while(0);

	if (h_dir != NULL_HANDLE)
	{
		i4_ret = c_fm_close(h_dir);
	}
	c_mem_free(ps_path);

	return i4_ret;
}
#endif


#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
INT32 video_engine_blank_deinit(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    )
{
    _MMP_VE_OSD_INFO_PTR_T pt_osd_info = &pt_this->t_osd_info;
    INT32 i4_ret = MMPR_OK;

    if ((NULL == pt_this) || (NULL_HANDLE == pt_osd_info->h_canvas_ex))
    {
        return MMPR_INV_ARG;
    }

    if (NULL_HANDLE != pt_osd_info->h_blank_frm)
    {
        i4_ret = c_wgl_destroy_widget_ex(pt_osd_info->h_blank_frm, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_osd_info->h_blank_frm = NULL_HANDLE;
    }

    return MMPR_OK;
}

INT32 video_engine_blank_init(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    )
{
    _MMP_VE_OSD_INFO_PTR_T pt_osd_info = &pt_this->t_osd_info;
    UINT32 ui4_canvas_width;
    UINT32 ui4_canvas_height;
    GL_RECT_T t_rect;
#ifdef _MMP_VERC_BLANK_INIT_COLOR
    GL_COLOR_T t_color_bk = { 255, { 34 }, { 68 }, { 102 } };
#else
    GL_COLOR_T t_color_bk = { 255, { 0 }, { 0 }, { 255 } };
#endif
    WGL_COLOR_INFO_T t_clr_info;
    INT32 i4_ret = MMPR_OK;

    if ((NULL == pt_this) || (NULL_HANDLE == pt_osd_info->h_canvas_ex))
    {
        return MMPR_INV_ARG;
    }

    /* Get canvas size. */
    i4_ret = c_wgl_get_canvas_size (
                    pt_osd_info->h_canvas_ex,
                    &ui4_canvas_width,
                    &ui4_canvas_height
                    );
    if (WGLR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_wgl_get_canvas_size() fail.  %s:%d %d\r\n", __FUNCTION__, __LINE__,i4_ret));
        return i4_ret;
    }

    SET_RECT_BY_SIZE (& t_rect, 0, 0, ui4_canvas_width, ui4_canvas_height);

    /* Create widget. */
    i4_ret = c_wgl_create_widget (
                    pt_osd_info->h_canvas_ex,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    & t_rect,
                    NULL,
                    255,
                    (VOID*) WGL_STL_GL_NO_IMG_UI,
                    0,
                    &pt_osd_info->h_blank_frm
                    );
    if (WGLR_OK != i4_ret)
    {
        pt_osd_info->h_blank_frm = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /* Set background color. */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_color_bk;
    t_clr_info.u_color_data.t_standard.t_disable   = t_color_bk;
    t_clr_info.u_color_data.t_standard.t_highlight = t_color_bk;

    i4_ret = c_wgl_do_cmd (
                    pt_osd_info->h_blank_frm,
                    WGL_CMD_GL_SET_COLOR,
                    WGL_PACK (WGL_CLR_BK),
                    WGL_PACK (& t_clr_info)
                    );
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_osd_info->h_blank_frm, WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (WGLR_OK == i4_ret)
    {
        return MMPR_OK;
    }

    i4_ret = video_engine_blank_deinit (pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_blank_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_blank_show(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    )
{
    _MMP_VE_OSD_INFO_PTR_T pt_osd_info = NULL;
	VSH_REGION_INFO_T      t_set_dsp_region = {0};
	SIZE_T                 z_size = sizeof(VSH_REGION_INFO_T);
    INT32                  i4_ret;

    if (NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }
	pt_osd_info = &pt_this->t_osd_info;
	/*to solve 3D/depth issue set disp to be 0 and restore back*/
	i4_ret = c_svctx_get_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_DISP_REGION,
                    (VOID*)&pt_osd_info->t_org_disp_rgn,
                    &z_size
                    );
	MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_DISP_REGION,
                    (VOID*)&t_set_dsp_region,
                    z_size
                    );
	MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_show(pt_osd_info->h_blank_frm, WGL_SW_NORMAL);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (WGLR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_blank_hide
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_blank_hide(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    )
{
    _MMP_VE_OSD_INFO_PTR_T pt_osd_info = NULL;
	SIZE_T                 z_size = sizeof(VSH_REGION_INFO_T);
    INT32                  i4_ret;

    if (NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }
	pt_osd_info = &pt_this->t_osd_info;

    i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_DISP_REGION,
                    (VOID*)&pt_osd_info->t_org_disp_rgn,
                    z_size
                    );
	MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_show(pt_osd_info->h_blank_frm, WGL_SW_HIDE);
    if (WGLR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_wgl_set_visibility() returns %d. %s:%d\n", i4_ret,__FUNCTION__, __LINE__));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}
#endif


/*----------------------------------------------------------------------------
 * Name: _mmp_ve_sbtl_set_line
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_sbtl_set_line(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_DISP_MODE_T*        pt_disp_mode      /* in  */
                    )
{
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_disp_mode))
    {
        return MMPR_INV_ARG;
    }

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SBTL_SET_TYPE_DISP_MODE,
                    (VOID*)pt_disp_mode,
                    sizeof(MM_SVC_SBTL_DISP_MODE_T)
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_ve_sbtl_set_time
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_sbtl_set_time(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_TIME_OFST_T*        pt_time_type      /* in  */
                    )
{
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_time_type))
    {
        return MMPR_INV_ARG;
    }

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SBTL_SET_TYPE_TIME_OFST,
                    (VOID*)pt_time_type,
                    sizeof(MM_SVC_SBTL_TIME_OFST_T)
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_ve_sbtl_set_font
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_sbtl_set_font(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_DISP_ATTR_T*        pt_font_type      /* in  */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_2ND_ELMT(pt_this);
    INT32 i4_ret = 0;

    if ((NULL == pt_this) ||
        (NULL == pt_elmt) ||
        (NULL == pt_font_type))
    {
        return MMPR_INV_ARG;
    }

    if (_MMP_VE_SBTL_STAT_OFF == pt_elmt->e_sbtl_stat)
    {
        i4_ret = c_svctx_generic_set_info(
                        pt_this->h_svctx_hdl,
                        pt_elmt->h_elmt_hdl,
                        SVCTX_MM_SBTL_SET_TYPE_NRML_ATTR,
                        (VOID*)pt_font_type,
                        sizeof(MM_SVC_SBTL_DISP_ATTR_T)
                        );
    }
    else
    {
        i4_ret = c_svctx_set(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_SBTL_SET_TYPE_NRML_ATTR,
                        (VOID*)pt_font_type,
                        sizeof(MM_SVC_SBTL_DISP_ATTR_T)
                        );
    }
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_ve_sbtl_set_encode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_sbtl_set_encode(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_FONT_ENC_T*         pt_encode_type    /* in  */
                    )
{
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_encode_type))
    {
        return MMPR_INV_ARG;
    }

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SBTL_SET_TYPE_FONT_ENC,
                    (VOID*)pt_encode_type,
                    sizeof(MM_SVC_SBTL_FONT_ENC_T)
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
INT32 mmp_ve_sbtl_set_show(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_SBTL_SHOW_HIDE_T*        pt_show_hide      /* in  */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    SVC_MM_SBTL_LYRIC_INFO_T t_lyric_info;
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_show_hide))
    {
        return MMPR_INV_ARG;
    }

    if (_MMP_VE_ELMT_TYPE_AUDIO == pt_elmt->e_elmt_type)
    {
        c_memset(&t_lyric_info, 0, sizeof(SVC_MM_SBTL_LYRIC_INFO_T));

        i4_ret = video_engine_get_lyric_info(
                        (MMP_VE_PLAY_INST_PTR_T)pt_this,
                        &t_lyric_info
                        );
        if ((MMPR_OK != i4_ret) || (TRUE != t_lyric_info.b_has_lyric))
        {
            MMP_DBG_INFO(("{MMP}video_engine_get_lyric_info:%d:%d\r\n",i4_ret,t_lyric_info.b_has_lyric));
            return MMPR_OK; /* To fix DTV00080939 */
        }
    } /* To fix DTV00083701 */

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SBTL_SET_TYPE_SHOW_HIDE,
                    (VOID*)pt_show_hide,
                    sizeof(MM_SVC_SBTL_SHOW_HIDE_T)
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_OK; /* To fix DTV00914466 */
    }

    return MMPR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: video_engine_set_sub_attr
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
extern INT32 video_engine_set_sub_attr(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SBTL_ATTR_PTR_T          pt_sbtl_attr      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_sbtl_attr))
    {
        return MMPR_INV_ARG;
    }
    MMP_DBG_INFO(("{mmp} sub attr type:%d\n\r",pt_sbtl_attr->t_attr_type));
    switch (pt_sbtl_attr->t_attr_type)
    {
        case MMP_VE_SBTL_SET_DISP_MODE:
            i4_ret = _mmp_ve_sbtl_set_line(pt_this, &pt_sbtl_attr->u.t_disp_mode);
            break;

        case MMP_VE_SBTL_SET_TIME_OFST:
            i4_ret = _mmp_ve_sbtl_set_time(pt_this, &pt_sbtl_attr->u.t_time_ofst);
            break;

        case MMP_VE_SBTL_SET_NRML_ATTR:
            i4_ret = mmp_ve_sbtl_set_font(pt_this, &pt_sbtl_attr->u.t_nrml_attr);
            break;

        case MMP_VE_SBTL_SET_FONT_ENC:
            i4_ret = mmp_ve_sbtl_set_encode(pt_this, &pt_sbtl_attr->u.t_font_enc);
            break;

        default:
            i4_ret = MMPR_NOT_SUPPORT;
    }

    return i4_ret;
}

VOID video_engine_sbtl_show_hide(MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                                            BOOL b_is_show)
{
    // CR CTV00363045
#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    MM_SVC_SBTL_SHOW_HIDE_T t_sbtl_state = { b_is_show };
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    if (NULL != pt_elmt &&
        _MMP_VE_SBTL_STAT_OFF != pt_elmt->e_sbtl_stat)
    {
        i4_ret = mmp_ve_sbtl_set_show(pt_this, &t_sbtl_state);
        if(MMPR_OK != i4_ret)
        {
            return;
        }
    }
#endif
}

#ifdef APP_TWN_SUPPORT
/*----------------------------------------------------------------------------
 * Name: video_engine_get_state
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_sbtl_state(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    MMP_ASSERT(NULL != pt_this);

    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);

    MMP_ASSERT(NULL != pt_elmt);

    return (INT32)pt_elmt->e_sbtl_stat;
}
#endif

#ifndef	APP_MMP_VIDEO_STRM_COMP_FILTER_CUST_RULE
#define _VE_AUD_DEP_TRACK_NUM (8)
static BOOL _video_eng_aud_same_lang(
    const CHAR* s639_lang_a,
    const CHAR* s639_lang_b)
{
    static const CHAR* s_str_lang[] = {
        "hrv", "ces", "nld", "esl", "fra", "kat", "deu", "ell", "srp", "slk", "gae"};

    static const CHAR* s_str_alias[] = {
        "scr", "cze", "dut", "spa", "fre", "geo", "ger", "gre", "scc", "slo", "gla"};

    INT32 i4_i;

    if (s639_lang_a == NULL || s639_lang_b == NULL)
    {
        return FALSE;
    }
    if (c_strcasecmp(s639_lang_a, s639_lang_b) == 0)
    {
        return TRUE;
    }

    for (i4_i = 0; i4_i < sizeof(s_str_lang)/sizeof(s_str_lang[0]); i4_i++)
    {
        if (0 == c_strcasecmp(s639_lang_a, s_str_lang[i4_i]))
        {
            if (0 == c_strcasecmp(s639_lang_b, s_str_alias[i4_i]))
            {
                return TRUE;
            }
            break;
        }
        if (0 == c_strcasecmp(s639_lang_a, s_str_alias[i4_i]))
        {
            if (0 == c_strcasecmp(s639_lang_b, s_str_lang[i4_i]))
            {
                return TRUE;
            }
            break;
        }
    }

    return FALSE;
}

BOOL video_engine_mpeg_aud_can_select(
    const SCDB_AUDIO_MPEG_T* pt_aud_mpeg,
    BOOL                     b_add,
    BOOL                     b_clear)
{
    static  CHAR           s_lang[_VE_AUD_DEP_TRACK_NUM][ISO_639_LANG_LEN];
    static  UINT8          ui1_idx = 0;
    if (b_clear)
    {
        ui1_idx = 0;
        return TRUE;
    }
    //b_clear true b_add  any  :  just clear list
    //b_add  true  b_clear false: do add into list
    //b_add  false b_clear false: check whether in list
    if (pt_aud_mpeg)
    {
        if (pt_aud_mpeg->e_type  == AUD_TYPE_VISUAL_IMPAIRED  ||
            pt_aud_mpeg->e_class == AUD_CLASS_VISUAL_IMPAIRED_AD)
        {
            //if mix type is independent or not in list
            if (pt_aud_mpeg->e_mix_type == AUD_MIX_INDEPENDENT)
            {
                return TRUE;
            }
            if (b_add == FALSE)
            {
                UINT8 ui1_i;
                if (ui1_idx > _VE_AUD_DEP_TRACK_NUM)
                {
                    ui1_idx = _VE_AUD_DEP_TRACK_NUM;
                }
                for (ui1_i = 0; ui1_i < ui1_idx; ui1_i++)
                {
                     if (_video_eng_aud_same_lang(s_lang[ui1_i], pt_aud_mpeg->s_lang))
                     {
                        return FALSE;
                     }
                }
                return TRUE;
            }
        }
        else
        {
            switch (pt_aud_mpeg->e_type)
            {
            case AUD_TYPE_UNKNOWN:
            case AUD_TYPE_CLEAN:
            case AUD_TYPE_HEARING_IMPAIRED:
            case AUD_TYPE_RESERVED:
            case AUD_TYPE_COMPLETE_MAIN:
                //here add into list
                if (b_add && ui1_idx < _VE_AUD_DEP_TRACK_NUM)
                {
                    DBG_INFO(("aud add lang:%s\n", pt_aud_mpeg->s_lang));
                    c_strcpy(s_lang[ui1_idx], pt_aud_mpeg->s_lang);
                    ui1_idx++;
                }
                return TRUE;
            default:
                break;
            }
        }
    }
    return FALSE;
}
#endif

#ifndef APP_MMP_PVR_AUDIO_SWITCH_CUST_RULE
/*----------------------------------------------------------------------------
 * Name: video_engine_get_aud_mode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_aud_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_AUD_DOWNMIX_MODE_T*         pe_aud_mode       /* out */
                    )
{
#ifdef APP_MMP_AUDIO_DUAL_NEW_SETTING_RULE
    SM_COMMAND_T at_sm_cmds[3];
    HANDLE_T h_aud_comp = NULL_HANDLE;
    SCC_AUD_DOWNMIX_MODE_T e_aud_mode = SCC_AUD_DOWNMIX_MODE_OFF;
    INT32 i4_ret;
	MMP_VE_CHN_INFO_T            t_chn_info;
	SCC_AUD_MATRIX_MODE_T	e_aud_mt_mode = SCC_AUD_MATRIX_MODE_DUAL_OFF;

    if ((NULL == pt_play_inst) || (NULL == pe_aud_mode))
    {
        return MMPR_INV_ARG;
    }

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_aud_comp);
    if(SMR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    do
    {
		i4_ret = video_engine_get_chn_info(
                        pt_play_inst,
                        &t_chn_info
                        );
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}video_engine_get_chn_info %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
			break;
        }

		if((ASH_CHANNELS_STEREO == t_chn_info.e_chn_type)||
			(ASH_CHANNELS_DUAL_MONO == t_chn_info.e_chn_type))
		{
			i4_ret = c_scc_aud_get_matrix_mode(h_aud_comp, &e_aud_mt_mode);
            MMP_DBG_INFO(("{mmp} get matrix mode:%d,i4_ret:%d\n\r",e_aud_mt_mode,i4_ret));
	        if(SMR_OK != i4_ret)
	        {
	            break;
	        }

			switch(e_aud_mt_mode)
    		{
    		case SCC_AUD_MATRIX_MODE_DUAL1:
				e_aud_mode = SCC_AUD_DOWNMIX_MODE_DUAL1;
				break;
			case SCC_AUD_MATRIX_MODE_DUAL2:
				e_aud_mode = SCC_AUD_DOWNMIX_MODE_DUAL2;
				break;
			case SCC_AUD_MATRIX_MODE_DUAL_MIX:
				e_aud_mode = SCC_AUD_DOWNMIX_MODE_DUAL_MIX;
				break;
			case SCC_AUD_MATRIX_MODE_DUAL_OFF:
				e_aud_mode = SCC_AUD_DOWNMIX_MODE_STEREO;
				break;
			default:
				break;
    		}
		}
		else
		{
	        i4_ret = c_scc_aud_get_downmix_mode(h_aud_comp, &e_aud_mode);
            MMP_DBG_INFO(("{mmp} get downmix mode:%d,i4_ret:%d\n\r",e_aud_mode,i4_ret));
	        if(SMR_OK != i4_ret)
	        {
	            break;
	        }
		}

        *pe_aud_mode = e_aud_mode;

        i4_ret = MMPR_OK;

    }while(0);

    c_scc_comp_close(h_aud_comp);

    return i4_ret;
#else
    SM_COMMAND_T at_sm_cmds[3];
    HANDLE_T h_aud_comp = NULL_HANDLE;
    SCC_AUD_DOWNMIX_MODE_T e_aud_mode = SCC_AUD_DOWNMIX_MODE_OFF;
    INT32 i4_ret = MMPR_OK;

    if ((NULL == pt_play_inst) || (NULL == pe_aud_mode))
    {
        return MMPR_INV_ARG;
    }

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_aud_comp);
    if(SMR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }


    i4_ret = c_scc_aud_get_downmix_mode(h_aud_comp, &e_aud_mode);
    MMP_DBG_INFO(("{mmp} get downmix mode:%d,i4_ret:%d\n\r",e_aud_mode,i4_ret));
    if(SMR_OK != i4_ret)
    {
        c_scc_comp_close(h_aud_comp);
        return i4_ret;
    }

    *pe_aud_mode = e_aud_mode;

    c_scc_comp_close(h_aud_comp);

    return i4_ret;
#endif
}

/*----------------------------------------------------------------------------
 * Name: video_engine_set_aud_mode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_set_aud_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_AUD_DOWNMIX_MODE_T          e_aud_mode        /* out */
                    )
{
    MMP_DBG_INFO(("{mmp} set aud mode:%d\n\r",e_aud_mode));
#ifdef APP_MMP_AUDIO_DUAL_NEW_SETTING_RULE
    SM_COMMAND_T at_sm_cmds[3];
    HANDLE_T h_aud_comp = NULL_HANDLE;
    INT32 i4_ret = MMPR_OK;

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_aud_comp);
    if(SMR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

	if((SCC_AUD_DOWNMIX_MODE_DUAL1 == e_aud_mode)||
		(SCC_AUD_DOWNMIX_MODE_DUAL2 == e_aud_mode)||
		(SCC_AUD_DOWNMIX_MODE_DUAL_MIX == e_aud_mode)||
		(SCC_AUD_DOWNMIX_MODE_DUAL_OFF == e_aud_mode)||
		(SCC_AUD_DOWNMIX_MODE_STEREO == e_aud_mode ||
		SCC_AUD_DOWNMIX_MODE_OFF == e_aud_mode))
	{
		switch(e_aud_mode)
		{
		case SCC_AUD_DOWNMIX_MODE_DUAL1:
			e_aud_mode = SCC_AUD_MATRIX_MODE_DUAL1;
			break;
		case SCC_AUD_DOWNMIX_MODE_DUAL2:
			e_aud_mode = SCC_AUD_MATRIX_MODE_DUAL2;
			break;
		case SCC_AUD_DOWNMIX_MODE_DUAL_MIX:
			e_aud_mode = SCC_AUD_MATRIX_MODE_DUAL_MIX;
			break;
		case SCC_AUD_DOWNMIX_MODE_DUAL_OFF:
		case SCC_AUD_DOWNMIX_MODE_STEREO:
			e_aud_mode = SCC_AUD_MATRIX_MODE_DUAL_OFF;
			break;
		default:
			break;
		}
		i4_ret = c_scc_aud_set_matrix_mode(h_aud_comp, e_aud_mode);
		IS_MMPR_OK(i4_ret);
	}
	else
	{
        i4_ret = c_scc_aud_set_downmix_mode(h_aud_comp, e_aud_mode);
        IS_MMPR_OK(i4_ret);
	}

    c_scc_comp_close(h_aud_comp);

    return i4_ret;
#else
    SM_COMMAND_T at_sm_cmds[3];
    HANDLE_T h_aud_comp = NULL_HANDLE;
    INT32 i4_ret;

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_aud_comp);
    if(SMR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    i4_ret = c_scc_aud_set_downmix_mode(h_aud_comp, e_aud_mode);
    IS_MMPR_OK(i4_ret);

    c_scc_comp_close(h_aud_comp);

    return i4_ret;
#endif
}
#else
/*----------------------------------------------------------------------------
 * Name: video_engine_get_aud_mode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_aud_mode(
                    SCC_AUD_MODE_TYPE_T             e_aud_type,       /*in */
                    UINT32*                         pui4_aud_mode     /* out */
                    )
{
    SM_COMMAND_T at_sm_cmds[3];
    HANDLE_T h_aud_comp = NULL_HANDLE;
    UINT32 ui4_aud_mode = 0;
    INT32 i4_ret = MMPR_OK;

    if(pui4_aud_mode == NULL)
    {
        MMP_DBG_INFO(("{MMP}%s:%d!!!\n",__FUNCTION__,__LINE__));
        return MMPR_INV_ARG;
    }

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_aud_comp);
    if(SMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}%s:%d,i4_ret:%d!!!\n",__FUNCTION__,__LINE__,i4_ret));
        return MMPR_FAIL;
    }

    MMP_DBG_INFO(("{mmp}get aud mode type:%d\n\r",e_aud_type));

    if(e_aud_type == SCC_AUD_MODE_TYPE_DOWNMIX)
    {
        i4_ret = c_scc_aud_get_downmix_mode(h_aud_comp, (SCC_AUD_DOWNMIX_MODE_T*)&ui4_aud_mode);
    }
    else
    {
        i4_ret = c_scc_aud_get_matrix_mode(h_aud_comp, (SCC_AUD_MATRIX_MODE_T*)&ui4_aud_mode);
    }

    MMP_DBG_INFO(("{mmp}get aud mode:%d,i4_ret:%d\n\r",ui4_aud_mode,i4_ret));

    *pui4_aud_mode = ui4_aud_mode;

    c_scc_comp_close(h_aud_comp);

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: video_engine_set_aud_mode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_set_aud_mode(
                    SCC_AUD_MODE_TYPE_T             e_aud_type,       /*in */
                    UINT32                          ui4_aud_mode     /* in */
                    )
{
    SM_COMMAND_T at_sm_cmds[3];
    HANDLE_T h_aud_comp = NULL_HANDLE;
    INT32 i4_ret = MMPR_OK;

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    MMP_DBG_INFO(("{mmp}set aud mode type:%d,mode:%d\n\r",e_aud_type,ui4_aud_mode));
    if(((e_aud_type == SCC_AUD_MODE_TYPE_MATRIX)&&
        (ui4_aud_mode > SCC_AUD_MATRIX_MODE_DUAL_MIX))||
        ((e_aud_type == SCC_AUD_MODE_TYPE_DOWNMIX)&&
        ((ui4_aud_mode > SCC_AUD_DOWNMIX_MODE_AUTO_LORO)&&
        (ui4_aud_mode != SCC_AUD_DOWNMIX_MODE_FORCE_OFF))))
    {
        MMP_DBG_INFO(("{MMP}%s:%d!!!\n",__FUNCTION__,__LINE__));
        return MMPR_INV_ARG;
    }

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_aud_comp);
    if(SMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}%s:%d!!!\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }

    if(e_aud_type == SCC_AUD_MODE_TYPE_DOWNMIX)
    {
        i4_ret = c_scc_aud_set_downmix_mode(h_aud_comp, (SCC_AUD_DOWNMIX_MODE_T)ui4_aud_mode);
    }
    else
    {
        i4_ret = c_scc_aud_set_matrix_mode(h_aud_comp, (SCC_AUD_MATRIX_MODE_T)ui4_aud_mode);
    }
    if(SMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}%s:%d,i4_ret:%d!!!\n",__FUNCTION__,__LINE__,i4_ret));
    }

    c_scc_comp_close(h_aud_comp);

    return i4_ret;
}
#endif


#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
static BOOL b_g_ttx_fct_status = FALSE;

#ifndef APP_MMP_VIDEO_STRM_COMP_FILTER_CUST_RULE
//notes: This API need be align with nav to get right count
BOOL video_engine_valid_ttx(const SCDB_REC_T* pt_scdb_rec)
{
    if (pt_scdb_rec == NULL)
    {
        MMP_DBG_INFO(("{mmp} valid ttx null handle\n"));
        return FALSE;
    }
    if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_TELETEXT_DVB)
    {
        const SCDB_TELETEXT_DVB_T*    pt_tlxt_dvb = &(pt_scdb_rec->u.t_dvb_tltxt);
        MMP_DBG_INFO(("ttx check type:%d pid:%d lang:%s\n",
                     pt_tlxt_dvb->ui2_pid, pt_tlxt_dvb->e_type, pt_tlxt_dvb->s_lang));
        if (pt_tlxt_dvb->e_type == DVB_TLTXT_SBTL_PAGE ||
            pt_tlxt_dvb->e_type == DVB_TLTXT_HEARING_IMPAIR_PAGE)
        {
            return TRUE;
        }
    }
    else if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_VBI_TELETEXT_DVB)
    {
         const SCDB_VBI_TELETEXT_DVB_T* pt_ttx_vbi = &(pt_scdb_rec->u.t_dvb_vbi_tltxt);
        MMP_DBG_INFO(("ttx check type:%d pid:%d lang:%s\n",
                     pt_ttx_vbi->ui2_pid, pt_ttx_vbi->e_type, pt_ttx_vbi->s_lang));
        if (pt_ttx_vbi->e_type == DVB_TLTXT_SBTL_PAGE ||
            pt_ttx_vbi->e_type == DVB_TLTXT_HEARING_IMPAIR_PAGE)
        {
            return TRUE;
        }
    }
    return FALSE;
}
#endif

static BOOL _video_engine_iter_ttx(
    UINT16                          ui2_num_recs,
    UINT16                          ui2_idx,
    const STREAM_COMP_ID_T*         pt_comp_id,
    const SCDB_REC_T*               pt_scdb_rec,
    VOID*                           pv_fltr_tag)
{
    if (pv_fltr_tag && pt_comp_id)
    {
        MMP_DBG_INFO(("cmp %d tag:%x\n", pt_comp_id->e_type, pt_comp_id->pv_stream_tag));
        if (c_memcmp(pt_comp_id, pv_fltr_tag, sizeof(STREAM_COMP_ID_T)) == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static INT32 _video_engine_ttx_scdb_update(
     _MMP_VE_PLAY_INST_PTR_T         pt_this,
     _MMP_VE_ELMT_INFO_PTR_T         pt_elmt)
{
    INT32                  i4_ret  = MMPR_OK;
    UINT32                 ui4_ttx_num = 0;
    BOOL                   b_ret       = FALSE;
    b_ret = a_nav_ttx_sbti_get_scdb_info_num(&ui4_ttx_num);
    MMP_DBG_INFO(("{mmp}scdb update num:%d,b_ret:%d\n\r",ui4_ttx_num,b_ret));
	if (b_ret == FALSE)
    {
        MMP_DBG_ERROR(("{MMP} ttx get num ret:%d\n", b_ret));
    }
    if (ui4_ttx_num == 0)
    {
        return MMPR_OK;
    }
    else
    {
        UINT32 ui4_ttx_idx = 0;
        MMP_DBG_INFO(("{mmp}scdb update state:%d\n\r",pt_elmt->e_ttx_state));
        switch (pt_elmt->e_ttx_state)
        {
            case MMP_TTX_STATE_SHOWN:
            {
                i4_ret = video_engine_convert_ttx_idx(pt_this, &pt_elmt->t_sbtl_comp_id, &ui4_ttx_idx);
                if (i4_ret != MMPR_OK)
                {
                    i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_HIDE, ui4_ttx_idx);
                    i4_ret = MMPR_IS_OPENED;
                }
                else
                {
                    return MMPR_OK;
                }
            }
            break;

            case MMP_TTX_STATE_STARTING:
            case MMP_TTX_STATE_STARTED:
            break;

            default:
                i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_START, 0);
            break;
        }
    }
    return i4_ret;

}

static VOID _video_engine_ttx_nfy_fct(
                    VOID*                           pv_inst_id,       /* in  */
                    VOID*                           pv_elmt_hdl,      /* in  */
                    VOID*                           pv_stm_type,      /* in  */
                    VOID*                           pv_nfy_code       /* in  */
                    )
{
    _MMP_VE_INST_ID_T       t_inst_id      = (_MMP_VE_INST_ID_T)(UINT32)pv_inst_id;
    HANDLE_T                h_elmt_hdl     = (HANDLE_T)(UINT32)pv_elmt_hdl;
    NAV_TTX_SBTI_NFY_COND_T e_ttx_nfy_code = (NAV_TTX_SBTI_NFY_COND_T)(UINT32)pv_nfy_code;

    if((_MMP_VERC_PLAY_INST_NUM  <= t_inst_id) ||
       (NULL == (_MMP_VE_PLAY_INST_PTR_T)video_engine_get_inst_by_idx(t_inst_id)))
    {
        return;
    }
    _MMP_VE_PLAY_INST_PTR_T pt_this     = (_MMP_VE_PLAY_INST_PTR_T)video_engine_get_inst_by_idx(t_inst_id);
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    _MMP_VE_ELMT_ID_T       e_id        = _MMP_VE_ELMT_ID_1ST;
    INT32                   i4_ret      = MMPR_OK;

    if ((NULL == pt_this) || (NULL == pt_elmt_1st))
    {
        return;
    }

    for (e_id = _MMP_VE_ELMT_ID_1ST; e_id < _MMP_VE_ELMT_ID_NUM; e_id++)
    {
        if (h_elmt_hdl == pt_this->at_elmt_info[e_id].h_elmt_hdl)
        {
            break;
        }
    }

    if (_MMP_VE_ELMT_ID_NUM <= e_id)
    {
        return;
    }

    /* treat some notify as invalid after STOP operation */
    if(( MMP_VE_PLAY_STAT_STOP == pt_this->e_play_stat) &&
       (_MMP_VE_ELMT_STAT_STOP == pt_elmt_1st->e_elmt_stat))
    {
         return;
    }

    switch(e_ttx_nfy_code)
    {
        case NAV_TTX_SBTI_STREAM_STARTED:
        {
            MMP_DBG_INFO(("{MMP} Get NAV_TTX_SBTI_STREAM_STARTED message compid:%d %x\n",
                            pt_elmt_1st->t_sbtl_comp_id.e_type,
                            pt_elmt_1st->t_sbtl_comp_id.pv_stream_tag));
            pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_STARTED;
            if (pt_elmt_1st->t_sbtl_comp_id.e_type == ST_TELETEXT)
            {
                 UINT32 ui4_ttx_idx = 0;
                 i4_ret = video_engine_convert_ttx_idx(pt_this, &pt_elmt_1st->t_sbtl_comp_id, &ui4_ttx_idx);
                 if (i4_ret == MMPR_OK)
                 {
                    i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_SHOW, ui4_ttx_idx);
                 }
                 MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case NAV_TTX_SBTI_STREAM_CLOSED:
        {
            MMP_DBG_INFO(("{MMP} Get NAV_TTX_SBTI_STREAM_CLOSED message!!!\n"));
            pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_STOPPED;
        }
        break;

        case NAV_TTX_SBTI_SCDB_UPDATED:
        {
            MMP_DBG_INFO(("{MMP} Get NAV_TTX_SBTI_SCDB_UPDATED message!!!\n"));
            i4_ret = video_engine_handle_scdb_update(pt_this, ST_TELETEXT);
        }
        break;

        default:
            return;
    }

    return;
}


static INT32 _video_engine_ttx_nfy(
    NAV_TTX_SBTI_NFY_COND_T     e_nfy_cond,
    VOID*                       pv_nfy_tag,
    UINT32                      ui4_data)
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pv_nfy_tag;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);

    if(NULL == pt_this || NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_FAIL;
    }

    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _video_engine_ttx_nfy_fct,
                    (VOID*)(UINT32)pt_this->t_inst_id,
                    (VOID*)(UINT32)pt_elmt->h_elmt_hdl,
                    (VOID*)(UINT32)ui4_data,
                    (VOID*)(UINT32)e_nfy_cond
                    );
    return MMPR_OK;
}


INT32 video_engine_convert_ttx_idx(
    _MMP_VE_PLAY_INST_PTR_T pt_this,
    STREAM_COMP_ID_T*       pt_comp_id,
    UINT32*                 pui4_ttx_idx
    )
{
    INT32                   i4_ret = MMPR_OK;
    SCDB_REC_T               t_scdb_rec_find;
    NAV_TTX_SBTI_SCDB_INFO_T t_scdb_rec_nav;
    STREAM_COMP_ID_T        t_comp_id_find;
	UINT32                  ui4_idx, ui4_ttx_num = 0;
    BOOL                    b_ret = FALSE;


    if (pt_this      &&
        pt_comp_id   &&
        pui4_ttx_idx &&
        pt_comp_id->e_type == ST_TELETEXT)
    {
    }
    else
    {
        return MMPR_INV_ARG;
    }
    c_memset(&t_comp_id_find,  0, sizeof(STREAM_COMP_ID_T));
    c_memset(&t_scdb_rec_find, 0, sizeof(SCDB_REC_T));
    c_memset(&t_scdb_rec_nav,  0, sizeof(NAV_TTX_SBTI_SCDB_INFO_T));

    i4_ret = c_svctx_get_stream_comp_id(
	                    pt_this->h_svctx_hdl,
	                    ST_TELETEXT,
	                    _video_engine_iter_ttx,
	                    pt_comp_id,
	                    &t_comp_id_find,
	                    &t_scdb_rec_find
	                    );
    if (i4_ret != SVCTXR_OK)
    {
        MMP_DBG_INFO(("not found comp id %x\n", pt_comp_id->pv_stream_tag));
        return MMPR_NOT_SUPPORT;
    }
    b_ret = a_nav_ttx_sbti_get_scdb_info_num(&ui4_ttx_num);
    MMP_DBG_INFO(("get ttx num:%d rectype:%d\n",ui4_ttx_num , t_scdb_rec_find.e_rec_type));
    for (ui4_idx = 0; ui4_idx < ui4_ttx_num; ui4_idx++)
    {
        b_ret = a_nav_ttx_sbti_get_scdb_info(ui4_idx, &t_scdb_rec_nav);
        if (b_ret == FALSE ||
            t_scdb_rec_find.e_rec_type != t_scdb_rec_nav.e_rec_type)
        {
            continue;
        }
        if (t_scdb_rec_find.e_rec_type == SCDB_REC_TYPE_TELETEXT_DVB)
        {
            SCDB_TELETEXT_DVB_T* pt_scdb_dvb = &t_scdb_rec_find.u.t_dvb_tltxt;
            MMP_DBG_INFO(("{MMP} cmp: pid:%d|%d lang:%s %s\n",
                         pt_scdb_dvb->ui2_pid, t_scdb_rec_nav.ui2_pid,
                         pt_scdb_dvb->s_lang,  t_scdb_rec_nav.s_lang));
            if (pt_scdb_dvb->e_type != t_scdb_rec_nav.e_tltxt_type)
            {
                continue;
            }
            if (pt_scdb_dvb->ui2_pid == t_scdb_rec_nav.ui2_pid &&
                0 == c_strcmp(pt_scdb_dvb->s_lang, t_scdb_rec_nav.s_lang))
            {
                *pui4_ttx_idx = ui4_idx;
                return MMPR_OK;
            }

        }
        if (t_scdb_rec_find.e_rec_type == SCDB_REC_TYPE_VBI_TELETEXT_DVB)
        {
            SCDB_VBI_TELETEXT_DVB_T* pt_scdb_vbi = &t_scdb_rec_find.u.t_dvb_vbi_tltxt;
            MMP_DBG_INFO(("{MMP} cmp: pid:%d|%d lang:%s %s\n",
                         pt_scdb_vbi->ui2_pid, t_scdb_rec_nav.ui2_pid,
                         pt_scdb_vbi->s_lang,  t_scdb_rec_nav.s_lang));
            if (pt_scdb_vbi->e_type != t_scdb_rec_nav.e_tltxt_type)
            {
                continue;
            }
            if (pt_scdb_vbi->ui2_pid == t_scdb_rec_nav.ui2_pid &&
                0 == c_strcmp(pt_scdb_vbi->s_lang, t_scdb_rec_nav.s_lang))
            {
                *pui4_ttx_idx = ui4_idx;
                return MMPR_OK;
            }
        }
    }
    return MMPR_NOT_SUPPORT;
}


INT32 video_engine_ctrl_ttx(
    _MMP_VE_PLAY_INST_PTR_T pt_this,
    MMP_TTX_CMD_T           e_cmd,
    UINT32                  ui4_idx)
{
    INT32                   i4_ret      = MMPR_OK;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = NULL;
    UINT32                  ui4_ttx_num = 0;
    BOOL                    b_ret       = FALSE;
    if (pt_this == NULL)
    {
        return MMPR_INV_ARG;
    }
    pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    if (pt_elmt_1st == NULL)
    {
        return MMPR_INV_ARG;
    }
    if (MEDIA_TYPE_TS != pt_elmt_1st->t_elmt_fmt.e_media_type)
    {
        return MMPR_OK;
    }
    if (!(pt_elmt_1st->ui4_notify_flag & MMP_VE_PLAY_FLAG_VIDEO_FMT_UPDATE))
    {
        return MMPR_NOT_SUPPORT;
    }

    b_ret = a_nav_ttx_sbti_get_scdb_info_num(&ui4_ttx_num);
    if (b_ret == FALSE)
    {
        MMP_DBG_ERROR(("{MMP} ttx get num ret:%d\n", i4_ret));
    }
    MMP_DBG_INFO(("{MMP} ttx begin to do ctrl:%d:%d\n", e_cmd,pt_elmt_1st->e_ttx_state));
    switch (e_cmd)
    {
        case MMP_TTX_CMD_START:
        {
            if (ui4_ttx_num == 0)
            {
                MMP_DBG_INFO(("{MMP} ttx not found yet\n"));
            }
            if(!b_g_ttx_fct_status)
            {
                i4_ret = a_nav_ttx_sbti_set_nfy_fct(_video_engine_ttx_nfy, (VOID*)pt_this);
                if (NAVR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("{MMP}a_nav_ttx_sbti_set_nfy_fct :%d\n", i4_ret));
                }
                b_g_ttx_fct_status = TRUE;
            }

            //notes: teletext num get correct only after open
            if (pt_elmt_1st->e_ttx_state == MMP_TTX_STATE_SHOWN)
            {
                i4_ret = a_nav_ttx_sbti_stop_ex();
                if (NAVR_OK != i4_ret)
                {
                    MMP_DBG_ERROR(("{MMP}a_nav_ttx_sbti_stop_ex :%d\n", i4_ret));
                }

                 pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_HIDEN;
            }
            pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_STARTING;
            i4_ret = a_nav_teletext_restart_stream();
            if (i4_ret != NAVR_OK)
            {
                pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_STOPPED;
            }
        }
        break;

        case MMP_TTX_CMD_STOP:
        {
            switch (pt_elmt_1st->e_ttx_state)
            {
                case MMP_TTX_STATE_SHOWN:
                    i4_ret = a_nav_ttx_sbti_stop_ex();
                    if (NAVR_OK != i4_ret)
                    {
                        MMP_DBG_ERROR(("{MMP}a_nav_ttx_sbti_stop_ex :%d\n", i4_ret));
                    }
                    pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_HIDEN;
                    //no break
                case MMP_TTX_STATE_STARTED:
                    i4_ret = a_nav_teletext_stop_stream();
                    pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_STOPPED;
                    break;
                default:
                    MMP_DBG_INFO(("{MMP} ttx can not stop in state:%d\n", pt_elmt_1st->e_ttx_state));
                    break;
            }
        }
        break;

        case MMP_TTX_CMD_SHOW:
        {
            if( ui4_idx >= ui4_ttx_num)
            {
                return MMPR_NOT_SUPPORT;
            }
            switch (pt_elmt_1st->e_ttx_state)
            {
                case MMP_TTX_STATE_SHOWN:
                case MMP_TTX_STATE_STARTED:
                    i4_ret = a_nav_ttx_sbti_start_ex(ui4_idx);
                    MMP_DBG_INFO(("{MMP} start ttx:%d ret:%d\n", ui4_idx, i4_ret));
                    pt_elmt_1st->e_ttx_state = MMP_TTX_STATE_SHOWN;
                    pt_elmt_1st->e_sbtl_stat = _MMP_VE_SBTL_STAT_ON;
                    break;
                default:
                    MMP_DBG_INFO(("{MMP} ttx can not show in state:%d\n", pt_elmt_1st->e_ttx_state));
                    break;
            }
        }
        break;

        case MMP_TTX_CMD_HIDE:
        {
            switch (pt_elmt_1st->e_ttx_state)
            {
                case MMP_TTX_STATE_SHOWN:
                    i4_ret = a_nav_ttx_sbti_stop_ex();
                    break;
                default:
                    MMP_DBG_INFO(("{MMP} ttx can not hide in state:%d\n", pt_elmt_1st->e_ttx_state));
                    break;
            }
        }
        break;
        default:
            i4_ret = MMPR_INV_ARG;
        break;

    }
    MMP_DBG_INFO(("{MMP} ttx ctrl:%d get num %d ret:%d at:%d\n", e_cmd, ui4_ttx_num, i4_ret, pt_elmt_1st->e_ttx_state));
    return i4_ret;
}

#endif

INT32 video_engine_handle_scdb_update(
    _MMP_VE_PLAY_INST_PTR_T         pt_this,
    STREAM_TYPE_T                   e_stream_type
    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt= NULL;
    INT32                   i4_ret = MMPR_OK;
    if (pt_this == NULL)
    {
        return MMPR_INV_ARG;
    }
    pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    if (pt_elmt == NULL)
    {
        return MMPR_INV_ARG;
    }

    MMP_DBG_INFO(("{mmp}update type:%d\n\r",e_stream_type));
    switch (e_stream_type)
    {
        case ST_TELETEXT:
        {
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
            i4_ret = _video_engine_ttx_scdb_update(pt_this, pt_elmt);

#endif
        }
        break;

        case ST_CLOSED_CAPTION:
        break;

		case ST_UNKNOWN:
		{
			if (pt_this->pf_play_nfy_fct != NULL)
			{
				pt_this->pf_play_nfy_fct(MMP_VE_NFY_CODE_AUDIO_INFO_UPDATE,NULL);
			}
		}
		break;

        default:
            return MMPR_OK;
        break;
    }

    if (pt_this->pf_play_nfy_fct != NULL)
    {
        pt_this->pf_play_nfy_fct(MMP_VE_NFY_CODE_SUBTITLE_INFO_UPDATE,
                                 (VOID*)(UINT32)(i4_ret == MMPR_IS_OPENED));
    }
    return i4_ret;
}

#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _video_engine_iter_sub
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static BOOL _video_engine_iter_sub(
                    UINT16                          ui2_num_recs,
                    UINT16                          ui2_idx,
                    const STREAM_COMP_ID_T*         pt_comp_id,
                    const SCDB_REC_T*               pt_scdb_rec,
                    VOID*                           pv_fltr_tag)
{
    MMP_VE_SUB_INFO_T* pt_sub_info = (MMP_VE_SUB_INFO_T*)pv_fltr_tag;

    if((_MMP_VERC_SUB_MAX_NUM <= pt_sub_info->ui2_sub_num) ||
       (_MMP_VERC_SUB_MAX_NUM <= ui2_idx) ||
       (ui2_num_recs <= ui2_idx))
    {
        return TRUE;
    }

    /* subtitle rec ? */
    MMP_DBG_INFO(("{mmp} f: %s, l: %d, func: %s: sbtl e_rec_type: %d.\n", __FILE__, __LINE__, __FUNCTION__, pt_scdb_rec->e_rec_type));

    switch(pt_scdb_rec->e_rec_type)
    {
		case SCDB_REC_TYPE_SUBTITLE_EXT:

			//skip IPCC
			if (((UINT32)pt_comp_id->pv_stream_tag == 0x765432aa))
			{
				return FALSE;
			}
			pt_sub_info->e_style[pt_sub_info->ui2_sub_num] |= MMP_VE_SBTL_STYLE_EXT;
			if (MM_SBTL_TYPE_VOBSUB != (MM_SBTL_TYPE_T)(pt_scdb_rec->u.t_ext_subtitle.b_is_related & (~0x80)))
			{
				pt_sub_info->e_style[pt_sub_info->ui2_sub_num] |= MMP_VE_SBTL_STYLE_TXT;
			}
			else
			{
				pt_sub_info->e_style[pt_sub_info->ui2_sub_num] |= MMP_VE_SBTL_STYLE_IMG;
			}
			break;
        case SCDB_REC_TYPE_SUBTITLE_DVB:
        case SCDB_REC_TYPE_SUBTITLE_DIVX:
        case SCDB_REC_TYPE_SUBTITLE_MKV:
        case SCDB_REC_TYPE_SUBTITLE_MP4:
		case SCDB_REC_TYPE_SUBTITLE_PS:
		case SCDB_REC_TYPE_CLOSED_CAPTION:
        case SCDB_REC_TYPE_SUBTITLE_PGS:
			if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_CLOSED_CAPTION)
			{
				/*skip fake CC*/
			   if ((pt_scdb_rec->u.t_atsc_cc.e_type == CC_ATSC_LINE_21 &&
			   	    pt_scdb_rec->u.t_atsc_cc.udata.t_cc_atsc_line_21.b_det_in_descr == FALSE)
			   	   ||
			   	   (pt_scdb_rec->u.t_atsc_cc.e_type == CC_ATSC_DTV &&
			   	   	pt_scdb_rec->u.t_atsc_cc.udata.t_cc_atsc_dtv.ui1_caption_svc_num == 0)
			   	   	)
			   {
					return FALSE;
			   }
			}
            if(pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_SUBTITLE_DVB)
            {
                /*following tv behavior: skip Unkown type*/
                if(pt_scdb_rec->u.t_dvb_sbtl.e_sbtl_type == DVB_SBTL_UNKNOWN)
                {
                    return FALSE;
                }
            }
			pt_sub_info->e_style[pt_sub_info->ui2_sub_num] |= MMP_VE_SBTL_STYLE_IMG;
			break;
       case SCDB_REC_TYPE_ISDB_CAPTION:
            pt_sub_info->e_style[pt_sub_info->ui2_sub_num] |= MMP_VE_SBTL_STYLE_IMG;
            break;

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
		case SCDB_REC_TYPE_VBI_TELETEXT_DVB:
		case SCDB_REC_TYPE_TELETEXT_DVB:
		{
			 if (video_engine_valid_ttx(pt_scdb_rec) == FALSE)
			 {
				return FALSE;
			 }
			 if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_TELETEXT_DVB)
			 {
				c_strncpy(pt_sub_info->as_lang[pt_sub_info->ui2_sub_num],
						  pt_scdb_rec->u.t_dvb_tltxt.s_lang,
						  ISO_639_LANG_LEN);
			 }
			 else
			 {
				c_strncpy(pt_sub_info->as_lang[pt_sub_info->ui2_sub_num],
						  pt_scdb_rec->u.t_dvb_vbi_tltxt.s_lang,
						  ISO_639_LANG_LEN);
			 }
		}
		break;
#endif
        default :
            return FALSE;
    }

    /* update subtitle info */
	MMP_DBG_INFO(("{MMP} add sbtl id: %d tag:%x\n", pt_comp_id->e_type, pt_comp_id->pv_stream_tag));
    c_memcpy(&pt_sub_info->at_comp_id[pt_sub_info->ui2_sub_num], pt_comp_id, sizeof(STREAM_COMP_ID_T));

    if (pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_SUBTITLE_DIVX)
    {
        c_strncpy(pt_sub_info->as_lang[pt_sub_info->ui2_sub_num],
                  pt_scdb_rec->u.t_subtitle_avi.s_lang,
                  ISO_639_LANG_LEN);
    }
    else if(pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_SUBTITLE_MKV)
    {
        c_strncpy(pt_sub_info->as_lang[pt_sub_info->ui2_sub_num],
                  pt_scdb_rec->u.t_subtitle_mkv.s_lang,
                  ISO_639_LANG_LEN);
        MMP_DBG_INFO(("{mmp} f: %s, l: %d, func: %s: mkv sbtl lang[%d]: %s.\n", __FILE__, __LINE__, __FUNCTION__, pt_sub_info->ui2_sub_num, pt_scdb_rec->u.t_subtitle_mkv.s_lang));
    }

    pt_sub_info->ui2_sub_num++;

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_sub_info
 *
 * Description: Get subtitle infomation.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_sub_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SUB_INFO_PTR_T           pt_sub_info       /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
	_MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
	SCDB_REC_T				t_scdb_rec = {0};
	STREAM_COMP_ID_T		t_comp_id;
	INT32					i4_ret = 0;
	UINT16					ui2_i = 0;

	if ((NULL == pt_this) || (NULL == pt_elmt) || (NULL == pt_sub_info))
	{
		MMP_ASSERT(FALSE);
		return MMPR_INV_ARG;
	}
	c_memset(&t_comp_id, 0, sizeof(STREAM_COMP_ID_T));

    MMP_DBG_INFO(("{mmp} f: %s, l: %d, func: %s: e_sbtl_stat: %d.\n", __FILE__, __LINE__, __FUNCTION__, pt_elmt->e_sbtl_stat));
    
	if (_MMP_VE_SBTL_STAT_OFF != pt_elmt->e_sbtl_stat)
	{
		pt_sub_info->t_sub_font = MMP_VE_SBTL_ENCODE_UNKNOW;
		if (pt_sub_info->ui2_sub_num > 0)
		{
			pt_sub_info->ui2_sub_num = 0;
		}
	}
	else
	{
		c_memset(pt_sub_info, 0, sizeof(MMP_VE_SUB_INFO_T));
		pt_sub_info->ui2_sel_idx = 0;
		pt_sub_info->ui2_sub_num = 0;
		pt_sub_info->ui4_strm_id = (UINT32)-1; /* Is 0xFFFFFFFF available as stream id ?*/
	}
	i4_ret = c_svctx_get_stream_comp_id(
					pt_this->h_svctx_hdl,
					ST_CLOSED_CAPTION,
					_video_engine_iter_sub,
					pt_sub_info,
					&t_comp_id,
					&t_scdb_rec
					);
    i4_ret = c_svctx_get_stream_comp_id(
					pt_this->h_svctx_hdl,
					ST_ISDB_CAPTION,
					_video_engine_iter_sub,
					pt_sub_info,
					&t_comp_id,
					&t_scdb_rec
					);

	i4_ret = c_svctx_get_stream_comp_id(
					pt_this->h_svctx_hdl,
					ST_SUBTITLE,
					_video_engine_iter_sub,
					pt_sub_info,
					&t_comp_id,
					&t_scdb_rec
					);
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
	i4_ret = c_svctx_get_stream_comp_id(
					pt_this->h_svctx_hdl,
					ST_TELETEXT,
					_video_engine_iter_sub,
					pt_sub_info,
					&t_comp_id,
					&t_scdb_rec
					);
#endif
	if (SVCTXR_OK != i4_ret && i4_ret != SVCTXR_NOT_EXIST)
	{
		MMP_DBG_ERROR(("{MMP} get sbtl info ret:%d at %d\n", i4_ret, __LINE__));
		return i4_ret;
	}


	for (ui2_i = 0; ui2_i < pt_sub_info->ui2_sub_num; ui2_i++)
	{
		//get correct sel idx for ts subtitle started later then get info

		if (c_memcmp(&(pt_sub_info->at_comp_id[ui2_i]),
					 &pt_elmt->t_sbtl_comp_id,
					 sizeof(STREAM_COMP_ID_T)) == 0)
		{
			pt_sub_info->ui2_sel_idx = ui2_i+1;
			break;
		}
	}

#ifdef APP_LAST_MEMORY_SUPPORT
    MMP_DBG_INFO(("{MMP} ui2_sel_idx:%d ui2_sub_num:%d state:%d playidx:%x \n",
                   pt_sub_info->ui2_sel_idx, pt_sub_info->ui2_sub_num, pt_elmt->e_sbtl_stat, video_engine_get_last_mem_subtitle_play_id()));
#endif

#ifdef APP_IPCC_SUPPORT
    /*add IPCC subtitle*/
    if (pt_elmt->ui1_ipcc_num > 0)
    {
        pt_sub_info->ui2_sub_num += pt_elmt->ui1_ipcc_num;
    }
#endif

    if (0 == pt_sub_info->ui2_sub_num)
    {
        return MMPR_OK;
    }
    /* add one sub and use the index = 0 item to stop subtitle */
    else
    {
        pt_sub_info->ui2_sub_num += 1;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_sub
 *
 * Description: Change subtitle.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_sub(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SUB_INFO_PTR_T           pt_sub_info       /* out */
                    )
{
	_MMP_VE_PLAY_INST_PTR_T pt_this 	= (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
#ifdef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
	if (pt_this == NULL)
	{
		return MMPR_INV_ARG;
	}
	return mmp_video_engine_custom_select_sub_title(pt_this->h_svctx_hdl,
													pt_sub_info);
#else
	_MMP_VE_ELMT_INFO_PTR_T pt_elmt 		=  _MMP_VE_GET_1ST_ELMT(pt_this);
	INT32					i4_ret			= 0;
	STREAM_COMP_ID_T		t_comp_id;
	MMP_VE_SBTL_STYLE		t_sbtl_style	= MMP_VE_SBTL_STYLE_NONE;
	STREAM_TYPE_T			t_strm_type 	= ST_SUBTITLE;
	STREAM_TYPE_T			t_new_strm_type = ST_SUBTITLE;

	if(NULL == pt_this || NULL == pt_sub_info ||
	   _MMP_VERC_SUB_MAX_NUM < pt_sub_info->ui2_sel_idx)
	{
		MMP_ASSERT(FALSE);
		return MMPR_INV_ARG;
	}
	c_memset(&t_comp_id, 0, sizeof(STREAM_COMP_ID_T));
	//add cc support when toggle cc and subtitle should stop stream
	if (_MMP_VE_SBTL_STAT_OFF != pt_elmt->e_sbtl_stat)
	{
		t_strm_type = pt_elmt->t_sbtl_comp_id.e_type;
	 }

	 if (0 == pt_sub_info->ui2_sel_idx)
	 {
		switch (t_strm_type)
		{
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
			case ST_TELETEXT:
				i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_HIDE, 0);
				break;
#endif
			case ST_SUBTITLE:
			case ST_CLOSED_CAPTION:
            case ST_ISDB_CAPTION:
				i4_ret = c_svctx_stop_stream(pt_this->h_svctx_hdl, t_strm_type);
				break;
			default:
				i4_ret = MMPR_NOT_SUPPORT;
				break;
		}
		pt_elmt->e_sbtl_stat = _MMP_VE_SBTL_STAT_OFF;
		c_memset(&pt_elmt->t_sbtl_comp_id, 0, sizeof(STREAM_COMP_ID_T));
#ifdef APP_LAST_MEMORY_SUPPORT
		video_engine_set_last_mem_subtitle_play_id(0);
#endif
		MMP_DBG_INFO(("{MMP} [stage 1] call close here:%d\n", t_strm_type));
		return i4_ret;
	 }

	 //prepare comp id and stop if sbtl type changed
#ifdef APP_IPCC_SUPPORT
	 if (pt_elmt->ui1_ipcc_num > 0 &&
		 pt_sub_info->ui2_sub_num <= pt_sub_info->ui2_sel_idx + pt_elmt->ui1_ipcc_num )
	 {
		UINT16	ui2_idx = pt_sub_info->ui2_sub_num-pt_sub_info->ui2_sel_idx-1;
		MM_SVC_SUBTITLE_INFO_USER_SET_T t_ipcc_set;
		UINT32							ui4_len = 0;
		if (ui2_idx >= MAX_IPCC_NUM || ui2_idx >= pt_elmt->ui1_ipcc_num)
		{
			return MMPR_INV_ARG;
		}
		ui4_len = c_strlen(pt_elmt->ps_ipcc_path[ui2_idx]);
		if (ui4_len > 256 || ui4_len == 0)
		{
			return MMPR_INV_ARG;
		}
		c_memset(&t_ipcc_set, 0, sizeof(MM_SVC_SUBTITLE_INFO_USER_SET_T));
		c_strncpy(t_ipcc_set.ps_full_path, pt_elmt->ps_ipcc_path[ui2_idx],256);
		i4_ret = c_svctx_media_set_info(
							   pt_this->h_svctx_hdl,
							   pt_elmt->h_elmt_hdl,
							   SVCTX_MM_SET_SBTL_USER_SET_INFO,
							   (VOID*)&t_ipcc_set,
							   sizeof(MM_SVC_SUBTITLE_INFO_USER_SET_T));
		if (i4_ret != SVCTXR_OK)
		{
			return i4_ret;
		}
		t_comp_id.e_type = ST_SUBTITLE;
		t_comp_id.pv_stream_tag = (VOID*)(0x765432aa);
	 }
	 else
#endif
	 {
		t_comp_id =  pt_sub_info->at_comp_id[pt_sub_info->ui2_sel_idx-1];
		t_new_strm_type = t_comp_id.e_type;
	 }

	 if (t_strm_type != t_new_strm_type)
	 {
		switch (t_strm_type)
		{
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
			case ST_TELETEXT:
				i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_HIDE, 0);
				break;
#endif
			case ST_SUBTITLE:
			case ST_CLOSED_CAPTION:
				i4_ret = c_svctx_stop_stream(pt_this->h_svctx_hdl, t_strm_type);
				break;
			default:
				break;
		}
		if (MMPR_OK != i4_ret)
		{
			MMP_DBG_ERROR(("{MMP} try to close sbtl ret:%d \n", i4_ret));
		}
		c_memset(&pt_elmt->t_sbtl_comp_id, 0, sizeof(STREAM_COMP_ID_T));
	 }


	 t_sbtl_style = pt_sub_info->e_style[pt_sub_info->ui2_sel_idx-1];

	 MMP_DBG_INFO(("{MMP} select sbtl stream type:%d style:%d tag:%d\n",
					 t_new_strm_type,t_sbtl_style, t_comp_id.pv_stream_tag));

	 switch (t_new_strm_type)
	 {
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
		case ST_TELETEXT:
		{
			UINT32 ui4_ttx_idx = 0;
			i4_ret = video_engine_convert_ttx_idx(pt_this, &t_comp_id, &ui4_ttx_idx);
			if (i4_ret != MMPR_OK)
			{
				MMP_DBG_INFO(("{MMP} can not find ttx for:%d\n", pt_sub_info->ui2_sel_idx));
				return i4_ret;
			}
			i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_SHOW, ui4_ttx_idx);
			break;
		}
#endif
		default:
		{
			i4_ret = c_svctx_select_stream(
						pt_this->h_svctx_hdl,
						&t_comp_id,
						NULL,
						NULL
						);
		}
		break;
	 }
	 if (i4_ret != MMPR_OK)
	 {
		c_memset(&pt_elmt->t_sbtl_comp_id, 0, sizeof(STREAM_COMP_ID_T));
	 }
	 else
	 {
		pt_elmt->t_sbtl_comp_id = t_comp_id;
	 }
	 pt_elmt->e_sbtl_stat = _MMP_VE_SBTL_STAT_ON;
	//we store last memory for internal and external seperator


#ifdef APP_LAST_MEMORY_SUPPORT
	video_engine_set_sbtl_last_mem(pt_sub_info);
#endif

	return i4_ret;
#endif
}

#endif

#ifdef APP_LAST_MEMORY_SUPPORT
#define VE_SUPPORT_SBTL_NUM_EACH_TYPE (20)
#define VE_SUPPORT_SBTL_TYPE_NUM      (4)
static BOOL _get_sbtl_type_idx(
    STREAM_TYPE_T e_strm_type,
    BOOL          b_external,
    UINT8*        pui1_idx)
{
    // ST_CLOSED_CAPTION,ST_ISDB_CAPTION,ST_ISDB_TEXT,ST_TELETEXT,ST_SUBTITLE,
    if (b_external)
    {
        *pui1_idx = 3;
    }
    else
    {
        switch (e_strm_type)
        {
            case ST_CLOSED_CAPTION:
                *pui1_idx = 0;
                break;
            case ST_TELETEXT:
                *pui1_idx = 1;
                break;
            case ST_SUBTITLE:
                *pui1_idx = 2;
                break;
            case ST_ISDB_CAPTION:
                *pui1_idx = 3;
                break;
            default:
                return FALSE;
        }
    }
    return TRUE;

}
VOID video_engine_set_sbtl_last_mem(
    MMP_VE_SUB_INFO_PTR_T   pt_sub_info)
{
    UINT8             ui1_idx      = 0;
    UINT8             ui2_sbtl_num = 0;
    UINT16            ui2_i     = 0;
#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
    MMP_VE_SBTL_STYLE t_sbtl_style;
#endif

    if (pt_sub_info == NULL ||
        pt_sub_info->ui2_sel_idx == 0 ||
        pt_sub_info->ui2_sel_idx  > _MMP_VERC_SUB_MAX_NUM)
    {
        MMP_DBG_ERROR(("{mmp} error set sbtl last mem\n"));
        return;
    }
#ifndef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
    t_sbtl_style = pt_sub_info->e_style[pt_sub_info->ui2_sel_idx - 1];
    if (t_sbtl_style & MMP_VE_SBTL_STYLE_EXT)
    {
         for (ui2_i = 0; ui2_i < pt_sub_info->ui2_sel_idx; ui2_i++)
         {
         	if ((pt_sub_info->e_style[ui2_i] & MMP_VE_SBTL_STYLE_EXT) ==
        		(t_sbtl_style & MMP_VE_SBTL_STYLE_EXT))
         	{
        		ui2_sbtl_num++;
         	}
         }
         _get_sbtl_type_idx(ST_UNKNOWN, TRUE, &ui1_idx);
    }
    else
#endif
    {
        STREAM_TYPE_T e_strm_type;
        e_strm_type = pt_sub_info->at_comp_id[pt_sub_info->ui2_sel_idx - 1].e_type;
        for (ui2_i = 0; ui2_i < pt_sub_info->ui2_sel_idx; ui2_i++)
        {
        	if (pt_sub_info->at_comp_id[ui2_i].e_type == e_strm_type)
        	{
        	    ui2_sbtl_num++;
        	}
        }
        _get_sbtl_type_idx(e_strm_type, FALSE, &ui1_idx);
    }
    video_engine_set_last_mem_subtitle_play_id((ui1_idx * VE_SUPPORT_SBTL_NUM_EACH_TYPE + ui2_sbtl_num));
    MMP_DBG_INFO(("sbtl lastmem:%d\n",video_engine_get_last_mem_subtitle_play_id()));
}
BOOL video_engine_chk_sbtl_last_mem(
    STREAM_TYPE_T           e_strm_type,
    BOOL                    b_external,
    BOOL                    b_reset)
{
    static UINT8 aui1_sbtl_idx[VE_SUPPORT_SBTL_TYPE_NUM];
    UINT8        ui1_idx = 0;
    if (b_reset && e_strm_type == ST_UNKNOWN)
    {
        c_memset(aui1_sbtl_idx, 0, VE_SUPPORT_SBTL_TYPE_NUM*sizeof(UINT8));
        return TRUE;
    }
    if (FALSE == _get_sbtl_type_idx(e_strm_type, b_external, &ui1_idx) ||
        ui1_idx >= VE_SUPPORT_SBTL_TYPE_NUM)
    {
        return FALSE;
    }
    if (b_reset)
    {
        MMP_DBG_INFO(("reset sbtl %d to be 0\n", ui1_idx));
        aui1_sbtl_idx[ui1_idx] = 0;
    }
    else
    {
        aui1_sbtl_idx[ui1_idx]++;
        MMP_DBG_INFO(("inc sbtl %d to be %d/%d\n", ui1_idx, aui1_sbtl_idx[ui1_idx], video_engine_get_last_mem_subtitle_play_id()));
    }
    if ((aui1_sbtl_idx[ui1_idx] + ui1_idx * VE_SUPPORT_SBTL_NUM_EACH_TYPE) == video_engine_get_last_mem_subtitle_play_id())
    {
        return TRUE;
    }
    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: mmp_ve_stop_info_update
 * Description: update stop info.
 * Inputs:
 * Outputs:
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_stop_info_update(
                    _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                    _MMP_VE_STOP_INFO_PTR_T         pt_stop_info
                    )
{
    UINT16 ui2_update_idx = 0;
    UINT16 i = 0;

    if ((NULL == pt_play_inst) || (NULL == pt_stop_info))
    {
        return MMPR_INV_ARG;
    }

    for (i = 0; i < _MMP_VERC_STOP_INFO_NUM; i++)
    {
        if (pt_stop_info->ui8_clip_id == pt_play_inst->at_stop_info[i].ui8_clip_id)
        {
            ui2_update_idx = i;       /* find out already exist clip id */
            break;
        }
    }

    if (_MMP_VERC_STOP_INFO_NUM == i) /* not found the same clip id */
    {
        for (i = 0; i < _MMP_VERC_STOP_INFO_NUM; i++)
        {
            if (0 == pt_play_inst->at_stop_info[i].ui8_clip_id)
            {
                ui2_update_idx = i;   /* find out the 1st empty clip id */
                break;
            }
        }
    }

    if (_MMP_VERC_STOP_INFO_NUM == i) /* not found any empty clip id */
    {
        _MMP_VE_STOP_INFO_T at_temp_info[_MMP_VERC_STOP_INFO_NUM];

        c_memset(at_temp_info,
                 0,
                 sizeof(_MMP_VE_STOP_INFO_T) * _MMP_VERC_STOP_INFO_NUM);

        c_memcpy(at_temp_info,
                 pt_play_inst->at_stop_info + 1,
                 sizeof(_MMP_VE_STOP_INFO_T) * (_MMP_VERC_STOP_INFO_NUM - 1));

        c_memcpy(pt_play_inst->at_stop_info,
                 at_temp_info,
                 sizeof(_MMP_VE_STOP_INFO_T) * _MMP_VERC_STOP_INFO_NUM);

        ui2_update_idx = _MMP_VERC_STOP_INFO_NUM - 1;
    }

    pt_play_inst->at_stop_info[ui2_update_idx] = *pt_stop_info;

    return MMPR_OK;
}

#ifndef APP_MMP_PVR_LAST_MEMORY_SUPPORT
/*----------------------------------------------------------------------------
 * Name: mmp_ve_stop_info_check
 * Description: check if exist the stop info by identitfy id
 * Inputs:
 * Outputs:
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_stop_info_check(
                    _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                    _MMP_VE_STOP_INFO_PTR_T         pt_stop_info
                    )
{
    UINT16 i = 0;

    if ((NULL == pt_play_inst) || (NULL == pt_stop_info))
    {
        return MMPR_INV_ARG;
    }

    for (i = 0; i < _MMP_VERC_STOP_INFO_NUM; i++)
    {
        if (pt_stop_info->ui8_clip_id == pt_play_inst->at_stop_info[i].ui8_clip_id)
        {
            *pt_stop_info = pt_play_inst->at_stop_info[i];
            return MMPR_OK;
        }
    }

    return MMPR_NO_DATA;
}
#endif
/*----------------------------------------------------------------------------
 * Name: mmp_ve_stop_info_set
 * Description: Save stop info to acfg
 * Inputs:
 * Outputs:
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_stop_info_set(
                            _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                            _MMP_VE_STOP_INFO_PTR_T         pt_stop_info)
{
    INT32  i4_ret        = MMPR_OK;
    UINT8                   ui1_idx;
    APP_CFG_MM_STOP_INFO_T  t_acfg_stop_info;

    if ((pt_play_inst == NULL) || (pt_stop_info == NULL))
    {
        return MMPR_INV_ARG;
    }

    for (ui1_idx=0; ui1_idx<_MMP_VERC_STOP_INFO_NUM; ui1_idx++)
    {
        c_memset((VOID*)&t_acfg_stop_info, 0, sizeof(APP_CFG_MM_STOP_INFO_T));

        t_acfg_stop_info.ui8_clip_id            = pt_stop_info[ui1_idx].ui8_clip_id;
        t_acfg_stop_info.ui4_title_idx          = pt_stop_info[ui1_idx].ui4_title_idx;
        t_acfg_stop_info.ui4_playlist_idx       = pt_stop_info[ui1_idx].ui4_playlist_idx;
        t_acfg_stop_info.ui4_chap_idx           = pt_stop_info[ui1_idx].ui4_chap_idx;
        t_acfg_stop_info.ui2_aud_idx            = pt_stop_info[ui1_idx].ui2_aud_idx;
        t_acfg_stop_info.ui2_sub_idx            = pt_stop_info[ui1_idx].ui2_sub_idx;
        t_acfg_stop_info.ui8_aud_pts_info       = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_aud_pts_info;
        t_acfg_stop_info.ui8_aud_frame_position = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_aud_frame_position;
        t_acfg_stop_info.ui8_i_pts_info         = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_i_pts_info;
        t_acfg_stop_info.ui8_pts_info           = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_pts_info;
        t_acfg_stop_info.ui8_i_frame_position   = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_i_frame_position;
        t_acfg_stop_info.ui8_frame_position     = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_frame_position;
        t_acfg_stop_info.i4_temporal_reference  = pt_stop_info[ui1_idx].t_pos_info.u.render_info.i4_temporal_reference;
        t_acfg_stop_info.ui2_decoding_order     = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui2_decoding_order;
        t_acfg_stop_info.ui4_timestap           = pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui4_timestap;
        i4_ret = a_cfg_set_mmp_last_memory_data(&t_acfg_stop_info, ui1_idx);
        if (i4_ret != APP_CFGR_OK)
        {
            break;
        }
    }

    if(ui1_idx == _MMP_VERC_STOP_INFO_NUM)
    {
        i4_ret = MMPR_OK;
    }
    else
    {
        i4_ret = MMPR_FAIL;
    }

    return i4_ret;
}

#ifndef APP_MMP_PVR_LAST_MEMORY_SUPPORT
/*----------------------------------------------------------------------------
 * Name: mmp_ve_stop_info_get
 * Description: Get stop info from acfg
 * Inputs:
 * Outputs:
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_stop_info_get(
                            _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                            _MMP_VE_STOP_INFO_PTR_T         pt_stop_info)
{
    INT32   i4_ret          = MMPR_OK;
    UINT8                   ui1_idx;
    APP_CFG_MM_STOP_INFO_T  t_acfg_stop_info;

    if ((pt_play_inst == NULL) || (pt_stop_info == NULL))
    {
        return MMPR_INV_ARG;
    }

    for(ui1_idx=0; ui1_idx<_MMP_VERC_STOP_INFO_NUM; ui1_idx++)
    {
        c_memset((VOID*)&t_acfg_stop_info, 0, sizeof(APP_CFG_MM_STOP_INFO_T));

        i4_ret = a_cfg_get_mmp_last_memory_data(&t_acfg_stop_info, ui1_idx);
        if (APP_CFGR_OK != i4_ret)
        {
            break;
        }
        pt_stop_info[ui1_idx].ui8_clip_id                                     = t_acfg_stop_info.ui8_clip_id;
        pt_stop_info[ui1_idx].ui4_title_idx                                   = t_acfg_stop_info.ui4_title_idx;
        pt_stop_info[ui1_idx].ui4_playlist_idx                                = t_acfg_stop_info.ui4_playlist_idx;
        pt_stop_info[ui1_idx].ui4_chap_idx                                    = t_acfg_stop_info.ui4_chap_idx;
        pt_stop_info[ui1_idx].ui2_aud_idx                                     = t_acfg_stop_info.ui2_aud_idx;
        pt_stop_info[ui1_idx].ui2_sub_idx                                     = t_acfg_stop_info.ui2_sub_idx;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_aud_pts_info       = t_acfg_stop_info.ui8_aud_pts_info;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_aud_frame_position = t_acfg_stop_info.ui8_aud_frame_position;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_i_pts_info         = t_acfg_stop_info.ui8_i_pts_info;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_pts_info           = t_acfg_stop_info.ui8_pts_info;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_i_frame_position   = t_acfg_stop_info.ui8_i_frame_position;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui8_frame_position     = t_acfg_stop_info.ui8_frame_position;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui2_decoding_order     = t_acfg_stop_info.ui2_decoding_order;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.i4_temporal_reference  = t_acfg_stop_info.i4_temporal_reference;
        pt_stop_info[ui1_idx].t_pos_info.u.render_info.ui4_timestap           = t_acfg_stop_info.ui4_timestap;
    }

    if (ui1_idx == _MMP_VERC_STOP_INFO_NUM)
    {
        i4_ret = MMPR_OK;
    }
    else
    {
        i4_ret = MMPR_FAIL;
    }
    return i4_ret;
}
#endif
/*----------------------------------------------------------------------------
 * Name: mmp_ve_stop_info_get_ex
 * Description: Get stop info from Middleware, and update stop info to acfg
 * Inputs:
 * Outputs:
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_stop_info_get_ex(
                            _MMP_VE_PLAY_INST_PTR_T         pt_play_inst,
                            _MMP_VE_ELMT_INFO_PTR_T         pt_elmt)
{
    INT32                   i4_ret          = MMPR_OK;
    _MMP_VE_PLAY_INST_PTR_T pt_this         = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    MMP_FP_PRESENT_MODE_T   t_present_mode;

    i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
    if (MMPR_OK != i4_ret)
    {
        t_present_mode = MMP_FP_PRESENT_MODE_FULL;
    }

    if (MMP_FP_PRESENT_MODE_FULL == t_present_mode &&
        MMP_FILE_SRC_MASS_STRG   == pt_elmt->t_file_src)
    {
        if ((_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type) &&
            (_MMP_VE_ELMT_STAT_PLAY  == pt_elmt->e_elmt_stat))
        {
            MM_SVC_STOP_INFO t_svc_info;
            SIZE_T           z_size         = 0;
            UINT8            ui1_lst_mode   = 0;

            i4_ret = a_cfg_get_mmp_last_memory_onoff(&ui1_lst_mode);
            if(i4_ret != APP_CFGR_OK)
            {
                MMP_DBG_INFO(("{MMP} acfg get_mmp_last_memory_mode error return %d Line %d\n", i4_ret, __LINE__));
                i4_ret = MMPR_INTERNAL_ERROR;
                return i4_ret;
            }
            /* Last Memory = OFF */
            if (ui1_lst_mode == 1)
            {
                MMP_DBG_INFO(("{MMP} last memory off \n"));
                i4_ret = MMPR_INTERNAL_ERROR;
                return i4_ret;
            }

            c_memset(&t_svc_info, 0, sizeof(MM_SVC_STOP_INFO));

            z_size = sizeof(MM_SVC_STOP_INFO);

            i4_ret = c_svctx_get(
                            pt_this->h_svctx_hdl,
                            SVCTX_MM_GET_STOP_INFO,
                            (VOID*)&t_svc_info,
                            &z_size
                            );
            if (SVCTXR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_GET_TYPE_STOP_INFO)returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                i4_ret = MMPR_INTERNAL_ERROR;
                return i4_ret;
            }

            pt_elmt->t_stop_info.ui4_title_idx = t_svc_info.ui4_title_idx;
            pt_elmt->t_stop_info.ui4_playlist_idx = t_svc_info.ui4_playlist_idx;
            pt_elmt->t_stop_info.ui4_chap_idx = t_svc_info.ui4_chap_idx;
            pt_elmt->t_stop_info.t_pos_info = t_svc_info.t_mm_svc_pos_info;
            pt_elmt->t_stop_info.ui2_aud_idx = video_engine_get_last_mem_audio_play_id();
            pt_elmt->t_stop_info.ui2_sub_idx = video_engine_get_last_mem_subtitle_play_id();

            i4_ret = mmp_ve_stop_info_update(pt_this, &pt_elmt->t_stop_info);
            if (MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} mmp_ve_stop_info_update: %s: %d %d\n", __FUNCTION__, __LINE__,i4_ret));
                return i4_ret;
            }

            i4_ret = mmp_ve_stop_info_set(pt_this, pt_this->at_stop_info);
            if (MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} mmp_ve_stop_info_set: %s: %d %d\n", __FUNCTION__, __LINE__,i4_ret));
                MMP_ASSERT(FALSE);
                return i4_ret;
            }
        }
    }
    else
    {
        return MMPR_NOT_SUPPORT;
    }
    return i4_ret;
}
extern INT32 video_engine_save_video_playback_last_momory(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret;

    if(NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    i4_ret = mmp_ve_stop_info_get_ex(pt_this, pt_elmt);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}mmp_ve_stop_info_get_ex %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        /*It is not matter to return when fail*/
    }

    return MMPR_OK;
}

#ifdef APP_MMP_PVR_LAST_MEMORY_SUPPORT
static APP_CFG_MM_STOP_INFO_T         t_pvr_stop_info_backup;
INT32 video_engine_before_pvr_play_get_lst_mem(CHAR*	ac_filepath)
{
	INT32	i4_ret;

	i4_ret = a_nav_rec_pvr_browser_get_file_state_data(ac_filepath, NAV_REC_PVR_SET_FILE_STATE_STOP_INFO_FLAG, &t_pvr_stop_info_backup);
	MMP_DBG_INFO (("{MMP} %s LAST_MEMORY i4_ret:%d\n",__FUNCTION__,i4_ret));

	return i4_ret;
}
INT32 video_engine_get_video_last_mem(
					MMP_VE_PLAY_INST_PTR_T			pt_play_inst,
					CHAR*							ac_filepath,
					APP_CFG_MM_STOP_INFO_T*         pt_stop_info
					)
{
    INT32   i4_ret          = MMPR_OK;
    APP_CFG_MM_STOP_INFO_T  t_acfg_stop_info;
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    if (pt_this == NULL)
    {
        return MMPR_INV_ARG;
    }

    c_memset((VOID*)&t_acfg_stop_info, 0, sizeof(APP_CFG_MM_STOP_INFO_T));

    i4_ret = a_nav_rec_pvr_browser_get_file_state_data(ac_filepath, NAV_REC_PVR_SET_FILE_STATE_STOP_INFO_FLAG, &t_acfg_stop_info);
    if (MMPR_OK != i4_ret)
	{
        return MMPR_FAIL;
	}
	c_memcpy(pt_stop_info, &t_acfg_stop_info, sizeof(APP_CFG_MM_STOP_INFO_T));
    return MMPR_OK;
}
INT32 video_engine_set_video_last_mem(
					MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
					CHAR* 							ac_filepath,
					BOOL							b_eos
					)
{
	_MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
	MMP_FP_PRESENT_MODE_T	t_present_mode;
	APP_CFG_MM_STOP_INFO_T  t_acfg_stop_info;
    INT32 i4_ret;

    if(NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

	c_memset((VOID*)&t_acfg_stop_info, 0, sizeof(APP_CFG_MM_STOP_INFO_T));

    i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
    if (MMPR_OK != i4_ret)
    {
        t_present_mode = MMP_FP_PRESENT_MODE_FULL;
    }

    if ((MMP_FP_PRESENT_MODE_FULL == t_present_mode) &&
        (MMP_FILE_SRC_MASS_STRG   == pt_elmt->t_file_src) &&
        (b_eos == FALSE))
    {
        if ((_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type) &&
            (_MMP_VE_ELMT_STAT_PLAY== pt_elmt->e_elmt_stat))
        {
			MM_SVC_STOP_INFO t_svc_info;
            SIZE_T           z_size         = 0;

            c_memset(&t_svc_info, 0, sizeof(MM_SVC_STOP_INFO));

            z_size = sizeof(MM_SVC_STOP_INFO);

            i4_ret = c_svctx_get(
                            pt_this->h_svctx_hdl,
                            SVCTX_MM_GET_STOP_INFO,
                            (VOID*)&t_svc_info,
                            &z_size
                            );
            if (SVCTXR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_GET_TYPE_STOP_INFO)returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                i4_ret = MMPR_INTERNAL_ERROR;
                return i4_ret;
            }

	        t_acfg_stop_info.ui8_clip_id            = t_svc_info.ui8_clip_id;
	        t_acfg_stop_info.ui4_title_idx          = t_svc_info.ui4_title_idx;
	        t_acfg_stop_info.ui4_playlist_idx       = t_svc_info.ui4_playlist_idx;
	        t_acfg_stop_info.ui4_chap_idx           = t_svc_info.ui4_chap_idx;
	        t_acfg_stop_info.ui2_aud_idx            = t_svc_info.ui2_aud_idx;
	        t_acfg_stop_info.ui2_sub_idx            = t_svc_info.ui2_sub_idx;
	        t_acfg_stop_info.ui8_aud_pts_info       = t_svc_info.t_mm_svc_pos_info.u.render_info.ui8_aud_pts_info;
	        t_acfg_stop_info.ui8_aud_frame_position = t_svc_info.t_mm_svc_pos_info.u.render_info.ui8_aud_frame_position;
	        t_acfg_stop_info.ui8_i_pts_info         = t_svc_info.t_mm_svc_pos_info.u.render_info.ui8_i_pts_info;
	        t_acfg_stop_info.ui8_pts_info           = t_svc_info.t_mm_svc_pos_info.u.render_info.ui8_pts_info;
	        t_acfg_stop_info.ui8_i_frame_position   = t_svc_info.t_mm_svc_pos_info.u.render_info.ui8_i_frame_position;
	        t_acfg_stop_info.ui8_frame_position     = t_svc_info.t_mm_svc_pos_info.u.render_info.ui8_frame_position;
	        t_acfg_stop_info.i4_temporal_reference  = t_svc_info.t_mm_svc_pos_info.u.render_info.i4_temporal_reference;
	        t_acfg_stop_info.ui2_decoding_order     = t_svc_info.t_mm_svc_pos_info.u.render_info.ui2_decoding_order;
	        t_acfg_stop_info.ui4_timestap           = t_svc_info.t_mm_svc_pos_info.u.render_info.ui4_timestap;
        }
    }
	a_nav_rec_pvr_browser_set_file_state_data(ac_filepath, NAV_REC_PVR_SET_FILE_STATE_STOP_INFO_FLAG, &t_acfg_stop_info);
    return MMPR_OK;;
}

INT32 video_engine_get_video_path(
					CHAR*							ac_filepath
					)
{
	UINT32                 ui4_idx;
	INT32				   i4_ret;
	CHAR 		ac_vp_pvr_filename[MMP_PVR_MAX_PATH_LEN] = {0};

	mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE, MMP_PL_IDX_TYPE_CRNT_PLAY, &ui4_idx);

	c_memset(ac_vp_pvr_filename, 0, MMP_PVR_MAX_PATH_LEN);
	i4_ret = a_nav_rec_pvr_get_file_path(ui4_idx, ac_vp_pvr_filename, MMP_PVR_MAX_PATH_LEN);
	if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO (("{MMP} a_nav_rec_pvr_get_file_path() returns %d.\n", i4_ret));
		return i4_ret;
    }
	c_memcpy(ac_filepath, ac_vp_pvr_filename, MMP_PVR_MAX_PATH_LEN);
	return MMPR_OK;
}
#endif
#endif

#ifdef DIVX_PLUS_CER
static INT32 _video_engine_chap_get_num(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,
                    MMP_VE_CHAP_NUM_PTR_T           pt_chap_num
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    UINT32 ui4_title_num = 0;
    MINFO_CHAP_INFO_T t_cur_chap_info;
    MINFO_TITLE_INFO_T t_title_info, tmp_title_info;
    MINFO_PLAYLIST_INFO_T t_list_info, tmp_list_info;
    MINFO_CHAP_INFO_T t_chap_info, tmp_chap_info;
    SIZE_T z_info_size = 0;
    UINT32 ui4_index;
    INT32 i4_ret;

    if ((NULL == pt_this) || (NULL == pt_chap_num))
    {
        return MMPR_INV_ARG;
    }

    /* Get title number */
    z_info_size = sizeof(UINT32);
    ui4_title_num = (UINT32)0;

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_TITLE_NUM,
                    &ui4_title_num,
                    &z_info_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_GET_TYPE_TITLE_NUM) %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    z_info_size = sizeof(MINFO_CHAP_INFO_T);
    c_memset(&t_cur_chap_info, 0, z_info_size);

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_CUR_POS,
                    &t_cur_chap_info,
                    &z_info_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_GET_TYPE_CUR_POS) %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    pt_elmt->t_chap_num.ui4_title_idx = t_cur_chap_info.ui4_title_idx;
    pt_elmt->t_chap_num.ui4_list_idx  = t_cur_chap_info.ui4_playlist_idx;
    pt_elmt->t_chap_num.ui4_chap_idx  = t_cur_chap_info.ui4_chap_idx;

    /* Get title information */
    z_info_size = sizeof(MINFO_TITLE_INFO_T);
    c_memset(&t_title_info, 0, z_info_size);

    t_title_info.ui4_title_idx = pt_elmt->t_chap_num.ui4_title_idx;

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_TITLE_INFO,
                    &t_title_info,
                    &z_info_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_GET_TYPE_TITLE_INFO) returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    /* Get playlist information */
    z_info_size = sizeof(MINFO_PLAYLIST_INFO_T);

    t_list_info.ui4_title_idx = pt_elmt->t_chap_num.ui4_title_idx;
    t_list_info.ui4_playlist_idx = pt_elmt->t_chap_num.ui4_list_idx;

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_PLAYLIST_INFO,
                    &t_list_info,
                    &z_info_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_get(SVCTX_MM_GET_TYPE_PLAYLIST_INFO) %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        c_memset(&t_list_info, 0, sizeof(t_list_info));
    }

    /* Get chapter information */
    z_info_size = sizeof(MINFO_CHAP_INFO_T);

    t_chap_info.ui4_title_idx = pt_elmt->t_chap_num.ui4_title_idx;
    t_chap_info.ui4_playlist_idx = pt_elmt->t_chap_num.ui4_list_idx;
    t_chap_info.ui4_chap_idx     = pt_elmt->t_chap_num.ui4_chap_idx;

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_CHAP_INFO,
                    &t_chap_info,
                    &z_info_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_get(SVCTX_MM_GET_TYPE_CHAP_INFO) returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        c_memset(&t_chap_info, 0, sizeof(t_chap_info));
    }

    pt_chap_num->ui4_title_num = ui4_title_num;
    pt_chap_num->ui4_title_idx = t_title_info.ui4_title_idx;
    pt_chap_num->ui4_list_num  = t_title_info.ui4_playlist_num;
    pt_chap_num->ui4_list_idx  = t_list_info.ui4_playlist_idx;
    pt_chap_num->ui4_chap_num  = t_list_info.ui4_chapter_num;
    pt_chap_num->ui4_chap_idx  = t_chap_info.ui4_chap_idx;

    z_info_size = 0x80;
    pt_chap_num->t_chap_ext.ui8_title_hide = 0;

    for(ui4_index=0; ui4_index < pt_chap_num->ui4_title_num; ui4_index++)
    {
        tmp_title_info.ui4_title_idx = ui4_index;

        i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_TITLE_INFO,
                        &tmp_title_info,
                        &z_info_size
                        );
        if (SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_get(SVCTX_MM_GET_TYPE_TITLE_INFO) returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }

        if (tmp_title_info.fg_hidden)
        {
            pt_chap_num->t_chap_ext.ui8_title_hide |= ((UINT64)1)<<ui4_index;
        }
    }

    z_info_size = sizeof(MINFO_PLAYLIST_INFO_T);
    pt_chap_num->t_chap_ext.ui8_list_hide = 0;
    tmp_list_info.ui4_title_idx = pt_elmt->t_chap_num.ui4_title_idx;

    for(ui4_index=0; ui4_index < pt_chap_num->ui4_list_num; ui4_index++)
    {
        tmp_list_info.ui4_playlist_idx = ui4_index;

        i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_PLAYLIST_INFO,
                        &tmp_list_info,
                        &z_info_size
                        );
        if (SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_get(SVCTX_MM_GET_TYPE_PLAYLIST_INFO) returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }

        if (tmp_list_info.fg_hidden)
        {
            pt_chap_num->t_chap_ext.ui8_list_hide |= ((UINT64)1)<<ui4_index;
        }
    }

    z_info_size = sizeof(MINFO_CHAP_INFO_T);
    pt_chap_num->t_chap_ext.ui8_chap_hide = 0;
    tmp_chap_info.ui4_title_idx = pt_elmt->t_chap_num.ui4_title_idx;
    tmp_chap_info.ui4_playlist_idx = pt_elmt->t_chap_num.ui4_list_idx;

    for(ui4_index=0; ui4_index < pt_chap_num->ui4_chap_num; ui4_index++)
    {
        tmp_chap_info.ui4_chap_idx = ui4_index;

        i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_CHAP_INFO,
                        &tmp_chap_info,
                        &z_info_size
                        );
        if (SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_get(SVCTX_MM_GET_TYPE_CHAP_INFO) %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }

        if (tmp_chap_info.fg_hidden)
        {
            pt_chap_num->t_chap_ext.ui8_chap_hide |= ((UINT64)1)<<ui4_index;
        }
    }

    MMP_DBG_INFO(("{MMP} IIIIIIIIIIIIIIIIIIIIIIIIIII\n"
               ">> Title    Number = %d\n"
               ">> Title    Index  = %d\n"
               ">> Playlist Number = %d\n"
               ">> Playlist Index  = %d\n"
               ">> Chapter  Number = %d\n"
               ">> Chapter  Index  = %d\n"
               "IIIIIIIIIIIIIIIIIIIIIIIIIII\n",
               pt_chap_num->ui4_title_num,
               pt_chap_num->ui4_title_idx,
               pt_chap_num->ui4_list_num,
               pt_chap_num->ui4_list_idx,
               pt_chap_num->ui4_chap_num,
               pt_chap_num->ui4_chap_idx));

    return MMPR_OK;
}

static INT32 _video_engine_chap_get_meta_data(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,
                    MMP_VE_CHAP_META_DATA_PTR_T     pt_meta_data
                    )
{
    SIZE_T z_size = sizeof(MMP_VE_CHAP_META_DATA_T);
    INT32 i4_ret;

    if (NULL == pt_this || NULL == pt_meta_data)
    {
        return MMPR_INV_ARG;
    }

    if ((pt_meta_data->e_type == MINFO_INFO_DISP_TYPE_SUBTITLE_TRACK_NAME) ||
        (pt_meta_data->e_type == MINFO_INFO_DISP_TYPE_SUBTITLE_TRACK_LANGUAGE))
    {
        if (0 < pt_meta_data->ui4_track_idx)
        {
            pt_meta_data->ui4_track_idx -= 1;
        }
        else
        {
            return MMPR_NO_DATA;
        }
    }

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_DISP_INFO,
                    pt_meta_data,
                    &z_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_GET_TYPE_DISP_INFO) returns %d.\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

static INT32 _video_engine_chap_set_title(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,
                    MMP_VE_TITLE_ID_PTR_T           pt_title_id
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    SRC_MM_INFO_T t_mm = {0};
    VSH_REGION_INFO_T t_vide_rgn = {0};
    VSH_REGION_INFO_T t_disp_rgn = {0};
    VSH_SET_PLANE_ORDER_INFO_T t_vpla_ord;
    SRC_DESC_T t_src_desc = {0};
    SNK_DESC_T t_snk_desc = {0};
    MM_SPEED_TYPE_T e_spd_type = MM_SPEED_TYPE_FORWARD_1X;
    UINT32 ui4_stream_mode = ST_MASK_AUDIO;
    MM_SVC_STOP_INFO t_svc_info;
    MMP_VE_DIVX_CERT_PTR_T pt_divx_cert = &(pt_title_id->e_divx_cert);
    INT32 i4_ret = 0;
	MMP_FP_PRESENT_MODE_T t_present_mode = MMP_FP_PRESENT_MODE_FULL;
    SIZE_T z_size = sizeof(MM_SVC_STOP_INFO);
    MM_SVC_STOP_INFO t_svc_info_track;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }
    c_memset(&t_svc_info, 0, sizeof(MM_SVC_STOP_INFO));
    c_memset(&t_svc_info_track, 0, sizeof(MM_SVC_STOP_INFO));

    t_svc_info_track.ui4_title_idx = pt_title_id->e_divx_cert.ui4_title_id;
    z_size = sizeof(MM_SVC_STOP_INFO);

    i4_ret = c_svctx_get( pt_this->h_svctx_hdl,
                         SVCTX_MM_GET_TYPE_RESUME_TRACK_INFO,
                         (VOID*)&t_svc_info_track,
                         &z_size
                         );
    if (SVCTXR_OK != i4_ret)
    {
       MMP_DBG_INFO(("{MMP}c_svctx_get(SVCTX_MM_GET_TYPE_RESUME_TRACK_INFO) %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

#ifdef APP_LAST_MEMORY_SUPPORT
    if(pt_elmt->t_chap_num.ui4_title_idx != pt_title_id->e_divx_cert.ui4_title_id)
    {
       i4_ret = c_svctx_get( pt_this->h_svctx_hdl,
                             SVCTX_MM_GET_STOP_INFO,
                             (VOID*)&t_svc_info,
                             &z_size
                             );
        if (SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_get(SVCTX_MM_GET_TYPE_RESUME_STOP_INFO) %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }
        t_mm.ui2_aud_idx = video_engine_get_last_mem_audio_play_id();
        t_mm.ui2_sub_idx = video_engine_get_last_mem_subtitle_play_id();
    }
#endif
    i4_ret = video_engine_full_stop_cust((MMP_VE_PLAY_INST_PTR_T)pt_this);
    if (MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        return i4_ret;
    }

    /* divx certification */
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {
        if(NULL == pt_divx_cert)
        {
            MMP_ASSERT(FALSE);
            return MMPR_INV_ARG;
        }

        pt_elmt->t_drm_info.ui4_title_id = pt_divx_cert->ui4_title_id;
        pt_elmt->b_check_yet = FALSE;

        video_engine_divx_cert_cust((MMP_VE_PLAY_INST_PTR_T)pt_this, pt_divx_cert);
    }

    if(MMP_FP_SHOW_ATTR_ID_SPEED == pt_elmt->t_spd_attr.e_id)
    {
        e_spd_type = (MM_SPEED_TYPE_T)(UINT32)pt_elmt->t_spd_attr.pv_param;
    }

    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {
        ui4_stream_mode |= ST_MASK_VIDEO;
    }

    t_mm.h_media = pt_elmt->h_elmt_hdl;
    t_mm.t_speed = e_spd_type;
#ifdef APP_LAST_MEMORY_SUPPORT
    UINT8  ui1_lst_mode     = 0;

    i4_ret = a_cfg_get_mmp_last_memory_onoff(&ui1_lst_mode);
    if (i4_ret != APP_CFGR_OK)
    {
        MMP_DBG_INFO(("{MMP} acfg get_mmp_last_memory_mode error return %d Line %d\n", i4_ret, __LINE__));
    }
    if(ui1_lst_mode == 0)
    {
        t_mm.t_pos_info = t_svc_info.t_mm_svc_pos_info;
    }
    else/*Last Memory = OFF*/
#endif
    {
        t_mm.t_pos_info = t_svc_info_track.t_mm_svc_pos_info;
    }
    t_mm.t_pos_info.t_pos_type = MM_SVC_POS_TYPE_ALL_TIME;
    t_mm.t_pos_info.ui2_idx = (UINT16)0;
    t_mm.ui4_title_idx = t_svc_info.ui4_title_idx;
    t_mm.ui4_playlist_idx = t_svc_info.ui4_playlist_idx;
    t_mm.ui4_chap_idx = t_svc_info.ui4_chap_idx;

#ifdef APP_LAST_MEMORY_SUPPORT
    if(pt_elmt->t_chap_num.ui4_title_idx != pt_title_id->e_divx_cert.ui4_title_id)
    {
        video_engine_set_last_mem_audio_play_id(t_svc_info_track.ui2_aud_idx);
        video_engine_set_last_mem_subtitle_play_id(t_svc_info_track.ui2_sub_idx);
        MMP_DBG_INFO(("{MMP}  title new audidx:%d sbtlidx:%d\n", t_svc_info_track.ui2_aud_idx, t_svc_info_track.ui2_sub_idx));
    }
    video_engine_set_last_mem_audio_num(0);
    video_engine_set_last_mem_sbtl_num(0);
    if (0 != t_svc_info_track.ui2_sub_idx)
    {
        ui4_stream_mode |= ST_MASK_SUBTITLE;
    }
#endif

    t_vide_rgn.ui4_x = 0;
    t_vide_rgn.ui4_y = 0;
    t_vide_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_vide_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;

	i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
	if (MMPR_OK != i4_ret)
	{
		t_present_mode = MMP_FP_PRESENT_MODE_FULL;
	}

    /* set display region */
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {
        if (MMP_FP_PRESENT_MODE_PREVIEW == t_present_mode)
        {
            t_disp_rgn.ui4_x = (pt_this->t_preview_rect.i4_left * VSH_REGION_MAX_WIDTH  + pt_this->t_osd_info.ui2_screen_w / 2) / pt_this->t_osd_info.ui2_screen_w;
            t_disp_rgn.ui4_y = (pt_this->t_preview_rect.i4_top  * VSH_REGION_MAX_HEIGHT + pt_this->t_osd_info.ui2_screen_h / 2) / pt_this->t_osd_info.ui2_screen_h;
            t_disp_rgn.ui4_width  = (RECT_W(&pt_this->t_preview_rect) * VSH_REGION_MAX_WIDTH  + pt_this->t_osd_info.ui2_screen_w / 2) / pt_this->t_osd_info.ui2_screen_w;
            t_disp_rgn.ui4_height = (RECT_H(&pt_this->t_preview_rect) * VSH_REGION_MAX_HEIGHT + pt_this->t_osd_info.ui2_screen_h / 2) / pt_this->t_osd_info.ui2_screen_h;
        }
        else        // Full mode  2
        {
            if (_MMP_VE_ELMT_EFCT_4SM == _MMP_VERC_GET_ELMT_EFFECT())       // s   3
            {
                t_disp_rgn.ui4_x = (UINT32)0;
                t_disp_rgn.ui4_y = (UINT32)0;
                t_disp_rgn.ui4_width  = (UINT32)0;
                t_disp_rgn.ui4_height = (UINT32)0;
            }
            else            // t
            {
                t_disp_rgn.ui4_x = (UINT32)0;
                t_disp_rgn.ui4_y = (UINT32)0;
                t_disp_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
                t_disp_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;
            }
        }
    }
    else
    {
        t_disp_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
        t_disp_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;
		t_disp_rgn.ui4_x = (VSH_REGION_MAX_WIDTH  - t_disp_rgn.ui4_width ) / 2;
		t_disp_rgn.ui4_y = (VSH_REGION_MAX_HEIGHT - t_disp_rgn.ui4_height) / 2;
    }

    t_vpla_ord.e_order_ctrl = VSH_PLANE_ORDER_CTRL_BOTTOM;
    t_vpla_ord.u.ui1_num_layers = 0;

    t_src_desc.e_type = SRC_TYPE_MEDIA_STORGE;
    t_src_desc.u_info.t_mm = t_mm;
    t_src_desc.ui4_title_idx = pt_title_id->e_divx_cert.ui4_title_id;
    t_src_desc.ui4_playlist_idx = 0;
    t_src_desc.ui4_chap_idx = 0;

    t_snk_desc.pt_video_region        = &t_vide_rgn;
    t_snk_desc.pt_disp_region         = &t_disp_rgn;
    t_snk_desc.pt_video_plane_order   = &t_vpla_ord;
    t_snk_desc.pt_video_strm_fltr_fct = video_engine_strm_comp_filter;
    t_snk_desc.pv_video_strm_fltr_tag = (VOID*)pt_this;
    t_snk_desc.pt_audio_strm_fltr_fct = video_engine_strm_comp_filter;
    t_snk_desc.pv_audio_strm_fltr_tag = (VOID*)pt_this;
    t_snk_desc.ps_snk_grp_name        = SN_PRES_MAIN_DISPLAY;

    t_snk_desc.e_text_strm_type       = ST_SUBTITLE; /* To fix DTV00215125 */
    t_snk_desc.u_text_strm.t_subtitle.pt_fltr_fct = video_engine_strm_comp_filter;
    t_snk_desc.u_text_strm.t_subtitle.pv_fltr_tag = (VOID*)pt_this;

    t_snk_desc.u_text_strm.t_subtitle.h_gl_plane = pt_this->t_osd_info.h_canvas_ex;

    i4_ret = c_svctx_select_svc(
                    pt_this->h_svctx_hdl,
                    ui4_stream_mode,
                    &t_src_desc,
                    &t_snk_desc,
                    svctx_media_play_nfy_fct,
                    (VOID*)pt_this
                    );
#ifdef APP_MMP_DBG_FLOW
      MMP_DBG_INFO(("{MMP} c_svctx_select_svc %d %s:%d\r\n", pt_elmt->h_elmt_hdl,__FUNCTION__, __LINE__));
#endif
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_select_svc() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    pt_elmt->t_chap_num.ui4_title_idx = pt_title_id->e_divx_cert.ui4_title_id;
    pt_elmt->t_chap_num.ui4_list_idx = (UINT32)0;
    pt_elmt->t_chap_num.ui4_chap_idx = (UINT32)0;
    pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;

    return MMPR_OK;
}

static INT32 _video_engine_chap_set_chap(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,
                    MMP_VE_CHAP_ID_PTR_T            pt_chap_id
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    MM_SVC_POS_INFO_T    t_pos_set;
    INT32 i4_ret;

    if ((NULL == pt_this) || (NULL == pt_chap_id))
    {
        return MMPR_INV_ARG;
    }

    t_pos_set.t_pos_type = MM_SVC_POS_TYPE_CHAPTER;
    t_pos_set.ui8_pos_val = MM_DIVX_PLUS_ID_TO_POS(pt_chap_id->ui4_list_id, pt_chap_id->ui4_chap_id);

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SET_TYPE_SEEK,
                    (VOID*)&t_pos_set,
                    sizeof(t_pos_set)
                    );
    MMPR_LOG_ON_FAIL(i4_ret);
    if (SVCTXR_OK != i4_ret)
    {
        if(SVCTXR_NOT_SUPPORT == i4_ret)
        {
            return MMPR_NOT_SUPPORT;
        }
        return MMPR_FAIL;
    }

    pt_elmt->t_chap_num.ui4_list_idx = pt_chap_id->ui4_list_id;
    pt_elmt->t_chap_num.ui4_chap_idx = pt_chap_id->ui4_chap_id;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_chap_set_sgmt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 _video_engine_chap_set_sgmt(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,           /* in  */
                    MMP_VE_SGMT_ID_PTR_T            pt_sgmt_id         /* in  */
                    )
{
    MM_SVC_BTN_INFO_T t_btn_set;
    INT32 i4_ret = 0;

    if (NULL == pt_this || NULL == pt_sgmt_id)
    {
        return MMPR_INV_ARG;
    }

    c_memset(&t_btn_set, 0, sizeof(MM_SVC_BTN_INFO_T));

    MMP_DBG_INFO(("{mmp} set sgmt type:%d\n\r",pt_sgmt_id->e_sgmt_type));
    switch(pt_sgmt_id->e_sgmt_type)
    {
        case MMP_VE_SGMT_TYPE_DIGIT:
            t_btn_set.t_btn_type = MM_SVC_BTN_TYPE_SELECT_DIGTS;
            t_btn_set.u.ui4_value = pt_sgmt_id->ui4_sgmt_id;
            break;

        case MMP_VE_SGMT_TYPE_NEXT:
            t_btn_set.t_btn_type = MM_SVC_BTN_TYPE_SELECT_NEXT;
            break;

        case MMP_VE_SGMT_TYPE_PREV:
            t_btn_set.t_btn_type = MM_SVC_BTN_TYPE_SELECT_PREV;
            break;

        default:
            return MMPR_NOT_SUPPORT;
    }

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SET_TYPE_BTN,
                    (VOID*)&t_btn_set,
                    sizeof(MM_SVC_BTN_INFO_T)
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    return MMPR_OK;
}

INT32 video_engine_chap_get(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CHAP_DATA_PTR_T          pt_chap_data      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret;

    if ((NULL == pt_this) || (NULL == pt_chap_data))
    {
        return MMPR_INV_ARG;
    }

    //pt_chap_data->u.t_chap_num.pt_chap_ext = &t_g_chap_num_ext;
    switch (pt_chap_data->e_chap_cmd)
    {
        case MMP_VE_CHAP_CMD_GET_NUM:
        {
            i4_ret = _video_engine_chap_get_num(pt_this, &pt_chap_data->u.t_chap_num);
        }
        break;
        case MMP_VE_CHAP_CMD_GET_META_DATA:
        {
            i4_ret = _video_engine_chap_get_meta_data(pt_this, &pt_chap_data->u.t_meta_data);
        }
        break;
        default:
            return MMPR_INV_ARG;
    }

    return i4_ret;
}

INT32 video_engine_chap_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CHAP_DATA_PTR_T          pt_chap_data      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret;

    if ((NULL == pt_this) || (NULL == pt_chap_data))
    {
        return MMPR_INV_ARG;
    }

    switch (pt_chap_data->e_chap_cmd)
    {
        case MMP_VE_CHAP_CMD_SET_TITLE:
            i4_ret = _video_engine_chap_set_title(pt_this, &pt_chap_data->u.t_title_id);
            break;

        case MMP_VE_CHAP_CMD_SET_CHAP:
            i4_ret = _video_engine_chap_set_chap(pt_this, &pt_chap_data->u.t_chap_id);
            break;

        case MMP_VE_CHAP_CMD_SET_SGMT:
            i4_ret = _video_engine_chap_set_sgmt(pt_this, &pt_chap_data->u.t_sgmt_id);
            break;

        default:
            return MMPR_INV_ARG;
    }

    return i4_ret;
}
#endif

#ifdef APP_MMP_ID3_SUPPORT
/*----------------------------------------------------------------------------
 * Name: video_engine_set_id3_encode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *              Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_set_id3_encode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MM_SBTL_ID3_ENC_T               e_type        /* in */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    if (NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }

    pt_this->e_id3_encode = e_type;

    return MMPR_OK;
}
#endif


/*-----------------------------------------------------------------------------
 * Name
 *      video_engine_svctx_nfy_output
 * Description
 *  update the timestamp for last RC operation
 *
 * Input argumenpvr
 * Output argumenpvr
 * Returns
 *---------------------------------------------------------------------------*/
INT32 video_engine_svctx_nfy_output(SVCTX_NTFY_CODE_T e_nfy_code)
{
    switch(e_nfy_code)
    {
    case SVCTX_NTFY_CODE_MEDIA_LOST:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_LOST\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSING:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSING\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSED\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_ERROR:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_ERROR\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_CHAPTER_UPDATE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_CHAPTER_UPDATE\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_TITLE_UPDATE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_TITLE_UPDATE\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_DURATION_UPDATE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_DURATION_UPDATE\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_AB_REPEAT_DONE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_AB_REPEAT_DONE\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_UOP_INVALID:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_UOP_INVALID\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_SEEK_READY:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_SEEK_READY\n"));
		#ifdef LINUX_AUTO_TEST
			CREATE_MMP_TMP_FILE(mmp_seek_done_file);
		#endif
        break;
    case SVCTX_NTFY_CODE_MEDIA_SPEED_UPDATE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_SPEED_UPDATE\n"));
		#ifdef LINUX_AUTO_TEST
			CREATE_MMP_TMP_FILE(mmp_trick_done_file);
		#endif
        break;
    case SVCTX_NTFY_CODE_MEDIA_SEEK_ERROR:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_SEEK_ERROR\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_REPEAT_DONE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_REPEAT_DONE\n"));
       break;
    case SVCTX_NTFY_CODE_MEDIA_MENU_PRESNT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_MENU_PRESNT\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_EOS:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_EOS\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_AS_CODEC_NOT_SUPPORT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_AS_CODEC_NOT_SUPPORT\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_VS_CODEC_NOT_SUPPORT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_VS_CODEC_NOT_SUPPORT\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_DONE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_DONE\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_HD_NOT_SUPPORT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_HD_NOT_SUPPORT\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_DRM_NOT_SUPPORT:
      MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_DRM_NOT_SUPPORT\n"));
         break;
    case SVCTX_NTFY_CODE_MEDIA_SUBTITLE_FMT_UPDATE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_SUBTITLE_FMT_UPDATE\n"));
        break;
    case SVCTX_NTFY_CODE_REACH_VALID_RANGE_START:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_REACH_VALID_RANGE_START\n"));
        break;
    case SVCTX_NTFY_CODE_REACH_VALID_RANGE_END:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_REACH_VALID_RANGE_END\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_BAD_TICK_Y_TO_N:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_BAD_TICK_Y_TO_N\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_BAD_TICK_N_TO_Y:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_BAD_TICK_N_TO_Y\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_FILE_NOT_SUPPORT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_FILE_NOT_SUPPORT\n"));
        break;

    case SVCTX_NTFY_CODE_MEDIA_FILE_OPER_ERROR:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_FILE_OPER_ERROR\n"));
        break;
#if 0
//#ifdef APP_MMP_PVR_SUPPORT
    case SVCTX_NTFY_CODE_STREAM_OPENED:
        e_ve_nfy_code = MMP_VE_NFY_CODE_STREAM_OPENED;
        break;
#endif

    case SVCTX_NTFY_CODE_MEDIA_RESOLUTION_NOT_SUPPORT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_RESOLUTION_NOT_SUPPORT\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_FRAMERATE_NOT_SUPPORT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_FRAMERATE_NOT_SUPPORT\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_NO_CONTENT:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_NO_CONTENT\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_RANGE_AB_DONE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_RANGE_AB_DONE\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_VIDEO_PRESENT:
       MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_VIDEO_PRESENT\n"));
       break;
    case SVCTX_NTFY_CODE_MEDIA_VS_BIT_RATE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_VS_BIT_RATE\n"));
        break;
    case SVCTX_NTFY_CODE_MEDIA_REPLAY:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_REPLAY\n"));
        break;
    case SVCTX_NTFY_CODE_NONE:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_NONE\n"));
         break;
    case SVCTX_NTFY_CODE_NORMAL:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_NORMAL\n"));
         break;
    case SVCTX_NTFY_CODE_SVCTX_THREAD_KICK_OFF:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SVCTX_THREAD_KICK_OFF\n"));
         break;
    case SVCTX_NTFY_CODE_DELIVERY_SYSTEM_CHANGE:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_DELIVERY_SYSTEM_CHANGE\n"));
         break;
    case SVCTX_NTFY_CODE_SIGNAL_DETECTING:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SIGNAL_DETECTING\n"));
        break;
    case SVCTX_NTFY_CODE_SIGNAL_LOCKED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SIGNAL_LOCKED\n"));
        break;

    case SVCTX_NTFY_CODE_SIGNAL_LOSS:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SIGNAL_LOSS\n"));
        break;
    case SVCTX_NTFY_CODE_INTERRUPTED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_INTERRUPTED\n"));
        break;
    case SVCTX_NTFY_CODE_SERVICE_CHANGING:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SERVICE_CHANGING\n"));
        break;
    case SVCTX_NTFY_CODE_OWN_SERVICE_CHANGING:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_OWN_SERVICE_CHANGING\n"));
        break;

    case SVCTX_NTFY_CODE_SERVICE_BLOCKED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SERVICE_BLOCKED\n"));
        break;
    case SVCTX_NTFY_CODE_SIGNAL_LOSS_AS_BLOCKED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SIGNAL_LOSS_AS_BLOCKED\n"));
        break;
    case SVCTX_NTFY_CODE_SIGNAL_LOCKED_AS_BLOCKED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SIGNAL_LOCKED_AS_BLOCKED\n"));
        break;
    case SVCTX_NTFY_CODE_SERVICE_UNBLOCKED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SERVICE_UNBLOCKED\n"));
        break;
    case SVCTX_NTFY_CODE_STOPPED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_STOPPED\n"));
		#ifdef LINUX_AUTO_TEST
			CREATE_MMP_TMP_FILE(mmp_stop_done_file);
		#endif
        break;
#ifdef APP_MMP_PVR_SUPPORT
    case SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_CANCEL:
	MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_CANCEL\n"));
	break;
#endif
    case SVCTX_NTFY_CODE_CRNT_EVN_START_QUERY:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_CRNT_EVN_START_QUERY\n"));
        break;
    case SVCTX_NTFY_CODE_CRNT_EVN_NOT_READY:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_CRNT_EVN_NOT_READY\n"));
        break;
    case SVCTX_NTFY_CODE_CRNT_EVN_READY:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_CRNT_EVN_READY\n"));
       break;
    case SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_AUDIO_ONLY_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_ONLY_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_ONLY_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_ONLY_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_VIDEO_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_VIDEO_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_CLEAR_VIDEO_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_CLEAR_VIDEO_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_NO_VIDEO_SVC:
      MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_NO_VIDEO_SVC\n"));
         break;
    case SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_CLEAR_AUDIO_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_CLEAR_AUDIO_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_NO_AUDIO_SVC:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_NO_AUDIO_SVC\n"));
        break;
    case SVCTX_NTFY_CODE_AUDIO_ONLY_STRM:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_ONLY_STRM\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_ONLY_STRM:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_ONLY_STRM\n"));
        break;
    case SVCTX_NTFY_CODE_WITH_CC_AVIL_INDICATOR:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_WITH_CC_AVIL_INDICATOR\n"));
        break;
    case SVCTX_NTFY_CODE_NO_CC_AVIL_INDICATOR:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_NO_CC_AVIL_INDICATOR\n"));
        break;
    case SVCTX_NTFY_CODE_EXISTED_CC_IND_CHG:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_EXISTED_CC_IND_CHG\n"));
        break;
    case SVCTX_NTFY_CODE_NO_ANY_STREAM:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_NO_ANY_STREAM\n"));
        break;
    case SVCTX_NTFY_CODE_NO_STREAM:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_NO_STREAM\n"));
        break;
    case SVCTX_NTFY_CODE_STREAM_STOPPED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_STREAM_STOPPED\n"));
        break;

    case SVCTX_NTFY_CODE_STREAM_STARTED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_STREAM_STARTED\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE\n"));
		#ifdef LINUX_AUTO_TEST
			CREATE_MMP_TMP_FILE(mmp_video_fmt_file);
		#endif
        break;
    case SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE:
       MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE\n"));
		#ifdef LINUX_AUTO_TEST
		   CREATE_MMP_TMP_FILE(mmp_audio_fmt_file);
		#endif
       break;
    case SVCTX_NTFY_CODE_VIDEO_AUTO_CLK_POS_PHS_DONE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_AUTO_CLK_POS_PHS_DONE\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_AUTO_COLOR_DONE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_AUTO_COLOR_DONE\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_ANA_COLOR_SYSTEM:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_ANA_COLOR_SYSTEM\n"));
         break;
    case SVCTX_NTFY_CODE_STREAM_STOPPED_AS_BLOCKED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_STREAM_STOPPED_AS_BLOCKED\n"));
         break;
    case SVCTX_NTFY_CODE_STREAM_STARTED_AS_BLOCKED:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_STREAM_STARTED_AS_BLOCKED\n"));
         break;
    case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE_AS_BLOCKED:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE_AS_BLOCKED\n"));
         break;
    case SVCTX_NTFY_CODE_AUDIO_DMUTE_AMUTE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_DMUTE_AMUTE\n"));
        break;
    case SVCTX_NTFY_CODE_AUDIO_DUNMUTE_AMUTE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_DUNMUTE_AMUTE\n"));
        break;

    case SVCTX_NTFY_CODE_AUDIO_DUNMUTE_AUNMUTE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_DUNMUTE_AUNMUTE\n"));
        break;
    case SVCTX_NTFY_CODE_AUDIO_DMUTE_AUNMUTE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_DMUTE_AUNMUTE\n"));
        break;
    case SVCTX_NTFY_CODE_AUDIO_AUTO_MUTE:
      MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_AUTO_MUTE\n"));
         break;
    case SVCTX_NTFY_CODE_AUDIO_AUTO_UNMUTE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_AUTO_UNMUTE\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_AUTO_MUTE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_AUTO_MUTE\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_AUTO_UNMUTE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_AUTO_UNMUTE\n"));
        break;
    case SVCTX_NTFY_CODE_VIDEO_PLAY_DONE:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_VIDEO_PLAY_DONE\n"));
        break;
    case SVCTX_NTFY_CODE_SCDB_ADD:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCDB_ADD\n"));
        break;

    case SVCTX_NTFY_CODE_SCDB_DEL:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCDB_DEL\n"));
        break;
    case SVCTX_NTFY_CODE_SCDB_MODIFY:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_SCDB_MODIFY\n"));
        break;
    case SVCTX_NTFY_CODE_NO_RESOURCES:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_NO_RESOURCES\n"));
        break;

    case SVCTX_NTFY_CODE_INTERNAL_ERROR:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_INTERNAL_ERROR\n"));
        break;
    case SVCTX_NTFY_CODE_CA:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_CA\n"));
        break;
    case SVCTX_NTFY_CODE_CP:
       MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_CP\n"));
       break;

    case SVCTX_NTFY_CODE_TUNER_SIGNAL_LOCKED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_TUNER_SIGNAL_LOCKED\n"));
        break;
    case SVCTX_NTFY_CODE_TUNER_SIGNAL_LOSS:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_TUNER_SIGNAL_LOSS\n"));
        break;
    case SVCTX_NTFY_CODE_CH_SRC_FROM_TUNER:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_CH_SRC_FROM_TUNER\n"));
         break;
    case SVCTX_NTFY_CODE_CH_SRC_FROM_SCART:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_CH_SRC_FROM_SCART\n"));
         break;
    case SVCTX_NTFY_CODE_RF_SCAN_REQUIRED:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_RF_SCAN_REQUIRED\n"));
         break;
    case SVCTX_NTFY_CODE_UNFREEZE:
         MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_UNFREEZE\n"));
         break;
    case SVCTX_NTFY_CODE_TV_SYS_DETECTED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_TV_SYS_DETECTED\n"));
        break;
    case SVCTX_NTFY_CODE_AUD_SYS_DETECTED:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUD_SYS_DETECTED\n"));
        break;

    case SVCTX_NTFY_CODE_PVR_TRICK_REACH_VALID_RANGE_END:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_PVR_TRICK_REACH_VALID_RANGE_END\n"));
        break;

    case SVCTX_NTFY_CODE_AUDIO_DOLBY_ATMOS:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_DOLBY_ATMOS\n"));
        break;

    case SVCTX_NTFY_CODE_AUDIO_DOLBY_NO_ATMOS:
        MMP_DBG_INFO(("{MMP} SVCTX_NTFY_CODE_AUDIO_DOLBY_NO_ATMOS\n"));
        break;

    default:
        MMP_DBG_INFO((" {MMP} NTFY default %d\n",e_nfy_code));
            break;

    }

    return MMPR_OK;
}







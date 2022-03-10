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
#include "video_engine_thumbnail.h"



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


/*-----------------------------------------------------------------------------
 * macros, typedefs, enums
 *---------------------------------------------------------------------------*/
#if defined(_MMP_VERC_PLAY_COVER_SUPPORT)
static  _MMP_VE_INFO_INST_T t_g_info_inst_cover_pic={0};
static  _MMP_VE_PLAY_INST_T t_g_play_inst_cover_pic={0};
static  BOOL                b_g_has_cover_pic=FALSE;
#endif

#ifdef APP_MMP_SHOW_BROKEN_THUMB 
static BOOL g_b_is_parse_ok = FALSE;
static BOOL	b_g_video_codec_not_support = FALSE;
#endif


#if defined(_MMP_VERC_PLAY_COVER_SUPPORT)
static INT32 _mmp_ve_info_cover_pic_close(VOID);
#endif
static VOID _mmp_ve_info_image_open_event_hdlr(
                    VOID*                           pv_pt_info_obj,
                    VOID*                           pv_ui4_ver,
                    VOID*                           pv_unused2,
                    VOID*                           pv_unused3
                    );

static VOID _mmp_ve_info_thumb_open_event_hdlr(
                    VOID*                           pv_pt_info_obj,
                    VOID*                           pv_ui4_ver,
                    VOID*                           pv_unused2,
                    VOID*                           pv_unused3
                    );

#if defined(_MMP_VERC_INFO_COVER_SUPPORT) /* For loading cover picture */
static INT32 _mmp_ve_info_image_open(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj /* in  */
                    );

static INT32 _mmp_ve_info_image_close(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj /* in  */
                    );

static INT32 _mmp_ve_info_image_load(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj,/* in  */
                    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*    pt_param    /* in  */
                    );

static INT32 _mmp_ve_info_image_stop(
                    _MMP_VE_PLAY_INST_PTR_T       pt_this,            /* in  */
                    _MMP_VE_INFO_INST_PTR_T       pt_this_obj         /* in  */
                    );
#endif

#if defined(_MMP_VERC_INFO_THUMB_SUPPORT)
static INT32 _mmp_ve_info_thumb_load(
                    _MMP_VE_PLAY_INST_PTR_T             pt_this,      /* in  */
                    _MMP_VE_INFO_INST_PTR_T             pt_this_obj,  /* in  */
                    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T* pt_param      /* in  */
                    );
static INT32 _mmp_ve_info_thumb_stop(
                    _MMP_VE_PLAY_INST_PTR_T       pt_this,            /* in  */
                    _MMP_VE_INFO_INST_PTR_T       pt_this_obj         /* in  */
                    );

#endif

#if defined(_MMP_VERC_INFO_COVER_SUPPORT) || \
    defined(_MMP_VERC_INFO_THUMB_SUPPORT) || \
    defined(_MMP_VERC_PLAY_COVER_SUPPORT) || \
    defined(_MMP_VERC_PLAY_THUMB_SUPPORT)
/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_lock_thumb_buf
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_thumb_lock_buf(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    BOOL                            b_lock            /* in  */
                    )
{
    INT32   i4_ret = MMPR_OK;

    if (b_lock)
    {
        /*Lock resource from DRC*/
        if (pt_this->pt_buf_thumb_show == NULL)
        {
            i4_ret = mmp_drc_lock_buf(MMP_DRC_RESID_SHOW, &pt_this->pt_buf_thumb_show);
            if(MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
        }

        if (pt_this->pt_buf_thumb_load == NULL)
        {
            i4_ret = mmp_drc_lock_buf(MMP_DRC_RESID_LOAD, &pt_this->pt_buf_thumb_load);
            if(MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
        }

        MMP_DBG_INFO(("$ [lock buff] lock buffer success.\n"));
    }
    else
    {
        /*Unlock resource from DRC*/
        if (NULL != pt_this->pt_buf_thumb_show)
        {
            i4_ret = mmp_drc_unlock_buf(pt_this->pt_buf_thumb_show);
            if(MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
            pt_this->pt_buf_thumb_show = NULL;
        }

        if (NULL != pt_this->pt_buf_thumb_load)
        {
            i4_ret = mmp_drc_unlock_buf(pt_this->pt_buf_thumb_load);
            if(MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
            pt_this->pt_buf_thumb_load = NULL;
        }

        MMP_DBG_INFO(("$ [lock buff] unlock buffer success.\n"));
    }

    return MMPR_OK;
}
#endif

static VOID _mmp_ve_info_splayer_open_nfy_fct(
                                                            VOID*  pv_nfy_code,
                                                            VOID*  pv_tag,
                                                            VOID*  pv_data,
                                                            VOID*  pv_param4
                                                            )
{
    _MMP_VE_INFO_INST_PTR_T pt_info = (_MMP_VE_INFO_INST_PTR_T)pv_param4;
    BOOL b_parse_ok;
    APPL_SPLAYER_INFO_EVENT e_code = (APPL_SPLAYER_INFO_EVENT)pv_nfy_code;

    if(SPLAYER_MM_EVENT_INFO_OPEN_OK == e_code)
    {
        MMP_DBG_INFO(("$ [media open] pasre successfully!\n"));
        b_parse_ok = TRUE;
    }
    else
    {
        MMP_DBG_ERROR(("$ [media open] open nfy return!\n"));
        return;
    }

#ifdef APP_MMP_SHOW_BROKEN_THUMB
    g_b_is_parse_ok = b_parse_ok;
#endif

    DBG_LOG_PRINT(("[%s %d]pt_info->e_elmt_type == %d\n",__FUNCTION__,__LINE__,pt_info->e_elmt_type));
    if(_MMP_VE_ELMT_TYPE_AUDIO == pt_info->e_elmt_type)
    {
        mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_ve_info_image_open_event_hdlr,
                        (VOID*)pt_info,
                        NULL,
                        (VOID*)(UINT32)b_parse_ok,
                        NULL
                        );
    }
    else if(_MMP_VE_ELMT_TYPE_VIDEO == pt_info->e_elmt_type)
    {
        mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_ve_info_thumb_open_event_hdlr,
                        (VOID*)pt_info,
                        NULL,
                        (VOID*)(UINT32)b_parse_ok,
                        NULL
                        );
    }
}
static VOID _mmp_vp_info_eventCallback(APPL_SPLAYER_INFO_EVENT e_nfy_code, VOID *pvTag, UINT32 u4Data,VOID *pvPara)
{
    mmp_mc_event_switch_context(
                                MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_ve_info_splayer_open_nfy_fct,
                                (VOID*)(UINT32)e_nfy_code,
                                (VOID*)pvTag,
                                (VOID*)(UINT32)u4Data,
                                (VOID*)pvPara);
}
#if NEVER
static VOID _mmp_ve_info_media_open_nfy_fct(
                    HANDLE_T                        h_svctx,
                    SVCTX_COND_T                    e_nfy_cond,
                    SVCTX_NTFY_CODE_T               e_code,
                    STREAM_TYPE_T                   e_stream_type,
                    VOID*                           pv_nfy_tag,
                    VOID*                           pv_data
                    )
{
    _MMP_VE_INFO_INST_PTR_T pt_info = (_MMP_VE_INFO_INST_PTR_T)pv_nfy_tag;
    BOOL b_parse_ok;
 
    if(SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSED == e_code)
    {
        MMP_DBG_INFO(("$ [media open] pasre successfully!\n"));
        b_parse_ok = TRUE;
    }
    else if(SVCTX_NTFY_CODE_MEDIA_ERROR == e_code || 
            SVCTX_NTFY_CODE_MEDIA_FILE_NOT_SUPPORT == e_code || 
            SVCTX_NTFY_CODE_MEDIA_FILE_OPER_ERROR == e_code)
    {
        MMP_DBG_INFO(("$ [media open] parse error!\n"));
#ifdef APP_MMP_SHOW_BROKEN_THUMB        
        MMPR_LOG_ON_FAIL (mmp_thumbnailmode_view_show_broken());
#endif
        b_parse_ok = FALSE;
    }
    else
    {
        MMP_DBG_ERROR(("$ [media open] open nfy return!\n"));
        return;
    }

#ifdef APP_MMP_SHOW_BROKEN_THUMB
    g_b_is_parse_ok = b_parse_ok;
#endif
    if(_MMP_VE_ELMT_TYPE_AUDIO == pt_info->e_elmt_type)
    {
        mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_ve_info_image_open_event_hdlr,
                        (VOID*)pt_info,
                        (VOID*)pt_info->ui4_info_ver,
                        (VOID*)(UINT32)b_parse_ok,
                        NULL
                        );
    }
    else if(_MMP_VE_ELMT_TYPE_VIDEO == pt_info->e_elmt_type)
    {
        mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_ve_info_thumb_open_event_hdlr,
                        (VOID*)pt_info,
                        (VOID*)pt_info->ui4_info_ver,
                        (VOID*)(UINT32)b_parse_ok,
                        NULL
                        );
    }
}
#endif

static VOID _mmp_ve_info_thumb_open_event_hdlr(
                    VOID*                           pv_pt_info_obj,
                    VOID*                           pv_ui4_ver,
                    VOID*                           pv_parse_ret,
                    VOID*                           pv_unused1
                    )
{
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = NULL;
    _MMP_VE_ELMT_STAT_T e_elm_priv_stat;
    BOOL b_parse_ok = (BOOL)(UINT32)pv_parse_ret;
#ifdef APP_MMP_SHOW_BROKEN_THUMB    
    MINFO_INFO_T t_minfo_rec;
    SIZE_T z_size = sizeof(MINFO_INFO_T);
#endif   

    if(NULL == pv_pt_info_obj)
    {
        MMP_DBG_ERROR(("$ [media open] open event null handler!\n"));
        MMP_ASSERT(0);
        return;
    }
    pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pv_pt_info_obj;
#ifdef NEVER
    /**/
    if(pt_this_obj->ui4_info_ver != (UINT32)(pv_ui4_ver))
    {
        /*notification is out of date*/
        MMP_DBG_INFO(("$ [media open] open event out of date\n"));
        return;
    }
#endif
    MMP_ASSERT(pt_this_obj->pf_info_nfy_fct);

    if(VIDEO_ENGINE_INFO_FLAG_STOPING & pt_this_obj->ui1_flag)
    {
        MMP_DBG_INFO(("$ [media open] exit for thumb stoping.\n"));
        return;
    }

    e_elm_priv_stat = pt_this_obj->e_elmt_stat;

    if(TRUE == b_parse_ok)
    {
        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_READY;
    }
    else
    {
        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_ERROR;
    }

    if(TRUE == b_parse_ok)
    {
#if defined(_MMP_VERC_INFO_THUMB_SUPPORT)
        INT32 i4_ret = MMPR_OK;
#ifdef APP_MMP_SHOW_BROKEN_THUMB
        i4_ret = c_svctx_media_get_info(
                        ((_MMP_VE_PLAY_INST_PTR_T)(pt_this_obj->pt_play_inst))->h_svctx_hdl,
                        pt_this_obj->h_elmt_hdl,
                        SVCTX_MM_GET_TYPE_MEDIA_FORMAT,
                        (VOID*)&t_minfo_rec,
                        z_size
                        );
        MMP_DBG_INFO(("{MMP} c_svctx_media_get_info() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        if(SVCTXR_OK == i4_ret)
        {
            pt_this_obj->t_elmt_fmt = t_minfo_rec.t_format;
            if(_MMP_VE_ELMT_TYPE_VIDEO == pt_this_obj->e_elmt_type)
            {
                if(!FMT_IS_VIDEO_CATEGORY(pt_this_obj->t_elmt_fmt))
                {
                   MMPR_LOG_ON_FAIL (mmp_thumbnailmode_view_show_broken()); 
                }
            }
        }
                
#endif

        if(_MMP_VE_ELMT_STAT_WAIT == e_elm_priv_stat)
        {
            MMP_DBG_INFO(("$ [media open] thumb loading...\n"));
            i4_ret = _mmp_ve_info_thumb_load(
                                            (_MMP_VE_PLAY_INST_PTR_T)pt_this_obj->pt_play_inst,
                                            pt_this_obj,
                                            NULL
                                            );
            if(MMPR_OK != i4_ret)
            {
                pt_this_obj->pf_info_nfy_fct(
                                            pt_this_obj->pv_info_nfy_tag,
                                            pt_this_obj,
                                            MMP_FP_INFO_NFY_ID_THUMBNAIL,
                                            (VOID*)(UINT32)FALSE
                                            );
            }
        }
        else
#endif
        {
            MMP_DBG_INFO(("$ [media info] info ready...\n"));
            pt_this_obj->pf_info_nfy_fct(
                                        pt_this_obj->pv_info_nfy_tag,
                                        pt_this_obj,
                                        MMP_FP_INFO_NFY_ID_INFO_READY,
                                        (VOID*)(UINT32)TRUE
                                        );
        }
    }
    else if(_MMP_VE_ELMT_STAT_WAIT == e_elm_priv_stat)
    {
        pt_this_obj->pf_info_nfy_fct(
                        pt_this_obj->pv_info_nfy_tag,
                        pt_this_obj,
                        MMP_FP_INFO_NFY_ID_THUMBNAIL,
                        (VOID*)(UINT32)FALSE
                        );
    }
    else
    {
        pt_this_obj->pf_info_nfy_fct(
                        pt_this_obj->pv_info_nfy_tag,
                        pt_this_obj,
                        MMP_FP_INFO_NFY_ID_INFO_READY,
                        (VOID*)(UINT32)FALSE
                        );
    }
}


static VOID _mmp_ve_info_image_open_event_hdlr(
                    VOID*                           pv_info_obj,
                    VOID*                           pv_ui4_ver,
                    VOID*                           pv_parse_ret,
                    VOID*                           pv_unused1
                    )
{
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pv_info_obj;
    
    BOOL                    b_parse_ok = (BOOL)(UINT32)pv_parse_ret;
     _MMP_VE_ELMT_STAT_T    e_elm_priv_stat;

    if(NULL == pt_this_obj)
    {
        MMP_DBG_ERROR(("$ [media open] open event null handler!\n"));
        MMP_ASSERT(0);
        return;
    }
#ifdef NEVER
    /**/
    if(pt_this_obj->ui4_info_ver != (UINT32)(pv_ui4_ver))
    {
        /*notification is out of date*/
        MMP_DBG_INFO(("$ [media open] open event out of data.\n"));
        return;
    }
#endif
    MMP_ASSERT(pt_this_obj->pf_info_nfy_fct);

    if(VIDEO_ENGINE_INFO_FLAG_STOPING & pt_this_obj->ui1_flag)
    {
        MMP_DBG_INFO(("$ [media open] exit for thumb stoping.\n"));
        return;
    }
    
    e_elm_priv_stat = pt_this_obj->e_elmt_stat;
    
    if(b_parse_ok)
    {
        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_READY;
    }
    else
    {
        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_ERROR;
    }

    MMP_DBG_INFO(("$ [media open event] %s,%d,b_parse_ok:%d,stat:%d\n\r",__FILE__,__LINE__,b_parse_ok,e_elm_priv_stat));
    if(b_parse_ok)   
    {
        if(_MMP_VE_ELMT_STAT_WAIT == e_elm_priv_stat)
        {
        #if defined(_MMP_VERC_INFO_COVER_SUPPORT)
            MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T  t_param ;
            INT32                      i4_ret  = MMPR_OK;
            _MMP_VE_PLAY_INST_PTR_T    pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_this_obj->pt_play_inst;
            BOOL                       b_success = TRUE;

            t_param.pt_rect     = &pt_this_obj->t_bound_rect;
            t_param.e_coords    = pt_this_obj->e_coords;
            t_param.e_rotate_op = pt_this_obj->e_rotate_op;

            i4_ret = _mmp_ve_info_image_load(pt_this, pt_this_obj, &t_param);
            if(i4_ret != MMPR_OK)
            {
                MMP_DBG_INFO(("_mmp_ve_info_image_load return fail:%d,line:%d try to load next\r\n",i4_ret,__LINE__));
                b_success = FALSE;
                if(NULL != pt_this_obj->pf_info_nfy_fct)
                {
                    
                    pt_this_obj->pf_info_nfy_fct(
                                pt_this_obj->pv_info_nfy_tag,
                                pt_this_obj,
                                MMP_FP_INFO_NFY_ID_THUMBNAIL,
                                (VOID *)(UINT32)b_success
                                );
                }
            }
        #endif
        }
        else
        {
            pt_this_obj->pf_info_nfy_fct(
                            pt_this_obj->pv_info_nfy_tag,
                            pt_this_obj,
                            MMP_FP_INFO_NFY_ID_INFO_READY,
                            (VOID*)(UINT32)FALSE
                            );
        }
    }
    else if(_MMP_VE_ELMT_STAT_WAIT == e_elm_priv_stat)
    {
        pt_this_obj->pf_info_nfy_fct(
                        pt_this_obj->pv_info_nfy_tag,
                        pt_this_obj,
                        MMP_FP_INFO_NFY_ID_THUMBNAIL,
                        (VOID*)(UINT32)FALSE
                        );
    }
    else
    {
        pt_this_obj->pf_info_nfy_fct(
                        pt_this_obj->pv_info_nfy_tag,
                        pt_this_obj,
                        MMP_FP_INFO_NFY_ID_INFO_READY,
                        (VOID*)(UINT32)FALSE
                        );
    }
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static APPL_SPLAYER_MEDIA_INFO_T tMediaInfo;

INT32 mmp_ve_info_open(
                            MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                            const CHAR*                     ps_info_name,     /* in  */
                            mmp_fp_info_nfy_fct             pf_info_nfy,      /* in  */
                            VOID*                           pv_info_nfy_tag,  /* in  */
                            MMP_VE_INFO_INST_PTR_T*         ppt_info_inst     /* out */
                            )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_INFO_INST_PTR_T pt_info = NULL;
    MM_SVC_COMMAND_T at_cmd[6];
    UINT8 ui1_cmd_num = 0;
#ifdef APP_NETWORK_SUPPORT
    MMP_FILE_SRC_TYPE_T e_file_src_type;
    SRC_TYPE_T e_mm_src_type;
    MMP_UTIL_INFO_T t_util_info;
    BOOL b_has_info = FALSE;
    c_memset(&t_util_info,0,sizeof(MMP_UTIL_INFO_T));
#endif
    BOOL b_match = FALSE;
    UINT32 i = 0;
    INT32 i4_ret = 0;

    MMP_DBG_INFO(("$ [media open] begin...\n"));
    MMP_ASSERT(NULL != pt_this && NULL != ps_info_name && NULL != pf_info_nfy && NULL != ppt_info_inst); 
    
    for(i = 0; i < _MMP_VERC_INFO_INST_NUM; i++)
    {
        if(0 == pt_this->at_info_inst[i].ui4_info_ver)
        {
            pt_info = &pt_this->at_info_inst[i];
            VIDEO_ENGINE_INFO_RESET(*pt_info);
            break;
        }
    }

    if(_MMP_VERC_INFO_INST_NUM == i)
    {
        return MMPR_OUT_OF_LIMIT;
    }

    pt_info->pf_info_nfy_fct = pf_info_nfy;
    pt_info->pv_info_nfy_tag = pv_info_nfy_tag;
    pt_info->pt_play_inst = pt_play_inst;
    pt_info->ui4_info_ver = (VIDEO_ENGINE_INFO_VER_INVALID == (++pt_this->ui4_info_id_counter)) ? (++pt_this->ui4_info_id_counter) : pt_this->ui4_info_id_counter;
    pt_info->ui4_load_ver = VIDEO_ENGINE_LOAD_VER_INVALID;
    
    do
    {
        i4_ret = mmp_util_filter_fct_by_audio(NULL, 0, ps_info_name, 0, &b_match, NULL);
        if(MMPR_OK == i4_ret && TRUE == b_match)
        {
            pt_info->e_elmt_type = _MMP_VE_ELMT_TYPE_AUDIO;
            break;
        }

        i4_ret = mmp_util_filter_fct_by_video(NULL, 0, ps_info_name, 0, &b_match, NULL);
        if(MMPR_OK == i4_ret && TRUE == b_match)
        {
            pt_info->e_elmt_type = _MMP_VE_ELMT_TYPE_VIDEO;
            break;
        }

        pt_info->h_elmt_hdl = NULL_HANDLE;
        return MMPR_NOT_SUPPORT;
    }while(0);

    do
    {
        at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_MEDIA_PATH;
        at_cmd[ui1_cmd_num].u.ps_text = (CHAR*)ps_info_name;
        ui1_cmd_num++;

#ifdef APP_NETWORK_SUPPORT
        /* Get source type according to file name */
        i4_ret = mmp_util_get_file_src_type(ps_info_name, &e_file_src_type);
        if(MMPR_OK != i4_ret)
        {
            e_file_src_type = MMP_FILE_SRC_MASS_STRG;
        }

        switch (e_file_src_type)
        {
            case MMP_FILE_SRC_DLNA:
            case MMP_FILE_SRC_NET_NEIGHBOR:
                e_mm_src_type = SRC_TYPE_MEDIA_NETWORK;
                break;
        
            default:
                e_mm_src_type = SRC_TYPE_MEDIA_STORGE;
                break;
        }
        
        at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SRC_TYPE;
        at_cmd[ui1_cmd_num].u.ui1_data = e_mm_src_type;
        ui1_cmd_num++;
        
        if(MMP_FILE_SRC_DLNA == e_file_src_type)
        {
            t_util_info.e_type = MMP_UTIL_IT_STRM_INFO;
            i4_ret = pt_this->pf_get_media_info_fct(
                                  ps_info_name,
                                  &b_has_info,
                                  &t_util_info
                                  );
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} pt_this->pf_get_media_info_fct() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                break;
            }

            if(TRUE == b_has_info)
            {
                at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_STRM_INFO;
                at_cmd[ui1_cmd_num].u.pv_data = &t_util_info.u.t_strm_info;
                ui1_cmd_num++;
            }
            
            at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_PROTOCL;
            at_cmd[ui1_cmd_num].u.ui4_data = PROTOCL_MODE_DLNA;
            ui1_cmd_num++;
        }
        else if (MMP_FILE_SRC_NET_NEIGHBOR == e_file_src_type)
        {
            at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_PROTOCL;
            at_cmd[ui1_cmd_num].u.ui4_data = PROTOCL_MODE_UNKNOWN;
            ui1_cmd_num++;
        }
#endif

        /* To fix DTV00096439 */
        at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_PLAY_MODE;
        at_cmd[ui1_cmd_num].u.ui1_data = (UINT8)MM_PLAY_MODE_PREV;
        ui1_cmd_num++;
        
        at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_END;

        /* keep filename */
        i4_ret = mmp_fid_add(ps_info_name, &pt_info->t_elmt_fid);
        if(MMPR_OK != i4_ret)
        {
            pt_info->t_elmt_fid = MMP_FID_NULL_REC_IDX;
            break;
        }

        MMP_DBG_INFO(("{MMP} $~~~~~~~~~~~~~~~~~~~~ >>>>>>>>>>>>>>>>>>>> [media open] $%d$ %s\n", pt_info->ui4_info_ver, ps_info_name));
#ifdef NEVER
    #ifdef ENABLE_MULTIMEDIA
        i4_ret = c_svctx_media_open(
                        pt_this->h_svctx_hdl,
                        at_cmd,
                        _mmp_ve_info_media_open_nfy_fct,
                        pt_info,
                        &pt_info->h_elmt_hdl
                        );
#ifdef APP_MMP_DBG_FLOW
        MMP_DBG_INFO(("{MMP} c_svctx_media_open %d %s:%d\r\n", pt_info->h_elmt_hdl,__FUNCTION__, __LINE__)); 
#endif
#else
        i4_ret = SVCTXR_NOT_SUPPORT;
#endif
        if(SVCTXR_OK != i4_ret)
        {
            pt_info->h_elmt_hdl = NULL_HANDLE;
            MMP_DBG_INFO(("{MMP}c_svctx_media_open() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }
#else
        c_memset(&tMediaInfo, 0, sizeof(APPL_SPLAYER_MEDIA_INFO_T));

        i4_ret =_appl_splayer_open_info(ps_info_name,
                                        _mmp_vp_info_eventCallback, 
                                        &tMediaInfo,
                                        (void *)pt_info);
        if(APPL_SPLAYER_SUCCESS != i4_ret)
        {
            MMP_DBG_ERROR(("{MMP}[%s:%d]_appl_splayer_open_info failed. returns: %d\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }
        else
        {
            MMP_DBG_INFO(("$ [media open] open file %s...\n", ps_info_name));
            MMP_DBG_INFO(("$ [media open] file handle = %08x\n", tMediaInfo.hMm));
            MMP_DBG_INFO(("$ [media open] file u64CallbackId = %08x\n", tMediaInfo.u64CallbackId));
            MMP_DBG_INFO(("$ [media open] file hAout = %08x\n", tMediaInfo.hAout));
            MMP_DBG_INFO(("$ [media open] file hDisp = %08x\n", tMediaInfo.hDisp));
        }
#endif

        *ppt_info_inst = (MMP_VE_INFO_INST_PTR_T)pt_info;

        MMP_DBG_INFO(("$ [media open] end.\n"));

        return MMPR_OK;

    }while(0);

    mmp_ve_info_close(pt_play_inst, (MMP_VE_INFO_INST_PTR_T)pt_info);

    return MMPR_NOT_SUPPORT;
}

/*-----------------------------------------------------------------------------
 * Name: video_engine_info_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_info_close(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,    /* in  */
                    MMP_VE_INFO_INST_PTR_T          pt_info_inst     /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pt_info_inst;
    INT32 i4_ret = 0;
    MMP_DBG_INFO(("$ [%s %d] begin...\n",__FUNCTION__,__LINE__));

    MMP_DBG_INFO(("$ [media close] begin...\n"));

    MMP_ASSERT(NULL != pt_this);

    if(NULL == pt_this_obj)
    {
        return MMPR_OK;
    }

#if defined(_MMP_VERC_INFO_COVER_SUPPORT)
    _mmp_ve_info_image_close(pt_this, pt_this_obj);
#endif

    /* free path */
    if(MMP_FID_NULL_REC_IDX != pt_this_obj->t_elmt_fid)
    {
#if 1 /* Only for test*/
        CHAR* ps_media_name = NULL;
        i4_ret = mmp_fid_get(pt_this_obj->t_elmt_fid, &ps_media_name);
        MMPR_LOG_ON_FAIL(i4_ret);
        MMP_DBG_INFO(("{MMP} $~~~~~~~~~~~~~~~~~~~~ <<<<<<<<<<<<<<<<<<<< [media close] $%d$ %s\n", pt_this_obj->ui4_info_ver, ps_media_name));
#endif
        i4_ret = mmp_fid_del(pt_this_obj->t_elmt_fid);
        if(MMPR_OK != i4_ret)
        {
            MMP_ASSERT(FALSE);
        }
    }

    if(NULL_HANDLE != tMediaInfo.hMm)
    {
#ifdef NEVER
        if(VIDEO_ENGINE_INFO_FLAG_LOADING == pt_this_obj->ui1_flag)
        {
#if defined(_MMP_VERC_INFO_THUMB_SUPPORT)
            if(_MMP_VE_ELMT_TYPE_VIDEO == pt_this_obj->e_elmt_type)
            {
            #ifdef ENABLE_MULTIMEDIA
                i4_ret = c_svctx_media_sync_cancel_load_thumbnail(
                              pt_this->h_svctx_hdl,
                              pt_this_obj->h_elmt_hdl
                              );
            #else
                i4_ret = SVCTXR_NOT_SUPPORT;
            #endif
                if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
                {
                    MMP_DBG_INFO(("{MMP}c_svctx_media_sync_cancel_load_thumbnail() %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                }
            }

            i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP}[stop thumb] unlock buffer failed. %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                return MMPR_FAIL;
            }
#endif
        }

#ifdef ENABLE_MULTIMEDIA
        i4_ret = c_svctx_media_close(
                        pt_this->h_svctx_hdl,
                        pt_this_obj->h_elmt_hdl
                        );
        MMP_DBG_INFO(("{MMP} c_svctx_media_close %d %d %s:%d\r\n", pt_this_obj->h_elmt_hdl,i4_ret,__FUNCTION__, __LINE__)); 
#else
        i4_ret = SVCTXR_NOT_SUPPORT;
#endif
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_media_close%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            MMP_ASSERT(FALSE);
        }
#else
        i4_ret = _appl_splayer_close_info(&tMediaInfo);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}close failed. %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }
#endif
    }

    VIDEO_ENGINE_INFO_RESET(*pt_this_obj);
    MMP_DBG_INFO(("$ [media close] info reset end.\n"));

    return MMPR_OK;
}
INT32 video_engine_get_music_cover(APPL_SPLAYER_MUSIC_COVER_T *p_tMusicCoverInfo)
{
    INT32 i4_ret = 0;
    DBG_LOG_PRINT(("**  *** %s,%d\r\n",__FUNCTION__,__LINE__));

    if(tMediaInfo.hMm != NULL)
    {
        i4_ret = _appl_splayer_get_music_cover(tMediaInfo.filePath, &tMediaInfo);
        if(APPL_SPLAYER_SUCCESS != i4_ret)
        {
            MMP_DBG_ERROR(("{MMP}[%s:%d]_appl_splayer_get_music_cover failed. returns: %d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }
        else
        {
            p_tMusicCoverInfo->b_pic_exist = tMediaInfo.b_pic_exist;
            p_tMusicCoverInfo->h_cover_img = tMediaInfo.h_cover_img;
            //p_tMusicCoverInfo->t_img = tMediaInfo.t_img;
            p_tMusicCoverInfo->u32PictureSize = tMediaInfo.u32PictureSize;
        }
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: video_engine_info_get
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_info_get(
                            MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                            MMP_VE_INFO_INST_PTR_T          pt_info_inst,     /* in  */
                            MMP_FP_INFO_TYPE_T              e_info_type,      /* in  */
                            SIZE_T*                         pz_size,          /* in/out */
                            UTF16_T*                        pv_buf            /* in/out */
                            )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pt_info_inst;
    MMP_VE_INFO_ID_T e_info_id;
    INT32 i4_ret = MMPR_OK;

    if(NULL == pt_this || NULL == pt_this_obj)
    {
        return MMPR_OK;
    }

    switch(e_info_type)
    {
        case MMP_FP_INFO_TYPE_TITLE :
            e_info_id = MMP_VE_INFO_ID_TITLE;
            break;

        case MMP_FP_INFO_TYPE_DATE:
            e_info_id = MMP_VE_INFO_ID_DATE;
            break;

        case MMP_FP_INFO_TYPE_GENRE:
            e_info_id = MMP_VE_INFO_ID_GENRE;
            break;

        case MMP_FP_INFO_TYPE_DIRECTOR:
            e_info_id = MMP_VE_INFO_ID_DIRECTOR;
            break;

        case MMP_FP_INFO_TYPE_PRODUCER:
            e_info_id = MMP_VE_INFO_ID_COPYRIGHT;
            break;

        case MMP_FP_INFO_TYPE_DURATION:
            e_info_id = MMP_VE_INFO_ID_DURATION;
            break;
            
        case MMP_FP_INFO_TYPE_SIZE:
            e_info_id = MMP_VE_INFO_ID_SIZE;
            break;
            
        case MMP_FP_INFO_TYPE_ARTIST:
            e_info_id = MMP_VE_INFO_ID_ARTIST;
            break;

        case MMP_FP_INFO_TYPE_ALBUM:
            e_info_id = MMP_VE_INFO_ID_ALBUM;
            break;

        case MMP_FP_INFO_TYPE_PROTECT:
            e_info_id = MMP_VE_INFO_ID_PROTECT;
            break;

        case MMP_FP_INFO_TYPE_RESOLUTION:
            e_info_id = MMP_VE_INFO_ID_RESOLUTION;
            break;

        case MMP_FP_INFO_TYPE_CREATE_TIME:
            e_info_id = MMP_VE_INFO_ID_CREATE_TIME;
            break;

        case MMP_FP_INFO_TYPE_LAST_WRITE_TIME:
            e_info_id = MMP_VE_INFO_ID_MODIFY_TIME;
            break;

        case MMP_FP_INFO_TYPE_YEAR:
            e_info_id = MMP_VE_INFO_ID_YEAR;
            break;

        case MMP_FP_INFO_TYPE_NAME:
            e_info_id = MMP_VE_INFO_ID_NAME;
            break;

        default:
            e_info_id = MMP_VE_INFO_ID_INVAL;
    }

    //MMP_DBG_INFO(("$ [info get] file handle = %08x\n", pt_this_obj->h_elmt_hdl));
    MMP_DBG_INFO(("$ [info get] tMediaInfo.hMm = %08x\n", tMediaInfo.hMm));

    switch(e_info_id)
    {
        case MMP_VE_INFO_ID_TITLE:
        case MMP_VE_INFO_ID_DATE:
        case MMP_VE_INFO_ID_GENRE:
        case MMP_VE_INFO_ID_DIRECTOR:
        case MMP_VE_INFO_ID_COPYRIGHT:
        case MMP_VE_INFO_ID_DURATION:
        case MMP_VE_INFO_ID_ARTIST:
        case MMP_VE_INFO_ID_ALBUM:
        case MMP_VE_INFO_ID_RESOLUTION:
        case MMP_VE_INFO_ID_YEAR:
            DBG_LOG_PRINT(("[%s %d]Ready to get info\n",__FUNCTION__,__LINE__));

            i4_ret = video_engine_get_meta_data(
                                                pt_this,
                                                tMediaInfo.hMm,
                                                e_info_id,
                                                pv_buf,
                                                pz_size
                                                );
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP}_video_engine_get_meta_data returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                return i4_ret;
            }

        break;

        case MMP_VE_INFO_ID_NAME:
        case MMP_VE_INFO_ID_PROTECT:
        case MMP_VE_INFO_ID_CREATE_TIME:
        case MMP_VE_INFO_ID_MODIFY_TIME:
        case MMP_VE_INFO_ID_SIZE:
            i4_ret = video_engine_get_file_data(
                            pt_this,
                            pt_this_obj->t_elmt_fid,
                            e_info_id,
                            pv_buf,
                            pz_size
                            );
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP}video_engine_get_file_data %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                return i4_ret;
            }
            break;

        default:
            return MMPR_NOT_SUPPORT;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_info_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_INST_PTR_T          pt_info_inst,     /* in  */
                    MMP_FP_INFO_TYPE_T              e_info_type,      /* in  */
                    SIZE_T*                         pz_size,          /* in  */
                    UINT8*                          pui1_buf          /* in  */
                    )
{
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: video_engine_info_cmd_do
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_info_cmd_do(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_INST_PTR_T          pt_info_inst,     /* in  */
                    MMP_FP_INFO_CMD_ID_T            e_info_cmd,
                    VOID*                           pv_info_cmd_tag
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pt_info_inst;
    INT32 i4_ret = MMPR_OK;

    if(NULL == pt_this || NULL == pt_this_obj)
    {
        return MMPR_INV_ARG;
    }

    switch(e_info_cmd)
    {
        case MMP_FP_INFO_CMD_ID_LOAD_THUMB : /* argument: a pointer to MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T variable */
        {
            MMP_DBG_INFO(("$ [cmd do] load thumb...\n"));
            if(NULL == pv_info_cmd_tag)
            {
                MMP_DBG_INFO(("{MMP}pv_cmd_param  cannot be NULL.%s:%d\r\n", __FUNCTION__, __LINE__));
                return MMPR_INV_ARG;
            }

            if(_MMP_VE_ELMT_TYPE_AUDIO == pt_this_obj->e_elmt_type)
            {
#if defined(_MMP_VERC_INFO_COVER_SUPPORT)
                MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T* pt_param = (MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*)pv_info_cmd_tag;
                if((NULL == pt_param->pt_rect) ||
                    WGL_RECT_IS_EMPTY(pt_param->pt_rect))
                {                   
                    i4_ret = MMPR_INV_ARG;
                    MMP_DBG_ERROR(("{mmp}null handle %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
                }
                c_memcpy(&pt_this_obj->t_bound_rect , pt_param->pt_rect ,sizeof(GL_RECT_T));
                pt_this_obj->e_coords     = pt_param->e_coords;
                pt_this_obj->e_rotate_op  = pt_param->e_rotate_op;
                
                i4_ret = _mmp_ve_info_image_load(pt_this, pt_this_obj, pv_info_cmd_tag);
                MMP_DBG_INFO(("{mmp}audio load image %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
#else
                i4_ret = MMPR_OK;
#endif
            }
            else if(_MMP_VE_ELMT_TYPE_VIDEO == pt_this_obj->e_elmt_type)
            {
#if defined(_MMP_VERC_INFO_THUMB_SUPPORT)
                i4_ret = _mmp_ve_info_thumb_load(pt_this, pt_this_obj, pv_info_cmd_tag);
#else
                i4_ret = MMPR_OK;
#endif
            }
            else
            {
                i4_ret = MMPR_NOT_SUPPORT;
            }
        }
        break;

        case MMP_FP_INFO_CMD_ID_STOP_THUMB : /* argument: NULL */
        {
            MMP_DBG_INFO(("$ [cmd do] stop thumb...\n"));

            if(_MMP_VE_ELMT_TYPE_AUDIO == pt_this_obj->e_elmt_type)
            {
#if defined(_MMP_VERC_INFO_COVER_SUPPORT)
                i4_ret = _mmp_ve_info_image_stop(pt_this, pt_this_obj);
#else
                i4_ret = MMPR_OK;
#endif
            }
            else if(_MMP_VE_ELMT_TYPE_VIDEO == pt_this_obj->e_elmt_type)
            {
#if defined(_MMP_VERC_INFO_THUMB_SUPPORT)
                i4_ret = _mmp_ve_info_thumb_stop(pt_this, pt_this_obj);
#else
                i4_ret = MMPR_OK;
#endif
            }
            else
            {
                i4_ret = MMPR_NOT_SUPPORT;
            }
        }
        break;

        case MMP_FP_INFO_CMD_ID_CLEAN_THUMB:
        {
            if(NULL == pv_info_cmd_tag)
            {
                MMP_DBG_INFO(("{MMP}pv_cmd_param cannot be NULL %s:%d:\r\n", __FUNCTION__, __LINE__));
                return MMPR_INV_ARG;
            }
            if(_MMP_VE_ELMT_TYPE_AUDIO == pt_this_obj->e_elmt_type)
            {
#if defined(_MMP_VERC_INFO_COVER_SUPPORT)
                MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T* pt_param = (MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*)pv_info_cmd_tag;
                GL_RECT_T               t_rect = *(pt_param->pt_rect);
                GL_COLOR_T              t_empty_clr = {0};

                i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, TRUE);
                if (MMPR_OK != i4_ret) 
                {
                    break;
                }

                mmp_drc_convert_rect_coord(pt_param->e_coords, &t_rect);
                i4_ret = c_gl_surface_draw_rect(pt_this->pt_buf_thumb_show->h_surf,
                                                &t_rect,
                                                &t_empty_clr,
                                                1,
                                                GL_STYLE_FILLED,
                                                GL_SYNC);
                if (GLR_OK != i4_ret) 
                {
                    break;
                }

                i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
                if (MMPR_OK != i4_ret) 
                {
                    break;
                }
#else
                i4_ret = MMPR_OK;
#endif
            }
        }
        break;

        default :
        {
            i4_ret =  MMPR_NOT_SUPPORT;
        }
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_cmd_res_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_info_cmd_res_init(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
#if defined(_MMP_VERC_INFO_COVER_SUPPORT) || defined(_MMP_VERC_INFO_THUMB_SUPPORT)
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    MMP_ASSERT(NULL != pt_this);

    MMP_DBG_INFO(("$ [res init] begin...\n"));

    if(VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag)
    {
        return MMPR_OK;
    }

    if(VIDEO_ENGINE_FLAG_PLAY_DISP_RESUMED & pt_this->ui4_flag)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    pt_this->ui4_flag |= VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED;

    MMP_DBG_INFO(("$ [res init] end.\n"));
#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: video_engine_info_cmd_res_reset
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_info_cmd_res_reset(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
#if defined(_MMP_VERC_INFO_COVER_SUPPORT) || defined(_MMP_VERC_INFO_THUMB_SUPPORT)
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret = 0;

    MMP_ASSERT(
                NULL != pt_this
                );

    MMP_DBG_INFO(("$ [res reset] begin...\n"));

    if(!(VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag))
    {
        return MMPR_OK;
    }

    i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, TRUE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}mmp_drc_clean_buf failed. %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = mmp_drc_clean_buf(pt_this->pt_buf_thumb_show);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}mmp_drc_clean_buf failed. %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}unlock buffer failed. %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    MMP_DBG_INFO(("$ [res reset] end.\n"));
#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_cmd_res_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 mmp_ve_info_cmd_res_deinit(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
#if defined(_MMP_VERC_INFO_COVER_SUPPORT) || defined(_MMP_VERC_INFO_THUMB_SUPPORT)
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    UINT32 i = 0;
    INT32 i4_ret = 0;

    MMP_DBG_INFO(("$ [res deinit] begin...\n"));

    if(!(VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag))
    {
        return MMPR_OK;
    }

    if(VIDEO_ENGINE_FLAG_PLAY_DISP_RESUMED & pt_this->ui4_flag)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    /* stop loading thumbnail */
    for(i = 0; i < _MMP_VERC_INFO_INST_NUM; i++)
    {
        if(0 != pt_this->at_info_inst[i].ui4_info_ver)
        {
            i4_ret = mmp_ve_info_cmd_do(
                              pt_play_inst,
                              (MMP_VE_INFO_INST_PTR_T)&pt_this->at_info_inst[i],
                              MMP_FP_INFO_CMD_ID_STOP_THUMB,
                              NULL
                              );
            IS_MMPR_OK(i4_ret);
        }
    }

    mmp_ve_info_cmd_res_reset(pt_play_inst);

    pt_this->ui4_flag &= ~(VIDEO_ENGINE_FLAG_PLAY_DISP_RESUMED |
                           VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED);

    MMP_DBG_INFO(("$ [res deinit] end.\n"));
#endif

    return MMPR_OK;
}


#if defined(_MMP_VERC_INFO_THUMB_SUPPORT) /* For loading thumbnail */
static VOID _mmp_ve_info_thumb_load_event_hdlr(
                    VOID*                           pv_pt_inf_inst,
                    VOID*                           pv_ui4_load_ver,
                    VOID*                           pv_b_show,
                    VOID*                           pv_unused3
                    )
{
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pv_pt_inf_inst;
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_this_obj->pt_play_inst;
    INT32 i4_ret;
    VIDEO_THUMBNAIL_EX_INFO t_thumb_ex_info;
    GL_RECT_T      at_rect;

    MMP_DBG_INFO(("{MMP} $~~~~~~~~~~~~~~~~~~~~ |||||||||||||||||||| [load thumb] version = %lu:%lu\n", pt_this_obj->ui4_load_ver, (UINT32)pv_ui4_load_ver));

    if((UINT32)pv_ui4_load_ver != pt_this_obj->ui4_load_ver)
    {
        return; /* out of date notify */
    }

    /*Unlock resource from DRC*/
    i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
    if (i4_ret != MMPR_OK)
    {
        MMP_DBG_INFO(("{MMP}unlock buffer failed %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return;
    }

    if (VIDEO_ENGINE_INFO_FLAG_STOPING & pt_this_obj->ui1_flag)
    {
        return; /* To fix DTV00075889 */
    }

    i4_ret = c_svctx_media_get_info(
                            pt_this->h_svctx_hdl,
                            pt_this_obj->h_elmt_hdl,
                            SVCTX_MM_GET_TYPE_THUMBNAIL_EX_INFO,
                            (VOID*)&t_thumb_ex_info,
                            sizeof(VIDEO_THUMBNAIL_EX_INFO)
                            );
    MMP_DBG_INFO(("{mmp} load rect %s,%d,x:%d,y:%d,w:%d,h:%d\n\r",__FILE__,__LINE__,
        t_thumb_ex_info.ui4_thumbnail_x,t_thumb_ex_info.ui4_thumbnail_y,
        t_thumb_ex_info.ui4_thumbnail_width,t_thumb_ex_info.ui4_thumbnail_height));

    at_rect.i4_left = t_thumb_ex_info.ui4_thumbnail_x;
    at_rect.i4_right = at_rect.i4_left + t_thumb_ex_info.ui4_thumbnail_width;
    at_rect.i4_top = t_thumb_ex_info.ui4_thumbnail_y;
    at_rect.i4_bottom = at_rect.i4_top + t_thumb_ex_info.ui4_thumbnail_height;
                
    mmp_drc_convert_screen_rect_coord(&at_rect);
    
    MMP_DBG_INFO(("{mmp} load rect %s,%d,l:%d,r:%d,t:%d,b:%d\n\r",__FILE__,__LINE__,
        at_rect.i4_left,at_rect.i4_right,at_rect.i4_top,at_rect.i4_bottom));

    pt_this_obj->ui1_flag |= VIDEO_ENGINE_INFO_FLAG_SUCCESS;
    MMP_DBG_INFO(("$ [load thumb] success!\n"));

    pt_this_obj->pf_info_nfy_fct(
                    pt_this_obj->pv_info_nfy_tag,
                    pt_this_obj,
                    MMP_FP_INFO_NFY_ID_THUMBNAIL_EX,
                    (VOID*)&at_rect
                    );

    pt_this_obj->pf_info_nfy_fct(
                    pt_this_obj->pv_info_nfy_tag,
                    pt_this_obj,
                    MMP_FP_INFO_NFY_ID_THUMBNAIL,
                    (VOID*)(UINT32)pv_b_show
                    );
}

static VOID _mmp_ve_info_thumb_load_nfy_fct(
                    HANDLE_T                    h_svctx,
                    SVCTX_COND_T                e_nfy_cond,
                    SVCTX_NTFY_CODE_T           e_code,
                    STREAM_TYPE_T               e_stream_type,
                    VOID*                       pv_nfy_tag
                    )
{
    if (e_code == SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_DONE)
    {
        BOOL b_show = FALSE;
#ifdef APP_MMP_SHOW_BROKEN_THUMB    
        if(b_g_video_codec_not_support)
        {
            MMP_DBG_INFO(("{MMP} $ [load thumb] thumb done, codec not support!\n"));
            b_g_video_codec_not_support = FALSE;
            b_show = FALSE;
        }
        else
#endif
        {
            MMP_DBG_INFO(("{MMP} $ [load thumb] done!\n"));
            b_show = TRUE;
        }
        mmp_mc_event_switch_context(
                            MMP_MC_CSC_RETRY_TYPE_NORMAL,
                            _mmp_ve_info_thumb_load_event_hdlr,
                            pv_nfy_tag,
                            (VOID*)((_MMP_VE_INFO_INST_PTR_T)pv_nfy_tag)->ui4_load_ver,
                            (VOID*)(UINT32)b_show,
                            NULL
                            );
    }
    else if(e_code == SVCTX_NTFY_CODE_MEDIA_VS_CODEC_NOT_SUPPORT)
    {
        MMP_DBG_INFO(("{MMP} [load thumb] Codec not support!\n"));
#ifdef APP_MMP_SHOW_BROKEN_THUMB
        b_g_video_codec_not_support = TRUE;
        MMPR_LOG_ON_FAIL (mmp_thumbnailmode_view_show_broken());
#endif
    }
}


/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_thumb_load
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_thumb_load(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj,/* in  */
                    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*    pt_param    /* in  */
                    )
{
    GL_RECT_T t_bound_rect;
    GL_RECT_T t_thumb_rect;
    SVCTX_VIDEO_THUMBNAIL_INFO_T t_thumb_info = {0};
    MINFO_INFO_T t_minfo_rec;
    SIZE_T z_size = sizeof(MINFO_INFO_T);
#ifdef APP_MMP_SHOW_BROKEN_THUMB
    MMP_FILE_SRC_TYPE_T e_src_type = 0;
    CHAR*           ps_media_name = NULL;
#endif
#ifdef _MMP_VERC_INFO_THUMB
    MINFO_INFO_T                        t_minfo_info_svctx;
#endif
    INT32 i4_ret;

    MMP_DBG_INFO(("$ [load thumb] begin...\n"));

    if(NULL != pt_param)
    {
        if(NULL == pt_param->pt_rect || WGL_RECT_IS_EMPTY(pt_param->pt_rect))
        {
            return MMPR_INV_ARG; /* the argument pt_param must be a valid value */
        }

        t_bound_rect = *pt_param->pt_rect;
        mmp_drc_convert_rect_coord(pt_param->e_coords, &t_bound_rect);
        pt_this_obj->t_bound_rect = t_bound_rect;
    }

    if(_MMP_VE_ELMT_STAT_INIT == pt_this_obj->e_elmt_stat)
    {
        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_WAIT;

        MMP_DBG_INFO(("$ [load thumb] exit for not ready.\n"));

        return MMPR_OK;
    }
    else if(_MMP_VE_ELMT_STAT_READY != pt_this_obj->e_elmt_stat)
    {
        return MMPR_OK;
    }

#ifdef APP_MMP_SHOW_BROKEN_THUMB
    i4_ret = mmp_fid_get(pt_this_obj->t_elmt_fid, &ps_media_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_minfo_get_info() failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }
    
    i4_ret = mmp_util_get_file_src_type(ps_media_name, &e_src_type);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} mmp_util_get_file_src_type() failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }
#endif

    if(MEDIA_TYPE_UNKNOWN == pt_this_obj->t_elmt_fmt.e_media_type)
    {
        
#ifdef APP_MMP_SHOW_BROKEN_THUMB
        if(!g_b_is_parse_ok && e_src_type == MMP_FILE_SRC_DLNA)
        {
            i4_ret =  MINFOR_FMT_NOT_SUPPORT;
            /* fix coverity check i4_ret */
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} MINFOR_FMT_NOT_SUPPORT %s:%d\r\n", __FUNCTION__, __LINE__));
            }
        }
        else
#endif
        {
            i4_ret = c_svctx_media_get_info(
                            pt_this->h_svctx_hdl,
                            pt_this_obj->h_elmt_hdl,
                            SVCTX_MM_GET_TYPE_MEDIA_FORMAT,
                            (VOID*)&t_minfo_rec,
                            z_size
                            );
            if(SVCTXR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} c_svctx_media_get_info() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                return MMPR_FAIL;
            }
            
            pt_this_obj->t_elmt_fmt = t_minfo_rec.t_format;
        }
    }
    
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_this_obj->e_elmt_type)
    {
        if(!FMT_IS_VIDEO_CATEGORY(pt_this_obj->t_elmt_fmt))
        {
            return MMPR_NOT_SUPPORT;
        }

#ifdef APP_NET_DLNA_SUPPORT
        //Check if server support seek
        if (MEDIA_TYPE_CONTAINER == pt_this_obj->t_elmt_fmt.e_media_type &&
            MEDIA_CONTNR_SUBTYPE_MP4 == pt_this_obj->t_elmt_fmt.t_media_subtype.u.e_contnr_subtype) 
        {
            CHAR*       ps_file_name = NULL;

            i4_ret = mmp_fid_get(pt_this_obj->t_elmt_fid, &ps_file_name);
            if (i4_ret != MMPR_OK)
            {
                MMP_DBG_INFO(("{MMP}mmp_fid_get.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            }
        
            if (FALSE == mmp_util_dlna_is_seek_supported(ps_file_name))
            {
                return MMPR_NOT_SUPPORT;
            }
        }
#endif
        
#ifdef _MMP_VERC_INFO_THUMB
        i4_ret = c_svctx_media_get_info(
                        pt_this->h_svctx_hdl,
                        pt_this_obj->h_elmt_hdl,
                        SVCTX_MM_GET_TYPE_GENERIC_INFO,
                        &t_minfo_info_svctx,
                        sizeof(MINFO_INFO_T)
                        );
        /* fix coverity check return value */
        if (i4_ret != MMPR_OK)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_media_get_info() fail.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }
        
        if ((SVCTXR_OK != i4_ret) ||
            (t_minfo_info_svctx.u.t_general_info.b_is_drm_exist))
        {
            MMP_DBG_INFO(("{MMP} c_svctx_media_get_info() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_NOT_SUPPORT;
        }

        {
            MINFO_INFO_CODEC_ENC_T t_video_file_type = MINFO_INFO_CODEC_VID_ENC_UNKONWN;
            
            i4_ret = c_svctx_media_get_info(
                            pt_this->h_svctx_hdl,
                            pt_this_obj->h_elmt_hdl,
                            SVCTX_MM_GET_TYPE_VID_CODEC_INFO,
                            &t_video_file_type,
                            sizeof(MINFO_INFO_CODEC_ENC_T)
                            );
            if( MINFO_INFO_CODEC_VID_ENC_DIVX == t_video_file_type &&
                FALSE == _MMP_VERC_HAS_DIVX_SUPPORT())
            {
                return MMPR_NOT_SUPPORT;
            }
        }
#else
        i4_ret = c_svctx_media_get_info(
                        pt_this->h_svctx_hdl,
                        pt_this_obj->h_elmt_hdl,
                        SVCTX_MM_GET_TYPE_GENERIC_INFO,
                        (VOID*)&t_minfo_rec,
                        z_size
                        );
        if ((SVCTXR_OK != i4_ret) ||
            (t_minfo_rec.u.t_general_info.b_is_drm_exist))
        {
            MMP_DBG_INFO(("{MMP} c_svctx_media_get_info() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_NOT_SUPPORT;
        }
#endif
    }

    /**/
    if(!(VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag))
    {
        return MMPR_RES_NOT_READY;
    }

    /*stop current loading*/
    if(VIDEO_ENGINE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag)
    {
        return MMPR_OK;
    }

    /*Lock resource from DRC*/
    i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, TRUE);
    if (i4_ret != MMPR_OK)
    {
        MMP_DBG_INFO(("{MMP}lock buffer failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    _VIDEO_ENGINE_NEW_LOAD_VER(pt_this_obj);

    t_bound_rect = pt_this_obj->t_bound_rect;

    t_thumb_info.h_surf = pt_this->pt_buf_thumb_show->h_surf;
    t_thumb_info.ui4_thumbnail_x = (UINT32)t_bound_rect.i4_left;
    t_thumb_info.ui4_thumbnail_y = (UINT32)t_bound_rect.i4_top;
    t_thumb_info.ui4_thumbnail_width = (UINT32)WGL_RECT_GET_WIDTH(&t_bound_rect);
    t_thumb_info.ui4_thumbnail_height =(UINT32) WGL_RECT_GET_HEIGHT(&t_bound_rect);
    t_thumb_info.pf_nfy = _mmp_ve_info_thumb_load_nfy_fct;
    t_thumb_info.pv_tag = pt_this_obj;
    t_thumb_info.ui8_pic_idx = _MMP_VERC_THUMB_PIC_INDEX;
	t_thumb_info.i4_time	 = (INT32)(-1);
    
#ifdef ENABLE_MULTIMEDIA
    i4_ret = c_svctx_media_load_thumbnail(
                    pt_this->h_svctx_hdl,
                    pt_this_obj->h_elmt_hdl,
                    &t_thumb_info
                    );
#else
    i4_ret = SVCTXR_NOT_SUPPORT;
#endif
    if (i4_ret != SVCTXR_ASYNC_NFY && i4_ret != SVCTXR_OK)
    {
        pt_this_obj->ui4_load_ver = VIDEO_ENGINE_LOAD_VER_INVALID;
        MMP_DBG_INFO(("{MMP}exit for c_svctx_media_load_thumbnail() failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));

        if(MMPR_OK != _mmp_ve_info_thumb_lock_buf(pt_this, FALSE))
        {
            MMP_DBG_INFO(("{MMP}[load thumb] unlock buffer failed. %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }

        return i4_ret;
    }

    pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;

#if 1 /* Only for test*/
    CHAR* ps_media_file_name = NULL;
    i4_ret = mmp_fid_get(pt_this_obj->t_elmt_fid, &ps_media_file_name);
    MMPR_LOG_ON_FAIL(i4_ret);
    MMP_DBG_INFO(("$ [load thumb] loading file %s...\n", ps_media_file_name));
#endif

    t_thumb_rect = t_bound_rect; /* temp use !!! */

    /*update status*/
    pt_this_obj->t_thumb_rect = t_thumb_rect;
    pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_STOPING;
    pt_this_obj->ui1_flag |=  VIDEO_ENGINE_INFO_FLAG_LOADING;

    MMP_DBG_INFO(("{MMP} $[load thumb] end. version = %lu\n", pt_this_obj->ui4_load_ver));
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_thumb_stop
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_thumb_stop(
                    _MMP_VE_PLAY_INST_PTR_T       pt_this,            /* in  */
                    _MMP_VE_INFO_INST_PTR_T       pt_this_obj         /* in  */
                    )
{
    INT32 i4_ret = MMPR_OK;

    MMP_DBG_INFO(("$ [stop thumb] begine ..ui1_flag = %u\n", pt_this_obj->ui1_flag));

    if(VIDEO_ENGINE_INFO_FLAG_SUCCESS & pt_this_obj->ui1_flag)
    {
        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_READY;

        pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_LOADING;
        pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_SUCCESS;

        MMP_DBG_INFO(("$ [stop thumb] exit for loading complete.\n"));
        return MMPR_OK;
    }
    else if(VIDEO_ENGINE_INFO_FLAG_STOPING & pt_this_obj->ui1_flag)
    {
        MMP_DBG_INFO(("$ [stop thumb] exit for already stoping.\n"));
        return MMPR_OK;
    }
    else if(!(VIDEO_ENGINE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag))
    {
        if(_MMP_VE_ELMT_STAT_WAIT == pt_this_obj->e_elmt_stat)
        {
            pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_INIT;
        }

        MMP_DBG_INFO(("$ [stop thumb] exit for not loading. ui1_flag = %u\n", pt_this_obj->ui1_flag));
        return MMPR_OK;
    }

    pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_READY;

    pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_LOADING;
    pt_this_obj->ui1_flag |=  VIDEO_ENGINE_INFO_FLAG_STOPING;

    if (pt_this->h_svctx_hdl != NULL_HANDLE && pt_this_obj->h_elmt_hdl != NULL_HANDLE)
    {
#ifdef ENABLE_MULTIMEDIA
        i4_ret = c_svctx_media_sync_cancel_load_thumbnail(
                           pt_this->h_svctx_hdl,
                           pt_this_obj->h_elmt_hdl);
        MMP_DBG_INFO(("{MMP} $[stop thumb] version = %lu,i4_ret:%d\n", pt_this_obj->ui4_load_ver,i4_ret));
#else
        i4_ret = SVCTXR_NOT_SUPPORT;
#endif
        if (SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_media_sync_cancel_load_thumbnail()%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }
    }

    i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}[stop thumb] unlock buffer failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    MMP_DBG_INFO(("$ [stop thumb] end.\n"));

    return MMPR_OK;
}
#endif

#if defined(_MMP_VERC_INFO_COVER_SUPPORT) /* For loading cover picture */

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_show(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,
                    _MMP_VE_INFO_INST_PTR_T         pt_this_obj
                    )
{
    INT32                    i4_ret_1=0,i4_ret_2=0;
    GL_HSURFACE_T            h_dst_surf=NULL_HANDLE,h_src_surf=NULL_HANDLE;
    UINT32                   ui4_dst_w=0,ui4_dst_h=0;
    UINT32                   ui4_src_w=0,ui4_src_h=0;

    h_dst_surf = (GL_HSURFACE_T)(pt_this->pt_buf_thumb_show->h_surf);
    h_src_surf = (GL_HSURFACE_T)(pt_this->pt_buf_thumb_load->h_surf);

    ui4_dst_w = (UINT32)WGL_RECT_GET_WIDTH(&(pt_this_obj->t_thumb_rect));
    ui4_dst_h = (UINT32)WGL_RECT_GET_HEIGHT(&(pt_this_obj->t_thumb_rect));

    ui4_src_w = ui4_dst_w;
    ui4_src_h = ui4_dst_h;

    i4_ret_1 = c_gl_surface_adv_stretch_blt(
                                h_dst_surf,
                                h_src_surf, 
                                pt_this_obj->t_thumb_rect.i4_left,
                                pt_this_obj->t_thumb_rect.i4_top,
                                ui4_dst_w,
                                ui4_dst_h,
                                pt_this_obj->t_bound_rect.i4_left,
                                pt_this_obj->t_bound_rect.i4_top,
                                ui4_src_w,
                                ui4_src_h,
                                GL_SYNC
                                );
    if(GLR_OK != i4_ret_1)
    {
        MMP_DBG_INFO(("{MMP} c_gl_surface_adv_stretch_blt() failed. i4_ret = %d.\r\n", i4_ret_1));
    }

    /*unlock resource from DRC*/
    i4_ret_2 = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
    if (i4_ret_2 != MMPR_OK)
    {
        MMP_DBG_INFO(("{MMP} _mmp_ve_info_thumb_lock_buf failed %d\n",i4_ret_2));
    }

    if(GLR_OK != i4_ret_1)
    {
        return i4_ret_1;
    }
    else
    {
        return i4_ret_2;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_load_nfy_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_ve_info_image_load_nfy_fct(
                    VOID*                           pv_info_obj,
                    VOID*                           pv_h_img,
                    VOID*                           pv_i4_ret,
                    VOID*                           pv_ver
                    )
{
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pv_info_obj;
    _MMP_VE_PLAY_INST_PTR_T pt_this = NULL;
    HANDLE_T h_img = (HANDLE_T)(UINT32)pv_h_img;
    UINT32 ui4_ver = (UINT32)pv_ver;
    BOOL b_success = TRUE;
    INT32 i4_ret=0;

    if(NULL == pt_this_obj || NULL_HANDLE == h_img)
    {
        MMP_DBG_ERROR(("$ [image load] error handle \n"));
        MMP_ASSERT(0);
        return;
    }

    pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_this_obj->pt_play_inst;

    /**/
    if(pt_this_obj->h_img != h_img || NULL_HANDLE == pt_this_obj->h_img)
    {
        /*notification is out of date*/
        MMP_DBG_ERROR(("$ [image load] error handle,return\n"));
        return;
    }

    /*check version*/
    if(pt_this_obj->ui4_load_ver != ui4_ver)
    {
        /*notification is out of date*/
        //return;
    }

    MMP_DBG_INFO(("{MMP} $ [load image] |||||||||||||||||||| load image success!\n"));

    if(VIDEO_ENGINE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag)
    {
        i4_ret = _mmp_ve_info_image_show(pt_this, pt_this_obj);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} _mmp_ve_info_image_show() failed %d\n",i4_ret));
            b_success = FALSE;
        }

        i4_ret = _mmp_ve_info_image_close(pt_this, pt_this_obj);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} _mmp_ve_info_image_close() failed %d\n",i4_ret));
        }

        pt_this_obj->ui1_flag |= VIDEO_ENGINE_INFO_FLAG_SUCCESS;

        /*notify client*/
        pt_this_obj->pf_info_nfy_fct(
                        pt_this_obj->pv_info_nfy_tag,
                        pt_this_obj,
                        MMP_FP_INFO_NFY_ID_THUMBNAIL,
                        (VOID*)(UINT32)b_success
                        );
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_open_nfy_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_ve_info_image_open_cb(
                    HANDLE_T                        h_handle,
                    const VOID*                     pv_tag,
                    IMG_NFY_EVENT_TYPE_T            e_event,
                    const VOID*                     pv_data
                    )
{
    IMG_NFY_LOAD_WITH_TAG_T*    pt_nfy=NULL;

    if(NULL_HANDLE == h_handle || NULL == pv_tag)
    {
        MMP_DBG_ERROR(("$ [image open] error handle \n"));
        return;
    }

    MMP_DBG_INFO(("{MMP} $ [open image] <<- <<- <<- <<- <<- open image file.\n"));

    if(IMG_NFY_LOAD_COMPLETE_WITH_TAG == e_event ||
       IMG_NFY_LOAD_COMPLETE_TYPE     == e_event) /*pv_data is an INT32 value that indicates the return value of loading image*/
    {
        if(NULL == pv_data)
        {
            MMP_DBG_ERROR(("$ [image open] null data \n"));
            MMP_ASSERT(0);
            return;
        }

        pt_nfy = (IMG_NFY_LOAD_WITH_TAG_T*)pv_data;

        /* post a message to itself */
        mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_CRITICAL,
                    _mmp_ve_info_image_load_nfy_fct,
                    (VOID*)pv_tag,
                    (VOID*)h_handle,
                    (VOID*)pt_nfy->i4_ret,
                    (VOID*)pt_nfy->pv_tag
                    );
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_open
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_open(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj /* in  */
                    )
{
    CHAR*           ps_media_name = NULL;
    CHAR*           pc_str1 = NULL;
    MINFO_INFO_T    t_minfo_rec;
    SIZE_T          z_size = sizeof(MINFO_INFO_T);
    UINT32          ui4_mask=0, ui4_ofs=0, ui4_len=0;
    UINT64          ui8_ofs=0;
    UINT32          ui4_read = 0;
    FM_FILE_INFO_T  t_info;
    HANDLE_T        h_file_usb = NULL_HANDLE;
    MEDIA_FORMAT_T  t_format;
    MMP_FILE_SRC_TYPE_T e_src_type;
    UINT32          i = 0;
    INT32           i4_ret=0;

    c_memset(&t_info,0,sizeof(FM_FILE_INFO_T));
    c_memset(&t_format,0,sizeof(MEDIA_FORMAT_T));
    
    i4_ret = mmp_fid_get(pt_this_obj->t_elmt_fid, &ps_media_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_minfo_get_info() failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    
    i4_ret = mmp_util_get_file_src_type(ps_media_name, &e_src_type);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} mmp_util_get_file_src_type() failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    
    /* PCM has no meta info */
    pc_str1 = c_strrchr(ps_media_name, (CHAR)'.');
    if ((NULL != pc_str1) && (0 == c_strcmp(pc_str1, ".pcm")))
    {
        i4_ret = MMPR_NOT_SUPPORT;
        return i4_ret;
    }
    
    t_format.b_fav_recg_only = FALSE;
    
    t_format.e_media_type = MEDIA_TYPE_UNKNOWN;
    
#ifdef APP_MMP_SHOW_BROKEN_THUMB       
    if(!g_b_is_parse_ok && (MMP_FILE_SRC_DLNA == e_src_type ))
    {
        i4_ret = MINFOR_FMT_NOT_SUPPORT;
        return i4_ret;
    }
#endif

    c_memset(&t_minfo_rec, 0, sizeof(MINFO_INFO_T));
    t_minfo_rec.e_info_type = MINFO_INFO_TYPE_ID3_DATA;
    /* fix DTV00841805 aac file */
    i4_ret = c_svctx_media_get_info(
                pt_this->h_svctx_hdl,
                pt_this_obj->h_elmt_hdl,
                SVCTX_MM_GET_TYPE_META_DATA,
                (VOID*)&t_minfo_rec,
                z_size
                    );
    if(MINFOR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_minfo_get_info() failed.%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    
    ui4_mask = t_minfo_rec.u.t_id3_data.ui4_pic_bitmask;
    if(0 == ui4_mask)
    {
        i4_ret = MMPR_NOT_SUPPORT;
        MMP_DBG_INFO(("{MMP} Picture bitmask of ID3 data is 0. %s:%d \r\n", __FUNCTION__, __LINE__));
        return i4_ret;
    }
    
    for(i = 0; i <= MINFO_ID3_PIC_STUDIO_LOGOTYPE; i++)
    {
        if(ui4_mask & ((UINT32)(1 << i)))
        {
            break; /* use i as the index to retrieve ID3 pic data */
        }
    }
    
    if(MINFO_ID3_PIC_STUDIO_LOGOTYPE <= i)
    {
        i4_ret = MMPR_NOT_SUPPORT;
        return i4_ret;
    }
    
    t_format = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].t_format;
    if(MEDIA_IMG_SUBTYPE_JPG != t_format.t_media_subtype.u.e_img_subtype)
    {
        i4_ret = MMPR_NOT_SUPPORT;
        return i4_ret;
    }
    
    ui4_ofs = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_starting_offset;
    ui4_len = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_length;
    
    /*alloc buf*/
    pt_this_obj->pui1_data = c_mem_alloc((SIZE_T)ui4_len);
    if(NULL == pt_this_obj->pui1_data)
    {
        i4_ret = MMPR_OUT_OF_MEM;
        return i4_ret;
    }
    c_memset(pt_this_obj->pui1_data, 0 , (SIZE_T)ui4_len);
    
    i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE, ps_media_name, &t_info);
    if(FMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} get file info i4_ret:%d\n",i4_ret));
        return i4_ret;
    }
    
    i4_ret = c_fm_open(FM_ROOT_HANDLE, ps_media_name, FM_READ_ONLY, 0777, FALSE, &h_file_usb);
    if(FMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} open USB file fail,i4_ret:%d\n",i4_ret));
        if(NULL_HANDLE != h_file_usb)
        {
            c_fm_close(h_file_usb);
            h_file_usb = NULL_HANDLE;
        }
        return i4_ret;
    }
    
    i4_ret =  c_fm_lseek(h_file_usb, (INT64)ui4_ofs, FM_SEEK_BGN, &ui8_ofs);
    if(FMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} lseek FLASH file fail,i4_ret:%d\n",i4_ret));
        if(NULL_HANDLE != h_file_usb)
        {
            c_fm_close(h_file_usb);
            h_file_usb = NULL_HANDLE;
        }
        return i4_ret;
    }
    
    i4_ret = c_fm_read(h_file_usb, pt_this_obj->pui1_data, ui4_len, &ui4_read);
    if(FMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} read file fail,i4_ret:%d\n",i4_ret));
        if(NULL_HANDLE != h_file_usb)
        {
            c_fm_close(h_file_usb);
            h_file_usb = NULL_HANDLE;
        }
        return i4_ret;
    }
    
    i4_ret = c_fm_close(h_file_usb);
    if(FMR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} close file fail,i4_ret:%d\n",i4_ret));
        h_file_usb = NULL_HANDLE;
        return i4_ret;
    }
    
    h_file_usb = NULL_HANDLE;
    
    i4_ret = c_img_mopen(
                    pt_this_obj->pui1_data,
                    (SIZE_T)ui4_len,
                    "JPG",
                    _mmp_ve_info_image_open_cb,
                    pt_this_obj,
                    &pt_this_obj->h_img
                    );
    if(IMGR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = c_img_get_dimension(
                    pt_this_obj->h_img,
                    INTRA_IMG_PRIMARY_IMG_TYPE,
                    &pt_this_obj->z_img_w,
                    &pt_this_obj->z_img_h
                );
    if(IMGR_OK != i4_ret)
    {
        return i4_ret;
    }
       
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_close
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: 
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_close(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj /* in  */
                    )
{
    if(NULL != pt_this_obj->pui1_data)
    {
        c_mem_free(pt_this_obj->pui1_data);
        pt_this_obj->pui1_data = NULL;
    }
    
    if(NULL_HANDLE != pt_this_obj->h_minfo)
    {
        c_minfo_close(pt_this_obj->h_minfo);
        pt_this_obj->h_minfo = NULL_HANDLE;
    }
    
    if(NULL_HANDLE != pt_this_obj->h_img)
    {
        c_img_close(pt_this_obj->h_img);
        pt_this_obj->h_img = NULL_HANDLE;
    }
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_load
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_load(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj,/* in  */
                    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*    pt_param    /* in  */
                    )
{
    INT32                      i4_ret=0;    
    GL_RECT_T                  t_bound_rect;
    GL_RECT_T                  t_thumb_rect;
    IMG_TYPE_DATA_T            t_type_data;
    SIZE_T                     t_size_w=0,t_size_h=0;
    IMG_INTRA_TYPE_T           e_img_type;
    SIZE_T                     t_dst_w=0,t_dst_h=0,t_size_tmp_h=0,t_size_tmp_w=0;

    c_memset(&t_type_data,0,sizeof(IMG_TYPE_DATA_T));

    if((NULL == pt_this_obj) ||
       (NULL == pt_param->pt_rect) || 
       WGL_RECT_IS_EMPTY(pt_param->pt_rect))
    {
        return MMPR_INV_ARG;
    }

    /**/
    if(0 == (VIDEO_ENGINE_FLAG_THUMB_DISP_RESUMED & pt_this->ui4_flag))
    {
        return MMPR_RES_NOT_READY;
    }

    if(_MMP_VE_ELMT_STAT_INIT == pt_this_obj->e_elmt_stat)
    {
        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_WAIT;

        MMP_DBG_INFO(("$ [load image] exit for init.\n"));

        return MMPR_OK;
    }
    else if(_MMP_VE_ELMT_STAT_READY != pt_this_obj->e_elmt_stat)
    {
        MMP_DBG_INFO(("$ [load image] exit for not ready.\n"));
        return MMPR_OK;
    }

    /*stop current loading*/
    if(VIDEO_ENGINE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag)
    {
        MMP_DBG_INFO(("$ [load image] exit for not lading.\n"));
        return MMPR_OK;
    }

    i4_ret = _mmp_ve_info_image_open(pt_this, pt_this_obj);
    if (i4_ret != MMPR_OK)
    {
        _mmp_ve_info_image_close(pt_this, pt_this_obj);
        return i4_ret;
    }

    t_bound_rect = *pt_param->pt_rect;
    mmp_drc_convert_rect_coord(pt_param->e_coords, &t_bound_rect);
    pt_this_obj->t_bound_rect = t_bound_rect;

    /*load image*/
     _VIDEO_ENGINE_NEW_LOAD_VER(pt_this_obj);
    t_type_data.ui4_data_flag = IMG_TYPE_DATA_TAG;

    e_img_type = INTRA_IMG_PRIMARY_IMG_TYPE;
    i4_ret = c_img_get_dimension(
                    pt_this_obj->h_img,
                    e_img_type,
                    &t_size_w,
                    &t_size_h
                    );
    if(GLR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_gl_surface_blt() failed. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

#if 1    
    /*Keep ration*/
    t_size_tmp_w =WGL_RECT_GET_WIDTH(&t_bound_rect);
    t_size_tmp_h =WGL_RECT_GET_HEIGHT(&t_bound_rect);
    
    if(0==t_size_w)
    {
        MMP_DBG_INFO(("{MMP} Size wrong %s:%s:%d\n", __FUNCTION__, __FUNCTION__, __LINE__)); 
        t_size_w = 1;
    }
    
    if(0==t_size_h)
    {
        MMP_DBG_INFO(("{MMP} Size wrong %s:%s:%d\n", __FUNCTION__, __FUNCTION__, __LINE__)); 
        t_size_h = 1;
    }
    
    t_dst_h = (t_size_tmp_w*t_size_h)/t_size_w;
    t_dst_w= (t_size_tmp_h*t_size_w)/t_size_h;
    
    if(t_dst_h>t_size_tmp_h)
    {
        t_dst_h = t_size_tmp_h;
        t_dst_w= (t_dst_h*t_size_w)/t_size_h;
    }
    else if(t_dst_w>t_size_tmp_w)
    {
        t_dst_w = t_size_tmp_w;
        t_dst_h = (t_dst_w*t_size_h)/t_size_w;
    }

    t_bound_rect.i4_left=t_bound_rect.i4_left+(t_size_tmp_w - t_dst_w)/2;
    
    t_bound_rect.i4_top=t_bound_rect.i4_top+(t_size_tmp_h - t_dst_h)/2;
    
    pt_this_obj->t_bound_rect.i4_left=t_bound_rect.i4_left;
    
    pt_this_obj->t_bound_rect.i4_top=t_bound_rect.i4_top;
#endif

    /*Lock resource from DRC*/
    i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, TRUE);
    if (i4_ret != MMPR_OK)
    {
        return i4_ret;
    }
    
    /*Clean buf:CR 72259*/
    i4_ret=mmp_drc_clean_buf(pt_this->pt_buf_thumb_load);
    MMPR_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_img_async_load(
                    pt_this_obj->h_img,
                    e_img_type,
                    &t_type_data,
                    IMG_ROTATE_CLOCKWS_0_OP_TYPE,
                    0,
                    0,
                    (UINT32)t_size_w,
                    (UINT32)t_size_h,
                    (UINT32)t_bound_rect.i4_left,
                    (UINT32)t_bound_rect.i4_top,
                    (UINT32)t_dst_w,
                    (UINT32)t_dst_h,
                    pt_this->pt_buf_thumb_load->h_surf
                    );

    if(GLR_OK != i4_ret)
    {
        INT32   i4_ret2=0;
        
        MMP_DBG_INFO(("{MMP} c_img_sync_load() failed. i4_ret = %d.\r\n", i4_ret));
        i4_ret2 = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret2);
        
        return i4_ret;
    }

    /*Temp*/
    t_thumb_rect = t_bound_rect;

    /*update status*/
    pt_this_obj->t_thumb_rect = t_thumb_rect;
    pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_STOPING;
    pt_this_obj->ui1_flag |=  VIDEO_ENGINE_INFO_FLAG_LOADING;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_stop
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_stop(
                    _MMP_VE_PLAY_INST_PTR_T       pt_this,            /* in  */
                    _MMP_VE_INFO_INST_PTR_T       pt_this_obj         /* in  */
                    )
{
    INT32 i4_ret = MMPR_OK;

    if(VIDEO_ENGINE_INFO_FLAG_SUCCESS & pt_this_obj->ui1_flag)
    {
        MMP_DBG_INFO(("$ [stop image] exit for loading complete.\n"));
        pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_LOADING;
        pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_SUCCESS;

        pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_READY;
        return MMPR_OK;
    }
    else if(VIDEO_ENGINE_INFO_FLAG_STOPING & pt_this_obj->ui1_flag)
    {
        MMP_DBG_INFO(("$ [stop image] exit for already stoping.\n"));
        return MMPR_OK;
    }
    else if(!(VIDEO_ENGINE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag))
    {
        MMP_DBG_INFO(("$ [stop image] exit for not loading.\n"));
        if(_MMP_VE_ELMT_STAT_WAIT == pt_this_obj->e_elmt_stat)
        {
            pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_INIT;
        }
        return MMPR_OK;
    }

    pt_this_obj->e_elmt_stat = _MMP_VE_ELMT_STAT_READY;

    pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_LOADING;
    pt_this_obj->ui1_flag |=  VIDEO_ENGINE_INFO_FLAG_STOPING;

    if(NULL_HANDLE != pt_this_obj->h_img)
    {
        MMP_DBG_INFO(("{MMP} $ [stop image] -------------------- stop to load image!\n"));
        i4_ret = c_img_stop(pt_this_obj->h_img, IMG_STOP_PRIMARY_OP_TYPE);
        if (IMGR_OK != i4_ret && IMGR_ALREADY_STOP != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} $ [stop image] c_img_stop() returns %d\r\n", i4_ret));
            return MMPR_FAIL;
        }
        
        /*unlock resource from DRC*/
        i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} _mmp_ve_info_thumb_lock_buf failed %d\n",i4_ret));
        }
    }

    return MMPR_OK;
}
#endif

#if defined(_MMP_VERC_PLAY_COVER_SUPPORT)
UINT32 ui4_cover_pic_w = 0;
UINT32 ui4_cover_pic_h = 0;
/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_stop
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_stop_ex(
                    _MMP_VE_PLAY_INST_PTR_T       pt_this,            /* in  */
                    _MMP_VE_INFO_INST_PTR_T       pt_this_obj         /* in  */
                    )
{
    INT32 i4_ret;

    if(NULL_HANDLE != pt_this_obj->h_img)
    {
        i4_ret = c_img_stop(pt_this_obj->h_img, IMG_STOP_PRIMARY_OP_TYPE);
        if (IMGR_OK != i4_ret)
        {
            if(IMGR_ALREADY_STOP == i4_ret)
            {
                return MMPR_OK;
            }
            else
            {
                return i4_ret;
            }
        }
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_load_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_load_ex(
                    _MMP_VE_PLAY_INST_PTR_T                pt_this,    /* in  */
                    _MMP_VE_INFO_INST_PTR_T                pt_this_obj,/* in  */
                    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T*    pt_param    /* in  */
                    )
{
    INT32                      i4_ret=0;
    INT32                      i4_ret2=0;
    GL_RECT_T                  t_bound_rect;
    GL_RECT_T                  t_thumb_rect;
    IMG_TYPE_DATA_T            t_type_data;
    SIZE_T                     t_size_w=0,t_size_h=0;
    IMG_INTRA_TYPE_T           e_img_type;
    SIZE_T                     t_dst_w=0,t_dst_h=0,t_size_tmp_h=0,t_size_tmp_w=0;
    
    if(NULL == pt_param->pt_rect || WGL_RECT_IS_EMPTY(pt_param->pt_rect))
    {
        MMP_DBG_INFO(("{MMP} MMPR_INV_ARG  \n"));
        return MMPR_INV_ARG;
    }
    
    /*No thumb*/
    if(NULL == pt_this_obj || NULL_HANDLE == pt_this_obj->h_img)
    {
        MMP_DBG_INFO(("{MMP} No thumb  \n"));
        return MMPR_OK;
    }
    
    c_memset(&t_type_data, 0, sizeof(IMG_TYPE_DATA_T));
    /*Lock resource from DRC*/
    i4_ret = _mmp_ve_info_thumb_lock_buf(pt_this, TRUE);
    IS_MMPR_OK(i4_ret);
    
    t_bound_rect = *pt_param->pt_rect;
    mmp_drc_convert_rect_coord(pt_param->e_coords, &t_bound_rect);
    
    /*load image*/
     _VIDEO_ENGINE_NEW_LOAD_VER(pt_this_obj);
  
    t_type_data.ui4_data_flag = IMG_TYPE_DATA_TAG;
     
    e_img_type = INTRA_IMG_PRIMARY_IMG_TYPE;
    i4_ret = c_img_get_dimension(
                    pt_this_obj->h_img,
                    e_img_type,
                    &t_size_w,
                    &t_size_h
                    );
    if(GLR_OK != i4_ret)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
        return i4_ret;
    }
     
    /*Keep ration*/
    t_size_tmp_w =WGL_RECT_GET_WIDTH(&t_bound_rect);
    t_size_tmp_h =WGL_RECT_GET_HEIGHT(&t_bound_rect);

    if(0==t_size_w)
    {
        MMP_DBG_INFO(("{MMP} Size wrong %s:%s:%d\n", __FUNCTION__, __FUNCTION__, __LINE__)); 
        t_size_w = 1;
    }

    if(0==t_size_h)
    {
        MMP_DBG_INFO(("{MMP} Size wrong %s:%s:%d\n", __FUNCTION__, __FUNCTION__, __LINE__)); 
        t_size_h = 1;
    }
    
    t_dst_h = (t_size_tmp_w*t_size_h)/t_size_w;
    t_dst_w= (t_size_tmp_h*t_size_w)/t_size_h;
    
    if(t_dst_h>t_size_tmp_h)
    {
        t_dst_h = t_size_tmp_h;
        t_dst_w= (t_dst_h*t_size_w)/t_size_h;
    }
    else if(t_dst_w>t_size_tmp_w)
    {
        t_dst_w = t_size_tmp_w;
        t_dst_h = (t_dst_w*t_size_h)/t_size_w;
    }
    pt_this_obj->t_bound_rect.i4_left=pt_this_obj->t_bound_rect.i4_left+
     (t_size_tmp_w - t_dst_w)/2;
    
    pt_this_obj->t_bound_rect.i4_top=pt_this_obj->t_bound_rect.i4_top+
     (t_size_tmp_h - t_dst_h)/2;
    
    /*Clean buf:CR 72259*/
    i4_ret=mmp_drc_clean_buf(pt_this->pt_buf_thumb_load);
    MMPR_LOG_ON_FAIL(i4_ret);
    
    i4_ret = c_img_async_load(
                    pt_this_obj->h_img,
                    e_img_type,
                    &t_type_data,
                    IMG_ROTATE_CLOCKWS_0_OP_TYPE,
                    0,
                    0,
                    (UINT32)t_size_w,
                    (UINT32)t_size_h,
                    (UINT32)pt_this_obj->t_bound_rect.i4_left,
                    (UINT32)pt_this_obj->t_bound_rect.i4_top,
                    (UINT32)t_dst_w,
                    (UINT32)t_dst_h,
                    pt_this->pt_buf_thumb_load->h_surf
                    );
    if(GLR_OK != i4_ret)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
        i4_ret2 =_mmp_ve_info_thumb_lock_buf(pt_this, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret2);
        return i4_ret;
    }

    /*Temp*/
    t_thumb_rect = t_bound_rect;

    /*update status*/
    pt_this_obj->t_bound_rect = t_bound_rect;
    pt_this_obj->t_thumb_rect = t_thumb_rect;
    pt_this_obj->ui1_flag &= ~VIDEO_ENGINE_INFO_FLAG_STOPING;
    pt_this_obj->ui1_flag |=  VIDEO_ENGINE_INFO_FLAG_LOADING;
    
    return MMPR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_show_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_image_show_ex(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,
                    _MMP_VE_INFO_INST_PTR_T         pt_this_obj
                    )
{
    INT32                    i4_ret_1,i4_ret_2;
    GL_HSURFACE_T            h_dst_surf,h_src_surf;
    UINT32                   ui4_dst_w,ui4_dst_h;
    UINT32                   ui4_src_w,ui4_src_h;

    h_dst_surf = (GL_HSURFACE_T)(t_g_play_inst_cover_pic.pt_buf_thumb_show->h_surf);
    h_src_surf = (GL_HSURFACE_T)(t_g_play_inst_cover_pic.pt_buf_thumb_load->h_surf);

    ui4_dst_w = (UINT32)WGL_RECT_GET_WIDTH(&(t_g_info_inst_cover_pic.t_thumb_rect));
    ui4_dst_h = (UINT32)WGL_RECT_GET_HEIGHT(&(t_g_info_inst_cover_pic.t_thumb_rect));

    ui4_src_w = ui4_dst_w;
    ui4_src_h = ui4_dst_h;

    i4_ret_1 = c_gl_surface_adv_stretch_blt(
                                h_dst_surf,
                                h_src_surf,
                                t_g_info_inst_cover_pic.t_thumb_rect.i4_left,
                                t_g_info_inst_cover_pic.t_thumb_rect.i4_top,
                                ui4_dst_w,
                                ui4_dst_h,
                                0,
                                0,
                                ui4_src_w,
                                ui4_src_h,
                                GL_SYNC
                                );
    if(GLR_OK != i4_ret_1)
    {
        MMPR_LOG_ON_FAIL(i4_ret_1);
    }
    else
    {
        MMP_DBG_INFO(("{MMP} Load cover pic success \n"));
    }

    /*unlock resource from DRC*/
    i4_ret_2 = _mmp_ve_info_thumb_lock_buf(&t_g_play_inst_cover_pic, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret_2);

    if(GLR_OK != i4_ret_1)
    {
        return i4_ret_1;
    }
    else
    {
        return i4_ret_2;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_load_nfy_fct_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_ve_info_image_load_nfy_fct_ex(
                    VOID*                           pv_info_obj,
                    VOID*                           pv_h_img,
                    VOID*                           pv_i4_ret,
                    VOID*                           pv_ver
                    )
{
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = (_MMP_VE_INFO_INST_PTR_T)pv_info_obj;
    HANDLE_T h_img = (HANDLE_T)(UINT32)pv_h_img;

    INT32 i4_ret = MMPR_OK;

    if(NULL == pt_this_obj || NULL_HANDLE == h_img)
    {
        MMP_ASSERT(0);
        MMP_DBG_INFO(("{MMP} null handle load\n"));
        return;
    }

    /**/
    if(pt_this_obj->h_img != h_img || NULL_HANDLE == pt_this_obj->h_img)
    {
        /*notification is out of date*/
        MMP_DBG_INFO(("{MMP} notification out of date %s:%s:%d\n", __FUNCTION__, __FUNCTION__, __LINE__));
        return;
    }

    if(VIDEO_ENGINE_INFO_FLAG_LOADING & pt_this_obj->ui1_flag)
    {
        i4_ret = _mmp_ve_info_image_show_ex(
                    (_MMP_VE_PLAY_INST_PTR_T)pt_this_obj->pt_play_inst,
                    pt_this_obj
                    );
        if(MMPR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        pt_this_obj->ui1_flag |= VIDEO_ENGINE_INFO_FLAG_SUCCESS;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_image_open_cb_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_ve_info_image_open_cb_ex(
                    HANDLE_T                        h_handle,
                    const VOID*                     pv_tag,
                    IMG_NFY_EVENT_TYPE_T            e_event,
                    const VOID*                     pv_data
                    )
{
    IMG_NFY_LOAD_WITH_TAG_T*    pt_nfy;

    if(NULL_HANDLE == h_handle || NULL == pv_tag)
    {
        MMP_DBG_INFO(("{MMP} null handle open \n"));
        return;
    }

    if(IMG_NFY_LOAD_COMPLETE_WITH_TAG == e_event ||
       IMG_NFY_LOAD_COMPLETE_TYPE     == e_event) /*pv_data is an INT32 value that indicates the return value of loading image*/
    {
        if(NULL == pv_data)
        {
            MMP_ASSERT(0);
            MMP_DBG_INFO(("{MMP} null data open \n"));
            return;
        }

        pt_nfy = (IMG_NFY_LOAD_WITH_TAG_T*)pv_data;

        /* post a message to itself */
        mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_CRITICAL,
                    _mmp_ve_info_image_load_nfy_fct_ex,
                    (VOID*)pv_tag,
                    (VOID*)h_handle,
                    (VOID*)pt_nfy->i4_ret,
                    (VOID*)pt_nfy->pv_tag
                    );
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_open_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _mmp_ve_info_cover_pic_open(_MMP_VE_PLAY_INST_PTR_T    pt_this,    /* in  */
                                            _MMP_VE_ELMT_INFO_PTR_T    pt_this_obj /* in  */)
{
    CHAR* pc_str1 = NULL;
    UINT32 i = 0;
    INT32 i4_ret = 0;
    MINFO_INFO_T t_minfo_rec;
    SIZE_T z_size = sizeof(MINFO_INFO_T);
    UINT32 ui4_mask, ui4_ofs, ui4_len;
    UINT64 ui8_ofs;
    UINT32 ui4_read = 0;
    FM_FILE_INFO_T t_info;
    HANDLE_T h_file_usb = NULL_HANDLE;
    MEDIA_FORMAT_T t_format;
    CHAR* ps_elmt_name = NULL;

    t_format.e_media_type = MEDIA_TYPE_UNKNOWN;
    t_format.b_fav_recg_only = FALSE;/*Play->False,other->True*/

    i4_ret = mmp_fid_get(pt_this_obj->t_elmt_fid, &ps_elmt_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} mmp fid get fail ,i4_ret:%d\n",i4_ret));
        return i4_ret;
    }

    if ((NULL == pt_this) || (NULL == ps_elmt_name))
    {
       MMP_DBG_INFO(("{MMP} MMPR_INV_ARG %s:%s:%d \n", __FUNCTION__, __FUNCTION__, __LINE__));
       return MMPR_INV_ARG;
    }
    t_g_info_inst_cover_pic.ui4_info_ver = (VIDEO_ENGINE_INFO_VER_INVALID == (++pt_this->ui4_info_id_counter)) ? (++pt_this->ui4_info_id_counter) : pt_this->ui4_info_id_counter;
    t_g_info_inst_cover_pic.ui4_load_ver = VIDEO_ENGINE_LOAD_VER_INVALID;
    t_g_info_inst_cover_pic.e_elmt_type = _MMP_VE_ELMT_TYPE_AUDIO;

    /*Close it first:For CR 71217*/
    i4_ret = _mmp_ve_info_cover_pic_close();
    MMPR_LOG_ON_FAIL(i4_ret);
    
    do
    {
        /* PCM has no meta info */
        pc_str1 = c_strrchr(ps_elmt_name, (CHAR)'.');
        if ((NULL != pc_str1) && (0 == c_strcmp(pc_str1, ".pcm")))
        {
            break;
        }
#ifdef APP_NET_DLNA_SUPPORT
        if (FALSE == mmp_util_dlna_is_seek_supported((CHAR*)ps_elmt_name))
        {
            MMP_DBG_INFO(("{MMP} %s[%d] dlna not seekable\r\n",__FUNCTION__,__LINE__));
            return MMPR_NOT_SUPPORT;
        }
#endif

    #if 0  /* fix DTV00841805 progress 00-02*/
        i4_ret = c_minfo_fopen_sync(
                        (CHAR*)ps_info_name,
                        &t_format,
                        &t_g_info_inst_cover_pic.h_minfo
                        );
        if(MINFOR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} Hasn't cover:%s:%s:%d\n", __FUNCTION__, __FUNCTION__, __LINE__));
            t_g_info_inst_cover_pic.h_minfo = NULL_HANDLE;
            break;
        }

        c_memset(&t_minfo_rec, 0, sizeof(MINFO_INFO_T));

        i4_ret = c_minfo_get_info(
                        t_g_info_inst_cover_pic.h_minfo,
                        MINFO_INFO_TYPE_ID3_DATA,
                        1,
                        (VOID*)(&t_minfo_rec),
                        &z_size
                        );
    #endif
        t_g_info_inst_cover_pic.h_minfo     = pt_this_obj->h_elmt_hdl;
        
        c_memset(&t_minfo_rec, 0, sizeof(MINFO_INFO_T));
        t_minfo_rec.e_info_type = MINFO_INFO_TYPE_ID3_DATA;

        i4_ret = c_svctx_media_get_info(
                    pt_this->h_svctx_hdl,
                    pt_this_obj->h_elmt_hdl,
                    SVCTX_MM_GET_TYPE_META_DATA,
                    (VOID*)&t_minfo_rec,
                    z_size
                        );
        
        if(MINFOR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} Hasn't cover:%s:%d:%d\n", __FUNCTION__, __LINE__,i4_ret));
            break;
        }

        ui4_mask = t_minfo_rec.u.t_id3_data.ui4_pic_bitmask;
        if(0 == ui4_mask)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMP_DBG_INFO(("{MMP} Hasn't cover:%s:%d:%d\n", __FUNCTION__, __LINE__,i4_ret));
            break;
        }

        for(i = 0; i <= MINFO_ID3_PIC_STUDIO_LOGOTYPE; i++)
        {
            if(ui4_mask & ((UINT32)(1 << i)))
            {
                break; /* use i as the index to retrieve ID3 pic data */
            }
        }

        if(MINFO_ID3_PIC_STUDIO_LOGOTYPE <= i)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        t_format = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].t_format;
        if(MEDIA_IMG_SUBTYPE_JPG != t_format.t_media_subtype.u.e_img_subtype)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        ui4_ofs = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_starting_offset;
        ui4_len = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_length;

        /*Free it first*/
        if(NULL!=t_g_info_inst_cover_pic.pui1_data)
        {
            c_mem_free(t_g_info_inst_cover_pic.pui1_data);
            t_g_info_inst_cover_pic.pui1_data=NULL;
        }

        /*alloc buf*/
        t_g_info_inst_cover_pic.pui1_data = c_mem_alloc((SIZE_T)ui4_len);
        if(NULL == t_g_info_inst_cover_pic.pui1_data)
        {
            i4_ret = MMPR_OUT_OF_MEM;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }
        c_memset(t_g_info_inst_cover_pic.pui1_data, 0 , (SIZE_T)ui4_len);

        i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE, ps_elmt_name, &t_info);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_open(FM_ROOT_HANDLE, ps_elmt_name, FM_READ_ONLY, 0777, FALSE, &h_file_usb);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret =  c_fm_lseek(h_file_usb, (INT64)ui4_ofs, FM_SEEK_BGN, &ui8_ofs);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_read(h_file_usb, t_g_info_inst_cover_pic.pui1_data, ui4_len, &ui4_read);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_close(h_file_usb);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_img_mopen(
                        t_g_info_inst_cover_pic.pui1_data,
                        (SIZE_T)ui4_len,
                        "JPG",
                        _mmp_ve_info_image_open_cb_ex,
                        &t_g_info_inst_cover_pic,
                        &t_g_info_inst_cover_pic.h_img
                        );
        if(IMGR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_img_get_dimension(
                        t_g_info_inst_cover_pic.h_img,
                        INTRA_IMG_PRIMARY_IMG_TYPE,
                        &t_g_info_inst_cover_pic.z_img_w,
                        &t_g_info_inst_cover_pic.z_img_h
                        );
        
        ui4_cover_pic_w = (UINT32)t_g_info_inst_cover_pic.z_img_w;
        ui4_cover_pic_h = (UINT32)t_g_info_inst_cover_pic.z_img_h;
        if(IMGR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        return  MMPR_OK;

    }while(0);

    if(MMPR_OK != i4_ret)
    {
        if(NULL_HANDLE != h_file_usb)
        {
            c_fm_close(h_file_usb);
            h_file_usb = NULL_HANDLE;
        }
    }

    _mmp_ve_info_cover_pic_close();

    return MMPR_NOT_SUPPORT;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_close_cover_pic
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_ve_info_cover_pic_close(VOID)
{
    _MMP_VE_INFO_INST_PTR_T pt_this_obj = &t_g_info_inst_cover_pic;

    if(NULL == pt_this_obj)
    {
        MMP_DBG_INFO(("{MMP} pt_this_obj null %s:%d \n", __FUNCTION__, __LINE__));
        return MMPR_OK;
    }

    if(NULL != pt_this_obj->pui1_data)
    {
        c_mem_free(pt_this_obj->pui1_data);
        pt_this_obj->pui1_data = NULL;
    }

    if(NULL_HANDLE != pt_this_obj->h_minfo)
    {
        c_minfo_close(pt_this_obj->h_minfo);
        pt_this_obj->h_minfo = NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this_obj->h_img)
    {
        c_img_close(pt_this_obj->h_img);
        pt_this_obj->h_img = NULL_HANDLE;
    }

    VIDEO_ENGINE_INFO_RESET(*pt_this_obj);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_cover_pic_load
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 video_engine_cover_load(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_RECT_T*                pt_rect,          /* in  */
                    MMP_FP_THUMB_COORDS_T           e_coord           /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T t_fp_load_thumb={0};
    INT32 i4_ret;

    if(NULL == pt_rect || NULL == pt_elmt)
    {
        MMP_DBG_INFO(("{MMP} MMPR_INV_ARG %s:%d \n", __FUNCTION__, __LINE__));
        return MMPR_INV_ARG;
    }
    
    i4_ret = _mmp_ve_info_cover_pic_open(pt_this, pt_elmt);
    if(MMPR_OK==i4_ret)
    {
        b_g_has_cover_pic = TRUE;
    }
    else
    {
        b_g_has_cover_pic = FALSE;
        return MMPR_OK;
    }

    i4_ret = mmp_drc_switch_mode(MMP_DRC_MODE_THUMB);
    IS_MMPR_OK(i4_ret);

    t_fp_load_thumb.e_coords=e_coord;
    t_fp_load_thumb.pt_rect=pt_rect;

    return _mmp_ve_info_image_load_ex(&t_g_play_inst_cover_pic,
                            &t_g_info_inst_cover_pic,
                            &t_fp_load_thumb);
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_cover_pic_stop
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 video_engine_cover_stop(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    INT32 i4_ret;

    if(!b_g_has_cover_pic)
    {
        return MMPR_OK;
    }

    /*unlock resource from DRC*/
    i4_ret = _mmp_ve_info_thumb_lock_buf(&t_g_play_inst_cover_pic, FALSE);
    /*MMPR_INV_ARG -> has been unlock*/
    if(MMPR_INV_ARG!=i4_ret)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _mmp_ve_info_image_stop_ex(&t_g_play_inst_cover_pic,
                                     &t_g_info_inst_cover_pic);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _mmp_ve_info_cover_pic_close();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_drc_switch_mode(MMP_DRC_MODE_FREE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_cover_pic_load
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 INT32 video_engine_has_cover_pic(MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                               BOOL                            *pb_value)
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret;

    if(NULL == pt_elmt)
    {
        MMP_DBG_INFO(("{MMP} MMPR_INV_ARG %s:%d \n", __FUNCTION__,__LINE__));
        return MMPR_INV_ARG;
    }
    
    if (MMP_FID_NULL_REC_IDX == pt_elmt->t_elmt_fid) 
    {
        b_g_has_cover_pic = FALSE;
        *pb_value = FALSE;
        
        return MMPR_OK;
    }

#if 0//#ifdef APP_NET_DLNA_SUPPORT
{
    MMP_FILE_SRC_TYPE_T e_file_src_type = MMP_FILE_SRC_UNKNOWN;

    i4_ret = mmp_util_get_file_src_type(ps_elmt_name, &e_file_src_type);
    if(MMPR_OK != i4_ret)
    {
        e_file_src_type = MMP_FILE_SRC_MASS_STRG;
    } 
    if ((MMP_FILE_SRC_DLNA == e_file_src_type)
#if	defined(APP_DMR_SUPPORT)&&defined(APP_MMP_DMR_SHOW_COVER_PICTURE_SUPPORT)
		&&(!a_mmp_dmr_is_active())
#endif		
		)
    {
        b_g_has_cover_pic = FALSE;
        *pb_value = b_g_has_cover_pic;
        DBG_INFO(("Do not load cover in dlna audio case\n"));
        return MMPR_OK;
    }
}
#endif
    
    i4_ret = _mmp_ve_info_cover_pic_open(pt_this, pt_elmt);
    if(MMPR_OK==i4_ret)
    {
        b_g_has_cover_pic = TRUE;
    }
    else
    {
        b_g_has_cover_pic = FALSE;
    }
    
    i4_ret=_mmp_ve_info_cover_pic_close();
    MMPR_LOG_ON_FAIL(i4_ret);
    
    *pb_value = b_g_has_cover_pic;
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: video_engine_get_cover_pic_size
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 INT32 video_engine_get_cover_pic_size(MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                                   UINT32                          *pui4_w,
                                   UINT32                          *pui4_h)
{
    *pui4_w = ui4_cover_pic_w;
    *pui4_h = ui4_cover_pic_h;
    
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_open_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _mmp_ve_info_cover_pic_open_ex(const CHAR*   ps_info_name,
                                   MMP_UTIL_IMG_TPL_INFO_T        *pt_info)
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = &t_g_play_inst_cover_pic;
    CHAR* pc_str1 = NULL;
    UINT32 i = 0;
    INT32 i4_ret = 0;
    MINFO_INFO_T t_minfo_rec;
    SIZE_T z_size = sizeof(MINFO_INFO_T);
    UINT32 ui4_mask, ui4_ofs, ui4_len;
    UINT64 ui8_ofs;
    UINT32 ui4_read = 0;
    FM_FILE_INFO_T t_info;
    HANDLE_T h_file_usb = NULL_HANDLE;
    MEDIA_FORMAT_T t_format;

    t_format.e_media_type = MEDIA_TYPE_UNKNOWN;
    t_format.b_fav_recg_only = FALSE;/*Play->False,other->True*/

    if ((NULL == pt_this) || (NULL == ps_info_name))
    {
        MMP_DBG_INFO(("{MMP} MMPR_INV_ARG %s:%%d \n", __FUNCTION__,__LINE__));
       return MMPR_INV_ARG;
    }
    t_g_info_inst_cover_pic.ui4_info_ver = (VIDEO_ENGINE_INFO_VER_INVALID == (++pt_this->ui4_info_id_counter)) ? (++pt_this->ui4_info_id_counter) : pt_this->ui4_info_id_counter;
    t_g_info_inst_cover_pic.ui4_load_ver = VIDEO_ENGINE_LOAD_VER_INVALID;
    t_g_info_inst_cover_pic.e_elmt_type = _MMP_VE_ELMT_TYPE_AUDIO;

    /*Close it first:For CR 71217*/
    i4_ret = _mmp_ve_info_cover_pic_close();
    MMPR_LOG_ON_FAIL(i4_ret);
    
    do
    {
        /* PCM has no meta info */
        pc_str1 = c_strrchr(ps_info_name, (CHAR)'.');
        if ((NULL != pc_str1) && (0 == c_strcmp(pc_str1, ".pcm")))
        {
            break;
        }
        
        i4_ret = c_minfo_fopen_sync(
                        (CHAR*)ps_info_name,
                        &t_format,
                        &t_g_info_inst_cover_pic.h_minfo
                        );
        if(MINFOR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} Hasn't cover:%s:%d\n", __FUNCTION__,__LINE__));
            t_g_info_inst_cover_pic.h_minfo = NULL_HANDLE;
            break;
        }

        c_memset(&t_minfo_rec, 0, sizeof(MINFO_INFO_T));

        i4_ret = c_minfo_get_info(
                        t_g_info_inst_cover_pic.h_minfo,
                        MINFO_INFO_TYPE_ID3_DATA,
                        1,
                        (VOID*)(&t_minfo_rec),
                        &z_size
                        );
        if(MINFOR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} Hasn't cover:%s:%d,i4_ret:%d\n", __FUNCTION__,__LINE__,i4_ret));
            break;
        }

        ui4_mask = t_minfo_rec.u.t_id3_data.ui4_pic_bitmask;
        if(0 == ui4_mask)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMP_DBG_INFO(("{MMP} Hasn't cover:%s:%d\n", __FUNCTION__,__LINE__));
            break;
        }

        for(i = 0; i <= MINFO_ID3_PIC_STUDIO_LOGOTYPE; i++)
        {
            if(ui4_mask & ((UINT32)(1 << i)))
            {
                break; /* use i as the index to retrieve ID3 pic data */
            }
        }

        if(MINFO_ID3_PIC_STUDIO_LOGOTYPE <= i)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        t_format = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].t_format;
        if(MEDIA_IMG_SUBTYPE_JPG != t_format.t_media_subtype.u.e_img_subtype)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        ui4_ofs = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_starting_offset;
        ui4_len = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_length;


       /*Free it first*/
       if(NULL!=pt_info->pui1_data)
       {
           c_mem_free(pt_info->pui1_data);
           pt_info->pui1_data=NULL;
       }
       
       /*alloc buf*/
       pt_info->pui1_data = c_mem_alloc((SIZE_T)ui4_len);
       if(NULL == pt_info->pui1_data)
       {
           i4_ret = MMPR_OUT_OF_MEM;
           MMPR_LOG_ON_FAIL(i4_ret);
           break;
       }
       c_memset(pt_info->pui1_data, 0 , (SIZE_T)ui4_len);

        i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE, ps_info_name, &t_info);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_open(FM_ROOT_HANDLE, ps_info_name, FM_READ_ONLY, 0777, FALSE, &h_file_usb);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret =  c_fm_lseek(h_file_usb, (INT64)ui4_ofs, FM_SEEK_BGN, &ui8_ofs);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_read(h_file_usb, pt_info->pui1_data, ui4_len, &ui4_read);
        pt_info->ui4_size = ui4_len;
        
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }
        
        i4_ret = c_fm_close(h_file_usb);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        return  MMPR_OK;

    }while(0);

    if(MMPR_OK != i4_ret)
    {
        if(NULL_HANDLE != h_file_usb)
        {
            c_fm_close(h_file_usb);
            h_file_usb = NULL_HANDLE;
        }
    }

    _mmp_ve_info_cover_pic_close();

    return MMPR_NOT_SUPPORT;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_cover_pic_load
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 video_engine_cover_load_image_template(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_RECT_T*                pt_rect,          /* in  */
                    MMP_FP_THUMB_COORDS_T           e_coord,           /* in  */
                    MMP_UTIL_IMG_TPL_INFO_T        *pt_info
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    CHAR* ps_elmt_name = NULL;
    INT32 i4_ret;

    if(NULL == pt_rect || NULL == pt_elmt)
    {
        MMP_DBG_INFO(("{MMP} MMPR_INV_ARG %s:%d \n", __FUNCTION__,__LINE__));
        return MMPR_INV_ARG;
    }
    
    i4_ret = mmp_fid_get(pt_elmt->t_elmt_fid, &ps_elmt_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} mmp fid get fail:%d\n",i4_ret));
        return i4_ret;
    }
    
    i4_ret = _mmp_ve_info_cover_pic_open_ex(ps_elmt_name,pt_info);
    if(MMPR_OK==i4_ret)
    {
        b_g_has_cover_pic = TRUE;
    }
    else
    {
        b_g_has_cover_pic = FALSE;
        return MMPR_OK;
    }

    i4_ret =mmp_util_create_img_tpl_from_file_ex(ps_elmt_name,
                                              WGL_IMG_ST_NO_SEGMENT,
                                              pt_info);
    IS_MMPR_OK(i4_ret);
    
    return MMPR_OK;
    
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_ve_info_open_ex
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _mmp_ve_info_cover_picture_open(const CHAR*   ps_info_name)
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = &t_g_play_inst_cover_pic;
    CHAR* pc_str1 = NULL;
    UINT32 i = 0;
    INT32 i4_ret = 0;
    MINFO_INFO_T t_minfo_rec;
    SIZE_T z_size = sizeof(MINFO_INFO_T);
    UINT32 ui4_mask, ui4_ofs, ui4_len;
    UINT64 ui8_ofs;
    UINT32 ui4_read = 0;
    FM_FILE_INFO_T t_info;
    HANDLE_T h_file_usb = NULL_HANDLE;
    MEDIA_FORMAT_T t_format;

    t_format.e_media_type = MEDIA_TYPE_UNKNOWN;
    t_format.b_fav_recg_only = FALSE;/*Play->False,other->True*/

    if ((NULL == pt_this) || (NULL == ps_info_name))
    {
        DBG_LOG_PRINT(("MMPR_INV_ARG %s:%s:%d \n", __FILE__, __FUNCTION__, __LINE__));
       return MMPR_INV_ARG;
    }
    t_g_info_inst_cover_pic.ui4_info_ver = (VIDEO_ENGINE_INFO_VER_INVALID == (++pt_this->ui4_info_id_counter)) ? (++pt_this->ui4_info_id_counter) : pt_this->ui4_info_id_counter;
    t_g_info_inst_cover_pic.ui4_load_ver = VIDEO_ENGINE_LOAD_VER_INVALID;
    t_g_info_inst_cover_pic.e_elmt_type = _MMP_VE_ELMT_TYPE_AUDIO;

    /*Close it first:For CR 71217*/
    i4_ret = _mmp_ve_info_cover_pic_close();
    MMPR_LOG_ON_FAIL(i4_ret);

    do
    {
        /* PCM has no meta info */
        pc_str1 = c_strrchr(ps_info_name, (CHAR)'.');
        if ((NULL != pc_str1) && (0 == c_strcmp(pc_str1, ".pcm")))
        {
            break;
        }

        i4_ret = c_minfo_fopen_sync(
                        (CHAR*)ps_info_name,
                        &t_format,
                        &t_g_info_inst_cover_pic.h_minfo
                        );
        if(MINFOR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("Hasn't cover:%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            t_g_info_inst_cover_pic.h_minfo = NULL_HANDLE;
            break;
        }

        c_memset(&t_minfo_rec, 0, sizeof(MINFO_INFO_T));

        i4_ret = c_minfo_get_info(
                        t_g_info_inst_cover_pic.h_minfo,
                        MINFO_INFO_TYPE_ID3_DATA,
                        1,
                        (VOID*)(&t_minfo_rec),
                        &z_size
                        );
        if(MINFOR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("Hasn't cover:%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            break;
        }

        ui4_mask = t_minfo_rec.u.t_id3_data.ui4_pic_bitmask;
        if(0 == ui4_mask)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            DBG_LOG_PRINT(("Hasn't cover:%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            break;
        }

        for(i = 0; i <= MINFO_ID3_PIC_STUDIO_LOGOTYPE; i++)
        {
            if(ui4_mask & ((UINT32)(1 << i)))
            {
                break; /* use i as the index to retrieve ID3 pic data */
            }
        }

        if(MINFO_ID3_PIC_STUDIO_LOGOTYPE <= i)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        t_format = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].t_format;
        if(MEDIA_IMG_SUBTYPE_JPG != t_format.t_media_subtype.u.e_img_subtype)
        {
            i4_ret = MMPR_NOT_SUPPORT;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        ui4_ofs = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_starting_offset;
        ui4_len = t_minfo_rec.u.t_id3_data.at_id3_attatched_pic[i].ui4_length;

        /*Free it first*/
        if(NULL!=t_g_info_inst_cover_pic.pui1_data)
        {
            c_mem_free(t_g_info_inst_cover_pic.pui1_data);
            t_g_info_inst_cover_pic.pui1_data=NULL;
        }

        /*alloc buf*/
        t_g_info_inst_cover_pic.pui1_data = c_mem_alloc((SIZE_T)ui4_len);
        if(NULL == t_g_info_inst_cover_pic.pui1_data)
        {
            i4_ret = MMPR_OUT_OF_MEM;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }
        c_memset(t_g_info_inst_cover_pic.pui1_data, 0 , (SIZE_T)ui4_len);

        i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE, ps_info_name, &t_info);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_open(FM_ROOT_HANDLE, ps_info_name, FM_READ_ONLY, 0777, FALSE, &h_file_usb);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret =  c_fm_lseek(h_file_usb, (INT64)ui4_ofs, FM_SEEK_BGN, &ui8_ofs);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_read(h_file_usb, t_g_info_inst_cover_pic.pui1_data, ui4_len, &ui4_read);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_fm_close(h_file_usb);
        if(FMR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_img_mopen(
                        t_g_info_inst_cover_pic.pui1_data,
                        (SIZE_T)ui4_len,
                        "JPG",
                        _mmp_ve_info_image_open_cb_ex,
                        &t_g_info_inst_cover_pic,
                        &t_g_info_inst_cover_pic.h_img
                        );
        if(IMGR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_img_get_dimension(
                        t_g_info_inst_cover_pic.h_img,
                        INTRA_IMG_PRIMARY_IMG_TYPE,
                        &t_g_info_inst_cover_pic.z_img_w,
                        &t_g_info_inst_cover_pic.z_img_h
                        );

        ui4_cover_pic_w = (UINT32)t_g_info_inst_cover_pic.z_img_w;
        ui4_cover_pic_h = (UINT32)t_g_info_inst_cover_pic.z_img_h;
        if(IMGR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        return  MMPR_OK;

    }while(0);

    if(MMPR_OK != i4_ret)
    {
        if(NULL_HANDLE != h_file_usb)
        {
            c_fm_close(h_file_usb);
            h_file_usb = NULL_HANDLE;
        }
    }

    _mmp_ve_info_cover_pic_close();

    return MMPR_NOT_SUPPORT;
}

/*-----------------------------------------------------------------------------
 * Name: mmp_ve_info_cover_pic_load
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 INT32 video_engine_file_has_cover_pic(CHAR*         ps_elmt_name,
                                             BOOL         *pb_value)
{

    INT32 i4_ret;

    if(NULL == ps_elmt_name)
    {
        DBG_LOG_PRINT(("MMPR_INV_ARG %s:%s:%d \n", __FILE__, __FUNCTION__, __LINE__));
        return MMPR_INV_ARG;
    }

#ifdef APP_NET_DLNA_SUPPORT
{
    MMP_FILE_SRC_TYPE_T e_file_src_type = MMP_FILE_SRC_UNKNOWN;

    i4_ret = mmp_util_get_file_src_type(ps_elmt_name, &e_file_src_type);
    if(MMPR_OK != i4_ret)
    {
        e_file_src_type = MMP_FILE_SRC_MASS_STRG;
    }
    if ((MMP_FILE_SRC_DLNA == e_file_src_type)
#if	defined(APP_DMR_SUPPORT)&&defined(APP_MMP_DMR_SHOW_COVER_PICTURE_SUPPORT)
		&&(!a_mmp_dmr_is_active())
#endif
		)
    {
        b_g_has_cover_pic = FALSE;
        *pb_value = b_g_has_cover_pic;
        DBG_INFO(("Do not load cover in dlna audio case\n"));
        return MMPR_OK;
    }
}
#endif

    i4_ret = _mmp_ve_info_cover_picture_open(ps_elmt_name);
    if(MMPR_OK==i4_ret)
    {
        b_g_has_cover_pic = TRUE;
    }
    else
    {
        b_g_has_cover_pic = FALSE;
    }

    i4_ret=_mmp_ve_info_cover_pic_close();
    MMPR_LOG_ON_FAIL(i4_ret);

    *pb_value = b_g_has_cover_pic;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: video_engine_file_cover_load
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 video_engine_file_cover_load(
                    CHAR*                           ps_elmt_name,     /* in  */
                    const GL_RECT_T*                pt_rect,          /* in  */
                    MMP_FP_THUMB_COORDS_T           e_coord           /* in  */
                    )
{
    MMP_FP_INFO_CMD_PARAM_LOAD_THUMB_T t_fp_load_thumb={0};
    INT32 i4_ret;

    if(NULL == pt_rect || NULL == ps_elmt_name)
    {
        DBG_LOG_PRINT(("MMPR_INV_ARG %s:%s:%d \n", __FILE__, __FUNCTION__, __LINE__));
        return MMPR_INV_ARG;
    }

    i4_ret = _mmp_ve_info_cover_picture_open(ps_elmt_name);
    if(MMPR_OK==i4_ret)
    {
        b_g_has_cover_pic = TRUE;
    }
    else
    {
        b_g_has_cover_pic = FALSE;
        return MMPR_OK;
    }

    i4_ret = mmp_drc_switch_mode(MMP_DRC_MODE_THUMB);
    IS_MMPR_OK(i4_ret);

    t_fp_load_thumb.e_coords=e_coord;
    t_fp_load_thumb.pt_rect=pt_rect;

    return _mmp_ve_info_image_load_ex(&t_g_play_inst_cover_pic,
                            &t_g_info_inst_cover_pic,
                            &t_fp_load_thumb);
}

#endif

#if defined(_MMP_VERC_PLAY_THUMB_SUPPORT)
static VOID _video_engine_thumb_deal_nfy_fct(
                    VOID*                           pv_nfy_tag,       /* in  */
                    VOID*                           pv_ctx_cond,      /* in  */
                    VOID*                           pv_nfy_code,      /* in  */
                    VOID*                           pv_stm_type       /* in  */
                    )
{
    _MMP_VE_INST_ID_T t_inst_id = (_MMP_VE_INST_ID_T)(((UINT32)pv_nfy_tag & 0xFFFF0000) >> 16);
    _MMP_VE_FILE_ID_T t_file_id = (_MMP_VE_FILE_ID_T)(((UINT32)pv_nfy_tag & 0x0000FFFF));

    if(_MMP_VERC_PLAY_INST_NUM <= t_inst_id || NULL == video_engine_get_inst_by_idx(t_inst_id))
    {
        MMP_ASSERT(FALSE);
        MMP_DBG_INFO(("{MMP} thumb %s:%d\n", __FUNCTION__,__LINE__));
        return;
    }

    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)video_engine_get_inst_by_idx(t_inst_id);
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    SVCTX_NTFY_CODE_T e_mw_nfy_code = (SVCTX_NTFY_CODE_T)(UINT32)pv_nfy_code;

	if(SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_CANCEL == e_mw_nfy_code)
	{
		INT32 i4_ret;
		
		MMP_DBG_INFO(("{MMP} _video_engine_thumb_deal_nfy_fct SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_CANCEL ######### \n"));

        i4_ret = mmp_drc_unlock_buf(pt_this->pt_buf_thumb_show);
        if(MMPR_OK != i4_ret)
        {
            return;
        }
		pt_this->pt_buf_thumb_show = NULL;
	
		if(pt_this->pf_play_nfy_fct!=NULL)    
	    {
	    	pt_this->pf_play_nfy_fct(MMP_VE_NFY_CODE_MEDIA_THUMBNAIL_CANCEL_STOP, NULL);
	    }

		return;
	}
	
#ifdef APP_MMP_PVR_SUPPORT	
	if(SVCTX_NTFY_CODE_MEDIA_PVR_THUMBNAIL_PARENT_RATING == e_mw_nfy_code)
	{
		MMP_DBG_INFO(("{MMP} vide_engine.c _video_engine_thumb_deal_nfy_fct SVCTX_NTFY_CODE_MEDIA_PVR_THUMBNAIL_PARENT_RATING ######### \n"));

		if(pt_this->pf_play_nfy_fct!=NULL)    
	    {
	    	pt_this->pf_play_nfy_fct(MMP_VE_NFY_CODE_MEDIA_PVR_THUMBNAIL_PIN_VALID_PARENT_RATING, NULL);
	    }
		
		return;
	}

	//<<<modify_by_weijia_20130924_for_pvr_guidance_description_blocked
	if(SVCTX_NTFY_CODE_MEDIA_GUIDANCE_BLOCKED_DUR_THUMB == e_mw_nfy_code)
	{
		MMP_DBG_INFO(("{MMP} vide_engine.c _video_engine_thumb_deal_nfy_fct SVCTX_NTFY_CODE_MEDIA_GUIDANCE_BLOCKED_DUR_THUMB ######### \n"));

		if(pt_this->pf_play_nfy_fct!=NULL)    
	    {
	    	pt_this->pf_play_nfy_fct(MMP_VE_NFY_CODE_MEDIA_PVR_GUIDANCE_BLOCKED_DUR_THUMB, NULL);
	    }
		
		return;
	}
	//>>>

	if(SVCTX_NTFY_CODE_MEDIA_PVR_PROG_BLOCKED == e_mw_nfy_code)
	{
		MMP_DBG_INFO(("{MMP} vide_engine.c _video_engine_thumb_deal_nfy_fct SVCTX_NTFY_CODE_MEDIA_PVR_PROG_BLOCKED ######### \n"));

		if(pt_this->pf_play_nfy_fct!=NULL)    
	    {
	    	pt_this->pf_play_nfy_fct(MMP_VE_NFY_CODE_MEDIA_PVR_PIN_VALID_PROG_BLOCKED, NULL);
	    }
		
		return;
	}	
#endif	

    if(NULL == pt_this || NULL == pt_elmt_1st)
    {
        MMP_ASSERT(FALSE);
        return;
    }

#ifdef CLI_SUPPORT
    MMP_DBG_INFO(("{MMP} <<LOAD>> [%u <-> %u] ", t_file_id, pt_elmt_1st->t_file_id));
    mmp_video_engine_cli_save_nfy_code(e_mw_nfy_code);
#endif /* CLI_SUPPORT */

    if(t_file_id != pt_elmt_1st->t_file_id)
    {
        return;
    }

    if(SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_DONE == e_mw_nfy_code)
    {
        MMP_VE_DIVX_CERT_T t_divx_cert;
        INT32 i4_ret;

        i4_ret = mmp_drc_unlock_buf(pt_this->pt_buf_thumb_show);
        if(MMPR_OK != i4_ret)
        {
            return;
        }
        pt_this->pt_buf_thumb_show = NULL;

        if(_MMP_VERC_HAS_DIVX_SUPPORT())    
        {
            _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
            DRM_INFO_SVCTX_T t_drm_info_svctx = {0};
                
            i4_ret = c_svctx_media_get_info(
                                pt_this->h_svctx_hdl,
                                pt_elmt->h_elmt_hdl,
                                SVCTX_DRM_GET_TYPE_INFO,
                                &t_drm_info_svctx,
                                sizeof(DRM_INFO_SVCTX_T)
                                );
            MMP_DBG_INFO(("[JY][START_PLAY][MEDIA_GET_INFO][RET] %d\n", i4_ret));
        }
        video_engine_start2play_cust((MMP_VE_PLAY_INST_PTR_T)pt_this, &t_divx_cert);
    }
}

/*----------------------------------------------------------------------------
 * Name: _svctx_media_play_nfy_fct
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
static VOID _video_engine_thumb_load_nfy_fct(
                    HANDLE_T                        h_ctx_hdl,        /* in  */
                    SVCTX_COND_T                    e_ctx_cond,       /* in  */
                    SVCTX_NTFY_CODE_T               e_nfy_code,       /* in  */
                    STREAM_TYPE_T                   e_stm_type,       /* in  */
                    VOID*                           pv_nfy_tag        /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pv_nfy_tag;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    UINT32 ui4_nfy_tag = 0;

    if(NULL == pt_this || NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return;
    }

    ui4_nfy_tag = ((UINT32)pt_this->t_inst_id << 16) |
                  ((UINT32)pt_elmt->t_file_id);

    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _video_engine_thumb_deal_nfy_fct,
                    (VOID*)(UINT32)ui4_nfy_tag,
                    (VOID*)(UINT32)e_ctx_cond,
                    (VOID*)(UINT32)e_nfy_code,
                    (VOID*)(UINT32)e_stm_type
                    );
}

/*----------------------------------------------------------------------------
 * Name: video_engine_thumb_full_stop
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
INT32 video_engine_thumb_full_stop(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret;
    
    if ((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }
    
    if (_MMP_VE_ELMT_STAT_THUMB == pt_elmt->e_elmt_stat &&
        NULL_HANDLE != pt_this->h_svctx_hdl &&
        NULL_HANDLE != pt_elmt->h_elmt_hdl)
    {
        i4_ret = c_svctx_media_sync_cancel_load_thumbnail(
                           pt_this->h_svctx_hdl, 
                           pt_elmt->h_elmt_hdl);
        if (i4_ret != SVCTXR_OK)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_media_sync_cancel_load_thumbnail %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }
        pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_STOP;
    }
        
    if (NULL != pt_this->pt_buf_thumb_show)
    {
        /*Unlock resource from DRC*/
        i4_ret = mmp_drc_unlock_buf(pt_this->pt_buf_thumb_show);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} mmp drc unlock buf fail:%d \n",i4_ret));
            return i4_ret;
        }
        pt_this->pt_buf_thumb_show = NULL;
    }
    
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_thumb_load
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
INT32 video_engine_thumb_load(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect     /* in  */
                    )
{
    MMP_VE_DIVX_CERT_T t_divx_cert;
    
    return video_engine_thumb_load_ex(
                    pt_play_inst,
                    e_thumb_coord,
                    pt_thumb_rect,
                    &t_divx_cert
                    );
}

/*----------------------------------------------------------------------------
 * Name: video_engine_thumb_load_ex
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
INT32 video_engine_thumb_load_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect,    /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    
    MINFO_INFO_T t_minfo_rec;
    SIZE_T z_size = sizeof(MINFO_INFO_T);
    
    SVCTX_VIDEO_THUMBNAIL_INFO_T t_thumb_info = {0};
    GL_RECT_T t_thumb_rect;
    INT32 i4_ret;
    
    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        MMP_DBG_INFO(("{MMP} null handle %s:%d \n", __FUNCTION__,__LINE__));
        return MMPR_INTERNAL_ERROR;
    }
    
    if(NULL_HANDLE == pt_elmt->h_elmt_hdl)
    {
        pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

        if(MMPR_NO_DATA == pt_elmt->i4_elmt_ret)
        {
            return MMPR_NO_DATA;
        }
        else
        {
            return MMPR_NOT_SUPPORT;
        }
    }
    if (_MMP_VE_ELMT_STAT_NOT_SUPPORT == pt_elmt->e_elmt_stat)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (_MMP_VE_ELMT_STAT_ERROR == pt_elmt->e_elmt_stat)
    {
        return MMPR_INTERNAL_ERROR;
    }
    else if (_MMP_VE_ELMT_STAT_READY != pt_elmt->e_elmt_stat)
    {
        return MMPR_OK;
    }
    
    if(MMP_FILE_SRC_DLNA != pt_elmt->t_file_src ||
       MEDIA_TYPE_UNKNOWN == pt_elmt->t_elmt_fmt.e_media_type)
    {
#ifdef ENABLE_MULTIMEDIA
        i4_ret = c_svctx_media_get_info(
                        pt_this->h_svctx_hdl,
                        pt_elmt->h_elmt_hdl,
                        SVCTX_MM_GET_TYPE_MEDIA_FORMAT,
                        (VOID*)&t_minfo_rec,
                        z_size
                        );
#else
        i4_ret = SVCTXR_NOT_SUPPORT;
#endif
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_media_get_info %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }

        pt_elmt->t_elmt_fmt = t_minfo_rec.t_format;
    }
    
    if(_MMP_VE_ELMT_TYPE_AUDIO == pt_elmt->e_elmt_type)
    {
        if(!FMT_IS_AUDIO_CATEGORY(pt_elmt->t_elmt_fmt))
        {
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;
            return MMPR_NOT_SUPPORT;
        }
    }
    else if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {
        if(!FMT_IS_VIDEO_CATEGORY(pt_elmt->t_elmt_fmt))
        {
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;
            return MMPR_NOT_SUPPORT;
        }
    }
    
    if (_MMP_VE_ELMT_STAT_NOT_SUPPORT == pt_elmt->e_elmt_stat)
    {
        return MMPR_NOT_SUPPORT;
    }
    else if (_MMP_VE_ELMT_STAT_ERROR == pt_elmt->e_elmt_stat)
    {
        return MMPR_INTERNAL_ERROR;
    }
    else if (_MMP_VE_ELMT_STAT_READY != pt_elmt->e_elmt_stat)
    {
        return MMPR_OK;
    }
    
    if(NULL == pt_thumb_rect || WGL_RECT_IS_EMPTY(pt_thumb_rect))
    {
        return MMPR_INV_ARG;
    }
    
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {

#ifdef APP_NET_DLNA_SUPPORT
        //Check if server support seek
        if (MEDIA_TYPE_CONTAINER == pt_elmt->t_elmt_fmt.e_media_type &&
            MEDIA_CONTNR_SUBTYPE_MP4 == pt_elmt->t_elmt_fmt.t_media_subtype.u.e_contnr_subtype) 
        {
            if (FALSE == mmp_util_dlna_is_seek_supported((CHAR*)pt_elmt->ps_file_name)) 
            {
                return video_engine_start2play_cust(pt_play_inst, pt_divx_cert);
            }
        }
#endif

        if(FALSE == pt_elmt->b_check_yet)
        {
            if(NULL == pt_divx_cert)
            {
                MMP_ASSERT(FALSE);
                return MMPR_INV_ARG;
            }

            pt_divx_cert->ui4_title_id = 0;
            i4_ret = video_engine_divx_cert_cust(pt_play_inst, pt_divx_cert);
            if(MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
            else if(MMP_VE_DRM_TYPE_NORMAL != pt_divx_cert->t_drm_type)
            {
                return MMPR_OK;
            }
        }
        else if(MMP_VE_DRM_TYPE_RENTAL == pt_elmt->t_drm_info.t_drm_type)
        {
            return video_engine_start2play_cust((MMP_VE_PLAY_INST_PTR_T)pt_this, pt_divx_cert);
        }
    }
    
    t_thumb_rect = *pt_thumb_rect;
    mmp_drc_convert_rect_coord(e_thumb_coord, &t_thumb_rect);
    
    /*Lock resource from DRC*/
    if (NULL == pt_this->pt_buf_thumb_show)
    {
        mmp_drc_set_single_mode_rect(&t_thumb_rect);

        i4_ret = mmp_drc_switch_mode(MMP_DRC_MODE_SINGLE);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
        
        i4_ret = mmp_drc_lock_buf(MMP_DRC_RESID_SHOW, &pt_this->pt_buf_thumb_show);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
        
        // CR DTV00359464
        i4_ret = mmp_drc_clean_buf(pt_this->pt_buf_thumb_show);
    }
    
    t_thumb_info.h_surf = pt_this->pt_buf_thumb_show->h_surf;
    t_thumb_info.ui4_thumbnail_x = 0;
    t_thumb_info.ui4_thumbnail_y = 0;
    t_thumb_info.ui4_thumbnail_width = (UINT32)WGL_RECT_GET_WIDTH(&t_thumb_rect);
    t_thumb_info.ui4_thumbnail_height =(UINT32) WGL_RECT_GET_HEIGHT(&t_thumb_rect);
    t_thumb_info.pf_nfy = _video_engine_thumb_load_nfy_fct;
    t_thumb_info.pv_tag = (VOID*)pt_this;
    t_thumb_info.ui8_pic_idx = _MMP_VERC_THUMB_PIC_INDEX;
	t_thumb_info.i4_time	 = (INT32)(-1);
    
#ifdef ENABLE_MULTIMEDIA
    i4_ret = c_svctx_media_load_thumbnail(
                    pt_this->h_svctx_hdl,
                    pt_elmt->h_elmt_hdl,
                    &t_thumb_info
                    );
    MMP_DBG_INFO(("{MMP} c_svctx_media_load_thumbnail() returns %d\n", i4_ret));
#else
    i4_ret = SVCTXR_NOT_SUPPORT;
#endif
    if (SVCTXR_ASYNC_NFY != i4_ret && SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_media_load_thumbnail:%d %s:%d\n",i4_ret ,__FUNCTION__, __LINE__));
        mmp_drc_unlock_buf(pt_this->pt_buf_thumb_show);
        pt_this->pt_buf_thumb_show = NULL;
        
        return i4_ret;
    }
    
#ifdef APP_MMP_PVR_GUIDANCE_BLOCK_SETTING
	video_engine_pvr_load_thumb_guidance_block_setting(pt_play_inst);
#endif
    
    pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_THUMB;
    
    return MMPR_OK;
}

INT32 video_engine_thumb_next(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect     /* in  */
                    )
{
    MMP_VE_DIVX_CERT_T t_divx_cert;

    return video_engine_thumb_next_ex(
                    pt_play_inst,
                    e_thumb_coord,
                    pt_thumb_rect,
                    &t_divx_cert
                    );
}

/*----------------------------------------------------------------------------
 * Name: video_engine_thumb_next_ex
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
INT32 video_engine_thumb_next_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_FP_THUMB_COORDS_T           e_thumb_coord,    /* in  */
                    const GL_RECT_T*                pt_thumb_rect,    /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_2nd = _MMP_VE_GET_2ND_ELMT(pt_this);
    INT32 i4_ret;
    
    if(NULL == pt_this || NULL == pt_elmt_1st || NULL == pt_elmt_2nd)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }
    
    if (_MMP_VE_ELMT_STAT_THUMB == pt_elmt_1st->e_elmt_stat)
    {
        i4_ret = video_engine_thumb_full_stop(pt_this);
    }
    else
    {
        i4_ret = video_engine_full_stop_cust(pt_play_inst);
    }
    
    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} _video_engine_sync_stop() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    
    i4_ret = video_engine_elmt_close_cust(pt_play_inst);
    if(MMPR_OK != i4_ret && MMPR_IS_CLOSED != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_close_elm %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    pt_elmt_1st = _MMP_VE_GET_1ST_ELMT((_MMP_VE_PLAY_INST_PTR_T)pt_play_inst);

    /* DLNA will not preload */
    if(MMP_FILE_SRC_DLNA == pt_elmt_2nd->t_file_src)
    {
        i4_ret = video_engine_elmt_open_cust(pt_play_inst);
        if(MMPR_OK != i4_ret && MMPR_IS_OPENED != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}video_engine_elmt_open_cust %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return i4_ret;
        }
        pt_elmt_2nd = _MMP_VE_GET_2ND_ELMT((_MMP_VE_PLAY_INST_PTR_T)pt_play_inst);
    }
    
    pt_this->e_play_stat = MMP_VE_PLAY_STAT_NEXT;
    
    c_memcpy(pt_elmt_1st, pt_elmt_2nd, sizeof(_MMP_VE_ELMT_INFO_T));
    c_memset(pt_elmt_2nd, 0, sizeof(_MMP_VE_ELMT_INFO_T));
    
    i4_ret = video_engine_thumb_load_ex(pt_play_inst, e_thumb_coord, pt_thumb_rect, pt_divx_cert);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_thumb_load_ex %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_thumb_stop
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
INT32 video_engine_thumb_stop(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret;
    
    MMP_ASSERT(NULL != pt_this);
    
    i4_ret = video_engine_thumb_full_stop(pt_this);
    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_thumb_full_stop %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
    
    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_STOP;
    
    return MMPR_IS_STOPPED;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_thumb_show
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
INT32 video_engine_thumb_show(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    HANDLE_T h_plane = NULL_HANDLE;
    INT32 i4_ret = MMPR_OK;
    
    i4_ret = mmp_drc_get_plane(&h_plane);
    IS_MMPR_OK(i4_ret);
    
    /*Lock resource from DRC*/
    if (NULL == pt_this->pt_buf_thumb_show)
    {
        i4_ret = mmp_drc_switch_mode(MMP_DRC_MODE_SINGLE);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
        
        i4_ret = mmp_drc_lock_buf(MMP_DRC_RESID_SHOW, &pt_this->pt_buf_thumb_show);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
    
    i4_ret = c_gl_plane_flip(h_plane, pt_this->pt_buf_thumb_show->h_view, TRUE);
    IS_MMPR_OK(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_thumb_hide
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
INT32 video_engine_thumb_hide(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    HANDLE_T h_plane = NULL_HANDLE;
    INT32 i4_ret;
    
    if(NULL == pt_this->pt_buf_thumb_show)
    {
        return MMPR_INV_ARG;
    }
    
    i4_ret = mmp_drc_get_plane(&h_plane);
    IS_MMPR_OK(i4_ret);
    
    i4_ret = c_gl_plane_flip(h_plane, NULL_HANDLE, TRUE);
    IS_MMPR_OK(i4_ret);
    
    i4_ret = mmp_drc_unlock_buf(pt_this->pt_buf_thumb_show);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
    pt_this->pt_buf_thumb_show = NULL;
    
    return MMPR_OK;
}
#endif


/*----------------------------------------------------------------------------
 * Name: video_engine_get_meta_data
 *
 * Description: Get mata data of the given element.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_meta_data(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    HANDLE_T                        h_elmt_hdl,       /* in  */
                    MMP_VE_INFO_ID_T                e_info_id,        /* in  */
                    UTF16_T *                       pv_buf,           /* in/out */
                    SIZE_T*                         pz_buf_len        /* in/out */
                    )
{
    MINFO_INFO_T t_minfo_rec;
    MM_SVC_DUR_INFO_T t_dur;
    MM_VIDEO_INFO_T t_video_info_rec = {0};
    SIZE_T z_size = sizeof(MINFO_INFO_T);
    MINFO_TYPE_META_DATA_T* pt_meta_date = NULL;
    INT32 i4_ret = MMPR_OK;
    BOOL b_is_resolution_fail = FALSE;

    if(NULL_HANDLE == h_elmt_hdl || NULL == pv_buf || NULL == pz_buf_len)
    {
        return MMPR_INV_ARG;
    }

    c_memset(pv_buf, 0, *pz_buf_len);
    c_memset(&t_minfo_rec, 0, sizeof(MINFO_INFO_T));
    c_memset(&t_dur, 0, sizeof(MM_SVC_DUR_INFO_T));

    pt_meta_date = &t_minfo_rec.u.t_meta_data;

    MMP_DBG_INFO(("{mmp} get meta data info_id:%d\n\r",e_info_id));
	tMediaInfo.ui2AdID = e_info_id;//add by wecong to use this id for get info by once
    switch(e_info_id)
    {
        case MMP_VE_INFO_ID_TITLE:
        case MMP_VE_INFO_ID_NEXT_TITLE:
            pt_meta_date->z_title_len = *pz_buf_len;
            pt_meta_date->pwc_str_title = pv_buf;
            break;

        case MMP_VE_INFO_ID_DIRECTOR:
            pt_meta_date->z_director_len = *pz_buf_len;
            pt_meta_date->pwc_str_director = pv_buf;
            break;

        case MMP_VE_INFO_ID_COPYRIGHT:
            pt_meta_date->z_copyright_len = *pz_buf_len;
            pt_meta_date->pwc_str_copyright = pv_buf;
            break;

        case MMP_VE_INFO_ID_YEAR:
            pt_meta_date->z_year_len = *pz_buf_len;
            pt_meta_date->pwc_str_year = pv_buf;
            break;

        case MMP_VE_INFO_ID_GENRE:
            pt_meta_date->z_genre_len = *pz_buf_len;
            pt_meta_date->pwc_str_genre = pv_buf;
            break;
            
        case MMP_VE_INFO_ID_ARTIST:
        case MMP_VE_INFO_ID_NEXT_ARTIST:
            tMediaInfo.u32ArtistLen = *pz_buf_len;
            break;

        case MMP_VE_INFO_ID_ALBUM:
            tMediaInfo.u32AlbumLen = *pz_buf_len;
            break;

        case MMP_VE_INFO_ID_DATE:
        case MMP_VE_INFO_ID_BITRATE:
        case MMP_VE_INFO_ID_DURATION:
        case MMP_VE_INFO_ID_RESOLUTION:
            break;

        default:
            break;
    }
#ifdef NEVER
#ifdef ENABLE_MULTIMEDIA
    if ('\0' != pt_this->e_language[0])
    {
        i4_ret = c_svctx_media_set_info(
                        pt_this->h_svctx_hdl,
                        h_elmt_hdl,
                        SVCTX_MM_SET_TYPE_LANGUAGE,
                        (VOID*)pt_this->e_language,
                        sizeof(ISO_639_LANG_T));
        MMPR_LOG_ON_FAIL(i4_ret);
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_media_set_info() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }
    }
    
    i4_ret = c_svctx_media_get_info(
                    pt_this->h_svctx_hdl,
                    h_elmt_hdl,
                    SVCTX_MM_GET_TYPE_META_DATA,
                    (VOID*)&t_minfo_rec,
                    z_size
                    );
    MMP_DBG_INFO(("{mmp} get info:%d\n\r",i4_ret));

    // CRDTV00362317 
    if(SVCTXR_OK != i4_ret)
    {   
        switch(e_info_id)
        {
            case MMP_VE_INFO_ID_DURATION:
            {
                t_dur.t_dur_type = MM_SVC_DUR_TYPE_ALL;
                i4_ret = c_svctx_media_get_info(
                                                pt_this->h_svctx_hdl,
                                                h_elmt_hdl,
                                                SVCTX_MM_GET_TYPE_DUR,
                                                (VOID*)&t_dur,
                                                z_size
                                                );
                pt_meta_date->ui8_pb_duration = t_dur.ui8_duration;
            }
                break;
            case MMP_VE_INFO_ID_RESOLUTION:
            {
                SIZE_T t_size = sizeof(MM_VIDEO_INFO_T);
                b_is_resolution_fail = TRUE;
                i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_VIDEO_INFO,
                    (VOID*)&t_video_info_rec,
                    &t_size
                    );
            }
                break;
            default:
                break;
        }
    }
#else
    i4_ret = SVCTXR_NOT_SUPPORT;
#endif
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_media_get_info() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

#else

    //use MI interface to get the media info
    MMP_DBG_INFO(("{media} get media info\n"));
    MMP_DBG_INFO(("[%s %d]e_type == %d\n",__FUNCTION__,__LINE__,tMediaInfo.e_type));

    i4_ret = a_appl_splayer_get_media_info(tMediaInfo.filePath, &tMediaInfo);
    if(APPL_SPLAYER_SUCCESS != i4_ret)
    {
        MMP_DBG_ERROR(("{MMP}[%s:%d]a_appl_splayer_get_media_info failed. returns: %d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }
    else
    {
        if(tMediaInfo.e_type == _MMP_VE_ELMT_TYPE_VIDEO)
        {
            MMP_DBG_INFO(("{MMP}[%s:%d]tMediaInfo.u32MsTime == %d\r\n", __FUNCTION__, __LINE__, tMediaInfo.u32MsTime));
        }
        else if(tMediaInfo.e_type == _MMP_VE_ELMT_TYPE_AUDIO)
        {
            MMP_DBG_INFO(("{MMP}[%s:%d]tMediaInfo.szMetadataAlbum == %s\r\n", __FUNCTION__, __LINE__, tMediaInfo.szMetadataAlbum));
            MMP_DBG_INFO(("{MMP}[%s:%d]tMediaInfo.szMetadataArtist == %s\r\n", __FUNCTION__, __LINE__, tMediaInfo.szMetadataArtist));
        }
        else
        {
            MMP_DBG_ERROR(("[%s %d]invalid media type\n",__FUNCTION__,__LINE__));
        }
    }
#endif

    switch(e_info_id)
    {
        case MMP_VE_INFO_ID_TITLE:
        case MMP_VE_INFO_ID_NEXT_TITLE:
            *pz_buf_len = tMediaInfo.u32TitleLen;
            c_uc_ps_to_w2s(tMediaInfo.szMetadataTitle, pv_buf, tMediaInfo.u32TitleLen + 1);
            break;

        case MMP_VE_INFO_ID_DIRECTOR:
            *pz_buf_len = pt_meta_date->z_director_len;
            break;

        case MMP_VE_INFO_ID_COPYRIGHT:
            *pz_buf_len = pt_meta_date->z_copyright_len;
            break;

        case MMP_VE_INFO_ID_YEAR:
            *pz_buf_len = tMediaInfo.u32YearLen;
            c_uc_ps_to_w2s(tMediaInfo.szYear, pv_buf, tMediaInfo.u32YearLen+1);
            break;

        case MMP_VE_INFO_ID_GENRE:
            *pz_buf_len = tMediaInfo.u32GenreLen;
            c_uc_ps_to_w2s(tMediaInfo.szMetadataGenre, pv_buf, tMediaInfo.u32GenreLen+1);
            break;

        case MMP_VE_INFO_ID_ARTIST:
        case MMP_VE_INFO_ID_NEXT_ARTIST:
            *pz_buf_len = (SIZE_T)tMediaInfo.u32ArtistLen;
            c_uc_ps_to_w2s(tMediaInfo.szMetadataArtist, pv_buf, tMediaInfo.u32ArtistLen+1);
            break;

        case MMP_VE_INFO_ID_ALBUM:
            *pz_buf_len = (SIZE_T)tMediaInfo.u32AlbumLen;
            c_uc_ps_to_w2s(tMediaInfo.szMetadataAlbum, pv_buf, tMediaInfo.u32AlbumLen+1);
            break;

        case MMP_VE_INFO_ID_DATE:
            if(sizeof(MM_TM_T) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_buf_len = sizeof(MM_TM_T);
            c_memcpy(pv_buf, &pt_meta_date->t_date, sizeof(MM_TM_T));
            break;

        case MMP_VE_INFO_ID_DURATION:
            if(sizeof(UINT64) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_buf_len = sizeof(UINT64);
            *(UINT64*)pv_buf = tMediaInfo.u32MsTime;
            break;
            
        case MMP_VE_INFO_ID_BITRATE:
            if(sizeof(UINT32) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_buf_len = sizeof(UINT32);
            *(UINT32*)pv_buf = pt_meta_date->ui4_bitrate;
            break;

        case MMP_VE_INFO_ID_RESOLUTION:
            if(sizeof(GL_SIZE_T) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            *pz_buf_len = sizeof(GL_SIZE_T);
            {
                ((GL_SIZE_T*)pv_buf)->ui4_width = pt_meta_date->t_video_es_info.i4_video_inf_width;
                ((GL_SIZE_T*)pv_buf)->ui4_height = pt_meta_date->t_video_es_info.i4_video_inf_height;           
            }
            break;
        default:
            break;
    }
    
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_file_data
 *
 * Description: Get mata data of the given element.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_file_data(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    FID_T                           t_elmt_fid,       /* in  */
                    MMP_VE_INFO_ID_T                e_info_id,        /* in  */
                    VOID*                           pv_buf,           /* in/out */
                    SIZE_T*                         pz_buf_len        /* in/out */
                    )
{
    FM_FILE_INFO_T t_finfo_rec;
    CHAR* ps_path = NULL;
    CHAR* ps_name = NULL;
    INT32 i4_ret;

#ifdef APP_S_PLATFORM
    MMP_FILE_SRC_TYPE_T e_file_src_type = MMP_FILE_SRC_UNKNOWN;
#endif

    if(MMP_FID_NULL_REC_IDX == t_elmt_fid || NULL == pv_buf || NULL == pz_buf_len)
    {
        return MMPR_INV_ARG;
    }

    i4_ret = mmp_fid_get(t_elmt_fid, &ps_path);
    if(MMPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

#ifdef APP_S_PLATFORM
     /* Get source type according to file name */
    i4_ret = mmp_util_get_file_src_type(ps_path, &e_file_src_type);
    if(MMPR_OK != i4_ret)
    {
        e_file_src_type = MMP_FILE_SRC_MASS_STRG;
    }

    if(e_file_src_type == MMP_FILE_SRC_DLNA)
    {
        i4_ret = c_fm_get_info_by_name(NULL_HANDLE, ps_path, &t_finfo_rec);
    }
    else
    {
        i4_ret = c_fm_mfw_get_info_by_name(NULL_HANDLE, ps_path, &t_finfo_rec);
    }
#else
    i4_ret = c_fm_mfw_get_info_by_name(NULL_HANDLE, ps_path, &t_finfo_rec);
#endif

    if(FMR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }
    MMP_DBG_INFO(("{mmp} get file data info_id:%d\n\r",e_info_id));
    switch(e_info_id)
    {
        case MMP_VE_INFO_ID_NAME:
            ps_name = c_strrchr(ps_path, '/');
            if (NULL == ps_name)
            {
                ps_name = ps_path;
            }
            else
            {
                ps_name += 1;
            }
            
            if ((c_strlen(ps_name) + 1) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            c_uc_ps_to_w2s(ps_name, (UTF16_T*)pv_buf, *pz_buf_len);
            *pz_buf_len = c_strlen(ps_name);
            break;
            
        case MMP_VE_INFO_ID_PROTECT:
            if(sizeof(BOOL) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            *(BOOL*)pv_buf = (FM_MODE_USR_WRITE & t_finfo_rec.ui4_mode) ? FALSE : TRUE;
            MMP_DBG_INFO(("{MMP} IIII >> Write Mask = %d %s:%d\n", 
                      (FM_MODE_USR_WRITE & t_finfo_rec.ui4_mode),
                       __FUNCTION__, __LINE__));
            *pz_buf_len = sizeof(BOOL);
            break;

        case MMP_VE_INFO_ID_CREATE_TIME:
            if(sizeof(DTG_T) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            i4_ret = c_dt_utc_sec_to_loc_dtg(
                                t_finfo_rec.ui8_create_time,
                                (DTG_T*)pv_buf
                                );
            if(DTR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }
            break;

        case MMP_VE_INFO_ID_ACCESS_TIME:
            if(sizeof(DTG_T) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            i4_ret = c_dt_utc_sec_to_loc_dtg(
                                t_finfo_rec.ui8_access_time,
                                (DTG_T*)pv_buf
                                );
            if(DTR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }
            break;

        case MMP_VE_INFO_ID_MODIFY_TIME:
            if(sizeof(DTG_T) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            i4_ret = c_dt_utc_sec_to_loc_dtg(
                                t_finfo_rec.ui8_modify_time,
                                (DTG_T*)pv_buf
                                );
            if(DTR_OK != i4_ret)
            {
                return MMPR_FAIL;
            }
            break;
            
        case MMP_VE_INFO_ID_SIZE:
            if(sizeof(UINT64) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }
            *(UINT64*)pv_buf = t_finfo_rec.ui8_size;
            *pz_buf_len = sizeof(UINT64);
            break;
            
        default:
            return MMPR_NOT_SUPPORT;
    }

    return MMPR_OK;
}
                  

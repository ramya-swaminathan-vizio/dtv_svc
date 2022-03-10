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
 * $RCSfile: video_engine.c,v $
 * $Revision$
 * $Date$
 * $Author$
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
#define VIDEO_CSVCTX_NAME             ("main_svctx")

#ifndef MM_INTL_SBTL_EXTENTION
#define MM_INTL_SBTL_EXTENTION        ":internal"
#endif

#define _MMP_VE_EXT_SBTL_TYPE_LIST    _MMP_VERC_EXT_SBTL_TYPE_LIST_PREFIX     \
                                       MM_INTL_SBTL_EXTENTION                 \
                                      _MMP_VERC_EXT_SBTL_TYPE_LIST_SUFFIX

#ifndef _MMP_VERC_CHECK_ZOOM_FROM_SML
#define _MMP_VERC_CHECK_ZOOM_FROM_SML()           (TRUE)
#endif

#ifndef _MMP_VERC_HAS_DIVX_SUPPORT
#define _MMP_VERC_HAS_DIVX_SUPPORT()              (TRUE)
#endif

/*-----------------------------------------------------------------------------
 * macros, typedefs, enums
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * extern variables declaration
 *---------------------------------------------------------------------------*/
extern HANDLE_T h_g_acfg_scc_main_disp;
extern HANDLE_T h_g_acfg_scc_main_vid;

/*-----------------------------------------------------------------------------
 * global variables definition
 *---------------------------------------------------------------------------*/
static _MMP_VE_PLAY_INST_PTR_T at_g_play_inst_list[_MMP_VERC_PLAY_INST_NUM] = {0};

#ifndef _MMP_VERC_REQ_WND_SIZE
#define _MMP_VERC_REQ_WND_SIZE ((UINT8)2)
#endif
static _MMP_VE_REQ_WND_T at_g_req_wnd[_MMP_VERC_REQ_WND_SIZE] = {{{0},0,0}, {{0},0,0}};

#ifdef APP_LAST_MEMORY_SUPPORT
UINT16 ui2_subtitle_play_idx = 0;
UINT16 ui2_audio_play_idx = 0;
UINT16 ui2_valid_sbtl_num = 0;
UINT16 ui2_valid_aud_num = 0;
#endif

#ifdef APP_S_PLATFORM
char ag_g_not_preload_file[] = "pvr"; /* fix DTV00945967 pvr file not preload */
#endif

static P_APPL_SPLAYER_T             gp_v_splayer = NULL;

static INT32 _video_engine_trick2play(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    );

/*-----------------------------------------------------------------------------
 * local functions definition
 *---------------------------------------------------------------------------*/
static INT32 _video_engine_get_trick(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    SPLAYER_TrickSpeed_e*                pt_spd_type       /* out */
                    );

static INT32 _video_engine_set_trick(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    SPLAYER_TrickSpeed_e                 e_spd_type        /* in  */
                    );


static VOID _mmp_vp_mmp_ctx_fct(VOID* pv_nfy_code, VOID* pv_tag, VOID* pv_data,VOID * pv_param4)
{
    DBG_LOG_PRINT(("[Jundi][%s %d]\n",__FUNCTION__,__LINE__));
    APPL_SPLAYER_PLAY_EVENT e_nfy_code = (APPL_SPLAYER_PLAY_EVENT) pv_nfy_code;   //sac modify   TF516PHIEUMTK00-2455
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pv_param4;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    MMP_VE_NFY_CODE_T e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_STOP_END;
   
    switch (e_nfy_code)
    {
        case SPLAYER_MM_EVENT_EXIT_OK:
            DBG_LOG_PRINT(("[Jundi][%s %d]SPLAYER_MM_EVENT_EXIT_OK\n",__FUNCTION__,__LINE__));
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_STOP_EOS;
            break;
        case SPLAYER_MM_EVENT_PLAYING_OK:
            //e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_DURATION_UPDATE;
            DBG_LOG_PRINT(("[Jundi][%s %d]SPLAYER_MM_EVENT_PLAYING_OK\n",__FUNCTION__,__LINE__));
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL;
            break;
        case SPLAYER_MM_EVENT_PLAYING_INIT_OK:
            DBG_LOG_PRINT(("[Jundi][%s %d]SPLAYER_MM_EVENT_PLAYING_INIT_OK\n",__FUNCTION__,__LINE__));
            DBG_LOG_PRINT(("** SPLAYER_MM_EVENT_PLAYING_INIT_OK *** %s,%d\r\n",__FUNCTION__,__LINE__));
            _video_engine_trick2play(pt_this);
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAYING_INIT_OK;
#ifdef NEVER
            appl_splayer_start_play((APPL_SPLAYER_PLAY_EVENT)pv_nfy_code, pv_tag, (UINT32) pv_data);
#endif /* NEVER */

            break;

        case SPLAYER_MM_EVENT_AUDIO_UNSUPPORTED:
            //appl_splayer_close(&gp_v_splayer);
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_NOT_SUPPORT;
            break;

        case SPLAYER_MM_EVENT_AUDIO_ONLY:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_SVC;
            break;
        case SPLAYER_MM_EVENT_VIDEO_UNSUPPORTED:
            //appl_splayer_close(&gp_v_splayer);
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT;
            break;

        default:
            break;
    }

    if(pt_this->pf_play_nfy_fct!=NULL)
    {
        //callback:_audio_player_engine_nfy_fct  or _mmp_vp_engine_nfy_fct
        pt_this->pf_play_nfy_fct(e_ve_nfy_code, NULL);
    }

}

static VOID _mmp_vp_splayer_eventCallback(APPL_SPLAYER_PLAY_EVENT e_nfy_code, VOID *pvTag, UINT32 u4Data,VOID *pvPara)
{
    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_vp_mmp_ctx_fct,
                    (VOID*)(UINT32)e_nfy_code,
                    (VOID*)pvTag,
                    (VOID*)(UINT32)u4Data,
                    (VOID*)pvPara);
}
static INT32 _mmp_vp_video_open(const CHAR* p_path,_MMP_VE_PLAY_INST_PTR_T pt_this)
{
    INT32 i4_ret;
    MMP_FP_PRESENT_MODE_T t_present_mode;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    if(gp_v_splayer != NULL)
        appl_splayer_close(&gp_v_splayer);
    
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
        {
            DBG_LOG_PRINT(("[%s %d]the media type is video\n",__FUNCTION__,__LINE__));
            DBG_LOG_PRINT(("[%s %d]pt_this->t_present_mode == %d\n",__FUNCTION__,__LINE__,pt_this->t_present_mode));
            
            //get the present_mode
            i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);    
            if (MMPR_OK != i4_ret)    
            {        
                t_present_mode = MMP_FP_PRESENT_MODE_FULL;
            }
            if(MMP_FP_PRESENT_MODE_FULL == t_present_mode)
            {
                DBG_LOG_PRINT(("[%s %d]the present mode is MMP_FP_PRESENT_MODE_FULL\n",__FUNCTION__,__LINE__));
                pt_this->t_present_mode = MMP_FP_PRESENT_MODE_FULL;
            }
            else if(MMP_FP_PRESENT_MODE_PREVIEW == t_present_mode)
            {
                DBG_LOG_PRINT(("[%s %d]the present mode is MMP_FP_PRESENT_MODE_PREVIEW\n",__FUNCTION__,__LINE__));
                pt_this->t_present_mode = MMP_FP_PRESENT_MODE_PREVIEW;
            }
        } 
        
        i4_ret = appl_splayer_open_async(p_path,_mmp_vp_splayer_eventCallback,NULL, 0/*APPL_SPLAYER_PLAY_MODE_LAST_FREEZE*/, &gp_v_splayer,pt_this);
        DBG_LOG_PRINT(("[video]appl_splayer_open_async() %s,i4_ret:%d\r\n",__FUNCTION__,i4_ret));
     
    return i4_ret;
}

static INT32 _mmp_vp_video_play(const CHAR* p_path,_MMP_VE_PLAY_INST_PTR_T pt_this)
{
    DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
    INT32 i4_ret = 0;
    MMP_FP_PRESENT_MODE_T t_present_mode;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    #if 0
    if(gp_v_splayer != NULL)
        appl_splayer_close(&gp_v_splayer);
    #endif
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
        {
            DBG_LOG_PRINT(("[%s %d]the media type is video\n",__FUNCTION__,__LINE__));
            DBG_LOG_PRINT(("[%s %d]pt_this->t_present_mode == %d\n",__FUNCTION__,__LINE__,pt_this->t_present_mode));
            
            //get the present_mode
            i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);    
            if (MMPR_OK != i4_ret)    
            {        
                t_present_mode = MMP_FP_PRESENT_MODE_FULL;
            }
            if(MMP_FP_PRESENT_MODE_FULL == t_present_mode)
            {
                DBG_LOG_PRINT(("[%s %d]the present mode is MMP_FP_PRESENT_MODE_FULL\n",__FUNCTION__,__LINE__));
                pt_this->t_present_mode = MMP_FP_PRESENT_MODE_FULL;
            }
            else if(MMP_FP_PRESENT_MODE_PREVIEW == t_present_mode)
            {
                DBG_LOG_PRINT(("[%s %d]the present mode is MMP_FP_PRESENT_MODE_PREVIEW\n",__FUNCTION__,__LINE__));
                pt_this->t_present_mode = MMP_FP_PRESENT_MODE_PREVIEW;
            }
        }
	    if (gp_v_splayer != NULL)
        {
            i4_ret = appl_splayer_play_async(p_path,_mmp_vp_splayer_eventCallback,NULL, 0/*APPL_SPLAYER_PLAY_MODE_LAST_FREEZE*/, &gp_v_splayer,pt_this);
	        DBG_LOG_PRINT(("[video]appl_splayer_play_async() %s,i4_ret:%d\r\n",__FUNCTION__,i4_ret));
        }
    return i4_ret;
}

static INT32 _mmp_vp_video_stop(VOID)
{
    if(gp_v_splayer != NULL)
    {
        appl_splayer_close(&gp_v_splayer);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_set_repeat
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
INT32 _video_engine_set_repeat(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    MM_SVC_REPEAT_TYPE_T            e_rpt_type        /* in  */
                    )
{
    MM_SVC_REPEAT_INFO_T t_repeat = { e_rpt_type };
    INT32 i4_ret = 0;

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SET_TYPE_REPEAT,
                    (VOID*)&t_repeat,
                    sizeof(MM_SVC_REPEAT_INFO_T)
                    );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_set fail:%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_do_nfy_fct
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
static VOID _video_engine_do_nfy_fct(
                    VOID*                           pv_inst_id,       /* in  */
                    VOID*                           pv_elmt_hdl,      /* in  */
                    VOID*                           pv_stm_type,      /* in  */
                    VOID*                           pv_nfy_code       /* in  */
                    )
{
    _MMP_VE_INST_ID_T t_inst_id = (_MMP_VE_INST_ID_T)(UINT32)pv_inst_id;
    HANDLE_T h_elmt_hdl = (HANDLE_T)(UINT32)pv_elmt_hdl;
    SVCTX_NTFY_CODE_T e_mw_nfy_code = (SVCTX_NTFY_CODE_T)(UINT32)pv_nfy_code;

    if((_MMP_VERC_PLAY_INST_NUM  <= t_inst_id) ||
       (NULL == at_g_play_inst_list[t_inst_id]))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    _MMP_VE_PLAY_INST_PTR_T pt_this = at_g_play_inst_list[t_inst_id];
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_2nd = _MMP_VE_GET_2ND_ELMT(pt_this);
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_cur = NULL;
    _MMP_VE_ELMT_ID_T i = _MMP_VE_ELMT_ID_1ST;
    _MMP_VE_FILE_ID_T t_file_id;

    MMP_VE_NFY_CODE_T e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_STOP_END;
    BOOL                     b_media_is_preload;
	INT32                    i4_ret = MMPR_OK;

    if ((NULL == pt_this) || (NULL == pt_elmt_1st) || (NULL == pt_elmt_2nd))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    for(i = _MMP_VE_ELMT_ID_1ST; i < _MMP_VE_ELMT_ID_NUM; i++)
    {
        pt_elmt_cur = &pt_this->at_elmt_info[i];
        if (h_elmt_hdl == pt_elmt_cur->h_elmt_hdl)
        {
            t_file_id = pt_elmt_cur->t_file_id;
            break;
        }
    }

    if (_MMP_VE_ELMT_ID_NUM <= i)
    {
        return;
    }

    if ( SVCTX_NTFY_CODE_MEDIA_AS_BIT_RATE_CHG != e_mw_nfy_code )
    {
        MMP_DBG_INFO(("{MMP}<<PLAY>> [%u <-> %u] %s:%d\n", t_file_id, pt_elmt_1st->t_file_id,__FUNCTION__, __LINE__));
        /*Output SVCTX NFY Info*/
        video_engine_svctx_nfy_output(e_mw_nfy_code);
    }

    /* treat some notify as invalid after STOP operation */
    if(( MMP_VE_PLAY_STAT_STOP == pt_this->e_play_stat) &&
       (_MMP_VE_ELMT_STAT_STOP == pt_elmt_1st->e_elmt_stat))
    {
        switch(e_mw_nfy_code)
        {
            case SVCTX_NTFY_CODE_MEDIA_ERROR:
            case SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSING:
            case SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSED:
            case SVCTX_NTFY_CODE_MEDIA_SEEK_READY:
            case SVCTX_NTFY_CODE_MEDIA_SEEK_ERROR:
            case SVCTX_NTFY_CODE_IN_STOPPING:
            case SVCTX_NTFY_CODE_STOPPED:
            case SVCTX_NTFY_CODE_NORMAL:

            case SVCTX_NTFY_CODE_MEDIA_HD_NOT_SUPPORT:
            case SVCTX_NTFY_CODE_MEDIA_DRM_NOT_SUPPORT:
            case SVCTX_NTFY_CODE_MEDIA_RESOLUTION_NOT_SUPPORT:
            case SVCTX_NTFY_CODE_MEDIA_FRAMERATE_NOT_SUPPORT:
            case SVCTX_NTFY_CODE_MEDIA_NO_CONTENT:
            case SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC:
            case SVCTX_NTFY_CODE_MEDIA_VS_CODEC_NOT_SUPPORT:
            case SVCTX_NTFY_CODE_MEDIA_AS_CODEC_NOT_SUPPORT:
            case SVCTX_NTFY_CODE_VIDEO_ONLY_STRM:
            case SVCTX_NTFY_CODE_AUDIO_ONLY_STRM:
                //for special file, we should change it to play stat and do nfy
                break;

            default:
                return;
        }
    }

    b_media_is_preload = (t_file_id == pt_elmt_2nd->t_file_id);
    pt_elmt_cur = b_media_is_preload ? pt_elmt_2nd : pt_elmt_1st;

    switch(e_mw_nfy_code)
    {
        case SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSING:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_OPEN_BGN;
            break;
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
        case SVCTX_NTFY_CODE_MEDIA_RANGE_AB_DONE:
            video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_STOP, 0);
            break;
#endif

#ifdef APP_MMP_PVR_SUPPORT
        case SVCTX_NTFY_CODE_STREAM_OPENED:
            e_ve_nfy_code = MMP_VE_NFY_CODE_STREAM_OPENED;
            break;
#endif
        case SVCTX_NTFY_CODE_MEDIA_FILE_NOT_SUPPORT:
        case SVCTX_NTFY_CODE_MEDIA_ERROR:
        case SVCTX_NTFY_CODE_MEDIA_FILE_OPER_ERROR:
        {
            pt_elmt_cur->b_is_media_error = TRUE;
            if((_MMP_VE_ELMT_STAT_INIT == pt_elmt_cur->e_elmt_stat) ||
               (_MMP_VE_ELMT_STAT_WAIT == pt_elmt_cur->e_elmt_stat))
            {
                if (SVCTX_NTFY_CODE_MEDIA_ERROR == e_mw_nfy_code)
                {
                    pt_elmt_cur->e_elmt_stat = _MMP_VE_ELMT_STAT_ERROR;
                }
                else
                {
                    pt_elmt_cur->e_elmt_stat = _MMP_VE_ELMT_STAT_NOT_SUPPORT;
                }
                if (TRUE == b_media_is_preload)
                {
                    e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_NEXT_OPEN_ERR;
                }
                else
                {
                    e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_OPEN_ERR;
                }
            }
            else if(_MMP_VE_ELMT_STAT_PLAY      == pt_elmt_cur->e_elmt_stat &&
                    SVCTX_NTFY_CODE_MEDIA_ERROR == e_mw_nfy_code)
            {
                pt_this->pf_play_nfy_fct(
                                MMP_VE_NFY_CODE_MEDIA_PLAY_ERR,
                                NULL
                                );
                /* send true means this notify is from SVCTX_NTFY_CODE_MEDIA_ERROR */
                pt_this->pf_play_nfy_fct(
                                MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT,
                                (VOID*)TRUE
                                );

                pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

                pt_this->pf_play_nfy_fct(
                                MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                               (VOID*)FALSE
                                );
            }
        }
        break;

        case SVCTX_NTFY_CODE_MEDIA_PRE_PROCESSED:
        {
            if ('\0' != pt_this->e_language[0])
            {
                i4_ret = c_svctx_media_set_info(
                                pt_this->h_svctx_hdl,
                                h_elmt_hdl,
                                SVCTX_MM_SET_TYPE_LANGUAGE,
                                (VOID*)pt_this->e_language,
                                sizeof(ISO_639_LANG_T));

                if(SVCTXR_OK != i4_ret)
                {
                    MMP_DBG_INFO(("{MMP} c_svctx_media_set_info() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                }
            }
#ifdef APP_MMP_SHOW_BROKEN_THUMB
            if(MMP_FILE_SRC_DLNA != pt_elmt_cur->t_file_src ||
               MEDIA_TYPE_UNKNOWN == pt_elmt_cur->t_elmt_fmt.e_media_type)
            {
                MINFO_INFO_T t_minfo_rec;
                SIZE_T z_size = sizeof(MINFO_INFO_T);
#ifdef ENABLE_MULTIMEDIA
                i4_ret = c_svctx_media_get_info(
                                pt_this->h_svctx_hdl,
                                pt_elmt_cur->h_elmt_hdl,
                                SVCTX_MM_GET_TYPE_MEDIA_FORMAT,
                                (VOID*)&t_minfo_rec,
                                z_size
                                );
#else
                i4_ret = SVCTXR_NOT_SUPPORT;
#endif
                if(SVCTXR_OK != i4_ret)
                {
                    MMP_DBG_INFO(("{MMP} c_svctx_media_get_info() returns  %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                    return;
                }

                pt_elmt_cur->t_elmt_fmt = t_minfo_rec.t_format;
            }
#endif
            if((_MMP_VE_ELMT_STAT_INIT == pt_elmt_cur->e_elmt_stat) ||
               (_MMP_VE_ELMT_STAT_WAIT == pt_elmt_cur->e_elmt_stat))
            {
                pt_elmt_cur->e_elmt_stat = _MMP_VE_ELMT_STAT_READY;
            }

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
            if (TRUE == pt_elmt_cur->b_dont_play)
            {
                pt_elmt_cur->b_dont_play = FALSE;
                return; /* STOP before c_svctx_select_svc() */
            }
#endif
            if (TRUE == b_media_is_preload)
            {
                e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_NEXT_OPEN_END;
            }
            else
            {
                 e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_OPEN_END;
            }
        }
        break;

        case SVCTX_NTFY_CODE_VIDEO_NUM_READY:
        {
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_PROGRAM_INFO_READY,
                            NULL
                            );
            /*
            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                            NULL
                            );
                            */
        }
        return;

        case SVCTX_NTFY_CODE_MEDIA_HD_NOT_SUPPORT:
        {
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_MEDIA_HD_NOT_SUPPORT;
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_HD_NOT_SUPPORT,
                            NULL
                            );

            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                           (VOID*)FALSE
                            );
        }
        return;

        case SVCTX_NTFY_CODE_MEDIA_DRM_NOT_SUPPORT:
        {
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_MEDIA_DRM_NOT_SUPPORT;
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_DRM_NOT_SUPPORT,
                            NULL
                            );

            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                           (VOID*)FALSE
                            );
        }
        return;

        case SVCTX_NTFY_CODE_MEDIA_RESOLUTION_NOT_SUPPORT:
        {
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_MEDIA_RESOLUTION_NOT_SUPPORT;
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_RESOLUTION_NOT_SUPPORT,
                            NULL
                            );

            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                           (VOID*)FALSE
                            );
        }
        return;

        case SVCTX_NTFY_CODE_MEDIA_FRAMERATE_NOT_SUPPORT:
        {
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_MEDIA_FRAMERATE_NOT_SUPPORT;
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_FRAMERATE_NOT_SUPPORT,
                            NULL
                            );

            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                            (VOID*)FALSE
                            );
        }
        return;

#if 1   /* This notify is only used for PVR playing */
        case SVCTX_NTFY_CODE_MEDIA_NO_CONTENT:
        {
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_HAS_NO_CONTENT,
                            NULL
                            );

            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                            NULL
                            );
        }
        return;

        case SVCTX_NTFY_CODE_MEDIA_CAM_RATING_LOWER_EVENT_RATING:
        {
            MMP_DBG_INFO(("%s-%d-SVCTX_NTFY_CODE_MEDIA_CAM_RATING_LOWER_EVENT_RATING msg\n",__FUNCTION__,__LINE__));
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_CAM_RATING_LOWER_EVENT_RATING,
                            NULL
                            );
        }
        return;
#endif

        case SVCTX_NTFY_CODE_NO_AUDIO_VIDEO_SVC:
        {
            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NO_AUDIO_VIDEO_SVC,
                            NULL
                            );

            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                            (VOID*)FALSE
                            );
        }
        return;

        case SVCTX_NTFY_CODE_AUDIO_ONLY_SVC:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_SVC;
            pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_AUDIO_ONLY;
            break;

        case SVCTX_NTFY_CODE_VIDEO_ONLY_SVC:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_ONLY_SVC;
            break;

        case SVCTX_NTFY_CODE_AUDIO_ONLY_STRM:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_STRM;
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_AUDIO_ONLY;
            break;

        case SVCTX_NTFY_CODE_VIDEO_ONLY_STRM:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_ONLY_STRM;
            break;

        case SVCTX_NTFY_CODE_AUDIO_VIDEO_SVC:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_VIDEO_SVC;
            break;

        case SVCTX_NTFY_CODE_MEDIA_AS_CODEC_NOT_SUPPORT:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_NOT_SUPPORT;
            break;

        case SVCTX_NTFY_CODE_MEDIA_VS_CODEC_NOT_SUPPORT:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT;
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_VIDEO_NOT_SUPPORT;
            break;

        case SVCTX_NTFY_CODE_AUDIO_FMT_UPDATE:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE;
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_AUDIO_FMT_UPDATE;
            break;
        case SVCTX_NTFY_CODE_SCDB_ADD:
        case SVCTX_NTFY_CODE_SCDB_DEL:
        case SVCTX_NTFY_CODE_SCDB_MODIFY:
			i4_ret = video_engine_handle_scdb_update(pt_this, ST_UNKNOWN);
#ifdef APP_MMP_SCDB_SEPARATE
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_SCDB_CHANGE;
#else
			//e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE;
#endif
            break;

        case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
			//add video show for that TS will do trick oper when start
            //mw will abort
            pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_VIDEO_FMT_UPDATE;
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
            //when video update we restart ttx
            i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_START, 0);
#endif
			if (b_media_is_preload == FALSE &&
				pt_elmt_1st->t_spd_attr.e_id == MMP_FP_SHOW_ATTR_ID_SPEED)
			{
				MM_SPEED_TYPE_T e_spd = (MM_SPEED_TYPE_T)(UINT32)pt_elmt_1st->t_spd_attr.pv_param;
				i4_ret = video_engine_set_speed((MMP_VE_PLAY_INST_PTR_T)pt_this, e_spd);
				MMP_DBG_INFO(("{MMP} reset setting speed:%d ret :%d\n", e_spd, i4_ret));
			}
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_FMT_UPDATE;
            break;

#ifdef APP_MMP_PVR_REMOVE_THUMB_CUST_RULE
#ifdef _MMP_VERC_PLAY_COVER_SUPPORT
            case SVCTX_NTFY_CODE_MEDIA_RATING_BLOCKED:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_NEED_PSW;
            break;
#endif
#else
			case SVCTX_NTFY_CODE_MEDIA_RATING_BLOCKED:
            case SVCTX_NTFY_CODE_REC_CHANNEL_LOCKED:
			case SVCTX_NTFY_CODE_REC_INPUT_LOCKED:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_NEED_PSW;
			break;
#endif

#ifdef APP_MMP_PVR_SUPPORT
#if ((!defined(_MMP_VERC_PLAY_COVER_SUPPORT))&&(defined(APP_MMP_PVR_REMOVE_THUMB_CUST_RULE)))
        case SVCTX_NTFY_CODE_MEDIA_RATING_BLOCKED:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PVR_PLAYING_PIN_VALID_PARENT_RATING;
            MMP_DBG_INFO(("vide_engine.c  SVCTX_NTFY_CODE_MEDIA_RATING_BLOCKED\n"));
            break;
#endif

		case SVCTX_NTFY_CODE_MEDIA_PVR_PLAYING_PARENT_RATING:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PVR_PLAYING_PIN_VALID_PARENT_RATING;
			break;

		case SVCTX_NTFY_CODE_MEDIA_GUIDANCE_BLOCKED_AFT_THUMB:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PVR_GUIDANCE_BLOCKED_AFTER_THUMB;
			break;

#ifdef SUPPORT_CIPLUS_RECORD
        case SVCTX_NTFY_CODE_CAM_CARD_REMOVE:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_CAM_CARD_REMOVE;
            break;
#endif

        case SVCTX_NTFY_CODE_SERVICE_PIN_BLOCKED:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_SERVICE_PIN_BLOCKED;
            break;

#if ((!defined(_MMP_VERC_PLAY_COVER_SUPPORT))&&(defined(APP_MMP_PVR_REMOVE_THUMB_CUST_RULE)))
        case SVCTX_NTFY_CODE_REC_CHANNEL_LOCKED:
        {
            MMP_DBG_INFO(("vide_engine.c  SVCTX_NTFY_CODE_REC_CHANNEL_LOCKED\n"));
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PVR_PLAYING_PIN_VALID_PROG_BLOCKED;;
            break;
        }
#endif
#endif

        case SVCTX_NTFY_CODE_NORMAL:
        {
#ifdef APP_LAST_MEMORY_SUPPORT
            INT32                   i4_ret = MMPR_OK;
            MMP_FP_PRESENT_MODE_T   t_present_mode;

            i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
            if (MMPR_OK != i4_ret)
            {
                t_present_mode = MMP_FP_PRESENT_MODE_FULL;
            }

            if ((_MMP_VE_ELMT_TYPE_VIDEO  == pt_elmt_1st->e_elmt_type) &&
                (MMP_FP_PRESENT_MODE_FULL == t_present_mode)           &&
                (MMP_FILE_SRC_MASS_STRG   == pt_elmt_1st->t_file_src))
            {
                c_memset((VOID*)&pt_elmt_1st->t_stop_info.t_pos_info, 0, sizeof(MM_SVC_POS_INFO_T));
                pt_elmt_1st->t_stop_info.ui2_aud_idx = 0;
                pt_elmt_1st->t_stop_info.ui2_sub_idx = 0;
                pt_elmt_1st->t_stop_info.ui4_title_idx = 0;
                pt_elmt_1st->t_stop_info.ui4_playlist_idx = 0;
                pt_elmt_1st->t_stop_info.ui4_chap_idx = 0;

                i4_ret = mmp_ve_stop_info_update(pt_this, &pt_elmt_1st->t_stop_info);
                if (MMPR_OK != i4_ret)
                {
                    MMP_DBG_INFO(("{MMP} mmp_ve_stop_info_update: %s: %d %d\n", __FUNCTION__, __LINE__,i4_ret));
                }

                i4_ret = mmp_ve_stop_info_set(pt_this, pt_this->at_stop_info);
                if (MMPR_OK != i4_ret)
                {
                    MMP_DBG_INFO(("{MMP} mmp_ve_stop_info_set: %s: %d %d\n", __FUNCTION__, __LINE__,i4_ret));
                    MMP_ASSERT(FALSE);
                }
            }
#endif

            if(MMP_FP_SHOW_ATTR_ID_REPEAT == pt_elmt_1st->t_rpt_attr.e_id)
            {
                if(MMP_REPEAT_MODE_ONE == (UINT32)pt_elmt_1st->t_rpt_attr.pv_param)
                {
                    _video_engine_set_repeat(pt_this, MM_SVC_REPEAT_ALL);
                }
                else
                {
                    _video_engine_set_repeat(pt_this, MM_SVC_REPEAT_OFF);
                }
            }

            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

            pt_this->pf_play_nfy_fct(
                            MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL,
                            (VOID*)TRUE
                            );

            return;
        }

        case SVCTX_NTFY_CODE_MEDIA_REPLAY:
#ifdef APP_LAST_MEMORY_SUPPORT
			ui2_valid_aud_num = 0;
			video_engine_chk_sbtl_last_mem(ST_UNKNOWN, FALSE, TRUE);
#endif
			pt_elmt_1st->e_sbtl_stat  = _MMP_VE_SBTL_STAT_OFF;
			pt_elmt_1st->ui4_notify_flag  = 0;
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_REPLAY;
			break;


        case SVCTX_NTFY_CODE_CHAPTER_CHANGE:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_CHAPTER_CHANGE;
            break;

        case SVCTX_NTFY_CODE_MEDIA_DURATION_UPDATE:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_DURATION_UPDATE;
            break;

        case SVCTX_NTFY_CODE_MEDIA_SUBTITLE_FMT_UPDATE:
        {
            pt_elmt_1st->e_sbtl_stat = _MMP_VE_SBTL_STAT_ON;
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_SUBTITLE_UPDATE;
            #ifdef APP_TWN_SUPPORT
            MM_SVC_SBTL_FONT_ENC_T     t_font_enc ;
            c_memset(&t_font_enc, 0 , sizeof(MM_SVC_SBTL_FONT_ENC_T));
            t_font_enc.e_enc_type = MM_SBTL_FONT_ENC_BIG5;
            mmp_ve_sbtl_set_encode(pt_this,&t_font_enc);

            MM_SVC_SBTL_DISP_ATTR_T     t_nrml_attr ;
            MM_SVC_SBTL_DISP_ATTR_T*    pt_nrml_attr = &t_nrml_attr;
            WGL_FONT_INFO_T*            pt_font_info = &pt_nrml_attr->t_font_info;

            c_memset(pt_nrml_attr, 0, sizeof(MMP_VE_SBTL_ATTR_T));

            pt_nrml_attr->t_attr_field = MM_SBTL_ATTR_FNT_INFO;

            c_strcpy(pt_font_info->a_c_font_name, SN_FONT_DEFAULT);

            pt_font_info->e_font_cmap  = FE_CMAP_ENC_UNICODE;
            pt_font_info->e_font_size  = FE_FNT_SIZE_LARGE;
            pt_font_info->e_font_style = FE_FNT_STYLE_REGULAR;
            pt_font_info->i2_width     = (INT16)0;

            mmp_ve_sbtl_set_font(pt_this,pt_nrml_attr);
            #endif
        }
        break;

        case SVCTX_NTFY_CODE_MEDIA_AB_REPEAT_DONE:
        {
            SPLAYER_TrickSpeed_e e_speed;
            INT32 i4_ret;

            i4_ret = _video_engine_get_trick (pt_this, &e_speed);
            if (MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} _video_engine_get_trick: %s: %d %d\n", __FUNCTION__, __LINE__,i4_ret));
                return;
            }

            switch (e_speed)
            {
                case SPLAYER_MM_TRICK_SPEED_1X:
                    pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_PLAY;
                    break;

                default:
                    return;
            }

            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AB_REPEAT_DONE;
        }
        break;

        case SVCTX_NTFY_CODE_MEDIA_SEEK_READY:
        {
            switch(pt_this->e_play_stat)
            {
                case MMP_VE_PLAY_STAT_PLAY:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_PLAY;
                    break;

                case MMP_VE_PLAY_STAT_PAUSE:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_PAUSE;
                    break;

                case MMP_VE_PLAY_STAT_BLANK:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_BLANK;
                    break;

                case MMP_VE_PLAY_STAT_FAST_FWD:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_FFWD;
                    break;

                case MMP_VE_PLAY_STAT_FAST_RWD:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_FRWD;
                    break;

                case MMP_VE_PLAY_STAT_SLOW_FWD:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_SFWD;
                    break;

                case MMP_VE_PLAY_STAT_SLOW_RWD:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_FRWD;
                    break;

                default:
                    pt_elmt_1st->e_elmt_oper = _MMP_VE_ELMT_OPER_PLAY;
                    break;
            }
#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
            //when video update we restart ttx
            i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_START, 0);
#endif

            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_SEEK_READY;
        }
        break;

        case SVCTX_NTFY_CODE_MEDIA_SEEK_ERROR:
        {
             e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_SEEK_ERROR;
        }
        break;

        case SVCTX_NTFY_CODE_NO_RESOURCES:
        {
             e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_NO_RESOURCES;
        }
        break;

        case SVCTX_NTFY_CODE_INTERNAL_ERROR:
        {
             e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_FILE_ERR;
        }
        break;

        case SVCTX_NTFY_CODE_IN_STOPPING:
        {
            pt_elmt_1st->e_sbtl_stat = _MMP_VE_SBTL_STAT_OFF;
            //for over is next status do not set to prev stat
            if (pt_elmt_1st->e_elmt_stat != _MMP_VE_ELMT_STAT_OVER)
            {
                pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_STOP;
            }
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_STOP_BGN;
        }
        break;

        case SVCTX_NTFY_CODE_MEDIA_EOS:
            pt_elmt_1st->e_elmt_stat = _MMP_VE_ELMT_STAT_OVER;
            return; /* notify EOS to video player as soon as STOPPED */

        case SVCTX_NTFY_CODE_STOPPED:
        {
            if(_MMP_VE_ELMT_STAT_OVER == pt_elmt_1st->e_elmt_stat)
            {
                e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_STOP_EOS;
            }
            else
            {
                if(pt_elmt_1st->ui4_notify_flag & MMP_VE_PLAY_FLAG_MEDIA_FRAMERATE_NOT_SUPPORT)
                {
                    e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_STOP_EOS;
                }
                else
                {
                    CHAR * ps_mscvt = "mscvt";  // should equal to MSCVT_NAME
                    CHAR   ps_active_app[APP_NAME_MAX_LEN+1] = {0};

                    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()
                        && AMR_OK == a_am_get_next_active_app(ps_active_app)
                        && 0 == c_strncmp(ps_active_app, ps_mscvt, APP_NAME_MAX_LEN))
                    {
                        e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_INTRRPTD;
                    }
                    else
                    {
                        e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_STOP_END;
                    }
                }
            }
#ifndef APP_AUDIO_ITAF_SUPPORT
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_STOP;
#endif
            MMP_DBG_INFO(("{MMP} Reciv code_stopped and set the element stat to stop!!!\n"));
        }
        break;

		case SVCTX_NTFY_CODE_MEDIA_THUMBNAIL_CANCEL:
		{
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_THUMBNAIL_CANCEL_STOP;
		}
		break;

		case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_CLEAR_VIDEO_SVC:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_AUD;
		break;

		case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_NO_VIDEO_SVC:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_AUD_ONLY;
		break;

		case SVCTX_NTFY_CODE_SCRAMBLED_AUDIO_VIDEO_SVC:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_VID_AUD;
		break;

		case SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_CLEAR_AUDIO_SVC:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_VID;
			pt_elmt_1st->ui4_notify_flag |= MMP_VE_PLAY_FLAG_VIDEO_SCRAMBLE;
            /*  fix DTV00939697 scaramble video ,audio play normal*/
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;
	    break;

		case SVCTX_NTFY_CODE_SCRAMBLED_VIDEO_NO_AUDIO_SVC:
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_SCRAMBLE_VID_ONLY;
		break;

		case SVCTX_NTFY_CODE_MEDIA_SPEED_UPDATE:
		{
			//MW change speed and AP need refresh UI
			MM_SPEED_TYPE_T e_speed;
			UINT32          ui4_speed = 0;
			SIZE_T          z_size    = sizeof(UINT32);

			i4_ret = c_svctx_get(
						pt_this->h_svctx_hdl,
						SVCTX_MM_GET_TYPE_SPEED,
						(VOID*)&ui4_speed,
						&z_size
						);
			if (SVCTXR_OK != i4_ret)
			{
				return;
			}
			e_speed = (MM_SPEED_TYPE_T)ui4_speed;

			if (e_speed >= MM_SPEED_TYPE_REWIND_1024X && e_speed <= MM_SPEED_TYPE_REWIND_1X)
			{
				pt_this->e_play_stat =  MMP_VE_PLAY_STAT_FAST_RWD;
			}
			else if (e_speed >= MM_SPEED_TYPE_REWIND_0_DOT_9X && e_speed <= MM_SPEED_TYPE_REWIND_1_DIV_32X)
			{
				pt_this->e_play_stat =  MMP_VE_PLAY_STAT_SLOW_RWD;
			}
			else if (e_speed >= MM_SPEED_TYPE_FORWARD_1_DIV_32X && e_speed <= MM_SPEED_TYPE_FORWARD_0_DOT_9X)
			{
				pt_this->e_play_stat =  MMP_VE_PLAY_STAT_SLOW_FWD;
			}
			else if (e_speed > MM_SPEED_TYPE_FORWARD_1X && e_speed <= MM_SPEED_TYPE_FORWARD_1024X)
			{
				pt_this->e_play_stat =  MMP_VE_PLAY_STAT_FAST_FWD;
			}
			else if (e_speed == MM_SPEED_TYPE_FORWARD_1X)
			{
				pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PLAY;
			}
			else if (e_speed == MM_SPEED_TYPE_PAUSE)
			{
			    if(pt_this->e_play_stat != MMP_VE_PLAY_STAT_BLANK)
                {
                    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PAUSE;
                }
			}
			e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_SPEED_UPDATE;
		}
		break;

        case SVCTX_NTFY_CODE_EXISTED_CC_IND_CHG:
            i4_ret = video_engine_handle_scdb_update(pt_this, ST_CLOSED_CAPTION);
        break;

        case SVCTX_NTFY_CODE_MEDIA_LOST:
            MMP_DBG_INFO(("<MMP> media lost msg tranf \n"));
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_MEDIA_LOST;
        break;

        case SVCTX_NTFY_CODE_PVR_TRICK_REACH_VALID_RANGE_END:
            pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PAUSE;
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PVR_TRICK_REACH_VALID_RANGE_END;
        break;

        case SVCTX_NTFY_CODE_AUDIO_DOLBY_ATMOS:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_DOLBY_ATMOS;
            break;
        case SVCTX_NTFY_CODE_AUDIO_DOLBY_NO_ATMOS:
            e_ve_nfy_code = MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_DOLBY_NO_ATMOS;
            break;

        default:
            return;
    }

    if(pt_this->pf_play_nfy_fct!=NULL)
    {
           pt_this->pf_play_nfy_fct(e_ve_nfy_code, NULL);
    }
}

/*----------------------------------------------------------------------------
 * Name: _svctx_media_open_nfy_fct
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
static VOID _svctx_media_open_nfy_fct(
                    HANDLE_T                        h_ctx_hdl,        /* in  */
                    SVCTX_COND_T                    e_ctx_cond,       /* in  */
                    SVCTX_NTFY_CODE_T               e_nfy_code,       /* in  */
                    STREAM_TYPE_T                   e_stm_type,       /* in  */
                    VOID*                           pv_nfy_tag,       /* in  */
                    VOID*                           pv_file_hdl       /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pv_nfy_tag;
    HANDLE_T h_elmt_hdl = (HANDLE_T)pv_file_hdl;

    if(NULL == pt_this)
    {
        MMP_ASSERT(FALSE);
        return;
    }
    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _video_engine_do_nfy_fct,
                    (VOID*)(UINT32)pt_this->t_inst_id,
                    (VOID*)(UINT32)h_elmt_hdl,
                    (VOID*)(UINT32)e_stm_type,
                    (VOID*)(UINT32)e_nfy_code
                    );
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
static VOID _svctx_media_play_nfy_fct(
                    HANDLE_T                        h_ctx_hdl,        /* in  */
                    SVCTX_COND_T                    e_ctx_cond,       /* in  */
                    SVCTX_NTFY_CODE_T               e_nfy_code,       /* in  */
                    STREAM_TYPE_T                   e_stm_type,       /* in  */
                    VOID*                           pv_nfy_tag        /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pv_nfy_tag;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);

    if(NULL == pt_this || NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return;
    }

    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _video_engine_do_nfy_fct,
                    (VOID*)(UINT32)pt_this->t_inst_id,
                    (VOID*)(UINT32)pt_elmt->h_elmt_hdl,
                    (VOID*)(UINT32)e_stm_type,
                    (VOID*)(UINT32)e_nfy_code
                    );
}

static INT32 _mmp_ve_play_inst_insert(
                    _MMP_VE_PLAY_INST_PTR_T         pt_play_inst
                    )
{
    _MMP_VE_INST_ID_T i = 0;

    for(i = 0; i < _MMP_VERC_PLAY_INST_NUM; i++)
    {
        if(NULL == at_g_play_inst_list[i])
        {
            pt_play_inst->t_inst_id = i;
            at_g_play_inst_list[i] = pt_play_inst;
            return MMPR_OK;
        }
    }

    MMP_DBG_INFO(("{MMP} The length of apt_g_ve_inst_array[] is too short. %s:%d\r\n", __FUNCTION__, __LINE__));
    MMP_ASSERT(FALSE);

    return MMPR_BUF_NOT_ENOUGH;
}

static INT32 _mmp_ve_play_inst_remove(
                    _MMP_VE_PLAY_INST_PTR_T         pt_play_inst
                    )
{
    _MMP_VE_INST_ID_T i = 0;

    for(i = 0; i < _MMP_VERC_PLAY_INST_NUM; i++)
    {
        if(pt_play_inst == at_g_play_inst_list[i])
        {
            pt_play_inst->t_inst_id = 0xFFFF;
            at_g_play_inst_list[i] = NULL;
            return MMPR_OK;
        }
    }
    MMP_DBG_INFO(("{MMP} This engine instance is not kept in apt_g_ve_inst_array[]. %s:%d\r\n", __FUNCTION__, __LINE__));
    MMP_ASSERT(FALSE);

    return MMPR_INV_ARG;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_iter_aud
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
static BOOL _video_engine_iter_aud(
                    UINT16                          ui2_num_recs,
                    UINT16                          ui2_idx,
                    const STREAM_COMP_ID_T*         pt_comp_id,
                    const SCDB_REC_T*               pt_scdb_rec,
                    VOID*                           pv_fltr_tag)
{
#ifdef APP_MMP_PVR_AUDIO_SWITCH_CUST_RULE
	return video_engine_iter_aud_cust(ui2_num_recs,
		                    			ui2_idx,
		                    			pt_comp_id,
		                    			pt_scdb_rec,
		                    			pv_fltr_tag);
#else
    MMP_VE_AUD_INFO_T* pt_aud_info = (MMP_VE_AUD_INFO_T*)pv_fltr_tag;
    UINT16 i = 0, ui2_adj_idx = 0;

    if (_MMP_VERC_AUD_MAX_NUM <= pt_aud_info->ui2_aud_num)
    {
        return TRUE;
    }

    if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG)
    {
            UINT16      ui2_comp_idx = STRM_COMP_FILTER_GET_COMP_IDX(ui2_idx);
            UINT16      ui2_loop_idx = STRM_COMP_FILTER_GET_LOOP_IDX(ui2_idx);
            if (ui2_loop_idx > 0)
            {
                if (ui2_comp_idx == ui2_num_recs)
                {
                    video_engine_mpeg_aud_can_select(
                              &pt_scdb_rec->u.t_audio_mpeg,
                              FALSE,
                              TRUE);
                    return TRUE;
                }
                if (video_engine_mpeg_aud_can_select(
                        &pt_scdb_rec->u.t_audio_mpeg,
                        FALSE,
                        FALSE) == FALSE)
                {
                    return FALSE;
                }
                //add in second loop
            }
            else
            {
                if (ui2_comp_idx < ui2_num_recs)
                {
                    video_engine_mpeg_aud_can_select(
                            &pt_scdb_rec->u.t_audio_mpeg,
                            TRUE,
                            FALSE);
                }
                //do not add in first loop
                return FALSE;
            }
    }
    else
    {
        if((_MMP_VERC_AUD_MAX_NUM <= ui2_idx) ||
            (ui2_num_recs <= ui2_idx))
        {
            return TRUE;
        }
    }

    /* digital audio rec ? */
    switch(pt_scdb_rec->e_rec_type)
    {
        case SCDB_REC_TYPE_AUDIO_MPEG:
        case SCDB_REC_TYPE_AUDIO_PS:
        case SCDB_REC_TYPE_AUDIO_AVI:
        case SCDB_REC_TYPE_AUDIO_MP4:
        case SCDB_REC_TYPE_AUDIO_ASF:
        case SCDB_REC_TYPE_AUDIO_MKV:
        case SCDB_REC_TYPE_AUDIO_ANALOG:
        case SCDB_REC_TYPE_AUDIO_DIGITAL:
        case SCDB_REC_TYPE_AUDIO_RM:
        case SCDB_REC_TYPE_SUBTITLE_DVB:
        case SCDB_REC_TYPE_SUBTITLE_DIVX:
        case SCDB_REC_TYPE_AUDIO_ES:
        case SCDB_REC_TYPE_AUDIO_FLV:
        case SCDB_REC_TYPE_AUDIO_OGG:
            break;

        default :
            return FALSE;
    }



    for (i = 0; i < _MMP_VERC_AUD_MAX_NUM; i++)
    {
        if (NULL == pt_aud_info->at_comp_id[i].pv_stream_tag)
        {
            ui2_adj_idx = i;
            break;
        }
    }

    if (_MMP_VERC_AUD_MAX_NUM == i)
    {
        return TRUE;
    }

    /* update audio info */
    c_memcpy(&pt_aud_info->at_comp_id[ui2_adj_idx], pt_comp_id, sizeof(STREAM_COMP_ID_T));

    if(((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_PS) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_ps.ui1_stream_id) &&
        (pt_aud_info->ui4_strm_sub_id == pt_scdb_rec->u.t_audio_ps.ui1_sub_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_AVI) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_avi.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_MP4) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_mp4.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_ASF) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_asf.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_MKV) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_mkv.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_MPEG) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_mpeg.ui2_pid) &&
        (pt_aud_info->ui4_strm_sub_id == pt_scdb_rec->u.t_audio_mpeg.ui1_index))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_ES) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_es.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_RM) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_rm.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_SUBTITLE_DVB) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_dvb_sbtl.ui2_pid))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_SUBTITLE_DIVX) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_subtitle_avi.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_FLV) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_flv.ui4_stream_id))
       ||
       ((pt_scdb_rec->e_rec_type  == SCDB_REC_TYPE_AUDIO_OGG) &&
        (pt_aud_info->ui4_strm_id == pt_scdb_rec->u.t_audio_ogg.ui4_stream_id)))
    {
        pt_aud_info->ui2_sel_idx = ui2_adj_idx;
    }


    MMP_DBG_INFO(("{mmp} f: %s, l: %d, func: %s: e_rec_type: %d.\n", __FILE__, __LINE__, __FUNCTION__, pt_scdb_rec->e_rec_type));
    
    switch (pt_scdb_rec->e_rec_type)
    {
        case SCDB_REC_TYPE_AUDIO_MPEG:
        {
            c_strncpy(pt_aud_info->as_lang[ui2_adj_idx],
                      pt_scdb_rec->u.t_audio_mpeg.s_lang,
                      ISO_639_LANG_LEN);
        }
        break;
            
        case SCDB_REC_TYPE_AUDIO_AVI:
        {
            c_strncpy(pt_aud_info->as_lang[ui2_adj_idx],
                      pt_scdb_rec->u.t_audio_avi.s_lang,
                      ISO_639_LANG_LEN);
        }
        break;

        case SCDB_REC_TYPE_AUDIO_MP4:
        {
            c_strncpy(pt_aud_info->as_lang[ui2_adj_idx],
                      pt_scdb_rec->u.t_audio_mp4.s_lang,
                      ISO_639_LANG_LEN);        
        }
        break;

        case SCDB_REC_TYPE_AUDIO_ASF:
        {
            if(c_strlen(pt_scdb_rec->u.t_audio_asf.s_lang) == 0)
            {
                c_strncpy(pt_aud_info->as_lang[ui2_adj_idx],
                          ISO_639_DEFAULT,
                          ISO_639_LANG_LEN);
            }
            else
            {
                c_strncpy(pt_aud_info->as_lang[ui2_adj_idx],
                          pt_scdb_rec->u.t_audio_asf.s_lang,
                          ISO_639_LANG_LEN);
            }
        }
        break;

        case SCDB_REC_TYPE_AUDIO_MKV:
        {
            c_strncpy(pt_aud_info->as_lang[ui2_adj_idx],
                      pt_scdb_rec->u.t_audio_mkv.s_lang,
                      ISO_639_LANG_LEN);
        }
        break;

        default:
        {
            c_strncpy(pt_aud_info->as_lang[ui2_adj_idx],
                      ISO_639_DEFAULT,
                      ISO_639_LANG_LEN);
        }
        break;
    }

    pt_aud_info->ui2_aud_num++;

    MMP_DBG_INFO(("%s[%d] ui2_aud_num:%d\r\n",__FUNCTION__,__LINE__,pt_aud_info->ui2_aud_num));
    return FALSE;
#endif
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_strm_comp_filter
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
static BOOL _video_engine_strm_comp_filter(
                    UINT16                          ui2_num_recs,     /* in  */
                    UINT16                          ui2_idx,          /* in  */
                    const STREAM_COMP_ID_T*         pt_comp_id,       /* in  */
                    const SCDB_REC_T*               pt_scdb_rec,      /* in  */
                    VOID*                           pv_fltr_tag       /* in  */
                    )
{
#ifdef	APP_MMP_VIDEO_STRM_COMP_FILTER_CUST_RULE
	return video_engine_strm_comp_filter_cust_rule(ui2_num_recs,
													ui2_idx,
													pt_comp_id,
													pt_scdb_rec,
													pv_fltr_tag);
#else
	BOOL                      b_match = FALSE;
    _MMP_VE_PLAY_INST_PTR_T   pt_this = (_MMP_VE_PLAY_INST_PTR_T)pv_fltr_tag;

    if((NULL == pt_comp_id) || (NULL == pt_scdb_rec) || (NULL == pt_this))
    {
        MMP_ASSERT(FALSE);
        return b_match;
    }

    switch(pt_scdb_rec->e_rec_type)
    {
        case SCDB_REC_TYPE_VIDEO_AVI:
        case SCDB_REC_TYPE_VIDEO_PS:
        case SCDB_REC_TYPE_VIDEO_MP4:
        case SCDB_REC_TYPE_VIDEO_ASF:
        case SCDB_REC_TYPE_VIDEO_MKV:
        case SCDB_REC_TYPE_VIDEO_MPEG:
        case SCDB_REC_TYPE_VIDEO_ANALOG:
        case SCDB_REC_TYPE_VIDEO_ES:
        case SCDB_REC_TYPE_VIDEO_RM:
        case SCDB_REC_TYPE_VIDEO_FLV:
        case SCDB_REC_TYPE_VIDEO_OGG:
        {
            return TRUE;
        }
        case SCDB_REC_TYPE_AUDIO_MPEG:
        {
#ifdef APP_LAST_MEMORY_SUPPORT
            UINT16      ui2_comp_idx = STRM_COMP_FILTER_GET_COMP_IDX(ui2_idx);
            UINT16      ui2_loop_idx = STRM_COMP_FILTER_GET_LOOP_IDX(ui2_idx);
            if (ui2_loop_idx > 0)
            {
                if (ui2_comp_idx == ui2_num_recs)
                {
                    b_match = TRUE;
                }
                else
                {
                    //get num
                    if (video_engine_mpeg_aud_can_select(
                                &pt_scdb_rec->u.t_audio_mpeg,
                                FALSE,
                                FALSE))
                    {
                        MMP_DBG_INFO(("check aud valid num:%d/%d\n", ui2_valid_aud_num, ui2_audio_play_idx));
                        if(ui2_audio_play_idx == ui2_valid_aud_num++)
                        {
                            b_match = TRUE;
                        }
                    }
                }
            }
            else
            {
                //fill lang first
                if (ui2_comp_idx < ui2_num_recs)
                {
                    video_engine_mpeg_aud_can_select(
                            &pt_scdb_rec->u.t_audio_mpeg,
                            TRUE,
                            FALSE);
                }
                b_match = FALSE;
            }
            if (b_match)
            {
                 //clear
                 video_engine_mpeg_aud_can_select(
                              &pt_scdb_rec->u.t_audio_mpeg,
                              FALSE,
                              TRUE);
            }
            break;
#else
            return TRUE;
#endif
        }
        case SCDB_REC_TYPE_AUDIO_PS:
        case SCDB_REC_TYPE_AUDIO_AVI:
        case SCDB_REC_TYPE_AUDIO_MP3:
        case SCDB_REC_TYPE_AUDIO_MP4:
        case SCDB_REC_TYPE_AUDIO_ASF:
        case SCDB_REC_TYPE_AUDIO_MKV:
        case SCDB_REC_TYPE_AUDIO_ANALOG:
        case SCDB_REC_TYPE_AUDIO_DIGITAL:
        case SCDB_REC_TYPE_AUDIO_ES:
        case SCDB_REC_TYPE_AUDIO_RM:
        case SCDB_REC_TYPE_AUDIO_FLV:
        case SCDB_REC_TYPE_AUDIO_OGG:
        {
#ifdef APP_LAST_MEMORY_SUPPORT
            if(ui2_audio_play_idx == ui2_valid_aud_num++)
#endif
            b_match = TRUE;
        }
        break;
		//internal ones not include Close captain
		case SCDB_REC_TYPE_SUBTITLE_EXT:
        {
#ifdef APP_LAST_MEMORY_SUPPORT
            b_match = video_engine_chk_sbtl_last_mem(ST_SUBTITLE, TRUE, FALSE);
#endif
        }
		break;

        case SCDB_REC_TYPE_SUBTITLE_DVB:
        case SCDB_REC_TYPE_SUBTITLE_DIVX:
        case SCDB_REC_TYPE_SUBTITLE_MKV:
        case SCDB_REC_TYPE_SUBTITLE_MP4:
		case SCDB_REC_TYPE_SUBTITLE_PS:
		case SCDB_REC_TYPE_CLOSED_CAPTION:
        case SCDB_REC_TYPE_ISDB_CAPTION:
        case SCDB_REC_TYPE_SUBTITLE_PGS:
        {
			if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_CLOSED_CAPTION)
			{
				   if ((pt_scdb_rec->u.t_atsc_cc.e_type == CC_ATSC_LINE_21 &&
				   	    pt_scdb_rec->u.t_atsc_cc.udata.t_cc_atsc_line_21.b_det_in_descr == FALSE)
				   	   ||
				   	   (pt_scdb_rec->u.t_atsc_cc.e_type == CC_ATSC_DTV &&
				   	   	pt_scdb_rec->u.t_atsc_cc.udata.t_cc_atsc_dtv.ui1_caption_svc_num == 0)
				   	   	)
				   {
						b_match = FALSE;
						break;
				   }
			}
#ifdef APP_LAST_MEMORY_SUPPORT
			b_match = video_engine_chk_sbtl_last_mem(pt_comp_id->e_type, FALSE, FALSE);
#endif
		}
		break;

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
		case SCDB_REC_TYPE_TELETEXT_DVB:
		case SCDB_REC_TYPE_VBI_TELETEXT_DVB:
		{
#ifdef APP_LAST_MEMORY_SUPPORT
			if (video_engine_valid_ttx(pt_scdb_rec))
			{
				b_match = video_engine_chk_sbtl_last_mem(pt_comp_id->e_type, FALSE, FALSE);
			}
#endif
		}
		break;
#endif
		default:
		break;
    }


	if (b_match)
    {
         _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
        if (pt_elmt)
        {
            switch (pt_comp_id->e_type)
            {
                case ST_SUBTITLE:
                case ST_CLOSED_CAPTION:
                case ST_TELETEXT:
                case ST_ISDB_CAPTION:
                {
                    pt_elmt->t_sbtl_comp_id = *pt_comp_id;
                    MMP_DBG_INFO(("filter got comp id:%x\n", pt_comp_id->pv_stream_tag));
                }
                break;
                default:
                break;
            }
        }
    }
     //let AP select teletext by itself, always return False just record compid
    if (pt_comp_id->e_type == ST_TELETEXT)
    {
        b_match =  FALSE;
    }
	if (b_match || ui2_idx+1 == ui2_num_recs)
	{
        //clear search idx when not found, for selecting in next loop
#ifdef APP_LAST_MEMORY_SUPPORT
        video_engine_chk_sbtl_last_mem(pt_comp_id->e_type, FALSE, TRUE);
       if (pt_comp_id->e_type == ST_AUDIO)
       {
	       ui2_valid_aud_num = 0;
       }
#endif
	}

    return b_match;
#endif
}

static INT32 _video_engine_elmt_open(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    _MMP_VE_ELMT_INFO_PTR_T         pt_elmt           /* in/out */
                    )
{
    MM_SVC_COMMAND_T at_cmd[8];
    UINT8 ui1_cmd_num = 0;
    SRC_TYPE_T e_mm_src_type;
    HANDLE_T h_elmt_hdl = NULL_HANDLE;
#ifdef APP_NETWORK_SUPPORT
    MMP_UTIL_INFO_T t_util_info;
    BOOL b_has_info = FALSE;
#endif
    MM_EXT_SBTL_INFO t_sbtl_info;
    MM_LYRIC_INFO t_lyrc_info;
    BOOL b_match = FALSE;
    INT32 i4_ret = 0;

    /* keep filename */
    i4_ret = mmp_fid_add(pt_elmt->ps_file_name, &pt_elmt->t_elmt_fid);
    if(MMPR_OK != i4_ret)
    {
        pt_elmt->t_elmt_fid = MMP_FID_NULL_REC_IDX;
        return MMPR_BUF_NOT_ENOUGH;
    }

    do
    {
        i4_ret = mmp_util_filter_fct_by_audio(NULL, 0, pt_elmt->ps_file_name, 0, &b_match, NULL);
        if(MMPR_OK == i4_ret && TRUE == b_match)
        {
            pt_elmt->e_elmt_type = _MMP_VE_ELMT_TYPE_AUDIO;
            break;
        }

        i4_ret = mmp_util_filter_fct_by_video(NULL, 0, pt_elmt->ps_file_name, 0, &b_match, NULL);
        if(MMPR_OK == i4_ret && TRUE == b_match)
        {
            pt_elmt->e_elmt_type = _MMP_VE_ELMT_TYPE_VIDEO;
            break;
        }

        pt_elmt->h_elmt_hdl = NULL_HANDLE;
        return MMPR_NOT_SUPPORT;

    }while(0);

    at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_MEDIA_PATH;
    at_cmd[ui1_cmd_num].u.ps_text = (CHAR*)pt_elmt->ps_file_name;
    ui1_cmd_num++;

    switch (pt_elmt->t_file_src)
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

    if(MMP_FILE_SRC_DLNA == pt_elmt->t_file_src)
    {
#ifdef APP_NETWORK_SUPPORT
        c_memset(&t_util_info, 0, sizeof(MMP_UTIL_INFO_T));

        t_util_info.e_type = MMP_UTIL_IT_STRM_INFO;
        i4_ret = pt_this->pf_get_media_info_fct(
                              pt_elmt->ps_file_name,
                              &b_has_info,
                              &t_util_info
                              );
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} pt_this->pf_get_media_info_fct() returns  %s:%d %d\r\n", __FUNCTION__, __LINE__,i4_ret));
            return i4_ret;
        }

        if(TRUE == b_has_info)
        {
            pt_elmt->t_elmt_fmt = t_util_info.u.t_strm_info.t_format;

            at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_STRM_INFO;
            at_cmd[ui1_cmd_num].u.pv_data = &t_util_info.u.t_strm_info;
            ui1_cmd_num++;
        }

        at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_PROTOCL;
        at_cmd[ui1_cmd_num].u.ui4_data = PROTOCL_MODE_DLNA;
        ui1_cmd_num++;
#else
        pt_elmt->h_elmt_hdl = NULL_HANDLE;
        return MMPR_NOT_SUPPORT;
#endif
    }
    else if (MMP_FILE_SRC_NET_NEIGHBOR == pt_elmt->t_file_src)
    {
        at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_PROTOCL;
        at_cmd[ui1_cmd_num].u.ui4_data = PROTOCL_MODE_UNKNOWN;
        ui1_cmd_num++;
    }
    else
    {
#ifdef APP_MMP_SUBTITLE_CUSTOMER_SUPPORT
        if (_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
        {
            /* init external subtitle info */
            CHAR* ps_ext = c_strrchr(pt_elmt->ps_file_name, '.');
            if (ps_ext == NULL ||
                c_strcasecmp(ps_ext, ".pvr" ) != 0)
            {
	            t_sbtl_info.e_type = MM_EXT_SBTL_TYPE_LST;
	            t_sbtl_info.u.ps_ext_lst = _MMP_VE_EXT_SBTL_TYPE_LIST;
	            t_sbtl_info.ps_prf_lang_lst = "eng;chi;fre;"; /* For MW test */

	            at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_EXT_SBTL_PATH;
	            at_cmd[ui1_cmd_num].u.pv_data = &t_sbtl_info;
                ui1_cmd_num++;
            }
        }
        else /* _MMP_VE_ELMT_TYPE_AUDIO  */
        {
            t_lyrc_info.e_type = MM_LYRIC_TYPE_LRC;
            t_lyrc_info.u.ps_lyric_list = "lrc;";
            t_lyrc_info.ps_prf_lang_lst = "eng;chi;fre;";

            at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_EXT_LYRIC_PATH;
            at_cmd[ui1_cmd_num].u.pv_data = &t_lyrc_info;
            ui1_cmd_num++;
        }
#else
		if (_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
        {
            /* init external subtitle info */
            t_sbtl_info.e_type = MM_EXT_SBTL_TYPE_LST;
            t_sbtl_info.u.ps_ext_lst = _MMP_VE_EXT_SBTL_TYPE_LIST;
            t_sbtl_info.ps_prf_lang_lst = "eng;chi;fre;"; /* For MW test */

            at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_EXT_SBTL_PATH;
            at_cmd[ui1_cmd_num].u.pv_data = &t_sbtl_info;
        }
        else /* _MMP_VE_ELMT_TYPE_AUDIO  */
        {
            t_lyrc_info.e_type = MM_LYRIC_TYPE_LRC;
            t_lyrc_info.u.ps_lyric_list = "lrc;";
            t_lyrc_info.ps_prf_lang_lst = "eng;chi;fre;";

            at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_EXT_LYRIC_PATH;
            at_cmd[ui1_cmd_num].u.pv_data = &t_lyrc_info;
        }

        ui1_cmd_num++;
#endif
    }

    /* To fix DTV00096439 */
    at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_PLAY_MODE;
    at_cmd[ui1_cmd_num].u.ui1_data = (UINT8)MM_PLAY_MODE_PLAY;
    ui1_cmd_num++;
    i4_ret = mmp_util_filter_fct_by_video_3d(NULL, 0, pt_elmt->ps_file_name, 0, &b_match, NULL);
    if(MMPR_OK == i4_ret && TRUE == b_match)
    {
        at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_SET_FILL_SCDB_MODE;
        at_cmd[ui1_cmd_num].u.ui1_data = (UINT8)MM_SVC_FILL_SCDB_APPEND;
        ui1_cmd_num++;
    }

    at_cmd[ui1_cmd_num].e_code = MM_SVC_CMD_CODE_END;

    /* file id dispatch */
    
     DBG_LOG_PRINT(("**   *** file:%s, %s,%d\r\n",pt_elmt->ps_file_name,__FUNCTION__,__LINE__));
    i4_ret = _mmp_vp_video_open(pt_elmt->ps_file_name, pt_this) ;
    DBG_LOG_PRINT(("[%s %d]i4_ret == %d\n",__FUNCTION__,__LINE__,i4_ret));
#ifdef NEVER
#ifdef ENABLE_MULTIMEDIA
    MMP_DBG_INFO(("{MMP} c_svctx_media_open %d %s:%d\r\n", pt_elmt->h_elmt_hdl,__FUNCTION__, __LINE__));
    i4_ret = c_svctx_media_open(
                    pt_this->h_svctx_hdl,
                    at_cmd,
                    _svctx_media_open_nfy_fct,
                    (VOID*)pt_this,
                    &h_elmt_hdl
                    );
#else
    i4_ret = SVCTXR_NOT_SUPPORT;
#endif
#endif /* NEVER */
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_media_open fail:%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        h_elmt_hdl = NULL_HANDLE;
    }

    pt_elmt->h_elmt_hdl = h_elmt_hdl;

    if (SVCTXR_OK == i4_ret)
    {
        i4_ret = MMPR_OK;
    }
    else if (SVCTXR_INV_ENTRY == i4_ret)
    {
        MMP_DBG_INFO(("{MMP} Video Engine MMPR_NO_DATA :%s:%d:%d\r\n", __FUNCTION__, __LINE__));
        i4_ret = MMPR_NO_DATA;
    }
    else
    {
        MMP_DBG_INFO(("{MMP} Video Engine MMPR_NOT_SUPPORT :%s:%d:%d\r\n", __FUNCTION__, __LINE__));
        i4_ret = MMPR_NOT_SUPPORT;
    }

    pt_elmt->i4_elmt_ret = i4_ret;

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_elmt_close
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
static INT32 _video_engine_elmt_close(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    _MMP_VE_ELMT_INFO_PTR_T         pt_elmt           /* in  */
                    )
{
    INT32 i4_ret = 0;
	
    _mmp_vp_video_stop();

    if(NULL_HANDLE == pt_elmt->h_elmt_hdl)
    {
        return MMPR_IS_CLOSED;
    }

    /* free path */
    if(MMP_FID_NULL_REC_IDX != pt_elmt->t_elmt_fid)
    {
        i4_ret = mmp_fid_del(pt_elmt->t_elmt_fid);
        MMP_ASSERT(MMPR_OK == i4_ret);
    }

#ifdef NEVER
#ifdef ENABLE_MULTIMEDIA
    MMP_DBG_INFO(("{MMP} c_svctx_media_close %d %s:%d\r\n", pt_elmt->h_elmt_hdl,__FUNCTION__, __LINE__));
    i4_ret = c_svctx_media_close(pt_this->h_svctx_hdl, pt_elmt->h_elmt_hdl);
#else
    i4_ret = SVCTXR_NOT_SUPPORT;
#endif
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_media_close Error %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }
#endif /* NEVER */


#if 0 /*CR 391724*/
    c_memset(pt_elmt, 0, sizeof(_MMP_VE_ELMT_INFO_T));
#else
    VIDEO_ENGINE_ELMT_RESET(*pt_elmt);
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_divx_cert
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
static INT32 _video_engine_divx_cert(
                     _MMP_VE_PLAY_INST_PTR_T         pt_this,     /* in  */
                     MMP_VE_DIVX_CERT_PTR_T         pt_divx_cert      /* out */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = NULL;
    DRM_INFO_SVCTX_T t_drm_info_svctx;
    DIVX_DRM_BASIC_INFO_T t_drm_info_basic;
#ifdef _MMP_VERC_DIVX
    MINFO_INFO_CODEC_ENC_T t_video_file_type;
#endif
    INT32 i4_ret = 0;

    if((NULL == pt_this) || (NULL == pt_divx_cert))
    {
        return MMPR_INV_ARG;
    }

    pt_elmt = &pt_this->at_elmt_info[_MMP_VE_ELMT_ID_1ST];

    if (TRUE != pt_elmt->b_check_yet)
    {
        c_memset(&t_drm_info_svctx, 0, sizeof(DRM_INFO_SVCTX_T));
        c_memset(&t_drm_info_basic, 0, sizeof(DIVX_DRM_BASIC_INFO_T));

        t_drm_info_svctx.ui4_idx = pt_divx_cert->ui4_title_id;
        t_drm_info_svctx.u.t_divx_drm_info_svctx.pt_divx_drm_basic_info = &t_drm_info_basic;

        /* get drm info */
#ifdef ENABLE_MULTIMEDIA
#ifdef _MMP_VERC_DIVX
        c_memset(&t_video_file_type, 0, sizeof(MINFO_INFO_CODEC_ENC_T));

        i4_ret = c_svctx_media_get_info(
                            pt_this->h_svctx_hdl,
                            pt_elmt->h_elmt_hdl,
                            SVCTX_MM_GET_TYPE_VID_CODEC_INFO,
                            &t_video_file_type,
                            sizeof(MINFO_INFO_CODEC_ENC_T)
                            );
        if(MINFO_INFO_CODEC_VID_ENC_DIVX ==  t_video_file_type)
        {
            pt_elmt->t_drm_info.t_file_type = MMP_VE_FILE_TYPE_DIVX;

            if(FALSE == _MMP_VERC_HAS_DIVX_SUPPORT())
            {
                return MMPR_NOT_SUPPORT;
            }
        }
        else
        {
            pt_elmt->t_drm_info.t_file_type = MMP_VE_FILE_TYPE_UNKNOWN;
        }
#endif
        i4_ret = c_svctx_media_get_info(
                            pt_this->h_svctx_hdl,
                            pt_elmt->h_elmt_hdl,
                            SVCTX_DRM_GET_TYPE_INFO,
                            &t_drm_info_svctx,
                            sizeof(DRM_INFO_SVCTX_T)
                            );
#else
        i4_ret = SVCTXR_NOT_SUPPORT;
#endif
        if (SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_media_get_info Error %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_NOT_SUPPORT;
        }

        if (DRM_TYPE_DIVX_DRM == t_drm_info_svctx.t_drm_type)
        {
            /* check basic info */
            if(t_drm_info_basic.ui1_flag & DIVX_DRM_AUTH_ERROR)
            {
                pt_elmt->t_drm_info.t_drm_type = MMP_VE_DRM_TYPE_UNAUTH;
                MMP_DBG_INFO(("{MMP} DivX DRM authorization error. %s %d \n", __FUNCTION__, __LINE__));
            }
            else if(t_drm_info_basic.ui1_flag & DIVX_DRM_RENTAL_EXPIRED)
            {
                pt_elmt->t_drm_info.t_drm_type = MMP_VE_DRM_TYPE_EXPIRE;
                pt_elmt->t_drm_info.ui4_use_limit = t_drm_info_basic.ui1_use_limit;
                pt_elmt->t_drm_info.ui4_use_count = t_drm_info_basic.ui1_use_count;
                pt_elmt->t_drm_info.ui4_use_left  = t_drm_info_basic.ui1_use_limit - t_drm_info_basic.ui1_use_count;
                MMP_DBG_INFO(("{MMP} DivX DRM expire: %d of %d.%s:%d\r\n",
                           t_drm_info_basic.ui1_use_count,
                           t_drm_info_basic.ui1_use_limit,
                           __FUNCTION__, __LINE__));
            }
            else if(t_drm_info_basic.ui1_flag & DIVX_DRM_RENTAL)
            {
                pt_elmt->t_drm_info.t_drm_type = MMP_VE_DRM_TYPE_RENTAL;
                pt_elmt->t_drm_info.ui4_use_limit = t_drm_info_basic.ui1_use_limit;
                pt_elmt->t_drm_info.ui4_use_count = t_drm_info_basic.ui1_use_count;
                pt_elmt->t_drm_info.ui4_use_left  = t_drm_info_basic.ui1_use_limit - t_drm_info_basic.ui1_use_count;
                MMP_DBG_INFO(("{MMP} DivX DRM rental: %d of %d %s:%d.\r\n",
                           t_drm_info_basic.ui1_use_count,
                           t_drm_info_basic.ui1_use_limit,
                           __FUNCTION__, __LINE__));
            }
        }
        else
        {
            pt_elmt->t_drm_info.t_drm_type = MMP_VE_DRM_TYPE_NORMAL;
            MMP_DBG_INFO(("{MMP} DivX DRM non-divx format  %s:%d..\r\n",__FUNCTION__, __LINE__));
        }

        pt_elmt->b_check_yet = TRUE;
    }

    c_memcpy(pt_divx_cert, &pt_elmt->t_drm_info, sizeof(MMP_VE_DIVX_CERT_T));

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_get_trick
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
static INT32 _video_engine_get_trick(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    SPLAYER_TrickSpeed_e*                pt_spd_type       /* out */
                    )
{
    //_MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    SPLAYER_TrickSpeed_e ui4_speed = 0;
    INT32  i4_ret = 0;
    //SIZE_T  z_size = sizeof(UINT32);
    APPL_SPLAYER_MOVIE_INFO_T *ptMovieInfo;
#if NEVER
    if(NULL == pt_elmt || NULL == pt_spd_type)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(_MMP_VE_ELMT_OPER_SEEK == pt_elmt->e_elmt_oper)
    {
        return MMPR_RES_NOT_READY;
    }

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_SPEED,
                    (VOID*)&ui4_speed,
                    &z_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_GET_TYPE_SPEED) Error %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    *pt_spd_type = (MM_SPEED_TYPE_T)ui4_speed;
#endif

    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_get_movie_speed(&gp_v_splayer, &ui4_speed);
        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_get_movie_speed() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
            return MMPR_FAIL;
        }
        else
        {
            DBG_LOG_PRINT(("[%s %d]ui4_speed == %d\r\n",__FUNCTION__,__LINE__,ui4_speed));
            *pt_spd_type = ui4_speed;
            DBG_LOG_PRINT(("[%s %d]pt_spd_type == %d\r\n",__FUNCTION__,__LINE__,*pt_spd_type));
        }
    }
    else
    {
        DBG_LOG_PRINT((" a_appl_splayer_get_movie_speed() Faid,%s,%d\r\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }

    DBG_LOG_PRINT(("**  *** %s,%d\r\n",__FUNCTION__,__LINE__));
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_set_trick
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
static INT32 _video_engine_set_trick(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                    SPLAYER_TrickSpeed_e                 e_spd_type        /* in  */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    //MM_SVC_TRICK_INFO_T t_trick = { e_spd_type };
    INT32 i4_ret = 0;
    SPLAYER_TrickSpeed_e         e_cur_speed;

    if (NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if (TRUE == pt_elmt->b_dont_play)
    {
        return MMPR_IS_STOPPED;
    }
#endif

#if 0/*Remove For Seek Error->Play*/
    if (_MMP_VE_ELMT_OPER_SEEK == pt_elmt->e_elmt_oper)
    {
        return MMPR_RES_NOT_READY;
    }
#endif
#if NEVER
    DBG_LOG_PRINT(("[%s %d]pt_elmt->e_elmt_stat == %d\n",__FUNCTION__,__LINE__,pt_elmt->e_elmt_stat));

    switch(pt_elmt->e_elmt_stat)
    {
        case _MMP_VE_ELMT_STAT_INIT:
        case _MMP_VE_ELMT_STAT_WAIT:
        case _MMP_VE_ELMT_STAT_ERROR:
        case _MMP_VE_ELMT_STAT_NOT_SUPPORT:
        case _MMP_VE_ELMT_STAT_READY:
#ifdef _MMP_VERC_PLAY_THUMB_SUPPORT
        case _MMP_VE_ELMT_STAT_THUMB:
#endif
        case _MMP_VE_ELMT_STAT_STOP:
        case _MMP_VE_ELMT_STAT_OVER:
            return MMPR_RES_NOT_READY;

        case _MMP_VE_ELMT_STAT_PLAY:
            break;

        default:
            MMP_ASSERT(FALSE);
    }
    {
        UINT32  ui4_speed = 0;
        SIZE_T  z_size = sizeof(UINT32);
        i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_SPEED,
                        (VOID*)&ui4_speed,
                        &z_size
                        );
        if (SVCTXR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }

        e_cur_speed = (MM_SPEED_TYPE_T)ui4_speed;
		if (e_cur_speed == e_spd_type &&
			e_spd_type != MM_SPEED_TYPE_STEP)
		{
			return MMPR_OK;
		}
    }
#endif

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
//when do trick we always stop ttx and 1X/Pause restart it @?
    if (e_spd_type != SPLAYER_MM_TRICK_SPEED_1X &&
        e_spd_type != SPLAYER_MM_TRICK_SPEED_0X)
    {
        if (pt_elmt->e_ttx_state == MMP_TTX_STATE_SHOWN ||
            pt_elmt->e_ttx_state == MMP_TTX_STATE_STARTED)
        {
            i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_STOP, 0);
        }
    }
#endif
#if NEVER
    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SET_TYPE_TRICK,
                    (VOID*)&t_trick,
                    sizeof(MM_SVC_TRICK_INFO_T)
                    );
	if (SVCTXR_BUFFER_UNDERFLOW == i4_ret)
	{
	  MMP_DBG_INFO(("{MMP} trick no act when buffer underflow\n"));
	  return MMPR_NO_ACTION;
	}

    if (SVCTXR_NOT_SUPPORT == i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_SET_TYPE_TRICK) returns %d %s:%d\n", i4_ret,__FUNCTION__, __LINE__));
        return MMPR_NOT_SUPPORT;
    }
    else if(SVCTXR_NEW_TRICK_FLOW == i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_SET_TYPE_TRICK) returns new trick for no index table case.\n"));
        return MMPR_TRICK_CHANGE;
    }
    else if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_SET_TYPE_TRICK) returns %d %s:%d\n", i4_ret,__FUNCTION__, __LINE__));
        return MMPR_FAIL;
    }
#endif
    /* **************set play speed of video**************/
    //1.first check the speed is forward or rewind
    if(e_spd_type < SPLAYER_MM_TRICK_SPEED_SLOW) //forword
    {
        if(gp_v_splayer != NULL)
        {
            i4_ret = a_appl_splayer_set_fastforword(&gp_v_splayer,e_spd_type);
            if(i4_ret != MMPR_OK)
            {
                DBG_LOG_PRINT((" a_appl_splayer_set_fastforword() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
            }
        }
    }
    else if(e_spd_type >= SPLAYER_MM_TRICK_SPEED_SLOW && e_spd_type < SPLAYER_MM_TRICK_SPEED_STEP)//rewind
    {
        if(gp_v_splayer != NULL)
        {
            i4_ret = a_appl_splayer_set_fastbackword(&gp_v_splayer,e_spd_type);
            if(i4_ret != MMPR_OK)
            {
                DBG_LOG_PRINT((" a_appl_splayer_set_fastbackword() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
            }
        }
    }

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
    //when change to normal restart it
    if (e_spd_type == SPLAYER_MM_TRICK_SPEED_1X ||
        e_spd_type == SPLAYER_MM_TRICK_SPEED_0X)
    {
        if (e_cur_speed != MM_SPEED_TYPE_FORWARD_1X &&
            e_cur_speed != MM_SPEED_TYPE_PAUSE)
        {
            i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_START, 0);
        }
    }
#endif

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _video_engine_start2play
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
static INT32 _video_engine_start2play(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                     MMP_VE_DIVX_CERT_PTR_T         pt_divx_cert      /* out */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret= MMPR_FAIL;
    DBG_LOG_PRINT(("**   *** %s,%d\r\n",__FUNCTION__,__LINE__));
    if ((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    DBG_LOG_PRINT(("**   *** file:%s, %s,%d\r\n",pt_elmt->ps_file_name,__FUNCTION__,__LINE__));
    i4_ret = _mmp_vp_video_play(pt_elmt->ps_file_name, pt_this);

    return i4_ret;

}
#ifdef NEVER

/*----------------------------------------------------------------------------
 * Name: _video_engine_start2play
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
static INT32 _video_engine_start2play(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                     MMP_VE_DIVX_CERT_PTR_T         pt_divx_cert      /* out */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
#ifndef APP_MMP_SHOW_BROKEN_THUMB
    MINFO_INFO_T t_minfo_rec;
#endif
    SRC_MM_INFO_T t_mm = {0};
    VSH_REGION_INFO_T t_vide_rgn = {0};
    VSH_REGION_INFO_T t_disp_rgn = {0};
    VSH_SET_PLANE_ORDER_INFO_T t_vpla_ord;
    SRC_DESC_T t_src_desc = {0};
    SNK_DESC_T t_snk_desc = {0};
    MM_SPEED_TYPE_T e_spd_type = MM_SPEED_TYPE_FORWARD_1X;
    UINT32 ui4_stream_mode = ST_MASK_AUDIO;
    MMP_FP_PRESENT_MODE_T t_present_mode;
    INT32 i4_ret = 0;
#ifdef APP_LAST_MEMORY_SUPPORT
    UINT8  ui1_lst_mode     = 0;
#ifdef APP_MMP_PVR_LAST_MEMORY_SUPPORT
	APP_CFG_MM_STOP_INFO_T         t_acfg_stop_info;
#endif
#endif

    if ((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if (TRUE == pt_elmt->b_dont_play)
    {
        return MMPR_IS_STOPPED;
    }
#endif

    if (NULL_HANDLE == pt_elmt->h_elmt_hdl)
    {
        pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;

        /* Added by You.Mai@1/24/2011 5:49:31PM to fix DTV00329275 */
        if (pt_elmt->t_elmt_fmt.e_media_type == MEDIA_TYPE_UNKNOWN)
        {
            pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_OVER;
        }

        return pt_elmt->i4_elmt_ret; /* c_svctx_media_open() returns FAIL */
    }

    switch(pt_elmt->e_elmt_stat)
    {
        case _MMP_VE_ELMT_STAT_INIT:
            if (NULL != pt_divx_cert)
            {
                pt_divx_cert->t_drm_type = MMP_VE_DRM_TYPE_NORMAL;
            }
            pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_WAIT;
            return MMPR_OK;

        case _MMP_VE_ELMT_STAT_WAIT:
            if (NULL != pt_divx_cert)
            {
                pt_divx_cert->t_drm_type = MMP_VE_DRM_TYPE_NORMAL;
            }
            return MMPR_OK;

        case _MMP_VE_ELMT_STAT_NOT_SUPPORT:
            return MMPR_NOT_SUPPORT;

        case _MMP_VE_ELMT_STAT_ERROR:
            return MMPR_INTERNAL_ERROR;

        case _MMP_VE_ELMT_STAT_READY:
#ifdef _MMP_VERC_PLAY_THUMB_SUPPORT
        case _MMP_VE_ELMT_STAT_THUMB:
#endif
        case _MMP_VE_ELMT_STAT_STOP:
        case _MMP_VE_ELMT_STAT_OVER:
            break;

        case _MMP_VE_ELMT_STAT_PLAY:
            return MMPR_IS_PLAYED;

        default:
            MMP_ASSERT(FALSE);
    }

#ifndef APP_MMP_SHOW_BROKEN_THUMB
    if(MMP_FILE_SRC_DLNA != pt_elmt->t_file_src ||
       MEDIA_TYPE_UNKNOWN == pt_elmt->t_elmt_fmt.e_media_type)
    {
#ifdef ENABLE_MULTIMEDIA
    	SIZE_T z_size = sizeof(MINFO_INFO_T);
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
            MMP_DBG_INFO(("{MMP} c_svctx_media_get_info() returns  %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }

        pt_elmt->t_elmt_fmt = t_minfo_rec.t_format;
    }
#endif

#ifdef _MMP_VERC_AUDIO_FMT_CHECK
    if(_MMP_VE_ELMT_TYPE_AUDIO == pt_elmt->e_elmt_type)
    {
        if(!FMT_IS_AUDIO_CATEGORY(pt_elmt->t_elmt_fmt))
        {
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;
            return MMPR_NOT_SUPPORT;
        }
    }
#endif

#ifdef _MMP_VERC_VIDEO_FMT_CHECK
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {
        if(!FMT_IS_VIDEO_CATEGORY(pt_elmt->t_elmt_fmt))
        {
            pt_this->e_play_stat = MMP_VE_PLAY_STAT_PLAY;
            return MMPR_NOT_SUPPORT;
        }
    }
#endif

    /* divx certification */
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type &&
       FALSE == pt_elmt->b_check_yet)
    {
        if(NULL == pt_divx_cert)
        {
            MMP_ASSERT(FALSE);
            return MMPR_INV_ARG;
        }

        pt_divx_cert->ui4_title_id = 0;

        i4_ret = _video_engine_divx_cert(pt_this, pt_divx_cert);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
        else if(MMP_VE_DRM_TYPE_NORMAL != pt_divx_cert->t_drm_type)
        {
            return MMPR_OK;
        }
    }

    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {
        ui4_stream_mode |= ST_MASK_VIDEO;
    }

    i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
    if (MMPR_OK != i4_ret)
    {
        t_present_mode = MMP_FP_PRESENT_MODE_FULL;
    }

#ifdef APP_LAST_MEMORY_SUPPORT
    do
    {
        UINT64 ui8_clip_id      = 0;
#ifdef APP_MMP_PVR_LAST_MEMORY_SUPPORT
        CHAR        ac_filepath[MMP_PVR_MAX_PATH_LEN] = {0};
#endif

        if ((_MMP_VE_ELMT_TYPE_VIDEO  == pt_elmt->e_elmt_type) &&
            (MMP_FP_PRESENT_MODE_FULL == t_present_mode)       &&
            (MMP_FILE_SRC_MASS_STRG   == pt_elmt->t_file_src))
        {
    		SIZE_T z_size = sizeof(UINT64);
            i4_ret = c_svctx_media_get_info(
                            pt_this->h_svctx_hdl,
                            pt_elmt->h_elmt_hdl,
                            SVCTX_MM_GET_MM_IDENTIFIER,
                            (VOID*)&ui8_clip_id,
                            z_size
                            );
            if (SVCTXR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP} c_svctx_media_get_info(SVCTX_MM_GET_MAGIC_NUMBER) returns  %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                break;
            }

            pt_elmt->t_stop_info.ui8_clip_id = ui8_clip_id;

            i4_ret = a_cfg_get_mmp_last_memory_onoff(&ui1_lst_mode);
            if (i4_ret != APP_CFGR_OK)
            {
                MMP_DBG_INFO(("{MMP} acfg get_mmp_last_memory_mode error return %d Line %d\n", i4_ret, __LINE__));
                break;
            }

            if (ui1_lst_mode == 1)/*Last Memory = OFF*/
            {
                break;
            }
#ifdef APP_MMP_PVR_LAST_MEMORY_SUPPORT
            i4_ret = video_engine_get_video_path(ac_filepath);
            if(i4_ret != MMPR_OK)
            {
                MMP_DBG_INFO(("\n{MMP} [last memory][error]video_engine_get_video_path return %d Line %d\n", i4_ret, __LINE__));
                break;
            }
            i4_ret = video_engine_get_video_last_mem((MMP_VE_PLAY_INST_PTR_T)pt_this,ac_filepath,&t_acfg_stop_info);
            if(i4_ret != MMPR_OK)
            {
                MMP_DBG_INFO(("\n{MMP} [last memory][error]video_engine_get_video_last_mem return %d Line %d\n", i4_ret, __LINE__));
                break;
            }
#else
            i4_ret = mmp_ve_stop_info_get(pt_this, pt_this->at_stop_info);
            if (i4_ret != MMPR_OK)
            {
                MMP_DBG_INFO(("\n{MMP} [last memory][error]mmp_ve_stop_info_get return %d Line %d\n", i4_ret, __LINE__));
                MMP_ASSERT(FALSE);
                break;
            }

            i4_ret = mmp_ve_stop_info_check(pt_this, &pt_elmt->t_stop_info);
            if (MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("\n{MMP} [last memory][error]mmp_ve_stop_info_check return %d Line %d\n", i4_ret, __LINE__));
                break;
            }
#endif
        }
        else
        {
            i4_ret = MMPR_NOT_SUPPORT;
        }
    } while(0);

    if (i4_ret != MMPR_OK)
    {
        ui1_lst_mode = 1;/*Last Memory = OFF*/
    }
    if (ui1_lst_mode == 0)/*Last Memory = ON*/
    {
#ifdef APP_MMP_PVR_LAST_MEMORY_SUPPORT
        t_mm.ui4_title_idx = t_acfg_stop_info.ui4_title_idx;
        t_mm.ui4_playlist_idx = t_acfg_stop_info.ui4_playlist_idx;
        t_mm.ui4_chap_idx = t_acfg_stop_info.ui4_chap_idx;
        t_mm.ui2_aud_idx = t_acfg_stop_info.ui2_aud_idx;
        t_mm.ui2_sub_idx = t_acfg_stop_info.ui2_sub_idx;
        t_mm.t_pos_info.u.render_info.ui8_aud_pts_info       = t_acfg_stop_info.ui8_aud_pts_info;
        t_mm.t_pos_info.u.render_info.ui8_aud_frame_position = t_acfg_stop_info.ui8_aud_frame_position;
        t_mm.t_pos_info.u.render_info.ui8_i_pts_info         = t_acfg_stop_info.ui8_i_pts_info;
        t_mm.t_pos_info.u.render_info.ui8_pts_info           = t_acfg_stop_info.ui8_pts_info;
        t_mm.t_pos_info.u.render_info.ui8_i_frame_position   = t_acfg_stop_info.ui8_i_frame_position;
        t_mm.t_pos_info.u.render_info.ui8_frame_position     = t_acfg_stop_info.ui8_frame_position;
        t_mm.t_pos_info.u.render_info.ui2_decoding_order     = t_acfg_stop_info.ui2_decoding_order;
        t_mm.t_pos_info.u.render_info.i4_temporal_reference  = t_acfg_stop_info.i4_temporal_reference;
        t_mm.t_pos_info.u.render_info.ui4_timestap           = t_acfg_stop_info.ui4_timestap;
        a_cfg_set_mmp_last_memory_onoff(1);

        MMP_DBG_INFO (("{MMP} [%s]:[%d]:ui4_title_idx == %lu,ui4_playlist_idx == %lu,\n",
                        __FUNCTION__,__LINE__,
            t_mm.ui4_title_idx,t_mm.ui4_playlist_idx));
        MMP_DBG_INFO (("{MMP} ui4_chap_idx == %lu,ui2_aud_idx = %d, ui2_sub_idx = %d, ui8_aud_pts_info = %llu,\n",
            t_mm.ui4_chap_idx,t_mm.ui2_aud_idx,
            t_mm.ui2_sub_idx,t_mm.t_pos_info.u.render_info.ui8_aud_pts_info));
        MMP_DBG_INFO (("{MMP} ui8_aud_frame_position = %llu,ui8_i_pts_info = %llu, ui8_pts_info = %llu,ui8_i_frame_position = %llu,\n",
            t_mm.t_pos_info.u.render_info.ui8_aud_frame_position,t_mm.t_pos_info.u.render_info.ui8_i_pts_info,
            t_mm.t_pos_info.u.render_info.ui8_pts_info,t_mm.t_pos_info.u.render_info.ui8_i_frame_position));
        MMP_DBG_INFO (("{MMP} ui8_frame_position = %llu,i4_temporal_reference = %ld, ui2_decoding_order = %d, ui4_timestap = %llu\n",
            t_mm.t_pos_info.u.render_info.ui8_frame_position,t_mm.t_pos_info.u.render_info.i4_temporal_reference,
            t_mm.t_pos_info.u.render_info.ui2_decoding_order,t_mm.t_pos_info.u.render_info.ui4_timestap));

#else
        t_mm.ui4_title_idx = pt_elmt->t_stop_info.ui4_title_idx;
        t_mm.ui4_playlist_idx = pt_elmt->t_stop_info.ui4_playlist_idx;
        t_mm.ui4_chap_idx = pt_elmt->t_stop_info.ui4_chap_idx;
        t_mm.ui2_aud_idx = pt_elmt->t_stop_info.ui2_aud_idx;
        t_mm.ui2_sub_idx = pt_elmt->t_stop_info.ui2_sub_idx;
        t_mm.t_pos_info = pt_elmt->t_stop_info.t_pos_info;

#ifdef APP_LAST_MEMORY_SUPPORT
#ifdef DIVX_PLUS_CER
        if(pt_elmt->t_stop_info.ui4_title_idx == pt_elmt->t_chap_num.ui4_title_idx
        && pt_elmt->t_stop_info.ui4_playlist_idx == pt_elmt->t_chap_num.ui4_list_idx)
        {
            ui2_audio_play_idx = pt_elmt->t_stop_info.ui2_aud_idx;
            ui2_subtitle_play_idx = pt_elmt->t_stop_info.ui2_sub_idx;
        }
        else

        {
            ui2_audio_play_idx = 0;
            ui2_subtitle_play_idx = 0;
        }
#else
        ui2_audio_play_idx = pt_elmt->t_stop_info.ui2_aud_idx;
        ui2_subtitle_play_idx = pt_elmt->t_stop_info.ui2_sub_idx;
#endif
#endif
#endif
    }
    else
#endif
    {
        t_mm.t_pos_info.t_pos_type = MM_SVC_POS_TYPE_ALL_TIME;
        t_mm.t_pos_info.ui2_idx = (UINT16)0;
        t_mm.t_pos_info.ui8_pos_val = (UINT64)0;
#ifdef APP_LAST_MEMORY_SUPPORT
        ui2_audio_play_idx = 0;
        ui2_subtitle_play_idx = 0;
#endif
    }


#ifdef APP_LAST_MEMORY_SUPPORT
    ui2_valid_aud_num = 0;
	video_engine_chk_sbtl_last_mem(ST_UNKNOWN, FALSE, TRUE);
#endif

	/*always enable subtitle if playing video*/
	if (_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
	{
		ui4_stream_mode |= (ST_MASK_SUBTITLE | ST_MASK_CLOSED_CAPTION | ST_MASK_ISDB_CAPTION);
    #ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
		ui4_stream_mode |= ST_MASK_TELETEXT;
    #endif
	}


    #ifdef APP_DVBT_SUPPORT
    {
        ISO_3166_COUNT_T s_country = {0};
        BOOL             b_independent_ad = FALSE;
        a_cfg_get_country(s_country);
        if (c_strcmp((CHAR*)s_country, "FIN") == 0)
        {
            b_independent_ad = TRUE;

        }
        i4_ret = c_svctx_media_set_info(
                        pt_this->h_svctx_hdl,
                        pt_elmt->h_elmt_hdl,
                        SVCTX_MM_SET_AUDIO_AD_TO_INDEPENDENT_AD,
                        (VOID*)&b_independent_ad,
                        sizeof(BOOL));
    }
    #endif

    t_mm.h_media = pt_elmt->h_elmt_hdl;
	/*alas!! this param never take effect put to FMT_UPDATE*/
    t_mm.t_speed = e_spd_type;

    /* set video region */
    t_vide_rgn.ui4_x = 0;
    t_vide_rgn.ui4_y = 0;
    t_vide_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_vide_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;

    /* set display region */
    if (_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)        // Video  1
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
    else            //  Audio
    {
        t_disp_rgn.ui4_x = (UINT32)0;
        t_disp_rgn.ui4_y = (UINT32)0;
        t_disp_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
        t_disp_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;
    }

    t_vpla_ord.e_order_ctrl = VSH_PLANE_ORDER_CTRL_BOTTOM;
    t_vpla_ord.u.ui1_num_layers = 0;

    t_src_desc.e_type = SRC_TYPE_MEDIA_STORGE;
    t_src_desc.u_info.t_mm = t_mm;

#ifdef APP_SUPPORT_MTK_ANDROID_RM
    t_src_desc.ui2_priority = 100;
#endif
#ifdef DIVX_PLUS_CER
    t_src_desc.ui4_title_idx = pt_elmt->t_chap_num.ui4_title_idx = 0;
    t_src_desc.ui4_playlist_idx = pt_elmt->t_chap_num.ui4_list_idx = 0;
    t_src_desc.ui4_chap_idx = pt_elmt->t_chap_num.ui4_chap_idx = 0;
#endif

    t_snk_desc.pt_video_region        = &t_vide_rgn;
    t_snk_desc.pt_disp_region         = &t_disp_rgn;
    t_snk_desc.pt_video_plane_order   = &t_vpla_ord;
    t_snk_desc.pt_video_strm_fltr_fct = _video_engine_strm_comp_filter;
    t_snk_desc.pv_video_strm_fltr_tag = (VOID*)pt_this;
    t_snk_desc.pt_audio_strm_fltr_fct = _video_engine_strm_comp_filter;
    t_snk_desc.pv_audio_strm_fltr_tag = (VOID*)pt_this;

    t_snk_desc.e_text_strm_type       = ST_SUBTITLE; /* To fix DTV00215125 */
    t_snk_desc.u_text_strm.t_subtitle.pt_fltr_fct = _video_engine_strm_comp_filter;
    t_snk_desc.u_text_strm.t_subtitle.pv_fltr_tag = (VOID*)pt_this;
    t_snk_desc.ps_snk_grp_name        = SN_PRES_MAIN_DISPLAY;
    /*CC and subtitle use different canvas to draw*/
	{
		HANDLE_T h_cc_canvas = a_nav_get_cc_canvas();
		if (NULL_HANDLE != pt_this->t_osd_info.h_sub_plane)
	    {
	        t_snk_desc.u_text_strm.t_subtitle.h_gl_plane = pt_this->t_osd_info.h_sub_plane;
	    }
	    else
	    {
	        t_snk_desc.u_text_strm.t_subtitle.h_gl_plane = pt_this->t_osd_info.h_canvas_ex;
	    }
		if (h_cc_canvas != NULL_HANDLE)
		{
			t_snk_desc.h_cc_gl_plane = h_cc_canvas;
		}
		else
		{
			t_snk_desc.h_cc_gl_plane = t_snk_desc.u_text_strm.t_subtitle.h_gl_plane;
		}
	}

    i4_ret = c_svctx_select_svc(
                    pt_this->h_svctx_hdl,
                    ui4_stream_mode,
                    &t_src_desc,
                    &t_snk_desc,
                    _svctx_media_play_nfy_fct,
                    (VOID*)pt_this
                    );
#ifdef APP_MMP_DBG_FLOW
        MMP_DBG_INFO(("{MMP} c_svctx_select_svc %d %s:%d\r\n", pt_elmt->h_elmt_hdl,__FUNCTION__, __LINE__));
#endif
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_select_svc() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }
#ifdef APP_IPCC_SUPPORT
	 video_engine_fill_ipcc_path(pt_elmt);
#endif

    pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;

    return MMPR_OK;
}
#endif /* NEVER */

/*----------------------------------------------------------------------------
 * Name: _video_engine_trick2play
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
static INT32 _video_engine_trick2play(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = MMPR_FAIL;
    DBG_LOG_PRINT(("**   *** %s,%d\r\n",__FUNCTION__,__LINE__));
#ifdef NEVER
    MM_SPEED_TYPE_T e_spd_type = MM_SPEED_TYPE_FORWARD_1X;
#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    MM_SVC_SBTL_SHOW_HIDE_T t_sbtl_show = { TRUE };
#endif
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if (MMP_FP_SHOW_ATTR_ID_SPEED == pt_elmt->t_spd_attr.e_id)
    {
        e_spd_type = (MM_SPEED_TYPE_T)(UINT32)pt_elmt->t_spd_attr.pv_param;
    }

    if (_MMP_VE_ELMT_STAT_OVER == pt_elmt->e_elmt_stat)
    {
        return MMPR_IS_STOPPED; /* for seek to end under pause state. */
    }

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    if (_MMP_VE_SBTL_STAT_OFF != pt_elmt->e_sbtl_stat)
    {
        i4_ret = mmp_ve_sbtl_set_show(pt_this, &t_sbtl_show);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    if (_MMP_VE_ELMT_OPER_BLANK == pt_elmt->e_elmt_oper)
    {
        i4_ret = video_engine_blank_hide(pt_this);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif

    i4_ret = _video_engine_set_trick(pt_this, e_spd_type);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} _video_engine_set_trick() returns  %s:%d %d\r\n", __FUNCTION__, __LINE__,i4_ret));
        return i4_ret;
    }
#endif /* NEVER */
    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_play_pause(&gp_v_splayer,TRUE);

        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_play_pause() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
            return i4_ret;
        }
        pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_PLAY;
        pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PLAY;

        return MMPR_IS_PLAYED;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_full_stop
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
static INT32 _video_engine_full_stop(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this           /* in  */
                    )
{
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if ((_MMP_VE_ELMT_STAT_WAIT  == pt_elmt->e_elmt_stat) ||
        (_MMP_VE_ELMT_STAT_READY == pt_elmt->e_elmt_stat))
    {
        pt_elmt->b_dont_play = TRUE;
        return MMPR_IS_STOPPED;
    }
#endif

    switch (pt_elmt->e_elmt_stat)
    {
        case _MMP_VE_ELMT_STAT_INIT:
        case _MMP_VE_ELMT_STAT_WAIT:
        case _MMP_VE_ELMT_STAT_ERROR:
        case _MMP_VE_ELMT_STAT_NOT_SUPPORT:
        case _MMP_VE_ELMT_STAT_READY:
            return MMPR_IS_STOPPED;

        case _MMP_VE_ELMT_STAT_OVER:
        case _MMP_VE_ELMT_STAT_PLAY:
        case _MMP_VE_ELMT_STAT_STOP:
            break;

        default:
            MMP_ASSERT(FALSE);
    }

    #ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    if (_MMP_VE_ELMT_OPER_BLANK == pt_elmt->e_elmt_oper)
    {
        MM_SVC_SBTL_SHOW_HIDE_T t_sbtl_show = { TRUE };
        if (_MMP_VE_SBTL_STAT_OFF != pt_elmt->e_sbtl_stat)
        {
            i4_ret = mmp_ve_sbtl_set_show(pt_this, &t_sbtl_show);
            if (MMPR_OK != i4_ret)
            {
                return i4_ret;
            }
        }
    }
    #endif

    MMP_DBG_INFO(("{MMP} c_svctx_sync_stop_selector_svc %d %s:%d\r\n", pt_elmt->h_elmt_hdl,__FUNCTION__, __LINE__));
    i4_ret = c_svctx_sync_stop_selector_svc(
                    pt_this->h_svctx_hdl,
                    DEFAULT_STOP_SVC_TIMEOUT
                    );
    if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret && SVCTXR_NO_RIGHT != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} \n!!!!c_svctx_stop_selector_svc() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
		#ifdef LINUX_AUTO_TEST
			CREATE_MMP_TMP_FILE(mmp_stop_fail_file);
		#endif
		return MMPR_FAIL;
    }

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    if (_MMP_VE_ELMT_OPER_BLANK == pt_elmt->e_elmt_oper)
    {
        i4_ret = video_engine_blank_hide(pt_this);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif
#ifdef APP_IPCC_SUPPORT
	video_engine_free_ipcc_path(pt_elmt);
#endif
    pt_elmt->b_check_yet = FALSE;
    pt_elmt->e_ctnt_rpt  =  MMP_VE_CTNT_RPT_TYPE_NONE;
    pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_STOP;

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
    pt_elmt->e_ttx_state = MMP_TTX_STATE_NONE;
#endif
    c_memset(&pt_elmt->t_sbtl_comp_id, 0, sizeof(STREAM_COMP_ID_T));
    pt_elmt->ui4_notify_flag = 0;

#ifdef APP_LAST_MEMORY_SUPPORT
    ui2_audio_play_idx    = 0;
    ui2_subtitle_play_idx = 0;
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _video_engine_calc_max_zoom
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
INT32 _video_engine_calc_max_zoom(
                    _MMP_VE_PLAY_INST_PTR_T         pt_this,          /* in  */
                     MMP_VE_ZOOM_TYPE_PTR_T         pt_max_zoom       /* out */
                    )
{
    VSH_REGION_CAPABILITY_INFO_T t_info = {0};
    MMP_VE_ZOOM_TYPE_T e_max_zoom = MMP_VE_ZOOM_TYPE_1X;
    VSH_REGION_INFO_T t_vid_region = {0};
    SIZE_T z_size = 0;
    FLOAT f_divisor = (FLOAT)0.0;
    INT32 i4_ret = 0;

    if(NULL == pt_this || NULL == pt_max_zoom)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    t_info.e_get_type = SM_VSH_GET_TYPE_VIDEO_REGION;
    z_size = sizeof(VSH_REGION_CAPABILITY_INFO_T);

    i4_ret = c_svctx_get_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_REGION_CAPABILITY,
                    &t_info,
                    &z_size
                    );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    MMP_DBG_INFO(("\n"
                  "|--------------------------\n"
                  "| Video Region Capability |\n"
                  "|-------------------------|\n"
                  "| b_is_enable   | %- 5d   |\n"
                  "| ui4_width_min | %- 5d   |\n"
                  "--------------------------|\n"
                  "\n",
                  t_info.b_is_enable,
                  t_info.ui4_width_min));

    MMP_DBG_INFO(("\n"
                  "|--------------------------\n"
                  "| Zoom  |     width       |\n"
                  "|-------------------------|\n"
                  "|   1X  |  7072 |  10000  |\n"
                  "|   2X  |  5000 |   7072  |\n"
                  "|   4X  |  3536 |   5000  |\n"
                  "|   8X  |  2500 |   3536  |\n"
                  "|  16X  |  1768 |   2500  |\n"
                  "|  32X  |  1250 |   1768  |\n"
                  "|  64X  |   884 |   1250  |\n"
                  "| 128X  |   625 |    884  |\n"
                  "| 256X  |   442 |    625  |\n"
                  "| 512X  |   312 |    442  |\n"
                  "--------------------------|\n"
                  "\n"));

#if 0 /* To fix DTV00083254 */
    if(TRUE != t_info.b_is_enable)
    {
        *pt_max_zoom = MMP_VE_ZOOM_TYPE_1X;
        return MMPR_OK;
    }
#endif

    for(e_max_zoom  = MMP_VE_ZOOM_TYPE_1X;
        e_max_zoom <= MMP_VE_ZOOM_TYPE_512X;
        e_max_zoom++)
    {
        if(0 == (e_max_zoom % 2))
        {
            f_divisor = (1 << (e_max_zoom / 2)) * 1.000;
        }
        else
        {
            f_divisor = (1 << (e_max_zoom / 2)) * 1.414;
        }

        t_vid_region.ui4_width  = (UINT32)(VSH_REGION_MAX_WIDTH  / f_divisor);
        t_vid_region.ui4_height = (UINT32)(VSH_REGION_MAX_HEIGHT / f_divisor);

        if((t_info.ui4_width_min  > t_vid_region.ui4_width) ||
           (t_info.ui4_height_min > t_vid_region.ui4_height))
        {
            *pt_max_zoom = (MMP_VE_ZOOM_TYPE_T)((UINT16)e_max_zoom - 1);
            return MMPR_OK;
        }
    }

    *pt_max_zoom = MMP_VE_ZOOM_TYPE_512X;
    return MMPR_OK;
}

INT32 video_engine_get_resolution(MMP_VE_PLAY_INST_PTR_T pt_play_inst, UINT32* pt_u4_width, UINT32* pt_u4_height)
{
    SIZE_T t_size = sizeof(MM_VIDEO_INFO_T);
    MM_VIDEO_INFO_T t_video_info_rec = {0};
    INT32 i4_ret = 0;
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    i4_ret = c_svctx_get(
        pt_this->h_svctx_hdl,
        SVCTX_MM_GET_TYPE_VIDEO_INFO,
        (VOID*)&t_video_info_rec,
        &t_size
        );
    MMPR_LOG_ON_FAIL(i4_ret);

    *pt_u4_width = t_video_info_rec.ui4_width;
    *pt_u4_height = t_video_info_rec.ui4_height;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * video engine static functions implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * video engine export methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: video_engine_create
 *
 * Description: This API is used to open a c_svctx instance, and to register
 *              a notification function to this video engine.
 *
 * Inputs:  pf_nfy             References the engine notification function.
 *
 * Outputs: ppv_engine_inst    Contains a pointer to the engine instance.
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_create(
                    mmp_ve_play_nfy_fct             pf_play_nfy,      /* in  */
                    MMP_VE_PLAY_INST_PTR_T*         ppt_play_inst     /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_play_inst = NULL;
    HANDLE_T h_svctx_hdl = NULL_HANDLE;
    SCC_DISP_RESOLUTION_T t_resolution = {0};
    _MMP_VE_INST_ID_T i = 0;
    INT32 i4_ret = 0;

    MMP_ASSERT(NULL != pf_play_nfy && NULL != ppt_play_inst);

    pt_play_inst = c_mem_alloc(sizeof(_MMP_VE_PLAY_INST_T));
    if(NULL == pt_play_inst)
    {
        MMP_DBG_INFO(("{MMP} c_mem_alloc() returns NUL  %s:%d \r\n", __FUNCTION__, __LINE__));
        return MMPR_OUT_OF_MEM;
    }

    c_memset(pt_play_inst, 0, sizeof(_MMP_VE_PLAY_INST_T));

    for(i = 0; i < _MMP_VE_ELMT_ID_NUM; i++)
    {
        VIDEO_ENGINE_ELMT_RESET(pt_play_inst->at_elmt_info[i]);
    }

    for(i = 0; i < _MMP_VERC_INFO_INST_NUM; i++)
    {
        VIDEO_ENGINE_INFO_RESET(pt_play_inst->at_info_inst[i]);
    }

    do
    {
        /* init c_svctx instance */
        i4_ret = c_svctx_open(VIDEO_CSVCTX_NAME, &h_svctx_hdl);
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_open() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        i4_ret = c_svctx_generic_set_info(
                            h_svctx_hdl, NULL_HANDLE,
                            SVCTX_MM_SBTL_SET_TYPE_DEFAULT,
                            NULL, (SIZE_T)0
                            );
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_generic_set_info() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        }

        pt_play_inst->h_svctx_hdl = h_svctx_hdl;

#if 0
        i4_ret = c_scc_disp_get_resolution(
                        h_g_acfg_scc_main_disp,
                        &t_resolution
                        );
        if(SMR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_scc_disp_get_resolution() %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }
#endif

        mmp_drc_get_panel_size(&t_resolution.ui2_width, &t_resolution.ui2_height);

        pt_play_inst->t_osd_info.h_canvas_ex  = mmp_main_get_canvas();
        pt_play_inst->t_osd_info.ui2_screen_w = t_resolution.ui2_width;
        pt_play_inst->t_osd_info.ui2_screen_h = t_resolution.ui2_height;

        pt_play_inst->t_file_id_counter = (_MMP_VE_FILE_ID_T)0;   /* file id dispatch */

        pt_play_inst->pf_play_nfy_fct = pf_play_nfy;
#ifdef APP_NETWORK_SUPPORT
        pt_play_inst->pf_get_media_info_fct = _MMP_VERC_GET_MEDIA_INFO_FCT();
#endif
        pt_play_inst->t_inst_id      = 0xFFFF;

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
        i4_ret = video_engine_blank_init(pt_play_inst);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#endif

        i4_ret = _mmp_ve_play_inst_insert(pt_play_inst);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        *ppt_play_inst = (MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

        return MMPR_OK;

    }while(0);

    i4_ret = video_engine_destroy((MMP_VE_PLAY_INST_PTR_T)pt_play_inst);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} video_engine_destroy() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        MMP_ASSERT(FALSE);
    }

    return MMPR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_destroy
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
INT32 video_engine_destroy(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret = 0;

    MMP_ASSERT(NULL != pt_this);

    i4_ret = video_engine_close(pt_play_inst);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} video_engine_close() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        MMP_ASSERT(FALSE);
    }

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    i4_ret = video_engine_blank_deinit(pt_this);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} video_engine_blank_deinit() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        MMP_ASSERT(FALSE);
    }
#endif

    if (NULL_HANDLE != pt_this->h_svctx_hdl)
    {
        i4_ret = c_svctx_close(pt_this->h_svctx_hdl);
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_close() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            MMP_ASSERT(FALSE);
        }
        pt_this->h_svctx_hdl = NULL_HANDLE;
    }

    if (NULL != pt_this->pv_drc_snapshot)
    {
        mmp_drc_snapshot_free(pt_this->pv_drc_snapshot);
        pt_this->pv_drc_snapshot = NULL;
    }

    i4_ret = _mmp_ve_play_inst_remove(pt_this);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} _mmp_ve_play_inst_remove() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        MMP_ASSERT(FALSE);
    }

    c_mem_free(pt_this);
    pt_this = NULL;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_attr_set
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
INT32 video_engine_attr_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT32                          ui4_attr_size,    /* in  */
                    const MMP_FP_SHOW_ATTR_T        at_show_attr[]      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = NULL;
    UINT32 i = 0;

    MMP_ASSERT(NULL != pt_this);

    pt_elmt = &pt_this->at_elmt_info[_MMP_VE_ELMT_ID_1ST];

    c_memset(&pt_elmt->t_spd_attr, 0, sizeof(MMP_FP_SHOW_ATTR_T));
    c_memset(&pt_elmt->t_rpt_attr, 0, sizeof(MMP_FP_SHOW_ATTR_T));

    for(i = 0; i < ui4_attr_size; i++)
    {
        if(MMP_FP_SHOW_ATTR_ID_SPEED == at_show_attr[i].e_id)
        {
            pt_elmt->t_spd_attr = at_show_attr[i];
        }
        else if(MMP_FP_SHOW_ATTR_ID_REPEAT == at_show_attr[i].e_id)
        {
            pt_elmt->t_rpt_attr = at_show_attr[i];
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_next_attr_set
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
INT32 video_engine_next_attr_set(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT32                          ui4_attr_size,    /* in  */
                    const MMP_FP_SHOW_ATTR_T        at_show_attr[]    /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = NULL;
    UINT32 i = 0;

    MMP_ASSERT(NULL != pt_this);

    pt_elmt = &pt_this->at_elmt_info[_MMP_VE_ELMT_ID_2ND];

    c_memset(&pt_elmt->t_spd_attr, 0, sizeof(MMP_FP_SHOW_ATTR_T));
    c_memset(&pt_elmt->t_rpt_attr, 0, sizeof(MMP_FP_SHOW_ATTR_T));

    for(i = 0; i < ui4_attr_size; ++i)
    {
        if(MMP_FP_SHOW_ATTR_ID_SPEED == at_show_attr[i].e_id)
        {
            pt_elmt->t_spd_attr = at_show_attr[i];
        }
        else if(MMP_FP_SHOW_ATTR_ID_REPEAT == at_show_attr[i].e_id)
        {
            pt_elmt->t_rpt_attr = at_show_attr[i];
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_open
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
INT32 video_engine_open(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const CHAR*                     ps_file_name      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    MMP_FILE_SRC_TYPE_T e_file_src_type;
    INT32 i4_ret;

    if(NULL == pt_this || NULL == ps_file_name)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    VIDEO_ENGINE_ELMT_RESET(*pt_elmt);

    pt_this->e_play_stat = MMP_VE_PLAY_STAT_OPEN;

    /* Get source type according to file name */
    i4_ret = mmp_util_get_file_src_type(ps_file_name, &e_file_src_type);
    if(MMPR_OK != i4_ret)
    {
        e_file_src_type = MMP_FILE_SRC_MASS_STRG;
    }

    pt_elmt->ps_file_name = ps_file_name;
    pt_elmt->t_file_id = ++pt_this->t_file_id_counter;
    pt_elmt->t_file_src = e_file_src_type;

    i4_ret = _video_engine_elmt_open(pt_this, pt_elmt);
    if(MMPR_OK != i4_ret && MMPR_IS_OPENED != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_next_preload
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
INT32 video_engine_next_preload(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const CHAR*                     ps_file_name      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_2ND_ELMT(pt_this);
    MMP_FILE_SRC_TYPE_T e_file_src_type;
    DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
    INT32 i4_ret;

    if(NULL == pt_this)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    if(NULL == ps_file_name)
    {
        i4_ret = _video_engine_elmt_close(pt_this, pt_elmt);
        if(MMPR_OK != i4_ret && MMPR_IS_CLOSED != i4_ret)
        {
            return i4_ret;
        }

        return MMPR_OK;
    }

    /* Get source type according to file name */
    i4_ret = mmp_util_get_file_src_type(ps_file_name, &e_file_src_type);
    if(MMPR_OK != i4_ret)
    {
        e_file_src_type = MMP_FILE_SRC_MASS_STRG;
    }

    pt_elmt->ps_file_name = ps_file_name;
    pt_elmt->t_file_id = ++pt_this->t_file_id_counter;
    pt_elmt->t_file_src = e_file_src_type;

    MMP_DBG_INFO(("{mmp} preload next file name:%s,file_src_type:%d\n\r",ps_file_name,e_file_src_type));
#ifndef APP_MMP_LOW_MEMORY_SUPPORT
    if ((MMP_FILE_SRC_DLNA == e_file_src_type) ||
        (MMP_FILE_SRC_NET_NEIGHBOR == e_file_src_type)
        #ifdef APP_S_PLATFORM
        || mmp_util_filter_fct_by_ext(ps_file_name,(CHAR*)ag_g_not_preload_file,1)
        #endif
        )
#endif
    {
        MMP_DBG_INFO(("{mmp} not preload next file\n\r"));
        return MMPR_OK;
    }
    DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
    i4_ret = _video_engine_elmt_open(pt_this, pt_elmt);
    if(MMPR_OK != i4_ret && MMPR_IS_OPENED != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_preview_activate
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
INT32 video_engine_preview_activate(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const MMP_FP_PREVIEW_INFO_T*    pt_preview_info
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    GL_RECT_T t_thumb_rect = { 0 }, t_preview_rect = { 0 };
    UINT32 ui4_width, ui4_height;
    INT32 i4_ret;

    t_thumb_rect = pt_preview_info->t_thumb_rect;
    mmp_drc_convert_rect_coord(pt_preview_info->e_coords, &t_thumb_rect);

    t_preview_rect = pt_preview_info->t_preview_rect;
    mmp_drc_convert_rect_coord(pt_preview_info->e_coords, &t_preview_rect);

    /*Check if there is snapshot*/
    if (NULL != pt_this->pv_drc_snapshot)
    {
        i4_ret = mmp_drc_snapshot_get_size(pt_this->pv_drc_snapshot, &ui4_width, &ui4_height);
        if (MMPR_OK != i4_ret ||
            RECT_W(&t_thumb_rect) != ui4_width ||
            RECT_H(&t_thumb_rect) != ui4_height)
        {
            mmp_drc_snapshot_free(pt_this->pv_drc_snapshot);
            pt_this->pv_drc_snapshot = NULL;
        }
    }

    /*Create snapshot if needed*/
    if (NULL == pt_this->pv_drc_snapshot && FALSE == RECT_EMPTY(&t_thumb_rect))
    {
        i4_ret = mmp_drc_snapshot_create(RECT_W(&t_thumb_rect),
                                         RECT_H(&t_thumb_rect),
                                         &pt_this->pv_drc_snapshot);
        if (MMPR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }
    }

    /*Save the snapshot*/
    if (FALSE == RECT_EMPTY(&t_thumb_rect))
    {
        mmp_drc_snapshot_save(pt_this->pv_drc_snapshot, NULL, &t_thumb_rect, TRUE);
    }

    pt_this->t_snapshot_rect = t_thumb_rect;
    pt_this->t_preview_rect = t_preview_rect;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_preview_inactivate
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
INT32 video_engine_preview_inactivate(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    /*Load the snapshot*/
    if (NULL != pt_this->pv_drc_snapshot)
    {
        mmp_drc_snapshot_load(
                    pt_this->pv_drc_snapshot,
                    NULL,
                    &pt_this->t_snapshot_rect
                    );
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_play
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
INT32 video_engine_play(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    if(NULL == pt_this)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    switch(pt_this->e_play_stat)
    {
        case MMP_VE_PLAY_STAT_PLAY:
            if(_MMP_VE_ELMT_STAT_OVER == pt_elmt->e_elmt_stat)
            {
                i4_ret = _video_engine_start2play(pt_this, pt_divx_cert);
            }
            else
            {
                i4_ret = MMPR_IS_PLAYED;
            }
            break;

        case MMP_VE_PLAY_STAT_PAUSE:
        case MMP_VE_PLAY_STAT_BLANK:
        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        case MMP_VE_PLAY_STAT_SLOW_FWD:
        case MMP_VE_PLAY_STAT_SLOW_RWD:
            i4_ret = _video_engine_trick2play(pt_this);
            break;

        case MMP_VE_PLAY_STAT_OPEN:
        case MMP_VE_PLAY_STAT_NEXT:
        case MMP_VE_PLAY_STAT_STOP:
            i4_ret = _video_engine_start2play(pt_this, pt_divx_cert);
            break;

        default:
            i4_ret = MMPR_OK;
            break;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_next
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
INT32 video_engine_next(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_2nd = _MMP_VE_GET_2ND_ELMT(pt_this);
    INT32  i4_ret = 0;

    if(NULL == pt_this || NULL == pt_elmt_1st || NULL == pt_elmt_2nd)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

#ifdef APP_LAST_MEMORY_SUPPORT
    i4_ret = mmp_ve_stop_info_get_ex(pt_this, pt_elmt_1st);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}mmp_ve_stop_info_get_ex %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        /*It is not matter to return when fail*/
    }
#endif
#if 0
    i4_ret = _video_engine_full_stop(pt_this);
    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}_video_engine_full_stop %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    i4_ret = _video_engine_elmt_close(pt_this, pt_elmt_1st);
    if(MMPR_OK != i4_ret && MMPR_IS_CLOSED != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_close_elm %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }
	MMP_DBG_INFO(("{mmp} next file name:%s,next file src:%d\n\r",pt_elmt_2nd->ps_file_name,pt_elmt_2nd->t_file_src));
    /* DLNA will not preload */
#ifndef APP_MMP_LOW_MEMORY_SUPPORT
    if((MMP_FILE_SRC_DLNA == pt_elmt_2nd->t_file_src) ||
       (MMP_FILE_SRC_NET_NEIGHBOR == pt_elmt_2nd->t_file_src)
       #ifdef APP_S_PLATFORM
        || mmp_util_filter_fct_by_ext(pt_elmt_2nd->ps_file_name,(CHAR*)ag_g_not_preload_file,1)
       #endif
		)
#endif
    {
    	MMP_DBG_INFO(("{mmp} not preload next file ,media open now\n\r"));
        _video_engine_elmt_open(pt_this, pt_elmt_2nd);
    }
#endif
    pt_this->e_play_stat = MMP_VE_PLAY_STAT_NEXT;

    c_memcpy(pt_elmt_1st, pt_elmt_2nd, sizeof(_MMP_VE_ELMT_INFO_T));
    c_memset(pt_elmt_2nd, 0, sizeof(_MMP_VE_ELMT_INFO_T));

    i4_ret = _video_engine_start2play(pt_this, pt_divx_cert);
    if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}_video_engine_start2play %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_pause
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
INT32 video_engine_pause(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    DBG_LOG_PRINT(("**   *** %s,%d\r\n",__FUNCTION__,__LINE__));

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_play_pause(&gp_v_splayer,FALSE);
        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_play_pause() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
            return i4_ret;
        }

        pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_PAUSE;
        pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PAUSE;

        return MMPR_IS_PAUSED;
    }

    return i4_ret;
}
#ifdef NEVER

/*----------------------------------------------------------------------------
 * Name: video_engine_pause
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
INT32 video_engine_pause(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;
    MM_SPEED_TYPE_T e_speed = MM_SPEED_TYPE_PAUSE;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(video_engine_trick_enable_ex(pt_play_inst, &e_speed) == FALSE)
    {
        MMP_DBG_INFO(("{MMP} %s[%d] pause not support\r\n",__FUNCTION__,__LINE__));
        return MMPR_RES_NOT_READY;
    }

    i4_ret = _video_engine_set_trick(pt_this, MM_SPEED_TYPE_PAUSE);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}_video_engine_set_trick %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_PAUSE;
    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PAUSE;

    return MMPR_IS_PAUSED;
}
#endif /* NEVER */

/*----------------------------------------------------------------------------
 * Name: video_engine_blank
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
INT32 video_engine_blank(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    MM_SVC_SBTL_SHOW_HIDE_T t_sbtl_hide = { FALSE };
    INT32 i4_ret = 0;
    MM_SPEED_TYPE_T e_speed = 0;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if (_MMP_VE_ELMT_OPER_SEEK == pt_elmt->e_elmt_oper)
    {
        return MMPR_RES_NOT_READY;
    }
    e_speed = MM_SPEED_TYPE_PAUSE;

    if(video_engine_trick_enable_ex(pt_play_inst, &e_speed) == FALSE)
    {
        MMP_DBG_INFO(("{MMP} %s[%d] pause not support\r\n",__FUNCTION__,__LINE__));
        return MMPR_RES_NOT_READY;
    }
    if (MMP_VE_PLAY_STAT_PAUSE != pt_this->e_play_stat)
    {
        i4_ret = _video_engine_set_trick(pt_this, MM_SPEED_TYPE_PAUSE);
        MMPR_LOG_ON_FAIL(i4_ret);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    if (_MMP_VE_SBTL_STAT_OFF != pt_elmt->e_sbtl_stat)
    {
        i4_ret = mmp_ve_sbtl_set_show(pt_this, &t_sbtl_hide);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    i4_ret = video_engine_blank_show(pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_BLANK;
    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_BLANK;

    return MMPR_IS_PAUSED;
#else
    return MMPR_NOT_SUPPORT;
#endif
}

/*----------------------------------------------------------------------------
 * Name: video_engine_fast_forward
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
INT32 video_engine_fast_forward(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_FAST_FWD_TYPE_T          e_ffwd_type       /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    if (_MMP_VE_ELMT_OPER_BLANK == pt_elmt->e_elmt_oper)
    {
        i4_ret = video_engine_blank_hide(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif

    i4_ret = _video_engine_set_trick(pt_this, (MM_SPEED_TYPE_T)e_ffwd_type);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_FFWD;
    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_FAST_FWD;

    return MMPR_IS_FAST_FORWARDED;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_fast_rewind
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
INT32 video_engine_fast_rewind(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_FAST_RWD_TYPE_T          e_frwd_type       /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    if (_MMP_VE_ELMT_OPER_BLANK == pt_elmt->e_elmt_oper)
    {
        i4_ret = video_engine_blank_hide(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif

    i4_ret = _video_engine_set_trick(pt_this, (MM_SPEED_TYPE_T)e_frwd_type);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_FRWD;
    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_FAST_RWD;

    return MMPR_IS_FAST_REWINDED;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_slow_forward
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
INT32 video_engine_slow_forward(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SLOW_FWD_TYPE_T          e_slow_fwd_type   /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    if (_MMP_VE_ELMT_OPER_BLANK == pt_elmt->e_elmt_oper)
    {
        i4_ret = video_engine_blank_hide(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);
        if (MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif

    i4_ret = _video_engine_set_trick(pt_this, (MM_SPEED_TYPE_T)e_slow_fwd_type);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_SFWD;
    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_SLOW_FWD;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_slow_rewind
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
INT32 video_engine_slow_rewind(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_SLOW_RWD_TYPE_T          e_slow_rwd_type   /* in  */
                    )
{
#if 0
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret = 0;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

#ifdef _MMP_VERC_PLAY_BLANK_SUPPORT
    if (_MMP_VE_ELMT_OPER_BLANK == pt_elmt->e_elmt_oper)
    {
        i4_ret = video_engine_blank_hide(pt_this);
        if (MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("video_engine_blank_hide() returns %d\n", i4_ret));
            return i4_ret;
        }
    }
#endif

    i4_ret = _video_engine_set_trick(pt_this, (MM_SPEED_TYPE_T)e_slow_rwd_type);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_SRWD;
    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_SLOW_RWD;

    return MMPR_OK_________;
#else
    return MMPR_NOT_SUPPORT;
#endif
}

/*----------------------------------------------------------------------------
 * Name: video_engine_step
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
INT32 video_engine_step(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret = 0;

    MMP_ASSERT(NULL != pt_this);

    i4_ret = _video_engine_set_trick(pt_this, MM_SPEED_TYPE_STEP);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_stop
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
INT32 video_engine_stop(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret;

    if(NULL == pt_this)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    i4_ret = _video_engine_full_stop(pt_this);
    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        return i4_ret;
    }

    pt_this->e_play_stat =  MMP_VE_PLAY_STAT_STOP;

    return MMPR_IS_STOPPED;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_stop_lyric
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
INT32 video_engine_stop_lyric(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret;

    if(NULL == pt_this)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    i4_ret = c_svctx_stop_stream(
                    pt_this->h_svctx_hdl,
                    ST_SUBTITLE
                    );
    MMPR_LOG_ON_FAIL(i4_ret);
    if (SVCTXR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_close_elm
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
INT32 video_engine_close(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    VSH_REGION_INFO_T t_adj_dsp_region = {0};
    SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
#if defined(_MMP_VERC_PLAY_THUMB_SUPPORT) || defined(APP_LAST_MEMORY_SUPPORT)
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
#endif
    _MMP_VE_ELMT_ID_T i = 0;
    MMP_FP_PRESENT_MODE_T t_present_mode;
    INT32 i4_ret;

    if (NULL == pt_this)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }
#if defined(_MMP_VERC_PLAY_THUMB_SUPPORT) || defined(APP_LAST_MEMORY_SUPPORT)
    if(NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }
#endif

    /* reset display region to full screen */
    t_adj_dsp_region.ui4_x = t_adj_dsp_region.ui4_y = 0;
    t_adj_dsp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_adj_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    i4_ret = c_svctx_set_stream_attr(
                pt_this->h_svctx_hdl,
                ST_VIDEO,
                SM_VSH_SET_TYPE_DISP_REGION,
                (VOID*)&t_adj_dsp_region,
                z_size
                );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_set_stream_attr %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
    if (MMPR_OK != i4_ret)
    {
        t_present_mode = MMP_FP_PRESENT_MODE_FULL;
    }

#ifdef APP_LAST_MEMORY_SUPPORT
    i4_ret = mmp_ve_stop_info_get_ex(pt_this, pt_elmt);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}mmp_ve_stop_info_get_ex %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        /*It is not matter to return when fail*/
    }
#endif

#ifdef _MMP_VERC_PLAY_THUMB_SUPPORT
    if(_MMP_VE_ELMT_STAT_THUMB == pt_elmt->e_elmt_stat)
    {
        i4_ret = video_engine_thumb_full_stop(pt_this);
    }
    else
    {
        i4_ret = _video_engine_full_stop(pt_this);
    }
#else
    i4_ret = _video_engine_full_stop(pt_this);
#endif
    
#ifdef NEVER
    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        return i4_ret;
    }
#endif /* NEVER */

    for(i = 0; i < _MMP_VE_ELMT_ID_NUM; i++)
    {
        _video_engine_elmt_close(pt_this, &pt_this->at_elmt_info[i]);
    }

    pt_this->e_play_stat = MMP_VE_PLAY_STAT_CLOSE;

    return MMPR_OK;
}

BOOL video_engine_trick_enable_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
                    MM_SPEED_TYPE_T*                pe_speed
                    )
{
    return TRUE;
#if NEVER
#ifdef ENABLE_MULTIMEDIA
    _MMP_VE_PLAY_INST_PTR_T     pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T     pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32                       i4_ret;
    SM_SESS_GNRC_UOP_CAP_INFO_T t_cap_info;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return FALSE;
    }

    c_memset(&t_cap_info, 0, sizeof(SM_SESS_GNRC_UOP_CAP_INFO_T));

    if (pt_elmt->e_ctnt_rpt == MMP_VE_CTNT_RPT_TYPE_PT_B)
    {
		 if (pe_speed &&
		 	((*pe_speed != MM_SPEED_TYPE_FORWARD_1X) &&
             (*pe_speed != MM_SPEED_TYPE_PAUSE)))
		 {
			MMP_DBG_INFO(("{MMP} disable trick when doing repeat!\n"));
			return FALSE;
		 }
    }

    t_cap_info.e_uop = _SM_SESS_GNRC_UOP_TRICK;
    if (pe_speed)
    {
        t_cap_info.u.t_speed = *pe_speed;
    }

    i4_ret = c_svctx_media_get_info(
                pt_this->h_svctx_hdl,
                pt_elmt->h_elmt_hdl,
                SVCTX_MM_GET_TYPE_UOP_CAP_INFO,
                (VOID*)&t_cap_info,
                sizeof(SM_SESS_GNRC_UOP_CAP_INFO_T)
                );
    if ((SVCTXR_OK != i4_ret) || (!t_cap_info.b_is_allowed))
    {
        MMP_DBG_INFO(("{MMP} uop trick allow ret%d  %d\n", i4_ret, t_cap_info.b_is_allowed));
        return FALSE;
    }

    return TRUE;
#endif

    return FALSE;
#endif
}


/*----------------------------------------------------------------------------
 * Name: video_engine_trick_enable
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: TRUE               Trick mode is supported.
 *          Otherwise          Trick mode is invalid.
 ----------------------------------------------------------------------------*/
BOOL video_engine_trick_enable(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
	return video_engine_trick_enable_ex(pt_play_inst, NULL);
}

/*----------------------------------------------------------------------------
 * Name: video_engine_seek_enable
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: TRUE               Time seek is supported.
 *          Otherwise          Time seek is invalid.
 ----------------------------------------------------------------------------*/
BOOL video_engine_seek_enable(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    DBG_LOG_PRINT(("enter  %s,%d\r\n",__FUNCTION__,__LINE__));

#ifdef NEVER
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    SM_SESS_GNRC_UOP_CAP_INFO_T t_cap_info;
    INT32 i4_ret = MMPR_OK;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return FALSE;
    }

    c_memset(&t_cap_info, 0, sizeof(SM_SESS_GNRC_UOP_CAP_INFO_T));

    t_cap_info.e_uop = _SM_SESS_GNRC_UOP_SEEK;
#ifdef ENABLE_MULTIMEDIA
    i4_ret = c_svctx_media_get_info(
                pt_this->h_svctx_hdl,
                pt_elmt->h_elmt_hdl,
                SVCTX_MM_GET_TYPE_UOP_CAP_INFO,
                (VOID*)&t_cap_info,
                sizeof(SM_SESS_GNRC_UOP_CAP_INFO_T)
                );
    if ((SVCTXR_OK != i4_ret) || (!t_cap_info.b_is_allowed))
    {
		return FALSE;
    }
#else
    return FALSE;
#endif

#ifdef APP_NET_DLNA_SUPPORT
    if (FALSE == mmp_util_dlna_is_seek_supported((CHAR*)pt_elmt->ps_file_name))
    {
    		return FALSE;
    }
#endif
    if (pt_elmt->e_ctnt_rpt == MMP_VE_CTNT_RPT_TYPE_PT_B)
    {
		MMP_DBG_INFO(("{MMP} disable seek when doing repeat!\n"));
		return FALSE;
    }
#endif /* NEVER */
    return TRUE;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_seek
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
INT32 video_engine_seek(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT32                          ui4_time_ofs      /* in  */
                    )

{    
    INT32 i4_ret= MMPR_FAIL;
    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_set_seek(&gp_v_splayer,ui4_time_ofs*1000);
        
        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_set_seek() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
        }
    }

    return i4_ret;
}

#ifdef NEVER
/*----------------------------------------------------------------------------
 * Name: video_engine_seek
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
INT32 video_engine_seek(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT32                          ui4_time_ofs      /* in  */
                    )
{
    return video_engine_seek_ex(
                    pt_play_inst,
                    MMP_VE_POS_TYPE_TIME,
                    ui4_time_ofs
                    );
}
#endif /* NEVER */

/*----------------------------------------------------------------------------
 * Name: video_engine_seek_ex
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
INT32 video_engine_seek_ex(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_POS_TYPE_T               t_pos_type,       /* in  */
                    UINT32                          ui4_time_ofs      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    MM_SVC_POS_INFO_T t_pos;
    INT32 i4_ret = 0;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(_MMP_VE_ELMT_OPER_SEEK == pt_elmt->e_elmt_oper)
    {
        return MMPR_RES_NOT_READY;
    }

    c_memset(&t_pos, 0, sizeof(MM_SVC_POS_INFO_T));

    if(MMP_VE_POS_TYPE_TIME == t_pos_type)
    {
        t_pos.t_pos_type = MM_SVC_POS_TYPE_ALL_TIME;
    }
    else
    {
        t_pos.t_pos_type = MM_SVC_POS_TYPE_ALL_OFFSET;
    }

    t_pos.ui2_idx = (UINT16)0;
    t_pos.ui8_pos_val = (UINT64)ui4_time_ofs;

#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
    i4_ret = video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_STOP, 0);
#endif

#ifdef ENABLE_MULTIMEDIA
    i4_ret = c_svctx_media_seek(
                    pt_this->h_svctx_hdl,
                    _svctx_media_play_nfy_fct,
                    (VOID*)pt_this,
                    &t_pos
                    );
#else
    i4_ret = SVCTXR_NOT_SUPPORT;
#endif
    if(SVCTXR_OK != i4_ret && SVCTXR_ASYNC_NFY != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_media_seek %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return i4_ret;
    }

    pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_SEEK;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_progress
 *
 * Description: Get loading progress, which is figured as percent value.
 *
 * Inputs:
 *
 * Outputs: pui1_load_prog     Return value is between 0 ~ 100
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_progress(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT8*                          pui1_prog_pct     /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
#ifdef _MMP_VERC_PLAY_THUMB_SUPPORT
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
#endif
    UINT8 ui1_crnt_prog = 0;
    SIZE_T z_size = sizeof(UINT8);
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pui1_prog_pct))
    {
        return MMPR_INV_ARG;
    }

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_CURR_PROCESS_PROGRESS,
                    (VOID*)&ui1_crnt_prog,
                    &z_size
                    );
    MMP_DBG_INFO(("{MMP} ui1_crnt_prog = %d.\n", ui1_crnt_prog));
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

#ifdef _MMP_VERC_PLAY_THUMB_SUPPORT
    if (_MMP_VE_ELMT_STAT_THUMB == pt_elmt->e_elmt_stat)
    {
        ui1_crnt_prog = ui1_crnt_prog / 2;
    }
    else
    {
        ui1_crnt_prog = ui1_crnt_prog / 2 + 50;
    }
#endif

    *pui1_prog_pct = ui1_crnt_prog;

    return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name: video_engine_get_position
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
INT32 video_engine_get_position(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_POS_TYPE_T               t_pos_type,       /* in  */
                    UINT64*                         pui8_pos_val      /* out */
                    )
{
    UINT32 u32MsTime = 0;
    INT32 i4_ret= MMPR_FAIL;
    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_get_av_position(&gp_v_splayer,&u32MsTime);
        
        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_get_av_position() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
        }
    }
    MMP_DBG_INFO(("  u32MsTime: %d,%s,%d\r\n",u32MsTime,__FUNCTION__,__LINE__));

    *pui8_pos_val = u32MsTime/1000;
    
    return MMPR_OK;    
}
#ifdef NEVER

/*----------------------------------------------------------------------------
 * Name: video_engine_get_position
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
INT32 video_engine_get_position(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_POS_TYPE_T               t_pos_type,       /* in  */
                    UINT64*                         pui8_pos_val      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this 	= (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    MM_SVC_TIME_CODE_INFO_T t_tc_info;
    MM_SVC_POS_INFO_T t_pos_info;
    SIZE_T z_size = 0;
    INT32 i4_ret = 0;

	if(NULL == pt_this || NULL == pui8_pos_val || NULL == pt_elmt_1st)
	{
		MMP_ASSERT(FALSE);
		return MMPR_INV_ARG;
	}
	if(pt_elmt_1st == NULL || !(_VIDEO_ENGINE_IS_PLAY_NORMAL(pt_elmt_1st)))
	{
		return MMPR_OK;
	}

    if(MMP_VE_POS_TYPE_TIME == t_pos_type)
    {
        t_tc_info.t_tm_code_type = MM_SVC_TM_CODE_TYPE_ALL;
        t_tc_info.ui2_idx = (UINT16)0;
        t_tc_info.ui8_time = (UINT64)0;

        z_size = sizeof(MM_SVC_TIME_CODE_INFO_T);

        i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_TIME_CODE,
                        (VOID*)&t_tc_info,
                        &z_size
                        );
        MMPR_LOG_ON_FAIL(i4_ret);
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_get %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }

        *pui8_pos_val = (UINT64)t_tc_info.ui8_time;
    }
    else
    {
        t_pos_info.t_pos_type = MM_SVC_POS_TYPE_ALL_OFFSET;
        t_pos_info.ui2_idx = (UINT16)0;
        t_pos_info.ui8_pos_val = (UINT64)0;

        z_size = sizeof(MM_SVC_POS_INFO_T);

        i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_POSIT_INFO,
                        (VOID*)&t_pos_info,
                        &z_size
                        );
        MMPR_LOG_ON_FAIL(i4_ret);
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_get %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }

        *pui8_pos_val = t_pos_info.ui8_pos_val;
    }

    return MMPR_OK;
}
#endif /* NEVER */
/*----------------------------------------------------------------------------
 * Name: video_engine_get_movie_info
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
INT32 video_engine_get_movie_info(APPL_SPLAYER_MOVIE_INFO_T *ptMovieInfo)

{
    INT32 i4_ret = 0;

    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_get_movie_info(&gp_v_splayer,ptMovieInfo);
        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_get_movie_info() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
        }
    }

    DBG_LOG_PRINT(("**  *** %s,%d\r\n",__FUNCTION__,__LINE__));

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_music_info
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
INT32 video_engine_get_music_info(APPL_SPLAYER_MUSIC_INFO_T *ptInfo)

{
    INT32 i4_ret = 0;

    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_get_music_info(&gp_v_splayer,ptInfo);
        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_get_music_info() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
        }
    }

    DBG_LOG_PRINT(("**  *** %s,%d\r\n",__FUNCTION__,__LINE__));

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_duration
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
INT32 video_engine_get_duration(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DUR_TYPE_T               t_dur_type,       /* in  */
                    UINT64*                         pui8_dur_val      /* out */
                    )

{
    UINT32 u32MsTime = 0;
    INT32 i4_ret = 0;
    if(gp_v_splayer != NULL)
    {
        i4_ret = a_appl_splayer_get_av_duration(&gp_v_splayer,&u32MsTime);

        if(i4_ret != MMPR_OK)
        {
            DBG_LOG_PRINT((" a_appl_splayer_get_av_duration() Fait at i4_ret:%d,%s,%d\r\n",i4_ret,__FUNCTION__,__LINE__));
        }
    }
    
    MMP_DBG_INFO(("  u32MsTime: %d,%s,%d\r\n",u32MsTime,__FUNCTION__,__LINE__));

    *pui8_dur_val = u32MsTime/1000;

    return i4_ret;
    
}

#ifdef NEVER

/*----------------------------------------------------------------------------
 * Name: video_engine_get_duration
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
INT32 video_engine_get_duration(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DUR_TYPE_T               t_dur_type,       /* in  */
                    UINT64*                         pui8_dur_val      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    MM_SVC_DUR_INFO_T t_dur;
    SIZE_T z_size = sizeof(MM_SVC_DUR_INFO_T);
    INT32 i4_ret = 0;

    MMP_ASSERT(NULL != pt_this && NULL != pui8_dur_val);

    if(MMP_VE_DUR_TYPE_TIME == t_dur_type)
    {
        t_dur.t_dur_type = MM_SVC_DUR_TYPE_ALL;
    }
    else
    {
        t_dur.t_dur_type = MM_SVC_DUR_TYPE_ALL_OFFSET;
    }

    t_dur.ui2_idx = (UINT16)0;
    t_dur.ui8_duration = (UINT64)0;

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_GET_TYPE_DUR,
                    (VOID*)&t_dur,
                    &z_size
                    );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    *pui8_dur_val = t_dur.ui8_duration;

    return MMPR_OK;
}
#endif /* NEVER */

/*----------------------------------------------------------------------------
 * Name: video_engine_get_lyric_info
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
INT32 video_engine_get_lyric_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SVC_MM_SBTL_LYRIC_INFO_T*       pt_lyric_info      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    SIZE_T z_size = sizeof(SVC_MM_SBTL_LYRIC_INFO_T);
    INT32 i4_ret = 0;
    SVC_MM_SBTL_LYRIC_INFO_T t_lyric_info;

    c_memset(&t_lyric_info,0,sizeof(SVC_MM_SBTL_LYRIC_INFO_T));

    MMP_ASSERT(NULL != pt_this && NULL != pt_lyric_info);

    i4_ret = c_svctx_get(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SBTL_GET_TYPE_LYRIC_INFO,
                    (VOID*)&t_lyric_info,
                    &z_size
                    );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get(SVCTX_MM_SBTL_GET_TYPE_LYRIC_INFO) %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    *pt_lyric_info = t_lyric_info;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_duration
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
INT32 video_engine_get_vid_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_VID_INFO_PTR_T           pt_vid_info       /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    SCDB_REC_T t_scdb_rec = {0};
    VSH_SRC_RESOLUTION_INFO_T t_src_res_info;
    INT32 i4_ret = 0;

    c_memset(&t_src_res_info, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = c_svctx_get_using_scdb_rec(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    &t_scdb_rec
                    );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_using_scdb_rec()  %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        t_scdb_rec.e_rec_type = SCDB_REC_TYPE_UNKNOWN;
    }

    i4_ret = c_svctx_get_video_src_resolution(
                    pt_this->h_svctx_hdl,
                    &t_src_res_info
                    );
    if((SVCTXR_OK != i4_ret) ||
       (0 == t_src_res_info.ui4_width) ||
       (0 == t_src_res_info.ui4_height) ||
       (VSH_SRC_TIMING_NOT_SUPPORT == t_src_res_info.e_timing_type))
    {
        pt_vid_info->e_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;
    }
    else
    {
        pt_vid_info->e_asp_ratio = a_sml_get_src_asp_ratio(&t_src_res_info);
    }

    pt_vid_info->e_rec_type = t_scdb_rec.e_rec_type;
    pt_vid_info->ui4_width = t_src_res_info.ui4_width;
    pt_vid_info->ui4_height = t_src_res_info.ui4_height;
    pt_vid_info->b_is_progressive = t_src_res_info.b_is_progressive;
    pt_vid_info->ui4_frame_rate = t_src_res_info.ui4_frame_rate;

    if (t_src_res_info.b_is_display_aspect_ratio)
    {
        switch (t_src_res_info.e_src_asp_ratio)
        {
            case VSH_SRC_ASPECT_RATIO_4_3:
                pt_vid_info->ui4_width = pt_vid_info->ui4_height * 4 / 3;
                break;

            case VSH_SRC_ASPECT_RATIO_16_9:
                pt_vid_info->ui4_width = pt_vid_info->ui4_height * 16 / 9;
                break;

            case VSH_SRC_ASPECT_RATIO_2_21_1:
                pt_vid_info->ui4_width = pt_vid_info->ui4_height * 2.21;
                break;

            case VSH_SRC_ASPECT_RATIO_USR:
                if ((0 != t_src_res_info.ui4_aspect_ratio_w) &&
                    (0 != t_src_res_info.ui4_aspect_ratio_h))
                {
                    pt_vid_info->ui4_width = pt_vid_info->ui4_height *
                                             t_src_res_info.ui4_aspect_ratio_w /
                                             t_src_res_info.ui4_aspect_ratio_h;
                }
                break;

            default:
                break;
        }
    }
    else
    {
        if ((0 != t_src_res_info.ui4_aspect_ratio_w) &&
            (0 != t_src_res_info.ui4_aspect_ratio_h))
        {
            pt_vid_info->ui4_width = pt_vid_info->ui4_width *
                                     t_src_res_info.ui4_aspect_ratio_w /
                                     t_src_res_info.ui4_aspect_ratio_h;
        }
    }

    switch(pt_vid_info->e_rec_type)
    {
        case SCDB_REC_TYPE_VIDEO_PS:
            pt_vid_info->t_enc_fmt = t_scdb_rec.u.t_video_ps.e_enc;
            break;

        case SCDB_REC_TYPE_VIDEO_AVI:
            pt_vid_info->t_enc_fmt = t_scdb_rec.u.t_video_avi.e_enc;
            break;

        case SCDB_REC_TYPE_VIDEO_MP4:
            pt_vid_info->t_enc_fmt = t_scdb_rec.u.t_video_mp4.e_enc;
            break;

        case SCDB_REC_TYPE_VIDEO_ASF:
            pt_vid_info->t_enc_fmt = t_scdb_rec.u.t_video_asf.e_enc;
            break;

        case SCDB_REC_TYPE_VIDEO_MPEG:
            pt_vid_info->t_enc_fmt = t_scdb_rec.u.t_video_mpeg.e_enc;
            break;

        default:
            pt_vid_info->t_enc_fmt = VID_ENC_UNKNOWN;
            break;
    }

    i4_ret = _video_engine_calc_max_zoom(pt_this, &pt_vid_info->t_max_zoom);
    if(MMPR_OK != i4_ret)
    {
        pt_vid_info->t_max_zoom = MMP_VE_ZOOM_TYPE_1X;
    }

    pt_vid_info->t_idx_zoom = MMP_VE_ZOOM_TYPE_1X;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_drm_info
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
INT32 video_engine_get_drm_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_DIVX_CERT_PTR_T          pt_drm_info       /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    if ((NULL == pt_this) || (NULL == pt_drm_info))
    {
        return MMPR_INV_ARG;
    }

    return _video_engine_divx_cert(pt_this, pt_drm_info);
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_aud_info
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
INT32 video_engine_get_aud_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_AUD_INFO_PTR_T           pt_aud_info       /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    SCDB_REC_T t_scdb_rec = {0};
    STREAM_COMP_ID_T t_comp_id;
    INT32 i4_ret = 0;
    ASH_AUDIO_INFO_T        t_info = {0};

    MMP_ASSERT(NULL != pt_this && NULL != pt_aud_info);

    /* default values */
    c_memset(pt_aud_info, 0, sizeof(MMP_VE_AUD_INFO_T));
    c_memset(&t_info, 0 ,sizeof(ASH_AUDIO_INFO_T));

     /* update audio common info */
    i4_ret = c_svctx_get_using_scdb_rec(
                    pt_this->h_svctx_hdl,
                    ST_AUDIO,
                    &t_scdb_rec
                    );
    if(SVCTXR_OK != i4_ret)
    {
    	i4_ret = c_svctx_get_stream_comp_id(
                pt_this->h_svctx_hdl,
                ST_AUDIO,
                _video_engine_iter_aud,
                pt_aud_info,
                &t_comp_id,
                &t_scdb_rec
                );
	    if(SVCTXR_NOT_EXIST == i4_ret)
	    {
	        MMP_DBG_INFO(("{MMP} c_svctx_get_stream_comp_id() %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
	        return MMPR_OK;
	    }
        MMP_DBG_INFO(("{MMP} c_svctx_get_using_scdb_rec() %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    pt_aud_info->e_rec_type = t_scdb_rec.e_rec_type;

    switch(pt_aud_info->e_rec_type)
    {
        case SCDB_REC_TYPE_AUDIO_PS:
            pt_aud_info->ui4_strm_id = (UINT32)t_scdb_rec.u.t_audio_ps.ui1_stream_id;
            pt_aud_info->ui4_strm_sub_id =(UINT32)t_scdb_rec.u.t_audio_ps.ui1_sub_stream_id;
            pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_ps.e_enc;
            break;

        case SCDB_REC_TYPE_AUDIO_AVI:
            pt_aud_info->ui4_strm_id = t_scdb_rec.u.t_audio_avi.ui4_stream_id;
            pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_avi.e_enc;
            break;

        case SCDB_REC_TYPE_AUDIO_MP4:
            pt_aud_info->ui4_strm_id = t_scdb_rec.u.t_audio_mp4.ui4_stream_id;
            pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_mp4.e_enc;
            break;

        case SCDB_REC_TYPE_AUDIO_ASF:
            pt_aud_info->ui4_strm_id = t_scdb_rec.u.t_audio_asf.ui4_stream_id;
            pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_asf.e_enc;
            break;

        case SCDB_REC_TYPE_AUDIO_MKV:
            pt_aud_info->ui4_strm_id = t_scdb_rec.u.t_audio_mkv.ui4_stream_id;
            pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_mkv.e_enc;
            break;

        case SCDB_REC_TYPE_AUDIO_MPEG:
            pt_aud_info->ui4_strm_id = (UINT32)t_scdb_rec.u.t_audio_mpeg.ui2_pid;
            pt_aud_info->ui4_strm_sub_id = (UINT32)t_scdb_rec.u.t_audio_mpeg.ui1_index;
            pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_mpeg.e_enc;
            break;

        case SCDB_REC_TYPE_AUDIO_ANALOG:
            /*t_aud_info.ui4_strm_id = t_scdb_rec.u.t_audio_analog;*/
            pt_aud_info->ui4_strm_id = (UINT32)250;
            pt_aud_info->t_enc_fmt = AUD_ENC_UNKNOWN;
            break;

        case SCDB_REC_TYPE_AUDIO_DIGITAL:
            /*t_aud_info.ui4_strm_id = t_scdb_rec.u.t_audio_digital;*/
            pt_aud_info->ui4_strm_id = (UINT32)500;
            pt_aud_info->t_enc_fmt = AUD_ENC_UNKNOWN;
            break;

        case SCDB_REC_TYPE_AUDIO_ES:
            pt_aud_info->ui4_strm_id = (UINT32)t_scdb_rec.u.t_audio_es.ui4_stream_id;
            pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_es.e_enc;
            break;

        case SCDB_REC_TYPE_AUDIO_RM:
            pt_aud_info->ui4_strm_id = (UINT32)t_scdb_rec.u.t_audio_rm.ui4_stream_id;
            break;

        case SCDB_REC_TYPE_AUDIO_FLV:
            pt_aud_info->ui4_strm_id = t_scdb_rec.u.t_audio_flv.ui4_stream_id;
            break;

        case SCDB_REC_TYPE_AUDIO_OGG:
            pt_aud_info->ui4_strm_id = t_scdb_rec.u.t_audio_ogg.ui4_stream_id;
            break;

		case SCDB_REC_TYPE_AUDIO_MP3:
			pt_aud_info->t_enc_fmt = t_scdb_rec.u.t_audio_mp3.e_enc;
			break;

        default :
            pt_aud_info->t_enc_fmt = AUD_ENC_UNKNOWN;
            return MMPR_INV_ARG;
    }

    i4_ret = c_svctx_get_stream_comp_id(
                pt_this->h_svctx_hdl,
                ST_AUDIO,
                _video_engine_iter_aud,
                pt_aud_info,
                &t_comp_id,
                &t_scdb_rec
                );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_stream_comp_id() %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_svctx_get_audio_info(
                    pt_this->h_svctx_hdl,
                    &t_info
                    );
    MMPR_LOG_ON_FAIL(i4_ret);
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("%s[%d] c_svctx_get_audio_info return:%d",__FUNCTION__,__LINE__,i4_ret));;
        return MMPR_FAIL;
    }
    pt_aud_info->e_dec_type  = t_info.e_dec_type;
    pt_aud_info->e_aud_fmt   = t_info.e_aud_fmt;
    pt_aud_info->e_channels = t_info.e_channels;
    if(pt_aud_info->e_dec_type == ASH_DECODE_TYPE_AC3 ||
       pt_aud_info->e_dec_type == ASH_DECODE_TYPE_EAC3)
    {
        if(MMP_VE_IS_DUALMONO(pt_aud_info->e_channels))
        {
            pt_aud_info->e_aud_mime_type = MMP_VE_AUD_SUB_TYPE_DUALMONO;
        }
        else if(MMP_VE_IS_MONO(pt_aud_info->e_channels))
        {
            pt_aud_info->e_aud_mime_type = MMP_VE_AUD_SUB_TYPE_MONO;
        }
        else if(MMP_VE_IS_STEREO(pt_aud_info->e_channels))
        {
            pt_aud_info->e_aud_mime_type = MMP_VE_AUD_SUB_TYPE_STEREO;
        }
        else
        {
            pt_aud_info->e_aud_mime_type = MMP_VE_AUD_SUB_TYPE_SURROUND;
        }
    }
#ifndef APP_MMP_PVR_AUDIO_SWITCH_CUST_RULE
    if(pt_aud_info->e_aud_mime_type == MMP_VE_AUD_SUB_TYPE_DUALMONO)
    {
        SCC_AUD_DOWNMIX_MODE_T  e_aud_mode = 0;
        i4_ret = video_engine_get_aud_mode(pt_play_inst,&e_aud_mode);
        if(i4_ret != MMPR_OK)
        {
            MMP_DBG_ERROR(("%s[%d] video_engine_get_aud_mode return:%d\r\n",__FUNCTION__,__LINE__,i4_ret));
        }
        pt_aud_info->e_aud_mode = e_aud_mode;
    }
#endif

    MMP_DBG_INFO(("%s[%d] e_aud_fmt:%d e_dec_type:%d e_channels:%d e_aud_mime_type:%d e_aud_mode:%d\r\n",
                    __FUNCTION__,__LINE__,
                    pt_aud_info->e_aud_fmt,
                    pt_aud_info->e_dec_type,
                    pt_aud_info->e_channels,
                    pt_aud_info->e_aud_mime_type,
                    pt_aud_info->e_aud_mode));

    /* change current audio index */
    if(0 == pt_aud_info->ui2_aud_num)
    {
        pt_aud_info->ui2_sel_idx = 0;
    }

    return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name: video_engine_get_chn_info
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
INT32 video_engine_get_chn_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CHN_INFO_PTR_T           pt_chn_info       /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    ASH_AUDIO_INFO_T t_audio_info;
    INT32 i4_ret = 0;

    MMP_ASSERT(NULL != pt_this && NULL != pt_chn_info);

    /* default values */
    c_memset(pt_chn_info, 0, sizeof(MMP_VE_CHN_INFO_T));
    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    /* update audio channels info */
    i4_ret = c_svctx_get_audio_info(
                    pt_this->h_svctx_hdl,
                    &t_audio_info
                    );
    MMPR_LOG_ON_FAIL(i4_ret);
    if(SVCTXR_OK != i4_ret)
    {
        t_audio_info.e_channels = ASH_CHANNELS_UNKNOWN;
    }

    pt_chn_info->e_chn_type = t_audio_info.e_channels;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_dtl_info
 *
 * Description: Get detail info of the given element.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_dtl_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_ID_T                e_info_id,        /* in  */
                    VOID*                           pv_buf,           /* in/out */
                    SIZE_T*                         pz_buf_len        /* in/out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32 i4_ret;

    if(NULL == pt_this || NULL == pv_buf || NULL == pz_buf_len)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    switch(e_info_id)
    {
        case MMP_VE_INFO_ID_TITLE:
        case MMP_VE_INFO_ID_YEAR:
        case MMP_VE_INFO_ID_DATE:
        case MMP_VE_INFO_ID_GENRE:
        case MMP_VE_INFO_ID_DIRECTOR:
        case MMP_VE_INFO_ID_COPYRIGHT:
        case MMP_VE_INFO_ID_DURATION:
        case MMP_VE_INFO_ID_BITRATE:
        case MMP_VE_INFO_ID_ARTIST:
        case MMP_VE_INFO_ID_ALBUM:
        case MMP_VE_INFO_ID_RESOLUTION:
            i4_ret = video_engine_get_meta_data(
                            pt_this,
                            pt_elmt->h_elmt_hdl,
                            e_info_id,
                            pv_buf,
                            pz_buf_len
                            );
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP}video_engine_get_meta_data %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                return i4_ret;
            }
            break;

        case MMP_VE_INFO_ID_NAME:
        case MMP_VE_INFO_ID_PROTECT:
        case MMP_VE_INFO_ID_CREATE_TIME:
        case MMP_VE_INFO_ID_MODIFY_TIME:
        case MMP_VE_INFO_ID_ACCESS_TIME:
        case MMP_VE_INFO_ID_SIZE:
            i4_ret = video_engine_get_file_data(
                            pt_this,
                            pt_elmt->t_elmt_fid,
                            e_info_id,
                            pv_buf,
                            pz_buf_len
                            );
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP}video_engine_get_file_data %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                return i4_ret;
            }
            break;


        case MMP_VE_INFO_ID_IS_SEEK_SUPPORTED:
        {
            BOOL    b_supported = TRUE;

            if(sizeof(BOOL) > *pz_buf_len)
            {
                return MMPR_BUF_NOT_ENOUGH;
            }

#ifdef APP_NET_DLNA_SUPPORT
            do {
                CHAR*   ps_file_name = NULL;

                if (MEDIA_TYPE_CONTAINER == pt_elmt->t_elmt_fmt.e_media_type &&
                    MEDIA_CONTNR_SUBTYPE_MP4 == pt_elmt->t_elmt_fmt.t_media_subtype.u.e_contnr_subtype)
                {
                    //continue
                }
                else
                {
                    break;
                }

                if(MMP_FID_NULL_REC_IDX == pt_elmt->t_elmt_fid)
                {
                    break;
                }

                i4_ret = mmp_fid_get(pt_elmt->t_elmt_fid, &ps_file_name);
                if (MMPR_OK != i4_ret)
                {
                    break;
                }

                if (FALSE == mmp_util_dlna_is_seek_supported(ps_file_name))
                {
                    b_supported = FALSE;
                }
            } while (0);
#endif
            *(BOOL*)pv_buf = b_supported;
            *pz_buf_len = sizeof(BOOL);
        }
        break;

        default:
            return MMPR_NOT_SUPPORT;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_next_dtl_info
 *
 * Description: Get detail info of the given element.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_next_dtl_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_INFO_ID_T                e_info_id,        /* in  */
                    VOID*                           pv_buf,           /* in/out */
                    SIZE_T*                         pz_buf_len        /* in/out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_2ND_ELMT(pt_this);
    INT32 i4_ret;

    if(NULL == pt_this || NULL == pv_buf || NULL == pz_buf_len)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    if(NULL == pt_elmt)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INTERNAL_ERROR;
    }

    switch(e_info_id)
    {
        case MMP_VE_INFO_ID_NEXT_TITLE:
        case MMP_VE_INFO_ID_NEXT_ARTIST:
            i4_ret = video_engine_get_meta_data(
                            pt_this,
                            pt_elmt->h_elmt_hdl,
                            e_info_id,
                            pv_buf,
                            pz_buf_len
                            );
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_INFO(("{MMP}video_engine_get_meta_data %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                return i4_ret;
            }
            break;
        default:
            return MMPR_NOT_SUPPORT;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_src_type
 *
 * Description: Get src type of the given element.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
INT32 video_engine_get_src_type(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    UINT8                           ui1_idx,          /* in  */
                    MMP_FILE_SRC_TYPE_T*            pt_file_src       /* out*/
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this  = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt;


    if (pt_this == NULL || pt_file_src == NULL)
    {
        return MMPR_INV_ARG;
    }

    if (ui1_idx > _MMP_VE_ELMT_ID_NUM)
    {
        return MMPR_INV_ARG;
    }

    switch(ui1_idx)
    {
    case _MMP_VE_ELMT_ID_1ST:
        pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
        if (pt_elmt != NULL)
        {
            *pt_file_src = pt_elmt->t_file_src;
        }
        else
        {
            return MMPR_FAIL;
        }
        break;
    case _MMP_VE_ELMT_ID_2ND:
        pt_elmt =  _MMP_VE_GET_2ND_ELMT(pt_this);
        if (pt_elmt != NULL)
        {
            *pt_file_src = pt_elmt->t_file_src;
        }
        else
        {
            return MMPR_FAIL;
        }
    default:
        break;
    }

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: video_engine_zoom
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
INT32 video_engine_zoom(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_ZOOM_TYPE_T              e_zoom_type       /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    MMP_VE_ZOOM_TYPE_T t_max_zoom = MMP_VE_ZOOM_TYPE_1X;
    VSH_REGION_INFO_T t_org_vid_region = {0};
    VSH_REGION_INFO_T t_org_dsp_region = {0};
    VSH_REGION_INFO_T t_adj_vid_region = {0};
    VSH_REGION_INFO_T t_adj_dsp_region = {0};
    SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
    FLOAT f_divisor = (FLOAT)0.0;
    INT32 i4_ret = 0;

    MMP_ASSERT(NULL != pt_this);

    i4_ret = _video_engine_calc_max_zoom(pt_this, &t_max_zoom);
    if(MMPR_OK != i4_ret)
    {
        t_max_zoom = MMP_VE_ZOOM_TYPE_1X;
    }

    if(t_max_zoom < e_zoom_type)
    {
        return MMPR_NOT_SUPPORT;
    }

    if((TRUE == _MMP_VERC_CHECK_ZOOM_FROM_SML()) &&
       (TRUE != a_sml_is_zoom_enable()))
    {
        return MMPR_NOT_SUPPORT;
    }
    i4_ret = c_svctx_get_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_VIDEO_REGION,
                    (VOID*)&t_org_vid_region,
                    &z_size
                    );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_svctx_get_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_DISP_REGION,
                    (VOID*)&t_org_dsp_region,
                    &z_size
                    );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    t_adj_dsp_region.ui4_x = t_adj_dsp_region.ui4_y = 0;
    t_adj_dsp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_adj_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    if(0 == (e_zoom_type % 2))
    {
        f_divisor = (1 << (e_zoom_type / 2)) * 1.000;
    }
    else
    {
        f_divisor = (1 << (e_zoom_type / 2)) * 1.414;
    }

    t_adj_vid_region.ui4_width  = (VSH_REGION_MAX_WIDTH  / f_divisor);
    t_adj_vid_region.ui4_height = (VSH_REGION_MAX_HEIGHT / f_divisor);
    t_adj_vid_region.ui4_x = (VSH_REGION_MAX_WIDTH  - t_adj_vid_region.ui4_width ) >> 1;
    t_adj_vid_region.ui4_y = (VSH_REGION_MAX_HEIGHT - t_adj_vid_region.ui4_height) >> 1;

    if(c_memcmp(&t_org_vid_region, &t_adj_vid_region, z_size) != 0)
    {
        i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_VIDEO_REGION,
                    (VOID*)&t_adj_vid_region,
                    z_size
                    );
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }
    }

    if(c_memcmp(&t_org_dsp_region, &t_adj_dsp_region, z_size) != 0)
    {
        i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_DISP_REGION,
                    (VOID*)&t_adj_dsp_region,
                    z_size
                    );
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_zoom_4sm
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
INT32 video_engine_zoom_4sm(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_VID_INFO_PTR_T           pt_vid_info       /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    _MMP_VE_OSD_INFO_PTR_T pt_osd_info = NULL;
    FLOAT f_scr_ratio = (FLOAT)0.0;
    FLOAT f_vid_ratio = (FLOAT)0.0;
    VSH_REGION_INFO_T t_org_vid_region = {0};
    VSH_REGION_INFO_T t_org_dsp_region = {0};
    VSH_REGION_INFO_T t_adj_vid_region = {0};
    VSH_REGION_INFO_T t_adj_dsp_region = {0};
    SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
    INT32 i4_ret = 0;

    if(NULL == pt_this || NULL == pt_vid_info)
    {
        return MMPR_INV_ARG;
    }

#if 0 /* To fix DTV00078761 */
    if(pt_vid_info->t_max_zoom < pt_vid_info->t_idx_zoom)
    {
        return MMPR_INV_ARG;
    }
#endif

    i4_ret = c_svctx_get_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_VIDEO_REGION,
                    (VOID*)&t_org_vid_region,
                    &z_size
                    );
    MMP_DBG_INFO(("{MMP}[x = %d][y = %d][w = %d][h = %d]\n", t_org_vid_region.ui4_x,t_org_vid_region.ui4_y,
                                                             t_org_vid_region.ui4_width,t_org_vid_region.ui4_height));
    MMP_DBG_INFO(("{MMP}[zoom = %d][2^zoom please]\n", pt_vid_info->t_idx_zoom));

    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_svctx_get_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_DISP_REGION,
                    (VOID*)&t_org_dsp_region,
                    &z_size
                    );

    MMP_DBG_INFO(("[mmp][x = %d][y = %d][w = %d][h = %d]\n", t_org_dsp_region.ui4_x, t_org_dsp_region.ui4_y,
                                                             t_org_dsp_region.ui4_width,t_org_dsp_region.ui4_height));
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    pt_osd_info = &pt_this->t_osd_info;
    f_scr_ratio = pt_osd_info->ui2_screen_w / (FLOAT)pt_osd_info->ui2_screen_h;
    f_vid_ratio = pt_vid_info->ui4_width / (FLOAT)pt_vid_info->ui4_height;

    MMP_DBG_INFO(("{MMP}[f_scr_ratio = %f] [f_vid_ratio = %f]\n", f_scr_ratio,f_vid_ratio));

    t_adj_vid_region.ui4_x = t_adj_vid_region.ui4_y = 0;
    t_adj_vid_region.ui4_width = VSH_REGION_MAX_WIDTH;
    t_adj_vid_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    t_adj_dsp_region.ui4_width = (pt_vid_info->ui4_width * VSH_REGION_MAX_WIDTH * (1 << (pt_vid_info->t_idx_zoom))) / pt_osd_info->ui2_screen_w;
    t_adj_dsp_region.ui4_height = (pt_vid_info->ui4_height * VSH_REGION_MAX_HEIGHT * (1 << (pt_vid_info->t_idx_zoom))) / pt_osd_info->ui2_screen_h;

    if((VSH_REGION_MAX_WIDTH  < t_adj_dsp_region.ui4_width) ||
       (VSH_REGION_MAX_HEIGHT < t_adj_dsp_region.ui4_height))
    {
        if(f_vid_ratio > f_scr_ratio) /* adjust according to width */
        {
            t_adj_dsp_region.ui4_width = VSH_REGION_MAX_WIDTH;
            t_adj_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT * f_scr_ratio / f_vid_ratio;
        }
        else /* adjust according to height */
        {
            t_adj_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;
            t_adj_dsp_region.ui4_width = VSH_REGION_MAX_WIDTH * f_vid_ratio / f_scr_ratio;
        }
    }

    t_adj_dsp_region.ui4_x = (VSH_REGION_MAX_WIDTH - t_adj_dsp_region.ui4_width) / 2;
    t_adj_dsp_region.ui4_y = (VSH_REGION_MAX_HEIGHT - t_adj_dsp_region.ui4_height) / 2;

    MMP_DBG_INFO(("{MMP}[x = %d][y = %d][w = %d][h = %d]\n", t_adj_vid_region.ui4_x,t_adj_vid_region.ui4_y,
                                                             t_adj_vid_region.ui4_width,t_adj_vid_region.ui4_height));

    if(c_memcmp(&t_org_vid_region, &t_adj_vid_region, z_size) != 0)
    {
        i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_VIDEO_REGION,
                    (VOID*)&t_adj_vid_region,
                    z_size
                    );

        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }

        pt_elmt->t_vid_region = t_adj_vid_region;
    }

    if(c_memcmp(&t_org_dsp_region, &t_adj_dsp_region, z_size) != 0)
    {
        i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_DISP_REGION,
                    (VOID*)&t_adj_dsp_region,
                    z_size
                    );
        MMP_DBG_INFO(("{MMP}[x = %d] [y = %d] [w = %d][h = %d]\n", t_adj_dsp_region.ui4_x,t_adj_dsp_region.ui4_y,
                                                               t_adj_dsp_region.ui4_width,t_adj_dsp_region.ui4_height));
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }

        pt_elmt->t_dsp_region = t_adj_dsp_region;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_zoom_reset
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
INT32 video_engine_zoom_reset(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    VSH_REGION_INFO_T t_adj_vid_region = { 0 };
    SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
    INT32 i4_ret = 0;

    t_adj_vid_region.ui4_x = 0;
    t_adj_vid_region.ui4_y = 0;
    t_adj_vid_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_adj_vid_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    i4_ret = c_svctx_set_stream_attr(
                pt_this->h_svctx_hdl,
                ST_VIDEO,
                SM_VSH_SET_TYPE_VIDEO_REGION,
                (VOID*)&t_adj_vid_region,
                z_size
                );
    MMPR_LOG_ON_FAIL(i4_ret);
    if(MMPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_zoom_reset_4sm
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
INT32 video_engine_zoom_reset_4sm(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    VSH_REGION_INFO_T t_adj_dsp_region = { 0 };
    SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
    INT32 i4_ret = 0;

    t_adj_dsp_region.ui4_x = 0;
    t_adj_dsp_region.ui4_y = 0;
    t_adj_dsp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_adj_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    i4_ret = c_svctx_set_stream_attr(
                pt_this->h_svctx_hdl,
                ST_VIDEO,
                SM_VSH_SET_TYPE_DISP_REGION,
                (VOID*)&t_adj_dsp_region,
                z_size
                );
    MMPR_LOG_ON_FAIL(i4_ret);
    if(MMPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_square_pixel
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
INT32 video_engine_square_pixel(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    VSH_SRC_RESOLUTION_INFO_T t_src_res_info;
    GL_SIZE_T t_panel_size;
    GL_SIZE_T t_video_size;
    VSH_REGION_INFO_T t_disp_region;
    VSH_REGION_INFO_T t_video_region;
    SIZE_T z_size = (SIZE_T)0;
    UINT32 ui4_x;
    UINT32 ui4_y;
    INT32 i4_ret = 0;

    c_memset(&t_src_res_info, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    /* get video size */
    i4_ret = c_svctx_get_video_src_resolution(
                    pt_this->h_svctx_hdl,
                    &t_src_res_info
                    );
    if((SVCTXR_OK != i4_ret) ||
       (0 == t_src_res_info.ui4_width) ||
       (0 == t_src_res_info.ui4_height) ||
       (VSH_SRC_TIMING_NOT_SUPPORT == t_src_res_info.e_timing_type))
    {
        return MMPR_FAIL;
    }

    MMP_DBG_INFO(("{MMP}[%s][Resolution][RET %d][ratio = %d]\n", __FUNCTION__, i4_ret,t_src_res_info.e_src_asp_ratio));
    MMP_DBG_INFO(("{MMP}[Resolution][w = %d] [h = %d]\n", t_src_res_info.ui4_width,t_src_res_info.ui4_height));
    MMP_DBG_INFO(("{MMP}[RATIO_4_3 = %d][RATIO_16_9 = %d] [RATIO_2_21_1 = %d] [RATIO_USR = %d]\n",
                    VSH_SRC_ASPECT_RATIO_4_3,VSH_SRC_ASPECT_RATIO_16_9,VSH_SRC_ASPECT_RATIO_2_21_1,VSH_SRC_ASPECT_RATIO_USR));

    t_video_size.ui4_width  = t_src_res_info.ui4_width;
    t_video_size.ui4_height = t_src_res_info.ui4_height;

    if (t_src_res_info.b_is_display_aspect_ratio)
    {
        switch (t_src_res_info.e_src_asp_ratio)
        {
            case VSH_SRC_ASPECT_RATIO_4_3:
                t_video_size.ui4_width = t_video_size.ui4_height * 4 / 3;
                break;

            case VSH_SRC_ASPECT_RATIO_16_9:
                t_video_size.ui4_width = t_video_size.ui4_height * 16 / 9;
                break;

            case VSH_SRC_ASPECT_RATIO_2_21_1:
                t_video_size.ui4_width = t_video_size.ui4_height * 2.21;
                break;

            case VSH_SRC_ASPECT_RATIO_USR:
                if ((0 != t_src_res_info.ui4_aspect_ratio_w) &&
                    (0 != t_src_res_info.ui4_aspect_ratio_h))
                {
                    t_video_size.ui4_width = t_video_size.ui4_height *
                                             t_src_res_info.ui4_aspect_ratio_w /
                                             t_src_res_info.ui4_aspect_ratio_h;
                }
                break;

            default:
                break;
        }
    }
    else
    {
        if ((0 != t_src_res_info.ui4_aspect_ratio_w) &&
            (0 != t_src_res_info.ui4_aspect_ratio_h))
        {
            t_video_size.ui4_width = t_video_size.ui4_width *
                                     t_src_res_info.ui4_aspect_ratio_w /
                                     t_src_res_info.ui4_aspect_ratio_h;
        }
    }

    /* get panel size */
    t_panel_size.ui4_width  = pt_this->t_osd_info.ui2_screen_w;
    t_panel_size.ui4_height = pt_this->t_osd_info.ui2_screen_h;

    /* set display region */
    ui4_x = (UINT32)((UINT64)t_panel_size.ui4_width * VSH_REGION_MAX_WIDTH / t_panel_size.ui4_height);
    ui4_y = (UINT32)((UINT64)t_video_size.ui4_width * VSH_REGION_MAX_WIDTH / t_video_size.ui4_height);

    t_disp_region.ui4_x = t_disp_region.ui4_y = 0;
    t_disp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_disp_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    if (ui4_x > ui4_y)      /* adjust hor */
    {
        t_disp_region.ui4_width = (UINT32)(((UINT64)t_panel_size.ui4_height * (UINT64)t_video_size.ui4_width * VSH_REGION_MAX_WIDTH) /
                                  ((UINT64)t_video_size.ui4_height * (UINT64)t_panel_size.ui4_width));
        t_disp_region.ui4_x = (VSH_REGION_MAX_WIDTH - t_disp_region.ui4_width) / 2;
    }
    else if (ui4_y > ui4_x) /* adjust ver */
    {
        t_disp_region.ui4_height = (UINT32)(((UINT64)t_panel_size.ui4_width * (UINT64)t_video_size.ui4_height * VSH_REGION_MAX_HEIGHT) /
                                   ((UINT64)t_video_size.ui4_width * (UINT64)t_panel_size.ui4_height));
        t_disp_region.ui4_y = (VSH_REGION_MAX_HEIGHT - t_disp_region.ui4_height) / 2;
    }

    MMP_DBG_INFO(("{MMP}[x = %d, y = %d]\n", ui4_x, ui4_y));

    MMP_DBG_INFO(("{MMP}[panel][h = %d][w = %d]\n", t_panel_size.ui4_height,t_panel_size.ui4_width));
    MMP_DBG_INFO(("{MMP}[video][h = %d][w = %d]\n", t_video_size.ui4_height,t_video_size.ui4_width));

    z_size = sizeof(VSH_REGION_INFO_T);
    i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_DISP_REGION,
                    (VOID*)&t_disp_region,
                    z_size
                    );
    MMP_DBG_INFO(("{MMP}[]disp[x = %d][y = %d][w = %d][h = %d]\n", t_disp_region.ui4_x,t_disp_region.ui4_y,
                                                             t_disp_region.ui4_width,t_disp_region.ui4_height));
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_video_src_resolution() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    /* set video region */
    t_video_region.ui4_x = t_video_region.ui4_y = 0;
    t_video_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_video_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    z_size = sizeof(VSH_REGION_INFO_T);
    i4_ret = c_svctx_set_stream_attr(
                    pt_this->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_VIDEO_REGION,
                    (VOID*)&t_video_region,
                    z_size
                    );
    MMP_DBG_INFO(("{MMP}[video][x = %d][y = %d][w = %d][h = %d]\n", t_video_region.ui4_x,t_video_region.ui4_y,
                                                                    t_video_region.ui4_width,t_video_region.ui4_height));
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_get_video_src_resolution() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_square_pixel_4sm
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
INT32 video_engine_square_pixel_4sm(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_SIZE_T*                pt_video_size     /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T  pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    VSH_REGION_INFO_T t_disp_region;
    VSH_REGION_INFO_T t_video_region;
    SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
    GL_SIZE_T t_panel_size;
    UINT32 ui4_x;
    UINT32 ui4_y;
    INT32 i4_ret = 0;

    if((0 == pt_video_size->ui4_width) || (0 == pt_video_size->ui4_height))
    {
        MMP_DBG_INFO(("{MMP}video_engine_square_pixel %s:%d:\r\n", __FUNCTION__, __LINE__));
        return MMPR_INV_ARG;
    }

    t_panel_size.ui4_width = pt_this->t_osd_info.ui2_screen_w;
    t_panel_size.ui4_height= pt_this->t_osd_info.ui2_screen_h;

    ui4_x = t_panel_size.ui4_width * 1000 / pt_video_size->ui4_width;
    ui4_y = t_panel_size.ui4_height * 1000 / pt_video_size->ui4_height;
    t_video_region.ui4_x = t_video_region.ui4_y = 0;
    t_video_region.ui4_width = VSH_REGION_MAX_WIDTH;
    t_video_region.ui4_height = VSH_REGION_MAX_HEIGHT;
    if (ui4_x >ui4_y)
    {
        /*adjust hor*/
        t_video_region.ui4_width = (t_panel_size.ui4_height*pt_video_size->ui4_width*1000)/
                                   (pt_video_size->ui4_height*t_panel_size.ui4_width);
        t_video_region.ui4_x = (VSH_REGION_MAX_WIDTH - t_video_region.ui4_width)/2;
    }
    else if(ui4_y > ui4_x)
    {
        /*adjust ver*/
        t_video_region.ui4_height= (t_panel_size.ui4_width*pt_video_size->ui4_height*1000)/
                                   (pt_video_size->ui4_width*t_panel_size.ui4_height);
        t_video_region.ui4_y = (VSH_REGION_MAX_HEIGHT- t_video_region.ui4_height)/2;
    }

    t_disp_region.ui4_x = t_disp_region.ui4_y = 0;
    t_disp_region.ui4_width = VSH_REGION_MAX_WIDTH;
    t_disp_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    i4_ret = c_svctx_set_stream_attr(
                pt_this->h_svctx_hdl,
                ST_VIDEO,
                SM_VSH_SET_TYPE_VIDEO_REGION,
                (VOID*)&t_video_region,
                z_size
                );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_svctx_set_stream_attr(
                pt_this->h_svctx_hdl,
                ST_VIDEO,
                SM_VSH_SET_TYPE_DISP_REGION,
                (VOID*)&t_disp_region,
                z_size
                );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_square_pixel_by_overscan_ratio
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
INT32 video_engine_square_pixel_by_overscan_ratio(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    const GL_SIZE_T*                pt_video_size,    /* in  */
                    UINT32                          ui4_ratio_x,      /* in  */ /* ex. 25 = 0.025% */
                    UINT32                          ui4_ratio_y,      /* in  */ /* ex. 25 = 0.025% */
                    BOOL*                           pb_adjusted       /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T  pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    VSH_REGION_INFO_T t_disp_region;
    VSH_REGION_INFO_T t_video_region;
    SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
    GL_SIZE_T t_panel_size;
    UINT32 ui4_x;
    UINT32 ui4_y;
    INT32 i4_ret = 0;

    if ((NULL == pt_this) || (NULL == pt_video_size) || (NULL == pb_adjusted))
    {
        return MMPR_INV_ARG;
    }

    *pb_adjusted = FALSE;

    if ((0 == pt_video_size->ui4_width) || (0 == pt_video_size->ui4_height))
    {
        MMP_DBG_INFO(("{MMP}video_engine_square_pixel() video size invalid%s:%d:\r\n", __FUNCTION__, __LINE__));
        return MMPR_INV_ARG;
    }

    t_panel_size.ui4_width = pt_this->t_osd_info.ui2_screen_w;
    t_panel_size.ui4_height= pt_this->t_osd_info.ui2_screen_h;

    ui4_x = t_panel_size.ui4_width * 1000 / pt_video_size->ui4_width;
    ui4_y = t_panel_size.ui4_height * 1000 / pt_video_size->ui4_height;

    t_disp_region.ui4_x = t_disp_region.ui4_y = 0;
    t_disp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_disp_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    if (ui4_x > ui4_y)
    {
        /*adjust hor*/
        t_disp_region.ui4_width = (UINT32)(((UINT64)t_panel_size.ui4_height * (UINT64)pt_video_size->ui4_width * VSH_REGION_MAX_WIDTH) /
                                  ((UINT64)pt_video_size->ui4_height * (UINT64)t_panel_size.ui4_width));
        t_disp_region.ui4_width = t_disp_region.ui4_width + (t_disp_region.ui4_width * ui4_ratio_x / 1000);

        if (t_disp_region.ui4_width > VSH_REGION_MAX_WIDTH)
        {
            t_disp_region.ui4_width = VSH_REGION_MAX_WIDTH;
        }

        t_disp_region.ui4_x = (VSH_REGION_MAX_WIDTH - t_disp_region.ui4_width) / 2;

        *pb_adjusted = TRUE;
    }
    else if (ui4_y > ui4_x)
    {
        /*adjust ver*/
        t_disp_region.ui4_height = (UINT32)(((UINT64)t_panel_size.ui4_width * (UINT64)pt_video_size->ui4_height * VSH_REGION_MAX_HEIGHT) /
                                   ((UINT64)pt_video_size->ui4_width * (UINT64)t_panel_size.ui4_height));
        t_disp_region.ui4_height = t_disp_region.ui4_height + (t_disp_region.ui4_height * ui4_ratio_y / 1000);

        if (t_disp_region.ui4_height > VSH_REGION_MAX_HEIGHT)
        {
            t_disp_region.ui4_height = VSH_REGION_MAX_HEIGHT;
        }

        t_disp_region.ui4_y = (VSH_REGION_MAX_HEIGHT - t_disp_region.ui4_height) / 2;

        *pb_adjusted = TRUE;
    }

    t_video_region.ui4_x = t_video_region.ui4_y = 0;
    t_video_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_video_region.ui4_height = VSH_REGION_MAX_HEIGHT;

    i4_ret = c_svctx_set_stream_attr(
                pt_this->h_svctx_hdl,
                ST_VIDEO,
                SM_VSH_SET_TYPE_VIDEO_REGION,
                (VOID*)&t_video_region,
                z_size
                );
    if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_svctx_set_stream_attr(
                pt_this->h_svctx_hdl,
                ST_VIDEO,
                SM_VSH_SET_TYPE_DISP_REGION,
                (VOID*)&t_disp_region,
                z_size
                );
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_svctx_set_stream_attr() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_mts
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
INT32 video_engine_mts(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_AUD_INFO_PTR_T           pt_aud_info       /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret = 0;

    if(NULL == pt_this || NULL == pt_aud_info ||
       _MMP_VERC_AUD_MAX_NUM <= pt_aud_info->ui2_sel_idx)
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1st = _MMP_VE_GET_1ST_ELMT(pt_this);
    if(pt_elmt_1st->b_is_media_error)
    {
        MMP_DBG_INFO(("{MMP}Get media error, don't allow change audio  %s:%d\r\n", __FUNCTION__, __LINE__));
        return MMPR_FAIL;
    }
    if(pt_aud_info->at_comp_id[pt_aud_info->ui2_sel_idx].e_type == ST_AUDIO)
    {
        i4_ret = c_svctx_select_stream(
                    pt_this->h_svctx_hdl,
                    &(pt_aud_info->at_comp_id[pt_aud_info->ui2_sel_idx]),
                    NULL,
                    NULL
                    );
        if(SVCTXR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP}c_svctx_select_stream() returns %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
            return MMPR_FAIL;
        }
#ifdef APP_LAST_MEMORY_SUPPORT
        ui2_audio_play_idx = pt_aud_info->ui2_sel_idx;
#endif
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_set_sub_plane
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
INT32 video_engine_set_sub_plane(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    HANDLE_T                        h_sub_plane       /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    if ((NULL == pt_this) || (NULL_HANDLE == h_sub_plane))
    {
        return MMPR_INV_ARG;
    }

    pt_this->t_osd_info.h_sub_plane = h_sub_plane;

    return MMPR_OK;
}

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
MMP_VE_PLAY_STAT_T video_engine_get_state(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst      /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    MMP_ASSERT(NULL != pt_this);

    return pt_this->e_play_stat;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_set_state
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
VOID video_engine_set_state(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_PLAY_STAT_T              e_stat            /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    MMP_ASSERT(NULL != pt_this);

    pt_this->e_play_stat = e_stat;
}


/*----------------------------------------------------------------------------
 * Name: video_engine_set_ctnt_repeat
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
INT32 video_engine_set_ctnt_repeat(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CTNT_RPT_TYPE_T          e_ctnt_rpt        /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);
    MM_SVC_REPEAT_INFO_T    t_ab_repeat_info;
    INT32                   i4_ret;
	SIZE_T                  z_size = 0;
	MM_SVC_TIME_CODE_INFO_T t_time_info;

    if ((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    switch (pt_this->e_play_stat)
    {
        case MMP_VE_PLAY_STAT_OPEN:
        case MMP_VE_PLAY_STAT_NEXT:
        case MMP_VE_PLAY_STAT_BLANK:
        case MMP_VE_PLAY_STAT_STOP:
        case MMP_VE_PLAY_STAT_CLOSE:
            return MMPR_RES_NOT_READY;

        case MMP_VE_PLAY_STAT_PAUSE:
            return MMPR_NOT_SUPPORT;

        default:
            break;
    }
	c_memset(&t_time_info, 0, sizeof(MM_SVC_TIME_CODE_INFO_T));

    t_ab_repeat_info.t_repeat_type = MM_SVC_REPEAT_AB;

    switch (e_ctnt_rpt)
    {
        case MMP_VE_CTNT_RPT_TYPE_PT_A:
            t_ab_repeat_info.u.e_repeat_ab_type = MM_SVC_REPEAT_AB_TYPE_SET_A;
			t_time_info.t_tm_code_type = MM_SVC_TM_CODE_TYPE_ALL;
        	t_time_info.ui2_idx = (UINT16)0;
        	z_size = sizeof(MM_SVC_TIME_CODE_INFO_T);

        	i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_TIME_CODE_MS,
                        (VOID*)&t_time_info,
                        &z_size
                        );
			if (i4_ret == SVCTXR_OK)
			{
				pt_elmt->ui8_time_rptA = t_time_info.ui8_time;
			}
			else
			{
				MMPR_LOG_ON_FAIL(i4_ret);
				pt_elmt->ui8_time_rptA = 0;
			}

            break;

        case MMP_VE_CTNT_RPT_TYPE_PT_B:
            t_ab_repeat_info.u.e_repeat_ab_type = MM_SVC_REPEAT_AB_TYPE_SET_B;

			t_time_info.t_tm_code_type = MM_SVC_TM_CODE_TYPE_ALL;
        	t_time_info.ui2_idx = (UINT16)0;
        	z_size = sizeof(MM_SVC_TIME_CODE_INFO_T);

        	i4_ret = c_svctx_get(
                        pt_this->h_svctx_hdl,
                        SVCTX_MM_GET_TYPE_TIME_CODE_MS,
                        (VOID*)&t_time_info,
                        &z_size
                        );
			if (i4_ret == SVCTXR_OK)
			{
				/*only support AB repeat for more than 1.5S*/
				if (((t_time_info.ui8_time > pt_elmt->ui8_time_rptA) &&
					  (t_time_info.ui8_time-pt_elmt->ui8_time_rptA <= 1500))||
					((t_time_info.ui8_time < pt_elmt->ui8_time_rptA) &&
					 (pt_elmt->ui8_time_rptA-t_time_info.ui8_time <= 1500))
					)
				{
					MMP_DBG_INFO(("{MMP} disable repeat AB < 1500ms\n"));
					return MMPR_WRONG_STATE;
				}
				#ifdef SYS_MMP_TTX_SUBTITLE_SUPPORT
                video_engine_ctrl_ttx(pt_this, MMP_TTX_CMD_STOP, 0);
				#endif
			}
			else
			{
				MMPR_LOG_ON_FAIL(i4_ret);
			}
            break;

        case MMP_VE_CTNT_RPT_TYPE_NONE:
            t_ab_repeat_info.u.e_repeat_ab_type = MM_SVC_REPEAT_AB_TYPE_CANCEL_ALL;
			pt_elmt->ui8_time_rptA = 0;
            break;

        default:
            return MMPR_INV_ARG;
    }

    i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SET_TYPE_REPEAT,
                    (VOID*)&t_ab_repeat_info,
                    sizeof(t_ab_repeat_info)
                    );
    if (SVCTXR_GET_POS_AS_TIME == i4_ret)
    {
        switch (pt_this->e_play_stat)
        {
            case MMP_VE_PLAY_STAT_FAST_FWD:
            case MMP_VE_PLAY_STAT_FAST_RWD:
            case MMP_VE_PLAY_STAT_SLOW_FWD:
            {
                i4_ret = _video_engine_trick2play(pt_this);
                if (MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                {
                    MMP_DBG_INFO(("{MMP} _video_engine_trick2play() %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
                    return i4_ret;
                }
            }
            break;

            default:
                break;
        }
    }
    else if (SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_set() %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));

        if(SVCTXR_NOT_SUPPORT== i4_ret)
        {
            return MMPR_NOT_SUPPORT;
        }
        if(SVCTXR_WRONG_STATE== i4_ret)
        {
            return MMPR_WRONG_STATE;
        }
        return MMPR_FAIL;
    }

    pt_elmt->e_ctnt_rpt = e_ctnt_rpt;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_ctnt_repeat
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
INT32 video_engine_get_ctnt_repeat(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    MMP_VE_CTNT_RPT_TYPE_T*         pe_ctnt_rpt       /* out  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt =  _MMP_VE_GET_1ST_ELMT(pt_this);

    if ((NULL == pt_this) || (NULL == pt_elmt) || (NULL == pe_ctnt_rpt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }

    *pe_ctnt_rpt = pt_elmt->e_ctnt_rpt;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: video_engine_set_screen_mode
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
INT32 video_engine_set_screen_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_VID_SCREEN_MODE_T           e_scr_mode        /* in  */
                    )
{
#if 1 /* Release it after porting to dev */
    INT32 i4_ret;

    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), (INT16)e_scr_mode);
    if(APP_CFGR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    i4_ret = a_cfg_update_screen_mode_ex();
    if(APP_CFGR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
#else
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    MMP_ASSERT(NULL != pt_this);

    return c_svctx_set_screen_mode(pt_this->h_svctx_hdl, e_scr_mode);
#endif
}

/*----------------------------------------------------------------------------
 * Name: video_engine_get_screen_mode
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
INT32 video_engine_get_screen_mode(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    SCC_VID_SCREEN_MODE_T*          pe_scr_mode       /* out */
                    )
{
#if 1 /* Release it after porting to dev */
    INT32 i4_ret;

    if(NULL == pe_scr_mode)
    {
       return MMPR_INV_ARG;
    }

    *pe_scr_mode = SCC_VID_SCREEN_MODE_UNKNOWN;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), (INT16*)pe_scr_mode);
    if(APP_CFGR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
#else
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    MMP_ASSERT(NULL != pt_this);

    return c_svctx_set_screen_mode(pt_this->h_svctx_hdl, e_scr_mode);
#endif
}

/*----------------------------------------------------------------------------
 * Name: video_engine_set_language
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
INT32 video_engine_set_language(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    ISO_639_LANG_T                  e_language        /* in */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    if (NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }

    c_memcpy(pt_this->e_language, e_language, sizeof(ISO_639_LANG_T));

    return MMPR_OK;
}

INT32 video_engine_get_program_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,      /* in  */
                    MMP_VE_PROGRAM_INFO_PTR_T       pt_prog_info)
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    UINT8 ui1_program_num = 0;
    UINT32 i4_ret;

    if(NULL == pt_this || NULL == pt_prog_info)
    {
        return MMPR_INV_ARG;
    }
    i4_ret = c_svctx_media_get_info(
                            pt_this->h_svctx_hdl,
                            pt_elmt->h_elmt_hdl,
                            SVCTX_MM_GET_PROGRAM_NUM,
                            (void*)&ui1_program_num,
                            sizeof(UINT8));
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_media_get_info failed%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }
    pt_prog_info->ui1_program_num = ui1_program_num;
    return MMPR_OK;


}
INT32 video_engine_program_select(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,      /* in  */
                    UINT32                          ui4_prog_idx)     /*  in  */
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);

    SRC_MM_INFO_T t_mm = {0};
    VSH_REGION_INFO_T t_vide_rgn = {0};
    VSH_REGION_INFO_T t_disp_rgn = {0};
    VSH_SET_PLANE_ORDER_INFO_T t_vpla_ord;
    SRC_DESC_T t_src_desc = {0};
    SNK_DESC_T t_snk_desc = {0};
    MM_SPEED_TYPE_T e_spd_type = MM_SPEED_TYPE_FORWARD_1X;
    UINT32 ui4_stream_mode = ST_MASK_AUDIO;
    MMP_FP_PRESENT_MODE_T    t_present_mode;
    INT32 i4_ret = 0;
    MM_SVC_STOP_INFO t_svc_info;
    MM_SVC_STOP_INFO t_svc_info_track;

    if((NULL == pt_this) || (NULL == pt_elmt))
    {
        MMP_ASSERT(FALSE);
        return MMPR_INV_ARG;
    }
    c_memset(&t_svc_info, 0, sizeof(MM_SVC_STOP_INFO));
#ifdef APP_LAST_MEMORY_SUPPORT
    SIZE_T z_size = 0;
    z_size = sizeof(MM_SVC_STOP_INFO);
    i4_ret = c_svctx_get( pt_this->h_svctx_hdl,
                             SVCTX_MM_GET_STOP_INFO,
                             (VOID*)&t_svc_info,
                             &z_size
                             );
    if (SVCTXR_OK == i4_ret)
    {
        if(t_svc_info.ui4_title_idx == ui4_prog_idx)
        {
           c_memset(&t_svc_info, 0, sizeof(MM_SVC_STOP_INFO));
        }
    }
    else
    {
        MMP_DBG_INFO(("c_svctx_get(SVCTX_MM_GET_TYPE_RESUME_STOP_INFO) returns %d\n", i4_ret));
    }
    t_mm.ui2_aud_idx = ui2_audio_play_idx;
    t_mm.ui2_sub_idx = ui2_subtitle_play_idx;
#endif
    i4_ret = _video_engine_full_stop(pt_this);
    if (MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        return i4_ret;
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
    t_mm.t_pos_info = t_svc_info.t_mm_svc_pos_info;
    t_mm.t_pos_info.t_pos_type = MM_SVC_POS_TYPE_ALL_TIME;
    t_mm.t_pos_info.ui2_idx = (UINT16)0;
    t_mm.ui4_title_idx = t_svc_info.ui4_title_idx;
    t_mm.ui4_playlist_idx = 0;
    t_mm.ui4_chap_idx = 0;
    t_mm.ui2_pmt_idx = (UINT16)ui4_prog_idx;

    c_memset(&t_svc_info_track, 0, sizeof(MM_SVC_STOP_INFO));

#ifdef APP_LAST_MEMORY_SUPPORT
    t_svc_info_track.ui4_title_idx = ui4_prog_idx;
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
    else
    {
        ui2_audio_play_idx = t_svc_info_track.ui2_aud_idx;
        ui2_subtitle_play_idx = t_svc_info_track.ui2_sub_idx;
    }

    if(0 != ui2_subtitle_play_idx)
    {
        ui4_stream_mode |= ST_MASK_SUBTITLE;
    }

#endif

        /*always enable cc if playing video fix DTV00939018*/
    if (_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {
        ui4_stream_mode |= ST_MASK_CLOSED_CAPTION;
    }

    t_vide_rgn.ui4_x = 0;
    t_vide_rgn.ui4_y = 0;
    t_vide_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_vide_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;

    /* set display region */
    if(_MMP_VE_ELMT_TYPE_VIDEO == pt_elmt->e_elmt_type)
    {

        i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
        if (MMPR_OK != i4_ret)
        {
            t_present_mode = MMP_FP_PRESENT_MODE_FULL;
        }
        if (MMP_FP_PRESENT_MODE_PREVIEW == t_present_mode)
        {
            t_disp_rgn.ui4_x = (pt_this->t_preview_rect.i4_left * VSH_REGION_MAX_WIDTH  + pt_this->t_osd_info.ui2_screen_w / 2) / pt_this->t_osd_info.ui2_screen_w;
            t_disp_rgn.ui4_y = (pt_this->t_preview_rect.i4_top  * VSH_REGION_MAX_HEIGHT + pt_this->t_osd_info.ui2_screen_h / 2) / pt_this->t_osd_info.ui2_screen_h;
            t_disp_rgn.ui4_width  = (RECT_W(&pt_this->t_preview_rect) * VSH_REGION_MAX_WIDTH  + pt_this->t_osd_info.ui2_screen_w / 2) / pt_this->t_osd_info.ui2_screen_w;
            t_disp_rgn.ui4_height = (RECT_H(&pt_this->t_preview_rect) * VSH_REGION_MAX_HEIGHT + pt_this->t_osd_info.ui2_screen_h / 2) / pt_this->t_osd_info.ui2_screen_h;
        }
        else if (_MMP_VE_ELMT_EFCT_4SM == _MMP_VERC_GET_ELMT_EFFECT())
        {
            t_disp_rgn.ui4_x = (UINT32)0;
            t_disp_rgn.ui4_y = (UINT32)0;
            t_disp_rgn.ui4_width  = (UINT32)0;
            t_disp_rgn.ui4_height = (UINT32)0;
        }
        else
        {
            t_disp_rgn.ui4_x = (UINT32)0;
            t_disp_rgn.ui4_y = (UINT32)0;
            t_disp_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
            t_disp_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;
        }
    }
    else
    {

        t_disp_rgn.ui4_x = 0;
        t_disp_rgn.ui4_y = 0;
        t_disp_rgn.ui4_width  = VSH_REGION_MAX_WIDTH;
        t_disp_rgn.ui4_height = VSH_REGION_MAX_HEIGHT;
    }
    t_vpla_ord.e_order_ctrl = VSH_PLANE_ORDER_CTRL_BOTTOM;
    t_vpla_ord.u.ui1_num_layers = 0;

    t_src_desc.e_type = SRC_TYPE_MEDIA_STORGE;
    t_src_desc.u_info.t_mm = t_mm;
    t_src_desc.ui4_title_idx = 0;
    t_src_desc.ui4_playlist_idx = 0;
    t_src_desc.ui4_chap_idx = 0;

    t_snk_desc.pt_video_region        = &t_vide_rgn;
    t_snk_desc.pt_disp_region         = &t_disp_rgn;
    t_snk_desc.pt_video_plane_order   = &t_vpla_ord;
    t_snk_desc.pt_video_strm_fltr_fct = _video_engine_strm_comp_filter;
    t_snk_desc.pv_video_strm_fltr_tag = (VOID*)pt_this;
    t_snk_desc.pt_audio_strm_fltr_fct = _video_engine_strm_comp_filter;
    t_snk_desc.pv_audio_strm_fltr_tag = (VOID*)pt_this;
    t_snk_desc.e_text_strm_type       = ST_SUBTITLE; /* To fix DTV00215125 */
    t_snk_desc.u_text_strm.t_subtitle.pt_fltr_fct = _video_engine_strm_comp_filter;
    t_snk_desc.u_text_strm.t_subtitle.pv_fltr_tag = (VOID*)pt_this;
    t_snk_desc.ps_snk_grp_name        = SN_PRES_MAIN_DISPLAY;
    //t_snk_desc.u_text_strm.t_subtitle.h_gl_plane = pt_this->t_osd_info.h_canvas_ex;

    /*CC and subtitle use different canvas to draw fix DTV00939018*/
{
    HANDLE_T h_cc_canvas = a_nav_get_cc_canvas();
    if (NULL_HANDLE != pt_this->t_osd_info.h_sub_plane)
    {
        t_snk_desc.u_text_strm.t_subtitle.h_gl_plane = pt_this->t_osd_info.h_sub_plane;
    }
    else
    {
        MMP_DBG_INFO(("{mmp} use mmp canvas %s,%d\n\r",__FILE__,__LINE__));
        t_snk_desc.u_text_strm.t_subtitle.h_gl_plane = pt_this->t_osd_info.h_canvas_ex;
    }
    if (h_cc_canvas != NULL_HANDLE)
    {
        MMP_DBG_INFO(("{mmp} use nav canvas %s,%d\n\r",__FILE__,__LINE__));
        t_snk_desc.h_cc_gl_plane = h_cc_canvas;
    }
    else
    {
        t_snk_desc.h_cc_gl_plane = t_snk_desc.u_text_strm.t_subtitle.h_gl_plane;
    }
}

    i4_ret = c_svctx_select_svc(
                    pt_this->h_svctx_hdl,
                    ui4_stream_mode,
                    &t_src_desc,
                    &t_snk_desc,
                    _svctx_media_play_nfy_fct,
                    (VOID*)pt_this
                    );
#ifdef APP_MMP_DBG_FLOW
     MMP_DBG_INFO(("{MMP} c_svctx_select_svc %d %s:%d\r\n", pt_elmt->h_elmt_hdl,__FUNCTION__, __LINE__));
#endif
    if(SVCTXR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP} c_svctx_select_svc() returns%s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_FAIL;
    }

    pt_elmt->e_elmt_stat = _MMP_VE_ELMT_STAT_PLAY;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * _mmp_video_engine_xxx() export methods implementations
 * these methods are provided for a_mmp_video_engine_xxx()
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_create
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
static VOID _mmp_video_engine_create(
                    VOID*                           pv_nfy_fct,       /* in  */
                    VOID*                           pv_wnd_idx,       /* in  */
                    VOID*                           pv_unused2,       /* in  */
                    VOID*                           pv_unused3        /* in  */
                    )
{
    MMP_VE_PLAY_INST_PTR_T pt_play_inst = NULL;
    UINT8 ui1_wnd_idx = (UINT8)(UINT32)pv_wnd_idx;
    INT32 i4_ret = 0;

    if((_MMP_VERC_REQ_WND_SIZE <= ui1_wnd_idx) ||
       (at_g_req_wnd[ui1_wnd_idx].pt_play_inst))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    i4_ret = video_engine_create(
                    (mmp_ve_play_nfy_fct)pv_nfy_fct,
                    &pt_play_inst
                    );
    if(MMPR_OK == i4_ret)
    {
        at_g_req_wnd[ui1_wnd_idx].pt_play_inst = pt_play_inst;
    }

    if(OSR_OK != c_sema_unlock(at_g_req_wnd[ui1_wnd_idx].h_sema_hdl))
    {
        MMP_ASSERT(0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_destroy
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
static VOID _mmp_video_engine_destroy(
                    VOID*                           pv_wnd_idx,       /* in  */
                    VOID*                           pv_unused1,       /* in  */
                    VOID*                           pv_unused2,       /* in  */
                    VOID*                           pv_unused3        /* in  */
                    )
{
    UINT8 ui1_wnd_idx = (UINT8)(UINT32)pv_wnd_idx;
    INT32 i4_ret = 0;

    if((_MMP_VERC_REQ_WND_SIZE <= ui1_wnd_idx) ||
       (!at_g_req_wnd[ui1_wnd_idx].pt_play_inst))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    /*reset SVCTX attribute*/
    a_tv_reset_svctx_parameter(((_MMP_VE_PLAY_INST_PTR_T)at_g_req_wnd[ui1_wnd_idx].pt_play_inst)->h_svctx_hdl);

    i4_ret = video_engine_destroy(at_g_req_wnd[ui1_wnd_idx].pt_play_inst);
    if(MMPR_OK != i4_ret)
    {
        MMP_ASSERT(0);
    }

    at_g_req_wnd[ui1_wnd_idx].pt_play_inst = NULL;

    if(OSR_OK != c_sema_unlock(at_g_req_wnd[ui1_wnd_idx].h_sema_hdl))
    {
        MMP_ASSERT(0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_open
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
static VOID _mmp_video_engine_open(
                    VOID*                           pv_wnd_idx,       /* in  */
                    VOID*                           pv_elm_name,      /* in  */
                    VOID*                           pv_unused1,       /* in  */
                    VOID*                           pv_unused2        /* in  */
                    )
{
    UINT8 ui1_wnd_idx = (UINT8)(UINT32)pv_wnd_idx;
    UINT8 ui1_icl_status;
    INT32 i4_ret = 0;

    if((_MMP_VERC_REQ_WND_SIZE <= ui1_wnd_idx) ||
       (!at_g_req_wnd[ui1_wnd_idx].pt_play_inst))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    ui1_icl_status = ICL_MMP_MEDIA_PLAY_STATUS_ON;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_MEDIA_PLAY_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_MEDIA_PLAY_STATUS_SIZE);

    i4_ret = mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_VIDEO);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}mmp_main_set_video_srm_mode %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    i4_ret = video_engine_open(at_g_req_wnd[ui1_wnd_idx].pt_play_inst, (const CHAR*)pv_elm_name);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_open %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    if(OSR_OK != c_sema_unlock(at_g_req_wnd[ui1_wnd_idx].h_sema_hdl))
    {
        MMP_ASSERT(0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_close
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
static VOID _mmp_video_engine_close(
                    VOID*                           pv_wnd_idx,       /* in  */
                    VOID*                           pv_unused1,       /* in  */
                    VOID*                           pv_unused2,       /* in  */
                    VOID*                           pv_unused3        /* in  */
                    )
{
    UINT8 ui1_wnd_idx = (UINT8)(UINT32)pv_wnd_idx;
    UINT8 ui1_icl_status;
    INT32 i4_ret = 0;

    if((_MMP_VERC_REQ_WND_SIZE <= ui1_wnd_idx) ||
       (!at_g_req_wnd[ui1_wnd_idx].pt_play_inst))
    {
        MMP_ASSERT(FALSE);
        return;
    }
	
#if 0
    i4_ret = video_engine_close(at_g_req_wnd[ui1_wnd_idx].pt_play_inst);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_close_elm %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }
#endif
	_mmp_vp_video_stop();

    i4_ret = mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_OFF);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}mmp_main_set_video_srm_mode %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    ui1_icl_status = ICL_MMP_MEDIA_PLAY_STATUS_OFF;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_MEDIA_PLAY_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_MMP_MEDIA_PLAY_STATUS_SIZE);

    if(OSR_OK != c_sema_unlock(at_g_req_wnd[ui1_wnd_idx].h_sema_hdl))
    {
        MMP_ASSERT(0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_play
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
static VOID _mmp_video_engine_play(
                    VOID*                           pv_wnd_idx,       /* in  */
                    VOID*                           pv_unused1,       /* in  */
                    VOID*                           pv_unused2,       /* in  */
                    VOID*                           pv_unused3        /* in  */
                    )
{
    UINT8 ui1_wnd_idx = (UINT8)(UINT32)pv_wnd_idx;
    MMP_VE_DIVX_CERT_T t_divx_cert;
    INT32 i4_ret = 0;

    if((_MMP_VERC_REQ_WND_SIZE <= ui1_wnd_idx) ||
       (!at_g_req_wnd[ui1_wnd_idx].pt_play_inst))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    i4_ret = video_engine_play(at_g_req_wnd[ui1_wnd_idx].pt_play_inst, &t_divx_cert);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_play %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    i4_ret = video_engine_zoom_reset_4sm((MMP_VE_PLAY_INST_PTR_T)at_g_req_wnd[ui1_wnd_idx].pt_play_inst);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_zoom_reset_4sm %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    if(OSR_OK != c_sema_unlock(at_g_req_wnd[ui1_wnd_idx].h_sema_hdl))
    {
        MMP_ASSERT(0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_stop
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
static VOID _mmp_video_engine_stop(
                    VOID*                           pv_wnd_idx,       /* in  */
                    VOID*                           pv_unused1,       /* in  */
                    VOID*                           pv_unused2,       /* in  */
                    VOID*                           pv_unused3        /* in  */
                    )
{
    UINT8 ui1_wnd_idx = (UINT8)(UINT32)pv_wnd_idx;
    INT32 i4_ret = 0;

    if((_MMP_VERC_REQ_WND_SIZE <= ui1_wnd_idx) ||
       (!at_g_req_wnd[ui1_wnd_idx].pt_play_inst))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    i4_ret = video_engine_stop(at_g_req_wnd[ui1_wnd_idx].pt_play_inst);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_stop %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    if(OSR_OK != c_sema_unlock(at_g_req_wnd[ui1_wnd_idx].h_sema_hdl))
    {
        MMP_ASSERT(0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_video_engine_video_info
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
static VOID _mmp_video_engine_video_info(
                    VOID*                           pv_wnd_idx,       /* in  */
                    VOID*                           pv_ptr_buf,       /* in  */
                    VOID*                           pv_unused2,       /* in  */
                    VOID*                           pv_unused3        /* in  */
                    )
{
    UINT8 ui1_wnd_idx = (UINT8)(UINT32)pv_wnd_idx;
    MMP_VE_VID_INFO_PTR_T pt_vid_info = (MMP_VE_VID_INFO_PTR_T)pv_ptr_buf;
    INT32 i4_ret = 0;

    if((_MMP_VERC_REQ_WND_SIZE <= ui1_wnd_idx) ||
       (!at_g_req_wnd[ui1_wnd_idx].pt_play_inst))
    {
        MMP_ASSERT(FALSE);
        return;
    }

    if(NULL == pt_vid_info)
    {
        return;
    }

    i4_ret = video_engine_get_vid_info((MMP_VE_PLAY_INST_PTR_T)at_g_req_wnd[ui1_wnd_idx].pt_play_inst, pt_vid_info);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}video_engine_stop %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
    }

    if(OSR_OK != c_sema_unlock(at_g_req_wnd[ui1_wnd_idx].h_sema_hdl))
    {
        MMP_ASSERT(0);
    }
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_video_engine_create
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
INT32 a_mmp_video_engine_create(
                    const CHAR                      s_client_name[16],/* in  */
                    mmp_ve_play_nfy_fct             pf_nfy_fct        /* in  */
                    )
{
    INT32 i4_ret = 0;
    UINT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
            return MMPR_FAIL;
        }
    }

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == at_g_req_wnd[i].s_client_name[0])
        {
            break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    c_strncpy(at_g_req_wnd[i].s_client_name, s_client_name, 16);

    /* create semaphores */
    do
    {
        i4_ret = c_sema_create(
                    &at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_TYPE_BINARY,
                    X_SEMA_STATE_LOCK
                    );
        if(OSR_OK != i4_ret)
        {
            break;
        }

        i4_ret = mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_video_engine_create,
                    (VOID*)pf_nfy_fct,
                    (VOID*)(UINT32)i,
                    (VOID*)NULL,
                    (VOID*)NULL
                    );
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /* wait result */
        i4_ret = c_sema_lock(
                    at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_OPTION_WAIT
                    );
        if(OSR_OK != i4_ret)
        {
            break;
        }

        if(NULL == at_g_req_wnd[i].pt_play_inst)
        {
            break;
        }

        return MMPR_OK;

    }while(0);

    MMP_ASSERT(MMPR_OK == a_mmp_video_engine_destroy(s_client_name));

    return MMPR_FAIL;
}

INT32 a_mmp_video_engine_destroy(
                    const CHAR                      s_client_name[16] /* in  */
                    )
{
    INT32 i4_ret = 0;
    UINT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    if(NULL != at_g_req_wnd[i].pt_play_inst)
    {
        i4_ret = mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_video_engine_destroy,
                    (VOID*)(UINT32)i,
                    (VOID*)NULL,
                    (VOID*)NULL,
                    (VOID*)NULL
                    );
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    /* wait result */
    i4_ret = c_sema_lock(
                    at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_OPTION_WAIT
                    );
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_sema_lock %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    i4_ret = c_sema_delete(at_g_req_wnd[i].h_sema_hdl);
    MMP_ASSERT(OSR_OK == i4_ret);
    at_g_req_wnd[i].h_sema_hdl = NULL_HANDLE;

    at_g_req_wnd[i].s_client_name[0] = 0;

    return MMPR_OK;
}

INT32 a_mmp_video_engine_open(
                    const CHAR                      s_client_name[16],/* in  */
                    const CHAR*                     ps_elm_name       /* in  */
                    )
{
    INT32 i4_ret = 0;
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    i4_ret = mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_video_engine_open,
                    (VOID*)(UINT32)i,
                    (VOID*)ps_elm_name,
                    (VOID*)NULL,
                    (VOID*)NULL
                    );
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* wait result */
    i4_ret = c_sema_lock(
                    at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_OPTION_WAIT
                    );
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_sema_lock %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    return MMPR_OK;
}

INT32 a_mmp_video_engine_close(
                    const CHAR                      s_client_name[16] /* in  */
                    )
{
    INT32 i4_ret = 0;
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    i4_ret = mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_video_engine_close,
                    (VOID*)(UINT32)i,
                    (VOID*)NULL,
                    (VOID*)NULL,
                    (VOID*)NULL
                    );
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* wait result */
    i4_ret = c_sema_lock(
                    at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_OPTION_WAIT
                    );
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_sema_lock %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    return MMPR_OK;
}

INT32 a_mmp_video_engine_play(
                    const CHAR                      s_client_name[16] /* in  */
                    )
{
    INT32 i4_ret = 0;
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    i4_ret = mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_video_engine_play,
                    (VOID*)(UINT32)i,
                    (VOID*)NULL,
                    (VOID*)NULL,
                    (VOID*)NULL
                    );
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* wait result */
    i4_ret = c_sema_lock(
                    at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_OPTION_WAIT
                    );
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_sema_lock %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    return MMPR_OK;
}
INT32 a_mmp_video_engine_pause(
                    const CHAR                      s_client_name[16] /* in  */
                    )
{
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    return video_engine_pause(at_g_req_wnd[i].pt_play_inst);
}

INT32 a_mmp_video_engine_fast_forward(
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_FAST_FWD_TYPE_T          e_fast_fwd_type   /* in  */
                    )
{
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    return video_engine_fast_forward(at_g_req_wnd[i].pt_play_inst, e_fast_fwd_type);
}

INT32 a_mmp_video_engine_fast_rewind(
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_FAST_RWD_TYPE_T          e_fast_rwd_type   /* in  */
                    )
{
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    return video_engine_fast_rewind(at_g_req_wnd[i].pt_play_inst, e_fast_rwd_type);
}

INT32 a_mmp_video_engine_stop(
                    const CHAR                      s_client_name[16] /* in  */
                    )
{
    INT32 i4_ret = 0;
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    i4_ret = mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_video_engine_stop,
                    (VOID*)(UINT32)i,
                    (VOID*)NULL,
                    (VOID*)NULL,
                    (VOID*)NULL
                    );
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* wait result */
    i4_ret = c_sema_lock(
                    at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_OPTION_WAIT
                    );
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_sema_lock %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    return MMPR_OK;
}
INT32 a_mmp_video_engine_get_duration (
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_DUR_TYPE_T               e_dur_type,       /* in  */
                    UINT64*                         pui8_dur_val      /* out */
                    )
{
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    return video_engine_get_duration(at_g_req_wnd[i].pt_play_inst, e_dur_type, pui8_dur_val);
}

INT32 a_mmp_video_engine_get_position (
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_POS_TYPE_T               e_pos_type,       /* in  */
                    UINT64*                         pui8_pos_val      /* out */
                    )
{
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    return video_engine_get_position(at_g_req_wnd[i].pt_play_inst, e_pos_type, pui8_pos_val);
}

INT32 a_mmp_video_engine_video_info(
                    const CHAR                      s_client_name[16],/* in  */
                    MMP_VE_VID_INFO_PTR_T           pt_video_info
                    )
{
    INT32 i4_ret = 0;
    INT8 i = 0;

    for(i = 0; i < _MMP_VERC_REQ_WND_SIZE; i++)
    {
        if(0 == c_strcmp(s_client_name, at_g_req_wnd[i].s_client_name))
        {
           break;
        }
    }

    if(_MMP_VERC_REQ_WND_SIZE == i)
    {
        return MMPR_FAIL;
    }

    if(NULL == pt_video_info)
    {
        return MMPR_INV_ARG;
    }

    i4_ret = mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_video_engine_video_info,
                    (VOID*)(UINT32)i,
                    (VOID*)pt_video_info,
                    (VOID*)NULL,
                    (VOID*)NULL
                    );
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* wait result */
    i4_ret = c_sema_lock(
                    at_g_req_wnd[i].h_sema_hdl,
                    X_SEMA_OPTION_WAIT
                    );
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_INFO(("{MMP}c_sema_lock %s:%d:%d\r\n", __FUNCTION__, __LINE__, i4_ret));
        return MMPR_INTERNAL_ERROR;
    }

    return MMPR_OK;
}

extern INT32 video_engine_unblock_svc(MMP_VE_PLAY_INST_PTR_T    pt_play_inst)
{
    INT32 i4_ret = MMPR_NOT_SUPPORT;
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    if (pt_this == NULL)
    {
        return i4_ret;
    }
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt = _MMP_VE_GET_1ST_ELMT(pt_this);
    if (pt_elmt && pt_elmt->e_elmt_stat == _MMP_VE_ELMT_STAT_PLAY)
    {
         //i4_ret = c_svctx_unblock_svc(pt_this->h_svctx_hdl, TRUE);
         BOOL b_block = FALSE;
         i4_ret = c_svctx_set(
                    pt_this->h_svctx_hdl,
                    SVCTX_MM_SET_RATING_UNBLOCK,
                    &b_block,
                    sizeof(BOOL));

    }
    return i4_ret;

}

extern INT32 video_engine_set_speed
(
    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
    SPLAYER_TrickSpeed_e                 e_speed
)
{
    _MMP_VE_PLAY_INST_PTR_T  pt_this      = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T  pt_elmt      =  _MMP_VE_GET_1ST_ELMT(pt_this);
    INT32                    i4_ret       = MMPR_OK;
    SPLAYER_TrickSpeed_e          e_crnt_speed = SPLAYER_MM_TRICK_SPEED_1X;

    if (pt_this == NULL || pt_elmt == NULL)
    {
        return MMPR_INV_ARG;
    }
    if (e_speed != SPLAYER_MM_TRICK_SPEED_1X &&
        e_speed != SPLAYER_MM_TRICK_SPEED_0X)
    {
        if (video_engine_trick_enable_ex(pt_play_inst, &e_speed) == FALSE)
        {
            return MMPR_NOT_SUPPORT;
        }
    }
    /*this API is fast enough*/
    i4_ret = _video_engine_get_trick(pt_this, &e_crnt_speed);
    if (i4_ret != MMPR_OK)
    {
        MMP_DBG_INFO(("{MMP} get trick return %d\n", i4_ret));
        return i4_ret;
    }
    if (e_crnt_speed == e_speed)
    {
        MMP_DBG_INFO(("{MMP} skip same speed setting\n"));
    }
    else
    {
        i4_ret = _video_engine_set_trick(pt_this, e_speed);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_INFO(("{MMP} set trick return %d\n", i4_ret));
            return i4_ret;
        }
    }

    /*change speed to status*/
    if (e_speed >= SPLAYER_MM_TRICK_SPEED_SLOW_2X && e_speed <= SPLAYER_MM_TRICK_SPEED_SLOW_32X)//fast rewind
    {
         pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_FRWD;
         pt_this->e_play_stat =  MMP_VE_PLAY_STAT_FAST_RWD;
         i4_ret = MMPR_IS_FAST_REWINDED;
    }
    else if (e_speed == SPLAYER_MM_TRICK_SPEED_SLOW_1_33X)//slow rewind
    {
         pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_SRWD;
         pt_this->e_play_stat =  MMP_VE_PLAY_STAT_SLOW_RWD;
         i4_ret = MMPR_IS_SLOW_REWINDED;
    }
    else if (e_speed >= SPLAYER_MM_TRICK_SPEED_1_25X && e_speed <= SPLAYER_MM_TRICK_SPEED_1_75X)//slow foword
    {
         pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_SFWD;
         pt_this->e_play_stat =  MMP_VE_PLAY_STAT_SLOW_FWD;
         i4_ret = MMPR_IS_SLOW_FORWARDED;
    }
    else if (e_speed >= SPLAYER_MM_TRICK_SPEED_2X && e_speed <= SPLAYER_MM_TRICK_SPEED_32X)//fast forword
    {
         pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_FFWD;
         pt_this->e_play_stat =  MMP_VE_PLAY_STAT_FAST_FWD;
         i4_ret = MMPR_IS_FAST_FORWARDED;
    }
    else if (e_speed == SPLAYER_MM_TRICK_SPEED_1X)
    {
         pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_PLAY;
         pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PLAY;
         i4_ret = MMPR_IS_PLAYED;
    }
    else if (e_speed == SPLAYER_MM_TRICK_SPEED_0X)
    {
         pt_elmt->e_elmt_oper = _MMP_VE_ELMT_OPER_PAUSE;
         pt_this->e_play_stat =  MMP_VE_PLAY_STAT_PAUSE;
         i4_ret = MMPR_IS_PAUSED;
    }
    return i4_ret;
}

extern INT32 video_engine_get_speed
(
    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,
    SPLAYER_TrickSpeed_e*                pe_speed
)
{
    INT32  i4_ret = MMPR_OK;
    i4_ret = _video_engine_get_trick((_MMP_VE_PLAY_INST_PTR_T)pt_play_inst, pe_speed);
    return i4_ret;
}

extern INT32 video_engine_start2play_cust(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,          /* in  */
                     MMP_VE_DIVX_CERT_PTR_T         pt_divx_cert      /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;

    return _video_engine_start2play(pt_this, pt_divx_cert);
}
INT32 video_engine_divx_cert_cust(
                     MMP_VE_PLAY_INST_PTR_T         pt_play_inst,     /* in  */
                     MMP_VE_DIVX_CERT_PTR_T         pt_divx_cert      /* out */
                    )
{
     _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    return _video_engine_divx_cert(pt_this, pt_divx_cert);
}

INT32 video_engine_full_stop_cust(
                    MMP_VE_PLAY_INST_PTR_T         pt_play_inst          /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    return _video_engine_full_stop(pt_this);
}

INT32 video_engine_elmt_open_cust(
                    MMP_VE_PLAY_INST_PTR_T         pt_play_inst         /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_2nd = _MMP_VE_GET_2ND_ELMT(pt_this);
    return _video_engine_elmt_open(pt_this,pt_elmt_2nd);
}

INT32 video_engine_elmt_close_cust(
                    MMP_VE_PLAY_INST_PTR_T         pt_play_inst         /* in  */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    _MMP_VE_ELMT_INFO_PTR_T pt_elmt_1nd = _MMP_VE_GET_1ST_ELMT(pt_this);
    return _video_engine_elmt_close(pt_this,pt_elmt_1nd);
}

BOOL video_engine_strm_comp_filter(
                    UINT16                          ui2_num_recs,     /* in  */
                    UINT16                          ui2_idx,          /* in  */
                    const STREAM_COMP_ID_T*         pt_comp_id,       /* in  */
                    const SCDB_REC_T*               pt_scdb_rec,      /* in  */
                    VOID*                           pv_fltr_tag       /* in  */
                    )
{
    return _video_engine_strm_comp_filter(ui2_num_recs,ui2_idx,pt_comp_id,pt_scdb_rec,pv_fltr_tag);
}

VOID svctx_media_play_nfy_fct(
                    HANDLE_T                        h_ctx_hdl,        /* in  */
                    SVCTX_COND_T                    e_ctx_cond,       /* in  */
                    SVCTX_NTFY_CODE_T               e_nfy_code,       /* in  */
                    STREAM_TYPE_T                   e_stm_type,       /* in  */
                    VOID*                           pv_nfy_tag        /* in  */
                    )
{
    return _svctx_media_play_nfy_fct( h_ctx_hdl, e_ctx_cond,e_nfy_code, e_stm_type, pv_nfy_tag );
}



MMP_VE_PLAY_INST_PTR_T video_engine_get_inst_by_idx(UINT32    ui4_inst_id)
{
    return (MMP_VE_PLAY_INST_PTR_T) at_g_play_inst_list[(_MMP_VE_INST_ID_T)ui4_inst_id];
}


#ifdef APP_LAST_MEMORY_SUPPORT
VOID video_engine_set_last_mem_audio_play_id(UINT16 ui2_audio_id)
{
    ui2_audio_play_idx = ui2_audio_id;
}

UINT16 video_engine_get_last_mem_audio_play_id(VOID)
{
    return ui2_audio_play_idx;
}

VOID video_engine_set_last_mem_subtitle_play_id(UINT16 ui2_sub_play_id)
{
   ui2_subtitle_play_idx = ui2_sub_play_id;
}

UINT16 video_engine_get_last_mem_subtitle_play_id(VOID)
{
    return ui2_subtitle_play_idx;
}

VOID video_engine_set_last_mem_audio_num(UINT16 ui2_num)
{
    ui2_valid_aud_num = ui2_num;
}

VOID video_engine_set_last_mem_sbtl_num(UINT16 ui2_num)
{
    ui2_valid_sbtl_num = ui2_num;
}
#endif





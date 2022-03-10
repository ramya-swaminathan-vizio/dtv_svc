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
 * $RCSfile: mmp_mmc_rc.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/list_player/a_mmp_list_player.h"
#include "mmp/photo_player2/a_mmp_photo_player.h"
#include "mmp/file_filter/mmp_ff.h"
#include "res/mmp/mmc/mmp_mmc_rc.h"
#include "mmp/listmode/listmode.h"
#include "mmp/thumbnailmode2/thumbnailmode.h"
#include "mmp/audio_player/a_audio_player.h"
#include "mmp/video_player/a_video_player.h"
#include "mmp/sort/a_mmp_sort.h"
#include "mmp/disp_res_ctrler/mmp_drc.h"
#include "res/app_util/config/a_cfg_custom.h"

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
#include "res/nav/a_nav_rmk_hdlr.h"
#endif

#include "mmp/dmr/mmp_dmr.h"

#include "mmp/browse_eng/mmp_browse_eng.h"

#ifdef APP_MENU_MMP_COEXIST
#include "menu2/a_menu.h"
#endif
#include "mmp/mmc/_mmp_mmc.h"
#include "mmp/foreground/mmp_foreground.h"
#include MMP_MLM_HEADER_FILE
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#if 0
#define SORT_CFG_NFY_TIMER_DELAY  1000
#define THUMBNAIL_SIZE_CFG_NFY_TIMER_DELAY  1000
#else
#define SORT_CFG_NFY_TIMER_DELAY  100
#define THUMBNAIL_SIZE_CFG_NFY_TIMER_DELAY  100
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static UINT16                         ui2_g_nfy_id = APP_CFG_NOTIFY_NULL_ID;
static HANDLE_T                       h_sort_cfg_nfy_timer = NULL_HANDLE;
static HANDLE_T                       h_thumbnail_size_cfg_nfy_timer= NULL_HANDLE;

static MMP_MC_BWR_PLAYER_INTER_ATTR_T     _at_inter_attr[MMP_MC_RC_FILE_BROWSER_MAX_COUNT * MMP_MC_RC_FILE_PLAYER_MAX_COUNT + 1] =
{
    {MMP_RC_BROWSER_ID_PHOTO_FRM, MMP_MEDIA_TYPE_PHOTO,FALSE},
    {MMP_BROWSE_ID_LAST, MMP_MEDIA_TYPE_UNKNOWN, TRUE}
};

 /*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
 /*---------------------------------------------------------------------------*/
 /**
  * @brief   Change thumbnail view size when the set has been changed.
  * @param
  * @param
  * @retval    The function succeded.
  */
 /*---------------------------------------------------------------------------*/
 static VOID _mmp_acfg_apply_nfy_fct(VOID*                     pv_event,
                               VOID*                       pv_data1,
                               VOID*                       pv_data2,
                               VOID*                       pv_tag)
{
     UINT16                     ui2_id = 0;

     ui2_id = (UINT16)(UINT32)pv_data1;
     if((CFG_MAKE_ID(APP_CFG_GRPID_MMP, APP_CFG_RECID_MMP_THUMB_SIZE) == ui2_id))
     {
         mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_BROWSER,
                              MMP_MSG_ID_CUST_APPLY_THUMB_SIZE_CFG,
                              pv_data1);

     }
     else
     {
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_BROWSER,
                          MMP_MSG_ID_CUST_APPLY_SORT_CFG,
                          pv_data1);
}

}

/*---------------------------------------------------------------------------*/
/**
 * @brief
 * @param
 * @param
 * @retval    The function succeded.
 */
/*---------------------------------------------------------------------------*/
static VOID _timer_nfy_fct(HANDLE_T  pt_tm_handle,
                                  VOID*     pv_tag)
{

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_acfg_apply_nfy_fct,
                                NULL,
                                pv_tag,
                                NULL,
                                NULL);

    return;
}


/*---------------------------------------------------------------------------*/
/**
 * @brief   Change thumbnail view size when the set has been changed.
 * @param
 * @param
 * @retval    The function succeded.
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_acfg_nfy_fct(VOID*                       pv_event,
                              VOID*                       pv_data1,
                              VOID*                       pv_data2,
                              VOID*                       pv_tag)
{
    UINT16                     ui2_id = 0;
    INT32                      i4_ret = 0;

    ui2_id = (UINT16)(UINT32)pv_data1;

    if((CFG_MAKE_ID(APP_CFG_GRPID_MMP, APP_CFG_RECID_MMP_THUMB_SIZE) == ui2_id))
    {
        mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_BROWSER,
                             MMP_MSG_ID_CUST_THUMB_SIZE_CFG_XNG,
                             pv_data1);

        i4_ret = c_timer_stop(h_thumbnail_size_cfg_nfy_timer);
        if(i4_ret != OSR_OK)
        {
           return ;
        }

        i4_ret = c_timer_start(h_thumbnail_size_cfg_nfy_timer,
                               THUMBNAIL_SIZE_CFG_NFY_TIMER_DELAY,
                               X_TIMER_FLAG_ONCE,
                               _timer_nfy_fct,
                               pv_data1);
        if(i4_ret != OSR_OK)
        {
           return ;
        }
    }
    else
    {
    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_BROWSER,
                         MMP_MSG_ID_CUST_SORT_CFG_XNG,
                         pv_data1);

        i4_ret = c_timer_stop(h_sort_cfg_nfy_timer);
        if(i4_ret != OSR_OK)
        {
           return ;
        }

    i4_ret = c_timer_start(h_sort_cfg_nfy_timer,
                           SORT_CFG_NFY_TIMER_DELAY,
                           X_TIMER_FLAG_ONCE,
                           _timer_nfy_fct,
                           pv_data1);
    if(i4_ret != OSR_OK)
    {
       return ;
    }

    }

    return ;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Change thumbnail view size when the set has been changed.
 * @param
 * @param
 * @retval    The function succeded.
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_acfg_nfy( UINT16   ui2_nfy_id,
                                VOID*   pv_tag,
                                UINT16  ui2_id)
{
   if((CFG_MAKE_ID(APP_CFG_GRPID_MMP, APP_CFG_RECID_MMP_THUMB_SIZE) != ui2_id) &&
      (CFG_MAKE_ID(APP_CFG_GRPID_MMP, APP_CFG_RECID_MMP_PHOTO_SORT) != ui2_id) &&
      (CFG_MAKE_ID(APP_CFG_GRPID_MMP, APP_CFG_RECID_MMP_AUDIO_SORT) != ui2_id) &&
      (CFG_MAKE_ID(APP_CFG_GRPID_MMP, APP_CFG_RECID_MMP_VIDEO_SORT) != ui2_id) )
   {
        return;
   }

    if(ui2_g_nfy_id != ui2_nfy_id)
    {
         return;
    }

    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_acfg_nfy_fct,
                                NULL,
                                (VOID *)(UINT32)ui2_id,
                                NULL,
                                NULL);
    return;
}

static INT32 _mmp_mmc_rc_handle_msg( MMP_MSG_ID_T    e_msg_id, VOID* pv_msg_param)
{
    switch(e_msg_id)
    {
        case MMP_MSG_ID_APP_PAUSED:
            IS_MMPR_OK(c_timer_stop(h_sort_cfg_nfy_timer));
            IS_MMPR_OK(c_timer_stop(h_thumbnail_size_cfg_nfy_timer));
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
            a_nav_cancel_remote_key(0);
#endif
            break;
        default :
            break;
    }
    return MMPR_OK;
}

static INT32 _mmp_mmc_rc_post_handle_msg(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param)
{
    switch(e_msg_id)
    {
        case MMP_MSG_ID_GUI_LANG_XNG:
#ifdef APP_MENU_MMP_COEXIST
            b_g_menu_mmp_coexist_allow_key = TRUE;
#endif
            break;
        default :
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_rc_mc_comps_register
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_mc_rc_comps_register(VOID)
{
    INT32                       i4_ret;
    
    /*register playlist*/
    i4_ret = a_mmp_reg_list_player();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("pe_type cannot be NULL.\r\n"));
        return i4_ret;
    }
    
#ifdef APP_CAST_TV_MMP_FG
    i4_ret = a_mmp_foreground_register();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_foreground_register() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef MMP_FB_RC_ENABLE_LIST_MODE
    /*register list mode*/
      i4_ret = a_mmp_listmode_register();
      if(MMPR_OK != i4_ret)
      {
          MMP_DBG_ERROR(("a_mmp_listmode_register() faled. i4_ret = %d.\r\n", i4_ret));
          return i4_ret;
      }
#endif

#ifndef APP_CAST_TV_MMP
    /*register thumbnail mode*/
    i4_ret = a_mmp_thumbnailmode_register();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_thumbnailmode_register() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT   
    /*register drm browse*/
    i4_ret = a_mmp_dmr_register();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_drm_register() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
#endif
#endif

    /*register photo player*/
    i4_ret = a_mmp_reg_photo_player();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_reg_photo_player() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
    /*register audio player*/
    i4_ret = a_mmp_audio_player_register();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_reg_photo_player() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef MMP_FB_RC_IS_ENABLE_VIDEO_FILTER
    /*register video player*/
    a_mmp_video_player_register();
#endif

#ifndef APP_CAST_TV_MMP
    /*register audio sort*/
    i4_ret = a_mmp_reg_sort_audio();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_reg_sort_audio() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifdef MMP_FB_RC_IS_ENABLE_VIDEO_FILTER
    /*register video sort*/
    i4_ret = a_mmp_reg_sort_video();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_reg_sort_video() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
#endif

#ifndef APP_CAST_TV_MMP
    /*register photo sort*/
    i4_ret = a_mmp_reg_sort_photo();
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("a_mmp_reg_sort_photo() faled. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_mc_rc_pre_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_mc_rc_pre_init(
    VOID*                       pv_param)
{
    INT32                   i4_ret;

    ui2_g_nfy_id = APP_CFG_NOTIFY_NULL_ID;
    IS_MMPR_OK(a_cfg_notify_reg(APP_CFG_GRPID_MMP,
                                NULL,
                                _mmp_acfg_nfy,
                                &ui2_g_nfy_id));

    /* Create Timer */
    IS_MMPR_OK(c_timer_create(&h_sort_cfg_nfy_timer));
    IS_MMPR_OK(c_timer_create(&h_thumbnail_size_cfg_nfy_timer));

    i4_ret = mmp_drc_init();
    if (i4_ret != MMPR_OK)
    {
        return i4_ret;
    }

    /* init file filter */
    i4_ret = mmp_ff_init();
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = mmp_be_init();
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_mc_rc_post_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_mc_rc_post_init(
    VOID*                       pv_param)
{
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_mc_rc_pre_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_mc_rc_pre_deinit(
    VOID*                       pv_param)
{
    if(APP_CFG_NOTIFY_NULL_ID != ui2_g_nfy_id)
    {
        MMP_EXEC_WITH_ASSERT(a_cfg_notify_unreg(ui2_g_nfy_id), APP_CFGR_OK);
        ui2_g_nfy_id = APP_CFG_NOTIFY_NULL_ID;
    }
    if(h_sort_cfg_nfy_timer != NULL_HANDLE)
    {
        MMP_EXEC_WITH_ASSERT(c_timer_delete(h_sort_cfg_nfy_timer), OSR_OK);
        h_sort_cfg_nfy_timer = NULL_HANDLE;
    }
    if(h_thumbnail_size_cfg_nfy_timer != NULL_HANDLE)
    {
        MMP_EXEC_WITH_ASSERT(c_timer_delete(h_thumbnail_size_cfg_nfy_timer), OSR_OK);
        h_thumbnail_size_cfg_nfy_timer = NULL_HANDLE;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_mc_rc_post_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_mc_rc_post_deinit(
    VOID*                       pv_param)
{
    INT32                   i4_ret;
 
    i4_ret = mmp_drc_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_be_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);

    return mmp_ff_deinit();
}

/*----------------------------------------------------------------------------
 * Name: mmp_mc_rc_get_def_setting
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
extern INT32 mmp_mc_rc_get_def_setting(
    MMP_MC_DEF_SETTING_T*                pt_setting)
{
    if(NULL == pt_setting)
    {
        return MMPR_INV_ARG;
    }

#ifndef APP_CAST_TV_MMP_FG
#ifdef APP_CAST_TV_MMP
    pt_setting->ui1_browser_id = MMP_RC_BROWSER_ID_LIST ;
#else
    pt_setting->ui1_browser_id = MMP_RC_BROWSER_ID_THUMBNAIL;
#endif 
#else
#ifdef APP_CAST_TV_MMP
    pt_setting->ui1_browser_id = MMP_RC_BROWSER_ID_LIST ;
#else
    pt_setting->ui1_browser_id = MMP_RC_BROWSER_ID_FOREGROUND;
#endif 
#endif
    pt_setting->ui1_list_idx = 0;
    pt_setting->ps_list_path = NULL;
    pt_setting->e_list_method = MMP_OPEN_METHOD_NEW;
    pt_setting->pf_rc_pre_handle_msg = _mmp_mmc_rc_handle_msg;
    pt_setting->pf_rc_post_handle_msg = _mmp_mmc_rc_post_handle_msg;
    pt_setting->at_inter_attr = _at_inter_attr;
    return MMPR_OK;
}

extern _MMP_MC_MEMBER_T                t_g_mmc;
INT32 mmp_mc_browse_fg_key_handler(UINT32 ui4_keycode, UINT32 ui4_keystatus)
{
    _MMP_MC_MEMBER_T*           pt_this = &t_g_mmc;
    UINT8                       ui1_file_idx;
    MMP_KEY_INFO                t_info;

    t_info.ui4_keycode   = ui4_keycode;
    t_info.ui4_keystatus = ui4_keystatus;

    ui1_file_idx = pt_this->t_active_fg.t_crnt_file.ui1_file_idx;
    if (MMP_PLAYER_IDX_NULL == ui1_file_idx)
    {
        return MMPR_NO_DATA;
    }

    /*Klocwork*/
    MMP_RET_WITH_ASSERT(ui1_file_idx < pt_this->ui1_player_used_count && ui1_file_idx < MMP_MC_RC_FILE_PLAYER_MAX_COUNT,
                        return MMPR_INTERNAL_ERROR);

    return pt_this->at_player[ui1_file_idx].t_intf.t_info_hdlr_intf.pf_cmd_do(NULL, MMP_FP_INFO_HDLR_CMD_ID_HANDLE_KEY, (VOID*)&t_info);
}




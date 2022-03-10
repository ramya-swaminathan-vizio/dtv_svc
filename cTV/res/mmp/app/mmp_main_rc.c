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
 * $RCSfile: mmp_main_rc.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
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
#include "u_irrc_btn_def.h"
#include "u_iom.h"
#include "u_cfg.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_dbg.h"

#include "res/fonts/a_font_custom.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_icl.h"
#include "app_util/a_cfg_ft_mngr.h"
#include "nav/a_navigator.h"

#include "mmp/mmp_common.h"
#include "mmp/mmp_tools.h"
#include "mmp/app/mmp_main.h"
#include "mmp/mmp_mmc_basic.h"
#include "res/mmp/app/mmp_main_rc.h"


#ifdef APP_COLOR_MODE_PALLET
    #include "res/mmp/img/mmp_img_table.i"
#endif
#include "mmp/common_ui2/mmp_info_bar.h"
#include "mmp/common_ui2/mmp_common_ui_animation.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "wizard/a_wzd.h"

#ifdef APP_DMR_SUPPORT
    #include "mmp/mmp_mmc_browse.h"
#endif

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#include "mmp/browse_eng/mmp_browse_eng.h"
#include "nav/scrn_blank/a_nav_scrn_blank.h"
#include "nav/pic_mode/pic_mode.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/banner2/a_banner.h"
#include "res/menu2/a_menu_custom.h"
#include "menu2/a_menu.h"
#include "res/menu2/menu_custom.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define _MMP_MAIN_RC_RCU_VOL_UP             (IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_VOL_UP))
#define _MMP_MAIN_RC_PANEL_VOL_UP           (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP))
#define _MMP_MAIN_RC_RCU_VOL_DOWN           (IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_VOL_DOWN))
#define _MMP_MAIN_RC_PANEL_VOL_DOWN         (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN))
#define _MMP_MAIN_RC_RCU_MUTE               (IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_MUTE))
#define _MMP_MAIN_RC_PANEL_MUTE             (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_MUTE))
#define _MMP_MAIN_RC_RCU_PREV_PRG           (IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_PREV_PRG))
#define _MMP_MAIN_RC_PANEL_PREV_PRG         (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_PREV_PRG))
#define _MMP_MAIN_RC_RCU_PRG_UP             (IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_PRG_UP))
#define _MMP_MAIN_RC_PANEL_PRG_UP           (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_PRG_UP))
#define _MMP_MAIN_RC_RCU_PRG_DOWN           (IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_PRG_DOWN))
#define _MMP_MAIN_RC_PANEL_PRG_DOWN         (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_PRG_DOWN))
#define _MMP_MAIN_RC_RCU_INP_SRC            (IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_INPUT_SRC))
#define _MMP_MAIN_RC_PANEL_INP_SRC          (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))

#define _MMP_MAIN_RC_VOL_CHANNEL            (CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL))

typedef enum __MMP_MAIN_RC_PAL_ID_T
{
    _MMP_MAIN_RC_PAL_ID_DEFAULT = 0,
    _MMP_MAIN_RC_PAL_ID_MMP
} _MMP_MAIN_RC_PAL_ID_T;

typedef struct __MMP_MAIN_RC_T
{
    INT16                       i2_vol;

#ifdef APP_COLOR_MODE_PALLET
    GL_HPALETTE_T               h_pal;
    GL_HPALETTE_T               h_def_pal;
#endif

    UINT16                      ui2_icl_nfy_id;
    UINT16                      ui2_icl_bk_player_nfy_id;
} _MMP_MAIN_RC_T;


extern VOID sys_cust_get_default_clut(GL_COLOR_T** ppt_clut, UINT16* pui2_size);
extern GL_COLOR_T* sys_cust_get_default_colorkey(VOID);

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static _MMP_MAIN_RC_T           t_g_main;

 /*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

#ifdef APP_COLOR_MODE_PALLET
    static INT32 _mmp_main_rc_init_pal(
        _MMP_MAIN_RC_T*         pt_this);

    static VOID _mmp_main_rc_deinit_pal(
        _MMP_MAIN_RC_T*         pt_this);

    static INT32 _mmp_main_rc_set_pal(
        _MMP_MAIN_RC_T*         pt_this,
        _MMP_MAIN_RC_PAL_ID_T   e_pal_id);
#endif

static INT32 _mmp_main_rc_icl_nfy_fct(UINT16              ui2_nfy_id,
                                      VOID*               pv_tag,
                                      ICL_NOTIFY_DATA_T*  pt_notify_data);
static VOID _mmp_main_rc_icl_nfy_hdlr(VOID* pv_tag1, VOID* pv_tag2,
                                      VOID* pv_tag3, VOID* pv_tag4);
//#ifdef APP_MMP_RC_PAUSED_WAIT_SVC
static VOID _mmp_main_rc_resume_wzd_in_mmp(VOID*                       pv_tag1,
                                           VOID*                       pv_tag2,
                                           VOID*                       pv_tag3,
                                           VOID*                       pv_tag4);
//#endif
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_pre_init
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_pre_init(VOID)
{
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_icl_bk_player_nfy_hdlr
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static VOID _mmp_main_rc_icl_bk_player_nfy_hdlr(VOID* pv_tag1,
                                                             VOID* pv_tag2,
                                                             VOID* pv_tag3,
                                                             VOID* pv_tag4)
{
    ICL_ID_TYPE e_id = (ICL_ID_TYPE) (((UINT32) pv_tag1) & 0x0000FFFF);

    if (e_id == ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS))
    {
        mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL,
                             MMP_MSG_ID_BK_PLAYER_STATUS_XNG,
                             NULL);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_icl_bk_player_nfy_fct
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static INT32 _mmp_main_rc_icl_bk_player_nfy_fct(UINT16              ui2_nfy_id,
                                                            VOID*               pv_tag,
                                                            ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    mmp_mc_event_switch_context (MMP_MC_CSC_RETRY_TYPE_ONCE,
                                 _mmp_main_rc_icl_bk_player_nfy_hdlr,
                                 (VOID*)(UINT32)pt_notify_data->pe_id[0],
                                 NULL,
                                 NULL,
                                 NULL);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_post_init
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_post_init(VOID)
{
    _MMP_MAIN_RC_T*     pt_this = &t_g_main;
    INT32               i4_ret = MMPR_OK;

#ifdef APP_COLOR_MODE_PALLET

    i4_ret = _mmp_main_rc_init_pal(pt_this);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
#endif

    i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _mmp_main_rc_icl_nfy_fct,
                              &pt_this->ui2_icl_nfy_id);
    if (i4_ret != ICLR_OK)
    {
        return i4_ret;
    }

    i4_ret = a_icl_notify_reg(ICL_GRPID_CUSTOM_MMP,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _mmp_main_rc_icl_bk_player_nfy_fct,
                              &pt_this->ui2_icl_bk_player_nfy_id);
    if (i4_ret != ICLR_OK)
    {
        return i4_ret;
    }

    /* create animation icon */
    i4_ret = mmp_common_ui_animation_init(mmp_main_get_canvas());
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_info_bar_init(mmp_main_get_canvas(), 0 , 0);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_key_pre_handler
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_pre_exit(VOID)
{
    INT32               i4_ret = MMPR_OK;

    i4_ret = mmp_common_ui_animation_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_info_bar_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_key_pre_handler
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_post_exit(VOID)
{
    _MMP_MAIN_RC_T*             pt_this = &t_g_main;

#ifdef APP_COLOR_MODE_PALLET
    _mmp_main_rc_deinit_pal(pt_this);
#endif

    if(0 != pt_this->ui2_icl_nfy_id)
    {
        a_icl_notify_unreg(pt_this->ui2_icl_nfy_id);
        pt_this->ui2_icl_nfy_id = 0;
    }

    if( 0 != pt_this->ui2_icl_bk_player_nfy_id)
    {
        a_icl_notify_unreg(pt_this->ui2_icl_bk_player_nfy_id);
        pt_this->ui2_icl_bk_player_nfy_id = 0;
    }
    c_memset(pt_this, 0, sizeof(_MMP_MAIN_RC_T));

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_pre_resume
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_pre_resume(VOID)
{
#ifdef APP_COLOR_MODE_PALLET
    {
        _MMP_MAIN_RC_T*             pt_this = &t_g_main;
        INT32                       i4_ret;

        i4_ret = _mmp_main_rc_set_pal(pt_this, _MMP_MAIN_RC_PAL_ID_MMP);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif

#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MMP, ZOOM_APP_RECID_MMP_DEFAULT));
#endif

#ifdef APP_3D_MODE_SUPPORT
    BOOL                        b_3d_support = FALSE;
    a_cfg_custom_plf_opt_get_3d_support(&b_3d_support);
    if(b_3d_support)
    {
        a_cfg_custom_3D_setting_reset_3D_mode();
    }
#endif

    c_wgl_img_cache_flush();

    /* Enable the unrecognize char transformation in mmp mode. */
    a_font_custom_enable_unrecognize_char(TRUE);

//#ifdef APP_MMP_RC_PAUSED_WAIT_SVC
    INT32                           i4_ret = MMPR_OK;
    ICL_CUSTOM_RESUME_NEXT_APP_T    e_next_app;

    i4_ret = a_icl_custom_get_next_resume_app(&e_next_app);
    if (i4_ret == ICLR_OK &&  ICL_CUSTOM_RESUME_NEXT_APP_MMP == e_next_app)
    {
        a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_LAST_ENTRY);
    }
//#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_post_resume
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_post_resume(VOID)
{
    _MMP_MAIN_RC_T*             pt_this = &t_g_main;
    INT32                       i4_ret;
    UINT8                       ui1_icl_status;

    /* fix DTV00821562 */
    a_tv_net_OSD_appear();
	a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);

    a_menu_custom_set_resuming_mmp_flag(FALSE);

    /**/
    i4_ret = a_tv_get_vol(_MMP_MAIN_RC_VOL_CHANNEL, &pt_this->i2_vol);
    if(TVR_OK != i4_ret)
    {
        pt_this->i2_vol = 0;
        return MMPR_FAIL;
    }
    banner_hide_msg();
    ui1_icl_status = ICL_MMP_SRC_STATUS_RESUME;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_SRC_STATUS),
              (VOID*) &ui1_icl_status,
               ICL_RECID_CUSTOM_MMP_SRC_STATUS_SIZE);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_pre_pause
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_pre_pause(VOID)
{
    a_cfg_set_skip_viewport_func(FALSE);

#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MMP, ZOOM_APP_RECID_MMP_DEFAULT));
#endif

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_post_pause
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_post_pause(VOID)
{
    UINT32             ui4_status = 0xFFFFFFFF;
    INT32              i4_ret = MMPR_OK;
    UINT8              ui1_icl_status;

#ifdef APP_COLOR_MODE_PALLET
    {
        _MMP_MAIN_RC_T*             pt_this = &t_g_main;
        INT32                       i4_ret;

        i4_ret = _mmp_main_rc_set_pal(pt_this, _MMP_MAIN_RC_PAL_ID_DEFAULT);
        if(MMPR_OK != i4_ret)
        {
            return i4_ret;
        }
    }
#endif

#ifdef APP_3D_MODE_SUPPORT
	BOOL						b_3d_support = FALSE;
	a_cfg_custom_plf_opt_get_3d_support(&b_3d_support);
	if(b_3d_support)
	{
		a_cfg_custom_3D_setting_reset_3D_mode();
	}
#endif

    /* when exit MMP, need to clear this flag. */
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS),
              (VOID*) &ui4_status,
              ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS_SIZE);

    c_wgl_img_cache_flush();

    /* Disable the unrecognize char transformation in mmp mode. */
    a_font_custom_enable_unrecognize_char(FALSE);

    /* fix DTV00821562 */
    a_tv_net_OSD_disapper();
	a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);

#ifdef APP_C4TV_SUPPORT
    /* cast source ,select source before link to menu page fix DTV00845309 */
    ISL_REC_T   t_isl_rec;
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type &&
        (MENU_SHORT_CUT_MMP_DEV_LIST == mmp_main_get_back_to_menu_page()
        || MENU_SHORT_CUT_MMP_MEDIA_TYPE == mmp_main_get_back_to_menu_page()
        ))
    {
        MMP_DBG_INFO(("cast source %s,%d\n\r",__FILE__,__LINE__));
        i4_ret = a_menu_shortcut_link((MENU_SHORT_CUT_T)mmp_main_get_back_to_menu_page());
        MMPR_LOG_ON_FAIL(i4_ret);

        mmp_main_set_back_to_menu_page(MENU_SHORT_CUT_MAX);
    }
#endif

    ui1_icl_status = ICL_MMP_SRC_STATUS_PAUSE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_SRC_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_CUSTOM_MMP_SRC_STATUS_SIZE);

    return MMPR_OK;
}

//#ifdef APP_MMP_RC_PAUSED_WAIT_SVC
/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_paused_wait_svc
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
INT32 mmp_main_rc_paused_wait_svc(VOID)
{
    INT32                           i4_ret = MMPR_OK;
    ICL_CUSTOM_RESUME_NEXT_APP_T    e_next_app;

    i4_ret = a_icl_custom_get_next_resume_app(&e_next_app);

#ifdef DEBUG
   DBG_LOG_PRINT(("\n%s,%d,i4_ret=%d,e_next_app=%d\n",
                __FILE__, __LINE__, i4_ret, (UINT32)e_next_app));
#endif

    if (i4_ret == ICLR_OK &&
        (ICL_CUSTOM_RESUME_NEXT_APP_WZD_NW == e_next_app
        || ICL_CUSTOM_RESUME_NEXT_APP_WZD_RC == e_next_app
        || ICL_CUSTOM_RESUME_NEXT_APP_WZD_DEVICE_SETUP == e_next_app
        || ICL_CUSTOM_RESUME_NEXT_APP_WIFI_WZD_RC == e_next_app
        || ICL_CUSTOM_RESUME_NEXT_APP_MIRACAST == e_next_app
        || ICL_CUSTOM_RESUME_NEXT_APP_WZD_TUNER_SETUP == e_next_app))
    {
        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                             _mmp_main_rc_resume_wzd_in_mmp,
                                             (VOID*)(UINT32)e_next_app,
                                             (VOID*)NULL,
                                             (VOID*)NULL,
                                             (VOID*)NULL);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_is_able_to_restore_vid_svc
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
BOOL mmp_main_rc_is_able_to_restore_vid_svc(CHAR*    ps_name)
{
    BOOL b_restore = TRUE;

    if (ps_name == NULL)
    {
        return b_restore;
    }

    if (0 == c_strcmp (ps_name, WZD_NAME))
    {
        b_restore = FALSE;
    }

    return (b_restore);
}
//#endif

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_key_pre_handler
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
#include "menu2/a_menu.h"
BOOL mmp_main_rc_key_pre_handler(
    UINT32                      ui4_key_status,
    UINT32                      ui4_key_code,
    VOID*                       pv_param)
{
    INT32       i4_ret;

    if(WGL_MSG_KEY_DOWN   == ui4_key_status)
        DBG_LOG_PRINT(("[MMP][%s %d] ui4_key_code = 0x%x\n",__FUNCTION__,__LINE__,ui4_key_code));

    if ((WGL_MSG_KEY_DOWN   == ui4_key_status) ||
        (WGL_MSG_KEY_UP     == ui4_key_status) ||
        (WGL_MSG_KEY_REPEAT == ui4_key_status))
    {
 		if (nav_is_component_visible(NAV_COMP_ID_SCREEN_MODE) ||
			nav_is_component_visible(NAV_COMP_ID_PICTURE_EFFECT))
        {
            if (BTN_P_EFFECT == ui4_key_code)
            {
                a_amb_default_key_handler_ex(ui4_key_status, (VOID*)ui4_key_code, (VOID*)NULL);
                DBG_INFO(("%s() P_EFFECT BUTTON: Line %d: return\n", __FUNCTION__, __LINE__));
                return FALSE;
            }
            /* fix DTV00850875 ,pic mode UI change */
            if (BTN_CURSOR_LEFT == ui4_key_code ||
                BTN_CURSOR_RIGHT == ui4_key_code ||
                BTN_SELECT == ui4_key_code ||
                BTN_EXIT == ui4_key_code)
            {
                a_amb_default_key_handler_ex(ui4_key_status, (VOID*)ui4_key_code, (VOID*)NULL);
                return FALSE;
            }
            else if (BTN_CURSOR_UP == ui4_key_code ||
                BTN_CURSOR_DOWN == ui4_key_code ||
                BTN_RETURN == ui4_key_code)
            {
                /* do NOT respond other key any more */
                return FALSE;
            }
        }
        else
        {
            menu_blank_oled_scrn_timer_refresh();
            if(menu_custom_is_blank_screen()      &&
               WGL_MSG_KEY_DOWN == ui4_key_status &&
               BTN_VOL_DOWN     != ui4_key_code   &&
               BTN_MUTE         != ui4_key_code   &&
               BTN_VOL_UP       != ui4_key_code   &&
               BTN_WIDGET       != ui4_key_code   &&
               BTN_IHEART_RADIO != ui4_key_code   &&
               BTN_XUMO         != ui4_key_code   &&
               BTN_AMAZON       != ui4_key_code   &&
               BTN_HULU         != ui4_key_code   &&
               BTN_NETFLIX      != ui4_key_code   &&
               BTN_HULU         != ui4_key_code   &&
               BTN_CRACKLE      != ui4_key_code   &&
               BTN_VUDU         != ui4_key_code   &&
               BTN_MGO          != ui4_key_code   &&
               BTN_WATCHFREE    != ui4_key_code   &&
               BTN_REDBOX       != ui4_key_code   &&
               BTN_HAYSTACK     != ui4_key_code   &&
               BTN_DISNEY       != ui4_key_code   &&
               BTN_PARTNER_2    != ui4_key_code   && // Peacock
               BTN_PARTNER_3    != ui4_key_code   && // Tubi
               BTN_PARTNER_4    != ui4_key_code   && // Pluto
               BTN_PARTNER_5    != ui4_key_code)     // HBOMAX
            {
                menu_custom_unblank_screen(ui4_key_code);
                DBG_LOG_PRINT(("%s() it is blank screen : Line %d: return\n", __FUNCTION__, __LINE__));
                return FALSE;
            }

			if (BTN_BLANK_SCREEN == ui4_key_code)
			{
			    if (a_menu_is_hot_key(ui4_key_code, WGL_MSG_KEY_DOWN))
	            {
	                a_menu_hot_key_handler(ui4_key_code,
	                                       WGL_MSG_KEY_DOWN,
	                                       NULL);
	            }
			}

            if (BTN_P_EFFECT == ui4_key_code)
            {
                a_amb_default_key_handler(ui4_key_status, (VOID*)ui4_key_code, (VOID*)NULL);
                DBG_LOG_PRINT(("%s() P_EFFECT BUTTON: Line %d: return\n", __FUNCTION__, __LINE__));
                return FALSE;
            }

            if (BTN_SHOW_VOL_BAR == ui4_key_code)
            {
                a_amb_default_key_handler(ui4_key_status, (VOID*)ui4_key_code, (VOID*)NULL);
                DBG_LOG_PRINT(("%s() BTN_SHOW_VOL_BAR BUTTON: Line %d: return\n", __FUNCTION__, __LINE__));
                return FALSE;
            }

            if (BTN_PANEL_POWER_INPUT == ui4_key_code)
            {
                 a_amb_default_key_handler(ui4_key_status, (VOID*)ui4_key_code, (VOID*)NULL);
                 DBG_LOG_PRINT(("%s() BTN_PANEL_POWER_INPUT: Line %d: return\n", __FUNCTION__, __LINE__));
                 return FALSE;
            }

            /* MMP support input list */
            if (nav_is_component_visible(NAV_COMP_ID_INPUT_SRC))
            {
                i4_ret = a_amb_default_key_handler(ui4_key_status, (VOID*)ui4_key_code, NULL);
                MMPR_LOG_ON_FAIL(i4_ret);
                return FALSE;
            }
        }
    }

#ifdef APP_DMR_SUPPORT
    UINT8 ui1_browser_id;
    BOOL  b_browser_sohw;

    if ((WGL_MSG_KEY_DOWN   == ui4_key_status) ||
        (WGL_MSG_KEY_UP     == ui4_key_status) ||
        (WGL_MSG_KEY_REPEAT == ui4_key_status))
    {
        i4_ret = mmp_mc_browse_get_active(&ui1_browser_id, &b_browser_sohw);
        if (MMPR_OK != i4_ret)
        {
           DBG_ERROR(("mmp_mc_browse_get_active() returns %d.\n", i4_ret));
        }

        if (MMP_RC_BROWSER_ID_DMR == ui1_browser_id)
        {
            return FALSE;
        }
    }
#endif

    switch(ui4_key_code)
    {
    case BTN_NETWORK:
    {
        a_menu_shortcut_link(MENU_SHORT_CUT_NETWORK_PAGE);
        return FALSE;
    }
    case _MMP_MAIN_RC_RCU_VOL_UP:
    case _MMP_MAIN_RC_PANEL_VOL_UP:
    case _MMP_MAIN_RC_RCU_VOL_DOWN:
    case _MMP_MAIN_RC_PANEL_VOL_DOWN:
    case _MMP_MAIN_RC_RCU_MUTE:
    case _MMP_MAIN_RC_PANEL_MUTE:
    {
        if (_MMP_MAIN_RC_PANEL_VOL_UP == ui4_key_code)
        {
            ui4_key_code = _MMP_MAIN_RC_RCU_VOL_UP;
        }
        else if (_MMP_MAIN_RC_PANEL_VOL_DOWN == ui4_key_code)
        {
            ui4_key_code = _MMP_MAIN_RC_RCU_VOL_DOWN;
        }
        else if (_MMP_MAIN_RC_PANEL_MUTE == ui4_key_code)
        {
            ui4_key_code = _MMP_MAIN_RC_RCU_MUTE;
        }

        i4_ret = a_amb_default_key_handler_ex(ui4_key_status, (VOID*)ui4_key_code, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);

        return FALSE;
    }
        break;
    case _MMP_MAIN_RC_RCU_PRG_UP:
    case _MMP_MAIN_RC_PANEL_PRG_UP:
    case _MMP_MAIN_RC_RCU_PRG_DOWN:
    case _MMP_MAIN_RC_PANEL_PRG_DOWN:
    {
    }
        return FALSE;
    case _MMP_MAIN_RC_RCU_INP_SRC:
    case _MMP_MAIN_RC_PANEL_INP_SRC:
    {
        if (WGL_MSG_KEY_DOWN == ui4_key_status ||
            WGL_MSG_KEY_REPEAT == ui4_key_status)
        {
            ui4_key_status = WGL_MSG_KEY_DOWN;

            if (_MMP_MAIN_RC_PANEL_INP_SRC == ui4_key_code)
            {
                ui4_key_code = _MMP_MAIN_RC_RCU_INP_SRC;
            }

            i4_ret = a_amb_default_key_handler(ui4_key_status, (VOID*)ui4_key_code, NULL);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }
        return FALSE;
    case _MMP_MAIN_RC_RCU_PREV_PRG:
    case _MMP_MAIN_RC_PANEL_PREV_PRG:
    {
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        if (TRUE == a_cfg_ftm_with_feature(APP_CFG_FTM_ID_ALLOW_PREV_PRG_WITHIN_SOURCE))
        {
            if(WGL_MSG_KEY_DOWN == ui4_key_status || WGL_MSG_KEY_REPEAT == ui4_key_status)
            {
                INT32 i4_ret = 0;
                ISL_REC_T  t_crnt_isl_rec;
                ISL_REC_T  t_last_isl_rec;

                i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_crnt_isl_rec);
                if (i4_ret != TVR_OK)
                {
                    break;
                }

                i4_ret = a_tv_get_last_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_last_isl_rec);
                if (i4_ret != TVR_OK)
                {
                    break;
                }

                if (t_crnt_isl_rec.ui1_id != t_last_isl_rec.ui1_id)
                {
                    i4_ret = a_tv_set_last_input_src_id (TV_WIN_ID_MAIN, t_crnt_isl_rec.ui1_id);
                    if (i4_ret != TVR_OK)
                    {
                        break;
                    }

                    i4_ret = a_tv_set_input_src_id (TV_WIN_ID_MAIN, t_last_isl_rec.ui1_id);
                    if (i4_ret != TVR_OK)
                    {
                        break;
                    }
                }

                a_amb_resume_app(NAV_NAME);
            }
        }
#endif
    }
        break;
    default:
        break;
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_key_post_handler
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
VOID mmp_main_rc_key_post_handler(
    UINT32                      ui4_key_status,
    UINT32                      ui4_key_code,
    VOID*                       pv_param)
{
    /*do nothing*/
}

/*-----------------------------------------------------------------------------
 * Name
 *      mmp_main_rc_system_key_handler
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static VOID  _send_epg_key(VOID*                       pv_param1,
                                 VOID*                       pv_param2,
                                 VOID*                       pv_param3,
                                 VOID*                       pv_param4)
{
    c_wgl_dispatch_event((UINT32)WGL_MSG_KEY_DOWN, (VOID*)(UINT32)BTN_PRG_INFO, NULL);

    mmp_main_rc_key_post_handler((UINT32)WGL_MSG_KEY_DOWN, (UINT32)BTN_PRG_INFO, NULL);

   DBG_LOG_PRINT(("\nBTN_EPG\n"));
}

BOOL mmp_main_rc_system_key_handler(
    UINT32                      ui4_keycode)
{
    if (a_scrn_blank_get_state() == NAV_SCRN_BLANK_STATE_BLANK)
    {
        if (IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER) == ui4_keycode)
        {
            /* Do nothing */
        }
        else
        {
            //nav_grab_activation(NAV_COMP_ID_SCRN_BLANK);
            a_scrn_blank_act((VOID*)NULL, (VOID*)NULL, (VOID*)NULL);
            return FALSE;
        }
    }

    if (BTN_EPG == ui4_keycode)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                    _send_epg_key,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);
        return FALSE;
    }

    if (BTN_MENU == ui4_keycode ||
        IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_MENU) == ui4_keycode)
    {
#ifdef APP_MENU_MMP_COEXIST
#ifdef APP_DMR_SUPPORT
        INT32 i4_ret;
        UINT8 ui1_browser_id;
        BOOL  b_browser_sohw;

        i4_ret = mmp_mc_browse_get_active(&ui1_browser_id, &b_browser_sohw);
        if (MMPR_OK != i4_ret)
        {
           DBG_ERROR(("mmp_mc_browse_get_active() returns %d.\n", i4_ret));
        }

        if (MMP_RC_BROWSER_ID_DMR == ui1_browser_id)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
#else
        return TRUE;
#endif
#else
        return FALSE;
#endif
    }

    return TRUE;
}

#ifdef APP_COLOR_MODE_PALLET
/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_init_pal
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static INT32 _mmp_main_rc_init_pal(
    _MMP_MAIN_RC_T*             pt_this)
{
    GL_COLOR_T*                 pt_color_table;
    INT32                       i4_ret;
    UINT16                      ui2_size;

    if(NULL_HANDLE != pt_this->h_pal)
    {
        MMP_ASSERT(0);  /*init twice*/
        return MMPR_INV_ARG;
    }

    /*create MMP palette*/
    i4_ret = c_gl_palette_create(GL_COLORMODE_ARGB_CLUT8,
                                 sizeof(_at_mmp_clr_table) / sizeof(GL_COLOR_T),
                                 _at_mmp_clr_table,
                                 &pt_this->h_pal);

    if(GLR_OK > i4_ret)
    {
        pt_this->h_pal = NULL_HANDLE;
        return MMPR_FAIL;
    }

    /*get default color table*/
    pt_color_table = NULL;
    ui2_size = 0;
    sys_cust_get_default_clut(&pt_color_table, &ui2_size);
    if(NULL == pt_color_table || 0 == ui2_size)
    {
        return MMPR_INV_ARG;
    }

    /*create default palette*/
    i4_ret = c_gl_palette_create(GL_COLORMODE_ARGB_CLUT8,
                                 ui2_size,
                                 pt_color_table,
                                 &pt_this->h_def_pal);
    if(GLR_OK > i4_ret)
    {
        pt_this->h_def_pal = NULL_HANDLE;
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_deinit_pal
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static VOID _mmp_main_rc_deinit_pal(
    _MMP_MAIN_RC_T*             pt_this)
{
    INT32                       i4_ret;

    if(pt_this)
    {
        if(NULL_HANDLE != pt_this->h_pal)
        {
            i4_ret = c_gl_obj_free(pt_this->h_pal);
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->h_pal = NULL_HANDLE;
        }

        if(NULL_HANDLE != pt_this->h_def_pal)
        {
            i4_ret = c_gl_obj_free(pt_this->h_def_pal);
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->h_def_pal = NULL_HANDLE;
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_set_pal
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static INT32 _mmp_main_rc_set_pal(
    _MMP_MAIN_RC_T*             pt_this,
    _MMP_MAIN_RC_PAL_ID_T       e_pal_id)
{
    GL_COLOR_T                  t_mmp_clr_key = {0};
    INT32                       i4_ret;
    WGL_CVS_CLR_CFG_T           t_cvs_clr_cfg = {0};
    GL_COLOR_T*                 pt_clr_key;

    /* Set the palette */
    if(_MMP_MAIN_RC_PAL_ID_MMP == e_pal_id)
    {
        t_cvs_clr_cfg.h_palette = pt_this->h_pal;
        t_mmp_clr_key.u3.index = MMP_DEFAULT_CLRKEY_IDX;
        pt_clr_key = &t_mmp_clr_key;
    }
    else
    {
        t_cvs_clr_cfg.h_palette = pt_this->h_def_pal;
        pt_clr_key = sys_cust_get_default_colorkey();
    }
    t_cvs_clr_cfg.ui4_flag   = WGL_CANVAS_CFG_PALETTE;

    if(pt_clr_key)
    {
        t_cvs_clr_cfg.t_colorkey = *pt_clr_key;
        t_cvs_clr_cfg.ui4_flag |= WGL_CANVAS_CFG_COLORKEY;
    }

    i4_ret = c_wgl_set_canvas_color(mmp_main_get_canvas(), &t_cvs_clr_cfg);
    return (WGLR_OK > i4_ret) ? MMPR_FAIL : MMPR_OK;;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_icl_nfy_fct
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static INT32 _mmp_main_rc_icl_nfy_fct(UINT16              ui2_nfy_id,
                                      VOID*               pv_tag,
                                      ICL_NOTIFY_DATA_T*  pt_notify_data)
{

    mmp_mc_event_switch_context (MMP_MC_CSC_RETRY_TYPE_ONCE,
                                 _mmp_main_rc_icl_nfy_hdlr,
                                 NULL,
                                 NULL,
                                 NULL,
                                 NULL);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_icl_nfy_fct
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static VOID _mmp_main_rc_icl_nfy_hdlr(VOID* pv_tag1, VOID* pv_tag2,
                                      VOID* pv_tag3, VOID* pv_tag4)
{
    MMP_VOL_UPD_INFO_T  t_vol_info;
    UINT8               ui1_icl_val;
    SIZE_T              z_size;
    INT32               i4_ret;

    c_memset(&t_vol_info, 0, sizeof(MMP_VOL_UPD_INFO_T));

    z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if (ICLR_OK == i4_ret && ui1_icl_val == ICL_CEC_SAC_STATUS_ON)
    {
        t_vol_info.b_cec_sac = TRUE;
    }

    t_vol_info.b_mute_dirty = TRUE;

    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL,
                         MMP_MSG_ID_VOL_INFO_UPD,
                         (VOID*)&t_vol_info);
}

//#ifdef APP_MMP_RC_PAUSED_WAIT_SVC
/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_main_rc_resume_wzd_in_mmp
 * Description
 *
 * Input arguments
 *
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
static VOID _mmp_main_rc_resume_wzd_in_mmp(VOID*                       pv_tag1,
                                  VOID*                       pv_tag2,
                                  VOID*                       pv_tag3,
                                  VOID*                       pv_tag4)
{
    ICL_CUSTOM_RESUME_NEXT_APP_T e_next_app = (ICL_CUSTOM_RESUME_NEXT_APP_T) (((UINT32) pv_tag1) & 0x0000FFFF);

#ifdef DEBUG
   DBG_LOG_PRINT(("\n%s,%d,e_next_app=%d\n",
                __FILE__, __LINE__, (UINT32)e_next_app));
#endif

    if (ICL_CUSTOM_RESUME_NEXT_APP_MIRACAST == e_next_app)
    {
        a_amb_resume_app("wfd");
        a_amb_clean_stack();
        return;
    }

    if (ICL_CUSTOM_RESUME_NEXT_APP_WZD_NW == e_next_app)
    {
        a_wzd_resume_network_setting();
    }
    else if (ICL_CUSTOM_RESUME_NEXT_APP_WZD_TUNER_SETUP == e_next_app)
    {
        a_wzd_resume_tv_setup();
    }
    else if (ICL_CUSTOM_RESUME_NEXT_APP_WZD_DEVICE_SETUP == e_next_app)
    {
        if (a_cfg_custom_get_wifi_remote_support())
        {
            a_wzd_resume_tv_remote_device_setup();
        }
    }

    else if(ICL_CUSTOM_RESUME_NEXT_APP_WIFI_WZD_RC == e_next_app)
    {
        if (a_cfg_custom_get_wifi_remote_support())
        {
            a_wzd_resume_tv_remote_pairing_setup();
        }
    }

    c_wgl_img_cache_flush();
    a_amb_clean_stack();
    a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_LAST_ENTRY);
}
//#endif


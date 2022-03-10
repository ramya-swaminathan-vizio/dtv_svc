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
 * $RCSfile: nav_fav_lst.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/118 $
 * $SWAuthor: $
 * $MD5HEX: 74c34b81b9b0a7ed0de302079c3cacb3 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "3d_setting.h"
#include "a_3d_setting.h"
#include "u_drv_cust.h"
#include "nav/sys_info/a_sys_info.h"
#include "menu2/menu_common/menu_common.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

static NAV_3D_SETTING_T     t_g_nav_3d_setting;
static BOOL                 b_g_is_HDMI_src = FALSE;
BOOL                        b_g_is_3RD_3d;

#ifdef CLI_SUPPORT
#ifdef APP_3D_FAC_TEST_SUPPORT

static INT32 _nav_3d_dialog_cli_hide
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_3d_video_playing_cli_check
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_3d_to_2d_cli_fun
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_3d_active_component_cli_fun
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);



static CLI_EXEC_T at_g_nav_3d_cli_cmd_tbl[] =
{
    { "hide_3d_dialog",        "h", _nav_3d_dialog_cli_hide,                   NULL, "hide 3d dialog",                            NAV_CLI_ACCESS_RIGHT_LVL },
    { "check_3d_video",        "c", _nav_3d_video_playing_cli_check,           NULL, "check 3d video playing status",             NAV_CLI_ACCESS_RIGHT_LVL },
    { "3d_to_2d",              "t", _nav_3d_to_2d_cli_fun,                     NULL, "3d to 2d",                                  NAV_CLI_ACCESS_RIGHT_LVL },
    { "3d_comp_active",        "act", _nav_3d_active_component_cli_fun,        NULL, "active 3d component",                       NAV_CLI_ACCESS_RIGHT_LVL },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T t_g_nav_3d_cli_cmd_entry =
{
    "nav_3d_set", NULL, NULL, at_g_nav_3d_cli_cmd_tbl, "nav 3d setting commands", NAV_CLI_ACCESS_RIGHT_LVL
};
/*-----------------------------------------------------------------------------
 * Name: _nav_3d_dialog_cli_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_3d_dialog_cli_hide
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32               i4_ret;

    i4_ret = a_nav_fac_hide_3d_dialog();

    DBG_INFO(("[3d_setting]hide 3d dialog and the return value is: %d !\n", i4_ret));

    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_3d_dialog_cli_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_3d_video_playing_cli_check
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    BOOL     b_is_3d_video_playing = FALSE;
    b_is_3d_video_playing = a_nav_fac_is_3d_video_playing();

    if (b_is_3d_video_playing)
    {
        DBG_INFO(("[3d_setting]3d video is playing!\n"));
    }
    else
    {
        DBG_INFO(("[3d_setting]3d video is not playing!\n"));
    }

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_3d_dialog_cli_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_3d_to_2d_cli_fun
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{

    a_nav_fac_3d_to_2d();

    DBG_INFO(("[3d_setting]3d to 2d!\n"));

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_3d_active_component_cli_fun
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_3d_active_component_cli_fun
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{

    nav_grab_activation(NAV_COMP_ID_3D_SETTING);

    DBG_INFO(("[3d_setting]active the 3d dialog component!\n"));

    return CLIR_OK;
}

#endif
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_ch_num_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _3d_setting_handler_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag)
{
    SI_3D_INFO_T*           pt_3D_info = &pt_si_info->u.t_3D_info;
    VSH_SRC_TAG3D_TYPE_T    e_src_tag_type = 0;
    TV_MODE_T               e_tv_mode = TV_MODE_TYPE_NORMAL;

    if (pt_3D_info->ui4_info_mask & SI_3D_SRC_TAG_INFO_MASK)
    {
        a_tv_get_mode(&e_tv_mode);
        if (e_tv_mode == TV_MODE_TYPE_POP || e_tv_mode == TV_MODE_TYPE_PIP)  /* PIP/POP Mode*/
        {
            DBG_INFO(("[3D setting] --- PIP/POP: Video update, mode: %d.\n", e_src_tag_type));

            if (VSH_SRC_TAG3D_2D            != e_src_tag_type &&
                VSH_SRC_TAG3D_NOT_SUPPORT   != e_src_tag_type &&
                VSH_SRC_TAG3D_TTDO          != e_src_tag_type)
            {
                DBG_INFO(("[3d setting] ---- PIP/POP detect 3D, switch to 2D mode. ---\n"));
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE), (INT16)APP_CFG_3D_MODE_AUTO);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

                /* 3D to 2D*/
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D), (INT16 )APP_CFG_3D_TO_2D_LEFT);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));
            }

            return NAVR_OK;
        }

        if (b_g_is_HDMI_src == FALSE)   /* only detect 3D content in HDMI input source*/
        {
            return NAVR_OK;
        }

        e_src_tag_type = pt_3D_info->t_src_tag_info.e_src_tag3D_type;
        DBG_LOG_PRINT(("\n<3D setting> ------- %s, %d.pre tag:%d, SRC tag:%d. -------\n",
                        __FUNCTION__, __LINE__,
                        t_g_nav_3d_setting.e_pre_tag_type, e_src_tag_type));

        /*if current TAG is 3D , and pre TAG is non-3D, should popup  a auto-detect dialog*/
        if (VSH_SRC_TAG3D_2D            != e_src_tag_type &&
            VSH_SRC_TAG3D_NOT_SUPPORT   != e_src_tag_type &&
            VSH_SRC_TAG3D_TTDO          != e_src_tag_type )
        {
            if (VSH_SRC_TAG3D_2D            == t_g_nav_3d_setting.e_pre_tag_type ||
                VSH_SRC_TAG3D_NOT_SUPPORT   == t_g_nav_3d_setting.e_pre_tag_type ||
                VSH_SRC_TAG3D_TTDO          == t_g_nav_3d_setting.e_pre_tag_type )
            {
                nav_grab_activation(NAV_COMP_ID_3D_SETTING);
                t_g_nav_3d_setting.e_pre_tag_type = e_src_tag_type;
            }
        }
        else
        {
            t_g_nav_3d_setting.e_pre_tag_type = e_src_tag_type;
        }
    }

    if (pt_3D_info->ui4_info_mask & SI_3D_MODE_INFO_MASK)
    {
        DBG_LOG_PRINT(("\n<3D setting> ------- %s, %d. Mode:%d, 3D_TO_2D:%d . -------\n",
                        __FUNCTION__, __LINE__,
                        pt_3D_info->t_3d_mode_info.i2_3D_mode,
                        pt_3D_info->t_3d_mode_info.i2_3D_to_2D));
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _3d_seting_sys_info_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _3d_seting_sys_info_handler (
                                            SI_INFO_CTRL_T              e_info_ctrl ,
                                            TV_WIN_ID_T                 e_tv_win_id ,
                                            SI_SET_INFO_T*              pt_si_info ,
                                            VOID*                       pv_tag)
{
    /* check validate */
    if (!pt_si_info)
    {
        return NAVR_INV_ARG;
    }

    /* as sys info module is one of navigator's component, we need not change the thread */

    /* switch to sub-handler */
    switch (pt_si_info->e_category)
    {
    case SI_CATEGORY_3D_MODE_INFO:
        _3d_setting_handler_info(e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag);
        break ;
    default :
        /* Do nothing */
        break ;
    }

    return NAVR_OK ;
}

static INT32 _3d_setting_sys_info_handler_init(VOID)
{
    INT32   i4_ret = NAVR_OK;
    UINT16                      ui2_si_listener_id = 0;

    i4_ret = a_si_listener_register (_3d_seting_sys_info_handler,
                            NULL ,
                            &ui2_si_listener_id);
    DBG_INFO(("i4_ret=%d\n",i4_ret));

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_3d_setting_handle_msg
* Description  -
* Input        -
* Output       -
* Returns      -
*-----------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_handle_msg(NAV_CONTEXT_T* pt_ctx,
                                  NAV_UI_MSG_T*  pt_ui_msg,
                                  VOID*          pv_arg1)
{
    INT32               i4_ret;
    NAV_3D_SETTING_T*   pt_this = &t_g_nav_3d_setting;
    ISL_REC_T           t_isl_rec = {0};
    NAV_XNG_SRC_TRGT_T* pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;
    BOOL                b_same_channel = FALSE;
    HANDLE_T                h_svctx = NULL_HANDLE;
    TV_MODE_T               e_tv_mode = TV_MODE_TYPE_NORMAL;
    NAV_STREAM_NOTIFY_DATA_T*       pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;
    VSH_SRC_RESOLUTION_INFO_T       t_src_res = {0};

    switch (pt_ui_msg->e_id)
    {
    	case NAV_UI_MSG_OTHER_APP_RESUMED:
            /* If next APP is not MENU, init var. */
            if (c_strcmp ((CHAR*)pv_arg1, MENU_NAME) != 0)
            {
            	pt_this->b_is_on      = FALSE;
                pt_this->e_pre_tag_type = VSH_SRC_TAG3D_2D;
            }
        	break;
        case NAV_UI_MSG_APP_PRE_RESUME:
            break;
        case NAV_UI_MSG_POWER_ON:
            break;
        case NAV_UI_MSG_APP_INITED:
            _3d_setting_sys_info_handler_init();
            break;
        case NAV_UI_MSG_NO_SIGNAL:
            /*No signal, the 3D mode will reset*/
            pt_this->e_pre_tag_type = VSH_SRC_TAG3D_NOT_SUPPORT;
            break;

        case NAV_UI_MSG_APP_RESUMED:
            menu_get_crnt_isl(&t_isl_rec);
            if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
            {
                b_g_is_HDMI_src = TRUE;
            }
            else
            {
                b_g_is_HDMI_src = FALSE;
            }
            break;
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:

            i4_ret = a_isl_get_rec_by_id(pt_xng_info->u.t_av.ui1_trgt_inp_src_id, &t_isl_rec);

            if (i4_ret != ISLR_OK)
            {
                b_g_is_HDMI_src = FALSE;
                break;
            }

            /*TV:  change channel, reset 3D mode*/
            if (pt_xng_info->e_type == INP_SRC_TYPE_TV)
            {
                b_same_channel = nav_is_same_channel(
                            pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                            pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                            pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                            pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                            pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                            pt_xng_info->u.t_tv.ui4_trgt_channel_id
                            );
                if (!b_same_channel)
                {
                    a_cfg_custom_3D_setting_reset_3D_mode();
                }

                return NAVR_OK;
            }

            /*change input source, reset 3D mode */
            if (!pt_xng_info->b_same_src_trgt)
            {
                pt_this->e_pre_tag_type = VSH_SRC_TAG3D_NOT_SUPPORT;
                a_cfg_custom_3D_setting_reset_3D_mode();
            }

            /* AV */
            if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
            {
                b_g_is_HDMI_src = TRUE;
            }
            else
            {
                b_g_is_HDMI_src = FALSE;
            }

            break;

        case NAV_UI_MSG_AS_APP_PAUSED:
        {
            if (NAV_UI_MSG_BEFORE_SVC_CHANGE == pt_ui_msg->e_id_as_paused)
            {
                i4_ret = a_isl_get_rec_by_id(pt_xng_info->u.t_av.ui1_trgt_inp_src_id, &t_isl_rec);
                if (i4_ret != ISLR_OK)
                {
                    b_g_is_HDMI_src = FALSE;
                    break;
                }

                /*TV:  change channel, reset 3D mode*/
                if (pt_xng_info->e_type == INP_SRC_TYPE_TV)
                {
                    b_same_channel = nav_is_same_channel(
                                pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                                pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                                pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                                pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                                pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                                pt_xng_info->u.t_tv.ui4_trgt_channel_id
                                );
                    if (!b_same_channel)
                    {
                        a_cfg_custom_3D_setting_reset_3D_mode();
                    }

                    return NAVR_OK;
                }

                /* change input source, reset 3D mode */
                if (!pt_xng_info->b_same_src_trgt)
                {
                    pt_this->e_pre_tag_type = VSH_SRC_TAG3D_NOT_SUPPORT;
                    a_cfg_custom_3D_setting_reset_3D_mode();
                }

                /* AV */
                if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
                {
                    b_g_is_HDMI_src = TRUE;

                    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                                                 (INT16)APP_CFG_3D_MODE_AUTO);
                }
                else
                {
                    b_g_is_HDMI_src = FALSE;
                }

                break;
            }

            if (NAV_UI_MSG_STREAM_NOTIFY == pt_ui_msg->e_id_as_paused)
            {
                a_tv_get_mode(&e_tv_mode);
                if (ST_VIDEO == pt_nfy_data->e_strm_type &&
                    NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type)
                {
                    i4_ret = nav_get_svctx_handle(pt_ui_msg->e_tv_win_id, &h_svctx);
                    if (i4_ret != NAVR_OK) {
                        return i4_ret;
                    }

                    i4_ret = c_svctx_get_video_src_resolution(h_svctx, &t_src_res);
                    if (i4_ret != NAVR_OK) {
                        return i4_ret;
                    }

                    if (VSH_SRC_TAG3D_2D            != t_src_res.e_src_tag3d_type &&
                        VSH_SRC_TAG3D_NOT_SUPPORT   != t_src_res.e_src_tag3d_type &&
                        VSH_SRC_TAG3D_TTDO          != t_src_res.e_src_tag3d_type)
                    {
                        /*when 3RD playing 3D, show dialog*/
                        if (VSH_SRC_TAG3D_2D == pt_this->e_pre_tag_type ||
                            VSH_SRC_TAG3D_NOT_SUPPORT == pt_this->e_pre_tag_type ||
                            VSH_SRC_TAG3D_TTDO == pt_this->e_pre_tag_type)
                        {
                            if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
                            {
                                b_g_is_3RD_3d = TRUE;
                                nav_grab_activation(NAV_COMP_ID_3D_SETTING);
                            }
                            else
                            {
                                b_g_is_3RD_3d = FALSE;
                            }
                        }

                        DBG_LOG_PRINT(("\n[nav 3D setting] --- stream updated, 3d mode: %d.\n", t_src_res.e_src_tag3d_type));
                        if (e_tv_mode == TV_MODE_TYPE_POP || e_tv_mode == TV_MODE_TYPE_PIP)  /* PIP/POP Mode*/
                        {
                            DBG_LOG_PRINT(("\n<3d setting 2> ---- PIP/POP detect 3D, switch to 2D mode. ---\n"));
                            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE), (INT16)APP_CFG_3D_MODE_AUTO);
                            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

                            /* 3D to 2D*/
                            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D), (INT16 )APP_CFG_3D_TO_2D_LEFT);
                            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));
                        }
                        else
                        {
                            if (VSH_SRC_TAG3D_2D == pt_this->e_pre_tag_type ||
                                VSH_SRC_TAG3D_NOT_SUPPORT == pt_this->e_pre_tag_type ||
                                VSH_SRC_TAG3D_TTDO == pt_this->e_pre_tag_type)
                            {
                                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                                                 (INT16)APP_CFG_3D_MODE_AUTO);
                            #ifdef LINUX_TURNKEY_SOLUTION
                                if(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
                                {
                                    DBG_LOG_PRINT(("\n[nav 3D setting] --- update to 3D_MODE_AUTO in APP_TV_NET_SVC_STATUS_RESUMED.\n"));
                                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));
                                }
                            #endif
                                pt_this->e_pre_tag_type = t_src_res.e_src_tag3d_type;
                            }
                        }
                    }
                    else
                    {
                        pt_this->e_pre_tag_type = t_src_res.e_src_tag3d_type;
                    }
                }
            }
        }
        break;

        default:
            break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_3d_setting_is_key_handler
* Description
* Input arguments
* Output arguments
* Returns  -
*---------------------------------------------------------------------------*/
static BOOL _nav_3d_setting_is_key_handler(NAV_CONTEXT_T*  pt_ctx,
                                         UINT32          ui4_key_code)
{
    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_init(NAV_CONTEXT_T* pt_ctx)
{
    NAV_3D_SETTING_T*           pt_this = &t_g_nav_3d_setting;
    INT32                       i4_ret = NAVR_OK;

    c_timer_create(&pt_this->h_timer);


    pt_this->b_is_on      = FALSE;
    pt_this->b_grab_activation = FALSE;

    i4_ret = pt_this->t_view_hdlr.pf_init(pt_ctx->t_gui_res.h_canvas,
                                          pt_ctx->t_gui_res.i4_x_offset,
                                          pt_ctx->t_gui_res.i4_y_offset
                                          );
    pt_this->e_pre_tag_type = 0;


#ifdef CLI_SUPPORT
#ifdef APP_3D_FAC_TEST_SUPPORT
        nav_register_comp_cli_entry (&t_g_nav_3d_cli_cmd_entry);
#endif
#endif

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_deinit(VOID)
{
    NAV_3D_SETTING_T* pt_this = &t_g_nav_3d_setting;

    pt_this->t_view_hdlr.pf_deinit();
    pt_this->b_is_on      = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_activate(NAV_CONTEXT_T*   pt_ctx,
                                       UINT32           ui4_key_code)
{
    NAV_3D_SETTING_T* pt_this = &t_g_nav_3d_setting;
    INT32        i4_ret = NAVR_OK;

    DBG_LOG_PRINT(("\n[nav 3D setting] --- _nav_3d_setting_activate\n"));

    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }
    nav_set_component_visible(NAV_COMP_ID_3D_SETTING);

    pt_this->b_is_on = TRUE;
    pt_this->b_grab_activation = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_on_timer_ch_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_inactivate(NAV_CONTEXT_T* pt_ctx)
{
    NAV_3D_SETTING_T* pt_this = &t_g_nav_3d_setting;
    INT32        i4_ret;

    DBG_LOG_PRINT(("\n[nav 3D setting] --- _nav_3d_setting_inactivate\n"));

    i4_ret = pt_this->t_view_hdlr.pf_hide();
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_hide(VOID)
{
    NAV_3D_SETTING_T* pt_this = &t_g_nav_3d_setting;

    if (pt_this->b_is_on == FALSE)
    {
        return NAVR_NO_ACTION;
    }

    pt_this->b_is_on = FALSE;

    nav_return_activation(NAV_COMP_ID_3D_SETTING);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
* public methods implementations
*---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
* Name
*      a_nav_retail_mode_register
* Description
* Input arguments
* Output arguments
* Returns  -
*---------------------------------------------------------------------------*/
INT32 a_nav_3d_setting_register(
                            NAV_3D_SETTING_VIEW_HDLR_T*       pt_view_hdlr)
{
    NAV_3D_SETTING_T*       pt_this = &(t_g_nav_3d_setting);
    NAV_COMP_T              t_comp;
    INT32                   i4_ret;
    BOOL                    b_is_support_3D = FALSE;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _nav_3d_setting_init;
    t_comp.pf_deinit         = _nav_3d_setting_deinit;
    t_comp.pf_is_key_handler = _nav_3d_setting_is_key_handler;
    t_comp.pf_activate       = _nav_3d_setting_activate;
    t_comp.pf_inactivate     = _nav_3d_setting_inactivate;
    t_comp.pf_hide           = _nav_3d_setting_hide;
    t_comp.pf_handle_msg     = _nav_3d_setting_handle_msg;

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        a_cfg_custom_plf_opt_get_3d_support(&b_is_support_3D);
    }
    if (b_is_support_3D)
    {
        i4_ret = nav_register_component(NAV_COMP_ID_3D_SETTING, &t_comp, COMP_EXEC_SET_3D_SETTING);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        if (pt_view_hdlr == NULL) {
            nav_3d_setting_view_register_default_hdlr(&pt_this->t_view_hdlr);
        } else {
            pt_this->t_view_hdlr = *pt_view_hdlr;
        }
    }
    return NAVR_OK;
}

#ifdef APP_3D_FAC_TEST_SUPPORT
/*-----------------------------------------------------------------------------
* Name
*      a_nav_fac_hide_3d_dialog
* Description
* Input arguments
* Output arguments
* Returns  -
*---------------------------------------------------------------------------*/
INT32 a_nav_fac_hide_3d_dialog( VOID )
{

    /* hide the component first if this component is visible, also this will hide the UI of this component*/
    if (nav_is_component_visible(NAV_COMP_ID_3D_SETTING))
    {
        nav_hide_component(NAV_COMP_ID_3D_SETTING);
    }

    /* here will set the 3d mode to auto, and enable 3d*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE), (INT16)APP_CFG_3D_MODE_AUTO);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D), (INT16 )APP_CFG_3D_TO_2D_OFF);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
* Name
*      a_nav_fac_hide_3d_dialog
* Description
* Input arguments
* Output arguments
* Returns  -
*---------------------------------------------------------------------------*/
BOOL a_nav_fac_is_3d_video_playing( VOID )
{
    TV_WIN_ID_T                     e_focused_win_id = TV_WIN_ID_MAIN ;
    VSH_SRC_RESOLUTION_INFO_T       t_src_res = {0};
    HANDLE_T                        h_svctx = NULL_HANDLE;
    INT32                           i4_ret;

    i4_ret = nav_get_focus_id (&e_focused_win_id) ;
    if (i4_ret != NAVR_OK) {
        return FALSE;
    }

    i4_ret = nav_get_svctx_handle(e_focused_win_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return FALSE;
    }

    i4_ret = c_svctx_get_video_src_resolution(h_svctx, &t_src_res);
    if (i4_ret != NAVR_OK) {
        return FALSE;
    }


    /* check if it is a valid timing */
    if(t_src_res.ui4_width != 0  &&
       t_src_res.ui4_height != 0 &&
       t_src_res.ui4_frame_rate != 0)
    {
        if (a_tv_custom_is_3D_mode_playing())
        {
            return TRUE;
        }
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
* Name
*      a_nav_fac_3d_to_2d
* Description
* Input arguments
* Output arguments
* Returns  -
*---------------------------------------------------------------------------*/
INT32 a_nav_fac_3d_to_2d( VOID )
{

    /* here will set the 3d mode to auto, and enable 3d*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE), (INT16)APP_CFG_3D_MODE_AUTO);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D), (INT16 )APP_CFG_3D_TO_2D_LEFT);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
* exported methods implementations
*---------------------------------------------------------------------------*/


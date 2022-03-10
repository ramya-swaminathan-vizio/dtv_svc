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
 * $RCSfile: nav_cec_view_rc.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_wgl_image.h"

#include "nav/nav_common.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_view.h"
#include "res/nav/cec2/nav_cec_view_rc.h"
#include "res/nav/nav_dbg.h"


#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define COLOR_INDEX_DIS_TEXT (51)
/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
#if 0
static NAV_CEC_CMD_T at_cec_cmd_rec [] = {
    CEC_CMD_STANDBY,
    CEC_CMD_POWER_ON
    };
static NAV_CEC_CMD_T at_cec_cmd_play [] = {
    CEC_CMD_STANDBY,
    CEC_CMD_POWER_ON
    };
#else
static NAV_CEC_CMD_T at_cec_cmd_rec [] = {
    CEC_CMD_STANDBY,
    CEC_CMD_POWER_ON,
    CEC_CMD_RECORD,
    CEC_CMD_DECK_CTRL,
    CEC_CMD_MENU
    };
static NAV_CEC_CMD_T at_cec_cmd_play [] = {
    CEC_CMD_STANDBY,
    CEC_CMD_POWER_ON,
    CEC_CMD_DECK_CTRL,
    CEC_CMD_MENU
    };
#endif
static NAV_CEC_CMD_T at_cec_cmd_audio_sys [] = {
    CEC_CMD_STANDBY,
    CEC_CMD_POWER_ON,
    CEC_CMD_SAC_SWITCH
    };
static NAV_CEC_CMD_T at_cec_cmd_setup [] = {
    CEC_CMD_CEC_FUNC_OFF,
    CEC_CMD_AUTO_OFF_ON,
    CEC_CMD_MANUAL_DEV_SCAN
    };
/*-----------------------------------------------------------------------------
                    private function implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    public function implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:    nav_cec_view_init_rc_status_txt
 * Description: Initialize RC for status text of cec view.
 * Input:   pt_rc       A pointer to NAV_CEC_VIEW_RC_STATUS_TXT_T.
 * Output:  -
 * Returns: NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_cec_view_init_rc_status_txt (
    NAV_CEC_VIEW_RC_STATUS_TXT_T* pt_rc_status_txt
    )
{
    INT32 i4_ret;

    /* For status text. */
    i4_ret = nav_img_create_default_bk_img_tpl (&pt_rc_status_txt->h_status_txt_bk_img);
    IS_CECR_OK(i4_ret);

    pt_rc_status_txt->t_txt_fg_clr = NAV_COLOR(NAV_COLOR_ID_TEXT);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:    nav_cec_view_deinit_rc_status_txt
 * Description: Deinitialize RC for status text of cec view.
 * Input:   pt_rc       A pointer to NAV_CEC_VIEW_RC_STATUS_TXT_T.
 * Output:  -
 * Returns: NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_cec_view_deinit_rc_status_txt (
    NAV_CEC_VIEW_RC_STATUS_TXT_T* pt_rc_status_txt
    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_img_tpl_destroy (pt_rc_status_txt->h_status_txt_bk_img);
    IS_CECR_OK(i4_ret);

    pt_rc_status_txt->h_status_txt_bk_img        = NULL_HANDLE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:    nav_cec_view_init_rc
 * Description: Initialize RC for cec view.
 * Input:   pt_rc       A pointer to NAV_CEC_VIEW_RC_T.
 * Output:  -
 * Returns: NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_cec_view_init_rc (
    NAV_CEC_VIEW_RC_T* pt_rc
    )
{
    INT32 i4_ret;
    /*
     *  Use the same image as the channel list. The mapping is:
     *  Major <--> Device list, Minor <--> Command list
     */
    i4_ret = nav_img_create_hlt_bar_bk_img_tpl (&pt_rc->h_dev_lst_elem_hlt_bk_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_create_ch_list_bk_img_tpl (&pt_rc->h_dev_lst_bk_img);
    IS_CECR_OK(i4_ret);

    /* FIXME!! */
    i4_ret = nav_img_create_hlt_bar_bk_img_tpl (&pt_rc->h_cmd_lst_elem_hlt_bk_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_cmd_list_bk_img_tpl (&pt_rc->h_cmd_lst_bk_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_act_src_icon_img (&pt_rc->h_dev_lst_lb_act_src_img);
    IS_CECR_OK(i4_ret);

    pt_rc->t_elm_normal_fg_clr = NAV_COLOR(NAV_COLOR_ID_TEXT);
    pt_rc->t_elm_hlt_fg_clr = NAV_COLOR(NAV_COLOR_ID_TEXT_HLT);
    pt_rc->t_elm_dis_fg_clr = NAV_COLOR(NAV_COLOR_ID_POP_BLUR);
    pt_rc->t_elm_bk_clr = APP_COLOR (APP_COLOR_TYPE_BLUE, APP_COLOR_ITEM_CONTENT);
    pt_rc->t_lb_bk_clr = NAV_COLOR(NAV_COLOR_ID_TRANS);
    pt_rc->t_title_fg_clr = NAV_COLOR(NAV_COLOR_ID_TEXT);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:    nav_cec_view_deinit_rc
 * Description: Deinitialize RC for cec view.
 * Input:   pt_rc       A pointer to NAV_CEC_VIEW_RC_T.
 * Output:  -
 * Returns: NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_cec_view_deinit_rc (
    NAV_CEC_VIEW_RC_T* pt_rc
    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_img_tpl_destroy (pt_rc->h_dev_lst_elem_hlt_bk_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_rc->h_dev_lst_bk_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_rc->h_cmd_lst_elem_hlt_bk_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_rc->h_cmd_lst_bk_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_rc->h_dev_lst_lb_act_src_img);
    IS_CECR_OK(i4_ret);

    pt_rc->h_dev_lst_elem_hlt_bk_img        = NULL_HANDLE;
    pt_rc->h_dev_lst_bk_img                 = NULL_HANDLE;
    pt_rc->h_cmd_lst_elem_hlt_bk_img        = NULL_HANDLE;
    pt_rc->h_cmd_lst_bk_img                 = NULL_HANDLE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:    nav_cec_view_rc_get_cmd_by_type
 * Description: Get available commands for the specified device type.
 * Input:   e_dev_type      CEC device type.
 * Output:  pui1_cmd_num    Number of elements of paui1_cmd.
 *          ppt_cec_cmd     Command array for the given device type.
 * Returns: NAVR_OK     This function executed successfully.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_cec_view_rc_get_cmd_by_type (
    NAV_CEC_DEV_TYPE_T e_dev_type,
    UINT8* pui1_cmd_num,
    NAV_CEC_CMD_T** ppt_cec_cmd
    )
{
    switch (e_dev_type)
    {
    case DEV_TYPE_PLAYBACK:
        *ppt_cec_cmd = at_cec_cmd_play;
        *pui1_cmd_num = (UINT8) (sizeof (at_cec_cmd_play) / sizeof (at_cec_cmd_play[0]));
        break;
    case DEV_TYPE_RECORDING:
        *ppt_cec_cmd = at_cec_cmd_rec;
        *pui1_cmd_num = (UINT8) (sizeof (at_cec_cmd_rec) / sizeof (at_cec_cmd_rec[0]));
        break;
    case DEV_TYPE_AUDIO_SYSTEM:
        *ppt_cec_cmd = at_cec_cmd_audio_sys;
        *pui1_cmd_num = (UINT8) (sizeof (at_cec_cmd_audio_sys) / sizeof (at_cec_cmd_audio_sys[0]));
        break;
    case DEV_TYPE_SETUP:
        *ppt_cec_cmd = at_cec_cmd_setup;
        *pui1_cmd_num = (UINT8) (sizeof (at_cec_cmd_setup) / sizeof (at_cec_cmd_setup[0]));
        break;
    default:
        return NAVR_FAIL;
    }
    return NAVR_OK;
}


/* For deck control. */
INT32  nav_cec_deck_ctrl_init_rc (
    NAV_CEC_DECK_CTRL_RC_T* pt_deck_ctrl_rc
    )
{
    INT32 i4_ret;

    i4_ret = nav_img_cec_create_deck_panel_img(&pt_deck_ctrl_rc->h_ctrl_pnl_frm_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_eject_img (&pt_deck_ctrl_rc->h_ctrl_pnl_eject_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_play_img (&pt_deck_ctrl_rc->h_ctrl_pnl_play_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_pause_img (&pt_deck_ctrl_rc->h_ctrl_pnl_pause_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_stop_img (&pt_deck_ctrl_rc->h_ctrl_pnl_stop_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_fast_forward_img (&pt_deck_ctrl_rc->h_ctrl_pnl_fast_forward_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_fast_reverse_img (&pt_deck_ctrl_rc->h_ctrl_pnl_fast_reverse_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_skip_forward_img (&pt_deck_ctrl_rc->h_ctrl_pnl_skip_forward_img);
    IS_CECR_OK(i4_ret);

    i4_ret = nav_img_cec_create_skip_reverse_img (&pt_deck_ctrl_rc->h_ctrl_pnl_skip_reverse_img);
    IS_CECR_OK(i4_ret);

    pt_deck_ctrl_rc->t_ctrl_pnl_icon_border_clr = NAV_COLOR(NAV_COLOR_ID_ORANGE);

    return NAVR_OK;
}
INT32  nav_cec_deck_ctrl_deinit_rc (
    NAV_CEC_DECK_CTRL_RC_T* pt_deck_ctrl_rc
    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_eject_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_play_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_pause_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_stop_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_fast_forward_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_fast_reverse_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_skip_forward_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_skip_reverse_img);
    IS_CECR_OK(i4_ret);

    i4_ret = c_wgl_img_tpl_destroy (pt_deck_ctrl_rc->h_ctrl_pnl_frm_img);
    IS_CECR_OK(i4_ret);

    pt_deck_ctrl_rc->h_ctrl_pnl_frm_img             = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_eject_img           = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_play_img            = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_stop_img            = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_pause_img           = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_fast_forward_img    = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_fast_reverse_img    = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_skip_forward_img    = NULL_HANDLE;
    pt_deck_ctrl_rc->h_ctrl_pnl_skip_reverse_img    = NULL_HANDLE;

    return NAVR_OK;
}

#endif /* APP_NAV_CEC_SUPPORT */
#endif /* APP_NAV_CEC_SUPPORT */


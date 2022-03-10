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
 * $RCSfile: usb_pld.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *       USB Plug Detection.
 *
 *---------------------------------------------------------------------------*/
#include <time.h>
#ifdef APP_NAV_USB_PLD
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_fm.h"
#include "c_fm.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_cfg.h"
#include <stdio.h>
#include "u_pcl.h"
#include "c_pcl.h"

#include "app_client.h"
#include "res/nav/nav_variant.h"
#include "app_util/a_cfg.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/a_navigator.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/nav/nav_view.h"
#include "wizard_anim/a_wzd.h"
#include "nav/banner2/a_banner.h"
#include "res/nav/nav_variant_custom.h"
#include "nav/usb_pld/nav_usb_pld.h"
#include "nav/usb_pld/nav_usb_pld_view.h"
#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "menu2/a_menu.h"
#include "rest/a_rest_event.h"

#include "u_device_type.h"
#include "app_util/a_isl.h"
#include "rest/a_rest_api.h"
#include "app_util/config/acfg_tv.h"
#include "msgconvert/msgconvert.h"
#include "res/nav/nav_dbg.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define RET_ON_ERR(_expr)  \
if(_expr != 0)\
{\
    DBG_ERROR (("<NAV_USB_PLD> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
    return _expr;\
}

#define NAV_UPGRADE_FILE            "/upgrade.pkg"
#define NAV_UPDATE_LOGIC_FILE       "/updatelogic.txt"

#ifdef APP_CAST_TV_MMP
#define NAV_USB_PLD_DLG_POWER_ON_TIMER_DELAY     10 /* sec */
#else
#define NAV_USB_PLD_DLG_POWER_ON_TIMER_DELAY     25 /* sec */
#endif

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_USB_PLD_HDLR_T t_g_nav_usb_pld = {0};
static UINT32   ui4_g_usb_dev_num = 0;
static BOOL     b_g_enable_usb_pop_up_dialog = TRUE;
static BOOL     b_g_show_dialog_delay = FALSE;
static BOOL     b_g_fac_set_respone_usb_disable= FALSE;

#ifdef APP_CAST_TV_MMP
static BOOL     b_g_is_retail_mode = FALSE;
#endif
struct timespec power_on_start;
BOOL b_isPowerOn = FALSE;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _nav_usb_pld_rmv_dev_nfy(
                    VOID*               pv_tag,
                    RMV_DEV_NFY_ID_T    e_nfy_id,
                    VOID*               pv_nfy_param);

static VOID _nav_usb_pld_rmv_dev_nfy_handler(
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3);

static INT32 _nav_usb_pld_module_entry(VOID);

static INT32 _nav_usb_pld_module_leave(VOID);

static INT32 _nav_usb_pld_hide (VOID);

static BOOL nav_custom_usb_dlg_check_special_file(CHAR* ps_path);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static BOOL nav_custom_usb_dlg_check_special_file(CHAR* ps_path)
{
    CHAR            ac_path_fac[128] = {0};
    HANDLE_T        h_file_open = NULL_HANDLE;
    INT32           i4_ret;

    c_strcpy(ac_path_fac, ps_path);
    c_strcat(ac_path_fac, "/FT_USB_AUTO_DISABLE_BREAK_IN_FILE.bin");

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       ac_path_fac,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_file_open);


    if(NAVR_OK == i4_ret)
    {
        c_fm_close(h_file_open);
        return TRUE;
    }
    else
    {
        c_fm_close(h_file_open);
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_init
 * Description:
 *      USB detection module initialization.
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_init(NAV_CONTEXT_T*   pt_ctx)
{
    NAV_USB_PLD_HDLR_T* pt_this = &t_g_nav_usb_pld;
    INT32               i4_ret = NAVR_OK;

    pt_this->pt_ctx = pt_ctx;

    /* register remove device notification function */
    i4_ret = a_rmv_dev_reg_monitor(
                    _nav_usb_pld_rmv_dev_nfy,
                    NULL,
                    &pt_this->ui4_rmv_dev_nfy);
    RET_ON_ERR(i4_ret);

    /* initialize view */
    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_this->pt_ctx->t_gui_res.h_canvas);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_deinit
 * Description:
 *      USB detection module deinitialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_deinit(VOID)
{
    NAV_USB_PLD_HDLR_T* pt_this = &t_g_nav_usb_pld;
    INT32               i4_ret = NAVR_OK;

    /* unregister remove device notification function */
    i4_ret = a_rmv_dev_unreg_monitor(pt_this->ui4_rmv_dev_nfy);
    RET_ON_ERR(i4_ret);

    /* deinitialize view */
    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_is_key_handler
 * Description:
 *
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *
 *---------------------------------------------------------------------------*/
static BOOL _nav_usb_pld_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code)
{
    NAV_USB_PLD_HDLR_T* pt_this = &t_g_nav_usb_pld;

#ifdef APP_CAST_TV_MMP
    if(BTN_TTX == ui4_key_code)
    {
        a_mmp_request_operation(MMP_REQ_OP_ENTER_VIDEO_BWR);
        return FALSE;
    }
#endif

    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_activate
 * Description:
 *      USB detection module activation.
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_activate(
                    NAV_CONTEXT_T*             pt_ctx,
                    UINT32                     ui4_key_code)
{
    nav_set_component_visible(NAV_COMP_ID_USB_PLD);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_inactivate
 * Description:
 *      USB detection module inactivation.
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_inactivate(NAV_CONTEXT_T*     pt_ctx)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_handle_msg
 * Description:
 *      USB detection module message handle function.
 * Input arguments:
 *      pt_ctx
 *      pt_ui_msg
 *      pv_arg1
 * Output arguments:
 *
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1)
{
    switch (pt_ui_msg->e_id)
    {
    /* NAV_UI_MSG_SYSTEM_POWER_ON ,nav maybe not resume, fix DTV00830304 */
    case NAV_UI_MSG_SYSTEM_POWER_ON:
    case NAV_UI_MSG_POWER_ON:
    {
    #ifdef APP_CAST_TV_MMP
        if(a_mmp_get_power_exit_video_state())
        {
            a_mmp_set_power_exit_video_state(FALSE);
        }
    #endif

        power_on_start.tv_sec = 0;
        power_on_start.tv_nsec = 0;
        clock_gettime(CLOCK_MONOTONIC, &power_on_start);
        b_isPowerOn = TRUE;
        break;
    }
#if defined(APP_SUPPORT_STR_CORE_OFF)
    case NAV_UI_MSG_POWER_OFF:
    {
        b_isPowerOn = FALSE;
    }
        break;
#endif
    case NAV_UI_MSG_APP_RESUMED:
        break;
    case NAV_UI_MSG_APP_PRE_RESUME:
        break;
    case NAV_UI_MSG_APP_PAUSING:
    {
        nav_return_activation(NAV_COMP_ID_USB_PLD);
    }
        break;
    case NAV_UI_MSG_EXTERNAL_CTRL_BEGIN:
        break;
    case NAV_UI_MSG_EXTERNAL_CTRL_END:
        break;
    case NAV_UI_MSG_AS_APP_PAUSED:
    {
        /*show USB Dialog again after menu paused from blank screen*/
        if (b_g_show_dialog_delay && NAV_UI_MSG_OTHER_APP_PAUSED == pt_ui_msg->e_id_as_paused)
        {
            b_g_show_dialog_delay = FALSE;

            c_thread_delay(200);
            nav_request_context_switch(_nav_usb_pld_rmv_dev_nfy_handler,
                                                    (VOID*)RMV_DEV_NFY_ID_DEVICE_INSERTED,
                                                    NULL,
                                                    NULL);
        }
        break;
    }
    default:
        break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_hide
 * Description:
 *      USB detection module hide.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_hide (VOID)
{
    NAV_USB_PLD_HDLR_T*   pt_this = &t_g_nav_usb_pld;
    INT32                 i4_ret = NAVR_OK;

    /* hide the view*/
    i4_ret = pt_this->t_view_hdlr.pf_hide();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_is_skype_FULLSCREEN
 * Description:
 *      should not popup USB detect dialog in skype.FULLSCREEN
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      TRUE    skype.FULLSCREEN is resumed
 *      FALSE   skype.FULLSCREEN is paused
 *---------------------------------------------------------------------------*/
static BOOL _nav_usb_pld_is_skype_FULLSCREEN(VOID)
{
    FILE *  p_fp = NULL;
    BOOL    b_is_fullscreen = FALSE;
    CHAR    c_tmp = 0;

    p_fp = fopen("/tmp/FULLSCREEN", "r");   /* The File path is same in AppManager.cpp*/
    if (NULL == p_fp)
    {
        return b_is_fullscreen;
    }

    c_tmp = (CHAR)fgetc(p_fp);
    if ('1' == c_tmp)   /* '1' means skype.FULLSCREEN is resumed*/
    {
        b_is_fullscreen = TRUE;
    }

    fclose(p_fp);
    return b_is_fullscreen;
}

#ifdef APP_CAST_TV_MMP_FG
static INT32 _nav_usb_pld_chg_inp_src_to_usb(VOID)
{
    UINT8  ui1_index = 0, ui1_src_num = 0;
    ISL_REC_T       t_isl_rec = {0};

    DBG_LOG_PRINT(("<usb_pld> _chg_inp_src_to_usb\n\r"));
    a_isl_get_num_rec(&ui1_src_num);
    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if ( t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_MMP )
        {
            a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
            return NAVR_OK;
        }
    }

#if 0
    TV_WIN_ID_T     t_tv_win_id;
    INT32           i4_ret = NAVR_OK;

    i4_ret = acfg_tv_get_focus_win(&t_tv_win_id);
    RET_ON_ERR(i4_ret);

    i4_ret = nav_change_av_inp_by_id(t_tv_win_id, t_isl_rec.ui1_id, NULL);
    RET_ON_ERR(i4_ret);
#endif
    return NAVR_OK;
}
#endif

static BOOL _nav_usb_pld_has_special_file(UINT32 ui4_mount_count,UINT8 ui1_odm_id,UINT32* pui4_usb_count)
{
    UINT32                   ui4_mount_idx;
    CHAR                     ac_path[128] = {0};
    CHAR                     ac_path_temp[128] = {0};
    HANDLE_T                 h_file_open = NULL_HANDLE;
    RMV_DEV_DEVICE_STATUS_T  e_dev_status;
    SIZE_T                   z_size = 128;

    *pui4_usb_count = 0;

    for (ui4_mount_idx = 0; ui4_mount_idx < ui4_mount_count; ui4_mount_idx++)
    {
        /*query mount point status*/
        if(a_rmv_dev_get_mnt_point_status_by_idx(ui4_mount_idx,&e_dev_status))
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
        {
            continue;
        }

        if(NAVR_OK !=  a_rmv_dev_get_mnt_point(ui4_mount_idx,
                                               &z_size,
                                               ac_path))
        {
            continue;
        }

        do {
            if (2 == ui1_odm_id && TRUE == nav_custom_usb_dlg_check_special_file(ac_path))
            {
                return TRUE;
            }
        } while(0);

        /* check if exsit upgrade file */
        c_strcpy(ac_path_temp, ac_path);
        c_strcat(ac_path, NAV_UPGRADE_FILE);
        c_strcat(ac_path_temp, NAV_UPDATE_LOGIC_FILE);

        if(NAVR_OK == c_fm_open(FM_ROOT_HANDLE,
                               ac_path,
                               FM_READ_ONLY,
                               0777,
                               FALSE,
                               &h_file_open) &&
           NULL_HANDLE != h_file_open)
        {
            c_fm_close(h_file_open);
            return TRUE;
        }

        if(NAVR_OK == c_fm_open(FM_ROOT_HANDLE,
                                ac_path_temp,
                                FM_READ_ONLY,
                                0777,
                                FALSE,
                                &h_file_open) &&
           NULL_HANDLE != h_file_open)
        {
            c_fm_close(h_file_open);
            return TRUE;
        }

        /* any way, count the usb device number */
        (*pui4_usb_count)++;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_time_diff
 * Description:
 *             Calculate the diff between start and end
 * Input arguments:
 *             Start and end time struct
 * Output arguments:
 *
 * Returns:
 *         Diff time struct between start and end
 *---------------------------------------------------------------------------*/
struct timespec _nav_usb_time_diff(struct timespec start, struct timespec end)
{
    struct timespec temp = {0, 0};

    if((end.tv_nsec-start.tv_nsec)<0)
    {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_time_from_power_on
 * Description:
 *             Calculate the diff between power on and current time
 * Input arguments:
 *             NA
 * Output arguments:
 *
 * Returns:
 *         Diff time struct between power on and current time
 *---------------------------------------------------------------------------*/
struct timespec _nav_usb_time_from_power_on()
{
    struct timespec current_time = {0, 0};
    struct timespec temp = {0, 0};

    /* Get current time */
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    temp = _nav_usb_time_diff(power_on_start, current_time);
    return temp;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_time_from_power_on
 * Description:
 *             Calculate the diff between power on and current time
 * Input arguments:
 *             NA
 * Output arguments:
 *
 * Returns:
 *         Diff time struct between power on and current time
 *---------------------------------------------------------------------------*/
 BOOL _nav_usb_is_over_delay_time_after_power_on()
{
    struct timespec diff_time = {0,0};
    diff_time = _nav_usb_time_from_power_on();

    if((diff_time.tv_sec >= NAV_USB_PLD_DLG_POWER_ON_TIMER_DELAY)
     &&(b_isPowerOn == TRUE))
    {
        return TRUE;
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_check_for_response
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *
 *---------------------------------------------------------------------------*/
static BOOL _nav_usb_pld_check_for_response (VOID)
{
    BOOL               b_is_need_response = TRUE;
    NAV_COMP_ID_T      e_comp_id;
    UINT32             ui4_mnt_count = 0;
    INT32              i4_ret;
    AM_CLIENT_STATE    e_status = YAHOO_STATUS_HIDE;
    UINT8              odm_id = 0;
    CHAR               ac_app_name[APP_NAME_MAX_LEN] = {0};
    UINT32             ui4_mnt_point = 0;
    CHAR               dev_name[128] = {0};
    SIZE_T             z_size = 128;

    a_cfg_custom_get_odm_idx(&odm_id);

    if (FALSE == b_g_enable_usb_pop_up_dialog)
    {
        return FALSE;
    }

    /*Vizio Tablet case,don't enter mmp foreground*/
    i4_ret = a_rmv_dev_get_mnt_point(ui4_mnt_point, &z_size, dev_name);
    RET_ON_ERR(i4_ret);
    DBG_LOG_PRINT(("<USB> get dev name:%s\n\r",dev_name));
    if (dev_name[0] != '\0' && c_strcmp(dev_name,"mtp://")== 0)
    {
        return FALSE;
    }
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    RET_ON_ERR(i4_ret);

    if (0 == ui4_mnt_count)
    {
        DBG_LOG_PRINT(("<mmp> %s,%d,has no mount point,should not response \n\r",__FUNCTION__,__LINE__));
        b_is_need_response = FALSE;
    }
    else
    {
        if(_nav_usb_pld_has_special_file(ui4_mnt_count,odm_id,&ui4_g_usb_dev_num) ||
           ui4_g_usb_dev_num == 0)
        {
             DBG_LOG_PRINT(("<mmp> %s,%d,has special file in usb or has no usb devs,should not response \n\r",__FUNCTION__,__LINE__));
            b_is_need_response = FALSE;
        }

#ifdef APP_RETAIL_MODE_SUPPORT
        {
            ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            DBG_LOG_PRINT(("<mmp> %s,%d,mode:%d\n\r",__FILE__,__LINE__,t_retail_mode));
            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                DBG_LOG_PRINT(("<mmp> %s,%d,current is retail mode,should not response \n\r",__FUNCTION__,__LINE__));
                b_is_need_response = FALSE;
            }
        }
#endif
        /* running in OOBE */
        if(a_wzd_is_oobe_mode())
        {
            DBG_LOG_PRINT(("<mmp> %s,%d,OOBE mode,should not response \n\r",__FUNCTION__,__LINE__));
            b_is_need_response = FALSE;
        }

        if (!nav_is_active())
        {
            i4_ret = a_am_get_active_app (ac_app_name);
            RET_ON_ERR(i4_ret);

        #ifdef APP_RETAIL_MODE_SUPPORT
            ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                DBG_LOG_PRINT(("<mmp> %s,%d,ACFG_RETAIL_MODE_NORMAL,should not response \n\r",__FUNCTION__,__LINE__));
                b_is_need_response = FALSE;
            }
        #endif

        #ifndef APP_CAST_TV_MMP_FG
            /* is running MMP? */
            if (0 == c_strcmp(ac_app_name, MMP_NAME))
            {
                DBG_LOG_PRINT(("<mmp> %s,%d,MMP is running,should not response \n\r",__FUNCTION__,__LINE__));
                b_is_need_response = FALSE;
            }
        #endif

            /* is MENU & MMP coexist status */
        #ifdef APP_MENU_MMP_COEXIST
            else if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                DBG_LOG_PRINT(("<mmp> %s,%d,MMP is running,should not response \n\r",__FUNCTION__,__LINE__));
                b_is_need_response = FALSE;
            }
        #endif
                    /* is running WIZARD? */
            else if (0 == c_strcmp(ac_app_name, WZD_NAME))
            {
                DBG_LOG_PRINT(("<mmp> %s,%d,wizard is running,should not response \n\r",__FUNCTION__,__LINE__));
                b_is_need_response = FALSE;
            }
                    /* is running MENU? */
            else if(0 == c_strcmp(ac_app_name, MENU_NAME))
            {
            #ifndef APP_CAST_TV_MMP_FG
            #ifndef APP_CAST_TV_MMP
                /* usb device number has been incressed and menu is showing.
                   we need send message for menu to show dialog */
                extern BOOL menu_custom_is_blank_screen(VOID);
                if ((menu_custom_is_blank_screen())
                    && (b_is_need_response))
                {
                    a_amb_pause_app(MENU_NAME);
                    c_thread_delay(500);
                    /*2.re-send USB Insert notification, inorder to wait nav processed menu pause msg
                             * if not, usb dialog will be hidden by menu pause msg and next app is not nav
                            */
                    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
                    {
                        DBG_LOG_PRINT(("<mmp> %s,%d,APP_TV_NET_SVC_STATUS_RESUMED is running with blank screen,should not response \n\r",__FUNCTION__,__LINE__));
                        b_g_show_dialog_delay = TRUE;
                        b_is_need_response = FALSE;
                    }
                }
                else if (b_is_need_response && _nav_usb_is_over_delay_time_after_power_on())
                {
                    b_is_need_response = FALSE;
                    DBG_LOG_PRINT(("<mmp> %s,%d,NAV_USB_PLD_POWER_ON_TIMER_TIMER_OUT,should not response \n\r",__FUNCTION__,__LINE__));
                    a_amb_dispatch_msg(MENU_NAME, MENU_MSG_EXTERNAL_REQ_SHOW_USB_POP_DLG, NULL, 0);
                }
            #else
                return a_mmp_request_operation(MMP_REQ_OP_ENTER_VIDEO_BWR);
            #endif
            #else
            #ifdef APP_MENU_MMP_COEXIST
                if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                {
                    DBG_LOG_PRINT(("<usb_pld>%s() %d\n",__FUNCTION__,__LINE__));

                    BOOL        b_is_mmp = FALSE;
                    return a_amb_dispatch_msg(MMP_NAME, MMP_MSG_EXTERNAL_REQ_INSET_USB, (VOID*)&b_is_mmp, sizeof(b_is_mmp));
                }
                else
            #endif
                {
                    if (nav_is_in_power_off())
                    {
                        DBG_LOG_PRINT(("<mmp> %s,%d,nav_is_in_power_off,should not response \n\r",__FUNCTION__,__LINE__));
                        b_is_need_response = FALSE;
                    }
                    //scan is running
                    else if(!nav_is_channel_scan_active())
                    {
                        DBG_LOG_PRINT(("<usb_pld>%s() %d\n",__FUNCTION__,__LINE__));
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_MMP");
                        _nav_usb_pld_chg_inp_src_to_usb();
                        rest_event_notify_current_input("usb");
                        return  a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
                    }
                }
            #endif
            }
        }
        else
        {
            e_comp_id = nav_get_active_component();

#ifdef APP_WR_UPDATER_UI_SUPPORT
            if ((NAV_COMP_ID_UPDATER == e_comp_id)
                || (NAV_COMP_ID_WR_UPDATER == e_comp_id))
#else
            if (NAV_COMP_ID_UPDATER == e_comp_id)
#endif
            {
                DBG_LOG_PRINT(("<mmp> %s,%d,updater comp is active,should not response \n\r",__FUNCTION__,__LINE__));
                b_is_need_response = FALSE;
            }
        }

        if (_nav_usb_pld_is_skype_FULLSCREEN())     /*skype.FULLSCREEN should not popup dialog*/
        {
            DBG_LOG_PRINT(("<mmp> %s,%d,_nav_usb_pld_is_skype_FULLSCREEN,should not response \n\r",__FUNCTION__,__LINE__));
            b_is_need_response = FALSE;
        }

        //scan is running
        if(nav_is_channel_scan_active())
        {
            DBG_LOG_PRINT(("<mmp> %s,%d,nav_is_channel_scan_active,should not response \n\r",__FUNCTION__,__LINE__));
            b_is_need_response = FALSE;
        }

#ifdef APP_CAST_TV_MMP
        PCL_WAKE_UP_REASON_T    e_wake_up_reason = PCL_WAKE_UP_REASON_UNKNOWN;
        c_pcl_get_wakeup_reason (& e_wake_up_reason, NULL);
        if ((e_wake_up_reason == PCL_WAKE_UP_REASON_IRRC
            || e_wake_up_reason == PCL_WAKE_UP_REASON_BT)
            && a_mmp_get_power_exit_video_state())
        {
            DBG_LOG_PRINT(("<mmp> %s,%d,PCL_WAKE_UP_REASON_IRRC or (PCL_WAKE_UP_REASON_BT & a_mmp_get_power_exit_video_state),should not response \n\r",__FUNCTION__,__LINE__));
            b_is_need_response = FALSE;
            a_mmp_set_power_exit_video_state(FALSE);
        }
#endif
    }

    if ((3 == odm_id || 5 == odm_id || 6 == odm_id || 7 ==odm_id) && b_g_fac_set_respone_usb_disable)
    {
        DBG_LOG_PRINT(("<mmp> %s,%d,odm(%d) b_g_fac_set_respone_usb_disable = %d ,should not response \n\r",__FUNCTION__,__LINE__,odm_id,b_g_fac_set_respone_usb_disable));
        b_is_need_response = FALSE;
    }

    DBG_LOG_PRINT(("<nav_usb> check response:%d, %s,%d\n\r",b_is_need_response,__FILE__,__LINE__));

    return b_is_need_response;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_rmv_dev_nfy
 * Description:
 *
 * Input arguments:
 *      pv_tag
 *      e_nfy_id
 *      pv_nfy_param
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_usb_pld_rmv_dev_nfy(
                    VOID*               pv_tag,
                    RMV_DEV_NFY_ID_T    e_nfy_id,
                    VOID*               pv_nfy_param)
{
    if ((RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)||
        (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id))
    {
        nav_request_context_switch(
                        _nav_usb_pld_rmv_dev_nfy_handler,
                        (VOID*)e_nfy_id,
                        NULL,
                        NULL);
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_rmv_dev_nfy_handler
 * Description:
 *
 * Input arguments:
 *      pv_tag1
 *      pv_tag2
 *      pv_tag3
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_usb_pld_rmv_dev_nfy_handler(
                    VOID*               pv_tag1,
                    VOID*               pv_tag2,
                    VOID*               pv_tag3)
{
    RMV_DEV_NFY_ID_T e_nfy_id = (RMV_DEV_NFY_ID_T)((UINT32)pv_tag1);

    if (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
    {
        /* go to the module entry */
        if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)//check whether the 3rd source is resumed
        {
            a_msg_convert_send_cmd(":am,am,:stop=Cobalt YTTV\n");
        }

        _nav_usb_pld_module_entry();
    }
    else if (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id)
    {
        /* go to the module leave */
        _nav_usb_pld_module_leave();
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_module_entry
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *
 * Returns:
 *
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_module_entry(VOID)
{
    DBG_LOG_PRINT(("[MMP][%s %d] USB insert\n",__FUNCTION__,__LINE__));

    if (TRUE == _nav_usb_pld_check_for_response())
    {
        if(_nav_usb_is_over_delay_time_after_power_on())
        {
            INT32       i4_ret = NAVR_OK;
            char        ac_app_name[APP_NAME_MAX_LEN] = {0};

            i4_ret = a_am_get_active_app (ac_app_name);
            RET_ON_ERR(i4_ret);

            /* mmp is show ,change mmp foreground ui */
            if(0 == c_strcmp(ac_app_name, MMP_NAME))
            {
                DBG_LOG_PRINT(("<usb_pld>%s() %d\n",__FUNCTION__,__LINE__));

                BOOL        b_is_mmp = TRUE;
                i4_ret = a_amb_dispatch_msg(MMP_NAME, MMP_MSG_EXTERNAL_REQ_INSET_USB, (VOID*)&b_is_mmp, sizeof(b_is_mmp));
                RET_ON_ERR(i4_ret);
            }
            else
            {
                DBG_LOG_PRINT(("<usb_pld>%s() %d\n",__FUNCTION__,__LINE__));
#ifdef  APP_C4TV_SUPPORT
                a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_MMP");
#endif
                _nav_usb_pld_chg_inp_src_to_usb();
                rest_event_notify_current_input("usb");

                return a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
            }
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_usb_pld_module_leave
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *
 * Returns:
 *
 *---------------------------------------------------------------------------*/
static INT32 _nav_usb_pld_module_leave(VOID)
{
#ifndef APP_CAST_TV_MMP_FG
    INT32                 i4_ret = NAVR_OK;
    char                  ac_app_name[APP_NAME_MAX_LEN] = {0};
#endif

#ifdef APP_CAST_TV_MMP
    ui4_g_usb_dev_num = 0;
    return NAVR_OK;
#endif
    DBG_LOG_PRINT(("[MMP][%s %d] USB remove\n",__FUNCTION__,__LINE__));
    if(nav_is_component_visible(NAV_COMP_ID_USB_PLD))
    {
    #ifndef APP_CAST_TV_MMP_FG
    	a_nav_usb_pld_view_dialog_hide();
    #endif
        nav_return_activation(NAV_COMP_ID_USB_PLD);
    }
    else
    {
    #ifndef APP_CAST_TV_MMP_FG
        i4_ret = a_am_get_active_app (ac_app_name);
        RET_ON_ERR(i4_ret);

        /* If menu is showing, we need notify menu to hide the usb pop up dialog. */
        if(0 == c_strcmp(ac_app_name, MENU_NAME))
        {
            a_amb_dispatch_msg(MENU_NAME, MENU_MSG_EXTERNAL_REQ_HIDE_USB_POP_DLG, NULL, 0);
        }
    #endif
    }

    /* Just count the usb device number */
   // _nav_usb_pld_check_for_response();

    return NAVR_OK;
}
#ifdef APP_CAST_TV_MMP
/*-----------------------------------------------------------------------------
 * Name:
 *      nav_usb_pld_get_retail_mode_status
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *
 * Returns:
 *
 *---------------------------------------------------------------------------*/
BOOL nav_usb_pld_get_retail_mode_status(VOID)
{
    return b_g_is_retail_mode;
}
#endif

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      a_nav_usb_pld_show_uplg_dialog
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 a_nav_usb_pld_show_uplg_dialog(VOID)
{
#ifndef APP_CAST_TV_MMP_FG
    INT32                 i4_ret = NAVR_OK;
    NAV_USB_PLD_HDLR_T*   pt_this = &t_g_nav_usb_pld;
#ifdef APP_WR_UPDATER_UI_SUPPORT
    if (_nav_usb_is_over_delay_time_after_power_on())
        && (NAV_COMP_ID_WR_UPDATER != nav_get_active_component()))
#else
    if (_nav_usb_is_over_delay_time_after_power_on())
#endif
    {
        i4_ret = nav_grab_activation(NAV_COMP_ID_USB_PLD);
        RET_ON_ERR(i4_ret);

        i4_ret = pt_this->t_view_hdlr.pf_show(NAV_USB_PLD_PAGE_UPLG_DIALOG);
        RET_ON_ERR(i4_ret);
    }

    ui4_g_usb_dev_num = 0;
#endif
    return NAVR_OK;
}

/*
b_enable = TRUE, to enable pop up dialog,
b_enable = FALSE, to disable pop up dialog
*/
INT32 a_nav_enable_usb_pop_up_dialog(BOOL b_enable)
{
    b_g_enable_usb_pop_up_dialog = b_enable;
    return NAVR_OK;
}

#ifdef APP_C4TV_SUPPORT
static VOID _nav_usb_pld_grab_active(VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{

    DBG_LOG_PRINT(("<nav_usb> set active %s,%d\n\r",__FILE__,__LINE__));

    nav_set_component_visible(NAV_COMP_ID_USB_PLD);
    nav_grab_activation(NAV_COMP_ID_USB_PLD);
    a_nav_usb_pld_show_uplg_dialog();
}

INT32 a_nav_usb_pld_component_active(VOID)
{
   nav_request_context_switch(_nav_usb_pld_grab_active, NULL, NULL, NULL);

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name:
 *      a_nav_usb_pld_register
 * Description:
 *      The registration function of the USB detection component.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 a_nav_usb_pld_register(VOID)
{
    NAV_USB_PLD_HDLR_T* pt_this = &t_g_nav_usb_pld;
    NAV_COMP_T          t_comp;
    INT32               i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_USB_PLD */
    t_comp.pf_init           = _nav_usb_pld_init;
    t_comp.pf_deinit         = _nav_usb_pld_deinit;
    t_comp.pf_is_key_handler = _nav_usb_pld_is_key_handler;
    t_comp.pf_activate       = _nav_usb_pld_activate;
    t_comp.pf_inactivate     = _nav_usb_pld_inactivate;
    t_comp.pf_hide           = _nav_usb_pld_hide;
    t_comp.pf_handle_msg     = _nav_usb_pld_handle_msg;
    t_comp.ui4_exclusive_set = COMP_EXC_SET_USB_PLD;

    i4_ret = nav_register_comp(
                NAV_COMP_ID_USB_PLD,
                &t_comp);
    RET_ON_ERR(i4_ret);

    /* register view */
    i4_ret = nav_usb_pld_view_register_default_hdlr(&pt_this->t_view_hdlr);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

INT32 a_nav_usb_pld_factory_set_response_usb_disable(BOOL b_is_disable)
{
    b_g_fac_set_respone_usb_disable = b_is_disable;
    return NAVR_OK;
}

#endif /* APP_NAV_USB_PLD */

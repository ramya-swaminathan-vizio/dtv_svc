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
 * $RCSfile: logo.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * This module of simple logo only co-work with loader Vlogo.
 * When power on, loader shows Vlogo but not to hide it. Need SLOGO to control *
 * how/when to hide.                                                          *
 * Currently implement as a timer, if need can be change to an application.
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_dbg.h"

#include "app_util/a_cfg.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "slogo.h"
#include "nav/nav_common.h"
#include "mi_common.h"
#include "mi_dispout.h"
#include "mi_os.h"

#define LOGO_WAIT_PNL_TIME_MS 100
#define LOGO_DISPLAY_TIME_MS 1000

static UINT16  u16_wait_panel_time_sum = 0;
static UINT32  u32_bootlogo_draw_time = 0;
static BOOL     b_bootlogo_show  = FALSE;
static BOOL     b_bootlogo_finished = FALSE;
static BOOL     b_bootlogo_minimal_display_done = FALSE;
static HANDLE_T h_hidelogo_timer = NULL_HANDLE;
static HANDLE_T h_wait_panel_resume_timer = NULL_HANDLE;
/*-----------------------------------------------------------------------------
                    typedefs
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
#include "c_cl.h"
#include "c_os.h"

static HANDLE_T h_g_lock = NULL_HANDLE;
static VOID _slogo_lock(VOID)
{

    /* Acquire lock */
    if(h_g_lock == NULL_HANDLE)
    {
        if(h_g_lock == NULL_HANDLE)
        {
            c_sema_create(&h_g_lock,
                          X_SEMA_TYPE_MUTEX,
                          X_SEMA_STATE_UNLOCK);
        }
    }

    /* Lock */
    if(h_g_lock)
    {
        c_sema_lock(h_g_lock, X_SEMA_OPTION_WAIT);
    }
}

static VOID _slogo_unlock(VOID)
{
    /* Unlock */
    if(h_g_lock)
    {
        c_sema_unlock(h_g_lock);
    }
}

BOOL a_slogo_init_check(VOID)
{
    UINT8 ui1_power_mode = 0;
    a_cfg_custom_get_power_mode_save(&ui1_power_mode);
    DBG_LOG_PRINT(("[LOGO] power_mode_save:%d \n",ui1_power_mode));
    b_bootlogo_finished = FALSE;
    if(ui1_power_mode != 0) //QS mode
    {
        b_bootlogo_minimal_display_done = TRUE;
        b_bootlogo_finished = TRUE;
        acfg_video_backlight_lock(FALSE);
        DBG_LOG_PRINT(("[LOGO] No need show logo\n"));
        return FALSE;
    }
    return TRUE;
}

VOID _slogo_show_end(VOID)
{
    UINT8 ui1_zoom_status = 0;
    a_cfg_cust_get_zoom_status(&ui1_zoom_status);
    //if the previous state is zoom on
    if(ui1_zoom_status)
    {
        DBG_LOG_PRINT(("[LOGO][BGM_OLED_COMPENSITION] zoom mode on\n"));
        nav_zoom_mode_enable();
    }
}

static VOID _slogo_muteAudio(BOOL bMute)
{
    a_cfg_cust_audio_mute(bMute);
    if (bMute)
    {
        dtv_svc_write_timestamp("<LOGO> [ECO] Audio mute");
    }
    else
    {
        dtv_svc_write_timestamp("<LOGO> [ECO] Audio unmute");
    }
}

static VOID _slogo_hide_on_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    b_bootlogo_minimal_display_done = TRUE;
    a_slogo_hide(0);
}

static VOID _WaitPanelResumeToShowLogo();

static VOID _slogo_wait_panel_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    _WaitPanelResumeToShowLogo();
}

static VOID _WaitPanelResumeToShowLogo()
{
    MI_DISPOUT_PowerStatus_t stPowerStatus;
    UINT16 u16BootLogoBackLight = 10000;
    memset(&stPowerStatus, 0, sizeof(MI_DISPOUT_PowerStatus_t));
    if (MI_DISPOUT_GetPowerStatus(MI_HANDLE_NULL, &stPowerStatus) == MI_ERR_BUSY)
    {
        if (0 == u16_wait_panel_time_sum)
        {
            dtv_svc_write_timestamp("Wait Panel resume ... start");
        }
        c_timer_start( h_wait_panel_resume_timer, LOGO_WAIT_PNL_TIME_MS, X_TIMER_FLAG_REPEAT, _slogo_wait_panel_timer_nfy, NULL);
        u16_wait_panel_time_sum += LOGO_WAIT_PNL_TIME_MS;
        return;
    }
    if(stPowerStatus.u16BootLogoBackLight < 10000)
    {
        u16BootLogoBackLight = stPowerStatus.u16BootLogoBackLight;
    }
    c_timer_stop(h_wait_panel_resume_timer);

    if (u16_wait_panel_time_sum)
    {
        char tmp[128]={0};
        snprintf(tmp, sizeof(tmp), "Wait Panel resume %d msec done", u16_wait_panel_time_sum);
        dtv_svc_write_timestamp(tmp);
    }
    u16_wait_panel_time_sum = 0;

    _slogo_lock();

    acfg_video_backlight_lock(TRUE);
    a_cfg_cust_backlight_ctrl_lock(TRUE);

    if (a_cfg_cust_get_support_local_dimming())
    {
        dtv_svc_write_timestamp("[LOGO] Support LDM, diable backlight ctrl & force to backlight 100");
        DBG_LOG_PRINT(("[LOGO] Support Local dimming, force to disable local dimming.\n"));
    }
    else
    {
        dtv_svc_write_timestamp("[LOGO] Not Support LDM, diable backlight ctrl & force to backlight 100");
        DBG_LOG_PRINT(("[LOGO] Not Support Local dimming, force to disable backlight control.\n"));
    }
    DBG_LOG_PRINT(("[LOGO] Force backlight to %d\n", u16BootLogoBackLight));
    ACFG_CustDrv_Set_Backlight(u16BootLogoBackLight, 0);

    _slogo_muteAudio(TRUE);
    b_bootlogo_show = TRUE;
    a_cfg_custom_draw_logo_image(BOOTLOGO_SHOW);
    _slogo_unlock();

    UINT32 _u32PNLResumeDoneTime = stPowerStatus.u32PNLResumeDoneTime;
    UINT32 u32CurSystemTime = 0;
    MI_OS_GetSystemTime(&u32CurSystemTime);

    char tmp[128]={0};
    snprintf(tmp, sizeof(tmp), "Logo show 1 sec start, Panel BL_ON = %u, Logo drew = %u, Current = %u", _u32PNLResumeDoneTime, u32_bootlogo_draw_time, u32CurSystemTime);
    dtv_svc_write_timestamp(tmp);

    c_timer_stop(h_hidelogo_timer);
    c_timer_start( h_hidelogo_timer,  LOGO_DISPLAY_TIME_MS, X_TIMER_FLAG_ONCE, _slogo_hide_on_timer_nfy, NULL);
}

BOOL a_slogo_is_show(void)
{
    return b_bootlogo_show;
}

BOOL a_slogo_is_finished(void)
{
    return b_bootlogo_finished;
}

VOID a_slogo_hide(UINT32 ui4_delay_time)
{
    _slogo_lock();
    if (FALSE == b_bootlogo_minimal_display_done ||
        TRUE == b_bootlogo_finished)
    {
        _slogo_unlock();
        return;
    }

    {   // Don't change the order
        a_cfg_custom_draw_logo_image(BOOTLOGO_HIDE);
        a_cfg_custom_set_black_pattern(TRUE);
        acfg_video_backlight_lock(FALSE);
        a_cfg_cust_backlight_ctrl_lock(FALSE);
        a_cfg_custom_draw_logo_image(BOOTLOGO_DEINIT);
        a_cfg_custom_set_black_pattern(FALSE);
    }

    a_scrn_svr_set_enable(TRUE);
    _slogo_show_end();
    _slogo_muteAudio(FALSE);
    b_bootlogo_show = FALSE;
    b_bootlogo_finished = TRUE;
    _slogo_unlock();

    if (c_handle_valid(h_wait_panel_resume_timer) == TRUE)
    {
         c_timer_stop(h_wait_panel_resume_timer);
         c_timer_delete(h_wait_panel_resume_timer);
    }
    h_wait_panel_resume_timer = NULL_HANDLE;
    if (c_handle_valid(h_hidelogo_timer) == TRUE)
    {
         c_timer_stop(h_hidelogo_timer);
         c_timer_delete(h_hidelogo_timer);
    }
    h_hidelogo_timer = NULL_HANDLE;
    dtv_svc_write_timestamp("_slogo_hide finished");
}

VOID a_slogo_show(void)
{
    if(NULL_HANDLE == h_hidelogo_timer)
    {
        c_timer_create(&h_hidelogo_timer);
    }
    if(NULL_HANDLE == h_wait_panel_resume_timer)
    {
        c_timer_create(&h_wait_panel_resume_timer);
    }

    a_scrn_svr_set_enable(FALSE);

    _slogo_lock();
    b_bootlogo_minimal_display_done = FALSE;
    b_bootlogo_show = FALSE;
    b_bootlogo_finished = FALSE;
    a_cfg_custom_draw_logo_image(BOOTLOGO_INIT);
    MI_OS_GetSystemTime(&u32_bootlogo_draw_time);
    dtv_svc_write_timestamp("a_slogo_show painted is ready");
    _slogo_unlock();

    _WaitPanelResumeToShowLogo();
}

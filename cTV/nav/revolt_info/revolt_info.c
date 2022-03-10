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
 * $RCSfile: revolt_info.c,v $
 * $Revision: #1 $
 * $Date: 2016/01/25 $
 * $Author: ffangfang wang $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT

#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"

//#include "c_fm.h"
//#include "c_dlm.h"

#include "app_util/a_cfg.h"
#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "nav/revolt_info/revolt_info.h"
#include "wdk/widget/wdk_widget.h"
#include "nav/revolt_misc/closed_captions_view.h"
//#include "res/nav/nav_mlm.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "res/revolt/revolt_warnings_mlm.h"
#include "c_aee.h"

#include "c_appman.h"
#include "u_irrc_btn_def.h"
#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>

#include "mmp/a_mmp.h"
#include "mmp/video_engine/a_video_engine.h"

#include "c_uc_str.h"

#include "cmpb/IMtkPb_ErrorCode.h"
#include "cmpb/IMtkPb_Ctrl.h"
#include "cmpb/IMtkPb_Snd.h"
#include "os/inc/x_os.h"

#include "nav/tuner_setup/tuner_setup_view.h"
#include "app_util/toast_widget/a_toast.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/nav/nav_dbg.h"

#define  NAV_REVOLT_INFO_AUTO_HIDE_TIMER_DURATION           5000
#define  NAV_REVOLT_AUDIO_TONE_FILE_PCM                     "/basic/audioTone/pair.pcm"

static WDK_TOAST_STYLE_T           e_g_toast_style = WDK_TOAST_MAX_NUM;

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct
{
    void*   pv_phy_addr;
    void*   pv_vir_addr;
    SIZE_T  ui4_buf_size;
}NAV_REVOLT_INFO_AUD_BUF_T;

extern void x_share_mem_free(void* pv_phy_addr, unsigned int z_size);
extern void x_munmap_share_mem(void* pv_virt_addr, unsigned int z_size);
extern void* x_share_mem_alloc(unsigned int z_size);
extern void* x_mmap_share_mem(void* pv_phy_addr, unsigned int z_size);
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_REVOLT_INFO_T t_g_nav_revolt_info;
static CC_CAP_STL_DATA_T t_g_cap;
static WDK_OSD_TOAST_T      t_g_wdk_view_slider={0} ;
static WDK_OSD_TOAST_T      t_g_wdk_view_string={0} ;
static WDK_OSD_TOAST_T*     t_g_wdk_view=&t_g_wdk_view_slider;

static IMTK_PB_HANDLE_T     hPB_Handle = NULL_HANDLE;
static HANDLE_T             h_pair_snd_thread  = NULL_HANDLE;

BOOL   g_custom_timeout     = FALSE;
UINT32 g_ui4_custom_timeout = 0;

#define BUFFER_SIZE         (256*1024)

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Refresh the list.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

static VOID _nav_revolt_info_reset_cc_timer(
                    NAV_REVOLT_INFO_T*                 pt_this
                    );

static IMTK_PB_CB_ERROR_CODE_T _snd_callback(IMTK_PB_HANDLE_T            hHandle,
                                             IMTKPB_SND_CLIP_COND_T      eSndCond,
                                             void*                       pvTag,
                                             uint32_t                    u4Data,
                                             uint32_t                    u4ClipTag)
{
    return IMTK_PB_CB_ERROR_CODE_OK;
}

static void _revolt_play_tone_thread(void*   pv_data)
{
    UINT32                  ui4_read_cnt    = 0;
    FILE*                   fp              = 0;
    UINT32                  ui4_buf_size    = BUFFER_SIZE;
    UINT8*                  pui1_buf        = NULL;
    IMTK_PB_ERROR_CODE_T    e_return        = IMTK_PB_ERROR_CODE_OK;
    BOOL                    b_play          = TRUE;

    DBG_INFO(("%s, [%d]\n",__FUNCTION__, __LINE__));

    pui1_buf = c_mem_alloc(BUFFER_SIZE);
    if(NULL == pui1_buf)
    {
        DBG_INFO(("Out of memory !!! \n\r"));
        return;
    }
    c_memset(pui1_buf, 0, BUFFER_SIZE);

    fp = fopen(NAV_REVOLT_AUDIO_TONE_FILE_PCM, "rb");

    if (fp == NULL)
    {
        DBG_INFO(("Open file Failed !\n"));
        return ;
    }

    while (b_play)
    {
        ui4_read_cnt = 0;
        ui4_read_cnt = fread( pui1_buf,
                              1,
                              ui4_buf_size,
                              fp);

        e_return = IMtkPb_Snd_SendClipDirect(hPB_Handle,
                                             pui1_buf,
                                             ui4_read_cnt,
                                             0);

        if(e_return == IMTK_PB_ERROR_CODE_GET_BUF_PENDING)
        {
            x_thread_delay(10);
            continue;
        }
        else if(e_return != IMTK_PB_ERROR_CODE_OK)
        {
            DBG_INFO(("IMtkPb_Snd_SendClipDirect() Failed: %d!\n", e_return));
            b_play = 0;
            break;
        }

        if (ui4_read_cnt < ui4_buf_size)
        {
            b_play = 0;
            break;
        }

    }

    fclose (fp);

    if(NULL != pui1_buf)
    {
        c_mem_free(pui1_buf);
        pui1_buf = NULL;
    }

    x_thread_delay(1000);

    e_return = IMtkPb_Snd_Stop(hPB_Handle);
    if(e_return != IMTK_PB_ERROR_CODE_OK)
    {
        DBG_INFO(("IMtkPb_Snd_Stop() Failed: %d!\n", e_return));
        hPB_Handle = NULL_HANDLE;
    }

    e_return = IMtkPb_Snd_Close(hPB_Handle);
    if(e_return != IMTK_PB_ERROR_CODE_OK)
    {
        DBG_INFO(("IMtkPb_Snd_Close() Failed: %d!\n", e_return));
        hPB_Handle = NULL_HANDLE;
    }

    hPB_Handle = NULL_HANDLE;

    DBG_INFO(("%s, [%d] END\n",__FUNCTION__, __LINE__));

    x_thread_exit();
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_revolt_info_stop_timer(
                    NAV_REVOLT_INFO_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop revolt_info::h_hide_timer failed!"));
    }

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_stop_cc_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_revolt_info_stop_cc_timer(
                    NAV_REVOLT_INFO_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_cc_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_cc_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop revolt_info::h_hide_cc_timer failed!"));
    }
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static HANDLE_T canvas = NULL_HANDLE;
static INT32 _nav_revolt_info_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_REVOLT_INFO_T* pt_this = &t_g_nav_revolt_info;
    INT32           i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }
    if (c_handle_valid(pt_this->h_hide_cc_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_cc_timer);
    }

    canvas = pt_ctx->t_gui_res.h_canvas;

    pt_this->b_is_on      = FALSE;

    pt_this->ui4_timeout  = NAV_REVOLT_INFO_AUTO_HIDE_TIMER_DURATION;

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->h_hide_cc_timer = NULL_HANDLE;
    pt_this->h_toast_warning = NULL_HANDLE;
    pt_this->h_toast_center_dialog = NULL_HANDLE;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_timer_create(&(pt_this->h_hide_cc_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    a_close_caption_init();

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_revolt_info_deinit(VOID)
{
    NAV_REVOLT_INFO_T* pt_this = &t_g_nav_revolt_info;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

     if (c_handle_valid(pt_this->h_hide_cc_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_cc_timer);
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->h_hide_cc_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;

    a_toast_destroy(pt_this->h_toast_warning);
    a_toast_destroy(pt_this->h_toast_center_dialog);

    a_wdk_toast_deinit(t_g_wdk_view);
    closed_captions_view_deinit(&t_g_cap);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_revolt_info_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_revolt_info_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_REVOLT_INFO_T* pt_this = &t_g_nav_revolt_info;

    if (pt_this->b_is_on == TRUE)
    {
        return NAVR_OK;
    }

    pt_this->b_is_on = TRUE;

    nav_set_component_visible(NAV_COMP_ID_REVOLT_INFO);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_revolt_info_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_revolt_info_hide(
                    VOID
                    )
{
    NAV_REVOLT_INFO_T* pt_this = &t_g_nav_revolt_info;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    pt_this->b_is_on = FALSE;

    _nav_revolt_info_stop_timer(pt_this);

    if (e_g_toast_style == WDK_WARNING_TOAST)
    {
        a_toast_hide(pt_this->h_toast_warning);
    }
    else if (e_g_toast_style == WDK_CENTER_DIALOG)
    {
        a_toast_hide(pt_this->h_toast_center_dialog);
    }
    else
    {
        if (c_wgl_float(t_g_wdk_view->h_base_frm, FALSE, FALSE) != WGLR_OK) {
            DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
        }
        a_wdk_toast_hide(TRUE, NULL, t_g_wdk_view);
    }
    //a_wdk_toast_deinit(t_g_wdk_view);

    if (pt_this->pf_cb != NULL)
    {
        pt_this->pf_cb(TOAST_EVENT_HIDE, TOAST_REASON_HIDE_TIMEOUT, NULL);
    }

    //if scan is running,show scan ui after toast hide
    tuner_setup_view_show_ex ();

    /* Return control. */
    nav_return_activation(NAV_COMP_ID_REVOLT_INFO);

    return NAVR_OK;
}

static INT32 _nav_revolt_info_warning_toast_wgl_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    NAV_REVOLT_INFO_T* pt_this = &t_g_nav_revolt_info;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        if (pt_this->pf_cb != NULL)
        {
            pt_this->pf_cb(TOAST_EVENT_KEY, TOAST_REASON_KEY_DOWN, pv_param1);
            a_amb_default_key_handler(WGL_MSG_KEY_DOWN, pv_param1, NULL);
        }
    }

    return c_wgl_default_msg_proc(h_widget,
                                  ui4_msg,
                                  pv_param1,
                                  pv_param2);

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_revolt_info_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    NAV_REVOLT_INFO_T* pt_this = &t_g_nav_revolt_info;

    if(pt_ui_msg->e_id == NAV_UI_MSG_REST_NOTIFICATION_HIDE)
    {
        DBG_INFO(("%s %d\n", __FUNCTION__, __LINE__));
        nav_hide_component(NAV_COMP_ID_REVOLT_INFO);
    }

    if(pv_arg1 == NULL){
        //DBG_INFO(("warning!!the msg send revolt_info is NULL\n"));
        return NAVR_NO_ACTION;
    }

    if(pt_ui_msg->e_id == NAV_UI_MSG_REST_NOTIFICATION)
    {
        WDK_TOAST_PARAM_T revolt_msg={0};
        WDK_TOAST_T wdk_pv_arg={0};
        c_memcpy((VOID*)&wdk_pv_arg, (const VOID*)pv_arg1, sizeof(WDK_TOAST_T));
        c_mem_free(pv_arg1);  //Maybe not fully free memory
        pv_arg1 = NULL;

        revolt_msg.e_toast_style = wdk_pv_arg.e_toast_style;////
        UTF16_T     w2s_string[256]  = {0}; //use to indicate the connected str for WDK_STRING_ID_ID
        UTF16_T     w2s_title_string[256] = {0};

        if (g_custom_timeout && (0 != g_ui4_custom_timeout))
        {
            pt_this->ui4_timeout  = g_ui4_custom_timeout;
            g_custom_timeout = FALSE;
            g_ui4_custom_timeout = 0;

            DBG_INFO(("[Revolt_Info] %s, pt_this->ui4_timeout=%d\n", __FUNCTION__, pt_this->ui4_timeout));
        }
        else
        {
            pt_this->ui4_timeout  = NAV_REVOLT_INFO_AUTO_HIDE_TIMER_DURATION;
        }

        DBG_INFO(("[ff] _nav_revolt_info_handle_msg, e_string_style=%d,e_toast_style=%d\n", wdk_pv_arg.e_string_style,wdk_pv_arg.e_toast_style));

        switch (wdk_pv_arg.e_string_style)
        {
            case WDK_STRING_TRACK:
            {
                revolt_msg.e_track_style = wdk_pv_arg.style.style_1.e_track_style;
                revolt_msg.i4_vol_track_val= wdk_pv_arg.style.style_1.i4_value;
                if(revolt_msg.e_toast_style == WDK_WARNING_TOAST)
                {
                    revolt_msg.w2s_str = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_1.ui4_id));
                }
                else
                {
                    revolt_msg.w2s_str = WGL_PACK (MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_1.ui4_id));
                }
                revolt_msg.i4_vol_track_range = wdk_pv_arg.style.style_1.i4_max_val;
                break;
            }
            case WDK_STRING_ID_ID:
            {
                //the two str should linked with "is" between
                VOID* w2s_str1 = NULL;
                VOID* w2s_str2 = NULL;
                CHAR  str_point[8] = ".";
                UTF16_T     w2s_str_point[64] = {0};

                //UTF16_T w2s_is[]  = { L' ', L'i', L's', L' ', L'\0'}; //"is"
                VOID* w2s_is = NULL;
                w2s_is = WGL_PACK (MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_IS));


                CHAR dst[128] = {0};

                if(revolt_msg.e_toast_style == WDK_WARNING_TOAST)
                {
                    w2s_str1 = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_2.ui4_id_1));
                    w2s_str2 = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_2.ui4_id_2));
                }
                else
                {
                    w2s_str1 = WGL_PACK (MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_2.ui4_id_1));
                    w2s_str2 = WGL_PACK (MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_2.ui4_id_2));
                }

                c_uc_w2s_strcat(w2s_string, w2s_str1);
                c_uc_w2s_to_ps((const UTF16_T* )w2s_string,dst,127);
                DBG_INFO(("[ff] _nav_revolt_info_handle_msg1,dst=%s\n",dst));

                VOID* w2s_are = NULL;
                w2s_are= WGL_PACK (MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_ARE));

                //if (c_uc_w2s_strcmp(w2s_str1, L"Speakers") == 0)
                if (c_uc_w2s_strcmp(w2s_str1, WGL_PACK (MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_AUD_SPEAKERS))) == 0)
                {
                    //c_uc_w2s_strcat(w2s_string, L" are ");
                    c_uc_w2s_strcat(w2s_string, L" ");
                    c_uc_w2s_strcat(w2s_string, w2s_are);
                    c_uc_w2s_strcat(w2s_string, L" ");
                }else
                {
                    c_uc_w2s_strcat(w2s_string, L" ");
                    c_uc_w2s_strcat(w2s_string, w2s_is);
                    c_uc_w2s_strcat(w2s_string, L" ");
                }

                c_uc_w2s_to_ps((const UTF16_T* )w2s_string,dst,127);
                DBG_INFO(("[ff] _nav_revolt_info_handle_msg2,dst=%s\n",dst));

                c_uc_w2s_strcat(w2s_string, w2s_str2);
                c_uc_w2s_to_ps((const UTF16_T* )w2s_string,dst,127);
                DBG_INFO(("[ff] _nav_revolt_info_handle_msg3,dst=%s\n",dst));

                c_uc_ps_to_w2s((const CHAR*)str_point, w2s_str_point, 63);
                c_uc_w2s_strncat(w2s_string,w2s_str_point,63);

                c_uc_w2s_to_ps((const UTF16_T* )w2s_string,dst,127);
                DBG_INFO(("[ff] _nav_revolt_info_handle_msg3,dst=%s\n",dst));

                revolt_msg.w2s_str = w2s_string;

                break;
            }
            case WDK_STRING_ID_VALUE:
            {
                revolt_msg.i4_vol_track_val = wdk_pv_arg.style.style_3.i4_value ;
                if(revolt_msg.e_toast_style == WDK_WARNING_TOAST)
                {
                    revolt_msg.w2s_str = WGL_PACK (MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_3.ui4_id));
                }
                else
                {
                    revolt_msg.w2s_str = WGL_PACK (MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), wdk_pv_arg.style.style_3.ui4_id));
                }
                break;
            }
            case WDK_STRING_STRING:
            {
                if (wdk_pv_arg.style.style_4.w2s_str)
                {
                    c_uc_w2s_strcat(w2s_string, wdk_pv_arg.style.style_4.w2s_str);
                    c_mem_free (wdk_pv_arg.style.style_4.w2s_str);
                    wdk_pv_arg.style.style_4.w2s_str = NULL;
                }

                revolt_msg.w2s_str = w2s_string;
                break;
            }
            case WDK_STRING_TITLE_CONTENT:
            {
                if (wdk_pv_arg.style.style_5.w2s_content_str)
                {
                    c_uc_w2s_strcat(w2s_string, wdk_pv_arg.style.style_5.w2s_content_str);
                    c_mem_free (wdk_pv_arg.style.style_5.w2s_content_str);
                    wdk_pv_arg.style.style_5.w2s_content_str = NULL;
                }

                revolt_msg.w2s_str = w2s_string;

                if (wdk_pv_arg.style.style_5.w2s_title_str)
                {
                    c_uc_w2s_strcat(w2s_title_string, wdk_pv_arg.style.style_5.w2s_title_str);
                    c_mem_free (wdk_pv_arg.style.style_5.w2s_title_str);
                    wdk_pv_arg.style.style_5.w2s_title_str = NULL;
                }
                break;
            }

            default:
                break;

        }

        nav_grab_activation(NAV_COMP_ID_REVOLT_INFO);

        if (e_g_toast_style != revolt_msg.e_toast_style)
        {
            if (e_g_toast_style != WDK_TOAST_MAX_NUM)
            {
                if (e_g_toast_style == WDK_WARNING_TOAST)
                {
                    a_toast_hide(pt_this->h_toast_warning);
                }
                else if (e_g_toast_style == WDK_CENTER_DIALOG)
                {
                    a_toast_hide(pt_this->h_toast_center_dialog);
                }
                else
                {
                    if (c_wgl_float(t_g_wdk_view->h_base_frm, FALSE, FALSE) != WGLR_OK) {
                        DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
                    }
                    a_wdk_toast_hide(TRUE, NULL, t_g_wdk_view);
                }
                //a_wdk_toast_deinit(t_g_wdk_view);

                if (pt_this->pf_cb != NULL)
                {
                    pt_this->pf_cb(TOAST_EVENT_HIDE, TOAST_REASON_HIDE_INTERRUPTED, NULL);
                }
            }
            e_g_toast_style = revolt_msg.e_toast_style;

            //===================init==================//
            switch(revolt_msg.e_toast_style)
            {
                case WDK_TOAST_SETTINGS_SLIDER:
                    t_g_wdk_view = &t_g_wdk_view_slider;
                    break;
                case WDK_WARNING_TOAST:
                    //t_g_wdk_view = &t_g_wdk_view_warning;
                    break;
                case WDK_CENTER_DIALOG:
                    //t_g_wdk_view = &t_g_wdk_view_dialog;
                    break;
                default:
                    t_g_wdk_view = &t_g_wdk_view_string;
                    break;
            }
            if (revolt_msg.e_toast_style == WDK_WARNING_TOAST && pt_this->h_toast_warning == NULL_HANDLE)
            {
                TOAST_INIT_PARAM_T  t_toast_init;
                c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
                t_toast_init.e_toast_style = TOAST_STYLE_MSG;
                t_toast_init.h_canvas = canvas;
                t_toast_init.t_custom_setting.u.t_msg_init.e_msg_type = TOAST_MSG_TYPE_WITH_WARNING_ICON;
                a_toast_create(&t_toast_init, & pt_this->h_toast_warning);
            }
            else if (revolt_msg.e_toast_style == WDK_CENTER_DIALOG && pt_this->h_toast_center_dialog == NULL_HANDLE)
            {
                TOAST_INIT_PARAM_T  t_toast_init;
                c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
                t_toast_init.e_toast_style = TOAST_STYLE_CENTER_DIALOG;
                t_toast_init.h_canvas = canvas;
                a_toast_create(&t_toast_init, & pt_this->h_toast_center_dialog);
            }
            else
            {
                a_wdk_toast_init (canvas, &revolt_msg, t_g_wdk_view);
            }
        }
        //if scan is running,hide scan ui before toast show
        tuner_setup_view_hide_ex ();

        nav_revolt_info_reset_timer(pt_this);

        if (revolt_msg.e_toast_style == WDK_WARNING_TOAST)
        {
            TOAST_CUSTOMIZATION_DATA_T  t_custom_data;
            c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
            t_custom_data.u.t_msg_init.w2s_msg_str = revolt_msg.w2s_str;
            TOAST_CONTROL_T*  pt_toast_control = NULL;
            INT32  i4_ret;

            i4_ret = c_wgl_do_cmd(pt_this->h_toast_warning,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pt_toast_control),
                                  NULL);

            if (i4_ret == WGLR_OK && pt_toast_control != NULL && nav_is_active())
            {
                t_custom_data.h_focus_handle = pt_toast_control->u.t_msg.h_txt_msg;
                t_custom_data.pf_wgl_cb = _nav_revolt_info_warning_toast_wgl_fct;
            }
            a_toast_show(pt_this->h_toast_warning, &t_custom_data);
        }
        else if (revolt_msg.e_toast_style == WDK_CENTER_DIALOG)
        {
            TOAST_CUSTOMIZATION_DATA_T  t_custom_data;
            c_memset(&t_custom_data, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
            t_custom_data.u.t_center_dialog_init.w2s_title_str = w2s_title_string;
            t_custom_data.u.t_center_dialog_init.w2s_msg_str = revolt_msg.w2s_str;
            a_toast_show(pt_this->h_toast_center_dialog, &t_custom_data);
        }
        else
        {
            if (c_wgl_float(t_g_wdk_view->h_base_frm, TRUE, FALSE) != WGLR_OK) {
                DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
            }
            a_wdk_toast_activate(TRUE, &revolt_msg, t_g_wdk_view);
        }

        if ((pt_this->pf_cb = wdk_pv_arg.pf_cb) == NULL)
        {
            /* set focus to nav defalut frame */
            extern INT32 nav_view_set_focus(VOID);
            nav_view_set_focus();
        }
    }
    else if(pt_ui_msg->e_id == NAV_UI_MSG_REST_CC)
    {
        c_memcpy((VOID*)&t_g_cap, (const VOID*)pv_arg1, sizeof(CC_CAP_STL_DATA_T));

        DBG_INFO(("[CC]at revoltinfo e_size=[%d], line=[%d]", t_g_cap.t_cc_info.t_pen_font.t_font.e_size, __LINE__));

        closed_captions_view_activate(&t_g_cap);
        _nav_revolt_info_reset_cc_timer(pt_this);

        c_mem_free(pv_arg1);
        pv_arg1 = NULL;
    }


    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_revolt_info_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    //execute in navigator's thread context
    nav_hide_component(NAV_COMP_ID_REVOLT_INFO);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_revolt_info_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    //execute in timer's thread context
    nav_request_context_switch(_nav_revolt_info_timeout_to_hide, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_revolt_info_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_revolt_info_reset_timer(
                    NAV_REVOLT_INFO_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if(pt_this == NULL)
    {
        pt_this = & t_g_nav_revolt_info;
    }

    _nav_revolt_info_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_revolt_info_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start revolt_info::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *     _nav_revolt_info_timeout_to_hide_cc_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_revolt_info_timeout_to_hide_cc_timer(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    //execute in navigator's thread context
    nav_hide_component(NAV_COMP_ID_REVOLT_INFO);

    NAV_REVOLT_INFO_T* pt_this = &t_g_nav_revolt_info;
    _nav_revolt_info_stop_cc_timer(pt_this);

    DBG_INFO(("wff call closed_captions_view_hide\n"));
    closed_captions_view_hide(&t_g_cap);
    //closed_captions_view_deinit(&t_cap);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_hide_cc_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_revolt_info_hide_cc_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    //execute in timer's thread context
    nav_request_context_switch(_nav_revolt_info_timeout_to_hide_cc_timer, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_revolt_info_reset_cc_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_revolt_info_reset_cc_timer(
                    NAV_REVOLT_INFO_T*                 pt_this
                    )
{
    INT32 i4_ret;
    DBG_INFO(("[%s]++,line:%d\n",__FUNCTION__,__LINE__));
    if(pt_this == NULL)
    {
        pt_this = & t_g_nav_revolt_info;
    }

    _nav_revolt_info_stop_cc_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_cc_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_revolt_info_hide_cc_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start revolt_info::h_hide_cc_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_revolt_info_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_revolt_info_register(
                    NAV_REVOLT_INFO_VIEW_HDLR_T*      pt_view_hdlr,
                    NAV_REVOLT_INFO_STYLE             e_style
                    )
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret;

    c_memset( &t_comp, 0, sizeof(NAV_COMP_T) );

    /* NAV_COMP_ID_REVOLT_INFO */
    t_comp.pf_init           = _nav_revolt_info_init;
    t_comp.pf_deinit         = _nav_revolt_info_deinit;
    t_comp.pf_is_key_handler = _nav_revolt_info_is_key_handler;
    t_comp.pf_activate       = _nav_revolt_info_activate;
    t_comp.pf_inactivate     = _nav_revolt_info_inactivate;
    t_comp.pf_hide           = _nav_revolt_info_hide;
    t_comp.pf_handle_msg     = _nav_revolt_info_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_REVOLT_INFO, &t_comp, COMP_EXEC_SET_REVOLT_INFO);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_revolt_info_play_audio_tone
 * Description: To play the pair sound
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_revolt_info_play_audio_tone()
{
    INT32                       i4_ret   = 0;
    IMTK_PB_ERROR_CODE_T        e_return = IMTK_PB_ERROR_CODE_OK;
    IMTK_PB_CTRL_AUD_PCM_INFO_T t_parm = {0};

    DBG_INFO(("%s, [%d]\n",__FUNCTION__, __LINE__));

    e_return = IMtkPb_Snd_Init();
    if (e_return != IMTK_PB_ERROR_CODE_OK)
    {
        DBG_INFO(("IMtkPb_Snd_Init() Failed: %d!\n", e_return));
        return -1;
    }

    if (NULL_HANDLE == hPB_Handle)
    {
        DBG_INFO(("%s, [%d]",__FUNCTION__, __LINE__));

        e_return = IMtkPb_Snd_Open(&hPB_Handle, 0);
        if (e_return != IMTK_PB_ERROR_CODE_OK)
        {
            DBG_INFO(("IMtkPb_Snd_Open() Failed: %d!\n", e_return));
            return -1;
        }

        IMtkPb_Snd_RegCallback(hPB_Handle,
                               _snd_callback,
                               0);

        t_parm.e_pcm_type = IMTK_PB_CTRL_AUD_PCM_TYPE_NORMAL;
        t_parm.eNumCh = IMTK_PB_CTRL_AUD_CH_MONO;
        t_parm.eSampleRate = IMTK_PB_CTRL_AUD_SAMPLE_RATE_44K;
        t_parm.u2BlockAlign = 0;
        t_parm.eBitsPerSample = IMTK_PB_CTRL_AUD_PCM_BIT_DEPTH_16;
        t_parm.fgBigEndian = 1;

        e_return = IMtkPb_Snd_SetParameter(hPB_Handle, &t_parm);
        if (e_return != IMTK_PB_ERROR_CODE_OK)
        {
            DBG_INFO(("IMtkPb_Snd_SetParameter() Failed: %d!\n", e_return));
            IMtkPb_Snd_Close(hPB_Handle);
            hPB_Handle = NULL_HANDLE;
            return -1;
        }
    }

    e_return = IMtkPb_Snd_Play(hPB_Handle);

    if (e_return != IMTK_PB_ERROR_CODE_OK)
    {
        DBG_INFO(("IMtkPb_Snd_Play() Failed: %d!\n", e_return));
        return -1;
    }

    i4_ret = x_thread_create(&h_pair_snd_thread,
                             "_pair_cmpb_push",
                             8192,
                             128,
                             _revolt_play_tone_thread,
                             0,
                             NULL);

    if (0 != i4_ret)
    {
        DBG_INFO(("x_thread_create return fail: %d!\n", i4_ret));
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_revolt_info_set_timeout
 * Description: To set customized UI disply time
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_revolt_info_set_timeout(UINT32 ui4_timeout)
{
    g_custom_timeout   = TRUE;
    g_ui4_custom_timeout = ui4_timeout;

    DBG_INFO(("[Revolt_Info] %s, ui4_custom_timeout=%d\n", __FUNCTION__, g_ui4_custom_timeout));
    return NAVR_OK;
}

UINT32 a_revolt_info_get_timeout(VOID)
{
    DBG_LOG_PRINT(("[Revolt_Info] %s, ui4_custom_timeout=%d\n", __FUNCTION__, g_ui4_custom_timeout));
    return g_ui4_custom_timeout;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_revolt_info_get_canvas
 * Description: To get the UI canvas.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
HANDLE_T a_revolt_info_get_canvas()
{
    DBG_INFO(("[Revolt_Info] %s, line=%d\n", __FUNCTION__, __LINE__));
    return canvas;
}

#endif /* APP_537X_SUPPORT */


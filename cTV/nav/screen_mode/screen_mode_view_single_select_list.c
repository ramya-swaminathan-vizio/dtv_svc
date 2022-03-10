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
 * $RCSfile: screen_mode_view_single_select_list.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: chengwei.shan $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Chengwei Shan $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT

#include "u_common.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"

#include "nav/screen_mode/screen_mode.h"
#include "res/revolt/revolt_warnings_mlm.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/nav/screen_mode/screen_mode_view_single_select_list_custom.h"

#include "wdk/a_wdk.h"

#include "app_util/toast_widget/a_toast.h"

#ifdef APP_TTS_SUPPORT
#include "c_tts.h"
#endif
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifdef APP_TTS_SUPPORT

  #define SCREEN_MODE_VIEW_PLAYER_TTS_DELAY_TIME       (450) /* ms */

  #ifndef MAX_TXT_MSG_CHAR
    #define MAX_TXT_MSG_CHAR                 16
  #endif

#endif
#define IS_SYNC_REPAINT                         (TRUE)

#ifndef SCREEN_MODE_MAX_TXT_MSG_NUM
#define SCREEN_MODE_MAX_TXT_MSG_NUM             16
#endif

#ifndef SCREEN_MODE_MAX_TXT_MSG_CHAR
#define SCREEN_MODE_MAX_TXT_MSG_CHAR            32
#endif

typedef struct _NAV_SCREEN_MODE_VIEW_T
{
    /* Internal Control */

    NAV_SCREEN_MODE_T*          pt_ctrl;
    BOOL                        b_is_refreshing;     /* FALSE -> Do Process Notification */
                                                     /* TRUE  -> No Process Notification */

    BOOL                        b_is_enable_change;
    UINT16                      ui2_curr_idx;
    UINT16                      ui2_elem_num;
    UINT16                      ui2_origin_elem_num;
    HANDLE_T                    h_canvas;
    HANDLE_T                    h_toast_view;
#ifdef APP_TTS_SUPPORT
    HANDLE_T                    h_tts_sound;        /* for voice prompt */
    TTS_STRING_T                t_sound_content;    /* store sound content to output. */
    HANDLE_T                    h_tts_timer;        /* for tts timer*/
#endif

} NAV_SCREEN_MODE_VIEW_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_SCREEN_MODE_VIEW_T t_g_nav_screen_mode_view       = {0};

static UTF16_T             w2s_title_msg[SCREEN_MODE_MAX_TXT_MSG_CHAR];
static UTF16_T*            apw2s_txt_msg[SCREEN_MODE_MAX_TXT_MSG_NUM];

static BOOL                b_g_toggle_by_btn_smart_pic = FALSE;
static BOOL                b_g_exit_by_btn_smart_pic   = FALSE;
static BOOL                b_g_exit_by_btn_select      = FALSE;
static WDK_OSD_TOAST_T      t_g_wdk_view={0} ;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_single_select_list_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32 _nav_screen_mode_view_single_select_list_wdgt_msg_cb_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );
#ifdef APP_TTS_SUPPORT
static VOID _nav_screen_mode_reset_tts_timer(NAV_SCREEN_MODE_VIEW_T* pt_this,CHAR *ps_str);
static VSH_SRC_ASPECT_RATIO_T _nav_screen_mode_view_get_src_asp_ratio (
                                TV_WIN_ID_T             e_focus_tv_win_id
                                );
#endif

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: alloc text buffer for apw2s_txt_msg
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  __screen_mode_alloc_text(VOID)
{
    UINT8           ui1_idx;

    for (ui1_idx = 0 ; ui1_idx < SCREEN_MODE_MAX_TXT_MSG_NUM; ui1_idx++)
    {
        apw2s_txt_msg[ui1_idx] = c_mem_alloc(SCREEN_MODE_MAX_TXT_MSG_CHAR * sizeof(UTF16_T));

        if (apw2s_txt_msg[ui1_idx] == NULL)
        {
            DBG_ERROR(("[NAV] screen_mode_alloc_text fail. \n"));
            return NAVR_FAIL;
        }

        /* Clear the content first */
        c_memset(apw2s_txt_msg[ui1_idx], 0, SCREEN_MODE_MAX_TXT_MSG_CHAR * sizeof(UTF16_T));
    }

    return NAVR_OK;
}

static INT32  __screen_mode_free_text(VOID)
{
    UINT8           ui1_idx;

    for (ui1_idx = 0; ui1_idx < SCREEN_MODE_MAX_TXT_MSG_NUM; ui1_idx++)
    {
        if (apw2s_txt_msg[ui1_idx] != NULL)
        {
            c_mem_free(apw2s_txt_msg[ui1_idx]);
            apw2s_txt_msg[ui1_idx] = NULL;
        }
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Return the judgement for key.
 *              Currently, it listens BTN_ASPECT
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _nav_screen_mode_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_DEBUG_ASPECT_RADIO( DBG_LOG_PRINT(("[NAV][ASPECT]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, ui4_key_code )); );

    return nav_screen_mode_view_custom_single_list_is_key_handler(ui4_key_code);
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Activate the view, focus on the "Listbox"
 *              Currently, it listens BTN_P_EFFECT.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_SCREEN_MODE_VIEW_T* pt_view = &t_g_nav_screen_mode_view;
    WDK_TOAST_PARAM_T       t_widget_param;
    UINT8                   ui1_idx = 0;
    BOOL                    b_enable = TRUE;
    INT32                   i4_ret = NAVR_OK;

#if 0
    CHAR                     s_buf[SCREEN_MODE_MAX_TXT_MSG_CHAR+1];
#endif

    DBG_LOG_PRINT(("%s, %d. ui2_curr_idx: %d, ui2_elem_num: %d. -------\n",
                        __FUNCTION__, __LINE__,
                        pt_view->ui2_curr_idx,
                        pt_view->ui2_elem_num)
                        );

    i4_ret = a_cfg_custom_get_wide_mode_enable_change(&b_enable);
    if (APP_CFGR_OK == i4_ret && FALSE == b_enable)
    {
        pt_view->b_is_enable_change = FALSE;
    }
    else
    {
        pt_view->b_is_enable_change = TRUE;
    }

    if (FALSE == pt_view->b_is_enable_change)
    {
        TOAST_CUSTOMIZATION_DATA_T t_custom_setting;

        if (NULL_HANDLE == pt_view->h_toast_view)
        {
            TOAST_INIT_PARAM_T  t_toast_init;

            c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
            t_toast_init.h_canvas                                   = pt_view->h_canvas;
            t_toast_init.e_toast_style                              = TOAST_STYLE_MSG;
            t_toast_init.t_custom_setting.u.t_msg_init.e_msg_type   = TOAST_MSG_TYPE_WITH_WARNING_ICON;
            a_toast_create(&t_toast_init, &pt_view->h_toast_view);
        }

        c_memset(&t_custom_setting, 0, sizeof(TOAST_CUSTOMIZATION_DATA_T));
        t_custom_setting.u.t_msg_init.w2s_msg_str = WGL_PACK(MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_23));
        i4_ret = a_toast_show(pt_view->h_toast_view, &t_custom_setting);
    }
    else
    {
        DBG_INFO(("%s,%d [scr mode]elem_num= %d, origin_num=%d \r\n",
                    __FUNCTION__,__LINE__,pt_view->ui2_elem_num,pt_view->ui2_origin_elem_num));

        if(pt_view->ui2_elem_num != pt_view->ui2_origin_elem_num)
        {
            pt_view->ui2_origin_elem_num = pt_view->ui2_elem_num;
            DBG_LOG_PRINT(("%s,%d [scr mode] toast deinit \r\n",__FUNCTION__,__LINE__));
            a_wdk_toast_deinit(&t_g_wdk_view);
        }

        c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));

        if (FALSE == t_g_wdk_view.b_have_init)
        {
            t_widget_param.e_toast_style = WDK_SINGLE_SELECT_LIST;
            t_widget_param.w2s_msg_t.i4_str_num = pt_view->ui2_elem_num;
            t_widget_param.b_is_pic_mode = FALSE;

            DBG_LOG_PRINT(("%s,%d [scr mode] toast init again \r\n",__FUNCTION__,__LINE__));
            a_wdk_toast_init(pt_view->h_canvas, &t_widget_param,&t_g_wdk_view);
        }

        t_widget_param.e_toast_style = WDK_SINGLE_SELECT_LIST;
        t_widget_param.w2s_msg_t.i4_str_num = pt_view->ui2_elem_num;
        t_widget_param.w2s_msg_t.e_msy_style = WDK_MSG_SEPARATELY;
        t_widget_param.w2s_str = WGL_PACK(w2s_title_msg);
        t_widget_param.ui4_sl_focus_num = pt_view->ui2_curr_idx;
        t_widget_param.h_t_focus_handle = t_g_wdk_view.h_list_txt[pt_view->ui2_curr_idx];
        t_widget_param.pf_cb = _nav_screen_mode_view_single_select_list_wdgt_proc_fct;
        t_widget_param.pf_send_msg_cb = _nav_screen_mode_view_single_select_list_wdgt_msg_cb_fct;

        for (ui1_idx = 0; ui1_idx < pt_view->ui2_elem_num && ui1_idx < SCREEN_MODE_MAX_TXT_MSG_NUM; ui1_idx++)
        {
        #if 0
            c_memset(s_buf, 0, sizeof(s_buf));
            c_uc_w2s_to_ps(apw2s_txt_msg[ui1_idx], s_buf, SCREEN_MODE_MAX_TXT_MSG_CHAR);
            DBG_LOG_PRINT(("[KK] %s, %d. pw2s_text: %s. -------\n", __FUNCTION__, __LINE__, s_buf));
        #endif
            t_widget_param.w2s_msg_t.w2s_str[ui1_idx] = (VOID*)(apw2s_txt_msg[ui1_idx]);
        }

        i4_ret = a_wdk_toast_activate(TRUE, &t_widget_param,&t_g_wdk_view);
    }

 #ifdef APP_TTS_SUPPORT
      /* get an instance of sound player. */
      if ((pt_view->h_tts_sound) == NULL_HANDLE)
      {
          i4_ret = c_tts_open_default_instance_fct(&(pt_view->h_tts_sound));
          if (i4_ret != OSR_OK)
          {
                DBG_LOG_PRINT(("{screen_mode}ERROR(%d): c_tts_open_default_instance_fct fail! i4_ret=%d.\n",__LINE__,i4_ret));
                return NAVR_FAIL;
          }
      }
#endif

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_hide(
                    VOID
                    )
{
    NAV_SCREEN_MODE_VIEW_T* pt_view = &t_g_nav_screen_mode_view;

    if (pt_view->b_is_enable_change)
    {
        a_wdk_toast_hide(TRUE, NULL,&t_g_wdk_view);
    }
    else
    {
        a_toast_hide(pt_view->h_toast_view);
    }

#ifdef APP_TTS_SUPPORT
    /* stop to read screen mode when details hided. */
    c_tts_stop_fct(pt_view->h_tts_sound);
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_SCREEN_MODE_VIEW_T* pt_view = &t_g_nav_screen_mode_view;

    switch(ui4_key_code) {
    case PSEUDO_BTN_ASPECT:
    case BTN_ASPECT:
    case BTN_CURSOR_LEFT:
    case BTN_CURSOR_RIGHT:
        nav_screen_mode_reset_timer(pt_view->pt_ctrl);
        break;
    case BTN_EXIT:
        nav_hide_component(NAV_COMP_ID_SCREEN_MODE);
        break;
    case BTN_SELECT:
        break;
    default:
        nav_rcu_key_handler(ui4_key_code);
        break;
    }
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Single select list's wdgt proc fct.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_single_select_list_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret = 0;

    if(ui4_msg == WGL_MSG_KEY_DOWN)
    {
        /* Translate BTN_CURSOR_RIGHT => BTN_CURSOR_LEFT */
        //if( (UINT32) pv_param1 == BTN_CURSOR_RIGHT )
        //{
        //    pv_param1 = (VOID *) BTN_CURSOR_LEFT;
        //}

        /* Can be customized */
        /* Translate BTN_SMART_PIC => BTN_CURSOR_LEFT */
        if(b_g_toggle_by_btn_smart_pic)
        {
            if ((UINT32) pv_param1 == PSEUDO_BTN_ASPECT ||
                (UINT32) pv_param1 == BTN_ASPECT)
            {
                pv_param1 = (VOID *) BTN_CURSOR_RIGHT;
            }
        }

        /* Can be customized */
        /* Translate BTN_P_EFFECT to EXIT */
        if(b_g_exit_by_btn_smart_pic)
        {
            if ((UINT32) pv_param1 == PSEUDO_BTN_ASPECT ||
                (UINT32) pv_param1 == BTN_ASPECT)
            {
                nav_hide_component(NAV_COMP_ID_SCREEN_MODE);
                return WGLR_OK;    /* Return Directly */
            }
        }

        /* Can be customized */
        /* Translate BTN_SELECT to EXIT */
        if(b_g_exit_by_btn_select)
        {
            if( (UINT32) pv_param1 == BTN_SELECT )
            {
                nav_hide_component(NAV_COMP_ID_SCREEN_MODE);
                nav_screen_mode_ctrl_update_index();
                return WGLR_OK;    /* Return Directly */
            }
        }
    }

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:

        /* Run NAV default key handler first */
        _nav_screen_mode_view_rcu_key_handler((UINT32)pv_param1);
        break;

    default:
        break;
    }

    /* Run WIDGET default key handler next */
    i4_ret = wdk_widget_select_list_proc_fct(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Single select list's wdgt message callback func.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_single_select_list_wdgt_msg_cb_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    WDK_WIDGET_SEND_MSG_T *wdk_widget_msg = (WDK_WIDGET_SEND_MSG_T*) pv_param1;

    if (!wdk_widget_msg)
    {
        return NAVR_OK;
    }

    DBG_API(("[KK] %s, %d. keycode: %u, index: %u.\n",
                        __FUNCTION__, __LINE__,
                        wdk_widget_msg->ui4_keycode,
                        wdk_widget_msg->ui4_selected_num));

    nav_screen_mode_ctrl_set_index(wdk_widget_msg->ui4_selected_num);

#ifdef APP_TTS_SUPPORT
    NAV_SCREEN_MODE_VIEW_T *pt_view = &t_g_nav_screen_mode_view;
    UINT16 ui2_idx = wdk_widget_msg->ui4_selected_num;
    CHAR *ps_txt = NULL;
    VSH_SRC_ASPECT_RATIO_T e_src_aspect = _nav_screen_mode_view_get_src_asp_ratio(TV_WIN_ID_MAIN);

    SCC_VID_SCREEN_MODE_T e_curr_scr_mode = 0;
    a_nav_screen_mode_get_cur_mode(&e_curr_scr_mode);

    switch(e_curr_scr_mode)
    {
        case SCC_VID_SCREEN_MODE_NORMAL:
            ps_txt = "CHANGE ASPECT RATIO normal";break;
        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
            ps_txt = "CHANGE ASPECT RATIO panoramic";break;
        case SCC_VID_SCREEN_MODE_LETTERBOX:
            ps_txt = "CHANGE ASPECT RATIO stretch"; break;
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
            ps_txt = "CHANGE ASPECT RATIO zoom";break;
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
            ps_txt = "CHANGE ASPECT RATIO wide";break;
        default:
            ps_txt = "error";break;
    }

#if 0
    switch(ui2_idx)
    {
        case 0:
            ps_txt = "CHANGE ASPECT RATIO wide";break;
        case 1:
            ps_txt = "CHANGE ASPECT RATIO zoom";break;
        case 2:
            ps_txt = "CHANGE ASPECT RATIO normal";break;
        case 3:
            ps_txt = (VSH_SRC_ASPECT_RATIO_4_3 == e_src_aspect) ? "CHANGE ASPECT RATIO panoramic" : "CHANGE ASPECT RATIO stretch"; break;
        case 4:
            ps_txt = (VSH_SRC_ASPECT_RATIO_4_3 == e_src_aspect) ? "CHANGE ASPECT RATIO panoramic" : "CHANGE ASPECT RATIO stretch"; break;
        case 5:
            ps_txt = "end";break;
        default:
            ps_txt = "error";break;
    }
#endif
    DBG_INFO(("[tts]%s(), %d ,string=%s,slect num=%d   \n" ,__FUNCTION__,__LINE__,ps_txt,ui2_idx));

    _nav_screen_mode_reset_tts_timer(pt_view, ps_txt);

#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_init(
                    NAV_SCREEN_MODE_T*                pt_ctrl,
                    HANDLE_T                       h_canvas,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset,
                    UINT16                         ui2_elem_num
                    )
{
    WDK_TOAST_PARAM_T       t_widget_param;
    BOOL                    b_enable = TRUE;
    INT32                   i4_ret = NAVR_OK;
    NAV_SCREEN_MODE_VIEW_T* pt_view = &t_g_nav_screen_mode_view;

    /* alloc space for ui2_elem_num */
    __screen_mode_alloc_text();

    c_memset(pt_view, 0, sizeof(NAV_SCREEN_MODE_VIEW_T));

    /* Save the ctrl to view */
    pt_view->pt_ctrl = pt_ctrl;
    pt_view->h_canvas = h_canvas;
    pt_view->h_toast_view = NULL_HANDLE;

    c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));

    i4_ret = a_cfg_custom_get_wide_mode_enable_change(&b_enable);
    if (APP_CFGR_OK == i4_ret && FALSE == b_enable)
    {
        pt_view->b_is_enable_change = FALSE;
    }
    else
    {
        pt_view->b_is_enable_change = TRUE;
    }

    if (FALSE == pt_view->b_is_enable_change)
    {
        TOAST_INIT_PARAM_T  t_toast_init;

        c_memset(&t_toast_init, 0, sizeof(TOAST_INIT_PARAM_T));
        t_toast_init.h_canvas                                   = h_canvas;
        t_toast_init.e_toast_style                              = TOAST_STYLE_MSG;
        t_toast_init.t_custom_setting.u.t_msg_init.e_msg_type   = TOAST_MSG_TYPE_WITH_WARNING_ICON;
        a_toast_create(&t_toast_init, &pt_view->h_toast_view);
    }
    else
    {
        t_widget_param.e_toast_style = WDK_SINGLE_SELECT_LIST;
        t_widget_param.w2s_msg_t.i4_str_num = ui2_elem_num;
        t_widget_param.b_is_pic_mode = FALSE;

        a_wdk_toast_init(h_canvas, &t_widget_param,&t_g_wdk_view);
    }

#ifdef APP_TTS_SUPPORT
      i4_ret = c_timer_create(&(pt_view->h_tts_timer));
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }
      /* set tts handle to NULL. */
      pt_view->h_tts_sound = NULL_HANDLE;
      pt_view->t_sound_content.ui4_id = 1;  /* init id is 1, then add 1 each time play sound. */
#endif

    /* Customization Environment */
    b_g_toggle_by_btn_smart_pic = NAV_SCREEN_MODE_TOGGLE_BY_BTN_ASPECT;
    b_g_exit_by_btn_smart_pic   = NAV_SCREEN_MODE_EXIT_BY_BTN_ASPECT;
    b_g_exit_by_btn_select      = NAV_SCREEN_MODE_EXIT_BY_BTN_SELECT;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_deinit(
                    VOID
                    )
{
    NAV_SCREEN_MODE_VIEW_T* pt_view = &t_g_nav_screen_mode_view;

    pt_view->pt_ctrl     = NULL;

    __screen_mode_free_text();

    if (FALSE == pt_view->b_is_enable_change)
    {
        a_toast_destroy(pt_view->h_toast_view);
    }
    else
    {
        a_wdk_toast_deinit(&t_g_wdk_view);
    }

#ifdef APP_TTS_SUPPORT
    if (c_handle_valid(pt_view->h_tts_timer) == TRUE)
    {
        c_timer_delete(pt_view->h_tts_timer);
    }
#endif

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the _nav_screen_mode_view_set_elem_num index
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_set_elem_num(UINT16    ui2_num)
{
    NAV_SCREEN_MODE_VIEW_T *pt_view = &t_g_nav_screen_mode_view;

    pt_view->ui2_elem_num = ui2_num;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the highlight index
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_set_hlt_index(UINT16    ui2_idx)
{
    NAV_SCREEN_MODE_VIEW_T *pt_view = &t_g_nav_screen_mode_view;

    pt_view->ui2_curr_idx = ui2_idx;

#ifdef APP_TTS_SUPPORT
    VSH_SRC_ASPECT_RATIO_T e_src_aspect = _nav_screen_mode_view_get_src_asp_ratio(TV_WIN_ID_MAIN);
    CHAR *ps_txt = NULL;
    static CHAR s_txt[128] = {0};
    SCC_VID_SCREEN_MODE_T e_curr_scr_mode = 0;
    a_nav_screen_mode_get_cur_mode(&e_curr_scr_mode);

    if (pt_view->b_is_enable_change)
    {
        switch(e_curr_scr_mode)
        {
            case SCC_VID_SCREEN_MODE_NORMAL:
                ps_txt = "CHANGE ASPECT RATIO normal";break;
            case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
                ps_txt = "CHANGE ASPECT RATIO panoramic";break;
            case SCC_VID_SCREEN_MODE_LETTERBOX:
                ps_txt = "CHANGE ASPECT RATIO stretch"; break;
            case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
                ps_txt = "CHANGE ASPECT RATIO zoom";break;
            case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
                ps_txt = "CHANGE ASPECT RATIO wide";break;
            default:
                ps_txt = "error";break;
        }

#if 0
        switch(ui2_idx)
        {
            case 0:
                ps_txt = "CHANGE ASPECT RATIO wide";break;
            case 1:
                ps_txt = "CHANGE ASPECT RATIO zoom";break;
            case 2:
                ps_txt = "CHANGE ASPECT RATIO normal";break;
            case 3:
                ps_txt = (VSH_SRC_ASPECT_RATIO_4_3 == e_src_aspect) ? "CHANGE ASPECT RATIO panoramic" : "CHANGE ASPECT RATIO stretch"; break;
            case 4:
                ps_txt = (VSH_SRC_ASPECT_RATIO_4_3 == e_src_aspect) ? "CHANGE ASPECT RATIO panoramic" : "CHANGE ASPECT RATIO stretch"; break;
            case 5:
                ps_txt = "end";break;
            default:
                ps_txt = "error";break;
        }
#endif
    }
    else
    {
        c_memset(s_txt, 0, sizeof(s_txt));
        c_uc_w2s_to_ps(MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_23), s_txt, 127);
        ps_txt = s_txt;
    }
    DBG_LOG_PRINT(("[tts]%s(), %d ,%s   \n",__FUNCTION__,__LINE__,ps_txt));
    _nav_screen_mode_reset_tts_timer(pt_view, ps_txt);

#endif

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the index's text
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_set_index_text(UINT16    ui2_idx,
                                               UTF16_T*  pw2s_text)
{
    if (ui2_idx > SCREEN_MODE_MAX_TXT_MSG_NUM - 1)
    {
        return NAVR_FAIL;
    }

    c_uc_w2s_strcpy((UTF16_T*)apw2s_txt_msg[ui2_idx], pw2s_text);
    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the refreshing flag.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_set_is_refreshing(BOOL      b_is_refreshing)
{
    NAV_SCREEN_MODE_VIEW_T *pt_view = &t_g_nav_screen_mode_view;

    /* Set the b_enable status to indicate whether do notification or not */
    pt_view->b_is_refreshing = b_is_refreshing;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the title text.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_view_set_title_text(UTF16_T*  pw2s_title)

{
    c_memset(w2s_title_msg, 0, sizeof(w2s_title_msg));
    c_uc_w2s_strcpy(w2s_title_msg, pw2s_title);
    return NAVR_OK;
}

#ifdef APP_TTS_SUPPORT
static VSH_SRC_ASPECT_RATIO_T _nav_screen_mode_view_get_src_asp_ratio (
                                TV_WIN_ID_T             e_focus_tv_win_id
                                )
{
    INT32                       i4_ret;
    VSH_SRC_RESOLUTION_INFO_T   t_src_res;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;;

    c_memset(&t_src_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    /* Get source aspect ratio. */
    i4_ret = nav_get_crnt_video_res_info (e_focus_tv_win_id, &t_src_res);

    if ((i4_ret != NAVR_OK) ||
        (t_src_res.ui4_width == 0) ||
        (t_src_res.ui4_height == 0) ||
        (t_src_res.e_timing_type == VSH_SRC_TIMING_NOT_SUPPORT))
    {
        e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;
    }
    else
    {
        /* Get aspect ratio from Screen Mode Library. */
        e_src_asp_ratio = a_sml_get_src_asp_ratio (& t_src_res);
    }

    if (VSH_SRC_ASPECT_RATIO_UNKNOWN == e_src_asp_ratio)
    {
        e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
        //e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_16_9;
    }

    return e_src_asp_ratio;
}

/*--------------------------------------------------------------------------
---
 * Name
 *      _screen_mode_tts_play_string
 * Description
 * Input arguments
 * Output arguments
 * Returns  -

*---------------------------------------------------------------------------*/
static VOID  _nav_screen_mode_tts_play_string(VOID* pv_arg1,
                                VOID* pv_arg2,
                                VOID* pv_arg3)
{
    INT32       i4_ret;
    NAV_SCREEN_MODE_VIEW_T*  pt_this = &t_g_nav_screen_mode_view;
    CHAR *ps_str          = (CHAR *)pv_arg1;

    /* get an instance of sound player. */
    if ((pt_this->h_tts_sound) == NULL_HANDLE)
    {
        i4_ret = c_tts_open_default_instance_fct(&(pt_this->h_tts_sound));
        if (i4_ret != OSR_OK)
        {
            DBG_LOG_PRINT(("<SCREEN_MODE>ERROR(%d): c_tts_open_default_instance_fct fail! i4_ret=%d.\n",__LINE__,i4_ret));
            return ;
        }
    }

    if ((ps_str != NULL) && (c_strlen(ps_str)>0))
    {
        pt_this->t_sound_content.ui4_id++;
        pt_this->t_sound_content.ui4_size = c_strlen(ps_str);
        pt_this->t_sound_content.ps_string = ps_str;

        DBG_INFO(("[TTS]: c_tts_stop_fct begain,ms=%d,%s,line:%d\n",  c_os_get_sys_tick() * c_os_get_sys_tick_period(), __FUNCTION__,__LINE__));
        c_tts_stop_fct(pt_this->h_tts_sound);

        DBG_INFO(("[TTS]: c_tts_play_fct begain,ms=%d,%s,line:%d\n",  c_os_get_sys_tick() * c_os_get_sys_tick_period(),__FUNCTION__, __LINE__));
        i4_ret = c_tts_play_fct(pt_this->h_tts_sound);
        if (i4_ret != OSR_OK)
        {
            DBG_INFO(("<SCRN_MODE>%s ERROR(%d): c_tts_play_fct fail! i4_ret=%d.\n",__FUNCTION__,__LINE__,i4_ret));
            return ;
        }

        if (i4_ret == TTSR_OK)
        {
            DBG_INFO(("[TTS]: c_tts_send_string_fct begain,ms=%d,%s,line:%d\n",  c_os_get_sys_tick() * c_os_get_sys_tick_period(), __FUNCTION__,__LINE__));

            i4_ret = c_tts_send_string_fct(pt_this->h_tts_sound,&(pt_this->t_sound_content));
            if (i4_ret != TTSR_OK)
            {
                DBG_LOG_PRINT(("<SCREEN_MODE>%s ERROR(%d): c_tts_send_string_fct fail! i4_ret=%d.\n",__FUNCTION__,__LINE__,i4_ret));
            }
            DBG_INFO(("[TTS]: c_tts_send_string_fct end,ms=%d,line:%d\n",  c_os_get_sys_tick() * c_os_get_sys_tick_period(), __LINE__));

        }
        else
        {
            DBG_INFO(("<SCREEN_MODE>%s ERROR(%d): c_tts_play_fct fail! i4_ret=%d.\n",__FUNCTION__,__LINE__,i4_ret));
        }
    }
    else
    {
        i4_ret = NAVR_INV_ARG;
        DBG_INFO(("<SCREEN_MODE>%s ERROR(%d): ps_str is NULL! or the length of ps_str is 0.\n",__FUNCTION__,__LINE__));
    }

    return ;
}

/*--------------------------------------------------------------------------
---
 * Name
 *      _screen_mode_tts_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns

*---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_tts_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* switch to execute context */
    nav_request_context_switch(_nav_screen_mode_tts_play_string, pv_tag, NULL, NULL);
}

/*--------------------------------------------------------------------------
---
 * Name
 *      _scrn_scr_reset_tts_timer
 * Description: reset the tts timer.
 * Input arguments
 * Output arguments
 * Returns

*---------------------------------------------------------------------------*/
 VOID _nav_screen_mode_reset_tts_timer(
                    NAV_SCREEN_MODE_VIEW_T*              pt_this,
                    CHAR*  ps_str
                    )
{
    INT32 i4_ret;
    if(!a_cfg_get_tts_play_enable())
    {
        DBG_LOG_PRINT(("[POWER ON +++] {%s %s() %d}. there is not support TTS.\n",__FILE__, __FUNCTION__, __LINE__));
        return ;
    }

    if (c_handle_valid(pt_this->h_tts_timer) == FALSE)
    {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_tts_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR(("stop screen_mode_reset_tts_timer::h_tts_timer failed!"));
    }

    i4_ret = c_timer_start(
                    pt_this->h_tts_timer,
                    SCREEN_MODE_VIEW_PLAYER_TTS_DELAY_TIME,
                    X_TIMER_FLAG_ONCE,
                    _nav_screen_mode_tts_timer_nfy,
                    ps_str
                    );
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR(("start screen_mode_reset_tts_timer::h_tts_timer failed!"));
    }
}

#endif

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_screen_mode_view_register_single_select_list_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_screen_mode_view_register_single_select_list_hdlr(
                    NAV_SCREEN_MODE_VIEW_HDLR_T*    pt_view_hdlr
                    )
{
    NAV_DEBUG_ASPECT_RADIO( DBG_LOG_PRINT(("[NAV][ASPECT]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init              = _nav_screen_mode_view_init;
    pt_view_hdlr->pf_deinit            = _nav_screen_mode_view_deinit;
    pt_view_hdlr->pf_is_key_handler    = _nav_screen_mode_view_is_key_handler;
    pt_view_hdlr->pf_activate          = _nav_screen_mode_view_activate;
    pt_view_hdlr->pf_hide              = _nav_screen_mode_view_hide;
    pt_view_hdlr->pf_set_elem_num      = _nav_screen_mode_view_set_elem_num;
    pt_view_hdlr->pf_set_hlt_index     = _nav_screen_mode_view_set_hlt_index;
    pt_view_hdlr->pf_set_index_text    = _nav_screen_mode_view_set_index_text;
    pt_view_hdlr->pf_set_is_refreshing = _nav_screen_mode_view_set_is_refreshing;
    pt_view_hdlr->pf_set_title_text    = _nav_screen_mode_view_set_title_text;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

#endif /* APP_537X_SUPPORT */

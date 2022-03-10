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
 * $RCSfile: pic_mode_view_single_select_list.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
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
#include "c_svctx.h"

#include "wizard_anim/a_wzd.h"
#include "nav/pic_mode/pic_mode.h"
#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/nav/pic_mode/pic_mode_view_single_select_list_custom.h"

#include "wdk/a_wdk.h"

#include "res/menu2/menu_mlm.h"

#ifdef  APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

#ifndef SINGLE_SELECT_MAX_TXT_MSG_NUM
#define SINGLE_SELECT_MAX_TXT_MSG_NUM           16
#endif

#ifndef SINGLE_SELECT_MAX_TXT_MSG_CHAR
#define SINGLE_SELECT_MAX_TXT_MSG_CHAR          32
#endif

#define PIC_MODE_VIEW_TTS_DELAY_TIME            (450) /* ms */

typedef struct _NAV_PIC_MODE_VIEW_T
{
    /* Internal Control */

    NAV_PIC_MODE_T*             pt_ctrl;
    BOOL                        b_is_refreshing;     /* FALSE -> Do Process Notification */
                                                     /* TRUE  -> No Process Notification */
    UINT16                      ui2_curr_idx;
    UINT16                      ui2_elem_num;

} NAV_PIC_MODE_VIEW_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_PIC_MODE_VIEW_T t_g_nav_pic_mode_view       = {0};

static UTF16_T             w2s_title_msg[SINGLE_SELECT_MAX_TXT_MSG_CHAR];
static UTF16_T*            apw2s_txt_msg[SINGLE_SELECT_MAX_TXT_MSG_NUM];

static BOOL                b_g_toggle_by_btn_smart_pic = FALSE;
static BOOL                b_g_exit_by_btn_smart_pic   = FALSE;
static BOOL                b_g_exit_by_btn_select      = FALSE;
static WDK_OSD_TOAST_T  	t_g_wdk_view={0} ;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_single_select_list_wdgt_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32 _nav_pic_mode_view_single_select_list_wdgt_msg_cb_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );
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
static INT32  __pic_mode_alloc_text(VOID)
{
    UINT8           ui1_idx;

    for (ui1_idx = 0 ; ui1_idx < SINGLE_SELECT_MAX_TXT_MSG_NUM; ui1_idx++)
    {
        apw2s_txt_msg[ui1_idx] = c_mem_alloc(SINGLE_SELECT_MAX_TXT_MSG_CHAR * sizeof(UTF16_T));

        if (apw2s_txt_msg[ui1_idx] == NULL)
        {
            DBG_ERROR(("[NAV] pic_mode_alloc_text fail. \n"));
            return NAVR_FAIL;
        }

        /* Clear the content first */
        c_memset(apw2s_txt_msg[ui1_idx], 0, SINGLE_SELECT_MAX_TXT_MSG_CHAR * sizeof(UTF16_T));
    }

    return NAVR_OK;
}

static INT32  __pic_mode_free_text(VOID)
{
    UINT8           ui1_idx;

    for (ui1_idx = 0; ui1_idx < SINGLE_SELECT_MAX_TXT_MSG_NUM; ui1_idx++)
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
 *              Currently, it listens BTN_P_EFFECT
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _nav_pic_mode_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_DEBUG_PIC_MODE( DBG_LOG_PRINT(("[NAV][PIC_MODE]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, ui4_key_code )); );

    return nav_pic_mode_view_custom_single_list_is_key_handler(ui4_key_code);
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
static INT32 _nav_pic_mode_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_PIC_MODE_VIEW_T*  pt_view = &t_g_nav_pic_mode_view;
    WDK_TOAST_PARAM_T     t_widget_param;
    UINT8                 ui1_idx = 0;
    INT32                 i4_ret = NAVR_OK;

#if 0
    CHAR                  s_buf[SINGLE_SELECT_MAX_TXT_MSG_CHAR+1];
#endif

    DBG_LOG_PRINT(("%s, %d. ui2_curr_idx: %d, ui2_elem_num: %d. -------\n",
                        __FUNCTION__, __LINE__,
                        pt_view->ui2_curr_idx,
                        pt_view->ui2_elem_num)
                        );

    c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));

    t_widget_param.e_toast_style = WDK_SINGLE_SELECT_LIST;
	t_widget_param.w2s_msg_t.i4_str_num = pt_view->ui2_elem_num;
	t_widget_param.w2s_msg_t.e_msy_style = WDK_MSG_SEPARATELY;
	t_widget_param.w2s_str = WGL_PACK(w2s_title_msg);
	t_widget_param.ui4_sl_focus_num = pt_view->ui2_curr_idx;
	t_widget_param.h_t_focus_handle = t_g_wdk_view.h_list_txt[pt_view->ui2_curr_idx];
	t_widget_param.pf_cb = _nav_pic_mode_view_single_select_list_wdgt_proc_fct;
	t_widget_param.pf_send_msg_cb = _nav_pic_mode_view_single_select_list_wdgt_msg_cb_fct;

    for (ui1_idx = 0; ui1_idx < pt_view->ui2_elem_num && ui1_idx < SINGLE_SELECT_MAX_TXT_MSG_NUM; ui1_idx++)
	{
	#if 0
	    c_memset(s_buf, 0, sizeof(s_buf));
	    c_uc_w2s_to_ps(apw2s_txt_msg[ui1_idx], s_buf, SINGLE_SELECT_MAX_TXT_MSG_CHAR);
        DBG_LOG_PRINT(("[KK] %s, %d. pw2s_text: %s. -------\n", __FUNCTION__, __LINE__, s_buf));
    #endif
        t_widget_param.w2s_msg_t.w2s_str[ui1_idx] = (VOID*)(apw2s_txt_msg[ui1_idx]);
	}

    if (c_wgl_float(t_g_wdk_view.h_base_frm, TRUE, FALSE) != WGLR_OK) {
        DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
    }

    i4_ret = a_wdk_toast_activate(TRUE, &t_widget_param,&t_g_wdk_view);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_hide(
                    VOID
                    )
{
    if (c_wgl_float(t_g_wdk_view.h_base_frm, FALSE, FALSE) != WGLR_OK) {
        DBG_ERROR(("[NAV] {%s,%d} fail.\r\n", __FUNCTION__, __LINE__));
    }

    a_wdk_toast_hide(TRUE, NULL,&t_g_wdk_view);
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
static VOID _nav_pic_mode_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;

    switch(ui4_key_code) {
    case BTN_P_EFFECT:
    case BTN_CURSOR_LEFT:
    case BTN_CURSOR_RIGHT:
        nav_pic_mode_reset_timer(pt_view->pt_ctrl);
        break;
    case BTN_EXIT:
        nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
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
static INT32 _nav_pic_mode_view_single_select_list_wdgt_proc_fct(
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
            if( (UINT32) pv_param1 == BTN_P_EFFECT )
            {
                pv_param1 = (VOID *) BTN_CURSOR_RIGHT;
            }
        }

        /* Can be customized */
        /* Translate BTN_P_EFFECT to EXIT */
        if(b_g_exit_by_btn_smart_pic)
        {
            if( (UINT32) pv_param1 == BTN_P_EFFECT )
            {
                nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
                return WGLR_OK;    /* Return Directly */
            }
        }

        /* Can be customized */
        /* Translate BTN_SELECT to EXIT */
        if(b_g_exit_by_btn_select)
        {
            if( (UINT32) pv_param1 == BTN_SELECT )
            {
                nav_hide_component(NAV_COMP_ID_PICTURE_EFFECT);
                nav_pic_mode_ctrl_update_index();
                return WGLR_OK;    /* Return Directly */
            }
        }

        if (a_wzd_is_oobe_mode())
        {
            switch ((UINT32)pv_param1)
            {
                case BTN_P_EFFECT:
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                case BTN_SELECT:
                case BTN_EXIT:
                    break;
                default:
                    return WGLR_OK;
            }
        }
    }

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:

        /* Run NAV default key handler first */
        _nav_pic_mode_view_rcu_key_handler((UINT32)pv_param1);
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
static INT32 _nav_pic_mode_view_wdgt_msg_tts_play_txt(UINT16 ui2_idx)
{
    UTF16_T w2s_tts_dst[512] = {0};

    c_uc_w2s_strcpy(w2s_tts_dst, w2s_title_msg);

    /* when dobly vision is playing,check picture mode title and
       tts play Dolby vision string    */
    if(a_acfg_cust_get_video_type() == SCC_VID_PQ_DOVI)
    {
        DBG_INFO(("[Dolby +++] {%s %s() %d}. SCC_VID_PQ_DOVI\n",__FILE__, __FUNCTION__, __LINE__));
      c_uc_w2s_strncat(w2s_tts_dst,L" ",c_uc_w2s_strlen(L" "));
      c_uc_w2s_strncat(w2s_tts_dst,L"Dolby vision",c_uc_w2s_strlen(L"Dolby vision"));
    }

    c_uc_w2s_strncat(w2s_tts_dst,L" ",c_uc_w2s_strlen(L" "));
    c_uc_w2s_strncat(w2s_tts_dst,apw2s_txt_msg[ui2_idx],c_uc_w2s_strlen(apw2s_txt_msg[ui2_idx]));
    a_app_tts_play_new_gap_just_once(w2s_tts_dst,c_uc_w2s_strlen(w2s_tts_dst),PIC_MODE_VIEW_TTS_DELAY_TIME);

    return NAVR_OK;
}
static INT32 _nav_pic_mode_view_single_select_list_wdgt_msg_cb_fct(
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

    DBG_LOG_PRINT(("[KK] %s, %d. keycode: %u, index: %u.\n",
                        __FUNCTION__, __LINE__,
                        wdk_widget_msg->ui4_keycode,
                        wdk_widget_msg->ui4_selected_num));

    nav_pic_mode_ctrl_set_index(wdk_widget_msg->ui4_selected_num);

#ifdef APP_TTS_SUPPORT
    _nav_pic_mode_view_wdgt_msg_tts_play_txt((UINT16)wdk_widget_msg->ui4_selected_num);
#endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_init(
                    NAV_PIC_MODE_T*                pt_ctrl,
                    HANDLE_T                       h_canvas,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset,
                    UINT16                         ui2_elem_num
                    )
{
    WDK_TOAST_PARAM_T    t_widget_param;
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;

    NAV_DEBUG_PIC_MODE( DBG_LOG_PRINT(("[NAV][PIC_MODE]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    /* alloc space for ui2_elem_num */
    __pic_mode_alloc_text();

    c_memset(pt_view, 0, sizeof(NAV_PIC_MODE_VIEW_T));

    /* Save the ctrl to view */
    pt_view->pt_ctrl = pt_ctrl;

    c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));

    t_widget_param.e_toast_style = WDK_SINGLE_SELECT_LIST;
	t_widget_param.w2s_msg_t.i4_str_num = ui2_elem_num;
	t_widget_param.b_is_pic_mode = TRUE;
	t_widget_param.ui1_pic_standard_idx = 0;

    a_wdk_toast_init(h_canvas, &t_widget_param,&t_g_wdk_view);

    /* Customization Environment */
    b_g_toggle_by_btn_smart_pic = NAV_PIC_MODE_TOGGLE_BY_BTN_SMART_PIC;
    b_g_exit_by_btn_smart_pic   = NAV_PIC_MODE_EXIT_BY_BTN_SMART_PIC;
    b_g_exit_by_btn_select      = NAV_PIC_MODE_EXIT_BY_BTN_SELECT;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_deinit(
                    VOID
                    )
{
    NAV_PIC_MODE_VIEW_T* pt_view = &t_g_nav_pic_mode_view;

    pt_view->pt_ctrl     = NULL;

    __pic_mode_free_text();

    a_wdk_toast_deinit(&t_g_wdk_view);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Set the _nav_pic_mode_view_set_elem_num index
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_pic_mode_view_set_elem_num(UINT16    ui2_num)
{
    NAV_PIC_MODE_VIEW_T *pt_view = &t_g_nav_pic_mode_view;

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
static INT32 _nav_pic_mode_view_set_hlt_index(UINT16    ui2_idx)
{
    NAV_PIC_MODE_VIEW_T *pt_view = &t_g_nav_pic_mode_view;

    pt_view->ui2_curr_idx = ui2_idx;

    #ifdef APP_TTS_SUPPORT
        _nav_pic_mode_view_wdgt_msg_tts_play_txt(ui2_idx);
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
static INT32 _nav_pic_mode_view_set_index_text(UINT16    ui2_idx,
                                               UTF16_T*  pw2s_text)
{
    if (ui2_idx > SINGLE_SELECT_MAX_TXT_MSG_NUM - 1)
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
static INT32 _nav_pic_mode_view_set_is_refreshing(BOOL      b_is_refreshing)
{
    NAV_PIC_MODE_VIEW_T *pt_view = &t_g_nav_pic_mode_view;

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
static INT32 _nav_pic_mode_view_set_title_text(UTF16_T*  pw2s_title)

{
    c_memset(w2s_title_msg, 0, sizeof(w2s_title_msg));
    c_uc_w2s_strcpy(w2s_title_msg, pw2s_title);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_pic_mode_view_register_single_select_list_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_pic_mode_view_register_single_select_list_hdlr(
                    NAV_PIC_MODE_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    NAV_DEBUG_PIC_MODE( DBG_LOG_PRINT(("[NAV][PIC_MODE]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init              = _nav_pic_mode_view_init;
    pt_view_hdlr->pf_deinit            = _nav_pic_mode_view_deinit;
    pt_view_hdlr->pf_is_key_handler    = _nav_pic_mode_view_is_key_handler;
    pt_view_hdlr->pf_activate          = _nav_pic_mode_view_activate;
    pt_view_hdlr->pf_hide              = _nav_pic_mode_view_hide;
	pt_view_hdlr->pf_set_elem_num      = _nav_pic_mode_view_set_elem_num;
    pt_view_hdlr->pf_set_hlt_index     = _nav_pic_mode_view_set_hlt_index;
    pt_view_hdlr->pf_set_index_text    = _nav_pic_mode_view_set_index_text;
    pt_view_hdlr->pf_set_is_refreshing = _nav_pic_mode_view_set_is_refreshing;
    pt_view_hdlr->pf_set_title_text    = _nav_pic_mode_view_set_title_text;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

#endif /* APP_537X_SUPPORT */

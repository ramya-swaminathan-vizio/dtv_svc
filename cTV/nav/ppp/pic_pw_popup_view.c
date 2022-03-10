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
#include "c_wgl.h"
#include "u_irrc_btn_def.h"

#include "pic_pw_popup.h"
#include "wdk/widget/wdk_widget.h"
#include "res/nav/nav_mlm.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif


/////////////////////////////////////////////////////////////////////////////////
#define  PP_POPUP_BUTTON_AMOUNT        (5)
#define  PIC_POPUP_PAGE_IDX            (0)
#define  PW_POPUP_PAGE_IDX             (1)

/////////////////////////////////////////////////////////////////////////////////
static WDK_OSD_TOAST_T    t_g_wdk_toast = {0};
static WDK_TOAST_PARAM_T  t_g_wdk_param = {0};

static UTF16_T*  pt_w2s[PP_POPUP_BUTTON_AMOUNT];

static ACFG_CUST_PIC_MODE_T     t_pic_mode = ACFG_CUST_PIC_MODE_STANDARD;
static UINT8		            ui1_power_mode = ICL_CUSTOM_POWER_MODE_ECO;
static UINT8                    ui1_lang_idx;
/////////////////////////////////////////////////////////////////////////////////
static INT32 _ppp_button_widget_proc_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2);

/////////////////////////////////////////////////////////////////////////////////
static VOID _ppp_view_text_alloc(UINT8 ui1_lang)
{
    WDK_TOAST_PARAM_T* pt_param = &t_g_wdk_param;

    pt_param->w2s_msg_t.i4_str_num = PP_POPUP_BUTTON_AMOUNT;
    pt_param->w2s_msg_t.e_msy_style = WDK_MSG_SEPARATELY;
    ui1_lang_idx = ui1_lang;

    for (INT32 i4_idx = 0; i4_idx < PP_POPUP_BUTTON_AMOUNT; ++i4_idx)
    {
        UTF16_T*  pt_text = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_NAV_PPP_STANDARD+i4_idx);

        if((!a_cfg_cust_get_support_energy_start_by_mode_name())&&(i4_idx == 0))
            //&&!a_cfg_cust_get_non_support_energy_start_keep_standard_by_mode_name())
        {
            pt_text = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_NAV_PPP_VIVID);
        }
        else if((!a_cfg_cust_get_support_energy_start_by_mode_name())&&(i4_idx == 2))
            //&&!a_cfg_cust_get_non_support_energy_start_keep_standard_by_mode_name())
        {
            pt_text = MLM_NAV_TEXT(ui1_lang_idx, MLM_NAV_KEY_NAV_PPP_STANDARD);
        }

        SIZE_T    text_sz = c_uc_w2s_strlen(pt_text);

        pt_w2s[i4_idx] = c_mem_alloc(sizeof(UTF16_T)*(text_sz+1));
        if (pt_w2s[i4_idx] != NULL)
        {
            c_uc_w2s_strncpy(pt_w2s[i4_idx], pt_text, text_sz);
            *(pt_w2s[i4_idx]+text_sz) = L'\0';
            pt_param->w2s_msg_t.w2s_str[i4_idx] = pt_w2s[i4_idx];
        }
    }
}

static VOID _ppp_view_text_free()
{
    for (INT32 i4_idx = 0; i4_idx < PP_POPUP_BUTTON_AMOUNT; ++i4_idx)
    {
        c_mem_free(pt_w2s[i4_idx]);
        pt_w2s[i4_idx] = NULL;
    }
}

static INT32 _ppp_view_init(
                    HANDLE_T h_canvas
                    )
{
    WDK_TOAST_PARAM_T* pt_param = &t_g_wdk_param;

    c_memset(pt_param, 0, sizeof(WDK_TOAST_PARAM_T));

    pt_param->e_toast_style = WDK_PIC_PW_POPUP;
    pt_param->pf_cb = _ppp_button_widget_proc_fct;
    pt_param->style.style_ppp.i4_frame_x_offset = 275;
    pt_param->style.style_ppp.i4_frame_y_offset = 163;

    _ppp_view_text_alloc(nav_get_mlm_lang_id());

	a_wdk_toast_init(h_canvas, pt_param, &t_g_wdk_toast);

    return NAVR_OK;
}

static INT32 _ppp_view_is_key_handler()
{
    return NAVR_OK;
}

static VOID _ppp_view_dispatch_key_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    nav_hide_component(NAV_COMP_ID_PPP);
    nav_rcu_key_handler((UINT32)pv_tag1);
}

static VOID _ppp_view_set_power_mode()
{
#ifdef APP_SUPPORT_STR_CORE_OFF
    a_icl_custom_set_power_mode(ui1_power_mode);

    if (ui1_power_mode == ICL_CUSTOM_POWER_MODE_ECO)
    {
        a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_ON);
        a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_ECO);
    }
    else
    {
        a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_OFF);
        a_cfg_custom_set_drv_eco_mode(ICL_CUSTOM_POWER_MODE_QUICK_START);
    }
#endif
}

static VOID _ppp_view_set_pw_mode_exit(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _ppp_view_set_power_mode();
    nav_hide_component(NAV_COMP_ID_PPP);
}

static VOID _ppp_view_set_pic_mode_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    a_cfg_custom_set_all_src_pic_mode(t_pic_mode);
}

static VOID _ppp_view_set_pic_mode()
{
    nav_request_context_switch(_ppp_view_set_pic_mode_nfy_fct, NULL, NULL, NULL);
}

static INT32 _ppp_button_widget_proc_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    INT32  i4_ret;
    WDK_TOAST_PARAM_T* pt_param = &t_g_wdk_param;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch ((UINT32)pv_param1)
        {
            case BTN_EXIT:
            {
                if (pt_param->style.style_ppp.ui1_crnt_page == PIC_POPUP_PAGE_IDX)
                {
                    DBG_LOG_PRINT(("[PPP][%s %d] t_pic_mode = %d\n",__FUNCTION__,__LINE__,t_pic_mode));
                    _ppp_view_set_pic_mode();
                    
                    nav_hide_component(NAV_COMP_ID_PPP);
                }
                else
                {
                    if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button) {
                        ui1_power_mode = ICL_CUSTOM_POWER_MODE_ECO;
                    } else {
                        ui1_power_mode = ICL_CUSTOM_POWER_MODE_QUICK_START;
                    }
                    nav_request_context_switch(_ppp_view_set_pw_mode_exit, (VOID*)h_widget, NULL, NULL);
                }
                break;
            }
            case BTN_RETURN:
            {
                if (pt_param->style.style_ppp.ui1_crnt_page == PW_POPUP_PAGE_IDX)
                {
                    pt_param->style.style_ppp.ui1_lang_idx = nav_get_mlm_lang_id();
                    pt_param->style.style_ppp.ui1_crnt_page = PIC_POPUP_PAGE_IDX;
                    pt_param->h_t_focus_handle = pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button;

                    i4_ret = a_wdk_toast_activate(TRUE, pt_param, &t_g_wdk_toast);
                    PPP_CHK_FAIL(i4_ret);
                }
                break;
            }
            case BTN_SELECT:
            {
                if (pt_param->style.style_ppp.ui1_crnt_page == PIC_POPUP_PAGE_IDX)
                {
                    if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button) {
                        t_pic_mode = (a_cfg_cust_get_support_energy_start_by_mode_name())?
                            ACFG_CUST_PIC_MODE_STANDARD:ACFG_CUST_PIC_MODE_RETAIL;
                    } else if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_middle_button) {
                        t_pic_mode = ACFG_CUST_PIC_MODE_BRIGHT_ROOM;
                    } else {
                        t_pic_mode = (a_cfg_cust_get_support_energy_start_by_mode_name())?
                            ACFG_CUST_PIC_MODE_RETAIL : ACFG_CUST_PIC_MODE_STANDARD;
                    }
                    _ppp_view_set_pic_mode();
                    nav_hide_component(NAV_COMP_ID_PPP);

#if 0  //DTV01341135 [Vizio][MUSC-4908]Remove display of the Picture Mode and Power Mode influencers
                    pt_param->style.style_ppp.ui1_lang_idx = nav_get_mlm_lang_id();
                    pt_param->style.style_ppp.ui1_crnt_page = PW_POPUP_PAGE_IDX;
                    pt_param->h_t_focus_handle = pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button;

                    i4_ret = a_wdk_toast_activate(TRUE, pt_param, &t_g_wdk_toast);
                    PPP_CHK_FAIL(i4_ret);
#endif

                }
                else
                {
                    if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button) {
                        ui1_power_mode = ICL_CUSTOM_POWER_MODE_ECO;
                    } else {
                        ui1_power_mode = ICL_CUSTOM_POWER_MODE_QUICK_START;
                    }
                    nav_request_context_switch(_ppp_view_set_pw_mode_exit, (VOID*)h_widget, NULL, NULL);
                }
                break;
            }
            case BTN_CURSOR_LEFT:
            {
                if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_right_button)
                {
                    TTS_PLAY( MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_CALIBRATED));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_middle_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                else if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_middle_button)
                {
                    TTS_PLAY( MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_VIVID));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                else if(h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button)
                {
                    TTS_PLAY( MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_STANDARD));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_right_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                else if(h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_right_button)
                {
                    TTS_PLAY(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_ECO));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                break;
            }
            case BTN_CURSOR_RIGHT:
            {
                if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button)
                {
                    TTS_PLAY(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_CALIBRATED));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_middle_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                else if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_middle_button)
                {
                    TTS_PLAY(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_STANDARD));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_right_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                else if (h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_right_button)
                {
                    TTS_PLAY( MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_VIVID));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                else if(h_widget == pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button)
                {
                    TTS_PLAY(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_PPP_QUICK_START));
                    i4_ret = c_wgl_set_focus(pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_right_button, WGL_SYNC_AUTO_REPAINT);
                    PPP_CHK_FAIL(i4_ret);
                }
                break;
            }
            default:
            {
                nav_request_context_switch(_ppp_view_dispatch_key_nfy_fct, pv_param1, NULL, NULL);
                break;
            }
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


static INT32 _ppp_view_activate(UINT32 ui4_key_code)
{
    INT32  i4_ret;
    WDK_TOAST_PARAM_T* pt_param = &t_g_wdk_param;
    UINT8   ui1_lang = nav_get_mlm_lang_id();
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 &i2_val);
    DBG_LOG_PRINT(("%s_%d i2_val:%d \n",__FUNCTION__,__LINE__,i2_val));
    pt_param->style.style_ppp.ui1_lang_idx =  ui1_lang;
    if((i2_val == ACFG_CUST_PIC_MODE_STANDARD)||
       (i2_val == ACFG_CUST_PIC_MODE_RETAIL))
    {
        pt_param->style.style_ppp.ui1_crnt_page = PIC_POPUP_PAGE_IDX;
        pt_param->h_t_focus_handle = pt_param->style.style_ppp.pt_wdk_ppp_button->h_pic_left_button;
        t_pic_mode = a_cfg_cust_get_support_energy_start_by_mode_name() ? ACFG_CUST_PIC_MODE_STANDARD : ACFG_CUST_PIC_MODE_VIVID;
    }
    else
    {
        pt_param->style.style_ppp.ui1_crnt_page = PW_POPUP_PAGE_IDX;
        pt_param->h_t_focus_handle = pt_param->style.style_ppp.pt_wdk_ppp_button->h_pw_left_button;
    }

    if (ui1_lang != ui1_lang_idx)
    {
        _ppp_view_text_free();
        _ppp_view_text_alloc(ui1_lang);
    }

    i4_ret = a_wdk_toast_activate(TRUE, pt_param, &t_g_wdk_toast);

    return i4_ret;
}

static INT32 _ppp_view_hide()
{
    PPP_CHK_FAIL(a_wdk_toast_hide(TRUE, NULL, &t_g_wdk_toast));
    return NAVR_OK;
}

static INT32 _ppp_view_deinit()
{
    _ppp_view_text_free();

    a_wdk_toast_deinit(&t_g_wdk_toast);

    return NAVR_OK;
}

INT32 a_nav_ppp_view_register_hdlr(NAV_PPP_VIEW_HDLR_T* pt_hdr)
{
    if (pt_hdr == NULL)
    {
        return NAVR_FAIL;
    }

    pt_hdr->pf_init = _ppp_view_init;
    pt_hdr->pf_is_key_handler = _ppp_view_is_key_handler;
    pt_hdr->pf_activate = _ppp_view_activate;
    pt_hdr->pf_hide = _ppp_view_hide;
    pt_hdr->pf_deinit = _ppp_view_deinit;

    return NAVR_OK;
}


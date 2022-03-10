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
 * $RCSfile: page_template.c,v $
 * $Revision: #3 $
 * $Date: 2015/08/05 $
 * $Author: hs_nali $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_CEC_MENU

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "u_cecm.h"
#include "c_cecm.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_page.h"

#include "menu_page_animation.h"
#include "menu2/menu_util2.h"

#include "app_util/a_cfg.h"
#include "res/nav/cec2/nav_cec_view_mlm.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/acfg_custom.h"

#include "menu2/menu_device/menu_page_device_setting.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"

#include "app_util/a_cec.h"
#include "nav/cec2/nav_cec.h"
#include "nav/input_src/input_src_view.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "c_tts.h"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MENU_DEV_LST_MAX_ELEM_NUM            (16)

#define ITEM_V_WIDE_TEXT 295
#define ITEM_V_WIDE_IMG  30


#define LIST_ITEM_CEC_IDX                 (0)
#ifdef APP_ARC_ONLY
#define LIST_ITEM_CEC_NUM                 (2)
/* CEC && Device Discovery */
#define MENU_CEC_LIST_ITEM_NUM            (2)
#else
#define LIST_ITEM_CEC_NUM                 (2)
/* CEC && SAC && Device Discovery */
#define MENU_CEC_LIST_ITEM_NUM            (3)
#endif
#define LIST_ITEM_SAC_IDX                 (1)
#define LIST_ITEM_SAC_NUM                 (2)
#define MAX_REC                           (16)
#define CEC_LST_VISIBLE_ELEM             (12)
#define CEC_LST_X                        (0 * GRID_W)
#define CEC_LST_Y                        (0 * GRID_H)
#define CEC_LST_W                        (CONTENT_W)
#define CEC_LST_H                        (CEC_LST_VISIBLE_ELEM * GRID_H)
#define DEV_DISCOVERY_BTN_X				(MENU_ITEM_V_LEFT)

#ifdef APP_ARC_ONLY
#define DEV_DISCOVERY_BTN_Y				(MENU_ITEM_V_HEIGHT*1)
#define MENU_CEC_DEV_LIST_Y             (MENU_ITEM_V_HEIGHT*2)
#else
#define DEV_DISCOVERY_BTN_Y				(MENU_ITEM_V_HEIGHT*2)
#define MENU_CEC_DEV_LIST_Y             (MENU_ITEM_V_HEIGHT*3)
#endif

#define DEV_DISCOVERY_BTN_W				(MENU_ITEM_V_WIDE)
#define DEV_DISCOVERY_BTN_H				(MENU_ITEM_V_HEIGHT)

#define MENU_CEC_MAX_DEVICE_NUM               (8)

#define MENU_CEC_DEV_LIST_X           (MENU_ITEM_V_INSET_L)
#define MENU_CEC_DEV_LIST_W           (MENU_ITEM_V_WIDE)
#define MENU_CEC_DEV_LIST_H           (MENU_ITEM_V_HEIGHT * 10)
#define MENU_CEC_DEV_LIST_ELEM_HEIGHT      (43)

#define CEC_REPEAT_DISCOVERY_INTER          (15*1000)

#define DEV_DISCOVERY_BTN_INSET_LEFT		65
#define DEV_DISCOVERY_BTN_INSET_RIGHT		10

typedef enum _CEC_SUBPAGE_T
{
    SUBPAGE_MAIN = 0,
    SUBPAGE_CEC,
    SUBPAGE_EARC,
    SUBPAGE_LAST_ENTRY,
}CEC_SUBPAGE_T;


typedef struct _MENU_CEC
{
    HANDLE_T        h_cnt_frm;
    BOOL            b_this_page_show;
    HANDLE_T        h_cec_item;
    HANDLE_T        h_sac_item;
    HANDLE_T        h_dev_discovery_item;
    CEC_SUBPAGE_T   e_subpage;
    CEC_SUBPAGE_T   e_pre_subpage;
    HANDLE_T        h_last_focus_item;
    HANDLE_T        h_cec_subpage;
    HANDLE_T        h_sac_subpage;
    HANDLE_T        h_cec_dev_list;
    HANDLE_T        h_show_info;
    HANDLE_T        h_menu_cecm;
    BOOL            b_dev_discovery_is_sel;

}MENU_CEC;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_cec;
static  MENU_CEC    t_g_cec_page_data;
static  UINT8       ui1_dev_disc_detect;

static HANDLE_T cec_name_timer = NULL_HANDLE;
static HANDLE_T vcec_discovery_timer = NULL_HANDLE;
static BOOL     b_vdt_start = FALSE; // status of vcec_discovery_timer
static UINT32   ui4_vcec_num = 0;
static UINT8    ui1_vcec_name[30] = {0};

BOOL rest_notify_flag = FALSE;
static char cec_name_port[5][APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _menu_cec_show_no_dev(UINT16 ui2_key, WGL_SW_CMD_T eCmd);
static INT32 _dev_discovery_item_show(VOID);
static INT32 _subpage_show(BOOL b_repaint);
static BOOL is_cec_dev_discover_enabled(VOID);
static INT32 _menu_vcec_discovery_timer_start(VOID);

extern INT32 nav_cec_set_earc_status(BOOL b_arcStatus);
extern INT32 nav_cec_arc_set_5v_status(UINT16 port_id, BOOL status);
extern void rest_event_notify(const char* uri, int intValue, const char* stringValue);

extern UINT32 nav_cec_custom_get_spd_info(UINT8 port, UINT8* description, UINT8 u8BufSize);
extern UINT32 hdmi_hot_plug_status (UINT16  ui2_internal_id);


#if 1
static INT32 _earc_item_show(VOID);
static INT32 _subpage_earc_show(VOID);
static INT32 _append_earc(VOID);
static UINT16 _get_cec_earc_idx(VOID);
static BOOL _is_earc_item_enable(VOID);
#endif

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
#ifdef APP_ARC_ONLY
/*----------------------------------------------------------------------------
 * Name: _set_cec_function_idx_ex
 *
 * Description:_set_cec_function_idx_ex
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _set_cec_function_idx_ex(UINT16 ui2_idx)
{

    UINT8 ui1_cec=0;
    UINT8 ui1_sac=0;
    UINT8 ui1_cec_auto_on=0;
    UINT8 ui1_arc_only_status=0;
    UINT16 ui2_speakers_out=0;
    UINT8 ui1_val = ICL_RECID_CUSTOM_INPUT_NAME_CHANGE;
    SIZE_T z_size = ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE;


    a_cfg_get_cec_func (&ui1_cec);
    a_cfg_get_cec_sac_func(&ui1_sac);
    a_cfg_get_cec_auto_on(&ui1_cec_auto_on);
    a_cfg_custom_get_speakers_out(&ui2_speakers_out);

    switch (ui2_idx)
    {
        case 0: /* OFF */
        {
            if(APP_CFG_CEC_OFF != ui1_cec)
            {
                a_cfg_set_cec_func (APP_CFG_CEC_OFF);
            }
            if((ui2_speakers_out != APP_CFG_AUD_AD_SPEAKER_ON)&&
                (0 != ui1_sac))
            {
                a_cfg_set_cec_sac_func(0);
            }
            if(APP_CFG_CEC_OFF != ui1_cec_auto_on)
            {
                a_cfg_set_cec_auto_on(APP_CFG_CEC_OFF);
            }
            c_thread_delay(300);
            break;
        }
        default: /* ON */
        {
            if(APP_CFG_CEC_ON != ui1_cec)
            {
                a_cfg_set_cec_func (APP_CFG_CEC_ON);
            }
            /* Set sac to on if TV speaker is Auto. */
            if((ui2_speakers_out != APP_CFG_AUD_AD_SPEAKER_ON) &&
                (1 != ui1_sac))
            {
                a_cfg_set_cec_sac_func(1);
            }
            if(APP_CFG_CEC_ON != ui1_cec_auto_on)
            {
                a_cfg_set_cec_auto_on(APP_CFG_CEC_ON);
            }
            c_thread_delay(300);
            break;
        }
    }

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_FLAG_CHANGE),
              (VOID*) &ui1_val,
              z_size);
    if (ui2_idx > 0)
    {
        _menu_vcec_discovery_timer_start();
    }

    menu_pm_refresh();
    menu_pm_repaint();
}

/*----------------------------------------------------------------------------
 * Name: _get_cec_function_idx_ex
 *
 * Description:_get_cec_function_idx_ex
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static UINT16 _get_cec_function_idx_ex(VOID)
{
    UINT8 ui1_on=0;

    a_cfg_get_cec_func (&ui1_on);
    return (UINT16)ui1_on;
}

/*----------------------------------------------------------------------------
 * Name: _to_prev_cec_idx_ex
 *
 * Description:_to_prev_cec_idx_ex
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_prev_cec_idx_ex(void)
{
	INT32       				i4_ret = MENUR_OK;
    UINT16 						ui2_idx=0;

    ui2_idx = _get_cec_function_idx_ex();

    if (ui2_idx > 0)
    {
        ui2_idx--;
    }
    else
    {
        ui2_idx = LIST_ITEM_CEC_NUM-1;
    }

	_set_cec_function_idx_ex(ui2_idx);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _to_next_cec_idx_ex
 *
 * Description:_to_next_cec_idx_ex
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_next_cec_idx_ex(void)
{
	INT32       				i4_ret = MENUR_OK;
    UINT16 						ui2_idx=0;

    ui2_idx = _get_cec_function_idx_ex();

    if (ui2_idx < LIST_ITEM_CEC_NUM-1)
    {
        ui2_idx++;
    }
    else
    {
        ui2_idx = 0;
    }

	_set_cec_function_idx_ex(ui2_idx);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _append_cec_ex
 *
 * Description: _append_cec_ex-->append the cec subpage item elem
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _append_cec_ex(VOID)
{
    INT32               i4_ret = MENUR_OK;
    MENU_CEC*  pt_this = &t_g_cec_page_data;
    WGL_LB_ITEM_T       at_items[1];
    UINT16              ui2_idx = 0;

    i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
                         WGL_CMD_LB_DEL_ALL,
                         NULL,
                         NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_idx=0;ui2_idx<LIST_ITEM_CEC_NUM;ui2_idx++)
    {
        /*append the cec elem*/
        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = MENU_TEXT(MLM_MENU_KEY_DISABLE+ui2_idx);

        i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _cec_item_show_ex
 *
 * Description: cec item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cec_item_show_ex(VOID)
{
    INT16 				i2_idx = 0;
    INT32 				i4_ret = MENUR_OK;;
	MENU_CEC*  pt_this = &t_g_cec_page_data;

	i2_idx = _get_cec_function_idx_ex();

    menu_list_chg_lang(pt_this->h_cec_item,
                        MLM_MENU_KEY_CEC_SETTINGS, 0, 0);

    menu_list_set_text(pt_this->h_cec_item,
                       0,
                       MENU_TEXT(MLM_MENU_KEY_DISABLE + i2_idx));

    menu_list_set_idx(pt_this->h_cec_item, 0);
    menu_list_adjust_rect(pt_this->h_cec_item);

	i4_ret = c_wgl_set_visibility(pt_this->h_cec_item,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _cec_list_item_proc_fct
 *
 * Description:_cec_list_item_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _cec_list_item_proc_fct_ex(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_CEC* 				pt_this = &t_g_cec_page_data;
	INT32							i4_ret = MENUR_OK;

	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_CEC_FUNCTION));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if (BTN_CURSOR_LEFT == ui4_key_code)
                {
                    _to_prev_cec_idx_ex();
                }
                else
                {
                    _to_next_cec_idx_ex();
                }
                _cec_item_show_ex();
                /*update device discovery item display when change the cec setting*/
                _dev_discovery_item_show();
                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);

			    return MENUR_OK;
            }
            case BTN_SELECT:
            {
                pt_this->h_last_focus_item = pt_this->h_cec_item;
				pt_this->e_pre_subpage = SUBPAGE_MAIN;
				pt_this->e_subpage = SUBPAGE_CEC;
                i4_ret = _subpage_show(TRUE);
				MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
				MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                return WGLR_OK;
			}
            case BTN_CURSOR_DOWN:
            {
                if(is_cec_dev_discover_enabled())
                {
                	c_wgl_set_focus(pt_this->h_dev_discovery_item,
    	                                 WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
					menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
					menu_pm_repaint();
                }
                return WGLR_OK;
            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                menu_nav_back();
                return WGLR_OK;
            }
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        UINT16 		ui2_idx=0;
        UTF16_T     w2s_str[64+1] = {0};

        ui2_idx = _get_cec_function_idx_ex();
        if(ui2_idx == 0)//enable
        {
            c_uc_ps_to_w2s("C E C, Disable", w2s_str, c_strlen("C E C, Disable"));
        }
        else //enbale
        {
            c_uc_ps_to_w2s("C E C, Enable", w2s_str, c_strlen("C E C, Enable"));
        }

        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
    }
#endif


    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _cec_list_item_create_ex
 *
 * Description:_cec_list_item_create_ex
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _cec_list_item_create_ex(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_CEC*  pt_this = &t_g_cec_page_data;

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_CEC_IDX,
                              LIST_ITEM_CEC_NUM,
                              _cec_list_item_proc_fct_ex,
                              &pt_this->h_cec_item);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _subpage_cec_show_ex(VOID)
 *
 * Description:CEC subpage show: Disable/ARC only/Enable
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _subpage_cec_show_ex(VOID)
{
	INT32       		i4_ret = MENUR_OK;
	MENU_CEC*  pt_this = &t_g_cec_page_data;
	UINT16				ui2_idx = 0;
    //UINT16              ui2_list_num = 0;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;


    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * 3 + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_main_set_title(MLM_MENU_KEY_CEC_SETTINGS);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_CEC_FUNCTION));

    ui1_dev_disc_detect = 0;

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cec_subpage,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _append_cec_ex();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_cec_subpage,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

	ui2_idx = _get_cec_function_idx_ex();
    i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
                 WGL_CMD_LB_HLT_ELEM,
                 WGL_PACK(ui2_idx),
                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    /* get list num */
//    i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
//                          WGL_CMD_LB_GET_ELEM_NUM,
//                          WGL_PACK (&ui2_list_num),
//                          NULL);
//    MENU_LOG_ON_FAIL(i4_ret);


    return i4_ret;
}

#else
/*----------------------------------------------------------------------------
 * Name: _set_cec_function_idx
 *
 * Description:_set_cec_function_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _set_cec_function_idx(UINT16 ui2_idx)
{

    UINT8 ui1_cec=0;
    UINT8 ui1_sac=0;
    UINT8 ui1_cec_auto_on=0;
    UINT8 ui1_arc_only_status=0;
    UINT16 ui2_speakers_out=0;
    UINT8 ui1_val = ICL_RECID_CUSTOM_INPUT_NAME_CHANGE;
    SIZE_T z_size = ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE;

    a_cfg_get_cec_func (&ui1_cec);
    a_cfg_get_cec_sac_func(&ui1_sac);
    a_cfg_get_cec_auto_on(&ui1_cec_auto_on);
    a_cfg_custom_get_speakers_out(&ui2_speakers_out);

    if( ui2_idx != 0) // on
    {
        if(APP_CFG_CEC_ON != ui1_cec)
        {
            a_cfg_set_cec_func (APP_CFG_CEC_ON);
        }
        /* Set sac to on if TV speaker is Auto. */
        if((ui2_speakers_out != APP_CFG_AUD_AD_SPEAKER_ON) &&
            (1 != ui1_sac))
        {
            a_cfg_set_cec_sac_func(1);
        }
        if(APP_CFG_CEC_ON != ui1_cec_auto_on)
        {
            a_cfg_set_cec_auto_on(APP_CFG_CEC_ON);
        }
        c_thread_delay(300);
    }
    else        //off
    {
        if(APP_CFG_CEC_OFF != ui1_cec)
        {
            a_cfg_set_cec_func (APP_CFG_CEC_OFF);
        }
        if((ui2_speakers_out != APP_CFG_AUD_AD_SPEAKER_ON)&&
            (0 != ui1_sac))
        {
            a_cfg_set_cec_sac_func(0);
        }
        if(APP_CFG_CEC_OFF != ui1_cec_auto_on)
        {
            a_cfg_set_cec_auto_on(APP_CFG_CEC_OFF);
        }
        c_thread_delay(300);
    }

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE, ICL_RECID_CUSTOM_FLAG_CHANGE),
              (VOID*) &ui1_val,
              z_size);

    menu_pm_refresh();
    menu_pm_repaint();
}

/*----------------------------------------------------------------------------
 * Name: _get_cec_function_idx
 *
 * Description:_get_cec_function_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static UINT16 _get_cec_function_idx(VOID)
{
    UINT8 ui1_on=0;

    a_cfg_get_cec_func (&ui1_on);
    return (UINT16)ui1_on;
}
/*----------------------------------------------------------------------------
 * Name: _to_prev_cec_idx
 *
 * Description:_to_prev_cec_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_prev_cec_idx(void)
{
	INT32       				i4_ret = MENUR_OK;
    UINT16 						ui2_idx=0;

    ui2_idx = _get_cec_function_idx();

    if (ui2_idx > 0)
    {
        ui2_idx--;
    }
    else
    {
        ui2_idx = LIST_ITEM_CEC_NUM-1;
    }

	_set_cec_function_idx(ui2_idx);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _to_next_cec_idx
 *
 * Description:_to_next_cec_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_next_cec_idx(void)
{
	INT32       				i4_ret = MENUR_OK;
    UINT16 						ui2_idx=0;

    ui2_idx = _get_cec_function_idx();

    if (ui2_idx < LIST_ITEM_CEC_NUM-1)
    {
        ui2_idx++;
    }
    else
    {
        ui2_idx = 0;
    }

	_set_cec_function_idx(ui2_idx);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _append_cec
 *
 * Description: _append_cec-->append the cec subpage item elem
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _append_cec(VOID)
{
    INT32               i4_ret = MENUR_OK;
    MENU_CEC*  pt_this = &t_g_cec_page_data;
    WGL_LB_ITEM_T       at_items[1];
    UINT16              ui2_idx = 0;

    i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
                         WGL_CMD_LB_DEL_ALL,
                         NULL,
                         NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_idx=0;ui2_idx<LIST_ITEM_CEC_NUM;ui2_idx++)
    {
        /*append the cec elem*/
        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = MENU_TEXT(MLM_MENU_KEY_DISABLE+ui2_idx);

        i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _cec_item_show
 *
 * Description: cec item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cec_item_show(VOID)
{
    INT16 				i2_idx = 0;
    INT32 				i4_ret = MENUR_OK;;
	MENU_CEC*  pt_this = &t_g_cec_page_data;

	i2_idx = _get_cec_function_idx();

    menu_list_chg_lang(pt_this->h_cec_item,
                        MLM_MENU_KEY_CEC_SETTINGS, 0, 0);

    menu_list_set_text(pt_this->h_cec_item,
                       0,
                       MENU_TEXT(MLM_MENU_KEY_DISABLE + i2_idx));

    menu_list_set_idx(pt_this->h_cec_item, 0);
    menu_list_adjust_rect(pt_this->h_cec_item);

	i4_ret = c_wgl_set_visibility(pt_this->h_cec_item,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _cec_list_item_proc_fct
 *
 * Description:_cec_list_item_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _cec_list_item_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_CEC* 				pt_this = &t_g_cec_page_data;
	INT32							i4_ret = MENUR_OK;

	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_CEC_FUNCTION));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if (BTN_CURSOR_LEFT == ui4_key_code)
                {
                    _to_prev_cec_idx();
                }
                else
                {
                    _to_next_cec_idx();
                }
                _cec_item_show();
                /*update device discovery item and sac item display when change the cec setting*/
                _dev_discovery_item_show();
                _earc_item_show();
                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);

			    return MENUR_OK;
            }
            case BTN_SELECT:
            {
                pt_this->h_last_focus_item = pt_this->h_cec_item;
				pt_this->e_pre_subpage = SUBPAGE_MAIN;
				pt_this->e_subpage = SUBPAGE_CEC;
                i4_ret = _subpage_show(TRUE);
				MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
				MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                return WGLR_OK;
			}
            case BTN_CURSOR_DOWN:
            {
                if(_is_earc_item_enable())
                {
                	c_wgl_set_focus(pt_this->h_sac_item,
    	                                 WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
					menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
					menu_pm_repaint();
                }
                return WGLR_OK;
            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                menu_nav_back();
                return WGLR_OK;
            }
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        UINT16      ui2_idx=0;
        UTF16_T     w2s_str[64+1] = {0};

        ui2_idx = _get_cec_function_idx();
        if(ui2_idx == 0)//enable
        {
            c_uc_ps_to_w2s("C E C, Disable", w2s_str, c_strlen("C E C, Disable"));
        }
        else //enbale
        {
            c_uc_ps_to_w2s("C E C, Enable", w2s_str, c_strlen("C E C, Enable"));
        }

        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
    }
#endif

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _cec_list_item_create
 *
 * Description:_cec_list_item_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _cec_list_item_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_CEC*  pt_this = &t_g_cec_page_data;

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_CEC_IDX,
                              LIST_ITEM_CEC_NUM,
                              _cec_list_item_proc_fct,
                              &pt_this->h_cec_item);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _subpage_cec_show(VOID)
 *
 * Description:CEC subpage show: OFF/ON
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _subpage_cec_show(VOID)
{
	INT32       		i4_ret = MENUR_OK;
	MENU_CEC*  pt_this = &t_g_cec_page_data;
	UINT16				ui2_idx = 0;
    //UINT16              ui2_list_num = 0;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * 3 + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_main_set_title(MLM_MENU_KEY_CEC_SETTINGS);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_CEC_FUNCTION));

    ui1_dev_disc_detect = 0;

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cec_subpage,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _append_cec();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_cec_subpage,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

	ui2_idx = _get_cec_function_idx();
    i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
                 WGL_CMD_LB_HLT_ELEM,
                 WGL_PACK(ui2_idx),
                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    /* get list num */
//    i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
//                          WGL_CMD_LB_GET_ELEM_NUM,
//                          WGL_PACK (&ui2_list_num),
//                          NULL);
//    MENU_LOG_ON_FAIL(i4_ret);


    return i4_ret;
}

#endif
/*----------------------------------------------------------------------------
 * Name: is_cec_dev_discover_enabled
 *
 * Description: is_cec_dev_discover_enabled
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static BOOL is_cec_dev_discover_enabled(VOID)
{
    UINT8   ui1_enable = FALSE;

    a_cfg_get_cec_func (&ui1_enable);

    if(ui1_enable == (UINT8)FALSE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _dev_discovery_item_show
 *
 * Description: device discovery item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _dev_discovery_item_show(VOID)
{
    INT32 				i4_ret = MENUR_OK;
    MENU_CEC*           pt_this = &t_g_cec_page_data;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

	i4_ret = c_wgl_do_cmd(pt_this->h_dev_discovery_item,
						  WGL_CMD_BTN_SET_TEXT,
						  WGL_PACK(MENU_TEXT(MLM_MENU_KEY_CEC_DEV_DISCOVER)),
						  WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_CEC_DEV_DISCOVER))));
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(pt_this->h_dev_discovery_item,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(is_cec_dev_discover_enabled())
    {
        i4_ret = c_wgl_enable(pt_this->h_dev_discovery_item,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_enable(pt_this->h_dev_discovery_item,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_cec_dev_list, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * (MENU_CEC_LIST_ITEM_NUM+ui1_dev_disc_detect)+ CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _subpage_main_show
 *
 * Description:cec list item/device discovery btn/cec dev list
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _subpage_main_show(VOID)
{
    INT32       			i4_ret = MENUR_OK;
	MENU_CEC* 		        pt_this = &t_g_cec_page_data;
    GL_RECT_T               t_rect = {0};
    HANDLE_T                h_last_shadow_item = NULL_HANDLE;

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cec_subpage,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_main_set_title(MLM_MENU_KEY_CEC_SETTINGS);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ARC_ONLY
    i4_ret = _cec_item_show_ex();
    MENU_LOG_ON_FAIL(i4_ret);
#else
    i4_ret = c_wgl_set_visibility(pt_this->h_sac_subpage,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _cec_item_show();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _earc_item_show();
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = _dev_discovery_item_show();
    MENU_LOG_ON_FAIL(i4_ret);

    if(pt_this->h_last_focus_item != NULL_HANDLE)
    {
        i4_ret = c_wgl_set_focus(pt_this->h_last_focus_item,
                                 WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_focus(pt_this->h_cec_item,
                                 WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * MENU_CEC_LIST_ITEM_NUM + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _subpage_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _subpage_show(BOOL b_repaint)
{
    INT32       		i4_ret = MENUR_OK;
    MENU_CEC*           pt_this = &t_g_cec_page_data;

    menu_set_help_tip_flag(TRUE);

    switch (pt_this->e_subpage)
    {
        case SUBPAGE_MAIN:
        {
            i4_ret = _subpage_main_show();
			MENU_LOG_ON_FAIL(i4_ret);
        }
            break;
#ifdef APP_ARC_ONLY
        case SUBPAGE_CEC:
        {
            i4_ret = _subpage_cec_show_ex();
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;
#else
        case SUBPAGE_CEC:
        {
			i4_ret = _subpage_cec_show();
			MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case SUBPAGE_EARC:
        {
            i4_ret = _subpage_earc_show();
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;
#endif

        default:
            break;
    }

    if (b_repaint)
    {
        i4_ret = menu_pm_repaint();
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _cec_list_subpage_proc_fct
 *
 * Description:_cec_list_subpage_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _cec_list_subpage_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_CEC* pt_this = &t_g_cec_page_data;

	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_CEC_FUNCTION));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  	ui4_key_code = (UINT32)pv_param1;
        INT32       i4_ret = MENUR_OK;
        UINT16      ui2_idx = 0;
        UINT16      ui2_elem_num = 0;

        switch (ui4_key_code)
        {
        case BTN_CURSOR_UP :
        case BTN_CURSOR_DOWN :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&ui2_elem_num),
                         NULL);

            if(ui4_key_code == BTN_CURSOR_UP)
            {
                if(ui2_idx == 0)
                {
					MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_PREV_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }
            else
            {
                if(ui2_idx == (UINT16)(ui2_elem_num - 1))
                {
					menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
					menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_NEXT_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }

            return MENUR_OK;
        }
        case BTN_SELECT :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);
#ifdef APP_ARC_ONLY
            _set_cec_function_idx_ex(ui2_idx);
#else
            _set_cec_function_idx(ui2_idx);
#endif

			pt_this->e_pre_subpage = SUBPAGE_CEC;
			pt_this->e_subpage = SUBPAGE_MAIN;
			i4_ret = _subpage_show(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case BTN_EXIT:
        case BTN_RETURN:

			pt_this->e_pre_subpage = SUBPAGE_CEC;
			pt_this->e_subpage = SUBPAGE_MAIN;
			i4_ret = _subpage_show(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;

        default :
            break ;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        UTF16_T     w2s_text[64+1] = {0};
        UINT16      ui2_tts_idx = 0;
        INT32		i4_ret = MENUR_OK;

        i4_ret = c_wgl_do_cmd(pt_this->h_cec_subpage,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_tts_idx),
                         NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_DISABLE + ui2_tts_idx)) ;
        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    }
#endif


    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _cec_list_subpage_create
 *
 * Description:_cec_list_subpage_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _cec_list_subpage_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T   		t_rect;
	MENU_CEC* pt_this = &t_g_cec_page_data;

    SET_RECT_BY_SIZE (&t_rect,
                      CEC_LST_X,
                      CEC_LST_Y,
                      CEC_LST_W,
                      CEC_LST_H);

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32+1;
    at_cols[0].ui2_width        = CEC_LST_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_MULTI_SEL |
                                  WGL_STL_GL_NO_IMG_UI;

    t_lb_init.ui2_max_elem_num  = MAX_REC;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    i4_ret = menu_list2_create (pt_this->h_cnt_frm,
                                &t_rect,
                                _cec_list_subpage_proc_fct,
                                &t_lb_init,
                                NULL,
                                &pt_this->h_cec_subpage);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create list for cec failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _dev_discovery_btn_create
 *
 * Description: device discovery button
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _dev_discovery_btn_create(HANDLE_T h_parent,
									wgl_widget_proc_fct  pf_wdgt_proc,
									UTF16_T*  pw2s_str,
									HANDLE_T* ph_widget)
{
	INT32				i4_ret = MENUR_OK;
	GL_RECT_T			t_rect;
	WGL_INSET_T 		t_inset;
	WGL_COLOR_INFO_T	t_color_info = {0};
	WGL_IMG_INFO_T		t_img_info = {0};
	WGL_FONT_INFO_T 	t_font_info = {0};
	GL_COLOR_T			t_color_txt = t_g_menu_color_white;
	GL_COLOR_T			t_color_txt_disable = { 255, {128}, {128}, {128}};

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
	SET_RECT_BY_SIZE(&t_rect,
					 DEV_DISCOVERY_BTN_X,
					 DEV_DISCOVERY_BTN_Y,
					 DEV_DISCOVERY_BTN_W,
					 DEV_DISCOVERY_BTN_H
					 );

	i4_ret = c_wgl_create_widget(h_parent,
								HT_WGL_WIDGET_BUTTON,
								WGL_CONTENT_BUTTON_DEF,
								WGL_BORDER_NULL,
								&t_rect,
								pf_wdgt_proc,
								255,
								NULL,
								NULL,
								ph_widget);
	MENU_LOG_ON_FAIL(i4_ret);

	t_inset.i4_left   = DEV_DISCOVERY_BTN_INSET_LEFT;
	t_inset.i4_right  = DEV_DISCOVERY_BTN_INSET_RIGHT;
	t_inset.i4_top	  = 0;
	t_inset.i4_bottom = 0;
	i4_ret = c_wgl_do_cmd(*ph_widget,
						   WGL_CMD_BTN_SET_CNT_INSET,
						   WGL_PACK(&t_inset),
						   NULL);
	MENU_LOG_ON_FAIL(i4_ret);

	t_img_info.e_type = WGL_IMG_SET_EXTEND;
	t_img_info.u_img_data.t_extend.t_enable 			= h_g_menu_img_item_bk;
	t_img_info.u_img_data.t_extend.t_disable			= h_g_menu_img_item_bk;
	t_img_info.u_img_data.t_extend.t_highlight			= h_g_menu_img_item_hlt_bk;
	t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_bk;
	t_img_info.u_img_data.t_extend.t_push				= h_g_menu_img_item_hlt_bk;
	t_img_info.u_img_data.t_extend.t_push_unhighlight	= h_g_menu_img_item_bk;
	i4_ret = c_wgl_do_cmd(*ph_widget,
						   WGL_CMD_GL_SET_IMAGE,
						   WGL_PACK(WGL_IMG_BK),
						   WGL_PACK(&t_img_info));
	MENU_LOG_ON_FAIL(i4_ret);

	t_color_info.e_type = WGL_COLOR_SET_EXTEND;
	t_color_info.u_color_data.t_extend.t_enable = t_color_txt;
	t_color_info.u_color_data.t_extend.t_disable = t_color_txt_disable;
	t_color_info.u_color_data.t_extend.t_highlight = t_color_txt;
	t_color_info.u_color_data.t_extend.t_highlight_inactive = t_color_txt;
	t_color_info.u_color_data.t_extend.t_push = t_color_txt;
	t_color_info.u_color_data.t_extend.t_push_unhighlight = t_color_txt;
	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_GL_SET_COLOR,
						  WGL_PACK(WGL_CLR_TEXT),
						  WGL_PACK(& t_color_info));
	MENU_LOG_ON_FAIL(i4_ret);

	c_strncpy(t_font_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_font_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_font_info.ui1_custom_size = 24;

	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_GL_SET_FONT,
						  WGL_PACK(&t_font_info),
						  NULL);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_BTN_SET_ALIGN,
						  WGL_PACK(WGL_AS_LEFT_CENTER),
						  NULL);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_BTN_SET_TEXT,
						  WGL_PACK(pw2s_str),
						  WGL_PACK(c_uc_w2s_strlen(pw2s_str)));
	MENU_LOG_ON_FAIL(i4_ret);

	return i4_ret;
}
#if 1
/*----------------------------------------------------------------------------
 * Name: _subpage_sac_show
 *
 * Description:EARC subpage show: OFF/ON
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _subpage_earc_show(VOID)
{
	INT32       		i4_ret = MENUR_OK;
	MENU_CEC*  pt_this = &t_g_cec_page_data;
	UINT16				ui2_idx = 0;
    UINT16              ui2_list_num = 0;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

	i4_ret = menu_main_set_title(MLM_MENU_KEY_EARC_MODE);
    MENU_LOG_ON_FAIL(i4_ret);

    //TODO
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EARC_MODE_HELP));

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_sac_subpage,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _append_earc();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_sac_subpage,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

	ui2_idx = _get_cec_earc_idx();
    i4_ret = c_wgl_do_cmd(pt_this->h_sac_subpage,
                 WGL_CMD_LB_HLT_ELEM,
                 WGL_PACK(ui2_idx),
                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    /* get list num */
    i4_ret = c_wgl_do_cmd(pt_this->h_sac_subpage,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK (&ui2_list_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_list_num + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _is_earc_item_enable
 *
 * Description: sac item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _is_earc_item_enable(VOID)
{
    UINT8 ui1_on;
    a_cfg_get_cec_func (&ui1_on);

    if ( ui1_on   != 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _earc_item_show
 *
 * Description: sac item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _earc_item_show(VOID)
{
    INT16 				i2_idx = 0;
    INT32 				i4_ret = MENUR_OK;;
	MENU_CEC*  pt_this = &t_g_cec_page_data;

	i2_idx = _get_cec_earc_idx();

    menu_list_chg_lang(pt_this->h_sac_item,
                        MLM_MENU_KEY_EARC_MODE, 0, 0);

    menu_list_set_text(pt_this->h_sac_item,
                       0,
                       MENU_TEXT(MLM_MENU_KEY_OFF + i2_idx));

    menu_list_set_idx(pt_this->h_sac_item, 0);
    menu_list_adjust_rect(pt_this->h_sac_item);

	i4_ret = c_wgl_set_visibility(pt_this->h_sac_item,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(_is_earc_item_enable())
    {
        i4_ret = c_wgl_enable(pt_this->h_sac_item,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_enable(pt_this->h_sac_item,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _cec_item_show_ex
 *
 * Description: cec item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _set_cec_earc_idx(UINT16 ui2_idx)
{
    DBG_LOG_PRINT(("#### %s(%d) set earc value %d\n", __FILE__, __LINE__, ui2_idx));

    UINT16   ui2_val = (ui2_idx==0)?0:1;
    UINT16   ui2_spk_out_idx = 0;
    UINT16   ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16   ui2_aud_out_mask = 0;
    INT16    i2_val_ex = 0;

    a_cfg_custom_get_speakers_out(&ui2_spk_out_idx);
    a_cfg_av_get(ui2_id, &i2_val_ex);
    ui2_aud_out_mask = (UINT16)i2_val_ex;

    if(2 != ui2_spk_out_idx)   //TV Speakers is not Auto
    {
        if(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) //TV Speakers is On
        {
            DBG_LOG_PRINT(("#### %s(%d) TV Speakers is On,Turn off the eARC\n", __FILE__, __LINE__));
            ui2_val = 0;
        }
    }
    nav_cec_set_earc_status(ui2_val);
    a_cfg_custom_set_earc(ui2_idx);

    //menu_pm_refresh();
    //menu_pm_repaint();
}

VOID a_set_cec_earc_idx(UINT16 ui2_idx)
{
    _set_cec_earc_idx(ui2_idx);
}

/*----------------------------------------------------------------------------
 * Name: _cec_item_show_ex
 *
 * Description: cec item
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_cec_earc_idx(VOID)
{
    UINT16   ui2_idx = 0;
    a_cfg_custom_get_earc(&ui2_idx);
    DBG_LOG_PRINT(("#### %s(%d) get earc value %d\n", __FILE__, __LINE__, ui2_idx));
    return ui2_idx;;
}

UINT16 a_get_cec_earc_idx(VOID)
{
    return _get_cec_earc_idx();
}

/*----------------------------------------------------------------------------
 * Name: _sac_list_subpage_proc_fct
 *
 * Description:_sac_list_subpage_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _earc_list_subpage_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_CEC* pt_this = &t_g_cec_page_data;

	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EARC_MODE_HELP));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  	ui4_key_code = (UINT32)pv_param1;
        INT32       i4_ret = MENUR_OK;
        UINT16      ui2_idx = 0;
        UINT16      ui2_elem_num = 0;

        switch (ui4_key_code)
        {
        case BTN_CURSOR_UP :
        case BTN_CURSOR_DOWN :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&ui2_elem_num),
                         NULL);

            if(ui4_key_code == BTN_CURSOR_UP)
            {
                if(ui2_idx == 0)
                {
					MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_PREV_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }
            else
            {
                if(ui2_idx == (UINT16)(ui2_elem_num - 1))
                {
					menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
					menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_NEXT_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }

            return MENUR_OK;
        }
        case BTN_SELECT :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            _set_cec_earc_idx(ui2_idx);

			pt_this->e_pre_subpage = SUBPAGE_EARC;
			pt_this->e_subpage = SUBPAGE_MAIN;
			i4_ret = _subpage_show(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        case BTN_EXIT:
        case BTN_RETURN:

			pt_this->e_pre_subpage = SUBPAGE_EARC;
			pt_this->e_subpage = SUBPAGE_MAIN;
			i4_ret = _subpage_show(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;

        default :
            break ;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        UTF16_T     w2s_text[64+1] = {0};
        UINT16      ui2_tts_idx = 0;
        INT32       i4_ret = MENUR_OK;

        i4_ret = c_wgl_do_cmd(pt_this->h_sac_subpage,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_tts_idx),
                         NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_OFF + ui2_tts_idx)) ;
        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    }
#endif

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _earc_list_subpage_create
 *
 * Description:_earc_list_subpage_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _earc_list_subpage_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T   		t_rect;
	MENU_CEC* pt_this = &t_g_cec_page_data;

    SET_RECT_BY_SIZE (&t_rect,
                      CEC_LST_X,
                      CEC_LST_Y,
                      CEC_LST_W,
                      CEC_LST_H);

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32+1;
    at_cols[0].ui2_width        = CEC_LST_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_MULTI_SEL |
                                  WGL_STL_GL_NO_IMG_UI;

    t_lb_init.ui2_max_elem_num  = MAX_REC;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    i4_ret = menu_list2_create (pt_this->h_cnt_frm,
                                &t_rect,
                                _earc_list_subpage_proc_fct,
                                &t_lb_init,
                                NULL,
                                &pt_this->h_sac_subpage);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create list for earc failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _append_earc
 *
 * Description: _append_earc-->append the earc subpage item elem
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _append_earc(VOID)
{
    INT32               i4_ret = MENUR_OK;
    MENU_CEC*  pt_this = &t_g_cec_page_data;
    WGL_LB_ITEM_T       at_items[1];
    UINT16              ui2_idx = 0;

    i4_ret = c_wgl_do_cmd(pt_this->h_sac_subpage,
                         WGL_CMD_LB_DEL_ALL,
                         NULL,
                         NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_idx=0;ui2_idx<LIST_ITEM_SAC_NUM;ui2_idx++)
    {
        /*append the cec elem*/
        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = MENU_TEXT(MLM_MENU_KEY_OFF+ui2_idx);

        i4_ret = c_wgl_do_cmd(pt_this->h_sac_subpage,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _to_prev_sac_idx
 *
 * Description:_to_prev_sac_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_prev_earc_idx(void)
{
	INT32       				i4_ret = MENUR_OK;
    UINT16 						ui2_idx=0;

    ui2_idx = _get_cec_earc_idx();

    if (ui2_idx > 0)
    {
        ui2_idx--;
    }
    else
    {
        ui2_idx = LIST_ITEM_SAC_NUM-1;
    }

	_set_cec_earc_idx(ui2_idx);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _to_next_sac_idx
 *
 * Description:_to_next_sac_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _to_next_earc_idx(void)
{
	INT32       				i4_ret = MENUR_OK;
    UINT16 						ui2_idx=0;

    ui2_idx = _get_cec_earc_idx();

    if (ui2_idx < LIST_ITEM_SAC_NUM-1)
    {
        ui2_idx++;
    }
    else
    {
        ui2_idx = 0;
    }

	_set_cec_earc_idx(ui2_idx);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _sac_list_item_proc_fct
 *
 * Description:_sac_list_item_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _earc_list_item_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_CEC* 				pt_this = &t_g_cec_page_data;
	INT32							i4_ret = MENUR_OK;

	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EARC_MODE_HELP));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if (BTN_CURSOR_LEFT == ui4_key_code)
                {
                    _to_prev_earc_idx();
                }
                else
                {
                    _to_next_earc_idx();
                }
                _earc_item_show();
                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);

			    return MENUR_OK;
            }
            case BTN_SELECT:
            {
                pt_this->h_last_focus_item = pt_this->h_sac_item;
				pt_this->e_pre_subpage = SUBPAGE_MAIN;
				pt_this->e_subpage = SUBPAGE_EARC;
                i4_ret = _subpage_show(TRUE);
				MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
            	c_wgl_set_focus(pt_this->h_cec_item,
	                                 WGL_SYNC_AUTO_REPAINT);
                return WGLR_OK;
			}
            case BTN_CURSOR_DOWN:
            {
            	c_wgl_set_focus(pt_this->h_dev_discovery_item,
	                                 WGL_SYNC_AUTO_REPAINT);
                return WGLR_OK;
            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                menu_nav_back();
                return WGLR_OK;
            }
            default:
                break;
        }
    }
    #ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        UINT16 		ui2_idx=0;
        UTF16_T     w2s_str[64+1] = {0};

        ui2_idx = _get_cec_earc_idx();
        if(ui2_idx == 0)//off
        {
            c_uc_ps_to_w2s("e A R C, OFF", w2s_str, c_strlen("e A R C, OFF"));
        }
        else if(ui2_idx == 1)//on
        {
            c_uc_ps_to_w2s("e A R C, ON", w2s_str, c_strlen("e A R C, ON"));
        }

        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
    }
    #endif

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _sac_list_item_create
 *
 * Description:_cec_list_item_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _earc_list_item_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_CEC*  pt_this = &t_g_cec_page_data;

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_SAC_IDX,
                              LIST_ITEM_SAC_NUM,
                              _earc_list_item_proc_fct,
                              &pt_this->h_sac_item);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    INT32        i4_ret=MENUR_OK;
    MENU_CEC*    pt_this = &t_g_cec_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32          ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
    #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
    #endif
        case BTN_RETURN:

            if(pt_this->e_subpage == SUBPAGE_MAIN)
            {
                menu_nav_back();
            }
            else if(pt_this->e_subpage == SUBPAGE_CEC)
            {
                pt_this->e_pre_subpage = SUBPAGE_CEC;
                pt_this->e_subpage = SUBPAGE_MAIN;
            	i4_ret = _subpage_show(FALSE);
            	MENU_LOG_ON_FAIL(i4_ret);
            }
            return WGLR_OK;

        case BTN_SELECT:
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_UP:
        {
            break ;
        }
        case BTN_CURSOR_DOWN:
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    INT32        i4_ret=MENUR_OK;
    MENU_CEC*    pt_this = &t_g_cec_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_keycode = (UINT32)pv_param1;
        HANDLE_T h_backbar;

        menu_get_backbar_handle(&h_backbar);

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT:
        case BTN_RETURN:
            if(pt_this->e_subpage == SUBPAGE_MAIN)
            {
                menu_nav_back();
            }
            else if(pt_this->e_subpage == SUBPAGE_CEC)
            {
                pt_this->e_pre_subpage = SUBPAGE_CEC;
                pt_this->e_subpage = SUBPAGE_MAIN;
            	i4_ret = _subpage_show(TRUE);
            	MENU_LOG_ON_FAIL(i4_ret);
            }
    #ifndef APP_ARC_ONLY
            else if(pt_this->e_subpage == SUBPAGE_EARC)
            {
                pt_this->e_pre_subpage = SUBPAGE_EARC;
                pt_this->e_subpage = SUBPAGE_MAIN;
            	i4_ret = _subpage_show(TRUE);
            	MENU_LOG_ON_FAIL(i4_ret);
            }
    #endif
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            if(pt_this->e_subpage == SUBPAGE_MAIN)
            {
                i4_ret = c_wgl_set_focus(pt_this->h_cec_item,WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(pt_this->e_subpage == SUBPAGE_CEC)
            {
                i4_ret = c_wgl_set_focus(pt_this->h_cec_subpage,WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }

#ifndef APP_ARC_ONLY
            else if(pt_this->e_subpage == SUBPAGE_EARC)
            {
                i4_ret = c_wgl_set_focus(pt_this->h_sac_subpage,WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
#endif
            return MENUR_OK;

        case BTN_CURSOR_UP:
            MENU_CHK_FAIL (menu_set_focus_on_homebar (TRUE));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _cec_dev_listbox_create
 *
 * Description: discovered cec devices append to the device discovery item.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_cec_view_no_dev_create(VOID)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[2];
    WGL_LB_ITEM_T       at_items[2];
    GL_RECT_T           t_rect;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_INSET_T                 t_inset;
    UTF16_T                     w2s_tmp_str[128]={0};
    UTF16_T                     w2s_str[128]={0};
	MENU_CEC*                   pt_this = &t_g_cec_page_data;

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = MENU_ITEM_V_WIDE-ITEM_V_WIDE_IMG;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align         = WGL_AS_LEFT_CENTER;
	at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width         = ITEM_V_WIDE_IMG;


    t_lb_init.ui4_style         = 0;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      MENU_CEC_DEV_LIST_X,
                      MENU_CEC_DEV_LIST_Y+25,
                      MENU_CEC_DEV_LIST_W,
                      MENU_CEC_DEV_LIST_H * 10);

    i4_ret = menu_list2_create (pt_this->h_cnt_frm,
                                &t_rect,
                                NULL,
                                & t_lb_init,
                                NULL,
                                &pt_this->h_show_info);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for show info failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set background image */
    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = NULL_HANDLE;//h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (pt_this->h_show_info,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = MENU_ITEM_BAR_CNT_INSET_L;
    t_inset.i4_right  = 8; //MENU_ITEM_BAR_CNT_INSET_R;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (pt_this->h_show_info,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    c_uc_w2s_strcpy (w2s_str, L"  ");
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_str;
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_tmp_str;
    i4_ret = c_wgl_do_cmd(pt_this->h_show_info, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;

}
/*----------------------------------------------------------------------------
 * Name: _menu_cec_view_dev_list_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_cec_view_dev_list_create (VOID)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[2];
    GL_RECT_T           t_rect;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_KEY_MAP_T    t_lb_key_map;
    WGL_INSET_T                 t_inset;
	MENU_CEC*           pt_this = &t_g_cec_page_data;
    GL_COLOR_T          		t_color_disable = { 255, {128}, {128}, {128}};
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    UINT8                       ui1_col;

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = ITEM_V_WIDE_TEXT;

    at_cols[1].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[1].ui1_align         = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_width         = ITEM_V_WIDE_IMG;


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = MENU_DEV_LST_MAX_ELEM_NUM;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      MENU_CEC_DEV_LIST_X,
                      MENU_CEC_DEV_LIST_Y,
                      MENU_CEC_DEV_LIST_W,
                      MENU_CEC_DEV_LIST_H);

    i4_ret = menu_list2_create (pt_this->h_cnt_frm,
                                &t_rect,
                                NULL,
                                & t_lb_init,
                                NULL,
                                &pt_this->h_cec_dev_list);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set text color */
    c_memset(&t_clr_elem, 0, sizeof(WGL_LB_COLOR_ELEM_SET_T));
    t_clr_elem.t_normal             = t_g_menu_color_white;
    t_clr_elem.t_disable            = t_color_disable;
    t_clr_elem.t_highlight          = t_g_menu_color_white;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_white;
    t_clr_elem.t_pushed             = t_g_menu_color_white;
    t_clr_elem.t_selected           = t_g_menu_color_white;
    t_clr_elem.t_selected_disable   = t_g_menu_color_white;

    for(ui1_col=0; ui1_col < t_lb_init.ui1_col_num; ui1_col++)
    {
        if(t_lb_init.at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (pt_this->h_cec_dev_list,
                                   WGL_CMD_LB_SET_COL_COLOR,
                                   WGL_PACK_2(ui1_col, WGL_CLR_TEXT),
                                   WGL_PACK(& t_clr_elem));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set background image */
    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (pt_this->h_cec_dev_list,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = DEV_DISCOVERY_BTN_INSET_LEFT;
    t_inset.i4_right  = 8; //MENU_ITEM_BAR_CNT_INSET_R;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (pt_this->h_cec_dev_list,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select = 0;
    t_lb_key_map.ui4_key_page_up    = 0;
    t_lb_key_map.ui4_key_page_down  = 0;
    i4_ret = c_wgl_do_cmd(pt_this->h_cec_dev_list, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cec_dev_list,
                               WGL_SW_HIDE);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _dev_discovery_start
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static INT32 _dev_discovery_start(VOID)
{
    INT32   i4_ret = 0;
    UINT8	ui1_cec_func = 0;
	MENU_CEC*           pt_this = &t_g_cec_page_data;


    i4_ret = c_wgl_set_visibility(pt_this->h_cec_dev_list,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (pt_this->h_show_info != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_show_info);
    }

    i4_ret = _menu_cec_view_no_dev_create();
    MENU_CHK_FAIL(i4_ret);

#ifdef WGL_ANIM_SUPPORT
    HANDLE_T        h_menu_animation = NULL_HANDLE;
    GL_RECT_T       t_rect = {0};

    SET_RECT_BY_SIZE(&t_rect,
                 CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                 CONTENT_Y * 4,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    menu_page_animation_get_handle(&h_menu_animation);
    c_wgl_move(h_menu_animation, &t_rect, FALSE);
#endif

    i4_ret = c_wgl_set_visibility(pt_this->h_cec_subpage,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_get_cec_func (&ui1_cec_func);

    if(ui1_cec_func != 0 )
    {
        i4_ret = c_cecm_stop_dev_discovery (pt_this->h_menu_cecm);
        if(i4_ret != CECMR_OK)
        {
            DBG_ERROR(("!!!!%s, line %d, i4_ret : %d\n", __func__, __LINE__, i4_ret));
        }

        i4_ret = c_cecm_start_dev_discovery (pt_this->h_menu_cecm, 0);
        if(i4_ret != CECMR_OK)
        {
            DBG_ERROR(("!!!!%s, line %d, i4_ret : %d\n", __func__, __LINE__, i4_ret));
        }

        i4_ret = _menu_cec_show_no_dev(MLM_MENU_KEY_CEC_DEV_DISCOVERY_WAIT, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_text[64+1] = {0};

        c_uc_w2s_strcpy(w2s_text, mlm_menu_get_text(0, MLM_MENU_KEY_CEC_DEV_DISCOVERY_WAIT));
        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif

    }

    c_wgl_set_focus(pt_this->h_cnt_frm, WGL_SYNC_AUTO_REPAINT);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _dev_discovery_btn_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _dev_discovery_btn_proc_fct(HANDLE_T	 h_widget,
									  UINT32	 ui4_msg,
									  VOID* 	 param1,
									  VOID* 	 param2)
{
	INT32		        i4_ret = MENUR_OK;
	MENU_CEC*           pt_this = &t_g_cec_page_data;

	switch (ui4_msg)
	{
		case WGL_MSG_GET_FOCUS:
		{
			menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_CEC_DEV_DISCOVER_HELP));
			break;
		}
		case WGL_MSG_KEY_DOWN:
		{
			UINT32 ui4_keycode = (UINT32)param1;
			switch (ui4_keycode)
			{
				case BTN_SELECT:
				{
                    /* adjust last shadow position */
                    GL_RECT_T  t_rect;
                    HANDLE_T   h_last_shadow_item;

                    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
                    MENU_LOG_ON_FAIL(i4_ret);

                    ui1_dev_disc_detect = 1;

                    t_rect.i4_left = CONTENT_X;
                	t_rect.i4_right = CONTENT_X + CONTENT_H;
                	t_rect.i4_top = MENU_ITEM_V_HEIGHT * (MENU_CEC_LIST_ITEM_NUM+ui1_dev_disc_detect) + CONTENT_Y;
                	t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

                	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
                	MENU_LOG_ON_FAIL(i4_ret);

                	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
                	MENU_LOG_ON_FAIL(i4_ret);

                    pt_this->b_dev_discovery_is_sel = TRUE;
                    i4_ret = _dev_discovery_start();
                    MENU_LOG_ON_FAIL(i4_ret);
				}
					break;

				case BTN_CURSOR_UP:
				{
    #ifdef APP_ARC_ONLY
                    i4_ret = c_wgl_set_focus(pt_this->h_cec_item,WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
    #else
                    i4_ret = c_wgl_set_focus(pt_this->h_sac_item,WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
    #endif
				}
					break;

				case BTN_CURSOR_DOWN:
				{
					menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
					menu_pm_repaint();
				}
					break;

				case BTN_RETURN:
				{
					menu_nav_back();
				}
					break;

				default:
					break;
			}
		}
			break;
#ifdef APP_TTS_SUPPORT
		case WGL_MSG_KEY_UP:
		{
            UTF16_T     w2s_text[128+1] = {0};
            i4_ret = c_wgl_do_cmd (pt_this->h_dev_discovery_item,
                               WGL_CMD_BTN_GET_TEXT,
                               WGL_PACK (w2s_text),
                               WGL_PACK (128));
            MENU_LOG_ON_FAIL(i4_ret);

            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
            break;
		}
#endif
		default:
			break;
	}

	return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _menu_cec_add_lb_item
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_cec_add_lb_item (HANDLE_T h_lb, UTF16_T* pw2s_txt, HANDLE_T h_img)
{
    INT32   i4_ret = 0;
    WGL_LB_ITEM_T               at_items[2];

    c_memset(at_items, 0, 2*sizeof(WGL_LB_ITEM_T));
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = pw2s_txt;

    at_items[1].e_col_type = LB_COL_TYPE_IMG;
    at_items[1].data.h_img = h_img;

    i4_ret = c_wgl_do_cmd(h_lb, WGL_CMD_LB_APPEND_ELEM, at_items, NULL);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    return MENUR_OK;
}
/**
 * @brief   This function gets default device name.
 * @param   ui1_la [in] Device LA.
 * @treurn  A UTF16 string.
 */
static UTF16_T* _menu_cec_view_get_def_dev_osd_name (UINT8 ui1_la)
{
    UINT16 ui2_mlm_idx = 0;
    switch (ui1_la)
    {
    case CECM_LOG_ADDR_REC_DEV_1:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_REC_1;
        break;
    case CECM_LOG_ADDR_REC_DEV_2:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_REC_2;
        break;
    case CECM_LOG_ADDR_REC_DEV_3:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_REC_3;
        break;
    case CECM_LOG_ADDR_TUNER_1:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_TUNER_1;
        break;
    case CECM_LOG_ADDR_TUNER_2:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_TUNER_2;
        break;
    case CECM_LOG_ADDR_TUNER_3:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_TUNER_3;
        break;
    case CECM_LOG_ADDR_TUNER_4:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_TUNER_4;
        break;
    case CECM_LOG_ADDR_PLAYBACK_DEV_1:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_PLAY_1;
        break;
    case CECM_LOG_ADDR_PLAYBACK_DEV_2:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_PLAY_2;
        break;
    case CECM_LOG_ADDR_PLAYBACK_DEV_3:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_PLAY_3;
        break;
    case CECM_LOG_ADDR_AUD_SYS:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_AUDIO;
        break;
    case CECM_LOG_ADDR_MAX:
        ui2_mlm_idx = MLM_CEC_KEY_DEV_SETUP;
        break;
    default:
        break;
    }

    return MLM_CEC_TEXT(ui2_g_menu_curr_lang, ui2_mlm_idx);
}

static INT32 _menu_cec_show_no_dev(UINT16 ui2_key, WGL_SW_CMD_T eCmd)
{
    INT32               i4_ret = MENUR_OK;
	MENU_CEC*           pt_this = &t_g_cec_page_data;

    if (pt_this->h_show_info == NULL_HANDLE)
    {
        return MENUR_FAIL;
    }

    i4_ret = c_wgl_do_cmd( pt_this->h_show_info,
                           WGL_CMD_LB_SET_ITEM_TEXT,
                           WGL_PACK_2((0), 0),
                           MENU_TEXT(ui2_key));

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_show_info, eCmd);

    return i4_ret;
}


INT32 get_cec_device_name(UINT8 hdmi_port_id, UTF16_T* cec_device_name, UINT8 ui1_str_len)
{
    UINT8               ui1_la = 0;
    INT32               i4_ret;
    UINT8               ui1_cec_func = 0;
    CEC_DEV_LST_T       t_lst;
    UINT8               ui1_loop = 0;
    UINT8               spd_info[30] = {0};

    //DBG_LOG_PRINT(("[MENU][CEC] get_cec_device_name(port:%d, str_len:%d)\n", hdmi_port_id, ui1_str_len));

    a_cfg_get_cec_func (&ui1_cec_func);
    if(ui1_cec_func == APP_CFG_CEC_OFF)
    {
        //DBG_LOG_PRINT(("[daniel][MENU][CEC]Warning: CEC is off!\n"));
        return MENUR_FAIL;
    }

    // Get name from xbox ...
    i4_ret = nav_cec_custom_get_spd_info(hdmi_port_id, spd_info, sizeof(spd_info));
    if( NAVR_OK != i4_ret )
    {
        //DBG_LOG_PRINT(("[MENU][CEC] Get spd_info failed!\n" ));
    }
    else
    {
        if( 0 != c_strlen(spd_info) )
        {
            DBG_LOG_PRINT(("[MENU][CEC]spd_info[]={%s}\n", spd_info));
            c_uc_ps_to_w2s(spd_info, cec_device_name, ui1_str_len);
            return MENUR_OK;
        }
    }

    // Get name from CEC ...
    c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
    a_cec_get_dev_list(nav_cec_get_mw_handle(), &t_lst, CEC_SORT_TYPE_DEFAULT);

    for (ui1_loop = 0;ui1_loop < t_lst.ui1_dev_num;ui1_loop++)
    {
        //DBG_LOG_PRINT(("[MENU][CEC] ui1_loop:%d, ui2_pa=0x%X \n", ui1_loop, t_lst.at_dev_info[ui1_loop].ui2_pa));

        if((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) == 0)
        {
            UINT8 hdmi_port = (t_lst.at_dev_info[ui1_loop].ui2_pa >> 12) - 1;
            if((hdmi_port == hdmi_port_id) && (hdmi_port < 4))
            {
                //DBG_LOG_PRINT(("[MENU][CEC] hdmi_port:%d, got name=> \n", hdmi_port_id ));

                c_uc_w2s_strncpy(cec_device_name, t_lst.at_dev_info[ui1_loop].aw2_osd_name, ui1_str_len);
                return MENUR_OK;
            }
        }
    }

    return MENUR_FAIL;
}

static BOOL _cec_check_PhyAddr_valid(UINT16 u16PhyAddr)
{
    if( (u16PhyAddr == CECM_INV_PA)||(u16PhyAddr == 0) )
    {
        return FALSE;
    }
    else
    {
        UINT16 u16PhyAddr_Bit15_12 = u16PhyAddr>>12;
        if( (u16PhyAddr_Bit15_12 > 4 )||(u16PhyAddr_Bit15_12 == 0) )
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*----------------------------------------------------------------------------
 * Name: _cec_dev_list_setting_animation_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _cec_dev_discover_cb_fct(
                                      VOID* pv_data,
                                      SIZE_T  z_data_size)
{
    UINT8               ui1_la = 0;
    UINT16              ui2_dev_num = 0;
    INT32               i4_ret;
    CECM_DEV_T          t_dev_info;
    UTF16_T*            pw2s_dev_osd_name = NULL;
    UINT8	        u8DeviceCount = 0;//ui1_idx=0;
    char	        dev_osd_name1[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1]={0};
    char                used_port[5][MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1] = {0};

    MENU_CEC*           pt_this = &t_g_cec_page_data;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

#ifdef APP_ARC_ONLY
	UINT8	ui1_cec_func = 0;
	CEC_DEV_LST_T   t_lst;
	UINT8	ui1_loop = 0;

	a_cfg_get_cec_func (&ui1_cec_func);
	if(ui1_cec_func == APP_CFG_CEC_ARC_ONLY)
	{
		c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));

		 /* clear the list */
	    c_wgl_do_cmd(pt_this->h_cec_dev_list, WGL_CMD_LB_DEL_ALL, NULL, NULL);

		i4_ret = a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);
		if(i4_ret != MENUR_OK)
		{
			DBG_ERROR(("\n####%s(%d)a_cec_get_dev_list fail return[]\n",__FUNCTION__,__LINE__,i4_ret));
		}

		for (ui1_loop = 0;ui1_loop < t_lst.ui1_dev_num;ui1_loop++)
		{
			if((t_lst.at_dev_info[ui1_loop].e_la == CECM_LOG_ADDR_AUD_SYS)&&
				(c_uc_w2s_strlen(t_lst.at_dev_info[ui1_loop].aw2_osd_name)!=0)&&
				(t_lst.at_dev_info[ui1_loop].b_amp_connected==FALSE))
			{
				pw2s_dev_osd_name = t_lst.at_dev_info[ui1_loop].aw2_osd_name;

				c_uc_w2s_to_ps(pw2s_dev_osd_name, dev_osd_name1, MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
				i4_ret = _menu_cec_add_lb_item (pt_this->h_cec_dev_list, pw2s_dev_osd_name, NULL_HANDLE);
				if(i4_ret != MENUR_OK)
				{
					DBG_ERROR(("\n####%s(%d)_menu_cec_add_lb_item fail return[]\n",__FUNCTION__,__LINE__,i4_ret));
				}
				u8DeviceCount++;
#ifdef APP_TTS_SUPPORT
                a_app_tts_play(t_lst.at_dev_info[ui1_loop].aw2_osd_name, c_uc_w2s_strlen(t_lst.at_dev_info[ui1_loop].aw2_osd_name));
#endif
			}
		}
	}
	else
#endif
    {
        CECM_CTRL_T t_cecm_ctrl = {0};
        t_cecm_ctrl.b_sync = TRUE;

	    /* clear the list */
	    c_wgl_do_cmd(pt_this->h_cec_dev_list, WGL_CMD_LB_DEL_ALL, NULL, NULL);

        DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} Check all CEC device:%d ~ %d\n", __FUNCTION__, __LINE__, CECM_LOG_ADDR_REC_DEV_1, CECM_LOG_ADDR_UNREGED_BRDCST-1 ));
	    for (ui1_la = CECM_LOG_ADDR_REC_DEV_1;ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST;ui1_la++)
	    {
            c_memset (&t_dev_info, 0, sizeof (CECM_DEV_T));

	        i4_ret = c_cecm_get_dev_info_by_la (
	                                    pt_this->h_menu_cecm,
	                                    (CECM_LOG_ADDR_T)ui1_la,
	                                    &t_cecm_ctrl,
	                                    &t_dev_info);
	        if (i4_ret != CECMR_OK)
	        {
	            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
	            break;
	        }
	        if ((t_dev_info.e_dev_state != CECM_DEV_STATE_UPDATED) || (t_dev_info.t_report_phy_addr.ui2_pa == CECM_INV_PA))
	        {
	            continue;
	        }


	        if (c_uc_w2s_strlen(t_dev_info.aw2_osd_name) != 0)
	        {
    	        char acCecName[MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN+1]={0};
                c_uc_w2s_to_ps(t_dev_info.aw2_osd_name, acCecName, MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
                DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} LA=%d, pa=0x%X, CEC_name[]={%s}\n", __FUNCTION__, __LINE__, ui1_la, t_dev_info.t_report_phy_addr.ui2_pa, acCecName ));

	            pw2s_dev_osd_name = t_dev_info.aw2_osd_name;
	        }
	        else
	        {
                DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} LA=%d, pa=0x%X, No CEC name => Use default name\n", __FUNCTION__, __LINE__, ui1_la, t_dev_info.t_report_phy_addr.ui2_pa ));
	            pw2s_dev_osd_name = _menu_cec_view_get_def_dev_osd_name(ui1_la);
	        }

            c_uc_w2s_to_ps(pw2s_dev_osd_name, dev_osd_name1, MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
            if( c_strlen(dev_osd_name1) )
            {
                DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} LA:%d, dev_osd_name1[%d]={%s}\n", __FUNCTION__, __LINE__, ui1_la, c_strlen(dev_osd_name1), dev_osd_name1 ));
            }

            //DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} LA=%d, pa=0x%X\n", __FUNCTION__, __LINE__, ui1_la, t_dev_info.t_report_phy_addr.ui2_pa ));
            // Check PA valid?
            if( FALSE == _cec_check_PhyAddr_valid(t_dev_info.t_report_phy_addr.ui2_pa) )
            {
                // Invalid PA!
                DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} Error: Invalid PA(0x%X) at LA=%d\n", __FUNCTION__, __LINE__, t_dev_info.t_report_phy_addr.ui2_pa, ui1_la ));
                continue;
            }

            UINT8 hdmi_port = t_dev_info.t_report_phy_addr.ui2_pa >> 12;
            //DBG_LOG_PRINT(("#### %s(%d) port=%d osd=%s,used_port=%s\n", __FILE__, __LINE__, hdmi_port, dev_osd_name1, used_port[hdmi_port]));
            if( hdmi_port <= 4 )
            {
                if(c_strlen(used_port[hdmi_port]) == 0)
                {
                    if( c_strlen(dev_osd_name1) )
                    {
                        c_strcpy(used_port[hdmi_port], dev_osd_name1); // Update to used_port[hdmi_port]
                        DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} LA:%d, Set used_port[%d]={%s}\n", __FUNCTION__, __LINE__, ui1_la, hdmi_port, used_port[hdmi_port] ));
                    }
                }
                else
                {
                    DBG_LOG_PRINT(("[MENU][CEC]{%s,%d} Warning: LA:%d, used_port[%d]={%s} \n", __FUNCTION__, __LINE__, ui1_la, hdmi_port, used_port[hdmi_port] ));
	                //DBG_INFO(("\n####dev_osd_name3 = %s\n",used_port[hdmi_port]));
                    if ( 0 == c_strcmp(used_port[hdmi_port], dev_osd_name1) )
                    {
                        continue; // Same device found...
                    }
                }
            }

	        if (t_dev_info.b_act_src)
	        {
	            i4_ret = _menu_cec_add_lb_item (pt_this->h_cec_dev_list, pw2s_dev_osd_name, NULL_HANDLE);
	        }
	        else
	        {
	            i4_ret = _menu_cec_add_lb_item (pt_this->h_cec_dev_list, pw2s_dev_osd_name, NULL_HANDLE);
	        }

	        //c_uc_w2s_to_ps(pw2s_dev_osd_name, dev_osd_name1, MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN);
	        //DBG_INFO(("\n####dev_osd_name1 = %s\n",dev_osd_name1));

			u8DeviceCount++;
	    }
		DBG_INFO(("\n#### %s(%d) dev_num = %d\n",__FUNCTION__, __LINE__, u8DeviceCount));
	}

    c_wgl_do_cmd(pt_this->h_cec_dev_list, WGL_CMD_LB_GET_ELEM_NUM, WGL_PACK (&ui2_dev_num), NULL);

    if (0 == ui2_dev_num)
    {
        i4_ret = _menu_cec_show_no_dev(MLM_MENU_KEY_CEC_DEV_DISCOVERY_NO_DEV, WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        UTF16_T     w2s_text[64+1] = {0};

        c_uc_w2s_strcpy(w2s_text, mlm_menu_get_text(0, MLM_MENU_KEY_CEC_DEV_DISCOVERY_NO_DEV));
        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif
    }
    else
    {
        i4_ret = _menu_cec_show_no_dev(MLM_MENU_KEY_EMPTY, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_wgl_set_focus(pt_this->h_dev_discovery_item, WGL_SYNC_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(pt_this->h_cec_dev_list, WGL_SW_NORMAL);
    c_wgl_repaint(pt_this->h_cec_dev_list, NULL, TRUE);

    if (ui2_dev_num > 0)
    {
        /* adjust last shadow position */
        i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
        MENU_LOG_ON_FAIL(i4_ret);

        t_rect.i4_left = CONTENT_X;
    	t_rect.i4_right = CONTENT_X + CONTENT_H;
    	t_rect.i4_top = MENU_ITEM_V_HEIGHT * ( MENU_CEC_LIST_ITEM_NUM + ui2_dev_num ) + CONTENT_Y;
    	t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    	MENU_LOG_ON_FAIL(i4_ret);

    	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    	MENU_LOG_ON_FAIL(i4_ret);

    	/* the cec dev list is not selected, so disable it*/
    	i4_ret = c_wgl_enable(pt_this->h_cec_dev_list, FALSE);

    	c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
    }

    pt_this->b_dev_discovery_is_sel = FALSE;

#ifdef WGL_ANIM_SUPPORT
    menu_page_animation_stop();
    menu_page_animation_hide();
#endif
}

#define         MAX_HDMI_INPUT      4
#define         get_cec_num_max     50
#define         W2S_HDMI_NAME_LEN   32

static UINT8    get_name_num[MAX_HDMI_INPUT] = {0};
static BOOL     _start_cec_change[MAX_HDMI_INPUT] = {FALSE};
static BOOL     _hdmi_cec_5V_status[MAX_HDMI_INPUT] = {FALSE};

static VOID _menu_cec_name_change(VOID* pv_data, SIZE_T z_data_len)
{
    INT32       i4_ret;
    UINT8       hdmi_port_id = 0;
    UINT8       ui1_cec_func = APP_CFG_CEC_OFF;
    UTF16_T     W2S_HDMI_NAME[W2S_HDMI_NAME_LEN];
    CHAR        CEC_HDMI_NAME[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    S_HDMI_NAME_T CFG_HDMI_NAME;
    
    a_cfg_get_cec_func(&ui1_cec_func);
    if(APP_CFG_CEC_OFF== ui1_cec_func)
    {
        c_timer_stop(cec_name_timer);
        return;
    }

    for(hdmi_port_id = 0; hdmi_port_id < MAX_HDMI_INPUT; hdmi_port_id++)
    {
        if(TRUE == _start_cec_change[hdmi_port_id])
        {
            if(_hdmi_cec_5V_status[hdmi_port_id] == TRUE)
            {
                if(get_name_num[hdmi_port_id]++ > get_cec_num_max)                              //for HDMI device which without CEC
                {
                    _start_cec_change[hdmi_port_id] = FALSE;
                }

                i4_ret = get_cec_device_name(hdmi_port_id, W2S_HDMI_NAME, W2S_HDMI_NAME_LEN);
                if((MENUR_OK == i4_ret) && (c_uc_w2s_strlen(W2S_HDMI_NAME) != 0))
                {
                    c_uc_w2s_to_ps(W2S_HDMI_NAME, CEC_HDMI_NAME, APP_CFG_CUSTOM_INP_NAME_LEN);
                    a_nav_ipts_get_cec_name(hdmi_port_id, &CFG_HDMI_NAME);

                    DBG_LOG_PRINT(("[%s] CEC_HDMI_NAME: %s; cec_name: %s \n", __FUNCTION__, CEC_HDMI_NAME, CFG_HDMI_NAME.cec_name));

                    if(c_strcmp(CEC_HDMI_NAME, CFG_HDMI_NAME.cec_name) == 0)  //HDMI CEC name is same as the last name, do not need to change the showing name
                    {
                        DBG_LOG_PRINT((" same hdmi name [%d] ,CFG_HDMI_NAME.show_cec_name=%d\n", hdmi_port_id,CFG_HDMI_NAME.show_cec_name));

                        //a_cfg_set_the_hdmi_priority_name(hdmi_port_id, CFG_HDMI_NAME.show_cec_name);
                        _start_cec_change[hdmi_port_id] = FALSE;

                        c_thread_delay(300);
                        if(0 == hdmi_port_id)
                        {
                            rest_event_notify("system/input/name", 1,"hdmi1");
                        }
                        else if(1 == hdmi_port_id)
                        {
                            rest_event_notify("system/input/name", 1,"hdmi2");
                        }
                        else if(2 == hdmi_port_id)
                        {
                            rest_event_notify("system/input/name", 1,"hdmi3");
                        }
                        else if(3 == hdmi_port_id)
                        {
                            rest_event_notify("system/input/name", 1,"hdmi4");
                        }
                    }
                    else
                    {
                        c_strcpy(CFG_HDMI_NAME.cec_name, CEC_HDMI_NAME);
                        CFG_HDMI_NAME.show_cec_name = TRUE;
                        a_nav_ipts_set_cec_name(hdmi_port_id, &CFG_HDMI_NAME);

                        DBG_LOG_PRINT(("new hdmi name [%d] \n", hdmi_port_id));
                        //a_cfg_set_the_hdmi_priority_name(hdmi_port_id,TRUE);
                        _start_cec_change[hdmi_port_id] = FALSE;
                    }
                }
                                          
            }
            else
            {
                DBG_LOG_PRINT(("[%s] default hdmi name [%d] \r\n", __FUNCTION__, hdmi_port_id));
                a_cfg_set_the_hdmi_priority_name(hdmi_port_id,FALSE);
                _start_cec_change[hdmi_port_id] = FALSE;
            }
        }
    }

    for(hdmi_port_id = 0; hdmi_port_id < MAX_HDMI_INPUT; hdmi_port_id++)
    {
        if(TRUE == _start_cec_change[hdmi_port_id])
        {
            return;
        }
    }
    c_timer_stop(cec_name_timer);
}

static VOID _menu_cec_name_check_timer_nfy(HANDLE_T h_timer, VOID* pv_tag)
{
    a_agent_async_invoke(_menu_cec_name_change,NULL,0);
}

static VOID _menu_cec_name_check_timer_reset(VOID)
{
    INT32 i4_ret;
    HANDLE_T cec_tmp_handle;

    c_timer_stop(cec_name_timer);

    i4_ret = c_timer_start(
                    cec_name_timer,
                    500,
                    X_TIMER_FLAG_REPEAT,
                    _menu_cec_name_check_timer_nfy,
                    &cec_tmp_handle
                    );

    if (i4_ret != OSR_OK) {
        DBG_ERROR(("[hongzhao] _nav_cec_name_check_timer start timer error\r\n"));
    }
}

static INT32 _menu_cec_check_is_vcec_notify_need(CEC_DEV_LST_T t_lst, BOOL* pb_notify, UINT8*  vdev_name, UINT8 vdev_len)
{
    UINT32      ui4_last_vcec_num = ui4_vcec_num;
    UINT8       ui1_loop = 0;
    UTF16_T*    pw2s_dev_osd_name = NULL;

    if (pb_notify == NULL)
    {
        return MENUR_INV_ARG;
    }

    ui4_vcec_num = 0;
    for (ui1_loop = 0; ui1_loop < t_lst.ui1_dev_num; ui1_loop++)
    {
        if(0 != (t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0FFF))
        {
            pw2s_dev_osd_name = t_lst.at_dev_info[ui1_loop].pw2s_dev_name;
            c_uc_w2s_to_ps(pw2s_dev_osd_name, vdev_name, vdev_len);
            ui4_vcec_num++;
        }
    }
    NAV_CEC_LOG_A("[VCEC NOTIFY] ui4_vcec_num = %d, ui4_last_vcec_num = %d\n", ui4_vcec_num, ui4_last_vcec_num);
    *pb_notify = ui4_last_vcec_num != ui4_vcec_num;
    NAV_CEC_LOG_A("[VCEC NOTIFY] pb_notify = %d, strlen = %d\n", *pb_notify, c_strlen(vdev_name));
    return MENUR_OK;
}

static INT32 _menu_cec_try_do_vcec_notify(CEC_DEV_LST_T t_lst)
{
    BOOL b_notify = FALSE;
    UINT8 vdev_name[30] = {0};
    UINT32 ui4_pre_vcec_num = ui4_vcec_num;

    MENU_CHK_FAIL(_menu_cec_check_is_vcec_notify_need(t_lst, &b_notify, vdev_name, sizeof(vdev_name)));
    if(b_notify)
    {
        if(0 !=c_strlen(vdev_name))  // insert cec
        {
            c_memset(ui1_vcec_name, 0, sizeof(ui1_vcec_name));
            c_memcpy(ui1_vcec_name,  vdev_name, c_strlen(vdev_name));
        }
        if(ui4_vcec_num > ui4_pre_vcec_num) //insert case
        {
            rest_event_notify("system/input/enable", 1, ui1_vcec_name);
        }
        else if(ui4_vcec_num < ui4_pre_vcec_num) //remove case
        {
            rest_event_notify("system/input/enable", 0, ui1_vcec_name);
        }
        c_thread_delay(300);
        rest_event_notify("system/input/name", 1, ui1_vcec_name);

    }
    return MENUR_OK;
}


static INT32 _menu_vcec_discovery_timer_stop(VOID)
{
    if (ui4_vcec_num > 0)
    {
        if(0 !=c_strlen(ui1_vcec_name))
        {
            rest_event_notify("system/input/enable", 0, ui1_vcec_name);
            c_thread_delay(300);
            rest_event_notify("system/input/name", 1, ui1_vcec_name);
        }
    }
    ui4_vcec_num = 0;
    NAV_CEC_LOG_A("[VCEC NOTIFY] ui4_vcec_num=%d strlen=%d \r\n", ui4_vcec_num, c_strlen(ui1_vcec_name));
    MENU_CHK_FAIL(c_timer_stop(vcec_discovery_timer));
    b_vdt_start = FALSE;
    return MENUR_OK;
}


static INT32 _do_vcec_discovery_timer(VOID)
{
    CEC_DEV_LST_T   t_lst;
    UINT8       ui1_cec_func = APP_CFG_CEC_ON;
    HANDLE_T    h_cecm = nav_cec_get_mw_handle();
    CECM_POLLING_INFO_T     t_polling_info;

    c_memset(&t_lst, 0, sizeof (CEC_DEV_LST_T));
    c_memset(&t_polling_info, 0, sizeof(CECM_POLLING_INFO_T));

    MENU_CHK_FAIL(a_cfg_get_cec_func(&ui1_cec_func));
    if (APP_CFG_CEC_OFF == ui1_cec_func)
    {
        NAV_CEC_LOG_A("[VCEC NOTIFY]ui1_cec_func = %d\n\r", ui1_cec_func);
        MENU_CHK_FAIL(_menu_vcec_discovery_timer_stop());
        return MENUR_OK;
    }
    if (nav_is_in_power_off())
    {
        NAV_CEC_LOG_A("[VCEC NOTIFY]is power off\n\r");
        MENU_CHK_FAIL(_menu_vcec_discovery_timer_stop());
        return MENUR_OK;
    }
    MENU_CHK_FAIL(c_cecm_set_polling_message(h_cecm,
                                    CECM_LOG_ADDR_AUD_SYS,
                                    TRUE,
                                    &t_polling_info));
    if (t_polling_info.b_ack_ok == FALSE)
    {
        NAV_CEC_LOG_A("[VCEC NOTIFY] no amp connect(%d)\n\r", t_polling_info.b_ack_ok);
        MENU_CHK_FAIL(_menu_vcec_discovery_timer_stop());
        return MENUR_OK;
    }

    MENU_CHK_FAIL(c_cecm_stop_dev_discovery (h_cecm));
    MENU_CHK_FAIL(c_cecm_start_dev_discovery(h_cecm, NAV_CEC_DEV_DISCOVERY_INTERVAL));
    MENU_CHK_FAIL(a_cec_get_dev_list(h_cecm, &t_lst, CEC_SORT_TYPE_DEFAULT));
    NAV_CEC_LOG_A("[VCEC NOTIFY] [%s][%d] ui1_dev_num=%d\n", __FUNCTION__, __LINE__, t_lst.ui1_dev_num);
    if(0 == t_lst.ui1_dev_num)
    {
        NAV_CEC_LOG_A("[VCEC NOTIFY] [%s][%d] no cec device, stop timer \n", __FUNCTION__, __LINE__);
        MENU_CHK_FAIL(_menu_vcec_discovery_timer_stop());
        return MENUR_OK;
    }
    MENU_LOG_ON_FAIL(_menu_cec_try_do_vcec_notify(t_lst));
    return MENUR_OK;

}

static VOID _do_vcec_discovery_timer_warp(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    MENU_LOG_ON_FAIL(_do_vcec_discovery_timer());
}

static VOID _timer_cec_discovery_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    nav_request_context_switch(_do_vcec_discovery_timer_warp,NULL, NULL,NULL);
}


static INT32 _menu_vcec_discovery_timer_start(VOID)
{
    if (b_vdt_start)
    {
        return MENUR_OK;
    }
    MENU_CHK_FAIL(c_timer_start(vcec_discovery_timer,
                   CEC_REPEAT_DISCOVERY_INTER,
                   X_TIMER_FLAG_REPEAT,
                   _timer_cec_discovery_fct,
                   NULL));
    b_vdt_start = TRUE;
    NAV_CEC_LOG_A("[VCEC NOTIFY] [%s][%d] \n",__FUNCTION__,__LINE__);
    return MENUR_OK;
}

//
//****************************************************************************************
//

void _cec_hot_plug_dev_status_update(UINT16  ui2_port_id, BOOL  b_5v_status)
{
    UINT8   ui1_hide_value = 0;
    UINT32  i4_ret = 0;

    DBG_LOG_PRINT(("<HDMI 5v> [%s][%d] b_5v_status: %d ui2_port_id: %d\n", \
                        __FUNCTION__, __LINE__, b_5v_status, ui2_port_id));

    nav_cec_arc_set_5v_status(ui2_port_id, b_5v_status);

    i4_ret = a_cfg_cust_get_hide_from_input(&ui1_hide_value);
    MENU_LOG_ON_FAIL(i4_ret);

    _hdmi_cec_5V_status[ui2_port_id - 1] = b_5v_status;
    get_name_num[ui2_port_id - 1] = 0;
    _start_cec_change[ui2_port_id - 1] = TRUE;

    BOOL b_cec_name_valid = FALSE;
    UTF16_T w2s_cec_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
    CHAR  CEC_CUST_HDMI_NAME_LAST[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    //Find CEC name if available. 
    b_cec_name_valid = a_cfg_cust_cec_get_device_name(ui2_port_id - 1, w2s_cec_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    if( b_cec_name_valid )
    {
        c_uc_w2s_to_ps(w2s_cec_name, CEC_CUST_HDMI_NAME_LAST, APP_CFG_CUSTOM_INP_NAME_LEN);
        DBG_LOG_PRINT(("[ACFG][INPUT_SRC][CEC]{%s,%d} Got CEC name:  CEC_CUST_HDMI_NAME_LAST:[%s],cec_name_port[ui2_port_id - 1]=%s\n",
            __FUNCTION__, __LINE__, CEC_CUST_HDMI_NAME_LAST,cec_name_port[ui2_port_id - 1] )); 
     }
    if(!b_5v_status)
    {
        //DTV03032448:update hdmi unplug status to avoid cec name not updated yet when isl get it
        c_strcpy(cec_name_port[ui2_port_id - 1], CEC_CUST_HDMI_NAME_LAST);//if plug a new CEC device,it will show the new CEC name even it has input name   
        a_cfg_set_the_hdmi_priority_name((ui2_port_id - 1), FALSE);
    }
    else
    {
        if ( 0 != c_strcmp(cec_name_port[ui2_port_id - 1], CEC_CUST_HDMI_NAME_LAST) )  
        {
            c_strcpy(cec_name_port[ui2_port_id - 1], CEC_CUST_HDMI_NAME_LAST);//if plug a new CEC device,it will show the new CEC name even it has input name
            //a_cfg_set_the_hdmi_priority_name(ui2_port_id - 1,TRUE);
         }  
    }
    _menu_cec_name_check_timer_reset();

    // HDMI status change
    _timer_cec_discovery_fct(vcec_discovery_timer, NULL);

    /* plug cec dev */
    if(b_5v_status == 1)
    {
        rest_notify_flag = TRUE;
        ui1_hide_value |= ((UINT8)1 << (ui2_port_id - 1));
        i4_ret = a_cfg_cust_set_hide_from_input(ui1_hide_value);
        MENU_LOG_ON_FAIL(i4_ret);
        MENU_LOG_ON_FAIL(_menu_vcec_discovery_timer_start());
    }

    /* unplug cec dev */
    if(b_5v_status == 0)
    {
        /*1==visible 0==hide*/
        ui1_hide_value &= ~((UINT8)1 << (ui2_port_id - 1));
        i4_ret = a_cfg_cust_set_hide_from_input(ui1_hide_value);
        MENU_LOG_ON_FAIL(i4_ret);

        nav_ipts_lst_set_cast_hdmi_hot_plug(ui2_port_id,FALSE);
        a_menu_test_patterns_turn_off();
    }
    else
    {
         nav_ipts_lst_set_cast_hdmi_hot_plug(ui2_port_id,TRUE);
         a_menu_test_patterns_clean_warming_msg();
    }

    if(b_5v_status == 0)
    {
        if(1 == ui2_port_id)
        {
            rest_event_notify("system/input/name", 0, "hdmi1");
            c_thread_delay(300);
            rest_event_notify("system/input/cec", 0, "hdmi1");
        }
        else if(2 == ui2_port_id)
        {
            rest_event_notify("system/input/name", 0, "hdmi2");
            c_thread_delay(300);
            rest_event_notify("system/input/cec", 0, "hdmi2");
        }
        else if(3 == ui2_port_id)
        {
            rest_event_notify("system/input/name", 0, "hdmi3");
            c_thread_delay(300);
            rest_event_notify("system/input/cec", 0, "hdmi3");
        }
        else if(4 == ui2_port_id)
        {
            rest_event_notify("system/input/name", 0, "hdmi4");
            c_thread_delay(300);
            rest_event_notify("system/input/cec", 0, "hdmi4");
        }
    }

    menu_input_repaint_hide_input_orig();
}


static VOID _cec_hot_plug_dev_cb_fct( VOID* pv_data, SIZE_T  z_data_size)
{
    UINT16  ui2_port_id = 0;
    BOOL    b_5v_status = 0;
    UINT8   ui1_hide_value = 0;
    UINT32  i4_ret = 0;

    if(pv_data == NULL)
    {
        DBG_ERROR(("<HDMI 5v> [%s][%d] data is NULL\n", __FUNCTION__, __LINE__));
        return;
    }

    b_5v_status = ((CECM_NFY_T*)pv_data)->u_data.t_5v_pwr_info.b_5v_power;
    ui2_port_id = ((CECM_NFY_T*)pv_data)->u_data.t_5v_pwr_info.ui2_comp_id;
    DBG_LOG_PRINT(("<HDMI 5v> [%s][%d] 5v_status: %d, port_id: %d \n", __FUNCTION__, __LINE__, b_5v_status, ui2_port_id));

    _cec_hot_plug_dev_status_update(ui2_port_id, b_5v_status);
}

/*----------------------------------------------------------------------------
 * @brief   This function will be called by MW if there is notification available.
 *          This function may be called by CLI test function.
 * @param   pv_nfy_data [in]    A pointer to CECM_NFY_T.
 * @param   pv_tag [in]         A private tag value.
 * @param   ui4_data [in]       Not used now.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 ----------------------------------------------------------------------------*/
static VOID _menu_cec_nfy_fct (CECM_NFY_T*   pv_nfy_data,
                              VOID*         pv_tag,
                              UINT32        ui4_data)
{
    CECM_MSGCODE_T e_msg = pv_nfy_data->u_code.e_msgcode;
	MENU_CEC*           pt_this = &t_g_cec_page_data;

    if(pv_nfy_data->e_nfy_type == CECM_NFY_TYPE_MSGCODE && pv_nfy_data->u_code.e_msgcode == CECM_MSGCODE_5V_PWR)
    {
        menu_async_invoke(_cec_hot_plug_dev_cb_fct, (VOID *)pv_nfy_data, sizeof(CECM_NFY_T), TRUE);
    }

    if(menu_get_cond() != MENU_COND_SHOW || !pt_this->b_this_page_show || !pt_this->b_dev_discovery_is_sel)
    {
        return;
    }

    if(e_msg == CECM_MSGCODE_DEV_LIST_NFY){
        menu_async_invoke(_cec_dev_discover_cb_fct, (VOID *)pv_nfy_data, sizeof(CECM_NFY_T), TRUE);
    }
}
extern UINT32 hdmi_hot_plug_status (UINT16  ui2_internal_id)
{
    return _hdmi_cec_5V_status[ui2_internal_id];
}


#ifdef WGL_ANIM_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _cec_dev_list_setting_animation_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _cec_dev_list_setting_animation_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    menu_page_animation_stop();
    menu_page_animation_hide();

    menu_set_focus_on_backbar(TRUE);
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
}
/*----------------------------------------------------------------------------
 * Name: _cec_dev_list_setting_animation_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _cec_dev_list_setting_animation_cb_fct(HANDLE_T                h_widget,
                      UINT16                  ui2_anim_type,
                      WGL_ANIM_COND_INF_T     e_anim_cond,
                      VOID*                   pv_tag)
{
    if (_ANIM_TOTAL_END(&e_anim_cond))
    {
        menu_async_invoke(_cec_dev_list_setting_animation_nfy, NULL, 0, TRUE);
    }
    return MENUR_OK;
}
#endif

/*-----------------------------------------------------------------------------
                   page interface implementation
-----------------------------------------------------------------------------*/

static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32           i4_ret = MENUR_OK;
    MENU_CEC*       pt_this = &t_g_cec_page_data;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &pt_this->h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_ARC_ONLY
    /*cec item*/
    i4_ret = _cec_list_item_create_ex();
    MENU_LOG_ON_FAIL(i4_ret);
#else
    /*cec item*/
    i4_ret = _cec_list_item_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*earc item*/
    i4_ret = _earc_list_item_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /*sac subpage*/
    i4_ret = _earc_list_subpage_create();
    MENU_LOG_ON_FAIL(i4_ret);
#endif


    /*device discovery item*/
    i4_ret = _dev_discovery_btn_create(pt_this->h_cnt_frm,
                                        _dev_discovery_btn_proc_fct,
                                        MENU_TEXT(MLM_MENU_KEY_CEC_DEV_DISCOVER),
                                        &pt_this->h_dev_discovery_item);

    MENU_LOG_ON_FAIL(i4_ret);

    /*cec dev list*/
    i4_ret = _menu_cec_view_dev_list_create();
    MENU_CHK_FAIL(i4_ret);

    /*cec subpage*/
    i4_ret = _cec_list_subpage_create();
    MENU_LOG_ON_FAIL(i4_ret);

    /* Register notify function to MW. */
    i4_ret = c_cecm_open_svc (_menu_cec_nfy_fct, NULL, &pt_this->h_menu_cecm);
    if (i4_ret != CECMR_OK)
    {
        DBG_ERROR(("!!!!%s line %d c_cecm_open_svc fail\n", __FILE__, __LINE__));
    }

#ifdef WGL_ANIM_SUPPORT
    menu_page_animation_set_callback_fct(_cec_dev_list_setting_animation_cb_fct, NULL);
#endif

    if (c_handle_valid(cec_name_timer) == TRUE) {
        c_timer_delete(cec_name_timer);
    }
    i4_ret = c_timer_create(&cec_name_timer);
    MENU_CHK_FAIL(i4_ret);

    if (c_handle_valid(vcec_discovery_timer) == TRUE) {
        c_timer_delete(vcec_discovery_timer);
    }
    i4_ret = c_timer_create(&vcec_discovery_timer);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    MENU_CEC*       pt_this = &t_g_cec_page_data;

    c_cecm_close_svc (pt_this->h_menu_cecm);

    if(pt_this->h_cec_dev_list != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_this->h_cec_dev_list);
    }

    if (c_handle_valid(cec_name_timer) == TRUE) {
        c_timer_delete(cec_name_timer);
    }
    cec_name_timer = NULL_HANDLE;

    if (c_handle_valid(vcec_discovery_timer) == TRUE) {
        c_timer_delete(vcec_discovery_timer);
    }
    vcec_discovery_timer = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32           i4_ret = 0;

    MENU_CEC*       pt_this = &t_g_cec_page_data;

    pt_this->b_this_page_show = TRUE;

    /* title */
    menu_main_set_title(MLM_MENU_KEY_CEC_SETTINGS);

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    menu_set_homebar_proc(_homebar_proc_fct);

#ifdef WGL_ANIM_SUPPORT
    HANDLE_T        h_menu_animation = NULL_HANDLE;
    GL_RECT_T       t_rect = {0};

    SET_RECT_BY_SIZE(&t_rect,
                 CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                 CONTENT_Y * 4,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    menu_page_animation_get_handle(&h_menu_animation);
    c_wgl_move(h_menu_animation, &t_rect, FALSE);
#endif

    ui1_dev_disc_detect = 0;

	pt_this->e_subpage = SUBPAGE_MAIN;
	i4_ret = _subpage_show(FALSE);
	MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    MENU_CEC*       pt_this = &t_g_cec_page_data;

    pt_this->b_this_page_show = FALSE;

#ifdef WGL_ANIM_SUPPORT
    INT32    i4_ret = MENUR_OK;

    i4_ret = menu_page_animation_stop();
    MENU_CHK_FAIL(i4_ret);
#endif

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

extern UTF16_T* get_def_dev_osd_name (UINT8 ui1_la)
{
    return _menu_cec_view_get_def_dev_osd_name(ui1_la);
}

extern INT32 menu_common_page_cec_init(VOID)
{
    t_g_menu_common_page_cec.pf_menu_page_create      = _on_page_create;
    t_g_menu_common_page_cec.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_common_page_cec.pf_menu_page_show        = _on_page_show;
    t_g_menu_common_page_cec.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_common_page_cec.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_common_page_cec.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_common_page_cec.pf_menu_page_update      = _on_page_update;

    return MENUR_OK;
}
#endif /* APP_CEC_MENU  */


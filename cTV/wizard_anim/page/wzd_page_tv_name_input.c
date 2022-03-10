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
#include "wizard_anim/wzd.h"
#include "wizard_anim/page/wzd_page_tv_name_input.h"
#include "res/wizard_anim/wzd_img.h"
#include "res/wdk/wdk_img.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/isl/a_isl_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "menu2/a_menu.h"
#include "wizard_anim/page/wzd_page_tv_setup.h"
//#include "wfrrc_interface.h"

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
#include "c_cecm.h"
#include "nav/cec2/nav_cec.h"
#include "res/nav/cec2/nav_cec_custom.h"
#endif//APP_ARC_ONLY
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

#define WZD_DEVICE_NAME_INPUT_SHOW_MIG_MAX_NUM          (256)
#define WZD_DEVICE_NAME_INPUT_INPUT_SRC_NUM             (16)
#define WZD_DEVICE_NAME_INPUT_INPUT_NUM                 (8)
#define WZD_DEVICE_NAME_INPUT_LEN_MAX                   (128)
#define WZD_DEVICE_NAME_INPUT_TYPE_NUM                  (8)
#define WZD_DEVICE_NAME_INPUT_TYPE_LEN                  (32)

typedef enum _TV_DEVICE_NAME_INPUT_TYPE
{
   DEVICE_TYPE_SELECT_BLURAY_PLAYER = 0,
   DEVICE_TYPE_SELECT_CABLE_BOX,
   DEVICE_TYPE_SELECT_COMPUTER,
   DEVICE_TYPE_SELECT_DVD_PLAYER,
   DEVICE_TYPE_SELECT_DVR,
   DEVICE_TYPE_SELECT_GAME,
   DEVICE_TYPE_SELECT_SATELLITE,
   DEVICE_TYPE_SELECT_VCR
}TV_DEVICE_NAME_INPUT_TYPE;

/* Enum the box of the select box */
typedef enum _WZD_SELECT_BOX_BTN_INDEX_T
{
    WZD_BOX_BTN_01 = 0,
    WZD_BOX_BTN_02,
    WZD_BOX_BTN_03,
    WZD_BOX_BTN_04,
    WZD_BOX_BTN_05,
    WZD_BOX_BTN_06,
    WZD_BOX_BTN_07,
    WZD_BOX_BTN_08,
    WZD_BOX_BTN_COUNT  /* 10 */
}WZD_SELECT_BOX_BTN_INDEX_T;

typedef enum {
    WZD_NAME_INPUT_CALLBACK_PARAM_NOTHING = 0,
    WZD_NAME_INPUT_CALLBACK_PARAM_FIRST,
    WZD_NAME_INPUT_CALLBACK_PARAM_SECOND,
} WZD_NAME_INPUT_CALLBACK_PARAM;


typedef struct _WZD_CHOOSE_BTN_T
{
    HANDLE_T            h_cb_btn_frm;
    HANDLE_T            h_cb_icon_1;
    HANDLE_T            h_cb_icon_2;
    HANDLE_T            h_cb_text;  
}WZD_CHOOSE_BTN_T;

typedef struct _WZD_DLG_PAGE_T
{
    HANDLE_T            h_dlg_frm;
    HANDLE_T            h_dlg_icon;
    HANDLE_T            h_dlg_text; 
    HANDLE_T            h_dlg_timer;
	HANDLE_T			h_amp_plug_dlg_timer;
}WZD_DLG_PAGE_T;

typedef struct _WZD_INPUT_PAGE_T
{
    HANDLE_T            h_input_desc_txt;
    HANDLE_T            h_show_dlg_timer;

}WZD_INPUT_PAGE_T;

typedef struct _WZD_SELECT_PAGE_T
{
    HANDLE_T                      h_select_frm; 
    HANDLE_T                      h_select_desc_txt;
    WZD_CHOOSE_BTN_T              t_sel_box_btn[WZD_BOX_BTN_COUNT];
}WZD_SELECT_PAGE_T;

typedef struct _WZD_TV_DEVICE_NAME_INPUT_MEMBER_T
{  
    UINT32                      ui4_sel_box_idx;
    BOOL                        b_is_named[WZD_DEVICE_NAME_INPUT_INPUT_NUM][WZD_BOX_BTN_COUNT];
    UINT32                      ui4_type_named_count[WZD_BOX_BTN_COUNT];

    /* dev type info */
    UINT32                      ui4_type_sel_idx;
    UINT32                      ui4_type_num;
    
    /* input src info */
    UINT8                       ui1_sel_src_idx;      /* Select source idx */
    UINT8                       aui1_input_src_id[WZD_DEVICE_NAME_INPUT_INPUT_SRC_NUM];

    NAME_INPUT_ENTER_REASON     e_name_input_enter_reason;
    TV_DEVICE_NAME_INPUT_STATE  e_state;
	UINT8						ui1_sel_box_num;
    BOOL                        b_show_checkbox;
    UINT8                       ui1_input_sel_box_idx;
} WZD_TV_DEVICE_NAME_INPUT_MEMBER_T;

typedef struct _WZD_NAME_INPUT_ANIM_COND_CB_DATA_T
{
    HANDLE_T                            h_anim_handle;                  /* the animation handle which callback to AP */
    WZD_NAME_INPUT_CALLBACK_PARAM       e_param;                        /* private tag data */
} WZD_NAME_INPUT_ANIM_COND_CB_DATA_T;

/* device setup diloge frame size */
#define WZD_SCREEN_DLG_FRM_X                 ((BASE_FRM_W - WZD_SCREEN_DLG_FRM_W) / 2)
#define WZD_SCREEN_DLG_FRM_Y                 (((BASE_FRM_H - WZD_SCREEN_DLG_FRM_H ) / 2) - (110 * WZD_UI_RATIO_W))
#define WZD_SCREEN_DLG_FRM_W                 (580 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_FRM_H                 (240 * WZD_UI_RATIO_W)

/* device setup diloge icon size */
#define WZD_SCREEN_DLG_ICON_X                ((WZD_SCREEN_DLG_FRM_W / 2) - (20 * WZD_UI_RATIO_W))
#define WZD_SCREEN_DLG_ICON_Y                (75 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_ICON_W                (40 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_ICON_H                (40 * WZD_UI_RATIO_W)

/* device setup diloge text size */
#define WZD_SCREEN_DLG_TEXT_X                (0)
#define WZD_SCREEN_DLG_TEXT_Y                (WZD_SCREEN_DLG_ICON_Y + WZD_SCREEN_DLG_ICON_H + 10 * WZD_UI_RATIO_W)
#define WZD_SCREEN_DLG_TEXT_W                (WZD_SCREEN_DLG_FRM_W)
#define WZD_SCREEN_DLG_TEXT_H                (100 * WZD_UI_RATIO_W)

/* select box frame. inside the layout frame */
#define WZD_CB_FRM_X                         (0)
#define WZD_CB_FRM_Y                         (10 * WZD_UI_RATIO_W)
#define WZD_CB_FRM_W                         (BASE_FRM_W - 2 * WZD_CB_FRM_X)
#define WZD_CB_FRM_H                         (640 * WZD_UI_RATIO_W)

#define WZD_BOX_BTN_GAP                      (-268 * WZD_UI_RATIO_W)

#define WZD_BOX_BTN_Y                        (0)
#define WZD_BOX_BTN_W                        (410 * WZD_UI_RATIO_W)
#define WZD_BOX_BTN_H                        (386 * WZD_UI_RATIO_W)

/* select box buttons */
#define WZD_BOX_BTN_MARGINS                  ((WZD_CB_FRM_W - 4 * WZD_BOX_BTN_W - 3 * WZD_BOX_BTN_GAP)/2) 
#define WZD_BOX_BTN_01_X                     (WZD_BOX_BTN_MARGINS)
#define WZD_BOX_BTN_02_X                     (WZD_BOX_BTN_01_X + WZD_BOX_BTN_W + WZD_BOX_BTN_GAP)
#define WZD_BOX_BTN_03_X                     (WZD_BOX_BTN_02_X + WZD_BOX_BTN_W + WZD_BOX_BTN_GAP)
#define WZD_BOX_BTN_04_X                     (WZD_BOX_BTN_03_X + WZD_BOX_BTN_W + WZD_BOX_BTN_GAP)
#define WZD_BOX_BTN_05_X                     (WZD_BOX_BTN_MARGINS)
#define WZD_BOX_BTN_06_X                     (WZD_BOX_BTN_01_X + WZD_BOX_BTN_W + WZD_BOX_BTN_GAP)
#define WZD_BOX_BTN_07_X                     (WZD_BOX_BTN_02_X + WZD_BOX_BTN_W + WZD_BOX_BTN_GAP)
#define WZD_BOX_BTN_08_X                     (WZD_BOX_BTN_03_X + WZD_BOX_BTN_W + WZD_BOX_BTN_GAP)

#define WZD_BOX_BTN_LINE1_Y                  WZD_BOX_BTN_Y - 20 * WZD_UI_RATIO_W
#define WZD_BOX_BTN_LINE2_Y                  WZD_BOX_BTN_Y + WZD_BOX_BTN_H - 265 * WZD_UI_RATIO_W

/* select box buttons layout */
#define  WZD_BOX_BTN_GET_RECTS()                                                                                                     \
{                                                                                                                                           \
    {WZD_BOX_BTN_01_X, WZD_BOX_BTN_LINE1_Y, WZD_BOX_BTN_01_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE1_Y + WZD_BOX_BTN_H}, \
    {WZD_BOX_BTN_02_X, WZD_BOX_BTN_LINE1_Y, WZD_BOX_BTN_02_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE1_Y + WZD_BOX_BTN_H}, \
    {WZD_BOX_BTN_03_X, WZD_BOX_BTN_LINE1_Y, WZD_BOX_BTN_03_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE1_Y + WZD_BOX_BTN_H}, \
    {WZD_BOX_BTN_04_X, WZD_BOX_BTN_LINE1_Y, WZD_BOX_BTN_04_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE1_Y + WZD_BOX_BTN_H}, \
    {WZD_BOX_BTN_05_X, WZD_BOX_BTN_LINE2_Y, WZD_BOX_BTN_05_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE2_Y + WZD_BOX_BTN_H}, \
    {WZD_BOX_BTN_06_X, WZD_BOX_BTN_LINE2_Y, WZD_BOX_BTN_06_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE2_Y + WZD_BOX_BTN_H}, \
    {WZD_BOX_BTN_07_X, WZD_BOX_BTN_LINE2_Y, WZD_BOX_BTN_07_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE2_Y + WZD_BOX_BTN_H}, \
    {WZD_BOX_BTN_08_X, WZD_BOX_BTN_LINE2_Y, WZD_BOX_BTN_08_X + WZD_BOX_BTN_W, WZD_BOX_BTN_LINE2_Y + WZD_BOX_BTN_H}, \
}

/* for move animation */
#define WZD_SEL_BOX_BTN_ICON_2_MOVE_DOWN_X        WZD_SEL_BOX_BTN_ICON_2_X - 5  * WZD_UI_RATIO_W
#define WZD_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y        WZD_SEL_BOX_BTN_ICON_2_Y + 20 * WZD_UI_RATIO_W
#define WZD_SEL_BOX_BTN_TXT_MOVE_DOWN_X           WZD_SEL_BOX_BTN_TXT_X
#define WZD_SEL_BOX_BTN_TXT_MOVE_DOWN_Y           WZD_SEL_BOX_BTN_TXT_Y - 40 * WZD_UI_RATIO_W + 20 * WZD_UI_RATIO_W

static WZD_TV_DEVICE_NAME_INPUT_MEMBER_T     t_g_tv_name_input;
static WZD_DLG_PAGE_T                        t_g_name_input_dlg_page;
static WZD_SELECT_PAGE_T                     t_g_name_input_select_type_page;
static WZD_INPUT_PAGE_T                      t_g_name_input_select_srouce_page;
static UINT32                                ui4_g_pre_focused_sb_idx = 0;

//static WZD_ANIM_COND_CB_DATA_T               at_anim_cb_data[WZD_TV_NAME_INPUT_ANIM_COND_CB_DATA_MAX_NUM];
static WZD_NAME_INPUT_ANIM_COND_CB_DATA_T      at_anim_cb_icon_data;
static WZD_NAME_INPUT_ANIM_COND_CB_DATA_T      at_anim_cb_txt_data;


/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_update_by_state(VOID);
static INT32 _wzd_page_tv_name_input_set_page_text(HANDLE_T h_parent, UTF16_T* pw2s_text);
static INT32 _wzd_page_tv_name_input_init(VOID);
static INT32 _wzd_page_tv_name_input_dlg_show(VOID);
static VOID _wzd_page_tv_name_input_finished_btn_dlg_show_nfy_fct(HANDLE_T  h_timer,
                                                                  VOID*     pv_tag);
static VOID _wzd_page_tv_name_input_timer_show_dialog_nfy_fct(HANDLE_T  h_timer,
                                                              VOID*     pv_tag);
static INT32 _wzd_page_tv_name_input_device_named_info (VOID);


#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
static VOID _wzd_page_tv_name_input_amp_plug_dlg_show_nfy_fct(HANDLE_T	h_timer,
																		   VOID*	 pv_tag);
#endif
#endif
#endif

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_sel_box_move_cond_cb_handler
 *
 * Description: update the state after the animiation is end
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_sel_box_move_cond_cb_handler(
    VOID*               pv_data,
    SIZE_T              z_data_size)
{
    WZD_NAME_INPUT_ANIM_COND_CB_DATA_T*            pt_anim_cb_data = NULL;
    WZD_NAME_INPUT_CALLBACK_PARAM                  param = WZD_NAME_INPUT_CALLBACK_PARAM_NOTHING;
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*             pt_this = &t_g_tv_name_input;
    WZD_INPUT_PAGE_T*                              pt_input_page = &t_g_name_input_select_srouce_page;

    do
    {
        /* Check input arguments */
        if ((NULL == pv_data) ||
            (z_data_size != sizeof(WZD_NAME_INPUT_ANIM_COND_CB_DATA_T)))
        {
            break;
        }

        pt_anim_cb_data = (WZD_NAME_INPUT_ANIM_COND_CB_DATA_T*)pv_data;

        if (NULL_HANDLE == pt_anim_cb_data->h_anim_handle)
        {
            break;
        }

        param = pt_anim_cb_data->e_param;
        
        c_wgl_set_alpha(pt_anim_cb_data->h_anim_handle, 255);

        /* Stop animation */
        if (WZD_NAME_INPUT_CALLBACK_PARAM_SECOND == param)
        {
            c_thread_delay(200);
            
            if (((DEVICE_TYPE_SELECT_CABLE_BOX == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE == pt_this->ui4_type_sel_idx)) && 
                (pt_this->ui1_sel_src_idx == (pt_this->ui1_sel_box_num-1)))
            {
                wzd_page_tv_setup_enter_from_tv_name_input_rf(pt_this->ui4_type_sel_idx);
            }
            else 
            {
                /* lose focus for the sel box when display the dialog */
                wzd_view_sel_box_lose_focus(pt_this->ui1_input_sel_box_idx, FALSE);
                
                wzd_view_full_screen_dlg_show(FALSE);
                
                c_timer_start(pt_input_page->h_show_dlg_timer, 
                              5000,
                              X_TIMER_FLAG_ONCE,
                              _wzd_page_tv_name_input_timer_show_dialog_nfy_fct,
                              NULL);
            }
            
        }
        else
        {
            /* do nothing */
        }

        a_wzd_anim_end(pt_anim_cb_data->h_anim_handle);
        
        /* clean data */
        if (pt_anim_cb_data->h_anim_handle == at_anim_cb_icon_data.h_anim_handle)
        {
            at_anim_cb_icon_data.h_anim_handle = NULL_HANDLE;
            at_anim_cb_icon_data.e_param = WZD_NAME_INPUT_CALLBACK_PARAM_NOTHING;
        }
        else if (pt_anim_cb_data->h_anim_handle == at_anim_cb_txt_data.h_anim_handle)
        {
            at_anim_cb_txt_data.h_anim_handle = NULL_HANDLE;
            at_anim_cb_txt_data.e_param = WZD_NAME_INPUT_CALLBACK_PARAM_NOTHING;
        }
        
    } while(0);
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_sel_box_move_cb_fct
 *
 * Description: for select signal type and cable device type
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_sel_box_move_cb_fct(
    HANDLE_T            h_widget,
    UINT16              ui2_anim_type,
    WGL_ANIM_COND_INF_T t_anim_cond_inf,
    VOID*               pv_tag)
{
    if (h_widget == NULL_HANDLE)
    {
        return WZDR_OK;
    }
    
    if (_ANIM_TOTAL_END(&t_anim_cond_inf))
    {
        DBG_INFO( ("[WZD_NAME_INPUT] ANIM_TOTAL_END Line@%d.\n", __LINE__));

        /* Async invoke callback handler function */        
        wzd_async_invoke(
                _wzd_page_tv_name_input_sel_box_move_cond_cb_handler, 
                pv_tag, 
                sizeof(WZD_NAME_INPUT_ANIM_COND_CB_DATA_T), 
                FALSE);
    }

    return WZDR_OK;   
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_page_set_checkmark
 *
 * Description: set checkmark(icon1) and move icon2 and text
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_page_set_checkmark (VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;
    WGL_IMG_INFO_T 					    t_img_info = {0};
    GL_RECT_T      					    t_rect = {0};
	WGL_HIMG_TPL_T 					    h_checkmark_icon = NULL_HANDLE;
    ANIM_DATA_MOVE_T                    t_anim_data_icon;
    ANIM_DATA_MOVE_T                    t_anim_data_txt;
    HANDLE_T       					    h_icon1 = NULL_HANDLE;
    HANDLE_T       					    h_icon2 = NULL_HANDLE;
	HANDLE_T    					    h_text = NULL_HANDLE;

    c_memset(&t_anim_data_icon, 0, sizeof(ANIM_DATA_MOVE_T));
    c_memset(&t_anim_data_txt, 0, sizeof(ANIM_DATA_MOVE_T));

    h_checkmark_icon = h_g_wzd_img_checkmark_green_large;

    /* move icon position */
    h_icon1 = wzd_view_sel_box_get_icon_1_handle(pt_this->ui1_input_sel_box_idx);

    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                      WGL_CMD_ICON_SET_ALIGN,
                      WGL_PACK(WGL_AS_CENTER_CENTER),
                      NULL));

	SET_RECT_BY_SIZE (&t_rect,
                      WZD_SEL_BOX_BTN_ICON_1_X,
                      WZD_SEL_BOX_BTN_ICON_1_Y  + 40 * WZD_UI_RATIO_W,
                      WZD_SEL_BOX_BTN_ICON_1_W  + 20 * WZD_UI_RATIO_W,
                      WZD_SEL_BOX_BTN_ICON_1_H);

    RET_ON_ERR (c_wgl_move(h_icon1,
                      &t_rect,
                      WGL_NO_AUTO_REPAINT));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                      WGL_CMD_GL_SET_IMAGE,
                      WGL_PACK(WGL_IMG_FG),
                      WGL_PACK(&t_img_info)));
    
    RET_ON_ERR (c_wgl_set_visibility (h_icon1, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_repaint (h_icon1, NULL, TRUE));

    /* start icon2 move animation */
    h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_input_sel_box_idx);

    t_anim_data_icon.ui2_total_steps = 6;
    t_anim_data_icon.ui2_frame_interval = 50;

    t_anim_data_icon.i2_start_x = WZD_SEL_BOX_BTN_ICON_2_X - 5 * WZD_UI_RATIO_W;
    t_anim_data_icon.i2_start_y = WZD_SEL_BOX_BTN_ICON_2_Y;
    t_anim_data_icon.i2_end_x   = WZD_SEL_BOX_BTN_ICON_2_MOVE_DOWN_X;
    t_anim_data_icon.i2_end_y   = WZD_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y;

    
    /* set h_icon2 move down callback data */
    c_memset(&at_anim_cb_icon_data, 0, sizeof(WZD_NAME_INPUT_ANIM_COND_CB_DATA_T));
    at_anim_cb_icon_data.h_anim_handle = h_icon2;
    at_anim_cb_icon_data.e_param = WZD_NAME_INPUT_CALLBACK_PARAM_FIRST;

    a_wzd_anim_set_cb(
               h_icon2,
               _wzd_page_tv_name_input_sel_box_move_cb_fct,
               (void *)&at_anim_cb_icon_data);

    a_wzd_anim_move_ex(h_icon2, &t_anim_data_icon, TRUE);

    /* start text move animation */
    h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_input_sel_box_idx);

    t_anim_data_txt.ui2_total_steps = 6;
    t_anim_data_txt.ui2_frame_interval = 50;

    t_anim_data_txt.i2_start_x = WZD_SEL_BOX_BTN_TXT_X;
    t_anim_data_txt.i2_start_y = WZD_SEL_BOX_BTN_TXT_Y - 40 * WZD_UI_RATIO_W ;
    t_anim_data_txt.i2_end_x   = WZD_SEL_BOX_BTN_TXT_MOVE_DOWN_X;
    t_anim_data_txt.i2_end_y   = WZD_SEL_BOX_BTN_TXT_MOVE_DOWN_Y;

    /* set h_text move down callback data */
    c_memset(&at_anim_cb_txt_data, 0, sizeof(WZD_NAME_INPUT_ANIM_COND_CB_DATA_T));
    at_anim_cb_txt_data.h_anim_handle = h_text;
    at_anim_cb_txt_data.e_param = WZD_NAME_INPUT_CALLBACK_PARAM_SECOND;

    /* set h_text move down callback */
    a_wzd_anim_set_cb(
               h_text,
               _wzd_page_tv_name_input_sel_box_move_cb_fct,
               (void *)&at_anim_cb_txt_data);

    a_wzd_anim_move_ex(h_text, &t_anim_data_txt, TRUE);

    return WZDR_OK;;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_page_update_checkmark
 *
 * Description: update the position of checkmark(icon1)/icon2/txt on the select box
 *              when get the focus.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_page_update_checkmark(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;
    WGL_IMG_INFO_T 					    t_img_info = {0};
    GL_RECT_T      					    t_rect_icon = {0};
    GL_RECT_T      					    t_rect_txt = {0};
	WGL_HIMG_TPL_T 					    h_checkmark_icon = NULL_HANDLE;
    HANDLE_T       					    h_icon1 = NULL_HANDLE;
    HANDLE_T       					    h_icon2 = NULL_HANDLE;
	HANDLE_T    					    h_text = NULL_HANDLE;
    BOOL         					    b_sel_status = FALSE;
    BOOL         					    b_sel_curr_same = FALSE;
    UINT8                               ui1_sel_box_idx = 0;
    INT32                               i4_ret = WZDR_OK;
    UINT8                               ui1_type_id = 0;
    
    if (!pt_this->b_show_checkbox)
    {
        return 0;
    }

    for (ui1_sel_box_idx = 0; ui1_sel_box_idx < WZD_BOX_BTN_COUNT; ui1_sel_box_idx++)
    {
        h_icon1 = wzd_view_sel_box_get_icon_1_handle(ui1_sel_box_idx);
        
        for (ui1_type_id = DEVICE_TYPE_SELECT_BLURAY_PLAYER; ui1_type_id <= DEVICE_TYPE_SELECT_VCR; ui1_type_id++)
        {
            if (pt_this->b_is_named[ui1_sel_box_idx][ui1_type_id])
            {
                b_sel_status = TRUE;
                if (pt_this->ui1_input_sel_box_idx == ui1_sel_box_idx)
                {
                    b_sel_curr_same = TRUE;
                    break;
                }
            }
        }
        if(b_sel_curr_same)
        {
            break;
        }
    }

    if (b_sel_status)
    {
        if (b_sel_curr_same)
        {  
            h_checkmark_icon = h_g_wzd_img_checkmark_green_large;
        }
        else
        {
            pt_this->b_show_checkbox = FALSE;
            h_checkmark_icon = NULL_HANDLE;
        }
    }
    else
    {
        pt_this->b_show_checkbox = FALSE;
        pt_this->ui1_input_sel_box_idx = 0;
        h_checkmark_icon = NULL_HANDLE;
    }

    /*update sel box icon2 and text position */
    if (b_sel_status)
    {
        if (pt_this->b_show_checkbox)
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_icon,
                                WZD_SEL_BOX_BTN_ICON_2_X - 5 * WZD_UI_RATIO_W,
                                WZD_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y,
                                WZD_SEL_BOX_BTN_ICON_2_W + 20 * WZD_UI_RATIO_W,
                                WZD_SEL_BOX_BTN_ICON_2_H);
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_SEL_BOX_BTN_TXT_X,
                             WZD_SEL_BOX_BTN_TXT_MOVE_DOWN_Y,
                             WZD_SEL_BOX_BTN_TXT_W,
                             WZD_SEL_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        else
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_icon,
                            WZD_SEL_BOX_BTN_ICON_2_X - 5 * WZD_UI_RATIO_W,
                            WZD_SEL_BOX_BTN_ICON_2_Y,
                            WZD_SEL_BOX_BTN_ICON_2_W + 20 * WZD_UI_RATIO_W,
                            WZD_SEL_BOX_BTN_ICON_2_H);
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_input_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_SEL_BOX_BTN_TXT_X,
                             WZD_SEL_BOX_BTN_TXT_Y - (40 * WZD_UI_RATIO_W),
                             WZD_SEL_BOX_BTN_TXT_W,
                             WZD_SEL_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        
    }

    /* update checkmark icon position*/ 
    if (pt_this->b_show_checkbox)
    {
        h_icon1 = wzd_view_sel_box_get_icon_1_handle(pt_this->ui1_input_sel_box_idx);
        SET_RECT_BY_SIZE(&t_rect_icon,
                        WZD_SEL_BOX_BTN_ICON_1_X,
                        WZD_SEL_BOX_BTN_ICON_1_Y  + 40 * WZD_UI_RATIO_W,
                        WZD_SEL_BOX_BTN_ICON_1_W  + 20 * WZD_UI_RATIO_W,
                        WZD_SEL_BOX_BTN_ICON_1_H);
    
        RET_ON_ERR (c_wgl_move(h_icon1,
                           &t_rect_icon,
                           WGL_NO_AUTO_REPAINT));
    
    }
    
    RET_ON_ERR (c_wgl_do_cmd(h_icon1,
                  WGL_CMD_ICON_SET_ALIGN,
                  WGL_PACK(WGL_AS_CENTER_CENTER),
                  NULL));
    
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    i4_ret = c_wgl_do_cmd(h_icon1,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_FG),
                           WGL_PACK(&t_img_info));                 
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_dlg_icon_create
 *
 * Description: This function creates the dialog icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_finished_dlg_icon_create (VOID)
{
    GL_RECT_T           t_rect = {0};
    INT32               i4_ret;
    WGL_INSET_T         t_inset;
    WZD_DLG_PAGE_T*     pt_dlg_page = &t_g_name_input_dlg_page;
    
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_SCREEN_DLG_ICON_X,
                      WZD_SCREEN_DLG_ICON_Y,
                      WZD_SCREEN_DLG_ICON_W,
                      WZD_SCREEN_DLG_ICON_H);

    i4_ret = c_wgl_create_widget(pt_dlg_page->h_dlg_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &pt_dlg_page->h_dlg_icon);

    RET_ON_ERR (i4_ret);

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_icon,
                              WGL_CMD_ICON_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(pt_dlg_page->h_dlg_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_BOTTOM,
                          NULL);
    RET_ON_ERR (i4_ret);

    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (pt_dlg_page->h_dlg_icon, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_dlg_text_create
 *
 * Description: This function creates the full screen dialog text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_finished_dlg_text_create(VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    CHAR*                       s_font_name = wzd_view_get_font_name();
    WZD_DLG_PAGE_T*             pt_dlg_page = &t_g_name_input_dlg_page;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_SCREEN_DLG_TEXT_X,
                      WZD_SCREEN_DLG_TEXT_Y,
                      WZD_SCREEN_DLG_TEXT_W,
                      WZD_SCREEN_DLG_TEXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (pt_dlg_page->h_dlg_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_512  |
                                             WGL_STL_TEXT_MAX_DIS_5_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     &pt_dlg_page->h_dlg_text));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_text,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_text,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_text,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_CENTER_TOP),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_text,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt);

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_text,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_dlg_page->h_dlg_text, WGL_SW_HIDE));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name:  _wzd_page_tv_name_input_dlg_create
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
static INT32 _wzd_page_tv_name_input_dlg_create (HANDLE_T parent)
{
    WZD_DLG_PAGE_T*     pt_dlg_page = &t_g_name_input_dlg_page;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_info;
    INT32               i4_ret = WZDR_OK;
    
    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_SCREEN_DLG_FRM_X,
                      WZD_SCREEN_DLG_FRM_Y,
                      WZD_SCREEN_DLG_FRM_W,
                      WZD_SCREEN_DLG_FRM_H);
  
    /* create widget */
    i4_ret = c_wgl_create_widget (parent,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  NULL,
                                  240,
                                  (VOID*) WZD_WIDGET_STYLE,
                                  0,
                                  &pt_dlg_page->h_dlg_frm);
    RET_ON_ERR(i4_ret);
    
    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_dialog;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_dialog;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dialog;

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK),
                              WGL_PACK (& t_img_info)));

    /* create icon */
    RET_ON_ERR (_wzd_page_tv_name_input_finished_dlg_icon_create());

    /* create text */
    RET_ON_ERR (_wzd_page_tv_name_input_finished_dlg_text_create());
	
    /* create dlg show timer */
    RET_ON_ERR (c_timer_create(&pt_dlg_page->h_dlg_timer));
	
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
	 /* create amp plug dlg show timer */
    RET_ON_ERR (c_timer_create(&pt_dlg_page->h_amp_plug_dlg_timer));
#endif
#endif
#endif


    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_dlg_page->h_dlg_frm, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_dlg_set_icon
 *
 * Description: The function set image template to the finished dialog icon.
 *
 *
 *
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_finished_dlg_set_icon (WGL_HIMG_TPL_T h_dlg_icon)
{
    WGL_IMG_INFO_T      t_img_info;
    WZD_DLG_PAGE_T*     pt_dlg_page = &t_g_name_input_dlg_page;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_dlg_icon;
    t_img_info.u_img_data.t_standard.t_disable = h_dlg_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_dlg_icon;
    RET_ON_ERR (c_wgl_do_cmd(pt_dlg_page->h_dlg_icon,
                            WGL_CMD_GL_SET_IMAGE,
                            (VOID*)WGL_IMG_FG,
                            (VOID*)&t_img_info));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_dlg_set_text
 *
 * Description: The function set the full screen dialog text.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_finished_dlg_set_text (UTF16_T* pw2s_text)
{
    WZD_DLG_PAGE_T*     pt_dlg_page = &t_g_name_input_dlg_page;

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_page->h_dlg_text,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (pw2s_text),
                      WGL_PACK ((UINT16)0xFFFF)));
    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_dlg_show
 *
 * Description: 
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_finished_dlg_show (VOID)
{
    WZD_DLG_PAGE_T* pt_dlg_page = &t_g_name_input_dlg_page;
    
    RET_ON_ERR (c_wgl_set_visibility (pt_dlg_page->h_dlg_icon, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_set_visibility (pt_dlg_page->h_dlg_text, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_set_visibility (pt_dlg_page->h_dlg_frm, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_insert (pt_dlg_page->h_dlg_frm,
                              NULL_HANDLE,
                              WGL_INSERT_TOPMOST,
                              WGL_NO_AUTO_REPAINT));
                              
    RET_ON_ERR (_wzd_page_tv_name_input_init());                       

    RET_ON_ERR (c_wgl_set_focus(pt_dlg_page->h_dlg_frm, FALSE));
    
    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_dlg_hide
 *
 * Description: The function hide the full screen dialog.
 *
 * Inputs: 
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_finished_dlg_hide (VOID)
{
    WZD_DLG_PAGE_T*     pt_dlg_page = &t_g_name_input_dlg_page;

    return c_wgl_set_visibility (pt_dlg_page->h_dlg_frm, WGL_SW_HIDE);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_init
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_init(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;

    c_memset(pt_this->aui1_input_src_id, 0, WZD_DEVICE_NAME_INPUT_INPUT_SRC_NUM);
    
    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_change_input
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
static INT32 _wzd_page_tv_name_input_change_input(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;
    UINT8  ui1_idx = 0;
    
    if (pt_this->ui1_sel_src_idx > (WZD_DEVICE_NAME_INPUT_INPUT_SRC_NUM - 1) ) /*Klocwork*/
    {
        return WZDR_OK;
    }

    ui1_idx = pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx];

    if (ui1_idx == (UINT8) - 1 || ui1_idx >= 16)
    {
        return WZDR_FAIL;
    }
    
    RET_ON_ERR(a_tv_change_input_src(wzd_get_crnt_svctx(),
                                     SVCTX_STRM_MODE_AS_LAST,
                                     ui1_idx,
                                     NULL));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_set_device_info
 *
 * Description: 
 *
 * Inputs:  - 
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_set_device_info(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;
    CHAR	s_str[WZD_DEVICE_NAME_INPUT_TYPE_LEN] = {0};
    
    INT32 i4_ret = WZDR_OK;

	c_memset(s_str, 0, WZD_DEVICE_NAME_INPUT_TYPE_LEN);
    if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_CABLE_BOX)
    {
	    c_uc_w2s_to_ps(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_CABLE_BOX), s_str, WZD_DEVICE_NAME_INPUT_TYPE_LEN);
    }
    else if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SATELLITE)
    {
	    c_uc_w2s_to_ps(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_SATELLITE), s_str, WZD_DEVICE_NAME_INPUT_TYPE_LEN);
    }
	a_cfg_custom_set_device_type(pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx],s_str);
    i4_ret = a_cfg_custom_set_inp_name(pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx], s_str);
    DBG_INFO( ("\n[%s(%d)] i4_ret = %d,pt_this->ui1_sel_src_idx=%d,s_str=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->ui1_sel_src_idx,s_str));

    if (i4_ret != WZDR_OK)
    {
        DBG_INFO( ("[Ln: %d] a_cfg_custom_set_inp_name(). i4_ret = %d\n", __LINE__,i4_ret));
        return WZDR_FAIL;      
    }

    _wzd_page_tv_name_input_device_named_info();

    return WZDR_OK;        
} 

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_choose_box_btns_set_all_unfloat
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_choose_box_btns_set_all_unfloat(VOID)
{
    INT32 index = 0;
    WZD_SELECT_PAGE_T* pt_select_page = &t_g_name_input_select_type_page;
   
    for (index = 0; index < WZD_BOX_BTN_COUNT; index++)
    {
        RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[index].h_cb_btn_frm, FALSE, FALSE)); 
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial
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
static INT32 _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*   pt_this = &t_g_tv_name_input;
    WZD_SELECT_PAGE_T*                   pt_select_page = &t_g_name_input_select_type_page;
    HANDLE_T                             h_txt_handle = NULL_HANDLE; 
    WGL_COLOR_INFO_T                     t_color_txt;
    WGL_FONT_INFO_T                      t_fnt_info;

    h_txt_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_text;

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

    /* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));
    
    RET_ON_ERR (c_wgl_enable(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_2, FALSE));
                                              
    return WZDR_OK;                      
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_hlt
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
static INT32 _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_hlt(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;
    WZD_SELECT_PAGE_T*                 pt_select_page = &t_g_name_input_select_type_page;
    HANDLE_T                           h_txt_handle = NULL_HANDLE; 
    WGL_COLOR_INFO_T                   t_color_txt; 

    h_txt_handle = pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_text;

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));
                              
    RET_ON_ERR (c_wgl_enable(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_icon_2, TRUE));

    return WZDR_OK;   
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_inp_page_set_losed_foucs_box_txt_initial
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
static INT32 _wzd_page_tv_name_input_inp_page_set_losed_foucs_box_txt_initial(UINT32 ui4_idx)
{
    HANDLE_T                             h_txt_handle = NULL_HANDLE; 
    HANDLE_T                             h_sb_icon1   = NULL_HANDLE;
    HANDLE_T                             h_sb_icon2   = NULL_HANDLE;
    WGL_COLOR_INFO_T                     t_color_txt;
    WGL_FONT_INFO_T                      t_fnt_info;
    WGL_IMG_INFO_T                       t_img_info;
    HANDLE_T                             h_checkmark_icon = NULL_HANDLE; 
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*   pt_this = &t_g_tv_name_input;
    GL_RECT_T                    		 t_rect = {0};

    h_txt_handle = wzd_view_sel_box_get_txt_handle(ui4_idx);

    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

    /* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));
    /* move position */
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_SEL_BOX_BTN_TXT_X,
                     WZD_SEL_BOX_BTN_TXT_Y - (40 * WZD_UI_RATIO_W),
                     WZD_SEL_BOX_BTN_TXT_W,
                     WZD_SEL_BOX_BTN_TXT_H);
    
    RET_ON_ERR (c_wgl_move(h_txt_handle,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));
                   
    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                    WGL_CMD_TEXT_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL));  

    /* update icon 1 */
    h_sb_icon1 = wzd_view_sel_box_get_icon_1_handle(ui4_idx);
    
    /* h_checkmark_icon = NULL_HANDLE */
    pt_this->b_show_checkbox = FALSE;
    
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;

    c_wgl_do_cmd(h_sb_icon1,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_FG),
                 WGL_PACK(&t_img_info)); 
                             
    /* update icon2 */
    h_sb_icon2 = wzd_view_sel_box_get_icon_2_handle(ui4_idx);  

    /* icon2 move position */
    SET_RECT_BY_SIZE (& t_rect,
                  WZD_SEL_BOX_BTN_ICON_2_X - 5 * WZD_UI_RATIO_W,
                  WZD_SEL_BOX_BTN_ICON_2_Y,
                  WZD_SEL_BOX_BTN_ICON_2_W + 20 * WZD_UI_RATIO_W,
                  WZD_SEL_BOX_BTN_ICON_2_H);
                  
    RET_ON_ERR (c_wgl_move(h_sb_icon2,
                           &t_rect,
                           WGL_NO_AUTO_REPAINT));
    
    RET_ON_ERR (c_wgl_do_cmd(h_sb_icon2,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL));
    
    RET_ON_ERR (c_wgl_enable(h_sb_icon2, FALSE));  
    
    return WZDR_OK;                      
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_inp_page_set_foucsed_box_txt_hlt
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
static INT32 _wzd_page_tv_name_input_inp_page_set_foucsed_box_txt_hlt(UINT32 ui4_idx)
{
    HANDLE_T                             h_txt_handle = NULL_HANDLE;
    HANDLE_T                             h_sb_icon2   = NULL_HANDLE;
    WGL_COLOR_INFO_T                     t_color_txt;
    WGL_FONT_INFO_T                      t_fnt_info;

    h_txt_handle = wzd_view_sel_box_get_txt_handle(ui4_idx);
    
    /* update color */
    c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
    t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
    COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (&t_color_txt)));

    /* update font size */
    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
    RET_ON_ERR (c_wgl_do_cmd (h_txt_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));
    /* update icon2 */
    h_sb_icon2 = wzd_view_sel_box_get_icon_2_handle(ui4_idx);                          
    RET_ON_ERR (c_wgl_enable(h_sb_icon2, TRUE));    
    
    return WZDR_OK;                     
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_choose_box_btn_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_choose_box_btn_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;
    WZD_SELECT_PAGE_T* pt_select_page = &t_g_name_input_select_type_page;
    
    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
            case BTN_SELECT:   
                _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial();
                pt_this->ui4_type_sel_idx = pt_this->ui4_sel_box_idx;
                pt_this->e_state = TV_DEVICE_NAME_INPUT_SRC_SELECT;
                _wzd_page_tv_name_input_update_by_state();
                
                break;

            case BTN_CURSOR_UP:
                if (pt_this->ui4_sel_box_idx >= WZD_BOX_BTN_05 && pt_this->ui4_sel_box_idx <= WZD_BOX_BTN_08) 
                {                 
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial();
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx - 4;
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_hlt();
                    RET_ON_ERR (c_wgl_set_focus(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, WGL_NO_AUTO_REPAINT));
                    RET_ON_ERR (_wzd_page_tv_name_input_choose_box_btns_set_all_unfloat());
                    RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE)); 
                } 
                wzd_view_main_frm_repaint();
                
                break;

            case BTN_CURSOR_DOWN:
                if (pt_this->ui4_sel_box_idx >= WZD_BOX_BTN_01 && pt_this->ui4_sel_box_idx <= WZD_BOX_BTN_04) 
                {
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial();
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx + 4;
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_hlt();
                    RET_ON_ERR (c_wgl_set_focus(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, WGL_NO_AUTO_REPAINT));   
                } 
                else
                {
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial();
                    RET_ON_ERR (wzd_view_footer_set_focus (WZD_FOOTER_BTN_01, TRUE));
                }
                RET_ON_ERR (_wzd_page_tv_name_input_choose_box_btns_set_all_unfloat());
                RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE));
                wzd_view_main_frm_repaint();
                
                break;
                
            case BTN_CURSOR_RIGHT:
                if (pt_this->ui4_sel_box_idx >= WZD_BOX_BTN_01 && pt_this->ui4_sel_box_idx <= WZD_BOX_BTN_07) 
                {
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial();
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx + 1;
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_hlt();                    
                    RET_ON_ERR (c_wgl_set_focus(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, WGL_NO_AUTO_REPAINT));     
                }
                RET_ON_ERR (_wzd_page_tv_name_input_choose_box_btns_set_all_unfloat());
                RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE));
                wzd_view_main_frm_repaint();

                break;
                
            case BTN_CURSOR_LEFT:
                if (pt_this->ui4_sel_box_idx >= WZD_BOX_BTN_02 && pt_this->ui4_sel_box_idx <= WZD_BOX_BTN_08) 
                {
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_initial();
                    pt_this->ui4_sel_box_idx = pt_this->ui4_sel_box_idx - 1;
                    _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_hlt();
                    RET_ON_ERR (c_wgl_set_focus(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, WGL_NO_AUTO_REPAINT)); 
                }
                RET_ON_ERR (_wzd_page_tv_name_input_choose_box_btns_set_all_unfloat());
                RET_ON_ERR (c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE));
                wzd_view_main_frm_repaint();
                
                break;
                
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
   
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_create_choose_box_frm
 *
 * Description: This function creates a choose box frame to display background
 *              image.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_create_choose_box_frm (HANDLE_T  h_parent)
                                              
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WZD_SELECT_PAGE_T*  pt_select_page = &t_g_name_input_select_type_page;
 

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_CB_FRM_X,
                      WZD_CB_FRM_Y,
                      WZD_CB_FRM_W,
                      WZD_CB_FRM_H);

    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     NULL,
                                     &pt_select_page->h_select_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_select_page->h_select_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (pt_select_page->h_select_frm, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_create_text
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
static INT32 _wzd_page_tv_name_input_create_text(
                           GL_RECT_T*               pt_rect,
                           HANDLE_T                 h_parent,
                           wgl_widget_proc_fct      pf_wdgt_proc,
                           UINT32                   ui4_style,
                           HANDLE_T*                ph_txt,
                           WGL_FONT_INFO_T*         pt_fnt_info,
                           UINT8                    ui1_align,
                           WGL_COLOR_INFO_T*        pt_color_bk,
                           WGL_COLOR_INFO_T*        pt_color_fg,
                           WGL_INSET_T*             pt_inset)
{
    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     pf_wdgt_proc,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     ph_txt));

    /* set font size */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (pt_fnt_info),
                              NULL));

    /* set content inset */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (pt_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (ui1_align),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (pt_color_bk)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (pt_color_fg)));    

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_txt, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_choose_box_create_icon
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
static INT32 _wzd_page_tv_name_input_choose_box_create_icon(HANDLE_T     h_parent,
                                              HANDLE_T*    ph_widget,
                                              GL_RECT_T*   pt_rect)
{   
    RET_ON_ERR (c_wgl_create_widget(h_parent,
                              HT_WGL_WIDGET_ICON,
                              WGL_CONTENT_ICON_DEF,
                              WGL_BORDER_NULL,
                              pt_rect,
                              NULL,
                              255,
                              (VOID*)WGL_STL_GL_NO_BK,
                              NULL,
                              ph_widget));

    RET_ON_ERR (c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_ICON_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL));

    RET_ON_ERR (c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_create_choose_box_button_widget
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_create_choose_box_button_widget(
                               HANDLE_T                h_parent,
                               const GL_RECT_T*        pt_rect,
                               wgl_widget_proc_fct     pf_wdgt_proc,
                               HANDLE_T*               ph_btn)
{
    INT32               i4_ret = WZDR_OK;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_info;

    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  pt_rect,
                                  pf_wdgt_proc,
                                  255,
                                  (VOID*) WZD_WIDGET_STYLE,
                                  NULL,
                                  ph_btn);
    RET_ON_ERR (i4_ret);                               

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_enable,    &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_disable,   &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_highlight, &t_g_wzd_color_base_frm_bk);

    i4_ret = c_wgl_do_cmd (h_parent,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK), /* background color */
                           WGL_PACK(&t_color_info));
                           
    RET_ON_ERR (i4_ret);
    
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

    i4_ret = c_wgl_do_cmd (*ph_btn,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK (WGL_IMG_BK), /* background image */
                           WGL_PACK (&t_img_info));
                           
    RET_ON_ERR (i4_ret);
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_create_choose_box_buttons
 *
 * Description: This function creates the select box buttons.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_create_choose_box_buttons(VOID)
{
    GL_RECT_T           at_btn_rect[WZD_BOX_BTN_COUNT] = WZD_BOX_BTN_GET_RECTS();
    UINT8               ui1_i = 0;
    UINT8               ui1_align = 0; 
    UINT32              ui4_style;
    INT32               i4_ret = WZDR_OK;
    WGL_INSET_T         t_inset;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_IMG_INFO_T      t_img_info;
    GL_RECT_T           t_rect_icon_1, t_rect_icon_2, t_rect_text;
    WGL_COLOR_INFO_T    t_color_info_bg, t_color_info_fg;
    CHAR*               s_font_name = wzd_view_get_font_name();
    WZD_SELECT_PAGE_T*  pt_select_page = &t_g_name_input_select_type_page;
                                                                       
    /* icon_1 rect */
    SET_RECT_BY_SIZE (& t_rect_icon_1,
                      -32 * WZD_UI_RATIO_W,
                      135 * WZD_UI_RATIO_W,
                      WZD_BOX_BTN_W + 78 * WZD_UI_RATIO_W,
                      40 * WZD_UI_RATIO_W);

    /* icon_2 rect */
    SET_RECT_BY_SIZE (& t_rect_icon_2,
                      -32 * WZD_UI_RATIO_W,
                      170 * WZD_UI_RATIO_W,
                      WZD_BOX_BTN_W + 70 * WZD_UI_RATIO_W,
                      40 * WZD_UI_RATIO_W);                    
    
    /* set text theme */
    SET_RECT_BY_SIZE (&t_rect_text,
                      33 * WZD_UI_RATIO_W,
                      190 * WZD_UI_RATIO_W,
                      343 * WZD_UI_RATIO_W,
                      80 * WZD_UI_RATIO_W);

    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_128  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;
    
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    /* create buttons */
    for( ui1_i = 0; ui1_i < WZD_BOX_BTN_COUNT ; ui1_i++ )
    { 
        i4_ret = _wzd_page_tv_name_input_create_choose_box_button_widget (pt_select_page->h_select_frm,
                                                                          &at_btn_rect[ui1_i],
                                                                          _wzd_page_tv_name_input_choose_box_btn_nfy_fct,
                                                                          &((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm));
        RET_ON_ERR (i4_ret);

        i4_ret = _wzd_page_tv_name_input_create_text(&t_rect_text,
                                                              (pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                                                              NULL,
                                                              ui4_style,
                                                              &(pt_select_page->t_sel_box_btn[ui1_i]).h_cb_text,
                                                              &t_fnt_info,
                                                              ui1_align,
                                                              &t_color_info_bg,
                                                              &t_color_info_fg,
                                                              &t_inset);
        RET_ON_ERR (i4_ret);

        /* icon_1 create */
        i4_ret = _wzd_page_tv_name_input_choose_box_create_icon((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                                                                 &(pt_select_page->t_sel_box_btn[ui1_i]).h_cb_icon_1,
                                                                 &t_rect_icon_1);   
        RET_ON_ERR (i4_ret);
                
        /* icon_2 create */
        i4_ret = _wzd_page_tv_name_input_choose_box_create_icon((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                                                                 &(pt_select_page->t_sel_box_btn[ui1_i]).h_cb_icon_2,
                                                                 &t_rect_icon_2);   
        RET_ON_ERR (i4_ret);
    }
    
    /* update background image */
    for ( ui1_i = WZD_BOX_BTN_05; ui1_i <= WZD_BOX_BTN_08 ; ui1_i++ )
    {

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_selectbox_small_1;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_selectbox_small_hlt;

        i4_ret = c_wgl_do_cmd ((pt_select_page->t_sel_box_btn[ui1_i]).h_cb_btn_frm,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_BK), /* background image */
                               WGL_PACK (&t_img_info));
                               
        RET_ON_ERR (i4_ret);
    }

    return WZDR_OK;
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_set_choose_box_buttons_content
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_set_choose_box_buttons_content (VOID)
{
    INT32               i4_ret = 0;
    UINT8               ui1_idx = 0;   
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_txt;
    WGL_FONT_INFO_T     t_fnt_info;
    WZD_SELECT_PAGE_T*  pt_select_page = &t_g_name_input_select_type_page;
    
    WGL_HIMG_TPL_T wzd_tv_device_name_input_img_choose[WZD_BOX_BTN_COUNT] =
                    {h_g_wzd_img_device_bluray,
                     h_g_wzd_img_device_cable,
                     h_g_wzd_img_device_computer,
                     h_g_wzd_img_device_dvd,
                     h_g_wzd_img_device_dvr,
                     h_g_wzd_img_device_game,
                     h_g_wzd_img_device_sat,
                     h_g_wzd_img_device_vcr,
                    };
                    
    WGL_HIMG_TPL_T wzd_tv_device_name_input_img_hlt_choose[WZD_BOX_BTN_COUNT] =
                    {h_g_wzd_img_device_bluray_hlt,
                     h_g_wzd_img_device_cable_hlt,
                     h_g_wzd_img_device_computer_hlt,
                     h_g_wzd_img_device_dvd_hlt,
                     h_g_wzd_img_device_dvr_hlt,
                     h_g_wzd_img_device_game_hlt,
                     h_g_wzd_img_device_sat_hlt,
                     h_g_wzd_img_device_vcr_hlt,
                    };

    UINT16 wzd_tv_device_name_input_type_mlm_text[WZD_BOX_BTN_COUNT] =   
                    {MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY,       
                     MLM_WZD_KEY_DEVICE_SETUP_TYPE_CABLE_BOX,      
                     MLM_WZD_KEY_DEVICE_SETUP_TYPE_COMPUTER,        
                     MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVD_PLAYER,      
                     MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVR,           
                     MLM_WZD_KEY_DEVICE_SETUP_TYPE_GAME,          
                     MLM_WZD_KEY_DEVICE_SETUP_TYPE_SATELLITE,     
                     MLM_WZD_KEY_DEVICE_SETUP_TYPE_VCR,                 
                    };
          
    for( ui1_idx = 0; ui1_idx < WZD_BOX_BTN_COUNT ; ui1_idx ++ )
    {
        /* set select box icon_1 */
        c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_checkmark_green_small;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_checkmark_green_small;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_checkmark_green_small;

        i4_ret = c_wgl_do_cmd((pt_select_page->t_sel_box_btn[ui1_idx]).h_cb_icon_1,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_FG),
                               WGL_PACK(&t_img_info));                 
        RET_ON_ERR(i4_ret);

        /* set select box icon_2 */
        c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
        t_img_info.e_type = WGL_IMG_SET_BASIC;
        t_img_info.u_img_data.t_standard.t_enable    = wzd_tv_device_name_input_img_hlt_choose[ui1_idx];
        t_img_info.u_img_data.t_standard.t_disable   = wzd_tv_device_name_input_img_choose[ui1_idx];

        i4_ret = c_wgl_do_cmd((pt_select_page->t_sel_box_btn[ui1_idx]).h_cb_icon_2,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK(WGL_IMG_FG),
                               WGL_PACK(&t_img_info));                 
        RET_ON_ERR(i4_ret);

        /* set select box text */                           
        i4_ret =  c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_idx].h_cb_text,
                                WGL_CMD_TEXT_SET_TEXT,
                                WGL_PACK (WZD_TEXT(wzd_tv_device_name_input_type_mlm_text[ui1_idx])),
                                WGL_PACK (c_uc_w2s_strlen (WZD_TEXT(wzd_tv_device_name_input_type_mlm_text[ui1_idx]))));
        RET_ON_ERR (i4_ret);

        c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
        t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
        RET_ON_ERR (c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_idx].h_cb_text,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_TEXT),
                                  WGL_PACK (&t_color_txt)));

        c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        
        RET_ON_ERR (c_wgl_do_cmd (pt_select_page->t_sel_box_btn[ui1_idx].h_cb_text,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (&t_fnt_info),
                                  NULL));  

        c_wgl_enable((pt_select_page->t_sel_box_btn[ui1_idx]).h_cb_icon_2, FALSE);
    }
    
    return WZDR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_desc_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/ 
static INT32 _wzd_page_tv_name_input_desc_create(HANDLE_T     h_parent,
                                           GL_RECT_T*   t_rect,
                                           HANDLE_T*    ph_widget)
{
    UINT32              i4_ret = WZDR_OK;
    UINT32              ui4_style = 0;
    UINT8               ui1_align = 0;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_color_info_bg, t_color_info_fg;
    WGL_INSET_T         t_inset;
    CHAR*               s_font_name = wzd_view_get_font_name();
    
    /* set font theme */   
    ui4_style = WGL_STL_TEXT_MULTILINE |
                WGL_STL_TEXT_MAX_512  |
                WGL_STL_TEXT_MAX_DIS_5_LINE |
                WZD_WIDGET_STYLE;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_begin_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_begin_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_begin_txt);

    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = _wzd_page_tv_name_input_create_text(
                t_rect,
                h_parent,
                NULL,
                ui4_style,
                ph_widget,
                &t_fnt_info,
                ui1_align,
                &t_color_info_bg,
                &t_color_info_fg,
                &t_inset);           
    RET_ON_ERR (i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_reset_device_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_set_page_text(HANDLE_T h_parent, UTF16_T* pw2s_text)
{    
    UINT32              i4_ret = WZDR_OK;    
   
    /* set text */
    i4_ret = c_wgl_do_cmd(h_parent,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen(pw2s_text)));
          
    RET_ON_ERR(i4_ret);  
    
    return WZDR_OK;        
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_text_connect
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_text_connect (const UTF16_T* prifix_w2s, UTF16_T* ps_w2s)
{    
    UINT32 ui4_len;
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;
    
    c_uc_w2s_strcpy(ps_w2s, prifix_w2s);
        
    switch (pt_this->ui4_type_sel_idx)
    {
    case DEVICE_TYPE_SELECT_BLURAY_PLAYER:   
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY_MSG), ui4_len);
        break;
        
    case DEVICE_TYPE_SELECT_CABLE_BOX:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_CABLE_BOX_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_CABLE_BOX_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_COMPUTER:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_COMPUTER_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_COMPUTER_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_DVD_PLAYER:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVD_PLAYER_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVD_PLAYER_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_DVR:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVR_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_DVR_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_GAME:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_GAME_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_GAME_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_SATELLITE:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_SATELLITE_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_SATELLITE_MSG), ui4_len);
        break;

    case DEVICE_TYPE_SELECT_VCR:
        ui4_len = c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_VCR_MSG));
        c_uc_w2s_strncat(ps_w2s, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_VCR_MSG), ui4_len);
        break;
       
    default:
        break;
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_source_full_dlg_text_connect
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_source_full_dlg_text_connect (UTF16_T* dlg_w2s)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;
    UTF16_T        str_w2s[WZD_DEVICE_NAME_INPUT_LEN_MAX + 1] = {0};
    CHAR           s_src_name[WZD_DEVICE_NAME_INPUT_LEN_MAX + 1] = {0};
    ISO_639_LANG_T s639_lang = {0};
    ISL_REC_T      t_isl_rec;
    INT32          i4_ret = WZDR_OK;
	
    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    i4_ret = a_isl_get_rec_by_id(pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx], &t_isl_rec); 
    if (i4_ret != ISLR_OK) {
        DBG_INFO( ("#####[Ln: %d] pt_this->ui1_sel_src_idx = %d, i4_ret = %d,src_id=%d!!!!\n",  __LINE__, pt_this->ui1_sel_src_idx, i4_ret,pt_this->aui1_input_src_id[pt_this->ui1_sel_src_idx])); 
        return WZDR_FAIL;
    }
    c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec), s_src_name, WZD_DEVICE_NAME_INPUT_LEN_MAX);

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if ((i4_ret == WZDR_OK) && (c_strncmp(s639_lang, s639_app_cfg_lang_spa, ISO_639_LANG_LEN) == 0))
    {
        c_uc_w2s_strncpy(str_w2s, WZD_TEXT(MLM_WZD_KEY_TV_DEVICE_NAME_INPUT_DLG_MSG_1), WZD_DEVICE_NAME_INPUT_LEN_MAX);
        c_uc_w2s_strncat(str_w2s, a_isl_get_display_name(&t_isl_rec), WZD_DEVICE_NAME_INPUT_LEN_MAX);
    }
    else
    {
        c_uc_w2s_strcpy(str_w2s, a_isl_get_display_name(&t_isl_rec));
    }

    c_uc_w2s_strncat(str_w2s, WZD_TEXT(MLM_WZD_KEY_TV_DEVICE_NAME_INPUT_DLG_MSG_2), WZD_DEVICE_NAME_INPUT_LEN_MAX);
    
    _wzd_page_tv_name_input_text_connect (str_w2s, dlg_w2s);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_full_dlg_set_content
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_full_dlg_set_content(VOID)
{
    UTF16_T code_w2s[WZD_DEVICE_NAME_INPUT_SHOW_MIG_MAX_NUM] = {0};

    wzd_view_full_screen_dlg_set_icon(h_g_wzd_img_checkmark_green_small, FALSE);

    _wzd_page_tv_name_input_source_full_dlg_text_connect(code_w2s);

    wzd_view_full_screen_dlg_set_text(code_w2s, FALSE);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_do_show_dialog_timer
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_do_show_dialog_timer(VOID* pv_data, SIZE_T  z_data_size)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;    
    INT32 i4_ret = WZDR_OK;

    wzd_view_full_screen_dlg_hide();
    _wzd_page_tv_name_input_init();

    /* find bug add log */
    i4_ret = a_wzd_is_resume_from_menu_setup();
    DBG_INFO( ( "[Ln: %d] Name input show dialog timer! i4_ret = %d, t_g_wzd.ui1_state = %d.\n", __LINE__, i4_ret, t_g_wzd.ui1_state));

    if (a_wzd_is_resume_from_menu_setup())
    {
        DBG_INFO( ( "[Ln: %d] Name input show dialog timer!\n", __LINE__));
        a_wzd_exit(); /*Exit Wizard*/
    }
    else
    {
        if ((pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP )||
			(pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE))
        {
            DBG_INFO( ( "[Ln: %d] #### Name input show dialog timer!\n", __LINE__));
            wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE);
	        //a_wzd_exit(); /*Exit Wizard*/
	        
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
	WZD_DLG_PAGE_T* 				   pt_dlg_page	  = &t_g_name_input_dlg_page;

			if(b_g_is_amp_plug_dlg_show == FALSE)
			{
				nav_cec_custom_amp_plug_dlg_show();
				
				c_timer_start(pt_dlg_page->h_amp_plug_dlg_timer, 
							  5000,
							  X_TIMER_FLAG_ONCE,
							  _wzd_page_tv_name_input_amp_plug_dlg_show_nfy_fct,
							  NULL); 
				
			}
			else
#endif
#endif
#endif
	        _wzd_page_tv_name_input_dlg_show();
        }

    }

    if (pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP )
    {
        pt_this->e_name_input_enter_reason = NAME_INPUT_ENTER_REASON_NONE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_timer_show_dialog_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_timer_show_dialog_nfy_fct(HANDLE_T  h_timer,
                                                              VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_page_tv_name_input_do_show_dialog_timer, NULL, 0, FALSE); 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_sel_box_nfy
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
static VOID _wzd_page_tv_name_input_sel_box_nfy(
                    UINT32           ui4_msg,
                    VOID*            pv_param1,
                    VOID*            pv_param2)
{   
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;
    WZD_INPUT_PAGE_T*                  pt_input_page = &t_g_name_input_select_srouce_page;
    BOOL                               b_is_set_checkmark = FALSE;

    switch (ui4_msg)
    {
        case WZD_SEL_BOX_MSG_ITEM_FOCUSED:
            pt_this->ui1_input_sel_box_idx = (UINT8)(UINT32)pv_param1;
            _wzd_page_tv_name_input_inp_page_set_foucsed_box_txt_hlt((UINT32)pv_param1);
            _wzd_page_tv_name_input_page_update_checkmark();
            break;

        case WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED:
            ui4_g_pre_focused_sb_idx = (UINT32)pv_param1;
            _wzd_page_tv_name_input_inp_page_set_losed_foucs_box_txt_initial((UINT32)pv_param1);
            break;
            
        case WZD_SEL_BOX_MSG_KEY_INPUT:
            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
                    b_is_set_checkmark = FALSE;

                    pt_this->ui1_sel_src_idx = (UINT8)(UINT32)pv_param2;
                    pt_this->ui1_input_sel_box_idx = (UINT8)(UINT32)pv_param2;
                    _wzd_page_tv_name_input_change_input();

                    /* need move icon2/text widget animation */
                    if (!pt_this->b_show_checkbox)
                    {
                        b_is_set_checkmark = TRUE;
                        pt_this->b_show_checkbox = TRUE;
                        _wzd_page_tv_name_input_page_set_checkmark();
                    }

                    if (!b_is_set_checkmark)
                    {
                        if ((DEVICE_TYPE_SELECT_CABLE_BOX== pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE== pt_this->ui4_type_sel_idx))
                    	{
    						if(pt_this->ui1_sel_src_idx == (pt_this->ui1_sel_box_num-1))
                			{	
                				wzd_page_tv_setup_enter_from_tv_name_input_rf(pt_this->ui4_type_sel_idx);
    							return;
                			}
                    	}
                    }

                    /* not need set device info for RF */
                    if (!(((DEVICE_TYPE_SELECT_CABLE_BOX== pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE== pt_this->ui4_type_sel_idx))
                        &&(pt_this->ui1_sel_src_idx == (pt_this->ui1_sel_box_num-1))))
                	{
        				_wzd_page_tv_name_input_set_device_info();
                	}
                    
                    /* Set dialog */    
                    _wzd_page_tv_name_input_full_dlg_set_content();

                    if (!b_is_set_checkmark)
                    {
                        /* lose focus for the sel box when display the dialog */
                        wzd_view_sel_box_lose_focus(pt_this->ui1_input_sel_box_idx, FALSE);
                        
                        wzd_view_full_screen_dlg_show(FALSE);
                        
                        c_timer_start(pt_input_page->h_show_dlg_timer, 
                                      5000,
                                      X_TIMER_FLAG_ONCE,
                                      _wzd_page_tv_name_input_timer_show_dialog_nfy_fct,
                                      NULL);
                    }
                    break;

                case BTN_CURSOR_DOWN:
                    {
                        /* save the lasted focus */
                        ui4_g_pre_focused_sb_idx = (UINT32)pv_param2;
                        wzd_view_sel_box_lose_focus(ui4_g_pre_focused_sb_idx, FALSE);

                        wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, TRUE);
                    }
                    break;                    

                default:
                    break;
            }
            break;
        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_set_sel_box_theme
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx        Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_set_sel_box_theme (VOID)
{
    UINT8                        		ui1_rec_num = 0;
    UINT32                       		ui4_i = 0;
    HANDLE_T                     		h_sb_txt = NULL_HANDLE;
    HANDLE_T                     		h_sb_icon_1st = NULL_HANDLE;
    HANDLE_T                     		h_sb_icon_2nd = NULL_HANDLE;
    GL_RECT_T                    		t_rect = {0};
    WGL_COLOR_INFO_T             		t_color_txt;
    WGL_FONT_INFO_T              		t_fnt_info;
	WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;

    RET_ON_ERR (a_isl_get_num_rec(&ui1_rec_num));
	
	if((pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_CABLE_BOX)||(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SATELLITE))
	{
		ui1_rec_num = ui1_rec_num + 1;
	}

    /* update text theme */
    for( ui4_i = 0; ui4_i < ui1_rec_num - 1; ui4_i++ )
    {       
        h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_i);

        /* move position */
        SET_RECT_BY_SIZE(&t_rect,
                         WZD_SEL_BOX_BTN_TXT_X,
                         WZD_SEL_BOX_BTN_TXT_Y - (40 * WZD_UI_RATIO_W),
                         WZD_SEL_BOX_BTN_TXT_W,
                         WZD_SEL_BOX_BTN_TXT_H);

        RET_ON_ERR (c_wgl_move(h_sb_txt,
                               &t_rect,
                               WGL_NO_AUTO_REPAINT));
                       
        /* set alignment */
        RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
                        WGL_CMD_TEXT_SET_ALIGN,
                        WGL_PACK(WGL_AS_CENTER_CENTER),
                        NULL));        

        /* set color */
        c_memset (&t_color_txt, 0, sizeof (WGL_COLOR_INFO_T));
        t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
        COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
        RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_TEXT),
                                  WGL_PACK (&t_color_txt)));

        /* set font size */
        c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        
        RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (&t_fnt_info),
                                  NULL));                    
    }

    /* update icon 1 theme */
    for( ui4_i = 0; ui4_i < ui1_rec_num - 1; ui4_i++ )
    {                    
        /* set icon_1 theme */
        h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui4_i);
        
        /* move position */
        SET_RECT_BY_SIZE(&t_rect,
                         WZD_SEL_BOX_BTN_ICON_1_X,
                         WZD_SEL_BOX_BTN_ICON_1_Y  + 40 * WZD_UI_RATIO_W,
                         WZD_SEL_BOX_BTN_ICON_1_W  + 20 * WZD_UI_RATIO_W,
                         WZD_SEL_BOX_BTN_ICON_1_H);

        RET_ON_ERR (c_wgl_move(h_sb_icon_1st,
                               &t_rect,
                               WGL_NO_AUTO_REPAINT));
        
        RET_ON_ERR (c_wgl_do_cmd(h_sb_icon_1st,
                              WGL_CMD_ICON_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL));
    } 

    /* update icon 2 theme */
    for( ui4_i = 0; ui4_i < ui1_rec_num - 1; ui4_i++ )
    { 
        /* set icon_2 theme */
        h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(ui4_i);

        /* move position */
        SET_RECT_BY_SIZE (& t_rect,
                      WZD_SEL_BOX_BTN_ICON_2_X - 5 * WZD_UI_RATIO_W,
                      WZD_SEL_BOX_BTN_ICON_2_Y,
                      WZD_SEL_BOX_BTN_ICON_2_W + 20 * WZD_UI_RATIO_W,
                      WZD_SEL_BOX_BTN_ICON_2_H);
                      
        RET_ON_ERR (c_wgl_move(h_sb_icon_2nd,
                               &t_rect,
                               WGL_NO_AUTO_REPAINT));

        RET_ON_ERR (c_wgl_do_cmd(h_sb_icon_2nd,
                              WGL_CMD_ICON_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                              NULL));
    }
                         
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_input_src_id_map
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static UINT8 _wzd_page_tv_name_input_input_src_id_map (UINT8 ui1_input_id)
{ 
    UINT8        ui1_rec_num = 0;
    ISL_REC_T    t_isl_rec = {0};
    UINT8        ui1_show_idx = 0xFF;
    UINT8        ui1_idx;
    BOOL         b_is_have_vga = FALSE;
	WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;

    a_isl_get_num_rec(&ui1_rec_num);

    for(ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
    {
        c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

        if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
        {
            b_is_have_vga = TRUE;
            break;
        }
    }

    if (ui1_rec_num == 2 ) 
    {
        ui1_show_idx = ui1_input_id - 1;
    } 
    
    if (ui1_rec_num >= 3)
    {
        c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
        a_isl_get_rec_by_idx(ui1_input_id, &t_isl_rec); 
        if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type && ui1_input_id >= 2) /* HDMI */
        {
            if (b_is_have_vga == TRUE)
            {
                ui1_show_idx = ui1_input_id - 3;
            }
            else
            {
                ui1_show_idx = ui1_input_id - 2;
            }
        }
        else if (DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type 
            || DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type)                  /* COMP */
        {
            if (b_is_have_vga == TRUE)
            {
                ui1_show_idx = ui1_rec_num - 4;
            }
            else
            {
                ui1_show_idx = ui1_rec_num - 3;
            }
        }
        else if ( DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type || DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
        {
            ui1_show_idx = 0xFF;
        }
        else
        {
           DBG_INFO( ("[Ln: %d] ui1_input_id[%d] get show idx error!!!\n", __LINE__, ui1_input_id, ui1_show_idx));
        }
    }

	/*TV input source(RF)*/
	if(ui1_input_id == 0)
	{
		ui1_show_idx = pt_this->ui1_sel_box_num-1;
	}

    return ui1_show_idx;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_update_sel_box_txt
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
static INT32 _wzd_page_tv_name_input_set_sel_box_content(VOID)
{
    INT32               i4_ret = WZDR_OK;
    UINT16              ui2_input_idx = 0;
    UINT8               ui1_show_idx = 0;
    UINT8               ui1_rec_num = 0;
    ISL_REC_T           t_isl_rec = {0};
    WGL_IMG_INFO_T      t_img_info;
    WGL_HIMG_TPL_T      h_inp_src_img;
    WGL_HIMG_TPL_T      h_inp_src_hlt_img;
    HANDLE_T            h_sb_text = NULL_HANDLE;
    HANDLE_T            h_sb_icon_1 = NULL_HANDLE;
    HANDLE_T            h_sb_icon_2 = NULL_HANDLE;
    CHAR                s_src_name[WZD_DEVICE_NAME_INPUT_LEN_MAX + 1] = {0};
    CHAR*               ps_disp_name = NULL;
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;
	CHAR           		s_rf_name[WZD_DEVICE_NAME_INPUT_TYPE_LEN + 1] = "Coaxial";//RF->Coaxial
	UTF16_T           	w2s_rf_name[WZD_DEVICE_NAME_INPUT_TYPE_LEN + 1] = {0};
    HANDLE_T            h_checkmark_icon = NULL_HANDLE;
    UINT8               ui1_type_id = 0;
    
    RET_ON_ERR (_wzd_page_tv_name_input_set_sel_box_theme());

    /* Iterate all the input sources */
    a_isl_get_num_rec(&ui1_rec_num);
    for (ui2_input_idx = 0; ui2_input_idx < ui1_rec_num; ui2_input_idx++)
    { 
        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        i4_ret = a_isl_get_rec_by_idx(ui2_input_idx, &t_isl_rec); 
        if (i4_ret != ISLR_OK)
        {
            DBG_INFO( ("[Ln: %d]  ui2_idx = %d, ui1_rec_num = %d, i4_ret = %d!!!!\n",  __LINE__, ui2_input_idx, ui1_rec_num, i4_ret)); 
            return WZDR_FAIL;
        }

        /* ignore TV inp src */
        if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
        {
            continue;
        }

        c_uc_w2s_to_ps(a_isl_get_display_name(&t_isl_rec), s_src_name, WZD_DEVICE_NAME_INPUT_LEN_MAX);
        ps_disp_name = c_str_toupper(s_src_name);

        if (0 == c_strncmp(ps_disp_name, "HDMI", 4))
        {
            h_inp_src_img     = h_g_wzd_img_icon_hdmi_gray;
            h_inp_src_hlt_img = h_g_wzd_img_icon_hdmi_white;     /* HDMI */
        }
        else if (0 == c_strncmp(ps_disp_name, "AV", 2)
            || 0 == c_strncmp(ps_disp_name, "COMP", 4)
            || 0 == c_strncmp(ps_disp_name, "RGB", 3))
        {
            h_inp_src_img     = h_g_wzd_img_icon_comp_gray;
            h_inp_src_hlt_img = h_g_wzd_img_icon_comp_white;     /* COMP */
        }
        else
        {
            continue;
        }

        ui1_show_idx = _wzd_page_tv_name_input_input_src_id_map((UINT8)ui2_input_idx);
        if (ui1_show_idx == 0XFF)
        {
            continue;
        }
        
        pt_this->aui1_input_src_id[ui1_show_idx] = t_isl_rec.ui1_id;
        
        /* set sel box text */
        h_sb_text = wzd_view_sel_box_get_txt_handle((INT32)ui1_show_idx);
        i4_ret = c_wgl_do_cmd(h_sb_text,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK (a_isl_get_display_name(&t_isl_rec)),                             
                              WGL_PACK ((UINT16)0xFFFF));
		
        /* set sel box icon 2 */
        c_memset(&t_img_info, 0, sizeof(t_img_info));
        t_img_info.e_type = WGL_IMG_SET_BASIC;
        t_img_info.u_img_data.t_standard.t_enable  = h_inp_src_hlt_img;
        t_img_info.u_img_data.t_standard.t_disable = h_inp_src_img;
                
        h_sb_icon_2 = wzd_view_sel_box_get_icon_2_handle((INT32)ui1_show_idx);
        RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK(WGL_IMG_FG),
                                  WGL_PACK(&t_img_info))); 
        RET_ON_ERR ( c_wgl_enable(h_sb_icon_2, FALSE));  
    }

	/*ADD RF BOX*/
	if ((DEVICE_TYPE_SELECT_CABLE_BOX == pt_this->ui4_type_sel_idx) || (DEVICE_TYPE_SELECT_SATELLITE == pt_this->ui4_type_sel_idx))
	{
		DBG_INFO( ("\n####%s(%d)ui1_rec_num=%d\n",__FUNCTION__,__LINE__,ui1_rec_num));
		c_uc_ps_to_w2s(s_rf_name,w2s_rf_name,WZD_DEVICE_NAME_INPUT_TYPE_LEN);
		
		/* set sel box text for the RF*/
	    h_sb_text = wzd_view_sel_box_get_txt_handle((INT32)(pt_this->ui1_sel_box_num-1));
	    c_wgl_do_cmd(h_sb_text,
	                 WGL_CMD_TEXT_SET_TEXT,
	                 WGL_PACK (w2s_rf_name),                             
	                 WGL_PACK ((UINT16)0xFFFF)); 
	    
	    /* set sel box icon 2 for the RF*/
	    c_memset(&t_img_info, 0, sizeof(t_img_info));
	    t_img_info.e_type = WGL_IMG_SET_BASIC;
	    t_img_info.u_img_data.t_standard.t_enable  = h_g_wzd_input_icon_rf_white;
	    t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_input_icon_RF;
	            
	    h_sb_icon_2 = wzd_view_sel_box_get_icon_2_handle((INT32)(pt_this->ui1_sel_box_num-1));
	    RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2,
	                              WGL_CMD_GL_SET_IMAGE,
	                              WGL_PACK(WGL_IMG_FG),
	                              WGL_PACK(&t_img_info))); 
	    c_wgl_enable(h_sb_icon_2, FALSE); 

		/*TV input source*/
		pt_this->aui1_input_src_id[pt_this->ui1_sel_box_num-1] = 0;
	}

    /* set sel box icon 1 */
    for (ui2_input_idx = 0; ui2_input_idx < WZD_BOX_BTN_COUNT; ui2_input_idx++)
    {
        h_sb_icon_1 = wzd_view_sel_box_get_icon_1_handle(ui2_input_idx);

        for (ui1_type_id = DEVICE_TYPE_SELECT_BLURAY_PLAYER; ui1_type_id <= DEVICE_TYPE_SELECT_VCR; ui1_type_id++)
        {
            if (pt_this->b_is_named[ui2_input_idx][ui1_type_id])
            {
                if (pt_this->ui1_input_sel_box_idx == ui2_input_idx)
                {
                    h_checkmark_icon = h_g_wzd_img_checkmark_green_large;
                    
                    t_img_info.e_type = WGL_IMG_SET_STANDARD;
                    t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
                    t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
                    t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;
                    
                    c_wgl_do_cmd(h_sb_icon_1,
                                 WGL_CMD_GL_SET_IMAGE,
                                 WGL_PACK(WGL_IMG_FG),
                                 WGL_PACK(&t_img_info));  
                    
                    RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1, WGL_SW_NORMAL));
                    pt_this->b_show_checkbox = TRUE;
                    break;
                }
            }
        }

        if (h_checkmark_icon == h_g_wzd_img_checkmark_green_large)
        {
            break;
        }
    }
    
    return WZDR_OK;   
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_create_sel_box
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_create_sel_box (VOID)
{
    UINT8                       		ui1_rec_num = 0;
    WZD_VIEW_SEL_BOX_INFO_T     		t_sel_box_info = {0};
    ISL_REC_T                   		t_isl_rec = {0};
    UINT8                       		ui1_idx;
    BOOL                        		b_is_have_vga = FALSE;
    BOOL                                b_is_have_cast = FALSE;
	WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;

    a_isl_get_num_rec(&ui1_rec_num);

    for (ui1_idx = 0; ui1_idx < ui1_rec_num; ui1_idx++)
    {
        c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

        if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
        {
            b_is_have_vga = TRUE;
        }
        else if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
        {
            b_is_have_cast = TRUE;
        }
    }
    
    c_memset(&t_sel_box_info, 0 , sizeof(WZD_VIEW_SEL_BOX_INFO_T));
    
    /* reset previous focused select box button */
    ui4_g_pre_focused_sb_idx = 0;

    /* for Cast tv virtual source */
    if (b_is_have_vga == TRUE)
    {
        t_sel_box_info.ui4_index_total = ui1_rec_num - 2;
    }
    else
    {
        t_sel_box_info.ui4_index_total = ui1_rec_num - 1;
    }

    if (b_is_have_cast && t_sel_box_info.ui4_index_total > 1)
    {
        t_sel_box_info.ui4_index_total--;
    }

	if((pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_CABLE_BOX)||(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SATELLITE))
	{
		t_sel_box_info.ui4_index_total = t_sel_box_info.ui4_index_total + 1;
	}

	pt_this->ui1_sel_box_num = t_sel_box_info.ui4_index_total;

    t_sel_box_info.pf_data_chg_nfy = _wzd_page_tv_name_input_sel_box_nfy;

    wzd_view_sel_box_set_info_data (&t_sel_box_info);

    return WZDR_OK;       
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_select_name_page_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_select_name_page_create(HANDLE_T  h_parent) 
{
    GL_RECT_T   t_rect;
    WZD_SELECT_PAGE_T* pt_select_page = &t_g_name_input_select_type_page;

    /* description text create */
    c_memset (&t_rect, 0, sizeof (GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      BASE_FRM_W,
                      80 * WZD_UI_RATIO_W);

    RET_ON_ERR( _wzd_page_tv_name_input_desc_create(h_parent,
                                                             &t_rect,
                                                             &pt_select_page->h_select_desc_txt));

    /* select box buttons create */
    RET_ON_ERR (_wzd_page_tv_name_input_create_choose_box_frm(h_parent));
    RET_ON_ERR ( _wzd_page_tv_name_input_create_choose_box_buttons());

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_select_input_page_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_select_input_page_create(HANDLE_T  h_parent)
{
    GL_RECT_T   t_rect;
    INT32       i4_ret;
    WZD_INPUT_PAGE_T* pt_input_page = &t_g_name_input_select_srouce_page;

    /* description text create */
    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      BASE_FRM_W,
                      80 * WZD_UI_RATIO_W);

    i4_ret = _wzd_page_tv_name_input_desc_create(h_parent,
                                                        &t_rect,
                                                        &pt_input_page->h_input_desc_txt);
    RET_ON_ERR(i4_ret);

    /* create dlg show timer */
    RET_ON_ERR (c_timer_create(&pt_input_page->h_show_dlg_timer));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_create
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/                        
static INT32 _wzd_page_tv_name_input_create (VOID)
{
    HANDLE_T h_layout_frm = NULL_HANDLE;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    c_memset( &t_g_tv_name_input, 0, sizeof(WZD_TV_DEVICE_NAME_INPUT_MEMBER_T) );
    c_memset( &t_g_name_input_dlg_page, 0, sizeof(WZD_DLG_PAGE_T) );
    c_memset( &t_g_name_input_select_type_page, 0, sizeof(WZD_SELECT_PAGE_T) );
    c_memset( &t_g_name_input_select_srouce_page, 0, sizeof(WZD_INPUT_PAGE_T) );
        
    RET_ON_ERR ( _wzd_page_tv_name_input_dlg_create(h_layout_frm) );
    
    RET_ON_ERR (_wzd_page_tv_name_input_select_name_page_create(h_layout_frm) );
    
    RET_ON_ERR (_wzd_page_tv_name_input_select_input_page_create(h_layout_frm) );
          
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_dlg_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_dlg_show(VOID)
{
    INT32               i4_ret = WZDR_OK;
    HANDLE_T            h_layout_frm = NULL_HANDLE;
	WZD_DLG_PAGE_T*     pt_dlg_page    = &t_g_name_input_dlg_page;
   
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));  
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE)); 
    
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
    RET_ON_ERR (wzd_view_title_txt_set_visibility (FALSE));
    RET_ON_ERR (wzd_view_footer_set_visibility (FALSE));

    /* Set main frame no background */
    RET_ON_ERR (wzd_view_set_main_frm_bg(NULL_HANDLE, FALSE)); 
    RET_ON_ERR (wzd_set_stream_play_region(FALSE, FALSE));
     
    i4_ret = _wzd_page_tv_name_input_finished_dlg_set_icon (h_g_wzd_img_checkmark_green_small);
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_name_input_finished_dlg_set_text (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_FINISHED_IMG));
    RET_ON_ERR (i4_ret);
    
    i4_ret = _wzd_page_tv_name_input_finished_dlg_show();
    RET_ON_ERR (i4_ret);
    
    RET_ON_ERR (wzd_view_main_frm_repaint());

	c_timer_start(pt_dlg_page->h_dlg_timer, 
				  5000,
				  X_TIMER_FLAG_ONCE,
				  _wzd_page_tv_name_input_finished_btn_dlg_show_nfy_fct,
				  NULL);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_device_named_info
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_device_named_info(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*   pt_this = &t_g_tv_name_input;
    CHAR                                 s_type_name[WZD_DEVICE_NAME_INPUT_LEN_MAX] = {0};
	CHAR                                 s_set_type_name[WZD_DEVICE_NAME_INPUT_LEN_MAX] = {0};
    UINT8                                ui1_rec_num = 0;
    INT32                                i4_ret = WZDR_OK; 
    UINT8                                ui1_input_id;  
    UINT8                                ui1_show_idx = 0xFF;

    c_memset(pt_this->b_is_named, 0, sizeof(pt_this->b_is_named));  
    c_memset(pt_this->ui4_type_named_count, 0, sizeof(pt_this->ui4_type_named_count));  
    
    a_isl_get_num_rec(&ui1_rec_num);
    
    for (ui1_input_id = 0; ui1_input_id < ui1_rec_num; ui1_input_id++)
    {
        //i4_ret = a_cfg_custom_get_inp_name(ui1_input_id, s_type_name);
        i4_ret = a_cfg_custom_get_device_type(ui1_input_id,s_type_name);
		DBG_INFO( ("\n####%s(%d) s_type_name=%s\n",__FUNCTION__,__LINE__,s_type_name));
        if (i4_ret != WZDR_OK || c_strlen(s_type_name) == 0)
        {
            continue;
        }

        ui1_show_idx = _wzd_page_tv_name_input_input_src_id_map(ui1_input_id);

		for(UINT16 ui2_dev_type_mlm_idx = MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY;ui2_dev_type_mlm_idx<=MLM_WZD_KEY_DEVICE_SETUP_TYPE_VCR;ui2_dev_type_mlm_idx++)
		{
			c_uc_w2s_to_ps(WZD_TEXT(ui2_dev_type_mlm_idx),s_set_type_name,WZD_DEVICE_NAME_INPUT_LEN_MAX);
			DBG_INFO( ("\n####%s(%d) s_set_type_name=%s\n",__FUNCTION__,__LINE__,s_set_type_name));
			if (c_strncmp(s_type_name, s_set_type_name, c_strlen(s_set_type_name)) == 0)
			{
			    if (pt_this->ui1_input_sel_box_idx == ui1_show_idx)
                {         
    				pt_this->b_is_named[ui1_show_idx][ui2_dev_type_mlm_idx-MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY] = TRUE;
    	            pt_this->ui4_type_named_count[ui2_dev_type_mlm_idx-MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY]++;
                }
                else
                {
                    pt_this->b_is_named[ui1_show_idx][ui2_dev_type_mlm_idx-MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY] = FALSE;
                }
			}
			else
			{
				pt_this->b_is_named[ui1_show_idx][ui2_dev_type_mlm_idx-MLM_WZD_KEY_DEVICE_SETUP_TYPE_BLU_RAY] = FALSE;
			}
				
		}

    }
    
    return WZDR_OK;                             
} 
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_select_input_show
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_select_input_show(VOID)
{
    HANDLE_T h_layout_frm = NULL_HANDLE;
    UTF16_T  ps_w2s[WZD_DEVICE_NAME_INPUT_SHOW_MIG_MAX_NUM] = {0}; 
    WZD_INPUT_PAGE_T*  pt_input_page = &t_g_name_input_select_srouce_page;
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*   pt_this = &t_g_tv_name_input;
 
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));

    /* Set main frame color */
    RET_ON_ERR (wzd_view_set_main_frm_bg(h_g_wzd_img_background, FALSE)); 

    /* Set footer */
    RET_ON_ERR (wzd_view_footer_set_btn_num(1));
    RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_BTN_BACK)));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
    RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, FALSE));
    RET_ON_ERR (wzd_view_footer_update_btn_navigation());
    
    /* Set title */
    if (pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP)
    {
    	if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_CABLE_BOX)
    	{
    	  RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_TV_DEVICE_NAME_INPUT_CABLE_BOX_TITLE), NULL_HANDLE));
    	}
    	else if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_SELECT_SATELLITE)
    	{
	    	RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_TV_DEVICE_NAME_INPUT_SATELLITE_TITLE), NULL_HANDLE));
    	}
    }
    else
    {
	    RET_ON_ERR(wzd_view_title_set_htxt (WZD_TEXT(MLM_WZD_KEY_TV_DEVICE_NAME_INPUT_TITLE), NULL_HANDLE));
    }

    /* Set description */
    RET_ON_ERR (_wzd_page_tv_name_input_text_connect (WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_SEL_INPUT_MSG), ps_w2s));  
    RET_ON_ERR (_wzd_page_tv_name_input_set_page_text (pt_input_page->h_input_desc_txt, ps_w2s));

    /* Set select box */
    RET_ON_ERR (_wzd_page_tv_name_input_create_sel_box ());

    /* Set select box content */
    RET_ON_ERR (_wzd_page_tv_name_input_set_sel_box_content());

    /* Show page */  
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
    RET_ON_ERR (c_wgl_set_visibility (pt_input_page->h_input_desc_txt, WGL_SW_RECURSIVE));
    
    if (pt_this->e_name_input_enter_reason != NAME_INPUT_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE)
    {
        RET_ON_ERR (wzd_view_sel_box_set_focus (pt_this->ui1_input_sel_box_idx, FALSE));
    }
    
    RET_ON_ERR (wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_NORMAL));
    _wzd_page_tv_name_input_page_update_checkmark();
    RET_ON_ERR (wzd_view_footer_set_visibility (TRUE));
    RET_ON_ERR (wzd_view_main_frm_repaint ());
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_update_by_state
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_name_input_update_by_state(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*   pt_this = &t_g_tv_name_input;    

    if (TV_DEVICE_NAME_INPUT_TYPE_SELECT == pt_this->e_state)
    {   
        #if 0
        pt_this->ui4_type_sel_idx = 0XFFFFFFFF;
        pt_this->ui4_sel_box_idx = WZD_BOX_BTN_01;
        RET_ON_ERR (_wzd_page_tv_name_input_select_type_show ());  
        #else
        {
            wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE);
	        //a_wzd_exit(); /*Exit Wizard*/
	        
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
	WZD_DLG_PAGE_T* 					 pt_dlg_page	= &t_g_name_input_dlg_page;

			if(b_g_is_amp_plug_dlg_show == FALSE)
			{
				nav_cec_custom_amp_plug_dlg_show();
				
				c_timer_start(pt_dlg_page->h_amp_plug_dlg_timer, 
							  5000,
							  X_TIMER_FLAG_ONCE,
							  _wzd_page_tv_name_input_amp_plug_dlg_show_nfy_fct,
							  NULL); 
				
			}
			else
#endif
#endif
#endif
	        _wzd_page_tv_name_input_dlg_show();
        }
        #endif
    }
    else if (TV_DEVICE_NAME_INPUT_SRC_SELECT == pt_this->e_state)
    {
    	if(pt_this->e_name_input_enter_reason != NAME_INPUT_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE)
		{
	        pt_this->ui1_sel_src_idx = 0XFF;
	        c_memset(pt_this->aui1_input_src_id, 0, sizeof(pt_this->aui1_input_src_id));
		}
        RET_ON_ERR (_wzd_page_tv_name_input_select_input_show ());
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_dsty
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
static INT32 _wzd_page_tv_name_input_dsty(VOID)
{
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_on_show
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
static INT32 _wzd_page_tv_name_input_on_show (UINT32  ui4_page_id)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;

    c_wgl_img_cache_flush();

    if (pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP)
    {       
        pt_this->e_state = TV_DEVICE_NAME_INPUT_SRC_SELECT;
		_wzd_page_tv_name_input_update_by_state();
    }
	else if(pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE)
	{
		pt_this->e_state = TV_DEVICE_NAME_INPUT_SRC_SELECT;
		_wzd_page_tv_name_input_update_by_state();

        /* display the full screen dialog move to notify callback function of page animation is finish */
	}
    else 
    {
        pt_this->ui4_sel_box_idx = 0;
        pt_this->e_state = TV_DEVICE_NAME_INPUT_TYPE_SELECT;
		_wzd_page_tv_name_input_update_by_state();
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_on_hide
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
static INT32 _wzd_page_tv_name_input_on_hide(UINT32 ui4_page_id)
{
    HANDLE_T h_layout_frm = NULL_HANDLE;
    
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
    
    c_wgl_img_cache_flush();
#if 0
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
    WZD_DLG_PAGE_T*         pt_dlg_page    = &t_g_name_input_dlg_page;
	INT32					i4_ret = WZDR_OK;

    if (NULL_HANDLE != pt_dlg_page->h_amp_plug_dlg_timer)
    {
        i4_ret = c_timer_delete(pt_dlg_page->h_amp_plug_dlg_timer);
        RET_ON_ERR(i4_ret);
    }
#endif
#endif
#endif
#endif
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_btn_do_show_dlg_timer
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_finished_btn_do_show_dlg_timer(VOID* pv_data,
                                                                          SIZE_T  z_data_size)
{
    _wzd_page_tv_name_input_finished_dlg_hide();
    wzd_page_goto( WZD_PAGE_NAVI_LAST_VALID_ITEM );
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_finished_btn_dlg_show_nfy_fct
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_finished_btn_dlg_show_nfy_fct(HANDLE_T  h_timer,
                                                                  VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_page_tv_name_input_finished_btn_do_show_dlg_timer, NULL, 0, FALSE); 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_name_input_choose_type_page_back_resume
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
static INT32 _wzd_page_name_input_choose_type_page_back_resume(VOID)
{
    if (!a_wzd_is_resume_from_menu_setup())
    {
        wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
    }

    return  WZDR_OK; 
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_name_input_input_page_back_resume
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
static INT32 _wzd_page_name_input_input_page_back_resume(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;

    /* resume device type info */       
    pt_this->ui4_type_sel_idx = 0XFFFFFFFF;    /* must clean in the last */
    pt_this->ui4_sel_box_idx = WZD_BOX_BTN_01;  
    pt_this->ui1_sel_src_idx = 0XFF;           /* must clean in the last */                        
                        
    /* back prev page */
    c_memset(pt_this->aui1_input_src_id, 0, sizeof(pt_this->aui1_input_src_id));

    if (pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP)
    {
        pt_this->e_name_input_enter_reason = NAME_INPUT_ENTER_REASON_NONE;
        wzd_page_tv_setup_enter_from_tv_name_input_input();
    }
    else
    {
        pt_this->e_state = TV_DEVICE_NAME_INPUT_TYPE_SELECT;
        _wzd_page_tv_name_input_update_by_state(); 
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_return_nfy_cb
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
static VOID _wzd_page_tv_name_input_return_nfy_cb(VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*      pt_this = &t_g_tv_name_input;

    switch (pt_this->e_state)
    {
        case TV_DEVICE_NAME_INPUT_TYPE_SELECT:
        {
            _wzd_page_name_input_choose_type_page_back_resume();
        }
            break;
        case TV_DEVICE_NAME_INPUT_SRC_SELECT:
        {
			if(!wzd_view_full_screen_dlg_is_show())
			{
	            _wzd_page_name_input_input_page_back_resume();
            }
        }
            break;
        default:
            break;
    }
    
    return;
}
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_amp_plug_dlg_show_do_timer
 *
 * Description: 
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_amp_plug_dlg_show_do_timer(VOID* pv_data,
																			SIZE_T	z_data_size)
{
	WZD_DLG_PAGE_T*             pt_dlg_page    = &t_g_name_input_dlg_page;
	
	c_timer_stop(pt_dlg_page->h_amp_plug_dlg_timer);
	
	_wzd_page_tv_name_input_dlg_show();
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_amp_plug_dlg_show_nfy_fct
 *
 * Description: 
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns: 0				   Successful.
 * Any other values 		   Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_amp_plug_dlg_show_nfy_fct(HANDLE_T	h_timer,
																		   VOID*	 pv_tag)
{
	wzd_async_invoke(_wzd_page_tv_name_input_amp_plug_dlg_show_do_timer, NULL, 0, FALSE); 
}
#endif
#endif
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_on_footer_nfy
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
static VOID _wzd_page_tv_name_input_on_footer_nfy(
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*        pt_this        = &t_g_tv_name_input;
    WZD_SELECT_PAGE_T*                        pt_select_page = &t_g_name_input_select_type_page;
	BOOL 									  b_visible = FALSE;
	HANDLE_T 								  h_sel_box = NULL_HANDLE;
    
    switch( ui4_msg )
    {
        case WZD_FOOTER_MSG_ITEM_FOCUSED:

            break;
        case WZD_FOOTER_MSG_KEY_INPUT:
            
            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
                    {
                        if( TV_DEVICE_NAME_INPUT_TYPE_SELECT == pt_this->e_state )     /* finished button okey */ 
                        {
                            if (!a_wzd_is_resume_from_menu_setup())
                            {
								
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
	WZD_DLG_PAGE_T* 	pt_dlg_page	 = &t_g_name_input_dlg_page;

								if(b_g_is_amp_plug_dlg_show == FALSE)
								{
									nav_cec_custom_amp_plug_dlg_show();
									
									c_timer_start(pt_dlg_page->h_amp_plug_dlg_timer, 
												  5000,
												  X_TIMER_FLAG_ONCE,
												  _wzd_page_tv_name_input_amp_plug_dlg_show_nfy_fct,
												  NULL); 
									
								}
								else
#endif
#endif
#endif
								 _wzd_page_tv_name_input_dlg_show();
                            }
                            else
                            {
                                a_wzd_exit();
                            }
                        }
                        else if( TV_DEVICE_NAME_INPUT_SRC_SELECT == pt_this->e_state ) /* back button okey */ 
                        {
                            _wzd_page_name_input_input_page_back_resume();     
                        }                                             
                    }
                    break;
                    
                case BTN_CURSOR_UP:
                    {
                        if( TV_DEVICE_NAME_INPUT_TYPE_SELECT == pt_this->e_state )
                        {
                            pt_this->ui4_sel_box_idx = WZD_BOX_BTN_01;
                            _wzd_page_tv_name_input_sel_page_set_losed_foucs_box_txt_hlt();
                            c_wgl_set_focus(pt_select_page->t_sel_box_btn[WZD_BOX_BTN_01].h_cb_btn_frm, WGL_NO_AUTO_REPAINT);
                            c_wgl_float(pt_select_page->t_sel_box_btn[pt_this->ui4_sel_box_idx].h_cb_btn_frm, TRUE, FALSE); 
                        }
                        else if( TV_DEVICE_NAME_INPUT_SRC_SELECT == pt_this->e_state )
                        {
							/* focus to pre select box */
							h_sel_box = wzd_view_sel_box_get_btn_handle (ui4_g_pre_focused_sb_idx);
							c_wgl_get_visibility(h_sel_box, &b_visible);
					        if (b_visible)
					        {
					            SHOW_ON_ERR (wzd_view_sel_box_set_focus(ui4_g_pre_focused_sb_idx, FALSE));
					        }
                        }
                                              
                        wzd_view_main_frm_repaint();
                    }
                default:
                    break;
            }
            break;
            
        default:
            break;
            
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_name_input_anim_finish_nfy
 *
 * Description: the notify callback function of the page animation is finish.
 *              only for RF scan is complete(tv setup page->tv name input page).
 *              display the full screen dialog after the page animation is finish.
 *              
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_name_input_anim_finish_nfy()
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T* pt_this = &t_g_tv_name_input;
    WZD_INPUT_PAGE_T*                  pt_input_page = &t_g_name_input_select_srouce_page;

    if(pt_this->e_name_input_enter_reason == NAME_INPUT_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE)
    {
        /* lose focus for the sel box when display the dialog */
        wzd_view_sel_box_lose_focus(pt_this->ui1_input_sel_box_idx, FALSE);
        
    	_wzd_page_tv_name_input_full_dlg_set_content();
        wzd_view_full_screen_dlg_show(FALSE);
                    
        c_timer_start(pt_input_page->h_show_dlg_timer, 
                      5000,
                      X_TIMER_FLAG_ONCE,
                      _wzd_page_tv_name_input_timer_show_dialog_nfy_fct,
                      NULL);
    }
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_device_name_input_get_page_info_data
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
INT32 wzd_page_tv_name_input_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data)
{    
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TITLE_DEVICE;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_DESC_DEVICE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = _wzd_page_tv_name_input_on_footer_nfy;
    pt_info_data->pf_return_nfy_fct        = _wzd_page_tv_name_input_return_nfy_cb;
    pt_info_data->pf_anim_finish_nfy_fct   = _wzd_page_tv_name_input_anim_finish_nfy;
   
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_page_tv_name_input_create;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_page_tv_name_input_dsty;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_page_tv_name_input_on_show;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_page_tv_name_input_on_hide;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_name_input_nfy_sel
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
INT32 wzd_page_tv_name_input_nfy_sel(UINT16               ui2_sel_idx,
                                     VOID*                pv_data,
                                     WZD_MSG_CUSTOM_T*    pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_name_input_enter_from_tuner_setup
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_name_input_enter_from_tuner_setup(UINT32 ui4_dev_type_sel_idx)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*  pt_this = &t_g_tv_name_input;

    /* here should updater the dev type by enter reason*/
    pt_this->e_name_input_enter_reason = NAME_INPUT_ENTER_REASON_TV_SETUP;
    pt_this->ui4_type_sel_idx = ui4_dev_type_sel_idx;
    
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_name_input_enter_from_tuner_setup_rf_scan
 *
 * Description: From tv turn setup RF channel scan complete: cable box/satellite->rf->scan complete->full dlg
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_name_input_enter_from_tuner_setup_rf_scan (VOID)
{
    WZD_TV_DEVICE_NAME_INPUT_MEMBER_T*    pt_this = &t_g_tv_name_input;

    /* here should updater the dev type by enter reason*/
    pt_this->e_name_input_enter_reason = NAME_INPUT_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE;
    
    wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );
	
    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_name_input_back_to_tuner_setup
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_name_input_back_to_tuner_setup(VOID)
{
    wzd_page_goto( WZD_PAGE_NAVI_PREV_PAGE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_device_name_input_unfocus_footer
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_device_name_input_unfocus_footer(VOID)
{
    return WZDR_OK;
}


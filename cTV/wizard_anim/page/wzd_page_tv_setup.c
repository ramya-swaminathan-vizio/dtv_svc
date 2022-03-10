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
#include "wizard_anim/page/wzd_page_tv_setup.h"
#include "wizard_anim/page/wzd_page_tv_remote_device_setup.h"
#include "wfrrc_interface.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "wdk/a_vkb.h"
#include "res/wdk/a_vkb_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_custom.h"
#include "wizard_anim/page/wzd_page_tv_name_input.h"

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
#include "c_cecm.h"
#include "nav/cec2/nav_cec.h"
#include "res/nav/cec2/nav_cec_custom.h"
#endif//APP_ARC_ONLY
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT
#ifdef RPC_ENABLE
#include "rpc.h"
#include "ri_desc.h"
#endif

#define WZD_TV_SETUP_CABLE_BOX_IDX      (1)
#define WZD_TV_SETUP_SATELLITE_IDX      (6)

#define	TV_SIGNAL_CABLE			(0)
#define	TV_SIGNAL_ANTENNA		(1)
#define	TV_SIGNAL_STATELINE		(2)
#define TV_UI_OFFSET			(300)

#define _GET_PHY_CH_NUM(v) (((v)>>16) & 0xFFFF)
#define _GET_VIR_CH_NUM(v) ( (v)      & 0xFFFF)

#define _SET_SCANE(start, end) ( ((start) << 16) | (end))

#define NTSC_TRSTRL_SVL_ID              ATSC_TRSTRL_SVL_ID
#define NTSC_TRSTRL_SVL_NAME            ATSC_TRSTRL_SVL_NAME
#define NTSC_TRSTRL_SVL_FILE            ATSC_TRSTRL_SVL_FILE
#define NTSC_TRSTRL_TUNER_NAME          SN_TUNER_GRP_0

#define NTSC_CABLE_SVL_ID               ATSC_CABLE_SVL_ID
#define NTSC_CABLE_SVL_NAME             ATSC_CABLE_SVL_NAME
#define NTSC_CABLE_SVL_FILE             ATSC_CABLE_SVL_FILE
#define NTSC_CABLE_TUNER_NAME           SN_TUNER_GRP_0

typedef enum _WZD_TV_SIG_SEL_BOX_BTN_INDEX_T
{
    WZD_TV_SIG_SEL_BOX_BTN_01 = 0,
    WZD_TV_SIG_SEL_BOX_BTN_02,
    WZD_TV_SIG_SEL_BOX_BTN_03,
    WZD_TV_SIG_SEL_BOX_BTN_04,
    WZD_TV_SIG_SEL_BOX_BTN_COUNT  /* 4 */
}WZD_TV_SIG_SEL_BOX_BTN_INDEX_T;

typedef enum TV_SETUP_STATE
{
	TV_SETUP_STATE_HIDE = 0,
	TV_SETUP_STATE_CHOOSE_SIG,
	TV_SETUP_STATE_ANTENNA_BEGIN_SCAN,
	TV_SETUP_STATE_ANTENNA_SCANNING,
	TV_SETUP_STATE_SELECT_CABLE_DEVICE,
	TV_SETUP_STATE_WALL_BEGIN_SCAN,
	TV_SETUP_STATE_WALL_SCANNING,
	TV_SETUP_STATE_COMPLETE,
	TV_SETUP_STATE_LAST_VALID_ITEM
}TV_SETUP_STATE;

typedef enum TV_SETUP_SIG_TYPE
{
	TV_SETUP_SIG_TYPE_CABLE = 0,
	TV_SETUP_SIG_TYPE_ANTENNA,
	TV_SETUP_SIG_TYPE_SATELLITE_BOX,
	TV_SETUP_SIG_TYPE_LAST_VALID_ITEM
}TV_SETUP_SIG_TYPE;

typedef enum TV_SETUP_CABLE_DEVICE_TYPE
{
	CABLE_DEVICE_TYPE_CABLE_BOX = 0,
	CABLE_DEVICE_TYPE_DIRECT_WALL,
	CABLE_DEVICE_TYPE_CABLE_BOX_RF,
	CABLE_DEVICE_TYPE_LAST_VALID_ITEM
}TV_SETUP_CABLE_DEVICE_TYPE;

typedef enum _TV_SETUP_ENTER_REASON
{
   TV_SETUP_ENTER_REASON_NONE = 0,
   TV_SETUP_ENTER_REASON_TV_REMOTE_DEVICE_SETUP_RF,
   TV_SETUP_ENTER_REASON_TV_NAME_INPUT_RF,
   TV_SETUP_ENTER_REASON_TV_NAME_INPUT_INPUT,
   TV_SETUP_ENTER_REASON_TV_REMOTE_DEVICE_SETUP_INPUT,
   TV_SETUP_ENTER_REASON_LAST_VALID_ITEM
}TV_SETUP_ENTER_REASON;

typedef enum {
    WZD_TV_SETUP_CALLBACK_PARAM_NOTHING = 0,
    WZD_TV_SETUP_CALLBACK_PARAM_FIRST,
    WZD_TV_SETUP_CALLBACK_PARAM_SECOND,
} WZD_TV_SETUP_CALLBACK_PARAM;

typedef struct _TV_SETUP_RF_SCAN_T
{
	UINT16              ui2_scanning_type;
    UINT16              ui2_status;                 /* the scan status */
    INT32               i4_prev_progress;

    /* Svl Builder of the NTSC AIR */
    BOOL                b_ntsc_air_scanning;
    HANDLE_T            h_ntsc_air;

    /* Svl Builder of the ATSC CABLE */
    BOOL                b_ntsc_cable_scanning;
    HANDLE_T            h_ntsc_cable;

    /* Svl Builder of the ATSC AIR */
    BOOL                b_atsc_air_scanning;
    HANDLE_T            h_atsc_air;

    /* Svl Builder of the ATSC CABLE */
    BOOL                b_atsc_cable_scanning;
    HANDLE_T            h_atsc_cable;

	HANDLE_T			h_timer_scan;
}TV_SETUP_RF_SCAN_T;

typedef struct _SB_SCAN_INFO_T {
	HANDLE_T			h_builder;
    INT32               i4_vir_ch_num;
    INT32               i4_phy_ch_num;
    INT32               i4_phy_ch_ttl;
	BOOL        		b_done;         /* if b_done is TRUE, it means that the builder has
                                   					sent a SB_REASON_COMPLETE, SB_REASON_CANCEL, 
                                   					SB_REASON_ABORT message */
}   SB_SCAN_INFO_T;

typedef struct _WZD_TV_SETUP_MEMBER_T
{
	HANDLE_T                    h_select_cable_device;  /* Select Cable device */
	HANDLE_T                    h_intro_text;           /* Scan introduction text */
	HANDLE_T                    h_dlg;                  /* Message box */
	HANDLE_T                    h_last_focused_wdg;
	WZD_FOOTER_BTN_INDEX_T      e_focused_footer;
	TV_SETUP_STATE              e_state;
	TV_SETUP_STATE              e_pre_state;            /* Pre state, for VKB return pre state*/
	TV_SETUP_SIG_TYPE           e_sig_type;             /* Signal type to scan */
	TV_SETUP_CABLE_DEVICE_TYPE  e_cable_device_type;    /* Cable Device Type */

	UINT16                      ui2_ch_num;             /* Total scanned channel number */

	BOOL                    	b_is_db_locked;

	WZD_FOOTER_BTN_INDEX_T      e_selected_footer;

	HANDLE_T                    h_img_demo_pic;      /* picture, show in right side */
	HANDLE_T                    h_img_right_hlt_IO_icons;
	UINT8						ui1_hlt_sel_box_indx;
	TV_SETUP_ENTER_REASON   	e_tv_setup_enter_reason;
	HANDLE_T					h_amp_plug_dlg_timer;
	BOOL                        b_is_choose_sig[WZD_TV_SIG_SEL_BOX_BTN_COUNT]; /* temp show checked mark */
    BOOL                        b_sig_show_checkbox; /* for choose signal type */
    UINT8                       ui1_sig_sel_box_idx; /* for choose signal type */
	BOOL                        b_is_choose_cable_dev[WZD_TV_SIG_SEL_BOX_BTN_COUNT]; /* for cable box device */
    BOOL                        b_cable_dev_show_checkbox;/* for cable box device */
    UINT8                       ui1_cable_dev_sel_box_idx; /* for cable box device */
}WZD_TV_SETUP_MEMBER_T;

typedef struct _WZD_TV_SETUP_ANIM_COND_CB_DATA_T
{
    HANDLE_T                        h_anim_handle;                  /* the animation handle which callback to AP */
    WZD_TV_SETUP_CALLBACK_PARAM     e_param;                        /* private tag data */
} WZD_TV_SETUP_ANIM_COND_CB_DATA_T;

static WZD_TV_SETUP_ANIM_COND_CB_DATA_T at_anim_cb_icon_data;
static WZD_TV_SETUP_ANIM_COND_CB_DATA_T at_anim_cb_txt_data;



static WZD_TV_SETUP_MEMBER_T gt_tv_setup;
static TV_SETUP_RF_SCAN_T	 gt_tv_setup_rf_scan;
static SB_SCAN_INFO_T   	 t_scan_info_atv;
static SB_SCAN_INFO_T  		 t_scan_info_dtv;
/*satellite scan: antenna ATV + DTV && cable ATV + DTV*/
static SB_SCAN_INFO_T   	 t_scan_info_atv_sat;
static SB_SCAN_INFO_T  		 t_scan_info_dtv_sat;

static UINT32                ui4_g_pre_focused_sb_idx = 0;

static INT32 _wzd_page_tv_setup_update_by_state(BOOL b_repaint);

static INT32 _wzd_page_tv_setup_help_lst_update (
					TV_SETUP_STATE			e_tv_setup_state,
            		BOOL           			b_repaint);

static INT32 _wzd_page_tv_setup_sel_box_initial_theme (const UINT32 ui4_btn_idx);
static INT32 _wzd_page_tv_setup_sel_box_hl_theme (const UINT32 ui4_btn_idx);

INT32 wzd_page_tv_setup_rf_scan_sat_cable_start (VOID);

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sel_box_move_cond_cb_handler
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
static VOID _wzd_page_tv_setup_sel_box_move_cond_cb_handler(
    VOID*               pv_data,
    SIZE_T              z_data_size)
{
    WZD_TV_SETUP_ANIM_COND_CB_DATA_T*             pt_anim_cb_data = NULL;
    WZD_TV_SETUP_CALLBACK_PARAM                   param;
    WZD_TV_SETUP_MEMBER_T*                        pt_this = &gt_tv_setup;

    do
    {
        /* Check input arguments */
        if ((NULL == pv_data) ||
            (z_data_size != sizeof(WZD_TV_SETUP_ANIM_COND_CB_DATA_T)))
        {
            break;
        }

        pt_anim_cb_data = (WZD_TV_SETUP_ANIM_COND_CB_DATA_T*)pv_data;

        if (NULL_HANDLE == pt_anim_cb_data->h_anim_handle)
        {
            break;
        }

        param = pt_anim_cb_data->e_param;
        
        c_wgl_set_alpha(pt_anim_cb_data->h_anim_handle, 255);

        /* Stop animation */
        if (WZD_TV_SETUP_CALLBACK_PARAM_SECOND == param)
        {
            c_thread_delay(200);
            
            if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_pre_state)
            {
                if (TV_SETUP_SIG_TYPE_SATELLITE_BOX == pt_this->e_sig_type)
                {
                    if (a_cfg_custom_get_wifi_remote_support())
                    {
                        wzd_page_tv_remote_device_setup_enter_from_tuner_setup(WZD_TV_SETUP_SATELLITE_IDX);
                    }
                    else
                    {
                        wzd_page_tv_name_input_enter_from_tuner_setup(WZD_TV_SETUP_SATELLITE_IDX);
                    }
                }
                else
                {
                    _wzd_page_tv_setup_update_by_state( TRUE );
                }
            }
            else if (TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_pre_state)
            {
                if (CABLE_DEVICE_TYPE_DIRECT_WALL == pt_this->e_cable_device_type)
                {
                    _wzd_page_tv_setup_update_by_state( TRUE );
                }
                else
                {
                    if (a_cfg_custom_get_wifi_remote_support())
                    {
                        wzd_page_tv_remote_device_setup_enter_from_tuner_setup(WZD_TV_SETUP_CABLE_BOX_IDX);
                    }
                    else
                    {
                        wzd_page_tv_name_input_enter_from_tuner_setup(WZD_TV_SETUP_CABLE_BOX_IDX);
                    }
                }
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
            at_anim_cb_icon_data.e_param = WZD_TV_SETUP_CALLBACK_PARAM_NOTHING;
        }
        else if (pt_anim_cb_data->h_anim_handle == at_anim_cb_txt_data.h_anim_handle)
        {
            at_anim_cb_txt_data.h_anim_handle = NULL_HANDLE;
            at_anim_cb_txt_data.e_param = WZD_TV_SETUP_CALLBACK_PARAM_NOTHING;
        }
        
    } while(0);
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sel_box_move_cb_fct
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
static INT32 _wzd_page_tv_setup_sel_box_move_cb_fct(
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
        DBG_INFO( ("[WZD_TV_SETUP] ANIM_TOTAL_END Line@%d.\n", __LINE__));

        /* Async invoke callback handler function */        
        wzd_async_invoke(
                _wzd_page_tv_setup_sel_box_move_cond_cb_handler, 
                pv_tag, 
                sizeof(WZD_TV_SETUP_ANIM_COND_CB_DATA_T), 
                FALSE);
    }

    return WZDR_OK;   
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sel_box_set_checkmark
 *
 * Description: set checkmark(icon1) and move icon2 and text when select the box.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_sel_box_set_checkmark (UINT8 ui1_sel_box_idx)
{
    WGL_IMG_INFO_T                      t_img_info = {0};
    GL_RECT_T                           t_rect = {0};
    WGL_HIMG_TPL_T                      h_checkmark_icon = NULL_HANDLE;
    ANIM_DATA_MOVE_T                    t_anim_data_icon;
    ANIM_DATA_MOVE_T                    t_anim_data_txt;
    HANDLE_T                            h_icon1 = NULL_HANDLE;
    HANDLE_T                            h_icon2 = NULL_HANDLE;
    HANDLE_T                            h_text = NULL_HANDLE;
    
    c_memset(&t_anim_data_icon, 0, sizeof(ANIM_DATA_MOVE_T));
    c_memset(&t_anim_data_txt, 0, sizeof(ANIM_DATA_MOVE_T));

    h_checkmark_icon = h_g_wzd_img_checkmark_green_large;

    /* move icon position */
    h_icon1 = wzd_view_sel_box_get_icon_1_handle(ui1_sel_box_idx);

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
    h_icon2 = wzd_view_sel_box_get_icon_2_handle(ui1_sel_box_idx);

    t_anim_data_icon.ui2_total_steps = 6;
    t_anim_data_icon.ui2_frame_interval = 50;

    if(TV_SETUP_SIG_TYPE_ANTENNA == ui1_sel_box_idx)
    {
        t_anim_data_icon.i2_start_x = WZD_SEL_BOX_BTN_ICON_2_X;
        t_anim_data_icon.i2_start_y = WZD_SEL_BOX_BTN_ICON_2_Y - 5 * WZD_UI_RATIO_W;
        t_anim_data_icon.i2_end_x   = WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_X;
        t_anim_data_icon.i2_end_y   = WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y2;
    }
    else
    {
        t_anim_data_icon.i2_start_x = WZD_SEL_BOX_BTN_ICON_2_X;
        t_anim_data_icon.i2_start_y = WZD_SEL_BOX_BTN_ICON_2_Y;
        t_anim_data_icon.i2_end_x   = WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_X;
        t_anim_data_icon.i2_end_y   = WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y1;
    }
    
    /* set h_icon2 move down callback data */
    c_memset(&at_anim_cb_icon_data, 0, sizeof(WZD_TV_SETUP_ANIM_COND_CB_DATA_T));
    at_anim_cb_icon_data.h_anim_handle = h_icon2;
    at_anim_cb_icon_data.e_param = WZD_TV_SETUP_CALLBACK_PARAM_FIRST;

    a_wzd_anim_set_cb(
               h_icon2,
               _wzd_page_tv_setup_sel_box_move_cb_fct,
               (void *)&at_anim_cb_icon_data);

    a_wzd_anim_move_ex(h_icon2, &t_anim_data_icon, TRUE);

    /* start text move animation */
    h_text = wzd_view_sel_box_get_txt_handle(ui1_sel_box_idx);

    t_anim_data_txt.ui2_total_steps = 6;
    t_anim_data_txt.ui2_frame_interval = 50;

    t_anim_data_txt.i2_start_x = WZD_SEL_BOX_BTN_TXT_X;
    t_anim_data_txt.i2_start_y = WZD_SEL_BOX_BTN_TXT_Y + 1 * WZD_UI_RATIO_W ;
    t_anim_data_txt.i2_end_x   = WZD_TV_SETUP_SEL_BOX_BTN_TXT_MOVE_DOWN_X;
    t_anim_data_txt.i2_end_y   = WZD_TV_SETUP_SEL_BOX_BTN_TXT_MOVE_DOWN_Y;
    
    /* set h_text move down callback data */
    c_memset(&at_anim_cb_txt_data, 0, sizeof(WZD_TV_SETUP_ANIM_COND_CB_DATA_T));
    at_anim_cb_txt_data.h_anim_handle = h_text;
    at_anim_cb_txt_data.e_param = WZD_TV_SETUP_CALLBACK_PARAM_SECOND;
    
    /* set h_text move down callback */
    a_wzd_anim_set_cb(
               h_text,
               _wzd_page_tv_setup_sel_box_move_cb_fct,
               (void *)&at_anim_cb_txt_data);

    a_wzd_anim_move_ex(h_text, &t_anim_data_txt, TRUE);
    
    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_choose_sig_update_checkmark
 *
 * Description: update the position of checkmark(icon1)/icon2/txt on select signal type page
 *              when get focus.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_choose_sig_update_checkmark (VOID)
{
    WZD_TV_SETUP_MEMBER_T*              pt_this = &gt_tv_setup;
    WGL_IMG_INFO_T 					    t_img_info = {0};
    GL_RECT_T      					    t_rect_icon = {0};
    GL_RECT_T      					    t_rect_txt = {0};
	WGL_HIMG_TPL_T 					    h_checkmark_icon = NULL_HANDLE;
    HANDLE_T       					    h_icon1 = NULL_HANDLE;
    HANDLE_T       					    h_icon2 = NULL_HANDLE;
	HANDLE_T    					    h_text = NULL_HANDLE;
    BOOL         					    b_sel_status = FALSE;
    BOOL         					    b_sel_curr_same = FALSE;
    INT32                               i4_ret = WZDR_OK;
    UINT8                               ui1_idx = 0;

    if (!pt_this->b_sig_show_checkbox)
    {
        return 0;
    }

    for (ui1_idx = 0; ui1_idx < WZD_TV_SIG_SEL_BOX_BTN_COUNT; ui1_idx++)
    {
        if (pt_this->b_is_choose_sig[ui1_idx])
        {
            b_sel_status = TRUE;
            if(pt_this->ui1_sig_sel_box_idx == ui1_idx)
            {
                b_sel_curr_same = TRUE;
                break;
            }
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
            pt_this->b_sig_show_checkbox = FALSE;
            h_checkmark_icon = NULL_HANDLE;
        }
    }
    else
    {
        pt_this->b_sig_show_checkbox = FALSE;
        pt_this->ui1_sig_sel_box_idx = 0;
        h_checkmark_icon = NULL_HANDLE;
    }
    
    /*update sel box icon2 and text position */
    if (b_sel_status)
    {
        if (pt_this->b_sig_show_checkbox)
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_sig_sel_box_idx);
            if (TV_SETUP_SIG_TYPE_ANTENNA == pt_this->ui1_sig_sel_box_idx)
            {
                SET_RECT_BY_SIZE(&t_rect_icon,
                                    WZD_SEL_BOX_BTN_ICON_2_X,
                                    WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y2,
                                    WZD_SEL_BOX_BTN_ICON_2_W,
                                    WZD_SEL_BOX_BTN_ICON_2_H);
            }
            else
            {
                
                SET_RECT_BY_SIZE(&t_rect_icon,
                                    WZD_SEL_BOX_BTN_ICON_2_X,
                                    WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y1,
                                    WZD_SEL_BOX_BTN_ICON_2_W,
                                    WZD_SEL_BOX_BTN_ICON_2_H);
            }
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_sig_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_SEL_BOX_BTN_TXT_X,
                             WZD_TV_SETUP_SEL_BOX_BTN_TXT_MOVE_DOWN_Y,
                             WZD_SEL_BOX_BTN_TXT_W,
                             WZD_SEL_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        else
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_sig_sel_box_idx);
            
            if (TV_SETUP_SIG_TYPE_ANTENNA == pt_this->ui1_sig_sel_box_idx)
            {
                SET_RECT_BY_SIZE(&t_rect_icon,
                                WZD_SEL_BOX_BTN_ICON_2_X,
                                WZD_SEL_BOX_BTN_ICON_2_Y - 5 * WZD_UI_RATIO_W,
                                WZD_SEL_BOX_BTN_ICON_2_W,
                                WZD_SEL_BOX_BTN_ICON_2_H);
            }
            else
            {
                
                SET_RECT_BY_SIZE(&t_rect_icon,
                                WZD_SEL_BOX_BTN_ICON_2_X,
                                WZD_SEL_BOX_BTN_ICON_2_Y,
                                WZD_SEL_BOX_BTN_ICON_2_W,
                                WZD_SEL_BOX_BTN_ICON_2_H);
            }
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_sig_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_SEL_BOX_BTN_TXT_X,
                             WZD_SEL_BOX_BTN_TXT_Y + (1 * WZD_UI_RATIO_W),
                             WZD_SEL_BOX_BTN_TXT_W,
                             WZD_SEL_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
    }

    /* update checkmark icon position*/ 
    if (pt_this->b_sig_show_checkbox)
    {
        h_icon1 = wzd_view_sel_box_get_icon_1_handle(pt_this->ui1_sig_sel_box_idx);
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
 * Name: _wzd_page_tv_setup_cable_dev_update_checkmark
 *
 * Description: update the position of checkmark(icon1)/icon2/txt on select cable device type
 *              when get the focus.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_cable_dev_update_checkmark (VOID)
{
    WZD_TV_SETUP_MEMBER_T*              pt_this = &gt_tv_setup;
    WGL_IMG_INFO_T 					    t_img_info = {0};
    GL_RECT_T      					    t_rect_icon = {0};
    GL_RECT_T      					    t_rect_txt = {0};
	WGL_HIMG_TPL_T 					    h_checkmark_icon = NULL_HANDLE;
    HANDLE_T       					    h_icon1 = NULL_HANDLE;
    HANDLE_T       					    h_icon2 = NULL_HANDLE;
	HANDLE_T    					    h_text = NULL_HANDLE;
    BOOL         					    b_sel_status = FALSE;
    BOOL         					    b_sel_curr_same = FALSE;
    INT32                               i4_ret = WZDR_OK;
    UINT8                               ui1_idx = 0;

    if (!pt_this->b_cable_dev_show_checkbox)
    {
        return 0;
    }

    for (ui1_idx = 0; ui1_idx < WZD_TV_SIG_SEL_BOX_BTN_COUNT; ui1_idx++)
    {
        if (pt_this->b_is_choose_cable_dev[ui1_idx])
        {
            b_sel_status = TRUE;
            if(pt_this->ui1_cable_dev_sel_box_idx == ui1_idx)
            {
                b_sel_curr_same = TRUE;
                break;
            }
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
            pt_this->b_cable_dev_show_checkbox = FALSE;
            h_checkmark_icon = NULL_HANDLE;
        }
    }
    else
    {
        pt_this->b_cable_dev_show_checkbox = FALSE;
        pt_this->ui1_cable_dev_sel_box_idx = 0;
        h_checkmark_icon = NULL_HANDLE;
    }
    
    /*update sel box icon2 and text position */
    if (b_sel_status)
    {
        if (pt_this->b_cable_dev_show_checkbox)
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_cable_dev_sel_box_idx);
            if (CABLE_DEVICE_TYPE_DIRECT_WALL == pt_this->ui1_cable_dev_sel_box_idx)
            {
                SET_RECT_BY_SIZE(&t_rect_icon,
                                    WZD_SEL_BOX_BTN_ICON_2_X,
                                    WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y2,
                                    WZD_SEL_BOX_BTN_ICON_2_W,
                                    WZD_SEL_BOX_BTN_ICON_2_H);
            }
            else
            {
                
                SET_RECT_BY_SIZE(&t_rect_icon,
                                    WZD_SEL_BOX_BTN_ICON_2_X,
                                    WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y1,
                                    WZD_SEL_BOX_BTN_ICON_2_W,
                                    WZD_SEL_BOX_BTN_ICON_2_H);
            }
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_cable_dev_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_SEL_BOX_BTN_TXT_X,
                             WZD_TV_SETUP_SEL_BOX_BTN_TXT_MOVE_DOWN_Y,
                             WZD_SEL_BOX_BTN_TXT_W,
                             WZD_SEL_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
        else
        {
            /* move icon2 position */
            h_icon2 = wzd_view_sel_box_get_icon_2_handle(pt_this->ui1_cable_dev_sel_box_idx);
            
            if (CABLE_DEVICE_TYPE_DIRECT_WALL == pt_this->ui1_cable_dev_sel_box_idx)
            {
                SET_RECT_BY_SIZE(&t_rect_icon,
                                WZD_SEL_BOX_BTN_ICON_2_X,
                                WZD_SEL_BOX_BTN_ICON_2_Y - 5 * WZD_UI_RATIO_W,
                                WZD_SEL_BOX_BTN_ICON_2_W,
                                WZD_SEL_BOX_BTN_ICON_2_H);
            }
            else
            {
                
                SET_RECT_BY_SIZE(&t_rect_icon,
                                WZD_SEL_BOX_BTN_ICON_2_X,
                                WZD_SEL_BOX_BTN_ICON_2_Y,
                                WZD_SEL_BOX_BTN_ICON_2_W,
                                WZD_SEL_BOX_BTN_ICON_2_H);
            }
            RET_ON_ERR (c_wgl_move(h_icon2,
                                   &t_rect_icon,
                                   WGL_NO_AUTO_REPAINT));
            
            /* move txt position */
            h_text = wzd_view_sel_box_get_txt_handle(pt_this->ui1_cable_dev_sel_box_idx);
            SET_RECT_BY_SIZE(&t_rect_txt,
                             WZD_SEL_BOX_BTN_TXT_X,
                             WZD_SEL_BOX_BTN_TXT_Y + (1 * WZD_UI_RATIO_W),
                             WZD_SEL_BOX_BTN_TXT_W,
                             WZD_SEL_BOX_BTN_TXT_H);
            
            RET_ON_ERR (c_wgl_move(h_text,
                                   &t_rect_txt,
                                   WGL_NO_AUTO_REPAINT));
        }
    }

    /* update checkmark icon position*/ 
    if (pt_this->b_cable_dev_show_checkbox)
    {
        h_icon1 = wzd_view_sel_box_get_icon_1_handle(pt_this->ui1_cable_dev_sel_box_idx);
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
 * Name: _wzd_page_tv_setup_reset_scanning_flag
 *
 * Description: The function reset the flag used for identify the status of sb-scanning.
 *
 * Inputs:
 *
 * Outputs: - 
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_setup_reset_scanning_flag (HANDLE_T   h_builder)
{

    if (h_builder == gt_tv_setup_rf_scan.h_ntsc_air)
    {
        gt_tv_setup_rf_scan.b_ntsc_air_scanning = FALSE;
    }
    else if (h_builder == gt_tv_setup_rf_scan.h_ntsc_cable)
    {
        gt_tv_setup_rf_scan.b_ntsc_cable_scanning = FALSE;
    }
    else if (h_builder == gt_tv_setup_rf_scan.h_atsc_air)
    {
        gt_tv_setup_rf_scan.b_atsc_air_scanning = FALSE;
    }
    else if (h_builder == gt_tv_setup_rf_scan.h_atsc_cable)
    {
        gt_tv_setup_rf_scan.b_atsc_cable_scanning = FALSE;
    }
    else
    {
        /* do nothing */
    }
}
/*-----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_is_scanning
 *
 * Description: This API checks whether the sb is scanning or not.
 *
 * Inputs: 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
BOOL wzd_page_tv_setup_is_scanning (VOID)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	
    if (pt_this->e_sig_type == TV_SETUP_SIG_TYPE_CABLE)
    {
        if (gt_tv_setup_rf_scan.b_ntsc_cable_scanning || gt_tv_setup_rf_scan.b_atsc_cable_scanning)
        {
            return TRUE;
        }
    }
    else if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)/* (ui2_scanning_type == WZD_SB_SCANNING_CABLE) */
    {
        if (gt_tv_setup_rf_scan.b_ntsc_cable_scanning || gt_tv_setup_rf_scan.b_atsc_cable_scanning ||
			gt_tv_setup_rf_scan.b_ntsc_air_scanning || gt_tv_setup_rf_scan.b_atsc_air_scanning)
        {
            return TRUE;
        }
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_get_scan_status
 *
 * Description: This API for querying the current scan status.
 *
 * Inputs: - 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
UINT16 wzd_page_tv_setup_get_scan_status (VOID)
{
    return gt_tv_setup_rf_scan.ui2_status;
}


/*-----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_set_scan_status
 *
 * Description: This API for seting the current scan status.
 *
 * Inputs: - 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
VOID wzd_page_tv_setup_set_scan_status   (UINT16  ui2_scan_status)
{
    gt_tv_setup_rf_scan.ui2_status = ui2_scan_status;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_scan_nfy_fct
 *
 * Description: The callback function of SVL Builder while scanning.
 *
 * Inputs:
 *
 * Outputs: - 
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_setup_scan_nfy_fct(HANDLE_T          h_builder,
                          UINT32            ui4_nfy_reason,
                          INT32             i4_nfy_data,
                          VOID*             pv_nfy_tag)
{
	WZD_TV_SETUP_MEMBER_T*      		pt_this = &gt_tv_setup;
	
    if (gt_tv_setup_rf_scan.ui2_status == WZD_SB_STATUS_SCANNING)
    {
        SB_SCAN_INFO_T*     pt_scan_info = (SB_SCAN_INFO_T*) pv_nfy_tag;

        if (ui4_nfy_reason & SB_REASON_PROGRESS)
        {
            SB_NFY_MSG_T    t_sb_nfy;

			c_memset(&t_sb_nfy, 0, sizeof(SB_NFY_MSG_T));

            pt_scan_info->i4_vir_ch_num += _GET_VIR_CH_NUM(i4_nfy_data);
            pt_scan_info->i4_phy_ch_num += 1;
            pt_scan_info->i4_phy_ch_ttl  = _GET_PHY_CH_NUM(i4_nfy_data);

            if(pt_scan_info->i4_phy_ch_num > pt_scan_info->i4_phy_ch_ttl)
            {
                pt_scan_info->i4_phy_ch_num = pt_scan_info->i4_phy_ch_ttl;
            }
			if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_CABLE)
			{
				t_sb_nfy.i4_atv_ch_num = t_scan_info_atv.i4_vir_ch_num;
				t_sb_nfy.i4_dtv_ch_num = t_scan_info_dtv.i4_vir_ch_num;
				t_sb_nfy.b_paint_info  = (_GET_VIR_CH_NUM(i4_nfy_data) > 0);
				t_sb_nfy.i4_progress   = (t_scan_info_atv.i4_phy_ch_num + t_scan_info_dtv.i4_phy_ch_num) * 100 /
									(t_scan_info_atv.i4_phy_ch_ttl + t_scan_info_dtv.i4_phy_ch_ttl);
			}
			else if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)
			{
		        t_sb_nfy.i4_atv_ch_num = t_scan_info_atv.i4_vir_ch_num + t_scan_info_atv_sat.i4_vir_ch_num;
	            t_sb_nfy.i4_dtv_ch_num = t_scan_info_dtv.i4_vir_ch_num + t_scan_info_dtv_sat.i4_vir_ch_num;
	            t_sb_nfy.b_paint_info  = (_GET_VIR_CH_NUM(i4_nfy_data) > 0);
	            t_sb_nfy.i4_progress   = (t_scan_info_atv.i4_phy_ch_num + t_scan_info_dtv.i4_phy_ch_num + t_scan_info_atv_sat.i4_phy_ch_num + t_scan_info_dtv_sat.i4_phy_ch_num) * 100 /
                                    (t_scan_info_atv.i4_phy_ch_ttl + t_scan_info_dtv.i4_phy_ch_ttl + t_scan_info_atv_sat.i4_phy_ch_ttl + t_scan_info_dtv_sat.i4_phy_ch_ttl);
			}

            /* make sure that the max progress is 99 before scanning is complete. */
            t_sb_nfy.i4_progress = (t_sb_nfy.i4_progress > 99) ? 99 : t_sb_nfy.i4_progress;

            if (t_sb_nfy.b_paint_info == TRUE ||
                t_sb_nfy.i4_progress != gt_tv_setup_rf_scan.i4_prev_progress)
            {
                gt_tv_setup_rf_scan.i4_prev_progress = t_sb_nfy.i4_progress;
                wzd_app_send_msg (WZD_MSG_SB_SCAN_PROGRESS, & t_sb_nfy, sizeof(SB_NFY_MSG_T));
            }
        }
        else if (ui4_nfy_reason & SB_REASON_COMPLETE)
        {
			DBG_INFO( ("\n####%s(%d)SB_REASON_COMPLETE\n",__FUNCTION__,__LINE__));
			
        	pt_scan_info->b_done = TRUE;
			
            _wzd_page_tv_setup_reset_scanning_flag (h_builder);
			
        	if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)
    		{
    			if(!t_scan_info_atv_sat.b_done && !t_scan_info_dtv_sat.b_done && t_scan_info_atv.b_done && t_scan_info_dtv.b_done)
				{
				    /* set antenna scan completed first */
                    a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);

					wzd_page_tv_setup_rf_scan_sat_cable_start();
					return;
				}
    		}

        	/*cable scan for sat*/
        	if((t_scan_info_atv_sat.i4_vir_ch_num + t_scan_info_dtv_sat.i4_vir_ch_num)>=1)
    		{	
    			INT32 i4_num = 0;
				i4_num = t_scan_info_atv_sat.i4_vir_ch_num + t_scan_info_dtv_sat.i4_vir_ch_num;
    			a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
				DBG_INFO( ("\n####%s(%d)SAT cable scan num=%d\n",__FUNCTION__,__LINE__,i4_num));
    		}

            if (!wzd_page_tv_setup_is_scanning())
            {
                gt_tv_setup_rf_scan.ui2_status = WZD_SB_STATUS_COMPLETE;
                wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);
            }
        }
        else if (ui4_nfy_reason & SB_REASON_CANCEL)
        {
        	pt_scan_info->b_done = TRUE;
            gt_tv_setup_rf_scan.ui2_status = WZD_SB_STATUS_CANCEL;
            wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);
        }
        else    /* SB_RESON_ABORT & unknown */
        {
			pt_scan_info->b_done = TRUE;
			
            _wzd_page_tv_setup_reset_scanning_flag (h_builder);

            gt_tv_setup_rf_scan.ui2_status = WZD_SB_STATUS_ERROR;
            wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0);
        }
    }
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_update_sb_snk_name
 *
 * Description: This API performs the RF start-scan task.
 *
 * Inputs:     
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_update_sb_snk_name(
    HANDLE_T    h_sb)
{
    INT32   i4_ret;
    CHAR    s_snk_name[SVCTX_SNK_NAME_MAX_SIZE + 1] = SN_PRES_MAIN_DISPLAY;
    SIZE_T  z_size = (SIZE_T)c_strlen(s_snk_name);

    /* set sync name to sb */
    i4_ret = c_sb_set(h_sb,
                      SB_KEY_TYPE_SET_TVD_SNK_NAME,
                      NULL,
                      z_size,
                      s_snk_name);
    if(i4_ret < 0)
    {
        return WZDR_FAIL;
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sb_nfy_fct
 *
 * Description: The callback function of SVL Builder.
 *      
 * Inputs:
 *      
 * Outputs:
 *
 * Returns: 
 *----------------------------------------------------------------------------*/ 
static VOID _wzd_page_tv_setup_sb_nfy_fct (HANDLE_T          h_builder,
                         SB_COND_T         e_builder_cond,
                         VOID*             pv_nfy_tag)
{
        /* do nothing */
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sb_init
 *
 * Description: The function initiates the sb builders.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_sb_init (VOID)
{
    SB_COND_T e_cond;

    /* Open SVL Builder of the NTSC AIR */
    if (gt_tv_setup_rf_scan.h_ntsc_air == NULL_HANDLE)
    {
        WZD_UTIL_NTSC_OPEN_DATA_T   t_sb_ntsc_air_data;
        c_memset(&t_sb_ntsc_air_data, 0, sizeof(WZD_UTIL_NTSC_OPEN_DATA_T));
    
        t_sb_ntsc_air_data.ui2_svl_id    = NTSC_TRSTRL_SVL_ID;   
        t_sb_ntsc_air_data.ps_svl_name   = NTSC_TRSTRL_SVL_NAME;  
        t_sb_ntsc_air_data.ps_file_name  = NTSC_TRSTRL_SVL_FILE; 
        t_sb_ntsc_air_data.ps_tuner_name = NTSC_TRSTRL_TUNER_NAME;
        t_sb_ntsc_air_data.b_use_orig    = TRUE;
    
        RET_ON_ERR (c_sb_open_builder(WZD_UTIL_NTSC_AIR_ENG_NAME, 
                                      & t_sb_ntsc_air_data, 
                                      NULL, _wzd_page_tv_setup_sb_nfy_fct, & gt_tv_setup_rf_scan.h_ntsc_air, & e_cond));
    }

    /* Open SVL Builder of the ATSC CABLE */
    if (gt_tv_setup_rf_scan.h_ntsc_cable == NULL_HANDLE)
    {
        WZD_UTIL_NTSC_OPEN_DATA_T   t_sb_ntsc_cable_data;
        c_memset(&t_sb_ntsc_cable_data, 0, sizeof(WZD_UTIL_NTSC_OPEN_DATA_T));
    
        t_sb_ntsc_cable_data.ui2_svl_id    = NTSC_CABLE_SVL_ID;   
        t_sb_ntsc_cable_data.ps_svl_name   = NTSC_CABLE_SVL_NAME;  
        t_sb_ntsc_cable_data.ps_file_name  = NTSC_CABLE_SVL_FILE; 
        t_sb_ntsc_cable_data.ps_tuner_name = NTSC_CABLE_TUNER_NAME;
        t_sb_ntsc_cable_data.b_use_orig    = TRUE;
    
        RET_ON_ERR (c_sb_open_builder(WZD_UTIL_NTSC_CABLE_ENG_NAME, 
                                      & t_sb_ntsc_cable_data, 
                                      NULL, _wzd_page_tv_setup_sb_nfy_fct, & gt_tv_setup_rf_scan.h_ntsc_cable, & e_cond));
    }

    /* Open SVL Builder of the ATSC AIR */
    if (gt_tv_setup_rf_scan.h_atsc_air == NULL_HANDLE)
    {
        WZD_UTIL_ATSC_AIR_OPEN_DATA_T   t_sb_atsc_air_data;
        c_memset(&t_sb_atsc_air_data, 0, sizeof(WZD_UTIL_ATSC_AIR_OPEN_DATA_T));
    
        t_sb_atsc_air_data.ui2_svl_id    = ATSC_TRSTRL_SVL_ID;   
        t_sb_atsc_air_data.ps_svl_name   = ATSC_TRSTRL_SVL_NAME;  
        t_sb_atsc_air_data.ps_file_name  = ATSC_TRSTRL_SVL_FILE; 
        t_sb_atsc_air_data.ps_tuner_name = ATSC_TRSTRL_TUNER_NAME;
        t_sb_atsc_air_data.b_use_orig    = TRUE;
    
        RET_ON_ERR (c_sb_open_builder(WZD_UTIL_ATSC_AIR_ENG_NAME, 
                                      & t_sb_atsc_air_data, 
                                      NULL, _wzd_page_tv_setup_sb_nfy_fct, & gt_tv_setup_rf_scan.h_atsc_air, & e_cond));
    }

    /* Open SVL Builder of the ATSC CABLE */
    if (gt_tv_setup_rf_scan.h_atsc_cable == NULL_HANDLE)
    {
        WZD_UTIL_ATSC_CABLE_OPEN_DATA_T   t_sb_atsc_cable_data;
        c_memset(&t_sb_atsc_cable_data, 0, sizeof(WZD_UTIL_ATSC_CABLE_OPEN_DATA_T));
    
        t_sb_atsc_cable_data.ui2_svl_id    = ATSC_CABLE_SVL_ID;   
        t_sb_atsc_cable_data.ps_svl_name   = ATSC_CABLE_SVL_NAME;  
        t_sb_atsc_cable_data.ps_file_name  = ATSC_CABLE_SVL_FILE; 
        t_sb_atsc_cable_data.ps_tuner_name = ATSC_CABLE_TUNER_NAME;
        t_sb_atsc_cable_data.b_use_orig    = TRUE;
    
        RET_ON_ERR (c_sb_open_builder(WZD_UTIL_ATSC_CABLE_ENG_NAME, 
                                      & t_sb_atsc_cable_data, 
                                      NULL, _wzd_page_tv_setup_sb_nfy_fct, & gt_tv_setup_rf_scan.h_atsc_cable, & e_cond));
    }

    gt_tv_setup_rf_scan.ui2_status   = WZD_SB_STATUS_WAIT;

    return 0;
}
/*-----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_scan_cancel
 *
 * Description: This API performs the cancel-scan task.
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_setup_scan_cancel (VOID)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
    
    if (pt_this->e_sig_type == TV_SETUP_SIG_TYPE_CABLE)
    {
        if (gt_tv_setup_rf_scan.b_ntsc_cable_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: ATV NTSC CABLE Svl Builder.\r\n"));
            c_sb_cancel_scan(gt_tv_setup_rf_scan.h_ntsc_cable);
            gt_tv_setup_rf_scan.b_ntsc_cable_scanning = FALSE;
        }

        if (gt_tv_setup_rf_scan.b_atsc_cable_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: DTV ATSC CABLE Svl Builder.\r\n"));
            c_sb_cancel_scan(gt_tv_setup_rf_scan.h_atsc_cable);
            gt_tv_setup_rf_scan.b_atsc_cable_scanning = FALSE;
        }
    }
	else if (pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)
    {
        if (gt_tv_setup_rf_scan.b_ntsc_air_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: ATV NTSC AIR Svl Builder.\r\n"));
            c_sb_cancel_scan(gt_tv_setup_rf_scan.h_ntsc_air);
            gt_tv_setup_rf_scan.b_ntsc_air_scanning = FALSE;
        }

        if (gt_tv_setup_rf_scan.b_atsc_air_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: DTV ATSC AIR Svl Builder.\r\n"));
            c_sb_cancel_scan(gt_tv_setup_rf_scan.h_atsc_air);
            gt_tv_setup_rf_scan.b_atsc_air_scanning = FALSE;
        }

		if (gt_tv_setup_rf_scan.b_ntsc_cable_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: ATV NTSC CABLE Svl Builder.\r\n"));
            c_sb_cancel_scan(gt_tv_setup_rf_scan.h_ntsc_cable);
            gt_tv_setup_rf_scan.b_ntsc_cable_scanning = FALSE;
        }

        if (gt_tv_setup_rf_scan.b_atsc_cable_scanning)
        {
            DBG_INFO(("<WZD> scan cancel: DTV ATSC CABLE Svl Builder.\r\n"));
            c_sb_cancel_scan(gt_tv_setup_rf_scan.h_atsc_cable);
            gt_tv_setup_rf_scan.b_atsc_cable_scanning = FALSE;
        }
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_rf_scan_start
 *
 * Description: This API performs the RF start-scan task.
 *
 * Inputs: ui2_scanning_type    the Cable Box or Satellite for scanning. 
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_setup_rf_scan_start (VOID)
{
    INT32                               i4_rc;
    BOOL                                b_successful = FALSE;
    SB_COND_T                           e_cond;

    WZD_UTIL_NTSC_SCAN_DATA_T           t_ntsc_air_scan_data;
	WZD_UTIL_NTSC_SCAN_DATA_T           t_ntsc_cable_scan_data;
    WZD_UTIL_ATSC_AIR_SCAN_DATA_T       t_atsc_air_scan_data;
    WZD_UTIL_ATSC_CABLE_SCAN_DATA_T     t_atsc_cable_scan_data;
	WZD_TV_SETUP_MEMBER_T*      		pt_this = &gt_tv_setup;

    if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)
	{
        c_svl_clean (t_g_wzd.h_air_svl);
        c_tsl_clean (t_g_wzd.h_air_tsl);
#ifndef APP_LOL_NWL_DISABLE
        c_nwl_clean (t_g_wzd.h_air_nwl);
        c_lol_clean (t_g_wzd.h_air_lol);
#endif

        c_svl_clean (t_g_wzd.h_cab_svl);
        c_tsl_clean (t_g_wzd.h_cab_tsl);
#ifndef APP_LOL_NWL_DISABLE
        c_nwl_clean (t_g_wzd.h_cab_nwl);
        c_lol_clean (t_g_wzd.h_cab_lol);
#endif
	}
    else if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_CABLE)
    {
        c_svl_clean (t_g_wzd.h_cab_svl);
        c_tsl_clean (t_g_wzd.h_cab_tsl);
#ifndef APP_LOL_NWL_DISABLE
        c_nwl_clean (t_g_wzd.h_cab_nwl);
        c_lol_clean (t_g_wzd.h_cab_lol);
#endif
    }

    /* initialize sb builders */
    i4_rc = _wzd_page_tv_setup_sb_init ();
    if (i4_rc != WZDR_OK)
    {
        gt_tv_setup_rf_scan.ui2_status = WZD_SB_STATUS_ERROR;
        return WZDR_FAIL;
    }

    i4_rc = SBR_INV_ARG;

	//if (ui2_scanning_type == WZD_SB_SCANNING_CABLE)
	if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_CABLE)
    {
        DBG_INFO(("<WZD> scan start: ATV NTSC Cable Svl Builder.\r\n"));
		
		DBG_INFO( ("\n####%s(%d)CABLE-ATV\n",__FUNCTION__,__LINE__));
			
        _wzd_page_tv_setup_update_sb_snk_name(gt_tv_setup_rf_scan.h_ntsc_cable);

        c_memset(& t_ntsc_cable_scan_data, 0, sizeof(WZD_UTIL_NTSC_SCAN_DATA_T));
        t_ntsc_cable_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
        t_ntsc_cable_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_RANGE_RF_CHANNEL;
        t_ntsc_cable_scan_data.ui2_start_idx = 2; 
        t_ntsc_cable_scan_data.ui2_end_idx   = 5;

		t_scan_info_atv.h_builder = gt_tv_setup_rf_scan.h_ntsc_cable;

        RPC_ADD_REF_DESC(RPC_DEFAULT_ID, & t_ntsc_cable_scan_data, RPC_DESC_SB_NTSC_SCAN_DATA_T, NULL);        
        i4_rc = c_sb_start_scan(gt_tv_setup_rf_scan.h_ntsc_cable, 
                                 & t_ntsc_cable_scan_data, & t_scan_info_atv, _wzd_page_tv_setup_scan_nfy_fct, & e_cond);

        gt_tv_setup_rf_scan.b_ntsc_cable_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;


        DBG_INFO(("<WZD> scan start: DTV ATSC CABLE Svl Builder.\r\n"));

		DBG_INFO( ("\n####%s(%d)CABLE-DTV\n",__FUNCTION__,__LINE__));
		
        c_memset(& t_atsc_cable_scan_data, 0, sizeof(WZD_UTIL_ATSC_CABLE_SCAN_DATA_T));
        t_atsc_cable_scan_data.e_scan_type   = SB_CQAM_SCAN_TYPE_RANGE_RF_CHANNEL;
        t_atsc_cable_scan_data.ui4_scan_info = _SET_SCANE(2, 5); 
        t_atsc_cable_scan_data.ui1_freq_plan = WZD_UTIL_ATSC_CABLE_FREQ_PLAN;
        t_atsc_cable_scan_data.ui4_mod_mask  = WZD_UTIL_ATSC_CABLE_DEF_MOD_MASK;

		t_scan_info_dtv.h_builder = gt_tv_setup_rf_scan.h_atsc_cable;

        RPC_ADD_REF_DESC(RPC_DEFAULT_ID, & t_atsc_cable_scan_data, RPC_DESC_SB_CQAM_SCAN_DATA_T, NULL);     
        i4_rc = c_sb_start_scan(gt_tv_setup_rf_scan.h_atsc_cable, 
                                & t_atsc_cable_scan_data, & t_scan_info_dtv, _wzd_page_tv_setup_scan_nfy_fct, & e_cond);

        gt_tv_setup_rf_scan.b_atsc_cable_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;


        /* check the scan status */
        if (gt_tv_setup_rf_scan.b_ntsc_cable_scanning && gt_tv_setup_rf_scan.b_atsc_cable_scanning)
        {
            b_successful = TRUE;
        }
    }
	else if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)//if (ui2_scanning_type == WZD_SB_SCANNING_SAT)
	{
		/*air*/
		DBG_INFO(("<WZD>Scan Mode: NTSC/AIR\r\n"));
		DBG_INFO( ("\n####%s(%d)SAT-AIR-ATV\n",__FUNCTION__,__LINE__));
		
        /* udpate the sink name to builder */
        _wzd_page_tv_setup_update_sb_snk_name(gt_tv_setup_rf_scan.h_ntsc_air);

        /* start scan */
        c_memset(&t_ntsc_air_scan_data, 0, sizeof(SB_NTSC_SCAN_DATA_T));

        t_ntsc_air_scan_data.ui1_freq_plan = SB_NTSC_TER_FREQ_PLAN;
        t_ntsc_air_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_RANGE_RF_CHANNEL;
        t_ntsc_air_scan_data.ui2_start_idx = 21; 
        t_ntsc_air_scan_data.ui2_end_idx   = 69;

		t_scan_info_atv.h_builder = gt_tv_setup_rf_scan.h_ntsc_air;
		
		RPC_ADD_REF_DESC(RPC_DEFAULT_ID, & t_ntsc_air_scan_data, RPC_DESC_SB_NTSC_SCAN_DATA_T, NULL);
		i4_rc = c_sb_start_scan(gt_tv_setup_rf_scan.h_ntsc_air, 
								 & t_ntsc_air_scan_data, & t_scan_info_atv, _wzd_page_tv_setup_scan_nfy_fct, & e_cond);

		gt_tv_setup_rf_scan.b_ntsc_air_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;

		DBG_INFO(("<MENU>Scan Mode: ATSC/AIR\r\n"));
		DBG_INFO( ("\n####%s(%d)SAT-AIR-DTV\n",__FUNCTION__,__LINE__));

		c_memset(& t_atsc_air_scan_data, 0, sizeof(WZD_UTIL_ATSC_AIR_SCAN_DATA_T));
        t_atsc_air_scan_data.e_scan_type   = SB_ATSC_SCAN_TYPE_RANGE_RF_CHANNEL;   
        t_atsc_air_scan_data.ui4_scan_info = _SET_SCANE(21, 69);

		t_scan_info_dtv.h_builder = gt_tv_setup_rf_scan.h_atsc_air;

        RPC_ADD_REF_DESC(RPC_DEFAULT_ID, & t_atsc_air_scan_data, RPC_DESC_SB_ATSC_SCAN_DATA_T, NULL);
        i4_rc = c_sb_start_scan(gt_tv_setup_rf_scan.h_atsc_air, 
                                & t_atsc_air_scan_data, & t_scan_info_dtv, _wzd_page_tv_setup_scan_nfy_fct, & e_cond);

        gt_tv_setup_rf_scan.b_atsc_air_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;
		
	    /* check the scan status */
	    if (gt_tv_setup_rf_scan.b_ntsc_air_scanning && gt_tv_setup_rf_scan.b_atsc_air_scanning)
	    {
	        b_successful = TRUE;
	    }
    }

    if (!b_successful)
    {
        gt_tv_setup_rf_scan.ui2_status = WZD_SB_STATUS_ERROR;
        wzd_page_tv_setup_scan_cancel ();
        return WZDR_FAIL;
    }
	
    /* Init the scan relative data */
    t_scan_info_atv.i4_vir_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_num = 0;
    t_scan_info_atv.i4_phy_ch_ttl = 200;  /* assign a big enough value */
	t_scan_info_atv.b_done = FALSE;
    t_scan_info_dtv.i4_vir_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_num = 0;
    t_scan_info_dtv.i4_phy_ch_ttl = 200;  /* assign a big enough value */
	t_scan_info_dtv.b_done = FALSE;

	t_scan_info_atv_sat.i4_vir_ch_num = 0;
    t_scan_info_atv_sat.i4_phy_ch_num = 0;
    t_scan_info_atv_sat.i4_phy_ch_ttl = 200;  /* assign a big enough value */
	t_scan_info_atv_sat.b_done = FALSE;
    t_scan_info_dtv_sat.i4_vir_ch_num = 0;
    t_scan_info_dtv_sat.i4_phy_ch_num = 0;
    t_scan_info_dtv_sat.i4_phy_ch_ttl = 200;  /* assign a big enough value */
	t_scan_info_dtv_sat.b_done = FALSE;

    //gt_tv_setup_rf_scan.ui2_scanning_type = ui2_scanning_type;
    gt_tv_setup_rf_scan.ui2_status        = WZD_SB_STATUS_SCANNING;
    gt_tv_setup_rf_scan.i4_prev_progress  = 200;       /* assign a non-zero value */

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_rf_scan_start
 *
 * Description: This API performs the satellite cable RF start-scan task.
 *			 Due to satellite cable rf can start scan only after satellite air rf scan is complete.
 *
 * Inputs:  
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_page_tv_setup_rf_scan_sat_cable_start (VOID)
{
    INT32                               i4_rc;
    BOOL                                b_successful = FALSE;
    SB_COND_T                           e_cond;

	WZD_UTIL_NTSC_SCAN_DATA_T           t_ntsc_cable_scan_data;
    WZD_UTIL_ATSC_CABLE_SCAN_DATA_T     t_atsc_cable_scan_data;

    i4_rc = SBR_INV_ARG;

	/*satellite cable*/
    DBG_INFO(("<####WZD> scan start: ATV NTSC Cable Svl Builder.\r\n"));
	DBG_INFO( ("\n####%s(%d)SAT-CABLE-ATV\n",__FUNCTION__,__LINE__));

    _wzd_page_tv_setup_update_sb_snk_name(gt_tv_setup_rf_scan.h_ntsc_cable);

    c_memset(& t_ntsc_cable_scan_data, 0, sizeof(WZD_UTIL_NTSC_SCAN_DATA_T));
    t_ntsc_cable_scan_data.ui1_freq_plan = SB_NTSC_CAB_FREQ_PLAN_AUTO;
    t_ntsc_cable_scan_data.e_scan_type   = SB_NTSC_SCAN_TYPE_RANGE_RF_CHANNEL;
    t_ntsc_cable_scan_data.ui2_start_idx = 73; 
    t_ntsc_cable_scan_data.ui2_end_idx   = 125;

	t_scan_info_atv_sat.h_builder = gt_tv_setup_rf_scan.h_ntsc_cable;

    RPC_ADD_REF_DESC(RPC_DEFAULT_ID, & t_ntsc_cable_scan_data, RPC_DESC_SB_NTSC_SCAN_DATA_T, NULL);
    i4_rc = c_sb_start_scan(gt_tv_setup_rf_scan.h_ntsc_cable, 
                             & t_ntsc_cable_scan_data, & t_scan_info_atv_sat, _wzd_page_tv_setup_scan_nfy_fct, & e_cond);

    gt_tv_setup_rf_scan.b_ntsc_cable_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;

	DBG_INFO( ("\n####%s(%d)SAT-CABLE-DTV\n",__FUNCTION__,__LINE__));

	c_memset(& t_atsc_cable_scan_data, 0, sizeof(WZD_UTIL_ATSC_CABLE_SCAN_DATA_T));
	t_atsc_cable_scan_data.e_scan_type	 = SB_CQAM_SCAN_TYPE_RANGE_RF_CHANNEL;
	t_atsc_cable_scan_data.ui4_scan_info = _SET_SCANE(73, 125); 
	t_atsc_cable_scan_data.ui1_freq_plan = WZD_UTIL_ATSC_CABLE_FREQ_PLAN;
	t_atsc_cable_scan_data.ui4_mod_mask  = WZD_UTIL_ATSC_CABLE_DEF_MOD_MASK;

	t_scan_info_dtv_sat.h_builder = gt_tv_setup_rf_scan.h_atsc_cable;

	RPC_ADD_REF_DESC(RPC_DEFAULT_ID, & t_atsc_cable_scan_data, RPC_DESC_SB_CQAM_SCAN_DATA_T, NULL); 	
	i4_rc = c_sb_start_scan(gt_tv_setup_rf_scan.h_atsc_cable, 
							& t_atsc_cable_scan_data, & t_scan_info_dtv_sat, _wzd_page_tv_setup_scan_nfy_fct, & e_cond);

	gt_tv_setup_rf_scan.b_atsc_cable_scanning = (i4_rc == SBR_OK) ? TRUE : FALSE;

    /* check the scan status */
    if (gt_tv_setup_rf_scan.b_ntsc_cable_scanning && gt_tv_setup_rf_scan.b_atsc_cable_scanning)
    {
        b_successful = TRUE;
    }

    if (!b_successful)
    {
        gt_tv_setup_rf_scan.ui2_status = WZD_SB_STATUS_ERROR;
        wzd_page_tv_setup_scan_cancel ();
        return WZDR_FAIL;
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sel_box_nfy
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
static VOID _wzd_page_tv_setup_sel_box_nfy(
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2
                                         )
{
    WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	UINT32 						ui4_idx = 0;
    BOOL                        b_set_checkmark = FALSE;

    switch( ui4_msg )
    {
		case WZD_SEL_BOX_MSG_ITEM_FOCUSED:
            if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state)
            {
                pt_this->ui1_sig_sel_box_idx = (UINT8)(UINT32)pv_param1;
                _wzd_page_tv_setup_choose_sig_update_checkmark();
            }
            else if (TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
            {
                pt_this->ui1_cable_dev_sel_box_idx = (UINT8)(UINT32)pv_param1;
                _wzd_page_tv_setup_cable_dev_update_checkmark();
            }
            DBG_INFO( ( "[WZD][SB] %d select box button is focused.\n", (UINT32)pv_param1 ));
			_wzd_page_tv_setup_sel_box_hl_theme((UINT32)pv_param1);
            break;

		case WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED:
            DBG_INFO( ( "[WZD][SB] %d select box button is lose focused.\n", (UINT32)pv_param1 ));
			_wzd_page_tv_setup_sel_box_initial_theme((UINT32)pv_param1);
            break;
			
        case WZD_SEL_BOX_MSG_KEY_INPUT:
            DBG_INFO( ( "[WZD][SB] Receive key input, current index = %d\n", (UINT32)pv_param2 ));
			ui4_idx = (UINT32)pv_param2;

            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
                    {
						if( (WZD_TV_SIG_SEL_BOX_BTN_INDEX_T)pv_param2 < WZD_TV_SIG_SEL_BOX_BTN_COUNT )
                        {
							if(pt_this->e_state == TV_SETUP_STATE_CHOOSE_SIG)
							{
							    b_set_checkmark = FALSE;
                                
							    /*temporary show check mark*/
                				c_memset(pt_this->b_is_choose_sig, 0, WZD_TV_SIG_SEL_BOX_BTN_COUNT);
                				pt_this->b_is_choose_sig[ui4_idx] = TRUE;
                				
                                pt_this->e_sig_type = ui4_idx;
                                pt_this->ui1_sig_sel_box_idx = (UINT8)ui4_idx;
                                
                                /* need move icon2/text widget animation */
                                if (!pt_this->b_sig_show_checkbox)
                                {
                                    pt_this->b_sig_show_checkbox = TRUE;
                                    _wzd_page_tv_setup_sel_box_set_checkmark(pt_this->ui1_sig_sel_box_idx);
                                    b_set_checkmark = TRUE;
                                }
                                
								if(ui4_idx == TV_SIGNAL_CABLE)
								{
								    DBG_INFO( ("\n####%s(%d)ui4_idx == TV_SIGNAL_CABLE\n",__FUNCTION__,__LINE__));
									pt_this->e_sig_type = TV_SETUP_SIG_TYPE_CABLE;
									pt_this->e_state = TV_SETUP_STATE_SELECT_CABLE_DEVICE;
									pt_this->e_pre_state = TV_SETUP_STATE_CHOOSE_SIG;
								}
								else if(ui4_idx == TV_SIGNAL_ANTENNA)
								{
									pt_this->e_sig_type = TV_SETUP_SIG_TYPE_ANTENNA;
									pt_this->e_state = TV_SETUP_STATE_ANTENNA_BEGIN_SCAN;
									pt_this->e_pre_state = TV_SETUP_STATE_CHOOSE_SIG;
								}
								else if(ui4_idx == TV_SIGNAL_STATELINE)
								{   
									pt_this->e_pre_state = TV_SETUP_STATE_CHOOSE_SIG;
                                    
    								if (!b_set_checkmark)
                                    {                        
    									pt_this->e_sig_type = TV_SETUP_SIG_TYPE_SATELLITE_BOX;
    									
                                        if (a_cfg_custom_get_wifi_remote_support())
                                        {
                                            wzd_page_tv_remote_device_setup_enter_from_tuner_setup(WZD_TV_SETUP_SATELLITE_IDX);
                                        }
    									else
    									{
    										wzd_page_tv_name_input_enter_from_tuner_setup(WZD_TV_SETUP_SATELLITE_IDX);
    									}
                                            return;
                                        }
								}

                                if (!b_set_checkmark)
                                {
    			                    _wzd_page_tv_setup_update_by_state( TRUE );
                                }
                                
							}
							else if(pt_this->e_state == TV_SETUP_STATE_SELECT_CABLE_DEVICE)
							{
							    b_set_checkmark = FALSE;
                                
							    /*temporary show check mark*/
                				c_memset(pt_this->b_is_choose_cable_dev, 0, WZD_TV_SIG_SEL_BOX_BTN_COUNT);
                				pt_this->b_is_choose_cable_dev[ui4_idx] = TRUE;
                                pt_this->ui1_cable_dev_sel_box_idx = (UINT8)ui4_idx;
                                
                                /* need move icon2/text widget animation */
                                if (!pt_this->b_cable_dev_show_checkbox)
                                {
                                    pt_this->b_cable_dev_show_checkbox = TRUE;
                                    _wzd_page_tv_setup_sel_box_set_checkmark(pt_this->ui1_cable_dev_sel_box_idx);
                                    b_set_checkmark = TRUE;
                                }
                                
								if( 0 == ui4_idx )//cable box
				                {
                                    pt_this->e_pre_state = TV_SETUP_STATE_SELECT_CABLE_DEVICE;

                                    if (!b_set_checkmark)
                                    {   
                                        if (a_cfg_custom_get_wifi_remote_support())
                                        {
                                            wzd_page_tv_remote_device_setup_enter_from_tuner_setup(WZD_TV_SETUP_CABLE_BOX_IDX);
                                        }
    									else
    									{
    										wzd_page_tv_name_input_enter_from_tuner_setup(WZD_TV_SETUP_CABLE_BOX_IDX);
    									}
                                        return;
                                    }
				                }
				                else
				                {

									pt_this->e_sig_type = TV_SETUP_SIG_TYPE_CABLE;
									pt_this->e_state = TV_SETUP_STATE_WALL_BEGIN_SCAN;
									pt_this->e_pre_state = TV_SETUP_STATE_SELECT_CABLE_DEVICE;
				                    pt_this->e_cable_device_type = CABLE_DEVICE_TYPE_DIRECT_WALL;

                                    if (!b_set_checkmark)
                                    {            
    				                    _wzd_page_tv_setup_update_by_state( TRUE );
                                    }
				                }
							}
                        }
                    }
                    break;
				case BTN_CURSOR_DOWN:
                    {
						/* save the lasted focus */
                        ui4_g_pre_focused_sb_idx = ui4_idx;
                        wzd_view_sel_box_lose_focus(ui4_g_pre_focused_sb_idx, FALSE);

						wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE);    /* Set focus to footer. */
            			wzd_view_main_frm_repaint();
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
 * Name: _wzd_page_tv_setup_sig_intro_set_text
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
static INT32 _wzd_page_tv_setup_sig_intro_set_text( BOOL b_repaint )

{
    WZD_TV_SETUP_MEMBER_T*          pt_this = &gt_tv_setup;
    UINT16                          ui2_text_id = 0;

    if ( (TV_SETUP_STATE_ANTENNA_BEGIN_SCAN == pt_this->e_state) ||
		 (TV_SETUP_STATE_ANTENNA_SCANNING == pt_this->e_state))    /* signal: antenna*/
    {
        if( TV_SETUP_SIG_TYPE_CABLE == pt_this->e_sig_type )
        {
            ui2_text_id = MLM_WZD_KEY_ANNOUNCE_TEXT_CAB;
        }
        else if( TV_SETUP_SIG_TYPE_ANTENNA == pt_this->e_sig_type )
        {
            ui2_text_id = MLM_WZD_KEY_ANNOUNCE_TEXT_ANT;
        }
		else
        {
            ui2_text_id = MLM_WZD_KEY_ANNOUNCE_TEXT_SATE;
        }
    }
    else if ( TV_SETUP_STATE_WALL_BEGIN_SCAN == pt_this->e_state ||
			 ((TV_SETUP_STATE_WALL_SCANNING == pt_this->e_state)) )  /* Signal: cable, cable device:through wall*/
    {
        if (CABLE_DEVICE_TYPE_DIRECT_WALL == pt_this->e_cable_device_type)
        {
        	DBG_INFO( ("\n####%s(%d)CABLE_DEVICE_TYPE_DIRECT_WALL\n",__FUNCTION__,__LINE__));
            ui2_text_id = MLM_WZD_KEY_ANNOUNCE_TEXT;
        }
		else if(CABLE_DEVICE_TYPE_CABLE_BOX_RF == pt_this->e_cable_device_type)
		{
			if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_CABLE)
			{
				DBG_INFO( ("\n####%s(%d)CABLE_DEVICE_TYPE_CABLE_BOX_RF\n",__FUNCTION__,__LINE__));
				ui2_text_id = MLM_WZD_KEY_ANNOUNCE_TEXT_CAB;
			}
			else if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)
			{
				DBG_INFO( ("\n####%s(%d)SATELLITE_BOX_RF\n",__FUNCTION__,__LINE__));
				ui2_text_id = MLM_WZD_KEY_ANNOUNCE_TEXT_SAT;
			}
		}
        else
        {
            ui2_text_id = MLM_WZD_KEY_EMPTY;
        }
    }
	else if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state) 	/* Signal: cable, cable device:cable box */
	{
		if (a_cfg_custom_get_wifi_remote_support())
        {
            ui2_text_id = MLM_WZD_KEY_TV_SETUP_DESC_TXT2;	
        }
		else
		{
			ui2_text_id = MLM_WZD_KEY_EMPTY;
		}
		
	}

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_intro_text,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (WZD_TEXT(ui2_text_id)),
                      WGL_PACK (c_uc_w2s_strlen (WZD_TEXT(ui2_text_id)))));

    if( b_repaint )
    {
        RET_ON_ERR (c_wgl_repaint (pt_this->h_intro_text, NULL, TRUE));
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_create_txt
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
static INT32 _wzd_page_tv_setup_create_txt (
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

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sel_box_initial_theme
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx		Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_sel_box_initial_theme (const UINT32 ui4_btn_idx)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	HANDLE_T 					h_sb_txt = NULL_HANDLE;
	HANDLE_T 					h_sb_icon = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_2nd = NULL_HANDLE;
	GL_RECT_T           		t_rect = {0};
	WGL_COLOR_INFO_T  			t_color_txt;
	WGL_FONT_INFO_T    			t_fnt_info;
	WGL_IMG_INFO_T				t_img_info;
    HANDLE_T                    h_sb_icon_1st = NULL_HANDLE;

	WGL_HIMG_TPL_T   			ah_img_cho_sig_nor[3] = {
															h_g_wzd_img_device_cableBox,
															h_g_wzd_img_device_antenna,
															h_g_wzd_img_device_satellite
															};
	WGL_HIMG_TPL_T   			ah_img_sel_cab_dev_nor[2] = {
															h_g_wzd_img_device_cableBox,
															h_g_wzd_img_device_coax,
															};

	WGL_HIMG_TPL_T      		h_checkmark_icon = NULL_HANDLE;

	c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	c_memset (&t_color_txt, 0, sizeof(WGL_COLOR_INFO_T));
	c_memset (&t_img_info, 0, sizeof(WGL_IMG_INFO_T));

	/* initial font info */	
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

	if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state ||
		TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
	{
		/* 
			text theme
		*/
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_TXT_X,
						WZD_SEL_BOX_BTN_TXT_Y + (1 * WZD_UI_RATIO_W),
						WZD_SEL_BOX_BTN_TXT_W,
						WZD_SEL_BOX_BTN_TXT_H);
		RET_ON_ERR (c_wgl_move(h_sb_txt,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		/* set alignment */
    	RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_ALIGN,
						WGL_PACK(WGL_AS_CENTER_TOP),
						NULL));

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_COLOR,
						WGL_PACK (WGL_CLR_TEXT),
						WGL_PACK (&t_color_txt)));

		/* update font size */
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_FONT,
						WGL_PACK (&t_fnt_info),
						NULL));

        
        /* update icon 1 theme */
        h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui4_btn_idx);
        
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
        
        if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state)
        {
            pt_this->b_sig_show_checkbox = FALSE;
        }
        else if (TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
        {
            pt_this->b_cable_dev_show_checkbox = FALSE;
        }
        
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
        t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;
        
        c_wgl_do_cmd(h_sb_icon_1st,
                     WGL_CMD_GL_SET_IMAGE,
                     WGL_PACK(WGL_IMG_FG),
                     WGL_PACK(&t_img_info));   
		/* 
			icon theme
		*/
		h_sb_icon = wzd_view_sel_box_get_icon_2_handle(ui4_btn_idx);
		
		/* move position */
		if (ui4_btn_idx == 1)
		{
			SET_RECT_BY_SIZE(&t_rect,
							WZD_SEL_BOX_BTN_ICON_2_X,
							WZD_SEL_BOX_BTN_ICON_2_Y - (5 * WZD_UI_RATIO_W),
							WZD_SEL_BOX_BTN_ICON_2_W,
							WZD_SEL_BOX_BTN_ICON_2_H);
		}
		else
		{
			SET_RECT_BY_SIZE(&t_rect,
							WZD_SEL_BOX_BTN_ICON_2_X,
							WZD_SEL_BOX_BTN_ICON_2_Y,
							WZD_SEL_BOX_BTN_ICON_2_W,
							WZD_SEL_BOX_BTN_ICON_2_H);
		} 
		RET_ON_ERR (c_wgl_move(h_sb_icon,
						&t_rect,
						WGL_NO_AUTO_REPAINT));
		
		RET_ON_ERR (c_wgl_do_cmd(h_sb_icon,
							  WGL_CMD_ICON_SET_ALIGN,
							  WGL_PACK(WGL_AS_CENTER_CENTER),
							  NULL));


	
	if(TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state)
	{
		t_img_info.e_type = WGL_IMG_SET_STANDARD;
		t_img_info.u_img_data.t_standard.t_disable = ah_img_cho_sig_nor[ui4_btn_idx];
		t_img_info.u_img_data.t_standard.t_enable = ah_img_cho_sig_nor[ui4_btn_idx];
		t_img_info.u_img_data.t_standard.t_highlight = ah_img_cho_sig_nor[ui4_btn_idx];
	}
	else
	{
		t_img_info.e_type = WGL_IMG_SET_STANDARD;
		t_img_info.u_img_data.t_standard.t_disable = ah_img_sel_cab_dev_nor[ui4_btn_idx];
		t_img_info.u_img_data.t_standard.t_enable = ah_img_sel_cab_dev_nor[ui4_btn_idx];
		t_img_info.u_img_data.t_standard.t_highlight = ah_img_sel_cab_dev_nor[ui4_btn_idx];
	}
	
	
	h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(ui4_btn_idx);
	RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2nd,
							  WGL_CMD_GL_SET_IMAGE,
							  WGL_PACK(WGL_IMG_FG),
							  WGL_PACK(&t_img_info)));

	}
	else
	{
		/* nothing todo */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_sel_box_hl_theme
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx		Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_sel_box_hl_theme (const UINT32 ui4_btn_idx)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
    HANDLE_T 					h_sb_txt = NULL_HANDLE;
	WGL_COLOR_INFO_T  			t_color_txt;
	WGL_FONT_INFO_T    			t_fnt_info;
    HANDLE_T					h_sb_icon_2nd = NULL_HANDLE;
	WGL_IMG_INFO_T				t_img_info;
	WGL_HIMG_TPL_T   			ah_img_cho_sig_hlt[3] = {
															h_g_wzd_img_device_cableBox_hlt,
															h_g_wzd_img_device_antenna_hlt,
															h_g_wzd_img_device_satellite_hlt
															};
	WGL_HIMG_TPL_T   			ah_img_sel_cab_dev_hlt[2] = {
															h_g_wzd_img_device_cableBox_hlt,
															h_g_wzd_img_device_coax_hlt,
															};

	c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	c_memset (&t_color_txt, 0, sizeof(WGL_COLOR_INFO_T));
	c_memset (&t_img_info, 0, sizeof(WGL_IMG_INFO_T));

	if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state ||
		TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
	{
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);

		c_wgl_do_cmd (h_sb_txt,
                      WGL_CMD_GL_SET_COLOR,
                      WGL_PACK (WGL_CLR_TEXT),
                      WGL_PACK (&t_color_txt));

		/* update font size */
	    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

	    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
		
		/* set font size */
		c_wgl_do_cmd (h_sb_txt,
                      WGL_CMD_GL_SET_FONT,
                      WGL_PACK (&t_fnt_info),
                      NULL);
		
		if(TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state)
		{
			t_img_info.e_type = WGL_IMG_SET_STANDARD;
			t_img_info.u_img_data.t_standard.t_disable = ah_img_cho_sig_hlt[ui4_btn_idx];
			t_img_info.u_img_data.t_standard.t_enable = ah_img_cho_sig_hlt[ui4_btn_idx];
			t_img_info.u_img_data.t_standard.t_highlight = ah_img_cho_sig_hlt[ui4_btn_idx];
		}
		else
		{
			t_img_info.e_type = WGL_IMG_SET_STANDARD;
			t_img_info.u_img_data.t_standard.t_disable = ah_img_sel_cab_dev_hlt[ui4_btn_idx];
			t_img_info.u_img_data.t_standard.t_enable = ah_img_sel_cab_dev_hlt[ui4_btn_idx];
			t_img_info.u_img_data.t_standard.t_highlight = ah_img_sel_cab_dev_hlt[ui4_btn_idx];
		}
		
		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(ui4_btn_idx);
		RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2nd,
								  WGL_CMD_GL_SET_IMAGE,
								  WGL_PACK(WGL_IMG_FG),
								  WGL_PACK(&t_img_info)));
	}
	else
	{
		/* todo */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_initial_sel_box_content
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
static INT32 _wzd_page_tv_setup_initial_sel_box_content (VOID)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	UINT8				   		ui1_sel_box = 0;
	WGL_IMG_INFO_T      		t_img_info;
	HANDLE_T 					h_sb_txt = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_1st = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_2nd = NULL_HANDLE;
    HANDLE_T                    h_checkmark_icon = NULL_HANDLE;

	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));

	if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state)
	{
		/* initial select box theme */
		for (ui1_sel_box = 0; ui1_sel_box < 3; ui1_sel_box++)
		{
			RET_ON_ERR (_wzd_page_tv_setup_sel_box_initial_theme(ui1_sel_box));
            
            h_checkmark_icon = NULL_HANDLE;
            
            /* set sel box icon 1 */
            h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui1_sel_box);

            if (pt_this->b_is_choose_sig[ui1_sel_box])
            {
                if(pt_this->ui1_sig_sel_box_idx == ui1_sel_box)
                {
                    h_checkmark_icon = h_g_wzd_img_checkmark_green_large;
                }
            }
        
            t_img_info.e_type = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
            t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
            t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;
        
            c_wgl_do_cmd(h_sb_icon_1st,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));  
		}

		/*BTN_1*/
		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(0);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

		t_img_info.e_type = WGL_IMG_SET_STANDARD;
		t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_img_device_cableBox;
		t_img_info.u_img_data.t_standard.t_enable = h_g_wzd_img_device_cableBox;
		t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_device_cableBox_hlt;

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(WZD_TV_SIG_SEL_BOX_BTN_01);
		RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2nd,
								  WGL_CMD_GL_SET_IMAGE,
								  WGL_PACK(WGL_IMG_FG),
								  WGL_PACK(&t_img_info)));

		h_sb_txt = wzd_view_sel_box_get_txt_handle(0);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_TEXT,
						WZD_TEXT(MLM_WZD_KEY_TUNER_2),
						WGL_PACK ((UINT16)0xFFFF)));

		/*BTN_2*/
		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(1);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

		t_img_info.e_type = WGL_IMG_SET_STANDARD;
		t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_img_device_antenna;
		t_img_info.u_img_data.t_standard.t_enable = h_g_wzd_img_device_antenna;
		t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_device_antenna_hlt;

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(1);
		RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2nd,
								  WGL_CMD_GL_SET_IMAGE,
								  WGL_PACK(WGL_IMG_FG),
								  WGL_PACK(&t_img_info)));

		h_sb_txt = wzd_view_sel_box_get_txt_handle(1);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_TEXT,
						WZD_TEXT(MLM_WZD_KEY_TUNER_1),
						WGL_PACK ((UINT16)0xFFFF)));

		/*BTN_3*/
		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(2);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

		t_img_info.e_type = WGL_IMG_SET_STANDARD;
		t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_img_device_satellite;
		t_img_info.u_img_data.t_standard.t_enable = h_g_wzd_img_device_satellite;
		t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_device_satellite_hlt;

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(2);
		RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2nd,
								  WGL_CMD_GL_SET_IMAGE,
								  WGL_PACK(WGL_IMG_FG),
								  WGL_PACK(&t_img_info)));

		h_sb_txt = wzd_view_sel_box_get_txt_handle(2);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_TEXT,
						WZD_TEXT(MLM_WZD_KEY_TUNER_3),
						WGL_PACK ((UINT16)0xFFFF)));

	}
	else if (TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
	{
		/* initial select box theme */
		for (ui1_sel_box = 0; ui1_sel_box < 2; ui1_sel_box++)
		{
			RET_ON_ERR (_wzd_page_tv_setup_sel_box_initial_theme(ui1_sel_box));
            
            /* set sel box icon 1 */
            h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui1_sel_box);

            if (pt_this->b_is_choose_cable_dev[ui1_sel_box])
            {
                if(pt_this->ui1_cable_dev_sel_box_idx == ui1_sel_box)
                {
                    h_checkmark_icon = h_g_wzd_img_checkmark_green_large;
                }
            }
        
            t_img_info.e_type = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_disable = h_checkmark_icon;
            t_img_info.u_img_data.t_standard.t_enable = h_checkmark_icon;
            t_img_info.u_img_data.t_standard.t_highlight = h_checkmark_icon;
        
            c_wgl_do_cmd(h_sb_icon_1st,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));  
		}

		/*BTN_1*/
		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(0);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

		t_img_info.e_type = WGL_IMG_SET_STANDARD;
	    t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_img_device_cableBox;
	    t_img_info.u_img_data.t_standard.t_enable = h_g_wzd_img_device_cableBox;
	    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_device_cableBox_hlt;

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(WZD_TV_SIG_SEL_BOX_BTN_01);
		RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2nd,
								  WGL_CMD_GL_SET_IMAGE,
								  WGL_PACK(WGL_IMG_FG),
								  WGL_PACK(&t_img_info)));

		h_sb_txt = wzd_view_sel_box_get_txt_handle(0);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_TEXT,
						WZD_TEXT(MLM_WZD_KEY_DEVICE_SETUP_TYPE_CABLE_BOX),
						WGL_PACK ((UINT16)0xFFFF)));

		/*BTN_2*/
		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(1);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

		t_img_info.e_type = WGL_IMG_SET_STANDARD;
	    t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_img_device_coax;
	    t_img_info.u_img_data.t_standard.t_enable = h_g_wzd_img_device_coax;
	    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_device_coax_hlt;

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(1);
		RET_ON_ERR ( c_wgl_do_cmd(h_sb_icon_2nd,
								  WGL_CMD_GL_SET_IMAGE,
								  WGL_PACK(WGL_IMG_FG),
								  WGL_PACK(&t_img_info)));

		h_sb_txt = wzd_view_sel_box_get_txt_handle(1);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_TEXT,
						WZD_TEXT(MLM_WZD_KEY_TUNER_CABLE_WALL),
						WGL_PACK ((UINT16)0xFFFF)));
	}
	else
	{
		/* do something */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_create_sel_box
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
static INT32 _wzd_page_tv_setup_create_sel_box (VOID)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
    WZD_VIEW_SEL_BOX_INFO_T    	t_sel_box_info;

	/* reset previous focused select box button */
    ui4_g_pre_focused_sb_idx = 0;

    c_memset(&t_sel_box_info, 0 , sizeof(WZD_VIEW_SEL_BOX_INFO_T));

	if ( TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state )
	{
		t_sel_box_info.ui4_index_total 		= 3;
	}
	else if(TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
	{
		t_sel_box_info.ui4_index_total 		= 2;
	}
	else
	{
		t_sel_box_info.ui4_index_total 		= 0;
	}

    t_sel_box_info.pf_data_chg_nfy 		= _wzd_page_tv_setup_sel_box_nfy;

    wzd_view_sel_box_set_info_data (&t_sel_box_info);

	_wzd_page_tv_setup_initial_sel_box_content();

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_help_lst_update
 *
 * Description: The function updates help information.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_tv_setup_help_lst_update (
					TV_SETUP_STATE			e_tv_setup_state,
            		BOOL           			b_repaint)
{
	UINT8		ui1_btn_num = 0;
    BOOL    	b_btn_1st = FALSE;
    BOOL    	b_btn_2nd = FALSE;
	UTF16_T*    pw2s_text_1st = NULL;
	UTF16_T*    pw2s_text_2nd = NULL;

	if (e_tv_setup_state == TV_SETUP_STATE_CHOOSE_SIG)
	{
		ui1_btn_num 	= 1;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_HELP_SKIP);
	}
	else if (e_tv_setup_state == TV_SETUP_STATE_SELECT_CABLE_DEVICE)
	{
		ui1_btn_num 	= 1;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_HELP_BACK);
	}
	else if (e_tv_setup_state == TV_SETUP_STATE_ANTENNA_BEGIN_SCAN ||
		e_tv_setup_state == TV_SETUP_STATE_WALL_BEGIN_SCAN)
	{
		ui1_btn_num		= 2;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_MSG_SCAN_BEGIN);
		
        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_NETWORK_VKB_CANCEL);
	}
	else if (e_tv_setup_state == TV_SETUP_STATE_ANTENNA_SCANNING ||
		e_tv_setup_state == TV_SETUP_STATE_WALL_SCANNING)
	{
		ui1_btn_num		= 2;

		b_btn_1st 		= FALSE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_MSG_SCAN_BEGIN);
		
        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_MSG_SCAN_STOP);
	}
	else
	{
		ui1_btn_num 	= 0;
	}

	/* set footer frame visibility */
	if (ui1_btn_num == 0)
	{
		SHOW_ON_ERR (wzd_view_footer_set_visibility(FALSE));
	}
	else
	{
		SHOW_ON_ERR (wzd_view_footer_set_visibility(TRUE));
	}

	/* set footer button num */
	SHOW_ON_ERR (wzd_view_footer_set_btn_num(ui1_btn_num));

	/* update 1st footer button */
	SHOW_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, pw2s_text_1st));
	SHOW_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, b_btn_1st));

	/* update 2nd footer button */
	SHOW_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_02, pw2s_text_2nd));
	SHOW_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, b_btn_2nd));

	/* update footer button navigation */
    SHOW_ON_ERR (wzd_view_footer_update_btn_navigation());

	if (b_repaint)
	{
		SHOW_ON_ERR (wzd_view_footer_frm_repaint());
	}

    return WZDR_OK;;
}


/*----------------------------------------------------------------------------
* Name: wzd_page_tv_setup_enter_from_tv_remote_device_setup_rf
*
* Description: from tv_remote_device_setup page to tv tuner setup page afer select cable box -> RF.
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/
INT32 wzd_page_tv_setup_enter_from_tv_remote_device_setup_rf(UINT32  ui4_dev_type_sel_idx)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;

	pt_this->e_tv_setup_enter_reason = TV_SETUP_ENTER_REASON_TV_REMOTE_DEVICE_SETUP_RF;

	if(ui4_dev_type_sel_idx == WZD_TV_SETUP_CABLE_BOX_IDX)
	{
		pt_this->e_sig_type = TV_SETUP_SIG_TYPE_CABLE;
	}
	else if(ui4_dev_type_sel_idx == WZD_TV_SETUP_SATELLITE_IDX)
	{
		pt_this->e_sig_type = TV_SETUP_SIG_TYPE_SATELLITE_BOX;
	}

	wzd_page_goto( WZD_PAGE_NAVI_PREV_PAGE);
	
	return WZDR_OK;
}
/*----------------------------------------------------------------------------
* Name: wzd_page_tv_setup_enter_from_tv_name_input_rf
*
* Description: from tv_name_input page to tv tuner setup page afer select cable box -> RF.
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/
INT32 wzd_page_tv_setup_enter_from_tv_name_input_rf(UINT32  ui4_dev_type_sel_idx)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;

	pt_this->e_tv_setup_enter_reason = TV_SETUP_ENTER_REASON_TV_NAME_INPUT_RF;

	if(ui4_dev_type_sel_idx == WZD_TV_SETUP_CABLE_BOX_IDX)
	{
		pt_this->e_sig_type = TV_SETUP_SIG_TYPE_CABLE;
	}
	else if(ui4_dev_type_sel_idx == WZD_TV_SETUP_SATELLITE_IDX)
	{
		pt_this->e_sig_type = TV_SETUP_SIG_TYPE_SATELLITE_BOX;
	}

	wzd_page_goto( WZD_PAGE_NAVI_PREV_PAGE);
	
	return WZDR_OK;
}
/*----------------------------------------------------------------------------
* Name: wzd_page_tv_setup_enter_from_tv_name_input_input
*
* Description: name input: input page->tv setup page 
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/
INT32 wzd_page_tv_setup_enter_from_tv_name_input_input(VOID)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;

    pt_this->e_tv_setup_enter_reason = TV_SETUP_ENTER_REASON_TV_NAME_INPUT_INPUT;

    wzd_page_goto( WZD_PAGE_NAVI_PREV_PAGE);
    
	return WZDR_OK;
}
/*----------------------------------------------------------------------------
* Name: wzd_page_tv_setup_enter_from_tv_remote_device_setup_input
*
* Description: device setup: input page->tv setup page 
*
* Inputs:
*
* Outputs:
*
* Returns:
*
----------------------------------------------------------------------------*/
INT32 wzd_page_tv_setup_enter_from_tv_remote_device_setup_input(VOID)
{
	WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;

    pt_this->e_tv_setup_enter_reason = TV_SETUP_ENTER_REASON_TV_REMOTE_DEVICE_SETUP_INPUT;

    wzd_page_goto( WZD_PAGE_NAVI_PREV_PAGE);
    
	return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_tv_setup_update_by_state
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
static INT32 _wzd_page_tv_setup_update_by_state(BOOL b_repaint)
{
    WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    BOOL                        b_repaint_main_frame = FALSE;
    GL_RECT_T                   t_rect = {0};
    UINT8 						ui1_i = 0;
    HANDLE_T 					h_sb_icon_1st = NULL_HANDLE;
    WZD_ANIM_MOVE_PAGE_TYPE_T   e_move_hide_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
    WZD_ANIM_MOVE_PAGE_TYPE_T   e_move_show_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    
    DBG_INFO( ("\n####%s(%d)pt_this->e_state=%d\n",__FUNCTION__,__LINE__,pt_this->e_state));

    if( TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state )
    {
        if (TV_SETUP_STATE_ANTENNA_BEGIN_SCAN == pt_this->e_pre_state ||
            TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_pre_state ||
            TV_SETUP_STATE_WALL_BEGIN_SCAN == pt_this->e_pre_state)
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER;
        }

        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

    	/*Reset the rf scan flag*/
		wzd_set_rf_scan_flag(FALSE);
		
        RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE));
        RET_ON_ERR (wzd_view_desc_txt_set_text(WZD_TEXT(MLM_WZD_KEY_TV_SETUP_DESC_TXT1)));
        RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_TV_SETUP_TV_SIGNAL), NULL_HANDLE));

        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
		RET_ON_ERR (wzd_view_desc_txt_set_visibility( TRUE ));
		RET_ON_ERR (_wzd_page_tv_setup_sig_intro_set_text(FALSE));
		RET_ON_ERR (c_wgl_set_visibility (pt_this->h_intro_text, WGL_SW_NORMAL));

        pt_this->e_sig_type = TV_SETUP_SIG_TYPE_LAST_VALID_ITEM;

        RET_ON_ERR (wzd_view_scan_bar_set_visibility( FALSE ));
		
		RET_ON_ERR (_wzd_page_tv_setup_create_sel_box());

        for (ui1_i = 0; ui1_i < WZD_TV_SIG_SEL_BOX_BTN_COUNT; ui1_i++)
        {
            if (pt_this->b_is_choose_sig[ui1_i])
            {
                pt_this->ui1_sig_sel_box_idx = ui1_i;
                pt_this->b_sig_show_checkbox = TRUE;
                
                h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui1_i);
    			RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_NORMAL));
                break;
            }
        }

        if(!pt_this->b_sig_show_checkbox)
        {
            pt_this->ui1_sig_sel_box_idx = 0;
        }
        
        RET_ON_ERR (wzd_view_sel_box_set_focus (pt_this->ui1_sig_sel_box_idx, FALSE));
        RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_NORMAL));
            
		/* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));
		DBG_INFO( ("\n====update state===============%d\n",__LINE__));

        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

        _wzd_page_tv_setup_choose_sig_update_checkmark();
		
        b_repaint_main_frame = TRUE;
    }
    else if( TV_SETUP_STATE_ANTENNA_BEGIN_SCAN == pt_this->e_state )
    {
        e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
        e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;

        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        //RET_ON_ERR (wzd_view_set_main_frm_bg(h_g_wzd_img_background, FALSE)); /* Change background for close display small video */
        RET_ON_ERR(wzd_view_scan_txt_set_text( WZD_TEXT(MLM_WZD_KEY_EMPTY)));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
        RET_ON_ERR (wzd_view_desc_txt_set_visibility( FALSE ));

        SET_RECT_BY_SIZE (&t_rect,
                        TV_SETUP_BEGIN_TXT_X,
                        TV_SETUP_BEGIN_TXT_Y,
                        TV_SETUP_BEGIN_TXT_W,
                        TV_SETUP_BEGIN_TXT_H);
        RET_ON_ERR ( c_wgl_move(pt_this->h_intro_text, &t_rect, FALSE));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_intro_text, WGL_SW_NORMAL));
        
        RET_ON_ERR (_wzd_page_tv_setup_sig_intro_set_text(FALSE));
		RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE));

		DBG_INFO( ("\n======_wzd_page_tv_setup_update_by_state=====%d\n",__LINE__));

        SHOW_ON_ERR (wzd_view_scan_bar_set_pos(0));  
		RET_ON_ERR (wzd_view_scan_txt_set_visibility( TRUE ));
        RET_ON_ERR (wzd_view_scan_bar_set_visibility( FALSE ));

        /* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));
        
		/* Display footer */
		RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE));

        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

        b_repaint_main_frame = TRUE;
    }
    else if( TV_SETUP_STATE_ANTENNA_SCANNING == pt_this->e_state )
    {
        a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
        
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
        RET_ON_ERR (wzd_view_desc_txt_set_visibility( FALSE ));

        SET_RECT_BY_SIZE (&t_rect,
                        TV_SETUP_BEGIN_TXT_X,
                        TV_SETUP_BEGIN_TXT_Y,
                        TV_SETUP_BEGIN_TXT_W,
                        TV_SETUP_BEGIN_TXT_H);
		
        RET_ON_ERR ( c_wgl_move(pt_this->h_intro_text, &t_rect, FALSE));

        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_intro_text, WGL_SW_NORMAL));
        
        RET_ON_ERR (_wzd_page_tv_setup_sig_intro_set_text(FALSE));
		RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE));

        RET_ON_ERR (wzd_view_scan_txt_set_visibility( TRUE ));
        RET_ON_ERR (wzd_view_scan_bar_set_pos (0));
        RET_ON_ERR (wzd_view_scan_bar_set_visibility( TRUE ));

        /* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));

		/* Set focus to stop scan btn */ 
		RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE));

        /* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));

        b_repaint_main_frame = TRUE;
    }
    else if ( TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state )
    {
        e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
        e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;

        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
		RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
        RET_ON_ERR (wzd_view_desc_txt_set_visibility( TRUE ));
        pt_this->e_cable_device_type = CABLE_DEVICE_TYPE_LAST_VALID_ITEM;
		RET_ON_ERR (wzd_view_desc_txt_set_text(WZD_TEXT(MLM_WZD_KEY_TV_SETUP_CABLE_CONNECT_WAY)));

		RET_ON_ERR (_wzd_page_tv_setup_create_sel_box());

        for (ui1_i = 0; ui1_i < WZD_TV_SIG_SEL_BOX_BTN_COUNT; ui1_i++)
        {
            if (pt_this->b_is_choose_cable_dev[ui1_i])
            {
                pt_this->ui1_cable_dev_sel_box_idx = ui1_i;
                pt_this->b_cable_dev_show_checkbox = TRUE;
                
                h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui1_i);
    			RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_NORMAL));
                break;
            }
        }

        if (!pt_this->b_cable_dev_show_checkbox)
        {
            pt_this->ui1_cable_dev_sel_box_idx = 0;
        }
        
		RET_ON_ERR (wzd_view_sel_box_set_focus (pt_this->ui1_cable_dev_sel_box_idx, FALSE));
        RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_NORMAL));

		/* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));

		DBG_INFO( ("\n====update state===============%d\n",__LINE__));

        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

        _wzd_page_tv_setup_cable_dev_update_checkmark();

        b_repaint_main_frame = TRUE;
    }
    else if ( TV_SETUP_STATE_WALL_BEGIN_SCAN == pt_this->e_state )
    {
        if (CABLE_DEVICE_TYPE_CABLE_BOX_RF == pt_this->e_cable_device_type)
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
        }
        else
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;
        }

        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));
       
	   RET_ON_ERR(wzd_view_scan_txt_set_text( WZD_TEXT(MLM_WZD_KEY_EMPTY)));
	   RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
	   RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
	   RET_ON_ERR (wzd_view_desc_txt_set_visibility( FALSE ));

	   SET_RECT_BY_SIZE (&t_rect,
					   TV_SETUP_BEGIN_TXT_X,
					   TV_SETUP_BEGIN_TXT_Y,
					   TV_SETUP_BEGIN_TXT_W,
					   TV_SETUP_BEGIN_TXT_H);
	   RET_ON_ERR ( c_wgl_move(pt_this->h_intro_text, &t_rect, FALSE));
	   RET_ON_ERR (c_wgl_set_visibility (pt_this->h_intro_text, WGL_SW_NORMAL));
	   
	   RET_ON_ERR (_wzd_page_tv_setup_sig_intro_set_text(FALSE));
	   RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE));

	   DBG_INFO( ("\n======_wzd_page_tv_setup_update_by_state=====%d\n",__LINE__));

	   SHOW_ON_ERR (wzd_view_scan_bar_set_pos(0));	
	   RET_ON_ERR (wzd_view_scan_txt_set_visibility( TRUE ));
	   RET_ON_ERR (wzd_view_scan_bar_set_visibility( FALSE ));

        /* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));

	   RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE));

        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));

	   b_repaint_main_frame = TRUE;
    }
    else if ( TV_SETUP_STATE_WALL_SCANNING == pt_this->e_state )
    {
        if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)
        {
            a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);
        }
        else
        {
            a_cfg_set_tuner_type(APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
        }
		
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
		RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));
        RET_ON_ERR (wzd_view_desc_txt_set_visibility( FALSE ));

        SET_RECT_BY_SIZE (&t_rect,
                        TV_SETUP_BEGIN_TXT_X,
                        TV_SETUP_BEGIN_TXT_Y,
                        TV_SETUP_BEGIN_TXT_W,
                        TV_SETUP_BEGIN_TXT_H);
		
        RET_ON_ERR ( c_wgl_move(pt_this->h_intro_text, &t_rect, FALSE));

        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_intro_text, WGL_SW_NORMAL));
        
        RET_ON_ERR (_wzd_page_tv_setup_sig_intro_set_text(FALSE));
		RET_ON_ERR (wzd_view_sel_box_show(WZD_SEL_BOX_SHOW_TYPE_HIDE));

        RET_ON_ERR (wzd_view_scan_txt_set_visibility( TRUE ));
        RET_ON_ERR (wzd_view_scan_bar_set_pos (0));
        RET_ON_ERR (wzd_view_scan_bar_set_visibility( TRUE ));

        /* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));

		/* Set focus to stop scan btn */ 
		RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE));

        /* update footer by state */
		SHOW_ON_ERR (_wzd_page_tv_setup_help_lst_update(pt_this->e_state, FALSE));

        b_repaint_main_frame = TRUE;
    }
    /* Repaint main frame or layout frame */
    if( b_repaint )
    {
        if( b_repaint_main_frame == TRUE )
        {
            RET_ON_ERR (wzd_view_main_frm_repaint());
        }
        else
        {
            RET_ON_ERR (c_wgl_repaint (h_layout_frm, NULL, TRUE));
        }
    }

    return WZDR_OK;
}
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_amp_plug_dlg_show_do_timer
 *
 * Description: 
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_tv_setup_amp_plug_dlg_show_do_timer(VOID* pv_data,
																			SIZE_T	z_data_size)
{
    WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	
	c_timer_stop(pt_this->h_amp_plug_dlg_timer);
	
	wzd_page_goto( WZD_PAGE_NAVI_LAST_FINISHED_PAGE );
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_amp_plug_dlg_show_nfy_fct
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
static VOID _wzd_page_tv_setup_amp_plug_dlg_show_nfy_fct(HANDLE_T	h_timer,
																		   VOID*	 pv_tag)
{
	wzd_async_invoke(_wzd_page_tv_setup_amp_plug_dlg_show_do_timer, NULL, 0, FALSE); 
}
#endif
#endif
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_data_chg
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
VOID _wzd_page_tv_setup_data_chg(VOID*    pv_tag,
                                     UINT32   ui4_msg,
                                     VOID*    pv_param1,
                                     VOID*    pv_param2)
{
    WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	UINT8							  ui1_val = 0;

    switch( ui4_msg )
    {
        case WZD_DLG_MSG_BTN_FOCUSED:
            DBG_INFO( ( "[WZD][DLG CLI Test] WZD_DLG_MSG_BTN_FOCUSED received, btn index =%d\n", (UINT32)pv_param1 ));
            break;

        case WZD_DLG_MSG_KEY_INPUT:
            if( BTN_SELECT == (UINT32)pv_param1 )
            {
                DBG_INFO( ( "[WZD][DLG CLI Test] WZD_DLG_MSG_KEY_INPUT received, keycode =%d, focused btn = %d\n", (UINT32)pv_param1, (UINT32)pv_param2 ));
                if( WZD_DLG_BTN_TYPE_02 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2 )
                {
                    wzd_dlg_hide( pt_this->h_dlg );
                }
                else if( WZD_DLG_BTN_TYPE_01 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2 )  /* User presses yes. */
                {   
                    /* Skip */
                	if (a_wzd_is_resume_from_menu_setup())
                    {
                        a_wzd_exit();   /* Exit wizard. */
                    }
                	else
            		{
            		    /* change input source to HDMI1 */
                        wzd_chg_inp_src_to_hdmi();

						if (a_cfg_custom_get_wifi_remote_support())
						{
							a_cfg_custom_get_wifi_remote_pair_status(&ui1_val);
							
							if (WIFI_REMOTE_PAIR_STATUS_PAIRED != ui1_val)
							{
                            #ifdef APP_CEC_SUPPORT
                            #ifdef APP_CEC2_SUPPORT
                            #ifdef APP_ARC_ONLY
								if(b_g_is_amp_plug_dlg_show == FALSE)
								{
									nav_cec_custom_amp_plug_dlg_show();
									
									c_timer_start(pt_this->h_amp_plug_dlg_timer, 
												  5000,
												  X_TIMER_FLAG_ONCE,
												  _wzd_page_tv_setup_amp_plug_dlg_show_nfy_fct,
												  NULL); 
									
								}
								else
                            #endif
                            #endif
                            #endif
                                {
									wzd_page_goto( WZD_PAGE_NAVI_LAST_FINISHED_PAGE );
                                }
							}
							else
							{
								wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );
							}
						}
	                    else
	                    {
                            #ifdef APP_CEC_SUPPORT
                            #ifdef APP_CEC2_SUPPORT
                            #ifdef APP_ARC_ONLY
								if(b_g_is_amp_plug_dlg_show == FALSE)
								{
									nav_cec_custom_amp_plug_dlg_show();
									
									c_timer_start(pt_this->h_amp_plug_dlg_timer, 
												  5000,
												  X_TIMER_FLAG_ONCE,
												  _wzd_page_tv_setup_amp_plug_dlg_show_nfy_fct,
												  NULL); 
									
								}
								else
                            #endif
                            #endif
                            #endif
                                {
								    wzd_page_goto( WZD_PAGE_NAVI_LAST_FINISHED_PAGE );
                                }
	                    }
            		}
                }
            }
            break;

        case WZD_DLG_MSG_DLG_HIDED:
            DBG_INFO( ( "[WZD][DLG CLI Test] WZD_DLG_MSG_DLG_HIDED received\n" ));
            c_wgl_set_focus( pt_this->h_last_focused_wdg, TRUE );
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_tv_stop_scan_dlg_data_chg
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
VOID _wzd_tv_stop_scan_dlg_data_chg (VOID*    pv_tag,
    	                             UINT32   ui4_msg,
    	                             VOID*    pv_param1,
    	                             VOID*    pv_param2)
{
    WZD_TV_SETUP_MEMBER_T*  pt_this = &gt_tv_setup;

    switch( ui4_msg )
    {
        case WZD_DLG_MSG_BTN_FOCUSED:
            DBG_INFO( ( "[WZD][DLG] WZD_DLG_MSG_BTN_FOCUSED received, btn index =%d\n", (UINT32)pv_param1 ));
            break;

        case WZD_DLG_MSG_KEY_INPUT:
            if( BTN_SELECT == (UINT32)pv_param1 )
            {
                DBG_INFO( ( "[WZD][DLG] WZD_DLG_MSG_KEY_INPUT received, btn index =%d\n", (UINT32)pv_param1 ));

				/* Continue scan */
                if (WZD_DLG_BTN_TYPE_01 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2)
                {
                	/* hide dialog */
                    wzd_dlg_hide(pt_this->h_dlg);
                    wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, TRUE);
                }
                else    /* Stop scan */
				{
					/* hide dialog */
                    wzd_dlg_hide(pt_this->h_dlg);
                    wzd_app_send_msg (WZD_MSG_BTN_SELECT, NULL, 0);
                }
            }
            break;

        case WZD_DLG_MSG_DLG_HIDED:
            DBG_INFO( ( "[WZD][DLG] WZD_DLG_MSG_DLG_HIDED received\n" ));
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_tv_stop_scan_dlg_create
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_tv_stop_scan_dlg_create (VOID)
{
    WZD_DLG_INIT_T          t_dlg_init;
    HANDLE_T                h_layout_frm = NULL_HANDLE;
    WZD_TV_SETUP_MEMBER_T*  pt_this = &gt_tv_setup;

	DBG_INFO( ("[WZD][TV] --- Stop scan dialog show! %d.\n", __LINE__));

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.ui4_hide_timer = 0;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;
    t_dlg_init.pf_fct = _wzd_tv_stop_scan_dlg_data_chg;
	t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_AUTO_HIDE;

    wzd_dlg_create(&t_dlg_init, &pt_this->h_dlg);

    wzd_dlg_set_text(pt_this->h_dlg, WZD_TEXT(MLM_WZD_KEY_TUNER_SETUP_STOP_SCAN_MSG), FALSE);
    wzd_dlg_set_btn_text(pt_this->h_dlg, WZD_DLG_BTN_TYPE_01,
                         WZD_TEXT(MLM_WZD_KEY_TUNER_SETUP_CONTINUE_SCAN), FALSE);
    wzd_dlg_set_btn_text(pt_this->h_dlg, WZD_DLG_BTN_TYPE_02,
                         WZD_TEXT(MLM_WZD_KEY_TUNER_SETUP_STOP_SCAN), FALSE);

    wzd_dlg_show( pt_this->h_dlg , TRUE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_create_dlg
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
static INT32 _wzd_page_tv_setup_create_dlg (VOID)
{
    WZD_DLG_INIT_T              t_dlg_init;
    HANDLE_T                    	h_layout_frm = NULL_HANDLE;
    WZD_TV_SETUP_MEMBER_T*    pt_this = &gt_tv_setup;

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T)); 
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_AUTO_HIDE | WZD_DLG_STYLE_MASK_WITH_DESC_MUTI_LINE;
    t_dlg_init.pf_fct = _wzd_page_tv_setup_data_chg;
    t_dlg_init.pv_tag = NULL;
    t_dlg_init.ui4_hide_timer = 0;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;

	/* Set Font */
    c_strcpy (t_dlg_init.t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_dlg_init.t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_dlg_init.t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_dlg_init.t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_dlg_init.t_fnt_info.ui1_custom_size = 22;
	
    wzd_dlg_create( &t_dlg_init, &pt_this->h_dlg );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_show_dlg
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
static INT32 _wzd_page_tv_setup_show_dlg (
                                UINT16 ui2_content,
                                UINT16 ui2_desc,
                                UINT16 ui2_left_btn,
                                UINT16 ui2_right_btn)
{
    WZD_TV_SETUP_MEMBER_T*        pt_this = &gt_tv_setup;

    if( NULL_HANDLE == pt_this->h_dlg )
    {
        return WZDR_FAIL;
    }
	
    c_wgl_get_focus( &pt_this->h_last_focused_wdg );

    wzd_dlg_set_text( pt_this->h_dlg, WZD_TEXT(ui2_content), FALSE );
	wzd_dlg_set_desc_text( pt_this->h_dlg, WZD_TEXT(ui2_desc), FALSE );
	
    wzd_dlg_set_btn_text( pt_this->h_dlg, WZD_DLG_BTN_TYPE_01, WZD_TEXT(ui2_left_btn), FALSE );

    wzd_dlg_set_btn_text( pt_this->h_dlg, WZD_DLG_BTN_TYPE_02, WZD_TEXT(ui2_right_btn), FALSE );

    wzd_dlg_show( pt_this->h_dlg , TRUE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_create
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
static INT32 _wzd_page_tv_setup_create (VOID)
{
    WZD_TV_SETUP_MEMBER_T*          pt_this = &gt_tv_setup;
    GL_RECT_T                       t_rect;
    HANDLE_T                        h_layout_frm = NULL_HANDLE;
    UINT32                          ui4_style = 0;
    WGL_FONT_INFO_T                 t_fnt_info;
    UINT8                           ui1_align = 0;
    WGL_COLOR_INFO_T                t_color_info_bg, t_color_info_fg;
    WGL_INSET_T                     t_inset;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    c_memset( &gt_tv_setup, 0, sizeof(WZD_TV_SETUP_MEMBER_T) );

    pt_this->e_sig_type = TV_SETUP_SIG_TYPE_LAST_VALID_ITEM;

    /* Create begin scan description text */
    SET_RECT_BY_SIZE (& t_rect,
                      TV_SETUP_BEGIN_TXT_X,
                      TV_SETUP_BEGIN_TXT_Y,
                      TV_SETUP_BEGIN_TXT_W,
                      TV_SETUP_BEGIN_TXT_H);

    ui4_style = WGL_STL_TEXT_MULTILINE |
                 WGL_STL_TEXT_MAX_4096  |
                 WGL_STL_TEXT_MAX_DIS_5_LINE |
                 WZD_WIDGET_STYLE;

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, WZD_FONT_NAME);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_gray);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_cho_mode_txt_gray);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_cho_mode_txt_gray);

    t_inset.i4_left   = TV_SETUP_BEGIN_TXT_INSET_L;
    t_inset.i4_right  = TV_SETUP_BEGIN_TXT_INSET_R;
    t_inset.i4_top    = TV_SETUP_BEGIN_TXT_INSET_T;
    t_inset.i4_bottom = TV_SETUP_BEGIN_TXT_INSET_B;

    RET_ON_ERR (_wzd_page_tv_setup_create_txt(
                                &t_rect,
                                h_layout_frm,
                                NULL,
                                ui4_style,
                                &pt_this->h_intro_text,
                                &t_fnt_info,
                                ui1_align,
                                &t_color_info_bg,
                                &t_color_info_fg,
                                &t_inset));

	/* create animation scan timer */
    RET_ON_ERR (c_timer_create (& t_g_wzd.h_timer_scan));
	
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
	/* create amp plug dlg hide timer */
    RET_ON_ERR (c_timer_create (& pt_this->h_amp_plug_dlg_timer));
#endif
#endif
#endif

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_dsty
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
static INT32 _wzd_page_tv_setup_dsty(VOID)
{
    WZD_TV_SETUP_MEMBER_T*          pt_this = &gt_tv_setup;

    if( pt_this->h_dlg )
    {
        wzd_dlg_destroy( pt_this->h_dlg );
    }

	if (gt_tv_setup_rf_scan.h_timer_scan != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete (gt_tv_setup_rf_scan.h_timer_scan));
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_on_show
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
static INT32 _wzd_page_tv_setup_on_show (
    UINT32                      ui4_page_id
    )
{
    WZD_TV_SETUP_MEMBER_T*          pt_this = &gt_tv_setup;
    INT32                           i4_ret = WZDR_OK;

    if (a_cfg_custom_get_wifi_remote_support())
    {
    	BOOL							b_db_status = FALSE;

        DEV_DB_LOCK_CHECK_COND_T e_check_cond = DEV_DB_LOCK_CHECK_COND_NONE;

        i4_ret = a_dev_db_check_lock_info( e_check_cond, &b_db_status );

        DBG_INFO( ("\n[wzd_db] a_dev_db_check_lock_info() i4_ret=%d , check_cond=%d, b_db_status=%d\n", i4_ret, e_check_cond, b_db_status));

    	if ((DEV_DBR_OK == i4_ret) && (b_db_status)) /* should check the return value and the lock status*/
    	{
    		pt_this->b_is_db_locked = TRUE;
    	}
    	else
    	{
    		pt_this->b_is_db_locked = FALSE;
    	}
    }

    pt_this->h_img_demo_pic = NULL_HANDLE;
    pt_this->h_img_right_hlt_IO_icons = NULL_HANDLE;

	/*Reset the rf scan flag*/
	wzd_set_rf_scan_flag(FALSE);

	if((pt_this->e_tv_setup_enter_reason  == TV_SETUP_ENTER_REASON_TV_REMOTE_DEVICE_SETUP_RF)||
		(pt_this->e_tv_setup_enter_reason  == TV_SETUP_ENTER_REASON_TV_NAME_INPUT_RF))
	{
		DBG_INFO( ("\n####%s(%d)TV_SETUP_ENTER_REASON_TV_REMOTE_DEVICE_SETUP_RF\n",__FUNCTION__,__LINE__));
		pt_this->e_pre_state = TV_SETUP_STATE_SELECT_CABLE_DEVICE;
		pt_this->e_state = TV_SETUP_STATE_WALL_BEGIN_SCAN;
	    pt_this->e_cable_device_type = CABLE_DEVICE_TYPE_CABLE_BOX_RF;
		DBG_INFO( ("\n####_wzd_page_tv_setup_on_show####%s(%d)\n",__FUNCTION__,__LINE__));
		RET_ON_ERR (_wzd_page_tv_setup_update_by_state( FALSE ));
        pt_this->e_tv_setup_enter_reason  = TV_SETUP_ENTER_REASON_NONE;
	}
	else
	{
	    if((pt_this->e_tv_setup_enter_reason  == TV_SETUP_ENTER_REASON_TV_NAME_INPUT_INPUT)||
            (pt_this->e_tv_setup_enter_reason  == TV_SETUP_ENTER_REASON_TV_REMOTE_DEVICE_SETUP_INPUT))
        {
            pt_this->e_tv_setup_enter_reason  = TV_SETUP_ENTER_REASON_NONE;
        }
	    /* Update display */
        pt_this->e_pre_state = TV_SETUP_STATE_HIDE;
	    pt_this->e_state = TV_SETUP_STATE_CHOOSE_SIG;
	    pt_this->e_sig_type = TV_SETUP_SIG_TYPE_LAST_VALID_ITEM;
		pt_this->e_cable_device_type = CABLE_DEVICE_TYPE_LAST_VALID_ITEM;
	    DBG_INFO( ("\n====_wzd_page_tv_setup_on_show====%d\n",__LINE__));
	    RET_ON_ERR (_wzd_page_tv_setup_update_by_state( FALSE ));
	}

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_on_hide
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
static INT32 _wzd_page_tv_setup_on_hide(UINT32 ui4_page_id)
{
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_return_nfy_cb
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
static VOID _wzd_page_tv_setup_return_nfy_cb(VOID)
{
    WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;

    if( TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state )
    {
        if (!a_wzd_is_resume_from_menu_setup())
        {
            wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
        }
		else
		{
			/* exit wizard. */
			a_wzd_exit();
		}
    }
    else if (TV_SETUP_STATE_ANTENNA_BEGIN_SCAN == pt_this->e_state)
    {
        pt_this->e_pre_state = pt_this->e_state;
        pt_this->e_state = TV_SETUP_STATE_CHOOSE_SIG;
        _wzd_page_tv_setup_update_by_state(TRUE);
    }
	else if (TV_SETUP_STATE_WALL_BEGIN_SCAN == pt_this->e_state)
	{
		pt_this->e_pre_state = pt_this->e_state;
		pt_this->e_state = TV_SETUP_STATE_CHOOSE_SIG;
		_wzd_page_tv_setup_update_by_state(TRUE);
	}
    else if (TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
    {
        pt_this->e_pre_state = pt_this->e_state;
        pt_this->e_state = TV_SETUP_STATE_CHOOSE_SIG;
        _wzd_page_tv_setup_update_by_state(TRUE);
    }
    
    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_tv_setup_on_footer_nfy
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
static VOID _wzd_page_tv_setup_on_footer_nfy(
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2)
{
    WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	BOOL 						b_visible = FALSE;
	HANDLE_T					h_layout_frm = NULL_HANDLE;
	HANDLE_T 					h_sel_box = NULL_HANDLE;

    switch( ui4_msg )
    {
        case WZD_FOOTER_MSG_ITEM_FOCUSED:
            DBG_INFO( ( "[WZD][CON TV] %d footer button is focused.\n", (UINT32)pv_param1 ));
            /*pt_this->e_focused_footer = (WZD_FOOTER_BTN_INDEX_T)(UINT32)pv_param1;*/
            break;
        case WZD_FOOTER_MSG_KEY_INPUT:
            DBG_INFO( ( "[WZD][CON TV] Receive key input, keycode = %d\n", (UINT32)pv_param1 ));

            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
                    {
						if(pt_this->e_state == TV_SETUP_STATE_CHOOSE_SIG)
						{
							/*skip button*/
							if( WZD_FOOTER_BTN_01 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )
							{
								if(TV_SETUP_STATE_HIDE != pt_this->e_state)
								{
								    /* from menu should just exit wizard, no need dialog */
								    if (a_wzd_is_resume_from_menu_setup())
                                    {
                                        a_wzd_exit();
                                    }
                                    else
                                    {
                                        /* Create and show skip dialog. */
                                        SHOW_ON_ERR (_wzd_page_tv_setup_create_dlg());
									    _wzd_page_tv_setup_show_dlg(MLM_WZD_KEY_TV_SETUP_SKIP_DIG,
																	MLM_WZD_KEY_TV_SETUP_SKIP_DIG_DESC,
																	MLM_WZD_KEY_TV_SETUP_SKIP_BUTTON1,
																	MLM_WZD_KEY_TV_SETUP_SKIP_BUTTON2);
                                    }
								}
							}
							break;
						}
						else if(pt_this->e_state == TV_SETUP_STATE_SELECT_CABLE_DEVICE)
						{
							if( WZD_FOOTER_BTN_01 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )  /* Back button pressed */
							{
								pt_this->e_pre_state = pt_this->e_state;
	                            pt_this->e_state = TV_SETUP_STATE_CHOOSE_SIG;
							    pt_this->e_sig_type = TV_SETUP_SIG_TYPE_LAST_VALID_ITEM;
							    _wzd_page_tv_setup_update_by_state(FALSE);
								wzd_view_main_frm_repaint();
							}
							break;
						}
						else if((pt_this->e_state == TV_SETUP_STATE_ANTENNA_BEGIN_SCAN) ||
							(pt_this->e_state == TV_SETUP_STATE_WALL_BEGIN_SCAN))
						{
							if( WZD_FOOTER_BTN_01 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )  /* Begin scan button pressed */
							{
								wzd_view_get_layout_frm(&h_layout_frm);
					            if (TV_SETUP_STATE_ANTENNA_BEGIN_SCAN == pt_this->e_state)
					            {
					                pt_this->e_state = TV_SETUP_STATE_ANTENNA_SCANNING;
					                _wzd_page_tv_setup_update_by_state( FALSE );

					                wzd_app_send_msg (WZD_MSG_SB_SCAN_START, NULL, 0);  /* Start scan */
					                wzd_view_main_frm_repaint();
					            }
					            else if (TV_SETUP_STATE_WALL_BEGIN_SCAN == pt_this->e_state)
					            {
									if(CABLE_DEVICE_TYPE_CABLE_BOX_RF == pt_this->e_cable_device_type)
					        		{
						        		/*set b_is_rf_scan flag*/
										wzd_set_rf_scan_flag(TRUE);
					        		}
									else
									{
										wzd_set_rf_scan_flag(FALSE);
									}
									pt_this->e_state = TV_SETUP_STATE_WALL_SCANNING;
					                _wzd_page_tv_setup_update_by_state( FALSE );
				        			DBG_INFO( ("\n####%s(%d)RF scan start\n",__FUNCTION__,__LINE__));
					                wzd_app_send_msg (WZD_MSG_SB_SCAN_START, NULL, 0);  /* Start scan */
					                wzd_view_main_frm_repaint();
					            }
							}
							else if(WZD_FOOTER_BTN_02 == (WZD_FOOTER_BTN_INDEX_T)pv_param2)/*Cancel button pressed*/
							{
							    pt_this->e_pre_state = pt_this->e_state;
								pt_this->e_state = TV_SETUP_STATE_CHOOSE_SIG;
						        _wzd_page_tv_setup_update_by_state(TRUE);
							}
							break;
						}
						else if((pt_this->e_state == TV_SETUP_STATE_ANTENNA_SCANNING) ||
								(pt_this->e_state == TV_SETUP_STATE_WALL_SCANNING))
						{
                            SHOW_ON_ERR (_wzd_tv_stop_scan_dlg_create());

							return;
						}

                    }
                    break;
                case BTN_CURSOR_UP:
                    {					
                        if (TV_SETUP_STATE_CHOOSE_SIG == pt_this->e_state)
                        {
                        	/* focus to pre select box */
							h_sel_box = wzd_view_sel_box_get_btn_handle (ui4_g_pre_focused_sb_idx);
							c_wgl_get_visibility(h_sel_box, &b_visible);
					        if (b_visible)
					        {
					            wzd_view_sel_box_set_focus(ui4_g_pre_focused_sb_idx, FALSE);
					        }
                            wzd_view_main_frm_repaint();
                        }
                        else if (TV_SETUP_STATE_ANTENNA_BEGIN_SCAN == pt_this->e_state)
                        {
                        }
                        else if (TV_SETUP_STATE_SELECT_CABLE_DEVICE == pt_this->e_state)
                        {
                            h_sel_box = wzd_view_sel_box_get_btn_handle (ui4_g_pre_focused_sb_idx);
							c_wgl_get_visibility(h_sel_box, &b_visible);
					        if (b_visible)
					        {
					            wzd_view_sel_box_set_focus(ui4_g_pre_focused_sb_idx, FALSE);
					        }
                            wzd_view_main_frm_repaint();
                        }
                        else if ( TV_SETUP_STATE_WALL_BEGIN_SCAN == pt_this->e_state)
                        {
                            wzd_view_main_frm_repaint();
                        }
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
 * Name: _wzd_page_tv_setup_on_hide
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
INT32 wzd_page_tv_setup_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data)
{
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TV_SETUP_TV_SIGNAL;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_LOC_DESC_TITLE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = _wzd_page_tv_setup_on_footer_nfy;
	pt_info_data->pf_return_nfy_fct        = _wzd_page_tv_setup_return_nfy_cb;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_page_tv_setup_create;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_page_tv_setup_dsty;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_page_tv_setup_on_show;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_page_tv_setup_on_hide;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_nfy_sel
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
INT32 wzd_page_tv_setup_nfy_sel(UINT16               ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_tv_setup_on_scan_complete
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
INT32 wzd_page_tv_setup_on_scan_complete( UINT16 ui2_ch_num )
{
    WZD_TV_SETUP_MEMBER_T*      pt_this = &gt_tv_setup;
	UINT8							  ui1_val = 0;

	if(wzd_panel_key_is_long_press())
	{
		return WZDR_OK;
	}
	/* re-select channel */
	if(pt_this->e_sig_type == TV_SETUP_SIG_TYPE_SATELLITE_BOX)
	{
		wzd_select_crnt_or_first_channel(TRUE);
	}
	else
	{
		wzd_select_crnt_or_first_channel(FALSE);
	}

    if (TV_SETUP_STATE_ANTENNA_SCANNING == pt_this->e_state)
    {
        if (a_wzd_is_resume_from_menu_setup())
        {
            a_wzd_exit();   /* Exit wizard. */
        }
    	else
		{
    		/* mute */
        	a_tv_set_mute (TRUE);
    		wzd_enable_vol_key(FALSE);

            if (a_cfg_custom_get_wifi_remote_support())
            {
                a_cfg_custom_get_wifi_remote_pair_status(&ui1_val);
                
                if(WIFI_REMOTE_PAIR_STATUS_PAIRED != ui1_val)
                {
                    wzd_page_tv_remote_device_setup_enter_from_tuner_not_pair_antenna();
                }
                else
                {
                    wzd_page_tv_remote_device_setup_enter_from_tuner_pair_antenna();
                }
            }
            else
            {
                	
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
				if(b_g_is_amp_plug_dlg_show == FALSE)
				{
					nav_cec_custom_amp_plug_dlg_show();
					
					c_timer_start(pt_this->h_amp_plug_dlg_timer, 
								  5000,
								  X_TIMER_FLAG_ONCE,
								  _wzd_page_tv_setup_amp_plug_dlg_show_nfy_fct,
								  NULL); 
					
				}
				else
#endif
#endif
#endif
                    wzd_page_goto( WZD_PAGE_NAVI_LAST_FINISHED_PAGE );
            }
		}
    }
    else if (TV_SETUP_STATE_WALL_SCANNING == pt_this->e_state)
    {
		if (a_wzd_is_resume_from_menu_setup())
        {
            if(pt_this->e_cable_device_type == CABLE_DEVICE_TYPE_DIRECT_WALL)
            {
                a_wzd_exit();   /* Exit wizard. */
            }
            else
            {
                if (a_cfg_custom_get_wifi_remote_support())
                {
                    /*rf scan->device setup*/
                    wzd_page_tv_remote_device_setup_enter_from_tuner_setup_rf_scan();
                }
                else
                {
                    /*rf scan->name input*/
                    wzd_page_tv_name_input_enter_from_tuner_setup_rf_scan();
                }
            }
        }
    	else
		{
    		/* mute */
        	a_tv_set_mute (TRUE);
    		wzd_enable_vol_key(FALSE);
            if (a_cfg_custom_get_wifi_remote_support())
            {
                a_cfg_custom_get_wifi_remote_pair_status(&ui1_val);
                
                if(WIFI_REMOTE_PAIR_STATUS_PAIRED != ui1_val)
                {
                    if(pt_this->e_cable_device_type == CABLE_DEVICE_TYPE_DIRECT_WALL)
                    {
                    	 wzd_page_tv_remote_device_setup_enter_from_tuner_not_pair_antenna();
                    }
                    else
                    {
                        /*rf scan->device setup*/
                        wzd_page_tv_remote_device_setup_enter_from_tuner_setup_rf_scan();
                    }
                }
                else
                {
                    if(pt_this->e_cable_device_type == CABLE_DEVICE_TYPE_DIRECT_WALL)
                    {
                        wzd_page_tv_remote_device_setup_enter_from_tuner_pair_direct_from_wall();
                    }
                    else
                    {
                        /*rf scan->device setup*/
    		            wzd_page_tv_remote_device_setup_enter_from_tuner_setup_rf_scan();
                    }
                }
            }
            else
            {
                if(pt_this->e_cable_device_type == CABLE_DEVICE_TYPE_CABLE_BOX_RF)
                {
		            wzd_page_tv_name_input_enter_from_tuner_setup_rf_scan();
	        	}
				else
				{
	                	
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
					if(b_g_is_amp_plug_dlg_show == FALSE)
					{
						nav_cec_custom_amp_plug_dlg_show();
						
						c_timer_start(pt_this->h_amp_plug_dlg_timer, 
									  5000,
									  X_TIMER_FLAG_ONCE,
									  _wzd_page_tv_setup_amp_plug_dlg_show_nfy_fct,
									  NULL); 
						
					}
					else
#endif
#endif
#endif
                    wzd_page_goto( WZD_PAGE_NAVI_LAST_FINISHED_PAGE );
				}
            }
		}
    }

    DBG_INFO( ( "[WZD][TV Setup] scan complete, enter rename input state.\n" ));

    return WZDR_OK;
}


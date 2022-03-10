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
#include "wizard_anim/page/wzd_page_wifi_remote_paring.h"
#include "wdk/a_vkb.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/wdk/wdk_img.h"
#include "am/a_am.h"
#include "amb/a_amb.h"
#include "nav/a_navigator.h"

#include "c_net_p2p_ctl.h"
#ifdef APP_WFD_SUPPORT
#include "wfd_client_export.h"
#endif
#include "app_util/a_network.h"
#include "wizard/wzd_dbg.h"

#define  DESC_VIEW_PIC_FLAG                 ("%p")
#define  DESC_VIEW_PIC_FLAG_LEN             (3)
#define  DESC_VIEW_UP_ARROW_IDX             (0)
#define  DESC_VIEW_DOWN_ARROW_IDX           (1)

#define  WZD_WIFI_REMOTE_PARING_TIMER_MAX      (20)

#define WZD_WIFI_REMOTE_DEVICES_MAX_NUM       (8)

typedef enum WIFI_REMOTE_PARING_STATE
{
   WIFI_REMOTE_PARING_STATE_HIDE = 0,
   WIFI_REMOTE_PARING_ACTIVING,
   WIFI_REMOTE_PARING_SEARCHING,
   WIFI_REMOTE_PARING_PAIRING,
   WIFI_REMOTE_PARING_FAIL,
   WIFI_REMOTE_PARING_SUCCESS,
   WIFI_REMOTE_PARING_STATE_LAST_VALID_ITEM
}WIFI_REMOTE_PARING_STATE;

typedef struct _WZD_WIFI_REMOTE_PARING_MEMBER_T
{
    HANDLE_T            h_dlg;

    UINT8               ui1_icon_step;
    HANDLE_T            h_animation_icon;
    
    HANDLE_T            h_image_icon;
    
    HANDLE_T            h_timer;
    HANDLE_T            h_wait_timer;
    HANDLE_T            h_remote_found_delay_timer;
	HANDLE_T            h_remote_pair_non_ack_timer;

    /*bluetooth remote control*/
    BOOL                b_remote_searching;
    BOOL                b_remote_paired;
    UINT8               ui1_timer_count;

    WIFI_REMOTE_PARING_STATE           e_state;
}WZD_WIFI_REMOTE_PARING_MEMBER_T;


static INT32 _wzd_page_wifi_remote_paring_update_by_state(BOOL b_repaint);
static VOID _wzd_wifi_remote_paring_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag);
static INT32 _wzd_page_wifi_remote_search_and_pair(VOID);
static INT32 _wzd_page_wifi_remote_paring_show_dlg (
                                UINT16 ui2_content,
                                UINT16 ui2_left_btn,
                                UINT16 ui2_right_btn);

static WZD_WIFI_REMOTE_PARING_MEMBER_T        gt_wifi_remote_paring;
/*----------------------------------------------------------------------------
 * Function Impliment
 ----------------------------------------------------------------------------*/
#ifdef APP_WFD_SUPPORT
 /*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_start_pairing
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_wifi_remote_start_pairing(VOID)
{
	INT32 i4_ret = WZDR_OK;

    DBG_INFO( ("<WZD>  start pairing now\n"));
    gt_wifi_remote_paring.e_state = WIFI_REMOTE_PARING_SEARCHING;
	i4_ret = (INT32)wfd_client_connect(WFD_CONNECT_PBC_FORCE_GO,NULL,NULL);
	if(i4_ret < 0)
	{
		DBG_ERROR( ("<WZD> wfd_client_connect fail @ file = %s, line = %d\n\r", __FILE__, __LINE__));
	}

}
#endif
/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_remote_timer_icon_update
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_wifi_remote_timer_icon_update(HANDLE_T   h_widget)
{
    INT32                i4_ret;
    WGL_IMG_INFO_T       t_img_info;
    WGL_HIMG_TPL_T       ah_g_searching_icon[12] =
    {
        h_g_wdk_img_loading_icon_1,
        h_g_wdk_img_loading_icon_2,
        h_g_wdk_img_loading_icon_3,
        h_g_wdk_img_loading_icon_4,
        h_g_wdk_img_loading_icon_5,
        h_g_wdk_img_loading_icon_6,
        h_g_wdk_img_loading_icon_7,
        h_g_wdk_img_loading_icon_8,
        h_g_wdk_img_loading_icon_9,
        h_g_wdk_img_loading_icon_10,
        h_g_wdk_img_loading_icon_11,
        h_g_wdk_img_loading_icon_12
    };

    if(gt_wifi_remote_paring.ui1_icon_step >= ((sizeof(ah_g_searching_icon) / sizeof(WGL_HIMG_TPL_T)) -1))
    {
        gt_wifi_remote_paring.ui1_icon_step = 0;
    }
    else
    {
        gt_wifi_remote_paring.ui1_icon_step++;
    }

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = ah_g_searching_icon[gt_wifi_remote_paring.ui1_icon_step];
    t_img_info.u_img_data.t_standard.t_disable   = ah_g_searching_icon[gt_wifi_remote_paring.ui1_icon_step];
    t_img_info.u_img_data.t_standard.t_highlight = ah_g_searching_icon[gt_wifi_remote_paring.ui1_icon_step];

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;

}
/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_remote_do_timer_nfy
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
static VOID _wzd_wifi_remote_do_timer_nfy(VOID* pv_data,
                                 SIZE_T  z_data_size)
{


    if (WIFI_REMOTE_PARING_SEARCHING == gt_wifi_remote_paring.e_state)
    {
        DBG_INFO( ("\n<wzd remote> --- searching --- \n"));
        if (gt_wifi_remote_paring.ui1_timer_count < WZD_WIFI_REMOTE_PARING_TIMER_MAX)
        {
            gt_wifi_remote_paring.ui1_timer_count += 1;

        #ifdef APP_WFD_SUPPORT
			if(wfd_client_get_p2p_init_state() < 0)
			{
				DBG_INFO( ("[WZD] P2P is disable, pairing will be fair\n"));
			}
			else
			{
				DBG_INFO( ("[WZD] P2P is enable, you can start pairing now\n"));
			}
		#endif

            _wzd_wifi_remote_timer_icon_update(gt_wifi_remote_paring.h_animation_icon);
            
            c_timer_start(gt_wifi_remote_paring.h_timer,
                                    1000,
                                    X_TIMER_FLAG_ONCE,
                                    _wzd_wifi_remote_paring_timer_notify_fct,
                                    NULL);
        }
        else
        {
            DBG_INFO( ("\n<wzd remote> ---searching timeout ---\n"));

            if (gt_wifi_remote_paring.b_remote_searching)  /* searching timeout*/
            {
                DBG_INFO( ("\n<wzd remote>---%s, stop_scan.\n", __FUNCTION__));
            }
            
            c_wgl_set_visibility(gt_wifi_remote_paring.h_animation_icon, WGL_SW_HIDE);
            gt_wifi_remote_paring.e_state = WIFI_REMOTE_PARING_FAIL;
            _wzd_page_wifi_remote_paring_update_by_state(TRUE);
        }
    }
    else if (WIFI_REMOTE_PARING_PAIRING == gt_wifi_remote_paring.e_state)
    {
        DBG_INFO( ("\n<wzd remote> --- pairing --- \n"));
        if (gt_wifi_remote_paring.ui1_timer_count < (WZD_WIFI_REMOTE_PARING_TIMER_MAX+10))
        {
            gt_wifi_remote_paring.ui1_timer_count += 1;

            _wzd_wifi_remote_timer_icon_update(gt_wifi_remote_paring.h_animation_icon);
            
            c_timer_start(gt_wifi_remote_paring.h_timer,
                                    1000,
                                    X_TIMER_FLAG_ONCE,
                                    _wzd_wifi_remote_paring_timer_notify_fct,
                                    NULL);
        }
        else
        {
            DBG_INFO( ("\n<wzd remote> --- pairing timeout ---\n"));

            c_wgl_set_visibility(gt_wifi_remote_paring.h_animation_icon, WGL_SW_HIDE);
            gt_wifi_remote_paring.e_state = WIFI_REMOTE_PARING_FAIL;
            _wzd_page_wifi_remote_paring_update_by_state(TRUE);
        }
    }
    else if (WIFI_REMOTE_PARING_SUCCESS == gt_wifi_remote_paring.e_state)
    {
        c_wgl_set_visibility(gt_wifi_remote_paring.h_animation_icon, WGL_SW_HIDE);
        gt_wifi_remote_paring.e_state = WIFI_REMOTE_PARING_SUCCESS;
        _wzd_page_wifi_remote_paring_update_by_state(TRUE);
    }
    else if (WIFI_REMOTE_PARING_FAIL == gt_wifi_remote_paring.e_state)
    {
        DBG_INFO( ("\n<wzd remote> --- Pair Fail ---\n"));
        if (gt_wifi_remote_paring.b_remote_searching)  /* searching timeout*/
        {
            DBG_INFO( ("\n<wzd remote>---%s, stop_scan.\n", __FUNCTION__));
        }

        c_wgl_set_visibility(gt_wifi_remote_paring.h_animation_icon, WGL_SW_HIDE);
        gt_wifi_remote_paring.e_state = WIFI_REMOTE_PARING_FAIL;
        _wzd_page_wifi_remote_paring_update_by_state(TRUE);

    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_remote_paring_timer_notify_fct
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
static VOID _wzd_wifi_remote_paring_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_wifi_remote_do_timer_nfy, pv_tag, (0), TRUE);
    return;
}
#ifdef APP_WFD_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_scan_wait_do_timer_nfy
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
static VOID _wzd_wifi_scan_wait_do_timer_nfy(VOID* pv_data,
                                 SIZE_T  z_data_size)
{
    INT32       i4_ret = WZDR_OK;
    WZD_WIFI_REMOTE_PARING_MEMBER_T*      pt_this = &gt_wifi_remote_paring;
    UINT8       pt_info[64] = {0};
    UINT8       ui1_idx = 0;


    ui1_idx = 0;
    while ( (0 == pt_info[ui1_idx]) && ui1_idx < 10)
    {
        ui1_idx ++;
    }

    if (ui1_idx >= 10)  /* First 10 elems value is 0, not VIZIO VUR in used*/
    {
        DBG_INFO( ("\n<wzd remote>wifi remote scan : %d\n", i4_ret));
        if (i4_ret < 0)
        {
            DBG_INFO( ("\n<wzd remote>---%s, stop_scan : %d\n", __FUNCTION__, i4_ret));
            pt_this->b_remote_paired = FALSE;
            pt_this->b_remote_searching = FALSE;
            c_wgl_set_visibility(pt_this->h_animation_icon, WGL_SW_HIDE);
            pt_this->e_state = WIFI_REMOTE_PARING_FAIL;
            _wzd_page_wifi_remote_paring_update_by_state(TRUE);
        }
    }
    else    /* VIZIO BT RC was in used, success*/
    {
        DBG_INFO( ("\n<wzd remote> wifi remote used successful\n"));
        pt_this->b_remote_paired = TRUE;
        pt_this->b_remote_searching = FALSE;
        c_wgl_set_visibility(pt_this->h_animation_icon, WGL_SW_HIDE);
        pt_this->e_state = WIFI_REMOTE_PARING_SUCCESS;
        _wzd_page_wifi_remote_paring_update_by_state(TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_scan_wait_timer_notify_fct
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
static VOID _wzd_wifi_scan_wait_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_wifi_scan_wait_do_timer_nfy, pv_tag, (0), TRUE);
    return;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_remote_found_delay_do_timer_nfy
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
static VOID _wzd_wifi_remote_found_delay_do_timer_nfy(VOID* pv_data,
                                 SIZE_T  z_data_size)
{
    DBG_INFO( ("\n<wzd remote> --- remote found delay --- \n"));

    if (a_wzd_is_resume_from_menu_setup() || a_wzd_is_resume_from_wifi_unpairing())
    {
        a_wzd_exit();
    }
    else
    {
        wzd_page_goto(WZD_PAGE_NAVI_NEXT_PAGE);
    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_remote_found_delay_timer_notify_fct
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
static VOID _wzd_wifi_remote_found_delay_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_wifi_remote_found_delay_do_timer_nfy, pv_tag, (0), TRUE);
    return;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_remote_pair_non_ack_do_timer_nfy
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
static VOID _wzd_wifi_remote_pair_non_ack_do_timer_nfy(VOID* pv_data,
                                 SIZE_T  z_data_size)
{
    DBG_INFO( ("\n<####%s(%d)wzd remote pairing> --- pair_non_ack --- \n",__FUNCTION__,__LINE__));

	_wzd_page_wifi_remote_paring_show_dlg( MLM_WZD_KEY_BT_REMOTE_NOT_FOUND_DESC,
                                           MLM_WZD_KEY_BT_REMOTE_DLG_RETRY,
                                           MLM_WZD_KEY_BT_REMOTE_DLG_SKIP);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_wifi_remote_pair_non_ack_timer_notify_fct
 *
 * Description: show error dialog if not receive the pair command for 1 mintus 
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_wifi_remote_pair_non_ack_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag)
{
    wzd_async_invoke(_wzd_wifi_remote_pair_non_ack_do_timer_nfy, pv_tag, (0), TRUE);
    return;
}

#ifdef APP_WFD_SUPPORT
static VOID _wzd_wifi_remote_p2p_connected(VOID* pv_data,
                                 SIZE_T  z_data_size)
{
	DBG_INFO( ("[WZD] ====> WLAN_NOTIFY_P2P_DEVICE_FOUND\n"));
	gt_wifi_remote_paring.b_remote_paired = TRUE;
	gt_wifi_remote_paring.b_remote_searching = FALSE;
	c_wgl_set_visibility(gt_wifi_remote_paring.h_animation_icon, WGL_SW_HIDE);
	gt_wifi_remote_paring.e_state = WIFI_REMOTE_PARING_SUCCESS;
	_wzd_page_wifi_remote_paring_update_by_state(TRUE);
}

static void _wzd_page_wifi_remote_notify_entry(int i4CallbackId, VOID *pParam)
{
    INT32  i4_ret = WZDR_OK;
	WZD_WIFI_REMOTE_PARING_MEMBER_T*      pt_this = &gt_wifi_remote_paring;

    DBG_INFO( ("\n<WZD> %s,%s,%d,i4CallbackId=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                i4CallbackId));

    switch (i4CallbackId)
    {
        case WLAN_NOTIFY_AP_STA_CONNECTED:
        {
			if (WIFI_REMOTE_PARING_SEARCHING != pt_this->e_state)
            {
                return;
            }
			
			DBG_INFO( ("<####WZD%s(%d)> receieve WLAN_NOTIFY_AP_STA_CONNECTED now\n",__FUNCTION__,__LINE__));
			i4_ret = wzd_async_invoke(_wzd_wifi_remote_p2p_connected, NULL, (0), TRUE);
			if(i4_ret < 0)
			{
				DBG_ERROR( ("<WZD> wzd_async_invoke fail @ file = %s, line = %d\n\r", __FILE__, __LINE__));
			}
        }
        	break;
         /*notify end-user press red and green buttons*/	
		 case WLAN_NOTIFY_P2P_WPS_RECEIVE_DPID_PBC:
         {
			if (WIFI_REMOTE_PARING_ACTIVING != pt_this->e_state)
			{
				return;
			}

			DBG_INFO( ("\n####%s(%d)WLAN_NOTIFY_P2P_WPS_RECEIVE_DPID_PBC\n",__FUNCTION__,__LINE__));
			
			/*stop the timer if receive pair command within 1 minitus*/
			i4_ret = c_timer_stop(pt_this->h_remote_pair_non_ack_timer); 
			DBG_INFO( ("<####WZD%s(%d)> c_timer_stop(&pt_this->h_remote_pair_non_ack_timer) return[%d]\n",__FUNCTION__,__LINE__,i4_ret));

			if(pt_this->e_state == WIFI_REMOTE_PARING_SEARCHING)
			{
				DBG_INFO( ("\n####%s(%d) return \n",__FUNCTION__,__LINE__));
				return;
			}
			
			c_wgl_insert(pt_this->h_animation_icon,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          FALSE);

		    c_wgl_set_visibility(pt_this->h_animation_icon, WGL_SW_NORMAL);
		    
			/*Start paring*/
		    _wzd_page_wifi_remote_start_pairing();

			/* enable the animation scan timer */
		    c_timer_start(pt_this->h_timer,
		                            1000,
		                            X_TIMER_FLAG_ONCE,
		                            _wzd_wifi_remote_paring_timer_notify_fct,
		                            NULL);

		    c_timer_start(pt_this->h_wait_timer,
		                            2000,
		                            X_TIMER_FLAG_ONCE,
		                            _wzd_wifi_scan_wait_timer_notify_fct,
		                            NULL);
         }
            break;
        default:
            break;
    }
}
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_search_and_pair
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
static INT32 _wzd_page_wifi_remote_search_and_pair(VOID)
{
    INT32       i4_ret = WZDR_OK;
    WZD_WIFI_REMOTE_PARING_MEMBER_T*      pt_this = &gt_wifi_remote_paring;

    /*init search/pair status */
    pt_this->b_remote_paired = FALSE;
    pt_this->b_remote_searching = TRUE;
    pt_this->ui1_timer_count = 0;
    
    RET_ON_ERR (a_cfg_custom_set_wifi_remote_pair_status(WIFI_REMOTE_PAIR_STATUS_PAIRING));

#ifdef APP_WFD_SUPPORT
	if(wfd_client_get_p2p_init_state() < 0)
	{
		DBG_INFO( ("<####WZD%s(%d)>  p2p is in disable state, enable now\n",__FUNCTION__,__LINE__));
		i4_ret = wfd_client_start(_wzd_page_wifi_remote_notify_entry);
		if(i4_ret < 0)
		{
			DBG_INFO( ("<####WZD%s(%d)>  wfd_client_start failed %d\n",__FUNCTION__,__LINE__,i4_ret));
		}
	}
	else
	{
		DBG_INFO( ("<####WZD>  p2p is in enable state\n"));
		wfd_client_reg_callback(_wzd_page_wifi_remote_notify_entry);
	}
#endif

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_data_chg
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
static VOID _wzd_page_wifi_remote_paring_data_chg(VOID*    pv_tag,
                                     UINT32   ui4_msg,
                                     VOID*    pv_param1,
                                     VOID*    pv_param2)
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*      pt_this = &gt_wifi_remote_paring;

    switch( ui4_msg )
    {
        case WZD_DLG_MSG_BTN_FOCUSED:
            break;

        case WZD_DLG_MSG_KEY_INPUT:
            if( BTN_SELECT == (UINT32)pv_param1 )
            {
                if( WZD_DLG_BTN_TYPE_01 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2 )  /*User presses Retry/Back*/
                {
                    wzd_dlg_hide( pt_this->h_dlg );
                    c_wgl_set_focus(pt_this->h_image_icon, FALSE);
                    pt_this->e_state = WIFI_REMOTE_PARING_ACTIVING;
                    _wzd_page_wifi_remote_paring_update_by_state(TRUE);
                }
                else if( WZD_DLG_BTN_TYPE_02 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2 )  /* User presses Skip. */
                {
					wzd_dlg_hide( pt_this->h_dlg );
					c_timer_stop(pt_this->h_remote_pair_non_ack_timer); 
					pt_this->e_state = WIFI_REMOTE_PARING_STATE_LAST_VALID_ITEM;
                    if (a_wzd_is_resume_from_menu_setup() || a_wzd_is_resume_from_wifi_unpairing())
                    {
                        a_wzd_exit();
                    }
                    else
                    {
                        wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );
                    }
                }
            }
            break;

        case WZD_DLG_MSG_DLG_HIDED:
            break;

        default:
            break;
    }

}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_create_image_icon
 *
 * Description: This function creates an icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_wifi_remote_paring_create_image_icon (VOID)
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*      pt_this = &gt_wifi_remote_paring;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    GL_RECT_T                   t_rect = {0};
    INT32                       i4_ret;
    WGL_IMG_INFO_T              t_img_info;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_WIFI_REMOTE_IMAGE_ICON_X,
                      WZD_WIFI_REMOTE_IMAGE_ICON_Y,
                      WZD_WIFI_REMOTE_IMAGE_ICON_W,
                      WZD_WIFI_REMOTE_IMAGE_ICON_H);

    i4_ret = c_wgl_create_widget(h_layout_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &pt_this->h_image_icon
                                 );
    RET_ON_ERR (i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(pt_this->h_image_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_TOP,
                          NULL);
    RET_ON_ERR (i4_ret);

    /* Set default title icon */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_wzd_img_remote_pairing_with_hands;
    t_img_info.u_img_data.t_standard.t_disable = h_g_wzd_img_remote_pairing_with_hands;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_remote_pairing_with_hands;
    RET_ON_ERR (c_wgl_do_cmd(pt_this->h_image_icon, WGL_CMD_GL_SET_IMAGE, (VOID*)WGL_IMG_FG, (VOID*)&t_img_info));

    RET_ON_ERR (c_wgl_set_visibility (pt_this->h_image_icon, WGL_SW_HIDE));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_create_animation_icon
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_wifi_remote_paring_create_animation_icon(HANDLE_T  h_parent,
                                           HANDLE_T* ph_widget)
{
	INT32			i4_ret;
	GL_RECT_T		t_rect;
	WGL_IMG_INFO_T		 t_img_info;

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
	SET_RECT_BY_SIZE(&t_rect,
					 WZD_WIFI_REMOTE_ICON_X,
					 WZD_WIFI_REMOTE_ICON_Y,
					 WZD_WIFI_REMOTE_ICON_W,
					 WZD_WIFI_REMOTE_ICON_H);

	i4_ret = c_wgl_create_widget(h_parent,
								HT_WGL_WIDGET_ICON,
								WGL_CONTENT_ICON_DEF,
								WGL_BORDER_TIMG,
								&t_rect,
								NULL,
								255,
								(VOID *)0,
								NULL,
								ph_widget);
	RET_ON_ERR(i4_ret);

	/* set icon alignment */
	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_ICON_SET_ALIGN,
						  (VOID*)WGL_AS_CENTER_CENTER,
						  NULL);
	RET_ON_ERR(i4_ret);

	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
	t_img_info.e_type							 = WGL_IMG_SET_STANDARD;
	t_img_info.u_img_data.t_standard.t_enable	 = h_g_wdk_img_loading_icon_1;
	t_img_info.u_img_data.t_standard.t_disable	 = h_g_wdk_img_loading_icon_1;
	t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_img_loading_icon_1;

	i4_ret = c_wgl_do_cmd(*ph_widget,
						  WGL_CMD_GL_SET_IMAGE,
						  WGL_PACK(WGL_IMG_FG),
						  WGL_PACK(&t_img_info));
	RET_ON_ERR(i4_ret);

	/* make icon invisible */
	i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
	RET_ON_ERR(i4_ret);

	return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_set_image_icon
 *
 * Description: This function creates an icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_wifi_remote_paring_set_image_icon (HANDLE_T      h_img)
{
    WGL_IMG_INFO_T              t_img_info;

    /* Set default title icon */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_img;
    t_img_info.u_img_data.t_standard.t_disable      = h_img;
    t_img_info.u_img_data.t_standard.t_highlight    = h_img;
    RET_ON_ERR (c_wgl_do_cmd(gt_wifi_remote_paring.h_image_icon,
                            WGL_CMD_GL_SET_IMAGE,
                            (VOID*)WGL_IMG_FG,
                            (VOID*)&t_img_info));

    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_create_dlg
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
static INT32 _wzd_page_wifi_remote_paring_create_dlg (VOID)
{
    WZD_DLG_INIT_T              t_dlg_init;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    WZD_WIFI_REMOTE_PARING_MEMBER_T*      pt_this = &gt_wifi_remote_paring;

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN;
    t_dlg_init.pf_fct = _wzd_page_wifi_remote_paring_data_chg;
    t_dlg_init.pv_tag = NULL;
    t_dlg_init.ui4_hide_timer = 0;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;

    wzd_dlg_create( &t_dlg_init, &pt_this->h_dlg );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_show_dlg
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
static INT32 _wzd_page_wifi_remote_paring_show_dlg (
                                UINT16 ui2_content,
                                UINT16 ui2_left_btn,
                                UINT16 ui2_right_btn)
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*        pt_this = &gt_wifi_remote_paring;

    if( NULL_HANDLE == pt_this->h_dlg )
    {
        return WZDR_FAIL;
    }

    wzd_dlg_set_text( pt_this->h_dlg, WZD_TEXT(ui2_content), TRUE );

    wzd_dlg_set_btn_text( pt_this->h_dlg, WZD_DLG_BTN_TYPE_01, WZD_TEXT(ui2_left_btn), FALSE );

    wzd_dlg_set_btn_text( pt_this->h_dlg, WZD_DLG_BTN_TYPE_02, WZD_TEXT(ui2_right_btn), FALSE );

    wzd_dlg_show( pt_this->h_dlg , TRUE );

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_pairing_return_nfy_cb
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
static VOID _wzd_page_wifi_remote_pairing_return_nfy_cb(VOID)
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*          pt_this = &gt_wifi_remote_paring;
    
    if (!a_wzd_is_resume_from_wifi_unpairing() && !a_wzd_is_resume_from_menu_setup())
    {
        if ((pt_this->e_state == WIFI_REMOTE_PARING_FAIL) ||
            (pt_this->e_state == WIFI_REMOTE_PARING_SUCCESS)||
            (pt_this->e_state == WIFI_REMOTE_PARING_ACTIVING)||
            (pt_this->e_state == WIFI_REMOTE_PARING_SEARCHING))
        {
            wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
        }
    }
    
    return;
}

/*----------------------------------------------------------------------------
 * Name: VOID_wzd_page_wifi_remote_pairing_exit_nfy_cb
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
static VOID _wzd_page_wifi_remote_pairing_exit_nfy_cb(VOID)
{
    UINT8                                   ui1_wifi_remote_pair_status;

    a_cfg_custom_get_wifi_remote_pair_status(&ui1_wifi_remote_pair_status);
    if(ui1_wifi_remote_pair_status != WIFI_REMOTE_PAIR_STATUS_PAIRED)
    {
    	if(gt_wifi_remote_paring.e_state != WIFI_REMOTE_PARING_FAIL)
    	{
	        gt_wifi_remote_paring.e_state = WIFI_REMOTE_PARING_FAIL;
	        _wzd_page_wifi_remote_paring_update_by_state(TRUE);
        }
    }
    
    return;
}

 /*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_create
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
static INT32 _wzd_page_wifi_remote_paring_create (VOID)
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*          pt_this = &gt_wifi_remote_paring;
    HANDLE_T                        h_layout_frm = NULL_HANDLE;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    c_memset( &gt_wifi_remote_paring, 0, sizeof(WZD_WIFI_REMOTE_PARING_MEMBER_T) );

    RET_ON_ERR (_wzd_page_wifi_remote_paring_create_image_icon ());
    RET_ON_ERR (_wzd_page_wifi_remote_paring_create_animation_icon(h_layout_frm, &pt_this->h_animation_icon));
    
    RET_ON_ERR (_wzd_page_wifi_remote_paring_create_dlg());           /* Create dialog. */

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_dsty
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
static INT32 _wzd_page_wifi_remote_paring_dsty(VOID)
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*          pt_this = &gt_wifi_remote_paring;
	
    if( pt_this->h_dlg )
    {
        wzd_dlg_destroy( pt_this->h_dlg );
        pt_this->h_dlg = NULL_HANDLE;
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_wifi_remote_paring_update_by_state
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
static INT32 _wzd_page_wifi_remote_paring_update_by_state(BOOL b_repaint)
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*          pt_this = &gt_wifi_remote_paring;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    BOOL                        b_repaint_main_frame = FALSE;
    GL_RECT_T                   t_rect = {0};
    
    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    if (WIFI_REMOTE_PARING_ACTIVING == pt_this->e_state)
    {
        RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_BT_REMOTE_SEARCH_DESC_TEXT), NULL_HANDLE)); 

		RET_ON_ERR (wzd_view_footer_set_visibility(FALSE));
        
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));

        SET_RECT_BY_SIZE (& t_rect,
                          WZD_WIFI_REMOTE_IMAGE_ICON_X,
	                      WZD_WIFI_REMOTE_IMAGE_ICON_Y,
	                      WZD_WIFI_REMOTE_IMAGE_ICON_W,
	                      WZD_WIFI_REMOTE_IMAGE_ICON_H);
        /* Update display */
        RET_ON_ERR (c_wgl_move( pt_this->h_image_icon, &t_rect,WGL_NO_AUTO_REPAINT));
                                
        RET_ON_ERR (_wzd_page_wifi_remote_paring_set_image_icon (h_g_wzd_img_remote_pairing_with_hands));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_image_icon, WGL_SW_NORMAL));  
        
        RET_ON_ERR (_wzd_page_wifi_remote_search_and_pair());

		/*h_remote_pair_non_ack_timer's timeout event --- show error dialog*/
        RET_ON_ERR (c_timer_start(pt_this->h_remote_pair_non_ack_timer,
                            60000,
                            X_TIMER_FLAG_ONCE,
                            _wzd_wifi_remote_pair_non_ack_timer_notify_fct,
                            NULL));

        b_repaint_main_frame = TRUE;
    }
    else if (WIFI_REMOTE_PARING_FAIL == pt_this->e_state)
    {
    #ifdef APP_WFD_SUPPORT
		wfd_client_unreg_callback(_wzd_page_wifi_remote_notify_entry);
	#endif
		RET_ON_ERR (wzd_view_footer_set_visibility(FALSE));
        
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));

        RET_ON_ERR (_wzd_page_wifi_remote_paring_set_image_icon (h_g_wzd_img_remote_pairing_with_hands));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_image_icon, WGL_SW_NORMAL));
        
        _wzd_page_wifi_remote_paring_show_dlg(MLM_WZD_KEY_BT_REMOTE_NOT_FOUND_DESC,
                                              MLM_WZD_KEY_BT_REMOTE_DLG_RETRY,
                                              MLM_WZD_KEY_BT_REMOTE_DLG_SKIP);
        b_repaint_main_frame = TRUE;
    }
    else if (WIFI_REMOTE_PARING_SUCCESS == pt_this->e_state)
    {
    #ifdef APP_WFD_SUPPORT
		wfd_client_unreg_callback(_wzd_page_wifi_remote_notify_entry);
	#endif
		RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_BT_REMOTE_FOUND_DESC), h_g_wzd_img_checkmark_white_dialog)); 
        RET_ON_ERR (wzd_view_footer_set_visibility(FALSE));
        
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
        RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));

        SET_RECT_BY_SIZE (& t_rect,
                      (1280-184)/2,
                      720 - 120 - 482,
                      184,
                      482);
        /* Update display */
        RET_ON_ERR (c_wgl_move( pt_this->h_image_icon, &t_rect, WGL_NO_AUTO_REPAINT));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_image_icon, WGL_SW_NORMAL));
        RET_ON_ERR (_wzd_page_wifi_remote_paring_set_image_icon (h_g_wzd_img_remote));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_image_icon, WGL_SW_NORMAL)); 
        
        RET_ON_ERR (c_timer_start(pt_this->h_remote_found_delay_timer,
                    3000,
                    X_TIMER_FLAG_ONCE,
                    _wzd_wifi_remote_found_delay_timer_notify_fct,
                    NULL));
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

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_on_show
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
static INT32 _wzd_page_wifi_remote_paring_on_show (
    UINT32                      ui4_page_id
    )
{
    WZD_WIFI_REMOTE_PARING_MEMBER_T*        pt_this = &gt_wifi_remote_paring;
    UINT8                                   ui1_wifi_remote_pair_status;

    RET_ON_ERR (c_timer_create(&pt_this->h_timer)); /*Create timer*/
    RET_ON_ERR (c_timer_create(&pt_this->h_wait_timer)); /*Create timer*/
    RET_ON_ERR (c_timer_create(&pt_this->h_remote_found_delay_timer)); /*Create timer*/
    RET_ON_ERR (c_timer_create(&pt_this->h_remote_pair_non_ack_timer)); /*Create timer for enter pairing page but not receive pair command for 1 minitus*/

    a_cfg_custom_get_wifi_remote_pair_status(&ui1_wifi_remote_pair_status);
    if(ui1_wifi_remote_pair_status == WIFI_REMOTE_PAIR_STATUS_PAIRED)
        pt_this->e_state = WIFI_REMOTE_PARING_SUCCESS;
    else
        pt_this->e_state = WIFI_REMOTE_PARING_ACTIVING;
    _wzd_page_wifi_remote_paring_update_by_state(TRUE);


    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_wifi_remote_paring_on_hide
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
static INT32 _wzd_page_wifi_remote_paring_on_hide(UINT32 ui4_page_id)
{
    if (gt_wifi_remote_paring.b_remote_searching == TRUE)
    {
        DBG_INFO( ("\n<wzd remote>---%s, stop_scan.\n", __FUNCTION__));
    }

#ifdef APP_WFD_SUPPORT
	wfd_client_unreg_callback(_wzd_page_wifi_remote_notify_entry);
#endif

    if (gt_wifi_remote_paring.h_timer != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete(gt_wifi_remote_paring.h_timer));
        gt_wifi_remote_paring.h_timer = NULL_HANDLE;
    }

    if (gt_wifi_remote_paring.h_wait_timer != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete(gt_wifi_remote_paring.h_wait_timer));
        gt_wifi_remote_paring.h_wait_timer = NULL_HANDLE;
    }

    if (gt_wifi_remote_paring.h_remote_found_delay_timer != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete(gt_wifi_remote_paring.h_remote_found_delay_timer));
        gt_wifi_remote_paring.h_remote_found_delay_timer = NULL_HANDLE;
    }

    if (gt_wifi_remote_paring.h_remote_pair_non_ack_timer != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete(gt_wifi_remote_paring.h_remote_pair_non_ack_timer));
        gt_wifi_remote_paring.h_remote_pair_non_ack_timer = NULL_HANDLE;
    }
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_wifi_remote_paring_get_page_info_data
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
INT32 wzd_page_wifi_remote_paring_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data)
{
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );
    DBG_INFO( ("====> wzd_page_wifi_remote_paring_get_page_info_data\n"));
    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = NULL;
    pt_info_data->pf_return_nfy_fct        = _wzd_page_wifi_remote_pairing_return_nfy_cb;
    pt_info_data->pf_exit_nfy_fct          = _wzd_page_wifi_remote_pairing_exit_nfy_cb;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_page_wifi_remote_paring_create;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_page_wifi_remote_paring_dsty;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_page_wifi_remote_paring_on_show;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_page_wifi_remote_paring_on_hide;


    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_wifi_remote_paring_nfy_sel
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
INT32 wzd_page_wifi_remote_paring_nfy_sel(UINT16               ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}


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
 * $RCSfile: bluetooth_timer.c,v $
 * $Revision: #3 $
 * $Date: 2015/11/14 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file implements bluetooth timer.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

/*-----------------------------------------------------------------------------
                        include files
-----------------------------------------------------------------------------*/

#include "c_os.h"
#include "bluetooth.h"
#include "bluetooth_timer.h"

typedef enum{
    BT_APP_TIMER_BITRATE,        // bitrate timer, to get bitrate from BTM and update UI
    BT_APP_TIMER_OSD_DISPLAY,    // OSD display timer, for auto display
    BT_APP_TIMER_RSSI_UPDATE,    // rssi update timer, to monitor signal strength of connected SRC device
    BT_APP_TIMER_AVRCP_CONNECT,  // avrcp connect timer
} BT_APP_TIMER_TYPE;

#define BT_BITRATE_TIME_OUT   1 * 1000   // 1s, time out for bitrate timer
#define BT_OSD_DISPLAY_TIME   5 * 1000   // 5s, time out for OSD display timer
#define BT_RSSI_UPDATE_TIME   5 * 1000   // 5s, time out for rssi update timer
#define BT_AVRCP_CONNECT_TIME 5 * 1000   // 5s, time out for avrcp connect timer

typedef struct{
    BT_APP_TIMER_TYPE  e_timer_type;
    UINT32             ui4_time_out;
    TIMER_FLAG_T       e_timer_flag;
    x_os_timer_cb_fct  pf_call_back;   // call back function after time out
    HANDLE_T           h_timer;
} BT_APP_TIMER_INTO_T;

static HANDLE_T    h_bt_sink_dev_scan_timer = NULL_HANDLE;

/**---------------------------------------------------------------------------
  * Name          - _bt_app_bitrate_timer_cb
  *
  * Description  - callback function for bitrate timer
  *---------------------------------------------------------------------------*/
static VOID _bt_app_bitrate_timer_cb(HANDLE_T pt_handle, VOID* pv_tag)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    
    t_bt_msg.msg_type = BT_APP_MSG_REQ_GET_BITRATE; 

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send bitrate update msg fail\n"));
    }
    
    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_osd_display_timer_cb
  *
  * Description  - callback function for osd display timer
  *---------------------------------------------------------------------------*/
static VOID _bt_app_ui_osd_display_timer_cb(HANDLE_T pt_handle, VOID* pv_tag)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    
    t_bt_msg.msg_type = BT_APP_MSG_REQ_HIDE_PLAY_WINDOW; 

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send hide play window msg fail\n"));
    }
    
    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_ui_rssi_update_timer_cb
  *
  * Description  - callback function for rssi update timer
  *---------------------------------------------------------------------------*/
static VOID _bt_app_ui_rssi_update_timer_cb(HANDLE_T pt_handle, VOID* pv_tag)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    
    t_bt_msg.msg_type = BT_APP_MSG_REQ_GET_RSSI_LEVEL; 

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send hide play window msg fail\n"));
    }
    
    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_ui_avrcp_connect_timer_cb
  *
  * Description  - callback function for AVRCP connect timer
  *---------------------------------------------------------------------------*/
static VOID _bt_app_ui_avrcp_connect_timer_cb(HANDLE_T pt_handle, VOID* pv_tag)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    
    t_bt_msg.msg_type = BT_APP_MSG_EVENT_NO_AVRCP; 

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send no AVRCP msg fail\n"));
    }
    
    return ;
}

static BT_APP_TIMER_INTO_T _gt_bt_app_timer[] = 
{
    {
        BT_APP_TIMER_BITRATE,
        BT_BITRATE_TIME_OUT,
        X_TIMER_FLAG_REPEAT,
        _bt_app_bitrate_timer_cb,
        NULL_HANDLE
    },
    {
        BT_APP_TIMER_OSD_DISPLAY,
        BT_OSD_DISPLAY_TIME,
        X_TIMER_FLAG_ONCE,
        _bt_app_ui_osd_display_timer_cb,
        NULL_HANDLE
    },
    {
        BT_APP_TIMER_RSSI_UPDATE,
        BT_RSSI_UPDATE_TIME,
        X_TIMER_FLAG_REPEAT,
        _bt_app_ui_rssi_update_timer_cb,
        NULL_HANDLE
    },
    {
        BT_APP_TIMER_AVRCP_CONNECT,
        BT_AVRCP_CONNECT_TIME,
        X_TIMER_FLAG_ONCE,
        _bt_app_ui_avrcp_connect_timer_cb,
        NULL_HANDLE
    },
};

static INT32 _bt_app_restart_timer(BT_APP_TIMER_TYPE e_timer_type)
{
    INT32 i4_ret;
    UINT8 ui1_idx = 0;

    for (ui1_idx = 0; ui1_idx < sizeof(_gt_bt_app_timer)/sizeof(BT_APP_TIMER_INTO_T); ui1_idx++)
    {
        if (e_timer_type == _gt_bt_app_timer[ui1_idx].e_timer_type)
        {
            if(NULL_HANDLE != _gt_bt_app_timer[ui1_idx].h_timer)
            {
                c_timer_stop(_gt_bt_app_timer[ui1_idx].h_timer);
                c_timer_delete(_gt_bt_app_timer[ui1_idx].h_timer);
                _gt_bt_app_timer[ui1_idx].h_timer = NULL_HANDLE;
            }
            
            i4_ret = c_timer_create(&(_gt_bt_app_timer[ui1_idx].h_timer));
            if((OSR_OK != i4_ret) || (NULL_HANDLE == _gt_bt_app_timer[ui1_idx].h_timer))
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: create timer fail, %d\n", i4_ret));
                return BT_APPR_FAIL;
            }

            i4_ret = c_timer_start(_gt_bt_app_timer[ui1_idx].h_timer,
                                   _gt_bt_app_timer[ui1_idx].ui4_time_out,
                                   _gt_bt_app_timer[ui1_idx].e_timer_flag,
                                   _gt_bt_app_timer[ui1_idx].pf_call_back,
                                   (VOID *)NULL);
            if (OSR_OK != i4_ret)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: start timer fail, %d\n", i4_ret));
                return BT_APPR_FAIL;
            }
        }
    }

    return BT_APPR_OK;
}

static INT32 _bt_app_stop_timer(BT_APP_TIMER_TYPE e_timer_type)
{
    UINT8 ui1_idx = 0;

    for (ui1_idx = 0; ui1_idx < sizeof(_gt_bt_app_timer)/sizeof(BT_APP_TIMER_INTO_T); ui1_idx++)
    {
        if (e_timer_type == _gt_bt_app_timer[ui1_idx].e_timer_type)
        {
            if (NULL_HANDLE != _gt_bt_app_timer[ui1_idx].h_timer)
            {
                c_timer_stop(_gt_bt_app_timer[ui1_idx].h_timer);
                c_timer_delete(_gt_bt_app_timer[ui1_idx].h_timer);
                _gt_bt_app_timer[ui1_idx].h_timer = NULL_HANDLE;
            }
        }
    }

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_start_bitrate_timer
  *
  * Description  - start bitrate timer to get bitrate from BTM and update UI
  *                     after starting bluetooth audio playback.
  *                     
  *---------------------------------------------------------------------------*/
INT32 bt_app_start_bitrate_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> start bitrate timer\n"));
    
    return _bt_app_restart_timer(BT_APP_TIMER_BITRATE);
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_stop_bitrate_timer
  *
  * Description  - stop bitrate timer
  *---------------------------------------------------------------------------*/
INT32 bt_app_stop_bitrate_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> stop bitrate timer\n"));
    
    return _bt_app_stop_timer(BT_APP_TIMER_BITRATE);
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_restart_osd_display_timer
  *
  * Description  - start osd display timer. After it timeout, hide playback window.
  *                     This timer is used for auto display. If Auto Display is on and Visualizer is on, 
  *                     OSD should only display 5 second on Play window
  *                     
  *---------------------------------------------------------------------------*/
INT32 bt_app_ui_restart_osd_display_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> start osd display timer\n"));
    
    return _bt_app_restart_timer(BT_APP_TIMER_OSD_DISPLAY);
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_stop_osd_display_timer
  *
  * Description  - stop osd display timer
  *---------------------------------------------------------------------------*/
INT32 bt_app_ui_stop_osd_display_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> stop osd display timer\n"));
    
    return _bt_app_stop_timer(BT_APP_TIMER_OSD_DISPLAY);
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_restart_rssi_update_timer
  *
  * Description  - start rssi update timer. After it timeout, update current signal strength.
  *                     
  *---------------------------------------------------------------------------*/
INT32 bt_app_ui_restart_rssi_update_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> start rssi update timer\n"));
    
    _bt_app_restart_timer(BT_APP_TIMER_RSSI_UPDATE);
    
    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_stop_rssi_update_timer
  *
  * Description  - stop rssi update timer
  *---------------------------------------------------------------------------*/
INT32 bt_app_ui_stop_rssi_update_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> stop rssi update timer\n"));
    
    return _bt_app_stop_timer(BT_APP_TIMER_RSSI_UPDATE);
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_start_avrcp_connect_timer
  *
  * Description  - start avrcp connect timer. 
  *                     When A2DP is established and AVRCP hasn't been established, start this timer.
  *                     After time out, we think AVRCP cannot be established.
  *                     
  *---------------------------------------------------------------------------*/
INT32 bt_app_start_avrcp_connect_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> start avrcp connect timer\n"));
    
    _bt_app_restart_timer(BT_APP_TIMER_AVRCP_CONNECT);
    
    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_stop_avrcp_connect_timer
  *
  * Description  - stop avrcp connect timer
  *---------------------------------------------------------------------------*/
INT32 bt_app_stop_avrcp_connect_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> stop avrcp connect timer\n"));
    
    return _bt_app_stop_timer(BT_APP_TIMER_AVRCP_CONNECT);
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_create_sink_device_scan_timer
  *
  * Description  - create sink device scan timer
  *---------------------------------------------------------------------------*/
INT32 bt_app_create_sink_device_scan_timer(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_ERR(("<BT_APP> Enter %s\n",__FUNCTION__));

    if (NULL_HANDLE == h_bt_sink_dev_scan_timer)
    {
        i4_ret = c_timer_create(&h_bt_sink_dev_scan_timer);
        if (OSR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("<BT_APP> ERR: create sink device scan timer fail, %d\n", i4_ret));
            return BT_APPR_FAIL;
        }
    }

    return BT_APPR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_sink_device_scan_timer_cb
  *
  * Description  - 
  *---------------------------------------------------------------------------*/
VOID bt_app_sink_device_scan_timer_cb(HANDLE_T    pt_handle, 
                                    VOID*       pv_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    
    BT_APP_LOG_ERR(("<BT_APP> Enter %s\n",__FUNCTION__));

    t_bt_msg.msg_type = BT_APP_MSG_NFY_SINK_SCAN_FINISH; 

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send BT_APP_MSG_NFY_SINK_SCAN_FINISH fail\n"));
    }

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_start_sink_device_scan_timer
  *
  * Description  - 
  *---------------------------------------------------------------------------*/
INT32 bt_app_start_sink_device_scan_timer(UINT32 ui4_msecond)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_ERR(("<BT_APP> Enter %s\n",__FUNCTION__));

    if (NULL_HANDLE != h_bt_sink_dev_scan_timer)
    {
        i4_ret = c_timer_start(h_bt_sink_dev_scan_timer,
                               ui4_msecond,
                               X_TIMER_FLAG_ONCE,
                               bt_app_sink_device_scan_timer_cb,
                               (VOID *)NULL);
        if (OSR_OK != i4_ret)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: start sink device scan timer fail, %d\n", i4_ret));
            return BT_APPR_FAIL;
        }
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: sink device scan timer not create\n"));
        return BT_APPR_FAIL;
    }

    return BT_APPR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_stop_sink_device_scan_timer
  *
  * Description  - 
  *---------------------------------------------------------------------------*/
INT32 bt_app_stop_sink_device_scan_timer(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_ERR(("<BT_APP> Enter %s\n",__FUNCTION__));

    if (NULL_HANDLE != h_bt_sink_dev_scan_timer)
    {    
         i4_ret = c_timer_stop(h_bt_sink_dev_scan_timer);
         
         if (OSR_OK != i4_ret)
         {
             BT_APP_LOG_ERR(("<BT_APP> ERR: stop sink device scan timer fail, %d\n", i4_ret));
             return BT_APPR_FAIL;
         }
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: sink device scan timer not create\n"));
        return BT_APPR_FAIL;
    }
    
    return BT_APPR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_delay
  *
  * Description  - 
  *---------------------------------------------------------------------------*/
VOID bt_app_delay(UINT32 u4_ms)
{
    UINT32  u4_sys_tick_period = c_os_get_sys_tick_period();
    UINT32  u4_init_sys_tick_count = c_os_get_sys_tick();
    UINT32  u4_cur_sys_tick_count = u4_init_sys_tick_count;
    UINT32  u4_total_delay_time = 0;

    BT_APP_LOG_ERR(("<BT_APP> Enter Func:%s, sys tick count[%d], period[%d], delay time[%d]\n", \
        __FUNCTION__, u4_init_sys_tick_count, u4_sys_tick_period, u4_ms));

    while (u4_total_delay_time < u4_ms)
    {
        // get current sys tick count
        u4_cur_sys_tick_count = c_os_get_sys_tick();

        // calculate the time pass since start
        u4_total_delay_time = (u4_cur_sys_tick_count - u4_init_sys_tick_count) * c_os_get_sys_tick_period();
        
        continue;
    }

    BT_APP_LOG_ERR(("<BT_APP> Exit Func:%s, current tick count[%d], total delay time[%d]\n", \
        __FUNCTION__, u4_cur_sys_tick_count, u4_total_delay_time));
    
}


#endif


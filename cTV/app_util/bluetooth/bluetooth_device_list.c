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
 * $RCSfile: bluetooth_device_list.c,v $
 * $Revision: #6 $
 * $Date: 2015/11/14 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file implements bluetooth device list.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

/*-----------------------------------------------------------------------------
                        include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "c_os.h"

#include "u_dbg.h"
#include "c_dbg.h"

#include "bluetooth.h"
#include "bluetooth_device_list.h"
#include "bluetooth_device.h"
#include "c_bt_mw_a2dp_src.h"
#include "bluetooth_global_variables.h"
#include "c_bt_mw_hidh.h"
#include "mtk_bt_service_a2dp_wrapper.h"

extern BLUETOOTH_STATE_T         _e_bluetooth_state;

// page info for bluetooth sink device list window
BT_APP_SINK_DEV_LIST_INFO_T _gt_bt_sink_dev_list_info={0};
static BOOL _gt_bt_sink_dev_list_init = FALSE;

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_device_list_get_focused_device
  *
  * Description  - get the focused device in sink device list
  *
  * Outputs       - pt_device: the focused device
  *---------------------------------------------------------------------------*/
INT32 bt_app_ui_sink_device_list_get_focused_device(BT_TARGET_DEV_INFO *pt_device)
{
    static BT_APP_SINK_DEV_LIST_INFO_T r_sink_dev_list_info;
    UINT8   u1_first_dev_index = 0;
    UINT8   u1_focus_row_index = 0;
    UINT8   u1_focus_dev_index = 0;

    if(NULL == pt_device)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_INV_ARG;
    }

    /* Get target device info from sink device list */
    c_memset(&r_sink_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));

    bt_app_ui_bt_sink_dev_list_info_get(&r_sink_dev_list_info);

    u1_first_dev_index = r_sink_dev_list_info.u1_first_dev_index;
    u1_focus_row_index = r_sink_dev_list_info.u1_focus_row_index;
    u1_focus_dev_index = u1_first_dev_index + u1_focus_row_index;

    c_memcpy((VOID*)pt_device->bdAddr,
             (VOID*)(r_sink_dev_list_info.sink_dev_list[u1_focus_dev_index].ac_addr),
             MAX_BDADDR_LEN);

    c_memcpy((VOID*)pt_device->name,
             (VOID*)(r_sink_dev_list_info.sink_dev_list[u1_focus_dev_index].ac_name),
             MAX_NAME_LEN);

    pt_device->cod = r_sink_dev_list_info.sink_dev_list[u1_focus_dev_index].ui4_cod;

    return r_sink_dev_list_info.sink_dev_list[u1_focus_dev_index].e_status;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_bt_sink_dev_list_set_focus
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
INT32 bt_app_ui_bt_sink_dev_list_set_focus(UINT8 ui1_focus_idx, BOOL b_highlight_focus)
{
    //INT32  i4_ret  = BT_APPR_OK;
    //UINT8  ui1_idx = 0;
    //WGL_COLOR_INFO_T t_clr_info;

    BT_APP_LOG_API(("<BT_APP><Sink_list> Set sink device list focus row:%d, highlight:%d\n",ui1_focus_idx, b_highlight_focus));

    _gt_bt_sink_dev_list_info.u1_focus_row_index = ui1_focus_idx;

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------------------------------
  * Name          - bt_app_sink_device_list_scan_start_proc
  *
  * Description  -
  *
  * Inputs        -
  *--------------------------------------------------------------------------------------------------*/
INT32 bt_app_sink_device_list_scan_start_proc(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));

    if (FALSE == bt_app_is_sink_dev_scaning()
        && (BLUETOOTH_SINK_DEVICE_LIST_STATE == _e_bluetooth_state))
    {
        t_bt_msg.msg_type = BT_APP_MSG_NFY_SINK_SCAN_START;

        i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);

        if (i4_ret != PBR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: send BT_APP_MSG_NFY_SINK_SCAN_START fail\n"));
        }
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: Scaning is going or not in sink device list, do not scan\n"));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_device_list_info_init
  *
  * Description  - Init bluetooth sink device list info
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_sink_device_list_info_init(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    /* Clear sink device list info */
    c_memset(&_gt_bt_sink_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));

    _gt_bt_sink_dev_list_info.u1_focus_row_index = 0xFF;

    _gt_bt_sink_dev_list_init = TRUE;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_device_list_unpaired_info_clear
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_sink_device_list_unpaired_info_clear(VOID)
{
    _gt_bt_sink_dev_list_info.u1_unpaired_dev_num = 0;
    _gt_bt_sink_dev_list_info.u1_total_dev_num = _gt_bt_sink_dev_list_info.u1_paired_dev_num;
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_device_list_paired_dev_scanning_status_clear
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_sink_device_list_paired_dev_scanning_status_clear(VOID)
{
    _gt_bt_sink_dev_list_info.u1_paired_dev_scanned_num = 0;
    c_memset(_gt_bt_sink_dev_list_info.au1_paired_dev_scan_status, 0, BT_APP_PAIRED_SINK_DEV_MAX * sizeof(UINT8));
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_device_list_paired_dev_scanning_status_update
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_sink_device_list_paired_dev_scanning_status_update(char* addr)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_A2DP_DEVICE_LIST    pt_sink_dev_list;
    //BT_A2DP_DEVICE_LIST      _r_paired_sink_dev_list;
    UINT8   u1_index = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> Enter Func:%s\n", __FUNCTION__));

    if ((NULL != addr) && (MAX_BDADDR_LEN - 1 == c_strlen(addr)))
    {
        /* Init data to 0 */
        //pt_sink_dev_list = &_r_paired_sink_dev_list;
        //c_memset(pt_sink_dev_list, 0, sizeof(BT_A2DP_DEVICE_LIST));

//        i4_ret = c_btm_get_paired_sink_dev_list(pt_sink_dev_list);
        i4_ret = a_mtkapi_a2dp_src_get_dev_list(&pt_sink_dev_list);
        BT_APP_LOG_ERR(("<BT_APP>1111111111 a_mtkapi_a2dp_src_get_dev_list , i4_ret = %d\n", i4_ret));
        
        BT_APP_LOG_ERR(("<BT_APP>1111111111 a_mtkapi_a2dp_src_get_dev_list , dev_num = %d\n", pt_sink_dev_list.dev_num));
        if(i4_ret != 0)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: get paired sink device list fail, %d\n", i4_ret));
            return;
        }

        // search target in paired sink device list, and update scanning status of it
        for (u1_index = 0; (u1_index < pt_sink_dev_list.dev_num && u1_index < MAX_DEV_NUM); u1_index++)
        {
            if (c_strncmp(pt_sink_dev_list.dev[u1_index].addr, addr, (MAX_BDADDR_LEN - 1)) == 0)
            {
                // MAC address match, find the target, mark as scanned status
                _gt_bt_sink_dev_list_info.au1_paired_dev_scan_status[u1_index] = 0x01;

                _gt_bt_sink_dev_list_info.u1_paired_dev_scanned_num ++;

                BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> Func:%s : find the target:%s, index[%d] in the paired list, paired dev scanned num[%d]\n",    \
                    __FUNCTION__, addr, u1_index, _gt_bt_sink_dev_list_info.u1_paired_dev_scanned_num));

                break;
            }
        }
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list> Func:%s : ERR: invalid argument\n", __FUNCTION__));
    }

    return;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_device_list_paired_dev_scanning_status_check
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
BOOL bt_app_ui_sink_device_list_paired_dev_scanning_status_check(char* addr)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_A2DP_DEVICE_LIST    pt_sink_dev_list;
    //BT_A2DP_DEVICE_LIST      _r_paired_sink_dev_list;
    UINT8   u1_index = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> Enter Func:%s\n", __FUNCTION__));

    if ((NULL != addr) && (MAX_BDADDR_LEN - 1 == c_strlen(addr)))
    {
        //pt_sink_dev_list = &_r_paired_sink_dev_list;
        //c_memset(pt_sink_dev_list, 0, sizeof(BT_TARGET_DEV_LIST));

        //i4_ret = c_btm_get_paired_sink_dev_list(pt_sink_dev_list);
        
        i4_ret = a_mtkapi_a2dp_src_get_dev_list(&pt_sink_dev_list);
        BT_APP_LOG_ERR(("<BT_APP>222222222 a_mtkapi_a2dp_src_get_dev_list , i4_ret = %d\n", i4_ret));
        
        BT_APP_LOG_ERR(("<BT_APP>222222222 a_mtkapi_a2dp_src_get_dev_list , dev_num = %d\n", pt_sink_dev_list.dev_num));

        if(i4_ret != 0)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: get paired sink device list fail, %d\n", i4_ret));
            return FALSE;
        }

        for (u1_index = 0; ((u1_index < pt_sink_dev_list.dev_num) && (u1_index < MAX_DEV_NUM)); u1_index++)
        {
            if (c_strncmp(pt_sink_dev_list.dev[u1_index].addr, addr, (MAX_BDADDR_LEN - 1)) == 0)
            {
                _gt_bt_sink_dev_list_info.au1_paired_dev_scan_status[u1_index] = 0x01;
                _gt_bt_sink_dev_list_info.u1_paired_dev_scanned_num ++;
                BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> Func:%s : find the target:%s, index[%d] in the paired list, paired dev scanned num[%d]\n",    \
                    __FUNCTION__, addr, u1_index, _gt_bt_sink_dev_list_info.u1_paired_dev_scanned_num));

                return TRUE;
            }
        }
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list> Func:%s : ERR: invalid argument\n", __FUNCTION__));
    }

    return FALSE;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_paired_sink_dev_list_data_update
  *
  * Description  -
  *
  * Inputs         -
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_paired_sink_dev_list_data_update(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_A2DP_DEVICE_LIST    pt_sink_dev_list;
    //BT_A2DP_DEVICE_LIST      _r_paired_sink_dev_list;
    BT_HID_TARGET_DEV_LIST pt_hid_device_list;
    BT_HID_STATUS_STRUCT_LIST pt_hid_device_status;
    UINT8  u1_hid_paired_dev_num = 0;
    UINT8   u1_index = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> Update paired hid sink device data\n"));
    a_bt_app_ui_sink_dev_list_info_print();
    /* Init data to 0 */
    //pt_sink_dev_list = &_r_paired_sink_dev_list;
    //c_memset(pt_sink_dev_list, 0, sizeof(BT_TARGET_DEV_LIST));
    // init data as 0
    c_memset(_gt_bt_sink_dev_list_info.sink_dev_list, 0, (_gt_bt_sink_dev_list_info.u1_paired_dev_num * sizeof(BT_APP_DEVICE_INFO_T)));
    c_memset(&pt_hid_device_list, 0, sizeof(BT_HID_TARGET_DEV_LIST));
    c_memset(&pt_hid_device_status, 0, sizeof(BT_HID_STATUS_STRUCT_LIST));
    //i4_ret = c_btm_get_paired_hid_dev_list(&pt_hid_device_list, &pt_hid_device_status);


    if(i4_ret >= 0)
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list>  get paired hid device list , %d\n", i4_ret));
        DBG_LOG_PRINT(("<BT_APP><Sink_list> %s(),%d,dev_num:%d \n",__FUNCTION__,__LINE__,pt_hid_device_list.dev_num));
        /* Registered device should not be more than 7, refer to spec */
        if (pt_hid_device_list.dev_num > BT_APP_PAIRED_SINK_DEV_MAX)
        {
            _gt_bt_sink_dev_list_info.u1_paired_dev_num = BT_APP_PAIRED_SINK_DEV_MAX;
            _gt_bt_sink_dev_list_info.u1_total_dev_num = _gt_bt_sink_dev_list_info.u1_paired_dev_num + _gt_bt_sink_dev_list_info.u1_unpaired_dev_num;
        }
        else
        {
            _gt_bt_sink_dev_list_info.u1_paired_dev_num = (UINT8)pt_hid_device_list.dev_num;
            _gt_bt_sink_dev_list_info.u1_total_dev_num = _gt_bt_sink_dev_list_info.u1_paired_dev_num + _gt_bt_sink_dev_list_info.u1_unpaired_dev_num;
        }

        DBG_LOG_PRINT(("<BT_APP><Sink_list> %s(),%d MAX_DEV_NUM:%d,u1_paired_dev_num:%d,u1_total_dev_num:%d \n",__FUNCTION__,__LINE__,MAX_DEV_NUM,_gt_bt_sink_dev_list_info.u1_paired_dev_num,_gt_bt_sink_dev_list_info.u1_total_dev_num));
        // copy MW paired sink device name and addr to list
        for (u1_index = 0; (u1_index < MAX_DEV_NUM)&&(u1_index < _gt_bt_sink_dev_list_info.u1_paired_dev_num); u1_index++)
        {
            c_memcpy(_gt_bt_sink_dev_list_info.sink_dev_list[u1_index].ac_name, pt_hid_device_list.device_list[u1_index].name, (BT_APP_NAME_LEN_MAX)-1);
            c_memcpy(_gt_bt_sink_dev_list_info.sink_dev_list[u1_index].ac_addr, pt_hid_device_list.device_list[u1_index].bdAddr, (BT_APP_BTADDR_LEN_MAX)-1);
            _gt_bt_sink_dev_list_info.sink_dev_list[u1_index].ui4_cod = pt_hid_device_list.device_list[u1_index].cod|0x0500;

            DBG_LOG_PRINT(("<BT_APP><Sink_list> %s(),%d,status:%d \n",__FUNCTION__,__LINE__,pt_hid_device_status.device_list[u1_index].status));
      			if(pt_hid_device_status.device_list[u1_index].status == BT_CONNECTED_STATUS)
      			{
              DBG_LOG_PRINT(("<BT_APP><Sink_list> e_status:BT_APP_REMOTE_DEVICE_STATUS_CONNECTED.%s(),%d,u1_index:%d \n",__FUNCTION__,__LINE__,u1_index));
      				_gt_bt_sink_dev_list_info.sink_dev_list[u1_index].e_status = BT_APP_REMOTE_DEVICE_STATUS_CONNECTED;
      			}
      			else if(pt_hid_device_status.device_list[u1_index].status == BT_PAIRED_STATUS)
      			{
              DBG_LOG_PRINT(("<BT_APP><Sink_list> e_status:BT_APP_REMOTE_DEVICE_STATUS_PAIRED.%s(),%d,u1_index:%d \n",__FUNCTION__,__LINE__,u1_index));
      				_gt_bt_sink_dev_list_info.sink_dev_list[u1_index].e_status = BT_APP_REMOTE_DEVICE_STATUS_PAIRED;
      			}
      			else
      			{
              DBG_LOG_PRINT(("<BT_APP><Sink_list> e_status:BT_APP_REMOTE_DEVICE_STATUS_UNPAIRED.%s(),%d,u1_index:%d \n",__FUNCTION__,__LINE__,u1_index));
      				_gt_bt_sink_dev_list_info.sink_dev_list[u1_index].e_status = BT_APP_REMOTE_DEVICE_STATUS_UNPAIRED;
      			}
        }

    }

  	//c_memset(pt_sink_dev_list, 0, sizeof(BT_TARGET_DEV_LIST));
  	//i4_ret = c_btm_get_paired_sink_dev_list(pt_sink_dev_list);
    i4_ret = a_mtkapi_a2dp_src_get_dev_list(&pt_sink_dev_list);
    BT_APP_LOG_ERR(("<BT_APP>3333333 a_mtkapi_a2dp_src_get_dev_list , i4_ret = %d\n", i4_ret));
    BT_APP_LOG_ERR(("<BT_APP>3333333 a_mtkapi_a2dp_src_get_dev_list , dev_num = %d\n", pt_sink_dev_list.dev_num));

    if(i4_ret >= 0)
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list>  get paired sink device list , %d\n", i4_ret));

    	u1_hid_paired_dev_num=_gt_bt_sink_dev_list_info.u1_paired_dev_num;
        /* Registered device should not be more than 7, refer to spec */
        if (pt_sink_dev_list.dev_num > BT_APP_PAIRED_SINK_DEV_MAX - _gt_bt_sink_dev_list_info.u1_total_dev_num)
        {
            _gt_bt_sink_dev_list_info.u1_paired_dev_num = BT_APP_PAIRED_SINK_DEV_MAX;
            _gt_bt_sink_dev_list_info.u1_total_dev_num = _gt_bt_sink_dev_list_info.u1_paired_dev_num + _gt_bt_sink_dev_list_info.u1_unpaired_dev_num;
        }
        else
        {
            _gt_bt_sink_dev_list_info.u1_paired_dev_num += (UINT8)pt_sink_dev_list.dev_num;
            _gt_bt_sink_dev_list_info.u1_total_dev_num = _gt_bt_sink_dev_list_info.u1_paired_dev_num + _gt_bt_sink_dev_list_info.u1_unpaired_dev_num;
        }

        // init data as 0
        //c_memset(_gt_bt_sink_dev_list_info.sink_dev_list, 0, (_gt_bt_sink_dev_list_info.u1_paired_dev_num * sizeof(BT_APP_DEVICE_INFO_T)));

        // copy MW paired sink device name and addr to list
        DBG_LOG_PRINT(("<yangqing_BT> %s(),%d,dev_num:%d,u1_paired_dev_num:%d,u1_total_dev_num:%d \n",__FUNCTION__,__LINE__,
                        pt_sink_dev_list.dev_num,_gt_bt_sink_dev_list_info.u1_paired_dev_num,_gt_bt_sink_dev_list_info.u1_total_dev_num));
        for (u1_index = 0; (u1_index < MAX_DEV_NUM)&&(u1_index < pt_sink_dev_list.dev_num); u1_index++)
        {
            c_memcpy(_gt_bt_sink_dev_list_info.sink_dev_list[u1_hid_paired_dev_num+u1_index].ac_name, pt_sink_dev_list.dev[u1_index].name, (BT_APP_NAME_LEN_MAX)-1);
            c_memcpy(_gt_bt_sink_dev_list_info.sink_dev_list[u1_hid_paired_dev_num+u1_index].ac_addr, pt_sink_dev_list.dev[u1_index].addr, (BT_APP_BTADDR_LEN_MAX)-1);
            //_gt_bt_sink_dev_list_info.sink_dev_list[u1_hid_paired_dev_num+u1_index].ui4_cod = pt_sink_dev_list->device_list[u1_index].cod&0xfaff;
        }
    		if (bt_app_output_a2dp_connected())
    		{
    			_gt_bt_sink_dev_list_info.sink_dev_list[u1_hid_paired_dev_num].e_status = BT_APP_REMOTE_DEVICE_STATUS_CONNECTED;
    		}
    		else
    		{
    			_gt_bt_sink_dev_list_info.sink_dev_list[u1_hid_paired_dev_num].e_status = BT_APP_REMOTE_DEVICE_STATUS_PAIRED;
    		}
    }
    a_bt_app_ui_sink_dev_list_info_print();
    BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> %d paired sink device data updated to the list.\n", _gt_bt_sink_dev_list_info.u1_paired_dev_num));
    
    return;
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_unpaired_sink_dev_list_data_update
  *
  * Description  -
  *
  * Inputs         -
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_unpaired_sink_dev_list_data_update(VOID)
{
    UINT32 u4_unpaired_dev_num = 0;
    UINT8  u1_paired_dev_num = 0;
    UINT32 u4_act_num = 0;
    UINT8   u1_index = 0;
    BOOL    b_dev_paired = FALSE;
    UINT8   u1_unpaired_dev_num_1 = 0;


    BT_APP_DEVICE_INFO_T*  pt_sink_dev_list =  NULL;
    BT_APP_REMOTE_DEV_T* pt_devs = NULL;
    static BT_APP_REMOTE_DEV_T  at_unpaired_sink_dev_list[BT_APP_TOTAL_SINK_DEV_MAX];

    BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> Update unpaired sink device data\n"));
    a_bt_app_ui_sink_dev_list_info_print();
    pt_sink_dev_list = _gt_bt_sink_dev_list_info.sink_dev_list;

    /* Init data to 0 */
    pt_devs = at_unpaired_sink_dev_list;
    c_memset(pt_devs, 0, (BT_APP_TOTAL_SINK_DEV_MAX * sizeof(BT_APP_REMOTE_DEV_T)));

    /* Get paired sink device number */
    u1_paired_dev_num = _gt_bt_sink_dev_list_info.u1_paired_dev_num;

    /* Get current unpaired sink device number in the link list */
    u4_unpaired_dev_num = bt_app_get_a2dp_snk_dev_num();

    if(u4_unpaired_dev_num <= 0)
    {
        _gt_bt_sink_dev_list_info.u1_unpaired_dev_num = 0;
        _gt_bt_sink_dev_list_info.u1_total_dev_num = u1_paired_dev_num;
    }
    else
    {
        if (u1_paired_dev_num + u4_unpaired_dev_num > BT_APP_TOTAL_SINK_DEV_MAX)
        {
            u4_unpaired_dev_num = BT_APP_TOTAL_SINK_DEV_MAX - u1_paired_dev_num;
        }
        DBG_LOG_PRINT(("<BT_APP><Sink_list> %s(),%d,u1_paired_dev_num:%d,u4_unpaired_dev_num:%d,\n",__FUNCTION__,__LINE__,u1_paired_dev_num,u4_unpaired_dev_num));
        /* Sync "u4_unpaired_dev_num" unpaired sink devices data from scaning detected device list */
        u4_act_num = bt_app_get_all_a2dp_snk_devs(pt_devs, u4_unpaired_dev_num);

        /* Clear old unpaired sink device info */
        //c_memset(&(pt_sink_dev_list[u1_paired_dev_num]), 0, (BT_APP_TOTAL_SINK_DEV_MAX - u1_paired_dev_num) * sizeof(BT_APP_DEVICE_INFO_T));
        u1_unpaired_dev_num_1 = 0;
        DBG_LOG_PRINT(("<BT_APP><Sink_list> %s(),%d,u4_act_num:%d \n",__FUNCTION__,__LINE__,u4_act_num));
        /* Copy new unpaired sink device info to the list */
        for (u1_index = 0; u1_index < u4_act_num; u1_index++)
        {
            b_dev_paired = FALSE;
            for (int i=0; i<u1_paired_dev_num; i++)
            {
                if (0 == c_strncmp(pt_devs[u1_index].r_bt_device_info.ac_addr, pt_sink_dev_list[i].ac_addr, BT_APP_BTADDR_LEN_MAX))
                {
                    DBG_LOG_PRINT(("<BT_APP><Sink_list> Device already paired: %s.\n",
                        pt_devs[u1_index].r_bt_device_info.ac_addr));
                    b_dev_paired = TRUE;
                    break;
                }
            }
            if (b_dev_paired == FALSE)
            {
                c_memcpy(&(pt_sink_dev_list[u1_paired_dev_num + u1_unpaired_dev_num_1]), &(pt_devs[u1_index].r_bt_device_info), sizeof(BT_APP_DEVICE_INFO_T));
                u1_unpaired_dev_num_1++;
            }
        }

        _gt_bt_sink_dev_list_info.u1_unpaired_dev_num = u1_unpaired_dev_num_1;
        _gt_bt_sink_dev_list_info.u1_total_dev_num = u1_paired_dev_num + u1_unpaired_dev_num_1;
    }
    a_bt_app_ui_sink_dev_list_info_print();
    BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> %d unpaired sink device data updated to the list.\n", _gt_bt_sink_dev_list_info.u1_unpaired_dev_num));

    return;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_dev_list_data_update
  *
  * Description  -
  *
  * Inputs         -
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_sink_dev_list_data_update(BOOL b_update_data)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    if (b_update_data)
    {
        bt_app_ui_paired_sink_dev_list_data_update();

        bt_app_ui_unpaired_sink_dev_list_data_update();
    }
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_sink_dev_list_info_print
  *
  * Description  -
  *
  * Inputs         -
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_sink_dev_list_info_print(VOID)
{
    UINT8   u1_index = 0;
    BT_APP_DEVICE_INFO_T*  pt_sink_dev_list =  NULL;

    pt_sink_dev_list = _gt_bt_sink_dev_list_info.sink_dev_list;

    BT_APP_LOG_INFO(("<BT_APP><Sink_list> ------------- Sink device list inforamtion -------------\n"));
    BT_APP_LOG_INFO(("<BT_APP><Sink_list> Total device num    : %d\n",_gt_bt_sink_dev_list_info.u1_total_dev_num));
    BT_APP_LOG_INFO(("<BT_APP><Sink_list> Paired device num   : %d\n",_gt_bt_sink_dev_list_info.u1_paired_dev_num));
    BT_APP_LOG_INFO(("<BT_APP><Sink_list> Unpaired device num : %d\n",_gt_bt_sink_dev_list_info.u1_unpaired_dev_num));
    BT_APP_LOG_INFO(("<BT_APP><Sink_list> First device index  : %d\n",_gt_bt_sink_dev_list_info.u1_first_dev_index));
    BT_APP_LOG_INFO(("<BT_APP><Sink_list> Focus row index     : %d\n",_gt_bt_sink_dev_list_info.u1_focus_row_index));
    BT_APP_LOG_INFO(("<BT_APP><Sink_list> Scrollbar shown     : %d\n",_gt_bt_sink_dev_list_info.b_scrollbar_shown));

    for (u1_index = 0; u1_index < _gt_bt_sink_dev_list_info.u1_total_dev_num; u1_index++)
    {
        if (u1_index < _gt_bt_sink_dev_list_info.u1_paired_dev_num)
        {
            BT_APP_LOG_INFO(("<BT_APP><Sink_list> Device %2d: [Paired]   Name:%s, MAC:%s ,status:%d\n",u1_index, pt_sink_dev_list[u1_index].ac_name, pt_sink_dev_list[u1_index].ac_addr,pt_sink_dev_list[u1_index].e_status));
        }
        else
        {
            BT_APP_LOG_INFO(("<BT_APP><Sink_list> Device %2d: [Unpaired] Name:%s, MAC:%s ,status:%d\n",u1_index, pt_sink_dev_list[u1_index].ac_name, pt_sink_dev_list[u1_index].ac_addr,pt_sink_dev_list[u1_index].e_status));
        }
    }

    BT_APP_LOG_INFO(("<BT_APP><Sink_list> --------------------------------------------------------\n"));
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_bt_sink_dev_list_info_get
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_bt_sink_dev_list_info_get(BT_APP_SINK_DEV_LIST_INFO_T* pr_sink_list_info)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));
    c_memcpy(pr_sink_list_info, &_gt_bt_sink_dev_list_info, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));
    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_ui_bt_sink_dev_list_info_set
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
VOID bt_app_ui_bt_sink_dev_list_info_set(BT_APP_SINK_DEV_LIST_INFO_T* pr_sink_list_info)
{
    _gt_bt_sink_dev_list_info = *pr_sink_list_info;
}

BOOL bt_app_ui_bt_sink_dev_list_init(void)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));
    return _gt_bt_sink_dev_list_init;
}

VOID a_bt_app_ui_sink_dev_list_data_update(BOOL b_update_data)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    if(!bt_app_ui_bt_sink_dev_list_init())
    {
        bt_app_ui_sink_device_list_info_init();
    }

    bt_app_ui_sink_dev_list_data_update(b_update_data);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));
}

BOOL a_bt_app_ui_bt_sink_dev_list_info_get(BT_APP_SINK_DEV_LIST_INFO_T* pr_sink_list_info)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    if(bt_app_ui_bt_sink_dev_list_init())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, bt_app_ui_bt_sink_dev_list_info_get\n", __FUNCTION__));
        bt_app_ui_bt_sink_dev_list_info_get(pr_sink_list_info);
        return TRUE;
    }

    return FALSE;
}

INT32 a_bt_app_ui_sink_device_list_get_focused_device(BT_TARGET_DEV_INFO *pt_device)
{
    return bt_app_ui_sink_device_list_get_focused_device(pt_device);
}

INT32 a_bt_app_ui_bt_sink_dev_list_set_focus(UINT8 ui1_focus_idx)
{
    //INT32  i4_ret  = BT_APPR_OK;
    //UINT8  ui1_idx = 0;
    //WGL_COLOR_INFO_T t_clr_info;

    BT_APP_LOG_API(("<BT_APP><Sink_list> Set sink device list focus row:%d\n",ui1_focus_idx));

    _gt_bt_sink_dev_list_info.u1_focus_row_index = ui1_focus_idx;

    return BT_APPR_OK;
}

VOID a_bt_app_ui_sink_dev_list_info_print(VOID)
{
	BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

	bt_app_ui_sink_dev_list_info_print();
	return;
}
#endif



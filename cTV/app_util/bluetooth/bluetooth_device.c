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
 * $RCSfile: bluetooth_device.c,v $
 * $Revision: #4 $
 * $Date: 2015/11/14 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file manages local bluetooth device info and paired devices.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

/*-----------------------------------------------------------------------------
                        include files
-----------------------------------------------------------------------------*/
//#include "x_ipcd.h"
//#include "ifcon_mw_rm.h"

#include <unistd.h>
#include <stdlib.h>

//#include "c_bt_mw_manager.h"
#include "u_bt_mw_gap.h"
#include "mtk_bt_service_gap_wrapper.h"

#include "bluetooth.h"
#include "bluetooth_hid.h"
#include "bluetooth_device.h"
#include "bluetooth_timer.h"
#include "bluetooth_global_variables.h"
//#include "c_bt_mw_a2dp_src.h"
//#include "c_bt_mw_hidh.h"
//#include "c_bt_mw_gap.h"
#include "bluetooth_device_list.h"
#include "mtk_bt_service_a2dp_wrapper.h"


// RSSI: Received Signal Strength Indication
// RSSI of remote device is mapped to 5 levels.
// This table is used to map RSSI value to RSSI level
// RSSI value = _gai4_rssi_map_table[4] or larger, level 5
// RSSI value = _gai4_rssi_map_table[3] - _gai4_rssi_map_table[4] - 1, level 4
// RSSI value = _gai4_rssi_map_table[2] - _gai4_rssi_map_table[3] - 1, level 3
// RSSI value = _gai4_rssi_map_table[1] - _gai4_rssi_map_table[2] - 1, level 2
// RSSI value = _gai4_rssi_map_table[0] - _gai4_rssi_map_table[1] - 1, level 1
// RSSI value = 0 - _gai4_rssi_map_table[0], level 0
static INT32 _gai4_rssi_map_table[BT_APP_RSSI_LEVEL_NUM] = {170, 175, 180, 185, 200};

// A2DP Sink device list, the devices in this list have A2DP Sink capability.
static BT_APP_REMOTE_DEVICE_LIST* _gpt_a2dp_snk_dev_list = NULL;

static BOOL ui2_g_bt_app_pts_enable = FALSE;

/**---------------------------------------------------------------------------
  * Name          - bluetooth_local_device_name_set
  *
  * Description  - Set Bluetooth local device(BDV itself) name
  *
  * Inputs        - name: BDV's Bluetooth device name
  *
  * Returns       - 0 : success, -1 : error
  *---------------------------------------------------------------------------*/
UINT32 bluetooth_local_device_name_set(const char* name)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> %s is called\n", __FUNCTION__));

    if(NULL == name)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

    a_bt_app_set_local_device_name((CHAR*)name);

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_send_local_name_req
  *
  * Description  - send request to set local bluetooth device name.
  *
  * Inputs        - b_on power is set to on or off
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_send_local_name_req(CHAR* pc_name)
{
    INT32  i4_ret = PBR_OK;
    UINT32 ui4_name_len = 0;
    CHAR   *pc_local_name = NULL;
    BT_APP_MSG_T t_bt_msg = {0};

    if(NULL == pc_name)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

    if(!a_bt_app_has_init())
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: BT APP has not init\n"));
        return PBR_FAIL;
    }

    ui4_name_len = c_strlen(pc_name);

    BT_APP_LOG_DEFAULT(("<BT_APP> BT local name: %s, %d\n", pc_name, ui4_name_len));

    pc_local_name = (CHAR *)c_mem_alloc(ui4_name_len + 1);
    if(NULL == pc_local_name)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for local name fail\n"));
        return PBR_FAIL;
    }
    c_memset(pc_local_name, 0, ui4_name_len + 1);

    c_strncpy(pc_local_name, pc_name, ui4_name_len);

    // send request to bluetooth thread
    t_bt_msg.msg_type = BT_APP_MSG_REQ_SET_LOCAL_NAME;
    t_bt_msg.ui4_data_size = ui4_name_len + 1;
    t_bt_msg.pv_data = pc_local_name;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send local name req fail\n"));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_set_local_device_name
  *
  * Description  - Set local bluetooth device name to MW and driver,  and send it to IFCon.
  *                     remote device will show this name when scan it
  *
  * Inputs         - pc_name: local device name
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_set_local_device_name(CHAR* pc_name)
{
    INT32 i4_ret = 0;
    UINT8 ui1_name_len = 0;
    CHAR  ac_data[32] = {0};

    if(NULL == pc_name)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> set local name: %s\n", pc_name));

    // set local bluetooth device name to MW and driver.
    i4_ret = a_mtkapi_bt_gap_set_name(pc_name);
    if (0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: set local name fail, %d\n", i4_ret));
        return PBR_FAIL;
    }

    ui1_name_len = (UINT8)c_strlen(pc_name);

    // send max 30 characters to ifcon, more data is dropped.
    if(ui1_name_len > 30)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> name len is more that 30, %d\n", ui1_name_len));

        ui1_name_len = 30;
    }

    // send bluetooth local device name to IFCon
    c_memcpy(&ac_data, pc_name, ui1_name_len);
    //d_ifcon_set_bluetooth_self_device_name(ac_data);

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_get_paired_device_list
  *
  * Description  - get the list of paired devices
  *
  * Returns       - the list of paired devices
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_get_paired_device_list(BT_TARGET_DEV_LIST *pt_device_list)
{
    INT32 i4_ret = PBR_OK;

    if(NULL == pt_device_list)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

//    i4_ret = c_btm_get_paired_src_dev_list(pt_device_list);
    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get paired dev list fail, %d\n", i4_ret));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_get_paired_src_device_num
  *
  * Description  - get the number of paired src devices
  *
  * Returns       - the number of paired src devices
  *---------------------------------------------------------------------------*/
UINT32 a_bt_app_get_paired_src_device_num(VOID)
{
    INT32 i4_ret = 0;
    BT_A2DP_DEVICE_LIST r_paired_src_dev_list = {0};
    
//    i4_ret = c_btm_get_paired_src_dev_list(&r_paired_src_dev_list);
    i4_ret = a_mtkapi_a2dp_src_get_dev_list(&r_paired_src_dev_list);

    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get paired src device num fail\n"));
        return 0;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s : paired src device num[%d]\n", __FUNCTION__, r_paired_src_dev_list.dev_num));

    return r_paired_src_dev_list.dev_num;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_src_paired_device_remove
  *
  * Description  - remove one paired device
  *
  * Inputs         - pc_addr: specify MAC address of the paired device which will be removed.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_src_paired_device_remove(CHAR* pc_addr)
{
    INT32 i4_ret = PBR_OK;
    UINT8 ui1_idx = 0;
    BT_TARGET_DEV_LIST t_device_list = {0};

    if(NULL == pc_addr)
    {
        BT_APP_LOG_ERR(("<BT_APP> %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

    BT_APP_LOG_INFO(("<BT_APP> remove paired device: %s\n", pc_addr));

    // erase paired info from Blueangel
    i4_ret = a_mtkapi_bt_gap_unpair(pc_addr);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> erase paired info fail, %d\n", i4_ret));
    }

    // get paired device list from BTM
//    i4_ret = c_btm_get_paired_src_dev_list(&t_device_list);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> get paired device list fail\n"));
        return PBR_FAIL;
    }

    // find the target device and remove it from paired device list
    for(ui1_idx = 0; ui1_idx < t_device_list.dev_num; ui1_idx++)
    {
        if(c_strncmp(t_device_list.device_list[ui1_idx].bdAddr, pc_addr, MAX_BDADDR_LEN) ==0)
        {
            i4_ret = a_mtkapi_bt_gap_unpair(pc_addr);
            break;
        }
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_src_paired_device_remove_all
  *
  * Description  - remove all paired device
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_src_paired_device_remove_all(VOID)
{
    INT32 i4_ret = PBR_OK;
    UINT8  i = 0;
    BT_TARGET_DEV_LIST t_device_list = {0};

    // get paired device list from BTM
//    i4_ret = c_btm_get_paired_src_dev_list(&t_device_list);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> get paired device list fail\n"));
    }

    // erase paired info from Blueangel
    for(i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP> erase paired info: %s\n", t_device_list.device_list[i].bdAddr));
        a_mtkapi_bt_gap_unpair(t_device_list.device_list[i].bdAddr);
    }

    // remove all src paired devices from paired device list
    for (i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP> erase paired info from SRC paired device list: %s\n", t_device_list.device_list[i].bdAddr));
//        i4_ret = c_btm_del_paired_av_dev_one(&(t_device_list.device_list[i]));
    }

    return i4_ret;
}


/**---------------------------------------------------------------------------
  * Name          - a_bt_app_get_paired_sink_device_num
  *
  * Description  - get the number of paired sink devices
  *
  * Returns       - the number of paired sink devices
  *---------------------------------------------------------------------------*/
UINT32 a_bt_app_get_paired_sink_device_num(VOID)
{
    INT32 i4_ret = 0;
    BT_TARGET_DEV_LIST r_paired_sink_dev_list = {0};

//    i4_ret = c_btm_get_paired_sink_dev_list(&r_paired_sink_dev_list);

    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get paired sink device num fail\n"));
        return 0;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s : paired sink device num[%d]\n", __FUNCTION__, r_paired_sink_dev_list.dev_num));

    return r_paired_sink_dev_list.dev_num;
}


/**---------------------------------------------------------------------------
  * Name          - a_bt_app_sink_paired_device_remove
  *
  * Description  - remove one sink paired device
  *
  * Inputs         - pc_addr: specify MAC address of the sink paired device which will be removed.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_sink_paired_device_remove(CHAR* pc_addr)
{
    INT32 i4_ret = PBR_OK;
    UINT8 ui1_idx = 0;
    BT_TARGET_DEV_LIST t_device_list = {0};

    if(NULL == pc_addr)
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list> %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

    BT_APP_LOG_INFO(("<BT_APP><Sink_list> remove sink paired device: %s\n", pc_addr));

    // erase paired info from Blueangel
//    i4_ret = a_mtkapi_bt_gap_unpair(pc_addr);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list> erase sink paired info fail, %d\n", i4_ret));
    }
    bt_app_remove_one_from_dev_list(pc_addr);
    // get sink paired device list from BTM
//    i4_ret = c_btm_get_paired_sink_dev_list(&t_device_list);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list> get sink paired device list fail, %d\n", i4_ret));
        return PBR_FAIL;
    }

    // find the target device and remove it from paired device list
    for(ui1_idx = 0; ui1_idx < t_device_list.dev_num; ui1_idx++)
    {
        if(c_strncmp(t_device_list.device_list[ui1_idx].bdAddr, pc_addr, MAX_BDADDR_LEN) ==0)
        {
//            i4_ret = c_btm_del_paired_av_dev_one(&(t_device_list.device_list[ui1_idx]));
            break;
        }
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_sink_paired_device_remove_all
  *
  * Description  - remove all sink paired device
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_sink_paired_device_remove_all(VOID)
{
    INT32 i4_ret = PBR_OK;
    UINT8  i = 0;
    BT_TARGET_DEV_LIST t_device_list = {0};

    if (bt_app_output_a2dp_connected())
    {
        BT_APP_LOG_INFO(("<BT_APP> Power OFF: Start to disconnect output a2dp connection\n"));

        bt_app_disconnect_with_sink_dev();
    }

    // get sink paired device list from BTM
//    i4_ret = c_btm_get_paired_sink_dev_list(&t_device_list);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP><Sink_list> get sink paired device list fail\n"));
    }

    // erase all sink paired info from Blueangel
    for(i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP><Sink_list> erase sink paired info from blueangel : %s\n", t_device_list.device_list[i].bdAddr));
        a_mtkapi_bt_gap_unpair(t_device_list.device_list[i].bdAddr);
        bt_app_remove_one_from_dev_list(t_device_list.device_list[i].bdAddr);
    }

    // remove all sink paired devices from paired device list
    for (i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP><Sink_list> erase sink paired info from sink paired device list: %s\n", t_device_list.device_list[i].bdAddr));
//        i4_ret = c_btm_del_paired_av_dev_one(&(t_device_list.device_list[i]));
    }

    return i4_ret;
}


/**---------------------------------------------------------------------------
  * Name          - a_bt_app_get_target_device_name
  *
  * Description  - Get the name of the device which is connected with BDV
  *
  * Inputs        - ui4_len: Buffer size of pc_device_name
  *
  * Outputs      - pc_device_name: the name of the device which is connected with BDV
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_get_target_device_name(CHAR *pc_device_name, UINT32 ui4_len)
{
    INT32 i4_ret = PBR_OK;
    BT_TARGET_DEV_INFO t_bt_dev_info = {0,0,{0},{0}};

    if(NULL == pc_device_name)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

    // get current connected device info from BTM.
//    i4_ret = c_btm_get_target_info(&t_bt_dev_info);
    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get target dev info fail, %d\n", i4_ret));
        return PBR_FAIL;
    }

    c_strncpy(pc_device_name, t_bt_dev_info.name, ui4_len);

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_latest_paired_src_device
  *
  * Description  - get the latest paired source device
  *
  * Outputs       - pt_device: the latest paired source device
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_get_latest_paired_src_device(BT_TARGET_DEV_INFO *pt_device)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_TARGET_DEV_LIST t_device_list = {0};

    if(NULL == pt_device)
    {
        BT_APP_LOG_ERR(("<BT_APP> %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_INV_ARG;
    }

    // get paired device list from BTM
//    i4_ret = c_btm_get_paired_src_dev_list(&t_device_list);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> get paired device list fail\n"));
        return PBR_FAIL;
    }

    if(0 == t_device_list.dev_num)
    {
        BT_APP_LOG_ERR(("<BT_APP> no paired device\n"));
        return PBR_FAIL;
    }

    c_memcpy((VOID*)pt_device,
             &(t_device_list.device_list[0]),
             sizeof(BT_TARGET_DEV_INFO));

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_latest_paired_sink_device
  *
  * Description  - get the latest paired sink device
  *
  * Outputs       - pt_device: the latest paired sink device
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_get_latest_paired_sink_device(BT_TARGET_DEV_INFO *pt_device)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_TARGET_DEV_LIST t_device_list = {0};

    if(NULL == pt_device)
    {
        BT_APP_LOG_ERR(("<BT_APP> %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_INV_ARG;
    }

    // get paired sink device list from BTM
//    i4_ret = c_btm_get_paired_sink_dev_list(&t_device_list);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> get paired sink device list fail\n"));
        return PBR_FAIL;
    }

    if(0 == t_device_list.dev_num)
    {
        BT_APP_LOG_ERR(("<BT_APP> no paired sink device\n"));
        return PBR_FAIL;
    }

    c_memcpy((VOID*)pt_device,
             &(t_device_list.device_list[0]),
             sizeof(BT_TARGET_DEV_INFO));

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_rssi_map_table
  *
  * Description  - Set RSSI map table
  *
  * Inputs        - ai4_rssi_map_table[]: RSSI map table
  *                  - ui1_len: the lentgh of RSSI map table
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_set_rssi_map_table(INT32 ai4_rssi_map_table[], UINT8 ui1_len)
{
    UINT8 ui1_idx = 0;

    // Check whether argument is valid.
    if(ui1_len < BT_APP_RSSI_LEVEL_NUM)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: Invalid argument\n"));
        BT_APP_LOG_ERR(("<BT_APP> ERR: RSSI level is more than %d\n",
            BT_APP_RSSI_LEVEL_NUM-1));
        return PBR_FAIL;
    }

    for(ui1_idx = 0; ui1_idx < BT_APP_RSSI_LEVEL_NUM - 1; ui1_idx++)
    {
        if(ai4_rssi_map_table[ui1_idx] >= ai4_rssi_map_table[ui1_idx + 1])
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: Invalid argument\n"));
            BT_APP_LOG_ERR(("<BT_APP> ERR: Level[%d] must be smaller than Level[%d]\n",
                ui1_idx + 1, ui1_idx + 2));
            return PBR_FAIL;
        }
    }

    // update RSSI map table
    for(ui1_idx = 0; ui1_idx < BT_APP_RSSI_LEVEL_NUM; ui1_idx++)
    {
        _gai4_rssi_map_table[ui1_idx] = ai4_rssi_map_table[ui1_idx];
    }

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_rssi_map_table
  *
  * Description  - Get RSSI map table
  *
  * Outputs      - pi4_rssi_map_table
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_get_rssi_map_table(INT32 *pi4_rssi_map_table)
{
    UINT8 ui1_idx = 0;

    // Check whether argument is valid.
    if(NULL == pi4_rssi_map_table)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_FAIL;
    }

    // Get RSSI map table
    for(ui1_idx = 0; ui1_idx < BT_APP_RSSI_LEVEL_NUM; ui1_idx++)
    {
        pi4_rssi_map_table[ui1_idx] = _gai4_rssi_map_table[ui1_idx];
    }

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_map_rssi_level
  *
  * Description  - Map RSSI value to several Levels
  *
  * Inputs        - RSSI value
  *
  * Returns       - RSSI Level
  *---------------------------------------------------------------------------*/
static UINT8 _bt_app_map_rssi_level(INT16 i4_rssi_value)
{
    UINT8 ui1_rssi_level = 0;

    // Map RSSI value to 5 level
    for(ui1_rssi_level = BT_APP_RSSI_LEVEL_NUM; ui1_rssi_level > 0; ui1_rssi_level --)
    {
        if(i4_rssi_value >= _gai4_rssi_map_table[ui1_rssi_level-1])
        {
            break;
        }
    }

    return ui1_rssi_level;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_src_rssi_level
  *
  * Description  - Get RSSI(Received Signal Strengh Indication) level of the connected SRC device.
  *                      The RSSI value is mapped to 5 level, please to see BDP00386461.
  *
  * Outputs      - pui1_rssi_level: RSSI level of the corrent connected SRC device
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_get_src_rssi_level(UINT8 *pui1_rssi_level)
{
    INT32 i4_ret = PBR_OK;
    INT16   i4_rssi_value = 0;
    UINT8 ui1_rssi_level = 0;
    //CHAR  ac_mac_addr[25] = {0};

    if(NULL == pui1_rssi_level)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_INV_ARG;
    }

    // get the MAC of the SRC device which is connected with BDV
//    i4_ret = c_btm_get_target_addr(ac_mac_addr);
    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get target MAC fail\n"));
        return BT_APPR_FAIL;
    }

    // Get RSSI value from BTM
//    i4_ret = c_btm_get_rssi(ac_mac_addr, &i4_rssi_value);
    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get rssi fail\n"));
        return BT_APPR_FAIL;
    }

    i4_rssi_value+=256;

    ui1_rssi_level = _bt_app_map_rssi_level(i4_rssi_value);

    BT_APP_LOG_INFO(("<BT_APP> current RSSI value: %d, level: %d\n",
        i4_rssi_value, ui1_rssi_level));

    *pui1_rssi_level = ui1_rssi_level;

    return BT_APPR_OK;
}

VOID bt_app_set_pts_enable(BOOL flag)
{
    ui2_g_bt_app_pts_enable = flag;
}

BOOL bt_app_get_pts_status(VOID)
{
    return ui2_g_bt_app_pts_enable;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_a2dp_snk_inquiry_response_cbk_fct
  *
  * Description  - callback this function to notify remote device info when receiving inquiry
  *                      response and the device has A2DP Sink capability.
  *
  * Inputs         - pt_result: remote device info.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
VOID _bt_app_a2dp_snk_inquiry_response_cbk_fct(tBTMW_GAP_DEVICE_INFO* pt_result, void* pv_tag)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    BT_APP_REMOTE_DEV_T* pt_remote_dev = NULL;

    if(NULL == pt_result)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return ;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> device_kind =%d\n", pt_result->device_kind));

    if (pt_result->device_kind == BT_DEVICE_LOCAL)
    {

    }
    else if (pt_result->device_kind == BT_DEVICE_SCAN)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> receive A2DP Sink inquiry response\n"));
        pt_remote_dev = (BT_APP_REMOTE_DEV_T *)c_mem_alloc(sizeof(BT_APP_REMOTE_DEV_T));
        if(NULL == pt_remote_dev)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem to receive remote device info fail\n"));
            return ;
        }
        c_memset(pt_remote_dev, 0, sizeof(BT_APP_REMOTE_DEV_T));

        if(!bt_app_get_pts_status())
        {
            c_strncpy(pt_remote_dev->r_bt_device_info.ac_name, pt_result->device.name, BT_APP_NAME_LEN_MAX-1);
        }

        c_strncpy(pt_remote_dev->r_bt_device_info.ac_addr, pt_result->device.bdAddr, BT_APP_BTADDR_LEN_MAX-1);
        pt_remote_dev->r_bt_device_info.ui4_cod = pt_result->device.cod;
        pt_remote_dev->r_bt_device_info.ui4_service = pt_result->device.service;
        //pt_remote_dev->r_bt_device_info.e_status = pt_result->isPaired;
        pt_remote_dev->r_bt_device_info.e_rssi_level = _bt_app_map_rssi_level(pt_result->device.rssi);

        BT_APP_LOG_DEFAULT(("<BT_APP> Name: %s\n", pt_remote_dev->r_bt_device_info.ac_name));
        BT_APP_LOG_DEFAULT(("<BT_APP> Addr: %s\n", pt_remote_dev->r_bt_device_info.ac_addr));
        BT_APP_LOG_DEFAULT(("<BT_APP> CoD : 0x%x\n", pt_remote_dev->r_bt_device_info.ui4_cod));
        BT_APP_LOG_DEFAULT(("<BT_APP> Service : 0x%x\n", pt_remote_dev->r_bt_device_info.ui4_service));
        BT_APP_LOG_DEFAULT(("<BT_APP> Status : 0x%x\n", pt_remote_dev->r_bt_device_info.e_status));
        BT_APP_LOG_DEFAULT(("<BT_APP> RSSI Level:%d, Value:%d\n", pt_remote_dev->r_bt_device_info.e_rssi_level, pt_result->device.rssi));

        //MW can't notify pt_remote_dev->r_bt_device_info.e_status
        if(bt_app_ui_sink_device_list_paired_dev_scanning_status_check(pt_remote_dev->r_bt_device_info.ac_addr))
        {
            c_mem_free(pt_remote_dev);
            pt_remote_dev = NULL;
            return;
        }

        t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_A2DP_SNK_DEV;
        t_bt_msg.ui4_data_size = sizeof(BT_APP_REMOTE_DEV_T);
        t_bt_msg.pv_data = pt_remote_dev;
        i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
        if (i4_ret != PBR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send A2DP SNK dev fail\n"));
            c_mem_free(pt_remote_dev);
            pt_remote_dev = NULL;
        }
    }
    else if (pt_result->device_kind == BT_DEVICE_BONDED)
    {

    }

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_init_a2dp_snk_dev_list
  *
  * Description  - Init A2DP Sink device List
  *---------------------------------------------------------------------------*/
INT32 _bt_app_init_a2dp_snk_dev_list(VOID)
{
    if(NULL == _gpt_a2dp_snk_dev_list)
    {
        _gpt_a2dp_snk_dev_list = (BT_APP_REMOTE_DEVICE_LIST *)c_mem_alloc(
            sizeof(BT_APP_REMOTE_DEVICE_LIST));
        if(NULL == _gpt_a2dp_snk_dev_list)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for a2dp snk dev list fail\n"));
            return BT_APPR_FAIL;
        }
        c_memset(_gpt_a2dp_snk_dev_list, 0, sizeof(BT_APP_REMOTE_DEVICE_LIST));
    }

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_free_a2dp_snk_dev_list
  *
  * Description  - Free A2DP Sink device List
  *---------------------------------------------------------------------------*/
INT32 _bt_app_free_a2dp_snk_dev_list(VOID)
{
    BT_APP_REMOTE_DEV_T* pt_dev = NULL;
    BT_APP_REMOTE_DEV_T* pt_dev_tmp = NULL;

    // free header node
    if(_gpt_a2dp_snk_dev_list != NULL)
    {
        pt_dev = _gpt_a2dp_snk_dev_list->pt_first_dev;
        c_mem_free(_gpt_a2dp_snk_dev_list);
        _gpt_a2dp_snk_dev_list = NULL;
    }

    // free every device
    while(pt_dev != NULL)
    {
        pt_dev_tmp = pt_dev;
        pt_dev = pt_dev->pt_next;
        c_mem_free(pt_dev_tmp);
    }

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_free_a2dp_snk_dev_list
  *
  * Description  - Free A2DP Sink device List
  *---------------------------------------------------------------------------*/
INT32 bt_app_remove_one_from_dev_list(char* bt_addr)
{
    BT_APP_REMOTE_DEV_T* pt_dev = NULL;
    BT_APP_REMOTE_DEV_T* pt_dev_tmp = NULL;
    if(NULL == bt_addr)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }
    BT_APP_LOG_INFO(("<BT_APP>_bt_app_remove_one_from_dev_list free unpaird: %s\n", bt_addr));

    // free header node
    if(_gpt_a2dp_snk_dev_list != NULL)
    {
        pt_dev = _gpt_a2dp_snk_dev_list->pt_first_dev;
        if (pt_dev == NULL)
        {
            return BT_APPR_OK;
        }

        if (0 == c_strncmp(pt_dev->r_bt_device_info.ac_addr,bt_addr,(BT_APP_BTADDR_LEN_MAX-1)))
        {
            _gpt_a2dp_snk_dev_list->pt_first_dev = pt_dev->pt_next;
            _gpt_a2dp_snk_dev_list->ui4_num --;
            BT_APP_LOG_INFO(("<BT_APP> free frist unpaird: %s\n", pt_dev->r_bt_device_info.ac_addr));
            c_mem_free(pt_dev);
            return BT_APPR_OK;
        }
    }

    while(pt_dev != NULL)
    {
        if (pt_dev->pt_next == NULL)
        {
            return BT_APPR_OK;
        }
        pt_dev_tmp = pt_dev->pt_next;
        BT_APP_LOG_INFO(("<BT_APP> pt_dev->pt_next mac: %s\n", pt_dev->pt_next->r_bt_device_info.ac_addr));
        if (0 == c_strncmp(pt_dev_tmp->r_bt_device_info.ac_addr,bt_addr,(BT_APP_BTADDR_LEN_MAX-1)))
        {
            pt_dev->pt_next = pt_dev_tmp->pt_next;
            _gpt_a2dp_snk_dev_list->ui4_num --;
            BT_APP_LOG_INFO(("<BT_APP> 2 free unpaird: %s\n", pt_dev_tmp->r_bt_device_info.ac_addr));
            c_mem_free(pt_dev_tmp);
            return BT_APPR_OK;
        }
        else
        {
            pt_dev = pt_dev->pt_next;
        }
    }

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_remote_dev_cmp
  *
  * Description  - This API compares remote device1 and remote device2.
  *                         1. Connected device > Paired device > Unpaired device.
  *                         2. For two unpaired devices, compare them with RSSI.
  *
  * Inputs         - pt_dev1: remote device1.
  *                      pt_dev2: remote device2.
  *
  * Returns       - returns a value indicating the relationship between the two devices, as follows:
  *                         Less than 0: device1 less than device2
  *                                       0: device1 equivalent device2
  *                     Greater than 0: device1 greater than device2
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_remote_dev_cmp(BT_APP_REMOTE_DEV_T* pt_dev1,
                                            BT_APP_REMOTE_DEV_T* pt_dev2)
{
    INT32 i4_ret = 0;

    if((NULL == pt_dev1) || (NULL == pt_dev2))
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return 0;
    }

    // If status of these two devices are UNPAIRED, compare RSSI.
    if((BT_APP_REMOTE_DEVICE_STATUS_UNPAIRED == pt_dev1->r_bt_device_info.e_status)
        && (BT_APP_REMOTE_DEVICE_STATUS_UNPAIRED == pt_dev2->r_bt_device_info.e_status))
    {
        i4_ret = pt_dev1->r_bt_device_info.e_rssi_level - pt_dev2->r_bt_device_info.e_rssi_level;
    }
    else
    {
        i4_ret = pt_dev1->r_bt_device_info.e_status - pt_dev2->r_bt_device_info.e_status;
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_insert_a2dp_snk_dev
  *
  * Description  - Insert one device which has A2DP Sink capability into A2DP Sink device List.
  *                     The A2DP Sink device List always be sorted by the following sequence:
  *                         1. Connected device.
  *                         2. Paired device.
  *                         3. Unpaired device (sorted by RSSI)
  *
  * Inputs         - pt_a2dp_snk_dev: A2DP Sink device info, This API will alloc another new memory to store it.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
VOID bt_app_insert_a2dp_snk_dev(BT_APP_REMOTE_DEV_T* pt_a2dp_snk_dev)
{
    BT_APP_REMOTE_DEV_T* pt_dev = NULL;
    BT_APP_REMOTE_DEV_T* pt_dev_tmp1 = NULL;  // Used to find insert position
    BT_APP_REMOTE_DEV_T* pt_dev_tmp2 = NULL;

    if(NULL == pt_a2dp_snk_dev)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return ;
    }

    if(NULL == _gpt_a2dp_snk_dev_list)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: no init A2DP Sink dev list\n"));
        return;
    }

    // Create node
    pt_dev = (BT_APP_REMOTE_DEV_T *)c_mem_alloc(sizeof(BT_APP_REMOTE_DEV_T));
    if(NULL == pt_dev)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for a2dp snk dev fail\n"));
        return ;
    }
    c_memcpy(pt_dev, pt_a2dp_snk_dev, sizeof(BT_APP_REMOTE_DEV_T));
    pt_dev->pt_next = NULL;

    _gpt_a2dp_snk_dev_list->ui4_num ++;

    // Find insert position, pt_dev_tmp2 >= pt_dev > pt_dev_tmp1
    pt_dev_tmp1 = _gpt_a2dp_snk_dev_list->pt_first_dev;
    pt_dev_tmp2 = NULL;
    while((pt_dev_tmp1 != NULL) && (_bt_app_remote_dev_cmp(pt_dev, pt_dev_tmp1) <= 0))
    {
        pt_dev_tmp2 = pt_dev_tmp1;
        pt_dev_tmp1 = pt_dev_tmp1->pt_next;
    }

    // Insert
    pt_dev->pt_next = pt_dev_tmp1;
    if(NULL == pt_dev_tmp2)
    {
        _gpt_a2dp_snk_dev_list->pt_first_dev = pt_dev;
    }
    else
    {
        pt_dev_tmp2->pt_next = pt_dev;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Insert A2DP sink device to list, name:%s\n", pt_dev->r_bt_device_info.ac_name));

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_a2dp_snk_dev_num
  *
  * Description  - Get A2DP Sink device number.
  *
  * Returns       - returns a value indicating how many A2DP Sink devices has been found.
  *                        0: have not started inquiry scan or have not found device.
  *
  *---------------------------------------------------------------------------*/
UINT32 bt_app_get_a2dp_snk_dev_num(VOID)
{
    UINT32 ui4_num = 0;

    if(_gpt_a2dp_snk_dev_list != NULL)
    {
        ui4_num = _gpt_a2dp_snk_dev_list->ui4_num;
    }

    return ui4_num;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_all_a2dp_snk_devs
  *
  * Description  - Get all discoverable devices which have A2DP Sink capability.
  *
  * Inputs        - ui4_num: the size of pt_devs, specify how many devices can be stored in pt_devs.
  *
  * Outputs      - pt_devs: contiguous buffer to store all discoverable devices which have A2DP Sink capability.
  *
  * Returns       - returns a value indicating how many devices are stored into pt_devs.
  *
  *---------------------------------------------------------------------------*/
UINT32 bt_app_get_all_a2dp_snk_devs(BT_APP_REMOTE_DEV_T *pt_devs, UINT32 ui4_num)
{
    UINT32 ui4_index = 0;
    BT_APP_REMOTE_DEV_T* pt_dev = NULL;

    if(_gpt_a2dp_snk_dev_list != NULL)
    {
        pt_dev = _gpt_a2dp_snk_dev_list->pt_first_dev;
        while((pt_dev != NULL) && (ui4_index < ui4_num))
        {
            c_memcpy(&(pt_devs[ui4_index]), pt_dev, sizeof(BT_APP_REMOTE_DEV_T));
            ui4_index ++;
            pt_dev = pt_dev->pt_next;
        }
    }

    return ui4_index;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_start_a2dp_snk_inquiry_scan
  *
  * Description  - start inquiry scan to find the devices which have A2DP Sink capability.
  *
  * Input         - time_out: ms
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_start_a2dp_snk_inquiry_scan(UINT32 time_out)
{
    INT32         i4_ret       = BT_APPR_OK;
    VOID*         pv_nfy_param = NULL;
    BT_NFY_ID_T   e_nfy_id     = BT_NFY_ID_UNKNOWN;

    if (bt_app_is_sink_dev_scaning())
    {
        BT_APP_LOG_API(("<BT_APP><Sink_list> Stop scaning before start connecting\n"));

        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }


    i4_ret = a_mtkapi_bt_gap_start_inquiry_scan(BT_INQUIRY_FILTER_TYPE_A2DP_SNK|BT_INQUIRY_FILTER_TYPE_HID);

    if(i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: start sink inquiry fail, %d\n", i4_ret));

        e_nfy_id = BT_NFY_ID_SCAN_FINISH;

        BT_APP_LOG_DEFAULT(("<BT_APP> bt_msg_brdcast\n"));
        bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Start sink device scaning...\n"));

        /* Free old detected sink device list */
        _bt_app_free_a2dp_snk_dev_list();

        // clear paired sink devices scanning status before start new scanning
        bt_app_ui_sink_device_list_paired_dev_scanning_status_clear();

        /* set flag indicate scaning is started */
        bt_app_set_flag_sink_dev_scaning(TRUE);

        /* create scan timer */
        bt_app_create_sink_device_scan_timer();

        /* start scan timer, time out 15s */
        bt_app_start_sink_device_scan_timer(time_out);

        /* init A2DP Sink device list */
        _bt_app_init_a2dp_snk_dev_list();
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_stop_a2dp_snk_inquiry_scan
  *
  * Description  - stop A2DP Sink divice inquiry scan.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_stop_a2dp_snk_inquiry_scan(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
    if(i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: stop sink inquiry fail, %d\n", i4_ret));
    }

    _bt_app_free_a2dp_snk_dev_list();

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_save_bluetooth_data
  *
  * Description  - save bluetooth data, which include:
  *                        1. bluetooth data used by Blueangel.
  *                        2. paired device list in BTM
  *                     These data is stored in DRAM when Blueangel and BTM are working.
  *                     Call this API to save these data to NAND flash from DRAM.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_save_bluetooth_data(VOID)
{
    //INT32   i4_ret = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));

    // save paired device list in BTM
//    c_btm_save_device_history();

    //execl("/bin/rm", "rm -rf /mnt/ubi_boot/bt/*", NULL);

    // save Bluetooth info into NAND /mnt/ubi_boot/bt/
    //i4_ret = execl("/bin/cp", "cp -arf /tmp/bluetooth /mnt/ubi_boot/bt/", NULL);
    //if (0 != i4_ret)
    {
        //BT_APP_LOG_DEFAULT(("<BT_APP> ERR: save device info fail, %d\n", i4_ret));
        //return PBR_FAIL;
    }

    return PBR_OK;
}
#if 0

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_load_bluetooth_data
  *
  * Description  - Load bluetooth data from NAND to DRAM
  *                     When Blueangel is working, it store data into DRAM.
  *                     This data is saved to NAND flash when power off.
  *                     Before Blueangel is started, this API need to be called to load bluetooth data from NAND to DRAM.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_load_bluetooth_data(VOID)
{


    INT32   i4_ret = 0;

    system("rm -rf /tmp/bluetooth");

    // load bluetooth data from NAND to DRAM
    i4_ret = system("cp -arf /mnt/ubi_boot/bt/bluetooth /tmp/");
    if (0 != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: recover device info fail, %d\n", i4_ret));
        return PBR_FAIL;
    }

    return PBR_OK;
}
#endif

/**---------------------------------------------------------------------------
  * Name          - a_bt_app_clear_bluetooth_data
  *
  * Description  - clear bluetooth data, which include:
  *                       1. bluetooth data used by Blueangel.
  *                       2. paired device list in BTM
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_clear_bluetooth_data(VOID)
{
    INT32   i4_ret = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    // disconnect BT before initialize personal information
    if (bt_app_input_a2dp_connected())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Stop BTM\n"));
        //c_btm_stop(FALSE,FALSE);
    }

    if (bt_app_output_a2dp_connected())
    {
        bt_app_disconnect_with_sink_dev();
    }

    c_thread_delay(300);

    //for BDP00416535, only do below process in normal mode
    //if (!(d_ifcon_diag_mode() || d_ifcon_service_mode()))
    {
        // delete link key
        //c_btm_paired_dev_erase_all();

        // remove all devices from paired device list
//        i4_ret = c_btm_del_paired_av_dev_all();
        if (0 != i4_ret)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: remove paired device fail, %d\n", i4_ret));
            return PBR_FAIL;
        }

//        c_btm_save_device_history();

        /* Update bluetooth standby status to IFCON when remove src/snk devices */
        a_bt_setup_bt_standby(TRUE);
    }

    // clear bluetooth data used by Blueangel
    //execl("/bin/rm", "rm -rf /tmp/bluetooth/bt_paired_sink_device_history.txt", NULL);
    //execl("/bin/rm", "rm -rf /mnt/ubi_boot/bt/bt_paired_sink_device_history.txt*", NULL);

    return PBR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - a_bt_app_clear_wireless_controller_data
  *
  * Description  - clear wireless controller data, which include:
  *                       1. wireless controller data used by Blueangel.
  *                       2. paired wireless controller device list in BTM
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_app_clear_wireless_controller_data(VOID)
{
    UINT8  i = 0;
    INT32 i4_ret = PBR_OK;
    BT_HID_TARGET_DEV_LIST t_device_list = {0};
    BT_HID_STATUS_STRUCT_LIST pt_device_status;
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    // disconnect all wireless controller before initialize personal information

    bt_app_hid_disconnect_all();


    //c_thread_delay(300);
    c_memset(&pt_device_status, 0, sizeof(BT_HID_STATUS_STRUCT_LIST));
    // get hid paired device list from BTM
//    i4_ret = c_btm_get_paired_hid_dev_list(&t_device_list, &pt_device_status);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> get hid paired device list fail\n"));
    }

    // erase all hid paired info from Blueangel
    for(i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP> erase hid paired info from blueangel : %s\n", t_device_list.device_list[i].bdAddr));
        a_mtkapi_bt_gap_unpair(t_device_list.device_list[i].bdAddr);
    }

    // remove all hid paired devices from paired device list
    for (i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP> erase hid paired info from sink paired device list: %s\n", t_device_list.device_list[i].bdAddr));
        i4_ret = a_mtkapi_bt_gap_unpair(t_device_list.device_list[i].bdAddr);
    }

    // clear wireless controller data used by Blueangel
    //execl("/bin/rm", "rm -rf /tmp/bluetooth/bt_paired_hid_device_history.txt", NULL);
    //execl("/bin/rm", "rm -rf /mnt/ubi_boot/bt/bt_paired_hid_device_history.txt*", NULL);

    return PBR_OK;
}

#endif


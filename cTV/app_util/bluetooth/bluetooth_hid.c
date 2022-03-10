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
 * $RCSfile: bluetooth_hid.c,v $
 * $Revision: #5 $
 * $Date: 2015/11/19 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file establishes HID connection.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include "a_cfg.h"

#include "u_bt_mw_hidh.h"
#include "mtk_bt_service_gap_wrapper.h"
#include "mtk_bt_service_hidh_wrapper.h"


#include "bluetooth.h"
#include "bluetooth_device.h"
#include "bluetooth_hid.h"
#include "bluetooth_spp.h"
#include "bluetooth_timer.h"
#include "bluetooth_global_variables.h"
#include "bluetooth_msgproc.h"
#include "bluetooth_device_list.h"

BOOL fg_bt_hid_disconnect_all = FALSE;

typedef VOID (*mtkstub_bluetooth_hid_connected_cbk_fct)(CHAR* pv_tag);
typedef VOID (*mtkstub_bluetooth_hid_disconnected_cbk_fct)(CHAR* pv_tag);
typedef VOID (*mtkstub_bluetooth_hid_connection_rejected_cbk_fct)(VOID);
typedef VOID (*mtkstub_bluetooth_hid_low_battery_cbk_fct)(uint8_t u1_tag);

static mtkstub_bluetooth_hid_connected_cbk_fct pf_bt_hid_connected_cbk_fct = NULL;
static mtkstub_bluetooth_hid_disconnected_cbk_fct pf_bt_hid_disconnected_cbk_fct = NULL;
static mtkstub_bluetooth_hid_connection_rejected_cbk_fct pf_bt_hid_connection_rejected_cbk_fct = NULL;
static mtkstub_bluetooth_hid_low_battery_cbk_fct pf_bt_hid_low_battery_cbk_fct = NULL;


/**---------------------------------------------------------------------------
* Name          - _bt_app_wireless_controller_inquiry_cbk_fct
*
* Description  - if a hid is detected,  will callback this function
*
* Input         -
*
* Returns       -
*---------------------------------------------------------------------------*/
#if 0
static VOID _bt_app_wireless_controller_inquiry_cbk_fct(BT_GAP_SCAN_RESULT* pt_result)
{
    INT32 i4_ret = BT_APPR_OK;
    
    if(NULL == pt_result)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return ;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> HID device is detected, name is %s, addr is %s\n",
                                                pt_result->name, pt_result->bdAddr));

    if(0 == strcmp("Wireless Controller", pt_result->name))
    {
        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }
        BT_APP_LOG_DEFAULT(("<BT_APP> Start to connect HID device\n"));
        i4_ret = a_mtkapi_hidh_connect(pt_result->bdAddr);
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: connect hidh fail, %d\n", i4_ret));
        }
    }

    return;
}
#endif
/**---------------------------------------------------------------------------
* Name          - bluetooth_hid_register_start
*
* Description  -  call this function to start HID scaning and connecting
*
* Input         -
*
* Returns       -
*---------------------------------------------------------------------------*/
INT32 bluetooth_hid_register_start()
{
    //c_btm_start_inquiry_scan(0, _bt_app_wireless_controller_inquiry_cbk_fct);
    return 0;
}

/**---------------------------------------------------------------------------
* Name          - bluetooth_hid_get_wireless_ctrllor_list
*
* Description  -  call this function to get wireless controller list(mac & connection state)
*
* Input         -
*
* Returns       -
*---------------------------------------------------------------------------*/
INT32 bluetooth_hid_get_wireless_controller_list(BT_TARGET_HID_LIST *list)
{
    INT32 i4_ret = BT_APPR_OK;
    UINT8 connect_stauts_confirm = 0x00;
    UINT8 first_index, second_index, i;
    BT_HID_TARGET_DEV_LIST pt_device_list;
    BT_HID_STATUS_STRUCT_LIST pt_device_status;

    if(NULL == list)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_FAIL;
    }
    c_memset(&pt_device_list, 0, sizeof(BT_HID_TARGET_DEV_LIST));
    c_memset(&pt_device_status, 0, sizeof(BT_HID_STATUS_STRUCT_LIST));
    //connect_stauts_confirm = c_btm_get_paired_hid_dev_list(&pt_device_list, &pt_device_status);

    BT_APP_LOG_DEFAULT(("<BT_APP> DS4 connect_status:%02x\n", connect_stauts_confirm));

    if(pt_device_list.dev_num > MAX_HID_NUM)
    {
        BT_APP_LOG_ERR(("<BT_APP>get hid num error\n"));
        return BT_APPR_FAIL;
    }

    first_index = connect_stauts_confirm & 0x0F;
    second_index = (connect_stauts_confirm & 0xF0)>>4;

    BT_APP_LOG_INFO(("<BT_APP> DS4 first_index=%d second_index=%d\n",
                                        first_index, second_index));

    list->num = pt_device_list.dev_num;

    for(i=0; i < pt_device_list.dev_num; i++)
    {
        strncpy(list->hid_list[i].bdAddr, pt_device_list.device_list[i].bdAddr, (MAX_BDADDR_LEN-1));
        list->hid_list[i].device_type=pt_device_list.device_list[i].device_type;
#if 0
        if(i==(first_index -1))
        {
            list->hid_list[i].ccState = BT_HID_CONN_STATE_FIRST;
        }
        else if(i==(second_index -1))
        {
            list->hid_list[i].ccState = BT_HID_CONN_STATE_SECOND;
        }
        else
        {
            list->hid_list[i].ccState = BT_HID_CONN_STATE_REGISTERED;
        }
#endif
        list->hid_list[i].ccState = pt_device_status.device_list[i].status;

        BT_APP_LOG_DEFAULT(("<BT_APP> DS4 Addr=%s ccState=%d device_type=%d\n",
                                                    list->hid_list[i].bdAddr,
                                                    list->hid_list[i].ccState,
                                                    list->hid_list[i].device_type));
    }

    return i4_ret;
}

INT32 bt_app_get_first_hid_addr(CHAR *addr)
{
    UINT32 i, i4_ret = BT_APPR_OK;
    BT_TARGET_HID_LIST list;

    i4_ret = bluetooth_hid_get_wireless_controller_list(&list);

    if(BT_APPR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP>Get wireless controller list error!\n"));
        return i4_ret;
    }

    for(i=0 ;i < list.num; i++)
    {
        if(BT_HID_CONN_STATE_CONNECTED == list.hid_list[i].ccState)
        {
            strncpy(addr, list.hid_list[i].bdAddr, (MAX_BDADDR_LEN-1));
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Get first HID addr: %s\n", addr));

    return i4_ret;
}

INT32 bt_app_hid_disconnect_all()
{
    UINT32 i4_ret = BT_APPR_OK;
    UINT32 i=0;

    BT_TARGET_HID_LIST list;

    i4_ret = bluetooth_hid_get_wireless_controller_list(&list);

    for(i=0 ;i < list.num; i++)
    {
        if(BT_HID_CONN_STATE_CONNECTED == list.hid_list[i].ccState)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> bt_app_hid_disconnect_all: first HID %s\n",list.hid_list[i].bdAddr));
            i4_ret=a_mtkapi_hidh_disconnect(list.hid_list[i].bdAddr);
        }
        #if 0
        else if(BT_HID_CONN_STATE_SECOND== list.hid_list[i].ccState)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> bt_app_hid_disconnect_all: first HID %s\n",list.hid_list[i].bdAddr));
            i4_ret=c_btm_disconnect_hid_sources(list.hid_list[i].bdAddr);
        }
        #endif
    }

    //bt_app_get_first_hid_addr(first_addr);
    //c_btm_disconnect_hid_sources(first_addr);

    return i4_ret;
}

INT32 bt_app_on_off_hid_reconnect(void)
{
    UINT32 i4_ret = BT_APPR_OK;
    UINT32 i=0;

    BT_TARGET_HID_LIST list;

    /* Before start connecting, stop scaning */
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

    i4_ret = bluetooth_hid_get_wireless_controller_list(&list);

    for(i=0 ;i < list.num; i++)
    {
        if ((BT_HID_CONN_STATE_PAIRED == list.hid_list[i].ccState)&&(list.hid_list[i].device_type != 1))
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> bt_app_hid_reconnect: first HID %s\n",list.hid_list[i].bdAddr));
            i4_ret=a_mtkapi_hidh_connect(list.hid_list[i].bdAddr);
        }
    }

    return i4_ret;
}

INT32 bt_app_get_connected_hid_num()
{
    INT32 num = 0, i4_ret = BT_APPR_OK;
    UINT32 i;
    BT_TARGET_HID_LIST list;

    i4_ret = bluetooth_hid_get_wireless_controller_list(&list);

    if(BT_APPR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP>Get wireless controller list error!\n"));
        return i4_ret;
    }

    for(i = 0; i < list.num; i++)
    {
        if((BT_HID_CONN_STATE_CONNECTED == list.hid_list[i].ccState))
        {
            num++;
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP>Get connected HID num: %d\n", num));

    return num;
}

INT32 bt_app_stop_scan_hid()
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_LOG_DEFAULT(("<BT_APP> %s \n", __FUNCTION__));
    i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
    return i4_ret;
}

/**---------------------------------------------------------------------------
* Name          - bluetooth_hid_remove_one
*
* Description  -  remove one wireless controller from hid list
* Input         -
*
* Returns       -
*---------------------------------------------------------------------------*/
INT32 bluetooth_hid_remove_one(CHAR* addr)
{
    BT_TARGET_DEV_INFO device_info;

    if(NULL == addr)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_FAIL;
    }
    else
    {
        strncpy(device_info.bdAddr, addr, (MAX_BDADDR_LEN-1));

        a_mtkapi_bt_gap_unpair(device_info.bdAddr);
        bt_app_remove_one_from_dev_list(device_info.bdAddr);
    }

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
* Name          - bluetooth_hid_remove_all
*
* Description  -  remove all wireless controllers
* Input         -
*
* Returns       -
*---------------------------------------------------------------------------*/
INT32 bluetooth_hid_remove_all(VOID)
{
    INT8  i = 0;
    INT32 i4_ret = PBR_OK;
    BT_HID_TARGET_DEV_LIST t_device_list = {0};
    BT_HID_STATUS_STRUCT_LIST pt_device_status;

    //bt_app_hid_disconnect_all();

    // get hid paired device list from BTM
    c_memset(&pt_device_status, 0, sizeof(BT_HID_STATUS_STRUCT_LIST));
    //i4_ret = c_btm_get_paired_hid_dev_list(&t_device_list, &pt_device_status);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> get hid paired device list fail\n"));
    }

    // erase all hid paired info from Blueangel
    for(i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP> erase hid paired info from blueangel : %s\n", t_device_list.device_list[i].bdAddr));
        a_mtkapi_bt_gap_unpair(t_device_list.device_list[i].bdAddr);
        bt_app_remove_one_from_dev_list(t_device_list.device_list[i].bdAddr);
    }

    // remove all hid paired devices from paired device list
    for (i=0; i<t_device_list.dev_num; i++)
    {
        BT_APP_LOG_INFO(("<BT_APP> erase hid paired info from sink paired device list: %s\n", t_device_list.device_list[i].bdAddr));
        //i4_ret = c_btm_del_paired_hid_dev_one(&(t_device_list.device_list[i]));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
* Name          - bluetooth_hid_wireless_controller_operation
*
* Description  -
*
* Input         -
*
* Returns       -
*---------------------------------------------------------------------------*/
VOID bluetooth_hid_wireless_controller_operation(CHAR *hid_addr, BT_HID_OPERATION_TYPE_E event)
{

    BT_APP_LOG_DEFAULT(("<BT_APP>Wireless Controller Operation:%d\n", event));

    switch(event)
    {
        case BT_HID_OPERATION_TURN_OFF:
            a_mtkapi_hidh_disconnect(hid_addr);
            break;

        case BT_HID_OPERATION_REMOVE:
            bluetooth_hid_remove_one(hid_addr);
            break;

        case BT_HID_OPERATION_REMOVE_ALL:
            bluetooth_hid_remove_all();
            break;
        default:
            break;
    }

    return;
}

VOID bt_app_notify_hid_connect_to_x2(VOID)
{
    if (NULL != pf_bt_hid_connected_cbk_fct)
    {
        pf_bt_hid_connected_cbk_fct("Wireless Controller");
        BT_APP_LOG_DEFAULT(("<BT_APP> notify X2: HID is connected\n"));
    }
}

VOID bt_app_notify_hid_disconnect_to_x2(VOID)
{
    if (NULL != pf_bt_hid_connected_cbk_fct)
    {
        pf_bt_hid_disconnected_cbk_fct("Wireless Controller");
        BT_APP_LOG_DEFAULT(("<BT_APP> notify X2: HID is disconnected\n"));
    }
}

VOID bt_app_notify_hid_connection_rejected_to_x2(VOID)
{
    if (NULL != pf_bt_hid_connection_rejected_cbk_fct)
    {
        pf_bt_hid_connection_rejected_cbk_fct();
    }
}
#if 0
static INT32 _bluetooth_hid_nfy_connected_proc()
{
    INT32   i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    bt_app_set_flag_hid_connected(TRUE);

    bt_app_notify_hid_connect_to_x2();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;

}

static INT32 _bluetooth_hid_nfy_disconnected_proc()
{
    INT32 i4_ret = BT_APPR_OK, hid_connected_num = 0;
    UINT8 u1_bt_mode = 0;
	UINT8 u1_bt_switch_status = 0;
    CHAR hid_addr[MAX_BDADDR_LEN] = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    hid_connected_num = bt_app_get_connected_hid_num();

    if(hid_connected_num > 0)
    {
        if(fg_bt_hid_disconnect_all)
        {
            bt_app_get_first_hid_addr(hid_addr);
            c_btm_disconnect_hid_sources(hid_addr);
        }
    }
    else
    {
        //clear flag
        fg_bt_hid_disconnect_all = FALSE;
        bt_app_set_flag_hid_connected(FALSE);

        a_cfg_get_bluetooth_switch_status(&u1_bt_switch_status);
		a_cfg_get_bluetooth_mode_status(&u1_bt_mode);

        bt_app_set_setting_mode_changed(FALSE);

        if (a_bt_bluetooth_mode_get() != u1_bt_mode)
        {
            a_bt_bluetooth_mode_set(u1_bt_mode);
        }

        if((APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_switch_status)
            && a_bt_is_bluetooth_enabled())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> All HID is disconnected, disable BT\n"));
            a_bt_enable_disable(FALSE);
        }
    }

    bt_app_notify_hid_disconnect_to_x2();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

#endif
/**---------------------------------------------------------------------------
* Name          - bt_app_hid_event_proc
*
* Description  -  process the event of HID
*
* Input         -
*
* Returns       -
*---------------------------------------------------------------------------*/
#if CONFIG_APP_SUPPORT_BX_BT
typedef struct
{
    BT_HID_EVENT state;
    CHAR    bdAddr[MAX_BDADDR_LEN];
}JELLYFISH_BT_HID_STATUS;

extern VOID bt_hid_notity_connection_state(JELLYFISH_BT_HID_STATUS bt_hid_message);//(BT_HID_EVENT state)
extern INT32 bt_hid_notify_wireless_controller_setting_start(void);
#endif

VOID bt_app_hid_event_proc(BT_HIDH_CBK_STRUCT *fg_bt_hid_struct_data)
{
    VOID*        pv_nfy_param = NULL;
    BT_NFY_ID_T   e_nfy_id = BT_NFY_ID_UNKNOWN;

#if CONFIG_APP_SUPPORT_BX_BT
    JELLYFISH_BT_HID_STATUS bt_hid_messages;
    bt_hid_messages.state =fg_bt_hid_struct_data->event;
#endif

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    BT_APP_LOG_DEFAULT(("<BT_APP> HID event: %d\n", fg_bt_hid_struct_data->event));



    switch(fg_bt_hid_struct_data->event)
    {
        case BT_HIDH_CONNECTED:
            if (bt_app_is_sink_dev_list_start()
                    ||bt_app_is_audio_output_dev_list_start())
            {
                _e_bluetooth_state = BLUETOOTH_BT_SRC_CONNECTED_STATE;
            }

            bt_app_set_flag_hid_connected(TRUE);
            bt_app_set_flag_keyboard_mouse_connected(TRUE);
            e_nfy_id = BT_NFY_ID_CONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);

            break;
        case BT_HIDH_CONNECTING:
            break;
        case BT_HIDH_DISCONNECTED:
            if (bt_app_is_sink_dev_list_start()
                    ||bt_app_is_audio_output_dev_list_start())
            {
                _e_bluetooth_state = BLUETOOTH_BT_SRC_DISCONNECTED_STATE;
            }
            //if (fg_bt_hid_struct_data->conn_nubmer == 0)
            {
                bt_app_set_flag_hid_connected(FALSE);
                bt_app_set_flag_keyboard_mouse_connected(FALSE);
            }
            e_nfy_id = BT_NFY_ID_DISCONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);

            break;
        case BT_HIDH_DISCONNECTING:
            break;
        case BT_HIDH_CONNECT_FAIL:
            e_nfy_id = BT_NFY_ID_CONNECT_FAIL;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        case BT_HIDH_DISCONNECT_FAIL:
            e_nfy_id = BT_NFY_ID_DISCONNECT_FAIL;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        case BT_HIDH_CONNECTION_REJECT:
        //case BT_HIDH_BATTERY:
        default:
            break;
    }

#if CONFIG_APP_SUPPORT_BX_BT
    bt_hid_notity_connection_state(bt_hid_messages);
if(0) bt_hid_notify_wireless_controller_setting_start();
#endif

    return;
}

#if CONFIG_APP_SUPPORT_BX_BT
VOID bt_app_notify_hid_connection_battery_low_to_x2(uint8_t controllerID)
{
    if (NULL != pf_bt_hid_low_battery_cbk_fct)
    {
        pf_bt_hid_low_battery_cbk_fct(controllerID);
    }
}
#endif

ErrorCode bluetooth_wireless_controller_settings_start(void)
{
#if CONFIG_APP_SUPPORT_BX_BT

    bt_hid_notify_wireless_controller_setting_start();
#endif
    return ERRORCODE_OK;
}

BOOL bluetooth_hid_connected_cbk_reg(mtkstub_bluetooth_hid_connected_cbk_fct fct)
{
    if(NULL == fct)
    {
        return FALSE;
    }
    else
    {
        pf_bt_hid_connected_cbk_fct = fct;
    return TRUE;
}
}

BOOL bluetooth_hid_connected_cbk_unreg(void)
{
    pf_bt_hid_connected_cbk_fct=NULL;
    return TRUE;
}

BOOL bluetooth_hid_disconnected_cbk_reg(mtkstub_bluetooth_hid_disconnected_cbk_fct fct)
{
    if(NULL == fct)
    {
        return FALSE;
    }
    else
    {
        pf_bt_hid_disconnected_cbk_fct = fct;
    return TRUE;
}
}

BOOL bluetooth_hid_disconnected_cbk_unreg(void)
{
    pf_bt_hid_disconnected_cbk_fct=NULL;
    return TRUE;
}

BOOL  bluetooth_hid_connection_rejected_cbk_reg(mtkstub_bluetooth_hid_connection_rejected_cbk_fct fct)
{
    if(NULL == fct)
    {
        return FALSE;
    }
    else
    {
        pf_bt_hid_connection_rejected_cbk_fct = fct;
        return TRUE;
    }
}

BOOL bluetooth_hid_connection_rejected_cbk_unreg(void)
{
    pf_bt_hid_connection_rejected_cbk_fct = NULL;
    return TRUE;
}

BOOL bluetooth_hid_low_battery_cbk_reg(mtkstub_bluetooth_hid_low_battery_cbk_fct fct)
{
    if(NULL == fct)
    {
        return FALSE;
    }
    else
    {
        pf_bt_hid_low_battery_cbk_fct = fct;
        return TRUE;
    }
}

BOOL bluetooth_hid_low_battery_cbk_unreg(void)
{
    pf_bt_hid_low_battery_cbk_fct = NULL;
    return TRUE;
}

VOID bluetooth_test_mode_start(BT_TEST_MODE_COMMAND_T *command)
{
    INT32 flag = 0;

    if(NULL == command)
    {
        BT_APP_LOG_DEFAULT(("Test mode command is null !\n"));
        return;
    }

    if(command->reset)//chip reset && BT reset
    {
         flag = 1;
    }
    else
    {
        if(BT_TEST_MODE_CLASSIC == command->function)//BDR/EDR
        {
            if(BT_TEST_MODE_TX == command->mode)
            {
                if(BT_TEST_MODE_WAVE==command->modulation)
                {
                    if(command->test_start)
                    {
                        switch(command->frequency)
                        {
                            case BT_TEST_MODE_CH0://continuous wave CHO
                                flag=2;
                                break;
                            case BT_TEST_MODE_CH39://continuous wave CH39
                                flag=3;
                                break;
                            case BT_TEST_MODE_CH78://continuous wave CH78
                                flag=4;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        flag = 119;
                    }
                }
                else if(BT_TEST_MODE_FIXED==command->modulation)
                {
                    if(BT_TEST_MODE_CH0==command->frequency)//Frequecy Fixed CH0
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DM1:
                                flag=5;
                                break;
                            case BT_TEST_MODE_DM3:
                                flag=6;
                                break;
                            case BT_TEST_MODE_DM5:
                                flag=7;
                                break;
                            case BT_TEST_MODE_DH1:
                                flag=8;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=9;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=10;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=11;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=12;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=13;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=14;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=15;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=16;
                                break;
                            default:
                                break;
                        }
                    }
                    else if(BT_TEST_MODE_CH39==command->frequency)//Frequecy Fixed CH39
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DM1:
                                flag=17;
                                break;
                            case BT_TEST_MODE_DM3:
                                flag=18;
                                break;
                            case BT_TEST_MODE_DM5:
                                flag=19;
                                break;
                            case BT_TEST_MODE_DH1:
                                flag=20;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=21;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=22;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=23;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=24;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=25;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=26;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=27;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=28;
                                break;
                            default:
                                break;
                        }
                    }
                    else if(BT_TEST_MODE_CH78==command->frequency)//Frequecy Fixed CH78
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DM1:
                                flag=29;
                                break;
                            case BT_TEST_MODE_DM3:
                                flag=30;
                                break;
                            case BT_TEST_MODE_DM5:
                                flag=31;
                                break;
                            case BT_TEST_MODE_DH1:
                                flag=32;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=33;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=34;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=35;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=36;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=37;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=38;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=39;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=40;
                                break;
                            default:
                                break;
                        }
                    }
                }
                else if(BT_TEST_MODE_HOPPING==command->modulation)/*Frequecy Hopping*/
                {
                    switch(command->packet)
                    {
                        case BT_TEST_MODE_DM1:
                            flag=41;
                            break;
                        case BT_TEST_MODE_DM3:
                            flag=42;
                            break;
                        case BT_TEST_MODE_DM5:
                            flag=43;
                            break;
                        case BT_TEST_MODE_DH1:
                            flag=44;
                            break;
                        case BT_TEST_MODE_DH3:
                            flag=45;
                            break;
                        case BT_TEST_MODE_DH5:
                            flag=46;
                            break;
                        case BT_TEST_MODE_2DH1:
                            flag=47;
                            break;
                        case BT_TEST_MODE_2DH3:
                            flag=48;
                            break;
                        case BT_TEST_MODE_2DH5:
                            flag=49;
                            break;
                        case BT_TEST_MODE_3DH1:
                            flag=50;
                            break;
                        case BT_TEST_MODE_3DH3:
                            flag=51;
                            break;
                        case BT_TEST_MODE_3DH5:
                            flag=52;
                            break;
                        default:
                            break;
                    }
                }
            }
            else if(BT_TEST_MODE_RX == command->mode)
            {
                if(BT_TEST_MODE_CH0==command->frequency)/*RX CH0*/
                {
                    if(command->test_start)
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DH1:
                                flag=53;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=54;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=55;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=56;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=57;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=58;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=59;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=60;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=61;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DH1:
                                flag=90;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=91;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=92;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=93;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=94;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=95;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=96;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=97;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=98;
                                break;
                            default:
                                break;
                        }
                    }
                }
                else if(BT_TEST_MODE_CH39 == command->frequency)//RX CH39
                {
                    if(command->test_start)
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DH1:
                                flag=62;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=63;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=64;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=65;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=66;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=67;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=68;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=69;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=70;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DH1:
                                flag=99;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=100;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=101;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=102;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=103;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=104;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=105;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=106;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=107;
                                break;
                            default:
                                break;
                        }
                    }
                }
                else if(BT_TEST_MODE_CH78 == command->frequency)//RX CH78
                {
                    if(command->test_start)
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DH1:
                                flag=71;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=72;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=73;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=74;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=75;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=76;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=77;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=78;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=79;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch(command->packet)
                        {
                            case BT_TEST_MODE_DH1:
                                flag=108;
                                break;
                            case BT_TEST_MODE_DH3:
                                flag=109;
                                break;
                            case BT_TEST_MODE_DH5:
                                flag=110;
                                break;
                            case BT_TEST_MODE_2DH1:
                                flag=111;
                                break;
                            case BT_TEST_MODE_2DH3:
                                flag=112;
                                break;
                            case BT_TEST_MODE_2DH5:
                                flag=113;
                                break;
                            case BT_TEST_MODE_3DH1:
                                flag=114;
                                break;
                            case BT_TEST_MODE_3DH3:
                                flag=115;
                                break;
                            case BT_TEST_MODE_3DH5:
                                flag=116;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            else if(BT_TEST_MODE_INQUIRY == command->mode)
            {
                flag = 89;
            }
        }
        else if(BT_TEST_MODE_LE ==  command->function)//BLE
        {
            if(BT_TEST_MODE_TX == command->mode)
            {
                if(BT_TEST_MODE_WAVE==command->modulation)
                {
                    if(command->test_start)
                    {
                        switch(command->frequency)
                        {
                            case BT_TEST_MODE_CH0://continuous wave CHO
                                flag=80;
                                break;
                            case BT_TEST_MODE_CH19://continuous wave CH19
                                flag=81;
                                break;
                            case BT_TEST_MODE_CH39://continuous wave CH39
                                flag=82;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        flag = 119;
                    }
                }
                else if(BT_TEST_MODE_FIXED==command->modulation)
                {
                    if(command->test_start)
                    {
                        switch(command->frequency)
                        {
                            case BT_TEST_MODE_CH0://frequency fixed CHO
                                flag=83;
                                break;
                            case BT_TEST_MODE_CH19://frequency fixed CH19
                                flag=84;
                                break;
                            case BT_TEST_MODE_CH39://frequency fixed CH39
                                flag=85;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        flag=117;
                    }
                }
            }
            else if(BT_TEST_MODE_RX==command->mode)
            {
                if(command->test_start)
                {
                    switch(command->frequency)
                    {
                        case BT_TEST_MODE_CH0://RX CH0
                            flag=86;
                            break;
                        case BT_TEST_MODE_CH19://RX CH19
                            flag=87;
                            break;
                        case BT_TEST_MODE_CH39://RX CH39
                            flag=88;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    flag=118;
                }
            }
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> rf test flag = %d\n", flag));

    //c_btm_rf_test(flag);

    return;
}

#endif


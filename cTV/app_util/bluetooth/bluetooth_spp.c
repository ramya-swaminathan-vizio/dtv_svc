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
 * $RCSfile: bluetooth_app.c,v $
 * $Revision: #2 $
 * $Date: 2015/10/24 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file establishes SPP connection, receive SPP data or send SPP data.
 *                  1> after A2DP and AVRCP are established, MTK notify this event to  X2
 *                  2>  X2 call bluetooth_spp_connect() to establish SPP connection.
 *                       May be double SPP UUID connection with one device.
 *                  3> when MTK receive SPP data from SRC device and data size exceeds threshold,
 *                        MTK call bluetooth_spp_received_data_cbk_fct to notify .
 *                  4>  X2 call bluetooth_spp_data_read() to read SPP data.
 *                  5>  X2 parse SPP data and call bluetooth_spp_send_data() to response.
 *      
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

/*-----------------------------------------------------------------------------
                        include files
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "c_dbg.h"

//#include "c_bt_mw_manager.h"
#include "c_bt_mw_spp.h"
#include "u_bt_mw_avrcp.h"
#include "bluetooth_global_variables.h"

#include "bluetooth.h"
#include "bluetooth_spp.h"
#include "a_bluetooth.h"
#include "mtk_bt_service_spp_wrapper.h"
#include "mtk_bt_service_a2dp_wrapper.h"


#define SPP_DATA_BUFFER_SIZE (1024)
typedef struct _BT_SPP_DATA_BUFFER   // the structure for SPP data buffer, which is a ring buffer.
{
    CHAR   ac_uuid[SPP_UUID_LENGTH];   // alloc data buffer for every UUID
    UINT32 ui4_rd;                     // read point
    UINT32 ui4_wr;                     // write point
    UINT8  aui1_bufBase[SPP_DATA_BUFFER_SIZE];   // the ring buffer
    struct _BT_SPP_DATA_BUFFER *next;  // the data buffer for other UUID
}BT_SPP_DATA_BUFFER;

// linked list for SPP data buffer
static BT_SPP_DATA_BUFFER * pt_spp_data_buffer_h = NULL;
// the semaphore for SPP data buffer
static HANDLE_T h_sema_spp_data_buf = NULL_HANDLE;

// The threshold of received SPP data to notify.
// when MTK receive SPP data from SRC device and data size exceeds threshold,
// MTK call bluetooth_spp_received_data_cbk_fct to notify .
static UINT32 ui4_spp_data_threshold_size = 0;
// The flag to specifies whether SPP receive/send data can be shown in the log.
static BOOL fg_enable_spp_data_log = TRUE;

typedef VOID (*bluetooth_spp_received_data_cbk_fct)(CHAR* pv_tag);
typedef VOID (*bluetooth_spp_connected_cbk_fct)(CHAR* pv_tag);
typedef VOID (*bluetooth_spp_disconnected_cbk_fct)(CHAR* pv_tag);

// callback this function to notify the event of receiving SPP data when SPP data exceed threshold.
static bluetooth_spp_received_data_cbk_fct pf_bt_spp_receivd_data_cbk_fct = NULL;

// callback this function to notify the event of spp connected success with uuid
static bluetooth_spp_connected_cbk_fct pf_bt_spp_connected_cbk_fct = NULL;

// callback this function to notify the event of spp disconnected with uuid
static bluetooth_spp_disconnected_cbk_fct pf_bt_spp_disconnected_cbk_fct = NULL;

// For iplib info for apple certification
static BT_APP_IPLIB_INFO_T iplib_info[] =
{
    {IPLIB_FW_VERSION, "1.0.0"},
    {IPLIB_HW_VERSION, "1.0.0"},
    {IPLIB_ACCESSARY_NAME, "AUDIO"}
};

// For spp connect fail notify from BTM, blueangel don't notify with uuid, app need to remember connect uuid
char ac_connect_target_uuid[SPP_UUID_LENGTH] = {0};


/**---------------------------------------------------------------------------
  * Name          - bluetooth_spp_set_data_size_threshold_to_notify
  *
  * Description  - Set threshold of received SPP data to notify.
  *                     If MTK receive SPP data from SRC device and data size exceeds threshold,
  *                     MTK should call bluetooth_spp_received_data_cbk_fct to notify .
  *
  * Inputs         - data_size
  *
  * Returns       - true : success, false : error
  *---------------------------------------------------------------------------*/
BOOL bluetooth_spp_set_data_size_threshold_to_notify(UINT32 data_size)
{
    ui4_spp_data_threshold_size = data_size;
    return TRUE;
}

/**---------------------------------------------------------------------------
  * Name          - bluetooth_spp_received_data_cbk_reg
  *
  * Description  - Register to allow notifying the event of receiving SPP data from SRC device 
  *                     Notify when SPP data exceed threshold.
  *
  * Inputs         - fct is callback to notify the event of receiving SPP data from SRC device
  *
  * Returns       - true : success, false : error
  *---------------------------------------------------------------------------*/
BOOL bluetooth_spp_received_data_cbk_reg(bluetooth_spp_received_data_cbk_fct fct)
{
    pf_bt_spp_receivd_data_cbk_fct  = fct;
    return TRUE;
}

/**---------------------------------------------------------------------------
  * Name          - bluetooth_spp_received_data_cbk_unreg
  *
  * Description  - Unregister to stop notifying the event of receiving SPP data from SRC device 
  *
  * Returns       - true : success, false : error
  *---------------------------------------------------------------------------*/
BOOL bluetooth_spp_received_data_cbk_unreg(void)
{
    pf_bt_spp_receivd_data_cbk_fct = NULL;
    return TRUE;
}

/*! \brief Register to notify spp status from disconnect to connect
 * 
 * \arg[in] fct is callback to notify the event of SPP connected with UUID 
 * \return true : success, false : error
 *
 */
BOOL bluetooth_spp_connected_cbk_reg(bluetooth_spp_connected_cbk_fct fct)
{
    if (NULL == fct)
    {
        return FALSE;
    }
    else
    {
        pf_bt_spp_connected_cbk_fct = fct;
        return TRUE;
    }
}

/*! \brief Unregister to stop notify spp status from disconnect to connect 
 * 
 * \return true : success, false : error
 *
 */
 BOOL bluetooth_spp_connected_cbk_unreg(void)
{
    pf_bt_spp_connected_cbk_fct = NULL;
    return TRUE;
}

/*! \brief Register to notify spp status from connect to disconnect
 * 
 * \arg[in] fct is callback to notify the event of SPP disconnected with UUID 
 * \return true : success, false : error
 *
 */
 BOOL bluetooth_spp_disconnected_cbk_reg(bluetooth_spp_disconnected_cbk_fct fct)
{
    if (NULL == fct)
    {
        return FALSE;
    }
    else
    {
        pf_bt_spp_disconnected_cbk_fct = fct;
        return TRUE;
    }
}

/*! \brief Unregister to stop notify spp status from connect to disconnect 
 * 
 * \return true : success, false : error
 *
 */
 BOOL bluetooth_spp_disconnected_cbk_unreg(void)
{
    pf_bt_spp_disconnected_cbk_fct = NULL;
    return TRUE;
}

/**---------------------------------------------------------------------------
  * Name          - bluetooth_spp_connect
  *
  * Description  - establish SPP connection with UUID
  *                     Send the request to bluetooth thread, 
  *                     bluetooth thread will call bt_spp_connect_with_uuid_proc to establish SPP connection
  *
  * Inputs         - uuid: 
  *
  * Returns       - true : success, false : error
  *---------------------------------------------------------------------------*/
BOOL bluetooth_spp_connect(char* uuid)
{
    INT32  i4_ret = PBR_OK;
    UINT32 ui4_uuid_len = 0;
    CHAR   *pc_uuid = NULL;
    BT_APP_MSG_T t_bt_msg = {0};

    if(NULL == uuid)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return FALSE;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> %s is called, uuid:%s\n", __FUNCTION__, uuid));

    // Check if the length of uuid is too long.
    ui4_uuid_len = c_strlen(uuid);
    if(ui4_uuid_len >= SPP_UUID_LENGTH)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: UUID is too long, %d, %d\n", 
            ui4_uuid_len, SPP_UUID_LENGTH));
        
        return FALSE;
    }

    pc_uuid = (CHAR *)c_mem_alloc(ui4_uuid_len + 1);
    if(NULL == pc_uuid)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: alloc mem for uuid fail\n"));
        return FALSE;
    }
    c_memset(pc_uuid, 0, ui4_uuid_len + 1);

    c_strncpy(pc_uuid, uuid, ui4_uuid_len);

    if(c_strcmp(ac_connect_target_uuid, "") != 0)
    {
        c_memset(ac_connect_target_uuid, 0, SPP_UUID_LENGTH);
        c_strncpy(ac_connect_target_uuid, uuid, ui4_uuid_len);
        BT_APP_LOG_INFO(("<BT_APP> Save connect target spp uuid:%s\n",ac_connect_target_uuid));
    }

    // send request to bluetooth thread
    t_bt_msg.msg_type = BT_APP_MSG_REQ_SPP_CONNECT; 
    t_bt_msg.ui4_data_size = ui4_uuid_len + 1;
    t_bt_msg.pv_data = pc_uuid;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send spp connect req fail\n"));
    }
    
    return TRUE;
}

/*! \brief Disconnect SPP with UUID
 * 
 * \arg[in] uuid length=8+1+4+1+4+1+4+1+12=36
 *
 * \return true : success, false : error
 *
 */
 BOOL bluetooth_spp_disconnect(char* uuid)
{
    INT32  i4_ret = PBR_OK;
    UINT32 ui4_uuid_len = 0;
    CHAR   *pc_uuid = NULL;
    BT_APP_MSG_T t_bt_msg = {0};

    if(NULL == uuid)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return FALSE;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> %s is called, %s\n", __FUNCTION__, uuid));

    // Check if the length of uuid is too long.
    ui4_uuid_len = c_strlen(uuid);
    if(ui4_uuid_len >= SPP_UUID_LENGTH)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: UUID is too long, %d, %d\n", 
            ui4_uuid_len, SPP_UUID_LENGTH));
        
        return FALSE;
    }

    pc_uuid = (CHAR *)c_mem_alloc(ui4_uuid_len + 1);
    if(NULL == pc_uuid)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: alloc mem for uuid fail\n"));
        return FALSE;
    }
    c_memset(pc_uuid, 0, ui4_uuid_len + 1);

    c_strncpy(pc_uuid, uuid, ui4_uuid_len);

    // send request to playback thread
    t_bt_msg.msg_type = BT_APP_MSG_REQ_SPP_DISCONNECT; 
    t_bt_msg.ui4_data_size = ui4_uuid_len + 1;
    t_bt_msg.pv_data = pc_uuid;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send spp disconnect req fail\n"));
    }
    
    return TRUE;
}


/**---------------------------------------------------------------------------
  * Name          - bluetooth_spp_data_read
  *
  * Description  - Read data sent from UUID via SPP.
  *                     This function will be called until the return length equals to zero.
  *
  * Inputs         - uuid: which UUID the data is read from.
  *                      data_size: 
  * Outputs       - data: 
  *
  * Returns       - length of actual read
  *---------------------------------------------------------------------------*/
UINT32 bluetooth_spp_data_read(char* data, UINT32 data_size, char* uuid)
{
    UINT32 ui4_temp = 0;
    UINT32 ui4_act_read_size = 0;     // actual read size
    BT_SPP_DATA_BUFFER *pt_buf = NULL;

    if((NULL == uuid) || (NULL == data))
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return 0;
    }

    bt_spp_data_buf_lock();
    
    // Find data buffer for the specified uuid
    pt_buf = pt_spp_data_buffer_h;
    while((pt_buf != NULL) && (c_strcmp(pt_buf->ac_uuid, uuid) !=0))
    {
        pt_buf = pt_buf->next;
    }
    if(NULL == pt_buf)  // Not find data buffer for the specified UUID
    {
        bt_spp_data_buf_unlock();
        
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: no buffer for UUID:%s\n", uuid));
        return 0;
    }

    // data size in the buffer
    ui4_act_read_size = (pt_buf->ui4_wr + SPP_DATA_BUFFER_SIZE - 
                         pt_buf->ui4_rd) % SPP_DATA_BUFFER_SIZE;

    // Check if the buffer is enough.
    if(ui4_act_read_size > data_size)
    {
        ui4_act_read_size = data_size;
    }

    // read data from buffer
    if((pt_buf->ui4_rd + ui4_act_read_size) <= SPP_DATA_BUFFER_SIZE)
    {
        c_memcpy(data, 
                 pt_buf->aui1_bufBase + pt_buf->ui4_rd, 
                 ui4_act_read_size);
    }
    else
    {
        ui4_temp = SPP_DATA_BUFFER_SIZE - pt_buf->ui4_rd;
        c_memcpy(data, 
                 pt_buf->aui1_bufBase + pt_buf->ui4_rd, 
                 ui4_temp);
        c_memcpy(data + ui4_temp, 
                 pt_buf->aui1_bufBase, 
                 ui4_act_read_size - ui4_temp);
    }
    pt_buf->ui4_rd = (pt_buf->ui4_rd + ui4_act_read_size) % SPP_DATA_BUFFER_SIZE;

    bt_spp_data_buf_unlock();

    return ui4_act_read_size;
}

/**---------------------------------------------------------------------------
  * Name          - bluetooth_spp_send_data
  *
  * Description  - Send data to UUID via SPP
  *
  * Inputs         - uuid: specify the UUID which the data is send to
  *                      data:
  *                      data_size: data size
  *
  * Returns       - length of actual send
  *---------------------------------------------------------------------------*/
UINT32 bluetooth_spp_send_data(char* data, UINT32 data_size, char* uuid)
{
    UINT32 ui4_idx = 0;
    
    if((NULL == uuid) || (NULL == data))
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return 0;
    }

    // print the data for debug
    if(fg_enable_spp_data_log)
    {
        BT_APP_LOG_DEFAULT(("\n<BT_APP> ------Send SPP data-------------------------\n"));
        BT_APP_LOG_DEFAULT(("<BT_APP> UUID: %s\n", uuid));
        BT_APP_LOG_DEFAULT(("<BT_APP> Data len: %d\n", data_size));
        
        for(ui4_idx = 0; ui4_idx < data_size; ui4_idx++)
        {
            BT_APP_LOG_DEFAULT(("%c", data[ui4_idx]));
        }
        BT_APP_LOG_DEFAULT(("\n<BT_APP> ------End-----------------------------------\n"));
    }
    
    //mark_temo c_btm_spp_send_data(data, data_size, uuid);
    
    return data_size;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_spp_create_data_buffer
  *
  * Description  - create and init spp data buffer for the specified UUID.
  *
  * Inputs         - uuid: specify the UUID for which the spp data buffer is created.
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static INT32 _bt_spp_create_data_buffer(CHAR* uuid)
{
    INT32  i4_ret = PBR_OK;
    UINT32 ui4_uuid_len = 0;
    BT_SPP_DATA_BUFFER *pt_buf = NULL;

    if(NULL == uuid)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }

    ui4_uuid_len = c_strlen(uuid);
    if(ui4_uuid_len > SPP_UUID_LENGTH - 1)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: UUID is too long, %d, %d\n", 
            ui4_uuid_len, SPP_UUID_LENGTH));
        
        return PBR_FAIL;
    }

    pt_buf = (BT_SPP_DATA_BUFFER *)c_mem_alloc(sizeof(BT_SPP_DATA_BUFFER));
    if(NULL == pt_buf)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: create spp data buffer fail\n"));
        return PBR_FAIL;
    }

    c_memset(pt_buf, 0, sizeof(BT_SPP_DATA_BUFFER));

    c_strncpy(pt_buf->ac_uuid, uuid, ui4_uuid_len);
    pt_buf->ui4_rd = 0;
    pt_buf->ui4_wr = 0;

    // insert into linked list as the first node.
    bt_spp_data_buf_lock();
    pt_buf->next = pt_spp_data_buffer_h; 
    pt_spp_data_buffer_h = pt_buf;
    bt_spp_data_buf_unlock();

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_spp_free_data_buffer
  *
  * Description  - free spp data buffer for the specified UUID.
  *
  * Inputs         - uuid: specify the UUID for which the spp data buffer is to free.
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static VOID _bt_spp_free_data_buffer(CHAR* uuid)
{
    BT_SPP_DATA_BUFFER *pt_buf_prev = NULL;
    BT_SPP_DATA_BUFFER *pt_buf_cur = NULL;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s, free data buffer for uuid:%s\n", __FUNCTION__, uuid));

    //free specific spp buffer
    bt_spp_data_buf_lock();
    pt_buf_prev = NULL;
    pt_buf_cur = pt_spp_data_buffer_h;
    BT_APP_LOG_DEFAULT(("<BT_APP> Search spp buffer start\n"));
    while(NULL != pt_buf_cur)
    {
        if (0 != c_strcmp(pt_buf_cur->ac_uuid, uuid))
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> uuid:%s, search next node\n", pt_buf_cur->ac_uuid));
            
            //search next node
            pt_buf_prev = pt_buf_cur;
            pt_buf_cur = pt_buf_prev->next;
        }
        else
        {
            //find the specific spp buffer
            BT_APP_LOG_DEFAULT(("<BT_APP> uuid:%s, find the target\n", pt_buf_cur->ac_uuid));
            break;
        }
    }
    BT_APP_LOG_DEFAULT(("<BT_APP> Search spp buffer end\n"));

    if (NULL != pt_buf_cur)
    {
        if(NULL == pt_buf_prev)
        {
            //first node is the target spp buffer
            pt_spp_data_buffer_h = pt_buf_cur->next;
        }
        else
        {
            pt_buf_prev->next = pt_buf_cur->next;
        }
        c_mem_free(pt_buf_cur);
        pt_buf_cur = NULL;
        
        BT_APP_LOG_DEFAULT(("<BT_APP> uuid:%s, free spp buffer done\n", uuid));
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, uuid:%s, spp buffer NOT exist\n", __FUNCTION__, uuid));
    }
    bt_spp_data_buf_unlock();
    
}


/**---------------------------------------------------------------------------
  * Name          - _bt_spp_notify_receiving_data_to_x2
  *
  * Description  - notify X2 the event of receiving SPP data when SPP data exceed threshold.
  *
  * Inputs         - uuid: specify the UUID for which the SPP connection is established. 
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static VOID _bt_spp_notify_receiving_data_to_x2(CHAR* uuid)
{
    if(NULL == uuid)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return;
    }
    
    if(NULL == pf_bt_spp_receivd_data_cbk_fct)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: please reg fct to receive spp data notify\n"));
        return;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> notify X2: receive spp data\n"));
    pf_bt_spp_receivd_data_cbk_fct(uuid);
}

static INT32 _bt_panasonic_spp_receive_data_proc(BT_SPP_RECEIVED_DATA *pt_spp_data)
{
    if (app_spp_check_ret_supported_api(pt_spp_data->aui1_data,pt_spp_data->ui4_data_len))
    {
        //app_spp_send_set_panasonic_tv_buffering
        app_spp_send_set_panasonic_tv_buffering();
    }
    else if (app_spp_check_ret_panasonic_tv_buffering(pt_spp_data->aui1_data,pt_spp_data->ui4_data_len) != 0 )
    {
        //start A2DP sound data
        //unmute audio
        a_app_set_spp_connect_status(TRUE);
        a_mtkapi_a2dp_src_mute_uploader(FALSE); //unmute
    }
    else
    {
        //start A2DP sound data
        a_mtkapi_a2dp_src_mute_uploader(FALSE); //unmute
    }
    return 0;
}


/**---------------------------------------------------------------------------
  * Name          - bt_spp_connect_with_uuid_proc
  *
  * Description  - run this API in Bluetooth thread to establish SPP connection
  *
  * Inputs         - uuid: specify the UUID for which the SPP connection is established. 
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
INT32 bt_spp_connect_with_uuid_proc(CHAR* uuid)
{
    INT32 i4_ret = 0;
    //CHAR  ac_mac_addr[25] = {0};

    if(NULL == uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }

    // get the MAC of the device which is connected with BDV
    //i4_ret = c_btm_get_target_addr(ac_mac_addr);
    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: cannot get target MAC\n"));
        return PBR_FAIL;
    }

    //mark_temp i4_ret = c_btm_spp_connectwithUUID_async(ac_mac_addr, uuid);
    if(i4_ret != 0)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, request spp connect fail, uuid:%s, i4_ret=%d\n", __FUNCTION__, uuid, i4_ret));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, request spp connect success, uuid:%s\n", __FUNCTION__, uuid));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_spp_disconnect_with_uuid_proc
  *
  * Description  - run this API in playback thread to disconnect SPP connection with uuid
  *
  * Inputs         - uuid: specify the UUID to disconnect SPP. 
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
INT32 bt_spp_disconnect_with_uuid_proc(CHAR* uuid)
{
    INT32 i4_ret = BT_APPR_OK;

    if(NULL == uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }
    
    // disconnect SPP
    //mark_temp i4_ret = c_btm_spp_disconnect(uuid);    
    if (BT_APPR_OK != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, request spp disconnect fail, uuid:%s, i4_ret=%d\n", __FUNCTION__, uuid, i4_ret));
        return i4_ret;
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, request spp disconnect success, uuid:%s\n", __FUNCTION__, uuid));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_spp_disconnect_all_req
  *
  * Description  - requset disconnect all SPP when A2DP disconnect
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
VOID bt_spp_disconnect_all_req(VOID)
{
    INT32   i4_ret = BT_APPR_FAIL;
    BT_SPP_DATA_BUFFER *pt_buf = NULL;
    UINT8   u1_counter = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    // this API is for disconnect all spp, so set flag here
    bt_app_set_flag_disconnect_all_spp(TRUE);

    pt_buf = pt_spp_data_buffer_h;

    // if spp connection existed, then will enter this while loop for the first time
    while ((NULL != pt_buf) && (BT_APPR_OK != i4_ret))
    {
        if(c_strcmp(pt_buf->ac_uuid, "") == 0)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: Exit %s, uuid is NULL\n", __FUNCTION__));
            return;
        }

        // disconnect SPP
        while ((BT_APPR_OK != i4_ret) && (u1_counter < 5))
        {
            i4_ret = bt_spp_disconnect_with_uuid_proc(pt_buf->ac_uuid);

            u1_counter++;

            BT_APP_LOG_DEFAULT(("<BT_APP> %s: loop %d\n", __FUNCTION__, u1_counter));
        }

        u1_counter = 0;

        // still request fail for 5 times
        if (BT_APPR_OK != i4_ret)
        {
            // get next spp
            pt_spp_data_buffer_h = pt_buf->next;

            BT_APP_LOG_DEFAULT(("<BT_APP> ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"));
            BT_APP_LOG_DEFAULT(("<BT_APP> %s: uuid:%s, forcibly free spp buffer success\n", __FUNCTION__, pt_buf->ac_uuid));
            
            // reqest spp disconnect fail for 5 times, then will no notify from MW
            // free spp buffer here
            c_mem_free(pt_buf);

            // disconnect next spp here because previous spp disconnect request fail
            pt_buf = pt_spp_data_buffer_h;
        }
    }

    if (NULL == pt_buf)
    {
        bt_app_set_flag_disconnect_all_spp(FALSE);
        
        BT_APP_LOG_DEFAULT(("<BT_APP> %s: no spp connection exist\n", __FUNCTION__));
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));
}

/**---------------------------------------------------------------------------
  * Name          - _bt_spp_connect_succeed_proc
  *
  * Description  - process the event from BTM: SPP connect succeed.
  *
  * Inputs         - uuid: 
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static INT32 _bt_spp_connect_succeed_proc(CHAR* uuid)
{

    if(NULL == uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }

    // create and init spp data buffer.
    _bt_spp_create_data_buffer(uuid);

    // notify spp connection success to X2
    if (NULL != pf_bt_spp_connected_cbk_fct)
    {
        pf_bt_spp_connected_cbk_fct(uuid);
        BT_APP_LOG_DEFAULT(("<BT_APP> spp conncet success, uuid:%s, notify to X2\n", uuid));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> spp conncet success, uuid:%s, callback is unreg\n", uuid));
    }
    
    //app_spp_send_get_supported_api();
    app_spp_send_get_supported_api();
    
    // erase the saved target uuid
    c_memset(ac_connect_target_uuid, 0, SPP_UUID_LENGTH);

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_spp_connect_fail_proc
  *
  * Description  - process the event from BTM: SPP connect fail.
  *
  * Inputs         - uuid: 
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static INT32 _bt_spp_connect_fail_proc(CHAR* uuid)
{
    if(NULL == uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"));

    // notify spp connection fail to X2
    if (NULL != pf_bt_spp_disconnected_cbk_fct)
    {
        pf_bt_spp_disconnected_cbk_fct(uuid);
        BT_APP_LOG_DEFAULT(("<BT_APP> SPP connect failed, UUID:%s, notify to X2\n", uuid));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> SPP connect failed, UUID:%s, callback is unreg\n", uuid));
    }

    //unmute audio
    
    // erase the saved target uuid
    c_memset(ac_connect_target_uuid, 0, SPP_UUID_LENGTH);

    return PBR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_spp_disconnect_success_nfy_proc
  *
  * Description  - process the event from BTM: SPP disconnect success
  *
  * Inputs         - uuid: 
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static INT32 _bt_spp_disconnect_success_nfy_proc(CHAR* uuid)
{
    if(NULL == uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> %s, spp disconnect success, uuid:%s\n", __FUNCTION__, uuid));

    _bt_spp_free_data_buffer(uuid);

    // notify spp disconnect to X2
    if (NULL != pf_bt_spp_disconnected_cbk_fct)
    {
        pf_bt_spp_disconnected_cbk_fct(uuid);
        BT_APP_LOG_DEFAULT(("<BT_APP> spp disconnect success, uuid:%s, notify to X2\n", uuid));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> spp disconnect success, uuid:%s, callback is unreg\n", uuid));
    }

    // disconnect remain spp if exist when a2dp is disconnected
    if (bt_app_need_disconnect_all_spp())
    {
        if (NULL == pt_spp_data_buffer_h)
        {
            bt_app_set_flag_disconnect_all_spp(FALSE);
            BT_APP_LOG_DEFAULT(("<BT_APP> %s, disconnect all spp done.\n", __FUNCTION__));
        }
        else
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> %s, disconnect next spp\n", __FUNCTION__));
            bt_spp_disconnect_all_req();
        }
    }
    //start a2dp audio
    a_mtkapi_a2dp_src_mute_uploader(FALSE); //unmute
    return PBR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_spp_disconnect_fail_nfy_proc
  *
  * Description  - process the event from BTM: SPP disconnect fail
  *
  * Inputs         - uuid: 
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static INT32 _bt_spp_disconnect_fail_nfy_proc(CHAR* uuid)
{
    static UINT8   u1_retry_counter = 0;
    
    if(NULL == uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"));
    BT_APP_LOG_DEFAULT(("<BT_APP> ERR: spp disconnect failed, uuid:%s, not notify to X2\n", uuid));

    // spp disconnection maybe triggered by
    // 1. X2 request to disconnect spp by bluetooth_spp_disconnect
    // 2. MTK disconnect all spp by bt_spp_disconnect_all_req due to A2DP disconnected
    // spp disconnect should one by one

    if (u1_retry_counter < 5)
    {
        bt_spp_disconnect_with_uuid_proc(uuid);

        u1_retry_counter++;

        BT_APP_LOG_DEFAULT(("<BT_APP> %s, retry disconnect spp: %d\n", __FUNCTION__, u1_retry_counter));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, retry disconnect spp for %d times, reset\n", __FUNCTION__, u1_retry_counter));

        u1_retry_counter = 0;
    }

    return PBR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_spp_receive_data_proc
  *
  * Description  - callback this function to write data to buffer when receiving spp data from MW.
  *
  * Inputs         - pui1_spp_data: spp data which is received from MW
  *                     uuid: which uuid spp data is received from
  *                     ui4_data_size: the size of pui1_spp_data
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
static INT32 _bt_spp_receive_data_proc(BT_SPP_RECEIVED_DATA *pt_spp_data)
{
    INT32 i4_ret = PBR_OK;
    UINT32 ui4_idx = 0;
    UINT32 ui4_temp = 0;
    UINT32 ui4_act_write_size = 0;     // The size of the data which is writed into the buffer actually.
    BT_SPP_DATA_BUFFER *pt_buf = NULL;

    if((NULL == pt_spp_data) || (pt_spp_data->ui4_data_len > MAX_SPP_DATA_LENGTH_APP))
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_FAIL;
    }

    // print the data for debug
    if(fg_enable_spp_data_log)
    {
        BT_APP_LOG_DEFAULT(("\n<BT_APP> ------Received SPP data---------------------\n"));
        BT_APP_LOG_DEFAULT(("<BT_APP> UUID: %s\n", pt_spp_data->ac_uuid));
        BT_APP_LOG_DEFAULT(("<BT_APP> Data len: %d\n", pt_spp_data->ui4_data_len));
        
        for(ui4_idx = 0; ui4_idx < pt_spp_data->ui4_data_len; ui4_idx++)
        {
            BT_APP_LOG_DEFAULT(("%c", pt_spp_data->aui1_data[ui4_idx]));
        }
        BT_APP_LOG_DEFAULT(("\n<BT_APP> ------End-----------------------------------\n"));
    }

    bt_spp_data_buf_lock();
    
    // Find data buffer for the specified uuid
    pt_buf = pt_spp_data_buffer_h;
    while((pt_buf != NULL) && (c_strcmp(pt_buf->ac_uuid, pt_spp_data->ac_uuid) !=0))
    {
        pt_buf = pt_buf->next;
    }
    if(NULL == pt_buf)  // Not find data buffer for the specified UUID
    {
        bt_spp_data_buf_unlock();
        
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR:%s, no buffer for UUID:%s\n", __FUNCTION__, pt_spp_data->ac_uuid));
        return PBR_FAIL;
    }

    // free buffer size
    ui4_act_write_size = SPP_DATA_BUFFER_SIZE - ((pt_buf->ui4_wr + SPP_DATA_BUFFER_SIZE - 
                                                 pt_buf->ui4_rd) % SPP_DATA_BUFFER_SIZE) - 1;

    // Check if the buffer is enough.
    if(ui4_act_write_size >= pt_spp_data->ui4_data_len)
    {
        ui4_act_write_size = pt_spp_data->ui4_data_len;
    }
    else  // no enough buffer
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR:%s, no enough buf, %d byte spp data is dropped\n", __FUNCTION__,
            pt_spp_data->ui4_data_len - ui4_act_write_size));
    }

    // copy spp data into buffer
    if((pt_buf->ui4_wr + ui4_act_write_size) <= SPP_DATA_BUFFER_SIZE)
    {
        c_memcpy(pt_buf->aui1_bufBase + pt_buf->ui4_wr, 
                 pt_spp_data->aui1_data, 
                 ui4_act_write_size);
    }
    else
    {
        ui4_temp = SPP_DATA_BUFFER_SIZE - pt_buf->ui4_wr;
        
        c_memcpy(pt_buf->aui1_bufBase + pt_buf->ui4_wr, 
                 pt_spp_data->aui1_data, 
                 ui4_temp);
        c_memcpy(pt_buf->aui1_bufBase, 
                 pt_spp_data->aui1_data + ui4_temp, 
                 ui4_act_write_size - ui4_temp);
    }
    pt_buf->ui4_wr = (pt_buf->ui4_wr + ui4_act_write_size) % SPP_DATA_BUFFER_SIZE;

    // data size in the buffer
    ui4_temp = (pt_buf->ui4_wr + SPP_DATA_BUFFER_SIZE - pt_buf->ui4_rd) 
                % SPP_DATA_BUFFER_SIZE;
    
    bt_spp_data_buf_unlock();
    
    // print the data for debug
    if(fg_enable_spp_data_log)
    {
        bt_spp_show_spp_data_buf();
    }
    
    // notify X2 the event of receiving SPP data when SPP data exceed threshold.
    if(ui4_temp >= ui4_spp_data_threshold_size)
    {
        _bt_spp_notify_receiving_data_to_x2(pt_spp_data->ac_uuid);
    }
    _bt_panasonic_spp_receive_data_proc(pt_spp_data);
    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_spp_event_nfy_proc
  *
  * Description  - process SPP event which is from BTM.
  *
  * Inputs         - bt_spp_event_type: 
  *                      pv_data: 
  *---------------------------------------------------------------------------*/
VOID bt_spp_event_nfy_proc(BT_SPP_EVENT bt_spp_event_type, VOID *pv_data)
{
    if(NULL == pv_data)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return ;
    }

    switch (bt_spp_event_type)
    {
        case BT_SPP_RECV_DATA:   // SPP event of receiving data
        {
            _bt_spp_receive_data_proc((BT_SPP_RECEIVED_DATA *)pv_data);
            break;
        }
        case BT_SPP_CONNECT:     // SPP connect successful
        {
            _bt_spp_connect_succeed_proc((CHAR *)pv_data);
            break;
        }
        case BT_SPP_CONNECT_FAIL:   // SPP connect fail
        {
            _bt_spp_connect_fail_proc((CHAR *)pv_data);
            break;
        }
        case BT_SPP_DISCONNECT:   // SPP disconnect successful
        {
            _bt_spp_disconnect_success_nfy_proc((CHAR *)pv_data);
            break;
        }
        case BT_SPP_DISCONNECT_FAIL:   // SPP disconnect fail
        {
            _bt_spp_disconnect_fail_nfy_proc((CHAR *)pv_data);
            break;
        }
        default:
        {
            break;
        }
    }
}

INT32 bt_spp_sema_create(VOID)
{
    INT32 i4_ret = OSR_OK;
    
    if (NULL_HANDLE == h_sema_spp_data_buf)
    {
        i4_ret = c_sema_create(&h_sema_spp_data_buf,
                               X_SEMA_TYPE_BINARY,
                               X_SEMA_STATE_UNLOCK);
        if(i4_ret != OSR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: create spp buf sema fail, %d\n", i4_ret));
        }
    }

    return i4_ret;
}

VOID bt_spp_data_buf_lock(VOID)
{
    INT32 i4_ret = OSR_OK;

    if (NULL_HANDLE == h_sema_spp_data_buf)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create spp buf sema\n"));
        return;
    }

    i4_ret = c_sema_lock(h_sema_spp_data_buf, X_SEMA_OPTION_WAIT);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: lock spp buf sema fail, %d\n", i4_ret));
    }
}

VOID bt_spp_data_buf_unlock(VOID)
{
    INT32 i4_ret = 0;

    if (NULL_HANDLE == h_sema_spp_data_buf)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create spp buf sema\n"));
        return;
    }

    i4_ret = c_sema_unlock(h_sema_spp_data_buf);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: unlock spp buf sema fail, %d\n", i4_ret));
    }
}

/**---------------------------------------------------------------------------
  * Name          - bt_spp_show_spp_data_buf
  *
  * Description  - Show the data in SPP data buffer
  *---------------------------------------------------------------------------*/
VOID bt_spp_show_spp_data_buf(VOID)
{
    UINT32 ui4_idx = 0;
    UINT32 ui4_data_size = 0;
    BT_SPP_DATA_BUFFER *pt_buf = NULL;

    bt_spp_data_buf_lock();
    
    BT_APP_LOG_DEFAULT(("\n<BT_APP> ------The data in SPP data buf--------------\n"));
    pt_buf = pt_spp_data_buffer_h;
    if(NULL == pt_buf)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ----- No SPP connection -----\n"));
    }
    while(pt_buf != NULL)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> UUID: %s\n", pt_buf->ac_uuid));

        // data size in the buffer
        ui4_data_size = (pt_buf->ui4_wr + SPP_DATA_BUFFER_SIZE - pt_buf->ui4_rd) 
                         % SPP_DATA_BUFFER_SIZE;
        
        BT_APP_LOG_DEFAULT(("<BT_APP> Data len: %d\n", ui4_data_size));

        ui4_idx = pt_buf->ui4_rd;
        ui4_data_size = 0;
        while(ui4_idx != pt_buf->ui4_wr)
        {
            ui4_data_size ++;
            BT_APP_LOG_DEFAULT(("%c", pt_buf->aui1_bufBase[ui4_idx]));
            ui4_idx = (ui4_idx + 1) % SPP_DATA_BUFFER_SIZE;
        }
        BT_APP_LOG_DEFAULT(("\n<BT_APP> ------End-----------------------------------\n"));
        
        pt_buf = pt_buf->next;
    }
    
    bt_spp_data_buf_unlock();
}

/**---------------------------------------------------------------------------
  * Name          - bt_spp_enable_data_log
  *
  * Description  - enable or disable SPP data log
  *
  * Inputs         - f_enable_data_log: specify whether SPP data is shown in the log.
  *
  * Returns       - 
  *---------------------------------------------------------------------------*/
VOID bt_spp_enable_data_log(BOOL f_enable_data_log)
{
   fg_enable_spp_data_log = f_enable_data_log;
}

/*! \brief To get FW version like "1.0.0"
 * 
 * \arg[out] version, Special firmware version for apple certification
 *
 * \return true : success, false : error
 *
 */
BOOL bluetooth_iplib_get_fw_version(char* version)
{
    if (NULL != version)
    {
        c_strncpy(version, iplib_info[IPLIB_FW_VERSION].ac_iplibinfo, MAX_IPLIB_INFO_LENGTH - 1);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*! \brief To get HW version like "1.0.0"
 * 
 * \arg[out] version, Special hardware version for apple certification
 *
 * \return true : success, false : error
 *
 */
BOOL bluetooth_iplib_get_hw_version(char* version)
{
    if (NULL != version)
    {
        c_strncpy(version, iplib_info[IPLIB_HW_VERSION].ac_iplibinfo, MAX_IPLIB_INFO_LENGTH - 1);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*! \brief To get accessary name like "_AUDIO"
 * 
 * \arg[out] name, accessary name
 *
 * \return true : success, false : error
 *
 */
BOOL bluetooth_iplib_get_name(char* name)
{
    if (NULL != name)
    {
        c_strncpy(name, iplib_info[IPLIB_ACCESSARY_NAME].ac_iplibinfo, MAX_IPLIB_INFO_LENGTH - 1);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*! \brief To get model number like "STR-DN1060"
 * 
 * \arg[out] model, model number
 *
 * \return true : success, false : error
 *
 */
BOOL bluetooth_iplib_get_model(char* model)
{
    if (NULL == model)
    {        
        BT_APP_LOG_ERR(("<BT_APP>%s, Invalid input argument\n",__FUNCTION__));
        return FALSE;
    }

    return TRUE;
}


static int app_spp_send_data(unsigned char *buf, int size, int dummy)
{
  int result;
  //BT_HDR *p_msg;
  //int status;
  CHAR addr[18] = {};
  BT_A2DP_ROLE local_role;
  BOOL status;
  result = 0;

 // status = app_spp_sendbuf(connection, p_msg);
 bt_app_get_cur_connect_status(addr, &local_role, &status);
 a_mtkapi_spp_send_data(addr,ac_connect_target_uuid,(CHAR *)buf,size);

  return result;
}

/*****************************************/
unsigned char checksum(unsigned char *buf, int size)
{
  unsigned char csum=0;
  int i;

  for(i = 0; i < size; i++)
    {
      csum += buf[i];
    }
  csum = (~(csum & 0xff) + 1) & 0xff;
  return csum;
}


/*******************************************/
int app_spp_send_mute(void)
{
    unsigned char buf[10];
    int result;

    buf[0] = 0xaa;
    buf[1] = 0x07; //ID(Remocon)
    buf[2] = 0x00; //Length
    buf[3] = 0x02; //Length
    buf[4] = 0x00; //Data
    buf[5] = 0x32; //Data
    buf[6] = checksum(buf,6);
    result = app_spp_send_data(buf, 7, 0);

    return result;
}

/*******************************************/
int app_spp_send_vol_down(void)
{
    unsigned char buf[10];
    int result;

    buf[0] = 0xaa;
    buf[1] = 0x07; //ID(Remocon)
    buf[2] = 0x00; //Length
    buf[3] = 0x02; //Length
    buf[4] = 0x00; //Data
    buf[5] = 0x21; //Data
    buf[6] = checksum(buf,6);
    result = app_spp_send_data(buf, 7, 0);

    return result;
}

/*******************************************/
int app_spp_send_vol_up(void)
{
    unsigned char buf[10];
    int result;

    buf[0] = 0xaa;
    buf[1] = 0x07; //ID(Remocon)
    buf[2] = 0x00; //Length
    buf[3] = 0x02; //Length
    buf[4] = 0x00; //Data
    buf[5] = 0x20; //Data
    buf[6] = checksum(buf,6);
    result = app_spp_send_data(buf, 7, 0);

    return result;
}

/*******************************************/
int app_spp_send_force_pairing(void)
{
    unsigned char buf[10];
    int result;

    buf[0] = 0xaa;
    buf[1] = 0x0c; //ID(Remocon)
    buf[2] = 0x00; //Length
    buf[3] = 0x00; //Length
    buf[4] = 0x4a; //checksum

    result = app_spp_send_data(buf, 5, 0);

    return result;
}

/*******************************************/
int app_spp_send_get_pairing_status(void)
{
    unsigned char buf[10];
    int result;

    buf[0] = 0xaa;
    buf[1] = 0x0e; //ID(DeviceStatus)
    buf[2] = 0x00; //Length
    buf[3] = 0x00; //Length
    buf[4] = 0x48; //checksum
    result = app_spp_send_data(buf, 5, 0);

    return result;
}
/*******************************************/
int app_spp_send_get_supported_api(void)
{
    unsigned char buf[10];
    int result;

    buf[0] = 0xaa;
    buf[1] = 0x00; //ID(GetSupportedApi)
    buf[2] = 0x00; //Length
    buf[3] = 0x01; //Length
    buf[4] = 0x01; //Data(ProtocolVersion)
    buf[5] = checksum(buf,5);
    result = app_spp_send_data(buf, 6, 0);

    return result;
}
/*******************************************/
int app_spp_send_set_panasonic_tv_buffering(void)
{
    unsigned char buf[10];
    int result;

    buf[0] = 0xaa;
    buf[1] = 0x25; //ID(SetPanasonicTVBuffering)
    buf[2] = 0x00; //Length
    buf[3] = 0x03; //Length
    buf[4] = 0x01; //Data(BufferControlEnable)
    buf[5] = 0x00; //Data(BufferSize)
    buf[6] = 0x64; //Data(BufferSize)
    buf[7] = checksum(buf,7);
    result = app_spp_send_data(buf, 8, 0);

    return result;
}

/*******************************************/
int app_spp_check_ret_supported_api(UINT8 *buf, UINT32 len)
{
    UINT8 sum;

    //check size
    if (len != 21)
      {
	return 0; 
      }
    //check check_sum
    //check data
    sum = checksum(buf,20);
    if (sum != buf[20])
      {
	return 0; 
      }

    if ( (buf[0] == 0xaa) &&   // Start
	 (buf[1] == 0x80) &&   // Command ID
	 (buf[2] == 0x00) &&   // Length
	 (buf[3] == 0x10) &&     // Length
	 ((buf[4] & 0x01) == 0x01) &&   // API 0 (01)
	 ((buf[5] & 0x0a) == 0x0a) )    // API 1 (0a)
      {
	return 1;
      }
    return 0;
}

/*******************************************/
int app_spp_check_get_pairing_status_data(UINT8 *buf, UINT32 len)
{
    UINT8 sum;

    //check size
    if (len != 6)
      {
	return 0; 
      }
    //check check_sum
    //check data
    sum = checksum(buf,5);
    if (sum != buf[5])
      {
	return 0; 
      }

    if ( (buf[0] == 0xaa) &&   // Start
	 (buf[1] == 0x8e) &&   // Command ID
	 (buf[2] == 0x00) &&   // Length
	 (buf[3] == 0x01) &&   // Length
	 (buf[4] == 0x01) )    // Pairing Mode
      {
	return 1;
      }
    return 2;
}

/*******************************************/
int app_spp_check_ret_panasonic_tv_buffering(UINT8 *buf, UINT32 len)
{
  UINT8 sum;
  
  //check size
  if (len != 6)
    {
      return 0; 
    }
  //check check_sum
  //check data
  sum = checksum(buf,5);
  if (sum != buf[5])
    {
      return 0; 
    }
  
  if ( (buf[0] == 0xaa) &&   // Start
       (buf[1] == 0xa5) &&   // Command ID
       (buf[2] == 0x00) &&   // Length
       (buf[3] == 0x01) )   // Length
    {
      if (buf[4] == 0x00)     // Result
	{
	  return 1;
	}
      else
	{
	  return 2;
	}
    }
  return 0;
}

/*******************************************/
int app_spp_check_ret_supported_api_buffering(UINT8 *buf, UINT32 len)
{
    UINT8 sum;

    //check size
    if (len != 21)
      {
    	return 0; 
      }
    //check check_sum
    //check data
    sum = checksum(buf,20);
    if (sum != buf[20])
      {
	return 0; 
      }

    if ( (buf[0] == 0xaa) &&   // Start
	 (buf[1] == 0x80) &&   // Command ID
	 (buf[2] == 0x00) &&   // Length
	 (buf[3] == 0x10) &&     // Length
	 ((buf[8] & 0x04) == 0x04) )   // API 4 (04)
      {
    	return 1;
      }
    return 0;
}


#endif


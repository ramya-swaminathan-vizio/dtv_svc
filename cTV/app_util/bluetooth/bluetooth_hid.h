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
 * $RCSfile: bluetooth_hid.h,v $
 * $Revision: #1 $
 * $Date: 2015/10/17 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *      This file is the internal header file for bluetooth hid.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#ifndef _BLUETOOTH_HID_H_
#define _BLUETOOTH_HID_H_

//#include "u_bluetooth.h"
#include "u_bt_mw_hidh.h"


#define MAX_HID_NUM 4

typedef struct _BT_HID_INFO
{
    UINT8   ccState;                                      /* Connextion State 0:registered 1:connected*/
    CHAR    bdAddr[MAX_BDADDR_LEN];   /* Bluetooth Address */
    UINT32  device_type;
}BT_HID_INFO_T;

typedef struct _BT_TARGET_HID_LIST
{
    UINT32                 num;
    BT_HID_INFO_T  hid_list[MAX_HID_NUM];
}BT_TARGET_HID_LIST;

typedef enum _BT_HID_OPERATION_TYPE
{
    BT_HID_OPERATION_TURN_OFF = 0,
    BT_HID_OPERATION_REMOVE,
    BT_HID_OPERATION_REMOVE_ALL
} BT_HID_OPERATION_TYPE_E;

typedef enum _BT_HID_CONNECT_STATE
{
    BT_HID_CONN_STATE_PAIRED = 0,
//    BT_HID_CONN_STATE_SECOND,
    BT_HID_CONN_STATE_CONNECTED
} BT_HID_CONNECT_STATE_E;

typedef enum _BT_TEST_MODE_FUNCTION
{
    BT_TEST_MODE_CLASSIC = 0,
    BT_TEST_MODE_LE
}BT_TEST_MODE_FUNCTION_E;

typedef enum _BT_TEST_MODE_TX_RX
{
    BT_TEST_MODE_TX = 0,
    BT_TEST_MODE_RX,
    BT_TEST_MODE_INQUIRY,
}BT_TEST_MODE_TX_RX_E;

typedef enum _BT_TEST_MODE_MODULATION
{
    BT_TEST_MODE_WAVE = 0,
    BT_TEST_MODE_FIXED,
    BT_TEST_MODE_HOPPING
}BT_TEST_MODE_MODULATION_E;

typedef enum _BT_TEST_MODE_FREQUENCY
{
    BT_TEST_MODE_CH0 = 0,
    BT_TEST_MODE_CH19,
    BT_TEST_MODE_CH39,
    BT_TEST_MODE_CH78
}BT_TEST_MODE_FREQUENCY_E;

typedef enum _BT_TEST_MODE_PACKET_TYPE
{
    BT_TEST_MODE_DM1 = 0,
    BT_TEST_MODE_DM3,
    BT_TEST_MODE_DM5,
    BT_TEST_MODE_DH1,
    BT_TEST_MODE_DH3,
    BT_TEST_MODE_DH5,
    BT_TEST_MODE_2DH1,
    BT_TEST_MODE_2DH3,
    BT_TEST_MODE_2DH5,
    BT_TEST_MODE_3DH1,
    BT_TEST_MODE_3DH3,
    BT_TEST_MODE_3DH5
}BT_TEST_MODE_PACKET_TYPE_E;

typedef struct _BT_TEST_MODE_COMMAND
{
    BOOL                                                    reset;
    BT_TEST_MODE_FUNCTION_E         function;
    BT_TEST_MODE_TX_RX_E                mode;
    BT_TEST_MODE_MODULATION_E    modulation;
    BT_TEST_MODE_FREQUENCY_E      frequency;
    BT_TEST_MODE_PACKET_TYPE_E   packet;
    BOOL                                                    test_start;  //start:TRUE  stop:FALSE
}BT_TEST_MODE_COMMAND_T;

extern VOID bluetooth_test_mode_start(BT_TEST_MODE_COMMAND_T *command);


extern VOID bt_app_hid_event_proc(BT_HIDH_CBK_STRUCT *fg_bt_hid_struct_data);
extern VOID bluetooth_hid_wireless_controller_operation(CHAR *hid_addr, BT_HID_OPERATION_TYPE_E event);
extern INT32 bluetooth_hid_register_start();
extern INT32 bluetooth_hid_get_wireless_controller_list(BT_TARGET_HID_LIST *list);
extern VOID bluetooth_hid_wireless_controller_operation(CHAR *hid_addr, BT_HID_OPERATION_TYPE_E event);
extern INT32 bt_app_hid_disconnect_all();
extern INT32 bt_app_stop_scan_hid();
extern INT32 bt_app_on_off_hid_reconnect(void);


#if CONFIG_APP_SUPPORT_BX_BT
extern VOID bt_app_notify_hid_connection_battery_low_to_x2(uint8_t controllerID);
#endif
#endif

#endif


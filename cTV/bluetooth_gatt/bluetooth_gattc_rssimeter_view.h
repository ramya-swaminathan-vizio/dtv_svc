/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
/*-----------------------------------------------------------------------------
 * $RCSfile: bluetooth_gattc_proc.c $
 * $Revision:
 * $Date:
 * $Author:
 * $CCRevision: $
 * $SWAuthor: TOOL $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/


#ifdef APP_BLUETOOTH_SUPPORT
 /*-----------------------------------------------------------------------------
					 include files
 -----------------------------------------------------------------------------*/
#ifndef __BLUETOOTH_GATTC_RSSI_METER_VIEW_H
#define __BLUETOOTH_GATTC_RSSI_METER_VIEW_H

#include "res/app_util/config/acfg_custom.h"

#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN 127
#endif

#define         GATT_RSSI_STATUS_LEN        (16)
#define         GATT_RSSI_NAME_LEN          MAX_NAME_LEN

typedef enum
{
    E_RSSI_WHITE,
    E_RSSI_RED,
    E_RSSI_GREEN,
    E_RSSI_YELLOW,
    E_RSSI_END
}E_RSSI_METER_STATUS;

typedef struct _T_RSSI_NOTIFY_MSG
{
    E_RSSI_METER_STATUS e_status;
    INT32               i4_rssi;
    INT32               i4_min_consecutive;
    INT32               i4_min_rssi_threshold;
    INT32               i4_max_rssi_threshold;
    CHAR                s_name[GATT_RSSI_NAME_LEN+1];
    INT32               i4_consecutive;
    INT32               i4_countdown;
    CHAR                c_mac_addr[MAC_ADDRESS_LENGTH_LEN + 1];
    BOOL                b_signal_meter;
}T_RSSI_NOTIFY_MSG;

typedef struct _T_RSSI_METER
{
    CHAR            s_status[GATT_RSSI_STATUS_LEN+1];
    INT32           i4_rssi;
    INT32           i4_min_rssi_threshold;
    INT32           i4_max_rssi_threshold;
    INT32           i4_consecutive;
    INT32           i4_contdown;
    INT32           i4_pin_count;
    INT32           i4_best_rssi;
    INT32           i4_worst_rssi;
    INT32           i4_average_rssi;
    INT32           i4_pings_per_min;
    CHAR            s_name[GATT_RSSI_NAME_LEN+1];
}T_RSSI_METER;


extern INT32 a_bluetooth_gattc_rssimeter_view_init(VOID);
extern INT32 a_bluetooth_gattc_rssi_meter_show(T_RSSI_METER *pt_rssi_meter);
extern INT32 a_bluetooth_gattc_rssi_meter_hide(VOID);
extern INT32 a_bluetooth_gattc_rssi_meter_info_refresh(T_RSSI_NOTIFY_MSG *pt_rssi_nfy_msg);
extern INT32 a_bluetooth_gattc_rssi_meter_dialog_enable(BOOL b_enable);
#endif //__BLUETOOTH_GATTC_RSSI_METER_VIEW_H
#endif


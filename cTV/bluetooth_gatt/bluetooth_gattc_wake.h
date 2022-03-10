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

#ifdef APP_BLUETOOTH_SUPPORT
#ifndef _BLUETOOTH_GATT_WAKE_H
#define _BLUETOOTH_GATT_WAKE_H

#include "amb/a_amb.h"
#include "u_bt_mw_gattc.h"

#define GATT_WAKE_TAG               "<BT_GATT><WAKE> "
#define DBG_WOBLE_INFO(_stmt)   do{DBG_API((GATT_WAKE_TAG));DBG_API(_stmt);}while(0)
#define DBG_WOBLE_API(_stmt)    do{DBG_ERROR((GATT_WAKE_TAG));DBG_ERROR(_stmt);}while(0)
#define DBG_WOBLE_ERR(_stmt)    do{DBG_ERROR((GATT_WAKE_TAG));DBG_ERROR(("F:%s,L:%d-->",__FUNCTION__,__LINE__));DBG_ERROR(_stmt);}while(0)
#define DBG_WOBLE_PRINT(_stmt)  do{DBG_ERROR(_stmt);}while(0)
#define DBG_WOBLE_DATA(_stmt)   do{DBG_API(_stmt);}while(0)

#define WOBLE_CHK_FAIL_RET(_func, _ret)   \
do{if (_ret != 0){DBG_WOBLE_ERR(("Err:"#_func" return err: ret=%d.\r\n", _ret));return _ret;}}while(0)
#define WOBLE_CHK_FAIL(_func, _ret)    \
do{if (_ret != 0){DBG_WOBLE_ERR(("Err:"#_func" return err: ret=%d.\r\n", _ret));}}while(0)
//------------------------------------------------------------------------------

#define SF_MAX_SIZE                 64      //max size for scan filter
#define SF_FILT_DATA_SIZE           20      //max size for filt data

//high rssi value
#define SF_MAX_RSSI_DEFAULT         -127
#define SF_MAX_RSSI_NO_PAIRED       -127//-56
//feature selection
#define SF_FEAT_SELN_DEV_NAME       0x0010  //for dev name
#define SF_FEAT_SELN_MAN_DATA       0x0020  //for manufacturer data
#define SF_FEAT_SELN_UUID           0x0004  //for UUID
//logic type
#define SF_LOGIC_TYPE_AND           0x01
#define SF_LOGIC_TYPE_OR            0x00
//filter type
#define SF_FILT_TYPE_UUID           2  //for UUID
#define SF_FILT_TYPE_DEV_NAME       4  //for dev name
#define SF_FILT_TYPE_MAN_DATA       5  //for manufacturer data
//------------------------------------------------------------------------------

typedef enum{
    WAKE_SF_ACT_ADD = 0,    //add
    WAKE_SF_ACT_DEL = 1,    //delete
    WAKE_SF_ACT_CLR = 2,    //clear
}WAKE_SF_ACT_TYPE_E;

//scan filter type for wake up on BLE  module
typedef enum {
    WAKE_SF_TYPE_NO_PAIRED_ANDROID,     //no paired for android
    WAKE_SF_TYPE_NO_PAIRED_IOS,         //no paired for IOS
    WAKE_SF_TYPE_PAIRED_ANDROID_08X,    //paired for android protocol 0.8.x
    WAKE_SF_TYPE_PAIRED_ANDROID_07X,    //paired for android protocol 0.7.x
    WAKE_SF_TYPE_PAIRED_IOS,            //paired for IOS
    WAKE_SF_TYPE_DIRECTED_PAIRING,      //directed pairing
    WAKE_SF_TYPE_DEV_NAME,              //device name, fot test

    WAKE_SF_TYPE_MAX
}WAKE_SCAN_FILTER_TYPE_E;

typedef INT32 (*PFN_SCAN_FILTER_CFG_FUNC)(WAKE_SF_ACT_TYPE_E e_act,
                                        WAKE_SCAN_FILTER_TYPE_E e_type,
                                        UINT32 ui4_index,
                                        UINT8 ui1_target_id,
                                        CHAR* pc_data);
//scan filter config
typedef struct{
    WAKE_SCAN_FILTER_TYPE_E e_type;     //filter type
    PFN_SCAN_FILTER_CFG_FUNC pf_sf_cfg; //filter setup  proc
}WAKE_SCAN_FILTER_CFG_T;


//filter info
typedef struct{
    CHAR	ac_filt_data[SF_FILT_DATA_SIZE+1];            //filt data
    UINT8	ui1_id;                                     //target id
    WAKE_SCAN_FILTER_TYPE_E e_type;                     //filter type
}WAKE_SCAN_FILTER_INFO_T;

typedef struct{
    UINT32 ui4_sf_cnt;                                  //scan filter counter
    WAKE_SCAN_FILTER_INFO_T at_filt_info[SF_MAX_SIZE];//scan filter info
}WAKE_SCAN_FILTER_T;

/****************************************function declarations******************************************/
extern INT32 bluetooth_gatt_scan_filter_init(VOID);
extern INT32 bluetooth_gatt_wake_on_ble_enable(BOOL b_enable);
extern INT32 bluetooth_gatt_del_scan_filter(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data);
extern INT32 bluetooth_gatt_add_scan_filter(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data);
extern INT32 bluetooth_gatt_modify_scan_filter(UINT8 ui1_target_id,
                                                CHAR* pc_data);
extern INT32 bluetooth_gatt_del_scan_filter_data_reverse(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data);
extern INT32 bluetooth_gatt_add_scan_filter_data_reverse(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data);
extern INT32 bluetooth_gatt_modify_scan_filter_data_reverse(UINT8 ui1_target_id,
                                                CHAR* pc_data,
                                                BOOL is_ios_dev);
extern INT32 bluetooth_gatt_show_scan_filter(VOID);

extern VOID bt_gatt_scan_filter_param_cb(BT_GATTC_SCAN_FILTER_PARAM_T *pt_scan_filter_param,VOID* tag);
extern VOID bt_gatt_scan_filter_status_cb(BT_GATTC_SCAN_FILTER_STATUS_T *pt_scan_filter_status,VOID* tag);
extern VOID bt_gatt_scan_filter_cfg_cb(BT_GATTC_SCAN_FILTER_CFG_T *pt_scan_filter_cfg,VOID* tag);
extern BOOL bluetooth_gatt_get_wake_on_ble_enable(VOID);

#endif /* _BLUETOOTH_GATT_WAKE_H */

#endif
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
                     include files
 -----------------------------------------------------------------------------*/
 
#ifdef APP_BLUETOOTH_SUPPORT
#include <stdio.h>
#include <string.h>
#include "res/app_util/config/acfg_custom.h"
#include "bgm/mtk_comp/bgm_cast_c4tv/a_bgm_cast_c4tv.h"

#include <mtk_bt_service_gattc_wrapper.h>

#include "bluetooth_gattc.h"
#include "bluetooth_gattc_wake.h"

#define COMPANY_SCAN_FILTER_IDX                     (0)
#define COMPANY_SCAN_FILTER_IDX2                    (1)
#define COMPANY_SCAN_FILTER_IDX3                    (2)

#define GATTC_IOS_SERVICE_UUID                      "69A3DBA"
#define GATTC_DIRECT_PAIRING                        "DBB"
//------------------------------------------------------------------------------
static INT32 _wake_sf_cfg_for_no_paired_android(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data);
static INT32 _wake_sf_cfg_for_paired_android_07x(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_mac);
static INT32 _wake_sf_cfg_for_paired_android_08x(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_mac);
static INT32 _wake_sf_cfg_for_paired_ios(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_mac);
static INT32 _wake_sf_cfg_for_dev_name(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data);
//------------------------------------------------------------------------------
static BOOL b_wake_sf_init = FALSE;
static BOOL b_sf_woble = FALSE;                     //wake enable flag
static HANDLE_T h_sf_sema = NULL_HANDLE;
static WAKE_SCAN_FILTER_T* pt_scan_filter = NULL;

static const WAKE_SCAN_FILTER_CFG_T at_wake_sf_cfg[] = {
    {WAKE_SF_TYPE_NO_PAIRED_ANDROID,    _wake_sf_cfg_for_no_paired_android},    //no paired for android
    {WAKE_SF_TYPE_PAIRED_ANDROID_08X,   _wake_sf_cfg_for_paired_android_08x},   //paired for android protocol 0.8.x
    {WAKE_SF_TYPE_PAIRED_ANDROID_07X,   _wake_sf_cfg_for_paired_android_07x},   //paired for android protocol 0.7.x
    {WAKE_SF_TYPE_PAIRED_IOS,           _wake_sf_cfg_for_paired_ios},           //paired for IOS

    {WAKE_SF_TYPE_DEV_NAME,             _wake_sf_cfg_for_dev_name},             //dev name
    {WAKE_SF_TYPE_MAX,                  NULL}
};

static INT32 i4_sf_company_id = 0x0058;
static INT32 i4_sf_company_id_mask = 0xFFFF;
//data mask without company id
//len(1byte)+mask
static const CHAR ac_sf_data_mask[WAKE_SF_TYPE_MAX][16+1] = {
    { 5,0xFF,0xFF,0x00,0x00,0x40},                                                          //no paired for android
    {16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xFF},   //no paired for IOS
    {11,0xFF,0xFF,0x01,0xF8,0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},                            //paired for android protocol 0.8.x
    {11,0xFF,0xFF,0x00,0xF0,0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},                            //paired for android protocol 0.7.x
    {16,0xF8,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xFF},   //paired for IOS
    {16,0xF8,0x01,0xFF,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xFF},   //directed pairing

    {SF_FILT_DATA_SIZE-1,0xFF},                                                           //dev name
};

//android default filt data without company id
static const CHAR ac_android_sf_default_filt_data[] = {
0xC1,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//ios default filt data, uuid
static const UCHAR ai_ios_sf_default_filt_data[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5D,0x4B,0xC1,0xCB,0xA5,0xDB,0xA3,0x69};
//static const UCHAR ac_ios_sf_default_filt_data[] = "00000000000000005D4BC1CBA5DBA369";
static const UCHAR ac_ios_sf_default_filt_data[] = "69A3DBA5CBC14B5D0000000000000000";

#define __SET_FILTER_PARAM(_scan_filt_param,\
                           _client_if,\
                           _action,\
                           _filt_index,\
                           _feat_seln,\
                           _list_logic_type,\
                           _filt_logic_type,\
                           _rssi_high_thres,\
                           _rssi_low_thres,\
                           _dely_mode,\
                           _found_timeout,\
                           _lost_timeout,\
                           _found_timeout_cnt) \
{\
    (_scan_filt_param).client_if = _client_if;\
    (_scan_filt_param).action = _action;\
    (_scan_filt_param).filt_index = _filt_index;\
    (_scan_filt_param).feat_seln = _feat_seln;\
    (_scan_filt_param).list_logic_type = _list_logic_type;\
    (_scan_filt_param).filt_logic_type = _filt_logic_type;\
    (_scan_filt_param).rssi_high_thres = _rssi_high_thres;\
    (_scan_filt_param).rssi_low_thres = _rssi_low_thres;\
    (_scan_filt_param).dely_mode = _dely_mode;\
    (_scan_filt_param).found_timeout = _found_timeout;\
    (_scan_filt_param).lost_timeout = _lost_timeout;\
    (_scan_filt_param).found_timeout_cnt = _found_timeout_cnt;\
}
//------------------------------------------------------------------------------
static INT32 _mac_addr_str2bytes(CHAR *in, UINT8 *out)
{
    unsigned int  ui4_i, aui4_tmp[6];

    for(ui4_i = 0; ui4_i < 6; ui4_i++)
    {
        sscanf(&in[2 * ui4_i], "%2x", &aui4_tmp[ui4_i]);
        out[ui4_i] = aui4_tmp[ui4_i];
    }

    return 0;
}

static INT32 _mac_addr_reverse(CHAR* pc_data)
{
    UINT32 ui4_i, ui4_len = c_strlen(pc_data);
    CHAR c_h4b, c_l4b;

    for(ui4_i = 0; ui4_i < (ui4_len >> 2); ui4_i++)
    {
        c_h4b = pc_data[(ui4_i << 1)];
        c_l4b = pc_data[(ui4_i << 1) + 1];

        pc_data[(ui4_i << 1)] = pc_data[ui4_len - (ui4_i << 1) - 2];
        pc_data[(ui4_i << 1) + 1] = pc_data[ui4_len - (ui4_i << 1) - 1];

        pc_data[ui4_len - (ui4_i << 1) - 2] = c_h4b;
        pc_data[ui4_len - (ui4_i << 1) - 1] = c_l4b;
    }

    return 0;
}

static VOID _data_print(CHAR* pc_data, INT32 ui4_len)
{
    UINT32 ui4_i;
    for (ui4_i = 0; ui4_i < ui4_len; ui4_i++)
    {
        DBG_LOG_PRINT(("%02X ", (UINT8)pc_data[ui4_i]));
    }
    DBG_LOG_PRINT(("\n"));
}

static BOOL _is_skip_filter_idx(INT32 i4_filter_idx)
{
    return (COMPANY_SCAN_FILTER_IDX == i4_filter_idx
            || COMPANY_SCAN_FILTER_IDX2 == i4_filter_idx
            || COMPANY_SCAN_FILTER_IDX3 == i4_filter_idx);
}

static VOID _hex2str(UINT8 *phex_buf, CHAR *ps_str, UINT32 ui4_num)
{
    UINT32  i = ui4_num;
    UINT32  j = 0;
    UINT8   c = 0x00;
    CHAR    c_hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    if (NULL == phex_buf
        || NULL == ps_str
        || 0 == ui4_num)
    {
        DBG_ERROR(("%s() Invalid agr!\n"));
        return;
    }
    while (i > 0)
    {
        c = phex_buf[i-1];
        ps_str[j++] = c_hex[((c&0xF0)>>4)];
        ps_str[j++] = c_hex[c];

        i--;
    }
    return;
}
//------------------------------------------------------------------------------
VOID bt_gatt_scan_filter_param_cb(BT_GATTC_SCAN_FILTER_PARAM_T *pt_scan_filter_param,VOID* tag)
{
    DBG_WOBLE_API(("scan filter param setup free space=%d.\r\n", pt_scan_filter_param->avbl_space));
    if (0 == pt_scan_filter_param->avbl_space)
    {
        DBG_WOBLE_ERR(("scan filter param space is full!\r\n"));
    }
}
VOID bt_gatt_scan_filter_status_cb(BT_GATTC_SCAN_FILTER_STATUS_T *pt_scan_filter_status,VOID* tag)
{
    if (pt_scan_filter_status->enable == 1)
    {
        DBG_WOBLE_API(("enable scan filter, start scan.\r\n"));
        //bluetooth_gattc_set_scan_parameters(5000, 2000);
        a_mtkapi_bt_gattc_scan();
        c_sema_unlock(h_sf_sema);
    }
}
VOID bt_gatt_scan_filter_cfg_cb(BT_GATTC_SCAN_FILTER_CFG_T *pt_scan_filter_cfg,VOID* tag)
{
    DBG_WOBLE_API(("scan filter cfg free space=%d, feature type=%x.\r\n",
        pt_scan_filter_cfg->avbl_space,
        pt_scan_filter_cfg->filt_type - 1));

    if (0 == pt_scan_filter_cfg->avbl_space)
    {
        DBG_WOBLE_ERR(("scan filter space is full for feature type %x!\r\n",
            pt_scan_filter_cfg->filt_type - 1));// return filt type value is setup type+1
    }
}
//-----------------------scan filter setup proc-------------------------------------
//no paired for android
static INT32 _wake_sf_cfg_for_no_paired_android(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data)
{
    INT32 i4_ret;
    UINT32 ui4_mask_len = ac_sf_data_mask[e_type][0];
    CHAR ac_mask[SF_FILT_DATA_SIZE];
    CHAR ac_filt_data[SF_FILT_DATA_SIZE];

    DBG_WOBLE_API(("filter setup proc - no paired for android, act=%d.\n",e_act));

    c_memset(ac_mask, 0, SF_FILT_DATA_SIZE);
    c_memset(ac_filt_data, 0, SF_FILT_DATA_SIZE);

    //get mask data
    c_memcpy(ac_mask, &ac_sf_data_mask[e_type][1], ui4_mask_len);
    //copy default data and then generate the right filt data
    c_memcpy(ac_filt_data, ac_android_sf_default_filt_data, ui4_mask_len);

    //print data
    DBG_WOBLE_INFO(("mask:"));
    _data_print(ac_mask, ui4_mask_len);
    DBG_WOBLE_INFO(("data:"));
    _data_print(ac_filt_data, ui4_mask_len);

    BT_GATTC_FILT_PARAM_SETUP_T scan_filt_param = {0};

    __SET_FILTER_PARAM(scan_filt_param,
                       bt_gattc_get_client_if(), //client_if
                       e_act,              //action
                       ui4_index,          //filt_index
                       SF_FEAT_SELN_MAN_DATA,//feat_seln
                       SF_LOGIC_TYPE_OR,   //list_logic_type
                       SF_LOGIC_TYPE_OR,   //filt_logic_type
                       SF_MAX_RSSI_NO_PAIRED,//rssi_high_thres
                       0,                  //rssi_low_thres
                       0,                  //dely_mode
                       0,                  //found_timeout
                       0,                  //lost_timeout
                       0);                 //found_timeout_cnt
    i4_ret = a_mtkapi_bt_gattc_scan_filter_param_setup(&scan_filt_param);
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_param_setup,i4_ret);

    i4_ret = a_mtkapi_bt_gattc_scan_filter_add_remove(bt_gattc_get_client_if(), //client_if
                                                    e_act,              //action
                                                    SF_FILT_TYPE_MAN_DATA,//filt_type
                                                    ui4_index,          //filt_index
                                                    i4_sf_company_id,   //company_id
                                                    i4_sf_company_id_mask,//company_id_mask,
                                                    NULL,               //p_uuid,
                                                    NULL,               //p_uuid_mask,
                                                    NULL,               //bd_addr,
                                                    0,                  //addr_type,
                                                    ui4_mask_len,       //data_len,
                                                    ac_filt_data,       //p_data,
                                                    ui4_mask_len,       //mask_len,
                                                    ac_mask);           //p_mask
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_add_remove,i4_ret);

    return 0;
}
//paired for android protocol 0.8.x
static INT32 _wake_sf_cfg_for_paired_android_08x(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_mac)
{
    INT32 i4_ret;
    UINT32 ui4_mask_len = ac_sf_data_mask[e_type][0];
    CHAR ac_mask[SF_FILT_DATA_SIZE];
    CHAR ac_filt_data[SF_FILT_DATA_SIZE];
    UINT8 aui1_mac_hex[6];

    DBG_WOBLE_API(("filter setup proc - paired for android 08x, act=%d.\n",e_act));

    c_memset(ac_mask, 0, SF_FILT_DATA_SIZE);
    c_memset(ac_filt_data, 0, SF_FILT_DATA_SIZE);

    //get mask data
    c_memcpy(ac_mask, &ac_sf_data_mask[e_type][1], ui4_mask_len);
    //copy default data and then generate the right filt data
    c_memcpy(ac_filt_data, ac_android_sf_default_filt_data, ui4_mask_len);
    //target id has 6 bits
    ac_filt_data[ui4_mask_len - 9] = (ui1_target_id >> 5) & 0x01;  //id: 6th-bit
    ac_filt_data[ui4_mask_len - 8] = (ui1_target_id << 3) & 0xF8;  //id: low 5 bits
    ac_filt_data[ui4_mask_len - 7] = 0x02;

    _mac_addr_str2bytes(pc_mac, aui1_mac_hex);        //change MAC str to hex
    c_memcpy(&ac_filt_data[ui4_mask_len - 6], aui1_mac_hex, 6);

    //print data
    DBG_WOBLE_INFO(("mask:"));
    _data_print(ac_mask, ui4_mask_len);
    DBG_WOBLE_INFO(("data:"));
    _data_print(ac_filt_data, ui4_mask_len);

    BT_GATTC_FILT_PARAM_SETUP_T scan_filt_param = {0};

    __SET_FILTER_PARAM(scan_filt_param,
                       bt_gattc_get_client_if(), //client_if
                       e_act,              //action
                       ui4_index,          //filt_index
                       SF_FEAT_SELN_MAN_DATA,//feat_seln
                       SF_LOGIC_TYPE_OR,   //list_logic_type
                       SF_LOGIC_TYPE_OR,   //filt_logic_type
                       SF_MAX_RSSI_DEFAULT,//rssi_high_thres
                       0,                  //rssi_low_thres
                       0,                  //dely_mode
                       0,                  //found_timeout
                       0,                  //lost_timeout
                       0);                 //found_timeout_cnt

    i4_ret = a_mtkapi_bt_gattc_scan_filter_param_setup(&scan_filt_param);
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_param_setup,i4_ret);

    i4_ret = a_mtkapi_bt_gattc_scan_filter_add_remove(bt_gattc_get_client_if(), //client_if
                                                    e_act,              //action
                                                    SF_FILT_TYPE_MAN_DATA,//filt_type
                                                    ui4_index,          //filt_index
                                                    i4_sf_company_id,   //company_id
                                                    i4_sf_company_id_mask,//company_id_mask,
                                                    NULL,               //p_uuid,
                                                    NULL,               //p_uuid_mask,
                                                    NULL,               //bd_addr,
                                                    0,                  //addr_type,
                                                    ui4_mask_len,       //data_len,
                                                    ac_filt_data,       //p_data,
                                                    ui4_mask_len,       //mask_len,
                                                    ac_mask);           //p_mask
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_add_remove,i4_ret);

    return 0;
}
//paired for android protocol 0.7.x
static INT32 _wake_sf_cfg_for_paired_android_07x(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_mac)
{
    INT32 i4_ret;
    UINT32 ui4_mask_len = ac_sf_data_mask[e_type][0];
    CHAR ac_mask[SF_FILT_DATA_SIZE];
    CHAR ac_filt_data[SF_FILT_DATA_SIZE];
    UINT8 aui1_mac_hex[6];

    DBG_WOBLE_API(("filter setup proc - paired for android 07x, act=%d.\n",e_act));

    c_memset(ac_mask, 0, SF_FILT_DATA_SIZE);
    c_memset(ac_filt_data, 0, SF_FILT_DATA_SIZE);

    //get mask data
    c_memcpy(ac_mask, &ac_sf_data_mask[e_type][1], ui4_mask_len);
    //copy default data and then generate the right filt data
    c_memcpy(ac_filt_data, ac_android_sf_default_filt_data, ui4_mask_len);
    //target id has 4 bits
    ac_filt_data[ui4_mask_len - 8] = (ui1_target_id << 4) & 0xF0;  //id
    ac_filt_data[ui4_mask_len - 7] = 0x02;

    _mac_addr_str2bytes(pc_mac, aui1_mac_hex);        //change MAC str to hex
    c_memcpy(&ac_filt_data[ui4_mask_len - 6], aui1_mac_hex, 6);

    //print data
    DBG_WOBLE_INFO(("mask:"));
    _data_print(ac_mask, ui4_mask_len);
    DBG_WOBLE_INFO(("data:"));
    _data_print(ac_filt_data, ui4_mask_len);

    BT_GATTC_FILT_PARAM_SETUP_T scan_filt_param = {0};

    __SET_FILTER_PARAM(scan_filt_param,
                       bt_gattc_get_client_if(), //client_if
                       e_act,              //action
                       ui4_index,          //filt_index
                       SF_FEAT_SELN_MAN_DATA,//feat_seln
                       SF_LOGIC_TYPE_OR,   //list_logic_type
                       SF_LOGIC_TYPE_OR,   //filt_logic_type
                       SF_MAX_RSSI_DEFAULT,//rssi_high_thres
                       0,                  //rssi_low_thres
                       0,                  //dely_mode
                       0,                  //found_timeout
                       0,                  //lost_timeout
                       0);                 //found_timeout_cnt

    i4_ret = a_mtkapi_bt_gattc_scan_filter_param_setup(&scan_filt_param);
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_param_setup,i4_ret);

    i4_ret = a_mtkapi_bt_gattc_scan_filter_add_remove(bt_gattc_get_client_if(), //client_if
                                                    e_act,              //action
                                                    SF_FILT_TYPE_MAN_DATA,//filt_type
                                                    ui4_index,          //filt_index
                                                    i4_sf_company_id,   //company_id
                                                    i4_sf_company_id_mask,//company_id_mask,
                                                    NULL,               //p_uuid,
                                                    NULL,               //p_uuid_mask,
                                                    NULL,               //bd_addr,
                                                    0,                  //addr_type,
                                                    ui4_mask_len,       //data_len,
                                                    ac_filt_data,       //p_data,
                                                    ui4_mask_len,       //mask_len,
                                                    ac_mask);           //p_mask
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_add_remove,i4_ret);

    return 0;
}
//paired for ios
typedef struct {
   uint8_t uu[16];
} bt_uuid_t;

static INT32 _wake_sf_cfg_for_paired_ios(WAKE_SF_ACT_TYPE_E      e_act,
                                              WAKE_SCAN_FILTER_TYPE_E e_type,
                                              UINT32 ui4_index,
                                              UINT8 ui1_target_id,
                                              CHAR* pc_mac)
{
    INT32 i4_ret;
    CHAR s_uuid[32+1] = {0};
    CHAR s_uuid_mask[32+1] = {0};
    UINT32 ui4_mask_len = ac_sf_data_mask[e_type][0];
    bt_uuid_t t_uuid,t_uuid_mask;
    CHAR ac_data_rev_before[SF_FILT_DATA_SIZE];//for reverse data
    UINT8 aui1_mac_hex[6];

    DBG_WOBLE_API(("filter setup proc - paired for ios, act=%d.\n",e_act));

    c_memset(&t_uuid_mask, 0, sizeof(bt_uuid_t));
    c_memset(&t_uuid, 0, sizeof(bt_uuid_t));

    c_memcpy(t_uuid_mask.uu, &ac_sf_data_mask[e_type][1], ui4_mask_len);
    c_memcpy(t_uuid.uu, ai_ios_sf_default_filt_data, ui4_mask_len);
    t_uuid.uu[1] = (ui1_target_id >> 5) ^ 0x2E;   //id: 6th-bit in first byte
    t_uuid.uu[0] = (ui1_target_id << 3) ^ 0xA8;   //id: low 5bit in second byte

    //change MAC to UUID order
    c_strncpy(ac_data_rev_before, pc_mac, SF_FILT_DATA_SIZE);
    _mac_addr_reverse(ac_data_rev_before);

    //change MAC str to hex
    _mac_addr_str2bytes(ac_data_rev_before, aui1_mac_hex);
    c_memcpy(&t_uuid.uu[2], aui1_mac_hex, 6);

    c_memset(s_uuid_mask, 0, sizeof(s_uuid_mask));
    c_memset(s_uuid, 0, sizeof(s_uuid));

    _hex2str(t_uuid_mask.uu, s_uuid_mask, ui4_mask_len);
    _hex2str(t_uuid.uu, s_uuid, ui4_mask_len);

    //print data
    DBG_WOBLE_INFO(("mask:%s\n", s_uuid_mask));
    DBG_WOBLE_INFO(("data:%s\n", s_uuid));

    BT_GATTC_FILT_PARAM_SETUP_T scan_filt_param = {0};

    __SET_FILTER_PARAM(scan_filt_param,
                       bt_gattc_get_client_if(),  //client_if
                       e_act,              //action
                       ui4_index,          //filt_index
                       SF_FEAT_SELN_UUID,  //feat_seln
                       SF_LOGIC_TYPE_OR,   //list_logic_type
                       SF_LOGIC_TYPE_AND,   //filt_logic_type
                       SF_MAX_RSSI_DEFAULT,//rssi_high_thres
                       0,                  //rssi_low_thres
                       0,                  //dely_mode
                       0,                  //found_timeout
                       0,                  //lost_timeout
                       0);                 //found_timeout_cnt


    i4_ret = a_mtkapi_bt_gattc_scan_filter_param_setup(&scan_filt_param);
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_param_setup,i4_ret);

    i4_ret = a_mtkapi_bt_gattc_scan_filter_add_remove(bt_gattc_get_client_if(), //client_if
                                                    e_act,              //action
                                                    SF_FILT_TYPE_UUID,  //filt_type
                                                    ui4_index,          //filt_index
                                                    0,                  //company_id
                                                    0,                  //company_id_mask,
                                                    &s_uuid,            //p_uuid,
                                                    &s_uuid_mask,       //p_uuid_mask,
                                                    NULL,               //bd_addr,
                                                    0,                  //addr_type,
                                                    0,                  //data_len,
                                                    NULL,               //p_data,
                                                    0,                  //mask_len,
                                                    NULL);              //p_mask

    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_add_remove,i4_ret);

    return 0;
}
//dev name
static INT32 _wake_sf_cfg_for_dev_name(WAKE_SF_ACT_TYPE_E e_act,
                                            WAKE_SCAN_FILTER_TYPE_E e_type,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data)
{
    INT32 i4_ret;
    UINT32 ui4_mask_len = ac_sf_data_mask[e_type][0];
    CHAR ac_mask[SF_FILT_DATA_SIZE];
    DBG_WOBLE_API(("filter setup proc - dev name, act=%d.\n",e_act));

    //truncate the mask len for filt data length
    if (ui4_mask_len > c_strlen(pc_data))
    {
        ui4_mask_len = c_strlen(pc_data);
    }

    //get mask data
    c_memset(ac_mask, ac_sf_data_mask[e_type][1], ui4_mask_len);
    ac_mask[ui4_mask_len] = 0;

    //print data
    DBG_WOBLE_INFO(("mask:"));
    _data_print(ac_mask, ui4_mask_len);
    DBG_WOBLE_INFO(("data:"));
    _data_print(pc_data, ui4_mask_len);

    BT_GATTC_FILT_PARAM_SETUP_T scan_filt_param = {0};

    __SET_FILTER_PARAM(scan_filt_param,
                       bt_gattc_get_client_if(), //client_if
                       e_act,              //action
                       ui4_index,          //filt_index
                       SF_FEAT_SELN_DEV_NAME,//feat_seln
                       SF_LOGIC_TYPE_OR,   //list_logic_type
                       SF_LOGIC_TYPE_OR,   //filt_logic_type
                       SF_MAX_RSSI_DEFAULT,//rssi_high_thres
                       0,                  //rssi_low_thres
                       0,                  //dely_mode
                       0,                  //found_timeout
                       0,                  //lost_timeout
                       0);                 //found_timeout_cnt

    i4_ret = a_mtkapi_bt_gattc_scan_filter_param_setup(&scan_filt_param);
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_param_setup,i4_ret);

    i4_ret = a_mtkapi_bt_gattc_scan_filter_add_remove(bt_gattc_get_client_if(), //client_if
                                                    e_act,              //action
                                                    SF_FILT_TYPE_DEV_NAME,//filt_type
                                                    ui4_index,          //filt_index
                                                    0,                  //company_id
                                                    0,                  //company_id_mask,
                                                    NULL,               //p_uuid,
                                                    NULL,               //p_uuid_mask,
                                                    NULL,               //bd_addr,
                                                    0,                  //addr_type,
                                                    ui4_mask_len,       //data_len,
                                                    pc_data,            //p_data,
                                                    ui4_mask_len,       //mask_len,
                                                    ac_mask);              //p_mask
    WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_add_remove,i4_ret);
    return 0;
}
//------------------------------------------------------------------------------
static INT32 _bluetooth_gatt_scan_filter(WAKE_SCAN_FILTER_TYPE_E e_type,
                                            WAKE_SF_ACT_TYPE_E e_act,
                                            UINT32 ui4_index,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data)
{
    INT32 i4_ret = -1;
    UINT32 ui4_i;

    for (ui4_i = 0; WAKE_SF_TYPE_MAX != at_wake_sf_cfg[ui4_i].e_type; ui4_i++)
    {
        if (at_wake_sf_cfg[ui4_i].e_type == e_type)
        {
            if (ac_sf_data_mask[e_type][0] >= SF_FILT_DATA_SIZE)
            {
                DBG_WOBLE_ERR(("Err: data length is too long, type=%d, len=%d.\n",
                    e_type, ac_sf_data_mask[e_type][0]));
                return -1;
            }
            DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
            i4_ret = at_wake_sf_cfg[ui4_i].pf_sf_cfg(e_act,
                                                    e_type,
                                                    ui4_index,
                                                    ui1_target_id,
                                                    pc_data);
            break;
        }
    }

    if (WAKE_SF_TYPE_MAX == at_wake_sf_cfg[ui4_i].e_type)
    {
        DBG_WOBLE_ERR(("Err:can't find scan filter type proc!\n"));
    }

    return i4_ret;
}

INT32 bluetooth_gatt_add_company_filter(WAKE_SF_ACT_TYPE_E e_act, INT32 i4_company_id, INT32 i4_company_mask)
{
    INT32 i4_ret = 0;

    DBG_INFO(("<BT_GATT> e_act=%d, company_id=0x%x, company_mask=0x%x\n",e_act, i4_company_id, i4_company_mask));

    BT_GATTC_FILT_PARAM_SETUP_T scan_filt_param = {0};

    __SET_FILTER_PARAM(scan_filt_param,
                        bt_gattc_get_client_if(),  //client_if
                        e_act,          //action
                        COMPANY_SCAN_FILTER_IDX, //filt_index
                        32,             //feat_seln
                        0x00,           //list_logic_type
                        0,              //filt_logic_type
                        -127,           //rssi_high_thres
                        0,                  //rssi_low_thres
                        0,                  //dely_mode
                        0,                  //found_timeout
                        0,                  //lost_timeout
                        0);                 //found_timeout_cnt

    i4_ret = a_mtkapi_bt_gattc_scan_filter_param_setup(&scan_filt_param);
    WOBLE_CHK_FAIL_RET(a_mtkapi_bt_gattc_scan_filter_param_setup,i4_ret);
    //c_thread_delay(200);
    i4_ret = a_mtkapi_bt_gattc_scan_filter_add_remove(bt_gattc_get_client_if(), //client_if
                                                    e_act,          //action
                                                    5,              //filt_type
                                                    COMPANY_SCAN_FILTER_IDX, //filt_index
                                                    i4_company_id,  //company_id
                                                    i4_company_mask,//company_id_mask,
                                                    NULL,               //p_uuid,
                                                    NULL,               //p_uuid_mask,
                                                    NULL,               //bd_addr,
                                                    0,                  //addr_type,
                                                    0,                  //data_len,
                                                    NULL,               //p_data,
                                                    0,                 //mask_len,
                                                    0);                //p_mask
    WOBLE_CHK_FAIL_RET(a_mtkapi_bt_gattc_scan_filter_add_remove,i4_ret);

    if (pt_scan_filter != NULL)
    {
        if (WAKE_SF_ACT_ADD == e_act)
        {
            pt_scan_filter->ui4_sf_cnt++;
        }
        else if (WAKE_SF_ACT_DEL == e_act)
        {
            pt_scan_filter->ui4_sf_cnt--;
        }
    }

    return 0;
}

static INT32 bluetooth_gatt_add_filter_by_uuid(WAKE_SF_ACT_TYPE_E e_act,
                                               WAKE_SCAN_FILTER_TYPE_E e_type,
                                               INT32 i4_idx,
                                               CHAR *ps_uuid)
{
    INT32 i4_ret;
    CHAR* ps_uuid2 = NULL;
    CHAR* ps_uuid_mask = NULL;

    DBG_WOBLE_API(("filter setup proc - add filter bt uuid, act=%d.\n",e_act));

    if (0 == strncmp(ps_uuid, GATTC_DIRECT_PAIRING, strlen(ps_uuid)))
    {
        ps_uuid_mask = "000000000000000000000000F0FF0000";
        ps_uuid2 = "000000000000000000000000B5DB0000";

        ps_uuid_mask = "0000FFF0000000000000000000000000";
        ps_uuid2     = "0000DBB5000000000000000000000000";
    }
    else if (0 == strncmp(ps_uuid, GATTC_IOS_SERVICE_UUID, strlen(ps_uuid)))
    {
        ps_uuid_mask = "0000000000000000FFFFFFFFF0FFFFFF";
        ps_uuid2 = ac_ios_sf_default_filt_data;

        ps_uuid_mask    = "FFFFFFF0FFFFFFFF0000000000000000";
        ps_uuid2        = "69A3DBA5CBC14B5D0000000000000000";
    }

    DBG_LOG_PRINT(("mask:%s\n", ps_uuid_mask));
    DBG_LOG_PRINT(("data:%s\n", ps_uuid2));

    BT_GATTC_FILT_PARAM_SETUP_T scan_filt_param = {0};

    __SET_FILTER_PARAM(scan_filt_param,
                        bt_gattc_get_client_if(), //client_if
                        e_act,              //action
                        i4_idx,          //filt_index
                        SF_FEAT_SELN_UUID,  //feat_seln
                        SF_LOGIC_TYPE_OR,   //list_logic_type
                        SF_LOGIC_TYPE_AND,   //filt_logic_type
                        SF_MAX_RSSI_DEFAULT,//rssi_high_thres
                        0,                  //rssi_low_thres
                        0,                  //dely_mode
                        0,                  //found_timeout
                        0,                  //lost_timeout
                        0);                 //found_timeout_cnt

    i4_ret = a_mtkapi_bt_gattc_scan_filter_param_setup(&scan_filt_param);
    WOBLE_CHK_FAIL_RET(a_mtkapi_bt_gattc_scan_filter_param_setup,i4_ret);

    i4_ret = a_mtkapi_bt_gattc_scan_filter_add_remove(bt_gattc_get_client_if(), //client_if
                                                e_act,              //action
                                                SF_FILT_TYPE_UUID,  //filt_type
                                                i4_idx,          //filt_index
                                                0,                  //company_id
                                                0,                  //company_id_mask,
                                                ps_uuid2,//&t_uuid,            //p_uuid,
                                                ps_uuid_mask,//&t_uuid_mask,       //p_uuid_mask,
                                                NULL,               //bd_addr,
                                                0,                  //addr_type,
                                                0,                  //data_len,
                                                NULL,               //p_data,
                                                0,                  //mask_len,
                                                NULL);              //p_mask

    WOBLE_CHK_FAIL_RET(a_mtkapi_bt_gattc_scan_filter_add_remove,i4_ret);

    if (pt_scan_filter != NULL)
    {
        if (WAKE_SF_ACT_ADD == e_act)
        {
            pt_scan_filter->ui4_sf_cnt++;
        }
        else if (WAKE_SF_ACT_DEL == e_act)
        {
            pt_scan_filter->ui4_sf_cnt--;
        }
    }

    return 0;
}

//add scan filter for wake module
INT32 bluetooth_gatt_add_scan_filter(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data)
{
    INT32 i4_ret = -1;
    UINT32 ui4_i;
    WAKE_SCAN_FILTER_INFO_T *pt_sf_info = pt_scan_filter->at_filt_info;
    DBG_WOBLE_API(("add a scan filter\n"));
    DBG_WOBLE_INFO(("ftype=%d,id=%d,data=%s\n", ui4_type, ui1_target_id, pc_data));

    if (b_wake_sf_init == FALSE)
    {
        DBG_WOBLE_ERR(("Err:scan filter hasn't inited.\n"));
        return -1;
    }

    //find empty space
    for(ui4_i = 0; ui4_i < SF_MAX_SIZE; ui4_i++)
    {
        if (_is_skip_filter_idx(ui4_i)) /* skip company scan filter */
        {
            continue;
        }

        if(c_strlen(pt_sf_info[ui4_i].ac_filt_data) == 0)
        {
            break;
        }
    }

    if ((ui4_i == SF_MAX_SIZE) || (pt_scan_filter->ui4_sf_cnt >= SF_MAX_SIZE))
    {
        DBG_WOBLE_ERR(("Err:add filter fail, no more free space!\n"));
        return -1;
    }
    DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
    i4_ret = _bluetooth_gatt_scan_filter(ui4_type,
                                        WAKE_SF_ACT_ADD,
                                        ui4_i,
                                        ui1_target_id,
                                        pc_data);


    if (i4_ret != 0)
    {
        DBG_WOBLE_ERR(("Err:fail to add a scan filter.\n"));
    }
    else    //opration return ok, save the new filter dev info
    {
        pt_sf_info[ui4_i].e_type = ui4_type;
        c_memcpy(pt_sf_info[ui4_i].ac_filt_data, pc_data, SF_FILT_DATA_SIZE);
        pt_sf_info[ui4_i].ac_filt_data[SF_FILT_DATA_SIZE] = 0; //add '\0'
        pt_sf_info[ui4_i].ui1_id = ui1_target_id;
        pt_scan_filter->ui4_sf_cnt++;

        DBG_WOBLE_API(("add a scan filter successfully, have %d filters.\n",
            pt_scan_filter->ui4_sf_cnt));
    }

    return i4_ret;
}

//delete scan filter for wake moudle
INT32 bluetooth_gatt_del_scan_filter(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data)
{
    INT32 i4_ret = -1;
    UINT32 ui4_i;
    WAKE_SCAN_FILTER_INFO_T *pt_sf_info = pt_scan_filter->at_filt_info;
    DBG_WOBLE_API(("delete a scan filter\n"));
    DBG_WOBLE_INFO(("ftype=%d,id=%d,data=%s\n", ui4_type, ui1_target_id, pc_data));

    if (b_wake_sf_init == FALSE)
    {
        DBG_WOBLE_ERR(("Err:scan filter hasn't inited.\n"));
        return -1;
    }

    //find the right filter index
    for(ui4_i = 0; ui4_i < SF_MAX_SIZE; ui4_i++)
    {
        if (_is_skip_filter_idx(ui4_i)) /* skip company scan filter */
        {
            continue;
        }

        if((c_strcmp(pt_sf_info[ui4_i].ac_filt_data, pc_data) == 0)
            && (pt_sf_info[ui4_i].ui1_id == ui1_target_id)
            && (pt_sf_info[ui4_i].e_type == ui4_type))
        {
            break;
        }
    }

    //no find it
    if (ui4_i == SF_MAX_SIZE)
    {
        DBG_WOBLE_ERR(("Err:can't find the filter.\n"));
        return -1;
    }

    i4_ret = _bluetooth_gatt_scan_filter(ui4_type,
                                    WAKE_SF_ACT_DEL,
                                    ui4_i,
                                    pt_sf_info[ui4_i].ui1_id,
                                    pc_data);

    if (i4_ret != 0)
    {
        DBG_WOBLE_ERR(("Err:fail to delete a scan filter.\n"));
    }

    i4_ret = 0; //no matter whether or not the opration is successful
    //clear the filter dev info
    c_memset(pt_sf_info[ui4_i].ac_filt_data, 0, SF_FILT_DATA_SIZE);
    pt_sf_info[ui4_i].ui1_id = 0;
    pt_sf_info[ui4_i].e_type = 0;
    pt_scan_filter->ui4_sf_cnt--;

    DBG_WOBLE_API(("delete a scan filter successfully, have %d filters.\n",
        pt_scan_filter->ui4_sf_cnt));

    return i4_ret;
}

//modify scan filter for wake moudle
INT32 bluetooth_gatt_modify_scan_filter(UINT8 ui1_target_id,
                                                CHAR* pc_data)
{
    INT32 i4_ret = -1;
    UINT32 ui4_i;
    WAKE_SCAN_FILTER_INFO_T *pt_sf_info = pt_scan_filter->at_filt_info;
    DBG_WOBLE_API(("modify a scan filter.\n"));

    if (b_wake_sf_init == FALSE)
    {
        DBG_WOBLE_ERR(("Err:scan filter hasn't inited.\n"));
        return -1;
    }

    //find the right filter index
    for(ui4_i = 0; ui4_i < SF_MAX_SIZE; ui4_i++)
    {
        if (_is_skip_filter_idx(ui4_i)) /* skip company scan filter */
        {
            continue;
        }
        if(c_strcmp(pt_sf_info[ui4_i].ac_filt_data, pc_data) == 0)
        {
            break;
        }
    }

    //no find it
    if (ui4_i == SF_MAX_SIZE)
    {
        DBG_WOBLE_ERR(("Err:can't find the filter.\n"));
        return -1;
    }

    DBG_WOBLE_INFO(("ftype=%d,old_id=%d,new_id=%d,data=%s\n",
        pt_sf_info[ui4_i].e_type,
        pt_sf_info[ui4_i].ui1_id,
        ui1_target_id,
        pc_data));

    //id no change
    if (pt_sf_info[ui4_i].ui1_id == ui1_target_id)
    {
        DBG_WOBLE_ERR(("new id is the same as old one, ignore the change.\n"));
        return 0;
    }

    //delete it first
    DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
    i4_ret = _bluetooth_gatt_scan_filter(pt_sf_info[ui4_i].e_type,
                                        WAKE_SF_ACT_DEL,
                                        ui4_i,
                                        pt_sf_info[ui4_i].ui1_id,
                                        pc_data);

    if (i4_ret != 0)
    {
        DBG_WOBLE_ERR(("Err:fail to delete a scan filter.\n"));
        return i4_ret;
    }

    //and then add it again with new info, modify only target id
    DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
    pt_sf_info[ui4_i].ui1_id = ui1_target_id;
    i4_ret = _bluetooth_gatt_scan_filter(pt_sf_info[ui4_i].e_type,
                                        WAKE_SF_ACT_ADD,
                                        ui4_i,
                                        ui1_target_id,
                                        pc_data);
    if (i4_ret != 0)
    {
        DBG_WOBLE_ERR(("Err:fail to add a scan filter.\n"));
        return i4_ret;
    }

    return i4_ret;
}

INT32 bluetooth_gatt_add_scan_filter_data_reverse(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data)
{
    CHAR ac_data[SF_FILT_DATA_SIZE];
    //reverse data first
    c_strncpy(ac_data, pc_data, SF_FILT_DATA_SIZE);
    _mac_addr_reverse(ac_data);

    return bluetooth_gatt_add_scan_filter(ui4_type,
                                            ui1_target_id,
                                            ac_data);
}
INT32 bluetooth_gatt_del_scan_filter_data_reverse(UINT32 ui4_type,
                                            UINT8 ui1_target_id,
                                            CHAR* pc_data)
{
    CHAR ac_data[SF_FILT_DATA_SIZE];
    //reverse data first
    c_strncpy(ac_data, pc_data, SF_FILT_DATA_SIZE);
    _mac_addr_reverse(ac_data);

    return bluetooth_gatt_del_scan_filter(ui4_type,
                                            ui1_target_id,
                                            ac_data);
}
INT32 bluetooth_gatt_modify_scan_filter_data_reverse(UINT8 ui1_target_id,
                                                CHAR* pc_data,
                                                BOOL is_ios_dev)
{
    CHAR ac_data[SF_FILT_DATA_SIZE];

    //reverse data first
    c_strncpy(ac_data, pc_data, SF_FILT_DATA_SIZE);
    //MFSD data is upside down, UUID is normal
    if (is_ios_dev != TRUE)
    {
        _mac_addr_reverse(ac_data);
    }

    return bluetooth_gatt_modify_scan_filter(ui1_target_id,
                                            ac_data);
}


//enable or disable wake on BLE
INT32 bluetooth_gatt_wake_on_ble_enable(BOOL b_enable)
{
    INT32 i4_ret;

    if (b_wake_sf_init == FALSE)
    {
        DBG_WOBLE_ERR(("Err: scan filter hasn't inited.\n"));
        return -1;
    }

    if (b_enable == TRUE)
    {
        a_mtkapi_bt_gattc_scan_filter_disable(bt_gattc_get_client_if());

        do {
            if (bluetooth_gatt_add_company_filter(WAKE_SF_ACT_DEL, 0x0058, 0xffff) != 0)
            {
                DBG_WOBLE_ERR(("del filter fail, break !\n"));
                break;
            }
            DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
            if (bluetooth_gatt_add_filter_by_uuid(WAKE_SF_ACT_DEL,WAKE_SF_TYPE_PAIRED_IOS,COMPANY_SCAN_FILTER_IDX2, GATTC_IOS_SERVICE_UUID) != 0)
            {
                DBG_WOBLE_ERR(("del filter fail, break !\n"));
                break;
            }
            if (bluetooth_gatt_add_filter_by_uuid(WAKE_SF_ACT_DEL,WAKE_SF_TYPE_DIRECTED_PAIRING, COMPANY_SCAN_FILTER_IDX3, GATTC_DIRECT_PAIRING) != 0)
            {
                DBG_WOBLE_ERR(("del filter fail, break !\n"));
                break;
            }
        } while (0);

        //enable scan filter first
        i4_ret = a_mtkapi_bt_gattc_scan_filter_enable(bt_gattc_get_client_if());
        WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_enable,i4_ret);
        //after enable, start scan in callback function
        c_sema_lock_timeout(h_sf_sema, 1000);

        //delay power off, make sure the cmd has been executed by FW
        c_thread_delay(200);    //200ms
        b_sf_woble = TRUE;
    }
    else// if (TRUE == b_sf_woble)
    {
        if (TRUE == b_sf_woble)
    {
        //stop scan first
        i4_ret = a_mtkapi_bt_gattc_stop_scan();
        WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_stop_scan,i4_ret);
        }

        //and disable scan filter
        a_mtkapi_bt_gattc_scan_filter_enable(bt_gattc_get_client_if());
        do {
            if (bluetooth_gatt_add_company_filter(WAKE_SF_ACT_ADD, 0x0058, 0xffff) != 0)
            {
                DBG_WOBLE_ERR(("add filter fail, break !\n"));
                break;
            }
            if (bluetooth_gatt_add_filter_by_uuid(WAKE_SF_ACT_ADD,WAKE_SF_TYPE_NO_PAIRED_IOS,COMPANY_SCAN_FILTER_IDX2, GATTC_IOS_SERVICE_UUID) != 0)
            {
                DBG_WOBLE_ERR(("add filter fail, break !\n"));
                break;
            }
            if (bluetooth_gatt_add_filter_by_uuid(WAKE_SF_ACT_ADD,WAKE_SF_TYPE_DIRECTED_PAIRING, COMPANY_SCAN_FILTER_IDX3, GATTC_DIRECT_PAIRING) != 0)
            {
                DBG_WOBLE_ERR(("add filter fail, break !\n"));
                break;
            }
        } while (0);

        a_mtkapi_bt_gattc_scan_filter_enable(bt_gattc_get_client_if());
        WOBLE_CHK_FAIL(a_mtkapi_bt_gattc_scan_filter_enable,i4_ret);

        b_sf_woble = FALSE;
    }

    DBG_WOBLE_API(("woble = %d\n", b_sf_woble));

    return 0;
}

INT32 bluetooth_gatt_show_scan_filter(VOID)
{
    UINT32 ui4_i;
    WAKE_SCAN_FILTER_INFO_T *pt_sf_info = pt_scan_filter->at_filt_info;

    if (b_wake_sf_init == FALSE)
    {
        DBG_WOBLE_ERR(("Err: scan filter hasn't inited.\n"));
        return -1;
    }

    DBG_WOBLE_API(("wake on BLE is %s.\n", (b_sf_woble?"ENABLE":"DISABLE")));
    DBG_WOBLE_PRINT(("have %d valiad scan filter(s):\n", pt_scan_filter->ui4_sf_cnt));

    DBG_WOBLE_PRINT(("SN  TYPE  ID  FILT-DATA\n"));
    for(ui4_i = 0; ui4_i < SF_MAX_SIZE; ui4_i++)
    {
        if (_is_skip_filter_idx(ui4_i)) /* skip company scan filter */
        {
            continue;
        }
        DBG_WOBLE_PRINT(("<%d> %2d %2d %s\n",
            ui4_i,
            pt_sf_info[ui4_i].e_type,
            pt_sf_info[ui4_i].ui1_id,
            pt_sf_info[ui4_i].ac_filt_data));
    }

    return 0;
}

INT32 bluetooth_gatt_scan_filter_init(VOID)
{
    INT32 i4_ret;
    BLE_CACHE_DEVICE *t_scan_ble_device = NULL;
    DBG_WOBLE_API(("scan filter init.\n"));

    if (b_wake_sf_init == TRUE)
    {
        DBG_WOBLE_ERR(("scan filter already init.\n"));
        return 0;
    }

    /* allocate mutex */
    i4_ret = c_sema_create(&h_sf_sema,
                           X_SEMA_TYPE_BINARY,
                           X_SEMA_STATE_LOCK);
    if(i4_ret != OSR_OK)
    {
        DBG_WOBLE_ERR(("Err: Can't create mutex.\n"));
        return -1;
    }

    pt_scan_filter = (WAKE_SCAN_FILTER_T*)c_mem_calloc(1, sizeof(WAKE_SCAN_FILTER_T));
    if (pt_scan_filter == NULL)
    {
        DBG_WOBLE_ERR(("Err: no memory.\n"));
        return -1;
    }

    t_scan_ble_device = (BLE_CACHE_DEVICE*)c_mem_alloc(MAX_CACHE_BLE_NUMBER*sizeof(BLE_CACHE_DEVICE));
    if (NULL == t_scan_ble_device)
    {
        DBG_WOBLE_ERR(("Err: no memory.\n"));
        return -1;
    }

    b_sf_woble = FALSE;
    b_wake_sf_init = TRUE;

    //read ble device info in acfg and add scan filter
    i4_ret = a_cfg_get_blegatt_macaddress_threshold(t_scan_ble_device);
    if (0 != i4_ret)
    {
        DBG_WOBLE_ERR(("Err:a_cfg_get_blegatt_macaddress_threshold return fail.\n"));
    }
    else
    {
        UINT32 ui4_i;

        for(ui4_i = 0; ui4_i < MAX_CACHE_BLE_NUMBER; ui4_i++)
        {
            //search history device
            if(0 != strncmp(t_scan_ble_device[ui4_i].c_mac_address,
                            "000000000000",
                            MAC_ADDRESS_LENGTH_LEN))
            {

                if (t_scan_ble_device[ui4_i].b_is_IOS == TRUE)
                {
                    DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
                    bluetooth_gatt_add_scan_filter(
                        WAKE_SF_TYPE_PAIRED_IOS,
                        t_scan_ble_device[ui4_i].ui_target_ID,
                        t_scan_ble_device[ui4_i].c_mac_address);
                }
                else
                {
                    bluetooth_gatt_add_scan_filter_data_reverse(
                        WAKE_SF_TYPE_PAIRED_ANDROID_08X,
                        t_scan_ble_device[ui4_i].ui_target_ID,
                        t_scan_ble_device[ui4_i].c_mac_address);
                }

            }
        }
    }

    if (a_bgm_is_active_standby_state() == FALSE)  //Avoid AC On to wake up from woble in QS mode
    {
        DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
        bluetooth_gatt_add_company_filter(WAKE_SF_ACT_ADD, 0x0058, 0xFFFF);
        bluetooth_gatt_add_filter_by_uuid(WAKE_SF_ACT_ADD,WAKE_SF_TYPE_NO_PAIRED_IOS,COMPANY_SCAN_FILTER_IDX2, GATTC_IOS_SERVICE_UUID);
        bluetooth_gatt_add_filter_by_uuid(WAKE_SF_ACT_ADD,WAKE_SF_TYPE_DIRECTED_PAIRING, COMPANY_SCAN_FILTER_IDX3, GATTC_DIRECT_PAIRING);
        a_mtkapi_bt_gattc_scan_filter_enable(bt_gattc_get_client_if());
    }

    return 0;
}

BOOL bluetooth_gatt_get_wake_on_ble_enable(VOID)
{

    if (b_wake_sf_init == FALSE)
    {
        DBG_WOBLE_ERR(("Err: scan filter hasn't inited.\n"));
        return FALSE;
    }

    DBG_WOBLE_API(("woble = %d\n", b_sf_woble));

    return b_sf_woble;
}
#endif


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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>
#include <iconv.h>
#include <error.h>

#include "u_common.h"
#include "u_sys_name.h"
#include "c_dbg.h"

#include "c_uc_str.h"
#include "c_os.h"
#include "c_httpc_api.h"
#include "app_util/a_icl.h"
#include "u_net_socket.h"
#include "c_net_socket.h"
#include "c_net_config.h"

#include "am/a_am.h"

#if CONFIG_APP_SUPPORT_TONE_PLAY
#include "a_tone_play.h"
#endif//CONFIG_APP_SUPPORT_TONE_PLAY

#include "c_net_wlan.h"
#include "c_net_config.h"


#include "u_net_ni_if.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "nav/revolt_info/a_revolt_info.h"
#include "wizard_anim/a_wzd.h"
#include "bgm/mtk_comp/bgm_cast_c4tv/a_bgm_cast_c4tv.h"
#include "u_dhcpc_api.h"

#include "x_httpc_api.h"

#include <mtk_bt_service_gattc_wrapper.h>
#include <mtk_bt_service_gap_wrapper.h>

#include "bluetooth.h"

#include "bluetooth_gattc.h"
#include "bluetooth_gattc_rssimeter_view.h"
#include "bluetooth_gattc_proc.h"
#include "bluetooth_gattc_wake.h"

#define _BT_GATTC_GET_TYPE_SRVC             (0)
#define _BT_GATTC_GET_TYPE_CHAR             (1)
#define _BT_GATTC_GET_TYPE_DESC             (2)
#define _BT_GATTC_GET_TYPE_LAST             (3)

#define BTM_GATTC_APP_UUID  "49557E50-D815-11E4-8830-0800200C9A66"

#define REMOVE_LAST_SCAN_BUFFER(_i)                                                     \
do {                                                                                    \
    if (_i >= MAX_SCAN_DEVICE)                                                          \
    {                                                                                   \
        DBG_ERROR(("%s() %d: buffer index overflow!!!\n\n", __FUNCTION__,__LINE__));    \
        break;                                                                          \
    }                                                                                   \
    last_scan_device[_i].b_used = FALSE;                                                \
    last_scan_device[_i].i4_max_interval = 0;                                           \
    last_scan_device[_i].ui_pairing_state = 0;                                          \
    last_scan_device[_i].ui8_time_sum = 0;                                              \
    memset(last_scan_device[_i].last_mac_addr, 0, sizeof(last_scan_device[_i].last_mac_addr));  \
    if (NULL == last_scan_device[_i].ui8_interval || 0 == last_scan_device[_i].i4_elem_num)     \
    {                                                                                           \
        DBG_LOG_PRINT(("%s() %d: no need clear ui8_interval!!!\n\n", __FUNCTION__,__LINE__));   \
        break;                                                                                  \
    }                                                                                           \
    memset(last_scan_device[_i].ui8_interval, 0, last_scan_device[_i].i4_elem_num*sizeof(UINT64)); \
}while(0)
/***************************************static variable defines**************************************/
static BOOL                                 b_is_init;
static INT32                                bt_gattc_app_client_if;

static INT8                                 i_scan_number;// up to 5 servers
static INT32                                i4_set_rssi_threshold;
static INT32                                i4_scan_status;
static INT32                                i4_target_id;
static BOOL                                 b_gatt_close;
static BOOL                                 b_ios_device = FALSE;
static uint8_t                              i_write_type = GATTC_WRITE_RESPONSE;

static uint8_t                              Ns[AES_BLOCK_SIZE], Nc[AES_BLOCK_SIZE], HC[AES_BLOCK_SIZE], Kn[AES_BLOCK_SIZE] = {0};
static AES_KEY                              aes;
static char                                 c_msd_security[3] = {0};
static EIR_MSD_VARIABLE_TAG                 variable_tag;
static BOOL                                 b_is_NS = FALSE;
static uint8_t                              write_c255[17] = {0};
static BLE_CACHE_DEVICE                     scan_ble_device[MAX_CACHE_BLE_NUMBER];
static BOOL                                 b_cache_full = FALSE;
static BOOL                                 b_cache_mac = FALSE;
static BOOL                                 b_rssi_show = TRUE;
static INT32                                i4_ble_version = 0;
static LAST_SCAN_DEVICE                     last_scan_device[MAX_SCAN_DEVICE];
static GATT_SERVER_DATA                     server_data_array[MAX_SCAN_DEVICE];

extern BOOL                                 b_allow_scan;
extern BOOL                                 b_can_scan;
extern BOOL                                 b_is_poweroff;

BOOL                                        b_always_allow_test_tool_pair = FALSE;

static T_RSSI_NOTIFY_MSG                    t_rssi_meter_nfy;
/****************************************functions declarations*************************************/
INT32 bluetooth_gatt_scan_device_cli(VOID);
INT32 bluetooth_gatt_set_rssi_cli(int rssi_threshold);
INT32 bluetooth_gatt_get_rssi_cli(VOID);
INT32 bluetooth_gatt_stop_scan_cli(VOID);
INT32 bluetooth_gatt_connect_service_cli(char *mac_address);
INT32 bluetooth_gatt_get_response_cli(const char *dir_path);
INT32 bluetooth_gatt_get_put_cli(const char *url_json);
INT32 bluetooth_gatt_write_data_cli(int char_index, const char* write_str);
INT32 bluetooth_gatt_read_data_cli(int char_index);

INT32 bluetooth_gatt_init_proc(VOID);
INT32 bluetooth_gattc_poweron_scan_proc(VOID);
INT32 bluetooth_gattc_scan_proc(VOID);
INT32 bluetooth_gattc_stop_scan_proc(VOID);
VOID bluetooth_gatt_deinit_proc(VOID);
INT32 bluetooth_gatt_close_proc(VOID);
INT32 bluetooth_gatt_event_msg_proc(const VOID *pv_msg);
INT32 bluetooth_gatt_intra_msg_proc(const VOID *pv_msg);
/*****************************************static functions defines***********************************/
// transform bt_uuid_t to string uuid
void _bt_gattc_print_uuid (UINT8* uuid, char* uuid_s)
{
    int i;
    char *ptr;
    ptr = uuid_s;
    for (i = 0 ; i < 16 ; i++) {
        sprintf(ptr, "%02X", uuid[i]);
        ptr+=2;
    }
    *ptr = '\0';
}

// transform uint8_t to char
static void _bt_gattc_print_uint8 (uint8_t* unsigned_char , int unsigned_char_len, char* signed_char)
{
    int i;
    char *ptr;
    ptr = signed_char;
    for (i = 0 ; i < unsigned_char_len ; i++) {
        sprintf(ptr, "%02X", unsigned_char[i]);
        ptr+=2;
    }
    *(ptr+1) = '\0';
}

static int _bt_gattc_btaddr_stoh(char *btaddr_s, uint8_t *bdaddr_h)
{
    int i;
    if(NULL == btaddr_s || NULL == bdaddr_h)
    {
        return -1;
    }
    for (i = 0; i < 6; i++)
    {
        bdaddr_h[i] = strtoul(btaddr_s, &btaddr_s, 16);
        btaddr_s++;
    }
    return 0;
}

static INT32 _bt_char_to_int(char c_value)
{
    if((INT32)c_value >= 48 && (INT32)c_value <= 57)
    {
        return ((INT32)c_value - 48);
    }
    else if((INT32)c_value >= 65 && (INT32)c_value <= 70)
    {
        return ((INT32)c_value - 55);
    }
    else if((INT32)c_value >= 97 && (INT32)c_value <= 102)
    {
        return ((INT32)c_value - 87);
    }
    else
    {
        DBG_INFO(("<BT_GATT> _bt_char_to_int error value.\n"));
        return 0;
    }
}

static INT32 _bt_bytes_to_int(char* s_value)
{
    int temp_high = _bt_char_to_int(s_value[0]);
    int temp_low = _bt_char_to_int(s_value[1]);

    return (temp_high * 16 + temp_low);
}

static char* _bt_int_to_char(INT32 i_transvalue, char *c_transarray, int j)
{
    if(i_transvalue >= 0 && i_transvalue <= 9)
    {
        c_transarray[j] = (char)(i_transvalue + 48);
        return c_transarray;
    }
    else if(i_transvalue >= 10 && i_transvalue <= 15)
    {
        c_transarray[j] = (char)(i_transvalue + 87);
        return c_transarray;
    }
    else
    {
        DBG_INFO(("<BT_GATT> _bt_int_to_char error value.\n"));
        return NULL;
    }
}

VOID __mem_print2(CHAR* _addr, UINT32 len, const CHAR*ps_func, INT32 line)
{
#define BUF_LEN         (128)
    int i = 0;
    int j = 0;
    UINT32 z_size = 0;
    CHAR buf[BUF_LEN] = {0};

    DBG_INFO(("<BT_GATT> __mem_print2 from (%s():%d), len=%d:\n", (!ps_func) ? "???" : ps_func, line, len));
    for(;i<len;i++)
    {
        sprintf(buf+z_size, "%02x ", *((UINT8 *)_addr+i));
        z_size += 3;

        if ((i+1)%16 == 0)
        {
            buf[z_size] = '\t';
            z_size += 1;

            for (j=0;j<16;j++)
            {
                sprintf(buf+z_size, "%c", (_addr[i-15+j] == 0) ? '^' : _addr[i-15+j]);
                z_size += 1;
            }

            buf[z_size] = ' ';
            buf[z_size+1] = 0;

            DBG_INFO(("%s\n", buf));

            z_size = 0;
            c_memset(buf, 0, BUF_LEN);
        }
        else if (i+1 == len)
        {
            for (j=(i+1)%16;j<16;j++)
            {
                sprintf(buf+z_size, "%s", "   ");
                z_size += 3;
            }
            buf[z_size] = '\t';
            z_size += 1;

            for (j=0;j<((i+1)%16);j++)
            {
                sprintf(buf+z_size, "%c", (_addr[i-(i%16)+j] == 0) ? '^' : _addr[i-(i%16)+j]);
                z_size += 1;
            }

            buf[z_size] = ' ';
            buf[z_size+1] = 0;

            DBG_INFO(("%s\n", buf));

            z_size = 0;
            c_memset(buf, 0, BUF_LEN);
        }
    }
}

static BOOL  _bt_url_response_need_convert_charset(CHAR* ps_url)
{
    BOOL b_ret = FALSE;

    do {
        if (NULL == ps_url || c_strlen(ps_url) == 0)
        {
            b_ret = FALSE;
            break;
        }

        DBG_LOG_PRINT(("%s() %d: ps_url=[%s]\n", __FUNCTION__,__LINE__,ps_url));

        if (c_strstr(ps_url, "static/tv_settings/system/country") != NULL)
        {
            b_ret = TRUE;
            break;
        }

        b_ret = FALSE;
    } while (0);

    return b_ret;
}

INT32 _bt_url_response_utf8_2_latin1(const CHAR * ps_src,CHAR * ps_dst,UINT32 ui4_dst_len)
{
    INT32   i = 0;
    UTF16_T *pw2s_str = NULL;

    if (NULL == ps_src || NULL == ps_dst || 0 == ui4_dst_len)
    {
        DBG_LOG_PRINT(("%s() Invalid argument!\n", __FUNCTION__));
        return BLUETOOTH_GATTC_FAILED;
    }

    if ((pw2s_str = (UTF16_T *)c_mem_alloc(ui4_dst_len*sizeof(UTF16_T)+1)) != NULL)
    {
        c_uc_ps_to_w2s(ps_src,pw2s_str, ui4_dst_len);

        for (i = 0; i < ui4_dst_len; i++)
        {
            if (0 == pw2s_str[i])
                break;
            ps_dst[i] = (UINT8)(pw2s_str[i]);
        }

        __mem_print2(ps_dst, ui4_dst_len, __FUNCTION__, __LINE__);
    }

    if (pw2s_str != NULL)
    {
        c_mem_free(pw2s_str);
        pw2s_str = NULL;
    }

    return i;
}

void __mem_print(char* _addr, UINT32 len)
{
    int i = 0;
    DBG_INFO(("<BT_GATT> print mem:"));
    for(;i<len;i++)
        DBG_INFO(("%0x ",(char)*(_addr+i)));

    DBG_INFO(("\n"));
}

static uint8_t* _bt_xor_operation(uint8_t *value_a, uint8_t *value_b)
{
    uint8_t *xor_result = malloc(AES_BLOCK_SIZE);
    int i = 0;
    for(; i < AES_BLOCK_SIZE; i++)
    {
        xor_result[i] = value_a[i] ^ value_b[i];
    }

    return xor_result;
}

static unsigned char* str2bytes(char *input, unsigned char *output)
{
    int len = strlen(input), i = 0;
    if(0 != len%2)
        return NULL;
    for(; i < len/2; i++)
    {
        sscanf(&input[2 * i], "%2x", (int *)&output[i]);
    }

    return NULL;
}

static unsigned char* revert_bytes(unsigned char input[], int len)
{
    unsigned char tmp;
    int i = 0;
    while(i< len/ 2)
    {
        tmp= input[i];
        input[i] = input[len - i- 1];
        input[len- i- 1] = tmp;
        i++;
    }
    return input;
}

static void _bt_AES_ecb_calc_nsnc()
{
    int i = 0;
    //make nonces: Ns,Nc
    srandom((unsigned int)time(NULL));
    long int ran[4];
    for(i = 0;i<4;i++)
    {
        ran[i] = random();
    }

    uint8_t *p1 = (uint8_t*)&ran[0];
    uint8_t *p2 = (uint8_t*)&ran[3];
    for(i = 0;i<AES_BLOCK_SIZE;i++)
    {
        Ns[i] = *p1++ ^ *p2--;
        Nc[i] = *p1 ^ *p2;
    }

    //DBG_INFO(("<BT_GATT> Ns:"));
   // for (i=0; i<AES_BLOCK_SIZE; ++i)
    //{
    //    DBG_INFO(("%0x ", Ns[i]));
    //}
    //DBG_INFO(("\n"));

    //DBG_INFO(("<BT_GATT> Nc:"));
    //for (i=0; i<AES_BLOCK_SIZE; ++i)
    //{
    //    DBG_INFO(("%0x ", Nc[i]));
    //}
    //DBG_INFO(("\n"));

    return;
}

static void _bt_AES_ecb_encrypt(uint8_t *High_counter)
{
    DBG_ERROR(("<BT_GATT> Enter function =%s, line=%d\r\n",__FUNCTION__, __LINE__));

    uint8_t t1[AES_BLOCK_SIZE], t2[AES_BLOCK_SIZE], t3[AES_BLOCK_SIZE], t4[AES_BLOCK_SIZE];
    unsigned int i;
    uint8_t *temp = NULL;

    // get t1, t1 = AES-E(Kp, Ns);
    AES_ecb_encrypt(Ns, t1, &aes, AES_ENCRYPT);

    // get t2, t2 = AES-E(Kp, t1 XOR Nc);
    temp = _bt_xor_operation(t1, Nc);
    AES_ecb_encrypt(temp, t2, &aes, AES_ENCRYPT);

    // get t3, t3 = AES-E(Kp, t2 XOR Ns XOR 0x e9 d3 19 38 b1 34 4e 69 9a c2 43 f3 66 7c 15 9e);
    temp = _bt_xor_operation(t2, Ns);
    temp = _bt_xor_operation(temp, calc_t3);
    AES_ecb_encrypt(temp, t3, &aes, AES_ENCRYPT);

    // get Kn, Kn = AES-E(Kp, t3 XOR Nc XOR 0x 5b e2 ee 6b eb cc 40 72 a5 2d 24 8f 5c c7 49 78);
    temp = _bt_xor_operation(t3, Nc);
    temp = _bt_xor_operation(temp, calc_kn);
    AES_ecb_encrypt(temp, Kn, &aes, AES_ENCRYPT);
    DBG_INFO(("<BT_GATT> Kn:"));
    for (i=0; i<AES_BLOCK_SIZE; ++i) {
    DBG_INFO(("%0x ", Kn[i]));
    }
    DBG_INFO(("\n"));

    // get t4, t4 = AES-E(Kp, Kn);
    AES_ecb_encrypt(Kn, t4, &aes, AES_ENCRYPT);

    // HCs = t4[127...64], HCc = t4[63...0];
    memcpy(High_counter, t4, AES_BLOCK_SIZE);
    DBG_INFO(("<BT_GATT> High_counter:"));
    for (i=0; i<AES_BLOCK_SIZE; ++i) {
    DBG_INFO(("%0x ", High_counter[i]));
    }
    DBG_INFO(("\n"));

    return;

}

static void _bt_AES_encrypt_data(uint8_t *indata, uint8_t *outdata, int bytes_read, uint8_t *counter)
{
    DBG_INFO(("<BT_GATT> Enter function =%s, line=%d\r\n",__FUNCTION__, __LINE__));
    //int i = 0;
    uint8_t t1[AES_BLOCK_SIZE] = {0};
    uint8_t *out = malloc(AES_BLOCK_SIZE);

    AES_set_encrypt_key(Kn, AES_BLOCK_SIZE * 8, &aes);
    AES_ecb_encrypt(counter, t1, &aes, AES_ENCRYPT);
    out = _bt_xor_operation(t1, indata);

    //DBG_INFO(("<BT_GATT> out:" ));
    //for(i = 0; i < AES_BLOCK_SIZE; i++)
    //{
    //    DBG_INFO(("%02x ",out[i]));
   // }
    //DBG_INFO(("\n"));

    memcpy(outdata, out, AES_BLOCK_SIZE);
    free(out);

    return;
}

static void _bt_url_get_response(char* ps_url, int write_number)
{
    BT_GATT_ENTER_FUNCTION();

    HANDLE_T h_handle;
    INT32 i4_ret;
    HTTPC_DATA_T t_data;
    x_httpc_data_init(&t_data);
    UINT64 ui8_content_len;
    INT32 i4_timeout = 60*2;
    CHAR s_Auth_type[64+1] = {0};

    i4_ret = x_httpc_new_session(&h_handle);
    if (i4_ret == HTTPR_OK)
    {
        DBG_INFO(("<BT_GATT> new session PASS\n"));
    }
    else
    {
        DBG_ERROR(("<BT_GATT> error: new session FAIL\n"));
    }

    snprintf(s_Auth_type, 64, "SESSION: %s", bt_gatt_get_session_token());
    x_httpc_append_header(h_handle, s_Auth_type);

    x_httpc_set_option(h_handle, HTTP_HANDLE_OPT_TIMEOUT, &i4_timeout);
    i4_ret = x_httpc_get(h_handle, ps_url, &t_data);

    if (i4_ret == HTTPR_OK)
    {
        DBG_INFO(("<BT_GATT> get PASS\n"));
    }
    else
    {
        DBG_ERROR(("<BT_GATT> error: x_httpc_get FAIL. retry.\n"));
        int i = 0;
        while(i<9)//retry 10 times.
        {
            sleep(3);
            i4_ret = x_httpc_get(h_handle, ps_url, &t_data);
            if (i4_ret == HTTPR_OK)
            {
                break;
            }
            i++;
        }
        if(i==9){
            DBG_ERROR(("<BT_GATT> error: x_httpc_get FAIL. retry FAIL.!!!\n"));
            BT_GATT_FREE(server_data_array[write_number].response_msg);
            x_httpc_free_session(h_handle);
            x_httpc_data_free(&t_data);
            return;
        }
    }

    x_httpc_get_info(h_handle, HTTP_HANDLE_INFO_RESPONSE_CODE, &(server_data_array[write_number].ui4_response_code));
    x_httpc_get_info(h_handle, HTTP_HANDLE_INFO_CONTENT_LENGTH, &ui8_content_len);
    DBG_INFO(("<BT_GATT> response code is %d\n", server_data_array[write_number].ui4_response_code));
    DBG_INFO(("<BT_GATT> content length is %lld\n", ui8_content_len));
    if(server_data_array[write_number].ui4_response_code != 200)
    {
        server_data_array[write_number].ui4_response_msg_len = 0;

        DBG_ERROR(("<BT_GATT> response error code is %d, %d\n", server_data_array[write_number].ui4_response_code, __LINE__));
        return;
    }
    t_data.pac_data[t_data.ui4_len] = '\0';
    DBG_INFO(("<BT_GATT> t_data::pac_data is %s\n ", t_data.pac_data));
    DBG_INFO(("<BT_GATT> t_data::ui4_len is %d\n ", t_data.ui4_len));
    UINT32 ui4_respponse_msg_len = server_data_array[write_number].ui4_response_msg_len = t_data.ui4_len;

    BT_GATT_FREE(server_data_array[write_number].response_msg);
    BT_GATT_MALLOC(server_data_array[write_number].response_msg, ui4_respponse_msg_len + 1);

    if (_bt_url_response_need_convert_charset(ps_url))
    {
        ui4_respponse_msg_len = _bt_url_response_utf8_2_latin1(t_data.pac_data, server_data_array[write_number].response_msg, t_data.ui4_len);
        if (ui4_respponse_msg_len <= 0)
        {
            memcpy(server_data_array[write_number].response_msg, t_data.pac_data, t_data.ui4_len);
            ui4_respponse_msg_len = t_data.ui4_len;
        }
        else
        {
            server_data_array[write_number].ui4_response_msg_len = (ui4_respponse_msg_len > t_data.ui4_len) ? \
                                                                    t_data.ui4_len : ui4_respponse_msg_len;
        }
    }
    else
    {
        memcpy(server_data_array[write_number].response_msg, t_data.pac_data, t_data.ui4_len);
    }
    server_data_array[write_number].response_msg[ui4_respponse_msg_len] = '\0';

    x_httpc_free_session(h_handle);
    x_httpc_data_free(&t_data);

    return;
}

static void _bt_url_put_response(char* put_url, char* put_body, int write_number)
{
    BT_GATT_ENTER_FUNCTION();

    DBG_INFO(("<BT_GATT> put_url is %s\n ", put_url));
    DBG_INFO(("<BT_GATT> put_body is %s\n ", put_body));

    CHAR s_Auth_type[64+1] = {0};
    HANDLE_T h_handle;
    INT32 i4_ret;
    HTTPC_DATA_T t_data;

    x_httpc_data_init(&t_data);
    i4_ret = x_httpc_new_session(&h_handle);
    if (i4_ret == HTTPR_OK)
    {
        DBG_INFO(("<BT_GATT> new session PASS\n"));
    }
    else
    {
        DBG_ERROR(("<BT_GATT> error: new session FAIL\n"));
    }

    x_httpc_append_header(h_handle, "Expect: ");
    x_httpc_append_header(h_handle, "content-type: application/json");

    snprintf(s_Auth_type, 64, "SESSION: %s", bt_gatt_get_session_token());
    x_httpc_append_header(h_handle, s_Auth_type);

    i4_ret = x_httpc_put(h_handle, put_url, put_body, c_strlen(put_body), &t_data);

    if (i4_ret == HTTPR_OK)
    {
        DBG_INFO(("<BT_GATT> get PASS\n"));
    }
    else
    {
        DBG_ERROR(("<BT_GATT> error: x_httpc_put FAIL.%s:%d.!!!\n",__FILE__,__LINE__));
        BT_GATT_FREE(server_data_array[write_number].response_msg);
        x_httpc_free_session(h_handle);
        x_httpc_data_free(&t_data);
        return ;
    }

    x_httpc_get_info(h_handle, HTTP_HANDLE_INFO_RESPONSE_CODE, &(server_data_array[write_number].ui4_response_code));
    DBG_INFO(("<BT_GATT> response code is %d\n", server_data_array[write_number].ui4_response_code));
    if(server_data_array[write_number].ui4_response_code != 200)
    {
        server_data_array[write_number].ui4_response_msg_len = 0;

        DBG_ERROR(("<BT_GATT> response error code is %d, %d\n", server_data_array[write_number].ui4_response_code, __LINE__));
        return;
    }
    t_data.pac_data[t_data.ui4_len] = '\0';
    DBG_INFO(("<BT_GATT> t_data::pac_data is %s\n ", t_data.pac_data));
    DBG_INFO(("<BT_GATT> t_data::ui4_len is %d\n ", t_data.ui4_len));
    UINT32 ui4_response_msg_len = server_data_array[write_number].ui4_response_msg_len = t_data.ui4_len;
    BT_GATT_FREE(server_data_array[write_number].response_msg);
    BT_GATT_MALLOC(server_data_array[write_number].response_msg, ui4_response_msg_len + 1);
    memcpy(server_data_array[write_number].response_msg, t_data.pac_data, t_data.ui4_len);
    server_data_array[write_number].response_msg[ui4_response_msg_len] = '\0';

    x_httpc_free_session(h_handle);
    x_httpc_data_free(&t_data);


}

static VOID _bt_print_server_data(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    int i;
    DBG_INFO(("<BT_GATT> ....................devices information ................\r\n"));
    for(i = 0; i < MAX_SCAN_DEVICE; i++)
    {
        DBG_INFO(("<BT_GATT> device_id = %d.\r\n", i));
        DBG_INFO(("<BT_GATT> conn_id = %d.\r\n", server_data_array[i].ble_connect_result.conn_id));
        DBG_INFO(("<BT_GATT> scan btaddr = %s.\r\n", server_data_array[i].ble_scan_result.btaddr));
        DBG_INFO(("<BT_GATT> connect btaddr = %s.\r\n", server_data_array[i].ble_connect_result.btaddr));
    }

}


// get scan status
static INT32 bluetooth_gatt_get_scan_status(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    // 0: stop_scan finish, 1 : scaning, other value means fail
    if(i4_scan_status < 0 || i4_scan_status > 1)
    {
        return BLUETOOTH_GATTC_FAILED;
    }

    return i4_scan_status;
}

/****************************************callback functions****************************************/
// get event msg from mw
VOID _bt_gattc_event_result_cb(BT_GATTC_EVENT_T bt_gatt_event, BT_GATTC_CONNECT_STATE_OR_RSSI_T *bt_gattc_conect_state_or_rssi, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();

    BT_GATT_MSG_T t_msg = {0};

    t_msg.ui4_msg_id    = BT_GATT_MSG_EVENT;
    t_msg.ui4_data1     = bt_gatt_event;
    t_msg.ui4_data3     = bt_gattc_conect_state_or_rssi;
    bt_gatt_send_msg(BT_GATT_MSG_EVENT, &t_msg);

    return;
}

VOID _bt_gattc_reg_client_result_cb(BT_GATTC_REG_CLIENT_T *pt_reg_client_result, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();
    BT_GATT_MSG_T t_msg = {0};

    t_msg.ui4_msg_id    = BT_GATT_MSG_INTRA;
    t_msg.ui4_data1     = BT_GATT_REG_APP_CB;
    t_msg.ui4_data3     = pt_reg_client_result;
    bt_gatt_send_msg(BT_GATT_MSG_INTRA, &t_msg);
    return;
}

// get scan server mac address result from mw
VOID _bt_gattc_scan_result_cb(BT_GATTC_SCAN_RST_T *pt_scan_result, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();

    if(pt_scan_result != NULL)
    {
        // send msg to gatt app self
        BT_GATT_MSG_T t_msg = {0};

        t_msg.ui4_msg_id    = BT_GATT_MSG_INTRA;
        t_msg.ui4_data1     = BT_GATT_SCAN_RESULT_CB;
        t_msg.ui4_data3     = pt_scan_result;
        bt_gatt_send_msg(BT_GATT_MSG_INTRA, &t_msg);

    }

    return;
}

VOID _bt_gattc_get_reg_notify_result_cb(BT_GATTC_GET_REG_NOTI_RST_T *pt_get_reg_noti_result, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();

    BT_GATT_MSG_T t_msg = {0};

    DBG_INFO(("<BT_GATT> conn_id = %d,handle=%d,registered = %d.\r\n",
                                                        pt_get_reg_noti_result->conn_id,
                                                        pt_get_reg_noti_result->handle,
                                                        pt_get_reg_noti_result->registered));
    if(pt_get_reg_noti_result != NULL)
    {
        t_msg.ui4_msg_id    = BT_GATT_MSG_INTRA;
        t_msg.ui4_data1     = BT_GATT_REG_NOTI_CB;
        t_msg.ui4_data3     = pt_get_reg_noti_result;
        bt_gatt_send_msg(BT_GATT_MSG_INTRA, &t_msg);
    }

    return;
}

VOID _bt_gattc_notify_result_cb(BT_GATTC_GET_NOTIFY_T *pt_notify, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret = 0;
    int i = 0;
    int connection_id = pt_notify->conn_id;// justify which device send request msg to audio platform
    int read_id = 0;


    if(pt_notify != NULL && pt_notify->notify_data.len != 0)
    {
        // print notify result information
        C0_HEADER notify_c0_result;
        memset(&notify_c0_result, 0, sizeof(C0_HEADER));

        notify_c0_result.i_sequence_number = pt_notify->notify_data.value[0];
        notify_c0_result.i_fragment_number = pt_notify->notify_data.value[1];
        DBG_INFO(("<BT_GATT> notify notify_c0_result.i_fragment_number = %d.\r\n", notify_c0_result.i_fragment_number));
        notify_c0_result.i_last_fragment_number = pt_notify->notify_data.value[2];
        DBG_INFO(("<BT_GATT> notify notify_c0_result.i_last_fragment_number = %d.\r\n", notify_c0_result.i_last_fragment_number));
        notify_c0_result.i_security_data = pt_notify->notify_data.value[3];
        notify_c0_result.i2_total_length = pt_notify->notify_data.value[4] + ((pt_notify->notify_data.value[5]) << 8);

/*****************************************************decrypt C0*********************************************************************/
        if(notify_c0_result.i_security_data == GATTC_ADD_SECURITY)
        {
            // for BLE security
            uint8_t CTRs[AES_BLOCK_SIZE] = {0}, input[AES_BLOCK_SIZE] = {0}, dec_out[AES_BLOCK_SIZE] = {0}, HCs[8] = {0}, LC0[4] = {0};
            UINT32 ui4_xsn = 0, ui4_lc0 = 0;

            // decrypt C0 from the 7th byte
            // get HC value
            DBG_ERROR(("<BT_GATT> start decrypt C0 ...\n" ));
            // HCs = t4[127...64], HCc = t4[63...0]
            // CTRs[0] = HCs{64} || XSN{32} || 0{1} || C0{1} || LC{30}
            memcpy(HCs, HC + 8, 8);
            memcpy(CTRs + 8, HCs, 8);
            ui4_xsn = notify_c0_result.i_sequence_number;
            memcpy(CTRs + 4, (char*)&ui4_xsn, 4);
            LC0[0] = LC0[0] &~ (1 << 7);// 0 for receive, 1 for send, set 0
            LC0[0] = LC0[0] &~ (1 << 6);// 1 for C0, 0 for C1-C80, set 1
            ui4_lc0 = LC0[0] << 24 | LC0[1] << 16 | LC0[2] << 8 | LC0[3];
            ui4_lc0 &= 0xc0000000;
            ui4_lc0 |= 0;
            memcpy(CTRs, (char*)&ui4_lc0, 4);
            memset(input, 0, AES_BLOCK_SIZE);
            memset(dec_out, 0, AES_BLOCK_SIZE);
            memcpy(input, pt_notify->notify_data.value + 6, 4);

            _bt_AES_encrypt_data(input, dec_out, 4, CTRs);
            memcpy(pt_notify->notify_data.value + 6, dec_out, 4);

        }
/************************************************************************************************************************/
        notify_c0_result.i2_payload_length = pt_notify->notify_data.value[6] + ((pt_notify->notify_data.value[7]) << 8);
        notify_c0_result.i_message_type = pt_notify->notify_data.value[8];
        notify_c0_result.i_check_sum = pt_notify->notify_data.value[9];
        DBG_INFO(("<BT_GATT> notify c0_header.i_sequence_number = %d\r\n", notify_c0_result.i_sequence_number));
        DBG_INFO(("<BT_GATT> notify c0_header.i_fragment_number = %d\r\n", notify_c0_result.i_fragment_number));
        DBG_INFO(("<BT_GATT> notify c0_header.i_last_fragment_number = %d\r\n", notify_c0_result.i_last_fragment_number));
        DBG_INFO(("<BT_GATT> notify c0_header.i_security_data = %d\r\n", notify_c0_result.i_security_data));
        DBG_INFO(("<BT_GATT> notify c0_header.i2_total_length = %d\r\n", notify_c0_result.i2_total_length));
        DBG_INFO(("<BT_GATT> notify c0_header.i2_payload_length = %d\r\n", notify_c0_result.i2_payload_length));
        DBG_INFO(("<BT_GATT> notify c0_header.i_message_type = %d\r\n", notify_c0_result.i_message_type));
        DBG_INFO(("<BT_GATT> notify c0_header.i_check_sum = %d\r\n", notify_c0_result.i_check_sum));

        if(notify_c0_result.i_message_type == 0x0A)
        {
            DBG_ERROR(("<BT_GATT> Sever nonce announcement.\n"));
            if(variable_tag.security_key != 0)
            {
                // for BLE security
                _bt_AES_ecb_calc_nsnc();
                b_is_NS = TRUE;
                // get aes_key
                if(strncmp(c_msd_security, "01", 2) == 0)
                {
                    i_ret = AES_set_encrypt_key(Kp, 128, &aes);

                }
                else if(strncmp(c_msd_security, "00", 2) == 0)
                {
                    i_ret = AES_set_encrypt_key(Kt, 128, &aes);
                }
                if (i_ret < 0)
                {
                    DBG_ERROR(("<BT_GATT> Unable to set encryption key in AES\n"));
                    return;
                }
            }
        }
        else if(notify_c0_result.i_message_type == 0x0B)
        {
            INT32 i4_new_target = 0, i4_store_id = 0, i4_tmp_target = 0;

            i4_tmp_target = (notify_c0_result.i2_payload_length >> 8) & 0x00ff;
            i4_new_target = ((i4_tmp_target & 0x0c) << 2) | (i4_tmp_target >> 4);
            DBG_ERROR(("<BT_GATT> Change target request, new target = %d.\n", i4_new_target));

            for(i = 0; i < MAX_SCAN_DEVICE; i++)
            {
                if(connection_id == server_data_array[i].ble_connect_result.conn_id)
                {
                    i4_store_id = i;
                    break;
                }
            }
            int i4_cache_msd_len = strlen(server_data_array[i4_store_id].ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN);
            int i4_cache_tag_offset = i4_cache_msd_len - GATTC_EIR_MSD_FIX_LEN - 2;

            memset(&scan_ble_device, 0, sizeof(scan_ble_device));
            i_ret = a_cfg_get_blegatt_macaddress_threshold(scan_ble_device);
            BT_GATT_CHECK_FAIL(a_cfg_get_blegatt_macaddress_threshold,i_ret);
            CHAR c_mac_address[MAC_ADDRESS_LENGTH_LEN + 1] = {0};
            if(b_ios_device)
            {
                // For IOS device
                //memcpy(c_mac_address, server_data_array[i4_store_id].ios_uuid_scan + 20, MAC_ADDRESS_LENGTH_LEN);
                int j;
                for(i = 0, j = 0; j < MAC_ADDRESS_LENGTH_LEN + 1; j++)
                {
                    if(server_data_array[i4_store_id].ios_uuid_scan[19 + j] != '-')
                    {
                        c_mac_address[i++] = server_data_array[i4_store_id].ios_uuid_scan[19 + j];
                    }
                }
            }
            else
            {
                // For Android device
                memcpy(c_mac_address, server_data_array[i4_store_id].ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_cache_tag_offset - 12, MAC_ADDRESS_LENGTH_LEN);
            }

            for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
            {
                if (strncmp(scan_ble_device[i].c_mac_address, c_mac_address, MAC_ADDRESS_LENGTH_LEN) == 0)
                {
                    DBG_INFO(("<BT_GATT> Cached mac_address: %s, get target_ID: %d\r\n.", scan_ble_device[i].c_mac_address, scan_ble_device[i].ui_target_ID));
                    break;
                }
            }

            if (MAX_CACHE_BLE_NUMBER == i)
            {
                for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
                {
                    if(strncmp(scan_ble_device[i].c_mac_address, "000000000000", MAC_ADDRESS_LENGTH_LEN) == 0)
                    {
                        memcpy(scan_ble_device[i].c_mac_address, c_mac_address, MAC_ADDRESS_LENGTH_LEN);
                        scan_ble_device[i].c_mac_address[MAC_ADDRESS_LENGTH_LEN] = '\0';
                        DBG_INFO(("<BT_GATT> mac_address: %s, get target_ID: %d\r\n.", scan_ble_device[i].c_mac_address, scan_ble_device[i].ui_target_ID));

                        scan_ble_device[i].ui_target_ID = i4_new_target;
                        scan_ble_device[i].b_is_IOS = b_ios_device == TRUE ? TRUE : FALSE;

                        if (scan_ble_device[i].b_is_IOS == TRUE)//for uuid, no need to reverse MAC
                        {
                            DBG_LOG_PRINT(("%s() %d: ==========\n",__FUNCTION__,__LINE__));
                            bluetooth_gatt_add_scan_filter(
                                WAKE_SF_TYPE_PAIRED_IOS,
                                scan_ble_device[i].ui_target_ID,
                                scan_ble_device[i].c_mac_address);
                        }
                        else
                        {
                            bluetooth_gatt_add_scan_filter_data_reverse(
                                WAKE_SF_TYPE_PAIRED_ANDROID_08X,
                                scan_ble_device[i].ui_target_ID,
                                scan_ble_device[i].c_mac_address);
                        }
                        break;
                    }
                }
            }
            else
            {
                DBG_INFO(("<BT_GATT> cached mac_address: %s, get target_ID: %d-->%d\r\n.",
                                                        scan_ble_device[i].c_mac_address,
                                                        scan_ble_device[i].ui_target_ID,
                                                        i4_new_target));

                scan_ble_device[i].ui_target_ID = i4_new_target;
                scan_ble_device[i].b_is_IOS = b_ios_device == TRUE ? TRUE : FALSE;
                i_ret = a_cfg_set_blegatt_macaddress_threshold(scan_ble_device);
                BT_GATT_CHECK_FAIL(a_cfg_set_blegatt_macaddress_threshold,i_ret);

                bluetooth_gatt_modify_scan_filter_data_reverse(scan_ble_device[i].ui_target_ID,
                                                scan_ble_device[i].c_mac_address,
                                                scan_ble_device[i].b_is_IOS);
            }

            b_cache_full = (i == MAX_CACHE_BLE_NUMBER) ? TRUE : FALSE; //(i == MAX_CACHE_BLE_NUMBER - 1) ? TRUE : FALSE;
            i_ret = a_cfg_set_blegatt_macaddress_threshold(scan_ble_device);
            BT_GATT_CHECK_FAIL(a_cfg_set_blegatt_macaddress_threshold,i_ret);

            return;
        }
        else if(notify_c0_result.i_message_type == 0x12)
        {
            if(b_ios_device)
            {
                // For IOS device
                DBG_ERROR(("<BT_GATT> Need disconnect from iOS server.\n"));
                for(i = 0; i < MAX_SCAN_DEVICE; i++)
                {
                    if(connection_id == server_data_array[i].ble_connect_result.conn_id)
                    {
                        break;
                    }
                }
                a_mtkapi_bt_gattc_close(server_data_array[i].ble_connect_result.client_if,
                                       server_data_array[i].ble_connect_result.btaddr,
                                       server_data_array[i].ble_connect_result.conn_id);
            }
        }

        // justify which message type is
        if(notify_c0_result.i2_total_length)
        {
            for(i = 0; i < MAX_SCAN_DEVICE; i++)
            {
                if(connection_id == server_data_array[i].ble_connect_result.conn_id)
                {
                    read_id = i;
                    break;
                }
            }

            //DBG_INFO(("<BT_GATT> read_id = %d\r\n", read_id));
            server_data_array[read_id].request_msg = NULL;
            server_data_array[read_id].ui4_request_msg_len = 0;
            memset(&(server_data_array[read_id].ble_read_result), 0, sizeof(BT_GATTC_READ_CHAR_RST_T));
            server_data_array[read_id].i_read_char_number = 1;
            memset(&(server_data_array[read_id].c0_header), 0, sizeof(C0_HEADER));
            memcpy(&(server_data_array[read_id].c0_header), &notify_c0_result, sizeof(C0_HEADER));

            // use char c0 to start read data
            int receive_conn_id = server_data_array[read_id].ble_char_result_array[1].conn_id;
            //int receive_char_inst_id = server_data_array[read_id].ble_char_result_array[1].char_id.inst_id;
            int receive_char_inst_id = server_data_array[read_id].aui4_char_result_handle[1];
            DBG_INFO(("<BT_GATT>%d:receive_conn_id=%d, receive_char_inst_id=%d",__LINE__,receive_conn_id, receive_char_inst_id));

            // call read char function
            i_ret = a_mtkapi_bt_gattc_read_char(receive_conn_id, receive_char_inst_id/*Equal to char-handle*/, 0);
            BT_GATT_CHECK_FAIL(a_mtkapi_bt_gattc_read_char,i_ret);
        }
    }

    return;
}

// get read char result from mw
VOID _bt_gattc_read_char_result_cb(BT_GATTC_READ_CHAR_RST_T *pt_read_char, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();
    int i = 0;
    static int read_connection_id = 0;
    static int read_scan_number = 0;

    if(pt_read_char != NULL)
    {
        // print read char information
        read_connection_id = pt_read_char->conn_id;
        for(i = 0; i < MAX_SCAN_DEVICE; i++)
        {
            if(read_connection_id == server_data_array[i].ble_connect_result.conn_id)
            {
                read_scan_number = i;
                break;
            }
        }

        memcpy(&(server_data_array[read_scan_number].ble_read_result), pt_read_char, sizeof(BT_GATTC_READ_CHAR_RST_T));// save it to ble_read_result

        // send msg to gatt app self
        BT_GATT_MSG_T t_msg = {0};

        t_msg.ui4_msg_id    = BT_GATT_MSG_INTRA;
        t_msg.ui4_data1     = BT_GATT_READ_CHAR_CB;
        t_msg.ui4_data2     = read_scan_number;
        //t_msg.ui4_data3     = i_read_scan_number;
        bt_gatt_send_msg(BT_GATT_MSG_INTRA, &t_msg);
    }

    return;
}

// get read desc result from mw
VOID _bt_gattc_read_desc_result_cb(BT_GATTC_READ_DESCR_RST_T *pt_read_desc, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();
    return;
}

// get write char result from mw
VOID _bt_gattc_write_char_result_cb(BT_GATTC_WRITE_CHAR_RST_T *pt_write_char, void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();
    int i = 0;
    static int write_connection_id = 0;
    static int write_scan_number = 0;

    if(pt_write_char != NULL)
    {
        write_connection_id = pt_write_char->conn_id;
        for(i = 0; i < MAX_SCAN_DEVICE; i++)
        {
            if(write_connection_id == server_data_array[i].ble_connect_result.conn_id)
            {
                write_scan_number = i;
                break;
            }
        }

        memcpy(&(server_data_array[write_scan_number].ble_write_result), pt_write_char, sizeof(BT_GATTC_WRITE_CHAR_RST_T));
        server_data_array[write_scan_number].i_write_char_number++;

        // send msg to gatt app self
        BT_GATT_MSG_T t_msg = {0};

        t_msg.ui4_msg_id    = BT_GATT_MSG_INTRA;
        t_msg.ui4_data1     = BT_GATT_WRITE_CHAR_CB;
        t_msg.ui4_data2     = write_scan_number;
        bt_gatt_send_msg(BT_GATT_MSG_INTRA, &t_msg);
    }

    return;
}

// get write desc result from mw
VOID _bt_gattc_write_desc_result_cb(BT_GATTC_WRITE_DESCR_RST_T *pt_write_desc,void* pv_tag)
{
    BT_GATT_ENTER_FUNCTION();

    if(pt_write_desc != NULL)
    {
        // send msg to gatt app self
        BT_GATT_MSG_T t_msg = {0};

        t_msg.ui4_msg_id    = BT_GATT_MSG_INTRA;
        t_msg.ui4_data1     = BT_GATT_WRITE_DESC_CB;
        t_msg.ui4_data3     = pt_write_desc;
        bt_gatt_send_msg(BT_GATT_MSG_INTRA, &t_msg);

    }

    return;
}

VOID _bt_gatt_get_gatt_db_cb(BT_GATTC_GET_GATT_DB_T *pt_get_gatt_db_result,void* pv_tag)
{
    int i = 0;
    SIZE_T z_size = 0;
    BT_GATTC_DB_ELEMENT_T *pt_element_ptr = NULL;

    z_size = pt_get_gatt_db_result->count * sizeof(BT_GATTC_DB_ELEMENT_T);
    DBG_INFO(("<BT_GATT> %s(), count =%ld, z_size=0x%x\n", __func__, (long)pt_get_gatt_db_result->count, z_size));

    if (pt_get_gatt_db_result->count == 0)
    {
        DBG_ERROR(("<BT_GATT>%s() get gatt db count=0.\n", __FUNCTION__));
        return;
    }

    pt_element_ptr = (BT_GATTC_DB_ELEMENT_T *)c_mem_alloc(z_size);
    if (NULL == pt_element_ptr)
    {
        DBG_ERROR(("<BT_GATT>%s() Alloc memory fail.\n", __FUNCTION__));
        return;
    }

    c_memcpy(pt_element_ptr, pt_get_gatt_db_result->gatt_db_element, z_size);

    for (i = 0; i < MAX_SCAN_DEVICE; i++)
    {
        if (pt_get_gatt_db_result->conn_id == server_data_array[i].ble_connect_result.conn_id)
        {
            break;
        }
    }

    DBG_INFO(("<BT_GATT> %s(),i=%d, count =%ld, conn_id=%d\n", __func__, i,
                                                    (long)pt_get_gatt_db_result->count,
                                                    pt_get_gatt_db_result->conn_id));

    server_data_array[i].t_gatt_db.conn_id = pt_get_gatt_db_result->conn_id;
    server_data_array[i].t_gatt_db.count = pt_get_gatt_db_result->count;
    if (server_data_array[i].t_gatt_db.gatt_db_element != NULL)
    {
        c_mem_free(server_data_array[i].t_gatt_db.gatt_db_element);
        server_data_array[i].t_gatt_db.gatt_db_element = NULL;
    }
    server_data_array[i].t_gatt_db.gatt_db_element = pt_element_ptr;

    BT_GATT_MSG_T t_msg = {0};

    t_msg.ui4_msg_id    = BT_GATT_MSG_INTRA;
    t_msg.ui4_data1     = BT_GATT_GET_DB_CB;
    t_msg.ui4_data2     = i;
    bt_gatt_send_msg(BT_GATT_MSG_INTRA, &t_msg);

    return;
}

VOID _bt_gattc_play_audio_tone(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    UINT16          ui2_status = 0;

    if (i4_target_id != 0)
    {
        DBG_INFO(("<BT_GATT> target id %d!=0, not play audio tone.\n",i4_target_id));
        return;
    }
    if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
    {
        if (WZD_UTIL_GET_STATUS_STATE(ui2_status) != WZD_STATE_RESUME_C4TV)
        {
            a_revolt_info_play_audio_tone();
        }
    }

    return;
}

VOID _bt_gattc_rssi_meter_notify(T_RSSI_NOTIFY_MSG *pt_nfy_msg)
{
    BT_GATT_ENTER_FUNCTION();

    if(pt_nfy_msg != NULL && pt_nfy_msg->b_signal_meter)
    {
        /* Free it after processed this message */
        T_RSSI_NOTIFY_MSG *pt_rssi_notify_msg = NULL;
        pt_rssi_notify_msg = (T_RSSI_NOTIFY_MSG *)c_mem_alloc(sizeof(T_RSSI_NOTIFY_MSG));

        if (NULL == pt_rssi_notify_msg)
        {
            DBG_LOG_PRINT(("<BT_GATT> _bt_gattc_rssi_meter_notify alloc memory fail!\n"));
            return;
        }

        DBG_INFO(("<BT_GATT> rssi meter notify to show UI.\r\n"));
        c_memcpy(pt_rssi_notify_msg, pt_nfy_msg, sizeof(T_RSSI_NOTIFY_MSG));

        // send msg to gatt app self
        BT_GATT_MSG_T t_msg = {0};

        t_msg.ui4_msg_id    = BT_GATT_MSG_RSSI_METER;
        t_msg.ui4_data1     = pt_rssi_notify_msg->e_status;
        t_msg.ui4_data2     = pt_rssi_notify_msg->i4_rssi;
        t_msg.ui4_data3     = pt_rssi_notify_msg;
        bt_gatt_send_msg(BT_GATT_MSG_RSSI_METER, &t_msg);
    }

    return;
}

static VOID _bt_gattc_set_rssi_meter_data(int rssi, INT32 i4_get_rssi_threshold, CHAR *c_mac_addr)
{
    t_rssi_meter_nfy.b_signal_meter = TRUE;
    t_rssi_meter_nfy.i4_rssi = rssi;

    if (0 == t_rssi_meter_nfy.i4_min_rssi_threshold
        && 0 == t_rssi_meter_nfy.i4_max_rssi_threshold)
    {
        t_rssi_meter_nfy.i4_min_rssi_threshold = i4_get_rssi_threshold;
    }

    if (c_strlen(t_rssi_meter_nfy.c_mac_addr) == 0
        || c_strncmp(t_rssi_meter_nfy.c_mac_addr, "000000000000", MAC_ADDRESS_LENGTH_LEN) == 0)
    {
        c_memcpy(t_rssi_meter_nfy.c_mac_addr, c_mac_addr, MAC_ADDRESS_LENGTH_LEN);
        t_rssi_meter_nfy.i4_countdown = t_rssi_meter_nfy.i4_min_consecutive;
    }

    if (rssi < i4_get_rssi_threshold)
    {
        DBG_INFO(("<BT_GATT>  rssi meter status to RED\r\n"));
        t_rssi_meter_nfy.e_status = E_RSSI_RED;
        t_rssi_meter_nfy.i4_consecutive = 0;
        t_rssi_meter_nfy.i4_countdown = t_rssi_meter_nfy.i4_min_consecutive;
    }
    else
    {
        t_rssi_meter_nfy.i4_consecutive++;
        if (t_rssi_meter_nfy.i4_min_consecutive != 0)
        {
            t_rssi_meter_nfy.e_status = (t_rssi_meter_nfy.i4_consecutive >= t_rssi_meter_nfy.i4_min_consecutive) \
                                        ? E_RSSI_GREEN : E_RSSI_YELLOW;
        }
        else
        {
            t_rssi_meter_nfy.e_status = E_RSSI_GREEN;
        }

        if (t_rssi_meter_nfy.i4_countdown != 0)
        {
            t_rssi_meter_nfy.i4_countdown--;
        }

        DBG_INFO(("<BT_GATT>  rssi meter status to %d\r\n", t_rssi_meter_nfy.e_status));
    }

    c_memset(t_rssi_meter_nfy.s_name, 0, sizeof(t_rssi_meter_nfy.s_name));

    BT_LOCAL_DEV dev_info;

    c_memset(&dev_info,0,sizeof(dev_info));
    a_mtkapi_bt_gap_get_local_dev_info(&dev_info);
    c_strcpy(t_rssi_meter_nfy.s_name,dev_info.name);

    if (c_mac_addr != NULL
        && c_strncmp(t_rssi_meter_nfy.c_mac_addr, c_mac_addr, MAC_ADDRESS_LENGTH_LEN) == 0)
    {
        DBG_INFO(("<BT_GATT> rssi meter notify.\r\n"));
        _bt_gattc_rssi_meter_notify(&t_rssi_meter_nfy);
    }

    return;
}

static BOOL _bt_gattc_allow_special_device_4_test(BOOL b_allow_pair, BOOL b_cache_mac, INT32 i4_target_ID)
{
    if (b_always_allow_test_tool_pair
        && (b_allow_pair && (i4_target_ID == 1))) // for TestBLE
    {
        return TRUE;
    }

    return FALSE;
}

static INT32 _bt_gattc_search_serivce(UINT32 ui4_srv_idx)
{
    UINT32  ui4_i = 0;
    BT_GATTC_GET_GATT_DB_T *pt_gatt_db = NULL;
    BT_GATTC_DB_ELEMENT_T *pt_db_elem = NULL;
    BT_GATTC_SEARCH_RST_T   t_service_rst = {0};

    BT_GATT_ENTER_FUNCTION();

    if (ui4_srv_idx >= MAX_SCAN_DEVICE)
    {
        DBG_ERROR(("<BT_GATT> search service with idx=%d fail\n",ui4_srv_idx));
        return BLUETOOTH_GATTC_FAILED;
    }

    pt_gatt_db = &server_data_array[ui4_srv_idx].t_gatt_db;
    if (NULL == pt_gatt_db->gatt_db_element)
    {
        DBG_ERROR(("<BT_GATT> db_element is NULL\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    for (ui4_i = 0; ui4_i < pt_gatt_db->count; ui4_i++)
    {
        pt_db_elem = &pt_gatt_db->gatt_db_element[ui4_i];
        if (BT_GATTC_DB_PRIMARY_SERVICE == pt_db_elem->type||
            BT_GATTC_DB_SECONDARY_SERVICE == pt_db_elem->type)
        {
            DBG_INFO(("<BT_GATT>_bt_gattc_search_serivce() uuid=[%s] is_primary=%d\n",
                                                                    pt_db_elem->uuid,
                                                                    (BT_GATTC_DB_PRIMARY_SERVICE == pt_db_elem->type)));
            t_service_rst.conn_id = pt_gatt_db->conn_id;
            t_service_rst.srvc_id.id.inst_id = pt_db_elem->id;
            c_strncpy(t_service_rst.srvc_id.id.uuid, pt_db_elem->uuid, BT_GATT_MAX_UUID_LEN);
            t_service_rst.srvc_id.is_primary = (BT_GATTC_DB_PRIMARY_SERVICE == pt_db_elem->type) ? TRUE : FALSE;

          //  _bt_gattc_search_service_result_cb(&t_service_rst);
        }
    }

    BT_GATT_EXTI_FUNCTION();
    return BLUETOOTH_GATTC_OK;
}

static INT32 _bt_gattc_get_char_handle(INT32 i4_conn_id, CHAR* uuid, HANDLE_T *ph_handle, UINT8 ui1_get_type)
{
    UINT32  i = 0;
    UINT32  j = 0;
    INT32   i4_ret = BLUETOOTH_GATTC_FAILED;
    BT_GATTC_DB_ELEMENT_T *pt_db_elem = NULL;
    BOOL    b_srv_match = FALSE;

    BT_GATT_ENTER_FUNCTION();

    if (ui1_get_type >= _BT_GATTC_GET_TYPE_LAST)
    {
        DBG_ERROR(("<BT_GATT> _bt_gattc_get_char_handle() Incorrect ui1_get_type=%d.\r\n", ui1_get_type));
        return i4_ret;
    }

    for(i = 0; i < MAX_SCAN_DEVICE; i++)
    {
        if(i4_conn_id == server_data_array[i].ble_connect_result.conn_id)
        {
            DBG_INFO(("<BT_GATT> _bt_gattc_get_char_handle() found i4_conn_id = %d uuid=[%s].\r\n", i4_conn_id,uuid));

            pt_db_elem = server_data_array[i].t_gatt_db.gatt_db_element;

            if (NULL == pt_db_elem)
            {
                DBG_ERROR(("<BT_GATT> %d:db_element is NULL\n", __LINE__));
                return BLUETOOTH_GATTC_FAILED;
            }

            for (j = 0; j < server_data_array[i].t_gatt_db.count; j++)
            {
                if (b_srv_match == FALSE)
                {
                    if ((BT_GATTC_DB_PRIMARY_SERVICE == pt_db_elem[j].type ||
                         BT_GATTC_DB_SECONDARY_SERVICE == pt_db_elem[j].type)
                        && c_strcmp(server_data_array[i].ble_service_result.srvc_id.id.uuid, pt_db_elem[j].uuid) == 0)
                    {
                        b_srv_match = TRUE;
                    }
                    continue;
                }

                if (_BT_GATTC_GET_TYPE_CHAR == ui1_get_type)
                {
                    if ((/*(strcmp(pt_db[j].uuid, GATTC_CHAR_C255_UUID) == 0)
                            || (strcmp(pt_db[j].uuid, GATTC_CHAR_C80_UUID) == 0)
                            || */(BT_GATTC_DB_CHARACTERISTIC == pt_db_elem[j].type))
                        && (c_strcmp(pt_db_elem[j].uuid, uuid) == 0))
                    {
                        *ph_handle = pt_db_elem[j].attribute_handle;
                        i4_ret = BLUETOOTH_GATTC_OK;

                        DBG_INFO(("<BT_GATT> _bt_gattc_get_char_handle() found char hanle=%d.\r\n", *ph_handle));
                        break;
                    }
                }

                if (_BT_GATTC_GET_TYPE_DESC == ui1_get_type)
                {
                    if (BT_GATTC_DB_DESCRIPTOR == pt_db_elem[j].type
                        && c_strcmp(pt_db_elem[j].uuid, uuid) == 0)
                    {
                        *ph_handle = pt_db_elem[j].attribute_handle;
                        i4_ret = BLUETOOTH_GATTC_OK;

                        DBG_INFO(("<BT_GATT> _bt_gattc_get_char_handle() found desc hanle=0x%x.\r\n", *ph_handle));
                        break;
                    }
                }
            }
            break;
        }
    }

    if (i4_ret != BLUETOOTH_GATTC_OK)
    {
        DBG_ERROR(("<BT_GATT> _bt_gattc_get_char_handle() get handle fail i4_ret=%d.\r\n", i4_ret));
    }

    BT_GATT_EXTI_FUNCTION();
    return i4_ret;
}

static INT32 _bt_gattc_get_char(UINT32 ui4_search_index)
{
    BOOL    b_service_match = FALSE;
    UINT32  ui4_i = 0;
    UINT32  ui4_count = 0;
    BT_GATTC_GET_GATT_DB_T *pt_gatt_db = NULL;
    BT_GATTC_DB_ELEMENT_T  *pt_db_elem = NULL;

    BT_GATTC_GET_CHAR_RST_T     t_char_rst = {0};

    UINT8   ui1_get_char_num = server_data_array[ui4_search_index].i_get_char_number;

    BT_GATT_ENTER_FUNCTION();

    if (ui4_search_index >= MAX_SCAN_DEVICE)
    {
        DBG_ERROR(("<BT_GATT>_bt_gattc_get_char() Invalid arg\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    b_service_match = server_data_array[ui4_search_index].ui4_gatt_db_loop_idx == 0 ? FALSE : TRUE;
    ui4_i = server_data_array[ui4_search_index].ui4_gatt_db_loop_idx;

    DBG_INFO(("<BT_GATT>_bt_gattc_get_char() ui4_i=%d, srv_idx=%d,ui1_get_char_num=%d\n",
                                                                        ui4_i,
                                                                        ui4_search_index,
                                                                        ui1_get_char_num));

    pt_gatt_db = &server_data_array[ui4_search_index].t_gatt_db;
    ui4_count = pt_gatt_db->count;

    if (NULL == pt_gatt_db->gatt_db_element)
    {
        DBG_ERROR(("<BT_GATT> %d:db_element is NULL\n", __LINE__));
        return BLUETOOTH_GATTC_FAILED;
    }

    for (; ui4_i < ui4_count; ui4_i++)
    {
        pt_db_elem = &pt_gatt_db->gatt_db_element[ui4_i];

        if (!b_service_match)
        {
            if ((BT_GATTC_DB_PRIMARY_SERVICE   == pt_db_elem->type||
                 BT_GATTC_DB_SECONDARY_SERVICE == pt_db_elem->type)
                && c_strcmp(server_data_array[ui4_search_index].ble_service_result.srvc_id.id.uuid, pt_db_elem->uuid) == 0)
            {
                b_service_match = TRUE;
            }
            continue;
        }

        if (BT_GATTC_DB_CHARACTERISTIC == pt_db_elem->type
            || (c_strcmp(pt_db_elem->uuid, GATTC_CHAR_C255_UUID) == 0)
            || (c_strcmp(pt_db_elem->uuid, GATTC_CHAR_C80_UUID) == 0))
        {
            t_char_rst.conn_id = server_data_array[ui4_search_index].ble_service_result.conn_id;
            t_char_rst.char_prop = pt_db_elem->properties;

            c_strncpy(t_char_rst.srvc_id.id.uuid , server_data_array[ui4_search_index].ble_service_result.srvc_id.id.uuid, BT_GATT_MAX_UUID_LEN);
            t_char_rst.srvc_id.id.inst_id = server_data_array[ui4_search_index].ble_service_result.srvc_id.id.inst_id;
            t_char_rst.srvc_id.is_primary =  server_data_array[ui4_search_index].ble_service_result.srvc_id.is_primary;

            c_strncpy(t_char_rst.char_id.uuid , pt_db_elem->uuid, BT_GATT_MAX_UUID_LEN);
            t_char_rst.char_id.inst_id = ui4_search_index; //inst_id indicate app client num

      //      _bt_gattc_get_char_result_cb(&t_char_rst);
            if (ui1_get_char_num < server_data_array[ui4_search_index].i_get_char_number)
            {
                //process current char, next char will be process after call _bt_gattc_get_char again.
                server_data_array[ui4_search_index].aui4_char_result_handle[server_data_array[ui4_search_index].i_get_char_out] = pt_db_elem->attribute_handle;
                break;
            }
        }
    }
    server_data_array[ui4_search_index].ui4_gatt_db_loop_idx = (ui4_i+1 >= ui4_count) ? 0 : ui4_i+1;

    BT_GATT_EXTI_FUNCTION();
    return BLUETOOTH_GATTC_OK;
}

static INT32 _bt_gattc_get_descr(UINT32 ui4_conn_id, HANDLE_T h_handle)
{
    UINT32  ui4_i = 0;
    UINT32  ui4_srv_i = 0;
    UINT32  ui4_count = 0;
    BOOL    b_found = FALSE;
    BOOL    b_service_match = FALSE;
    BOOL    b_char_match = FALSE;
    UINT32  ui4_get_desc_num = 0;;

    BT_GATTC_GET_GATT_DB_T      *pt_gatt_db = NULL;
    BT_GATTC_DB_ELEMENT_T       *pt_db_elem = NULL;
    BT_GATTC_GET_DESCR_RST_T    t_desc_rst = {0};

    BT_GATT_ENTER_FUNCTION();

    DBG_INFO(("<BT_GATT>_bt_gattc_get_descr() ui4_conn_id=%d,h_handle=%d\n", ui4_conn_id, h_handle));

    for (ui4_srv_i = 0; ui4_srv_i < MAX_SCAN_DEVICE; ui4_srv_i++)
    {
        if (ui4_conn_id == server_data_array[ui4_srv_i].ble_connect_result.conn_id)
        {
            b_found = TRUE;
            break;
        }
    }

    if (b_found)
    {
        pt_gatt_db          = &server_data_array[ui4_srv_i].t_gatt_db;
        ui4_count           = pt_gatt_db->count;
        ui4_get_desc_num    = 0;

        if (0 == ui4_count || NULL == pt_gatt_db->gatt_db_element)
        {
            DBG_ERROR(("<BT_GATT> %d:db_element is Empty!!\n", __LINE__));
            return BLUETOOTH_GATTC_FAILED;
        }

        for (ui4_i = 0; ui4_i < ui4_count; ui4_i++)
        {
            pt_db_elem = &pt_gatt_db->gatt_db_element[ui4_i];

            if (!b_service_match)
            {
                if ((BT_GATTC_DB_PRIMARY_SERVICE == pt_db_elem->type||
                     BT_GATTC_DB_SECONDARY_SERVICE == pt_db_elem->type)
                    && c_strcmp(server_data_array[ui4_srv_i].ble_service_result.srvc_id.id.uuid, pt_db_elem->uuid) == 0)
                {
                    DBG_INFO(("<BT_GATT>_bt_gattc_get_descr() found service_uuid[%s]\n", pt_db_elem->uuid));

                    b_service_match = TRUE;

                    c_strncpy(t_desc_rst.srvc_id.id.uuid, pt_db_elem->uuid, BT_GATT_MAX_UUID_LEN);
                    t_desc_rst.srvc_id.id.inst_id = pt_db_elem->id;
                    t_desc_rst.srvc_id.is_primary = (pt_db_elem->type == BT_GATTC_DB_PRIMARY_SERVICE) ? TRUE : FALSE;
                }
                continue;
            }

            if (!b_char_match)
            {
                if (BT_GATTC_DB_CHARACTERISTIC == pt_db_elem->type
                    && h_handle == pt_db_elem->attribute_handle)
                {
                    DBG_INFO(("<BT_GATT>_bt_gattc_get_descr() found char_uuid[%s]\n", pt_db_elem->uuid));

                    b_char_match = TRUE;
                    t_desc_rst.conn_id = ui4_conn_id;
                    c_strncpy(t_desc_rst.char_id.uuid, pt_db_elem->uuid, BT_GATT_MAX_UUID_LEN);
                    t_desc_rst.char_id.inst_id = pt_db_elem->id;
                }
                continue;
            }

            if (BT_GATTC_DB_DESCRIPTOR == pt_db_elem->type)
            {
                if (ui4_get_desc_num < server_data_array[ui4_srv_i].ui4_get_desc_num)
                {
                    ui4_get_desc_num++;
                    continue;
                }

                if((strncmp(pt_db_elem->uuid + 4, "2902", 4) == 0)
                    && (strncmp(t_desc_rst.srvc_id.id.uuid, GATTC_SERVICE_UUID, 8) == 0))
                {
                    DBG_INFO(("<BT_GATT>_bt_gattc_get_descr() found desc_uuid[%s] id=%d conn_id=%d\n",
                                                                                    pt_db_elem->uuid,
                                                                                    pt_db_elem->id,
                                                                                    t_desc_rst.conn_id));

                    c_strncpy(t_desc_rst.descr_id.uuid, pt_db_elem->uuid, BT_GATT_MAX_UUID_LEN);
                    t_desc_rst.descr_id.inst_id = pt_db_elem->id;

                    server_data_array[ui4_srv_i].ui4_get_desc_num++;

                //    _bt_gattc_get_desc_result_cb(&t_desc_rst);

                    break;
                }
                else
                    continue;
            }
        }
    }

    BT_GATT_EXTI_FUNCTION();
    return BLUETOOTH_GATTC_OK;
}

/***********************************************************************************************/
// scan cli
INT32 bluetooth_gatt_scan_device_cli(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;

    // from the beginning, so all parameters are initialized

    i_scan_number = 0;
    memset(server_data_array, 0, sizeof(GATT_SERVER_DATA) * MAX_SCAN_DEVICE);

    // call scan function
    i_ret = a_mtkapi_bt_gattc_scan();
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_scan,i_ret);

    return BLUETOOTH_GATTC_OK;
}

// set_rssi cli
INT32 bluetooth_gatt_set_rssi_cli(int rssi_threshold)
{
#ifdef APP_BLE_SUPPORT
    BT_GATT_ENTER_FUNCTION();
    INT32 i_ret;

    // set rssi threshold, scan rssi need larger than i4_set_rssi_threshold
    i_ret = a_cfg_set_blegatt_rssi_threshold(rssi_threshold);
    BT_GATT_CHECK_FAIL_RET(a_cfg_set_blegatt_rssi_threshold,i_ret);
    DBG_ERROR(("<BT_GATT> rssi_threshold = %d\r\n", rssi_threshold));
#else
   DBG_ERROR(("<BT_GATT> APP_BLE_SUPPORT undefined\r\n"));
#endif
    return BLUETOOTH_GATTC_OK;
}

// get_rssi cli
INT32 bluetooth_gatt_get_rssi_cli(VOID)
{
#ifdef APP_BLE_SUPPORT
    BT_GATT_ENTER_FUNCTION();
    INT32 i_ret;
    INT32 i4_get_rssi_threshold = 0;

    i_ret = a_cfg_get_blegatt_rssi_threshold(&i4_get_rssi_threshold);
    BT_GATT_CHECK_FAIL_RET(a_cfg_get_blegatt_rssi_threshold,i_ret);
    DBG_ERROR(("<BT_GATT> get rssi threshold = %d\r\n.", i4_get_rssi_threshold));
#else
   DBG_ERROR(("<BT_GATT> APP_BLE_SUPPORT undefined\r\n"));
#endif
    return BLUETOOTH_GATTC_OK;
}

// stop_scan cli
INT32 bluetooth_gatt_stop_scan_cli(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;

    // call stop scan function
    i_ret = a_mtkapi_bt_gattc_stop_scan();
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_stop_scan,i_ret);

    return BLUETOOTH_GATTC_OK;
}

// connect cli
INT32 bluetooth_gatt_get_put_cli(const char *url_json)
{
    BT_GATT_ENTER_FUNCTION();

        int i_count = 0;
        char *url = NULL;
        char *json_data = NULL;
        int get_response_type = 0;
        int write_number = 0;
        int offset = 0;
        INT32 i_ret;
        uint8_t c_check_sum;
        int send_conn_id;
        //int send_service_inst_id;
        INT32 send_char_inst_id;

        int pre_url_len = strlen(GATTC_PRE_REQUEST_IP);
        int url_json_len = strlen(url_json);
        DBG_ERROR(("<BT_GATT> url_json = %s\n", url_json));
        DBG_ERROR(("<BT_GATT> url_json_len = %d\n", url_json_len));
        int msg_len = server_data_array[write_number].ui4_request_msg_len = pre_url_len + url_json_len;

        BT_GATT_FREE(server_data_array[write_number].request_msg);
        BT_GATT_MALLOC(server_data_array[write_number].request_msg, server_data_array[write_number].ui4_request_msg_len + 1);
        memset(server_data_array[write_number].request_msg, 0, server_data_array[write_number].ui4_request_msg_len + 1);

        memcpy(server_data_array[write_number].request_msg, GATTC_PRE_REQUEST_IP, pre_url_len);
        memcpy(server_data_array[write_number].request_msg + pre_url_len, url_json, url_json_len);
        server_data_array[write_number].request_msg[msg_len] = '\0';

        DBG_ERROR(("<BT_GATT> server_data_array[write_number].request_msg = %s\n", server_data_array[write_number].request_msg));
        DBG_ERROR(("<BT_GATT> server_data_array[write_number].ui4_request_msg_len = %d\n", server_data_array[write_number].ui4_request_msg_len));

        for(i_count = 0; i_count < server_data_array[write_number].ui4_request_msg_len; i_count++)
        {
            if(server_data_array[write_number].request_msg[i_count] == '{')
            {
                offset = i_count;
                if(server_data_array[write_number].request_msg[i_count + 1] != '\0' && server_data_array[write_number].request_msg[i_count + 1] != '}')
                {
                    get_response_type = 1;
                    break;
                }
            }
        }

        DBG_ERROR(("<BT_GATT> offset = %d\n", offset));

        if(get_response_type == 0)// get command
        {
            if(offset == 0)
            {
                url = server_data_array[write_number].request_msg;
                DBG_ERROR(("<BT_GATT> url = %s\n", url));
            }
            else
            {
                server_data_array[write_number].request_msg[offset] = '\0';
                server_data_array[write_number].request_msg[offset + 1] = '\0';
                url = server_data_array[write_number].request_msg;
                //url = (char*)malloc(offset);
                //memset(url, 0, offset);
                //memcpy(url, server_data_array[write_number].request_msg, offset);
                //url[offset] = '\0';
                DBG_ERROR(("<BT_GATT> url = %s\n", url));
            }

            _bt_url_get_response(url, 0);

        }
        else if(get_response_type == 1)// put command
        {
            // add url header
            BT_GATT_MALLOC(url, offset + 1);
            BT_GATT_MALLOC(json_data, server_data_array[write_number].ui4_request_msg_len - offset + 1);
            memset(url, 0, offset + 1);
            memset(json_data, 0, server_data_array[write_number].ui4_request_msg_len - offset + 1);
            memcpy(url, server_data_array[write_number].request_msg, offset);
            url[offset] = '\0';
            memcpy(json_data, server_data_array[write_number].request_msg + offset, server_data_array[write_number].ui4_request_msg_len - offset);
            json_data[server_data_array[write_number].ui4_request_msg_len - offset] = '\0';
            DBG_ERROR(("<BT_GATT> url = %s\n", url));
            DBG_ERROR(("<BT_GATT> json_data = %s\n", json_data));

            _bt_url_put_response(url, json_data, 0);

            BT_GATT_FREE(url);
            BT_GATT_FREE(json_data);
        }

        BT_GATT_FREE(server_data_array[write_number].request_msg);

    // msg payload  XOR operation
    DBG_ERROR(("<BT_GATT> response_msg is %s\n ", server_data_array[write_number].response_msg));
    DBG_ERROR(("<BT_GATT> response_msg length is %d\n ", server_data_array[write_number].ui4_response_msg_len));

    c_check_sum = 0x00;
    for(i_count = 0; i_count < server_data_array[write_number].ui4_response_msg_len; i_count++)
    {
        c_check_sum ^= server_data_array[write_number].response_msg[i_count];
    }

    // C0 XOR opration except c_check_sum
    uint8_t c0_header_value[MAX_CHARACTERISTIC_LIMIT];
    memset(c0_header_value, 0, MAX_CHARACTERISTIC_LIMIT);
    c0_header_value[0] = 0x00;
    c0_header_value[1] = 0x00;
    int last_fragment_number = (server_data_array[write_number].ui4_response_msg_len) / MAX_FRAGMENT_LIMIT;
    int remain_flags = (server_data_array[write_number].ui4_response_msg_len) % MAX_FRAGMENT_LIMIT;
    if(0 != remain_flags)
    {
        last_fragment_number++;
    }
    c0_header_value[2] = (last_fragment_number -1) & 0xFF;
    c0_header_value[4] = (server_data_array[write_number].ui4_response_msg_len) & 0xFF;
    c0_header_value[5] = ((server_data_array[write_number].ui4_response_msg_len) >> 8) & 0xFF;

    server_data_array[write_number].ui4_response_code = 200;
    c0_header_value[6] = (server_data_array[write_number].ui4_response_code) & 0xFF;
    c0_header_value[7] = ((server_data_array[write_number].ui4_response_code) >> 8) & 0xFF;

    c0_header_value[8] = 0x05;
    for(i_count = 0; i_count < MAX_CHARACTERISTIC_LIMIT; i_count++)
    {
        c_check_sum ^= c0_header_value[i_count];
    }
    c0_header_value[9] = c_check_sum;

    //_bt_gattc_print_uint8(c0_header, 10, c_c0_header);
    DBG_INFO(("<BT_GATT> c0_header = "));
    for(i_count = 0; i_count < 10; i_count++)
    {
        DBG_INFO(("%02X", c0_header_value[i_count]));
        DBG_INFO(("-"));
    }
    DBG_INFO(("\r\n"));

    // copy paramters
    send_conn_id = server_data_array[write_number].ble_char_result_array[0].conn_id;
    send_char_inst_id = server_data_array[write_number].aui4_char_result_handle[0];
    //send_char_inst_id = server_data_array[write_number].ble_char_result_array[0].char_id.inst_id;

    // write msg header to c0
    i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id,
                                      send_char_inst_id, //equal to char handle
                                      i_write_type,
                                      MAX_CHARACTERISTIC_LIMIT,
                                      0,
                                      (char*)c0_header_value);
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);

    return BLUETOOTH_GATTC_OK;
}

INT32 bluetooth_gatt_get_response_cli(const char *dir_path)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;

    int read_bytes = 0;
    //int file_len = 0;
    int write_number = 0;
    int send_conn_id;
    //int send_service_inst_id;
    int send_char_inst_id;
    uint8_t c_check_sum;
    int i_count = 0;

    DBG_ERROR(("<BT_GATT> dir_path = %s\r\n", dir_path));
    char *response = malloc(1000);
    memset(response, 0, 1000);
    FILE* read_file = fopen(dir_path, "rb");
    if(NULL == read_file)
    {
        DBG_ERROR(("<BT_GATT> open file failed!\r\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    read_bytes = fread(response, 1, 1000, read_file);
    DBG_ERROR(("<BT_GATT> read_bytes = %d\r\n", read_bytes));
    if(read_bytes == 0)
    {
        DBG_ERROR(("<BT_GATT> read file failed!\r\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    DBG_ERROR(("<BT_GATT> response_msg = %s\r\n", response));
    server_data_array[write_number].ui4_response_msg_len = read_bytes;
    server_data_array[write_number].response_msg = response;

    c_check_sum = 0x00;
    for(i_count = 0; i_count < server_data_array[write_number].ui4_response_msg_len; i_count++)
    {
        c_check_sum ^= server_data_array[write_number].response_msg[i_count];
    }

    // C0 XOR opration except c_check_sum
    uint8_t c0_header_value[MAX_CHARACTERISTIC_LIMIT];
    memset(c0_header_value, 0, MAX_CHARACTERISTIC_LIMIT);
    c0_header_value[0] = 0x00;
    c0_header_value[1] = 0x00;
    int last_fragment_number = (server_data_array[write_number].ui4_response_msg_len) / MAX_FRAGMENT_LIMIT;
    int remain_flags = (server_data_array[write_number].ui4_response_msg_len) % MAX_FRAGMENT_LIMIT;
    if(0 != remain_flags)
    {
        last_fragment_number++;
    }
    c0_header_value[2] = (last_fragment_number -1) & 0xFF;
    c0_header_value[4] = (server_data_array[write_number].ui4_response_msg_len) & 0xFF;
    c0_header_value[5] = ((server_data_array[write_number].ui4_response_msg_len) >> 8) & 0xFF;

    server_data_array[write_number].ui4_response_code = 200;
    c0_header_value[6] = (server_data_array[write_number].ui4_response_code) & 0xFF;
    c0_header_value[7] = ((server_data_array[write_number].ui4_response_code) >> 8) & 0xFF;

    c0_header_value[8] = 0x05;
    for(i_count = 0; i_count < MAX_CHARACTERISTIC_LIMIT; i_count++)
    {
        c_check_sum ^= c0_header_value[i_count];
    }
    c0_header_value[9] = c_check_sum;

    //_bt_gattc_print_uint8(c0_header, 10, c_c0_header);
    DBG_INFO(("<BT_GATT> c0_header = "));
    for(i_count = 0; i_count < 10; i_count++)
    {
        DBG_INFO(("%02X", c0_header_value[i_count]));
        DBG_INFO(("-"));
    }
    DBG_INFO(("\r\n"));

    // copy paramters
    send_conn_id = server_data_array[write_number].ble_char_result_array[0].conn_id;
    //send_char_inst_id = server_data_array[write_number].ble_char_result_array[0].char_id.inst_id;
    send_char_inst_id = server_data_array[write_number].aui4_char_result_handle[0];

    // write msg header to c0
    i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id,
                                          send_char_inst_id, //equal to char handle
                                          i_write_type,
                                          MAX_CHARACTERISTIC_LIMIT,
                                          0,
                                          (char*)c0_header_value);
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);

    return BLUETOOTH_GATTC_OK;
}

INT32 bluetooth_gatt_write_data(int write_number)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;
    int i_count = 0;
    int send_conn_id;
    //int send_service_inst_id;
    int send_char_inst_id;
    // C0 XOR opration except c_check_sum
    uint8_t c0_header_value[MAX_CHARACTERISTIC_LIMIT];

    uint8_t c_check_sum;
    int get_response_type = 0;
    int offset = 0, i4_total_request_len = 0;
    char *url = NULL;
    char *json_data = NULL;

    server_data_array[write_number].i_write_char_number = 0;
    server_data_array[write_number].response_msg = NULL;
    server_data_array[write_number].i_fragment_number = 0;
    server_data_array[write_number].ui4_write_msg_len = 0;

/***********************************************************decrypt C0, C1, C2, C3...*************************************************************/
    // for BLE security
    uint8_t CTRs[AES_BLOCK_SIZE] = {0}, CTRc[AES_BLOCK_SIZE] = {0}, HCs[8] = {0}, HCc[8] = {0}, recv_LCn[4] = {0}, send_LCn[4] = {0};
    uint8_t input[AES_BLOCK_SIZE] = {0}, dec_out[AES_BLOCK_SIZE] = {0}, enc_out[AES_BLOCK_SIZE] = {0};
    char *receive_msg = NULL, *decrypt_msg = NULL, *encrypt_msg = NULL, *response_msg = NULL;
    UINT32 ui4_xsn = 0, ui4_recv_lcn = 0, ui4_send_lcn = 0, i4_rev_Cn_number = 0, i4_sed_Cn_number = 0;
    INT32 dec_len = 0, enc_len = 0;

    if(b_is_NS)
    {
        DBG_ERROR(("<BT_GATT> write Nc.\n"));
        BT_GATT_FREE(server_data_array[write_number].response_msg);
        BT_GATT_MALLOC(server_data_array[write_number].response_msg, AES_BLOCK_SIZE + 1);
        memcpy(server_data_array[write_number].response_msg, Nc, AES_BLOCK_SIZE);
        server_data_array[write_number].response_msg[AES_BLOCK_SIZE] = '\0';
        server_data_array[write_number].ui4_response_msg_len = AES_BLOCK_SIZE;

        c_check_sum = 0x00;
        for(i_count = 0; i_count < AES_BLOCK_SIZE; i_count++)
        {
            c_check_sum ^= Nc[i_count];
        }

        // C0 XOR opration except c_check_sum
        uint8_t c0_header_value[MAX_CHARACTERISTIC_LIMIT];
        memset(c0_header_value, 0, MAX_CHARACTERISTIC_LIMIT);
        c0_header_value[8] = 0x07;
        for(i_count = 0; i_count < MAX_CHARACTERISTIC_LIMIT; i_count++)
        {
            c_check_sum ^= c0_header_value[i_count];
        }
        c0_header_value[9] = c_check_sum;

        // copy paramters
        send_conn_id = server_data_array[write_number].ble_char_result_array[0].conn_id;
        //send_char_inst_id = server_data_array[write_number].ble_char_result_array[0].char_id.inst_id;
        send_char_inst_id = server_data_array[write_number].aui4_char_result_handle[0];

        // write msg header to c0
        i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id,
                                          send_char_inst_id, //equal to char handle
                                          i_write_type,
                                          MAX_CHARACTERISTIC_LIMIT,
                                          0,
                                          (char*)c0_header_value);
        BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);
        b_is_NS = FALSE;
        return 0;
    }

    if(server_data_array[write_number].c0_header.i_security_data == GATTC_ADD_SECURITY)
    {
        DBG_ERROR(("<BT_GATT> start decrypt C1, C2, C3 ...\n" ));
        i4_rev_Cn_number = 0;

        BT_GATT_FREE(receive_msg);
        BT_GATT_MALLOC(receive_msg, server_data_array[write_number].c0_header.i2_total_length + 4);

        __mem_print(server_data_array[write_number].request_msg, server_data_array[write_number].ui4_request_msg_len);

        memcpy(receive_msg, server_data_array[write_number].request_msg, server_data_array[write_number].c0_header.i2_total_length + 4);
        BT_GATT_FREE(server_data_array[write_number].request_msg);
        BT_GATT_MALLOC(server_data_array[write_number].request_msg, server_data_array[write_number].c0_header.i2_total_length + strlen(GATTC_PRE_REQUEST_IP) + 1);
        i4_total_request_len = server_data_array[write_number].c0_header.i2_total_length + strlen(GATTC_PRE_REQUEST_IP);
        server_data_array[write_number].request_msg[i4_total_request_len] = '\0';
        BT_GATT_FREE(decrypt_msg);
        BT_GATT_MALLOC(decrypt_msg, server_data_array[write_number].c0_header.i2_total_length + 4);

        // HCs = t4[127...64], HCc = t4[63...0]
        // CTRs[0] = HCs{64} || XSN{32} || 0{1} || C0{1} || LC{30}
        memcpy(HCs, HC + 8, 8);
        memcpy(CTRs + 8, HCs, 8);
        ui4_xsn = server_data_array[write_number].c0_header.i_sequence_number;
        memcpy(CTRs + 4, (char*)&ui4_xsn, 4);

        recv_LCn[0] = recv_LCn[0] &~ (1 << 7);// 0 for receive, 1 for send, set 0
        recv_LCn[0] = recv_LCn[0] &~ (1 << 6);// 1 for C0, 0 for C1-C80, set 0
        ui4_recv_lcn = recv_LCn[0] << 24 | recv_LCn[1] << 16 | recv_LCn[2] << 8 | recv_LCn[3];
        ui4_recv_lcn &= 0xc0000000;

        dec_len = server_data_array[write_number].c0_header.i2_total_length + 4;
        while (1)
        {
            memset(input, 0, AES_BLOCK_SIZE);
            memset(dec_out, 0, AES_BLOCK_SIZE);
            if(dec_len > AES_BLOCK_SIZE)
            {
                memcpy(input, receive_msg + offset, AES_BLOCK_SIZE);
            }
            else
            {
                memcpy(input, receive_msg + offset, dec_len);
            }
            ui4_recv_lcn &= 0xFFFFFF00;
            i4_rev_Cn_number &= 0x000000FF;
            ui4_recv_lcn |= i4_rev_Cn_number;
            memcpy(CTRs, (char*)&ui4_recv_lcn, 4) ;

            if(dec_len > AES_BLOCK_SIZE)
            {
                _bt_AES_encrypt_data(input, dec_out, AES_BLOCK_SIZE, CTRs);
                memcpy(decrypt_msg + offset, dec_out, AES_BLOCK_SIZE);
                offset += AES_BLOCK_SIZE;
                dec_len -= AES_BLOCK_SIZE;
            }
            else
            {
                _bt_AES_encrypt_data(input, dec_out, dec_len, CTRs);
                memcpy(decrypt_msg + offset, dec_out, dec_len);
                break;
            }
            i4_rev_Cn_number++;
        }

        offset = 0;
        DBG_ERROR(("<BT_GATT> decrypt_msg = %s\r\n", decrypt_msg + 4));

        memcpy(server_data_array[write_number].request_msg, GATTC_PRE_REQUEST_IP, strlen(GATTC_PRE_REQUEST_IP));
        memcpy(server_data_array[write_number].request_msg + strlen(GATTC_PRE_REQUEST_IP), decrypt_msg + 4, server_data_array[write_number].c0_header.i2_total_length);
        server_data_array[write_number].ui4_request_msg_len = server_data_array[write_number].c0_header.i2_total_length + strlen(GATTC_PRE_REQUEST_IP);

        BT_GATT_FREE(receive_msg);
        BT_GATT_FREE(decrypt_msg);

    }
/**********************************************************************************************************************************/

    DBG_ERROR(("<BT_GATT> write_number is %d\n ", write_number));
    DBG_ERROR(("<BT_GATT> request_msg is %s\n ", server_data_array[write_number].request_msg));
    DBG_ERROR(("<BT_GATT> ui4_request_msg_len is %d\n ", server_data_array[write_number].ui4_request_msg_len));

    for(i_count = 0; i_count < server_data_array[write_number].ui4_request_msg_len; i_count++)
    {
        if(server_data_array[write_number].request_msg[i_count] == '{')
        {
            offset = i_count;
            if(server_data_array[write_number].request_msg[i_count + 1] != '\0' && server_data_array[write_number].request_msg[i_count + 1] != '}')
            {
                get_response_type = 1;
                break;
            }
        }
    }

    if(get_response_type == 0)// get command
    {
        if(offset == 0)
        {
            url = server_data_array[write_number].request_msg;
            DBG_INFO(("<BT_GATT> get url = %s\n", url));
        }
        else
        {
            server_data_array[write_number].request_msg[offset] = '\0';
            server_data_array[write_number].request_msg[offset + 1] = '\0';
            url = server_data_array[write_number].request_msg;
            DBG_INFO(("<BT_GATT> get url = %s\n", url));
        }

        _bt_url_get_response(url, write_number);

    }
    else if(get_response_type == 1)// put command
    {
        // seperate url and json_data from request_msg
        BT_GATT_MALLOC(url, offset + 1);
        BT_GATT_MALLOC(json_data, server_data_array[write_number].ui4_request_msg_len - offset + 1);
        memset(url, 0, offset + 1);
        memset(json_data, 0, server_data_array[write_number].ui4_request_msg_len - offset + 1);
        memcpy(url, server_data_array[write_number].request_msg, offset);
        url[offset] = '\0';
        memcpy(json_data, server_data_array[write_number].request_msg + offset, server_data_array[write_number].ui4_request_msg_len - offset);
        json_data[server_data_array[write_number].ui4_request_msg_len - offset] = '\0';
        DBG_INFO(("<BT_GATT> put url = %s\n", url));
        DBG_INFO(("<BT_GATT> json_data = %s\n", json_data));

        _bt_url_put_response(url, json_data, write_number);

        BT_GATT_FREE(url);
        BT_GATT_FREE(json_data);
    }

    if(server_data_array[write_number].ui4_response_msg_len == 0
        || NULL == server_data_array[write_number].response_msg)
    {
        return BLUETOOTH_GATTC_OK;
    }

    // msg payload  XOR operation
    DBG_ERROR(("<BT_GATT> bt_addr is %s\n ", server_data_array[write_number].ble_scan_result.btaddr));
    DBG_ERROR(("<BT_GATT> response_msg is %s\n ", server_data_array[write_number].response_msg));
    DBG_ERROR(("<BT_GATT> response_msg length is %d\n ", server_data_array[write_number].ui4_response_msg_len));
    __mem_print2(server_data_array[write_number].response_msg, server_data_array[write_number].ui4_response_msg_len,__FUNCTION__,__LINE__);

    memset(c0_header_value, 0, MAX_CHARACTERISTIC_LIMIT);
    c_check_sum = 0x00;
    for(i_count = 0; i_count < server_data_array[write_number].ui4_response_msg_len; i_count++)
    {
        c_check_sum ^= server_data_array[write_number].response_msg[i_count];
    }

    c0_header_value[0] = server_data_array[write_number].c0_header.i_sequence_number;
    c0_header_value[1] = 0x00;
    int last_fragment_number = (server_data_array[write_number].ui4_response_msg_len) / MAX_FRAGMENT_LIMIT;
    int remain_flags = (server_data_array[write_number].ui4_response_msg_len) % MAX_FRAGMENT_LIMIT;
    if(0 != remain_flags)
    {
        last_fragment_number++;
    }
    c0_header_value[2] = (last_fragment_number -1) & 0xFF;
    if(server_data_array[write_number].c0_header.i_security_data == GATTC_ADD_SECURITY)
    {
        c0_header_value[3] = 1;
    }

    c0_header_value[4] = (server_data_array[write_number].ui4_response_msg_len) & 0xFF;
    c0_header_value[5] = ((server_data_array[write_number].ui4_response_msg_len) >> 8) & 0xFF;

    server_data_array[write_number].ui4_response_code = 200;
    c0_header_value[6] = (server_data_array[write_number].ui4_response_code) & 0xFF;
    c0_header_value[7] = ((server_data_array[write_number].ui4_response_code) >> 8) & 0xFF;

    c0_header_value[8] = 0x05;
    for(i_count = 0; i_count < MAX_CHARACTERISTIC_LIMIT; i_count++)
    {
        c_check_sum ^= c0_header_value[i_count];
    }
    c0_header_value[9] = c_check_sum;

/******************************************************encrypt C0, C1, C2...***************************************************************/
    if(server_data_array[write_number].c0_header.i_security_data == GATTC_ADD_SECURITY)
    {
        DBG_ERROR(("<BT_GATT> start encrypt C0, C1, C2 ...\n" ));
        i4_sed_Cn_number = 0;
        int i4_loop_number = 0;

        BT_GATT_FREE(encrypt_msg);
        BT_GATT_MALLOC(encrypt_msg, server_data_array[write_number].ui4_response_msg_len + 4);

        BT_GATT_FREE(response_msg);
        BT_GATT_MALLOC(response_msg, server_data_array[write_number].ui4_response_msg_len + 4);

        memcpy(response_msg, c0_header_value + 6, 4);
        memcpy(response_msg + 4, server_data_array[write_number].response_msg, server_data_array[write_number].ui4_response_msg_len);

        // HCs = t4[127...64], HCc = t4[63...0]
        memcpy(HCc, HC, 8);
        memcpy(CTRc + 8, HCc, 8);
        ui4_xsn = server_data_array[write_number].c0_header.i_sequence_number;
        memcpy(CTRc + 4, (char*)&ui4_xsn, 4);

        send_LCn[0] = send_LCn[0] | (1 << 7);// 0 for receive, 1 for send, set 1
        send_LCn[0] = send_LCn[0] &~ (1 << 6);// 1 for C0, 0 for C1-C80, set 0
        ui4_send_lcn = send_LCn[0] << 24 | send_LCn[1] << 16 | send_LCn[2] << 8 | send_LCn[3];
        ui4_send_lcn &= 0xc0000000;

        enc_len = server_data_array[write_number].ui4_response_msg_len + 4;
        offset = 0;
        while (1)
        {
            memset(input, 0, AES_BLOCK_SIZE);
            memset(enc_out, 0, AES_BLOCK_SIZE);
            if(enc_len > AES_BLOCK_SIZE)
            {
                memcpy(input, response_msg + offset, AES_BLOCK_SIZE);
            }
            else
            {
                memcpy(input, response_msg + offset, enc_len);
            }
            ui4_send_lcn &= 0xFFFFFF00;
            i4_sed_Cn_number &= 0x000000FF;
            ui4_send_lcn |= i4_sed_Cn_number;
            memcpy(CTRc, (char*)&ui4_send_lcn, 4);
            if(i4_loop_number >= 256)
            {
                UINT32 ui4_big_sign = i4_loop_number / 256;
                memcpy(CTRc + 1, (char*)&ui4_big_sign, 1);
            }

            if(enc_len > AES_BLOCK_SIZE)
            {
                _bt_AES_encrypt_data(input, enc_out, AES_BLOCK_SIZE, CTRc);
                memcpy(encrypt_msg + offset, enc_out, AES_BLOCK_SIZE);
                offset += AES_BLOCK_SIZE;
                enc_len -= AES_BLOCK_SIZE;
            }
            else
            {
                _bt_AES_encrypt_data(input, enc_out, enc_len, CTRc);
                memcpy(encrypt_msg + offset, enc_out, enc_len);
                break;
            }
            i4_sed_Cn_number++;
            i4_loop_number++;
        }

        memcpy(c0_header_value + 6, encrypt_msg, 4);
        memcpy(server_data_array[write_number].response_msg, encrypt_msg + 4, server_data_array[write_number].ui4_response_msg_len);

        BT_GATT_FREE(encrypt_msg);
        BT_GATT_FREE(response_msg);
    }
/**********************************************************************************************************************************/

    // copy paramters
    send_conn_id = server_data_array[write_number].ble_char_result_array[0].conn_id;
    //send_char_inst_id = server_data_array[write_number].ble_char_result_array[0].char_id.inst_id;
    send_char_inst_id = server_data_array[write_number].aui4_char_result_handle[0];

    // write msg header to c0
    i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id,
                                          send_char_inst_id, //equal to char handle
                                          i_write_type,
                                          MAX_CHARACTERISTIC_LIMIT,
                                          0,
                                          (char*)c0_header_value);
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);

    return BLUETOOTH_GATTC_OK;
}

// write cli
INT32 bluetooth_gatt_write_data_cli(int char_index, const char* write_str)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;
    int send_conn_id;
//  int send_service_inst_id;
    int send_char_inst_id;

    int write_number = 0;
    //i_write_scan_number = 0;
    if(char_index == 255)
    {
        char_index = MAX_CHAR_UUID - 1;
    }
    int write_len = strlen(write_str);
    DBG_LOG_PRINT(("<BT_GATT> char_index is %d\n ", char_index));
    DBG_LOG_PRINT(("<BT_GATT> write_str is %s\n ", write_str));
    DBG_LOG_PRINT(("<BT_GATT> write_len is %d\n ", write_len));
    //DBG_ERROR(("<BT_GATT> request_msg is %s\n ", server_data_array[write_number].request_msg));
    //DBG_ERROR(("<BT_GATT> ui4_request_msg_len is %d\n ", server_data_array[write_number].ui4_request_msg_len));
    //for(; i_count < i_scan_number; i_count++)
    //{
        server_data_array[write_number].i_write_char_number = 0;
        server_data_array[write_number].response_msg = NULL;
    //}

    // copy paramters
    send_conn_id = server_data_array[write_number].ble_char_result_array[char_index].conn_id;
    //send_char_inst_id = server_data_array[write_number].ble_char_result_array[char_index].char_id.inst_id;
    send_char_inst_id = server_data_array[write_number].aui4_char_result_handle[char_index];

    // print get char information
    DBG_LOG_PRINT(("<BT_GATT> show write char: %s()\r\n", __FUNCTION__));
    DBG_LOG_PRINT(("<BT_GATT> conn_id = %d.\r\n", send_conn_id));
    DBG_LOG_PRINT(("<BT_GATT> service_uuid = %s.\r\n", server_data_array[write_number].ble_char_result_array[char_index].srvc_id.id.uuid));
    DBG_LOG_PRINT(("<BT_GATT> char_uuid = %s.\r\n", server_data_array[write_number].ble_char_result_array[char_index].char_id.uuid));

    // write msg header to c0
    i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id,
                                      send_char_inst_id, //equal to char handle
                                      i_write_type,
                                      strlen(write_str),
                                      0,
                                      (char*)write_str);
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);

    return BLUETOOTH_GATTC_OK;
}

// read cli
INT32 bluetooth_gatt_read_data_cli(int char_index)
{
    BT_GATT_ENTER_FUNCTION();
#if 0
    INT32 i_ret;
    //int i = 0;
    //int j = 0;
    int write_number = 0;

    // reset read char parameters
    //i_read_scan_number = 0;
    /*for(; i < i_scan_number; i++)
    {
        server_data_array[i].request_msg = NULL;
        server_data_array[i].ui4_request_msg_len = 0;
        memset(&(server_data_array[i].ble_read_result), 0, sizeof(bluetooth_gatt_read_char_rst_t));
        server_data_array[i].i_read_char_number = 0;
        memset(&(server_data_array[i].c0_header), 0, sizeof(C0_HEADER));

        // sort according to the conn_id
        for(; j < i_scan_number - i - 1; j++)
        {
            if(server_data_array[j + 1].ble_connect_result.conn_id < server_data_array[j].ble_connect_result.conn_id)
            {
                GATT_SERVER_DATA server_data_temp;
                memcpy(&server_data_temp, &(server_data_array[j]), sizeof(GATT_SERVER_DATA));
                memcpy(&(server_data_array[j]), &(server_data_array[j + 1]), sizeof(GATT_SERVER_DATA));
                memcpy(&(server_data_array[j + 1]), &server_data_temp, sizeof(GATT_SERVER_DATA));
            }
        }
    }*/

    DBG_ERROR(("<BT_GATT> i_scan_number = %d\r\n", i_scan_number));

    // use char c0 to start read data
    int receive_conn_id = server_data_array[write_number].ble_char_result_array[char_index].conn_id;
    //CHAR receive_service_uuid[BT_GATT_MAX_UUID_LEN] = {0};
    //memcpy(&receive_service_uuid, &(server_data_array[write_number].ble_char_result_array[char_index].srvc_id.id.uuid), BT_GATT_MAX_UUID_LEN);
    //int receive_service_inst_id = server_data_array[write_number].ble_char_result_array[char_index].srvc_id.id.inst_id;
    //CHAR receive_char_uuid[BT_GATT_MAX_UUID_LEN] = {0};
    //memcpy(&receive_char_uuid, &(server_data_array[write_number].ble_char_result_array[char_index].char_id.uuid), BT_GATT_MAX_UUID_LEN);
    //int receive_char_inst_id = server_data_array[write_number].ble_char_result_array[char_index].char_id.inst_id;
    int receive_char_inst_id = server_data_array[write_number].aui4_char_result_handle[char_index];
    server_data_array[write_number].i_read_char_number = char_index;
    server_data_array[write_number].c0_header.i2_total_length = 100;

    // call read char function
    i_ret = a_mtkapi_bt_gattc_read_char(receive_conn_id, receive_char_inst_id/*Equal to char-handle*/, 0);
    //i_ret = a_mtkapi_bt_gattc_read_char(receive_conn_id, &receive_service_uuid, receive_service_inst_id, &receive_char_uuid, receive_char_inst_id, 0);
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_read_char,i_ret);
#endif
    return BLUETOOTH_GATTC_OK;
}

INT32 bluetooth_gatt_security_data_cli(const char *message, int i_msd_key)
{
    uint8_t input[AES_BLOCK_SIZE] = {0};
    uint8_t enc_out[AES_BLOCK_SIZE] = {0};
    uint8_t dec_out[AES_BLOCK_SIZE] = {0};
    int offset = 0;
    int enc_len, dec_len;
    uint8_t *enc_text = NULL;
    uint8_t *dec_text = NULL;
    dec_len = enc_len = strlen(message);
    enc_text = malloc(enc_len);
    dec_text = malloc(dec_len);
    int i = 0;
    uint8_t HCc[8] = {0};
    uint8_t XSN_ex[4] = {0};
    uint8_t CTRs[AES_BLOCK_SIZE] = {0};

    DBG_ERROR(("<BT_GATT> enc_len = %d\n", enc_len));

    // calculate Ns && Nc
    _bt_AES_ecb_calc_nsnc();
    if(i_msd_key == 1)
    {
        if (AES_set_encrypt_key(Kp, 128, &aes) < 0)
        {
            fprintf(stderr, "Unable to set encryption key in AES\n");
            return BLUETOOTH_GATTC_FAILED;
        }
    }
    else if(i_msd_key == 0)
    {
        if (AES_set_encrypt_key(Kt, 128, &aes) < 0)
        {
            fprintf(stderr, "Unable to set encryption key in AES\n");
            return BLUETOOTH_GATTC_FAILED;
        }
    }
    // get aes_key

    // get HC value
    _bt_AES_ecb_encrypt(HC);

    // HCs = t4[127...64], HCc = t4[63...0];
    memcpy(HCc, HC + 8, 8);

    memcpy(CTRs, HCc, 8);
    memcpy(CTRs+8, XSN_ex, 4);
    memset(CTRs+12, 0, 4);
    DBG_ERROR(("<BT_GATT> ctr:" ));
    for(; i < 16; i++)
    {
        DBG_ERROR(("<BT_GATT> %0x ",CTRs[i]));
    }

    // encrypt process
    while (1)
    {
        if(enc_len > AES_BLOCK_SIZE)
        {
            memcpy(input, message + offset, AES_BLOCK_SIZE);
            _bt_AES_encrypt_data(input, enc_out, AES_BLOCK_SIZE, CTRs);
            memcpy(enc_text + offset, enc_out, AES_BLOCK_SIZE);
            offset += AES_BLOCK_SIZE;
            enc_len -= AES_BLOCK_SIZE;
            DBG_ERROR(("<BT_GATT> offset = %d, enc_len = %d, %d\n", offset, enc_len, __LINE__));
        }
        else
        {
            memset(input, 0, AES_BLOCK_SIZE);
            memset(enc_out, 0, AES_BLOCK_SIZE);
            memcpy(input, message + offset, enc_len);
            _bt_AES_encrypt_data(input, enc_out, enc_len, CTRs);
            memcpy(enc_text + offset, enc_out, enc_len);
            DBG_ERROR(("<BT_GATT> offset = %d, enc_len = %d, %d\n", offset, enc_len, __LINE__));
            break;
        }
    }
    DBG_ERROR(("<BT_GATT> enc_text = %s\n", enc_text));

    // decrypt process
    offset = 0;
    while (1)
    {
        if(dec_len > AES_BLOCK_SIZE)
        {
            memcpy(input, enc_text + offset, AES_BLOCK_SIZE);
            _bt_AES_encrypt_data(input, dec_out, AES_BLOCK_SIZE, CTRs);
            memcpy(dec_text + offset, dec_out, AES_BLOCK_SIZE);
            offset += AES_BLOCK_SIZE;
            dec_len -= AES_BLOCK_SIZE;
        }
        else
        {
            memset(input, 0, AES_BLOCK_SIZE);
            memset(dec_out, 0, AES_BLOCK_SIZE);
            memcpy(input, enc_text + offset, dec_len);
            _bt_AES_encrypt_data(input, dec_out, dec_len, CTRs);
            memcpy(dec_text + offset, dec_out, dec_len);
            break;
        }
    }
    DBG_ERROR(("<BT_GATT> dec_text = %s\n", dec_text));

    return 0;

}

VOID bluetooth_gatt_reset_rssi_meter(VOID)
{
    c_memset(&t_rssi_meter_nfy, 0, sizeof(T_RSSI_NOTIFY_MSG));
}

INT32 a_bluetooth_gattc_rssi_meter_dialog_enable(BOOL b_enable)
{
    b_rssi_show = b_enable;
    DBG_LOG_PRINT(("<BT_GATT> b_rssi_show = %s!\r\n.",(b_rssi_show == TRUE) ? "TRUE" : "FALSE"));
    return 0;
}

INT32 bt_gattc_get_client_if(VOID)
{
    DBG_LOG_PRINT(("%s() %d: bt_gattc_app_client_if=%d\n",__FUNCTION__,__LINE__,bt_gattc_app_client_if));
    return bt_gattc_app_client_if;
}
/******************************************functions defines***************************************/
// register callback, and initial some parameters
INT32 bluetooth_gatt_init_proc(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i4_ret;

    b_is_init = FALSE;

    if(!b_is_init)
    {
        // callback function register
        MTKRPCAPI_BT_APP_GATTC_CB_FUNC_T      t_gatt_cbk_func;
        c_memset(&t_gatt_cbk_func, 0x0, sizeof(MTKRPCAPI_BT_APP_GATTC_CB_FUNC_T));

        t_gatt_cbk_func.bt_gattc_event_cb                = _bt_gattc_event_result_cb;
        t_gatt_cbk_func.bt_gattc_reg_client_cb           = _bt_gattc_reg_client_result_cb;
        t_gatt_cbk_func.bt_gattc_scan_cb                 = _bt_gattc_scan_result_cb;
        t_gatt_cbk_func.bt_gattc_get_reg_noti_cb         = _bt_gattc_get_reg_notify_result_cb;
        t_gatt_cbk_func.bt_gattc_notify_cb               = _bt_gattc_notify_result_cb;
        t_gatt_cbk_func.bt_gattc_read_char_cb            = _bt_gattc_read_char_result_cb;
        t_gatt_cbk_func.bt_gattc_read_desc_cb            = _bt_gattc_read_desc_result_cb;
        t_gatt_cbk_func.bt_gattc_write_char_cb           = _bt_gattc_write_char_result_cb;
        t_gatt_cbk_func.bt_gattc_write_desc_cb           = _bt_gattc_write_desc_result_cb;
        t_gatt_cbk_func.bt_gattc_get_gatt_db_cb          = _bt_gatt_get_gatt_db_cb;
        t_gatt_cbk_func.bt_gattc_scan_filter_param_cb    = bt_gatt_scan_filter_param_cb;
        t_gatt_cbk_func.bt_gattc_scan_filter_status_cb   = bt_gatt_scan_filter_status_cb;
        t_gatt_cbk_func.bt_gattc_scan_filter_cfg_cb      = bt_gatt_scan_filter_cfg_cb;

        i4_ret = a_mtkapi_bt_gattc_base_init(&t_gatt_cbk_func,NULL);
        BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_base_init,i4_ret);

        i4_ret = a_mtkapi_bt_gattc_register_app(BTM_GATTC_APP_UUID);
        BT_GATT_CHECK_FAIL(a_mtkapi_bt_gattc_register_app,i4_ret);

        // static parameters init
        memset(server_data_array, 0, sizeof(GATT_SERVER_DATA) * MAX_SCAN_DEVICE);
        memset(last_scan_device, 0, sizeof(last_scan_device));

        i_scan_number = 0;
        i4_set_rssi_threshold = 0;
        i4_scan_status = 0;
        b_allow_scan = FALSE;
        b_gatt_close = FALSE;

        bluetooth_gatt_scan_filter_init();

        b_is_init = TRUE;
    }
    else
    {
        DBG_ERROR(("<BT_GATT> error: %s() called again, callback register again.\r\n",__FUNCTION__));
    }

    return BLUETOOTH_GATTC_OK;
}

// auto scan after power on
INT32 bluetooth_gattc_poweron_scan_proc(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;

    b_gatt_close = FALSE;

    // call scan function
    i_ret = a_mtkapi_bt_gattc_scan();
    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_scan, i_ret);

    return BLUETOOTH_GATTC_OK;
}

// scan interface
INT32 bluetooth_gattc_scan_proc(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;

    // avoid extern call in not allow time
    if(b_allow_scan && i_scan_number < MAX_SCAN_DEVICE)
    {
        i_ret = bluetooth_gatt_get_scan_status();
        if(i_ret == 0)
        {
            i4_scan_status++;

            // call scan function
            i_ret = a_mtkapi_bt_gattc_scan();
            BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_scan,i_ret);
        }
        else
        {
            DBG_ERROR(("<BT_GATT> Can not scan now!\r\n"));
        }
    }

    return BLUETOOTH_GATTC_OK;
}

// stop scan interface
INT32 bluetooth_gattc_stop_scan_proc(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;

    i_ret = bluetooth_gatt_get_scan_status();
    if(i_ret == 1)
    {
        // call stop scan function
        i_ret = a_mtkapi_bt_gattc_stop_scan();
        BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_stop_scan,i_ret);
        i4_scan_status--;
    }
    else
    {
        DBG_ERROR(("<BT_GATT> Can not stop scan now!\r\n"));
    }

    return BLUETOOTH_GATTC_OK;

}

// close gatt app
INT32 bluetooth_gatt_close_proc(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i4_ret;
    int i = 0;
    //c_sema_create (h_getchar_sema);

    b_gatt_close = TRUE;
    b_allow_scan = FALSE;

    // copy parameters
    for(; i < MAX_SCAN_DEVICE; i++)
    {
        BT_GATT_FREE(server_data_array[i].request_msg);
        BT_GATT_FREE(server_data_array[i].response_msg);

        if(last_scan_device[i].ui8_interval != NULL)
        {
            free(last_scan_device[i].ui8_interval);
            last_scan_device[i].ui8_interval = NULL;
            last_scan_device[i].i4_elem_num = 0;
        }

        char* deinit_bt_addr = server_data_array[i].ble_connect_result.btaddr;
        int deinit_conn_id = server_data_array[i].ble_connect_result.conn_id;
        if(deinit_bt_addr != NULL && deinit_conn_id != 0)
        {
            //i4_ret = c_btm_gattc_close(deinit_bt_addr, deinit_conn_id);
            i4_ret = a_mtkapi_bt_gattc_close(server_data_array[i].ble_connect_result.client_if,
                                             deinit_bt_addr,
                                             deinit_conn_id);
            BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_close,i4_ret);
        }
    }

    return BLUETOOTH_GATTC_OK;
}

// deinit gatt app
VOID bluetooth_gatt_deinit_proc(VOID)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i4_ret;

    b_is_init = FALSE;
    // static parameters init
    memset(server_data_array, 0, sizeof(GATT_SERVER_DATA) * MAX_SCAN_DEVICE);

    i4_ret = a_mtkapi_bt_gattc_stop_scan();
    BT_GATT_CHECK_FAIL(a_mtkapi_bt_gattc_stop_scan,i4_ret);
}

// process some events msg from mw
INT32 bluetooth_gatt_event_msg_proc(const VOID *pv_msg)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;
    BT_GATT_MSG_T* pt_bt_msg = (BT_GATT_MSG_T*)pv_msg;

    DBG_LOG_PRINT(("<BT_GATT> Get event {id:%d}.\r\n",pt_bt_msg->ui4_data1));

    switch (pt_bt_msg->ui4_data1)
    {
        case BT_GATTC_REGISTER_CLIENT:

            break;

        case BT_GATTC_CONNECT:
            {
                int i = 0;
                BT_GATTC_CONNECT_RST_T* pt_find = NULL;
                // get open result and save it
                for(i = 0; i < MAX_SCAN_DEVICE; i++)
                {
                    pt_find = &(server_data_array[i].ble_connect_result);
                    if(pt_find->conn_id == 0)
                    {
                        memset(pt_find, 0, sizeof(BT_GATTC_CONNECT_RST_T));

                        a_mtkapi_bt_gattc_get_connect_result_info(pt_find);

                        server_data_array[i].i_connect_sign = GATTC_CONNECTED;

                        DBG_LOG_PRINT(("<BT_GATT> show connect result: bluetooth_gattc_get_connect_result_info()\r\n"));
                        DBG_LOG_PRINT(("<BT_GATT> conn_id = %d.\r\n", pt_find->conn_id));
                        DBG_LOG_PRINT(("<BT_GATT> btaddr = %s.\r\n", pt_find->btaddr));
                        DBG_LOG_PRINT(("<BT_GATT> waiting(%d sec) for gatt db ready...\r\n",3500));

                        c_thread_delay(3500);

                        i_ret = a_mtkapi_bt_gattc_get_gatt_db(pt_find->conn_id);
                        BT_GATT_CHECK_FAIL_RET(c_btm_gattc_get_gatt_db,i_ret);
                        break;
                    }
                }

                _bt_print_server_data();
            }
            break;

        case BT_GATTC_DISCONNECT:
            {
                // get disconnect result
                DBG_LOG_PRINT(("<BT_GATT> one gatt server disconnect.\r\n"));
                int i = 0;
                BT_GATTC_CONNECT_RST_T*  pt_find = NULL;
                BT_GATTC_CONNECT_RST_T   ble_disconnect_result;

                a_mtkapi_bt_gattc_get_disconnect_result_info(&ble_disconnect_result);

                DBG_LOG_PRINT(("<BT_GATT> show disconnect result: c_btm_bt_gattc_get_disconnect_result_info()\r\n"));
                DBG_LOG_PRINT(("<BT_GATT> conn_id = %d.\r\n", ble_disconnect_result.conn_id));
                DBG_LOG_PRINT(("<BT_GATT> client_if = %d.\r\n", ble_disconnect_result.client_if));
                DBG_LOG_PRINT(("<BT_GATT> btaddr = %s.\r\n", ble_disconnect_result.btaddr));

                for(; i < MAX_SCAN_DEVICE; i++)
                {
                    pt_find = &(server_data_array[i].ble_connect_result);

                    if( pt_find->conn_id > 0 &&
                        ble_disconnect_result.conn_id == pt_find->conn_id)
                    {
                        server_data_array[i].i_connect_sign = GATTC_DISCONNECT;
                        server_data_array[i].i_get_char_number = 0;
                        server_data_array[i].ui4_gatt_db_loop_idx = 0;
#if 0
                        if (server_data_array[i].pt_registered_char != NULL)
                        {
                            i_ret = a_mtkapi_bt_gattc_dereg_noti(ble_disconnect_result.client_if,
                                                                 server_data_array[i].ble_scan_result.btaddr,
                                                                 server_data_array[i].ui4_reg_char_handle);
                            BT_GATT_CHECK_FAIL(a_mtkapi_bt_gattc_dereg_noti,i_ret);

                            server_data_array[i].pt_registered_char = NULL;
                        }
#endif
                        if (server_data_array[i].t_gatt_db.gatt_db_element != NULL)
                        {
                            c_mem_free(server_data_array[i].t_gatt_db.gatt_db_element);
                        }
                        memset(&(server_data_array[i]), 0, sizeof(GATT_SERVER_DATA));
                        _bt_print_server_data();
                        break;
                    }
                }

                DBG_ERROR(("<BT_GATT> i_scan_number = %d.\r\n", i_scan_number));

                i_scan_number--;
                i_scan_number = (i_scan_number < 0) ? 0: i_scan_number;

                if(!b_gatt_close && i_scan_number < MAX_SCAN_DEVICE)
                {
                    i_ret = a_mtkapi_bt_gattc_set_scan_parameters(server_data_array[i_scan_number].ble_connect_result.client_if,
                                                          GATTC_SCAN_INTERVAL,
                                                          GATTC_SCAN_WINDOW);
                    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_set_scan_parameters,i_ret);

                    // call scan function
                    i_ret = a_mtkapi_bt_gattc_scan();
                    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_scan,i_ret);
                }
            }
            break;

        case BT_GATTC_GET_RSSI_DONE:
            DBG_LOG_PRINT(("<BT_GATT> get rssi done.\r\n"));
            break;

        default:
            DBG_ERROR(("<BT_GATT> error: can't recognize the bluetooth gatt msgtype %d.\r\n", pt_bt_msg->ui4_msg_id));
            return BLUETOOTH_GATTC_FAILED;
    }

    return BLUETOOTH_GATTC_OK;
}

INT32 bluetooth_gattc_allow_pair(char *c_mac_addr, INT32 i4_rssi, INT32 i4_get_rssi_threshold, INT32 i4_min_consecutive,INT32 i4_max_interval, BOOL *b_allow_pair)
{
    /* Allow condition:
    *  rssi > threshold && consective == i4_min_consective && interval <= i4_max_interval
    */
    UINT8 ui1_count = 0;
    INT32 i = 0;
    INT32 j = 0;
    INT32 i4_cache_idx = -1;
    INT32 i4_unused_idx = -1;
    INT32 i4_timeout_idx = -1;
    UINT64 ui8_time_tmp = 0;
    UINT64 ui8_max_delay = 0;
    UINT64 ui8_cur_delay = 0;

    ui8_time_tmp = c_os_get_sys_tick()*c_os_get_sys_tick_period();

    // get special buffer index
    for(i = 0; i < MAX_SCAN_DEVICE; i++)
    {
        if (last_scan_device[i].b_used)
        {
            ui1_count++;
        }

        /* find a un-used buffer */
        if (-1 == i4_unused_idx
            && FALSE == last_scan_device[i].b_used)
        {
            i4_unused_idx = i;
        }

        /* find cached buffer */
        if(-1 == i4_cache_idx
            && strncmp(last_scan_device[i].last_mac_addr, c_mac_addr, MAC_ADDRESS_LENGTH_LEN)==0)
        {
            i4_cache_idx = i;
        }

        /* find the max delayed buffer */
        if (/*i != i4_cache_idx
            && */last_scan_device[i].b_used
            && last_scan_device[i].ui8_interval != NULL)
        {
            ui8_cur_delay = ui8_time_tmp - last_scan_device[i].ui8_interval[0];
            if (ui8_cur_delay > last_scan_device[i].i4_max_interval
                && ui8_max_delay < ui8_cur_delay)
            {
                ui8_max_delay = ui8_cur_delay;
                i4_timeout_idx = i;
            }
        }

        DBG_INFO(("<BT_GATTC> last_scan_device[%d]=[%d,%d,%d,%s,0x%x,%llu,%d]\n", i,
                                                            last_scan_device[i].b_used,
                                                            last_scan_device[i].i4_elem_num,
                                                            last_scan_device[i].i4_max_interval,
                                                            last_scan_device[i].last_mac_addr,
                                                            last_scan_device[i].ui8_interval,
                                                            last_scan_device[i].ui8_time_sum,
                                                            last_scan_device[i].ui_pairing_state));
    }

    DBG_INFO(("<BT_GATTC> last scan buffer count=%d, cached=%d, un-used=%d, max-delayed=%d\n",
                                                                                ui1_count,
                                                                                i4_cache_idx,
                                                                                i4_unused_idx,
                                                                                i4_timeout_idx));
    // if pair, need rssi > rssi_threshold
    if(i4_rssi > i4_get_rssi_threshold)
    {
        if(i4_min_consecutive <= 0 || i4_max_interval <= 0)
        {
            // OK
            *b_allow_pair = TRUE;
            DBG_INFO(("<BT_GATT> Allow pair, no need check consecutiem.\n"));
            return BLUETOOTH_GATTC_OK;
        }

        if (-1 == i4_cache_idx) //(i == MAX_SCAN_DEVICE)
        {
            /* Remove timerout ADV */
            if (i4_unused_idx < 0 || i4_unused_idx >= MAX_SCAN_DEVICE)
            {
                if (i4_timeout_idx < 0 || i4_timeout_idx >= MAX_SCAN_DEVICE)
                {
                    DBG_LOG_PRINT(("Not Allow! Pairing buffer is full, please wait...\n"));
                    return BLUETOOTH_GATTC_OK;
                }

                j = i4_timeout_idx;

                DBG_INFO(("<BT_GATT> timerout remove paring buffer[%d]=[%s]\n", j, last_scan_device[j].last_mac_addr));
                REMOVE_LAST_SCAN_BUFFER(j);
            }
            else
            {
                j = i4_unused_idx;
            }

            if (last_scan_device[j].i4_elem_num < i4_min_consecutive
                && last_scan_device[j].ui8_interval != NULL)
            {
                free(last_scan_device[j].ui8_interval);
                last_scan_device[j].ui8_interval = NULL;
                last_scan_device[j].i4_elem_num = 0;
            }

            if (NULL == last_scan_device[j].ui8_interval && i4_min_consecutive > 0)
            {
                last_scan_device[j].i4_elem_num = i4_min_consecutive;
                last_scan_device[j].ui8_interval = (UINT64*)malloc(i4_min_consecutive * sizeof(UINT64));

                if (NULL == last_scan_device[j].ui8_interval)
                {
                    last_scan_device[j].i4_elem_num = 0;

                    DBG_ERROR(("Malloc memory fail(@L%d)!!!\n\n", __LINE__));
                    return BLUETOOTH_GATTC_FAILED;
                }
                memset(last_scan_device[j].ui8_interval, 0, i4_min_consecutive * sizeof(UINT64));
            }

            last_scan_device[j].b_used = TRUE;
            last_scan_device[j].i4_max_interval = i4_max_interval;
            memcpy(last_scan_device[j].last_mac_addr, c_mac_addr, MAC_ADDRESS_LENGTH_LEN);
            last_scan_device[j].last_mac_addr[MAC_ADDRESS_LENGTH_LEN] = '\0';
            i = j;

            DBG_INFO(("<BT_GATT> add paring buffer[%d]=[%s]\n", i, c_mac_addr));
        }
        else
        {
            i = i4_cache_idx;

            /* Exception process */
            if (i4_min_consecutive > last_scan_device[i].i4_elem_num)
            {
                UINT64 *pui8_tmp = NULL;

                DBG_LOG_PRINT(("<BT_GATTC> Warning, min consective change(%d-->%d)!!!\n", last_scan_device[i].i4_elem_num, i4_min_consecutive));

                pui8_tmp = (UINT64*)malloc(i4_min_consecutive * sizeof(UINT64));
                if (pui8_tmp != NULL)
                {
                    DBG_INFO(("<BT_GATTC> extend interval buffer.\n"));

                    memset(pui8_tmp, 0, i4_min_consecutive * sizeof(UINT64));
                    memcpy(pui8_tmp, last_scan_device[i].ui8_interval, last_scan_device[i].i4_elem_num*sizeof(UINT64));
                    free(last_scan_device[i].ui8_interval);

                    last_scan_device[i].i4_elem_num = i4_min_consecutive;
                    last_scan_device[i].ui8_interval = pui8_tmp;
                    pui8_tmp = NULL;
                }
                else
                {
                    DBG_INFO(("<BT_GATTC> extend buffer fail, use old min-consective.\n"));
                    i4_min_consecutive = last_scan_device[i].i4_elem_num;
                }
            }
        }

        last_scan_device[i].ui_pairing_state += 1;
        last_scan_device[i].ui8_interval[last_scan_device[i].ui_pairing_state-1] = c_os_get_sys_tick()*c_os_get_sys_tick_period();
        last_scan_device[i].ui8_time_sum = last_scan_device[i].ui8_interval[last_scan_device[i].ui_pairing_state-1] \
                                            - last_scan_device[i].ui8_interval[0];

        if (last_scan_device[i].ui8_time_sum > (GATTC_SCAN_INTERVAL+GATTC_SCAN_WINDOW))
        {
            last_scan_device[i].ui8_time_sum = last_scan_device[i].ui8_time_sum/(GATTC_SCAN_INTERVAL+GATTC_SCAN_WINDOW)*GATTC_SCAN_WINDOW;
            last_scan_device[i].ui8_time_sum += (last_scan_device[i].ui8_time_sum %(GATTC_SCAN_INTERVAL+GATTC_SCAN_WINDOW) - GATTC_SCAN_INTERVAL);
        }

        DBG_INFO(("<BT_GATTC> pairing_state=%d.\n", last_scan_device[i].ui_pairing_state));

        if (last_scan_device[i].ui8_time_sum > i4_max_interval)
        {
            // throw previous all, count from the current one: this_time > i4_max_interval
            if (last_scan_device[i].ui_pairing_state >= 2
                && (last_scan_device[i].ui8_interval[last_scan_device[i].ui_pairing_state-1]
                    - last_scan_device[i].ui8_interval[last_scan_device[i].ui_pairing_state-2]) > i4_max_interval)
            {
                last_scan_device[i].ui8_interval[0] = last_scan_device[i].ui8_interval[last_scan_device[i].ui_pairing_state-1];

                for(j = 1; j < last_scan_device[i].ui_pairing_state; j++)
                {
                    last_scan_device[i].ui8_interval[j] = 0;
                }

                last_scan_device[i].ui_pairing_state = 1;

                DBG_INFO(("<BT_GATTC> btaddr=[%s] timeout(%lld) for max-interval(%d), reset paring state to 1.\n",
                                                                            last_scan_device[i].last_mac_addr,
                                                                            last_scan_device[i].ui8_time_sum,
                                                                            i4_max_interval));
            }
            else    // throw first one: total_time > i4_max_interval
            {
                for(j = 0; j < last_scan_device[i].ui_pairing_state; j++)
                {
                    last_scan_device[i].ui8_interval[j] = last_scan_device[i].ui8_interval[j+1];
                }

                last_scan_device[i].ui_pairing_state -= 1;
                DBG_INFO(("<BT_GATTC> btaddr=[%s] timeout(%lld) for max-interval(%d), paring state reduce one.\n",
                                                                            last_scan_device[i].last_mac_addr,
                                                                            last_scan_device[i].ui8_time_sum,
                                                                            i4_max_interval));
            }

            return BLUETOOTH_GATTC_OK;
        }

        // justice whether allow pair
        if(last_scan_device[i].ui_pairing_state == i4_min_consecutive)
        {
            // OK
            *b_allow_pair = TRUE;
            DBG_INFO(("<BT_GATT> allow pair, remove paring buffer[%d]=[%s]\n", i, last_scan_device[i].last_mac_addr));
            REMOVE_LAST_SCAN_BUFFER(i);
        }
    }
    else
    {
        // reset from pairing_state = 0
        if(-1 == i4_cache_idx)
        {
            return BLUETOOTH_GATTC_OK;
        }

        DBG_INFO(("<BT_GATT>rssi too worse, remove paring buffer[%d]=[%s]\n", i, last_scan_device[i].last_mac_addr));
        REMOVE_LAST_SCAN_BUFFER(i4_cache_idx);
    }

    return BLUETOOTH_GATTC_OK;
}

INT32 bluetooth_gattc_ios_data_parse(CHAR uuid_scan[], UINT32 *ui4_final_cons, INT32 *i4_target_ID)
{
    INT32 i4_ios_sn = 0, i4_ios_target = 0;
    i4_ios_sn = _bt_char_to_int(uuid_scan[7]);
    memset(&variable_tag, 0, sizeof(EIR_MSD_VARIABLE_TAG));
    char c_ios_sign[5] = {0};
    UINT32 ui4_ios_sign = 0;

    memcpy(c_ios_sign, uuid_scan + 28, 4);
    ui4_ios_sign = (_bt_char_to_int(c_ios_sign[0]) << 12)
                    | (_bt_char_to_int(c_ios_sign[1]) << 8)
                    | (_bt_char_to_int(c_ios_sign[2]) << 4)
                    | (_bt_char_to_int(c_ios_sign[3]));

    *ui4_final_cons = ui4_ios_sign ^ 0x2ea8;
    i4_ios_target = (*ui4_final_cons >> 3) & 0x3f;
    i4_ble_version = (*ui4_final_cons >> 9) & 0x7f;
    DBG_INFO(("<BT_GATT> ui4_final_cons = %u, i4_ios_sn = %d, i4_ios_target = %d, i4_ios_version = %d\n",
                                                                            *ui4_final_cons,
                                                                            i4_ios_sn,
                                                                            i4_ios_target,
                                                                            i4_ble_version));
    *i4_target_ID = i4_ios_target;
    switch(i4_ios_sn)
    {
        case 4:
        {
            // S1
            variable_tag.signal_meter = 1;
            variable_tag.no_wakeup = 0;
            variable_tag.signal_meter = 1;
        }
        break;
        case 7:
        {
            // S2
            variable_tag.no_wakeup = 0;
            variable_tag.security_key = 0;
        }
        break;
        case 6:
        {
            // S3
            variable_tag.no_wakeup = 0;
            variable_tag.security_key = 1;
            memcpy(c_msd_security, "00", 2);
        }
        case 1:
        {
            // S4
            variable_tag.no_wakeup = 0;
            variable_tag.security_key = 1;
            memcpy(c_msd_security, "01", 2);
        }
        break;
        case 12:
        {
            // S9
            variable_tag.signal_meter = 1;
            variable_tag.no_wakeup = 1;
        }
        break;
        case 15:
        {
            // S10
            variable_tag.security_key = 0;
            variable_tag.no_wakeup = 1;
        }
        break;
        case 14:
        {
            // S11
            variable_tag.no_wakeup = 1;
            variable_tag.security_key = 1;
            memcpy(c_msd_security, "00", 2);
        }
        break;
        case 9:
        {
            // S12
            variable_tag.no_wakeup = 1;
            variable_tag.security_key = 1;
            memcpy(c_msd_security, "01", 2);
        }
        break;
        default:
        {
            DBG_ERROR(("<BT_GATT> unsupport IOS service version.\r\n"));
            b_can_scan = TRUE;
            return BLUETOOTH_GATTC_FAILED;
        }
        break;
    }
    return BLUETOOTH_GATTC_OK;
}

INT32 bluetooth_gattc_directed_pairing(char scan_uuid[], UINT32 *final_cons, INT32 *target_ID, INT32 *cache_index, BOOL *direct_pair)
{
    CHAR c_mac_addr[MAC_ADDRESS_LENGTH_LEN + 1] = {0};
    BOOL b_cache_server = FALSE, b_pair_me = FALSE;
    INT32 i, j, i_ret = 0;

    for(i = 0, j = 0; j < MAC_ADDRESS_LENGTH_LEN + 1; j++)
    {
        if(scan_uuid[19 + j] != '-')
        {
            c_mac_addr[i++] = scan_uuid[19 + j];
        }
    }

    // to see if tablet's mac address have cached
    memset(scan_ble_device, 0, sizeof(scan_ble_device));
    i_ret = a_cfg_get_blegatt_macaddress_threshold(scan_ble_device);
    BT_GATT_CHECK_FAIL_RET(a_cfg_get_blegatt_macaddress_threshold,i_ret);
    for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
    {
        scan_ble_device[i].c_mac_address[MAC_ADDRESS_LENGTH_LEN] = '\0';

        if(strncmp(scan_ble_device[i].c_mac_address, c_mac_addr, MAC_ADDRESS_LENGTH_LEN) == 0)
        {
            b_cache_server = TRUE;
        }

        DBG_INFO(("<BT_GATT> cached mac_address: %s, target_ID: %d\r\n.", scan_ble_device[i].c_mac_address, scan_ble_device[i].ui_target_ID));
    }

    // to see if tablet want to directed pair with me
    uint8_t bd_address[6] = {0};
    BT_LOCAL_DEV local_dev_info;
    a_mtkapi_bt_gap_get_local_dev_info(&local_dev_info);
    _bt_gattc_btaddr_stoh(local_dev_info.bdAddr, bd_address);

    DBG_INFO(("<BT_GATT> bd_address = name[%s] [%2x,%2x,%2x,%2x,%2x,%2x]\r\n.",local_dev_info.name,
                                                        bd_address[0],bd_address[1],bd_address[2],
                                                        bd_address[3],bd_address[4],bd_address[5]));

    uint8_t u_byte_1 = ((uint8_t)_bt_bytes_to_int(scan_uuid)) ^ 0x69;
    uint8_t u_byte_2 = ((uint8_t)_bt_bytes_to_int(scan_uuid + 2)) ^ 0xa3;
    uint8_t u_byte_3 = ((uint8_t)_bt_bytes_to_int(scan_uuid + 9)) ^ 0xcb;
    uint8_t u_byte_4 = ((uint8_t)_bt_bytes_to_int(scan_uuid + 11)) ^ 0xc1;
    uint8_t u_byte_5 = ((uint8_t)_bt_bytes_to_int(scan_uuid + 14)) ^ 0x4b;
    uint8_t u_byte_6 = ((uint8_t)_bt_bytes_to_int(scan_uuid + 16)) ^ 0x5d;
    DBG_INFO(("<BT_GATT> u_byte_1 = %d, u_byte_2 = %d, u_byte_3 = %d\r\n.", u_byte_1, u_byte_2, u_byte_3));
    DBG_INFO(("<BT_GATT> u_byte_4 = %d, u_byte_5 = %d, u_byte_6 = %d\r\n.", u_byte_4, u_byte_5, u_byte_6));
    if(u_byte_1 == bd_address[0] && u_byte_2 == bd_address[1] && u_byte_3 == bd_address[2]
        && u_byte_4 == bd_address[3] && u_byte_5 == bd_address[4] && u_byte_6 == bd_address[5])
    {
        b_pair_me = TRUE;
    }
    else
    {
        b_pair_me = FALSE;
        DBG_ERROR(("<BT_GATT> directed pairing but not with me.\r\n."));
    }

    // now begin directed pairing
    if(b_pair_me && b_cache_server)
    {

        i_ret = bluetooth_gattc_ios_data_parse(scan_uuid, final_cons, target_ID);
        BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_directed_pairing, i_ret);
        DBG_INFO(("<BT_GATT> Direct pairing:i4_target_ID = %d\r\n", target_ID));
        b_cache_mac = FALSE;
        for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
        {
            if(strncmp(scan_ble_device[i].c_mac_address, "000000000000", MAC_ADDRESS_LENGTH_LEN) != 0
                && (strncmp(scan_ble_device[i].c_mac_address, c_mac_addr, MAC_ADDRESS_LENGTH_LEN) == 0))
            {
                b_cache_mac = TRUE;
                *cache_index = i;
                break;
            }
        }
        *direct_pair = TRUE;
    }
    else
    {
        *direct_pair = FALSE;
    }

    return BLUETOOTH_GATTC_OK;
}

// process some event msg from gatt app self
INT32 bluetooth_gatt_intra_msg_proc(const VOID *pv_msg)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i_ret;
    HANDLE_T    h_char = NULL_HANDLE;

    BT_GATT_MSG_T* pt_bt_msg = (BT_GATT_MSG_T*)pv_msg;

    switch (pt_bt_msg->ui4_data1)
    {
        case BT_GATT_SCAN_RESULT_CB:
        {
            if(b_can_scan)
            {
                BT_GATTC_SCAN_RST_T* get_scan_result = (BT_GATTC_SCAN_RST_T*)(pt_bt_msg->ui4_data3);
                BT_GATTC_SCAN_RST_T  ble_scan_result;
                INT32 i4_get_rssi_threshold = 0, i4_min_rssi = 0;
                INT32 i4_max_interval = 3000000;
                INT32 i4_min_consecutive = 3;
                INT32 i4_msd_len = 0, i4_tag_offset = 0, i4_tag_bitmap_low = 0;
                INT32 i4_tag_bitmap_high = 0, i4_tag_nine_low = 0;
                INT32 i4_tag_nine_high = 0, i = 0, i4_target_ID = 0, i4_cache_index = 0;
                CHAR  uuid_scan[37], manufacturer_data[MAX_EIR_MSD_LEN] = {'\0'}, C1_00_58[9] = {'\0'};
                CHAR  c_mac_addr[MAC_ADDRESS_LENGTH_LEN + 1] = {0};
                CHAR  c_msd_scan_para[5], c_msd_conn_para[9], c_msd_pair_para[7], c_msd_max_rssi[3], c_msd_sign_timeout[3];
                UINT32 ui4_final_cons = 0;
                b_can_scan = FALSE;
                BOOL b_directed_pair = FALSE, b_allow_pair = FALSE;
                DBG_LOG_PRINT(("<BT_GATT> Scan result:{rssi:0x%x,btaddr:%s,adv_data:%s}\n",get_scan_result->rssi,get_scan_result->btaddr,get_scan_result->adv_data));
#ifdef APP_BLE_SUPPORT
                /* set BT gattc server rssi */
                if (ICLR_OK != a_icl_set_bt_gattc_server_rssi((int32_t)get_scan_result->rssi))
                {
                    DBG_LOG_PRINT(("\n%d %s a_icl_custom_set_bt_gattc_server_rssi() failed!\n", __LINE__, __FILE__));
                }
#endif
                if (a_bgm_is_active_standby_state())
                {
                    DBG_LOG_PRINT(("<BT_GATT> woble from active-standby mode\n"));
                    a_bgm_cast_exit_active_standby(NULL, NULL, NULL);
                    b_can_scan = TRUE;
                    break;
                }

                memcpy(&ble_scan_result, get_scan_result, sizeof(BT_GATTC_SCAN_RST_T));

                //c_strncpy(uuid_scan, ble_scan_result.uuid, BT_GATT_MAX_UUID_LEN);
                __mem_print2(ble_scan_result.adv_data, 37, __FUNCTION__,__LINE__);

                c_memset(uuid_scan, 0, sizeof(uuid_scan));
                _bt_gattc_print_uuid(ble_scan_result.adv_data,uuid_scan);

                if(strncmp(uuid_scan + 4, GATTC_DIRECT_PAIRING,strlen(GATTC_DIRECT_PAIRING)) == 0)
                {
                    // For direct pairing
                    DBG_INFO(("<BT_GATT> now start Android or IOS directed pairing, uuid = %s\r\n.", uuid_scan));
                    i_ret = bluetooth_gattc_directed_pairing(uuid_scan, &ui4_final_cons, &i4_target_ID, &i4_cache_index, &b_directed_pair);
                    BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_directed_pairing, i_ret);
                }
                else
                {
                    if(strncmp(uuid_scan, GATTC_IOS_SERVICE_UUID,strlen(GATTC_IOS_SERVICE_UUID)) == 0)
                    {
                        // For IOS device
                        b_ios_device = TRUE;
                        DBG_INFO(("<BT_GATT> device is IOS, uuid = %s\r\n.", uuid_scan));

                        i_ret = bluetooth_gattc_ios_data_parse(uuid_scan, &ui4_final_cons, &i4_target_ID);
                        BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_directed_pairing, i_ret);
                    }
                    else
                    {
                        // For Android device
                        b_ios_device = FALSE;
                        DBG_INFO(("<BT_GATT> device is Android, adv_data + BT_GATT_MAX_UUID_LEN = %s\r\n.", ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN));

                        i4_msd_len = strlen(ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN);
                        memcpy(C1_00_58, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_msd_len - 8, 8);
                        if(strncmp(C1_00_58, GATTC_MANU_SPEC_DATA, 8) != 0)
                        {
                            // not the vizio product
                            DBG_INFO(("<BT_GATT> not vizio device. adv_data + BT_GATT_MAX_UUID_LEN = %s\r\n.", ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN));
                            b_can_scan = TRUE;
                            return BLUETOOTH_GATTC_OK;
                        }

                        i4_tag_offset = i4_msd_len - GATTC_EIR_MSD_FIX_LEN - 2;// tags present bitmap
                        i4_tag_bitmap_high = _bt_char_to_int(ble_scan_result.adv_data[i4_tag_offset + BT_GATT_MAX_UUID_LEN]);
                        i4_tag_bitmap_low = _bt_char_to_int(ble_scan_result.adv_data[i4_tag_offset + 1 + BT_GATT_MAX_UUID_LEN]);
                        DBG_LOG_PRINT(("<BT_GATT> i4_msd_len=%d,i4_tag_offset=%d,i4_tag_bitmap_high=%d,i4_tag_bitmap_low=%d\r\n.", i4_msd_len, i4_tag_offset,i4_tag_bitmap_high,i4_tag_bitmap_low));
                        memset(&variable_tag, 0, sizeof(EIR_MSD_VARIABLE_TAG));
                        variable_tag.signal_meter   = i4_tag_bitmap_low & 0x01;
                        variable_tag.mac_address    = i4_tag_bitmap_low & 0x02;
                        variable_tag.security_key   = i4_tag_bitmap_low & 0x04;
                        variable_tag.scan_parameter     = i4_tag_bitmap_low & 0x08;
                        variable_tag.connect_parameter = i4_tag_bitmap_high & 0x01;
                        variable_tag.pair_parameter     = i4_tag_bitmap_high & 0x02;
                        variable_tag.no_wakeup      = i4_tag_bitmap_high & 0x04;
                        variable_tag.more_bits_eight= i4_tag_bitmap_high & 0x08;
                        variable_tag.ui_key_offset += (variable_tag.more_bits_eight != 0 ? 2 : 0);

                        variable_tag.ui_key_offset += (variable_tag.mac_address != 0 ? 12 : 0);
                        variable_tag.ui_scan_offset += variable_tag.ui_key_offset;
                        variable_tag.ui_scan_offset += (variable_tag.security_key != 0 ? 2 : 0);
                        variable_tag.ui_connect_offset += variable_tag.ui_scan_offset;
                        variable_tag.ui_connect_offset += (variable_tag.scan_parameter != 0 ? 4 : 0);
                        variable_tag.ui_pair_offset += variable_tag.ui_connect_offset;
                        variable_tag.ui_pair_offset += (variable_tag.connect_parameter != 0 ? 8 : 0);
                        variable_tag.ui_wakeup_offset += variable_tag.ui_pair_offset;
                        variable_tag.ui_wakeup_offset += (variable_tag.pair_parameter != 0 ? 6 : 0);


                        if(variable_tag.scan_parameter != 0)
                        {
                            memcpy(c_msd_scan_para, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset - variable_tag.ui_scan_offset - 4, 4);
                            c_msd_scan_para[4] = '\0';
                        }

                        if(variable_tag.connect_parameter != 0)
                        {
                            memcpy(c_msd_conn_para, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset - variable_tag.ui_connect_offset - 8, 8);
                            c_msd_conn_para[8] = '\0';
                        }

                        if(variable_tag.pair_parameter != 0)
                        {
                            memcpy(c_msd_pair_para, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset - variable_tag.ui_pair_offset - 6, 6);
                            c_msd_pair_para[6] = '\0';
                            i4_min_rssi = _bt_bytes_to_int(c_msd_pair_para + 4) - 256;
                            t_rssi_meter_nfy.i4_min_rssi_threshold = i4_min_rssi;

                            i4_max_interval = _bt_bytes_to_int(c_msd_pair_para + 2);
                            i4_min_consecutive = _bt_bytes_to_int(c_msd_pair_para);
                            t_rssi_meter_nfy.i4_min_consecutive = i4_min_consecutive;
                            i4_get_rssi_threshold = i4_min_rssi;
                            DBG_LOG_PRINT(("<BT_GATT> c_msd_pair_para = %s, min_rssi = %d, max_interval = %d, min_consecutive = %d\r\n.", c_msd_pair_para, i4_min_rssi, i4_max_interval, i4_min_consecutive));
                        }
                        else
                        {
                        #ifdef APP_BLE_SUPPORT
                            i_ret = a_cfg_get_blegatt_rssi_threshold(&i4_get_rssi_threshold);
                            BT_GATT_CHECK_FAIL_RET(a_cfg_get_blegatt_rssi_threshold,i_ret);
                        #endif
                            DBG_INFO(("<BT_GATT> i4_get_rssi_threshold = %d\r\n.", i4_get_rssi_threshold));

                        }

                        if(variable_tag.more_bits_eight != 0)
                        {
                            // parse the 9th byte
                            i4_tag_nine_low = _bt_char_to_int(ble_scan_result.adv_data[i4_tag_offset - 1 + BT_GATT_MAX_UUID_LEN]);
                            i4_tag_nine_high =_bt_char_to_int(ble_scan_result.adv_data[i4_tag_offset - 2 + BT_GATT_MAX_UUID_LEN]);
                            DBG_LOG_PRINT(("<BT_GATT> i4_tag_nine_low=%d,i4_tag_nine_high=%d\r\n.", i4_tag_nine_low, i4_tag_nine_high));
                            variable_tag.max_rssi       = i4_tag_nine_low & 0x01;
                            variable_tag.signal_meter_timeout = i4_tag_nine_low & 0x02;
                            variable_tag.delta_value = i4_tag_nine_low & 0x04;
                            variable_tag.hardware_type = i4_tag_nine_low & 0x08;
                            variable_tag.more_bits_nine = i4_tag_nine_high & 0x08;

                            variable_tag.ui_maxrssi_offset += variable_tag.ui_wakeup_offset;
                            //variable_tag.ui_wakeup_offset += 2;
                            if(variable_tag.max_rssi != 0)
                            {

                                variable_tag.ui_maxrssi_offset += 2;
                                memcpy(c_msd_max_rssi, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset - variable_tag.ui_maxrssi_offset - 2, 2);
                                c_msd_max_rssi[2] = '\0';
                                int max_rssi = _bt_bytes_to_int(c_msd_max_rssi);
                                t_rssi_meter_nfy.i4_max_rssi_threshold = max_rssi;
                                DBG_LOG_PRINT(("<BT_GATT> c_msd_max_rssi = %s, max_rssi = %d\r\n.", c_msd_max_rssi, max_rssi));
                            }
                            variable_tag.ui_timeout_offset += variable_tag.ui_maxrssi_offset;

                            if(variable_tag.signal_meter_timeout != 0)
                            {

                                variable_tag.ui_timeout_offset += 2;
                                memcpy(c_msd_sign_timeout, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset - variable_tag.ui_timeout_offset - 2, 2);
                                c_msd_sign_timeout[2] = '\0';
                            }

                            if(variable_tag.delta_value != 0 && variable_tag.hardware_type != 0 )
                            {
                                char c_msd_delta[3] = {0};
                                memcpy(c_msd_delta, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset - variable_tag.ui_timeout_offset - 2, 2);
                                c_msd_delta[2] = '\0';
                                int delta_sign = _bt_bytes_to_int(c_msd_delta) & 0x80;
                                int delta_value = 0;
                                if(delta_sign == 0)
                                {
                                    delta_value = _bt_bytes_to_int(c_msd_delta);
                                }
                                else
                                {
                                    delta_value = _bt_bytes_to_int(c_msd_delta) - 256;
                                }
                                i4_get_rssi_threshold = (i4_get_rssi_threshold == 0) ? -50 : i4_get_rssi_threshold;
                                i4_get_rssi_threshold += delta_value;
                                DBG_ERROR(("<BT_GATT> delta_value = %d, c_msd_delta = %s, i4_get_rssi_threshold = %d\r\n.", variable_tag.delta_value, c_msd_delta, i4_get_rssi_threshold));
                            }

                        }
                    }

                    memset(scan_ble_device, 0, sizeof(scan_ble_device));
                    i_ret = a_cfg_get_blegatt_macaddress_threshold(scan_ble_device);
                    BT_GATT_CHECK_FAIL_RET(a_cfg_get_blegatt_macaddress_threshold,i_ret);

                    if (bt_gatt_get_dbg_level() & DBG_LEVEL_INFO)
                    {
                        for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
                        {
                            if(strncmp(scan_ble_device[i].c_mac_address, "000000000000", MAC_ADDRESS_LENGTH_LEN) != 0)
                            {
                                //scan_ble_device[i].c_mac_address[MAC_ADDRESS_LENGTH_LEN] = '\0';
                                DBG_LOG_PRINT(("<BT_GATT> cached mac_address: %s, target_ID: %d, IOS: %s\r\n.",
                                                                        scan_ble_device[i].c_mac_address,
                                                                        scan_ble_device[i].ui_target_ID,
                                                                        scan_ble_device[i].b_is_IOS ? "Yes" : "No"));
                            }
                        }
                    }

                    if(b_ios_device)
                    {
                        // For IOS device
                        #ifdef APP_BLE_SUPPORT
                        i_ret = a_cfg_get_blegatt_rssi_threshold(&i4_get_rssi_threshold);
                        BT_GATT_CHECK_FAIL_RET(a_cfg_get_blegatt_rssi_threshold,i_ret);
                        i4_get_rssi_threshold -= GATTC_ANDROID_IOS_OFFSET;// iOS need weaker rssi
                        #endif

                        int j;
                        for(i = 0, j = 0; j < MAC_ADDRESS_LENGTH_LEN + 1; j++)
                        {
                            if(uuid_scan[19 + j] != '-')
                            {
                                c_mac_addr[i++] = uuid_scan[19 + j];
                            }
                        }
                    }
                    else
                    {
                        // For Android device
                        memcpy(c_mac_addr, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset - 12, MAC_ADDRESS_LENGTH_LEN);
                        i4_target_ID = (_bt_bytes_to_int(ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset + 2) >> 3) | ((_bt_char_to_int(ble_scan_result.adv_data[i4_tag_offset + 5 + BT_GATT_MAX_UUID_LEN]) & 0x1) << 5);
                        i4_ble_version = (_bt_bytes_to_int(ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN + i4_tag_offset + 4) >> 1) & 0x7F;
                    }

                    DBG_LOG_PRINT(("<BT_GATT> i4_target_ID = %d, c_mac_addr=[%s], btaddr=[%s]\r\n", i4_target_ID, c_mac_addr, ble_scan_result.btaddr));
                    b_cache_mac = FALSE;
                    for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
                    {
                        if(strncmp(scan_ble_device[i].c_mac_address, "000000000000", MAC_ADDRESS_LENGTH_LEN) != 0
                            && (strncmp(scan_ble_device[i].c_mac_address, c_mac_addr, MAC_ADDRESS_LENGTH_LEN) == 0))
                        {
                            i4_cache_index = i;
                            b_cache_mac = TRUE;
                            if((i4_target_ID != 0)
                                && (i4_target_ID != scan_ble_device[i].ui_target_ID))
                            {
                                DBG_LOG_PRINT(("<BT_GATT> target id is different with target id in scan_ble_device\r\n"));
                                if (variable_tag.signal_meter != 0)
                                {
                                    DBG_INFO(("<BT_GATT> rssi meter mode, continue.\r\n"));
                                    break;
                                }
                                b_can_scan = TRUE;
                                return BLUETOOTH_GATTC_OK;
                            }
                            break;
                        }
                    }

                    if (variable_tag.signal_meter != 0 && b_rssi_show)
                    {
                        _bt_gattc_set_rssi_meter_data(ble_scan_result.rssi, i4_get_rssi_threshold, c_mac_addr);

                        b_can_scan = TRUE;
                        break;
                    }

                    i4_get_rssi_threshold = (i4_get_rssi_threshold == 0) ? -60 : i4_get_rssi_threshold;
                    // whether allow pair
                    bluetooth_gattc_allow_pair(c_mac_addr, ble_scan_result.rssi, i4_get_rssi_threshold, i4_min_consecutive, i4_max_interval, &b_allow_pair);
                }

                DBG_INFO(("<BT_GATT> i4_get_rssi_threshold = %d\r\n.", i4_get_rssi_threshold));
                DBG_INFO(("<BT_GATT> b_directed_pair = %s\r\n.", (b_directed_pair == TRUE) ? "TRUE" : "FALSE"));
                DBG_INFO(("<BT_GATT> b_allow_pair = %s\r\n.", (b_allow_pair == TRUE) ? "TRUE" : "FALSE"));
                DBG_INFO(("<BT_GATT> b_rssi_show = %s\r\n.", (b_rssi_show == TRUE) ? "TRUE" : "FALSE"));
                DBG_INFO(("<BT_GATT> b_cache_mac = %s\r\n", (b_cache_mac == TRUE) ? "TURE" : "FALSE"));
                if(b_directed_pair // directed pairing
                || (b_allow_pair && (i4_target_ID == 0)) // for proximity pairing
                || (b_cache_mac && i4_target_ID != 0)// for direct connected
                || _bt_gattc_allow_special_device_4_test(b_allow_pair, b_cache_mac, i4_target_ID))
                {
                    char C255_wirte[13];
                    char* C_C255_write = NULL;
                    memset(write_c255, 0, 17);
                    if(b_ios_device || b_directed_pair)
                    {
                        // For IOS device
                        i_write_type = GATTC_WRITE_RESPONSE;
                        memcpy(server_data_array[i_scan_number].ios_uuid_scan, uuid_scan, 37);
                        if(!b_cache_mac)
                        {
                            if (i4_target_ID == 0)
                            {
                                ui4_final_cons = ui4_final_cons & 0xFFF7;
                            }
                        }
                        else
                        {
                            ui4_final_cons = (ui4_final_cons & 0xFE07) | (scan_ble_device[i4_cache_index].ui_target_ID << 3);
                        }

                        INT32 first_data = ui4_final_cons >> 12;
                        C_C255_write = _bt_int_to_char(first_data, C255_wirte, 2);
                        INT32 second_data = (ui4_final_cons >> 8) & 0x0f;
                        C_C255_write = _bt_int_to_char(second_data, C255_wirte, 3);
                        INT32 third_data = (ui4_final_cons >> 4) & 0x00f;
                        C_C255_write = _bt_int_to_char(third_data, C255_wirte, 0);
                        INT32 forth_data = ui4_final_cons & 0x000f;
                        C_C255_write = _bt_int_to_char(forth_data, C255_wirte, 1);
                        memcpy(C_C255_write + 4, "11C10058", 8);
                    }
                    else
                    {
                        // For Android device
                        i_write_type = GATTC_WRITE_COMMAND;
                        memcpy(manufacturer_data, ble_scan_result.adv_data + BT_GATT_MAX_UUID_LEN, i4_msd_len);
                        memcpy(c_msd_security, manufacturer_data + i4_tag_offset - variable_tag.ui_key_offset - 2, 2);
                        memcpy(C255_wirte, manufacturer_data + i4_tag_offset + 2, 12);
                        if(!b_cache_mac)
                        {
                            // no cache
                            C255_wirte[1] = '0';
                            C_C255_write = C255_wirte;
                        }
                        else
                        {
                            // cached
                            //C_C255_write = _bt_int_to_char(scan_ble_device[i4_cache_index].ui_target_ID, C255_wirte);
                            UINT8 ui_target_data = (scan_ble_device[i4_cache_index].ui_target_ID) << 3;
                            UINT8 ui_high = (ui_target_data & 0xf0) >> 4;
                            C_C255_write = _bt_int_to_char(ui_high, C255_wirte, 0);
                            UINT8 ui_low = ui_target_data & 0x0f;
                            C_C255_write = _bt_int_to_char(ui_low, C255_wirte, 1);
                        }
                    }

                    C_C255_write[12] = '\0';
                    str2bytes(C_C255_write, write_c255);
                    revert_bytes(write_c255, 6);
                    c_msd_security[2] = '\0';
                    DBG_INFO(("<BT_GATT> c_msd_security = %s, i_scan_number=%d\r\n", c_msd_security, i_scan_number));

                    if(i_scan_number == 0)
                    {
                        memcpy(&(server_data_array[i_scan_number].ble_scan_result), &ble_scan_result, sizeof(BT_GATTC_SCAN_RST_T));
                        memcpy(server_data_array[i_scan_number].device_mac_addr, c_mac_addr, MAC_ADDRESS_LENGTH_LEN + 1);
                        i_scan_number++;

                        //c_thread_delay(3000);
                        i_ret = a_mtkapi_bt_gattc_stop_scan();
                        //c_thread_delay(5000);
                        BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_stop_scan,i_ret);

                        i4_target_id = i4_target_ID;
                        // call open function
                        //i_ret = c_btm_gattc_open(ble_scan_result.btaddr, TRUE, 0);
                        DBG_INFO(("<BT_GATT>bt_gattc_app_client_if=%d,btaddr=[%s]\n",bt_gattc_app_client_if,ble_scan_result.btaddr));
                        i_ret = a_mtkapi_bt_gattc_open(bt_gattc_get_client_if(),
                                                       ble_scan_result.btaddr,
                                                       TRUE,
                                                       0);
                        BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_open,i_ret);
                        //CHAR uuid[BT_GATT_MAX_UUID_LEN] = {0};
                        a_mtkapi_bt_gattc_search_service(bt_gattc_get_client_if(),
                                                         ble_scan_result.adv_data);
                    }
                    else if(i_scan_number > 0)
                    {
                        int i = 0, same_index = 0;
                        BOOL b_find_same = FALSE;
                        for(; i < MAX_SCAN_DEVICE; i++)
                        {
                            if(strncmp(server_data_array[i].device_mac_addr, c_mac_addr, MAC_ADDRESS_LENGTH_LEN) == 0)
                            {
                                DBG_INFO(("<BT_GATT> Find the same bluetooth mac address.\r\n"));
                                b_find_same = TRUE;
                                same_index = i;
                                break;
                            }
                        }

                        if(!b_find_same || (b_find_same && server_data_array[same_index].i_connect_sign == GATTC_DISCONNECT))
                        {
                            //i_scan_number++;
                            DBG_ERROR(("<BT_GATT> start open BLE connection.\r\n"));
                            //strncpy(ble_scan_result_array[i_scan_number].btaddr, ble_scan_result.btaddr, 18);
                            for(i = 0; i < MAX_SCAN_DEVICE; i++)
                            {
                                if(server_data_array[i].ble_connect_result.conn_id == 0)
                                {
                                    memcpy(&(server_data_array[i].ble_scan_result), &ble_scan_result, sizeof(BT_GATTC_SCAN_RST_T));
                                    memcpy(server_data_array[i].device_mac_addr, c_mac_addr, MAC_ADDRESS_LENGTH_LEN + 1);
                                    break;
                                }
                            }
                            i_scan_number = (b_find_same == TRUE) ? i_scan_number : i_scan_number+1;

                            c_thread_delay(3000);

                            i_ret = a_mtkapi_bt_gattc_stop_scan();
                            c_thread_delay(200);
                            BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_stop_scan,i_ret);

                            b_allow_scan = FALSE;
                            i4_target_id = i4_target_ID;

                            // call open function
                            //i_ret = c_btm_gattc_open(ble_scan_result.btaddr, TRUE, 0);
                            DBG_INFO(("<BT_GATT> bt_gattc_app_client_if=%d\n",bt_gattc_app_client_if));
                            i_ret = a_mtkapi_bt_gattc_open(bt_gattc_app_client_if,
                                                        ble_scan_result.btaddr,
                                                        TRUE,
                                                        0);
                            BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_open,i_ret);
                        }
                    }
                }

                b_can_scan = TRUE;
            }
        }
        break;
#if 0
        case BT_GATT_SEARCH_SERVICE_CB:
            {
                char uuid_service[37];
                int search_index = pt_bt_msg->ui4_data2;

                c_strncpy(uuid_service, server_data_array[search_index].ble_service_result.srvc_id.id.uuid, BT_GATT_MAX_UUID_LEN);

                DBG_INFO(("<BT_GATT> show search service result: \r\n"));
                DBG_INFO(("<BT_GATT> conn_id = %d.\r\n", server_data_array[search_index].ble_service_result.conn_id));
                DBG_INFO(("<BT_GATT> service uuid = %s.\r\n",uuid_service));

                //start to get char
                server_data_array[search_index].ui4_gatt_db_loop_idx = 0;
                i_ret = _bt_gattc_get_char(search_index);
                BT_GATT_CHECK_FAIL_RET(_bt_gattc_get_char,i_ret);
            }
            break;

        case BT_GATT_GET_CHAR_CB:
            {
                int getchar_index = pt_bt_msg->ui4_data2;
                int get_char_number = (int)pt_bt_msg->ui4_data3;//server_data_array[getchar_index].i_get_char_out;
                bluetooth_gatt_get_char_rst_t get_char;
                memcpy(&get_char, &(server_data_array[getchar_index].ble_char_result_array[get_char_number]), sizeof(bluetooth_gatt_get_char_rst_t));

                char uuid_char[37] = {0};
                //_bt_gattc_print_uuid(&(get_char.char_id.uuid),uuid_char);
                c_strncpy(uuid_char, get_char.char_id.uuid, BT_GATT_MAX_UUID_LEN);

                if(c_strcmp(uuid_char, GATTC_CHAR_C0_UUID) == 0)
                {
                    DBG_ERROR(("<BT_GATT> register for C0.\r\n"));

                    if (_bt_gattc_get_char_handle(get_char.conn_id, get_char.char_id.uuid, &h_char, _BT_GATTC_GET_TYPE_CHAR) != BLUETOOTH_GATTC_OK)
                    {
                        DBG_ERROR(("<BT_GATT> Cannot get character handle.\r\n"));
                        break;
                    }

                    h_char = server_data_array[getchar_index].aui4_char_result_handle[get_char_number];

                    server_data_array[getchar_index].ui4_reg_char_handle = h_char;
                    // call register notify function
                    i_ret = c_btm_bt_gattc_reg_noti(server_data_array[getchar_index].ble_connect_result.client_if,
                                                    server_data_array[getchar_index].ble_connect_result.btaddr,
                                                    h_char);
                    BT_GATT_CHECK_FAIL_RET(c_btm_bt_gattc_reg_noti,i_ret);

                    server_data_array[getchar_index].i_write_char_number = 0;
                }
                else if(c_strcmp(uuid_char, GATTC_CHAR_C255_UUID) == 0)
                {
                    INT32   send_conn_id = 0;
                    INT32   i = 0;
                    BOOL    b_connetion_closure = FALSE;

                    server_data_array[getchar_index].ui4_response_msg_len = 0;
                    server_data_array[getchar_index].i_read_char_number = 0;

                    h_char = server_data_array[getchar_index].aui4_char_result_handle[get_char_number];

                    DBG_ERROR(("<BT_GATT> write for h_char=%d,conn_id=%d, C255 bt_addr=[%s].\r\n",
                                                h_char,
                                                get_char.conn_id,
                                                server_data_array[getchar_index].ble_scan_result.btaddr));

                    send_conn_id = get_char.conn_id;
                    memset(write_c255 + 6, 0, 11);
                    if(/*TRUE == a_misc_uli_get_update_on()|| TRUE == a_uli_update_upg_in_progress() || */b_is_poweroff)
                    {
                        // audio shutting down
                        write_c255[6] = 0x01;
                        write_c255[7] = (b_is_poweroff) ? 0x01 : 0x03;
                        b_connetion_closure = TRUE;
                        DBG_ERROR(("<BT_GATT> audio have shut down, "));
                    }

                    if(i4_ble_version != 0x47)
                    {
                        // unsupport ble protocol version
                        write_c255[6] = 0x02;
                        write_c255[7] = 0x47;
                        write_c255[8] = 0x47;
                        b_connetion_closure = TRUE;
                        DBG_ERROR(("<BT_GATT> unsupport ble protocol version, %d, ", i4_ble_version));
                    }

                    if(!(strncmp(c_msd_security, "01", 2) == 0 || strncmp(c_msd_security, "00", 2) == 0))
                    {
                        // invalid security key
                        write_c255[6] = 0x03;
                        write_c255[7] = atoi(c_msd_security);
                        write_c255[8] = 0xFF;
                        b_connetion_closure = TRUE;
                        DBG_ERROR(("<BT_GATT> invalid security key, %s, ", c_msd_security));
                    }

                    if(b_cache_full)
                    {
                        // database is full, need connection closure
                        write_c255[6] = 0x05;
                        write_c255[7] = 0x0a;
                        b_connetion_closure = TRUE;
                        DBG_ERROR(("<BT_GATT> database is full, "));
                    }

                    if(!b_connetion_closure)
                    {
                        DBG_ERROR(("<BT_GATT> connection establish.\r\n"));

                        write_c255[6] = 0x00;
                        BT_LOCAL_DEV local_dev_info;
                        c_btm_get_local_dev_info(&local_dev_info);
                        _bt_gattc_btaddr_stoh(local_dev_info.bdAddr, write_c255 + 7);
                        if(b_cache_mac)
                        {
                            write_c255[13] = 0x06;
                        }
                        else
                        {
                            write_c255[13] = 0x03;
                        }
                        write_c255[14] = 0xEC;
                        write_c255[15] = 0xCE;
                        write_c255[16] = 0x9C;
                    }
                    else
                    {
                        DBG_ERROR(("connection closure.\r\n"));
                    }

                    for (i = 0; i < 17; i++)
                    {
                        DBG_ERROR(("<BT_GATT> write_c255[%d] = %2x\r\n.", i, write_c255[i]));
                    }

                    i_write_type = (b_ios_device == TRUE) ? GATTC_WRITE_RESPONSE : GATTC_WRITE_COMMAND;
                    //i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id, &send_service_uuid, send_service_inst_id, &send_char_uuid, send_char_inst_id, i_write_type, 17, 0, (char*)write_c255);

                    i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id,
                                                      h_char,
                                                      i_write_type,
                                                      17,
                                                      0,
                                                      (char*)write_c255);
                    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);
                }
                else
                {
                    i_ret = _bt_gattc_get_char(getchar_index);
                    BT_GATT_CHECK_FAIL_RET(_bt_gattc_get_char,i_ret);
                }
            }
            break;
#endif
        case BT_GATT_REG_NOTI_CB:
            {
                BT_GATTC_GET_REG_NOTI_RST_T *reg_notify_info = (BT_GATTC_GET_REG_NOTI_RST_T*)pt_bt_msg->ui4_data3;
                int i = 0;
                int conn_id = 0;

                for (i = 0; i < MAX_SCAN_DEVICE; i++)
                {
                    DBG_INFO(("<BT_GATT> reg_notify_handle=%d,ui4_reg_char_handle=%d\n",reg_notify_info->handle,
                                                                    server_data_array[i].ui4_reg_char_handle));

                    if (reg_notify_info->handle == server_data_array[i].ui4_reg_char_handle)
                    {
                        conn_id = server_data_array[i].ble_service_result.conn_id;
                        server_data_array[i].pt_registered_char = &(server_data_array[i].ble_char_result_array[server_data_array[i].i_get_char_out]);
                        DBG_ERROR(("<BT_GATT> BT_GATT_REG_NOTI_CB i = %d\r\n.", i));
                        break;
                    }
                }
                if (MAX_SCAN_DEVICE == i)
                {
                    DBG_INFO(("<BT_GATT> BT_GATT_REG_NOTI_CB invalid register notification, ignore!!\r\n.", conn_id, i));
                    break;
                }
                if (b_ios_device)
                {
                    i_ret = _bt_gattc_get_descr(conn_id, reg_notify_info->handle);
                    BT_GATT_CHECK_FAIL(_bt_gattc_get_descr,i_ret);
                }
                else
                {
                    DBG_INFO(("<BT_GATT> BT_GATT_REG_NOTI_CB conn_id = %d, i=%d\r\n.", conn_id, i));
                    i_ret = _bt_gattc_get_char(i);
                    BT_GATT_CHECK_FAIL_RET(_bt_gattc_get_char,i_ret);
                }
            }
            break;
#if 0
        case BT_GATT_GET_DESC_CB:
            {
                bluetooth_gatt_get_descriptor_rst_t *get_desc_value = (bluetooth_gatt_get_descriptor_rst_t*)pt_bt_msg->ui4_data3;

                char    get_descrp_uuid[37];
                char    get_srv_uuid[37];
                int     send_conn_id;
                int     send_desc_inst_id;

                c_strncpy(get_descrp_uuid, get_desc_value->descr_id.uuid, BT_GATT_MAX_UUID_LEN);
                c_strncpy(get_srv_uuid, get_desc_value->srvc_id.id.uuid, BT_GATT_MAX_UUID_LEN);

                if((strncmp(get_descrp_uuid + 4, "2902", 4) == 0) && (strncmp(get_srv_uuid, GATTC_SERVICE_UUID, 8) == 0))
                {
                    DBG_ERROR(("<BT_GATT> get desc 2902 uuid: %s conn_id=%d.\r\n", get_descrp_uuid, get_desc_value->conn_id));

                    char desc_value[]= {0x02, 0x00};

                    send_conn_id = get_desc_value->conn_id;

                    //send_desc_inst_id = get_desc_value->descr_id.inst_id;
                    if (_bt_gattc_get_char_handle(send_conn_id,
                                                  get_desc_value->descr_id.uuid,
                                                  &send_desc_inst_id,
                                                  _BT_GATTC_GET_TYPE_DESC) != BLUETOOTH_GATTC_OK)
                    {
                        DBG_ERROR(("<BT_GATT>%d:get char handel fail\n", __LINE__));
                        break;
                    }

                    DBG_INFO(("<BT_GATT> BT_GATT_GET_DESC_CB line %d: send_conn_id=%d\n", __LINE__, send_conn_id));

                    i_ret = c_btm_gattc_write_descr(send_conn_id,
                                                        send_desc_inst_id,
                                                        2,
                                                        2,
                                                        0,
                                                        desc_value);
                    BT_GATT_CHECK_FAIL(c_btm_gattc_write_descr,i_ret);
                }
                else
                {
                    //i_ret = _bt_gattc_get_descr(get_desc_value->conn_id, get_desc_value->char_id.inst_id);
                    if (_bt_gattc_get_char_handle(get_desc_value->conn_id,
                                                  get_desc_value->char_id.uuid,
                                                  &send_desc_inst_id,
                                                  _BT_GATTC_GET_TYPE_CHAR) != BLUETOOTH_GATTC_OK)
                    {
                        DBG_ERROR(("<BT_GATT>%d:get char handel fail\n", __LINE__));
                        break;
                    }
                    i_ret = _bt_gattc_get_descr(get_desc_value->conn_id, send_desc_inst_id);
                    BT_GATT_CHECK_FAIL(_bt_gattc_get_descr,i_ret);
                }

                if (get_desc_value)
                {
                    c_mem_free(get_desc_value);
                }
            }
            break;
#endif
        case BT_GATT_WRITE_DESC_CB:
            {
                INT32 i4_get_idx = 0;
                BOOL    b_found = FALSE;
                BT_GATTC_WRITE_DESCR_RST_T *write_desc_info = (BT_GATTC_WRITE_DESCR_RST_T *)pt_bt_msg->ui4_data3;

                DBG_INFO(("<BT_GATT> BT_GATT_WRITE_DESC_CB conn_id = %d\r\n.", write_desc_info->conn_id));
                for (i4_get_idx = 0; i4_get_idx < MAX_SCAN_DEVICE; i4_get_idx++)
                {
                    if (server_data_array[i4_get_idx].ble_connect_result.conn_id == write_desc_info->conn_id)
                    {
                        b_found = TRUE;
                        DBG_INFO(("<BT_GATT> BT_GATT_WRITE_DESC_CB Found = %d\r\n.", i4_get_idx));
                        break;
                    }
                }

                if (b_found)
                {
                    i_ret = _bt_gattc_get_char(i4_get_idx);
                    BT_GATT_CHECK_FAIL_RET(_bt_gattc_get_char,i_ret);
                }
                else
                {
                    DBG_INFO(("<BT_GATT> BT_GATT_WRITE_DESC_CB Not Found char.\r\n.", i4_get_idx));
                }
            }
            break;
        case BT_GATT_READ_CHAR_CB:
            {
                INT32  i4_idx = 0;
                UINT32 i_read_scan_number = pt_bt_msg->ui4_data2;

                char uuid_char_read[37] = {0};

                for (i4_idx = 0; i4_idx < server_data_array[i_read_scan_number].t_gatt_db.count; i4_idx++)
                {
                    if (NULL == server_data_array[i_read_scan_number].t_gatt_db.gatt_db_element)
                    {
                        DBG_ERROR(("<BT_GATT> %d:db_element is NULL\n", __LINE__));
                        return BLUETOOTH_GATTC_FAILED;
                    }

                    if (BT_GATTC_DB_CHARACTERISTIC == server_data_array[i_read_scan_number].t_gatt_db.gatt_db_element[i4_idx].type
                        && (server_data_array[i_read_scan_number].t_gatt_db.gatt_db_element[i4_idx].attribute_handle
                            == server_data_array[i_read_scan_number].ble_read_result.read_data.handle))
                    {
                        c_strncpy(uuid_char_read, server_data_array[i_read_scan_number].t_gatt_db.gatt_db_element[i4_idx].uuid, BT_GATT_MAX_UUID_LEN);
                        break;
                    }
                }
                DBG_INFO(("<BT_GATT> char_uuid = %s.\r\n", uuid_char_read));

                char value_bytes[60];
                _bt_gattc_print_uint8(server_data_array[i_read_scan_number].ble_read_result.read_data.value.value, server_data_array[i_read_scan_number].ble_read_result.read_data.value.len, value_bytes);
                DBG_INFO(("<BT_GATT> value_bytes = %s\r\n", value_bytes));

                // read c1, c2,...
                if(server_data_array[i_read_scan_number].i_read_char_number != 0)
                {
                    if(server_data_array[i_read_scan_number].c0_header.i2_total_length == 0)
                    {
                        DBG_ERROR(("<BT_GATT> c0_header.i2_total_length is 0.\r\n"));
                    }
                    else
                    {
                        if(b_is_NS)
                        {
                            memcpy(Ns, server_data_array[i_read_scan_number].ble_read_result.read_data.value.value, AES_BLOCK_SIZE);
                            char Ns_bytes[50];
                            _bt_gattc_print_uint8(Ns, AES_BLOCK_SIZE, Ns_bytes);
                            DBG_INFO(("<BT_GATT> Ns_bytes = %s\r\n", Ns_bytes));
                            char Nc_bytes[50];
                            _bt_gattc_print_uint8(Nc, AES_BLOCK_SIZE, Nc_bytes);
                            DBG_INFO(("<BT_GATT> Nc_bytes = %s\r\n", Nc_bytes));

                            _bt_AES_ecb_encrypt(HC);

                            // start write response msg to gatt server
                            i_ret = bluetooth_gatt_write_data(i_read_scan_number);
                            BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_write_data,i_ret);
                            return 0;
                        }

                        // malloc request_msg from c1
                        if(server_data_array[i_read_scan_number].i_read_char_number == 1 && server_data_array[i_read_scan_number].c0_header.i_fragment_number == 0)
                        {
                            if(server_data_array[i_read_scan_number].c0_header.i_security_data == GATTC_ADD_SECURITY)
                            {
                                // for security
                                UINT32 tot_request_msg_length = server_data_array[i_read_scan_number].c0_header.i2_total_length + 4;
                                BT_GATT_FREE(server_data_array[i_read_scan_number].request_msg);
                                BT_GATT_MALLOC(server_data_array[i_read_scan_number].request_msg, tot_request_msg_length + 1);
                                memset(server_data_array[i_read_scan_number].request_msg, 0, tot_request_msg_length + 1);
                                server_data_array[i_read_scan_number].request_msg[0] = (char)(server_data_array[i_read_scan_number].c0_header.i2_payload_length & 0x00ff);
                                server_data_array[i_read_scan_number].request_msg[1] = (char)((server_data_array[i_read_scan_number].c0_header.i2_payload_length >> 8) & 0x00ff);
                                server_data_array[i_read_scan_number].request_msg[2] = server_data_array[i_read_scan_number].c0_header.i_message_type;
                                server_data_array[i_read_scan_number].request_msg[3] = server_data_array[i_read_scan_number].c0_header.i_check_sum;
                                server_data_array[i_read_scan_number].ui4_request_msg_len = 4;
                            }
                            else
                            {
                                // for non-security
                                UINT32 pre_request_msg_length = strlen(GATTC_PRE_REQUEST_IP);
                                UINT32 tot_request_msg_length = server_data_array[i_read_scan_number].c0_header.i2_total_length + pre_request_msg_length;
                                BT_GATT_FREE(server_data_array[i_read_scan_number].request_msg);
                                BT_GATT_MALLOC(server_data_array[i_read_scan_number].request_msg, tot_request_msg_length + 1);
                                memset(server_data_array[i_read_scan_number].request_msg, 0, tot_request_msg_length + 1);
                                memcpy(server_data_array[i_read_scan_number].request_msg, GATTC_PRE_REQUEST_IP, pre_request_msg_length);
                                server_data_array[i_read_scan_number].ui4_request_msg_len = pre_request_msg_length;
                            }

                        }

                        // copy to request_msg from each read_char.read_data.value.value
                        UINT32 ui4_msg_offset = (server_data_array[i_read_scan_number].c0_header.i_security_data == GATTC_ADD_SECURITY) ? 4 : strlen(GATTC_PRE_REQUEST_IP);
                        UINT32 pre_request_url_length = server_data_array[i_read_scan_number].c0_header.i2_total_length + ui4_msg_offset;
                        if(server_data_array[i_read_scan_number].i_read_char_number != 0 && server_data_array[i_read_scan_number].ui4_request_msg_len < pre_request_url_length)
                        {
                            // concatenate all payload to be whole msg
                            if((pre_request_url_length - server_data_array[i_read_scan_number].ui4_request_msg_len) > server_data_array[i_read_scan_number].ble_read_result.read_data.value.len)
                            {
                                memcpy(server_data_array[i_read_scan_number].request_msg + server_data_array[i_read_scan_number].ui4_request_msg_len, (char*)server_data_array[i_read_scan_number].ble_read_result.read_data.value.value, server_data_array[i_read_scan_number].ble_read_result.read_data.value.len);
                                server_data_array[i_read_scan_number].ui4_request_msg_len += server_data_array[i_read_scan_number].ble_read_result.read_data.value.len;

                                // only use the first char uuid to read data
                                server_data_array[i_read_scan_number].i_read_char_number++;
                                //DBG_INFO(("<BT_GATT> i4_read_char_number = %d.\r\n", server_data_array[i_read_scan_number].i_read_char_number));
                                uint8_t i_read_char_number = server_data_array[i_read_scan_number].i_read_char_number;
                                int receive_conn_id = server_data_array[i_read_scan_number].ble_char_result_array[i_read_char_number].conn_id;
                                //int receive_char_inst_id = server_data_array[i_read_scan_number].ble_char_result_array[i_read_char_number].char_id.inst_id;
                                h_char = server_data_array[i_read_scan_number].aui4_char_result_handle[i_read_char_number];
                                DBG_INFO(("<BT_GATT> server_data_array[%d].h_char = %d\r\n",i_read_scan_number, h_char));

                                i_ret = a_mtkapi_bt_gattc_read_char(receive_conn_id, h_char, 0);
                                //i_ret = a_mtkapi_bt_gattc_read_char(receive_conn_id, &receive_service_uuid, receive_service_inst_id, &receive_char_uuid, receive_char_inst_id, 0);
                                BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_read_char,i_ret);
                            }
                            else
                            {
                                memcpy(server_data_array[i_read_scan_number].request_msg + server_data_array[i_read_scan_number].ui4_request_msg_len, (char*)server_data_array[i_read_scan_number].ble_read_result.read_data.value.value, pre_request_url_length - server_data_array[i_read_scan_number].ui4_request_msg_len);
                                server_data_array[i_read_scan_number].ui4_request_msg_len += (pre_request_url_length - server_data_array[i_read_scan_number].ui4_request_msg_len);
                            }
                        }

                        // send the msg to http server
                        DBG_INFO(("<BT_GATT> ui4_request_msg_len = %d, pre_request_url_length = %d\r\n", server_data_array[i_read_scan_number].ui4_request_msg_len, pre_request_url_length));
                        if(server_data_array[i_read_scan_number].ui4_request_msg_len == pre_request_url_length)
                        {
                            UINT32 ui4_request_msg_len = server_data_array[i_read_scan_number].ui4_request_msg_len;
                            server_data_array[i_read_scan_number].request_msg[ui4_request_msg_len] = '\0';
                            DBG_ERROR(("<BT_GATT> final request_msg = %s\r\n", server_data_array[i_read_scan_number].request_msg));
                            DBG_ERROR(("<BT_GATT> final request_msg length = %d\r\n", server_data_array[i_read_scan_number].ui4_request_msg_len));

                            if(0)
                            {
                                b_allow_scan = TRUE;
                                // start another scan, top to 5 server
                                i_ret = a_mtkapi_bt_gattc_set_scan_parameters(server_data_array[i_read_scan_number].ble_connect_result.client_if,
                                                                        GATTC_SCAN_INTERVAL,
                                                                        GATTC_SCAN_WINDOW);
                                BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_set_scan_parameters,i_ret);

                                // call scan function
                                i_ret = a_mtkapi_bt_gattc_scan();
                                BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_scan,i_ret);
                                //i_scan_number++;//
                            }

                            // start write response msg to gatt server
                            i_ret = bluetooth_gatt_write_data(i_read_scan_number);
                            BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_write_data,i_ret);
                        }
                    }
                }
            }
            break;

        case BT_GATT_WRITE_CHAR_CB:
            {
                UINT32              i_write_scan_number = pt_bt_msg->ui4_data2;
                GATT_SERVER_DATA    *pt_cur_server_data = NULL;
                INT32               i = 0;
                BT_GATTC_DB_ELEMENT_T *pt_char_elem = NULL;

                char response_bytes[MAX_CHARACTERISTIC_LIMIT + 1];
                int write_conn_id;
                char write_char_char_uuid[BT_GATT_MAX_UUID_LEN];

                pt_cur_server_data = &server_data_array[i_write_scan_number];
                if (NULL == pt_cur_server_data)
                {
                    DBG_ERROR(("<BT_GATT> Invalid server data.\r\n"));
                    break;
                }

                h_char = pt_cur_server_data->ble_write_result.handle;
                DBG_INFO(("<BT_GATT> Write char handle=%d\r\n",h_char));


                if (NULL == pt_cur_server_data->t_gatt_db.gatt_db_element)
                {
                    DBG_ERROR(("<BT_GATT> %d:db_element is NULL\n", __LINE__));
                    return BLUETOOTH_GATTC_FAILED;
                }

                for (i = 0; i < pt_cur_server_data->t_gatt_db.count; i++)
                {
                    if ((BT_GATTC_DB_CHARACTERISTIC == pt_cur_server_data->t_gatt_db.gatt_db_element[i].type||
                         (c_strcmp(pt_cur_server_data->t_gatt_db.gatt_db_element[i].uuid, GATTC_CHAR_C255_UUID) == 0)||
                         (c_strcmp(pt_cur_server_data->t_gatt_db.gatt_db_element[i].uuid, GATTC_CHAR_C80_UUID) == 0))&&
                          h_char == pt_cur_server_data->t_gatt_db.gatt_db_element[i].attribute_handle)
                    {
                        pt_char_elem = &pt_cur_server_data->t_gatt_db.gatt_db_element[i];
                        break;
                    }
                }

                if (NULL == pt_char_elem)
                {
                    DBG_ERROR(("<BT_GATT> Get char by handle fail.\r\n"));
                    break;
                }

                c_strncpy(write_char_char_uuid, pt_char_elem->uuid, BT_GATT_MAX_UUID_LEN);

                DBG_INFO(("<BT_GATT> write char char uuid = %s.\r\n", write_char_char_uuid));

                //sleep(3);
                if((pt_cur_server_data->ui4_response_msg_len == 0) && (pt_cur_server_data->i_read_char_number != 0))
                {
                    BT_GATT_EXTI_FUNCTION();
                    return BLUETOOTH_GATTC_OK;
                }

                if(c_strcmp(write_char_char_uuid, GATTC_CHAR_C255_UUID) == 0)
                {
                    _bt_gattc_play_audio_tone();
                    pt_cur_server_data->i_write_char_number--;
                }
                /*****************************************write C0 for next fragment*******************************************/
                else if(c_strcmp(write_char_char_uuid, GATTC_CHAR_C80_UUID) == 0)
                {
                    // next fragment
                    uint8_t c_check_sum;
                    int send_conn_id;
                    int i_count = 0;

                    DBG_INFO(("<BT_GATT>write C0 for next fragment\n"));

                    pt_cur_server_data->i_write_char_number = 0;

                    int ui4_response_msg_len = pt_cur_server_data->ui4_response_msg_len + pt_cur_server_data->ui4_write_msg_len;

                    c_check_sum = 0x00;
                    for(i_count = 0; i_count < ui4_response_msg_len; i_count++)
                    {
                        c_check_sum ^= pt_cur_server_data->response_msg[i_count];
                    }

                    // C0 XOR opration except c_check_sum
                    uint8_t c0_header_value[MAX_CHARACTERISTIC_LIMIT];
                    memset(c0_header_value, 0, MAX_CHARACTERISTIC_LIMIT);
                    pt_cur_server_data->i_fragment_number++;
                    c0_header_value[0] = 0x00;
                    c0_header_value[1] = pt_cur_server_data->i_fragment_number;
                    int last_fragment_number = ui4_response_msg_len / MAX_FRAGMENT_LIMIT;
                    int remain_flags = ui4_response_msg_len % MAX_FRAGMENT_LIMIT;
                    if(0 != remain_flags)
                    {
                        last_fragment_number++;
                    }
                    c0_header_value[2] = (last_fragment_number -1) & 0xFF;
                    c0_header_value[4] = ui4_response_msg_len & 0xFF;
                    c0_header_value[5] = (ui4_response_msg_len >> 8) & 0xFF;

                    pt_cur_server_data->ui4_response_code = 200;
                    c0_header_value[6] = 0x00;
                    c0_header_value[7] = 0x00;

                    c0_header_value[8] = 0x00;//0x05;
                    for(i_count = 0; i_count < MAX_CHARACTERISTIC_LIMIT; i_count++)
                    {
                        c_check_sum ^= c0_header_value[i_count];
                    }
                    //c0_header_value[9] = c_check_sum;
                    c0_header_value[9] = 0x00;//c_check_sum - 1;

                    // copy paramters
                    send_conn_id = pt_cur_server_data->ble_char_result_array[0].conn_id;

                    // write msg header to c0
                    if (_bt_gattc_get_char_handle(pt_cur_server_data->ble_char_result_array[0].conn_id,
                                                  pt_cur_server_data->ble_char_result_array[0].char_id.uuid,
                                                  &h_char,
                                                  _BT_GATTC_GET_TYPE_CHAR) != BLUETOOTH_GATTC_OK
                       )
                    {
                        DBG_ERROR(("<BT_GATT> %d Cannot get character handle.\r\n",__LINE__));
                        break;
                    }

                    i_ret = a_mtkapi_bt_gattc_write_char(send_conn_id,
                                                      h_char,
                                                      i_write_type,
                                                      MAX_CHARACTERISTIC_LIMIT,
                                                      0,
                                                      (char*)c0_header_value);
                    BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);

                    BT_GATT_EXTI_FUNCTION();
                    return BLUETOOTH_GATTC_OK;
                }

                /*****************************************write msg payload to c1, c2, ...**********************************************/
                // copy t_data.pac_data msg to response_bytes
                if(pt_cur_server_data->ui4_response_msg_len > 0)
                {
                    DBG_INFO(("<BT_GATT>write msg payload to c1, c2, ...\n"));

                    // copy paramters
                    uint8_t i_write_char_number = pt_cur_server_data->i_write_char_number;
                    write_conn_id = pt_cur_server_data->ble_char_result_array[i_write_char_number].conn_id;
                    //write_char_inst_id = pt_cur_server_data->ble_char_result_array[i_write_char_number].char_id.inst_id;

                    memset(response_bytes, 0, MAX_CHARACTERISTIC_LIMIT + 1);

                    DBG_INFO(("<BT_GATT> server_data_array[%d].ui4_response_msg_len = %d\r\n",
                                i_write_scan_number,
                                pt_cur_server_data->ui4_response_msg_len));

                    h_char = pt_cur_server_data->aui4_char_result_handle[i_write_char_number];
                    DBG_INFO(("<BT_GATT> server_data_array[%d].h_char = %d, conn_id=%d\r\n",
                                                                    i_write_scan_number,
                                                                    h_char,
                                                                    pt_cur_server_data->ble_connect_result.conn_id));

                    if(pt_cur_server_data->ui4_response_msg_len < MAX_CHARACTERISTIC_LIMIT)
                    {
                        memcpy(response_bytes, pt_cur_server_data->response_msg + pt_cur_server_data->ui4_write_msg_len, pt_cur_server_data->ui4_response_msg_len);
                        response_bytes[MAX_CHARACTERISTIC_LIMIT] = '\0';

                        i_ret = a_mtkapi_bt_gattc_write_char(write_conn_id,
                                                          h_char,
                                                          i_write_type,
                                                          pt_cur_server_data->ui4_response_msg_len,
                                                          0,
                                                          response_bytes);

                        //i_ret = a_mtkapi_bt_gattc_write_char(write_conn_id, &write_service_uuid, write_service_inst_id, &write_char_uuid, write_char_inst_id, i_write_type, server_data_array[i_write_scan_number].ui4_response_msg_len, 0, response_bytes);
                        BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);

                        pt_cur_server_data->ui4_response_msg_len = 0;
                    }
                    else
                    {
                        memcpy(response_bytes, pt_cur_server_data->response_msg + pt_cur_server_data->ui4_write_msg_len, MAX_CHARACTERISTIC_LIMIT);
                        // call write char function
                        response_bytes[MAX_CHARACTERISTIC_LIMIT] = '\0';


                        i_ret = a_mtkapi_bt_gattc_write_char(write_conn_id,
                                                          h_char,
                                                          i_write_type,
                                                          MAX_CHARACTERISTIC_LIMIT,
                                                          0,
                                                          response_bytes);

                        //i_ret = a_mtkapi_bt_gattc_write_char(write_conn_id, &write_service_uuid, write_service_inst_id, &write_char_uuid, write_char_inst_id, i_write_type, MAX_CHARACTERISTIC_LIMIT, 0, response_bytes);
                        BT_GATT_CHECK_FAIL_RET(a_mtkapi_bt_gattc_write_char,i_ret);

                        pt_cur_server_data->ui4_response_msg_len -= MAX_CHARACTERISTIC_LIMIT;
                        pt_cur_server_data->ui4_write_msg_len += MAX_CHARACTERISTIC_LIMIT;
                    }
                }
            }
            break;
        case BT_GATT_GET_DB_CB:
        {
            UINT32 ui4_srv_data_idx = (UINT32)pt_bt_msg->ui4_data2;

            DBG_INFO(("<BT_GATT> BT_GATT_GET_DB_CB(ui4_db_service_idx=%d)\r\n", ui4_srv_data_idx));

            _bt_gattc_search_serivce(ui4_srv_data_idx);

            break;
        }
        case BT_GATT_REG_APP_CB:
        {
            BT_GATTC_REG_CLIENT_T* reg_result = (BT_GATTC_REG_CLIENT_T*)pt_bt_msg->ui4_data3;

            bt_gattc_app_client_if = reg_result->client_if;
            DBG_LOG_PRINT(("register app OK {id:0x%x,uuid:%s}\n",bt_gattc_app_client_if,reg_result->uuid));
        }
        default:
            {
                DBG_ERROR(("<BT_GATT> error: can't recognize the bluetooth gatt msgtype %d.\r\n", pt_bt_msg->ui4_msg_id));
                return BLUETOOTH_GATTC_FAILED;
            }
    }

    BT_GATT_EXTI_FUNCTION();
    return BLUETOOTH_GATTC_OK;
}
#endif

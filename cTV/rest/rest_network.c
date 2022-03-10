#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <cJSON.h>
#include <stdlib.h>
#include <unistd.h>

#include "c_dbg.h"
#include "u_common.h"
#include "c_dt.h"
#include "c_handle.h"
#include "u_cli.h"
#include "x_os.h"
#include "c_speedtest_async.h"

#include "amb/a_amb.h"
#include "am/a_am.h"
#include "menu2/a_menu.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "wizard_anim/a_wzd.h"

#include "rest_ipc.h"
#include "rest.h"
#include "a_rest_api.h"
#include "rest_ipc_handler.h"
#include "app_util/a_common.h"
#include "rest_cmd.h"
#include "rest_json.h"
#include "app_util/a_network.h"
#include "res/app_util/a_custom_log.h"
#include "res/app_util/network/network_custom.h"
#include "rest_network.h"
#include "rest_dbg_level.h"
#include "a_rest_event.h"
#include "rest_system.h"

#define VIZIO_SOFTAP_PRE_NAME       "VIZIOCastDisplay"
#define REST_TEST_CONNECTION_TIMER  (2*60*1000)  /* 2 min */
#define REST_SOFTAP_TIMER           (500)        /* 500ms */
#define REST_SOFTAP_TIMEOUT         (30*60*1000) /* 30min */
#define REST_CHECK_READY_TIMER      (1000)        /* 1 s */

pthread_mutex_t softap_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ssid_lock = PTHREAD_MUTEX_INITIALIZER;


REST_DATA_WIFI_APS_T t_g_ap_list = {0};
static NET_802_11_ESS_INFO_T at_ess_info[REST_TV_APS_NUM_MAX];
static UINT32 ui4_g_rest_nw_nfy_id = 0;
static CHAR s_access_point[REST_ACCESS_POINT_LEN+1] = {0};

static CHAR     s_net_pwd[REST_PASSWORD_LEN+1] = {0};

/* test connection  */
static HANDLE_T h_test_timer = NULL_HANDLE;
static HANDLE_T h_softap_timer = NULL_HANDLE;
static HANDLE_T h_rest_ready_timer = NULL_HANDLE;
static UINT8    ui1_g_rest_ready_count = 0;
static UINT32   ui4_g_rest_test_connection_nfy_id = 0;
static UINT32   ui4_g_rest_test_connection_tag = 0;
static BOOL     b_test_success = TRUE;
static UINT32   ui4_g_softap_start_time = 0;

REST_NW_CONN_TEST_STATUS e_g_nw_test_status = REST_NW_TEST_END;
REST_DATA_TEST_CONNECTION_T t_g_test_result = {0};
static BOOL     g_hidden_network = FALSE;

BOOL g_pin_google_success = FALSE;

typedef struct{
    UINT16  ui2_id;
    CHAR *  ps_error_string;
} _REST_NET_ERR_CODE_MAP;

/* audio mapping error ID to error string */
static _REST_NET_ERR_CODE_MAP at_error_id_mapping_string_table[] =
{
    {REST_NET_EMPTY,                    ""},
    {REST_NET_SUCCESS,                  "SUCCESS"},
    {REST_NET_WIFI_MISSING_PASSWORD,    "NET_WIFI_MISSING_PASSWORD"},
    {REST_NET_WIFI_NOT_EXISTED,         "NET_WIFI_NOT_EXISTED"},
    {REST_NET_WIFI_ALREADY_CONNECTED,   "NET_WIFI_ALREADY_CONNECTED"},
    {REST_NET_WIFI_NEEDS_VALID_SSID,    "NET_WIFI_NEEDS_VALID_SSID"},
    {REST_NET_WIFI_AUTH_REJECTED,       "NET_WIFI_AUTH_REJECTED"},
    {REST_NET_WIFI_CONNECT_TIMEOUT,     "NET_WIFI_CONNECT_TIMEOUT"},
    {REST_NET_WIFI_CONNECT_ABORTED,     "NET_WIFI_CONNECT_ABORTED"},
    {REST_NET_WIFI_CONNECTION_ERROR,    "NET_WIFI_CONNECTION_ERROR"},
    {REST_NET_IP_DHCP_FAILED,           "NET_IP_DHCP_FAILED"},
    {REST_NET_IP_MANUAL_CONFIG_ERROR,   "NET_IP_MANUAL_CONFIG_ERROR"},
    {REST_NET_UNKNOWN_ERROR,            "NET_UNKNOWN_ERROR"},
};

CHAR* ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPAEAP_OR_WPA2EAP+1];

static INT32 _rest_change_softap_channel_setting_with_current_bss(VOID);
static VOID _rest_softap_start_timer(VOID);
static VOID _rest_softap_stop_timer(VOID);

VOID _rest_wifi_associate_hidden_network(VOID);
VOID _rest_wifi_pre_associate_hidden_network(VOID);
static VOID _receive_associate_ok(VOID*      pv_data,
                                            SIZE_T     z_data_size);
VOID rest_stop_softap(VOID);
VOID rest_start_softap(VOID);
VOID rest_start_softap_ex(VOID);
extern  void update_test_connection_status();

static VOID _rest_network_init_ap_em_mapping_string_table()
{
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_NONE] =                 "NONE";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_OPEN] =                 "OPEN";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_SHARED] =               "SHARED";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WEPAUTO] =              "WEPAUTO";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA] =                  "WPA";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_PSK] =              "WPA/PSK";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_PSK_GTKIP] =        "WPA/GTKIP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_PSK_AES] =          "WPA/AES";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_PSK_AES_GTKIP] =    "WPA/AES-GTKIP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_PSK_TKIP] =         "WPA/TKIP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2] =                 "WPA2";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_PSK] =             "WPA2/PSK";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_PSK_GTKIP] =       "WPA2/GTKIP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_PSK_AES] =         "WPA2/AES";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_PSK_AES_GTKIP] =   "WPA2/AES-GTKIP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_PSK_TKIP] =        "WPA2/TKIP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_PSK_SHA256_AES] =  "WPA2/SHA256AES";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK] =    "WPA2PSK";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK_GTKIP] = "WPA2PSK-GTKIP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_PSK_TKIP_GWEP104] = "WPA/TKIP/GWEP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_PSK_GWEP104] =     "WPA2/GWEP";
    /* WPA3 AUTH MODE BEGIN*/
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_SAE] =              "WPA/SAE";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_SAE] =             "WPA2/SAE";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_OR_WPA2SAE] =       "WPA/WPA2SAE";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_OWE] =              "WPA/OWE";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_OWE] =             "WPA2/OWE";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE] =       "WPA/WPA2OWE";
    /* WPA3 AUTH MODE END*/
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA_EAP] =              "WPA/EAP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPA2_EAP] =             "WPA2/EAP";
    ps_ap_em_mapping_string_table[IEEE_802_11_AUTH_MODE_WPAEAP_OR_WPA2EAP] =    "WPAEAP/WPA2EAP";
}

INT32 rest_network_get_error_str_with_id(const UINT16 ui2_id, CHAR* ps_error_string)
{
    UINT16 ui2_i = 0;
    UINT16 ui2_total_num = sizeof(at_error_id_mapping_string_table)/sizeof(_REST_NET_ERR_CODE_MAP);

    if (!ps_error_string)
    {
        return RESTR_INV_ARG;
    }

    for (ui2_i = 0; ui2_i < ui2_total_num; ++ui2_i)
    {
        if (ui2_id == at_error_id_mapping_string_table[ui2_i].ui2_id)
        {
            strncpy(ps_error_string, at_error_id_mapping_string_table[ui2_i].ps_error_string, REST_ERROR_CODE);
            break;
        }
    }

    return RESTR_OK;
}

INT32 rest_network_update_error_code(REST_NET_ERR_CODE e_code)
{
    rest_network_get_error_str_with_id((UINT16)e_code, t_g_test_result.err_code);
    t_g_test_result.err_code[REST_ERROR_CODE-1]= '\0';
    DBG_ERROR(("[KK] current rest Error code: %s.\n\r", t_g_test_result.err_code));

    return RESTR_OK;
}

static VOID _rest_dump_ap_list(VOID)
{
    UINT8 ui1_idx = 0;

    DBG_INFO(("[KK] _rest_dump_ap_list: [ap_num]=%d, [connected]=%d.\n\r", t_g_ap_list.ap_num, t_g_ap_list.connected));

    for (ui1_idx = 0; ui1_idx < t_g_ap_list.ap_num; ui1_idx++)
    {
        DBG_INFO(("[KK] _rest_dump_ap_list: [%d], [NAME]=%s, [CH]=%d, [RSSI]=%d, [BAND]=%s, [EM]=%s, [BSSID]=%s.\n\r",
                   ui1_idx,
                   t_g_ap_list.aplist[ui1_idx].name,
                   t_g_ap_list.aplist[ui1_idx].i2_Channel,
                   t_g_ap_list.aplist[ui1_idx].rssi,
                   t_g_ap_list.aplist[ui1_idx].band,
                   t_g_ap_list.aplist[ui1_idx].em,
                   t_g_ap_list.aplist[ui1_idx].bssid));
    }

    DBG_INFO(("[KK] _rest_dump_ap_list End.\n\r"));
}

static BOOL _rest_is_valid_hex_string(CHAR* s_input, UINT8 ui1_length)
{
    BOOL b_valid = TRUE;
    UINT8 ui1_idx = 0;

    for(ui1_idx=0; ui1_idx<ui1_length; ui1_idx++)
    {
        if( (s_input[ui1_idx] >='0' &&  s_input[ui1_idx] <='9')
            || (s_input[ui1_idx] >='a' &&  s_input[ui1_idx] <='f')
            || (s_input[ui1_idx] >='A' &&  s_input[ui1_idx] <='F')
          )
        {
            continue;
        }

        b_valid = FALSE;
        break;
    }

    return b_valid;
}

static BOOL _rest_is_valid_wep_input_key(NET_802_11_AUTH_CIPHER_T    e_AuthCipher,
                             CHAR*                      s_input,
                             BOOL*                      pb_IsAscii)
{
    BOOL b_valid = TRUE;
    *pb_IsAscii = TRUE;

    UINT8 ui1_length = (UINT8)c_strlen(s_input);

    switch(e_AuthCipher)
    {
        case IEEE_802_11_AUTH_CIPHER_WEP40:
        {
            if(ui1_length == 5)
            {
                b_valid = TRUE;
                *pb_IsAscii = TRUE;
            }
            else if(ui1_length == 10)
            {
                *pb_IsAscii = FALSE;
                b_valid = _rest_is_valid_hex_string(s_input, ui1_length);
            }
            else
            {
                b_valid = FALSE;
            }

            break;
        }

        case IEEE_802_11_AUTH_CIPHER_WEP104:
        {
            if(ui1_length == 13)
            {
                b_valid = TRUE;
                *pb_IsAscii = TRUE;
            }
            else if(ui1_length == 26)
            {
                *pb_IsAscii = FALSE;
                b_valid = _rest_is_valid_hex_string(s_input, ui1_length);
            }
            else
            {
                b_valid = FALSE;
            }

            break;
        }

        default:
            break;
    }

    return b_valid;
}

static BOOL _rest_is_valid_input_key(NET_802_11_ASSOCIATE_T*    pt_associate,
                                      CHAR*                      s_input,
                                      BOOL*                      pb_IsAscii)
{
    BOOL b_valid = TRUE;

    *pb_IsAscii = TRUE;

    switch(pt_associate->e_AuthMode)
    {
        case IEEE_802_11_AUTH_MODE_NONE:
        case IEEE_802_11_AUTH_MODE_OPEN:
        case IEEE_802_11_AUTH_MODE_WPA_OWE:
        case IEEE_802_11_AUTH_MODE_WPA2_OWE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE:
            break;

        case IEEE_802_11_AUTH_MODE_SHARED:
        case IEEE_802_11_AUTH_MODE_WEPAUTO:
        {
            /*WEP authCipher maybe  IEEE_802_11_AUTH_CIPHER_WEP104 or IEEE_802_11_AUTH_CIPHER_WEP40 .*/
            b_valid = _rest_is_valid_wep_input_key(IEEE_802_11_AUTH_CIPHER_WEP40,
                                               s_input,
                                               pb_IsAscii);
            if(b_valid)
            {
                pt_associate->e_AuthCipher = IEEE_802_11_AUTH_CIPHER_WEP40;
            }
            else
            {

                b_valid = _rest_is_valid_wep_input_key(IEEE_802_11_AUTH_CIPHER_WEP104,
                                                   s_input,
                                                   pb_IsAscii);
                if(b_valid)
                {
                    pt_associate->e_AuthCipher = IEEE_802_11_AUTH_CIPHER_WEP104;
                }
            }

            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA:
        case IEEE_802_11_AUTH_MODE_WPA_PSK:
        case IEEE_802_11_AUTH_MODE_WPA2:
        case IEEE_802_11_AUTH_MODE_WPA2_PSK:
        case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
        {
            /*check wpa input key*/
            UINT8 ui1_length = (UINT8)c_strlen(s_input);

            if(ui1_length < 8 || ui1_length > 64)
            {
                b_valid = FALSE;
            }
            else if(ui1_length == 64)
            {
                *pb_IsAscii = FALSE;

                b_valid = _rest_is_valid_hex_string(s_input, ui1_length);
            }
            else
            {
                b_valid = TRUE;
                *pb_IsAscii = TRUE;
            }

            break;
        }

        default:
            break;
    }

    return b_valid;
}

static VOID _rest_test_ntp(VOID)
{
    struct      timeval tv;
    struct      timezone tz;
    DTG_T       t_loc_dtg;
    INT64       sec;

    c_memset(&t_loc_dtg, 0, sizeof(DTG_T));
    if (gettimeofday(&tv, &tz) == 0)
    {
        sec = (INT64)tv.tv_sec;
        c_dt_utc_sec_to_loc_dtg(sec, &t_loc_dtg);

        DBG_INFO(("[year,mon,day,hour,min] =[%d-%d-%d-%d-%d] \n ",
                 t_loc_dtg.ui2_yr,
                 t_loc_dtg.ui1_mo,
                 t_loc_dtg.ui1_day,
                 t_loc_dtg.ui1_hr,
                 t_loc_dtg.ui1_min));

        if (((t_loc_dtg.ui2_yr == 0) && (t_loc_dtg.ui1_mo == 0)) ||
            (t_loc_dtg.ui2_yr == 1970))
        {
            c_strncpy(t_g_test_result.ntp, "FALSE", REST_NTP_LEN);
            return;
        }
        c_strncpy(t_g_test_result.ntp, "TRUE", REST_NTP_LEN);
        return;
    }

    c_strncpy(t_g_test_result.ntp, "FALSE", REST_NTP_LEN);
    return;
}

static VOID _rest_test_interface(VOID)
{
    NET_802_11_BSS_INFO_T CurrBss;
    INT32 i4_ret = 0;

    if (a_nw_is_ethernet_plugin())
    {
        c_strncpy(t_g_test_result.conn_method, "Ethernet", REST_CONN_METHOD_LEN);
    }
    else
    {
        c_strncpy(t_g_test_result.conn_method, "WiFi", REST_CONN_METHOD_LEN);

        c_memset(&CurrBss, 0, sizeof(CurrBss));
        i4_ret = a_nw_wlan_get_curr_bss(&CurrBss);
        if(i4_ret != NWR_OK)
        {
            CurrBss.t_Ssid.ui4_SsidLen = 0;
        }
        else
        {
            c_strncpy(t_g_test_result.ssid, CurrBss.t_Ssid.ui1_aSsid, REST_SSID_MAX_LEN);
            t_g_test_result.ssid[REST_SSID_MAX_LEN] = 0;
        }
    }
}

static VOID _rest_test_dns(VOID)
{
    c_strncpy(t_g_test_result.dns, "TRUE", REST_DNS_LEN);
}

static VOID _rest_test_speed(VOID)
{
    t_g_test_result.conn_speed = 50.0;
}

static VOID _rest_authmode2str(NET_802_11_AUTH_MODE_T e_AuthMode, CHAR* ps_auth)
{
    if (NULL == ps_auth)
    {
        return;
    }

    if (e_AuthMode > IEEE_802_11_AUTH_MODE_WPAEAP_OR_WPA2EAP)
    {
        return;
    }

    c_strncpy(ps_auth, ps_ap_em_mapping_string_table[e_AuthMode], REST_DATA_EM_LEN);
    ps_auth[REST_DATA_EM_LEN-1] = '\0';

    return;
}

/* filter out SSID with "VIZIOCastDisplay" */
static BOOL _wzd_nw_is_filter_out_ssid(const CHAR* pssid)
{
    /* do not enable yet */
    if (1)
    {
        return FALSE;
    }

    if (pssid == NULL)
    {
        return FALSE;
    }

    if (c_strlen(pssid) < c_strlen(VIZIO_SOFTAP_PRE_NAME))
    {
        return FALSE;
    }

    if (0 == c_strncmp(pssid, VIZIO_SOFTAP_PRE_NAME, c_strlen(VIZIO_SOFTAP_PRE_NAME)))
    {
        DBG_INFO( ("[WZD][NW] --- filter out VIZIOCastDisplay. FUNC: %s LINE: %d\n",
                    __FUNCTION__, __LINE__));
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static BOOL _rest_is_lock_ap(NET_802_11_AUTH_MODE_T e_AuthMode,
                             NET_802_11_AUTH_CIPHER_T e_AuthCipher)
{
  if ((e_AuthMode== IEEE_802_11_AUTH_MODE_NONE ||
       e_AuthMode == IEEE_802_11_AUTH_MODE_OPEN) &&
      e_AuthCipher == IEEE_802_11_AUTH_CIPHER_NONE)
  {
    return FALSE;
  }
  else if (e_AuthMode == IEEE_802_11_AUTH_MODE_WPA_OWE ||
           e_AuthMode == IEEE_802_11_AUTH_MODE_WPA2_OWE ||
           e_AuthMode == IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE)
  {
    return FALSE;
  }

  return TRUE;
}

static VOID _rest_update_ap_list(VOID)
{
    INT32                       i4_ret = 0;
    NET_802_11_ESS_LIST_T       t_essList_tmp;
    NET_802_11_ESS_INFO_T*      p_essInfo = NULL;
    NET_802_11_ESS_INFO_T       t_essInfo_tmp;
    NET_802_11_BSS_INFO_T       t_CurrBss;
    NET_802_11_BSS_INFO_T*      p_bssInfo = NULL;
    NET_802_11_SCAN_RESULT_T    t_scan_result;
    UINT8                       ui1_idx = 0;
    UINT8                       ui1_idx_2 = 0;
    UINT32                      ui4_idx = 0;
    CHAR                        s_authmode_temp[REST_DATA_EM_LEN+1] = {0};

    pthread_mutex_lock(&ssid_lock);

    /* clear old list */
    c_memset(&t_g_ap_list, 0, sizeof(t_g_ap_list));
    c_memset(&at_ess_info, 0, sizeof(at_ess_info));

    c_memset (&t_essList_tmp, 0, sizeof(t_essList_tmp));
    i4_ret = a_nw_wlan_get_ess_list(&t_essList_tmp);
    REST_LOG_ON_FAIL(i4_ret);

    c_memset (&t_scan_result, 0, sizeof(t_scan_result));
    i4_ret = a_nw_wlan_get_scan_result(&t_scan_result);
    REST_LOG_ON_FAIL(i4_ret);

    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    if(i4_ret != NWR_OK)
    {
        DBG_ERROR(("\n%s,%d\n", __FUNCTION__, __LINE__));
        c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
    }

    if(t_essList_tmp.ui4_NumberOfItems == 0)
    {
        DBG_INFO(("\n%s,%d,NO AP LIST\n", __FUNCTION__, __LINE__));
        pthread_mutex_unlock(&ssid_lock);
        return;
    }

    if(t_scan_result.ui4_NumberOfItems == 0)
    {
        DBG_INFO(("\n%s,%d,NO AP LIST\n", __FUNCTION__, __LINE__));
        pthread_mutex_unlock(&ssid_lock);
        return;
    }

    if ((t_CurrBss.t_Ssid.ui4_SsidLen > 0)
        &&((UINT8)WLAN_WPA_COMPLETED == t_CurrBss.u8_wpa_status))
    {
        t_g_ap_list.connected = TRUE;
    }
    else
    {
        t_g_ap_list.connected = FALSE;
    }


    /* sort wlan ap list */
    do
    {
        if (FALSE == t_g_ap_list.connected)
        {
            break;
        }

        if (t_essList_tmp.p_EssInfo[0].t_Ssid.ui4_SsidLen == t_CurrBss.t_Ssid.ui4_SsidLen &&
            0 == c_strncmp(t_essList_tmp.p_EssInfo[0].t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen))
        {
            break;
        }

        for (ui1_idx = 1; ui1_idx < (UINT8)t_essList_tmp.ui4_NumberOfItems; ui1_idx ++)
        {
            if (t_essList_tmp.p_EssInfo[ui1_idx].t_Ssid.ui4_SsidLen == t_CurrBss.t_Ssid.ui4_SsidLen &&
                0 == c_strncmp(t_essList_tmp.p_EssInfo[ui1_idx].t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen))
            {
                /* use bubble algorithm to sort. */
                for (ui1_idx_2 = ui1_idx; ui1_idx_2 > 0; ui1_idx_2--)
                {
                    c_memcpy(&t_essInfo_tmp,
                             &(t_essList_tmp.p_EssInfo[ui1_idx_2]),
                             sizeof(NET_802_11_ESS_INFO_T));

                    c_memcpy(&(t_essList_tmp.p_EssInfo[ui1_idx_2]),
                             &(t_essList_tmp.p_EssInfo[ui1_idx_2-1]),
                             sizeof(NET_802_11_ESS_INFO_T));

                    c_memcpy(&(t_essList_tmp.p_EssInfo[ui1_idx_2-1]),
                             &t_essInfo_tmp,
                             sizeof(NET_802_11_ESS_INFO_T));
                }

                break;
            }
        }

        /* TODO: do NOT Find in the essList */
        if (ui1_idx == (UINT8)t_essList_tmp.ui4_NumberOfItems)
        {
            DBG_INFO(("[KK] %s, LINE: %d, ui1_idx: %u\n", __FUNCTION__, __LINE__, ui1_idx));
        }
    }while(0);

    ui1_idx = 0;
    t_g_ap_list.ap_num = 0;

    while (t_g_ap_list.ap_num < REST_TV_APS_NUM_MAX &&
           ui1_idx < t_essList_tmp.ui4_NumberOfItems)
    {
        p_essInfo = &(t_essList_tmp.p_EssInfo[ui1_idx]);
        if (NULL == p_essInfo)
        {
            ui1_idx++;
            continue;
        }

        if (_wzd_nw_is_filter_out_ssid(p_essInfo->t_Ssid.ui1_aSsid))
        {
            ui1_idx++;
            continue;
        }

        if (c_strlen(p_essInfo->t_Ssid.ui1_aSsid) != 0 &&
            p_essInfo->t_Ssid.ui4_SsidLen > 0)
        {
            /* store ESS info */
            at_ess_info[t_g_ap_list.ap_num].e_AuthMode = p_essInfo->e_AuthMode;
            at_ess_info[t_g_ap_list.ap_num].e_AuthCipher = p_essInfo->e_AuthCipher;
            c_memcpy(at_ess_info[t_g_ap_list.ap_num].t_Bssid,
                     p_essInfo->t_Bssid, sizeof(NET_802_11_BSSID_T));
            c_strncpy(at_ess_info[t_g_ap_list.ap_num].t_Ssid.ui1_aSsid,
                      p_essInfo->t_Ssid.ui1_aSsid, REST_SSID_MAX_LEN);
            at_ess_info[t_g_ap_list.ap_num].t_Ssid.ui4_SsidLen = p_essInfo->t_Ssid.ui4_SsidLen;


            /* update SSID info */
            c_strncpy(t_g_ap_list.aplist[t_g_ap_list.ap_num].name,
                       p_essInfo->t_Ssid.ui1_aSsid, REST_SSID_MAX_LEN);

            /* update bSSID info */
            c_sprintf ( t_g_ap_list.aplist[t_g_ap_list.ap_num].bssid,
                        "%02X:%02X:%02X:%02X:%02X:%02X\0",
                        p_essInfo->t_Bssid[0],
                        p_essInfo->t_Bssid[1],
                        p_essInfo->t_Bssid[2],
                        p_essInfo->t_Bssid[3],
                        p_essInfo->t_Bssid[4],
                        p_essInfo->t_Bssid[5]);

            /* update authmode info */
            c_memset(s_authmode_temp, 0, sizeof(s_authmode_temp));
            _rest_authmode2str(p_essInfo->e_AuthMode, s_authmode_temp);
            c_strncpy(t_g_ap_list.aplist[t_g_ap_list.ap_num].em, s_authmode_temp, REST_DATA_EM_LEN-1);
            t_g_ap_list.aplist[t_g_ap_list.ap_num].passwordReq = _rest_is_lock_ap(p_essInfo->e_AuthMode, p_essInfo->e_AuthCipher);

            /* update RSSI info and channel info from BSS */
            t_g_ap_list.aplist[t_g_ap_list.ap_num].i2_Channel = -1000;
            t_g_ap_list.aplist[t_g_ap_list.ap_num].rssi = 0;
            for (ui4_idx = 0; ui4_idx < t_scan_result.ui4_NumberOfItems; ui4_idx++)
            {
                p_bssInfo = &(t_scan_result.p_BssInfo[ui4_idx]);
                if (NULL == p_bssInfo)
                {
                    continue;
                }

                if ((p_essInfo->t_Ssid.ui4_SsidLen == p_bssInfo->t_Ssid.ui4_SsidLen) &&
                    (0 == c_strncmp(p_essInfo->t_Ssid.ui1_aSsid, p_bssInfo->t_Ssid.ui1_aSsid, p_bssInfo->t_Ssid.ui4_SsidLen)))
                {
                    t_g_ap_list.aplist[t_g_ap_list.ap_num].rssi = p_bssInfo->i2_Level_dB;
                    t_g_ap_list.aplist[t_g_ap_list.ap_num].i2_Channel = p_bssInfo->i2_Channel;
                    break;
                }
            }

            /* update band info */
            if ((-1000 == t_g_ap_list.aplist[t_g_ap_list.ap_num].i2_Channel) ||
                (t_g_ap_list.aplist[t_g_ap_list.ap_num].i2_Channel > 0 && t_g_ap_list.aplist[t_g_ap_list.ap_num].i2_Channel < 15))
            {
                c_strncpy(t_g_ap_list.aplist[t_g_ap_list.ap_num].band, "2.4GHz", REST_DATA_BAND_LEN);
            }
            else
            {
                c_strncpy(t_g_ap_list.aplist[t_g_ap_list.ap_num].band, "5GHz", REST_DATA_BAND_LEN);
            }

            t_g_ap_list.ap_num++;
        }
        ui1_idx++;
    }

    pthread_mutex_unlock(&ssid_lock);

    if (0)
    {
        _rest_dump_ap_list();
    }

    return;
}
static VOID _recieve_wlan_scan(VOID*      pv_data,
                                    SIZE_T     z_data_size)
{
    _rest_update_ap_list();
    if(g_hidden_network == TRUE)
    {
        _rest_wifi_associate_hidden_network();
    }
    return;
}

static VOID _rest_update_ap_list_with_local_buff(VOID)
{
    INT32                       i4_ret = 0;
    NET_802_11_BSS_INFO_T       t_CurrBss;
    UINT8                       ui1_idx = 0;
    UINT8                       ui1_idx_2 = 0;
    REST_DATA_WIFI_AP_T         t_aplist;

    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    if(i4_ret != NWR_OK)
    {
        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
    }

    if ((t_CurrBss.t_Ssid.ui4_SsidLen > 0)
        &&((UINT8)WLAN_WPA_COMPLETED == t_CurrBss.u8_wpa_status))
    {
        t_g_ap_list.connected = TRUE;
    }
    else
    {
        t_g_ap_list.connected = FALSE;
    }

    if (FALSE == t_g_ap_list.connected || t_g_ap_list.ap_num == 0)
    {
        return;
    }

    /* sort wlan ap list */
    do
    {
        if (c_strlen(t_g_ap_list.aplist[0].name) == t_CurrBss.t_Ssid.ui4_SsidLen &&
            0 == c_strncmp(t_g_ap_list.aplist[0].name, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen))
        {
            break;
        }

        for (ui1_idx = 1; ui1_idx < (UINT8)t_g_ap_list.ap_num; ui1_idx ++)
        {
            if (c_strlen(t_g_ap_list.aplist[ui1_idx].name) == t_CurrBss.t_Ssid.ui4_SsidLen &&
                0 == c_strncmp(t_g_ap_list.aplist[ui1_idx].name, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen))
            {
                /* use bubble algorithm to sort. */
                for (ui1_idx_2 = ui1_idx; ui1_idx_2 > 0; ui1_idx_2--)
                {
                    c_memcpy(&t_aplist,
                             &(t_g_ap_list.aplist[ui1_idx_2]),
                             sizeof(REST_DATA_WIFI_AP_T));

                    c_memcpy(&(t_g_ap_list.aplist[ui1_idx_2]),
                             &(t_g_ap_list.aplist[ui1_idx_2-1]),
                             sizeof(REST_DATA_WIFI_AP_T));

                    c_memcpy(&(t_g_ap_list.aplist[ui1_idx_2-1]),
                             &t_aplist,
                             sizeof(REST_DATA_WIFI_AP_T));
                }

                break;
            }
        }

        /* TODO: do NOT Find in the AP List */
        if (ui1_idx == (UINT8)t_g_ap_list.ap_num)
        {
            DBG_INFO(("[KK] %s, LINE: %d, ui1_idx: %u\n", __FUNCTION__, __LINE__, ui1_idx));
        }
    }while(0);


    if (1)
    {
        _rest_dump_ap_list();
    }

    return;
}

static VOID _rest_softap_timer_nfy_handler(
                                    VOID*      pv_data,
                                    SIZE_T     z_data_size
                                    )
{
    //DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;

    UINT32  ui4_curr_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
    UINT32  ui4_period_time = ui4_curr_time - ui4_g_softap_start_time;

    REST_LOG_ON_FAIL(a_cfg_get_wzd_status(&ui2_status));

    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

    //DBG_API(("%s, oobe [state= %d]\n\r", __FUNCTION__, (int)ui1_state));

    if (WZD_STATE_RESUME_C4TV == ui1_state)
    {
        // Enter OOBE, stop timer, using OOBE to start/stop softap.
        _rest_softap_stop_timer();
        return;
    }
    else if (ui4_period_time > REST_SOFTAP_TIMEOUT)
    {
        // Timeout, stop timer & softap.
        _rest_softap_stop_timer();
        rest_stop_softap();
        return;
    }
    else
    {
        // Keep softap alive for 30min after power on.
        rest_start_softap_ex();
    }

}

static VOID _rest_softap_timer_nfy(HANDLE_T h_timer, VOID*    pv_tag)
{
    //DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    rest_async_invoke(_rest_softap_timer_nfy_handler, NULL, 0, TRUE);

    return;
}

static VOID _rest_softap_start_timer(VOID)
{
    INT32 i4_ret;

    DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    ui4_g_softap_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

    i4_ret = c_timer_start(
                    h_softap_timer,
                    REST_SOFTAP_TIMER,
                    X_TIMER_FLAG_REPEAT,
                    _rest_softap_timer_nfy,
                    NULL);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR(("%s, %d, c_timer_start failed!\n", __FUNCTION__, __LINE__));
    }

    return;
}

static VOID _rest_softap_stop_timer(VOID)
{
    INT32 i4_ret;

    DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    if (c_handle_valid(h_softap_timer) == FALSE)
    {
        return;
    }

    i4_ret = c_timer_stop(h_softap_timer);
    if (i4_ret != OSR_OK)
    {
        DBG_ERROR(("%s, %d, c_timer_stop failed!\n", __FUNCTION__, __LINE__));
    }
}

VOID rest_softap_power_on(VOID)
{
    // Start softap for 30min.

    DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    _rest_softap_stop_timer();
    _rest_softap_start_timer();

    return;
}
#if 0
VOID rest_nw_launch_sc_home(VOID)
{
    DBG_LOG_PRINT(("call rest_nw_launch_sc_home\n\r"));
    DBG_LOG_PRINT(("a_am_is_power_on()=%d\n\r", a_am_is_power_on()));
    DBG_LOG_PRINT(("a_am_is_suspnd_mode()=%d\n\r", a_am_is_suspnd_mode()));
    DBG_LOG_PRINT(("a_am_get_suspend_status()=%d\n\r", a_am_get_suspend_status()));
    // a_am_is_power_on()=0 a_am_is_suspnd_mode()=0 a_am_get_suspend_status()=1
    if (a_am_is_power_on() == FALSE && a_am_is_suspnd_mode() == FALSE) {
        DBG_LOG_PRINT(("Needless to launch SC Home\n\r"));
        return;
    }

    // TODO: check network connection
    // if (still can access internet) return;

    // TODO: can call a_rest_launch_sc_home() only if network has ever connected in every power cycle

    //DBG_LOG_PRINT(("call a_rest_launch_sc_home\n\r"));
    //a_rest_launch_sc_home();
}
#endif

VOID rest_nw_set_is_hidden_notwork(BOOL is_hidden)
{
    DBG_INFO(("[%s %d] is_hidden: %d\r\n", __FUNCTION__, __LINE__, is_hidden));
    g_hidden_network = is_hidden;
}

static VOID _rest_nw_notify_callback(VOID* pv_tag,
                                     NW_NFY_ID_T e_nfy_id,
                                     VOID* pv_nfy_param)
{
    CHAR s_resume_ap[APP_NAME_MAX_LEN+1] = {0};
    INT32 i4_ret = RESTR_OK;

    i4_ret = a_am_get_active_app(s_resume_ap);
    if(i4_ret != AEER_OK)
    {
        DBG_ERROR(("\n%s,get active app failed\n", __FUNCTION__));
        return;
    }

    /* only support one NW client */
    if(strcmp(s_resume_ap, MENU_NAME) == 0)
    {
        DBG_INFO(("\n%s,s_resume_ap=%s\n", __FUNCTION__, s_resume_ap));
        return;
    }

    switch (e_nfy_id)
    {
        case NW_NFY_ID_ETHERNET_PLUGIN:
        {
            DBG_INFO(("\n%s,%d,NW_NFY_ID_ETHERNET_PLUGIN\n", __FUNCTION__, __LINE__));
            if ( WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)pv_nfy_param)
            {
                c_strncpy(t_g_test_result.conn_method, "Ethernet", REST_CONN_METHOD_LEN);
            }

            break;
        }
        case NW_NFY_ID_ETHERNET_UNPLUG:
        {
            DBG_INFO(("\n%s,%d,NW_NFY_ID_ETHERNET_UNPLUG\n", __FUNCTION__, __LINE__));
            if ( WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)pv_nfy_param)
            {
                c_strncpy(t_g_test_result.conn_method, "WiFi", REST_CONN_METHOD_LEN);
            }

            //rest_nw_launch_sc_home();

            break;
        }
        case NW_NFY_ID_DHCP_FAILURE_LINKLOCAL:
        {
            DBG_INFO(("\n%s,%d,NW_NFY_ID_DHCP_FAILURE_LINKLOCAL\n", __FUNCTION__, __LINE__));
            if(FALSE == t_g_test_result.reconnecting)
            {
                rest_network_update_error_code(REST_NET_IP_DHCP_FAILED);
            }
            break;
        }
    #ifdef APP_NETWORK_WIFI_SUPPORT
        case NW_NFY_ID_WLAN_SCAN:
        {
            DBG_INFO(("\n%s,%d,NW_NFY_ID_WLAN_SCAN\n", __FUNCTION__, __LINE__));
            if ( WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)pv_nfy_param)
            {
                rest_async_invoke(_recieve_wlan_scan,NULL,0,TRUE);
            }
            break;
        }

        case NW_NFY_ID_WLAN_ASSOCIATE:
        case NW_NFY_ID_WLAN_WPS_ASSOCIATE:
        {
            if ((WLAN_NOTIFY_MSG_T)(UINT32)(pv_nfy_param) == WLAN_NFY_MSG_OK)
            {
                DBG_INFO(("\n%s,%d,NW_NFY_ID_WLAN_ASSOCIATE success\n",
                                __FUNCTION__, __LINE__));

                // notify app.cpp to launch
                //a_rest_launch_partner_key_app();
                //rest_network_update_error_code(REST_NET_SUCCESS);

                /* TODO: (steven) need update softAP channel */
                //_rest_change_softap_channel_setting_with_current_bss();
                rest_async_invoke(_receive_associate_ok,NULL,0,TRUE);
            }
            else if ((WLAN_NOTIFY_MSG_T)(UINT32)(pv_nfy_param) == WLAN_NFY_MSG_PSK_INCORRECT)
            {
                DBG_INFO(("\n%s,%d,NW_NFY_ID_WLAN_ASSOCIATE WLAN_NFY_MSG_NO_MATCHED_CONFIG\n",
                                __FUNCTION__, __LINE__));
                if(FALSE == t_g_test_result.reconnecting)
                {
                    rest_network_update_error_code(REST_NET_WIFI_AUTH_REJECTED);
                }
                rest_nw_set_is_hidden_notwork(FALSE);
            }
            else if ((WLAN_NOTIFY_MSG_T)(UINT32)(pv_nfy_param) == WLAN_NFY_MSG_DISCONNECTED)
            {
                DBG_INFO(("\n%s,%d,NW_NFY_ID_WLAN_ASSOCIATE WLAN_NFY_MSG_DISCONNECTED\n",
                                __FUNCTION__, __LINE__));
                //DBG_LOG_PRINT(("\n%s,%d, Launch SC Home\n", __FUNCTION__, __LINE__));

                UINT16  ui2_status    = 0;
                UINT8   ui1_state     = 0;
                UINT8   ui1_page_idx  = 0;

                a_cfg_get_wzd_status(&ui2_status);
                ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
                ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);
                DBG_INFO(("a_cfg_get_wzd_status [state= %d] [page= %d]\n\r", (int)ui1_state, (int)ui1_page_idx));

                /*if ((WZD_PAGE_INDEX_C4TV_ALL_SET == ui1_page_idx) || (WZD_PAGE_INDEX_C4TV_END == ui1_page_idx)) {
                    rest_nw_launch_sc_home();
                }*/
            }
            else if ((WLAN_NOTIFY_MSG_T)(UINT32)(pv_nfy_param) == WLAN_NFY_MSG_AUTH_TIMEOUT ||
                     (WLAN_NOTIFY_MSG_T)(UINT32)(pv_nfy_param) == WLAN_NFY_MSG_ASSOC_TIMEOUT)
            {
                DBG_INFO(("\n%s,%d,NW_NFY_ID_WLAN_ASSOCIATE WLAN_NFY_MSG_AUTH_TIMEOUT\n",
                                __FUNCTION__, __LINE__));
                if(FALSE == t_g_test_result.reconnecting)
                {
                    rest_network_update_error_code(REST_NET_WIFI_CONNECT_TIMEOUT);
                }
                rest_nw_set_is_hidden_notwork(FALSE);
            }
            else
            {
                DBG_INFO(("\n%s,%d,NW_NFY_ID_WLAN_ASSOCIATE ERROR: %u\n",
                                __FUNCTION__, __LINE__, (UINT32)(pv_nfy_param)));
                if(FALSE == t_g_test_result.reconnecting)
                {
                    rest_network_update_error_code(REST_NET_WIFI_CONNECTION_ERROR);
                }
                rest_nw_set_is_hidden_notwork(FALSE);
            }

            break;
        }
        case NW_NFY_ID_WLAN_START_IND:
        {
            break;
        }
    #endif

        default:
            break;
    }
}
#if 0
static VOID _rest_nw_notify_callback(VOID* pv_tag,
                                     NW_NFY_ID_T e_nfy_id,
                                     VOID* pv_nfy_param)
{
    REST_NW_NFY_DATA_T t_nw_nfy_data;
    CHAR s_resume_ap[APP_NAME_MAX_LEN+1] = {0};
    INT32 i4_ret = RESTR_OK;

    i4_ret = a_am_get_active_app(s_resume_ap);
    if(i4_ret != AEER_OK)
    {
        DBG_ERROR(("\n%s,get active app failed\n", __FUNCTION__));
        return;
    }

    /* only support one NW client */
    if(strcmp(s_resume_ap, MENU_NAME) == 0)
    {
        DBG_INFO(("\n%s,s_resume_ap=%s\n", __FUNCTION__, s_resume_ap));
        return;
    }

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    rest_async_invoke(_rest_nw_notify_handler,
                      &t_nw_nfy_data,sizeof(REST_NW_NFY_DATA_T),TRUE);
}
#endif
INT32 rest_network_register_notify(VOID)
{
    INT32 i4_ret = RESTR_OK;

    c_memset(&t_g_test_result, 0, sizeof(t_g_test_result));

    _rest_network_init_ap_em_mapping_string_table();

    i4_ret = c_timer_create(&h_softap_timer);
    if (i4_ret != OSR_OK) {
        return RESTR_FAIL;
    }

    i4_ret = a_nw_register(_rest_nw_notify_callback,
                           NULL,
                           &ui4_g_rest_nw_nfy_id);
    REST_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 rest_network_unregister_notify(VOID)
{
    INT32 i4_ret = RESTR_OK;

    if (c_handle_valid(h_softap_timer) == TRUE)
    {
        c_timer_delete(h_softap_timer);
        h_softap_timer = NULL_HANDLE;
    }

    if (ui4_g_rest_nw_nfy_id > 0)
    {
        i4_ret = a_nw_unregister(ui4_g_rest_nw_nfy_id);
        REST_LOG_ON_FAIL(i4_ret);

        ui4_g_rest_nw_nfy_id = 0;
    }

    return i4_ret;
}

static INT32 _rest_get_ip_address(CHAR *ps_ip_address, UINT32 ui4_address)
{
    INT32 i4_ret = 0;
    UINT8 ui1_col = 0;
    CHAR  char_data[5] = {0};



    for(ui1_col= 0; ui1_col < 4; ui1_col++)
    {
        c_memset(char_data, 0, sizeof(char_data));
        c_sprintf(char_data,("%d\0"), (ui4_address>>(8*ui1_col))&0xFF);
        c_strncat(ps_ip_address, char_data, c_strlen(char_data));
        if (ui1_col < 3)
        {
            c_strncat(ps_ip_address, ".", sizeof(CHAR));
        }
    }

    return i4_ret;
}

static INT32 _rest_get_curr_access_point(REST_DATA_WIFI_AP_T *pt_ap)
{
    INT32 i4_ret = RESTR_OK;
    NET_802_11_BSS_INFO_T t_CurrBss;

    if (pt_ap == NULL)
    {
        DBG_LOG_PRINT(("%s, %d ERROR!", __FUNCTION__, __LINE__));
        return RESTR_INV_ARG;
    }

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);

    DBG_LOG_PRINT(("\n[NW][Rest] [%s, %d] t_CurrBss.t_Ssid.ui1_aSsid = %s, t_CurrBss.t_Ssid.ui4_SsidLen = %d i4_ret = %d\n",
        __FUNCTION__, __LINE__, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen, i4_ret));

    REST_LOG_ON_FAIL(i4_ret);
    if (i4_ret != NWR_OK || t_CurrBss.t_Ssid.ui4_SsidLen == 0)
    {
        DBG_ERROR(("\n%s,%d a_nw_wlan_get_curr_bss failed.\n", __FUNCTION__, __LINE__));
        c_strcpy(pt_ap->name, REST_STR_NOT_AVAILABLE);
        return RESTR_FAIL;
    }

    if (t_CurrBss.i2_Level == 0)
    {
        t_CurrBss.i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();
    }

    pt_ap->rssi = t_CurrBss.i2_Level;
    c_sprintf ( pt_ap->bssid,
                "%02X:%02X:%02X:%02X:%02X:%02X\0",
                t_CurrBss.t_Bssid[0],
                t_CurrBss.t_Bssid[1],
                t_CurrBss.t_Bssid[2],
                t_CurrBss.t_Bssid[3],
                t_CurrBss.t_Bssid[4],
                t_CurrBss.t_Bssid[5]);
    c_strncpy(pt_ap->name, t_CurrBss.t_Ssid.ui1_aSsid, REST_SSID_MAX_LEN);

    if (t_CurrBss.i2_Channel > 0 && t_CurrBss.i2_Channel < 15)
    {
        c_strncpy(pt_ap->band, "2.4GHz", REST_DATA_BAND_LEN);
    }
    else
    {
        c_strncpy(pt_ap->band, "5GHz", REST_DATA_BAND_LEN);
    }
    _rest_authmode2str(t_CurrBss.e_AuthMode, pt_ap->em);

    return RESTR_OK;
}

static INT32 _rest_set_wifi_ssid(CHAR *ps_ssid)
{
    c_strncpy(s_access_point, ps_ssid, REST_SSID_MAX_LEN);
    DBG_INFO(("s_access_point:%s", s_access_point));
    return RESTR_OK;
}

static INT32 _rest_get_wifi_ssid(CHAR *ps_ssid)
{
    if (!ps_ssid)
    {
        return RESTR_INV_ARG;
    }

    c_strncpy(ps_ssid, s_access_point, REST_SSID_MAX_LEN);
    DBG_INFO(("s_access_point:%s", ps_ssid));

    return RESTR_OK;
}

static INT32 _rest_wifi_pre_associate(CHAR *ps_password, NET_802_11_ASSOCIATE_T* pt_associate)
{
    UINT8 ui1_idx = 0;
    BOOL  b_valid = FALSE;
    BOOL  b_IsAscii = FALSE;
    NET_802_11_ESS_LIST_T t_essList;
    INT32       i4_ret;

    NET_802_11_ESS_INFO_T* p_essInfo = NULL;

    if (0 == c_strlen(s_access_point))
    {
        DBG_ERROR(("\n%s,%d,ssid is empty!!!\n", __FUNCTION__, __LINE__));
        return RESTR_FAIL;
    }

    c_memset(&t_essList, 0, sizeof(t_essList));

    i4_ret = a_nw_wlan_get_ess_list(&t_essList);

    DBG_LOG_PRINT(("\n%s,%d,Hidden network,ap name =%s, ui4_NumberOfItems =%d!!!\n", __FUNCTION__, __LINE__,s_access_point,t_essList.ui4_NumberOfItems));

    for (ui1_idx = 0;ui1_idx<(UINT8)t_essList.ui4_NumberOfItems; ui1_idx ++)
    {
        p_essInfo = &t_essList.p_EssInfo[ui1_idx];

        if(p_essInfo->t_Ssid.ui4_SsidLen == 0)
        {
            continue;
        }
        if(c_strncmp(p_essInfo->t_Ssid.ui1_aSsid, s_access_point,NET_802_11_MAX_LEN_SSID ) != 0)
        {
            continue;
        }

        pt_associate->t_Ssid      = p_essInfo->t_Ssid;
        c_memcpy(pt_associate->t_Bssid,p_essInfo->t_Bssid, sizeof(NET_802_11_BSSID_T));

        pt_associate->e_AuthMode  = p_essInfo->e_AuthMode;
        pt_associate->e_AuthCipher= p_essInfo->e_AuthCipher;

        break;
    }
    DBG_LOG_PRINT(("\n%s,%d,Hidden network,ui1_idx=%d!!!\n", __FUNCTION__, __LINE__,ui1_idx));

    /* hidden ap */
    if (ui1_idx >= t_essList.ui4_NumberOfItems)
    {
        DBG_INFO(("\n%s,%d,Hidden network!!!\n", __FUNCTION__, __LINE__));

        c_strncpy(pt_associate->t_Ssid.ui1_aSsid, s_access_point, REST_SSID_MAX_LEN);
        pt_associate->t_Ssid.ui4_SsidLen = c_strlen(pt_associate->t_Ssid.ui1_aSsid);

        pt_associate->t_Bssid[0]=0xFF;
        pt_associate->t_Bssid[1]=0xFF;
        pt_associate->t_Bssid[2]=0xFF;
        pt_associate->t_Bssid[3]=0xFF;
        pt_associate->t_Bssid[4]=0xFF;
        pt_associate->t_Bssid[5]=0xFF;

        /* hard code */
        pt_associate->e_AssocCase     = IEEE_802_11_MANUAL_ASSOC;
        pt_associate->ui1_Priority    = 0;
        if (c_strlen(ps_password) > 0)
        {
            pt_associate->e_AuthMode      = IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK;
            pt_associate->e_AuthCipher    = IEEE_802_11_AUTH_CIPHER_AES_OR_TKIP;
        }
        else
        {
            pt_associate->e_AuthMode      = IEEE_802_11_AUTH_MODE_NONE;
            pt_associate->e_AuthCipher    = IEEE_802_11_AUTH_CIPHER_NONE;
        }
    }

    DBG_INFO(("\n%s,%d,ui1_aSsid=%s,e_AuthMode=%d,e_AuthCipher=%d\n",
                            __FUNCTION__, __LINE__, pt_associate->t_Ssid.ui1_aSsid,
                            pt_associate->e_AuthMode,pt_associate->e_AuthCipher));

    b_valid = _rest_is_valid_input_key(pt_associate, ps_password, &b_IsAscii);
    if (b_valid)
    {
        pt_associate->t_Key.pui1_PassPhrase = ps_password;
        pt_associate->t_Key.b_IsAscii = b_IsAscii;

        return RESTR_OK;
    }
    else
    {
        return RESTR_FAIL;
    }
}

static INT32 _rest_wifi_associate(CHAR *ps_password)
{
    INT32 i4_ret  = RESTR_OK;
    UINT8 ui1_idx = 0;
    BOOL  b_valid = FALSE;
    BOOL  b_IsAscii = FALSE;
    NET_802_11_ASSOCIATE_T t_associate;

    c_memset(&t_associate, 0, sizeof(t_associate));

    for (ui1_idx=0; ui1_idx<REST_TV_APS_NUM_MAX; ui1_idx++)
    {
        if (0 == c_strcmp(at_ess_info[ui1_idx].t_Ssid.ui1_aSsid, s_access_point))
        {
            c_strncpy(t_associate.t_Ssid.ui1_aSsid, s_access_point, REST_SSID_MAX_LEN);
            t_associate.t_Ssid.ui4_SsidLen = c_strlen(t_associate.t_Ssid.ui1_aSsid);
            c_memcpy(t_associate.t_Bssid, at_ess_info[ui1_idx].t_Bssid, sizeof(NET_802_11_BSSID_T));
            t_associate.e_AuthMode = at_ess_info[ui1_idx].e_AuthMode;
            t_associate.e_AuthCipher = at_ess_info[ui1_idx].e_AuthCipher;
            t_associate.e_AssocCase = IEEE_802_11_SCAN_ASSOC;
            DBG_INFO(("\n%s,%d,ui1_aSsid=%s,e_AuthMode=%d,e_AuthCipher=%d\n",
                            __FUNCTION__, __LINE__, t_associate.t_Ssid.ui1_aSsid,
                            t_associate.e_AuthMode,t_associate.e_AuthCipher));
            break;
        }
    }

    if (ui1_idx == REST_TV_APS_NUM_MAX)
    {
        rest_network_update_error_code(REST_NET_WIFI_NOT_EXISTED);
        DBG_LOG_PRINT(("[KK] %s, %d,  REST_TV_APS_NUM_MAX!!!\n", __FUNCTION__, __LINE__));
        return RESTR_FAIL;
    }

    b_valid = _rest_is_valid_input_key(&t_associate, ps_password, &b_IsAscii);
    if (b_valid)
    {
        t_associate.t_Key.pui1_PassPhrase = ps_password;
        t_associate.t_Key.b_IsAscii = b_IsAscii;
        i4_ret = a_nw_wlan_associate(&t_associate);
        rest_network_update_error_code(REST_NET_EMPTY);
        if (i4_ret != NWR_OK)
        {
            rest_network_update_error_code(REST_NET_WIFI_CONNECTION_ERROR);
            DBG_LOG_PRINT(("[KK] %s, %d, a_nw_wlan associate FAILED!!!\n", __FUNCTION__, __LINE__));
            return RESTR_FAIL;
        }
    }
    else
    {
        rest_network_update_error_code(REST_NET_WIFI_AUTH_REJECTED);
        return RESTR_FAIL;
    }

    return RESTR_OK;
}

static VOID _rest_network_speed_test_notify_callback(
                                INT32               i4Status,
                                DOUBLE              u4Speed)
{
    DBG_INFO(("\n[KK] %s,%s,%d,e_g_nw_test_status=%d,i4Status=%d,u4Speed=%f\n",
                __FILE__, __FUNCTION__, __LINE__,
                (UINT32)e_g_nw_test_status, i4Status, u4Speed));

    /* test connection speed timeout*/
    if (e_g_nw_test_status != REST_NW_TEST_SPEED_TEST)
    {
        return;
    }

    /* speed test is finished */
    e_g_nw_test_status = REST_NW_TEST_END;

    c_timer_stop(h_test_timer);

    if (i4Status == 0)
    {
        /* kbit/s, middleware return data is bytes/s, so need data*8/1024 */
        t_g_test_result.conn_speed = u4Speed/128;
        t_g_test_result.reconnecting=FALSE;
        rest_network_update_error_code(REST_NET_SUCCESS);
        update_test_connection_status();
    }
    else
    {
        /* speed test is failed */
        t_g_test_result.conn_speed = 0;
    }

    b_test_success = TRUE;

    return;
}

static INT32 _rest_network_speed_test(VOID)
{
    INT32    i4_ret = 0;

    DBG_INFO(("[KK] _rest_network_speed_test.\n\r"));

    e_g_nw_test_status = REST_NW_TEST_SPEED_TEST;

    i4_ret= c_speedtest(NULL, _rest_network_speed_test_notify_callback);
    if (i4_ret != 0)
    {
        DBG_ERROR(("[KK] c_speedtest start failed.\n\r"));
        c_speedtest_cancel();

        e_g_nw_test_status = REST_NW_TEST_END;
        update_test_connection_status();
        c_timer_stop(h_test_timer);
    }

    return i4_ret;
}

static VOID _rest_test_connection_notify_handler(
                                    VOID*      pv_data,
                                    SIZE_T     z_data_size
                                    )
{
    REST_NW_NFY_DATA_T* pt_nw_nfy_data = (REST_NW_NFY_DATA_T*)pv_data;
    BOOL                b_nw_is_connect = FALSE;
	UINT8				ui1_demo_mode = 0;

    DBG_INFO(("\n[KK] %s,%s,%d,ui4_g_test_connection_tag=%d,pv_tag=%d"
                "e_g_nw_test_status=%d,b_nw_is_connect=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                ui4_g_rest_test_connection_tag, pt_nw_nfy_data->pv_tag,
                (UINT32)e_g_nw_test_status,
                (UINT32)pt_nw_nfy_data->pv_nfy_param));

    if ((UINT32)pt_nw_nfy_data->pv_tag == ui4_g_rest_test_connection_tag)
    {
        switch(pt_nw_nfy_data->e_nfy_id)
        {
            case NW_NFY_ID_INTERN_CT_RESULT:
            {
                DBG_INFO(("[KK] NW_NFY_ID_INTERN_CT_RESULT !!!\n\r"));

                b_nw_is_connect = (BOOL)(UINT32)(pt_nw_nfy_data->pv_nfy_param);
                if (b_nw_is_connect)
                {
                    c_strncpy(t_g_test_result.dns, "TRUE", REST_DNS_LEN);
                    e_g_nw_test_status = REST_NW_TEST_SPEED_TEST;

                    /* update NTP status again! */
                    _rest_test_ntp();

            		a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);
            		if (ui1_demo_mode == 0)
            		{
                        c_thread_delay(1000);
                        _rest_network_speed_test();
            		}

                }
                else
                {
                    c_strncpy(t_g_test_result.dns, "FALSE", REST_DNS_LEN);
                    t_g_test_result.conn_speed = 0;
                    e_g_nw_test_status = REST_NW_TEST_END;
                    update_test_connection_status();
                    c_timer_stop(h_test_timer);
                }
            }
                break;
            default:
                return;
        }
    }
}

static VOID _rest_test_connection_notify_callback(
                                    VOID*       pv_tag,
                                    NW_NFY_ID_T e_nfy_id,
                                    VOID*       pv_nfy_param
                                    )
{
    REST_NW_NFY_DATA_T t_nw_nfy_data;
    //CHAR s_resume_ap[APP_NAME_MAX_LEN+1] = {0};
    //INT32 i4_ret = RESTR_OK;

    if (e_g_nw_test_status != REST_NW_TEST_CONNECT_TEST)
    {
        return;
    }

    DBG_INFO(("[KK] _rest_test_connection_notify_callback, e_nfy_id: %d.\n\r", e_nfy_id));
#if 0
    i4_ret = a_am_get_active_app(s_resume_ap);
    if (i4_ret != AEER_OK)
    {
        DBG_ERROR(("\n%s,get active app failed\n", __FUNCTION__));
        return;
    }

    /* only support one NW client */
    if (strcmp(s_resume_ap, MENU_NAME) == 0)
    {
        DBG_INFO(("\n%s,s_resume_ap=%s\n", __FUNCTION__, s_resume_ap));
        return;
    }
#endif
    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    rest_async_invoke(_rest_test_connection_notify_handler,
                      &t_nw_nfy_data,
                      sizeof(REST_NW_NFY_DATA_T),
                      TRUE);
}

static VOID _rest_test_timer_nfy_handler(
                                    VOID*      pv_data,
                                    SIZE_T     z_data_size
                                    )
{
    DBG_INFO(("[KK][Warning] <%s,%d> test timeout! e_g_nw_test_status=%d\n", __FUNCTION__, __LINE__, e_g_nw_test_status));
    e_g_nw_test_status = REST_NW_TEST_END;
    update_test_connection_status();
}

static VOID _rest_test_timer_nfy_cb(HANDLE_T  pt_tm_handle,
                                    VOID*     pv_tag)
{
    rest_async_invoke(_rest_test_timer_nfy_handler, NULL, 0, TRUE);
}

static VOID _rest_test_network_connection_start(VOID)
{
    INT32              i4_ret  = RESTR_OK;
    NW_DHCP_STATE_T    e_dhcp_state = NW_DHCP_STOPPED;
    BOOL               b_auto_ip  = FALSE;
    UINT8              ui1_retries = 0;

    if (NULL_HANDLE == h_test_timer)
    {
        i4_ret = c_timer_create(&h_test_timer);
        REST_LOG_ON_FAIL(i4_ret);
    }
    rest_network_update_error_code(REST_NET_EMPTY);

    b_test_success = FALSE;
    e_g_nw_test_status = REST_NW_TEST_CONNECT_TEST;

    /* If Ethernet is not connected, let check the current BSS status first!                                  */
    /* If a_nw_wlan_get_curr_bss() failed, let's try more times since WiFi AP may be just under connecting... */
    if (!a_nw_is_ethernet_plugin())
    {
        do
        {
            NET_802_11_BSS_INFO_T    CurrBss;
            c_memset(&CurrBss, 0, sizeof(CurrBss));
            i4_ret = a_nw_wlan_get_curr_bss(&CurrBss);

            /* AP connection may be in progress, let wait */
            if ((NWR_OK == i4_ret) && (CurrBss.t_Ssid.ui4_SsidLen != 0))
            {
                break;
            }
            else
            {
                DBG_INFO(("%s: a_nw_wlan_get_curr_bss() failed!", __FUNCTION__));
                DBG_INFO(("delay 1s & try #: %d\n", ui1_retries));
                c_thread_delay(1000);
                ++ui1_retries;
            }
        }
        while(ui1_retries < 5);
    }

    /* get network interface */
    _rest_test_interface();

    nw_custom_get_auto_ip_config(&b_auto_ip);
    DBG_LOG_PRINT(("%s: Current auto_ip_config setting is %s.", __FUNCTION__, (b_auto_ip) ? "TRUE" : "FASLE"));
    if (TRUE == b_auto_ip)
    {
        ui1_retries = 0;
        do
        {
            i4_ret = a_nw_get_dhcp_status(&e_dhcp_state);

            /* DHCP may be in progress, let wait */
            if ((NW_DHCP_STOPPED == e_dhcp_state)
                || (NW_DHCP_STARTING == e_dhcp_state))
            {
                DBG_INFO(("%s: Current e_dhcp_state is %d!", __FUNCTION__, e_dhcp_state));
                DBG_INFO(("delay 1s & wait #: %d\n", ui1_retries));
                c_thread_delay(1000);
                ++ui1_retries;
                a_nw_get_dhcp_status(&e_dhcp_state);
            }
            else
            {
                break;
            }
        }
        while(ui1_retries < 5);

        do{
            ui1_retries = 0;
            if(e_dhcp_state == NW_DHCP_STARTING)
            {
                c_thread_delay(1000);
                ++ui1_retries;
                a_nw_get_dhcp_status(&e_dhcp_state);
            }
            else
            {
                break;
            }
        }while(ui1_retries < 10);

        DBG_LOG_PRINT(("\n[KK] %s,%s,%d, e_dhcp_state=%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, e_dhcp_state, i4_ret));

        /* get the dhcp status, if current dhcp is "on" and not get ip addr, should return test fail */
        if ((e_dhcp_state != NW_DHCP_STOPPED) && (e_dhcp_state != NW_DHCP_STARTED))
        {
            b_test_success = FALSE;
            e_g_nw_test_status = REST_NW_TEST_END;
            update_test_connection_status();
            return;
        }
    }

    /* ntp interface */
    _rest_test_ntp();

    //TODO:
    //rest_network_update_error_code(REST_NET_SUCCESS);

    c_timer_stop(h_test_timer);
    i4_ret = c_timer_start (h_test_timer,
                            REST_TEST_CONNECTION_TIMER,
                            X_TIMER_FLAG_ONCE,
                            _rest_test_timer_nfy_cb,
                            NULL);
    REST_LOG_ON_FAIL(i4_ret);

    if (ui4_g_rest_test_connection_nfy_id > 0)
    {
        i4_ret = a_nw_unregister(ui4_g_rest_test_connection_nfy_id);
        REST_LOG_ON_FAIL(i4_ret);
        ui4_g_rest_test_connection_nfy_id = 0;
    }

    ui4_g_rest_test_connection_tag++;
    i4_ret = a_nw_register(_rest_test_connection_notify_callback,
                           (VOID*)ui4_g_rest_test_connection_tag, &ui4_g_rest_test_connection_nfy_id);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = a_nw_connection_test((CHAR*)"www.google.com");
    REST_LOG_ON_FAIL(i4_ret);

    if (i4_ret != NWR_OK)
    {
		g_pin_google_success = TRUE;//Add google test condition

        b_test_success = FALSE;
        e_g_nw_test_status = REST_NW_TEST_END;
        update_test_connection_status();
        c_timer_stop(h_test_timer);

        if (ui4_g_rest_test_connection_nfy_id > 0)
        {
            i4_ret = a_nw_unregister(ui4_g_rest_test_connection_nfy_id);
            REST_LOG_ON_FAIL(i4_ret);
            ui4_g_rest_test_connection_nfy_id = 0;
        }
        return;
    }
    else
    {
        DBG_INFO(("a_nw_connection_test() return OK! Wait for async notification..."));
    }

    return;
}

static VOID _rest_test_network_connection(VOID*      pv_data,
                                          SIZE_T     z_data_size)
{
    _rest_test_network_connection_start();
}

VOID _rest_wifi_pre_associate_hidden_network(VOID)
{
        UINT32      ui4_len;
        INT32       i4_ret;

        DBG_INFO(("%s, %d, Enter\n", __FUNCTION__, __LINE__));
        ui4_len= c_strlen(s_access_point);
        i4_ret = a_nw_wlan_scan_with_ssid(s_access_point, ui4_len);
}


VOID _rest_wifi_associate_hidden_network(VOID)
{
    INT32                   i4_ret = RESTR_OK;
    NET_802_11_ASSOCIATE_T  t_associate;

    DBG_LOG_PRINT(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    c_memset(&t_associate, 0, sizeof(t_associate));

    i4_ret = _rest_wifi_pre_associate(s_net_pwd, &t_associate);
    if (i4_ret != RESTR_OK)
    {
        rest_network_update_error_code(REST_NET_WIFI_CONNECTION_ERROR);
        DBG_LOG_PRINT(("[KK] %s, %d, _rest_wifi_pre_associate FAILED!!!\n", __FUNCTION__, __LINE__));
        return;
    }

    i4_ret = a_nw_custom_wlan_disassociate();
    REST_LOG_ON_FAIL(i4_ret);
    i4_ret = a_nw_wlan_associate(&t_associate);
    if (i4_ret != NWR_OK)
    {
        rest_network_update_error_code(REST_NET_WIFI_CONNECTION_ERROR);
        DBG_LOG_PRINT(("[KK] %s, %d, a_nw_wlan associate FAILED!!!\n", __FUNCTION__, __LINE__));
        return;
    }
}

static VOID _rest_network_associate_handler(VOID*      pv_data,
                                            SIZE_T     z_data_size)
{
    BOOL*   pb_hidden = (BOOL*)pv_data;
    g_hidden_network = *pb_hidden;

    if (*pb_hidden == TRUE)
    {
        /* rest client need some time  */
       c_thread_delay(600);

        _rest_wifi_pre_associate_hidden_network();

    }
    else
    {
        DBG_INFO(("%s, %d, Enter\n", __FUNCTION__, __LINE__));
        INT32 i4_ret = RESTR_OK;

        c_thread_delay(600);

        i4_ret = a_nw_custom_wlan_disassociate();
        REST_LOG_ON_FAIL(i4_ret);

        c_thread_delay(300);
        rest_stop_softap();

        c_thread_delay(300);
        rest_start_softap();

        c_thread_delay(300);

        rest_wifi_associate(s_net_pwd);
    }
    t_g_test_result.reconnecting=FALSE;

}
static VOID _rest_no_ready_delay_notify_network_status_timer_nfy_cb(HANDLE_T  pt_tm_handle,
                                    VOID*     pv_tag)
{
    INT32 i4_ret = RESTR_OK;
    ui1_g_rest_ready_count ++;
    if(rest_get_python_ready() || (ui1_g_rest_ready_count >= 20))
    {
        rest_event_notify("tv_settings/network/connection_status", 1, "");
        c_timer_stop(h_rest_ready_timer);
    }
    else
    {
        c_timer_stop(h_rest_ready_timer);
        i4_ret = c_timer_start (h_rest_ready_timer,
                                REST_CHECK_READY_TIMER,
                                X_TIMER_FLAG_ONCE,
                                _rest_no_ready_delay_notify_network_status_timer_nfy_cb,
                                NULL);
        REST_LOG_ON_FAIL(i4_ret);
    }
}

VOID rest_no_ready_delay_notify_network_status()
{
    INT32 i4_ret = RESTR_OK;
    ui1_g_rest_ready_count =0;
    if (NULL_HANDLE == h_rest_ready_timer)
    {
        i4_ret = c_timer_create(&h_rest_ready_timer);
        REST_LOG_ON_FAIL(h_rest_ready_timer);
    }
    c_timer_stop(h_rest_ready_timer);
    i4_ret = c_timer_start (h_rest_ready_timer,
                            REST_CHECK_READY_TIMER,
                            X_TIMER_FLAG_ONCE,
                            _rest_no_ready_delay_notify_network_status_timer_nfy_cb,
                            NULL);
    REST_LOG_ON_FAIL(i4_ret);
}

INT32 rest_check_network_time()
{
     struct      timeval tv;
    struct      timezone tz;
    DTG_T       t_loc_dtg;
    INT64       sec;

    c_memset(&t_loc_dtg, 0, sizeof(DTG_T));
    if (gettimeofday(&tv, &tz) == 0)
    {
        sec = (INT64)tv.tv_sec;
        c_dt_utc_sec_to_loc_dtg(sec, &t_loc_dtg);

        DBG_INFO(("[year,mon,day,hour,min] =[%d-%d-%d-%d-%d] \n ",
                 t_loc_dtg.ui2_yr,
                 t_loc_dtg.ui1_mo,
                 t_loc_dtg.ui1_day,
                 t_loc_dtg.ui1_hr,
                 t_loc_dtg.ui1_min));

        if (((t_loc_dtg.ui2_yr == 0) && (t_loc_dtg.ui1_mo == 0)) ||
            (t_loc_dtg.ui2_yr == 1970))
        {
            return 0;
        }

        return 1;
    }

    return 0;
}

INT32 rest_wifi_associate(CHAR *ps_password)
{
    return _rest_wifi_associate(ps_password);
}

INT32 rest_wifi_associate_ex(BOOL b_hidden, CHAR *ps_password)
{
    DBG_INFO(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    INT32 i4_ret = RESTR_OK;
    BOOL    b_hidden_network = b_hidden;

    c_memset(s_net_pwd, 0, REST_PASSWORD_LEN+1);
    c_strncpy(s_net_pwd, ps_password, REST_PASSWORD_LEN);
    rest_network_update_error_code(REST_NET_EMPTY);
    t_g_test_result.reconnecting=TRUE;
    g_hidden_network = b_hidden;

    DBG_LOG_PRINT(("%s, %d, pwd: %s b_hidden_network=%d \n", __FUNCTION__, __LINE__, s_net_pwd,b_hidden_network));

    i4_ret = rest_async_invoke(_rest_network_associate_handler, (VOID*)&b_hidden_network, sizeof(BOOL), TRUE);
    REST_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 rest_set_wifi_ssid(CHAR *ps_ssid)
{
    return _rest_set_wifi_ssid(ps_ssid);
}

INT32 rest_get_wifi_ssid(CHAR *ps_ssid)
{
    return _rest_get_wifi_ssid(ps_ssid);
}

INT32 rest_get_curr_access_point(REST_DATA_WIFI_AP_T *pt_ap)
{
    NW_WLAN_STATE_T e_wlan_state = NW_WLAN_UNPLUG;
    a_nw_wlan_status(&e_wlan_state);

    DBG_LOG_PRINT(("\n[NW][Rest] [%s, %d] e_wlan_state = %d\n", __FUNCTION__, __LINE__, e_wlan_state));

    if (e_wlan_state == NW_WLAN_ASSOCIATE)
    {
        return _rest_get_curr_access_point(pt_ap);
    }
    else
    {
        return RESTR_FAIL;
    }
}

INT32 rest_get_access_point_by_ssid(CHAR *ps_ssid, REST_DATA_WIFI_AP_T *pt_ap)
{
    UINT8 ui1_idx = 0;

    if (NULL == ps_ssid || NULL == pt_ap)
    {
        DBG_ERROR(("%s, %d ERROR!", __FUNCTION__, __LINE__));
        return RESTR_INV_ARG;
    }
    pthread_mutex_lock(&ssid_lock);
    for (ui1_idx = 0; ui1_idx < t_g_ap_list.ap_num; ui1_idx++)
    {
        if (c_strcmp(t_g_ap_list.aplist[ui1_idx].name, ps_ssid) == 0)
        {
            DBG_INFO(("\n%s,%d, Found Matched one ap: %s\n", __FUNCTION__, __LINE__, ps_ssid));
            c_memcpy(pt_ap, &(t_g_ap_list.aplist[ui1_idx]), sizeof(REST_DATA_WIFI_AP_T));
            break;
        }
    }
    pthread_mutex_unlock(&ssid_lock);

    if (ui1_idx == t_g_ap_list.ap_num)
    {
        DBG_ERROR(("%s, %d ERROR!", __FUNCTION__, __LINE__));
        return RESTR_FAIL;
    }

    return RESTR_OK;
}

INT32 rest_get_curr_ap_security_type(CHAR *ps_security)
{
    INT32 i4_ret = RESTR_OK;
    CHAR  s_em[REST_DATA_EM_LEN+1] = {0};
    NET_802_11_BSS_INFO_T t_CurrBss;

    if (!ps_security)
    {
        return RESTR_INV_ARG;
    }

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    REST_LOG_ON_FAIL(i4_ret);

    if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        _rest_authmode2str(t_CurrBss.e_AuthMode, s_em);
    }
    else
    {
        c_strcpy(s_em, REST_STR_NOT_AVAILABLE);
    }

    c_strncpy(ps_security, s_em, REST_DATA_EM_LEN);

    return RESTR_OK;
}

INT32 rest_update_ap_list_with_local_buff(VOID)
{
    /* need update ap list */
    _rest_update_ap_list_with_local_buff();

    return RESTR_OK;
}

INT32 rest_cmd_get_wireless_access_points(cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = rest_pack_aps(&t_g_ap_list, root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

INT32 rest_cmd_get_wifi_password(cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = rest_pack_ap_password_to_json(root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

INT32 rest_cmd_test_network_connection(VOID)
{
    INT32 i4_ret  = RESTR_OK;
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = rest_async_invoke(_rest_test_network_connection, NULL, 0, TRUE);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_network_test_results(cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_g_test_result, 0, sizeof(t_g_test_result));
    _rest_test_ntp();
    _rest_test_interface();
    _rest_test_dns();
    _rest_test_speed();

    i4_ret = rest_pack_test_connection(&t_g_test_result, root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

VOID rest_test_interface()
{
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    _rest_test_interface();
}

INT32 rest_cmd_get_network_test_results_ex(VOID)
{
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_g_test_result, 0, sizeof(t_g_test_result));

    rest_network_update_error_code(REST_NET_EMPTY);
    c_strncpy(t_g_test_result.dns, REST_STR_NOT_AVAILABLE, REST_DNS_LEN);

    _rest_test_ntp();
    _rest_test_interface();

    return RESTR_OK;
}

INT32 rest_cmd_get_current_access_point(cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;
    REST_DATA_WIFI_AP_T t_ap;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_ap, 0, sizeof(t_ap));
    i4_ret = _rest_get_curr_access_point(&t_ap);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = rest_pack_ap(&t_ap, root, i4_ret);
    REST_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

INT32 rest_cmd_set_current_access_point(cJSON *jpackage, cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;
    REST_DATA_WIFI_AP_T t_ap;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_ap, 0, sizeof(REST_DATA_WIFI_AP_T));
    i4_ret = rest_unpack_json_ap(&t_ap, jpackage);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = _rest_set_wifi_ssid(t_ap.name);
    REST_LOG_ON_FAIL(i4_ret);

    rest_pack_json_directly(root, i4_ret);
    return i4_ret;
}

INT32 rest_cmd_set_wifi_password(cJSON *jpackage, cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;
    T_REST_WRITE_REQ_CMD t_req;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_req, 0, sizeof(T_REST_WRITE_REQ_CMD));

    i4_ret = rest_unpack_json_to_string_by_request_value(&t_req, jpackage, "VALUE");
    REST_LOG_ON_FAIL(i4_ret);

    if(i4_ret == RESTR_OK && t_req.value != NULL)
    {
        i4_ret = _rest_wifi_associate(t_req.value);
        REST_LOG_ON_FAIL(i4_ret);
    }

    if (t_req.value != NULL)
    {
        c_mem_free(t_req.value);
        t_req.value = NULL;
    }

    rest_pack_json_directly(root, i4_ret);
    return RESTR_OK;
}

INT32 rest_cmd_action_start_ap_search(cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_wlan_scan();
    REST_LOG_ON_FAIL(i4_ret);

    rest_pack_json_directly(root, i4_ret);
    return i4_ret;
}

INT32 rest_cmd_action_stop_ap_search(cJSON *root)
{
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    rest_pack_json_directly(root, 0);
    return RESTR_OK;
}

INT32 rest_cmd_get_nw_connection_type(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    BOOL  b_ethernet = FALSE;
    CHAR  s_conn_type[REST_NW_CONN_TYPE_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_ethernet_connect_info(&b_ethernet);
    REST_LOG_ON_FAIL(i4_ret);

    if (b_ethernet)
    {
        c_strncpy(s_conn_type, "Ethernet", REST_NW_CONN_TYPE_LEN);
    }
    else
    {
        c_strncpy(s_conn_type, "WiFi", REST_NW_CONN_TYPE_LEN);
    }

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_conn_type, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_wifi_ssid(cJSON *root)
{
    NET_802_11_BSS_INFO_T t_CurrBss;
    INT32 i4_ret = RESTR_OK;
    CHAR  s_ssid[REST_SSID_MAX_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    REST_LOG_ON_FAIL(i4_ret);

    if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        c_strncpy(s_ssid, t_CurrBss.t_Ssid.ui1_aSsid, REST_SSID_MAX_LEN);
    }

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_ssid, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_wifi_security_type(cJSON *root)
{
    NET_802_11_BSS_INFO_T t_CurrBss;
    INT32 i4_ret = RESTR_OK;
    CHAR  s_em[REST_DATA_EM_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    REST_LOG_ON_FAIL(i4_ret);

    if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        _rest_authmode2str(t_CurrBss.e_AuthMode, s_em);
    }

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_em, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_ip_address(cJSON *root)
{
    INT32 i4_ret  = RESTR_OK;
    CHAR  s_ip_address[REST_IP_ADDRESS_LEN+1] = {0};
    NW_IP_INFO_T t_ip_info = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = _rest_get_ip_address(s_ip_address, t_ip_info.ui4_address);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_ip_address, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 rest_cmd_get_nw_gateway(cJSON *root)
{
    NW_IP_INFO_T t_ip_info = {0};
    INT32 i4_ret = RESTR_OK;
    CHAR  s_gateway[REST_IP_ADDRESS_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = _rest_get_ip_address(s_gateway, t_ip_info.ui4_gw);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_gateway, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_nw_subnet_mask(cJSON *root)
{
    NW_IP_INFO_T t_ip_info = {0};
    INT32 i4_ret = RESTR_OK;
    CHAR  s_subnet_mask[REST_IP_ADDRESS_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = _rest_get_ip_address(s_subnet_mask, t_ip_info.ui4_netmask);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_subnet_mask, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_nw_prefer_dns_server(cJSON *root)
{
    NW_IP_INFO_T t_ip_info = {0};
    INT32 i4_ret = RESTR_OK;
    CHAR  s_dns[REST_IP_ADDRESS_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = _rest_get_ip_address(s_dns, t_ip_info.ui4_1st_dns);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_dns, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_alternate_dns_server(cJSON *root)
{
    NW_IP_INFO_T t_ip_info = {0};
    INT32 i4_ret = RESTR_OK;
    CHAR  s_dns[REST_IP_ADDRESS_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
    REST_LOG_ON_FAIL(i4_ret);

    i4_ret = _rest_get_ip_address(s_dns, t_ip_info.ui4_2nd_dns);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_string(s_dns, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_nw_download_speed(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    UINT32 ui4_download_speed = 50;
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_int(ui4_download_speed, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_signal_strength(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    UINT32 ui4_signal_strength = 80;
    REST_DATA_PARAM_1_T t_data_param = {0};
    NET_802_11_BSS_INFO_T t_CurrBss;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    REST_LOG_ON_FAIL(i4_ret);

    if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        ui4_signal_strength = (UINT32)t_CurrBss.i2_Level;
    }

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_int(ui4_signal_strength, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_wifi_rssi(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    UINT32 ui4_wifi_channel = 0;
    REST_DATA_PARAM_1_T t_data_param = {0};
    NET_802_11_BSS_INFO_T t_CurrBss;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    REST_LOG_ON_FAIL(i4_ret);

    if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        ui4_wifi_channel = (UINT32)t_CurrBss.i2_Channel;
    }

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_int(ui4_wifi_channel, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_wifi_channel(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    UINT32 ui4_wifi_channel = 0;
    REST_DATA_PARAM_1_T t_data_param = {0};
    NET_802_11_BSS_INFO_T t_CurrBss;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    REST_LOG_ON_FAIL(i4_ret);

    if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        ui4_wifi_channel = (UINT32)t_CurrBss.i2_Channel;
    }

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = i4_ret;

    i4_ret = rest_pack_int(ui4_wifi_channel, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_rj45_mac_address(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    CHAR  s_mac[REST_MAC_ADDRESS_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_mac_addr_string(NI_ETHERNET_0, s_mac);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = RESTR_OK;

    i4_ret = rest_pack_string(s_mac, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_wlan_mac_address(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    CHAR  s_mac[REST_MAC_ADDRESS_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_mac_addr_string(NI_WIRELESS_0, s_mac);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = RESTR_OK;

    i4_ret = rest_pack_string(s_mac, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

INT32 rest_cmd_get_bt_mac_address(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    CHAR  s_mac[REST_MAC_ADDRESS_LEN+1] = {0};
    REST_DATA_PARAM_1_T t_data_param = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = a_nw_get_mac_addr_string(NI_ETHERNET_0, s_mac);
    REST_LOG_ON_FAIL(i4_ret);

    t_data_param.e_enable_type = REST_DATA_ENABLE_TYPE_TRUE;
    t_data_param.e_lock_type = REST_DATA_LOCK_TYPE_TRUE;
    t_data_param.i4_ret_code = RESTR_OK;

    i4_ret = rest_pack_string(s_mac, root, &t_data_param);
    REST_LOG_ON_FAIL(i4_ret);

    return RESTR_OK;
}

static INT32 _rest_get_current_softap_channel(VOID)
{
    INT32 i4_ap_channel  = -1;

    DBG_API(("%s, %d, Enter, i4_ap_channel:%d.\n", __FUNCTION__, __LINE__, i4_ap_channel));
	return RESTR_OK;

    if (0 != access("/data/wifi/hostapd.conf", F_OK))
    {
//        DBG_LOG_PRINT(("%s, %d, Enter, /data/wifi/hostapd.conf not exist!\n", __FUNCTION__, __LINE__));
        return i4_ap_channel;
    }
    else
    {
        INT32 channel_num =0;
        CHAR  channel[100] = {0};
        FILE* fp=fopen("/data/wifi/hostapd.conf","r");
        if (fp)
        {
            while(!feof(fp) && fscanf(fp,"%95s",channel) == 1)
            {
                if (sscanf(channel,"channel=%d",&channel_num) == 1)
                {
                    break;
                }
            }
            fclose(fp);
        }

        KK_LOG(KK_LOG_LVL_API, "[REST][NW]", "current softap channel = %d.\n\r", channel_num);

        return channel_num;
    }
}

static INT32 _rest_change_softap_channel_setting_with_current_bss(VOID)
{
    INT32                   i4_ret = RESTR_OK;
    NET_802_11_BSS_INFO_T   t_CurrBss;
    INT32                   i4_try = 0;
    INT32 i4_current_channel  = _rest_get_current_softap_channel();

    while (i4_try < 10)
    {
        c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));

        i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
        REST_LOG_ON_FAIL(i4_ret);

        if (NWR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_API, "[REST][NW]", "a_nw_wlan_get_curr_bss failed. i4_ret: %d\n\r", i4_ret);
            i4_try ++;
            c_thread_delay(100);
        }
        else
        {
            break;
        }
    }

    if (i4_ret != NWR_OK || t_CurrBss.t_Ssid.ui4_SsidLen == 0 || t_CurrBss.i2_Channel == 0)
    {
        KK_LOG(KK_LOG_LVL_API, "[REST][NW]", "a_nw_wlan_get_curr_bss failed. i4_ret: %d\n\r", i4_ret);
        return RESTR_FAIL;
    }

    KK_LOG(KK_LOG_LVL_API, "[REST][NW]", "channel = %d. i4_current_channel: %d\n\r",
                    t_CurrBss.i2_Channel, i4_current_channel);

    if (i4_current_channel != t_CurrBss.i2_Channel)
    {
        rest_change_softap_channel_setting(t_CurrBss.i2_Channel);
        rest_stop_softap();
        rest_start_softap_ex();
    }

    return RESTR_OK;
}
static VOID _receive_associate_ok(VOID*      pv_data,
                                            SIZE_T     z_data_size)
{
     rest_network_update_error_code(REST_NET_SUCCESS);

    /* TODO: (steven) need update softAP channel */
    _rest_change_softap_channel_setting_with_current_bss();
    return;
}

VOID rest_change_softap_channel_setting(INT16 i2_channel)
{
    INT32 i4_ap_channel       = (INT32)i2_channel;
    INT32 i4_current_channel  = _rest_get_current_softap_channel();
	return;

    KK_LOG(KK_LOG_LVL_API, "[REST][NW]", "i4_ap_channel = %d. i4_current_channel: %d\n\r",
                    i4_ap_channel, i4_current_channel);

    if (i4_current_channel != i4_ap_channel)
    {
        if (0 != access("/data/wifi/hostapd.conf", F_OK))
        {
         //   DBG_LOG_PRINT(("%s, %d, Enter, /data/wifi/hostapd.conf not exist!\n", __FUNCTION__, __LINE__));
            return;
        }

        char channel[100] = {0};

        if(i4_ap_channel > 0 && i4_ap_channel < 15)
        {
            system("sed -i \'5c hw_mode=g\' /data/wifi/hostapd.conf");// for 2.4G
        }
        else
        {
            system("sed -i \'5c hw_mode=a\' /data/wifi/hostapd.conf");// for 5G
        }
        c_sprintf(channel, "sed -i \'4c channel=%d\' /data/wifi/hostapd.conf", i4_ap_channel);
        system(channel);
        s_sync();
        //system("sync");
        //system("echo cat /data/wifi/hostapd.conf"); //dolphin not use
        //system("cat /data/wifi/hostapd.conf");
    }
}

VOID rest_set_default_name(VOID)
{
    char name[100] = {0};
    UINT32 random_num = 0;
    UINT32 seed = 0;
    seed = (unsigned)clock();
    srand(seed);
    random_num = rand()%9000 + 1000;
    c_sprintf(name, "%s%d", VIZIO_SOFTAP_PRE_NAME, random_num);

    DBG_LOG_PRINT(("%s, %d, Enter name: %s\n", __FUNCTION__, __LINE__, name));
#ifdef A_C4TV_APRON_CAST_NAME
    a_c4tv_apron_set_cast_name(name);
#else
    a_cfg_custom_set_tv_name(name);
#endif
    rest_event_notify("tv_settings/cast/device_name", 0, name);
}

VOID rest_change_softap_default_name(VOID)
{
    DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    if (0 != access("/data/wifi/hostapd.conf", F_OK))
    {
      //  DBG_LOG_PRINT(("%s, %d, Enter, /data/wifi/hostapd.conf not exist!\n", __FUNCTION__, __LINE__));
        return;
    }
    else
    {
        char cmd[100] = {0};
        char name[100] = {0};
        UINT32 random_num = 0;
        UINT32 seed = 0;
        seed = (unsigned)clock();
        srand(seed);
        random_num = rand()%9000 + 1000;
        c_sprintf(name, "%s%d", VIZIO_SOFTAP_PRE_NAME, random_num);

        DBG_INFO(("%s, %d, Enter name: %s\n", __FUNCTION__, __LINE__, name));
#ifdef APP_C4TV_SUPPORT
        a_c4tv_apron_set_cast_name(name);
        rest_event_notify("tv_settings/cast/device_name", 0, name);
#endif

        c_sprintf(cmd, "sed -i \'7c ssid=%s\' /data/wifi/hostapd.conf", name);
        system(cmd);

        //system("sync");
        //system("cat /data/wifi/hostapd.conf"); //dolphin not use
        s_sync();
    }
}

VOID rest_change_softap_name(CHAR* name)
{
    DBG_API(("%s, %d, Enter\n"));
    char ssid[REST_SSID_MAX_LEN+1] = {0};
    char cmd[100] = {0};
	return;

    if (name == NULL)
    {
        return;
    }

    if (0 != access("/data/wifi/hostapd.conf", F_OK))
    {
      //  DBG_LOG_PRINT(("%s, %d, Enter, /data/wifi/hostapd.conf not exist!\n", __FUNCTION__, __LINE__));
        return;
    }

    c_strncpy(ssid, name, REST_SSID_MAX_LEN);

    DBG_API(("%s, %d, len of [%s]: %u!\n", __FUNCTION__, __LINE__, name, c_strlen(name)));

    c_snprintf(cmd, 100, "sed -i \'7c ssid=%s\' /data/wifi/hostapd.conf", ssid);
    system(cmd);
    //system("sync");
    //system("cat /data/wifi/hostapd.conf"); //dolphin not use
    s_sync();
}

VOID rest_kill_proc_by_name(CHAR* name)
{
    char cmd[100] = {0};

    DBG_API(("%s, %d, Enter. name=%s\n", __FUNCTION__, __LINE__, name));

    c_snprintf(cmd, 100, "kill -9 `ps | grep %s | awk \'{print $1}\'`", name);
    system(cmd);
}

VOID rest_stop_softap(VOID)
{
    CHAR* ps_hostapd = "hostapd";
    CHAR* ps_dnsmasq = "dnsmasq";

    pthread_mutex_lock(&softap_lock);

    DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    rest_kill_proc_by_name(ps_hostapd);
    rest_kill_proc_by_name(ps_dnsmasq);

    system("ifconfig uap0 0.0.0.0");
    system("ifconfig uap0 down");

    pthread_mutex_unlock(&softap_lock);
}

VOID rest_start_softap(VOID)
{
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
	return;
    if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        DBG_INFO(("%s,%d.disable softap during demo mode!\n", __FUNCTION__, __LINE__));
        return;
    }
    if(0 != access("/tmp/support_softap", R_OK)){
        // DBG_LOG_PRINT(("L%d softap not supported\n\r", __LINE__));
        return;
    }

    pthread_mutex_lock(&softap_lock);

    DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));

    INT32 i4_ret = system("ifconfig | grep uap0 > /dev/null");

    if((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
    {
        DBG_INFO(("%s, %d, Uap0 exist, just Return, cannot start\n", __FUNCTION__, __LINE__));
        pthread_mutex_unlock(&softap_lock);
        return;
    }

    if (0 != access("/data/wifi/hostapd.conf", F_OK))
    {
       // DBG_LOG_PRINT(("%s, %d, Enter, /data/wifi/hostapd.conf not exist!\n", __FUNCTION__, __LINE__));
        pthread_mutex_unlock(&softap_lock);
        return;
    }

    system("hostapd -e /data/wifi/hostapd_entropy.bin /data/wifi/hostapd.conf &");

    int count = 100;
    while(count--)
    {
        i4_ret = system("ps | grep hostapd > /dev/null");
        if((-1 != i4_ret) && (WIFEXITED(i4_ret)) && (0==WEXITSTATUS(i4_ret)))
        {
            DBG_INFO(("hostapd start completed!\n"));
            break;
        }
        else
        {
            DBG_INFO(("Waiting for hostapd start completing ...\n"));
            usleep(250000);
        }
    }

    system("ifconfig uap0 up");

    system("ifconfig uap0 192.168.255.249 netmask 255.255.255.248");

    system("dnsmasq &");

    pthread_mutex_unlock(&softap_lock);
}

VOID rest_start_softap_ex()
{

    //DBG_API(("%s, %d, Enter\n", __FUNCTION__, __LINE__));
return;

    if (0 != access("/data/wifi/hostapd.conf", F_OK))
    {
        if (0 != access("/data/wifi", F_OK))
        {
            //system("mkdir /data/wifi");
            //system("chmod 777 /data/wifi"); //dolphin
            s_mkdir("/data/wifi");
            s_chmod("/data/wifi",0777);
        }

        system("cp -f /basic/softap/hostapd.conf /data/wifi/hostapd.conf");
        //system("sync");
        s_sync();
        rest_change_softap_default_name();
    }

    if (0 == access("/tmp/hostapd.conf", F_OK))
    {
        rest_stop_softap();
        //system("rm -f /tmp/hostapd.conf");
        s_rm("/tmp/hostapd.conf");
    }
    rest_start_softap();

}

// Stop both timer & softap.
VOID rest_stop_softap_ex(VOID)
{
    DBG_INFO(("%s, %d, Enter\n", __FUNCTION__, __LINE__));
    _rest_softap_stop_timer();
    rest_stop_softap();
}

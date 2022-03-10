
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <syslog.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

#include "mdns.h"
#include "sha1.h"

#include <sys/time.h>
//#include "res/menu2/menu_custom.h"

UINT32 u4_from_addr = 0;
static UINT32 u4_host_addr = 0;

static CHAR VIZIO_CAST_NAME[MDNS_VALUE_MAX_LEN] = {0};
static CHAR GOOGLE_CAST_ID[MDNS_VALUE_MAX_LEN] = {0};
static CHAR GOOGLE_CAST_CD[MDNS_VALUE_MAX_LEN] = {0};
static CHAR DEVICE_INSTANCE_ID[MDNS_VALUE_MAX_LEN] = {0};
static CHAR DEVICE_ID[2*SHA1HashSize] = {0};
static int is_mdns_registered = 0;
static int is_mdns_stop = 0;
static UINT32 u4_get_cid_count = 0;
pid_t dns_sd_pid = 0;
pid_t mdnsd_pid = 0;

#define ARG_NUM 32
#define ARG_LEN_MAX 64
static vizio_mdns_server_t gVizioMdnsServer;

//per 'VIZIO Smartcast mDNS Discovery Specification v0.7.pdf' remove rver, mver, bt and bver.
static mdns_key_val_t gVizioKeyVal[] =
{
    //{VIZIO_KEY_ID,mdns_vizio_get_key_id},
    {VIZIO_KEY_DID,mdns_vizio_get_key_did},
    {VIZIO_KEY_CID,mdns_vizio_get_key_cid},
    {VIZIO_KEY_CCD,mdns_vizio_get_key_ccd},
    {VIZIO_KEY_ETH,mdns_vizio_get_key_eth},
    {VIZIO_KEY_WIFI,mdns_vizio_get_key_wifi},
    //{VIZIO_KEY_BT,NULL},
    {VIZIO_KEY_FVER,mdns_vizio_get_key_fver},
    //{VIZIO_KEY_RVER,mdns_vizio_get_key_rver},
    //{VIZIO_KEY_MVER,mdns_vizio_get_key_mver},
    //{VIZIO_KEY_BVER,NULL},
    {VIZIO_KEY_DT,mdns_vizio_get_key_dt},
    {VIZIO_KEY_PWR,mdns_vizio_get_key_pwr},
    {VIZIO_KEY_OOBE,mdns_vizio_get_key_oobe},
    {VIZIO_KEY_ULI,mdns_vizio_get_key_uli},
    {VIZIO_KEY_TOS,mdns_vizio_get_key_tos},
    {VIZIO_KEY_NAME,mdns_vizio_get_key_name},
    {VIZIO_KEY_MDL,mdns_vizio_get_key_mdl},
    {VIZIO_KEY_SOC,mdns_vizio_get_key_soc},
    //{VIZIO_KEY_DL,mdns_vizio_get_key_dl},
    //{VIZIO_KEY_DC,mdns_vizio_get_key_dc},
    {VIZIO_KEY_VER,mdns_vizio_get_key_ver},
    //{VIZIO_KEY_ES,mdns_vizio_get_key_es},
    {VIZIO_KEY_HP,mdns_vizio_get_key_hp},
    {VIZIO_KEY_HSP,mdns_vizio_get_key_hsp},
    {VIZIO_KEY_WP,mdns_vizio_get_key_wp},
    {VIZIO_KEY_WSP,mdns_vizio_get_key_wsp},
};

static char* pc_argv[ARG_NUM];
static char* pc_argv_tmp[ARG_NUM][ARG_LEN_MAX];

//get serial number
INT32 mdns_vizio_get_key_id(CHAR *val,UINT8 *plen)
{
    //UINT32 len;
    INT32 ret;
    CHAR    s_sn[NAV_UPDATE_ULI_REG_INFO_SN_LEN+1] = {0};
    UINT32  ui4_buff_len = sizeof(s_sn);
    if(!val || !plen)
    {
        return -1;
    }
    ret = a_uli_get_serial_number((UINT8 *)s_sn, &ui4_buff_len);
    if(ret == 0)
    {
        /*
        len = strlen(s_sn);
        *plen = len;
        memcpy((VOID*)val,(VOID*)s_sn,len);
        */
        if(DEVICE_ID[0] == 0)
        {
            SHA1Context context;
            uint8_t device_id[SHA1HashSize] = {0};
            ret = SHA1Reset(&context);
            INT32 i = 0;
            if(ret)
            {
                DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            }
            ret = SHA1Input(&context,(const uint8_t*)s_sn,strlen(s_sn));
            if(ret)
            {
                DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            }
            ret = SHA1Result(&context,(uint8_t*)device_id);
            if(ret)
            {
                DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            }
            for(i = 0;i <SHA1HashSize;++i)
            {
                //c_dbg_stmt("%02x \n",device_id[i]);
                c_sprintf((CHAR*)(DEVICE_ID+i*2),"%02x",device_id[i]);
            }
        }
        *plen = 2*SHA1HashSize;
        memcpy((VOID*)val,(VOID*)DEVICE_ID,*plen);
            //DBG_LOG_PRINT(("\n zile_sha,DEVICE_ID = %s,%d,%s,%s\n",DEVICE_ID,__LINE__,__func__,__FILE__));
    }
    return ret;
}

// not sure yet
INT32 mdns_vizio_get_key_did(CHAR *val,UINT8 *plen)
{
    BOOL b_device_instance_id_initialized = FALSE;
    b_device_instance_id_initialized = (DEVICE_INSTANCE_ID[0] == 0)? FALSE : TRUE;

    if(!val || !plen)
    {
        return -1;
    }

    if(!b_device_instance_id_initialized)
    {
        rest_get_device_instance_id(DEVICE_INSTANCE_ID);
        if(!b_device_instance_id_initialized)
        {
            DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            return -1;
        }
    }
    snprintf(val, MDNS_KEY_VALUE_MAX_LEN, "%s", DEVICE_INSTANCE_ID);

    return 0;
}

// not sure yet
INT32 mdns_vizio_get_key_cid(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    if(GOOGLE_CAST_ID[0] != 0)
    {
        snprintf(val, MDNS_KEY_VALUE_MAX_LEN, "%s", GOOGLE_CAST_ID);
        return 0;
    }
    return -1;

    /*
    CHAR     ver_string[64]                 = {'0'};
    UINT32   ui4_cast_builder_name_len      = 64;
    INT32 ret = 0;

    if(!val || !plen)
    {
        return -1;
    }

    ret = a_c4tv_apron_get_cast_builder_name(ver_string,&ui4_cast_builder_name_len);
    if(ret)
    {
        return -1;
    }
    *plen = strlen(ver_string);
    memcpy((VOID*)val,ver_string,*plen);
    return 0;
*/
}
INT32 mdns_vizio_get_key_ccd(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    if(GOOGLE_CAST_CD[0] != 0)
    {
        snprintf(val, MDNS_KEY_VALUE_MAX_LEN, "%s", GOOGLE_CAST_CD);
        return 0;
    }
    return -1;
}
//get eth mac
INT32 mdns_vizio_get_key_eth(CHAR *val,UINT8 *plen)
{
    INT32 ret;
    UINT8 mac[6] = {0};
    CHAR tmp[16] = {0};
    INT32 i;

    if(!val || !plen)
    {
        return -1;
    }

    ret = c_net_ni_get_mac((CHAR*)NI_ETHERNET_0,(CHAR*)mac);
    if(ret)
    {
        return -1;
    }

    *plen = 12;
    val[0] = (mac[0] >> 4) & 0x0f;
    val[1] = (mac[0] >> 0) & 0x0f;

    val[2] = (mac[1] >> 4) & 0x0f;
    val[3] = (mac[1] >> 0) & 0x0f;

    val[4] = (mac[2] >> 4) & 0x0f;
    val[5] = (mac[2] >> 0) & 0x0f;

    val[6] = (mac[3] >> 4) & 0x0f;
    val[7] = (mac[3] >> 0) & 0x0f;

    val[8] = (mac[4] >> 4) & 0x0f;
    val[9] = (mac[4] >> 0) & 0x0f;

    val[10] = (mac[5] >> 4) & 0x0f;
    val[11] = (mac[5] >> 0) & 0x0f;

    for(i = 0;i < *plen;++i)
    {
        c_sprintf((CHAR*)(tmp+i),"%x",val[i]);
    }
    memcpy((VOID*)val,(VOID*)tmp,*plen);

    return ret;
}

//get wifi mac
INT32 mdns_vizio_get_key_wifi(CHAR *val,UINT8 *plen)
{
    INT32 ret;
    UINT8 mac[6] = {0};
    CHAR tmp[16] = {0};
    INT32 i;

    if(!val || !plen)
    {
        return -1;
    }
    ret = c_net_ni_get_mac((CHAR*)NI_WIRELESS_0,(CHAR*)mac);
    if(ret)
    {
        return -1;
    }

    *plen = 12;
    val[0] = (mac[0] >> 4) & 0x0f;
    val[1] = (mac[0] >> 0) & 0x0f;

    val[2] = (mac[1] >> 4) & 0x0f;
    val[3] = (mac[1] >> 0) & 0x0f;

    val[4] = (mac[2] >> 4) & 0x0f;
    val[5] = (mac[2] >> 0) & 0x0f;

    val[6] = (mac[3] >> 4) & 0x0f;
    val[7] = (mac[3] >> 0) & 0x0f;

    val[8] = (mac[4] >> 4) & 0x0f;
    val[9] = (mac[4] >> 0) & 0x0f;

    val[10] = (mac[5] >> 4) & 0x0f;
    val[11] = (mac[5] >> 0) & 0x0f;

    for(i = 0;i < *plen;++i)
    {
        c_sprintf((CHAR*)(tmp+i),"%x",val[i]);
    }
    memcpy((VOID*)val,(VOID*)tmp,*plen);

    return ret;
}

//get firmware version
INT32 mdns_vizio_get_key_fver(CHAR *val,UINT8 *plen)
{
    const CHAR* ver;
    if(!val || !plen)
    {
        return -1;
    }
    ver = sys_cust_get_usb_upg_version();
    if(ver == NULL)
    {
        return -1;
    }
    memcpy((VOID*)val,(VOID*)ver,strlen(ver));
    *plen = strlen(ver);

    /*ULI_PROJECT_STATUS_STRUCT    t_status;
    CHAR                         s_esn[48];
    CHAR                         s_qh[32];
    CHAR                         s_version[32];
    CHAR                         s_info[128];
    CHAR                         s_error[128];
    INT32                        i4_ret;

    if(!val || !plen)
    {
        return -1;
    }

    c_memset((VOID*)&t_status, 0, sizeof(ULI_PROJECT_STATUS_STRUCT));

    t_status.pszESN               = (INT8 *)s_esn;
    t_status.uiESNBufferLen       = sizeof(s_esn);
    t_status.pszQueryHost         = (INT8 *)s_qh;
    t_status.uiQueryHostBufferLen = sizeof(s_qh);
    t_status.pszVersion           = (INT8 *)s_version;
    t_status.uiVersionBufferLen   = sizeof(s_version);
    t_status.pszInfo              = (INT8 *)s_info;
    t_status.uiInfoBufferLen      = sizeof(s_info);
    t_status.pszLastError         = (INT8 *)s_error;
    t_status.uiLastErrorBufferLen = sizeof(s_error);

    i4_ret = a_uli_on_status_request(&t_status);

    if (ULIR_OK != i4_ret)
    {
        DBG_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_on_status_request() failed, %d\n", i4_ret));

        return CLIR_CMD_EXEC_ERROR;
    }*/

    return 0;
}

//get Prefix version of the V2SCP spec in which this device is compliant
INT32 mdns_vizio_get_key_rver(CHAR *val,UINT8 *plen)
{
    CHAR version[MDNS_VALUE_MAX_LEN] = {0};
    CHAR *pos;
    INT32 ret = 0;
    if(!val || !plen)
    {
        return -1;
    }
    ret = a_tv_rest_version(version);
    if(ret == 0)
    {
        *plen = strlen(version);
        if(*plen <= 0)
        {
            DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            return -1;
        }
        pos = strchr((const char*)version,'_');
        if(pos == NULL)
        {
            DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            return -1;
        }
        *plen = (UINT8)(pos - version);
        memcpy((VOID*)val,(VOID*)version,*plen);
    }

    return ret;
}

//Postfix version of the V2SCP spec defined by the REST API spreadsheet in which this device is compliant
INT32 mdns_vizio_get_key_mver(CHAR *val,UINT8 *plen)
{
    CHAR version[MDNS_VALUE_MAX_LEN] = {0};
    CHAR *pos;
    INT32 ret = 0;
    if(!val || !plen)
    {
        return -1;
    }
    ret = a_tv_rest_version(version);
    if(ret == 0)
    {
        *plen = strlen(version);
        if(*plen <= 0)
        {
            DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            return -1;
        }
        pos = strchr((const char*)version,'_');
        if(pos == NULL)
        {
            DBG_LOG_PRINT(("%d,%s,%s\n",__LINE__,__func__,__FILE__));
            return -1;
        }
        *plen = (UINT8)((version+*plen-1)-pos);
        memcpy((VOID*)val,(VOID*)(pos+1),*plen);
    }

    return ret;
}

//    Version of the Rest BLE spec in which this device compliant
INT32 mdns_vizio_get_key_bver(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    return a_uli_get_serial_number((UINT8*)val,(UINT32*)plen);
}

INT32 mdns_vizio_get_key_dt(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    *plen = 1;
    *val = '1';
    return 0;
}
INT32 mdns_vizio_get_key_pwr(CHAR *val,UINT8 *plen)
{
    UINT32   ui4_custom_status   = 0;
    INT32 ret;
    if(!val || !plen)
    {
        return -1;
    }
    *plen = 1;
    *val = 0;
    ret = a_bgm_get_custom_status(&ui4_custom_status);
    if(ui4_custom_status | BGM_CUSTOM_STATUS_BIT_ACTIVE_STANDBY)
    {
        *val = 3;
    }
    *val = '0' + *val;

    return ret;
}

INT32 mdns_vizio_get_key_oobe(CHAR *val,UINT8 *plen)
{
    BOOL b ;
    if(!val || !plen)
    {
        return -1;
    }
    *plen = 1;
    b = a_wzd_is_oobe_mode();
    *val = b + '0';
    return 0;
}
INT32 mdns_vizio_get_key_uli(CHAR *val,UINT8 *plen)
{
    UINT8 ui1_updating_status = 0;
    INT32 ret = 0;
    if(!val || !plen)
    {
        return -1;
    }
    *plen = 1;
#ifdef APP_ULI_UPG_SUPPORT
    ret = a_nav_updater_uli_get_updating_status(&ui1_updating_status);
#endif
    if(ret == 0)
    {
        if(ui1_updating_status == CHECK_STATE_NONE)
        {
            *val = '0' + 0;//no upgrade
        }
        else if(ui1_updating_status == CHECK_STATE_DOWNLOADING)
        {
            *val = '0' + 3;//downloading upgrade
        }
        else if(ui1_updating_status == CHECK_STATE_CHECK_INSTALLED)
        {
            *val = '0' + 6;//background upgrde available,waiting for user to tuner the TV off
        }
        else if(ui1_updating_status == CHECK_STATE_CHECK_INSTALLING)
        {
            *val = '0' + 9;//upgrading
        }
        else if(ui1_updating_status == CHECK_STATE_FW_INITED)
        {
            *val = 'C' ;//upgraded
        }
    }
    return ret;
}

INT32 mdns_vizio_get_key_tos(CHAR *val,UINT8 *plen)
{
    BOOL b ;
    if(!val || !plen)
    {
        return -1;
    }
    *plen = 1;
    b = a_tv_custom_get_tos();
    val[0] = b + '0';
    return 0;
}



//The Friendly name of the Vizio Cast device
INT32 mdns_vizio_get_key_name(CHAR *val,UINT8 *plen)
{
    INT32 ret;
    CHAR tv_name[MAX_TV_NAME_LEN] = {0};
    UINT32 tv_name_len = MAX_TV_NAME_LEN;

    if(!val || !plen)
    {
        return -1;
    }

    ret = a_cfg_custom_get_tv_name(tv_name,&tv_name_len);
    if(ret == 0)
    {
        tv_name_len = strlen(tv_name);
        *plen = (UINT8)tv_name_len;
        memcpy((VOID*)val,(VOID*)tv_name,tv_name_len);
        //c_strcat(val,"\"");
        //c_strcat(val,tv_name);
        //c_strcat(val,"\"");
    }

    return ret;
}

//get model name
INT32 mdns_vizio_get_key_mdl(CHAR *val,UINT8 *plen)
{
    INT32 ret = -1;
    if(!val || !plen)
    {
        return -1;
    }
    ret = a_cfg_custom_get_model_name(val);
    if(ret)
    {
        return -1;
    }
    *plen = strlen(val);
/*    ret = a_cfg_custom_get_model_name(model_name);
    if(ret == 0)
    {
        *plen = strlen(model_name);
        memcpy((VOID*)val,(VOID*)model_name,*plen);
    }
    */
    return ret;
}

//get soc,such as MTK
INT32 mdns_vizio_get_key_soc(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    *plen = strlen("MTK");
    strncpy((VOID*)val,"MTK",*plen);
    return 0;
}

INT32 mdns_vizio_get_key_dl(CHAR *val,UINT8 *plen)
{
    UINT16 ui2_indx=0;
    if(!val || !plen)
    {
        return -1;
    }
    ui2_indx = menu_custom_get_gui_lang_idx();
    val[0] = ui2_indx + '0';
    *plen = 1;
    return 0;
}

INT32 mdns_vizio_get_key_dc(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_US;
    a_cfg_custom_get_country_code(&t_country);
    val[0] = t_country + '0';
    *plen = 1;
    return 0;
}

INT32 mdns_vizio_get_key_ver(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    val[0] = '5';
    *plen = 1;
    return 0;
}

INT32 mdns_vizio_get_key_es(CHAR *val,UINT8 *plen)
{
    BOOL star;
    if(!val || !plen)
    {
        return -1;
    }
    star = a_cfg_get_energy_star();
    *plen = 1;
    *val = (CHAR)star + '0';

    /*
    ret = a_cfg_custom_get_drv_eco_mode(&ui4_eco);

    if(!ret)
    {
        *plen = 1;
        *val = (CHAR)ui4_eco + '0';
    }*/
    return 0;
}
INT32 mdns_vizio_get_key_hp(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    *plen = strlen(VIZIO_HTTP_PORT);
    memcpy((VOID*)val,(VOID*)VIZIO_HTTP_PORT,*plen);

    /*
    val[0] = (VIZIO_HTTP_PORT >> 8) & 0xff;
    val[1] = (VIZIO_HTTP_PORT >> 0) & 0xff;

    //c_sprintf(&val[0],"%x",73);
    //c_sprintf(&val[1],"%x",46);

    *plen = 2;
    */
    return 0;
}

INT32 mdns_vizio_get_key_hsp(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }

    *plen = strlen(VIZIO_HTTPS_PORT);
    memcpy((VOID*)val,(VOID*)VIZIO_HTTPS_PORT,*plen);

    /*
    val[0] = (VIZIO_HTTPS_PORT >> 8) & 0xff;
    val[1] = (VIZIO_HTTPS_PORT >> 0) & 0xff;
    //c_sprintf(&val[0],"%x",73);
    //c_sprintf(&val[1],"%x",45);

    *plen = 2;
    */
    return 0;
}
INT32 mdns_vizio_get_key_wp(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    *plen = strlen(VIZIO_WS_PORT);
    memcpy((VOID*)val,(VOID*)VIZIO_WS_PORT,*plen);

/*
    val[0] = (VIZIO_WS_PORT >> 8) & 0xff;
    val[1] = (VIZIO_WS_PORT >> 0) & 0xff;
    //c_sprintf(&val[0],"%x",73);
    //c_sprintf(&val[1],"%x",45);

    *plen = 2;
    */
    return 0;
}
INT32 mdns_vizio_get_key_wsp(CHAR *val,UINT8 *plen)
{
    if(!val || !plen)
    {
        return -1;
    }
    *plen = strlen(VIZIO_WSP_PORT);
    memcpy((VOID*)val,(VOID*)VIZIO_WSP_PORT,*plen);
/*
    val[0] = (VIZIO_WS_PORT >> 8) & 0xff;
    val[1] = (VIZIO_WS_PORT >> 0) & 0xff;
    //c_sprintf(&val[0],"%x",73);
    //c_sprintf(&val[1],"%x",45);

    *plen = 2;
    */
    return 0;
}


static INT32 mdns_create_recv_sock()
{
    INT32 sd;
    INT32 opt_val = 1;
    INT32 ret;
    struct sockaddr_in serveraddr;
    //struct ip_mreq mreq;

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        DBG_LOG_PRINT(("Create mDNS socket error! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return sd;
    }

    ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,(VOID*)&opt_val,sizeof(opt_val));
    if(ret < 0)
    {
        DBG_LOG_PRINT(("set socket opt fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        close(sd);
        return ret;
    }

    /* bind to an address */
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(MDNS_PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);    /* receive multicast */

    ret = bind(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret < 0)
    {
        close(sd);
        DBG_LOG_PRINT(("bind socket fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return ret;
    }

    // add membership to receiving socket
    #if 0
    memset(&mreq,I 0, sizeof(struct ip_mreq));
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    mreq.imr_multiaddr.s_addr = inet_addr(MDNS_ADDR);
    ret = setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mreq, sizeof(mreq));
    if (ret < 0)
    {
        close(sd);
        c_dbg_stmt("set socket opt fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return ret;
    }
    #endif

    // enable loopback in case someone else needs the data
    ret = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *) &opt_val, sizeof(opt_val));
    if (ret < 0)
    {
        close(sd);
        DBG_ERROR(("set socket opt fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return ret;
    }


#ifdef IP_PKTINFO
    ret = setsockopt(sd, SOL_IP, IP_PKTINFO, (char *) &opt_val, sizeof(opt_val));
    if (ret < 0)
    {
        close(sd);
        DBG_ERROR(("set socket opt fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return ret;
    }
#endif

    return sd;
}

static INT32 mdns_vizio_parse_google_cid(mdns_packet_t *pkt)
{
    UINT8 ui1_full_name_len = 0;
    UINT8 ui1_model_name_len = 0;
    UINT16 off = sizeof(UINT16)*6;//len of header
    CHAR full_name[MDNS_VALUE_MAX_LEN] = {0};
    CHAR model_name[MDNS_VALUE_MAX_LEN] = {0};

    if ((!pkt) || (!(pkt->buffer)))
    {
        return -1;
    }

    ui1_full_name_len =(*(UINT8*)((UINT32)pkt->buffer + off));
    memcpy((VOID*)full_name,(VOID*)((UINT32)pkt->buffer + off + 1),ui1_full_name_len);
    DBG_INFO(("[%s][%s] u4_get_cid_count:%d , full_name : %s.\r\n", __FILE__, __FUNCTION__, u4_get_cid_count, full_name));

    a_cfg_custom_get_model_name(model_name);
    DBG_INFO(("[%s][%s] model_name: %s .\r\n", __FILE__, __FUNCTION__, model_name));
    if(c_strstr(full_name, model_name) != NULL)//Jack Xu:GOOGLE_CAST_ID is sometimes incorrect.
    {
        ui1_model_name_len = strlen(model_name)+1;
        memcpy((VOID*)GOOGLE_CAST_ID,(VOID*)((UINT32)full_name+ui1_model_name_len),ui1_full_name_len-ui1_model_name_len);
        DBG_LOG_PRINT(("[%s][%s] GOOGLE_CAST_ID : %s.\r\n", __FILE__, __FUNCTION__, GOOGLE_CAST_ID));
    }

    u4_get_cid_count++;

    return 0;
}

static INT32 mdns_vizio_parse_google_ccd(mdns_packet_t *pkt)
{
    UINT8 ui1_full_name_len = 0;
    UINT8 ui1_model_name_len = 0;
    UINT16 off = sizeof(UINT16)*6;//len of header
    CHAR model_name[MDNS_VALUE_MAX_LEN] = {0};
    CHAR pkt_md[MDNS_VALUE_MAX_LEN] = {0};
    char *p_buf = NULL;
    int id_start = 0;
    int cd_start = 0;
    int rm_start = 0;
    int md_start = 0;

    if (pkt == NULL)
    {
        return -1;
    }
    p_buf = pkt->buffer + off + 1;

    for(int i = 0; i < pkt->u2PktSize; ++i)
    {
#if 0
        // dump packet
        if ('\0' == *(p_buf + i))
        {
            //printf("(null)");
        }
        else
        {
            printf("%c", *(p_buf + i));
        }
#endif
        if (('i' == *(p_buf + i)) && ('d' == *(p_buf + i + 1)) && ('=' == *(p_buf + i + 2)))
        {
            id_start = i;
        }
        else if (('#' == *(p_buf + i)) && ('c' == *(p_buf + i + 1)) && ('d' == *(p_buf + i + 2)) && ('=' == *(p_buf + i + 3)))
        {
            cd_start = i;
        }
        else if (('r' == *(p_buf + i)) && ('m' == *(p_buf + i + 1)) && ('=' == *(p_buf + i + 2)))
        {
            rm_start = i;
        }
        else if (('m' == *(p_buf + i)) && ('d' == *(p_buf + i + 1)) && ('=' == *(p_buf + i + 2)))
        {
            md_start = i;
        }
    }

    if ((id_start == 0) || (cd_start == 0) || (rm_start == 0) || (md_start == 0))
    {
        return -1;
    }

    a_cfg_custom_get_model_name(model_name);
    ui1_model_name_len = strlen(model_name)+1;
    memcpy((VOID*)pkt_md,(VOID*)((UINT32)p_buf + md_start + 3), ui1_model_name_len);
    if (c_strstr(pkt_md, model_name) == NULL)
    {
        return -1;
    }

    int len = rm_start - cd_start - 4 - 1;
    if (len < MDNS_VALUE_MAX_LEN)
    {
        memcpy((VOID*)GOOGLE_CAST_CD,(VOID*)((UINT32)p_buf + cd_start + 4), len);
        DBG_LOG_PRINT(("[%s][%s] GOOGLE_CAST_CD : %s.\r\n", __FILE__, __FUNCTION__, GOOGLE_CAST_CD));
    }
    else
    {
        DBG_ERROR(("[%s][%s] Get GOOGLE_CAST_CD fail\n", __FILE__, __FUNCTION__));
        return -1;
    }

    len = cd_start - id_start - 3;
    if (len < MDNS_VALUE_MAX_LEN)
    {
        memcpy((VOID*)GOOGLE_CAST_ID,(VOID*)((UINT32)p_buf + id_start + 3), len);
        DBG_LOG_PRINT(("[%s][%s] GOOGLE_CAST_ID : %s.\r\n", __FILE__, __FUNCTION__, GOOGLE_CAST_ID));
    }
    else
    {
        DBG_ERROR(("[%s][%s] Get GOOGLE_CAST_ID fail\n", __FILE__, __FUNCTION__));
        return -1;
    }

    return 0;
}

INT32 mdns_vizio_probe_change_name(void)
{
    CHAR c = '0';
    UINT8 len = strlen(VIZIO_CAST_NAME);
    if(len == 63)
    {
        len -= 1;
    }
    pthread_mutex_lock(&gVizioMdnsServer.dataLock);
    VIZIO_CAST_NAME[len] = c + gVizioMdnsServer.i4NameConflictCount;
    pthread_mutex_unlock(&gVizioMdnsServer.dataLock);
    a_cfg_custom_set_tv_name(VIZIO_CAST_NAME);
    return 0;
}


INT32 a_mdns_get_google_cast_id(CHAR * val)
{
    if(!val)
    {
        DBG_ERROR(("val is NULL! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return MDNS_FAIL_PARA;
    }
    strncpy(val, GOOGLE_CAST_ID, strlen(GOOGLE_CAST_ID));
    return 0;
}

INT32 a_mdns_get_google_cast_cd(CHAR * val)
{
    if(!val)
    {
        DBG_ERROR(("val is NULL! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return MDNS_FAIL_PARA;
    }
    strncpy(val, GOOGLE_CAST_CD, strlen(GOOGLE_CAST_CD));
    return 0;
}

static pid_t mdns_vizio_exec_dns_sd(BOOL b_is_kill)
{
    if(b_is_kill)
    {
        if(dns_sd_pid > 0 && kill(dns_sd_pid, 0) == 0)
        {
            DBG_LOG_PRINT(("[%s %d] kill 9 dns-sd.\n", __FUNCTION__, __LINE__));
            kill(dns_sd_pid, 9);
        }
    }

    {
        /* Check mdnsd */
        FILE *fp = fopen(MDNSD_PID_FILE, "r");
        if(fp != NULL) {
           fscanf(fp, "%d", &mdnsd_pid);
           fclose(fp);
        }
        DBG_LOG_PRINT(("[%s %d] mdns PID = %d.\n", __FUNCTION__, __LINE__, mdnsd_pid));
        if (kill(mdnsd_pid, 0))
        {
            DBG_LOG_PRINT(("[%s %d] mdns daemon doesn't exist!!\n", __FUNCTION__, __LINE__));
            return 0;
        }
        else
        {
            DBG_LOG_PRINT(("[%s %d] mdns daemon already exist!!\n", __FUNCTION__, __LINE__));
        }
    }

    INT32 i = 0;
    INT32 ret = 0;
    char VizioCastName[ARG_NUM] = {0};
    UINT32 nCastNameLen = ARG_NUM;
    a_cfg_custom_get_cast_name((CHAR*)VizioCastName, &nCastNameLen);

    pc_argv[0] = "dns-sd";
    pc_argv[1] = "-R";
    pc_argv[2] = VizioCastName;
    pc_argv[3] = "_viziocast._tcp";
    pc_argv[4] = "local";
    pc_argv[5] = "7345";
    INT32 count = sizeof(gVizioKeyVal)/sizeof(mdns_key_val_t);
    INT32 nIndex = 6;
    INT32 nIndex_tmp = 0;

    for(i = 0; i < count; i++)
    {
        UINT8 len = 0;
        CHAR val[MDNS_KEY_VALUE_MAX_LEN] = {0};
        if(gVizioKeyVal[i].get_val != NULL)
        {
            get_key_val fun_get_val = gVizioKeyVal[i].get_val;
            ret = fun_get_val(val,&len);

            if(ret == 0)
            {
                memset(pc_argv_tmp[nIndex_tmp], 0 , ARG_LEN_MAX);
                strcat(pc_argv_tmp[nIndex_tmp], gVizioKeyVal[i].key_name);
                strcat(pc_argv_tmp[nIndex_tmp], val);
                pc_argv[nIndex] = pc_argv_tmp[nIndex_tmp];
                nIndex++;
                nIndex_tmp++;
            }
        }
    }
    pc_argv[nIndex] = NULL;

    // Here create process dns-sd to register _viziocast._tcp
    pid_t my_pid = 0;

    my_pid = fork();
    // Do not call acfg, or add print here, see below.
    if( my_pid < 0) {
        DBG_LOG_PRINT(("[%s %d] Something wrong, fork() return [%d]\n", __func__, __LINE__, my_pid));
    } else if ( my_pid == 0) {
        // Do not call acfg, or add print in the child process, this may cause dead lock.
        // There are multiple threads running on the parent process,
        // when fork from the parent, a lock may be in locking state however child process has
        // just one thread, causing dead lock.
        execv("/bin/dns-sd", pc_argv);
    } else {
        // TODO: Missing waitpid that will cause zombie process.
        usleep(5000 * 1000);
        is_mdns_registered = 1;
        DBG_LOG_PRINT(("[%s %d] My pid[%d], fork() return[%d].\n", __func__, __LINE__, getpid(), my_pid));
    }
    return my_pid;
}

static void _mdns_main_loop(vizio_mdns_server_t *svr)
{
    fd_set sockfd_set;
    INT32 ret;
    int max_fd = svr->i4SockFd + 1;

    svr->pkt.buffer = (UINT8*)c_mem_alloc(MDNS_PACKET_MAX_SIZE);
    if(svr->pkt.buffer == NULL)
    {
        DBG_ERROR(("Alloc packet buffer fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return;
    }

    while(!is_mdns_stop) // This loop monitor local cast_shell to get google cast id
    {
        if(svr->pkt.buffer == NULL)
        {
            DBG_LOG_PRINT(("pkt.buffer is NULL, line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
            break;
        }
        memset(svr->pkt.buffer,0,MDNS_PACKET_MAX_SIZE);

        FD_ZERO(&sockfd_set);
        FD_SET(svr->i4SockFd, &sockfd_set);
        select(max_fd, &sockfd_set, NULL, NULL, NULL);

        if (FD_ISSET(svr->i4SockFd, &sockfd_set))
        {
            struct sockaddr_in fromaddr;
            socklen_t sockaddr_size = sizeof(struct sockaddr_in);
            ssize_t recvsize;
            //add lock here?

            recvsize = recvfrom(svr->i4SockFd, svr->pkt.buffer, MDNS_PACKET_MAX_SIZE, 0, (struct sockaddr *) &fromaddr, &sockaddr_size);

            if (is_mdns_stop)
            {
                DBG_LOG_PRINT(("[%s][%d] break loop\n", __FUNCTION__, __LINE__));
                break;
            }

            if (recvsize < 0)
            {
                DBG_ERROR(("recv fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
                //unlock here
                continue;
            }
            svr->pkt.u2PktSize = recvsize;

            if(GOOGLE_CAST_CD[0] == 0)
            {
                mdns_vizio_parse_google_ccd(&svr->pkt);
            }

            if(DEVICE_INSTANCE_ID[0] == 0)
            {
                ret = rest_get_device_instance_id(DEVICE_INSTANCE_ID);
                if(ret == 0)
                {
                    DBG_LOG_PRINT(("[%s][%s] DEVICE_INSTANCE_ID : %s. Run dns-sd.\r\n", __FILE__, __FUNCTION__, DEVICE_INSTANCE_ID));
                    dns_sd_pid = mdns_vizio_exec_dns_sd(TRUE);
                }
                else
                {
                    DBG_ERROR(("[%s][%s] Get DEVICE_INSTANCE_ID fail, ret = %d\n", __FILE__, __FUNCTION__, ret));
                }
            }

            u4_from_addr = ntohl((UINT32)fromaddr.sin_addr.s_addr);
            //DBG_LOG_PRINT(("[%s][%d] client IP: %s , Port: %d.\n", __FUNCTION__,__LINE__, inet_ntoa(fromaddr.sin_addr), htons(fromaddr.sin_port)));
            if(u4_host_addr == 0)
            {
                NW_IP_INFO_T    t_net_ip_info;
                c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));
                a_nw_get_crnt_ip_info(&t_net_ip_info);
                u4_host_addr = ntohl(t_net_ip_info.ui4_address);
            }

            if(GOOGLE_CAST_ID[0] == 0 && dns_sd_pid == 0 && u4_get_cid_count >= 5)
            {
                dns_sd_pid = mdns_vizio_exec_dns_sd(FALSE);
            }

            if(GOOGLE_CAST_ID[0] == 0 && u4_host_addr == u4_from_addr)
            {
                mdns_vizio_parse_google_cid(&svr->pkt);
            }
            else if((GOOGLE_CAST_ID[0] != 0) && (strlen(DEVICE_INSTANCE_ID) != 0))
            {
                dns_sd_pid = mdns_vizio_exec_dns_sd(TRUE);
                DBG_LOG_PRINT(("[%s][%d] Exit thread of rest mdns ......\n", __FUNCTION__,__LINE__));
                break;
            }
        }
    }
    //DBG_LOG_PRINT(("[%s][%d] stop mdns_main_loop\n", __FUNCTION__,__LINE__));
    c_mem_free(svr->pkt.buffer);
    svr->pkt.buffer = NULL;
    u4_get_cid_count = 0;
    pthread_mutex_destroy(&(svr->dataLock));
    close(svr->i4SockFd);
    pthread_exit(NULL);

    return;
}

INT32 mdns_vizio_service_register(void)
{
    pthread_attr_t attr;

    if(gVizioMdnsServer.bInit)
    {
        return MDNS_FAIL_INIT;
    }
    memset(&gVizioMdnsServer,0,sizeof(vizio_mdns_server_t));

    gVizioMdnsServer.i4SockFd = mdns_create_recv_sock();
    if (gVizioMdnsServer.i4SockFd < 0)
    {
        DBG_ERROR(("Create mDNS socket error! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__));
        return MDNS_FAIL_SOCK;
    }


    // init thread
    pthread_mutex_init(&gVizioMdnsServer.dataLock, NULL);
    pthread_attr_init(&attr);
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&gVizioMdnsServer.tid, &attr,(start_routine)_mdns_main_loop,(void*)&gVizioMdnsServer) != 0)
    {
        pthread_mutex_destroy(&gVizioMdnsServer.dataLock);
        pthread_attr_destroy(&attr);
        close(gVizioMdnsServer.i4SockFd);
        return MDNS_FAIL_THREAD;
    }
    pthread_attr_destroy(&attr);
    gVizioMdnsServer.bInit = TRUE;

    return 0;
}

INT32 a_mdns_stop(void)
{
    is_mdns_stop = 1;
    is_mdns_registered = 0;

    if(dns_sd_pid > 0 && kill(dns_sd_pid, 0) == 0)
    {
        DBG_LOG_PRINT(("[%s %d] kill 9 dns-sd.\n", __FUNCTION__, __LINE__));
        kill(dns_sd_pid, 9);
        dns_sd_pid = 0;
    }

    if (gVizioMdnsServer.bInit)
    {
        DBG_LOG_PRINT(("[%s %d] Waiting _mdns_main_loop finished\n", __func__, __LINE__));
        shutdown(gVizioMdnsServer.i4SockFd, SHUT_RD); // in order to unblock recvfrom
        pthread_join(gVizioMdnsServer.tid, NULL);
        gVizioMdnsServer.bInit = FALSE;
    }

    return 0;
}

INT32 a_mdns_start(void)
{
    if (is_mdns_registered == 1) return 0;
    is_mdns_stop = 0;
    return mdns_vizio_service_register();
}

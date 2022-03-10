/*-------------------------------------------------------------------------
    
-------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*
 * No Warranty                                                                *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MTK with respect to any MTK *
 * Deliverables or any use thereof, and MTK Deliverables are provided on an   *
 * "AS IS" basis.  MTK hereby expressly disclaims all such warranties,        *
 * including any implied warranties of merchantability, non-infringement and  *
 * fitness for a particular purpose and any warranties arising out of course  *
 * of performance, course of dealing or usage of trade.  Parties further      *
 * acknowledge that Company may, either presently and/or in the future,       *
 * instruct MTK to assist it in the development and the implementation, in    *
 * accordance with Company's designs, of certain softwares relating to        *
 * Company's product(s) (the "Services").  Except as may be otherwise agreed  *
 * to in writing, no warranties of any kind, whether express or implied, are  *
 * given by MTK with respect to the Services provided, and the Services are   *
 * provided on an "AS IS" basis.  Company further acknowledges that the       *
 * Services may contain errors, that testing is important and Company is      *
 * solely responsible for fully testing the Services and/or derivatives       *
 * thereof before they are used, sublicensed or distributed.  Should there be *
 * any third party action brought against MTK, arising out of or relating to  *
 * the Services, Company agree to fully indemnify and hold MTK harmless.      *
 * If the parties mutually agree to enter into or continue a business         *
 * relationship or other arrangement, the terms and conditions set forth      *
 * hereunder shall remain effective and, unless explicitly stated otherwise,  *
 * shall prevail in the event of a conflict in the terms in any agreements    *
 * entered into between the parties.                                          *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Copyright (c) 2004, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 * $RCSfile: wfd_p2p_conn.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "wfd_p2p_conn.h"
#include "wfd_dev_list.h"
#include "c_net_p2p_ctl.h"
#ifdef APP_MENU_WFD_COEXIST
#include "menu2/a_menu.h"
#endif

#include "mmp/a_mmp.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "res/app_util/config/acfg_custom.h"
#include "wfrrc_interface.h"

#include "app_util/a_network.h"
#include "u_net_ni_if.h"

#include "res/app_util/config/acfg_cust_odm.h"

#ifndef APP_MIRACAST_AGEOUT
#define APP_MIRACAST_AGEOUT (100)
#endif

static BOOL b_g_p2p_open_connection = FALSE;
WFD_P2P_INFO_T t_g_wfd_p2p_info;

BOOL b_g_resume_wfd_directly = FALSE;
extern INT32  a_nw_get_mac_addr(CHAR *psz_name,UINT8 *pMacAddr);
static void _wfd_client_p2p_nfy(int notifyId,void * param);

static VOID _passphrase_hash(UINT8* pui1_input, CHAR* ps_output)
{
    UINT8 i, ui1_num_1 = 0, ui1_num_2 = 0;

    if((ps_output == NULL) || (pui1_input == NULL))
    {
        DBG_LOG_PRINT(("_passphrase_hash: input array null pointer\n"));
        return;
    }

    pui1_input++; // discard the prefix of MAC address, always "00"

    for (i = 0; i < 4; i++)
    {
        //DBG_LOG_PRINT(("_passphrase_hash: %d turn: pui1_input = %d\n", (i+1), *pui1_input));
        ui1_num_1 = *pui1_input % 10;
        ui1_num_2 = (*pui1_input / 10) % 10;
        ps_output[i*2] = ui1_num_1 + '0';
        ps_output[i*2 + 1] = ui1_num_2 + '0';
        pui1_input++;
    }

}

/*This API is to export for register callback function in earlier stage*/
VOID wfd_p2p_reg_client_cb(VOID)
{
    wfd_client_reg_callback( _wfd_client_p2p_nfy);
}

INT32 wfd_p2p_init(VOID)
{
    c_memset(&t_g_wfd_p2p_info, 0, sizeof(WFD_P2P_INFO_T));
    t_g_wfd_p2p_info.b_is_start = FALSE;
    t_g_wfd_p2p_info.b_set_force_go= TRUE;
    t_g_wfd_p2p_info.b_is_go= FALSE;
    t_g_wfd_p2p_info.b_set_miracast= TRUE;
    c_sprintf (t_g_wfd_p2p_info.interface_name,"p2p0");
    return WFDR_OK;
}

BOOL wfd_p2p_get_auto_conn_status(VOID)
{
    return t_g_wfd_p2p_info.b_is_auto_conn;
}

void wfd_p2p_set_auto_conn_status(BOOL b_status)
{
    t_g_wfd_p2p_info.b_is_auto_conn = b_status;
}

void wfd_p2p_enable_auto_conn_by_device(WFD_MSG_T e_msg, VOID * param)
{
    CHAR    s_app_name[APP_NAME_MAX_LEN+1] = {'\0'};
    INT32   i4_ret = 0;

    /* check whether WFD app resume, if YES, then return directly and run normal flow; otherwise, run the below flow */
    i4_ret = a_am_get_active_app(s_app_name);
    if (i4_ret == AMBR_OK && c_strcmp(s_app_name, WFD_NAME) == 0)
    {
        return;
    }
    #ifdef APP_MENU_WFD_COEXIST
    if(i4_ret == AMBR_OK && 
       c_strcmp(s_app_name, MENU_NAME) == 0 && 
       wfd_app_get_wfd_cond() == WFD_COND_PAUSED_WAIT_SVC)
    {
        return;
    }
    #endif
    
    /* get & check device info, if the device is a paired device and exist at Flash, continue; otherwise, return directly */
    if(NULL != t_g_wfd_p2p_info.p_request_connect_mac)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
    }

    if(FALSE == a_wfd_device_info_is_device_register(t_g_wfd_p2p_info.p_request_connect_mac, DEVICE_INFO_ARR_LEN))
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return;
    }

    /* check the current status of TV, such as which source, which app resume, or 3rd already run now */
    //TO DO

    /* resume WFD app */
    wfd_app_amb_resume();

    /* send message */
    if(WFD_MSG_P2P_NEG_REQ!=e_msg)//no need to accept request pcb notify.
    {
        wfd_main_send_msg_to_view(e_msg, param);
    }

    /* set status */
    wfd_p2p_set_auto_conn_status(TRUE);
}


INT32 wfd_p2p_assign_VIZIO_param_for_forceGO(CHAR* s_ssid, CHAR* s_psk)
{
    CHAR   s_num[6] = {0};
    UINT8  ui1_str[6] = {0};
    CHAR  s_hash[10] = {0};
    UINT16  ui2_num = 0;

    if ((s_ssid == NULL) || (s_psk == NULL))
    {
       DBG_LOG_PRINT(("%s,%s,%d, s_ssid or s_psk is null pointer\n",__FILE__, __FUNCTION__, __LINE__));
       return WFDR_FAIL;
    }

    a_nw_get_mac_addr(NI_WIRELESS_0, ui1_str);
    ui2_num = (UINT16)(ui1_str[3] + ui1_str[4] + ui1_str[5]);
    s_num[0] = ((ui2_num / 26) % 26) + 'A';
    s_num[1] = (ui2_num % 26) + 'A';
    s_num[2] = '\0';
    _passphrase_hash(ui1_str, s_hash);
    c_strcpy(s_psk, s_hash);
    c_strcpy(s_ssid, "DIRECT-");
    c_strcat(s_ssid, s_num);   
    c_strcat(s_ssid, "-VIZIOTV");
    DBG_LOG_PRINT(("%s,%s,%d, ra0 MAC=%02X:%02X:%02X:%02X:%02X:%02X, s_ssid=%s\n",
                       __FILE__, __FUNCTION__, __LINE__,
                       ui1_str[0], ui1_str[1], ui1_str[2], ui1_str[3], ui1_str[4], ui1_str[5], s_ssid));
    return WFDR_OK;
}


INT32 wfd_p2p_enable_wifi_display(VOID)
{
    if(t_g_wfd_p2p_info.b_is_start)
    {
        return WFDR_OK;
    }
    if(wfd_client_get_p2p_init_state() == 0 )
    {
//      if(wfd_client_get_miracast_mode() != 0)
//        {
//            WFD_SEND_RETRY_TYPE_T       e_retry_type = WFD_SEND_RETRY_TYPE_ONCE;
//            wfd_event_handler           pf_event_handler =  wfd_main_handle_msg;
//            VOID*                       pv_param1 = (VOID *)(UINT32)WFD_MSG_DIRECT_ON;
//            VOID*                       pv_param2 = NULL;
//            VOID*                       pv_param3 = NULL;
//            VOID*                       pv_param4 = NULL;
//            wfd_event_send_context(e_retry_type,pf_event_handler, pv_param1, pv_param2, pv_param3, pv_param4);
//          return WFDR_OK;
//        }
//      else
//      {

            WFD_SEND_RETRY_TYPE_T       e_retry_type = WFD_SEND_RETRY_TYPE_ONCE;
            wfd_event_handler           pf_event_handler =  wfd_main_handle_msg;
            VOID*                       pv_param1 = (VOID *)(UINT32)WFD_MSG_P2P_ENABLE_OK;
            VOID*                       pv_param2 = NULL;
            VOID*                       pv_param3 = NULL;
            VOID*                       pv_param4 = NULL;

            t_g_wfd_p2p_info.b_is_start = TRUE;
            wfd_client_reg_callback( _wfd_client_p2p_nfy);
            if(t_g_wfd_p2p_info.b_set_miracast && (wfd_client_get_miracast_mode() != 0))
            {
                wfd_p2p_enable_miracast();
            }

            wfd_event_send_context(e_retry_type,pf_event_handler, pv_param1, pv_param2, pv_param3, pv_param4);
            return WFDR_OK;
//      }
    }
    INT32 i4_ret = wfd_client_start(_wfd_client_p2p_nfy);
    if(i4_ret < 0)
    {
        return WFDR_FAIL;
    }
    return WFDR_OK;
}

INT32 wfd_p2p_disable_wifi_display(VOID)
{    
    if(!t_g_wfd_p2p_info.b_is_start)
    {
        return WFDR_OK;
    }
    
    t_g_wfd_p2p_info.b_is_start = FALSE;
    wfd_client_unreg_callback(_wfd_client_p2p_nfy);

    //wfd_client_stopfind();

    if(t_g_wfd_p2p_info.b_set_force_go)
    {
        wfd_p2p_disable_force_go();
    }
    wfd_client_clear_device_list();

 //   usleep(1000000);
    if(t_g_wfd_p2p_info.b_is_go)
    {
        c_net_wlan_stop_p2p_dhcpd_sever();
        t_g_wfd_p2p_info.b_is_go = FALSE;
    }
    else
    {
        c_net_p2p_stop_dhcpc(t_g_wfd_p2p_info.interface_name);
    }


    if(t_g_wfd_p2p_info.b_set_miracast)
    {
        wfd_p2p_disable_miracast();
    }

    t_g_wfd_p2p_info.b_is_go = FALSE;
    if(wfd_client_stop() == 0)
    {
        return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_get_devicenumber(VOID)
{ 
    INT32 i4_ret = wfd_client_get_deviceNumber();
    if(i4_ret < 0)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }   
    return i4_ret;
}

INT32 wfd_p2p_get_wfdDevType(INT32 index)
{   
    return wfd_client_get_wfdDevType(wfd_client_get_deviceMac(index));
}

INT32 wfd_p2p_get_rssi(INT32 index)
{
    return wfd_client_get_rssi(wfd_client_get_deviceMac(index));
}

INT32 wfd_p2p_get_device_info(WFD_DEV_INFO_TYPE_T e_type,void* pv_param,INT32 index)
{
   char* ps_src = NULL;
    
    switch(e_type)
    {
        case WFD_DEV_NAME:
        {
            char* ps_name = (char*)pv_param;
             ps_src =  (char *)wfd_client_get_deviceName(wfd_client_get_deviceMac(index));
             if(ps_src == NULL)
             {
                 return WFDR_FAIL;
             }
            c_strncpy(ps_name,ps_src,DEVICE_INFO_ARR_LEN);
            break;
        }
        case WFD_DEV_MAC:
        {
            char* ps_mac = (char*)pv_param;
            ps_src =  (char *)wfd_client_get_deviceMac((int)index);
            if(ps_src == NULL)
            {
                return WFDR_FAIL;
            }
            c_strncpy(ps_mac,ps_src,DEVICE_INFO_ARR_LEN);
            break;
        }
        case WFD_DEV_TYPE:
        {
            char* ps_type = (char*)pv_param;
            ps_src = (char *) wfd_client_get_deviceType(wfd_client_get_deviceMac(index));
            if(ps_src == NULL)
            {
                return WFDR_FAIL;
            }
            c_strncpy(ps_type,ps_src,DEVICE_INFO_ARR_LEN);
            break;
        }
        case WFD_DEV_PORT:
        {
            UINT32* pui4_port = (UINT32*)pv_param;
            *pui4_port =  wfd_client_get_rtspPort(wfd_client_get_deviceMac(index));
            if(*pui4_port < 0)
            {
                return WFDR_FAIL;
            }
            break;
        }
       case WFD_DEV_ALL:

       {
            WFD_DEVICE_INFO_T* pt_device = (WFD_DEVICE_INFO_T*)pv_param;
            ps_src = (char *) wfd_client_get_deviceMac((int)index);
            if(ps_src == NULL)
            {
                return WFDR_FAIL;
            }
            c_strncpy(pt_device->ps_device_mac,ps_src,DEVICE_INFO_ARR_LEN);
            
            ps_src = (char *) wfd_client_get_device_info_str(pt_device->ps_device_mac, DEVICE_INFO_STR_NAME);
            if(ps_src == NULL)
            {
                return WFDR_FAIL;
            }
            c_strncpy(pt_device->ps_device_name,ps_src,DEVICE_INFO_ARR_LEN);

            ps_src = (char *) wfd_client_get_device_info_str(pt_device->ps_device_mac, DEVICE_INFO_STR_TYPE);
            if(ps_src == NULL)
            {
                return WFDR_FAIL;
            }
            c_strncpy(pt_device->ps_device_type,ps_src,DEVICE_INFO_ARR_LEN);
            
            pt_device->i4_device_port =  wfd_client_get_rtspPort(pt_device->ps_device_mac);
            if(pt_device->i4_device_port < 0)
            {
                return WFDR_FAIL;
            }
            
            INT32 i4_isconn = 0;
            i4_isconn = wfd_client_is_connected(pt_device->ps_device_mac);
            if(i4_isconn == 1)
                pt_device->b_connect = TRUE;
            else
                pt_device->b_connect = FALSE;
            
            break; 
       }
       default:
            break;
     }
    
    return WFDR_OK;
}

INT32 wfd_p2p_connect_pbc(INT32 index)
{
    if(!t_g_wfd_p2p_info.b_is_start)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }


    const char* temp = NULL;
    temp = wfd_client_get_deviceMac(index);
    if(!temp)
        return WFDR_FAIL;

    if(wfd_client_get_is_wfd_device(temp)!=0)
    {
        return WFDR_FAIL;
    }
    
    c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
    c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,temp,DEVICE_INFO_ARR_LEN);
    if(t_g_wfd_p2p_info.b_set_force_go)
    {
        if (wfd_client_connect_invite(NULL, NULL, t_g_wfd_p2p_info.p_wait_connect_mac) == 0)
        {
            return WFDR_OK;
        }
        else
        {
            DBG_LOG_PRINT(("\n%s,%s,%d\n",
                        __FILE__, __FUNCTION__, __LINE__));
            return WFDR_FAIL;
        }
    }
    else
    {
        if (wfd_client_connect(WFD_CONNECT_PBC, t_g_wfd_p2p_info.p_wait_connect_mac, NULL) == 0)
        {
            return WFDR_OK;
        }
        else
        {
            DBG_LOG_PRINT(("\n%s,%s,%d\n",
                        __FILE__, __FUNCTION__, __LINE__));
            return WFDR_FAIL;
        }
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;        
}

INT32 wfd_p2p_forced_GO_connect_pbc(INT32 index)
{
    if(!t_g_wfd_p2p_info.b_is_start)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    const char* temp = NULL;
     temp = wfd_client_get_deviceMac(index);
     if(!temp)
         return WFDR_FAIL;

     c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
     c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,temp,DEVICE_INFO_ARR_LEN);
    if (wfd_client_connect(WFD_CONNECT_PBC_FORCE_GO,t_g_wfd_p2p_info.p_wait_connect_mac , NULL) == 0)
    {
        return WFDR_OK;
    }
    else
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL; 
}


//call enter pin before
INT32 wfd_p2p_connect_pin(INT32 index)
{    
    if(t_g_wfd_p2p_info.b_set_force_go)
    {
        return wfd_p2p_forced_GO_connect_pin(index);
    }

    if(!t_g_wfd_p2p_info.b_is_start)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    const char* temp = NULL;
    temp = wfd_client_get_deviceMac(index);
    if(!temp)
        return WFDR_FAIL;

    c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
    c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,temp,DEVICE_INFO_ARR_LEN);

   if (wfd_client_connect(WFD_CONNECT_PIN, t_g_wfd_p2p_info.p_wait_connect_mac,t_g_wfd_p2p_info.pin_for_enter) == 0)
    {
        return WFDR_OK;
    }
    else
    {
        WFD_DBG_LOG_EX("conn pin fail",index);
        return WFDR_FAIL;
    }
    WFD_DBG_LOG_EX("conn pin fail",index);
    return WFDR_FAIL;        
}
//call enter pin before
INT32 wfd_p2p_forced_GO_connect_pin(INT32 index)
{
    if(!t_g_wfd_p2p_info.b_is_start)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    const char* temp = NULL;
    temp = wfd_client_get_deviceMac(index);
    if(!temp)
        return WFDR_FAIL;

    c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
    c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,temp,DEVICE_INFO_ARR_LEN);
    if (wfd_client_connect(WFD_CONNECT_PIN_FORCE_GO, t_g_wfd_p2p_info.p_wait_connect_mac,t_g_wfd_p2p_info.pin_for_enter) == 0)
    {
        return WFDR_OK;
    }
    else
    {
        WFD_DBG_LOG_EX("force GO conn pin fail",index);
        return WFDR_FAIL;
    }
    WFD_DBG_LOG_EX("force GO conn pin fail",index);
    return WFDR_FAIL; 
}

// force go mode will no use(wfd_client_disconnect_all)
INT32 wfd_p2p_disconnect(VOID)
{
    if( t_g_wfd_p2p_info.b_set_force_go)
    {
       return wfd_p2p_disconnect_device(t_g_wfd_p2p_info.p_connect_mac);
    }
    else
    {
       if (wfd_client_disconnect_all() == 0)
       {
          return WFDR_OK;
       }
       DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
    }
       return WFDR_FAIL;
}

INT32 wfd_p2p_connect_cancel(VOID)
{
//wait enhance
    c_net_wlan_p2p_wpsCancel();
    return WFDR_OK;

}

INT32 wfd_p2p_disconnect_device(const char* mac)
{
       if (wfd_client_disconnect_device(mac) == 0)
       {
          return WFDR_OK;
       }
       DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
       return WFDR_FAIL;
}

//ok - connect fail false
INT32 wfd_p2p_is_connected(INT32 index)
{
    if (wfd_client_is_connected(wfd_client_get_deviceMac(index)) == 1)
    {
       return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_find(VOID)
{     
    if(!t_g_wfd_p2p_info.b_is_start)
      {
          DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
          return WFDR_OK;
      }
    WFD_DBG_LOG(1);
    if (wfd_client_find() == 0)
    {
       return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_stop_find(VOID)
{
    if (wfd_client_stopfind() == 0)
    {
       return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}
// if get  get event IP_GET
INT32 wfd_p2p_try_to_find_ip(VOID)
{
    if (wfd_client_get_other_ip(t_g_wfd_p2p_info.p_connect_mac) == 0)
    {
       return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_pin_display_accept(VOID)
{
    c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
    c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,t_g_wfd_p2p_info.p_request_connect_mac,DEVICE_INFO_ARR_LEN);

    if (wfd_client_connect(WFD_CONNECT_PIN_DISPLAY_ACCEPT,NULL,NULL) == 0)
    {
       return WFDR_OK;
    }

    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_pbc_request_accept(VOID)
{
    const char* mac= NULL;
    mac = t_g_wfd_p2p_info.p_request_connect_mac;
    DBG_LOG_PRINT(("\n%s,%s,%d,mac=%s\n",
                __FILE__, __FUNCTION__, __LINE__, mac));
    c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
    c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,t_g_wfd_p2p_info.p_request_connect_mac,DEVICE_INFO_ARR_LEN);
    if(t_g_wfd_p2p_info.b_set_force_go)
    {
        if  (wfd_client_connect(WFD_CONNECT_PBC_FORCE_GO,NULL,NULL) == 0)
        {
           return WFDR_OK;
        }
    }
    else
    {
    if  (wfd_client_connect(WFD_CONNECT_PBC_REQ_ACCEPT,mac,NULL) == 0)
    {
       return WFDR_OK;
    }
    }

    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_get_connect_ip( char* ps_ip)
{
    if(ps_ip == NULL)
    {
        return WFDR_INV_ARG;
    }
    char*ps_src = NULL;
    ps_src =  (char *)wfd_client_get_Ip(t_g_wfd_p2p_info.p_connect_mac);
    
    if(ps_src == NULL)
    {
        return WFDR_FAIL;
    }
    c_strncpy(ps_ip,ps_src,DEVICE_INFO_ARR_LEN);
    return WFDR_OK;
}

char* wfd_p2p_get_pin_to_show()
{
    const char* ps_src = NULL;
    ps_src =  (char *)wfd_client_pin_to_show();
    
    if(ps_src == NULL)
    {
        WFD_DBG_LOG_EX(ps_src,0);
        return NULL;
    }

    c_memset(t_g_wfd_p2p_info.pin_for_show, 0, sizeof(t_g_wfd_p2p_info.pin_for_show));
    c_strncpy(t_g_wfd_p2p_info.pin_for_show,ps_src,DEVICE_INFO_ARR_LEN);
    
    WFD_DBG_LOG_EX(t_g_wfd_p2p_info.pin_for_show,0);
    return t_g_wfd_p2p_info.pin_for_show;
}

INT32 wfd_p2p_set_enter_pin(char* pincode)
{
    if(pincode == NULL)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_INV_ARG;
    }  
    c_memset(t_g_wfd_p2p_info.pin_for_enter, 0, sizeof(t_g_wfd_p2p_info.pin_for_show));
    c_strncpy(t_g_wfd_p2p_info.pin_for_enter,pincode,DEVICE_INFO_ARR_LEN);
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_request_as_keypad_of(INT32 index)
{
    if(!t_g_wfd_p2p_info.b_is_start)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_OK;
    }

    const char* temp = NULL;
    temp = wfd_client_get_deviceMac(index);
    if(!temp)
        return WFDR_FAIL;

    c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
    c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,temp,DEVICE_INFO_ARR_LEN);

    if (wfd_client_connect(WFD_CONNECT_REQUEST_KEYPAD,t_g_wfd_p2p_info.p_wait_connect_mac, NULL) == 0)
    {
       return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_p2p_request_as_display_of(INT32 index)
{
    
    if(!t_g_wfd_p2p_info.b_is_start)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return WFDR_OK;
    }
    const char* temp = NULL;
     temp = wfd_client_get_deviceMac(index);
    if(!temp)
        return WFDR_FAIL;

    c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
    c_strncpy(t_g_wfd_p2p_info.p_wait_connect_mac,temp,DEVICE_INFO_ARR_LEN);

    if (wfd_client_connect(WFD_CONNECT_REQUEST_DISPLAY,t_g_wfd_p2p_info.p_wait_connect_mac, NULL) == 0)
    {
       return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__));
       return WFDR_FAIL;
    }

INT32 wfd_p2p_get_req_name(char * name)
{
    const char* temp = NULL;
    temp = wfd_client_get_device_info_str(t_g_wfd_p2p_info.p_request_connect_mac,DEVICE_INFO_STR_NAME);
    if(!temp)
    return WFDR_FAIL;

    c_strncpy(name,temp,DEVICE_INFO_ARR_LEN);
    return WFDR_OK;
}

//return index -1 is fail
INT32 wfd_p2p_get_req_index(VOID)
{
    INT32 i4_ret = -1;
   i4_ret = wfd_client_get_device_index(t_g_wfd_p2p_info.p_request_connect_mac);
    return i4_ret;
}

INT32 wfd_p2p_enable_miracast(VOID)
    {
    INT32 i4_ret = -1;
    i4_ret = wfd_client_enable_Miracast();
    return i4_ret;
    }

INT32 wfd_p2p_disable_miracast(VOID)
    {
    INT32 i4_ret = -1;
   i4_ret = wfd_client_disable_Miracast();
    return i4_ret;
}

INT32 wfd_p2p_enable_force_go(VOID)
{
    INT32 i4_ret = -1;
    i4_ret = wfd_client_group_add();
    return i4_ret;
}

INT32 wfd_p2p_disable_force_go(VOID)
{
    INT32 i4_ret = -1;
    i4_ret = wfd_client_group_remove(NULL);
    return i4_ret;
}

//return index -1 is fail
INT32 wfd_p2p_get_connect_index(VOID)
{
   return wfd_client_get_connect_index();
}

extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
static void _wfd_client_p2p_nfy(int notifyId,void *param)
{
    INT32  i4_ret = 0;
#ifdef APP_PORTING
    CHAR   s_ssid[32] = {0};
    CHAR   s_passphrase[64] = {0};
#endif
    WFD_SEND_RETRY_TYPE_T       e_retry_type = WFD_SEND_RETRY_TYPE_ONCE;
    wfd_event_handler           pf_event_handler =  wfd_main_handle_msg;
    VOID*                       pv_param1 = NULL; 
    VOID*                       pv_param2 = NULL;
    VOID*                       pv_param3 = NULL;
    VOID*                       pv_param4 = NULL;
    WFD_MSG_T                   e_msg = WFD_MSG_END;
    WFD_DBG_LOG(notifyId);
    UINT8                       ui1_miracast_status = 0;
    UINT8                       ui1_wifi_remote_status = 0;
    NET_802_11_P2P_DATA * _p2p_info = (NET_802_11_P2P_DATA*) param;

    /* by model support */
    if (FALSE == a_cfg_custom_get_wfd_support())
    {
        DBG_LOG_PRINT(("\ncurrent model do not support miracast\n"));
        return;
    }

    /* check whether miracast enabled or not */
    a_cfg_custom_get_miracast_enable_status(&ui1_miracast_status);
    if (0 == ui1_miracast_status)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,notifyId=%d,b_Is_GO=%d,miracast is disabled\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    notifyId,
                    _p2p_info->b_Is_GO));

        /* for miracast disabled case, still need to process this notify */
        if (WLAN_NOTIFY_P2P_GROUP_STARTED == notifyId)
        {
            if(_p2p_info->b_Is_GO)
            {
                t_g_wfd_p2p_info.b_is_go = TRUE;
                c_net_wlan_start_p2p_dhcpd_sever(NULL,NULL);
            }
            else
            {
                t_g_wfd_p2p_info.b_is_go = FALSE;
                c_net_p2p_start_dhcpc(t_g_wfd_p2p_info.interface_name);
            }
        }
        
        return;
    }

    /* check wifi remote is pairing or not */
    a_cfg_custom_get_wifi_remote_pair_status(&ui1_wifi_remote_status);
    if (WIFI_REMOTE_PAIR_STATUS_PAIRING == ui1_wifi_remote_status)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,wifi remote is pairing, discard messages\n",
                    __FILE__, __FUNCTION__, __LINE__));
        return;
    }

    DBG_LOG_PRINT(("\n%s,%s,%d,notifyId=%d,param->b_Is_GO=%d,param->_mac=%s,p_wait_connect_mac=%s,p_connect_mac=%s\n",
                __FILE__, __FUNCTION__, __LINE__, 
                notifyId,
                _p2p_info->b_Is_GO,
                _p2p_info->_mac,
                t_g_wfd_p2p_info.p_wait_connect_mac,
                t_g_wfd_p2p_info.p_connect_mac));

    switch (notifyId)
    {
        case WLAN_NOTIFY_P2P_DEVICE_FOUND:
        {
            e_msg = WFD_MSG_P2P_DEVICE_FOUND;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            break;
        }

        case WLAN_NOTIFY_P2P_DEVICE_LOST:
        {
            e_msg = WFD_MSG_P2P_DEVICE_LOST;

            //start dhcp
            pv_param1 = (VOID*)(UINT32)e_msg; 
            break;
        }
        //ralink solution sta connect as connect
        case WLAN_NOTIFY_P2P_GROUP_STARTED:
        {
            
            if(_p2p_info->b_Is_GO)
            {
                t_g_wfd_p2p_info.b_is_go = TRUE;
                c_net_wlan_start_p2p_dhcpd_sever(NULL,NULL);
            }
            else
            {
                t_g_wfd_p2p_info.b_is_go = FALSE;
                c_net_p2p_start_dhcpc(t_g_wfd_p2p_info.interface_name);
            }
            e_msg = WFD_MSG_P2P_GROUP_START;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            return;
        }
        case WLAN_NOTIFY_P2P_GROUP_REMOVED:
        {
            if(t_g_wfd_p2p_info.b_is_go)
            {
                c_net_wlan_stop_p2p_dhcpd_sever();
                t_g_wfd_p2p_info.b_is_go = FALSE;
        }
            else
        {
                c_net_p2p_stop_dhcpc(t_g_wfd_p2p_info.interface_name);
            }
            e_msg = WFD_MSG_P2P_GROUP_REMOVED;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
            c_memset(t_g_wfd_p2p_info.p_request_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_request_connect_mac));
             if(t_g_wfd_p2p_info.b_set_miracast)
             {
                 wfd_p2p_enable_miracast();
             }
#ifdef APP_PORTING
                wfd_p2p_assign_VIZIO_param_for_forceGO(s_ssid, s_passphrase);            
                i4_ret = wfd_client_group_add_param(s_ssid, s_passphrase);
                if (i4_ret < 0)
                {
                    DBG_LOG_PRINT(("wfd_client_group_add_param fail @ file = %s, function = %s, line = %d\n\r", 
                                        __FILE__, __FUNCTION__, __LINE__));
                }
                else
                {
                    DBG_LOG_PRINT(("wfd_client_group_add_param successful @ file = %s, function = %s, line = %d\n\r", 
                                        __FILE__, __FUNCTION__, __LINE__));
                }
#endif            
            return;
        }
        #ifdef APP_PORTING
        case WLAN_NOTIFY_AP_STA_CONNECTED:
        {
            /* check if wifi remote, miracast discard it */
            if (c_check_if_remote_mac_address(_p2p_info->_mac) == 0)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,_mac=%s, is remote mac address\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            _p2p_info->_mac));
                return;
            }

            c_net_wlan_p2p_set_ageout(_p2p_info->_mac, APP_MIRACAST_AGEOUT);
            c_strcpy(t_g_wfd_p2p_info.p_connect_mac, _p2p_info->_mac);
            if(c_strcmp(t_g_wfd_p2p_info.p_wait_connect_mac,_p2p_info->_mac) == 0)
            {
                c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
            }
            e_msg = WFD_MSG_AP_STA_CONNECTED;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            break;
        }
        #endif
        case WLAN_NOTIFY_AP_STA_DISCONNECTED:
        {
            if((c_strcmp(t_g_wfd_p2p_info.p_wait_connect_mac,_p2p_info->_mac) == 0))
            {
//                c_memset(t_g_wfd_p2p_info.p_wait_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_wait_connect_mac));
                return;
            }

            if((c_strcmp(t_g_wfd_p2p_info.p_connect_mac,_p2p_info->_mac) != 0))
            {
                return;
            }
            
            c_memset(t_g_wfd_p2p_info.p_connect_mac, 0, sizeof(t_g_wfd_p2p_info.p_connect_mac));

            e_msg = WFD_MSG_AP_STA_DISCONNECTED;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            break;
        }
        case WLAN_NOTIFY_WFD_IP_GET:
        {
            char s_resume_ap[APP_NAME_MAX_LEN+1] = {0};
            INT32 i4_ret = 0;
            
            i4_ret = a_am_get_active_app(s_resume_ap);
            if((0 == i4_ret) && (strcmp(s_resume_ap, "wfd") == 0))
            {
                b_g_resume_wfd_directly = FALSE;
            }
            else
            {
                b_g_resume_wfd_directly = TRUE;

                c_wgl_img_cache_flush();

            #ifdef APP_MENU_MMP_COEXIST
                if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
                {
                    a_icl_custom_set_next_resume_app(ICL_CUSTOM_RESUME_NEXT_APP_MIRACAST);
                    a_amb_resume_app(MMP_NAME);
                }
                else
                {
                    cmd_convert_send_cmd("\n:am,dtv_app_mtk,:resume=wfd\n");
                }
            #else
                cmd_convert_send_cmd("\n:am,dtv_app_mtk,:resume=wfd\n");
            #endif
                
                a_amb_clean_stack();
            }
            
            e_msg = WFD_MSG_P2P_IP_GET;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            break;
        }
        case WLAN_NOTIFY_P2P_SUPP_START_IND:
        {
            if (b_g_p2p_open_connection)
            {
                DBG_LOG_PRINT(("%s,%s,%d,p2p connection opened.\n",__FILE__, __FUNCTION__, __LINE__));
            }
            else
            {
                DBG_LOG_PRINT(("%s,%s,%d,call c_net_p2p_open_connection.\n",__FILE__, __FUNCTION__, __LINE__));
                i4_ret = c_net_p2p_open_connection();
                if (i4_ret < 0)
                {
                    DBG_LOG_PRINT(("%s,%s,%d,call c_net_p2p_open_connection fail!\n",__FILE__, __FUNCTION__, __LINE__));
                }
                else
                {
                    DBG_LOG_PRINT(("%s,%s,%d,call c_net_p2p_open_connection successful!\n",__FILE__, __FUNCTION__, __LINE__));
                    b_g_p2p_open_connection = TRUE;
                }
            }

            if(t_g_wfd_p2p_info.b_set_miracast)
            {
                wfd_p2p_enable_miracast();
            }
#ifdef APP_PORTING
                wfd_p2p_assign_VIZIO_param_for_forceGO(s_ssid, s_passphrase);
                i4_ret = wfd_client_group_add_param(s_ssid, s_passphrase);
                if (i4_ret < 0)
                {
                    DBG_LOG_PRINT(("wfd_client_group_add_param fail @ file = %s, function = %s, line = %d\n\r", 
                                        __FILE__, __FUNCTION__, __LINE__));
                }
                else
                {
                    DBG_LOG_PRINT(("wfd_client_group_add_param successful @ file = %s, function = %s, line = %d\n\r", 
                                        __FILE__, __FUNCTION__, __LINE__));
                }
#endif            
            e_msg = WFD_MSG_P2P_ENABLE_OK;
            t_g_wfd_p2p_info.b_is_start = TRUE;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            break;
        }
        case WLAN_NOTIFY_P2P_SUPP_START_FAILED:
        {
            e_msg = WFD_MSG_P2P_ENABLE_FAILED;
            t_g_wfd_p2p_info.b_is_start = FALSE;
            pv_param1 = (VOID*)(UINT32)e_msg; 
            break;
        }
        
        case WLAN_NOTIFY_WFD_PIN_KEYPAD:
        {
            if(c_strcmp(t_g_wfd_p2p_info.p_wait_connect_mac,_p2p_info->_mac) != 0)
        {
                e_msg = WFD_MSG_P2P_ENTER_PIN_REQ;
                c_strncpy(t_g_wfd_p2p_info.p_request_connect_mac,_p2p_info->_mac,DEVICE_INFO_ARR_LEN);
        }
            else
            e_msg = WFD_MSG_P2P_ENTER_PIN;
            pv_param1 = (VOID *)(UINT32)e_msg;
            break;
        }
        case WLAN_NOTIFY_WFD_PIN_DISPLAY:
        {
            if(c_strcmp(t_g_wfd_p2p_info.p_wait_connect_mac,_p2p_info->_mac) != 0)
            {
                e_msg = WFD_MSG_P2P_SHOW_PIN_REQ;
                c_strncpy(t_g_wfd_p2p_info.p_request_connect_mac,_p2p_info->_mac,DEVICE_INFO_ARR_LEN);
            }
            else
            {
            e_msg = WFD_MSG_P2P_SHOW_PIN;
            }
            pv_param1 = (VOID *)(UINT32)e_msg;
            char *ps_pin = NULL;
            ps_pin = wfd_p2p_get_pin_to_show();
            if (!ps_pin)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d\n",
                            __FILE__, __FUNCTION__, __LINE__));
                return;
            }
            pv_param2 = (VOID *)ps_pin;
            break;           
        }
        
        case WLAN_NOTIFY_P2P_GO_NEG_REQUEST:
        {
            if(c_strcmp(t_g_wfd_p2p_info.p_wait_connect_mac,_p2p_info->_mac) != 0)
            {
                c_strncpy(t_g_wfd_p2p_info.p_request_connect_mac,_p2p_info->_mac,DEVICE_INFO_ARR_LEN);
            }
            e_msg = WFD_MSG_P2P_NEG_REQ;
            pv_param1 = (VOID *)(UINT32)e_msg;
            break;
        }

        case WLAN_NOTIFY_WFD_PBC:
        {
//            if(c_strcmp(t_g_wfd_p2p_info.p_wait_connect_mac,_p2p_info->_mac) != 0)
//            {
                c_strncpy(t_g_wfd_p2p_info.p_request_connect_mac,_p2p_info->_mac,DEVICE_INFO_ARR_LEN);
//            }
            e_msg = WFD_MSG_P2P_PBC_REQ;
            pv_param1 = (VOID *)(UINT32)e_msg;
            break;
        }
        default:
        {
            return;
        }
    }

    if(pv_param1 != NULL)
        wfd_event_send_context(e_retry_type, pf_event_handler,pv_param1,pv_param2,pv_param3,pv_param4); 
    
    return;
}



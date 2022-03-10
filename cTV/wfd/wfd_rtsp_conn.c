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
 * $SWAuthor: cheng shen $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "wfd_rtsp_conn.h"
#include "wfd_p2p_conn.h"

extern WFD_P2P_INFO_T t_g_wfd_p2p_info;

static void _wfd_client_rtsp_nfy(WFD_RTSP_Event_e e,void * param);

INT32 wfd_rtsp_start_rtsp(VOID)
{
    if (wfd_client_start_rtsp(wfd_client_get_device_info_str(t_g_wfd_p2p_info.p_connect_mac,DEVICE_INFO_STR_MAC),_wfd_client_rtsp_nfy) == 0)
    {
//        wfd_free_video_resource();
        return WFDR_OK;
    }
    
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_rtsp_start_rtsp_ip_port(const char *s_ip, UINT32 ui4_port)
{
    if ((!s_ip)||(ui4_port<0))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_INV_ARG;
    }
    
    if (wfd_client_start_rtsp_ip_port(s_ip,ui4_port) >= 0)
    {
        return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_rtsp_play(VOID)
{
    if (wfd_client_media_play() == 0)
    {
        return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
    
}

INT32 wfd_rtsp_pause(VOID)
{
    if (wfd_client_media_pause() == 0)
    {
        return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
    
}

INT32 wfd_rtsp_stop(VOID)
{
    if (wfd_client_media_teardown() == 0)
    {
//        wfd_restore_video_resource();
        return WFDR_OK;
    }
//    wfd_restore_video_resource();
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
    
}

INT32 wfd_rtsp_send_IDRReq(VOID)
{
    if (wfd_client_send_IDRReq() >= 0)
    {
        return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
    
}

INT32 wfd_rtsp_enter_standby_mode(VOID)
{
    if (wfd_client_enter_standby_mode() >= 0)
    {
        return WFDR_OK;
    }
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return WFDR_FAIL;
}

INT32 wfd_rtsp_get_rtp_session_id(char *buf, int buflen)
{ 
    if ((!buf)||(buflen<=0))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_INV_ARG;
    }

    char *ptr = NULL;   
    ptr = (char *)wfd_client_get_rtpSessionId();
    if (!ptr)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    
    c_strncpy(buf, ptr, buflen);
    return WFDR_OK;
} 

INT32 wfd_rtsp_uibc_gen_event(int isMultiTouch)
{
    INT32 i4_ret = -1;
    
    i4_ret = wfd_client_uibc_gen_event(isMultiTouch);
    if (i4_ret < 0)
    {
       DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n", 
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
       return WFDR_FAIL;
    }
    return WFDR_OK;
} 


INT32 wfd_rtsp_uibc_cap_update(char *type)
{
    INT32 i4_ret = WFDR_OK;
    
    DBG_INFO(("[NW]enter %s\n", __FUNCTION__));
    i4_ret = wfd_client_uibc_cap_update(type);
    if (i4_ret < 0)
    {
       return WFDR_FAIL;
    }

    return WFDR_OK;
} 


INT32 wfd_rtsp_show_rtp_statistics(void)
{
    INT32 i4_ret = WFDR_OK;
    WFD_PUSH_PLAYER_STATS_T *rtps = NULL;

    rtps = (WFD_PUSH_PLAYER_STATS_T *)c_mem_alloc(sizeof(WFD_PUSH_PLAYER_STATS_T));
    if (!rtps)
        return WFDR_FAIL;
    c_memset(rtps, 0, sizeof(WFD_PUSH_PLAYER_STATS_T));
    i4_ret = wfd_client_get_rtp_stats((char *)rtps, sizeof(WFD_PUSH_PLAYER_STATS_T));
    /* note, the return is true or false */
    if (i4_ret <= 0)
    {
        if (rtps)
            c_mem_free(rtps);
        DBG_INFO(("Failed to get RTP stats\n"));
        return WFDR_FAIL;
    }
    else
    {
        DBG_INFO(("\n[RTP Statistics]\n-------------------------\n"));
        DBG_INFO(("Total received bytes:\t\t%u\n", rtps->total_received_size));
        DBG_INFO(("Total consumed bytes:\t\t%u\n", rtps->total_consumed_size));
        DBG_INFO(("Buf write idx:\t\t\t%d\n", rtps->buf_w_idx));
        DBG_INFO(("Buf read idx:\t\t\t%d\n", rtps->buf_r_idx));
        DBG_INFO(("Buf write position:\t\t%d\n", rtps->buf_w_start_pos));
        DBG_INFO(("Buffered bytes:\t\t\t%d\n", rtps->buffered_size));
        DBG_INFO(("Total buffer size:\t\t%d\n", rtps->total_size));
        DBG_INFO(("Out-of-buffer count:\t\t%d\n", rtps->oob_count));
        DBG_INFO(("CMPB GetBuffer err count:\t%d\n", rtps->cmpb_getbuffer_error_count));
        DBG_INFO(("CMPB SendData err count:\t%d\n", rtps->cmpb_senddata_error_count));
        DBG_INFO(("CMPB HeaderParse fail count:\t%d\n", rtps->header_parse_fail_count));
        DBG_INFO(("Audio PID:\t\t\t%d\n", rtps->audio_pid));
        DBG_INFO(("Video PID:\t\t\t%d\n", rtps->video_pid));
        DBG_INFO(("Audio codec:\t\t\t%d\n", rtps->audio_codec));
        DBG_INFO(("Video codec:\t\t\t%d\n", rtps->video_codec));
        DBG_INFO(("Player status:\t\t\t%d\n", rtps->pushplayer_status));
        DBG_INFO(("-------------------------\n"));
    }

    if (rtps)
        c_mem_free(rtps);
    return WFDR_OK;
    

}

static void _wfd_client_rtsp_nfy(WFD_RTSP_Event_e e,void* param)
{
        WFD_SEND_RETRY_TYPE_T       e_retry_type = WFD_SEND_RETRY_TYPE_ONCE;
        wfd_event_handler           pf_event_handler =  wfd_main_handle_msg;
        VOID*                       pv_param1 = NULL; 
        VOID*                       pv_param2 = NULL;
        VOID*                       pv_param3 = NULL;
        VOID*                       pv_param4 = NULL;
        WFD_MSG_T                   e_msg = WFD_MSG_END;
        WFD_DBG_LOG(e);
    /*  if(wfd_app_get_wfd_cond() !=  WFD_COND_RESUME)
        {
            return;
        } */
        switch (e)
        {
            case WFD_RTSP_TEARDOWN:
            {
                e_msg = WFD_MSG_RTSP_TEARDOWN;
                pv_param1 = (VOID*)(UINT32)e_msg; 
                break;
            }
            default:
            {
                return;
            }

        }
    
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,e_msg=%d\n", 
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                e_msg));
    if(pv_param1 != NULL)
        wfd_event_send_context(e_retry_type, pf_event_handler,pv_param1,pv_param2,pv_param3,pv_param4); 
    
    return;
}

INT32 wfd_rtsp_dump_ts_set_path(char *path)
{
    INT32 i4_ret = WFDR_OK;

    if (!path || !c_strlen(path))
        return WFDR_FAIL;
    i4_ret = wfd_client_dump_ts_set_path(path);
    /* note, the return is true or false */
    if (i4_ret < 0)
        return WFDR_FAIL;
    else
        return WFDR_OK;
}

INT32 wfd_rtsp_dump_ts_set_enable(int enable)
{
    INT32 i4_ret = WFDR_OK;

    i4_ret = wfd_client_dump_ts_set_enable(enable);
    /* note, the return is true or false */
    if (i4_ret < 0)
        return WFDR_FAIL;
    else
        return WFDR_OK;
}


INT32 wfd_rtsp_rtsp_sigma_cmd(int cmdtype, char *data, int datalen)
{
    INT32 i4_ret = WFDR_OK;

    i4_ret = wfd_client_rtsp_sigma_cmd(cmdtype, data, datalen);
    /* note, the return is true or false */
    if (i4_ret < 0)
        return WFDR_FAIL;
    else
        return WFDR_OK;
}

INT32 wfd_rtsp_conf_init(void)
{
    INT32 i4_ret = WFDR_OK;

    i4_ret = wfd_client_rtsp_conf_reset();

    if (i4_ret < 0)
        return WFDR_FAIL;
    else
        return WFDR_OK;
}

INT32 wfd_rtsp_set_ts_filename(char *tsname)
{
    INT32 i4_ret = WFDR_OK;

    if (!tsname || !strlen(tsname))
        return WFDR_FAIL;
    i4_ret = wfd_client_rtsp_conf_set(WFD_RTSP_CONF_TYPE_TS_READ_NAME, tsname, strlen(tsname));
    /* note, the return is true or false */
    if (i4_ret < 0)
        return WFDR_FAIL;
    else
        return WFDR_OK;
}



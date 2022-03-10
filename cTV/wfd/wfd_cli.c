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
 * $RCSfile: wfd_cli.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: hs_mingmingzhang $
 * $MD5HEX: 8ebc2c7a2c0fc209f18ef9bd3ccc4afd $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
#include "wfd.h"
#include "wfd_p2p_conn.h"
#include "wfd_rtsp_conn.h"
#include "wfd_dev_list.h"

/*--------------------------------------------------------------------------
 * private data declarations
 *------------------------------------------------------------------------*/
static HANDLE_T	 h_timer_find = NULL_HANDLE;
/*--------------------------------------------------------------------------
 * private methods declarations
 *------------------------------------------------------------------------*/
static INT32  _wfd_cli_set_dbg_level (
    INT32                       i4_argc,
    const CHAR**                pps_argv);

static INT32  _wfd_cli_get_dbg_level (
    INT32                       i4_argc,
    const CHAR**                pps_argv);
extern INT32 wfd_view_sta_toggle_show(BOOL b_show);

extern INT32 wfd_view_sta_set_bk(VOID);
extern INT32 wfd_view_sta_get_bk(VOID);


/*--------------------------------------------------------------------------
 * private methods implementations
 *------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------
 * Name: _helloworld_cli_get_dbg_level
 *
 * Description: This API gets the current debug level.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 -------------------------------------------------------------------------*/
static INT32 _wfd_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;

    i4_ret = c_cli_show_dbg_level(wfd_get_dbg_level());

    return i4_ret;
}

/*--------------------------------------------------------------------------
 * Name: _hw_cli_set_dbg_level
 *
 * Description: This API sets the debug level.
 *
 * Inputs:  i4_argc         Contains the argument count.
 *          pps_argv        Contains the arguments.
 *
 * Outputs: -
 *
 * Returns: CLIR_OK         Routine successful.
 -------------------------------------------------------------------------*/
static INT32 _wfd_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    INT32  i4_ret;

    i4_ret = c_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if (i4_ret == CLIR_OK){
        wfd_set_dbg_level(ui2_dbg_level);
    }

    return i4_ret;
}

static VOID _timer_notify(HANDLE_T  pt_tm_handle, VOID*  pv_tag)
{
	INT32  i4_ret = 0;
	INT32  i4_devnum = wfd_p2p_get_devicenumber();
	WFD_DEVICE_INFO_T  t_device_info;
	
	if (i4_devnum <= 0)
	{
		fprintf(stderr, "no invalid device info to print,command format.usage:prinfo.\n");	 
		return;
	}
	
	for (INT32  temp = 0; temp < i4_devnum; temp++)
	{
		i4_ret = wfd_p2p_get_device_info(WFD_DEV_ALL,(VOID*)&t_device_info,temp);
		if (i4_ret != WFDR_OK){
        	DBG_LOG_PRINT(("%s %d fail\n ",__FUNCTION__,__LINE__));
			return;
    	}
		INT32 i4_rssi = wfd_p2p_get_rssi(temp);
		INT32 i4_devType = wfd_p2p_get_wfdDevType(temp);

		char ps_wfd_devType[10] = {0};
		char *ps_devType_source = "Source";
		char *ps_devType_sink = "Sink";
		
		if (i4_devType == 0)
			c_strncpy(ps_wfd_devType, ps_devType_source, 10);
		else if (i4_devType == 1)
			c_strncpy(ps_wfd_devType, ps_devType_sink, 10);
	
		DBG_LOG_PRINT(("[%d] %s (%s)\n", temp, t_device_info.ps_device_name, t_device_info.ps_device_mac));
		DBG_LOG_PRINT(("    WFD device type: %s\n", ps_wfd_devType));
		DBG_LOG_PRINT(("    Signal level: %d\n", i4_rssi));
		DBG_LOG_PRINT(("    RTSP port: %d\n", t_device_info.i4_device_port));     	        		
	} 
	c_timer_delete(h_timer_find);
	h_timer_find = NULL_HANDLE;
	return;	
}

static INT32 _wfd_cli_stop_p2p (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;
    i4_ret = wfd_p2p_disable_wifi_display();

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}

static INT32 _wfd_cli_p2p_find (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;
    i4_ret = wfd_p2p_find();

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
    }
	if(h_timer_find == NULL_HANDLE)
	{
		c_timer_create(&h_timer_find);
		c_timer_start(h_timer_find, 
	                  10000, 
	                  X_TIMER_FLAG_REPEAT, 
	                  _timer_notify, 
	                  NULL);		
	}
	else
	{
		c_timer_stop(h_timer_find);
		c_timer_start(h_timer_find, 
	                  10000, 
	                  X_TIMER_FLAG_REPEAT, 
	                  _timer_notify, 
	                  NULL);
	}			
    return i4_ret;
}

static INT32 _wfd_cli_p2p_stop_find (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;
    i4_ret = wfd_p2p_stop_find();

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}

static INT32 _wfd_cli_start_p2p (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;
    i4_ret = wfd_p2p_enable_wifi_display();

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
    }

    wfd_rtsp_conf_init();
    
    return i4_ret;
}
static INT32 _wfd_cli_pbc_conn (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 mode;    
    INT32  i4_ret;
	if (i4_argc != 2)
	{
		fprintf(stderr, "p2p connect ,invalid command format.usage:pbc index.\n");
		return -1;
	}
	
	if (c_strlen(pps_argv[1]) == 1 && (pps_argv[1][0] >= '0' && pps_argv[1][0] <= '9'))
	{
		mode = pps_argv[1][0] - '0';
	}
	else 
	{
		fprintf(stderr, "p2p connect ,invalid parameter:mode!\n");
		return -1;
	}
    i4_ret = wfd_p2p_connect_pbc(mode);

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
    
}
static INT32 _wfd_cli_req_show (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 mode;    
    INT32  i4_ret;
	if (i4_argc != 2)
	{
		fprintf(stderr, "p2p connect ,invalid command format.usage:pbc index.\n");
		return -1;
	}
	
	if (c_strlen(pps_argv[1]) == 1 && (pps_argv[1][0] >= '0' && pps_argv[1][0] <= '9'))
	{
		mode = pps_argv[1][0] - '0';
	}
	else 
	{
		fprintf(stderr, "p2p connect ,invalid parameter:mode!\n");
		return -1;
	}
    i4_ret = wfd_p2p_request_as_display_of(mode);

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}

static INT32 _wfd_cli_req_enter (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 mode;    
    INT32  i4_ret;
	if (i4_argc != 2)
	{
		fprintf(stderr, "p2p connect ,invalid command format.usage:pbc index.\n");
		return -1;
	}
	
	if (c_strlen(pps_argv[1]) == 1 && (pps_argv[1][0] >= '0' && pps_argv[1][0] <= '9'))
	{
		mode = pps_argv[1][0] - '0';
	}
	else 
	{
		fprintf(stderr, "p2p connect ,invalid parameter:mode!\n");
		return -1;
	}
    
    i4_ret = wfd_p2p_request_as_keypad_of(mode);

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}

/*call receive WFD_DEVICE_EVENT_SHOW_PIN_REQ after */
static INT32 _wfd_cli_pin_display_accept (INT32 i4_argc, const CHAR** pps_argv)
{
	INT32  i4_ret = 0;
	i4_ret = wfd_p2p_pin_display_accept();
	if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
		return -1;
    }
    return i4_ret;
}

/*call _wfd_cli_req_show() after */
static INT32 _wfd_cli_show_pin (INT32 i4_argc, const CHAR** pps_argv)
{
    char* p_temp = NULL;
    p_temp = wfd_p2p_get_pin_to_show();

    if (p_temp != NULL)
	{
        DBG_LOG_PRINT(("%s %d pin=%s\n ",__FUNCTION__,__LINE__,p_temp));
    }
    else
    {
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
		return -1;
    }
    return 0;
}

static INT32 _wfd_cli_get_num (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 mode;    
    mode = wfd_p2p_get_devicenumber();

    DBG_LOG_PRINT(("%s %d num=%d\n",__FUNCTION__,__LINE__,mode));
    return 0;
}
/*call _wfd_cli_req_enter() after */
static INT32 _wfd_cli_p2p_pin_conn (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 mode;    
    INT32  i4_ret;
	char ps_pincode[10] = {0};
	if (i4_argc != 3)
	{
		fprintf(stderr, "p2p connect ,invalid command format.usage:pbc index.\n");
		return -1;
	}
	
	if (c_strlen(pps_argv[1]) == 1 && (pps_argv[1][0] >= '0' && pps_argv[1][0] <= '9'))
	{
		mode = pps_argv[1][0] - '0';
	}
	else 
	{
		fprintf(stderr, "p2p connect ,invalid parameter:mode!\n");
		return -1;
	}

	if (c_strlen(pps_argv[2]) == 8)
	{
		for(i4_ret = 0; i4_ret < 8; i4_ret++)
		{
			if(pps_argv[2][i4_ret] < '0' || pps_argv[2][i4_ret] > '9')
			{
				fprintf(stderr, "p2p connect ,invalid parameter 2:pin code!\n");
				return -1;
			}
		}
		c_strncpy(ps_pincode, pps_argv[2], c_strlen(pps_argv[2]));
		DBG_LOG_PRINT(("%s %d pin=%s\n ",__FUNCTION__,__LINE__,ps_pincode));
	}
	else 
	{
		fprintf(stderr, "p2p connect ,invalid parameter 2:pin code length!\n");
		return -1;
	}
		
	i4_ret = wfd_p2p_set_enter_pin(ps_pincode);
	if (i4_ret != WFDR_OK)
	{
        DBG_LOG_PRINT(("%s %d wfd_p2p_set_enter_pin() fail\n",__FUNCTION__,__LINE__));
		return -1;
    }
	
    i4_ret = wfd_p2p_connect_pin(mode);
    if (i4_ret != WFDR_OK)
	{
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));
		return -1;
    }
    return i4_ret;
}

static INT32 _wfd_cli_disconnect (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret;    
    i4_ret = wfd_p2p_disconnect();
    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d \n ",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}
static INT32 _wfd_cli_get_info (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 mode;   
    WFD_DEVICE_INFO_T device_info;
    INT32  i4_ret;
	if (i4_argc != 2)
	{
		fprintf(stderr, "p2p connect ,invalid command format.usage:pbc index.\n");
		return -1;
	}
	
	if (c_strlen(pps_argv[1]) == 1 && (pps_argv[1][0] >= '0' && pps_argv[1][0] <= '9'))
	{
		mode = pps_argv[1][0] - '0';
	}
	else 
	{
		fprintf(stderr, "p2p connect ,invalid parameter:mode!\n");
		return -1;
	}
    
    i4_ret = wfd_p2p_get_device_info(WFD_DEV_ALL,(VOID*)&device_info,mode);

    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n",__FUNCTION__,__LINE__));        
        return i4_ret;
    }


    DBG_LOG_PRINT(("%s %d name:%s\n",__FUNCTION__,__LINE__,device_info.ps_device_name));
    DBG_LOG_PRINT(("%s %d mac:%s\n",__FUNCTION__,__LINE__,device_info.ps_device_mac));
    DBG_LOG_PRINT(("%s %d ip:%s\n",__FUNCTION__,__LINE__,device_info.ps_device_ip));
    DBG_LOG_PRINT(("%s %d type %s\n",__FUNCTION__,__LINE__,device_info.ps_device_type));
    DBG_LOG_PRINT(("%s %d b_connect %d\n",__FUNCTION__,__LINE__,device_info.b_connect));        
    DBG_LOG_PRINT(("%s %d port %d\n",__FUNCTION__,__LINE__,device_info.i4_device_port));
        
    return i4_ret;
}

static INT32 _wfd_cli_print_info(INT32 i4_argc, const CHAR** pps_argv)
{
	INT32  i4_ret = 0;
	INT32  i4_devnum = wfd_p2p_get_devicenumber();
	WFD_DEVICE_INFO_T  t_device_info;
		
	if (i4_devnum <= 0)
	{
		fprintf(stderr, "no invalid device info to print,command format.usage:prinfo.\n");	 
		return -1;
	}
	
	for (INT32  temp = 0; temp < i4_devnum; temp++)
	{
		i4_ret = wfd_p2p_get_device_info(WFD_DEV_ALL,(VOID*)&t_device_info,temp);
		if (i4_ret != WFDR_OK){
        	DBG_LOG_PRINT(("%s %d fail\n ",__FUNCTION__,__LINE__));
			return -1;
    	}
		
		INT32 i4_rssi = wfd_p2p_get_rssi(temp);
		INT32 i4_devType = wfd_p2p_get_wfdDevType(temp);

		char ps_wfd_devType[10] = {0};
		char *ps_devType_source = "Source";
		char *ps_devType_sink = "Sink";
		
		if (i4_devType == 0)
			c_strncpy(ps_wfd_devType, ps_devType_source, 10);
		else if (i4_devType == 1)
			c_strncpy(ps_wfd_devType, ps_devType_sink, 10);
	
		DBG_LOG_PRINT(("[%d] %s (%s)\n", temp, t_device_info.ps_device_name, t_device_info.ps_device_mac));
		DBG_LOG_PRINT(("    WFD device type: %s\n", ps_wfd_devType));
		DBG_LOG_PRINT(("    Signal level: %d\n", i4_rssi));
		DBG_LOG_PRINT(("    RTSP port: %d\n", t_device_info.i4_device_port));     		
		if(wfd_p2p_is_connected(temp) == WFDR_OK)
		{
    		DBG_LOG_PRINT(("    is connect: true\n"));
		}
		else
		{
    		DBG_LOG_PRINT(("    is connect: false\n"));
		}
	}
	return WFDR_OK;
}

static INT32 _wfd_cli_debug_sta (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 mode;   
    INT32  i4_ret = 0;
	if (i4_argc != 2)
	{
		fprintf(stderr, "p2p connect ,invalid command format.usage:pbc index.\n");
		return -1;
	}
	
	if (c_strlen(pps_argv[1]) == 1 && (pps_argv[1][0] >= '0' && pps_argv[1][0] <= '9'))
	{
		mode = pps_argv[1][0] - '0';
	}
	else 
	{
		fprintf(stderr, "p2p connect ,invalid parameter:mode!\n");
		return -1;
	}
    
    switch ( mode )
    {
        case 0 :
            wfd_view_sta_set_bk();
            break;
        case 1 :
            wfd_view_sta_get_bk();
            break;
        case 2 :
            wfd_view_sta_toggle_show(TRUE);
            break;
            
        case 3 :
            wfd_view_sta_toggle_show(FALSE);
            break;
        default:
            break;
    }
    
    return i4_ret;
}

static INT32 _wfd_cli_start_rtsp (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret;    
    i4_ret = wfd_rtsp_start_rtsp();
    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d fail\n ",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}

static INT32 _wfd_cli_start_rtsp_ip_port (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 index = 0;
    INT32 i4_ret = 0;

    if (i4_argc < 3)
    {
       DBG_LOG_PRINT(("Please input the IP and PORT\n\r"));
       return CLIR_OK;
    }

    index = atoi(pps_argv[2]);

    i4_ret = a_wfd_wifi_display_start_rtsp((char *)pps_argv[1],index);

    if (i4_ret)
    {
        DBG_LOG_PRINT(("[NW_CLI]: wfd_client_start_rtsp is Unsuccessful\n\r"));
        return WFDR_FAIL;
    }
    else
    {
       DBG_LOG_PRINT((" [NW_CLI]:wfd_client_start_rtsp  success\n\r"));
       return WFDR_OK;
    }
}

static INT32 _wfd_cli_stop_rtsp (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret;
    i4_ret = wfd_rtsp_stop();
    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d \n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}
static INT32 _wfd_cli_play_rtsp (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret;    
    i4_ret = wfd_rtsp_play();
    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d  \n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}

static INT32 _wfd_cli_pause_rtsp (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret;    
    i4_ret = wfd_rtsp_pause();
    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d \n ",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}
static INT32 _wfd_cli_try_get_ip (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret;    
    i4_ret = wfd_p2p_try_to_find_ip();
    if (i4_ret != WFDR_OK){
        DBG_LOG_PRINT(("%s %d \n",__FUNCTION__,__LINE__));
    }
    return i4_ret;
}

static INT32 _wfd_cli_show_rtp_statistics(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;
    
    i4_ret = a_wfd_wifi_display_show_rtp_statistics();
    if (i4_ret)
    {
        DBG_LOG_PRINT(("[NW_CLI]: %s is Unsuccessful\n", __FUNCTION__));
        return CLIR_CMD_EXEC_ERROR;
    }
    else
    {
       DBG_LOG_PRINT((" [NW_CLI]:%s success\n", __FUNCTION__));
       return CLIR_OK;
    }    
}

static INT32 _wfd_cli_display_dump_ts_set_path(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;
    char *path = NULL;
    #define DUMP_TS_PATH_SIZE_MAX   256

    if (i4_argc != 2 ||
        strlen(pps_argv[1])==0)
    {
        DBG_LOG_PRINT(("CLI error. Please use \"dtsp [path]\".\nExample:dtsp /mnt/usb/sda1\n", __FUNCTION__));
        return CLIR_CMD_EXEC_ERROR;
    }

    path = (char *)malloc(DUMP_TS_PATH_SIZE_MAX);
    if (!path)
        return CLIR_CMD_EXEC_ERROR;
    else
        memset(path, 0, DUMP_TS_PATH_SIZE_MAX);
    strncpy(path, pps_argv[1], DUMP_TS_PATH_SIZE_MAX-1);
    DBG_LOG_PRINT(("Setting dump ts path to [%s]\n", path));
    i4_ret = a_wfd_wifi_display_dump_ts_set_path(path);
    if (i4_ret)
    {
        DBG_LOG_PRINT(("[NW_CLI]: %s is Unsuccessful\n", __FUNCTION__));
    }
    else
    {
       DBG_LOG_PRINT((" [NW_CLI]:%s success\n", __FUNCTION__));
    }
    if (path)
        free(path);
    return CLIR_OK;
}
    

static INT32 _wfd_cli_dump_ts_set_enable(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;
    int enable = 0;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("CLI error. Please use \"dtse [0|1]\".\n0=disable, 1=enable\n", __FUNCTION__));
        return CLIR_CMD_EXEC_ERROR;
    }

    enable = atoi(pps_argv[1]);
    i4_ret = a_wfd_wifi_display_dump_ts_set_enable(enable);
    if (i4_ret)
    {
        DBG_LOG_PRINT(("Dump TS %s successful\n", enable?"Enabled":"Disabled"));
    }
    else
    {
       DBG_LOG_PRINT((" [NW_CLI]:%s success\n", __FUNCTION__));
    }
    return CLIR_OK;
}

static INT32 _wfd_cli_set_ts_filename(INT32  i4_argc, const CHAR** pps_argv)
{

    INT32 i4_ret = 0;
    char *tsname = NULL;
#define TS_FILENAME_MAX   256

    if (i4_argc != 2 ||
        strlen(pps_argv[1])==0)
    {
        DBG_LOG_PRINT(("CLI error. Please use \"setts [name]\".\nExample:setts wfd-file1.ts\n", __FUNCTION__));
        return CLIR_CMD_EXEC_ERROR;
    }

    tsname = (char *)malloc(TS_FILENAME_MAX);
    if (!tsname)
        return CLIR_CMD_EXEC_ERROR;
    else
        memset(tsname, 0, TS_FILENAME_MAX);
    strncpy(tsname, pps_argv[1], TS_FILENAME_MAX-1);
    DBG_LOG_PRINT(("Setting ts name to [%s]\n", tsname));
    i4_ret = wfd_rtsp_set_ts_filename(tsname);
    if (i4_ret)
    {
        DBG_LOG_PRINT(("[NW_CLI]: %s is Unsuccessful\n", __FUNCTION__));
    }
    else
    {
       DBG_LOG_PRINT((" [NW_CLI]:%s success\n", __FUNCTION__));
    }
    if (tsname)
        free(tsname);
    return CLIR_OK;
}

static INT32 _wfd_cli_add_device(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;
    NAV_WFD_DEVICE_INFO_T    t_device_info;

    if (i4_argc != 4)
    {
        DBG_LOG_PRINT(("CLI error. Usage:ad VizioWFD 00:11:22:33:44:55 PC\n", __FUNCTION__));
        return CLIR_CMD_EXEC_ERROR;
    }
    
    c_memset(&t_device_info, 0, sizeof(NAV_WFD_DEVICE_INFO_T));
    c_memcpy(t_device_info.s_device_name, (char *)pps_argv[1], DEVICE_INFO_ARR_LEN); 
    c_memcpy(t_device_info.s_device_mac, (char *)pps_argv[2], DEVICE_INFO_ARR_LEN); 
    c_memcpy(t_device_info.s_device_type, (char *)pps_argv[3], DEVICE_INFO_ARR_LEN); 
    
    i4_ret = a_wfd_device_info_add_device(&t_device_info);
    if(i4_ret != CLIR_OK)
    {
        DBG_LOG_PRINT(("[WFD] %s failure == %d \r\n", __FUNCTION__, i4_ret));
        return CLIR_CMD_EXEC_ERROR;
    }
    
    i4_ret = a_wfd_device_info_save_list();      
    if(i4_ret != CLIR_OK)
    {
        DBG_LOG_PRINT(("[WFD] %s failure == %d \r\n", __FUNCTION__, i4_ret));
        return CLIR_CMD_EXEC_ERROR;
    }

    return CLIR_OK;
}

static INT32 _wfd_cli_delete_device(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;
    UINT8 ui1_idx = 0;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("CLI error. Usage:dd 0\n", __FUNCTION__));
        return CLIR_CMD_EXEC_ERROR;
    }

	if (c_strlen(pps_argv[1]) == 1 && (pps_argv[1][0] >= '0' && pps_argv[1][0] <= '9'))
	{
		ui1_idx = pps_argv[1][0] - '0';
	}
	else 
	{
		DBG_LOG_PRINT(("invalid parameter\n", __FUNCTION__));
		return CLIR_CMD_EXEC_ERROR;
	}

    i4_ret = a_wfd_device_info_unpair_device(ui1_idx);
    if(i4_ret != CLIR_OK)
    {
        DBG_LOG_PRINT(("[WFD] %s failure == %d \r\n", __FUNCTION__, i4_ret));
        return CLIR_CMD_EXEC_ERROR;
    }

    return CLIR_OK;
}

static INT32 _wfd_cli_show_device(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = 0;

    if (i4_argc != 1)
    {
        DBG_LOG_PRINT(("CLI error. Usage:sd\n", __FUNCTION__));
        return CLIR_CMD_EXEC_ERROR;
    }

    i4_ret = a_wfd_device_info_show_list();
    if(i4_ret != CLIR_OK)
    {
        DBG_LOG_PRINT(("[WFD] %s failure == %d \r\n", __FUNCTION__, i4_ret));
        return CLIR_CMD_EXEC_ERROR;
    }

    return CLIR_OK;
}

/*--------------------------------------------------------------------------
 * variable declarations
 *------------------------------------------------------------------------*/
/* command table */
static CLI_EXEC_T at_wfd_cmd_tbl[] =
{
    {CLI_GET_DBG_LVL_STR, NULL, _wfd_cli_get_dbg_level, NULL, CLI_GET_DBG_LVL_HELP_STR, CLI_GUEST},

    {CLI_SET_DBG_LVL_STR, NULL, _wfd_cli_set_dbg_level, NULL, CLI_SET_DBG_LVL_HELP_STR, CLI_GUEST},
        
    {"stopp2p",   "p2poff", _wfd_cli_stop_p2p, NULL, "stopp2p" ,  CLI_GUEST},
        
    {"startp2p",  "p2pon", _wfd_cli_start_p2p, NULL, "startp2p",CLI_GUEST},
    
    {"p2pfind",  "find", _wfd_cli_p2p_find, NULL, "p2pfind",CLI_GUEST},
        
    {"p2pstopfind",  "sfind", _wfd_cli_p2p_stop_find, NULL, "p2pstopfind",CLI_GUEST},
        
    {"p2p pbc connect",  "pbc", _wfd_cli_pbc_conn, NULL, "p2ppbcconnect" ,  CLI_GUEST},
        
    {"p2p req show",  "prs", _wfd_cli_req_show, NULL, "p2p req show" ,  CLI_GUEST},
        
    {"p2p req enter",  "pre", _wfd_cli_req_enter, NULL, "p2p req enter" ,  CLI_GUEST},

	{"pinShow Accept",  "psa", _wfd_cli_pin_display_accept, NULL, "pinShow Accept" ,  CLI_GUEST},
	   
    {"p2pshowpin",   "spin", _wfd_cli_show_pin, NULL, "p2pgetpin" ,  CLI_GUEST},

    {"p2p pin connect",  "pin", _wfd_cli_p2p_pin_conn, NULL, "p2ppinconnect" ,  CLI_GUEST},
        
    {"p2pgetnum",   "gnum", _wfd_cli_get_num, NULL, "p2pgetnum" ,  CLI_GUEST},
        
    {"p2pdisconnect",   "dconn", _wfd_cli_disconnect, NULL, "p2pdisconnect" ,  CLI_GUEST},
        
    {"getdeviceinfo",  "ginfo", _wfd_cli_get_info, NULL, "getdeviceinfo" ,  CLI_GUEST},

	{"printdevinfo",  "prinfo", _wfd_cli_print_info, NULL, "printdevinfo" ,  CLI_GUEST},

    {"start rtsp",  "rtspon", _wfd_cli_start_rtsp, NULL, "start rtsp" ,  CLI_GUEST},
        
    {"stop rtsp",  "rtspoff", _wfd_cli_stop_rtsp, NULL, "stop rtsp" ,  CLI_GUEST},
        
    {"play rtsp",  "srtsp", _wfd_cli_play_rtsp, NULL, "play rtsp" ,  CLI_GUEST},
        
    {"pause rtsp",  "prtsp", _wfd_cli_pause_rtsp, NULL, "pause rtsp" ,  CLI_GUEST},

    {"try get ip",  "gip", _wfd_cli_try_get_ip, NULL, "get rtsp" ,  CLI_GUEST},

    {"start rtsp IPport",  "dsrtsp", _wfd_cli_start_rtsp_ip_port, NULL, "start rtsp IPport" ,  CLI_GUEST},

    {"debug sta",  "dsta", _wfd_cli_debug_sta, NULL, "debug sta" ,  CLI_GUEST},

    {"show rtp stats", "rtps", _wfd_cli_show_rtp_statistics, NULL, "show rtp statistics", CLI_GUEST},
    {"dump ts set path", "dtsp", _wfd_cli_display_dump_ts_set_path, NULL, "dump ts set path", CLI_GUEST},
    {"dump ts enable", "dtse", _wfd_cli_dump_ts_set_enable, NULL, "dump ts enable", CLI_GUEST},
    {"set ts filename", "setts", _wfd_cli_set_ts_filename, NULL, "set ts filename", CLI_GUEST},

    {"add device", "ad", _wfd_cli_add_device, NULL, "add a device into paired list", CLI_GUEST},
    {"delete device", "dd", _wfd_cli_delete_device, NULL, "delete a device from paired list", CLI_GUEST},
    {"show device", "sd", _wfd_cli_show_device, NULL, "show all device info from paired list", CLI_GUEST},

    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_wfd_root_cmd_tbl[] =
{
    {   "wifi-dispaly",
        "wfd",
        NULL,
        at_wfd_cmd_tbl,
        "wifi-dispaly commands",
        CLI_GUEST
    },
    END_OF_CLI_CMD_TBL
};


/*--------------------------------------------------------------------------
 * export methods implementations
 *------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
 * Name:    hw_cli_attach_cmd_tbl
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *-------------------------------------------------------------------------*/
INT32 wfd_cli_attach_cmd_tbl(VOID)
{
    return (c_cli_attach_cmd_tbl(at_wfd_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}


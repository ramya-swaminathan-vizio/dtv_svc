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
 * $RCSfile: bluetooth_cli.c,v $
 * $Revision: #6 $
 * $Date: 2015/11/09 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file implements the CLI of bluetooth.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "c_cli.h"
#include "a_cfg.h"
#include "x_dbg.h"
#include "x_os.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


#include "bluetooth.h"
#include "bluetooth_timer.h"
#include "bluetooth_msgproc.h"
#include "bluetooth_spp.h"
#include "bluetooth_device.h"
#include "bluetooth_device_list.h"
#include "bluetooth_global_variables.h"
#include "bluetooth_hid.h"

#include "c_bt_mw_hidh.h"
#include "c_bt_mw_manager.h"
#include "c_bt_mw_gap.h"
#include "c_bt_mw_avrcp.h"
#include "c_bt_mw_spp.h"

#undef UART_PORT
#define UART_PORT UINT8
#ifndef MIN
#define MIN(a,b) ((a < b) ? a : b)
#endif

// dbg level
static UINT16 ui2_g_bt_app_dbg_level = DBG_LEVEL_ERROR;
extern VOID _bt_app_a2dp_snk_inquiry_response_cbk_fct(BT_GAP_SCAN_RESULT* pt_result);
extern INT32 c_btm_bt_disconnect_audio_sources(char *addr, audio_conn_type_t type);
extern INT32 c_btm_set_virtual_sniffer(INT32 enable);
extern void btmw_test_do_cli_cmd(int argc, char **argv);
extern int btmw_test_cli_init(void);

/**-----------------------------------------------------------------------------
  * Name          - bluetooth_get_dbg_level
  *
  * Description  - the API returns the current setting of debug level
  *
  * Returns       - UINT16 the current debug level
  *
  *---------------------------------------------------------------------------*/
UINT16 bluetooth_get_dbg_level(VOID)
{
    return ui2_g_bt_app_dbg_level;
}


/**-----------------------------------------------------------------------------
  * Name          - bluetooth_set_dbg_level
  *
  * Description  - this API is setting the debug level
  *
  * Inputs        - INT32 the debug level wanted to set
  *
  *---------------------------------------------------------------------------*/
VOID bluetooth_set_dbg_level(UINT16 ui2_db_level)
{
    ui2_g_bt_app_dbg_level = ui2_db_level;
}

/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_cli_get_dbg_level
  *
  * Description  - the API gets the current debug level and show it
  *
  * Returns       - INT32 if CLIR_OK, the routine is successful;else, the routine is failed
  *
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_cli_get_dbg_level(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret = CLIR_OK;

    i4_ret = c_cli_show_dbg_level(bluetooth_get_dbg_level());

    return i4_ret;
}


/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_cli_set_dbg_level
  *
  * Description  - this API sets the debug leve
  *
  * Returns       - INT32 if CLIR_OK, the routine is successful;else, the routine is failed
  *
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_cli_set_dbg_level(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level = 0;
    INT32  i4_ret = CLIR_OK;

    i4_ret = c_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if (CLIR_OK == i4_ret)
    {
        bluetooth_set_dbg_level(ui2_dbg_level);
    }

    return i4_ret;
}

/**-----------------------------------------------------------------------------
  * Name          - _atoi
  *
  * Description  - Convert a number string to a number.
  *
  * Returns       - Sum of the number string.
  *
  *---------------------------------------------------------------------------*/
static INT32 _atoi( const CHAR* ps )
{
    INT32  i4_total;

    i4_total = 0;
    while ( *ps != 0 )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            i4_total = 10 * i4_total + (*ps - '0');
            ps++; /* get next char */
        }
        else /* not a digit char */
        {
            return (-1);
        }
    }

    return i4_total;
}

/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_cli_set_mw_dbg_level
  *
  * Description  - this API sets the debug leve of MW
  *
  * Returns       - INT32 if CLIR_OK, the routine is successful;else, the routine is failed
  *
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_cli_set_mw_dbg_level(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_dbg_level = 0;
    UINT16 ui2_dbg_level = 0;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help\n"));
        DBG_LOG_PRINT(("bt_set_level [DBG_level]\n"));
        return CLIR_INV_ARG;
    }

    i4_dbg_level = _atoi(pps_argv[1]);

    // set APP debug level
    if(i4_dbg_level > 0)
    {
        ui2_dbg_level = DBG_LEVEL_ERROR | DBG_LEVEL_API | DBG_LEVEL_INFO;
        bluetooth_set_dbg_level(ui2_dbg_level);
    }

    // set MW debug level
    //c_btm_set_mw_debug_level(i4_dbg_level);

    DBG_LOG_PRINT(("Bluetooth module debug level is %d now\n", i4_dbg_level));

    return CLIR_OK;
}

static INT32 _bluetooth_cli_btmw_test(INT32 i4_argc, const CHAR** pps_argv)
{
    btmw_test_cli_init();

    btmw_test_do_cli_cmd(i4_argc-1, (CHAR**)(pps_argv+1));

    fflush(stdout);

    return CLIR_OK;
}

static INT32 _bluetooth_cli_init(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc != 1)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help\n"));
        DBG_LOG_PRINT(("bt_init\n"));
        return CLIR_INV_ARG;
    }

    // set MW debug level
    bluetooth_init();

    DBG_LOG_PRINT(("bluetoot init done.\n"));

    return CLIR_OK;
}

static INT32 _pbk_bt_start(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_tosec = 0;
    bluetoothAudioInputMode e_bt_mode = BLUETOOTH_AUDIO_INPUT_MODE_PAIRING;

    if (i4_argc > 3)
    {
        DBG_LOG_PRINT(("Invalid arguments, Help:\n"));
        DBG_LOG_PRINT(("bt_start [bt_mode] [tosec]\n"));
        DBG_LOG_PRINT(("  [bt_mode]: PAIRING | CONNECT | PLAYING | CLOSED\n"));
        return CLIR_INV_ARG;
    }

    if(i4_argc == 1)
    {
        e_bt_mode = BLUETOOTH_AUDIO_INPUT_MODE_PAIRING;
        i4_tosec = 0;
    }
    else if(i4_argc >= 2)
    {
        if(c_strcmp(pps_argv[1], "CLOSED") == 0)
        {
            e_bt_mode = BLUETOOTH_AUDIO_INPUT_MODE_CLOSED;
        }
        else if(c_strcmp(pps_argv[1], "PAIRING") == 0)
        {
            e_bt_mode = BLUETOOTH_AUDIO_INPUT_MODE_PAIRING;
        }
        else if(c_strcmp(pps_argv[1], "CONNECT") == 0)
        {
            e_bt_mode = BLUETOOTH_AUDIO_INPUT_MODE_CONNECT;
        }
        else if(c_strcmp(pps_argv[1], "PLAYING") == 0)
        {
            e_bt_mode = BLUETOOTH_AUDIO_INPUT_MODE_PLAY;
        }
        else
        {
            DBG_LOG_PRINT(("Invalid mode\n"));
            return CLIR_INV_ARG;
        }

        if(i4_argc >= 3)
        {
            i4_tosec = _atoi(pps_argv[2]);
        }
        else
        {
            i4_tosec = 0;
        }
    }

    bluetooth_pbk_audio_input_start(e_bt_mode, i4_tosec);

    return CLIR_OK;
}

static INT32 _pbk_bt_stop(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc != 1)
    {
        DBG_ERROR(("<BLUETOOTH_CLI> invalid arguments.\n"));
        return CLIR_INV_ARG;
    }

    bluetooth_pbk_audio_input_stop();

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bluetooth_cli_pair
  *
  * Description  - The CLI is used to pair with a bluetooth device
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_cli_pair(INT32 i4_argc, const CHAR** pps_argv)
{
    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("bt_pair [MAC_Address]\n"));
        return CLIR_OK;
    }

    c_btm_pair((char*)pps_argv[1], 0);

    return CLIR_OK;
}

static INT32 _pbk_bt_mode_get(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
    bluetoothAudioInputMode e_mode = BLUETOOTH_AUDIO_INPUT_MODE_CLOSED;
    UINT32 tosec = 0;

    bluetooth_audio_input_mode_get(&e_mode, &tosec);

    DBG_LOG_PRINT(("Bluetooth Mode: %d, tosec: %d\n", e_mode, tosec));

    return CLIR_OK;
}

static INT32 _pbk_bt_locla_device_info_get(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
    BT_LOCAL_DEV dev_info;
    INT32 i4_ret;

    a_mtkapi_bt_gap_get_local_dev_info(&dev_info);

    if (0 == i4_ret)
    {
        BT_APP_LOG_DEFAULT(("get local device info ok!\n"));
        BT_APP_LOG_DEFAULT(("ps_dev_info.bdAddr:      %s\n", dev_info.bdAddr));
        BT_APP_LOG_DEFAULT(("ps_dev_info.name:        %s\n", dev_info.name));
        BT_APP_LOG_DEFAULT(("ps_dev_info.state:     %s\n", dev_info.state? "on" : "off"));
        BT_APP_LOG_DEFAULT(("ps_dev_info.scan_mode:   %ld\n", (unsigned long)dev_info.scan_mode));
        BT_APP_LOG_DEFAULT(("ps_dev_info.service: %ld\n", (unsigned long)dev_info.service));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("get local device info failed!\n"));
    }

    return CLIR_OK;
}

// set bluetooth local device name
static INT32 _bluetooth_local_device_name_set(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
    char name[255];
    INT32 st_strlen = 0;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("<BLUETOOTH_CLI> invalid arguments.\n"));
        return CLIR_OK;
    }
    c_memset(name, 0, 255);
    st_strlen = c_strlen( pps_argv[1] );
    c_strncpy(name, pps_argv[1], st_strlen);

    a_bt_app_set_local_device_name(name);

    return CLIR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - _bluetooth_paired_list_get
  *
  * Description  - Show all paired devices
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_paired_list_get(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret  = CLIR_OK;
    UINT8 ui1_idx = 0;
    BT_TARGET_DEV_LIST pt_device_list = {0};

    i4_ret = a_bt_app_get_paired_device_list(&pt_device_list);
    if(0 == i4_ret)
    {
        if(pt_device_list.dev_num > 0)
        {
            for(ui1_idx = 0; ui1_idx < pt_device_list.dev_num; ui1_idx++)
            {
                DBG_LOG_PRINT(("Name:%s. Mac_addr:%s\n",
                            pt_device_list.device_list[ui1_idx].name,
                            pt_device_list.device_list[ui1_idx].bdAddr));
            }
        }
        else
        {
            DBG_LOG_PRINT(("No paired device\n"));
        }

    }
    else
    {
        DBG_LOG_PRINT(("Get paired device fail.\n"));
    }

    return CLIR_OK;
}


static INT32 _bluetooth_paired_device_erase(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
    char addr[18];

    if (i4_argc != 2)
    {
        DBG_ERROR(("<BLUETOOTH_CLI> invalid arguments.\n"));
        return CLIR_INV_ARG;
    }

    c_memset(addr, 0, 18*sizeof(char));

    c_strncpy(addr, pps_argv[1], 18 - 1);

    a_bt_app_src_paired_device_remove(addr);

    return CLIR_OK;
}


static INT32 _bluetooth_paired_device_erase_all(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{

    if (i4_argc != 1)
    {
        DBG_ERROR(("<BLUETOOTH_CLI> invalid arguments.\n"));
        return CLIR_INV_ARG;
    }

    a_bt_app_src_paired_device_remove_all();

    return CLIR_OK;
}

static INT32 _bluetooth_remote_device_get(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
    char mac_addr[25];

    c_memset(mac_addr, 0, 25);

    c_btm_get_target_addr(mac_addr);

    DBG_LOG_PRINT(("[BT][CLI]addr: %s.\n",mac_addr));

    return CLIR_OK;
}

#if 0
static INT32 _bluetooth_audio_control_meta_data_get(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
    //INT32           i4_ret = 0;

    if (i4_argc != 1)
    {
        DBG_ERROR(("<BLUETOOTH_CLI> invalid arguments.\n"));
        return CLIR_INV_ARG;
    }

    return CLIR_OK;
}
#endif
static INT32 _bluetooth_audio_control_play_status_get(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    INT32   i4_ret = BT_APPR_OK;
    UINT32  ui4_play_status_count = 0;
    bt_player_status_values_t pt_playStatus = {0};

    bt_app_set_playstatus_ready_flag(FALSE);
    i4_ret = c_btm_avrcp_get_play_status(&pt_playStatus);
    if(0 != i4_ret)
    {
        DBG_LOG_PRINT(("send request to get Play status failed\n"));
        return CLIR_OK;
    }

    while(!bt_app_playstatus_is_ready())
    {
        ui4_play_status_count++;
        if(ui4_play_status_count>20)
        {
            DBG_LOG_PRINT(("Cannot obtain Play status\n"));
            return CLIR_OK;
        }
        c_thread_delay(200);
    }

    i4_ret = c_btm_avrcp_get_play_status(&pt_playStatus);
    if(0 != i4_ret)
    {
        DBG_LOG_PRINT(("Cannot obtain Play status\n"));
        return CLIR_OK;
    }

    DBG_LOG_PRINT(("[BT][CLI]Songlength(ms) : %d.\n",pt_playStatus.song_length));
    DBG_LOG_PRINT(("[BT][CLI]Songposition   : %d.\n",pt_playStatus.song_position));
    switch(pt_playStatus.play_status)
    {
        case AVRCP_STATUS_STOPPED:
            DBG_LOG_PRINT(("[BT][CLI]playstatus     : STOPPED.\n"));
            break;
        case AVRCP_STATUS_PLAYING:
            DBG_LOG_PRINT(("[BT][CLI]playstatus     : PLAYING.\n"));
            break;
        case AVRCP_STATUS_PAUSED:
            DBG_LOG_PRINT(("[BT][CLI]playstatus     : PAUSED.\n"));
            break;
        case AVRCP_STATUS_FORWARDSEEK:
            DBG_LOG_PRINT(("[BT][CLI]playstatus     : FORWARDSEEK.\n"));
            break;
        case AVRCP_STATUS_REWINDSEEK:
            DBG_LOG_PRINT(("[BT][CLI]playstatus     : REWINDSEEK.\n"));
            break;
        default:
            DBG_LOG_PRINT(("[BT][CLI]No such status %d\n", pt_playStatus.play_status));
            break;
    }

#endif

    return CLIR_OK;
}

static INT32 _bluetooth_connect_audio_sources_cli (
    INT32                      i4_argc,
    const CHAR*               pps_argv[])
{
    #if 0
    audio_conn_type_t type = CONN_TYPE_A2DP;
    CHAR addr[18];

    c_memset(&addr, 0, sizeof(addr));
    if(3 == i4_argc)
    {
        if(c_strlen(pps_argv[1]) != 17)
        {
            DBG_LOG_PRINT(("MAC address input error,please input it again\n"));
            DBG_LOG_PRINT(("like as: 11:22:33:44:55:66\n"));
            return BT_ERR_OUT_OF_RANGE;
        }
        if (c_strcmp(pps_argv[2], "a2dp")== 0)
            type = CONN_TYPE_A2DP;
        else if (c_strcmp(pps_argv[2], "avctp")== 0)
            type = CONN_TYPE_AVCTP;
        else
            return BT_ERR_INVALID_PARAM;

        c_strncpy(addr, pps_argv[1], 17);
        DBG_LOG_PRINT(("addr:%s\n", addr));

        //c_btm_connect_audio_sources(addr, type);
    }
    else
    {
        DBG_LOG_PRINT(("input error\n"));
        return BT_ERR_INVALID_PARAM;
    }
	#endif
    return BT_ERR_SUCCESS;


}

static INT32 _bluetooth_disconnect_audio_sources_cli (
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{

    audio_conn_type_t type = CONN_TYPE_A2DP;
    CHAR addr[18];
    DBG_LOG_PRINT(("argv[0]:%s\n", pps_argv[0]));
    DBG_LOG_PRINT(("argv[1]:%s\n", pps_argv[1]));
    DBG_LOG_PRINT(("argv[2]:%s\n", pps_argv[2]));
    c_memset(&addr, 0, sizeof(addr));
    if(2 == i4_argc)
    {
        if (c_strcmp(pps_argv[1], "a2dp")== 0)
            type = CONN_TYPE_A2DP;
        else if (c_strcmp(pps_argv[1], "avctp")== 0)
            type = CONN_TYPE_AVCTP;
        else
            return BT_ERR_INVALID_PARAM;
        c_strncpy(addr, "11:22:33:44:55:66", 17);
        c_btm_bt_disconnect_audio_sources(addr, type);
    }
    else if(3 == i4_argc)
    {
        if(c_strlen(pps_argv[1]) != 17)
        {
            DBG_LOG_PRINT(("MAC address input error,please input it again\n"));
            DBG_LOG_PRINT(("like as: 11:22:33:44:55:66\n"));
            return BT_ERR_OUT_OF_RANGE;
        }
        if (c_strcmp(pps_argv[2], "a2dp")== 0)
            type = CONN_TYPE_A2DP;
        else if (c_strcmp(pps_argv[2], "avctp")== 0)
            type = CONN_TYPE_AVCTP;
        else
            return BT_ERR_INVALID_PARAM;

        c_strncpy(addr, pps_argv[1], 17);

        c_btm_bt_disconnect_audio_sources(addr, type);
    }
    else
    {
        DBG_LOG_PRINT(("input error\n"));
        return BT_ERR_INVALID_PARAM;
    }

    return BT_ERR_SUCCESS;


}

static INT32 _bluetooth_avrcp_get_capabilities_cli (
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    //BT_AVRCP_KEY_STATE action = BUTTON_ACT_AUTO;
    avrcp_apability_type_t type;

    if(2 == i4_argc)
    {
        if (c_strcmp(pps_argv[1], "companyid") == 0)
        {
            type = CAPABILITY_COMPANYID;
        }
        else if (c_strcmp(pps_argv[1], "events") == 0)
        {
            type = CAPABILITY_EVENTS;
        }
        else
        {
            DBG_LOG_PRINT(("unknow capability\n"));
            type = CAPABILITY_UNKNOWN;
        }
        //c_btm_bt_avrcp_get_capabilities(type);
    }
    //default mode is CT
    else
    {
        DBG_LOG_PRINT(("input error\n"));
        //action = BUTTON_ACT_AUTO;
    }

#endif

    return 0;
}

static INT32 _bluetooth_avrcp_enable_abortrsp_cli(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
    sys_enable_t enable=DISABLED;
    INT32 i4_ret = 0;
    if (i4_argc == 1)
    {
        //i4_ret = bt_audio_get_abortrsp_mode(&enable);
        if(0 != i4_ret)
        {
            DBG_LOG_PRINT(("get abortrsp mode failed\n"));
            return -1;
        }
        DBG_LOG_PRINT(("Abort Response Mode : %s\n",
            enable? "Enable" : "Disable"));

        return 0;
    }

    if (c_strcmp(pps_argv[1], "enable") == 0)
    {
        enable = ENABLED;
    }
    else if (c_strcmp(pps_argv[1], "disable") == 0)
    {
        enable = DISABLED;
    }
    else
    {
        return -1;
    }

    //i4_ret = bt_audio_set_abortrsp_mode(enable);
    if(0 != i4_ret)
    {
        DBG_LOG_PRINT(("set abortrsp mode failed\n"));
        return -1;
    }

    return 0;
}

static INT32 _bluetooth_reg_avrcp_notification_cli(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    CHAR pNotificationStr[64];
    if(2 == i4_argc)
    {
        //pNotificationStr = strdup(pps_argv[1]);
        c_strncpy(pNotificationStr, pps_argv[1], c_strlen(pps_argv[1]));
    }
    else
    {
        c_strncpy(pNotificationStr, "trackChange", c_strlen(pps_argv[1]));
    }
   // c_btm_register_avrcp_notification(pNotificationStr);

#endif

    return 0;
}

static INT32 _bluetooth_avrcp_command_send(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    BT_AVRCP_KEY_STATE e_action = BUTTON_ACT_AUTO;
    INT32 i4_ret = BT_APPR_OK;

    if((i4_argc != 2) && (i4_argc != 3))
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("bt_cmd_send [avrcp_key] [push|release]\n"));
        DBG_LOG_PRINT(("    [avrcp_key]: play,pause,stop,next,prev,ff,fr\n"));
        return CLIR_INV_ARG;
    }

    if(3 == i4_argc)
    {
        if(0 == c_strcmp(pps_argv[2], "push"))
        {
            e_action = BT_AVRCP_KEY_STATE_PRESS;
    }
        else if(0 == c_strcmp(pps_argv[2], "release"))
    {
            e_action = BUTTON_ACT_RELEASE;
    }
    else
    {
            DBG_LOG_PRINT(("Invalid arguments, help:\n"));
            DBG_LOG_PRINT(("bt_cmd_send [avrcp_key] [push|release]\n"));
        }
    }

    if(0 == c_strcmp(pps_argv[1], "play"))
    {
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PLAY, e_action);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else if(0 ==c_strcmp(pps_argv[1], "pause"))
    {
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PAUSE, e_action);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else if(0 ==c_strcmp(pps_argv[1], "stop"))
    {
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_STOP, e_action);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else if(0 ==c_strcmp(pps_argv[1], "next"))
    {
        //c_btm_cmd_seekff(e_action);
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_FWD, e_action);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else if(0 ==c_strcmp(pps_argv[1], "prev"))
    {
        //c_btm_cmd_backward(e_action);
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_BWD, e_action);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else if(0 ==c_strcmp(pps_argv[1], "ff"))
    {
        //c_btm_cmd_seekfff(e_action);
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_FFWD, e_action);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else if(0 ==c_strcmp(pps_argv[1], "fr"))
    {
        //c_btm_cmd_seekrw(e_action);
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_RWD, e_action);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        DBG_LOG_PRINT(("<BT_APP> invalid avrcp key\n"));
    }

#endif

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bluetooth_cli_change_volume
  *
  * Description  - The CLI to change volume
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_cli_change_volume(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = CLIR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("volume [0|1], 0: volume up, 1: volume down\n"));
        return CLIR_INV_ARG;
    }

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_VOLUME_CHG;
    if (c_strcmp(pps_argv[1], "0")== 0)
    {
        t_bt_msg.ui4_msg_id = BT_VOLUME_TYPE_UP;
    }
    else if (c_strcmp(pps_argv[1], "1")== 0)
    {
        t_bt_msg.ui4_msg_id = BT_VOLUME_TYPE_DOWN;
    }
    else
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("volume [0|1], 0: volume up, 1: volume down\n"));
        return CLIR_INV_ARG;
    }

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != CLIR_OK)
    {
        DBG_LOG_PRINT(("ERR: send volume msg fail, %d\n", i4_ret));
    }

    return CLIR_OK;
}


static INT32 _bluetooth_cmdv_send_sircs(INT32 i4Argc, const CHAR ** szArgv)
{
    UINT16 ui2_category_code;
    UINT8  ui1_category_code_h;
    UINT8  ui1_category_code_l;
    UINT8  ui1_key_code;
    UINT32 ui4_interval_time;
    CHAR   *s_end_ptr;

    CHAR   c_category_code[4]; // length is just for max length of input ( there is no margin for \0 !! )
    CHAR   c_key_code[2];      // length is just for max length of input ( there is no margin for \0 !! )
    SIZE_T st_strlen;
    UINT8  i;

    if ( i4Argc != 3 && i4Argc != 4 )
    {
        DBG_LOG_PRINT(("cmdv [category code] [key code] <interval time>\n"));
        return CLIR_OK;
    }

    st_strlen = c_strlen( szArgv[1] );
    if( st_strlen == 0 )
    {
        DBG_LOG_PRINT(("cmdv [category code] [key code] <interval time>\n"));
        return CLIR_OK;
    }
    else
    {
        if( st_strlen > 4 )
            st_strlen = 4;
        c_strncpy( c_category_code, szArgv[1], st_strlen);
        ui2_category_code = 0;
        for( i=0; i<(UINT8)st_strlen; i++ )
        {
            ui2_category_code *= 16;
            if( c_category_code[i] >= '0' && c_category_code[i] <= '9')
            {
                ui2_category_code += c_category_code[i]-48;
            }
            else if( c_category_code[i] >= 'A' && c_category_code[i] <= 'F')
            {
                ui2_category_code += c_category_code[i]-65+10;
            }
            else if( c_category_code[i] >= 'a' && c_category_code[i] <= 'f')
            {
                ui2_category_code += c_category_code[i]-97+10;
            }
            else
            {
                DBG_LOG_PRINT(("cmdv [category code] [key code] <interval time>\n"));
                return CLIR_OK;
            }
        }

        ui1_category_code_h = (UINT8)((ui2_category_code&0xFF00)>>8);
        ui1_category_code_l = (UINT8)(ui2_category_code&0x00FF);
        //d_diag_printf("ui2_category_code:%d, ui1_category_code_h:%d, ui1_category_code_l:%d\n",
                        //ui2_c/ategory_code,ui1_category_code_h,ui1_category_code_l);
    }

    st_strlen = c_strlen( szArgv[2] );
    if( st_strlen == 0 )
    {
        DBG_LOG_PRINT(("cmdv [category code] [key code] <interval time>\n"));
        return CLIR_OK;
    }
    else{
        if( st_strlen > 2 ) st_strlen = 2;
        c_strncpy( c_key_code, szArgv[2], st_strlen);
        ui1_key_code = 0;
        for( i=0; i<(UINT8)st_strlen; i++)
        {
            ui1_key_code *= 16;
            if( c_key_code[i] >= '0' && c_key_code[i] <= '9')
            {
                ui1_key_code += c_key_code[i]-48;
            }
            else if( c_key_code[i] >= 'A' && c_key_code[i] <= 'F')
            {
                ui1_key_code += c_key_code[i]-65+10;
            }
            else if( c_key_code[i] >= 'a' && c_key_code[i] <= 'f')
            {
                ui1_key_code += c_key_code[i]-97+10;
            }
            else
            {
                DBG_LOG_PRINT(("cmdv [category code] [key code] <interval time>\n"));
                return CLIR_OK;
            }
        }
    }

    if ( i4Argc == 3 )
    {
        ui4_interval_time = 0;
    }
    else
    {
        ui4_interval_time = (UINT32)c_strtoull(szArgv[3], &s_end_ptr, 0);
        if ( s_end_ptr == szArgv[3] )
        {
            DBG_LOG_PRINT(("cmdv [category code] [key code] <interval time>\n"));
            return CLIR_OK;
        }
    }

    if ( ui4_interval_time < 165 )
        ui4_interval_time = 165;

    DBG_LOG_PRINT(("<bluetooth> ui1_category_code_h = %d, ui1_category_code_l= %d,ui1_key_code=%d,ui4_interval_time=%d\n",
        ui1_category_code_h,ui1_category_code_l,
        ui1_key_code,ui4_interval_time));

    //d_ifcon_send_sircs_code(ui1_category_code_h, ui1_category_code_l, ui1_key_code, ui4_interval_time);

    return CLIR_OK;
}

static INT32 _bluetooth_decoder_aac(
    INT32                      i4_argc,
    const CHAR**               pps_argv)
{
     if (i4_argc != 3)
    {
        DBG_ERROR(("<Bluetooth> invalid arguments.\n"));
		DBG_ERROR(("Usage: dec_aac inputfile.aac outputfile.wav\n"));
        return CLIR_INV_ARG;
    }
    return 0;
    //return Bluetooth_Decoder_AAC_File(pps_argv[1], pps_argv[2]);
}

static INT32 _bluetooth_set_pts_test(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 pts_test = 0;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("\nInvalid cmd, please see below help:\n"
            "bt_pts_test [type]\n"
            "   [type]: 0: disable PTS test, 1: enable PTS test\n"));
        return CLIR_OK;
    }

    pts_test = _atoi(pps_argv[1]);

    if(pts_test != 0)
    {
        //c_btm_set_pts_mode(TRUE);
        DBG_LOG_PRINT(("Enable PTS mode\n"));
    }
    else
    {
        //c_btm_set_pts_mode(FALSE);
        DBG_LOG_PRINT(("Disable PTS mode\n"));
    }

    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_pin_code(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("set_pin [PIN_CODE]\n"));
        return CLIR_INV_ARG;
    }

    //c_btm_set_pin((char*)pps_argv[1]);

    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_ssp_mitm(INT32 i4_argc, const CHAR** pps_argv)
{
    //INT32 i4_mitm_mode = 0;
    #if 0
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("set_ssp_mitm [1|0], 1:MITM Required, 0:MITM Not Required\n"));
        return CLIR_INV_ARG;
    }

    i4_mitm_mode = _atoi(pps_argv[1]);

    //c_btm_setssp_mitm(i4_mitm_mode);
    #endif
    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_ssp_bonding(INT32 i4_argc, const CHAR** pps_argv)
{
    //INT32 i4_mitm_mode = 0;
    #if 0
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("set_ssp_bonding [2|1|0], 2:General Bonding, 1:Dedicated Bonding, 0:No Bounding\n"));
        return CLIR_INV_ARG;
    }

    i4_mitm_mode = _atoi(pps_argv[1]);

    //c_btm_setssp_bonding(i4_mitm_mode);
    #endif
    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_ssp_io_cap(INT32 i4_argc, const CHAR** pps_argv)
{
    //INT32 i4_io_cap = 0;
    #if 0
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("set_ssp_io_cap [0|1|2|3], 0:DisplayOnly, 1:DisplayYesNo, 2:KeyboardOnly, 3:NoInputNoOutput\n"));
        return CLIR_INV_ARG;
    }

    i4_io_cap = _atoi(pps_argv[1]);

    //c_btm_setssp_io_cap(i4_io_cap);
    #endif
    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_ssp_enable_devB(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("set_ssp_enable\n"));
        return CLIR_INV_ARG;
    }


    //mark_temp c_btm_spp_enable_devb((char*)pps_argv[1]);

    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_ssp_disable_devB(INT32 i4_argc, const CHAR** pps_argv)
{
    //INT32 i4_port_number = 0;
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("spp_disable_devb\n"));
        return CLIR_INV_ARG;
    }

    //i4_port_number = _atoi(pps_argv[1]);

    //mark_temp c_btm_spp_disable_devb((char*)pps_argv[1]);

    return CLIR_OK;
}

static INT32 _bluetooth_cli_rssi_set_map_table(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 ui1_idx = 0;
    INT32 ai4_rssi_map_table[BT_APP_RSSI_LEVEL_NUM] = {0};

    if (i4_argc != 6)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("rssi_set_map_table [level_1] [level_2] [level_3] [level_4] [level_5]\n"));
        return CLIR_INV_ARG;
    }

    for(ui1_idx = 0; ui1_idx < BT_APP_RSSI_LEVEL_NUM; ui1_idx++)
    {
        ai4_rssi_map_table[ui1_idx] = atoi(pps_argv[ui1_idx + 1]);
    }

    bt_app_set_rssi_map_table(ai4_rssi_map_table, BT_APP_RSSI_LEVEL_NUM);

    return CLIR_OK;
}

static INT32 _bluetooth_cli_rssi_show_map_table(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 ui1_idx = 0;
    INT32 ai4_rssi_map_table[BT_APP_RSSI_LEVEL_NUM] = {0};

    bt_app_get_rssi_map_table(ai4_rssi_map_table);

    for(ui1_idx = 0; ui1_idx < BT_APP_RSSI_LEVEL_NUM; ui1_idx++)
    {
        DBG_LOG_PRINT(("Level[%d]=%d\n", ui1_idx + 1, ai4_rssi_map_table[ui1_idx]));
    }

    return CLIR_OK;
}

static INT32 _bluetooth_cli_get_rssi(INT32 i4_argc, const CHAR** pps_argv)
{
    INT16 rssi_value;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, please see below help:\n"));
        DBG_LOG_PRINT(("get_rssi [MAC Address]\n"));
        return CLIR_INV_ARG;
    }
    c_btm_get_rssi((char*)pps_argv[1], &rssi_value);

    DBG_LOG_PRINT(("MAC Addr: %s", pps_argv[1]));
    DBG_LOG_PRINT(("RSSI value: %d", rssi_value));

    return CLIR_OK;
}

static INT32 _bluetooth_cli_spp_connect(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("spp_connect <MAC_ADDRESS> [optional:UUID]\n"));
        DBG_LOG_PRINT(("    Default UUID:00001101-0000-1000-8000-00805F9B34FB]\n"));
        return CLIR_INV_ARG;
    }

    if (3 == i4_argc)
    {
        //mark_temp c_btm_bt_spp_connect((char*)pps_argv[1], (char*)pps_argv[2]);
    }
    else if (2 == i4_argc)
    {
        //mark_temp c_btm_bt_spp_connect((char*)pps_argv[1], NULL);
    }
    else
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("spp_connect <MAC_ADDRESS> [optional:UUID]\n"));
        DBG_LOG_PRINT(("    Default UUID:00001101-0000-1000-8000-00805F9B34FB]\n"));
        return CLIR_INV_ARG;
    }

    return CLIR_OK;
}

static INT32 _bluetooth_cli_spp_disconnect(INT32 i4_argc, const CHAR** pps_argv)
{
    //UART_PORT port=0;

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("spp_disconnect <PortNum>\n"));
        return CLIR_INV_ARG;
    }

    //port = (UART_PORT)atoi((char*)pps_argv[1]);
    //mark_temp c_btm_bt_spp_disconnect(port);

    return CLIR_OK;
}

static INT32 _bluetooth_cli_spp_send_data(INT32 i4_argc, const CHAR** pps_argv)
{
    //UART_PORT port=0;
    INT32 i = 0;
    INT32 i4_data_len = 0;
    CHAR ps_spp_data[513] = {0};

    if(i4_argc < 3)
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("spp_send_data <PortNum> <String>\n"));
        return CLIR_INV_ARG;
    }

    //port = (UINT8)atoi((char*)pps_argv[1]);

    for(i = 2; i < i4_argc; i++)
    {
        i4_data_len += c_strlen(pps_argv[i]);
        if(i4_data_len >= 513)
        {
            DBG_LOG_PRINT(("ERR: The length of string must less than 513\n"));
            return CLIR_INV_ARG;
        }
        c_strncat(ps_spp_data, pps_argv[i], c_strlen(pps_argv[i]));
    }

    //mark_temp c_btm_bt_spp_send_data(ps_spp_data, i4_data_len, port);

    return CLIR_OK;
}

static INT32 _bluetooth_cli_spp_send_data_from_file(INT32 i4_argc, const CHAR** pps_argv)
{
    //UART_PORT port=0;

    if(i4_argc != 3)
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("spp_send_data_from <PortNum> <FILE_NAME>\n"));
        return CLIR_INV_ARG;
    }

    //port = (UINT8)atoi((char*)pps_argv[1]);

    //mark_temp c_btm_bt_spp_send_data_fromfilet((char*)pps_argv[2], port);

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bluetooth_cli_spp_enable_log
  *
  * Description  - The CLI to enable or disable SPP data log
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_cli_spp_enable_log(INT32 i4_argc, const CHAR** pps_argv)
{
    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("spp_enable_log [0|1], 0: disable spp log, 1: enable spp log\n"));
        return CLIR_INV_ARG;
    }

    if (c_strcmp(pps_argv[1], "0")== 0)
    {
        //bt_spp_enable_data_log(FALSE);
    }
    else
    {
        //bt_spp_enable_data_log(TRUE);
    }

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bluetooth_cli_spp_show_buf
  *
  * Description  - The CLI to show the data in SPP data buffer
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_cli_spp_show_buf(INT32 i4_argc, const CHAR** pps_argv)
{
    //bt_spp_show_spp_data_buf();

    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_nfc(INT32 i4_argc, const CHAR** pps_argv)
{
    return CLIR_OK;
}

static INT32 _bluetooth_cli_get_nfc(INT32 i4_argc, const CHAR** pps_argv)
{
    return CLIR_OK;
}

static INT32 _bluetooth_cli_set_virtual_sniffer(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("bt_set_vsniffer_log [on|off]\n"));
        return CLIR_INV_ARG;
    }

    if (c_strcmp(pps_argv[1], "on")== 0)
    {
        c_btm_set_virtual_sniffer(1);
    }
    else if (c_strcmp(pps_argv[1], "off")== 0)
    {
        c_btm_set_virtual_sniffer(0);
    }
    else
    {
        DBG_LOG_PRINT(("Invalid arguments, help:\n"));
        DBG_LOG_PRINT(("bt_set_vsniffer_log [on|off]\n"));
        return CLIR_INV_ARG;
    }

    return CLIR_OK;
}

/*for bluetooth ATE API*/
#define BLUETOOTH_ATE_COMMAND "sh /usr/sbin/btate"
static INT32 _bluetooth_cli_ate_init(INT32 i4_argc, const CHAR** pps_argv)
{
    #if 0  //just fix for logically dead code
    BOOL fg_power;
    fg_power = 0; //c_btm_get_power_status();
    if(fg_power)
    {
        a_mtkapi_bt_gap_stop_inquiry_scan(FALSE, FALSE);
        //c_btm_set_pairable_sync(FALSE);
        c_thread_delay(500);
    }
    else
    #endif
    {
        c_btm_bluetooth_on_off(TRUE);
        c_thread_delay(500);
        a_mtkapi_bt_gap_stop_inquiry_scan(FALSE, FALSE);
        //c_btm_set_pairable_sync(FALSE);
        c_thread_delay(500);
    }
    return 0;
}

static INT32 _bluetooth_cli_ate_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
#if 0
    int i = 0;
    char ps_ate_cmd[256];

    if ( i4_argc < 3 )
    {
        DBG_LOG_PRINT(("Invalid parameter\n"));
        DBG_LOG_PRINT(("bt_ate_cmd [test case][start|stop][parameters...]\n"));
        DBG_LOG_PRINT(("bt_ate_cmd 2 1 0x03 16 0xaabbccddeeff 1 2 3\n"));
        return 0;
    }
    //a_mtkapi_bt_gap_stop_inquiry_scan(FALSE, FALSE);

    if(3 == atoi(pps_argv[1]))
    {
        if(1 == atoi(pps_argv[2]))
        {
            c_btm_start_inquiry_scan(0, NULL);
        }
        else if(0 == atoi(pps_argv[2]))
        {
            a_mtkapi_bt_gap_stop_inquiry_scan();
        }
        else
        {
            DBG_LOG_PRINT(("Invalid parameter\n"));
            DBG_LOG_PRINT(("bt_ate_cmd 3 [1|0]\n"));
        }
        return CLIR_OK;
    }

    c_memset(ps_ate_cmd, 0, sizeof(ps_ate_cmd));
    c_strncpy(ps_ate_cmd, BLUETOOTH_ATE_COMMAND, c_strlen(BLUETOOTH_ATE_COMMAND));
    for(i=0;i<i4_argc;i++)
    {
        c_strncat(ps_ate_cmd, " ", c_strlen(" "));
        c_strncat(ps_ate_cmd, pps_argv[i+1], MIN((255 - c_strlen(ps_ate_cmd)),c_strlen(pps_argv[i+1])));
    }
    //ps_ate_cmd[255] = '\0';
    DBG_LOG_PRINT(("ps_ate_cmd:%s\n", ps_ate_cmd));

    //execl("/bin/sh", BLUETOOTH_ATE_COMMAND, NULL);
#endif
    return CLIR_OK;
}

static INT32 _bluetooth_cli_ant_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
#if 0
    INT32 i4_enable = 0;

    if(i4_argc != 2)
    {
        DBG_LOG_PRINT(("input error\n"));
        DBG_LOG_PRINT(("input error\n"));
        return -1;
    }
    else
    {
        if(NULL == pps_argv[1])
        {
            return 0;
        }

        i4_enable = (INT32)atol(pps_argv[1]);
        if(0 == i4_enable)
        {
            system("./usr/local/bin/iwpriv ra0 set ant=2");
        }
        else
        {
            system("./usr/local/bin/iwpriv ra0 set ant=3");
        }
    }
#endif
    return CLIR_OK;
}

static INT32 _bluetooth_cli_nfc_cmd(INT32 i4_argc, const CHAR** pps_argv)
{
    BT_APP_MSG_T t_bt_msg = {0};
    t_bt_msg.msg_type = BT_APP_MSG_IFCON_CMD_NFC_START;
    INT32 i4_ret = CLIR_OK;
    //t_bt_msg.ui4_msg_id = IFCON_NFC_CMD_START_VALID;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != CLIR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send BT_APP_MSG_IFCON_CMD_NFC_START fail, %d\n", i4_ret));
    }


    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_start_a2dp_snk_scan
  *
  * Description  - CLI: start inquiry scan to find the devices which have A2DP Sink capability.
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_start_a2dp_snk_scan(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32   i4_ret = BT_APPR_OK;

    // start pairing mode
    //i4_ret = c_btm_btstart("PAIRING", 0);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : PAIRING fail %d\n", i4_ret));
        return CLIR_OK;
    }

    bt_app_start_a2dp_snk_inquiry_scan(TIME_OUT_SINK_DEVICE_GUI_SCAN);

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_stop_a2dp_snk_scan
  *
  * Description  - CLI: stop A2DP Sink device inquiry scan.
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_stop_a2dp_snk_scan(INT32 i4_argc, const CHAR** pps_argv)
{
    bt_app_stop_a2dp_snk_inquiry_scan();

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_show_a2dp_snk_dev
  *
  * Description  - CLI: show the discoverable devices which have A2DP Sink capability.
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_show_a2dp_snk_dev(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT32 ui4_num = 0;
    UINT32 ui4_index = 0;
    BT_APP_REMOTE_DEV_T* pt_devs = NULL;

    ui4_num = bt_app_get_a2dp_snk_dev_num();
    if(ui4_num <= 0)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> have not start scan or have not found device\n"));
        return CLIR_OK;
    }

    // Create buffer
    pt_devs = (BT_APP_REMOTE_DEV_T *)c_mem_alloc(ui4_num * sizeof(BT_APP_REMOTE_DEV_T));
    if(NULL == pt_devs)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: alloc mem fail\n"));
        return CLIR_OK;
    }

    ui4_index = bt_app_get_all_a2dp_snk_devs(pt_devs, ui4_num);
    if(ui4_index < ui4_num)
    {
        ui4_num = ui4_index;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> A2DP SNK device num: %d\n\n", ui4_num));
    for(ui4_index=0; ui4_index<ui4_num; ui4_index++)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ------------------------------------\n"));
        BT_APP_LOG_DEFAULT(("<BT_APP> Name: %s\n", pt_devs[ui4_index].r_bt_device_info.ac_name));
        BT_APP_LOG_DEFAULT(("<BT_APP> Addr: %s\n", pt_devs[ui4_index].r_bt_device_info.ac_addr));
        BT_APP_LOG_DEFAULT(("<BT_APP> CoD : 0x%x\n", pt_devs[ui4_index].r_bt_device_info.ui4_cod));
        BT_APP_LOG_DEFAULT(("<BT_APP> CoD : 0x%x\n", pt_devs[ui4_index].r_bt_device_info.ui4_service));
        BT_APP_LOG_DEFAULT(("<BT_APP> Stat: %d\n", pt_devs[ui4_index].r_bt_device_info.e_status));
        BT_APP_LOG_DEFAULT(("<BT_APP> RSSI Level:%d\n", pt_devs[ui4_index].r_bt_device_info.e_rssi_level));
        BT_APP_LOG_DEFAULT(("<BT_APP> ------------------------------------\n"));
    }

    if(pt_devs != NULL)
    {
        c_mem_free(pt_devs);
        pt_devs = NULL;
    }

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_simulate_detect_sink_dev
  *
  * Description  - CLI:
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_simulate_detect_sink_dev(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_ret = BT_APPR_OK;
    UINT8 u1_index = 0;
    UINT8 u1_detected_num = 0;
    char name[3] = "00";
    char addr[18] = "00:00:00:00:00:00";
    BT_GAP_SCAN_RESULT  ar_detected_dev_list[19];

    u1_detected_num = (UINT8)atoi(pps_argv[1]);
    if (u1_detected_num > 19)
    {
        u1_detected_num = 19;
    }

    if (i4_argc != 2)
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("send_dev [num]\n"));
        return CLIR_INV_ARG;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Simulate detect sink device\n"));


    /*0. Free old detected sink device list */
    _bt_app_free_a2dp_snk_dev_list();

    /* Set unpaired device number to 0 */
    bt_app_ui_sink_device_list_unpaired_info_clear();

    /* init A2DP Sink device list */
    _bt_app_init_a2dp_snk_dev_list();


    c_memset(ar_detected_dev_list, 0, 19 * sizeof(BT_GAP_SCAN_RESULT));

    for (u1_index = 0; u1_index < 19; u1_index++)
    {
        if (u1_index >= 0 && u1_index < 10)
        {
            name[0] = '0';
            name[1] = '0' + u1_index;

            addr[15] = '0';
            addr[16] = '0' + u1_index;

        }
        else if (u1_index >= 10 && u1_index < 20)
        {
            name[0] = '1';
            name[1] = '0' + u1_index - 10;

            addr[15] = '1';
            addr[16] = '0' + u1_index - 10;
        }

        c_strncpy(ar_detected_dev_list[u1_index].name, name, MAX_NAME_LEN -1);
        c_strncpy(ar_detected_dev_list[u1_index].bdAddr, addr, MAX_BDADDR_LEN-1);
        ar_detected_dev_list[u1_index].isPaired = 0;

    }

    for (u1_index = 0; u1_index < u1_detected_num; u1_index++)
    {
        _bt_app_a2dp_snk_inquiry_response_cbk_fct(&ar_detected_dev_list[u1_index]);
    }

    return i4_ret;

}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_absolute_volume_cbk
  *
  * Description  - CLI: Simulate SRC register notification command of Event_Volume_Changed.
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_absolute_volume_cbk(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 u1_absolute_volume = 0;
    INT16 u1_flag = 0;

    if (i4_argc != 3)
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("absolute_volume_cmd [Type] [Volume]\n"));
        DBG_LOG_PRINT(("[Type]  1: Get volume 2: Set volume\n"));
        DBG_LOG_PRINT(("[Volume]: Specify volume percentage when Type is 2, any value when Type is 1\n"));
        return CLIR_INV_ARG;
    }

    u1_flag = (INT16)atoi(pps_argv[1]);
    u1_absolute_volume = (UINT8)atoi(pps_argv[2]);

    bluetooth_absolute_volume_cmd_cbk(u1_flag, &u1_absolute_volume);

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_avrcp_cmd_cbk
  *
  * Description  - CLI: Simulate SRC send AVRCP key command.
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_avrcp_cmd_cbk(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 u1_cmd_type = 0;
    UINT8 u1_press = 0;

    if (i4_argc != 3)
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("src_avrcp_cmd [Cmd_Type] [Press]\n"));
        DBG_LOG_PRINT(("[Cmd_Type] 0:PLAY 1:PAUSE 2:NEXT 3:PREV 4:FF 5:FR 6:STOP\n"));
        DBG_LOG_PRINT(("[Press] 1:Press key 2:Release key\n"));
        return CLIR_INV_ARG;
    }

    u1_cmd_type = (UINT8)atoi(pps_argv[1]);
    u1_press = (UINT8)atoi(pps_argv[2]);

    if (!((u1_cmd_type >= 0 && u1_cmd_type <= 6) && (u1_press >= 0 && u1_press <= 1)))
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("src_avrcp_cmd [Cmd_Type] [Press]\n"));
        DBG_LOG_PRINT(("[Cmd_Type] 0:PLAY 1:PAUSE 2:NEXT 3:PREV 4:FF 5:FR 6:STOP\n"));
        DBG_LOG_PRINT(("[Press] 1:Press key 2:Release key\n"));
        return CLIR_INV_ARG;
    }

    bluetooth_avrcp_cmd_cbk(u1_cmd_type, u1_press);

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_bluetooth_mode
  *
  * Description  - CLI: Set or get bluetooth mode.
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_bluetooth_mode(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 u1_bt_mode = 0;
    UINT8 u1_cmd_type = 0;

    u1_cmd_type = (UINT8)atoi(pps_argv[1]);
    u1_bt_mode = (UINT8)atoi(pps_argv[2]);

    if (!(((i4_argc == 2) && (u1_cmd_type == 0))
        || ((i4_argc == 3) && (u1_cmd_type == 1) && (u1_bt_mode >= 0) && (u1_bt_mode <= 3))))
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("bt_mode [cmd_type] <mode>\n"));
        DBG_LOG_PRINT(("[cmd_type] 0: get internal bt mode, 1: set internal bt mode\n"));
        DBG_LOG_PRINT(("[mode] 0:SNK mode, 1:SRC/SNK mode, 2:OFF 3:SRC mode\n"));
        return CLIR_INV_ARG;
    }

    switch (u1_cmd_type)
    {
        case 0:
            u1_bt_mode = a_bt_bluetooth_mode_get();
            DBG_INFO(("Internal bluetooth mode:%d\n",u1_bt_mode));
            break;
        case 1:
            a_bt_bluetooth_mode_set(u1_bt_mode);
            break;
        default:
            break;
    }

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_bluetooth_enable_disable
  *
  * Description  - CLI: control bluetooth RF
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_bluetooth_enable_disable(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 u1_cmd_type = 0;

    u1_cmd_type = (UINT8)atoi(pps_argv[1]);

    if ((i4_argc != 2) || (u1_cmd_type != 0 && u1_cmd_type != 1))
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("bt_enable [cmd_type]\n"));
        DBG_LOG_PRINT(("[cmd_type] 0: Disalbe bt, 1: Enable bt\n"));
        return CLIR_INV_ARG;
    }

    switch (u1_cmd_type)
    {
        case 0:
            a_bt_enable_disable(FALSE);
            break;
        case 1:
            a_bt_enable_disable(TRUE);
            break;
        default:
            break;
    }

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_sink_device_list_test_ctrl
  *
  * Description  - CLI:
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_sink_device_list_test_ctrl(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 u1_action = 0;

    u1_action = (UINT8)atoi(pps_argv[1]);

    if ((i4_argc != 2) || (u1_action != 0 && u1_action != 1))
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("snklist [action]\n"));
        DBG_LOG_PRINT(("[action] 0: Close sink device list, 1: Open sink device list\n"));
        return CLIR_INV_ARG;
    }

    switch (u1_action)
    {
        case 0:
            bluetooth_audio_output_device_list_close();
            break;
        case 1:
            bluetooth_audio_output_device_list_start();
            break;
        default:
            break;
    }

    return CLIR_OK;
}

static INT32 _bluetooth_cli_iplib_info_get(INT32 i4_argc, const CHAR** pps_argv)
{
    char ac_iplib_info[16] = {0};

    if (i4_argc > 1)
    {
        DBG_LOG_PRINT(("Invalid command, help:\n"));
        DBG_LOG_PRINT(("iplib_get_info\n"));
        return CLIR_INV_ARG;
    }

    DBG_LOG_PRINT(("iplib information:\n"));

    c_memset(ac_iplib_info, 0, 16);
    //bluetooth_iplib_get_fw_version(ac_iplib_info);
    DBG_LOG_PRINT(("FW Version:%s\n",ac_iplib_info));

    c_memset(ac_iplib_info, 0, 16);
    //bluetooth_iplib_get_hw_version(ac_iplib_info);
    DBG_LOG_PRINT(("HW Version:%s\n",ac_iplib_info));

    c_memset(ac_iplib_info, 0, 16);
    //bluetooth_iplib_get_name(ac_iplib_info);
    DBG_LOG_PRINT(("Accessary Name:%s\n",ac_iplib_info));

    c_memset(ac_iplib_info, 0, 16);
    //bluetooth_iplib_get_model(ac_iplib_info);
    DBG_LOG_PRINT(("Model:%s\n",ac_iplib_info));

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_bluetooth_key_trigger
  *
  * Description  - CLI: trigger bluetooth trigger
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_bluetooth_key_trigger(INT32 i4_argc, const CHAR** pps_argv)
{
    bluetooth_audio_output_connect_start();
    return CLIR_OK;
}

static INT32 _bt_app_cli_bluetooth_video_delay(INT32 i4_argc, const CHAR** pps_argv)
    {
        //UINT8 cmd_type;
        //UINT32 u4DelayMs;

        //cmd_type = (UINT8)atoi(pps_argv[1]);
        //u4DelayMs = (UINT32)atoi(pps_argv[2]);

        return CLIR_OK;
    }


/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_hid_register
  *
  * Description  - CLI: register one wireless controller
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_hid_register(INT32 i4_argc, const CHAR** pps_argv)
{
    bluetooth_hid_register_start();

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_get_hid_list
  *
  * Description  - CLI:get hid device list
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_get_hid_list(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT8 connect_stauts_confirm = 0x00;
    UINT8 first_index, second_index, i;
    BT_HID_TARGET_DEV_LIST pt_device_list;
    BT_TARGET_HID_LIST list;
    BT_HID_STATUS_STRUCT_LIST pt_device_status;

    c_memset(&pt_device_list, 0, sizeof(BT_HID_TARGET_DEV_LIST));
    c_memset(&pt_device_status, 0, sizeof(BT_HID_STATUS_STRUCT_LIST));

    connect_stauts_confirm = c_btm_get_paired_hid_dev_list(&pt_device_list, &pt_device_status);

    first_index = (UINT8)(connect_stauts_confirm & 0x0F);
    second_index = (UINT8)((connect_stauts_confirm & 0xF0)>>4);

    BT_APP_LOG_DEFAULT(("<BT_APP> first_index=%d second_index=%d\n",
                                                first_index,
                                                second_index));

    BT_APP_LOG_DEFAULT(("<BT_APP> HID device num=%d\n",
                                                pt_device_list.dev_num));

    for(i=0; i<pt_device_list.dev_num; i++)
    {
        strncpy(list.hid_list[i].bdAddr, pt_device_list.device_list[i].bdAddr, (MAX_BDADDR_LEN-1));

        list.hid_list[i].ccState = pt_device_status.device_list[i].status;
#if 0
        if(i==(first_index -1))
        {
            list.hid_list[i].ccState = BT_HID_CONN_STATE_FIRST;
        }
        else if(i==(second_index -1))
        {
            list.hid_list[i].ccState = BT_HID_CONN_STATE_SECOND;
        }
        else
        {
            list.hid_list[i].ccState = BT_HID_CONN_STATE_REGISTERED;
        }
#endif
        BT_APP_LOG_DEFAULT(("<BT_APP> HID Addr=%s ccState=%d\n",
                                                list.hid_list[i].bdAddr, list.hid_list[i].ccState));
    }

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_cli_hid_operation
  *
  * Description  - CLI: wireless controller operation(turn off/remove one/remove all)
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_cli_hid_operation(INT32 i4_argc, const CHAR** pps_argv)
{
    CHAR bt_addr[18];
    UINT8 u1_action = 0;

    strncpy(bt_addr, pps_argv[1], 17);
    bt_addr[17] = '\0';

    u1_action = (UINT8)atoi(pps_argv[2]);

    if ((i4_argc != 3) || (u1_action != 0 && u1_action != 1 && u1_action != 2))
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("hid_ctrl [mac_addr] [action]\n"));
        DBG_LOG_PRINT(("[action] 0: turn off, 1: remove one 2:remove all\n"));
        return CLIR_INV_ARG;
    }

    bluetooth_hid_wireless_controller_operation(bt_addr, u1_action);

    return CLIR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bluetooth_scan_hid_and_a2dp_cli
  *
  * Description  - CLI: scan A2DP & HID device
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_scan_hid_and_a2dp_cli(INT32 i4_argc, const CHAR **pps_argv)
{
    INT32 a2dp_type = 0;
    INT32 hid_type = 0;
    UINT32 time_out = 0;

    if(i4_argc != 4)
    {
        BT_APP_LOG_ERR(("A parameter is required!\n"));
        return -1;
    }
    else
    {
        a2dp_type = atoi(pps_argv[1]);
        hid_type = atoi(pps_argv[2]);
        time_out = atoi(pps_argv[3]);

        if(( 1 == a2dp_type) && (0 == hid_type))
        {
            c_btm_start_inquiry_scan(BT_INQUIRY_FILTER_TYPE_A2DP_SNK,_bt_app_a2dp_snk_inquiry_response_cbk_fct);
        }
        else if((0 == a2dp_type) && (1 == hid_type))
        {
            c_btm_start_inquiry_scan(0,_bt_app_a2dp_snk_inquiry_response_cbk_fct);
        }
        else if((1 == a2dp_type) && (1 == hid_type))
        {
            c_btm_start_inquiry_scan(0,_bt_app_a2dp_snk_inquiry_response_cbk_fct);
        }
        else
        {
            BT_APP_LOG_ERR(("Invalid required!\n"));
        }

    BT_APP_LOG_DEFAULT(("<BT_APP> Start keyboard&mouse scaning...\n"));

        /* Free old detected sink device list */
        _bt_app_free_a2dp_snk_dev_list();

        // clear paired sink devices scanning status before start new scanning
        bt_app_ui_sink_device_list_paired_dev_scanning_status_clear();

        /* set flag indicate scaning is started */
        bt_app_set_flag_sink_dev_scaning(TRUE);

        /* create scan timer */
        bt_app_create_sink_device_scan_timer();

        /* start scan timer, time out 15s */
        bt_app_start_sink_device_scan_timer(time_out);

        /* init A2DP Sink device list */
        _bt_app_init_a2dp_snk_dev_list();
    }
    return 0;
}


INT32 bluetooth_scan_hid_and_a2dp_cli(VOID)
{
    //INT32 a2dp_type = 0;
    //INT32 hid_type = 0;
    UINT32 time_out = 0;

    //a2dp_type = 1;
    //hid_type = 1;
    time_out = 15000;
#if 0
    if(( 1 == a2dp_type) && (0 == hid_type))
    {
        c_btm_start_inquiry_scan(BT_INQUIRY_FILTER_TYPE_A2DP_SNK,_bt_app_a2dp_snk_inquiry_response_cbk_fct);
    }
    else if((0 == a2dp_type) && (1 == hid_type))
    {
        c_btm_start_inquiry_scan(0,_bt_app_a2dp_snk_inquiry_response_cbk_fct);
    }
    else if((1 == a2dp_type) && (1 == hid_type))
    {
        c_btm_start_inquiry_scan(0,_bt_app_a2dp_snk_inquiry_response_cbk_fct);
    }
    else
    {
        BT_APP_LOG_ERR(("Invalid required!\n"));
    }
#endif
    c_btm_start_inquiry_scan(0,_bt_app_a2dp_snk_inquiry_response_cbk_fct);
    BT_APP_LOG_DEFAULT(("<BT_APP> Start keyboard&mouse scaning...\n"));

    /* Free old detected sink device list */
    _bt_app_free_a2dp_snk_dev_list();

    // clear paired sink devices scanning status before start new scanning
    bt_app_ui_sink_device_list_paired_dev_scanning_status_clear();

    /* set flag indicate scaning is started */
    bt_app_set_flag_sink_dev_scaning(TRUE);

    /* create scan timer */
    bt_app_create_sink_device_scan_timer();

    /* start scan timer, time out 15s */
    bt_app_start_sink_device_scan_timer(time_out);

    /* init A2DP Sink device list */
    _bt_app_init_a2dp_snk_dev_list();

    return 0;
}


/**---------------------------------------------------------------------------
  * Name          - _bluetooth_pts_enable_disable_cli
  *
  * Description  -
  *---------------------------------------------------------------------------*/
static INT32 _bluetooth_pts_enable_disable_cli(INT32 i4_argc, const CHAR **pps_argv)
{
    UINT8 u1_cmd_type = 0;

    u1_cmd_type = (UINT8)atoi(pps_argv[1]);

    if ((i4_argc != 2) || (u1_cmd_type != 0 && u1_cmd_type != 1))
    {
        DBG_LOG_PRINT(("Invalid command, Help:\n"));
        DBG_LOG_PRINT(("pts_enable [cmd_type]\n"));
        DBG_LOG_PRINT(("[cmd_type] 0: Disalbe bt, 1: Enable bt\n"));
        return CLIR_INV_ARG;
    }

    switch (u1_cmd_type)
    {
        case 0:
            bt_app_set_pts_enable(FALSE);
            break;
        case 1:
            bt_app_set_pts_enable(TRUE);
            break;
        default:
            break;
    }

    return CLIR_OK;

}

// Bluetooth command cli in normal mode
static CLI_EXEC_T at_bluetooth_cmd_tbl[] =
{
    {"gdl", "gdl", _bluetooth_cli_get_dbg_level, NULL, CLI_GET_DBG_LVL_HELP_STR, CLI_GUEST},
    {"sdl", "sdl", _bluetooth_cli_set_dbg_level, NULL, CLI_SET_DBG_LVL_HELP_STR, CLI_GUEST},
    {"bt_set_level", NULL, _bluetooth_cli_set_mw_dbg_level, NULL, "Set MW debug level", CLI_GUEST},
    {"btmw_test", NULL, _bluetooth_cli_btmw_test, NULL, "use btmw test cli", CLI_GUEST},
    {"bt_init", NULL, _bluetooth_cli_init, NULL, "bluetooth_init", CLI_GUEST},
    {"bt_start", NULL, _pbk_bt_start, NULL, "bluetooth_pbk_audio_input_start", CLI_GUEST},
    {"bt_stop", NULL, _pbk_bt_stop, NULL, "bluetooth_pbk_audio_input_stop", CLI_GUEST},
    {"bt_pair", NULL, _bluetooth_cli_pair, NULL, "try to pair with BT device", CLI_GUEST},
    {"bt_mode_get", NULL, _pbk_bt_mode_get, NULL, "bluetooth_audio_input_mode_get", CLI_GUEST},
    {"bt_local_info_get", NULL, _pbk_bt_locla_device_info_get, NULL, "Show BT local device info",CLI_GUEST},
    {"bt_local_name_set", NULL, _bluetooth_local_device_name_set, NULL, "set bluetooth local device name and send it to ifcon", CLI_GUEST},
    {"bt_paired_list_get", NULL, _bluetooth_paired_list_get, NULL, "Show all paired devices", CLI_GUEST},
    {"bt_device_erase", NULL, _bluetooth_paired_device_erase, NULL, "erase one paired device", CLI_GUEST},
    {"bt_device_erase_all", NULL, _bluetooth_paired_device_erase_all, NULL, "erase all paired device", CLI_GUEST},
    {"bt_remote_device_get", NULL, _bluetooth_remote_device_get, NULL, "bluetooth_remote_device_get", CLI_GUEST},
    {"bt_play_status_get", NULL, _bluetooth_audio_control_play_status_get, NULL, "get play status", CLI_GUEST},
    {"bt_play_capabilities", NULL, _bluetooth_avrcp_get_capabilities_cli, NULL, "bt_play_capabilities [companyid|events]", CLI_GUEST},
    {"bt_play_abortrsp", NULL, _bluetooth_avrcp_enable_abortrsp_cli, NULL, "bt_play_abortrsp [enable|disable]", CLI_GUEST},
    {"bt_cmd_cc", NULL, _bluetooth_connect_audio_sources_cli, NULL, "bt_cmd_cc mac [a2dp|avctp]", CLI_GUEST},
    {"bt_cmd_dc", NULL, _bluetooth_disconnect_audio_sources_cli, NULL, "bt_cmd_dc [a2dp|avctp]", CLI_GUEST},
    {"bt_reg_avrcp_notification", NULL, _bluetooth_reg_avrcp_notification_cli, NULL, "bt_reg_avrcp_notification [ps|trackChange]", CLI_GUEST},
    {"bt_cmd_send", NULL, _bluetooth_avrcp_command_send, NULL, "send AVRCP cmd", CLI_GUEST},
    {"cmdv", NULL, _bluetooth_cmdv_send_sircs, NULL, "Sircs Command for BDV", CLI_ADMIN},
    {"volume", NULL, _bluetooth_cli_change_volume, NULL, "change volume", CLI_ADMIN},
    {"dec_aac", NULL, _bluetooth_decoder_aac, NULL, "decoder aac file", CLI_GUEST},
    {"bt_pts_test", NULL, _bluetooth_set_pts_test, NULL, "Enable or disable PTS mode", CLI_GUEST},

    {"set_pin", NULL, _bluetooth_cli_set_pin_code, NULL, "set pin code", CLI_GUEST},

    {"rssi_set_map_table", NULL, _bluetooth_cli_rssi_set_map_table, NULL, "Set RSSI map table", CLI_GUEST},
    {"rssi_show_map_table", NULL, _bluetooth_cli_rssi_show_map_table, NULL, "Show RSSI map table", CLI_GUEST},
    {"get_rssi", NULL, _bluetooth_cli_get_rssi, NULL, "get Received Signal Strengh Indication", CLI_GUEST},

    {"set_ssp_mitm", NULL, _bluetooth_cli_set_ssp_mitm, NULL, "MITM protection is required or not", CLI_GUEST},
    {"set_ssp_bonding", NULL, _bluetooth_cli_set_ssp_bonding, NULL, "set SSP Bonding mode", CLI_GUEST},
    {"set_ssp_io_cap", NULL, _bluetooth_cli_set_ssp_io_cap, NULL, "set SSP io capabilities", CLI_GUEST},
    {"spp_connect", NULL, _bluetooth_cli_spp_connect, NULL, "establish spp connection", CLI_GUEST},
    {"spp_disconnect", NULL, _bluetooth_cli_spp_disconnect, NULL, "disconnect spp connection", CLI_GUEST},
    {"spp_send_data", NULL, _bluetooth_cli_spp_send_data, NULL, "send data by spp connection", CLI_GUEST},
    {"spp_send_data_from", NULL, _bluetooth_cli_spp_send_data_from_file, NULL, "send SPP data from file", CLI_GUEST},
    {"spp_enable_devb", NULL, _bluetooth_cli_set_ssp_enable_devB, NULL, "enable spp devB", CLI_GUEST},
    {"spp_disable_devb", NULL, _bluetooth_cli_set_ssp_disable_devB, NULL, "spp_disable_devb [port]", CLI_GUEST},
    {"spp_enable_log", NULL, _bluetooth_cli_spp_enable_log, NULL, "enable or disable SPP data log", CLI_GUEST},
    {"spp_show_buf", NULL, _bluetooth_cli_spp_show_buf, NULL, "Show the data in SPP data buf", CLI_GUEST},

    {"set_nfc", NULL, _bluetooth_cli_set_nfc, NULL, "Set nfc", CLI_GUEST},
    {"get_nfc", NULL, _bluetooth_cli_get_nfc, NULL, "Show nfc setting", CLI_GUEST},
    {"bt_set_vsniffer_log", NULL, _bluetooth_cli_set_virtual_sniffer, NULL, "enable/disable vsniffer log", CLI_GUEST},
    {"bt_ate_init", NULL, _bluetooth_cli_ate_init, NULL, "bt_ate_init, init bluetooth", CLI_GUEST},
    {"bt_ate_cmd", NULL, _bluetooth_cli_ate_cmd, NULL, "bt_ate_cmd [test case][start|stop][parameters...]", CLI_GUEST},
    {"bt_ate_ant", NULL, _bluetooth_cli_ant_cmd, NULL, "bt_ate_ant [0|1], 0:main ant, 1:sub ant", CLI_GUEST},
    {"nfc_cmd", NULL, _bluetooth_cli_nfc_cmd, NULL, "nfc cmd", CLI_GUEST},

    {"a2dp_snk_start_scan", NULL, _bt_app_cli_start_a2dp_snk_scan, NULL, "start A2DP Sink device inquiry scan", CLI_GUEST},
    {"a2dp_snk_stop_scan", NULL, _bt_app_cli_stop_a2dp_snk_scan, NULL, "stop A2DP Sink device inquiry scan", CLI_GUEST},
    {"a2dp_snk_dev_show", NULL, _bt_app_cli_show_a2dp_snk_dev, NULL, "show  A2DP discoverable Sink device", CLI_GUEST},
    {"send_dev", NULL, _bt_app_cli_simulate_detect_sink_dev, NULL, "Simulate detected sink device", CLI_GUEST},
    {"absolute_volume_cmd", NULL, _bt_app_cli_absolute_volume_cbk, NULL, "Simulate SRC send Set/Get absolute volume command", CLI_GUEST},
    {"src_avrcp_cmd", NULL, _bt_app_cli_avrcp_cmd_cbk, NULL, "Simulate SRC send AVRCP key command", CLI_GUEST},
    {"bt_mode", NULL, _bt_app_cli_bluetooth_mode, NULL, "Set/Get internal bluetooth mode", CLI_GUEST},
    {"snklist", NULL, _bt_app_cli_sink_device_list_test_ctrl, NULL, "Open/Close sink device list", CLI_GUEST},
    {"bt_enable", NULL, _bt_app_cli_bluetooth_enable_disable, NULL, "Enable/Disable bluetooth", CLI_GUEST},
    {"iplib_get_info", NULL, _bluetooth_cli_iplib_info_get, NULL, "iplib get information", CLI_GUEST},

    {"bluetooth_key", NULL, _bt_app_cli_bluetooth_key_trigger, NULL, "trigger bluetooth key", CLI_GUEST},
    {"set_video_delay", NULL, _bt_app_cli_bluetooth_video_delay, NULL, "set video delay", CLI_GUEST},
    {"hid_rg", NULL, _bt_app_cli_hid_register, NULL, "register one hid", CLI_GUEST},
    {"hid_get_list", NULL, _bt_app_cli_get_hid_list, NULL, "get hid list", CLI_GUEST},
    {"hid_ctrl", NULL, _bt_app_cli_hid_operation, NULL, "wireless controller operation", CLI_GUEST},
    {"scan_a2dp_and_hid", NULL, _bluetooth_scan_hid_and_a2dp_cli, NULL, "scan hid and a2dp device", CLI_GUEST},
    {"pts_enable", NULL, _bluetooth_pts_enable_disable_cli, NULL, "Enable/ Disable PTS", CLI_GUEST},
    END_OF_CLI_CMD_TBL
};


// The directory for Bluetooth commands in normal mode
static CLI_EXEC_T at_bluetooth_cmd_root[] =
{
    // The abbreviation cannot be "bt". because "bt" is used in DBG mode
    {"bluetooth", NULL, NULL, at_bluetooth_cmd_tbl, "Bluetooth commands", CLI_GUEST},
    END_OF_CLI_CMD_TBL
};

#if 0
// Bluetooth command cli in DBG mode
static CLI_EXEC_T at_bluetooth_cmd_dbg_tbl[] =
{
    {"bt_set_level", "sdl", _bluetooth_cli_set_mw_dbg_level, NULL, "Set log level", CLI_GUEST},
    {"bt_local_name_set", NULL, _bluetooth_local_device_name_set, NULL, "Set local name", CLI_GUEST},
    {"bt_local_name_save", NULL, _bluetooth_local_device_name_set, NULL, "Save local name", CLI_GUEST},
    {"bt_meta_data_get", NULL, _bluetooth_audio_control_meta_data_get, NULL, "Get meta data", CLI_GUEST},
    {"bt_play_status_get", NULL, _bluetooth_audio_control_play_status_get, NULL, "Get play status", CLI_GUEST},
    {"bt_cmd_cc", NULL, _bluetooth_connect_audio_sources_cli, NULL, "cc", CLI_GUEST},
    {"bt_cmd_dc", NULL, _bluetooth_disconnect_audio_sources_cli, NULL, "dc", CLI_GUEST},
    {"bt_cmd_send", NULL, _bluetooth_avrcp_command_send, NULL, "Send cmd", CLI_GUEST},
    {"bt_set_vsniffer_log", NULL, _bluetooth_cli_set_virtual_sniffer, NULL, "enable/disable vsniffer log", CLI_HIDDEN},

    END_OF_CLI_CMD_TBL
};

// The directory for Bluetooth commands in DBG mode

static CLI_EXEC_T at_bluetooth_dbg_root[] = {
    {"bt", NULL, NULL, at_bluetooth_cmd_dbg_tbl, "Bluetooth Debug Commands", CLI_GUEST},
    END_OF_CLI_CMD_TBL
};
#endif

/**-----------------------------------------------------------------------------
  * Name          - bluetooth_cli_attach_cmd_tbl
  *
  * Description  - attaches bluetooth comand table to CLI
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
VOID bluetooth_cli_attach_cmd_tbl(VOID)
{
#ifdef CLI_SUPPORT

    INT32 i4_ret = 0;

    // attach bluetooth command cli in normal mode
    i4_ret = c_cli_attach_cmd_tbl(at_bluetooth_cmd_root, CLI_CAT_APP, CLI_GRP_GUI);
    if (i4_ret != CLIR_NOT_INIT && i4_ret != CLIR_OK)
    {
        DBG_LOG_PRINT(("<BT_APP> ERR: attach BT cmd failed, %d\n", i4_ret));
    }

    // attach bluetooth command cli in DBG mode.
    //i4_ret = c_cli_attach_cmd_tbl(at_bluetooth_dbg_root, CLI_CAT_APP, CLI_GRP_GUI);
    //if (i4_ret != CLIR_NOT_INIT && i4_ret != CLIR_OK)
    //{
        //DBG_LOG_PRINT(("<BT_APP> ERR: attach dbg BT cmd failed, %d\n", i4_ret));
    //}

#endif
}

#endif


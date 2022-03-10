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
 * $RCSfile: bluetooth_msgproc.c,v $
 * $Revision: #8 $
 * $Date: 2015/11/19 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file implements normal msgproc for bluetooth.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

/*-----------------------------------------------------------------------------
                        include files
-----------------------------------------------------------------------------*/
#include "u_cli.h"

/* application level */
#include "amb/a_amb.h"
#include "am/a_am.h"
#include "app_util/a_common.h"
#include "a_cfg.h"
#include "agent/a_agent.h"

#include "bluetooth.h"
#include "bluetooth_msgproc.h"
#include "bluetooth_spp.h"
#include "bluetooth_device.h"
#include "bluetooth_device_list.h"
#include "bluetooth_timer.h"
#include "bluetooth_global_variables.h"
#include "bluetooth_hid.h"

#include "mtk_bt_service_gap_wrapper.h"
#include "mtk_bt_service_avrcp_wrapper.h"

#include "mtk_bt_service_hidh_wrapper.h"
#include "mtk_bt_service_a2dp_wrapper.h"
#include "mtk_bt_service_spp_wrapper.h"
#include "bluetooth_spp.h"

#include "c_scc.h"
#include "x_aud_dec.h"

#include "u_dbg.h"
#include "u_wgl_text.h"
#include "u_gl.h"
#include "u_sys_name.h"

#include "c_dbg.h"
#include "c_os.h"
#include "c_uc_str.h"
#include "c_wgl.h"

#include "c_fm.h"
#include "c_dm.h"
#include "u_dm.h"
#include "u_btn_map.h"
#include <string.h>

#include <sys/time.h>
#include <stdio.h>
#include "core/input.h"
#include "directfb.h"

#ifdef APP_BLE_SUPPORT
#include "bluetooth_gatt/bluetooth_gattc.h"
#endif

#define BLUETOOTH_THREAD_NAME            "bluetooth"
#define BLUETOOTH_STACK_SIZE             (1024 * 32)
#define BLUETOOTH_THREAD_PRIORITY        ((UINT8) 200) //PRIORITY(PRIORITY_CLASS_NORMAL, PRIORITY_LAYER_UI, 0)

static    BOOL  tv_mute         =TRUE;
static    BOOL  bt_mute         = FALSE;


BLUETOOTH_STATE_T                   _e_bluetooth_state;
HANDLE_T    h_bluetooth_timer_bar = NULL_HANDLE;
HANDLE_T    h_bt_volume_timer = NULL_HANDLE;
static    BOOL  b_received_volume = FALSE;

static    BOOL  b_received_prev = FALSE;

// The queue to receive bluetooth msg
static HANDLE_T h_s_bluetooth_queue  = NULL_HANDLE;
// Bluetooth thread which is used to deal with bluetooth msg
static HANDLE_T h_bluetooth_thread = NULL_HANDLE;

extern BOOL b_homeshare_started;

// start this timer when NFC touch,
// If no device request to connect within 30sec, turn off bluetooth and show warning.
#define BT_NFC_TOUCH_TIME_OUT 30 * 1000    // time out for NFC touch
//static  HANDLE_T h_bt_nfc_touch_timer = NULL_HANDLE;
// The flag specify whether NFC touch timer is started.
//static  BOOL fg_nfc_touch_timer_is_started = FALSE;

//copy from playback_normal_msgproc_aud.c

/* ================================================================*/
extern BOOL                         _b_key_processed;
extern UINT8                        _ui1_engine_id;
extern BOOL                         _b_key_valid;
extern BOOL                         _b_audio_error_pause;

BOOL   _b_ff_key_press = FALSE;
BOOL   _b_fr_key_press = FALSE;

extern INT32 c_dm_get_device(
    DM_DEV_SPEC_T *pt_spec,
    HANDLE_T *ph_dev);

extern INT32 x_thread_create(HANDLE_T    *ph_th_hdl,         /* thread handle */
            const CHAR  *ps_name,
            SIZE_T       z_stacksize,
            UINT8        ui1_pri,           /* thread priority */
            x_os_thread_main_fct pf_main,   /* thread's main function */
            SIZE_T       z_arg_size,
            VOID         *pv_arg);
extern VOID x_thread_exit (VOID);

/* ================================================================*/

extern INT32 bluetooth_scan_hid_and_a2dp_cli(VOID);

INT32 bt_utf8_to_ascii(const UINT8 * pf_str, UINT8 * pt_asc)
{
    INT8 i,j;
    UINT8 i1_plus_num = 0;
    for(i=0,j=0;(i<60)&&(j<20)&&(pf_str[i] != '\0'); i++,j++)
    {
        i1_plus_num = (pf_str[i] & 0xe0);
        if(i1_plus_num == 0xe0)
        {
            pt_asc[j]='_';
            i += 2;
        }
        else if(i1_plus_num == 0xc0)
        {
            pt_asc[j]='_';
            i += 1;
        }
        else if(i1_plus_num <= 0x60)
        {
            pt_asc[j]= pf_str[i];
        }

    }

    return 0;
}

// send device name to IFCon, device name is showed on VFD by IFCon only in PLAY MODE
INT32 bt_app_send_connected_device_name_to_ifcon(VOID)
{
    CHAR ac_bt_device_name[MAX_NAME_LEN] = {0};
    UINT8 ui1_bt_name[20] = {0};
    //UINT8 ui1_bt_send_name[22] = {0};
    UINT8 i = 0;
    UINT8 ui1_strlen = 20;//if device name length>20 ui1_strlen = 20

    BT_APP_LOG_API(("<BT_APP> %s is called\n", __FUNCTION__));

    // get connected device name
    a_bt_app_get_target_device_name(ac_bt_device_name, MAX_NAME_LEN-1);

    // transform device name from UTF8 to ASCII
    bt_utf8_to_ascii((const UINT8 *)ac_bt_device_name, ui1_bt_name);

    //printf("<BT_APP>Device name:");

    for(i=0;i<20;i++)
    {
        //printf("%c",ui1_bt_name[i]);
        if(ui1_bt_name[i] == 0)
        {
            ui1_strlen = i;
            break;
        }
        //ui1_bt_send_name[i+2] = ui1_bt_name[i];
    }
    //ui1_bt_send_name[0] = 0;
    //ui1_bt_send_name[1] = ui1_strlen;
    BT_APP_LOG_INFO(("\n<BT_APP>Name length:%d\n",ui1_strlen));
    ui1_strlen = ui1_strlen + 2;
    //d_ifcon_set_bluetooth_name(ui1_bt_send_name,ui1_strlen);

    return 0;
}

static INT32 _bt_app_set_mute(BOOL tv_mute,BOOL bt_mute)
{
	BT_APP_LOG_API(("<BT_APP>_bt_app_set_mute\n"));
	INT32 i4_ret;
	HANDLE_T h_audio_scc_comp;
	SM_COMMAND_T at_sm_cmds[3];
	at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    /* Use SCC to determine whether HP is plugged or not. */
    i4_ret = c_scc_comp_open (at_sm_cmds, &h_audio_scc_comp);
    if(tv_mute)
	{
		c_scc_aud_set_output_port(h_audio_scc_comp,SCC_AUD_OUT_PORT_SPEAKER, FALSE);//mute tv speaker
		BT_APP_LOG_API(("<BT_APP>mute tv speaker\n"));

	}
	else
	{
		c_scc_aud_set_output_port(h_audio_scc_comp,SCC_AUD_OUT_PORT_SPEAKER, TRUE);//unmute tv speaker
		BT_APP_LOG_API(("<BT_APP>unmute tv speaker\n"));
	}
    if(bt_mute)
    {
		c_scc_aud_set_output_port(h_audio_scc_comp,SCC_AUD_OUT_PORT_BLUETOOTH, FALSE);//mute bt
		BT_APP_LOG_API(("<BT_APP>mute bluetooth\n"));
	}

	else
	{
		c_scc_aud_set_output_port(h_audio_scc_comp,SCC_AUD_OUT_PORT_BLUETOOTH, TRUE);//unmute bt
		BT_APP_LOG_API(("<BT_APP>unmute bluetooth\n"));
	}
	i4_ret = c_scc_comp_close (h_audio_scc_comp);
	return BT_APPR_OK;
}
/**---------------------------------------------------------------------------
  * Name          - _bt_app_send_playback_time_to_ifcon
  *
  * Description  - send playback time to IFCon to update FLD
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_send_playback_time_to_ifcon(VOID)
{
    return BT_APPR_OK;
}
#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_nfc_touch_time_out_cb
  *
  * Description  - callback function for BT NFC touch timer
  *---------------------------------------------------------------------------*/
static VOID _bt_app_nfc_touch_time_out_cb(HANDLE_T pt_handle, VOID* pv_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_INFO(("<BT_APP> NFC touch timeout\n"));

    // Clear flag
    bt_app_set_flag_nfc_detected(FALSE);

    t_bt_msg.msg_type = BT_APP_MSG_EVENT_NFC_TOUCH_TIME_OUT;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send NFC time out msg fail\n"));
    }

    return ;
}
#endif
#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_start_nfc_touch_timer
  *
  * Description  - start BT NFC touch timer when NFC touch
  *                     start timer when NFC touch,
  *                     after timeout, turn off bluetooth and show warning.
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_start_nfc_touch_timer(VOID)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_API(("<BT_APP> start BT NFC touch timer\n"));

    fg_nfc_touch_timer_is_started = TRUE;

    if(NULL_HANDLE != h_bt_nfc_touch_timer)
    {
        c_timer_stop(h_bt_nfc_touch_timer);
        c_timer_delete(h_bt_nfc_touch_timer);
        h_bt_nfc_touch_timer = NULL_HANDLE;
    }

    i4_ret = c_timer_create(&h_bt_nfc_touch_timer);
    if((PBR_OK != i4_ret) || (NULL_HANDLE == h_bt_nfc_touch_timer))
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: create NFC touch timer fail, %d\n", i4_ret));
        return PBR_FAIL;
    }

    i4_ret = c_timer_start(h_bt_nfc_touch_timer,
                           BT_NFC_TOUCH_TIME_OUT,
                           X_TIMER_FLAG_ONCE,
                           _bt_app_nfc_touch_time_out_cb,
                           (VOID *)NULL);
    if (OSR_OK != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: start NFC touch timer fail, %d\n", i4_ret));
        return PBR_FAIL;
    }

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_stop_nfc_touch_timer
  *
  * Description  - stop BT NFC touch timer
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_stop_nfc_touch_timer(VOID)
{
    BT_APP_LOG_API(("<BT_APP> stop BT NFC touch timer\n"));

    fg_nfc_touch_timer_is_started = FALSE;

    if (NULL_HANDLE != h_bt_nfc_touch_timer)
    {
        c_timer_stop(h_bt_nfc_touch_timer);
        c_timer_delete(h_bt_nfc_touch_timer);
        h_bt_nfc_touch_timer = NULL_HANDLE;
    }

    return PLAYBACKR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_nfc_touch_timer_is_started
  *
  * Description  - check whether NFC touch timer is started.
  *---------------------------------------------------------------------------*/
static BOOL _bt_app_nfc_touch_timer_is_started()
{
    return fg_nfc_touch_timer_is_started;
}

#endif

/**---------------------------------------------------------------------------
  * Name          - bt_app_send_req_to_get_meta_data
  *
  * Description  - call MW API to send request to get meta data from SRC.
  *                     After MW get meta data from SRC, it notify BT_MEDIA_INFO_OK to APP.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
INT32 bt_app_send_req_to_get_meta_data(VOID)
{
#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    INT32 i4_ret = PBR_OK;
//    BT_AVRCP_MEDIA_INFO t_get_medinfo = {{0}};

    // clear media info firstly
    bt_app_clear_media_info();

    // send request to get media info from SRC.
    //i4_ret = c_btm_avrcp_get_mediaInfo(&t_get_medinfo);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send req to get meta data fail, %d\n", i4_ret));
        return PBR_FAIL;
    }

#endif

    return PBR_OK;
}

#if 0

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_input_a2dp_connected_proc
  *
  * Description  - Process the GAP event form BTM: Input A2DP is established
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_input_a2dp_connected_proc(VOID)
{
    //INT32   i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if (bt_app_input_a2dp_connected())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Input a2dp is already connected state, no need process connected msg.\n"));

        if (bt_app_in_playing_mode())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> In Bluetooth AUDIO function and PLAYING mode\n"));

            bt_app_start_bluetooth(BT_APP_MODE_PLAY);
        }

        return;
    }
    else
    {
        // if system is during power off sequence, prohibit connection
        if (!bt_app_is_BtConnectable())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line[%d]: Porhibit A2DP connection during system power off\n", __FUNCTION__, __LINE__));

            // disconnect instantly after connected will cause some error, add delay for safe
            c_thread_delay(100);

            bt_app_disconnect_with_src_dev();

            return;
        }


        bt_app_send_connected_device_name_to_ifcon();

        // if NFC touch timer is started, stop it.
        if(_bt_app_nfc_touch_timer_is_started())
        {
            _bt_app_stop_nfc_touch_timer();
            // clear flag
            bt_app_set_flag_nfc_detected(FALSE);
        }

        // Set flag
        bt_app_set_flag_input_a2dp_connected(TRUE);
        bt_app_set_flag_output_a2dp_connected(FALSE);  // SRC role and SNK role A2DP should be exclusive

        // clear media info for previous device
        bt_app_clear_media_info();
        // clear playback time for previous device
        bt_app_clear_playback_time();

        if(bt_app_is_bluetooth_audio_function_start())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> In Bluetooth AUDIO function\n"));
            // in bluetooth function, start bluetooth playback by APP.
            // otherwise, start bluetooth playback by  X2
            bt_app_start_bluetooth(BT_APP_MODE_PLAY);
        }
        else
        {
            if (bt_app_is_sink_dev_list_start()
                ||bt_app_is_audio_output_dev_list_start())
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d, in Sink device list, window state:%d\n", \
                    __FUNCTION__, __LINE__, _e_bluetooth_state));

                /* Return to <bluetooth settings> */
                bt_app_close_sink_device_list();
            }

            // not in bluetooth function,  X2 start playback after A2DP connected notify
            // X2 will call bluetooth_pbk_audio_input_start(MODE_PLAY) to start playback.
            bt_app_set_flag_wait_x2_start_playback(TRUE);
        }

        // Notify A2DP connected to  X2
        bt_app_notify_input_a2dp_connect_to_x2();

        if(bt_app_avrcp_connected())  // AVRCP is established before A2DP
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> AVRCP has been connected\n"));

            // Notify A2DP and AVRCP connected to X2
            bt_app_notify_input_a2dp_avrcp_connect_to_x2();
        }
        else    // AVRCP has not established
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> AVRCP has NOT been connected\n"));

            // start timer for AVRCP connection.
            // After time out, we think AVRCP cannot be established.
            bt_app_start_avrcp_connect_timer();
        }

    }

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_output_a2dp_connected_proc
  *
  * Description  - Process the GAP event form BTM: Output A2DP is established
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_output_a2dp_connected_proc(VOID)
{
    INT32   i4_ret = BT_APPR_OK;
    //CHAR    ps_app_name[APP_NAME_MAX_LEN]   = {0};
    //BOOL    b_support_scms_t = bt_app_is_target_support_scms_t();

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if (bt_app_output_a2dp_connected())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Output a2dp is already connected state, no need process connected msg.\n"));
        return;
    }

    // if system is during power off sequence, prohibit connection
    if (!bt_app_is_BtConnectable())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line[%d]: Porhibit A2DP connection during system power off\n", __FUNCTION__, __LINE__));

        // disconnect instantly after connected will cause some error, add delay for safe
        c_thread_delay(100);

        bt_app_disconnect_with_sink_dev();

        return;
    }

    //MSB11G doesn't have IFCON
    // set bt status to IFCON
    //d_ifcon_set_bt_status(IFCON_BT_STT_CONNECTED_A2DP_SRC_MODE);
    // send connected device name to IFCON
    //bt_app_send_connected_device_name_to_ifcon();

    //set the flag
    bt_app_set_flag_input_a2dp_connected(FALSE); // SRC role and SNK role A2DP should be exclusive
    bt_app_set_flag_output_a2dp_connected(TRUE);

    // start playing mode
    //i4_ret = c_btm_btstart("PLAYING", 0);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : PLAYING fail %d\n", i4_ret));
    }

    // According to  spec, always notify to X2 then X2 show M-EI07 if  app is active
    bt_app_notify_output_a2dp_connect_to_x2();

    return;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_a2dp_connected_proc
  *
  * Description  - Process the GAP event form BTM: A2DP is established
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_a2dp_connected_proc(VOID)
{
    BT_A2DP_ROLE e_bt_a2dp_role = BT_A2DP_ROLE_MAX;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    //e_bt_a2dp_role = c_btm_get_a2dp_role();

    switch (e_bt_a2dp_role)
    {
        case BT_A2DP_ROLE_SINK:
            BT_APP_LOG_DEFAULT(("<BT_APP> A2DP connected, SNK role\n"));
            _bt_app_btm_nfy_input_a2dp_connected_proc();
            break;
        case BT_A2DP_ROLE_SRC:
            BT_APP_LOG_DEFAULT(("<BT_APP> A2DP connected, SRC role\n"));
            _bt_app_btm_nfy_output_a2dp_connected_proc();
            break;
        default:
            BT_APP_LOG_ERR(("<BT_APP> ERR: A2DP connected, unknown role:%d\n", e_bt_a2dp_role));
            break;
    }

    return;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_avrcp_connected_proc
  *
  * Description  - Process the GAP event form BTM: AVRCP is established
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_avrcp_connected_proc(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    // stop timer
    bt_app_stop_avrcp_connect_timer();

    // Set flag
    bt_app_set_flag_avrcp_connected(TRUE);

    if(bt_app_input_a2dp_connected())   // A2DP has established
    {
        // Notify A2DP and AVRCP connected to  X2
        bt_app_notify_input_a2dp_avrcp_connect_to_x2();
    }

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_support_avrcp_1_3_proc
  *
  * Description  - Process the GAP event form BTM: current connected device support AVRCP 1.3
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_support_avrcp_1_3_proc(VOID)
{
    // When playback starting, we need send request to SRC to get meta data.
    // But, AVRCP connection may not been established at that time,
    // Then, request will fail, we need send it again when AVRCP 1.3 connection success.
    if((BLUETOOTH_MUSIC_PLAYBACK_STATE == _e_bluetooth_state)
        && (bt_app_meta_data_req_need_send_again()))
    {
        // send request to get meta data from SRC.
        bt_app_send_req_to_get_meta_data();
    }

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_connect_success_proc
  *
  * Description  - Process the GAP event form BTM: connection is completed
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_connect_success_proc(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    /* Update bluetooth standby status to IFCON when a2dp connected success */
    a_bt_setup_bt_standby(FALSE);

    return ;
}

#endif

#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_amp_menu_start_a2dp_snk_inquiry_scan
  *
  * Description  - This API only used for STR model
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_amp_menu_start_a2dp_snk_inquiry_scan(VOID)
{
    INT32   i4_ret = BT_APPR_OK;
    //IFCON_BT_STT_SCAN_T t_bt_stt_scan = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    BT_APP_LOG_INFO(("<BT_APP><STR> Start sink device scaning in AMP Menu\n"));

    /* Send STT_DVD_BT_scan to IFCON to inform scaning is started */
    //t_bt_stt_scan.e_bt_scan_mode      = IFCON_BT_STT_SCAN_MODE_START;
    //t_bt_stt_scan.u1_detected_dev_num = 0x00;

    //d_ifcon_set_stt_bt_scan(t_bt_stt_scan);

    // start pairing mode
    i4_ret = c_btm_btstart("PAIRING", 0);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : PAIRING fail %d\n", i4_ret));
        return;
    }

    /* Time out is 10s for AMP Menu scan */
    bt_app_start_a2dp_snk_inquiry_scan(TIME_OUT_SINK_DEVICE_AMP_MENU_SCAN);
}
#endif
#if 0

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_audio_input_disconnected_proc
  *
  * Description  - Process the GAP event form BTM: SRC device disconnected.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_audio_input_disconnected_proc(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    UINT8 u1_bt_mode = 0;
	UINT8 u1_bt_switch_staus = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if (!bt_app_input_a2dp_connected())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Input a2dp is already disconnected state, no need process disconnect msg.\n"));
        return;
    }

     // if NFC touch timer is started, stop it.
    if(_bt_app_nfc_touch_timer_is_started())
    {
        _bt_app_stop_nfc_touch_timer();
    }
    bt_app_stop_avrcp_connect_timer();
    bt_app_stop_bitrate_timer();
    bt_app_ui_stop_rssi_update_timer();
    bluetooth_progress_timer_bar_stop();

    // clear flag
    bt_app_set_flag_input_a2dp_connected(FALSE);
    bt_app_set_flag_avrcp_connected(FALSE);
    bt_app_set_flag_a2dp_avrcp_is_notified(FALSE);
    bt_app_set_flag_nfc_detected(FALSE);
    bt_app_set_flag_input_a2dp_connection_with_TV(FALSE);
    bt_app_set_flag_input_a2dp_initiator(FALSE);
    bt_app_set_setting_mode_changed(FALSE);

    // Notify A2DP disconnected to  X2 - iAPService
    bt_app_notify_input_a2dp_disconnect_to_x2();

    // clear media info
    bt_app_clear_media_info();
    // clear playback time
    bt_app_clear_playback_time();

    // disconnect SPP and release data buffer when disconnect
    //bt_spp_disconnect_all_req();

    if(!bt_app_is_bluetooth_audio_function_start())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Process input a2dp disconnected nfy in other than BT function\n"));

        // Recover bluetooth mode according to setting
        a_cfg_get_bluetooth_switch_status(&u1_bt_switch_staus);
        a_cfg_get_bluetooth_mode_status(&u1_bt_mode);

        if (a_bt_bluetooth_mode_get() != u1_bt_mode)
        {
            a_bt_bluetooth_mode_set(u1_bt_mode);
        }

        if(APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_switch_staus && a_bt_is_bluetooth_enabled())
        {
            a_bt_enable_disable(FALSE);
        }

        /* <STR> and <BAR> Change bt mode to Transmitter from other mode and paired sink device exist */
        if ((APP_CFG_BLUETOOTH_SWITCH_SOURCE == u1_bt_mode)
            && (0 != a_bt_app_get_paired_sink_device_num()))
        {
            BT_APP_LOG_INFO(("<BT_APP> BT mode change to TX, disconnect input a2dp and connect to sink device\n"));

            bt_app_connect_with_sink_dev(TRUE, NULL);
        }

        /* For PAIRING key detected and A2DP is connected in other than BT function case, need to disconnec first then notify to X2 */
        if (bt_app_is_pairing_key_detected())
        {
            BT_APP_LOG_INFO(("<BT_APP> Input A2DP is disconnected due to [PAIRING] key\n"));

            //bt_app_notify_bt_cmd_key_to_x2(BLUETOOTH_CMD_PAIRING);

            bt_app_set_flag_pairing_key_detected(FALSE);
        }

    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Process input a2dp disconnected nfy in BT function\n"));

        //i4_ret = c_btm_btstart("PAIRING", 300);
        if (BT_APPR_OK != i4_ret)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : PAIRING fail %d\n", i4_ret));
            return;
        }

        _e_bluetooth_state = BLUETOOTH_WAIT_PAIR_STATE;
    }

    // turn off BT RF
    if (bt_app_need_disable_bt_after_disconnect()
        && a_bt_is_bluetooth_enabled())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d : disable bluetooth\n", __FUNCTION__, __LINE__));

        a_bt_enable_disable(FALSE);
        bt_app_set_flag_disable_bt_after_disconnect(FALSE);
    }

    // unlock sema to allow sink deivce list open by X2
    bt_a2dp_disconnection_sema_unlock();

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_audio_output_disconnected_proc
  *
  * Description  - Process the GAP event form BTM: Sink device disconnected
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_audio_output_disconnected_proc(VOID)
{
    //INT32   i4_ret = BT_APPR_OK;
    CHAR    ps_app_name[APP_NAME_MAX_LEN]   = {0};
    UINT8   u1_bt_status = 0;
	UINT8   u1_bt_setting_mode = 0;
    //BT_TARGET_DEV_INFO t_target_device = {0,0,{0},{0}};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if (!bt_app_output_a2dp_connected())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Output a2dp is already disconnected state, no need process disconnect msg.\n"));
        return;
    }

    a_cfg_get_bluetooth_switch_status(&u1_bt_status);
    a_cfg_get_bluetooth_mode_status(&u1_bt_setting_mode);
    // clear flag
    bt_app_set_flag_output_a2dp_connected(FALSE);
    bt_app_set_flag_avrcp_connected(FALSE);
    bt_app_set_setting_mode_changed(FALSE);

    a_am_get_active_app(ps_app_name);

#if 0
    // Process output a2dp disconnected event in MTK app case
    if ((c_strncmp(NAV_NAME, ps_app_name, c_strlen(NAV_NAME)) != 0)
        && (c_strncmp(MSCVT_NAME, ps_app_name, c_strlen(MSCVT_NAME)) != 0))
    {
        if (bt_app_is_sink_dev_list_start()
            ||bt_app_is_audio_output_dev_list_start())
        {
            // start pairing mode
            i4_ret = c_btm_btstart("PAIRING", 0);
            if (BT_APPR_OK != i4_ret)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : PAIRING fail %d\n", i4_ret));
                return;
            }

            if (bt_app_is_2nd_sink_connect())
            {
                /* Start new connection when there is already output a2dp connection existed */
                BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> Start new connection\n"));

                bt_app_set_flag_start_2nd_sink_connect(FALSE);

                c_memset(&t_target_device, 0, sizeof(BT_TARGET_DEV_INFO));

                i4_ret = bt_app_ui_sink_device_list_get_focused_device(&t_target_device);
                if(i4_ret != BT_APPR_OK)
                {
                    BT_APP_LOG_ERR(("<BT_APP> ERR: get focused sink device fail, %d\n", i4_ret));
                }
                else
                {
                    bt_app_connect_with_sink_dev(FALSE, &t_target_device);
                }
            }
            else if (bt_app_need_show_disconnect_message())
            {
                BT_APP_LOG_INFO(("<BT_APP> Line:%d, need show disconnect msg:%d\n", __LINE__, COMM_WARN_M_BT_DISCONNECT));

                _e_bluetooth_state = BLUETOOTH_BT_SRC_DISCONNECTED_STATE;

            }
            else
            {
                BT_APP_LOG_INFO(("<BT_APP> Line:%d, no need show disconnect msg\n", __LINE__));

                /* Recover show message next time */
                bt_app_set_flag_show_disconnect_message(TRUE);
            }
        }
        else
        {
            /* Recover when warning message shown 5 second timeout */
            _e_bluetooth_state = BLUETOOTH_SRC_PLAYBACK_STATE;
        }
    }
#endif

    // Notify to X2 that audio output a2dp disconnection success
    // X2 will show M-EI03 if active app is  app
    bt_app_notify_output_a2dp_disconnect_to_x2();

    if (bt_app_nfc_detected())
    {
        //disconnect output a2dp due to NFC detected, need to change mode to receiver
        BT_APP_LOG_INFO(("<BT_APP> Set internal bluetooth mode to Receiver due to NFC touch\n"));

        //a_bt_bluetooth_mode_set(CFG_BLUETOOTH_MODE_RECEIVER);

        //d_ifcon_set_bt_status(IFCON_BT_STT_CONNECTABLE_A2DP_SNK_MODE);
    }
    else
    {
        BT_APP_LOG_INFO(("<BT_APP> Output a2dp disconnected due to other than NFC touch\n"));

        // change bluetooth mode from Transmitter to Receiver/OFF in setup when output a2dp is connected
        // need to change bluetooth mode and setup bt power after disconnetion
        if (a_bt_bluetooth_mode_get() != u1_bt_setting_mode)
        {
            a_bt_bluetooth_mode_set(u1_bt_setting_mode);
        }

        //MSB11G doesn't support RX mode
        if((APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_status) && a_bt_is_bluetooth_enabled())
        {
            a_bt_enable_disable(FALSE);
        }
    }

    // turn off BT RF
    if (bt_app_need_disable_bt_after_disconnect()
        && a_bt_is_bluetooth_enabled())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d : disable bluetooth\n", __FUNCTION__, __LINE__));

        a_bt_enable_disable(FALSE);
        bt_app_set_flag_disable_bt_after_disconnect(FALSE);
    }

    return;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_disconnected_proc
  *
  * Description  - Process the GAP event form BTM: A2DP disconnected.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_disconnected_proc(VOID)
{
    BT_A2DP_ROLE e_bt_a2dp_role = BT_A2DP_ROLE_MAX;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    BOOL b_input_audio_connected = FALSE;
    BOOL b_output_audio_connected = FALSE;

    //e_bt_a2dp_role = c_btm_get_a2dp_role();

    b_input_audio_connected = bt_app_input_a2dp_connected();

    b_output_audio_connected = bt_app_output_a2dp_connected();

    BT_APP_LOG_DEFAULT(("<BT_APP> e_bt_a2dp_role[%d], b_input_audio_connected[%d], b_output_audio_connected[%d]\n", e_bt_a2dp_role, b_input_audio_connected, b_output_audio_connected));

    if (b_input_audio_connected || b_output_audio_connected)
    {
        if (b_input_audio_connected)
        {
            _bt_app_btm_nfy_audio_input_disconnected_proc();
        }
        else
        {
            _bt_app_btm_nfy_audio_output_disconnected_proc();
        }
    }

    return;

}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_input_connect_timeout_proc
  *
  * Description  - Process the GAP event form BTM: input connection time out
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_btm_nfy_input_connect_timeout_proc(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    //i4_ret = c_btm_btstart("PAIRING",300);
    if (BT_APPR_OK != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : PAIRING fail %d\n", i4_ret));
        return BT_APPR_FAIL;
    }

    //d_ifcon_set_bt_status(IFCON_BT_STT_DISCOVERABLE);

    // reset flag if input a2dp connection timeout
    bt_app_set_flag_input_a2dp_initiator(FALSE);

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_output_connect_timeout_proc
  *
  * Description  - Process the GAP event form BTM: output connection time out
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_btm_nfy_output_connect_timeout_proc(VOID)
{
    INT32   i4_ret = BT_APPR_OK;

    //d_ifcon_set_bt_status(IFCON_BT_STT_CONNECTABLE_A2DP_SRC_MODE);

    if(bt_app_is_sink_dev_list_start()
        ||bt_app_is_audio_output_dev_list_start())
    {
        // start pairing mode
        //i4_ret = c_btm_btstart("PAIRING", 0);
        if (i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : PAIRING fail %d\n", i4_ret));
            return BT_APPR_FAIL;
        }

        _e_bluetooth_state = BLUETOOTH_BT_CONNECTION_FAIL_STATE;
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Not in sink device list window, no need to show W-EI01\n"));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_connect_timeout_proc
  *
  * Description  - Process the GAP event form BTM: connection time out
  *                    Only when the connection is trigger by platform itself, then will receive timeout notify when connection fail.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_btm_nfy_connect_timeout_proc(VOID)
{
    //here can't get a2dp role by c_btm_get_a2dp_role, role is updated only when connection success
    if (bt_app_is_input_a2dp_initiator())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> A2DP connect timeout, SNK role\n"));
        _bt_app_btm_nfy_input_connect_timeout_proc();
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> A2DP connect timeout, SRC role\n"));
        _bt_app_btm_nfy_output_connect_timeout_proc();
    }

    return BT_APPR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_2nd_connect_coming_proc
  *
  * Description  - Process the GAP event form BTM: another device request to connect.
  *                     When BDV is connected with device A, if device B request to connect,
  *                     the connection is switched from A to B.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_2nd_connect_coming_proc(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    // if NFC touch timer is started, stop it.
    if(_bt_app_nfc_touch_timer_is_started())
    {
        _bt_app_stop_nfc_touch_timer();
    }
    bt_app_stop_avrcp_connect_timer();
    bt_app_ui_stop_rssi_update_timer();
    bluetooth_progress_timer_bar_stop();

    // clear flag
    bt_app_set_flag_input_a2dp_connected(FALSE);
    bt_app_set_flag_avrcp_connected(FALSE);
    bt_app_set_flag_a2dp_avrcp_is_notified(FALSE);
    bt_app_set_flag_input_a2dp_connection_with_TV(FALSE);
    bt_app_set_flag_input_a2dp_initiator(FALSE);

    // Notify A2DP disconnected to  X2 - iAPService
    bt_app_notify_input_a2dp_disconnect_to_x2();

    // clear media info for previous device
    bt_app_clear_media_info();
    // clear playback time for previous device
    bt_app_clear_playback_time();

    // disconnect SPP and release data buffer when disconnect
    //bt_spp_disconnect_all_req();

    // show waiting screen.
    // A2DP maybe be kept in other BT function, if not BT function, don't show warning
    if (bt_app_is_bluetooth_audio_function_start())
    {
        if(bt_app_nfc_detected())    // NFC touch
        {
            // Clear flag
            bt_app_set_flag_nfc_detected(FALSE);

            // show "connecting..please wait"
            //a_comm_warn_begin(COMM_WARN_M_BT_D_NFC_DEVICE_CONNECTING);
        }
        else
        {
            // show "The new device is being connected, please wait a moment "
            //a_comm_warn_begin(COMM_WARN_M_BT_D_NEW_DEVICE_CONNECTING);
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n", __FUNCTION__));

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_2nd_connect_fail_proc
  *
  * Description  - Process the GAP event form BTM: first connection is disconnected, 2nd connection coming but connect fail
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_2nd_connect_fail_proc(VOID)
{
    #if 0
    INT32 i4_ret = BT_APPR_OK;
    UINT8 u1_bt_mode = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    // A2DP may keep connection in other than BT function, enter pairing mode only when in BT function
    if(bt_app_is_bluetooth_audio_function_start())
    {
        bt_app_start_bluetooth(BT_APP_MODE_PAIRING);
    }
    else
    {
        // 2nd connection fail, need to update status to IFCON
        a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

        if (APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_mode)
        {
            d_ifcon_set_bt_status(IFCON_BT_STT_CLOSED);
        }
        else if (CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode)
        {
            d_ifcon_set_bt_status(IFCON_BT_STT_CONNECTABLE_A2DP_SNK_MODE);
        }
        else if (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode)
        {
            d_ifcon_set_bt_status(IFCON_BT_STT_CONNECTABLE_A2DP_SRC_MODE);
        }

        i4_ret = c_btm_stop(FALSE, FALSE);
        if (i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_stop fail, %d\n", i4_ret));
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n", __FUNCTION__));
#endif
    return ;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_support_scms_t_proc
  *
  * Description  - Process the GAP event form BTM: support SCMS_T
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_support_scms_t_proc(VOID)
{
    #if A2DP_SUPPORT
    UINT8 ui1_scms_t = 0;
//    ui1_scms_t = c_btm_bt_get_scms_t();

    bt_app_set_flag_target_support_scms_t(ui1_scms_t);

    BT_APP_LOG_DEFAULT(("<BT_APP> Target device %s support SCMS-T\n", (ui1_scms_t ? "do" : "don't")));
    #endif

    return ;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_connecting_start_proc
  *
  * Description  - Process the GAP event form BTM: When pairing or A2DP connecting is started,
                        this notify will be received regardless of connection is triggered from BDV or SRC.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_connecting_start_proc(VOID)
{
    return;
}
#endif
/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_mode_changed_proc
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_mode_changed_proc(tBTMW_GAP_STATE* e_gap_event)
{
#if 0
    BT_MODE_TYPE e_mode;

    e_mode = c_btm_get_mode();

    switch(e_gap_event)
    {
        case BT_OFF_MODE:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Change to BT_OFF_MODE\n"));
            break;
        }
        case BT_CONNECT_MODE:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Change to BT_CONNECT_MODE\n"));
            break;
        }
        case BT_PAIRING_MODE:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Change to BT_PAIRING_MODE\n"));
            break;
        }
        case BT_PLAYING_MODE:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Change to BT_PLAYING_MODE\n"));
            break;
        }
        case BT_EXIT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Change to BT_EXIT\n"));
            break;
        }
        default:
            break;
    }

    switch (e_mode)
    {
        case BT_MODE_CLOSE:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Current mode: CLOSE\n"));
            break;
        }
        case BT_MODE_PAIRING:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Current mode: PAIRING\n"));
            break;
        }
        case BT_MODE_CONNECTING:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Current mode: CONNECTING\n"));
            break;
        }
        case BT_MODE_PLAYING:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Current mode: PLAYING\n"));
            break;
        }
        case BT_MODE_OFF:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Current mode: OFF\n"));
            break;
        }
        default:
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: Current mode: %d\n", e_mode));
        }
    }
#endif
}

static VOID bt_connect_device_proc(VOID)
{
    BT_TARGET_DEV_INFO  t_target_device;
    INT32 i4_ret = 0;

    /* Get target device info from sink device list */
    c_memset(&t_target_device, 0, sizeof(BT_TARGET_DEV_INFO));

    i4_ret = a_bt_app_ui_sink_device_list_get_focused_device(&t_target_device);

    DBG_LOG_PRINT(("<MENU_BT> get focused device name=%s, addr=%s, cod=0x%x\n",
        t_target_device.name, t_target_device.bdAddr, t_target_device.cod));

    if(i4_ret < BT_APPR_OK)
    {
        DBG_LOG_PRINT(("<MENU_BT> ERR: get focused sink device fail, %d\n", i4_ret));
        return;
    }

    if((t_target_device.cod&0x0500)==0x0500)
    {

        DBG_LOG_PRINT(("<MENU_BT> Start to connect keyboard/ mouse device %s\n",
                t_target_device.bdAddr));
        DBG_LOG_PRINT(("<MENU_BT> Start to call c_btm_connect_hid_sources.\n"));
        a_bt_app_connect_with_hid_dev(t_target_device.bdAddr);
        DBG_LOG_PRINT(("<MENU_BT> c_btm_connect_hid_sources, i4_ret: %d.\n", i4_ret));
    }
    else
    {
        DBG_LOG_PRINT(("<MENU_BT> Start to connect A2DP device.\n"));
        /* Focused device is not connected, then connect to it */

        DBG_LOG_PRINT(("<MENU_BT> A2DP name=%s, addr=%s\n",
            t_target_device.name, t_target_device.bdAddr));
        a_bt_app_connect_with_sink_dev(FALSE, &t_target_device);
    }

}
/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_gap_event_proc
  *
  * Description  - Process the event form BTM:
  *
  * Inputs        -



  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_gap_event_proc(tBTMW_GAP_STATE* e_gap_event)
{
    VOID*         pv_nfy_param = NULL;
    BT_NFY_ID_T   e_nfy_id = BT_NFY_ID_UNKNOWN;
    INT32         i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));
    BT_APP_LOG_DEFAULT(("<BT_APP> %s, Gap state: %d, reason=%d, bdaddr=%s.\n",
        __FUNCTION__, e_gap_event->state, e_gap_event->reason, e_gap_event->bd_addr));

    switch (e_gap_event->state)
    {
        case GAP_STATE_ON:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 111111111GAP_STATE_ON\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_ON;

            //e_nfy_id = 10;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case GAP_STATE_ACL_CONNECTED:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 2222222222GAP_STATE_ACL_CONNECTED\n"));
            e_nfy_id = BT_NFY_ID_GAP_STATE_ACL_CONNECTED;

            //e_nfy_id = 12;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case GAP_STATE_ACL_DISCONNECTED:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 3333333333GAP_STATE_ACL_DISCONNECTED\n"));
            e_nfy_id = BT_NFY_ID_GAP_STATE_ACL_DISCONNECTED;

            //e_nfy_id = 13;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case GAP_STATE_DISCOVERY_STARTED:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 44444444444GAP_STATE_DISCOVERY_STARTED\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_DISCOVERY_STARTED;

            //e_nfy_id = 18;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case GAP_STATE_DISCOVERY_STOPED:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 5555555555GAP_STATE_DISCOVERY_STARTED\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_DISCOVERY_STOPED;

            //e_nfy_id = 19;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case GAP_STATE_OFF:
        //case BT_EXIT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 6666666GAP_STATE_OFF\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_OFF;

            //e_nfy_id = 11;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            _bt_app_btm_nfy_mode_changed_proc(e_gap_event);
            break;
        }
        case GAP_STATE_BONDING:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 77777777 GAP_STATE_BONDING\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_BONDING;

            //e_nfy_id = 15;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case GAP_STATE_BONDED:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 888888888888 GAP_STATE_BONDED\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_BONDED;

            //e_nfy_id = 14;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            bt_connect_device_proc();
            break;
        }
        case GAP_STATE_NO_BOND: //BT_PAIRING_TIMEOUT:           // The GAP event from BTM: time-out in pairing mode
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 9999999 GAP_STATE_NO_BOND\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_NO_BOND;

            //e_nfy_id = 16;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            i4_ret = bt_app_stop_bluetooth();  // return to home after time-out in pairing mode
            BT_APP_LOG_ON_FAIL(i4_ret);
            break;
        }
        case GAP_STATE_UNPAIR_SUCCESS:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> 99999999 GAP_STATE_BONDED\n"));

            e_nfy_id = BT_NFY_ID_GAP_STATE_UNPAIR_SUCCESS;

            //e_nfy_id = 17;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
#if 0
        case BT_A2DP_CONNECTION_SUCCESS:   // The GAP event from BTM: A2DP is established
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_CONNECTION_SUCCESS\n"));

            _bt_app_btm_nfy_a2dp_connected_proc();

            e_nfy_id = BT_NFY_ID_CONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case BT_AVRCP_CONNECTION_SUCCESS:  // The GAP event from BTM: AVRCP is established
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_AVRCP_CONNECTION_SUCCESS\n"));

            _bt_app_btm_nfy_avrcp_connected_proc();

            e_nfy_id = BT_NFY_ID_CONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case BT_SUPPORT_AVRCP_1_3:         // The GAP event from BTM: current connected device support AVRCP 1.3
        {
            BT_APP_LOG_INFO(("<BT_APP> BT_SUPPORT_AVRCP_1_3\n"));

            _bt_app_btm_nfy_support_avrcp_1_3_proc();
            break;
        }
        case BT_NOT_SUPPORT_AVRCP_1_3:     // The GAP event from BTM: not support AVRCP 1.3
        {
            BT_APP_LOG_INFO(("<BT_APP> BT_NOT_SUPPORT_AVRCP_1_3\n"));
            break;
        }
        case BT_CONNECT_SUCCESS:           // The GAP event from BTM: connection is completed
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_CONNECT_SUCCESS\n"));

            _bt_app_btm_nfy_connect_success_proc();

            e_nfy_id = BT_NFY_ID_CONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case BT_DISCONNECTED:              // The GAP event from BTM: both A2DP and AVRCP have been disconnected.
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_DISCONNECTED\n"));

            _bt_app_btm_nfy_disconnected_proc();

            e_nfy_id = BT_NFY_ID_DISCONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case BT_CONNECT_MISSING:           // The GAP event from BTM: connection is missing
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_CONNECT_MISSING\n"));

            _bt_app_btm_nfy_audio_input_disconnected_proc();
            break;
        }
        case BT_CONNECT_TIMEOUT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_CONNECT_TIMEOUT\n"));

            _bt_app_btm_nfy_connect_timeout_proc();

            e_nfy_id = BT_NFY_ID_CONNECT_FAIL;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case BT_2ND_CONNECT_COMMING:       // The GAP event from BTM: another device request to connec.
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_2ND_CONNECT_COMMING\n"));

            _bt_app_btm_nfy_2nd_connect_coming_proc();
            break;
        }
        case BT_2ND_CONNECT_FAIL:         // The GAP event from BTM: 2nd connection fail.
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_2ND_CONNECT_FAIL\n"));

            _bt_app_btm_nfy_2nd_connect_fail_proc();

            break;
        }
        case BT_SUPPORT_SCMS_T:           // The GAP event from BTM: support SCMS_T
		{
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_SUPPORT_SCMS_T\n"));

            _bt_app_btm_nfy_support_scms_t_proc();
			break;
	    }
        case BT_REGISTER_PS_SUCCESS:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_REGISTER_PS_SUCCESS\n"));
            break;
        }
        case BT_REGISTER_PS_FAIL:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_REGISTER_PS_FAIL\n"));
            break;
        }
        case BT_CONNECT_COMING:           // pairing or connecting is started
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_CONNECT_COMING\n"));

            _bt_app_btm_nfy_connecting_start_proc();
            break;
        }
#endif
        default:
        {
            BT_APP_LOG_INFO(("<BT_APP> no used GAP event, %d\n", e_gap_event->state));
            break;
        }
    }
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_track_chgd_proc
  *
  * Description  - Process the event form BTM: Track is changed
  *                     When track is changed, APP need to do:
  *                     1. call MW API to send request to get meta data from SRC.
  *                         After MW get meta data from SRC, it notify BT_MEDIA_INFO_OK to APP.
  *                     2. update UI
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
VOID _bt_app_btm_nfy_track_chgd_proc(UINT32 ui4_track_idx)
{

    // send request to get meta data from SRC.
    bt_app_send_req_to_get_meta_data();

    // track change or playstatus change need to issue GetPlayStatus
    bt_app_send_req_to_get_playstatus();

    return ;
}

#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_play_state_chgd_proc
  *
  * Description  - Process the event from BTM: playback state is changed
  *
  * Inputs        - e_playstate: playback status (play/pause/stop/...)
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_play_state_chgd_proc(BTPlayState e_playstate)
{
    //BOOL b_ui_always_display = TRUE;

    switch (e_playstate)
    {
        case BT_PLAY_STATE_STOP:
        {
            _b_ff_key_press = FALSE;
            _b_fr_key_press = FALSE;
            break;
        }
        case BT_PLAY_STATE_PLAY:
        {
            _b_ff_key_press = FALSE;
            _b_fr_key_press = FALSE;

            // In play state, display small Information Display C for 5 seconds
            //b_ui_always_display = FALSE;

            break;
        }
        case BT_PLAY_STATE_PAUSE:
        {
            _b_ff_key_press = FALSE;
            _b_fr_key_press = FALSE;
            break;
        }
        case BT_PLAY_STATUS_FWD_SEEK:
        {
            _b_ff_key_press = TRUE;
            _b_fr_key_press = FALSE;

            break;
        }
        case BT_PLAY_STATUS_REV_SEEK:
        {
            _b_fr_key_press = TRUE;
            _b_ff_key_press = FALSE;

            break;
        }
        default:
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: invalid play state id, %d\n", e_playstate));
            break;
        }
    }

    // track change or playstatus change need to issue GetPlayStatus
    bt_app_send_req_to_get_playstatus();

    // some SRC device don't notify track change when continuously forward in PAUSE state and second time change to next content
    // EX. track1 -> forward to track2, notify track change -> continue forward until change to next content, but no track change msg
    // add this patch to request meta data when start play
    bt_app_send_req_to_get_meta_data();

    return ;
}
#endif

/**---------------------------------------------------------------------------
  * Name          - bt_app_send_req_to_get_playstatus
  *
  * Description  - This API send request to BTM to get play status from SRC
  *                     After BTM get play status, it will notify BT_PLAY_STATUS_OK.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
INT32 bt_app_send_req_to_get_playstatus(VOID)
{
    INT32 i4_ret = PBR_OK;
    //bt_player_status_values_t t_play_status = {0};

    BT_APP_LOG_API(("<BT_APP> API: %s\n", __FUNCTION__));

    if(!bt_app_in_playing_mode())
    {
        BT_APP_LOG_INFO(("<BT_APP> Not in playing mode, don't issue GetPlayStatus\n"));
        return PBR_OK;
    }

    bt_app_set_playstatus_ready_flag(FALSE);

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT
    // send request to SRC to get play status
//    i4_ret = c_btm_avrcp_get_play_status(&t_play_status);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send request to get playstatus fail, %d\n", i4_ret));
    }
#endif

    return 0;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_meta_data_ok_proc
  *
  * Description  - Process the event from BTM: meta data has been ready in BTM
  *                     Meta data include artist, artist and album.
  *                     After meta data is ready, APP should get it from BTM and update UI.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_btm_nfy_meta_data_ok_proc()
{
#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    INT32 i4_ret = 0;
    BT_AVRCP_MEDIA_INFO t_mediainfo = {{0}};
    BT_NFY_ID_T   e_nfy_id = BT_NFY_ID_UNKNOWN;

    // get media info from BTM
//    i4_ret = c_btm_avrcp_get_mediaInfo(&t_mediainfo);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get media info from BTM fail, %d\n", i4_ret));
        return ;
    }

    BT_APP_LOG_INFO(("<BT_APP> ac_track_name:%s\nac_album_title:%s\nac_artist_name:%s\n",
                      t_mediainfo.title, t_mediainfo.album, t_mediainfo.artist));

    bt_app_save_media_info(&t_mediainfo);
	e_nfy_id = BT_NFY_ID_AVPCP_GET_META_DATA_OK;
    bt_msg_brdcast(e_nfy_id, (VOID*)&t_mediainfo);

#endif

    return ;
}
#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_play_status_ok_proc
  *
  * Description  - Process the event from BTM: play status has been ready in BTM
  *                     Play status include song length, song position and running status (play/pause/stop/...)
  *                     After play status is ready, APP should get it from BTM and update UI.
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_btm_nfy_play_status_ok_proc(VOID)
{
#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    INT32 i4_ret = BT_APPR_OK;
    BT_NFY_ID_T   e_nfy_id = BT_NFY_ID_UNKNOWN;

    bt_player_status_values_t t_playStatus = {0};

    // Get play status from BT manager
    i4_ret = c_btm_avrcp_get_play_status(&t_playStatus);
    if(0 != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: get play status fail, %d\n", i4_ret));
        return BT_APPR_FAIL;
    }

    bt_app_set_playstatus_ready_flag(TRUE);

	e_nfy_id = BT_NFY_ID_AVPCP_GET_PLAY_STATUS_OK;

    bt_msg_brdcast(e_nfy_id, (VOID*)&t_playStatus);
#endif
	return i4_ret;
}
#endif

#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_btm_nfy_volume_change_proc
  *
  * Description  - Process the event from BTM: volume change
  *
  * Inputs        - e_vol_type: volume up or volume down
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_btm_nfy_volume_change_proc(BTVolType e_vol_type)
{
    return BT_APPR_OK;
}
#endif
#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_ifcon_cmd_bt_pairing_key_proc
  *
  * Description  - ![PAIRING] key is only valid in Receiver mode for <BAR> model
  *
  *                     ![PAIRING] key is valid in RX/TX mode for <STR> model
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_ifcon_cmd_bt_pairing_key_proc(VOID)
{
    #if 0
    INT32   i4_ret = BT_APPR_OK;
    UINT8   u1_bt_mode = 0;

    BT_APP_LOG_INFO(("<BT_APP> Enter %s\n",__FUNCTION__));

    //read bluetooth mode setting from flash
    a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

    if(CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode)
    {
        /* both for <BAR> and <STR> model */
        if (bt_app_is_bluetooth_audio_function_start())
        {
            if (bt_app_input_a2dp_connected())
            {
                BT_APP_LOG_INFO(("<BT_APP> In BT function and connected, disconnect input A2DP and return to PAIRING window\n"));
                bt_app_disconnect_with_src_dev();
            }
            else
            {
                BT_APP_LOG_INFO(("<BT_APP> In BT function and NOT connected, do nothing\n"));
            }
        }
        else
        {
            /*  spec <MSA2G_BT_key_behavior.pptx>, page8. only notify to X2 in RX mode & BT function is not started */

            if (bt_app_input_a2dp_connected())
            {
                BT_APP_LOG_INFO(("<BT_APP> In other than BT function and connected, disconnect input A2DP\n"));
                i4_ret = c_btm_stop(FALSE,FALSE);
                if (i4_ret != BT_APPR_OK)
                {
                    BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_stop fail, %d\n", i4_ret));
                }
                else
                {
                    // set flag pairing key detected, when input a2dp disconnect success, notify bluetooth cmd to X2
                    bt_app_set_flag_pairing_key_detected(TRUE);
                }
            }
            else
            {
                BT_APP_LOG_INFO(("<BT_APP> In other than BT function and NOT connected\n"));

                bt_app_notify_bt_cmd_key_to_x2(BLUETOOTH_CMD_PAIRING);
            }
        }
    }

    if (d_is_str15_model() && (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode))
    {
        /* [PAIRING] key is valid in TX mode for <STR> model */
        if (bt_app_output_a2dp_connected())
        {
            BT_APP_LOG_INFO(("<BT_APP><STR> TX mode and A2DP is already connected, need to disconnect\n"));
            bt_app_disconnect_with_sink_dev();
        }

        _bt_app_amp_menu_start_a2dp_snk_inquiry_scan();
    }
    #endif

    BT_APP_LOG_INFO(("<BT_APP> Exit %s\n",__FUNCTION__));
}
#endif
#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_ifcon_cmd_bt_connection_key_proc
  *
  * Description  -
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static VOID _bt_app_ifcon_cmd_bt_connection_key_proc(VOID)
{
    #if 0
    INT32   i4_ret = BT_APPR_OK;
    UINT8   u1_bt_mode = 0;
    UINT32  u4PairedNum = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));

    //read bluetooth mode setting from flash
    a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

    if (d_is_str15_model())
    {
        if(CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode)
        {
            if (bt_app_input_a2dp_connected())
            {
                /* only for <STR> model */
                if (bt_app_is_bluetooth_audio_function_start())
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP><STR> In BT function, disconnect input A2DP and return to PAIRING window\n"));
                    bt_app_disconnect_with_src_dev();
                }
                else
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP><STR> In other than BT function, disconnect input A2DP\n"));
                    i4_ret = c_btm_stop(FALSE,FALSE);
                    if (i4_ret != BT_APPR_OK)
                    {
                        BT_APP_LOG_ERR(("<BT_APP><STR> ERR: c_btm_stop fail, %d\n", i4_ret));
                    }
                }
            }
            else
            {
                if (bt_app_is_bluetooth_audio_function_start())
                {
                    u4PairedNum = a_bt_app_get_paired_src_device_num();
                    if (u4PairedNum > 0)
                    {
                        /* Paired device exist, then auto link to last connected device */
                        BT_APP_LOG_DEFAULT(("<BT_APP><STR> In BT function : paired device exist, start auto link\n"));

                        bt_app_enter_connecting_mode();
                    }
                }
                else
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP> Bluetooth AUDIO function is not started, notify [CONNECTION] key to X2\n"));

                    /*  spec <MSA2G_BT_key_behavior.pptx>, page9. only notify to X2 when BT function is not started & A2DP is not connected */
                    bt_app_notify_bt_cmd_key_to_x2(BLUETOOTH_CMD_CONNECTION);
                }
            }
        }
        else if (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode)
        {
            if (bt_app_output_a2dp_connected() || bt_app_input_a2dp_connected())
            {
                if (bt_app_output_a2dp_connected())
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP><STR> TX mode and Output A2DP is already connected, need to disconnect\n"));
                    bt_app_disconnect_with_sink_dev();
                }
                else
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP><STR> TX mode and Input A2DP is already connected, need to disconnect\n"));
                    /* only for <STR> model */
                    if (bt_app_is_bluetooth_audio_function_start())
                    {
                        BT_APP_LOG_DEFAULT(("<BT_APP><STR> In BT function, disconnect input A2DP and return to PAIRING window\n"));
                        bt_app_disconnect_with_src_dev();
                    }
                    else
                    {
                        BT_APP_LOG_DEFAULT(("<BT_APP><STR> In other than BT function, disconnect input A2DP\n"));
                        i4_ret = c_btm_stop(FALSE,FALSE);
                        if (i4_ret != BT_APPR_OK)
                        {
                            BT_APP_LOG_ERR(("<BT_APP><STR> ERR: c_btm_stop fail, %d\n", i4_ret));
                        }
                    }
                }
            }
            else
            {
                BT_APP_LOG_DEFAULT(("<BT_APP><STR> TX mode and A2DP is NOT connected, start auto link\n"));
                i4_ret = bt_app_connect_with_sink_dev(TRUE, NULL);
                if (BT_APPR_TX_AUTO_CONNECTION_FAIL == i4_ret)
                {
                    _bt_app_amp_menu_start_a2dp_snk_inquiry_scan();
                }
            }

            // it seems no need to notify X2 CONNECTION key event, this key event only for start BT function?
        }
        else
        {
            BT_APP_LOG_ERR(("<BT_APP><STR> ERR: Not in RX/TX mode, no need process [CONNECTION] key\n"));
        }
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: not STR model, no need process [CONNECTION] key\n"));
    }
#endif

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n",__FUNCTION__));
}
#endif
#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_ifcon_cmd_bt_start_key_proc
  *
  * Description  - Process the command from IFCon: COM_DVD_BT_start
  *                IFCON_BT_CMD_START_KEY_CONNECTION: [CONNECTION/PAIRING BLUETOOTH] key short <STR>
  *                IFCON_BT_CMD_START_KEY_PAIRING:        [CONNECTION/PAIRING BLUETOOTH] key long  <STR> / [PAIRING] key <BAR>
  *
  * Inputs        - e_bt_start_key:
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_ifcon_cmd_bt_start_key_proc(E_IFCON_BT_CMD_START_E e_bt_start_key)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> BT key from IFCON: %d\n", e_bt_start_key));

    switch (e_bt_start_key)
    {
        case IFCON_BT_CMD_START_KEY_PAIRING:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Detect [PAIRING] key\n"));

            _bt_app_ifcon_cmd_bt_pairing_key_proc();

            break;
        }
        case IFCON_BT_CMD_START_KEY_CONNECTION:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Detect [CONNECTION] key\n"));

            _bt_app_ifcon_cmd_bt_connection_key_proc();

            break;
        }
        default:
        {
            break;
        }
    }

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_ifcon_cmd_nfc_start_proc
  *
  * Description  - Process the command from IFCon: COM_DVD_NFC_start
  *
  * Inputs        - e_nfc_cmd:
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_ifcon_cmd_nfc_start_proc(E_IFCON_NFC_CMD_START_E e_nfc_cmd)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s: process NFC command[%d] from IFCON\n", __FUNCTION__, e_nfc_cmd));

    switch (e_nfc_cmd)
    {
        case IFCON_NFC_CMD_START_VALID: // When NFC device touch, IFCon send this command.
        {
            // set flag
            bt_app_set_flag_nfc_detected(TRUE);

            /* when detected NFC touch, MTK callback to notify  X2 nfc touch event
                     *  X2 change bluetooth mode to Receiver forcibly if  in Transmitter mode by calls config_bluetooth_set()
                     *  SRC device initiate to connect at other than bluetooth function, X2 need to start bluetooth function in special case
                     *  Special case:1. network is connected 2.NFC is detected 3. If BRAVIA TV is connected
                     *  Normal case: do nothing, X2 do not start bluetooth audio function
                     */
            bt_app_notify_nfc_detected_to_x2();

            // start NFC touch timer when NFC touch
            _bt_app_start_nfc_touch_timer();

            if(!bt_app_is_bluetooth_audio_function_start())  // Bluetooth function hasn't been started.
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> Detect NFC touch in other than BT function\n"));

                // 1. turn on bluetooth RF
                if(!a_bt_is_bluetooth_enabled())
                {
                    a_bt_enable_disable(TRUE);
                }

                if (bt_app_output_a2dp_connected())
                {
                    /* If output a2dp is connected, disconnect it first, bluetooth mode will be changed in disconnect proc */
                    BT_APP_LOG_DEFAULT(("<BT_APP> Output a2dp is connected, need to disconnect it due to NFC touch coming\n"));

                    bt_app_disconnect_with_sink_dev();
                }
                else
                {
                    /* no bt connection existed then change to receiver mode forcilbly */
                    BT_APP_LOG_DEFAULT(("<BT_APP> Set internal bluetooth mode to Receiver due to NFC touch\n"));

                    a_bt_bluetooth_mode_set(CFG_BLUETOOTH_MODE_RECEIVER);
                }
            }
            else     // Bluetooth function has been started.
            {
                // show message "A Device has been detected, Please wait a moment."
                BT_APP_LOG_DEFAULT(("<BT_APP> Detect NFC touch in BT function, show message: Device has been detected.\n"));

                a_comm_warn_begin(COMM_WARN_M_BT_D_NFC_DEVICE_DETECTED);
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return BT_APPR_OK;
}
#endif


/**---------------------------------------------------------------------------
  * Name          - _bt_app_event_nfc_touch_time_out_proc
  *
  * Description  - Process the event: no device request to connect after NFC touch
  *                       1. turn off bluetooth
  *                       2. Show warning
  *                       3. send ERROR msg to IFCon
  *---------------------------------------------------------------------------*/
static VOID _bt_app_event_nfc_touch_time_out_proc(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> process NFC time out\n"));

    // Send ERROR msg to IFCon, IFCon will show "Not Connect" on VFD.
    //d_ifcon_bt_message_no();

    if(bt_app_is_bluetooth_audio_function_start())
    {
    }
    else
    {
        // NFC Spec:
        // NFC in Receiver mode: bluetooth mode is no change
        // NFC in Transmitter mode: change to receiver mode, even after exit from BT function, bluetooth mode is Reciever mode
        // NFC in OFF mode: turn on recevier mode temporarily, and after exit from BT function, turn off BT, bluetooth mode is still OFF.
        a_bt_enable_disable_recovery(TRUE);
    }
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_function_key_stt_change_proc
  *
  * Description  - Process the event: the status of [FUNCTION] key is changed
  *                     According to HI spec, Bluetooth connect is prohibitted when [FUNCTION] key is disable.
  *                     So we need turn off Bluetooth and NFC when [FUNCTION] key is disable, and recover it
  *                     when [FUNCTION] key is enable.
  *
  * Inputs        - b_enable, TRUE: [FUNCTION] key is enable, FALSE: [FUNCTION] key is disable
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_function_key_stt_change_proc(BOOL b_enable)
{
    if(bt_app_is_bluetooth_audio_function_start())
    {
        // function key status should not change in BT function
        BT_APP_LOG_DEFAULT(("<BT_APP> In BT function, ignore function key stt change\n"));
        return BT_APPR_OK;
    }

    if(b_enable)  // [FUNCTION] key is enable
    {
        // Turn on bluetooth device if bluetooth mode is Receiver mode and paired src device existed
        //a_bt_enable_disable_recovery(TRUE);

        BT_APP_LOG_INFO(("<BT_APP> %s, FUNCTION key enabled\n", __FUNCTION__));

        // notify NFC status to IFCon.
        //a_cfg_get_nfc_enable_state(&ui1_nfc_setting);
        //d_ifcon_set_sys_nfc_stt(ui1_nfc_setting);
    }
    else         // [FUNCTION] key is disable
    {
        // turn off Bluetooth RF
        //if(a_bt_is_bluetooth_enabled())
        //{
        //    a_bt_enable_disable(FALSE);
        //}
        //for BDP00420235
        // 1. BT is enabled 2. NFC is diaalbed 3. Function change is blocked in  side

        BT_APP_LOG_INFO(("<BT_APP> %s, FUNCTION key disabled\n", __FUNCTION__));

        // notify NFC status: OFF to IFCon
        //d_ifcon_set_sys_nfc_stt(NFC_OFF);
    }

    return BT_APPR_OK;
}


/**------------------------------------------------------------------------------------------------------------------
  * Name          - _bluetooth_avrcp_cmd_map_key_code
  *
  * Description  - Refer to I2C_Category_DVD_CD_forMTK_Ver004.xlsx "Key Remocon" sheet
  *
  * Inputs        -  arg[in] BT_AVRCP_CMD_TYPE
  *
  * Returns       - arg[out] e_key_code
  *------------------------------------------------------------------------------------------------------------------*/
VOID _bluetooth_avrcp_cmd_map_key_code(BT_AVRCP_CMD_TYPE bt_cmd_type, BT_APP_AVRCP_KEY_CODE_E *e_key_code)
{
    *e_key_code = BT_APP_AVRCP_KEY_CODE_NONE;
    switch (bt_cmd_type)
    {
        case BT_AVRCP_CMD_TYPE_PLAY:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_PLAY;
            break;
        case BT_AVRCP_CMD_TYPE_PAUSE:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_PAUSE;
            break;
        case BT_AVRCP_CMD_TYPE_FWD:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_NEXT;
            break;
        case BT_AVRCP_CMD_TYPE_BWD:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_PREV;
            break;
        case BT_AVRCP_CMD_TYPE_FFWD:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_FF;
            break;
        case BT_AVRCP_CMD_TYPE_RWD:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_FR;
            break;
        case BT_AVRCP_CMD_TYPE_STOP:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_STOP;
            break;
        default:
            *e_key_code = BT_APP_AVRCP_KEY_CODE_NONE;
            break;
    }

    BT_APP_LOG_INFO(("<BT_APP> IR key code:%d\n",*e_key_code));
}

CoreInputDevice * g_pdevice = NULL;

static DFBEnumerationResult EnumInputDevices_Callback(CoreInputDevice * device,void * ctx)
{
    if (g_pdevice == NULL)
        g_pdevice = device;

    return DFENUM_OK;
}

VOID _bt_key_send_by_dfb(DFBInputDeviceKeySymbol syb,
        int keyCode, DFBInputDeviceKeyIdentifier keyId,UINT8 press)
{
    DFBInputEvent event;

    do
    {
        dfb_input_enumerate_devices(EnumInputDevices_Callback, NULL, DICAPS_ALL);
        if (g_pdevice == NULL)
        {
            BT_APP_LOG_ERR(("_bt_key_send_by_dfb can not get the dfb device\n"));
           break;
        }
		if (press == 1)
		{
	        event.type = DIET_KEYPRESS;
	        event.flags =
	            (DFBInputEventFlags)(DIEF_KEYSYMBOL | DIEF_KEYCODE | DIEF_KEYID);
	        event.key_symbol = syb;
	        event.key_code = keyCode;
	        event.key_id = keyId;
	        BT_APP_LOG_INFO(("key_symbol press : 0x%x, key_code: %d, key_id: %d \n", syb, keyCode, keyId));
	        dfb_input_dispatch(g_pdevice, &event);
        }
		else if (press == 0)
		{
	        event.type = DIET_KEYRELEASE;
	        event.flags =
	            (DFBInputEventFlags)(DIEF_KEYSYMBOL | DIEF_KEYCODE | DIEF_KEYID);
	        event.key_symbol = syb;
	        event.key_code = keyCode;
	        event.key_id = keyId;
	        BT_APP_LOG_INFO(("key_symbol release: 0x%x, key_code: %d, key_id: %d \n", syb, keyCode, keyId));
	        dfb_input_dispatch(g_pdevice, &event);
		}
		else
		{
	        BT_APP_LOG_INFO(("_bt_key_send_by_dfb press is invalid: %d \n", press));
		}

    } while(0);
	return;

}


/**------------------------------------------------------------------------------------------------------------------
  * Name          - _bluetooth_avrcp_cmd_map_bdp_key_code
  *
  * Description  -
  *
  * Inputs        -  arg[in] BT_AVRCP_CMD_TYPE
  *
  * Returns       - arg[out] e_key_code
  *------------------------------------------------------------------------------------------------------------------*/
DFBInputDeviceKeySymbol _bluetooth_avrcp_cmd_map_bdp_key_code(BT_AVRCP_CMD_TYPE bt_cmd_type)
{
    DFBInputDeviceKeySymbol e_key_code=BT_AVRCP_CMD_TYPE_MAX;

    switch (bt_cmd_type)
    {
        case BT_AVRCP_CMD_TYPE_PLAY:
            e_key_code = BTN_SELECT;
            break;
        case BT_AVRCP_CMD_TYPE_PAUSE:
            e_key_code = BTN_SELECT;
            break;
        case BT_AVRCP_CMD_TYPE_FWD:
            e_key_code = BTN_PRG_UP;
            break;
        case BT_AVRCP_CMD_TYPE_BWD:
            e_key_code = BTN_PRG_DOWN;
            break;
        case BT_AVRCP_CMD_TYPE_FFWD:
            e_key_code = BTN_FF;
            break;
        case BT_AVRCP_CMD_TYPE_RWD:
            e_key_code = BTN_FR;
            break;
        case BT_AVRCP_CMD_TYPE_STOP:
            e_key_code = BTN_FAV_CH;
            break;
        default:
            break;
    }

    BT_APP_LOG_INFO(("<BT_APP> BDP receive avrcp key code:%d\n", e_key_code));

    return e_key_code;
}


/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_avrcp_cmd_map_sircs_cmd
  *
  * Description  - BDV7G model refer to <CMDV_BDV7G.xlsx>, IV model refer to <Command-V_IV_Remote_Key_rev5.xlsx>
  *
  * Inputs        -  arg[in] BT_AVRCP_CMD_TYPE
  *
  * Returns       - arg[out] e_key_code
  *------------------------------------------------------------------------------------------------------------------*/
VOID bluetooth_avrcp_cmd_map_sircs_cmd(BT_AVRCP_CMD_TYPE bt_cmd_type,
                                                UINT8 *ui1_high_category_code,
                                                UINT8 *ui1_low_category_code,
                                                UINT8 *ui1_key_code)
{
    #if 0
    if(d_is_soundbar_model() || d_is_str15_model())
    {
        *ui1_high_category_code = 0x01;
        *ui1_low_category_code = 0x10;

        switch (bt_cmd_type)
        {
            case BT_AVRCP_CMD_TYPE_PLAY:
                *ui1_key_code = 0x32;
                break;
            case BT_AVRCP_CMD_TYPE_PAUSE:
                *ui1_key_code = 0x39;
                break;
            case BT_AVRCP_CMD_TYPE_FWD:
                *ui1_key_code = 0x31;
                break;
            case BT_AVRCP_CMD_TYPE_BWD:
                *ui1_key_code = 0x30;
                break;
            case BT_AVRCP_CMD_TYPE_FFWD:
                *ui1_key_code = 0x34;
                break;
            case BT_AVRCP_CMD_TYPE_RWD:
                *ui1_key_code = 0x33;
                break;
            case BT_AVRCP_CMD_TYPE_STOP:
                *ui1_key_code = 0x38;
                break;
            default:
                *ui1_high_category_code = 0x00;
                *ui1_low_category_code = 0x00;
                *ui1_key_code = 0x00;
                break;
        }
    }
    else
    {
        switch (bt_cmd_type)
        {
            case BT_AVRCP_CMD_TYPE_PLAY:
                *ui1_high_category_code = 0x00;
                *ui1_low_category_code = 0xD0;
                *ui1_key_code = 0x02;
                break;
            case BT_AVRCP_CMD_TYPE_PAUSE:
                *ui1_high_category_code = 0x00;
                *ui1_low_category_code = 0xD0;
                *ui1_key_code = 0x01;
                break;
            case BT_AVRCP_CMD_TYPE_FWD:
                *ui1_high_category_code = 0x02;
                *ui1_low_category_code = 0x10;
                *ui1_key_code = 0x31;
                break;
            case BT_AVRCP_CMD_TYPE_BWD:
                *ui1_high_category_code = 0x02;
                *ui1_low_category_code = 0x10;
                *ui1_key_code = 0x30;
                break;
            case BT_AVRCP_CMD_TYPE_FFWD:
                *ui1_high_category_code = 0x02;
                *ui1_low_category_code = 0x10;
                *ui1_key_code = 0x34;
                break;
            case BT_AVRCP_CMD_TYPE_RWD:
                *ui1_high_category_code = 0x02;
                *ui1_low_category_code = 0x10;
                *ui1_key_code = 0x33;
                break;
            case BT_AVRCP_CMD_TYPE_STOP:
                *ui1_high_category_code = 0x00;
                *ui1_low_category_code = 0xD0;
                *ui1_key_code = 0x00;
                break;
            default:
                *ui1_high_category_code = 0x00;
                *ui1_low_category_code = 0x00;
                *ui1_key_code = 0x00;
                break;
        }
    }

    BT_APP_LOG_INFO(("<BT_APP> Sircs cmd:: high category code:0x%2x, low category code:0x%2x, key code:0x%2x\n",    \
        *ui1_high_category_code, *ui1_low_category_code, *ui1_key_code));
    #endif
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_src_mode_avrcp_key_cmd_proc
  *
  * Description  - Process AVRCP key command from BTM, 2 method to implement
  *                    1. Send sircs command to IFCON,IFCON behave as if the command come from real buttons or remote commander.
  *                    2. Directly process key in MTK, key code will send to IOM(then send to AM/Widget) and Lircd_simulator(then send to DFB)
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_src_mode_avrcp_key_cmd_proc(BT_AVRCP_CMD_TYPE bt_cmd_type, UINT8 press)
{
    INT32 i4_ret = PBR_OK;

    DFBInputDeviceKeySymbol dfb_key_code;


    BT_APP_LOG_DEFAULT(("<BT_APP> %s(), cmd_type:%d, state:%d\n",__FUNCTION__, bt_cmd_type, press));


    {
        dfb_key_code = _bluetooth_avrcp_cmd_map_bdp_key_code(bt_cmd_type);

        switch (bt_cmd_type)
        {
            case BT_AVRCP_CMD_TYPE_PLAY:
            case BT_AVRCP_CMD_TYPE_PAUSE:
            case BT_AVRCP_CMD_TYPE_FWD:
            case BT_AVRCP_CMD_TYPE_BWD:
            case BT_AVRCP_CMD_TYPE_FFWD:
            case BT_AVRCP_CMD_TYPE_RWD:
            case BT_AVRCP_CMD_TYPE_STOP:
                _bt_key_send_by_dfb(dfb_key_code, 0, DIKI_UNKNOWN,press);
				BT_APP_LOG_ERR(("<BT_APP> DFB AVRCP cmd_type:%d\n",bt_cmd_type));
                break;
            default:
                BT_APP_LOG_ERR(("<BT_APP> ERR: Invalid AVRCP cmd_type:%d\n",bt_cmd_type));
				i4_ret= PBR_FAIL;
                break;
        }
    }

    return i4_ret;

}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_src_mode_upload_info_proc
  *
  * Description  - set downsample according to sample_freq, because LDAC support 44.1 ~ 96kHZ, only LDAC case will notify this info
  *
  * Inputs        - sample_freq: 44100, 48000, 88200, 96000
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_src_mode_upload_info_proc(BOOL fg_only_check_mute, VOID* pv_data)
{
    INT32 i4_ret = PBR_OK;
    //BT_A2DP_UPLOAD_INFO* pt_upload_info = NULL;

    //pt_upload_info = (BT_A2DP_UPLOAD_INFO*)pv_data;

    //only check pt_upload_info.fgNeedMuteACP
    if(fg_only_check_mute)
    {
        /* if detect HDMI input ACP type 2/3, need to mute output and show warning */
        if (!bt_app_is_sink_dev_list_start()
            /*&& (TRUE == pt_upload_info->fgNeedMuteACP)*/)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> HDMI Input source with HDCP ACP type = 2 or 3, show W-EI03\n"));

            bt_app_set_flag_show_content_protect_warn(TRUE);

        }
    }

    return i4_ret;
}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_sink_device_scan_start_proc
  *
  * Description  -
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_sink_device_scan_start_proc(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    bt_app_start_a2dp_snk_inquiry_scan(TIME_OUT_SINK_DEVICE_GUI_SCAN);

    return i4_ret;
}

#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_sink_device_scan_finish_amp_menu_proc
  *
  * Description  - Only for STR model, data sync proc
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_sink_device_scan_finish_amp_menu_proc(VOID)
{
    BT_APP_SINK_DEV_LIST_INFO_T r_sink_dev_list_info;
    //IFCON_BT_STT_SCAN_T         r_bt_stt_scan = {0};
    UINT8                       u1_detected_dev_num = 0;

    c_memset(&r_sink_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));

    bt_app_ui_bt_sink_dev_list_info_get(&r_sink_dev_list_info);

    // limit the scanning result within 10
    if (r_sink_dev_list_info.u1_unpaired_dev_num + r_sink_dev_list_info.u1_paired_dev_scanned_num > 10)
    {
        u1_detected_dev_num = 10;
    }
    else
    {
        u1_detected_dev_num = r_sink_dev_list_info.u1_unpaired_dev_num + r_sink_dev_list_info.u1_paired_dev_scanned_num;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP><STR> Scaning process is completed in AMP Menu, paired scanned dev num[%d], unpaired dev num[%d], total device[%d]\n",  \
        r_sink_dev_list_info.u1_paired_dev_scanned_num, r_sink_dev_list_info.u1_unpaired_dev_num, u1_detected_dev_num));

    /* Inform IFCON scan result */
    //r_bt_stt_scan.e_bt_scan_mode      = IFCON_BT_STT_SCAN_MODE_STOP;
    //r_bt_stt_scan.u1_detected_dev_num = u1_detected_dev_num;
    //d_ifcon_set_stt_bt_scan(r_bt_stt_scan);

    return BT_APPR_OK;
}

#endif

/**---------------------------------------------------------------------------
  * Name          - _bt_app_sink_device_scan_finish_proc
  *
  * Description  -
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_sink_device_scan_finish_proc(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    /* stop scan timer */
    i4_ret = bt_app_stop_sink_device_scan_timer();
    if(i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: stop sink scan timer fail, %d\n", i4_ret));
    }

    i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
    if(i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: stop sink inquiry fail, %d\n", i4_ret));
    }

    /* Update sink device data */
    bt_app_ui_sink_dev_list_data_update(TRUE);

    /* clear flag to indicate scaning finished */
    bt_app_set_flag_sink_dev_scaning(FALSE);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));

    return i4_ret;
}

/*! \fn INT32 pb_normal_return_key_proc(
    UINT32 ui4_key)
    \brief this function is to process return key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_normal_return_key_proc(UINT32 ui4_key)
{
    INT32       i4_ret = PBR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s: Detect [BACK] key\n", __FUNCTION__));

    if (bt_app_is_bluetooth_audio_function_start())
    {
        if( _e_bluetooth_state == BLUETOOTH_MUSIC_PLAYBACK_STATE )
        {
            bt_app_disconnect_with_src_dev();
        }
        else if(BLUETOOTH_SRC_DEVICE_LIST_STATE == _e_bluetooth_state)
        {
            //i4_ret = c_btm_btstart("PAIRING", 300);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }
    }
    else if (bt_app_is_sink_dev_list_start()
        ||bt_app_is_audio_output_dev_list_start())
    {
        bt_app_close_sink_device_list();
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> %s, error case\n", __FUNCTION__));
    }

    return BT_APPR_OK;
}

/*! \fn INT32 pb_bluetooth_sink_mode_normal_option_key_proc(
    UINT32 ui4_key)
    \brief this function is to process option key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_src_mode_normal_option_key_proc(UINT32 ui4_key)
{
    INT32   i4_ret = BT_APPR_OK;
    UINT8   u1_total_dev_num = 0;
    UINT8   u1_focus_row_index = 0;
    static BT_APP_SINK_DEV_LIST_INFO_T r_sink_dev_list_info;

    BT_APP_LOG_API(("<BT_APP><Sink_list> Enter %s\n", __FUNCTION__));

    c_memset(&r_sink_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));

    bt_app_ui_bt_sink_dev_list_info_get(&r_sink_dev_list_info);

    u1_total_dev_num = r_sink_dev_list_info.u1_total_dev_num;
    u1_focus_row_index = r_sink_dev_list_info.u1_focus_row_index;

    /* Option menu is displayed only when list has device and focus on the device */
    if ((u1_total_dev_num != 0) && (u1_focus_row_index < BT_APP_SINK_DEVICE_NUM_PER_PAGE))
    {
        /* Adjust focus row text color */
        bt_app_ui_bt_sink_dev_list_set_focus(u1_focus_row_index, FALSE);
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_sink_device_list_key_proc
  *
  * Description  -
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_sink_device_list_key_proc(UINT32 ui4_msg, UINT32 ui4_key)
{
    INT32   i4_ret;
    UINT8   u1_focus_row_index = 0;
    UINT8   u1_first_dev_index = 0;
    UINT8   u1_focus_dev_index = 0;
    BT_TARGET_DEV_INFO t_target_device = {0,0,{0},{0}};

    u1_focus_row_index = _gt_bt_sink_dev_list_info.u1_focus_row_index;
    u1_first_dev_index = _gt_bt_sink_dev_list_info.u1_first_dev_index;
    u1_focus_dev_index = u1_first_dev_index + u1_focus_row_index;

    BT_APP_LOG_API(("<BT_APP> %s is called\n", __FUNCTION__));

    switch (ui4_key)
    {
        case BTN_ENTER:
        {
            if (ui4_msg == WGL_MSG_KEY_DOWN)
            {
                if (bt_app_output_a2dp_connected() && (u1_focus_dev_index == 0))
                {
                    /* Focused device is already connected, then disconnect it */
                    bt_app_disconnect_with_sink_dev();
                }
                else if(bt_app_keyboard_mouse_connected()&& (u1_focus_dev_index == 0))
                {
                    c_memset(&t_target_device, 0, sizeof(BT_TARGET_DEV_INFO));

                    i4_ret = bt_app_ui_sink_device_list_get_focused_device(&t_target_device);

                    BT_APP_LOG_DEFAULT(("<BT_APP> get focused device name=%s, addr=%s cod=0x%x\n",
                                                        t_target_device.name, t_target_device.bdAddr));

                    if(i4_ret != BT_APPR_OK)
                    {
                        BT_APP_LOG_ERR(("<BT_APP> ERR: get focused sink device fail, %d\n", i4_ret));
                        return BT_APPR_OK;
                    }

                    #if 0
                    if((t_target_device.cod&0x0500)==0x0500)
                    {
                        if(((t_target_device.cod&0x40)==0x40)
                            ||((t_target_device.cod&0x80)==0x80)
                            ||((t_target_device.cod&0xC0)==0xC0))
                        {
                            c_btm_disconnect_hid_sources(t_target_device.bdAddr);
                        }
                    }
                    #endif
                }
                else
                {
                    /* Get target device info from sink device list */
                    c_memset(&t_target_device, 0, sizeof(BT_TARGET_DEV_INFO));

                    i4_ret = bt_app_ui_sink_device_list_get_focused_device(&t_target_device);

                    BT_APP_LOG_DEFAULT(("<BT_APP> get focused device name=%s, addr=%s cod=0x%x\n",
                                                        t_target_device.name, t_target_device.bdAddr));

                    if(i4_ret != BT_APPR_OK)
                    {
                        BT_APP_LOG_ERR(("<BT_APP> ERR: get focused sink device fail, %d\n", i4_ret));
                        return BT_APPR_OK;
                    }

                    #if 0
                    if((t_target_device.cod&0x0500)==0x0500)
                    {
                        if(((t_target_device.cod&0x40)==0x40)
                            ||((t_target_device.cod&0x80)==0x80)
                            ||((t_target_device.cod&0xC0)==0xC0))
                        {
                            BT_APP_LOG_DEFAULT(("<BT_APP> Start to connect keyboard&mouse device %s\n",
                                                                        t_target_device.bdAddr));
                            c_btm_connect_hid_sources(t_target_device.bdAddr);
                        }
                    }
                    else
                    #endif
                    {
                        /* Focused device is not connected, then connect to it */
                        bt_app_connect_with_sink_dev(FALSE, &t_target_device);
                    }
                }
            }
            break;
        }
        case BTN_CURSOR_UP:
        case BTN_CURSOR_DOWN:
        {
            break;
        }
        default:
            break;
    }

    return BT_APPR_OK;

}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_bt_mode_setting_chg_proc
  *
  * Description  -
  *
  * Inputs        - u1_bt_mode_cfg: bt mode in bluetooth setting
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_bt_mode_setting_chg_proc(UINT8 u1_bt_mode_cfg)
{
    BOOL    b_bt_need_power_on = TRUE;
    UINT8   u1_bt_setting_mode = 0;
	UINT8   u1_bt_switch_staus= 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Receive notify, bt mode setting change to: %d\n", u1_bt_mode_cfg));

    //get current bluetooth config setting
    a_cfg_get_bluetooth_switch_status(&u1_bt_switch_staus);
	a_cfg_get_bluetooth_mode_status(&u1_bt_setting_mode);

    // check if bt mode request to change is same as current setting value or not
    // to avoid frequently change bt mode
    if (u1_bt_setting_mode != u1_bt_mode_cfg)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: Func:%s : request mode[%d] don't match with current setting value[%d]\n", __FUNCTION__, u1_bt_mode_cfg, u1_bt_setting_mode));
        return BT_APPR_OK;
    }

    /* Exit sink device list */
    if (bt_app_is_sink_dev_list_start())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, close sink device list\n", __FUNCTION__));

        bt_app_close_sink_device_list();
    }

    if (!bt_app_input_a2dp_connected()
        && !bt_app_output_a2dp_connected()
        &&!bt_app_hid_connected())
    {
        /* there is no any connection */
        BT_APP_LOG_DEFAULT(("<BT_APP> BT mode setting change, no any connection exist\n"));

        //condition to set bt power on:
        //1. Transmitter mode
        //2. Receiver mode and SRC paired device is existed
        //if (((CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode_cfg) && (a_bt_app_get_paired_src_device_num() == 0))
        //    || (APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_mode_cfg))
        if(APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_switch_staus)
        {
            b_bt_need_power_on = FALSE;
        }
        else
        {
            b_bt_need_power_on = TRUE;
        }

        if (b_bt_need_power_on)
        {
            /* turn on BT RF before change internal bt mode */
            if(a_bt_is_bluetooth_enabled() != b_bt_need_power_on)
            {
                a_bt_enable_disable(b_bt_need_power_on);
            }

            if (a_bt_bluetooth_mode_get() != u1_bt_mode_cfg)
            {
                a_bt_bluetooth_mode_set(u1_bt_mode_cfg);
            }
        }
        else
        {
            /* change internal bt mode before close bt power */
            if (a_bt_bluetooth_mode_get() != u1_bt_mode_cfg)
            {
                a_bt_bluetooth_mode_set(u1_bt_mode_cfg);
            }

            if(a_bt_is_bluetooth_enabled() != b_bt_need_power_on)
            {
                a_bt_enable_disable(b_bt_need_power_on);
            }
        }

    }
    else
    {
        // Check if bluetooth is connected
        BT_APP_LOG_DEFAULT(("<BT_APP> BT mode setting change, input a2dp connected:%s, output a2dp connected:%s\n", \
        (bt_app_input_a2dp_connected() ? "TRUE" : "FALSE"), (bt_app_output_a2dp_connected() ? "TRUE" : "FALSE")));

        // if input a2dp is connected, and bluetooth is change to other than receiver mode, disconnect it
        if (bt_app_input_a2dp_connected())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Input a2dp is connected, bluetooth mode change to %d, start disconnect a2dp\n", u1_bt_mode_cfg));

            bt_app_set_setting_mode_changed(TRUE);

            //c_btm_stop(FALSE,FALSE);
        }

        // if output a2dp is connected, and bluetooth is change to other than transmitter mode, disconnect it
        if (bt_app_output_a2dp_connected() && (APP_CFG_BLUETOOTH_SWITCH_SOURCE!= u1_bt_mode_cfg))
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Output a2dp is connected, bluetooth mode change to %d, start disconnect a2dp\n", u1_bt_mode_cfg));

            bt_app_set_setting_mode_changed(TRUE);

            bt_app_disconnect_with_sink_dev();
        }

        if(bt_app_hid_connected()&&(APP_CFG_BLUETOOTH_SWITCH_SOURCE!= u1_bt_mode_cfg))
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> HID is connected, bluetooth mode change to %d, start disconnect HID\n", u1_bt_mode_cfg));

            bt_app_set_setting_mode_changed(TRUE);

            bt_app_hid_disconnect_all();
        }
    }

    BT_APP_LOG_API(("<BT_APP> Exit %s\n", __FUNCTION__));

    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_bt_dongle_attach_nfy_proc
  *
  * Description  - When power on, wait for bt dongle attach, when receive this notify, set bt RF and bluetooth mode
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_bt_dongle_attach_nfy_proc(VOID)
{
    // unlock semaphore to inform bt device is attached
    //bt_app_dongle_attach_sema_unlock();
    //BT_APP_LOG_ERR(("_bt_app_bt_dongle_attach_nfy_proc:%s\n",__FUNCTION__));
    INT32 i = 40;
    if (!a_bt_app_has_init())
    {
        while(i)
        {
            if(access("/sys/bus/usb/drivers/btmtk_usb", F_OK) == 0)
            {
                BT_APP_LOG_ERR(("BT ko inmsmod is  OK Func:%s\n",__FUNCTION__));
                break;
            }
            else
            {
                BT_APP_LOG_ERR(("wait BT ko ismod sleep 500ms Func:%s\n",__FUNCTION__));
                c_thread_delay(500);
                i--;
                if (i<=0)
                {
                    BT_APP_LOG_ERR(("wait BT ko 20s, return Func:%s\n",__FUNCTION__));
                    return BT_APPR_FAIL;
                }
            }
        }

        BT_APP_LOG_ERR(("sleep 5s, Func:%s\n",__FUNCTION__));
        c_thread_delay(5000);

        bluetooth_init();
        bluetooth_system_power_on_proc();

    }
    else
    {
        a_bt_system_bootup_sequence_init();
    }

#ifdef APP_BLE_SUPPORT
    INT32 i4_ret = 0;
    i4_ret = bt_aud_sendmsg_to_ble_gatt(BT_MSG_TO_GATT_APP);
    BT_APP_CHK_FAIL(i4_ret, i4_ret);
#endif


    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_bt_tx_device_list_req_proc
  *
  * Description  - IFCON send REQ_DVD_BT_bt_tx_device_list to get specific sink device information
  *
  * Inputs        - u1_sink_dev_index: specify which index in the scanning sink device list, include paired and unpaired device
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_bt_tx_device_list_req_proc(UINT8 u1_sink_dev_index)
{
    //IFCON_BT_STT_TX_DEV_LIST_T     t_bt_stt_tx_device;
    static BT_APP_SINK_DEV_LIST_INFO_T    r_sink_dev_list_info;
    BT_APP_DEVICE_INFO_T           r_target_dev_info;
    UINT8                          u1_paired_dev_num = 0;
    UINT8                          u1_unpaired_dev_num = 0;
    UINT8                          u1_paired_scanned_dev_num = 0;
    UINT8                          u1_detected_dev_num = 0;
    UINT8                          u1_name_length = 0;
    UINT8                          u1_index = 0;
    UINT8                          u1_paired_scanned_dev_sum = 0;
    UINT8                          u1_target_index = BT_APP_TOTAL_SINK_DEV_MAX;

    //c_memset(&t_bt_stt_tx_device, 0, sizeof(IFCON_BT_STT_TX_DEV_LIST_T));
    c_memset(&r_sink_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));
    c_memset(&r_target_dev_info, 0, sizeof(BT_APP_DEVICE_INFO_T));

    bt_app_ui_bt_sink_dev_list_info_get(&r_sink_dev_list_info);

    u1_paired_dev_num = r_sink_dev_list_info.u1_paired_dev_num;

    u1_unpaired_dev_num = r_sink_dev_list_info.u1_unpaired_dev_num;

    u1_paired_scanned_dev_num = r_sink_dev_list_info.u1_paired_dev_scanned_num;

    // total detected device include paired and unpaired sink device, limited within 10
    u1_detected_dev_num = u1_paired_scanned_dev_num + u1_unpaired_dev_num;

    // u1_sink_dev_index start from 0 ~ N-1 (N:u1_detected_dev_num)
    if (u1_sink_dev_index >= u1_detected_dev_num)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: req tx device list, index[%d], paired scanned dev num[%d], unpaired scanned dev num[%d], total detected dev num[%d]\n", \
            u1_sink_dev_index, u1_paired_scanned_dev_num, u1_unpaired_dev_num, u1_detected_dev_num));
        return BT_APPR_OK;
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> req tx device list, index[%d], paired scanned dev num[%d], unpaired scanned dev num[%d], total detected dev num[%d]\n", \
            u1_sink_dev_index, u1_paired_scanned_dev_num, u1_unpaired_dev_num, u1_detected_dev_num));
    }

    if (u1_sink_dev_index < u1_paired_scanned_dev_num)
    {
        // the device lie in paired device list
        for (u1_index = 0; u1_index < BT_APP_PAIRED_SINK_DEV_MAX; u1_index++)
        {
            // find scanned device
            if (r_sink_dev_list_info.au1_paired_dev_scan_status[u1_index] == 0x01)
            {
                u1_paired_scanned_dev_sum++;

                if (u1_sink_dev_index < u1_paired_scanned_dev_sum)
                {
                    u1_target_index = u1_index;

                    r_target_dev_info = r_sink_dev_list_info.sink_dev_list[u1_target_index];

                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    else
    {
        // the device lie in unpaired device list
        u1_target_index = u1_paired_dev_num + u1_sink_dev_index - u1_paired_scanned_dev_num;
        r_target_dev_info = r_sink_dev_list_info.sink_dev_list[u1_target_index];
    }

    if (u1_target_index < BT_APP_TOTAL_SINK_DEV_MAX)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s : index[%d], target index[%d]\n", __FUNCTION__, u1_sink_dev_index, u1_target_index));

        u1_name_length = (UINT8)c_strlen(r_target_dev_info.ac_name);
        if (u1_name_length > 20)
        {
            u1_name_length = 20;
        }

        //t_bt_stt_tx_device.u1_dev_index   = u1_sink_dev_index;
        //t_bt_stt_tx_device.u1_name_length = u1_name_length;

        //c_strncpy(t_bt_stt_tx_device.ac_dev_name, r_target_dev_info.ac_name, u1_name_length);

        //d_ifcon_set_stt_bt_tx_device_list(t_bt_stt_tx_device);
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: Func:%s : can't find the target.\n", __FUNCTION__));
    }

    return BT_APPR_OK;
}

#if 0
/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_data_sync_ifcon_bt_cmd_scan_cancel_proc
  *
  * Description  -
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_data_sync_ifcon_bt_cmd_scan_cancel_proc(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    IFCON_BT_STT_SCAN_T t_bt_stt_scan = {0};

    BT_APP_LOG_INFO(("<BT_APP><STR> Cancel sink device scaning in AMP Menu\n"));

    if (bt_app_is_sink_dev_scaning())
    {
        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }

    /* Cancel scaning, init as no detected device */
    _gt_bt_sink_dev_list_info.u1_unpaired_dev_num = 0;
    _gt_bt_sink_dev_list_info.u1_total_dev_num = _gt_bt_sink_dev_list_info.u1_paired_dev_num;

    /* Send STT_DVD_BT_start to IFCON to inform scaning is started */
    t_bt_stt_scan.e_bt_scan_mode      = IFCON_BT_STT_SCAN_MODE_CANCEL;
    t_bt_stt_scan.u1_detected_dev_num = 0x00;

    d_ifcon_set_stt_bt_scan(t_bt_stt_scan);

    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_data_sync_ifcon_bt_cmd_scan_proc
  *
  * Description  -
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_data_sync_ifcon_bt_cmd_scan_proc(E_IFCON_BT_CMD_SCAN_E e_bt_cmd_scan)
{
    UINT8 u1_bt_mode = 0;

    //read bluetooth mode setting from flash
    a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

    if (!(d_is_str15_model() && (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode)))
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: Not STR model & TX mode\n"));
        return BT_APPR_OK;
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> receive bt scan command:%d\n", e_bt_cmd_scan));
    }

    switch (e_bt_cmd_scan)
    {
        case IFCON_BT_CMD_BT_SCAN_MODE_START:
        {
            _bt_app_amp_menu_start_a2dp_snk_inquiry_scan();
        }
            break;
        case IFCON_BT_CMD_BT_SCAN_MODE_STOP:
            break;
        case IFCON_BT_CMD_BT_SCAN_MODE_CANCEL:
        {
            _bt_app_data_sync_ifcon_bt_cmd_scan_cancel_proc();
        }
            break;
        default:
            break;
    }

    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_data_sync_ifcon_bt_cmd_tx_dev_list_proc
  *
  * Description  - IFCON send COM_DVD_BT_tx_device_list to request to connect device
  *
  * Inputs        - u1_index: specify which index in the unpaired sink device list is going to connect to
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_data_sync_ifcon_bt_cmd_tx_dev_list_proc(UINT8 u1_index)
{
    UINT8 u1_bt_mode = 0;
    BT_APP_SINK_DEV_LIST_INFO_T     r_sink_dev_list_info;
    BT_TARGET_DEV_INFO              t_target_device = {0,0,{0},{0}};
    BT_APP_DEVICE_INFO_T            t_target_device_info;
    UINT8                           u1_detected_dev_base_index = 0;
    UINT8                           u1_unpaired_dev_num = 0;

    //read bluetooth mode setting from flash
    a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

    if (!(d_is_str15_model() && (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode)))
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: Not STR model & TX mode\n"));
        return BT_APPR_OK;
    }

    c_memset(&t_target_device, 0, sizeof(BT_TARGET_DEV_INFO));

    c_memset(&t_target_device_info, 0, sizeof(BT_APP_DEVICE_INFO_T));

    c_memset(&r_sink_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));
    bt_app_ui_bt_sink_dev_list_info_get(&r_sink_dev_list_info);

    u1_detected_dev_base_index = r_sink_dev_list_info.u1_paired_dev_num;

    u1_unpaired_dev_num = r_sink_dev_list_info.u1_unpaired_dev_num;

    if ((u1_index >= u1_unpaired_dev_num)
        || (u1_detected_dev_base_index + u1_index >= BT_APP_TOTAL_SINK_DEV_MAX))
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: receive bt tx device list command, index:%d, total detected device num:%d, base index:%d\n", \
            u1_index, u1_unpaired_dev_num, u1_detected_dev_base_index));
        return BT_APPR_OK;
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> receive bt tx device list command, index:%d, total detected device num:%d, base index:%d\n", \
        u1_index, u1_unpaired_dev_num, u1_detected_dev_base_index));
    }

    // get the target device info
    t_target_device_info = r_sink_dev_list_info.sink_dev_list[u1_detected_dev_base_index + u1_index];

    // copy the target device addr and name
    c_memcpy(t_target_device.bdAddr, t_target_device_info.ac_addr, MAX_BDADDR_LEN);

    c_memcpy(t_target_device.name, t_target_device_info.ac_name, MAX_NAME_LEN);

    bt_app_connect_with_sink_dev(FALSE, &t_target_device);

    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_data_sync_ifcon_bt_cmd_rx_a2dp_connect_disconnect_proc
  *
  * Description  - IFCON send COM_DVD_BT_rx_a2dp_connect_disconnect to request to connect/disconnect device
  *
  * Inputs        - u1_index: E_IFCON_BT_CMD_A2DP_CONNECT_E
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_data_sync_ifcon_bt_cmd_rx_a2dp_connect_disconnect_proc(E_IFCON_BT_CMD_A2DP_CONNECT_E u1_index)
{
    BT_TARGET_DEV_INFO t_device = {0,0,{0},{0}};

    if (!d_is_str15_model())
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, Not STR model\n",__FUNCTION__));
        return BT_APPR_OK;
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> receive bt rx a2dp connect or disconnect command:%d\n", u1_index));
    }

    switch (u1_index)
    {
        case IFCON_BT_CMD_A2DP_CONNECT:
        {
            /* Ony paired src device exist and input a2dp disconnect, process this msg
                    *  IFCON initiates to call input a2dp connection when BT app is already launched in some zone
                    */
            if ((0 != a_bt_app_get_paired_src_device_num())
                && (FALSE == bt_app_input_a2dp_connected())
                && (bt_app_is_bluetooth_audio_function_start()))
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> IFCON trigger to connect to last SRC device\n"));

                // connect to the latest paired device
                bt_app_get_latest_paired_src_device(&t_device);

                //indicate input a2dp connection is triggered by platform itself
                bt_app_set_flag_input_a2dp_initiator(TRUE);

                bt_app_connect(t_device.bdAddr);
            }
        }
            break;
        case IFCON_BT_CMD_A2DP_DISCONNECT:
        {
            /* Only when input a2dp is connected, then disconnect it */
            if (bt_app_input_a2dp_connected())
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> IFCON trigger to disconnect current connected SRC device\n"));

                bt_app_disconnect_with_src_dev();
            }
        }
            break;
        default:
            break;
    }

    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_data_sync_ifcon_bt_cmd_tx_a2dp_connect_disconnect_proc
  *
  * Description  - IFCON send COM_DVD_BT_tx_a2dp_connect_disconnect to request to connect/disconnect device
  *
  * Inputs        - u1_index: E_IFCON_BT_CMD_A2DP_CONNECT_E
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_data_sync_ifcon_bt_cmd_tx_a2dp_connect_disconnect_proc(E_IFCON_BT_CMD_A2DP_CONNECT_E u1_index)
{
    UINT8   u1_bt_mode = 0;

    if (!d_is_str15_model())
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, Not STR model\n",__FUNCTION__));
        return BT_APPR_OK;
    }
    else
    {
        u1_bt_mode = a_bt_bluetooth_mode_get();

        BT_APP_LOG_DEFAULT(("<BT_APP> receive bt tx a2dp connect or disconnect command:%d, bt_mode:%d\n", u1_index, u1_bt_mode));
    }

    switch (u1_index)
    {
        case IFCON_BT_CMD_A2DP_CONNECT:
        {
            /* Ony paired sink device exist and output a2dp disconnect, process this msg */
            if ((0 != a_bt_app_get_paired_sink_device_num())
                && (FALSE == bt_app_output_a2dp_connected())
                && (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode || 3 == u1_bt_mode))
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> IFCON trigger to connect to last SNK device\n"));

                bt_app_connect_with_sink_dev(TRUE, NULL);
            }
        }
            break;
        case IFCON_BT_CMD_A2DP_DISCONNECT:
        {
            /* Only when output a2dp is connected, then disconnect it */
            if (bt_app_output_a2dp_connected())
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> IFCON trigger to disconnect current connected SNK device\n"));

                bt_app_disconnect_with_sink_dev();
            }
        }
            break;
        default:
            break;
    }

    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_data_sync_ifcon_bt_cmd_proc
  *
  * Description  -
  *
  * Inputs        -
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_data_sync_ifcon_bt_cmd_proc(BT_APP_DATA_SYNC_BT_CMD_E e_bt_cmd_type, UINT8 u1_data)
{
    UINT8   u1_bt_setting_mode = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s, receive data sync bt command:%d, data:%d\n", __FUNCTION__, e_bt_cmd_type, u1_data));

    switch (e_bt_cmd_type)
    {
        case BT_APP_DVD_CMD_BT_MODE:
        {
            a_cfg_get_bluetooth_switch_status(&u1_bt_setting_mode);

            if (u1_bt_setting_mode != u1_data)
            {
                if ((bt_app_is_bluetooth_audio_function_start() || pb_is_miracast_mode())
                    && (IFCON_BT_CMD_BTMODE_TRANSMITTER == u1_data))
                {
                    BT_APP_LOG_ERR(("<BT_APP> ERR: BT/Miracast function, ignore COM_DVD_BT_bt_mode(TX)\n"));
                    return BT_APPR_OK;
                }

                /* backup BT MODE */
                a_cfg_set_bluetooth_mode(u1_data);

                /* In case: BT Transmiiter, if paired sink device existed, auto connect to the last one */
                if ((IFCON_BT_CMD_BTMODE_TRANSMITTER == u1_data) && (0 != a_bt_app_get_paired_sink_device_num()))
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP> TX mode, registered device exist, auto connection is to be started\n"));
                }
            }
            else
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> Bluetooth mode setting value not changed, ignore COM_DVD_BT_bt_mode\n"));
            }
        }
            break;

        case BT_APP_DVD_CMD_BT_STANDBY:
        {
            /* backup BT standby mode */
            if (IFCON_BT_CMD_BT_STANDBY_OFF == u1_data)
            {
                a_cfg_set_bluetooth_standby(CFG_BLUETOOTH_STANDBY_OFF);
            }
            else if (IFCON_BT_CMD_BT_STANDBY_ON == u1_data)
            {
                a_cfg_set_bluetooth_standby(CFG_BLUETOOTH_STANDBY_ON);
            }
        }
            break;

        case BT_APP_DVD_CMD_BT_AAC:
        {
            /* backup AAC mode */
            if (IFCON_BT_CMD_BT_AAC_OFF == u1_data)
            {
                a_cfg_set_bluetooth_audio_aac1(CFG_BLUETOOTH_AUDIO_AAC1_OFF);
            }
            else if (IFCON_BT_CMD_BT_AAC_ON == u1_data)
            {
                a_cfg_set_bluetooth_audio_aac1(CFG_BLUETOOTH_AUDIO_AAC1_ON);
            }
        }
            break;
        case BT_APP_DVD_CMD_BT_LDAC:
        {
            /* backup LDAC mode */
            if (IFCON_BT_CMD_BT_LDAC_OFF == u1_data)
            {
                a_cfg_set_bluetooth_audio_ldac(CFG_BLUETOOTH_AUDIO_LDAC_OFF);
            }
            else if (IFCON_BT_CMD_BT_LDAC_ON == u1_data)
            {
                a_cfg_set_bluetooth_audio_ldac(CFG_BLUETOOTH_AUDIO_LDAC_ON);
            }
        }
            break;
        case BT_APP_DVD_CMD_BT_TX_QOS:
        {
            /* backup QOS mode */
            a_cfg_set_bluetooth_transmitter_quality(u1_data);
        }
            break;
        case BT_APP_DVD_CMD_BT_SCAN:
        {
            _bt_app_data_sync_ifcon_bt_cmd_scan_proc(u1_data);
        }
            break;
        case BT_APP_DVD_CMD_BT_TX_DEV_LIST:
        {
            _bt_app_data_sync_ifcon_bt_cmd_tx_dev_list_proc(u1_data);
        }
            break;
        case BT_APP_DVD_CMD_BT_RX_A2DP_CONNECT_DISCONNECT:
        {
            _bt_app_data_sync_ifcon_bt_cmd_rx_a2dp_connect_disconnect_proc(u1_data);
        }
            break;
        case BT_APP_DVD_CMD_BT_TX_A2DP_CONNECT_DISCONNECT:
        {
            _bt_app_data_sync_ifcon_bt_cmd_tx_a2dp_connect_disconnect_proc(u1_data);
        }
            break;
        default:
            break;
    }

    return BT_APPR_OK;
}

/**----------------------------------------------------------------------------------------------
  * Name          - _bt_app_src_mode_pbc_stt_proc
  *
  * Description  - BT output a2dp connected state, when pbc status changed in playback normal window,
  *                    need to START/SUSPEND A2DP streaming according to pbc status.
  *
  * Inputs        - ePBCStt:
  *
  *---------------------------------------------------------------------------------------------*/
static INT32 _bt_app_src_mode_pbc_stt_proc(PB_PBC_STT_E ePBCStt)
{
    switch (ePBCStt)
    {
        case PB_PBC_STT_STOP:
        {
            if(bt_app_is_vol_tmp_display())
            {
                pb_tmp_display_hide();
            }
            c_btm_a2dp_cmd(BT_A2DP_SUSPEND);
            break;
        }
        case PB_PBC_STT_PAUSE:
        //case PB_PBC_STT_SWITCHING_DISC:
        //case PB_PBC_STT_STOP_PARSE:
        //case PB_PBC_STT_PREV_NEXT:
        //case PB_PBC_STT_NOT_LAST_FIlE:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ePBCStt:%d, set a2dp SUSPEND\n",ePBCStt));
            c_btm_a2dp_cmd(BT_A2DP_SUSPEND);
            break;
        }
        case PB_PBC_STT_PLAY:
        {
            c_btm_a2dp_cmd(BT_A2DP_START);
            break;
        }
        case PB_PBC_STT_FF:
        case PB_PBC_STT_FR:
        case PB_PBC_STT_SF:
        case PB_PBC_STT_SR:
        case PB_PBC_STT_STEP:
        case PB_PBC_STT_FSPLAY:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ePBCStt:%d, set a2dp START\n", ePBCStt));
            c_btm_a2dp_cmd(BT_A2DP_START);
            break;
        }
        default:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Default case, ePBCStt:%d\n", ePBCStt));
            //c_btm_a2dp_cmd(BT_A2DP_START);
            break;
        }
    }

    return BT_APPR_OK;
}
#endif

/**-----------------------------------------------------------------------------------------
  * Name          - bt_app_audio_input_a2dp_connect_disconnect_proc
  *
  * Description  -
  *
  * Inputs         -
  *----------------------------------------------------------------------------------------*/
static INT32 _bt_app_audio_input_a2dp_connect_disconnect_proc(BT_APP_MSG_T *pt_bt_msg)
{
    INT32   i4_ret = BT_APPR_OK;
    UINT8   u1_bt_mode = 0;
    BT_TARGET_DEV_INFO t_device = {0,0,{0},{0}};

    // get bluetooth mode setting
    a_cfg_get_bluetooth_mode_status(&u1_bt_mode);

    if (pt_bt_msg->ui4_msg_id == TRUE)
    {
        // connect a2dp
        if (pt_bt_msg->pv_data != NULL)
        {
            // connect to specific addr
            BT_APP_LOG_DEFAULT(("<BT_APP> X2 request input a2dp connect, bt_addr:%s\n", pt_bt_msg->pv_data));

            c_strncpy(t_device.bdAddr, pt_bt_msg->pv_data, MAX_BDADDR_LEN - 1);
        }
        else
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> X2 request last input a2dp connect\n"));

            // connect to last paired src device
            i4_ret = bt_app_get_latest_paired_src_device(&t_device);
            if(i4_ret != BT_APPR_OK)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> no paired device\n"));
                return BT_APPR_OK;
            }
        }

        if (!bt_app_input_a2dp_connected() && (APP_CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode))
        {
            // 1. turn on bluetooth RF
            if(!a_bt_is_bluetooth_enabled())
            {
                a_bt_enable_disable(TRUE);
            }

            // set to RX mode
            if (a_bt_bluetooth_mode_get() != u1_bt_mode)
            {
                a_bt_bluetooth_mode_set(u1_bt_mode);
            }

            //i4_ret = c_btm_btstart("CONNECTING", 15);
            if (i4_ret != BT_APPR_OK)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : CONNECTING fail %d\n", i4_ret));
                return BT_APPR_FAIL;
            }

            //indicate input a2dp connection is triggered by platform itself
            bt_app_set_flag_input_a2dp_initiator(TRUE);

            bt_app_connect(t_device.bdAddr);
        }
        else
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: %s : Input a2dp is already connected or Not BT Receiver setting\n", __FUNCTION__));
            return BT_APPR_FAIL;
        }

    }
    else
    {
        //disconnect a2dp
        if (bt_app_input_a2dp_connected())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> X2 request input a2dp disconnect\n"));

            //c_btm_stop(FALSE,FALSE);
        }
        else
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: X2 request input a2dp disconnect, but no input a2dp connected\n"));
        }
    }

    return i4_ret;
}


/**-----------------------------------------------------------------------------------------
  * Name          - _bt_app_on_off_proc
  *
  * Description  -
  *
  * Inputs         -
  *----------------------------------------------------------------------------------------*/
static INT32 _bt_app_on_off_proc(VOID)
{
    UINT8 u1_bt_switch_status = 0;
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

	i4_ret = a_cfg_get_bluetooth_switch_status(&u1_bt_switch_status);
	BT_APP_CHK_FAIL(i4_ret, i4_ret);

	if (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_switch_status)
	{
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, switch ON.\n",__FUNCTION__));

        if (a_bt_check_bt_device() && a_bt_app_has_init())
        {
            if (!a_bt_is_bluetooth_enabled())
            {
                i4_ret = a_bt_enable_disable(TRUE);
                BT_APP_CHK_FAIL(i4_ret, i4_ret);
            }

            BT_APP_CHK_FAIL(i4_ret,i4_ret);
            bt_app_on_off_hid_reconnect();
            i4_ret = bt_app_connect_with_sink_dev(TRUE, NULL);
            if (0 != i4_ret)
            {
                i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(TRUE, TRUE);
            }
            //BT_APP_CHK_FAIL(i4_ret,i4_ret);
            //bt_app_on_off_hid_reconnect();
        }

	}
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, switch OFF.\n",__FUNCTION__));
        // only for exit bluetooth function, no need stop btm
        i4_ret = bt_app_stop_bluetooth();
        BT_APP_CHK_FAIL(i4_ret, i4_ret);

        /* disconnect output a2dp */
        if (bt_app_output_a2dp_connected())
        {
            BT_APP_LOG_INFO(("<BT_APP> Start to disconnect output a2dp connection\n"));
            i4_ret = bt_app_disconnect_with_sink_dev();
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }

        /* disconnect HID */
        if(bt_app_hid_connected())
        {
            BT_APP_LOG_INFO(("<BT_APP> Start to disconnect HID connection\n"));
            i4_ret = bt_app_hid_disconnect_all();
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }

        i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(FALSE, FALSE);
        BT_APP_CHK_FAIL(i4_ret, i4_ret);

        if (a_bt_is_bluetooth_enabled())
        {
            i4_ret = a_bt_enable_disable(FALSE);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }

    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

/**-----------------------------------------------------------------------------------------
  * Name          - _bt_app_on_off_proc
  *
  * Description  -
  *
  * Inputs         -
  *----------------------------------------------------------------------------------------*/
static INT32 _bt_app_resume_on_off_proc(VOID)
{
    UINT8 u1_bt_switch_status = 0;
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

	i4_ret = a_cfg_get_bluetooth_switch_status(&u1_bt_switch_status);
	BT_APP_CHK_FAIL(i4_ret, i4_ret);

	if (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_switch_status)
	{
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, switch on.\n",__FUNCTION__));
#if 0
        // only for exit bluetooth function, no need stop btm
        i4_ret = bt_app_stop_bluetooth();
        BT_APP_CHK_FAIL(i4_ret, i4_ret);

        /* disconnect output a2dp */
        if (bt_app_output_a2dp_connected())
        {
            BT_APP_LOG_INFO(("<BT_APP> Start to disconnect output a2dp connection\n"));
            i4_ret = bt_app_disconnect_with_sink_dev();
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }

        /* disconnect HID */
        if(bt_app_hid_connected())
        {
            BT_APP_LOG_INFO(("<BT_APP> Start to disconnect HID connection\n"));
            i4_ret = bt_app_hid_disconnect_all();
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan(FALSE, FALSE);
        BT_APP_CHK_FAIL(i4_ret, i4_ret);

        if (a_bt_is_bluetooth_enabled())
        {
            i4_ret = a_bt_enable_disable(FALSE);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }
#endif
        if (a_bt_check_bt_device() && a_bt_app_has_init())
        {
            if (!a_bt_is_bluetooth_enabled())
            {
                i4_ret = a_bt_enable_disable(TRUE);
                BT_APP_CHK_FAIL(i4_ret, i4_ret);
            }

            i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(TRUE, TRUE);
            BT_APP_CHK_FAIL(i4_ret,i4_ret);

            i4_ret = bt_app_connect_with_sink_dev(TRUE, NULL);
            BT_APP_CHK_FAIL(i4_ret,i4_ret);
        }
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, switch OFF.\n",__FUNCTION__));
#if 0
        if (a_bt_check_bt_device() && a_bt_app_has_init())
        {
            if (!a_bt_is_bluetooth_enabled())
            {
                i4_ret = a_bt_enable_disable(TRUE);
                BT_APP_CHK_FAIL(i4_ret, i4_ret);
            }

        }

        if (a_bt_is_bluetooth_enabled())
        {
            i4_ret = a_bt_enable_disable(FALSE);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }
#endif
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

VOID bt_app_a2dp_event_proc2(BT_A2DP_EVENT_PARAM *fg_bt_a2dp_struct_data)
{
    VOID*        pv_nfy_param = NULL;
    BT_NFY_ID_T   e_nfy_id = BT_NFY_ID_UNKNOWN;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    BT_APP_LOG_DEFAULT(("<BT_APP> HID event: %d\n", fg_bt_a2dp_struct_data->event));

    switch(fg_bt_a2dp_struct_data->event)
    {

        case BT_A2DP_EVENT_CONNECTED:   // The GAP event from BTM: A2DP is established
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_EVENT_CONNECTED\n"));

            //_bt_app_btm_nfy_a2dp_connected_proc();

            e_nfy_id = BT_NFY_ID_CONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }

        case BT_A2DP_EVENT_DISCONNECTED:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_EVENT_DISCONNECTED\n"));
            //_bt_app_btm_nfy_disconnected_proc();

            e_nfy_id = BT_NFY_ID_DISCONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }

        case BT_A2DP_EVENT_CONNECT_TIMEOUT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_EVENT_DISCONNECTED\n"));

            //_bt_app_btm_nfy_connect_timeout_proc();

            e_nfy_id = BT_NFY_ID_CONNECT_FAIL;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }

        case BT_A2DP_EVENT_STREAM_SUSPEND:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_EVENT_STREAM_SUSPEND\n"));
            break;
        }

        case BT_A2DP_EVENT_STREAM_START:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_EVENT_STREAM_START\n"));
            break;
        }

        case BT_A2DP_EVENT_CONNECT_COMING:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_EVENT_CONNECT_COMING\n"));
            //_bt_app_btm_nfy_connecting_start_proc();
            break;
        }

        case BT_A2DP_EVENT_PLAYER_EVENT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_A2DP_EVENT_PLAYER_EVENT\n"));
            break;
        }

        default:
            break;
    }

}


#define BTMW_RPC_A2DP_CASE_RETURN_STR(const) case const: return #const;

static CHAR* btmw_rpc_test_a2dp_sink_app_event(BT_A2DP_EVENT event)
{
    switch((int)event)
    {
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_CONNECTED)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_DISCONNECTED)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_CONNECT_TIMEOUT)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_STREAM_SUSPEND)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_STREAM_START)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_CONNECT_COMING)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_PLAYER_EVENT)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_ROLE_CHANGED)
        default: return "UNKNOWN_EVENT";
   }
}
static CHAR* btmw_rpc_test_a2dp_sink_player_event_str(BT_A2DP_PLAYER_EVENT player_event)
{
    switch((int)player_event)
    {
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_STOP)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_STOP_FAIL)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_START)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_START_FAIL)
        default: return "UNKNOWN_EVENT";
   }
}

static CHAR* btmw_rpc_test_a2dp_get_codec_str(UINT8 codec_tpye)
{
     switch(codec_tpye)
     {
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_SBC)
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_MP3)
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_AAC)
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_LDAC)
         default: return "UNKNOWN_CODEC_TYPE";
    }
}

CHAR g_rpc_a2dp_addr_test[18];
static BT_A2DP_ROLE g_rpc_a2dp_local_role = BT_A2DP_ROLE_SRC;
static BOOL g_connect_flag = FALSE;
static BOOL g_panasonic_spp_connect = FALSE;

BT_A2DP_STREAM_STATE g_rpc_a2dp_stream_state = BT_A2DP_STREAM_STATE_SUSPEND;


INT32 bt_app_get_cur_connect_status(CHAR *addr, BT_A2DP_ROLE *local_role, BOOL *status)
{
    if (addr == NULL)
    {
        return -1;
    }
    strcpy(addr,g_rpc_a2dp_addr_test);
    *local_role = g_rpc_a2dp_local_role;
    *status = g_connect_flag;


    BT_APP_LOG_DEFAULT(("<tanss> Enter %s ,%s %d\n",__FUNCTION__,__FILE__,__LINE__));
    BT_APP_LOG_DEFAULT(("<tanss> addr: %s ,local_role = %d ,status = %d\n",addr,*local_role,*status));

    return 0;
}

INT32 a_app_set_spp_connect_status(BOOL status)
{
    g_panasonic_spp_connect = status;
    BT_APP_LOG_DEFAULT(("<tanss>g_panasonic_spp_connect = %d Enter %s ,%s %d\n",g_panasonic_spp_connect,
                        __FUNCTION__,__FILE__,__LINE__));
    return 0;
}

INT32 a_app_get_spp_connect_status(BOOL *status)
{
    if (status == NULL)
    {
        return -1;
    }

    *status = g_panasonic_spp_connect;
    BT_APP_LOG_DEFAULT(("<tanss>*status = %d Enter %s ,%s %d\n",*status,
                        __FUNCTION__,__FILE__,__LINE__));
    return 0;
}

INT32 a_app_spp_send_vol_up(VOID)
{
    if (g_panasonic_spp_connect == FALSE)
    {
        return -1;
    }
    //app_spp_send_vol_up();
    return 0;
}

INT32 a_app_spp_send_vol_down(VOID)
{
    if (g_panasonic_spp_connect == FALSE)
    {
        return -1;
    }
    //app_spp_send_vol_down();
    return 0;
}


INT32 a_spp_send_mute(VOID)
{
    if (g_panasonic_spp_connect == FALSE)
    {
        return -1;
    }
    //app_spp_send_mute();
    return 0;
}

/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_hid_event_cbk
  *
  * Description  - MW callback this function to notify APP of HID event
  *
  * Inputs        -
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
VOID bt_app_a2dp_event_proc(BT_A2DP_EVENT_PARAM *param)
{
    UINT8 codec_type = 0;
    VOID*        pv_nfy_param = NULL;
    BT_NFY_ID_T   e_nfy_id = BT_NFY_ID_UNKNOWN;

    if (NULL == param)
    {
        BT_APP_LOG_DEFAULT(("param is NULL\n"));
        return;
    }
    BT_APP_LOG_DEFAULT(("<tanss> Enter %s ,%s\n",__FUNCTION__,__FILE__));

    BT_APP_LOG_DEFAULT(("tanss addr=%s, event=%d, %s\n", param->addr, param->event,
        btmw_rpc_test_a2dp_sink_app_event(param->event)));
    switch (param->event)
    {
        case BT_A2DP_EVENT_CONNECTED:
            //a_mtkapi_a2dp_sink_start_player();
            BT_APP_LOG_DEFAULT(("A2DP connected(%s)\n", param->addr));

            strcpy(g_rpc_a2dp_addr_test, param->addr);
            g_rpc_a2dp_local_role = param->data.connected_data.local_role;
            g_connect_flag = TRUE;
            g_panasonic_spp_connect = FALSE;

            codec_type = param->data.connected_data.config.codec_type;
            BT_APP_LOG_DEFAULT(("current codec is:%s(%d)\n", \
                btmw_rpc_test_a2dp_get_codec_str(codec_type), \
                codec_type));
            bt_app_set_flag_output_a2dp_connected(TRUE);

            e_nfy_id = BT_NFY_ID_CONNECT_SUCCESS;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            //spp_connect
            if (BT_A2DP_ROLE_SRC == param->data.connected_data.local_role)
            {
                //audio mute
                a_mtkapi_a2dp_src_mute_uploader(TRUE);
                a_mtkapi_spp_connect(param->addr,"00001101-0000-8000-00805F9B34FB");
            }
            switch (codec_type)
            {
                case BT_A2DP_CODEC_TYPE_SBC: //A2D_MEDIA_CT_SBC
                {
                    BT_A2DP_SBC_CONF *local_sbc = &param->data.connected_data.config.codec_conf.sbc_conf;
                    BT_APP_LOG_DEFAULT(("min_bitpool:%d\n", local_sbc->min_bitpool));
                    BT_APP_LOG_DEFAULT(("max_bitpool:%d\n", local_sbc->max_bitpool));


                    break;
                }
                case BT_A2DP_CODEC_TYPE_AAC:
                {
                    BT_A2DP_AAC_CONF *local_aac = &param->data.connected_data.config.codec_conf.aac_conf;
                    BT_APP_LOG_DEFAULT(("object_type:%d\n", local_aac->object_type));
                    BT_APP_LOG_DEFAULT(("sample_rate:%ld\n", local_aac->samp_freq));
                    BT_APP_LOG_DEFAULT(("channels:%d\n", local_aac->channels));
                    BT_APP_LOG_DEFAULT(("VBR supported? (%s)\n", local_aac->vbr ? "TRUE" : "FALSE"));
                    BT_APP_LOG_DEFAULT(("bit_rate:%d\n", local_aac->bitrate));

                    break;
                }
                default:
                    BT_APP_LOG_DEFAULT(("invalid codec type:%d\n", codec_type));
                    break;
            }
            break;
        case BT_A2DP_EVENT_DISCONNECTED:

            if (BT_A2DP_ROLE_SINK == g_rpc_a2dp_local_role)
            {
                a_mtkapi_a2dp_sink_stop_player();
            }
            else if (BT_A2DP_ROLE_SRC == g_rpc_a2dp_local_role)
            {
        		tv_mute = FALSE;
    			bt_mute = TRUE;
                _bt_app_set_mute(tv_mute,bt_mute);
                a_mtkapi_a2dp_src_mute_uploader(FALSE); //unmute
            }
            BT_APP_LOG_DEFAULT(("A2DP disconnected(%s)\n", param->addr));
            g_rpc_a2dp_addr_test[0] = 0;

            g_connect_flag = FALSE;

            e_nfy_id = BT_NFY_ID_DISCONNECT_SUCCESS;
            bt_app_set_flag_output_a2dp_connected(FALSE);
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        case BT_A2DP_EVENT_CONNECT_TIMEOUT:
            BT_APP_LOG_DEFAULT(("A2DP Connect Timeout(%s)\n", param->addr));
            g_rpc_a2dp_addr_test[0] = 0;

            bt_app_set_flag_output_a2dp_connected(FALSE);
            g_connect_flag = FALSE;
            e_nfy_id = BT_NFY_ID_CONNECT_FAIL;
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        case BT_A2DP_EVENT_STREAM_SUSPEND:
            g_rpc_a2dp_stream_state = BT_A2DP_STREAM_STATE_SUSPEND;
            break;
        case BT_A2DP_EVENT_STREAM_START:
            g_rpc_a2dp_stream_state = BT_A2DP_STREAM_STATE_PLAYING;
            if (BT_A2DP_ROLE_SINK == g_rpc_a2dp_local_role)
            {
                BT_APP_LOG_DEFAULT(("tanss to start player(open alsa)\n"));
                a_mtkapi_a2dp_sink_start_player();
            }
            else if (BT_A2DP_ROLE_SRC == g_rpc_a2dp_local_role)
            {
                tv_mute = TRUE;
                bt_mute = FALSE;
                _bt_app_set_mute(tv_mute,bt_mute);
            }
            break;
        case BT_A2DP_EVENT_CONNECT_COMING:
            break;
        case BT_A2DP_EVENT_PLAYER_EVENT:
            BT_APP_LOG_DEFAULT(("player event %s(%d)\n",
                btmw_rpc_test_a2dp_sink_player_event_str(param->data.player_event),
                param->data.player_event));
            break;
        case BT_A2DP_EVENT_ROLE_CHANGED:
            break;
        default:
            break;
    }
    return;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_msg_proc
  *
  * Description  - Process Bluetooth msg
  *                     This API is runned in PLAYBACK thread
  *
  * Inputs        - pt_appmsg: Bluetooth msg
  *---------------------------------------------------------------------------*/
static VOID bt_app_msg_proc(VOID* pt_btmsg, SIZE_T z_data_len)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T *pt_bt_msg = NULL;
    VOID*        pv_nfy_param = NULL;
    BT_NFY_ID_T   e_nfy_id = BT_NFY_ID_UNKNOWN;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    if(NULL == pt_btmsg)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return;
    }

    pt_bt_msg = (BT_APP_MSG_T*) pt_btmsg;
    switch (pt_bt_msg->msg_type)
    {
        case BT_APP_MSG_BTM_NFY_GAP_EVENT:        // The event from BTM: GAP event
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                BT_APP_LOG_ERR(("<BT_APP> tanss: %s, pt_bt_msg->pv_data != NULL data\n", __FUNCTION__));
                _bt_app_btm_nfy_gap_event_proc((tBTMW_GAP_STATE*)(pt_bt_msg->pv_data));
            }
            else
            {
                 BT_APP_LOG_ERR(("<BT_APP> ERR: %s, NULL data\n", __FUNCTION__));
            }
            break;
        }
        case BT_APP_MSG_BTM_NFY_A2DP_SNK_DEV:    // The event from BTM: Find A2DP Sink device
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_BTM_NFY_A2DP_SNK_DEV\n"));
            if(pt_bt_msg->pv_data != NULL)
            {
                BT_APP_REMOTE_DEV_T *r_bt_device_info = (BT_APP_REMOTE_DEV_T*)pt_bt_msg->pv_data;
                BT_APP_DEVICE_INFO_T   bt_device_info;
                bt_app_insert_a2dp_snk_dev((BT_APP_REMOTE_DEV_T*)(pt_bt_msg->pv_data));


                e_nfy_id = BT_NFY_ID_A2DP_SNK_DEVICE;
                memcpy(&bt_device_info,&r_bt_device_info->r_bt_device_info,sizeof(BT_APP_DEVICE_INFO_T));
                bt_msg_brdcast(e_nfy_id, (VOID*)&bt_device_info);
                c_mem_free(pt_bt_msg->pv_data);

                pt_bt_msg->pv_data = NULL;
            }
            break;
        }
        case BT_APP_MSG_BTM_NFY_TRACK_CHGD:       // The event form BTM: Track is changed
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_BTM_NFY_TRACK_CHGD\n"));

            _bt_app_btm_nfy_track_chgd_proc(pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_BTM_NFY_PLAY_STATE_CHGD:  // The event from BTM: playback state (play/pause/stop/...) is changed
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_BTM_NFY_PLAY_STATE_CHGD\n"));

            //_bt_app_btm_nfy_play_state_chgd_proc(pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_BTM_NFY_META_DATA_OK:     // The event from BTM: meta data has been ready in BTM
        {
            _bt_app_btm_nfy_meta_data_ok_proc();
            break;
        }
        case BT_APP_MSG_BTM_NFY_PLAY_STATUS_OK:   // The event from BTM: play status has been ready in BTM
        {
            //_bt_app_btm_nfy_play_status_ok_proc();
            break;
        }
        case BT_APP_MSG_BTM_NFY_VOLUME_CHG:      // The event from BTM: volume change
        {
            //_bt_app_btm_nfy_volume_change_proc(pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_BTM_NFY_SPP_EVENT:       // The event from BTM: SPP event
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                //bt_spp_event_nfy_proc(pt_bt_msg->ui4_msg_id, pt_bt_msg->pv_data);
                c_mem_free(pt_bt_msg->pv_data);
                pt_bt_msg->pv_data = NULL;
            }
            break;
        }
        case BT_APP_MSG_IFCON_CMD_BT_START_KEY:     // The command from IFCon: COM_DVD_BT_start
        {
            //_bt_app_ifcon_cmd_bt_start_key_proc(pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_IFCON_CMD_NFC_START:        // The command from IFCon: COM_DVD_NFC_start
        {
            //_bt_app_ifcon_cmd_nfc_start_proc(pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_EVENT_NFC_TOUCH_TIME_OUT: // The event: no device request to connect after NFC touch
        {
            _bt_app_event_nfc_touch_time_out_proc();
            break;
        }
        case BT_APP_MSG_REQ_ENABLE_BT:      // Request: enable bluetooth
        {
            a_bt_enable_disable(TRUE);
            break;
        }
        case BT_APP_MSG_REQ_DISABLE_BT:     // Request: disable bluetooth
        {
            a_bt_enable_disable(FALSE);
            break;
        }
        case BT_APP_MSG_PRE_SUSPEND_EXIT:     // Request: disable bluetooth
        {
            _bt_app_resume_on_off_proc();
            break;
        }
        case BT_APP_MSG_REQ_SET_LOCAL_NAME:    // Request: set local bluetooth device name
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                a_bt_app_set_local_device_name((CHAR *)(pt_bt_msg->pv_data));
                c_mem_free(pt_bt_msg->pv_data);
                pt_bt_msg->pv_data = NULL;
            }
            break;
        }
    	case BT_APP_MSG_REQ_START_BT_INPUT:    // Request: start bluetooth
        {
            bt_app_start_bluetooth(pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_REQ_STOP_BT_INPUT:     // Request: stop bluetooth
        {
            i4_ret = bt_app_stop_bluetooth();
            BT_APP_LOG_ON_FAIL(i4_ret);
            break;
        }
        case BT_APP_MSG_REQ_SPP_CONNECT:       // Request: establish SPP connection
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                //bt_spp_connect_with_uuid_proc((CHAR *)(pt_bt_msg->pv_data));
                //c_mem_free(pt_bt_msg->pv_data);
                //pt_bt_msg->pv_data = NULL;
            }
            break;
        }
        case BT_APP_MSG_REQ_SPP_DISCONNECT:    // Request: disconnect SPP connection
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                //bt_spp_disconnect_with_uuid_proc((CHAR *)(pt_bt_msg->pv_data));
                //c_mem_free(pt_bt_msg->pv_data);
                //pt_bt_msg->pv_data = NULL;
            }
            break;
        }
        case BT_APP_MSG_REQ_GET_BITRATE:       // Request: get bitrate from BTM and update UI
        {
            break;
        }
        case BT_APP_MSG_REQ_GET_PLAYSTATUS:    // Request: get play status from BTM
        {
            bt_app_send_req_to_get_playstatus();
            break;
        }
        case BT_APP_MSG_REQ_GET_RSSI_LEVEL:    // Request: get RSSI level of connected SRC device and update UI
        {
            break;
        }
        case BT_APP_MSG_REQ_HIDE_PLAY_WINDOW:  // Request: hide playback window
        {
            break;
        }
        case BT_APP_MSG_NFY_FUNCTION_KEY_STT:  // The event: the status of [FUNCTION] key is changed
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_FUNCTION_KEY_STT\n"));
            _bt_app_function_key_stt_change_proc((UINT8)pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_EVENT_NO_AVRCP:        // The event:  cannot establish AVRCP
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_EVENT_NO_AVRCP\n"));

            // Even if AVRCP cannot be established, this notify is needed.
            // If no this notify, X2 will not establish SPP.
            if (bt_app_input_a2dp_connected())
            {
            bt_app_notify_input_a2dp_avrcp_connect_to_x2();
            }
            else
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_EVENT_NO_AVRCP: A2DP is disconnected\n"));
            }
            break;
        }
        case BT_APP_MSG_NFY_AMP_VOLUME_CHGD:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_AMP_VOLUME_CHGD\n"));
            bt_app_amp_volume_changed_proc();
            break;
        }
        case BT_APP_MSG_BTM_NFY_AVRCP_KEY_CMD:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_BTM_NFY_AVRCP_KEY_CMD\n"));
            _bt_app_src_mode_avrcp_key_cmd_proc((UINT8)pt_bt_msg->ui4_msg_id, (UINT8)pt_bt_msg->ui4_data1);
            break;
        }
        case BT_APP_MSG_BTM_NFY_UPLOAD_INFO:
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_BTM_NFY_UPLOAD_INFO\n"));
                _bt_app_src_mode_upload_info_proc((UINT8)pt_bt_msg->ui4_msg_id, pt_bt_msg->pv_data);
            }
            break;
        }
        case BT_APP_MSG_REQ_START_SINK_DEVICE_LIST:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_REQ_START_SINK_DEVICE_LIST\n"));
            bt_app_start_sink_device_list((UINT8)pt_bt_msg->ui4_data1);
            break;
        }
        case BT_APP_MSG_REQ_CLOSE_SINK_DEVICE_LIST:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_REQ_CLOSE_SINK_DEVICE_LIST\n"));
            bt_app_close_sink_device_list();
            break;
        }
        case BT_APP_MSG_REQ_INPUT_A2DP_CONNECT_DISCONNECT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_REQ_INPUT_A2DP_CONNECT_DISCONNECT\n"));
            _bt_app_audio_input_a2dp_connect_disconnect_proc(pt_bt_msg);
            break;
        }
        case BT_APP_MSG_NFY_SINK_SCAN_START:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_SINK_SCAN_START\n"));
            _bt_app_sink_device_scan_start_proc();
            break;
        }
        case BT_APP_MSG_NFY_SINK_SCAN_FINISH:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_SINK_SCAN_FINISH\n"));
            _bt_app_sink_device_scan_finish_proc();
            e_nfy_id = BT_NFY_ID_SCAN_FINISH;

            BT_APP_LOG_DEFAULT(("<BT_APP> bt_msg_brdcast\n"));
            bt_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
            break;
        }
        case BT_APP_MSG_GET_PAIRING_KEY:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_GET_PAIRING_KEY\n"));
            e_nfy_id = BT_NFY_ID_PAIRING_KEY;

            BT_APP_LOG_DEFAULT(("<BT_APP> bt_msg_brdcast\n"));
            bt_msg_brdcast(e_nfy_id, (VOID*)pt_bt_msg->pv_data);
            pt_bt_msg->pv_data=NULL;
            break;
        }
        case BT_APP_MSG_SINK_LIST_KEY_EVENT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_SINK_LIST_KEY_EVENT\n"));
            _bt_app_sink_device_list_key_proc(pt_bt_msg->ui4_msg_id, pt_bt_msg->ui4_data1);
            break;
        }
        case BT_APP_MSG_NFY_BT_MODE_CHG:      // notify the event: bluetooth mode is changed in setup
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_BT_MODE_CHG\n"));
            _bt_app_bt_mode_setting_chg_proc((UINT8)pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_NFY_BT_DONGLE_ATTACH:      // notify the event: bluetooth dongle is attached
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_BT_DONGLE_ATTACH\n"));
            if(pt_bt_msg->ui4_msg_id == BT_UNPLUG)
            {
                a_bt_check_bt_device();
            }
            else
            {
                _bt_app_bt_dongle_attach_nfy_proc();
            }
            break;
        }
        case BT_APP_MSG_REQ_BT_TX_DEV_LIST:      // IFCON request to get the sink device information
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_REQ_BT_TX_DEV_LIST\n"));
            _bt_app_bt_tx_device_list_req_proc((UINT8)pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_IFCON_DATA_SYNC_BT_CMD:      // IFCON send bluetooth command
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_IFCON_DATA_SYNC_BT_CMD\n"));
            //_bt_app_data_sync_ifcon_bt_cmd_proc(pt_bt_msg->ui4_msg_id, pt_bt_msg->ui4_data1);
            break;
        }
        case BT_APP_MSG_NFY_SRC_MODE_PBC_STT:      // receive pbc status change notify
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_SRC_MODE_PBC_STT\n"));
            //_bt_app_src_mode_pbc_stt_proc(pt_bt_msg->ui4_msg_id);
            break;
        }
        case BT_APP_MSG_NFY_HID_EVENT:
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_HID_EVENT\n"));
                bt_app_hid_event_proc((BT_HIDH_CBK_STRUCT *)(pt_bt_msg->pv_data));
            }
            break;
        }
        case BT_APP_MSG_NFY_A2DP_EVENT:
        {
            if(pt_bt_msg->pv_data != NULL)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_NFY_A2DP_EVENT\n"));
                bt_app_a2dp_event_proc((BT_A2DP_EVENT_PARAM *)(pt_bt_msg->pv_data));
            }
            break;
        }
        case BT_APP_MSG_INIT:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_INIT\n"));
            //i4_ret = _bt_app_init_proc();
            //BT_APP_LOG_ON_FAIL(i4_ret);
            break;
        }
        case BT_APP_MSG_ON_OFF_PROC:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> BT_APP_MSG_ON_OFF_PROC\n"));
            i4_ret = _bt_app_on_off_proc();
            BT_APP_LOG_ON_FAIL(i4_ret);
            break;
        }
        default:
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: No such BT msg type\n"));
            break;
        }
    }

    if(pt_bt_msg->pv_data != NULL)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> c_mem_free(pt_bt_msg->pv_data)\n"));
        c_mem_free(pt_bt_msg->pv_data);
        BT_APP_LOG_DEFAULT(("<BT_APP> c_mem_free(pt_bt_msg->pv_data) OK!\n"));
        pt_bt_msg->pv_data = NULL;
    }

    return;
}
#if 0
static INT32 _bluetooth_notify_msg_proc(const VOID *pv_msg)
{
    BT_APP_MSG_T *pt_msg = (BT_APP_MSG_T*)pv_msg;

    if(NULL == pv_msg)
    {
        BT_APP_LOG_ERR(("<BT_APP> %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }

    bt_app_sema_lock();

    switch( pt_msg->msg_type)
    {

        default:
            break;

    }

    if(pt_msg->pv_data != NULL)
    {
        c_mem_free(pt_msg->pv_data);
        pt_msg->pv_data = NULL;
    }

    bt_app_sema_unlock();

    return 0;
}
#endif
static void _bluetooth_msg_proc_thread(VOID * pvArg)
{
    BT_APP_MSG_T t_msg;
    SIZE_T z_size = sizeof(BT_APP_MSG_T);
    UINT16 ui2_index = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> %s START.\n", __FUNCTION__));

    while(1)
    {
        //c_thread_delay(10);
        if(OSR_OK == c_msg_q_receive(&ui2_index,
                                    (VOID *)&t_msg,
                                    &z_size,
                                    &h_s_bluetooth_queue,
                                    1,
                                    X_MSGQ_OPTION_WAIT))
        {
            bt_app_msg_proc(&t_msg,sizeof(BT_APP_MSG_T));
        }
        else
        {
            c_thread_delay(100);
            continue;
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> %s END.\n", __FUNCTION__));
    x_thread_exit();

}

/**-----------------------------------------------------------------------------
  * Name          - bt_create_bluetooth_thread
  *
  * Description  - create and start bluetooth msg proc thread
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_create_bluetooth_thread(VOID)
{
    INT32 i4_ret = OSR_OK;

    if(NULL_HANDLE == h_bluetooth_thread)
    {
        // Create a queue to receive bluetooth msg
        if(NULL_HANDLE == h_s_bluetooth_queue)
        {
            if (c_msg_q_create(&h_s_bluetooth_queue,
                               "bluetooth_q",
                               sizeof(BT_APP_MSG_T),
                               64) != OSR_OK)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: create bluetooth queue fail\n"));
                return BTR_FAIL;
            }
        }

        // Create bluetooth thread to handle bluetooth msg
        if (x_thread_create(&h_bluetooth_thread,
                           BLUETOOTH_THREAD_NAME,
                           BLUETOOTH_STACK_SIZE,
                           BLUETOOTH_THREAD_PRIORITY,
                           _bluetooth_msg_proc_thread,
                           0,
                           NULL) != OSR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: create bluetooth thread fail\n"));
            return BTR_FAIL;
        }
    }

    return i4_ret;
}

/**-----------------------------------------------------------------------------
  * Name          - bt_app_send_msg_to_bt_thread
  *
  * Description  - send msg to bluetooth thread
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bt_app_send_msg_to_bt_thread(BT_APP_MSG_T *pt_bt_msg)
{
    INT32 i4_ret = PBR_OK;

    if (NULL_HANDLE == h_s_bluetooth_queue)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: bt msg queue hasn't created\n"));
        return PBR_FAIL;
    }

    i4_ret = c_msg_q_send(h_s_bluetooth_queue,
                          (VOID*)pt_bt_msg,
                          sizeof(BT_APP_MSG_T),
                          200);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send msg to bt thread fail, %d\n", i4_ret));
    }

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_send_bt_msg_to_playback
  *
  * Description  - send Bluetooth msg to playback
  *
  * Inputs         - pt_bt_msg: Bluetooth msg
  *---------------------------------------------------------------------------*/
INT32 bt_app_send_bt_msg_to_playback(BT_APP_MSG_T *pt_btmsg)
{
    INT32    i4_ret = BT_APPR_OK;
    //BT_APP_MSG_T t_bt_msg = {0};

    //BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    if(NULL == pt_btmsg)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_INV_ARG;
    }
    bt_app_send_msg_to_bt_thread(pt_btmsg);
    #if 0
    c_memcpy(&t_bt_msg, pt_btmsg, sizeof(BT_APP_MSG_T));

    i4_ret = a_agent_async_invoke((agent_async_func)bt_app_msg_proc,
                          (VOID*)&t_bt_msg,
                          sizeof(BT_APP_MSG_T)
                          );
    #endif
    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_function_key_stt_nfy
  *
  * Description  - call this API to notify the event: the status of [FUNCTION] key is changed
  *                     When [FUNCTION] key is disable, turn off Bluetooth and NFC.
  *
  * Inputs        - bEnable: TRUE: [FUNCTION] key is enable, FALSE: [FUNCTION] key is disable
  *---------------------------------------------------------------------------*/
INT32 bt_app_function_key_stt_nfy(BOOL bEnable)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_app_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Function key status: %d \n", bEnable));

    t_bt_app_msg.msg_type = BT_APP_MSG_NFY_FUNCTION_KEY_STT;
    t_bt_app_msg.ui4_msg_id = bEnable;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_app_msg);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send Function key STT fail\n"));
    }

    return i4_ret;
}

VOID bluetooth_progress_timer_bar_cb(HANDLE_T    pt_handle,
                                    VOID*       pv_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    BT_AVRCP_PLAY_STATUS e_playstatus = AVRCP_PLAY_STATUS_MAX;

    e_playstatus = bt_app_get_running_status();

    if (bt_app_playstatus_is_ready()
        && (AVRCP_PLAY_STATUS_STOPPED == e_playstatus || AVRCP_PLAY_STATUS_PAUSED == e_playstatus))
    {
        // if playstatus is stop or pause, don't send request, otherwise, it cause some device cannot enter sleep mode
        // because it continuously receive AVRCP command
        BT_APP_LOG_INFO(("<BT_APP> Playstatus:%d, don't issue GetPlayStatus\n", e_playstatus));
        return;
    }

    t_bt_msg.msg_type = BT_APP_MSG_REQ_GET_PLAYSTATUS;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send play status update msg fail\n"));
    }

    return ;
}

VOID bluetooth_volume_flag_timer_cb(HANDLE_T    pt_handle,
                                    VOID*       pv_tag)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Volume timer time out\n"));
    if(b_received_volume)
    {
        b_received_volume = FALSE;
        b_received_prev = FALSE;
    }
}


INT32 bluetooth_progress_timer_bar_initial(VOID)
{
    INT32 i4_ret = 0;

    //printf("<BT_APP> bluetooth_progress_timer_bar_initial\n");
    if (NULL_HANDLE == h_bluetooth_timer_bar)
    {
        i4_ret = c_timer_create(&h_bluetooth_timer_bar);
        if (OSR_OK != i4_ret)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: create bt timer bar fail, %d\n", i4_ret));
            return BTR_FAIL;
        }
    }

    if (NULL_HANDLE == h_bt_volume_timer)
    {
        i4_ret = c_timer_create(&h_bt_volume_timer);
        if (OSR_OK != i4_ret)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: create volume timer fail, %d\n", i4_ret));
            return BTR_FAIL;
        }
    }

    return PLAYBACKR_OK;
}

INT32 bluetooth_progress_timer_bar_start(VOID)
{

    INT32 i4_ret = 0;

    if (NULL_HANDLE != h_bluetooth_timer_bar)
    {
        i4_ret = c_timer_start(h_bluetooth_timer_bar,
                       1000,
                       X_TIMER_FLAG_REPEAT,
                      bluetooth_progress_timer_bar_cb,
                      (VOID *)NULL);
        if (OSR_OK != i4_ret)
        {
            BT_APP_LOG_API(("<BT_APP> Func:%s.failed, line:%d ,i4_ret: %d\n",__FUNCTION__,__LINE__,i4_ret));
            return BTR_FAIL;
        }
        else
        {
            BT_APP_LOG_API(("<BT_APP> Func:%s.sucessful, line:%d ,i4_ret: %d\n",__FUNCTION__,__LINE__,i4_ret));
        }
    }

    return PLAYBACKR_OK;
}

INT32 bluetooth_progress_timer_bar_stop(VOID)
{

    if (NULL_HANDLE != h_bluetooth_timer_bar)
    {
         BT_APP_LOG_INFO(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));
         c_timer_stop(h_bluetooth_timer_bar);
    }
    return PLAYBACKR_OK;
}

INT32 bluetooth_volume_timer_start(UINT32 ui4_msecond)
{
    INT32 i4_ret = 0;

    if (NULL_HANDLE != h_bt_volume_timer)
    {
        i4_ret = c_timer_start(h_bt_volume_timer,
                               ui4_msecond,//200,
                               X_TIMER_FLAG_ONCE,
                               bluetooth_volume_flag_timer_cb,
                               (VOID *)NULL);
        if (OSR_OK != i4_ret)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: start volume timer fail, %d\n", i4_ret));
            return BTR_FAIL;
        }
    }

    return PLAYBACKR_OK;
}

INT32 bluetooth_volume_timer_stop(VOID)
{
    if (NULL_HANDLE != h_bt_volume_timer)
    {
         BT_APP_LOG_DEFAULT(("<Bluetooth> Enter %s, line: %d\n",__FUNCTION__,__LINE__));
         c_timer_stop(h_bt_volume_timer);
         b_received_volume = FALSE;
         b_received_prev = FALSE;
    }
    return PLAYBACKR_OK;
}

INT32 bluetooth_stop_all_media_engine(VOID)
{
	//INT32 i4_ret;
    //UINT8 ui1_cnt= 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    return 0;
}

#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_display_key_proc
  *
  * Description  - process [DISPLAY] key
  *
  * Inputs        -
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_display_key_proc(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s : detect [DISPLAY] key\n", __FUNCTION__));

    return PBR_OK;
}
#endif

/*! \fn INT32 pb_normal_next_key_proc(
    UINT32 ui4_key)
    \brief this function is to process next key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_normal_next_key_proc(UINT32 ui4_key)
{
    INT32     i4_ret = PBR_OK;
    BT_AVRCP_KEY_STATE action;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    action = BT_AVRCP_KEY_STATE_PRESS;

    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_FWD, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }
    //c_thread_delay(500);
    action = BT_AVRCP_KEY_STATE_RELEASE;
    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_FWD, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }

#endif

    return PBR_OK;
}

/*! \fn INT32 pb_normal_prev_key_proc(
    UINT32 ui4_key)
    \brief this function is to process prev key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_normal_prev_key_proc(UINT32 ui4_key)
{
    INT32     i4_ret = PBR_OK;
    BT_AVRCP_KEY_STATE action;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    action = BT_AVRCP_KEY_STATE_PRESS;
    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_BWD, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }
    //c_thread_delay(500);
    action = BT_AVRCP_KEY_STATE_RELEASE;
    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_BWD, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }

#endif

    return PBR_OK;
}


/*! \fn INT32 pb_normal_stop_key_proc(
    UINT32 ui4_key)
    \brief this function is to process stop key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_normal_stop_key_proc(UINT32 ui4_key)
{
    INT32       i4_ret = PBR_OK;
    BT_AVRCP_KEY_STATE action;
    action = BT_AVRCP_KEY_STATE_PRESS;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_STOP, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }
    //c_thread_delay(200);
    action = BT_AVRCP_KEY_STATE_RELEASE;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));
    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_STOP, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }

#endif

    return i4_ret;
}


/*! \fn INT32 pb_normal_pause_key_proc(
    UINT32 ui4_key)
    \brief this function is to process pause key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_normal_pause_key_proc(
    UINT32 ui4_key)
{
    INT32    i4_ret = PBR_OK;
    BT_AVRCP_KEY_STATE action;
    action = BT_AVRCP_KEY_STATE_PRESS;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PAUSE, action);
    if (PBR_OK != i4_ret)
    {
       BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

       //return PBR_FAIL;
    }
    //c_thread_delay(200);
    action = BT_AVRCP_KEY_STATE_RELEASE;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));
    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PAUSE, action);
    if (PBR_OK != i4_ret)
    {
       BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

       //return PBR_FAIL;
    }

#endif

    return i4_ret;
}


/*! \fn INT32 pb_normal_play_key_proc(
    UINT32 ui4_key)
    \brief this function is to process play key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_normal_play_key_proc(
    UINT32 ui4_key)
{
    INT32    i4_ret = PBR_OK;
    //PB_PBC_STT_INFO_T    t_pbc_info;
    BT_AVRCP_KEY_STATE action;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line: %d\n",__FUNCTION__,__LINE__));

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    if(_b_fr_key_press)
    {
        action = BT_AVRCP_KEY_STATE_RELEASE;
        //call btm interface
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_RWD, action);
        if (PBR_OK != i4_ret)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

            //return PBR_FAIL;
        }
        _b_fr_key_press = FALSE;
        /*for fix BDP00397064: Xperia E issue*/
        c_thread_delay(500);
    }

    if(_b_ff_key_press)
    {
        action = BT_AVRCP_KEY_STATE_RELEASE;
        //call btm interface
        i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_FFWD, action);
        if (PBR_OK != i4_ret)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

            //return PBR_FAIL;
        }
        _b_ff_key_press = FALSE;
        /*for fix BDP00397064: Xperia E issue*/
        c_thread_delay(500);
    }

    action = BT_AVRCP_KEY_STATE_PRESS;
    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PLAY, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }


    //c_thread_delay(200);
    //c_thread_delay(1000);
    INT32 i4_delay = 10;
    BT_APP_LOG_DEFAULT(("<BT_APP> delay %ldms\n", i4_delay));
    c_thread_delay(i4_delay);

    action = BT_AVRCP_KEY_STATE_RELEASE;
    //call btm interface
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PLAY, action);
    if (PBR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s.failed, line: %d\n",__FUNCTION__,__LINE__));

        //return PBR_FAIL;
    }

#endif

    return i4_ret;
}

/*! \fn INT32 pb_bluetooth_sink_mode_normal_option_key_proc(
    UINT32 ui4_key)
    \brief this function is to process option key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_sink_mode_normal_option_key_proc(UINT32 ui4_key)
{
    BT_APP_LOG_API(("<BT_APP> Enter %s\n", __FUNCTION__));

    return PBR_OK;
}

/*! \fn INT32 pb_normal_option_key_proc(
    UINT32 ui4_key)
    \brief this function is to process option key
    \retval INT32 if PBR_OK, this function is called successful;else, failed
*/
INT32 pb_bluetooth_normal_option_key_proc(UINT32 ui4_key)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s: Detect [OPTION] key, _e_bluetooth_state[%d]\n", __FUNCTION__, _e_bluetooth_state));

    if (BLUETOOTH_SINK_DEVICE_LIST_STATE == _e_bluetooth_state)
    {
        i4_ret = pb_bluetooth_src_mode_normal_option_key_proc(ui4_key);
    }
    else
    {
        i4_ret = pb_bluetooth_sink_mode_normal_option_key_proc(ui4_key);
    }

    return i4_ret;
}
#if 0
/**---------------------------------------------------------------------------
  * Name          - _bt_app_disc_tray_is_open
  *
  * Description  - check whether disc tray is open or not.
  *
  * Return:       - TRUE: tray is open. FALSE: tray isn't open
  *---------------------------------------------------------------------------*/
static BOOL _bt_app_disc_tray_is_open(VOID)
{
    INT32    i4_ret = BT_APPR_OK;
    HANDLE_T h_dev;
    DM_DEV_SPEC_T       t_dev_spec;

    t_dev_spec.t_hw_type = DM_HW_TYPE_IDE;
    t_dev_spec.t_dev_type = DM_DEV_SKT_TYPE_OPTI_DRV;
    t_dev_spec.ui4_unit_id = 0; // need to check BD Disc connect to which IDE port

    // check whether disc tray connect
    i4_ret = c_dm_get_device(&t_dev_spec, &h_dev);
    if (BT_APPR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> no disc tray, %d\n", i4_ret));
        return FALSE;
    }

    return FALSE;
}
#endif
#if 0
INT32 pb_bluetooth_connection_key_proc(void)
{
    UINT8 u1_bt_mode = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> %s\n", __FUNCTION__));

    if(!bt_app_is_sink_dev_list_start())
    {
        a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

        if(APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode)
        {
            if(0 != a_bt_app_get_paired_sink_device_num())
            {
                if(bt_app_output_a2dp_connected())
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP> Last paired sink device exist, disconnect\n"));
                    bt_app_set_flag_start_2nd_sink_connect(FALSE);
                    bt_app_disconnect_with_sink_dev();
                }
                else
                {
                    BT_APP_LOG_DEFAULT(("<BT_APP> Last paired sink device exist, connect\n"));
                    if(bt_app_is_audio_output_dev_list_start())
                    {
                        bt_app_connect_with_sink_dev(TRUE, NULL);
                    }
                    else
                    {
                        bt_app_set_flag_start_list_by_bluetooth_key(TRUE);
                        bt_app_connect_with_sink_dev(TRUE, NULL);
                        bt_app_audio_output_dev_list_start();
                    }
                }
            }
            else
            {
                if(!bt_app_is_audio_output_dev_list_start())
                {
                    bt_app_set_flag_start_list_by_bluetooth_key(TRUE);
                    bt_app_audio_output_dev_list_start();
                }
            }
        }
        else if(APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_mode)
        {
            _e_bluetooth_state = BLUETOOTH_SRC_PLAYBACK_STATE;
        }
    }

    return PBR_OK;
}

#endif
/**---------------------------------------------------------------------------
  * Name          - bt_app_osc_play_select_proc
  *
  * Description  - process the event: "PLAY" is selected from option menu
  *---------------------------------------------------------------------------*/
INT32 bt_app_osc_play_select_proc(VOID)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_API(("<BT_APP> API: %s\n", __FUNCTION__));

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    // call btm interface
    ///i4_ret = c_btm_cmd_play(BT_AVRCP_KEY_STATE_PRESS);
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PLAY, BT_AVRCP_KEY_STATE_PRESS);
    BT_APP_LOG_ON_FAIL(i4_ret);

    c_thread_delay(1000);

    //call btm interface
    //i4_ret = c_btm_cmd_play(BT_AVRCP_KEY_STATE_RELEASE);
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_PLAY, BT_AVRCP_KEY_STATE_RELEASE);
    BT_APP_LOG_ON_FAIL(i4_ret);

#endif

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_osc_stop_select_proc
  *
  * Description  - process the event: "STOP" is selected from option menu
  *---------------------------------------------------------------------------*/
INT32 bt_app_osc_stop_select_proc(VOID)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_API(("<BT_APP> API: %s\n", __FUNCTION__));

#ifdef APP_BLUETOOTH_AVRCP_SUPPORT

    //i4_ret = c_btm_cmd_stop(BT_AVRCP_KEY_STATE_PRESS);
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_STOP, BT_AVRCP_KEY_STATE_PRESS);
    BT_APP_LOG_ON_FAIL(i4_ret);

    c_thread_delay(1000);

    //call btm interface
    //i4_ret = c_btm_cmd_stop(BT_AVRCP_KEY_STATE_RELEASE);
    i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_STOP, BT_AVRCP_KEY_STATE_RELEASE);
    BT_APP_LOG_ON_FAIL(i4_ret);

#endif

    return PBR_OK;
}

#if CONFIG_PTS_BLUETOOTH
static BOOL _b_bt_pts_test = FALSE;
VOID bt_app_set_pts_test_flag(BOOL b_pts_test)
{
    _b_bt_pts_test = b_pts_test;

    return ;
}

BOOL bt_app_pts_test(VOID)
{
    return _b_bt_pts_test;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_osc_avrcp_connect_select_proc
  *
  * Description  - It is used for PTS test.
  *---------------------------------------------------------------------------*/
INT32 bt_app_osc_avrcp_connect_select_proc(
    OP_MENU_HANDLE_T  h_op_menu,
    HANDLE_T          h_menu,
    HANDLE_T          h_parent_menu,
    INT32             i4_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_TARGET_DEV_INFO t_device = {0,0,{0},{0}};

    //disable option key
    _e_bluetooth_state = BLUETOOTH_ENABLE_STATE;

    //c_btm_connect_audio_sources(t_device.bdAddr, CONN_TYPE_AVCTP);

    return 0;

}

/**---------------------------------------------------------------------------
  * Name          - bt_app_osc_avctp_connect_select_proc
  *
  * Description  - It is used for PTS test.
  *---------------------------------------------------------------------------*/
INT32 bt_app_osc_avctp_connect_select_proc(
    OP_MENU_HANDLE_T  h_op_menu,
    HANDLE_T          h_menu,
    HANDLE_T          h_parent_menu,
    INT32             i4_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_TARGET_DEV_INFO t_device = {0,0,{0},{0}};

    //c_btm_connect_audio_sources(t_device.bdAddr, CONN_TYPE_AVCTP);

    return 0;
}
#endif

/**---------------------------------------------------------------------------
  * Name          - bt_app_remove_confirm_msgbox_exit_proc
  *
  * Description  - Process the event: remove confirmation message box exit
  *
  * Inputs         - b_remove: remove device or not.
  *                      b_remove_all: remove one device or remove all device
  *---------------------------------------------------------------------------*/
INT32 bt_app_remove_confirm_msgbox_exit_proc(BOOL b_remove, BOOL b_remove_all)
{
    BT_TARGET_DEV_INFO t_device = {0,0,{0},{0}};
    INT32              i4_ret = BT_APPR_OK;

    if(b_remove)  // remove device
    {
        if(b_remove_all)
        {
            if (bt_app_is_sink_dev_list_start()
                ||bt_app_is_audio_output_dev_list_start())
            {
                /* check if scaning is started */
                if (bt_app_is_sink_dev_scaning())
                {
                    BT_APP_LOG_INFO(("<BT_APP><Sink_list> Stop scaning before remove all sink paired devices\n"));

                    /* stop scan timer */
                    bt_app_stop_sink_device_scan_timer();

                    i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
                    if(i4_ret != BT_APPR_OK)
                    {
                        BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
                    }

                    bt_app_set_flag_sink_dev_scaning(FALSE);
                }

                if (bt_app_output_a2dp_connected())
                {
                    /* No need to show disconnect message because need show remove device message */
                    bt_app_set_flag_show_disconnect_message(FALSE);

                    /* remove device should disconnect connected device */
                    bt_app_disconnect_with_sink_dev();
                }

                a_bt_app_sink_paired_device_remove_all();

                // remove all paired device and no unpaired device, then set focus on SCAN button
                if (_gt_bt_sink_dev_list_info.u1_unpaired_dev_num == 0)
                {
                    _gt_bt_sink_dev_list_info.u1_focus_row_index = 0xFF;
                }
                else
                {
                    // focus to the first row
                    _gt_bt_sink_dev_list_info.u1_focus_row_index = 0;
                }

                // set window state to BLUETOOTH_SINK_DEVICE_LIST_STATE
                // then when "COMM_WARN_M_BT_D_REMOVED" shown finish, can recover sink device list
                _e_bluetooth_state = BLUETOOTH_SINK_DEVICE_LIST_STATE;
            }
            else
            {
                a_bt_app_src_paired_device_remove_all();
            }
        }
        else
        {
            if (bt_app_is_sink_dev_list_start()
                ||bt_app_is_audio_output_dev_list_start())
            {
                static BT_APP_SINK_DEV_LIST_INFO_T r_sink_dev_list_info;
                UINT8                       u1_first_dev_index = 0;
                UINT8                       u1_focus_row_index = 0;
                UINT8                       u1_focus_dev_index = 0;
                UINT8                       u1_total_dev_num   = 0;

                /* check if scaning is started */
                if (bt_app_is_sink_dev_scaning())
                {
                    BT_APP_LOG_INFO(("<BT_APP><Sink_list> Stop scaning before remove one paired devices\n"));

                    /* stop scan timer */
                    bt_app_stop_sink_device_scan_timer();

                    i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
                    if(i4_ret != BT_APPR_OK)
                    {
                        BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
                    }

                    bt_app_set_flag_sink_dev_scaning(FALSE);
                }

                /* Get focused device MAC info */
                c_memset(&r_sink_dev_list_info, 0, sizeof(BT_APP_SINK_DEV_LIST_INFO_T));

                bt_app_ui_bt_sink_dev_list_info_get(&r_sink_dev_list_info);

                u1_total_dev_num   = r_sink_dev_list_info.u1_total_dev_num;
                u1_first_dev_index = r_sink_dev_list_info.u1_first_dev_index;
                u1_focus_row_index = r_sink_dev_list_info.u1_focus_row_index;
                u1_focus_dev_index = u1_first_dev_index + u1_focus_row_index;

                if (bt_app_output_a2dp_connected()
                    &&(0 == u1_focus_dev_index))
                {
                    /* No need to show disconnect message because need show remove device message */
                    bt_app_set_flag_show_disconnect_message(FALSE);
                    /* remove device should disconnect connected device */
                    bt_app_disconnect_with_sink_dev();
                }

                a_bt_app_sink_paired_device_remove(r_sink_dev_list_info.sink_dev_list[u1_focus_dev_index].ac_addr);

                if (u1_focus_dev_index + 1 == u1_total_dev_num)
                {
                    /* The removed device is the last one in the sink device list, need to adjust focus row index */
                    if (u1_focus_row_index != 0)
                    {
                        // last one device but not focus on the first row, then focus to the previous row
                        _gt_bt_sink_dev_list_info.u1_focus_row_index = u1_focus_row_index - 1;
                    }
                    else
                    {
                        // the last one and focus on the first row, then it must be the only one, then set focus to SCAN button
                        _gt_bt_sink_dev_list_info.u1_focus_row_index = 0xFF;
                    }
                }

                _e_bluetooth_state = BLUETOOTH_SINK_DEVICE_LIST_STATE;
            }
            else
            {
                a_bt_app_src_paired_device_remove(t_device.bdAddr);
            }
        }

        /* Update bluetooth standby status to IFCON when remove src/snk devices */
        a_bt_setup_bt_standby(FALSE);
    }
    else   // cancel
    {
        if (bt_app_is_sink_dev_list_start()
            ||bt_app_is_audio_output_dev_list_start())
        {
            _e_bluetooth_state = BLUETOOTH_SINK_DEVICE_LIST_STATE;
        }
    }

    return BT_APPR_OK;
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_power_confirm_msgbox_exit_proc
  *
  * Description  - Process the event: BT power confirmation message box exit
  *
  * Inputs         -
  *
  *---------------------------------------------------------------------------*/
INT32 bt_app_power_confirm_msgbox_exit_proc(BOOL b_power_on)
{
    INT32   i4_ret = BT_APPR_OK;

    if(b_power_on) //ok
    {
        //a_cfg_set_bluetooth_switch_status(APP_CFG_BLUETOOTH_SWITCH_ON);
        bt_app_audio_output_dev_list_start();
    }

    return i4_ret;
}


/**---------------------------------------------------------------------------
  * Name          - bt_app_exit_osc_post_proc
  *
  * Description  - Do some process after option menu exit.
  *
  * Inputs         -
  *---------------------------------------------------------------------------*/
INT32 bt_app_exit_osc_post_proc(VOID)
{
    if(BLUETOOTH_MUSIC_PLAYBACK_STATE == _e_bluetooth_state)
    {
        // send playback time to IFCon to update FLD
        _bt_app_send_playback_time_to_ifcon();
    }

    return BT_APPR_OK;
}

#endif


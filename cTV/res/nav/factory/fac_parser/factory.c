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
 * $RCSfile: factory.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_cli.h"
#include "c_handle.h"
#include "c_cfg.h"
#include "c_dbg.h"

#include "app_util/a_cfg.h"
#include "app_util/a_dbg_level_app.h"
#include "app_util/a_sleep_timer.h"
#include "app_util/a_common.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "c_svctx.h"
#include "c_sb.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_iom.h"
#include "res/nav/factory/a_factory.h"

#include "am/a_am.h"
#include "wizard2/a_wzd.h"
#include "nav/fav_lst/a_fav_lst.h"
#include "res/menu2/menu_custom.h"

#ifdef RPC_ENABLE
#include "rpc.h"
#include "ri_desc.h"
#endif

#include <unistd.h>
#include <stdlib.h>
#include "res/app_util/config/acfg_cust_factory_vizio.h"

#include "res/nav/factory/fac_ch_table/nav_fac_load_ch.h"


#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "c_net_socket.h"
#include "agent/agent.h"
#include "app_util/a_network.h"
#include "c_net_config.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/nav_common.h"
#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "../dev/app_util/config/_acfg.h"
#include "../dev/app_util/a_cfg.h"
#include "menu2/menu_common/menu_common.h"
#include "res/app_util/network/network_custom.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct
{
    VOID*                           pv_cmd_val;
    factory_set_cmd_nfy_fct         pf_nfy_fct;
    VOID*                           pv_nfy_tag;
} FACTORY_SET_CMD_MSG_T;

#undef DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE            factory_get_dbg_level()


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static HANDLE_T     h_g_factory = NULL_HANDLE;

static HANDLE_T     h_g_svctx = NULL_HANDLE;

static UINT16       ui2_factory_dbg_level = DBG_LEVEL_NONE;

static factory_custom_init_fct      pf_custom_init_fct;

extern UINT8    aui1_faccmd_ret_val[CMD_LEN_Maximum];

extern BOOL g_b_enter_fac_mode;

HANDLE_T            h_fac_ethernet_timer = NULL_HANDLE;
HANDLE_T            h_fac_wifi_timer = NULL_HANDLE;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _factory_init (
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    );
static INT32 _factory_exit (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    );
static INT32 _factory_pause (
                    HANDLE_T                    h_app
                    );
static INT32 _factory_resume (
                    HANDLE_T                    h_app
                    );
static INT32 _factory_process_msg (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    );



static VOID _fac_ethernet_timeout(HANDLE_T h_timer, VOID* pv_tag);
static VOID _fac_ping_notify_eth(INT16 rsptime);
static VOID _fac_wifi_timeout(HANDLE_T h_timer, VOID* pv_tag);
static VOID _fac_ping_notify_wifi(INT16 rsptime);
static UINT32 _fac_eth_connect(void);
static UINT32 _fac_wifi_connect(void);
static UINT32 _fac_eth_ping(void);
static UINT32 _fac_wifi_ping(void);

static UINT8 _fac_get_wifi_rssi(void);

static UINT32 _fac_audio_tone(BOOL bOnOff);

static void _fac_set_burning_mode(UINT8 value);
/*----------------------------------------------------------------------------
 * Name: factory_get_dbg_level
 *
 * Description:
 *      Get factory debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 factory_get_dbg_level(VOID)
{
    return ui2_factory_dbg_level;
}

/*----------------------------------------------------------------------------
 * Name: factory_set_dbg_level
 *
 * Description:
 *      Get factory debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID factory_set_dbg_level(UINT16 ui2_dbg_level)
{
    ui2_factory_dbg_level = ui2_dbg_level;
}

/*---------------------------------------------------------------------------
 * Name
 *      a_factory_set_registration
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
VOID a_factory_set_registration(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                )
{
    c_strcpy(pt_reg->s_name, FACTORY_NAME);
    pt_reg->t_fct_tbl.pf_init                   = _factory_init;
    pt_reg->t_fct_tbl.pf_exit                   = _factory_exit;
    pt_reg->t_fct_tbl.pf_pause                  = _factory_pause;
    pt_reg->t_fct_tbl.pf_resume                 = _factory_resume;
    pt_reg->t_fct_tbl.pf_process_msg            = _factory_process_msg;
    pt_reg->t_desc.ui8_flags                    = ~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = 8192;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 16;
    pt_reg->t_desc.ui4_app_group_id             = 0;
    pt_reg->t_desc.ui4_app_id                   = 0;
    pt_reg->t_desc.t_max_res.z_min_memory       = 1024 * 4;
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024 * 4;
    pt_reg->t_desc.t_max_res.ui8_max_files_size = 1024 * 1;
    pt_reg->t_desc.t_max_res.ui2_max_files      = 1;
    pt_reg->t_desc.t_max_res.ui2_max_handles    = 64;
    pt_reg->t_desc.t_max_res.ui2_max_threads    = 1;
    pt_reg->t_desc.t_max_res.ui2_max_semaphores = 4;
    pt_reg->t_desc.t_max_res.ui2_max_msg_queues = 1;
    pt_reg->t_desc.t_max_res.ui2_max_nb_msgs    = 20;
    pt_reg->t_desc.t_max_res.ui2_max_msg_size   = 64;
    pt_reg->t_desc.ui2_msg_count                = 20;
    pt_reg->t_desc.ui2_max_msg_size             = 64;
    pt_reg->ui2_key_num                         = 0;

    pf_custom_init_fct = pf_init_fct;
}

/*---------------------------------------------------------------------------
 * Name
 *      a_factory_set_cmd
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
INT32 a_factory_set_cmd(
                FACTORY_SET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_cmd_val,
                factory_set_cmd_nfy_fct         pf_nfy_fct,
                VOID*                           pv_nfy_tag
                )
{
    FACTORY_SET_CMD_MSG_T   t_msg;
    INT32                   i4_ret;

    if (h_g_factory == NULL_HANDLE)
    {
        return FACTORYR_NOT_INIT;
    }

    t_msg.pv_cmd_val = pv_cmd_val;
    t_msg.pf_nfy_fct = pf_nfy_fct;
    t_msg.pv_nfy_tag = pv_nfy_tag;

    i4_ret = c_app_send_msg ( h_g_factory,
                              (UINT32) t_cmd_type,
                              (VOID*) &t_msg,
                              sizeof(t_msg),
                              NULL,
                              NULL );
    if (i4_ret == AEER_OK)
    {
        i4_ret = FACTORYR_OK;
    }
    else if (i4_ret == AEER_OUT_OF_MEMORY)
    {
        i4_ret = FACTORYR_OUT_OF_MEMORY;
    }
    else
    {
        i4_ret = FACTORYR_FAIL;
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------
 * Name
 *      a_factory_get_cmd
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
FACTORY_COND_TYPE_T a_factory_get_cmd(
                FACTORY_GET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_buf,
                SIZE_T                          z_buflen
                )
{
    FACTORY_COND_TYPE_T     t_cond = FACTORY_COND_OK;
    INT32                   i4_ret;

    if (h_g_factory == NULL_HANDLE)
    {
        return FACTORY_COND_NOT_INIT;
    }

    switch (t_cmd_type)
    {
    case FACTORY_GET_CMD_SET_ADAPTIVE_LUMA:
        DBG_INFO(("<factory> get ADAPTIVE LUMA\n"));
        if ((pv_buf == NULL) || (z_buflen < sizeof(INT16)))
        {
            return FACTORY_COND_INV_ARG;
        }
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA),
                              (INT16*) pv_buf);
        if (i4_ret == APP_CFGR_INV_ARG)
        {
            t_cond = FACTORY_COND_INV_ARG;
        }
        else if (i4_ret != APP_CFGR_OK)
        {
            t_cond = FACTORY_COND_FAIL;
        }
        break;

    default:
        t_cond = FACTORY_COND_INV_CMD;
    }

    return t_cond;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
 * Name
 *      _factory_init
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_init (
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<factory> init is invoked\n"));

//    factory_cli_init();

    h_g_factory = h_app;

    if (a_tv_open(SVCTX_NAME_MAIN,
                  NULL,
                  NULL,
                  &h_g_svctx) != TVR_OK)
    {
        DBG_ERROR(("<factory> TV daemon init fails\n"));
        return AEER_FAIL;
    }

    if (pf_custom_init_fct != NULL)
    {
        pf_custom_init_fct ();
    }

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name             -
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_exit (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    )
{
    DBG_INFO(("<factory> exit is invoked\n"));

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_pause
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_pause (
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<factory> pause is invoked\n"));

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_resume
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_resume (
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<factory> resume is invoked\n"));

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _factory_process_msg
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _factory_process_msg (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    )
{
    FACTORY_SET_CMD_MSG_T*      pt_msg;
    FACTORY_COND_TYPE_T         t_cond;
    BOOL                        b_complete;
    INT32                       i4_ret;
    INT16                       i2_get_value;


    DBG_INFO(("<factory> process message is invoked\n"));

    pt_msg = (FACTORY_SET_CMD_MSG_T*) pv_msg;

    i4_ret = APP_CFGR_OK;
    t_cond = FACTORY_COND_OK;
    b_complete = TRUE;

    switch (ui4_type)
    {
        case FACTORY_SET_CMD_CONTEXT_SWITCH:
            if (NULL != pt_msg->pf_nfy_fct)
            {
                pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
            }
            break;

        case FACTORY_CMD_SET_MODEL_INDEX:
            DBG_INFO(("<factory> set model index\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_MODEL_INDEX:
            DBG_INFO(("<factory> get model index\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_MODEL_NAME:
            DBG_INFO(("<factory> set model name\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_MODEL_NAME:
            DBG_INFO(("<factory> get model name\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_SERIAL_NUMBER:
            DBG_INFO(("<factory> set serial number\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_SERIAL_NUMBER:
            DBG_INFO(("<factory> get serial number\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_KEY_HASH:
            DBG_INFO(("<factory> get key hash\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_MAC_ADDRESS:
            DBG_INFO(("<factory> set mac address\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_MAC_ADDRESS:
            DBG_INFO(("<factory> get mac address\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_IP_ADDRESS:
            DBG_INFO(("<factory> set ip address\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_IP_ADDRESS:
            DBG_INFO(("<factory> get ip address\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_VERSION:
            DBG_INFO(("<factory> get version\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_POWER_STATUS:
            DBG_INFO(("<factory> set power status\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_POWER_STATUS:
            DBG_INFO(("<factory> get power status\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_STANDBY_DISABLE:
            DBG_INFO(("<factory> set standby disble\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_STANDBY_DISABLE:
            DBG_INFO(("<factory> get standby disable\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_BURNING_MODE:
            DBG_INFO(("<factory> set buring mode\n"));
            _fac_set_burning_mode((UINT8) (UINT32) pt_msg->pv_cmd_val);
            break;

        case FACTORY_CMD_GET_BURNING_MODE:
            DBG_INFO(("<factory> get buring mode\n"));
            UINT32 ui4_read = 0;
            a_cfg_eep_raw_read(0x1C87, aui1_faccmd_ret_val, 1, &ui4_read);
            DBG_INFO(("<factory> get buring mode  >> aui1_faccmd_ret_val[0] == %d \n",aui1_faccmd_ret_val[0]));
            DBG_INFO(("<factory> get buring mode  >> ui4_read == %d \n",ui4_read));
            break;

        case FACTORY_CMD_SET_TIMER_STATUS:
            DBG_INFO(("<factory> set timer status\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_TIMER_STATUS:
            DBG_INFO(("<factory> get timer status\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_TIMER_VALUE:
            DBG_INFO(("<factory> set timer value\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_INPUT_SOURCE:
            DBG_INFO(("<factory> set input source\n"));
            break;

        case FACTORY_CMD_GET_INPUT_SOURCE:
            DBG_INFO(("<factory> get input source\n"));
            //TODO
            break;

        case FACTORY_CMD_DO_CHANNEL_PRESET:
            DBG_INFO(("<factory> do channel preset\n"));
            acfg_SAC_load_default_channel("FQ");
            break;

        case FACTORY_CMD_GET_CHANNEL_FREQ:
            DBG_INFO(("<factory> get channel freq\n"));
            INT32 temp;
            temp = acfg_SAC_get_channel_freqency();

            aui1_faccmd_ret_val[0] = (UINT8)((temp & 0xFF000000) >> 24);
            aui1_faccmd_ret_val[1] = (UINT8)((temp & 0x00FF0000) >> 16);
            aui1_faccmd_ret_val[2] = (UINT8)((temp & 0x0000FF00) >> 8);
            aui1_faccmd_ret_val[3] = (UINT8)((temp & 0x000000FF) >> 0);

            break;

        case FACTORY_CMD_SET_CHANNEL:
            DBG_INFO(("<factory> set channel\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_CHANNEL:
            DBG_INFO(("<factory> get channel\n"));
            //TODO
            break;

        case FACTORY_CMD_DO_CHANNEL_CLEAN:
            DBG_INFO(("<factory> do channel clean\n"));
            a_cfg_cust_fac_clear_ch_table();
            break;

        case FACTORY_CMD_GET_ADC_CALIBRATION_FLAG:
            DBG_INFO(("<factory> get adc calibration flag\n"));
            //TODO
            break;

        case FACTORY_CMD_DO_ADC_CALIBRATION:
            DBG_INFO(("<factory> do adc calibration\n"));
            //TODO
            break;

        case FACTORY_CMD_CLEAR_ADC_RESULT:
            DBG_INFO(("<factory> clear adc result\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_ADC_DATA:
            DBG_INFO(("<factory> set adc data\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_ADC_DATA:
            DBG_INFO(("<factory> get adc data\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_ADC_DATA_BUNDLE:
            DBG_INFO(("<factory> set adc data bundle\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_ADC_DATA_BUNDLE:
            DBG_INFO(("<factory> get adc data bundle\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_AUDIO_OUT:
            DBG_INFO(("<factory> set audio out\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_AUDIO_OUT:
            DBG_INFO(("<factory> get audio out\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_SOUND_MODE:
            DBG_INFO(("<factory> set sound mode\n"));
            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);
            if (i4_ret == APP_CFGR_INV_ARG)
            {
                t_cond = FACTORY_COND_INV_ARG;
            }
            else if (i4_ret != APP_CFGR_OK)
            {
                t_cond = FACTORY_COND_FAIL;
            }

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE));

            break;

        case FACTORY_CMD_GET_SOUND_MODE:
            DBG_INFO(("<factory> get sound mode\n"));
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MODE), &i2_get_value);
            aui1_faccmd_ret_val[0] = (UINT8)i2_get_value + 1;

            if (i4_ret == APP_CFGR_INV_ARG)
            {
                t_cond = FACTORY_COND_INV_ARG;
            }
            else if (i4_ret != APP_CFGR_OK)
            {
                t_cond = FACTORY_COND_FAIL;
            }

            break;

        case FACTORY_CMD_SET_VOLUME:
            DBG_INFO(("<factory> set volume\n"));

            i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                              (INT16) (UINT32) pt_msg->pv_cmd_val);

            if (i4_ret == APP_CFGR_INV_ARG)
            {
                t_cond = FACTORY_COND_INV_ARG;
            }
            else if (i4_ret != APP_CFGR_OK)
            {
                t_cond = FACTORY_COND_FAIL;
            }

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));

            break;

        case FACTORY_CMD_GET_VOLUME:
            DBG_INFO(("<factory> get volume\n"));

            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL), &i2_get_value);
            aui1_faccmd_ret_val[0] = (UINT8)i2_get_value;

            if (i4_ret == APP_CFGR_INV_ARG)
            {
                t_cond = FACTORY_COND_INV_ARG;
            }
            else if (i4_ret != APP_CFGR_OK)
            {
                t_cond = FACTORY_COND_FAIL;
            }

            break;

        case FACTORY_CMD_SET_PICTURE_MODE:
            DBG_INFO(("<factory> set picture mode\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_PICTURE_MODE:
            DBG_INFO(("<factory> get picture mode\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_PICTURE_PROPERTY:
            DBG_INFO(("<factory> set picture property\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_PICTURE_PROPERTY:
            DBG_INFO(("<factory> get picture property\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_LOCAL_DIMMING:
            DBG_INFO(("<factory> set local dimming\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_LOCAL_DIMMING:
            DBG_INFO(("<factory> get local dimming\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_CLEAR_ACTION:
            DBG_INFO(("<factory> set clear action\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_CLEAR_ACTION:
            DBG_INFO(("<factory> get clear action\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_CT_MODE:
            DBG_INFO(("<factory> set ct mode\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_CT_MODE:
            DBG_INFO(("<factory> get ct mode\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_CT_VALUE:
            DBG_INFO(("<factory> set ct value\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_CT_VALUE:
            DBG_INFO(("<factory> get ct value\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_CT_VALUE_BUNDLE:
            DBG_INFO(("<factory> ct value bundle\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_CT_VALUE_BUNDLE:
            DBG_INFO(("<factory> ct value bundle\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_TEST_PATTERN:
            DBG_INFO(("<factory> set test pattern\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_TEST_PATTERN:
            DBG_INFO(("<factory> get test pattern\n"));
            //TODO
            break;

        case FACTORY_CMD_DO_SETTING_RESET:
            DBG_INFO(("<factory> do setting reset\n"));
            if(pt_msg->pv_cmd_val == NULL)
            {
                a_cfg_custom_reset_pic_mode_setting();
                a_cfg_custom_reset_pic_settings();
            }
            else if (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 1)
                a_cfg_custom_reset_audio();
            else
                a_cfg_fac_reset();

            break;

        case FACTORY_CMD_GET_POWERON_TIME:
            DBG_INFO(("<factory> get poweron time\n"));
            //TODO
            break;

        case FACTORY_CMD_DO_REBOOT:
            DBG_INFO(("<factory> do reboot\n"));
            system("reboot");
            break;

        case FACTORY_CMD_GET_EDID:
            DBG_INFO(("<factory> get edid\n"));
            UINT8   aui1_edid[256] = {0};
            C_GetHDMI1InternalEdidData(aui1_edid);
            C_GetHDMI2InternalEdidData(aui1_edid);
            C_GetHDMI3InternalEdidData(aui1_edid);
            C_GetHDMI4InternalEdidData(aui1_edid);
            C_GetVGAEdidData(aui1_edid);
            c_memset(aui1_faccmd_ret_val, 0x00, sizeof(aui1_faccmd_ret_val));
            c_memcpy( &aui1_faccmd_ret_val, &aui1_edid, 256);
            //TODO
            break;

        case FACTORY_CMD_DO_SKIP_OOBE:
            DBG_INFO(("<factory> do skip oobe\n"));
            a_cfg_set_wzd_status (APP_CFG_WZD_STATUS_INIT+2);
            a_cfg_store();//save to eeprom
            break;

        case FACTORY_CMD_SET_IR_KEYPAD_BLOCK:
            DBG_INFO(("<factory> set ir keypad block\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_IR_KEYPAD_BLOCK:
            DBG_INFO(("<factory> ir keypad block\n"));
            //TODO
            break;

        case FACTORY_CMD_INJECT_KEY_EVENT:
            DBG_INFO(("<factory> inject key event\n"));
            //TODO
            break;

        case FACTORY_CMD_CAPTURE_KEY_EVENT:
            DBG_INFO(("<factory> capture key evnet\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_SOUND_BALANCE:
            DBG_INFO(("<factory> set sound balance\n"));

                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), ((UINT8) (UINT32) pt_msg->pv_cmd_val));

            if (i4_ret != APP_CFGR_OK)
            {
                t_cond = FACTORY_COND_FAIL;
            }
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));

            break;

        case FACTORY_CMD_GET_SOUND_BALANCE:
            DBG_INFO(("<factory> get sound balance\n"));

            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), &i2_get_value);
            DBG_INFO(("<factory> Get sound balance ===%x \n",i2_get_value));
            aui1_faccmd_ret_val[0] = 0x00;
            aui1_faccmd_ret_val[1] = 0x00;
            aui1_faccmd_ret_val[2] = 0x00;
            aui1_faccmd_ret_val[3] = (UINT8)i2_get_value;

            if (i4_ret == APP_CFGR_INV_ARG)
            {
                t_cond = FACTORY_COND_INV_ARG;
            }
            else if (i4_ret != APP_CFGR_OK)
            {
                t_cond = FACTORY_COND_FAIL;
            }

            break;

        case FACTORY_CMD_DO_SOUND_TONE_TEST:
            DBG_INFO(("<factory> do sound tone test\n"));
            if(pt_msg->pv_cmd_val == NULL)
            {
                _fac_audio_tone(FALSE);
            }
            else if (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 1)
            {
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), -50);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
                _fac_audio_tone(TRUE);
            }
            else if (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 2)
            {
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 50);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
                _fac_audio_tone(TRUE);
            }
            else if (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 3)
            {
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE), 0);
                a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE));
                _fac_audio_tone(TRUE);
            }
            else if (((UINT8) (UINT32) pt_msg->pv_cmd_val) == 4)
            {
                //nothing to do;
            }
            else
            {
                //nothing to do;
            }

            break;

        case FACTORY_CMD_SET_FACTORY_RECORD:
            DBG_INFO(("<factory> set factory record\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_FACTORY_RECORD:
            DBG_INFO(("<factory> get factory record\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_LED_ONOFF:
            DBG_INFO(("<factory> set led onoff\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_LED_ONOFF:
            DBG_INFO(("<factory> get led onoff\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_FACTORY_CONTINUE:
            DBG_INFO(("<factory> set factory continue\n"));
            g_b_enter_fac_mode = (INT8) (UINT32)pt_msg->pv_cmd_val;
            //TODO
            break;

        case FACTORY_CMD_GET_FACTORY_CONTINUE:
            DBG_INFO(("<factory> get factory continue\n"));
            aui1_faccmd_ret_val[0] = g_b_enter_fac_mode;
            break;

        case FACTORY_CMD_DO_BT_PAIR:
            DBG_INFO(("<factory> do bt pair\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_BT_RSSI:
            DBG_INFO(("<factory> get bt rssi\n"));
            //TODO
            break;

        case FACTORY_CMD_DO_WIFI_CONNECT:
            DBG_INFO(("<factory> do wifi connect ..\n"));
            _fac_wifi_connect();
            break;

        case FACTORY_CMD_DO_WIFI_TEST:
            DBG_INFO(("<factory> do wifi test\n"));
            _fac_wifi_ping();
            break;

        case FACTORY_CMD_GET_WIFI_RSSI:
            DBG_INFO(("<factory> get wifi rssi\n"));
            aui1_faccmd_ret_val[0] = _fac_get_wifi_rssi();
            break;

        case FACTORY_CMD_DO_ETH_TEST:
            DBG_INFO(("<factory> do eth test\n"));
            _fac_eth_connect();
            _fac_eth_ping();
            break;

        case FACTORY_CMD_WRITE_I2C:
            DBG_INFO(("<factory> write i2c\n"));
            //TODO
            break;

        case FACTORY_CMD_READ_I2C:
            DBG_INFO(("<factory> read i2c\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_LIGHTSENSOR_VALUE:
            DBG_INFO(("<factory> get lightsensor value\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_IPERF_ACTIVE:
            DBG_INFO(("<factory> set iperf active\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_IPERF_ACTIVE:
            DBG_INFO(("<factory> get iperf active\n"));
            //TODO
            break;

        case FACTORY_CMD_DO_USB_TEST:
            DBG_INFO(("<factory> do usb test\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_11POINT_GAMMA:
            DBG_INFO(("<factory> set 11point gamma\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_11POINT_GAMMA:
            DBG_INFO(("<factory> get 11point gamma\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_CEC:
            DBG_INFO(("<factory> set cec\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_CEC:
            DBG_INFO(("<factory> get cec\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_SOUND_AQBYPASS:
            DBG_INFO(("<factory> set sound aqbypass\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_SOUND_AQBYPASS:
            DBG_INFO(("<factory> get sound aqbypass TV\n"));
            //TODO
            break;

        case FACTORY_CMD_SET_SOUND_PQBYPASS:
            DBG_INFO(("<factory> set sound pqbypass\n"));
            //TODO
            break;

        case FACTORY_CMD_GET_SOUND_PQBYPASS:
            DBG_INFO(("<factory> get sound pqbypass\n"));
            //TODO
            break;

        case FACTORY_CMD_PROGRAM_KEY_DATA_NETWORK:
            DBG_INFO(("<factory> program key data network\n"));
            //TODO
            break;

        case FACTORY_CMD_PROGRAM_KEY_DATA_USB:
            DBG_INFO(("<factory> program key data usb\n"));
            //TODO
            break;

        return AEER_FAIL;


        default:
            t_cond = FACTORY_COND_INV_CMD;
    }

    if ((FACTORY_SET_CMD_CONTEXT_SWITCH != ui4_type) &&
        b_complete                       &&
        (t_cond != FACTORY_COND_INV_CMD) &&
        (pt_msg->pf_nfy_fct != NULL))
    {
        pt_msg->pf_nfy_fct ( pt_msg->pv_nfy_tag, (VOID*) t_cond );
    }

    return AEER_OK;
}



static VOID _fac_ethernet_timeout( HANDLE_T    h_timer,
                            VOID*       pv_tag   )
{
    static CHAR             a_ip[20]={0};

    /* Assign IP to the array : a_ip */
    c_memset( a_ip, 0, sizeof(a_ip));  // Clear all to 0.
    c_sprintf(a_ip, "%d.%d.%d.%d", aui1_faccmd_ret_val[0], aui1_faccmd_ret_val[1]
                                 , aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[3]);

    aui1_faccmd_ret_val[4]--;

    if((h_fac_ethernet_timer != NULL_HANDLE) && (aui1_faccmd_ret_val[4] == 0))
        {
            c_timer_stop(h_fac_ethernet_timer);
            c_timer_delete(h_fac_ethernet_timer);
        }

    /* Ping the IP Address */
    a_cfg_ping_ip_v4( a_ip, 2, &_fac_ping_notify_eth);

}


static VOID _fac_wifi_timeout(HANDLE_T    h_timer,
                            VOID*       pv_tag   )
{
    static CHAR             a_ip[20]={0};

    /* Assign IP to the array : a_ip */
    c_memset( a_ip, 0, sizeof(a_ip));  // Clear all to 0.
    c_sprintf(a_ip, "%d.%d.%d.%d", aui1_faccmd_ret_val[0], aui1_faccmd_ret_val[1]
                                         , aui1_faccmd_ret_val[2], aui1_faccmd_ret_val[3]);

    aui1_faccmd_ret_val[4]--;

    if((h_fac_wifi_timer != NULL_HANDLE) && (aui1_faccmd_ret_val[4] == 0))
    {
        c_timer_stop(h_fac_wifi_timer);
        c_timer_delete(h_fac_wifi_timer);
    }

    /* Ping the IP Address */
    a_cfg_ping_ip_v4( a_ip, 2, &_fac_ping_notify_wifi);

}


static VOID _fac_ping_notify_eth(INT16 rsptime)
{
    if(rsptime == -1)
    {
        DBG_INFO (("_fac_ping_notify_eth >>>> fail: %d ms\n", rsptime));
        ++aui1_faccmd_ret_val[6];
    }

    if (aui1_faccmd_ret_val[4] == 0)
        {
        aui1_faccmd_ret_val[7] = (aui1_faccmd_ret_val[6] / aui1_faccmd_ret_val[5]) * 100;
        fact_vizio_ret_uart_ack_data(&aui1_faccmd_ret_val[7], FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
    }
}


static VOID _fac_ping_notify_wifi(INT16 rsptime)
{
    if(rsptime == -1)
    {
        DBG_INFO (("_fac_ping_notify_wifi >>>> fail: %d ms\n", rsptime));
        ++aui1_faccmd_ret_val[6];
}

    if (aui1_faccmd_ret_val[4] == 0)
        {
        aui1_faccmd_ret_val[7] = (aui1_faccmd_ret_val[6] / aui1_faccmd_ret_val[5]) * 100;
        fact_vizio_ret_uart_ack_data(&aui1_faccmd_ret_val[7], FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
    }

}


static UINT32 _fac_wifi_connect(void)
{
    INT32   i4_ret;
    UINT8   ui1_i;
    CHAR    password[64] = {0};
    CHAR    a_ssid[NET_802_11_MAX_LEN_SSID] = {0};
    UINT16  Data_Length = 0;
    CHAR    ssid_length = 0;

    Data_Length = (UINT16)((aui1_faccmd_ret_val[2] << 8) | aui1_faccmd_ret_val[3]);
   /* Assign SSID and Password to the array */
    for(int i = 0, j = 0; i < Data_Length; i++)
    {
        if ( j == 0)
        {
            if (aui1_faccmd_ret_val[i+7] != 0x00)
                a_ssid[i] = aui1_faccmd_ret_val[i+7];
            else
            {
                a_ssid[i] = '\0';
                ssid_length = i + 1;
                j++;
            }
        }
        else
        {
            if (aui1_faccmd_ret_val[i+7] != 0x00)
            {
                password[j-1] = aui1_faccmd_ret_val[i+7];
                j++;
            }
            else
                break;
        }
    }
    DBG_INFO(("a_ssid == %s\n", a_ssid));
    DBG_INFO(("password == %s\n", password));

    /* Check data_size length */
    if(ssid_length >= NET_802_11_MAX_LEN_SSID)
        return FACTORY_COND_INV_ARG;

    /* Switch to Wifi mode */
    i4_ret = nw_custom_get_network_interface(&ui1_i);

    if (i4_ret != NWR_OK)
    {
        DBG_INFO(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
        return FACTORY_COND_FAIL;
    }

    if(ui1_i!=APP_CFG_NET_INTERFACE_WIFI)
    {
        i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_WIFI);
        if (i4_ret != NWR_OK)
        {
            DBG_INFO(("[Fac] a_nw_chg_network_interface(wifi) Fail. Return %d.\n", i4_ret));
            return FACTORY_COND_FAIL;
        }
    }


    /* Associate */
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;

    pt_associate = (NET_802_11_ASSOCIATE_T*)c_mem_alloc(sizeof(NET_802_11_ASSOCIATE_T));
    c_memset(pt_associate, 0x00, sizeof(NET_802_11_ASSOCIATE_T));
    pt_associate->e_AssocCase = IEEE_802_11_MANUAL_ASSOC;

    pt_associate->t_Ssid.ui4_SsidLen = (UINT32)c_strlen(a_ssid);
    c_memcpy(pt_associate->t_Ssid.ui1_aSsid, a_ssid,(SIZE_T)pt_associate->t_Ssid.ui4_SsidLen);
    c_memset(pt_associate->t_Bssid, 0xff,sizeof(NET_802_11_BSSID_T));

    #if 1
    pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_WPA2_PSK;
    pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_TKIP;
    #else
    pt_associate->e_AuthMode  = IEEE_802_11_AUTH_MODE_NONE;
    pt_associate->e_AuthCipher= IEEE_802_11_AUTH_CIPHER_NONE;
    #endif

    /* Password phrase => if e_AuthMode is IEEE_802_11_AUTH_MODE_NONE then Ignored */
    pt_associate->t_Key.pui1_PassPhrase = password;
    pt_associate->t_Key.b_IsAscii = FALSE;

    i4_ret = a_nw_wlan_associate(pt_associate);
    if (i4_ret != NWR_OK)
    {
        DBG_INFO(("[Fac] a_nw_wlan_associate() Fail. Return %d.\n", i4_ret));
        return FACTORY_COND_FAIL;
    }

    return AEER_OK;
}


static UINT32 _fac_wifi_ping(void)
{
    c_timer_create(&h_fac_wifi_timer);
    c_timer_start(h_fac_wifi_timer,
                    50,//(50*ui4_wait_time),
                    X_TIMER_FLAG_REPEAT, //X_TIMER_FLAG_ONCE,
                    _fac_wifi_timeout,
                    NULL);

    return AEER_OK;
}


static UINT32 _fac_eth_connect(void)
{
    INT32   i4_ret;
    UINT8   ui1_i;

    /* Switch to Ethernet mode */
    i4_ret = nw_custom_get_network_interface(&ui1_i);
    if (i4_ret != NWR_OK)
    {
        DBG_INFO(("[Fac] nw_custom_get_network_interface() Fail. Return %d.\n", i4_ret));
        return FACTORY_COND_FAIL;
    }

    if(ui1_i!=APP_CFG_NET_INTERFACE_ETH0)
    {
        i4_ret = a_nw_chg_network_interface(APP_CFG_NET_INTERFACE_ETH0);
        if (i4_ret != NWR_OK)
        {
            DBG_INFO(("[Fac] a_nw_chg_network_interface(eth0) Fail. Return %d.\n", i4_ret));
            return FACTORY_COND_FAIL;
        }
    }

    return AEER_OK;

}


static UINT32 _fac_eth_ping(void)
{
    c_timer_create(&h_fac_ethernet_timer);
    c_timer_start(h_fac_ethernet_timer,
                    (50),
                    X_TIMER_FLAG_REPEAT, //X_TIMER_FLAG_ONCE,
                    _fac_ethernet_timeout,
                    NULL);

    return AEER_OK;

}


static UINT32 _fac_audio_tone(BOOL bOnOff)
{
    INT32   i4_ret;
    TV_WIN_ID_T e_win_id;
    HANDLE_T h_aud_scc_comp;
    SM_COMMAND_T at_sm_cmds[3];
    SCC_AUD_CLIP_T      t_aud_clip;


    i4_ret = nav_get_focus_id (&e_win_id);
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR (("%s:%s:%d:%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open (at_sm_cmds, &h_aud_scc_comp);
    if (i4_ret != SMR_OK)
    {
        DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }


    if (bOnOff == TRUE)
    {
        DBG_INFO(("_fac_audio_tone == %d.\n", bOnOff));

        /* FIXME !!Left 1KHz. */
        t_aud_clip.e_type           = SCC_AUD_CLIP_TYPE_TONE;           /* Tone */
        t_aud_clip.ui4_out_port_mask= ~0;                               /* All out port */
        t_aud_clip.ui4_repeat_cnt   = SCC_AUD_CLIP_REPEAT_CNT_FOREVER;  /* Forever */

        t_aud_clip.ui4_ch_mask        = ~0;
        t_aud_clip.u.ui4_tone_freq    = 1000;

        /* Set test tone. */
        i4_ret = c_scc_aud_set_clip (h_aud_scc_comp, &t_aud_clip, NULL, NULL);
        if (i4_ret != SMR_OK)
        {
            c_scc_comp_close (h_aud_scc_comp);
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
        /* Play test tone. */
        i4_ret = c_scc_aud_set_clip_ctrl(h_aud_scc_comp, SCC_AUD_CTRL_MODE_PLAY);
        if (i4_ret != SMR_OK)
        {
            c_scc_comp_close (h_aud_scc_comp);
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        i4_ret = c_scc_comp_close (h_aud_scc_comp);
        if (i4_ret != SMR_OK)
        {
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
    }
    else
    {
        DBG_INFO(("_fac_audio_tone == %d.\n", bOnOff));

        /* Stop audio test tone. */
        i4_ret = c_scc_aud_set_clip_ctrl(h_aud_scc_comp, SCC_AUD_CTRL_MODE_STOP);
        if (i4_ret != SMR_OK)
        {
            c_scc_comp_close (h_aud_scc_comp);
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
        i4_ret = c_scc_comp_close (h_aud_scc_comp);
        if (i4_ret != SMR_OK)
        {
            DBG_ERROR(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
    }

    return AEER_OK;
}

static UINT8 _fac_get_wifi_rssi(void)
{
    UINT8 retvalue = 0;
#if 1
    NET_802_11_WIFI_RSSI_T      t_rssi;
    c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));
    a_nw_wlan_get_rssi(&t_rssi);
    retvalue = (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2;
#else
    /* Get Signal Strength Level */
    NET_802_11_BSS_INFO_T   t_CurrBss;
    a_nw_wlan_get_curr_bss(&t_CurrBss);
    UINT32 ui4_cnv_lvl = t_CurrBss.i2_Level;
    ui4_cnv_lvl = (ui4_cnv_lvl * 256) / 100;
    if(ui4_cnv_lvl>255)
        ui4_cnv_lvl = 255;
    retvalue = (UINT8) ui4_cnv_lvl;
#endif

    return retvalue;
}

static void _fac_set_burning_mode(UINT8 value)
{
    UINT8   ui1_fac_mask;
    DRV_CUST_OPERATION_INFO_T    t_op_info;//added,20110622
    UINT16 ui2_Burn_idx = 0;//added,20110622
    SIZE_T z_size = sizeof(ui2_Burn_idx);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32 i4_Ret = 0;

    DBG_INFO(("<fac_parser> _fac_set_burning_mode === %d\n",value));
    a_cfg_get_factory_mode(&ui1_fac_mask);
    if(value == 0)
    {
        a_cfg_set_factory_mode(ui1_fac_mask & ~APP_CFG_FAC_MODE_BURNING_MASK);
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_WITH_SIGNAL,
                                      NULL
                                      );
        ui2_Burn_idx = 0;
    }
    else
    {
        a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_NO_SIGNAL,
                                      NULL
                                      );
        ui2_Burn_idx = 1;
    }
    a_cfg_update_factory_mode();
    a_cfg_store();

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* get from driver */
    i4_Ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    if (i4_Ret != RMR_OK)
    {
        DBG_INFO(("<fac_parser> Set BurnIn mode failed !\n"));
    }

}
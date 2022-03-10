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
 * $RCSfile: fact_parser.c,v $
 * $Revision: #1 $
 * $Date: 2015/06/11 $
 * $Author: dtvbm11 $
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
#include "c_dbg.h"

#include "u_irrc_btn_def.h"
#include "u_iom.h"
#include "c_iom.h"

#include "app_util/a_dbg_level_app.h"
#include "app_util/a_common.h"
//#include "res/nav/factory/a_factory.h"
#include "res/app_util/config/a_cfg_custom.h"
//TOP Denny 2009/02/05 add - start : For c_svctx_open() & NAVR_OK
#include "nav/nav_common.h"
#include "c_svctx.h"
//TOP Denny 2009/02/05 add - end

//TOP Denny 2009/02/09 add
#include "res/nav/nav_variant.h"

//TOP Denny 2009/02/20 add-start
#include "res/app_util/config/acfg_custom.h"
#include "app_util/a_tv.h"
#include "app_util/config/_acfg.h"
#include "menu2/menu_common/menu_common.h"
//#include "res/app_util/config/acfg_tpv_fac_custom.h"
//TOP Denny 2009/02/20 add-end

#include "mtperipheral.h"
#include "TPV_factory/a_TPV_factory.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/* Modified by MTK. */
#define FACTORY_VIR_UART_ID       7//use 7 will cause cli no function    7 // 1     //  7 : CLI/factory share the same port.

BOOL g_b_enter_TPV_fac_mode = FALSE;  //ke_vizio_20121220


typedef struct
{
    TPV_FACTORY_SET_CMD_TYPE_T              t_cmd_type;
    UINT8                           aui1_rf_num[3];
    UINT8                           ui1_cs;
} FACTORY_PARSER_SCAN_INFO_T;

//#define CMD_LEN_Maximum             30 // Denny 2009/01/07 move to a_factory.h

#undef DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE            factory_get_dbg_level()

//#define ACK_FOR_CHANGING_SOURCE_RESULT
//#define CLOSE_LISTENER
//TOP Denny 2009/02/05 add
#define CHECK_AUTO_COLOR_TIMEOUT

//TOP Denny 2009/02/20 add-start
typedef struct
{
    VOID*                           pv_cmd_val;
    factory_set_cmd_nfy_fct         pf_nfy_fct;
    VOID*                           pv_nfy_tag;
} FACTORY_SET_CMD_MSG_T;
//TOP Denny 2009/02/20 add-end

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static HANDLE_T                     h_iom_uart = NULL_HANDLE;

static UINT8                        aui1_cmd_buf[CMD_LEN_Maximum];

static UINT16                       ui2_cmd_buf_idx;

static UINT8                        ui1_cmd_length;

static FACTORY_PARSER_SCAN_INFO_T   t_scan_info;

static BOOL                         b_cli_simulate;

static BOOL                         b_factory_mode_started = FALSE;

static UINT32 ui4_timer_pre;
static UINT32 ui4_timer;
static UINT32 ui4_cmd_len_pre;


static INT32 _fact_parser_cli_cmd(INT32 i4_argc, const CHAR** pps_argv);

static CLI_EXEC_T at_FACTORY_SET_CMD_tbl[] =
{
    {"cmd",   "c",   _fact_parser_cli_cmd,  NULL, "usage: SL CM0 CM1 CM2 CM3", CLI_ACCESS_RIGHT_APP_CFG},
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_factory_root_cmd_tbl[] =
{
    {"fact_parser", "fp",  NULL,  at_FACTORY_SET_CMD_tbl, "factory commands",   CLI_ACCESS_RIGHT_APP_CFG},
    END_OF_CLI_CMD_TBL
};

UINT8 aui1_faccmd_ret_val[CMD_LEN_Maximum] = {0};

static UINT8 gPktNbr = 0; // Denny 2008/09/17 add per Uart2AckByte_TV_Proposal071129.txt

BOOL                        b_send_auto_clr_result = FALSE;

extern BOOL                 b_send_alignment_cmd;

extern UINT8                ui1_hdcp_block_size; // (HBS) the size of each block of HDCP data.

extern INT8                 ui1_hdcp_last_block_num; // the last(final) block number of HDCP data.

//Denny 2009/01/12
UINT8                       ui1_data_leng = 0; // Denny 2009/01/12 add

//Denny 2009/02/05 add
static HANDLE_T             h_g_fac_auto_color_svctx = NULL_HANDLE;

//Denny 2009/02/05 add
#ifdef CHECK_AUTO_COLOR_TIMEOUT
HANDLE_T                    h_fac_auto_color_timer = NULL_HANDLE;
//UINT32                      ui4_fac_auto_start_time = 0;
BOOL                        b_auto_color_time_out = FALSE;
#endif

#ifdef TPV_2K19_DFX_SIGNAL_DETECT
UINT8 g_ui1_signal_status = 0;
#endif
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _fact_parser_iom_nfy_fct(
                    VOID*                       pv_nfy_tag,
                    IOM_NFY_COND_T              e_nfy_cond,
                    UINT32                      ui4_evt_code,
                    UINT32                      ui4_data);
static VOID _fact_parser_iom_nfy_rec_buf(
                    UINT32                      ui4_size);
static VOID _fact_parser_parse_and_set_cmd(VOID);
static VOID _fact_parser_set_cmd_nfy(
                    VOID*                       pv_tag,
                    VOID*                       pv_val);
static VOID _fact_parser_set_cmd_nfy_to_leave(
                    VOID*                       pv_tag,
                    VOID*                       pv_val);

#if 0
static VOID _fact_parser_single_rf_scan_nfy(
                    VOID*                       pv_tag,
                    VOID*                       pv_val);
#endif

void TPVComm_TwoAckByteOkMsgGet(UINT8 *pui1_Buff);
void TPVComm_TwoAckByteNotSupportMsgGet(UINT8 *pui1_Buff);

//TOP Denny 2009/02/05 add - start
VOID fac_AutoColor2_svctx_notify_fct(
    HANDLE_T            h_g_auto_color_dialog_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag);
//TOP Denny 2009/02/05 add - end

extern INT32 c_svctx_get(
                    HANDLE_T                        h_svctx,            /* in  */
                    SVCTX_GET_TYPE_T                e_get_type,         /* in  */
                    VOID*                           pv_get_info,        /* in/out */
                    SIZE_T*                         pz_get_info_size    /* in/out */
                    );
//TOP Denny 2009/02/05 add
#ifdef CLOSE_LISTENER
extern INT32 factory_close_svctx(UINT16 ui2_type);
#endif

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: fact_parser_init
 *
 * Description: Initialize the factory parser.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
__attribute__ ((visibility("default"))) VOID a_TPV_fact_parser_init(VOID)
{
    UART_SETTING_T  t_uart_setting;
    /* Added by MTK. */
    UINT32 ui4_mode = IOM_UART_OPERATION_MODE_FACTORY| IOM_UART_OPERATION_MODE_TRANSPARENT;
//TOP Denny 2009/02/05 add
    INT32           i4_ret;

    ui2_cmd_buf_idx = 0;
    ui4_cmd_len_pre = 0;
    c_memset(&t_scan_info, 0, sizeof(t_scan_info));

    t_uart_setting.e_speed    = IOM_UART_SPEED_115200;
    t_uart_setting.e_data_len = IOM_UART_DATA_LEN_8;
    t_uart_setting.e_parity   = IOM_UART_PARITY_NONE;
    t_uart_setting.e_stop_bit = IOM_UART_STOP_BIT_1;

    //ke_vizio_20160929 mask, due to abnomral  setting.
    //MTPINMUX_SetEx(235, 3);
    //MTPINMUX_SetEx(236, 3);	
	
    if (c_iom_open(IOM_DEV_TYPE_IO_UART,
                   FACTORY_VIR_UART_ID,
                   NULL,
                   (VOID*) &t_uart_setting,
                   NULL,
                   _fact_parser_iom_nfy_fct,
                   &h_iom_uart) != IOMR_OK)
    {
        /*DBG_ERROR(("<fact_parser> UART open fails\n"));*/
        DBG_LOG_PRINT(("<fact_parser> UART open fails\n"));
    }

    /* Added by MTK. */
    if (c_iom_set(h_iom_uart,
                  IOM_SET_UART_OPERATION_MODE,
                  &ui4_mode,
                  sizeof(ui4_mode)))
    {
        DBG_LOG_PRINT(("<fact_parser> Start UART mode fails\n"));
    }
    b_cli_simulate = FALSE;

    if (c_cli_attach_cmd_tbl(at_factory_root_cmd_tbl,
                             CLI_CAT_APP,
                             CLI_GRP_GUI) != CLIR_OK)
    {
        /*DBG_ERROR(("<fact_parser> CLI init fails\n"));*/
        DBG_LOG_PRINT(("<fact_parser> CLI init fails\n"));
    }

//TOP Denny 2009/02/05 add-start
    i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_g_fac_auto_color_svctx);
    if (i4_ret != NAVR_OK) {
        return;
    }

    i4_ret = c_svctx_set_listener(h_g_fac_auto_color_svctx,
                                  fac_AutoColor2_svctx_notify_fct,
                                  NULL);
    if (i4_ret != NAVR_OK) {
        return;
    }
//TOP Denny 2009/02/05 add-end
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _fact_parser_iom_nfy_fct
 *
 * Description: Factory parser UART handler.
 *
 * Inputs:  pv_nfy_tag      Contains a tag value.
 *          e_nfy_cond      Contains the notify condition.
 *          ui4_evt_code    Contains the event code.
 *          ui4_data        Contains information related to the event.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _fact_parser_iom_nfy_fct(
    VOID*               pv_nfy_tag,
    IOM_NFY_COND_T      e_nfy_cond,
    UINT32              ui4_evt_code,
    UINT32              ui4_data)
{
    switch (e_nfy_cond)
    {
    case IOM_NFY_COND_REC_UART_DATA:
        _fact_parser_iom_nfy_rec_buf(ui4_data);
        break;

    case IOM_NFY_COND_XMT_COMPLETE:
        /* what to do? */
        break;

    default:
        break;
    }
}
/* Added by MTK. */
static VOID _fact_parse_cmd( VOID* pv_data, VOID* pv_val)
{
    _fact_parser_parse_and_set_cmd ();
}
/*-----------------------------------------------------------------------------
 * Name: _fact_parser_iom_nfy_rec_buf
 *
 * Description: Call back function of receiving data. It's called as UART driver
 *              call the notify function.
 *
 * Inputs:  ui4_data        Contains information related to the event.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
#if 1
static VOID _fact_parser_iom_nfy_rec_buf(
    UINT32              ui4_data)
{
    IOM_UART_T*         pt_iom_uart;
    UINT16              ui2_idx;
    UINT32              ui4_timer_period = 0;
    
    pt_iom_uart = (IOM_UART_T*) ui4_data;
    if (0 == pt_iom_uart->z_len)
    {
        return;
    }

    #if 0
    ui2_idx = 0;
    while(ui2_idx < pt_iom_uart->z_len)
    {
        //pt_iom_uart->pui1_data[ui2_idx]
        DBG_LOG_PRINT(("\n[TPV_FAC] %s pui1_data[%d]: 0x%x\n", __FUNCTION__, ui2_idx, pt_iom_uart->pui1_data[ui2_idx]));
        ++ui2_idx;
    }
    #endif
        
    ui4_timer = c_os_get_sys_tick();
    ui4_timer_period = ui4_timer - ui4_timer_pre;
    DBG_LOG_PRINT(("\n[TPV_FAC] %s ui4_timer_period: %d\n", __FUNCTION__, ui4_timer_period));
    DBG_LOG_PRINT(("\n[TPV_FAC] %s ui4_cmd_len_pre: %d\n", __FUNCTION__, ui4_cmd_len_pre));
    if((ui4_timer_period < 45) && (ui4_cmd_len_pre > 30) &&
       (!(((pt_iom_uart->pui1_data[0] == 0x6E) && (pt_iom_uart->pui1_data[1] == 0x51) &&(pt_iom_uart->pui1_data[3] == 0x01)) ||
       (pt_iom_uart->pui1_data[0] == 0x6E) && (pt_iom_uart->pui1_data[1] == 0x51) &&(pt_iom_uart->pui1_data[3] == 0x03))))
    {
        ui2_idx = 0;
        /* MTK: Suggest to add a lock here. */
        while (ui2_idx < pt_iom_uart->z_len)
        {

            if(ui2_cmd_buf_idx >= CMD_LEN_Maximum)  //ke_vizio_20110402 for clean warning.
            {
                break;
            }
            
            aui1_cmd_buf[ui2_cmd_buf_idx] = pt_iom_uart->pui1_data[ui2_idx];
            ++ui2_cmd_buf_idx;
            ++ui2_idx;
        }
        
        ui1_cmd_length = ui1_cmd_length + pt_iom_uart->z_len;
        /* Added by MTK. */
        if (a_TPV_factory_set_cmd(TPV_FACTORY_SET_CMD_CONTEXT_SWITCH,
                              NULL,
                              _fact_parse_cmd,
                              NULL ) != FACTORYR_OK)
        {
            DBG_LOG_PRINT(("<fact_parser> UART ack command to factory daemon fails\n"));
        }
    }
    else
    {
        ui2_idx = 0;
        ui2_cmd_buf_idx = 0;
        /* MTK: Suggest to add a lock here. */
        while (ui2_idx < pt_iom_uart->z_len)
        {
    //        if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0xC0) || (pt_iom_uart->pui1_data[ui2_idx] == 0x58)) // Denny 2008/09/10 modify
            if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0x6E) || (pt_iom_uart->pui1_data[ui2_idx] == 0x58))
            {
                if(ui2_cmd_buf_idx >= CMD_LEN_Maximum)  //ke_vizio_20110402 for clean warning.
                {
                    break;
                }
                
                aui1_cmd_buf[ui2_cmd_buf_idx] = pt_iom_uart->pui1_data[ui2_idx];
                ++ui2_cmd_buf_idx;
                
            }
            ++ui2_idx;
        }

        ui1_cmd_length = pt_iom_uart->z_len;
        /* Added by MTK. */
        if (a_TPV_factory_set_cmd(TPV_FACTORY_SET_CMD_CONTEXT_SWITCH,
                              NULL,
                              _fact_parse_cmd,
                              NULL ) != FACTORYR_OK)
        {
            DBG_LOG_PRINT(("<fact_parser> UART ack command to factory daemon fails\n"));
        }
    }
    
    ui4_timer_pre = ui4_timer;
    ui4_cmd_len_pre = pt_iom_uart->z_len;
    return;
}
#else
static VOID _fact_parser_iom_nfy_rec_buf(
    UINT32              ui4_data)
{
    IOM_UART_T*         pt_iom_uart;
    UINT16              ui2_idx;

    pt_iom_uart = (IOM_UART_T*) ui4_data;
    if (0 == pt_iom_uart->z_len)
    {
        return;
    }
    ui2_idx = 0;
    /* MTK: Suggest to add a lock here. */
    while (ui2_idx < pt_iom_uart->z_len)
    {
//        if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0xC0) || (pt_iom_uart->pui1_data[ui2_idx] == 0x58)) // Denny 2008/09/10 modify
        if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0x6E) || (pt_iom_uart->pui1_data[ui2_idx] == 0x58))
        {
            if(ui2_cmd_buf_idx >= CMD_LEN_Maximum)  //ke_vizio_20110402 for clean warning.
            {
                break;
            }
            
            aui1_cmd_buf[ui2_cmd_buf_idx] = pt_iom_uart->pui1_data[ui2_idx];
            ++ui2_cmd_buf_idx;
        }
        ++ui2_idx;
    }

    ui2_cmd_buf_idx = 0;
    ui1_cmd_length = pt_iom_uart->z_len;
    /* Added by MTK. */
    if (a_TPV_factory_set_cmd(TPV_FACTORY_SET_CMD_CONTEXT_SWITCH,
                          NULL,
                          _fact_parse_cmd,
                          NULL ) != FACTORYR_OK)
    {
        DBG_LOG_PRINT(("<fact_parser> UART ack command to factory daemon fails\n"));
    }
    /* Removed by MTK. */
//    _fact_parser_parse_and_set_cmd();
    /* MTK: Suggest to unlock here. */

    return;
}

#endif
/*-----------------------------------------------------------------------------
 * Name: _fact_parser_parse_and_set_cmd
 *
 * Description: Parse the command and send translated generic message to the
 *              factory daemon.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _fact_parser_parse_and_set_cmd(VOID)
{
    TPV_FACTORY_SET_CMD_TYPE_T      t_cmd_type = TPV_FACTORY_INVALID_CMD;
    VOID*                       pv_cmd_val = (VOID*) 0;
    VOID*                       pv_tag = (VOID*) 0;
    BOOL                        b_do_common_set_cmd;
    UINT16                      ui2_id;
#if 0		//kyo_20091006 mark for Alignment inactive issue
    static INT16                i2_adaptive_luma;
#endif
    UINT16                      aui2_eep_address_high;
    UINT8                       aui1_eep_address_low;
    UINT8                       ui1_eep_bytes;
    UINT32                      aui4_eep_address;
    UINT8                       ui1_checksum = 0x6E, ui1_length = 0; // Denny 2008/09/17 add
    INT32                       i4_ret = 0;

    //ke_vizio_20170922 add.
    if((aui1_cmd_buf[2] >= 0x00) && (aui1_cmd_buf[2] <= 0x80)){
        DBG_LOG_PRINT(("0 <= cmd[2] <= 0x80\n, illegal length"));

        //special case for security key code.  //TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY
        // ingore DBS_Hi byte
        if(aui1_cmd_buf[4] == 0xFE && aui1_cmd_buf[5] == 0xF0 && aui1_cmd_buf[6] == 0x1B){
            ui1_length = 11 + aui1_cmd_buf[9];
            DBG_LOG_PRINT(("ui1_length : %d\n", ui1_length));
        }
        else{
            ui1_length = (aui1_cmd_buf[2]-0x80)+3;
        }
    }
    else{
        ui1_length = (aui1_cmd_buf[2]-0x80)+3;
    }
    
    b_do_common_set_cmd = TRUE;

    // Check CMD format
    if(!( ((aui1_cmd_buf[0]==0x6E) && (aui1_cmd_buf[1]==0x51)) // 2k9 cmd
        || (aui1_cmd_buf[0]==0x58)))                           //
    {
        return;
    }

    if((aui1_cmd_buf[0]==0x6E) && (aui1_cmd_buf[1]==0x51))
    {
        // Checksum
        for(ui2_id = 1; ui2_id < (ui1_length); ui2_id ++)
        {
            if(ui2_id >= CMD_LEN_Maximum)  //ke_vizio_20110330 for clean warning.
            {
                DBG_LOG_PRINT(("ui1_length >= CMD_LEN_Maximum\n"));
                return;
            }
            ui1_checksum ^= aui1_cmd_buf[ui2_id];
        }

        if(ui1_checksum != aui1_cmd_buf[ui1_length])      // Check sum is not correct
        {
            #if 1  //For get check sum
            //c_thread_delay(10000);  //ke_vizio_201220 cancel.
            DBG_LOG_PRINT(("Check Sum error!!! Check sum is 0x%x\n", ui1_checksum));
            #endif
            return;
        }
    }

    if(aui1_cmd_buf[0] == 0x6E && aui1_cmd_buf[1] == 0x51 && aui1_cmd_buf[2] == 0x86 && \
       aui1_cmd_buf[3] == 0x03 && aui1_cmd_buf[4] == 0xFE && aui1_cmd_buf[5] == 0xE1 && \
       aui1_cmd_buf[6] == 0xA0 && aui1_cmd_buf[7] == 0x00 && aui1_cmd_buf[8] == 0x01)
    {
        DBG_LOG_PRINT(("Enter factory\n"));
        g_b_enter_TPV_fac_mode = TRUE;
    }

  #ifdef TPV_2K19_DFM
    if(aui1_cmd_buf[0] == 0x6E && aui1_cmd_buf[1] == 0x51 && aui1_cmd_buf[2] == 0x88 && \
       aui1_cmd_buf[3] == 0x03 && aui1_cmd_buf[4] == 0xFE && aui1_cmd_buf[5] == 0xE1 && \
       aui1_cmd_buf[6] == 0xA0 && aui1_cmd_buf[7] == 0x03)
    {
        DBG_LOG_PRINT(("Enter factory Quick Mode\n"));
        g_b_enter_TPV_fac_mode = TRUE;
    }
  #endif

    if(g_b_enter_TPV_fac_mode == FALSE)
    {
        DBG_LOG_PRINT(("Enter factory fail\n"));
        return ;
    }

    
    switch(aui1_cmd_buf[0])
    {
        // 2k8 Factory Alignment Commands (1st Byte)
        case 0x58:
            // Cmd Byte (2nd Byte)
            switch(aui1_cmd_buf[1])
            {
                case 0x10:  // Set BRIGHTNESS
                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_BRIGHTNESS;
                    pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[2];
                    break;

                case 0xEF:  /* Enter/exit factory mode */
                    switch (aui1_cmd_buf[2])
                    {
                        case 0x00: /* Exit factory mode */
                            t_cmd_type = TPV_FACTORY_SET_CMD_LEAVE_FACTORY_MODE;
                            pv_cmd_val = (VOID*) 0;
#if 1
                            pv_tag = (VOID*) ((t_cmd_type << 24)      |
                                              (aui1_cmd_buf[1] ^
                                               aui1_cmd_buf[2] ^
                                               aui1_cmd_buf[3] ^
                                               aui1_cmd_buf[4]));

                            if (a_TPV_factory_set_cmd(t_cmd_type,
                                                  pv_cmd_val,
                                                  _fact_parser_set_cmd_nfy_to_leave,
                                                  pv_tag ) != FACTORYR_OK)
                            {
                                /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
                                DBG_LOG_PRINT(("<fact_parser> Set command to factory daemon fails\n"));
                            }
                            return;
#else
                            break;
#endif

                        case 0x01: /* Enter factory mode */
                            t_cmd_type = TPV_FACTORY_SET_CMD_ENTER_FACTORY_MODE;
                            pv_cmd_val = (VOID*) 0;
                            break;

                        default:
                            return;
                    }
                    break;
                case 0xD0:  // Write EEPROM data by byte
                    t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_TO_NVRAM_ONE_BYTE;
                    aui2_eep_address_high = (UINT16)aui1_cmd_buf[2];
                    aui1_eep_address_low = (UINT8)aui1_cmd_buf[3];
                    aui4_eep_address = ((aui2_eep_address_high << 8) | aui1_eep_address_low);
                    pv_cmd_val = (VOID*) (aui4_eep_address);
                    aui1_faccmd_ret_val[0] = aui1_cmd_buf[4];
                    break;

                case 0xD1:  // Read EEPROM data by byte
                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_FROM_NVRAM_ONE_BYTE;
                    aui2_eep_address_high = (UINT16)aui1_cmd_buf[2];
                    aui1_eep_address_low = (UINT8)aui1_cmd_buf[3];
                    aui4_eep_address = ((aui2_eep_address_high << 8) | aui1_eep_address_low);
                    pv_cmd_val = (VOID*) (aui4_eep_address);
                    break;

                case 0xE0:  // Write EEPROM data by up to 8 bytes
                    t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_TO_NVRAM_MULTI_BYTES;
                    ui1_eep_bytes = (UINT8)aui1_cmd_buf[2];
                    if(ui1_eep_bytes > 8)
                    {
                        ui1_eep_bytes = 8;
                    }
                    if(ui1_eep_bytes == 0)
                    {
                        ui1_eep_bytes = 1;
                    }

                    aui2_eep_address_high = (UINT16)aui1_cmd_buf[3];
                    aui1_eep_address_low = (UINT8)aui1_cmd_buf[4];
                    aui4_eep_address = ((aui2_eep_address_high << 8) | aui1_eep_address_low);
                    pv_cmd_val = (VOID*) ((aui4_eep_address << 8) | ui1_eep_bytes);
                    for(ui2_id = 0; ui2_id < ui1_eep_bytes; ui2_id ++)
                    {
                        aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+5];
#if 0
                        SerTransparent();
                        Printf("aui1_cmd_buf[%d+5]= %x\n", ui2_id, aui1_cmd_buf[ui2_id+5]);
#endif
                    }
                    break;

                case 0xE1:  // Read EEPROM data by up to 8 bytes
                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_FROM_NVRAM_MULTI_BYTES;
                    aui2_eep_address_high = (UINT16)aui1_cmd_buf[2];
                    aui1_eep_address_low = (UINT8)aui1_cmd_buf[3];
                    ui1_eep_bytes = (UINT8)aui1_cmd_buf[4];
                    if(ui1_eep_bytes > 8)
                    {
                        ui1_eep_bytes = 8;
                    }
                    if(ui1_eep_bytes == 0)
                    {
                        ui1_eep_bytes = 1;
                    }

                    aui4_eep_address = ((aui2_eep_address_high << 8) | aui1_eep_address_low);
                    pv_cmd_val = (VOID*) ((aui4_eep_address << 8) | ui1_eep_bytes);
                    break;
                default:
                    break;
            }
            break;

        // 2k9 Factory Alignment Commands
        case 0x6E:
            switch(aui1_cmd_buf[1])
            {
                case 0x51:

                    switch(aui1_cmd_buf[2])
                    {
                        // Packet Length = 4
                        case 0x84:
                            switch(aui1_cmd_buf[3])
                            {
                                // Read Commands
                                case 0x01:
                                    switch(aui1_cmd_buf[4])
                                    {
                                        // Read Volume
                                        case 0x62:
                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_VOLUME;
                                            break;
                                    }
                                    break;
                                // Write Commands
                                case 0x03:
                                    switch(aui1_cmd_buf[4])
                                    {
                                        // Set Volume
                                        case 0x62:
                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_VOLUME;
                                            pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[6];
                                            break;
                                    }
                                    break;
                                default:
                                    break;
                            }
                            break;
                        // Packet Length = 6
                        case 0x86: // aui1_cmd_buf[2] == 0x86
                            switch (aui1_cmd_buf[3])
                            {   case 0x01: // Read

                                    switch (aui1_cmd_buf[4])
                                    {
                                        case 0xfe: // Pre2
                                            switch (aui1_cmd_buf[5])  //cmd byte
                                            {
                                                case 0x16: // R Gain (Color Temp)
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_COLOR_GAIN_RED;
                                                    break;
                                                case 0x18: // G Gain (Color Temp)
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_COLOR_GAIN_GREEN;
                                                    break;
                                                case 0x1A: // B Gain (Color Temp)
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_COLOR_GAIN_BLUE;
                                                    break;
                                                case 0x6C: // R Offset (Color Temp)
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_COLOR_OFFSET_RED;
                                                    break;
                                                case 0x6E: // G Offset (Color Temp)
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_COLOR_OFFSET_GREEN;
                                                    break;
                                                case 0x70: // B Offset (Color Temp)
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_COLOR_OFFSET_BLUE;
                                                    break;
                                                case 0x10: // Brightness
                                                    t_cmd_type = TPV_FACTORY_READ_CMD_BRIGHTNESS;
                                                    break;
                                                case 0x12: // Contrast
                                                    t_cmd_type = TPV_FACTORY_READ_CMD_CONTRAST;
                                                    break;
                                                case 0x60: // Input Source
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_GET_SOURCE_TYPE;
                                                    break;
                                                case 0x66:
                                                {
                                                    if(aui1_cmd_buf[6] == 0x0C)
                                                        t_cmd_type = TPV_FACTORY_READ_CMD_GET_CPU_TEMPERATURE;
                                                    break;
                                                }
                                                case 0xE1: // FCode01
                                                    switch (aui1_cmd_buf[6])
                                                    {
                                                    	case 0xA4:	//kyo_20111226
                                                            switch(aui1_cmd_buf[7])
                                                            {
                                                            case 0x0B:
                                                                if (aui1_cmd_buf[8] == 0x00)
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_HDCP_LEN;
                                                                break;

                                                            case 0x1D:  // TPV_FACTORY_SET_CMD_GET_LIGHT_SENSOR, Ben 20180326
                                                                if (aui1_cmd_buf[8] == 0x00)
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_GET_LIGHT_SENSOR;
                                                                break;
                                                                
                                                            default:
                                                                break;
                                                            }
                                                            break;
                                                        case 0xA7:  //ke_vizio_20130716 add
                                                            switch(aui1_cmd_buf[7])
                                                            {
                                                            case 0x07:
                                                                if(aui1_cmd_buf[8] == 0x01){
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_GET_PANEL_TYPE;
                                                                }
                                                                break;
                                                            default:
                                                                break;
                                                            }
                                                            break;
#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output in Alignment
                                                        case 0xA9:
                                                            switch(aui1_cmd_buf[7])
                                                            {
                                                                case 0x00:
                                                                    switch(aui1_cmd_buf[8])
                                                                    {
                                                                        case 0x00:
                                                                            t_cmd_type = TPV_FACTORY_SET_CMD_GET_VCOM_DATA;
                                                                            break;
                                                                    }
                                                                    break;
                                                                case 0x04:
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_GET_PANEL_GAMMA_DATA;
                                                                    pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[8];
                                                                    break;
                                                            }
                                                            break;
#endif
                                                        case 0xE2: // Read HDCP CRC
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_HDCP_CRC;
                                                            break;
                                                        case 0xE3:	//kyo_20111223
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x00){
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_READ_HDCP_KSV;
                                                            }
                                                            else if(aui1_cmd_buf[7] == 0x01){
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_READ_HDCP_2_X_RECEIVE_ID;  // Read HDCP 2.x Receive ID
                                                            }
                                                        }
                                                            break;
                                                        case 0xAC:  //ke_vizio_20130708 add
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_GET_PANEL_ID;
                                                            break;
														case 0xB8:  
															if (aui1_cmd_buf[7] == 0x00)
															{
																if (aui1_cmd_buf[8] == 0x02)
																	t_cmd_type = TPV_FACTORY_SET_CMD_GET_PQ_BYPASS;
															}	
                                                            break;	
                                                        default:
                                                            break;
                                                    }
                                                    break;
                                                case 0xE2: // FCode02
                                                    switch (aui1_cmd_buf[6])
                                                    {
                                                        case 0x01: // ADC Gain Red
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_ADC_GAIN_RED;
                                                            break;

                                                        case 0x02: // ADC Gain Green
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_ADC_GAIN_GREEN;
                                                            break;

                                                        case 0x03: // ADC Gain Blue
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_ADC_GAIN_BLUE;
                                                            break;

                                                        case 0x04: // ADC Offset Red
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_ADC_OFFSET_RED;
                                                            break;

                                                        case 0x05: // ADC Offset Green
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_ADC_OFFSET_GREEN;
                                                            break;

                                                        case 0x06: // ADC Offset Blue
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_ADC_OFFSET_BLUE;
                                                            break;
                                                    }
                                                    break;

                                                case 0xE3: // Bulk Data Transfer Read/Write
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_FROM_NVRAM_MULTI_BYTES;
                                                    aui2_eep_address_high = (UINT16)aui1_cmd_buf[7];
                                                    aui1_eep_address_low = (UINT8)aui1_cmd_buf[8];
                                                    ui1_eep_bytes = (UINT8)aui1_cmd_buf[6];
                                                    if(ui1_eep_bytes > 8)
                                                    {
                                                        ui1_eep_bytes = 8;
                                                    }
                                                    if(ui1_eep_bytes == 0)
                                                    {
                                                        ui1_eep_bytes = 1;
                                                    }

                                                    aui4_eep_address = ((aui2_eep_address_high << 8) | aui1_eep_address_low);
                                                    pv_cmd_val = (VOID*) ((aui4_eep_address << 8) | ui1_eep_bytes);
                                                    break;

                                                // FCode04 >>> aui1_cmd_buf[5]==0xE4  // Denny 2009/02/27 add
                                                case 0xE4:
                                                    switch(aui1_cmd_buf[6])
                                                    {
//Denny 2009/03/17 add-start
                                                        case 0x07:
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x01)  //ke_vizio_20190320
                                                            {
                                                                t_cmd_type = TPV_FACTORY_READ_CMD_GET_LOCKSIGNAL_STATUS;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  //source ID
                                                            }
                                                            else if(aui1_cmd_buf[7] == 0x02)  //ke_vizio_20190318
                                                            {
                                                                t_cmd_type = TPV_FACTORY_READ_CMD_READ_IO_INTERFACE_STATUS;
                                                            }
                                                            else
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_CHECK_SIGNAL;
                                                            }
                                                            break;
                                                        }
//Denny 2009/03/17 add-end
                                                        case 0x13: // Read S/W version
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_READ_SW_VER;
                                                            break;
                                                        default:
                                                            break;
                                                    }
                                                    break;

                                                //ke_20090107_add  // Denny 2009/01/12 add -start
                                                case 0xE8: //FCode08
                                                {
                                                    t_cmd_type = TPV_FACTORY_READ_CMD_EDID_SERIAL_NUM;
                                                    pv_cmd_val = (VOID*) ((UINT32)aui1_cmd_buf[6]);
                                                    break;
                                                }

                                                case 0xE9: //FCode09
                                                {
                                                    t_cmd_type = TPV_FACTORY_READ_CMD_EDID_MODEL_NAME;
                                                    pv_cmd_val = (VOID*) ((UINT32)aui1_cmd_buf[6]);
                                                    break;
                                                }
                                                // Denny 2009/01/12 add -end

                                                case 0xEA: // Read HDCP data
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_READ_HDCP_DATA;
                                                    ui1_hdcp_block_size = (UINT8)(UINT16)aui1_cmd_buf[6];
                                                    pv_cmd_val = (VOID*) ((UINT32)aui1_cmd_buf[7]);
                                                    break;

                                                case 0xF0:  //FCode10
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        case 0x01:
                                                            if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8] == 0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR;
                                                            }

                                                            if(aui1_cmd_buf[7] == 0x02 && aui1_cmd_buf[8] == 0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_WIRED_ETHERNET_IPV4_ADDR;
                                                            }
                                                            break;

                                                        case 0x02:
                                                            if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8] == 0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR;
                                                            }

                                                            if(aui1_cmd_buf[7] == 0x02 && aui1_cmd_buf[8] == 0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_WIFI_IPV4_ADDR;
                                                            }

                                                            #ifdef APP_TPV_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
                                                            if(aui1_cmd_buf[7] == 0x06 && aui1_cmd_buf[8] == 0x00)  //ke_vizio_20170523
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_WIFI_AUTO_DETECTION_STATUS;
                                                            }
                                                            #endif
                                                            break;


                                                        case 0x03:
                                                            if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8] == 0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR;
                                                            }
															
															if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8] == 0x02)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI;
                                                            }
                                                            break;

														case 0x11:	//kyo_20111226
															switch(aui1_cmd_buf[7])
															{
															case 0x03:
																if(aui1_cmd_buf[8]==0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_FAC_GET_VOL;
																}
																break;
	                                                        default:
	                                                            break;
	                                                        }
	                                                        break;
															
														case 0x18:	//kyo_20111223
															switch(aui1_cmd_buf[7])
															{
															case 0x03:
																if(aui1_cmd_buf[8]==0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_FAC_NVM_VER;
																}
																break;
														
															case 0x04:
																if(aui1_cmd_buf[8]==0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_FAC_MODEL_NAME;
																}
																break;	
                                                            
															//Frankie_add
															case 0x06:
																if(aui1_cmd_buf[8]==0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_FAC_MCU_VER;
																}
																break;		

															case 0x07:
																if(aui1_cmd_buf[8]==0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_FAC_AQ_VER;
																}
																break;

															case 0x08:
																if(aui1_cmd_buf[8]==0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_FAC_PQ_VER;
																}
																break;																
                                                            
															case 0x12:
																if(aui1_cmd_buf[8]==0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_FAC_UBOOT_VER;
																}
																break;	                                                            
	                                                        default:
	                                                            break;
	                                                        }
                                                            break;
                                               #ifdef TPV_2K19_DFM // Ben 20181221
                                                        case 0x1C:
                                                            if(aui1_cmd_buf[7] == 0x02)
                                                            {
                                                                pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];   // Function_Type
                                                                t_cmd_type = TPV_FACTORY_GET_CMD_FACTORY_CHECK_FLAG;
                                                            }
                                                            break;
                                               #endif
                                                        default:
                                                            break;
                                                    }
                                                    break;
												case 0xF1: // FCode11		// Ben 20131125
													switch(aui1_cmd_buf[6])
													{
		                                                case 0x05:
															if(aui1_cmd_buf[7] == 0x02) // Ben 20131121
															{
																if(aui1_cmd_buf[8] == 0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_GET_ULPK_INDEX;
																}
																if(aui1_cmd_buf[8] == 0x01)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_GET_ULI_REG_STATUS;
																}
															}
                                                            if(aui1_cmd_buf[7] == 0x04)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_ULPK_KEY;
                                                            }
															break;
		                                                default:
		                                                    break;
													}
													break;

												case 0xCC: // Frankie_add light sensor
													switch(aui1_cmd_buf[6])
													{
		                                                case 0x55:
															if(aui1_cmd_buf[7] == 0x00) 
															{
																if(aui1_cmd_buf[8] == 0x00)
																{
																	t_cmd_type = TPV_FACTORY_SET_CMD_GET_LIGHT_SENSOR;
																}
															}
															break;
		                                                default:
		                                                    break;
													}
													break;
																									
                                                default:
                                                    break;
                                            }
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                case 0x03: // Write
                                    switch (aui1_cmd_buf[4])
                                    {
                                        case 0xfe: // Pre2
                                            switch (aui1_cmd_buf[5])
                                            {
                                                // Alignment Color
                                                case 0x16: // R Gain (Color Temp)
                                                case 0x18: // G Gain (Color Temp)
                                                case 0x1A: // B Gain (Color Temp)
                                                case 0x6C: // R Offset (Color Temp)
                                                case 0x6E: // G Offset (Color Temp)
                                                case 0x70: // B Offset (Color Temp)
                                                    if(aui1_cmd_buf[6]==0x00)
                                                    {
                                                        pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];	//kyo_20091007
#if 0
                                                        // Positive numbers
                                                        if(aui1_cmd_buf[8]>=128 && aui1_cmd_buf[8]<=153) //Denny 2009/03/06 //148=>153
                                                        {
                                                            pv_cmd_val = (VOID*) (aui1_cmd_buf[8] - 128);
                                                        }
                                                        // Negative numbers
                                                        else if(aui1_cmd_buf[8]>=103 && aui1_cmd_buf[8]<=127) // Do 2's complement
                                                        {
                                                            UINT8 ui1_2complement = (~(128 - aui1_cmd_buf[8]))+1; // (0xEC~0xFF => -20~-1 => -0x14~-0x01)
                                                            pv_cmd_val = (VOID*) ui1_2complement;
                                                        }
                                                        else if(aui1_cmd_buf[8]>153) //Denny 2009/03/06 //148=>153
                                                        {
                                                            pv_cmd_val = (VOID*) 0x19; // +25 //Denny 2009/03/06 //0x14=>0x19
                                                        }
                                                        else if(aui1_cmd_buf[8]<103) //Denny 2009/03/06 //108=>103
                                                        {
                                                            pv_cmd_val = (VOID*) 0xE7; // -25 //Denny 2009/03/06 //0xEC=>0xE7
                                                        }
#endif
                                                        switch(aui1_cmd_buf[5])
                                                        {
                                                        case 0x16: // R Gain (Color Temp)
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_RED;
                                                            break;
                                                        case 0x18: // G Gain (Color Temp)
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_GREEN;
                                                            break;
                                                        case 0x1A: // B Gain (Color Temp)
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_COLOR_GAIN_BLUE;
                                                            break;
                                                        case 0x6C: // R Offset (Color Temp)
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_COLOR_OFFSET_RED;
                                                            break;
                                                        case 0x6E: // G Offset (Color Temp)
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_COLOR_OFFSET_GREEN;
                                                            break;
                                                        case 0x70: // B Offset (Color Temp)
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_COLOR_OFFSET_BLUE;
                                                            break;
                                                        }
                                                    }
                                                    break;

                                                case 0x12: // Contrast
                                                    if(aui1_cmd_buf[6]==0x00)
                                                    {
                                                        t_cmd_type = TPV_FACTORY_SET_CMD_SET_CONTRAST;
                                                        pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                    }
                                                    break;
                                                case 0x10: // Brightness
                                                    if(aui1_cmd_buf[6]==0x00)
                                                    {
                                                        t_cmd_type = TPV_FACTORY_SET_CMD_SET_BRIGHTNESS;
                                                        pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                    }
                                                    break;

                                                // Save or Recall Color Temp >>> aui1_cmd_buf[5]==0x14
                                                case 0x14:
                                                    switch (aui1_cmd_buf[6])
                                                    {
                                                        case 0x01: // Color sRGB
                                                            break;
                                                        case 0x05: // Color 6500K // WARM
                                                            // Recall Color Temp
                                                            if((aui1_cmd_buf[8]==0x01) || (aui1_cmd_buf[8]==0x21))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_WARM; //ke_vizio_20191015 rename
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            // Save Color Temp
                                                            else if(aui1_cmd_buf[8]==0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_WARM;  //ke_vizio_20191015 rename
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            break;
                                                        case 0x06: // Color 7500(7800) // Normal
                                                            // Recall Color Temp
                                                            if((aui1_cmd_buf[8]==0x01) || (aui1_cmd_buf[8]==0x21))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_NORMAL;  //ke_vizio_20191015 rename
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            // Save Color Temp
                                                            else if(aui1_cmd_buf[8]==0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_NORMAL;  //ke_vizio_20191015 rename
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            break;
                                                        case 0x0A: // Color 11500K // COOL
                                                            // Recall Color Temp
                                                            if((aui1_cmd_buf[8]==0x01) || (aui1_cmd_buf[8]==0x21))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_COOL;
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            // Save Color Temp
                                                            else if(aui1_cmd_buf[8]==0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_COOL;
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            break;
                                                        case 0x0B: // Select color temp USER
                                                            // Recall Color Temp
                                                            if((aui1_cmd_buf[8]==0x01) || (aui1_cmd_buf[8]==0x21))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_COLOR_TEMP_USER;
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            // Save Color Temp
                                                            else if(aui1_cmd_buf[8]==0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_COLOR_TEMP_USER;
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            break;
                                                        case 0x00: // Save All Color Temp
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_TO_NVRAM; // Save to NVRAM
                                                            pv_cmd_val = (VOID*) 0;
                                                            break;
                                                        default:
                                                            break;
                                                    }
                                                    break; // end of case 0x14: // Save or Recall Color Temp >>> aui1_cmd_buf[5]==0x14

                                                // Auto-Config (Auto Adjust)[PC] >>> aui1_cmd_buf[5]==0x1E
                                                case 0x1E: // Invoke Auto-config
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_AUTO_CLK_PHS_POS;
                                                    pv_cmd_val = (VOID*) 0;
                                                    break;

                                                // Auto-Level (Auto Color)[front ADC] >>> aui1_cmd_buf[5]==0x1F
                                                case 0x1F: // Invoke ADC calibration
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_AUTO_COLOR;
                                                    pv_cmd_val = (VOID*) 0;
                                                    break;

                                                // Restore Factory Default >>> aui1_cmd_buf[5]==0x04
                                                case 0x04: // Hard reset NVRAM
                                                    if((aui1_cmd_buf[6]==0x00) && (aui1_cmd_buf[7]==0x00) && (aui1_cmd_buf[8]==0x00))
                                                    {
                                                        t_cmd_type = TPV_FACTORY_SET_CMD_RESET_NVRAM_FACTORY_DEFAULT;
                                                        pv_cmd_val = (VOID*) 0;
                                                    }
                                                    //ke_vizio_20121220 add
                                                    if((aui1_cmd_buf[6]==0x02) && (aui1_cmd_buf[7]==0x00) && (aui1_cmd_buf[8]==0x00))
                                                    {
                                                        t_cmd_type = TPV_FACTORY_SET_CMD_Execute_Factory_Domain_Reset;
                                                        pv_cmd_val = (VOID*) 0;
                                                    }
                                                    break;

                                                // Select Input (Main) Source >>> aui1_cmd_buf[5]==0x60
                                                case 0x60:
                                                    if(!(aui1_cmd_buf[6]==0)) // Check Ext Byte
                                                    {
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        UINT8 aui1_sub_id = ((aui1_cmd_buf[7]&0xE0)>>5); // Get the port number;
                                                        if(aui1_sub_id == 0) aui1_sub_id = 1;
                                                        pv_cmd_val = (VOID*)(UINT32) aui1_sub_id; // Set port number
                                                    }

                                                    switch(aui1_cmd_buf[7] & 0x1F)
                                                    {
                                                        case 0x01: // Select source analog RGB
                                                        case 0x02: // Select source analog RGB
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_VGA;
                                                            break;

                                                        case 0x03: // Select source HDMI
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI;
                                                            break;

                                                        case 0x04: // Select source TV
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_TV;
                                                            break;

                                                        case 0x05: // Select source AV
                                                    #if 0 //New VIZIO spec combine YPbPr and CVBS
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMP_VIDEO;
                                                    #else
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMBI;
                                                    #endif
                                                            break;

                                                        case 0x07: // Select source YPbPr1
                                                    #if 0 //New VIZIO spec combine YPbPr and CVBS
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_Y_PB_PR;
                                                    #else
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMBI;  
                                                    #endif
                                                            break;

                                                        case 0x09: // Select source Scart1/Scart2
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_SCART;
                                                            break;
                                                        default:
                                                            break;
                                                    }
                                                    aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];
                                                    break;

                                                case 0xD6: //ke_vizio_20121220 modify // Power Down
                                                    if(((aui1_cmd_buf[6]==0x00) && (aui1_cmd_buf[7]==0x00) && (aui1_cmd_buf[8]==0x00))||
                                                       ((aui1_cmd_buf[6]==0x00) && (aui1_cmd_buf[7]==0x00) && (aui1_cmd_buf[8]==0x05)))
                                                    {
                                                        t_cmd_type = TPV_FACTORY_SET_CMD_POWER_DOWN;
                                                    }
                                                    break;

                                                // FCode01 >>> aui1_cmd_buf[5]==0xE1
                                                case 0xE1: // FCode01
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        // Enter/Exit Factory Mode
                                                        case 0xA0:
                                                            // Enter Factory mode
                                                            if((aui1_cmd_buf[7]==0x00)&&(aui1_cmd_buf[8]==0x01))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_ENTER_FACTORY_MODE;
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            // Exit Factory mode
                                                            else if((aui1_cmd_buf[7]==0x00)&&(aui1_cmd_buf[8]==0x00))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_LEAVE_FACTORY_MODE;
                                                                pv_cmd_val = (VOID*) 0;
                                                            }
                                                            break;

                                                        // NVM Init
                                                        case 0xA1: // Reset at final stage (before ex-factory & shipping)
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_RESET_AT_FINAL_STAGE;
                                                            pv_cmd_val = (VOID*) 0;
                                                            break;

                                                        case 0xA2: // Set Burn-in mode
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_AGEING_MODE;
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            break;

                                                        case 0xA3:  //ke_vizio_20160907 add
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x00 && aui1_cmd_buf[8] == 0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_CLEAR_BACKLIGHT_HOUR;
                                                            }
                                                            break;
                                                        }
                                                    
                                                        case 0xA7: // ZhongLi
                                                            switch (aui1_cmd_buf[7])
                                                            {
                                                                case 0x00:  /* Set virgin mode */
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_VIRGIN_MODE;
                                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                    break;

                                                                case 0x01:  /* Set ort mode */
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_ORT_MODE;
                                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                    break;

                                                                case 0x02:  /* Set audio balance */
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_BALANCE_MODE;
                                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                    break;

                                                                case 0x03:  /* Set DCR mode */
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_DYNAMIC_CONTRAST_MODE;
                                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                    break;

                                                                case 0x04:  /* Set cable/antenna mode */
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_TUNER_SOURCE_MODE;
                                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                    break;

                                                                case 0x05:  /* Set smart picture mode */
                                                                    switch (aui1_cmd_buf[8])
                                                                    {
                                                                        case 0x00: // Select picture mode VIVID
                                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_VIVID;
                                                                            pv_cmd_val = (VOID*) 0;
                                                                            break;

                                                                        case 0x01: // Select picture mode BRIGHT
                                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_BRIGHT;
                                                                            pv_cmd_val = (VOID*) 0;
                                                                            break;

                                                                        case 0x02: // Select picture mode CALIBTATED
                                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_CALIBRATED;
                                                                            pv_cmd_val = (VOID*) 0;
                                                                            break;

                                                                        case 0x03: // Select picture mode CALIBTATED DARK
                                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_CALIBRATED_DARK;
                                                                            pv_cmd_val = (VOID*) 0;
                                                                            break;

                                                                        case 0x04: // Select picture mode GAME
                                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_GAME;
                                                                            pv_cmd_val = (VOID*) 0;
                                                                            break;

                                                                        case 0x05: // Select picture mode SPORT
                                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_PIC_MODE_SPORT;
                                                                            pv_cmd_val = (VOID*) 0;
                                                                            break;	

                                                                        default:
                                                                            return;
                                                                    }
                                                                    break;

                                                                case 0x08: // Auto Calculate the HDCP's CRC value. //ke_20090107_add  // Denny 2009/01/12 add
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE;
                                                                    pv_cmd_val = (VOID*) 0;
                                                                    break;

                                                                case 0x0B: // Set EDID Self Writing Request Event // Denny 2010/03/19 add
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_EDID_SELF_WRITE;
                                                                    pv_cmd_val = (VOID*) 0;
                                                                    break;

                                                                case 0xA0: // Reset before adjusting white-balance
                                                                    t_cmd_type = TPV_FACTORY_SET_CMD_PREPARE_FOR_WB_ADJ;
                                                                    pv_cmd_val = (VOID*) 0;
                                                                    break;

                                                                default:
                                                                    return;
                                                            }
                                                            break; // end of aui1_cmd_buf[6]==0xA7 (ZhongLi commands)

#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2009/12/24 add
                                                        case 0xA8:
                                                            
															switch (aui1_cmd_buf[7])
                                                            {
                                                            case 0x00:  /* Set Panel Vcom Alignment Initialize */
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_ON_OFF;
                                                                pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                break;

                                                            case 0x01:  /* Store Panel Vcom Alignment Data (to panel) */
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_GAMMA_ON_OFF;
                                                                pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                break;

                                                            }
                                                            break;
#endif

#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output in Alignment
                                                        case 0xA9:
                                                            switch (aui1_cmd_buf[7])
                                                            {
                                                            case 0x02:  /* Set Panel Vcom Alignment Initialize */
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_INITIAL_VCOM_ALIGNMENT;
                                                                pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                                break;

                                                            case 0x03:  /* Store Panel Vcom Alignment Data (to panel) */
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_STORE_VCOM_ALIGNMENT_DATA;
                                                                pv_cmd_val = (VOID*) 0;
                                                                break;

                                                            case 0x05:
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_STORE_PANEL_GAMMA_DATA;
                                                                pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            }
                                                            break;
                                                        case 0xAA:
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_FINETUNE_VCOM_DATA;
                                                            pv_cmd_val = (VOID*) 0;
                                                            aui1_faccmd_ret_val[0] = aui1_cmd_buf[7]; //Polarity 0:Add the offset. 1:Minus the offset.
                                                            aui1_faccmd_ret_val[1] = aui1_cmd_buf[8]; //Offset
                                                            break;
#endif
                                                        case 0xE0: // HDCP Transfer start
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SETUP_BULK_DATA_TRANS;
                                                            ui1_hdcp_last_block_num= aui1_cmd_buf[7];
                                                            ui1_hdcp_block_size = aui1_cmd_buf[8];
                                                            break;

                                                        case 0xE2: // Write HDCP CRC
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_HDCP_CRC;
                                                            pv_cmd_val = (VOID*) (UINT32) (((UINT16)aui1_cmd_buf[7]<<8) | (UINT16)aui1_cmd_buf[8]);
                                                            break;

                                                        default:
                                                            break;
                                                    }
                                                    break; // end of case 0xE1: // FCode01


                                                // FCode02 >>> aui1_cmd_buf[5]==0xE2
                                                case 0xE2: // FCode02
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        // Set ADC gain/offset.
                                                        case 0x01: // SEt ADC R Gain
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_ADC_GAIN_RED;
                                                            break;

                                                        case 0x02: // SEt ADC G Gain
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_ADC_GAIN_GREEN;
                                                            break;

                                                        case 0x03: // SEt ADC B Gain
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_ADC_GAIN_BLUE;
                                                            break;

                                                        case 0x04: // SEt ADC R Offset
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_ADC_OFFSET_RED;
                                                            break;

                                                        case 0x05: // SEt ADC G Offset
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_ADC_OFFSET_GREEN;
                                                            break;

                                                        case 0x06: // SEt ADC B Offset
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_ADC_OFFSET_BLUE;
                                                            break;
                                                    }
                                                    break; // end of case 0xE2: // FCode02

                                                case 0xE4: //FCode04  //ke_vizio_20131030 add
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        case 0x04:
                                                            if(aui1_cmd_buf[7] == 0x00)
                                                            {
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_PICTURE_SIZE;
                                                            }
                                                            break;
                                                        default:
                                                            break;
                                                    }
                                                    break;
                                                // FCode05 >>> aui1_cmd_buf[5]==0xE5	//kyo_20111226
                                                case 0xE5: // FCode05
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SELECT_TV_CHANNEL;
                                                    for(ui2_id = 0; ui2_id < 3; ui2_id ++)
                                                    {
                                                        aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+6];
                                                    }
                                                    break; // end of case 0xE5: // FCode05

                                                // FCode07 >>> aui1_cmd_buf[5]==0xE7  // Denny 2008/11/03 add
                                                case 0xE7: // FCode07
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_TEST_PATTERN;
                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                    break; // end of case 0xE2: // FCode07

                                                //ke_vizio_20121205 sync from Denny
                                                // FCode10 >>> aui1_cmd_buf[5]==0xF0
                                                case 0xF0:
                                                {
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        case 0x10:
                                                        {
                                                            switch(aui1_cmd_buf[7])
                                                            {
                                                                case 0x05:
                                                                    switch(aui1_cmd_buf[8])
                                                                    {
                                                                    #ifdef Disable_USB_Auto_Start
                                                                    case 0x01:
                                                                        t_cmd_type = TPV_FACTORY_SET_CMD_FAC_DISABLE_USB_AUTO_START; //Denny 2012/11/08 add to Disable USB Auto Start in TPV Factory FT (Function Test).....
                                                                        break;
                                                                    #endif
                                                                    default:
                                                                        break;
                                                                    }
                                                                    break;
                                                                default:
                                                                    break;
                                                            }
                                                            break;
                                                        }

                                                        case 0x12:  //ke_vizio_20160908 add
                                                        {
                                                            if(aui1_cmd_buf[7]==0x00)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_CEC_ON_OFF;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];
                                                            }
                                                            else if(aui1_cmd_buf[7]==0x01)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_ARC_ON_OFF;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];
                                                            }
                                                            break;
                                                        }

                                                        #ifdef APP_TPV_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
                                                        case 0x02:  //ke_vizio_20170523
                                                        {
                                                            if(aui1_cmd_buf[7]==0x05)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_WIFI_AUTO_DETECTION;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];
                                                            }
															break;
                                                        }
                                                        #endif

													#ifdef FAC_BT_TESTBLE //Ben 20170809
														case 0x03:
														{
															// Test-BLE on/off,
															if(aui1_cmd_buf[7] == 0x04)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_TESTBLE_ON_OFF;
																pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            }
                                                            break;
														}
													#endif

                                                    #ifdef FAC_BACKLIGHT_CHECK // Ben 20180403
                                                        case 0x1C:  // TPV_FACTORY_SET_CMD_LCDIM_TEST  , Ben 20180326
                                                        if(aui1_cmd_buf[7]==0x03)
                                                        {
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_LCDIM_TEST;
                                                            pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                        }
                                                        break;
                                                    #endif
                                                    
                                                        default:
                                                            break;
                                                    }
                                                    break;
                                                }
                                                
                                                // Backlight
                                                case 0x13: // Set BACKLIGHT
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SET_BACK_LIGHT;
                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                    break;

                                            #ifdef FAC_WB_USE_SCE_PATTERN  // Ben 20170818
										   
												// Internal pattern
												case 0x74:
												{
													if(aui1_cmd_buf[6] == 0x0C)
													{
														if(aui1_cmd_buf[7] == 0x00)
														{
														    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[8];
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_INTERNAL_TEST_PATTERN;
														}
													}
												}
												break;						
											#endif


                                                default:
//TOP Denny 2009/01/20 add for Model Name & Serial Number cmd -start
                                                //Special case when the code length is 6, 0x86.
                                                {
                                                    if(aui1_cmd_buf[3] == 0x03 && aui1_cmd_buf[4] == 0xfe)
                                                    {
                                                        if(aui1_cmd_buf[5] == 0xe8){
														    t_cmd_type = TPV_FACTORY_SET_CMD_EDID_SERIAL_NUM;
                                                        }
                                                        else if(aui1_cmd_buf[5] == 0xe9){
															t_cmd_type = TPV_FACTORY_SET_CMD_EDID_MODEL_NAME;
														}
                                                        #if 1
                                                        pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[6];
                                                        ui1_data_leng = (aui1_cmd_buf[2]&0x0F)-4; // 4+L

                                                        for(ui2_id = 0; ui2_id < ui1_data_leng; ui2_id ++)
                                                        {
                                                            //ke_vizio_20110401
                                                            if((ui2_id+7) >= CMD_LEN_Maximum){
                                                                break;
                                                            }
                                                            aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+7];
                                                        }
                                                        #else
                                                        pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[6];
                                                        if(pv_cmd_val <=8 )
                                                        {   //batch mode
                                                            ui1_data_leng = (aui1_cmd_buf[2]&0x0F)-4; // 4+L

                                                            for(ui2_id = 0; ui2_id < ui1_data_leng; ui2_id ++)
                                                            {
                                                                //ke_vizio_20110401
                                                                if((ui2_id+7) >= CMD_LEN_Maximum){
                                                                    break;
                                                                }
                                                                aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+7];
                                                            }
                                                        }
                                                        else
                                                        {   //direct mode
                                                            ui1_data_leng = (UINT8)pv_cmd_val;
                                                            for(ui2_id = 0; ui2_id < pv_cmd_val; ui2_id ++)
                                                            {
                                                                //ke_test
                                                                if((ui2_id+7) >= CMD_LEN_Maximum){
                                                                    break;
                                                                }
                                                                
                                                                aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+7];
                                                            }
                                                        }
                                                        #endif
                                                        break; //Denny 2010/02/01 add. If it's not added, the cmd won't be executed.
                                                    }
                                                    return;
                                            }
//TOP Denny 2009/01/20 add for Model Name & Serial Number cmd -end
                                            }

                                            break;

                                        default:
                                            return;
                                    }
                                    break;

                                default:
                                    return;
                            }
                            break;// -- end of Packet length = 6

                        default:  // Packet length != 6

                            switch (aui1_cmd_buf[3])
                            {   
                                case 0x01: // Read
                                    switch (aui1_cmd_buf[4])
                                    {
                                        case 0xfe: // Pre2
                                            switch(aui1_cmd_buf[5])
                                            {
                                                // FCode10 >>> aui1_cmd_buf[5]==0xF0
                                                case 0xF0:
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                    case 0x10:
                                                        switch(aui1_cmd_buf[7])
                                                        {
                                                        case 0x03:
                                                            if(aui1_cmd_buf[8]==0x01)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FAC_GET_USB_ATTACH;
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];
                                                            }
                                                            break;

                                                        case 0x04:
                                                            if(aui1_cmd_buf[8]==0x01)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FAC_GET_USB_OVERCURRENT;
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];
                                                            }
                                                            break;
															
															default:
																break;
														}
														break;
														
													case 0x14:	
														switch(aui1_cmd_buf[7])
                                                        {
                                                        case 0x02:
															if(aui1_cmd_buf[8]==0x02)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_READ_KEYPAD_STATUS;   //Denny 2014/02/17 add
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];
                                                            }
															break;
                                                        default:
                                                            break;
                                                        }
                                                        break;
                                                    case 0x16:
                                                        switch(aui1_cmd_buf[7])
                                                        {
                                                        case 0x02:
                                                            if(aui1_cmd_buf[8]==0x07)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_READ_CHANNEL_FREQ;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[9];  //Tuner_Attr
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[10]; //Ch_Attr
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[11]; //MajorCh_HiByte
                                                                aui1_faccmd_ret_val[3] = aui1_cmd_buf[12]; //MajorCh_LoByte
                                                                aui1_faccmd_ret_val[4] = aui1_cmd_buf[13]; //MinorCh_HiByte
                                                                aui1_faccmd_ret_val[5] = aui1_cmd_buf[14]; //MinorCh_Lobyte
                                                            }
                                                            break;
                                                        default:
                                                            break;
                                                        }
                                                        break;
                                            #if 1	//sam 121129
                                                    // 0x17
                                                    case 0x17:
                                                        switch(aui1_cmd_buf[7])
                                                        {
                                                        case 0x03:
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_FAC_READ_EDID; //Denny 2011/12/26 add
                                                            for(ui2_id = 0; ui2_id <= 2; ui2_id ++)
                                                            {
                                                                aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+8];
                                                            }
                                                            break;

                                                        default:
                                                            break;
                                                        }
                                                        break;
                                            #endif

                                                    case 0x1A:
                                                        switch(aui1_cmd_buf[7])
                                                        {
                                                            case 0x02:
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_GAMMA_TABLE_FROM_STORAGE;   
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8]*2;	//length >> High+Low byte = 1
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];	//gammaID
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[10];	//colorTemp
                                                                aui1_faccmd_ret_val[3] = aui1_cmd_buf[11];	//color R/G/B
                                                                aui1_faccmd_ret_val[4] = aui1_cmd_buf[12];	//StartNo
                                                                break;
                                                            default:
                                                                break;
                                                        }
                                                        break;

                                                    case 0x1B:
                                                        switch(aui1_cmd_buf[7])
                                                        {
                                                            case 0x02:
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_READ_SECURITY_KEY_STATUS;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8]; //key_number = n
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    aui1_faccmd_ret_val[1+ui2_id] = aui1_cmd_buf[9+ui2_id]; // check_key[n]
                                                                }
                                                                break;
                                                            }

                                                            default:
                                                                break;
                                                        }
                                                        break;

                                                    default:
                                                        break;
                                                    }
                                                break;

                                                case 0xF1: // FCode11
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        case 0x05:
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x03)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_GET_POTK_KEY;
                                                            }
                                                            if(aui1_cmd_buf[7] == 0x05)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_CHECK_POTK_INDEX;

                                                                for(ui2_id = 0; ui2_id < (aui1_cmd_buf[8]); ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }
                                                            break;
                                                        }
                                                        default:
                                                            break;
                                                    }
                                                    break;
                                                    
                                                default:
                                                    break;
                                            }
                                            break;

                                        default:
                                            break;
                                    }
                                    break;
                                    
                                case 0x03: // Write

                                    switch (aui1_cmd_buf[4])
                                    {
                                        case 0xfe: // Pre2
                                            switch (aui1_cmd_buf[5])
                                            {

                                                case 0x14:
                                                    {
                                                        switch (aui1_cmd_buf[6])
                                                        {
                                                            case 0xF6:
                                                            {
                                                                switch (aui1_cmd_buf[7])
                                                                {
                                                                    case 0x01:
                                                                    {
                                                                        //aui1_faccmd_ret_val[0]: ColorTemp
                                                                        //aui1_faccmd_ret_val[1]: LV_high
                                                                        //aui1_faccmd_ret_val[2]: LV_low
                                                                        UINT8   ui1_i;
                                                                        
                                                                        for(ui1_i=0; ui1_i<3; ui1_i++)
                                                                            aui1_faccmd_ret_val[ui1_i] = aui1_cmd_buf[8+ui1_i];
                                                                        t_cmd_type = TPV_FACTORY_SET_CMD_SET_HDR_PANEL_NITS;
                                                                    }
                                                                    break;

                                                                    case 0x02:
                                                                    {
                                                                        //aui1_faccmd_ret_val[0]: ColorTemp
                                                                        //aui1_faccmd_ret_val[1]: x_high
                                                                        //aui1_faccmd_ret_val[2]: x_low
                                                                        //aui1_faccmd_ret_val[3]: y_high
                                                                        //aui1_faccmd_ret_val[4]: y_low
                                                                        UINT8   ui1_i;
                                                                        
                                                                        for(ui1_i=0; ui1_i<5; ui1_i++)
                                                                            aui1_faccmd_ret_val[ui1_i] = aui1_cmd_buf[8+ui1_i];
                                                                        t_cmd_type = TPV_FACTORY_SET_CMD_SET_HDR_PANEL_GAMUT;
                                                                    }
                                                                    break;

                                                                  #ifdef TPV_2K19_DFM
                                                                    case 0x03:
                                                                    {
                                                                        //aui1_faccmd_ret_val[0]: Warm_LV.HiByte
                                                                        //aui1_faccmd_ret_val[1]: Warm_LV.LoByte
                                                                        //aui1_faccmd_ret_val[2]: Normal_LV.HiByte
                                                                        //aui1_faccmd_ret_val[3]: Normal_LV.LoByte
                                                                        //aui1_faccmd_ret_val[4]: Cool_LV.HiByte
                                                                        //aui1_faccmd_ret_val[5]: Cool_LVLoiByte
                                                                        UINT8   ui1_i;
                                                                        
                                                                        for(ui1_i=0; ui1_i<6; ui1_i++)
                                                                            aui1_faccmd_ret_val[ui1_i] = aui1_cmd_buf[8+ui1_i];
                                                                        t_cmd_type = TPV_FACTORY_SET_CMD_SET_HDR_PANEL_NITS_NEW;
                                                                    }
                                                                    break;
                                                                  #endif
                                                                }
                                                            }
                                                            break;
                                                        }  
                                                    }
                                                    break;
#ifdef FAC_WB_USE_SCE_PATTERN // Denny 2009/12/21 add
                                                case 0x74:
                                                    {
                                                        switch (aui1_cmd_buf[6])
                                                        {
                                                        case 0x01:
                                                            {
                                                                UINT8   ui1_i;
                                                                /* Copy the values of 7th byte to 13th byte. Total 7 bytes. */
                                                                for(ui1_i=0; ui1_i<7; ui1_i++)
                                                                    aui1_faccmd_ret_val[ui1_i] = aui1_cmd_buf[7+ui1_i];
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_INTERNAL_RGB_PATTERN;
                                                            }
                                                            break;
                                                        case 0x05:
                                                            {
                                                                UINT8   ui1_i;
                                                                /* Copy the values of 7th byte to 9th byte. Total 3 bytes. */
                                                                for(ui1_i=0; ui1_i<3; ui1_i++)
                                                                    aui1_faccmd_ret_val[ui1_i] = aui1_cmd_buf[7+ui1_i];
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_INTERNAL_GRAY_PATTERN;
                                                            }
                                                            break;
                                                        default:
                                                            break;
                                                        }
                                                    }
                                                    break;
#endif

                                                //ke_vizio_20130702
                                                // FCode01 >>> aui1_cmd_buf[5]==0xE1
                                                case 0xE1: // FCode01
                                                    switch(aui1_cmd_buf[6])
                                                    {

                                                #ifdef TPV_2K19_DFM
                                                    case 0xA0:
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x03)
                                                            {
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];   // mode
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];   // pattern switch
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[10];  // pattern level
                                                                
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_ENTER_QUICK_FACTORY_MODE;
                                                            }
                                                        }
                                                        break;
                                                #endif
                                                
                                                    case 0xA3:
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x01)
                                                            {                                                              
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];   // mode
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];   // Data[3]
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[10];  // Data[2]
                                                                aui1_faccmd_ret_val[3] = aui1_cmd_buf[11];  // Data[1]
                                                                aui1_faccmd_ret_val[4] = aui1_cmd_buf[12];  // Data[0]
                                                                
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FACTORY_MODE_TIME;
                                                            }

                                                            break;
                                                        }
                                                    case 0xA9:
                                                        switch(aui1_cmd_buf[7])
                                                        {
                                                        #ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output in Alignment
                                                        //Set Panel Vcom Data(2)
                                                        case 0x01:
                                                            pv_cmd_val = (VOID*)(UINT32)(((UINT32)aui1_cmd_buf[8]<<8) + (UINT32)aui1_cmd_buf[9]);
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_VCOM_DATA;
                                                            break;
                                                        case 0x04:
                                                            aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];   // Seg_x
                                                            aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];   // Hi-byte
                                                            aui1_faccmd_ret_val[2] = aui1_cmd_buf[10];  // Lo-byte
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_PANEL_GAMMA_DATA;
                                                            break;
                                                        #endif
                                                        }
                                                        break;

                                                    case 0xAC: //ke_vizio_20160907 modify
                                                        {
                                                            aui1_faccmd_ret_val[0] = aui1_cmd_buf[10];  //SnLoByte
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_PANEL_ID;
                                                            break;
                                                        }
                                                   case 0xB8:
                                                        {
															if (aui1_cmd_buf[7] == 0x00)
															{
																if (aui1_cmd_buf[8] == 0x02)
																{
																	aui1_faccmd_ret_val[0] = aui1_cmd_buf[9]; //State
																	t_cmd_type = TPV_FACTORY_SET_CMD_SET_PQ_BYPASS;
																}
															}
                                                            break;
                                                        }
                                                    default:
                                                        break;
                                                    }
                                                    break;
                                                    
                                                // FCode03 >>> aui1_cmd_buf[5]==0xE3
                                                case 0xE3: // FCode03
                                                    if(((aui1_cmd_buf[2]-0x80)-5)<2) // Check the length bytes
                                                        break;
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_TO_NVRAM_MULTI_BYTES;
                                                    ui1_eep_bytes = aui1_cmd_buf[6]; // Cmd length (the max length is 8)
                                                    if(ui1_eep_bytes > 8)
                                                    {
                                                        ui1_eep_bytes = 8;
                                                    }
                                                    if(ui1_eep_bytes == 0)
                                                    {
                                                        ui1_eep_bytes = 1;
                                                    }

                                                    aui2_eep_address_high = (UINT16)aui1_cmd_buf[7];
                                                    aui1_eep_address_low = (UINT8)aui1_cmd_buf[8];
                                                    aui4_eep_address = ((aui2_eep_address_high << 8) | aui1_eep_address_low);
                                                    pv_cmd_val = (VOID*) ((aui4_eep_address << 8) | ui1_eep_bytes);

                                                    for(ui2_id = 0; ui2_id < ui1_eep_bytes; ui2_id ++)
                                                    {
                                                        //ke_vizio_20110330 for clean warning.
                                                        if((ui2_id+9) >= CMD_LEN_Maximum)
                                                        {
                                                            break;
                                                        }
                                                        
                                                        aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                    }
                                                    break;

                                                // FCode08 >>> aui1_cmd_buf[5]==0xE8
                                                case 0xE8:   //FCode08 : Write Osd EDID Serial Number
                                                case 0xE9:   //FCode09 : Write Osd EDID Model Name
                                                { //ke_20090107_add  // Denny 2009/01/12 add -start
                                                    if(aui1_cmd_buf[5] == 0xE8){
                                                        t_cmd_type = TPV_FACTORY_SET_CMD_EDID_SERIAL_NUM;
                                                    }
                                                    else if(aui1_cmd_buf[5] == 0xE9){
                                                        t_cmd_type = TPV_FACTORY_SET_CMD_EDID_MODEL_NAME;
                                                    }

                                                    pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[6];  //EBN
                                                    ui1_data_leng = (aui1_cmd_buf[2]&0x0F)-4; // 4+L

                                                    for(ui2_id = 0; ui2_id < ui1_data_leng; ui2_id ++)
                                                    {
                                                        //ke_vizio_20110330 for clean warning.
                                                        if((ui2_id+7) >= CMD_LEN_Maximum)
                                                        {
                                                            break;
                                                        }
                                                        
                                                        aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+7];
                                                    }
                                                    break;
                                                } //ke_20090107_add  // Denny 2009/01/12 add -end

                                                // FCode0A >>> aui1_cmd_buf[5]==0xEA
                                                // Write HDCP Data
                                                case 0xEA: // FCode0A
                                                    t_cmd_type = TPV_FACTORY_SET_CMD_SAVE_HDCP_DATA;
                                                    ui1_hdcp_block_size = (UINT8)(UINT16)aui1_cmd_buf[6];
                                                    pv_cmd_val = (VOID*) ((UINT32)aui1_cmd_buf[7]);
                                                    for(ui2_id = 0; ui2_id < ui1_hdcp_block_size; ui2_id ++)
                                                    {
                                                        //ke_vizio_20110330 for clean warning.
                                                        if((ui2_id+8) >= CMD_LEN_Maximum)
                                                        {
                                                            break;
                                                        }
                                                        
                                                        aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+8];
                                                    }
                                                    break;

                                                //FCode10 >>> aui1_cmd_buf[5]==0xF0
                                                case 0xF0: //FCode10 : W
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        case 0x01:
                                                            if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8]==0x06)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_WIRED_ETHERNET_MAC_ADDR;
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }

                                                            if(aui1_cmd_buf[7] == 0x02 && aui1_cmd_buf[8]==0x04)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_WIRED_ETHERNET_IPV4_ADDR;
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }

                                                            if(aui1_cmd_buf[7] == 0x03 && (aui1_cmd_buf[2] == (aui1_cmd_buf[8] + 0x86)))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[9];
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[10];
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[11];
                                                                aui1_faccmd_ret_val[3] = aui1_cmd_buf[12];
                                                            }

                                                            //ke_vizio_20131119 add
                                                            if(aui1_cmd_buf[7] == 0x05)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_TEST_WIRED_ETHERNET_PORT_V2;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // SndNr
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // Data1
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[10]; // Data2
                                                                aui1_faccmd_ret_val[3] = aui1_cmd_buf[11]; // Data3
                                                                aui1_faccmd_ret_val[4] = aui1_cmd_buf[12]; // Data4
                                                                aui1_faccmd_ret_val[5] = aui1_cmd_buf[13]; // Data5
                                                                aui1_faccmd_ret_val[6] = aui1_cmd_buf[14]; // Data6
                                                                aui1_faccmd_ret_val[7] = aui1_cmd_buf[15]; // Data7
                                                            }
                                                            break;
                                                            
                                                        case 0x02:
                                                            if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8]==0x06)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_WIFI_MAC_ADDR;
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }

                                                            if(aui1_cmd_buf[7] == 0x02 && aui1_cmd_buf[8]==0x04)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_WIFI_IPV4_ADDR;
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }

                                                            if((aui1_cmd_buf[7] == 0x03) && (aui1_cmd_buf[2] == (aui1_cmd_buf[8] + 0x86)))
                                                            {
                                                                UINT16 ui2_byte_cnt = 0;
                                                                if(aui1_cmd_buf[8]>6)
                                                                    ui2_byte_cnt = aui1_cmd_buf[8];
                                                                else 
                                                                    return;
                                                                // MTK platform has receive limit bytes. 
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_TEST_WIFI_PORT;
                                                                aui1_faccmd_ret_val[0] = (UINT8)ui2_byte_cnt - 6;
                                                                for(ui2_id = 1; ui2_id <= ui2_byte_cnt; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+8];
                                                                }
                                                            }

                                                            //ke_vizio_20131113 add
                                                            if((aui1_cmd_buf[7] == 0x04) && (aui1_cmd_buf[2] == (aui1_cmd_buf[9] + 0x87)))
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_TEST_WIFI_PORT_V2;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // TimeLimit
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // n
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[9]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+10) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id + 2] = aui1_cmd_buf[ui2_id + 10];
                                                                }
                                                            }
                                                            break;
                                                            
                                                        case 0x03:
                                                            if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8]==0x06)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_BLUETOOTH_MAC_ADDR;
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }
                                                            if(aui1_cmd_buf[7] == 0x02) // Bluetooth Test V2 for 5691/5695
                                                            {
                                                                UINT16 ui2_byte_cnt = 0;
                                                                
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FAC_BTUETOOTH_V2_TEST;

                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];

                                                                ui2_byte_cnt = aui1_cmd_buf[9];

                                                                if (ui2_byte_cnt == 0)
                                                                    ui2_byte_cnt = 6; // error avoid    
                                                                
                                                                aui1_faccmd_ret_val[1] = ui2_byte_cnt;

                                                                for(ui2_id = 0; ui2_id < ui2_byte_cnt ; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id+2] = aui1_cmd_buf[ui2_id+10];
                                                                }
                                                            }
                                                            break;

                                                        case 0x04:
                                                            if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8]==0x06)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_TRANS_BT_MAC_ADDR_TO_TV;
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }
                                                            if(aui1_cmd_buf[7] == 0x02) // Bluetooth Test V3 for 5691/5695
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FAC_BTUETOOTH_V3_TEST;

                                                                for(ui2_id = 0; ui2_id < 7; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    //if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    //{
                                                                    //    break;
                                                                    //}
                                                                    
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+8];
                                                                }
                                                            }
                                                            break;

                                                    #ifdef TPV_2K19_DFM // Ben 20181221
                                                        case 0x0D:
                                                            if(aui1_cmd_buf[7] == 0x03 && aui1_cmd_buf[8]==0x01)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_UPLOAD_CHANNEL_MAP_FROM_USB_DEVICE;
                                                                aui1_faccmd_ret_val[0]=aui1_cmd_buf[9];  //portID
                                                            }
                                                            break;
                                                    #endif

														case 0x11:
	                                                        switch(aui1_cmd_buf[7])
	                                                        {
	                                                        case 0x03:
	                                                            if((aui1_cmd_buf[8]==0x01) && (aui1_cmd_buf[2]==0x87))
	                                                            {
	                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FAC_SET_VOL;
	                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[9];
	                                                            }
	                                                        }
	                                                        break;

	                                                    case 0x16:
	                                                        if(aui1_cmd_buf[7] == 0x02)
	                                                        {
	                                                            if(aui1_cmd_buf[8] == 0x06)
	                                                            {
	                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FAC_SEL_TV_CH;
	                                                                for(ui2_id = 0; ui2_id < 6; ui2_id ++)
	                                                                {
	                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
	                                                                }
	                                                            }
	                                                        }
	                                                        break;

                                                        case 0x1A:  //ke_vizio_20130705 add
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x02)
	                                                        {
	                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE;
	                                                            aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // n : length of Gamma Data
	                                                            aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // Gamma ID
	                                                            aui1_faccmd_ret_val[2] = aui1_cmd_buf[10]; // Color Temp
	                                                            aui1_faccmd_ret_val[3] = aui1_cmd_buf[11]; // Color Channel
	                                                            aui1_faccmd_ret_val[4] = aui1_cmd_buf[12]; // Start No

	                                                            for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    aui1_faccmd_ret_val[5 + 2*ui2_id] = aui1_cmd_buf[13 + 2*ui2_id];   // HiByte
                                                                    aui1_faccmd_ret_val[5 + 2*ui2_id + 1] = aui1_cmd_buf[13 + 2*ui2_id + 1];  //LoByte
                                                                }
                                                            }
                                                            break;
                                                        }

                                                        case 0x1B:
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x01)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY_START;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // TotalBlockNo
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // Which_Key
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[10]; // DataLen HiByte
                                                                aui1_faccmd_ret_val[3] = aui1_cmd_buf[11]; // DataLen LoByte
                                                                aui1_faccmd_ret_val[4] = aui1_cmd_buf[12]; // CRC HiByte
                                                                aui1_faccmd_ret_val[5] = aui1_cmd_buf[13]; // CRC LoByte
                                                            }
                                                            else if(aui1_cmd_buf[7] == 0x02)
                                                            {
                                                                UINT16 ui2_data_len = 0;
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_WRITE_SECURITY_KEY;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // DBS_Hi
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // DBS_Li
                                                                aui1_faccmd_ret_val[2] = aui1_cmd_buf[10]; // CurrBlockNo

                                                                ui2_data_len = (UINT16)(aui1_cmd_buf[8]<<8) + aui1_cmd_buf[9];
                                                                for(ui2_id = 0; ui2_id < ui2_data_len; ui2_id++)
                                                                {
                                                                    aui1_faccmd_ret_val[3 + ui2_id] = aui1_cmd_buf[11 + ui2_id];   // Data
                                                                }
                                                            }

                                                            break;
                                                        }
                                                #ifdef TPV_2K19_DFM // Ben 20181221
                                                        case 0x1C:
                                                        {
                                                            if(aui1_cmd_buf[7] == 0x02)
                                                            {
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_FACTORY_CHECK_FLAG;
                                                                aui1_faccmd_ret_val[0] = aui1_cmd_buf[8];  // Function_Type
                                                                aui1_faccmd_ret_val[1] = aui1_cmd_buf[9];  // status
                                                            }
                                                            break;
                                                        }

                                                        case 0x1D:
                                                        {
                                                            // aui1_cmd_buf[7] ------- n: gamma point num, Def:17, Max:20 (reserved)
                                                            // aui1_cmd_buf[8] ------- ColorTemp, 0:cool 1:normal 2: warm
                                                            // aui1_cmd_buf[9:42] ----- R data, 17 point * 2 hi/lo Bytes = 34
                                                            // aui1_cmd_buf[43:76] ----- G data, 17 point * 2 hi/lo Bytes = 34
                                                            // aui1_cmd_buf[77:110] ----B data, 17 point * 2 hi/lo Bytes = 34
                                                            
                                                            t_cmd_type = TPV_FACTORY_SET_CMD_SET_GAMMA_TABLE_TO_STORAGE_NEW;
                                                            
                                                            aui1_faccmd_ret_val[0] = aui1_cmd_buf[7];  // n 
                                                            aui1_faccmd_ret_val[1] = aui1_cmd_buf[8];  // ColorTemp

                                                            for(ui2_id = 0; ui2_id < 51; ui2_id++) //RGB data, 17 * 3 = 51
                                                            {
                                                                aui1_faccmd_ret_val[2 + 2*ui2_id] = aui1_cmd_buf[9 + 2*ui2_id];   // HiByte
                                                                aui1_faccmd_ret_val[2 + 2*ui2_id + 1] = aui1_cmd_buf[9 + 2*ui2_id + 1];  //LoByte
                                                            }
                                                            
                                                            break;
                                                        }
                                                #endif

                                                        default:
                                                            break;
                                                    }
                                                    break;

                                                //FCode11 >>> aui1_cmd_buf[5]==0xF1
                                                case 0xF1: //FCode11 : W 
                                                    switch(aui1_cmd_buf[6])
                                                    {
                                                        case 0x05:
                                                            if(aui1_cmd_buf[7] == 0x04 && (aui1_cmd_buf[2] == (aui1_cmd_buf[8] + 0x86)))
                                                            {
                                                                // MTK platform has receive limit bytes. 
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_ULPK_KEY;
                                                                for(ui2_id = 0; ui2_id < aui1_cmd_buf[8]; ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }

                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }
                                                            if(aui1_cmd_buf[7] == 0x03 && (aui1_cmd_buf[2] == (aui1_cmd_buf[8] + 0x88))) // Ben 2012/10/25 added for POTK.
                                                            {
                                                                // MTK platform has receive limit bytes. 
                                                                t_cmd_type = TPV_FACTORY_SET_CMD_SET_POTK_KEY;
                                                                for(ui2_id = 0; ui2_id < (aui1_cmd_buf[8] + 2); ui2_id++)
                                                                {
                                                                    //ke_vizio_20110330 for clean warning.
                                                                    if((ui2_id+9) >= CMD_LEN_Maximum)
                                                                    {
                                                                        break;
                                                                    }
                                                                    
                                                                    //aui1_faccmd_ret_val[0] = AddHi
                                                                    //aui1_faccmd_ret_val[1] = AddLo
                                                                    aui1_faccmd_ret_val[ui2_id] = aui1_cmd_buf[ui2_id+9];
                                                                }
                                                            }	
                                                            break;
                                                        default:
                                                            break;
                                                    }
                                                    break;
                                                default:
                                                    break;
                                            }      // End of switch (aui1_cmd_buf[5])
                                    }          // End of switch (aui1_cmd_buf[4])
                                    break;
								default:
									break;
                            }              // End of switch (aui1_cmd_buf[3])
                            break; // End of Packet length != 6
                    } // End of switch(aui1_cmd_buf[2])
                    break;
                default:
                    break;
            } // End of switch(aui1_cmd_buf[1])
            break;
        default:
            break;
    }


    if (b_factory_mode_started == FALSE)
    {
        b_factory_mode_started = TRUE;
#if 0		//kyo_20091006 mark for Alignment inactive issue
        /* Backup adaptive luma setting */
        a_factory_get_cmd(TPV_FACTORY_GET_CMD_SET_ADAPTIVE_LUMA,
                          (VOID*) &i2_adaptive_luma,
                          sizeof(i2_adaptive_luma));
#endif
        /* Disable adaptive luma setting */
        i4_ret = a_TPV_factory_set_cmd(TPV_FACTORY_SET_CMD_SET_ADAPTIVE_LUMA,
                          0,
                          NULL,
                          NULL);
        TPV_LOG_ON_FAIL(i4_ret);
    }

    if (b_do_common_set_cmd)
    {
        pv_tag = (VOID*) ((t_cmd_type << 24) |
                          (aui1_cmd_buf[1] ^
                           aui1_cmd_buf[2] ^
                           aui1_cmd_buf[3] ^
                           aui1_cmd_buf[4] ^
                           aui1_cmd_buf[5]
                           ));

        if (a_TPV_factory_set_cmd(t_cmd_type,
                              pv_cmd_val,
                              _fact_parser_set_cmd_nfy,
                              pv_tag ) != FACTORYR_OK)
        {
            /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
            DBG_LOG_PRINT(("<fact_parser> Set command to factory daemon fails\n"));
        }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _fact_parser_set_cmd_nfy
 *
 * Description: Notification function called from the factory daemon.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _fact_parser_set_cmd_nfy(
    VOID*               pv_tag,
    VOID*               pv_val)
{
    UINT8       ui1_i;
    UINT8       aui1_ret_buf[CMD_LEN_Maximum] ={0};
    IOM_UART_T  t_iom_uart;

    c_memset( &t_iom_uart, 0, sizeof(IOM_UART_T));  //ke_vizio_20110330 for clean warning.
    
    if (b_cli_simulate == FALSE)
    {
        c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

        if((aui1_cmd_buf[0]==0x6E) && (aui1_cmd_buf[1]==0x51))
        {
            TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);
        }
        else if(aui1_cmd_buf[0]!=0x58)
        {
            TPVComm_TwoAckByteNotSupportMsgGet(aui1_ret_buf);
            c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
            return;
        }
        //ke_vizio_20110330 for clean warning.
        if(ui1_cmd_length > CMD_LEN_Maximum)
        {
            DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
            return;
        }
        
        // 2K8 Factory Alignment Cmd
        if(aui1_cmd_buf[0] == 0x58)
        {
            for(ui1_i = 0; ui1_i < ui1_cmd_length; ui1_i++)
                aui1_ret_buf[ui1_i] = aui1_cmd_buf[ui1_i];
            t_iom_uart.pui1_data = aui1_ret_buf;
            t_iom_uart.z_len     = ui1_cmd_length;

            if (c_iom_output(h_iom_uart, &t_iom_uart) != IOMR_OK)
            {
                /*DBG_ERROR(("<fact_parser> Output response to UART fails\n"));*/
                DBG_LOG_PRINT(("<fact_parser> Output response to UART fails\n"));
            }

            switch(aui1_cmd_buf[1])
            {
                case 0xD1: // Read EEprom data by one byte
                    aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                    t_iom_uart.pui1_data = aui1_ret_buf;
                    t_iom_uart.z_len = 1;
                    c_iom_output(h_iom_uart, &t_iom_uart);					
                    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                    break;
                case 0xE1: // Read EEPROM data by multi-bytes
                    for(ui1_i = 0; ui1_i < aui1_cmd_buf[4]; ui1_i++)
                    {
                        //ke_vizio_20110330 for clean warning.
                        if((ui1_i+1) >= CMD_LEN_Maximum)
                        {
                            DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
                            return;
                        }
                    
                        aui1_ret_buf[ui1_i] = aui1_faccmd_ret_val[ui1_i+1];
                    }
                    t_iom_uart.pui1_data = aui1_ret_buf;
                    t_iom_uart.z_len = aui1_cmd_buf[4];
                    c_iom_output(h_iom_uart, &t_iom_uart);
                    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                    break;
                default:
                    break;
            }

        }
        // 2k9 Factory Alignment Cmd
        else if(aui1_cmd_buf[0] == 0x6E)
        {
            switch(aui1_cmd_buf[2]) // Cmd length
            {
            case 0x84:
                switch(aui1_cmd_buf[3])
                {
                // Read commands
                case 0x01:
                    switch(aui1_cmd_buf[4])
                    {
                        case 0x62: // Read volume
                            aui1_ret_buf[2] = 0x01;     // DataLen = 1
                            aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                            t_iom_uart.pui1_data = aui1_ret_buf;
                            t_iom_uart.z_len = 4;
                            c_iom_output(h_iom_uart, &t_iom_uart);							
                            c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                            break;
                        default:
                            break;
                    }
                    break;
                // Write commands
                case 0x03:
                    {
                        UINT8 ui1_Len_tmp1 = 3;
                        aui1_ret_buf[2] = 0x00;     // DataLen = 0

                        t_iom_uart.pui1_data = aui1_ret_buf;
                        t_iom_uart.z_len = ui1_Len_tmp1;
                    }
                    c_iom_output(h_iom_uart, &t_iom_uart);					
                    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                    break;
                default:
                    break;
                }
                break;

            default:
                switch (aui1_cmd_buf[3])
                {
                // Read commands
                case 0x01:
                    switch(aui1_cmd_buf[5])
                    {
                        case 0x16: // R Gain (Color Temp)
                        case 0x18: // G Gain (Color Temp)
                        case 0x1A: // B Gain (Color Temp)
                        case 0x6C: // R Offset (Color Temp)
                        case 0x6E: // G Offset (Color Temp)
                        case 0x70: // B Offset (Color Temp)
#if 0
                            {
                                UINT8 ui1_tmp = aui1_faccmd_ret_val[0];
                                UINT8 ui1_2complement;
                                // Positive numbers
                                if(ui1_tmp <= 25) //Denny 2009/03/06 //20=>25
                                {
                                    ui1_tmp = 128 + ui1_tmp;
                                }
                                // Negative numbers
                                else if(ui1_tmp >= 231 && ui1_tmp <= 255) //Denny 2009/03/06 //236=>231
                                {
                                    ui1_2complement = (~ui1_tmp)+1;
                                    ui1_tmp = 128 - ui1_2complement;
                                }
                                // Larger than +20
                                else if(ui1_tmp > 25 && ui1_tmp < 128) //Denny 2009/03/06 //20=>25
                                {
                                    ui1_tmp = 153; //Denny 2009/03/06 //148=>153
                                }
                                // Smaller than -20
                                else if(ui1_tmp < 231)  //Denny 2009/03/06 //236=>231
                                {
                                    ui1_tmp = 103; //Denny 2009/03/06 //108=>103
                                }
                                aui1_faccmd_ret_val[0] = ui1_tmp;
                            }
#endif
                        case 0x10: // Brightness
                        case 0x12: // Contrast
                            aui1_ret_buf[2] = 0x01;     // DataLen = 1
                            aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                            t_iom_uart.pui1_data = aui1_ret_buf;
                            t_iom_uart.z_len = 4;
                            c_iom_output(h_iom_uart, &t_iom_uart);							
                            c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                            break;

                        // FCode01
                        case 0xE1:
                            switch(aui1_cmd_buf[6])
                            {
                            	case 0xA4:	//kyo_20111226
                                    switch(aui1_cmd_buf[7])
                                    {
                                    case 0x0B: //TPV_FACTORY_SET_CMD_READ_HDCP_LEN
                                        aui1_ret_buf[2] = 2;
                                        aui1_ret_buf[3] = aui1_faccmd_ret_val[0]; // hi byte
                                        aui1_ret_buf[4] = aui1_faccmd_ret_val[1]; // lo byte
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        t_iom_uart.z_len = aui1_ret_buf[2] + 3;
                                        c_iom_output(h_iom_uart, &t_iom_uart);										
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear
                                        break;
                                        
                                    case 0x1D: // TPV_FACTORY_SET_CMD_GET_LIGHT_SENSOR
										aui1_ret_buf[2] = 0x02; 	// DataLen = 2
										aui1_ret_buf[3] = aui1_faccmd_ret_val[0];  // hi byte
										aui1_ret_buf[4] = aui1_faccmd_ret_val[1];  // lo byte
										t_iom_uart.pui1_data = aui1_ret_buf;
										t_iom_uart.z_len = 5;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                        break;
                                        
                                    default:
                                        break;
                                    }
                                    break;
                                case 0xA7: //ke_vizio_20130716 add
                                {
                                    UINT8 ui_idx = 0;
                                    aui1_ret_buf[2] = aui1_faccmd_ret_val[0];

                                    for(ui_idx = 0; ui_idx < aui1_faccmd_ret_val[0]; ui_idx++)
                                    {
                                        aui1_ret_buf[3+ui_idx] = aui1_faccmd_ret_val[1 + ui_idx];
                                    }
                                    
                                    t_iom_uart.pui1_data = aui1_ret_buf;
                                    t_iom_uart.z_len = aui1_ret_buf[2] + 3;
                                    c_iom_output(h_iom_uart, &t_iom_uart);										
									c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear
                                    break;
                                }
#ifdef FACTORY_VCOM_TEST_PATTERN//Denny 2009/12/01 add for Test pattern output in Alignment
                                case 0xA9: //VCom related
                                    switch(aui1_cmd_buf[7])
                                    {
                                    case 0x00:
                                        switch(aui1_cmd_buf[8])
                                        {
                                            // Get VCom Data //TPV_FACTORY_SET_CMD_GET_VCOM_REGISTER
                                            case 0x00:
                                                aui1_ret_buf[2] = 0x02;
                                                aui1_ret_buf[3] = aui1_faccmd_ret_val[0]; // VCom - High byte
                                                aui1_ret_buf[4] = aui1_faccmd_ret_val[1]; // VCom - Low byte
                                                t_iom_uart.pui1_data = aui1_ret_buf;
                                                t_iom_uart.z_len = 5;
                                                c_iom_output(h_iom_uart, &t_iom_uart);												
                                                c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                                break;
                                        }
                                        break;
                                    case 0x04:
                                        // Get Gamma Data //TPV_FACTORY_SET_CMD_GET_PANEL_GAMMA_DATA
                                        if(aui1_cmd_buf[8])
                                        {// Read one of the value from gamma1 to gamma8
                                            aui1_ret_buf[2] = 3;
                                            aui1_ret_buf[3] = aui1_cmd_buf[8];          // Seg_y, ie the index number.
                                            aui1_ret_buf[4] = aui1_faccmd_ret_val[1];   // Gamma - High byte
                                            aui1_ret_buf[5] = aui1_faccmd_ret_val[2];   // Gamma - Low byte
                                            t_iom_uart.z_len = 6;
                                        }
                                        else
                                        {// Read all the values from gamma1 to gamma8
                                            UINT8   ui1_i;
                                            aui1_ret_buf[2] = 17;
                                            aui1_ret_buf[3] = 0;                        // Seg_y, ie the index number.
                                            for(ui1_i=0; ui1_i<8; ui1_i++)
                                            {
                                                aui1_ret_buf[(2*ui1_i)+4] = aui1_faccmd_ret_val[(2*ui1_i)+1]; // Gamma - High byte
                                                aui1_ret_buf[(2*ui1_i)+5] = aui1_faccmd_ret_val[(2*ui1_i)+2]; // Gamma - Low byte
                                            }
                                            t_iom_uart.z_len = 20;
                                        }
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        c_iom_output(h_iom_uart, &t_iom_uart);										
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear
                                    }
                                    break;

#endif
                                case 0xAC:  //ke_vizio_20130708 add
                                    if((aui1_cmd_buf[7] == 0) && (aui1_cmd_buf[8] == 0))
                                    {
                                        //TPV_FACTORY_SET_CMD_GET_PANEL_ID
                                        aui1_ret_buf[2] = 0x04;     // DataLen = 4
                                        aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                                        aui1_ret_buf[4] = aui1_faccmd_ret_val[1];
                                        aui1_ret_buf[5] = aui1_faccmd_ret_val[2];
                                        aui1_ret_buf[6] = aui1_faccmd_ret_val[3];
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        t_iom_uart.z_len = 7;
                                        c_iom_output(h_iom_uart, &t_iom_uart);									
                                        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                    }
                                    break;
                                case 0xB8:  // TPV_FACTORY_SET_CMD_GET_PQ_BYPASS
                                    if((aui1_cmd_buf[7] == 0) && (aui1_cmd_buf[8] == 2))
                                    {
										aui1_ret_buf[2] = 0x01; 	// DataLen = 1
										aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
										t_iom_uart.pui1_data = aui1_ret_buf;
										t_iom_uart.z_len = 4;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                    }
                                    break;									
                                // Read HDCP CRC
                                case 0xE2:
                                    aui1_ret_buf[2] = 0x02;     // DataLen = 1
                                    aui1_ret_buf[3] = aui1_faccmd_ret_val[0]; // HDCP CRC - High byte
                                    aui1_ret_buf[4] = aui1_faccmd_ret_val[1]; // HDCP CRC - Low byte
                                    t_iom_uart.pui1_data = aui1_ret_buf;
                                    t_iom_uart.z_len = 5;
                                    c_iom_output(h_iom_uart, &t_iom_uart);									
                                    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                    break;					
                                
                               
								case 0xE3:
								// TPV_FACTORY_SET_CMD_READ_HDCP_KSV 
								// TPV_FACTORY_SET_CMD_READ_HDCP_2_X_RECEIVE_ID

									aui1_ret_buf[2] = 0x05; 	// DataLen = 1

                                    if (aui1_cmd_buf[7] == 0x00)
                                    {                           
                                        aui1_ret_buf[3] = aui1_faccmd_ret_val[0]; // KSV
                                        aui1_ret_buf[4] = aui1_faccmd_ret_val[1]; // KSV
                                        aui1_ret_buf[5] = aui1_faccmd_ret_val[2]; // KSV
                                        aui1_ret_buf[6] = aui1_faccmd_ret_val[3]; // KSV
                                        aui1_ret_buf[7] = aui1_faccmd_ret_val[4]; // KSV
                                    }
                                    if (aui1_cmd_buf[7] == 0x01)
                                    {                           
                                        aui1_ret_buf[3] = aui1_faccmd_ret_val[0]; // Receiver ID
                                        aui1_ret_buf[4] = aui1_faccmd_ret_val[1]; // Receiver ID
                                        aui1_ret_buf[5] = aui1_faccmd_ret_val[2]; //  Receiver ID
                                        aui1_ret_buf[6] = aui1_faccmd_ret_val[3]; // Receiver ID
                                        aui1_ret_buf[7] = aui1_faccmd_ret_val[4]; // Receiver ID
                                    }
                                    
                                    t_iom_uart.pui1_data = aui1_ret_buf;
                                    t_iom_uart.z_len = 8;
                                    c_iom_output(h_iom_uart, &t_iom_uart);
                                    break;	//<TPV>Stone_20120529 end                              								
								
								case 0xE1:  //Frankie_20160510
									//TPV_FACTORY_SET_CMD_SET_PANEL_ID
									//UINT8 ui1_Len_tmp1 = 4;
									aui1_ret_buf[2] = 0x01;     // DataLen = 1
									aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
									t_iom_uart.pui1_data = aui1_ret_buf;
									t_iom_uart.z_len = 4; //ui1_Len_tmp1;
									c_iom_output(h_iom_uart, &t_iom_uart);
									c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear					
									break;	   
								
                                default:
                                    break;
                            }
                            break;


                        // FCode02
                        case 0xE2:
                            aui1_ret_buf[2] = 0x01;     // DataLen = 1
                            aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                            t_iom_uart.pui1_data = aui1_ret_buf;
                            t_iom_uart.z_len = 4;
                            c_iom_output(h_iom_uart, &t_iom_uart);
							c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                            break;

                        // FCode03
                        // Read NVRAM with Multi-bytes
                        case 0xE3:
                            aui1_ret_buf[2] = aui1_faccmd_ret_val[0];     // DataLen

                            for(ui1_i = 1; ui1_i <= aui1_faccmd_ret_val[0]; ui1_i++)
                            {
                                //ke_vizio_20110330 for clean warning.
                                if((ui1_i+2) >= CMD_LEN_Maximum)
                                {
                                    DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
                                    return;
                                }
                                
                                aui1_ret_buf[ui1_i+2] = aui1_faccmd_ret_val[ui1_i];
                            }

                            t_iom_uart.pui1_data = aui1_ret_buf;
                            t_iom_uart.z_len = aui1_faccmd_ret_val[0] + 3;
                            c_iom_output(h_iom_uart, &t_iom_uart);
							c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                            break;

                        // FCode04 //Denny 2009/02/27
                        case 0xE4:
                            switch(aui1_cmd_buf[6])
                            {
//Denny 2009/03/17 add-start
                            // Check if no signal or not
                            case 0x07:
                                aui1_ret_buf[2] = 0x01;     // DataLen = 1
                                if(aui1_faccmd_ret_val[0] == 1)
                                    aui1_ret_buf[3] = 0; // No signal inputed
                                else if(aui1_faccmd_ret_val[0] == 2)
                                    aui1_ret_buf[3] = 1; // Signal inputed
                                else
                                    return;
                                t_iom_uart.pui1_data = aui1_ret_buf;
                                t_iom_uart.z_len = 4;
                                c_iom_output(h_iom_uart, &t_iom_uart);
								c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                break;
//Denny 2009/03/17 add-end
                            // Read S/W Version & Model name
                            case 0x13:
                                aui1_ret_buf[2] = ui1_data_leng;     // DataLen

                                for(ui1_i = 0; ui1_i < ui1_data_leng; ui1_i++)
                                {
                                    //ke_vizio_20110330 for clean warning.
                                    if((ui1_i+3) >= CMD_LEN_Maximum)
                                    {
                                        DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
                                        return;
                                    }
                                
                                    aui1_ret_buf[ui1_i+3] = aui1_faccmd_ret_val[ui1_i];
                                }

                                t_iom_uart.pui1_data = aui1_ret_buf;
                                t_iom_uart.z_len = ui1_data_leng + 3;
                                c_iom_output(h_iom_uart, &t_iom_uart);
								c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                break;
                            default:
                                break;
                            }
                            break;

                        //FCode08 :  Read Osd Edid Serial Number
                        //FCode09 :  Read Osd Edid Model Name
                        case 0xE8: //TPV_FACTORY_READ_CMD_EDID_SERIAL_NUM
                        case 0xE9: //TPV_FACTORY_READ_CMD_EDID_MODEL_NAME
                        { //ke_20090107_add  // Denny 2009/01/12 add -start
                            aui1_ret_buf[2] = ui1_data_leng;     // DataLen

                            for(ui1_i = 0; ui1_i < ui1_data_leng; ui1_i++)
                            {
                                //ke_vizio_20110330 for clean warning.
                                if((ui1_i+3) >= CMD_LEN_Maximum)
                                {
                                    DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
                                    return;
                                }

                                aui1_ret_buf[ui1_i+3] = aui1_faccmd_ret_val[ui1_i];
                            }

                            t_iom_uart.pui1_data = aui1_ret_buf;
                            t_iom_uart.z_len = ui1_data_leng + 3;
                            c_iom_output(h_iom_uart, &t_iom_uart);
                            c_memset(aui1_faccmd_ret_val, 0x00, CMD_LEN_Maximum);  // clear //Denny 2011/03/22 add
                            break;
                        } //ke_20090107_add  // Denny 2009/01/12 add -end

                        // FCode0A
                        // Read HDCP Data
                        case 0xEA:
                            aui1_ret_buf[2] = aui1_faccmd_ret_val[0];     // DataLen

                            for(ui1_i = 1; ui1_i <= aui1_faccmd_ret_val[0]; ui1_i++)
                            {
                                //ke_vizio_20110330 for clean warning.
                                if((ui1_i+2) >= CMD_LEN_Maximum)
                                {
                                    DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
                                    return;
                                }
                                aui1_ret_buf[ui1_i+2] = aui1_faccmd_ret_val[ui1_i];
                            }

                            t_iom_uart.pui1_data = aui1_ret_buf;
                            t_iom_uart.z_len = aui1_faccmd_ret_val[0] + 3;
                            c_iom_output(h_iom_uart, &t_iom_uart);
							c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                            break;

                        case 0xF0:  //FCode10 : R
                            switch(aui1_cmd_buf[6])
                            {
                                case 0x01:
                                case 0x02:
                                case 0x03:
                                    if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8] == 0x00)
                                    {
                                        //c_dbg_stmt("!!!!%s 0x01 0x00\n", __func__); 
                                        #if 1
                                        aui1_ret_buf[2] = 6;

                                        for(ui1_i = 0; ui1_i < 6; ui1_i++)
                                        {
                                            //aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                                            aui1_ret_buf[ui1_i + 3] = aui1_faccmd_ret_val[ui1_i];
                                        }
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        t_iom_uart.z_len = 9;
                                        c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                        #endif
                                    }
                                    /*
                                    if(aui1_cmd_buf[7] == 0x01 && aui1_cmd_buf[8] == 0x02) //TPV_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI
                                    {
                                        //c_dbg_stmt("!!!!%s 0x01 0x00\n", __func__); 
                                        #if 1
                                        aui1_ret_buf[2] = 2;

                                        for(ui1_i = 0; ui1_i < 2; ui1_i++)
                                        {
                                            //aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                                            aui1_ret_buf[ui1_i + 3] = aui1_faccmd_ret_val[ui1_i];
                                        }
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        t_iom_uart.z_len = 5;
                                        c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                        #endif
                                    }									
									*/
                                    if(aui1_cmd_buf[7] == 0x02 && aui1_cmd_buf[8] == 0x00)
                                    {
                                        //c_dbg_stmt("!!!!%s 0x02 0x00\n", __func__);
                                        #if 1
                                        aui1_ret_buf[2] = 4;

                                        for(ui1_i = 0; ui1_i < 4; ui1_i++)
                                        {
                                            //aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                                            aui1_ret_buf[ui1_i + 3] = aui1_faccmd_ret_val[ui1_i];
                                        }
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        t_iom_uart.z_len = 7;
                                        c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                        #endif
                                    }

								#ifdef APP_TPV_DFT_WIFI_AUTO_DETECTION  //ke_vizio_20170523
                                    if(aui1_cmd_buf[7] == 0x06 && aui1_cmd_buf[8] == 0x00) //ke_vizio_20170523
                                    {
                                        DBG_INFO(("!!!! TPV_FACTORY_SET_CMD_GET_WIFI_AUTO_DETECTION_STATUS\n"));

                                        aui1_ret_buf[2] = aui1_faccmd_ret_val[0];
                                        aui1_ret_buf[3] = aui1_faccmd_ret_val[1];
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        t_iom_uart.z_len = 4;
                                        c_iom_output(h_iom_uart, &t_iom_uart);
                                        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                    }
                                    break;
								#endif
                                    
								case 0x10:	//kyo_20111226-start
									if((aui1_cmd_buf[7]==0x03) //TPV_FACTORY_SET_CMD_FAC_GET_USB_ATTACH
									 ||(aui1_cmd_buf[7]==0x04) //TPV_FACTORY_SET_CMD_FAC_GET_USB_OVERCURRENT
									 )
									{
									#if 0
										aui1_ret_buf[2] = 0x01; 	// DataLen = 1
										aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
										t_iom_uart.pui1_data = aui1_ret_buf;
										t_iom_uart.z_len = 4;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
									#else	//sam 120816
	                                    aui1_ret_buf[2] = 0x02;     // DataLen = 1
	                                    aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
										aui1_ret_buf[4] = aui1_faccmd_ret_val[1];
	                                    t_iom_uart.pui1_data = aui1_ret_buf;
	                                    t_iom_uart.z_len = 5;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
									#endif
									}
									break;

								case 0x11:
									if(aui1_cmd_buf[7]==0x03) // TPV_FACTORY_SET_CMD_FAC_GET_VOL
									{
										aui1_ret_buf[2] = 0x01; 	// DataLen = 1
										aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
										t_iom_uart.pui1_data = aui1_ret_buf;
										t_iom_uart.z_len = 4;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
									}
									break;
								
								case 0x14:
									if(aui1_cmd_buf[7]==0x02) 
									{
									    if(aui1_cmd_buf[8]==0x02) //TPV_FACTORY_SET_CMD_READ_KEYPAD_STATUS
										{ //Denny 2014/02/17 add
											aui1_ret_buf[2] = 0x01; 	// DataLen = 1
											aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
											t_iom_uart.pui1_data = aui1_ret_buf;
											t_iom_uart.z_len = 4;
											c_iom_output(h_iom_uart, &t_iom_uart);
											c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
										}	
									}
									break;									
									
							#if 1	//sam 121129
								case 0x17:	
									if(aui1_cmd_buf[7]==0x03) //TPV_FACTORY_SET_CMD_FAC_READ_EDID
									{ //Denny 2011/12/26 add
										aui1_ret_buf[2] = aui1_faccmd_ret_val[0];	  // DataLen
										for(ui1_i = 1; ui1_i <= aui1_ret_buf[2]; ui1_i++)
										{
											aui1_ret_buf[ui1_i+2] = aui1_faccmd_ret_val[ui1_i];
										}
									
										t_iom_uart.pui1_data = aui1_ret_buf;
										t_iom_uart.z_len = aui1_ret_buf[2]+3;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);
									}
									break;
							#endif		
								case 0x18:
									if((aui1_cmd_buf[7]==0x03) // TPV_FACTORY_SET_CMD_FAC_NVM_VER
									|| (aui1_cmd_buf[7]==0x04) // TPV_FACTORY_SET_CMD_FAC_MODEL_NAME
									|| (aui1_cmd_buf[7]==0x06) // TPV_FACTORY_SET_CMD_FAC_MCU_VER
									|| (aui1_cmd_buf[7]==0x07) // TPV_FACTORY_SET_CMD_FAC_AQ_VER
									|| (aui1_cmd_buf[7]==0x08) // TPV_FACTORY_SET_CMD_FAC_PQ_VER
									|| (aui1_cmd_buf[7]==0x12) // TPV_FACTORY_SET_CMD_FAC_PQ_VER
										 )
									{ 
										aui1_ret_buf[2] = ui1_data_leng;	 // DataLen
									
										for(ui1_i = 0; ui1_i < ui1_data_leng; ui1_i++)
										{
											aui1_ret_buf[ui1_i+3] = aui1_faccmd_ret_val[ui1_i];
										}
									
										t_iom_uart.pui1_data = aui1_ret_buf;
										t_iom_uart.z_len = ui1_data_leng + 3;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);
									}
									break;	//kyo_20111226-end
                        #ifdef TPV_2K19_DFM // Ben 20181221
                                case 0x1C:
                                {
                                    if(aui1_cmd_buf[7] == 0x02)
                                    {
                                        DBG_INFO(("!!!! TPV_FACTORY_GET_CMD_FACTORY_CHECK_FLAG\n"));

                                        aui1_ret_buf[2] = 0x01; 	             // DataLen = 1
                                        aui1_ret_buf[3] = aui1_faccmd_ret_val[0];// status
                                        t_iom_uart.pui1_data = aui1_ret_buf;
                                        t_iom_uart.z_len = 4;
                                        c_iom_output(h_iom_uart, &t_iom_uart);
                                        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                                    }					
									break;
                                }
                        #endif
									
                                default:
                                    break;
                            }
                            break;
                            
                        case 0xF1:  //FCode11 : R
                            if(aui1_cmd_buf[6] == 0x05)
                            {
                            	if(aui1_cmd_buf[7] == 0x04) //TPV_FACTORY_SET_CMD_GET_ULPK_KEY
                            	{
									aui1_ret_buf[2] = ui1_data_leng;
								
									for(ui1_i = 0; ui1_i < ui1_data_leng; ui1_i++)
                                	{
	                                    //ke_vizio_20110330 for clean warning.
	                                    if((ui1_i + 3) >= CMD_LEN_Maximum)
	                                    {
	                                        DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
	                                        return;
	                                    }
	                                    aui1_ret_buf[ui1_i + 3] = aui1_faccmd_ret_val[ui1_i];
	                                }
	                                t_iom_uart.pui1_data = aui1_ret_buf;
	                                t_iom_uart.z_len = ui1_data_leng + 3;
	                                c_iom_output(h_iom_uart, &t_iom_uart);
									c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);

									break;
                            	}
								
                                if(aui1_cmd_buf[7] == 0x03) //TPV_FACTORY_SET_CMD_GET_POTK_KEY
                                {
                                    aui1_ret_buf[2] = ui1_data_leng;

                                    for(ui1_i = 0; ui1_i < ui1_data_leng; ui1_i++)
                                    {
                                        //ke_vizio_20110330 for clean warning.
                                        if((ui1_i + 3) >= CMD_LEN_Maximum)
                                        {
                                            DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
                                            return;
                                        }
                                        //aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                                        aui1_ret_buf[ui1_i + 3] = aui1_faccmd_ret_val[ui1_i];
                                    }
                                    t_iom_uart.pui1_data = aui1_ret_buf;
                                    t_iom_uart.z_len = ui1_data_leng + 3;
                                    c_iom_output(h_iom_uart, &t_iom_uart);
    								c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);

                                    break;
                                }
                                if(aui1_cmd_buf[7] == 0x05) //TPV_FACTORY_SET_CMD_CHECK_POTK_INDEX
                            	{
									aui1_ret_buf[2] = ui1_data_leng;
	                                aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                                    
	                                t_iom_uart.pui1_data = aui1_ret_buf;
	                                t_iom_uart.z_len = ui1_data_leng + 3;
	                                c_iom_output(h_iom_uart, &t_iom_uart);
									c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);

									break;
                            	}
                                if(aui1_cmd_buf[7] == 0x02) //TPV_FACTORY_SET_CMD_GET_ULPK_INDEX
                            	{
									aui1_ret_buf[2] = ui1_data_leng;
								
									for(ui1_i = 0; ui1_i < ui1_data_leng; ui1_i++)
                                	{
	                                    //ke_vizio_20110330 for clean warning.
	                                    if((ui1_i + 3) >= CMD_LEN_Maximum)
	                                    {
	                                        DBG_LOG_PRINT(("!!!!%s line %d over CMD_LEN_Maximum\n", __func__, __LINE__));
	                                        return;
	                                    }
	                                    aui1_ret_buf[ui1_i + 3] = aui1_faccmd_ret_val[ui1_i];
	                                }
	                                t_iom_uart.pui1_data = aui1_ret_buf;
	                                t_iom_uart.z_len = ui1_data_leng + 3;
	                                c_iom_output(h_iom_uart, &t_iom_uart);
									c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);

									break;
                            	}
                            }
                            break;
                            
                        case 0xCC:  
                            if(aui1_cmd_buf[6] == 0x55)
                            {
                            	if(aui1_cmd_buf[7] == 0x00)	
                            	{
									if(aui1_cmd_buf[8] == 0x00)	//TPV_FACTORY_SET_CMD_GET_LIGHT_SENSOR
									{
										aui1_ret_buf[2] = 0x02; 	// DataLen = 2
										aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
										aui1_ret_buf[4] = aui1_faccmd_ret_val[1];
										t_iom_uart.pui1_data = aui1_ret_buf;
										t_iom_uart.z_len = 5;
										c_iom_output(h_iom_uart, &t_iom_uart);
										c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
									}
                            	}
                            }
                            break;					
                            
                        default:
                            break;
                    }
                    break;

                // Write Commands
                case 0x03:
                    // Skip "Auto Color" Command
                    if((aui1_cmd_buf[4]==0xfe) && (aui1_cmd_buf[5]==0x1f)
                    && (aui1_cmd_buf[6]==0x00) && (aui1_cmd_buf[7]==00) && (aui1_cmd_buf[7]==00))
                    {
                        // Send Ack : To indicate "not valid src".
                        {
                            if(aui1_faccmd_ret_val[0]==1)
                            {
                                UINT8       aui1_ret_buf[CMD_LEN_Maximum];
                                IOM_UART_T  t_iom_uart;

                                c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

                                TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);

                                // Send Ack.
                                aui1_ret_buf[2] = 1;
                                aui1_ret_buf[3] = 2;
                                t_iom_uart.pui1_data = aui1_ret_buf;
                                t_iom_uart.z_len = 4;
                                c_iom_output(h_iom_uart, &t_iom_uart);
                                c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
#ifdef CLOSE_LISTENER
                                factory_close_svctx(1);
#endif
                                return;
                            }
                        }
                        // Send Ack : To indicate "No Signal Input".
                        {
                            if(aui1_faccmd_ret_val[0]==2)
                            {
                                UINT8       aui1_ret_buf[CMD_LEN_Maximum];
                                IOM_UART_T  t_iom_uart;

                                c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

                                TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);

                                // Send Ack.
                                aui1_ret_buf[2] = 1;
                                aui1_ret_buf[3] = 4;
                                t_iom_uart.pui1_data = aui1_ret_buf;
                                t_iom_uart.z_len = 4;
                                c_iom_output(h_iom_uart, &t_iom_uart);
#ifdef CLOSE_LISTENER
                                factory_close_svctx(1);
#endif
								c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear
                            }
                        }
                        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                        return;
                    }
//TOP Denny 2009/01/17 modify for SZ EPE issue#72 - Auto-color alignment cost 30 seconds for a part of TV sets.
                    // Send ACK for "Select Input Source" Command
                    else if((aui1_cmd_buf[4]==0xfe) && (aui1_cmd_buf[5]==0x60))
                    {
                        UINT8 ui1_Len_tmp1 = 3;
                        aui1_ret_buf[2] = 0x00;     // DataLen = 0
                        /* Delay 1 Second */
                        t_iom_uart.pui1_data = aui1_ret_buf;
                        t_iom_uart.z_len = ui1_Len_tmp1;
                        c_thread_delay(1000);
                        c_iom_output(h_iom_uart, &t_iom_uart);
                        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
                        return; // Send ACK in fac_ChagneSrc_svctx_notify_fct()
                    }
                    #ifdef Disable_USB_Auto_Start  //ke_vizio_20121205
                    // TPV_FACTORY_SET_CMD_FAC_DISABLE_USB_AUTO_START
                    else if(    (aui1_cmd_buf[4]==0xfe) && (aui1_cmd_buf[5]==0xf0) && (aui1_cmd_buf[6]==0x10) //Denny 2012/11/08 add to Disable USB Auto Start in TPV Factory FT (Function Test).....
                             && (aui1_cmd_buf[7]==0x05) && (aui1_cmd_buf[8]==0x01)  )
                    {
                        UINT8 ui1_Len_tmp1 = 4;
                        aui1_ret_buf[2] = 0x01;     // DataLen = 1
                        aui1_ret_buf[3] = 0x01;     // Result : [0]Fail, [1]Success

                        t_iom_uart.pui1_data = aui1_ret_buf;
                        t_iom_uart.z_len = ui1_Len_tmp1;
                        c_iom_output(h_iom_uart, &t_iom_uart);
					    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear
                        return;
                    }
                    #endif
                    else if((aui1_cmd_buf[4]==0xfe) && (aui1_cmd_buf[5]==0xe1)&& (aui1_cmd_buf[6]==0xac))  //ke_vizio_20130708 add
                    {
                        //TPV_FACTORY_SET_CMD_SET_PANEL_ID
                        UINT8 ui1_Len_tmp1 = 4;
                        aui1_ret_buf[2] = 0x01;     // DataLen = 1
                        aui1_ret_buf[3] = aui1_faccmd_ret_val[0];
                        t_iom_uart.pui1_data = aui1_ret_buf;
                        t_iom_uart.z_len = ui1_Len_tmp1;
                        c_iom_output(h_iom_uart, &t_iom_uart);
					    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear
                        return;
                    }
                    
                    // Normal Operation (Send ACK)
                    {
                        UINT8 ui1_Len_tmp1 = 3;
                        aui1_ret_buf[2] = 0x00;     // DataLen = 0

                        t_iom_uart.pui1_data = aui1_ret_buf;
                        t_iom_uart.z_len = ui1_Len_tmp1;
                    }
					// 2013/06/13 Ben added to debug ACK command.
					//c_dbg_stmt("!!!!Ben aui1_ret_buf[0]= %d\n", aui1_ret_buf[0]);
					//c_dbg_stmt("!!!!Ben aui1_ret_buf[1]= %d\n", aui1_ret_buf[1]);
					//c_dbg_stmt("!!!!Ben aui1_ret_buf[2]= %d\n", aui1_ret_buf[2]);

                    c_iom_output(h_iom_uart, &t_iom_uart);
					c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);	// clear
                    break;

                default:
                    break;
                }
                break;
            }
        }
    }
    else
    {
        for(ui1_i = 0; ui1_i < ui1_cmd_length; ui1_i++)
        {
            DBG_LOG_PRINT(("%02X ", t_iom_uart.pui1_data[ui1_i]));
        }
        switch (aui1_cmd_buf[1])
        {
            case 0x4F:
            case 0xD1:
                DBG_LOG_PRINT(("%02X", aui1_faccmd_ret_val[0]));
                break;

            case 0xE1:
                for(ui1_i = 0; ui1_i < aui1_ret_buf[4]; ui1_i++)
                {   
                    //ke_vizio_20110401 for clean warning.
                    if(ui1_i >= CMD_LEN_Maximum){
                        break;
                    }
                    DBG_LOG_PRINT(("%02X ", aui1_faccmd_ret_val[ui1_i]));
                }
                break;

            default:
                break;
        }
        DBG_LOG_PRINT(("\n\r"));
    }
#if 0	//kyo_20111228
    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
#endif
    return;
}

/*-----------------------------------------------------------------------------
 * Name: _fact_parser_set_cmd_nfy_to_leave
 *
 * Description: Notification function called from the factory daemon.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _fact_parser_set_cmd_nfy_to_leave(
    VOID*               pv_tag,
    VOID*               pv_val)
{
    UINT8           ui1_i;
    UINT8           aui1_ret_buf[6] ={0};  //ke_vizio_20110330 for clean warning.
    IOM_UART_T      t_iom_uart;
    UART_SETTING_T  t_uart_setting;

    for(ui1_i = 0; ui1_i < 5; ui1_i++)
        aui1_ret_buf[ui1_i] = aui1_cmd_buf[ui1_i];

    t_iom_uart.pui1_data = aui1_ret_buf;
    t_iom_uart.z_len     = 6; // Denny 2008/09/10 modify // 5->6

    if (b_cli_simulate == FALSE)
    {
        if (c_iom_output(h_iom_uart, &t_iom_uart) != IOMR_OK)
        {
            /*DBG_ERROR(("<fact_parser> Output response to UART fails\n"));*/
            DBG_LOG_PRINT(("<fact_parser> Output response to UART fails\n"));
        }

        t_uart_setting.e_speed    = IOM_UART_SPEED_75;
        t_uart_setting.e_data_len = IOM_UART_DATA_LEN_8;
        t_uart_setting.e_parity   = IOM_UART_PARITY_NONE;
        t_uart_setting.e_stop_bit = IOM_UART_STOP_BIT_1;

        if (c_iom_set(h_iom_uart,
                      IOM_SET_UART_SETTING,
                      (VOID*) &t_uart_setting,
                      sizeof(t_uart_setting)) != IOMR_OK)
        {
            /*DBG_ERROR(("<fact_parser> Stop UART fails\n"));*/
            DBG_LOG_PRINT(("<fact_parser> Stop UART fails\n"));
        }
    }
    else
    {
        for(ui1_i = 0; ui1_i < 6; ui1_i++)    // Denny 2008/09/10 modify // for(ui1_i = 0; ui1_i < 5; ui1_i++)
            DBG_LOG_PRINT(("%02X ", t_iom_uart.pui1_data[ui1_i]));
        DBG_LOG_PRINT(("\n\r"));
        b_cli_simulate = FALSE;
    }

    return;
}
#if 0
/*-----------------------------------------------------------------------------
 * Name: _fact_parser_single_rf_scan_nfy
 *
 * Description: Notification function called from the factory daemon.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _fact_parser_single_rf_scan_nfy(
    VOID*               pv_tag,
    VOID*               pv_val)
{
    if (t_scan_info.t_cmd_type == TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_TRSTRL)
    {   /* scan for digital now */
        t_scan_info.t_cmd_type = TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_TRSTRL;

        if (a_factory_set_cmd(t_scan_info.t_cmd_type,
                              (VOID*)(UINT32) t_scan_info.aui1_rf_num[0],
                              _fact_parser_single_rf_scan_nfy,
                              pv_tag ) != TPV_FACTORYR_OK)
        {
            /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
            c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
            return;
        }
    }
    else if (t_scan_info.t_cmd_type == TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_CABLE)
    {   /* scan for digital now */
        t_scan_info.t_cmd_type = TPV_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_CABLE;

        if (a_factory_set_cmd(t_scan_info.t_cmd_type,
                              (VOID*)(UINT32) t_scan_info.aui1_rf_num[0],
                              _fact_parser_single_rf_scan_nfy,
                              pv_tag ) != TPV_FACTORYR_OK)
        {
            /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
            c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
            return;
        }
    }
    else
    {
        if (t_scan_info.t_cmd_type == FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_TRSTRL)
        {   /* scan for analog next rf now */
            t_scan_info.t_cmd_type = FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_TRSTRL;
        }
        else if (t_scan_info.t_cmd_type == FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_CABLE)
        {   /* scan for analog next rf now */
            t_scan_info.t_cmd_type = FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_CABLE;
        }

        if (t_scan_info.aui1_rf_num[1] != 0)
        {   /* Check if any more RF channel to scan */
            t_scan_info.aui1_rf_num[0] = t_scan_info.aui1_rf_num[1];
            t_scan_info.aui1_rf_num[1] = 0;

            if (a_factory_set_cmd(t_scan_info.t_cmd_type,
                                  (VOID*)(UINT32) t_scan_info.aui1_rf_num[0],
                                  _fact_parser_single_rf_scan_nfy,
                                  pv_tag ) != TPV_FACTORYR_OK)
            {
                /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
                c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
            }
        }
        else if (t_scan_info.aui1_rf_num[2] != 0)
        {   /* Check if any more RF channel to scan */
            t_scan_info.aui1_rf_num[0] = t_scan_info.aui1_rf_num[2];
            t_scan_info.aui1_rf_num[2] = 0;

            if (a_factory_set_cmd(t_scan_info.t_cmd_type,
                                  (VOID*)(UINT32) t_scan_info.aui1_rf_num[0],
                                  _fact_parser_single_rf_scan_nfy,
                                  pv_tag ) != TPV_FACTORYR_OK)
            {
                /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
                c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
            }
        }
        else
        {
            _fact_parser_set_cmd_nfy((VOID*)(UINT32) t_scan_info.ui1_cs, NULL);

            c_memset((VOID*) &t_scan_info, 0, sizeof(t_scan_info));
        }
    }

    return;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _fact_parser_cli_cmd
 *
 * Description: CLI simulation of command input.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _fact_parser_cli_cmd(INT32        i4_argc,
                                  const CHAR** pps_argv)
{
    IOM_UART_T          t_iom_uart;
    UINT8               aui1_data[CMD_LEN_Maximum] = {0};
    UINT16              ui2_idx;
    CHAR                s_conv[16] = "0x";

#if 0
    for (ui2_idx = 0; ui2_idx < (i4_argc-1); ui2_idx++)
    {
        s_conv[2] = '\0';
        c_strncat(s_conv, pps_argv[ui2_idx + 1], 13);
        aui1_data[ui2_idx] = c_strtoull(s_conv, NULL, 0);
        c_dbg_stmt("aui1_data[%d] : 0x%X\n", ui2_idx, aui1_data[ui2_idx]);
    }

    t_iom_uart.pui1_data = aui1_data;
    t_iom_uart.z_len = ui2_idx;

    #if 0
    if(((aui1_data[1] != 0xE0) && (t_iom_uart.z_len != 5)) || ((aui1_data[1] == 0xE0) && ((aui1_data[2] == 0) || ((t_iom_uart.z_len - aui1_data[2]) != 5))))
    {
        c_dbg_stmt("usage: cmd SL CM0 CM1 CM2 CM3\n\r");
        return CLIR_INV_CMD_USAGE;
    }
    
    b_cli_simulate = TRUE;
    #endif
#else
    //ke_vizio_20110330 for clean warning.
    if(i4_argc > 15)
    {
        DBG_LOG_PRINT(("usage: cmd SL CM0 CM1 CM2 CM3...\n"));
        return CLIR_INV_CMD_USAGE;
    }

    aui1_data[0] = 0x6e;
    aui1_data[1] = 0x51;
    //maxium input argv[] : 15
    for (ui2_idx = 0; ui2_idx < (i4_argc); ui2_idx++)
    {
        s_conv[2] = '\0';
        c_strncat(s_conv, pps_argv[ui2_idx + 1], 13);
        aui1_data[ui2_idx+2] = c_strtoull(s_conv, NULL, 0);
        //c_dbg_stmt("aui1_data[%d] : 0x%X\n", ui2_idx, aui1_data[ui2_idx]);
    }

    t_iom_uart.pui1_data = aui1_data;
    t_iom_uart.z_len = ui2_idx + 2;
    
    if(aui1_data[0] != 0x6e || aui1_data[1] != 0x51)
    {
        DBG_LOG_PRINT(("usage: c cmd0 cmd1 ...\n\r"));
        return CLIR_INV_CMD_USAGE;
    }

    // Checksum
    UINT8  ui1_checksum = 0x6E;
    UINT8  ui1_length = (aui1_data[2]-0x80)+3;

    for(ui2_idx = 1; ui2_idx < (ui1_length); ui2_idx++)
    {
        //ke_vizio_20110330 for clean warning.
        if( ui1_length >= CMD_LEN_Maximum)
        {
            DBG_LOG_PRINT(("ui1_length > CMD_LEN_Maximum\n"));
            return CLIR_INV_CMD_USAGE;
        }
    
        ui1_checksum ^= aui1_data[ui2_idx];
    }

    if(ui1_checksum != aui1_data[ui1_length])      // Check sum is not correct
    {
        DBG_LOG_PRINT(("Check Sum error!!! Check sum is 0x%x\n", ui1_checksum));
        return CLIR_INV_CMD_USAGE;
    }
#endif

    

    _fact_parser_iom_nfy_fct(NULL,
                             IOM_NFY_COND_REC_UART_DATA,
                             0,
                             (UINT32) &t_iom_uart);

    return(CLIR_OK);
}

//
//  Uart2AckByte for TV proposal
//
//#define  _FPD_LINKID_DBG_               0        // for FPD side

//
//typedef enum { eLink_NG=0, eLink_OK, eLink_NOT_SUPPORTED  } tagLINKSTAT;


// ==========================================================================
// LinkId define
//   bit7,bit6           : AckType (0,1,2,3)
//   bit5,bit4,bit3,bit2 : Packet number
//   bit1,bit0           : Checksum
//
// AckType3: used for ack supported uart command
// AckType2: used for ack not supported uart command
// AckType1: reserved
// AckType0: reserved
//
//   >>>>>  good AckType3 LinkId table  <<<<<
//   { C2H C7H CBH CCH D3H D4H D8H DDH E3H E4H E8H EDH F0H F5H F9H FEH }  <--- table, 0xc0 ~ 0xff, for TV side
// = [ 02  07  0B  0C  13  14  18  1D  23  24  28  2D  30  35  39  3E  ]  <--- mask bit 7 and 6, used as index value for PC side
//
//
//   >>>>>  good AckType2 LinkId table  <<<<<
//   { 81H 86H 8AH 8FH 92H 97H 9BH 9CH A2H A7H ABH ACH B3H B4H B8H BDH }  <--- table, 0x80 ~ 0xbf, for TV side
// = [ 01  06  0A  0F  12  17  1B  1C  22  27  2B  2C  33  34  38  3D  ]  <--- mask bit 7 and 6, used as index value for PC side
// ==========================================================================

void TPVComm_TwoAckByteOkMsgGet(UINT8 *pui1_Buff)
{
  static const UINT8 UartAck_Ok_MsgTbl[16] =
    {0xc2,0xc7,0xcb,0xcc,0xd3,0xd4,0xd8,0xdd,0xe3,0xe4,0xe8,0xed,0xf0,0xf5,0xf9,0xfe};

  gPktNbr &= 0x0f;
  pui1_Buff[0] = UartAck_Ok_MsgTbl[gPktNbr++];
  pui1_Buff[1] = ~pui1_Buff[0];            // 2nd byte value = 1st byte 1's complement value
}

void TPVComm_TwoAckByteNotSupportMsgGet(UINT8 *pui1_Buff)
{
  static const UINT8 UartAck_NotSupport_MsgTbl[16] =
    {0x81,0x86,0x8a,0x8f,0x92,0x97,0x9b,0x9c,0xa2,0xa7,0xab,0xac,0xb3,0xb4,0xb8,0xbd};

  gPktNbr &= 0x0f;
  pui1_Buff[0] = UartAck_NotSupport_MsgTbl[gPktNbr++];
  pui1_Buff[1] = ~pui1_Buff[0];            // 2nd byte value = 1st byte 1's complement value
}

/*-----------------------------------------------------------------------------
 * Name: fac_AutoColor2_svctx_notify_fct
 * Description: Get the Auto-Color procedure status
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
VOID fac_AutoColor2_svctx_notify_fct(
    HANDLE_T            h_g_auto_color_dialog_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if((e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS || e_code == SVCTX_NTFY_CODE_INTERRUPTED)
     && (b_send_alignment_cmd == TRUE))
    {

        UINT8       aui1_ret_buf[CMD_LEN_Maximum];
        IOM_UART_T  t_iom_uart;

        c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

        TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);

        // Send Ack : To indicate "No signal input".
        aui1_ret_buf[2] = 1;
        aui1_ret_buf[3] = 4;
        t_iom_uart.pui1_data = aui1_ret_buf;
        t_iom_uart.z_len = 4;
        c_iom_output(h_iom_uart, &t_iom_uart);

#ifdef CLOSE_LISTENER
        factory_close_svctx(1);
#endif
//TOP Denny 2009/02/05 add
#ifdef CHECK_AUTO_COLOR_TIMEOUT
        c_timer_stop(h_fac_auto_color_timer);
        c_timer_delete(h_fac_auto_color_timer);
#endif

        b_send_alignment_cmd = FALSE;

        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
    }
    else if((e_code == SVCTX_NTFY_CODE_VIDEO_AUTO_COLOR_DONE) && (b_send_alignment_cmd == TRUE))
    {
//forroc for Auto color return fail command start
        UINT8       aui1_ret_buf[CMD_LEN_Maximum];
        IOM_UART_T  t_iom_uart;
// Denny 2009/01/16 mark for unuse code
/*
        AUTO_COLOR_COND_T e_auto_clr_cnd;
        SIZE_T z_get_info_size = sizeof(AUTO_COLOR_COND_T);
        INT32                   i4_ret;
*/
        c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

        TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);
#if 0
        i4_ret = c_svctx_get(h_g_auto_color_dialog_svctx,
                             SVCTX_COMMON_GET_AUTO_COLOR_COND,
                             &e_auto_clr_cnd,
                             &z_get_info_size
                            );
        if (i4_ret == SVCTXR_OK && e_auto_clr_cnd == AUTO_COLOR_COND_SUCCESS)
        {
            // Successful
            aui1_ret_buf[3] = 1;
        }
        else
        // Send Ack : To indicate "Invalid pattern".
        {
            // Failed
            aui1_ret_buf[3] = 3; // // Denny 2008/12/23 modify //aui1_ret_buf[3] = 0;
        }
#else
        aui1_ret_buf[3] = 1;
#endif
        aui1_ret_buf[2] = 1;
//        aui1_ret_buf[3] = 1;
        t_iom_uart.pui1_data = aui1_ret_buf;
        t_iom_uart.z_len = 4;
        c_iom_output(h_iom_uart, &t_iom_uart);

#ifdef CLOSE_LISTENER
        factory_close_svctx(1);
#endif
//TOP Denny 2009/02/05 add
#ifdef CHECK_AUTO_COLOR_TIMEOUT
        c_timer_stop(h_fac_auto_color_timer);
        c_timer_delete(h_fac_auto_color_timer);
#endif

        b_send_alignment_cmd = FALSE;
//forroc for Auto color return fail command start

        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear

    }

    #ifdef TPV_2K19_DFX_SIGNAL_DETECT
    if(e_code == SVCTX_NTFY_CODE_SIGNAL_LOCKED)
    {
        DBG_LOG_PRINT(("%s \n", "SVCTX_NTFY_CODE_SIGNAL_LOCKED"));
        g_ui1_signal_status = SVCTX_NTFY_CODE_SIGNAL_LOCKED;
    }
    else if(e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS)
    {
        DBG_LOG_PRINT(("%s \n", "SVCTX_NTFY_CODE_SIGNAL_LOSS"));
        g_ui1_signal_status = SVCTX_NTFY_CODE_SIGNAL_LOSS;
    }
    else if(e_code == SVCTX_NTFY_CODE_STOPPED)  //ke_vizio)20190320
    {
        DBG_LOG_PRINT(("%s \n", "SVCTX_NTFY_CODE_SIGNAL_LOSS"));
        // For channel table is not ready.
        g_ui1_signal_status = SVCTX_NTFY_CODE_STOPPED;
    }
    #endif

    //c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
}

#ifdef ACK_FOR_CHANGING_SOURCE_RESULT
VOID fac_ChagneSrc_svctx_notify_fct(
    HANDLE_T            h_g_auto_color_dialog_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if((e_code == SVCTX_NTFY_CODE_SIGNAL_LOCKED) && (b_send_alignment_cmd == TRUE))
    {
        UINT8       aui1_ret_buf[CMD_LEN_Maximum];
        IOM_UART_T  t_iom_uart;

        c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

        TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);

        aui1_ret_buf[2] = 0;
//        aui1_ret_buf[2] = 1;
//        aui1_ret_buf[3] = 1;
        t_iom_uart.pui1_data = aui1_ret_buf;
        t_iom_uart.z_len = 3;
        c_iom_output(h_iom_uart, &t_iom_uart);

#ifdef CLOSE_LISTENER
        factory_close_svctx(2);
#endif
        b_send_alignment_cmd = FALSE;
    }
    else if((e_code == SVCTX_NTFY_CODE_SIGNAL_LOSS) && (b_send_alignment_cmd == TRUE))
    {
        UINT8       aui1_ret_buf[CMD_LEN_Maximum];
        IOM_UART_T  t_iom_uart;

        c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

        TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);

        aui1_ret_buf[2] = 1;
        aui1_ret_buf[3] = 0;
        t_iom_uart.pui1_data = aui1_ret_buf;
        t_iom_uart.z_len = 4;
        c_iom_output(h_iom_uart, &t_iom_uart);

#ifdef CLOSE_LISTENER
        factory_close_svctx(2);
#endif
        b_send_alignment_cmd = FALSE;
    }
    c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
}
#endif

//TOP Denny 2009/02/05 add
#ifdef CHECK_AUTO_COLOR_TIMEOUT
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID fac_auto_color_timeout(HANDLE_T    h_timer,
                            VOID*       pv_tag   )
{
    INT32 i4_ret;
    {
        c_timer_stop(h_fac_auto_color_timer);
        c_timer_delete(h_fac_auto_color_timer);
        i4_ret = c_app_send_msg(h_g_TPV_factory,
                                (UINT32) TPV_FACTORY_FAKE_CMD_SEND_ACK,
                                NULL,
                                0,
                                NULL,
                                NULL );
        (void)i4_ret; // Handle unused variable.
    }
}
#endif

void fact_send_uart_msg(UINT8 ui1_val, UINT8 ui1_ack_len, BOOL b_clear_cmd_buf)
{
    UINT8       aui1_ret_buf[CMD_LEN_Maximum];
    IOM_UART_T  t_iom_uart;

    c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

    TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);

    if(ui1_ack_len==3)
    {
        aui1_ret_buf[2] = ui1_val;
    }
    else
    {
        aui1_ret_buf[2] = 1;
        aui1_ret_buf[3] = ui1_val;
    }
    t_iom_uart.pui1_data = aui1_ret_buf;
    t_iom_uart.z_len = ui1_ack_len;
    c_iom_output(h_iom_uart, &t_iom_uart);

    b_send_alignment_cmd = FALSE;
    if(b_clear_cmd_buf)
    {
        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
    }
}

void fact_send_uart_ack(UINT8 * pui1_val, UINT8 ui1_ack_len, BOOL b_clear_cmd_buf)
{
    UINT8       aui1_ret_buf[CMD_LEN_Maximum];
    UINT8       ui1_i;
    IOM_UART_T  t_iom_uart;

    c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear

    TPVComm_TwoAckByteOkMsgGet(aui1_ret_buf);

    if(ui1_ack_len<=3)
    // <= 3
    {
        ui1_ack_len = 3;
        aui1_ret_buf[2] = 0;
    }
    else
    // > 3
    {
        aui1_ret_buf[2] = ui1_ack_len - 3;
        for(ui1_i=0; ui1_i<(ui1_ack_len-3); ui1_i++)
            aui1_ret_buf[ui1_i+3] = pui1_val[ui1_i];
    }
    t_iom_uart.pui1_data = aui1_ret_buf;
    t_iom_uart.z_len = ui1_ack_len;
    c_iom_output(h_iom_uart, &t_iom_uart);

    b_send_alignment_cmd = FALSE;
    if(b_clear_cmd_buf)
    {
        c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear
    }
}


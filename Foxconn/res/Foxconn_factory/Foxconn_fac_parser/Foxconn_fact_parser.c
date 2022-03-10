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
//#include "res/app_util/config/acfg_Foxconn_fac_custom.h"
//TOP Denny 2009/02/20 add-end

#include "mtperipheral.h"
#include "res/Foxconn_factory/a_Foxconn_factory.h"
#include "Cus_Fac_foxconn.h"//WT@@20180213
 

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/* Modified by MTK. */
#define FACTORY_VIR_UART_ID       7//use 7 will cause cli no function    7 // 1     //  7 : CLI/factory share the same port.

//BOOL g_b_enter_Foxconn_fac_mode = FALSE;  //ke_vizio_20121220

/* 2007/03/19 Derek add this macro to simply code structure */ //WT@@20180315 ADD
#define FACTORY_SEND_CMD(fact_cmd4, cmd_type, cmd_val)	\
		if(ui2_UART_DataLength == fact_cmd4)					\
		{												\
			t_cmd_type=cmd_type;						\
			pv_cmd_val = (VOID*)(UINT32) cmd_val;		\
		}												\
		else											\
		{												\
			t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;		\
			pv_cmd_val = (VOID*)(UINT32) 0;				\
		}

typedef struct
{
    Foxconn_FACTORY_SET_CMD_TYPE_T	t_cmd_type;
    UINT8							aui1_rf_num[3];
    UINT8							ui1_cs;
} FACTORY_PARSER_SCAN_INFO_T;

//#define CMD_LEN_Maximum             30 // Denny 2009/01/07 move to a_factory.h

#undef DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE            factory_get_dbg_level()
#define FACTORY_CMD_ERROR_REP		0xFFFF//WT@@20180213
#define FACTORY_NOSUPPORT_RETURN	0xFFFE//WT@@20180213


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
static HANDLE_T	h_iom_uart = NULL_HANDLE;
UINT8			aui1_cmd_buf[CMD_LEN_Maximum] = {0};
UINT8			aui1_faccmd_ret_val[CMD_LEN_Maximum] = {0};
UINT8			aui1_faccmd_buf[HDCP2x_MAX_LEN] = {0};
#if 1
unsigned char	inFactory1 = 0;
unsigned char	cLong_Command1 = 0;
unsigned char	iFsum1 = 0;
unsigned int	FCommand1 = 0;
UINT8			bInFbuf1[CMD_LEN_Maximum-6] = {0};
unsigned int	Flen1 = 0, iBuff1 = 0;

unsigned char	inFactory2 = 0;
unsigned char	cLong_Command2 = 0;
unsigned char	iFsum2 = 0;
unsigned int	FCommand2 = 0;
//unsigned char	bInFbuf2[CMD_LEN_Maximum-6] = {0}; //hc@200604 changed
UINT8	        bInFbuf2[CMD_LEN_Maximum-6] = {0}; //hc@200604 chagned
unsigned int	Flen2 = 0, iBuff2 = 0;

UINT8			bInFHead[5] = {0};
unsigned char	bInFHead_cnt = 0;
unsigned char	iFsum = 0;

#else
static UINT16                       ui2_cmd_buf_idx;
#endif
static UINT8                        ui1_cmd_length;
static FACTORY_PARSER_SCAN_INFO_T	t_scan_info;
static BOOL                         b_cli_simulate;

//static BOOL						b_factory_mode_started = FALSE;

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

UINT16  ui2_cmd_return_type;//WT@@20180213
UINT16	ui2_delay_conut=0;//WT@@20180213

static UINT8 _gen_checksum(UINT8 *pui1_data,UINT16 ui1_count);//colby@191220

#if 0
static VOID _fact_parser_Printf(const CHAR* ps)//WT@@20180213
{
    UINT8  ui1_x=0,ui2_y=0;
    UINT8 aui1_com[256],aui1_ret_buf[256];
    IOM_UART_T  t_iom_uart;
   
    while ( *ps != 0 )
    {
        aui1_com[ui1_x] = *ps;	
	 ui1_x++;
	 ps++;
    }

    while ( ui2_y<ui1_x )
	{
		aui1_ret_buf[0]=aui1_com[ui2_y];
       	t_iom_uart.pui1_data= aui1_ret_buf;
       	t_iom_uart.z_len = 1;
	       ui2_y++;
		   
              c_iom_output(h_iom_uart, &t_iom_uart);   
        }
}
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
#if 0
static VOID _fact_parser_set_cmd_nfy_to_leave(
                    VOID*                       pv_tag,
                    VOID*                       pv_val);

static VOID _fact_parser_single_rf_scan_nfy(
                    VOID*                       pv_tag,
                    VOID*                       pv_val);
#endif

void FoxconnComm_TwoAckByteOkMsgGet(UINT8 *pui1_Buff);
void FoxconnComm_TwoAckByteNotSupportMsgGet(UINT8 *pui1_Buff);

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
extern VOID x_thread_delay (UINT32  ui4_delay);//WT@@20180223

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*======================== Tommy 0301 Start==============================*/
void Factory_Return_NACK(void) {
    UINT8 aui1_my_buf[] = {0x01, 0x00, 0x00, 0x00, 0xFE};
	IOM_UART_T	t_iom_uart;

	t_iom_uart.pui1_data = aui1_my_buf;
	t_iom_uart.z_len	 = 5;
	if (c_iom_output(h_iom_uart, &t_iom_uart) != IOMR_OK)
	{
		DBG_INFO(("<fact_parser> Output response to UART fails\n"));
	}
}

void Factory_Return_NOT_SUPPORT(void) {
	DBG_INFO(("<fact_parser> Factory_Return_NOT_SUPPORT \n"));
    UINT8 aui1_my_buf[] = {0x01, 0x01, 0x00, 0x00, 0xFD};
	IOM_UART_T	t_iom_uart;

	t_iom_uart.pui1_data = aui1_my_buf;
	t_iom_uart.z_len	 = 5;
	if (c_iom_output(h_iom_uart, &t_iom_uart) != IOMR_OK)
	{
		DBG_INFO(("<fact_parser> Output response to UART fails\n"));
	}
}
/*======================== Tommy 0301 End==============================*/
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
__attribute__ ((visibility("default"))) VOID a_Foxconn_fact_parser_init(VOID)
{
    UART_SETTING_T  t_uart_setting;
    /* Added by MTK. */
    UINT32 ui4_mode = IOM_UART_OPERATION_MODE_FACTORY| IOM_UART_OPERATION_MODE_TRANSPARENT;
//TOP Denny 2009/02/05 add
    INT32           i4_ret;

#if 0
    ui2_cmd_buf_idx = 0;
#endif
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
static VOID _fact_parser_iom_nfy_rec_buf(    UINT32          ui4_data)
{
    IOM_UART_T*         pt_iom_uart;

#if 1
	int i ,j;
	pt_iom_uart = (IOM_UART_T*) ui4_data;
	if (0 == pt_iom_uart->z_len)
	{
		return;
	}

	if (cLong_Command1 == 0) {
		DBG_LOG_PRINT(("$$$$$$ [ Factory1_Clean ]  \n"));
		inFactory1 = 0;
		FCommand1 = 0;
		iFsum1 = 0;
		iBuff1 = 0;
		Flen1 = 0;
	}
	if (cLong_Command2 == 0) {
		DBG_LOG_PRINT(("$$$$$$ [ Factory2_Clean ]  \n"));
		inFactory2 = 0;
		FCommand2 = 0;
		iFsum2 = 0;
		iBuff2 = 0;
		Flen2 = 0;
	}

	DBG_LOG_PRINT(("$$$$$$ [ MTK -> FOXCONN Len	] = %d \n", pt_iom_uart->z_len));
	for (i = 0; i < pt_iom_uart->z_len; i++) 
	{
//		DBG_LOG_PRINT(("$$$$$$ [ Factory ]	: pt_iom_uart->pui1_data[%d] = %X \n", i, pt_iom_uart->pui1_data[i]));

		if ((pt_iom_uart->pui1_data[i] == 0xC0) && (bInFHead_cnt == 0))  //&& ( inFactory1 == 0) && (inFactory2 == 0)
		{
			bInFHead_cnt = 1;
			bInFHead[0] = 0xC0;
			iFsum = 0xC0;
		} else if (bInFHead_cnt != 0) {
			if (bInFHead_cnt == 5) {
				if (inFactory1 == 0) {
					Flen1 = ((((UINT16)bInFHead[3]<<8)& 0xFF00 )|((UINT16)bInFHead[4]& 0x00FF ));	
					if (Flen1 <= CMD_LEN_Maximum) {
						DBG_LOG_PRINT(("$$$$$$ [ INTO Factory1 ]  \n"));
						inFactory1 = 1;
						iFsum1 = iFsum;
						FCommand1 = (((UINT16)bInFHead[1]<<8)& 0xFF00 )|((UINT16)bInFHead[2]& 0x00FF ); 
						DBG_LOG_PRINT(("$$$$$$ [ FCommand1 ]   %X \n", FCommand1));
						iBuff1 = Flen1;
						DBG_LOG_PRINT(("$$$$$$ [ Flen1 ]   %d \n", Flen1));
						cLong_Command1 = 1;

						if ((inFactory2 == 1) && (FCommand1 == FCommand2) && (Flen1 == Flen2)) {
							DBG_LOG_PRINT(("$$$$$$ [ Disable  cLong_Command2]  \n"));
							cLong_Command2 = 0;
							inFactory2 = 0;
						}
					}
				} else if (inFactory2 == 0) {
					Flen2 = ((((UINT16)bInFHead[3]<<8)& 0xFF00 )|((UINT16)bInFHead[4]& 0x00FF ));	
					if (Flen2 <= CMD_LEN_Maximum) {
						DBG_LOG_PRINT(("$$$$$$ [ INTO Factory2 ]  \n"));
						inFactory2 = 1;
						iFsum2 = iFsum;
						FCommand2 = (((UINT16)bInFHead[1]<<8)& 0xFF00 )|((UINT16)bInFHead[2]& 0x00FF ); 
						DBG_LOG_PRINT(("$$$$$$ [ FCommand2 ]   %X \n", FCommand2));
						iBuff2 = Flen2;
						DBG_LOG_PRINT(("$$$$$$ [ Flen2 ]   %d \n", Flen2));
						cLong_Command2 = 1;

						if ((inFactory1 == 1) && (FCommand1 == FCommand2) && (Flen1 == Flen2)) {
							DBG_LOG_PRINT(("$$$$$$ [ Disable  cLong_Command1]  \n"));
							cLong_Command1 = 0;
							inFactory1 = 0;
						}
					}
				}

				bInFHead_cnt = 0;
				iFsum = 0;
			} else {
				bInFHead[bInFHead_cnt] = pt_iom_uart->pui1_data[i];
				iFsum += bInFHead[bInFHead_cnt];
				bInFHead_cnt++;
			}
		}

		if (inFactory1 == 1) 
		{
			if (iBuff1 == 0) 
			{
				cLong_Command1 = 0;
				iFsum1 &= 0xFF;
				iFsum1 = 0xFF - iFsum1;
				DBG_LOG_PRINT(("$$$$$$ [ CheckSum1 ]   %X \n", iFsum1));

				if (iFsum1 == pt_iom_uart->pui1_data[i]) {
					cLong_Command2 = 0;
					bInFHead_cnt = 0;
//					return Factory_Command(FCommand1, bInFbuf1, Flen1);
					aui1_cmd_buf[0] = 0xC0;
					aui1_cmd_buf[1] = (FCommand1>>8) & 0x00FF;
					aui1_cmd_buf[2] = FCommand1 & 0x00FF;
					aui1_cmd_buf[3] = (Flen1>>8) & 0x00FF;
					aui1_cmd_buf[4] = Flen1 & 0x00FF;
					if (Flen1 > CMD_LEN_Maximum-6)	//Tommy 20210129 MTK request
					{
						DBG_LOG_PRINT(("<fact_parser> inFactory1 Command too long \n"));
						inFactory1 = 0;
						FCommand1 = 0;
						iFsum1 = 0;
						iBuff1 = 0;
						Flen1 = 0;
						return;
					}
					for (j=0; j<Flen1; j++)
					{
						aui1_cmd_buf[j+5] = bInFbuf1[j];
					}
					ui1_cmd_length = Flen1+6;
					aui1_cmd_buf[ui1_cmd_length-1]=iFsum1;
					if (a_Foxconn_factory_set_cmd(Foxconn_FACTORY_SET_CMD_CONTEXT_SWITCH,
						  NULL,
						  _fact_parse_cmd,
						  NULL ) != FACTORYR_OK)
					{
						DBG_LOG_PRINT(("<fact_parser> UART ack command to factory daemon fails\n"));
					}
					return;
				} else {
					DBG_LOG_PRINT(("<fact_parser> CheckSum1 Compare Fail \n"));
					inFactory1 = 0;
					FCommand1 = 0;
					iFsum1 = 0;
					iBuff1 = 0;
					Flen1 = 0;
					if ((inFactory2 == 0) && (bInFHead_cnt == 0)) 
					{
//						Factory_Return_NOT_SUPPORT();
						return;
					}
				}
			}
			bInFbuf1[Flen1 - iBuff1] = pt_iom_uart->pui1_data[i];
//			DBG_LOG_PRINT(("$$$$$$ [ bInFbuf1 ]  : iBuff1 = %d : bInFbuf1[%d] = %X \n", iBuff1, Flen1 - iBuff1, bInFbuf1[Flen1 - iBuff1]));
			iBuff1--;
			iFsum1 += pt_iom_uart->pui1_data[i];
		}
	
		if (inFactory2 == 1) 
		{
			if (iBuff2 == 0) 
			{
				cLong_Command2 = 0;
				iFsum2 &= 0xFF;
				iFsum2 = 0xFF - iFsum2;
				DBG_LOG_PRINT(("$$$$$$ [ CheckSum2 ]   %X \n", iFsum2));

				if (iFsum2 == pt_iom_uart->pui1_data[i]) 
				{
					cLong_Command1 = 0;
					bInFHead_cnt = 0;
//					return Factory_Command(FCommand2, bInFbuf2, Flen2);
					aui1_cmd_buf[0] = 0xC0;
					aui1_cmd_buf[1] = (FCommand2>>8) & 0x00FF;
					aui1_cmd_buf[2] = FCommand2 & 0x00FF;
					aui1_cmd_buf[3] = (Flen2>>8) & 0x00FF;
					aui1_cmd_buf[4] = Flen2 & 0x00FF;
					if (Flen2 > CMD_LEN_Maximum-6)	//Tommy 20210129 MTK request
					{
						DBG_LOG_PRINT(("<fact_parser> inFactory2 Command too long \n"));
						inFactory2 = 0;
						FCommand2 = 0;
						iFsum2 = 0;
						iBuff2 = 0;
						Flen2 = 0;
						return;
					}
					for (j=0; j<Flen2; j++)
					{
						aui1_cmd_buf[j+5] = bInFbuf2[j];
					}
					ui1_cmd_length = Flen2+6;
					aui1_cmd_buf[ui1_cmd_length-1]=iFsum2;
					if (a_Foxconn_factory_set_cmd(Foxconn_FACTORY_SET_CMD_CONTEXT_SWITCH,
	                      NULL,
	                      _fact_parse_cmd,
	                      NULL ) != FACTORYR_OK)
				    {
				        DBG_LOG_PRINT(("<fact_parser> UART ack command to factory daemon fails\n"));
				    }
					return;
				} else {
					DBG_LOG_PRINT(("<fact_parser> CheckSum2 Compare Fail \n"));
					inFactory2 = 0;
					FCommand2 = 0;
					iFsum2 = 0;
					iBuff2 = 0;
					Flen2 = 0;
					if ((inFactory1 == 0) && (bInFHead_cnt == 0)) 
					{
//						Factory_Return_NOT_SUPPORT();
						return;
					}
				}
			}
			bInFbuf2[Flen2 - iBuff2] = pt_iom_uart->pui1_data[i];
//			DBG_LOG_PRINT(("$$$$$$ [ bInFbuf2 ]  : iBuff2 = %d : bInFbuf2[%d] = %X \n", iBuff2, Flen2 - iBuff2, bInFbuf2[Flen2 - iBuff2]));
			iBuff2--;
			iFsum2 += pt_iom_uart->pui1_data[i];
		}
	}

	if ((cLong_Command1 == 1) || (cLong_Command2 == 1) || (bInFHead_cnt != 0)) {
		return;
	} else {
		DBG_LOG_PRINT(("$$$$$$ [ Factory Fail ]  \n"));
		if (inFactory1 == 1) 
			Factory_Return_NACK();
		return;
	}

#else
    UINT16              ui2_idx;

	pt_iom_uart = (IOM_UART_T*) ui4_data;
	if (0 == pt_iom_uart->z_len)
	{
		return;
	}
    ui2_idx = 0;
	DBG_LOG_PRINT(("<_fact_parser_iom_nfy_rec_buf> Get UART Len = %d \n",pt_iom_uart->z_len));
	
    /* MTK: Suggest to add a lock here. */
    while (ui2_idx < pt_iom_uart->z_len)
    {
        if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0xC0))	//Tommy 20200108
//        if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0xC0) || (pt_iom_uart->pui1_data[ui2_idx] == 0x58)) // Denny 2008/09/10 modify
//        if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0x6E) || (pt_iom_uart->pui1_data[ui2_idx] == 0x58))
        {
            if(ui2_cmd_buf_idx >= CMD_LEN_Maximum)  //ke_vizio_20110402 for clean warning.
            {
                break;
            }
            
            aui1_cmd_buf[ui2_cmd_buf_idx] = pt_iom_uart->pui1_data[ui2_idx];
            ++ui2_cmd_buf_idx;
			DBG_LOG_PRINT(("<_fact_parser_iom_nfy_rec_buf> aui1_cmd_buf[%d] = 0x%X \n",ui2_cmd_buf_idx, aui1_cmd_buf[ui2_cmd_buf_idx]));
        }
        ++ui2_idx;
    }

    ui2_cmd_buf_idx = 0;
    ui1_cmd_length = pt_iom_uart->z_len;
    /* Added by MTK. */
    if (a_Foxconn_factory_set_cmd(Foxconn_FACTORY_SET_CMD_CONTEXT_SWITCH,
                          NULL,
                          _fact_parse_cmd,
                          NULL ) != FACTORYR_OK)
    {
        DBG_LOG_PRINT(("<fact_parser> UART ack command to factory daemon fails\n"));
    }
    /* Removed by MTK. */
//    _fact_parser_parse_and_set_cmd();
    /* MTK: Suggest to unlock here. */
#endif
    return;
}

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
//WT@@20180213
	Foxconn_FACTORY_SET_CMD_TYPE_T	t_cmd_type = Foxconn_FACTORY_INVALID_CMD;;
	VOID*							pv_cmd_val = (VOID*) 0;
	VOID*							pv_tag = (VOID*) 0;
	BOOL							b_do_common_set_cmd = FALSE;
	
	
//	UINT16	ui2_temp_value;
//	UINT32	ui2_check_sum = 0;
//	UINT8	ui2_cur_cmd_len=ui2_cmd_len;
	
	UINT16 ui2_UART_Item; 
	UINT16 ui2_UART_DataLength; 
	
//	int j;
//	for (j=0; j<ui1_cmd_length; j++)
//		DBG_INFO(("aui1_cmd_buf[%d] = 0x%X \n",j ,aui1_cmd_buf[j]));
	
	ui2_cmd_return_type=Foxconn_FACTORY_CMD_RETURN_DEFAULT;
	
	if (aui1_cmd_buf[0] == 0xC0)
	{

		ui2_UART_Item = (((UINT16)aui1_cmd_buf[1]<<8)& 0xFF00 )|((UINT16)aui1_cmd_buf[2]& 0x00FF );
		ui2_UART_DataLength = (((UINT16)aui1_cmd_buf[3]<<8)& 0xFF00 )|((UINT16)aui1_cmd_buf[4]& 0x00FF );	

#if 0
/*======================== Tommy 0301 Start==============================*/
		if (ui2_UART_DataLength <= CMD_LEN_Maximum) 
		{
			unsigned char iFsum = 0;
			int i = 0;
			
			for (i = 0;  i < ui2_UART_DataLength+5; ++i)
			{
				iFsum+=aui1_cmd_buf[i];
			}
			iFsum &= 0xFF;
			iFsum = 0xFF - iFsum;
			
			if (iFsum != aui1_cmd_buf[5+ui2_UART_DataLength])
			{
				  t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
				  pv_cmd_val = (VOID*) 0;
				  Factory_Return_NOT_SUPPORT();
				  return;
			}
		}
/*======================== Tommy 0301 End==============================*/
#endif
		b_do_common_set_cmd = TRUE;
		DBG_INFO(("\n <fact_parser>_fact_parser_parse_and_set_cmd1 \n"));

        DBG_INFO(("\n --------------------------------cmd----------------------------------- \n"));        
		switch ( ui2_UART_Item ) // ui2_UART_Item
		{
/*======================== Tommy 0303 Start==============================*/
			case GET_FAC_VERSION:
				{
					UINT8 auif_my_buf[5+Foxconn_Factory_Lens] = {0x00, 0x01, 0x00, Foxconn_Factory_Lens};
					IOM_UART_T	t_iom_uart;
					unsigned char iFsum = 0;
					int i = 0;
					
					b_do_common_set_cmd = FALSE;
					
					t_iom_uart.pui1_data = auif_my_buf;
					t_iom_uart.z_len	 = 5+Foxconn_Factory_Lens;

					c_strcpy((CHAR*)auif_my_buf+4,Foxconn_Factory_Version);
					for (i = 0;  i < 5+Foxconn_Factory_Lens; ++i)
					{
						iFsum += auif_my_buf[i];
					}
					iFsum &= 0xFF;
					iFsum = 0xFF - iFsum;
					auif_my_buf[4+Foxconn_Factory_Lens] = iFsum;
					
					if (c_iom_output(h_iom_uart, &t_iom_uart) != IOMR_OK)
					{
						DBG_INFO(("<fact_parser> Output response to UART fails\n"));
					}
				}
				break;

			case SET_MODEL_TYPE:
				switch(aui1_cmd_buf[5])
				{
				#if defined(MT5691_MODEL)
					case 0x01 ... 0x61: //colby@20012  //  ModelIndex 1~ 97//update WT@20210409 &20210526 &20210607
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_MODEL_INDEX, aui1_cmd_buf[5]);
						break;
				#elif defined(MT5695_MODEL)	
					case 0x01 ... 0x11: ////  ModelIndex 1~ 17//update WT@20210817
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_MODEL_INDEX, aui1_cmd_buf[5]);
						break;
				#endif
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;						
						pv_cmd_val = (VOID*) 0;
						break;
				}
				break;            

			case GET_MODEL_TYPE:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_GET_MODEL_INDEX, 0);
                break;
			
			// FXC Jim 2018 0713 vvvvvv
			case SET_MODEL_GROUP:
				FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_MODEL_GROUP, aui1_cmd_buf[5]);
                break;
				
			case GET_MODEL_GROUP:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_GET_MODEL_GROUP, 0);
                break;
			// FXC Jim 2018 0713 ^^^^^	
            // RD used 20200120 EEPROM control 
			case GET_EPPROM_LOAD: //colby@20200120
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_GET_CMD_EEPROM_LOAD, 0);
                break;
               
			case SET_EEPROM_RESET:
                FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_EEPROM_RESET, 0);
                break;

			case SET_EEPROM_DATA:
				DBG_INFO(("<fact_parser> SET_EEPROM_DATA\n"));
				t_cmd_type = Foxconn_FACTORY_GET_CMD_EEPROM_SET;
				pv_cmd_val = (VOID*) &aui1_cmd_buf[4];  /* set data len */
                break;
		   
			case KEYPAD_STATUS:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_READ_KEYPAD_POWER, 0);
				break;

			case GET_KEYPAD_ADC_FXN:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_READ_KEYPAD_ADC_VALUE, 0);
				break;
				
			case SET_TUNER_MODE:
				break;
				
			case GET_TUNER_MODE:
				break;
				
			case SAVE_WBData_To_Default:				//Tommy 20180607
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_RESET_WB_DATA,0);
				break;

			case BYPASS_PQ_SETTING:						//Tommy 20180607
				FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_PQ_BYPASS, aui1_cmd_buf[5]);
				break;
			
			// yuan vvvvv 			
// FXC_Jim 2018_0331 vvvvvv		
			case SET_PERSET_CHANNEL_TO_USB:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_PERSET_CHANNEL_TO_USB;
				pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				break;
				
			case SET_POWER_ON_OFF: //colby@191223
                    switch(aui1_cmd_buf[5])
					{
                        case 0x00:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_POWER_OFF;
							pv_cmd_val = (VOID*) 0;
							break;

                        case 0x01:    
							t_cmd_type = Foxconn_FACTORY_SET_CMD_NOT_SUPPORT;
							pv_cmd_val = (VOID*) 0;                 
							break;						
                        default:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
							pv_cmd_val = (VOID*) 0;
                            break;
                    }
                    break;
					
			case GET_AGING_TIME_T:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_T, 0);
				break;
			
			case GET_AGING_TIME_P:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_P, 0);
				break;

			case CLEAR_AGING_TIME:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_SET_AGING_TIME, 0);
				break;
			
// FXC_Jim 2018_0331 ^^^^^				
			case FAC_PERSET_CHANNEL:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_PERSET_CHANNEL;
				pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				break;

			case SOFTWARE_RESET:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_DO_REBOOT;
				pv_cmd_val = (VOID*) 0;
				break;

/*======================== Tommy 0303 End==============================*/
			case SET_SERIAL_NUMBER:/*Set Serial Number & Get Serial Number*/
				if(ui2_UART_DataLength == 0x0F) 
				{  
					DBG_INFO(("<fact_parser> Set Serial Number\n"));
					t_cmd_type = Foxconn_FACTORY_SET_CMD_EDID_SERIAL_NUM;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				break;
				
			case GET_SERIAL_NUMBER: 
				if(ui2_UART_DataLength == 0x00) 
				{	 
					DBG_INFO(("<fact_parser> Get Serial Number\n"));
					t_cmd_type = Foxconn_FACTORY_READ_CMD_EDID_SERIAL_NUM;
					pv_cmd_val = (VOID*) 0;
				}

				break;			   
#if 1
			case GET_WIFI_MAC_ADDR :  // ui2_UART_Item = 0087
				if((ui2_UART_DataLength == 6)|| (ui2_UART_DataLength == 0) ) //&& (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR;
					pv_cmd_val = (VOID*) 0;
				}
				break;
#endif
			case SET_ETHERNET_MAC_ADDR:/*SET_ETHERNET_MAC_ADDR*/
				if((ui2_UART_DataLength == 6) ) //  && (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_WIRED_ETHERNET_MAC_ADDR;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;		 
				}
				break;
				  
			case GET_ETHERNET_MAC_ADDR :	// *GET_ETHERNET_MAC_ADDR*
				if((ui2_UART_DataLength == 6) || (ui2_UART_DataLength == 0)|| (ui2_UART_DataLength == 17)) //&& (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR;
					pv_cmd_val = (VOID*) 0;
				}
				break;

			case SET_NW_KEY_ULPK:/*SET_NW_KEY_ULPK*/
#if 1  // From TPV  ( ULPK 4.X)
				if((ui2_UART_DataLength == ULPK_DATA_LEN) ) /* ULPK_ID (4) +ULPK_KEY (32) */
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_ULPK_KEY;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
#else
				if((ui2_UART_DataLength == 96) ) // && (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_ULPK_KEY;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				// yuan 2012 0827 vvvvv
				else if (ui2_UART_DataLength == 17)
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_ULPK_BY_16BYTES;
					pv_cmd_val = (VOID*)&aui1_cmd_buf[5];
				}
#endif
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				// yuan 2012 0827 ^^^^^
				break;

			case GET_NW_KEY_ULPK:/*GET_NW_KEY_ULPK*/
				if((ui2_UART_DataLength == 0) ) //&& (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_ULPK_KEY;
					pv_cmd_val = (VOID*) 0;
				}

				break;

			case SET_NW_KEY_POTK:/*SET_NW_KEY_POTK*/
				if((ui2_UART_DataLength == 16) ) // && (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_POTK_KEY;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				// yuan 2012 0827 vvvvv
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				// yuan 2012 0827 ^^^^^

				break;

			case GET_POTK:/*GET_NW_KEY_POTK*/
				if((ui2_UART_DataLength == 0) ) //&& (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_POTK_KEY;
					pv_cmd_val = (VOID*) 0;
				}

				break;

			case GET_POTK_STATUS:/*GET_NW_KEY_POTK_STATUS*/
				if((ui2_UART_DataLength == 0) ) //&& (ui1_cs == aui1_checksum))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECK_POTK_INDEX;
					pv_cmd_val = (VOID*) 0;
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;

			case SET_MAIN_INPUT_SRC:/* Set Input Source */
				if (ui2_UART_DataLength != 1) 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;  
					break;
				} 	  
				switch ( aui1_cmd_buf[5] )
				{
					case 0x00 : //20211202 Tommy
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_BOOT_SC_DISABLE;
						pv_cmd_val = (VOID*) 1;
						break;
					case 0x01 : //TV
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_TV;
						pv_cmd_val = (VOID*) 1;
						break;
						
					case 0x02 :  //analog
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMP_VIDEO;
						//			  t_cmd_type = FACTORY_SET_CMD_SELECT_INPUT_SOURCE_Y_PB_PR;  
						pv_cmd_val = (VOID*) 1;
						break;
						
					case 0x03 : // combine, NT@FXC, 20130319
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMBI;  
						pv_cmd_val = (VOID*) 1;
						break;		
						
					case 0x31 : //component
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_Y_PB_PR;  
						pv_cmd_val = (VOID*) 1;
						break;	  
						
					case 0x41 : //VGA
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_VGA;  
						pv_cmd_val = (VOID*) 1;
						break;	
						
					case 0x11 : //HDMI1
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI;
						pv_cmd_val = (VOID*) 1;
						break;		
						
					case 0x12 : //HDMI2
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI;
						pv_cmd_val = (VOID*) 2;
						break;		
						
					case 0x13 : //HDMI3
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI;
						pv_cmd_val = (VOID*) 3;
						break;	
						
					case 0x14 : //HDMI4
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI;
						pv_cmd_val = (VOID*) 4;
						break;		
						
					default : 
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;				  
						break;
				}
				break;

			case GET_MAIN_INPUT_SRC:/* Get Input Source Status*/

				if (ui2_UART_DataLength == 0)
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_SOURCE_TYPE;
					pv_cmd_val = (VOID*) 0;
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;

			case SET_HDMI_EDID:/*SET EDID*/
				if((ui2_UART_DataLength == 2) ) 
				{
					if (aui1_cmd_buf[5] == 1 )						  
						t_cmd_type = Foxconn_FACTORY_GET_CMD_CUST_SET_INT_HDMI_EDID;
					else if (aui1_cmd_buf[5] == 2 )						  
						t_cmd_type = Foxconn_FACTORY_GET_CMD_CUST_SET_INT_VGA_EDID;			  
						pv_cmd_val =  (VOID*)(UINT32)aui1_cmd_buf[6];	 // yuan 2012 0726 
				}
				else if((ui2_UART_DataLength == 1) ) 
				{
					if (aui1_cmd_buf[5] == 1 )						  
						t_cmd_type = Foxconn_FACTORY_GET_CMD_CUST_SET_INT_HDMI_EDID;
					else if (aui1_cmd_buf[5] == 2 )						  
						t_cmd_type = Foxconn_FACTORY_GET_CMD_CUST_SET_INT_VGA_EDID;			  
						pv_cmd_val = (VOID*)1;   // yuan 2012 0726 
				} 		  
				break;

			case GET_HDMI_EDID:/*GET EDID*/
				if((ui2_UART_DataLength == 1) ) 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_FAC_READ_EDID;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				break;
				
			case GET_HDMI_EDID_512:/*GET EDID 512B*/
				if((ui2_UART_DataLength == 1) )//WT@20210122 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_FAC_READ_EDID_512;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				break;				

			case SET_HDCP_KEY:	//Tommy 20191004 MST Key long 304
				if (aui1_cmd_buf[5] <= 18)
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_WRITE_HDCP_14_DATA;//FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE ; // yuan debug FACTORY_SET_CMD_WRITE_HDCP;
					pv_cmd_val = (VOID*)&aui1_cmd_buf[5];
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;
				
			case GET_HDCP_KEY:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_14_DATA;//FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV;
				pv_cmd_val = (VOID*) 1;
				break;
				
			case SET_HDCP2X_KEY:	//Tommy 20191004 MST Key long 1044 -> 0 ~ 8 = 0x6f, 9 = 0x37
				if (((aui1_cmd_buf[5] < 9) && (ui2_UART_DataLength == 111)) ||
					((aui1_cmd_buf[5] == 9) && (ui2_UART_DataLength == 55)))
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_WRITE_HDCP_2X_DATA;//FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_HDCP_CRC16_AUTO_WRITE ; // yuan debug FACTORY_SET_CMD_WRITE_HDCP;
					pv_cmd_val = (VOID*)&aui1_cmd_buf[5];
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;

			case GET_HDCP2X_KEY:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_2X_DATA;//FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV;
				pv_cmd_val = (VOID*) 1;
				break;
				
			case GET_FW_VERSION:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_SW_VER;
				pv_cmd_val = (VOID*) 0;
				break;
				
			case GET_PANEL_NAME://WT@@20180320
				if((ui2_UART_DataLength == 0) ) 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE;
					pv_cmd_val = (VOID*) 0;
				}
				break;
//Start =============================================//WT@@20180313/0314/0315/0316
			case SET_PIC_RESET:
				{
					if (ui2_UART_DataLength == 0)
					{
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_PICTURE_RESET;
						pv_cmd_val = (VOID*) 0;
					}
					else
					{
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
					}
				}
					break;

			 case SET_PIC_MODE:
			 {
				  if (ui2_UART_DataLength == 1)
				  {
					 t_cmd_type = Foxconn_FACTORY_SET_CMD_SELECT_PIC_MODE_VIVID;
					 switch(aui1_cmd_buf[5])
					 {
						 case Picture_Mode_Vivid:   //Vivd		 
							 pv_cmd_val = (VOID*) 0;
							 break;
						 case Picture_Mode_Dynamic_HiBright:  //Bright		
							 pv_cmd_val = (VOID*) 1;
							 break;
						 case Picture_Mode_Calibrated:  //calibrated 		 
							 pv_cmd_val = (VOID*) 2;
							 break;
						 case Picture_Mode_Calibrated_Dark:  //calibrated dark		 				
							 pv_cmd_val = (VOID*) 3;
							 break;
						 case Picture_Mode_Game:  //game 		 
							 pv_cmd_val = (VOID*) 4;
							 break;
						 case Picture_Mode_Football_Sport:  //Soprt 		
							 pv_cmd_val = (VOID*) 5;
							 break;
//						 case 0x0b:  //basketball
//							 pv_cmd_val = (VOID*) 6;
//							 break;
//						 case 0x0c:  //baseball
//							 pv_cmd_val = (VOID*) 7;
//							 break;
//						 case 0x03:  //custom
//							 pv_cmd_val = (VOID*) 8;
//							 break;
			 
						 default:
							 t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
							 pv_cmd_val = (VOID*) 0;
							 break;
					}
				  }
					 else
					 {
					 t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					 pv_cmd_val = (VOID*) 0;
					 }		  
				  break;
			  }  

			 case GET_PIC_MODE:
				 /*GET_PIC_MODE*/
				 t_cmd_type = Foxconn_FACTORY_GET_CMD_SELECT_PIC_MODE;
				 pv_cmd_val = (VOID*) 0;
				 break;
					 
			 case SET_COLORTEMP:
				switch(aui1_cmd_buf[5])
				{
					/* Select Color temp Cool */
					case COLORTEMP_Cool:
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_COOL, 0);
						break;
					/* Select Color temp Warm */
					case COLORTEMP_Warm1_6500K:
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_WARM, 0);
						break;
					/* Select Color temp Normal */
					case COLORTEMP_Normal:
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_NORMAL, 0);
						break;
					/* Select Color temp User */
					case COLORTEMP_User:
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SELECT_COLOR_TEMP_USER, 0);
						break;
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;
				}
				break;
					 
			case GET_COLORTEMP:
					/*GET_CT_MODE*/
					t_cmd_type = Foxconn_FACTORY_GET_CMD_SELECT_COLOR_TEMP;
					pv_cmd_val = (VOID*) 0;
					break;

			case SET_BRGHTNSS:
                if(aui1_cmd_buf[5]>100)
                {
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
                }else
				    FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_BRIGHTNESS, aui1_cmd_buf[5]);
				break;
				
			case GET_BRGHTNSS:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_GET_CMD_GET_BRIGHTNESS, 0);
				break;
			
			case SET_CONTRAST:
                if(aui1_cmd_buf[5]>100)
                {
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
                }else               
				    FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_CONTRAST, aui1_cmd_buf[5]);
				break;
				
			case GET_CONTRAST:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_GET_CMD_GET_CONTRAST, 0);
				break;

			case SET_BACKLIGHT:
                if(aui1_cmd_buf[5]>100)
                {
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
                }else               
				    FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_BACK_LIGHT, aui1_cmd_buf[5]);
				break;
				
			case GET_BACKLIGHT:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_GET_CMD_GET_BACK_LIGHT, 0);
				break;
			
			case SET_HUE:
                switch(aui1_cmd_buf[5])
                {
                    case 0 ... 0x32:
                    case 0xCE ... 0xFF:
				        FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_HUE, aui1_cmd_buf[5]);
                        break;

                    default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;                        
                        break;
                }
				break;

			case GET_HUE:
				/*GET_HUE*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_HUE;
				pv_cmd_val = (VOID*)0;
				break;
				
			case SET_COLOR:
                if(aui1_cmd_buf[5]>100)
                {
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
                }else
				    FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_COLOR, aui1_cmd_buf[5]);
				break;
					
			case GET_COLOR:
				/*GET_COLOR*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_COLOR;
				pv_cmd_val = (VOID*)0;
				break;
				
			case SET_SHARPNESS:
                if(aui1_cmd_buf[5]>100)
                {
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
                }else
				    FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_SHARPNESS, aui1_cmd_buf[5]);               
				break;
			
			case GET_SHARPNESS:
				/*GET_SHARPNESS*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_SHARPNESS;
				pv_cmd_val = (VOID*) 0;

			case SET_NR:
				switch(aui1_cmd_buf[5])
				{
					/* noise reduction -- Auto */
					case 0x01:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_NOISE_REDUCTION;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					/* noise reduction -- High */
					case 0x02:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_NOISE_REDUCTION;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					/* noise reduction -- Mid */
					case 0x03:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_NOISE_REDUCTION;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					/* noise reduction -- Low */
					case 0x04:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_NOISE_REDUCTION;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					/* noise reduction -- Off */
					case 0x05:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_NOISE_REDUCTION;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;
				}
				break;
				
			case GET_NR:
				/*GET_NR*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_NOISE_REDUCTION;
				pv_cmd_val = (VOID*) 0;
				break;

			case SET_MPEG_NR:
				switch(aui1_cmd_buf[5]) //20111110 sammi modified 
				{
					/* MEPG noise reduction -- off */
					case 0x01:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_MEPG_NR;
						pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[5];
						break;
					/* MEPG noise reduction -- Low */
					case 0x02:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_MEPG_NR;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					/* MEPG noise reduction -- Mid */
					case 0x03:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_MEPG_NR;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					/* MEPG noise reduction -- High */
					case 0x04:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_MEPG_NR;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;

					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;
				}
				break;
				
			case GET_MPEG_NR:
				/*GET_MPEG_NR*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_MEPG_NR;
				pv_cmd_val = (VOID*) 0;
				break;
				
			case SET_Motion_Flow:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_MOTION_FLOW;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case GET_Motion_Flow:
				/*GET_Motion_Flow*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_MOTION_FLOW;
				pv_cmd_val = (VOID*) 0;
				break;
			
			case SET_ACTIVE_LED_ZONE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_ACTIVE_LED_ZONE;
				pv_cmd_val = (VOID*)	&aui1_cmd_buf[5];								 
				break;

			case Motion_blur_Reduction:
				t_cmd_type = Foxconn_FACTORY_SET_CLEAR_ACTION;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];						 
				break;

			case SET_DBC_CONTROL:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_DBC_CONTROL;
				//pv_cmd_val = (VOID*)0;
				pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				break;
			
			case GET_DBC_CONTROL:
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_DBC_CONTROL;
				pv_cmd_val = (VOID*) (UINT32) aui1_cmd_buf[5];
				break;

			case SET_LIGHT_SENSOR__STATUS:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_LIGHT_SENSOR;
				pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[5];
				break;
			
			case GET_LIGHT_SENSOR__STATUS:
				/*GET_LIGHT_SENSOR__STATUS*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_LIGHT_SENSOR;
				pv_cmd_val = (VOID*) 0;
				break;

			case GET_LIGHT_SENSOR_LEVEL:
				// NT@CVT, 20120614, Light Sensor Level
				t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL;
				pv_cmd_val = (VOID*) 0;
				break;
		      // FXC_Jim 20180713 vvvvvv	
			case GET_LIGHT_SENSOR_LEVEL_TWOBYTES:
				// NT@CVT, 20120614, Light Sensor Level
				t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL_TWOBYTES;
				pv_cmd_val = (VOID*) 0;
				break;
			// FXC_Jim 20180713 ^^^^^^
	        case SET_Game_mode://FXC_WT@@20180627
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_GAME_MODE;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
		        break;

	        case SET_ADAPTIVE_LUMA_BLACK_DETAIL://FXC_WT@@20180627
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_ADAPTIVE_LUMA;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
		        break;
				
	        case GET_ADAPTIVE_LUMA_BLACK_DETAIL:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_ADAPTIVE_LUMA;
				pv_cmd_val = (VOID*) 0;
				break;
					
			case CAPTION_SW:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_CLOSE_CAPTION;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;
			
			case CAPTION_MODE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_CLOSE_CAPTION_MODE;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case SET_SND_RESET:
				/*SET_SND_RESET*/
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SOUND_RESET;
				pv_cmd_val = (VOID*) 0;
				break;

			case SET_SND_MODE:
				/*SET_SND_MODE*/
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_SOUND_MODE;
				pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[5];
				break;

			case GET_SND_MODE:
				/*GET_SND_MODE*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_SOUND_MODE;
				pv_cmd_val = (VOID*) 0;
				break;

			case SET_MTS:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_MTS;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case GET_MTS:
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_MTS;
				pv_cmd_val = (VOID*)0;
				break;

			case SET_VOLUME:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_VOLUME;//FACTORY_SET_CMD_SET_VOLUME;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case GET_VOLUME:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_VOLUME;//FACTORY_SET_CMD_GET_VOLUME;
				pv_cmd_val = (VOID*) 0;
				break;

			case SET_MUTE:
				//Cedric note: send 0: unmute 1: mute
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_MUTE_STATUS;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case GET_MUTE:
				/*GET_MUTE*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_MUTE_STATUS;
				pv_cmd_val = (VOID*) 0;
				break;

			case SET_AUDIO_OUT:
				/*SET_AUD_OUT*/
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_AUDIO_OUT;
				pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[5];
				break;

			case GET_AUDIO_OUT:
				/*GET_AUD_OUT*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_AUDIO_OUT;
				pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[5];
				break;

			case  SET_SP_MODE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_SP_MODE;
				pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[5];
				break;

			case GET_SP_MODE:
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_SP_MODE;
				pv_cmd_val = (VOID*) 0;
				break;

			case SET_SURROUND:
				switch(aui1_cmd_buf[5])
				{
					case 0x01:
						/* Surround On */										
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_AUDIO_SURR;
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
						break;
					case 0x00:	
					case 0x02:
						/* Surround Off */
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_AUDIO_SURR;
						//aui1_cmd_buf[5] = 0;	   
						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];	
						break;
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;
				}
				break;

			case SET_WIDE_MODE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_WIDEMODE;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case GET_WIDE_MODE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_WIDEMODE;
				pv_cmd_val = (VOID*)0;
				break;

			case SET_PC_WIDE_MODE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_PC_WIDEMODE;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case GET_PC_WIDE_MODE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_WIDEMODE;//Foxconn_FACTORY_GET_CMD_GET_PC_WIDEMODE;
				pv_cmd_val = (VOID*)0;
				break;

			case SET_LED_STATUE:
			switch(aui1_cmd_buf[5])
			{
				case 0x01:
					/*SET_LED_STATUE*/
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_STANDBY_LED;
					pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[6];
					// NT@CVT, 20120615
					if (aui1_cmd_buf[6] == 0)
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_STANDBY_LED_OFF;
					break;
					
				case 0x02:
					/*SET_LED_STATUE*/			
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_TIMER_AMBER_LED;
					pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[6];
					// NT@CVT, 20120615
					if (aui1_cmd_buf[6] == 0)
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_TIMER_AMBER_LED_OFF;
					break;
					
				case 0x03:
					/*SET_LED_STATUE*/
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_POWER_LED;
					pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[6];
					// NT@CVT, 20120615
					if (aui1_cmd_buf[6] == 0)
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_POWER_LED_OFF;
					break;
					
				default:
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
					break;
			}
			break;

			case GET_LED_STATUE:
				/*GET_LED_LEVEL*/			
				t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_LED_STATUS;
				pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[5];
				break;

			case FACTORY_RESET:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_RESET_NVRAM_FACTORY_DEFAULT;
				pv_cmd_val = (VOID*) 0; 			
				break;

			case SET_SKIP_INITIAL:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_SKIP_INITIAL;
				pv_cmd_val = (VOID*) 0;
				break;

			case Set_Store_Demo:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_STORE_DEMO;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case DISPLAY_MENU:
				/* Menu On */
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_MENU);
				break;
			
			case SET_IR_KEY:
               	//DBG_INFO(("\n --------------------------------IR----------------------------------- \n"));
				switch(aui1_cmd_buf[5])
				{
					case 0x01:
						/* CURSOR_UP */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_CURSOR_UP);
						break;
					case 0x02:
						/* CURSOR_DOWN */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_CURSOR_DOWN);
						break;
					case 0x03:
						/* CURSOR_LEFT */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_CURSOR_LEFT);                       
						break;
					case 0x04:
						/* CURSOR_RIGHT */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_CURSOR_RIGHT);                        
						break;
					case 0x05:
						/* PRG_UP */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_PRG_UP);                       
						break;
					case 0x06:
						/* PRG_DOWN */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_PRG_DOWN);                      
						break;
					case 0x07:
						/* MTS */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_MTS);                      
						break;
					case 0x08:
						/* CC */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_CC);                       
						break;
					case 0x09:
						/*WIDE_MODE */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_ASPECT);                      
						break;
					case 0x0a:
						/*TOOLS */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_TOOLS);                       
						break;
					case 0x0b:
						/* IR Key "0"  */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_0);                      
						break;
					case 0x0c:
						/* IR Key "1"  */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_1);                       
						break;	
					case 0x0d:
						/* IR key "2" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_2);                     
						break;
					case 0x0e:
						/* IR key "3" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_3);                 
						break;					
					case 0x0f:
						/* IR key "4" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_4);                      
						break;
					case 0x10:
						/* IR key "5" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_5);                    
						break;
					case 0x11:
						/* IR key "6" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_6);                      
						break;
					case 0x12:
						/* IR key "7" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_7);                      
						break;
					case 0x13:
						/* IR key "8" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_8);                      
						break;
					case 0x14:
						/* IR key "9" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_9);                       
						break;
					case 0x15:
						/* IR key "." */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_DIGIT_DOT);                     
						break;
					case 0x16:
						/* IR key "ENT" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_SELECT);                      
						break;
					case 0x17:
						/* IR key "POWER OFF" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_POWER_OFF);                       
						break;
					case 0x18:
						/* IR key "Vol UP" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_VOL_UP);                      
						break;
					case 0x19:
						/* IR key "Vol Down" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_VOL_DOWN);                       
						break;
					case 0x20:
						/* IR key "Menu" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_MENU);                       
						break;					
					case 0x21:
						/* IR key "Exit" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_EXIT);                      
						break;					
					case 0x22:
						/* IR key "Back" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_RETURN);                     
						break;
					case 0x23:
						/* IR key "Info" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_PRG_INFO);                      
						break;
					case 0x24:
						/* IR key "INPUT" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_INPUT_SRC);                      
						break;					
					case 0x25:
						/* IR key "MUTE" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_MUTE);                     
						break;					
					case 0xE0:
						/* IR key "POWER OFF" */
						FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_PRESS_RCU_BUTTON, BTN_EXIT); 	                     
						break;
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;
				}
				break;
			
			case SET_DHCP_DEF: //Tommy 20210928
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_DHCP_DEF;
				pv_cmd_val = (VOID*) 0;
				break;
			
			case SET_WIFI_ANTENNA : 
				FACTORY_SEND_CMD(0x01, Foxconn_FACTORY_SET_CMD_SET_WIFI_ANTENNA, aui1_cmd_buf[5]); 							   
				break;
				
			case SET_CONNECT_WIFI:
//				t_cmd_type = FACTORY_SET_CMD_SET_CONNECT_WIFI;	// Kide 120620 marked
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_WIFI_CONNECTION;	// Kide 120620 add
				pv_cmd_val = (VOID*)& aui1_cmd_buf[4];
				break;

			case CHECK_WIFI_STATUS:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_WIFI_STATUS ;
				pv_cmd_val = (VOID*) 0;
				break;

			case GET_WIFI_RSSI:	// Kide 120620
				if((ui2_UART_DataLength == 0) ) // yuan 2013 0102 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_WIFI_RSSI;
					pv_cmd_val = (VOID*) 0;
				}
				break;

			case Get_BT_Mac_Addr:	//Tommy 20201224
				t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR;	
				pv_cmd_val = (VOID*) 0;
				break;

			case Get_BT_Rssi:		//Tommy 20200424
				if (ui2_UART_DataLength == 0 || ui2_UART_DataLength == 7) 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI;	
					pv_cmd_val = (VOID*)& aui1_cmd_buf[4];
				}
				break;
				
			case SET_DIRECT_TUNNING:
				if (ui2_UART_DataLength == 2) 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_DIRECT_TUNE;
					pv_cmd_val = (VOID*) 0;
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;
// FXC_Jim 2018_0331 vvvvv
			case GET_TUNING_STATUS:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_GET_TUNING_STATUS, 0); 							   
				break;		
// FXC_Jim 2018_0331 ^^^^^^
			case GET_SIGNAL_STATUS:
				if (ui2_UART_DataLength == 0) 
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECK_SIGNAL;//20111126 sammi modified
					pv_cmd_val = (VOID*) 0;
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;	
				}
				break;

			case CHECK_USB_DEVICE://20120209 add for USB device 
				t_cmd_type = Foxconn_FACTORY_SET_CMD_FAC_GET_USB_STATUS;
				pv_cmd_val = (VOID*) 1; 		
				break;

			case SET_Gamma_INTERNAL_PATTERN:		//Tommy 20180413
				if (ui2_UART_DataLength == 7)
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_WHITE_PATTERN;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
					break;
				
			case SET_WB_INTERNAL_PATTERN:			//Tommy 20180413
				if (ui2_UART_DataLength == 7)
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_WB_WHITE_PATTERN;
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5];
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;
// FXC_Jim 2018_0331 vvvvvv
				case SET_AUTO_POWER_OFF_TIME://FXC_WT@@20180328
				switch(aui1_cmd_buf[5])
				{
					case 0x00:	
					case 0x01:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_AUTO_POWER_OFF_TIME;
						pv_cmd_val = (VOID*)(UINT32) aui1_cmd_buf[5];
						break;

					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;						
						pv_cmd_val = (VOID*) 0;
						break;
				}
				break;

				case SET_HDMI_CONTROL://FXC_WT@@20180328
									t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_ARC_ON_OFF;
									pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
									break;
// FXC_Jim 2018_0331 ^^^^^^
			case SET_CEC_STATUS:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_CONTROL_CEC;
				pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				break;

			case GET_CEC_STATUS:
				/*GET_CEC_STATUS*/
				t_cmd_type = Foxconn_FACTORY_GET_CMD_GET_CONTROL_CEC;
				pv_cmd_val = (VOID*) 0;
				break;

			case SET_KEY_LOCK://20111126 sammi move from A1 to 80 
			// NT@CVT, 20120615
			//t_cmd_type = FACTORY_SET_CMD_SET_KEY_LOCK;
			//pv_cmd_val = (VOID*)&aui1_cmd_buf[5];
				switch (aui1_cmd_buf[5])
				{
					case 0x01:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_RC_LOCK;
						pv_cmd_val = (VOID*) 0;
						break;
					case 0x02:
						t_cmd_type = Foxconn_FAATORY_SET_CMD_SET_RC_UNLOCK;
						pv_cmd_val = (VOID*) 0;
						break;
					case 0x03:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_KP_LOCK;
						pv_cmd_val = (VOID*) 0;
						break;
					case 0x04:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_KP_UNLOCK;
						pv_cmd_val = (VOID*) 0;
						break;									  
				}
				break;

			case GET_SIRCS_CATEGORY://FXC_WT@@20180410
				switch(aui1_cmd_buf[3])
				{
					case 0x00:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_IR_CODE;
						pv_cmd_val = (VOID*)0;
						break;
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
					break;
				}
				break;

			case SET_RATING:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_PARENT_RATING;
				pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[5];
				break;

			case WRITE_AUDIO_BALANCE:
				t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_AUDIO_BALANCE;
				pv_cmd_val = (VOID*) (UINT32)aui1_cmd_buf[5];
				break;

//End =============================================//WT@@20180313/0314/0315/0316
// FXC_Jim 2018_0331 vvvvvv

			case Vcom_Internal_Pattern:
				{
#if 1
					if (ui2_UART_DataLength == 193)
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_FULL_VCOM_INTERNAL_PATTERN;
					else if (ui2_UART_DataLength == 1)
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_VCOM_INTERNAL_PATTERN;
					else
					{
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;
					}
						
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5]; 
				

#else
					switch (aui1_cmd_buf[3])
					{
						case 0x00 :
							if (aui1_cmd_buf[4] == 0x03)	
							{
								t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_ENABLE_VCOM_INTERNAL_PATTERN;
								pv_cmd_val = (VOID*) &aui1_cmd_buf[5]; 
							}
							else if (aui1_cmd_buf[4] == 0x01)
							{   //C0 91 01 00 01 00
								if (aui1_cmd_buf[5] == 0x00)
									t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_DISABLE_VCOM_INTERNAL_PATTERN;
								else
									t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_ENABLE_VCOM_INTERNAL_PATTERN;
								pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
							}
							break;
							
						case 0x01:
							if (aui1_cmd_buf[4] == 0x01)
							{
								t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_ENABLE_VCOM_INTERNAL_PATTERN;
								pv_cmd_val = (VOID*) 0;
							}
							else if (aui1_cmd_buf[4] == 0x00)
							{
								t_cmd_type = Foxconn_FACTORY_SET_CMD_CUST_DISABLE_VCOM_INTERNAL_PATTERN;
								pv_cmd_val = (VOID*)0;
							}
							else if (aui1_cmd_buf[4] == 0x02)
							{
								t_cmd_type = Foxconn_FACTORY_SET_CMD_ENABLE_SPECIAL_PATTERN;//WT@20150521
								pv_cmd_val = (VOID*) 0;
								break;                
							}
							else if (aui1_cmd_buf[4] == 0x03)
							{
								t_cmd_type =Foxconn_FACTORY_SET_CMD_DISABLE_SPECIAL_PATTERN;//WT@20150521
								pv_cmd_val = (VOID*) 0;
								break;                
							}                
							else
							{
								t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
								pv_cmd_val = (VOID*) 0;      
							}
							break;

						default:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
							pv_cmd_val = (VOID*) 0;      
							break;
					}
#endif					
				}
				break;

			case VCOM_IMPLEMENTATION:
				DBG_INFO(("VCOM_IMPLEMENTATION  Start \n"));
				t_cmd_type = Foxconn_FACTORY_SET_CMD_VCOM_IMPLEMENTATION;
				pv_cmd_val = (VOID*) (UINT32)& aui1_cmd_buf[4];
				break;


			case I2C_IMPLEMENTATION:	//Tommy 20200615
				DBG_INFO(("VCOM_IMPLEMENTATION	Start \n"));
				t_cmd_type = Foxconn_FACTORY_SET_CMD_I2C_IMPLEMENTATION;
				pv_cmd_val = (VOID*) (UINT32)& aui1_cmd_buf[4];
				break;
// FXC_Jim 2018_0331 ^^^^^^

			case SET_CT_DATA:		//Tommy 20180410
//				DBG_INFO(("\n <fact_parser>SET_CT_DATA 0x72  \n"));
				if (ui2_UART_DataLength == 3) 
				{
					UINT32 tmp1, tmp2;
					tmp1 =((UINT32)aui1_cmd_buf[6]<<6 )&0xC0;
					tmp2 =((UINT32)aui1_cmd_buf[7] >>2 )&0x3F; 
//					DBG_INFO(("\n <fact_parser>ui2_UART_DataLength 3   \n"));
					pv_cmd_val=  (VOID*)(UINT32)( tmp1+tmp2) ;										
//					DBG_INFO("<factory> pv_cmd_val :%x, %x, %x\n", aui1_cmd_buf[6], aui1_cmd_buf[7], pv_cmd_val);


					switch(aui1_cmd_buf[5])
					{    
						case 0x01:	
							t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED;	
							DBG_INFO(("\n <fact_parser>Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_RED  \n")); 
							break;
						case 0x02:  
							t_cmd_type =  Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_GREEN;	
							break;
						case 0x03:	
							t_cmd_type =  Foxconn_FACTORY_SET_CMD_SET_COLOR_GAIN_BLUE;	
							break;
						case 0x04:	
							t_cmd_type =  Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_RED;	
							break;
						case 0x05:	
							t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_GREEN;	
							break;
						case 0x06:	
							t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_COLOR_OFFSET_BLUE;		
							break;	
						default:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
							pv_cmd_val = (VOID*) 0;
							break;
					}						
					break;
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break; // SET_CT_DATA		

			case GET_CT_DATA:
				if (ui2_UART_DataLength == 1) 
				{
					switch(aui1_cmd_buf[5])
					{
						case 0x01:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_RED;
							pv_cmd_val = (VOID*) 0;
							break;
						case 0x02:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_GREEN;
							pv_cmd_val = (VOID*) 0;
							break;
						case 0x03:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_BLUE;
							pv_cmd_val = (VOID*) 0;
							break;
						case 0x04:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_RED;
							pv_cmd_val = (VOID*) 0;
							break;
						case 0x05:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_GREEN;
							pv_cmd_val = (VOID*) 0;
							break;
						case 0x06:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_BLUE;
							pv_cmd_val = (VOID*) 0;
							break;
						default:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
							pv_cmd_val = (VOID*) 0;
							break;
					}
				}
				break; //GET_CT_DATA

#ifdef FAC_BACKLIGHT_CHECK //Add Tommy 20210923
			case Set_Backlight_Individual_Zone_Check:
				if (ui2_UART_DataLength == 0)
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_BACKLIGHT_ZONE_CHECK;
					pv_cmd_val = (VOID*) 0; 			
				}
				else
				{
					t_cmd_type =Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;
#endif        
#if 1
// FXC_Jim 2018_0331vvvvvv
			case GET_POWER_ON_TIME:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_GET_POWERONTIME, 0); 							   
				break;
			
			case GET_ETHERENT_STATUS:/*SET_ETHERNET_MAC_ADDR*/
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_CHECK_ETHERNET_STATUS, 0); 							   
				break;   // FXC Jim 2018 0410 
				
		    case Get_FREQUENCY:
				FACTORY_SEND_CMD(0x00, Foxconn_FACTORY_SET_CMD_GET_VIDEO_FREQ, 0); 							   
				break;
// FXC_Jim 2018_0331 ^^^^^^		
			case SET_AGING_MODE:
				DBG_INFO(("\n <fact_parser>SET_AGING_MODE 3   \n"));
				if (ui2_UART_DataLength == 1)
				{
					switch(aui1_cmd_buf[5])
					{
						case 0x01:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_BURN_OFF;
							pv_cmd_val = (VOID*) 0; 			
							break;
						case 0x02:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_BURN_ON;
							pv_cmd_val = (VOID*) 0; 			
							break;
						case 0x03 : 
							t_cmd_type = Foxconn_FACTORY_SET_CMD_BURN_ON_WITH_WHITE_PATTERN;
							pv_cmd_val = (VOID*) 0;                                                                     
							break;
						default:
							t_cmd_type =Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
							pv_cmd_val = (VOID*) 0;
							break;
					}
					break;
				}
				else
				{
					t_cmd_type =Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;

				case GET_AGING_STATUS://FXC_WT@@20180614					
					switch(aui1_cmd_buf[3])
						{
						case 0x00:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_BURN_STATUS;
									pv_cmd_val = (VOID*) 0;
									break;
						default:
							t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
							pv_cmd_val = (VOID*) 0;
							break;
						}
						break;
						
				 case SET_HDR_NITS_VALUE://20120131 sammi add
					if (ui2_UART_DataLength ==  2 )
					{
#if 0 //From TPV
							UINT8   ui1_i;
							for(ui1_i=0; ui1_i<3; ui1_i++)
							{
								aui1_cmd_buf[ui1_i] = aui1_cmd_buf[8+ui1_i];
							}
#endif
							t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_HDR_NITS;
							pv_cmd_val = (VOID*)((UINT16)(aui1_cmd_buf[5] << 8) +   // [1]:high byte,
										(UINT16) aui1_cmd_buf[6]);		  // [2]:low byte
//							pv_cmd_val = (VOID*) &aui1_cmd_buf[5]; 
				 	}
					else
					{
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
					}
					break; 				
				
				case GET_HDR_NITS_VALUE:																																																																																																																																																																																																														
					if (ui2_UART_DataLength == 0 )
					{
						DBG_INFO(("\n <fact_parser>ui2_UART_DataLength  = %d\n", ui2_UART_DataLength));
						t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_HDR_NITS;
						pv_cmd_val = (VOID*) 0;
					}
					else
					{
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
					}
					break;			

				case GET_VIDEO_TIMMING:
					if (ui2_UART_DataLength == 0 )
					{
						t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_VIDEO_TIMING;
						pv_cmd_val = (VOID*) 0;
					}
					else
					{
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
					}
					break;		
				 
			case GET_APL_VALUE:																																																																																																																																																																																																														
				 if (ui2_UART_DataLength == 0 )
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_APL_VALUE;
					pv_cmd_val = (VOID*) 0;
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;
					
			case DETECT_HDMI_CABLE:
				if (ui2_UART_DataLength == 1 )
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_HDMI_CABLE_DET;
					// yuan 2012 0717 pv_cmd_val = (VOID*) 0;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}	

				break;	
				
			case SET_LOCAL_DIMMING://20120131 sammi add
				if (ui2_UART_DataLength == 1 )
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_FAC_LOCAL_DIMMING;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[5];
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;                            
				
				case 0x3d:
				switch(aui1_cmd_buf[3])
					{
					case 0x00:
								t_cmd_type = Foxconn_FACTORY_SET_CMD_SET_FFA;
								//   pv_cmd_val = (VOID*)0;
								pv_cmd_val = (VOID*) &aui1_cmd_buf[4]; // yuan 2012 0716
								break;
							default:
								t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
								pv_cmd_val = (VOID*) 0;
								break;
							}						
						break;                       
			case 0x3e:
				switch(aui1_cmd_buf[3])
					{
					case 0x00:
								t_cmd_type = Foxconn_FACTORY_SET_CMD_GET_FFA;
								// pv_cmd_val = (VOID*)0;
								pv_cmd_val = (VOID*) &aui1_cmd_buf[5]; // yuan 2012 0716
								break;
							default:
								t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
								pv_cmd_val = (VOID*) 0;
								break;
							}
						break;				
			//Boi20180306 Boitest
			//Boi20180306 Boitest
			case WRITE_GAMMA_17_AND_33_POINT:
				DBG_INFO(("\n <fact_parser>WRITE_GAMMA_17_AND_33_POINT  = %d\n", ui2_UART_DataLength));
				  if (ui2_UART_DataLength == 18 ) // ||ui2_UART_DataLength == 34  )
				  
				{				
					t_cmd_type = Foxconn_FACTORY_SET_CMD_WRITE_GAMMA_TABLE_USING_TEST; // Boitest
					DBG_INFO(("<fact_parser> Foxconn_FACTORY_SET_CMD_WRITE_GAMMA_TABLE_USING_TEST\n"));
					pv_cmd_val = (VOID*) &aui1_cmd_buf[5]; //colby@191128
				}
				else
				{
					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				}
				break;
				  
			case LOAD_GAMMA_TABLE:
				switch(aui1_cmd_buf[3])//20111025 sammi modified 
					{
					case 0x00:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_GAMMA_TABLE;
						pv_cmd_val = (VOID*)1;
						break;
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;	
					}
					break;
				
			case Get_HDCP_BKSV: //colby@191206 check hdcp vaild
					t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD;
					pv_cmd_val = (VOID*)&aui1_cmd_buf[5];
                    break;
#if 0 //colby@191209 ksv function    
				switch(aui1_cmd_buf[5])//20111025 sammi modified 
					{
					case 0x00:
				    {                     
                        if(a_cfg_custom_HDCPX_vaild(0x00)==

					t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
					pv_cmd_val = (VOID*) 0;
				    }
                     
						t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_14_KSV;
						pv_cmd_val = (VOID*)1;
						break;
					case 0x01:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_22_ID;
						pv_cmd_val = (VOID*)1;
						break;						
					default:
						t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
						pv_cmd_val = (VOID*) 0;
						break;	
					}
#endif					
					break;			

					
#endif
			
		}// Foxconn Factory command
	}
	else
	{
		  t_cmd_type = Foxconn_FACTORY_SET_CMD_CHECKSUM_ERROR;
		  pv_cmd_val = (VOID*) 0;
/*======================== Tommy 0301 Start==============================*/
		  Factory_Return_NOT_SUPPORT();
/*======================== Tommy 0301 End==============================*/
	}				
	
	if (b_do_common_set_cmd)
	{
		switch(t_cmd_type)		
		{
			case Foxconn_FACTORY_GET_CMD_GET_DBC_CONTROL://WT@@20180315 ADD
				ui2_cmd_return_type = Foxconn_FACTORY_GET_CMD_GET_DBC_CONTROL;
				break;
			case Foxconn_FACTORY_READ_CMD_EDID_SERIAL_NUM:
			case Foxconn_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR:
			case Foxconn_FACTORY_SET_CMD_GET_ULPK_KEY:
			case Foxconn_FACTORY_SET_CMD_GET_POTK_KEY:
				//ui2_cmd_return_type = TPV_FACTORY_READ_CMD_EDID_SERIAL_NUM;
				ui2_cmd_return_type =(UINT16) t_cmd_type;
				break;
			case Foxconn_FACTORY_SET_CMD_GET_SOURCE_TYPE:
			case Foxconn_FACTORY_SET_CMD_GET_MODEL_INDEX:
			case Foxconn_FACTORY_GET_CMD_SELECT_PIC_MODE:
			case Foxconn_FACTORY_GET_CMD_SELECT_COLOR_TEMP:
			case Foxconn_FACTORY_GET_CMD_GET_BRIGHTNESS:
			case Foxconn_FACTORY_GET_CMD_GET_CONTRAST:
			case Foxconn_FACTORY_GET_CMD_GET_BACK_LIGHT:
			case Foxconn_FACTORY_GET_CMD_GET_COLOR:
			case Foxconn_FACTORY_GET_CMD_GET_HUE:
			case Foxconn_FACTORY_GET_CMD_GET_SHARPNESS:
			case Foxconn_FACTORY_GET_CMD_GET_NOISE_REDUCTION:
			case Foxconn_FACTORY_GET_CMD_GET_MEPG_NR:
			case Foxconn_FACTORY_GET_CMD_MOTION_FLOW:
			case Foxconn_FACTORY_GET_CMD_GET_LIGHT_SENSOR:
			case Foxconn_FACTORY_SET_CMD_GET_WIDEMODE:
			case Foxconn_FACTORY_SET_CMD_GET_LED_STATUS:
			case Foxconn_FACTORY_GET_CMD_GET_SOUND_MODE:
			case Foxconn_FACTORY_GET_CMD_GET_MTS:
			case Foxconn_FACTORY_SET_CMD_READ_VOLUME:
			case Foxconn_FACTORY_GET_CMD_GET_MUTE_STATUS:
			case Foxconn_FACTORY_GET_CMD_GET_AUDIO_OUT:
			case Foxconn_FACTORY_GET_CMD_GET_SP_MODE:
			case Foxconn_FACTORY_GET_CMD_GET_CONTROL_CEC:
			case Foxconn_FACTORY_SET_CMD_GET_APL_VALUE:
			case Foxconn_FACTORY_SET_CMD_GET_VIDEO_TIMING:
			case Foxconn_FACTORY_SET_CMD_GET_HDMI_CABLE_DET: 
			case Foxconn_FACTORY_SET_CMD_FAC_GET_USB_STATUS: 
			case Foxconn_FACTORY_SET_CMD_CHECK_SIGNAL:	
			case Foxconn_FACTORY_SET_CMD_GET_WIFI_STATUS:
			case Foxconn_FACTORY_SET_CMD_READ_KEYPAD_POWER:				//Tommy 20180322
			case Foxconn_FACTORY_SET_CMD_CHECK_POTK_INDEX:
			case Foxconn_FACTORY_SET_CMD_GET_BURN_STATUS:
// FXC_Jim 2018_0331vvvvv
			case Foxconn_FACTORY_SET_CMD_GET_VIDEO_FREQ:    // FXC_Jim 20180328
//			case Foxconn_FACTORY_SET_CMD_SET_DIRECT_TUNE:
			case Foxconn_FACTORY_SET_CMD_GET_TUNING_STATUS :
			case Foxconn_FACTORY_SET_CMD_CHECK_ETHERNET_STATUS:
			case Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL:
			case Foxconn_FACTORY_SET_CMD_GET_ADAPTIVE_LUMA://FXC_WT@@20180627
// FXC_Jim 2018_0331 ^^^^^^
				ui2_cmd_return_type =(UINT16)Foxconn_FACTORY_CMD_GET_RETURN_ONE_BYTE;
				break;
			case Foxconn_FACTORY_SET_CMD_READ_KEYPAD_ADC_VALUE: 			//Tommy 20180329
			case Foxconn_FACTORY_SET_CMD_GET_MODEL_GROUP:	  // FXC_Jim 20180713
			case Foxconn_FACTORY_SET_CMD_CUST_READ_LIGHT_SENSOR_LEVEL_TWOBYTES: // FXC_Jim 20180713

				ui2_cmd_return_type =(UINT16)Foxconn_FACTORY_CMD_GET_RETURN_TWO_BYTE;
				break;
			case Foxconn_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR:
				ui2_cmd_return_type =(UINT16)Foxconn_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR;
				break;
			case Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR:	//Tommy 20201224
				ui2_cmd_return_type =(UINT16)Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR;
				break;
			case Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI:	//Tommy 20201224
				ui2_cmd_return_type =(UINT16)Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI;
				break;
			case Foxconn_FACTORY_SET_CMD_FAC_READ_EDID:
				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_FAC_READ_EDID; 				
				break;
			case Foxconn_FACTORY_SET_CMD_FAC_READ_EDID_512: //WT@20210122
				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_FAC_READ_EDID_512;				
				break;				
		    case Foxconn_FACTORY_SET_CMD_READ_HDCP_14_DATA://FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV:
			     ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_14_DATA;
				 break;
		    case Foxconn_FACTORY_SET_CMD_READ_HDCP_2X_DATA://FXC_WT@@20180419//Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV:
			     ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_2X_DATA;
				 break;		
			case Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD:
//				DBG_INFO(("\n <factory> ui2_cmd_return_type----------------------------- \n"));                
				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD;
				break;
            case Foxconn_FACTORY_SET_CMD_POWER_OFF: //colby@191223            
                 ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_POWER_OFF;
                 break;                 
            case Foxconn_FACTORY_SET_CMD_NOT_SUPPORT: //colby@191223
                 ui2_cmd_return_type = FACTORY_NOSUPPORT_RETURN;
                 break;                
//		    case Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV:
//			     ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV;
//				 break;
			case Foxconn_FACTORY_SET_CMD_READ_SW_VER:
				 ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_SW_VER;			   
				 break;
			case Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE ://WT@@20180320
				ui2_cmd_return_type = (UINT16) Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE; 		
				break;		
			case Foxconn_FACTORY_GET_CMD_EEPROM_LOAD ://colby@200120
				ui2_cmd_return_type = (UINT16) Foxconn_FACTORY_GET_CMD_EEPROM_LOAD; 		
				break;	                
            case Foxconn_FACTORY_SET_CMD_GET_IR_CODE://FXC_WT@@20180410
				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_GET_IR_CODE;
			break;			
			// yuan vvvvv
// FXC_Jim 2018_0331 vvvvv
		case Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_T:
		case Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_P : 
                  ui2_cmd_return_type =   Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_P;
			break;
		case Foxconn_FACTORY_SET_CMD_GET_POWERONTIME : 
			ui2_cmd_return_type =  Foxconn_FACTORY_SET_CMD_GET_POWERONTIME;
			break;

		case Foxconn_FACTORY_SET_CMD_I2C_IMPLEMENTATION:	//Tommy 20200615
		case Foxconn_FACTORY_SET_CMD_VCOM_IMPLEMENTATION:
			if (aui1_cmd_buf[5]== 0x00)
				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_VCOM_IMPLEMENTATION;
//			else
//				ui2_cmd_return_type =Foxconn_FACTORY_CMD_GET_RETURN_ONE_BYTE;
			break;	
		case Foxconn_FACTORY_SET_CMD_READ_HDCP_14_KSV:
				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_14_KSV;
				break;
		case Foxconn_FACTORY_SET_CMD_READ_HDCP_22_ID:	
				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_HDCP_22_ID;
				break;
// FXC_Jim 2018_0331 ^^^^^^
			case  Foxconn_FACTORY_SET_CMD_READ_GAMMA_TABLE:

				ui2_cmd_return_type = Foxconn_FACTORY_SET_CMD_READ_GAMMA_TABLE;
				break;

			case Foxconn_FACTORY_SET_CMD_GET_HDR_NITS : 
				ui2_cmd_return_type = Foxconn_FACTORY_CMD_GET_RETURN_TWO_BYTE;
				break;

			case Foxconn_FACTORY_SET_CMD_GET_FFA : 
				ui2_cmd_return_type =Foxconn_FACTORY_SET_CMD_GET_FFA;
				break;

			case Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_RED:
			case Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_GREEN:
			case Foxconn_FACTORY_SET_CMD_READ_COLOR_GAIN_BLUE:
			case Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_RED:
			case Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_GREEN:
			case Foxconn_FACTORY_SET_CMD_READ_COLOR_OFFSET_BLUE:
				ui2_cmd_return_type =Foxconn_FACTORY_SET_CMD_READ_WB_DATA;
				break;

			case Foxconn_FACTORY_SET_CMD_GET_WIFI_RSSI:  // yuan 2013 0102 
				ui2_cmd_return_type =Foxconn_FACTORY_SET_CMD_GET_WIFI_RSSI;
				break;
						 
			// yuan ^^^^^
			default:
				ui2_cmd_return_type=Foxconn_FACTORY_CMD_RETURN_DEFAULT;
				/* do nothing */
			break;	   
	
		}
		
		if (a_Foxconn_factory_set_cmd(t_cmd_type,
							  pv_cmd_val,
							  _fact_parser_set_cmd_nfy,
							  pv_tag ) != FACTORYR_OK)
		{
						//  Printf("<fact_parser> Set command to factory daemon fails\n");
			Factory_Return_NACK();
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
	//UINT8       ui1_i;
	//UINT8       aui1_ret_buf[CMD_LEN_Maximum] ={0};
	IOM_UART_T  t_iom_uart;

	c_memset( &t_iom_uart, 0, sizeof(IOM_UART_T));  //ke_vizio_20110330 for clean warning.

	//WT@@20180213
	//IOM_UART_T  t_iom_uart;
	//const CHAR* Ps_Temp;
	UINT8		aui1_ret_buf[260],aui1_com[1600]={0};	// Kide 120626 256->260
	UINT16	   ui2_i=0,ui2_j=0;
	//UINT8	   ui1_x=0;/*,ui1_checksum=0;*/
	//UINT32 /*ui4_int_data,ui4_com_data,*/ui4_check_sum=0;//cox110323
#ifdef LINUX_TURNKEY_SOLUTION // 20110901, Danny add new cmd
	//	  UINT32	idfile_size =0;
#endif

	//Printf("<fact_parser>set command return value\n");

	if (ui2_delay_conut!=0)
	{
		x_thread_delay(ui2_delay_conut);
		ui2_delay_conut=0;
	}
	
	if (((UINT32)pv_tag) == FACTORY_CMD_ERROR_REP)/*Error Handle*/
	{
		aui1_com[0] = (UINT8)0x1;
		aui1_com[1] = (UINT8)0x0;
		aui1_com[2] = (UINT8)0x0;
		aui1_com[3] = (UINT8)0x0;
		aui1_com[4] = _gen_checksum(aui1_com, 4 ); //Tommy 20201013
//		while(ui2_j<4)
//		{
//			ui4_check_sum+= aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<5 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = 1;
			ui2_i++;
#if 0
			if (ui2_i>0xff)
			{
				c_dbg_stmt("buffer overflow \n");
				return;
			}
#endif
			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
		return;
	}
	else if(((UINT32)pv_tag) == FACTORY_NOSUPPORT_RETURN)
	{
		aui1_com[0] = (UINT8)0x1;
		aui1_com[1] = (UINT8)0x1;
		aui1_com[2] = (UINT8)0x0;
		aui1_com[3] = (UINT8)0x0;
		aui1_com[4] = _gen_checksum(aui1_com, 4 ); //Tommy 20201013
//		while(ui2_j<4)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<5 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = 1;
			ui2_i++;
#if 0
			if (ui2_i>0xff)
			{
				c_dbg_stmt("buffer overflow \n");
				return;
			}
#endif
			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
		return;
	}
	
	if (ui2_cmd_return_type ==Foxconn_FACTORY_SET_CMD_EDID_SERIAL_NUM)
	{
		DBG_INFO(("<factory_return> Set Serial Number\n"));
#if 1 //googol@111202,[Factory command] ULPK and ESN write/read function link.
		if(((Foxconn_FACTORY_COND_TYPE_T)(UINT32)pv_val)==Foxconn_FACTORY_COND_OK)
		{
			aui1_ret_buf[0] = 's';
			aui1_ret_buf[1] = 's';
			aui1_ret_buf[2] = 'n';
			t_iom_uart.z_len = 3;
			c_iom_output(h_iom_uart, &t_iom_uart);				
		}
		else
		{
			aui1_ret_buf[0] = 'n';
			aui1_ret_buf[1] = 'g';
			t_iom_uart.z_len = 2;
			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
#endif
	}		
	else if (ui2_cmd_return_type == Foxconn_FACTORY_READ_CMD_EDID_SERIAL_NUM)
	{ 	
		DBG_INFO(("<factory_return> Get Serial Number\n"));
		//if(((FACTORY_COND_TYPE_T)(UINT32)pv_val)==FACTORY_COND_OK)
		{
			int j;
			aui1_ret_buf[0] = 0x00;
			aui1_ret_buf[1] = 0x01;
			aui1_ret_buf[2] = 0x00;
			aui1_ret_buf[3] = 0x0F;
			for(j=0;j<LEN_SERIAL_NUMBER;j++) 
			{
				//DBG_INFO("%02x\n", aui1_faccmd_buf[j]);
			}

			for(j=0;j<LEN_SERIAL_NUMBER;j++) 
			{
				aui1_ret_buf[j+4] = aui1_faccmd_buf[j]; 
			}
			for(j=0;j<LEN_SERIAL_NUMBER;j++) 
			{
				//DBG_INFO("%02x\n", aui1_ret_buf[j]);
			} 	  
			aui1_ret_buf[LEN_SERIAL_NUMBER + 4] = _gen_checksum(aui1_ret_buf, LEN_SERIAL_NUMBER + 4);//yuan 2012 0625 
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = LEN_SERIAL_NUMBER + 4+1;
			c_iom_output(h_iom_uart, &t_iom_uart);		  
		}
	}
	else  if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_WIRED_ETHERNET_MAC_ADDR|| 
			ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_WIFI_MAC_ADDR||
			ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_MAC_ADDR)	//Tommy 20201224
	{
		printf("<factory_return> Get MAC\n");
		if (aui1_faccmd_buf[0] == 0 && aui1_faccmd_buf[1] == 0 && aui1_faccmd_buf[2] == 0
			&& aui1_faccmd_buf[3] == 0 && aui1_faccmd_buf[4] == 0 && aui1_faccmd_buf[5] == 0 )
		{
			aui1_com[0] = (UINT8)0x1;
			aui1_com[1] = (UINT8)0x1;
			aui1_com[2] = (UINT8)0x0;
			aui1_com[3] = (UINT8)0x0;
			aui1_com[4] = _gen_checksum(aui1_com, 4 ); //Tommy 20201013
//			while(ui2_j<4)
//			{
//				ui4_check_sum += aui1_com[ui2_j];
//				ui2_j++;
//			}
//			aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
			while ( ui2_i<5 )
			{
				aui1_ret_buf[0]=aui1_com[ui2_i];
				t_iom_uart.pui1_data = aui1_ret_buf;
				t_iom_uart.z_len = 1;
				ui2_i++;
				c_iom_output(h_iom_uart, &t_iom_uart);	 
			}
			return;
		}
		else
		{
			aui1_com[0] = 0x00;
			aui1_com[1] = 0x01;
			aui1_com[2] = 0x00;
			aui1_com[3] = 0x06;
			aui1_com[4] = aui1_faccmd_buf[0];
			aui1_com[5] = aui1_faccmd_buf[1];
			aui1_com[6] = aui1_faccmd_buf[2];
			aui1_com[7] = aui1_faccmd_buf[3];
			aui1_com[8] = aui1_faccmd_buf[4];
			aui1_com[9] = aui1_faccmd_buf[5];
			aui1_com[10] = _gen_checksum(aui1_com, 10 ); //Tommy 20201013

//			while(ui2_j<10)
//			{
//				ui4_check_sum += aui1_com[ui2_j];
//				ui2_j++;
//			}
//			aui1_com[10]=(0xff-(UINT8)ui4_check_sum);
			while ( ui2_i<11 )
			{
				aui1_ret_buf[0]=aui1_com[ui2_i];
				t_iom_uart.pui1_data = aui1_ret_buf;
				t_iom_uart.z_len = 1;
				ui2_i++;

				if (ui2_i>0xff)
				{
					//c_dbg_stmt("buffer overflow \n");
					return;
				}

				c_iom_output(h_iom_uart, &t_iom_uart);	 
			}
		}	
	}
	else  if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_BLUETOOTH_RSSI)
	{
		int iLength;
		printf("<factory_return> Get RSSI and MAC \n");
		if (aui1_faccmd_buf[1] == 0 && aui1_faccmd_buf[2] == 0 && aui1_faccmd_buf[3] == 0
			&& aui1_faccmd_buf[4] == 0 && aui1_faccmd_buf[5] == 0 && aui1_faccmd_buf[6] == 0 )
		{
			aui1_com[0] = 0x00;
			aui1_com[1] = 0x01;
			aui1_com[2] = 0x00;
			aui1_com[3] = 0x01;
			aui1_com[4] = aui1_faccmd_buf[0];
			aui1_com[5] = _gen_checksum(aui1_com, 5 ); //Tommy 20201224

			iLength = 6;

		}
		else
		{
			aui1_com[0] = 0x00;
			aui1_com[1] = 0x01;
			aui1_com[2] = 0x00;
			aui1_com[3] = 0x07;
			aui1_com[4] = aui1_faccmd_buf[0];
			aui1_com[5] = aui1_faccmd_buf[1];
			aui1_com[6] = aui1_faccmd_buf[2];
			aui1_com[7] = aui1_faccmd_buf[3];
			aui1_com[8] = aui1_faccmd_buf[4];
			aui1_com[9] = aui1_faccmd_buf[5];
			aui1_com[10] = aui1_faccmd_buf[6];
			aui1_com[11] = _gen_checksum(aui1_com, 11 ); //Tommy 20201224

			iLength = 12;

		}	
		while ( ui2_i < iLength )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = 1;
			ui2_i++;
		
			if (ui2_i>0xff)
			{
				//c_dbg_stmt("buffer overflow \n");
				return;
			}
		
			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
	}
	else  if (ui2_cmd_return_type ==Foxconn_FACTORY_SET_CMD_GET_ULPK_KEY)
	{
		//DBG_INFO(("<factory_return> Get ULPK\n"));
		if(((Foxconn_FACTORY_COND_TYPE_T)(UINT32)pv_val)==Foxconn_FACTORY_COND_OK)
		{
			int j;

			aui1_ret_buf[0] = 0x00;
			aui1_ret_buf[1] = 0x01;
			aui1_ret_buf[2] = 0x00;
			aui1_ret_buf[3] = ULPK_DATA_LEN; /* ULPK len < 255 */
#if 0
			for(j=0;j<LEN_ULI_ULPK;j++) 
			{
//				c_dbg_stmt("%02x\n", aui1_faccmd_buf[j]);
			}
#endif
			for(j=0;j<ULPK_DATA_LEN;j++) 
			{
				aui1_ret_buf[j+4] = aui1_faccmd_buf[j]; 
			}
#if 0
			for(j=0;j<LEN_ULI_ULPK;j++) 
			{
//				c_dbg_stmt("%02x\n", aui1_ret_buf[j]);
			}	 
#endif
			aui1_ret_buf[ULPK_DATA_LEN + 4] = _gen_checksum(aui1_ret_buf, ULPK_DATA_LEN + 4 );//yuan 2012 0703 
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = ULPK_DATA_LEN + 4+1;
			c_iom_output(h_iom_uart, &t_iom_uart);   
		}
	}
	// yuan 2012 0103 
	else  if (ui2_cmd_return_type ==Foxconn_FACTORY_SET_CMD_GET_POTK_KEY)
	{
		DBG_INFO(("<factory_return> Get POTK\n"));
		if(((Foxconn_FACTORY_COND_TYPE_T)(UINT32)pv_val)==Foxconn_FACTORY_COND_OK)
		{
			int j;
			aui1_ret_buf[0] = 0x00;
			aui1_ret_buf[1] = 0x01;
			aui1_ret_buf[2] = 0x00;
			aui1_ret_buf[3] = 0x10;
#if 0
			for(j=0;j<LEN_ULI_ULPK;j++) 
			{
	//			c_dbg_stmt("%02x\n", aui1_faccmd_buf[j]);
			}
#endif
			for(j=0;j<POTK_KEY_LEN;j++) 
			{
				aui1_ret_buf[j+4] = aui1_faccmd_buf[j]; 
			}
#if 0
			for(j=0;j<LEN_ULI_ULPK;j++) 
			{
	//			c_dbg_stmt("%02x\n", aui1_ret_buf[j]);
			}	 
#endif
			aui1_ret_buf[POTK_KEY_LEN + 4] = _gen_checksum(aui1_ret_buf, POTK_KEY_LEN + 4 );//yuan 2012 0703 
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = POTK_KEY_LEN + 4+1;
			c_iom_output(h_iom_uart, &t_iom_uart);   
		}
	}		
	else if (ui2_cmd_return_type ==Foxconn_FACTORY_SET_CMD_FAC_READ_EDID	)	//colby@20191118	 
	{
		DBG_INFO(("<fact_parser> Foxconn_FACTORY_SET_CMD_FAC_READ_EDID\n"));

		aui1_com[0] = 0x00;
		aui1_com[1] = 0x01;
		aui1_com[2] = 0x01;
		aui1_com[3] = 0x00;

    	for(ui2_j=0;ui2_j<EDID_MAX_LEN;ui2_j++) 
		{
			aui1_com[ui2_j+4] = aui1_faccmd_buf[ui2_j];
//			DBG_INFO(("EDID aui1_faccmd_buf[%d] = 0x%X \n",ui2_j, aui1_faccmd_buf[ui2_j]));
		}

		aui1_com[EDID_MAX_LEN + 4] = _gen_checksum(aui1_com, EDID_MAX_LEN + 4 ); 
//		ui4_check_sum = 0;
//		while(ui2_i < EDID_MAX_LEN+4)
//		{
//			ui4_check_sum += aui1_com[ui2_i];
//			ui2_i++;
//		}
//		aui1_com[EDID_MAX_LEN + 4] = (0xff-(UINT8)ui4_check_sum);
//		DBG_INFO((" checksum=%x \n",aui1_com[EDID_MAX_LEN + 4]));
		
		t_iom_uart.pui1_data = aui1_com;
		t_iom_uart.z_len = EDID_MAX_LEN + 4+1;
		
//		for (ui2_j=0;ui2_j<t_iom_uart.z_len;ui2_j++)
//	        DBG_INFO(("EDID_Return[%d] = 0x%X \n",ui2_j, t_iom_uart.pui1_data[ui2_j]));
			
		c_iom_output(h_iom_uart, &t_iom_uart);	
		return;
	}
	else if (ui2_cmd_return_type ==Foxconn_FACTORY_SET_CMD_FAC_READ_EDID_512)	//WT@20210122
	{
		DBG_INFO(("<fact_parser> Foxconn_FACTORY_SET_CMD_FAC_READ_EDID_512\n"));

		aui1_com[0] = 0x00;
		aui1_com[1] = 0x01;
		aui1_com[2] = 0x01;
		aui1_com[3] = 0x00;

		for(ui2_j=0;ui2_j<EDID_MAX_LEN_512;ui2_j++) 
		{
			aui1_com[ui2_j+4] = aui1_faccmd_buf[ui2_j];
		}

		aui1_com[EDID_MAX_LEN_512+ 4] = _gen_checksum(aui1_com, EDID_MAX_LEN_512+ 4 ); 
		
		t_iom_uart.pui1_data = aui1_com;
		t_iom_uart.z_len = EDID_MAX_LEN_512+ 4+1;
		
		c_iom_output(h_iom_uart, &t_iom_uart);	
		return;
	}
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_HDCP_14_DATA)//Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV 
	{
//		c_dbg_stmt("<fact_parser> Foxconn_FACTORY_SET_CMD_READ_HDCP1.4_DATA \n");
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		while ( ui2_j<HDCP1x_MAX_LEN ) //colby@191204
		{
			aui1_com[ui2_j+4]=aui1_faccmd_buf[ui2_j];
//			DBG_INFO((" aui1_com[%d + 4]= 0x%X \n",ui2_j+4, aui1_com[ui2_j + 4]));
			ui2_j++;
		}
		aui1_com[2] = ui2_j >> 8;
		aui1_com[3] = ui2_j;
		aui1_com[ui2_j + 4] = _gen_checksum(aui1_com, ui2_j + 4 ); //Tommy 20201013
//		while(ui2_i<ui2_j+4)
//		{
//			ui4_check_sum += aui1_com[ui2_i];
//			ui2_i++;
//		}
//		aui1_com[ui2_i]=(0xff-(UINT8)ui4_check_sum);
		ui2_j = 0;
//		while ( ui2_j<(ui2_i+1) )//11*2byte*3 color+magic num 8 bytes+cs=75bytes
		while ( ui2_j<(HDCP1x_MAX_LEN+5) )//11*2byte*3 color+magic num 8 bytes+cs=75bytes
		{
			aui1_ret_buf[0] =aui1_com[ui2_j];	
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = 1;
			ui2_j++;
#if 0
			if (ui2_i>320)
			{
				c_dbg_stmt("buffer overflow \n");
				return;
			}
#endif
			c_iom_output(h_iom_uart, &t_iom_uart);   
			x_thread_delay(1);
		}
		return;
	}
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_HDCP_2X_DATA)//Foxconn_FACTORY_SET_CMD_READ_HDCP_KSV 
	{
//		c_dbg_stmt("<fact_parser> Foxconn_FACTORY_SET_CMD_READ_HDCP2.2_DATA\n");
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		while ( ui2_j<HDCP2x_MAX_LEN ) //colby@191204
		{
			aui1_com[ui2_j+4]=aui1_faccmd_buf[ui2_j];
//			DBG_INFO((" aui1_com[%d + 4]= 0x%X \n",ui2_j+4, aui1_com[ui2_j + 4]));
			ui2_j++;
		}
		aui1_com[2] = ui2_j >> 8;
		aui1_com[3] = ui2_j;
		aui1_com[ui2_j + 4] = _gen_checksum(aui1_com, ui2_j + 4 ); //Tommy 20201013
//		while(ui2_i<ui2_j+4)
//		{
//			ui4_check_sum += aui1_com[ui2_i];
//			ui2_i++;
//		}
//		aui1_com[ui2_i]=(0xff-(UINT8)ui4_check_sum);
		ui2_j = 0;
//		while ( ui2_j<(ui2_i+1) )//11*2byte*3 color+magic num 8 bytes+cs=75bytes
		while ( ui2_j<(HDCP2x_MAX_LEN+5) )//11*2byte*3 color+magic num 8 bytes+cs=75bytes
		{
			aui1_ret_buf[0] =aui1_com[ui2_j];	
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = 1;
			ui2_j++;
#if 0
			if (ui2_i>320)
			{
				c_dbg_stmt("buffer overflow \n");
				return;
			}
#endif
			c_iom_output(h_iom_uart, &t_iom_uart);   
			x_thread_delay(1);
		}
		return;
	}
    else if(ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_POWER_OFF) //colby@191223
    {
        //DBG_INFO(("\n Foxconn_FACTORY_SET_CMD_POWER_OFF retrun --------------- \n"));
		aui1_ret_buf[0] = 0x00;
		aui1_ret_buf[1] = 0x01;
		aui1_ret_buf[2] = 0x00;
		aui1_ret_buf[3] = 0x00;
        aui1_ret_buf[4] = _gen_checksum(aui1_ret_buf, 4 );
		t_iom_uart.pui1_data = aui1_ret_buf;
		t_iom_uart.z_len = 5;
		c_iom_output(h_iom_uart, &t_iom_uart);
        x_thread_delay(150);
        a_amb_power_on(FALSE);                
    }  
    else if(ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD) //colby@191206
    {
        DBG_INFO(("\n Foxconn_FACTORY_SET_CMD_READ_HDCP_VAILD retrun --------------- \n"));
		aui1_ret_buf[0] = 0x00;
		aui1_ret_buf[1] = 0x01;
		aui1_ret_buf[2] = 0x00;
		aui1_ret_buf[3] = 0x01;
        aui1_ret_buf[4] = aui1_faccmd_buf[0]; /* return 0x00:Pass other:fail */
        aui1_ret_buf[5] = _gen_checksum(aui1_ret_buf, 5 );
		t_iom_uart.pui1_data = aui1_ret_buf;
		t_iom_uart.z_len = 6;
		c_iom_output(h_iom_uart, &t_iom_uart);
    }   
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_SW_VER)	
	{
//		c_dbg_stmt(("<factory_return> Foxconn_FACTORY_SET_CMD_READ_SW_VER\n"));
//		if(((FACTORY_COND_TYPE_T)(UINT32)pv_val)==FACTORY_COND_OK)
		{
			INT16 j, length;
			aui1_ret_buf[0] = 0x00;
			aui1_ret_buf[1] = 0x01;
			aui1_ret_buf[2] = 0x00;

			length = 32+8; // 
			for(j=0;j<length;j++) 
			{
//				c_dbg_stmt("%02x\n", aui1_faccmd_buf[j]);
				if (aui1_faccmd_buf[j] == 0)
				{
					length = j;
					break;
				}
			}
			aui1_ret_buf[3] = length;
			for(j=0;j<length;j++) 
			{
				aui1_ret_buf[j+4] = aui1_faccmd_buf[j]; 
			}
			for(j=0;j<length;j++) 
			{
				//c_dbg_stmt("%02x\n", aui1_ret_buf[j]);
			} 	  
			aui1_ret_buf[length + 4] = _gen_checksum(aui1_ret_buf, length + 4 );//googol@120201
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = length + 5;
			c_iom_output(h_iom_uart, &t_iom_uart);   
		}
		return;
	}
	else if(ui2_cmd_return_type==Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE)//colby@191220
	{
		DBG_INFO(("<factory_return> Foxconn_FACTORY_SET_CMD_GET_PANEL_TYPE \n"));

		if(((Foxconn_FACTORY_COND_TYPE_T)(UINT32)pv_val)==Foxconn_FACTORY_COND_OK)
		{
			int j;
            UINT8 data_len = aui1_faccmd_buf[0];
			aui1_ret_buf[0] = 0x00;
			aui1_ret_buf[1] = 0x01;
			aui1_ret_buf[2] = 0x00;
			aui1_ret_buf[3] = data_len; 

			for(j=0;j<data_len;j++) 
			{           
				aui1_ret_buf[j+4] = aui1_faccmd_buf[j+1]; 
			}

			aui1_ret_buf[data_len + 4] = _gen_checksum(aui1_ret_buf, data_len + 4); 

			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = data_len + 4 + 1;
			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
	} 
	else if(ui2_cmd_return_type==Foxconn_FACTORY_GET_CMD_EEPROM_LOAD)//colby@191220
	{
		DBG_INFO(("<factory_return> Foxconn_FACTORY_GET_CMD_EEPROM_LOAD \n"));

		if(((Foxconn_FACTORY_COND_TYPE_T)(UINT32)pv_val)==Foxconn_FACTORY_COND_OK)
		{
			int j;
            UINT8 data_len = aui1_faccmd_buf[0];
			aui1_ret_buf[0] = 0x00;
			aui1_ret_buf[1] = 0x01;
			aui1_ret_buf[2] = 0x00;
			aui1_ret_buf[3] = data_len; 

			for(j=0;j<data_len;j++) 
			{           
				aui1_ret_buf[j+4] = aui1_faccmd_buf[j+1]; 
			}

			aui1_ret_buf[data_len + 4] = _gen_checksum(aui1_ret_buf, data_len + 4); 

			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = data_len + 4 + 1;
			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
	}     
	else if ( ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_IR_CODE)//FXC_WT@@20180410
	{
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x4;	// yuan 
		aui1_com[4] = (UINT8) (((UINT32) pv_tag) >> 24);
		aui1_com[5] = (UINT8) (((UINT32) pv_tag) >> 16);
		aui1_com[6] = (UINT8) (((UINT32) pv_tag) >> 8);
		aui1_com[7] = (UINT8) ((UINT32) pv_tag);
		aui1_com[8] = _gen_checksum(aui1_com, 8 ); //Tommy 20201013
//		while(ui2_j<8)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<9 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len	 = 1;
			ui2_i++;
				c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
	   return;
	} 
	else  if (ui2_cmd_return_type == Foxconn_FACTORY_GET_CMD_GET_DBC_CONTROL)
	{	
		UINT8 ui1_check = (UINT8)((UINT32)pv_tag >> 8); 

		DBG_INFO(("<fact_parser>FACTORY_SET_CMD_GET_DBC_CONTROL %u, %u \n", pv_tag, ui1_check)); 
		if (ui1_check!= 0 )
		{
			aui1_com[0] = 0x1;
			aui1_com[1] = 0x1;
			aui1_com[2] = 0x0;
			aui1_com[3] = 0x0; 
			aui1_com[4] = _gen_checksum(aui1_com, 4 ); //Tommy 20201013

//			while(ui2_j<4)
//			{
//				ui4_check_sum += aui1_com[ui2_j];
//				ui2_j++;
//			}
//			aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
			while ( ui2_i<5 )
			{
				aui1_ret_buf[0]=aui1_com[ui2_i];
				t_iom_uart.pui1_data = aui1_ret_buf;
				t_iom_uart.z_len	 = 1;
				ui2_i++;
				c_iom_output(h_iom_uart, &t_iom_uart);	
			}
		}
	}
	else if ( ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_LED_STATUS)
	{
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x2;
		aui1_com[4] = (UINT8) ((UINT32) pv_tag);
		aui1_com[5] = (UINT8) (((UINT32) pv_tag) >> 8);
		aui1_com[6] = _gen_checksum(aui1_com, 6 ); //Tommy 20201013
//		while(ui2_j<6)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<7 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len	 = 1;
			ui2_i++;
			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
		return;
	}
	// yuan vvvvv
// FXC_Jim 2018_0331 vvvvv
		 else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_POWERONTIME)
		 	{
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x4;
		aui1_com[4] = (UINT8) (((UINT32) pv_tag) >> 24);//20111110 sammi modified
		aui1_com[5] = (UINT8) (((UINT32) pv_tag) >> 16);
		aui1_com[6] = (UINT8) (((UINT32) pv_tag) >> 8);
		aui1_com[7] = (UINT8) ((UINT32) pv_tag);
		aui1_com[8] = _gen_checksum(aui1_com, 8 ); //Tommy 20201013
//		while(ui2_j<8)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<9 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len	 = 1;
			ui2_i++;
#if 0
			if (ui2_i>0xff)
			{
				c_dbg_stmt("buffer overflow \n");
				return;
			}
#endif
                c_iom_output(h_iom_uart, &t_iom_uart);   
		}
		return;
	}
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_VCOM_IMPLEMENTATION)
	{
		if((((Foxconn_FACTORY_COND_TYPE_T)(UINT32)pv_val)==Foxconn_FACTORY_COND_OK)&&(aui1_faccmd_buf[0]!=20))
		{
		    

			int j;
			aui1_ret_buf[0] = 0x00;
			aui1_ret_buf[1] = 0x01;
			aui1_ret_buf[2] = 0x00;
			aui1_ret_buf[3] = aui1_faccmd_buf[0];

			for(j=0;j<aui1_faccmd_buf[0];j++) 
			{
				aui1_ret_buf[4+j] = aui1_faccmd_buf[1+j]; 
			}

			aui1_ret_buf[aui1_faccmd_buf[0] + 4] = _gen_checksum(aui1_ret_buf, aui1_faccmd_buf[0] + 4 ); 
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = aui1_faccmd_buf[0] + 4 + 1;
			c_iom_output(h_iom_uart, &t_iom_uart);   
                    
		}       

	}
// FXC_Jim 2018_0331 ^^^^^^
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_HDR_NITS)
	{
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x2;
		aui1_com[4] = (UINT8) (((UINT32) pv_tag)>>8);
		aui1_com[5] = (UINT8) ((UINT32) pv_tag);
		aui1_com[6] = _gen_checksum(aui1_com, 6); //Tommy 20201013
//		while(ui2_j<6)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<7 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len	 = 1;
			ui2_i++;

			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
		return;
	}

	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_GAMMA_TABLE) //colby@20200115
	{
		//c_dbg_stmt("<fact_parser> FACTORY_SET_CMD_READ_GAMMA_TABLE_CN\n");
		aui1_ret_buf[0] = 0x0;
		aui1_ret_buf[1] = 0x1;
		aui1_ret_buf[2] = 0x0;
		aui1_ret_buf[3] = GAMMA_MAX_LEN;

		while (ui2_j < GAMMA_MAX_LEN)
		{
			aui1_ret_buf[ui2_j+4]=aui1_faccmd_buf[ui2_j];
		    ui2_j++;
		}

		aui1_ret_buf[GAMMA_MAX_LEN + 4]=_gen_checksum(aui1_ret_buf, GAMMA_MAX_LEN + 4 );

		t_iom_uart.pui1_data = aui1_ret_buf;
		t_iom_uart.z_len = GAMMA_MAX_LEN + 4 + 1;
		c_iom_output(h_iom_uart, &t_iom_uart);   
		x_thread_delay(1);
		return;	
	}

	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_HDCP_14_KSV) 
	{
		//	c_dbg_stmt("<fact_parser> FACTORY_SET_CMD_GET_FFA\n");
		int j , Length;
		aui1_ret_buf[0] = 0x00;
		aui1_ret_buf[1] = 0x01;
		aui1_ret_buf[2] = 0x00;
		aui1_ret_buf[3] =HDMI_KSV_DATA;

		Length = HDMI_KSV_DATA;
		for(j=0;j<Length;j++) 
		{
			aui1_ret_buf[j+4] = aui1_faccmd_buf[j]; 
		}

		aui1_ret_buf[Length + 4] = _gen_checksum(aui1_ret_buf, Length + 4 );//yuan 2012 0703 
		t_iom_uart.pui1_data = aui1_ret_buf;
		t_iom_uart.z_len = Length + 4+1;
		c_iom_output(h_iom_uart, &t_iom_uart);   

		return;
	}

	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_HDCP_22_ID) 
	{
		//	c_dbg_stmt("<fact_parser> FACTORY_SET_CMD_GET_FFA\n");
		int j , Length;
		aui1_ret_buf[0] = 0x00;
		aui1_ret_buf[1] = 0x01;
		aui1_ret_buf[2] = 0x00;
		aui1_ret_buf[3] = HDMI_ID_DATA;

		Length = HDMI_ID_DATA;
		for(j=0;j<Length;j++) 
		{
			aui1_ret_buf[j+4] = aui1_faccmd_buf[j]; 
		}

		aui1_ret_buf[Length + 4] = _gen_checksum(aui1_ret_buf, Length + 4 );//yuan 2012 0703 
		t_iom_uart.pui1_data = aui1_ret_buf;
		t_iom_uart.z_len = Length + 4+1;
		c_iom_output(h_iom_uart, &t_iom_uart);   

		return;
	}
		
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_FFA) 
	{  
		//	c_dbg_stmt("<fact_parser> FACTORY_SET_CMD_GET_FFA\n");
		int j , Length;
		aui1_ret_buf[0] = 0x00;
		aui1_ret_buf[1] = 0x01;
		aui1_ret_buf[2] = 0x00;
		aui1_ret_buf[3] = aui1_faccmd_buf[0];

		Length = aui1_faccmd_buf[0];
		for(j=0;j<Length;j++) 
		{
			aui1_ret_buf[j+4] = aui1_faccmd_buf[j+1]; 
		}

		aui1_ret_buf[Length + 4] = _gen_checksum(aui1_ret_buf, Length + 4 );//yuan 2012 0703 
		t_iom_uart.pui1_data = aui1_ret_buf;
		t_iom_uart.z_len = Length + 4+1;
		c_iom_output(h_iom_uart, &t_iom_uart);   

		return;
	}
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_WB_DATA)
	{
		//c_dbg_stmt("<fact_parser> FACT_CMD_READ_WB_DATA\n");
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x2;
		aui1_com[4] = (UINT8) (((UINT32) pv_tag>>6 & 0x03));
		aui1_com[5] = (UINT8) (((UINT32) pv_tag<<2 )& 0xFC);
		aui1_com[6] = _gen_checksum(aui1_com, 6 ); //Tommy 20201013
//		while(ui2_j<6)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<7 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len     = 1;
			ui2_i++;

			c_iom_output(h_iom_uart, &t_iom_uart);   
		}
		return;
	}
	// yuan ^^^^^
// FXC_Jim 20180331 vvvvvv
      else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_AGING_TIME_P)
      	{
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x4;
		aui1_com[4] = (UINT8) (((UINT32) pv_tag) >> 24);//20111110 sammi modified
		aui1_com[5] = (UINT8) (((UINT32) pv_tag) >> 16);
		aui1_com[6] = (UINT8) (((UINT32) pv_tag) >> 8);
		aui1_com[7] = (UINT8) ((UINT32) pv_tag);
		aui1_com[9] = _gen_checksum(aui1_com, 8 ); //Tommy 20201013
//		while(ui2_j<8)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<9 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len	 = 1;
			ui2_i++;
#if 0
			if (ui2_i>0xff)
			{
				c_dbg_stmt("buffer overflow \n");
				return;
			}
#endif
                c_iom_output(h_iom_uart, &t_iom_uart);  
	 }
      	}
// FXC_Jim 20180331 ^^^^^^
	// yuan 2013 0102 vvvvv
	else if ( ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_GET_WIFI_RSSI)
	{
#if 1
		aui1_com[0] = 0x00;
		aui1_com[1] = 0x01;
		aui1_com[2] = 0x00;
		aui1_com[3] = 0x03;
		aui1_com[4] = aui1_faccmd_buf[0];
		aui1_com[5] = aui1_faccmd_buf[1];
		aui1_com[6] = aui1_faccmd_buf[2];
		aui1_com[7] = _gen_checksum(aui1_com, 7 ); //Tommy 20201224

		while ( ui2_i < 8 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len = 1;
			ui2_i++;

			if (ui2_i>0xff)
			{
				//c_dbg_stmt("buffer overflow \n");
				return;
			}

			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}

#else
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x2;
		aui1_com[4] = 0x0;
		aui1_com[5] = (UINT8) ((UINT32) pv_tag);
		aui1_com[6] = _gen_checksum(aui1_com, 6 ); //Tommy 20201013
//		while(ui2_j<6)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<7 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len	 = 1;
			ui2_i++;

			c_iom_output(h_iom_uart, &t_iom_uart);	 
		}
#endif
		return;
	}   
	else if (ui2_cmd_return_type == Foxconn_FACTORY_SET_CMD_READ_WB_DATA)
	{
		//c_dbg_stmt("<fact_parser> FACT_CMD_READ_WB_DATA\n");
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x2;
		aui1_com[4] = (UINT8) (((UINT32) pv_tag>>6 & 0x03));
		aui1_com[5] = (UINT8) (((UINT32) pv_tag<<2 )& 0xFC);
		aui1_com[6] = _gen_checksum(aui1_com, 6); //Tommy 20201013
//		while(ui2_j<6)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<7 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len     = 1;
			ui2_i++;

			c_iom_output(h_iom_uart, &t_iom_uart);   
		}
		return;
	}
	// yuan ^^^^^
	else if ( ui2_cmd_return_type == Foxconn_FACTORY_CMD_GET_RETURN_ONE_BYTE)		
	{
		//c_dbg_stmt("<fact_parser> FACT_CMD_READ_WB_DATA\n");
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x1;
		aui1_com[4] = (UINT8) ((UINT32) pv_tag);
		aui1_com[5] = _gen_checksum(aui1_com, 5); //Tommy 20201013
//		while(ui2_j<5)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<6 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len     = 1;
			ui2_i++;

			c_iom_output(h_iom_uart, &t_iom_uart);   
		}
		return;
	}
	else if ( ui2_cmd_return_type == Foxconn_FACTORY_CMD_GET_RETURN_TWO_BYTE)		//Tommy 10080330
	{
		//c_dbg_stmt("<fact_parser> FACT_CMD_READ_WB_DATA\n");
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x1;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x2;
		aui1_com[4] = (UINT8) (((UINT32) pv_tag>>8 & 0xFF));
		aui1_com[5] = (UINT8) (((UINT32) pv_tag )& 0xFF);
		aui1_com[6] = _gen_checksum(aui1_com, 6 ); //Tommy 20201013
		
//		Printf("Tommy pv_tag = %x", pv_tag);
//		while(ui2_j<6)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<7 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len     = 1;
			ui2_i++;

			c_iom_output(h_iom_uart, &t_iom_uart);   
		}
		return;
	}
	else
	{
		aui1_com[0] = 0x0;
		aui1_com[1] = 0x0;
		aui1_com[2] = 0x0;
		aui1_com[3] = 0x0;
		aui1_com[4] = _gen_checksum(aui1_com, 4 ); //Tommy 20201013
//		while(ui2_j<4)
//		{
//			ui4_check_sum += aui1_com[ui2_j];
//			ui2_j++;
//		}
//		aui1_com[ui2_j]=(0xff-(UINT8)ui4_check_sum);
		while ( ui2_i<5 )
		{
			aui1_ret_buf[0]=aui1_com[ui2_i];
			t_iom_uart.pui1_data = aui1_ret_buf;
			t_iom_uart.z_len	   = 1;
			ui2_i++;

			c_iom_output(h_iom_uart, &t_iom_uart);   
		}

		x_thread_delay(1);
	}	
	return;
}
	
#if 0
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
    if (t_scan_info.t_cmd_type == Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_TRSTRL)
    {   /* scan for digital now */
        t_scan_info.t_cmd_type = Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_TRSTRL;

        if (a_factory_set_cmd(t_scan_info.t_cmd_type,
                              (VOID*)(UINT32) t_scan_info.aui1_rf_num[0],
                              _fact_parser_single_rf_scan_nfy,
                              pv_tag ) != Foxconn_FACTORY_COND_OK)
        {
            /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
  //          c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
            return;
        }
    }
    else if (t_scan_info.t_cmd_type == Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_CABLE)
    {   /* scan for digital now */
        t_scan_info.t_cmd_type = Foxconn_FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_CABLE;

        if (a_factory_set_cmd(t_scan_info.t_cmd_type,
                              (VOID*)(UINT32) t_scan_info.aui1_rf_num[0],
                              _fact_parser_single_rf_scan_nfy,
                              pv_tag ) != Foxconn_FACTORYR_OK)
        {
            /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
//            c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
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
                                  pv_tag ) != Foxconn_FACTORYR_OK)
            {
                /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
    //            c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
            }
        }
        else if (t_scan_info.aui1_rf_num[2] != 0)
        {   /* Check if any more RF channel to scan */
            t_scan_info.aui1_rf_num[0] = t_scan_info.aui1_rf_num[2];
            t_scan_info.aui1_rf_num[2] = 0;

            if (a_factory_set_cmd(t_scan_info.t_cmd_type,
                                  (VOID*)(UINT32) t_scan_info.aui1_rf_num[0],
                                  _fact_parser_single_rf_scan_nfy,
                                  pv_tag ) != Foxconn_FACTORYR_OK)
            {
                /*DBG_ERROR(("<fact_parser> Set command to factory daemon fails\n"));*/
    //            c_dbg_stmt("<fact_parser> Set command to factory daemon fails\n");
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
   //     c_dbg_stmt("aui1_data[%d] : 0x%X\n", ui2_idx, aui1_data[ui2_idx]);
    }

    t_iom_uart.pui1_data = aui1_data;
    t_iom_uart.z_len = ui2_idx;

    #if 0
    if(((aui1_data[1] != 0xE0) && (t_iom_uart.z_len != 5)) || ((aui1_data[1] == 0xE0) && ((aui1_data[2] == 0) || ((t_iom_uart.z_len - aui1_data[2]) != 5))))
    {
    //    c_dbg_stmt("usage: cmd SL CM0 CM1 CM2 CM3\n\r");
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

void FoxconnComm_TwoAckByteOkMsgGet(UINT8 *pui1_Buff)
{
  static const UINT8 UartAck_Ok_MsgTbl[16] =
    {0xc2,0xc7,0xcb,0xcc,0xd3,0xd4,0xd8,0xdd,0xe3,0xe4,0xe8,0xed,0xf0,0xf5,0xf9,0xfe};

  gPktNbr &= 0x0f;
  pui1_Buff[0] = UartAck_Ok_MsgTbl[gPktNbr++];
  pui1_Buff[1] = ~pui1_Buff[0];            // 2nd byte value = 1st byte 1's complement value
}

void FoxconnComm_TwoAckByteNotSupportMsgGet(UINT8 *pui1_Buff)
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

        FoxconnComm_TwoAckByteOkMsgGet(aui1_ret_buf);

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

        FoxconnComm_TwoAckByteOkMsgGet(aui1_ret_buf);
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

        FoxconnComm_TwoAckByteOkMsgGet(aui1_ret_buf);

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

        FoxconnComm_TwoAckByteOkMsgGet(aui1_ret_buf);

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
        i4_ret = c_app_send_msg(h_g_Foxconn_factory,
                                (UINT32) Foxconn_FACTORY_FAKE_CMD_SEND_ACK,
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

    FoxconnComm_TwoAckByteOkMsgGet(aui1_ret_buf);

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

    FoxconnComm_TwoAckByteOkMsgGet(aui1_ret_buf);

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

#if 1//WT@@
static UINT8 _gen_checksum(UINT8 *pui1_data,UINT16 ui1_count) //colby@191220
{
	UINT32	ui4_checksum=0;
	UINT16	loop = 0 ;

	for(loop = 0;loop < ui1_count;loop++)
	{
		ui4_checksum = pui1_data[loop] + ui4_checksum;
	}
	ui4_checksum = (0xff-(UINT8)ui4_checksum);

	return (UINT8)ui4_checksum;
}
#endif

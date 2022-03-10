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
#include "c_dbg.h"

#include "u_irrc_btn_def.h"
#include "u_iom.h"
#include "c_iom.h"

#include "app_util/a_dbg_level_app.h"
#include "app_util/a_common.h"
#include "res/nav/factory/a_factory.h"


#include "mtperipheral.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define FACTORY_VIR_UART_ID         1

#define CHK   (0)

typedef struct
{
    FACTORY_SET_CMD_TYPE_T          t_cmd_type;
    UINT8                           aui1_rf_num[3];
    UINT8                           ui1_cs;
} FACTORY_PARSER_SCAN_INFO_T;

#define CMD_LEN                     5

//#undef DBG_LEVEL_MODULE
//#define DBG_LEVEL_MODULE            factory_get_dbg_level()


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static HANDLE_T                     h_iom_uart = NULL_HANDLE;

static UINT8                        aui1_cmd_buf[CMD_LEN_Maximum];

static UINT16                       ui2_cmd_buf_idx;

static FACTORY_PARSER_SCAN_INFO_T   t_scan_info;

static BOOL                         b_cli_simulate;

//static BOOL                         b_factory_mode_started = FALSE;
static UINT8                        ui1_cmd_length;

UINT8	aui1_faccmd_ret_val[CMD_LEN_Maximum];

#ifdef CLI_SUPPORT
static INT32 _fact_parser_cli_cmd(INT32 i4_argc, const CHAR** pps_argv);

static CLI_EXEC_T at_FACTORY_SET_CMD_tbl[] = 
{
    {"cmd",   "c",   _fact_parser_cli_cmd,  NULL, "usage: SL CM0 CM1 CM2 CM3", CLI_GUEST},
    END_OF_CLI_CMD_TBL
};
static CLI_EXEC_T at_factory_root_cmd_tbl[] =
{
    {"fact_parser", "fp",  NULL,  at_FACTORY_SET_CMD_tbl, "factory commands",   CLI_GUEST},
    END_OF_CLI_CMD_TBL
};
#endif

BOOL g_b_enter_fac_mode = FALSE; 

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _fact_parser_iom_nfy_fct(
                    VOID*                       pv_nfy_tag,
                    IOM_NFY_COND_T              e_nfy_cond,
                    UINT32                      ui4_evt_code,
                    UINT32                      ui4_data
                    );
static VOID _fact_parser_iom_nfy_rec_buf(
                    UINT32                      ui4_size
                    );
static VOID _fact_parser_parse_and_set_cmd (
                    VOID
                    );

						
static VOID _fact_parser_set_cmd_nfy(
                    VOID*                       pv_tag,
                    VOID*                       pv_val
                    );	



//static VOID _fact_parser_parse_and_set_cmd(VOID);
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
__attribute__ ((visibility("default"))) VOID a_fact_parser_init(VOID)
{
    UART_SETTING_T  t_uart_setting;
    UINT32 ui4_mode = IOM_UART_OPERATION_MODE_FACTORY| IOM_UART_OPERATION_MODE_TRANSPARENT;


    ui2_cmd_buf_idx = 0;

    c_memset(&t_scan_info, 0, sizeof(t_scan_info));

    t_uart_setting.e_speed    = IOM_UART_SPEED_115200;
    t_uart_setting.e_data_len = IOM_UART_DATA_LEN_8;
    t_uart_setting.e_parity   = IOM_UART_PARITY_NONE;
    t_uart_setting.e_stop_bit = IOM_UART_STOP_BIT_1;

	MTPINMUX_SetEx(235, 3);
	MTPINMUX_SetEx(236, 3);	
	
    if (c_iom_open(IOM_DEV_TYPE_IO_UART,
                   FACTORY_VIR_UART_ID,
                   NULL,
                   (VOID*) &t_uart_setting,
                   NULL,
                   _fact_parser_iom_nfy_fct,
                   &h_iom_uart) != IOMR_OK)
    {
        DBG_LOG_PRINT(("<fact_parser> UART open fails\n"));
    }

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
        DBG_LOG_PRINT(("<fact_parser> CLI init fails\n"));
    }


}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _fact_parse_cmd 
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _fact_parse_cmd
(
    VOID *pv_tag,
    VOID *pv_val
)
{
    _fact_parser_parse_and_set_cmd();
}

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
        if ((ui2_cmd_buf_idx != 0) || (pt_iom_uart->pui1_data[ui2_idx] == 0xFF))
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

    if (a_factory_set_cmd(FACTORY_SET_CMD_CONTEXT_SWITCH,
                          NULL,
                          _fact_parse_cmd,
                          NULL ) != FACTORYR_OK)
    {
        DBG_LOG_PRINT(("<fact_parser> UART ack command to factory daemon fails\n"));
    }

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
    FACTORY_SET_CMD_TYPE_T      t_cmd_type = FACTORY_CMD_INVALID;
    VOID*                       pv_cmd_val =(VOID*) 0;
    VOID*                       pv_tag = (VOID*) 0;
    UINT16                      ui2_id; 
    UINT8                       ui1_checksum = 0xFF;	//MSG_START
	UINT8						ui1_length = (aui1_cmd_buf[3])+4;	//VIZIO DATA_SIZE + MSG_START + MSG_TYPE + CMD_TYPE 
	UINT16 Data_Length; 


    // STEP 1. Check VIZIO MSG_START 
    if(aui1_cmd_buf[0]!=0xFF)
    	return;
    	
    // STEP 2. Check VIZIO MSG_TYPE 
    if(aui1_cmd_buf[1]!=0xFA)
    {
    	fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_MSG_TYPE, TRUE);
    	return;    	
    }		
  
	// STEP 3. Check VIZIO Checksum
    if((aui1_cmd_buf[0]==0xFF) && (aui1_cmd_buf[1]==0xFA))
    {
        for(ui2_id = 1; ui2_id < (ui1_length); ui2_id ++)
        {
            if(ui2_id >= CMD_LEN_Maximum)  
            {
                DBG_LOG_PRINT(("ui1_length >= CMD_LEN_Maximum\n"));
                return;
            }
            
            ui1_checksum ^= aui1_cmd_buf[ui2_id];	//Calculate Checksum  
        }

        if(ui1_checksum != aui1_cmd_buf[ui1_length])	//Compare Checksum     
        {      	
           	fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INCORRECT_CHECKSUM, TRUE);
            DBG_LOG_PRINT(("Check Sum error!!! Check sum is 0x%x\n", ui1_checksum));
            return;
        }
    }
   
   
	switch(aui1_cmd_buf[4])	//VIZIO CMD_TYPE
    {
        case 0x03:	//0x03 >> Set()
    		switch (aui1_cmd_buf[6])	//VIZIO CMD_CODE
    		{
 				case 0x00:  //Set_Model_Index
					t_cmd_type = FACTORY_CMD_SET_MODEL_INDEX;
  					//To Do;
     				break;
					
   				case 0x01:  //Set_Model name
					t_cmd_type = FACTORY_CMD_SET_MODEL_NAME;
  					//To Do;
     				break;
  
 				case 0x04:  //Set_Serial_Number
					t_cmd_type = FACTORY_CMD_SET_SERIAL_NUMBER;
  					//To Do;
     				break;
 
  				case 0x73:  //Get_Key_Hash
					t_cmd_type = FACTORY_CMD_GET_KEY_HASH;
  					//To Do;
     				break;
     				    				
 				case 0x2d:  //Set_MAC_Address
					t_cmd_type = FACTORY_CMD_SET_MAC_ADDRESS;
  					//To Do;
     				break;
     				    				
 				case 0x2e:  //Set_IP_Address
					t_cmd_type = FACTORY_CMD_SET_IP_ADDRESS;
  					//To Do;
     				break;
     			
 				case 0x12:  //Set_Power_Status
					t_cmd_type = FACTORY_CMD_SET_POWER_STATUS;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
     				break;
     				
 				case 0x76:  //Set_Standby_Disable
					t_cmd_type = FACTORY_CMD_SET_STANDBY_DISABLE;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
     				break;

 				case 0x2b:  //Set_Burning_Mode
					t_cmd_type = FACTORY_CMD_SET_BURNING_MODE;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
     				break; 

 				case 0x2c:  //Set_Timer_Status
					t_cmd_type = FACTORY_CMD_SET_TIMER_STATUS;
  					//To Do;
     				break;
     				
 				case 0x4a:  //Set_Input_Source
					t_cmd_type = FACTORY_CMD_SET_INPUT_SOURCE;
  					//To Do;
     				break; 
     				    				
 				case 0x4f:  //Do_Channel_Preset
					if(aui1_cmd_buf[7] != 0x00)
					{
						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
						return;
					}
					t_cmd_type = FACTORY_CMD_DO_CHANNEL_PRESET;
  					//To Do;
     				break; 
     			
 				case 0x31:  //Set_Channel
					t_cmd_type = FACTORY_CMD_SET_CHANNEL;
  					//To Do;
     				break;
     				
 				case 0x50:  //Do_Channel_Clean
 					t_cmd_type = FACTORY_CMD_DO_CHANNEL_CLEAN;
     				break;
     				
				case 0x28:  //Do_ADC_Calibration
 					t_cmd_type = FACTORY_CMD_DO_ADC_CALIBRATION;
  					//To Do;
     				break; 
     				    				
 				case 0x3d:  //Clear_ADC_Result
  					t_cmd_type = FACTORY_CMD_CLEAR_ADC_RESULT;
  					//To Do;
     				break; 
     			
 				case 0x2a:  //Set_ADC_Data
  					t_cmd_type = FACTORY_CMD_SET_ADC_DATA;
  					//To Do;
     				break;
     				
 				case 0x77:  //Set_ADC_Data_Bundle
					t_cmd_type = FACTORY_CMD_SET_ADC_DATA_BUNDLE;
  					//To Do;
     				break;

 				case 0x72:  //Set_Audio_Out
					t_cmd_type = FACTORY_CMD_SET_AUDIO_OUT;
  					//To Do;
     				break; 
     				
 				case 0x1b:  //Set_Sound_Mode; Set_Volume
 					switch (aui1_cmd_buf[7])	//VIZIO CMD_CODE
    				{
    					case 0x02:	//Set_Volume
							if(aui1_cmd_buf[8] > 64)
							{
								fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
								return;
							}	
  		            		t_cmd_type = FACTORY_CMD_SET_VOLUME;							
                    		pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[8];
    						break;
    						
    					case 0x05:	//Set_Sound_Mode
							if(aui1_cmd_buf[8] < 1 || aui1_cmd_buf[8] > 6)
							{
								fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
								return;
							}
							t_cmd_type = FACTORY_CMD_SET_SOUND_MODE;
							aui1_cmd_buf[8] = aui1_cmd_buf[8] - 1;
    						pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[8];
    						break;
    						
    					default:
    						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
    						return;	    				
					}
       				break; 
     			
 				case 0x26:  //Set_Picture_Mode; Set_Picture_Property; Set_Local_Dimming; Set_Clear_Action; Set_CT_Mode
 					switch (aui1_cmd_buf[7])	
    				{
    					case 0x00:	//Set_Picture_Mode
    						t_cmd_type = FACTORY_CMD_SET_PICTURE_MODE;
    						break;
    						
    					case 0x03:	//Set Backlight
    					case 0x04:	//Set Brightness
    					case 0x05:	//Set Contrast
    						t_cmd_type = FACTORY_CMD_SET_PICTURE_PROPERTY;
    						break;       						    						 						
    						
    					case 0x45:	//Set_Local_Dimming
    						t_cmd_type = FACTORY_CMD_SET_LOCAL_DIMMING;
    						break;
    						
    					case 0x46:	//Set_Clear_Action
    						t_cmd_type = FACTORY_CMD_SET_CLEAR_ACTION;
    						break; 
    						
    					case 0x09:	//Set_CT_Mode
    						t_cmd_type = FACTORY_CMD_SET_CT_MODE;
    						break;
    						
    					default:
    						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
    						return;	    				
					}
					break;

     				
 				case 0x39:  //Set_CT_Value
					t_cmd_type = FACTORY_CMD_SET_CT_VALUE;
  					//To Do;
     				break; 
     				    				
 				case 0x78:  //Set_CT_Value_Bundle
					t_cmd_type = FACTORY_CMD_SET_CT_VALUE_BUNDLE;
  					//To Do;
     				break; 
     			
 				case 0x3c:  //Set_Test_Pattern
					t_cmd_type = FACTORY_CMD_SET_TEST_PATTERN;
  					//To Do;
     				break;
     				
 				case 0x1a:  //Do_Setting_Reset
					t_cmd_type = FACTORY_CMD_DO_SETTING_RESET;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
  					//To Do;
     				break;  
     				 
 				case 0x17:  //Do_Reboot
					t_cmd_type = FACTORY_CMD_DO_REBOOT;
  					//To Do;
     				break;
     				
 				case 0x56:  //Do_Skip_OOBE
					t_cmd_type = FACTORY_CMD_DO_SKIP_OOBE;
     				break; 

 				case 0x0f:  //Set_IR_KeyPad_Block
					t_cmd_type = FACTORY_CMD_SET_IR_KEYPAD_BLOCK;
  					//To Do;
     				break; 

 				case 0x74:  //Inject_Key_Event
					t_cmd_type = FACTORY_CMD_INJECT_KEY_EVENT;
  					//To Do;
     				break; 

 				case 0x59:  //Set_Sound_Balance
					if ((aui1_cmd_buf[7] != 0x00) || (aui1_cmd_buf[8] != 0x00) || (aui1_cmd_buf[9] != 0x00))
					{
						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
						return;
					}						
					
					if((aui1_cmd_buf[10] > 0x32) && (aui1_cmd_buf[10] < 0xCE))
					{
						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
						return;
					}	
					
					t_cmd_type = FACTORY_CMD_SET_SOUND_BALANCE;
					pv_cmd_val = (VOID*)(UINT32)(aui1_cmd_buf[10]);
     				break; 
 
 				case 0x5a:  //Do_Sound_Tone_Test
					t_cmd_type = FACTORY_CMD_DO_SOUND_TONE_TEST;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
  					//To Do;
     				break;
     				
 				case 0x5b:  //Set_Factory_Record
					t_cmd_type = FACTORY_CMD_SET_FACTORY_RECORD;
  					//To Do;
     				break; 

 				case 0x5c:  //Set_LED_OnOff
					t_cmd_type = FACTORY_CMD_SET_LED_ONOFF;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
  					//To Do;
     				break; 

 				case 0x5e:  //Set_Factory_Continue
					if((aui1_cmd_buf[7] != 0x00) && (aui1_cmd_buf[7] != 0x01))
					{
						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
						return;
					}
						
					t_cmd_type = FACTORY_CMD_SET_FACTORY_CONTINUE;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
     				break; 

 				case 0x60:  //Do_BT_Pair
					t_cmd_type = FACTORY_CMD_DO_BT_PAIR;
  					//To Do;
     				break; 
     				
 				case 0x63:  //Do_WiFi_Connect
					Data_Length = (UINT16) ((aui1_cmd_buf[2] << 8) |  aui1_cmd_buf[3]);
					
					DBG_INFO(("Data_Length ...........== %d\n",Data_Length));
					for (int i=0; i < Data_Length + 4; i++)
						aui1_faccmd_ret_val[i] = aui1_cmd_buf[i];
						
  					t_cmd_type = FACTORY_CMD_DO_WIFI_CONNECT;
     				break; 

 				case 0x6a:  //Write_I2C
					t_cmd_type = FACTORY_CMD_WRITE_I2C;
  					//To Do;
     				break; 
 
 				case 0x90:  //Set_Iperf_Active
					t_cmd_type = FACTORY_CMD_SET_IPERF_ACTIVE;
  					//To Do;
     				break;
     				
 				case 0x7a:  //Do_USB_Test
					t_cmd_type = FACTORY_CMD_DO_USB_TEST;
  					//To Do;
     				break; 

 				case 0x79:  //Set_11Point_Gamma
					t_cmd_type = FACTORY_CMD_SET_11POINT_GAMMA;
  					//To Do;
     				break; 

 				case 0x54:  //Set_CEC
					t_cmd_type = FACTORY_CMD_SET_CEC;
  					//To Do;
     				break; 

 				case 0x1e:  //Set_Sound_AQBypass
					t_cmd_type = FACTORY_CMD_SET_SOUND_AQBYPASS;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
  					//To Do;
     				break; 
     				    
 				case 0x45:  //Set_Picture_PQBypass
					t_cmd_type = FACTORY_CMD_SET_SOUND_PQBYPASS;
					pv_cmd_val = (VOID*)(UINT32)aui1_cmd_buf[7];
  					//To Do;
     				break; 

 				case 0x91:  //Program_Key_Data_Network
					t_cmd_type = FACTORY_CMD_PROGRAM_KEY_DATA_NETWORK;
  					//To Do;
     				break; 

 				case 0x92:  //Program_Key_Data_USB
					t_cmd_type = FACTORY_CMD_PROGRAM_KEY_DATA_USB;
  					//To Do;
     				break;  
     				    								     				     				     				     				  				     				      			      			
     			default:
     				fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_COMMAND_CODE, TRUE);
     				return;

     		}	
   			break;
 
       case 0x01:	//0x01 >> Get()
    		switch (aui1_cmd_buf[6])	//VIZIO CMD_CODE
    		{
 				case 0x00:  //Get_Model_Index
					t_cmd_type = FACTORY_CMD_GET_MODEL_INDEX;
  					//To Do;
     				break; 
     			
 				case 0x03:  //Get_Model_Name
					t_cmd_type = FACTORY_CMD_GET_MODEL_NAME;
  					//To Do;
     				break;
     				
 				case 0x04:  //Get_Serial_Number
					t_cmd_type = FACTORY_CMD_GET_SERIAL_NUMBER;
  					//To Do;
     				break; 
     				    				    			
 				case 0x2d:  //Get_MAC_Address
					t_cmd_type = FACTORY_CMD_GET_MAC_ADDRESS;
  					//To Do;
     				break;
     				
 				case 0x2e:  //Get_IP_Address
					t_cmd_type = FACTORY_CMD_GET_IP_ADDRESS;
  					//To Do;
     				break;

 				case 0x0b:  //Get_Version
					t_cmd_type = FACTORY_CMD_GET_VERSION;
  					//To Do;
     				break; 
     			
 				case 0x12:  //Get_Power_Status
					t_cmd_type = FACTORY_CMD_GET_POWER_STATUS;
  					//To Do;
     				break;
     				
 				case 0x76:  //Get_Standby_Disable
					t_cmd_type = FACTORY_CMD_GET_STANDBY_DISABLE;
  					//To Do;
     				break; 
     				    				
 				case 0x2b:  //Get_Burning_Mode
					t_cmd_type = FACTORY_CMD_GET_BURNING_MODE;
  					//To Do;
     				break; 
     			
 				case 0x2c:  //Get_Timer_Status
					t_cmd_type = FACTORY_CMD_GET_TIMER_STATUS;
  					//To Do;
     				break;
     				
 				case 0x75:  //Get_Timer_Value
					t_cmd_type = FACTORY_CMD_GET_TIMER_VALUE;
  					//To Do;
     				break;
     				
 				case 0x4a:  //Get_Input_Source
					t_cmd_type = FACTORY_CMD_GET_INPUT_SOURCE;
  					//To Do;
     				break; 
     			
 				case 0x6d:  //Get_Channel_Freq
					t_cmd_type = FACTORY_CMD_GET_CHANNEL_FREQ;
  					//To Do;
     				break;
     				
 				case 0x31:  //Get_Channel
					t_cmd_type = FACTORY_CMD_GET_CHANNEL;
  					//To Do;
     				break;

 				case 0x29:  //Get_ADC_Calibration_Flag
					t_cmd_type = FACTORY_CMD_GET_ADC_CALIBRATION_FLAG;
  					//To Do;
     				break; 
     			
 				case 0x2a:  //Get_ADC_Data
					t_cmd_type = FACTORY_CMD_GET_ADC_DATA;
  					//To Do;
     				break;
     				
 				case 0x77:  //Get_ADC_Data_Bundle
					t_cmd_type = FACTORY_CMD_GET_ADC_DATA_BUNDLE;
  					//To Do;
     				break; 
     				    				
 				case 0x72:  //Get_Audio_Out
					t_cmd_type = FACTORY_CMD_GET_AUDIO_OUT;
  					//To Do;
     				break; 
     			
 				case 0x1b:  //Get_Sound_Mode; Get_Volume
					switch (aui1_cmd_buf[7])	//VIZIO CMD_CODE
					{
    					case 0x02:	//Get_Volume
  					t_cmd_type = FACTORY_CMD_GET_VOLUME;
    						break;
    						
    					case 0x05:	//Get_Sound_Mode
    						t_cmd_type = FACTORY_CMD_GET_SOUND_MODE;
    						break;
    						
    					default:
    						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
    						return;	    				
					}
     				break;
     				
 				case 0x26:  //Get_Picture_Mode; Get_Picture_Property; Get_Local_Dimming; Get_Clear_Action; Get_CT_Mode
 					switch (aui1_cmd_buf[7])	
    				{
    					case 0x00:	//Get_Picture_Mode
    						t_cmd_type = FACTORY_CMD_GET_PICTURE_MODE;
    						break;
    						
    					case 0x03:	//Get Backlight
    					case 0x04:	//Get Brightness
    					case 0x05:	//Get Contrast
    						t_cmd_type = FACTORY_CMD_GET_PICTURE_PROPERTY;
    						break;       						    						 						
    						
    					case 0x45:	//Get_Local_Dimming
    						t_cmd_type = FACTORY_CMD_GET_LOCAL_DIMMING;
    						break;
    						
    					case 0x46:	//Get_Clear_Action
    						t_cmd_type = FACTORY_CMD_GET_CLEAR_ACTION;
    						break; 
    						
    					case 0x09:	//Get_CT_Mode
    						t_cmd_type = FACTORY_CMD_GET_CT_MODE;
    						break;
    						
    					default:
    						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
    						return;	    				
					}
					break;
     				
 				case 0x39:  //Get_CT_Value
					t_cmd_type = FACTORY_CMD_GET_CT_VALUE;
  					//To Do;
     				break;
     				
 				case 0x78:  //Get_CT_Value_Bundle
					t_cmd_type = FACTORY_CMD_GET_CT_VALUE_BUNDLE;
  					//To Do;
     				break; 
				
 				case 0x6f:  //Get_PowerOn_Time
					t_cmd_type = FACTORY_CMD_GET_POWERON_TIME;
  					//To Do;
     				break;
     				
 				case 0x16:  //Get_EDID
					t_cmd_type = FACTORY_CMD_GET_EDID;
  					//To Do;
     				break;

 				case 0x0f:  //Get_IR_KeyPad_Block
					t_cmd_type = FACTORY_CMD_GET_IR_KEYPAD_BLOCK;
  					//To Do;
     				break; 
     			
 				case 0x74:  //Capture_Key_Event
					t_cmd_type = FACTORY_CMD_CAPTURE_KEY_EVENT;
  					//To Do;
     				break;
     				
 				case 0x59:  //Get_Sound_Balance
					t_cmd_type = FACTORY_CMD_GET_SOUND_BALANCE;
  					//To Do;
     				break; 
     				    				
 				case 0x5b:  //Get_Factory_Record
					t_cmd_type = FACTORY_CMD_GET_FACTORY_RECORD;
  					//To Do;
     				break; 
     			
 				case 0x5c:  //Get_LED_OnOff
					t_cmd_type = FACTORY_CMD_GET_LED_ONOFF;
  					//To Do;
     				break;
     				
 				case 0x5e:  //Get_Factory_Continue
					t_cmd_type = FACTORY_CMD_GET_FACTORY_CONTINUE;
  					//To Do;
     				break; 
     				
 				case 0x61:  //Get_BT_RSSI
					t_cmd_type = FACTORY_CMD_GET_BT_RSSI;
  					//To Do;
     				break;
     				
 				case 0x65:  //Do_WiFi_Test
					t_cmd_type = FACTORY_CMD_DO_WIFI_TEST;
					aui1_faccmd_ret_val[0] = aui1_cmd_buf[7];
					aui1_faccmd_ret_val[1] = aui1_cmd_buf[8];
					aui1_faccmd_ret_val[2] = aui1_cmd_buf[9];
					aui1_faccmd_ret_val[3] = aui1_cmd_buf[10];
					aui1_faccmd_ret_val[4] = aui1_cmd_buf[12];
					aui1_faccmd_ret_val[5] = aui1_cmd_buf[12];
					aui1_faccmd_ret_val[6] = 0;
					aui1_faccmd_ret_val[7] = 0;
     				break;

 				case 0x64:  //Get_WiFi_RSSI
					t_cmd_type = FACTORY_CMD_GET_WIFI_RSSI;
  					//To Do;
     				break; 
     			
 				case 0x67:  //Do_ETH_Test
					t_cmd_type = FACTORY_CMD_DO_ETH_TEST;
					aui1_faccmd_ret_val[0] = aui1_cmd_buf[7];
					aui1_faccmd_ret_val[1] = aui1_cmd_buf[8];
					aui1_faccmd_ret_val[2] = aui1_cmd_buf[9];
					aui1_faccmd_ret_val[3] = aui1_cmd_buf[10];
					aui1_faccmd_ret_val[4] = aui1_cmd_buf[12];
					aui1_faccmd_ret_val[5] = aui1_cmd_buf[12];
					aui1_faccmd_ret_val[6] = 0;
					aui1_faccmd_ret_val[7] = 0;
     				break;
     				
 				case 0x6a:  //Read_I2C
					t_cmd_type = FACTORY_CMD_READ_I2C;
  					//To Do;
     				break; 
     				    				
 				case 0x6e:  //Get_LightSensor_Value
					t_cmd_type = FACTORY_CMD_GET_LIGHTSENSOR_VALUE;
  					//To Do;
     				break; 
     			
 				case 0x90:  //Get_Iperf_Active
					t_cmd_type = FACTORY_CMD_GET_IPERF_ACTIVE;
  					//To Do;
     				break;
     				
 				case 0x79:  //Get_11Point_Gamma
					t_cmd_type = FACTORY_CMD_GET_11POINT_GAMMA;
  					//To Do;
     				break;
     				
 				case 0x54:  //Get_CEC
					t_cmd_type = FACTORY_CMD_GET_CEC;
  					//To Do;
     				break;

 				case 0x1e:  //Get_Sound_AQBypass
					t_cmd_type = FACTORY_CMD_GET_SOUND_AQBYPASS;
  					//To Do;
     				break; 
     			
 				case 0x45:  //Get_Picture_PQBypass
					t_cmd_type = FACTORY_CMD_GET_SOUND_PQBYPASS;
  					//To Do;
     				break;
     							      				     				    			      			
     			default:
       				fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_COMMAND_CODE, TRUE);
     				return;
     		}	
     	    break;		
     		
		default:
	    	fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_COMMAND_TYPE, TRUE);
     		return;                                                                                                                     
	}
	


	if (a_factory_set_cmd(t_cmd_type,
                          pv_cmd_val,
                          _fact_parser_set_cmd_nfy,
                          pv_tag ) != FACTORYR_OK)
    {
        DBG_LOG_PRINT(("<fact_parser> Set command to factory daemon fails\n"));
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
	UINT8	aui1_ret_buf[CMD_LEN_Maximum] ={0};

	c_memset(aui1_ret_buf, 0x00, CMD_LEN_Maximum);  // clear
	

	switch(aui1_cmd_buf[4])	//VIZIO CMD_TYPE
    {
        case 0x03:	//0x03 >> Set()
    		switch (aui1_cmd_buf[6])	//VIZIO CMD_CODE
    		{
 				case 0x00:  //Set_Model_Index
  					//To Do;
     				break; 
     			
 				case 0x04:  //Set_Serial_Number
  					//To Do;
     				break;
 
  				case 0x73:  //Get_Key_Hash
  					//To Do;
     				break;
     				    				
 				case 0x2d:  //Set_MAC_Address
  					//To Do;
     				break;
     				    				
 				case 0x2e:  //Set_IP_Address
  					//To Do;
     				break;
     			
 				case 0x12:  //Set_Power_Status
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break;
     				
 				case 0x76:  //Set_Standby_Disable
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break;

 				case 0x2b:  //Set_Burning_Mode
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 
     			
 				case 0x2c:  //Set_Timer_Status
  					//To Do;
     				break;
     				
 				case 0x4a:  //Set_Input_Source
  					//To Do;
     				break; 
     				    				
 				case 0x4f:  //Do_Channel_Preset
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 
     			
 				case 0x31:  //Set_Channel
  					//To Do;
     				break;
     				
 				case 0x50:  //Do_Channel_Clean
   					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break;
     				
				case 0x28:  //Do_ADC_Calibration
  					//To Do;
     				break; 
     				    				
 				case 0x3d:  //Clear_ADC_Result
  					//To Do;
     				break; 
     			
 				case 0x2a:  //Set_ADC_Data
  					//To Do;
     				break;
     				
 				case 0x77:  //Set_ADC_Data_Bundle
  					//To Do;
     				break;

 				case 0x72:  //Set_Audio_Out
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 
     				
 				case 0x1b:  //Set_Sound_Mode; Set_Volume	
					switch (aui1_cmd_buf[7])	
					{
    					case 0x02:	//Set_Volume
						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
    						break;
    						
    					case 0x05:	//Set_Sound_Mode
    						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
    						break;
    						
    					default:
    						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
    						return;	    				
					}					
       				break; 
     			
 				case 0x26:  //Set_Picture_Mode; Set_Picture_Property; Set_Local_Dimming; Set_Clear_Action; Set_CT_Mode
  					//To Do;
     				break;
     				
 				case 0x39:  //Set_CT_Value
  					//To Do;
     				break; 
     				    				
 				case 0x78:  //Set_CT_Value_Bundle
  					//To Do;
     				break; 
     			
 				case 0x3c:  //Set_Test_Pattern
  					//To Do;
     				break;
     				
 				case 0x1a:  //Do_Setting_Reset
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break;  
     				 
 				case 0x17:  //Do_Reboot
  					//Nothing To Do;
     				break;
     				
 				case 0x56:  //Do_Skip_OOBE
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 

 				case 0x0f:  //Set_IR_KeyPad_Block
  					//To Do;
     				break; 

 				case 0x74:  //Inject_Key_Event
  					//To Do;
     				break; 

 				case 0x59:  //Set_Sound_Balance
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 
 
 				case 0x5a:  //Do_Sound_Tone_Test
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break;
     				
 				case 0x5b:  //Set_Factory_Record
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 

 				case 0x5c:  //Set_LED_OnOff
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 

 				case 0x5e:  //Set_Factory_Continue
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 

 				case 0x60:  //Do_BT_Pair
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 
     				
 				case 0x63:  //Do_WiFi_Connect
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 
     				
 				case 0x6a:  //Write_I2C
  					//To Do;
     				break; 
 
 				case 0x90:  //Set_Iperf_Active
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break;
     				
 				case 0x7a:  //Do_USB_Test
  					//To Do;
     				break; 

 				case 0x79:  //Set_11Point_Gamma
  					//To Do;
     				break; 

 				case 0x54:  //Set_CEC
  					//To Do;
     				break; 

 				case 0x1e:  //Set_Sound_AQBypass
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 
     				    
 				case 0x45:  //Set_Picture_PQBypass
  					fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_SUCCESS, TRUE);
     				break; 

 				case 0x91:  //Program_Key_Data_Network
  					//To Do;
     				break; 

 				case 0x92:  //Program_Key_Data_USB
  					//To Do;
     				break;  
     				    								     				     				     				     				  				     				      			      			
     			default:
     				return;
     		}	
     		break;
 
       case 0x01:	//0x01 >> Get()
    		switch (aui1_cmd_buf[6])	//VIZIO CMD_CODE
    		{
 				case 0x00:  //Get_Model_Index
  					//To Do;
     				break; 
     			
 				case 0x03:  //Get_Model_Name
  					//To Do;
     				break;
     				
 				case 0x04:  //Get_Serial_Number
  					//To Do;
     				break; 
     				    				    			
 				case 0x2d:  //Get_MAC_Address
  					//To Do;
     				break;
     				
 				case 0x2e:  //Get_IP_Address
  					//To Do;
     				break;

 				case 0x0b:  //Get_Version
  					//To Do;
     				break; 
     			
 				case 0x12:  //Get_Power_Status
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break;
     				
 				case 0x76:  //Get_Standby_Disable
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break; 
     				    				
 				case 0x2b:  //Get_Burning_Mode
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break; 
     			
 				case 0x2c:  //Get_Timer_Status
  					//To Do;
     				break;
     				
 				case 0x75:  //Get_Timer_Value
  					//To Do;
     				break;
     				
 				case 0x4a:  //Get_Input_Source
  					//To Do;
     				break; 
     			
 				case 0x6d:  //Get_Channel_Freq
					for (int i = 0; i < 4 ; i++)
					{
						aui1_ret_buf[i] = aui1_faccmd_ret_val[i];
					}
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 4, TRUE);
     				break;
     				
 				case 0x31:  //Get_Channel
  					//To Do;
     				break;

 				case 0x29:  //Get_ADC_Calibration_Flag
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break; 
     			
 				case 0x2a:  //Get_ADC_Data
  					//To Do;
     				break;
     				
 				case 0x77:  //Get_ADC_Data_Bundle
  					//To Do;
     				break; 
     				    				
 				case 0x72:  //Get_Audio_Out
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break; 
     			
 				case 0x1b:  //Get_Sound_Mode; Get_Volume
					switch (aui1_cmd_buf[7])	//VIZIO CMD_CODE
					{
    					case 0x02:	//Get_Volume
							aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
							fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
    						break;
					
    					case 0x05:	//Get_Sound_Mode
						aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                    	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
    						break;
    						
    					default:
    						fact_vizio_ret_uart_ack(FACTORY_VIZIO_CMD_INVALID_PARAMETER, TRUE);
    						return;	    				
					}	
     				break;
     				
 				case 0x26:  //Get_Picture_Mode; Get_Picture_Property; Get_Local_Dimming; Get_Clear_Action; Get_CT_Mode
  					//To Do;
     				break; 
     				
 				case 0x39:  //Get_CT_Value
  					//To Do;
     				break;
     				
 				case 0x78:  //Get_CT_Value_Bundle
  					//To Do;
     				break; 
     			
 				case 0x6f:  //Get_PowerOn_Time
  					//To Do;
     				break;
     				
 				case 0x16:  //Get_EDID
					for (int i = 0; i < 256 ; i++)
					{
						aui1_ret_buf[i] = aui1_faccmd_ret_val[i]; 
					}


     				break;

 				case 0x0f:  //Get_IR_KeyPad_Block
  					//To Do;
     				break; 
     			
 				case 0x74:  //Capture_Key_Event
  					//To Do;
     				break;
     				
 				case 0x59:  //Get_Sound_Balance
					for (int i = 0; i < 4 ; i++)
					{
						aui1_ret_buf[i] = aui1_faccmd_ret_val[i];
					}
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 4, TRUE);
     				break; 
     				    				
 				case 0x5b:  //Get_Factory_Record
  					//To Do;
     				break; 
     			
 				case 0x5c:  //Get_LED_OnOff
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break;
     				
 				case 0x5e:  //Get_Factory_Continue
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break; 
     				
 				case 0x61:  //Get_BT_RSSI
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break;
     				
 				case 0x65:  //Do_WiFi_Test
					//aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	//fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break;

 				case 0x64:  //Get_WiFi_RSSI
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break; 
     			
 				case 0x67:  //Do_ETH_Test
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break;
     				
 				case 0x6a:  //Read_I2C
  					//To Do;
     				break; 
     				    				
 				case 0x6e:  //Get_LightSensor_Value
  					//To Do;
     				break; 
     			
 				case 0x90:  //Get_Iperf_Active
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break;
     				
 				case 0x79:  //Get_11Point_Gamma
  					//To Do;
     				break;
     				
 				case 0x54:  //Get_CEC
  					//To Do;
     				break;

 				case 0x1e:  //Get_Sound_AQBypass
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break; 
     			
 				case 0x45:  //Get_Picture_PQBypass
					aui1_ret_buf[0] = aui1_faccmd_ret_val[0];
                   	fact_vizio_ret_uart_ack_data(aui1_ret_buf, FACTORY_VIZIO_CMD_SUCCESS, 1, TRUE);
     				break;
     							      				     				    			      			
     			default:
     				return;
    		}	
     		break;     		
     		
		default:
     		return;                                                                                                                     
	}                                                                                                                   
	
}


#ifdef CLI_SUPPORT
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
    UINT8               aui1_data[CMD_LEN];
    UINT16              ui2_idx;
    CHAR                s_conv[16] = "0x";

    if(i4_argc != 6)
    {
        ;//DBG_INFO(("usage: cmd SL CM0 CM1 CM2 CM3\n\r"));
        return CLIR_INV_CMD_USAGE;
    }

    b_cli_simulate = TRUE;

    for (ui2_idx = 0; ui2_idx < CMD_LEN; ui2_idx++)
    {
        s_conv[2] = '\0';
        c_strncat(s_conv, pps_argv[ui2_idx + 1], 13);
        aui1_data[ui2_idx] = (UINT8)c_strtoull(s_conv, NULL, 0);
    }

    t_iom_uart.pui1_data = aui1_data;
    t_iom_uart.z_len     = CMD_LEN;

    _fact_parser_iom_nfy_fct(NULL,
                             IOM_NFY_COND_REC_UART_DATA,
                             0,
                             (UINT32) &t_iom_uart);

    return(CLIR_OK);
}
#endif


VOID fact_vizio_ret_uart_ack(UINT8 error_code, BOOL b_clear_cmd_buf)
{
    UINT8       aui1_ret_buf[6];
	UINT8	ret_checksum = 0x00;
    IOM_UART_T  t_iom_uart;
     
    aui1_ret_buf[0] = 0xff;	//MSG_START
    aui1_ret_buf[1] = 0xfc;	//MSG_TYPE
    aui1_ret_buf[2] = 0x00;	//DATA_SIZE HighByte
	aui1_ret_buf[3] = 0x01;	//DATA_SIZE LowByte
	aui1_ret_buf[4] = error_code;	//RET_ERROR

	for (int i =0; i < 5; i++)
		ret_checksum ^= aui1_ret_buf[i];

	aui1_ret_buf[5] = ret_checksum;
		
	// UART output
    t_iom_uart.pui1_data = aui1_ret_buf;
    t_iom_uart.z_len = 6; //MSG_START + MSG_TYPE + DATA_SIZE + RET_ERROR + Checksum
    c_iom_output(h_iom_uart, &t_iom_uart);   
    
    if (b_clear_cmd_buf == TRUE)
    	c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear buff
  
}


VOID fact_vizio_ret_uart_ack_data(UINT8 * pui1_val, UINT8 error_code ,UINT8 ui1_ack_len, BOOL b_clear_cmd_buf)
{
    UINT8       aui1_ret_buf[CMD_LEN_Maximum];
    UINT8       ui1_i;
	UINT8	ret_checksum = 0x00;
    IOM_UART_T  t_iom_uart;
     
    aui1_ret_buf[0] = 0xff;	//MSG_START
    aui1_ret_buf[1] = 0xfc;	//MSG_TYPE
    aui1_ret_buf[2] = 0x00;	//DATA_SIZE HighByte
	aui1_ret_buf[3] = ui1_ack_len + 1;	//DATA_SIZE LowByte + RET_ERROR
	aui1_ret_buf[4] = error_code;	//RET_ERROR

	
	for(ui1_i=0; ui1_i<ui1_ack_len; ui1_i++)
		aui1_ret_buf[ui1_i+5] = pui1_val[ui1_i];

	for (int i=0; i < (ui1_ack_len+5); i++)
		ret_checksum ^= aui1_ret_buf[i];

	aui1_ret_buf[ui1_ack_len+5] = ret_checksum;		


	// UART output
    t_iom_uart.pui1_data = aui1_ret_buf;
    t_iom_uart.z_len = ui1_ack_len + 6; //MSG_START + MSG_TYPE + DATA_SIZE + RET_ERROR + Checksum
    c_iom_output(h_iom_uart, &t_iom_uart);   
    
    if (b_clear_cmd_buf == TRUE)
    	c_memset(aui1_cmd_buf, 0x00, CMD_LEN_Maximum);  // clear buff
  
}



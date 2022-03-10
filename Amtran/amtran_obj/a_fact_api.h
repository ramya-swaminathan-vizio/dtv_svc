/*----------------------------------------------------------------------------
  AmTRAN Corp. Company Confidential Strictly Private
  $File: a_fact_parser.h
  $Author: sin_heyiwang $
  ---------------------------------------------------------------------------
  >>>>>>>>>>>>>>>>>>>>>>>>> COPYRIGHT NOTICE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  ---------------------------------------------------------------------------
  Copyright 2010 AmTRAN Corp.
  All right reserved.

  AmTRAN owns the sole copyright to this software.
  Any unauthorized use, copy, distribution, reproduction, disclosure of this
  information in whole or in part is prohibited.
 ---------------------------------------------------------------------------*/
#ifndef _A_FACT_API_H_
#define _A_FACT_API_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#define FACT_API_CHECK_FAIL_AND_PRINT_ALL(_condition_for_fail, _ret, _err_string, _ok_string)  \
do{ \
    if (_condition_for_fail)   \
    {   \
        if (NULL != _err_string && '\0' != _err_string[0]) \
        { \
            DBG_LOG_PRINT(("---------[%s]---> %s.\r\n", __FILE__, _err_string)); \
        } \
        return _ret;  \
    }   \
    else \
    { \
        if (NULL != _ok_string && '\0' != _ok_string[0]) \
        { \
            DBG_LOG_PRINT(("---------[%s]---> %s.\r\n", __FILE__, _ok_string)); \
        } \
    } \
}while(FALSE)

#define FACT_API_CHECK_FAIL_AND_PRINT(_condition_for_fail, _ret, _err_string) FACT_API_CHECK_FAIL_AND_PRINT_ALL(_condition_for_fail, _ret, _err_string, "")
#define FACT_API_CHECK_FAIL(_condition_for_fail, _ret) FACT_API_CHECK_FAIL_AND_PRINT_ALL(_condition_for_fail, _ret, "", "")

#define aui1_size       ((unsigned char)170)

typedef struct _UART_CMD_TYPE
{
    unsigned char       ui1_Header;
    unsigned char       ui1_Command_Type;
    unsigned char       ui1_Length;
    unsigned char       ui1_Function_Code;
    unsigned char       aui1_data_payload[aui1_size];
} UART_CMD_TYPE;

#define BV_CMD_HEADER           (0xD3)
#define BV_CMD_SET              (0x87)
#define BV_CMD_GET              (0x97)

#define COMM_CMD_HEADER         (0xC0)
#define COMM_CMD_SET            (0x63)
#define COMM_CMD_GET            (0x73)
#define COMM_ACK_ERROR          (0xFE)
#define COMM_OP_ACK_ERROR       (0x01)

#define COMM_MIN_SIZE           (unsigned char)(0x07)
#define COMM_HEADER_POS         (unsigned char)(0x00)
#define COMM_TYPE_POS           (unsigned char)(0x01)
#define COMM_LEN_POS            (unsigned char)(0x02)
#define COMM_FUNC_POS           (unsigned char)(0x03)
#define COMM_PAY_POS_1          (unsigned char)(0x04)
#define COMM_PAY_POS_2          (unsigned char)(0x05)

#define MAC_ADDRESS_LENGTH      6   //Unit:  byte
#define IP_ADDRESS_LENGTH       4   //Unit:  byte
#define MAX_SSID_LENGTH         32  //Unit:  byte
#define ULPK_KEY_LENGHT         96
#define TV_SN_LENGHT            13
#define DHCP_ON                 0
#define DHCP_OFF                1

#define HDMI_HDCP_BLOCK_LENGTH  160

typedef enum
{
    FACTORY_STATUS_SUCCESS         = 0xE0,
    FACTORY_STATUS_CHKSUM_NG       = 0xE1,
    FACTORY_STATUS_TIMEOUT         = 0xE2,
    FACTORY_STATUS_INVALID_COMMAND = 0xE3,
    FACTORY_STATUS_INVALID_FUNC    = 0xE4,
    FACTORY_STATUS_INVALID_OPC     = 0xE5,
    FACTORY_STATUS_INVALID_ULPK    = 0xE6,
    FACTORY_STATUS_DHCP_TIMEOUT    = 0xE7,
    FACTORY_STATUS_PING_FAIL       = 0xE8,
    FACTORY_STATUS_UNDEFINE_ERROR  = 0xEF

} FACTORY_CMD_STATUS;

typedef enum
{
    FACTORY_Source_TV,
    FACTORY_Source_RGB,
    FACTORY_Source_AV1,
    FACTORY_Source_AV2,
    FACTORY_Source_AV3,
    FACTORY_Source_COMP_1,
    FACTORY_Source_COMP_2,
    FACTORY_Source_COMP_3,
    FACTORY_Source_HDMI_1,
    FACTORY_Source_HDMI_2,
    FACTORY_Source_HDMI_3,
    FACTORY_Source_HDMI_4,
    FACTORY_Source_HDMI_5,
    FACTORY_Source_MMP_BROWSER,
    FACTORY_Source_MMP_PHOTO,
    FACTORY_Source_MMP_AUDIO,
    FACTORY_Source_MMP_VIDEO,
    FACTORY_Source_SCART_1,
    FACTORY_Source_MAX
} FACTORY_CMD_SOURCE;

typedef enum
{
    FACTORY_RGB_Red_Gain,
    FACTORY_RGB_Green_Gain,
    FACTORY_RGB_Blue_Gain,
    FACTORY_RGB_Red_Offset,
    FACTORY_RGB_Green_Offset,
    FACTORY_RGB_Blue_Offset
} FACTORY_CMD_RGB_GAIN_OFFSET;

typedef enum
{
    FACTORY_Red_High,
    FACTORY_Red_Low,
    FACTORY_Green_High,
    FACTORY_Green_Low,
    FACTORY_Blue_High,
    FACTORY_Blue_Low
} FACTORY_CMD_RGB_HIGH_Low;

#if 0 // Removed by david. the indexes of color temp should follow ACFG_CUST_CLR_TEMP_T in acfg_custom_video.h.
typedef enum
{
    FACTORY_Color_Temp_Cool,
    FACTORY_Color_Temp_Normal,
    FACTORY_Color_Temp_Computer,
    FACTORY_Color_Temp_Custom,
} FACTORY_CMD_COLOR_TEMP;
#endif

typedef enum
{
    FACTORY_Backlight_Ctrl_Off             = 0,
    FACTORY_Backlight_Ctrl_DCR             = 3,
    FACTORY_Backlight_Ctrl_OPC             = 4,
    FACTORY_Backlight_Ctrl_Local_Dimming   = 5
} FACTORY_CMD_BACKLIGHT_CTRL;

typedef enum
{
    FACTORY_PIC_CUSTOM,
    FACTORY_PIC_STANDARD,
    FACTORY_PIC_MOVIE,
    FACTORY_PIC_GAME,
    FACTORY_PIC_VIVID,
    FACTORY_PIC_FOOTBALL,
    FACTORY_PIC_GOLF,
    FACTORY_PIC_BASKETBALL,
    FACTORY_PIC_BASEBALL,
    FACTORY_PIC_MAX
} FACTORY_CMD_PIC_MODE;

typedef enum
{
    FACTORY_COMP_Y_GAIN,
    FACTORY_COMP_Pb_GAIN,
    FACTORY_COMP_Pr_GAIN,
    FACTORY_COMP_Y_OFFSET,
    FACTORY_COMP_Pb_OFFSET,
    FACTORY_COMP_Pr_OFFSET,
    FACTORY_VGA_R_GAIN,
    FACTORY_VGA_G_GAIN,
    FACTORY_VGA_B_GAIN,
    FACTORY_VGA_R_OFFSET,
    FACTORY_VGA_G_OFFSET,
    FACTORY_VGA_B_OFFSET,
    FACTORY_1_COMP_Y_GAIN,
    FACTORY_1_COMP_Pb_GAIN,
    FACTORY_1_COMP_Pr_GAIN,
    FACTORY_1_COMP_Y_OFFSET,
    FACTORY_1_COMP_Pb_OFFSET,
    FACTORY_1_COMP_Pr_OFFSET
} FACTORY_CMD_GAIN_OFFSET;

//Add for get value of EFuse embedded gain
typedef enum
{
    FACTORY_COMP_Y_EEFUSE_GAIN,
    FACTORY_COMP_Pb_EEFUSE_GAIN,
    FACTORY_COMP_Pr_EEFUSE_GAIN,
} FACTORY_CMD_COMP_EEFUSE_ADC;

typedef enum
{
    FACTORY_VGA_R_EEFUSE_GAIN,
    FACTORY_VGA_G_EEFUSE_GAIN,
    FACTORY_VGA_B_EEFUSE_GAIN,
    FACTORY_VGA_COMP_Y_EEFUSE_GAIN,
    FACTORY_VGA_COMP_Pb_EEFUSE_GAIN,
    FACTORY_VGA_COMP_Pr_EEFUSE_GAIN,
} FACTORY_CMD_VGA_EEFUSE_ADC;

typedef enum
{
    READ_VGA_EDID=0,
    READ_BLOCK1_HDMI_EDID,
    READ_BLOCK2_HDMI_EDID,
    WRITE_VGA_EDID,
    WRITE_BLOCK1_HDMI_EDID,
    WRITE_BLOCK2_HDMI_EDID,
}eEDID_COMMAND;

typedef enum
{
    READ_BLOCK1_HDMI_HDCP=0,
    READ_BLOCK2_HDMI_HDCP,
    WRITE_BLOCK1_HDMI_HDCP,
    WRITE_BLOCK2_HDMI_HDCP,
}eHDCP_COMMAND;

typedef enum
{
    ANT_0=0,
    ANT_1=1,
    ANT_AUTO=3,
    ANT_0_1=4,
    ANT_0_1_DEBUG=5,
} eANTENNA_TESTING_CMD;

/*=======================

typedef enum
{
    FACTORY_AUD_MTS_UNKNOWN = 0,
    FACTORY_AUD_MTS_MONO,
    FACTORY_AUD_MTS_STEREO,
    FACTORY_AUD_MTS_SUB_LANG,
    FACTORY_AUD_MTS_DUAL1,
    FACTORY_AUD_MTS_DUAL2,
    FACTORY_AUD_MTS_NICAM_MONO,
    FACTORY_AUD_MTS_NICAM_STEREO,
    FACTORY_AUD_MTS_NICAM_DUAL1,
    FACTORY_AUD_MTS_NICAM_DUAL2,
    FACTORY_AUD_MTS_FM_MONO,
    FACTORY_AUD_MTS_FM_STEREO
} FACTORY_CMD_AUD_MTS;

typedef enum
{
    FACTORY_AUD_SPDIF_FMT_OFF = 0,
    FACTORY_AUD_SPDIF_FMT_RAW,
    FACTORY_AUD_SPDIF_FMT_PCM_16,
    FACTORY_AUD_SPDIF_FMT_PCM_24
} FACTORY_CMD_AUD_SPDIF_FMT;

========================*/

typedef enum
{
    Fact_Get_model_qty,
    Fact_Get_model_name,
    Fact_Get_Emanual_filename,
    Fact_Get_Emanual_checksum,
    Fact_Get_retail_filename,
    Fact_Get_retail_checksum,
    Fact_Get_PQ_gamma_checksum,
    Fact_Get_PQ_gamma_SCE_checksum,
    Fact_Get_PQ_qty_checksum,
    Fact_Get_PQ_index,
    Fact_Get_AQ_model_name,
    Fact_Get_AQ_checksum,
    Fact_Get_AQ_index,
    Fact_Get_TCON_checksum,
    Fact_Get_BLC_checksum,
    Fact_Get_EDID_checksum,
} FACTORY_CMD_ModelIndexCheck;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern void _fact_parser_parse_and_set_cmd( void* pv_data, void* pv_val);
extern unsigned char fact_parser_chksum(const void*  pv_data);
extern FACTORY_CMD_STATUS AMT_Fac_Power_OnOff(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_EnterExit_Factory_Mode(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Factory_Mode(unsigned char *Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Reset_Settings(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Save_NVRAM(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Clean_ADC_Flag(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Run_Auto_Color(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Run_Auto_Adjust(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Run_Burning_Mode(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_IRRx_OnOff(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Select_Source(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_EDID_WP_OnOff(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Pic_Mode(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Color_Temp(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Brightness(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Contrast(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Backlight(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_GainOffset(unsigned char Mode,unsigned char Val);
extern FACTORY_CMD_STATUS AMT_Fac_Set_MTS(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Volume(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Treble(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Bass(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Aud_Mode(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Model_Index(unsigned char Index);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Backlight_Control(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_SRS_OnOff(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Flicker_OnOff(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Digital_Aud_Out(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_LS_Control(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Inp_Src(unsigned char *input_name);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Pic_Mode(unsigned char *ui1_value);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ADC_Flag(unsigned char *Mode, unsigned char *ui1_status);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ADC_Gain_Offset(FACTORY_CMD_GAIN_OFFSET Mode, unsigned char *value);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Light_Sensor_Lux(unsigned char *ui1_value ,unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Model_Index(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Ver_Num(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Revison_Num(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Remote_key_code( unsigned char ui1_RemoteCode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Adaptive_Luma( unsigned char ui1_Status);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Flesh_Tone( unsigned char ui1_Status);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Button_Event(unsigned char *ui1_index, unsigned char ui1_length); // David 20181211, sent button event.
extern FACTORY_CMD_STATUS AMT_Fac_Get_TV_Channel(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_TV_MTS(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_CC_INFO(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Timing_INFO(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Signal_Status(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Volume_Value(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Treble(unsigned char *ui1_index, unsigned char *ui1_length);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Bass(unsigned char *ui1_index, unsigned char *ui1_length);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Time_Zone(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Edid_cmd(eEDID_COMMAND eEdidCommand,unsigned char *pEdidData, unsigned char ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Edid_cmd(eEDID_COMMAND eEdidCommand,unsigned char *pEdidData, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_HDMI_HDCP(UINT8 ui1_idx, unsigned char *pc_hdcp);
extern FACTORY_CMD_STATUS AMT_Fac_Get_HDMI_HDCP(UINT8 ui1_idx, unsigned char *pc_hdcp, unsigned char *ui1_length);
extern FACTORY_CMD_STATUS AMT_Fac_Set_HDCP_TEST_KEY(unsigned char data);
extern FACTORY_CMD_STATUS AMT_Fac_Check_Key_Flag(unsigned char * Val);
extern FACTORY_CMD_STATUS AMT_Fac_Clear_Key_Flag(unsigned char * Val);
extern FACTORY_CMD_STATUS AMT_Fac_Get_LIGHTSENSOR_TABLE(UINT8 ui1_idx, unsigned char *pc_table, unsigned char *ui1_bytesize);
extern FACTORY_CMD_STATUS AMT_Fac_Set_LIGHTSENSOR_TABLE(UINT8 ui1_idx, unsigned char *pc_table);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Driving_Current(UINT32);
extern FACTORY_CMD_STATUS AMT_Fac_Set_SSP(UINT32 ui4_val);
extern FACTORY_CMD_STATUS AMT_Fac_DUMP_LED_SENSOR_INFO(UINT8 ui1_idx);

extern FACTORY_CMD_STATUS AMT_Fac_Set_HDMI_Default_edid(void);
extern FACTORY_CMD_STATUS AMT_Fac_Set_VGA_Default_edid(void);
extern void AMT_Fac_Get_Menu_Level(unsigned char *Page_COND, unsigned char *Page_Level);
extern unsigned char AMT_Fac_Get_Menu_Tab_index(void);
extern void AMT_Fac_Get_Menu_Page_Item_Type_Index(unsigned char *ui1_item_type, unsigned char *ui1_item_idx);
extern unsigned char AMT_Fac_Get_Menu_Page_Item_e_state(void);
extern unsigned char AMT_Fac_Get_Menu_Page_Item_type_vlaue( signed short *i4_range_vlaue);

//eth
extern FACTORY_CMD_STATUS AMT_Fac_Set_Eth_IP(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Eth_IP(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Eth_Mac_Addr(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Eth_Mac_Addr(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Eth_SelfTest(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS  AMT_Fac_Get_Eth_IP_By_TV_SN(unsigned char *ui1_index, unsigned char *ui1_lenght);

//wifi
extern FACTORY_CMD_STATUS AMT_Fac_Set_Wifi_IP(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Wifi_IP(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Wifi_Mac_Addr(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Wifi_SelfTest(unsigned char *ui1_index, unsigned char *ui1_data, unsigned char *ui1_lenght);

// BT
extern FACTORY_CMD_STATUS AMT_Fac_Get_BT_Mac_Addr(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_BT_RSSI_Display(BOOL b_enable);
extern FACTORY_CMD_STATUS AMT_Fac_Get_BT_RSSI(unsigned char *ui1_value);


//burning
extern FACTORY_CMD_STATUS AMT_Fac_Get_Burning_Time(unsigned char *ui1_index, unsigned char *ui1_lenght);

//ULPK
extern FACTORY_CMD_STATUS AMT_Fac_Set_ULPK_Data(unsigned char* ui1_index, unsigned char ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ULPK_Data(unsigned char* ui1_index, unsigned char *ui1_lenght);

//SN
extern FACTORY_CMD_STATUS AMT_Fac_Set_SN_Data(unsigned char* ui1_index, unsigned char ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_SN_Data(unsigned char* ui1_index, unsigned char *ui1_lenght);

//POTK
extern FACTORY_CMD_STATUS AMT_Fac_Set_POTK_Data(unsigned char* ui1_index, unsigned char ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_POTK_Check(unsigned char* ui1_index, unsigned char ui1_lenght);

extern FACTORY_CMD_STATUS AMT_Fac_Set_Gain_Offset_To_Other_Source(unsigned char Mode ,unsigned char Value);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Factory_Record(unsigned char *offset, unsigned char *value,unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Factory_Record(unsigned char *offset, unsigned char *value,unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_SRS_TruVolume_OnOff(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_3D_Mode(unsigned char Mode, unsigned char Type);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Wide_Mode(unsigned char Mode); // David 20181210, set wide mode

extern FACTORY_CMD_STATUS AMT_Fac_Get_CEC_Data(unsigned char *name ,unsigned char *ui1_lenght);

extern FACTORY_CMD_STATUS AMT_Fac_Set_Wifi_Parmater(unsigned char *data);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Wifi_Parmater(unsigned char *data,unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Wifi_result(unsigned char *data,unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Wifi_Vendor(unsigned char *data,unsigned char *ui1_lenght);

extern FACTORY_CMD_STATUS AMT_Fac_Set_TV_Speaker(unsigned char on_off);
extern FACTORY_CMD_STATUS AMT_Fac_Set_TV_Channel(unsigned char *Type,unsigned char *Channel);
extern FACTORY_CMD_STATUS AMT_Fac_Set_CC_INFO(unsigned char Mode, unsigned char ui1_index);

extern FACTORY_CMD_STATUS  AMT_Fac_Get_Eep_Gamma_Key(unsigned char mode,unsigned char *key);
extern FACTORY_CMD_STATUS  AMT_Fac_Set_Eep_Gamma_Key(unsigned char mode,unsigned char key);
extern FACTORY_CMD_STATUS  AMT_Fac_Save_17PointGamma(void);
extern FACTORY_CMD_STATUS  AMT_Fac_Get_17PointGamma(unsigned char Index,unsigned char *RVal_Hi,unsigned char *RVal_Lo,unsigned char *GVal_Hi,unsigned char *GVal_Lo,unsigned char *BVal_Hi,unsigned char *BVal_Lo);
extern FACTORY_CMD_STATUS  AMT_Fac_Set_17PointGamma(unsigned char Index,unsigned char R_Hi,unsigned char R_Lo,unsigned char G_Hi,unsigned char G_Lo,unsigned char B_Hi,unsigned char B_Lo);
extern FACTORY_CMD_STATUS  AMT_Fac_Set_Default_17PointGamma();

#ifdef WHITE_PATTERN_MODIFICATION
extern FACTORY_CMD_STATUS AMT_Fac_Set_White_Pattern_OnOff(unsigned char uc_mode, unsigned char uc_val);
#else
extern FACTORY_CMD_STATUS AMT_Fac_Set_White_Pattern_OnOff(unsigned char Mode);
#endif
extern FACTORY_CMD_STATUS AMT_Fac_Set_TV_DEF_CHANNEL(unsigned char data);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Gamma_Curve(unsigned char ui1_index); // Added by david.
extern FACTORY_CMD_STATUS AMT_Fac_Get_Gamma_Curve(unsigned char *ui1_index); // Added by david.
extern FACTORY_CMD_STATUS AMT_Fac_Set_Wifi_Disconnect(unsigned char data);
extern FACTORY_CMD_STATUS AMT_Fac_Set_EFuse_Gain_Mode (unsigned char ui1_mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_EFuse_Gain_Mode (unsigned char* ui1_mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Vcom_Data (unsigned char* ui1_value, unsigned char* ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Vcom_Data (unsigned char* ui1_value, unsigned char* ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Global_Volume(unsigned char input, unsigned char value);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Global_Volume(unsigned char input, unsigned char *value);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Audio_Bypss_Mode(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Audio_Bypss_Mode(unsigned char* Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_SAC_INFO(unsigned char ui1_Status);
extern FACTORY_CMD_STATUS AMT_Fac_Get_SAC_INFO(unsigned char* Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_CEC_Function(unsigned char ui1_Status);
extern FACTORY_CMD_STATUS AMT_Fac_Get_CEC_Function(unsigned char* Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Set_CMD_Data(unsigned char* ui1_index, unsigned char ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Burning_Mode(unsigned char *Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Color_Temp(unsigned char *Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Brightness(unsigned char *Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Contrast(unsigned char *Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Backlight(unsigned char *Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_GainOffset(unsigned char Mode,unsigned char *Val);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Running_Time(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_EEPROM_Data (unsigned char* ui1_value, unsigned char* ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_VGA_EEFUSE_ADC (FACTORY_CMD_VGA_EEFUSE_ADC Mode, unsigned char *value, unsigned char *data_payload_1);
extern FACTORY_CMD_STATUS AMT_Fac_Get_COMP_EEFUSE_ADC (FACTORY_CMD_COMP_EEFUSE_ADC Mode, unsigned char *value, unsigned char *data_payload_1);
extern FACTORY_CMD_STATUS AMT_Fac_Get_PQ_SCE_INPUT_CAP (unsigned char* ui1_value, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ULPK_Status(unsigned char* ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Eth_Connection(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ModelIndexCheck(unsigned char* ui1_index, unsigned char *ui1_lenght);
// USB
extern FACTORY_CMD_STATUS AMT_Fac_Get_USB_Cnt(unsigned char *pui1_cnt);
/*
extern FACTORY_CMD_STATUS AMT_Fac_Set_Mic_Volume(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Mic_Volume(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Echo_Volume(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Echo_Volume(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_Karaoke_Status(unsigned char Mode);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Karaoke_Status(unsigned char *ui1_index, unsigned char *ui1_lenght);
*/
extern FACTORY_CMD_STATUS AMT_Fac_Set_Keypad_Status(unsigned char ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Keypad_Status(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Keypad_ADC_value(unsigned char *ui1_index, unsigned char *ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Set_LED_Logo(unsigned char ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_LED_Logo(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Set_ALS_Calibration_Data(unsigned char *pui1_buf, unsigned char ui1_lenght);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ALS_Queue(unsigned char *pui1_buf, unsigned char *pui1_length);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ALS_Calibration_Data(unsigned char *pui1_buf, unsigned char ui1_size, unsigned char *pui1_length);
extern FACTORY_CMD_STATUS AMT_Fac_Set_ALS_Calibration_Status(unsigned char *pui1_buf);
extern FACTORY_CMD_STATUS AMT_Fac_Get_ALS_Calibration_Status(unsigned char *pui1_buf, unsigned char ui1_size, unsigned char *pui1_length);

extern FACTORY_CMD_STATUS AMT_Fac_Set_Gain_Offset_To_Other_Color_Temp(unsigned char ui1_mode_src ,unsigned char ui1_mode_dest); // Added by david.
extern FACTORY_CMD_STATUS AMT_Fac_Set_11PointGamma(unsigned char Index,unsigned char RVal,unsigned char GVal,unsigned char BVal);
extern FACTORY_CMD_STATUS AMT_Fac_Get_11PointGamma(unsigned char Index,unsigned char *RVal,unsigned char *GVal,unsigned char *BVal);
extern FACTORY_CMD_STATUS AMT_Fac_Get_POTK_Status(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Get_REG_Status(unsigned char *ui1_index);
extern FACTORY_CMD_STATUS AMT_Fac_Exit_OOBE(void);
#if 0
extern FACTORY_CMD_STATUS AMT_Fac_Set_Default_Burning_Flag(unsigned char ui1_val);
extern FACTORY_CMD_STATUS AMT_Fac_Get_Default_Burning_Flag(unsigned char *pui1_val);
#endif

extern void Burning_Wifi_Test(void);
extern void Fake_SSID(void);
extern void Record_RunningTime_Procedure(void); //Add for Get Running Time
#endif /*_A_FACT_PARSER_H_*/


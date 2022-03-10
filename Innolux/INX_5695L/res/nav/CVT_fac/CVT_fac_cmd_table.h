#ifndef __CVT_FAC_CMD_TABLE_H
#define __CVT_FAC_CMD_TABLE_H

#include "app_util/a_common.h"

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long  int u32;

#define CVT_OK    0
#define CVT_FAIL  1
#define CVT_WRITE_FAIL 2

#define CVT_TEST_OK 0
#define CVT_TESTING 1
#define CVT_TEST_FAIL 2

#define CVT_TTY_PACKET_MIN_SIZE 6

#define CVT_TTY_CMD_SYNC_BYTE   0xff
#define CVT_TTY_CMD_START_BYTE  0x33

typedef enum
{
    RF_AUTO_TEST = 0x01,
    AUTO_WB,
    FAC_AT_TEST,
    AUTO_SIGNAL,
    PROJECT_ID_MAX,     //illegal
}tty_cvt_cmd_project_ID;

typedef enum
{
    START_HDCP = 0x00,
    ACK,
    RET_START_HDCP,
    SEND_HDCP_DATA,
    SEND_HDCP_CRC,
    ACK_HDCP_STATUS,

    START_CI_PLUS = 0x06,
    RET_START_CI_PLUS,
    SEND_CI_PLUS_DATA,
    SEND_CIPLUS_CRC,
    ACK_CI_PLUS_STATUS,

    SET_MAC_ADDR = 0x0B,
    GET_MAC_ADDR,
    RET_MAC_ADDR,

    GET_HDCP_KEY_ID = 0x0E,
    RET_HDCP_KEY_ID,

    GET_MAX_LEN = 0x10,
    RET_MIN_LEN,

    GET_CHECKSUM = 0x12,
    RET_CHECKSUM,

    GET_SOURCE = 0x14,
    RET_SOURCE,
    SET_SOURCE,

    SET_VOLUME = 0x17,

    SET_CHANNEL = 0x18,
    CHANGE_CHANNEL_NUM,

    CTRL_IO = 0x1A,

    GET_CIPLUS_KEY_ID = 0x1B,
    RET_CIPLUS_KEY_ID,

    GET_KEYPAD_STATUS = 0x1D,
    RET_KEYPAD_STATUS,

    SET_BARCODE = 0x1F,
    GET_BARCODE,
    RET_BARCODE,

    GET_HDCP_KSV = 0x22,
    RET_HDCP_KSV,

    SET_ATSC_AIR_CABLE = 0x24,
    RET_ATSC_AIR_CABLE,
    SET_ATSC_PRO_NUM,

    GET_TOOL_VERSION = 0x27,
    RET_TOOL_VERSION,

    CHECK_CI_FUNC = 0x29,
    RET_CI_FUNC_STATUS,

    GET_IP_INFO = 0x31,
    RET_IP_INFO,

    GET_WIFI_STATUS = 0x33,
    RET_WIFI_STATUS,

    GET_USB_COUNT = 0x35,
    RET_USB_COUNT,

    SEND_CVTE_FAC_IR = 0x37,

    CHECK_BLUETOOCH = 0x38,
    RET_BLUETOOCH_STATUS,

    START_SEND_FILE = 0x40,
    RET_START_SEND_FILE,
    SEND_FILE_DATA,
    SEND_FILE_CRC,
    ACK_FILE_STATUS,
    GET_FILE_ID,
    RET_FILE_ID,

    CTRL_KEYPAD_FUNC = 0x47,

    SET_PANEL_MODEL_ID = 0x48,
    GET_PANEL_MODEL_ID = 0x49,

    SET_TCL_DEVICE_ID = 0x50,
    GET_TCL_DEVICE_ID,
    RET_TCL_DEVICE_ID,

    GET_USB_DEVICES_STAT = 0x53,
    RET_USB_DEVICES_STAT,

    SET_COMM_CMD = 0x55,
    RET_COMM_CMD,

    GET_FIXED_CHECKSUM = 0x57,
    RET_FIXED_CHECKSUM,

    SET_CFG_MAC_ADDR = 0x59,
    GET_CFG_MAC_ADDR,
    RET_CFG_MAC_ADDR,

    SET_CUSTOMER_BARCODE = 0x5c,
    GET_CUSTOMER_BARCODE,
    RET_CUSTOMER_BARCODE,

    GET_AGING_STATUS = 0x5F,
    RET_AGING_STATUS,

    SET_PROJECTID = 0x61,
    GET_PROJECTID,
    RET_PROJECTID,

    SET_MODELINDEX = 0x64,
    GET_MODELINDEX,
    CHECK_HDCP_KEY1_X = 0x66,
    CHECK_HDCP_KEY2_X,

    SET_HDMI_EDID=0xA6,
    CHECK_HDMI_EDID,

    MAX_CMD_ID,
}tty_cvt_cmd_ID;

typedef enum
{
    CVT_FAC_RESET,
    CVT_FAC_GET_MODEL_NAME,
    CVT_FAC_GET_MODEL_INDEX,
    CVT_FAC_CHECK_HDCP_KEY1_4,
    CVT_FAC_CHECK_HDCP_KEY2_2,
    CVT_FAC_GET_MMCBLK_NUM,
    CVT_FAC_SET_MODEL_INDEX,
    CVT_FAC_GET_TCON_CHECKSUM,
    CVT_FAC_SET_MOTOR_DOWN,
    CVT_FAC_SET_MOTOR_UP,
    CVT_FAC_GET_MIC_VALUE,
    CVT_FAC_CHECK_MIC,
    CVT_FAC_SET_MIC_LED,
}common_command;

typedef enum
{
    ACK_CHILD_ID = 0x05,
    ACK_RETURN_TYPE = 0x06,
    ACK_ASCII_DATA = 0x07,
}common_command_ack;

typedef enum {
    EN_AT_ATV = 0,
    EN_AT_DTV,
    EN_AT_DVBS,
    EN_AT_DVBC,
    EN_AT_DVBT,
    EN_AT_DVBT2,
    EN_AT_VGA,
    EN_AT_VGA2,
    EN_AT_HDMI1,
    EN_AT_HDMI2,
    EN_AT_HDMI3,
    EN_AT_HDMI4,
    EN_AT_HDMI5,
    EN_AT_SCART1,
    EN_AT_SCART2,
    EN_AT_AV1,
    EN_AT_AV2,
    EN_AT_AV3,
    EN_AT_AV4,
    EN_AT_YPBPR1,
    EN_AT_YPBPR2,
    EN_AT_YPBPR3,
    EN_AT_YPBPR4,
    EN_AT_USB1,
    EN_AT_USB2,
    EN_AT_USB3,
    EN_AT_USB4,
    EN_AT_SVIDEO1,
    EN_AT_SVIDEO2,
    EN_AT_DVD,
    EN_AT_OTHER,
    EN_AT_VGA3,
    EN_AT_VGA4,
    EN_AT_SOURCE_MAX,
}en_CVTE_AT_SOURCE; 

typedef enum {
    EN_AT_LVDS_PIN = 0,
    EN_AT_BLON_PIN,
    EN_AT_ADJ_PWM_PIN,
    EN_AT_DVD5V_PIN,
    EN_AT_DVDIR_PIN,
    EN_AT_DVD12V_PIN,
    EN_AT_DVDDAT_PIN,
    EN_AT_IO_MAX,
}en_CVTE_AT_IOPin;

typedef enum {
    EN_AT_LOW = 0,
    EN_AT_HIGH,
    EN_AT_LEVEL_MAX,
}en_CVTE_AT_IO_LEVEL;

typedef enum {
    EN_NONE_KEY = 0,
    EN_HDCP_KEY,
    EN_CI_PLUS_KEY,
    EN_HDCP_20G,
    EN_HDCP_22G,
    EN_WIDEVINE_KEY,    //cus1 = 5
    EN_ESN_KEY,         //cus2 = 6
    EN_KEY_MAX,
}en_key_type_live;

typedef enum{
    Ethernet_MAC = 0x00,
    WIFI_MAC,
    Bluetooth_MAC,
    Customer1_MAC,
    Customer2_MAC,
    Customer3_MAC,
}en_Mac_Addr_type;

typedef struct
{
    UINT8                  data_length;
    tty_cvt_cmd_project_ID  project_ID;
    tty_cvt_cmd_ID              cmd_ID;
    UINT8*                 p_data_buff;
}tty_cvt_cmd_pcaket;

typedef enum
{
    ACK_SYN_IDX = 0x00,
    ACK_BEGIN_IDX,
    ACK_PACKET_SIZE_IDX,
    ACK_PROJECT_ID_IDX,
    ACK_ACK_ID_IDX,
}tty_cvt_cmd_ACK_pcaket;

typedef enum{
    ACK_LONG_ERROR_CODE_IDX = 0x05,
    ACK_LONG_ID_FOR_ACK_IDX,
    ACK_LONG_DATA_IDX,
}tty_cvt_cmd_ACK_pcaket_type1;

typedef enum
{
    ACK_SHORT_DATA_IDX = 0x05,
}tty_cvt_cmd_ACK_pcaket_type2;

typedef enum
{
    HDCP1Px = 0x01,
    CIPlus,
    HDCP2P0,
    HDCP2P2,
    CUS1,
    CUS2,
    CUS3,
    CUS4,
    CUS5,
    FAC_FILE_TYPE_MAX,
}tty_cvt_cmd_fac_file_type;
/*****************************************************************************
 *                                  STRUCT
 * **************************************************************************/
typedef struct {
    /* 
     * »ñÈ¡TV°å¿¨Checksum 
     * ========================================================================
     * Ó¦ÓÃ²ÎÊý checksum·µ»ØchecksumÊý×é
     * ·µ»ØÖµ·µ»Ø Êý×é³¤¶È
     * */
    u8 (*CVTE_GetTVChecksum)(u8* checksum);

    /* 
     * ÉèÖÃ°å¿¨Í¨µÀ 
     * ========================================================================
     * ·µ»Ø£º0-ok, 1-fail
     * */
    u8 (*CVTE_SetTVSource)(en_CVTE_AT_SOURCE source);

    /* 
     * »ñÈ¡TV°å¿¨Í¨µÀ 
     * ========================================================================
     * Í¨¹ýÒýÓÃ²ÎÊýsource·µ»ØÍ¨µÀID
     * ·µ»Ø:0-ok, 1-fail
     * */
    u8 (*CVTE_GetTVSource)(en_CVTE_AT_SOURCE *source);

    /*
     * ÉèÖÃ°å¿¨ÒôÁ¿ 
     * ========================================================================
     * ²ÎÊý£ºvolume - [0-100] ÒôÁ¿Öµ
     * ·µ»Ø£º0-ok, 1-fail
     * */
    u8 (*CVTE_SetVolume)(u8 volume);

    /* ÉèÖÃ°å¿¨ÆµµÀ£¬Î´Ê¹ÓÃ */
    u8 (*CVTE_SetTVChannel)(void);

    /*
     * ÇÐÌ¨Ö¸Áî£¬TVÐèÒª¸ù¾ÝËùÔÚÍ¨µÀ½øÐÐ²Ù×÷£¬ÈçÔÚDTV£¬ÔòÇÐ»»DTVµÄ½ÚÄ¿ 
     * ========================================================================
     * ²ÎÊý num: ÉèÖÃµÄÌ¨ºÅ
     * ·µ»Ø£º0-ok, 1-fail
     *
     * */
    u8 (*CVTE_ChangeTVNum)(u16 num);

    /*
     * TV°å¿é´®¿ÚÊä³ö½Ó¿Ú 
     * ========================================================================
     * ²ÎÊý datas: ´ýÊä³öµÄ×Ö·û´®
     *      len:   ×Ö·û´®³¤¶È
     *
     * ·µ»Ø£º0-ok, 1-fail
     * ÃèÊö£º
     *      µ÷ÓÃTV°å¿¨µÄ´®¿ÚÊä³öº¯Êý£¬Êä³ö±¾¿âµÄÍ¨ÐÅÐÅÏ¢
     * */
    u8 (*CVTE_UsartSendData)(u8* datas, u16 len);

    /* 
    * »ñÈ¡MACµØÖ· 
    * ========================================================================
    * ²ÎÊý£º
    *	   macAddr:´ý·µ»ØµÄmacµØÖ·
    * ·µ»Ø£º
    *	   0-ok, 1-fail
    *
    * ÃèÊö£º
    *	   MACµØÖ·
    * */
    u8 (*CVTE_GetTVMacAddr)(UINT8* ui1_macAddr);
    /*
    * »ñÈ¡TV HDCP KEYµÄÎ¨Ò»Âë 
    * ========================================================================
    * ²ÎÊý:
    *	   hdcpId : ·µ»ØµÄIDÊýÖµ
    * ·µ»Ø£º0-ok, 1-fail
    * */
    u8 (*CVTE_GetTVHDCP_ID)(u32* hdcpId);

    /* 
    * »ñÈ¡TV CI+ KEY Î¨Ò»Âë 
    * ========================================================================
    * ²ÎÊý: 
    *	   ciplusId : ·µ»ØµÄIDÖµ
    * ·µ»Ø£º0-ok, 1-fail
    * */
    u8 (*CVTE_GetTVCIPlus_ID)(u32* ciplusId);

    /* 
    * ±£´æHDCP KEY 
    * ========================================================================
    * ²ÎÊý£º
    *	   key: KEYÊý¾Ý
    *	   len: ³¤¶È
    *	   fileID: ¸ÃkeyµÄIDÖµ£¬½«Ð´Èë°å¿¨
    * ·µ»Ø£º
    * 0£º ÉÕÂ¼³É¹¦
    * 2£º ÉÕÂ¼Ê§°Ü
    * 
    * ÃèÊö£º
    *	   ¸ÃÖ¸Áî°ÑKEYÐ´ÈëFLASHÖÐ
    */
    u8 (*CVTE_SaveHDCPKeyToTV)(u8* key, u32 len, u32 fileId);

    /* 
    * ±£´æCI+ KEY 
    * ========================================================================
    * ²ÎÊý£º
    *	   key: KEYÊý¾Ý
    *	   len: ³¤¶È
    *	   fileID: ¸ÃkeyµÄIDÖµ£¬½«Ð´Èë°å¿¨
    * ·µ»Ø£º
    * 0£º ÉÕÂ¼³É¹¦
    * 2£º ÉÕÂ¼Ê§°Ü
    * 
    * ÃèÊö£º
    *	   ¸ÃÖ¸Áî°ÑKEYÐ´ÈëFLASHÖÐ
    */

    u8 (*CVTE_SaveCIPlusKeyToTV)(u8* key, u32 len, u32 fileId);
    /* 
    *
    * ±£´æMACµØÖ·
    * ========================================================================
    * ·µ»Ø£º
    * 0£º ÉÕÂ¼³É¹¦
    * 2£º ÉÕÂ¼Ê§°Ü
    *
    * */
    u8 (*CVTE_SaveMACAddrToTV)(UINT8* ui1_macAddr);

    /*
    * ÉèÖÃTV°å¿¨µÄIO µçÆ½
    * ========================================================================
    * ²ÎÊý£º
    *	   pin: ¶¨ÒåµÄ´ý¿ØÖÆio ¿Ú
    *	   level: io¿ØÖÆµÄ·½Ïò
    *
    * ·µ»Ø£º0-ok, 1-fail
    * */
    u8 (*CVTE_CtrlIOLevel)(en_CVTE_AT_IOPin pin, en_CVTE_AT_IO_LEVEL level);

    /**
    * »ñÈ¡µ±Ç°°´¼ü°å×´Ì¬
    * ========================================================================
    * ²ÎÊý£º
    *	   keyStatus:
    *	   °´¼ü°åµÄ×´Ì¬£º D7 D6 D5 D4 D3 D2 D1 D0
    *					|  |  |  |	|  |  |  |
    *				   K7 K6 K5 K4 K3 K2 K1 K0
    *	   0:´ú±íÎ´°´ÏÂ£¬1£º´ú±í°´ÏÂ
    * ·µ»Ø£º
    *	   0 - ok
    *	   1 - fail
    */
    u8 (*CVTE_GetCurrentKeyPadStatus)(u8* keyStatus);

    /**
    * Ð´barcodeµ½°å¿¨flashÀïÃæ
    * ========================================================================
    * ²ÎÊý£º
    *	   barcode- ÌõÐÎÂëÊý×é
    *	   len	  - ÌõÐÎÂë³¤¶È
    * ·µ»Ø£º
    *	  0 - success
    *	  1 - fail
    */
    u8 (*CVTE_SaveBarcodeToFlash)(u8* barcode, u8 len);

    /**
    * ·µ»Ø°å¿¨ÌõÐÎÂë
    * ========================================================================
    * ²ÎÊý£º
    *	  retBarcode - ´ý·µ»ØµÄbarcodeÊý×é
    *	  len - barcodeµÄ³¤¶È£¬Èç¹û¶ÁÈ¡²»µ½»ò²»³É¹¦£¬Ôò·µ»Ø 0
    * ·µ»Ø£º
    *	  0 - ok
    *	  1 - fail
    */
    u8 (*CVTE_GetBarcodeFromFlash)(u8* retBarcode, u8* len);

    /**
    * Ð´¿Í»§×Ô¶¨ÒåµÄbarcodeµ½°å¿¨flashÀïÃæ
    * ========================================================================
    * ²ÎÊý£º
    *	   type    - ÉÕÂ¼µÄÓÃ»§ÀàÐÍ
    *	   barcode - ÌõÐÎÂëÊý×é
    *	   len	   - ÌõÐÎÂë³¤¶È
    * ·µ»Ø£º
    *	  0 - success
    *	  1 - fail
    */
    u8 (*CVTE_SaveCustomerBarcodeToFlash)(u8 type, u8* barcode, u8 len);

    /**
    * ·µ»ØÓÃ»§×Ô¶¨Òå°å¿¨ÌõÐÎÂë
    * ========================================================================
    * ²ÎÊý£º
    *	  type		 - ÉÕÂ¼µÄÓÃ»§ÀàÐÍ
    *	  retBarcode - ´ý·µ»ØµÄbarcodeÊý×é, Ä©Î²±ØÐëÌí¼Ó '\0'
    *	  len		 - barcodeµÄ³¤¶È£¬Èç¹û¶ÁÈ¡²»µ½»ò²»³É¹¦£¬Ôò·µ»Ø 0
    * ·µ»Ø£º
    *	  0 - ok
    *	  1 - fail
    */
    u8 (*CVTE_GetCustomerBarcodeFromFlash)(u8 type, u8* retBarcode, u8* len);


    /**
    * ·µ»ØKSVÊý×é
    * ========================================================================
    * ²ÎÊý£º
    *	   ksvCode:·µ»ØµÄÊý×éÖ¸Õë£¬ ³¤¶È¹Ì¶¨Îª5¸öbyte
    *	   k[4] : D39-D32 : retcmd[5]
    *	   k[3] : D31-D24 : retcmd[6]
    *	   K[2] : D23-D16 : retcmd[7]
    *	   K[1] : D15-D8  : retcmd[8]
    *	   K[0] : D7-D0   : retcmd[9]
    * ·µ»Ø£º
    *	  0 - OK
    *	  1 - FAIL
    */
    u8 (*CVTE_GetHDCP_KSV_Code)(u8* ksvCode);

    /**
    * ÉèÖÃATSCÄ£Ê½
    * ·µ»ØATSCÉèÖÃºóµÄÄ£Ê½
    * ========================================================================
    * ²ÎÊý£º
    *	   type: 0 - AIR
    *			 1 - CABLE
    * ·µ»Ø£º
    *	   0 - air
    *	   1 - cable
    */
    u8 (*CVTE_SetATSC_AIR_CABLE_mode)(u8 type);

    /**
    * ÉèÖÃATSCÆµµã
    * ========================================================================
    * ²ÎÊý£º
    *	   majorPro: Ö÷ÆµµÀºÅ
    *	   minorPro: ´ÎÆµµÀºÅ
    * ·µ»Ø£º
    *	   0 - ok
    *	   1 - faile
    */
    u8 (*CVTE_SetATSC_ProNumber)(u8 major, u8 minor);


    /**
    * »ñÈ¡CI ¿¨ ¹¦ÄÜ×´Ì¬
    * ========================================================================
    * ²ÎÊý£º
    *	  u8* status: ´ý·µ»ØµÄ½á¹û
    *				  0 - OK
    *				  1 - Î´²åÈë
    *				  2 - CI¹¦ÄÜÒì³£
    * ·µ»Ø£º
    *	  0 - ok
    *	  1 - faile
    */
    u8 (*CVTE_GetCIFunctionStatus)(u8* status);

    /**
    * »ñÈ¡IPµØÖ·£¬ ¿ÉÒÔÊÇIPV6, Ò²¿ÉÒÔÊÇIPV4
    * ========================================================================
    * ²ÎÊý£º
    *	  u8* ipStr: IP bufferÖ¸Õë
    * ·µ»Ø£º
    *	  IP´®µÄ³¤¶È
    */
    u8 (*CVTE_GetIPAddr)(UINT8* ui1_ip);

    /**
    * »ñÈ¡WIFI²âÊÔ½á¹û
    * ========================================================================
    * ²ÎÊý£º
    *	  u8* status: ²âÊÔ½á¹û
    *								  0 - OK
    *								  1 - Testing
    *		  2 - Failed
    * ·µ»Ø£º
    *	  0 - OK
    *	  1 - Faile
    */
    u8 (*CVTE_GetWifiTestResult)(u8* status);

    /**
    * »ñÈ¡USBÁ¬½Ó×´Ì¬
    * ========================================================================
    * ²ÎÊý£º
    *	  u8* usb_count - USBÁ¬½Ó¸öÊý
    * ·µ»Ø£º
    *	  0 - OK
    *				  1 - Faile
    */
    u8 (*CVTE_GetUSBConnectCount)(u8* usb_count);

    /**
    * ¼ì²âBluetooth²âÊÔ×´Ì¬
    *=========================================================================
    * ²ÎÊý£º
    *			  u8* status			  - test result
    *													  0 - OK
    *													  1 - Testing
    *													  2 - Failed
    * ·µ»Ø£º
    *			  0 - EXIT_SUCCESS
    *			  1 - EXIT_FAILED
    */
    u8 (*CVTE_CheckBluetoothStatus)(u8* status);


    /**
    * ¹¤³§Ò£¿ØÆ÷´®¿Ú²Ù×÷Èë¿Ú£¬½ÓÊÜCVTE¹¤³§Ò£¿ØÆ÷°´¼üÂëÖµ£¬ÈçÒªÖ§³ÖÆäËûÐ­Òé£¬ÐèÒª
    * ÌáÇ°¸æÖª²âÊÔ³ÌÐò
    *=========================================================================
    * ²ÎÊý£º
    *			  key_code - Ò£¿Ø°´¼üÂëÖµ
    * ·µ»Ø£º 0 - EXIT_SUCCESS
    *				1 - EXIT_FIALED
    */
    u8 (*CVTE_FAC_IR_Ctrl)(u8 key_code);

    /**
    * Get Aging status.
    *========================================================================
    * Parames:
    *	   u8 type: 
    *	   u8* status: 
    * return:
    *	   0 - SUCCESS
    *	   1 - function error
    */
    u8(*CVTE_GetAgingStatus)(u8 type, u32* status);

    /** 
    * ±£´æÎÄ¼þµ½flash 
    * ========================================================================
    * ²ÎÊý£º
    *	   buf: ÎÄ¼þÊý¾Ý
    *	   len: ³¤¶È
    *	   fileID: ¸ÃÎÄ¼þµÄÎ¨Ò»IDÖµ£¬½«Ð´Èë°å¿¨
    *	   filetype:ÎÄ¼þÀàÐÍ
    * ·µ»Ø£º
    * 0£º ÉÕÂ¼³É¹¦
    * 2£º ÉÕÂ¼Ê§°Ü
    * 
    * ÃèÊö£º
    *	   ¸ÃÖ¸Áî°ÑÎÄ¼þÐ´ÈëFLASHÖÐ
    */
    u8 (*CVTE_FAC_write_file)(UINT8* buf, u32 len, u8 filetype);

    /**
    * Get file unique id
    * ========================================================================
    * Parames:
    *	   u8 filetype: the file type which one you get id
    *	   u32* fileId: the point for return result
    * return:
    *	   0: SUCCESS
    *	   1: Get id error
    *	   2: no filetype id;
    */
    u8(*CVTE_FAC_get_file_id)(u8 filetype, u32* fileId);

    /**
    * Get widevine device id, the global unique id for widevine
    * ========================================================================
    * Parames:
    *	   u8* deviceId: the pointer for device id itself
    *	   int* length: the point for device id length
    * return:
    *	   0: SUCCESS
    *	   1: Fail
    */
    u8 (*CVTE_FAC_get_widevine_device_id)(u8* widevineKeyId,int* widevineKeyIdLength);

    /**
    * Get esn device id, the global unique id for widevine
    * ========================================================================
    * Parames:
    *	   u8* deviceId: the pointer for device id itself
    *	   int* length: the point for device id length
    * return:
    *	   0: SUCCESS
    *	   1: Fail
    */
    u8 (*CVTE_FAC_get_esn_device_id)(u8* esnKeyId,int* esnKeyIdLength);

    /**
    * check file type can be used
    *========================================================================
    * Parames:
    *	   u8 filetype: the file type
    *	   u8* result: 0- can be use,1-aready exist ,2-useless
    * return:
    *	   0 - SUCCESS
    *	   1 - function error
    */
    u8 (*CVTE_FAC_check_filetype)(u8 filetype, u8* result);

    u8 (*CVTE_FAC_ctrl_keypad)(u8 enable,u8 *result);

    u8 (*CVTE_GetMmcBlkCount)(u8 *result);

    u8 (*CVTE_GetTconChecksum)(u32 *checksum);

}st_CVTE_AT_RegFunction; 

#endif

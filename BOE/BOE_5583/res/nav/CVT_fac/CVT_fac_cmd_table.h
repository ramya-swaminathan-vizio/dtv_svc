#ifndef __CVT_FAC_CMD_TABLE_H
#define __CVT_FAC_CMD_TABLE_H

#include "app_util/a_common.h"

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long  int u32;



#define CVT_OK    0
#define CVT_FAIL  1
#define CVT_WRITE_FAIL 2
#define CVT_CMD_COMPLETE 3
#define CVT_CMD_RUNNING 4
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

    BOE_GET_ULPK_INDEX = 0x70,
    RET_BOE_GET_ULPK_INDEX = 0x71,
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
	BOE_ULPK_KEY,  //tmp value for boe,not belong to CVTE AT
	BOE_POTK_KEY, 
	BOE_SERIEL_NUMBER,
	FAC_FILE_TYPE_MAX,
}tty_cvt_cmd_fac_file_type;
/*****************************************************************************
 *                                  STRUCT
 * **************************************************************************/
typedef struct {
    /* 
     * 获取TV板卡Checksum 
     * ========================================================================
     * 应用参数 checksum返回checksum数组
     * 返回值返回 数组长度
     * */
    u8 (*CVTE_GetTVChecksum)(u8* checksum);

    /* 
     * 设置板卡通道 
     * ========================================================================
     * 返回：0-ok, 1-fail
     * */
    u8 (*CVTE_SetTVSource)(en_CVTE_AT_SOURCE source);

    /* 
     * 获取TV板卡通道 
     * ========================================================================
     * 通过引用参数source返回通道ID
     * 返回:0-ok, 1-fail
     * */
    u8 (*CVTE_GetTVSource)(en_CVTE_AT_SOURCE *source);

    /*
     * 设置板卡音量 
     * ========================================================================
     * 参数：volume - [0-100] 音量值
     * 返回：0-ok, 1-fail
     * */
    u8 (*CVTE_SetVolume)(u8 volume);

    /* 设置板卡频道，未使用 */
    u8 (*CVTE_SetTVChannel)(void);

    /*
     * 切台指令，TV需要根据所在通道进行操作，如在DTV，则切换DTV的节目 
     * ========================================================================
     * 参数 num: 设置的台号
     * 返回：0-ok, 1-fail
     *
     * */
    u8 (*CVTE_ChangeTVNum)(u16 num);

    /*
     * TV板块串口输出接口 
     * ========================================================================
     * 参数 datas: 待输出的字符串
     *      len:   字符串长度
     *
     * 返回：0-ok, 1-fail
     * 描述：
     *      调用TV板卡的串口输出函数，输出本库的通信信息
     * */
    u8 (*CVTE_UsartSendData)(u8* datas, u16 len);

   /* 
	* 获取MAC地址 
	* ========================================================================
	* 参数：
	*	   macAddr:待返回的mac地址
	* 返回：
	*	   0-ok, 1-fail
	*
	* 描述：
	*	   MAC地址
	* */
   u8 (*CVTE_GetTVMacAddr)(UINT8* ui1_macAddr);
   /*
	* 获取TV HDCP KEY的唯一码 
	* ========================================================================
	* 参数:
	*	   hdcpId : 返回的ID数值
	* 返回：0-ok, 1-fail
	* */
   u8 (*CVTE_GetTVHDCP_ID)(u32* hdcpId);

   /* 
	* 获取TV CI+ KEY 唯一码 
	* ========================================================================
	* 参数: 
	*	   ciplusId : 返回的ID值
	* 返回：0-ok, 1-fail
	* */
   u8 (*CVTE_GetTVCIPlus_ID)(u32* ciplusId);

   /* 
	* 保存HDCP KEY 
	* ========================================================================
	* 参数：
	*	   key: KEY数据
	*	   len: 长度
	*	   fileID: 该key的ID值，将写入板卡
	* 返回：
	* 0： 烧录成功
	* 2： 烧录失败
	* 
	* 描述：
	*	   该指令把KEY写入FLASH中
	*/
   u8 (*CVTE_SaveHDCPKeyToTV)(u8* key, u32 len, u32 fileId);

   /* 
	* 保存CI+ KEY 
	* ========================================================================
	* 参数：
	*	   key: KEY数据
	*	   len: 长度
	*	   fileID: 该key的ID值，将写入板卡
	* 返回：
	* 0： 烧录成功
	* 2： 烧录失败
	* 
	* 描述：
	*	   该指令把KEY写入FLASH中
	*/

   u8 (*CVTE_SaveCIPlusKeyToTV)(u8* key, u32 len, u32 fileId);
   /* 
	*
	* 保存MAC地址
	* ========================================================================
	* 返回：
	* 0： 烧录成功
	* 2： 烧录失败
	*
	* */
   u8 (*CVTE_SaveMACAddrToTV)(UINT8* ui1_macAddr);

   /*
	* 设置TV板卡的IO 电平
	* ========================================================================
	* 参数：
	*	   pin: 定义的待控制io 口
	*	   level: io控制的方向
	*
	* 返回：0-ok, 1-fail
	* */
   u8 (*CVTE_CtrlIOLevel)(en_CVTE_AT_IOPin pin, en_CVTE_AT_IO_LEVEL level);

   /**
	* 获取当前按键板状态
	* ========================================================================
	* 参数：
	*	   keyStatus:
	*	   按键板的状态： D7 D6 D5 D4 D3 D2 D1 D0
	*					|  |  |  |	|  |  |  |
	*				   K7 K6 K5 K4 K3 K2 K1 K0
	*	   0:代表未按下，1：代表按下
	* 返回：
	*	   0 - ok
	*	   1 - fail
	*/
   u8 (*CVTE_GetCurrentKeyPadStatus)(u8* keyStatus);
	
	/**
	* 写barcode到板卡flash里面
	* ========================================================================
	* 参数：
	*	   barcode- 条形码数组
	*	   len	  - 条形码长度
	* 返回：
	*	  0 - success
	*	  1 - fail
	*/
   u8 (*CVTE_SaveBarcodeToFlash)(u8* barcode, u8 len);

   /**
	* 返回板卡条形码
	* ========================================================================
	* 参数：
	*	  retBarcode - 待返回的barcode数组
	*	  len - barcode的长度，如果读取不到或不成功，则返回 0
	* 返回：
	*	  0 - ok
	*	  1 - fail
	*/
   u8 (*CVTE_GetBarcodeFromFlash)(u8* retBarcode, u8* len);

   /**
	* 写客户自定义的barcode到板卡flash里面
	* ========================================================================
	* 参数：
	*	   type    - 烧录的用户类型
	*	   barcode - 条形码数组
	*	   len	   - 条形码长度
	* 返回：
	*	  0 - success
	*	  1 - fail
	*/
   u8 (*CVTE_SaveCustomerBarcodeToFlash)(u8 type, u8* barcode, u8 len);

   /**
	* 返回用户自定义板卡条形码
	* ========================================================================
	* 参数：
	*	  type		 - 烧录的用户类型
	*	  retBarcode - 待返回的barcode数组, 末尾必须添加 '\0'
	*	  len		 - barcode的长度，如果读取不到或不成功，则返回 0
	* 返回：
	*	  0 - ok
	*	  1 - fail
	*/
   u8 (*CVTE_GetCustomerBarcodeFromFlash)(u8 type, u8* retBarcode, u8* len);


   /**
	* 返回KSV数组
	* ========================================================================
	* 参数：
	*	   ksvCode:返回的数组指针， 长度固定为5个byte
	*	   k[4] : D39-D32 : retcmd[5]
	*	   k[3] : D31-D24 : retcmd[6]
	*	   K[2] : D23-D16 : retcmd[7]
	*	   K[1] : D15-D8  : retcmd[8]
	*	   K[0] : D7-D0   : retcmd[9]
	* 返回：
	*	  0 - OK
	*	  1 - FAIL
	*/
   u8 (*CVTE_GetHDCP_KSV_Code)(u8* ksvCode);

   /**
	* 设置ATSC模式
	* 返回ATSC设置后的模式
	* ========================================================================
	* 参数：
	*	   type: 0 - AIR
	*			 1 - CABLE
	* 返回：
	*	   0 - air
	*	   1 - cable
	*/
   u8 (*CVTE_SetATSC_AIR_CABLE_mode)(u8 type);

   /**
	* 设置ATSC频点
	* ========================================================================
	* 参数：
	*	   majorPro: 主频道号
	*	   minorPro: 次频道号
	* 返回：
	*	   0 - ok
	*	   1 - faile
	*/
   u8 (*CVTE_SetATSC_ProNumber)(u8 major, u8 minor);

   
   /**
   * 获取CI 卡 功能状态
   * ========================================================================
   * 参数：
   *	  u8* status: 待返回的结果
   *				  0 - OK
   *				  1 - 未插入
   *				  2 - CI功能异常
   * 返回：
   *	  0 - ok
   *	  1 - faile
   */
  u8 (*CVTE_GetCIFunctionStatus)(u8* status);

  /**
   * 获取IP地址， 可以是IPV6, 也可以是IPV4
   * ========================================================================
   * 参数：
   *	  u8* ipStr: IP buffer指针
   * 返回：
   *	  IP串的长度
   */
  u8 (*CVTE_GetIPAddr)(UINT8* ui1_ip);

  /**
   * 获取WIFI测试结果
   * ========================================================================
   * 参数：
   *	  u8* status: 测试结果
   *								  0 - OK
   *								  1 - Testing
   *		  2 - Failed
   * 返回：
   *	  0 - OK
   *	  1 - Faile
   */
  u8 (*CVTE_GetWifiTestResult)(u8* status);

  /**
   * 获取Bluetooth测试结果
   * ========================================================================
   * 参数：
   *	  u8* status: 测试结果
   *								  0 - OK
   *								  1 - Testing
   *		  2 - Failed
   * 返回：
   *	  0 - OK
   *	  1 - Faile
   */
  u8 (*CVTE_GetBluetoothTestResult)(u8* status);

  /**
   * 获取USB连接状态
   * ========================================================================
   * 参数：
   *	  u8* usb_count - USB连接个数
   * 返回：
   *	  0 - OK
   *				  1 - Faile
   */
  u8 (*CVTE_GetUSBConnectCount)(u8* usb_count);

  /**
   * 检测Bluetooth测试状态
   *=========================================================================
   * 参数：
   *			  u8* status			  - test result
   *													  0 - OK
   *													  1 - Testing
   *													  2 - Failed
   * 返回：
   *			  0 - EXIT_SUCCESS
   *			  1 - EXIT_FAILED
   */
  u8 (*CVTE_CheckBluetoothStatus)(u8* status);


  /**
   * 工厂遥控器串口操作入口，接受CVTE工厂遥控器按键码值，如要支持其他协议，需要
   * 提前告知测试程序
   *=========================================================================
   * 参数：
   *			  key_code - 遥控按键码值
   * 返回： 0 - EXIT_SUCCESS
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
	* 保存文件到flash 
	* ========================================================================
	* 参数：
	*	   buf: 文件数据
	*	   len: 长度
	*	   fileID: 该文件的唯一ID值，将写入板卡
	*	   filetype:文件类型
	* 返回：
	* 0： 烧录成功
	* 2： 烧录失败
	* 
	* 描述：
	*	   该指令把文件写入FLASH中
	*/
   u8 (*CVTE_FAC_write_file)(u8* buf, u32 len, u8 filetype);
   
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

    u8 (*CVTE_GetMmcBlkCount)(u8 *result,char emmcString[]);

}st_CVTE_AT_RegFunction;


#endif

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#ifdef APP_BLUETOOTH_SUPPORT
 #ifndef _BLUETOOTH_GATTC_PROC_H
 #define _BLUETOOTH_GATTC_PROC_H

/********************************************include files*********************************************/
 #include "openssl/aes.h"
 #include "u_bt_mw_gattc.h"

/************************************macros, defines, typedefs, enums***********************************/
// define max length
#define		MAX_CHARACTERISTIC_LIMIT		20
#define		MAX_CHARACTERISTIC_NUMBER		80
#define 	MAX_FRAGMENT_LIMIT				(MAX_CHARACTERISTIC_LIMIT * MAX_CHARACTERISTIC_NUMBER)// each fragment has 80 characteristics and each characteristic has 20 bytes, refer to vizio spec
#define		MAX_CHAR_UUID					82// refer to vizio apk source code, TOTAL_CUSTOM_CHARCT = 101
#define		MAX_SCAN_DEVICE					5// if less than 5 servers are connected with the client, the client should continue to scan for new servers, refer to vizio spec
#define		MAX_EIR_MSD_LEN					(30 * 2)
#define		GATTC_EIR_MSD_FIX_LEN			(6 * 2)
#define 	GATTC_SERVICE_UUID				"69A3DBA5-CBC1-4B5D-91F6-F8109BED2EA8"
#define		GATTC_CHAR_UUID					"9D592CXX"
#define		GATTC_CHAR_C0_UUID				"9D592C00-2710-63B3-92AC-E1072B9843D2"
#define		GATTC_CHAR_C80_UUID				"9D592C50-2710-63B3-92AC-E1072B9843D2"
#define		GATTC_CHAR_C255_UUID			"9D592CFF-2710-63B3-92AC-E1072B9843D2"
#define		GATTC_PRE_REQUEST_IP			"http://127.0.0.1:7346/"
#define		GATTC_MANU_SPEC_DATA			"11C10058"
#define     GATTC_IOS_SERVICE_UUID          "69A3DBA"
#define 	GATTC_DIRECT_PAIRING			"DBB"
#define     GATTC_IOS_WRITE_DESCR           "00002902-0000-1000-8000-00805F9B34FB"
#define		GATTC_ANDROID_IOS_OFFSET		(-7)

#define     GATTC_SCAN_INTERVAL             (1600)   /* Interval have to larger than window */
#define     GATTC_SCAN_WINDOW               (800)

//uint8_t 	Kp[AES_BLOCK_SIZE] 	= 			{0x1c,0x10,0x26,0x6a,0xdd,0xc3,0x48,0xef,0x8e,0x54,0x9c,0xac,0x89,0x53,0x0c,0x5f};
uint8_t 	Kp[AES_BLOCK_SIZE] 	= 			{0x36,0x2a,0x38,0xf9,0x95,0xc9,0x9d,0x80,0x43,0x03,0xfe,0xe6,0xa5,0xb4,0x66,0xaf};
uint8_t     Kt[AES_BLOCK_SIZE]  = 			{0x1c,0x10,0x26,0x6a,0xdd,0xc3,0x48,0xef,0x8e,0x54,0x9c,0xac,0x89,0x53,0x0c,0x5f};
uint8_t 	calc_t3[AES_BLOCK_SIZE] = 		{0xe9,0xd3,0x19,0x38,0xb1,0x34,0x4e,0x69,0x9a,0xc2,0x43,0xf3,0x66,0x7c,0x15,0x9e};
uint8_t 	calc_kn[AES_BLOCK_SIZE] = 		{0x5b,0xe2,0xee,0x6b,0xeb,0xcc,0x40,0x72,0xa5,0x2d,0x24,0x8f,0x5c,0xc7,0x49,0x78};

typedef struct _CTR_STATE
{
	unsigned int	num;
    uint8_t 		ivec[16];
    uint8_t 		ecount[16];
}CTR_STATE;

typedef struct _EIR_MSD_VARIABLE_TAG
{
	UINT8		signal_meter;
	UINT8		mac_address;
	UINT8		security_key;
	UINT8		ui_key_offset;
	UINT8		scan_parameter;
	UINT8		ui_scan_offset;
	UINT8		connect_parameter;
	UINT8		ui_connect_offset;
	UINT8		pair_parameter;
	UINT8		ui_pair_offset;
	UINT8		no_wakeup;
	UINT8		ui_wakeup_offset;
	UINT8		more_bits_eight;
	UINT8		max_rssi;
	UINT8		ui_maxrssi_offset;
	UINT8		signal_meter_timeout;
	UINT8		ui_timeout_offset;
	UINT8       flag_delta;
	UINT8       hardware_type;
	UINT8       more_bits_nine;
	UINT8       delta_value;
}EIR_MSD_VARIABLE_TAG;

typedef enum
{
	GATTC_NON_SECURITY = 0,
	GATTC_ADD_SECURITY
}GATTC_SECURITY;

typedef enum
{
    GATTC_WRITE_COMMAND = 1,
    GATTC_WRITE_RESPONSE
}GATTC_WRITE_TYPE;

typedef enum
{
    GATTC_NO_CONNECT = 0,
    GATTC_CONNECTED,
    GATTC_DISCONNECT
}GATTC_CONNECT_STATUS;

typedef struct _C0_HEADER
{
	uint8_t		i_sequence_number;
	uint8_t		i_fragment_number;
	uint8_t		i_last_fragment_number;
	uint8_t		i_security_data;
	uint16_t	i2_total_length;

	uint16_t	i2_payload_length;
	uint8_t		i_message_type;
	uint8_t		i_check_sum;
}C0_HEADER;

typedef struct _LAST_SCAN_DEVICE
{
    BOOL        b_used;
	CHAR 		last_mac_addr[MAC_ADDRESS_LENGTH_LEN + 1];
	uint8_t		ui_pairing_state;   /* count of ADV received within consective */
	UINT64*		ui8_interval;       /* Timestamp for every ADV within consective */
	UINT64		ui8_time_sum;
    INT32       i4_max_interval;
    INT32       i4_elem_num;        /* ui8_interval buffer num */
}LAST_SCAN_DEVICE;

typedef struct _GATT_SERVER_DATA
{
	BT_GATTC_SCAN_RST_T			        ble_scan_result;
	BT_GATTC_CONNECT_RST_T 		        ble_connect_result;
	BT_GATTC_READ_CHAR_RST_T		    ble_read_result;
	BT_GATTC_WRITE_CHAR_RST_T		    ble_write_result;

    BT_GATTC_SEARCH_RST_T               ble_service_result;
    BT_GATTC_GET_CHAR_RST_T             ble_char_result_array[MAX_CHAR_UUID];
    BT_GATTC_GET_CHAR_RST_T             *pt_registered_char;


    BT_GATTC_GET_GATT_DB_T              t_gatt_db;           /*use to save service for end-user*/

	CHAR 								ios_uuid_scan[37];
    CHAR                                device_mac_addr[MAC_ADDRESS_LENGTH_LEN + 1];

	uint8_t								i_fragment_number;
	uint8_t								i_cache_device;
	uint8_t                             i_connect_sign;
	uint8_t								i_get_char_number;
	uint8_t								i_get_char_out;
	uint8_t								i_read_char_number;// 0,...,MAX_CHAR_UUID
	uint8_t								i_write_char_number;// 0,...,MAX_CHAR_UUID

    UINT32                              aui4_char_result_handle[MAX_CHAR_UUID];
    UINT32                              ui4_reg_char_handle;
	INT32								ui4_response_code;
	UINT32								ui4_request_msg_len;
	UINT32                              ui4_gatt_db_loop_idx;
    UINT32                              ui4_get_desc_num;
	UINT32								ui4_response_msg_len;
	UINT32								ui4_write_msg_len;

	C0_HEADER							c0_header;

	char*								response_msg;
	char*								request_msg;
}GATT_SERVER_DATA;

/****************************************function declarations******************************************/
extern INT32 bluetooth_gattc_poweron_scan_proc(VOID);
extern INT32 bluetooth_gattc_scan_proc(VOID);
extern INT32 bluetooth_gattc_stop_scan_proc(VOID);
#endif
#endif


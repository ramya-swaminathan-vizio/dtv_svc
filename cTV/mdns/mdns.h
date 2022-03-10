
#ifndef __MDNS_H__
#define __MDNS_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

#include "u_irrc_btn_def.h"

#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_aee.h"
#include "c_appman.h"
#include "c_wgl.h"
#include "c_iom.h"
#include "c_svctx.h"
#include "c_pcl.h"
#include "x_os.h"
#include "c_net_config.h"
//#include "sys_custom.h"
#include "amb/a_amb.h"
#include "am/a_am.h"
#include "bgm/a_bgm.h"
#include "res/bgm/bgm_variant.h"
#include "app_util/a_cfg.h"
#include "app_util/a_common.h"
#include "app_util/a_network.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "app_util/rmv_dev/a_rmv_evt.h"
#include "nav/input_src/a_input_src.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "nav/updater/a_nav_updater.h"
#include "nav/updater/nav_updater.h"

#include "res/app_util/config/a_cfg_custom.h"

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#ifndef SOL_IP
#define SOL_IP IPPROTO_IP
#endif


#define MDNS_ADDR "224.0.0.251"
#define MDNS_PORT 5353
#define MDNS_PACKET_MAX_SIZE 65536
#define MDNS_PACKET_HEADER_SIZE (sizeof(UINT16)*6)
#define MDNS_KEY_VALUE_MAX_LEN (256)
#define MDNS_VALUE_MAX_LEN (128)

#define VIZIO_HTTP_PORT "7346"
#define VIZIO_HTTPS_PORT "7345"
#define VIZIO_WS_PORT "8005"
#define VIZIO_WSP_PORT "8006"


#define MDNS_NAME_LEN_INDICATER UINT8


#define MDNS_FLAG_RESP 	(1 << 15)	// Query=0 / Response=1
#define MDNS_FLAG_AA	(1 << 10)	// Authoritative
#define MDNS_FLAG_TC	(1 <<  9)	// TrunCation
#define MDNS_FLAG_RD	(1 <<  8)	// Recursion Desired
#define MDNS_FLAG_RA	(1 <<  7)	// Recursion Available
#define MDNS_FLAG_Z		(1 <<  6)	// Reserved (zero)

#define MDNS_FLAG_GET_RCODE(flag)	(flag & 0x0F)
#define MDNS_FLAG_GET_OPCODE(flag)	((flag >> 11) & 0x0F)

#define GOOGLE_SERVICE "_googlecast._tcp.local"
#define DNS_SD_SERVICE_QUERY "_services._dns-sd._udp.local."
#define DNS_SD_SERVICE "\011_services\07_dns-sd\04_udp\05local"
#define VIZIO_SERVICE_NAME "_viziocast._tcp.local."
#define VIZIO_SERVICE "\012_viziocast\04_tcp\05local"
#define VIZIO_SERVICE_TARGET "\05local"
#define VIZIO_SERVICE_TTL ((UINT32)(365*24*60*60))
#define VIZIO_SERVICE_PRIORITY ((UINT16)0)
#define VIZIO_SERVICE_WEIGHT ((UINT16)0)
#define VIZIO_SERVICE_PORT ((UINT16)7345)

#define MDNS_FAIL_INIT -10
#define MDNS_FAIL_SOCK -9
#define MDNS_FAIL_THREAD -8
#define MDNS_FAIL_PARA -7


#define VIZIO_KEY_ID "id="
#define VIZIO_KEY_DID "did="
#define VIZIO_KEY_CID "cid="
#define VIZIO_KEY_CCD "ccd="
#define VIZIO_KEY_ETH "eth="
#define VIZIO_KEY_WIFI "wifi="
#define VIZIO_KEY_BT "bt="
#define VIZIO_KEY_FVER "fver="
#define VIZIO_KEY_RVER "rver="
#define VIZIO_KEY_MVER "mver="
#define VIZIO_KEY_BVER "bver="
#define VIZIO_KEY_DT "dt="
#define VIZIO_KEY_PWR "pwr="
#define VIZIO_KEY_OOBE "oobe="
#define VIZIO_KEY_ULI "uli="
#define VIZIO_KEY_TOS "tos="
#define VIZIO_KEY_NAME "name="
#define VIZIO_KEY_MDL "mdl="
#define VIZIO_KEY_SOC "soc="
#define VIZIO_KEY_DL "dl="
#define VIZIO_KEY_DC "dc="
#define VIZIO_KEY_VER "ver="
#define VIZIO_KEY_ES "es="
#define VIZIO_KEY_HP "hp="
#define VIZIO_KEY_HSP "hsp="
#define VIZIO_KEY_WP "wp="
#define VIZIO_KEY_WSP "wsp="

#define MDNSD_PID_FILE "/var/run/mdnsd.pid"

typedef void *(*start_routine) (void *);

typedef INT32 (*get_key_val) (CHAR *,UINT8*);

typedef struct mdns_key_val
{
    CHAR *key_name;
    get_key_val get_val;
}mdns_key_val_t;


typedef	enum qtype
{
	QTYPE_A		= 1,
	QTYPE_PTR		= 12,
	QTYPE_TXT		= 16,
	QTYPE_SRV		= 33,
	QTYPE_ANY		= 255,
}e_qtype_t;

typedef	enum rr_type
{
	RR_A		= 0x01,
	RR_PTR		= 0x0C,
	RR_TXT		= 0x10,
	RR_AAAA		= 0x1C,
	RR_SRV		= 0x21,
	RR_NSEC		= 0x2F,
	RR_ANY		= 0xFF,
}e_rr_type_t;


typedef struct mdns_qn_entry
{
    UINT16 u2LabelLen;
    UINT16 u2QType;
	UINT16 u2QClass;
	UINT16 u2NameSize;
	UINT8 *pQName;
	struct mdns_qn_entry *next;
}mdns_qn_entry_t;


typedef struct mdns_rr_entry
{
    UINT16 u2NameLen;
    UINT8 *pName;

    UINT16 u2Type;
    UINT16 u2Class;
    UINT32 u4TTL;

    UINT16 u2RdLength;
    UINT8 *pRdata;

    UINT16 u2Size;
    UINT8 *buffer;
    struct mdns_rr_entry *next;

}mdns_rr_entry_t;


typedef struct mdns_packet
{
    UINT16 u2Id;
    UINT16 u2Flags;
    UINT16 u2NumQr;
    UINT16 u2NumAns;
    UINT16 u2NumAuth;
    UINT16 u2NumAdd;

    UINT16 u2PktSize;
    UINT8* buffer;

    mdns_qn_entry_t *pQn;
    mdns_rr_entry_t *pAns;
    mdns_rr_entry_t *pAuth;
    mdns_rr_entry_t *pAdd;

}mdns_packet_t;


typedef struct vizio_mdns_server
{
    BOOL bInit;
	BOOL bStop;
	BOOL bNameConflict;
	BOOL bProbing;
	BOOL bSD;
	INT32 i4NameConflictCount;
	INT32 i4SockFd;
	pthread_mutex_t dataLock;
	pthread_t tid;
    mdns_packet_t pkt;

}vizio_mdns_server_t;


UINT8 *mdns_write_u16(UINT8 *ptr, const UINT16 v);
UINT8 *mdns_write_u32(UINT8 *ptr, const UINT32 v);
UINT16 mdns_read_u16(const UINT8 *ptr);
UINT32 mdns_read_u32(const UINT8 *ptr);
INT32 mdns_parse_qname(UINT8 **name,UINT8* start);
INT32 mdns_parse_question(mdns_packet_t *pkt) ;
INT32 mdns_parse_pkt(mdns_packet_t *pkt) ;
INT32 mdns_free_question(mdns_packet_t *pkt) ;
INT32 mdns_uncompress_nlabel(mdns_packet_t *pkt, UINT16 off,mdns_qn_entry_t *q) ;

UINT16 mdns_label_len(mdns_packet_t *pkt, UINT16 off);


extern CHAR* sys_cust_get_usb_upg_version(VOID);
extern BOOL a_wzd_is_oobe_mode(VOID);
extern INT32 a_c4tv_apron_get_cast_name(CHAR *ps_cast_name,UINT32 *pui4_cast_name_len);
INT32 mdns_vizio_get_key_id(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_did(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_cid(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_ccd(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_eth(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_wifi(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_bt(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_fver(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_rver(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_mver(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_bver(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_dt(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_pwr(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_oobe(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_uli(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_tos(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_name(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_mdl(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_soc(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_dl(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_dc(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_ver(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_es(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_hp(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_hsp(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_wp(CHAR *val,UINT8 *plen);
INT32 mdns_vizio_get_key_wsp(CHAR *val,UINT8 *plen);

INT32 a_mdns_register(vizio_mdns_server_t *svr);
void mdns_vizio_register(vizio_mdns_server_t *svr);
INT32 mdns_vizio_announce(vizio_mdns_server_t *svr);
INT32 mdns_vizio_make_rr_record(mdns_rr_entry_t *prr,e_rr_type_t type);
INT32 mdns_vizio_make_rr_rdata(mdns_rr_entry_t *rr,e_rr_type_t type);
INT32 mdns_vizio_make_packet(mdns_packet_t *pkt);
INT32 mdns_vizio_free_packet(mdns_packet_t *pkt);
INT32 mdns_vizio_probe(vizio_mdns_server_t *svr);
INT32 mdns_vizio_probe_change_name(void);
INT32 mdns_vizio_probe_change_name(void);
BOOL mdns_vizio_probe_is_name_conflict(void);
VOID mdns_vizio_probe_clear_name_conflict(void);
INT32 mdns_vizio_probe_make_pkt(mdns_packet_t* pkt);
INT32 mdns_vizio_probe_free_pkt(mdns_packet_t* pkt);
INT32 mdns_vizio_probe_make_question(mdns_packet_t* pkt,const CHAR* name);
INT32 mdns_vizio_probe_free_question(mdns_packet_t* pkt);
INT32 mdns_vizio_probe_send_query(mdns_packet_t* pkt);
VOID mdns_vizio_probe_set_probing(BOOL val);
BOOL mdns_vizio_probe_is_probing(void);
VOID mdns_vizio_probe_set_name_conflict(BOOL val);



#endif


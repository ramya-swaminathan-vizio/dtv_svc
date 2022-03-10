/*
 * athcfg_helper.h
 *
 *  Created on: 2011/9/26
 *      Author: James Liang
 */

#ifndef ATHCFG_HELPER_H_
#define ATHCFG_HELPER_H_

//#define   EIO     5   /* I/O error */
//#define   E2BIG   7   /* Argument list too long */
//#define   EINVAL  22  /* Invalid argument */
#define EIFNAME 100 /* Interface name erros */

#define RT_OID_802_11_QUERY_PID                 0x0839
#define RT_OID_802_11_QUERY_VID                 0x083A
#define OID_802_3_CURRENT_ADDRESS               0x060A
#define RT_OID_VERSION_INFO                     0x0608
#define RT_OID_802_11_QUERY_LINK_STATUS         0x060C
#define OID_802_11_RSSI                         0x060D
#define OID_802_11_STATISTICS                   0x060E
#define RT_OID_802_11_RSSI                      0x0108  /*rt2860 only , kathy */
#define RT_OID_802_11_RSSI_1                    0x0109  /*rt2860 only , kathy */
#define RT_OID_802_11_RSSI_2                    0x010A  /*rt2860 only , kathy */
#define RT_OID_802_11_QUERY_NUM_OF_TX_ANT       0x083B
#define RT_OID_802_11_QUERY_NUM_OF_RX_ANT       0x083C
#define RT_OID_802_11_QUERY_DIV_ANT_NUM         0x083D
#define RT_OID_802_11_ENABLE_ANT_DIV            0x083E
#define RT_PRIV_IOCTL                           (SIOCIWFIRSTPRIV + 0x01) /* Sync. with AP for wsc upnp daemon */
//#define IFNAME                                                  "ra0"

//1st byte : 01:ANT0 / 02:ANT1 / _athcfg_lna_div_set("wifi0",AH_TRUE):DUAL_ANT

typedef enum {
    AH_FALSE = 0,       /* NB: lots of code assumes false is zero */
    AH_TRUE  = 1,
} HAL_BOOL;

/**
 * @brief Helpers for Get Tx-Antenna Number.
 * @param ifname ath0/ra0
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          0     success
 */
int _athcfg_tx_antenna_num_get(char *ifrn_name, UINT16 *val);

/**
 * @brief Helpers for Get Rx-Antenna Number.
 * @param ifname ath0/ra0
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          0     success
 */
int _athcfg_rx_antenna_num_get(char *ifrn_name, UINT16 *val);

/**
 * @brief Helpers for Get LNA.
 * @param ifname ath0/ra0
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          0     success
 */
int _athcfg_lna_get(char *ifrn_name, UINT16 *val);

/**
 * @brief Helpers for Set LNA.
 * @param ifname ath0/ra0
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          0     success
 */
int _athcfg_lna_set(char *ifrn_name, UINT8 val);

/**
 * @brief Helpers for Enable/Disable Rx-LNA Diversity.
 * @param ifname ath0/ra0
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          0     success
 */
int _athcfg_lna_div_set(char *ifrn_name, HAL_BOOL is_enabled);

/**
 * @brief Helpers for Get Statsinfo Level.
 * @param ifrn_name ath0/ra0
 * @param val RSSI returned
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          EINVAL Invalid argument
 *          0     success
 */
int _athcfg_getStatsinfoLevel(char *ifrn_name, UINT8 *val);

/**
 * @brief Helpers for Get Statsinfo RSSI.
 * @param ifrn_name ath0/ra0
 * @param val RSSI returned
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          EINVAL Invalid argument
 *          0     success
 */
int _athcfg_getStatsinfoRSSI(char *ifrn_name, UINT8 *val);

/**
 * @brief Helpers for Get Hst-Stats RSSI.
 * @param ifrn_name ath0/ra0
 * @param val RSSI returned
 * @returns E2BIG ifname too big
 * @returns EIFNAME ifname error
 *          EIO   ioctl error
 *          0     success
 */
int _athcfg_getHstStatsRSSI(char *ifrn_name, UINT8 *val);

/**
 * @brief Helpers for Get PID of wifi module
 * @param PID
 * @returns EIO ioctl error
 *          0   success
 *
 */
int get_PID(char *PID);

/**
 * @brief Helpers for Get VID of wifi module
 * @param VID
 * @returns EIO ioctl error
 *          0   success
 *
 */
int get_VID(char *VID);

/**
 * @brief Helpers for Get Driver version of wifi module
 * @param Driver version
 * @returns EIO ioctl error
 *          0   success
 *
 */

int get_Driver_Version(char *Driver_version);

/**
 * @brief Helpers for Get MAC address of wifi module
 * @param Driver version
 * @returns EIO ioctl error
 *          0   success
 *
 */

int get_MAC_address(char *MAC_address);



#endif /* ATHCFG_HELPER_H_ */

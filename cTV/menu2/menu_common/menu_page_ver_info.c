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
 * AGREES TO THE FOLLOWING:                                                    *
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
 * $RCSfile: menu_page_ver_info.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_sm_video_hdlr.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_tsl.h"
#include "c_svctx.h"

#include "mi_common.h"
#include "mi_audio.h"


#include "app_util/a_key_seq.h"


#include "menu2/menu.h"
#include "menu2/menu_device/menu_page_device_status_info.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_network_phase1/menu_network.h"

#include "res/app_util/network/network_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "app_util/a_network.h"
#include "c_speedtest_async.h"
#include "res/nav/nav_mlm.h"

#include "wfrrc_interface.h"
#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "c_tts.h"
#endif

#include "mmp/a_mmp.h"

#include "rest/a_rest_api.h"
#include "menu2/menu_dbg.h"
#include "app_util/uli/uli_custom.h"

#ifdef MTK_CAMERA_DPTZ_SUPPORT
#include "MtkV4L2.h"
#endif

#ifdef COMMON_VER_INFO_ENABLE
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define SO_NAME_UTV_PROVISION                   "/basic/lib/libupdatetv_provision.so"
#define COMMON_VER_INFO_ELEM_SIZE              (36) //(44)
#define COMMON_VER_INOF_ELEM_NUM               (21)

#define COMMON_VER_ARROW_WIDTH                 (20*4/3)
#define COMMON_VER_ARROW_HEIGHT                (9*4/3)

#define COMMON_VER_INFO_LB_X                   (0)
#define COMMON_VER_INFO_LB_Y                   (COMMON_VER_ARROW_HEIGHT)
#define COMMON_VER_INFO_LB_W                   MENU_ITEM_V_WIDE //(CONTENT_W - 15*4/3)
#define COMMON_VER_INFO_LB_H                   (COMMON_VER_INFO_ELEM_SIZE * COMMON_VER_INOF_ELEM_NUM)

#define COMMON_VER_INFO_INSET_L         (8*4/3)
#define COMMON_VER_INFO_INSET_R         (8*4/3)

#define COMMON_VER_INFO_LB_COL_W        (COMMON_VER_INFO_LB_W)
#define COMMON_VER_INFO_LB_ALIGN        (WGL_AS_LEFT_CENTER)

#define COMMON_VER_INFO_FONT_SIZE            FE_FNT_SIZE_SMALL

#define MENU_UPDATER_ULI_STATUS_MASK_REGISTERED                         0x0001
#define MENU_UPDATER_ULI_STATUS_MASK_FACTORY_TEST_MODE                  0x0002
#define MENU_UPDATER_ULI_STATUS_MASK_FIELD_TEST_MODE                    0x0004
#define MENU_UPDATER_ULI_STATUS_MASK_LOOP_TEST_MODE                     0x0008

#define VER_INFO_TIMER (1000)
#define VER_INFO_REFRESH_TIMER (10000)

#define BT_DEVICES_MAX_ELEM_NUM  (8)
#define MENU_REMOTE_VER_LEN             (16)
#define MENU_REMOTE_INFO_BATTERY_LEN    (16)
#define MENU_REMOTE_INFO_MAC_LEN        (32)
#define MENU_REMOTE_NAME_LEN             (32)
#define NETWORK_SPEED_LEN                 (16)

#define MENU_PAGE_VER_INFO_KEY_SEQ_LEN  (3)

#define WEAKEST_SIGNAL_STRENGTH     -85
#define STRONGEST_SIGNAL_STRENGTH   -50
#define MAX_SIGNAL_STRENGTH(a,b)	((a > b) ? a : b)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifdef APP_EMANUAL_SP6_SUPPORT
typedef enum
{
    VER_INFO_KEY_SEQ_PLAY,
    VER_INFO_KEY_SEQ_STOP,
    VER_INFO_KEY_SEQ_NUM
}E_KEY_SEQ_TYPE;
#endif

/* CUST TUNER MODEL TYPE */
#define CUST_TUNER_LG_TDVWH810F   0x71
#define CUST_TUNER_SS_DTVS203     0x72
#define CUST_TUNER_SONY           0x73
#define CUST_TUNER_NXP_TDA18273   0x74
#define CUST_TUNER_SS_DTVS20C     0x75
#define CUST_TUNER_SONY_RE215     0x76
#define CUST_TUNER_SILICON_TUNERA 0x77
#define CUST_TUNER_SHARP_VA1G2CD  0x78
#define CUST_TUNER_TCL_F20WT      0x79
#define CUST_TUNER_SILABS_SI2158  0x80
#define CUST_TUNER_Mxl_MXL601     0x81
#define CUST_TUNER_NXP_TDA18274   0x82
#define CUST_TUNER_SONY_RB221      0x83
#define CUST_TUNER_SONY_RA217      0x84
#define CUST_TUNER_LG_TDSTH570F   0x85
#define CUST_TUNER_SILABS_SI2157  0x86
#define CUST_TUNER_SONY_RA227      0x87
#define CUST_TUNER_NXP_TDA18275   0x88
#define CUST_TUNER_ML_MXL661      0x89
#define CUST_TUNER_SILABS_SI2151  0x8F
#define CUST_TUNER_SONY_RA231      0x90
#define CUST_TUNER_NXP_TDA182I5a  0x91

#define CUST_TUNER_TYPE_MAX_LEN       (16)
#define CUST_TUNER_TYPE_NAME_MAX_LEN  (128)

#ifdef MT5695L_MODEL
#define SSTAR_VENDOR_ID "1D6B"
#define SSTAR_PRODUCT_ID "0102"
#endif

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_ver_info;

static HANDLE_T     h_cnt_frm;
static HANDLE_T     h_lb_ver_info;
static HANDLE_T     h_arrow_up;
static HANDLE_T     h_arrow_down;
static HANDLE_T     h_signal_timer;
static HANDLE_T     h_refresh_timer;
static BOOL         b_async_flag = FALSE;

static char     s_airplay_version[12] = {0};
static UTF16_T  w2s_g_sq[128];
static CHAR     s_tuner_type[CUST_TUNER_TYPE_NAME_MAX_LEN+1] = {0};

typedef enum _VER_INFO_ROWNUM
{
    VER_INFO_ROW_SYSTEM_INFO = 0,
    VER_INFO_ROW_CAST_NAME,
    VER_INFO_ROW_SN,
    VER_INFO_ROW_MODEL,
    VER_INFO_ROW_SW_VER,
    VER_INFO_ROW_CAST_VER,
    VER_INFO_ROW_CHROMIUM_VER,
    VER_INFO_ROW_REST_VER,  // sc config
    VER_INFO_ROW_SOURCE,
    VER_INFO_ROW_RESOLUTION,
    VER_INFO_ROW_VFREQ,
    VER_INFO_ROW_FREE_SYNC_RATE,
    VER_INFO_ROW_AUDIO_TYPE_IN,
    VER_INFO_ROW_AUDIO_TYPE_OUT,
    VER_INFO_ROW_HDR,
    VER_INFO_ROW_VRR,
    VER_INFO_ROW_FIRMMAKER_MODE,
    VER_INFO_BLUETOOTH_VERSION,

    VER_INFO_ROW_NETWORK,
    VER_INFO_ROW_SSID,
    VER_INFO_ROW_WIFI_STRENGTH,
    VER_INFO_ROW_IP_TYPE,
    VER_INFO_ROW_IP_ADDR,
    VER_INFO_ROW_DEF_GATEWAY,
    VER_INFO_ROW_SUB_MASK,
    VER_INFO_ROW_IPV6_ADDR,
    VER_INFO_ROW_IPV6_DEF_GATEWAY,
    VER_INFO_ROW_IPV6_PREFIX_LENGTH,
    VER_INFO_ROW_PREF_DNS,
    VER_INFO_ROW_ALT_DNS,
#ifndef MT5583_MODEL
    VER_INFO_ROW_RJ45_MAC,
#else
    VER_INFO_ROW_ID_MAC,
#endif
    VER_INFO_ROW_WLAN_MAC,
    VER_INFO_ROW_CONNECTION_TYPE,
    VER_INFO_ROW_SECURITY_TYPE,
    VER_INFO_ROW_WIFI_MODE,
    VER_INFO_REMOTE_INFO,
    VER_INFO_REMOTE_STATUS,
    VER_INFO_BATTERY_LIFE,
    VER_INFO_REMOTE_VERSION,
    VER_INFO_ROW_BLUETOOTH_FIRMWARE,
    VER_INFO_ROW_REMOTE_SERIAL,
    VER_INFO_ROW_BLUETOOTH_MAC,

    VER_INFO_ROW_APPLICATION,
    VER_INFO_ROW_VIZIO_NDK_VER,
    VER_INFO_ROW_SCPL,
    VER_INFO_ROW_AIRPLAY_VER,
    VER_INFO_ROW_AIRPLAY_INTERNAL,
    VER_INFO_ROW_APPLE_TV_VER,
    VER_INFO_ROW_HBOMAX_VER,
    VER_INFO_ROW_COBALT,
    VER_INFO_ROW_DAI,
    VER_INFO_ROW_DLM_GENERIC_HOOKS,

  #ifdef MT5695L_MODEL // MVR-162: retrieve the ISP and DSPG firmware version.
    VER_INFO_ROW_CAMERA_INFO,
    VER_INFO_ROW_CAMERA_ISP,
    VER_INFO_ROW_MIC_ARRAY_DSP,
  #endif

    VER_INFO_ROW_UTV,
    VER_INFO_ROW_UTV_ESN,
    VER_INFO_ROW_UTV_SV,
    VER_INFO_ROW_UTV_REG,
    VER_INFO_ROW_UTV_NP,
    VER_INFO_ROW_NETFLIX_ESN,
    VER_INFO_ROW_UTV_UID,
    VER_INFO_ROW_DEV_ID,
    VER_INFO_ROW_PROV_ID,
    VER_INFO_ROW_UTV_DA,
    VER_INFO_ROW_COUNTRY,
    VER_INFO_ACCUMULATED_OPERATING_HOURS,
    VER_INFO_ROW_CHANNEL_INFO,
    VER_INFO_ROW_PHY_CH,
    VER_INFO_ROW_FREQ,
    VER_INFO_ROW_MODULATION,
    VER_INFO_ROW_STATUS,
    VER_INFO_ROW_SQ,
    VER_INFO_ROW_TUNER,
    //VER_INFO_ROW_GOOGLE_HOME_VER,
    //VER_INFO_ROW_AMAZON_VER,
    //VER_INFO_ROW_PROGRESSIVE,
    //VER_INFO_ROW_FRC_VER,
    //VER_INFO_ROW_DIID,
    //VER_INFO_ROW_TV_AD_ID,
   // VER_INFO_ROW_NETFLIX_ESN2,
    //VER_INFO_ROW_VCT,
    //VER_INFO_ROW_SLD,
    //VER_INFO_ROW_DOWN_SPEED,
    //VER_INFO_ROW_RSSI,
    //VER_INFO_ROW_WIFI_CHANNEL,
    //VER_INFO_MAC_ADDRESS,
    //VER_INFO_ROW_UTV_GID,
    //VER_INFO_ROW_UTV_MV,
    //VER_INFO_ROW_UTV_FCT,
    //VER_INFO_ROW_UTV_FET,
    //VER_INFO_ROW_UTV_LT,
    //VER_INFO_ROW_UTV_SYN,
    //VER_INFO_ROW_UTV_LDT,
    //VER_INFO_ROW_UTV_LDM,
    //VER_INFO_ROW_UTV_EC,
    //VER_INFO_ROW_UTV_LE,
    //VER_INFO_ROW_UTV_LET,
    //VER_INFO_ROW_RD,
    //VER_INFO_ROW_ML,
    //VER_INFO_ROW_MC,
    //VER_INFO_ROW_SRV_RST,
    //VER_INFO_ROW_SRV_CHK,

    VER_INFO_ROW_LAST_NUM
}VER_INFO_ROWNUM;

static UINT16   a_g_ver_info_idx[VER_INFO_ROW_LAST_NUM+1] = {0};
static ACFG_MI_MM_INFO_T     st_mi_info = {0};
static BOOL                  b_oled = FALSE;
typedef struct _VER_ITEM
{
     VER_INFO_ROWNUM   e_row_idx;
     UINT16  ui2_mlm_idx;
}VER_ITEM;

static VER_ITEM    t_g_ver_items [VER_INFO_ROW_LAST_NUM+1] =
{
    { VER_INFO_ROW_SYSTEM_INFO,             MLM_MENU_KEY_SYS_INFO},
    { VER_INFO_ROW_CAST_NAME,               MLM_MENU_KEY_SYS_INFO_CAST_NAME},
    { VER_INFO_ROW_SN,                      MLM_MENU_KEY_SYS_INFO_SN},
    { VER_INFO_ROW_MODEL,                   MLM_MENU_KEY_SYS_INFO_MODEL},
    { VER_INFO_ROW_SW_VER,                  MLM_MENU_KEY_SYS_INFO_VER},
    { VER_INFO_ROW_CAST_VER,                MLM_MENU_KEY_SYS_INFO_CAST_VER},
    { VER_INFO_ROW_CHROMIUM_VER,            MLM_MENU_KEY_SYS_INFO_CHROMIUM_VISION},
    { VER_INFO_ROW_REST_VER,                MLM_MENU_KEY_SYS_INFO_REST_VISION},
    { VER_INFO_ROW_SOURCE,                  MLM_MENU_KEY_SYS_INFO_SOURCE},
    { VER_INFO_ROW_RESOLUTION,              MLM_MENU_KEY_SYS_INFO_RESOLITION},
    { VER_INFO_ROW_VFREQ,                   MLM_MENU_KEY_SYS_INFO_VFREQ},
    { VER_INFO_ROW_FREE_SYNC_RATE,          MLM_MENU_KEY_SYS_INFO_FREE_SYNC_RATE},
    { VER_INFO_ROW_AUDIO_TYPE_IN,           MLM_MENU_KEY_SYS_INFO_AUDIO_TYPE},
    { VER_INFO_ROW_AUDIO_TYPE_OUT,          MLM_MENU_KEY_SYS_INFO_AUDIO_TYPE_OUT},
    { VER_INFO_ROW_HDR,                     MLM_MENU_KEY_SYS_INFO_HDR},
    { VER_INFO_ROW_VRR,                     MLM_MENU_KEY_SYS_INFO_VRR},
    { VER_INFO_ROW_FIRMMAKER_MODE,          MLM_MENU_KEY_SYS_INFO_FILMMAKER_MODE},
    { VER_INFO_BLUETOOTH_VERSION,           MLM_MENU_KEY_VER_INFO_BLUETOOTH_VER},

    { VER_INFO_ROW_NETWORK,                 MLM_MENU_KEY_SYS_INFO_NETWORK},
    { VER_INFO_ROW_SSID,                    MLM_MENU_KEY_SYS_INFO_SSID},
    { VER_INFO_ROW_WIFI_STRENGTH,           MLM_MENU_KEY_SYS_INFO_WIFI_STRENGTH},
    { VER_INFO_ROW_IP_TYPE,                 MLM_MENU_KEY_SYS_INFO_IP_TYPE},
    { VER_INFO_ROW_IP_ADDR,                 MLM_MENU_KEY_SYS_INFO_IP_ADDR},
    { VER_INFO_ROW_DEF_GATEWAY,             MLM_MENU_KEY_SYS_INFO_DEF_GATEWAY},
    { VER_INFO_ROW_SUB_MASK,                MLM_MENU_KEY_SYS_INFO_SUB_MASK},
    { VER_INFO_ROW_IPV6_ADDR,               MLM_MENU_KEY_SYS_INFO_IPV6_ADDR},
    { VER_INFO_ROW_IPV6_DEF_GATEWAY,        MLM_MENU_KEY_SYS_INFO_IPV6_DEF_GATEWAY},
    { VER_INFO_ROW_IPV6_PREFIX_LENGTH,      MLM_MENU_KEY_SYS_INFO_IPV6_PREFIX_LENGTH},
    { VER_INFO_ROW_PREF_DNS,                MLM_MENU_KEY_SYS_INFO_PREF_DNS},
    { VER_INFO_ROW_ALT_DNS,                 MLM_MENU_KEY_SYS_INFO_ALT_DNS},
#ifndef MT5583_MODEL
    { VER_INFO_ROW_RJ45_MAC,                MLM_MENU_KEY_SYS_INFO_RJ45_MAC},
#else
    { VER_INFO_ROW_ID_MAC,                  MLM_MENU_KEY_SYS_INFO_ID_MAC},
#endif
    { VER_INFO_ROW_WLAN_MAC,                MLM_MENU_KEY_SYS_INFO_WLAN_MAC},
    { VER_INFO_ROW_CONNECTION_TYPE,         MLM_MENU_KEY_SYS_INFO_CONNECTION_TYPE},
    { VER_INFO_ROW_SECURITY_TYPE,           MLM_MENU_KEY_SYS_INFO_SECURITY_TYPE},
    { VER_INFO_ROW_WIFI_MODE,               MLM_MENU_KEY_SYS_INFO_WIFI_MODE},
    { VER_INFO_REMOTE_INFO,                 MLM_MENU_KEY_SYS_INFO_REMOTE},
    { VER_INFO_REMOTE_STATUS,               MLM_MENU_KEY_SYS_INFO_REMOTE_MODEL},
    { VER_INFO_BATTERY_LIFE,                MLM_MENU_KEY_SYS_INFO_BATTERY},
    { VER_INFO_REMOTE_VERSION,              MLM_MENU_KEY_SYS_INFO_VERSION},
    { VER_INFO_ROW_BLUETOOTH_FIRMWARE,      MLM_MENU_KEY_SYS_INFO_BLUETOOTH_FIRMWARE},
    { VER_INFO_ROW_REMOTE_SERIAL,           MLM_MENU_KEY_SYS_INFO_REMOTE_SERIAL_NUM},
    { VER_INFO_ROW_BLUETOOTH_MAC,           MLM_MENU_KEY_SYS_INFO_BLUETOOTH_MAC},

    { VER_INFO_ROW_APPLICATION,             MLM_MENU_KEY_SYS_INFO_APPLICATION},
    { VER_INFO_ROW_VIZIO_NDK_VER,           MLM_MENU_KEY_SYS_INFO_VIZIO_NDK_VERSION},
    { VER_INFO_ROW_SCPL,                    MLM_MENU_KEY_SYS_INFO_SCPL},
    { VER_INFO_ROW_AIRPLAY_VER,             MLM_MENU_KEY_SYS_INFO_AIRPLAY_VERSION},
    { VER_INFO_ROW_AIRPLAY_INTERNAL,        MLM_MENU_KEY_SYS_INFO_AIRPLAY_INTERNAL},
    { VER_INFO_ROW_APPLE_TV_VER,            MLM_MENU_KEY_SYS_INFO_APPLE_TV_VERSION},
    { VER_INFO_ROW_HBOMAX_VER,              MLM_MENU_KEY_SYS_INFO_HBOMAX_VERSION},
    { VER_INFO_ROW_COBALT,                  MLM_MENU_KEY_SYS_INFO_COBALT},
    { VER_INFO_ROW_DAI,                     MLM_MENU_KEY_SYS_INFO_DAI},
    { VER_INFO_ROW_DLM_GENERIC_HOOKS,       MLM_MENU_KEY_SYS_INFO_DLM_GENERIC_HOOKS},

  #ifdef MT5695L_MODEL // MVR-162
    { VER_INFO_ROW_CAMERA_INFO,       MLM_MENU_KEY_SYS_INFO_CAMERA_INFO},
    { VER_INFO_ROW_CAMERA_ISP,        MLM_MENU_KEY_SYS_INFO_CAMERA_ISP},
    { VER_INFO_ROW_MIC_ARRAY_DSP,     MLM_MENU_KEY_SYS_INFO_MIC_ARRAY_DSP},
  #endif

    { VER_INFO_ROW_UTV,                     MLM_MENU_KEY_SYS_INFO_UTV},
    { VER_INFO_ROW_UTV_ESN,                 MLM_MENU_KEY_SYS_INFO_UTV_ESN},
    { VER_INFO_ROW_UTV_SV,                  MLM_MENU_KEY_SYS_INFO_UTV_SV},
    { VER_INFO_ROW_UTV_REG,                 MLM_MENU_KEY_SYS_INFO_UTV_REG},
    { VER_INFO_ROW_UTV_NP,                  MLM_MENU_KEY_SYS_INFO_UTV_NP},
    { VER_INFO_ROW_NETFLIX_ESN,             MLM_MENU_KEY_SYS_INFO_NETFLIX_ESN},
    { VER_INFO_ROW_UTV_UID,                 MLM_MENU_KEY_SYS_INFO_UTV_UID},
    { VER_INFO_ROW_DEV_ID,                  MLM_MENU_KEY_SYS_INFO_UTV_DEV_ID},
    { VER_INFO_ROW_PROV_ID,                 MLM_MENU_KEY_SYS_INFO_UTV_PROV_ID},
    { VER_INFO_ROW_UTV_DA,                  MLM_MENU_KEY_SYS_INFO_UTV_DA},
    { VER_INFO_ROW_COUNTRY,                 MLM_MENU_KEY_SYS_INFO_COUNTRY},
    { VER_INFO_ACCUMULATED_OPERATING_HOURS, MLM_MENU_KEY_SYS_INFO_ACCUMULATED_OPERATING_HOURS},
    { VER_INFO_ROW_CHANNEL_INFO,            MLM_MENU_KEY_SYS_INFO_CHANNEL_INFO},
    { VER_INFO_ROW_PHY_CH,                  MLM_MENU_KEY_SYS_INFO_PHY_CH},
    { VER_INFO_ROW_FREQ,                    MLM_MENU_KEY_SYS_INFO_FREQ},
    { VER_INFO_ROW_MODULATION,              MLM_MENU_KEY_SYS_INFO_MODULATION},
    { VER_INFO_ROW_STATUS,                  MLM_MENU_KEY_SYS_INFO_STATUS},
    { VER_INFO_ROW_SQ,                      MLM_MENU_KEY_SYS_INFO_SQ},
    { VER_INFO_ROW_TUNER,                   MLM_MENU_KEY_SYS_INFO_TUNER},
// { VER_INFO_ROW_GOOGLE_HOME_VER,        MLM_MENU_KEY_SYS_INFO_GOOGLE_HOME_VERSION},
// { VER_INFO_ROW_AMAZON_VER,        MLM_MENU_KEY_SYS_INFO_AMAZON_VERSION},
// { VER_INFO_ROW_PROGRESSIVE,            MLM_MENU_KEY_SYS_INFO_PROGRESSIVE},
// { VER_INFO_ROW_FRC_VER,     MLM_MENU_KEY_SYS_INFO_FRC_VER},
// { VER_INFO_ROW_DIID,                MLM_MENU_KEY_SYS_INFO_DIID},
// { VER_INFO_ROW_TV_AD_ID,                MLM_MENU_KEY_SYS_INFO_TV_AD_ID},
// { VER_INFO_ROW_NETFLIX_ESN2,       MLM_MENU_KEY_SYS_INFO_NETFLIX_ESN2},
 //{ VER_INFO_ROW_VCT,                          MLM_MENU_KEY_SYS_INFO_VCT},
 //{ VER_INFO_ROW_SLD,                           MLM_MENU_KEY_SYS_INFO_SLD},
//   { VER_INFO_ROW_DOWN_SPEED,         MLM_MENU_KEY_SYS_INFO_DOWNLOAD_SPEED},
//   { VER_INFO_ROW_RSSI,               MLM_MENU_KEY_SYS_INFO_RSSI},
//   { VER_INFO_ROW_WIFI_CHANNEL,       MLM_MENU_KEY_SYS_INFO_WIFI_CHANNEL},
 //{ VER_INFO_MAC_ADDRESS,            MLM_MENU_KEY_SYS_INFO_MAC_ADDR},
//   { VER_INFO_ROW_UTV_GID,            MLM_MENU_KEY_SYS_INFO_UTV_GID},
//   { VER_INFO_ROW_UTV_MV,             MLM_MENU_KEY_SYS_INFO_UTV_MV},
 //{ VER_INFO_ROW_UTV_FCT,                   MLM_MENU_KEY_SYS_INFO_UTV_FCT},
//   { VER_INFO_ROW_UTV_FET,            MLM_MENU_KEY_SYS_INFO_UTV_FET},
//   { VER_INFO_ROW_UTV_LT,             MLM_MENU_KEY_SYS_INFO_UTV_LT},
 //{ VER_INFO_ROW_UTV_SYN,                   MLM_MENU_KEY_SYS_INFO_UTV_SYN},
//   { VER_INFO_ROW_UTV_LDT,            MLM_MENU_KEY_SYS_INFO_UTV_LDT},
//   { VER_INFO_ROW_UTV_LDM,            MLM_MENU_KEY_SYS_INFO_UTV_LDM},
//   { VER_INFO_ROW_UTV_EC,             MLM_MENU_KEY_SYS_INFO_UTV_EC},
//   { VER_INFO_ROW_UTV_LE,             MLM_MENU_KEY_SYS_INFO_UTV_LE},
//   { VER_INFO_ROW_UTV_LET,            MLM_MENU_KEY_SYS_INFO_UTV_LET},
//   { VER_INFO_ROW_RD,                 MLM_MENU_KEY_SYS_INFO_UTV_RD},
 //{ VER_INFO_ROW_ML,                            MLM_MENU_KEY_SYS_INFO_UTV_ML},
 //{ VER_INFO_ROW_MC,                           MLM_MENU_KEY_SYS_INFO_UTV_MC},
 //{ VER_INFO_ROW_SRV_RST,                  MLM_MENU_KEY_SERVICE_RST_ITEM},
 //{ VER_INFO_ROW_SRV_CHK,                 MLM_MENU_KEY_SERVICE_RST_ITEM},

   { VER_INFO_ROW_LAST_NUM,           MLM_MENU_KEY_EMPTY}
};

UINT16 aui_mlm[VER_INFO_ROW_LAST_NUM+1] =
{
    MLM_MENU_KEY_SYS_INFO,
    MLM_MENU_KEY_SYS_INFO_CAST_NAME,
    MLM_MENU_KEY_SYS_INFO_SN,
    MLM_MENU_KEY_SYS_INFO_MODEL,
    MLM_MENU_KEY_SYS_INFO_VER,
    MLM_MENU_KEY_SYS_INFO_REST_VISION,
    MLM_MENU_KEY_SYS_INFO_AIRPLAY_VERSION,
    MLM_MENU_KEY_SYS_INFO_CHROMIUM_VISION,
    MLM_MENU_KEY_SYS_INFO_CAST_VER,
    MLM_MENU_KEY_SYS_INFO_SOURCE,
    MLM_MENU_KEY_SYS_INFO_RESOLITION,
    MLM_MENU_KEY_SYS_INFO_VFREQ,
    //MLM_MENU_KEY_SYS_INFO_PROGRESSIVE,
    MLM_MENU_KEY_SYS_INFO_AUDIO_TYPE,
    MLM_MENU_KEY_SYS_INFO_AUDIO_TYPE_OUT,
    MLM_MENU_KEY_SYS_INFO_HDR,
    //MLM_MENU_KEY_SYS_INFO_FRC_VER,
    MLM_MENU_KEY_SYS_INFO_NETFLIX_ESN,
    MLM_MENU_KEY_SYS_INFO_NETFLIX_ESN2,
    MLM_MENU_KEY_SYS_INFO_CHANNEL_INFO,
    MLM_MENU_KEY_SYS_INFO_PHY_CH,
    MLM_MENU_KEY_SYS_INFO_FREQ,
    MLM_MENU_KEY_SYS_INFO_MODULATION,
    MLM_MENU_KEY_SYS_INFO_STATUS,
    MLM_MENU_KEY_SYS_INFO_SQ,
    MLM_MENU_KEY_SYS_INFO_TUNER,
    //MLM_MENU_KEY_SYS_INFO_VCT,
    //MLM_MENU_KEY_SYS_INFO_SLD,
    MLM_MENU_KEY_SYS_INFO_REMOTE,
    MLM_MENU_KEY_SYS_INFO_REMOTE_MODEL,
    MLM_MENU_KEY_SYS_INFO_VERSION,
    MLM_MENU_KEY_SYS_INFO_MAC_ADDR,
    MLM_MENU_KEY_SYS_INFO_BATTERY,

    MLM_MENU_KEY_SYS_INFO_NETWORK,
    MLM_MENU_KEY_SYS_INFO_CONNECTION_TYPE,
    MLM_MENU_KEY_SYS_INFO_SSID,
    MLM_MENU_KEY_SYS_INFO_SECURITY_TYPE,
    MLM_MENU_KEY_SYS_INFO_IP_ADDR,
    MLM_MENU_KEY_SYS_INFO_DEF_GATEWAY,
    MLM_MENU_KEY_SYS_INFO_SUB_MASK,
    MLM_MENU_KEY_SYS_INFO_PREF_DNS,
    MLM_MENU_KEY_SYS_INFO_ALT_DNS,
    MLM_MENU_KEY_SYS_INFO_DOWNLOAD_SPEED,
    MLM_MENU_KEY_SYS_INFO_WIFI_STRENGTH,
    MLM_MENU_KEY_SYS_INFO_RSSI,
    MLM_MENU_KEY_SYS_INFO_WIFI_CHANNEL,
    MLM_MENU_KEY_SYS_INFO_RJ45_MAC,
    MLM_MENU_KEY_SYS_INFO_WLAN_MAC,
    MLM_MENU_KEY_SYS_INFO_WIFI_MODE,
    //MLM_MENU_KEY_SYS_INFO_BLUETOOTH_MAC,
    MLM_MENU_KEY_SYS_INFO_UTV,
    MLM_MENU_KEY_SYS_INFO_UTV_ESN,
    MLM_MENU_KEY_SYS_INFO_UTV_DA,
    MLM_MENU_KEY_SYS_INFO_UTV_UID,
    MLM_MENU_KEY_SYS_INFO_UTV_MV,
    MLM_MENU_KEY_SYS_INFO_UTV_SV,
    MLM_MENU_KEY_SYS_INFO_UTV_REG,
    //MLM_MENU_KEY_SYS_INFO_UTV_FCT,
    MLM_MENU_KEY_SYS_INFO_UTV_FET,
    MLM_MENU_KEY_SYS_INFO_UTV_LT,
    MLM_MENU_KEY_SYS_INFO_UTV_NP,
    //MLM_MENU_KEY_SYS_INFO_UTV_SYN,
    MLM_MENU_KEY_SYS_INFO_UTV_LDT,
    MLM_MENU_KEY_SYS_INFO_UTV_LDM,
    MLM_MENU_KEY_SYS_INFO_UTV_EC,
    MLM_MENU_KEY_SYS_INFO_UTV_LE,
    MLM_MENU_KEY_SYS_INFO_UTV_LET,
    //MLM_MENU_KEY_SYS_INFO_UTV_LPS,
    //MLM_MENU_KEY_SYS_INFO_UTV_LDV,
    //MLM_MENU_KEY_SYS_INFO_UTV_LDS,
    //MLM_MENU_KEY_SYS_INFO_UTV_DEV_CLASS,
    MLM_MENU_KEY_SYS_INFO_UTV_RD,
    MLM_MENU_KEY_SYS_INFO_UTV_DEV_ID,
    MLM_MENU_KEY_SYS_INFO_UTV_PROV_ID
    //MLM_MENU_KEY_SYS_INFO_UTV_ML,
    //MLM_MENU_KEY_SYS_INFO_UTV_MC
    //MLM_MENU_KEY_SERVICE_RST_ITEM,
    //MLM_MENU_KEY_SERVICE_CHECK_ITEM
};

static BOOL     ab_item_show_flag[VER_INFO_ROW_LAST_NUM+1] = {0};
static BOOL     b_airplay_install = FALSE;
static INT32 _refresh_info(VOID);
static VOID _ver_info_reset_timer(VOID);
static VOID _timer_signal_nfy_fct(HANDLE_T h_timer,VOID* pv_tag);
static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag);
static INT32 _lb_ver_info_update_first_elem(VOID);

#ifdef APP_EMANUAL_SP6_SUPPORT
static UINT16   aui2_key_seq_id[VER_INFO_KEY_SEQ_NUM] = {0};
static UINT32   ui4_key_seq_play[MENU_PAGE_VER_INFO_KEY_SEQ_LEN] =
                                 {BTN_CURSOR_LEFT, BTN_CURSOR_RIGHT, BTN_PLAY};
static UINT32   ui4_key_seq_stop[MENU_PAGE_VER_INFO_KEY_SEQ_LEN] =
                                 {BTN_CURSOR_LEFT, BTN_CURSOR_RIGHT, BTN_STOP};
#endif


/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
extern CHAR* sys_cust_get_usb_upg_version(VOID);
extern INT32 a_pop_get_audio_focus(VOID);
extern INT32 nav_get_svctx_handle(TV_WIN_ID_T e_tv_win_id,HANDLE_T* ph_svctx);
extern INT32 x_thread_create(HANDLE_T    *ph_th_hdl,         /* thread handle */
            const CHAR  *ps_name,
            SIZE_T       z_stacksize,
            UINT8        ui1_pri,           /* thread priority */
            x_os_thread_main_fct pf_main,   /* thread's main function */
            SIZE_T       z_arg_size,
            VOID         *pv_arg);

extern INT32 a_isl_get_vtrl_input_display_name(ISL_REC_T*    pt_isl_rec,
                                                    CHAR*         s_name);
extern INT32 c_scc_aud_get_iec_type( HANDLE_T                   h_aud,
                              SCC_AUD_IEC_TYPE_T*        pe_iec_type );

extern BOOL a_is_oled_compensation_support();
static INT32 _ver_info_get_scc_audio_type_out(SCC_AUD_IEC_TYPE_T*  pe_iec_type);
static INT32 _ver_info_item_update(VER_INFO_ROWNUM ver_info_row, CHAR* s_value);
static INT32 _ver_info_item_update_uc(VER_INFO_ROWNUM ver_info_row, UTF16_T* w2s_tmp_str);
extern INT32 ver_info_get_audio_type_in(CHAR* s_name);


/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

 /*----------------------------------------------------------------------------
 * Name: _menu_show_download_speed
 *
 * Description: get download speed and show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 i4_g_speed = 0;
static VOID _menu_show_download_speed(VOID*  pv_data1,
                                      VOID*  pv_data2,
                                      VOID*  pv_data3)
{
#if 0
    INT32 i4_ret;
    CHAR        string[64]      ={'\0'};
    UTF16_T     w2s_str[128]  = {0};
    UTF16_T     w2s_tmp_str[128]     = {0};

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    c_snprintf(string, NETWORK_SPEED_LEN-1, "%.2f Kb/s",(DOUBLE)i4_g_speed);
    c_uc_ps_to_w2s(string,w2s_tmp_str,c_strlen(string));


    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_DOWN_SPEED],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_DOWN_SPEED],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_refresh();
    menu_pm_repaint();
#endif
    return ;
}


/*----------------------------------------------------------------------------
 * Name: download_speed_callback
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID download_speed_callback(INT32 i4Status,DOUBLE  u4Speed)
{
    if (i4Status == 0)
    {
        /* kbit/s, middleware return data is bytes/s, so need data*8/1024 */
        i4_g_speed = u4Speed/128;
    }
    else
    {
        /* speed test is failed */
        i4_g_speed = 0;
    }

    menu_request_context_switch(_menu_show_download_speed, NULL, NULL, NULL);

    return;
}

/*get corrent svctx*/
HANDLE_T get_crnt_svctx(VOID)
{
    TV_WIN_ID_T     t_win_id     = TV_WIN_ID_MAIN;
    HANDLE_T        h_crnt_svctx = NULL_HANDLE;

    if (!a_tv_get_focus_win(&t_win_id))
    {
        nav_get_svctx_handle(t_win_id,&h_crnt_svctx);
        return h_crnt_svctx;
    }
    else
    {
        DBG_LOG_PRINT(("Could not get current svctx. \n"));
    }

    return NULL_HANDLE;
}

INT32 menu_get_netflix_esn2(CHAR* s_esn2_str)
{
    INT32   i4_ret = MENUR_OK;
#define OBJ_ID_BUFF_SZ          (256)       /* 256 bytes */
#define OBJ_CONTENT_BUFF_SZ     (1024 * 7)  /* 5K bytes  */

    static CHAR     s_obj_id[OBJ_ID_BUFF_SZ] = {0};
    static UCHAR    s_obj_content[OBJ_CONTENT_BUFF_SZ] = {0};

    BOOL    b_get_esn = FALSE;
    CHAR    s_NFL_OWN_NAME[16] = {0};
    CHAR    s_KPE_OBJ_NAME[16] = {0};

    FILE * pFile = NULL;

    c_memset(s_obj_id, 0, OBJ_ID_BUFF_SZ);
    c_memset(s_obj_content, 0, OBJ_CONTENT_BUFF_SZ);

    pFile = fopen ("/tmp/netflix/nrd-app/idfile","r");
    if (pFile != NULL)
    {
        if ( fgets(s_obj_id, sizeof(s_obj_id)-1, pFile) != NULL
           && c_strlen(s_obj_id) > 0)
        {
            b_get_esn = TRUE;
        }
        fclose(pFile);
    }

    if (!b_get_esn)
    {
        do {
            /* Owner & Object names */
            memset(s_NFL_OWN_NAME, 0, 16);
            memset(s_KPE_OBJ_NAME, 0, 16);

            /*Init Object Name & Owner*/
        #ifdef ULI_USE_ODL_LIB
            i4_ret = utv_project_get_owner("NETFLIX_NATIVE",s_NFL_OWN_NAME);
            if (0 != i4_ret)
            {
                DBG_ERROR(("<MENU:>: utv_project_get_owner() failed: %d\n", i4_ret));
                break;
            }

            i4_ret = utv_project_get_name("NETFLIX_NATIVE_KPE",s_KPE_OBJ_NAME);
            if (0 != i4_ret)
            {
                DBG_ERROR(("<MENU:>: utv_project_get_name() failed: %d\n", i4_ret));
                break;
            }
            DBG_INFO(("<MENU> %d ver info page get Netflix data.\n", __LINE__));

            i4_ret = utv_project_on_obj_req((CHAR *)s_NFL_OWN_NAME,
                                            (CHAR *)s_KPE_OBJ_NAME,
                                            (CHAR *)&(s_obj_id[0]),
                                            OBJ_ID_BUFF_SZ,
                                            (UCHAR *)&(s_obj_content[0]),
                                            OBJ_CONTENT_BUFF_SZ,
                                            &ui4_obj_sz,
                                            &ui4_encrypt_type);
        #endif

            if (0 != i4_ret)
            {
                DBG_ERROR(("<MENU:>: utv_project_on_obj_req() failed: %d\n", i4_ret));
                break;
            }
        }while (0);
    }

    DBG_LOG_PRINT(("<menu> Netflix ESN2=[%s]\n",s_obj_id));

    c_strcpy(s_esn2_str, s_obj_id);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _int_to_w2s
 *
 * Description: Interger to string utility function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _int_to_w2s(UTF16_T* w2s_dst,
                  INT32 i4_src,
                  UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}

#if 0
static INT32 _ver_info_netflix_esn2_update(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UTF16_T w2s_tmp_str[256] = {0};
    UTF16_T w2s_str[256] = {0};

    static CHAR     s_obj_id[256] = {0};

    menu_get_netflix_esn2(s_obj_id);

    /* NETFLIX ESN2 */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (c_strlen(s_obj_id) == 0)
    {
        c_strcpy(s_obj_id, " N/A");
    }

    c_uc_ps_to_w2s(s_obj_id, w2s_tmp_str,127);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_NETFLIX_ESN2],0),
                       w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_NETFLIX_ESN2],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
#endif

static void menu_ver_info_netflix_esn_prefix(CHAR* s_esn_prefix)
{
    UINT8 ui1_odm_id = 0;

    a_cfg_custom_get_odm_idx(&ui1_odm_id);

    switch (ui1_odm_id)
    {
        case ODM_ID_Amtran:
        case ODM_ID_Wistron:
        case ODM_ID_Foxconn:
        case ODM_ID_KONKA:
        default:
            break;

        case ODM_ID_TPV:
            c_strcpy(s_esn_prefix, "VIZMG332");
            break;

        case ODM_ID_BOE:
            c_strcpy(s_esn_prefix, "VIZMG335");
            break;

        case ODM_ID_Innolux:
            c_strcpy(s_esn_prefix, "VIZMG336");
            break;
    }
}

INT32 menu_ver_info_netflix_esn(CHAR* s_esn, UINT32 sesn_max_len)
{
    /*** Netflix ESN ***/
    CHAR     buff[256] = {0};
    FILE     *pFile = NULL;
    CHAR     *p_esn = NULL;
    UTF16_T  w2s_tmp_str[256] = {0};
    UTF16_T  w2s_str[256] = {0};

    pFile = fopen ("/certificate/netflix/ESNID","r");
    if (pFile != NULL)
    {
        if (NULL == fgets(buff, sizeof(buff) - 1, pFile))
        {
            c_strcpy(buff, "N/A");
        }
        fclose(pFile);
    }

    if(NULL != (p_esn = strstr(buff,"=")))
    {
    #if 1
        c_strncpy(w2s_tmp_str, p_esn + 1, sesn_max_len);

        menu_ver_info_netflix_esn_prefix(w2s_str);

        c_uc_w2s_strncat(w2s_str, w2s_tmp_str, c_uc_w2s_strlen(w2s_tmp_str));

        c_strncpy(s_esn, w2s_str, sesn_max_len);
        DBG_LOG_PRINT((" [%d] s_esn: %s \n", __LINE__, (CHAR*)s_esn));
    #else
        c_strncpy(s_esn, p_esn + 1, sesn_max_len);
    #endif
    }
    else if (c_strlen(buff) != 0)
    {
        c_strncpy(s_esn, buff, sesn_max_len);
    }
    else {
        c_strncpy(s_esn, "N/A", sesn_max_len);
    }

    return MENUR_OK;
}

static INT32 _ver_info_netflix_info_update(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UTF16_T w2s_tmp_str[256] = {0};
    UTF16_T w2s_str[256] = {0};
    CHAR    buff[256] = {0};

    menu_ver_info_netflix_esn(buff, 256);

    c_uc_ps_to_w2s(buff, w2s_tmp_str,256);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_NETFLIX_ESN],0),
                       w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_NETFLIX_ESN],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

   // _ver_info_netflix_esn2_update();

    return i4_ret;
}

INT32 menu_ver_info_apple_tv_ver(CHAR* s_ver, UINT32 max_len)
{
    CHAR    buff[256] = {0};
    FILE    *pFile = NULL;

    pFile = fopen ("/data/app/appletv/VERSION","r");
    if (pFile != NULL)
    {
        if (NULL == fgets(buff, sizeof(buff) - 1, pFile))
        {
            c_strcpy(buff, "N/A");
        }
        fclose(pFile);
    }

    if (c_strlen(buff) != 0)
    {
        c_strncpy(s_ver, buff, max_len);
    }
    else {
        c_strncpy(s_ver, "N/A", max_len);
    }

    return MENUR_OK;
}

INT32 menu_ver_info_hbomax_ver(CHAR* s_ver, UINT32 max_len)
{
    CHAR    buff[256] = {0};
    FILE    *pFile = NULL;

    pFile = fopen ("/data/app/hbomax/VERSION","r");
    if (pFile != NULL)
    {
        if (NULL == fgets(buff, sizeof(buff) - 1, pFile))
        {
            c_strcpy(buff, "N/A");
        }
        fclose(pFile);
    }

    if (c_strlen(buff) != 0)
    {
        c_strncpy(s_ver, buff, max_len);
    }
    else {
        c_strncpy(s_ver, "N/A", max_len);
    }

    return MENUR_OK;
}

INT32 menu_ver_info_castcore_ver(CHAR* s_ver, UINT32 max_len)
{
    CHAR    buff[256] = {0};
    FILE    *pFile = NULL;

    pFile = fopen ("/data/app/castcore/VERSION","r");
    if (pFile != NULL)
    {
        if (NULL == fgets(buff, sizeof(buff) - 1, pFile))
        {
            c_strcpy(buff, "N/A");
        }
        fclose(pFile);
    }

    if (c_strlen(buff) != 0)
    {
        c_strncpy(s_ver, buff, max_len);
    }
    else {
        c_strncpy(s_ver, "N/A", max_len);
    }

    return MENUR_OK;
}

INT32 menu_ver_info_vizio_ndk_ver(CHAR* s_ver, UINT32 max_len)
{
    CHAR    buff[256] = {0};
    FILE    *pFile = NULL;

    pFile = fopen ("/data/app/viziondk/VERSION","r");
    if (pFile != NULL)
    {
        if (NULL == fgets(buff, sizeof(buff) - 1, pFile))
        {
            c_strcpy(buff, "N/A");
        }
        fclose(pFile);
    }

    if (c_strlen(buff) != 0)
    {
        c_strncpy(s_ver, buff, max_len);
    }
    else {
        c_strncpy(s_ver, "N/A", max_len);
    }

    return MENUR_OK;
}



INT32 menu_ver_info_airplay_internal_ver(CHAR* s_ver, UINT32 max_len)
{
    CHAR    buff[256] = {0};
    FILE    *pFile = NULL;

    pFile = fopen ("/data/app/vzairplay/VERSION","r");
    if (pFile != NULL)
    {
        if (NULL == fgets(buff, sizeof(buff) - 1, pFile))
        {
            c_strcpy(buff, "N/A");
        }
        fclose(pFile);
    }

    if (c_strlen(buff) != 0)
    {
        c_strncpy(s_ver, buff, max_len);
    }
    else {
        c_strncpy(s_ver, "N/A", max_len);
    }

    return MENUR_OK;
}


INT32 menu_ver_info_bluetooth_ver(CHAR* s_ver, UINT32 max_len)
{
    CHAR    buff[256] = {0};
    FILE    *pFile = NULL;
    char *pos;

    pFile = fopen ("/data/app/bluetooth/VERSION","r");
    if (pFile != NULL)
    {
        if (fgets(buff, sizeof(buff) - 1, pFile) == NULL)
        {
            c_strcpy(buff, "N/A");
        }

        if ((pos = c_strchr(buff, '\n')) != NULL) {
            *pos = '\0';
        }

        fclose(pFile);
    }

    c_strncpy(s_ver, buff, max_len);
    return MENUR_OK;
}

INT32 menu_ver_info_accumulated_operating_hours(FLOAT* pf_hours)
{
    INT32 i4_ret = 0;
    UINT32 ui4_hours;
    a_cfg_cust_drv_get_oled_display_time(&ui4_hours);
    if (MENUR_OK == i4_ret)
    {
        *pf_hours = (FLOAT)ui4_hours / 60;
    }
    return i4_ret;
}


static INT32 _ver_info_accumulated_operating_hours_update(VOID)
{
    INT32  i4_ret = 0;
    FLOAT  f_value = 0;
    CHAR   s_buf[32];

    MENU_LOG_ON_FAIL(menu_ver_info_accumulated_operating_hours(&f_value));
    DBG_LOG_PRINT(("[menu][system info] %s %.1f ui4_value = %d\n",__FUNCTION__,__LINE__, f_value));
    c_sprintf(s_buf, "%.1f", f_value);
    i4_ret = _ver_info_item_update(VER_INFO_ACCUMULATED_OPERATING_HOURS, s_buf);

    return i4_ret;
}


static INT32 _ver_info_bluetooth_version_update(VOID)
{
    INT32 i4_ret = 0;
    CHAR  s_ver[64] = {0};
    UTF16_T w2s_ver[256] = {0};
    UTF16_T w2s_str[256] = {0};

    MENU_LOG_ON_FAIL(menu_ver_info_bluetooth_ver(s_ver, 64));
    c_uc_ps_to_w2s(s_ver, w2s_ver, c_strlen(s_ver));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_BLUETOOTH_VERSION], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_ver, c_uc_w2s_strlen(w2s_ver));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_BLUETOOTH_VERSION], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ver_info_country_update(VOID)
{
    INT32 i4_ret = 0;
    UTF16_T w2s_country[256] = {0};
    UTF16_T w2s_str[256] = {0};

    ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_LAST_ENTRY;
    a_cfg_custom_get_country_code(&t_country);

    switch (t_country)
    {
        case ACFG_COUNTRY_CODE_US:
            DBG_LOG_PRINT(("[sysinfo] Country: US (%d) \n\r", t_country));
            c_uc_w2s_strcat(w2s_country, MENU_TEXT(MLM_MENU_KEY_COUNTRY_USA));
            break;

        case ACFG_COUNTRY_CODE_MEX:
            DBG_LOG_PRINT(("[sysinfo] Country: MEX (%d) \n\r", t_country));
            c_uc_w2s_strcat(w2s_country, MENU_TEXT(MLM_MENU_KEY_COUNTRY_MEX));
            break;

        case ACFG_COUNTRY_CODE_CA:
            DBG_LOG_PRINT(("[sysinfo] Country: CA (%d) \n\r", t_country));
            c_uc_w2s_strcat(w2s_country, MENU_TEXT(MLM_MENU_KEY_COUNTRY_CA));
            break;

        case ACFG_COUNTRY_CODE_UNKNOWN:
            DBG_LOG_PRINT(("[sysinfo] Country: UNKNOWN (%d) \n\r", t_country));
            c_uc_w2s_strcat(w2s_country, MENU_TEXT(MLM_MENU_KEY_COUNTRY_UNKNOWN));
            break;

        default:
            DBG_LOG_PRINT(("[sysinfo] Country: NA (%d) \n\r", t_country));
            c_uc_w2s_strcat(w2s_country, MENU_TEXT(MLM_MENU_KEY_SYS_INFO_NA));
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_COUNTRY], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_country, c_uc_w2s_strlen(w2s_country));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_COUNTRY], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ver_info_signal_quality_update(VOID)
{
    INT32                           i4_ret = 0;
    UTF16_T                         w2s_tmp_str[128];
    UTF16_T                         w2s_str[128];
    UINT8                           ui1_signal_level = 0;
    CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8                           ui1_input_id = 0;
    ISL_REC_T                       t_isl_rec;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
    {
        return MENUR_OK;
    }

    /*Signal Quality*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    SVL_REC_T                       t_svl_rec;
    BOOL                            b_found = FALSE;
    BOOL                            b_digital_ch = FALSE;

      /* Get digital/analog channel */
     menu_get_crnt_svl_rec(&t_svl_rec, &b_found);

    if(b_found &&
       t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
    {
        b_digital_ch = TRUE;
    }

    if(b_digital_ch)
    {
        i4_ret = c_svctx_get_signal_level(menu_get_crnt_svctx(),&ui1_signal_level);
    }
    else
    {
        i4_ret = c_svctx_get_dbm_signal_level(menu_get_crnt_svctx(),(INT16*)&ui1_signal_level);
    }
    _int_to_w2s(w2s_tmp_str, ui1_signal_level, 8);

    c_uc_w2s_strcpy(w2s_str,w2s_g_sq);
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SQ], 0),
                          WGL_PACK(w2s_str));
    MENU_LOG_ON_FAIL(i4_ret);
    _lb_ver_info_update_first_elem();

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
* Name:
*                 _menu_page_ver_info_get_tuner_model_type
* Description:
*                        This function is used to get customer tuner model type.
* Input arguments:
*        s_tmp_str      Contains the model type name of the customer tuner.
*
* Output arguments:
*                   None
* Returns:
*                  None
*---------------------------------------------------------------------------*/
static INT32 _menu_page_ver_info_get_tuner_model_type(CHAR* s_tmp_str)
{
    INT32    i4_ret = 0;

    if (NULL == s_tmp_str)
    {
       DBG_ERROR(("{MENU VER INFO GET TUNER MODEL TYPE FAIL}%s,%d\n", __FUNCTION__, __LINE__));
       return MENUR_FAIL;
    }

    i4_ret = a_cfg_custom_get_tuner_name(s_tmp_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return  i4_ret;

}

/*----------------------------------------------------------------------------
* Name:
*                 _ver_info_tuner_update
* Description:
*                         This function is used to get customer tuner model type then refeash it.
* Input arguments:
*        None
*
* Output arguments:
*                   None
* Returns:
*                  None
*---------------------------------------------------------------------------*/

static INT32 _ver_info_tuner_update(VOID)
{
    INT32           i4_ret = 0;
    UTF16_T         w2s_tmp_str[CUST_TUNER_TYPE_NAME_MAX_LEN];
    UTF16_T         w2s_str[CUST_TUNER_TYPE_NAME_MAX_LEN];

    /* Tuner */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    c_uc_ps_to_w2s(s_tuner_type,w2s_tmp_str,CUST_TUNER_TYPE_NAME_MAX_LEN-1);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_TUNER],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_TUNER],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ver_info_ch_info_update(VOID)
{
    INT32                           i4_ret = 0;
    BOOL                            b_found = FALSE;
    BOOL                            b_digital = FALSE;
    BOOL                            b_cable = FALSE;
    SVL_REC_T                       t_svl_rec ;
    TSL_REC_T                       t_tsl_rec;
    UINT16                          ui2_crnt_svl_id = 0;
    UINT32                          ui4_ver_id = 0;
    UINT32                          ui4_msgid = 0;
    UINT32                          ui4_phy_ch = 0;
    FLOAT                           f_freq = 0;
    UTF16_T                         w2s_tmp_str[128];
    UTF16_T                         w2s_str[128];
    //const CHAR*                     s_tmp_str;
    CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8                           ui1_input_id = 0;
    ISL_REC_T                       t_isl_rec;
    CHAR                            s_buf[32] = {0};

    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));

    /* Tuner */
    _ver_info_tuner_update();


    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
    {
        return MENUR_OK;
    }


    /*get svl record*/
    menu_get_crnt_svl_rec (&t_svl_rec ,&b_found) ;

    /*get tsl record*/
    c_tsl_get_rec(menu_get_crnt_tsl(),
                    t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                    &t_tsl_rec,
                    &ui4_ver_id);

    ui4_phy_ch = SB_TSL_GET_PTC_FROM_RECID (t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id);

    /*Physical Channel*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    _int_to_w2s(w2s_tmp_str,ui4_phy_ch,6);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_PHY_CH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_PHY_CH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);



    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    b_cable = (ATSC_TRSTRL_SVL_ID == ui2_crnt_svl_id) ? FALSE : TRUE ;
    b_digital = (BRDCST_TYPE_ANALOG == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type) ? FALSE :TRUE ;

    switch ((UINT8)(b_cable) << 1 | (UINT8)(b_digital))
    {
        case 0 :                                    /* air && analog */
            f_freq = (FLOAT)t_tsl_rec.udata.t_ter_ana.ui4_freq;
            // for DTV02028123
            f_freq += 15625;
            ui4_msgid = MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_NTSC;
        break ;

        case 1 :                                    /* air && digital */
            f_freq = (FLOAT)t_tsl_rec.udata.t_ter_dig.ui4_freq ;
            ui4_msgid = (UINT32)t_tsl_rec.udata.t_ter_dig.e_mod +MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_UNKNOWN ;
        break ;
        case 2 :                                    /* cable && analog */
            f_freq = (FLOAT)t_tsl_rec.udata.t_cab_ana.ui4_freq ;
            ui4_msgid = MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_NTSC;
        break ;
        case 3 :                                    /* cable && digital */
            f_freq = (FLOAT)t_tsl_rec.udata.t_cab_dig.ui4_freq ;
            ui4_msgid = (UINT32)t_tsl_rec.udata.t_cab_dig.e_mod +MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_UNKNOWN ;
        break ;
        default :
        break ;
    }
    // for DTV02028123
    f_freq /= 1000000;
    /*Frequency*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    c_sprintf(s_buf, "%.2f", f_freq);
    c_uc_ps_to_w2s(s_buf, w2s_tmp_str, 9);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_FREQ],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_FREQ],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Modulation*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_MODULATION],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strcat(w2s_str,MENU_TEXT(ui4_msgid));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_MODULATION],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*status*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    ui4_msgid = menu_is_signal_loss () ?
                    MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_UNLOCK : MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_LOCK ;

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_STATUS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strcat(w2s_str,MENU_TEXT(ui4_msgid));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_STATUS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Signal Quality*/
    _ver_info_signal_quality_update();



    /*VCT Count*/

    /*SLD Count*/

    return MENUR_OK;
}

#if 0
static INT32 _get_wifi_remote_channel(UTF16_T* pw2s_channel)
{
    UINT8       ui1_ch = 0;
    CHAR        ac_channel[4] = {0};
    INT32       i4_ret = 0;
    NET_802_11_BSS_INFO_T CurrBss;

    //a_cfg_custom_get_last_p2p0_op_channel(&ui1_ch);
    c_memset(&CurrBss, 0, sizeof(CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&CurrBss);
    MENU_LOG_ON_FAIL(i4_ret);
    if (c_strlen(CurrBss.t_Ssid.ui1_aSsid) > 0)
    {
        ui1_ch = CurrBss.i2_Channel;
    }
    DBG_LOG_PRINT(("%s,%d [sys info]wifi chanel:%d.\r\n",__FUNCTION__,__LINE__,CurrBss.i2_Channel));

    c_sprintf(ac_channel, "%d", ui1_ch);
    c_uc_ps_to_w2s(ac_channel, pw2s_channel, c_strlen(ac_channel));

    return MENUR_OK;
}
#endif


static INT32 _ver_info_remote_info_update(VOID)
{
    UINT32          ui4_status_mlm_idx = MLM_MENU_KEY_SYS_INFO_REMOTE_NOT_PAIRED_NOT_CONNECT;
    REST_API_BT_REMOTE_INFO_T remote_info = {0};
    MENU_LOG_ON_FAIL(rest_get_bluetooth_status(&remote_info));

    switch(remote_info.remote_status)
    {
        case 0:
            ui4_status_mlm_idx = MLM_MENU_KEY_SYS_INFO_REMOTE_PAIRED_NOT_CONNECT;
            break;
        case 1:
            ui4_status_mlm_idx = MLM_MENU_KEY_SYS_INFO_REMOTE_NOT_PAIRED_NOT_CONNECT;
            break;
        case 2:
            ui4_status_mlm_idx = MLM_MENU_KEY_SYS_INFO_REMOTE_PAIRED_CONNECT;
            break;
        default:
            DBG_LOG_PRINT(("[menu][system info] %s remote_status = %d\n",__FUNCTION__,__LINE__, remote_info.remote_status));
            break;
    }

    MENU_LOG_ON_FAIL(_ver_info_item_update_uc(VER_INFO_REMOTE_STATUS, MENU_TEXT(ui4_status_mlm_idx)));

    if (remote_info.remote_status == 1) // NOT PAIRED
    {
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_BATTERY_LIFE, "N/A"));
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_REMOTE_VERSION, "N/A"));
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_REMOTE_SERIAL, "N/A"));
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_BLUETOOTH_MAC, "N/A"));
    }
    else
    {
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_BATTERY_LIFE, remote_info.battery_level));
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_REMOTE_VERSION, remote_info.firmware_version));
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_REMOTE_SERIAL, remote_info.serial_number));
        MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_BLUETOOTH_MAC, remote_info.address));
    }
    return MENUR_OK;
}

static INT32 _ver_info_binaries_version_update(VOID)
{
    REST_API_BINARIES_VERSION_T version = {0};

    MENU_LOG_ON_FAIL(rest_get_binaries_version(&version));
    MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_DAI, version.dai));
    MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_AIRPLAY_INTERNAL, version.airplay));
    MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_COBALT, version.cobalt));
    MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_BLUETOOTH_FIRMWARE, version.bluetooth));

    return MENUR_OK;
}

static INT32 _ver_info_sc_config_update(VOID)
{
    CHAR p_version[64];

    MENU_LOG_ON_FAIL(rest_get_device_info(p_version));
    MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_REST_VER, p_version));

    return MENUR_OK;
}

static INT32 _ver_info_nw_get_ssid(UTF16_T *pw2s_ssid)
{
    INT32                   i4_ret = MENUR_OK;
    INT32                   i4_len = 0;
    BOOL                    b_wireless_connected = FALSE;
    NW_WLAN_STATE_T         e_wlan_state;
    NET_802_11_BSS_INFO_T   t_bss_info;
    CHAR                    s_data[NET_802_11_MAX_LEN_SSID+1] = {0};

    i4_ret = a_nw_wlan_status(&e_wlan_state);
    MENU_LOG_ON_FAIL(i4_ret);

    if (e_wlan_state == NW_WLAN_ASSOCIATE)  /* has associate with wifi*/
    {
        c_memset (&t_bss_info, 0, sizeof(t_bss_info));
        i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
        if(i4_ret != MENUR_OK)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            c_memset(t_bss_info.t_Bssid, 0, sizeof(t_bss_info.t_Bssid));
            t_bss_info.t_Ssid.ui4_SsidLen = 0;
        }
        if ((c_strlen(t_bss_info.t_Ssid.ui1_aSsid) > 0) /*wifi has been connected*/
            &&((UINT8)WLAN_WPA_COMPLETED == t_bss_info.u8_wpa_status))
        {
            b_wireless_connected = TRUE;
        }

        DBG_INFO(("\n%s,%d,from middleware:u8_wpa_status=%d,"
                    "t_CurrBss.t_Ssid.ui4_SsidLen=%d,t_CurrBss.t_Ssid.ui1_aSsid=%s,\n",
                   __FUNCTION__, __LINE__,
                   t_bss_info.u8_wpa_status,
                   t_bss_info.t_Ssid.ui4_SsidLen,
                   t_bss_info.t_Ssid.ui1_aSsid));

        if (a_nw_custom_is_get_ip_addr()&& b_wireless_connected)
        {
            if (c_strlen(t_bss_info.t_Ssid.ui1_aSsid) != 0)
            {
                c_memset(s_data, 0, NET_802_11_MAX_LEN_SSID+1);

                c_strncat(s_data, t_bss_info.t_Ssid.ui1_aSsid, NET_802_11_MAX_LEN_SSID);

                /*if (c_strlen(t_bss_info.t_Ssid.ui1_aSsid) > 16)
                                {
                                    s_data[13] = '.';
                                    s_data[14] = '.';
                                    s_data[15] = '.';
                                    s_data[16] = 0;
                                }*/

                i4_len = c_strlen(s_data);
                c_uc_ps_to_w2s(s_data, pw2s_ssid, i4_len);
            }
        }
        else
        {

        }
    }
    else if (e_wlan_state == NW_WLAN_ASSOCIATING)
    {

    }
    else    /* not associate with wifi*/
    {

    }

    return i4_ret;
}

static INT32 _ver_info_nw_get_security_type(UTF16_T *pw2s_sec_type)
{
    INT32                   i4_ret = RMR_OK;
    NW_WLAN_STATE_T         e_wlan_state;
    NET_802_11_BSS_INFO_T   t_bss_info = {0};
    CHAR                    string[33] = "N/A";
    UTF16_T                 w2s_tmp_str[128] = {0};

    i4_ret = a_nw_wlan_status(&e_wlan_state);
    MENU_LOG_ON_FAIL(i4_ret);

    if (e_wlan_state == NW_WLAN_ASSOCIATE)
    {
        c_memset(&t_bss_info, 0, sizeof(t_bss_info));
        i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    switch(t_bss_info.e_AuthMode)
    {
        case IEEE_802_11_AUTH_MODE_NONE:
        case IEEE_802_11_AUTH_MODE_OPEN:
        {
            c_strncpy(string, "Open", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_SHARED:
        {
            c_strncpy(string, "WEP Shared", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WEPAUTO:
        {
            c_strncpy(string, "WEPAUTO", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA:
        {
            if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_TKIP)
            {
                c_strncpy(string, "WPA TKIP", 32);
            }
            else if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_AES)
            {
                c_strncpy(string, "WPA AES", 32);
            }
            else
            {
                c_strncpy(string, "WPA", 32);
            }
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_PSK:
        {
            c_strncpy(string, "WPA/PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2:
        {
            if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_TKIP)
            {
                c_strncpy(string, "WPA2 TKIP", 32);
            }
            else if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_AES)
            {
                c_strncpy(string, "WPA2 AES", 32);
            }
            else
            {
                c_strncpy(string, "WPA2", 32);
            }
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2_PSK:
        {
            c_strncpy(string, "WPA2/PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
        {
            c_strncpy(string, "WPAPSK/WPA2PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2_PSK_SHA256_AES:
        {
            c_strncpy(string, "WPA2PSK-SHA256AES", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_SAE:
        case IEEE_802_11_AUTH_MODE_WPA2_SAE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2SAE:
        {
            c_strncpy(string, "WPA3 SAE", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_OWE:
        case IEEE_802_11_AUTH_MODE_WPA2_OWE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE:
        {
            c_strncpy(string, "WPA3 Open Enhanced", 32);
            break;
        }

        default:
            break;
    }
    c_uc_ps_to_w2s(string, w2s_tmp_str,127);
    c_uc_w2s_strcpy(pw2s_sec_type, w2s_tmp_str);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ver_info_nw_get_dev_info_thread_main
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _ver_info_nw_get_dev_info_thread_main (VOID* pv_arg)
{
#ifdef VIZIO_FUSION_SUPPORT

    UTF16_T         w2s_tmp_str[128];
    UTF16_T         w2s_str[128];
    BT_GAP_LOCAL_PROPERTIES_RESULT local_dev_info;

    c_memset(w2s_tmp_str,     0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,         0, sizeof(w2s_str));
    c_memset(&local_dev_info, 0, sizeof(BT_GAP_LOCAL_PROPERTIES_RESULT));
#endif
#if 0
    c_btm_get_local_dev_info(&local_dev_info);
    c_uc_ps_to_w2s(local_dev_info.bdAddr,w2s_tmp_str,c_strlen(local_dev_info.bdAddr));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_BLUETOOTH_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_BLUETOOTH_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
}

//
//*****************************************************************************
//
#ifdef MT5695L_MODEL // MVR-162

static INT32 _ver_info_camera_info_update(VOID)
{
    INT32           i4_ret = MENUR_OK;

    UTF16_T         w2s_tmp_str[128];
    UTF16_T         w2s_str[128];
    CHAR *          s_tmp_str;

    CHAR            s_ip_str[16];
    NW_IP_INFO_T    t_net_ip_info;

    CHAR            s_mac_str[64];
    CHAR            s_model_name[64] = {0};
    CHAR            tmp[32] = {0};
    BOOL            b_plug = FALSE;

    DBG_LOG_PRINT(("\r\n\033[45m ************************* \033[0m \n", __FILE__, __FUNCTION__ ));
    DBG_LOG_PRINT(("\033[45m {%s %s()} \033[0m \n", __FILE__, __FUNCTION__ ));
    DBG_LOG_PRINT(("\033[45m ************************* \033[0m \n", __FILE__, __FUNCTION__ ));

    /* Camera ISP */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

#ifdef MTK_CAMERA_DPTZ_SUPPORT
    AVAILABLE_DEVICE_INFO_T availableDevice;
    if (E_MTK_V4L2_RET_OK == mtk_v4l2_get_available_device(&availableDevice))
    {
        for (int i = 0; i < availableDevice.size; ++i)
        {
            const DEVICE_INFO_T* deviceInfo = &availableDevice.deviceList[i];

            if(0 == strcasecmp(deviceInfo->vendorid, SSTAR_VENDOR_ID) && 0 == strcasecmp(deviceInfo->productid, SSTAR_PRODUCT_ID))
            {
                c_uc_ps_to_w2s(deviceInfo->firmwareVersion, w2s_tmp_str, c_strlen(deviceInfo->firmwareVersion));
                DBG_LOG_PRINT(("firmwareVersion: %s\n", deviceInfo->firmwareVersion));
                break;
            }
        }
    }
    else
#endif
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CAMERA_ISP],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CAMERA_ISP],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /* MIC Array DSP */
    CHAR    buff[256] = {0};
    FILE * pFile = NULL;
    pFile = fopen ("/sys/class/voicep/dbmdx/pomelo_ver","r");

    if (pFile != NULL)
    {
        if (NULL == fgets(buff, sizeof(buff) - 1, pFile))
        {
            c_strcpy(buff, "N/A");
        }
        fclose(pFile);
    }

    if (c_strlen(buff) != 0)
    {
        DBG_LOG_PRINT(("%s\n", buff));
        char removed[] = "DSPG_pomelo_version: ";
        if(strlen(removed) >= c_strlen(buff))
        {
            c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
        }
        else
        {
            char *start = strstr(buff, removed);
            char *end = start + strlen(removed);
            strcpy(start, end);
            c_uc_ps_to_w2s(buff, w2s_tmp_str, sizeof(buff));
        }
    }
    else
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_MIC_ARRAY_DSP],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_MIC_ARRAY_DSP],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
#endif

//
//*****************************************************************************
//

static INT32 _ver_info_nw_info_update(VOID)
{
    INT32           i4_ret = MENUR_OK;

    NW_IP_INFO_T    t_net_ip_info;
    NW_IPV6_INFO_T  t_net_ipv6_info;
    CHAR *          s_tmp_str;
    CHAR            s_ip_str[16];
    CHAR            s_mac_str[64];
    CHAR            s_model_name[ACFG_CUSTOM_WIFI_MODULE_NAME_LEN] = {0};
    UTF16_T         w2s_tmp_str[129];
    UTF16_T         w2s_str[129];
    BOOL            b_plug = FALSE;

    /*Connection Type*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = a_nw_get_ethernet_connect_info(&b_plug);
    if(i4_ret)
    {
        s_tmp_str = "UNKNOWN";
    }
    else
    {
        if(b_plug)
        {
            s_tmp_str = "Wired Connection";
        }
        else
        {
            NW_WLAN_BAND_T i4_freq_band = NW_WLAN_FREQ_UNKNOWN;
            i4_freq_band = a_nw_custom_wifi_frequency_band();
            if(i4_freq_band == NW_WLAN_FREQ_2_4_BAND)
            {
                s_tmp_str = "Wi-Fi 2.4GHz";
            }
            else if(i4_freq_band == NW_WLAN_FREQ_5_BAND)
            {
                s_tmp_str = "Wi-Fi 5GHz";
            }
            else if(i4_freq_band == NW_WLAN_FREQ_6_BAND)
            {
                s_tmp_str = "Wi-Fi 6GHz";
            }
            else
            {
                s_tmp_str = "Wi-Fi";
            }
        }
    }

    c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CONNECTION_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CONNECTION_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /* SSID */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (!b_plug)
    {
        _ver_info_nw_get_ssid(w2s_tmp_str);
    }

    if (c_uc_w2s_strlen(w2s_tmp_str) == 0)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SSID],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SSID],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (!b_plug)
    {
        _ver_info_nw_get_security_type(w2s_tmp_str);
    }

    if (c_uc_w2s_strlen(w2s_tmp_str) == 0)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 IP Address*/
    c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    i4_ret = a_nw_get_crnt_ip_info(&t_net_ip_info);
    MENU_LOG_ON_FAIL(i4_ret);

    if(0 == t_net_ip_info.ui4_address)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_address);
        c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IP_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IP_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 Default Gateway*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_gw);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);


    /*IPv4 Subnet Mask*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_netmask);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SUB_MASK],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SUB_MASK],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 Pref. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_1st_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 Alt. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_2nd_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 IP Address*/
    c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
    MENU_LOG_ON_FAIL(i4_ret);

    if(0 == c_strlen(t_net_ipv6_info.ac_v6ip))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_v6ip, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_v6ip));
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IPV6_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IPV6_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 Default Gateway*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(0 == c_strlen(t_net_ipv6_info.ac_v6gw))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_v6gw, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_v6gw));
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IPV6_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IPV6_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 Prefix Length*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    if(0 == t_net_ipv6_info.ui4_prefix)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        _int_to_w2s(w2s_tmp_str, t_net_ipv6_info.ui4_prefix, 4);
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IPV6_PREFIX_LENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IPV6_PREFIX_LENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 Pref. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(0 != c_strlen(t_net_ipv6_info.ac_dns1))
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_dns1, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_dns1));
        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_PREF_DNS],0),
                    w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str, L", ", c_uc_w2s_strlen(w2s_str));
        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_PREF_DNS],0),
                    w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*IPv6 Alt. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(0 != c_strlen(t_net_ipv6_info.ac_dns2))
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_dns2, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_dns2));
        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_ALT_DNS],0),
                    w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str, L", ", c_uc_w2s_strlen(w2s_tmp_str));
        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_ALT_DNS],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*IP Type*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if((c_strlen(t_net_ipv6_info.ac_v6ip) != 0) && (t_net_ip_info.ui4_address != 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" IPv6 & IPv4 ");
    }
    else if((c_strlen(t_net_ipv6_info.ac_v6ip) != 0) && (t_net_ip_info.ui4_address == 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" IPv6 ");
    }
    else if((c_strlen(t_net_ipv6_info.ac_v6ip) == 0) && (t_net_ip_info.ui4_address != 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" IPv4 ");
    }
    else if((c_strlen(t_net_ipv6_info.ac_v6ip) == 0) && (t_net_ip_info.ui4_address == 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IP_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_IP_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);


    /*Download Speed*/
    /*
    if(i4_g_speed == 0)
    {
        i4_ret= c_speedtest(NULL,download_speed_callback);
        if (i4_ret != 0)
        {
            c_speedtest_cancel();
        }
    }
    else
    {
        _menu_show_download_speed(NULL, NULL, NULL);
    }
    */

    /*WIFI Strength*/
    INT32   i2_Level = 80;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();

    _int_to_w2s(w2s_tmp_str,i2_Level,4);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_STRENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_STRENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*RSSI*/
  #if 0
    INT32                       i4Rssi_avg = 0;
    NET_802_11_WIFI_RSSI_T      t_rssi;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));
    c_memset (&t_rssi,    0, sizeof(NET_802_11_WIFI_RSSI_T));

    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    if (i4_ret == 0)
    {
    	i4Rssi_avg = t_rssi.i4Rssi_a;
    	if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_a)&&(t_rssi.i4Rssi_a < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_a);

        if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_b)&&(t_rssi.i4Rssi_b < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_b);

        if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_c)&&(t_rssi.i4Rssi_c < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_c);
    }
    DBG_LOG_PRINT(("[TEST][%s]:[%d]i4Rssi_avg=%d\n",__FILE__,__LINE__,i4Rssi_avg));

    _int_to_w2s(w2s_tmp_str,i4Rssi_avg,4);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RSSI],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RSSI],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
  #endif

    /*WIFI Channel*/
  #if 0
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    i4_ret = _get_wifi_remote_channel(w2s_tmp_str);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_CHANNEL],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_CHANNEL],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
  #endif

    /*RJ45 MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);
#ifndef MT5583_MODEL
    //Get the RJ45 Mac
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);

    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#else
    //Get the ID Mac
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);

    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_ID_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_ID_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    /*WLAN MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);

    a_nw_get_mac_addr_string(NI_WIRELESS_0,s_mac_str);
    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*WiFi Module*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    a_cfg_cust_get_wifi_model_name(s_model_name, ACFG_CUSTOM_WIFI_MODULE_NAME_LEN);
    DBG_LOG_PRINT((" %s, %d line, wifi_nodule_name: %s\n", __FILE__, __LINE__, s_model_name));
    c_uc_ps_to_w2s(s_model_name,w2s_tmp_str,c_strlen(s_model_name));
     i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_MODE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_MODE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);



    return MENUR_OK;
}
static INT32 _ver_info_check_tv_mode()
{
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))
    TV_MODE_T   e_tv_mode = TV_MODE_TYPE_NORMAL;
    TV_WIN_ID_T ui1_pip_aud_src;
    ISL_REC_T   t_isl_rec;

    a_tv_get_mode(&e_tv_mode);
    if( e_tv_mode != TV_MODE_TYPE_NORMAL)
    {
        ui1_pip_aud_src = (TV_WIN_ID_T)a_pop_get_audio_focus();
        if(ui1_pip_aud_src != TV_WIN_ID_MAIN)
        {

            i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_SUB,
                                                &t_isl_rec);
            if( (i4_ret != TVR_OK) ||
                (t_isl_rec.e_src_type != INP_SRC_TYPE_TV) )
            {
                return MENUR_FAIL;
            }
        }
    }
#endif

    return MENUR_OK;
}

INT32 menu_ver_info_get_scc_audio_type_out(SCC_AUD_IEC_TYPE_T*  pe_iec_type)
{
    INT32                     i4_ret = MENUR_OK;
    HANDLE_T                  h_scc = NULL_HANDLE;

    if(pe_iec_type == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* get scc main / sub  handle */
    {
        SM_COMMAND_T                          at_sm_cmds[3];

        if(NULL_HANDLE == h_scc)
        {
             /*scc component for mts operation*/
            at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
            at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
            at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
            at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
            at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
            at_sm_cmds[2].u.ui4_data = 0;

            i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc);
            MENU_CHK_FAIL(SMR_OK == i4_ret ? MENUR_OK : i4_ret);
        }
    }

    do
    {
        /*get scc audio get &iec_type */
        {
            i4_ret = c_scc_aud_get_iec_type(h_scc,pe_iec_type);
            DBG_LOG_PRINT(("\n[audio type] %s  %s  (%d) i4_ret=(%d) pe_iec_type=(%d)\n",__FILE__,__FUNCTION__,__LINE__,i4_ret,*pe_iec_type));
            if(i4_ret != SMR_OK)
            {
                break;
            }
        }
    }while(0);
    c_scc_comp_close(h_scc);

    return i4_ret;

}

static INT32 _ver_info_get_scc_audio_type_out(SCC_AUD_IEC_TYPE_T*  pe_iec_type)
{
    INT32 i4_ret = MENUR_OK;

    if(pe_iec_type == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* check scc on / off */
    {
        UINT8          ui1_sac_status;
        UINT8          ui1_ces_func = 0;
        SIZE_T         z_size ;

        i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_CEC, ICL_RECID_CEC_AMP_PLUG),
                           &ui1_sac_status,
                           &z_size);
        MENU_CHK_FAIL(ICLR_OK == i4_ret ? MENUR_OK : i4_ret);


        i4_ret = a_cfg_get_cec_func (&ui1_ces_func);
        MENU_CHK_FAIL(APP_CFGR_OK == i4_ret ? MENUR_OK : i4_ret);

        #if 0
        if (ui1_sac_status == ICL_CEC_AMP_UNPLUG || ui1_ces_func == APP_CFG_CEC_OFF)
        {
             return MENUR_INV_STATE;
        }
        #endif
    }

    i4_ret = menu_ver_info_get_scc_audio_type_out(pe_iec_type);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ver_info_get_audio_stream_text_in_vtrl(UTF16_T* w2s_str, SIZE_T z_len)
{
    UTF16_T*        pw2s_text     = NULL_HANDLE ;
    SCC_AUD_IEC_TYPE_T  e_iec_type          =   SCC_AUD_IEC_CFG_PCM;
    INT16 i2_val = 0;
    INT32 i4_ret;
    UTF16_T     w2s[64] = {0} ;
    INT32	   eRet ;
    MI_AUDIO_Caps_t stAudioCaps;
    memset(&stAudioCaps,0,sizeof(MI_AUDIO_Caps_t));
    MI_AUDIO_CodecType_e *peCodecType = (MI_AUDIO_CodecType_e *)calloc(stAudioCaps.u32DecoderNum,sizeof(MI_AUDIO_CodecType_e));
    MI_AUDIO_DtsVersion_e *eDtsVersion = (MI_AUDIO_DtsVersion_e *)calloc(1, sizeof(MI_AUDIO_DtsVersion_e));

    /*get dts version*/
    eRet = MI_AUDIO_GetAttr(0, E_MI_AUDIO_ATTR_TYPE_DTS_VERSION, NULL, eDtsVersion);
    eRet = MI_AUDIO_GetAttr(0, E_MI_AUDIO_ATTR_TYPE_CODEC_TYPE, NULL, peCodecType);
    DBG_LOG_PRINT(("[sysinfo] eDtsVersion = %d \n",*eDtsVersion));
    DBG_LOG_PRINT(("[sysinfo] peCodecType = %d \n",*peCodecType));

    i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_val);
    DBG_LOG_PRINT(("[+++] {%s %s() %d}. st_mi_info.eAudioCodec = 0x%x, i2_val = %d.\n",__FILE__, __FUNCTION__, __LINE__,st_mi_info.eAudioCodec,i2_val));

    if(E_MI_MM_AUDIO_CODEC_TYPE_AC3 == st_mi_info.eAudioCodec|| E_MI_MM_AUDIO_CODEC_TYPE_AC3P == st_mi_info.eAudioCodec)
    {
        pw2s_text = L"Dolby Audio";
    }
    else if((E_MI_MM_AUDIO_CODEC_TYPE_AAC == st_mi_info.eAudioCodec) &&
        (e_iec_type == SCC_AUD_IEC_CFG_DD || e_iec_type == SCC_AUD_IEC_CFG_DDP))
    {
        //Dolby Audio-DD
        pw2s_text = L"Dolby Audio";
    }
	else if(E_MI_AUDIO_CODEC_TYPE_DTS  ==  *peCodecType)
	{
		pw2s_text = L"DTS";
	}
	else if(E_MI_AUDIO_CODEC_TYPE_DTS_LBR    ==  *peCodecType)
	{
		if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
		{
			c_uc_w2s_strcpy(w2s, L"DTS-HD ");
		}
		else
		{
			c_uc_w2s_strcpy(w2s, L"DTS Express ");
		}
		pw2s_text = w2s;
	}
    else if(E_MI_AUDIO_CODEC_TYPE_DTSHD  == *peCodecType)
    {
        if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
		{
			c_uc_w2s_strcpy(w2s, L"DTS-HD ");
		}
		else
		{
			c_uc_w2s_strcpy(w2s, L"DTS-HD Master Audio ");
		}
		pw2s_text = w2s;
    }
	else if(E_MI_AUDIO_CODEC_TYPE_DTS_X == *peCodecType)
	{
		if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
		{
			c_uc_w2s_strcpy(w2s, L"DTS:X ");
		}
		else
		{
			c_uc_w2s_strcpy(w2s, L"DTS ");
		}
		pw2s_text = w2s;
	}
#if 0
    else if(E_MI_MM_AUDIO_CODEC_TYPE_DTS_LBR    == st_mi_info.eAudioCodec)
    {
        pw2s_text = L"DTS Express";
    }
    else if(E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD_MA  == st_mi_info.eAudioCodec)
    {
        pw2s_text = L"DTS-HD MA";
    }
#endif
    else if (i2_val == SCC_AUD_MTS_MONO)
    {
        pw2s_text = L"MONO";
    }
    else if (i2_val == SCC_AUD_MTS_STEREO)
    {
        pw2s_text = L"STEREO";
    }
    c_uc_w2s_strncpy(w2s_str, pw2s_text, z_len);
	free(eDtsVersion);
	free(peCodecType);
    return MENUR_OK;
}

static INT32 _ver_info_get_audio_stream_text(UTF16_T* w2s_str, SIZE_T z_len)
{
    INT32       i4_ret;
	INT32       eRet;
    UTF16_T     w2s_string[65]  = {0};
    UTF16_T*    pw2s_audio_fmt  = NULL;
    ASH_AUDIO_INFO_T t_audio_info;
    SIZE_T      z_len_remain = 64;
    SVL_REC_T   t_svl_rec;
    BOOL        b_found;
    BOOL        b_digital_ch = FALSE;
    UINT8       cast_state = 0;
    UTF16_T     w2s[64] = {0} ;
    ISL_REC_T   t_isl_rec = {0};
    extern UTF16_T* nav_get_audio_fmt_str(ASH_CHANNELS_T e_channels);
    extern UTF16_T* nav_get_audio_mts_str(SCC_AUD_MTS_T e_mts);
	SCC_AUD_IEC_TYPE_T		  e_iec_type;
	MI_AUDIO_DtsVersion_e *eDtsVersion = (MI_AUDIO_DtsVersion_e *)calloc(1, sizeof(MI_AUDIO_DtsVersion_e));

    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    /* Get digital/analog channel */
    menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    //get non-TV source status
    menu_get_crnt_isl(&t_isl_rec);
    if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)       // for vtrl source
    {
		free(eDtsVersion);
        return _ver_info_get_audio_stream_text_in_vtrl(w2s_str, z_len);
    }
    a_icl_custom_get_cast_src_status(&cast_state);
    //DBG_LOG_PRINT(("[Yuhong] %s  %s  (%d) cast_state=(%d) e_video_type=(%x)\n",__FILE__,__FUNCTION__,__LINE__,cast_state,t_isl_rec.t_avc_info.e_video_type));
    if(b_found &&
       (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)&&
       (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI)&&
       (!cast_state || t_isl_rec.t_avc_info.e_video_type !=DEV_VTRL_CAST)&&
       (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_COMBI ||
        t_isl_rec.t_avc_info.e_video_type != DEV_AVC_Y_PB_PR))
    {
        b_digital_ch = TRUE;
    }

	/*get dts version*/
	eRet = MI_AUDIO_GetAttr(0, E_MI_AUDIO_ATTR_TYPE_DTS_VERSION, NULL, eDtsVersion);
	DBG_LOG_PRINT(("[sysinfo] eDtsVersion = %d \n", *eDtsVersion));

    /* get stream num */
    i4_ret = _ver_info_check_tv_mode();
    MENU_CHK_FAIL(i4_ret);

	i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
	MENU_LOG_ON_FAIL(i4_ret);

    if ((b_digital_ch || a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)&&
        (!cast_state || t_isl_rec.t_avc_info.e_video_type !=DEV_VTRL_CAST)&&
        (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status()))
    {
        i4_ret = c_svctx_get_audio_info(menu_get_crnt_svctx(), &t_audio_info);
        if(i4_ret == SVCTXR_OK)
        {
            DBG_LOG_PRINT(("[sysinfo] {%s %s() %d}_audio_info.e_aud_fmt = 0x%x, t_audio_info.e_dec_type = %d\n",__FILE__, __FUNCTION__, __LINE__,t_audio_info.e_aud_fmt,t_audio_info.e_dec_type));

            if (ASH_AUDIO_FMT_AC3 ==  t_audio_info.e_aud_fmt || ASH_AUDIO_FMT_E_AC3 == t_audio_info.e_aud_fmt)
            {
                z_len_remain = c_uc_w2s_strlen(w2s_string);
                c_uc_w2s_strncat(w2s_string, L"Dolby Audio ", 64 - z_len_remain);
            }
            else if((ASH_AUDIO_FMT_AAC == t_audio_info.e_aud_fmt)&&(e_iec_type == SCC_AUD_IEC_CFG_DD))
            {
                c_uc_w2s_strcpy(w2s, L"Dolby Audio ");
                pw2s_audio_fmt = w2s ;
            }
            else if(ASH_DECODE_TYPE_DTS_NORMAL == t_audio_info.e_dec_type)
            {
                c_uc_w2s_strcpy(w2s, L"DTS ");
                pw2s_audio_fmt = w2s ;
            }
            else if(ASH_DECODE_TYPE_DTS_EXPRESS == t_audio_info.e_dec_type)
            {
                if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
                {
                    c_uc_w2s_strcpy(w2s, L"DTS-HD ");
                }
                else
                {
                    c_uc_w2s_strcpy(w2s, L"DTS Express ");
                }
                pw2s_audio_fmt = w2s ;
            }
            else if(ASH_DECODE_TYPE_DTS_HD == t_audio_info.e_dec_type)
            {
                if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
                {
                    c_uc_w2s_strcpy(w2s, L"DTS-HD ");
                }
                else
                {
                    c_uc_w2s_strcpy(w2s, L"DTS-HD Master Audio ");
                }
                pw2s_audio_fmt = w2s ;
            }
            else if(ASH_DECODE_TYPE_DTS_X == t_audio_info.e_dec_type)
            {
                if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
                {
                   c_uc_w2s_strcpy(w2s, L"DTS:X ");
                }
                else
                {
                   c_uc_w2s_strcpy(w2s, L"DTS ");
                }
                pw2s_audio_fmt = w2s ;
            }
            else
            {
                /* Do nothing */
                if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_PCM ||
                t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS ||
                t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_AAC)
                {
                    z_len_remain = c_uc_w2s_strlen(w2s_string);
                    c_uc_w2s_strncat(w2s_string, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_STEREO), 64 - z_len_remain);
                }
            }
        }
    }
    else
    {
        INT16 i2_val = 0;

        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_val);
        pw2s_audio_fmt = nav_get_audio_mts_str((SCC_AUD_MTS_T)i2_val);

        i4_ret = c_svctx_get_audio_info(menu_get_crnt_svctx(), &t_audio_info);
        if(i4_ret != SVCTXR_OK)
        {
            DBG_LOG_PRINT(("[sysinfo] %s,%d get audio info fail \r\n",__FUNCTION__,__LINE__));
        }

        /*get again*/
        i4_ret = c_svctx_get_audio_info(menu_get_crnt_svctx(), &t_audio_info);
        if(i4_ret != SVCTXR_OK)
        {
            DBG_LOG_PRINT(("[sysinfo] %s,%d get audio info fail \r\n",__FUNCTION__,__LINE__));
        }

        DBG_LOG_PRINT(("[sysinfo] {%s %s() %d}. @@HDMI t_audio_info.e_aud_fmt = 0x%x, t_audio_info.e_dec_type = %d,i2_val = %d.\n",__FILE__, __FUNCTION__, __LINE__,t_audio_info.e_aud_fmt,t_audio_info.e_dec_type,i2_val));

        if (ASH_AUDIO_FMT_AC3 ==  t_audio_info.e_aud_fmt
            || ASH_AUDIO_FMT_E_AC3 == t_audio_info.e_aud_fmt
            || ASH_AUDIO_FMT_OPUS  == t_audio_info.e_aud_fmt)//trueHD
        {
            c_uc_w2s_strcpy(w2s, L"Dolby Audio ");
            pw2s_audio_fmt = w2s ;
        }
        else if((ASH_AUDIO_FMT_AAC == t_audio_info.e_aud_fmt)&&(e_iec_type == SCC_AUD_IEC_CFG_DD))
        {
            c_uc_w2s_strcpy(w2s, L"Dolby Audio ");
            pw2s_audio_fmt = w2s ;
        }
        else if(ASH_DECODE_TYPE_DTS_NORMAL == t_audio_info.e_dec_type)
        {
			c_uc_w2s_strcpy(w2s, L"DTS ");
	          pw2s_audio_fmt = w2s ;
        }
        else if(ASH_DECODE_TYPE_DTS_EXPRESS == t_audio_info.e_dec_type)
        {
			if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
			{
				c_uc_w2s_strcpy(w2s, L"DTS-HD ");
			}
			else
			{
				c_uc_w2s_strcpy(w2s, L"DTS Express ");
			}
			pw2s_audio_fmt = w2s ;
			}
        else if(ASH_DECODE_TYPE_DTS_HD == t_audio_info.e_dec_type)
        {
			if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
			{
				c_uc_w2s_strcpy(w2s, L"DTS-HD ");
			}
			else
			{
				c_uc_w2s_strcpy(w2s, L"DTS-HD Master Audio ");
			}
			pw2s_audio_fmt = w2s ;
        }
        else if(ASH_DECODE_TYPE_DTS_X == t_audio_info.e_dec_type)
        {
			if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
			{
				c_uc_w2s_strcpy(w2s, L"DTS:X ");
			}
			else
			{
				c_uc_w2s_strcpy(w2s, L"DTS ");
			}
			pw2s_audio_fmt = w2s ;
        }
        else if((ASH_AUDIO_FMT_DTS == t_audio_info.e_aud_fmt) ||
                (ASH_AUDIO_FMT_DTS_EXPRESS == t_audio_info.e_aud_fmt)||
                (ASH_AUDIO_FMT_DTS_HD == t_audio_info.e_aud_fmt))
        {
            c_uc_w2s_strcpy(w2s, L"DTS-HD ");
            pw2s_audio_fmt = w2s ;
        }
#if 0
        else if((ASH_AUDIO_FMT_DTS_EXPRESS == t_audio_info.e_aud_fmt)&&(e_iec_type == SCC_AUD_IEC_CFG_DD))
		{
            c_uc_w2s_strcpy(w2s, L"DTS Express ");
            pw2s_audio_fmt = w2s ;
		}
        else if((ASH_AUDIO_FMT_DTS_HD == t_audio_info.e_aud_fmt)&&(e_iec_type == SCC_AUD_IEC_CFG_DD))
		{
            c_uc_w2s_strcpy(w2s, L"DTS-HD MA ");
            pw2s_audio_fmt = w2s ;
		}
#endif
        else if (i2_val == SCC_AUD_MTS_MONO)
        {
            c_uc_w2s_strcat (w2s, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_MONO)) ;
            pw2s_audio_fmt = w2s ;
        }
        else if (i2_val == SCC_AUD_MTS_STEREO)
        {
            c_uc_w2s_strcat (w2s, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_STEREO)) ;
            pw2s_audio_fmt = w2s ;
        }

        c_uc_w2s_strncpy(w2s_string, pw2s_audio_fmt, 64);
    }

    if (c_uc_w2s_strlen(w2s_string) == 0)
    {
        c_memset(w2s_string, 0, sizeof(w2s_string));
        c_uc_w2s_strcpy(w2s_string, L" ");
    }
    free(eDtsVersion);
    c_memset(w2s_str, 0, sizeof(UTF16_T)*z_len);
    c_uc_w2s_strncpy(w2s_str, w2s_string, z_len);
    w2s_str[z_len - 1] = 0;
    return MENUR_OK;
}

INT32 menu_ver_info_get_audio_stream_text(CHAR* str_type, SIZE_T z_len)
{
    UTF16_T              w2s_tmp_str[128] = {0};
    INT32           i4_ret;
    i4_ret = _ver_info_get_audio_stream_text(w2s_tmp_str, 127);
    c_uc_w2s_to_ps(w2s_tmp_str, str_type, z_len);
    return i4_ret;
}


#ifdef APP_ULI_UPG_SUPPORT

static UINT8 _ver_info_get_installed_drmp(VOID)
{
	UINT8 ui1_installed = 0;

	if (access("/certificate/drmp/GCast_Cert", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/GCast_key", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/NetFlix", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/WideVine", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/playready25_bgroup_cert", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/playready25_zgpriv", F_OK) == 0)
	{
		ui1_installed++;
	}

	if (access("/certificate/drmp/playready3_cert", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/playread3_key", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/airplay_mfi", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/airplay_fps", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/iot_cert", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/iot_key", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/iot_truststore", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/iotv2_cert", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/iotv2_key", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/vizio_key", F_OK) == 0)
	{
		ui1_installed++;
	}
	if (access("/certificate/drmp/vizio_cert", F_OK) == 0)
	{
		ui1_installed++;
	}
	DBG_LOG_PRINT(("installed drmp %d \n",ui1_installed));
	return ui1_installed;
}

UINT8 menu_ver_info_get_installed_drmp(VOID)
{
    return _ver_info_get_installed_drmp();
}


INT32 menu_ver_info_utv_info_get(MENU_VER_ULI_INFO* pver_uli_info)
{
    CHAR  string_id[16] ={0};
    UINT32 ui4_buff_len = 0;
    UINT8   ui1_ulpk_key_temp[32];
    UINT32  ui4_ulpk_len = 32;
    UINT32  ui4_ulpk_uid_temp = 0;
    UINT8   ui1_installed_drmp = 0;
    CHAR    s_tmp_str_token_d[256] = {0};
    CHAR    s_tmp_str_token_p[256] = {0};
    CHAR*   s_tmp_str;

    ULI_NEW_UPDATE_INFO_T    t_update_info;

    /*** ESN ***/
    a_uli_get_serial_number((UINT8 *)string_id, &ui4_buff_len);
    if (ui4_buff_len == 0)
    {
        c_strcpy((CHAR*)string_id, " N/A");
    }
    c_strcpy(pver_uli_info->str_esn, string_id);

    /*** DA: Device Agent ***/
    a_uli_custom_get_update_info(&t_update_info);
//    DBG_LOG_PRINT(("utv info,line:%d,da:%s.\n",__LINE__,(CHAR*)t_update_info.ps_qda_version));
    if (c_strlen((CHAR*)t_update_info.ps_qda_version) <= 0 || c_strlen((CHAR*)t_update_info.ps_qda_version) >= 32)
    {
        c_strcpy((CHAR*)t_update_info.ps_qda_version, " ");
    }
    c_strcpy(pver_uli_info->str_device_agent, (CHAR*)t_update_info.ps_qda_version);

    /*** UID ***/
    a_uli_get_factory_ulpk_v4(&ui1_ulpk_key_temp, &ui4_ulpk_len, &ui4_ulpk_uid_temp);
    if(ui4_ulpk_uid_temp != 0)
    {
         c_sprintf(pver_uli_info->str_uid, "%d",  ui4_ulpk_uid_temp);
    }
    else
    {
        c_strcpy(pver_uli_info->str_uid, "N/A");
    }

    /*** SV ***/
#if 0
    if (c_strlen((CHAR*)t_update_info.ps_software_version) <= 0 || c_strlen((CHAR*)t_update_info.ps_software_version) >= 32)
    {
        c_strcpy((CHAR*)t_update_info.ps_software_version, " ");
    }
    c_strcpy(pver_uli_info->str_sv, (CHAR*)t_update_info.ps_software_version);
#endif
	s_tmp_str =  sys_cust_get_usb_upg_version();

	c_strcpy(pver_uli_info->str_sv,s_tmp_str);

    /*** DEV ID ***/
    getTokenFromFile("/certificate/PersistentPath", "core_",s_tmp_str_token_d);
    if(s_tmp_str_token_d[0] != 0)
    {
        c_strncpy(pver_uli_info->str_dev_id, (CHAR*)s_tmp_str_token_d, 8);
    }
    else
    {
        c_strcpy(pver_uli_info->str_dev_id, "N/A");
    }

    /*** Prov ID ***/
    getTokenFromFile("/certificate/PersistentPath", "drmp_",s_tmp_str_token_p);
    DBG_LOG_PRINT(("utv info,s_tmp_str_token_d:%s \n",(CHAR*)s_tmp_str_token_p));
    if(s_tmp_str_token_p[0] != 0)
    {
        c_strncpy(pver_uli_info->str_prov_id, (CHAR*)s_tmp_str_token_p, 8);
    }
    else
    {
        c_strcpy(pver_uli_info->str_prov_id, "N/A");
    }

    /*** REG ***/
    if (s_tmp_str_token_p[0] !=0 &&
        s_tmp_str_token_d[0] != 0)
    {
        c_strcpy(pver_uli_info->str_reg, "Yes");
    }
    else
    {
        c_strcpy(pver_uli_info->str_reg, "No");
    }

    /*** NP ***/
    CHAR str_tmp[8] = {0};
    ui1_installed_drmp = _ver_info_get_installed_drmp();
    c_sprintf(str_tmp, "%d",  ui1_installed_drmp);
    c_strcat(pver_uli_info->str_np, str_tmp);
    c_strcat(pver_uli_info->str_np, "/");
    c_sprintf(str_tmp, "%d",  ULI_MAX_AVAIABLE_DRMP);
    c_strcat(pver_uli_info->str_np, str_tmp);

    DBG_LOG_PRINT(("[menu] [%s %d] \n pver_uli_info->str_esn = %s \n pver_uli_info->str_sv = %s \n pver_uli_info->str_reg = %s \n pver_uli_info->str_np = %s \n pver_uli_info->str_uid = %s \n pver_uli_info->str_device_agent = %s \n pver_uli_info->str_dev_id = %s \n pver_uli_info->str_prov_id = %s \n",__FUNCTION__,__LINE__,
        pver_uli_info->str_esn,
        pver_uli_info->str_sv,
        pver_uli_info->str_reg,
        pver_uli_info->str_np,
        pver_uli_info->str_uid,
        pver_uli_info->str_device_agent,
        pver_uli_info->str_dev_id,
        pver_uli_info->str_prov_id));

   return MENUR_OK;
}

static INT32 _ver_info_item_update_uc(VER_INFO_ROWNUM ver_info_row, UTF16_T* w2s_tmp_str)
{
    INT32                       i4_ret = MENUR_OK;
    UTF16_T                     w2s_str[128];

    if (ab_item_show_flag[ver_info_row] == FALSE) return MENUR_OK;
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[ver_info_row],0),
                       w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[ver_info_row],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}


static INT32 _ver_info_item_update(VER_INFO_ROWNUM ver_info_row, CHAR* s_value)
{
    INT32                       i4_ret = MENUR_OK;
    UTF16_T                     w2s_tmp_str[128];

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));

    c_uc_ps_to_w2s(s_value, w2s_tmp_str, c_strlen(s_value));

    i4_ret = _ver_info_item_update_uc(ver_info_row, w2s_tmp_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ver_info_utv_info_update(VOID)
{
    INT32                       i4_ret = MENUR_OK;
    MENU_VER_ULI_INFO           ver_uli_info = {0};

    menu_ver_info_utv_info_get(&ver_uli_info);

    /* ESN */
    i4_ret = _ver_info_item_update(VER_INFO_ROW_UTV_ESN, ver_uli_info.str_esn);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Device Agent */
    i4_ret = _ver_info_item_update(VER_INFO_ROW_UTV_DA, ver_uli_info.str_device_agent);
    MENU_LOG_ON_FAIL(i4_ret);

    /*UID*/
    i4_ret = _ver_info_item_update(VER_INFO_ROW_UTV_UID, ver_uli_info.str_uid);
    MENU_LOG_ON_FAIL(i4_ret);

    /*SV*/
    i4_ret = _ver_info_item_update(VER_INFO_ROW_UTV_SV, ver_uli_info.str_sv);
    MENU_LOG_ON_FAIL(i4_ret);

    /*DEV ID*/
    i4_ret = _ver_info_item_update(VER_INFO_ROW_DEV_ID, ver_uli_info.str_dev_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Prov ID*/
    i4_ret = _ver_info_item_update(VER_INFO_ROW_PROV_ID, ver_uli_info.str_prov_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*REG*/
    i4_ret = _ver_info_item_update(VER_INFO_ROW_UTV_REG, ver_uli_info.str_reg);
    MENU_LOG_ON_FAIL(i4_ret);

    /*NP*/
    i4_ret = _ver_info_item_update(VER_INFO_ROW_UTV_NP, ver_uli_info.str_np);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _ver_info_get_chromium_ver
 *
 * Description:
 *  This function is used to get version of chromium. It will output "N/A"
 *  if can`t get version of chromium
 *
 * Inputs:
 *
 * Outputs:
 *  bin_ver     : version for chromium.
 * Returns:
 ----------------------------------------------------------------------------*/
static void _ver_info_get_chromium_ver(char* bin_ver)
{
    char    ver[64] = {0};

    a_rest_get_conjure_version(ver);
    c_strncpy(bin_ver, ver, c_strlen(ver));
}


static INT32 _lb_ver_info_update_first_elem(VOID)
{
    INT32                       i4_ret = MENUR_OK;
    UTF16_T                     w2s_str[128] = {0};

    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(0,0),
                            w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    if (0 != c_uc_w2s_strcmp(w2s_str, MENU_TEXT(MLM_MENU_KEY_SYS_INFO)))
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_uc_w2s_strcpy(w2s_str, MENU_TEXT(MLM_MENU_KEY_SYS_INFO));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SYSTEM_INFO],0),
                            w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static INT32 _lb_ver_info_update_audio_type(VOID)
{
    UTF16_T              w2s_tmp_str[128] = {0};
    INT32                i4_ret = MENUR_OK;
    UTF16_T              w2s_str[128] = {0};
    const CHAR*          s_tmp_str;
    UINT16               ui2_audio_num;
    ISL_REC_T            t_isl_rec;
    CHAR                 s_name[10] = {0};
    UTF16_T              w2s_tmp2_str[128] = {0};

    MENU_LOG_ON_FAIL(menu_get_crnt_isl(&t_isl_rec));

    i4_ret = c_svctx_get_scdb_num_recs(
                menu_get_crnt_svctx(),
                ST_AUDIO,
                &ui2_audio_num
                );

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (i4_ret < MENUR_OK)
    {
        DBG_LOG_PRINT(("%s,%d, c_svctx_get_scdb_num_recs fail! i4_ret=%d\r\n",__FUNCTION__, __LINE__,i4_ret));
    }

    if (i4_ret == MENUR_OK && (menu_is_signal_loss() || ui2_audio_num == 0) && INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type)
    {
        s_tmp_str = NULL;
        c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));
    }
    else
    {
        _ver_info_get_audio_stream_text(w2s_tmp_str, 127);
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                          WGL_CMD_LB_GET_ITEM_TEXT,
                          WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AUDIO_TYPE_IN],0),
                          w2s_str);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = ver_info_get_audio_type_in(s_name);
    DBG_LOG_PRINT(("[%s][%d] s_name=%s\n", __FUNCTION__, __LINE__,s_name));
    if (c_strlen(s_name) > 0)
    {
        c_uc_ps_to_w2s(s_name,w2s_tmp2_str,c_strlen(s_name));
        c_uc_w2s_strncat(w2s_str,w2s_tmp2_str,c_uc_w2s_strlen(w2s_tmp2_str));
    }
    else
    {
        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
    }

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AUDIO_TYPE_IN],0),
                          w2s_str);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 ver_info_get_hdr_type(CHAR* str_hdr)
{
    UINT8  ui1_type = a_acfg_cust_get_video_type();

    if ( ui1_type == SCC_VID_PQ_DOVI)
    {
        c_strncpy(str_hdr, "Dolby Vision", c_strlen("Dolby Vision"));
    }
    else if ( ui1_type == SCC_VID_PQ_HDR10)
    {
        c_strncpy(str_hdr, "HDR10", c_strlen("HDR10"));
    }
    else if ( ui1_type  == SCC_VID_PQ_HDR10PLUS)
    {
        c_strncpy(str_hdr, "HDR10+", c_strlen("HDR10+"));
    }
    else if ( ui1_type == SCC_VID_PQ_HLG)
    {
        c_strncpy(str_hdr, "HLG", c_strlen("HLG"));
    }
    else
    {
        c_strncpy(str_hdr, "NO", c_strlen("NO"));
    }

    return MENUR_OK;
}

static INT32 _lb_ver_info_update_hdr_type(VOID)
{
    CHAR                 str_hdr[128] = {0};
    UTF16_T              w2s_tmp_str[128] = {0};
    INT32                i4_ret = MENUR_OK;
    UTF16_T              w2s_str[128] = {0};

    i4_ret = ver_info_get_hdr_type(str_hdr);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_ps_to_w2s(str_hdr, w2s_tmp_str, c_strlen(str_hdr));
    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_HDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str, w2s_tmp_str, c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_HDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 menu_ver_info_get_audio_type_out(CHAR* s_audio_type_out)
{
    INT32                i4_ret = MENUR_OK;
    const CHAR*          s_tmp_str;
    SCC_AUD_IEC_TYPE_T   e_iec_type = SCC_AUD_IEC_CFG_NONE ;
    UINT16               ui2_audio_num;
    UINT16               ui2_dig_out;
    ISL_REC_T            t_isl_rec;

    if (s_audio_type_out == NULL)
    {
        return MENUR_FAIL;
    }

    do
    {
        a_cfg_custom_get_digital_audio(&ui2_dig_out);
        if (ui2_dig_out == 1)
        {
            s_tmp_str = " PCM ";
            break;
        }
        else if (ui2_dig_out == 2)
        {
            s_tmp_str = " Bitstream ";
            break;
        }

        i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
        MENU_BREAK_ON_FAIL(i4_ret);

        /*get again*/
        i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
        MENU_BREAK_ON_FAIL(i4_ret);

        switch (e_iec_type)
        {
            case SCC_AUD_IEC_CFG_PCM:    // output mono/stream
            {
                s_tmp_str = " PCM ";
                break;
            }

            case SCC_AUD_IEC_CFG_DD:         // output Dolby DD
            {
                s_tmp_str = " Dolby Audio - DD ";
                break;
            }

            case SCC_AUD_IEC_CFG_DDP:        // output Dolby DD+
            {
                s_tmp_str = " Dolby Audio - DD+ ";
                break;
            }

            case SCC_AUD_IEC_CFG_DDP_ATMOS:  // output Dolby ATMOS
            {
                s_tmp_str = " Dolby Atmos - DD+ ";
                break;
            }

            case SCC_AUD_IEC_CFG_Bitstream:  // not Dolby stream, but channel number more than 2
            {
                s_tmp_str = " Bitstream ";
                break;
            }

            case SCC_AUD_IEC_CFG_DTS:
            {
                s_tmp_str = " DTS-HD ";
                break;
            }

            default:
            {
                s_tmp_str = " PCM ";
                break;
            }
        }
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        s_tmp_str = " ";
    }

    DBG_LOG_PRINT(("{%s %s() %d} \n", __FILE__, __FUNCTION__, __LINE__));
    DBG_LOG_PRINT(("s_tmp_str = %s, e_iec_type = %d, i4_ret = %d\n", s_tmp_str, e_iec_type, i4_ret));

    MENU_LOG_ON_FAIL(menu_get_crnt_isl(&t_isl_rec));
    i4_ret = c_svctx_get_scdb_num_recs(
                menu_get_crnt_svctx(),
                ST_AUDIO,
                &ui2_audio_num
                );
    if (i4_ret < MENUR_OK)
    {
        DBG_LOG_PRINT(("%s,%d, c_svctx_get_scdb_num_recs fail! i4_ret=%d\r\n",__FUNCTION__, __LINE__,i4_ret));
    }
    if (i4_ret == MENUR_OK && (menu_is_signal_loss() || ui2_audio_num == 0) && INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type)
    {
        s_tmp_str = " ";
    }
    c_strncpy(s_audio_type_out, s_tmp_str, c_strlen(s_tmp_str));

    return i4_ret;
}

static INT32 _lb_ver_info_update_audio_type_out(VOID)
{
    UTF16_T              w2s_tmp_str[128] = {0};
    INT32                i4_ret = MENUR_OK;
    UTF16_T              w2s_str[128] = {0};
    const CHAR*          s_tmp_str;
    SCC_AUD_IEC_TYPE_T   e_iec_type = SCC_AUD_IEC_CFG_NONE;
    UINT16               ui2_audio_num;
    UINT16               ui2_dig_out;
    ISL_REC_T            t_isl_rec;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    do
    {
        a_cfg_custom_get_digital_audio(&ui2_dig_out);
        if (ui2_dig_out == 1)
        {
            s_tmp_str = " PCM ";
            break;
        }

        i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
        MENU_BREAK_ON_FAIL(i4_ret);
        /*get again*/
        i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
        MENU_BREAK_ON_FAIL(i4_ret);

        switch(e_iec_type)
        {
            case SCC_AUD_IEC_CFG_PCM:    // output mono/stream
            {
                s_tmp_str = " PCM ";
                break;
            }

            case SCC_AUD_IEC_CFG_DD:         // output Dolby DD
            {
                s_tmp_str = " Dolby Audio - DD ";
                break;
            }

            case SCC_AUD_IEC_CFG_DDP:        // output Dolby DD+
            {
                s_tmp_str = " Dolby Audio - DD+ ";
                break;
            }

            case SCC_AUD_IEC_CFG_MAT:
            {
                s_tmp_str = " Dolby Audio - MAT ";
                break;
            }

            case SCC_AUD_IEC_CFG_TRUEHD:
            {
                s_tmp_str = " Dolby Audio - TrueHD ";
                break;
            }

            case SCC_AUD_IEC_CFG_DDP_ATMOS:  // output Dolby ATMOS
            {
                s_tmp_str = " Dolby Atmos - DD+ ";
                break;
            }

            case SCC_AUD_IEC_CFG_MAT_ATMOS:
            {
                s_tmp_str = " Dolby Atmos - MAT ";
                break;
            }

            case SCC_AUD_IEC_CFG_TRUEHD_ATMOS:
            {
                s_tmp_str = " Dolby Atmos - TrueHD ";
                break;
            }

            case SCC_AUD_IEC_CFG_Bitstream:  // not Dolby stream, but channel number more than 2
            {
                s_tmp_str = " Bitstream ";
                break;
            }

            case SCC_AUD_IEC_CFG_DTS:
            {
                s_tmp_str = " DTS ";
                break;
            }

            case SCC_AUD_IEC_CFG_DTSHD:
            {
                s_tmp_str = " DTS-HD ";
                break;
            }

            case SCC_AUD_IEC_CFG_DTSX:
            {
                s_tmp_str = " DTS:X ";
                break;
            }

            default:
            {
                s_tmp_str = " PCM ";
                break;
            }
        }
    }while(0);

    if (i4_ret != MENUR_OK)
    {
        s_tmp_str = " ";
    }

    DBG_LOG_PRINT(("{%s %s() %d} \n", __FILE__, __FUNCTION__, __LINE__));
    DBG_LOG_PRINT(("s_tmp_str = %s, e_iec_type = %d, i4_ret = %d\n", s_tmp_str, e_iec_type, i4_ret));

    MENU_LOG_ON_FAIL(menu_get_crnt_isl(&t_isl_rec));
    i4_ret = c_svctx_get_scdb_num_recs(
                menu_get_crnt_svctx(),
                ST_AUDIO,
                &ui2_audio_num
                );
    if (i4_ret < MENUR_OK)
    {
        DBG_LOG_PRINT(("%s,%d, c_svctx_get_scdb_num_recs fail! i4_ret=%d\r\n",__FUNCTION__, __LINE__,i4_ret));
    }

    if (i4_ret == MENUR_OK && (menu_is_signal_loss() || ui2_audio_num == 0) && INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type)
    {
        s_tmp_str = " ";
    }

    c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AUDIO_TYPE_OUT],0),
                            w2s_str);
    MENU_CHK_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AUDIO_TYPE_OUT],0),
                            w2s_str);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ver_info_update_apple_tv_ver(VOID)
{
    INT32 i4_ret = 0;
    UTF16_T w2s_version[30] = {0};
    UTF16_T w2s_str[256] = {0};
    CHAR str_version[64] = {0};

    menu_ver_info_apple_tv_ver(str_version, 64);
    c_uc_ps_to_w2s(str_version, w2s_version, c_strlen(str_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_APPLE_TV_VER], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_version, c_uc_w2s_strlen(w2s_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_APPLE_TV_VER], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ver_info_update_hbomax_ver(VOID)
{
    INT32 i4_ret = 0;
    UTF16_T w2s_version[30] = {0};
    UTF16_T w2s_str[256] = {0};
    CHAR str_version[64] = {0};

    menu_ver_info_hbomax_ver(str_version, 64);
    c_uc_ps_to_w2s(str_version, w2s_version, c_strlen(str_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_HBOMAX_VER], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_version, c_uc_w2s_strlen(w2s_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_HBOMAX_VER], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ver_info_update_vizio_ndk_ver(VOID)
{
    INT32 i4_ret = 0;

    UTF16_T w2s_version[30] = {0};
    UTF16_T w2s_str[256] = {0};
    CHAR str_version[64] = {0};

    menu_ver_info_vizio_ndk_ver(str_version, 64);
    c_uc_ps_to_w2s(str_version, w2s_version, c_strlen(str_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_VIZIO_NDK_VER], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_version, c_uc_w2s_strlen(w2s_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_VIZIO_NDK_VER], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _ver_info_update_airplay_internal_ver(VOID)
{
    INT32 i4_ret = 0;
    CHAR str_version[64] = {0};

    MENU_LOG_ON_FAIL(menu_ver_info_airplay_internal_ver(str_version, 64));

    MENU_LOG_ON_FAIL(_ver_info_item_update(VER_INFO_ROW_AIRPLAY_INTERNAL, str_version));

    return i4_ret;
}

static INT32 _ver_info_update_amazon_ver(VOID)
{
    INT32 i4_ret = MENUR_OK;
  #if 0
    UTF16_T w2s_version[30] = {0};
    UTF16_T w2s_str[256] = {0};
    CHAR str_version[30] = {0};

    _ver_info_get_amazon_ver(str_version);
    c_uc_ps_to_w2s(str_version, w2s_version, c_strlen(str_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AMAZON_VER], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_version, c_uc_w2s_strlen(w2s_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AMAZON_VER], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);
  #endif
    return i4_ret;
}

INT32 menu_ver_info_get_vss(CHAR* s_vss)
{
    INT32   i4_ret = MENUR_OK;
    BOOL b_vrr_apply = FALSE;

    if(s_vss == NULL)
    {
        return MENUR_FAIL;
    }

    //a_cfg_cust_drv_get_vrr_status(&b_vrr_apply, 1);
    b_vrr_apply = a_cfg_cust_drv_get_vrr_status();
    DBG_LOG_PRINT(("[%s][%d] b_vrr_apply = %d\n", __FUNCTION__, __LINE__, b_vrr_apply));

    CHAR* str_vrr = b_vrr_apply ? "YES" : "NO";
    c_strncpy(s_vss, str_vrr, c_strlen(str_vrr));

    return i4_ret;
}

static INT32 _ver_info_update_vss(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UTF16_T w2s_vrr[10] = {0};
    UTF16_T w2s_str[256] = {0};
    BOOL b_vrr_apply = FALSE;

    //a_cfg_cust_drv_get_vrr_status(&b_vrr_apply, 1);
    b_vrr_apply = a_cfg_cust_drv_get_vrr_status();
    DBG_LOG_PRINT(("[%s][%d] b_vrr_apply = %d\n", __FUNCTION__, __LINE__, b_vrr_apply));

    CHAR* str_vrr = b_vrr_apply ? "YES" : "NO";

    c_uc_ps_to_w2s(str_vrr, w2s_vrr, c_strlen(str_vrr));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_VRR], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_vrr, c_uc_w2s_strlen(w2s_vrr));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_VRR], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

// used by rest endpoint to get frame rate as the way menu info page does.
FLOAT menu_ver_info_get_vertical_frequency(VOID)
{
    /*Vertical Frequency*/
    INT32           i4_ret = 0;
    VSH_SRC_RESOLUTION_INFO_T     t_res;
    FLOAT fFrameRate;
    UINT16                        ui2_value = 0;
    ISL_REC_T       t_isl_rec;

    c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    if (a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE)
    {
        //a_cfg_cust_drv_get_free_sync_rate(&ui2_value, sizeof(UINT16));
        ui2_value = a_cfg_cust_drv_get_free_sync_rate();
        DBG_LOG_PRINT(("[%s, %d] HDMI freesync_flag:1, free_sync_rate:%d \n", __FUNCTION__, __LINE__, ui2_value ));
        return ((FLOAT)ui2_value);
    }
    else
    {
        DBG_LOG_PRINT(("[%s, %d] HDMI freesync_flag:0\n", __FUNCTION__, __LINE__));
        c_svctx_get_video_src_resolution(get_crnt_svctx(),&t_res);

        DBG_LOG_PRINT(("[%s, %d] INP_SRC_TYPE:%d, ui4_frame_rate:%d\n", __FUNCTION__, __LINE__, t_isl_rec.e_src_type, t_res.ui4_frame_rate ));

        if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)       // for vtrl source
        {
            DBG_LOG_PRINT(("[%s:%d] st_mi_info.MI_U32_FramePerSec %d\n", __FUNCTION__, __LINE__, (int)st_mi_info.MI_U32_FramePerSec));
            t_res.ui4_frame_rate = (st_mi_info.MI_U32_FramePerSec + 500) / 1000;
            DBG_LOG_PRINT(("[%s:%d] t_res.ui4_frame_rate %.2f\n", __FUNCTION__, __LINE__, (FLOAT)t_res.ui4_frame_rate));
            return (FLOAT)t_res.ui4_frame_rate;
        }
        else
        {
           if((t_res.ui4_frame_rate / 1000 ) > 0)
            {
                fFrameRate = (FLOAT)t_res.ui4_frame_rate / 100;
                DBG_LOG_PRINT(("[%s:%d] fFrameRate %.2f\x1b[0m\n", __FUNCTION__, __LINE__, fFrameRate));
                return fFrameRate;
            }
            else
            {
                DBG_LOG_PRINT(("[%s:%d] s_buf %.2f\x1b[0m\n", __FUNCTION__, __LINE__, t_res.ui4_frame_rate));
                return t_res.ui4_frame_rate;
            }
        }
    }

    return 0;
}


static INT32 _ver_info_update_free_sync_rate(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UTF16_T w2s_value[10] = {0};
    UTF16_T w2s_str[256] = {0};
    UTF16_T* w2s_prefix = L"  ";
    UINT16  ui2_value = 0;
    CHAR    s_value[32];

    if (a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE)
    {
        //a_cfg_cust_drv_get_free_sync_rate(&ui2_value, sizeof(UINT16));
        ui2_value = a_cfg_cust_drv_get_free_sync_rate();

        sprintf(s_value, "  %u", ui2_value);
        c_uc_ps_to_w2s(s_value, w2s_value, c_strlen(s_value));

        c_uc_w2s_strcat(w2s_str, w2s_prefix);
        c_uc_w2s_strcat(w2s_str, MENU_TEXT(t_g_ver_items[VER_INFO_ROW_VFREQ].ui2_mlm_idx));
        c_uc_w2s_strncat(w2s_str, w2s_value, c_uc_w2s_strlen(w2s_value));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_VFREQ], 0),
                                w2s_str);

        MENU_LOG_ON_FAIL(i4_ret);

        return i4_ret;
    }
    else
    {
        // do nothing if not freesync case.
        return i4_ret;
    }
}


static INT32 _ver_info_update_frc_version(VOID)
{
    INT32   i4_ret = MENUR_OK;
  #if 0
    UTF16_T w2s_vrr[10] = {0};
    UTF16_T w2s_str[256] = {0};
    UINT32  ui4_frc_version;
    CHAR    s_frc_version[32];
    if (ab_item_show_flag[VER_INFO_ROW_FRC_VER] == FALSE)
    {
        return i4_ret;
    }
    a_cfg_cust_drv_get_frc_version(&ui4_frc_version, 4);

    sprintf(s_frc_version, "%d", ui4_frc_version);
    c_uc_ps_to_w2s(s_frc_version, w2s_vrr, c_strlen(s_frc_version));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_FRC_VER], 0),
                            w2s_str);

    c_uc_w2s_strncat(w2s_str, w2s_vrr, c_uc_w2s_strlen(w2s_vrr));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_FRC_VER], 0),
                            w2s_str);

    MENU_LOG_ON_FAIL(i4_ret);
  #endif
    return i4_ret;
}

INT32 menu_ver_info_get_resolution(CHAR* res_str)
{
    INT32 i4_ret = MENUR_OK;
    ISL_REC_T t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T t_res;
    BOOL         b_interlace             = FALSE;

    c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("[sysinfo] Source t_isl_rec.e_src_type:%d \n\r", t_isl_rec.e_src_type));

    if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)		 // for vtrl source
    {
        MENU_LOG_ON_FAIL(a_cfg_mi_mm_querry_ex(&st_mi_info, &b_interlace));

        if (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)//for APK cast
        {
            DBG_LOG_PRINT(("[sysinfo] Cast source t_res.ui4_height:%d b_interlace= %d\n\r",st_mi_info.MI_U32_MovieHeight, b_interlace));

            if (st_mi_info.MI_U32_MovieHeight > VIDEO_HEIGHT_1440)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 2160);
            }
			else if (st_mi_info.MI_U32_MovieHeight > VIDEO_HEIGHT_1080)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 1440);
            }
            else if (st_mi_info.MI_U32_MovieHeight > VIDEO_HEIGHT_720)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 1080);
            }
            else if (st_mi_info.MI_U32_MovieHeight > VIDEO_HEIGHT_480)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 720);
            }
            else if (st_mi_info.MI_U32_MovieHeight > 0)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 480);
            }
        }
        else
        {
            if(st_mi_info.MI_U32_MovieHeight != 0  &&
                st_mi_info.MI_U32_MovieWidth != 0)
            {
                c_sprintf(res_str, "%d X %d", st_mi_info.MI_U32_MovieWidth, st_mi_info.MI_U32_MovieHeight) ;
            }
        }
    }
    else
    {
        c_svctx_get_video_src_resolution(get_crnt_svctx(),&t_res);
        b_interlace = !t_res.b_is_progressive;

        DBG_LOG_PRINT(("[sysinfo] Source width: %d, height: %d, %s \n\r",
                        t_res.ui4_width, t_res.ui4_height, ((b_interlace)?("interlace"):("progressive"))));
        DBG_LOG_PRINT(("[sysinfo] timing_type is %d \n", t_res.e_timing_type));

        if (t_res.e_timing_type == VSH_SRC_TIMING_VIDEO)
        {
        #if 1
            if (t_res.ui4_height == VIDEO_HEIGHT_2160)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 2160);
            }
            else if (t_res.ui4_height == VIDEO_HEIGHT_1440)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 1440);
            }
            else if (t_res.ui4_height == VIDEO_HEIGHT_1080)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 1080);
            }
            else if (t_res.ui4_height == VIDEO_HEIGHT_720)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 720);
            }
            else if (t_res.ui4_height == VIDEO_HEIGHT_480)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 480);
            }
            else if (t_res.ui4_height > 0) //See jira MVV-7092 for the reason for the modification
            {
                c_sprintf (res_str, "%d X %d", t_res.ui4_width, t_res.ui4_height);
            }
        #else
            if (t_res.ui4_height > VIDEO_HEIGHT_1440)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 2160);
            }
			else if (t_res.ui4_height > VIDEO_HEIGHT_1080)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 1440);
            }
            else if (t_res.ui4_height > VIDEO_HEIGHT_720)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 1080);
            }
            else if (t_res.ui4_height > VIDEO_HEIGHT_576)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 720);
            }
            else if (t_res.ui4_height == VIDEO_HEIGHT_480)
            {
                c_sprintf(res_str, b_interlace ? "%di" : "%dp", 480);
            }
			else if(t_res.ui4_height > 0)//See jira MVV-7092 for the reason for the modification
			{
				c_sprintf (res_str, "%d X %d", t_res.ui4_width,t_res.ui4_height);
			}
        #endif
        }
        else
        {
            DBG_LOG_PRINT(("[sysinfo] timing_type is VSH_SRC_TIMING_GRAPHIC \n"));
            if (t_res.ui4_height > 0)
            {
                 c_sprintf (res_str, "%d X %d", t_res.ui4_width,t_res.ui4_height);
            }
        }
    }

    if (c_strlen(res_str) == 0)
    {
        c_strcpy(res_str, "N/A");
    }

    return i4_ret;

}

INT32 menu_ver_info_get_frame_rate(CHAR* frm_rt_str)
{
    VSH_SRC_RESOLUTION_INFO_T     t_res;
    FLOAT                         f_frame_rate = 0;
    CHAR                          s_buf[32];
    UINT16                        ui2_value = 0;
    UTF16_T                       w2s_str[128] = {0};
    ISL_REC_T                     t_isl_rec;

    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    menu_get_crnt_isl(&t_isl_rec);


    if (a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE)
    {
        //a_cfg_cust_drv_get_free_sync_rate(&ui2_value, sizeof(UINT16));
        ui2_value = a_cfg_cust_drv_get_free_sync_rate();
        DBG_LOG_PRINT(("[sysinfo] HDMI freesync_flag:1, free_sync_rate:%d \n", ui2_value ));

        c_sprintf(s_buf, "  %u", ui2_value);
    }
    else
    {
        DBG_LOG_PRINT(("[sysinfo] HDMI freesync_flag:0\n" ));
        c_svctx_get_video_src_resolution(get_crnt_svctx(),&t_res);

        DBG_LOG_PRINT(("[sysinfo] INP_SRC_TYPE:%d, ui4_frame_rate:%d\n", t_isl_rec.e_src_type, t_res.ui4_frame_rate ));

        if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)       // for vtrl source
        {
            DBG_LOG_PRINT(("[sysinfo] st_mi_info.MI_U32_FramePerSec: %d \n", st_mi_info.MI_U32_FramePerSec ));

            t_res.ui4_frame_rate = (st_mi_info.MI_U32_FramePerSec + 500) / 1000;
            if (t_res.ui4_frame_rate == 0)
            {
                c_strcpy(s_buf, "N/A");
            }
            else
            {
                c_sprintf(s_buf, "%d", t_res.ui4_frame_rate);
            }
         }
         else
         {
            if((t_res.ui4_frame_rate / 1000 ) > 0)
            {
                f_frame_rate = (FLOAT)t_res.ui4_frame_rate / 100;
                c_sprintf(s_buf, "%.2f",  f_frame_rate);
            }
            else
            {
                c_sprintf(s_buf, "%d", t_res.ui4_frame_rate);
            }
        }
    }

    c_strcpy(frm_rt_str, s_buf);
    return MENUR_OK;
}

INT32 menu_ver_info_get_audio_out(CHAR* aud_ot_str)
{
    UTF16_T              w2s_tmp_str[128] = {0};
    INT32                i4_ret = MENUR_OK;
    UTF16_T              w2s_str[128] = {0};
    const CHAR*          s_tmp_str;
    SCC_AUD_IEC_TYPE_T   e_iec_type = SCC_AUD_IEC_CFG_NONE;
    UINT16               ui2_audio_num;
    UINT16               ui2_dig_out;
    ISL_REC_T            t_isl_rec;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    do
    {
        a_cfg_custom_get_digital_audio(&ui2_dig_out);
        if (ui2_dig_out == 1)
        {
            s_tmp_str = " PCM ";
            break;
        }

        i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
        MENU_BREAK_ON_FAIL(i4_ret);
        /*get again*/
        i4_ret = _ver_info_get_scc_audio_type_out(&e_iec_type);
        MENU_BREAK_ON_FAIL(i4_ret);

        switch(e_iec_type)
        {
            case SCC_AUD_IEC_CFG_PCM:    // output mono/stream
            {
                s_tmp_str = " PCM ";
                break;
            }

            case SCC_AUD_IEC_CFG_DD:         // output Dolby DD
            {
                s_tmp_str = " Dolby Audio - DD ";
                break;
            }

            case SCC_AUD_IEC_CFG_DDP:        // output Dolby DD+
            {
                s_tmp_str = " Dolby Audio - DD+ ";
                break;
            }

            case SCC_AUD_IEC_CFG_MAT:
            {
                s_tmp_str = " Dolby Audio - MAT ";
                break;
            }

            case SCC_AUD_IEC_CFG_TRUEHD:
            {
                s_tmp_str = " Dolby Audio - TrueHD ";
                break;
            }

            case SCC_AUD_IEC_CFG_DDP_ATMOS:  // output Dolby ATMOS
            {
                s_tmp_str = " Dolby Atmos - DD+ ";
                break;
            }

            case SCC_AUD_IEC_CFG_MAT_ATMOS:
            {
                s_tmp_str = " Dolby Atmos - MAT ";
                break;
            }

            case SCC_AUD_IEC_CFG_TRUEHD_ATMOS:
            {
                s_tmp_str = " Dolby Atmos - TrueHD ";
                break;
            }

            case SCC_AUD_IEC_CFG_Bitstream:  // not Dolby stream, but channel number more than 2
            {
                s_tmp_str = " Bitstream ";
                break;
            }

            case SCC_AUD_IEC_CFG_DTS:
            {
                s_tmp_str = " DTS ";
                break;
            }

            case SCC_AUD_IEC_CFG_DTSHD:
            {
                s_tmp_str = " DTS-HD ";
                break;
            }

            case SCC_AUD_IEC_CFG_DTSX:
            {
                s_tmp_str = " DTS:X ";
                break;
            }

            default:
            {
                s_tmp_str = " PCM ";
                break;
            }
        }
    }while(0);

    if (i4_ret != MENUR_OK)
    {
        s_tmp_str = " ";
    }

    DBG_LOG_PRINT(("{%s %s() %d} \n", __FILE__, __FUNCTION__, __LINE__));
    DBG_LOG_PRINT(("s_tmp_str = %s, e_iec_type = %d, i4_ret = %d\n", s_tmp_str, e_iec_type, i4_ret));

    c_strcpy(aud_ot_str, s_tmp_str);

    return MENUR_OK;
}

static VOID _lb_ver_info_update_data_thread_main (VOID* pv_arg)
{
    /*----------------------------------Channel Info------------------------------------*/

     _ver_info_ch_info_update();

#ifdef MT5695L_MODEL // MVR-162
    /*------------------------------------Camera-------------------------------------*/
    _ver_info_camera_info_update();
#endif

    /*------------------------------------Network-------------------------------------*/

    _ver_info_nw_info_update();

    /*-------------------------------------UTV----------------------------------------*/
#ifdef APP_ULI_UPG_SUPPORT

    _ver_info_utv_info_update();
#endif


    MENU_LOG_ON_FAIL(_ver_info_remote_info_update());

    MENU_LOG_ON_FAIL(_ver_info_binaries_version_update());

    MENU_LOG_ON_FAIL(_ver_info_sc_config_update());

}


static INT32 _lb_ver_info_update_data_async(VOID)
{
    /*Create thread to get nw dev info,because it will cost some time(5s).*/
    HANDLE_T                h_thread;
    if (x_thread_create(& h_thread,
                        "_lb_ver_info_update_data_async",
                        8192,
                        127,
                        _lb_ver_info_update_data_thread_main,
                        0,
                        NULL)
        != OSR_OK)
    {
        DBG_ERROR(("create thread failed:_lb_ver_info_update_data_async\n"));
        return MENUR_FAIL;
    }

    return MENUR_OK;
}


static INT32 _lb_ver_info_update_data(VOID)
{
    INT32           i4_ret = APP_CFGR_OK;
    const CHAR*     s_tmp_str;
    UTF16_T         w2s_tmp_str[128] = {0};
    UTF16_T         w2s_str[128] = {0};
    UTF16_T         w2s_sn[128] = {0};
    CHAR            s_model_name[32] = {0};
    CHAR            string[64] = "1234";
    CHAR            s_vtrl_name[24] = {0};
    ISL_REC_T       t_isl_rec;

    /*----------------------------System Information---------------------------*/

    //*****
    //***** TV Name *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_CAST_NAME] == TRUE)
    {
        CHAR    s_tv_name[MAX_TV_NAME_LEN+1] = {0};
        UINT32                       ui4_len = MAX_TV_NAME_LEN;

        i4_ret = a_cfg_custom_get_tv_name(s_tv_name,&ui4_len);
        DBG_LOG_PRINT (("\n [%s][%d] s_tv_name[%s], ui4_len[%d]\n", s_tv_name, ui4_len));

        c_uc_ps_to_w2s(s_tv_name, w2s_tmp_str, c_strlen(s_tv_name));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CAST_NAME],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CAST_NAME],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** Serial Number *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_SN] == TRUE)
    {
    #ifdef APP_ULI_UPG_SUPPORT
        UINT32  ui4_buff_len = 64;
        CHAR    str_sn[64] = {0};
        UINT32  ui4_digs_len = 0;

        c_memset(string, 0, sizeof(string));

        i4_ret = a_uli_get_serial_number((UINT8 *)str_sn, &ui4_buff_len);
        MENU_LOG_ON_FAIL(i4_ret);

        if (ui4_buff_len < 15)
        {
            c_strncpy(string, str_sn + 2, 2);
            c_strncat(string, str_sn, 2);
            c_strncat(string, str_sn + 6, 2);
            c_strncat(string, str_sn + 4, 2);
            c_strncat(string, str_sn + 8, 5);

            ui4_digs_len = c_strlen(string);
            c_strcat(string, str_sn + ui4_digs_len);
        }
        else
        {
            c_strncpy(string, str_sn + 8, 2);
            c_strncat(string, str_sn, 8);

            ui4_digs_len = c_strlen(string);
            c_strcat(string, str_sn + ui4_digs_len);
        }
    #endif

        if ((i4_ret != 0) || (0 == strcmp(string,"")))
        {
            c_strncpy(string,"N/A", strlen("N/A"));
          #if 0
            if(0==strcmp(string,""))
            {
                DBG_LOG_PRINT(("RJ45 MAC\n\r"));
                a_nw_get_mac_addr_string((CHAR*)NI_ETHERNET_0, string);
            }
            else
            {
                a_nw_get_mac_addr_string((CHAR*)NI_WIRELESS_0, string);
                DBG_LOG_PRINT(("WIFI MAC\n\r"));
            }
          #endif
        }

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SN],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_ps_to_w2s(string, w2s_sn, c_strlen(string));

        c_uc_w2s_strncat(w2s_str,w2s_sn,c_uc_w2s_strlen(w2s_sn));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SN],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** Model Name *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_MODEL] == TRUE)
    {
        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));

    #ifndef APP_CUST_PLT_OPT
        if (a_app_cust_plt_opt())
    #endif
        {
            a_cfg_custom_get_model_name(s_model_name);
        }
        c_uc_ps_to_w2s(s_model_name,w2s_tmp_str,c_strlen(s_model_name));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_MODEL],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_MODEL],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** SW Version *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_SW_VER] == TRUE)
    {
        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));
        s_tmp_str = sys_cust_get_usb_upg_version();
        c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SW_VER],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SW_VER],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** SCPL Version *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_SCPL] == TRUE)
    {
        CHAR version[128] = {0};

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));

        a_rest_get_Rest_Version(version);
        DBG_LOG_PRINT(("rest vision:%s \n",version));
        if(version[0]!= 0)
        {
            c_uc_ps_to_w2s(version,w2s_tmp_str,c_strlen(version));
        }
        else
        {
            c_uc_ps_to_w2s("N/A",w2s_tmp_str,12);
        }
        MENU_LOG_ON_FAIL(_ver_info_item_update_uc(VER_INFO_ROW_SCPL, w2s_tmp_str));
    }

    //*****
    //***** AirPlay Version *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_AIRPLAY_VER] == TRUE)
    {
        char res_buf[1024] = {0};

        c_memset(res_buf, 0, 1024);
        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));

        a_rest_app_get_info_from_airplay("sdkBuildVersion", (void *)res_buf);
        c_strncpy(s_airplay_version, res_buf, 12);
        DBG_LOG_PRINT(("airplay version:%s \n", s_airplay_version));

        if (s_airplay_version[0] != 0)
        {
            c_uc_ps_to_w2s(s_airplay_version, w2s_tmp_str, 12);
        }
        else
        {
            c_uc_ps_to_w2s("N/A", w2s_tmp_str, 12);
        }

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                              WGL_CMD_LB_GET_ITEM_TEXT,
                              WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AIRPLAY_VER],0),
                              w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_AIRPLAY_VER],0),
                              w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** Chromium Version *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_CHROMIUM_VER]  == TRUE)
    {
        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));

        char    chromium_ver[24];
        c_memset(chromium_ver, 0, sizeof(chromium_ver));
        _ver_info_get_chromium_ver(chromium_ver);
        c_uc_ps_to_w2s(chromium_ver, w2s_tmp_str, sizeof(chromium_ver));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CHROMIUM_VER], 0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
        c_uc_w2s_strncat(w2s_str, w2s_tmp_str, c_uc_w2s_strlen(w2s_tmp_str));
        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CHROMIUM_VER], 0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** Cast Version *****
    //*****
    {
        CHAR     ver_string[64]                 = {'0'};
        CHAR     dlm_ver_string[25]             = {'0'}; // e.g. MTKC-105.222.303.897
        CHAR     int_ver_string[35]             = {'0'}; // e.g. castlite_20210806_0600_RC03
        CHAR     separator[]                    = " | ";
        UINT32   ui4_cast_builder_name_len      = 64;

        c_memset(w2s_tmp_str,    0, sizeof(w2s_tmp_str));
        c_memset(w2s_str,        0, sizeof(w2s_str));

        FILE* fp_dlm = fopen("/data/app/castshell/VERSION", "r");
        if (fp_dlm)
        {
            UINT32 dlm_len = fread(dlm_ver_string, sizeof(CHAR), sizeof(dlm_ver_string), fp_dlm);
            fclose(fp_dlm);

            if (dlm_len > 0)
            {
                FILE* fp_int = fopen("/data/app/castshell/VERSION_internal", "r");
                if (fp_int)
                {
                    UINT32 int_len = fread(int_ver_string, sizeof(CHAR), sizeof(int_ver_string), fp_int);
                    fclose(fp_int);

                    if (int_len > 0)
                    {
                        // remove redundant \n character after fread()
                        dlm_ver_string[c_strlen(dlm_ver_string) - 1] = 0;
                        int_ver_string[c_strlen(int_ver_string) - 1] = 0;

                        c_strncpy(ver_string, dlm_ver_string, c_strlen(dlm_ver_string));
                        c_strncat(ver_string, separator, c_strlen(separator));
                        c_strncat(ver_string, int_ver_string, c_strlen(int_ver_string));
                    }
                }
            }
        }

        if (strncmp(ver_string, "0", strlen(ver_string)) == 0)
        {
            a_c4tv_apron_get_cast_builder_name(ver_string, &ui4_cast_builder_name_len);
        }

        c_uc_ps_to_w2s(ver_string,w2s_tmp_str,c_strlen(ver_string));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CAST_VER],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_CAST_VER],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** Source Type *****
    //*****
    SVL_REC_T   t_svl_rec;
    BOOL        b_found;
    UINT8       cast_state = 0;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    MENU_LOG_ON_FAIL(i4_ret);

    a_icl_custom_get_cast_src_status(&cast_state);

    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        s_tmp_str = "MMP";
    }
    else if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
    {
        if (b_found && BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
        {
            /*DTV*/
            s_tmp_str = "DTV";
        }
        else
        {
            /*ATV*/
            s_tmp_str = "ATV";
        }
    }
    else if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type)
    {
        switch(t_isl_rec.t_avc_info.e_video_type)
        {
            case DEV_AVC_S_VIDEO:
            /*case DEV_AVC_COMBI:*/
                /*AV*/
                s_tmp_str = "AV";
                break;
            case DEV_AVC_COMP_VIDEO:
            case DEV_AVC_COMBI:
            case DEV_AVC_Y_PB_PR:
                /*Composite*/
                s_tmp_str = "Composite";
                break;
            case DEV_AVC_DVI:
                /*DVI*/
                s_tmp_str = "DVI";
                break;
            case DEV_AVC_HDMI:
                /*HDMI*/
                s_tmp_str = "HDMI";
                break;
            case DEV_AVC_VGA:
                /*RGB*/
                s_tmp_str = "RGB";
                break;
            default:
                s_tmp_str = "AV";
                break;
        }
    }
    else if (cast_state || DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
        if(t_isl_rec.ui1_internal_id == 0)
        {
            s_tmp_str = "SMARTCAST";
        }
        else
        {
            a_isl_get_vtrl_input_display_name(&t_isl_rec,s_vtrl_name);

        }
    }
    else if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {

    }

    if ((DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)&&(t_isl_rec.ui1_internal_id > 0))
    {
        c_uc_ps_to_w2s(s_vtrl_name,w2s_tmp_str,c_strlen(s_vtrl_name));
    }
    else
    {
        c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));
    }
    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SOURCE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_SOURCE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    //*****
    //***** Resolution *****
    //*****
    {
        char   res_str[64] = {'\0'};

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));

        menu_ver_info_get_resolution(res_str);
        c_uc_ps_to_w2s(res_str, w2s_tmp_str, c_strlen(res_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RESOLUTION],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RESOLUTION],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** Vertical Frequency *****
    //*****
    {
        VSH_SRC_RESOLUTION_INFO_T     t_res;
        FLOAT                         f_frame_rate = 0;
        CHAR                          s_buf[32];
        UINT16                        ui2_value = 0;

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

        if (a_acfg_cust_is_detect_hdmi_freesync_flag() == TRUE)
        {
            //a_cfg_cust_drv_get_free_sync_rate(&ui2_value, sizeof(UINT16));
            ui2_value = a_cfg_cust_drv_get_free_sync_rate();
            DBG_LOG_PRINT(("[sysinfo] HDMI freesync_flag:1, free_sync_rate:%d \n", ui2_value ));

            sprintf(s_buf, "  %u", ui2_value);
            c_uc_ps_to_w2s(s_buf, w2s_tmp_str, c_strlen(s_buf));
        }
        else
        {
            DBG_LOG_PRINT(("[sysinfo] HDMI freesync_flag:0\n" ));
            c_svctx_get_video_src_resolution(get_crnt_svctx(),&t_res);

            DBG_LOG_PRINT(("[sysinfo] INP_SRC_TYPE:%d, ui4_frame_rate:%d\n", t_isl_rec.e_src_type, t_res.ui4_frame_rate ));

            if (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type)       // for vtrl source
            {
                DBG_LOG_PRINT(("[sysinfo] st_mi_info.MI_U32_FramePerSec: %d \n", st_mi_info.MI_U32_FramePerSec ));

                t_res.ui4_frame_rate = (st_mi_info.MI_U32_FramePerSec + 500) / 1000;
                if (t_res.ui4_frame_rate == 0)
                {
                    c_strcpy(s_buf, "N/A");
                }
                else
                {
                    c_sprintf(s_buf, "%d", t_res.ui4_frame_rate);
                }
                c_uc_ps_to_w2s(s_buf, w2s_tmp_str, 6);
             }
             else
             {
                if((t_res.ui4_frame_rate / 1000 ) > 0)
                {
                    f_frame_rate = (FLOAT)t_res.ui4_frame_rate / 100;
                    c_sprintf(s_buf, "%.2f",  f_frame_rate);
                    c_uc_ps_to_w2s(s_buf, w2s_tmp_str, 6);
                }
                else
                {
                    c_sprintf(s_buf, "%d", t_res.ui4_frame_rate);
                    c_uc_ps_to_w2s(s_buf, w2s_tmp_str, 6);
                }
            }
        }

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_VFREQ],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str, w2s_tmp_str, c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_VFREQ],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        // Print ALLM status at HDMI for debug...
        if( INP_SRC_TYPE_AV == t_isl_rec.e_src_type )
        {
            DBG_LOG_PRINT(("[sysinfo][ALLM] INP_SRC_TYPE:%d, ALLM_flag:%d\n", t_isl_rec.e_src_type, a_cfg_cust_drv_get_allm_status() ));
        }
    }

    //*****
    //***** Audio In *****
    //*****
    i4_ret = _lb_ver_info_update_audio_type();
    MENU_LOG_ON_FAIL(i4_ret);

    //*****
    //***** Audio Out *****
    //*****
    i4_ret = _lb_ver_info_update_audio_type_out();
    MENU_LOG_ON_FAIL(i4_ret);

    //*****
    //***** HDR *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_HDR] == TRUE)
    {
        i4_ret = _lb_ver_info_update_hdr_type();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    _ver_info_update_amazon_ver();
    MENU_LOG_ON_FAIL(_ver_info_update_airplay_internal_ver());
    MENU_LOG_ON_FAIL(_ver_info_update_apple_tv_ver());
    MENU_LOG_ON_FAIL(_ver_info_update_hbomax_ver());
    MENU_LOG_ON_FAIL(_ver_info_update_vizio_ndk_ver());

    //*****
    //***** VSS *****
    //*****
    if (ab_item_show_flag[VER_INFO_ROW_VRR] == TRUE)
    {
        i4_ret = _ver_info_update_vss();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    //*****
    //***** Netflix *****
    //*****
    i4_ret = _ver_info_netflix_info_update();
    MENU_LOG_ON_FAIL(i4_ret);

    //*****
    //***** Country *****
    //*****
    i4_ret = _ver_info_country_update();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ver_info_accumulated_operating_hours_update();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ver_info_update_frc_version();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ver_info_update_free_sync_rate();
    MENU_LOG_ON_FAIL(i4_ret);

    //*****
    //***** Bluetooth *****
    //*****
    i4_ret = _ver_info_bluetooth_version_update();
    MENU_LOG_ON_FAIL(i4_ret);


//    _lb_ver_info_update_first_elem();

    if (b_async_flag)
    {
        _lb_ver_info_update_data_async();
        b_async_flag = FALSE;
    }
    else
    {
        _lb_ver_info_update_data_thread_main(NULL);
    }

    return MENUR_OK;
}

static INT32 _ver_info_update_arrow_state(UINT32 ui4_keycode)
{
    INT32   i4_ret = MENUR_OK;
    UINT32  ui4_hlt_idx = 0;
    UINT16  ui2_tmp = 0;

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui4_hlt_idx),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_tmp = (UINT32)ui4_hlt_idx;

    if (BTN_CURSOR_UP == ui4_keycode || BTN_PRG_UP == ui4_keycode)
    {
        if (ui2_tmp <= a_g_ver_info_idx[VER_INFO_ROW_SYSTEM_INFO] + 1) /*Cursor will get to the first item*/
        {
            c_wgl_show(h_arrow_up,WGL_SW_HIDE);
        }
        if (ui2_tmp <= a_g_ver_info_idx[VER_INFO_ROW_LAST_NUM] - COMMON_VER_INOF_ELEM_NUM) /*Cursor will get to the last 12th item*/
        {
            c_wgl_show(h_arrow_down,WGL_SW_NORMAL);
        }
    }
    if (BTN_CURSOR_DOWN == ui4_keycode || BTN_PRG_DOWN == ui4_keycode)
    {
        if (ui2_tmp >= a_g_ver_info_idx[VER_INFO_ROW_LAST_NUM] - 2) /*Cursor will get to the last item after cursor down*/
        {
            c_wgl_show(h_arrow_down,WGL_SW_HIDE);
        }
        if (ui2_tmp >= a_g_ver_info_idx[VER_INFO_ROW_SYSTEM_INFO] + COMMON_VER_INOF_ELEM_NUM - 1) /*Cursor will get to the 12th item after cursor down*/
        {
            c_wgl_show(h_arrow_up,WGL_SW_NORMAL);
        }
    }

    return MENUR_OK;
}

static INT32 _ver_info_backbar_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    if(WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32      ui4_keycode = (UINT32)param1;
        HANDLE_T    h_homebar = NULL_HANDLE;
        HANDLE_T    h_backbar = NULL_HANDLE;

        menu_get_homebar_handle(&h_homebar);
        menu_get_backbar_handle(&h_backbar);

        switch(ui4_keycode)
        {
            case BTN_SELECT:
                if(h_widget == h_backbar)
                {
                    menu_nav_back();
                }
                if(h_widget == h_homebar)
                {
                    menu_nav_go_home_menu();
                }
                break;
            case BTN_RETURN:
                menu_nav_back();
                break;
            case BTN_CURSOR_UP:
                if(h_widget == h_backbar)
                {
                    menu_set_focus_on_homebar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
                }
                if(h_widget == h_homebar)
                {
                    /*Do nothing*/
                }
                break;
            case BTN_CURSOR_DOWN:
                if(h_widget == h_backbar)
                {
                    c_wgl_do_cmd (h_lb_ver_info,
                                    WGL_CMD_LB_HLT_ELEM,
                                    WGL_PACK(0),
                                    NULL);
                    c_wgl_set_focus(h_lb_ver_info,WGL_SYNC_AUTO_REPAINT);
                #ifndef APP_SYS_INFO_SP6_SUPPORT
                    if (a_cfg_custom_get_wifi_remote_support())
                    {
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_SYSTEM_INFO));
                    }
                    else
                #endif
                    {
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_SYSTEM_INFO_NO_REMOTE));
                    }
                    menu_hide_help_tip();
                }
                if(h_widget == h_homebar)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                }
                break;
            case BTN_CURSOR_LEFT:
                #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                    return MENUR_OK;
                #endif
                menu_nav_back();
                break;
            default:
                break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _ver_info_widget_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ver_info_widget_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    UINT32      ui4_keycode = (UINT32)param1;
#ifdef APP_TTS_SUPPORT
    UTF16_T     w2s_str[128+1] = {0};
    CHAR        info_srting[128+1] = {0};
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8           ui1_input_id = 0;
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
#endif


    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32      ui4_hlt_idx = 0;
        UINT32      ui4_ele_num = 0;
        UINT16      ui2_tmp = 0;

        /*reset timer first */
        _ver_info_reset_timer();

        switch (ui4_keycode)
        {
        /************************************
        Add feature that channel +/- can page +/-. detail see MVP-3127/MVD-782/MVV-7159. What i do is following:
        1.the following  two case statements.
        2.forbit that BTN_PRG_UP/BTN_PRG_DOWN can change channel when sysinfo page is show in file menu_custom.c
        *************************************/
        case BTN_PRG_UP:
        {
            UINT32           new_hlt = 0;
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui4_hlt_idx),
                            NULL);
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ELEM_NUM,
                            WGL_PACK(&ui4_ele_num),
                            NULL);                      //due to eletment numbers is not sure,so get current ELEM_NUM

            if(ui4_ele_num <= 61)                      //three pages
            {
                if(ui4_hlt_idx > COMMON_VER_INOF_ELEM_NUM + 9)
                {
                    new_hlt = COMMON_VER_INOF_ELEM_NUM + 9;
                }
                else if(ui4_hlt_idx >= 0)
                {
                    new_hlt = 0;
                }
            }
            else                                         //four pages
            {
                if(ui4_hlt_idx > COMMON_VER_INOF_ELEM_NUM * 2 + 8 )
                {
                    new_hlt = COMMON_VER_INOF_ELEM_NUM * 2 + 8;
                }
                else if(ui4_hlt_idx > COMMON_VER_INOF_ELEM_NUM + 9)
                {
                    new_hlt = COMMON_VER_INOF_ELEM_NUM + 9;
                }
                else if(ui4_hlt_idx >= 0)
                {
                    new_hlt = 0;
                }
            }


            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_HLT_ELEM,
                            WGL_PACK(new_hlt),
                            NULL);
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                            NULL,
                            NULL);
            c_wgl_repaint(h_lb_ver_info, NULL, TRUE);
            _ver_info_update_arrow_state(ui4_keycode);
        }
        break;

        case BTN_PRG_DOWN:
        {
            UINT32           new_hlt = 0;
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui4_hlt_idx),
                            NULL);
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_ELEM_NUM,
                            WGL_PACK(&ui4_ele_num),
                            NULL);
            if(ui4_ele_num <= 61)
            {
                if( ui4_hlt_idx < COMMON_VER_INOF_ELEM_NUM + 9 )
                {
                    new_hlt = COMMON_VER_INOF_ELEM_NUM + 9;
                }
                else if( (ui4_hlt_idx <= COMMON_VER_INOF_ELEM_NUM * 2 - 2) && (ui4_hlt_idx != ui4_ele_num - 1 - 10))
                {
                    new_hlt = ui4_ele_num - 1 - 10;
                }
                else
                {
                    new_hlt = ui4_ele_num - 1;
                }
            }
            else
            {
                if( ui4_hlt_idx < COMMON_VER_INOF_ELEM_NUM + 9 )
                {
                    new_hlt = COMMON_VER_INOF_ELEM_NUM + 9;
                }
                else if( ui4_hlt_idx <= COMMON_VER_INOF_ELEM_NUM * 2 - 2)
                {
                    new_hlt = COMMON_VER_INOF_ELEM_NUM * 2 + 8;
                }
                else
                {
                    new_hlt = ui4_ele_num - 1;
                }
            }
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_HLT_ELEM,
                            WGL_PACK(new_hlt),
                            NULL);
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                            NULL,
                            NULL);
            c_wgl_repaint(h_lb_ver_info, NULL, TRUE);
            _ver_info_update_arrow_state(ui4_keycode);
        }
        break;

        case BTN_SELECT:
        {
            BOOL b_reset_page = TRUE;
            UINT32  ui4_dlg_page = -1;

            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui4_hlt_idx),
                            NULL);
 #if 0
            if (ui4_hlt_idx == a_g_ver_info_idx[VER_INFO_ROW_SRV_CHK])
            {
                ui4_dlg_page = ui4_page_service_check_dialog;
            }
            else if (ui4_hlt_idx == a_g_ver_info_idx[VER_INFO_ROW_SRV_RST])
            {
                ui4_dlg_page = ui4_page_service_rst_dialog;
            }
 #endif
            if (ui4_dlg_page != -1)
            {
                b_reset_page = menu_page_is_reset_page(ui4_dlg_page);

#ifdef APP_MENU_DLG_COEXIST
                if(b_reset_page)
                {
                    MENU_LOG_ON_FAIL(menu_set_page_hide(FALSE));
                }
                else
                {
                    MENU_LOG_ON_FAIL(menu_set_page_hide(TRUE));
                }
#else
                if(b_reset_page)
                {
                    MENU_LOG_ON_FAIL(menu_hide_help_tip());
                }
#endif

                menu_nav_go(ui4_dlg_page, NULL);

                #ifdef APP_MENU_DLG_COEXIST
                BOOL b_hide = TRUE;

                MENU_LOG_ON_FAIL(menu_get_page_hide(&b_hide));

                if(!b_hide)
                {
                    MENU_LOG_ON_FAIL(menu_set_page_hide(TRUE));
                }
                #endif
            }
            return WMPR_DONE;
        }
        case BTN_EXIT:
        //case BTN_SELECT:
        case BTN_RETURN:
            menu_nav_back();
            return WMPR_DONE;
        case BTN_CURSOR_UP:
            c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui4_hlt_idx),
                            NULL);
            ui2_tmp = (UINT16)ui4_hlt_idx;
            if (ui2_tmp <= a_g_ver_info_idx[VER_INFO_ROW_SYSTEM_INFO])
            {
                menu_set_focus_on_backbar(TRUE);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            }
            _ver_info_update_arrow_state(ui4_keycode);
            break;
        case BTN_CURSOR_DOWN:
            {
                c_wgl_do_cmd(h_lb_ver_info,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui4_hlt_idx),
                            NULL);
                ui2_tmp = (UINT16)ui4_hlt_idx;
                if (ui2_tmp == (a_g_ver_info_idx[VER_INFO_ROW_LAST_NUM]-1))
                {
                    menu_help_tip_keytip_set_focus(h_lb_ver_info,ui2_tmp,FALSE);
                    menu_pm_repaint();
                }
                _ver_info_update_arrow_state(ui4_keycode);
            }
            break;
        default:
            break;
        }
        break;
    }
    case WGL_MSG_KEY_UP:
    {
        if( ui4_keycode == BTN_PRG_UP ||
            ui4_keycode == BTN_PRG_DOWN ||
            ui4_keycode == BTN_PREV_PRG)
        {
            if(t_g_menu_is_scanning == FALSE &&
               t_g_menu_enable_channel_change == TRUE )
            {
                _refresh_info();
                menu_pm_repaint();
                return WMPR_DONE;
            }
        }
    }
#ifdef APP_TTS_SUPPORT
    case WGL_MSG_GET_FOCUS:
    {
        UINT32      ui4_hlt_idx = 0;
        //BOOL        b_read_number_for_string = FALSE;

        c_wgl_do_cmd(h_lb_ver_info,
                WGL_CMD_LB_GET_HLT_INDEX,
                WGL_PACK(&ui4_hlt_idx),
                NULL);

#if 0
        if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
        {
            if(ui4_hlt_idx > VER_INFO_ROW_NETFLIX_ESN2)
            {
                ui4_hlt_idx = ui4_hlt_idx + (VER_INFO_ROW_TUNER - VER_INFO_ROW_NETFLIX_ESN2);
            }
        }
#endif
        c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(ui4_hlt_idx,0),
                    w2s_str);

        {

           /*trans to string*/
           c_uc_w2s_to_ps (w2s_str, info_srting, c_uc_w2s_strlen(w2s_str));

           CHAR*       srting_tts = c_strchr(info_srting,':');
           if(srting_tts != NULL)
           {
               UINT16      str_len_title = 0;
               UINT16      str_len_txt   = 0;
               UTF16_T     string_ver_menu_w2s_str[128+1] = {0};
               CHAR        string_ver_menu[128+1] = {0};
               CHAR        string_ver_menu_title[128+1] = {0};
               CHAR        string_ver_menu_txt  [128+1] = {0};

               /*get title and text*/
               c_sprintf(string_ver_menu_title,"%s",info_srting);
               c_sprintf(string_ver_menu_txt,"%s",srting_tts);

               str_len_title = c_strlen(string_ver_menu_title);
               str_len_txt   = c_strlen(string_ver_menu_txt);

               c_snprintf(string_ver_menu_title, (str_len_title - str_len_txt + 1), "%s",string_ver_menu_title);

               /*remove two spaces */
               sprintf(string_ver_menu_title,"%s",string_ver_menu_title + 2);
               sprintf(string_ver_menu_txt,"%s",string_ver_menu_txt + 3);

               if(c_strcmp(string_ver_menu_title,"Serial Number") == 0 ||
                  c_strcmp(string_ver_menu_title,"ESN") == 0 )
               {
                   /*title:text*/ /*DTV02762679:one by one palying letters and digits,ex:"04LTMWZKKV00502"*/
                   c_sprintf(string_ver_menu, "<say-as interpret-as=\"characters\">%s</say-as>",string_ver_menu_txt);
                   c_sprintf(string_ver_menu_txt, "%s",string_ver_menu);
                   c_sprintf(string_ver_menu, "%s:%s",string_ver_menu_title,string_ver_menu_txt);

                   DBG_LOG_PRINT(("[sys info tts][sn] %s:%s.\n",string_ver_menu_title,string_ver_menu_txt));
               }
               else
               {
                  /*title:text*/
                  sprintf(string_ver_menu, "%s:%s",string_ver_menu_title,string_ver_menu_txt);
               }
               /*set text*/
               c_uc_ps_to_w2s(string_ver_menu, string_ver_menu_w2s_str, c_strlen(string_ver_menu));
               c_uc_w2s_strcpy(w2s_str,string_ver_menu_w2s_str);

           }

           /*tts playing*/
           a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
        }
        //c_uc_w2s_to_ps (w2s_str, info_srting, c_uc_w2s_strlen(w2s_str));
        DBG_INFO(("%s,%d [info tts]get focus idx= %d str= %s, \r\n",__FUNCTION__,__LINE__,ui4_hlt_idx,info_srting));
        break;
    }
#endif

    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
extern UINT32 sys_cust_get_cc_width( VOID );
extern UINT32 sys_cust_get_cc_height( VOID );

/*----------------------------------------------------------------------------
 * Name: _init_version
 *
 * Description:
 *      The version component show the version information.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _lb_ver_info_create(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget
)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    //WGL_IMG_INFO_T              t_img_info;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols;
    WGL_LB_ITEM_T               at_items;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    const CHAR*         s_tmp_str;
    UTF16_T             w2s_tmp_str[128];

    UINT8 ui1_i;


    /* Column info */
    at_cols.e_col_type       = LB_COL_TYPE_TEXT;
    at_cols.ui1_align        = COMMON_VER_INFO_LB_ALIGN;
    at_cols.ui2_width        = COMMON_VER_INFO_LB_COL_W;
    at_cols.ui2_max_text_len = 128;

    /* listbox init struct */
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = VER_INFO_ROW_LAST_NUM;


    t_lb_init.ui2_elem_size     = COMMON_VER_INFO_ELEM_SIZE;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     COMMON_VER_INFO_LB_X,
                     COMMON_VER_INFO_LB_Y,
                     COMMON_VER_INFO_LB_W,
                     COMMON_VER_INFO_LB_H);

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  _ver_info_widget_proc_fct,
                                  255,
                                  & t_lb_init,
                                  NULL,
                                  ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    if(1366 == (UINT32)sys_cust_get_cc_width() &&
        768 == (UINT32)sys_cust_get_cc_height())
    {
        t_fnt_info.e_font_size    = FE_FNT_SIZE_MEDIUM;
    }
    else
    {
        t_fnt_info.e_font_size    = COMMON_VER_INFO_FONT_SIZE;
    }
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Inset */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 15;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)0,
                          &t_inset);
    MENU_LOG_ON_FAIL(i4_ret);

#if 1
    t_inset.i4_left     = COMMON_VER_INFO_INSET_L + 5*4/3;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
#endif

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_disable = t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;//t_g_menu_color_ver_info_text_hlt;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_pushed = t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_selected = t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_selected_disable = t_g_menu_color_bk1_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;//t_g_menu_color_ver_info_bk;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (& t_hlt_elem_effect, 0, sizeof (WGL_LB_HLT_ELEM_EFFECT_T));

    /* Set long text scroll effect */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    CHAR         s_model_name[PLF_OPT_MODEL_NAME_LEN] = {0};
    a_cfg_custom_get_model_name(s_model_name);

    s_tmp_str = "  ";

    for (ui1_i = 0; ui1_i < VER_INFO_ROW_LAST_NUM; ui1_i ++)
    {
        if (FALSE == ab_item_show_flag[ui1_i])
        {
            continue;
        }


        if (  ui1_i != VER_INFO_ROW_SYSTEM_INFO
           && ui1_i != VER_INFO_ROW_NETWORK
          #ifdef MT5695L_MODEL
           && ui1_i != VER_INFO_ROW_CAMERA_INFO
          #endif
           && ui1_i != VER_INFO_ROW_UTV
           //&& ui1_i != VER_INFO_ROW_RD
           //&& ui1_i != VER_INFO_ROW_ML
           //&& ui1_i != VER_INFO_ROW_MC
           && ui1_i != VER_INFO_REMOTE_INFO
           && ui1_i != VER_INFO_ROW_APPLICATION
           && ui1_i != VER_INFO_ROW_CHANNEL_INFO
           )
        {
            c_uc_ps_to_w2s(s_tmp_str, w2s_tmp_str, c_strlen(s_tmp_str));
            c_uc_w2s_strcat(w2s_tmp_str,MENU_TEXT(t_g_ver_items[ui1_i].ui2_mlm_idx));
        }
        else
        {
            c_uc_w2s_strcpy(w2s_tmp_str,MENU_TEXT(t_g_ver_items[ui1_i].ui2_mlm_idx));
        }

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = w2s_tmp_str;

        i4_ret = c_wgl_do_cmd(*ph_widget,
                                WGL_CMD_LB_APPEND_ELEM,
                                WGL_PACK(&at_items),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    }

    return MENUR_OK;
}

static INT32 _chg_lang(VOID)
{
    INT32               i4_ret;
    UINT8               ui1_i;
    const CHAR*         s_tmp_str;
    UTF16_T             w2s_tmp_str[128];
    UTF16_T             w2s_str[128];

    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_SYSTEM_INFO);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(w2s_g_sq, 0, sizeof(w2s_g_sq));

    s_tmp_str = "  ";

    for (ui1_i = 0; ui1_i < VER_INFO_ROW_LAST_NUM; ui1_i ++)
    {
        if (FALSE == ab_item_show_flag[ui1_i])
        {
            continue;
        }

        if (  ui1_i != VER_INFO_ROW_SYSTEM_INFO
           && ui1_i != VER_INFO_ROW_NETWORK
          #ifdef MT5695L_MODEL
           && ui1_i != VER_INFO_ROW_CAMERA_INFO
          #endif
           && ui1_i != VER_INFO_ROW_UTV
           //&& ui1_i != VER_INFO_ROW_RD
           //&& ui1_i != VER_INFO_ROW_ML
           //&& ui1_i != VER_INFO_ROW_MC
           && ui1_i != VER_INFO_REMOTE_INFO
           && ui1_i != VER_INFO_ROW_APPLICATION
           && ui1_i != VER_INFO_ROW_CHANNEL_INFO
           )
        {
            c_uc_ps_to_w2s(s_tmp_str, w2s_str, c_strlen(s_tmp_str));
            c_uc_w2s_strcat(w2s_str,MENU_TEXT(t_g_ver_items[ui1_i].ui2_mlm_idx));
            if (ui1_i == VER_INFO_ROW_SQ)
            {
                c_uc_w2s_strcpy(w2s_g_sq,w2s_str);
            }
        }
        else
        {
            c_uc_w2s_strcpy(w2s_str,MENU_TEXT(t_g_ver_items[ui1_i].ui2_mlm_idx));
        }

        c_uc_ps_to_w2s(s_tmp_str, w2s_tmp_str, c_strlen(s_tmp_str));
        c_uc_w2s_strcat(w2s_str,w2s_tmp_str);
        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2(a_g_ver_info_idx[ui1_i],0),
                                w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));
    }
    c_uc_ps_to_w2s(s_tmp_str, w2s_tmp_str, c_strlen(s_tmp_str));
    c_uc_w2s_strcat(w2s_g_sq,w2s_tmp_str);

    return MENUR_OK;
}

static VOID _do_update_signal_quality(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    INT32 i4_ret = 0;
    _ver_info_signal_quality_update();

    i4_ret = _ver_info_update_free_sync_rate();
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_repaint(h_lb_ver_info, NULL, TRUE);

    i4_ret=c_timer_stop(h_signal_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_signal_timer,
                  VER_INFO_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _timer_signal_nfy_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);

}

static VOID _timer_signal_nfy_fct(HANDLE_T h_timer,VOID* pv_tag)
{
    menu_async_invoke(_do_update_signal_quality, NULL, 0, FALSE);
}

static VOID _do_animation_timer(VOID* pv_data,
                                SIZE_T  z_data_size)
{
    INT32 i4_ret = 0;

    _refresh_info();
    c_wgl_repaint(h_lb_ver_info, NULL, TRUE);

    i4_ret=c_timer_stop(h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_refresh_timer,
                  VER_INFO_REFRESH_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _timer_animation_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);
}


static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    menu_async_invoke(_do_animation_timer, NULL, 0, FALSE);
}

static VOID _ver_info_reset_timer(VOID)
{
    INT32 i4_ret = 0;
    DBG_LOG_PRINT((" [menu] %s,%d\r\n",__FUNCTION__,__LINE__));

    i4_ret=c_timer_stop(h_signal_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_signal_timer,
                  VER_INFO_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _timer_signal_nfy_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_stop(h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_refresh_timer,
                  VER_INFO_REFRESH_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _timer_animation_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);

}

static VOID _ver_info_idx_remapping(VOID)
{
    UINT16      ui2_tmp_idx = 0;
    UINT16      ui2_i = 0;

    c_memset(a_g_ver_info_idx,0,sizeof(UINT16)*VER_INFO_ROW_LAST_NUM);

    ui2_tmp_idx = 0;

    for (ui2_i = 0; ui2_i < sizeof(t_g_ver_items)/sizeof(t_g_ver_items[0]) - 1; ui2_i++)
    {
        if (TRUE == ab_item_show_flag[t_g_ver_items[ui2_i].e_row_idx])
        {
            a_g_ver_info_idx[t_g_ver_items[ui2_i].e_row_idx] = ui2_tmp_idx++;
        }
    }

    /*Last NUM*/
    a_g_ver_info_idx[VER_INFO_ROW_LAST_NUM]     = ui2_tmp_idx;
    c_wgl_do_cmd(h_lb_ver_info,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_tmp_idx),
                 NULL);
}

static VOID _init_item_show_flag(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UINT16  ui2_idx = 0;
    UINT16  ui2_row = 0;
    BOOL            b_tv_source = TRUE;
    BOOL            b_plug = FALSE;
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8           ui1_input_id = 0;
    ISL_REC_T       t_isl_rec;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
    {
        b_tv_source = FALSE;
    }
    #ifdef APP_MENU_MMP_COEXIST
    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        b_tv_source = FALSE;
    }
    else if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        b_tv_source = FALSE;
    }
    #endif
    for (ui2_idx = 0; ui2_idx < VER_INFO_ROW_LAST_NUM; ui2_idx++)
    {
        ab_item_show_flag[ui2_idx] = FALSE;
    }

    a_nw_get_ethernet_connect_info(&b_plug);
    for (ui2_idx = 0; ui2_idx < sizeof(t_g_ver_items)/sizeof(t_g_ver_items[0]); ui2_idx++)
    {
        ui2_row = t_g_ver_items[ui2_idx].e_row_idx;

        switch (ui2_row)
        {
#ifdef APP_SYS_INFO_SP6_SUPPORT
            case VER_INFO_ROW_SSID:
            case VER_INFO_ROW_SECURITY_TYPE:
            //case VER_INFO_ROW_WLAN_MAC:
                ab_item_show_flag[ui2_row] = !b_plug;
                break;
#endif
            case VER_INFO_ROW_PHY_CH:
            case VER_INFO_ROW_FREQ:
            case VER_INFO_ROW_MODULATION:
            case VER_INFO_ROW_STATUS:
            case VER_INFO_ROW_SQ:
                ab_item_show_flag[ui2_row] = b_tv_source;
                break;
        #if 0
            case VER_INFO_ROW_PROGRESSIVE:
                ab_item_show_flag[ui2_row] = FALSE;
                break;
        #endif

        #ifdef APP_SYS_INFO_SP6_SUPPORT
          #if 0
            case VER_INFO_ROW_VCT:
            case VER_INFO_ROW_SLD:
                ab_item_show_flag[ui2_row] = FALSE;
                break;
          #endif

          #if 0//show DEV_CLASS
            case VER_INFO_ROW_DEV_CLASS:
                ab_item_show_flag[ui2_row] = FALSE;
          #endif
        #endif

            //case VER_INFO_ROW_RD:
            //case VER_INFO_ROW_ML:
            //case VER_INFO_ROW_MC:
                ab_item_show_flag[ui2_row] = FALSE;
                break;

            case VER_INFO_ROW_AIRPLAY_VER:
//            case VER_INFO_ROW_REST_VER:
                if(b_airplay_install)
                {
                   ab_item_show_flag[ui2_row] = TRUE;
                }
                else
               {
                if (a_rest_app_check_install_airplay())
                {
                    ab_item_show_flag[ui2_row] = TRUE;
                    b_airplay_install = TRUE;
                }
                else
                {
                    ab_item_show_flag[ui2_row] = FALSE;
                }
               }
            break;

        #ifndef MT5583_MODEL
            case VER_INFO_ROW_RJ45_MAC:
        #else
            case VER_INFO_ROW_ID_MAC:
        #endif
            case VER_INFO_ROW_WLAN_MAC:
            //case VER_INFO_ROW_BLUETOOTH_MAC:
                ab_item_show_flag[ui2_row] = TRUE;
                break;

        #if 0
            case VER_INFO_ROW_UTV_SYN:
            case VER_INFO_ROW_UTV_FCT:
                ab_item_show_flag[ui2_row] = FALSE;
                break;

            case VER_INFO_ROW_FRC_VER:
                ab_item_show_flag[ui2_row] = _ver_is_frc_version_show();
                break;

            case VER_INFO_ROW_UTV_MV:
            case VER_INFO_ROW_UTV_FET:
            case VER_INFO_ROW_UTV_LT:
            case VER_INFO_ROW_TV_AD_ID:
            case VER_INFO_ROW_UTV_LDT:
            case VER_INFO_ROW_UTV_LE:
            case VER_INFO_ROW_UTV_LET:
            case VER_INFO_ROW_UTV_LDM:
            case VER_INFO_ROW_UTV_GID:
            case VER_INFO_ROW_UTV_EC:
            case VER_INFO_ROW_DIID:
            case VER_INFO_ROW_GOOGLE_HOME_VER:
                ab_item_show_flag[ui2_row] = FALSE;
                break;
        #endif

            case VER_INFO_ROW_VRR:
                ab_item_show_flag[ui2_row] = a_cfg_cust_is_variable_refresh_rate_support();
                break;
            case VER_INFO_ACCUMULATED_OPERATING_HOURS:
                ab_item_show_flag[ui2_row] = b_oled;
                break;
            case VER_INFO_ROW_DLM_GENERIC_HOOKS:
            case VER_INFO_ROW_FIRMMAKER_MODE:
            case VER_INFO_ROW_FREE_SYNC_RATE:

            case VER_INFO_ROW_REMOTE_SERIAL:
                ab_item_show_flag[ui2_row] = FALSE;
                break;
            case VER_INFO_ROW_HBOMAX_VER:
                ab_item_show_flag[ui2_row] = FALSE;
                break;

        #if 0//#ifdef MT5695L_MODEL // MVR-162
            case VER_INFO_ROW_CAMERA_INFO:
            case VER_INFO_ROW_CAMERA_ISP:
            case VER_INFO_ROW_MIC_ARRAY_DSP:
                ab_item_show_flag[ui2_row] = FALSE;
        #endif // #ifndef MT5695L_MODEL

            default:
                ab_item_show_flag[ui2_row] = TRUE;
                break;
        }
    }

#if 0 // debug
    for (ui2_idx = 0; ui2_idx < VER_INFO_ROW_LAST_NUM; ui2_idx++)
    {
        DBG_LOG_PRINT((" ab_item_show_flag[%d]: %d \n", ui2_idx, ab_item_show_flag[ui2_idx]));
    }
#endif

    return;
}

#ifdef APP_EMANUAL_SP6_SUPPORT
static VOID _ver_info_key_seq_proc(VOID* pv_data, SIZE_T  z_data_size)
{
    UINT16 ui2_key_seq_id = *(UINT16*)pv_data;
    UINT32 ui4_cur_page = 0;
    UINT32 ui4_hlt_idx = 0;
    extern UINT32 ui4_g_menu_page_ver_info;
    extern UINT32 ui4_g_menu_page_mc_ver;

    if (menu_nav_get_crnt_page(&ui4_cur_page) != MENUR_OK)
    {
        DBG_ERROR(("<MENU> %s Line %d: return error!\n", __FUNCTION__, __LINE__));
        return;
    }

    c_wgl_do_cmd(h_lb_ver_info,
                 WGL_CMD_LB_GET_HLT_INDEX,
                 WGL_PACK(&ui4_hlt_idx),
                 NULL);

    if (ui4_cur_page != ui4_g_menu_page_ver_info
        || ui4_hlt_idx != a_g_ver_info_idx[VER_INFO_ROW_MC])
    {
        DBG_INFO(("<MENU> %s Line %d: return error!\n", __FUNCTION__, __LINE__));
        return;
    }

    if (ui2_key_seq_id == aui2_key_seq_id[VER_INFO_KEY_SEQ_PLAY])
    {
        menu_nav_go(ui4_g_menu_page_mc_ver, NULL);
    }
    else if (ui2_key_seq_id == aui2_key_seq_id[VER_INFO_KEY_SEQ_STOP])
    {
        a_cfg_custom_set_test_mc_version(NULL);
    }
    else
    {
        /* Do Nothing */
    }
}

static VOID _key_sequence_nfy_fct(UINT16 ui2_id, VOID*  pv_tag)
{
    menu_async_invoke(_ver_info_key_seq_proc, (VOID *)&ui2_id, sizeof(ui2_id), FALSE);
}

#endif // #ifdef APP_EMANUAL_SP6_SUPPORT


/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

    _init_item_show_flag();
    b_airplay_install = a_rest_app_check_install_airplay();

    _ver_info_idx_remapping();

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _lb_ver_info_create(h_cnt_frm, &h_lb_ver_info);
    MENU_LOG_ON_FAIL(i4_ret);

    /* bottom arrow up */
    SET_RECT_BY_SIZE(&t_rect,
                        (COMMON_VER_INFO_LB_W-COMMON_VER_ARROW_WIDTH)/2, // COMMON_VER_INFO_LB_X + 24,
                        2,
                        COMMON_VER_ARROW_WIDTH,
                        COMMON_VER_ARROW_HEIGHT);

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &h_arrow_up);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_arrow_up;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_arrow_up;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_arrow_up;
    i4_ret = c_wgl_do_cmd(h_arrow_up,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    /* bottom arrow down */
    SET_RECT_BY_SIZE(&t_rect,
                        (COMMON_VER_INFO_LB_W-COMMON_VER_ARROW_WIDTH)/2, // COMMON_VER_INFO_LB_X + 24,
                        COMMON_VER_INFO_LB_Y + COMMON_VER_INFO_LB_H + 2,
                        COMMON_VER_ARROW_WIDTH,
                        COMMON_VER_ARROW_HEIGHT);
    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &h_arrow_down);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_arrow_down;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_arrow_down;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_arrow_down;
    i4_ret = c_wgl_do_cmd(h_arrow_down,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_timer_create(&h_signal_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_EMANUAL_SP6_SUPPORT
    a_key_seq_reg(ui4_key_seq_play,
                  MENU_PAGE_VER_INFO_KEY_SEQ_LEN,
                  _key_sequence_nfy_fct,
                  (VOID *)NULL,
                  &aui2_key_seq_id[VER_INFO_KEY_SEQ_PLAY]);

    a_key_seq_reg(ui4_key_seq_stop,
                  MENU_PAGE_VER_INFO_KEY_SEQ_LEN,
                  _key_sequence_nfy_fct,
                  (VOID *)NULL,
                  &aui2_key_seq_id[VER_INFO_KEY_SEQ_STOP]);
#endif

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_page_ver_info_get_tuner_model_type(s_tuner_type);
    MENU_LOG_ON_FAIL(i4_ret);
    b_oled = a_is_oled_compensation_support();

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32           i4_ret;
    GL_RECT_T t_rect = {0};
    HANDLE_T h_last_shadow_item = NULL_HANDLE;

    t_g_menu_enable_channel_change = FALSE;
    b_async_flag = TRUE;
    _init_item_show_flag();
    _ver_info_idx_remapping();

    i4_ret = menu_set_homebar_proc(_ver_info_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_ver_info_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (h_lb_ver_info,
                            WGL_CMD_LB_HLT_ELEM_VISIBLE,
                            WGL_PACK(0),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(h_lb_ver_info,WGL_NO_AUTO_REPAINT);

    i4_ret=c_timer_start(h_signal_timer,
                  VER_INFO_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _timer_signal_nfy_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_refresh_timer,
                  VER_INFO_REFRESH_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _timer_animation_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    _chg_lang();

    i4_g_speed = 0;
    _lb_ver_info_update_data();

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left    = CONTENT_X;
    t_rect.i4_right   = CONTENT_X + CONTENT_H;
    t_rect.i4_top     = COMMON_VER_INFO_LB_H + CONTENT_Y + 25;
    t_rect.i4_bottom  = t_rect.i4_top + 150;

    i4_ret = c_wgl_move(h_last_shadow_item,&t_rect,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

#ifndef APP_SYS_INFO_SP6_SUPPORT
    if (a_cfg_custom_get_wifi_remote_support())
    {
        menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_SYSTEM_INFO));
    }
    else
#endif
    {
        menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_SYSTEM_INFO_NO_REMOTE));
    }

    /* set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(h_arrow_up,WGL_SW_HIDE);

    // menu_pm_repaint();

    menu_timer_enable(FALSE);
    menu_timer_stop();

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32    i4_ret;

    t_g_menu_enable_channel_change = TRUE;

    i4_ret=c_timer_stop(h_signal_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_stop(h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_timer_enable(TRUE);
    menu_timer_start();

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

static INT32 _refresh_info(VOID)
{
    INT32 i4_ret = MENUR_OK;

    /*i4_ret = _reset_sys_info();
    MENU_LOG_ON_FAIL(i4_ret);*/

    _init_item_show_flag();

    _ver_info_idx_remapping();

    _chg_lang();

    i4_ret = _lb_ver_info_update_data();
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

extern INT32 menu_common_page_ver_info_init(VOID)
{
    t_g_menu_common_page_ver_info.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_ver_info.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_ver_info.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_ver_info.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_ver_info.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_ver_info.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_ver_info.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

extern INT32 menu_common_page_get_ver_info(CHAR *ps_ver_info, SIZE_T *pz_len)
{
    INT32               i4_ret;
    UINT8               ui1_i;
    CHAR*               s_tmp_str = NULL;
    UTF16_T             w2s_str[128];
    UINT32              ui4_len = 2048;
    SIZE_T              z_item_len = 0;
    SIZE_T              z_content_len = 0;

    if (NULL == ps_ver_info || NULL == pz_len || 0 == *pz_len)
    {
        DBG_ERROR(("%s() Invalid argument!\n\n",__FUNCTION__));
        return MENUR_INV_ARG;
    }

    DBG_LOG_PRINT(("%s() %d: *pz_len=%d ============\n\n",__FUNCTION__,__LINE__,(*pz_len)));

    _refresh_info();
    DBG_LOG_PRINT(("%s() %d:============\n\n",__FUNCTION__,__LINE__));

    s_tmp_str = (CHAR*)c_mem_alloc(ui4_len*sizeof(CHAR));
    if (NULL == s_tmp_str)
    {
        DBG_LOG_PRINT(("%s() %d:Memory allock fail!\n\n", __FUNCTION__,__LINE__));
        return MENUR_OUT_OF_MEMORY;
    }
    c_memset(s_tmp_str, 0, ui4_len*sizeof(CHAR));
    z_content_len = 0;

    DBG_LOG_PRINT(("%s() %d:============\n\n",__FUNCTION__,__LINE__));

    for (ui1_i = 0; ui1_i < VER_INFO_ROW_LAST_NUM; ui1_i ++)
    {
        if (FALSE == ab_item_show_flag[ui1_i])
        {
            continue;
        }

        c_memset(w2s_str, 0, sizeof(w2s_str));

        i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                              WGL_CMD_LB_GET_ITEM_TEXT,
                              WGL_PACK_2(a_g_ver_info_idx[ui1_i],0),
                              w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        z_item_len = c_uc_w2s_strlen(w2s_str);
        //z_content_len = c_strlen(s_tmp_str);

        if (z_content_len + z_item_len >= ui4_len)
        {
            DBG_LOG_PRINT(("%s() %d: buffer is full!\n\n",__FUNCTION__,__LINE__));
            break;
        }

        c_uc_w2s_to_ps(w2s_str, s_tmp_str+z_content_len, ui4_len-z_content_len-1);
        z_content_len += z_item_len;
        s_tmp_str[z_content_len++] = '\n';
        s_tmp_str[z_content_len] = 0;
        DBG_LOG_PRINT(("%s() %d:%s",__FUNCTION__,__LINE__,&s_tmp_str[z_content_len-z_item_len-1]));
    }


    s_tmp_str[ui4_len-1] = 0;
    DBG_LOG_PRINT(("\n%s() Print ver info:\t\n%s\n",__FUNCTION__,s_tmp_str));

    c_strncpy(ps_ver_info, s_tmp_str, (*pz_len)-1);
    DBG_LOG_PRINT(("\n%s() Print copy:\t\n%s\n",__FUNCTION__,ps_ver_info));

    if (s_tmp_str != NULL)
    {
        c_mem_free(s_tmp_str);
        s_tmp_str = NULL;
    }

    return MENUR_OK;
}
#endif /* COMMON_VER_INFO_ENABLE */


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
 * $RCSfile: page_template.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/04 $
 * $Author: jg_lizhuwang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <unistd.h>
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_tools.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_svctx.h"
#include "c_wgl_sets.h"
#include "c_wgl_rect.h"

#include "app_util/a_tv.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_vizio/menu_page_bt_devices.h"
#include "menu2/menu_vizio/menu_page_bt_json_db.h"
#include "menu2/menu_network_phase1/menu_network.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "res/menu2/menu_custom.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "mmp/file_browser/a_file_browser.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "app_util/a_cfg.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "nav/input_src/a_input_src.h"

#include "rest/vzipc/vzIpcServer.h"


#ifdef APP_NETWORK_SUPPORT
#include "app_util/a_network.h"
#endif
#include "nav/input_src/input_src.h"
#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#include "rest/a_rest_api.h"
#endif


#include "app_util/a_key_seq.h"
#include "app_util/help_tip/a_help_tip.h"
#include "res/msgconvert/msgconvert_custom.h"
#include "res/menu2/menu_img.h"

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#ifdef APP_WFD_SUPPORT
#include "wfd/a_wfd.h"
#include "wfd/wfd.h"
#endif

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#include "u_mm_hdlr.h"
#include "nav/c4tv_apron/c4tv_apron.h"

#ifdef LINUX_TURNKEY_SOLUTION
extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
#endif

#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT
#include "app_util/download_util/a_download_util.h"
#endif
#endif

#ifdef COMMON_EX_MAIN_MENU_ENABLE

#define DEBUG_MAIN_NETWORK(x)   x

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MAIN_MENU_BTN_X                 (0)
#define MAIN_MENU_BTN_Y                 (0)
#define MAIN_MENU_BTN_W                 (CONTENT_W/3 - 2)
#define MAIN_MENU_BTN_H                 ((CONTENT_H)/3+8)

#define MAIN_MENU_TEXT_W                (MAIN_MENU_BTN_W)
#define MAIN_MENU_TEXT_H                (MAIN_MENU_BTN_H/2)

#define MAIN_MENU_TAB_TEXT_ALIGN        (WGL_AS_CENTER_BOTTOM)
#define MAIN_MENU_TAB_TEXT_MAX_LEN      (128)

#define MAIN_MENU_FONT_SIZE             FE_FNT_SIZE_MEDIUM
#define MAIN_MENU_BTN_ALIGNMENT         WGL_AS_CENTER_CENTER

//#define MAIN_MENU_MAX_PAGE_NUM   (8)
#define MAIN_MENU_MAX_PAGE_NUM   (9)

#define DEVICE_SET_UP_SUPPORT     1  //need support api
#define MAIN_MENU_ITEM_V_TITLE_W       (2)
#define MAIN_MENU_ITME_END              (0xff)

/*
#define MAIN_MENU_ITEM_INDEX_PIC            ((UINT16)(0))
#define MAIN_MENU_ITEM_INDEX_AUD            ((UINT16)(1))
#define MAIN_MENU_ITEM_INDEX_NETWORK        ((UINT16)(2))
#define MAIN_MENU_ITEM_INDEX_TUNER_SET      ((UINT16)(3))
#define MAIN_MENU_ITEM_INDEX_ACCESSIBILITY  ((UINT16)(4))
#define MAIN_MENU_ITEM_INDEX_SYSTEM         ((UINT16)(5))*/
/*#define MAIN_MENU_ITEM_INDEX_GUID_SETUP     ((UINT16)(8))*/
/*#define MAIN_MENU_ITEM_INDEX_MOBILE_DEVICE     ((UINT16)(8))*//*
#define MAIN_MENU_ITEM_INDEX_ADMIN_PRIVACY  ((UINT16)(6))
#define MAIN_MENU_ITEM_INDEX_USER_MANUAL    ((UINT16)(7))
#define MAIN_MENU_ITEM_INDEX_END            ((UINT16)(8))*/

#define _TTS_CNT_MAX_LEN                    (512)
#define TIME_BAR_X              (475)
#define TIME_BAR_Y              (FRAME_TOP_INTV)
#define TIME_BAR_W              (126)
#define TIME_BAR_H              (46)

#define DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_X              ((SCREEN_W - DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_W)/2)
#define DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_Y              ((SCREEN_H - DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_H)/2)
#define DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_W              (613)
#define DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_H              (234)

#define DISABLE_AUDIO_SETTINGS_DIALOG_ICON_X              (0)
#define DISABLE_AUDIO_SETTINGS_DIALOG_ICON_Y              (10)
#define DISABLE_AUDIO_SETTINGS_DIALOG_ICON_W              (DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_W)
#define DISABLE_AUDIO_SETTINGS_DIALOG_ICON_H              (52)

#define DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_X             (0)
#define DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_Y             (DISABLE_AUDIO_SETTINGS_DIALOG_ICON_Y + DISABLE_AUDIO_SETTINGS_DIALOG_ICON_H + 10)
#define DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_W             (DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_W)
#define DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_H             (MENU_ITEM_V_HEIGHT*2-DISABLE_AUDIO_SETTINGS_DIALOG_ICON_H)

#define DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_X            (DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_W-DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_X-DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_W)
#define DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_Y            (DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_H - DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_H - 32)
#define DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_W            (164)
#define DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_H            (33)

#define DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_X            ((DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_W-(DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_W*2))/3)
#define DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_Y            (DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_Y)
#define DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_W            (DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_W)
#define DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_H            (DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_H)

typedef VOID (*disable_audio_settings_dialog_cb_fct)(HANDLE_T widget_handle, UINT32 ui4_key_code);

extern INT32 _json_bt_db_get_mac(t_bt_item_type type, const char *name, const char *mac);

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
extern INT32 a_cfg_custom_get_srcid_com_or_av(UINT8* pSrcId);
#endif

MENU_PAGE_FCT_TBL_T  t_g_menu_page_ex_main_menu;

static HANDLE_T     h_cnt_frm;
static HANDLE_T     h_time_frm;
static HANDLE_T     h_time_txt;

static HANDLE_T     ah_list_box[MAIN_MENU_MAX_PAGE_NUM];
static UINT8        ui1_hlt_index=0;
//static UINT8        ui1_pre_item_idx = MAIN_MENU_ITEM_INDEX_PIC;
static UINT8        ui1_pre_item_idx = MAIN_MENU_ITEM_INDEX_BT_HEADPHONES;

static UINT16       aui2_help_id[MAIN_MENU_MAX_PAGE_NUM];
static UINT8        ui1_total_page_number = MAIN_MENU_MAX_PAGE_NUM;
static BOOL         ab_items_show[MAIN_MENU_MAX_PAGE_NUM] = {TRUE};
static UINT8        aui1_items_on_ui[MAIN_MENU_MAX_PAGE_NUM] = {0};
static HANDLE_T     h_time_timer;
static BOOL         b_2021sku = FALSE;

static  HANDLE_T    h_confirm_dialog_frm;
static  HANDLE_T    h_warning_icon;
static  HANDLE_T    h_confirm_dialog_title;
static  HANDLE_T    h_confirm_dialog_disconnect;
static  HANDLE_T    h_confirm_dialog_cancel;

static BOOL got_bt_scan_response = FALSE;

#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT

extern BOOL gb_um_is_staging_mode;

#define MENU_PAGE_USER_MANUAL_KEY_SEQ_LEN   ((UINT16)(3))

typedef enum
{
    USER_MANUAL_KEY_SEQ_PLAY,
    USER_MANUAL_KEY_SEQ_STOP,
    USER_MANUAL_KEY_SEQ_NUM
}E_KEY_SEQ_TYPE;

static UINT16       aui2_um_key_seq_id[USER_MANUAL_KEY_SEQ_NUM] = {0};
static UINT32       ui4_um_key_seq_play[MENU_PAGE_USER_MANUAL_KEY_SEQ_LEN] =
                                 {BTN_CURSOR_LEFT, BTN_CURSOR_RIGHT, BTN_PLAY};

static UINT32       ui4_um_key_seq_stop[MENU_PAGE_USER_MANUAL_KEY_SEQ_LEN] =
                                 {BTN_CURSOR_LEFT, BTN_CURSOR_RIGHT, BTN_STOP};
#endif
#endif


static GL_RECT_T   t_rect_border_title = {
    5,
    0,
    MAIN_MENU_ITEM_V_TITLE_W,
    MENU_ITEM_V_HEIGHT};


static WGL_INSET_T t_inset_border = {
    MAIN_MENU_ITEM_V_TITLE_W,
    0,
    0,
    0};


typedef struct __MAIN_MENU_NW_NFY_DATA
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}__MAIN_MENU_NW_NFY_DATA;




typedef struct _MAIN_MENU_PAGE_DATA_T
{
    UINT32       ui4_nw_nfy_id;
    BOOL         b_this_page_show;

    UINT16      ui2_show_test_page_key_id;
    UINT16      ui2_show_test_page_key_id1;
}MAIN_MENU_PAGE_DATA_T;


static MAIN_MENU_PAGE_DATA_T       t_main_menu_nw_page_data;

#ifdef APP_TTS_SUPPORT
static UTF16_T w2s_tts_content[_TTS_CNT_MAX_LEN+1];
#endif

static UINT16  aui2_msg_id[MAIN_MENU_MAX_PAGE_NUM]={
                                MLM_MENU_KEY_BT_HEADPHONES,
                                MLM_MENU_KEY_MAIN_MENU_PIC_SETTING,
                                MLM_MENU_KEY_AUD,
                                MLM_MENU_KEY_MAIN_MENU_NETWORK,
                                MLM_MENU_KEY_TUNER_SET,
                                MLM_MENU_KEY_TTS_ACCESSIBILITY,
                                MLM_MENU_KEY_MAIN_MENU_SYSTEM,
                                MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET,
                             /*   MLM_MENU_KEY_MOBILE_DEVICE,*/
                                MLM_MENU_KEY_HELP_MANUAL
                                };
/*----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _menu_time_timer_start(VOID);
static BOOL _tv_channels_is_enabled(VOID);

/*----------------------------------------------------------------------------
 * Name: _main_menu_set_back_bar_image
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
static INT32 _main_menu_set_back_bar_image(BOOL b_is_back_bar_show)

{
    INT32           i4_ret = MENUR_OK;
    WGL_IMG_INFO_T  t_img_info;
    HANDLE_T        h_back_bar_frm = NULL_HANDLE;

    i4_ret = menu_get_backbar_handle (&h_back_bar_frm);
    MENU_CHK_FAIL(i4_ret);

    /* set image */
    if(!b_is_back_bar_show)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE; //h_g_menu_back_bar_bk;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_back_bar_bk_hlt;
        t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE; //h_g_menu_back_bar_bk;
        i4_ret = c_wgl_do_cmd(h_back_bar_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        menu_show_backbar(FALSE, FALSE);
    }
    return i4_ret;

}

#ifdef APP_NETWORK_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _main_menu_update_network_status
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
INT32 _main_menu_update_network_status(HANDLE_T *ph_image, UTF16_T  *pw2s_text)
{
    INT32                   i4_ret = MENUR_OK;
    NET_802_11_BSS_INFO_T   t_bss_info;
    BOOL                    b_wireless_connected = FALSE;
    NW_DHCP_STATE_T         e_dhcp_state;
    INT32                   i4_len = 0;
    UTF16_T                 w2s_data[32+1] = {0};
    CHAR                    s_data[32+1] = {0};
    BOOL                    b_ethernet = FALSE;
    HANDLE_T                at_img_signal_icon[5] =
    {
        h_g_wifi_signal_half_v2,
        h_g_wifi_signal_1_v2,
        h_g_wifi_signal_2_v2,
        h_g_wifi_signal_3_v2,
        h_g_wifi_signal_4_v2
    };


    //DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d}: \n", __FUNCTION__,__LINE__ )); );

    a_nw_get_ethernet_connect_info(&b_ethernet);
    MENU_LOG_ON_FAIL(i4_ret);

    DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} b_ethernet:%d\n",   __FUNCTION__,__LINE__, b_ethernet )); );

    if(!b_ethernet) /* WIFI*/
    {
        NW_WLAN_STATE_T     e_wlan_state = NW_WLAN_UNPLUG;

        MENU_LOG_ON_FAIL( a_nw_wlan_status(&e_wlan_state));

        DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} WIFI: e_wlan_state:%d\n",   __FUNCTION__,__LINE__, e_wlan_state  )); );

        if (e_wlan_state == NW_WLAN_ASSOCIATE)  /* has associate with wifi*/
        {
            DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} NW_WLAN_ASSOCIATE\n",   __FUNCTION__,__LINE__  )); );

            c_memset (&t_bss_info, 0, sizeof(t_bss_info));
            i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
            if(i4_ret != NWR_OK)
            {
                DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} Error: i4_ret:%d => a_nw_wlan_get_curr_bss() failed!!\n", __FUNCTION__,__LINE__, i4_ret ));

                c_memset( t_bss_info.t_Bssid, 0, sizeof(t_bss_info.t_Bssid));
                t_bss_info.t_Ssid.ui4_SsidLen = 0;
            }
            else
            {
                DBG_LOG_PRINT(("\n[MENU][NETWORK] {%s,%d} BSS_Info from middleware: u8_wpa_status=%d,"
                                "t_CurrBss.t_Ssid.ui4_SsidLen=%d, t_CurrBss.t_Ssid.ui1_aSsid=%s, t_bss_info.i2_Level=%d\n",
                               __FUNCTION__, __LINE__,
                               t_bss_info.u8_wpa_status,
                               t_bss_info.t_Ssid.ui4_SsidLen, t_bss_info.t_Ssid.ui1_aSsid,
                               t_bss_info.i2_Level));

                /* BSS Info Depend on wpa_supplicant support for current dongle */
                /* If wpa_supplicant not support, we can convert rssi to level */
                if (0 == t_bss_info.i2_Level)
                {
                    t_bss_info.i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();
                    DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} t_bss_info.i2_Level:%d\n", __FUNCTION__,__LINE__,t_bss_info.i2_Level )); );
                }

                if( ( c_strlen(t_bss_info.t_Ssid.ui1_aSsid) > 0)/*wifi has been connected*/
                  &&((UINT8)WLAN_WPA_COMPLETED == t_bss_info.u8_wpa_status)
                  )
                {
                    BOOL b_is_get_ip_addr = a_nw_custom_is_get_ip_addr();
                    DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} b_is_get_ip_addr:%d\n", __FUNCTION__,__LINE__, b_is_get_ip_addr )); );
                    if( b_is_get_ip_addr )
                    {
                        b_wireless_connected = TRUE;
                    }
                }
            }

            DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} b_wireless_connected:%d\n", __FUNCTION__,__LINE__, b_wireless_connected )); );

            if( b_wireless_connected )
            {
                INT16           i2_new_level = 0;

                i2_new_level = a_nw_custom_wifi_signal_remapping(t_bss_info.i2_Level);
                DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} WIFI connect OK, i2_new_level:%d\n", __FUNCTION__,__LINE__, i2_new_level )); );

                if (i2_new_level > 80)
                {
                    *ph_image = at_img_signal_icon[4];
                }
                else if (i2_new_level <= 20)
                {
                    *ph_image = at_img_signal_icon[0];
                }
                else
                {
                    *ph_image = at_img_signal_icon[(((i2_new_level-1)) /20)%5];
                }

                if ( c_strlen(t_bss_info.t_Ssid.ui1_aSsid) == 0)
                {
                    pw2s_text = MENU_TEXT(MLM_MENU_KEY_EMPTY);
                }
                else
                {
                    /* connect via wireless */
                    c_memset(w2s_data, 0, 32 * sizeof(UTF16_T));
                    c_memset(s_data, 0, 32);

                    c_strncat(s_data, t_bss_info.t_Ssid.ui1_aSsid, 32);

                    i4_len = c_strlen(s_data);
                    c_uc_ps_to_w2s(s_data, pw2s_text, i4_len);
                }
            }
            else
            {
                a_nw_get_dhcp_status(&e_dhcp_state);
                DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} WIFI connect NG! e_dhcp_state:%d\n", __FUNCTION__,__LINE__, e_dhcp_state )); );

            #if 0    //CID:4491221
                if (NW_DHCP_STARTING == e_dhcp_state)
                {
                    //c_dbg_secure_stmt("\n==============_main_menu_update_network_status===========%d\n",__LINE__);
                    *ph_image = h_g_wifi_signal_error_v2;
                }
                else
                {
                    //c_dbg_secure_stmt("\n====update network status==================%d\n",__LINE__);
                    *ph_image = h_g_wifi_signal_error_v2;
                }
             #endif
                *ph_image = h_g_wifi_signal_error_v2;

                pw2s_text = MENU_TEXT(MLM_MENU_KEY_EMPTY);
            }
        }
        else if (e_wlan_state == NW_WLAN_ASSOCIATING)
        {
            DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} NW_WLAN_ASSOCIATING\n",   __FUNCTION__,__LINE__  )); );
            //c_dbg_secure_stmt("\n====update network status==================%d\n",__LINE__);
            *ph_image = NULL_HANDLE;
            pw2s_text = MENU_TEXT(MLM_MENU_KEY_EMPTY);
        }
        else    /* not associate with wifi*/
        {
            DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d} NW_WLAN_OTHER\n",   __FUNCTION__,__LINE__  )); );
            //c_dbg_secure_stmt("\n====update network status==================%d\n",__LINE__);
            *ph_image = h_g_wifi_signal_error_v2;
            pw2s_text = MENU_TEXT(MLM_MENU_KEY_EMPTY);
        }

    }
    else    /* WIRED */
    {
        if (NWR_OK == a_get_nw_init_status())
        {
            *ph_image = h_g_ethernet_v2;
            pw2s_text = MENU_TEXT(MLM_MENU_KEY_EMPTY);
        }
        else
        {
            *ph_image = h_g_wifi_signal_error_v2;
            pw2s_text = MENU_TEXT(MLM_MENU_KEY_EMPTY);
        }
    }

    return MENUR_OK;
}
#endif


/*----------------------------------------------------------------------------
 * Name: _menu_list_create
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
INT32 _menu_list_create(
                        HANDLE_T            h_parent,
                        UINT8               ui1_index,
                        wgl_widget_proc_fct pf_wdgt_proc,
                        HANDLE_T            *ph_widget,
                        WGL_HIMG_TPL_T      h_img_normal,
                        WGL_HIMG_TPL_T      h_img_hlt)
{
    INT32                       i4_ret = MENUR_OK;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[4];
    WGL_LB_ITEM_T               at_items[4];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    //WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_setting_icon;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_null;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_signal;
    UINT16                      ui2_i;
    WGL_IMG_INFO_T              t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /*===================================================================*
     | icon | text    |    NULL           |  NULL  | ---  other   items  |
     | icon | network |    access point   |  image | ---  network item   |
     *===================================================================*/

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_width        = MENU_ITEM_V_SETTING_ICON+15;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = 120;//(MENU_ITEM_V_WIDE - MAIN_MENU_ITEM_V_TITLE_W - MENU_ITEM_V_LB_ARROW_W*2 - MENU_ITEM_V_LB_INSET_L*2);

    at_cols[2].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[2].ui2_max_text_len = 32;
    at_cols[2].ui2_width        = 300;

    at_cols[3].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[3].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[3].ui2_width        = MENU_ITEM_V_SETTING_SIGNAL + 30;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 4;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * ui1_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* element inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 65;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* column inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK(ui2_i),
                              WGL_PACK(&t_inset));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;

    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(1),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(2),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_white;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(2, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui2_i=0; ui2_i<4; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef MAIN_MENU_ITEM_TEXT_SCROLL_EFFECT
    /* Set long text scroll effect */
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
    c_memset(&t_hlt_elem_effect, 0, sizeof(WGL_LB_HLT_ELEM_EFFECT_T));
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
#endif

    /* Set LB elements */
    c_memset(&t_img_setting_icon, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_setting_icon.h_normal                      = h_img_normal;
    t_img_setting_icon.h_disable                     = h_img_normal;
    t_img_setting_icon.h_highlight                   = h_img_hlt;
    t_img_setting_icon.h_highlight_unfocus           = h_img_normal;
    t_img_setting_icon.h_pushed                      = h_img_normal;
    t_img_setting_icon.h_selected                    = h_img_hlt;
    t_img_setting_icon.h_selected_disable            = h_img_normal;
    t_img_setting_icon.h_selected_pushed             = h_img_hlt;
    t_img_setting_icon.h_selected_highlight          = h_img_hlt;
    t_img_setting_icon.h_selected_highlight_unfocus  = h_img_normal;

    c_memset(&t_img_suit_null, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_null.h_highlight          = NULL_HANDLE;
    t_img_suit_null.h_selected_highlight = NULL_HANDLE;

    c_memset(&t_img_suit_signal, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_signal.h_selected_highlight          = h_g_menu_signal_4of5;
    t_img_suit_signal.h_selected_highlight_unfocus  = h_g_menu_signal_4of5;
    t_img_suit_signal.h_normal                      = h_g_menu_signal_4of5;
    t_img_suit_signal.h_disable                     = h_g_menu_signal_4of5;
    t_img_suit_signal.h_highlight                   = h_g_menu_signal_4of5;
    t_img_suit_signal.h_highlight_unfocus           = h_g_menu_signal_4of5;
    t_img_suit_signal.h_pushed                      = h_g_menu_signal_4of5;
    t_img_suit_signal.h_selected                    = h_g_menu_signal_4of5;
    t_img_suit_signal.h_selected_disable            = h_g_menu_signal_4of5;
    t_img_suit_signal.h_selected_pushed             = h_g_menu_signal_4of5;


    at_items[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_items[0].data.pt_img_suit = &t_img_setting_icon;

    at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text   = MENU_TEXT(MLM_MENU_KEY_EMPTY);

    at_items[2].e_col_type       = LB_COL_TYPE_TEXT;
    at_items[2].data.pw2s_text   = MENU_TEXT(MLM_MENU_KEY_EMPTY);

    at_items[3].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_items[3].data.pt_img_suit = &t_img_suit_null;

    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE; //h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE; //h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
                    function Implementation
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Name
 *      _tv_channels_is_enabled
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _tv_channels_is_enabled(VOID)
{
    INT32           i4_ret = 0;
    ISL_REC_T       t_isl_rec;

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    //"TV channels" grayed out and not selectable for all input expect tuner and comp
    if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV  && !a_nav_ipts_is_comp_source(&t_isl_rec))
    //if (msg_convert_custom_netflix_active() || msg_convert_custom_cobalt_alive() || msg_convert_custom_appletv_plus_active() || msg_convert_custom_hbomax_active())
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}


/*-----------------------------------------------------------------------------
 * Name
 *      _tuner_is_visible
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _tuner_is_visible(VOID)
{
#if 1 // Fix coverity-4490306 Structurally dead code
    return TRUE;   //DTV00897303 [Vizio][TMC-3779]When DUT in HDMI or SCH source, "Channel" is grayed out.

#else
    INT32                       i4_ret = -1;
    ISL_REC_T                   t_isl_rec;
    ISL_REC_T*                  pt_isl_rec = &t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;

    c_memset(&t_resol, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = menu_get_crnt_isl(pt_isl_rec);
#if 0
    if(msg_convert_custom_netflix_active())
    {
        return FALSE;
    }
    if(msg_convert_custom_cobalt_alive())
    {
        return FALSE;
    }

    if(msg_convert_custom_browser_ctrl_active())
    {
        return FALSE;
    }
#endif
    return TRUE;   //DTV00897303 [Vizio][TMC-3779]When DUT in HDMI or SCH source, "Channel" is grayed out.
    if(i4_ret != MENUR_OK)
    {
        return FALSE;
    }
#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return FALSE;
    }
    else if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED && pt_isl_rec->e_src_type != INP_SRC_TYPE_TV)
    {
        return FALSE;
    }
    else if(a_tv_custom_is_3D_mode_playing() == TRUE)
    {
        return FALSE;
    }

#ifdef APP_MENU_WFD_COEXIST
    else if(WFD_COND_PAUSED_WAIT_SVC == wfd_app_get_wfd_cond())
    {
        return FALSE;
    }
#endif
    else
    {
        c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
        i4_ret = menu_get_crnt_isl(pt_isl_rec);
        if(i4_ret != MENUR_OK)
        {
            return FALSE;
        }

        /* Only TV source is visible */
        if( pt_isl_rec->e_src_type == INP_SRC_TYPE_TV )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }

    }
#else
    if(a_tv_custom_is_3D_mode_playing() == TRUE)
    {
        return FALSE;
    }

#ifdef APP_MENU_WFD_COEXIST

    else if(WFD_COND_PAUSED_WAIT_SVC == wfd_app_get_wfd_cond())
    {
        return FALSE;
    }
#endif
    else
    {
        c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
        i4_ret = menu_get_crnt_isl(pt_isl_rec);
        if(i4_ret != MENUR_OK)
        {
            return FALSE;
        }

        /* Only TV source is visible */
        if( pt_isl_rec->e_src_type == INP_SRC_TYPE_TV )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#endif

#endif
}

static BOOL _cc_is_support_ipcc(VOID)
{
    BOOL b_support = FALSE;

#ifdef APP_IPCC_SUPPORT
    APP_TV_NET_IPCC_PROPERTY t_ipcc_property = {0};

    a_tv_net_get_ipcc_property(&t_ipcc_property);
    b_support = t_ipcc_property.b_running;

    DBG_INFO(("%s() t_type = %d, b_support = %d \n\n", __FUNCTION__, b_support));

#endif

    return b_support;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _cc_is_visible
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _cc_is_visible(
                    VOID
                    )
{
    INT32                       i4_ret = -1;
    ISL_REC_T                   t_isl_rec;
    ISL_REC_T*                  pt_isl_rec = &t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resol;
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
    UINT8 SrcId = 0;
#endif

    i4_ret = menu_get_crnt_isl(pt_isl_rec);
    if(i4_ret != MENUR_OK)
    {
        return FALSE;
    }
    c_memset(&t_resol, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        return FALSE;
    }
    //DTV02082038  Fix sSmartCast home page can;t show Caption(cloased caption) Item
    #if 0
    else if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED && pt_isl_rec->e_src_type != INP_SRC_TYPE_TV)
    {
        return FALSE;
    }
    #endif
    else if(a_tv_custom_is_3D_mode_playing() == TRUE)
    {
        return FALSE;
    }
    else
    {
        c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
        i4_ret = menu_get_crnt_isl(pt_isl_rec);
        if(i4_ret != MENUR_OK)
        {
            return FALSE;
        }

        /* Only tuner and complsite are visible*/
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
        DBG_INFO(("<MENU> main page current source:0x%x\n", pt_isl_rec->t_avc_info.e_video_type));
        if(( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_VGA && t_resol.e_timing_type != VSH_SRC_TIMING_VIDEO) ||
            ( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_Y_PB_PR) || /* Component*/
            /*( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_COMP_VIDEO) || */ /* AV */
            ( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_COMBI) ||
            ( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI))
        {
            /*AV source and component source use the same port*/
            if(pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_COMBI)
            {
                i4_ret = a_cfg_custom_get_srcid_com_or_av(&SrcId);
                if(i4_ret != MENUR_OK)
                {
                    DBG_ERROR(("<MENU>a_cfg_custom_get_srcid_com_or_av fail   fail(%d), line(%d)\n",i4_ret,__LINE__));
                    return FALSE;
                }

                if((SrcId == 1) || (SrcId == 0))/*component source or no source*/
                {
                    return FALSE;
                }
                else /*2, AV source */
                {
                    return TRUE;
                }
            }
            else
            {
                /*HDMI CASE*/
                return FALSE;
            }

        }
#endif

        return TRUE;
    }
#else
    if(a_tv_custom_is_3D_mode_playing() == TRUE)
    {
        return FALSE;
    }
    else
    {
        c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
        i4_ret = menu_get_crnt_isl(pt_isl_rec);
        if(i4_ret != MENUR_OK)
        {
            return FALSE;
        }

        /* vga or  hdmi need grayout */
        if(( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_VGA && t_resol.e_timing_type != VSH_SRC_TIMING_VIDEO) ||
           ( pt_isl_rec->t_avc_info.e_video_type == DEV_AVC_HDMI ))
        {
            return FALSE;
        }
        return TRUE;
    }
#endif
}

static BOOL _e_manual_visible(VOID)
{
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
#ifdef APP_RETAIL_MODE_SUPPORT
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
#endif
    return (t_retail_mode != ACFG_RETAIL_MODE_NORMAL);
}

#ifdef APP_EMANUAL_SUPPORT
static VOID _start_e_manual(VOID)
{

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
#ifdef APP_EMANUAL_SP6_SUPPORT
        CHAR ps_cmd[128] = {0};
#endif

#ifdef APP_CFG_DIMMING_OFF_IN_EMANUAL
        a_cfg_custom_set_dimming_off();
#endif
        menu_set_start_user_manual_flag(TRUE);

#ifdef APP_EMANUAL_SP6_SUPPORT

        DBG_INFO(("\n####%s(%d) UM of SP6 Support\n",__FUNCTION__,__LINE__));

        a_um_clear_temp();

        /* check get IP and server is avalible or not */
        if(a_nw_custom_is_get_ip_addr() && (TRUE == a_um_is_server_avalible()))
        {
            if(menu_manual_in_flash() || a_is_dld_um_in_flash())   // check manual in flash or not
            {
                DBG_INFO(("\n !!!!!Check update and show e_manual ####%s(%d)\n",__FUNCTION__,__LINE__));

                // check update here, no dialog
                if(TRUE == a_um_chk_manual_is_up_to_date())
                {
                    a_tv_net_send_cmd("\n:am,dtv_app_mtk,:button=MENU\n"); // hide menu

                    // Show manual
                    DBG_INFO(("\n !!!!!Show UM ####%s(%d)\n",__FUNCTION__,__LINE__));

                    DBG_INFO(("\n%s(%d)Close MBR\n",__FUNCTION__,__LINE__));
                    a_cfg_custom_set_reduce_blur(0);
                    a_cfg_custom_update_reduce_blur(0);

                    if(a_is_dld_um_in_flash())
                    {
                        a_show_dld_um();
                    }
                    else
                    {
                        c_sprintf(ps_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//3rd_rw/e_manual/test_manual/index.htm");
                        cmd_convert_send_cmd(ps_cmd);

                        DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be TRUE after send command.\n",__FUNCTION__,__LINE__));
                        a_um_set_status_is_displaying(TRUE);
                    }
                }
                else
                {
                    a_tv_net_send_cmd("\n:am,dtv_app_mtk,:button=MENU\n"); // hide menu

                    a_download_util_file();
                    DBG_INFO(("\n !!!!!download and untar and show e_manual ####%s(%d)\n",__FUNCTION__,__LINE__));

                }

            }
            else
            {
                a_tv_net_send_cmd("\n:am,dtv_app_mtk,:button=MENU\n"); // hide menu

                a_download_util_file();
                DBG_INFO(("\n !!!!!download and untar and show e_manual ####%s(%d)\n",__FUNCTION__,__LINE__));
            }
        }
        else
        {
            a_tv_net_send_cmd("\n:am,dtv_app_mtk,:button=MENU\n"); // hide menu

            if(menu_manual_in_flash() || a_is_dld_um_in_flash())   // check manual in flash or not
            {
                DBG_INFO(("\n !!!!!Show UM ####%s(%d)\n",__FUNCTION__,__LINE__));

                DBG_INFO(("\n%s(%d)Close MBR\n",__FUNCTION__,__LINE__));
                a_cfg_custom_set_reduce_blur(0);
                a_cfg_custom_update_reduce_blur(0);

                if(a_is_dld_um_in_flash())
                {
                    a_show_dld_um();
                }
                else
                {
                    c_sprintf(ps_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//3rd_rw/e_manual/test_manual/index.htm");
                    cmd_convert_send_cmd(ps_cmd);

                    DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be TRUE after send command.\n",__FUNCTION__,__LINE__));
                    a_um_set_status_is_displaying(TRUE);
                }
            }
            else
            {
                DBG_INFO(("\n%s(%d)Close MBR\n",__FUNCTION__,__LINE__));
                a_cfg_custom_set_reduce_blur(0);
                a_cfg_custom_update_reduce_blur(0);

                DBG_INFO(("\n!!!! Show help page ####%s(%d)\n",__FUNCTION__,__LINE__));
                c_sprintf(ps_cmd,"\n:dtv_app_mtk,am,:start_ex=[html_apps,\"-w 1280 -h 720 -x redirect_app -m NO -u %s\"]\n", "//basic/e_manual/help_guide/index.htm");
                cmd_convert_send_cmd(ps_cmd);

                DBG_INFO(("\n\t\t####%s(%d)Set user manual displaying status to be TRUE after send command.\n",__FUNCTION__,__LINE__));
                a_um_set_status_is_displaying(TRUE);
            }

        }

#else
        a_tv_net_send_cmd("\n:am,dtv_app_mtk,:button=MENU\n");
#endif
    }

}
#endif

/*----------------------------------------------------------------------------
 * Name: _menu_show_test_page_key_seq_handler
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
static VOID _menu_show_test_page_key_seq_handler(VOID*  pv_data,
                                                SIZE_T  z_data_size)
{
    INT32           i4_ret = MENUR_OK;

    i4_ret = menu_nav_go(ui4_g_menu_page_test_special_param, NULL);
    MENU_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _menu_key_sequence_show_test_page_nfy_fct
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
VOID _menu_key_sequence_show_test_page_nfy_fct(UINT16 ui2_id,  VOID* pv_tag)
{
    MAIN_MENU_PAGE_DATA_T* pt_page_data = &t_main_menu_nw_page_data;
    UINT32  ui4_cur_page = 0;

    if (!t_main_menu_nw_page_data.b_this_page_show)
    {
        return;
    }

    if (pt_page_data->ui2_show_test_page_key_id == ui2_id ||
        pt_page_data->ui2_show_test_page_key_id1 == ui2_id)
    {
        if (MENUR_OK != menu_nav_get_crnt_page(&ui4_cur_page) ||
            ui4_g_menu_page_main_menu != ui4_cur_page)
        {
            DBG_ERROR(("<MENU> %s Line %d: return error!\n", __FUNCTION__, __LINE__));
            return;
        }
        menu_async_invoke(_menu_show_test_page_key_seq_handler, NULL, 0, TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _page_show_test_page_key_seq_reg
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
static VOID _page_show_test_page_key_seq_reg(VOID)
{
    INT32               i4_ret = 0;
    MAIN_MENU_PAGE_DATA_T* pt_page_data = &t_main_menu_nw_page_data;
    UINT32              aui4_key_seq[3] = {BTN_CURSOR_LEFT, BTN_CURSOR_RIGHT, BTN_PLAY};
    UINT32              aui4_key_seq1[3] = {BTN_CURSOR_LEFT, BTN_CURSOR_RIGHT, BTN_CURSOR_UP};
    DBG_LOG_PRINT(("[MENU]Show TEST page KEY sequence reg in FUNC: %s.\n", __FUNCTION__));

    if(APP_KEY_SEQ_OK != a_key_seq_reg(aui4_key_seq,
                                       3,
                                       _menu_key_sequence_show_test_page_nfy_fct,
                                       NULL,
                                       &(pt_page_data->ui2_show_test_page_key_id)))
    {
        DBG_ERROR(("<MENU> Signal LVL register error:%s:%d:%d\r\n",__FILE__, __LINE__, i4_ret));
    }
    if(APP_KEY_SEQ_OK != a_key_seq_reg(aui4_key_seq1,
                                       3,
                                       _menu_key_sequence_show_test_page_nfy_fct,
                                       NULL,
                                       &(pt_page_data->ui2_show_test_page_key_id1)))
    {
        DBG_ERROR(("<MENU> Signal LVL register error:%s:%d:%d\r\n",__FILE__, __LINE__, i4_ret));
    }
}

/*----------------------------------------------------------------------------
 * Name: _page_show_test_page_key_seq_unreg
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
static VOID _page_show_test_page_key_seq_unreg(VOID)
{
    INT32               i4_ret = 0;
    MAIN_MENU_PAGE_DATA_T* pt_page_data = &t_main_menu_nw_page_data;

    DBG_LOG_PRINT(("[MENU]Signal LVL KEY sequence unreg in FUNC: %s.\n", __FUNCTION__));

    if (APP_KEY_SEQ_OK != a_key_seq_unreg(pt_page_data->ui2_show_test_page_key_id))
    {
        DBG_ERROR(("<MENU> Signal LVL un-register error:%s:%d:%d\r\n",
                    __FILE__, __LINE__, i4_ret));
    }

    if (APP_KEY_SEQ_OK != a_key_seq_unreg(pt_page_data->ui2_show_test_page_key_id1))
    {
        DBG_ERROR(("<MENU> Signal LVL un-register error:%s:%d:%d\r\n",
                    __FILE__, __LINE__, i4_ret));
    }

    pt_page_data->ui2_show_test_page_key_id = 0;
    pt_page_data->ui2_show_test_page_key_id1 = 0;
}
static BOOL _menu_page_parental_control_enable(VOID)
{
    ISL_REC_T   t_isl_rec;
    INT32       i4_ret = 0;
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
    UINT8 SrcId = 0;
#endif
    menu_get_crnt_isl(&t_isl_rec);

#ifdef APP_AV_COMPONENT_USE_ONE_PORT
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR || /* Component*/
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI ||
        t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI))
    {
        /*AV source and component source use the same port*/
        if(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI)
        {
            i4_ret = a_cfg_custom_get_srcid_com_or_av(&SrcId);
                if(i4_ret != MENUR_OK)
                {
                    DBG_LOG_PRINT(("<MENU>a_cfg_custom_get_srcid_com_or_av fail   fail(%d), line(%d)\n",i4_ret,__LINE__));
                    return FALSE;
                }

                if((SrcId == 1) || (SrcId == 0))/*component source or no source*/
                {
                    return FALSE;
                }
                else /*2, AV source */
                {
                    return TRUE;
                }
        }
        return FALSE;
    }
#endif
    return FALSE;
}

BOOL a_menu_page_parental_control_enable(VOID)
{
    return _menu_page_parental_control_enable();

}

static VOID _menu_page_atsc_auto_sacn_sync_change_source_to_tv(
    VOID*                              pv_this,
    VOID*                              pv_unused2,
    VOID*                              pv_unused3)
{
    INT32               i4_ret = 0;
    TV_WIN_ID_T         e_focus_id;
    ISL_REC_T           t_isl_rec;
    BOOL                b_cast_state = 0;

    /*If previous source is CastTV, exit it */
    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
    NAV_LOG_ON_FAIL(i4_ret);

    b_cast_state = a_c4tv_apron_check_cast_state();

    DBG_LOG_PRINT(("<NAV INPUT> b_cast_state=%d, cur input=%d\r\n",
                                                                    b_cast_state,
                                                                    t_isl_rec.ui1_id));

    if ((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type
        && DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type))
    {
        nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID, TV_WIN_ID_MAIN, 0);
    }
    else if (DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type)
    {
        nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID, TV_WIN_ID_MAIN, 0);
    }
    else
    {
        if((b_cast_state))
        {
             DBG_LOG_PRINT(("%s_%d send change message again \n ",__FUNCTION__,__LINE__));
            nav_request_context_switch(_menu_page_atsc_auto_sacn_sync_change_source_to_tv,
                                       NULL,
                                       NULL,
                                       NULL);
            return;
        }
        nav_ipts_switch_src(NAV_IPTS_SMS_TO_TV, TV_WIN_ID_MAIN, 0);
    }
    menu_custom_update_the_old_display_region_after_change_source_tv();
}
static INT32 _menu_page_atsc_auto_sacn_change_source_to_tv(VOID)
{
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8           ui1_input_id = 0;
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret = MENUR_OK;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("%s_%d current source is %d ui1_input_id:0x%x \n ",__FUNCTION__,__LINE__,t_isl_rec.e_src_type,ui1_input_id));
    if((INP_SRC_TYPE_TV == t_isl_rec.e_src_type) || (_menu_page_parental_control_enable()))//For comp source,need control Parent Control,DTV00935369
    {
        DBG_LOG_PRINT(("%s_%d current source is tv \n ",__FUNCTION__,__LINE__));
        return MENUR_OK;
    }

    if(mmp_main_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
    {
        a_mmp_pause_background_mmp_for_menu();
    }
    rest_event_notify_current_input("tuner");
    nav_request_context_switch(_menu_page_atsc_auto_sacn_sync_change_source_to_tv,
                               NULL,
                               NULL,
                               NULL);

    return i4_ret;
}

static INT32 _main_menu_play_tts(VOID)
{
#ifdef APP_TTS_SUPPORT
    INT32   i4_ret = MENUR_OK;
    BOOL    b_visible = FALSE;
    UINT8   ui1_tts_switch_status = APP_CFG_TTS_SWITCH_OFF;

    a_cfg_get_tts_switch_status(&ui1_tts_switch_status);
    if (APP_CFG_TTS_SWITCH_OFF == ui1_tts_switch_status)
    {
        DBG_INFO(("_main_menu_play_tts() TTS Switch is off\n"));
        return i4_ret;
    }
    c_wgl_get_visibility(ah_list_box[aui1_items_on_ui[ui1_hlt_index]], &b_visible);
    if (!b_visible)
    {
        DBG_LOG_PRINT(("menu item is not visible.\n"));
        return i4_ret;
    }
    c_memset(w2s_tts_content, 0, sizeof(w2s_tts_content));
    if (MAIN_MENU_ITEM_INDEX_ADMIN_PRIVACY == aui1_items_on_ui[ui1_hlt_index])
    {
        c_uc_w2s_strncpy(w2s_tts_content,
                 MLM_MENU_TEXT(0, MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET_TTS),
                 _TTS_CNT_MAX_LEN);
    }
    else
    {
        c_uc_w2s_strncpy(w2s_tts_content,
                         MLM_MENU_TEXT(0, aui2_msg_id[aui1_items_on_ui[ui1_hlt_index]]),
                         _TTS_CNT_MAX_LEN);
    }
    if (MAIN_MENU_ITEM_INDEX_NETWORK == aui1_items_on_ui[ui1_hlt_index])
    {
        UTF16_T w2s_ssid[33] = {0};

        i4_ret = c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_NETWORK],
                         WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2(0, 2),
                         WGL_PACK(w2s_ssid));
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strcat(w2s_tts_content, _TEXT("."));
        c_uc_w2s_strcat(w2s_tts_content, w2s_ssid);
    }

    i4_ret = a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
#else
    return MENUR_OK;
#endif
}

static INT32 _confirm_dialog_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        {
            disable_audio_settings_dialog_cb_fct  pf_back = NULL;
            INT32           i4_ret;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pf_back),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(pf_back != NULL)
            {
                pf_back(h_widget, ui4_keycode);
            }

            return WGLR_OK;
        }
        default:
            break;
        }

        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _confirm_dialog_create(VOID)
{
    INT32       i4_ret;
    GL_RECT_T    t_rect;
    HANDLE_T     h_root_frm;

    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_IMG_INFO_T    t_img_info;

    WGL_INSET_T t_inset = {
        8*4/3,
        8*4/3,
        3*4/3,
        0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_X,
                      DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_Y,
                      DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_W,
                      DISABLE_AUDIO_SETTINGS_DIALOG_FRAM_H);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 0,
                                 &h_confirm_dialog_frm);
    MENU_LOG_ON_FAIL(i4_ret);

     t_img_info.e_type = WGL_IMG_SET_STANDARD;
     t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_box_v2;
     t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_box_v2;
     t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_box_v2;
     i4_ret = c_wgl_do_cmd(h_confirm_dialog_frm,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                      DISABLE_AUDIO_SETTINGS_DIALOG_ICON_X,
                      DISABLE_AUDIO_SETTINGS_DIALOG_ICON_Y,
                      DISABLE_AUDIO_SETTINGS_DIALOG_ICON_W,
                      DISABLE_AUDIO_SETTINGS_DIALOG_ICON_H);

    i4_ret = c_wgl_create_widget(h_confirm_dialog_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &h_warning_icon);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_rect.i4_left      = 0;
    t_rect.i4_right     = 0;
    t_rect.i4_top       = 0;
    t_rect.i4_bottom    = 0;
    i4_ret = c_wgl_do_cmd (h_warning_icon,
                           WGL_CMD_GL_SET_INSET,
                           &t_rect,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_warning_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_warning_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_warning_icon;
    i4_ret = c_wgl_do_cmd(h_warning_icon,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_FG),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(h_warning_icon,
                           WGL_CMD_ICON_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     SET_RECT_BY_SIZE(&t_rect,
                      DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_X,
                      DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_Y,
                      DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_W,
                      DISABLE_AUDIO_SETTINGS_DIALOG_TITLE_H);

     i4_ret = c_wgl_create_widget(h_confirm_dialog_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                                  NULL,
                                  &h_confirm_dialog_title);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     /* Set Insets */
     i4_ret = c_wgl_do_cmd(h_confirm_dialog_title,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(h_confirm_dialog_title,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_TOP,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Font */
     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

     t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
     t_fnt_info.ui1_custom_size = 24;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
     i4_ret = c_wgl_do_cmd (h_confirm_dialog_title,
                            WGL_CMD_GL_SET_FONT,
                            (void*)&t_fnt_info,
                            NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
     t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
     i4_ret = c_wgl_do_cmd(h_confirm_dialog_title,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info) );
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_X,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_Y,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_W,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_H);

    i4_ret = c_wgl_create_widget(h_confirm_dialog_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _confirm_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &h_confirm_dialog_disconnect);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_confirm_dialog_disconnect,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (h_confirm_dialog_disconnect,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(h_confirm_dialog_disconnect,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(h_confirm_dialog_disconnect,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_X,
                     DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_Y,
                     DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_W,
                     DISABLE_AUDIO_SETTINGS_DIALOG_CANCEL_H);

    i4_ret = c_wgl_create_widget(h_confirm_dialog_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _confirm_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &h_confirm_dialog_cancel);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_confirm_dialog_cancel,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (h_confirm_dialog_cancel,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(h_confirm_dialog_cancel,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(h_confirm_dialog_cancel,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility (h_confirm_dialog_frm, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (h_confirm_dialog_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 menu_disable_audio_settings_hide_confirm_dialog(BOOL  b_repaint)																  
{
    DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO :   %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_visibility(h_confirm_dialog_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)						   
    {
        i4_ret = c_wgl_repaint(h_confirm_dialog_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}

VOID disable_audio_settings_confirm_dialog_set_focus_cancel(VOID)
{
    DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO :   %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));

    c_wgl_set_focus(h_confirm_dialog_cancel,
                        WGL_SYNC_AUTO_REPAINT);

#ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (h_confirm_dialog_cancel,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif
}
												
VOID disable_audio_settings_confirm_dialog_set_focus_disconnect(VOID)
{
    DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO :   %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));
    c_wgl_set_focus(h_confirm_dialog_disconnect,
                        WGL_SYNC_AUTO_REPAINT);

#ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (h_confirm_dialog_disconnect,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif

}

static VOID disable_audio_settings_confirm_dialog_disconnect_cb_fct(HANDLE_T h_widget, UINT32 ui4_key_code)
{
    INT32 i4_ret;
    DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO :  %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));
    static char disconnect_mac[18] = {0};

    if (BTN_CURSOR_LEFT == ui4_key_code)
    {
        disable_audio_settings_confirm_dialog_set_focus_cancel();
    }
    else if (BTN_CURSOR_RIGHT == ui4_key_code)							
    {
        disable_audio_settings_confirm_dialog_set_focus_disconnect();
    }
    else if (BTN_SELECT == ui4_key_code)
    {
        menu_disable_audio_settings_hide_confirm_dialog(TRUE);
        i4_ret = c_wgl_set_focus(ah_list_box[MAIN_MENU_ITEM_INDEX_AUD], WGL_SYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        if (_json_bt_db_get_mac(BD_ARR_TYPE_CONNECTED, NULL, disconnect_mac) == MENUR_OK)
        {
            SendReqBTAUDIO_Q(BTAPI_STOP_STREAM, disconnect_mac);
            char *pt_msg = NULL;
            do
            {
                pt_msg = GetRespBTAUDIO_Q(BTAPI_STOP_STREAM);
                if (NULL != pt_msg)
                {
                    free(pt_msg);
                    return;
                }
                else
                {
                    msleep(10);
                }
            } while (NULL == pt_msg);
        }
        DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO :  %s,%s,%d,  disconnect_mac = %s \n", __FILE__, __FUNCTION__, __LINE__, disconnect_mac));
    }
    else
    {
        menu_disable_audio_settings_hide_confirm_dialog(TRUE);
        i4_ret = c_wgl_set_focus(ah_list_box[MAIN_MENU_ITEM_INDEX_AUD], WGL_SYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

static VOID disable_audio_settings_confirm_dialog_cancel_cb_fct(HANDLE_T widget_handle, UINT32 ui4_key_code)
{
    INT32 i4_ret;
    DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO :  %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));
    if (BTN_CURSOR_LEFT == ui4_key_code)
    {
        disable_audio_settings_confirm_dialog_set_focus_cancel();
    }
    else if (BTN_CURSOR_RIGHT == ui4_key_code)
    {
        disable_audio_settings_confirm_dialog_set_focus_disconnect();
    }
    else
    {
        menu_disable_audio_settings_hide_confirm_dialog(TRUE);
        i4_ret = c_wgl_set_focus(ah_list_box[MAIN_MENU_ITEM_INDEX_AUD], WGL_SYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

INT32 menu_disable_audio_settings_show_confirm_dialog_ex(
                                    UTF16_T*            pw2s_msg_text,
                                    UTF16_T*            pw2s_btn_disconnect,
                                    UTF16_T*            pw2s_btn_cancel,
                                    disable_audio_settings_dialog_cb_fct    pf_back_disconnect,
                                    disable_audio_settings_dialog_cb_fct    pf_back_cancel,
                                    BOOL                b_repaint
                                    )
{
    DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO :   %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));
    INT32 i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;

    if (NULL == pw2s_msg_text || NULL == pw2s_btn_disconnect || NULL == pw2s_btn_cancel)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(h_confirm_dialog_disconnect,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_disconnect),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_confirm_dialog_cancel,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_cancel),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_confirm_dialog_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_text),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_confirm_dialog_disconnect,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_disconnect),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_confirm_dialog_cancel,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_cancel),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_X,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_Y,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_W,
                     DISABLE_AUDIO_SETTINGS_DIALOG_DISCONNECT_H);

    c_wgl_move(h_confirm_dialog_disconnect, &t_rect, WGL_NO_AUTO_REPAINT);
    c_wgl_set_focus(h_confirm_dialog_disconnect, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(h_confirm_dialog_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(h_confirm_dialog_frm,  NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[256] = {0};

        c_uc_w2s_strcpy(w2s_str, pw2s_msg_text);
        c_uc_w2s_strcat(w2s_str, _TEXT("."));
        c_uc_w2s_strcat(w2s_str, pw2s_btn_disconnect);

        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
    #endif
    }

    return MENUR_OK;
}

static INT32 _list_item_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32  i4_ret=0;
    BOOL   b_care_key=FALSE;
    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        b_care_key = TRUE;
        i4_ret = menu_set_help_tip(MENU_TEXT(aui2_help_id[aui1_items_on_ui[ui1_hlt_index]]));
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;
        BOOL   b_need_help_tip=FALSE;
        GL_RECT_T       t_rect;
        UINT8           ui1_old_hlt_idx = 4;
        GL_RECT_T   t_rect_1;
        GL_RECT_T   t_rect_2;
        GL_RECT_T   t_rect_union;
        HANDLE_T        h_last_shadow_item = NULL_HANDLE;
        extern UINT32 ui4_g_menu_page_nw;
        UINT32 aui4_page[MAIN_MENU_MAX_PAGE_NUM]={
                             ui4_g_menu_page_bt_headphones,     //Bluetooth headphones
                             ui4_g_menu_page_vid,               /*Picture        0*/
                             ui4_g_menu_page_aud,               /*Audio          1*/
                             ui4_g_menu_page_nw,                /*Network      2*/
                             ui4_g_menu_page_channels,          /*Tuner          3*/
                             ui4_page_accessibility,            /*Accessibility 4*/
                             ui4_g_menu_page_setup,             /*Setting        5*/
                             ui4_page_help_sys_info_and_reset,  /*Reset & Privacy  6*/
                             ui4_g_menu_page_user_manual        /*User Menu   8*/
                             };
        if(a_tv_custom_get_tos() == FALSE || a_tv_custom_get_privacy() == FALSE)
        {
            aui4_page[MAIN_MENU_ITEM_INDEX_NETWORK] = ui4_g_menu_page_terms;
        }
        MENU_ASSERT(ui1_hlt_index < ui1_total_page_number);
        /*Keep OLD*/
        ui1_old_hlt_idx = ui1_hlt_index;
        switch (ui4_keycode)
        {
            case BTN_CURSOR_UP:
            {
                b_care_key = TRUE;
                if(ui1_hlt_index != 0)
                {
                    UINT8 jumpIndex = MAIN_MENU_ITEM_INDEX_TUNER_SET;
                    if (ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES] == FALSE)
                    {
                        --jumpIndex;
                    }
                    //not select TV channels,when _tv_channels_is_enabled false
                    if(!_tv_channels_is_enabled() && ui1_hlt_index == (jumpIndex+1))
                    {
                        ui1_hlt_index = (jumpIndex-1);
                    }
                    else
                        ui1_hlt_index = ui1_hlt_index - 1;
                }
                MENU_ASSERT(ui1_hlt_index < ui1_total_page_number);
                ui1_pre_item_idx = aui1_items_on_ui[ui1_hlt_index];
            }
            break;
            case BTN_CURSOR_DOWN:
            {
                b_care_key = TRUE;
                UINT16  ui2_idx = 0;
                if((ui1_total_page_number -1) == ui1_hlt_index)
                {
                    ui2_idx = 2;
                    i4_ret = menu_help_tip_keytip_set_focus(ah_list_box[aui1_items_on_ui[ui1_hlt_index]],
                                                         ui2_idx,
                                                         FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                    return MENUR_OK;
                }
                else
                {
                    //not select TV channels,when _tv_channels_is_enabled false
                    UINT8 jumpIndex = MAIN_MENU_ITEM_INDEX_TUNER_SET;
                    if (ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES] == FALSE)
                    {
                        --jumpIndex;
                    }
                    if(!_tv_channels_is_enabled() && ui1_hlt_index == (jumpIndex -1))
                    {
                        ui1_hlt_index = (jumpIndex+1);
                    }
                    else
                    {
                        ui1_hlt_index = ui1_hlt_index + 1;
                    }
                    ui1_pre_item_idx = aui1_items_on_ui[ui1_hlt_index];
                }
            }
            break;

            case BTN_SELECT:
            {
                UINT8    ui1_page_id = aui1_items_on_ui[ui1_hlt_index];
                SET_RECT_BY_SIZE(&t_rect,
                                 CONTENT_X,
                                 CONTENT_Y,
                                 CONTENT_W,
                                 CONTENT_H);

                i4_ret = c_wgl_move(h_cnt_frm,&t_rect,FALSE);
                MENU_CHK_FAIL(i4_ret);

                //Below code of naming menu page TV Setting is legacy. Hence retained 
                CHAR headphone_name[256] = {0};
                SIZE_T  c_ps_str_len = 0;
                SIZE_T  c_w2s_str_len = 0;
                UTF16_T w2s_data[256] = {0};
                get_connected_audio_device_from_jsondb(w2s_data);

                c_w2s_str_len = c_uc_w2s_strlen(w2s_data);
                c_ps_str_len = c_w2s_str_len * sizeof(UTF16_T);
                c_uc_w2s_to_ps(w2s_data, headphone_name, c_ps_str_len);

                DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO : headphone_name = %s  %s,%s,%d, \n", headphone_name, __FILE__, __FUNCTION__, __LINE__));
                if (!((MAIN_MENU_ITEM_INDEX_AUD == aui1_items_on_ui[ui1_hlt_index])
                    && (ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES] == TRUE)
                    && c_strcmp(headphone_name, "None") && c_strcmp(headphone_name, "")))
                {
                    //Show title text
                    i4_ret = menu_main_set_title(MLM_MENU_KEY_TV_SETTING);
                    MENU_CHK_FAIL(i4_ret);
                
                    /*Show back bar*/
                    if (aui4_page[ui1_page_id] != ui4_g_menu_page_user_manual)
                    {
                        i4_ret = menu_show_backbar(TRUE, FALSE);
                        MENU_CHK_FAIL(i4_ret);
                    }
                    if(1==FALSE)
                    {
                        b_need_help_tip = FALSE;
                    }
                    else
                    {
                        b_need_help_tip = TRUE;
                    }
                    /* Show the key tip */
                    i4_ret = menu_help_tip_keytip_show(b_need_help_tip);
                    MENU_CHK_FAIL(i4_ret);
                }

                if(ui1_hlt_index >= ui1_total_page_number)
                {
                    return MENUR_FAIL;
                }

#ifdef APP_EMANUAL_SUPPORT
                if(MAIN_MENU_ITEM_INDEX_USER_MANUAL == aui1_items_on_ui[ui1_hlt_index])
                {
                    _start_e_manual();
                }
                else
#endif
                if (MAIN_MENU_ITEM_INDEX_NETWORK == aui1_items_on_ui[ui1_hlt_index]
                    && aui4_page[ui1_page_id] == ui4_g_menu_page_terms
                    && access("/data/enable_network_tos", F_OK) < 0)
                {
                    TV_WIN_ID_T                 e_focus_id;
                    ISL_REC_T                   t_isl_rec;

                    // Deep-link into OOBE VIZIO ToS
                    DBG_LOG_PRINT(("Deep-linked OOBE TOS Page launch\n"));

                    i4_ret = a_tv_get_focus_win(&e_focus_id);
                    NAV_LOG_ON_FAIL(i4_ret);
                    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id,&t_isl_rec);
                    NAV_LOG_ON_FAIL(i4_ret);

                    if (INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type
                        && DEV_VTRL_CAST != t_isl_rec.t_avc_info.e_video_type)
                    {
                        DBG_LOG_PRINT(("Switching source to SmartCast.\n"));
                        change_source_way = TRUE;
                    }

                    a_wzd_resume_state_only_c4tv(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS);
                    a_rest_app_launch_cast_to_conjure_apps();

                    // Hide menu
                    menu_leave(FALSE, 0);
                    return MENUR_OK;
                }
                else
                {
                    /* last shadow */
                    menu_pm_get_last_shadow_item(&h_last_shadow_item);
                    i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    if(aui4_page[ui1_page_id] == ui4_g_menu_page_channels)
                    {
                        //_menu_page_atsc_auto_sacn_change_source_to_tv();
                    }
                    //Under 3rd app, when enter user manual, set empty title text.
                    if (aui4_page[ui1_page_id] == ui4_g_menu_page_user_manual)
                    {
                        i4_ret = menu_main_set_title(MLM_MENU_KEY_EMPTY);
                        MENU_CHK_FAIL(i4_ret);
                    }

                    //Disable Audio Menu when bt headphone is connected 
                    if ((MAIN_MENU_ITEM_INDEX_AUD == aui1_items_on_ui[ui1_hlt_index]) 
                        && (ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES] == TRUE)
                        && c_strcmp(headphone_name, "None") && c_strcmp(headphone_name, ""))
                    {
                        DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO : Entry... :  %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));
                        INT32 i4_ret = MENUR_OK;
                        UTF16_T  w2s_title[128] = {0};
                        UINT16 ui2_lang_idx = 0; 
                        ISO_639_LANG_T s639_lang;
                    
                        if (ui4_msg == WGL_MSG_KEY_REPEAT)
                        {
                            return WGLR_OK;
                        }

                        i4_ret = a_cfg_get_gui_lang(s639_lang);
                        if(i4_ret != APP_CFGR_OK)
                        {
                            DBG_INFO(("[%s,%d]a_cfg_get_gui_lang failed\n",__FILE__, __LINE__));
                        }
                        if(c_strncmp(s639_lang,"eng",3) ==0)
                        {
                            ui2_lang_idx = 0; /*ENG*/
                        }
                        else if(c_strncmp(s639_lang,"fre",3) ==0)
                        {
                            ui2_lang_idx = 1; /*FRE*/
                        }
                        else if(c_strncmp(s639_lang,"spa",3) ==0)
                        {
                            ui2_lang_idx = 2; /*SPA*/
                        }
                        else
                        {
                            ui2_lang_idx = 0; /*ENG*/
                        }

                        c_uc_w2s_strncpy(w2s_title, MLM_MENU_TEXT(ui2_lang_idx,MLM_MENU_KEY_MAIN_MENU_AUD_DISABLE), 128);
                        c_uc_w2s_strncat(w2s_title, L"\n", sizeof(L"\n"));
                        i4_ret = menu_disable_audio_settings_show_confirm_dialog_ex(w2s_title,
                                                                MLM_MENU_TEXT(ui2_lang_idx,MLM_MENU_KEY_MAIN_MENU_AUD_DISABLE_CANCEL),   
                                                                MLM_MENU_TEXT(ui2_lang_idx,MLM_MENU_KEY_MAIN_MENU_AUD_DISABLE_DISCONNECT),   
                                                                disable_audio_settings_confirm_dialog_cancel_cb_fct,
                                                                disable_audio_settings_confirm_dialog_disconnect_cb_fct,
                                                                TRUE);
                        DBG_LOG_PRINT(("MAIN_MENU_PAGE_DISABLE_AUDIO : Exit... :  %s,%s,%d, \n", __FILE__, __FUNCTION__, __LINE__));
                    }
                    else
                    {
                        i4_ret=menu_nav_go(aui4_page[ui1_page_id],NULL);
                        MENU_CHK_FAIL(i4_ret);
                    }
                }

            }
            break;
            case BTN_RETURN:
#ifdef APP_MENU_MMP_COEXIST
            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                /* Multimedia */
                a_amb_resume_app(MMP_NAME);
            }
#endif
                /* hide main menu*/
            menu_leave(TRUE, MENU_PM_HIDE_DELAY);
            a_menu_test_patterns_turn_off();
            break;
            case BTN_EXIT:
                menu_leave (FALSE, 0);
                break;

            default:
                break;
        }
        if(b_care_key)
        {
            /* union the rect */
            if(ui1_old_hlt_idx >= ui1_total_page_number)
            {
                return MENUR_FAIL;
            }
            c_wgl_get_coords(ah_list_box[aui1_items_on_ui[ui1_old_hlt_idx]],
                             WGL_COORDS_PARENT,
                             &t_rect_1);

            if(ui1_hlt_index >= ui1_total_page_number)
            {
                return MENUR_FAIL;
            }
            c_wgl_get_coords(ah_list_box[aui1_items_on_ui[ui1_hlt_index]],
                             WGL_COORDS_PARENT,
                             &t_rect_2);
            c_wgl_rect_union(&t_rect_union, &t_rect_1, &t_rect_2);

            /*Need Enhance Help MLM*/
            if (ui1_hlt_index < ui1_total_page_number)
            {
                i4_ret = menu_set_and_show_help_tip(MENU_TEXT(aui2_help_id[aui1_items_on_ui[ui1_hlt_index]]));
                MENU_LOG_ON_FAIL(i4_ret);
            }

            _main_menu_play_tts();
            c_wgl_set_focus(ah_list_box[aui1_items_on_ui[ui1_hlt_index]], WGL_NO_AUTO_REPAINT);
            c_wgl_repaint(h_cnt_frm,&t_rect_union, TRUE);

        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

void set_bt_audio_device_status() {
    /* Update Text is it is allowed to show */
    if(TRUE == ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES])
    {
        UTF16_T w2s_data[256] = {0};
        get_connected_audio_device_from_jsondb(w2s_data);

        INT32 i4_ret = c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES],
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(0,2),
                              WGL_PACK(w2s_data));
        MENU_CHK_FAIL(i4_ret);
        WGL_LB_HLT_ELEM_EFFECT_T t_hlt_elem_effect;
        /* Set long text scroll effect */
        t_hlt_elem_effect.ui4_style = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
        t_hlt_elem_effect.t_text_scrl.ui4_style =
            WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR | WGL_LB_TEXT_SCRL_STL_REPEAT;
        t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
        t_hlt_elem_effect.t_text_scrl.ui4_ms_delay = 180;
        t_hlt_elem_effect.t_text_scrl.b_sync = FALSE;
        i4_ret = c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES], WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK(&t_hlt_elem_effect), NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* If page is already visible, then repaint this control*/
        if(t_main_menu_nw_page_data.b_this_page_show) {
            i4_ret = c_wgl_repaint(ah_list_box[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES], NULL, FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _main_menu_set_text
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
static INT32 _main_menu_set_text(VOID)
{
    INT32               i4_ret = MENUR_OK;
    WGL_COLOR_INFO_T    t_clr_info;
    UINT8               ui1_i = 0;
    UTF16_T             w2s_data[32+1] = {0};
    HANDLE_T            h_network_image= NULL_HANDLE;
    HANDLE_T            h_tv_channels_image= NULL_HANDLE;
    WGL_LB_ITEM_IMG_SUIT_T t_img_suit_network;
    WGL_LB_ITEM_IMG_SUIT_T t_img_suit_tv_channels;


    /* set all item  text */
    for(ui1_i=0; ui1_i < MAIN_MENU_MAX_PAGE_NUM;ui1_i++)
    {
        if(TRUE == ab_items_show[ui1_i])
        {
           i4_ret = c_wgl_do_cmd(ah_list_box[ui1_i],
                                  WGL_CMD_LB_SET_ITEM_TEXT,
                                  WGL_PACK_2(0,1),
                                  WGL_PACK(MENU_TEXT(aui2_msg_id[ui1_i])));
            MENU_CHK_FAIL(i4_ret);

            /*Network access point*/
            if(aui2_msg_id[ui1_i] == MLM_MENU_KEY_MAIN_MENU_NETWORK)
            {
                DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d}: \n", __FUNCTION__,__LINE__ )); );

                _main_menu_update_network_status(&h_network_image,w2s_data);

                i4_ret = c_wgl_do_cmd(ah_list_box[ui1_i],
                                      WGL_CMD_LB_SET_ITEM_TEXT,
                                      WGL_PACK_2(0,2),
                                      WGL_PACK(w2s_data));
                MENU_CHK_FAIL(i4_ret);

                c_memset(&t_img_suit_network, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
                t_img_suit_network.h_normal                         = h_network_image;
                t_img_suit_network.h_disable                        = h_network_image;
                t_img_suit_network.h_highlight                      = h_network_image;
                t_img_suit_network.h_selected_highlight             = h_network_image;
                t_img_suit_network.h_highlight_unfocus              = h_network_image;
                t_img_suit_network.h_pushed                         = h_network_image;
                t_img_suit_network.h_selected                       = h_network_image;
                t_img_suit_network.h_selected_disable               = h_network_image;
                t_img_suit_network.h_selected_highlight_unfocus     = h_network_image;
                t_img_suit_network.h_selected_pushed                = h_network_image;

                i4_ret = c_wgl_do_cmd(ah_list_box[ui1_i],
                                      WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                                      WGL_PACK_2(0,3),
                                      WGL_PACK(&t_img_suit_network));
                MENU_CHK_FAIL(i4_ret);

            }

            /*Check TV Channels gray out icon*/
            if(aui2_msg_id[ui1_i] == MLM_MENU_KEY_TUNER_SET)
            {
                if(_tv_channels_is_enabled())
                {
                    h_tv_channels_image = h_g_menu_img_main_channels;
                }
                else
                {
                    h_tv_channels_image = h_g_menu_img_main_tv_channels_grayed_out;
                }
                c_memset(&t_img_suit_tv_channels, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
                t_img_suit_tv_channels.h_normal                         = h_tv_channels_image;
                t_img_suit_tv_channels.h_disable                        = h_tv_channels_image;
                t_img_suit_tv_channels.h_highlight                      = h_tv_channels_image;
                t_img_suit_tv_channels.h_selected_highlight             = h_tv_channels_image;
                t_img_suit_tv_channels.h_highlight_unfocus              = h_tv_channels_image;
                t_img_suit_tv_channels.h_pushed                         = h_tv_channels_image;
                t_img_suit_tv_channels.h_selected                       = h_tv_channels_image;
                t_img_suit_tv_channels.h_selected_disable               = h_tv_channels_image;
                t_img_suit_tv_channels.h_selected_highlight_unfocus     = h_tv_channels_image;
                t_img_suit_tv_channels.h_selected_pushed                = h_tv_channels_image;

                i4_ret = c_wgl_do_cmd(ah_list_box[ui1_i],
                                      WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                                      WGL_PACK_2(0,0),
                                      WGL_PACK(&t_img_suit_tv_channels));
                MENU_CHK_FAIL(i4_ret);

            }

            /* Set Text Color */
            t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
            if(aui2_msg_id[ui1_i] == MLM_MENU_KEY_TUNER_SET && !_tv_channels_is_enabled())
            {
                t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_gray;
                t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_gray;
                t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_gray;
            }
            else
            {
                t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
                t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
                t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
            }

            i4_ret = c_wgl_do_cmd(ah_list_box[ui1_i],
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(1, WGL_CLR_TEXT),
                                  WGL_PACK(&t_clr_info) );
            MENU_LOG_ON_FAIL(i4_ret);


            i4_ret = c_wgl_do_cmd(ah_list_box[ui1_i],
                                  WGL_CMD_LB_SET_COL_COLOR,
                                  WGL_PACK_2(2, WGL_CLR_TEXT),
                                  WGL_PACK(&t_clr_info) );
            MENU_LOG_ON_FAIL(i4_ret);
        }

    }

    /*load all help mlm*/
    /*
    aui2_help_id[0] = MLM_MENU_KEY_TAB_HELP_PICTURE;
    if (b_2021sku)
    {
        aui2_help_id[1] = MLM_MENU_KEY_TAB_HELP_AUDIO_NO_EQ;
    }
    else
    {
        aui2_help_id[1] = MLM_MENU_KEY_TAB_HELP_AUDIO;
    }
    aui2_help_id[2] = MLM_MENU_KEY_TAB_HELP_NETWORK;
    aui2_help_id[3] = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SIGNAL_SRC;
    aui2_help_id[4] = MLM_MENU_KEY_HELP_TIP_ACCESSIBILITY;
    aui2_help_id[5] = MLM_MENU_KEY_TAB_HELP_SETTINGS_NO_NAME_INPT;
    aui2_help_id[6] = MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET_HELP;
    aui2_help_id[7] = MLM_MENU_KEY_HELP_MANUAL_HELP;*/

    aui2_help_id[0] = MLM_MENU_KEY_BT_HEADPHONES_HELP_TIP;
    aui2_help_id[1] = MLM_MENU_KEY_TAB_HELP_PICTURE;
    if (b_2021sku)
    {
        aui2_help_id[2] = MLM_MENU_KEY_TAB_HELP_AUDIO_NO_EQ;
    }
    else
    {
        aui2_help_id[2] = MLM_MENU_KEY_TAB_HELP_AUDIO;
    }
    aui2_help_id[3] = MLM_MENU_KEY_TAB_HELP_NETWORK;
    aui2_help_id[4] = MLM_MENU_KEY_HELP_TIP_TV_SETTING_SIGNAL_SRC;
    aui2_help_id[5] = MLM_MENU_KEY_HELP_TIP_ACCESSIBILITY;
    aui2_help_id[6] = MLM_MENU_KEY_TAB_HELP_SETTINGS_NO_NAME_INPT;
    aui2_help_id[7] = MLM_MENU_KEY_MAIN_MENU_SYS_INFO_AND_RESET_HELP;
    aui2_help_id[8] = MLM_MENU_KEY_HELP_MANUAL_HELP;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _main_menu_create
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
static INT32 _main_menu_create(VOID)
{
    INT32   i4_ret;
    UINT8   ui1_i;

    ui1_total_page_number = MAIN_MENU_MAX_PAGE_NUM;

    WGL_HIMG_TPL_T   ah_img_nor[MAIN_MENU_MAX_PAGE_NUM]
                        ={h_g_menu_img_main_bt_headphones,
                          h_g_menu_img_main_picture,
                          h_g_menu_img_main_audio,
                          h_g_menu_img_main_network ,
                          h_g_menu_img_main_channels,
                          h_g_menu_img_main_accessiblity,
                          h_g_menu_img_main_system,
                          h_g_menu_img_main_admin,
                          h_g_menu_img_main_user_manual};

     WGL_HIMG_TPL_T   ah_img_hlt[MAIN_MENU_MAX_PAGE_NUM]
                        ={h_g_menu_img_main_bt_headphones,
                          h_g_menu_img_main_picture,
                          h_g_menu_img_main_audio,
                          h_g_menu_img_main_network ,
                          h_g_menu_img_main_channels,
                          h_g_menu_img_main_accessiblity,
                          h_g_menu_img_main_system,
                          h_g_menu_img_main_admin,
                          h_g_menu_img_main_user_manual};
    /* Create all items */
    for(ui1_i=0; ui1_i < MAIN_MENU_MAX_PAGE_NUM; ui1_i++)
    {
        i4_ret =  _menu_list_create(h_cnt_frm,
                                    ui1_i,
                                    _list_item_proc_fct,
                                    &ah_list_box[ui1_i],
                                    ah_img_nor[ui1_i],
                                    ah_img_hlt[ui1_i]);
        MENU_CHK_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _main_menu_refresh(VOID)
{
    INT32       i4_ret             = MENUR_OK;
    UINT8       ui1_idx            = 0;
    UINT8       ui1_i              = 0;
    UINT8       ui1_hide_cnt       = 0;
    GL_RECT_T   t_rect;
    HANDLE_T    h_last_shadow_item = NULL_HANDLE;

    ui1_total_page_number = MAIN_MENU_MAX_PAGE_NUM;

    for (ui1_idx = 0; ui1_idx < MAIN_MENU_MAX_PAGE_NUM; ui1_idx++)
    {
        ab_items_show[ui1_idx] = TRUE;
        aui1_items_on_ui[ui1_idx] = 0xFF;
    }

    /* Enable BT Headphone feature if file exist */
    if( access("/tmp/enable_bt_headphone", F_OK) < 0 ) {
        ui1_total_page_number -= 1;
        ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES] = FALSE;
    }

    if(FALSE == _tuner_is_visible())
    {
        ui1_total_page_number -= 1;
        ab_items_show[MAIN_MENU_ITEM_INDEX_TUNER_SET] = FALSE;
    }

    if (FALSE == _e_manual_visible())
    {
        ui1_total_page_number -= 1;
        ab_items_show[MAIN_MENU_ITEM_INDEX_USER_MANUAL] = FALSE;
    }

    /* Update UI */
    ui1_hide_cnt = 0;
    ui1_i        = 0;

    /*  Bluetooth headphones */
    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(1),
                                   WGL_PACK(300)));

    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(2),
                                   WGL_PACK(150)));
    /* Text Set Alignment */
    MENU_LOG_ON_FAIL( c_wgl_do_cmd (ah_list_box[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES],
                                   WGL_CMD_LB_SET_COL_ALIGN,
                                   WGL_PACK (2),
                                   WGL_PACK (WGL_AS_LEFT_CENTER)));

    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(3),
                                   WGL_PACK(50)));
    /* channel */
    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_TUNER_SET],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(1),
                                   WGL_PACK(300)));

    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_TUNER_SET],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(2),
                                   WGL_PACK(0)));



    /* Accessibility */
    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_ACCESSIBILITY],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(1),
                                   WGL_PACK(300)));

    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_ACCESSIBILITY],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(2),
                                   WGL_PACK(0)));

    /* Admin & Privacy*/
    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_ADMIN_PRIVACY],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(1),
                                   WGL_PACK(300)));

    MENU_LOG_ON_FAIL(c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_ADMIN_PRIVACY],
                                  WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK(2),
                                  WGL_PACK(0)));
    /* USER MANUAL */
    MENU_LOG_ON_FAIL( c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_USER_MANUAL],
                                   WGL_CMD_LB_SET_COL_WIDTH,
                                   WGL_PACK(1),
                                   WGL_PACK(240)));

    MENU_LOG_ON_FAIL(c_wgl_do_cmd(ah_list_box[MAIN_MENU_ITEM_INDEX_USER_MANUAL],
                                  WGL_CMD_LB_SET_COL_WIDTH,
                                  WGL_PACK(2),
                                  WGL_PACK(60)));
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui1_idx = 0; ui1_idx < MAIN_MENU_MAX_PAGE_NUM; ui1_idx++)
    {
        if (TRUE == ab_items_show[ui1_idx])
        {
            MENU_CHK_FAIL(c_wgl_set_visibility(ah_list_box[ui1_idx], WGL_SW_NORMAL));

            SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_LEFT,
                         MENU_ITEM_V_HEIGHT * (ui1_idx - ui1_hide_cnt),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);

            i4_ret = c_wgl_move(ah_list_box[ui1_idx],
                                &t_rect,
                                WGL_NO_AUTO_REPAINT);

            MENU_CHK_FAIL(i4_ret);

            aui1_items_on_ui[ui1_i++] = ui1_idx;
        }
        else
        {
            ui1_hide_cnt++;
            MENU_LOG_ON_FAIL(c_wgl_set_visibility(ah_list_box[ui1_idx], WGL_SW_HIDE));
        }
    }

    /*Adjust last shadow position*/
    t_rect.i4_left   = CONTENT_X;
    t_rect.i4_right  = CONTENT_X + CONTENT_H;
    t_rect.i4_top    = MENU_ITEM_V_HEIGHT * (ui1_idx - ui1_hide_cnt)+ CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT));

    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL));

    _main_menu_set_text();

    return i4_ret;
}

#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT

static VOID _user_manual_staging_proc(VOID* pv_data, SIZE_T  z_data_size)
{
    UINT16 ui2_key_seq_id = *(UINT16*)pv_data;
    UINT32 ui4_cur_page = 0;

    if (menu_nav_get_crnt_page(&ui4_cur_page) != MENUR_OK)
    {
        DBG_ERROR(("<MENU> %s Line %d: return error!\n", __FUNCTION__, __LINE__));
        return;
    }

    if (ui4_cur_page != ui4_g_menu_page_main_menu
        || MAIN_MENU_ITEM_INDEX_USER_MANUAL != aui1_items_on_ui[ui1_hlt_index])
    {
        DBG_INFO(("<MENU> %s Line %d: return error!\n", __FUNCTION__, __LINE__));
        return;
    }

    if (ui2_key_seq_id == aui2_um_key_seq_id[USER_MANUAL_KEY_SEQ_PLAY])
    {
        gb_um_is_staging_mode = TRUE;
        DBG_INFO(("<MENU> %s Line %d: Set user manual staging mode!\n", __FUNCTION__, __LINE__));
    }

    if (ui2_key_seq_id == aui2_um_key_seq_id[USER_MANUAL_KEY_SEQ_STOP])
    {
        gb_um_is_staging_mode = FALSE;
        DBG_INFO(("<MENU> %s Line %d: Clear user manual staging mode!\n", __FUNCTION__, __LINE__));
    }
}

static VOID _user_manual_key_seq_nfy_fct(UINT16 ui2_id, VOID*  pv_tag)
{
    menu_async_invoke(_user_manual_staging_proc, (VOID *)&ui2_id, sizeof(ui2_id), FALSE);
}

#endif
#endif
static  INT32 _menu_time_bar_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    return 0;
}

static INT32 _menu_time_text_init(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget
    )
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T     t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     TIME_BAR_W,
                     TIME_BAR_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_128),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(TITLE_ALIGN),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = TITLE_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 28;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


static INT32 _menu_time_bar_init(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    //WGL_IMG_INFO_T  t_img_info;
    HANDLE_T                 h_frm_main;

    /*backbar*/
    SET_RECT_BY_SIZE(&t_rect,
                     TIME_BAR_X,
                     TIME_BAR_Y,
                     TIME_BAR_W,
                     TIME_BAR_H);
    i4_ret = menu_pm_get_main_frm(&h_frm_main);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = c_wgl_create_widget(h_frm_main,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _menu_time_bar_proc_fct,
                                 255,
                                 (VOID*)(0),
                                 (VOID*)0,
                                 &h_time_frm);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = _menu_time_text_init(h_time_frm,
                            &h_time_txt);
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_visibility(h_time_frm, WGL_SW_HIDE);

    return MENUR_OK;

}

static INT32 _menu_time_text_update(VOID)
{
    INT32           i4_ret;
    UINT8                       time_format;
    DT_COND_T                   t_dt_cond = DT_FREE_RUNNING;
    BOOL                        b_is_get_time    = FALSE;
    DTG_T                       t_loc_dtg        = {0};
    UINT32                      ui4_crnt_time    =  0;
    CHAR*                       ps_am_pm = NULL ;
    CHAR                        s_crnt_time[9]   = {0};  /* HH:MM */
    CHAR                        s_crnt_time_ex[9]= {0};
    UTF16_T                     w2s_crnt_time[9] = {0};


    i4_ret = a_cfg_cust_get_time_format(&time_format);
    MENU_CHK_FAIL(i4_ret);

    c_dt_get_utc(NULL, &t_dt_cond);

    /* first check the system time*/
    b_is_get_time = a_dst_get_local_time(&t_loc_dtg);

    if ((TRUE == b_is_get_time) && (time_format != 1))
    {
        ui4_crnt_time = t_loc_dtg.ui1_hr * 60 + t_loc_dtg.ui1_min ;

        if (t_loc_dtg.ui1_hr > 12)
        {
            t_loc_dtg.ui1_hr %= 12;//0301
            ps_am_pm = "PM ";
        }
        else if (t_loc_dtg.ui1_hr == 12)
        {
            ps_am_pm = "PM ";
        }
        else if (t_loc_dtg.ui1_hr == 0)
        {
            t_loc_dtg.ui1_hr = 12;
            ps_am_pm = "AM ";
        }
        else
        {
            ps_am_pm = "AM ";
        }

        c_memset (s_crnt_time_ex, 0, sizeof(s_crnt_time_ex));
        c_memset (s_crnt_time, 0, sizeof(s_crnt_time));

        /* prepare string to update ITM_TIMER */
        c_sprintf(s_crnt_time, "%d:%02d", t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min);

        c_sprintf(s_crnt_time_ex, "%s %s", s_crnt_time, ps_am_pm);
        c_uc_ps_to_w2s(s_crnt_time_ex, w2s_crnt_time,
                       sizeof(w2s_crnt_time)/sizeof(w2s_crnt_time[0])-1);
    }
    else if(time_format == 1)
    {
        ui4_crnt_time = t_loc_dtg.ui1_hr * 60 + t_loc_dtg.ui1_min ;

        /* prepare string to update ITM_TIMER */
        c_sprintf(s_crnt_time, "%d:%02d", t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min);
        c_uc_ps_to_w2s(s_crnt_time, w2s_crnt_time,
                       sizeof(w2s_crnt_time)/sizeof(w2s_crnt_time[0])-1);

        /* do nothing here*/
    }
    else
    {
        ps_am_pm = " ";

        /* do nothing here*/
    }

    i4_ret = c_wgl_do_cmd(h_time_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_crnt_time,
                          WGL_PACK((UINT16)0x80));
    MENU_CHK_FAIL(i4_ret);
    c_wgl_repaint(h_time_txt, NULL, FALSE);

    // Fix coverity-4697186 Missing return statement
    return MENUR_OK;
}

static VOID _menu_time_timer_action(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    if ((ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES] == TRUE) && ( got_bt_scan_response == FALSE ))
    {
        char *pt_msg = GetRespBTAUDIO_Q( BTAPI_GET_SCAN_LIST );
        if( pt_msg != NULL )
        {
            DBG_LOG_PRINT (("\n%s\n", __FUNCTION__ ));

            _json_bt_db_populate( pt_msg );

            set_bt_audio_device_status();

            free( pt_msg );
            got_bt_scan_response = TRUE;
        }
    }

    _menu_time_text_update();
}

static VOID _menu_time_timer_nfy_fct(HANDLE_T  pt_tm_handle,
                                  VOID*     pv_tag)
{
    menu_request_context_switch(_menu_time_timer_action,NULL,NULL,NULL);
    return;
}

static INT32 _menu_time_timer_start(VOID)
{
    INT32 i4_ret;
    i4_ret = c_timer_start(h_time_timer,
                           1000,
                           X_TIMER_FLAG_REPEAT,
                           _menu_time_timer_nfy_fct,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    return  MENUR_OK ;
}

static INT32 _menu_time_timer_stop(VOID)
{
    INT32 i4_ret;
    i4_ret = c_timer_stop(h_time_timer);
    return i4_ret == OSR_OK ? MENUR_OK : MENUR_FAIL;
}


/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret = 0;
    CHAR        s_tv_name[MAX_TV_NAME_LEN+1] = {0};
    UINT32      ui4_len = MAX_TV_NAME_LEN;
    UTF16_T     w2s_tmp_str[128] = {0};

    c_memset(&t_main_menu_nw_page_data, 0, sizeof(MAIN_MENU_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_tv_name(s_tv_name,&ui4_len);
    DBG_LOG_PRINT (("\n[menu_tv_name] _get_tv_name_text() s_tv_name[%s],ui4_len[%d]\n",s_tv_name,ui4_len));
    MENU_LOG_ON_FAIL(i4_ret);
    c_uc_ps_to_w2s(s_tv_name, w2s_tmp_str, c_strlen(s_tv_name));

    i4_ret = menu_main_set_title_text(w2s_tmp_str);
    MENU_CHK_FAIL(i4_ret);

    MENU_CHK_FAIL(_menu_time_bar_init());

    i4_ret = _main_menu_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _main_menu_set_text();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _main_menu_set_back_bar_image(TRUE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _confirm_dialog_create();
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT
    a_key_seq_reg(ui4_um_key_seq_play,
                  MENU_PAGE_USER_MANUAL_KEY_SEQ_LEN,
                  _user_manual_key_seq_nfy_fct,
                  (VOID *)NULL,
                  &aui2_um_key_seq_id[USER_MANUAL_KEY_SEQ_PLAY]);

    a_key_seq_reg(ui4_um_key_seq_stop,
                  MENU_PAGE_USER_MANUAL_KEY_SEQ_LEN,
                  _user_manual_key_seq_nfy_fct,
                  (VOID *)NULL,
                  &aui2_um_key_seq_id[USER_MANUAL_KEY_SEQ_STOP]);
#endif
#endif

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);
    /* Create Timer */
    i4_ret = c_timer_create(&h_time_timer);
    if(i4_ret != OSR_OK)
    {
        DBG_ERROR(("<MENU>Can't create timer\r\n"));
    }


    //b_2021sku = a_cfg_cust_Is_CurModel_2021();
    b_2021sku = a_cfg_cust_Is_CurModel_after_2021_J();

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    /* un-register show signal level key sequence */
    _page_show_test_page_key_seq_unreg();
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _main_menu_update_network_status
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


/*----------------------------------------------------------------------------
 * Name: _main_menu_nw_notify_handler
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
static VOID _main_menu_nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    __MAIN_MENU_NW_NFY_DATA* pt_nw_nfy_data = (__MAIN_MENU_NW_NFY_DATA*)pv_data;
    INT32       i4_ret = 0;

    NW_NFY_ID_T e_NW_NFY_ID_T = pt_nw_nfy_data->e_nfy_id;

    switch(e_NW_NFY_ID_T)
    {
        case NW_NFY_ID_ETHERNET_UNPLUG:
        case NW_NFY_ID_ETHERNET_PLUGIN:
        {
            DBG_INFO(("\n=========_main_menu_nw_notify_handler==============%d\n",__LINE__));

            DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d}: ETHERNET_UNPLUG/PLUGIN: , PID:%d, TID:%d\n",
                __FUNCTION__,__LINE__, getpid(), MApi_Sys_get_thread_id() )); );

            _main_menu_set_text();
            i4_ret = c_wgl_repaint(ah_list_box[MAIN_MENU_ITEM_INDEX_NETWORK], NULL, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }

        case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
#ifdef APP_NETWORK_WIFI_SUPPORT
        case NW_NFY_ID_WLAN_ASSOCIATE:
#endif
        {
            WLAN_NOTIFY_MSG_T eWLAN_NOTIFY_MSG = (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param);

            DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d}: WLAN_ASSOCIATE/DHCP_SUCCESS_DHCPv4: nty_id:%d, MSG:%d,PID:%d, TID:%d\n",
                    __FUNCTION__,__LINE__, e_NW_NFY_ID_T, eWLAN_NOTIFY_MSG, getpid(), MApi_Sys_get_thread_id() )); );

            if( (eWLAN_NOTIFY_MSG == WLAN_NFY_MSG_OK)
              ||(eWLAN_NOTIFY_MSG == WLAN_NFY_MSG_DISCONNECTED)
              )
            {
                _main_menu_set_text();

                i4_ret = c_wgl_repaint(ah_list_box[MAIN_MENU_ITEM_INDEX_NETWORK], NULL, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                return;
            }
            else
            {
                DEBUG_MAIN_NETWORK( DBG_LOG_PRINT(("[MENU][NETWORK] {%s,%d}: WLAN_ASSOCIATE/DHCP_SUCCESS_DHCPv4: nty_id:%d, MSG:%d  no handle~\n",
                        __FUNCTION__,__LINE__, e_NW_NFY_ID_T, eWLAN_NOTIFY_MSG )); );
            }
            break;
        }

        default:
            return;
    }

    //MENU_LOG_ON_FAIL(c_wgl_repaint(ah_list_box[MAIN_MENU_ITEM_INDEX_NETWORK], NULL, TRUE));

    return;
}


/*----------------------------------------------------------------------------
 * Name: _main_menu_nw_notify_callback
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

static VOID _main_menu_nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    __MAIN_MENU_NW_NFY_DATA t_nw_nfy_data;

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    menu_async_invoke(_main_menu_nw_notify_handler,&t_nw_nfy_data,sizeof(__MAIN_MENU_NW_NFY_DATA),TRUE);
}

#ifdef APP_ZOOM_MODE_SUPPORT
static UINT8 _main_menu_get_focus_hlt_idx(VOID)
{
    UINT8 ui1_i = 0;

    MENU_LOG_ON_FAIL(a_cfg_custom_get_main_menu_pre_item(&ui1_pre_item_idx));

    if (ui1_hlt_index < MAIN_MENU_MAX_PAGE_NUM)
    {
        for (ui1_i = 0; ui1_i < MAIN_MENU_MAX_PAGE_NUM; ui1_i++)
        {
            if (aui1_items_on_ui[ui1_i] == ui1_pre_item_idx)
            {
                ui1_hlt_index = ui1_i;
                break;
            }
        }

        if ((ui1_pre_item_idx == MAIN_MENU_ITEM_INDEX_TUNER_SET)&&(FALSE == _tuner_is_visible() || !_tv_channels_is_enabled()))
        {
            ui1_hlt_index = MAIN_MENU_ITEM_INDEX_NETWORK;
            ui1_pre_item_idx = MAIN_MENU_ITEM_INDEX_NETWORK;
            a_cfg_custom_set_main_menu_pre_item(ui1_pre_item_idx);
        }
    }
    else
    {
        ui1_hlt_index = 0;
    }

    return ui1_hlt_index;
}
#endif

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32 i4_ret;
    GL_RECT_T       t_rect;
    //INT32 ui1_idx;
    MAIN_MENU_PAGE_DATA_T* pt_page_data = &t_main_menu_nw_page_data;
    CHAR        s_tv_name[MAX_TV_NAME_LEN+1] = {0};
    UINT32      ui4_len = MAX_TV_NAME_LEN;
    UTF16_T     w2s_tmp_str[128] = {0};


#ifdef APP_ZOOM_MODE_SUPPORT
    /* pre-select target zoom sector */
    if (menu_get_cond() != MENU_COND_SHOW && !t_g_menu_common.b_is_hot_key_enter)
    {
        UINT8   ui1_hlt_idx = _main_menu_get_focus_hlt_idx();

        a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DEFAULT));

        if (ui1_hlt_idx <= 5)
        {
            a_zoom_mode_select_sector(ZOOM_SECTOR_ITEM_1, TRUE);
        }
        else
        {
            a_zoom_mode_select_sector(ZOOM_SECTOR_ITEM_4, TRUE);
        }
    }
#endif
    i4_ret = a_cfg_custom_get_tv_name(s_tv_name,&ui4_len);
    DBG_LOG_PRINT (("\n[menu_tv_name] _get_tv_name_text() s_tv_name[%s],ui4_len[%d]\n",s_tv_name,ui4_len));
    MENU_LOG_ON_FAIL(i4_ret);
    c_uc_ps_to_w2s(s_tv_name, w2s_tmp_str, c_strlen(s_tv_name));

    i4_ret = menu_main_set_title_text(w2s_tmp_str);
    MENU_CHK_FAIL(i4_ret);
    /* register network call back */
    i4_ret = a_nw_register(_main_menu_nw_notify_callback, (VOID*)pt_page_data, &pt_page_data->ui4_nw_nfy_id );
    MENU_LOG_ON_FAIL(i4_ret);

    /* register show test page key sequence */
    if (pt_page_data->ui2_show_test_page_key_id == 0)
    {
        _page_show_test_page_key_seq_reg();
    }

    /* show main menu */
    menu_main_set_visibility(TRUE);

    SET_RECT_BY_SIZE(&t_rect,
                     CONTENT_X,
                     CONTENT_Y ,
                     CONTENT_W,
                     CONTENT_H);

    i4_ret = c_wgl_move(h_cnt_frm,
                        &t_rect,
                        FALSE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _main_menu_set_back_bar_image(TRUE);
    MENU_CHK_FAIL(i4_ret);

    _main_menu_refresh();

    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_cnt_frm, WGL_SW_NORMAL));
    MENU_LOG_ON_FAIL(c_wgl_repaint(h_cnt_frm,NULL,TRUE));

    /*Fake For Homebar icon*/
    i4_ret = menu_main_set_main_title_visibility(FALSE);
    MENU_CHK_FAIL(i4_ret);

    t_main_menu_nw_page_data.b_this_page_show = TRUE;

    set_delay_lock_cust_pic_mode_status(TRUE);


    MENU_LOG_ON_FAIL(_menu_time_text_update());

    if ((ab_items_show[MAIN_MENU_ITEM_INDEX_BT_HEADPHONES] == TRUE) && ( got_bt_scan_response == FALSE ))
        SendReqBTAUDIO_Q( BTAPI_GET_SCAN_LIST, NULL );

    MENU_LOG_ON_FAIL(_menu_time_timer_start());

    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_time_frm, WGL_SW_RECURSIVE));


    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32 i4_ret;

    MAIN_MENU_PAGE_DATA_T* pt_page_data = &t_main_menu_nw_page_data;

    /*unregister network message callback*/
    i4_ret = a_nw_unregister(pt_page_data->ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    HANDLE_T    h_frm_main = NULL_HANDLE;

    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        i4_ret = menu_pm_get_main_frm(&h_frm_main);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_float(h_frm_main, FALSE, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif
    i4_ret = menu_set_and_trigger_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _main_menu_set_back_bar_image(FALSE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm, WGL_SW_HIDE_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
    /*Fake For Homebar icon*/
    i4_ret = menu_main_set_main_title_visibility(FALSE);
    MENU_CHK_FAIL(i4_ret);

    t_main_menu_nw_page_data.b_this_page_show = FALSE;

    MENU_LOG_ON_FAIL(a_cfg_custom_set_main_menu_pre_item(ui1_pre_item_idx));
    c_wgl_set_visibility(h_time_frm, WGL_SW_HIDE);
    i4_ret = _menu_time_timer_stop();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    UINT8 ui1_i = 0;

    MENU_LOG_ON_FAIL(a_cfg_custom_get_main_menu_pre_item(&ui1_pre_item_idx));

    if (ui1_hlt_index < MAIN_MENU_MAX_PAGE_NUM)
    {
        for (ui1_i = 0; ui1_i < MAIN_MENU_MAX_PAGE_NUM; ui1_i++)
        {
            if (aui1_items_on_ui[ui1_i] == ui1_pre_item_idx)
            {
                ui1_hlt_index = ui1_i;
                break;
            }
        }

        if ((ui1_pre_item_idx == MAIN_MENU_ITEM_INDEX_TUNER_SET)&&(FALSE == _tuner_is_visible()))
        {
            ui1_hlt_index = MAIN_MENU_ITEM_INDEX_TIMERS;
            ui1_pre_item_idx = MAIN_MENU_ITEM_INDEX_TIMERS;
            a_cfg_custom_set_main_menu_pre_item(ui1_pre_item_idx);
        }


        i4_ret = c_wgl_set_focus(ah_list_box[aui1_items_on_ui[ui1_hlt_index]], WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
        if (!menu_custom_is_blank_screen())
        {
            _main_menu_play_tts();
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    menu_disable_audio_settings_hide_confirm_dialog(TRUE);
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    UINT32 ui4_crnt_page_id;

    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret =_main_menu_set_text();
        MENU_LOG_ON_FAIL(i4_ret);

        menu_nav_get_crnt_page(&ui4_crnt_page_id);

        if (ui4_crnt_page_id == ui4_g_menu_page_main_menu)
        {
            i4_ret = menu_set_help_tip(MENU_TEXT(aui2_help_id[aui1_items_on_ui[ui1_hlt_index]]));
            MENU_LOG_ON_FAIL(i4_ret);

            menu_pm_repaint();
        }
    }

    return MENUR_OK;
}

extern INT32 menu_page_ex_main_menu_init(VOID)
{
    t_g_menu_page_ex_main_menu.pf_menu_page_create      = _on_page_create;
    t_g_menu_page_ex_main_menu.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_page_ex_main_menu.pf_menu_page_show        = _on_page_show;
    t_g_menu_page_ex_main_menu.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_page_ex_main_menu.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_page_ex_main_menu.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_page_ex_main_menu.pf_menu_page_update      = _on_page_update;

    return MENUR_OK;
}

extern INT32 main_menu_set_hlt_index(UINT8  ui1_value)
{
    ui1_pre_item_idx = ui1_value;
    if ((ui1_pre_item_idx == MAIN_MENU_ITEM_INDEX_TUNER_SET)&&(FALSE == _tuner_is_visible()))
    {
        ui1_pre_item_idx = MAIN_MENU_ITEM_INDEX_TIMERS;
        a_cfg_custom_set_main_menu_pre_item(ui1_pre_item_idx);
    }
    else
    {
        a_cfg_custom_set_main_menu_pre_item(ui1_pre_item_idx);
    }
    return MENUR_OK;
}

extern BOOL menu_cc_is_visible(VOID)
{
    return (_cc_is_visible() || _cc_is_support_ipcc());
}

extern BOOL a_menu_cc_is_support_ipcc(VOID)
{
    return _cc_is_support_ipcc();
}

#endif /* COMMON_EX_MAIN_MENU_ENABLE */


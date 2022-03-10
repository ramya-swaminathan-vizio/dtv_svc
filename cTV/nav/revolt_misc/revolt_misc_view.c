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
 * $RCSfile: revolt_misc_system_info_view.c,v $
 * $Revision: #1 $
 * $Date: 2016/01/21 $
 * $Author: sin_fangyuan $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX:  $
 *
 * Description:
 *       System Info
 *
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>


#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_common.h"
#include "u_sys_name.h"
#include "u_sm_audio_hdlr.h"
#include "u_svl.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_raised.h"
#include "u_wgl_tools.h"
#include "u_dbg.h"
#include "u_pcl.h"
#include "u_gl.h"
#include "u_net_wlan.h"
#include "u_drv_cust.h"
#include "c_common.h"
#include "c_os.h"
#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl_image.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_dbg.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_tsl.h"
#include "c_wgl.h"
#include "c_pcl.h"
#include "c_speedtest_async.h"
#include "c_rm.h"

#include "app_util/a_key_seq.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_network.h"
//#include "wizard/wzd_util.h"

#include "nav/nav_common.h"
#include "nav/dialog/nav_dialog.h"
#include "nav/revolt_misc/revolt_misc.h"
#include "nav/revolt_misc/revolt_misc_view.h"
#include "nav/revolt_misc/test_page_view.h"
#include "nav/pop/a_pop.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"

#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_colors.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/network/network_custom.h"

#include "menu2/menu_common/menu_common.h"

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#include "app_util/uli/uli_custom.h"
#endif

#include "rest/a_rest.h"
#include "app_util/a_cec.h"
#include "nav/cec2/a_nav_cec.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "c_fm.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define RET_ON_ERR(_expr)  \
{ \
    INT32 expr = _expr; \
    if(expr != 0)\
    {\
        DBG_LOG_PRINT(("<REVOLT_MISC_VIEW> ERR: file = %s, line = %d,%d\n\r", __FILE__, __LINE__,expr)); \
        return expr;\
    } \
}

typedef struct _OSD_CONTENT_T
{
    GL_HSCREEN_T    h_screen;
    GL_HPLANE_T     h_plane;
    HANDLE_T        h_canvas;
    UINT32          ui4_canvas_width;
    UINT32          ui4_canvas_height;

    /* widget */
    HANDLE_T        h_main_frame;   /* Main frame */
    HANDLE_T        h_left_title;
    HANDLE_T        h_left_title_cont;
    HANDLE_T        h_right_title;
    HANDLE_T        h_left_list_box;
    HANDLE_T        h_left_up_list_box;
    HANDLE_T        h_center_list_box;
    HANDLE_T        h_right_list_box;
    WGL_HIMG_TPL_T  h_bk_img_tpl;
    BOOL            b_is_show;
    UINT8           ui1_hdmi_cnt;
} OSD_CONTENT_T;

typedef enum _LEFT_UP_SYS_INFO_ROWNUM
{
    LEFT_SYS_INFO_ROW_SERIAL_NUMBER = 0,
    LEFT_SYS_INFO_ROW_MODEL_NAME,
    LEFT_SYS_INFO_ROW_VERSION,
    LEFT_SYS_INFO_ROW_CAST_VERSION,
    LEFT_SYS_INFO_ROW_CHROMIUM_VERSION,
//    LEFT_SYS_INFO_ROW_FRC_VERSION,
    LEFT_SYS_INFO_ROW_NETFLIX_ESN,

    U_LEFT_SYS_INFO_ROW_LAST_NUM
}LEFT_UP_SYS_INFO_ROWNUM;


typedef enum _LEFT_SYS_INFO_ROWNUM
{
    LEFT_SYS_INFO_ROW_ESN = 0,
    LEFT_SYS_INFO_ROW_SV,
    LEFT_SYS_INFO_ROW_REG,
    LEFT_SYS_INFO_ROW_NP,
    LEFT_SYS_INFO_ROW_UID,
    LEFT_SYS_INFO_ROW_DA,
    LEFT_SYS_INFO_ROW_DEV_ID,
    LEFT_SYS_INFO_ROW_PROV_ID,
    LEFT_SYS_INFO_ROW_HDR,
    LEFT_SYS_INFO_ROW_MODEL_GROUP,

    LEFT_SYS_INFO_ROW_LAST_NUM
}LEFT_SYS_INFO_ROWNUM;

typedef enum _CENTER_SYS_INFO_ROWNUM
{
    CENTER_SYS_INFO_ROW_CONNECTION = 0,
    CENTER_SYS_INFO_ROW_SSID,
    CENTER_SYS_INFO_ROW_IP,
    CENTER_SYS_INFO_ROW_GATEWAY,
    CENTER_SYS_INFO_ROW_SUBNET,
    CENTER_SYS_INFO_ROW_PREF_DNS,
    CENTER_SYS_INFO_ROW_ALT_DNS,
    CENTER_SYS_INFO_ROW_SECURITY_TYPE,
    CENTER_SYS_INFO_ROW_DOWNLOAD_SPEED,
    CENTER_SYS_INFO_ROW_WIFI_RSSI,
    CENTER_SYS_INFO_ROW_WIFI_CHANNEL,
    CENTER_SYS_INFO_ROW_RJ45_MAC,
    CENTER_SYS_INFO_ROW_WLAN_MAC,
    //CENTER_SYS_INFO_ROW_BT_MAC,
    //CENTER_SYS_INFO_ROW_BT_DEVICES,

    CENTER_SYS_INFO_ROW_LAST_NUM
}CENTER_SYS_INFO_ROWNUM;

typedef enum _RIGHT_SYS_INFO_ROWNUM
{
    RIGHT_SYS_INFO_ROW_TUNNER = 0,
    RIGHT_SYS_INFO_ROW_RESOLUTION,
    RIGHT_SYS_INFO_ROW_VERT_FREQUENCY,
    RIGHT_SYS_INFO_ROW_AUDIO_TYPE,
    RIGHT_SYS_INFO_ROW_PHYSICAL_CHANNEL,
    RIGHT_SYS_INFO_ROW_FREQUENCY,
    RIGHT_SYS_INFO_ROW_MODULATION,
    RIGHT_SYS_INFO_ROW_SIGNAL_STRENGTH,
//    RIGHT_SYS_INFO_ROW_CAST,
    RIGHT_SYS_INFO_ROW_HDMI_1,
    RIGHT_SYS_INFO_ROW_HDMI_2,
    RIGHT_SYS_INFO_ROW_HDMI_3,
    RIGHT_SYS_INFO_ROW_HDMI_4,
    RIGHT_SYS_INFO_ROW_COMP,
    RIGHT_SYS_INFO_ROW_USB,

    RIGHT_SYS_INFO_ROW_LAST_NUM
}RIGHT_SYS_INFO_ROWNUM;

typedef struct _NAV_TEST_PAGE_DATA_T
{
    UINT32       ui4_nw_nfy_id;
    BOOL         b_this_page_show;

    UINT16      ui2_show_test_page_key_id;
}NAV_TEST_PAGE_DATA_T;


#define REVOLT_FRAME_WIDTH                     (1558)
#define REVOLT_FRAME_HEIGHT                    (800)
#define REVOLT_FRAME_X                         (180)
#define REVOLT_FRAME_Y                         (180)

#define LEFT_TITLE_WIDTH                       (450)
#define LEFT_TITLE_HEIGHT                      (40)
#define LEFT_TITLE_X                           (25)
#define LEFT_TITLE_Y                           (10)

#define LEFT_CONT_WIDTH                        (200)
#define LEFT_CONT_HEIGHT                       (40)
#define LEFT_CONT_X                            (470)
#define LEFT_CONT_Y                            (10)

#define RIGHT_TITLE_WIDTH                       (400)
#define RIGHT_TITLE_HEIGHT                      (LEFT_TITLE_HEIGHT)
#define RIGHT_TITLE_X                           (REVOLT_FRAME_WIDTH - 400)
#define RIGHT_TITLE_Y                           (LEFT_TITLE_Y)

#define LEFT_UP_LB_WIDTH                        (650)
#define LEFT_UP_LB_HEIGHT                       (390)
#define LEFT_UP_LB_X                            (LEFT_TITLE_X)
#define LEFT_UP_LB_Y                            (LEFT_TITLE_Y + 50)

#define LEFT_LB_WIDTH                           (650)
#define LEFT_LB_HEIGHT                          (400)
#define LEFT_LB_X                               (LEFT_TITLE_X)
#define LEFT_LB_Y                               (350)

#define CENTER_LB_WIDTH                         (450 )
#define CENTER_LB_HEIGHT                        (600)
#define CENTER_LB_X                             (LEFT_LB_X + LEFT_LB_WIDTH)
#define CENTER_LB_Y                             (LEFT_TITLE_Y + 50)

#define RIGHT_LB_WIDTH                          (500)
#define RIGHT_LB_HEIGHT                         (600)
#define RIGHT_LB_X                              (CENTER_LB_X + CENTER_LB_WIDTH)
#define RIGHT_LB_Y                              (LEFT_TITLE_Y + 50)


#define COLS_WIDTH                              (500)

#define FE_FNT_SIZE_CUSTOM_LB                   (30)
#define SYS_INFO_TIMER                          (1000)


#define NAV_TEXT(key)   \
            MLM_NAV_TEXT(ui2_g_nav_curr_lang, (key))

#define SVCTX_NAME_MAIN         "main_svctx"
#define SVCTX_NAME_SUB          "sub_svctx"

#define NAV_UPDATER_ULI_STATUS_MASK_REGISTERED                         0x0001
#define NAV_UPDATER_ULI_STATUS_MASK_FACTORY_TEST_MODE                  0x0002
#define NAV_UPDATER_ULI_STATUS_MASK_FIELD_TEST_MODE                    0x0004
#define NAV_UPDATER_ULI_STATUS_MASK_LOOP_TEST_MODE                     0x0008

/* CUST TUNER MODEL TYPE */
#define CUST_TUNER_SILABS_SI2151  0x8F
#define CUST_TUNER_NXP_TDA182I5a  0x91

#define CUST_TUNER_TYPE_MAX_LEN       (16)
#define CUST_TUNER_TYPE_NAME_MAX_LEN  (128)

/*          USB              */
#define SYS_INFO_PAGE_MAX_NAME_LEN	  ((INT32)128)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static OSD_CONTENT_T            tg_view = {0};
static HANDLE_T                 h_signal_timer = NULL_HANDLE;
static UINT16                   ui2_g_nav_curr_lang = 0;

GL_COLOR_T                      t_g_lb_color_white = { 255, { 255 }, { 255 }, { 255 }};
GL_COLOR_T                      t_g_bk_color_black = { 255, { 0 }, { 0 }, { 0 }};
static UINT16                   a_g_up_left_sys_info_idx[U_LEFT_SYS_INFO_ROW_LAST_NUM+1] = {0};
static UINT16                   a_g_left_sys_info_idx[LEFT_SYS_INFO_ROW_LAST_NUM+1] = {0};
static UINT16                   a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_LAST_NUM+1] = {0};
static UINT16                   a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_LAST_NUM+1] = {0};

static BOOL     ab_up_left_item_show_flag[U_LEFT_SYS_INFO_ROW_LAST_NUM] = {1};
static BOOL     ab_left_item_show_flag[LEFT_SYS_INFO_ROW_LAST_NUM] = {1};
static BOOL     ab_center_item_show_flag[CENTER_SYS_INFO_ROW_LAST_NUM] = {1};
static BOOL     ab_right_item_show_flag[RIGHT_SYS_INFO_ROW_LAST_NUM] = {1};

static UINT16   aui2_up_left_item_show[] =
{
    LEFT_SYS_INFO_ROW_SERIAL_NUMBER,
    LEFT_SYS_INFO_ROW_MODEL_NAME,
    LEFT_SYS_INFO_ROW_VERSION,
    LEFT_SYS_INFO_ROW_CAST_VERSION,
    LEFT_SYS_INFO_ROW_CHROMIUM_VERSION,
//    LEFT_SYS_INFO_ROW_FRC_VERSION,
    LEFT_SYS_INFO_ROW_NETFLIX_ESN,
};

static UINT16   aui2_left_item_show[] =
{
    LEFT_SYS_INFO_ROW_ESN,
    LEFT_SYS_INFO_ROW_SV,
    LEFT_SYS_INFO_ROW_REG,
    LEFT_SYS_INFO_ROW_NP,
    LEFT_SYS_INFO_ROW_UID,
    LEFT_SYS_INFO_ROW_DA,
    LEFT_SYS_INFO_ROW_DEV_ID,
    LEFT_SYS_INFO_ROW_PROV_ID,
    LEFT_SYS_INFO_ROW_HDR,
    LEFT_SYS_INFO_ROW_MODEL_GROUP,
};

static UINT16   aui2_center_item_show[] =
{
    CENTER_SYS_INFO_ROW_CONNECTION,
    CENTER_SYS_INFO_ROW_SSID,
    CENTER_SYS_INFO_ROW_IP,
    CENTER_SYS_INFO_ROW_GATEWAY,
    CENTER_SYS_INFO_ROW_SUBNET,
    CENTER_SYS_INFO_ROW_PREF_DNS,
    CENTER_SYS_INFO_ROW_ALT_DNS,
    CENTER_SYS_INFO_ROW_SECURITY_TYPE,
    CENTER_SYS_INFO_ROW_DOWNLOAD_SPEED,
    CENTER_SYS_INFO_ROW_WIFI_RSSI,
    CENTER_SYS_INFO_ROW_WIFI_CHANNEL,
    CENTER_SYS_INFO_ROW_RJ45_MAC,
    CENTER_SYS_INFO_ROW_WLAN_MAC,
    //CENTER_SYS_INFO_ROW_BT_MAC,
    //CENTER_SYS_INFO_ROW_BT_DEVICES,
};

static UINT16   aui2_right_item_show[] =
{
    RIGHT_SYS_INFO_ROW_TUNNER,
    RIGHT_SYS_INFO_ROW_RESOLUTION,
    RIGHT_SYS_INFO_ROW_VERT_FREQUENCY,
    RIGHT_SYS_INFO_ROW_AUDIO_TYPE,
    RIGHT_SYS_INFO_ROW_PHYSICAL_CHANNEL,
    RIGHT_SYS_INFO_ROW_FREQUENCY,
    RIGHT_SYS_INFO_ROW_MODULATION,
    RIGHT_SYS_INFO_ROW_SIGNAL_STRENGTH,
//    RIGHT_SYS_INFO_ROW_CAST,
    RIGHT_SYS_INFO_ROW_HDMI_1,
    RIGHT_SYS_INFO_ROW_HDMI_2,
    RIGHT_SYS_INFO_ROW_HDMI_3,
    RIGHT_SYS_INFO_ROW_HDMI_4,
    RIGHT_SYS_INFO_ROW_COMP,
    RIGHT_SYS_INFO_ROW_USB,
};

static UINT16 aui_up_left_mlm[U_LEFT_SYS_INFO_ROW_LAST_NUM] = {
                                                MLM_NAV_KEY_NAV_SYS_INFO_SERIAL_NAME,
                                                MLM_NAV_KEY_NAV_SYS_INFO_MODEL_NAME,
                                                MLM_NAV_KEY_NAV_SYS_INFO_VERSION,
                                                MLM_NAV_KEY_NAV_SYS_INFO_CAST_VERSION,
                                                MLM_NAV_KEY_SYS_INFO_CHROMIUM_VISION,
//                                                MLM_NAV_KEY_NAV_SYS_INFO_FRC_VERSION,
                                                MLM_NAV_KEY_NAV_SYS_INFO_NETFLIX_ESN};

static UINT16 aui_left_mlm[LEFT_SYS_INFO_ROW_LAST_NUM] = {
                                                MLM_NAV_KEY_SYS_INFO_UTV_ESN,
                                                MLM_NAV_KEY_NAV_SYS_INFO_SV,
                                                MLM_NAV_KEY_NAV_SYS_INFO_REG,
                                                MLM_NAV_KEY_NAV_SYS_INFO_NP,
                                                MLM_NAV_KEY_NAV_SYS_INFO_UID,
                                                MLM_NAV_KEY_NAV_SYS_INFO_UTV_DA,
                                                MLM_NAV_KEY_NAV_SYS_INFO_UTV_DEV_ID,
                                                MLM_NAV_KEY_NAV_SYS_INFO_UTV_PROV_ID,
                                                MLM_NAV_KEY_NAV_SYS_INFO_HDR,
                                                MLM_NAV_KEY_NAV_SYS_INFO_MODEL_GROUP};


static UINT16 aui_center_mlm[CENTER_SYS_INFO_ROW_LAST_NUM] = {
                                                MLM_NAV_KEY_NAV_SYS_INFO_CONNECTION,
                                                MLM_NAV_KEY_NAV_SYS_INFO_SSID,
                                                MLM_NAV_KEY_NAV_SYS_INFO_IP,
                                                MLM_NAV_KEY_NAV_SYS_INFO_GATEWAY,
                                                MLM_NAV_KEY_NAV_SYS_INFO_SUBNET,
                                                MLM_NAV_KEY_NAV_SYS_INFO_PREF_DNS,
                                                MLM_NAV_KEY_NAV_SYS_INFO_ALT_DNS,
                                                MLM_NAV_KEY_NAV_SYS_INFO_SECURITY_TYPE,
                                                MLM_NAV_KEY_NAV_SYS_INFO_DOWNLOAD_SPEED,
                                                MLM_NAV_KEY_NAV_SYS_INFO_WIFI_RSSI,
                                                MLM_NAV_KEY_NAV_SYS_INFO_WIFI_CHANNEL,
                                                MLM_NAV_KEY_NAV_SYS_INFO_RJ45_MAC,
                                                MLM_NAV_KEY_NAV_SYS_INFO_WLAN_MAC
                                                //MLM_NAV_KEY_NAV_SYS_INFO_BT_MAC,
                                                //MLM_NAV_KEY_NAV_SYS_INFO_BT_DEVICES
                                                };
static UINT16 aui_right_mlm[RIGHT_SYS_INFO_ROW_LAST_NUM] = {
                                            MLM_NAV_KEY_NAV_SYS_INFO_TUNNER,
                                            MLM_NAV_KEY_NAV_SYS_INFO_RESOLUTION,
                                            MLM_NAV_KEY_NAV_SYS_INFO_VERT_FREQUENCY,
                                            MLM_NAV_KEY_NAV_SYS_INFO_AUDIO_TYPE,
                                            MLM_NAV_KEY_NAV_SYS_INFO_PHYSICAL_CHANNEL,
                                            MLM_NAV_KEY_NAV_SYS_INFO_FREQUENCY,
                                            MLM_NAV_KEY_NAV_SYS_INFO_MODULATION,
                                            MLM_NAV_KEY_NAV_SYS_INFO_SIGNAL_STRENGTH,
//                                            MLM_NAV_KEY_NAV_SYS_INFO_CAST,
                                            MLM_NAV_KEY_NAV_SYS_INFO_HDMI_1,
                                            MLM_NAV_KEY_NAV_SYS_INFO_HDMI_2,
                                            MLM_NAV_KEY_NAV_SYS_INFO_HDMI_3,
                                            MLM_NAV_KEY_NAV_SYS_INFO_HDMI_4,
                                            MLM_NAV_KEY_NAV_SYS_INFO_COMP,
                                            MLM_NAV_KEY_NAV_SYS_INFO_USB
                                            };


static NAV_TEST_PAGE_DATA_T       t_nav_test_page_data;
static INT32    i4_g_speed = 0;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

static INT32 _revolt_misc_wgl_main_frame_attr_init(VOID);
static INT32 _revolt_misc_wgl_left_title_attr_init(VOID);

static INT32 _revolt_misc_wgl_right_title_attr_init(VOID);


static INT32 _revolt_misc_view_init_widgets(VOID);

static INT32 _lb_update_first_elem(VOID);

static UINT32 _ver_info_idx_remapping(VOID);

extern CHAR* sys_cust_get_usb_upg_version(VOID);

extern CHAR*  sys_cust_get_cust_serial( VOID );


static VOID _int_to_w2s(UTF16_T* w2s_dst,
                  INT32 i4_src,
                  UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}

static INT32 _get_comp( DRV_CUSTOM_CUST_SPEC_TYPE_T drv_type, VOID* pv_data, SIZE_T z_size)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    INT32                        i4_ret = 0;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    /* set operation type */
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = drv_type;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = pv_data;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if (i4_ret < 0)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }

    return i4_ret;
}

static INT32 _sys_info_update_list_box_item(HANDLE_T h_list_box,
                                   UINT32   ui4_idx,
                                   CHAR*    s_value)
{
    INT32                       i4_ret = 0;
    UTF16_T                     w2s_tmp_str[128];
    UTF16_T                     w2s_str[128];

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    c_uc_ps_to_w2s(s_value, w2s_tmp_str, c_strlen(s_value));

    i4_ret = c_wgl_do_cmd(h_list_box,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_left_sys_info_idx[ui4_idx],0),
                            w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_left_sys_info_idx[ui4_idx],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    return i4_ret;
}

static INT32 _sys_info_update_left_list_box_item (LEFT_SYS_INFO_ROWNUM   row,
                                                  CHAR*                  s_value)
{
    INT32                       i4_ret = 0;

    i4_ret = _sys_info_update_list_box_item(tg_view.h_left_list_box, row, s_value);
    RET_ON_ERR(i4_ret);

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _sys_info_utv_info_update
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _sys_info_utv_info_update(VOID)
{
    INT32                       i4_ret = MENUR_OK;
#ifdef APP_ULI_UPG_SUPPORT

    MENU_VER_ULI_INFO           ver_uli_info = {0};

    menu_ver_info_utv_info_get(&ver_uli_info);

    /* ESN */
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_ESN, ver_uli_info.str_esn);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Device Agent */
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_DA, ver_uli_info.str_device_agent);
    MENU_LOG_ON_FAIL(i4_ret);

    /*UID*/
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_UID, ver_uli_info.str_uid);
    MENU_LOG_ON_FAIL(i4_ret);

    /*SV*/
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_SV, ver_uli_info.str_sv);
    MENU_LOG_ON_FAIL(i4_ret);

    /*DEV ID*/
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_DEV_ID, ver_uli_info.str_dev_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Prov ID*/
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_PROV_ID, ver_uli_info.str_prov_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*REG*/
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_REG, ver_uli_info.str_reg);
    MENU_LOG_ON_FAIL(i4_ret);

    /*NP*/
    i4_ret = _sys_info_update_left_list_box_item(LEFT_SYS_INFO_ROW_NP, ver_uli_info.str_np);
    MENU_LOG_ON_FAIL(i4_ret);

#endif
    return i4_ret;
}

/*----------------------------------------------------------------------------
* Name:
*                 _revolt_misc_get_tuner_model_type
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
static INT32 _revolt_misc_get_tuner_model_type(CHAR* s_tmp_str)
{
    INT32    i4_ret = 0;
    UINT32   ui4_idx = 0;

    if (NULL == s_tmp_str)
    {
       DBG_ERROR(("{_revolt_misc_get_tuner_model_type}%s,%d\n", __FUNCTION__, __LINE__));
       return RMR_FAIL;
    }

    i4_ret = a_cfg_custom_get_tuner_name(s_tmp_str);
    if (i4_ret < 0)
    {
       DBG_ERROR(("{a_cfg_custom_get_tuner_name fail}%s,%d,%d\n", __FUNCTION__, __LINE__,i4_ret));
       return RMR_FAIL;
    }

    return  i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: menu_is_signal_loss
 *
 * Description:
 *  Check if it is in signal loss status.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
BOOL  _nav_is_signal_loss(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_svctx;
    BOOL        b_signal_loss = FALSE;

    h_svctx = nav_get_crnt_svctx();

    i4_ret = c_svctx_is_signal_loss(h_svctx, &b_signal_loss);
    if(i4_ret != RMR_OK)
    {
        return TRUE;
    }

    return b_signal_loss;
}

/*----------------------------------------------------------------------------
 * Name:_sys_info_get_audio_stream_text(
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _sys_info_get_audio_stream_text(UTF16_T* w2s_str, SIZE_T z_len)
{
    INT32               i4_ret;
    UTF16_T             w2s_string[65]  = {0};
    UTF16_T*            pw2s_audio_fmt  = NULL;
    ASH_AUDIO_INFO_T    t_audio_info;
    SIZE_T              z_len_remain = 64;
    SVL_REC_T           t_svl_rec;
    BOOL                b_found;
    BOOL                b_digital_ch = FALSE;
    extern UTF16_T*     nav_get_audio_fmt_str(ASH_CHANNELS_T e_channels);
    extern UTF16_T*     nav_get_audio_mts_str(SCC_AUD_MTS_T e_mts);

    c_uc_ps_to_w2s("Unknown", w2s_str, z_len);

    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    /* Get digital/analog channel */
    nav_get_crnt_svl_rec(&t_svl_rec, &b_found);

    if(b_found &&
       t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
    {
        b_digital_ch = TRUE;
    }

    /* get stream num */
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))

    TV_MODE_T   e_tv_mode = TV_MODE_TYPE_NORMAL;;
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
                return -1;
            }
        }
    }
#endif

    ISL_REC_T  t_isl_rec;
    a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN,&t_isl_rec);

    if (b_digital_ch && (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        /*a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED*/)
    {
        i4_ret = c_svctx_get_audio_info(nav_get_crnt_svctx(), &t_audio_info);
        if(i4_ret == SVCTXR_OK)
        {
           // pw2s_audio_fmt = nav_get_audio_fmt_str(t_audio_info.e_channels);

            if (ASH_AUDIO_FMT_MPEG == t_audio_info.e_aud_fmt)
            {
                z_len_remain = c_uc_w2s_strlen(w2s_string);
                c_uc_w2s_strncat(w2s_string, L"MPEG ", 64 - z_len_remain);
            }
            else if (ASH_AUDIO_FMT_AC3 ==  t_audio_info.e_aud_fmt)
            {
                z_len_remain = c_uc_w2s_strlen(w2s_string);
                c_uc_w2s_strncat(w2s_string, L"Dolby D ", 64 - z_len_remain);
            }
            else if (ASH_AUDIO_FMT_E_AC3 == t_audio_info.e_aud_fmt)
            {
                z_len_remain = c_uc_w2s_strlen(w2s_string);
                c_uc_w2s_strncat(w2s_string, L"Dolby D + ", 64 - z_len_remain);
            }
            else
            {
                /* Do nothing */
            }
        }
    }
    else
    {
        INT16 i2_val = 0;

        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_val);
        pw2s_audio_fmt = nav_get_audio_mts_str((SCC_AUD_MTS_T)i2_val);
        if (i2_val == SCC_AUD_MTS_MONO)
        {
            z_len_remain = c_uc_w2s_strlen(w2s_string);
            c_uc_w2s_strncat(w2s_string, L"Mono ", 64 - z_len_remain);
        }
        else if (i2_val == SCC_AUD_MTS_STEREO)
        {
            z_len_remain = c_uc_w2s_strlen(w2s_string);
            c_uc_w2s_strncat(w2s_string, L"Stereo ", 64 - z_len_remain);
        }
        else if (i2_val == SCC_AUD_MTS_SUB_LANG)
        {
            z_len_remain = c_uc_w2s_strlen(w2s_string);
            c_uc_w2s_strncat(w2s_string, L"SAP ", 64 - z_len_remain);
        }

        c_uc_w2s_strncpy(w2s_string, pw2s_audio_fmt, 64);
    }

    if (c_uc_w2s_strlen(w2s_string) == 0)
    {
        c_memset(w2s_string, 0, sizeof(w2s_string));
        c_uc_w2s_strcpy(w2s_string, L"UNKNOWN");
    }

    c_memset(w2s_str, 0, sizeof(UTF16_T)*z_len);
    c_uc_w2s_strncpy(w2s_str, w2s_string, z_len);
    w2s_str[z_len - 1] = 0;
    return 0;
}

/*----------------------------------------------------------------------------
 * Name:_sys_info_signal_strength_update(
 * Description:  get Signal Strength
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _sys_info_signal_strength_update(VOID)
{
    INT32                           i4_ret = 0;
    UTF16_T                         w2s_tmp_str[128];
    UTF16_T                         w2s_str[128];
    UINT8                           ui1_signal_level = 0;
    SVL_REC_T                       t_svl_rec;
    BOOL                            b_found = FALSE;
    BOOL                            b_digital_ch = FALSE;

    /*Signal Strength*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    /* Get digital/analog channel */
    nav_get_crnt_svl_rec(&t_svl_rec, &b_found);

    if(b_found &&
       t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
    {
        b_digital_ch = TRUE;
    }

    if(b_digital_ch)
    {
        i4_ret = c_svctx_get_signal_level(nav_get_crnt_svctx(),&ui1_signal_level);
    }
    else
    {
        i4_ret = c_svctx_get_dbm_signal_level(nav_get_crnt_svctx(),(INT16*)&ui1_signal_level);
    }
    if(i4_ret != SVCTXR_OK)
    {
        DBG_ERROR(("<_sys_info_signal_strength_update>info:file=%s,line=%d,i4_ret=%d\n\r",__FILE__,__LINE__,i4_ret));
    }
    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_SIGNAL_STRENGTH],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    _int_to_w2s(w2s_tmp_str, ui1_signal_level, 8);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_SIGNAL_STRENGTH],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}


/*----------------------------------------------------------------------------
 * Name:_ver_info_ch_info_update
 * Description:  get Physical Channel,Frequency/Modulation
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
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
    UINT32                          ui4_freq = 0;
    UTF16_T                         w2s_tmp_str[128];
    UTF16_T                         w2s_str[128];
    //const CHAR*                     s_tmp_str;
    CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8                           ui1_input_id = 0;
    ISL_REC_T                       t_isl_rec;
    HANDLE_T                        h_tsl;

    c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
    c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    RET_ON_ERR(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    RET_ON_ERR(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    RET_ON_ERR(i4_ret);

    if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
    {
        return RMR_OK;
    }

    /*get svl record*/
    nav_get_crnt_svl_rec (&t_svl_rec ,&b_found) ;

    /*get tsl record*/
    h_tsl = nav_get_crnt_tsl();
    c_tsl_get_rec(h_tsl,
                    t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                    &t_tsl_rec,
                    &ui4_ver_id);

    ui4_phy_ch = SB_TSL_GET_PTC_FROM_RECID (t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id);

    /*Physical Channel*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    _int_to_w2s(w2s_tmp_str,ui4_phy_ch,6);
    c_tsl_close(h_tsl);

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_PHYSICAL_CHANNEL],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_PHYSICAL_CHANNEL],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    RET_ON_ERR(i4_ret);

    b_cable = (ATSC_TRSTRL_SVL_ID == ui2_crnt_svl_id) ? FALSE : TRUE ;
    b_digital = (BRDCST_TYPE_ANALOG == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type) ? FALSE :TRUE ;

    switch ((UINT8)(b_cable) << 1 | (UINT8)(b_digital))
    {
        case 0 :                                    /* air && analog */
            ui4_freq = t_tsl_rec.udata.t_ter_ana.ui4_freq ;
            ui4_msgid = MLM_NAV_KEY_TV_DIAGNOSTICS_MOD_NTSC;
        break ;

        case 1 :                                    /* air && digital */
            ui4_freq = t_tsl_rec.udata.t_ter_dig.ui4_freq ;
            ui4_msgid = (UINT32)t_tsl_rec.udata.t_ter_dig.e_mod +MLM_NAV_KEY_TV_DIAGNOSTICS_MOD_UNKNOWN ;
        break ;
        case 2 :                                    /* cable && analog */
            ui4_freq = t_tsl_rec.udata.t_cab_ana.ui4_freq ;
            ui4_msgid = MLM_NAV_KEY_TV_DIAGNOSTICS_MOD_NTSC;
        break ;
        case 3 :                                    /* cable && digital */
            ui4_freq = t_tsl_rec.udata.t_cab_dig.ui4_freq ;
            ui4_msgid = (UINT32)t_tsl_rec.udata.t_cab_dig.e_mod +MLM_NAV_KEY_TV_DIAGNOSTICS_MOD_UNKNOWN ;
        break ;
        default :
        break ;
    }

    ui4_freq /= 1000000;

    /*Frequency*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    _int_to_w2s(w2s_tmp_str,ui4_freq,9);

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_FREQUENCY],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_FREQUENCY],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*Modulation*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    _int_to_w2s(w2s_tmp_str,ui4_freq,9);

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_MODULATION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strcat(w2s_str,NAV_TEXT(ui4_msgid));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_MODULATION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}

/*----------------------------------------------------------------------------
 * Name:_sys_info_nw_get_security_type
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _sys_info_nw_get_security_type(CHAR* ps_auth)
{
    INT32                   i4_ret = RMR_OK;
    NW_WLAN_STATE_T         e_wlan_state;
    NET_802_11_BSS_INFO_T   t_bss_info = {0};

    i4_ret = a_nw_wlan_status(&e_wlan_state);
    RET_ON_ERR(i4_ret);

    if (e_wlan_state == NW_WLAN_ASSOCIATE)
    {
        c_memset(&t_bss_info, 0, sizeof(t_bss_info));
        i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);

        if(i4_ret != RMR_OK)
        {
            DBG_ERROR(("<revolt_misc_get_curr_bss_fail>file=%s,line=%d,%d\n\r",__FILE__,__LINE__,i4_ret));
        }
    }

    switch(t_bss_info.e_AuthMode)
    {
        case IEEE_802_11_AUTH_MODE_NONE:
        case IEEE_802_11_AUTH_MODE_OPEN:
        {
            c_strncpy(ps_auth, "Open", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_SHARED:
        {
            c_strncpy(ps_auth, "WEP Shared", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WEPAUTO:
        {
            c_strncpy(ps_auth, "WEPAUTO", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA:
        {
            if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_TKIP)
            {
                c_strncpy(ps_auth, "WPA TKIP", 32);
            }
            else if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_AES)
            {
                c_strncpy(ps_auth, "WPA AES", 32);
            }
            else
            {
                c_strncpy(ps_auth, "WPA", 32);
            }
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_PSK:
        {
            c_strncpy(ps_auth, "WPA/PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2:
        {
            if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_TKIP)
            {
                c_strncpy(ps_auth, "WPA2 TKIP", 32);
            }
            else if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_AES)
            {
                c_strncpy(ps_auth, "WPA2 AES", 32);
            }
            else
            {
                c_strncpy(ps_auth, "WPA2", 32);
            }
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2_PSK:
        {
            c_strncpy(ps_auth, "WPA2/PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
        {
            c_strncpy(ps_auth, "WPAPSK/WPA2PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2_PSK_SHA256_AES:
        {
            c_strncpy(ps_auth, "WPA2PSK-SHA256AES", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_SAE:
        case IEEE_802_11_AUTH_MODE_WPA2_SAE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2SAE:
        {
            c_strncpy(ps_auth, "WPA3 SAE", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_OWE:
        case IEEE_802_11_AUTH_MODE_WPA2_OWE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE:
        {
            c_strncpy(ps_auth, "WPA3 Open Enhanced", 32);
            break;
        }

        default:
            break;
    }

    return RMR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _revolt_misc_view_show_test_speed
 *
 * Description: when get download speed, show these info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _revolt_misc_view_show_test_speed(VOID*  pv_data1,
                                                     VOID*  pv_data2,
                                                     VOID*  pv_data3)
{
    CHAR        ps_buf[10] = {0};
    UTF16_T     w2s_data[128] ={0};
    UTF16_T     w2s_buf[128] ={0};

    c_wgl_do_cmd(tg_view.h_center_list_box,
                WGL_CMD_LB_GET_ITEM_TEXT,
                WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_DOWNLOAD_SPEED],0),
                w2s_data);

    if(0 != c_uc_w2s_strcmp(w2s_data, NAV_TEXT(aui_center_mlm[CENTER_SYS_INFO_ROW_DOWNLOAD_SPEED])))
    {
        c_uc_w2s_strcpy(w2s_data, NAV_TEXT(aui_center_mlm[CENTER_SYS_INFO_ROW_DOWNLOAD_SPEED]));

    }

    c_sprintf(ps_buf, " %dkb/s\n",  i4_g_speed);
    c_uc_ps_to_w2s(ps_buf, w2s_buf, 128);
    c_uc_w2s_strncat(w2s_data,w2s_buf,c_uc_w2s_strlen(w2s_buf));

    /*show download speed*/
     c_wgl_do_cmd(tg_view.h_center_list_box,
                WGL_CMD_LB_SET_ITEM_TEXT,
                WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_DOWNLOAD_SPEED],0),
                w2s_data);

    return ;
}

/*----------------------------------------------------------------------------
 * Name: _revolt_misc_view_SpeedtestNtyFct
 *
 * Description: when the test process is end or time was expired,this function will be call
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _revolt_misc_view_SpeedtestNtyFct(
                INT32               i4Status,
                DOUBLE              u4Speed)
{
    DBG_LOG_PRINT(("\n<revolt_misc>%s,%s,%d,i4Status=%d,u4Speed=%f\n",
                __FILE__, __FUNCTION__, __LINE__,  i4Status, u4Speed));
    /* store speed value */
    nw_custom_set_speed(u4Speed);

    if(i4Status == 0)
    {
        /*kbit/s, middleware return data is bytes/s, so need data*8/1024 */
        i4_g_speed = (INT32)(u4Speed/128);
    }

    nav_request_context_switch(_revolt_misc_view_show_test_speed, NULL, NULL, NULL);

    return;
}


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

static void _nav_ver_info_get_chromium_ver(char* bin_ver)
{
    char    ver[64] = {0};

    a_rest_get_conjure_version(ver);
    c_strncpy(bin_ver, ver, c_strlen(ver));
}


/*----------------------------------------------------------------------------
 * Name: _left_up_lb_update_data
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _left_up_lb_update_data(VOID)
{
    INT32           i4_ret = 0;
    UTF16_T         w2s_tmp_str[128] = {0};
    UTF16_T         w2s_str[128] = {0};
    //UTF16_T         w2s_sn[128] = {0};
    CHAR            ac_buf[40] = {0};
    const CHAR*     s_tmp_str;

    /*Serial Number*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

#ifdef APP_ULI_UPG_SUPPORT
    UINT32 ui4_buff_len = 64;
    CHAR    str_sn[64] = "N/A";
    CHAR    string_sn[64] = {0};
    UINT32  ui4_digs_len = 0;
    i4_ret = a_uli_get_serial_number((UINT8 *)str_sn, &ui4_buff_len);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<REVOLT_MISC_VIEW>a_uli_on_get_serial_numer fail:file=%s,line=%d,i4_ret=%d\n\r",
                    __FILE__,__LINE__,i4_ret));
    }

    if (ui4_buff_len < 15)
    {
        c_strncpy(string_sn, str_sn + 2, 2);
        c_strncat(string_sn, str_sn, 2);
        c_strncat(string_sn, str_sn + 6, 2);
        c_strncat(string_sn, str_sn + 4, 2);
        c_strncat(string_sn, str_sn + 8, 5);

        ui4_digs_len = c_strlen(string_sn);
        c_strcat(string_sn, str_sn + ui4_digs_len);
    }
    else
    {
        c_strncpy(string_sn, str_sn + 8, 2);
        c_strncat(string_sn, str_sn, 8);

        ui4_digs_len = c_strlen(string_sn);
        c_strcat(string_sn, str_sn + ui4_digs_len);
    }

    c_uc_ps_to_w2s(string_sn,w2s_tmp_str,c_strlen(string_sn));
#endif

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_SERIAL_NUMBER],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_SERIAL_NUMBER],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*Model Name*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = a_cfg_custom_get_model_name(ac_buf);

    c_uc_ps_to_w2s(ac_buf,w2s_tmp_str,c_strlen(ac_buf));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_MODEL_NAME],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_MODEL_NAME],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*Version*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    s_tmp_str = sys_cust_get_usb_upg_version();

    c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

     /*Cast Version*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    CHAR    str_version[64] = {0};
    UINT32  ui4_version_len= 64;

    a_c4tv_apron_get_cast_builder_name(str_version,&ui4_version_len);
    c_uc_ps_to_w2s(str_version,w2s_tmp_str,128);

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_CAST_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_CAST_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);


    /*Chrominum Version*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    char    chromium_ver[24];
    c_memset(chromium_ver, 0, sizeof(chromium_ver));
    _nav_ver_info_get_chromium_ver(chromium_ver);
    c_uc_ps_to_w2s(chromium_ver, w2s_tmp_str, sizeof(chromium_ver));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_CHROMIUM_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_CHROMIUM_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*FRC Version*/
#if 0
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_NOT_AVAILABLE));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_FRC_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_FRC_VERSION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);
#endif

    /*Netflix ESN*/
    CHAR    string[256] = "N/A";
    UTF16_T w2s_tmp[256] = {0};
    UTF16_T w2s_str_esn[256] = {0};


    menu_ver_info_netflix_esn(string, 256);

    c_uc_ps_to_w2s(string, w2s_tmp,256);

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_NETFLIX_ESN],0),
                    w2s_str_esn);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str_esn,w2s_tmp,c_uc_w2s_strlen(w2s_tmp));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_NETFLIX_ESN],0),
                    w2s_str_esn);
    RET_ON_ERR(i4_ret);

    return RMR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _left_lb_update_data
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _left_lb_update_data(VOID)
{
    INT32                   i4_ret = 0;
    UTF16_T                 w2s_tmp_str[128] = {0};
    UTF16_T                 w2s_str[128] = {0};
	CHAR	                s_disp_name[ACFG_MAX_DISP_NAME+1];
	HANDLE_T                h_scc_comp = NULL_HANDLE;
	SCC_VID_HDR_TYPE_T      t_hdr_type;
	SCC_DOVI_INFO_T         t_dolby_vision;

    /* UID-LE*/
    i4_ret = _sys_info_utv_info_update();
    RET_ON_ERR(i4_ret);

    /*HDR*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

	i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));

	h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
				  h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);


	i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);

	DBG_LOG_PRINT(("%s,%d, t_hdr_type=%d.\r\n",__FUNCTION__, __LINE__,(UINT32)t_hdr_type));

	c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));
	i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
	DBG_LOG_PRINT(("[Dolby Vision]%s,%d, t_dolby_vision.ui1_is_doviHDR=(%d).\r\n",__FUNCTION__, __LINE__,(UINT32)t_dolby_vision.ui1_is_doviHDR));

	if (t_dolby_vision.ui1_is_doviHDR != 0) //	Dolby vision
	{
		c_uc_ps_to_w2s("Dolby Vision", w2s_tmp_str, c_strlen("Dolby Vision"));
		DBG_LOG_PRINT(("[Dolby Vision]%s,%d, t_dolby_vision.ui1_is_doviHDR=Dolby Vision.\r\n",__FUNCTION__, __LINE__,(UINT32)t_dolby_vision.ui1_is_doviHDR));
	}
	else if (t_hdr_type == SCC_VID_PQ_HDR10)
	{
		c_uc_ps_to_w2s("HDR10", w2s_tmp_str, c_strlen("HDR10"));
		DBG_LOG_PRINT(("%s,%d, t_hdr_type=HDR10.\r\n",__FUNCTION__, __LINE__));
	}
	else if (t_hdr_type == SCC_VID_PQ_HDR10PLUS)
	{
		c_uc_ps_to_w2s("HDR10+", w2s_tmp_str, c_strlen("HDR10+"));
		DBG_LOG_PRINT(("%s,%d, t_hdr_type=HDR10+.\r\n",__FUNCTION__, __LINE__));
	}
	else if (t_hdr_type == SCC_VID_PQ_HLG)
	{
		c_uc_ps_to_w2s("HLG", w2s_tmp_str, c_strlen("HLG"));
		DBG_LOG_PRINT(("%s,%d, t_hdr_type=HLD.\r\n",__FUNCTION__, __LINE__));
	}
	else
	{
		c_uc_ps_to_w2s("NO", w2s_tmp_str, c_strlen("NO"));
		DBG_LOG_PRINT(("%s,%d, t_hdr_type=NO.\r\n",__FUNCTION__, __LINE__));
	}

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_left_sys_info_idx[LEFT_SYS_INFO_ROW_HDR],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_left_sys_info_idx[LEFT_SYS_INFO_ROW_HDR],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*Model Group*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    CHAR  str_tmp[64] = "MG";
    CHAR  str_mg_id[32] = {0};
    UINT32 ui4_group_id = 0;

    i4_ret = a_cfg_custom_get_model_group_id(&ui4_group_id);
    RET_ON_ERR(i4_ret);

    c_sprintf(str_mg_id,"%x",ui4_group_id);
    c_strcat(str_tmp,str_mg_id);
    c_uc_ps_to_w2s(str_tmp,w2s_tmp_str,c_strlen(str_tmp));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_left_sys_info_idx[LEFT_SYS_INFO_ROW_MODEL_GROUP],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_left_sys_info_idx[LEFT_SYS_INFO_ROW_MODEL_GROUP],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _center_lb_update_data
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _center_lb_update_data(VOID)
{
    INT32           i4_ret = RMR_OK;
    static NW_IP_INFO_T    t_net_ip_info;
    CHAR            s_ip_str[16];
    CHAR            s_mac_str[64];
    UTF16_T         w2s_tmp_str[128];
    UTF16_T         w2s_str[128];
    BOOL            b_plug = FALSE;
    NET_802_11_WIFI_RSSI_T      t_rssi;
    CHAR                        s_data[128] = {0};

    /*Connection */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_CONNECTION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    i4_ret = a_nw_get_ethernet_connect_info(&b_plug);

    if(i4_ret != 0)
    {
        c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_DISCONNECTED));
    }
    else
    {
        if(b_plug)
        {
            c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_WIRED));
        }
        else
        {
            c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_WIRELESS));
        }
    }

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_CONNECTION],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*SSID*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_SSID],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    NET_802_11_BSS_INFO_T       CurrBss;

    c_memset(&CurrBss, 0, sizeof(CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&CurrBss);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<revolt_misc_view> a_nw_wlan_get_curr_bss fail file=%s,line=%d\n\r",__FILE__,__LINE__));
    }

    if (CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        c_uc_ps_to_w2s(CurrBss.t_Ssid.ui1_aSsid, w2s_tmp_str, c_strlen(CurrBss.t_Ssid.ui1_aSsid));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_NOT_AVAILABLE));
    }
    DBG_INFO(("<REVOLT_MISC_VIEW>file=%s,line=%d,ssid=%s\n\r",__FILE__,__LINE__,CurrBss.t_Ssid.ui1_aSsid));

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_SSID],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*IP Address*/
    c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_IP],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    i4_ret = a_nw_get_crnt_ip_info(&t_net_ip_info);
    //i4_ret = a_nw_manual_ip_config(&t_ip_info);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<revolt_misc_get_ip fail>\n\r"));
    }

    DBG_INFO(("<REVOLT_MISC_VIEW>file=%s,line=%d,ui4_address=%d\n\r",__FILE__,__LINE__,t_net_ip_info.ui4_address));

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_address);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_IP],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*Gateway*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_gw);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));
    DBG_INFO(("<REVOLT_MISC_VIEW>file=%s,line=%d,gateway:%s\n\r",__FILE__,__LINE__,s_ip_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_GATEWAY],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_GATEWAY],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);


    /*Subnet*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_netmask);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));
    DBG_INFO(("<REVOLT_MISC_VIEW>file=%s,line=%d,subnet:%s\n\r",__FILE__,__LINE__,s_ip_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_SUBNET],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_SUBNET],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*Pref. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_1st_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));
    DBG_INFO(("<REVOLT_MISC_VIEW>file=%s,line=%d,dns:%s\n\r",__FILE__,__LINE__,s_ip_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

   i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*Alt. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_2nd_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));
    DBG_INFO(("<REVOLT_MISC_VIEW>file=%s,line=%d,ans:%s\n\r",__FILE__,__LINE__,s_ip_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /* Security Type */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    CHAR  str_sec_type[32] = {0};

    if (!b_plug)
    {
        _sys_info_nw_get_security_type(str_sec_type);
        c_uc_ps_to_w2s(str_sec_type, w2s_tmp_str, c_strlen(str_sec_type));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_tmp_str, NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_NOT_AVAILABLE));
    }

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /* Download Speed */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret= c_speedtest(NULL, _revolt_misc_view_SpeedtestNtyFct);
    if (i4_ret != 0)
    {
        DBG_ERROR(("<revolt_misc>file=%s,line=%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
        c_speedtest_cancel();
    }

    /* WIFI RSSI */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_WIFI_RSSI],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    if (!b_plug)
    {

        i4_ret = a_nw_wlan_get_rssi(&t_rssi);
        RET_ON_ERR(i4_ret);
        c_sprintf(s_data, "%d dBm", (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
        c_uc_ps_to_w2s(s_data, w2s_tmp_str, c_strlen(s_data));

    }
    else
    {
        c_sprintf(s_data, "%d dBm", 0);
        c_uc_ps_to_w2s(s_data, w2s_tmp_str, c_strlen(s_data));
    }

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_WIFI_RSSI],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

     /* WiFi-Channel */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                  WGL_CMD_LB_GET_ITEM_TEXT,
                  WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_WIFI_CHANNEL],0),
                  w2s_str);
    RET_ON_ERR(i4_ret);

    CHAR    str_Channel[64] = {0};

    if (CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        c_sprintf(str_Channel, "%d", CurrBss.i2_Channel);
        c_uc_ps_to_w2s(str_Channel, w2s_tmp_str, c_strlen(str_Channel));
    }
    else
    {
        c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_NOT_AVAILABLE));
    }
    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_WIFI_CHANNEL],0),
                  w2s_str);
    RET_ON_ERR(i4_ret);

    /*RJ45 MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);

    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);
    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*WLAN MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);

    a_nw_get_mac_addr_string(NI_WIRELESS_0,s_mac_str);
    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);
#if 0
    /*BT MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    BT_GAP_LOCAL_PROPERTIES_RESULT local_dev_info;

    i4_ret = c_btm_get_local_dev_info(&local_dev_info);
    if(i4_ret < 0)
    {
        DBG_ERROR(("<REVOLT_MISC_VIEW>c_btm_get_local_dev_info fail:file=%s,line=%d,i4_ret=%d\n\r",
                    __FILE__,__LINE__,i4_ret));
    }
    DBG_LOG_PRINT(("c_btm_get_local_dev_info BT MAC:%s,BT Name:%s\n\r",
                local_dev_info.bdAddr,local_dev_info.name));

    c_uc_ps_to_w2s(local_dev_info.bdAddr,w2s_tmp_str,c_strlen(local_dev_info.bdAddr));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_BT_MAC],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_BT_MAC],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*BT Devices*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    c_uc_ps_to_w2s(local_dev_info.name,w2s_tmp_str,128);

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_BT_DEVICES],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_BT_DEVICES],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);
#endif
    return RMR_OK;
}


/*----------------------------------------------------------------------------
 * Name: get_USB_dev_info
 * Description:
 * Inputs:	-
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32  _get_USB_dev_info(VOID)
{
	RMV_DEV_DEVICE_STATUS_T  e_dev_status;
	INT32		i4_ret = 0;
	CHAR		ac_path[SYS_INFO_PAGE_MAX_NAME_LEN] = {0};
	CHAR		ac_info[SYS_INFO_PAGE_MAX_NAME_LEN] = {0};
  	UTF16_T     u2_ac_info[SYS_INFO_PAGE_MAX_NAME_LEN]={0};
	UTF16_T 	w2s_tmp_str[SYS_INFO_PAGE_MAX_NAME_LEN] = {0};
	SIZE_T		z_size = SYS_INFO_PAGE_MAX_NAME_LEN;
	UINT32		ui4_len = SYS_INFO_PAGE_MAX_NAME_LEN;
	UINT32		ui4_idx = 0;
	UTF16_T 	w2s_str[128] = {0};

	i4_ret = a_rmv_dev_get_active_mnt_pnt(&ui4_idx, &z_size, ac_path);

	/*query mount point status*/
	i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
								ui4_idx,
								&e_dev_status);

	if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
		(TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
		(TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
	{
		DBG_INFO(("\n%s,%s,%d,ui4_idx=%d,ac_path=%s,e_dev_status=%d\n",
					__FILE__, __FUNCTION__, __LINE__,
					ui4_idx, ac_path, e_dev_status));


	}

	if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
	{
		z_size = SYS_INFO_PAGE_MAX_NAME_LEN;
		i4_ret = a_rmv_dev_get_mnt_point_info(
								ui4_idx,
								RMV_DEV_INFO_ID_DESC,
								&z_size,
								(VOID*)(ac_info));

	}
	else
	{
		i4_ret = c_fm_get_volume_label(NULL_HANDLE,
									   ac_path,
									   ac_info,
									   &ui4_len);

	}

    c_uc_ps_to_w2s(ac_info,u2_ac_info,sizeof(ac_info));
	if (c_uc_w2s_strlen(u2_ac_info) == 0)
	{
		c_strncpy (ac_info , "none" ,5);
	}
	i4_ret = c_uc_ps_to_w2s(ac_info, w2s_tmp_str, SYS_INFO_PAGE_MAX_NAME_LEN);
	RET_ON_ERR(i4_ret);

   i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
				   WGL_CMD_LB_GET_ITEM_TEXT,
				   WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_USB],0),
				   w2s_str);
   RET_ON_ERR(i4_ret);

   c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

   i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
				   WGL_CMD_LB_SET_ITEM_TEXT,
				   WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_USB],0),
				   w2s_str);
   RET_ON_ERR(i4_ret);
   return NAVR_OK;
}

 /*----------------------------------------------------------------------------
 * Name: _get_comb_dev_info
 * Description:
 * Inputs:	-
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _get_comb_dev_info(VOID)
{
	INT32			i4_ret = 0;
	ISL_REC_T	    t_isl_rec;
	UTF16_T         w2s_str[128] = {0};
	const char *    s_str;
	UTF16_T         w2s_tmp_str[128] = {0};
	CHAR       		s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8           ui1_input_id = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    RET_ON_ERR(i4_ret);

	i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
	RET_ON_ERR(i4_ret);

	i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
	RET_ON_ERR(i4_ret);


	if (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type)
	{
		/*check signal*/
		if (nav_is_signal_loss(TV_WIN_ID_MAIN) == TRUE )
		{
			s_str = " none ";
		}
		else
		{
			s_str = " COMP ";
		}
	}
	else
	{
		 s_str = " none ";
	}
	c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
	c_memset(w2s_str, 0, sizeof(w2s_str));
	c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));

	i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
					WGL_CMD_LB_GET_ITEM_TEXT,
					WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_COMP],0),
					w2s_str);
	RET_ON_ERR(i4_ret);

	c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

	i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
					WGL_CMD_LB_SET_ITEM_TEXT,
					WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_COMP],0),
					w2s_str);
	RET_ON_ERR(i4_ret);

	 return RMR_OK;

}

 /*----------------------------------------------------------------------------
  * Name: _get_tv_dev_info
  * Description:
  * Inputs:  -
  * Outputs: -
  * Returns: -
  ----------------------------------------------------------------------------*/
extern HANDLE_T menu_get_crnt_svctx(VOID);

static INT32 _revolt_misc_get_hdmi_iid_count(UINT8 *pui1_cnt)
{
    ISL_REC_T t_isl_rec;
    INT32		  		i4_ret = 0;

    i4_ret = a_isl_get_rec_by_dev_type (DEV_AVC_HDMI, 0, &t_isl_rec);
    if (i4_ret != ISLR_OK)
    {
        return i4_ret;
    }

    *pui1_cnt = t_isl_rec.ui1_iid_count;

    return i4_ret;

}
static INT32 _get_tv_dev_info(VOID)
{
	INT32		  		i4_ret = 0;
	CHAR				s_disp_name[ACFG_MAX_DISP_NAME+1];
	UINT8				ui1_input;
	ISL_REC_T			t_isl_rec = {0};
	UTF16_T 			w2s_str[128] = {0};
	UTF16_T 			w2s_tmp_str[128] = {0};
	VSH_SRC_RESOLUTION_INFO_T	  t_resol;
	CHAR			    s_tuner_type[CUST_TUNER_TYPE_MAX_LEN+1] = {0};
	CHAR				s_cast_str[128] = {0};

	/* Get target input source */
	a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
	a_cfg_av_get_input_src(s_disp_name, &ui1_input);
	a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
	c_memset (&t_resol, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));
	 c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resol);
	 i4_ret = _revolt_misc_get_tuner_model_type(s_tuner_type);
	 /*current state is not in TV and composite source */
	 if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV )
	 {
		 if ((t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
		 &&(t_resol.ui4_height == 0)
		 &&(t_resol.ui4_width== 0))
		 {
			 c_strncpy(s_cast_str , " none " ,5);
		 }
		 else
		 {
		 	 c_strncpy(s_cast_str , " TV " ,5);
		 }
	  }
	 else
	 {
		 c_strncpy(s_cast_str , " none " ,5);
	 }

	 c_sprintf(s_cast_str,"%s, %s",s_cast_str,s_tuner_type);

		c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
		c_memset(w2s_str, 0, sizeof(w2s_str));

		c_uc_ps_to_w2s(s_cast_str,w2s_tmp_str,c_strlen(s_cast_str));

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_GET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_TUNNER],0),
						w2s_str);
		RET_ON_ERR(i4_ret);

		c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_SET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_TUNNER],0),
						w2s_str);
		RET_ON_ERR(i4_ret);


	 return TRUE;
}


static UINT32 _nav_cec_custom_get_amp_hdmi1_5v(UINT8 *pui1_5v_status)
{
  INT32   i4_ret;
  DRV_CUST_OPERATION_INFO_T    t_op_info={0};
  SIZE_T					   z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
  SIZE_T					   z_size = sizeof(pui1_5v_status);


  c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
  t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
  t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_5V_STATUS;
  t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
  t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

  /*get driver value */
  i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
						  DRV_CUST_COMP_ID,
						  FALSE,
						  ANY_PORT_NUM,
						  0,
						  &t_op_info,
						  &z_size_drv
						  );

  if(i4_ret != RMR_OK)
  {
	  DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
	  return i4_ret;
  }

  return i4_ret;
}

static UINT32 _nav_cec_custom_get_amp_hdmi2_5v(UINT8 *pui1_5v_status)
{
  INT32   i4_ret;
  DRV_CUST_OPERATION_INFO_T    t_op_info={0};
  SIZE_T					   z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
  SIZE_T					   z_size = sizeof(pui1_5v_status);


  c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
  t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
  t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI2_5V_STATUS;
  t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
  t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

  /*get driver value */
  i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
						  DRV_CUST_COMP_ID,
						  FALSE,
						  ANY_PORT_NUM,
						  0,
						  &t_op_info,
						  &z_size_drv
						  );

  if(i4_ret != RMR_OK)
  {
	  DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
	  return i4_ret;
  }

  return i4_ret;
}


 static UINT32 _nav_cec_custom_get_amp_hdmi3_5v(UINT8 *pui1_5v_status)
 {
	 INT32	 i4_ret;
	 DRV_CUST_OPERATION_INFO_T	  t_op_info={0};
	 SIZE_T 					  z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	 SIZE_T 					  z_size = sizeof(pui1_5v_status);
	 c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
	 t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
	 t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI3_5V_STATUS;
	 t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
	 t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
	 /*get driver value */
	 i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
							 DRV_CUST_COMP_ID,
							 FALSE,
							 ANY_PORT_NUM,
							 0,
							 &t_op_info,
							 &z_size_drv
							 );

	 if(i4_ret != RMR_OK)
	 {
		 DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
		 return i4_ret;
	 }
	 return i4_ret;
 }

 static UINT32 _nav_cec_custom_get_amp_hdmi4_5v(UINT8 *pui1_5v_status)
 {
	 INT32	 i4_ret;
	 DRV_CUST_OPERATION_INFO_T	  t_op_info={0};
	 SIZE_T 					  z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	 SIZE_T 					  z_size = sizeof(pui1_5v_status);
	 c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
	 t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
	 t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI4_5V_STATUS;
	 t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
	 t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
	 /*get driver value */
	 i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
							 DRV_CUST_COMP_ID,
							 FALSE,
							 ANY_PORT_NUM,
							 0,
							 &t_op_info,
							 &z_size_drv
							 );

	 if(i4_ret != RMR_OK)
	 {
		 DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
		 return i4_ret;
	 }
	 return i4_ret;
 }
#ifdef NEVER

static INT32 _get_hdmi_dev_info(UINT16 ui2_usb_hdmi_num)
{
	INT32			i4_ret = 0;
	ISL_REC_T	    t_isl_rec;
	UTF16_T         w2s_str[128] = {0};
	const char *    s_str;
	UTF16_T         w2s_tmp_str[128] = {0};
	CHAR       		s_disp_name[ACFG_MAX_DISP_NAME+1];
    UINT8           ui1_input_id = 0;
	UINT8			ui1_src_count = 0;
	UTF16_T 		w2s_HDMI_name[4][APP_CFG_CUSTOM_INP_NAME_LEN];
	CEC_DEV_INFO_T	t_dev_info;

	i4_ret = a_isl_get_num_rec(&ui1_src_count);
	NAV_CHK_FAIL(i4_ret == ISLR_OK ? NAVR_OK : i4_ret);

	if( 0 == ui1_src_count )
	{
		return NAVR_NOT_EXIST;
	}

	c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
	i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    RET_ON_ERR(i4_ret);

	i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
	RET_ON_ERR(i4_ret);

	c_memset(w2s_HDMI_name[t_isl_rec.ui1_internal_id], 0, sizeof(w2s_HDMI_name[t_isl_rec.ui1_internal_id]));

	 i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
	 RET_ON_ERR(i4_ret);

	if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type && DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
	{
		 /* Find CEC name if available. */

		 DBG_LOG_PRINT(("[REVOLT MISC]Get HDMI info FUNC: %s,%d,ui1_internal_id:%d\n", __FILE__,__LINE__,t_isl_rec.ui1_internal_id));

		 i4_ret = a_cec_get_dev_info (a_nav_cec_get_mw_handle (), t_isl_rec.ui1_internal_id, 0, &t_dev_info);
		 if (i4_ret == CECR_OK)
		 {
			 c_uc_w2s_strncpy (w2s_HDMI_name[t_isl_rec.ui1_internal_id], t_dev_info.aw2_osd_name, CECM_OSD_NAME_SIZE);
		 }
	}

	{

		   UINT8 get_hdmi1_state;
		   UINT8 get_hdmi2_state;
		   UINT8 get_hdmi3_state;
	 	   UINT8 get_hdmi4_state;

		   if(c_uc_w2s_strlen(w2s_HDMI_name[0]) == 0)
		   {
				 _nav_cec_custom_get_amp_hdmi1_5v(&get_hdmi1_state);

				 if (get_hdmi1_state != 0)
				 {
					 s_str = " HDMI ";
				 }
				 else
				 {
					 s_str = " none ";
				 }
				c_memset(&w2s_tmp_str, 0, sizeof(w2s_tmp_str));
				c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
				c_uc_w2s_strncat(w2s_HDMI_name[0],w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
		   }

		   if(c_uc_w2s_strlen(w2s_HDMI_name[1]) == 0)
		   {
			   _nav_cec_custom_get_amp_hdmi2_5v(&get_hdmi2_state);

			   if (get_hdmi2_state != 0)
			   {
				   s_str = " HDMI ";
			   }
			   else
			   {
				   s_str = " none ";
			   }
			   c_memset(&w2s_tmp_str, 0, sizeof(w2s_tmp_str));
			   c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
			   c_uc_w2s_strncat(w2s_HDMI_name[1],w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
		   }

		   if(c_uc_w2s_strlen(w2s_HDMI_name[2]) == 0)
		   {
				_nav_cec_custom_get_amp_hdmi3_5v(&get_hdmi3_state);

				if (get_hdmi3_state != 0)
				{
					s_str = " HDMI ";
				}
				else
				{
					s_str = " none ";
				}
				c_memset(&w2s_tmp_str, 0, sizeof(w2s_tmp_str));
				c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
				c_uc_w2s_strncat(w2s_HDMI_name[2],w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
		   }
		   if (ui2_usb_hdmi_num == 4)
		   {
			   if(c_uc_w2s_strlen(w2s_HDMI_name[3]) == 0)
			   {
					_nav_cec_custom_get_amp_hdmi4_5v(&get_hdmi4_state);

					if (get_hdmi4_state != 0)
					{
						s_str = " HDMI ";
					}
					else
					{
						s_str = " none ";
					}
					c_memset(&w2s_tmp_str, 0, sizeof(w2s_tmp_str));
					c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
					c_uc_w2s_strncat(w2s_HDMI_name[3],w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));
			   }
		   }
	   }

    /*HDMI-1*/

	c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_1],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_HDMI_name[0],c_uc_w2s_strlen(w2s_HDMI_name[0]));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_1],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*HDMI-2*/
   	c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_2],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_HDMI_name[1],c_uc_w2s_strlen(w2s_HDMI_name[1]));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_2],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    /*HDMI-3*/
   	c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_3],0),
                    w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_HDMI_name[2],c_uc_w2s_strlen(w2s_HDMI_name[2]));


   i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
					 WGL_CMD_LB_SET_ITEM_TEXT,
					 WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_3],0),
					 w2s_str);
	 RET_ON_ERR(i4_ret);

 	if(ui2_usb_hdmi_num == 4)
 	{
		/*HDMI-4*/
	   	c_memset(w2s_str, 0, sizeof(w2s_str));

	    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
	                    WGL_CMD_LB_GET_ITEM_TEXT,
	                    WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_4],0),
	                    w2s_str);
	    RET_ON_ERR(i4_ret);

	    c_uc_w2s_strncat(w2s_str,w2s_HDMI_name[3],c_uc_w2s_strlen(w2s_HDMI_name[3]));


	   i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						 WGL_CMD_LB_SET_ITEM_TEXT,
						 WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_4],0),
						 w2s_str);
		 RET_ON_ERR(i4_ret);
	}
	 return RMR_OK;

 }
#endif /* NEVER */

static INT32 _get_hdmi_dev_info(UINT16 ui2_usb_hdmi_num)
{
    INT32			i4_ret = 0;
    UTF16_T         w2s_str[128] = {0};
    UTF16_T         w2s_tmp_str[128] = {0};
    CEC_DEV_INFO_T	t_dev_info;
    UINT8           ui1_state = 0;
    UINT8           ui1_internal_id = 0;

    /*HDMI-1*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    ui1_internal_id = 0;
    _nav_cec_custom_get_amp_hdmi1_5v(&ui1_state);
    if ( ui1_state == 0)
    {
        c_uc_w2s_strncpy (w2s_tmp_str, L" none", 30);
    }
    else
    {
        i4_ret = a_cec_get_dev_info (a_nav_cec_get_mw_handle (), ui1_internal_id, 0, &t_dev_info);
        if ((i4_ret == CECR_OK)&&(c_uc_w2s_strlen(t_dev_info.aw2_osd_name)>0))
        {
            c_uc_w2s_strncpy (w2s_tmp_str, t_dev_info.aw2_osd_name, CECM_OSD_NAME_SIZE);
        }
        else
        {
            c_uc_w2s_strncpy (w2s_tmp_str, L" Detected", 30);
        }
    }

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_1],0),
                            w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_1],0),
                        w2s_str);
    RET_ON_ERR(i4_ret);

    /*HDMI-2*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    ui1_internal_id = 1;
    _nav_cec_custom_get_amp_hdmi2_5v(&ui1_state);
    if ( ui1_state == 0)
    {
        c_uc_w2s_strncpy (w2s_tmp_str, L" none", 30);
    }
    else
    {
        i4_ret = a_cec_get_dev_info (a_nav_cec_get_mw_handle (), ui1_internal_id, 0, &t_dev_info);
        if ((i4_ret == CECR_OK)&&(c_uc_w2s_strlen(t_dev_info.aw2_osd_name)>0))
        {
            c_uc_w2s_strncpy (w2s_tmp_str, t_dev_info.aw2_osd_name, CECM_OSD_NAME_SIZE);
        }
        else
        {
            c_uc_w2s_strncpy (w2s_tmp_str, L" Detected", 30);
        }
    }

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_2],0),
                        w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_2],0),
                            w2s_str);
    RET_ON_ERR(i4_ret);

    /*HDMI-3*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    ui1_internal_id = 2;
    _nav_cec_custom_get_amp_hdmi3_5v(&ui1_state);
    if ( ui1_state == 0)
    {
        c_uc_w2s_strncpy (w2s_tmp_str, L" none", 30);
    }
    else
    {
        i4_ret = a_cec_get_dev_info (a_nav_cec_get_mw_handle (), ui1_internal_id, 0, &t_dev_info);
        if ((i4_ret == CECR_OK)&&(c_uc_w2s_strlen(t_dev_info.aw2_osd_name)>0))
        {
            c_uc_w2s_strncpy (w2s_tmp_str, t_dev_info.aw2_osd_name, CECM_OSD_NAME_SIZE);
        }
        else
        {
            c_uc_w2s_strncpy (w2s_tmp_str, L" Detected", 30);
    }
    }

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_3],0),
                        w2s_str);
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));


    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_3],0),
                        w2s_str);
    RET_ON_ERR(i4_ret);

    /*HDMI-4*/
    if(ui2_usb_hdmi_num == 4)
    {
        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));

        ui1_internal_id = 3;
        _nav_cec_custom_get_amp_hdmi4_5v(&ui1_state);
        if ( ui1_state == 0)
        {
            c_uc_w2s_strncpy (w2s_tmp_str, L" none", 30);
        }
        else
        {
            i4_ret = a_cec_get_dev_info (a_nav_cec_get_mw_handle (), ui1_internal_id, 0, &t_dev_info);
            if ((i4_ret == CECR_OK)&&(c_uc_w2s_strlen(t_dev_info.aw2_osd_name)>0))
            {
                c_uc_w2s_strncpy (w2s_tmp_str, t_dev_info.aw2_osd_name, CECM_OSD_NAME_SIZE);
            }
            else
            {
                c_uc_w2s_strncpy (w2s_tmp_str, L" Detected", 30);
            }
        }

        i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_4],0),
                                w2s_str);
        RET_ON_ERR(i4_ret);

        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_HDMI_4],0),
                            w2s_str);
                            RET_ON_ERR(i4_ret);
        }

    return RMR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _right_lb_update_data
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _right_lb_update_data(VOID)
{

	    INT32           i4_ret = 0;
	    UTF16_T         w2s_tmp_str[128] = {0};
	    UTF16_T         w2s_str[128] = {0};


		/*Tunner*/
		_get_tv_dev_info();

		/*Resolution*/
		VSH_SRC_RESOLUTION_INFO_T t_res;

		c_memset(&t_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

		c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
		c_memset(w2s_str, 0, sizeof(w2s_str));

		i4_ret = c_svctx_get_video_src_resolution(nav_get_crnt_svctx(),&t_res);
		if(i4_ret != 0)
		{
			DBG_ERROR(("<REVOLT_MISC_VIEW>c_svctx_get_video_src_resolution fail:file=%s,line=%d,i4_ret=%d\n\r",
						__FILE__,__LINE__,i4_ret));
		}

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_GET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_RESOLUTION],0),
						w2s_str);
		RET_ON_ERR(i4_ret);

		if (t_res.ui4_height !=0)
		{
			CHAR		s_str_temp[64] = {0};
			ISL_REC_T	t_isl_rec;
			TV_WIN_ID_T t_win_id = TV_WIN_ID_MAIN;

			a_tv_get_focus_win(&t_win_id);
			a_tv_get_isl_rec_by_win_id(t_win_id,&t_isl_rec);

			if ((INP_SRC_TYPE_AV == t_isl_rec.e_src_type) &&
				((DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type) ||
				(t_res.e_timing_type == VSH_SRC_TIMING_GRAPHIC)))  /* pc timing*/
			{
				c_sprintf(s_str_temp,("%d x %d\0"),t_res.ui4_width,t_res.ui4_height);
			}
			else
			{
				if (t_res.b_is_progressive)
				{
					c_sprintf(s_str_temp,("%dp\0"),t_res.ui4_height);
				}
				else
				{
					c_sprintf(s_str_temp,("%di\0"),t_res.ui4_height);
				}
			}

			c_uc_ps_to_w2s(s_str_temp,w2s_tmp_str,c_strlen(s_str_temp));
		}
		c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_SET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_RESOLUTION],0),
						w2s_str);
		RET_ON_ERR(i4_ret);

		/*Vertical Frequency*/
		c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
		c_memset(w2s_str, 0, sizeof(w2s_str));

		FLOAT	f_frame_rate = 0;
		CHAR	s_buf[32];

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

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_GET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_VERT_FREQUENCY],0),
						w2s_str);
		RET_ON_ERR(i4_ret);

		c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_SET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_VERT_FREQUENCY],0),
						w2s_str);
		RET_ON_ERR(i4_ret);

		/* Audio Type */
		c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
		c_memset(w2s_str, 0, sizeof(w2s_str));

		if (_nav_is_signal_loss())
		{
			c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_CONNECTION_TYPE_NOT_AVAILABLE));
		}
		else
		{
			_sys_info_get_audio_stream_text(w2s_tmp_str, 127);
		}

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_GET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_AUDIO_TYPE],0),
						w2s_str);
		RET_ON_ERR(i4_ret);

		c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

		i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
						WGL_CMD_LB_SET_ITEM_TEXT,
						WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_AUDIO_TYPE],0),
						w2s_str);
		RET_ON_ERR(i4_ret);

		/*Physical Channel ,Frequency/Modulation*/
		i4_ret = _ver_info_ch_info_update();
		RET_ON_ERR(i4_ret);


		/*Signal Strength*/
		i4_ret = _sys_info_signal_strength_update();
		RET_ON_ERR(i4_ret);

		/*Cast*/
//		_get_tv_dev_info();

   /*HDMI*/
#ifdef NEVER
	UINT16 ui2_usb_hdmi_num = 3;
	_get_comp(DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_PORT, &ui2_usb_hdmi_num, (SIZE_T)sizeof(UINT16));
	DBG_LOG_PRINT(("<_right_lb_update_data>---ui2_usb_hdmi_num: %d\r\n", ui2_usb_hdmi_num));
#endif /* NEVER */

   _get_hdmi_dev_info(tg_view.ui1_hdmi_cnt);
   DBG_LOG_PRINT(("<_right_lb_update_data>---tg_view.ui1_hdmid_cnt: %d\r\n", tg_view.ui1_hdmi_cnt));


   /*COMP*/
   _get_comb_dev_info();


    /*USB*/
	_get_USB_dev_info();

    return RMR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *     _ver_info_idx_remapping
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/

static UINT32 _ver_info_idx_remapping(VOID)
{
    UINT16      ui2_tmp_idx = 0;
    UINT16      ui2_i       = 0;
    INT32       i4_ret      = RMR_OK;

    /* up left_info_idx_remapping*/
    c_memset(a_g_up_left_sys_info_idx,0,sizeof(UINT16)*U_LEFT_SYS_INFO_ROW_LAST_NUM);

    for (ui2_i = 0; ui2_i < sizeof(aui2_up_left_item_show)/sizeof(aui2_up_left_item_show[0]); ui2_i++)
    {
        ab_up_left_item_show_flag[ui2_i] = 1;
        if (TRUE == ab_up_left_item_show_flag[aui2_up_left_item_show[ui2_i]])
        {
            a_g_up_left_sys_info_idx[aui2_up_left_item_show[ui2_i]] = ui2_tmp_idx++;
        }
    }
    //Last NUM
    a_g_up_left_sys_info_idx[U_LEFT_SYS_INFO_ROW_LAST_NUM] = ui2_tmp_idx;
    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_tmp_idx),
                 NULL);
    RET_ON_ERR(i4_ret);


    /*left_info_idx_remapping*/
    c_memset(a_g_left_sys_info_idx,0,sizeof(UINT16)*LEFT_SYS_INFO_ROW_LAST_NUM);
    ui2_tmp_idx = 0;

    for (ui2_i = 0; ui2_i < sizeof(aui2_left_item_show)/sizeof(aui2_left_item_show[0]); ui2_i++)
    {
        ab_left_item_show_flag[ui2_i] = 1;
        if (TRUE == ab_left_item_show_flag[aui2_left_item_show[ui2_i]])
        {
            a_g_left_sys_info_idx[aui2_left_item_show[ui2_i]] = ui2_tmp_idx++;
        }
    }
    //Last NUM
    a_g_left_sys_info_idx[LEFT_SYS_INFO_ROW_LAST_NUM] = ui2_tmp_idx;
    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_tmp_idx),
                 NULL);
    RET_ON_ERR(i4_ret);

    /*center_info_idx_remapping*/
    c_memset(a_g_center_sys_info_idx,0,sizeof(UINT16)*CENTER_SYS_INFO_ROW_LAST_NUM);
    ui2_tmp_idx = 0;
/*
    i4_ret = _init_center_item_show_flag();
    RET_ON_ERR(i4_ret);
 */
    for (ui2_i = 0; ui2_i < sizeof(aui2_center_item_show)/sizeof(aui2_center_item_show[0]); ui2_i++)
    {
        ab_center_item_show_flag[ui2_i] = 1;
        if (TRUE == ab_center_item_show_flag[aui2_center_item_show[ui2_i]])
        {
            a_g_center_sys_info_idx[aui2_center_item_show[ui2_i]] = ui2_tmp_idx++;
        }
    }
    //Last NUM
    a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_LAST_NUM] = ui2_tmp_idx;
    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_tmp_idx),
                 NULL);
    RET_ON_ERR(i4_ret);

    /*left_info_idx_remapping*/
    c_memset(a_g_right_sys_info_idx,0,sizeof(UINT16)*RIGHT_SYS_INFO_ROW_LAST_NUM);
    ui2_tmp_idx = 0;

    for (ui2_i = 0; ui2_i < sizeof(aui2_right_item_show)/sizeof(aui2_right_item_show[0]); ui2_i++)
    {
        ab_right_item_show_flag[ui2_i] = 1;

#ifdef NEVER
		UINT16 ui2_usb_hdmi_num = 3;
		_get_comp(DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_PORT, &ui2_usb_hdmi_num, (SIZE_T)sizeof(UINT16));

		DBG_LOG_PRINT(("<_ver_info_idx_remapping>---ui2_usb_hdmi_num: %d\r\n", ui2_usb_hdmi_num));
#endif /* NEVER */
		if (RIGHT_SYS_INFO_ROW_HDMI_4 == ui2_i)
		{
			if (tg_view.ui1_hdmi_cnt < 4)
			{
				ab_right_item_show_flag[ui2_i] = 0;
			}
		}
        if (TRUE == ab_right_item_show_flag[aui2_right_item_show[ui2_i]])
        {
            a_g_right_sys_info_idx[aui2_right_item_show[ui2_i]] = ui2_tmp_idx++;
        }
    }
    //Last NUM
    a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_LAST_NUM] = ui2_tmp_idx;
    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_tmp_idx),
                 NULL);
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lb_update_first_elem
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _lb_update_first_elem(VOID)
{
    INT32                       i4_ret = RMR_OK;
    UTF16_T                     w2s_str[128] = {0};

    /*update up left lb first elem*/
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(0,0),
                            w2s_str);
    RET_ON_ERR(i4_ret);

    if (0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_SERIAL_NAME)))
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_uc_w2s_strcpy(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_SERIAL_NAME));

        i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_up_left_sys_info_idx[LEFT_SYS_INFO_ROW_SERIAL_NUMBER],0),
                            w2s_str);
        RET_ON_ERR(i4_ret);
    }

    /*update left lb first elem*/
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(0,0),
                            w2s_str);
    RET_ON_ERR(i4_ret);

    CHAR w2s_str_dst[128] = {0};
    c_uc_w2s_to_ps((const UTF16_T* )w2s_str,w2s_str_dst,127);
    DBG_LOG_PRINT(("<revolt_misc>dst=%s,%s,%d\n",w2s_str_dst,__FILE__,__LINE__));

    if (0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_UID)))
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_uc_w2s_strcpy(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_UID));

        CHAR w2s_str_dst[128] = {0};
        c_uc_w2s_to_ps((const UTF16_T* )w2s_str,w2s_str_dst,127);
        DBG_LOG_PRINT(("<revolt_misc>dst=%s,%s,%d\n",w2s_str_dst,__FILE__,__LINE__));

        i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_left_sys_info_idx[LEFT_SYS_INFO_ROW_UID],0),
                            w2s_str);
        RET_ON_ERR(i4_ret);
    }

    /*update center lb first elem*/
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(0,0),
                            w2s_str);
    RET_ON_ERR(i4_ret);

    if (0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_CONNECTION)))
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_uc_w2s_strcpy(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_CONNECTION));

        i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_center_sys_info_idx[CENTER_SYS_INFO_ROW_CONNECTION],0),
                            w2s_str);
        RET_ON_ERR(i4_ret);
    }

    /*update right lb first elem*/
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                            WGL_CMD_LB_GET_ITEM_TEXT,
                            WGL_PACK_2(0,0),
                            w2s_str);
    RET_ON_ERR(i4_ret);

    if (0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_TUNNER)))
    {
        c_memset(w2s_str, 0, sizeof(w2s_str));
        c_uc_w2s_strcpy(w2s_str, NAV_TEXT(MLM_NAV_KEY_NAV_SYS_INFO_TUNNER));

        i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2(a_g_right_sys_info_idx[RIGHT_SYS_INFO_ROW_TUNNER],0),
                            w2s_str);
        RET_ON_ERR(i4_ret);
    }

    return RMR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *      _revolt_misc_get_gui_lang
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/

static INT32 _revolt_misc_get_gui_lang(VOID)
{
    INT32 i4_ret;
    ISO_639_LANG_T s639_lang;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    RET_ON_ERR(i4_ret);

    ui2_g_nav_curr_lang = mlm_nav_s639_to_langidx(s639_lang);

    return RMR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *      _revolt_misc_view_init_widgets
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _revolt_misc_sys_info_update_data(VOID)
{
    INT32                       i4_ret;

    i4_ret = _revolt_misc_get_gui_lang();
    RET_ON_ERR(i4_ret);

    i4_ret = _ver_info_idx_remapping();
    RET_ON_ERR(i4_ret);

    i4_ret = _lb_update_first_elem();
    RET_ON_ERR(i4_ret);

    /* update up left listbox data */
    i4_ret = _left_up_lb_update_data();
    RET_ON_ERR(i4_ret);

    /* update left listbox data */
    i4_ret = _left_lb_update_data();
    RET_ON_ERR(i4_ret);

    /* update center listbox data */
    i4_ret = _center_lb_update_data();
    RET_ON_ERR(i4_ret);

    /* update right listbox data */
    i4_ret = _right_lb_update_data();
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(tg_view.h_main_frame, NULL, TRUE);
    RET_ON_ERR(i4_ret);
    return RMR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _revolt_misc_wgl_left_up_lb_attr_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_left_up_lb_attr_init(VOID)
{
    INT32                       i4_ret = 0;
    GL_RECT_T                   t_rect;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           t_cols;
    WGL_LB_ITEM_T               at_items;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
    UTF16_T                     w2s_tmp_str[128] = {0};
    INT8                        ui1_i = 0;

     // Column info
    t_cols.e_col_type           = LB_COL_TYPE_TEXT;
    t_cols.ui1_align            = WGL_AS_LEFT_CENTER;
    t_cols.ui2_width            = 650;
    t_cols.ui2_max_text_len     = 128;

#ifdef WGL_LB_SUPPORT_MULTI_LINE
    //listbox init struct
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT |
                                  WGL_STL_LB_SUPPORT_MULTILINE;
#else
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;
#endif

    t_lb_init.ui2_max_elem_num  = U_LEFT_SYS_INFO_ROW_LAST_NUM;
    t_lb_init.ui2_elem_size     = 30;
    t_lb_init.ui2_elem_distance = 5;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &t_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     LEFT_UP_LB_X,
                     LEFT_UP_LB_Y,
                     LEFT_UP_LB_WIDTH,
                     LEFT_UP_LB_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_main_frame,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_lb_init,
                                 &tg_view,
                                 &(tg_view.h_left_up_list_box));
    DBG_LOG_PRINT(("<REVOLT_MISC_VIEW>file=%s,line=%d,i4_ret=%d\n\r",__FILE__,__LINE__,i4_ret));
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = FE_FNT_SIZE_CUSTOM_LB;

    i4_ret = c_wgl_do_cmd (tg_view.h_left_up_list_box,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Inset
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 5;

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)0,
                          &t_inset);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    //Set LB colors
    t_lb_color.t_normal             = t_g_lb_color_white;
    t_lb_color.t_disable            = t_g_lb_color_white;
    t_lb_color.t_highlight          = t_g_lb_color_white;
    t_lb_color.t_highlight_unfocus  = t_g_lb_color_white;
    t_lb_color.t_pushed             = t_g_lb_color_white;
    t_lb_color.t_selected           = t_g_lb_color_white;
    t_lb_color.t_selected_disable   = t_g_lb_color_white;
    i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    RET_ON_ERR(i4_ret);

    // Set long text scroll effect
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (tg_view.h_left_up_list_box,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = _revolt_misc_get_gui_lang();
    RET_ON_ERR(i4_ret);

    for (ui1_i = 0; ui1_i < U_LEFT_SYS_INFO_ROW_LAST_NUM; ui1_i ++)
    {
        c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(aui_up_left_mlm[ui1_i]));

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = w2s_tmp_str;

        i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(&at_items),
                              NULL);
        RET_ON_ERR(i4_ret);

        c_memset(w2s_tmp_str, 0, 128);
    }

    i4_ret = c_wgl_set_visibility(tg_view.h_left_up_list_box, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _revolt_misc_wgl_left_lb_attr_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_left_lb_attr_init(VOID)
{
    INT32                       i4_ret = 0;
    GL_RECT_T                   t_rect;
   // WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           t_cols;
    WGL_LB_ITEM_T               at_items;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
    UTF16_T                     w2s_tmp_str[128] = {0};
    INT8                        ui1_i = 0;
    //const CHAR*                 s_tmp_str = " ";

     // Column info
    t_cols.e_col_type           = LB_COL_TYPE_TEXT;
    t_cols.ui1_align            = WGL_AS_LEFT_CENTER;
    t_cols.ui2_width            = COLS_WIDTH;
    t_cols.ui2_max_text_len     = 128;

    //listbox init struct
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = LEFT_SYS_INFO_ROW_LAST_NUM;
    t_lb_init.ui2_elem_size     = 22;
    t_lb_init.ui2_elem_distance = 5;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &t_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     LEFT_LB_X,
                     LEFT_LB_Y,
                     LEFT_LB_WIDTH,
                     LEFT_LB_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_main_frame,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_lb_init,
                                 &tg_view,
                                 &(tg_view.h_left_list_box));
    DBG_LOG_PRINT(("<REVOLT_MISC_VIEW>file=%s,line=%d,i4_ret=%d\n\r",__FILE__,__LINE__,i4_ret));
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = FE_FNT_SIZE_CUSTOM_LB;

    i4_ret = c_wgl_do_cmd (tg_view.h_left_list_box,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Inset
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 5;

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)0,
                          &t_inset);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    //Set LB colors
    t_lb_color.t_normal             = t_g_lb_color_white;
    t_lb_color.t_disable            = t_g_lb_color_white;
    t_lb_color.t_highlight          = t_g_lb_color_white;
    t_lb_color.t_highlight_unfocus  = t_g_lb_color_white;
    t_lb_color.t_pushed             = t_g_lb_color_white;
    t_lb_color.t_selected           = t_g_lb_color_white;
    t_lb_color.t_selected_disable   = t_g_lb_color_white;
    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    RET_ON_ERR(i4_ret);
#if 0
    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    RET_ON_ERR(i4_ret);


    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_lb_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_lb_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_lb_color_white;
    i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    RET_ON_ERR(i4_ret);
#endif
    // Set long text scroll effect
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (tg_view.h_left_list_box,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = _revolt_misc_get_gui_lang();
    RET_ON_ERR(i4_ret);

    for (ui1_i = 0; ui1_i < LEFT_SYS_INFO_ROW_LAST_NUM; ui1_i ++)
    {
        c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(aui_left_mlm[ui1_i]));

        CHAR dst[128] = {0};
        c_uc_w2s_to_ps((const UTF16_T* )w2s_tmp_str,dst,127);
        DBG_LOG_PRINT(("<revolt_misc> ui1_i:%d,dst=%s\n",ui1_i,dst));

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = w2s_tmp_str;

        i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(&at_items),
                              NULL);
        RET_ON_ERR(i4_ret);

        c_memset(w2s_tmp_str, 0, 128);
    }

    i4_ret = c_wgl_set_visibility(tg_view.h_left_list_box, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _revolt_misc_wgl_center_lb_attr_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_center_lb_attr_init(VOID)
{
    INT32                       i4_ret = 0;
    GL_RECT_T                   t_rect;
   // WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           t_cols;
    WGL_LB_ITEM_T               at_items;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
    UTF16_T                     w2s_tmp_str[128] = {0};
    INT8                        ui1_i = 0;
    //const CHAR*                 s_tmp_str = " ";

     // Column info
    t_cols.e_col_type           = LB_COL_TYPE_TEXT;
    t_cols.ui1_align            = WGL_AS_LEFT_CENTER;
    t_cols.ui2_width            = COLS_WIDTH;
    t_cols.ui2_max_text_len     = 128;

    //listbox init struct
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = CENTER_SYS_INFO_ROW_LAST_NUM;
    t_lb_init.ui2_elem_size     = 30;
    t_lb_init.ui2_elem_distance = 10;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &t_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     CENTER_LB_X,
                     CENTER_LB_Y,
                     CENTER_LB_WIDTH,
                     CENTER_LB_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_main_frame,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_lb_init,
                                 &tg_view,
                                 &(tg_view.h_center_list_box));
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = FE_FNT_SIZE_CUSTOM_LB;

    i4_ret = c_wgl_do_cmd (tg_view.h_center_list_box,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Inset
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 5;

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)0,
                          &t_inset);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    //Set LB colors
    t_lb_color.t_normal             = t_g_lb_color_white;
    t_lb_color.t_disable            = t_g_lb_color_white;
    t_lb_color.t_highlight          = t_g_lb_color_white;
    t_lb_color.t_highlight_unfocus  = t_g_lb_color_white;
    t_lb_color.t_pushed             = t_g_lb_color_white;
    t_lb_color.t_selected           = t_g_lb_color_white;
    t_lb_color.t_selected_disable   = t_g_lb_color_white;
    i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    RET_ON_ERR(i4_ret);

    // Set long text scroll effect
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (tg_view.h_center_list_box,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = _revolt_misc_get_gui_lang();
    RET_ON_ERR(i4_ret);

    for (ui1_i = 0; ui1_i < CENTER_SYS_INFO_ROW_LAST_NUM; ui1_i ++)
    {
        //c_uc_ps_to_w2s(s_tmp_str, w2s_tmp_str, c_uc_w2s_strlen(w2s_tmp_str));
        c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(aui_center_mlm[ui1_i]));
        //c_uc_w2s_strcat(w2s_tmp_str,s_tmp_str);

        //DBG_LOG_PRINT(("<w2s_tmp_str>info:w2s_tmp_str=%s,file=%s,line=%d\n\r",w2s_tmp_str,__FILE__,__LINE__));

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = w2s_tmp_str;

        i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(&at_items),
                              NULL);
        RET_ON_ERR(i4_ret);

        c_memset(w2s_tmp_str, 0, 128);
    }

    i4_ret = c_wgl_set_visibility(tg_view.h_center_list_box, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _revolt_misc_wgl_right_lb_attr_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_right_lb_attr_init(VOID)
{
    INT32                       i4_ret = 0;
    GL_RECT_T                   t_rect;
   // WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           t_cols;
    WGL_LB_ITEM_T               at_items;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;
    UTF16_T                     w2s_tmp_str[128] = {0};
    INT8                        ui1_i = 0;
    //const CHAR*                 s_tmp_str = " ";

     // Column info
    t_cols.e_col_type           = LB_COL_TYPE_TEXT;
    t_cols.ui1_align            = WGL_AS_LEFT_CENTER;
    t_cols.ui2_width            = COLS_WIDTH;
    t_cols.ui2_max_text_len     = 128;

    //listbox init struct
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = RIGHT_SYS_INFO_ROW_LAST_NUM;
    t_lb_init.ui2_elem_size     = 32;
    t_lb_init.ui2_elem_distance = 10;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &t_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     RIGHT_LB_X,
                     RIGHT_LB_Y,
                     RIGHT_LB_WIDTH,
                     RIGHT_LB_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_main_frame,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_lb_init,
                                 &tg_view,
                                 &(tg_view.h_right_list_box));
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = FE_FNT_SIZE_CUSTOM_LB;

    i4_ret = c_wgl_do_cmd (tg_view.h_right_list_box,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Inset
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 5;

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)0,
                          &t_inset);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 10;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    //Set LB colors
    t_lb_color.t_normal             = t_g_lb_color_white;
    t_lb_color.t_disable            = t_g_lb_color_white;
    t_lb_color.t_highlight          = t_g_lb_color_white;
    t_lb_color.t_highlight_unfocus  = t_g_lb_color_white;
    t_lb_color.t_pushed             = t_g_lb_color_white;
    t_lb_color.t_selected           = t_g_lb_color_white;
    t_lb_color.t_selected_disable   = t_g_lb_color_white;
    i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    RET_ON_ERR(i4_ret);

    // Set long text scroll effect
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (tg_view.h_right_list_box,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = _revolt_misc_get_gui_lang();
    RET_ON_ERR(i4_ret);

#ifdef NEVER
	UINT16 ui2_usb_hdmi_num = 3;
    _get_comp(DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_PORT, &ui2_usb_hdmi_num, (SIZE_T)sizeof(UINT16));

	DBG_LOG_PRINT(("<_revolt_misc_wgl_right_lb_attr_init>---ui2_usb_hdmi_num: %d\r\n", ui2_usb_hdmi_num));
#endif /* NEVER */

    for (ui1_i = 0; ui1_i < RIGHT_SYS_INFO_ROW_LAST_NUM; ui1_i ++)
    {
    	if (RIGHT_SYS_INFO_ROW_HDMI_4 == ui1_i)
		{
			if (tg_view.ui1_hdmi_cnt < 4)
			{
				continue;
			}
		}

        //c_uc_ps_to_w2s(s_tmp_str, w2s_tmp_str, c_uc_w2s_strlen(w2s_tmp_str));
        c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(aui_right_mlm[ui1_i]));
        //c_uc_w2s_strcat(w2s_tmp_str,s_tmp_str);

       // DBG_LOG_PRINT(("<w2s_tmp_str>info:w2s_tmp_str=%s,file=%s,line=%d\n\r",w2s_tmp_str,__FILE__,__LINE__));

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = w2s_tmp_str;

        i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(&at_items),
                              NULL);
        RET_ON_ERR(i4_ret);

        c_memset(w2s_tmp_str, 0, 128);
    }

    i4_ret = c_wgl_set_visibility(tg_view.h_right_list_box, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}


/*----------------------------------------------------------------------------
 * Name:  _revolt_misc_wgl_right_title_attr_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_right_title_attr_init(VOID)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    UTF16_T             w2s_tmp_str[128] = {0};
    UTF16_T             w2s_str[128] = {0};
    UINT16              s_rand[4]={0};
    CHAR                s_temp[4]={0};
    CHAR                s_tmp_str[5]={0};
    UINT16              i;
    UINT32              seed=0;
    time_t              t;

    SET_RECT_BY_SIZE(&t_rect,
                     RIGHT_TITLE_X,
                     RIGHT_TITLE_Y,
                     RIGHT_TITLE_WIDTH,
                     RIGHT_TITLE_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_main_frame,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)WGL_STL_TEXT_MAX_128,
                                 &tg_view,
                                 &(tg_view.h_right_title));
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 32;

    i4_ret = c_wgl_do_cmd (tg_view.h_right_title,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(tg_view.h_right_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_REVOLT_MISC_RIGHT_TITLE));  //VIZIO:

    seed = ((UINT32) time(&t));
    srand(seed);
    for (i = 0;i < 4; i++)
    {
        s_rand[i] = rand()%10;     //get the number [0~9]
        c_sprintf(s_temp,("%d"),s_rand[i]);   //(int) change to (string)
        c_strncat(s_tmp_str,s_temp,c_strlen(s_temp));
    }
    DBG_LOG_PRINT(("[revolt_misc] s_tmp_str=(%s)\n",s_tmp_str));

    //s_tmp_str = sys_cust_get_usb_upg_version();

    c_uc_ps_to_w2s(s_tmp_str,w2s_str,c_strlen(s_tmp_str));
    c_uc_w2s_strncat(w2s_tmp_str,w2s_str,c_uc_w2s_strlen(w2s_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_right_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_tmp_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_view.h_right_title, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:  _revolt_misc_wgl_left_title_attr_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_left_title_attr_init(VOID)
{
    INT32                       i4_ret = 0;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    UTF16_T                     w2s_tmp_str[128] = {0};

    SET_RECT_BY_SIZE(&t_rect,
                     LEFT_TITLE_X,
                     LEFT_TITLE_Y,
                     LEFT_TITLE_WIDTH,
                     LEFT_TITLE_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_main_frame,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128),
                                 &tg_view,
                                 &(tg_view.h_left_title));
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 32;

    i4_ret = c_wgl_do_cmd (tg_view.h_left_title,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(tg_view.h_left_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    c_uc_w2s_strcpy(w2s_tmp_str,NAV_TEXT(MLM_NAV_KEY_NAV_REVOLT_MISC_LEFT_TITLE));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_tmp_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_view.h_left_title, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name:  _revolt_misc_wgl_left_title_content_init
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_left_title_content_init(VOID)
{
    INT32                       i4_ret = 0;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    UTF16_T                     w2s_tmp_str[128] = {0};
    CHAR                        s_tmp_str[128] = {0};
    CHAR                        s_model_name[64] = {0};
    CHAR                        s_tmp[8] = "\"";

    SET_RECT_BY_SIZE(&t_rect,
                     LEFT_CONT_X,
                     LEFT_CONT_Y,
                     LEFT_CONT_WIDTH,
                     LEFT_CONT_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_main_frame,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128),
                                 &tg_view,
                                 &(tg_view.h_left_title_cont));
    RET_ON_ERR(i4_ret);

    //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = FE_FNT_SIZE_CUSTOM_LB;

    i4_ret = c_wgl_do_cmd (tg_view.h_left_title_cont,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(tg_view.h_left_title_cont,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    a_cfg_custom_get_model_name(s_model_name);

    c_strncat(s_tmp_str,s_tmp,c_strlen(s_tmp));
    c_strncat(s_tmp_str,s_model_name,c_strlen(s_model_name));
    c_strncat(s_tmp_str,s_tmp,c_strlen(s_tmp));

    c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));

    i4_ret = c_wgl_do_cmd(tg_view.h_left_title_cont,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_tmp_str),
                          WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_view.h_left_title_cont, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _revolt_misc_main_frame_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _revolt_misc_main_frame_nfy_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    INT32     i4_ret;
    UINT32    ui4_keycode = (UINT32)pv_param1;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
            case BTN_INPUT_SRC:
                {
                    DBG_LOG_PRINT(("<revolt_misc>BTN_INPUT_SRC:file=%s,line=%d\n\r",__FILE__,__LINE__));
                    revolt_misc_view_hide();
                    nav_rcu_key_handler(ui4_keycode);
                    nav_return_activation(NAV_COMP_ID_REVOLT_MISC);
                }
                break;
            case BTN_CURSOR_UP:
                break;
            case BTN_CURSOR_DOWN:
                break;
            default:
                break;
            }
            break;
        }
        case WGL_MSG_KEY_UP:
            break;
        default:
            break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *      _revolt_misc_wgl_main_frm_attr_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _revolt_misc_wgl_main_frame_attr_init(VOID)
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    WGL_IMG_INFO_T    t_img_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    SET_RECT_BY_SIZE(&t_rect,
                     REVOLT_FRAME_X,
                     REVOLT_FRAME_Y,
                     REVOLT_FRAME_WIDTH,
                     REVOLT_FRAME_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_view.h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _revolt_misc_main_frame_nfy_fct,
                                 255,
                                 NULL,
                                 &(tg_view),
                                 &(tg_view.h_main_frame));
    RET_ON_ERR(i4_ret);

    //get background img
    i4_ret = nav_img_create_revolt_misc_bk(&(tg_view.h_bk_img_tpl));
    RET_ON_ERR(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = tg_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = tg_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = tg_view.h_bk_img_tpl;
    i4_ret = c_wgl_do_cmd(tg_view.h_main_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_view.h_main_frame, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_focus(tg_view.h_main_frame,WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}

/*--------------------------------------------------------------------------
 * Name
 *      _revolt_misc_view_init_widgets
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *------------------------------------------------------------------------*/
static INT32 _revolt_misc_view_init_widgets(VOID)
{
    INT32   i4_ret;

    /* init mian frame widgets */
    i4_ret = _revolt_misc_wgl_main_frame_attr_init();
    RET_ON_ERR(i4_ret);

    /* init left title widgets */
    i4_ret = _revolt_misc_wgl_left_title_attr_init();
    RET_ON_ERR(i4_ret);

    /* init left title content widgets */
    i4_ret = _revolt_misc_wgl_left_title_content_init();
    RET_ON_ERR(i4_ret);

    /* init left title widgets */
    i4_ret = _revolt_misc_wgl_right_title_attr_init();
    RET_ON_ERR(i4_ret);

    /* init up left listbox widgets */
    i4_ret = _revolt_misc_wgl_left_up_lb_attr_init();
    RET_ON_ERR(i4_ret);

    /* init down left listbox widgets */
    i4_ret= _revolt_misc_wgl_left_lb_attr_init();
    RET_ON_ERR(i4_ret);


    /* init centerlistbox widgets */
    i4_ret= _revolt_misc_wgl_center_lb_attr_init();
    RET_ON_ERR(i4_ret);


    /* init rightlistbox widgets */
    i4_ret= _revolt_misc_wgl_right_lb_attr_init();
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _timer_signal_update
 * Description:
 * Input arguments:

 * Output arguments:
 *      None
 * Returns:

 *---------------------------------------------------------------------------*/
static VOID _timer_signal_update(VOID* pv_tag1,
                                    VOID* pv_tag2,
                                    VOID* pv_tag3)
{

    //_sys_info_signal_strength_update();

    c_wgl_repaint(tg_view.h_main_frame, NULL, TRUE);

	revolt_misc_view_update_data();
}


/*-----------------------------------------------------------------------------
 * Name
 *      _timer_signal_nfy_fct
 * Description:
 * Input arguments:

 * Output arguments:
 *      None
 * Returns:

 *---------------------------------------------------------------------------*/
static VOID _timer_signal_nfy_fct(HANDLE_T h_timer,VOID* pv_tag)
{
    nav_request_context_switch(_timer_signal_update,NULL, NULL,NULL);
}

/*-----------------------------------------------------------------------
 * Name: _nav_show_test_page_key_seq_handler
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
static VOID _nav_show_test_page_key_seq_handler(VOID*  pv_tag1,
                                                VOID*  pv_tag2,
                                                VOID*  pv_tag3)
{
    revolt_misc_view_hide();
    test_page_view_create(tg_view.h_canvas);
}

/*----------------------------------------------------------------------------
 * Name: _nav_key_sequence_show_test_page_nfy_fct
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
VOID _nav_key_sequence_show_test_page_nfy_fct(UINT16 ui2_id,  VOID* pv_tag)
{
    NAV_TEST_PAGE_DATA_T* pt_page_data = &t_nav_test_page_data;

    if (pt_page_data->ui2_show_test_page_key_id != ui2_id)
    {
        return;
    }

    nav_request_context_switch(_nav_show_test_page_key_seq_handler, NULL, NULL, NULL);
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
    INT32                 i4_ret = 0;
    NAV_TEST_PAGE_DATA_T* pt_page_data = &t_nav_test_page_data;
    UINT32                aui4_key_seq[3] = {BTN_CURSOR_LEFT, BTN_CURSOR_RIGHT, BTN_PLAY};

    i4_ret = a_key_seq_reg(aui4_key_seq,
                           3,
                           _nav_key_sequence_show_test_page_nfy_fct,
                           NULL,
                           &(pt_page_data->ui2_show_test_page_key_id));
    if (APP_KEY_SEQ_OK != i4_ret)
    {
        DBG_ERROR(("<REVOLT MISC> Signal LVL register error:%s:%d:%d\r\n",__FILE__, __LINE__, i4_ret));
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
    NAV_TEST_PAGE_DATA_T* pt_page_data = &t_nav_test_page_data;

    DBG_LOG_PRINT(("[REVOLT MISC]Signal LVL KEY sequence unreg in FUNC: %s,%d\n", __FILE__,__LINE__));

    i4_ret = a_key_seq_unreg(pt_page_data->ui2_show_test_page_key_id);
    if (APP_KEY_SEQ_OK != i4_ret)
    {
        DBG_ERROR(("<REVOLT MISC> Signal LVL un-register error:%s:%d:%d\r\n",
                    __FILE__, __LINE__, i4_ret));
    }

    pt_page_data->ui2_show_test_page_key_id = 0;
}




/*-----------------------------------------------------------------------------
 * Name
 *      revolt_misc_view_init
 * Description:
 *      system info view initialization.
 * Input arguments:
 *      pt_ctrl         pointer to struct REVOLT_MISC_SYSTEM_INFO_VIEW_T
 *      h_canvas        canvas handle
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 revolt_misc_view_init( HANDLE_T  h_canvas)
{
    INT32   i4_ret;

    tg_view.h_canvas = h_canvas;

    i4_ret = c_timer_create(&h_signal_timer);
    RET_ON_ERR(i4_ret);

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     revolt_mis_view_deinit
 * Description:
 *      system info  view deinitialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 revolt_misc_view_deinit (VOID)
{
    c_wgl_destroy_widget_ex(tg_view.h_main_frame, FALSE);
    c_memset(&tg_view, 0, sizeof(OSD_CONTENT_T));

    /* un-register show signal level key sequence */
    _page_show_test_page_key_seq_unreg();

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      revolt_misc_view_hide
 * Description:
 *      hide UI.
 * Input arguments:
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 revolt_misc_view_hide (VOID)
{
    INT32 i4_ret = RMR_OK;

    if(tg_view.b_is_show)
    {
        c_wgl_show(tg_view.h_main_frame, WGL_SW_HIDE);
        tg_view.b_is_show = FALSE;
    }

    if(h_signal_timer)
    {
        i4_ret=c_timer_stop(h_signal_timer);
        RET_ON_ERR(i4_ret);

    }

    return RMR_OK;

}

/*-----------------------------------------------------------------------------
 * Name:
 *      revolt_misc_view_show
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 revolt_misc_view_show (VOID)
{
    INT32                   i4_ret = RMR_OK;
    NAV_TEST_PAGE_DATA_T*   pt_page_data = &t_nav_test_page_data;
    UINT8                   ui1_cnt = 3;

    if(tg_view.b_is_show)
    {
        return RMR_OK;
    }
    i4_ret = _revolt_misc_get_hdmi_iid_count(&ui1_cnt);
    RET_ON_ERR(i4_ret);
    tg_view.ui1_hdmi_cnt = ui1_cnt;

    nav_grab_activation(NAV_COMP_ID_REVOLT_MISC);
    tg_view.b_is_show = TRUE;

    i4_ret = _revolt_misc_view_init_widgets();
    RET_ON_ERR(i4_ret);

    i4_ret = _revolt_misc_sys_info_update_data();
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_show(tg_view.h_main_frame, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_focus(tg_view.h_main_frame,WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

    i4_ret=c_timer_start(h_signal_timer,
                  SYS_INFO_TIMER,
                  X_TIMER_FLAG_REPEAT,
                  _timer_signal_nfy_fct,
                  NULL);
    RET_ON_ERR(i4_ret);


     /* register show test page key sequence */
    if (pt_page_data->ui2_show_test_page_key_id == 0)
    {
        _page_show_test_page_key_seq_reg();
    }

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      revolt_misc_view_update_data
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
INT32 revolt_misc_view_update_data(VOID)
{
    INT32   i4_ret = 0;
    UTF16_T w2s_str[128] = {0};
    INT32   idx =0 ;

    i4_ret = _revolt_misc_get_gui_lang();
    RET_ON_ERR(i4_ret);

    if(tg_view.b_is_show)
    {
         /*clean left up lb elem*/
        c_memset(w2s_str, 0, sizeof(w2s_str));

        for (idx=0; idx < U_LEFT_SYS_INFO_ROW_LAST_NUM; idx++)
        {
            c_memset(w2s_str, 0, 128);
            i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(a_g_up_left_sys_info_idx[idx],0),
                                w2s_str);
            RET_ON_ERR(i4_ret);

            if(0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(aui_up_left_mlm[idx])))
            {
                c_uc_w2s_strcpy(w2s_str, NAV_TEXT(aui_up_left_mlm[idx]));

                i4_ret = c_wgl_do_cmd(tg_view.h_left_up_list_box,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2(a_g_up_left_sys_info_idx[idx],0),
                                w2s_str);
                RET_ON_ERR(i4_ret);
            }
        }

        /* update left up listbox data */
        i4_ret = _left_up_lb_update_data();
        RET_ON_ERR(i4_ret);

        /*clean left lb elem*/
        c_memset(w2s_str, 0, sizeof(w2s_str));

        for (idx=0; idx < LEFT_SYS_INFO_ROW_LAST_NUM; idx++)
        {
            c_memset(w2s_str, 0, 128);
            i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(a_g_left_sys_info_idx[idx],0),
                                w2s_str);
            RET_ON_ERR(i4_ret);

            if(0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(aui_left_mlm[idx])))
            {
                c_uc_w2s_strcpy(w2s_str, NAV_TEXT(aui_left_mlm[idx]));

                i4_ret = c_wgl_do_cmd(tg_view.h_left_list_box,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2(a_g_left_sys_info_idx[idx],0),
                                w2s_str);
                RET_ON_ERR(i4_ret);
            }
        }

        /* update left listbox data */
        i4_ret = _left_lb_update_data();
        RET_ON_ERR(i4_ret);

        /*clean center lb elem*/
        c_memset(w2s_str, 0, sizeof(w2s_str));

        for (idx=0; idx < CENTER_SYS_INFO_ROW_LAST_NUM; idx++)
        {
            c_memset(w2s_str, 0, 128);
            i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(a_g_center_sys_info_idx[idx],0),
                                w2s_str);
            RET_ON_ERR(i4_ret);

            if(0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(aui_center_mlm[idx])))
            {
                c_uc_w2s_strcpy(w2s_str, NAV_TEXT(aui_center_mlm[idx]));

                i4_ret = c_wgl_do_cmd(tg_view.h_center_list_box,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2(a_g_center_sys_info_idx[idx],0),
                                w2s_str);
                RET_ON_ERR(i4_ret);
            }
        }

        /* update center listbox data */
        i4_ret = _center_lb_update_data();
        RET_ON_ERR(i4_ret);

        /*clean right lb elem*/
        c_memset(w2s_str, 0, sizeof(w2s_str));

#ifdef NEVER
		UINT16 ui2_usb_hdmi_num = 3;
		_get_comp(DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_PORT, &ui2_usb_hdmi_num, (SIZE_T)sizeof(UINT16));

		DBG_LOG_PRINT(("<revolt_misc_view_update_data>---ui2_usb_hdmi_num: %d\r\n", ui2_usb_hdmi_num));
#endif /* NEVER */

        for (idx=0; idx < RIGHT_SYS_INFO_ROW_LAST_NUM; idx++)
        {

			if (RIGHT_SYS_INFO_ROW_HDMI_4 == idx )
			{
				if (tg_view.ui1_hdmi_cnt < 4)
				{
					continue;
				}
			}
            c_memset(w2s_str, 0, 128);
            i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                                WGL_CMD_LB_GET_ITEM_TEXT,
                                WGL_PACK_2(a_g_right_sys_info_idx[idx],0),
                                w2s_str);
            RET_ON_ERR(i4_ret);

            if(0 != c_uc_w2s_strcmp(w2s_str, NAV_TEXT(aui_right_mlm[idx])))
            {
                c_uc_w2s_strcpy(w2s_str, NAV_TEXT(aui_right_mlm[idx]));

                i4_ret = c_wgl_do_cmd(tg_view.h_right_list_box,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2(a_g_right_sys_info_idx[idx],0),
                                w2s_str);
                RET_ON_ERR(i4_ret);
            }
        }

        /* update center listbox data */
        i4_ret = _right_lb_update_data();
        RET_ON_ERR(i4_ret);
    }
    return RMR_OK;
}

CHAR* revolt_misc_view_get_cust_serial(VOID)
{
    return sys_cust_get_cust_serial();
}




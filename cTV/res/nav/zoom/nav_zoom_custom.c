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
 * $RCSfile: nav_zoom_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Zoom mode is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_ZOOM_MODE_SUPPORT

#include "u_common.h"
#include "u_os.h"
#include "u_gl.h"
#include "u_irrc_btn_def.h"
#include "c_os.h"
#include "c_handle.h"
#include "c_pcl.h"
#include "c_cfg.h"
#include "c_iom.h"
#include "c_gl.h"
#include "c_wgl.h"

#include "app_client.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_zoom_mode.h"
#include "app_util/zoom_mode/zoom_mode.h"

#include "nav/a_navigator.h"
#include "menu2/a_menu.h"
#include "mmp/a_mmp.h"
#include "am/a_am.h"

#include "nav/nav_common.h"
#include "nav/navigator.h"

#include "nav/zoom/nav_zoom.h"
#include "nav/zoom/nav_zoom_view.h"

#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"
#include "res/revolt/revolt_settings_mlm.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/a_custom_log.h"

#include "res/msgconvert/msgconvert_custom.h"

#include "res/nav/zoom/nav_zoom_custom.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "rest/a_rest_event.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define NAV_ZOOM_APP_EMPTY              ((ZOOM_SECTOR_SET_T) 0)

#define NAV_ZOOM_APP_FULL_SCREEN        (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_1)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_3)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_4)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_6)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_7)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_8)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_9)  )

#define NAV_ZOOM_MENU_SCREEN_MODE       (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_3)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_6)  )

#define NAV_ZOOM_MENU_DIALOG            NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_MENU_PIC_SIZE          NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_MENU_EQUALIZER         (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_4)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_6)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_7)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_8)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_9)  )

#define NAV_ZOOM_MENU_COLOR_TUNER       (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_1)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_3)  )

#define NAV_ZOOM_MENU_SLIDER            (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_4)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_6)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_7)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_8)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_9)  )

/* Sidebar */
#define NAV_ZOOM_MENU_DEFAULT           (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_1)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_4)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_7)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_8)  )

#define NAV_ZOOM_NAV_CH_LIST            NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_NAV_PICTURE_EFFECT     NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_NAV_BANNER             (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_1)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_3)  )

#define NAV_ZOOM_NAV_INPUT_SRC          (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_1)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_4)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  )

#define NAV_ZOOM_NAV_SCREEN_MODE        (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_1)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_4)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  )

#define NAV_ZOOM_NAV_DIALOG             NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_NAV_USB_PLD            NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_NAV_SCREEN_SAVER       NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_NAV_VOL_CTRL           (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_7)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_8)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_9)  )

#define NAV_ZOOM_NAV_SLEEP              NAV_ZOOM_APP_FULL_SCREEN

#define NAV_ZOOM_NAV_POWER              NAV_ZOOM_APP_FULL_SCREEN


#define NAV_ZOOM_YH_DOCK                (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_7)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_8)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_9)  )

#define NAV_ZOOM_YH_SIDEBAR             (ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_1)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_2)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_4)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_5)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_7)  |   \
                                         ZOOM_SECTOR_IDX_TO_ID(ZOOM_SECTOR_ITEM_8)  )


#define NAV_ZOOM_ENLARGE_OSD_NUM        (3) /* will enlarge GL_OSD_PLANE_1/2/3 */
//#define NAV_ZOOM_NAVIGATION_ENABLE      (0) /*dis/enable navigation zoom XRC-260*/
typedef struct __NAV_ZOOM_SECTOR_MAP_T{
    UINT16              ui2_id;
    ZOOM_SECTOR_ITEM    e_default_item;
    ZOOM_SECTOR_SET_T   t_include_items;
} _NAV_ZOOM_SECTOR_MAP_T;

typedef struct __NAV_ZOOM_CUST_T
{
    UINT16                      ui2_zoom_mode_cfg_nfy;

    UINT16                      ui2_icl_app_status_nfy_id;
    UINT16                      ui2_icl_net_tv_svc_nfy_id;

    HANDLE_T                    h_iom;
    HANDLE_T                    h_timer_region_check;

    BOOL                        b_is_num_pad_navi_start;            /* Number Pad Zoom Navigation start or not */

} _NAV_ZOOM_CUST_T;

typedef struct __ZOOM_REGION_SIZE_T
{
    UINT32          ui4_region_w;
    UINT32          ui4_region_h;
}_ZOOM_REGION_SIZE_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
BOOL                            b_is_zoom_on_from_power_on = FALSE; /* zoom mode enable when power on */

static _NAV_ZOOM_CUST_T         t_g_zoom_cust;
static BOOL                     b_is_first_zoom_on = FALSE;
static BOOL                     b_is_enabled = FALSE; /* zoom mode enable or not */
static BOOL                     b_zoom_pause = FALSE; /* zoom mode pause or not */
static HANDLE_T                 h_handle_msg_wait_timer = NULL_HANDLE;
static HANDLE_T                 h_handle_msg_dash_wait_timer = NULL_HANDLE;
static _ZOOM_REGION_SIZE_T      at_g_region_size[NAV_ZOOM_ENLARGE_OSD_NUM];
static BOOL                     b_is_region_size_changed = FALSE;
static BOOL                     b_is_dash_digital_pad    = FALSE;
static BOOL                     b_is_dir_nav_pad         = FALSE;
static BOOL                     b_is_dash_digital_pad_timer_status    = FALSE;
static ZOOM_SECTOR_ITEM         e_current_sector = ZOOM_SECTOR_DEFAULT_ITEM;
static _NAV_ZOOM_SECTOR_MAP_T   at_zoom_sector_mapping_id_table[] =
{
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SCREEN_MODE),        ZOOM_SECTOR_ITEM_2,     NAV_ZOOM_MENU_SCREEN_MODE},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG),             ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_MENU_DIALOG},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_PIC_SIZE),           ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_MENU_PIC_SIZE},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_EQUALIZER),          ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_MENU_EQUALIZER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_COLOR_TUNER),        ZOOM_SECTOR_ITEM_8,     NAV_ZOOM_MENU_COLOR_TUNER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SLIDER),             ZOOM_SECTOR_ITEM_2,     NAV_ZOOM_MENU_SLIDER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DEFAULT),            ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_MENU_DEFAULT},

    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_CH_LIST),                     ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_NAV_CH_LIST},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_PICTURE_EFFECT),              ZOOM_SECTOR_ITEM_4,     NAV_ZOOM_NAV_PICTURE_EFFECT},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_BANNER),                      ZOOM_SECTOR_ITEM_2,     NAV_ZOOM_NAV_BANNER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_INPUT_SRC),                   ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_NAV_INPUT_SRC},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_SCREEN_MODE),                 ZOOM_SECTOR_ITEM_4,     NAV_ZOOM_NAV_SCREEN_MODE},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_DIALOG),                      ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_NAV_DIALOG},
    //{ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_USB_PLD),                   ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_NAV_USB_PLD},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_SCREEN_SAVER),                ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_NAV_SCREEN_SAVER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_VOL_CTRL),                    ZOOM_SECTOR_ITEM_8,     NAV_ZOOM_NAV_VOL_CTRL},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_SLEEP),                       ZOOM_SECTOR_ITEM_2,     NAV_ZOOM_NAV_SLEEP},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_POWER),                       ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_NAV_POWER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, ZOOM_APP_RECID_NAV_DEFAULT),              ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_NAV_SCREEN_SAVER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO),                 ZOOM_SECTOR_ITEM_2,     NAV_ZOOM_NAV_BANNER},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_C4TV_APRON),                  ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_APP_FULL_SCREEN},

    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MMP, ZOOM_APP_RECID_MMP_DEFAULT),              ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_APP_FULL_SCREEN},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_MMP, ZOOM_APP_RECID_MMP_VP_TB_SHOW),           ZOOM_SECTOR_ITEM_8,     NAV_ZOOM_APP_FULL_SCREEN},

    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_3RD_APP, ZOOM_APP_RECID_YH_DOCK),              ZOOM_SECTOR_ITEM_8,     NAV_ZOOM_YH_DOCK},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_3RD_APP, ZOOM_APP_RECID_YH_SIDEBAR),           ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_YH_SIDEBAR},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_3RD_APP, ZOOM_APP_RECID_RETAIL_MODE),          ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_APP_FULL_SCREEN},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_3RD_APP, ZOOM_APP_RECID_RETAIL_DIALOG),        ZOOM_SECTOR_ITEM_5,     NAV_ZOOM_APP_FULL_SCREEN},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_3RD_APP, ZOOM_APP_RECID_APP_FULL_SCREEN),      ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_APP_FULL_SCREEN},
    {ZOOM_MAKE_ID(ZOOM_APP_GRPID_3RD_APP, ZOOM_APP_RECID_APP_DEFAULT),          ZOOM_SECTOR_ITEM_1,     NAV_ZOOM_APP_FULL_SCREEN},

};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_cust_deinit(VOID);
static INT32 _nav_zoom_cust_power_msg_hdlr(UINT8 ui1_zoom_mode);
static VOID  _nav_zoom_cust_cb_fct (VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3);
static VOID  _nav_zoom_cust_timer_wait_cb_fct (HANDLE_T  pt_tm_handle,VOID* pv_tag);
static INT32 _nav_zoom_cust_enable_wait_timer(VOID);
static INT32 _nav_zoom_cust_disable_wait_timer(VOID);
static VOID _nav_zoom_cust_timer_dash_wait_cb_fct (HANDLE_T  pt_tm_handle,VOID* pv_tag);
static BOOL _nav_zoom_cust_dash_get_digital_pad_status(VOID);
static BOOL _nav_zoom_cust_dash_set_digital_pad_status(BOOL b_dash);
static BOOL _nav_zoom_cust_dash_get_digital_pad_timer(VOID);
static BOOL _nav_zoom_cust_dash_set_digital_pad_timer(BOOL b_dash);
#if 0
static BOOL _nav_zoom_cust_dash_digital_pad_status(UINT32 ui4_evt_code,IOM_NFY_COND_T  e_nfy_cond,BOOL b_is_start );
#endif
static INT32 _nav_zoom_cust_enable_dash_timer(VOID);
static INT32 _nav_zoom_cust_disable_dash_timer(VOID);
static UINT32 _nav_zoom_cust_menu_num_pad(UINT32 ui4_evt_code);
static BOOL _nav_zoom_cust_get_nav_zoom_status(VOID);
static BOOL _nav_zoom_cust_set_nav_zoom_status(BOOL b_nav);
static VOID _nav_zoom_cust_cfg_change_cb (
                UINT16              ui2_nfy_id,
                VOID*               pv_tag,
                UINT16              ui2_id);

static INT32 _nav_zoom_cust_icl_app_status_cb (
                UINT16              ui2_nfy_id,
                VOID*               pv_tag,
                ICL_NOTIFY_DATA_T*  pt_notify_data);

static INT32 _nav_zoom_cust_icl_net_tv_svc_status_cb (
                UINT16              ui2_nfy_id,
                VOID*               pv_tag,
                ICL_NOTIFY_DATA_T*  pt_notify_data);

static VOID _nav_zoom_cust_iom_cb_func (
                VOID*               pv_nfy_tag,
                IOM_NFY_COND_T      e_nfy_cond,
                UINT32              ui4_evt_code,
                UINT32              ui4_data);

static INT32 _nav_zoom_cust_set_num_pad_navi_enable(BOOL b_enabled);

static VOID  _nav_zoom_cust_select_sector_with_app_status (VOID);
static VOID _nav_zoom_cust_recover();
static BOOL _nav_zoom_cust_zoom_osd1(VOID);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_cust_update_region_size (VOID)
{
    INT32                   i4_ret = 0;
    UINT32                  ui4_region_w = 0;
    UINT32                  ui4_region_h = 0;

    i4_ret = a_gl_zoom_mode_get_region_size(
                        GL_OSD_PLANE_2,
                        &ui4_region_w,
                        &ui4_region_h);
    if (i4_ret != GLR_OK)
    {
        if (0 != at_g_region_size[0].ui4_region_w ||
            0 != at_g_region_size[0].ui4_region_h)
        {
            b_is_region_size_changed = TRUE;

            at_g_region_size[0].ui4_region_w = 0;
            at_g_region_size[0].ui4_region_h = 0;

            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "OSD_PLANE_2 size: [%u, %u].\n\r",
                ui4_region_w, ui4_region_h);
        }
    }
    else
    {
        if (ui4_region_w != at_g_region_size[0].ui4_region_w ||
            ui4_region_h != at_g_region_size[0].ui4_region_h)
        {
            b_is_region_size_changed = TRUE;

            at_g_region_size[0].ui4_region_w = ui4_region_w;
            at_g_region_size[0].ui4_region_h = ui4_region_h;

            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "OSD_PLANE_2 size: [%u, %u].\n\r",
                ui4_region_w, ui4_region_h);
        }
    }

    i4_ret = a_gl_zoom_mode_get_region_size(
                        GL_OSD_PLANE_3,
                        &ui4_region_w,
                        &ui4_region_h);
    if (i4_ret != GLR_OK)
    {
        if (0 != at_g_region_size[1].ui4_region_w ||
            0 != at_g_region_size[1].ui4_region_h)
        {
            b_is_region_size_changed = TRUE;

            at_g_region_size[1].ui4_region_w = 0;
            at_g_region_size[1].ui4_region_h = 0;

            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "OSD_PLANE_3 size: [0, 0].\n\r");
        }
    }
    else
    {
        if (ui4_region_w != at_g_region_size[1].ui4_region_w ||
            ui4_region_h != at_g_region_size[1].ui4_region_h)
        {
            b_is_region_size_changed = TRUE;

            at_g_region_size[1].ui4_region_w = ui4_region_w;
            at_g_region_size[1].ui4_region_h = ui4_region_h;

            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "OSD_PLANE_3 size: [%u, %u].\n\r",
                ui4_region_w, ui4_region_h);
        }
    }
    i4_ret = a_gl_zoom_mode_get_region_size(
                        GL_OSD_PLANE_1,
                        &ui4_region_w,
                        &ui4_region_h);
    if (i4_ret != GLR_OK)
    {
        if (0 != at_g_region_size[2].ui4_region_w ||
            0 != at_g_region_size[2].ui4_region_h)
        {
            b_is_region_size_changed = TRUE;

            at_g_region_size[2].ui4_region_w = 0;
            at_g_region_size[2].ui4_region_h = 0;

            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "OSD_PLANE_1 size: [0, 0].\n\r");
        }
    }
    else
    {
        if (ui4_region_w != at_g_region_size[2].ui4_region_w ||
            ui4_region_h != at_g_region_size[2].ui4_region_h)
        {
            b_is_region_size_changed = TRUE;

            at_g_region_size[2].ui4_region_w = ui4_region_w;
            at_g_region_size[2].ui4_region_h = ui4_region_h;

            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "OSD_PLANE_1 size: [%u, %u].\n\r",
                ui4_region_w, ui4_region_h);
        }
    }

    return;
}


//#ifdef VIZIO_FUSION_SUPPORT
static INT32 _nav_zoom_get_sector_with_plane_and_item(
                ZOOM_SECTOR_ITEM        e_item,
                GL_OSD_PLANE_T          e_plane,
                GL_OSD_ZOOM_SECTOR_T*   pt_zoom_sector
                )
{
    UINT32      ui4_screen_w = 0;
    UINT32      ui4_screen_h = 0;
    INT32       i4_item = (INT32)e_item-1;

    if (!pt_zoom_sector || e_item < ZOOM_SECTOR_ITEM_1 || e_item > ZOOM_SECTOR_ITEM_9)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "argv is invalid, e_item: %d.\n\r", e_item);
        return NAVR_INV_ARG;
    }

    if (GL_OSD_PLANE_2 == e_plane)
    {
        ui4_screen_w = at_g_region_size[0].ui4_region_w;
        ui4_screen_h = at_g_region_size[0].ui4_region_h;
    }
    else if (GL_OSD_PLANE_3 == e_plane)
    {
        ui4_screen_w = at_g_region_size[1].ui4_region_w;
        ui4_screen_h = at_g_region_size[1].ui4_region_h;
    }
    else if(GL_OSD_PLANE_1 == e_plane)
    {
        ui4_screen_w = at_g_region_size[2].ui4_region_w;
        ui4_screen_h = at_g_region_size[2].ui4_region_h;
    }
    else
    {
        return NAVR_FAIL;
    }

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "select sector: [%d], plane: [%d], size: [%u, %u].\n\r",
            e_item, e_plane, ui4_screen_w, ui4_screen_h);

    pt_zoom_sector->e_plane = e_plane;
#if 0
    pt_zoom_sector->ui4_X = (ui4_screen_w/4)*(i4_item%3);
    pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*(i4_item/3);
#endif

    switch(e_item)
    {
        case ZOOM_SECTOR_ITEM_1:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*0;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*0;
            break;
        }
        case ZOOM_SECTOR_ITEM_2:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*1;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*0;
            break;
        }
        case ZOOM_SECTOR_ITEM_3:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*2;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*0;
            break;
        }
        case ZOOM_SECTOR_ITEM_4:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*0;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*1;
            break;
        }
        case ZOOM_SECTOR_ITEM_5:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*1;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*1;
            break;
        }
        case ZOOM_SECTOR_ITEM_6:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*2;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*1;
            break;
        }
        case ZOOM_SECTOR_ITEM_7:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*0;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*2;
            break;
        }
        case ZOOM_SECTOR_ITEM_8:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*1;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*2;
            break;
        }
        case ZOOM_SECTOR_ITEM_9:
        {
            pt_zoom_sector->ui4_X = (ui4_screen_w/4)*2;
            pt_zoom_sector->ui4_Y = (ui4_screen_h/4)*2;
            break;
        }
        default:
        {
            KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", " select sector error. \n\r");
            break;
        }

    }

    pt_zoom_sector->ui4_W = ui4_screen_w/2;
    pt_zoom_sector->ui4_H = ui4_screen_h/2;

    return NAVR_OK;
}
//#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_check_sector_has_content
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_zoom_cust_check_sector_has_content(ZOOM_SECTOR_ITEM e_item)
{
    if (e_item < ZOOM_SECTOR_ITEM_1 || e_item > ZOOM_SECTOR_ITEM_9)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "argv is invalid, sector: %d.\n\r", e_item);
        return FALSE;
    }

    return a_zoom_check_sector_has_content(e_item);
}

 /*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_navi_sector
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_cust_navi_sector(ZOOM_SECTOR_ITEM e_item)
{
    INT32                   i4_ret = NAVR_OK;
    GL_OSD_ZOOM_SECTOR_T    at_zoom_sector[3];

    if (!b_is_enabled)
    {
        return NAVR_OK;
    }

    if (e_item < ZOOM_SECTOR_ITEM_1 || e_item > ZOOM_SECTOR_ITEM_9)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "argv is invalid, sector: %d.\n\r", e_item);
        return NAVR_INV_ARG;
    }
    if(e_current_sector != e_item)
    {
        nav_zoom_mode_indicate_icon_hide(NULL, NULL, NULL);
    }
    /* update region size first */
    _nav_zoom_cust_update_region_size();

    /* get rect with sector item */
    c_memset(at_zoom_sector, 0, 3 * sizeof(GL_OSD_ZOOM_SECTOR_T));
    i4_ret = _nav_zoom_get_sector_with_plane_and_item(e_item, GL_OSD_PLANE_2, &at_zoom_sector[0]);
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "nav_zoom get_sector_with_plane_and_item failed.\n\r");
    }
    i4_ret = _nav_zoom_get_sector_with_plane_and_item(e_item, GL_OSD_PLANE_3, &at_zoom_sector[1]);
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "nav_zoom get_sector_with_plane_and_item failed.\n\r");
    }
    if(_nav_zoom_cust_zoom_osd1())
    {
        i4_ret = _nav_zoom_get_sector_with_plane_and_item(e_item, GL_OSD_PLANE_1, &at_zoom_sector[2]);
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "nav_zoom get_sector_with_plane_and_item failed.\n\r");
        }
        i4_ret = nav_zoom_mode_enlarge_sector(at_zoom_sector, 3);
    }
    else
    {
        /* start enlarge sector */
        i4_ret = nav_zoom_mode_enlarge_sector(at_zoom_sector, 2);
    }
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "a_nav zoom_mode_enlarge_sector failed.\n\r");
    }

    b_is_region_size_changed = FALSE;

    e_current_sector = e_item;

    /* show the sector indicate */
    if(i4_ret == NAVR_OK)
    {
        i4_ret = nav_zoom_sector_indicate_activate((UINT8)e_item);
    }
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_zoom_mode indicate_activate failed.\n\r");
        return NAVR_FAIL;
    }
    /*move the position of zoom dialog to sector 5.*/
    //i4_ret = nav_zoom_mode_msg_move(e_item, FALSE);
    //NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

static VOID _nav_zoom_cust_select_top_sector_handler (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32                   i4_ret = 0;
    ZOOM_SECTOR_ITEM        e_sector_item = a_zoom_get_1st_sector_item_from_slist();

    if (e_sector_item != ZOOM_SECTOR_INVALID_ITEM)
    {
        /* start navi sector */
        KK_LOG(KK_LOG_LVL_KEY,"[ZOOM]","select to %d\n\r",e_sector_item);
        i4_ret = _nav_zoom_cust_navi_sector(e_sector_item);
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
            return;
        }
    }
    else
    {
         i4_ret = _nav_zoom_cust_navi_sector(ZOOM_SECTOR_ITEM_5);
         if (NAVR_OK != i4_ret)
         {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
            return;
         }
        /* do nothing */
    }
}

static VOID _nav_zoom_cust_timer_region_check_cb_fct (HANDLE_T  pt_tm_handle,
                                                      VOID*     pv_tag)
{
    if (!b_is_enabled)
    {
        c_timer_stop(pt_tm_handle);
        return;
    }

    /* update region size */
    _nav_zoom_cust_update_region_size();

    if (b_is_region_size_changed)
    {
        KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "region size is changed !\n\r");

        b_is_region_size_changed = FALSE;
        nav_request_context_switch(_nav_zoom_cust_select_top_sector_handler, NULL, NULL, NULL);
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_navi_sector_with_id
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_cust_navi_sector_with_id(UINT16 ui2_id)
{
    INT32                   i4_ret = NAVR_OK;
    ZOOM_SECTOR_ITEM        e_sector_item = ZOOM_SECTOR_INVALID_ITEM;
    UINT8                   ui1_app_id = ZOOM_APP_GRPID_3RD_APP;
    UINT8                   ui1_comp_id = ZOOM_APP_RECID_APP_DEFAULT;

    ui1_app_id = ZOOM_GET_GROUP(ui2_id);
    ui1_comp_id = ZOOM_GET_IDX(ui2_id);
    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "app_id: %u, comp_id: %u.\n\r", ui1_app_id, ui1_comp_id);


    /* get zoom sector from slist */
    e_sector_item = a_zoom_get_sector_item_from_slist(ui2_id);

    /* get default zoom sector */
    if (e_sector_item == ZOOM_SECTOR_INVALID_ITEM)
    {
        e_sector_item = nav_zoom_cust_get_default_sector_item(ui2_id);
    }
    else
    {
        if (ui1_app_id==ZOOM_APP_GRPID_3RD_APP && ui1_comp_id==ZOOM_APP_RECID_APP_FULL_SCREEN)
        {
            KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "3rd_full_screen has in list.\n\r");
            return NAVR_OK;
        }
    }
    if (ZOOM_SECTOR_INVALID_ITEM == e_sector_item)
    {
        e_sector_item = ZOOM_SECTOR_DEFAULT_ITEM;
    }

    /* start navi sector */
    i4_ret = _nav_zoom_cust_navi_sector(e_sector_item);
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
        return NAVR_FAIL;
    }
    DBG_LOG_PRINT(("[zoom] {%s %s() %d}. ui1_comp_id = %d,e_sector_item = %d\n",__FILE__, __FUNCTION__, __LINE__,ui1_comp_id,e_sector_item));
    /* need add item to slist */
    a_zoom_add_field_into_slist_head(ui2_id, e_sector_item);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_navi_default_sector
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_cust_navi_default_sector(VOID)
{
    INT32                   i4_ret = NAVR_OK;
    UINT8                   ui1_value = APP_CFG_CUST_ZOOM_MODE_OFF;
    CHAR                    s_app_name[APP_NAME_MAX_LEN];
    UINT8                   ui1_app_id = ZOOM_APP_GRPID_NAV;
    UINT8                   ui1_comp_id = 0;
    UINT8                   ui1_idx = 0;
    NAV_COMP_ID_T           e_active_comp = NAV_COMP_ID_LAST_VALID_ENTRY;

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "Enter.\n\r");

    //i4_ret = a_cfg_cust_get_zoom_mode(&ui1_value);
    i4_ret = a_cfg_cust_get_zoom_status(&ui1_value);
    if (APP_CFGR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_cfg_cust get_zoom_mode failed.\n\r");
        return NAVR_FAIL;
    }

    if (ui1_value != APP_CFG_CUST_ZOOM_MODE_ON)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "current_zoom_mode is NOT on.\n\r");
        return NAVR_FAIL;
    }

    /* check yahoo and 3rd app status first */
    UINT8                   ui1_yahoo_status;
    UINT8                   ui1_app_status;

    /* get network widget dock status */
    i4_ret = a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_yahoo_status);
    if (ICLR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_icl_custom get_nw_widget_status.\n\r");
        return NAVR_FAIL;
    }

    /* get network app status */
    i4_ret = a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_APP, &ui1_app_status);
    if (ICLR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_icl_custom get_nw_widget_status.\n\r");
        return NAVR_FAIL;
    }

    if ((YAHOO_STATUS_HIDE != ui1_yahoo_status || NW_APP_STATUS_HIDE != ui1_app_status))
    {
        _nav_zoom_cust_select_sector_with_app_status();
        return NAVR_OK;
    }

    /* check active app */

    if (b_is_zoom_on_from_power_on)
    {
        DBG_LOG_PRINT(("%s:%d,first zoom when power on,don't set sector.\r\n",__FILE__,__LINE__));
        return NAVR_FAIL;
    }
    i4_ret = a_am_get_active_app(s_app_name);
    if (AMR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_am get_active_app failed.\n\r");
        return NAVR_FAIL;
    }
    if (0 == c_strcmp (s_app_name, NAV_NAME))
    {
        ui1_app_id = ZOOM_APP_GRPID_NAV;
    }
    else if (0 == c_strcmp (s_app_name, MENU_NAME))
    {
        ui1_app_id = ZOOM_APP_GRPID_MENU;
    }
    else if (0 == c_strcmp (s_app_name, MMP_NAME))
    {
        ui1_app_id = ZOOM_APP_GRPID_MMP;
    }
    else
    {
        return NAVR_FAIL;
    }

    /* check active or visiable app comp */
    if (ui1_app_id == ZOOM_APP_GRPID_MENU)
    {
        //TODO: get comp id from menu
        ui1_comp_id = ZOOM_APP_RECID_MENU_DEFAULT;
    }
    else if (ui1_app_id == ZOOM_APP_GRPID_MMP)
    {
        ui1_comp_id = ZOOM_APP_RECID_MMP_DEFAULT;
    }
    else if (ui1_app_id == ZOOM_APP_GRPID_NAV)
    {
        ui1_comp_id = ZOOM_APP_RECID_NAV_DEFAULT;

        do {
            e_active_comp = nav_get_active_component();
            if (ZOOM_SECTOR_INVALID_ITEM != nav_zoom_cust_get_default_sector_item(ZOOM_MAKE_ID(ui1_app_id, (UINT8)e_active_comp)))
            {
                ui1_comp_id = (UINT8)e_active_comp;
                break;
            }

            if (FALSE == nav_any_component_visible())
            {
                break;
            }

            for (ui1_idx = 0; ui1_idx < NAV_COMP_ID_LAST_VALID_ENTRY; ui1_idx++)
            {
                if (TRUE == nav_is_component_visible(ui1_idx)
                    && ZOOM_SECTOR_INVALID_ITEM != nav_zoom_cust_get_default_sector_item(ZOOM_MAKE_ID(ui1_app_id, ui1_idx)))
                {
                    ui1_comp_id = ui1_idx;
                    break;
                }
            }

        }while(0);
    }
#if 0 /*dead logic code*/
    else
    {
        return NAVR_OK;
    }
#endif

    /* start default zoom sector with app id and comp id */
    i4_ret = _nav_zoom_cust_navi_sector_with_id(ZOOM_MAKE_ID(ui1_app_id, ui1_comp_id));
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_pause
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_cust_pause()
{
    INT32                   i4_ret = NAVR_OK;
    _NAV_ZOOM_CUST_T*       pt_this = &t_g_zoom_cust;

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "_nav_zoom_cust_pause.\n\r");
    /* stop region check timer */
    i4_ret = c_timer_stop(pt_this->h_timer_region_check);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
    }

    i4_ret = nav_zoom_mode_disable();
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_nav zoom_mode_disable failed.\n\r");
        return;
    }
    b_zoom_pause = TRUE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_recover
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_cust_recover()
{
    INT32                   i4_ret = NAVR_OK;
    _NAV_ZOOM_CUST_T*       pt_this = &t_g_zoom_cust;

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "_nav_zoom_cust_recover.\n\r");
    /* re-start region check timer */
    i4_ret = c_timer_stop(pt_this->h_timer_region_check);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
    }
    i4_ret = c_timer_start(pt_this->h_timer_region_check,
                    500,
                    X_TIMER_FLAG_REPEAT,
                    _nav_zoom_cust_timer_region_check_cb_fct,
                    NULL);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer start failed.\n\r");
    }

    i4_ret = nav_zoom_mode_enable();
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_nav nav_zoom_mode_enable failed.\n\r");
        return;
    }
    a_nav_zoom_cust_select_top_sector();
    b_zoom_pause = FALSE;

    return;
}

/**
 * @brief   This function handles keys from IOM notifications.
 * @param   pv_tag1 [in]  e_nfy_cond
 * @param   pv_tag2 [in]  ui4_evt_code
 * @param   pv_tag3 [in]  NULL
 * @retval  NAVR_OK         This function executed successfully.
 * @retval  Otherwise       This function failed.
 */
static VOID _nav_zoom_cust_iom_handler(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32                   i4_ret = NAVR_OK;
    _NAV_ZOOM_CUST_T*       pt_this = &t_g_zoom_cust;
    IOM_NFY_COND_T          e_nfy_cond = (IOM_NFY_COND_T)(UINT32)pv_tag1;
    UINT32                  ui4_evt_code = (UINT32)pv_tag2;
    UINT32                  ui4_key_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);
    ZOOM_SECTOR_ITEM        e_sector_item = ZOOM_SECTOR_DEFAULT_ITEM;
    BOOL                    b_is_start = pt_this->b_is_num_pad_navi_start;
    UINT16                  ui2_msg_mlm_idx    = 0 ;

    if (!b_is_enabled)
    {
        return;
    }

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "ui4_key_code = 0x%x b_is_enabled = %d\n\r",ui4_key_code,b_is_enabled);

#if 1
    if ((BTN_GFX_ZOOM_NAVIGATION == ui4_key_code)&&(!nav_is_channel_scan_active()))
    {
        if (IOM_NFY_COND_BTN_DOWN == e_nfy_cond)
        {
            KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "BTN_GFX_ZOOM_NAVIGATION BTN_DOWN.\n\r");

            b_is_start = !b_is_start;

            /*show the text msg when num pad switch between zoom mode and digit mode.*/
            if (b_is_start)
            {
                ui2_msg_mlm_idx = MLM_SETTINGS_KEY_NUM_PAD_IN_ZOOM;
                _nav_zoom_cust_dash_set_digital_pad_status(FALSE);
            }
            else
            {
                ui2_msg_mlm_idx = MLM_SETTINGS_KEY_NUM_PAD_IN_DIGIT;
                _nav_zoom_cust_dash_set_digital_pad_status(TRUE);
            }
            //i4_ret = nav_zoom_mode_msg_show(ui2_msg_mlm_idx);
            i4_ret = nav_zoom_mode_send_toast_msg(ui2_msg_mlm_idx);
            if (NAVR_OK != i4_ret)
            {
                KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_mode msg_show failed.\n\r");
            }
            _nav_zoom_cust_set_num_pad_navi_enable(b_is_start);
        }

        ZOOM_SECTOR_ITEM e_sector = nav_zoom_cust_get_current_sector_item();
        UINT32 i4_nav_active_id   = nav_get_active_component();
        /* DTV02203243 : press dash key && set defult ZOOM_SECTOR_ITEM_2 for NAV_COMP_ID_REVOLT_INFO*/
        if(( NAV_COMP_ID_REVOLT_INFO == i4_nav_active_id) && (ZOOM_SECTOR_ITEM_2 != e_sector ))
        {
            a_nav_zoom_cust_select_sector(ZOOM_SECTOR_ITEM_2,TRUE);
        }

        DBG_LOG_PRINT(("\n\n[ zoom +++ ] {%s %s() %d}. e_sector = %d,i4_nav_active_id = %d\n\n",
                       __FILE__, __FUNCTION__, __LINE__,e_sector,NAV_COMP_ID_REVOLT_INFO == i4_nav_active_id));
        return ;
    }
#endif

    if ((ui4_key_code >= BTN_GFX_ZOOM_SECTOR_1 && ui4_key_code <= BTN_GFX_ZOOM_SECTOR_9))
    {
        if (IOM_NFY_COND_BTN_DOWN == e_nfy_cond)
        {
            KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "BTN_DIGIT_X BTN_DOWN.\n\r");

            e_sector_item = (ui4_key_code - BTN_GFX_ZOOM_SECTOR_1) + ZOOM_SECTOR_ITEM_1;

            KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "e_sector_item = %d \n\r",e_sector_item);

            /* check select sector has content or not */
            if (FALSE == _nav_zoom_cust_check_sector_has_content(e_sector_item))
            {
                KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "_nav_zoom_cust check_sector_has_content is FALSE.\n\r");

                /* show msg dialog */
                ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NO_CONTENT;
                //i4_ret = nav_zoom_mode_msg_show(ui2_msg_mlm_idx);
                if((nav_get_active_component() == NAV_COMP_ID_REVOLT_INFO)&&(nav_zoom_cust_get_current_sector_item()!= ZOOM_SECTOR_ITEM_2))
                {
                    a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO));
                    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO));
                }
                i4_ret = nav_zoom_mode_send_toast_msg(ui2_msg_mlm_idx);
                if (NAVR_OK != i4_ret)
                {
                    KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_mode msg_show failed.\n\r");
                }

                return;
            }
            else
            {
                KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "_nav_zoom_cust check_sector_has_content is TRUE.\n\r");

                /* hide msg dialog */
                //nav_zoom_mode_msg_hide();
            }

            if (b_zoom_pause == TRUE)
            {
                b_zoom_pause = FALSE;
                i4_ret = nav_zoom_mode_enable();
                if (NAVR_OK != i4_ret)
                {
                    KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_nav nav_zoom_mode_enable failed.\n\r");
                    return;
                }
            }

            /* start navi sector */
            i4_ret = _nav_zoom_cust_navi_sector(e_sector_item);
            if (NAVR_OK != i4_ret)
            {
                KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
                return;
            }

            a_zoom_update_1st_sector_item_in_slist(e_sector_item);
        }
    }

    if(_nav_zoom_cust_dash_get_digital_pad_status() == FALSE)
    {
        /* Pause zoom mode by "0" key when number pad in zoom mode. "0" and other digit key can recover zoom mode. */
        if (ui4_key_code == BTN_DIGIT_0)
        {
            if (b_zoom_pause == FALSE)
            {
                _nav_zoom_cust_pause();
            }
            else
            {
                _nav_zoom_cust_recover();
            }
        }
    }
    else
    {
/* DTV02196394 always shows the messageNumber pad in Digital mode*/
#if 0
        if (ui4_key_code == BTN_DIGIT_0)
        {
            i4_ret = nav_zoom_mode_send_toast_msg(MLM_SETTINGS_KEY_NUM_PAD_IN_DIGIT);
            if (NAVR_OK != i4_ret)
            {
                KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_mode msg_show failed.\n\r");
            }
        }
#endif
        DBG_LOG_PRINT(("[dash +++] {%s %s() %d}. digtial pad, disable resume/pasue zoom mode !!!\n",__FILE__, __FUNCTION__, __LINE__));
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_cust_deinit(VOID)
{
    _NAV_ZOOM_CUST_T*       pt_this = &t_g_zoom_cust;

    /* free resoruce */
    if (c_handle_valid(pt_this->h_timer_region_check) == TRUE)
    {
        c_timer_delete(pt_this->h_timer_region_check);
        pt_this->h_timer_region_check = NULL_HANDLE;
    }

    /* Close the opened device referenced by h_iom */
    if (pt_this->h_iom != NULL_HANDLE)
    {
        c_iom_close(pt_this->h_iom);
        pt_this->h_iom = NULL_HANDLE;
    }

    /* Unregister notify */
    if (APP_CFG_NOTIFY_NULL_ID != pt_this->ui2_zoom_mode_cfg_nfy)
    {
        a_cfg_notify_unreg(pt_this->ui2_zoom_mode_cfg_nfy);
        pt_this->ui2_zoom_mode_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
    }

    if (0xFFFF != pt_this->ui2_icl_app_status_nfy_id)
    {
        a_icl_notify_unreg(pt_this->ui2_icl_app_status_nfy_id);
        pt_this->ui2_icl_app_status_nfy_id = 0xFFFF;
    }

    if (0xFFFF != pt_this->ui2_icl_net_tv_svc_nfy_id)
    {
        a_icl_notify_unreg(pt_this->ui2_icl_net_tv_svc_nfy_id);
        pt_this->ui2_icl_net_tv_svc_nfy_id = 0xFFFF;
    }

    /* zero memory */
    c_memset(pt_this, 0, sizeof(_NAV_ZOOM_CUST_T));

    return NAVR_OK;
}

static INT32 _nav_zoom_cust_set_num_pad_navi_enable(BOOL b_enabled)
{
    _NAV_ZOOM_CUST_T*           pt_this = &t_g_zoom_cust;

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "num_pad_navi_enabled: [%d], enable: [%d].\n\r",
            pt_this->b_is_num_pad_navi_start, b_enabled);
    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "num_pad_navi_enabled: [%d], enable: [%d].\n\r",
            pt_this->b_is_num_pad_navi_start, b_enabled);

    pt_this->b_is_num_pad_navi_start = b_enabled;

    /* 1. send num pad zoom mode state to EAM when zoom mode change */
    if (b_enabled)
    {
        a_tv_net_send_cmd("\n:dtv_app_mtk,am,:num_pad_zoom_nav_mode_enable\n");
    }
    else
    {
        a_tv_net_send_cmd("\n:dtv_app_mtk,am,:num_pad_zoom_nav_mode_disable\n");
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_cfg_change_msg_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_cust_cfg_change_msg_hdlr(
    VOID*                               pv_unused,
    VOID*                               pv_unused2,
    VOID*                               pv_unused3)
{
    INT32                       i4_ret;
    _NAV_ZOOM_CUST_T*           pt_this = &t_g_zoom_cust;
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;
    BOOL                        b_is_start = FALSE;
    BOOL                        b_is_need_show_msg = TRUE;
    UINT16                      ui2_msg_mlm_idx    = 0 ;
    ZOOM_SECTOR_ITEM            e_sector_item = ZOOM_SECTOR_INVALID_ITEM;

    //i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);
    i4_ret = a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
    if (APP_CFGR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_cfg_cust get_zoom_mode failed.\n\r");
        return;
    }

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "zoom_mode: %s.\n\r", ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON ? "ON" : "OFF");

    b_is_start = (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON) ? TRUE : FALSE;

    if (!b_is_start && !b_is_enabled)
    {
        b_is_need_show_msg = FALSE;
    }

    b_is_enabled = b_is_start;

    if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        i4_ret = nav_zoom_mode_enable();
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_nav zoom_mode_enable failed.\n\r");
            return;
        }

        /* send zoom mode state to EAM when zoom mode change */
        a_tv_net_send_cmd("\n:dtv_app_mtk,am,:zoom_mode_enable\n");

        _nav_zoom_cust_set_num_pad_navi_enable(b_is_start);

        /* re-start region check timer */
        i4_ret = c_timer_stop(pt_this->h_timer_region_check);
        if (OSR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
        }
        i4_ret = c_timer_start(pt_this->h_timer_region_check,
                        500,
                        X_TIMER_FLAG_REPEAT,
                        _nav_zoom_cust_timer_region_check_cb_fct,
                        NULL);
        if (OSR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer start failed.\n\r");
        }

        e_sector_item = a_zoom_get_1st_sector_item_from_slist();
        if (e_sector_item != ZOOM_SECTOR_INVALID_ITEM)
        {
        	/* REVOLT_INFO is activate and display zoom mode is off */
        	UINT32 i4_nav_active_id = nav_get_active_component();

			if(NAV_COMP_ID_REVOLT_INFO == i4_nav_active_id)
			{
				e_sector_item = nav_zoom_cust_get_default_sector_item(ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO));
				KK_LOG(KK_LOG_LVL_NORMAL, "[zoom_mode]", "zoom_mode: now: i4_nav_active_id (%d), ***SET default_sector(%d).\n\r",i4_nav_active_id,e_sector_item);

				a_zoom_move_field_to_slist_head(ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO));

			}
            else
            {
               /*change acfg,notify zoom mode info and set sector 2.*/
               i4_ret =  _nav_zoom_cust_navi_sector_with_id(ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_REVOLT_INFO));
               if (NAVR_OK != i4_ret)
               {
                   KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust_navi_sector_with_id failed.\n\r");
                   return;
               }
            }
            /* start navi sector */
            i4_ret = _nav_zoom_cust_navi_sector(e_sector_item);
            if (NAVR_OK != i4_ret)
            {
                KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
                return;
            }
        }
        else
        {
            i4_ret = _nav_zoom_cust_navi_default_sector();
            if (NAVR_OK != i4_ret)
            {
                KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "_nav_zoom_cust navi_default_sector failed.\n\r");

                i4_ret = _nav_zoom_cust_navi_sector(ZOOM_SECTOR_ITEM_5);
                if (NAVR_OK != i4_ret)
                {
                    KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
                    return;
                }
            }
        }

        /* show zoom mode enable msg */
#if NAV_ZOOM_NAVIGATION_ENABLE
        if (a_cfg_cust_zoom_digit_selection_support())
        {
            ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NAV_MODE_ON;
        }
        else
        {
            ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NAV_MODE_NO_NUMBER_PAD_ON;

        }
#else
        ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_MODE_ON;
#endif

#if NAV_ZOOM_ON_TITLE_ADD_IMG
			UTF16_T w2s_str[512] = {0};
			c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), ui2_msg_mlm_idx));
			i4_ret = nav_zoom_mode_show_img_title(w2s_str);
#else
	        i4_ret = nav_zoom_mode_send_toast_msg(ui2_msg_mlm_idx);
#endif

        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_mode msg_show MLM_SETTINGS_KEY_ZOOM_MODE_ON failed.\n\r");
        }
    }
    else
    {
        /* stop region check timer */
        i4_ret = c_timer_stop(pt_this->h_timer_region_check);
        if (OSR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
        }

        i4_ret = nav_zoom_mode_disable();
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_nav zoom_mode_disable failed.\n\r");
            return;
        }
        b_zoom_pause = FALSE;

        /* show zoom mode disable msg */
        if (b_is_need_show_msg)
        {
            ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_MODE_OFF;
		#if NAV_ZOOM_ON_TITLE_ADD_IMG
			UTF16_T w2s_str[512] = {0};
			c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), ui2_msg_mlm_idx));
			i4_ret = nav_zoom_mode_show_img_title(w2s_str);
		#else
            i4_ret = nav_zoom_mode_send_toast_msg(ui2_msg_mlm_idx);
		#endif
            if (NAVR_OK != i4_ret)
            {
                KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_mode msg_show MLM_SETTINGS_KEY_ZOOM_MODE_OFF failed.\n\r");
            }
        }

        _nav_zoom_cust_set_num_pad_navi_enable(b_is_start);

        /* send zoom mode state to EAM when zoom mode change */
        a_tv_net_send_cmd("\n:dtv_app_mtk,am,:zoom_mode_disable\n");
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_cfg_change_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_cust_cfg_change_cb (
                UINT16              ui2_nfy_id,
                VOID*               pv_tag,
                UINT16              ui2_id)
{
    _NAV_ZOOM_CUST_T*             pt_this;

    if (CFG_MAKE_ID(APP_CFG_GRPID_CUST_MISC_BASE, APP_CFG_RECID_CUST_ZOOM_MODE) == ui2_id)
    {
        pt_this = &t_g_zoom_cust;

        if (pt_this->ui2_zoom_mode_cfg_nfy == ui2_nfy_id)
        {
            /*post a message to itself*/
            nav_request_context_switch(_nav_zoom_cust_cfg_change_msg_hdlr,
                                       NULL,
                                       NULL,
                                       NULL);
        }
    }
}

static VOID _nav_zoom_cust_select_sector_with_app_status (VOID)
{
    INT32                   i4_ret = 0;
    UINT8                   ui1_app_id = ZOOM_APP_GRPID_3RD_APP;
    UINT8                   ui1_comp_id = ZOOM_APP_RECID_APP_DEFAULT;
    UINT8                   ui1_yahoo_status;
    UINT8                   ui1_app_status;
    ZOOM_SECTOR_ITEM        e_sector_item;

    /* get network widget dock status */
    i4_ret = a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_yahoo_status);
    if (ICLR_OK != i4_ret)
    {
       return;
    }

    /* get network app status */
    i4_ret = a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_APP, &ui1_app_status);
    if (ICLR_OK != i4_ret)
    {
       return;
    }

    KK_LOG(KK_LOG_LVL_KEY, "[ZOOM]", "yahoo and 3rd app status: [%u, %u].\n\r", ui1_yahoo_status, ui1_app_status);

    if (YAHOO_STATUS_HIDE == ui1_yahoo_status &&
        NW_APP_STATUS_HIDE == ui1_app_status)
    {
       KK_LOG(KK_LOG_LVL_WARN, "[ZOOM]", "yahoo and 3rd app are HIDE.\n\r");

       a_zoom_remove_fields_from_slist(ui1_app_id);

       e_sector_item = a_zoom_get_1st_sector_item_from_slist();
       if (e_sector_item != ZOOM_SECTOR_INVALID_ITEM)
       {
           /* start navi sector */
           i4_ret = _nav_zoom_cust_navi_sector(e_sector_item);
           if (NAVR_OK != i4_ret)
           {
               KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
               return;
           }
       }
       else
       {
           /* do nothing */
       }

       return;
    }
    else if (ui1_yahoo_status == YAHOO_STATUS_DOCK_UP)
    {
       ui1_comp_id = ZOOM_APP_RECID_YH_DOCK;
    }
    else if (ui1_yahoo_status == YAHOO_STATUS_SIDEBAR)
    {
       ui1_comp_id = ZOOM_APP_RECID_YH_SIDEBAR;
    }
    else
    {
       ui1_comp_id = ZOOM_APP_RECID_APP_FULL_SCREEN;
    }

    /* start default zoom sector with app id and comp id */
    i4_ret = _nav_zoom_cust_navi_sector_with_id(ZOOM_MAKE_ID(ui1_app_id, ui1_comp_id));
    if (NAVR_OK != i4_ret)
    {
       KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
       return;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_icl_app_status_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_cust_icl_app_status_handler (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
#if 0
    INT32                   i4_ret = ICLR_OK;
    UINT8                   ui1_val = APP_STATUS_LAST_ENTRY;
    UINT8                   ui1_app_id = ZOOM_APP_GRPID_3RD_APP;
    UINT8                   ui1_comp_id = 0;

    i4_ret = a_icl_get_app_status(&ui1_val);
    if (ICLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get icl rec. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
    }

    if (APP_STATUS_YH_DOCK == ui1_val)
    {
        ui1_comp_id = ZOOM_APP_RECID_YH_DOCK;
    }
    else if (APP_STATUS_YH_SIDEBAR == ui1_val)
    {
        ui1_comp_id = ZOOM_APP_RECID_YH_SIDEBAR;
    }
    else
    {
        return;
    }

    /* start default zoom sector with app id and comp id */
    i4_ret = _nav_zoom_cust_navi_sector_with_id(ZOOM_MAKE_ID(ui1_app_id, ui1_comp_id));
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
        return;
    }
#else
    _nav_zoom_cust_select_sector_with_app_status();
#endif

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_icl_net_tv_svc_status_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_zoom_cust_icl_net_tv_svc_status_handler (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32                   i4_ret = ICLR_OK;
    UINT8                   ui1_val = APP_STATUS_NET_TV_SVC_PAUSE;
    UINT8                   ui1_app_id = ZOOM_APP_GRPID_3RD_APP;
    UINT8                   ui1_comp_id = 0;

    i4_ret = a_icl_get_net_tv_svc_status(&ui1_val);
    if (ICLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get icl rec. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
    }

    if (APP_STATUS_NET_TV_SVC_RESUMED == ui1_val)
    {
        ui1_comp_id = ZOOM_APP_RECID_APP_FULL_SCREEN;
    }
    else
    {
        return;
    }

    /* start default zoom sector with app id and comp id */
    i4_ret = _nav_zoom_cust_navi_sector_with_id(ZOOM_MAKE_ID(ui1_app_id, ui1_comp_id));
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
        return;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_icl_app_status_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_cust_icl_app_status_cb (
                UINT16              ui2_nfy_id,
                VOID*               pv_tag,
                ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    return nav_request_context_switch(_nav_zoom_cust_icl_app_status_handler,
                                      NULL,
                                      NULL,
                                      NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_zoom_cust_icl_net_tv_svc_status_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_zoom_cust_icl_net_tv_svc_status_cb (
                UINT16              ui2_nfy_id,
                VOID*               pv_tag,
                ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    return nav_request_context_switch(_nav_zoom_cust_icl_net_tv_svc_status_handler,
                                      NULL,
                                      NULL,
                                      NULL);
}

static VOID _nav_zoom_cust_iom_cb_func (
                VOID*               pv_nfy_tag,
                IOM_NFY_COND_T      e_nfy_cond,
                UINT32              ui4_evt_code,
                UINT32              ui4_data)
{
    if (e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        nav_request_context_switch(_nav_zoom_cust_iom_handler,
                                   (VOID*) (UINT32)e_nfy_cond,
                                   (VOID*) ui4_evt_code,
                                   NULL);
    }
    return;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_cust_comp_state_trans_nfy (
    NAV_COMP_STATE_TRANS_COND_T e_cond,
    NAV_COMP_ID_T               e_from_comp_id,
    NAV_COMP_ID_T               e_to_comp_id)
{

    if (!b_is_enabled)
    {
        return NAVR_OK;
    }

#if 0
    UINT8                   ui1_comp_id = ZOOM_APP_RECID_NAV_DEFAULT;

    if (!nav_is_active() || nav_is_pausing())
    {
        return NAVR_OK;
    }

    if (e_cond == NAV_COMP_STATE_TRANS_BEFORE_ACTIVATION_CHANGE)
    {
        /* do nothing */
    }
    else if (e_cond == NAV_COMP_STATE_TRANS_AFTER_ACTIVATION_CHANGE)
    {
        KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "from_comp_id: %d, to_comp_id: %d.\n\r", (INT32)e_from_comp_id, (INT32)e_to_comp_id);

        if (e_to_comp_id == NAV_COMP_ID_LAST_VALID_ENTRY)
        {
            ui1_comp_id = ZOOM_APP_RECID_NAV_DEFAULT;
        }
        else
        {
            ui1_comp_id = (UINT8)e_to_comp_id;
        }


        _nav_zoom_cust_navi_sector_with_id(ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV, ui1_comp_id));
    }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_cust_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_cust_handle_msg (
    NAV_UI_MSG_T*               pt_ui_msg,
    VOID*                       pv_arg1
    )
{
    INT32                       i4_ret = 0;
    NAV_UI_MSG_ID_T             e_id;
    UINT8                       ui1_app_id = ZOOM_APP_GRPID_MENU;
    UINT8                       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;
    CHAR                        s_app_name[APP_NAME_MAX_LEN] = {0};

#if 0
     if((pt_ui_msg->e_id == NAV_UI_MSG_SYSTEM_POWER_ON)||
       (pt_ui_msg->e_id == NAV_UI_MSG_POWER_ON))
     {
            a_cfg_cust_get_zoom_status(&ui1_zoom_mode);

            if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
            {
               _nav_zoom_cust_set_num_pad_navi_enable(TRUE);
               _nav_zoom_cust_recover();
               nav_zoom_mode_send_toast_msg(MLM_SETTINGS_KEY_ZOOM_MODE_ON);
            }
     }

    if (b_is_first_zoom_on)
    {
        return NAVR_OK;
    }
#endif

    /* handle the message when NAV is pausing */
    e_id = (NAV_UI_MSG_AS_APP_PAUSED == pt_ui_msg->e_id)
         ? pt_ui_msg->e_id_as_paused
         : pt_ui_msg->e_id ;

    switch(e_id)
    {
    case NAV_UI_MSG_NO_ANY_VISIBLE_COMP:
        {
            a_zoom_remove_fields_from_slist(ZOOM_APP_GRPID_NAV);
            break;
        }

    case NAV_UI_MSG_OTHER_APP_PAUSED:
        {
            i4_ret = a_am_get_next_active_app(s_app_name);
            if (AMR_OK == i4_ret && 0 == c_strcmp (s_app_name, (CHAR*)pv_arg1))
            {
                break;
            }

            if (0 == c_strcmp ((CHAR*)pv_arg1, MENU_NAME))
            {
                ui1_app_id = ZOOM_APP_GRPID_MENU;
            }
            else
            {
                break;
            }

            a_zoom_remove_fields_from_slist(ui1_app_id);
        }
        break;

    case NAV_UI_MSG_SYSTEM_POWER_ON:
    case NAV_UI_MSG_POWER_ON:
        if (FALSE == b_is_first_zoom_on)
        {
            b_is_first_zoom_on = TRUE;
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] POWER ON.\n"));
#if 0 /*DTV02158836 no need*/
        #ifdef APP_TTS_SUPPORT
            //const UTF16_T* ps_power_msg = L"POWER ON";
            const UTF16_T* ps_power_msg = L"  POWER ON        ";
            a_app_tts_play_new_gap_just_once(ps_power_msg,c_uc_w2s_strlen(ps_power_msg),3);
        #endif
#endif
            //a_cfg_cust_get_zoom_mode(&ui1_zoom_mode);
            a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
            //a_cfg_cust_set_zoom_mode(ui1_zoom_mode);
            rest_event_notify("app/zoom/enabled", ui1_zoom_mode, "");
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] POWER ON. ui1_zoom_mode = %d\n",ui1_zoom_mode));
            if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
            {
               b_is_zoom_on_from_power_on = TRUE;
               _nav_zoom_cust_enable_wait_timer();
            }
        }
        break;

    case NAV_UI_MSG_POWER_OFF:
        {
            DBG_LOG_PRINT(("[NAV][ZOOM][Handle_Msg] POWER OFF.\n"));
            a_zoom_clean_slist();

			/*power on msg,wait for TTS play power on msg*/
            _nav_zoom_cust_disable_wait_timer();

            /*DTV02194182:Press RC Dash key can change channel when DUT in zoom mode(number pad in Digital mode) */
            _nav_zoom_cust_disable_dash_timer();
            /*default is zoom pad*/
            _nav_zoom_cust_dash_set_digital_pad_status(FALSE);

            b_is_zoom_on_from_power_on = FALSE;
            b_is_first_zoom_on = FALSE;
        }
        break;

    default:
        break;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_zoom_cust_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_zoom_cust_init(VOID)
{
    _NAV_ZOOM_CUST_T*       pt_this = &t_g_zoom_cust;
    INT32                   i4_ret;
    IRRC_SETTING_T          t_irrc_setting;

    do
    {
        /*init data member*/
        c_memset(at_g_region_size, 0, NAV_ZOOM_ENLARGE_OSD_NUM*sizeof(_ZOOM_REGION_SIZE_T));

        pt_this->ui2_zoom_mode_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
        pt_this->b_is_num_pad_navi_start = FALSE;

        pt_this->ui2_icl_app_status_nfy_id = 0xFFFF;
        pt_this->ui2_icl_net_tv_svc_nfy_id = 0xFFFF;

        i4_ret = c_timer_create(&(pt_this->h_timer_region_check));
        if (i4_ret != OSR_OK)
        {
            pt_this->h_timer_region_check = NULL_HANDLE;
            break;
        }

        i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_CUST_MISC_BASE,
                                  NULL,
                                  _nav_zoom_cust_cfg_change_cb,
                                  &pt_this->ui2_zoom_mode_cfg_nfy);
        if(APP_CFGR_OK != i4_ret)
        {
            pt_this->ui2_zoom_mode_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;
            break;
        }

    #if 0
        i4_ret = a_icl_notify_reg(ICL_GRPID_APP_STATUS,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _nav_zoom_cust_icl_app_status_cb,
                                  &pt_this->ui2_icl_app_status_nfy_id);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"register ICL_GRPID_APP_STATUS icl notify failed\r\n"));

            pt_this->ui2_icl_app_status_nfy_id = 0xFFFF;
            break;
        }
    #else
        i4_ret = a_icl_notify_reg(ICL_GRPID_CUSTOM_NW_WIDGET,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _nav_zoom_cust_icl_app_status_cb,
                                  &pt_this->ui2_icl_app_status_nfy_id);
        if (ICLR_OK != i4_ret)
        {
            pt_this->ui2_icl_app_status_nfy_id = 0xFFFF;
            break;
        }
   #endif

        if (0)
        {
        i4_ret = a_icl_notify_reg(ICL_GRPID_NET_TV_SVC_STATUS,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _nav_zoom_cust_icl_net_tv_svc_status_cb,
                                  &pt_this->ui2_icl_net_tv_svc_nfy_id);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"register ICL_GRPID_NET_TV_SVC_STATUS icl notify failed\r\n"));

            pt_this->ui2_icl_net_tv_svc_nfy_id = 0xFFFF;
            break;
        }
        }

        /* IOM open */
        c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
        t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;//(KEY_GROUP_TO_MASK(KEY_GROUP_PRG_CTRL));
        t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
        t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
        t_irrc_setting.b_notify_raw_data        = TRUE;

        i4_ret = c_iom_open(
                        IOM_DEV_TYPE_IN_IRRC,
                        IOM_DEV_ID_ANY,
                        NULL,
                        (VOID*)&t_irrc_setting,
                        NULL,
                        _nav_zoom_cust_iom_cb_func,
                        &pt_this->h_iom
                        );
        if (i4_ret != IOMR_OK)
        {
            DBG_ERROR((_ERROR_HEADER"register iom_nfy fail, i4_ret: %d.\r\n", i4_ret));
            break;
        }

        return NAVR_OK;

    } while(0);

    /* free resoruce */
    _nav_zoom_cust_deinit();

    return i4_ret;
}

ZOOM_SECTOR_ITEM nav_zoom_cust_get_default_sector_item(const UINT16 ui2_id)
{
    UINT16 ui2_i            = 0;
    UINT16 ui2_total_num    = sizeof(at_zoom_sector_mapping_id_table)/sizeof(_NAV_ZOOM_SECTOR_MAP_T);

    for (ui2_i = 0; ui2_i < ui2_total_num; ++ui2_i)
    {
        if (ui2_id == at_zoom_sector_mapping_id_table[ui2_i].ui2_id)
        {
            return at_zoom_sector_mapping_id_table[ui2_i].e_default_item;
        }
    }

    return ZOOM_SECTOR_INVALID_ITEM;
}

ZOOM_SECTOR_SET_T nav_zoom_cust_get_include_items(const UINT16 ui2_id)
{
    UINT16 ui2_i            = 0;
    UINT16 ui2_total_num    = sizeof(at_zoom_sector_mapping_id_table)/sizeof(_NAV_ZOOM_SECTOR_MAP_T);

    for (ui2_i = 0; ui2_i < ui2_total_num; ++ui2_i)
    {
        if (ui2_id == at_zoom_sector_mapping_id_table[ui2_i].ui2_id)
        {
            return at_zoom_sector_mapping_id_table[ui2_i].t_include_items;
        }
    }

    return NAV_ZOOM_APP_EMPTY;
}

ZOOM_SECTOR_ITEM nav_zoom_cust_get_current_sector_item(VOID)
{
    return e_current_sector;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
VOID a_nav_zoom_cust_select_top_sector (VOID)
{
    nav_request_context_switch(_nav_zoom_cust_select_top_sector_handler, NULL, NULL, NULL);
}

INT32 a_nav_zoom_cust_select_sector (UINT8 ui1_sector, BOOL b_need_store)
{
    INT32                       i4_ret = 0;

    if (ui1_sector < ZOOM_SECTOR_ITEM_1 || ui1_sector > ZOOM_SECTOR_ITEM_9)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "invalid param.\n\r");
        return NAVR_INV_ARG;
    }

    /* start navi sector */
    i4_ret = _nav_zoom_cust_navi_sector((ZOOM_SECTOR_ITEM)ui1_sector);
    if (NAVR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
        return NAVR_FAIL;
    }

    if (b_need_store)
    {
        a_zoom_update_1st_sector_item_in_slist((ZOOM_SECTOR_ITEM)ui1_sector);
    }

    return i4_ret;
}

BOOL a_nav_zoom_cust_get_num_pad_navi_status (VOID)
{
    return t_g_zoom_cust.b_is_num_pad_navi_start;
}
VOID nav_zoom_mode_power_on_send_toast_msg(VOID)
{
    INT32       i4_ret = 0;
    UINT8       ui1_zoom_mode = APP_CFG_CUST_ZOOM_MODE_OFF;
    a_cfg_cust_get_zoom_status(&ui1_zoom_mode);

    if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
    {
       i4_ret = nav_zoom_mode_send_toast_msg(MLM_SETTINGS_KEY_ZOOM_MODE_ON);
       if (NAVR_OK != i4_ret)
       {
          KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
          return;
       }
    }

}
static BOOL _nav_zoom_cust_zoom_osd1(VOID)//For netflix and youtube need zoom in osd1
{
    return (msg_convert_custom_netflix_active()||msg_convert_custom_cobalt_alive());
}

BOOL a_nav_zoom_first_power_on()
{
    return b_is_zoom_on_from_power_on;
}

static INT32 _nav_zoom_cust_power_msg_hdlr(UINT8 ui1_zoom_mode)
{
    INT32                       i4_ret;
    _NAV_ZOOM_CUST_T*           pt_this = &t_g_zoom_cust;
    BOOL                        b_is_start = FALSE;
    ZOOM_SECTOR_ITEM            e_sector_item = ZOOM_SECTOR_INVALID_ITEM;
    UINT16                      ui2_msg_mlm_idx    = 0;

    KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "zoom_mode: %s.\n\r", ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON ? "ON" : "OFF");

    b_is_start = (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON) ? TRUE : FALSE;

    b_is_enabled = b_is_start;

    if (ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        /*vizio hide logo*/
        a_cfg_custom_draw_logo_image(BOOTLOGO_HIDE);
        a_cfg_custom_draw_logo_image(BOOTLOGO_DEINIT);

        i4_ret = nav_zoom_mode_enable();
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_nav zoom_mode_enable failed.\n\r");
            return NAVR_FAIL;
        }

        /* send zoom mode state to EAM when zoom mode change */
        a_tv_net_send_cmd("\n:dtv_app_mtk,am,:zoom_mode_enable\n");

        _nav_zoom_cust_set_num_pad_navi_enable(b_is_start);

        /* re-start region check timer */
        i4_ret = c_timer_stop(pt_this->h_timer_region_check);
        if (OSR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
        }
        i4_ret = c_timer_start(pt_this->h_timer_region_check,
                        500,
                        X_TIMER_FLAG_REPEAT,
                        _nav_zoom_cust_timer_region_check_cb_fct,
                        NULL);
        if (OSR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer start failed.\n\r");
        }

        i4_ret = _nav_zoom_cust_navi_sector(ZOOM_SECTOR_ITEM_2);
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust navi_sector failed.\n\r");
            return NAVR_INV_ARG;
        }

        /* show zoom mode enable msg */
#if NAV_ZOOM_NAVIGATION_ENABLE
        if (a_cfg_cust_zoom_digit_selection_support())
        {
            ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NAV_MODE_ON;
        }
        else
        {
            ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NAV_MODE_NO_NUMBER_PAD_ON;

        }
#else
        ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_MODE_ON;
#endif

#if NAV_ZOOM_ON_TITLE_ADD_IMG
			UTF16_T w2s_str[512] = {0};
			c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), ui2_msg_mlm_idx));
			i4_ret = nav_zoom_mode_show_img_title(w2s_str);
#else
	        i4_ret = nav_zoom_mode_send_toast_msg(ui2_msg_mlm_idx);
#endif
        if (NAVR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_mode msg_show MLM_SETTINGS_KEY_ZOOM_MODE_ON failed.\n\r");
        }
        /*when zoom mode is on, TV delay 3500 for banner*/
        a_banner_view_set_delay_show_banner(TRUE,3500);

    }

    return NAVR_OK;
}
static VOID _nav_zoom_cust_cb_fct (VOID* pv_tag1,VOID* pv_tag2,VOID* pv_tag3)
{
    _nav_zoom_cust_power_msg_hdlr(APP_CFG_CUST_ZOOM_MODE_ON); //zoom mode is on
}
static VOID _nav_zoom_cust_timer_wait_cb_fct (HANDLE_T  pt_tm_handle,VOID* pv_tag)
{
    nav_request_context_switch(_nav_zoom_cust_cb_fct, NULL, NULL, NULL);
}

static INT32 _nav_zoom_cust_enable_wait_timer(VOID)
{
    INT32 i4_ret = 0;

    if(h_handle_msg_wait_timer == NULL_HANDLE)
    {
       i4_ret = c_timer_create(&h_handle_msg_wait_timer);
       if (OSR_OK != i4_ret)
       {
           KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
       }
    }
   /* re-start region check timer */
    i4_ret = c_timer_stop(h_handle_msg_wait_timer);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
    }
    i4_ret = c_timer_start(h_handle_msg_wait_timer,
                    300,
                    X_TIMER_FLAG_ONCE,
                    _nav_zoom_cust_timer_wait_cb_fct,
                    NULL);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer start failed.\n\r");
    }

    return NAVR_OK;

}
static INT32 _nav_zoom_cust_disable_wait_timer(VOID)
{
    /* free resoruce */
    if (c_handle_valid(h_handle_msg_wait_timer) == TRUE)
    {
        c_timer_delete(h_handle_msg_wait_timer);
        h_handle_msg_wait_timer = NULL_HANDLE;
    }
    return NAVR_OK;
}
/*enable/disable zoom mode*/
static BOOL _nav_zoom_cust_get_nav_zoom_status(VOID)
{
    return b_is_dir_nav_pad;
}
BOOL a_nav_zoom_cust_get_nav_zoom_status(VOID)
{
    BOOL b_pad_status = _nav_zoom_cust_get_nav_zoom_status();
    //DBG_LOG_PRINT(("[dash +++] {%s %s() %d}. b_pad_status = %d\n",__FILE__, __FUNCTION__, __LINE__,b_pad_status));
    return b_pad_status;
}

static BOOL _nav_zoom_cust_set_nav_zoom_status(BOOL b_nav)
{
    UINT32  i4_ret          = NAVR_OK;
    UINT16  ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NAV_MENU_OFF;
#if NAV_ZOOM_NAVIGATION_ENABLE
    /*show msg:Zoom mode navigation mode as dis/enabled.*/
    if(b_nav == TRUE)
    {
        ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NAV_MENU_ON;
    }
    else if(b_nav == FALSE)
    {
        ui2_msg_mlm_idx = MLM_SETTINGS_KEY_ZOOM_NAV_MENU_OFF;
    }

    i4_ret = nav_zoom_mode_send_toast_msg(ui2_msg_mlm_idx);
    if (NAVR_OK != i4_ret)
    {
      KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "_nav_zoom_cust_set_nav_zoom_status failed.\n\r");
      return NAVR_NO_ACTION;
    }
#endif
    b_is_dir_nav_pad = b_nav;
    return b_is_dir_nav_pad;
}

static UINT32 _nav_zoom_cust_menu_num_pad(UINT32 ui4_evt_code)
{
    UINT32 ui4_ret_code = ui4_evt_code;
#if NAV_ZOOM_NAVIGATION_ENABLE
    ZOOM_SECTOR_ITEM e_sector = nav_zoom_cust_get_current_sector_item();
    DBG_LOG_PRINT(("[RC +++] {%s %s() %d}. the top e_sector: %d\n",__FILE__, __FUNCTION__, __LINE__,e_sector));
    switch(ui4_evt_code)
    {
        case BTN_CURSOR_LEFT:
            if( e_sector == ZOOM_SECTOR_ITEM_1 ||
                e_sector == ZOOM_SECTOR_ITEM_4 ||
                e_sector == ZOOM_SECTOR_ITEM_7  )
            {
                e_sector += 2;
            }
            else
            {
                e_sector -= 1;
            }
            break;
        case BTN_CURSOR_RIGHT:
            if( e_sector == ZOOM_SECTOR_ITEM_3 ||
                e_sector == ZOOM_SECTOR_ITEM_6 ||
                e_sector == ZOOM_SECTOR_ITEM_9  )
            {
                e_sector -= 2;
            }
            else
            {
                e_sector += 1;
            }
            break;
        case BTN_CURSOR_UP:
            if( e_sector == ZOOM_SECTOR_ITEM_1 ||
                e_sector == ZOOM_SECTOR_ITEM_2 ||
                e_sector == ZOOM_SECTOR_ITEM_3  )
            {
                e_sector += 6;
            }
            else
            {
                e_sector -= 3;
            }
            break;
        case BTN_CURSOR_DOWN:
            if( e_sector == ZOOM_SECTOR_ITEM_7 ||
                e_sector == ZOOM_SECTOR_ITEM_8 ||
                e_sector == ZOOM_SECTOR_ITEM_9  )
            {
                e_sector -= 6;
            }
            else
            {
                e_sector += 3;
            }
            break;
        case BTN_SELECT:
            {
                e_sector = ZOOM_SECTOR_ITEM_5;
            }
            break;
        default: /*no action*/
            DBG_LOG_PRINT(("[RC +++] {%s %s() %d}. the top key: %d,ui4_ret_code = 0x%x\n",__FILE__, __FUNCTION__, __LINE__,e_sector,ui4_ret_code));
            return ui4_ret_code;
    }

    ui4_ret_code = e_sector -ZOOM_SECTOR_ITEM_1 + BTN_GFX_ZOOM_SECTOR_1;
    DBG_LOG_PRINT(("[RC +++] {%s %s() %d}. the top key: %d,ui4_ret_code = 0x%x\n",__FILE__, __FUNCTION__, __LINE__,e_sector,ui4_ret_code));
#endif
   return ui4_ret_code;
}

UINT32 a_nav_zoom_cust_navigation_num_pad(UINT32 ui4_evt_code)
{
    return _nav_zoom_cust_menu_num_pad(ui4_evt_code);
}
VOID a_nav_zoom_cust_long_press_menu(BOOL b_zoom_mode)
{

     UINT8   ui1_zoom_mode  = APP_CFG_CUST_ZOOM_MODE_OFF;
     UINT32  i4_ret         = NAVR_OK;
     BOOL    b_pad_zoom     = _nav_zoom_cust_get_nav_zoom_status();
     i4_ret = a_cfg_cust_get_zoom_status(&ui1_zoom_mode);
     if (NAVR_OK != i4_ret)
     {
         KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "a_nav_zoom_cust_long_press_menu failed.\n\r");
     }

     a_zoom_add_field_into_slist_head(ZOOM_MAKE_ID(ZOOM_APP_GRPID_NAV,NAV_COMP_ID_REVOLT_INFO), ZOOM_SECTOR_ITEM_2);

#if NAV_ZOOM_NAVIGATION_ENABLE
     /*when zoom mode is on,long press menu key to en/disable navigtaion zoom mode*/
     if( ui1_zoom_mode == APP_CFG_CUST_ZOOM_MODE_ON)
     {
        /*long press menu to dis/enable zoom navigation mode*/
        if(b_zoom_mode == TRUE )
         {
           _nav_zoom_cust_set_nav_zoom_status(!b_pad_zoom);
         }
         /*short press menu to disable zoom navigation mode*/
         else if(b_zoom_mode == FALSE)
         {
            _nav_zoom_cust_set_nav_zoom_status(FALSE);
         }

     }
#endif
     DBG_LOG_PRINT(("[RC +++] {%s %s() %d}. ui1_zoom_mode = %d,set@@@:%d\n",__FILE__, __FUNCTION__, __LINE__,ui1_zoom_mode,!b_pad_zoom));
}
static VOID _nav_zoom_cust_timer_dash_wait_cb_fct (HANDLE_T  pt_tm_handle,VOID* pv_tag)
{
    DBG_INFO(("[dash +++] {%s %s() %d}.  4000 ms \n",__FILE__, __FUNCTION__, __LINE__));

    /*disable timer */
    _nav_zoom_cust_disable_dash_timer();

    return;
}
/*record zoom mode pad or digital pad.
function:
        _nav_zoom_cust_dash_get_digital_pad_status
        _nav_zoom_cust_dash_set_digital_pad_status
result:
    0:zoom pad,1:digital pad.
*/
static BOOL _nav_zoom_cust_dash_get_digital_pad_status(VOID)
{
    BOOL b_status = TRUE;

    if (a_cfg_cust_zoom_digit_selection_support()
         && b_is_dash_digital_pad == FALSE) //zoom pad
    {
        b_status = FALSE;
    }

    return b_status;
}
BOOL a_nav_zoom_cust_get_digital_pad_status(VOID)
{
    BOOL b_pad_status = _nav_zoom_cust_dash_get_digital_pad_status();
    DBG_INFO(("[dash +++] {%s %s() %d}. digital_pad = %d\n",__FILE__, __FUNCTION__, __LINE__,b_pad_status));
    return b_pad_status;
}

static BOOL _nav_zoom_cust_dash_set_digital_pad_status(BOOL b_dash)
{
    b_is_dash_digital_pad = b_dash;
    return b_is_dash_digital_pad;
}

VOID a_nav_zoom_cust_set_digital_pad_status(BOOL b_digit_pad)
{
    DBG_INFO(("[dash +++] {%s %s() %d}. Set digital pad status= %d\n",__FILE__, __FUNCTION__, __LINE__,b_digit_pad));

    _nav_zoom_cust_dash_set_digital_pad_status(b_digit_pad);

    return;
}


/*DTV02194182:
[Step 4]Press RC number pad to change channel(ex:14-2)
Press RC Dash key can change channel when DUT in zoom mode(number pad in Digital mode)
solution:
        found a timer to wait about 3s,(ex:14-2).
function:
        _nav_zoom_cust_dash_get_digital_pad_timer
        _nav_zoom_cust_dash_set_digital_pad_timer

        _nav_zoom_cust_enable_dash_timer
        _nav_zoom_cust_disable_dash_timer

*/
static BOOL _nav_zoom_cust_dash_get_digital_pad_timer(VOID)
{
    return b_is_dash_digital_pad_timer_status;
}
/*timer cb_fct,call this to disable*/
static BOOL _nav_zoom_cust_dash_set_digital_pad_timer(BOOL b_dash)
{
    b_is_dash_digital_pad_timer_status = b_dash;
    return b_is_dash_digital_pad_timer_status;
}

#if 0
static BOOL _nav_zoom_cust_dash_digital_pad_status(UINT32 ui4_evt_code,IOM_NFY_COND_T  e_nfy_cond,BOOL b_is_start )
{

    UINT32   ui4_key_code       = IOM_GET_EVT_GRP_ID (ui4_evt_code);
    UINT16   ui2_msg_mlm_idx    = 0 ;
    UINT32   i4_ret = NAVR_OK;
    if ((BTN_GFX_ZOOM_NAVIGATION == ui4_key_code)&&(!nav_is_channel_scan_active()))
       {
            if (IOM_NFY_COND_BTN_DOWN == e_nfy_cond)
            {
                KK_LOG(KK_LOG_LVL_NORMAL, "[ZOOM]", "BTN_GFX_ZOOM_NAVIGATION BTN_DOWN.\n\r");

                //b_is_start = !b_is_start;

                /*show the text msg when num pad switch between zoom mode and digit mode.*/
                if (b_is_start)
                {
                    ui2_msg_mlm_idx = MLM_SETTINGS_KEY_NUM_PAD_IN_ZOOM;
                    _nav_zoom_cust_dash_set_digital_pad_status(FALSE);
                }
                else
                {
                    ui2_msg_mlm_idx = MLM_SETTINGS_KEY_NUM_PAD_IN_DIGIT;
                    _nav_zoom_cust_dash_set_digital_pad_status(TRUE);
                }


                i4_ret = nav_zoom_mode_send_toast_msg(ui2_msg_mlm_idx);
                if (NAVR_OK != i4_ret)
                {
                    KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "nav_zoom_mode msg_show failed.\n\r");
                }

                _nav_zoom_cust_set_num_pad_navi_enable(b_is_start);

            }

        }

    return i4_ret;

}
#endif
static INT32 _nav_zoom_cust_enable_dash_timer(VOID)
{
    INT32 i4_ret = 0;
    DBG_INFO(("[dash +++] {%s %s() %d}. enter.\n",__FILE__, __FUNCTION__, __LINE__));
    if (NULL_HANDLE == h_handle_msg_dash_wait_timer)
    {
        i4_ret = c_timer_create(&h_handle_msg_dash_wait_timer);
        if (OSR_OK != i4_ret)
        {
            KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
            return OSR_INV_ARG;
        }
    }

    /* re-start region check timer */
    i4_ret = c_timer_stop(h_handle_msg_dash_wait_timer);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer stop failed.\n\r");
    }

    i4_ret = c_timer_start(h_handle_msg_dash_wait_timer,
                    3000,
                    X_TIMER_FLAG_ONCE,
                    _nav_zoom_cust_timer_dash_wait_cb_fct,
                    NULL);
    if (OSR_OK != i4_ret)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[ZOOM]", "timer start failed.\n\r");
    }

    /*digital_pad_timer*/
    _nav_zoom_cust_dash_set_digital_pad_timer(TRUE);

    return NAVR_OK;
}
BOOL a_nav_zoom_cust_get_digital_timer_status(VOID)
{
    return _nav_zoom_cust_dash_get_digital_pad_timer();
}
INT32 a_nav_zoom_cust_enable_dash_timer(VOID)
{
    return _nav_zoom_cust_enable_dash_timer();
}
static INT32 _nav_zoom_cust_disable_dash_timer(VOID)
{
    /* free resoruce */
    if (c_handle_valid(h_handle_msg_dash_wait_timer) == TRUE)
    {
        c_timer_delete(h_handle_msg_dash_wait_timer);
        h_handle_msg_dash_wait_timer = NULL_HANDLE;
    }

     /*disable timer */
    _nav_zoom_cust_dash_set_digital_pad_timer(FALSE);

    DBG_INFO(("[dash +++] {%s %s() %d}. \n",__FILE__, __FUNCTION__, __LINE__));

    return NAVR_OK;
}

#endif /*APP_ZOOM_MODE_SUPPORT*/


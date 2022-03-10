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
 * $RCSfile: input_src_list.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT
#ifdef APP_NAV_IPTS_LST

#include "u_common.h"
#include "u_wgl_common.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_handle.h"
#include "c_os.h"
#include "c_dbg.h"
#include "u_cecm.h"

#ifdef APP_TTS_SUPPORT
#include "u_tts.h"
#include "c_tts.h"
#endif

#include "app_util/a_common.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_cec.h"
#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "wdk/a_cnt_indctr.h"
#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "nav/banner2/a_banner.h"
#include "nav/input_src/input_src_list.h"
#include "nav/input_src/input_src_view.h"
#include "nav/input_src/input_src.h"
#include "res/nav/input_src/input_src_list_rc.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_variant_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "wfd/wfd.h"
#include "menu2/menu_common/menu_common.h"

#ifdef APP_CEC_MENU
#include "app_util/a_cec.h"
#include "nav/cec2/a_nav_cec.h"
#include "nav/cec2/nav_cec.h"
#endif

#if defined(APP_COLOR_MODE_PALLET)
    #if !defined(APP_OSD_640x360)
        #include "res/nav/input_src/input_src_list_img_p.i"
    #else
        #error Not implement
    #endif
#else /* 444 mode */
    #include "res/nav/input_src/input_src_list_img.i"
#endif

#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/retail_mode/nav_retail_mode.h"
#endif

#include "res/nav/nav_img_rc.h"
#include "nav/banner2/banner.h"
#include "res/nav/banner2/banner_rc.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/app_util/cec/cec_custom.h"
#include "nav/cc_info/cc_info.h"
#include "nav/viewport/a_nav_viewport.h"

#include "mmp/a_mmp.h"
#include "mmp/app/mmp_main.h"
#include "menu2/a_menu.h"

#include "rest/a_rest_event.h"
#include "rest/a_rest_api.h"
#include "res/nav/one_channel_list/ocl.h"
#include "rest/tv/tv_settings/a_picture_ex.h"

#include "wdk/widget/wdk_widget.h"
#include "nav/long_press/long_press.h"
#include "res/nav/nav_dbg.h"
#include "res/menu2/menu_custom.h"

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define NAV_INPUT_SRC_UI_HAS_DEV_ICON   0


#if 0
#undef  DBG_ERROR
#if 0
    #define DBG_ERROR(_stmt)    c_dbg_stmt _stmt
#else
    #define DBG_ERROR(_stmt)    DBG_LOG_PRINT(_stmt)
#endif

#else

#ifdef NAV_CHK_FAIL
#undef NAV_CHK_FAIL
#endif
#ifdef NAV_LOG_ON_FAIL
#undef NAV_LOG_ON_FAIL
#endif
#ifdef NAV_BREAK_ON_FAIL
#undef NAV_BREAK_ON_FAIL
#endif

#define NAV_CHK_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<NAV>[INPUT_SRC]{%s,%d} Error: Return fail: rtn:%d \n", __FILE__, __LINE__, _ret)); \
    return NAVR_FAIL;  \
}   \
}while(FALSE)

#define NAV_LOG_ON_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<NAV>[INPUT_SRC]{%s,%d} Error: Return fail: rtn:%d \n", __FILE__, __LINE__, _ret)); \
}   \
}while(FALSE)

#define NAV_BREAK_ON_FAIL(_ret)  \
if (_ret < 0)   \
{   \
    DBG_LOG_PRINT(("<NAV>[INPUT_SRC]{%s,%d} Error: Return fail: rtn:%d \n", __FILE__, __LINE__, _ret)); \
    break;  \
}
#endif

//==================================================================================

#define _NAV_IPTS_LST_ACT_IF_UI_NOT_INIT(_pt_this, _stmt)               \
{                                                                       \
    if(!(_pt_this)->b_ui_init)                                          \
    {                                                                   \
        NAV_ASSERT(0);                                                  \
        _stmt;                                                          \
    }                                                                   \
}

#define _NAV_IPTS_LIST_IS_SYNC_REPAINT      (TRUE)
#define _NAV_IPTS_LIST_STOP_TIMER           (TRUE)
#define _NAV_IPTS_LIST_RESET_TIMER          (FALSE)

#ifdef APP_CEC_MENU
#define _NAV_IPTS_LIST_FAKE_DEV_ID          (0xFF)
#define _NAV_IPTS_LIST_FAKE_DEV_NUM         (5)
#else
#define _NAV_IPTS_LIST_FAKE_DEV_ID          (0xFF)
#define _NAV_IPTS_LIST_FAKE_DEV_NUM         (0)
#endif

#define _NAV_INTS_LIST_DLG_TIMER            (5000)
#define ISL_VTRL_INPUT_SRC_ID_BASE                  ((UINT8)  200)

//----------------------------------------------------------------------------
#if(NAV_INPUT_SRC_UI_VERTICAL)
    #define NAV_INPUT_SRC_UI_USE_WDK    0
#else
    #define NAV_INPUT_SRC_UI_USE_WDK    1
#endif

//----------------------------------------------------------------------------

#if(NAV_INPUT_SRC_UI_VERTICAL)
    #define NAV_INPUT_SRC_UI_HAS_TITLE      1
    #define NAV_INPUT_SRC_UI_HAS_ALIAS      0
    #define NAV_INPUT_SRC_UI_VIZIO_STYLE    1
    #define NAV_INPUT_SRC_UI_HAS_TV_CH_NUM_NAME_TEXT    0

    #define NAV_INPUT_SRC_UI_LB_BG_COLOR    1
    #define NAV_INPUT_SRC_UI_LB_ELM_BG_IMG  0
    #define NAV_INPUT_SRC_UI_LB_ELM_BG_COLOR 1
#else
    #define NAV_INPUT_SRC_UI_HAS_TITLE      0
    #define NAV_INPUT_SRC_UI_HAS_ALIAS      0
    #define NAV_INPUT_SRC_UI_VIZIO_STYLE    0
    #define NAV_INPUT_SRC_UI_HAS_TV_CH_NUM_NAME_TEXT    0

    #define NAV_INPUT_SRC_UI_LB_BG_COLOR    0
    #define NAV_INPUT_SRC_UI_LB_ELM_BG_IMG  0
    #define NAV_INPUT_SRC_UI_LB_ELM_BG_COLOR 0
#endif


#if(NAV_INPUT_SRC_UI_HAS_ALIAS)
    #define NAV_UI_LISTBOX_COL_NUM          3
    #define NAV_UI_LISTBOX_COL_IDX_ALIAS    2
#else
    #define NAV_UI_LISTBOX_COL_NUM          2
#endif

//=================================================================================

#define PRINT_RECT_PARA(rect) (rect).i4_left, (rect).i4_top, \
    ((rect).i4_right-(rect).i4_left), ((rect).i4_bottom-(rect).i4_top), (rect).i4_right, (rect).i4_bottom

#define NAV_PRINT_COLOR_PARA(stColor) (stColor).a, (stColor).u1.r, (stColor).u2.g, (stColor).u3.b

//=================================================================================

#define NAV_ENABLE_FRAME_BG_COLOR       0

#define NAV_INPUT_SRC_LOAD_SKIN_TEST    0

#define NAV_ENABLE_TEST_FRAME_BG_COLOR  0

#if(NAV_ENABLE_TEST_FRAME_BG_COLOR)
static HANDLE_T s_ipts_debug_h_frame;
#endif

//----------------------------------------------------------------------------------
#if( NAV_INPUT_SRC_LOAD_SKIN_TEST )
static HANDLE_T s_debug_h_listbox;
#endif

#if(NAV_INPUT_SRC_UI_USE_WDK)
static WDK_OSD_TOAST_T      t_g_wdk_view={0} ;
#endif
static UINT8                ui1_last_idx = 0;
ZOOM_SECTOR_ITEM            e_last_sector_item = ZOOM_SECTOR_ITEM_1;

//=================================================================================


typedef enum {
    E_FUNC_ELEMENT_NULL,
    E_FUNC_ELEMENT_POWER_OFF,
    E_FUNC_ELEMENT_NUM,
}E_FUNC_ELEMENT_TYPE;

typedef struct __NAV_IPTS_LST_ELEM_INFO_T
{
    INT16                                   i2_idx;
    UINT8                                   ui1_id;
    BOOL                                    b_is_disabled;
    E_FUNC_ELEMENT_TYPE                     e_func_type;
} _NAV_IPTS_LST_ELEM_INFO_T;

typedef struct __NAV_IPTS_LST_LAZY_INFO_T
{
    HANDLE_T                                h_parent;
    UTF16_T*                                w2s_grp;
    INT32                                   i4_frame_offset_x;
    INT32                                   i4_frame_offset_y;
    APP_COLOR_TYPE_T                        e_color_type;
} _NAV_IPTS_LST_LAZY_INFO_T;

typedef struct __NAV_IPTS_LIST_MEMBER_T
{
    nav_ipts_lst_unknown_key_handler_fct    pf_unknown_key_handler;
    nav_ipts_lst_activate_handler_fct       pf_activate_handler;
    nav_ipts_lst_autoclose_nfy_fct          pf_autoclose_nfy;
    VOID*                                   pv_tag;
    VOID*                                   pv_custom_data;
    NAV_IPTS_LST_STATUS_BAR_TYPE_T          e_bar_type;
    TV_WIN_ID_T                             e_grp;
    TV_MODE_T                               e_tv_mode;
    NAV_IPTS_LST_ACTIVE_KEY_GROUP_T         e_key_grp;

#if(NAV_INPUT_SRC_UI_USE_WDK)
    WDK_OSD_TOAST_T                         *pt_wdk_view;

    /*rc*/
    HANDLE_T                                h_new_list_txt;
    HANDLE_T                                h_new_list_txt_frm;
#endif

    HANDLE_T                                h_frame;
    HANDLE_T                                h_listbox;
    HANDLE_T                                h_indctr;
#if( NAV_IPTS_LST_CLOSE_TIMER_EN )
    HANDLE_T                                h_close_timer;
#endif
#if( NAV_IPTS_LST_SELECT_TIMER_EN)
    HANDLE_T                                h_select_timer;
#endif
    WGL_HIMG_TPL_T                          h_listbox_bk_img;
    WGL_HIMG_TPL_T                          h_listbox_ht_img;
    WGL_HIMG_TPL_T                          h_disable_img;
    WGL_HIMG_TPL_T                          h_disable_ht_img;
    WGL_HIMG_TPL_T                          h_active_img;
    WGL_HIMG_TPL_T                          h_active_ht_img;

    /*lazy init*/
    _NAV_IPTS_LST_LAZY_INFO_T               t_lazy_info;
    BOOL                                    b_ui_init;
#if(NAV_INPUT_SRC_UI_USE_WDK)
    BOOL                                    b_toast_init;
    BOOL                                    b_toast_active;
#endif

    /**/
    BOOL                                    b_show_active;
    BOOL                                    b_show_disabled;
    BOOL                                    b_is_opened;
    BOOL                                    b_ht_disabled;
    BOOL                                    b_activate_next_ht;
    BOOL                                    b_is_select_timer_start;
    BOOL                                    b_wait_for_virtual_src_switch;
    UINT8                                   ui1_grp_src_id;
    UINT8                                   ui1_other_grp_src_id;
    UINT8                                   ui1_max_elems;
    UINT8                                   ui1_fac_trigger_idx;   /* key index in factory mode trigger key list*/
    UINT32                                  ui4_select_timer_ver;
    UINT16                                  ui2_actived_idx;
    UINT8                                   ui1_inp_idx_bef_sel;
    _NAV_IPTS_LST_ELEM_INFO_T               at_elem[1];
} _NAV_IPTS_LIST_MEMBER_T;

#define MAX_IPTS_LST_TOAST_TXT_NUM              (16)

#define IPTS_SRC_TOAST_LIST_TXT_ITEM_X             (124)
#define IPTS_SRC_TOAST_LIST_TXT_ITEM_Y             (526-458)
#define IPTS_SRC_TOAST_LIST_TXT_ITEM_W             (202)
#define IPTS_SRC_TOAST_LIST_TXT_ITEM_H            (28)

#define IPTS_SRC_TOAST_LIST_FRM_X                 (0)
#define IPTS_SRC_TOAST_LIST_FRM_Y                 (458-317)
#define IPTS_SRC_TOAST_LIST_FRM_W                 (1920)
#define IPTS_SRC_TOAST_LIST_FRM_H                 (164)
#define WDK_VIEW_LIST_TXT_W_EX                          (170)

#define IPTS_MAX_HDMI_PORT                      (5)
#define IPTS_MAX_VTRL_PORT                      (5)
#define IPTS_MAX_CEC_PORT                       (16)


#ifdef APP_NAV_IPTS_LST_ENABLE_KEY_REMAP
#define _NAV_IPTS_LST_CHECK_REMAP(_ui4_key_code)                                                    \
{                                                                                                   \
    if(NAV_IPTS_LST_IS_REMAP_KEY((_ui4_key_code)))                                                  \
    {                                                                                               \
        NAV_IPTS_LST_REMAP_KEY((_ui4_key_code), nav_get_key_source());                              \
    }                                                                                               \
}

#else

#define _NAV_IPTS_LST_CHECK_REMAP(_ui4_key_code)                                                    \
{                                                                                                   \
}

#define _NAV_IPTS_LST_IS_SIM_STRING(_str)       \
{\
    c_memset(s_tmp_name, 0, sizeof(s_tmp_name));    \
    c_str_tolower(s_inp_alias_name);                \
    c_strcpy(s_tmp_name, _str);                     \
    c_str_tolower(s_tmp_name);                      \
    \
    if (c_strstr(s_inp_alias_name, s_tmp_name) != NULL) \
    {\
        i4_cmp_result = 0;  \
        break;  \
    }\
}
#endif

/*-----------------------------------------------------------------------------
 * customization
 *---------------------------------------------------------------------------*/
#ifndef NAV_IPTS_GET_LST_LAZY_INIT
    #define NAV_IPTS_GET_LST_LAZY_INIT()                        (TRUE)
#endif

#if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
typedef struct _NAV_IPTS_CEC_DEV_T
{
    UINT16             ui2_dev_index_in_ipts;
    UINT16             ui2_dev_pa;
    CECM_LOG_ADDR_T    e_dev_la;
}NAV_IPTS_CEC_DEV_T;
#endif

typedef struct __NAV_IPTS_LST_CRNT_HT_INFO_T
{
    BOOL    b_enable;
    UINT8    ui1_max_elems;

    UINT16    ui2_ht_full_range_bar_id;
    UINT16    ui2_ht_scroll_range_bar_id;

    ISL_REC_T    t_isl_scroll_range_first;
} _NAV_IPTS_LST_CRNT_HT_INFO_T;

typedef struct _HDMI_SORTING_REC_T
{
    UINT32   at_elem;
    UINT32    ui4_show_count;
} HDMI_SORTING_REC_T;

typedef struct _IPT_LIST_ELEM_NUM
{
    UINT16      ui2_via_num;
    UINT16      ui2_wfd_num;
    UINT16      ui2_isl_num;
    UINT16      ui2_cec_num;
    UINT16      ui2_retail_num;
    UINT16      ui2_func_num; //power down
    UINT16      ui2_total_num;
}IPT_LIST_ELEM_NUM;

typedef struct _IPT_LIST_REC_T
{
    INP_SRC_TYPE_T              e_src_type;
    DEVICE_TYPE_T               e_video_type;
    HANDLE_T                    h_img;
    HANDLE_T                    h_img_hlt;
    WGL_LB_ITEM_IMG_SUIT_T      t_item_img_disable;
    WGL_LB_ITEM_IMG_SUIT_T      t_item_img_normal;

    BOOL b_tv_channel_valid;
    UTF16_T                     w2s_ch_name[64+1];
    UTF16_T                     w2s_ch_no[64+1];

    HANDLE_T                    h_elem_col0_img;
    UTF16_T                     w2s_elem_col1_name[32];
    UTF16_T                     w2s_elem_col2_name[32];
    _NAV_IPTS_LST_ELEM_INFO_T   t_elem;
    UINT16                      ui2_num;
    BOOL                        b_cec_dev;
    BOOL                        b_conn_amp;
} IPT_LIST_REC_T;

typedef enum {
    E_TOAST_MOVE_NONE,
    E_TOAST_MOVE_PREV,
    E_TOAST_MOVE_NEXT
}E_TOAST_MOVE_DIR;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
extern WGL_IMG_T NAV_IPTS_LST_BOX_BK_IMG;
extern WGL_IMG_T NAV_IPTS_LST_BOX_HT_IMG;

#ifdef APP_NAV_IPTS_LST_BAR_DISABLE
extern WGL_IMG_T NAV_IPTS_LST_BAR_DIS_IMG;
extern WGL_IMG_T NAV_IPTS_LST_BAR_DIS_HT_IMG;
#endif

#ifdef APP_NAV_IPTS_LST_BAR_ACTIVE
extern WGL_IMG_T NAV_IPTS_LST_BAR_ACTIVE_IMG;
extern WGL_IMG_T NAV_IPTS_LST_BAR_ACTIVE_HT_IMG;
#endif
BOOL        b_ipts_ls_dialog_show = FALSE;
extern BOOL b_key_front_pannel;

extern UINT32 aui4_fac_trigger_key[4];
static UINT32 m_aui4_fac_trigger_key[4] = {0};

#if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
static UINT16 ui2_original_pa = 0;
static UINT16 ui2_next_pa = 0;
static BOOL   b_is_select_dev_in_lst = FALSE;
static NAV_IPTS_CEC_DEV_T  at_ipts_cec_dev[IPTS_MAX_CEC_PORT];

#endif

static HANDLE_T         h_ipts_ls_info_fram = NULL_HANDLE;
static HANDLE_T         h_ipts_ls_info_text = NULL_HANDLE;
static HANDLE_T         h_info_timer = NULL_HANDLE;
static UINT32           ui4_retail_elem_idx = 0;
//static UINT32           ui4_via_src_cnt = 0;

#if(NAV_INPUT_SRC_UI_HAS_DEV_ICON)
static WGL_HIMG_TPL_T*               h_inp_icon_img;
#endif

static UINT8                        NAV_IPTS_LST_BOX_ELEM_COUNT = 0;
static WGL_HIMG_TPL_T                    h_inp_icon_shadow_img;
#if(NAV_INPUT_SRC_UI_HAS_TV_CH_NUM_NAME_TEXT)
static WGL_HIMG_TPL_T                          h_inp_tv_ch_no_text;
static WGL_HIMG_TPL_T                          h_inp_tv_ch_name_text;
#endif
static _NAV_IPTS_LIST_MEMBER_T*                pt_ipts_list = NULL;
static _NAV_IPTS_LST_CRNT_HT_INFO_T             at_crnt_ht_element;
static IPT_LIST_REC_T                           *pt_ipt_list_rec = NULL;
static IPT_LIST_ELEM_NUM                        t_list_elem_num;
#ifdef APP_IPCC_SUPPORT
static BOOL b_ipcc_show = TRUE;
#endif

static WDK_TOAST_PARAM_T                t_g_toast_param;

#if(NAV_INPUT_SRC_UI_USE_WDK)
/* Care X pos only for letf/right moving */
static INT32                            aui4_g_toast_list_txt_pos[MAX_IPTS_LST_TOAST_TXT_NUM] = {0};
static UINT8                            aui1_g_toast_list_txt_idx[MAX_IPTS_LST_TOAST_TXT_NUM] = {0};
#endif

#ifdef APP_TTS_SUPPORT
static HANDLE_T _h_g_tts = NULL_HANDLE;
static UINT32   _ui4_g_tts_string_id = 0;
static INT32    i4_g_tts_tag = 0;
static TTS_CB_T t_g_tts_cb = {0};
#endif
static IPT_LIST_REC_T                      t_tv_rec_backup;
UINT16 input_source_vcec_pa = 0;
BOOL b_nav_ipts_lst_set_active_flag = FALSE;

static BOOL    b_PowerON_on_isl_flag = FALSE;

#if(NAV_INPUT_SRC_UI_VERTICAL)
static BOOL _s_b_navigate_by_up_down = FALSE;
#endif

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

extern INT32 nav_ipts_ls_info_init(_NAV_IPTS_LIST_MEMBER_T* pt_this);
extern INT32 nav_ipts_lst_info_free(_NAV_IPTS_LIST_MEMBER_T* pt_this);
extern INT32 nav_ipts_ls_info_show(VOID);
extern INT32 nav_ipts_ls_info_hide (VOID);
extern INT32 nav_ipts_lst_tts_play_stop(BOOL b_play, UTF16_T *pw2s_content);
static INT32 _nav_ipts_lst_tts_play_stop_ex(BOOL b_play, UTF16_T *pw2s_content);

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_frame_create(_NAV_IPTS_LIST_MEMBER_T*        pt_this,
                                        HANDLE_T                        h_parent,
                                        INT32                           i4_frame_offset_x,
                                        INT32                           i4_frame_offset_y);

static INT32 _nav_ipts_lst_listbox_create(_NAV_IPTS_LIST_MEMBER_T*      pt_this,
                                          APP_COLOR_TYPE_T              e_color_type);

static INT32 _nav_ipts_lst_listbox_load_skin(_NAV_IPTS_LIST_MEMBER_T*   pt_this,
                                             APP_COLOR_TYPE_T           e_color_type,
                                             INT32                      i4_name_idx,
                                             INT32                      i4_bar_idx);

static INT32 _nav_ipts_lst_image_create(_NAV_IPTS_LIST_MEMBER_T*        pt_this);

static INT32 _nav_ipts_lst_update_elems(_NAV_IPTS_LIST_MEMBER_T*        pt_this,
                                                  TV_WIN_ID_T                     e_grp,
                                                  BOOL                            b_force);

static INT32 _nav_ipts_lst_reset_close_timer(_NAV_IPTS_LIST_MEMBER_T*    pt_this,
                                            BOOL                        b_stop_only);

static VOID _nav_ipts_lst_reset_select_timer(_NAV_IPTS_LIST_MEMBER_T*   pt_this,
                                            BOOL                        b_stop_only);

static VOID _nav_ipts_lst_autoclose_cb(HANDLE_T                         h_timer,
                                       VOID*                            pv_this);

static VOID _nav_ipts_lst_autoclose_msg_hdlr(VOID*                      pv_this,
                                             VOID*                      pv_unused2,
                                             VOID*                      pv_unused3);

/**/
static INT32 _nav_ipts_lst_frame_nfy_fct(HANDLE_T                       h_widget,
                                         UINT32                         ui4_msg,
                                         VOID*                          pv_param1,
                                         VOID*                          pv_param2);

static INT32 _nav_ipts_lst_init_ui(_NAV_IPTS_LIST_MEMBER_T*             pt_this);
static VOID _nav_ipts_lst_deinit_ui(_NAV_IPTS_LIST_MEMBER_T*            pt_this);
static INT32 _nav_ipts_lst_lazy_init(_NAV_IPTS_LIST_MEMBER_T*           pt_this);

static INT32 _nav_ipts_lst_handle_key(_NAV_IPTS_LIST_MEMBER_T*          pt_this,
                                      UINT32                            ui4_keycode,
                                      UINT32                            ui4_key_state);

static INT32 _nav_ipts_enter_factory_menu(_NAV_IPTS_LIST_MEMBER_T*     pt_this);

static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag);
static INT32 _nav_ipts_ls_demo_mode_off(VOID);

static INT32 _nav_ipts_lst_update_elems_ex( _NAV_IPTS_LIST_MEMBER_T*            pt_this,
                                                        TV_WIN_ID_T                         e_grp,
                                                        BOOL                                b_force);

#if(NAV_INPUT_SRC_UI_USE_WDK)
static INT32 _nav_ipts_new_list_txt_hide(_NAV_IPTS_LIST_MEMBER_T* pt_this);
static INT32 _nav_ipts_lst_new_list_txt_active(_NAV_IPTS_LIST_MEMBER_T* pt_this);
static INT32 _nav_ipts_new_list_txt_move(_NAV_IPTS_LIST_MEMBER_T* pt_this, E_TOAST_MOVE_DIR e_move_dir);
#endif

static INT32 _nav_ipts_ch_name_text_preprocess(CHAR *ps_src, CHAR *ps_dst, size_t t_dst_size);

VOID nav_ipts_lst_print_elems(_NAV_IPTS_LIST_MEMBER_T *pt_this);

static INT32 _nav_ipts_lst_update_cec_device_pa(VOID * pv_ipts_lst,UINT8  ui1_idx);
BOOL _nav_ipts_lst_pwrdwn_check_sku_default_enable(VOID);


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

static char g_ipts_ac_tmp_str_buf[256];
char* nav_cust_get_char_string( const UTF16_T* w2s_str )
{
    g_ipts_ac_tmp_str_buf[0] = 0;

    if( w2s_str == NULL )
    {
        c_strncpy(g_ipts_ac_tmp_str_buf, "NULL pointer", 10);
        return g_ipts_ac_tmp_str_buf;
    }


    SIZE_T w2s_str_len = c_uc_w2s_strlen(w2s_str);

    if( w2s_str_len == 0 )
    {
        c_strncpy(g_ipts_ac_tmp_str_buf, "empty", 10);
    }
    else
    {
        c_uc_w2s_to_ps(w2s_str, g_ipts_ac_tmp_str_buf, 255);
        g_ipts_ac_tmp_str_buf[255] = 0;
    }

    return g_ipts_ac_tmp_str_buf;
}

static INT32 ipts_config_icon(HANDLE_T h_icon,
                            WGL_HIMG_TPL_T  h_img,
                            WGL_HIMG_TPL_T  h_img_hlt)
{
    INT32           i4_ret;
    WGL_IMG_INFO_T  t_img_info;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_icon:0x%X\n", __FUNCTION__, __LINE__, h_icon )); );

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_extend.t_enable    = h_img;
    t_img_info.u_img_data.t_extend.t_disable   = h_img;
    t_img_info.u_img_data.t_extend.t_highlight = h_img_hlt;

    i4_ret = c_wgl_do_cmd(h_icon,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_FG),
                 WGL_PACK(&t_img_info));

    i4_ret = c_wgl_do_cmd(h_icon,
                 WGL_CMD_ICON_SET_ALIGN,
                 WGL_PACK(WGL_AS_CENTER_CENTER),
                 NULL);

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_insert(h_icon:0x%X,)\n", __FUNCTION__, __LINE__, h_icon )); );

    i4_ret = c_wgl_insert(h_icon,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 ipts_create_icon(HANDLE_T    h_parent,
                            HANDLE_T*   h_handle,
                            GL_RECT_T*  t_rect,
                            HANDLE_T    h_img,
                            HANDLE_T    h_img_hlt)
{
    INT32   i4_ret;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_parent:0x%X\n",
        __FUNCTION__, __LINE__, h_parent )); );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 t_rect,
                                 NULL,
                                 255,
                                 NULL,
                                 NULL,
                                 h_handle);
    //DBG_INFO(("i4_ret=%d\n", i4_ret));
    if( i4_ret != 0 )
    {
        DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} Error: i4_ret:%d\n",
            __FUNCTION__, __LINE__, i4_ret ));
        return i4_ret;
    }

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_parent(0x%X) create HT_WGL_WIDGET_ICON(0x%X) (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
        __FUNCTION__, __LINE__, h_parent, *h_handle, PRINT_RECT_PARA(*t_rect)  )); );


    return ipts_config_icon(*h_handle, h_img, h_img_hlt);
}

static INT32 ipts_config_text_utf16(HANDLE_T      h_txt,
                            CHAR*       ps_font_type,
                          FE_FNT_SIZE   e_font_size,
                          UTF16_T* pw2s)
{
    INT32  i4_ret;
    WGL_COLOR_INFO_T t_clr_info;
    WGL_INSET_T      t_inset;
    WGL_FONT_INFO_T     t_fnt_info;

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, ps_font_type);
    t_fnt_info.e_font_size  = e_font_size;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd ( h_txt,
                            WGL_CMD_GL_SET_FONT,
                            WGL_PACK(&t_fnt_info),
                            NULL);
    MENU_CHK_FAIL(i4_ret);
    /* Set Text Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)pw2s,
                          (VOID*)c_uc_w2s_strlen (pw2s));
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_txt,
                            WGL_CMD_TEXT_SET_CNT_INSET,
                            &t_inset,
                            NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_insert(h_txt,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_txt,NULL,TRUE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 ipts_create_text_utf16(HANDLE_T      h_parent,
                          HANDLE_T*     ph_handle,
                          GL_RECT_T*    t_rect,
                            CHAR*        ps_font_type,
                          FE_FNT_SIZE   e_font_size,
                          UTF16_T* pw2s)
{
    INT32   i4_ret;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32
                                         | WGL_STL_GL_NO_IMG_UI
                                         | WGL_STL_GL_NO_BK),
                                 0,
                                 ph_handle);
    MENU_CHK_FAIL(i4_ret);

    return ipts_config_text_utf16(*ph_handle, ps_font_type, e_font_size, pw2s);
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_get_alias_icon_handle
 * Description
 *      nav_ipts_get_alias_icon_handle
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

HANDLE_T nav_ipts_get_alias_icon_handle(CHAR *s_inp_alias_name, BOOL b_from)
{
    INT32   i4_cmp_result;
    UINT16  ui2_mlm_idx = 0;
    CHAR    s_tmp_name[32] = {0};

    if (NULL == s_inp_alias_name ||
        c_strlen(s_inp_alias_name) == 0)
    {
        return NULL_HANDLE;
    }

    ui2_mlm_idx = menu_page_naming_is_predef_name(s_inp_alias_name);
    if (ui2_mlm_idx != 0xFFFF)
    {
        c_uc_w2s_to_ps(MLM_MENU_TEXT(0, ui2_mlm_idx), s_inp_alias_name, APP_CFG_CUSTOM_INP_NAME_LEN);
    }

    do//BluRay
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Blu-ray");//For Naming
        if(0 == i4_cmp_result)
            break;

        _NAV_IPTS_LST_IS_SIM_STRING("Blu-ray")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_blueray_lt_img;
        else
            return h_g_nav_banner_new_input_new_dvd_blueray_pic;
    }

    do//Cable Box
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Cable Box");//For Naming
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("Cable Box")

        i4_cmp_result = c_strcmp(s_inp_alias_name, "TV");//For Device setting
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("TV")

        i4_cmp_result = c_strcmp(s_inp_alias_name, "Cable, IPTV");//For Device setting
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("Cable, IPTV")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_cable_lt_img;
        else
                return h_g_nav_banner_new_input_new_box_pic;
    }

    do//PC
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Computer");//For Naming
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("Computer")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_computer_lt_img;
        else
            return h_g_nav_banner_new_input_new_computer_pic;
    }

    do//DVR
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "DVR");//For Naming
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("DVR")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_dvr_lt_img;
        else
            return h_g_nav_banner_new_input_new_dvr_pic;
    }

    do//DVD
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "DVD player");//For Naming
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("DVD player")

        i4_cmp_result = c_strcmp(s_inp_alias_name, "DVD");//For Device setting
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("DVD")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_dvd_lt_img;
        else
            return h_g_nav_banner_new_input_new_dvd_pic;
    }

    do//Game
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Game");//For Naming
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("Game")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_game_lt_img;
        else
            return h_g_nav_banner_new_input_new_game_pic;
    }

    do//Satellite
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Satellite");//For Naming
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("Satellite")

        i4_cmp_result = c_strcmp(s_inp_alias_name, "Satellite/DSS");//For Device setting
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("Satellite/DSS")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_satellite_lt_img;
        else
            return h_g_nav_banner_new_input_new_satellite_pic;
    }

    do //VCR
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "VCR");//For Naming and Device setting
        if(0 == i4_cmp_result)
            break;
        _NAV_IPTS_LST_IS_SIM_STRING("VCR")
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return h_g_nav_banner_new_input_vcr_lt_img;
        else
            return h_g_nav_banner_new_input_new_dvr_pic;
    }
    //====================================================No picture have
    do //VCR
    {
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Receiver, Misc Audio");//For Device setting
        if(0 == i4_cmp_result)
            break;
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Amplifier");//For Device setting
        if(0 == i4_cmp_result)
            break;
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Video Accessory");//For Device setting
        if(0 == i4_cmp_result)
            break;
        i4_cmp_result = c_strcmp(s_inp_alias_name, "Xbox");//For Device setting
        if(0 == i4_cmp_result)
            break;
    }while(0);
    if(0 == i4_cmp_result)
    {
        if(b_from)
            return NULL_HANDLE;
        else
            return NULL_HANDLE;
    }

    return NULL_HANDLE;
}

HANDLE_T    nav_ipts_get_alias_icon(UINT8 ui1_input_id,BOOL    b_from)
{
    CHAR    s_inp_alias_name[32] = {0};

    a_cfg_custom_get_device_type(ui1_input_id,s_inp_alias_name);

    return nav_ipts_get_alias_icon_handle(s_inp_alias_name, b_from);
}

#if(NAV_INPUT_SRC_UI_USE_WDK)
INT32 nav_ipts_new_lst_text_create(VOID* pv_ipts_lst)
{
/* Step1 Init toast list text */
    _NAV_IPTS_LIST_MEMBER_T*            pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    HANDLE_T                            h_canvas = NULL_HANDLE;
    UINT32                              ui4_canvas_w = 0;
    UINT32                              ui4_canvas_h = 0;
    GL_RECT_T                           t_rect;
    INT32                               i4_ret;
    UINT8                               ui1_idx = 0;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    ///c_memset(&t_g_toast_param, 0, sizeof(t_g_toast_param));

    if (pt_this->b_toast_init)
    {
        a_wdk_toast_deinit(&t_g_wdk_view);
        //return NAVR_OK;
    }

    DBG_INFO(("%s() %d: =========\r\n",__FUNCTION__,__LINE__));

    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    h_canvas = pt_this->t_lazy_info.h_parent;

    nav_get_ui_canvas_size(&ui4_canvas_w,&ui4_canvas_h);
    DBG_INFO(("%s() %d: ui4_canvas_w=%d, ui4_canvas_h=%d\r\n",__FUNCTION__,__LINE__,ui4_canvas_w,ui4_canvas_h));
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} ui4_canvas_w:%d, ui4_canvas_h:%d \n",
        __FUNCTION__, __LINE__, ui4_canvas_w,ui4_canvas_h)); );

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     ui4_canvas_w,
                     ui4_canvas_h);
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} create_widget(HT_WGL_WIDGET_FRAME, h_new_list_txt_frm :(%d %d %d %d) \n",
        __FUNCTION__, __LINE__, t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );

    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 0,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                                 NULL,
                                 &pt_this->h_new_list_txt_frm);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_create_widget(HT_WGL_WIDGET_FRAME) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    t_g_toast_param.e_toast_style = WDK_INPUT_LIST;
    t_g_toast_param.w2s_msg_t.e_msy_style = WDK_MSG_SEPARATELY;
    t_g_toast_param.ui4_sl_first_num = 0;
    t_g_toast_param.h_t_focus_handle = pt_this->h_listbox;
    t_g_toast_param.pf_send_msg_cb = NULL;

    t_g_toast_param.b_is_pic_mode = FALSE;

    a_wdk_toast_init(pt_this->h_new_list_txt_frm, &t_g_toast_param, &t_g_wdk_view);

    pt_this->pt_wdk_view = &t_g_wdk_view;
    pt_this->b_toast_init = TRUE;

    DBG_INFO(("%s() %d: =========\r\n",__FUNCTION__,__LINE__));

    for(ui1_idx = 0; ui1_idx < t_g_toast_param.w2s_msg_t.i4_str_num; ui1_idx++)
    {
        aui4_g_toast_list_txt_pos[ui1_idx] = IPTS_SRC_TOAST_LIST_TXT_ITEM_X + ui1_idx * WDK_VIEW_LIST_TXT_W_EX;
        aui1_g_toast_list_txt_idx[ui1_idx] = ui1_idx;
    }

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_create(
    const NAV_IPTS_LST_CREATE_INFO_T*   pt_info,
    VOID**                              ppv_ipts_lst)
{
    _NAV_IPTS_LIST_MEMBER_T*            pt_this;
    SIZE_T                              z_size;
    INT32                               i4_ret;
    UINT8                               ui1_num_recs;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_info:0x%X\n",
        __FUNCTION__, __LINE__, (UINT32)pt_info )); );

    if(NULL == pt_info || NULL == ppv_ipts_lst)
    {
        return NAVR_INV_ARG;
    }

    /*get count of input source*/
    i4_ret = a_isl_get_num_rec(&ui1_num_recs);
    if(ISLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s: a_isl_get_num_rec() failed. i4_ret = %d.\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* Add VIA rec */
    ui1_num_recs += _NAV_IPTS_LIST_FAKE_DEV_NUM + 1;

    if (a_cfg_custom_get_wfd_support() == TRUE)
    {
        /* Add Miracast rec */
        ui1_num_recs++;
    }

    NAV_IPTS_LST_BOX_ELEM_COUNT = ui1_num_recs;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} NAV_IPTS_LST_BOX_ELEM_COUNT = ui1_num_recs:%d \n",
        __FUNCTION__, __LINE__, NAV_IPTS_LST_BOX_ELEM_COUNT )); );

#if(NAV_INPUT_SRC_UI_HAS_DEV_ICON)
    h_inp_icon_img = (WGL_HIMG_TPL_T*)c_mem_alloc(ui1_num_recs * sizeof(WGL_HIMG_TPL_T));
    if(NULL == h_inp_icon_img)
    {
        return NAVR_OUT_OF_MEM;
    }
#endif

    /*alloc resource*/
    if(ui1_num_recs > 0)
    {
        z_size = sizeof(_NAV_IPTS_LIST_MEMBER_T) + (ui1_num_recs - 1) * sizeof(_NAV_IPTS_LST_ELEM_INFO_T);
    }
    else
    {
        z_size = sizeof(_NAV_IPTS_LIST_MEMBER_T);
    }

    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)c_mem_alloc(z_size);
    if(NULL == pt_this)
    {
        return NAVR_OUT_OF_MEM;
    }

    //NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_mem_alloc pt_this(%d) => 0x%X \n", __FUNCTION__, __LINE__, z_size, (UINT32)pt_this )); );


    /*init data member*/
    c_memset(pt_this, 0, z_size);

    pt_this->e_grp = TV_WIN_ID_LAST_VALID_ENTRY;
    pt_this->e_tv_mode = TV_MODE_TYPE_NORMAL;
    pt_this->e_key_grp = NAV_IPTS_LST_PRI_KEY_GROUP;
    pt_this->ui1_grp_src_id = 0xFF;
    pt_this->ui1_other_grp_src_id = 0xFF;
    pt_this->pf_unknown_key_handler = pt_info->pf_unknown_key_handler;
    pt_this->pf_activate_handler = pt_info->pf_activate_handler;
    pt_this->pf_autoclose_nfy = pt_info->pf_autoclose_nfy;
    pt_this->pv_tag = pt_info->pv_tag;
    pt_this->e_bar_type = pt_info->e_bar_type;
    pt_this->b_show_active = pt_info->b_show_active;
    pt_this->b_show_disabled = pt_info->b_show_disabled;
    pt_this->b_ht_disabled = pt_info->b_ht_disabled;
    pt_this->b_activate_next_ht = pt_info->b_activate_next_ht;
    pt_this->ui1_max_elems = ui1_num_recs;

    /*info for lazy init*/
    pt_this->t_lazy_info.h_parent = pt_info->h_parent;
    pt_this->t_lazy_info.i4_frame_offset_x = pt_info->i4_frame_offset_x;
    pt_this->t_lazy_info.i4_frame_offset_y = pt_info->i4_frame_offset_y;
    pt_this->t_lazy_info.e_color_type = pt_info->e_color_type;


#if(NAV_INPUT_SRC_UI_VERTICAL)
    // debug...
    if( pt_this->e_bar_type != NAV_IPTS_LST_SBT_RIGHT )
    {
        DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: Invalid e_bar_type:%d, force to NAV_IPTS_LST_SBT_RIGHT\n", __FUNCTION__, __LINE__, pt_this->e_bar_type ));
        pt_this->e_bar_type = NAV_IPTS_LST_SBT_RIGHT;
    }
#endif


    /*init UI*/
    if(FALSE == NAV_IPTS_GET_LST_LAZY_INIT())
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_init_ui() \n",
            __FUNCTION__, __LINE__ )); );
        i4_ret = _nav_ipts_lst_init_ui(pt_this);
        if(NAVR_OK != i4_ret)
        {
            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_free() \n",
                __FUNCTION__, __LINE__ )); );

            nav_ipts_lst_free(pt_this);
        }
        else
        {
            *ppv_ipts_lst = pt_this;
        }
        DBG_INFO(("<INP LIST> file: %s line: %d  %s If it show twice, it's wrong\n", __FILE__, __LINE__, __FUNCTION__));
        nav_ipts_ls_info_init(pt_this);
    }
    else
    {
        *ppv_ipts_lst = pt_this;
        i4_ret = NAVR_OK;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_free
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
VOID nav_ipts_lst_free(
    VOID*              pv_ipts_lst)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this;
    SIZE_T                      z_size;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pv_ipts_lst:0x%X \n",
        __FUNCTION__, __LINE__, (UINT32)pv_ipts_lst )); );

    if(NULL == pv_ipts_lst)
    {
        return;
    }

    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;

    /*free UI*/
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_deinit_ui() \n",
        __FUNCTION__, __LINE__ )); );
    _nav_ipts_lst_deinit_ui(pt_this);

    nav_ipts_lst_info_free(pt_this);

    /*list title*/
    if(pt_this->t_lazy_info.w2s_grp)
    {
        c_mem_free(pt_this->t_lazy_info.w2s_grp);
        pt_this->t_lazy_info.w2s_grp = NULL;
    }

    /*reset memory before free*/
    z_size = sizeof(_NAV_IPTS_LIST_MEMBER_T);
    z_size += (pt_this->ui1_max_elems >= 1) ? (pt_this->ui1_max_elems - 1) * sizeof(_NAV_IPTS_LST_ELEM_INFO_T) : 0;
    c_memset(pt_this, (UINT8)'N', z_size);

    /*free memory*/
#if(NAV_INPUT_SRC_UI_HAS_DEV_ICON)
    if(NULL != h_inp_icon_img)
    {
        DBG_INFO(("<INP LIST> file: %s line: %d  %s If it show twice, it's wrong\n", __FILE__, __LINE__, __FUNCTION__));
        c_mem_free(h_inp_icon_img);
        h_inp_icon_img = NULL;
    }
#endif

    if (NULL != pt_ipt_list_rec)
    {
        DBG_INFO(("<INP LIST> file: %s line: %d  %s If it show twice, it's wrong\n", __FILE__, __LINE__, __FUNCTION__));
        c_mem_free(pt_ipt_list_rec);
        pt_ipt_list_rec = NULL;
    }

    c_mem_free(pt_this);
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_set_group
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_set_group(
    VOID*                               pv_ipts_lst,
    TV_WIN_ID_T                         e_grp,
    const UTF16_T*                      w2s_grp,
    NAV_IPTS_LST_ACTIVE_KEY_GROUP_T     e_key_grp)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    UINT32                      ui4_len;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pv_ipts_lst:0x%X, e_grp:%d, e_key_grp:%d\n",
        __FUNCTION__, __LINE__, pv_ipts_lst, e_grp, e_key_grp )); );

    if( w2s_grp )
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} w2s_grp:%s\n",
            __FUNCTION__, __LINE__, menu_custom_get_char_string(w2s_grp)  )); );
    }

    if(NULL == pv_ipts_lst || TV_WIN_ID_LAST_VALID_ENTRY == e_grp)
    {
        DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: Invalid para!! \n", __FUNCTION__, __LINE__ ));
        return NAVR_INV_ARG;
    }

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pv_ipts_lst->b_ui_init:%d\n",
        __FUNCTION__, __LINE__, pt_this->b_ui_init )); );

    pt_this->e_key_grp = e_key_grp;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this->t_lazy_info.w2s_grp:0x%X\n",
        __FUNCTION__, __LINE__, (UINT32)pt_this->t_lazy_info.w2s_grp )); );

    /*free title buffer*/
    if(pt_this->t_lazy_info.w2s_grp)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this->t_lazy_info.w2s_grp:0x%X => Free title buffer\n",
            __FUNCTION__, __LINE__, (UINT32)pt_this->t_lazy_info.w2s_grp )); );
        c_mem_free(pt_this->t_lazy_info.w2s_grp);
        pt_this->t_lazy_info.w2s_grp = NULL;
    }

    if(pt_this->b_ui_init)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_update_elems()\n",
            __FUNCTION__, __LINE__ )); );

        return _nav_ipts_lst_update_elems(pt_this, e_grp, FALSE);
    }
    else
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} UI not inited! \n", __FUNCTION__, __LINE__ )); );

        /*allocate necessary buffer*/
        ui4_len = (w2s_grp) ? c_uc_w2s_strlen(w2s_grp) : 0;
        if(ui4_len)
        {
            pt_this->t_lazy_info.w2s_grp = c_mem_alloc((ui4_len + 1) * sizeof(UTF16_T));
            if(NULL == pt_this->t_lazy_info.w2s_grp)
            {
                DBG_ERROR((_ERROR_HEADER"%s(): c_mem_alloc() failed, size = %d.\r\n", __FUNCTION__, (ui4_len + 1) * sizeof(UTF16_T)));
                return NAVR_OUT_OF_MEM;
            }

            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this->t_lazy_info.w2s_grp:0x%X\n",
                __FUNCTION__, __LINE__, (UINT32)pt_this->t_lazy_info.w2s_grp )); );

            /*backup title*/
            c_uc_w2s_strncpy(pt_this->t_lazy_info.w2s_grp, w2s_grp, ui4_len);
            pt_this->t_lazy_info.w2s_grp[ui4_len] = 0;
        }

        /*backup target group*/
        pt_this->e_grp = e_grp;

        return NAVR_OK;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_set_ht
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_set_ht(
    VOID*                 pv_ipts_lst,
    UINT8                 ui1_idx,
    NAV_IPTS_HT_TYPE_T    e_ht_type)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                       i4_ret;
    UINT16                      ui2_visible, ui2_crnt_ht;
    UINT16                      ui2_elem_num;
    UINT16                      ui2_fst_vsb_idx = WGL_LB_NULL_INDEX ;
    UINT16                      ui2_lst_vsb_idx = WGL_LB_NULL_INDEX ;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_idx:%d, e_ht_type:%d\n",
        __FUNCTION__, __LINE__, ui1_idx, e_ht_type )); );

    if(NULL == pt_this)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    if((ui1_idx > pt_this->ui1_max_elems) ||
       (pt_this->at_elem[ui1_idx].i2_idx < 0))
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    /*get first visible index*/
    ui2_visible = 0;
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                          WGL_PACK(&ui2_visible),
                          NULL);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

    /*get highlight*/
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_crnt_ht),
                          NULL);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox: ui2_visible:%d, ui2_crnt_ht:%d\n",
        __FUNCTION__, __LINE__, ui2_visible, ui2_crnt_ht )); );

    at_crnt_ht_element.ui2_ht_full_range_bar_id = ui1_idx;
    //at_crnt_ht_element.ui2_ht_full_range_bar_id = pt_this->at_elem[ui1_idx].i2_idx;

    switch (e_ht_type)
    {
    case NAV_IPTS_HT_TYPE_PREV:
        if (ui2_crnt_ht == 0)
        {
            at_crnt_ht_element.ui2_ht_scroll_range_bar_id= (NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0;
            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                  WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx),
                                  WGL_PACK((NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0));

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM_VISIBLE(%d,%d)\n",
                __FUNCTION__, __LINE__,
                pt_this->at_elem[ui1_idx].i2_idx,
                ((NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0)
                )); );

        }
        else if (ui2_crnt_ht == ui2_visible)
        {
            at_crnt_ht_element.ui2_ht_scroll_range_bar_id = 0;

            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                  WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx),
                                  WGL_PACK(0));

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM_VISIBLE(%d,%d)\n",
                __FUNCTION__, __LINE__, pt_this->at_elem[ui1_idx].i2_idx, 0 )); );

        }
        else
        {
            at_crnt_ht_element.ui2_ht_scroll_range_bar_id = ui2_crnt_ht - ui2_visible - 1;
            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                  WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx),
                                  WGL_PACK((UINT16)ui2_crnt_ht - ui2_visible - 1));

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM_VISIBLE(%d,%d)\n",
                __FUNCTION__, __LINE__, pt_this->at_elem[ui1_idx].i2_idx, (ui2_crnt_ht - ui2_visible - 1) )); );

        }
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} NAV_IPTS_LST_BOX_ELEM_COUNT:%d, ui2_ht_scroll_range_bar_id:%d\n",
            __FUNCTION__, __LINE__, NAV_IPTS_LST_BOX_ELEM_COUNT, at_crnt_ht_element.ui2_ht_scroll_range_bar_id )); );

    #if(NAV_INPUT_SRC_UI_USE_WDK)
        _nav_ipts_new_list_txt_move(pt_this,E_TOAST_MOVE_PREV);
    #endif

#if(NAV_INPUT_SRC_UI_VERTICAL)
#ifdef APP_ZOOM_MODE_SUPPORT
        if (ui1_idx > 4 || (ui1_last_idx == 0))
        {
            a_zoom_mode_select_sector(ZOOM_SECTOR_ITEM_4, TRUE);
            e_last_sector_item = ZOOM_SECTOR_ITEM_4;
        }
        if (ui1_idx <= 1)
        {
            a_zoom_mode_select_sector(ZOOM_SECTOR_ITEM_1, TRUE);
            e_last_sector_item = ZOOM_SECTOR_ITEM_1;
        }
        ui1_last_idx = ui1_idx;
#endif
#endif 
        break;

    case NAV_IPTS_HT_TYPE_NEXT:
        c_wgl_do_cmd (pt_this->h_listbox,
                      WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                      WGL_PACK(&ui2_lst_vsb_idx),
                      NULL) ;

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox: ui2_lst_vsb_idx:%d, ui2_crnt_ht:%d\n",
            __FUNCTION__, __LINE__, ui2_lst_vsb_idx, ui2_crnt_ht )); );

        if (ui2_crnt_ht == ui2_lst_vsb_idx)
        {
            if(0 == pt_this->at_elem[ui1_idx].i2_idx)
                at_crnt_ht_element.ui2_ht_scroll_range_bar_id = 0;
            else
                at_crnt_ht_element.ui2_ht_scroll_range_bar_id = (NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0;

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} NAV_IPTS_LST_BOX_ELEM_COUNT:%d, ui2_ht_scroll_range_bar_id:%d\n",
                __FUNCTION__, __LINE__, NAV_IPTS_LST_BOX_ELEM_COUNT, at_crnt_ht_element.ui2_ht_scroll_range_bar_id )); );

            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                  WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx),
                                  WGL_PACK((NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0));

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM_VISIBLE(%d,%d)\n",
                __FUNCTION__, __LINE__, pt_this->at_elem[ui1_idx].i2_idx, ((NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0) )); );
        }
        else
        {
            at_crnt_ht_element.ui2_ht_scroll_range_bar_id = pt_this->at_elem[ui1_idx].i2_idx - ui2_visible;

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui2_visible:%d, ui2_ht_scroll_range_bar_id:%d\n",
                __FUNCTION__, __LINE__, ui2_visible, at_crnt_ht_element.ui2_ht_scroll_range_bar_id )); );

            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                  WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx),
                                  WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx - ui2_visible));
            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM_VISIBLE(%d,%d)\n",
                __FUNCTION__, __LINE__, pt_this->at_elem[ui1_idx].i2_idx,
                    pt_this->at_elem[ui1_idx].i2_idx - ui2_visible )); );

        }
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

    #if(NAV_INPUT_SRC_UI_USE_WDK)
        _nav_ipts_new_list_txt_move(pt_this,E_TOAST_MOVE_NEXT);
    #endif

#if(NAV_INPUT_SRC_UI_VERTICAL)
#ifdef APP_ZOOM_MODE_SUPPORT
        if (ui1_idx == 0 )
        {
            a_zoom_mode_select_sector(ZOOM_SECTOR_ITEM_1, TRUE);
            e_last_sector_item = ZOOM_SECTOR_ITEM_1;
        }
        else if (ui1_idx > 4 )
        {
            a_zoom_mode_select_sector(ZOOM_SECTOR_ITEM_4, TRUE);
            e_last_sector_item = ZOOM_SECTOR_ITEM_4;
        }

        ui1_last_idx = ui1_idx;
#endif
#endif        
        break;

    default:
        /* first is VIA/WFD not repaint */
        if (0xFF == pt_this->at_elem[0].ui1_id
            && FALSE == pt_this->at_elem[0].b_is_disabled)
        {
            break;
        }

        at_crnt_ht_element.ui2_ht_scroll_range_bar_id = 0;

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui2_ht_scroll_range_bar_id:%d\n",
            __FUNCTION__, __LINE__, at_crnt_ht_element.ui2_ht_scroll_range_bar_id )); );

        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_HLT_ELEM_VISIBLE,
                              WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx),
                              WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx));
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM_VISIBLE(%d,%d)\n",
            __FUNCTION__, __LINE__, pt_this->at_elem[ui1_idx].i2_idx, pt_this->at_elem[ui1_idx].i2_idx )); );


        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_repaint(h_listbox) \n",
            __FUNCTION__, __LINE__ )); );
        i4_ret = c_wgl_repaint(pt_this->h_listbox, NULL, _NAV_IPTS_LIST_IS_SYNC_REPAINT);
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

#if(NAV_INPUT_SRC_UI_VERTICAL)
#ifdef APP_ZOOM_MODE_SUPPORT
        a_zoom_mode_select_sector(e_last_sector_item, TRUE);
#endif
#endif  

        break;
    }

    /*if(ui2_visible > pt_this->at_elem[ui1_idx].i2_idx || (ui2_visible + NAV_IPTS_LST_BOX_ELEM_COUNT) <= pt_this->at_elem[ui1_idx].i2_idx)*/
    if(pt_this->b_is_opened )
    {
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_repaint(h_listbox) \n",
            __FUNCTION__, __LINE__ )); );

        i4_ret = c_wgl_repaint(pt_this->h_listbox, NULL, _NAV_IPTS_LIST_IS_SYNC_REPAINT);
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_GET_ELEM_NUM,
                              WGL_PACK(&ui2_elem_num),
                              NULL);
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox: ui2_elem_num:%d, NAV_IPTS_LST_BOX_ELEM_COUNT:%d \n",
            __FUNCTION__, __LINE__, ui2_elem_num, NAV_IPTS_LST_BOX_ELEM_COUNT )); );

        if (ui2_elem_num >= NAV_IPTS_LST_BOX_ELEM_COUNT)
        {
            c_wgl_do_cmd (pt_this->h_listbox,
                          WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                          WGL_PACK(&ui2_fst_vsb_idx),
                          NULL) ;
            if (0 != ui2_fst_vsb_idx)
            {
                //a_cnt_indctr_show(pt_this->h_indctr, CNT_INDCTR_MASK_UP);
            }
            else
            {
                //a_cnt_indctr_hide(pt_this->h_indctr, CNT_INDCTR_MASK_UP);
            }
            c_wgl_do_cmd (pt_this->h_listbox,
                          WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                          WGL_PACK(&ui2_lst_vsb_idx),
                          NULL) ;

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox: ui2_fst_vsb_idx:%d, ui2_lst_vsb_idx:%d \n",
                __FUNCTION__, __LINE__, ui2_fst_vsb_idx, ui2_lst_vsb_idx )); );

            if ((ui2_elem_num - 1) != ui2_lst_vsb_idx)
            {
                //a_cnt_indctr_show(pt_this->h_indctr, CNT_INDCTR_MASK_DOWN);
            }
            else
            {
                //a_cnt_indctr_hide(pt_this->h_indctr, CNT_INDCTR_MASK_DOWN);
            }
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_get_ht
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_get_ht(
    VOID*                 pv_ipts_lst,
    UINT8*                pui1_idx)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                       i4_ret, i;
    UINT16                      ui2_idx;

    if((NULL == pt_this) || (NULL == pui1_idx))
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    /*check init flag*/
    if(FALSE == pt_this->b_ui_init)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_lazy_init()\n",
            __FUNCTION__, __LINE__ )); );

        i4_ret = _nav_ipts_lst_lazy_init(pt_this);
        if(NAVR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_idx),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get highlight index. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*get idx in input source*/
    for(i = 0; i < pt_this->ui1_max_elems; i++)
    {
        if((UINT16)pt_this->at_elem[i].i2_idx == ui2_idx)
        {
            *pui1_idx = (UINT8)i;
            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox ht: ui2_idx:%d, *pui1_idx:%d \n",
                __FUNCTION__, __LINE__, ui2_idx, *pui1_idx )); );

            return NAVR_OK;
        }
    }

    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_change_to_cast_for_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_change_to_cast_for_hide(UINT8 ui1_source_id)
{
    TV_WIN_ID_T                 e_focus_id;
    INT32                       i4_ret;

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_LOG_ON_FAIL(i4_ret);

    rest_event_notify_current_input("CAST:SMARTCAST");

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, e_focus_id ));
    );

    i4_ret = a_tv_set_input_src_id(e_focus_id, ui1_source_id);
    NAV_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _nav_ipts_lst_update_cec_device_pa(VOID * pv_ipts_lst,UINT8  ui1_idx)
{
#if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_idx:%d\n",
        __FUNCTION__, __LINE__, ui1_idx )); );

    {
        CEC_DEV_LST_T               t_lst;
        UINT8                       ui1_count;
        _NAV_IPTS_LIST_MEMBER_T*    pt_this = pv_ipts_lst;

        c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
        a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

        if (t_lst.ui1_dev_num == 0)
        {
            return NAVR_OK;
        }

        for (ui1_count = 0; ui1_count < IPTS_MAX_CEC_PORT; ui1_count++)
        {
            if ((UINT16)pt_this->at_elem[ui1_idx].i2_idx != at_ipts_cec_dev[ui1_count].ui2_dev_index_in_ipts)
            {
                continue;
            }

            ui2_original_pa = ui2_next_pa;
            ui2_next_pa = at_ipts_cec_dev[ui1_count].ui2_dev_pa;
        }
    }
#endif

    return NAVR_OK;
}

static INT32 _nav_ipts_lst_update_vcec_pa(VOID * pv_ipts_lst,UINT8  ui1_idx, UINT16* ui2_dev_pa)
{
    CEC_DEV_LST_T               t_lst;
    UINT8                       ui1_count;
    //_NAV_IPTS_LIST_MEMBER_T*    pt_this = pv_ipts_lst;

    c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
    a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

    if (t_lst.ui1_dev_num == 0)
    {
        return NAVR_NOT_EXIST;
    }

    for (ui1_count = 0; ui1_count < IPTS_MAX_CEC_PORT; ui1_count++)
    {
        if( (at_ipts_cec_dev[ui1_count].ui2_dev_pa & 0x0FFF)
          &&(ui1_idx == at_ipts_cec_dev[ui1_count].ui2_dev_index_in_ipts)
          )
        {
                *ui2_dev_pa = at_ipts_cec_dev[ui1_count].ui2_dev_pa;
                return NAVR_OK;
        }
    }

    return NAVR_FAIL;
}


static INT32 _nav_ipts_lst_set_current_input_by_rest(_NAV_IPTS_LIST_MEMBER_T*  pv_ipts_lst,
                                                                 ISL_REC_T  *pt_isl_rec)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = pv_ipts_lst;
    INT32                       i4_ret  = NAVR_OK;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if( pt_this == NULL || pt_isl_rec == NULL )
    {
        return NAVR_INV_ARG;
    }

    if (a_nav_ipts_is_cast_source(pt_isl_rec) == TRUE)
    {
        if(pt_isl_rec->ui1_internal_id == 0)    /* smart cast */
        {
            TV_WIN_ID_T  e_focus_id_current = {0};
            ISL_REC_T  t_isl_rec_currnt = {0};

            i4_ret = a_tv_get_focus_win(&e_focus_id_current);
            NAV_CHK_FAIL(i4_ret);

            i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id_current, &t_isl_rec_currnt);
            NAV_CHK_FAIL(i4_ret);

            if (t_isl_rec_currnt.t_avc_info.e_video_type != DEV_VTRL_CAST
                || (t_isl_rec_currnt.t_avc_info.e_video_type == DEV_VTRL_CAST
                    && t_isl_rec_currnt.ui1_internal_id != 0)) {
                rest_event_notify_current_input("CAST:SMARTCAST");
            }
        }
        else    /* other virtual input */
        {
            CHAR    s_inp_name[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};
            CHAR    s_name[APP_CFG_CUSTOM_INP_NAME_LEN + 5] = {0};

            DBG_INFO(("\n[VTRL INPUT] %s,%d,pt_isl_rec->ui1_id %d\n",__FUNCTION__,__LINE__,pt_isl_rec->ui1_id));

            i4_ret = a_cfg_get_vtrl_name(pt_isl_rec->ui1_internal_id - 1, s_inp_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            NAV_CHK_FAIL(i4_ret);

            c_strncat(s_name,"CAST:",5);
            c_strncat(s_name,s_inp_name,sizeof(s_inp_name));
            DBG_INFO(("\n[VTRL INPUT] %s,%d,s_name %s\n",__FUNCTION__,__LINE__,s_name));
            rest_event_notify_current_input(s_name);
        }
    }
    else if(a_nav_ipts_is_usb_source(pt_isl_rec) == TRUE)
    {
        a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_MMP");
        rest_event_notify_current_input("usb");
    }
    else if(a_nav_ipts_is_tv_source(pt_isl_rec) == TRUE)
    {
        rest_event_notify_current_input("tuner");
    }
    else if(a_nav_ipts_is_hdmi_source(pt_isl_rec) == TRUE)
    {
        if(pt_isl_rec->ui1_internal_id == 0) {
            rest_event_notify_current_input("hdmi1");
        } else if(pt_isl_rec->ui1_internal_id == 1) {
            rest_event_notify_current_input("hdmi2");
        } else if(pt_isl_rec->ui1_internal_id == 2) {
            rest_event_notify_current_input("hdmi3");
        } else if(pt_isl_rec->ui1_internal_id == 3) {
            rest_event_notify_current_input("hdmi4");
        }
    }
    else if(a_nav_ipts_is_comp_source(pt_isl_rec) == TRUE)
    {
        rest_event_notify_current_input("comp");
    }
    else
    {
        /* UNKNOW */
        return NAVR_NOT_EXIST;
    }
    return NAVR_OK;
}

INT32 a_nav_ipts_lst_set_current_input_by_rest(VOID*  pv_ipts_lst,
                                                                 ISL_REC_T  *pt_isl_rec)
{
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    return _nav_ipts_lst_set_current_input_by_rest((_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst,pt_isl_rec);
}

INT32 nav_ipts_lst_set_active_immediate(VOID * pv_ipts_lst,UINT8  ui1_idx)
{
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_idx:%d\n", __FUNCTION__, __LINE__, ui1_idx )); );

    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T* ) pv_ipts_lst;
    INT32                       i4_ret  = NAVR_OK;

    if(pt_this == NULL)
    {
        return NAVR_INV_ARG;
    }
    if(pt_this->pf_activate_handler == NULL_HANDLE)
    {
        return NAVR_FAIL;
    }

#if (!NAV_INPUT_SRC_UI_VERTICAL)
    if ((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED
        ||a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP))
        && (ui1_idx == 0))
    {
        return NAVR_DO_NOT_CONTINUE;
    }
#endif

#ifdef APP_RETAIL_MODE_SUPPORT
    {
        ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

        if (b_key_front_pannel && (ACFG_RETAIL_MODE_NORMAL == t_retail_mode))
        {
            if (ui4_retail_elem_idx == ui1_idx)
            {
                _nav_ipts_ls_demo_mode_off();

                a_input_src_do_cmd(NAV_IPTS_CMD_VIEW_VISIBILITY,
                                    (VOID *) TRUE,
                                    (VOID *) 0);
                return NAVR_DO_NOT_CONTINUE;
            }
        }
    }
#endif

#ifdef APP_WFD_SUPPORT
    {
        if (a_cfg_custom_get_wfd_support()==TRUE)
        {
            if ((a_wfd_is_rtsp_play_status() == TRUE) && (ui1_idx == 0))
            {
                return NAVR_DO_NOT_CONTINUE;
            }
        }
    }
#endif

    if(b_PowerON_on_isl_flag)
    {
        if (pt_this->at_elem[ui1_idx].e_func_type == E_FUNC_ELEMENT_POWER_OFF)
        {
            nav_set_power_to_input_status(FALSE);
            b_PowerON_on_isl_flag = FALSE;
            //nav_request_context_switch(nav_long_press_power_nfy_timer,(VOID*) 3000, (VOID*) PRESS_KEYPAD_POWER_2_SEC, NULL);

            ISL_LOG(_ISL_LOG_TYPE_FUNC,("[isl_func] %s(%d) Send Power key event to iom\n", __FUNCTION__, __LINE__));
            c_iom_send_evt(BTN_POWER , 120);
            return NAVR_DO_NOT_CONTINUE;
        }
    }

    a_rest_set_test_patterns_turn_off();

#ifdef APP_CAST_TEST_PATTERN
    /* exit pattern before change source */
    a_menu_exit_test_patterns_by_power();
#endif

    /****************** update isl rec in other module *************************/
    ISL_REC_T  t_isl_rec = {0};
    a_isl_get_rec_by_id(pt_this->at_elem[ui1_idx].ui1_id, &t_isl_rec);

#ifdef APP_CAST_TV_MMP
    {
        mmp_main_set_last_isl_rec(&t_isl_rec);
    }
#endif
    i4_ret = _nav_ipts_lst_set_current_input_by_rest(pt_this,&t_isl_rec);
    NAV_CHK_FAIL(i4_ret);
    /***************************************************************************/

    i4_ret = pt_this->pf_activate_handler(pt_this, pt_this->pv_tag, pt_this->e_grp, pt_this->at_elem[ui1_idx].ui1_id);
    NAV_CHK_FAIL(i4_ret);

    /******************* update isl rec to homekit *****************************/
//    if(INP_SRC_TYPE_VTRL != t_isl_rec.e_src_type)
//    {
        i4_ret = _nav_ipts_lst_set_current_input_by_rest(pt_this,&t_isl_rec);
        NAV_CHK_FAIL(i4_ret);
//    }
    /***************************************************************************/

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_set_active
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_set_active( VOID*                     pv_ipts_lst,
                               UINT8                     ui1_idx,
                               _NAV_IPTS_ACTIVE_TYPE_T   e_type,
                               BOOL                      b_force_select)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                       i4_ret;
    UINT8                       ui1_crnt_idx;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pv_ipts_lst:0x%X, ui1_idx:%d, e_type:%d, b_force_select:%d\n",
        __FUNCTION__, __LINE__, (UINT32)pv_ipts_lst, ui1_idx, e_type, b_force_select )); );

    if(NULL == pt_this)
    {
        return NAVR_INV_ARG;
    }

    /*check init flag*/
    if(FALSE == pt_this->b_ui_init)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_lazy_init()\n",
            __FUNCTION__, __LINE__ )); );

        i4_ret = _nav_ipts_lst_lazy_init(pt_this);
        NAV_CHK_FAIL(i4_ret);
    }

    /* ??? */
    if (!b_force_select)
    {
#if(!NAV_INPUT_SRC_UI_VERTICAL)
        if ((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED
            || a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP)) &&
            (e_type == NAV_IPTS_ACTIVE_TYPE_NO_ACTION))
        {
            ui1_idx = 0;
        }

    #ifdef APP_WFD_SUPPORT
        if (a_cfg_custom_get_wfd_support()==TRUE)
        {
            if ((a_wfd_is_rtsp_play_status() == TRUE) &&
                (e_type == NAV_IPTS_ACTIVE_TYPE_NO_ACTION))
            {
                ui1_idx = 0;
            }
        }
    #endif
#endif

        /*get current active*/
        i4_ret = nav_ipts_lst_get_active(pv_ipts_lst, &ui1_crnt_idx);
        NAV_LOG_ON_FAIL(i4_ret);

        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_idx:%d, ui1_crnt_idx:%d, \n",
            __FUNCTION__, __LINE__, ui1_idx, ui1_crnt_idx )); );

        if(ui1_crnt_idx == ui1_idx)
        {
            /*data not update*/
            return NAVR_OK;
        }
    }

    /* set new active index */
    {
        if((ui1_idx > pt_this->ui1_max_elems) ||
           (TRUE == pt_this->at_elem[ui1_idx].b_is_disabled) ||
           (pt_this->at_elem[ui1_idx].i2_idx < 0))
        {
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}Error: ui1_idx:%d, pt_this->ui1_max_elems:%d, at_elem[].b_is_disabled:%d, at_elem[].i2_idx:%d\n",
                __FUNCTION__, __LINE__, ui1_idx, pt_this->ui1_max_elems,
                pt_this->at_elem[ui1_idx].b_is_disabled, pt_this->at_elem[ui1_idx].i2_idx ));

            return NAVR_INV_ARG;
        }


        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_SEL_ELEM: ui1_idx:%d, pt_this->at_elem[ui1_idx].i2_idx:%d, \n",
            __FUNCTION__, __LINE__, ui1_idx, pt_this->at_elem[ui1_idx].i2_idx )); );

        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_SEL_ELEM,
                              WGL_PACK((UINT16)pt_this->at_elem[ui1_idx].i2_idx),
                              NULL);
        NAV_CHK_FAIL( i4_ret == WGLR_OK ? NAVR_OK : i4_ret );


        /*update highlight*/
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_ht(%d, DEFAULT)\n",
            __FUNCTION__, __LINE__, ui1_idx )); );
        i4_ret = nav_ipts_lst_set_ht(pt_this, ui1_idx, NAV_IPTS_HT_TYPE_DEFAULT);
        NAV_CHK_FAIL(i4_ret);
    }

    i4_ret = _nav_ipts_lst_update_cec_device_pa(pt_this,ui1_idx);
    NAV_LOG_ON_FAIL(i4_ret);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this->ui2_actived_idx:%d, )\n",
        __FUNCTION__, __LINE__, pt_this->ui2_actived_idx )); );

    /*action*/
    if( e_type == NAV_IPTS_ACTIVE_TYPE_NO_ACTION )
    {
        // do nothing
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} NAV_IPTS_ACTIVE_TYPE_NO_ACTION\n",
            __FUNCTION__, __LINE__  )); );
    }
    else if( (e_type == NAV_IPTS_ACTIVE_TYPE_IMMEDIATE)
          //&& (pt_this->ui2_actived_idx != ui1_idx)
           )
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} NAV_IPTS_ACTIVE_TYPE_IMMEDIATE \n", __FUNCTION__, __LINE__  )); );

        if( pt_this->ui2_actived_idx != ui1_idx )
        {
            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this->ui2_actived_idx:%d, ui1_idx:%d\n",
                __FUNCTION__, __LINE__, pt_this->ui2_actived_idx, ui1_idx )); );

            input_source_vcec_pa = 0;
    		b_nav_ipts_lst_set_active_flag = TRUE;
    		DBG_LOG_PRINT(("#### %s(%d) b_nav_ipts_lst_set_active_flag= %d \n", __FILE__, __LINE__ , b_nav_ipts_lst_set_active_flag));
            i4_ret = _nav_ipts_lst_update_vcec_pa(pt_this,ui1_idx, &input_source_vcec_pa);
            NAV_LOG_ON_FAIL(i4_ret);
            DBG_LOG_PRINT(("#### %s(%d) pa= %X ret = %d \n", __FILE__, __LINE__ , input_source_vcec_pa, i4_ret));

            i4_ret = nav_ipts_lst_set_active_immediate(pt_this,ui1_idx);
            NAV_LOG_ON_FAIL(i4_ret);
            if(NAVR_OK == i4_ret)
            {
               /* show banner */
               {
                   UINT8 u1_idx = 0xFF;
                   ISL_REC_T tmp_isl_rec;

                   if(0 == nav_ipts_lst_get_ht(pt_this,&u1_idx) && (0xFF != u1_idx))
                   {
                       if( 0 == a_isl_get_rec_by_id(pt_this->at_elem[u1_idx].ui1_id, &tmp_isl_rec) &&
                          !(INP_SRC_TYPE_VTRL == tmp_isl_rec.e_src_type && DEV_VTRL_MMP == tmp_isl_rec.t_avc_info.e_video_type))
                        {
                            nav_show_banner_input_source_msg_hdlr();
                        }
                        else
                        {
                           /* when current input source is usb,we should not show into banner  */
                           DBG_INFO(("it is USB input source ,we should not show info banner or failed to get rec info by id\n"));
                        }
                   }
                }
            }
        }

    }
    else if (e_type == NAV_IPTS_ACTIVE_TYPE_DELAY) /* nav_ipts_lst_set_active_delay */
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} NAV_IPTS_ACTIVE_TYPE_DELAY\n",
            __FUNCTION__, __LINE__  )); );

    #if(NAV_INPUT_SRC_UI_VERTICAL)
        if( _s_b_navigate_by_up_down )
        {
            NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_select_timer(,stop=%d) \n",
                __FUNCTION__, __LINE__, _NAV_IPTS_LIST_STOP_TIMER )); );
            _nav_ipts_lst_reset_select_timer (pt_this, _NAV_IPTS_LIST_STOP_TIMER);
        }
        else
    #endif
        {
            NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_select_timer(,stop=%d) \n",
                __FUNCTION__, __LINE__, _NAV_IPTS_LIST_RESET_TIMER )); );
            _nav_ipts_lst_reset_select_timer (pt_this, _NAV_IPTS_LIST_RESET_TIMER);
        }
    }
    else
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Unknown!!!!!!!!!!!!!!!\n",
            __FUNCTION__, __LINE__  )); );

        NAV_CHK_FAIL(NAVR_INV_ARG);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_set_active_by_id
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_set_active_by_id(
    VOID*                           pv_ipts_lst,
    UINT8                           ui1_id,
    BOOL                            b_with_action)
{
    _NAV_IPTS_LIST_MEMBER_T*        pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                           i, i4_ret;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pv_ipts_lst:0x%X, ui1_id:%d, b_with_action:%d, \n",
        __FUNCTION__, __LINE__, (UINT32)pv_ipts_lst, ui1_id, b_with_action )); );

    if(NULL == pt_this)
    {
        return NAVR_INV_ARG;
    }

    /*check init flag*/
    if(FALSE == pt_this->b_ui_init)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_lazy_init()\n",
            __FUNCTION__, __LINE__ )); );

        i4_ret = _nav_ipts_lst_lazy_init(pt_this);
        NAV_CHK_FAIL(i4_ret);
    }

    /*get idx in input source*/
    for(i = 0; i < pt_this->ui1_max_elems; i++)
    {
        if(pt_this->at_elem[i].ui1_id == ui1_id)
        {
            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active(%d)\n",
                __FUNCTION__, __LINE__, i )); );

            return nav_ipts_lst_set_active (pv_ipts_lst, i, b_with_action ? NAV_IPTS_ACTIVE_TYPE_IMMEDIATE: NAV_IPTS_ACTIVE_TYPE_NO_ACTION, FALSE);
        }
    }

    return NAVR_INV_ARG;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_get_active
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_get_active(
    VOID*                     pv_ipts_lst,
    UINT8*                    pui1_idx)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                       i4_ret, i;
    UINT16                      ui2_idx;

    if((NULL == pt_this) || (NULL == pui1_idx))
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    /*check init flag*/
    if(FALSE == pt_this->b_ui_init)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_lazy_init()\n",
            __FUNCTION__, __LINE__ )); );

        i4_ret = _nav_ipts_lst_lazy_init(pt_this);
        if(NAVR_OK != i4_ret)
        {
            return i4_ret;
        }
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_GET_SEL_INDEXES,
                          WGL_PACK((UINT16)1),      /* buffer size */
                          WGL_PACK(&ui2_idx));      /* the buffer  */
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to get active index. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*get idx in input source*/
    for(i = 0; i < pt_this->ui1_max_elems; i++)
    {
        if((UINT16)pt_this->at_elem[i].i2_idx == ui2_idx)
        {
            *pui1_idx = (UINT8)i;

            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox: ui2_idx:%d, *pui1_idx:%d\n",
                __FUNCTION__, __LINE__, ui2_idx, *pui1_idx )); );


            return NAVR_OK;
        }
    }

    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_open
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_open(VOID *   pv_ipts_lst)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                       i4_ret;
    UINT16                      ui2_ht;
    //UINT16                      ui2_elem_num;
//    UINT16                      ui2_fst_vsb_idx = WGL_LB_NULL_INDEX ;
//    UINT16                      ui2_lst_vsb_idx = WGL_LB_NULL_INDEX ;
    UINT8                       ui1_status = 0;
    CHAR                        s_app_name[16] = {0};

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pv_ipts_lst:0x%X \n",
        __FUNCTION__, __LINE__, pv_ipts_lst )); );

    if(NULL == pv_ipts_lst)
    {
        return NAVR_INV_ARG;
    }

    pt_ipts_list = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;

    {
        nav_banner_ipts_hide_itm();
        nav_banner_cc_itm_hide();

#ifdef APP_IPCC_SUPPORT
        //b_ipcc_show = nav_ci_get_ipcc_visible();
        nav_ci_set_ipcc_visible(FALSE);
#endif

        a_nav_viewport_hide_async();
    }

    /*check init flag*/
    if(FALSE == pt_this->b_ui_init)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_lazy_init()\n",
            __FUNCTION__, __LINE__ )); );

        i4_ret = _nav_ipts_lst_lazy_init(pt_this);
        NAV_CHK_FAIL(i4_ret);
    }

    if(pt_this->b_is_opened)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_set_focus(h_listbox) \n", __FUNCTION__, __LINE__ )); );

        i4_ret = c_wgl_set_focus(pt_this->h_listbox, TRUE);
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
        return NAVR_OK;
    }

     NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

     /* Hide yahoo dock */
    {
        a_am_get_active_app(s_app_name);

        a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_status);

        DBG_INFO(("%s() %d: app name=[%s], yahoo status=%d\n",__FUNCTION__,__LINE__,
                                                                    s_app_name, ui1_status));

        if ((1 == ui1_status || 2 == ui1_status)
            && c_strcmp(s_app_name, MMP_NAME) == 0)
        {
            a_tv_net_send_cmd("\n:dtv_app_mtk,yahoo,:ui_show=yes\n");
        }
    }

    {
        /*get active*/
        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_GET_SEL_INDEXES,
                              WGL_PACK((UINT16)1),      /* buffer size */
                              WGL_PACK(&pt_this->ui2_actived_idx));   /* the buffer  */
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox GET_SEL_INDEXES: pt_this->ui2_actived_idx:%d\n",
            __FUNCTION__, __LINE__, pt_this->ui2_actived_idx )); );


        /*get highlight*/
        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_ht),
                              NULL);
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox GET_HLT_INDEX: ui2_ht:%d\n",
            __FUNCTION__, __LINE__, ui2_ht )); );

    }

    /*sync highlight*/
    if(ui2_ht != pt_this->ui2_actived_idx)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK((UINT16)pt_this->ui2_actived_idx),
                          WGL_PACK((NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0));
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM_VISIBLE: (%d, %d)\n",
            __FUNCTION__, __LINE__, pt_this->ui2_actived_idx,
            ((NAV_IPTS_LST_BOX_ELEM_COUNT > 1) ? (NAV_IPTS_LST_BOX_ELEM_COUNT - 1) : 0)
            )); );

    }

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_set_focus(h_listbox, FALSE)\n",
        __FUNCTION__, __LINE__ )); );
    i4_ret = c_wgl_set_focus(pt_this->h_listbox, FALSE);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

#if(NAV_INPUT_SRC_UI_HAS_DEV_ICON)
    UINT8  ui1_cnt_loop;
    for(ui1_cnt_loop = 0;ui1_cnt_loop < NAV_IPTS_LST_BOX_ELEM_COUNT;ui1_cnt_loop++)
    {
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_set_visibility(h_inp_icon_img[%d], WGL_SW_HIDE) \n",
            __FUNCTION__, __LINE__, ui1_cnt_loop )); );
        i4_ret = c_wgl_set_visibility(h_inp_icon_img[ui1_cnt_loop],WGL_SW_HIDE);
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
    }
#endif

#if 0
    for(ui1_cnt_loop = at_crnt_ht_element.ui1_max_elems;ui1_cnt_loop < NAV_IPTS_LST_BOX_ELEM_COUNT;ui1_cnt_loop++)
    {
        ipts_config_icon(h_inp_icon_img[ui1_cnt_loop],
                            NULL_HANDLE,
                            NULL_HANDLE);
    }

    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
#endif

#if(NAV_INPUT_SRC_UI_HAS_TV_CH_NUM_NAME_TEXT)
    i4_ret = c_wgl_set_visibility(h_inp_tv_ch_name_text,WGL_SW_HIDE);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

    i4_ret = c_wgl_set_visibility(h_inp_tv_ch_no_text,WGL_SW_HIDE);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
#endif

    i4_ret = c_wgl_set_visibility(h_inp_icon_shadow_img,WGL_SW_HIDE);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

 #if( !NAV_INPUT_SRC_UI_VERTICAL )
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_set_visibility(pt_this->h_frame, WGL_SW_HIDE_RECURSIVE)\n",
        __FUNCTION__, __LINE__ )); );
    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_HIDE_RECURSIVE);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
 #endif

  #if 0 // No use
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_elem_num),
                          NULL);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox => ui2_elem_num:%d\n", __FUNCTION__, __LINE__, ui2_elem_num )); );
  #endif

#if( NAV_INPUT_SRC_UI_VERTICAL )
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_set_visibility(pt_this->h_frame, WGL_SW_RECURSIVE)\n",
        __FUNCTION__, __LINE__ )); );
    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_RECURSIVE);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_repaint(pt_this->h_frame, NULL, _NAV_IPTS_LIST_IS_SYNC_REPAINT)\n",
        __FUNCTION__, __LINE__ )); );
    i4_ret = c_wgl_repaint(pt_this->h_frame, NULL, _NAV_IPTS_LIST_IS_SYNC_REPAINT);
    NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
#endif


#if(NAV_INPUT_SRC_UI_USE_WDK)
    /* Step3 active toast list text */

    _nav_ipts_lst_new_list_txt_active(pt_this);

    if (pt_this->pt_wdk_view != NULL)
    {
        i4_ret = c_wgl_float(pt_this->pt_wdk_view->h_base_frm, TRUE, WGL_SYNC_AUTO_REPAINT);
        NAV_CHK_FAIL( WGLR_OK == i4_ret ? NAVR_OK : i4_ret );
    }
#endif

    /*reset timer*/
    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_close_timer(,%d) \n",
        __FUNCTION__, __LINE__, _NAV_IPTS_LIST_RESET_TIMER )); );
    i4_ret = _nav_ipts_lst_reset_close_timer(pt_this, _NAV_IPTS_LIST_RESET_TIMER);
    NAV_CHK_FAIL(i4_ret);

    /* Co-exist with Network APs */
    {
        a_tv_net_OSD_appear();
        a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);
    }
    pt_this->b_is_opened = TRUE;
/*
    if (b_key_front_pannel && a_cfg_custom_get_one_button_support())
    {
        nav_ipts_ls_info_show();
    }
*/

#if(NAV_INPUT_SRC_UI_VERTICAL)
    _s_b_navigate_by_up_down = FALSE;
#endif

    return NAVR_OK;
}

static HANDLE_T h_input_source_lock = NULL_HANDLE;

static INT32 _input_source_lock(VOID)
{
    /* Acquire lock */
    if(h_input_source_lock == NULL_HANDLE)
    {
        a_amb_lock();
        if(h_input_source_lock == NULL_HANDLE)
        {
            c_sema_create(&h_input_source_lock,
                          X_SEMA_TYPE_MUTEX,
                          X_SEMA_STATE_UNLOCK);
        }
        a_amb_unlock();
    }

    /* Lock */
    if(h_input_source_lock)
    {
        c_sema_lock(h_input_source_lock, X_SEMA_OPTION_WAIT);
    }

    return NAVR_OK;
}
static INT32 _input_source_unlock(VOID)
{
    /* Unlock */
    if(h_input_source_lock)
    {
        c_sema_unlock(h_input_source_lock);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_close
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_close(
    VOID*                pv_ipts_lst)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                       i4_ret;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if(NULL == pv_ipts_lst)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    /*check init flag*/
    if(FALSE == pt_this->b_ui_init)
    {
        return NAVR_OK;
    }

    /*stop timer*/
    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_close_timer(,stop=%d) \n",
        __FUNCTION__, __LINE__, _NAV_IPTS_LIST_STOP_TIMER )); );
    _nav_ipts_lst_reset_close_timer(pt_this, _NAV_IPTS_LIST_STOP_TIMER);

    /*stop select timer*/
    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_select_timer(,stop=%d) \n",
        __FUNCTION__, __LINE__, _NAV_IPTS_LIST_STOP_TIMER )); );
    _nav_ipts_lst_reset_select_timer (pt_this, _NAV_IPTS_LIST_STOP_TIMER);

    /*reset status*/
    pt_this->b_wait_for_virtual_src_switch = FALSE;

    _input_source_lock();
    {
        if(FALSE == pt_this->b_is_opened)
        {
            _input_source_unlock();
            return NAVR_OK;
        }

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_set_visibility(pt_this->h_frame, WGL_SW_HIDE) \n",
            __FUNCTION__, __LINE__ )); );

        i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_HIDE);
        NAV_CHK_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);

        nav_ipts_lst_float((VOID*)pt_this, FALSE, FALSE);

    #if( NAV_INPUT_SRC_UI_USE_WDK )
        _nav_ipts_new_list_txt_hide(pt_this);

        i4_ret = c_wgl_float(pt_this->pt_wdk_view->h_base_frm, FALSE, FALSE);
        NAV_LOG_ON_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);
    #endif

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_repaint(pt_this->h_frame, NULL, _NAV_IPTS_LIST_IS_SYNC_REPAINT)\n",
            __FUNCTION__, __LINE__ )); );
        i4_ret = c_wgl_repaint(pt_this->h_frame, NULL, _NAV_IPTS_LIST_IS_SYNC_REPAINT);
        NAV_CHK_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);

        /* Co-exist with Network APs */

        {
            a_tv_net_OSD_disapper();
            a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);
        }
        pt_this->b_is_opened = FALSE;

        if(b_PowerON_on_isl_flag == TRUE)
        {
            DBG_INFO(("[isl_func] %s(%d) Set b_PowerON_on_isl_flag = FALSE;\n", __FILE__, __LINE__));
            b_PowerON_on_isl_flag = FALSE;
            nav_set_power_to_input_status(FALSE);
        }
    }
    _input_source_unlock();

    nav_banner_ipts_show_itm();
#ifdef APP_IPCC_SUPPORT
    nav_ci_set_ipcc_visible(b_ipcc_show);
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_is_opened
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_is_opened(
    VOID*                    pv_ipts_lst,
    BOOL*                    pb_is_opened)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;

    if(NULL == pv_ipts_lst || NULL == pb_is_opened)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    *pb_is_opened = pt_this->b_is_opened;
    return NAVR_OK;

}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_is_key_handler(
    VOID*                       pv_ipts_lst,
    UINT32                      ui4_keycode,
    BOOL*                       pb_is_handler)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    UINT32                      ui4_key_act_next, ui4_key_act_next_2, ui4_key_act_prev, ui4_key_act_crnt_ht, ui4_key_next_ht, ui4_key_prev_ht, ui4_key_apply_close, ui4_key_close;
    if((nav_get_key_source() == KEY_SRC_FRONT_PANEL) && a_nav_get_panel_key_disable_status())
    {
        DBG_ERROR(("%s_%d For panel key will be disable by odm Amtran\n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }

    if(NULL == pv_ipts_lst || NULL == pb_is_handler)
    {
        return NAVR_INV_ARG;
    }

    if(FALSE == pt_this->b_is_opened)
    {
        *pb_is_handler = FALSE;
    }
    else
    {
        _NAV_IPTS_LST_CHECK_REMAP(ui4_keycode);

        if(NAV_IPTS_LST_PRI_KEY_GROUP == pt_this->e_key_grp)
        {
            ui4_key_act_next = NAV_IPTS_LST_PRI_KEY_ACT_NEXT;
            ui4_key_act_next_2 = NAV_IPTS_LST_PRI_KEY_ACT_NEXT_2;
            ui4_key_act_prev = NAV_IPTS_LST_PRI_KEY_ACT_PREV;
            ui4_key_act_crnt_ht = NAV_IPTS_LST_PRI_KEY_ACT_CRNT_HT;
            ui4_key_next_ht = NAV_IPTS_LST_PRI_KEY_NEXT_HT;
            ui4_key_prev_ht = NAV_IPTS_LST_PRI_KEY_PREV_HT;
            ui4_key_apply_close = NAV_IPTS_LST_PRI_KEY_APPLY_CLOSE;
            ui4_key_close = NAV_IPTS_LST_PRI_KEY_CLOSE;
        }
        else
        {
            ui4_key_act_next = NAV_IPTS_LST_SEC_KEY_ACT_NEXT;
            ui4_key_act_next_2 = NAV_IPTS_LST_SEC_KEY_ACT_NEXT_2;
            ui4_key_act_prev = NAV_IPTS_LST_SEC_KEY_ACT_PREV;
            ui4_key_act_crnt_ht = NAV_IPTS_LST_SEC_KEY_ACT_CRNT_HT;
            ui4_key_next_ht = NAV_IPTS_LST_SEC_KEY_NEXT_HT;
            ui4_key_prev_ht = NAV_IPTS_LST_SEC_KEY_PREV_HT;
            ui4_key_apply_close = NAV_IPTS_LST_SEC_KEY_APPLY_CLOSE;
            ui4_key_close = NAV_IPTS_LST_SEC_KEY_CLOSE;
        }

        if((ui4_key_act_next == ui4_keycode) ||
           (ui4_key_act_next_2 == ui4_keycode) ||
           (ui4_key_act_prev == ui4_keycode) ||
           (ui4_key_act_crnt_ht == ui4_keycode) ||
           (ui4_key_next_ht == ui4_keycode) ||
           (ui4_key_prev_ht == ui4_keycode) ||
           (ui4_key_apply_close == ui4_keycode) ||
           (ui4_key_close == ui4_keycode))
        {
            *pb_is_handler = TRUE;
        }
        else
        {
            *pb_is_handler = FALSE;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ipts_lst_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 nav_ipts_lst_key_handler(
    VOID*                       pv_ipts_lst,
    UINT32                      ui4_keycode)
{
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;
    INT32                       i4_ret;

    if(NULL == pv_ipts_lst)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Parameters is wrong.\r\n", __FUNCTION__));
        return NAVR_INV_ARG;
    }

    if(FALSE == pt_this->b_is_opened)
    {
        return NAVR_NO_ACTION;
    }

    /**/
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_set_focus(pt_this->h_listbox, FALSE)\n",
        __FUNCTION__, __LINE__ )); );
    i4_ret = c_wgl_set_focus(pt_this->h_listbox, FALSE);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /**/
    i4_ret = _nav_ipts_lst_handle_key(pt_this, ui4_keycode, WGL_KEY_STATE_DOWN);
    nav_ipts_lst_float((VOID*)pt_this, TRUE, FALSE);
    return i4_ret;

}

VOID nav_ipts_auto_close(VOID)
{
    VOID* pt_this = nav_ipts_get_list_context();
    _nav_ipts_lst_autoclose_cb(NULL_HANDLE, pt_this);
}

INT32 nav_ipts_change_active_by_nfy(TV_WIN_ID_T e_grp, VOID *pv_ipts_lst)
{
    INT32           i4_ret = NAVR_OK;
    ISL_REC_T       t_cur_isl = {0};
    BOOL            b_opend = FALSE;
    UINT8           ui1_loop = 0;
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;

    nav_ipts_lst_is_opened(pv_ipts_lst, &b_opend);

    if (!b_opend)
    {
        return NAVR_OK;
    }

    i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_cur_isl);
    NAV_CHK_FAIL(i4_ret);

    for (ui1_loop = 0; ui1_loop < pt_this->ui1_max_elems; ui1_loop++)
    {
        if (pt_this->at_elem[ui1_loop].ui1_id == 0xFF
            && pt_this->at_elem[ui1_loop].b_is_disabled == FALSE)
        {
            /* first element is VIA/WFD */
            _nav_ipts_lst_autoclose_msg_hdlr(pv_ipts_lst, NULL, NULL);

            return i4_ret;
        }

        if (t_cur_isl.ui1_id == pt_this->at_elem[ui1_loop].ui1_id)
        {
            break;
        }
    }

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active(%d)\n",
        __FUNCTION__, __LINE__, ui1_loop )); );

    nav_ipts_lst_set_active(pt_this, ui1_loop, NAV_IPTS_ACTIVE_TYPE_NO_ACTION, FALSE);


    return i4_ret;
}

VOID nav_ipts_lst_print_elems(_NAV_IPTS_LIST_MEMBER_T *pt_this)
{
#if 1
    UINT8 ui1_loop = 0;
    DBG_LOG_PRINT(("%s(): pt_this:0x%X, max_elems = %d\n", __FUNCTION__, (UINT32)pt_this, pt_this->ui1_max_elems));
    DBG_LOG_PRINT(("%s(): ===================================================\n", __FUNCTION__));
    DBG_LOG_PRINT(("Print Input list Info: [ idx\t id\t disabled\t e_func_type ]\n"));

    for (ui1_loop = 0; ui1_loop < pt_this->ui1_max_elems; ui1_loop++)
    {
        DBG_LOG_PRINT(("pt_this->at_elem[%d] = [%d, %d, %d, %d]\n",
                        ui1_loop,
                        pt_this->at_elem[ui1_loop].i2_idx,
                        pt_this->at_elem[ui1_loop].ui1_id,
                        pt_this->at_elem[ui1_loop].b_is_disabled,
                        pt_this->at_elem[ui1_loop].e_func_type));
    }

  #if 0//defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
    //at_ipts_cec_dev
    DBG_LOG_PRINT(("\n\nPrint CEC Info:\n\t idx|\t dev la|\t dev pa\n"));
    for (ui1_loop = 0; ui1_loop < 16; ui1_loop++)
    {
        DBG_LOG_PRINT(("at_ipts_cec_dev[%d] = [%d, %d, %x]\n",
                        ui1_loop,
                        at_ipts_cec_dev[ui1_loop].ui2_dev_index_in_ipts,
                        at_ipts_cec_dev[ui1_loop].e_dev_la,
                        at_ipts_cec_dev[ui1_loop].ui2_dev_pa));
    }
  #endif

    DBG_LOG_PRINT(("%s(): ===================================================\n", __FUNCTION__));
#endif
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_select_msg_hdlr
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_lst_select_msg_hdlr(
    VOID*                                    pv_timer_ver,
    VOID*                                    pv_timer,
    VOID*                                    pv_unused3)
{
#if( NAV_IPTS_LST_SELECT_TIMER_EN)
    INT32                                    i4_ret;
    _NAV_IPTS_LIST_MEMBER_T* pt_this = nav_ipts_get_list_context ();
    HANDLE_T                 h_timer = (HANDLE_T)(UINT32)pv_timer;

    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} h_timer:0x%X, pv_timer_ver:%d\n",
        __FUNCTION__, __LINE__, h_timer, (UINT32)pv_timer_ver )); );

    if (h_timer == pt_this->h_select_timer)
    {
        UINT8 ui1_crnt_idx = 0;
        UINT32 ui4_timer_ver = (UINT32)pv_timer_ver;

        if (ui4_timer_ver != pt_this->ui4_select_timer_ver)
        {
            /* Drop old version request. */
            return;
        }

        if(FALSE == pt_this->b_is_opened)
        {
            return;
        }

        /* Get current active. */
        i4_ret = nav_ipts_lst_get_active(pt_this, &ui1_crnt_idx);
        NAV_LOG_ON_FAIL(i4_ret);

        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active(%d)\n",
            __FUNCTION__, __LINE__, ui1_crnt_idx )); );
        nav_ipts_lst_set_active (pt_this, ui1_crnt_idx, NAV_IPTS_ACTIVE_TYPE_IMMEDIATE, TRUE);

        _nav_ipts_lst_autoclose_msg_hdlr(pt_this, NULL, NULL);
    }
#endif
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_select_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_lst_select_cb(
    HANDLE_T                           h_timer,
    VOID*                              pv_timer_ver)
{
    /*post a message to itself*/
    nav_request_context_switch(_nav_ipts_lst_select_msg_hdlr,
                               pv_timer_ver,
                               (VOID*)h_timer,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_reset_select_timer
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_lst_reset_select_timer(
    _NAV_IPTS_LIST_MEMBER_T*                pt_this,
    BOOL                                    b_stop_only)
{
    INT32                                   i4_ret;

    pt_this->ui4_select_timer_ver++;

    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} b_stop_only:%d, ui4_select_timer_ver:%d \n",
        __FUNCTION__, __LINE__, b_stop_only, pt_this->ui4_select_timer_ver )); );

    if (c_handle_valid(pt_this->h_select_timer) == FALSE)
    {
        DBG_LOG_PRINT(("<NAV INP> file: %s line: %d  %s h_select_timer invalid\n", __FILE__, __LINE__, __FUNCTION__));
        return;
    }
    i4_ret = c_timer_stop(pt_this->h_select_timer);
    if(OSR_OK != i4_ret)
    {
        DBG_LOG_PRINT((_ERROR_HEADER"%s(): stop Input-Src-List's timer failed!\r\n", __FUNCTION__));
        return;
    }

    pt_this->b_is_select_timer_start = !b_stop_only;
    if(_NAV_IPTS_LIST_STOP_TIMER == b_stop_only)
    {
        return;
    }

    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} h_select_timer start timeout=%d \n",
        __FUNCTION__, __LINE__, NAV_IPTS_LST_SELECT_DUR )); );

    i4_ret = c_timer_start(pt_this->h_select_timer,
                           NAV_IPTS_LST_SELECT_DUR,
                           X_TIMER_FLAG_ONCE,
                           _nav_ipts_lst_select_cb,
                           (VOID*)pt_this->ui4_select_timer_ver);

    if(OSR_OK != i4_ret)
    {
        DBG_LOG_PRINT((_ERROR_HEADER"%s(): start ipts's h_select_timer failed!\r\n", __FUNCTION__));
        return;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_frame_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_frame_create(
    _NAV_IPTS_LIST_MEMBER_T*            pt_this,
    HANDLE_T                            h_parent,
    INT32                               i4_frame_offset_x,
    INT32                               i4_frame_offset_y)
{
    GL_RECT_T                           t_rect;
    INT32                               i4_ret;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} i4_frame_offset_x,y: %d,%d\n",
        __FUNCTION__, __LINE__, i4_frame_offset_x, i4_frame_offset_y)); );

    /* create channel frame */
    SET_RECT_BY_SIZE(&t_rect,
                     NAV_IPTS_LST_FM_LEFT,
                     NAV_IPTS_LST_FM_TOP,
                     NAV_IPTS_LST_FM_WIDTH,
                     NAV_IPTS_LST_FM_HEIGHT);

#if(NAV_ENABLE_FRAME_BG_COLOR)
    UINT8  ui1_frame_alpha = 0xC0; // 0
    UINT32 ui4_frame_style = WGL_STL_GL_NO_IMG_UI;
#else
    UINT8  ui1_frame_alpha = 0;
    UINT32 ui4_frame_style = (WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK);
#endif

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_ipts_lst_frame_nfy_fct,
                                 ui1_frame_alpha,
                                 (VOID*)(ui4_frame_style),
                                 pt_this,
                                 &pt_this->h_frame);
    NAV_CHK_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} (0x%X) create h_frame(0x%X) (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
        __FUNCTION__, __LINE__, h_parent, pt_this->h_frame, PRINT_RECT_PARA(t_rect) )); );

#if(NAV_ENABLE_TEST_FRAME_BG_COLOR)
    s_ipts_debug_h_frame = pt_this->h_frame;
#endif

    /* set theme */
#if(NAV_ENABLE_FRAME_BG_COLOR)
    //if( (ui4_frame_style & WGL_STL_GL_NO_IMG_UI) == WGL_STL_GL_NO_IMG_UI )
    {
        /* Menu Background */
        //GL_COLOR_T t_g_menu_color_transp            = { 0,   {   0 }, {   0 }, {   0 }};
        //GL_COLOR_T t_g_menu_color_white             = { 255, { 255 }, { 255 }, { 255 }};
        //GL_COLOR_T t_g_menu_color_black             = { 255, {   0 }, {   0 }, {   0 }};
        GL_COLOR_T t_frame_color_bk0    = { 255, {   1 }, {   1 }, {   1 }}; // Black

        WGL_COLOR_INFO_T    t_color_info = {0};
        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        t_color_info.u_color_data.t_standard.t_enable   = t_frame_color_bk0;
        t_color_info.u_color_data.t_standard.t_disable  = t_frame_color_bk0;
        t_color_info.u_color_data.t_standard.t_highlight= t_frame_color_bk0;

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_frame WGL_CMD_GL_SET_COLOR-WGL_CLR_BK: {%d,%d,%d,%d}\n",
            __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_frame_color_bk0) )); );

        i4_ret = c_wgl_do_cmd( pt_this->h_frame,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK), /* background color */
                              WGL_PACK(& t_color_info) );

        NAV_CHK_FAIL( (i4_ret == WGLR_OK ? NAVR_OK : i4_ret) );
    }
#endif


#ifdef APP_VTRL_INP_SRC_SUPPORT
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_float(pt_this->h_frame,TRUE,FALSE) \n",
        __FUNCTION__, __LINE__ )); );
    i4_ret = c_wgl_float(pt_this->h_frame,TRUE,FALSE);
    NAV_CHK_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_listbox_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_listbox_create(
    _NAV_IPTS_LIST_MEMBER_T*              pt_this,
    APP_COLOR_TYPE_T                      e_color_type)
{
    INT32                                 i4_ret, i4_name_idx, i4_bar_idx;
    GL_RECT_T                             t_rect;
    WGL_LB_INIT_T                         t_init_info;
    WGL_LB_COL_INIT_T                     at_cols[NAV_UI_LISTBOX_COL_NUM];


    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_color_type:%d, e_bar_type:%d\n",
        __FUNCTION__, __LINE__, e_color_type, pt_this->e_bar_type )); );

#if(NAV_INPUT_SRC_UI_VERTICAL)
    // debug...
    if( pt_this->e_bar_type != NAV_IPTS_LST_SBT_RIGHT )
    {
        DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: Invalid e_bar_type:%d\n",
            __FUNCTION__, __LINE__, pt_this->e_bar_type ));
    }
#endif

    switch(pt_this->e_bar_type)
    {
    case NAV_IPTS_LST_SBT_LEFT:
        {
            i4_bar_idx = 0;
            i4_name_idx = 1;
        }
        break;

    case NAV_IPTS_LST_SBT_RIGHT:
        {
            i4_bar_idx = 1;
            i4_name_idx = 0;
        }
        break;

    case NAV_IPTS_LST_SBT_NULL:
    default:
        {
            i4_name_idx = 0;
            i4_bar_idx = 1;
        }
        break;
    }
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} i4_bar_idx:%d, i4_name_idx:%d\n",
        __FUNCTION__, __LINE__, i4_bar_idx, i4_name_idx )); );

    /* Bar(Icon) column */
    at_cols[i4_bar_idx].e_col_type           = LB_COL_TYPE_IMG_SUIT;
    at_cols[i4_bar_idx].ui1_align            = NAV_IPTS_LST_BOX_BAR_ALIGNMENT; // WGL_AS_LEFT_CENTER
    at_cols[i4_bar_idx].ui2_width            = NAV_IPTS_LST_BOX_BAR_WIDTH;

    /*Name column*/
    at_cols[i4_name_idx].e_col_type           = LB_COL_TYPE_TEXT;
    at_cols[i4_name_idx].ui1_align            = NAV_IPTS_LST_BOX_NAME_ALIGNMENT; // WGL_AS_LEFT_CENTER
    at_cols[i4_name_idx].ui2_width            = NAV_IPTS_LST_BOX_NAME_WIDTH;
    at_cols[i4_name_idx].ui2_max_text_len     = NAV_IPTS_LST_BOX_NAME_MAX_TEXT_LEN;

#if( NAV_INPUT_SRC_UI_HAS_ALIAS )
    /*Alias column*/
    at_cols[NAV_UI_LISTBOX_COL_IDX_ALIAS].e_col_type           = LB_COL_TYPE_TEXT;
    at_cols[NAV_UI_LISTBOX_COL_IDX_ALIAS].ui1_align            = NAV_IPTS_LST_BOX_ALIAS_ALIGNMENT;
    at_cols[NAV_UI_LISTBOX_COL_IDX_ALIAS].ui2_width            = NAV_IPTS_LST_BOX_ALIAS_WIDTH;
    at_cols[NAV_UI_LISTBOX_COL_IDX_ALIAS].ui2_max_text_len     = NAV_IPTS_LST_BOX_ALIAS_MAX_TEXT_LEN;
#endif

    t_init_info.ui4_style                   = NAV_IPTS_LST_BOX_STYLE |
                                                WGL_STL_LB_NO_SMART_CUT |
                                                WGL_STL_LB_FORCE_SEL |
                                                WGL_STL_LB_FORCE_HLT;
    t_init_info.ui2_max_elem_num            = pt_this->ui1_max_elems;
    t_init_info.ui2_elem_size               = NAV_IPTS_LST_BOX_ELEM_HEIGHT;
    t_init_info.ui2_elem_distance           = NAV_IPTS_LST_BOX_ELEM_DTANCE;
    t_init_info.ui1_col_num                 = NAV_UI_LISTBOX_COL_NUM;
    t_init_info.at_cols                     = at_cols;



    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} NAV_IPTS_LST_BOX_ELEM_COUNT:%d\n",
        __FUNCTION__, __LINE__, NAV_IPTS_LST_BOX_ELEM_COUNT )); );


    SET_RECT_BY_SIZE(&t_rect,
                     NAV_IPTS_LST_BOX_LEFT,
                     NAV_IPTS_LST_BOX_TOP,
                     NAV_IPTS_LST_BOX_WIDTH,
                     NAV_IPTS_LST_BOX_HEIGHT);

    i4_ret = c_wgl_create_widget(pt_this->h_frame,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 DEFAULT_BK_ALPHA,
                                 &t_init_info,
                                 NULL,
                                 &pt_this->h_listbox);

    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_create_widget(HT_WGL_WIDGET_LIST_BOX) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        pt_this->h_listbox = NULL_HANDLE;
        return NAVR_FAIL;
    }
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_frame(0x%X) create h_listbox(0x%X) (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
        __FUNCTION__, __LINE__, pt_this->h_frame, pt_this->h_listbox, PRINT_RECT_PARA(t_rect)  )); );

#if( NAV_INPUT_SRC_LOAD_SKIN_TEST )
    s_debug_h_listbox = pt_this->h_listbox;
#endif

#ifdef APP_VTRL_INP_SRC_SUPPORT
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_float(h_listbox,TRUE,FALSE) \n",
        __FUNCTION__, __LINE__  )); );
    i4_ret = c_wgl_float(pt_this->h_listbox,TRUE,FALSE);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): c_wgl_float(HT_WGL_WIDGET_LIST_BOX) failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        pt_this->h_listbox = NULL_HANDLE;
        return NAVR_FAIL;
    }
#endif


    do
    {
    #if(NAV_INPUT_SRC_UI_HAS_TITLE)
        WGL_LB_TITLE_INFO_T   t_title_info = {0};
        /*title alignment and rect*/
        t_title_info.ui1_align = NAV_IPTS_LST_TITLE_ALIGN;
        SET_RECT_BY_SIZE(&t_title_info.t_rect,
                         NAV_IPTS_LST_TITLE_LEFT,
                         NAV_IPTS_LST_TITLE_TOP,
                         NAV_IPTS_LST_TITLE_WIDTH,
                         NAV_IPTS_LST_TITLE_HEIGHT);
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox WGL_CMD_LB_SET_TITLE_INFO: (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
            __FUNCTION__, __LINE__, PRINT_RECT_PARA(t_rect)  )); );

        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_SET_TITLE_INFO,
                              (VOID*)&t_title_info,
                              (VOID*)0);
        if(WGLR_OK != i4_ret)
        {
            //DBG_ERROR((_ERROR_HEADER"%s(): Fail to set Title's alignment and rectangle. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: h_listbox WGL_CMD_LB_SET_TITLE_INFO failed!!\n",
                    __FUNCTION__, __LINE__ ));
            i4_ret = NAVR_FAIL;
            break;
        }
    #endif

        i4_ret = _nav_ipts_lst_listbox_load_skin(pt_this, e_color_type, i4_name_idx, i4_bar_idx);
        if(NAVR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: _nav_ipts_lst_listbox_load_skin() failed!!\n",
                    __FUNCTION__, __LINE__ ));
            break;
        }

    #if(NAV_INPUT_SRC_UI_HAS_DEV_ICON)
        UINT8  ui1_cnt_loop;

        for(ui1_cnt_loop = 0;ui1_cnt_loop < NAV_IPTS_LST_BOX_ELEM_COUNT;ui1_cnt_loop++)
        {
            SET_RECT_BY_SIZE (&t_rect,
                              NAV_IPTS_LST_BOX_LEFT + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ,
                              NAV_IPTS_LST_BOX_TOP + (NAV_IPTS_LST_BOX_ELEM_HEIGHT *ui1_cnt_loop),
                              NAV_IPTS_LST_BOX_WIDTH - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ -NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_RIGHT_ADJ,
                              NAV_IPTS_LST_BOX_ELEM_HEIGHT/2);

            i4_ret = ipts_create_icon(pt_this->h_frame,
                                    h_inp_icon_img+ui1_cnt_loop,
                                    &t_rect,
                                    NULL_HANDLE,
                                    NULL_HANDLE);
            if(WGLR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: ipts_create_icon() failed!!\n", __FUNCTION__, __LINE__ ));
                return NAVR_FAIL;
            }
            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_frame create_icon() =>h_inp_icon_img[%d]:0x%X): (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
                __FUNCTION__, __LINE__, ui1_cnt_loop, h_inp_icon_img[ui1_cnt_loop], PRINT_RECT_PARA(t_rect) )); );
        }
    #endif

    #if(NAV_INPUT_SRC_UI_HAS_TV_CH_NUM_NAME_TEXT)
        SET_RECT_BY_SIZE (&t_rect,
                      NAV_IPTS_LST_BOX_LEFT + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ,
                      NAV_IPTS_LST_BOX_TOP + (NAV_IPTS_LST_BOX_ELEM_HEIGHT/2),
                      NAV_IPTS_LST_BOX_WIDTH - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ -NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_RIGHT_ADJ,
                      NAV_IPTS_LST_BOX_ELEM_HEIGHT/2);
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_frame h_inp_tv_ch_name_text (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
            __FUNCTION__, __LINE__, PRINT_RECT_PARA(t_rect) )); );
        i4_ret = ipts_create_text_utf16(pt_this->h_frame,
                                &h_inp_tv_ch_name_text,
                                &t_rect,
                                NAV_IPTS_CH_NAME_FONT,
                                NAV_IPTS_CH_NAME_FONT_SIZE,
                                NULL);
        if(WGLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: ipts_create_text_utf16() failed!!\n",  __FUNCTION__, __LINE__ ));
            return NAVR_FAIL;
        }

        SET_RECT_BY_SIZE (&t_rect,
                          NAV_IPTS_LST_BOX_LEFT + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ,
                          NAV_IPTS_LST_BOX_TOP,
                          NAV_IPTS_LST_BOX_WIDTH - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_RIGHT_ADJ,
                          NAV_IPTS_LST_BOX_ELEM_HEIGHT/2);
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_frame h_inp_tv_ch_no_text (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
            __FUNCTION__, __LINE__, PRINT_RECT_PARA(t_rect) )); );
        i4_ret = ipts_create_text_utf16(pt_this->h_frame,
                                &h_inp_tv_ch_no_text,
                                &t_rect,
                                NAV_IPTS_CH_NO_FONT,
                                NAV_IPTS_CH_NO_FONT_SIZE,//Cedric 0402
                                NULL);
        if(WGLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: ipts_create_text_utf16() failed!!\n",  __FUNCTION__, __LINE__ ));
            return NAVR_FAIL;
        }
    #endif


        SET_RECT_BY_SIZE (&t_rect,
                          NAV_IPTS_LST_BOX_LEFT,
                          NAV_IPTS_LST_BOX_TOP + (NAV_IPTS_LST_BOX_ELEM_HEIGHT * NAV_IPTS_LST_BOX_ELEM_COUNT),
                          NAV_IPTS_LST_BOX_WIDTH,
                          NAV_IPTS_LST_SHADOW_HEIGHT);
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_frame create_icon(h_inp_icon_shadow_img): (%d,%d  w:%d,h:%d  r:%d,b:%d ) \n",
            __FUNCTION__, __LINE__,  PRINT_RECT_PARA(t_rect) )); );
        i4_ret = ipts_create_icon(pt_this->h_frame,
                                &h_inp_icon_shadow_img,
                                &t_rect,
                                h_g_nav_banner_new_lastshadow_img,
                                h_g_nav_banner_new_lastshadow_img);
        if(WGLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: ipts_create_icon() failed!!\n",  __FUNCTION__, __LINE__ ));
            return NAVR_FAIL;
        }

        return NAVR_OK;

    } while(0);


    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} c_wgl_destroy_widget(pt_this->h_listbox) \n",
        __FUNCTION__, __LINE__  )); );

    c_wgl_destroy_widget(pt_this->h_listbox);
    pt_this->h_listbox = NULL_HANDLE;

    return i4_ret;
}


#if( NAV_INPUT_SRC_LOAD_SKIN_TEST )

#define DEBUG_PARA_NUM_MAX 32
static int s_ai_ipts_debug_para[DEBUG_PARA_NUM_MAX];
int _nav_ipts_debug_read_para(void)
{
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    c_memset(s_ai_ipts_debug_para, 0, sizeof(s_ai_ipts_debug_para) );

    char* pcFullFileName = "/data/nav_input_src.txt";

    FILE* pfIn = fopen( pcFullFileName, "r" );
    if(pfIn == NULL)
    {
        DBG_LOG_PRINT(("\n\nError: Open file(%s) failed\n\n", pcFullFileName));
        return -1;
    }

    int i_para_count = 0;

    int i;
    for( i = 0; i < DEBUG_PARA_NUM_MAX; i += 1 )
    {
        int i_fscan_rtn = fscanf(pfIn, "%d", &(s_ai_ipts_debug_para[i]) );
        if( i_fscan_rtn == 1 )
        {
            printf("%d scan => %d => %d \n", i, i_fscan_rtn, s_ai_ipts_debug_para[i] );
            i_para_count += 1;
        }
        else
        {
            printf("%d scan => %d \n", i, i_fscan_rtn );
            break;
        }
    }

    fclose(pfIn);

    return i_para_count;
}

#if(NAV_ENABLE_TEST_FRAME_BG_COLOR)
void _nav_ipts_lst_listbox_load_skin_test_frame_BG_color(int* piColor)
{
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}\n", __FUNCTION__, __LINE__ )); );

    //s_ipts_debug_h_frame = pt_this->h_frame;

    /* Menu Background */
    //GL_COLOR_T t_g_menu_color_transp            = { 0,   {   0 }, {   0 }, {   0 }};
    //GL_COLOR_T t_g_menu_color_white             = { 255, { 255 }, { 255 }, { 255 }};
    //GL_COLOR_T t_g_menu_color_black             = { 255, {   0 }, {   0 }, {   0 }};

    GL_COLOR_T t_frame_color_bk0  = { 255, {   1 }, {   1 }, {   1 }};

    t_frame_color_bk0.a = piColor[0];
    t_frame_color_bk0.u1.r = piColor[1];
    t_frame_color_bk0.u2.g = piColor[2];
    t_frame_color_bk0.u3.b = piColor[3];

    WGL_COLOR_INFO_T    t_color_info = {0};
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info.u_color_data.t_standard.t_enable   = t_frame_color_bk0;
    t_color_info.u_color_data.t_standard.t_disable  = t_frame_color_bk0;
    t_color_info.u_color_data.t_standard.t_highlight= t_frame_color_bk0;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_frame WGL_CMD_GL_SET_COLOR-WGL_CLR_BK: {%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_frame_color_bk0)  ));   );

    INT32 i4_ret = c_wgl_do_cmd( s_ipts_debug_h_frame,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK), /* background color */
                          WGL_PACK(& t_color_info) );

    NAV_LOG_ON_FAIL( i4_ret );
}
#endif

void _nav_ipts_lst_listbox_load_skin_test_listbox_ELM_BG_color(int* piColor)
{
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}\n", __FUNCTION__, __LINE__ )); );

    GL_COLOR_T t_listbox_elm_BG_color_normal = { 0, { 0 }, { 0 }, { 0 }};
    GL_COLOR_T t_listbox_elm_BG_color_high = { 255, { 122 }, { 122 }, { 122 }};

    t_listbox_elm_BG_color_high.a = piColor[0];
    t_listbox_elm_BG_color_high.u1.r = piColor[1];
    t_listbox_elm_BG_color_high.u2.g = piColor[2];
    t_listbox_elm_BG_color_high.u3.b = piColor[3];
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} t_listbox_elm_BG_color_high:{%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_listbox_elm_BG_color_high) )); );


#if 1
    /* element background colors */
    /* transparent element background color */
    WGL_LB_COLOR_ELEM_SET_T  t_color_elem = {0};

    t_color_elem.t_normal = t_listbox_elm_BG_color_normal;
    t_color_elem.t_disable             = t_color_elem.t_normal;
    t_color_elem.t_pushed              = t_color_elem.t_normal;
    t_color_elem.t_selected            = t_color_elem.t_normal;
    t_color_elem.t_selected_disable    = t_color_elem.t_normal;

    t_color_elem.t_highlight           = t_listbox_elm_BG_color_high;
    t_color_elem.t_highlight_unfocus   = t_color_elem.t_highlight;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_SET_ELEM_COLOR-WGL_CLR_BK: {%d,%d,%d,%d}{%d,%d,%d,%d}  \n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_listbox_elm_BG_color_normal),
                        NAV_PRINT_COLOR_PARA(t_listbox_elm_BG_color_high)   )); );

    INT32 i4_ret = c_wgl_do_cmd( s_debug_h_listbox,
                               WGL_CMD_LB_SET_ELEM_COLOR,
                               WGL_PACK(WGL_CLR_BK),
                               WGL_PACK(&t_color_elem));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set element's background color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif

}

void _nav_ipts_lst_listbox_load_skin_test_listbox_BG_color(int* piColor)
{
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}\n", __FUNCTION__, __LINE__ )); );

    GL_COLOR_T t_listbox_bg_color = { 0, { 0 }, { 0 }, { 0 }};

    t_listbox_bg_color.a = piColor[0];
    t_listbox_bg_color.u1.r = piColor[1];
    t_listbox_bg_color.u2.g = piColor[2];
    t_listbox_bg_color.u3.b = piColor[3];
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} t_listbox_bg_color:{%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_listbox_bg_color) )); );


    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_GL_SET_COLOR-WGL_CLR_BK: {%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_listbox_bg_color) )); );

    WGL_COLOR_INFO_T  t_clr_info = {0};

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_listbox_bg_color;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_listbox_bg_color;
    t_clr_info.u_color_data.t_standard.t_disable    = t_listbox_bg_color;
    INT32 i4_ret = c_wgl_do_cmd(s_debug_h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set listbox bk-color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

}

void _nav_ipts_lst_listbox_load_skin_test(void)
{
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}\n", __FUNCTION__, __LINE__ )); );

    int i_para_count = _nav_ipts_debug_read_para();

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} i_para_count:%d\n",
        __FUNCTION__, __LINE__, i_para_count )); );

    if( i_para_count < 8 )
    {
        DBG_LOG_PRINT(("\nError: No debug para! \n"));
        return;
    }

    //=============================================================================================
#if(NAV_ENABLE_TEST_FRAME_BG_COLOR)
    _nav_ipts_lst_listbox_load_skin_test_frame_BG_color( s_ai_ipts_debug_para + 0 );
#endif
    //===================================================================================
  #if 0
    /* element background colors */
    _nav_ipts_lst_listbox_load_skin_test_listbox_ELM_BG_color(s_ai_ipts_debug_para + 4);
  #endif
    //===================================================================================
  #if 0
    if( i_para_count < 12 )
    {
        DBG_LOG_PRINT(("\nError: No debug para! \n"));
        return;
    }

    _nav_ipts_lst_listbox_load_skin_test_listbox_BG_color(s_ai_ipts_debug_para + 8);
  #endif
}
#endif

#if(NAV_INPUT_SRC_UI_HAS_TITLE)
static INT32 _nav_ipts_lst_listbox_load_skin_title(
    _NAV_IPTS_LIST_MEMBER_T*    pt_this,
    APP_COLOR_TYPE_T            e_color_type
    )
{
    INT32  i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T    t_title_font_info = { FE_FNT_SIZE_CUSTOM, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL, 0, 24, 0};


    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_color_type:%d\n",
        __FUNCTION__, __LINE__, e_color_type )); );


#if 0
    /* Only for fix klocwork warning */
    c_strncpy( t_title_font_info.a_c_font_name, NAV_FONT_NORMAL, WGL_MAX_FONT_NAME );
    t_title_font_info.a_c_font_name[WGL_MAX_FONT_NAME-1] = '\0';
    c_strncpy( t_elem_font_info.a_c_font_name, NAV_FONT_NORMAL, WGL_MAX_FONT_NAME );
    t_elem_font_info.a_c_font_name[WGL_MAX_FONT_NAME-1] = '\0';
#endif


    /*Title's foreground color*/
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    NAV_IPTS_LST_BOX_CLR_TITLE_FG(e_color_type, t_clr_info.u_color_data.t_standard.t_disable);
    t_clr_info.u_color_data.t_standard.t_enable      = t_clr_info.u_color_data.t_standard.t_disable;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_clr_info.u_color_data.t_standard.t_disable;

    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_FG,
                          &t_clr_info);
    if(WGLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((_ERROR_HEADER"%s(): Fail to set Title's foreground color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /*Title's background color*/
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    NAV_IPTS_LST_BOX_CLR_TITLE_BK(e_color_type, t_clr_info.u_color_data.t_standard.t_disable);
    t_clr_info.u_color_data.t_standard.t_enable      = t_clr_info.u_color_data.t_standard.t_disable;
    t_clr_info.u_color_data.t_standard.t_highlight   = t_clr_info.u_color_data.t_standard.t_disable;

    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_LB_TITLE_BK,
                          &t_clr_info);
    if(WGLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((_ERROR_HEADER"%s(): Fail to set Title's background color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set Title's font */
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_title_font_info,
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_LOG_PRINT((_ERROR_HEADER"%s(): Fail to set Title's font. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_listbox_load_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_listbox_load_skin(
    _NAV_IPTS_LIST_MEMBER_T*                 pt_this,
    APP_COLOR_TYPE_T                         e_color_type,
    INT32                                    i4_name_idx,
    INT32                                    i4_bar_idx)
{
    WGL_FONT_INFO_T                          t_elem_font_info = { FE_FNT_SIZE_CUSTOM, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL, 0, 20, 0};;
    WGL_COLOR_INFO_T                         t_clr_info;
    WGL_INSET_T                              t_inset;
    WGL_LB_COLOR_ELEM_SET_T                  t_color_elem;
    WGL_LB_KEY_MAP_T                         t_key_map = {0};
    INT32                                    i4_ret, ui4_idx;



    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_color_type:%d, i4_name_idx:%d, i4_bar_idx:%d\n",
        __FUNCTION__, __LINE__, e_color_type, i4_name_idx, i4_bar_idx )); );



    /* listbox view port background color */
    t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
    NAV_IPTS_LST_BOX_CLR_VP_BK(e_color_type, t_clr_info.u_color_data.t_standard.t_disable);
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} t_clr_info.u_color_data.t_standard.t_disable:{%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_clr_info.u_color_data.t_standard.t_disable) )); );

    t_clr_info.u_color_data.t_standard.t_enable    = t_clr_info.u_color_data.t_standard.t_disable;
    t_clr_info.u_color_data.t_standard.t_highlight = t_clr_info.u_color_data.t_standard.t_disable;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_GL_SET_COLOR-CLR_LB_VP_BK: {%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_clr_info.u_color_data.t_standard.t_disable) )); );

    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_VP_BK),
                          WGL_PACK(&t_clr_info));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set listbox viewport's bk-color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }


#if( NAV_INPUT_SRC_UI_LB_BG_COLOR )
    /* Set LB colors */
    GL_COLOR_T t_listbox_bg_color = { 200, { 1 }, { 1 }, { 1 }};

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_GL_SET_COLOR-WGL_CLR_BK: {%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_listbox_bg_color) )); );

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_listbox_bg_color;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_listbox_bg_color;
    t_clr_info.u_color_data.t_standard.t_disable    = t_listbox_bg_color;
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set listbox bk-color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif


#if(NAV_INPUT_SRC_UI_LB_ELM_BG_IMG)
    /* element image background */
    WGL_LB_IMG_ELEM_SET_T  t_img_elem = {0};

    t_img_elem.h_highlight           = pt_this->h_listbox_ht_img;
    t_img_elem.h_highlight_unfocus   = pt_this->h_listbox_ht_img;
    t_img_elem.h_normal = pt_this->h_listbox_bk_img;
    t_img_elem.h_disable = pt_this->h_listbox_bk_img;
    t_img_elem.h_selected = pt_this->h_listbox_bk_img;
    t_img_elem.h_selected_disable = pt_this->h_listbox_bk_img;
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE\n",
        __FUNCTION__, __LINE__, e_color_type )); );
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                          WGL_PACK(& t_img_elem),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set listbox highlight image. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif


#if(NAV_INPUT_SRC_UI_LB_ELM_BG_COLOR)
    /* element background colors */

  #if 0 // No use
    NAV_IPTS_LST_BOX_CLR_ELEM_BK(e_color_type, t_color_elem.t_normal);
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} t_color_elem.t_normal:{%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_color_elem.t_normal) )); );
  #endif

  #if 1 // VIZIO
    /* transparent element background color */
    GL_COLOR_T t_listbox_elm_BG_color_normal = { 0, { 0 }, { 0 }, { 0 }};
    GL_COLOR_T t_listbox_elm_BG_color_high = { 255, { 64 }, { 128 }, { 128 }};

    t_color_elem.t_normal = t_listbox_elm_BG_color_normal;
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} t_color_elem.t_normal:{%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_color_elem.t_normal) )); );
  #endif

    t_color_elem.t_disable             = t_color_elem.t_normal;
    t_color_elem.t_highlight           = t_color_elem.t_normal;
    t_color_elem.t_highlight_unfocus   = t_color_elem.t_normal;
    t_color_elem.t_pushed              = t_color_elem.t_normal;
    t_color_elem.t_selected            = t_color_elem.t_normal;
    t_color_elem.t_selected_disable    = t_color_elem.t_normal;

    t_color_elem.t_highlight           = t_listbox_elm_BG_color_high;
    t_color_elem.t_highlight_unfocus   = t_listbox_elm_BG_color_high;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_SET_ELEM_COLOR-WGL_CLR_BK {%d,%d,%d,%d}\n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_color_elem.t_highlight) )); );

    i4_ret = c_wgl_do_cmd (pt_this->h_listbox,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(&t_color_elem));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set element's background color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif


    /*column BG color*/
    NAV_IPTS_LST_BOX_CLR_COL_BK(e_color_type, t_color_elem.t_normal);
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} t_color_elem.t_normal {%d,%d,%d,%d} \n",
        __FUNCTION__, __LINE__, NAV_PRINT_COLOR_PARA(t_color_elem.t_normal) )); );
    t_color_elem.t_disable             = t_color_elem.t_normal;
    t_color_elem.t_highlight           = t_color_elem.t_normal;
    t_color_elem.t_highlight_unfocus   = t_color_elem.t_normal;
    t_color_elem.t_pushed              = t_color_elem.t_normal;
    t_color_elem.t_selected            = t_color_elem.t_normal;
    t_color_elem.t_selected_disable    = t_color_elem.t_normal;

    for (ui4_idx = 0 ; ui4_idx < NAV_UI_LISTBOX_COL_NUM; ui4_idx++)
    {
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox[][%d] WGL_CMD_LB_SET_COL_COLOR-WGL_CLR_BK: {%d,%d,%d,%d} \n",
            __FUNCTION__, __LINE__, ui4_idx, NAV_PRINT_COLOR_PARA(t_color_elem.t_normal) )); );

        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui4_idx, WGL_CLR_BK),
                              WGL_PACK(&t_color_elem));
        if(WGLR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): Fail to set col-%d's background color. i4_ret = %d\r\n", __FUNCTION__, ui4_idx, i4_ret));
            return NAVR_FAIL;
        }
    }


    /*set name text color*/
    NAV_IPTS_LST_BOX_CLR_ELEM_FG(e_color_type, t_color_elem);
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Name: h_listbox[][%d] WGL_CMD_LB_SET_COL_COLOR-WGL_CLR_TEXT: {%d,%d,%d,%d} \n",
        __FUNCTION__, __LINE__, i4_name_idx, NAV_PRINT_COLOR_PARA(t_color_elem.t_normal) )); );
    i4_ret = c_wgl_do_cmd (pt_this->h_listbox,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(i4_name_idx, WGL_CLR_TEXT),
                           WGL_PACK(&t_color_elem));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set name's fg color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

#if(NAV_INPUT_SRC_UI_HAS_ALIAS)
    /*set alias color*/
    NAV_IPTS_LST_BOX_CLR_ELEM_FG(e_color_type, t_color_elem);
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} alias: h_listbox[][%d] WGL_CMD_LB_SET_COL_COLOR-WGL_CLR_TEXT: {%d,%d,%d,%d} \n",
        __FUNCTION__, __LINE__, NAV_UI_LISTBOX_COL_IDX_ALIAS, NAV_PRINT_COLOR_PARA(t_color_elem.t_normal) )); );
    i4_ret = c_wgl_do_cmd (pt_this->h_listbox,
                           WGL_CMD_LB_SET_COL_COLOR,
                           WGL_PACK_2(NAV_UI_LISTBOX_COL_IDX_ALIAS, WGL_CLR_TEXT),
                           WGL_PACK(&t_color_elem));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set alias's fg color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif

    /* set Name's font */
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox[][%d] WGL_CMD_LB_SET_COL_FONT\n",
        __FUNCTION__, __LINE__, i4_name_idx )); );
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_SET_COL_FONT,
                          WGL_PACK(i4_name_idx),
                          WGL_PACK(&t_elem_font_info));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set Name's font. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

#if(NAV_INPUT_SRC_UI_HAS_ALIAS)
    /* set Alias's font */
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox[][%d] WGL_CMD_LB_SET_COL_FONT\n",
        __FUNCTION__, __LINE__, NAV_UI_LISTBOX_COL_IDX_ALIAS )); );
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_SET_COL_FONT,
                          WGL_PACK(NAV_UI_LISTBOX_COL_IDX_ALIAS),
                          WGL_PACK(&t_elem_font_info));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set Name's font. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif

#if(NAV_INPUT_SRC_UI_HAS_TITLE)
    if( 0 != _nav_ipts_lst_listbox_load_skin_title( pt_this, e_color_type) )
    {
        DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} Error: _nav_ipts_lst_listbox_load_skin_title() failed!!\n", __FUNCTION__, __LINE__ ));
        return NAVR_FAIL;
    }
#endif

    /* set Name's inset */
    NAV_IPTS_LST_BOX_NAME_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(i4_name_idx),
                          WGL_PACK(&t_inset));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set Name's Inset. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

#if(NAV_INPUT_SRC_UI_HAS_ALIAS)
    /* set Alias's inset */
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(NAV_UI_LISTBOX_COL_IDX_ALIAS),
                          WGL_PACK(&t_inset));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set Name's Inset. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
#endif

    /* set Bar's inset */
    if(i4_bar_idx >= 0)
    {
        NAV_IPTS_LST_BOX_BAR_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);

        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK(i4_bar_idx),
                              WGL_PACK(&t_inset));
        if(WGLR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): Fail to set Bar's Inset. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
    }

    /* set content inset */
    NAV_IPTS_LST_BOX_CONTENT_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set content's Inset. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set element inset */
    NAV_IPTS_LST_BOX_ELEM_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set element's Inset. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* Set long text scroll effect */
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect = {0};
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (pt_this->h_listbox,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    //MENU_LOG_ON_FAIL(i4_ret);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }


    /*set keymap*/
    i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                          WGL_CMD_LB_SET_KEY_MAP,
                          WGL_PACK(& t_key_map),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set keymap. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_image_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_image_create(
    _NAV_IPTS_LIST_MEMBER_T*            pt_this)
{
    INT32                               i4_ret;


    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} \n",
        __FUNCTION__, __LINE__ )); );

#ifdef NAV_IPTS_LST_BOX_BK_IMG
    /*listbox background image*/
    i4_ret = c_wgl_img_tpl_create(NAV_IPTS_LST_BOX_BK_STYLE,
                                  &NAV_IPTS_LST_BOX_BK_IMG,
                                  &pt_this->h_listbox_bk_img);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

#else
    i4_ret = nav_img_create_ch_list_bk_img_tpl(&pt_this->h_listbox_bk_img);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

#endif

#ifdef NAV_IPTS_LST_BOX_HT_IMG
    /*listbox highlight image*/
    i4_ret = c_wgl_img_tpl_create(NAV_IPTS_LST_BOX_HT_STYLE,
                                  &NAV_IPTS_LST_BOX_HT_IMG,
                                  &pt_this->h_listbox_ht_img);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

#else
    i4_ret = nav_img_create_hlt_bar_bk_img_tpl(&pt_this->h_listbox_ht_img);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

#endif

#ifdef APP_NAV_IPTS_LST_BAR_DISABLE
    /*disable image in status bar*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                  &NAV_IPTS_LST_BAR_DIS_IMG,
                                  &pt_this->h_disable_img);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                  &NAV_IPTS_LST_BAR_DIS_HT_IMG,
                                  &pt_this->h_disable_ht_img);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
#endif

#ifdef APP_NAV_IPTS_LST_BAR_ACTIVE
    /*disable image in status bar*/
    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                  &NAV_IPTS_LST_BAR_ACTIVE_IMG,
                                  &pt_this->h_active_img);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    //NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} Create pt_this->h_active_img =0x%X\n",
    //    __FUNCTION__, __LINE__, pt_this->h_active_img )); );


    i4_ret = c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                  &NAV_IPTS_LST_BAR_ACTIVE_HT_IMG,
                                  &pt_this->h_active_ht_img);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    //NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} Create pt_this->h_active_ht_img =0x%X\n",
    //    __FUNCTION__, __LINE__, pt_this->h_active_ht_img )); );
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_is_able_to_pip_pop
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _nav_ipts_lst_is_able_to_pip_pop (ISL_REC_T* pt_isl_other, ISL_REC_T* pt_isl_iterate)
{
    INT32 i4_ret;
    BOOL b_is_same = FALSE;

    /*disabled?*/
    i4_ret = a_isl_is_same_group(pt_isl_other, pt_isl_iterate, &b_is_same);
    if(ISLR_OK != i4_ret)
    {
        return FALSE;
    }

    if ((pt_isl_iterate->ui4_attr_bits & ISL_ATTR_BIT_SKIPPED) == ISL_ATTR_BIT_SKIPPED)
    {
        b_is_same = TRUE;
    }
#ifdef APP_VTRL_INP_SRC_SUPPORT
    if ((pt_isl_iterate->t_avc_info.e_video_type & DEV_VTRL) == DEV_VTRL)
    {
        b_is_same = TRUE;
    }
#endif

    return !b_is_same;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_calculate_num
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_calculate_num(VOID)
{
    INT32                               i4_ret = NAVR_OK;
    ACFG_RETAIL_MODE_T                     t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    UINT16                              ui2_loop = 0;
    UINT8                               ui1_num_recs = 0;
    UINT8                               ui1_cec_func = APP_CFG_CEC_OFF;

#if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
    CEC_DEV_LST_T t_lst;
    UINT8 ui1_amp_conn_num;
#endif

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    c_memset(&t_list_elem_num, 0, sizeof(t_list_elem_num));

    /*get count of input source*/
    i4_ret = a_isl_get_num_rec(&ui1_num_recs);
    NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret );

    t_list_elem_num.ui2_isl_num = ui1_num_recs;

#ifdef APP_WFD_SUPPORT
    /* Add Miracast rec */
    if ((a_cfg_custom_get_wfd_support()==TRUE)
        && (a_wfd_is_rtsp_play_status() == TRUE))
    {
        ui1_num_recs++;
        t_list_elem_num.ui2_wfd_num = 1;
    }
#endif

{
    ui1_num_recs++;
    t_list_elem_num.ui2_func_num = 1;
}

    /* Add CEC rec */
    ui1_amp_conn_num = 0;
    a_cfg_get_cec_func(&ui1_cec_func);

    if (ui1_cec_func != APP_CFG_CEC_OFF)
    {
        c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
        a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

        for (ui2_loop = 0; ui2_loop < t_lst.ui1_dev_num; ui2_loop++)
        {
            if (TRUE == t_lst.at_dev_info[ui2_loop].b_amp_connected)
            {
            #ifdef APP_ARC_ONLY
                if (APP_CFG_CEC_ARC_ONLY == ui1_cec_func
                    && CECM_LOG_ADDR_AUD_SYS != t_lst.at_dev_info[ui2_loop].e_la)
                {
                    continue;
                }
            #endif
                ui1_amp_conn_num++;
            }
        }

        ui1_num_recs += ui1_amp_conn_num;
        t_list_elem_num.ui2_cec_num = ui1_amp_conn_num;
    }

    /* Add retail mode */
#ifdef APP_RETAIL_MODE_SUPPORT
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
#endif

    if (FALSE && b_key_front_pannel && (ACFG_RETAIL_MODE_NORMAL == t_retail_mode))
    {
        ui1_num_recs++;
        t_list_elem_num.ui2_retail_num = 1;
    }

    t_list_elem_num.ui2_total_num = (t_list_elem_num.ui2_via_num
                                    + t_list_elem_num.ui2_wfd_num
                                    + t_list_elem_num.ui2_isl_num
                                    + t_list_elem_num.ui2_cec_num
                                    + t_list_elem_num.ui2_retail_num
                                    + t_list_elem_num.ui2_func_num);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} => t_list_elem_num.ui2_total_num:%d\n",
        __FUNCTION__, __LINE__, t_list_elem_num.ui2_total_num )); );

    return NAVR_OK;
}

static INT32 _nav_ipts_lst_elem_sort(IPT_LIST_REC_T* pt_rec)
{
    INT32                               i4_ret = NAVR_OK;
    IPT_LIST_REC_T                      *pt_iterate_rec = pt_rec;
    UINT16                              ui2_loop = 0;
    ISL_REC_T                           t_isl_rec = {0};

    IPT_LIST_REC_T                      t_comp_rec[2];
    UINT8                               ui1_comp_num = 0;

    IPT_LIST_REC_T                      t_hdmi_rec[IPTS_MAX_HDMI_PORT];
    UINT8                               ui1_hdmi_num = 0;

    IPT_LIST_REC_T                      t_tv_rec[1];
    UINT8                               ui1_tv_num = 0;

    IPT_LIST_REC_T                      t_vga_rec;
    UINT8                               ui1_vga_num = 0;

    IPT_LIST_REC_T                      t_cast_rec[IPTS_MAX_VTRL_PORT + 1];
    UINT8                               ui1_cast_num = 0;
    UINT8                               ui1_smartcast_count = 0;

#ifdef ISL_VTRL_INP_SRC_MMP
    IPT_LIST_REC_T                      t_usb_rec;
    UINT8   ui1_usb_plug = 0;
#endif

    IPT_LIST_REC_T                      t_func_rec;
    UINT8                               ui1_func_num = 0;

    IPT_LIST_REC_T                      t_cec_rec[IPTS_MAX_CEC_PORT];
    UINT8                               t_cec_rec_dev_idx_in_list[IPTS_MAX_CEC_PORT];
    UINT8                               ui1_cec_num = 0;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} -- start\n", __FUNCTION__, __LINE__ )); );

    c_memset(&t_comp_rec, 0, sizeof(t_comp_rec));
    c_memset(&t_vga_rec, 0, sizeof(t_vga_rec));
    c_memset(&t_tv_rec, 0, sizeof(t_tv_rec));
    c_memset(t_hdmi_rec, 0, sizeof(t_hdmi_rec));
    c_memset(t_cast_rec, 0, sizeof(t_cast_rec));
#ifdef ISL_VTRL_INP_SRC_MMP
    c_memset(&t_usb_rec, 0, sizeof(t_usb_rec));
#endif
    c_memset(&t_func_rec, 0, sizeof(t_func_rec));


    for (ui2_loop = 0; ui2_loop < pt_rec[0].ui2_num; ui2_loop++)
    {
        /* input source */
        {
            c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));

            /*function element*/
            {
                if(pt_iterate_rec[ui2_loop].t_elem.e_func_type != E_FUNC_ELEMENT_NULL)
                {
                    if( _nav_ipts_lst_pwrdwn_check_sku_default_enable() == TRUE)
                    {
                        if ((nav_get_power_to_input_status() == TRUE && pt_iterate_rec[ui2_loop].t_elem.e_func_type == E_FUNC_ELEMENT_POWER_OFF)
                            || b_PowerON_on_isl_flag == TRUE)
                        {
                            ISL_LOG(_ISL_LOG_TYPE_FUNC,("%s(%d) E_FUNC_ELEMENT_POWER_OFF: ui2_loop[%d] \n", __FUNCTION__, __LINE__,ui2_loop));
                            c_memcpy(&t_func_rec, &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
                            ui1_func_num ++;

                            b_PowerON_on_isl_flag = TRUE;
                        }
                    }
                    continue;
                }
            }

            i4_ret = a_isl_get_rec_by_id(pt_iterate_rec[ui2_loop].t_elem.ui1_id, &t_isl_rec);

            if (i4_ret != ISLR_OK)
            {
                continue;
            }

            /* _nav_ipts_get_virtual_input_record */
            if (a_nav_ipts_is_cast_source(&t_isl_rec) == TRUE)
            {
                if(ui1_cast_num > (IPTS_MAX_VTRL_PORT + 1))
                {
                    continue;
                }
                c_memcpy(&(t_cast_rec[ui1_cast_num]), &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
                ui1_cast_num++;
            }
#ifdef ISL_VTRL_INP_SRC_MMP
            else if (a_nav_ipts_is_usb_source(&t_isl_rec))
            {
                c_memcpy(&t_usb_rec, &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
            }
#endif
            else if (a_nav_ipts_is_tv_source(&t_isl_rec) == TRUE)
            {
                c_memcpy(&t_tv_rec, &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
                DBG_ERROR(("%s_%d e_src_type:%d \n",__FUNCTION__,__LINE__,t_tv_rec[0].e_src_type));
                ui1_tv_num++;
            }
            else if (a_nav_ipts_is_comp_source(&t_isl_rec) == TRUE)
            {
                if (ui1_comp_num > 2)
                {
                    continue;
                }

                c_memcpy(&(t_comp_rec[ui1_comp_num]), &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
                ui1_comp_num++;
            }
            else if (a_nav_ipts_is_vga_source(&t_isl_rec) == TRUE )
            {
                c_memcpy(&t_vga_rec, &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
                ui1_vga_num++;
            }
            else if (a_nav_ipts_is_hdmi_source(&t_isl_rec) == TRUE  && (pt_iterate_rec[ui2_loop].b_conn_amp == FALSE))
            {
                if(ui1_hdmi_num > IPTS_MAX_HDMI_PORT)
                {
                    continue;
                }
                c_memcpy(&(t_hdmi_rec[ui1_hdmi_num]), &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
                ui1_hdmi_num++;
            }
        }
        /* cec device */
        {
            if(pt_iterate_rec[ui2_loop].b_cec_dev == TRUE)
            {
                if(ui1_cec_num > IPTS_MAX_CEC_PORT)
                {
                    continue;
                }
                c_memcpy(&(t_cec_rec[ui1_cec_num]), &(pt_iterate_rec[ui2_loop]), sizeof(IPT_LIST_REC_T));
                DBG_LOG_PRINT(("cxcx %s %d ui1_cec_num:%d ui2_loop:%d\n",__FUNCTION__,__LINE__,ui1_cec_num,ui2_loop));
                t_cec_rec_dev_idx_in_list[ui1_cec_num] = ui2_loop;
                ui1_cec_num++;
            }
        }

    }

    /* add to pt_iterate_rec */
    {
        pt_iterate_rec[0].ui2_num = 0;

        {
            if (ui1_func_num != 0)
            {
                c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num]),
                         &t_func_rec,
                         sizeof(IPT_LIST_REC_T));
                pt_iterate_rec[0].ui2_num += 1;
            }
        }

        {
            if(ui1_cast_num != 0)
            {
                UINT8   ui1_cast_count = 0;
                UINT8   ui1_cast_index = 0;

                /* vitual input */
                for(ui1_cast_index = 0; ui1_cast_index < ui1_cast_num; ui1_cast_index++)
                {
                    if(ui1_cast_index == 0)  /* skip Smartcast to check hide  */
                    {
                        ui1_cast_count++;
                        c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_cast_count - 1]),
                                 &(t_cast_rec[ui1_cast_index]),
                                 sizeof(IPT_LIST_REC_T));
                        if(c_uc_w2s_strncmp(t_cast_rec[ui1_cast_index].w2s_elem_col1_name, L"SMARTCAST", 9) == 0)
                        {
                            ui1_smartcast_count++;
                        }
                        continue;
                    }
                    i4_ret = a_isl_get_rec_by_id(t_cast_rec[ui1_cast_index].t_elem.ui1_id, &t_isl_rec);
                    NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

                    if( nav_ipts_view_input_src_is_hide_src(&t_isl_rec) == TRUE )
                    {
                        continue;
                    }
                    if(c_uc_w2s_strncmp(t_cast_rec[ui1_cast_index].w2s_elem_col1_name, L"SMARTCAST", 9) == 0)
                    {
                        ui1_smartcast_count++;
                        if(ui1_smartcast_count >1)
                        {
                          	DBG_INFO(("%s_%d may some mistake vtrl input,so need ignore ui1_smartcast_count:%d \n",__FUNCTION__,__LINE__,ui1_smartcast_count));
                          	continue;
                        }
                    }



                    ui1_cast_count++;
                    c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_cast_count - 1]),
                               &(t_cast_rec[ui1_cast_index]),
                               sizeof(IPT_LIST_REC_T));
                }

                ui1_cast_num = ui1_cast_count;
                pt_iterate_rec[0].ui2_num += ui1_cast_num;
                //DBG_LOG_PRINT(("<NAV_INPUT> ui1_cast_num: %d \n", ui1_cast_num));
            }
        }

#ifdef ISL_VTRL_INP_SRC_MMP
        {

            UINT8   ui1_usb_count = 0;
            UINT8   ui1_usb_index = 0;

            /* check usb */
            for(ui1_usb_index = 0; ui1_usb_index < 1/* ui1_usb_num */; ui1_usb_index++)
            {
                if(nav_ipts_is_allow_show_usb_src() == FALSE)
                {
                    continue;
                }
                ui1_usb_count++;
                c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_usb_count - 1]),
                         &t_usb_rec,
                         sizeof(IPT_LIST_REC_T));
            }
            ui1_usb_plug = ui1_usb_count;
            pt_iterate_rec[0].ui2_num += ui1_usb_plug;
            //DBG_LOG_PRINT(("<NAV_INPUT> ui1_usb_plug: %d \n", ui1_usb_plug));
        }
#endif

        {
            if(ui1_hdmi_num != 0)
            {
                UINT8   ui1_hdmi_count = 0;
                UINT8   ui1_hdmi_index = 0;

                for(ui1_hdmi_index = 0; ui1_hdmi_index < ui1_hdmi_num; ui1_hdmi_index++)
                {
                    i4_ret = a_isl_get_rec_by_id(t_hdmi_rec[ui1_hdmi_index].t_elem.ui1_id, &t_isl_rec);
                    NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

                    if( nav_ipts_view_input_src_is_hide_src(&t_isl_rec) == TRUE )
                    {
                        continue;
                    }

                    ui1_hdmi_count++;
                    c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_hdmi_count - 1]),
                             &(t_hdmi_rec[ui1_hdmi_index]),
                             sizeof(IPT_LIST_REC_T));
                }

                ui1_hdmi_num = ui1_hdmi_count;
                pt_iterate_rec[0].ui2_num += ui1_hdmi_num;
                //DBG_LOG_PRINT(("<NAV_INPUT> ui1_hdmi_num: %d \n", ui1_hdmi_num));
            }
        }

        /*there will be only one comp, so ui1_comp_num will be 1*/
        if (ui1_comp_num != 0)
        {
            UINT8   ui1_comp_count = 0;
            UINT8   ui1_comp_index = 0;

            if(ui1_comp_num > 1)
            {
                DBG_INFO(("<INPUT SRC LIST>[%s][%d] There's more than one COMP\n", __FUNCTION__, __LINE__));
               // return NAVR_FAIL;
            }

            /* check comp*/
            for(ui1_comp_index = 0; ui1_comp_index < 1 /* ui1_comp_num */; ui1_comp_index++)
            {
                i4_ret = a_isl_get_rec_by_id(t_comp_rec[ui1_comp_index].t_elem.ui1_id, &t_isl_rec);

                NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);
                if( nav_ipts_view_input_src_is_hide_src(&t_isl_rec) == TRUE )
                {
                    continue;
                }
                ui1_comp_count++;
                c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_comp_count - 1]),
                           &t_comp_rec[ui1_comp_index],
                           sizeof(IPT_LIST_REC_T));
            }
            ui1_comp_num = ui1_comp_count;
            pt_iterate_rec[0].ui2_num += ui1_comp_num;
            //DBG_LOG_PRINT(("<NAV_INPUT> ui1_comp_num: %d \n", ui1_comp_num));
        }

        if (ui1_tv_num != 0)
        {
            UINT8   ui1_tv_count = 0;
            UINT8   ui1_tv_index = 0;
            CHAR    ac_arc_name[64 + 1];
            CHAR    ac_arc_name1[64 + 1];

            /* check tv */
            for(ui1_tv_index = 0; ui1_tv_index <  ui1_tv_num ; ui1_tv_index++)
            {
                i4_ret = a_isl_get_rec_by_id(t_tv_rec[ui1_tv_index].t_elem.ui1_id, &t_isl_rec);
                NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

                if( nav_ipts_view_input_src_is_hide_src(&t_isl_rec) == TRUE )
                {
                    continue;
                }
                ui1_tv_count++;
                DBG_LOG_PRINT(("{%s,%d} e_src_type:%d \n",__FUNCTION__,__LINE__,t_tv_rec[ui1_tv_index].e_src_type));
                c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_tv_count - 1]),
                           &t_tv_rec[ui1_tv_index],
                           sizeof(IPT_LIST_REC_T));
                c_uc_w2s_to_ps(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_tv_count - 1].w2s_elem_col1_name, ac_arc_name, 64 + 1);
                c_uc_w2s_to_ps(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_tv_count - 1].w2s_elem_col2_name, ac_arc_name1, 64 + 1);
                DBG_LOG_PRINT(("<NAV INPUT>w2s_elem_col1_name: %s  w2s_elem_col2_name:%s \n",ac_arc_name,ac_arc_name1));
                DBG_LOG_PRINT(("{%s,%d} e_src_type:%d \n",__FUNCTION__,__LINE__,pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_tv_count - 1].e_src_type));
            }
            ui1_tv_num = ui1_tv_count;
            pt_iterate_rec[0].ui2_num += ui1_tv_num;
            if( nav_ipts_view_input_src_is_hide_src(&t_isl_rec) == FALSE )
            {
                if(pt_iterate_rec[pt_iterate_rec[0].ui2_num - 1 ].e_src_type != INP_SRC_TYPE_TV)
                {
                    c_uc_w2s_to_ps(t_tv_rec_backup.w2s_elem_col1_name, ac_arc_name, 64 + 1);
                    c_uc_w2s_to_ps(t_tv_rec_backup.w2s_elem_col2_name, ac_arc_name1, 64 + 1);
                    DBG_LOG_PRINT(("<NAV INPUT>w2s_elem_col1_name: %s  w2s_elem_col2_name:%s \n",ac_arc_name,ac_arc_name1));
                    DBG_LOG_PRINT(("{%s,%d} num:%d \n",__FUNCTION__,__LINE__,pt_iterate_rec[0].ui2_num  - 1));
                    c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num  - 1]),
                       &t_tv_rec_backup,
                       sizeof(IPT_LIST_REC_T));
                    c_uc_w2s_to_ps(pt_iterate_rec[pt_iterate_rec[0].ui2_num  - 1].w2s_elem_col1_name, ac_arc_name, 64 + 1);
                    c_uc_w2s_to_ps(pt_iterate_rec[pt_iterate_rec[0].ui2_num  - 1].w2s_elem_col2_name, ac_arc_name1, 64 + 1);
                    DBG_LOG_PRINT(("<NAV INPUT>w2s_elem_col1_name: %s  w2s_elem_col2_name:%s \n",ac_arc_name,ac_arc_name1));
                    DBG_LOG_PRINT(("<NAV_INPUT> line:%d e_src_type: %d \n",__LINE__, pt_iterate_rec[pt_iterate_rec[0].ui2_num - 1 ].e_src_type));
                    DBG_LOG_PRINT(("<NAV_INPUT> line:%d ui1_id: %d \n", __LINE__,pt_iterate_rec[pt_iterate_rec[0].ui2_num - 1 ].t_elem.ui1_id));
                }
            }
        }

        if (ui1_vga_num != 0)
        {
            UINT8   ui1_vga_count = 0;
            UINT8   ui1_vga_index = 0;

            /* check vga */
            for(ui1_vga_index = 0; ui1_vga_index < ui1_vga_num ; ui1_vga_index++)
            {
                i4_ret = a_isl_get_rec_by_id(t_tv_rec[ui1_vga_index].t_elem.ui1_id, &t_isl_rec);
                NAV_CHK_FAIL(i4_ret == APP_CFGR_OK ? NAVR_OK : i4_ret);

                if( nav_ipts_view_input_src_is_hide_src(&t_isl_rec) == TRUE )
                {
                    continue;
                }
                ui1_vga_count++;
                c_memcpy(&(pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_vga_count - 1]),
                         &t_vga_rec, /* &t_vga_rec[ui1_vga_index] ,*/
                         sizeof(IPT_LIST_REC_T));
            }
            ui1_vga_num = ui1_vga_count;
            pt_iterate_rec[0].ui2_num += ui1_vga_num;
        }

        /*add cec device connected to AMP after we can hide input*/
        if(ui1_cec_num != 0 )
        {
            UINT8   ui1_cec_count = 0;
            UINT8   ui1_cec_index = 0;

            for(ui1_cec_index = 0; ui1_cec_index < ui1_cec_num; ui1_cec_index++)
            {
                if(t_cec_rec[ui1_cec_index].b_conn_amp == FALSE)
                {
                    continue;
                }
                ui1_cec_count++;
                c_memcpy(&pt_iterate_rec[pt_iterate_rec[0].ui2_num + ui1_cec_count - 1],
                         &t_cec_rec[ui1_cec_index],
                         sizeof(IPT_LIST_REC_T));
                DBG_LOG_PRINT(("<NAV_INPUT CXCX> ui1_cec_index:%d ui1_cec_num: %d idx=%d\n",
                    ui1_cec_index,ui1_cec_num,pt_iterate_rec[0].ui2_num + ui1_cec_count - 1));

                #if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
                UINT8 ui1_loop = 0;
                //update at_ipts_cec_dev ui2_dev_index_in_ipts after sort
                for (ui1_loop = 0; ui1_loop < 16; ui1_loop++)
                {
                    //DBG_LOG_PRINT(("<NAV_INPUT> ui1_loop:%d ui2_dev_index_in_ipts:%d ui1_cec_index:%d\n",ui1_loop,at_ipts_cec_dev[ui1_loop].ui2_dev_index_in_ipts,t_cec_rec_dev_idx_in_list[ui1_cec_index]));
                    if(at_ipts_cec_dev[ui1_loop].ui2_dev_index_in_ipts == t_cec_rec_dev_idx_in_list[ui1_cec_index])
                    {
                        at_ipts_cec_dev[ui1_loop].ui2_dev_index_in_ipts = (pt_iterate_rec[0].ui2_num + ui1_cec_count - 1);
                        //DBG_LOG_PRINT(("<NAV_INPUT> ui2_dev_index_in_ipts:%d ui1_loop:%d\n",at_ipts_cec_dev[ui1_loop].ui2_dev_index_in_ipts,ui1_loop));
                    }
                }
                #endif
            }
            ui1_cec_num = ui1_cec_count;

            pt_iterate_rec[0].ui2_num += ui1_cec_num;

        }
    }

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} -- end\n", __FUNCTION__, __LINE__ )); );

    return NAVR_OK;
}

static INT32 _nav_ipts_lst_elem_sort_pwrdwn(
    TV_WIN_ID_T                         e_grp,
    IPT_LIST_REC_T*                     pt_isl_rec)
{
    ISL_REC_T       t_isl_rec = {0};
    INT32           i4_ret = NAVR_OK;
    UINT8           ui1_crn_src_elem = 0xFF;
    UINT8           ui1_pwr_elem = 0xFF;
    UINT8           ui1_loop = 0;
    UINT8           ui1_elem_src_idx = 0;
    UINT8           ui1_elem_dst_idx = 0;
    UINT8           ui1_elem_num = 0;

    IPT_LIST_REC_T  *pt_rec = NULL;

    IPT_LIST_REC_T   t_pwr_rec;
    c_memset(&t_pwr_rec, 0, sizeof(t_pwr_rec));

    if (NULL == pt_isl_rec)
    {
        return NAVR_FAIL;
    }

    ui1_elem_num = pt_isl_rec[0].ui2_num;

    /* view find first elem */
    {
        i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_isl_rec);
        if(TVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): a_tv_get_isl_rec_by_win_id(%d) failed. i4_ret = %d\r\n", __FUNCTION__, e_grp, i4_ret));
            return NAVR_FAIL;
        }

        pt_rec = (IPT_LIST_REC_T*)&pt_isl_rec[0];
        for (ui1_loop = 0; ui1_loop < ui1_elem_num; ui1_loop++)
        {
            /* Get the first elem */
            if (t_isl_rec.ui1_id == pt_rec->t_elem.ui1_id)
            {
                DBG_INFO(("[isl_func] %s %d, ui1_crn_src_elem[%d]\n",__FUNCTION__,__LINE__, ui1_loop));
                ui1_crn_src_elem = ui1_loop;
            }

            /* Get pwr off elem*/
            if (pt_rec->t_elem.e_func_type == E_FUNC_ELEMENT_POWER_OFF)
            {
                ISL_LOG(_ISL_LOG_TYPE_FUNC,("%s(%d) ui1_pwr_elem[%d] \n", __FUNCTION__, __LINE__,ui1_loop));
                c_memcpy(&t_pwr_rec, &pt_isl_rec[ui1_loop], sizeof(IPT_LIST_REC_T));
                ui1_pwr_elem = ui1_loop;
            }

            pt_rec++;
        }

        if(ui1_crn_src_elem == 0xFF || ui1_pwr_elem == 0xFF)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): ui1_crn_src_elem(%d) ui1_pwr_elem(%d) failed. \r\n", __FUNCTION__, ui1_crn_src_elem, ui1_pwr_elem));
            return NAVR_FAIL;
        }
    }

    #if 0 //for debug
    DBG_LOG_PRINT(("[isl_func] nav_ipts_lst_print_elems after collect before resort -----------------\n"));
    UINT8 ui1_loop_print = 0;
    DBG_LOG_PRINT(("%s(): max_elems = %d\n", __FUNCTION__, ui1_elem_num));
    DBG_LOG_PRINT(("%s(): ===================================================\n", __FUNCTION__));
    DBG_LOG_PRINT(("Print Input list Info:\n\t idx\t id\t disabled\t e_func_type\n"));

    for (ui1_loop_print = 0; ui1_loop_print < ui1_elem_num; ui1_loop_print++)
    {
        DBG_LOG_PRINT(("pt_ipt_list_rec->at_elem[%d] = [%d, %d, %d, %d]\n",
                        ui1_loop_print,
                        pt_isl_rec[ui1_loop_print].t_elem.i2_idx,
                        pt_isl_rec[ui1_loop_print].t_elem.ui1_id,
                        pt_isl_rec[ui1_loop_print].t_elem.b_is_disabled,
                        pt_isl_rec[ui1_loop_print].t_elem.e_func_type));
    }
    #endif

    /* Shift the pwr off item to next to current src  */
    //e.g. current src is HDMI1
    // src isl: PowerOff, TV, comp, HDMI1, HDMI2...
    // dst isl: TV, comp, HDMI1, PowerOff, HDMI2...
    {
        for (ui1_loop = 0; ui1_loop < ui1_elem_num; ui1_loop++)
        {
            //copy elem from idx[pwr_elem+1] to idx[pwr_elem] until meet idx[crn_src_elem]

            ui1_elem_dst_idx = ui1_loop + ui1_pwr_elem;
            ui1_elem_src_idx = ui1_elem_dst_idx + 1;

            if(ui1_elem_src_idx >= ui1_elem_num)
            {
                ui1_elem_src_idx -= ui1_elem_num;
            }

            if(ui1_elem_dst_idx >= ui1_elem_num)
            {
                ui1_elem_dst_idx -= ui1_elem_num;
            }

            // if the src_elem is current src, no need to do next shift step, to keep pwr_elem on the right of crn_src_elem
            if(ui1_elem_dst_idx == ui1_crn_src_elem)
            {
                c_memcpy(&pt_isl_rec[ui1_elem_dst_idx], &(t_pwr_rec), sizeof(IPT_LIST_REC_T));
                break;
            }

            c_memcpy(&pt_isl_rec[ui1_elem_dst_idx], &(pt_isl_rec[ui1_elem_src_idx]), sizeof(IPT_LIST_REC_T));
        }
    }

    pt_isl_rec[0].ui2_num = ui1_elem_num;

    #if 0 // for debug
    DBG_LOG_PRINT(("[isl_func] nav_ipts_lst_print_elems after collect after resort -----------------\n"));
    DBG_LOG_PRINT(("%s(): max_elems = %d\n", __FUNCTION__, pt_isl_rec[0].ui2_num));
    DBG_LOG_PRINT(("%s(): ===================================================\n", __FUNCTION__));
    DBG_LOG_PRINT(("Print Input list Info:\n\t idx\t id\t disabled\t e_func_type\n"));

    for (ui1_loop_print = 0; ui1_loop_print < pt_isl_rec[0].ui2_num; ui1_loop_print++)
    {
        DBG_LOG_PRINT(("pt_ipt_list_rec->at_elem[%d] = [%d, %d, %d, %d]\n",
                        ui1_loop_print,
                        pt_isl_rec[ui1_loop_print].t_elem.i2_idx,
                        pt_isl_rec[ui1_loop_print].t_elem.ui1_id,
                        pt_isl_rec[ui1_loop_print].t_elem.b_is_disabled,
                        pt_isl_rec[ui1_loop_print].t_elem.e_func_type));
    }
    #endif

    return NAVR_OK;

}


// Power Off item in input list
// Support: For all 2021 skus except V5
BOOL _nav_ipts_lst_pwrdwn_check_sku_default_enable(VOID)
{
    BOOL bEnable = FALSE;

    if(a_cfg_cust_Is_CurModel_after_2021_J())
    {
        EnuCusModelSeries enModel = a_cfg_cust_get_CurModelSeries();
        if(enModel == CUS_MODEL_2021_91_V5)
        {
            bEnable = FALSE;
        }
        else
        {
            bEnable = TRUE;
        }
    }

    return bEnable;
}

#if(/*!NAV_INPUT_SRC_UI_VERTICAL*/1)
static INT32 _nav_ipts_lst_update_toast_list_text(
    _NAV_IPTS_LIST_MEMBER_T*            pt_this,
    TV_WIN_ID_T                         e_grp,
    BOOL                                b_force)
{
    /* Step2 update toast list text */
    INT32           i4_ret = NAVR_OK;
    UINT8           i = 0;
    UINT8           ui1_loop = 0;
    ISL_REC_T       t_isl_rec = {0};
    IPT_LIST_REC_T  *pt_rec = NULL;
    UINT8           ui1_head = 0;
    static UINT8    ui1_rec_sum = 0xff;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    if (NULL == pt_this)
    {
        return NAVR_FAIL;
    }

    /* view find first elem */
    {
        i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_isl_rec);
        if(TVR_OK != i4_ret)
        {
            DBG_ERROR((_ERROR_HEADER"%s(): a_tv_get_isl_rec_by_win_id(%d) failed. i4_ret = %d\r\n", __FUNCTION__, e_grp, i4_ret));
            return NAVR_FAIL;
        }

        pt_rec = (IPT_LIST_REC_T*)&pt_ipt_list_rec[0];

        do{

#ifdef APP_WFD_SUPPORT
            if (a_cfg_custom_get_wfd_support() == TRUE
                && a_wfd_is_rtsp_play_status() == TRUE)
            {
                ui1_head = 0;
                break;
            }
#endif
#if(!NAV_INPUT_SRC_UI_VERTICAL)

            pt_rec = (IPT_LIST_REC_T*)&pt_ipt_list_rec[0];
            for (ui1_loop = 0; ui1_loop < pt_ipt_list_rec[0].ui2_num; ui1_loop++)
            {
                /* Get the first elem */
                if (t_isl_rec.ui1_id == pt_rec->t_elem.ui1_id)
                {
                    ui1_head = ui1_loop;
                    break;
                }

                pt_rec++;
            }
#endif

        }while(0);
    }

    {
        i = 0;
        ui1_loop = ui1_head;
        c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));

        t_g_toast_param.w2s_msg_t.i4_str_num = 0;

        t_g_toast_param.w2s_str = MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_NAV_CHANGE_INPUT);
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} w2s_str:%s \n",
            __FUNCTION__, __LINE__, menu_custom_get_char_string(t_g_toast_param.w2s_str)  )); );

        t_g_toast_param.w2s_help_str = MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_NAV_ISL_POWER_OFF_HELP_TEXT);
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} w2s_help_str:%s \n",
            __FUNCTION__, __LINE__, menu_custom_get_char_string(t_g_toast_param.w2s_help_str)  )); );


        do {
            //NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, i:%d\n",
            //    __FUNCTION__, __LINE__, ui1_loop, i )); );

            pt_rec = (IPT_LIST_REC_T*)&pt_ipt_list_rec[ui1_loop];

            if (c_uc_w2s_strlen(pt_rec->w2s_elem_col1_name) !=0 )
            {
                t_g_toast_param.w2s_msg_t.w2s_str[i] = pt_rec->w2s_elem_col1_name;
                NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, i:%d, w2s_elem_col1_name:%s\n",
                    __FUNCTION__, __LINE__, ui1_loop, i, menu_custom_get_char_string(pt_rec->w2s_elem_col1_name) )); );
            }
            else if (c_uc_w2s_strlen(pt_rec->w2s_elem_col2_name) !=0 )
            {
                t_g_toast_param.w2s_msg_t.w2s_str[i] = pt_rec->w2s_elem_col2_name;
                NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, i:%d, w2s_elem_col2_name:%s\n",
                    __FUNCTION__, __LINE__, ui1_loop, i, menu_custom_get_char_string(pt_rec->w2s_elem_col2_name) )); );
            }

            if (INP_SRC_TYPE_TV == pt_rec->e_src_type)
            {
                c_memset(pt_rec->w2s_elem_col2_name, 0, sizeof(pt_rec->w2s_elem_col2_name));

                if (c_uc_w2s_strlen(pt_rec->w2s_ch_no) != 0)
                {
                    c_uc_w2s_strcpy(pt_rec->w2s_elem_col2_name, pt_rec->w2s_ch_no);
                    c_uc_w2s_strcat(pt_rec->w2s_elem_col2_name, L" ");
                }

                if (c_uc_w2s_strlen(pt_rec->w2s_ch_name) != 0)
                {
                    c_uc_w2s_strcat(pt_rec->w2s_elem_col2_name, pt_rec->w2s_ch_name);
                }

                t_g_toast_param.w2s_msg_t.w2s_str[i] = pt_rec->w2s_elem_col2_name;
                if (c_uc_w2s_strlen(t_g_toast_param.w2s_msg_t.w2s_str[i]) > 0)
                {
                    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, i:%d, t_g_toast_param.w2s_msg_t.w2s_str[i]:%s\n",
                        __FUNCTION__, __LINE__, ui1_loop, i, menu_custom_get_char_string(t_g_toast_param.w2s_msg_t.w2s_str[i]) )); );
                }
                if (c_uc_w2s_strlen(t_g_toast_param.w2s_msg_t.w2s_str[i]) == 0)
                {
                    t_g_toast_param.w2s_msg_t.w2s_str[i] = pt_rec->w2s_elem_col1_name;
                    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, i:%d, t_g_toast_param.w2s_msg_t.w2s_str[i]:%s\n",
                        __FUNCTION__, __LINE__, ui1_loop, i, menu_custom_get_char_string(t_g_toast_param.w2s_msg_t.w2s_str[i]) )); );
                }

            }

            t_g_toast_param.w2s_msg_t.i4_str_num++;

            i++;
            ui1_loop++;
            ui1_loop = ui1_loop % pt_ipt_list_rec[0].ui2_num;
        }while(ui1_head !=  ui1_loop);

        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_ipt_list_rec[0].ui2_num:%d, t_g_toast_param.w2s_msg_t.i4_str_num:%d\n",
            __FUNCTION__, __LINE__, pt_ipt_list_rec[0].ui2_num, t_g_toast_param.w2s_msg_t.i4_str_num )); );


        if (ui1_rec_sum != i)
        {
            ui1_rec_sum = i;
        #if(NAV_INPUT_SRC_UI_USE_WDK)
            nav_ipts_new_lst_text_create(pt_this);
        #endif
        }
    }

    return i4_ret;

}
#endif

static INT32 _nav_ipts_lst_update_elems(
    _NAV_IPTS_LIST_MEMBER_T*            pt_this,
    TV_WIN_ID_T                         e_grp,
    BOOL                                b_force)
{
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this:0x%X\n", __FUNCTION__, __LINE__, (UINT32)pt_this )); );

    return _nav_ipts_lst_update_elems_ex(pt_this,e_grp,b_force);
}

static INT32 _ipt_list_rec_collect(_NAV_IPTS_LIST_MEMBER_T* pt_this,
                                       TV_WIN_ID_T e_grp,
                                       IPT_LIST_REC_T* pt_ipt_list_rec)
{
    ISL_REC_T                           t_isl_active = {0};
    ISL_REC_T                           t_isl_other = {0};
    ISL_REC_T                           t_isl_iterate = {0};
    WGL_LB_ITEM_IMG_SUIT_T              t_item_img_disable = {0} , t_item_img_normal = {0};
    TV_MODE_T                           e_tv_mode;
    INT32                               i4_ret;
    UINT32                              i;
    ACFG_RETAIL_MODE_T                  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    //CHAR                                ps_tmp[64]  = {0} ;
    CHAR                                s_ch_name[CH_NAME_MAX_LENGTH + 1] = {0} ;
    SVL_REC_T                           t_svl_rec = {0} ;
    HANDLE_T                            h_alias_name_icon = NULL_HANDLE;
    BOOL                                b_svl_empty = FALSE;
    HDMI_SORTING_REC_T                  at_hdmi_sorting[4];
    UINT8                               ui1_check_loop;
    UINT8                               ui1_isl_num = 0;
    UINT8                               ui1_loop;


    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} -- start\n", __FUNCTION__, __LINE__ )); );


    /* Image for disable items*/
    if(pt_this->b_show_disabled)
    {
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} pt_this->b_show_disabled is true\n", __FUNCTION__, __LINE__ )); );
        t_item_img_disable.h_normal = pt_this->h_disable_img;
        t_item_img_disable.h_disable = pt_this->h_disable_img;
        t_item_img_disable.h_highlight = pt_this->h_disable_ht_img;
        t_item_img_disable.h_highlight_unfocus = pt_this->h_disable_ht_img;
        t_item_img_disable.h_selected_highlight = pt_this->h_disable_ht_img;
        t_item_img_disable.h_selected_highlight_unfocus = pt_this->h_disable_ht_img;
        t_item_img_disable.h_selected = pt_this->h_disable_img;
        t_item_img_disable.h_selected_disable = pt_this->h_disable_img;
        t_item_img_disable.h_pushed = pt_this->h_disable_img;
        t_item_img_disable.h_selected_pushed = pt_this->h_disable_img;
    }

    /* Image for normal items image */
    if(pt_this->b_show_active)
    {
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} pt_this->b_show_active is true\n", __FUNCTION__, __LINE__ )); );
        t_item_img_normal.h_normal = NULL_HANDLE;
        t_item_img_normal.h_disable = NULL_HANDLE;
        t_item_img_normal.h_highlight = NULL_HANDLE;
        t_item_img_normal.h_highlight_unfocus = NULL_HANDLE;
        t_item_img_normal.h_selected_highlight = pt_this->h_active_ht_img;
        t_item_img_disable.h_selected_highlight_unfocus = pt_this->h_active_ht_img;
        t_item_img_normal.h_selected = pt_this->h_active_img;
        t_item_img_normal.h_selected_disable = pt_this->h_active_img;
        t_item_img_normal.h_pushed = pt_this->h_active_img;
        t_item_img_disable.h_selected_pushed = pt_this->h_active_img;
    }

    c_memset(at_hdmi_sorting, 0, sizeof(HDMI_SORTING_REC_T)*4);

    /* reset at_elem?? */
    for (ui1_loop = 0; ui1_loop < NAV_IPTS_LST_BOX_ELEM_COUNT; ui1_loop++)
    {
        pt_this->at_elem[ui1_loop].b_is_disabled = TRUE;
        pt_this->at_elem[ui1_loop].i2_idx = 0;
        pt_this->at_elem[ui1_loop].ui1_id = 0xFF;
        pt_this->at_elem[ui1_loop].e_func_type = E_FUNC_ELEMENT_NULL;
    }

    i = 0;

    /* ================= Add WFD ================= */
#ifdef APP_WFD_SUPPORT
    {

        if (a_cfg_custom_get_wfd_support() == TRUE
            && a_wfd_is_rtsp_play_status() == TRUE)
        {
            /* 1.update e_src_type e_video_type */
            {
                pt_ipt_list_rec[i].e_src_type   = INP_SRC_TYPE_UNKNOWN;
                pt_ipt_list_rec[i].e_video_type = DEV_UNKNOWN;
            }
            /* 2.update h_img h_img_hlt */
            {
                pt_ipt_list_rec[i].h_img = h_g_nav_banner_new_input_via_img;
                pt_ipt_list_rec[i].h_img_hlt = h_g_nav_banner_new_input_via_img;
            }
            /* 3.update t_item_img_disable t_item_img_normal */
            {
                pt_ipt_list_rec[i].t_item_img_normal = t_item_img_normal;
                pt_ipt_list_rec[i].t_item_img_disable = t_item_img_disable;
                //NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} pt_ipt_list_rec[%d].t_item_img_normal=0x%X\n",
                  //      __FUNCTION__, __LINE__, i, pt_ipt_list_rec[i].t_item_img_normal )); );
            }
            /* 4.update w2s_ch_name w2s_ch_no */
            /* NULL should set 0 */
            /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
            {
                UTF16_T                             w2s_device_name[DEVICE_INFO_ARR_LEN + 1];

                //h_elem_col0_img = NULL_HANDLE;
                w2s_device_name[DEVICE_INFO_ARR_LEN] = 0;
                i4_ret = a_wfd_get_device_name(w2s_device_name);
                NAV_LOG_ON_FAIL(WGLR_OK == i4_ret ? NAVR_OK : i4_ret);
                c_uc_w2s_strcpy(pt_ipt_list_rec[i].w2s_elem_col1_name, w2s_device_name);
            #if 1//(NAV_INPUT_SRC_UI_HAS_ALIAS)
                c_uc_w2s_strcpy(pt_ipt_list_rec[i].w2s_elem_col2_name, L" ");
            #endif
            }
            /* 6.t_elem */
            {
                pt_ipt_list_rec[i].t_elem.b_is_disabled = FALSE;
                pt_ipt_list_rec[i].t_elem.i2_idx = i;
                pt_ipt_list_rec[i].t_elem.ui1_id = -1;
            }
            /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
            {
                //ui2_num ??
                pt_ipt_list_rec[i].b_cec_dev = FALSE;
                pt_ipt_list_rec[i].b_conn_amp = FALSE;
            }
            i++;
        }
    }
#endif

    /* ================= Add ISL ================= */
    {
        /*get tv mode*/
        i4_ret = a_tv_get_mode(&e_tv_mode);
        NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);

        /*get active group*/
        i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_isl_active);
        NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);

        /*get other group*/
        if(TV_MODE_TYPE_NORMAL != e_tv_mode)
        {
            i4_ret = a_tv_get_isl_rec_by_win_id((TV_WIN_ID_MAIN == e_grp) ? TV_WIN_ID_SUB : TV_WIN_ID_MAIN,
                                                &t_isl_other);
            NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);
        }

        {
            i4_ret = a_isl_get_num_rec(&ui1_isl_num);
            NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);
        }
        NAV_DEBUG_INPUT_SRC_REC_COLLECT(
            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_isl_num:%d \n", __FUNCTION__, __LINE__,
                 ui1_isl_num )); );

        for (ui1_loop = 0; ui1_loop < ui1_isl_num; ui1_loop++)
        {
            NAV_DEBUG_INPUT_SRC_REC_COLLECT(
                DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ---------- ui1_loop:%d -------------------------------------------- \n",
                    __FUNCTION__, __LINE__, ui1_loop )); );

            /* pt_isl_rec -> pt_ipt_list_rec */
            {
                i4_ret = a_isl_get_rec_by_idx(ui1_loop, &t_isl_iterate);
                NAV_CHK_FAIL(ISLR_OK == i4_ret ? NAVR_OK : i4_ret);

                BOOL bIsSrcHDMI = FALSE;
                if( (t_isl_iterate.e_src_type == INP_SRC_TYPE_AV)
                  &&(t_isl_iterate.t_avc_info.e_video_type == DEV_AVC_HDMI)
                  )
                {
                    bIsSrcHDMI = TRUE;
                }
                NAV_DEBUG_INPUT_SRC_REC_COLLECT(
                    DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, .ui1_id=%d, e_src_type:%d .ui1_internal_id:%d, t_avc_info.e_video_type:0x%X, bIsSrcHDMI:%d\n", __FUNCTION__, __LINE__,
                        ui1_loop, t_isl_iterate.ui1_id, t_isl_iterate.e_src_type,
                        t_isl_iterate.ui1_internal_id, t_isl_iterate.t_avc_info.e_video_type, bIsSrcHDMI )); );

                pt_ipt_list_rec[i+ui1_loop].t_elem.ui1_id = t_isl_iterate.ui1_id;

                NAV_DEBUG_INPUT_SRC_REC_COLLECT(
                    DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, pt_ipt_list_rec[%d].t_elem.ui1_id=%d \n", __FUNCTION__, __LINE__,
                        ui1_loop, i+ui1_loop, pt_ipt_list_rec[i+ui1_loop].t_elem.ui1_id )); );

                {
                    if(TV_MODE_TYPE_NORMAL != e_tv_mode)
                    {
                        pt_ipt_list_rec[i+ui1_loop].t_elem.b_is_disabled = !_nav_ipts_lst_is_able_to_pip_pop (&t_isl_other, &t_isl_iterate);
                    }
                    else
                    {
                        pt_ipt_list_rec[i+ui1_loop].t_elem.b_is_disabled \
                        = ((t_isl_iterate.ui4_attr_bits & ISL_ATTR_BIT_SKIPPED) == ISL_ATTR_BIT_SKIPPED) ? TRUE : FALSE;
                    }

                    if((TRUE == pt_ipt_list_rec[i+ui1_loop].t_elem.b_is_disabled) && (FALSE == pt_this->b_show_disabled))
                    {
                        continue;
                    }
                }


                {
                    UTF16_T         w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
                    UTF16_T         w2s_device_type[32];
                    UTF16_T*        w2s_name;

                    c_memset (w2s_alias, 0, sizeof(w2s_alias));
                    c_memset (w2s_device_type, 0, sizeof(w2s_device_type));

                    /*icon*/
                    pt_ipt_list_rec[i+ui1_loop].t_item_img_disable = t_item_img_disable;
                    pt_ipt_list_rec[i+ui1_loop].t_item_img_normal= t_item_img_normal;

                    /* elem name */
                    {
                        {
                            w2s_name = a_isl_get_display_name(&t_isl_iterate);
                        }

                        {
                            CHAR    ac_device_type[32];
                            c_memset (ac_device_type, 0, sizeof(ac_device_type));
                            a_cfg_custom_get_device_type(ui1_loop,ac_device_type);
                            c_uc_ps_to_w2s(ac_device_type, w2s_device_type, 31);
                        }

                        {
                            a_isl_get_display_name_ex(&t_isl_iterate, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);
                            w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN] = 0;

                            /*SPEC v3.4 if name longer than 16, display ... instead of the actual name*/
                            //if(c_uc_w2s_strlen(w2s_alias) > 16)
                            //{
                            //    w2s_alias[16] = '\0';

                            //    c_uc_w2s_strncat(w2s_alias, L"...", 3);
                            //}
                        }

                        NAV_DEBUG_INPUT_SRC_REC_COLLECT(
                            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, w2s_name:[%s], w2s_alias:[%s]\n", __FUNCTION__, __LINE__,
                                ui1_loop, nav_cust_get_char_string(w2s_name), nav_cust_get_char_string(w2s_alias)  ));
                        );


                        /* if((a_nav_ipts_is_tv_source(&t_isl_iterate) == TRUE) && (FALSE == b_svl_empty))
                        {
                            c_uc_w2s_strcpy(pt_ipt_list_rec[i+ui1_loop].w2s_elem_col1_name, L" ");
                        }
                        else */
                        {
                            if( c_uc_w2s_strlen(w2s_alias) > 0)
                            {
                                c_uc_w2s_strncpy(pt_ipt_list_rec[i+ui1_loop].w2s_elem_col1_name, w2s_alias, 31);
                            }
                            else
                            {
                                c_uc_w2s_strncpy(pt_ipt_list_rec[i+ui1_loop].w2s_elem_col1_name, w2s_name, 31);
                            }
                        }

                        //NAV_DEBUG_INPUT_SRC_REC_COLLECT(
                            DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, pt_ipt_list_rec[%d].w2s_elem_col1_name:[%s]\n", __FUNCTION__, __LINE__,
                                ui1_loop, i+ui1_loop, nav_cust_get_char_string(pt_ipt_list_rec[i+ui1_loop].w2s_elem_col1_name)  ));
                        //);
                    }


                    if( a_nav_ipts_is_tv_source(&t_isl_iterate) == TRUE )
                    {
                        // Get TV channel no/name
                        CHAR ac_ch_no[64] = {0};

                        //if(a_nav_ipts_is_tv_source(&t_isl_iterate) == TRUE)
                        {
                            BOOL    b_found = FALSE;

                            i4_ret = nav_get_crnt_svl_rec(&t_svl_rec, &b_found);
                            NAV_CHK_FAIL(i4_ret);

                            nav_set_ch_num_and_name (&t_svl_rec, ac_ch_no, s_ch_name) ;

                            if( 0 == c_strlen(ac_ch_no) )
                            {
                                b_svl_empty = TRUE;
                                NAV_DEBUG_INPUT_SRC_REC_COLLECT(
                                    DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, TV channel empty\n", __FUNCTION__, __LINE__,
                                        ui1_loop ));
                                );
                            }
                            else
                            {
                                NAV_DEBUG_INPUT_SRC_REC_COLLECT(
                                    DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, ac_ch_no:[%s], s_ch_name:[%s]\n", __FUNCTION__, __LINE__,
                                        ui1_loop, ac_ch_no, s_ch_name ));
                                );
                            }
                        }

                        /* 1.update e_src_type e_video_type */
                        pt_ipt_list_rec[i+ui1_loop].e_src_type = INP_SRC_TYPE_TV;
                        pt_ipt_list_rec[i+ui1_loop].e_video_type = DEV_UNKNOWN;


                        /* 2.update h_img h_img_hlt */
                        if(c_strlen(s_ch_name) > 0 || b_svl_empty == FALSE)
                        {
                            pt_ipt_list_rec[i+ui1_loop].h_img = NULL_HANDLE;
                            pt_ipt_list_rec[i+ui1_loop].h_img_hlt = NULL_HANDLE;
                        }
                        else
                        {
                            pt_ipt_list_rec[i+ui1_loop].h_img = h_g_nav_banner_new_input_tuner_img;
                            pt_ipt_list_rec[i+ui1_loop].h_img_hlt = h_g_nav_banner_new_input_tuner_img;
                        }

                        //Update channel number
                        NAV_ASSERT (c_strlen(ac_ch_no) < (sizeof(ac_ch_no)-1) ) ;
                        BANNER_CHK_FAIL ( (c_strlen(ac_ch_no) < (sizeof(ac_ch_no)-1) ) ? NAVR_OK : NAVR_FAIL) ;

                        if( b_svl_empty )
                        {
                            c_uc_w2s_strcpy( pt_ipt_list_rec[i+ui1_loop].w2s_ch_no, L"" ) ;
                            pt_ipt_list_rec[i+ui1_loop].b_tv_channel_valid = FALSE;
                        }
                        else
                        {
                            c_uc_ps_to_w2s( ac_ch_no, pt_ipt_list_rec[i+ui1_loop].w2s_ch_no, 63 );
                            pt_ipt_list_rec[i+ui1_loop].b_tv_channel_valid = TRUE;
                        }

                        /* 3.update t_item_img_disable t_item_img_normal */

                        /* 4.update w2s_ch_name w2s_ch_no */
                        {
                            if(c_strlen(s_ch_name) > 0)
                            {
                                c_uc_ps_to_w2s(s_ch_name, pt_ipt_list_rec[i+ui1_loop].w2s_ch_name, c_strlen(s_ch_name));
                            }
                            else
                            {
                                if(b_svl_empty)
                                {
                                    pt_ipt_list_rec[i+ui1_loop].w2s_ch_name[0] = 0x0;
                                }
                                else
                                {
                                    UINT8 ui1_brdcst_src;
                                    UTF16_T *pw2s_text = NULL;

                                    a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_brdcst_src);
                                    switch (ui1_brdcst_src)
                                    {
                                    case APP_CFG_BS_SRC_AIR:
                                        pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_IN_SRC_AIR);
                                        break ;
                                    case APP_CFG_BS_SRC_CABLE:
                                        pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_IN_SRC_CABLE);
                                        break ;
                                    default :
                                        pw2s_text = BANNER_TEXT("unknown");
                                        break ;
                                    }
                                #if(NAV_INPUT_SRC_UI_HAS_TV_CH_NUM_NAME_TEXT)
                                    ipts_config_text_utf16(h_inp_tv_ch_name_text,
                                                    NAV_IPTS_CH_NAME_FONT,
                                                    NAV_IPTS_CH_NAME_FONT_SIZE,
                                                    pw2s_text);
                                #endif
                                    c_uc_w2s_strcpy(pt_ipt_list_rec[i+ui1_loop].w2s_ch_name, pw2s_text);
                                }
                            }

                            //Update channel number
                            //NAV_ASSERT (c_strlen(ps_tmp) < sizeof(ps_tmp) -1 ) ;
                            //BANNER_CHK_FAIL ( (c_strlen(ps_tmp) < sizeof(ps_tmp) -1 ) ? NAVR_OK : NAVR_FAIL) ;
                            //c_uc_ps_to_w2s (ps_tmp, pt_ipt_list_rec[i+ui1_loop].w2s_ch_no, c_strlen(ps_tmp)) ;

                        #if(NAV_INPUT_SRC_UI_VERTICAL)
                            if( !b_svl_empty )
                            {
                                // Overwrite col1 for UI display...
                                //c_memset(pt_rec->w2s_elem_col2_name, 0, sizeof(pt_rec->w2s_elem_col2_name));
                                IPT_LIST_REC_T* pt_IPT_LIST_REC = (IPT_LIST_REC_T*)&(pt_ipt_list_rec[i+ui1_loop]);

                                if( c_uc_w2s_strlen(pt_IPT_LIST_REC->w2s_ch_no) > 0 )
                                {
                                    c_uc_w2s_strncpy(pt_IPT_LIST_REC->w2s_elem_col1_name, pt_IPT_LIST_REC->w2s_ch_no, 31);
                                    c_uc_w2s_strcat(pt_IPT_LIST_REC->w2s_elem_col1_name, L" ");
                                }
                                if (c_uc_w2s_strlen(pt_IPT_LIST_REC->w2s_ch_name) > 0)
                                {
                                    c_uc_w2s_strncat(pt_IPT_LIST_REC->w2s_elem_col1_name, pt_IPT_LIST_REC->w2s_ch_name, 31);
                                }
                                DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, TV.w2s_elem_col1_name:[%s]\n", __FUNCTION__, __LINE__,
                                    ui1_loop, nav_cust_get_char_string(pt_IPT_LIST_REC->w2s_elem_col1_name)  ));
                            }
                        #endif

                        }

                        /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
                        /* 6.t_elem */
                        /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
                        {
                            pt_ipt_list_rec[i+ui1_loop].b_cec_dev = FALSE;
                            pt_ipt_list_rec[i+ui1_loop].b_conn_amp = FALSE;
                        }
                        /*backup the tv record for tv will some unknow reason the tv data will be miss*/
                        {
                            CHAR    ac_arc_name[64 + 1];
                            CHAR    ac_arc_name1[64 + 1];
                            c_memset(&t_tv_rec_backup, 0, sizeof(t_tv_rec_backup));
                            c_memcpy(&(t_tv_rec_backup), &(pt_ipt_list_rec[i+ui1_loop]), sizeof(IPT_LIST_REC_T));
                            DBG_INFO(("%s_%d e_src_type:%d \n",__FUNCTION__,__LINE__,t_tv_rec_backup.e_src_type));
                            DBG_INFO(("%s_%d ui1_id:%d \n",__FUNCTION__,__LINE__,t_tv_rec_backup.t_elem.ui1_id));
                            c_uc_w2s_to_ps(t_tv_rec_backup.w2s_elem_col1_name, ac_arc_name, 64 + 1);
                            c_uc_w2s_to_ps(t_tv_rec_backup.w2s_elem_col2_name, ac_arc_name1, 64 + 1);
                            DBG_INFO(("<INPUT SRC LIST> w2s_elem_col1_name:{%s}, w2s_elem_col2_name:{%s} \n",ac_arc_name,ac_arc_name1));
                        }
                    }
                    else if(a_nav_ipts_is_hdmi_source(&t_isl_iterate) == TRUE
                        || a_nav_ipts_is_div_source(&t_isl_iterate) == TRUE)
                    {
                        if( (c_uc_w2s_strlen(w2s_alias) > 0) || (c_uc_w2s_strlen(w2s_device_type) > 0))
                        {
                           h_alias_name_icon = nav_ipts_get_alias_icon(ui1_loop,1);
                        }
                        else
                        {
                           h_alias_name_icon = NULL_HANDLE;
                        }

                        /* 1.update e_src_type e_video_type */
                        {
                            pt_ipt_list_rec[i+ui1_loop].e_src_type = INP_SRC_TYPE_AV;
                            pt_ipt_list_rec[i+ui1_loop].e_video_type = DEV_AVC_HDMI;
                        }

                        /* 2.update h_img h_img_hlt */
                        {
                            if(NULL_HANDLE == h_alias_name_icon)
                            {
                                pt_ipt_list_rec[i+ui1_loop].h_img = h_g_nav_banner_new_input_hdmi_lt_img;
                                pt_ipt_list_rec[i+ui1_loop].h_img_hlt = h_g_nav_banner_new_input_hdmi_lt_img;
                            }
                            else
                            {
                                pt_ipt_list_rec[i+ui1_loop].h_img = h_alias_name_icon;
                                pt_ipt_list_rec[i+ui1_loop].h_img_hlt = h_alias_name_icon;
                            }
                        }

                        /* 3.update t_item_img_disable t_item_img_normal */
                        /* 4.update w2s_ch_name w2s_ch_no */
                        /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
                        /* 6.t_elem */
                        /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
                        {
                            pt_ipt_list_rec[i+ui1_loop].b_cec_dev = FALSE;
                            pt_ipt_list_rec[i+ui1_loop].b_conn_amp = FALSE;
                        }

                        /* at_hdmi_sorting */
                        for(ui1_check_loop = 0;ui1_check_loop < 4;ui1_check_loop++)
                        {
                            if(0 == at_hdmi_sorting[ui1_check_loop].at_elem)
                            {
                                at_hdmi_sorting[ui1_check_loop].ui4_show_count = t_isl_iterate.ui1_id;
                                at_hdmi_sorting[ui1_check_loop].at_elem = i+ui1_loop;
                                break;
                            }
                        }
                    }
                    else if(a_nav_ipts_is_comp_source(&t_isl_iterate) == TRUE)
                    {
                        if( (c_uc_w2s_strlen(w2s_alias) > 0) || (c_uc_w2s_strlen(w2s_device_type) > 0))
                        {
                           h_alias_name_icon = nav_ipts_get_alias_icon(ui1_loop,1);
                        }
                        else
                        {
                           h_alias_name_icon = NULL_HANDLE;
                        }
                        /* 1.update e_src_type e_video_type */
                        {
                            pt_ipt_list_rec[i+ui1_loop].e_src_type = INP_SRC_TYPE_AV;
                            pt_ipt_list_rec[i+ui1_loop].e_video_type = DEV_AVC_COMBI;
                        }
                        /* 2.update h_img h_img_hlt */
                        {
                            if(NULL_HANDLE == h_alias_name_icon)
                            {
                                pt_ipt_list_rec[i+ui1_loop].h_img = h_g_nav_banner_new_input_computer_lt_img;
                                pt_ipt_list_rec[i+ui1_loop].h_img_hlt = h_g_nav_banner_new_input_computer_lt_img;
                            }
                            else
                            {
                                pt_ipt_list_rec[i+ui1_loop].h_img = h_alias_name_icon;
                                pt_ipt_list_rec[i+ui1_loop].h_img_hlt = h_alias_name_icon;
                            }
                        }
                        /* 3.update t_item_img_disable t_item_img_normal */
                        /* 4.update w2s_ch_name w2s_ch_no */
                        /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
                        /* 6.t_elem */
                        /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
                        {
                            pt_ipt_list_rec[i+ui1_loop].b_cec_dev = FALSE;
                            pt_ipt_list_rec[i+ui1_loop].b_conn_amp = FALSE;
                        }
                    }
                    else if(a_nav_ipts_is_vga_source(&t_isl_iterate) == TRUE)
                    {
                        if( (c_uc_w2s_strlen(w2s_alias) > 0) || (c_uc_w2s_strlen(w2s_device_type) > 0))
                        {
                           h_alias_name_icon = nav_ipts_get_alias_icon(ui1_loop,1);
                        }
                        else
                        {
                           h_alias_name_icon = NULL_HANDLE;
                        }
                        /* 1.update e_src_type e_video_type */
                        {
                            pt_ipt_list_rec[i+ui1_loop].e_src_type = INP_SRC_TYPE_AV;
                            pt_ipt_list_rec[i+ui1_loop].e_video_type = DEV_AVC_VGA;
                        }
                        /* 2.update h_img h_img_hlt */
                        {
                            if(NULL_HANDLE == h_alias_name_icon)
                            {
                                pt_ipt_list_rec[i+ui1_loop].h_img = h_g_nav_banner_new_input_computer_lt_img;
                                pt_ipt_list_rec[i+ui1_loop].h_img_hlt = h_g_nav_banner_new_input_computer_lt_img;
                            }
                            else
                            {
                                pt_ipt_list_rec[i+ui1_loop].h_img = h_alias_name_icon;
                                pt_ipt_list_rec[i+ui1_loop].h_img_hlt = h_alias_name_icon;
                            }
                        }
                        /* 3.update t_item_img_disable t_item_img_normal */
                        /* 4.update w2s_ch_name w2s_ch_no */
                        /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
                        /* 6.t_elem */
                        /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
                        {
                            pt_ipt_list_rec[i+ui1_loop].b_cec_dev = FALSE;
                            pt_ipt_list_rec[i+ui1_loop].b_conn_amp = FALSE;
                        }
                    }
                    else
                    {
                        NAV_DEBUG_INPUT_SRC_REC_COLLECT( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_id: %d, ui1_internal_id:%d, Unknown src_type !!\n",
                                    __FUNCTION__, __LINE__, t_isl_iterate.ui1_id, t_isl_iterate.ui1_internal_id)); );

                        /* 1.update e_src_type e_video_type */
                        {
                            pt_ipt_list_rec[i+ui1_loop].e_src_type = INP_SRC_TYPE_UNKNOWN;
                            pt_ipt_list_rec[i+ui1_loop].e_video_type = DEV_UNKNOWN;
                        }
                        /* 2.update h_img h_img_hlt */
                        {
                            pt_ipt_list_rec[i+ui1_loop].h_img = NULL_HANDLE;
                            pt_ipt_list_rec[i+ui1_loop].h_img_hlt = NULL_HANDLE;
                        }
                        /* 3.update t_item_img_disable t_item_img_normal */
                        /* NULL */
                        /* 4.update w2s_ch_name w2s_ch_no */
                        /* NULL */
                        /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
                        /* NULL */
                        /* 6.t_elem */
                        /* NULL */
                        /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
                        /* NULL */
                    }
                }
            }
        }

        i += ui1_loop;
    }

    //================= Add Power Off =================
    {
        {
            pt_ipt_list_rec[i].t_elem.b_is_disabled = FALSE;
            pt_ipt_list_rec[i].t_elem.i2_idx = i;
            pt_ipt_list_rec[i].t_elem.ui1_id = ui1_loop;
            pt_ipt_list_rec[i].t_elem.e_func_type = E_FUNC_ELEMENT_POWER_OFF;

            /*others setting*/
            pt_ipt_list_rec[i].b_cec_dev = FALSE;
            pt_ipt_list_rec[i].b_conn_amp = FALSE;

            /*icon*/
            pt_ipt_list_rec[i].t_item_img_disable = t_item_img_normal;
            pt_ipt_list_rec[i].t_item_img_normal = t_item_img_normal;

            /*name*/
            c_uc_w2s_strcpy(pt_ipt_list_rec[i].w2s_elem_col1_name, L"POWER OFF ");
            //c_uc_w2s_strcpy(pt_ipt_list_rec[i].w2s_elem_col1_name,MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_AUTO_POWER_OFF_OFF));

            pt_ipt_list_rec[i].h_img = h_g_nav_banner_new_input_off_lt_img;
            pt_ipt_list_rec[i].h_img_hlt = h_g_nav_banner_new_input_off_lt_img;
            i ++;
        }
    }

    //================= Add CEC =================
    do
    {
        UINT8 ui1_amp_conn_num = 0;
        UINT8 ui1_hdmi_idx;
        BOOL b_able_to_add = TRUE;
        //UTF16_T cec_last_name[5][32] = {0};
        #define ISL_USED_PORT_NUM   5
        CHAR used_hdmi_name[ISL_USED_PORT_NUM][CECM_OSD_NAME_SIZE+1] = {0};

    #if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
        CEC_DEV_LST_T    t_lst;
    #endif
        UINT8 ui1_cec_func = APP_CFG_CEC_OFF;
        CHAR next_add_device_name[CECM_OSD_NAME_SIZE+1] = {0};

        {
            a_cfg_get_cec_func(&ui1_cec_func);

            if (ui1_cec_func == APP_CFG_CEC_OFF)
            {
                break;
            }
        }

        c_memset(used_hdmi_name, 0, sizeof(used_hdmi_name));
        c_memset(at_ipts_cec_dev, 0, sizeof(at_ipts_cec_dev));
        c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));

        a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

        DBG_LOG_PRINT(("<INPUT SRC LIST>[%s][%d] t_lst.ui1_dev_num:%d\n", __FUNCTION__,__LINE__, t_lst.ui1_dev_num));

        for (ui1_loop = 0; ui1_loop < t_lst.ui1_dev_num; ui1_loop++)
        {
            ui1_hdmi_idx = (t_lst.at_dev_info[ui1_loop].ui2_pa >> 12) - 1;

            DBG_LOG_PRINT(("<INPUT SRC LIST>[%s][%d] ui1_loop:%d, ui2_pa:0x%X \n", \
                            __FUNCTION__,__LINE__, ui1_loop, t_lst.at_dev_info[ui1_loop].ui2_pa ));

            // Fix array over range! Why ui2_pa is 0x101!?
            if( ((t_lst.at_dev_info[ui1_loop].ui2_pa >> 12) == 0 )
              ||(ui1_hdmi_idx >= ISL_USED_PORT_NUM)
              )
            {
                DBG_LOG_PRINT(("<INPUT SRC LIST>[%s][%d] Warning!! ui1_loop:%d, ui2_pa:0x%X, ui1_hdmi_idx:%d => Skip\n", __FUNCTION__,__LINE__,
                                            ui1_loop, t_lst.at_dev_info[ui1_loop].ui2_pa, ui1_hdmi_idx ));
                continue;
            }

            c_memset(next_add_device_name, 0, sizeof(next_add_device_name));
            c_uc_w2s_to_ps(t_lst.at_dev_info[ui1_loop].aw2_osd_name, next_add_device_name, CECM_OSD_NAME_SIZE);

            DBG_LOG_PRINT(("<INPUT SRC LIST>[%s][%d] aw2_osd_name:{%s}, used_hdmi_name:{%s}, ui1_hdmi_idx:%d, addr:0x%x\n", __FUNCTION__, __LINE__,\
                next_add_device_name, used_hdmi_name[ui1_hdmi_idx], ui1_hdmi_idx, t_lst.at_dev_info[ui1_loop].ui2_pa));

            if(c_strcmp(next_add_device_name, used_hdmi_name[ui1_hdmi_idx]) == 0)
            {
                if(((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) == 0) && (ui1_amp_conn_num > 0))
                {
                    ui1_amp_conn_num --;
                    c_memset(&(pt_ipt_list_rec[i+ui1_amp_conn_num]), 0, sizeof(IPT_LIST_REC_T));
                }
                DBG_LOG_PRINT(("<INPUT SRC LIST>[%s][%d] no need update the same device\n", __FUNCTION__, __LINE__));
                continue;
            }
            else
            {
                c_strcpy(used_hdmi_name[ui1_hdmi_idx], next_add_device_name);
                //DTV02833938:for oppo dvd show two device name in input list,because oppo DVD would be a disc player and an amp device at the same time
                //oppo dvd aaddr always is 0x1300 if plug in hdmi1,like a AVR connected device addr (generally,one connected cec device addr should be 0x1000)
                if((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) && (t_lst.ui1_dev_num == 1))
                {
                    DBG_LOG_PRINT(("<INPUT SRC LIST>[%s][%d] no need update the same device\n", __FUNCTION__, __LINE__));
                    continue;
                }
            }

            if ((t_lst.at_dev_info[ui1_loop].ui2_pa & 0x0fff) == 0)
            {
                continue;
            }

            if (TV_MODE_TYPE_NORMAL == e_tv_mode)
            {
                b_able_to_add = TRUE;
            }
            else
            {
                i4_ret = a_isl_get_rec_by_dev_type (DEV_AVC_HDMI, ui1_hdmi_idx, &t_isl_iterate);
                if (i4_ret == ISLR_OK)
                {
                    b_able_to_add = _nav_ipts_lst_is_able_to_pip_pop (&t_isl_other, &t_isl_iterate);
                }
                else
                {
                    b_able_to_add = FALSE;
                }

            }

        #ifdef APP_ARC_ONLY
            if (APP_CFG_CEC_ARC_ONLY == ui1_cec_func
                && CECM_LOG_ADDR_AUD_SYS != t_lst.at_dev_info[ui1_loop].e_la)
            {
            /*
                 *original is FALSE, because of SPEC4.1 4.8.1 input name is
                 *automatic if CEC is enabled or ARC only
                 */
                b_able_to_add = TRUE;
            }
        #endif

            if (b_able_to_add == FALSE)
            {
                continue;
            }

            do
            {
                i4_ret = a_isl_get_rec_by_dev_type (DEV_AVC_HDMI, ui1_hdmi_idx, &t_isl_iterate);
                if (i4_ret == ISLR_OK)
                {
                    break;
                }
                else
                {
                    DBG_INFO(("a_isl_get_rec_by_dev_type in input_src_list return Error %d[DEV_AVC_HDMI] !\n ",i4_ret));
                }
                i4_ret = a_isl_get_rec_by_dev_type (DEV_AVC_AUDIO_INP, ui1_hdmi_idx, &t_isl_iterate);
                if (i4_ret == ISLR_OK)
                {
                    break;
                }
                else
                {
                    DBG_INFO(("a_isl_get_rec_by_dev_type in input_src_list return Error %d[DEV_AVC_AUDIO_INP] !\n ",i4_ret));
                }
            }while(0);

            /* Device is connected to an AMP */
            if (TRUE == t_lst.at_dev_info[ui1_loop].b_amp_connected)
            {
                /* 1.update e_src_type e_video_type */
                /* NULL */
                /* 2.update h_img h_img_hlt */
                {
                    if( c_uc_w2s_strlen(t_lst.at_dev_info[ui1_loop].aw2_osd_name) != 0 )
                    {
                        #if 0 /* cec device can not rename */
                        UTF16_T w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN + 1]={0};
                        CHAR    ac_alias[APP_CFG_CUSTOM_INP_NAME_LEN + 1]={0};
                        c_memset (ac_alias, 0, APP_CFG_CUSTOM_INP_NAME_LEN + 1);
                        c_memset (w2s_alias, 0, APP_CFG_CUSTOM_INP_NAME_LEN + 1);
                        a_cfg_custom_get_cec_name(ui1_loop, ac_alias);
                        if(c_strlen(ac_alias) > 0)
                        {
                            pt_ipt_list_rec[i+ui1_amp_conn_num].h_img = h_alias_name_icon;
                            pt_ipt_list_rec[i+ui1_amp_conn_num].h_img_hlt = h_alias_name_icon;
                        }
                        #endif
                    }
                    else
                    {
                        pt_ipt_list_rec[i+ui1_amp_conn_num].h_img = h_g_nav_banner_new_input_hdmi_lt_img;
                        pt_ipt_list_rec[i+ui1_amp_conn_num].h_img_hlt = h_g_nav_banner_new_input_hdmi_lt_img;
                    }
                }
                /* 3.update t_item_img_disable t_item_img_normal */
                pt_ipt_list_rec[i+ui1_amp_conn_num].t_item_img_disable = t_item_img_disable;
                pt_ipt_list_rec[i+ui1_amp_conn_num].t_item_img_normal = t_item_img_normal;
                /* 4.update w2s_ch_name w2s_ch_no */
                /* NULL */
                /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
                {
                    if( c_uc_w2s_strlen(t_lst.at_dev_info[ui1_loop].aw2_osd_name) != 0 )
                    {
                    #if 0 /* cec device can not rename */
                        UTF16_T w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN + 1]={0};
                        CHAR    ac_alias[APP_CFG_CUSTOM_INP_NAME_LEN + 1]={0};
                        c_memset (ac_alias, 0, APP_CFG_CUSTOM_INP_NAME_LEN + 1);
                        c_memset (w2s_alias, 0, APP_CFG_CUSTOM_INP_NAME_LEN + 1);
                        a_cfg_custom_get_cec_name(ui1_loop, ac_alias);
                        if(c_strlen(ac_alias)> 0)
                        {
                        c_uc_ps_to_w2s(ac_alias ,w2s_alias ,APP_CFG_CUSTOM_INP_NAME_LEN);
                        c_uc_w2s_strcpy(pt_ipt_list_rec[i+ui1_amp_conn_num].w2s_elem_col1_name,w2s_alias);
                        }
                        else
                    #endif
                        {
                            c_uc_w2s_strcpy(pt_ipt_list_rec[i+ui1_amp_conn_num].w2s_elem_col1_name,
                                            t_lst.at_dev_info[ui1_loop].aw2_osd_name);
                        }
                    }
                    else
                    {
                        c_uc_w2s_strcpy(pt_ipt_list_rec[i+ui1_amp_conn_num].w2s_elem_col1_name,
                                        a_cec_custom_get_dev_category_name (t_lst.at_dev_info[ui1_loop].e_la));
                    }

                    /* debug */
                    {
                        CHAR    ac_osd_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1]={0};

                        c_uc_w2s_to_ps(t_lst.at_dev_info[ui1_loop].aw2_osd_name, ac_osd_name, APP_CFG_CUSTOM_INP_NAME_LEN);

                        DBG_INFO(("<INPUT SRC LIST>[%s][%d] ac_osd_name: %s b_act_src %d e_la %d ui2_pa %X ui1_loop:%d i:%d \n",\
                                        __FUNCTION__, __LINE__,\
                                       ac_osd_name,t_lst.at_dev_info[ui1_loop].b_act_src\
                                       ,t_lst.at_dev_info[ui1_loop].e_la,t_lst.at_dev_info[ui1_loop].ui2_pa,i));
                    }
                }
                /* 6.t_elem */
                pt_ipt_list_rec[i+ui1_amp_conn_num].t_elem.b_is_disabled = FALSE;
                pt_ipt_list_rec[i+ui1_amp_conn_num].t_elem.i2_idx = i+ui1_amp_conn_num;
                pt_ipt_list_rec[i+ui1_amp_conn_num].t_elem.ui1_id = at_hdmi_sorting[ui1_hdmi_idx].ui4_show_count;
                /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
                pt_ipt_list_rec[i+ui1_amp_conn_num].b_cec_dev = TRUE;
                pt_ipt_list_rec[i+ui1_amp_conn_num].b_conn_amp = TRUE;

                at_ipts_cec_dev[ui1_loop].ui2_dev_index_in_ipts = i+ui1_amp_conn_num;

                ui1_amp_conn_num++;
            }
            else
            {
                /* 1.update e_src_type e_video_type */
                /* NULL */
                /* 2.update h_img h_img_hlt */
                /* NULL */
                /* 3.update t_item_img_disable t_item_img_normal */
                /* NULL */
                /* 4.update w2s_ch_name w2s_ch_no */
                /* NULL */
                /* 5.h_elem_col0_img  w2s_elem_col1_name[32]  w2s_elem_col2_name[32] */
                /* NULL */
                /* 6.t_elem */
                /* NULL */
                /* 7.other :  ui2_num b_cec_dev b_conn_amp*/
                {
                    UINT8 ui8_tmp_idx = 0;
                    ui8_tmp_idx = at_hdmi_sorting[ui1_hdmi_idx].at_elem;

                    pt_ipt_list_rec[ui8_tmp_idx].b_cec_dev = TRUE;
                    pt_ipt_list_rec[ui8_tmp_idx].b_conn_amp = FALSE;
                }

                {
                    UINT8 ui8_tmp_idx = 0;
                    ui8_tmp_idx = at_hdmi_sorting[ui1_hdmi_idx].at_elem;

                    at_ipts_cec_dev[ui1_loop].ui2_dev_index_in_ipts = ui8_tmp_idx;
                }
            }

            at_ipts_cec_dev[ui1_loop].e_dev_la = t_lst.at_dev_info[ui1_loop].e_la;
            at_ipts_cec_dev[ui1_loop].ui2_dev_pa = t_lst.at_dev_info[ui1_loop].ui2_pa;
        }

        //DBG_LOG_PRINT(("<NAV INPUT> file: %s line: %d  %s amp_conn_num: %d\n", __FILE__, __LINE__, __FUNCTION__, ui1_amp_conn_num));
        i += ui1_amp_conn_num;

    }while(0);

    //================= Add Retail mode =================
#ifdef APP_RETAIL_MODE_SUPPORT
    {
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

        if (FALSE && b_key_front_pannel && (ACFG_RETAIL_MODE_NORMAL == t_retail_mode))
        {
            pt_ipt_list_rec[i].t_elem.b_is_disabled = FALSE;
            pt_ipt_list_rec[i].t_elem.i2_idx = i;
            pt_ipt_list_rec[i].t_elem.ui1_id = -1;

            /*icon*/
            pt_ipt_list_rec[i].t_item_img_disable = t_item_img_normal;
            pt_ipt_list_rec[i].t_item_img_normal = t_item_img_normal;

            /*name*/
            c_uc_w2s_strcpy(pt_ipt_list_rec[i].w2s_elem_col1_name,
                            MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_TURN_DEMO_OFF));

            pt_ipt_list_rec[i].h_img = h_g_nav_banner_new_input_off_lt_img;
            pt_ipt_list_rec[i].h_img_hlt = h_g_nav_banner_new_input_off_lt_img;
            i ++;
        }
    }
#endif

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} -- end\n", __FUNCTION__, __LINE__ )); );

    return NAVR_OK;
}

#if(NAV_INPUT_SRC_UI_VERTICAL)
static UINT8 s_u8_active_elem_idx = 0;
#endif

static INT32 _ipt_list_rec_set_to_list(_NAV_IPTS_LIST_MEMBER_T* pt_this,
                                            TV_WIN_ID_T e_grp,
                                            IPT_LIST_REC_T* pt_ipt_list_rec)
{
    INT32           i4_ret = NAVR_OK;
    UINT8           i = 0;
    UINT8           ui1_loop = 0;
    ISL_REC_T       t_isl_rec = {0};
    GL_RECT_T       t_rect = {0};
    IPT_LIST_REC_T *pt_rec = NULL;
    UINT8           ui1_head = 0;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} -- START\n", __FUNCTION__, __LINE__ )); );

    if(pt_ipt_list_rec == NULL)
    {
        return NAVR_INV_ARG;
    }

    i4_ret = _nav_ipts_lst_elem_sort(pt_ipt_list_rec);
    NAV_CHK_FAIL(i4_ret);

    if(nav_get_power_to_input_status() == TRUE && _nav_ipts_lst_pwrdwn_check_sku_default_enable() == TRUE)
    {
        _nav_ipts_lst_elem_sort_pwrdwn(e_grp, pt_ipt_list_rec);
        NAV_CHK_FAIL(i4_ret);
    }


    // Check bar_type ...
    UINT32 ui4_name_idx, ui4_bar_idx;
    if( NAV_IPTS_LST_SBT_LEFT == pt_this->e_bar_type )
    {
        ui4_name_idx = 1;
        ui4_bar_idx = 0;
    }
    else
    {
        ui4_name_idx = 0;
        ui4_bar_idx = 1;
    }
    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui4_name_idx:%d, ui4_bar_idx:%d\n",
        __FUNCTION__, __LINE__, ui4_name_idx, ui4_bar_idx )); );


#if(NAV_INPUT_SRC_UI_VIZIO_STYLE)
    WGL_LB_ITEM_IMG_SUIT_T  t_item_img_empty = {0}, t_item_img_current_src = {0};
    t_item_img_current_src.h_normal = pt_this->h_active_img;
    t_item_img_current_src.h_disable = pt_this->h_active_img;
    t_item_img_current_src.h_highlight = pt_this->h_active_img;
    t_item_img_current_src.h_highlight_unfocus = pt_this->h_active_img;
    t_item_img_current_src.h_selected_highlight = pt_this->h_active_img;
    t_item_img_current_src.h_selected_highlight_unfocus = pt_this->h_active_img;
    t_item_img_current_src.h_selected = pt_this->h_active_img;
    t_item_img_current_src.h_selected_disable = pt_this->h_active_img;
    t_item_img_current_src.h_pushed = pt_this->h_active_img;
    t_item_img_current_src.h_selected_pushed = pt_this->h_active_img;
#endif


    i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_isl_rec);
    NAV_CHK_FAIL(i4_ret == TVR_OK ? NAVR_OK : i4_ret);

    /* Get the first elem */
    do{

    #ifdef APP_WFD_SUPPORT
        if (a_cfg_custom_get_wfd_support() == TRUE
            && a_wfd_is_rtsp_play_status() == TRUE)
        {
            ui1_head = 0;
            break;
        }
    #endif

        pt_rec = (IPT_LIST_REC_T*)&pt_ipt_list_rec[0];

        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} t_isl_rec.ui1_id:%d, pt_ipt_list_rec[0].ui2_num:%d\n",
            __FUNCTION__, __LINE__, t_isl_rec.ui1_id, pt_ipt_list_rec[0].ui2_num )); );

        for (ui1_loop = 0; ui1_loop < pt_ipt_list_rec[0].ui2_num; ui1_loop++)
        {
            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_loop:%d, pt_rec->t_elem.ui1_id:%d\n",
                __FUNCTION__, __LINE__, ui1_loop, pt_rec->t_elem.ui1_id )); );

            if (t_isl_rec.ui1_id == pt_rec->t_elem.ui1_id)
            {
                ui1_head = ui1_loop;

            #if( NAV_INPUT_SRC_UI_VERTICAL )
                s_u8_active_elem_idx = ui1_loop;
                NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} s_u8_active_elem_idx:%d\n",
                    __FUNCTION__, __LINE__, s_u8_active_elem_idx )); );
            #endif
                break;
            }

            pt_rec++;
        }

    }while(0);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_head:%d\n",
        __FUNCTION__, __LINE__, ui1_head )); );

#if( NAV_INPUT_SRC_UI_VERTICAL )
    s_u8_active_elem_idx = ui1_head;
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} set s_u8_active_elem_idx =%d, set ui1_head=0\n",
        __FUNCTION__, __LINE__, s_u8_active_elem_idx )); );

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} set ui1_head=0\n", __FUNCTION__, __LINE__ )); );
    ui1_head = 0;// daniel
#endif

    i = 0;
    ui1_loop = ui1_head;


    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_ipt_list_rec[0].ui2_num:%d\n",
        __FUNCTION__, __LINE__, pt_ipt_list_rec[0].ui2_num )); );

    /* get at_elem  base on  pt_ipt_list_rec and ui1_head */
    do
    {
        NAV_DEBUG_INPUT_SRC(
            DBG_LOG_PRINT(("\n[NAV][INPUT_SRC]{%s,%d} ---------- ui1_loop:%d, i:%d --------------------------------------- \n",
                __FUNCTION__, __LINE__, ui1_loop, i )); );

        pt_rec = (IPT_LIST_REC_T*)&pt_ipt_list_rec[ui1_loop];

        c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));
        a_isl_get_rec_by_id(pt_rec->t_elem.ui1_id, &t_isl_rec);

        /* set element */
        pt_this->at_elem[i].b_is_disabled = pt_rec->t_elem.b_is_disabled;
        pt_this->at_elem[i].i2_idx = i;
        pt_this->at_elem[i].ui1_id = pt_rec->t_elem.ui1_id;
        pt_this->at_elem[i].e_func_type = pt_rec->t_elem.e_func_type;


        /* debug name */
        {
            CHAR    ac_elem_col1_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
            CHAR    ac_elem_col2_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1];

            c_uc_w2s_to_ps(pt_rec->w2s_elem_col1_name, ac_elem_col1_name, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(pt_rec->w2s_elem_col2_name, ac_elem_col2_name, APP_CFG_CUSTOM_INP_NAME_LEN);

            DBG_LOG_PRINT(("<INPUT SRC LIST> i:%d, ui1_loop:%d, name: [%s] [%s]\n", i, ui1_loop, ac_elem_col1_name, ac_elem_col2_name ));

            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} i:%d, ui1_loop:%d, name: [%s] [%s]\n",
                __FUNCTION__, __LINE__, i,ui1_loop, ac_elem_col1_name, ac_elem_col2_name )); );
        }

        // Set UI listbox...
        {
            // Set UI Bar(icon)
            WGL_LB_ITEM_IMG_SUIT_T * pt_item_img_tmp;
        #if(NAV_INPUT_SRC_UI_VERTICAL && NAV_INPUT_SRC_UI_VIZIO_STYLE) // Only current source need icon...
            if( s_u8_active_elem_idx == i ) // current source
            {
                pt_item_img_tmp = &(t_item_img_current_src);
                NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} i:%d, Use: t_item_img_current_src\n",
                    __FUNCTION__, __LINE__, i ));  );
            }
            else
            {
                pt_item_img_tmp = &(t_item_img_empty);
                NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} i:%d, Use: t_item_img_empty\n",
                    __FUNCTION__, __LINE__, i ));  );

            }
        #else
            pt_item_img_tmp = &(pt_rec->t_item_img_normal);
            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} i:%d, Use: pt_rec->t_item_img_normal\n",
                __FUNCTION__, __LINE__, i ));  );
        #endif

            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox[%d,%d], WGL_CMD_LB_SET_ITEM_IMAGE_SUIT: 0x%X\n",
                __FUNCTION__, __LINE__, i, ui4_bar_idx, (UINT32)pt_item_img_tmp )); );
            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                                  WGL_PACK_2(i, ui4_bar_idx /* 0 */ ),
                                  WGL_PACK(pt_item_img_tmp) );
            NAV_CHK_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);


            // set UI name
            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox[%d,%d], WGL_CMD_LB_SET_ITEM_TEXT, [%s]\n",
                __FUNCTION__, __LINE__, i, ui4_name_idx, menu_custom_get_char_string( pt_rec->w2s_elem_col1_name)  )); );
            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_SET_ITEM_TEXT,
                                  WGL_PACK_2(i, ui4_name_idx /* 1 */),
                                  WGL_PACK(pt_rec->w2s_elem_col1_name));
            NAV_CHK_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);


        #if( NAV_INPUT_SRC_UI_HAS_ALIAS )
            //c_uc_w2s_strncpy(pt_rec->w2s_elem_col2_name, L"XXXXXX", 30);
            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox[%d,2], WGL_CMD_LB_SET_ITEM_TEXT, [%s]\n",
                __FUNCTION__, __LINE__, i, menu_custom_get_char_string( pt_rec->w2s_elem_col2_name)  )); );
            i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                  WGL_CMD_LB_SET_ITEM_TEXT,
                                  WGL_PACK_2(i, NAV_UI_LISTBOX_COL_IDX_ALIAS),
                                  WGL_PACK(pt_rec->w2s_elem_col2_name));
            NAV_CHK_FAIL(i4_ret == WGLR_OK ? NAVR_OK : i4_ret);
        #endif

        }

        if (c_uc_w2s_strcmp(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_TURN_DEMO_OFF),
                            pt_rec->w2s_elem_col1_name) == 0)
        {
            ui4_retail_elem_idx = i;
        }

        if (a_nav_ipts_is_tv_source(&t_isl_rec) == TRUE)
        {
            NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} i:%d, b_tv_channel_valid:%d, w2s_ch_no:[%s], w2s_ch_name:[%s]\n",
                __FUNCTION__, __LINE__, i, pt_rec->b_tv_channel_valid,
                nav_cust_get_char_string(pt_rec->w2s_ch_no), nav_cust_get_char_string(pt_rec->w2s_ch_name)  )); );

        #if(NAV_INPUT_SRC_UI_HAS_TV_CH_NUM_NAME_TEXT)
            SET_RECT_BY_SIZE (&t_rect,
                              NAV_IPTS_LST_BOX_LEFT + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ,
                              ((NAV_IPTS_LST_BOX_TOP + (NAV_IPTS_LST_BOX_ELEM_HEIGHT * i))+(NAV_IPTS_LST_BOX_ELEM_HEIGHT/2)),
                              NAV_IPTS_LST_BOX_WIDTH - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_RIGHT_ADJ,
                              NAV_IPTS_LST_BOX_ELEM_HEIGHT/2);

            c_wgl_move(h_inp_tv_ch_name_text, &t_rect, WGL_NO_AUTO_REPAINT);

            ipts_config_text_utf16(h_inp_tv_ch_name_text,NAV_IPTS_CH_NAME_FONT,NAV_IPTS_CH_NAME_FONT_SIZE, pt_rec->w2s_ch_name);

            SET_RECT_BY_SIZE (&t_rect,
                              NAV_IPTS_LST_BOX_LEFT + NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ,
                              NAV_IPTS_LST_BOX_TOP + (NAV_IPTS_LST_BOX_ELEM_HEIGHT * i),
                              NAV_IPTS_LST_BOX_WIDTH - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_LEFT_ADJ - NAV_BANNER_LEVEL_1_INPUT_CH_NAME_WGL_RIGHT_ADJ,
                              NAV_IPTS_LST_BOX_ELEM_HEIGHT/2);

            c_wgl_move(h_inp_tv_ch_no_text, &t_rect, WGL_NO_AUTO_REPAINT);

            ipts_config_text_utf16(h_inp_tv_ch_no_text,NAV_IPTS_CH_NO_FONT,NAV_IPTS_CH_NO_FONT_SIZE,pt_rec->w2s_ch_no);

            i4_ret = c_wgl_do_cmd(h_inp_tv_ch_no_text,
                                  WGL_CMD_TEXT_SET_ALIGN,
                                  WGL_PACK(WGL_AS_CENTER_CENTER),
                                  NULL);
        #endif

            /* debug */
          #if 0
            {
                CHAR    ac_tv_ch_no[64 + 1];
                CHAR    ac_tv_ch_name[64 + 1];

                c_uc_w2s_to_ps(pt_rec->w2s_ch_no, ac_tv_ch_no, 64 + 1);
                c_uc_w2s_to_ps(pt_rec->w2s_ch_name, ac_tv_ch_name, 64 + 1);

                DBG_LOG_PRINT(("<INPUT SRC LIST> TV name: %s %s\n", ac_tv_ch_no, ac_tv_ch_name ));
            }
          #endif
        }

        if (a_nav_ipts_is_hdmi_source(&t_isl_rec) == TRUE)
        {
        #if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
            UINT8 ui1_loop_cec = 0;
            //update at_ipts_cec_dev ui2_dev_index_in_ipts after sort
            for (ui1_loop_cec = 0; ui1_loop_cec < 16; ui1_loop_cec++)
            {
                //DBG_LOG_PRINT(("<INPUT SRC LIST> ui1_loop_cec:%d ui2_dev_index_in_ipts:%d \n",ui1_loop_cec,at_ipts_cec_dev[ui1_loop_cec].ui2_dev_index_in_ipts));
                if(at_ipts_cec_dev[ui1_loop_cec].ui2_dev_index_in_ipts == ui1_loop)
                {
                    at_ipts_cec_dev[ui1_loop_cec].ui2_dev_index_in_ipts = i;
                    //DBG_LOG_PRINT(("<INPUT SRC LIST> ui2_dev_index_in_ipts:%d i:%d\n",at_ipts_cec_dev[ui1_loop_cec].ui2_dev_index_in_ipts,i));
                }
            }
        #endif
        }

    #if(NAV_INPUT_SRC_UI_HAS_DEV_ICON)
        ipts_config_icon(h_inp_icon_img[i],pt_rec->h_img,pt_rec->h_img_hlt);
    #endif

        i++;
        ui1_loop++;
        ui1_loop = ui1_loop % pt_ipt_list_rec[0].ui2_num;


    }while(ui1_head !=  ui1_loop);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} -- END\n", __FUNCTION__, __LINE__ )); );

    return i4_ret;
}

static INT32 _nav_ipts_lst_update_elems_ex(
    _NAV_IPTS_LIST_MEMBER_T*            pt_this,
    TV_WIN_ID_T                         e_grp,
    BOOL                                b_force)
{
    INT32                               i4_ret;
    TV_MODE_T                           e_tv_mode;
    ISL_REC_T                           t_isl_active, t_isl_other;
    GL_RECT_T                           t_rect;
    UINT32                              ui4_active_idx;
    UINT8                               ui1_num_recs = 0;


    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this:0x%X, e_grp:%d, b_force:%d \n",
        __FUNCTION__, __LINE__, (UINT32)pt_this, e_grp, b_force )); );


    /* get t_list_elem_num.ui2_total_num */
    {
        i4_ret = _nav_ipts_lst_calculate_num();
        NAV_LOG_ON_FAIL(i4_ret);

        ui1_num_recs = t_list_elem_num.ui2_total_num;
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_num_recs:%d\n",
            __FUNCTION__, __LINE__, ui1_num_recs )); );

    }

    /* reset all elem -> should set in input src view */
    {
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox WGL_CMD_LB_DEL_ALL \n",
            __FUNCTION__, __LINE__ )); );
        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                WGL_CMD_LB_DEL_ALL,
                                WGL_PACK(NULL),
                                WGL_PACK(NULL));
        NAV_CHK_FAIL(i4_ret);


        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox WGL_CMD_LB_SET_ELEM_NUM:%d \n",
            __FUNCTION__, __LINE__, ui1_num_recs )); );
        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                                WGL_CMD_LB_SET_ELEM_NUM,
                                WGL_PACK((UINT16)ui1_num_recs),
                                NULL);
        NAV_CHK_FAIL(i4_ret);
    }

    /* update at_crnt_ht_element ?? */
    {
        at_crnt_ht_element.ui1_max_elems = ui1_num_recs;
    }

    /*  */
    {
        _NAV_IPTS_LST_ACT_IF_UI_NOT_INIT(pt_this, return NAVR_NOT_ALLOW);

        /* create pt_ipt_list_rec */
        {
            if (NULL == pt_ipt_list_rec)
            {
               pt_ipt_list_rec = (IPT_LIST_REC_T *)c_mem_alloc(NAV_IPTS_LST_BOX_ELEM_COUNT * sizeof(IPT_LIST_REC_T));
            }

            if (NULL == pt_ipt_list_rec)
            {
               return NAVR_NOT_ALLOW;
            }
        }

        c_memset(pt_ipt_list_rec, 0, NAV_IPTS_LST_BOX_ELEM_COUNT * sizeof(IPT_LIST_REC_T));

        pt_ipt_list_rec[0].ui2_num = ui1_num_recs;

        /* update pt_ipt_list_rec at_ipts_cec_dev ( show in input list view ) */
        i4_ret = _ipt_list_rec_collect(pt_this,e_grp, pt_ipt_list_rec);
        NAV_CHK_FAIL(i4_ret);

        /* set to view */
        i4_ret = _ipt_list_rec_set_to_list(pt_this,e_grp, pt_ipt_list_rec);
        NAV_CHK_FAIL(i4_ret);

        /* debug */
        NAV_DEBUG_INPUT_SRC( nav_ipts_lst_print_elems(pt_this); );
    }

#if(NAV_INPUT_SRC_UI_HAS_TITLE)
    { /*set title*/
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d}  \n",
            __FUNCTION__, __LINE__  )); );

        UTF16_T  w2s_grp[20]={0};// = L"daniel_title";
        c_uc_w2s_strcpy(w2s_grp, L"Input");

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox WGL_CMD_LB_SET_TITLE_TEXT:[%s]\n",
            __FUNCTION__, __LINE__, menu_custom_get_char_string(w2s_grp))); );

        i4_ret = c_wgl_do_cmd(pt_this->h_listbox,
                              WGL_CMD_LB_SET_TITLE_TEXT,
                              (VOID*)w2s_grp,
                              (VOID*)((NULL == w2s_grp) ? 0 : c_uc_w2s_strlen(w2s_grp)));

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox WGL_CMD_LB_SET_TITLE_TEXT: i4_ret:%d\n",
            __FUNCTION__, __LINE__, i4_ret   )); );

        if(WGLR_OK != i4_ret)
        {
            DBG_LOG_PRINT((_ERROR_HEADER"%s(): Fail to set Title. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
            return NAVR_FAIL;
        }
    }
#endif


    // Test listbox skin
  #if(NAV_INPUT_SRC_LOAD_SKIN_TEST)
    _nav_ipts_lst_listbox_load_skin_test();
  #endif

    /* ??? */
    {
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} pt_ipt_list_rec[0].ui2_num:%d \n",
            __FUNCTION__, __LINE__, pt_ipt_list_rec[0].ui2_num)); );

    #if( !NAV_IPTS_LST_BOX_HEIGHT_FIX )
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_IPTS_LST_BOX_LEFT,
                         NAV_IPTS_LST_BOX_TOP,
                         NAV_IPTS_LST_BOX_WIDTH,
                         (NAV_IPTS_LST_BOX_ELEM_HEIGHT * pt_ipt_list_rec[0].ui2_num)
                         + (NAV_IPTS_LST_BOX_CONTENT_INSET_TOP + NAV_IPTS_LST_BOX_CONTENT_INSET_BOTTOM)
                         );

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_listbox move:(%d %d %d %d) \n",
            __FUNCTION__, __LINE__, t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );

        i4_ret = c_wgl_move(pt_this->h_listbox,
                            &t_rect,
                            WGL_SYNC_AUTO_REPAINT);
    #endif

    #if( !NAV_INPUT_SRC_UI_VERTICAL)
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_IPTS_LST_BOX_LEFT,
                         (NAV_IPTS_LST_BOX_ELEM_HEIGHT * pt_ipt_list_rec[0].ui2_num) - 1,
                         NAV_IPTS_LST_BOX_WIDTH,
                         NAV_IPTS_LST_SHADOW_HEIGHT);
        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} h_inp_icon_shadow_img move:(%d %d %d %d) \n",
            __FUNCTION__, __LINE__, t_rect.i4_left, t_rect.i4_top, t_rect.i4_right, t_rect.i4_bottom)); );


        i4_ret = c_wgl_move(h_inp_icon_shadow_img,
                            &t_rect,
                            WGL_SYNC_AUTO_REPAINT);
    #endif

    #if(NAV_INPUT_SRC_UI_VERTICAL)
        ui4_active_idx = s_u8_active_elem_idx;
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui4_active_idx:%d \n",
            __FUNCTION__, __LINE__, ui4_active_idx )); );
    #else
        ui4_active_idx = 0;
    #endif


        /*update active idx*/
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active(%d)\n",
            __FUNCTION__, __LINE__, ui4_active_idx )); );

        i4_ret = nav_ipts_lst_set_active(pt_this, ui4_active_idx, NAV_IPTS_ACTIVE_TYPE_NO_ACTION, FALSE);
        if(NAVR_OK != i4_ret && NAVR_DELAY_ACTION != i4_ret)
        {
            return NAVR_FAIL;
        }

        /*update highlight idx*/
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_ht(%d, DEFAULT)\n",
            __FUNCTION__, __LINE__, ui4_active_idx )); );

        i4_ret = nav_ipts_lst_set_ht(pt_this, ui4_active_idx, NAV_IPTS_HT_TYPE_DEFAULT);
        NAV_CHK_FAIL(i4_ret);
    }

    /*update pt_this current status */
    {
        /*keep current status*/
        i4_ret = a_tv_get_mode(&e_tv_mode);
        NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);


        /*get active group*/
        i4_ret = a_tv_get_isl_rec_by_win_id(e_grp, &t_isl_active);
        NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);

        /*get other group*/
        if(TV_MODE_TYPE_NORMAL != e_tv_mode)
        {
            i4_ret = a_tv_get_isl_rec_by_win_id((TV_WIN_ID_MAIN == e_grp) ? TV_WIN_ID_SUB : TV_WIN_ID_MAIN,
                                                &t_isl_other);
            NAV_CHK_FAIL(TVR_OK == i4_ret ? NAVR_OK : i4_ret);
        }

        pt_this->e_grp = e_grp;
        pt_this->e_tv_mode = e_tv_mode;
        pt_this->ui1_grp_src_id = t_isl_active.ui1_id;
        pt_this->ui1_other_grp_src_id = (TV_MODE_TYPE_NORMAL != e_tv_mode) ? t_isl_other.ui1_id : 0xFF;

    }


  #if(/*!NAV_INPUT_SRC_UI_VERTICAL*/1)
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_update_toast_list_text()\n", __FUNCTION__, __LINE__ )); );
    _nav_ipts_lst_update_toast_list_text(pt_this, e_grp, b_force);
  #endif

#ifdef APP_TTS_SUPPORT
    {
        nav_ipts_lst_tts_play_stop(TRUE,t_g_toast_param.w2s_msg_t.w2s_str[ui4_active_idx]);
    }
#endif

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} --- END \n",
        __FUNCTION__, __LINE__ )); );

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_reset_close_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_reset_close_timer(
    _NAV_IPTS_LIST_MEMBER_T*                pt_this,
    BOOL                                    b_stop_only)
{
    INT32                                   i4_ret = NAVR_OK;

    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} b_stop_only:%d \n",
        __FUNCTION__, __LINE__, b_stop_only )); );

    /*check init flag*/
    _NAV_IPTS_LST_ACT_IF_UI_NOT_INIT(pt_this,  return NAVR_NOT_ALLOW);

#if( NAV_IPTS_LST_CLOSE_TIMER_EN )
    if (c_handle_valid(pt_this->h_close_timer) == FALSE)
    {
        NAV_CHK_FAIL(NAVR_INV_HANDLE);
    }
    i4_ret = c_timer_stop(pt_this->h_close_timer);
    NAV_CHK_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret );

    if(_NAV_IPTS_LIST_STOP_TIMER == b_stop_only)
    {
        return NAVR_OK;
    }

    NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} h_close_timer start timeout=%d \n",
        __FUNCTION__, __LINE__, NAV_IPTS_LST_CLOSE_DUR )); );
    i4_ret = c_timer_start(pt_this->h_close_timer,
                           NAV_IPTS_LST_CLOSE_DUR,
                           X_TIMER_FLAG_ONCE,
                           _nav_ipts_lst_autoclose_cb,
                           pt_this);
    NAV_CHK_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret );
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_autoclose_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_lst_autoclose_cb(
    HANDLE_T                           h_timer,
    VOID*                              pv_this)
{
    /*post a message to itself*/
    nav_request_context_switch(_nav_ipts_lst_autoclose_msg_hdlr,
                               pv_this,
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_autoclose_msg_hdlr
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_lst_autoclose_msg_hdlr(
    VOID*                                    pv_this,
    VOID*                                    pv_unused2,
    VOID*                                    pv_unused3)
{
    INT32                                    i4_ret;
    _NAV_IPTS_LIST_MEMBER_T*                 pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_this;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n",
        __FUNCTION__, __LINE__ )); );

    if(pt_this && pt_this->b_is_opened)
    {
        /*check init flag*/
        _NAV_IPTS_LST_ACT_IF_UI_NOT_INIT(pt_this, return);

        i4_ret = nav_ipts_lst_close(pt_this);
        if(NAVR_OK == i4_ret && pt_this->pf_autoclose_nfy)
        {
            pt_this->pf_autoclose_nfy(pt_this, pt_this->pv_tag);
        }
    }
}

VOID nav_ipts_list_manual_close(VOID)
{
    if(NULL != pt_ipts_list)
    {
        if(pt_ipts_list->b_is_opened)
        {
            NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_close_timer(,%d) \n",
                __FUNCTION__, __LINE__, _NAV_IPTS_LIST_RESET_TIMER )); );
            _nav_ipts_lst_reset_close_timer(pt_ipts_list, _NAV_IPTS_LIST_RESET_TIMER);
        }
    }
}

BOOL nav_ipts_list_is_running(VOID)
{
    if(NULL != pt_ipts_list)
        return pt_ipts_list->b_is_opened;
    else
        return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_frame_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_frame_nfy_fct(
    HANDLE_T                             h_widget,
    UINT32                               ui4_msg,
    VOID*                                pv_param1,
    VOID*                                pv_param2)
{
    BOOL                                 b_to_default = TRUE;

    switch(ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T                     h_child_widget = (HANDLE_T) pv_param1;
            WGL_NOTIFY_DATA_T*           pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;
            _NAV_IPTS_LIST_MEMBER_T*     pt_this;
            VOID*                        pv_tag;
            INT32                        i4_ret;

            /*check source and get necessary info*/
            switch(pt_wgl_nfy_data->ui4_nc_code)
            {
            case WGL_NC_GL_KEY_DOWN:
                {
                    /* dispatch 3rd widget hotkey to default key handler */
                    if (pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_NETFLIX ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_AMAZON ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_MGO ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_VUDU ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_WIDGET ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_IHEART_RADIO ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_WATCHFREE ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_REDBOX ||
                        pt_wgl_nfy_data->u.t_key.ui4_key_code == BTN_HAYSTACK)
                    {
                        break;
                    }

                    i4_ret = c_handle_get_tag(h_widget, &pv_tag);
                    NAV_CHK_FAIL(i4_ret);

                    if(NULL == pv_tag)
                    {
                        return NAVR_INV_ARG;
                    }

                    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_tag;

                    /*check init flag*/
                    _NAV_IPTS_LST_ACT_IF_UI_NOT_INIT(pt_this, break);

                    /*check notify source*/
                    if(h_child_widget != pt_this->h_listbox)
                    {
                        break;
                    }

                    b_to_default = FALSE;
                }
                break;

            default:
                break;
            }

            /*continue or call default widget procedure*/
            if(b_to_default)
            {
                break;
            }

            /*handle notify*/
            switch(pt_wgl_nfy_data->ui4_nc_code)
            {
            case WGL_NC_GL_KEY_DOWN:
                {
                    _NAV_IPTS_LST_CHECK_REMAP(pt_wgl_nfy_data->u.t_key.ui4_key_code);

                    _nav_ipts_lst_handle_key(pt_this,
                                             pt_wgl_nfy_data->u.t_key.ui4_key_code,
                                             pt_wgl_nfy_data->u.t_key.ui4_key_state);
                }
                break;

            default:
                break;
            }
        }
        break;

    default:
        break;
    }

    if(b_to_default)
    {
        return c_wgl_default_msg_proc(h_widget,
                                      ui4_msg,
                                      pv_param1,
                                      pv_param2);
    }

    return WGLR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_init_ui
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_init_ui(
    _NAV_IPTS_LIST_MEMBER_T*    pt_this)
{
    INT32                       i4_ret;
    UINT8                       ui1_i = 0;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this:0x%X \n",
        __FUNCTION__, __LINE__, (UINT32)pt_this )); );

    if(pt_this->b_ui_init)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this->b_ui_init:%d => return\n",
            __FUNCTION__, __LINE__, pt_this->b_ui_init )); );

        return NAVR_OK;
    }

    do
    {
         /*creat timer*/
        {
        #if( NAV_IPTS_LST_CLOSE_TIMER_EN )
            if (c_handle_valid(pt_this->h_close_timer) == TRUE)
            {
                c_timer_delete(pt_this->h_close_timer);
            }

            pt_this->h_close_timer    = NULL_HANDLE;

            i4_ret = c_timer_create(&pt_this->h_close_timer);
            NAV_BREAK_ON_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);
        #endif

        #if(NAV_IPTS_LST_SELECT_TIMER_EN)
            if (c_handle_valid(pt_this->h_select_timer) == TRUE)
            {
                c_timer_delete(pt_this->h_select_timer);
            }

            pt_this->h_select_timer    = NULL_HANDLE;

            i4_ret = c_timer_create(&pt_this->h_select_timer);
            NAV_BREAK_ON_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);
        #endif
        }

        /*init image*/
        i4_ret = _nav_ipts_lst_image_create(pt_this);
        NAV_BREAK_ON_FAIL(i4_ret);

        /*init frame*/
        i4_ret = _nav_ipts_lst_frame_create(pt_this, pt_this->t_lazy_info.h_parent, pt_this->t_lazy_info.i4_frame_offset_x, pt_this->t_lazy_info.i4_frame_offset_y);
        NAV_BREAK_ON_FAIL(i4_ret);

        /*init listbox*/
        DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} e_bar_type:%d\n", __FUNCTION__, __LINE__, pt_this->e_bar_type ));
        i4_ret = _nav_ipts_lst_listbox_create(pt_this, pt_this->t_lazy_info.e_color_type);
        NAV_BREAK_ON_FAIL(i4_ret);

#ifdef APP_NAV_IPTS_LST_CUSTOM
        /**/
        i4_ret = nav_ipts_lst_custom_init(pt_this->h_frame, pt_this->h_listbox, &pt_this->pv_custom_data);
        NAV_BREAK_ON_FAIL(i4_ret);

        /**/
        i4_ret = nav_ipts_lst_custom_load_skin(pt_this->pv_custom_data, pt_this->h_frame, pt_this->h_listbox);
        NAV_BREAK_ON_FAIL(i4_ret);
#endif

        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} set pt_this->b_ui_init = TRUE\n",
            __FUNCTION__, __LINE__ )); );
        pt_this->b_ui_init = TRUE;

        c_memset (&at_crnt_ht_element, 0, sizeof(_NAV_IPTS_LST_CRNT_HT_INFO_T));

        /*sync elements*/
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_update_elems()\n",
            __FUNCTION__, __LINE__ )); );
        i4_ret = _nav_ipts_lst_update_elems(pt_this, pt_this->e_grp, TRUE);
        NAV_BREAK_ON_FAIL(i4_ret);

        for(ui1_i = 0; ui1_i < 4; ui1_i++)
        {
            m_aui4_fac_trigger_key[ui1_i] = aui4_fac_trigger_key[ui1_i];
        }

        return NAVR_OK;

    } while(0);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_deinit_ui() \n",
        __FUNCTION__, __LINE__ )); );

    _nav_ipts_lst_deinit_ui(pt_this);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_deinit_ui
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_ipts_lst_deinit_ui(
    _NAV_IPTS_LIST_MEMBER_T*    pt_this)
{
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this:0x%X \n",
        __FUNCTION__, __LINE__, (UINT32)pt_this )); );

#ifdef APP_NAV_IPTS_LST_CUSTOM
    /**/
    nav_ipts_lst_custom_deinit(pt_this->pv_custom_data);

#endif

    /*free timer*/
#if( NAV_IPTS_LST_CLOSE_TIMER_EN )
    if(TRUE == c_handle_valid(pt_this->h_close_timer))
    {
        c_timer_delete(pt_this->h_close_timer);
    }
    pt_this->h_close_timer    = NULL_HANDLE;
#endif

#if(NAV_IPTS_LST_SELECT_TIMER_EN)
    if(TRUE == c_handle_valid(pt_this->h_select_timer))
    {
        c_timer_delete(pt_this->h_select_timer);
    }
    pt_this->h_select_timer    = NULL_HANDLE;
#endif

    /*free content indicator */
    if(TRUE == c_handle_valid(pt_this->h_indctr))
    {
        a_cnt_indctr_destroy(pt_this->h_indctr);
    }

    /*free listbox*/
    if(TRUE == c_handle_valid(pt_this->h_listbox))
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_destroy_widget(pt_this->h_listbox)\n",
            __FUNCTION__, __LINE__ )); );
        c_wgl_destroy_widget(pt_this->h_listbox);
    }

    /*free frame*/
    if(TRUE == c_handle_valid(pt_this->h_frame))
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} c_wgl_destroy_widget(pt_this->h_frame)\n",
            __FUNCTION__, __LINE__ )); );

        c_wgl_destroy_widget(pt_this->h_frame);
    }

    /*free images*/
    if(TRUE == c_handle_valid(pt_this->h_listbox_bk_img))
    {
        c_wgl_img_tpl_destroy(pt_this->h_listbox_bk_img);
    }
    if(TRUE == c_handle_valid(pt_this->h_listbox_ht_img))
    {
        c_wgl_img_tpl_destroy(pt_this->h_listbox_ht_img);
    }
    if(TRUE == c_handle_valid(pt_this->h_disable_img))
    {
        c_wgl_img_tpl_destroy(pt_this->h_disable_img);
    }
    if(TRUE == c_handle_valid(pt_this->h_disable_ht_img))
    {
        c_wgl_img_tpl_destroy(pt_this->h_disable_ht_img);
    }
    if(TRUE == c_handle_valid(pt_this->h_active_img))
    {
        c_wgl_img_tpl_destroy(pt_this->h_active_img);
    }
    if(TRUE == c_handle_valid(pt_this->h_active_ht_img))
    {
        c_wgl_img_tpl_destroy(pt_this->h_active_ht_img);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_deinit_ui
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_lazy_init(
    _NAV_IPTS_LIST_MEMBER_T*    pt_this)
{
    INT32                       i4_ret;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} pt_this:0x%X\n",
        __FUNCTION__, __LINE__, pt_this )); );

    i4_ret = _nav_ipts_lst_init_ui(pt_this);
    if(NAVR_OK != i4_ret)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}Error: _nav_ipts_lst_init_ui() failed, call nav_ipts_lst_free()\n",
            __FUNCTION__, __LINE__ )); );

        nav_ipts_lst_free(pt_this);
        return i4_ret;
    }

    i4_ret = nav_ipts_ls_info_init(pt_this);
    if(NAVR_OK != i4_ret)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}Error: nav_ipts_ls_info_init() failed\n",
            __FUNCTION__, __LINE__ )); );

        nav_ipts_lst_info_free(pt_this);
        return i4_ret;
    }

    /*sync elements*/
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call _nav_ipts_lst_update_elems()\n",
        __FUNCTION__, __LINE__ )); );
    i4_ret = _nav_ipts_lst_update_elems(pt_this, pt_this->e_grp, TRUE);
    if(NAVR_OK != i4_ret)
    {
        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d}Error: _nav_ipts_lst_update_elems() failed\n",
            __FUNCTION__, __LINE__ )); );

        return i4_ret;
    }

    /*free title buffer*/
    if(pt_this->t_lazy_info.w2s_grp)
    {
        c_mem_free(pt_this->t_lazy_info.w2s_grp);
        pt_this->t_lazy_info.w2s_grp = NULL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ipts_lst_handle_key
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ipts_lst_handle_key(
    _NAV_IPTS_LIST_MEMBER_T*    pt_this,
    UINT32                      ui4_keycode,
    UINT32                      ui4_key_state)
{
    UINT32                       ui4_key_act_next, ui4_key_act_next_2, ui4_key_act_prev, ui4_key_act_crnt_ht, ui4_key_next_ht, ui4_key_prev_ht, ui4_key_apply_close, ui4_key_close;
    UINT8                        ui1_idx, ui1_new;
    INT32                        i4_ret, i;
    BOOL                         b_force_select = FALSE;

    UINT8 u8_cur_highlight_index = 0;
    UINT8 u8_cur_active_index = 0;


    if( pt_this == NULL )
    {
        DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} Error: (pt_this==NULL), ui4_keycode:0x%X, ui4_key_state:%d\n",
            __FUNCTION__, __LINE__, ui4_keycode, ui4_key_state ));
        return NAVR_FAIL;
    }

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("\n\n[NAV][INPUT_SRC][KEY]{%s,%d}====================================================================== \n",
        __FUNCTION__, __LINE__, ui4_keycode, ui4_key_state )); );
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui4_keycode:0x%X, ui4_key_state:%d\n",
        __FUNCTION__, __LINE__, ui4_keycode, ui4_key_state )); );

    /* Step3 move toast list text */
    if((nav_get_key_source() == KEY_SRC_FRONT_PANEL)&&a_nav_get_panel_key_disable_status())
    {
        DBG_LOG_PRINT(("%s_%d For panel key will be disable by odm Amtran \n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }

    NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} pt_this->e_key_grp:%d\n",
        __FUNCTION__, __LINE__, pt_this->e_key_grp )); );

    if(NAV_IPTS_LST_PRI_KEY_GROUP == pt_this->e_key_grp)
    {
        ui4_key_act_next = NAV_IPTS_LST_PRI_KEY_ACT_NEXT;
        ui4_key_act_next_2 = NAV_IPTS_LST_PRI_KEY_ACT_NEXT_2;
        ui4_key_act_prev = NAV_IPTS_LST_PRI_KEY_ACT_PREV;
        ui4_key_act_crnt_ht = NAV_IPTS_LST_PRI_KEY_ACT_CRNT_HT;
        ui4_key_next_ht = NAV_IPTS_LST_PRI_KEY_NEXT_HT;
        ui4_key_prev_ht = NAV_IPTS_LST_PRI_KEY_PREV_HT;
        ui4_key_apply_close = NAV_IPTS_LST_PRI_KEY_APPLY_CLOSE;
        ui4_key_close = NAV_IPTS_LST_PRI_KEY_CLOSE;

        NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} PRI valid key: %X %X %X %X %X %X %X %X\n",
            __FUNCTION__, __LINE__,
            ui4_key_act_next, ui4_key_act_next_2, ui4_key_act_prev, ui4_key_act_crnt_ht,
            ui4_key_next_ht, ui4_key_prev_ht, ui4_key_apply_close, ui4_key_close
            )); );
    }
    else
    {
        ui4_key_act_next = NAV_IPTS_LST_SEC_KEY_ACT_NEXT;
        ui4_key_act_next_2 = NAV_IPTS_LST_SEC_KEY_ACT_NEXT_2;
        ui4_key_act_prev = NAV_IPTS_LST_SEC_KEY_ACT_PREV;
        ui4_key_act_crnt_ht = NAV_IPTS_LST_SEC_KEY_ACT_CRNT_HT;
        ui4_key_next_ht = NAV_IPTS_LST_SEC_KEY_NEXT_HT;
        ui4_key_prev_ht = NAV_IPTS_LST_SEC_KEY_PREV_HT;
        ui4_key_apply_close = NAV_IPTS_LST_SEC_KEY_APPLY_CLOSE;
        ui4_key_close = NAV_IPTS_LST_SEC_KEY_CLOSE;
        NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} SEC valid key: %X %X %X %X %X %X %X %X\n",
            __FUNCTION__, __LINE__,
            ui4_key_act_next, ui4_key_act_next_2, ui4_key_act_prev, ui4_key_act_crnt_ht,
            ui4_key_next_ht, ui4_key_prev_ht, ui4_key_apply_close, ui4_key_close
            )); );

    }

    if (pt_this->ui1_fac_trigger_idx >= sizeof (m_aui4_fac_trigger_key) / sizeof(UINT32))
    {
        DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} Error: \n",  __FUNCTION__, __LINE__ ));
        return (NAVR_FAIL);
    }

    if((ui4_key_act_next == ui4_keycode) ||
       (ui4_key_act_next_2 == ui4_keycode) ||
       (ui4_key_act_prev == ui4_keycode) ||
       (ui4_key_act_crnt_ht == ui4_keycode) ||
       (ui4_key_next_ht == ui4_keycode) ||
       (ui4_key_prev_ht == ui4_keycode) ||
       (ui4_key_apply_close == ui4_keycode))
    {
        NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} Need handle: ui4_keycode:0x%X, ui4_key_state:%d\n",
            __FUNCTION__, __LINE__, ui4_keycode, ui4_key_state )); );

        if(pt_this->b_wait_for_virtual_src_switch)  /*waiting for selecting virtual input*/
        {
            DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} b_wait_for_virtual_src_switch:%d \n",
                __FUNCTION__, __LINE__, pt_this->b_wait_for_virtual_src_switch  ));
            return NAVR_OK;
        }

        if(WGL_KEY_STATE_UP != ui4_key_state)
        {

            /*get current highlight*/
            i4_ret = nav_ipts_lst_get_ht(pt_this, &u8_cur_highlight_index);
            if(NAVR_OK != i4_ret)
            {
                return i4_ret;
            }
            NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} u8_cur_highlight_index:%d\n",
                __FUNCTION__, __LINE__, u8_cur_highlight_index )); );


            /*get current active*/
            i4_ret = nav_ipts_lst_get_active(pt_this, &u8_cur_active_index);
            if(NAVR_OK != i4_ret)
            {
                return i4_ret;
            }
            NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} u8_cur_active_index:%d\n",
                __FUNCTION__, __LINE__, u8_cur_active_index )); );


            if((ui4_key_act_crnt_ht == ui4_keycode) ||
               (ui4_key_next_ht == ui4_keycode) ||
               (ui4_key_prev_ht == ui4_keycode) ||
               (ui4_key_act_prev == ui4_keycode) ||
               ((pt_this->b_activate_next_ht) && (ui4_key_act_next == ui4_keycode)) ||
               ((pt_this->b_activate_next_ht) && (ui4_key_act_next_2 == ui4_keycode)) ||
               (ui4_key_apply_close == ui4_keycode))
            {
                /*get current highlight*/
              #if 1
                ui1_idx = u8_cur_highlight_index;
              #else
                i4_ret = nav_ipts_lst_get_ht(pt_this, &ui1_idx);
                if(NAVR_OK != i4_ret)
                {
                    return i4_ret;
                }
              #endif
                NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} current highlight ui1_idx = %d\n",
                    __FUNCTION__, __LINE__, ui1_idx )); );
            }
            else
            {
                /*get current active*/
              #if 1
                ui1_idx = u8_cur_active_index;
              #else
                i4_ret = nav_ipts_lst_get_active(pt_this, &ui1_idx);
                if(NAVR_OK != i4_ret)
                {
                    return i4_ret;
                }
              #endif
                NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} current active ui1_idx = %d\n",
                  __FUNCTION__, __LINE__, ui1_idx )); );
            }


            BOOL repeat_do = FALSE;
            ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
            i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
            if (APP_CFGR_OK != i4_ret)
            {
                DBG_ERROR(("[RETLMOD_SKIP_CAST] %s LINE=%d a_cfg_custom_get_retail_mode_setting() failed !\n", __FILE__, __LINE__));
            }

            /*get next or previous*/
            if((ui4_key_act_crnt_ht == ui4_keycode) ||
               (ui4_key_apply_close == ui4_keycode))
            {
                ui1_new = ui1_idx;
                NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui1_idx:%d, ui1_new = %d\n",
                    __FUNCTION__, __LINE__, ui1_idx, ui1_new )); );

                b_is_select_dev_in_lst = TRUE;
            }
            else if((ui4_key_act_next == ui4_keycode) ||
                    (ui4_key_act_next_2 == ui4_keycode) ||
                    (ui4_key_next_ht == ui4_keycode))
            {
                b_is_select_dev_in_lst = TRUE;
                do {
                    if (repeat_do)
                    {
                        ui1_idx = ui1_new;
                    }

                    ui1_new = (UINT8)(((ui1_idx + 1) >= pt_this->ui1_max_elems) ? 0 : (ui1_idx + 1));
                    NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui1_idx:%d, ui1_new = %d\n",
                        __FUNCTION__, __LINE__, ui1_idx, ui1_new )); );

                    if((ui4_key_act_next == ui4_keycode) ||
                       (ui4_key_act_next_2 == ui4_keycode) ||
                       ((ui4_key_next_ht == ui4_keycode) &&
                        (FALSE == pt_this->b_ht_disabled || FALSE == pt_this->b_show_disabled)))
                    {
                        for(i = 1; i < pt_this->ui1_max_elems; i++)
                        {
                            if(FALSE == pt_this->at_elem[ui1_new].b_is_disabled)
                            {
                                break;
                            }

                            ui1_new = (UINT8)(((ui1_new + 1) >= pt_this->ui1_max_elems) ? 0 : (ui1_new + 1));
                            NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui1_idx:%d, ui1_new = %d\n",
                                __FUNCTION__, __LINE__, ui1_idx, ui1_new )); );

                        }

                        /*find new?*/
                        if(i >= pt_this->ui1_max_elems)
                        {
                            return NAVR_OK;  /*cannot find anyone enabled*/
                        }
                    }
                    repeat_do = FALSE;

                    if ( ACFG_RETAIL_MODE_NORMAL == retm_status )
                    {
                        ISL_REC_T tmp_isl_rec;
                        i4_ret = a_isl_get_rec_by_id(pt_this->at_elem[ui1_new].ui1_id, &tmp_isl_rec);
                        if (ISLR_OK == i4_ret)
                        {
                            if (INP_SRC_TYPE_VTRL == tmp_isl_rec.e_src_type &&
                                  (DEV_VTRL_CAST == tmp_isl_rec.t_avc_info.e_video_type))
                            {
                                repeat_do = TRUE;
                                //retm_status = ACFG_RETAIL_MODE_HOME;
                            }
                        }
                    }
                }while (repeat_do);

                /*same idx*/
                if(ui1_new == ui1_idx)
                {
                    DBG_LOG_PRINT(("[isl_func] %s %d, ui1_new == ui1_idx[%d] \n",__FUNCTION__,__LINE__,ui1_new));
                    return NAVR_OK;
                }
            }
            else /*ui4_key_act_prev || ui4_key_prev_ht*/
            {
                do {
                    if (repeat_do)
                    {
                        ui1_idx = ui1_new;
                    }
                    ui1_new = (UINT8)((ui1_idx > 0) ? (ui1_idx - 1) :
                                              ((pt_this->ui1_max_elems > 0) ? (pt_this->ui1_max_elems - 1) : 0));
                    NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui1_idx:%d, ui1_new = %d\n",
                        __FUNCTION__, __LINE__, ui1_idx, ui1_new )); );

                    if((ui4_key_act_prev == ui4_keycode) ||
                       ((ui4_key_prev_ht == ui4_keycode) &&
                        (FALSE == pt_this->b_ht_disabled || FALSE == pt_this->b_show_disabled)))
                    {
                        for(i = 1; i < pt_this->ui1_max_elems; i++)
                        {
                            if(FALSE == pt_this->at_elem[ui1_new].b_is_disabled)
                            {
                                break;
                            }

                            ui1_new = (UINT8)((ui1_new > 0) ? (ui1_new - 1) : (pt_this->ui1_max_elems - 1));
                            NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui1_idx:%d, ui1_new = %d\n",
                                __FUNCTION__, __LINE__, ui1_idx, ui1_new )); );
                        }

                        /*find new?*/
                        if(i >= pt_this->ui1_max_elems)
                        {
                            return NAVR_OK;  /*cannot find anyone enabled*/
                        }
                    }
                    repeat_do = FALSE;
                    if ( ACFG_RETAIL_MODE_NORMAL == retm_status )
                    {
                        ISL_REC_T tmp_isl_rec;
                        i4_ret = a_isl_get_rec_by_id(pt_this->at_elem[ui1_new].ui1_id, &tmp_isl_rec);
                        if (ISLR_OK == i4_ret)
                        {
                            if (INP_SRC_TYPE_VTRL == tmp_isl_rec.e_src_type &&
                                  (DEV_VTRL_CAST == tmp_isl_rec.t_avc_info.e_video_type))
                            {
                                repeat_do = TRUE;
                                //retm_status = ACFG_RETAIL_MODE_HOME;
                            }
                        }
                    }
                }while (repeat_do);

                /*same idx*/
                if(ui1_new == ui1_idx)
                {
                    DBG_LOG_PRINT(("[isl_func] %s %d, ui1_new == ui1_idx[%d] \n",__FUNCTION__,__LINE__,ui1_new));
                    return NAVR_OK;
                }
            }

            /* Force BTN_SELECT to select source. */
            if (ui4_keycode == ui4_key_act_crnt_ht)
            {
                b_force_select = TRUE;
            }

    #if (NAV_INPUT_SRC_UI_VERTICAL)
            if( (ui4_key_act_prev == ui4_keycode)
              ||(ui4_key_act_next_2 == ui4_keycode)
              )
            {
                _s_b_navigate_by_up_down = TRUE;
                NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} _s_b_navigate_by_up_down = TRUE;\n",
                    __FUNCTION__, __LINE__ )); );
            }
    #endif

            /* Stop delay-select timer. */
            NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_select_timer(,stop=%d) \n",
                __FUNCTION__, __LINE__, _NAV_IPTS_LIST_STOP_TIMER )); );
            _nav_ipts_lst_reset_select_timer(pt_this, _NAV_IPTS_LIST_STOP_TIMER);

            // Reset close timer
            NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_close_timer(,stop=%d) \n",
                __FUNCTION__, __LINE__, _NAV_IPTS_LIST_RESET_TIMER )); );
            _nav_ipts_lst_reset_close_timer(pt_this, _NAV_IPTS_LIST_RESET_TIMER);


            /*activate next or previous*/
            if((ui4_key_act_crnt_ht != 0) &&
               ((ui4_key_next_ht == ui4_keycode) ||
                (ui4_key_prev_ht == ui4_keycode)))
            {
                // Only move Highlight, no need timer to change source...
                NAV_IPTS_HT_TYPE_T    e_ht_type;

                if (ui4_key_next_ht == ui4_keycode)
                {
                    e_ht_type = NAV_IPTS_HT_TYPE_NEXT;
                    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui4_keycode:0x%X, NAV_IPTS_HT_TYPE_NEXT\n", __FUNCTION__, __LINE__, ui4_keycode )); );
                }
                else
                {
                    e_ht_type = NAV_IPTS_HT_TYPE_PREV;
                    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui4_keycode:0x%X, NAV_IPTS_HT_TYPE_PREV\n", __FUNCTION__, __LINE__, ui4_keycode )); );
                }

                NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_ht(%d, type:%d)\n",
                    __FUNCTION__, __LINE__, ui1_new, e_ht_type )); );

                i4_ret = nav_ipts_lst_set_ht(pt_this, ui1_new, e_ht_type);
            }
            else
            {
                // Move Highlight, and enablt select timer to change source...
                if(FALSE == pt_this->at_elem[ui1_new].b_is_disabled)
                {
                    if (ui4_key_act_next == ui4_keycode ||
                        ui4_key_act_next_2 == ui4_keycode ||
                        ui4_key_act_prev == ui4_keycode)
                    {
                        if (ui4_key_act_prev == ui4_keycode)
                        {
                            NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui4_keycode:0x%X, NAV_IPTS_HT_TYPE_PREV\n", __FUNCTION__, __LINE__, ui4_keycode )); );

                            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_ht(%d, PREV)\n",
                                __FUNCTION__, __LINE__, ui1_new )); );

                            nav_ipts_lst_set_ht(pt_this, ui1_new, NAV_IPTS_HT_TYPE_PREV);
                        }
                        else
                        {
                            NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} ui4_keycode:0x%X, NAV_IPTS_HT_TYPE_NEXT\n", __FUNCTION__, __LINE__, ui4_keycode )); );

                            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_ht(%d, NEXT)\n",
                                __FUNCTION__, __LINE__, ui1_new )); );

                            nav_ipts_lst_set_ht(pt_this, ui1_new, NAV_IPTS_HT_TYPE_NEXT);
                        }

                    #if(NAV_INPUT_SRC_UI_USE_WDK)
                        if(b_PowerON_on_isl_flag)
                        {
                            if(pt_this->at_elem[ui1_new].e_func_type == E_FUNC_ELEMENT_POWER_OFF)
                            {
                                ISL_LOG(_ISL_LOG_TYPE_FUNC,("[isl_func] %s(%d) Show notification\n", __FUNCTION__, __LINE__));
                                wdk_set_help_toast_visible(TRUE, &t_g_wdk_view);
                            }
                            else
                            {
                                wdk_set_help_toast_visible(FALSE, &t_g_wdk_view);
                            }
                        }
                        else
                        {
                            wdk_set_help_toast_visible(FALSE, &t_g_wdk_view);
                        }
                    #endif

                        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active(%d,DELAY )\n",
                            __FUNCTION__, __LINE__, ui1_new )); );
                        i4_ret = nav_ipts_lst_set_active(pt_this, ui1_new, NAV_IPTS_ACTIVE_TYPE_DELAY, b_force_select);
                        if(NAVR_DELAY_ACTION == i4_ret)
                        {
                            NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} set ->b_wait_for_virtual_src_switch=TRUE\n",
                                __FUNCTION__, __LINE__ )); );
                            pt_this->b_wait_for_virtual_src_switch = TRUE;
                            i4_ret = NAVR_OK;
                        }
                    }
                    else if (m_aui4_fac_trigger_key[pt_this->ui1_fac_trigger_idx] != ui4_keycode)
                    {
                        NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call nav_ipts_lst_set_active(%d)\n",
                            __FUNCTION__, __LINE__, ui1_new )); );

                        i4_ret = nav_ipts_lst_set_active(pt_this, ui1_new, NAV_IPTS_ACTIVE_TYPE_IMMEDIATE, b_force_select);
                    }
                }
                else
                {
                    i4_ret = NAVR_OK;
                }
            }

            if(NAVR_OK != i4_ret)
            {
                return i4_ret;
            }

    #ifdef APP_TTS_SUPPORT
           nav_ipts_lst_tts_play_stop(TRUE,t_g_toast_param.w2s_msg_t.w2s_str[ui1_new]);
    #endif

            if(ui4_key_apply_close == ui4_keycode)
            {
                _nav_ipts_lst_autoclose_msg_hdlr(pt_this, NULL, NULL);
            }
        }
    }
    else if (m_aui4_fac_trigger_key[pt_this->ui1_fac_trigger_idx] == ui4_keycode)  /* Enter factory menu*/
    {
        NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} m_aui4_fac_trigger_key\n",
            __FUNCTION__, __LINE__ )); );

        pt_this->ui1_fac_trigger_idx++;

        if (pt_this->ui1_fac_trigger_idx == sizeof(m_aui4_fac_trigger_key) / sizeof(UINT32))
        {
            return (_nav_ipts_enter_factory_menu(pt_this));
        }
    }
#if( NAV_INPUT_SRC_UI_VERTICAL )
    else if ((UINT32)BTN_CURSOR_LEFT == ui4_keycode || (UINT32)BTN_CURSOR_RIGHT == ui4_keycode)
    {
        NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d}  BTN_CURSOR_LEFT BTN_CURSOR_RIGHT do nothing\n",
            __FUNCTION__, __LINE__ )); );
    }
#endif
    else
    {
        NAV_DEBUG_INPUT_SRC_KEY( DBG_LOG_PRINT(("[NAV][INPUT_SRC][KEY]{%s,%d} <<< else >>> ui4_key_close:0x%X\n",
            __FUNCTION__, __LINE__, ui4_key_close )); );

        if( (ui4_key_close == ui4_keycode) || (BTN_PRG_INFO == ui4_keycode))
        {
            /* Stop delay-select timer. */
            NAV_DEBUG_INPUT_SRC_TIMER( DBG_LOG_PRINT(("[NAV][INPUT_SRC][TIMER]{%s,%d} call _nav_ipts_lst_reset_select_timer(,stop=%d) \n",
                __FUNCTION__, __LINE__, _NAV_IPTS_LIST_STOP_TIMER )); );
            _nav_ipts_lst_reset_select_timer (pt_this, _NAV_IPTS_LIST_STOP_TIMER);

            if(WGL_KEY_STATE_UP != ui4_key_state)
            {
                _nav_ipts_lst_autoclose_msg_hdlr(pt_this, NULL, NULL);
            }
        }
        else if(pt_this->pf_unknown_key_handler)
        {
            pt_this->pf_unknown_key_handler(pt_this,
                                            pt_this->pv_tag,
                                            ui4_keycode,
                                            ui4_key_state);
        }
    }

    if(WGL_KEY_STATE_UP != ui4_key_state)
    {
        /*reset timer*/
        nav_bnr_timer_reload(NULL_HANDLE,0,(NAV_BNR_STATE_TIMER_OPER_TYPE_T)0);
    }

    return NAVR_OK;
}

static INT32 _nav_ipts_enter_factory_menu(
    _NAV_IPTS_LIST_MEMBER_T*     pt_this)
{
    INT32                        i4_ret;

    pt_this->ui1_fac_trigger_idx = 0;

    DBG_INFO(("\n------------[_nav_ipts_enter_factory_menu]------------\n"));

    i4_ret = a_menu_enter_factory_menu();
    if (MENUR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): a_menu_enter_factory_menu() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

#if defined APP_CEC2_SUPPORT && defined APP_CEC_SUPPORT && defined APP_CEC_MENU
extern INT32 a_nav_ipts_get_dev_pa_in_input_list(UINT16* pui2_pa_orig, UINT16* pui2_pa_next)
{
    if ((pui2_pa_orig == NULL) || (pui2_pa_next == NULL))
    {
        return NAVR_FAIL;
    }

    *pui2_pa_orig = ui2_original_pa;
    *pui2_pa_next = ui2_next_pa;

    return NAVR_OK;
}
INT32 a_nav_ipts_get_dev_pa_in_input_list_by_hlt_idx(UINT16 ui2_hlt_index, UINT16* pui2_pa)
{

    CEC_DEV_LST_T               t_lst;
    UINT8                       ui1_count;
    UTF16_T 			w2s_text[APP_CFG_CUSTOM_INP_NAME_LEN] = {0};

    c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
    a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

    if (t_lst.ui1_dev_num == 0)
    {
        return NAVR_OK;
    }

    if(pt_ipts_list == NULL_HANDLE)
    {
        return NAVR_OK;
    }

    if(pt_ipts_list->h_listbox == NULL_HANDLE)
    {
        return NAVR_OK;
    }

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_GET_ITEM_TEXT\n", __FUNCTION__, __LINE__ )); );

    c_wgl_do_cmd(pt_ipts_list->h_listbox,
			  WGL_CMD_LB_GET_ITEM_TEXT,
			  WGL_PACK_2(ui2_hlt_index,1),
			  WGL_PACK(w2s_text));

    for (ui1_count = 0; ui1_count < t_lst.ui1_dev_num; ui1_count++)
    {
        if(0 == c_uc_w2s_strncmp(w2s_text, t_lst.at_dev_info[ui1_count].aw2_osd_name, c_uc_w2s_strlen(t_lst.at_dev_info[ui1_count].aw2_osd_name)))
        {
          *pui2_pa = t_lst.at_dev_info[ui1_count].ui2_pa;

        }
    }

    return NAVR_OK;
}

extern BOOL a_nav_ipts_ist_is_select_dev_in_lst(VOID)
{
    return b_is_select_dev_in_lst;
}

extern VOID a_nav_ipts_lst_is_select_dev_in_lst(BOOL b_select_dev)
{
    b_is_select_dev_in_lst = b_select_dev;
}

#endif
extern INT32 nav_ipts_ist_select_vtrl_input(CHAR* sc_name)
{
    INT32       i4_ret = 0;
    UINT16      ui2_index = 0;
    UTF16_T     w2s_text[24] = {0};
    UINT32      ui4_elem_num = 0;
    UINT16      ui2_id= 0;
    CHAR        s_dsp_name[24];


    i4_ret = c_wgl_do_cmd(pt_ipts_list->h_listbox,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui4_elem_num),
                          NULL);
    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_GET_ELEM_NUM: ui4_elem_num:%d \n",
        __FUNCTION__, __LINE__, ui4_elem_num )); );

    for(ui2_id = 0; ui2_id < ui4_elem_num; ui2_id ++ )
    {
        i4_ret = c_wgl_do_cmd(pt_ipts_list->h_listbox,
                      WGL_CMD_LB_GET_ITEM_TEXT,
                      WGL_PACK_2(0, ui2_id),
                      WGL_PACK(w2s_text));

         c_uc_w2s_to_ps(w2s_text,s_dsp_name,24);
         DBG_INFO(("<NAV INP> file: %s line: %d  %s id %d; s_dsp_name %s  sc_name %s\n",
            __FILE__, __LINE__, __FUNCTION__,ui2_id,s_dsp_name,sc_name));
         if(c_strcmp(s_dsp_name,sc_name) == 0)
         {
            break;
         }


    }
    ui2_index = ui2_id;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_HLT_ELEM: ui2_index:%d \n",
        __FUNCTION__, __LINE__, ui2_index )); );

    i4_ret = c_wgl_do_cmd(pt_ipts_list->h_listbox,
                      WGL_CMD_LB_HLT_ELEM,
                      WGL_PACK(ui2_index),
                      NULL);

    i4_ret = c_wgl_do_cmd(pt_ipts_list->h_listbox,
                      WGL_CMD_LB_SET_INDEX_SEL,
                      WGL_PACK(ui2_index),
                      NULL);

    return i4_ret;
}

INT32 nav_ipts_ls_info_init(_NAV_IPTS_LIST_MEMBER_T* pt_this)
{

    INT32               i4_ret;
    GL_RECT_T           t_rect;
    //WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    GL_COLOR_T          t_color_text = NAV_COLOR(NAV_COLOR_ID_TEXT);
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;
    UINT32              ui4_canvas_w, ui4_canvas_h;
    HANDLE_T            h_canvas = pt_this->t_lazy_info.h_parent;//t_g_navigator.t_nav_ctx.t_gui_res.h_canvas;

    c_wgl_get_canvas_size(h_canvas, &ui4_canvas_w, &ui4_canvas_h);
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      0,
                      ui4_canvas_h-55,//t_g_navigator.t_nav_ctx.t_gui_res.ui4_canvas_height - 60,
                      ui4_canvas_w,
                      55
                       );

    /* create frame */
    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 0,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                                 NULL,
                                 &h_ipts_ls_info_fram);
    NAV_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, 0, 0, ui4_canvas_w, 55);

    /* create text */
    i4_ret = c_wgl_create_widget(h_ipts_ls_info_fram,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 220,
                                 (VOID*)( WGL_STL_TEXT_MAX_512 |
                                          WGL_STL_TEXT_MULTILINE |
                                          WGL_STL_TEXT_MAX_DIS_5_LINE|
                                          WGL_STL_GL_NO_BK),
                                 NULL,
                                 &h_ipts_ls_info_text);
    NAV_CHK_FAIL(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd (h_ipts_ls_info_text,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_CENTER_CENTER),
                              NULL);
    NAV_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(h_ipts_ls_info_text,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    NAV_CHK_FAIL(i4_ret);

    t_inset.i4_left     = 10;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_ipts_ls_info_text,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_ipts_ls_info_text,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK((INT32)(-5)),
                          NULL);
    NAV_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(t_fnt_info));

    t_fnt_info.e_font_size = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    c_strncpy(&(t_fnt_info.a_c_font_name[0]), NAV_FONT_NORMAL, WGL_MAX_FONT_NAME);

    i4_ret = c_wgl_do_cmd (h_ipts_ls_info_text,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    NAV_CHK_FAIL(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_color_text;
    t_clr_info.u_color_data.t_standard.t_highlight = t_color_text;
    t_clr_info.u_color_data.t_standard.t_disable = t_color_text;
    i4_ret = c_wgl_do_cmd(h_ipts_ls_info_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    NAV_CHK_FAIL(i4_ret);
/*
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(h_ipts_ls_info_text,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAV_CHK_FAIL(i4_ret);
*/
    i4_ret = c_wgl_do_cmd (h_ipts_ls_info_text,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_INPUT_LIST_DIALOG_CONTENT)),
                      WGL_PACK (c_uc_w2s_strlen (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_INPUT_LIST_DIALOG_CONTENT))));
    NAV_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_ipts_ls_info_fram, WGL_SW_RECURSIVE);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_ipts_ls_info_fram, WGL_SW_HIDE);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_info_timer);
    NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

INT32 nav_ipts_lst_info_free(_NAV_IPTS_LIST_MEMBER_T* pt_this)
{

    /*free timer*/
    if(TRUE == c_handle_valid(h_info_timer))
    {
        c_timer_delete(h_info_timer);
    }

    /*free text*/
    if(TRUE == c_handle_valid(h_ipts_ls_info_text))
    {
        c_wgl_destroy_widget(h_ipts_ls_info_text);
    }

    /*free frame*/
    if(TRUE == c_handle_valid(h_ipts_ls_info_fram))
    {
        c_wgl_destroy_widget(h_ipts_ls_info_fram);
    }

    return NAVR_OK;
}

INT32 nav_ipts_ls_info_show(VOID)
{
    INT32   i4_ret = NAVR_OK;

    if (h_ipts_ls_info_text != NULL_HANDLE)
    {
        i4_ret = c_wgl_do_cmd (h_ipts_ls_info_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_INPUT_LIST_DIALOG_CONTENT)),
                          WGL_PACK (c_uc_w2s_strlen (MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_INPUT_LIST_DIALOG_CONTENT))));
        NAV_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(h_ipts_ls_info_fram, WGL_SW_RECURSIVE);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_ipts_ls_info_fram, NULL, TRUE);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_info_timer,
                  _NAV_INTS_LIST_DLG_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _timer_animation_fct,
                  NULL);

    NAV_LOG_ON_FAIL(i4_ret);

    b_ipts_ls_dialog_show = TRUE;
    return i4_ret;
}

INT32 nav_ipts_ls_info_hide (VOID)
{
    INT32                    i4_ret = NAVR_OK;

    if (b_ipts_ls_dialog_show == FALSE)
    {
        return NAVR_NO_ACTION;
    }

    i4_ret = c_wgl_set_visibility(h_ipts_ls_info_fram, WGL_SW_HIDE_RECURSIVE);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_ipts_ls_info_fram, NULL, TRUE);
    NAV_LOG_ON_FAIL(i4_ret);

    b_ipts_ls_dialog_show = FALSE;
    return NAVR_OK;
}


VOID nav_ipts_get_hlt_full_range_id(UINT16 *pui2_id)
{
    *pui2_id = at_crnt_ht_element.ui2_ht_full_range_bar_id;
    return;
}

static VOID _timer_animation_fct(HANDLE_T  h_timer,
                                 VOID*     pv_tag)
{
    nav_ipts_ls_info_hide();
}

static INT32 _nav_ipts_ls_demo_mode_off(VOID)
{
    ACFG_RETAIL_MODE_T    t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        a_nav_retail_mode_exit();
    }

    return NAVR_OK;
}

#if(NAV_INPUT_SRC_UI_USE_WDK)
static INT32 _nav_ipts_start_animation(
    HANDLE_T            h_anim_move,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    INT32        i4_ret = MENUR_OK;
    GL_RECT_T*   pt_rect_from = NULL;
    GL_RECT_T*   pt_rect_to = NULL;
    WGL_ANIMATION_DATA_T   t_anim_data;
    WGL_ANIM_CONTEXT_T e_anim_context = ANIM_CONTEXT_APP_SYNC;

    /* Get move animation start, end position */
    pt_rect_from = (GL_RECT_T*)pv_param1;
    pt_rect_to   = (GL_RECT_T*)pv_param2;

    /* Check move animation start, end position */
    if ((NULL == pt_rect_from) ||
        (NULL == pt_rect_to))
    {
        return MENUR_INV_ARG;
    }

    /* Check animation handle validation */
    if (NULL_HANDLE == h_anim_move)
    {
        return MENUR_INV_ARG;
    }

    return 0;

    do
    {
        /* Clear animation data */
        c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));

        /* Move animation widget */
        i4_ret = c_wgl_move (h_anim_move,
                             pt_rect_from,
                             WGL_NO_AUTO_REPAINT);
        if (i4_ret != WGLR_OK)
        {
            break;
        }

        /* Stop origional animation firstly */
        i4_ret = c_wgl_end_animation (h_anim_move, NULL, NULL);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
        }

        /* begin animation */
        t_anim_data.ui2_count = 1;

        /* Alloc memory for animation control data */
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));
        if((NULL == t_anim_data.pt_anim_data) ||
           (NULL == t_anim_data.pt_path_mode))
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data,0,sizeof(WGL_ANIM_DATA_INFO));
        c_memset(t_anim_data.pt_path_mode,0,sizeof(WGL_ANIM_PATH_DATA_T));

        /* Initialize animation path mode */
        t_anim_data.ui4_flag = WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
        t_anim_data.pt_path_mode->ui2_anim_type = WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_path_mode->ui2_total_steps = 8;
        t_anim_data.pt_path_mode->ui2_frame_interval = (UINT16)c_wgl_get_tick_interval()*2;
        t_anim_data.pt_path_mode->ui4_start_tick = 0;
        //t_anim_data.pt_path_mode->pf_type_cb = NULL;

        /* Initialize animation data info */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;
        t_anim_data.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_anim_data->u_data.t_move.i2_start_x = pt_rect_from->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_start_y = pt_rect_from->i4_top;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_x   = pt_rect_to->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_y   = pt_rect_to->i4_top;

        t_anim_data.pt_anim_data->pf_type_cb = WGL_ANIM_MOVE_PATH_JUMP;

        /* Set focus to animation widget */
        //c_wgl_set_focus(h_anim_move, WGL_NO_AUTO_REPAINT);

        /* Show animation widget */
        c_wgl_set_visibility(h_anim_move, WGL_SW_NORMAL);

        /* Start animation */
        i4_ret= c_wgl_start_animation(
                                      h_anim_move,
                                      &t_anim_data,
                                      e_anim_context);
        if (i4_ret != WGLR_OK)
        {
            DBG_ERROR(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

    } while(0);

    /* Free memory for animation control data */
    if (t_anim_data.pt_anim_data)
    {
        c_mem_free(t_anim_data.pt_anim_data);
    }

    if (t_anim_data.pt_path_mode)
    {
        c_mem_free(t_anim_data.pt_path_mode);
    }

    return MENUR_OK;
}

static INT32 _nav_ipts_new_list_txt_move(_NAV_IPTS_LIST_MEMBER_T* pt_this, E_TOAST_MOVE_DIR e_move_dir)
{
    INT32               i4_ret = NAVR_OK;
    UINT8               ui1_idx = 0;

    INT32               i4_txt_num = 0;
    INT32               i4_dim = 0;
    GL_RECT_T           t_rect = {0};
    GL_RECT_T           t_rect_end = {0};
    UINT16              ui2_lst_hlt_idx;
    //GL_COLOR_T          t_color = { 128, { 106}, { 106}, { 106}};
    //WGL_COLOR_INFO_T    t_clr_info;
    UINT32              ui4_item_num = 0;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} e_move_dir:%d, \n",
        __FUNCTION__, __LINE__, e_move_dir )); );

#if( NAV_INPUT_SRC_UI_VERTICAL || (NAV_INPUT_SRC_UI_USE_WDK==0) )
    return NAVR_OK;
#endif

    pt_this->ui1_inp_idx_bef_sel = 0;
    if (NULL == pt_this->pt_wdk_view)
    {
        DBG_ERROR(("[INPUT LIST] wdk widget not init\r\n"));
        return NAVR_FAIL;
    }

    i4_txt_num = t_g_toast_param.w2s_msg_t.i4_str_num;

    SET_RECT_BY_SIZE (&t_rect,
                        IPTS_SRC_TOAST_LIST_TXT_ITEM_X,
                        IPTS_SRC_TOAST_LIST_TXT_ITEM_Y,
                        IPTS_SRC_TOAST_LIST_TXT_ITEM_W,
                        IPTS_SRC_TOAST_LIST_TXT_ITEM_H);

    c_wgl_do_cmd (pt_this->h_listbox,
                      WGL_CMD_LB_GET_HLT_INDEX,
                      WGL_PACK(&ui2_lst_hlt_idx),
                      NULL) ;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} h_listbox WGL_CMD_LB_GET_HLT_INDEX: ui2_lst_hlt_idx:%d \n",
        __FUNCTION__, __LINE__, ui2_lst_hlt_idx )); );

    ui4_item_num = MAX_IPTS_LST_TOAST_TXT_NUM;

    if (i4_txt_num < MAX_IPTS_LST_TOAST_TXT_NUM)
    {
        ui4_item_num = i4_txt_num;
    }

    pt_this->ui1_inp_idx_bef_sel = (ui4_item_num - ui2_lst_hlt_idx) % ui4_item_num;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} i4_txt_num:%d \n",
        __FUNCTION__, __LINE__, i4_txt_num )); );

    for(ui1_idx = 0; ui1_idx < i4_txt_num && i4_txt_num < MAX_IPTS_LST_TOAST_TXT_NUM; ui1_idx++)
    {
        c_wgl_do_cmd (pt_this->pt_wdk_view->h_list_txt[ui1_idx],
                           WGL_CMD_TEXT_SET_TEXT,
                           t_g_toast_param.w2s_msg_t.w2s_str[ui2_lst_hlt_idx%i4_txt_num],
                           (VOID*)c_uc_w2s_strlen(t_g_toast_param.w2s_msg_t.w2s_str[ui2_lst_hlt_idx%i4_txt_num]));

        NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} ui1_idx:%d, WGL_CMD_TEXT_SET_TEXT: w2s_str[%d] \n",
            __FUNCTION__, __LINE__, ui1_idx, ui2_lst_hlt_idx%i4_txt_num )); );

        ui2_lst_hlt_idx++;
    }


    a_wdk_toast_list_adjust(pt_this->pt_wdk_view->h_list_txt,ui4_item_num);

    if (0 != ui4_item_num)
    {
         a_wdk_toast_adjust_list_focus_line(pt_this->ui1_inp_idx_bef_sel,
                                           pt_this->pt_wdk_view->h_list_txt_focus,
                                           pt_this->pt_wdk_view->h_list_txt,
                                           ui4_item_num
                                           );
    }

#if 0
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_color;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_color;
    t_clr_info.u_color_data.t_standard.t_disable    = t_color;
    c_wgl_do_cmd(pt_this->pt_wdk_view->h_dialog_frm,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info));
#endif

    c_wgl_repaint(pt_this->pt_wdk_view->h_base_frm, NULL, TRUE);

    i4_dim = (E_TOAST_MOVE_NEXT == e_move_dir) ? IPTS_SRC_TOAST_LIST_TXT_ITEM_W : 0-IPTS_SRC_TOAST_LIST_TXT_ITEM_W;

    SET_RECT_BY_SIZE (&t_rect,
                        IPTS_SRC_TOAST_LIST_FRM_X+i4_dim,
                        IPTS_SRC_TOAST_LIST_FRM_Y,
                        IPTS_SRC_TOAST_LIST_FRM_W,
                        IPTS_SRC_TOAST_LIST_FRM_H);
    /*c_wgl_move(pt_this->pt_wdk_view->h_list_txt_frm,
                &t_rect,
                TRUE);*/

    SET_RECT_BY_SIZE (&t_rect_end,
                        IPTS_SRC_TOAST_LIST_FRM_X,
                        IPTS_SRC_TOAST_LIST_FRM_Y,
                        IPTS_SRC_TOAST_LIST_FRM_W,
                        IPTS_SRC_TOAST_LIST_FRM_H);

    _nav_ipts_start_animation(pt_this->pt_wdk_view->h_list_txt_frm,
                              &t_rect,
                              &t_rect_end);
    //c_wgl_repaint(pt_this->pt_wdk_view->h_list_txt_frm, NULL, TRUE);

    return i4_ret;
}

static INT32 _nav_ipts_new_list_txt_hide(_NAV_IPTS_LIST_MEMBER_T* pt_this)
{
    INT32       i4_ret = NAVR_OK;

    NAV_DEBUG_INPUT_SRC_UI( DBG_LOG_PRINT(("[NAV][INPUT_SRC][UI]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    i4_ret = a_wdk_toast_hide(TRUE, NULL,&t_g_wdk_view);
    NAV_LOG_ON_FAIL(i4_ret);

    c_wgl_set_highlight_widget(NULL_HANDLE);

    i4_ret = c_wgl_set_visibility(pt_this->h_new_list_txt_frm, WGL_SW_HIDE_RECURSIVE);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_new_list_txt_frm, NULL, TRUE);
    NAV_LOG_ON_FAIL(i4_ret);

    pt_this->b_toast_active = FALSE;
    return NAVR_OK;
}

static INT32 _nav_ipts_lst_new_list_txt_active(_NAV_IPTS_LIST_MEMBER_T* pt_this)
{
    INT32       i4_ret = NAVR_OK;


    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    i4_ret = c_wgl_set_visibility(pt_this->h_new_list_txt_frm, WGL_SW_NORMAL);
    NAV_LOG_ON_FAIL(i4_ret);

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} call c_wgl_set_highlight_widget(0(0x%X))\n",
        __FUNCTION__, __LINE__, t_g_wdk_view.h_list_txt[0] )); );
    c_wgl_set_highlight_widget( t_g_wdk_view.h_list_txt[0] );

#if (NAV_INPUT_SRC_UI_USE_WDK)
    i4_ret = a_wdk_toast_activate(TRUE, &t_g_toast_param,&t_g_wdk_view);
    NAV_LOG_ON_FAIL(i4_ret);
#endif

#if 0
    UINT8       ui1_idx = 0;
    INT32 i4_num = t_g_toast_param.w2s_msg_t.i4_str_num;

    for(ui1_idx = 0; ui1_idx < i4_num; ui1_idx++)
    {
       aui4_g_toast_list_txt_pos[ui1_idx] = IPTS_SRC_TOAST_LIST_TXT_ITEM_X \
                                            + (ui1_idx+i4_num) % i4_num * WDK_VIEW_LIST_TXT_W_EX;
    }
#endif

    pt_this->b_toast_active = TRUE;

    return NAVR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name:    _nav_ipts_ch_name_text_preprocess
 *
 * Description: This function can run in place. String ps_src contain channel
 *              number here, this shouldn't process as channel name.Means ch
 *              number like "xxx-xxx" left and right part should take it as a
 *              whole number.
 *
 *              ps_src and ps_dst should be same because of the channel no.
 * Inputs:  ps_src
 *
 * Outputs: ps_dst
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_ipts_ch_name_text_preprocess(CHAR *ps_src, CHAR *ps_dst, size_t t_dst_size)
{
    CHAR  ps_src_tmp[128] = {0};
    CHAR *p_terminal = NULL;
    CHAR *p_src_index = NULL;
    INT32 index = 0;
    ptrdiff_t   t_offset;

    if (ps_src == NULL || ps_dst == NULL)
    {
        return NAVR_FAIL;
    }

    c_memcpy(ps_src_tmp, ps_src, c_strlen(ps_src));

    /*jump over ch_no to ch_name*/
    p_src_index = c_strchr(ps_src_tmp, ' ');
    if(p_src_index == NULL)
    {
        p_src_index = ps_src_tmp;
    }
    else
    {
        p_src_index += 1;
    }

    t_offset = p_src_index - ps_src_tmp;
    p_terminal = c_strchr(p_src_index, '-');

    if (p_terminal != NULL)
    {
        while (p_src_index < p_terminal)
        {
            *(ps_dst + t_offset + index++) = *p_src_index;
            *(ps_dst + t_offset + index++) = ' ';
            p_src_index++;
        }

        while (*p_src_index != '\0')
        {
            *(ps_dst + t_offset + index++) = *p_src_index++;
        }

        *(ps_dst + t_offset + index) = '\0';
        if (c_strlen(p_src_index) < t_dst_size)
        {
            return NAVR_OK;
        }
    }

    return NAVR_FAIL;
}

#ifdef APP_TTS_SUPPORT
static UINT32 _nav_ipts_lst_tts_cb_fct (HANDLE_T      h_tts,
                              TTS_CB_CODE_E e_type,
                              UINT32        ui4_status,
                              UINT32        ui4_string_id,
                              VOID          *pv_tag)
{
    switch(e_type)
    {
        case TTS_STR_STATE:
            if(TTS_STR_ST_PLAYED == (TTS_STRING_STATE_E) ui4_status)
            {
                DBG_INFO (("_nav_ipts_lst_tts_cb_fct() TTS with string id = %d has just finished playing\r\n", ui4_string_id));
            }
            break;
        case TTS_APP_STATE:
            break;
        case TTS_CPBLTY_CHNG_STATE:
            break;
        default:
            break;
    }

    return 0;
}

static INT32 _nav_ipts_tts_init(VOID)
{
    INT32       i4_ret = NAVR_OK;

    if (NULL_HANDLE != _h_g_tts)
    {
        DBG_INFO(("[APP_TV_MISC] tts handle initilized already!\n"));
        return NAVR_OK;
    }
    i4_ret = c_tts_open_default_instance_fct(&_h_g_tts);
    if (TTSR_OK != i4_ret)
    {
        DBG_ERROR(("_nav_ipts_tts_init Open tts handle failure!\n"));
        return NAVR_FAIL;
    }

    t_g_tts_cb.pf_fct = _nav_ipts_lst_tts_cb_fct;
    t_g_tts_cb.pv_tag = (VOID *)&i4_g_tts_tag;
    i4_ret = c_tts_set_fct(_h_g_tts, TTS_SET_CALLBACK, (VOID *)&t_g_tts_cb, sizeof(TTS_CB_T));
    if (TTSR_OK != i4_ret)
    {
        DBG_ERROR(("<NAV INPUT>set tts callback fails! ret=%d\n", i4_ret));
        return NAVR_FAIL;
    }

    _ui4_g_tts_string_id = 0;

    return NAVR_OK;
}
#endif

INT32 nav_ipts_lst_float(VOID* pv_list, BOOL b_float, BOOL b_repaint)
{
#if 0
    UINT8 ui1_cnt_loop = 0;
    _NAV_IPTS_LIST_MEMBER_T *pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_list;

    for (ui1_cnt_loop = 0;ui1_cnt_loop < NAV_IPTS_LST_BOX_ELEM_COUNT;ui1_cnt_loop++)
    {
        c_wgl_float(h_inp_icon_img[ui1_cnt_loop], b_float, WGL_NO_AUTO_REPAINT);
    }

    c_wgl_float(pt_this->h_frame, b_float, WGL_NO_AUTO_REPAINT);
    c_wgl_float(pt_this->h_listbox, b_float, WGL_NO_AUTO_REPAINT);
    c_wgl_float(h_inp_tv_ch_name_text, b_float, WGL_NO_AUTO_REPAINT);
    c_wgl_float(h_inp_tv_ch_no_text, b_float, WGL_NO_AUTO_REPAINT);
    c_wgl_float(h_ipts_ls_info_fram,b_float, WGL_NO_AUTO_REPAINT);
    c_wgl_float(h_ipts_ls_info_text,b_float, WGL_NO_AUTO_REPAINT);

    /*c_wgl_insert (pt_this->h_frame,
                   NULL_HANDLE,
                   WGL_INSERT_TOPMOST,
                   WGL_NO_AUTO_REPAINT);*/
    c_wgl_insert (h_ipts_ls_info_fram,
                   NULL_HANDLE,
                   WGL_INSERT_BEFORE,
                   WGL_SYNC_AUTO_REPAINT);

    c_wgl_repaint(pt_this->h_frame, NULL, b_repaint);
#endif
    return NAVR_OK;
}

INT32 nav_ipts_lst_lazy_init(VOID* pv_ipts_lst,TV_WIN_ID_T e_grp)
{
    UINT8                       ui1_num_recs = 0;
    INT32                       i4_ret;
    _NAV_IPTS_LIST_MEMBER_T*    pt_this = (_NAV_IPTS_LIST_MEMBER_T*)pv_ipts_lst;

    NAV_DEBUG_INPUT_SRC( DBG_LOG_PRINT(("[NAV][INPUT_SRC]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    /* get t_list_elem_num.ui2_total_num */
    {
        i4_ret = _nav_ipts_lst_calculate_num();
        NAV_LOG_ON_FAIL(i4_ret);

        ui1_num_recs = t_list_elem_num.ui2_total_num;
    }

    /* create pt_ipt_list_rec */
    {
        if (NULL == pt_ipt_list_rec)
        {
           pt_ipt_list_rec = (IPT_LIST_REC_T *)c_mem_alloc(NAV_IPTS_LST_BOX_ELEM_COUNT * sizeof(IPT_LIST_REC_T));
        }

        if (NULL == pt_ipt_list_rec)
        {
           return NAVR_NOT_ALLOW;
        }
    }

    c_memset(pt_ipt_list_rec, 0, NAV_IPTS_LST_BOX_ELEM_COUNT * sizeof(IPT_LIST_REC_T));
    pt_ipt_list_rec[0].ui2_num = ui1_num_recs;

    /* update pt_ipt_list_rec at_ipts_cec_dev ( show in input list view ) */
    i4_ret = _ipt_list_rec_collect(pt_this,e_grp, pt_ipt_list_rec);
    NAV_CHK_FAIL(i4_ret);

    /* set to view */
    i4_ret = _nav_ipts_lst_elem_sort(pt_ipt_list_rec);;
    NAV_CHK_FAIL(i4_ret);

    if(nav_get_power_to_input_status() == TRUE && _nav_ipts_lst_pwrdwn_check_sku_default_enable() == TRUE)
    {
        i4_ret = _nav_ipts_lst_elem_sort_pwrdwn(e_grp, pt_ipt_list_rec);
        NAV_CHK_FAIL(i4_ret);
    }

    /* debug */
    NAV_DEBUG_INPUT_SRC( nav_ipts_lst_print_elems(pt_this); );

    return NAVR_OK;
}

INT32 nav_ipts_get_next_source(UINT8 ui1_crnt_id,ISL_REC_T* t_next_isl_rec)
{
    UINT8 pt_loopid = 0;
    if(pt_ipt_list_rec == NULL)
    {
        DBG_LOG_PRINT(("[hongzhao] %s %d pt_ipt_list_rec == NULL\n",__FUNCTION__,__LINE__));
        return NAVR_FAIL;
    }
    for(pt_loopid = 0; pt_loopid < pt_ipt_list_rec[0].ui2_num; pt_loopid++)
    {
        if(pt_ipt_list_rec[pt_loopid].t_elem.ui1_id == ui1_crnt_id)
        {
            break;
        }
    }
    if(pt_loopid >= pt_ipt_list_rec[0].ui2_num)
    {
        DBG_LOG_PRINT(("[hongzhao] %s %d get next source ID error\r\n",__FUNCTION__,__LINE__));
        return NAVR_FAIL;
    }
    pt_loopid++;
    pt_loopid = (UINT8)((pt_loopid >= pt_ipt_list_rec[0].ui2_num) ? 0 : pt_loopid);

    return a_isl_get_rec_by_id(pt_ipt_list_rec[pt_loopid].t_elem.ui1_id, t_next_isl_rec);
}

INT32 nav_ipts_get_prev_source(UINT8 ui1_crnt_id,ISL_REC_T* t_prev_isl_rec)
{
    UINT8 pt_loopid = 0;

    if(pt_ipt_list_rec == NULL)
    {
        DBG_LOG_PRINT(("[hongzhao] %s %d pt_ipt_list_rec == NULL\n",__FUNCTION__,__LINE__));
        return NAVR_FAIL;
    }

    for(pt_loopid = 0; pt_loopid < pt_ipt_list_rec[0].ui2_num; pt_loopid++)
    {
        if(pt_ipt_list_rec[pt_loopid].t_elem.ui1_id == ui1_crnt_id)
        {
            break;
        }
    }

    if(pt_loopid >= pt_ipt_list_rec[0].ui2_num)
    {
        DBG_LOG_PRINT(("[hongzhao] %s %d get next source ID error\r\n",__FUNCTION__,__LINE__));
        return NAVR_FAIL;
    }


    //pt_loopid = (UINT8)((pt_loopid == 0) ? pt_ipt_list_rec[0].ui2_num - 1 : pt_loopid--);
    if( pt_loopid == 0 )
    {
        pt_loopid = pt_ipt_list_rec[0].ui2_num - 1;
    }
    else
    {
        pt_loopid = pt_loopid - 1;
    }

    return a_isl_get_rec_by_id(pt_ipt_list_rec[pt_loopid].t_elem.ui1_id, t_prev_isl_rec);
}

#ifdef APP_TTS_SUPPORT
static INT32 _nav_ipts_lst_tts_play_stop_ex(BOOL b_play, UTF16_T *pw2s_content)
{

    INT32   i4_ret = NAVR_OK;
    UINT16  ui2_i = 0;
    UINT16  ui2_pos = 0;
    CHAR    s_tmp_content[128] = {0};
    CHAR    s_content[128] = {0};

    TTS_STRING_T  t_tts_string_info = {0};
    i4_ret = _nav_ipts_tts_init();
    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR(("nav_ipts_lst_tts_play_stop() init tts fail, abort tts play! \n"));
        return i4_ret;
    }

    if (NULL == pw2s_content || c_uc_w2s_strlen(pw2s_content) == 0)
    {
        DBG_ERROR(("<NAV INPUT>TTS Play content is NULL\n"));
        return NAVR_OK;
    }

    c_uc_w2s_to_ps(pw2s_content, s_tmp_content, sizeof(s_tmp_content)-1);
    c_memset(s_content, 0, sizeof(s_content));

    while (s_tmp_content[ui2_pos] != '\0' && ui2_pos < 127)
    {
        if (('A' <= s_tmp_content[ui2_pos] && s_tmp_content[ui2_pos] <= 'Z')
            || ('a' <= s_tmp_content[ui2_pos] && s_tmp_content[ui2_pos] <= 'z')
            || ('0' <= s_tmp_content[ui2_pos] && s_tmp_content[ui2_pos] <= '9')
            || (' ' == s_tmp_content[ui2_pos] || s_tmp_content[ui2_pos] == '.'
            || '-' == s_tmp_content[ui2_pos]))
        {
            s_content[ui2_i] = s_tmp_content[ui2_pos];
            ui2_i++;
        }
        ui2_pos++;
    }

    t_tts_string_info.ui4_id = _ui4_g_tts_string_id++;
    t_tts_string_info.ps_string = s_content;

    DBG_INFO(("<NAV INPUT> file: %s line: %d  %s s_content before: %s\n", __FILE__, __LINE__, __FUNCTION__, s_content));

    t_tts_string_info.ui4_size = c_strlen(t_tts_string_info.ps_string);
    if (0 == t_tts_string_info.ui4_size)
    {
        DBG_ERROR(("<NAV INPUT>[%s:%d]tts string is empty, abort tts play! \n", __func__, __LINE__));
        return NAVR_FAIL;
    }
    /* Stop the running or queued tts requests, so current tts can be played
     * immediately */
    i4_ret = c_tts_stop_fct(_h_g_tts);
    if (TTSR_OK != i4_ret)
    {
        DBG_ERROR(("<NAV INPUT>[%s:%d]fails to stop running tts! ret=%d\n", __func__, __LINE__, i4_ret));
    }

    if (b_play)
    {
        /* (Mandatory)TTS engine need c_tts_play() called to do the preparation. */
        i4_ret = c_tts_play_fct(_h_g_tts);
        if (TTSR_OK != i4_ret)
        {
            DBG_ERROR(("<NAV INPUT>[%s:%d]tts play fails! ret=%d\n", __func__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }

        i4_ret = c_tts_send_string_fct(_h_g_tts, &t_tts_string_info);
        if (TTSR_OK != i4_ret)
        {
            DBG_ERROR(("<NAV INPUT>[%s:%d]tts play fails! ret=%d\n", __func__, __LINE__, i4_ret));
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

static INT32 _ch_lst2_w2s_ch_r(
            UTF16_T *pt_src_w2s,
            UTF16_T *pt_dst_w2s,
            SIZE_T t_dst_size,
            CHAR *a,
            CHAR *b
            )
{
    SIZE_T t_sz;
    CHAR  ps_src[64] = {0};
    CHAR  ps_dst[128] = {0};

    c_uc_w2s_to_ps(pt_src_w2s, ps_src, 64);

    CHAR *p_str = ps_src;
    CHAR *p_next;
    while ((p_str = c_strtok(p_str, a, &p_next, &t_sz)) != NULL)
    {
        c_strncat(ps_dst, p_str, p_next-p_str);
        if (*p_next == 0)
            break;
        c_strcat(ps_dst, b);
        p_str = p_next;
    }

    SIZE_T t_len = c_strlen(ps_dst);
    if (t_len < t_dst_size)
    {
        return c_uc_ps_to_w2s(ps_dst, pt_dst_w2s, t_len);
    }

    return NAVR_FAIL;
}


INT32 nav_ipts_lst_tts_play_stop(BOOL b_play, UTF16_T *pw2s_content)
{
    UTF16_T         w2s_string[256]         = {0};
    UTF16_T         w2s_string_new[256]   = {0};
    if(!a_cfg_get_tts_play_enable())
    {
        DBG_ERROR(("[POWER ON +++] {%s %s() %d}. there is not support TTS.\n",__FILE__, __FUNCTION__, __LINE__));
        return NAVR_FAIL;
    }

    c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_CHANGE_INPUT));
    c_uc_w2s_strcat (w2s_string, (UTF16_T*)L" ");

    {
        if(1)/* TV Channel name */
        {
            UTF16_T         w2s_ch_name[256]  = {0};
            CHAR            ps_ch_name[128]   = {0};
            c_uc_w2s_to_ps(pw2s_content,ps_ch_name, c_uc_w2s_strlen(pw2s_content));

            /*In this case, ch_name will never be 64 characters so text process can run in place*/
            _nav_ipts_ch_name_text_preprocess(ps_ch_name, ps_ch_name, 128);

            if(!strcmp(ps_ch_name,"WatchFree+"))
            {
               memset(ps_ch_name,0,128);
               strcpy(ps_ch_name,"WatchFreePlus");
            }
            c_uc_ps_to_w2s(ps_ch_name,w2s_ch_name,c_strlen(ps_ch_name));
            c_uc_w2s_strcat(w2s_string,w2s_ch_name);
        }
        else
        {
            c_uc_w2s_strcat(w2s_string,pw2s_content);
        }
    }

    _ch_lst2_w2s_ch_r(w2s_string, w2s_string_new, 128, "-", " dash ");

    return _nav_ipts_lst_tts_play_stop_ex(b_play,w2s_string_new);
}
#endif
#endif /*APP_NAV_IPTS_LST*/
#endif /*APP_537X_SUPPORT*/


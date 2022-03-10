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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: jg_zhenliwang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_sb_atsc_eng.h"
#include "u_sb_cqam_eng.h"
#include "u_sb_ntsc_eng.h"
#include "u_cli.h"
#include "u_gl.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_wgl_image.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_dt.h"
#include "x_os.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/dst/a_dst_custom.h"

#include "menu2/menu_util2.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include <sys/time.h>
#include "res/menu2/menu_img.h"
#include "wdk/util/wdk_wgl_util.h"

#ifdef TIME_MEASUREMENT
#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#endif

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#endif

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#endif
#include "menu2/menu_network_phase1/menu_tos_dialog.h"
#include "menu2/menu_network_phase1/menu_network.h"

#include "menu2/menu_dbg.h"
#include "res/nav/banner2/banner_rc.h"
#include "rest/a_rest_api.h"



/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MAX_POSTAL_CODE                 (5)
#define NTP_CHK_TIME_DELAY              10000
#define COUNTRY_HIDE                    (0)     /*hide country item*/
#define TIME_AUTOMATIC                  (1)     /*automatic time*/

#if TIME_AUTOMATIC
#define AT_TIME_CHECK                   (0)     /*automatic time status*/
#define AT_TIME_UNCHECK                 (1)

#define AT_TIME_GRAYED_OUT              (0)
#define AT_TIME_NOGRAYED_OUT            (1)

#define TIME_AUTOMATIC_LIST             (0)     /*automatic time UI style*/
#define TIME_AUTOMATIC_CHECKBOX         (1)     /*list style or checkbox style*/
#endif

#if TIME_AUTOMATIC_CHECKBOX
#define CHECKBOX_ICN_X                 (540)    /*checkbox's position offset*/
#define CHECKBOX_ICN_Y                 (20)
#define CHECKBOX_ICN_W                 (32)
#define CHECKBOX_ICN_H                 (32)
#endif

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#define TIME_LOCAL_SETTING_MAX_LEN      (7)

#if 0
#define COUNTRY_CODE_IDX_CA        (0)
#define COUNTRY_CODE_IDX_MEX       (1)
#define COUNTRY_CODE_IDX_US        (2)
#else
#define COUNTRY_CODE_IDX_US         (0)
#define COUNTRY_CODE_IDX_MEX        (1)
#define COUNTRY_CODE_IDX_CA         (2)
#endif
#define COUNTRY_CODE_IDX_LAST      (3)
#endif

#define MENU_SHOW_COUNTRY_CODE     1
#if MENU_SHOW_COUNTRY_CODE
#define MENU_CHG_COUNTRY_CODE_SHOW_DLG
#endif

typedef enum {
    _HELP_TIP_TYPE_HOMEBAR = 0,
    _HELP_TIP_TYPE_BACKBAR,
    _HELP_TIP_TYPE_TIMEZONE,
    _HELP_TIP_TYPE_DLS,
    _HELP_TIP_TYPE_TF,
    _HELP_TIP_TYPE_TF_EX,
    _HELP_TIP_TYPE_POSTAL_CODE,
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    _HELP_TIP_TYPE_CHG_COUNTRY_CODE,
    _HELP_TIP_TYPE_CHG_COUNTRY_CODE_EX,
    _HELP_TIP_TYPE_COUNTRY,
#endif
    _HELP_TIP_TYPE_TIMEZONE_EX,
    _HELP_TIP_TYPE_DLS_EX,
    _HELP_TIP_TYPE_AUTO_DLS_NOT_SUPPORT,
    _HELP_TIP_TYPE_AUTOMATIC_TIME,
#if TIME_AUTOMATIC_LIST
    _HELP_TIP_TYPE_AUTOMATIC_TIME_EX,
#endif
    _HELP_TIP_TYPE_LAST_ENTRY

} _HELP_TIP_TYPE_T ;

typedef enum{
    LOCAL_TIME_VIEW_INIT = 0,
    LOCAL_TIME_VIEW_LB_TIME_ZONE_EX,
    LOCAL_TIME_VIEW_LB_DLS_EX,
    LOCAL_TIME_VIEW_LB_TF_EX,
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    LOCAL_TIME_VIEW_LB_CCC_EX,
#endif
    LOCAL_TIME_VIEW_EB_EX,
#if TIME_AUTOMATIC_LIST
    LOCAL_TIME_VIEW_AT_EX,
#endif
    LOCAL_TIME_VIEW_LAST_ENTRY
}LOCAL_TIME_VIEW_TYPE_T;

#define NTP_CHK_TIME         10000
#define PAGE_TIME_ZONE_ITEM_NUM 10
#ifdef APP_C4TV_SUPPORT

extern INT32 a_c4tv_apron_set_time_format(BOOL b_is_time_in_12_hour_format);
#endif
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_time_local_setting_auto_dst;

static  LOCAL_TIME_VIEW_TYPE_T e_view_type = LOCAL_TIME_VIEW_INIT;
#if TIME_AUTOMATIC
static HANDLE_T    h_lb_autmomatic_time;
#if TIME_AUTOMATIC_LIST
static HANDLE_T    h_lb_autmomatic_time_ex;
#endif
#if TIME_AUTOMATIC_CHECKBOX
extern WGL_HIMG_TPL_T  h_g_menu_common_checkbox_white_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_checkbox_white_checked_v2;
static HANDLE_T    checkbox_icon;
static HANDLE_T    checkbox_checked_icon;
#endif

typedef struct _ZONE_MAP_AREA
{
    CHAR *ps_cast_zone;
    INT32 i4_idx;
} ZONE_MAP_AREA;

ZONE_MAP_AREA cast_zone_maps[] =
{
    {"Pacific/Midway", 23},                 /* IDLW */ //change for new time zone standard
    {"Pacific/Honolulu", 0},                /* HST */
    {"America/Anchorage", 1},               /* AKST */
    {"America/Los_Angeles", 2},             /* PST */
    {"America/Vancouver", 2},               /* PST */
    {"America/Tijuana", 2},                 /* PST */
    {"America/Phoenix", 3},                 /* MST */
    {"America/Denver", 3},                  /* MST */
    {"America/Edmonton", 3},                /* MST */
    {"America/Chihuahua", 3},               /* MST */
    {"America/Regina", 4},                  /* CST */
    {"America/Costa_Rica", 4},              /* CST */
    {"America/Chicago", 4},                 /* CST */
    {"America/Mexico_City", 4},             /* CST */
    {"America/Winnipeg", 4},                /* CST */
    //{"America/Bogota", 5},
    {"America/New_York", 5},                /* EST */
    {"America/Toronto", 5},                 /* EST */
    {"America/Caracas", 6},                 /* AST */
    {"America/Barbados", 6},                /* AST */
    {"America/Halifax", 6},                 /* AST */
    {"America/Manaus", 6},                  /* AST */
    {"America/Santiago", 6},                /* AST */
    //{"America/St_Johns", 7},              /*GMT-3.5*/ remove for vizio spec change 5.4.1
    {"America/Sao_Paulo", 7},               /* ART */
    {"America/Araguaina", 7},               /* ART */
    {"America/Argentina/Buenos_Aires", 7},  /* ART */
    {"America/Argentina/San_Luis", 7},      /* ART */
    {"America/Montevideo", 7},              /* ART */
    {"America/Godthab", 7},                 /* ART */
    {"Atlantic/South_Georgia", 8},          /* AT */
    {"Atlantic/Cape_Verde", 9},             /* WAT */
    {"Atlantic/Azores", 9},                 /* WAT */
    {"Africa/Casablanca", 10},              /* GMT */
    {"Europe/London", 10},                  /* GMT */
    {"Europe/Dublin", 10},                  /* GMT */
    {"Europe/Amsterdam", 11},               /* CET */
    {"Europe/Belgrade", 11},                /* CET */
    {"Europe/Berlin", 11},                  /* CET */
    {"Europe/Brussels", 11},                /* CET */
    {"Europe/Copenhagen", 11},              /* CET */
    {"Europe/Lisbon", 11},                  /* CET */
    {"Europe/Madrid", 11},                  /* CET */
    {"Europe/Oslo", 12},                    /* EET */
    {"Europe/Paris", 11},                   /* CET */
    {"Europe/Rome", 11},                    /* CET */
    {"Europe/Stockholm", 11},               /* CET */
    {"Europe/Sarajevo", 11},                /* CET */
    {"Europe/Vienna", 11},                  /* CET */
    {"Europe/Warsaw", 11},                  /* CET */
    {"Europe/Zurich", 11},                  /* CET */
    {"Africa/Windhoek", 12},                /* EET */
    {"Africa/Lagos", 11},                   /* CET */
    {"Africa/Brazzaville", 11},             /* CET */
    {"Africa/Cairo", 12},                   /* EET */
    {"Africa/Harare", 12},                  /* EET */
    {"Africa/Maputo", 12},                  /* EET */
    {"Africa/Johannesburg", 12},            /* EET */
    {"Europe/Helsinki", 12},                /* EET */
    {"Europe/Athens", 12},                  /* EET */
    {"Asia/Amman", 12},                     /* EET */
    {"Asia/Beirut", 12},                    /* EET */
    {"Asia/Jerusalem", 12},                 /* EET */
    {"Europe/Minsk", 13},                   /* MSK */
    {"Asia/Baghdad", 13},                   /* MSK */
    {"Asia/Riyadh", 13},                    /* MSK */
    {"Asia/Kuwait", 13},                    /* MSK */
    {"Africa/Nairobi", 13},                 /* MSK */
    {"Asia/Tehran", 13},                    /* MSK */
    {"Europe/Moscow", 13},                  /* MSK */
    {"Asia/Dubai", 14},                     /* AMT */
    {"Asia/Tbilisi", 14},                   /* AMT */
    {"Indian/Mauritius", 14},               /* AMT */
    {"Asia/Baku", 14},                      /* AMT */
    {"Asia/Yerevan", 14},                   /* AMT */
    {"Asia/Kabul", 14},                     /* AMT */
    {"Asia/Karachi", 15},                   /* PKT */
    {"Asia/Ashgabat", 15},                  /* PKT */
    {"Asia/Oral", 15},                      /* PKT */
    {"Asia/Kolkata", 15},                   /* PKT */
    {"Asia/Colombo", 15},                   /* PKT */
    {"Asia/Kathmandu", 15},                 /* PKT */
    {"Asia/Yekaterinburg", 15},             /* PKT */
    {"Asia/Almaty", 16},                    /* OMSK */
    {"Asia/Dhaka", 16},                     /* OMSK */
    {"Asia/Rangoon", 16},                   /* OMSK */
    {"Asia/Bangkok", 17},                   /* KRAT */
    {"Asia/Jakarta", 17},                   /* KRAT */
    {"Asia/Omsk", 16},                      /* OMSK */
    {"Asia/Novosibirsk", 17},               /* KRAT */
    {"Asia/Shanghai", 18},                  /* CST */
    {"Asia/Hong_Kong", 18},                 /* CST */
    {"Asia/Kuala_Lumpur", 18},              /* CST */
    {"Asia/Singapore", 18},                 /* CST */
    {"Asia/Manila", 18},                    /* CST */
    {"Asia/Taipei", 18},                    /* CST */
    {"Asia/Makassar", 18},                  /* CST */
    {"Asia/Krasnoyarsk", 17},               /* KRAT */
    {"Australia/Perth", 18},                /* CST */
    {"Australia/Eucla", 18},                /* CST */
    {"Asia/Irkutsk", 18},                   /* CST */
    {"Asia/Seoul", 19},                     /* JST */
    {"Asia/Tokyo", 19},                     /* JST */
    {"Asia/Jayapura", 19},                  /* JST */
    {"Australia/Adelaide", 19},             /* JST */
    {"Australia/Darwin", 19},               /* JST */
    {"Australia/Brisbane", 20},             /* AEST */
    {"Australia/Hobart", 20},               /* AEST */
    {"Australia/Sydney", 20},               /* AEST */
    {"Asia/Yakutsk", 19},                   /* JST */
    {"Pacific/Guam", 20},                   /* AEST */
    {"Pacific/Port_Moresby", 20},           /* AEST */
    {"Asia/Vladivostok", 20},               /* AEST */
    {"Asia/Sakhalin", 21},                  /* SAKT */
    {"Asia/Magadan", 21},                   /* SAKT */
    {"Pacific/Auckland", 22},               /* NZST */
    {"Pacific/Fiji", 22},                   /* NZST */
    {"Pacific/Majuro", 22},                 /* NZST */
    {"Pacific/Tongatapu", 23},              /* IDLW */
    {"Pacific/Apia", 23},                   /* IDLW */
    {"Pacific/Kiritimati", 24}              /* NT */
};
CHAR *str_cast_zone_wo_dst[]=
{
    "Etc/GMT+10",
    "Etc/GMT+9",
    "Etc/GMT+8",
    "Etc/GMT+7",
    //"Etc/GMT+7", remove for new time zone standard
    "Etc/GMT+6",
    //"Etc/GMT+5",
    "Etc/GMT+5",
    "Etc/GMT+4",
    //"Etc/GMT+3.5", remove for new time zone standard
    "Etc/GMT+3",
    "Etc/GMT+2",
    "Etc/GMT+1",
    "Etc/GMT",
    "Etc/GMT-1",
    "Etc/GMT-2",
    "Etc/GMT-3",
    "Etc/GMT-4",
    "Etc/GMT-5",
    "Etc/GMT-6",
    "Etc/GMT-7",
    "Etc/GMT-8",
    "Etc/GMT-9",
    "Etc/GMT-10",
    "Etc/GMT-11",
    "Etc/GMT-12",
    "Etc/GMT+12",
    "Etc/GMT+11",
};
#endif
static HANDLE_T    h_lb_time_zone;
static HANDLE_T    h_lb_time_zone_ex;
static HANDLE_T    h_cnt_frm;
static HANDLE_T    h_timer_ntp_update;
static HANDLE_T    h_lb_daylight_saving;
static HANDLE_T    h_lb_daylight_saving_ex;
static HANDLE_T    h_eb_postal_code;
static HANDLE_T    h_lb_time_format;
static HANDLE_T    h_lb_time_format_ex;

static HANDLE_T    h_g_dt = NULL_HANDLE;

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
static  HANDLE_T   h_lb_chg_country_code;
static  HANDLE_T   h_lb_chg_country_code_ex;
/*static  HANDLE_T   h_action_item_country;*/
static  HANDLE_T   h_vkb;
static  HANDLE_T   h_vkb_last_focus;
static  UINT32     ui4_page_id_pass;
static  BOOL       b_show_clear_memory_from_tls = FALSE;
#endif
static  BOOL       b_help_tip_back_press = FALSE; //record press back item
static  BOOL       b_help_tip_set_and_show = TRUE;

static BOOL        b_g_page_in_on;
static UINT32      ui4_page_id;

static HANDLE_T    h_homebar = NULL_HANDLE;
static HANDLE_T    h_backbar = NULL_HANDLE;

static UINT16      apw2s_help_tip[_HELP_TIP_TYPE_LAST_ENTRY] = {0};

static UTF16_T     w2s_postal_code[10];
static UINT16      ui2_lst_last_hlt= 0xFFFF;

static UINT16      aui2_country_code_txt[COUNTRY_CODE_IDX_LAST] = {
                                                MLM_MENU_KEY_COUNTRY_USA,
                                                MLM_MENU_KEY_COUNTRY_MEX,
                                                MLM_MENU_KEY_COUNTRY_CA
                                              };
static GL_RECT_T   g_t_list_tz_rect = {0};
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2);

static INT32 _change_view(LOCAL_TIME_VIEW_TYPE_T  e_local_time_view_type, UINT8 ui1FocusIdx);

static INT32 _show_lb_time_zone_ex_view(BOOL b_repaint);

static INT32 _show_lb_dls_ex_view(BOOL b_repaint);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
static UINT16 _time_local_setting_page_get_country_code_idx(VOID);

static INT32 _time_local_setting_page_set_country_code_idx(UINT16 ui2_idx);

static INT32 _show_time_local_setting_pwd_vkb(VOID);
#endif

static INT32 _ntp_timer_start(void);
static INT32 _ntp_timer_stop(void);
static VOID _ntp_timer_nfy_fct(HANDLE_T h_timer, VOID* pv_tag);
static INT32 _update_title_info(BOOL b_repaint);
static VOID _do_ntp_timer_nfy(VOID*pv_data, SIZE_T z_data_size);
//static BOOL _get_ntp_time(DTG_T* pt_loc_dtg);


extern BOOL _crnt_source_is_tv (VOID);


static INT32 _hide_time_local_setting_pwd_vkb(VOID);
static INT32 _time_local_setting_page_help_tip_cb(
                        HANDLE_T            h_widget,
                        UINT32              ui4_msg,
                        VOID*               pv_param1,
                        VOID*               pv_param2,
                        BOOL*               pb_processed);

static INT32 _time_local_setting_update_shadow_item_pos(VOID);
#if TIME_AUTOMATIC
static INT32 _lb_automatic_time_proc_fct(HANDLE_T    h_widget,
                                   UINT32      ui4_msg,
                                   VOID*       param1,
                                   VOID*       param2);
#if TIME_AUTOMATIC_LIST
static INT32 _creat_automatic_lb_time_ex(VOID);
static INT32 _show_lb_automatic_time_ex_view(BOOL b_repaint);
#endif
static VOID _set_automatic_time_idx(UINT16 ui2_idx);
static UINT16 _get_automatic_time_idx(VOID);
static INT32 _time_zone_dst_grayed_out_enable (BOOL b_hide_enable);
#if TIME_AUTOMATIC_CHECKBOX
static INT32 _automatic_time_checkbox_create(VOID);
static INT32 _automatic_time_checkbox_show(UINT8 ui1_automatic);
static INT32 _automatic_time_checkbox_hide(VOID);
#endif
static INT32 _automatic_time_set_dst(UINT8 ui1_automatic);
static INT32 _automatic_time_get_geofencing_timezone(REST_TIMZONE_T *p_at_geo_timezone);
static INT32 _automatic_time_set_geofencing_timezone(char* ps_timezone);
static BOOL _time_crnt_source_is_tv (VOID);
static INT32 _automatic_time_geofencing_timezone_handle(UINT8 ui1_automatic);
INT32 menu_page_set_automatic_time_to_refresh(VOID);

static REST_TIMZONE_T at_geo_timezone; //by get geofencing timezone
#endif
/*----------------------------------------------------------------------------
                        Pseudo Builder
 ----------------------------------------------------------------------------*/
INT32 menu_time_local_setting_get_tz_offset(UINT16 ui2_tz_idx, TIME_T *pt_tz_offset)
{
    if (ui2_tz_idx < 0 || NULL == pt_tz_offset)
    {
        return MENUR_INV_ARG;
    }
    switch (ui2_tz_idx)
    {
    case 0:
        *pt_tz_offset = -10  * 3600;      /* HST */  //change for new time zone standard (DTV02194418)
        break;
    case 1:
        *pt_tz_offset = -9   * 3600;      /* AKST */
        break;
    case 2:
        *pt_tz_offset = -8   * 3600;      /* PST(default)*/
        break;
    case 3:
        *pt_tz_offset = -7   * 3600;      /* MST */
        break;
    case 4:
        *pt_tz_offset = -6   * 3600;      /* CST */
        break;
    case 5:
        *pt_tz_offset = -5   * 3600;      /* EST */
        break;
    case 6:
        *pt_tz_offset = -4   * 3600;      /* AST */
        break;
    case 7:
       *pt_tz_offset = -3  * 3600;        /* ART */
       break;
    case 8:
        *pt_tz_offset = -2  * 3600;       /* AT */
        break;
    case 9:
        *pt_tz_offset = -1   * 3600;      /* WAT */
        break;
    case 10:
        *pt_tz_offset = 0   * 3600;       /* GMT */
        break;
    case 11:
        *pt_tz_offset = 1   * 3600;       /* CET */
        break;
    case 12:
        *pt_tz_offset = 2   * 3600;       /* EET */
        break;
    case 13:
        *pt_tz_offset = 3   * 3600;       /* MSK */
        break;
    case 14:
        *pt_tz_offset = 4 *   3600;         /* AMT */
        break;
    case 15:
        *pt_tz_offset = 5   * 3600;       /* PKT */
        break;
    case 16:
        *pt_tz_offset = 6   * 3600;       /* OMSK */
       break;
    case 17:
        *pt_tz_offset = 7  * 3600;        /* KRAT */
       break;
    case 18:
        *pt_tz_offset = 8  * 3600;        /* CST */
        break;
    case 19:
        *pt_tz_offset = 9   * 3600;       /* JST */
        break;
    case 20:
        *pt_tz_offset = 10   * 3600;      /* AEST */
        break;
    case 21:
        *pt_tz_offset = 11   * 3600;      /* SAKT */
        break;
    case 22:
        *pt_tz_offset = 12   * 3600;      /* NZST */
        break;
    case 23:
        *pt_tz_offset = -12   * 3600;     /* IDLW */
        break;
    case 24:
        *pt_tz_offset = -11   * 3600;     /* NT */
        break;
    default:
        ui2_tz_idx  = 2;
        *pt_tz_offset = -8   * 3600;      /* PST(default) */
        break;
    }

    return MENUR_OK;
}

#ifdef APP_TTS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _tts_play_timezone_minus
 *
 * Description: replace string, ex:  xxx-xxx-xxx -> xxx minus xxx-xxx
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tts_play_timezone_minus(UINT16 *pt_w2s_src, UTF16_T *pt_w2s_dst, SIZE_T dst_sz)
{
    UINT32   ui4_pos;
    UINT32   ui4_area_sz;
    UINT32   ui4_rest_sz = 64;
    UTF16_T  buffer[64+1] = {0};

    if (c_uc_w2s_chr_ex(pt_w2s_src, L'-', &ui4_pos) != NULL)
    {
        if (ui4_rest_sz > ui4_pos)
        {
            ui4_rest_sz -= ui4_pos;
            c_uc_w2s_strncpy(buffer, pt_w2s_src, ui4_pos);

            ui4_area_sz = c_uc_w2s_strlen(L" ,minus ");
            if (ui4_rest_sz > ui4_area_sz)
            {
                ui4_rest_sz -= ui4_area_sz;
                c_uc_w2s_strncat(buffer, L" ,minus ", ui4_area_sz);

                ui4_area_sz = c_uc_w2s_strlen(pt_w2s_src+ui4_pos+1);
                if (ui4_rest_sz > ui4_area_sz)
                {
                    ui4_rest_sz -= ui4_area_sz;
                    c_uc_w2s_strncat(buffer, pt_w2s_src+ui4_pos+1, ui4_area_sz);
                    if (dst_sz >= (64-ui4_rest_sz))
                    {
                        c_uc_w2s_strcpy(pt_w2s_dst, buffer);
                        return MENUR_OK;
                    }
                    return MENUR_FAIL;
                }
                return MENUR_FAIL;
            }
            return MENUR_FAIL;
        }
        return MENUR_FAIL;
    }
    return MENUR_FAIL;
}

static VOID _tts_play(UINT16 fir_mlm_key, UINT16 sec_mlm_key, BOOL b_sec_exist)
{
    UTF16_T w2s_str[64+1] = {0};

    c_uc_w2s_strcpy(w2s_str, mlm_menu_get_text(0, fir_mlm_key));
    c_uc_w2s_strcat(w2s_str, (UTF16_T *)L" ");

    if (b_sec_exist)
    {
        c_uc_w2s_strcat(w2s_str, mlm_menu_get_text(0, sec_mlm_key));
    }

    _tts_play_timezone_minus(w2s_str, w2s_str, 64);

    a_app_tts_play(w2s_str, 64);
}

static UINT16 _tts_get_country_mlm_key(UINT16  ui2_idx)
{
    UINT16 ui2_ret = MLM_MENU_KEY_COUNTRY_USA;

    switch (ui2_idx)
    {
        case COUNTRY_CODE_IDX_US:
            ui2_ret = MLM_MENU_KEY_COUNTRY_USA;
            break;
        case COUNTRY_CODE_IDX_CA:
            ui2_ret = MLM_MENU_KEY_COUNTRY_CA;
            break;
        case COUNTRY_CODE_IDX_MEX:
            ui2_ret = MLM_MENU_KEY_COUNTRY_MEX;
            break;
        default:
            break;
    }

    return ui2_ret;
}
#endif
VOID _do_update_title_info(VOID* pv_data, SIZE_T  z_data_size)
{
    DBG_INFO(("<MENU> Update time by dt notify\n"));
    _update_title_info(TRUE);
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _menu_page_date_time_nfy_dt (HANDLE_T     h_dt,
                                         VOID*        pv_tag,
                                         DT_COND_T    t_dt_cond,
                                         TIME_T       t_delta)
{
    /* This page is not active, do nothing. */
    if (b_g_page_in_on)
    {
		menu_async_invoke(_do_update_title_info, NULL, 0, FALSE);
    }

    DTG_T       t_dtg = {0};
    BOOL        b_is_get_time = a_dst_get_local_time(&t_dtg);
	if(b_is_get_time)
	{
		DBG_LOG_PRINT(("[ TIME +++ ] {%s %s() %d}. @@@@@@@@@@@@@@@@@ time: %d/%d/%d %d:%d.\n",__FILE__, __FUNCTION__, __LINE__,
				t_dtg.ui1_mo,t_dtg.ui1_day,t_dtg.ui2_yr,t_dtg.ui1_hr,t_dtg.ui1_min));
	}
}

/*----------------------------------------------------------------------------
 * Name: _init_date_time_in_menu
 *
 * Description: Init the date time handle in menu
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _init_date_time_in_menu(VOID)
{
    if (NULL_HANDLE == h_g_dt)
    {
        c_dt_reg_nfy_fct(_menu_page_date_time_nfy_dt,
                         NULL,
                         &h_g_dt);
    }

    return MENUR_OK;
}


/* Time Zone */
static VOID _set_time_zone_idx(UINT16 ui2_idx)
{
    TIME_T      t_tz_offset = 0;
    BOOL        b_dls       = FALSE;
    CHAR        str[16] = {0};

    a_cfg_get_time_zone_data(&t_tz_offset, &b_dls);

    b_dls = FALSE;

    switch (ui2_idx)
    {
    case 0:
        t_tz_offset = -10  * 3600;      /* HST */   //change for new time zone standard (DTV02194418)
        break;
    case 1:
        t_tz_offset = -9   * 3600;      /* AKST */
        break;
    case 2:
        t_tz_offset = -8   * 3600;      /* PST(default)*/
        break;
    case 3:
        t_tz_offset = -7   * 3600;      /* MST */
        break;
    case 4:
        t_tz_offset = -6   * 3600;      /* CST */
        break;
    case 5:
        t_tz_offset = -5   * 3600;      /* EST */
        break;
    case 6:
        t_tz_offset = -4   * 3600;      /* AST */
        break;
    case 7:
        t_tz_offset = -3  * 3600;      /* ART */
       break;
    case 8:
        t_tz_offset = -2  * 3600;      /* AT */
        break;
    case 9:
        t_tz_offset = -1   * 3600;      /* WAT */
        break;
    case 10:
        t_tz_offset = 0   * 3600;      /* GMT */
        break;
    case 11:
        t_tz_offset = 1   * 3600;      /* CET */
        break;
    case 12:
        t_tz_offset = 2   * 3600;      /* EET */
        break;
    case 13:
        t_tz_offset = 3   * 3600;      /* MSK */
        break;
    case 14:
        t_tz_offset = 4   * 3600;      /* AMT */
        break;
    case 15:
        t_tz_offset = 5   * 3600;      /* PKT */
        break;
    case 16:
        t_tz_offset = 6   * 3600;      /* OMSK */
       break;
    case 17:
        t_tz_offset = 7  * 3600;       /* KRAT */
       break;
    case 18:
        t_tz_offset = 8  * 3600;       /* CST */
        break;
    case 19:
        t_tz_offset = 9   * 3600;      /* JST */
        break;
    case 20:
        t_tz_offset = 10   * 3600;     /* AEST */
        break;
    case 21:
        t_tz_offset = 11   * 3600;     /* SAKT */
        break;
    case 22:
        t_tz_offset = 12   * 3600;     /* NZST */
        break;
    case 23:
        t_tz_offset = -12   * 3600;    /* IDLW */
        break;
    case 24:
        t_tz_offset = -11   * 3600;     /* NT */
        break;
    default:
        ui2_idx  = 2;
        t_tz_offset = -8   * 3600;      /* PST(default) */
        break;
    }

    a_cfg_set_time_zone_data(t_tz_offset, b_dls);

    a_cfg_custom_set_timezone_idx((UINT8)ui2_idx);
    DBG_LOG_PRINT(("[MENU][DST][%s %d] tz = %d\n",__FUNCTION__,__LINE__,ui2_idx));
    a_cfg_update_time_zone();

    c_uc_w2s_to_ps(MLM_MENU_TEXT(0, MLM_MENU_KEY_BRCM_TIME_ZONE_HST+ui2_idx), str, 16);
    DBG_LOG_PRINT(("[rest notify timezone]%s:%d str = %s\n", __FUNCTION__, __LINE__, str));
    rest_event_notify("system/time/timezone", 0, str);
}


static UINT16 _get_time_zone_idx(VOID)
{
    UINT8 ui1_tz = APP_CFG_TZ_EASTERN_TIME;

    a_cfg_custom_get_timezone_idx(&ui1_tz);

    return (UINT16)ui1_tz;
}

/* include hawaii  and arizona */
static BOOL _is_a_unnamed_tz()
{
     switch (_get_time_zone_idx())
     {
          case  8: case  9: case 11:  //change for new time zone standard (DTV02194418)
          case 12: case 13: case 10:
          case 14: case 15: case 16:
          case 17: case 18: case 19:
          case 21: case 22: case 20:
          case 23: case 24: case 25:
          case  0: case  7:
          {
             return TRUE;
          }
          default:
             return FALSE;
     }
}

static BOOL _is_auto_dls_support()
{
    switch (_get_time_zone_idx())
    {
       case 0:                           //change for new time zone standard (DTV02194418)
       case 20:
       return FALSE;
       default:return TRUE;
    }
    return TRUE;
}
/* Daylight Saving */
static VOID _set_dls_idx(UINT16 ui2_idx)
{
    a_cfg_custom_set_dst(ui2_idx);
    return;
}

static UINT16 _get_dls_idx(VOID)
{
    UINT16   ui2_dls = 0;

    a_cfg_custom_get_dst(&ui2_dls);

    /* Auto Test & Daylight Saving Time */
    DBG_LOG_PRINT(("\n<Menu>[DST][%s,%s,%d] dst =%s,\n",
                    __FILE__,__FUNCTION__,__LINE__,
                    ui2_dls == DST_AUTO ? "Auto" :
                    ui2_dls == DST_ON ? "ON" :"OFF"));
    return ui2_dls;
}


/*----------------------------------------------------------------------------
 * Name: _itoa
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
VOID _itoa(UTF16_T* w2s_dst,
                  INT32 i4_src,
                  UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}

static INT32 _update_dls_by_tz(UINT16 ui2_index)
{
    INT32   i4_ret = MENUR_OK;
    DBG_LOG_PRINT(("[MENU][DST][%s %d] tz = %d\n",__FUNCTION__,__LINE__,ui2_index));
    _set_dls_idx((_is_a_unnamed_tz() || 20 == ui2_index || 10 == ui2_index) ? DST_OFF : DST_AUTO);

    MENU_LOG_ON_FAIL(menu_list_set_idx(h_lb_daylight_saving, _get_dls_idx()));
    MENU_LOG_ON_FAIL(menu_list_adjust_rect(h_lb_daylight_saving));
    MENU_LOG_ON_FAIL(menu_pm_repaint());
    return i4_ret;
}

static INT32 _eb_postal_code_get_text(UTF16_T *pw2s_text)
{
    c_uc_w2s_strcpy(pw2s_text, w2s_postal_code);

    return MENUR_OK;
}


static INT32 _eb_postal_code_set_text(HANDLE_T  h_widget, UTF16_T *pw2s_text)
{
    INT32   i4_ret = 0;
    i4_ret = c_wgl_do_cmd(h_widget,
                 WGL_CMD_EB_SET_TEXT,
                 (VOID*)pw2s_text,
                 (VOID*)c_uc_w2s_strlen(pw2s_text));

    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _eb_postal_code_set_text_left
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
static INT32 _eb_postal_code_set_text_left(HANDLE_T    h_widget,
                                           UTF16_T     *pw2s_text)
{
    INT32 i4_ret;
    UTF16_T w2s_buf[10];

    c_memset(w2s_buf, 0, 10*sizeof(UTF16_T));

    c_uc_w2s_strcpy(w2s_buf, pw2s_text);

    c_uc_w2s_strcpy(w2s_postal_code, pw2s_text);

    c_uc_w2s_strncat(w2s_buf, _TEXT("_"),
                     10 - c_uc_w2s_strlen(w2s_buf));

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}



/*----------------------------------------------------------------------------
 * Name: _set_nav
 *
 * Description: Set the navigation
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _set_nav(VOID)
{
    INT32   i4_ret = 0;
    WGL_KEY_LINK_T      at_key_lnk[2];

    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_backbar;
        if(AT_TIME_NOGRAYED_OUT == _get_automatic_time_idx())
        {
           at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
           at_key_lnk[1].h_widget = h_lb_time_zone;
        }
        else
        {
           at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
           at_key_lnk[1].h_widget = h_lb_time_format;
        }
        i4_ret = c_wgl_set_navigation(h_lb_autmomatic_time, 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_lb_autmomatic_time;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_lb_daylight_saving;
        i4_ret = c_wgl_set_navigation(h_lb_time_zone, 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_lb_time_zone;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_lb_time_format;
        i4_ret = c_wgl_set_navigation(h_lb_daylight_saving, 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);

        if(AT_TIME_NOGRAYED_OUT == _get_automatic_time_idx())
        {
            at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
            at_key_lnk[0].h_widget = h_lb_daylight_saving;
        }
        else
        {
            at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
            at_key_lnk[0].h_widget = h_lb_autmomatic_time;
        }
        i4_ret = c_wgl_set_navigation(h_lb_time_format, 1, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);


#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
        at_key_lnk[0].ui4_key   = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget  = h_lb_daylight_saving;
        at_key_lnk[1].ui4_key   = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget  = h_lb_chg_country_code;
        i4_ret = c_wgl_set_navigation(h_eb_postal_code, 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);

        /*at_key_lnk[0].ui4_key   = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget  = h_eb_postal_code;
        at_key_lnk[1].ui4_key   = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget  = h_action_item_country;
        i4_ret = c_wgl_set_navigation(h_lb_chg_country_code, 1, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);*/
#endif
    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _widgets_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32  i4_ret;

    switch (ui4_msg)
   {
        case WGL_MSG_GET_FOCUS:
        {
           if(h_widget == h_lb_daylight_saving)
           {
                if (b_help_tip_set_and_show) {
                    i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_DLS]));
                    MENU_LOG_ON_FAIL(i4_ret);
                } else {
                    i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_DLS]));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
           }
           else if (h_widget == h_lb_time_zone)
           {
             if(FALSE == b_help_tip_back_press)
             {
                if (b_help_tip_set_and_show) {
                    i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TIMEZONE]));
                    MENU_LOG_ON_FAIL(i4_ret);
                } else {
                    i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TIMEZONE]));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
             }
             else
             {
                 b_help_tip_back_press = FALSE;
             }

           }
           else if (h_widget == h_lb_time_format)
           {
                if (b_help_tip_set_and_show) {
                    i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF]));
                    MENU_LOG_ON_FAIL(i4_ret);
                } else {
                    i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF]));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
           }

           else if (h_widget == h_lb_time_format_ex)
           {
                if (b_help_tip_set_and_show) {
                    i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF_EX]));
                    MENU_LOG_ON_FAIL(i4_ret);
                } else {
                    i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF_EX]));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
           }
           else if(h_widget == h_eb_postal_code)
           {
               i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE]));
               MENU_LOG_ON_FAIL(i4_ret);
           }
           else if(h_widget == h_lb_time_zone_ex)
           {
                if (b_help_tip_set_and_show) {
                    i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TIMEZONE_EX]));
                    MENU_LOG_ON_FAIL(i4_ret);
                } else {
                    i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TIMEZONE_EX]));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
           }
           else if(h_widget == h_lb_daylight_saving_ex)
           {
               i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_DLS_EX]));
               MENU_LOG_ON_FAIL(i4_ret);
           }
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
           else if(h_widget == h_lb_chg_country_code)
           {
                if (b_help_tip_set_and_show) {
                    i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_CHG_COUNTRY_CODE]));
                    MENU_LOG_ON_FAIL(i4_ret);
                } else {
                    i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_CHG_COUNTRY_CODE]));
                    MENU_LOG_ON_FAIL(i4_ret);
                }
           }
           else if(h_widget == h_lb_chg_country_code_ex)
           {
               i4_ret = menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_CHG_COUNTRY_CODE_EX]));
               MENU_LOG_ON_FAIL(i4_ret);
           }
           /*else if(h_widget == h_action_item_country)
           {
               i4_ret = menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_COUNTRY]));
               MENU_LOG_ON_FAIL(i4_ret);
           }*/
#endif
#if TIME_AUTOMATIC
#if TIME_AUTOMATIC_LIST
            else if (h_widget == h_lb_autmomatic_time_ex)
            {
                 if (b_help_tip_set_and_show) {
                     i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF_EX]));
                     MENU_LOG_ON_FAIL(i4_ret);
                 } else {
                     i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF_EX]));
                     MENU_LOG_ON_FAIL(i4_ret);
                 }
            }
#endif
            else if (h_widget == h_lb_autmomatic_time)
            {
                 if (b_help_tip_set_and_show) {
                     i4_ret=menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_AUTOMATIC_TIME]));
                     MENU_LOG_ON_FAIL(i4_ret);
                 } else {
                     i4_ret=menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_AUTOMATIC_TIME]));
                     MENU_LOG_ON_FAIL(i4_ret);
                 }
            }
#endif
            b_help_tip_set_and_show = TRUE;
        }
        break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;

            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    if(h_lb_daylight_saving==h_widget)
                    {
                        i4_ret = _change_view(LOCAL_TIME_VIEW_LB_DLS_EX, 0);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else if (h_lb_time_zone==h_widget)
                    {
                        i4_ret = _change_view(LOCAL_TIME_VIEW_LB_TIME_ZONE_EX, 0);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else if (h_lb_time_format==h_widget)
                    {
                        i4_ret = _change_view(LOCAL_TIME_VIEW_LB_TF_EX, 0);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
                    else if (h_widget == h_lb_chg_country_code)
                    {
                        i4_ret = _change_view(LOCAL_TIME_VIEW_LB_CCC_EX, 0);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
#endif
#if TIME_AUTOMATIC
#if TIME_AUTOMATIC_LIST
                    else if (h_lb_autmomatic_time == h_widget)
                    {
                        i4_ret = _change_view(LOCAL_TIME_VIEW_AT_EX, 0);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
#endif
#endif
                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                break;

                case BTN_RETURN :
                {
                    menu_nav_back();
                    menu_list_arrow_hide(TRUE);
                }
                break;
            }

        }
        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}



/*----------------------------------------------------------------------------
 * Name: _lb_from_to_proc_fct
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
static INT32 _lb_timeZone_proc_fct(HANDLE_T    h_widget,
                                   UINT32      ui4_msg,
                                   VOID*       param1,
                                   VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    ui2_idx = _get_time_zone_idx();


    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        i4_ret=menu_list_set_idx(h_widget, ui2_idx);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=menu_list_adjust_rect(h_lb_time_zone);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_CURSOR_LEFT:
            {
                if (ui2_idx > 0)
                {
                    ui2_idx --;
                }
                else
                {
                    ui2_idx = MLM_MENU_KEY_BRCM_TIME_ZONE_NT - MLM_MENU_KEY_BRCM_TIME_ZONE_HST;
                }

                _set_time_zone_idx(ui2_idx);
                menu_list_set_idx(h_widget, ui2_idx);

                i4_ret=menu_list_adjust_rect(h_lb_time_zone);
                MENU_LOG_ON_FAIL(i4_ret);

                _update_dls_by_tz(ui2_idx);
                i4_ret = _update_title_info(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

				/*refresh item,the param is meanless*/
				i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
				MENU_LOG_ON_FAIL(i4_ret);

                c_wgl_repaint(h_widget, NULL, TRUE);

                return  WGLR_OK;
            }
            case BTN_CURSOR_RIGHT:
            {
                if (ui2_idx < MLM_MENU_KEY_BRCM_TIME_ZONE_NT - MLM_MENU_KEY_BRCM_TIME_ZONE_HST)
                {
                    ui2_idx ++;
                }
                else
                {
                    ui2_idx = 0;
                }

                _set_time_zone_idx(ui2_idx);
                menu_list_set_idx(h_widget, ui2_idx);

                i4_ret=menu_list_adjust_rect(h_lb_time_zone);
                MENU_LOG_ON_FAIL(i4_ret);

                _update_dls_by_tz(ui2_idx);
                i4_ret = _update_title_info(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

				/*refresh item,the param is meanless*/
				i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
				MENU_LOG_ON_FAIL(i4_ret);

                c_wgl_repaint(h_widget, NULL, TRUE);

                return  WGLR_OK;
            }
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    case WGL_MSG_KEY_UP:
        _tts_play(MLM_MENU_KEY_TIME_ZONE, MLM_MENU_KEY_BRCM_TIME_ZONE_HST+ui2_idx, TRUE);
        break;
#endif
    default:
        break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

static HANDLE_T h_focus = NULL_HANDLE;
static VOID _menu_dls_dialog_btn_cb_fct(UINT32 ui4_key_code)
{
    menu_tos_dialog_hide(TRUE);
    if(NULL_HANDLE != h_focus)
        c_wgl_set_focus(h_focus, WGL_SYNC_AUTO_REPAINT);
    h_focus = NULL_HANDLE;
    menu_pm_repaint();
}

static VOID dls_show_warming()
{
     menu_tos_dialog_show(MLM_MENU_KEY_EMPTY,
                          apw2s_help_tip[_HELP_TIP_TYPE_AUTO_DLS_NOT_SUPPORT],
                          MLM_MENU_KEY_OK,
                          _menu_dls_dialog_btn_cb_fct,
                          TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _eb_postal_code_fct
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
static INT32 _lb_dls_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        i4_ret=menu_list_set_idx(h_widget, _get_dls_idx());
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=menu_list_adjust_rect(h_lb_daylight_saving);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                {
                    ui2_idx = _get_dls_idx();

                    {
                        if (ui2_idx > DST_AUTO)
                            ui2_idx --;
                        else
                            ui2_idx = DST_OFF;
                    }
                    _set_dls_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(h_lb_daylight_saving);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = _update_title_info(TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    /*refresh item,the param is meanless*/
                    i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
                    MENU_LOG_ON_FAIL(i4_ret);
                    c_wgl_repaint(h_widget, NULL, TRUE);
                    return  WGLR_OK;
                }
                case BTN_CURSOR_RIGHT:
                {
                    ui2_idx = _get_dls_idx();

                    {
                        if (ui2_idx <  DST_OFF)
                            ui2_idx ++;
                        else
                            ui2_idx = DST_AUTO;
                    }
                    _set_dls_idx(ui2_idx);

                    menu_list_set_idx(h_widget, ui2_idx);

                    i4_ret=menu_list_adjust_rect(h_lb_daylight_saving);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = _update_title_info(TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    /*refresh item,the param is meanless*/
                    i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
                    MENU_LOG_ON_FAIL(i4_ret);
                    c_wgl_repaint(h_widget, NULL, TRUE);
                    return  WGLR_OK;
                }
                case BTN_CURSOR_DOWN:
                {
                    c_wgl_set_focus(h_lb_time_format, WGL_SYNC_AUTO_REPAINT);
                    return MENUR_OK;
                }

                default:
                    break;
            }
        }
#ifdef APP_TTS_SUPPORT
        case WGL_MSG_KEY_UP:
            _tts_play(MLM_MENU_KEY_TIME_DLS, MLM_MENU_KEY_TIME_DLS_AUTO+_get_dls_idx(), TRUE);
            break;
#endif
        default:
            break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _eb_postal_code_fct
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
static INT32 _eb_postal_code_fct(HANDLE_T    h_widget,
                                  UINT32      ui4_msg,
                                  VOID*       param1,
                                  VOID*       param2)
{
    INT32 i4_ret;
    static UTF16_T w2s_eb_text[10] = {0};
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    ACFG_COUNTRY_CODE_T t_country;

    a_cfg_custom_get_country_code(&t_country);
#endif

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS:
        {
            a_cfg_custom_get_postal_code(w2s_postal_code);
        #ifdef APP_ADD_COUNTRY_CODE_SUPPORT
            if (t_country != ACFG_COUNTRY_CODE_CA)
            {
                w2s_postal_code[5] = L'\0';
            }
        #endif
            _eb_postal_code_set_text_left( h_widget, (UTF16_T *)w2s_postal_code);
        }
        break;

        case WGL_MSG_LOSE_FOCUS:
        {
            _eb_postal_code_set_text(h_widget, w2s_postal_code);
            a_cfg_custom_set_postal_code(w2s_postal_code);
        }
        break;

        case WGL_MSG_KEY_DOWN:
        {
            UINT32  ui4_keycode = (UINT32)param1;
            UINT16  ui2_max_postal_code_length = MAX_POSTAL_CODE;

         #ifdef APP_ADD_COUNTRY_CODE_SUPPORT
            if (t_country == ACFG_COUNTRY_CODE_CA)
            {
                ui2_max_postal_code_length = MAX_POSTAL_CODE + 2;
            }
         #endif

            switch (ui4_keycode)
            {
                case BTN_DIGIT_0:
                case BTN_DIGIT_1:
                case BTN_DIGIT_2:
                case BTN_DIGIT_3:
                case BTN_DIGIT_4:
                case BTN_DIGIT_5:
                case BTN_DIGIT_6:
                case BTN_DIGIT_7:
                case BTN_DIGIT_8:
                case BTN_DIGIT_9:
                case BTN_KB_0:
                case BTN_KB_1:
                case BTN_KB_2:
                case BTN_KB_3:
                case BTN_KB_4:
                case BTN_KB_5:
                case BTN_KB_6:
                case BTN_KB_7:
                case BTN_KB_8:
                case BTN_KB_9:
                {

                    UTF16_T w2s_digital[3]={0};
                    CHAR    s_digital[3]={0};

                    _eb_postal_code_get_text( (UTF16_T *)w2s_eb_text);

                    UINT16 ui2_input = (UINT16)(ui4_keycode - BTN_DIGIT_0);

                    c_sprintf(s_digital, "%d",  ui2_input);
                    c_uc_ps_to_w2s(s_digital, w2s_digital, 3);

                    if (c_uc_w2s_strlen(w2s_eb_text) < ui2_max_postal_code_length)
                    {
                        c_uc_w2s_strncat(w2s_eb_text, w2s_digital,
                                         10 - c_uc_w2s_strlen(w2s_eb_text));

                        _eb_postal_code_set_text_left(h_widget, w2s_eb_text);
                    }
                    else
                    {

                        _eb_postal_code_set_text_left(h_widget, w2s_digital);

                    }

                    c_wgl_repaint(h_widget, NULL, TRUE);
                    return WMPR_DONE;
                }

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
                case BTN_CURSOR_UP:
                {
                    /* do nothing. */
                }
                break;

                case BTN_SELECT:
                {
                    if (t_country != ACFG_COUNTRY_CODE_CA)
                    {
                        i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_POSTAL_CODE_IDX);
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        e_view_type = LOCAL_TIME_VIEW_EB_EX;
                        i4_ret = _show_time_local_setting_pwd_vkb();
                        MENU_LOG_ON_FAIL(i4_ret);
                    }

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                break;
#else
                case BTN_CURSOR_UP:
                case BTN_SELECT:
                {
                    i4_ret = c_wgl_set_focus(h_lb_daylight_saving,
                                             WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                break;
#endif

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
                case BTN_CURSOR_DOWN:
#if MENU_SHOW_COUNTRY_CODE
                {
                    /* do nothing */
                }
#else
                {
                    i4_ret = menu_help_tip_keytip_set_focus(h_eb_postal_code,
                                                           0,
                                                           TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
#endif
                break;
#else
                case BTN_CURSOR_DOWN:
                {
                    i4_ret = menu_help_tip_keytip_set_focus(h_eb_postal_code,
                                                           0,
                                                           TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                break;
#endif
                case BTN_KB_BACKSPACE:
                case BTN_CURSOR_LEFT:
                {
                    UTF16_T w2s_temp[10] = {0};
                    UTF16_T ui2Strlen;

                    _eb_postal_code_get_text( (UTF16_T *)w2s_eb_text);

                    ui2Strlen = c_uc_w2s_strlen(w2s_eb_text);

                    if (ui2Strlen >0)
                    {
                        c_uc_w2s_strncpy(w2s_temp, w2s_eb_text, (ui2Strlen -1));
                    }

                    _eb_postal_code_set_text_left(h_widget, w2s_temp);
                    c_wgl_repaint(h_widget, NULL, TRUE);

                    return WGLR_OK;
                }

                default:
                    break;
            }
        }
    default:
        break;
    }
    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_tf_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    INT32  i4_ret=0;
    UINT8  ui1_idx=0;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        a_cfg_cust_get_time_format(&ui1_idx);

        i4_ret=menu_list_set_idx(h_widget, ui1_idx);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=menu_list_adjust_rect(h_lb_time_format);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                {
                    i4_ret = a_cfg_cust_get_time_format(&ui1_idx);
                    MENU_LOG_ON_FAIL(i4_ret);

                    ui1_idx ^= 1;

                    menu_list_set_idx(h_widget, ui1_idx);

                    i4_ret = a_cfg_cust_set_time_format(ui1_idx);
                    MENU_LOG_ON_FAIL(i4_ret);

                    //  ui1_idx == 0 , in 12_hour_format, ui1_idx == 1, in 24_hour_format
                    a_c4tv_apron_set_time_format((ui1_idx == 0) ? TRUE : FALSE);

                    i4_ret=menu_list_adjust_rect(h_lb_time_format);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = _update_title_info(TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    /*refresh item,the param is meanless*/
                   //i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
                   //MENU_LOG_ON_FAIL(i4_ret);

                    //c_wgl_repaint(h_widget, NULL, TRUE);
                    menu_pm_repaint();

                    return  WGLR_OK;
                }
                case BTN_CURSOR_UP:
                {
                    c_wgl_set_focus(h_lb_daylight_saving, WGL_SYNC_AUTO_REPAINT);
                }
                    break;
                case BTN_CURSOR_DOWN:
                {
                    c_wgl_set_focus(h_lb_chg_country_code, WGL_SYNC_AUTO_REPAINT);
                }
                    break;
                default:
                    break;
            }
        }
        case WGL_MSG_KEY_UP:
        {
            a_cfg_cust_get_time_format(&ui1_idx);
			#ifdef APP_TTS_SUPPORT
            _tts_play(MLM_MENU_KEY_TIME_FORMAT, MLM_MENU_KEY_12_HOUR+ui1_idx, TRUE);
			#endif
        }
            break;
        default:
            break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

static INT32 _show_lb_tf_ex_view(BOOL b_repaint)
{
    INT32    i4_ret;
    UINT8    ui2_crnt_ht;

#if TIME_AUTOMATIC
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#if TIME_AUTOMATIC_LIST
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#if TIME_AUTOMATIC_CHECKBOX
    i4_ret = _automatic_time_checkbox_hide();
	MENU_LOG_ON_FAIL(i4_ret);
#endif
#endif
    i4_ret = c_wgl_set_visibility(h_lb_time_zone,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone_ex ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = c_wgl_set_visibility(h_action_item_country,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);*/
#endif

    i4_ret = c_wgl_set_visibility(h_lb_time_format ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_cust_get_time_format(&ui2_crnt_ht);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_lb_time_format_ex,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                          NULL);    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_format_ex, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret= c_wgl_set_focus(h_lb_time_format_ex, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}


static INT32 _lb_tf_proc_ex_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if (0xffff != ui2_lst_last_hlt)
        {
            i4_ret=c_wgl_do_cmd(h_lb_time_format_ex,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(0),
                             NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            ui2_lst_last_hlt = 0xffff;
        }
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        i4_ret = c_wgl_do_cmd(h_lb_time_format_ex,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                i4_ret = a_cfg_cust_set_time_format((UINT8)ui2_crnt_ht);
                MENU_LOG_ON_FAIL(i4_ret);

                //  ui2_crnt_ht == 0 , in 12_hour_format, ui2_crnt_ht == 1, in 24_hour_format
                a_c4tv_apron_set_time_format((ui2_crnt_ht == 0) ? TRUE : FALSE);
            }
            case BTN_RETURN :
            {
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_FORMAT_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;
            case BTN_CURSOR_UP:
            {
                if(0 == ui2_crnt_ht)
                {
                    i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd(h_lb_time_format_ex,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    ui2_lst_last_hlt = ui2_crnt_ht;

                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
                break;
            case BTN_CURSOR_DOWN:
            {
                if((MLM_MENU_KEY_24_HOUR- MLM_MENU_KEY_12_HOUR) == ui2_crnt_ht)
                {
                    ui2_lst_last_hlt = ui2_crnt_ht;

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
                break;

            default:
                break;
        }
    }
    else if (WGL_MSG_KEY_UP==ui4_msg)
    {
#ifdef  APP_TTS_SUPPORT
        i4_ret = c_wgl_do_cmd(h_lb_time_format_ex,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        _tts_play(MLM_MENU_KEY_12_HOUR+ui2_crnt_ht, 0, FALSE);
#endif
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _creat_lb_time_format_ex(VOID)
{
    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_cnt_frm,
                               &t_rect,
                               _lb_tf_proc_ex_fct,
                               &t_lb_init,
                               NULL,
                               &h_lb_time_format_ex);
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (h_lb_time_format_ex,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(h_lb_time_format_ex,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT

static VOID _time_local_setting_country_info_thread_main (VOID* pv_arg)
{
    a_tv_net_reset_3rd_ap_data(APP_TV_NET_RESET_ITEM_ALL);

    x_thread_exit();
}

static INT32 _time_local_setting_page_insert_lb_ccc(VOID)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_i;

    WGL_LB_ITEM_T               at_items[3];
    WGL_LB_ITEM_IMG_SUIT_T t_img_suit_left;
    WGL_LB_ITEM_IMG_SUIT_T t_img_suit_right;

    i4_ret = c_wgl_do_cmd(h_lb_chg_country_code, WGL_CMD_LB_DEL_ALL, NULL, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Hide left/right arrow */
    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_left.h_highlight          = NULL_HANDLE;
    t_img_suit_left.h_selected_highlight = NULL_HANDLE;

    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_right.h_highlight          = NULL_HANDLE;
    t_img_suit_right.h_selected_highlight = NULL_HANDLE;

    for (ui2_i=0; ui2_i < COUNTRY_CODE_IDX_LAST; ui2_i++)
    {
        at_items[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[0].data.pt_img_suit = &t_img_suit_left;

        at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text   = MENU_TEXT(MLM_MENU_KEY_EMPTY);

        at_items[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[2].data.pt_img_suit = &t_img_suit_right;

        i4_ret = c_wgl_do_cmd(h_lb_chg_country_code, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static VOID _time_local_setting_page_show_confirm(VOID)
{
    b_show_clear_memory_from_tls = TRUE;
    //menu_page_set_hide_main_inpageswitch();
    //menu_nav_go(ui4_page_id_pass, NULL);
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_page_show_lb_ccc_ex_view
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_page_show_lb_ccc_ex_view(BOOL  b_repaint)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_crnt_ht = 0;

#if TIME_AUTOMATIC
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#if TIME_AUTOMATIC_LIST
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#if TIME_AUTOMATIC_CHECKBOX
    i4_ret = _automatic_time_checkbox_hide();
	MENU_LOG_ON_FAIL(i4_ret);
#endif
#endif

    i4_ret = c_wgl_set_visibility(h_lb_time_zone,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_format,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = c_wgl_set_visibility(h_action_item_country,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);*/
#endif

    ui2_crnt_ht = _time_local_setting_page_get_country_code_idx();
    ui2_lst_last_hlt = ui2_crnt_ht;

    i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_crnt_ht),
                          WGL_PACK(ui2_crnt_ht));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code_ex, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(h_lb_chg_country_code_ex, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_page_lb_ccc_ex_proc_fct
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_page_lb_ccc_ex_proc_fct(
                        HANDLE_T    h_widget,
                        UINT32      ui4_msg,
                        VOID*       param1,
                        VOID*       param2)
{
    INT32       i4_ret = MENUR_OK;
    UINT16      ui2_crnt_ht = 0;

    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        if (0xffff != ui2_lst_last_hlt)
        {
            i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                                  WGL_CMD_LB_HLT_ELEM,
                                  WGL_PACK(ui2_lst_last_hlt),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            ui2_lst_last_hlt = 0xffff;
        }
    }
    else if(WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;
        UINT16 ui2_old_idx = 0;

        switch (ui4_keycode)
        {
            case BTN_CUSTOM_1:
            case BTN_SELECT:
            {
                i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_crnt_ht),
                                      NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_list_get_idx(h_lb_chg_country_code, &ui2_old_idx);

                if (ui2_crnt_ht == ui2_old_idx)
                {
                    i4_ret = _change_view(
                                        LOCAL_TIME_VIEW_INIT,
                                        ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    break;
                }

                if (COUNTRY_CODE_IDX_MEX == ui2_crnt_ht)
                {
                    i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                                MLM_MENU_KEY_ZIP_CODE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_TAB_HELP_POSTAL_CODE;
                }
                else
                {
                    i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                                MLM_MENU_KEY_POSTAL_CODE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_SET_POSTAL_CODE;
                }

                i4_ret = _time_local_setting_page_set_country_code_idx(ui2_crnt_ht);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = _change_view(
                                    LOCAL_TIME_VIEW_INIT,
                                    ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_refresh();
                MENU_LOG_ON_FAIL(i4_ret);
                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);

                if (COUNTRY_CODE_IDX_US != ui2_crnt_ht)
                {
                    c_wgl_enable(h_eb_postal_code, FALSE);
                }
                else
                {
                    c_wgl_enable(h_eb_postal_code, TRUE);
                }

                menu_list_set_idx(h_lb_chg_country_code, ui2_crnt_ht);
                menu_list_adjust_rect(h_lb_chg_country_code);

                _time_local_setting_page_show_confirm();

                /*Create thread to reset 3rd info,because it will cost some time(3s).*/
                HANDLE_T                h_thread;
                if (x_thread_create(& h_thread,
                                    "_thread_time_local_reset_3rd_info",
                                    8192,
                                    127,
                                    _time_local_setting_country_info_thread_main,
                                    0,
                                    NULL)
                    != OSR_OK)
                {
                    DBG_ERROR(("create thread failed:_time_local_setting_country_info_thread_main\n"));
                }
            }
                break;
            case BTN_RETURN :
            {
                i4_ret = _change_view(
                                    LOCAL_TIME_VIEW_INIT,
                                    ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;
            case BTN_CURSOR_UP:
            {
                i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if(0 == ui2_crnt_ht)
                {
                    ui2_lst_last_hlt = ui2_crnt_ht;

                    i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
                break;
            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                                      WGL_CMD_LB_GET_HLT_INDEX,
                                      WGL_PACK(&ui2_crnt_ht),
                                      NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                //if((MLM_MENU_KEY_COUNTRY_USA - MLM_MENU_KEY_COUNTRY_CA) == ui2_crnt_ht)
                if ((COUNTRY_CODE_IDX_LAST -1) == ui2_crnt_ht)
                {
                    ui2_lst_last_hlt = ui2_crnt_ht;

                    i4_ret = menu_help_tip_keytip_set_focus(
                                    h_lb_chg_country_code_ex,
                                    0,
                                    TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    #ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT //fix DTV00607321
                    if (MENUR_INV_STATE == i4_ret)
                    {
                        return MENUR_OK;
                    }
                    #endif
                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
                break;
            default:
                break;
        }
    }
    else if(WGL_MSG_KEY_UP == ui4_msg)
    {
#ifdef APP_TTS_SUPPORT
        i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        _tts_play(_tts_get_country_mlm_key(ui2_crnt_ht), 0, FALSE);
#endif
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_page_creat_lb_ccc_ex
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_page_creat_lb_ccc_ex(VOID)
{

    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect;
    WGL_LB_IMG_ELEM_SET_T           t_img_elem;

    /* Listbox */
    c_memset(at_cols, 0, sizeof(WGL_LB_COL_INIT_T)*1);
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    c_memset(&t_lb_init, 0, sizeof(WGL_LB_INIT_T));
    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;
    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_cnt_frm,
                               &t_rect,
                               _time_local_setting_page_lb_ccc_ex_proc_fct,
                               &t_lb_init,
                               NULL,
                               &h_lb_chg_country_code_ex);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_img_elem, 0, sizeof(WGL_LB_IMG_ELEM_SET_T));
    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd (h_lb_chg_country_code_ex,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(&t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_page_get_country_code_idx
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *
 *
 *---------------------------------------------------------------------------*/
static UINT16 _time_local_setting_page_get_country_code_idx(VOID)
{
    ACFG_COUNTRY_CODE_T t_country_code = ACFG_COUNTRY_CODE_US;
    UINT16              ui2_country_code_idx = 0;

    a_cfg_custom_get_country_code(&t_country_code);
    if (ACFG_COUNTRY_CODE_US == t_country_code)
    {
        ui2_country_code_idx = COUNTRY_CODE_IDX_US;
    }
    else if (ACFG_COUNTRY_CODE_MEX == t_country_code)
    {
        ui2_country_code_idx = COUNTRY_CODE_IDX_MEX;
    }
    else if (ACFG_COUNTRY_CODE_CA == t_country_code)
    {
        ui2_country_code_idx = COUNTRY_CODE_IDX_CA;
    }
    else
    {
        ui2_country_code_idx = COUNTRY_CODE_IDX_US;
    }

    return ui2_country_code_idx;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_page_set_country_code_idx
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *
 *
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_page_set_country_code_idx(UINT16 ui2_idx)
{
    INT32    i4_ret = MENUR_OK;

    switch (ui2_idx)
    {
        case COUNTRY_CODE_IDX_CA:
            a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_CA);
            break;

        case COUNTRY_CODE_IDX_MEX:
            a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_MEX);
            break;

        case COUNTRY_CODE_IDX_US:
        default:
            a_cfg_custom_set_country_code(ACFG_COUNTRY_CODE_US);
            break;
    }

    a_cfg_custom_get_postal_code(w2s_postal_code);
    if (ui2_idx != COUNTRY_CODE_IDX_CA)
    {
        w2s_postal_code[5] = L'\0';
    }
    i4_ret = _eb_postal_code_set_text(h_eb_postal_code, (UTF16_T*)w2s_postal_code);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_eb_postal_code, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_page_lb_ccc_proc_fct
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_page_lb_ccc_proc_fct(
                            HANDLE_T    h_widget,
                            UINT32      ui4_msg,
                            VOID*       param1,
                            VOID*       param2)
{
    INT32   i4_ret = MENUR_OK;
    UINT16  ui2_idx = 0;

    ui2_idx = _time_local_setting_page_get_country_code_idx();

    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        i4_ret = menu_list_set_idx(h_widget,
                                   ui2_idx);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_list_adjust_rect(h_lb_chg_country_code);
        MENU_LOG_ON_FAIL(i4_ret);

        if (COUNTRY_CODE_IDX_MEX == ui2_idx)
        {
            i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                        MLM_MENU_KEY_ZIP_CODE);
            MENU_LOG_ON_FAIL(i4_ret);

            apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_TAB_HELP_POSTAL_CODE;
        }
        else
        {
            i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                        MLM_MENU_KEY_POSTAL_CODE);
            MENU_LOG_ON_FAIL(i4_ret);

            apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_SET_POSTAL_CODE;
        }

        if (COUNTRY_CODE_IDX_US != ui2_idx)
        {
            c_wgl_enable(h_eb_postal_code, FALSE);
        }
        else
        {
            c_wgl_enable(h_eb_postal_code, TRUE);
        }
    }

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
                //param1 = (VOID*)BTN_SELECT;
                //break;
            #if 1
            {
                if (BTN_CURSOR_LEFT == ui4_keycode)
                {
                    if (ui2_idx > 0)
                    {
                        ui2_idx --;
                    }
                    else
                    {
                        ui2_idx = COUNTRY_CODE_IDX_LAST - 1;
                    }
                }
                else
                {
                    if (ui2_idx < COUNTRY_CODE_IDX_LAST - 1)
                    {
                        ui2_idx ++;
                    }
                    else
                    {
                        ui2_idx = 0;
                    }
                }

                i4_ret = _time_local_setting_page_set_country_code_idx(ui2_idx);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_list_set_idx(h_widget, ui2_idx);

                i4_ret = menu_list_adjust_rect(h_lb_chg_country_code);
                MENU_LOG_ON_FAIL(i4_ret);

                if (COUNTRY_CODE_IDX_MEX == ui2_idx)
                {
                    i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                                MLM_MENU_KEY_ZIP_CODE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_TAB_HELP_POSTAL_CODE;
                }
                else
                {
                    i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                                MLM_MENU_KEY_POSTAL_CODE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_SET_POSTAL_CODE;
                }

                if (COUNTRY_CODE_IDX_US != ui2_idx)
                {
                    c_wgl_enable(h_eb_postal_code, FALSE);
                }
                else
                {
                    c_wgl_enable(h_eb_postal_code, TRUE);
                }

                i4_ret = c_wgl_repaint(h_eb_postal_code,
                                       NULL,
                                       TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                _time_local_setting_page_show_confirm();
            }

            return MENUR_OK;
            #endif
            case BTN_CURSOR_UP:
            {
                c_wgl_set_focus(h_lb_time_format, WGL_NO_AUTO_REPAINT);
                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }
            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_help_tip_keytip_set_focus(
                                h_lb_chg_country_code,
                                0,
                                TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }
            default:
                break;
            }
        }
            break;
#ifdef APP_TTS_SUPPORT
        case WGL_MSG_KEY_UP:
            _tts_play(MLM_MENU_KEY_COUNTRY, _tts_get_country_mlm_key(ui2_idx), TRUE);
            break;
#endif
        default:
            break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

#endif


/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        /* hide old help tip first*/
        menu_hide_help_tip();
        /* trigger help tip */
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            MENU_CHK_FAIL (menu_nav_go_home_menu ()) ;
            menu_list_arrow_hide(FALSE);
            ui2_lst_last_hlt = 0xffff;
            return MENUR_OK ;

        case BTN_CURSOR_UP:
            break ;

        case BTN_CURSOR_DOWN :

            menu_set_focus_on_backbar(TRUE);

            break ;

         case BTN_RETURN :
         {
            menu_list_arrow_hide(FALSE);

            if (LOCAL_TIME_VIEW_LB_TIME_ZONE_EX == e_view_type)
            {
                _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX);
                menu_pm_repaint();
            }
            else if(LOCAL_TIME_VIEW_LB_DLS_EX == e_view_type)
            {
                _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_DLS_IDX);
                menu_pm_repaint();
            }
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
            else if(LOCAL_TIME_VIEW_LB_CCC_EX == e_view_type)
            {
                _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX);
                menu_pm_repaint();
            }
#endif
            else if (LOCAL_TIME_VIEW_EB_EX == e_view_type)
            {
                e_view_type = LOCAL_TIME_VIEW_INIT;
                _hide_time_local_setting_pwd_vkb();
                menu_pm_repaint();
            }
#if TIME_AUTOMATIC_LIST
            else if(LOCAL_TIME_VIEW_AT_EX == e_view_type)
            {
                _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX);
                menu_pm_repaint();
            }
#endif
            else
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

                MENU_CHK_FAIL (menu_nav_back ()) ;
            }
            ui2_lst_last_hlt = 0xffff;
         }
         break;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32 i4_ret;

    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        #ifdef APP_TTS_SUPPORT
        a_app_tts_play(L"back", c_uc_w2s_strlen(L"back"));
        #endif

        menu_hide_help_tip();
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
        #endif
        case BTN_RETURN :
        case BTN_SELECT :
            b_help_tip_back_press = FALSE;
            menu_list_arrow_hide(FALSE);
            if (LOCAL_TIME_VIEW_LB_TIME_ZONE_EX == e_view_type)
            {
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(LOCAL_TIME_VIEW_LB_DLS_EX == e_view_type)
            {
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_DLS_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(LOCAL_TIME_VIEW_LB_TF_EX == e_view_type)
            {
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_FORMAT_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
            else if(LOCAL_TIME_VIEW_LB_CCC_EX == e_view_type)
            {
                i4_ret = _change_view(
                                    LOCAL_TIME_VIEW_INIT,
                                    ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
#endif
            else if (LOCAL_TIME_VIEW_EB_EX == e_view_type)
            {
                e_view_type = LOCAL_TIME_VIEW_INIT;
                _hide_time_local_setting_pwd_vkb();
                menu_pm_repaint();
            }
#if TIME_AUTOMATIC_LIST
            else if(LOCAL_TIME_VIEW_AT_EX == e_view_type)
            {
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
#endif
            else
            {
                b_help_tip_back_press = TRUE;
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

                MENU_CHK_FAIL (menu_nav_back ()) ;
            }
            ui2_lst_last_hlt = 0xffff;
            return MENUR_OK ;

        case BTN_CURSOR_DOWN:
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            if(LOCAL_TIME_VIEW_INIT == e_view_type)
            {

                MENU_CHK_FAIL (c_wgl_set_focus (h_lb_autmomatic_time, WGL_SYNC_AUTO_REPAINT));
                //MENU_CHK_FAIL (c_wgl_set_focus (h_lb_time_zone, WGL_SYNC_AUTO_REPAINT));
            }
            else if (LOCAL_TIME_VIEW_LB_TIME_ZONE_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TIMEZONE_EX]));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (h_lb_time_zone_ex, WGL_SYNC_AUTO_REPAINT));
            }
            else if (LOCAL_TIME_VIEW_LB_DLS_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_DLS_EX]));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (h_lb_daylight_saving_ex, WGL_SYNC_AUTO_REPAINT));
            }
            else if (LOCAL_TIME_VIEW_LB_TF_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF_EX]));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (h_lb_time_format_ex, WGL_SYNC_AUTO_REPAINT));
            }
            else if (LOCAL_TIME_VIEW_LB_CCC_EX == e_view_type)
            {

                i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_CHG_COUNTRY_CODE_EX]));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (h_lb_chg_country_code_ex, WGL_SYNC_AUTO_REPAINT));
            }
            else if (LOCAL_TIME_VIEW_EB_EX == e_view_type)
            {
                a_vkb_set_focus(h_vkb);
            }
#if TIME_AUTOMATIC_LIST
            else if (LOCAL_TIME_VIEW_AT_EX == e_view_type)
            {
                i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_AUTOMATIC_TIME_EX]));
                MENU_LOG_ON_FAIL(i4_ret);

                MENU_CHK_FAIL (c_wgl_set_focus (h_lb_autmomatic_time_ex, WGL_SYNC_AUTO_REPAINT));
            }
#endif
            menu_pm_repaint();
            /* update help tip */
            break ;

        case BTN_CURSOR_UP :
            MENU_CHK_FAIL (menu_set_focus_on_homebar (TRUE));

            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _show_init_view
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
static INT32 _show_init_view(BOOL b_repaint, UINT8 ui1FocusIdx)
{
    INT32        i4_ret;
    UINT8        ui2_idx = 0;
	UINT8		 ui1_automatic;

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
#if TIME_AUTOMATIC
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
#if TIME_AUTOMATIC_LIST
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    ui1_automatic = _get_automatic_time_idx();
#if TIME_AUTOMATIC_CHECKBOX
    i4_ret = _automatic_time_checkbox_show(ui1_automatic);
	MENU_LOG_ON_FAIL(i4_ret);
#endif
#endif
    i4_ret = c_wgl_set_visibility(h_lb_time_format, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_format_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = c_wgl_set_visibility(h_action_item_country, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    ui2_idx = _time_local_setting_page_get_country_code_idx();

    if (COUNTRY_CODE_IDX_US != ui2_idx)
    {
        c_wgl_enable(h_eb_postal_code, FALSE);
    }
    else
    {
        c_wgl_enable(h_eb_postal_code, TRUE);
    }

    switch(ui1FocusIdx)
    {
        case ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX:
            i4_ret= c_wgl_set_focus(h_lb_time_zone,WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
            break;

        case ATSC_TIME_LOCAL_SET_DLS_IDX:
            i4_ret= c_wgl_set_focus(h_lb_daylight_saving,WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
            break;

        case ATSC_TIME_LOCAL_SET_TIME_FORMAT_IDX:
            i4_ret= c_wgl_set_focus(h_lb_time_format,WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
            break;
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
        case ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX:
        {
            i4_ret = c_wgl_set_focus(h_lb_chg_country_code, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case ATSC_TIME_LOCAL_SET_COUNTRY_IDX:
        {
            /*i4_ret = c_wgl_set_focus(h_action_item_country, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);*/
        }
            break;
#endif
       case ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX:
        {
            i4_ret = c_wgl_set_focus(h_lb_autmomatic_time, WGL_NO_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
           break;

        default:
            break;
    }

    menu_list_arrow_hide(FALSE);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _change_view
 *
 * Description:
 *  if start to scan unsuccessfully, it will show "scan error" message, and
 * callback the notify to CLI (if any).
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _change_view(LOCAL_TIME_VIEW_TYPE_T  e_local_time_view_type, UINT8 ui1FocusIdx)
{
    INT32        i4_ret;

    e_view_type = e_local_time_view_type;

    /* tips */
    _time_local_setting_update_shadow_item_pos();

    switch(e_view_type)
    {
        case LOCAL_TIME_VIEW_INIT:
        {
            /* title */
            /*menu_main_set_title(MLM_MENU_KEY_TIME_NOT_AVAILABLE);*/
            DBG_LOG_PRINT(("[ TIME +++ ] {%s %s() %d}. remove ***MLM_MENU_KEY_TIME_NOT_AVAILABLE fail!!\n",__FILE__, __FUNCTION__, __LINE__));
            i4_ret = _ntp_timer_start();
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = _update_title_info(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
            b_help_tip_set_and_show = FALSE;

            i4_ret=_show_init_view(TRUE, ui1FocusIdx);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_list_arrow_hide(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;

        case LOCAL_TIME_VIEW_LB_TIME_ZONE_EX:
        {
            i4_ret = _ntp_timer_stop();
            MENU_LOG_ON_FAIL(i4_ret);

            menu_main_set_title(MLM_MENU_KEY_TIME_ZONE);
            i4_ret =_show_lb_time_zone_ex_view(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;
        case LOCAL_TIME_VIEW_LB_DLS_EX:
        {
            i4_ret = _ntp_timer_stop();
            MENU_LOG_ON_FAIL(i4_ret);

            MENU_LOG_ON_FAIL(menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_DLS_EX])));

            menu_main_set_title(MLM_MENU_KEY_TIME_DLS);
            i4_ret =_show_lb_dls_ex_view(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_list_arrow_hide(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;
        case LOCAL_TIME_VIEW_LB_TF_EX:
        {
            i4_ret = _ntp_timer_stop();
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_TF_EX]));
            MENU_LOG_ON_FAIL(i4_ret);

            menu_main_set_title(MLM_MENU_KEY_TIME_FORMAT);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =_show_lb_tf_ex_view(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_list_arrow_hide(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
        break;
    #ifdef APP_ADD_COUNTRY_CODE_SUPPORT
        case LOCAL_TIME_VIEW_LB_CCC_EX:
        {
            i4_ret = _ntp_timer_stop();
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_CHG_COUNTRY_CODE_EX]));
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_main_set_title(MLM_MENU_KEY_COUNTRY);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = _time_local_setting_page_show_lb_ccc_ex_view(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_list_arrow_hide(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;
    #endif
#if TIME_AUTOMATIC_LIST
        case LOCAL_TIME_VIEW_AT_EX:
        {
            DBG_LOG_PRINT(("[ TIME +++ ] {%s %s() %d}. LOCAL_TIME_VIEW_AT_EX !\n",__FILE__, __FUNCTION__, __LINE__));
            i4_ret = _ntp_timer_stop();
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_set_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_AUTOMATIC_TIME]));
            MENU_LOG_ON_FAIL(i4_ret);

            menu_main_set_title(MLM_MENU_KEY_TIME_ZONE_AT);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret =_show_lb_automatic_time_ex_view(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = menu_list_arrow_hide(FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        break;
#endif
        default:
        break;
    }

    //_time_local_setting_update_shadow_item_pos();

    if(ui1FocusIdx == ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX)
    {
        /*refresh item,the param is meanless*/
        i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _change_lang(VOID)
{
    INT32  i4_ret = 0;
    UINT8  ui2_i = 0;
    UINT16 ui2_elem_num=0;
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    ACFG_COUNTRY_CODE_T t_country;
#endif

    i4_ret=menu_list_chg_lang(h_lb_daylight_saving,
                       MLM_MENU_KEY_TIME_DLS,
                       MLM_MENU_KEY_TIME_DLS_AUTO,
                       MLM_MENU_KEY_TIME_DLS_OFF);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_list_adjust_rect(h_lb_daylight_saving);

    i4_ret=menu_list_chg_lang(h_lb_time_zone,
                       MLM_MENU_KEY_TIME_ZONE,
                       MLM_MENU_KEY_BRCM_TIME_ZONE_HST,
                       MLM_MENU_KEY_BRCM_TIME_ZONE_NT);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_list_adjust_rect(h_lb_time_zone);

    i4_ret=menu_list_chg_lang(h_lb_time_format,
                       MLM_MENU_KEY_TIME_FORMAT,
                       MLM_MENU_KEY_12_HOUR,
                       MLM_MENU_KEY_24_HOUR);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_list_adjust_rect(h_lb_time_format);

    ui2_elem_num = MLM_MENU_KEY_24_HOUR - MLM_MENU_KEY_12_HOUR+1;
    i4_ret=c_wgl_do_cmd(h_lb_time_format_ex,
                        WGL_CMD_LB_SET_ELEM_NUM,
                        WGL_PACK(ui2_elem_num),
                        NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_lb_time_format_ex,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(MENU_TEXT(MLM_MENU_KEY_12_HOUR + ui2_i)));
        MENU_LOG_ON_FAIL(i4_ret);
    }

#if TIME_AUTOMATIC_LIST
    i4_ret=menu_list_chg_lang(h_lb_autmomatic_time,
                          MLM_MENU_KEY_TIME_ZONE_AT,
                          MLM_MENU_KEY_TIME_ZONE_AT_CHECK,
                          MLM_MENU_KEY_TIME_ZONE_AT_NOCHECK);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_list_adjust_rect(h_lb_autmomatic_time);
    ui2_elem_num = MLM_MENU_KEY_TIME_ZONE_AT_NOCHECK - MLM_MENU_KEY_TIME_ZONE_AT_CHECK + 1;
    i4_ret=c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                        WGL_CMD_LB_SET_ELEM_NUM,
                        WGL_PACK(ui2_elem_num),
                        NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(MENU_TEXT(MLM_MENU_KEY_TIME_ZONE_AT_CHECK + ui2_i)));
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif
#if TIME_AUTOMATIC_CHECKBOX
i4_ret=menu_action_chg_lang(h_lb_autmomatic_time,
                      MLM_MENU_KEY_TIME_ZONE_AT,
                      MLM_MENU_KEY_EMPTY);
MENU_LOG_ON_FAIL(i4_ret);
#endif

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    a_cfg_custom_get_country_code(&t_country);
    if (t_country == ACFG_COUNTRY_CODE_MEX)
    {
        i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                    MLM_MENU_KEY_ZIP_CODE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                    MLM_MENU_KEY_POSTAL_CODE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = menu_list_chg_lang(h_lb_chg_country_code,
                                MLM_MENU_KEY_COUNTRY,
                                aui2_country_code_txt[COUNTRY_CODE_IDX_LAST-2],
                                aui2_country_code_txt[COUNTRY_CODE_IDX_LAST-1]);
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui2_i=0; ui2_i<COUNTRY_CODE_IDX_LAST; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_lb_chg_country_code,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(ui2_i, 1),
                              WGL_PACK(MENU_TEXT(aui2_country_code_txt[ui2_i])));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = menu_list_adjust_rect(h_lb_chg_country_code);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = menu_action_chg_lang(h_action_item_country,
                                MLM_MENU_KEY_COUNTRY,
                                MLM_MENU_KEY_EMPTY);*/
    MENU_CHK_FAIL(i4_ret);
#else
    i4_ret = menu_edit_chg_lang(h_eb_postal_code,
                                MLM_MENU_KEY_POSTAL_CODE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    MENU_LOG_ON_FAIL(i4_ret);

    /* set time zone item */
    ui2_elem_num = MLM_MENU_KEY_BRCM_TIME_ZONE_NT  - MLM_MENU_KEY_BRCM_TIME_ZONE_HST + 1 ;
    i4_ret=c_wgl_do_cmd(h_lb_time_zone_ex,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_elem_num),
                 NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2 (ui2_i, 0),
                     WGL_PACK(MENU_TEXT(MLM_MENU_KEY_BRCM_TIME_ZONE_HST + ui2_i)));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* set day night saving item*/
    ui2_elem_num = (MLM_MENU_KEY_TIME_DLS_OFF - MLM_MENU_KEY_TIME_DLS_AUTO)+1;
    i4_ret=c_wgl_do_cmd(h_lb_daylight_saving_ex,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_elem_num),
                 NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_i = 0; ui2_i < ui2_elem_num; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                     WGL_CMD_LB_SET_ITEM_TEXT,
                     WGL_PACK_2 (ui2_i, 0),
                     WGL_PACK(MENU_TEXT(MLM_MENU_KEY_TIME_DLS_AUTO + ui2_i)));
        MENU_LOG_ON_FAIL(i4_ret);
    }

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    ui2_elem_num = COUNTRY_CODE_IDX_LAST; //(MLM_MENU_KEY_COUNTRY_USA- MLM_MENU_KEY_COUNTRY_CA)+1;
    i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK(ui2_elem_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui2_i=0; ui2_i<ui2_elem_num; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_lb_chg_country_code_ex,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 (ui2_i, 0),
                              WGL_PACK(MENU_TEXT(aui2_country_code_txt[ui2_i]))/*WGL_PACK(MENU_TEXT(MLM_MENU_KEY_COUNTRY_CA+ui2_i))*/);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif

    i4_ret=menu_change_help_tip_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        global functions implementation
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _show_lb_time_zone_ex_view
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _show_lb_time_zone_ex_view(BOOL b_repaint)
{
    GL_RECT_T           t_rect = {0};
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;
    UINT16   ui2_hlt_pos;

    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#if TIME_AUTOMATIC_LIST
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#if TIME_AUTOMATIC_CHECKBOX
    i4_ret = _automatic_time_checkbox_hide();
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    i4_ret = c_wgl_set_visibility(h_lb_time_zone,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_format,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = c_wgl_set_visibility(h_action_item_country,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);*/
#endif

    i4_ret= c_wgl_set_focus(h_lb_time_zone_ex,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_crnt_ht = _get_time_zone_idx();
    ui2_hlt_pos = (ui2_crnt_ht >= PAGE_TIME_ZONE_ITEM_NUM) ? PAGE_TIME_ZONE_ITEM_NUM-1 : ui2_crnt_ht;

    i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_crnt_ht),
                          WGL_PACK(ui2_hlt_pos));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      12,
                      CONTENT_W,
                      PAGE_TIME_ZONE_ITEM_NUM*MENU_ITEM_V_HEIGHT);

    c_wgl_move(h_lb_time_zone_ex, &t_rect, FALSE);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone_ex,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_arrow_state_update(h_lb_time_zone_ex, BTN_INVALID, FALSE);

    if (b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _show_lb_time_zone_ex_view
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _show_lb_dls_ex_view(BOOL b_repaint)
{
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;

    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#if TIME_AUTOMATIC_LIST
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time_ex,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#if TIME_AUTOMATIC_CHECKBOX
    i4_ret = _automatic_time_checkbox_hide();
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    i4_ret = c_wgl_set_visibility(h_lb_time_zone,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone_ex ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_format,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code_ex, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = c_wgl_set_visibility(h_action_item_country,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);*/
#endif

    ui2_crnt_ht = _get_dls_idx();

    i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                      WGL_CMD_LB_HLT_ELEM,
                      WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                      NULL);    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving_ex,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret= c_wgl_set_focus(h_lb_daylight_saving_ex,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);


    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}


static INT32 _lb_time_zone_ex_proc_fct(HANDLE_T    h_widget,
                                        UINT32      ui4_msg,
                                        VOID*       param1,
                                        VOID*       param2)
{
    INT32   i4_ret;
    UINT16  ui2_crnt_ht;
    UINT16  ui2_hlt_pos = 0;


    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if (0xffff != ui2_lst_last_hlt)
        {
            ui2_hlt_pos = (ui2_lst_last_hlt >= PAGE_TIME_ZONE_ITEM_NUM) ? PAGE_TIME_ZONE_ITEM_NUM-1 : ui2_hlt_pos;

            i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                                  WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                  WGL_PACK(ui2_lst_last_hlt),
                                  WGL_PACK(ui2_hlt_pos));
            MENU_LOG_ON_FAIL(i4_ret);

            ui2_lst_last_hlt = 0xffff;
        }
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;

        menu_list_arrow_state_update(h_lb_time_zone_ex, ui4_keycode, TRUE);

        switch (ui4_keycode)
        {
            case BTN_CUSTOM_1:
            case BTN_SELECT:
            {
                i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                 _set_time_zone_idx(ui2_crnt_ht);
                 _update_dls_by_tz(ui2_crnt_ht);
                menu_list_arrow_hide(FALSE);

                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_RETURN :
            {
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_CURSOR_UP:
            {
                i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if(0==ui2_crnt_ht)
                {
                    ui2_lst_last_hlt =ui2_crnt_ht;

                    i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if((MLM_MENU_KEY_BRCM_TIME_ZONE_NT - MLM_MENU_KEY_BRCM_TIME_ZONE_HST) == ui2_crnt_ht)
                {
                    ui2_lst_last_hlt =ui2_crnt_ht;
                    i4_ret=menu_help_tip_keytip_set_focus(h_lb_time_zone_ex,0,TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    #ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT //fix DTV00607321
                    if (MENUR_INV_STATE == i4_ret)
                    {
                        return MENUR_OK;
                    }
                    #endif

                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            default:
            break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd(h_lb_time_zone_ex,
                             WGL_CMD_LB_GET_HLT_INDEX,
                             WGL_PACK(&ui2_crnt_ht),
                             NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        _tts_play(MLM_MENU_KEY_BRCM_TIME_ZONE_HST+ui2_crnt_ht, 0, FALSE);
    }
#endif
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _lb_time_dls_ex_fct(HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       param1,
                                VOID*       param2)
{
    INT32 i4_ret;
    UINT16 ui2_crnt_ht;
    UINT16  ui2_tz_idx = _get_time_zone_idx();

    DBG_INFO(("[MENU][DST][%s %d] current tz idx = %d\n",__FUNCTION__,__LINE__,ui2_tz_idx));
    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if (0xffff != ui2_lst_last_hlt)
        {
            i4_ret=c_wgl_do_cmd(h_lb_daylight_saving_ex,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(ui2_lst_last_hlt),
                             NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            ui2_lst_last_hlt = 0xffff;
        }
        else
        {
            MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_lb_daylight_saving_ex,
                                           WGL_CMD_LB_HLT_ELEM,
                                           WGL_PACK( _get_dls_idx()),
                                           NULL));
        }
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
            case BTN_CUSTOM_1:
            case BTN_SELECT:
            {
                i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                 _set_dls_idx(ui2_crnt_ht);

                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_DLS_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_RETURN :
            {
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_DLS_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            break;

            case BTN_CURSOR_UP:
            {
                i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if(0==ui2_crnt_ht)
                {
                    ui2_lst_last_hlt =ui2_crnt_ht;

                    i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
            break;

            case BTN_CURSOR_DOWN:
            {
                i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                if((MLM_MENU_KEY_TIME_DLS_OFF - MLM_MENU_KEY_TIME_DLS_AUTO)==ui2_crnt_ht)
                {
                    ui2_lst_last_hlt =ui2_crnt_ht;
                    i4_ret=menu_help_tip_keytip_set_focus(h_lb_daylight_saving_ex,0,TRUE);
                    MENU_LOG_ON_FAIL(i4_ret);
                    #ifdef APP_VIEW_MODE_GRAY_OUT_SUPPORT //fix DTV00607321
                    if (MENUR_INV_STATE == i4_ret)
                    {
                        return MENUR_OK;
                    }
                    #endif

                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);
                    return MENUR_OK;
                }
            }
            break;

            default:
            break;
        }
    }
    else if (WGL_MSG_KEY_UP == ui4_msg)
    {
#ifdef APP_TTS_SUPPORT
        i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                                     WGL_CMD_LB_GET_HLT_INDEX,
                                     WGL_PACK(&ui2_crnt_ht),
                                     NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        _tts_play(MLM_MENU_KEY_TIME_DLS_AUTO+ui2_crnt_ht, 0, FALSE);
#endif
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


/*-----------------------------------------------------------------------------
                        global functions implementation
-----------------------------------------------------------------------------*/

static INT32 _creat_lb_time_zone_ex(VOID)
{

    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      PAGE_TIME_ZONE_ITEM_NUM*MENU_ITEM_V_HEIGHT);

    g_t_list_tz_rect.i4_left = t_rect.i4_left;
    g_t_list_tz_rect.i4_top = t_rect.i4_top;
    g_t_list_tz_rect.i4_right = t_rect.i4_right;
    g_t_list_tz_rect.i4_bottom = t_rect.i4_bottom;

    i4_ret = menu_list2_create(h_cnt_frm,
                               &t_rect,
                               _lb_time_zone_ex_proc_fct,
                               &t_lb_init,
                               NULL,
                               &h_lb_time_zone_ex);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left   = MENU_ITEM_BAR_CNT_INSET_L;
    t_inset.i4_right  = MENU_ITEM_BAR_CNT_INSET_R;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (h_lb_time_zone_ex,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (h_lb_time_zone_ex,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    menu_list_arrow_create(h_cnt_frm, &t_rect);

    return MENUR_OK;
}



static INT32 _creat_lb_daylight_saving_ex(VOID)
{

    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_cnt_frm,
                               &t_rect,
                               _lb_time_dls_ex_fct,
                               &t_lb_init,
                               NULL,
                               &h_lb_daylight_saving_ex);
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (h_lb_daylight_saving_ex,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(h_lb_daylight_saving_ex,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_set_postal_code
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_set_postal_code(VOID)
{
    UTF16_T      w2s_star_txt[TIME_LOCAL_SETTING_MAX_LEN+1] = {0};
    INT32        i4_ret = MENUR_OK;
    //ACFG_COUNTRY_CODE_T t_country;

    //a_cfg_custom_get_country_code(&t_country);

    i4_ret = a_vkb_do_cmd(h_vkb,
                          VKB_CMD_GET_TEXT,
                          (VOID*)w2s_star_txt,
                          (VOID*)(TIME_LOCAL_SETTING_MAX_LEN+1));
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strcpy(w2s_postal_code, w2s_star_txt);
    a_cfg_custom_set_postal_code(w2s_star_txt);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _show_time_local_setting_pwd_vkb
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _show_time_local_setting_pwd_vkb(VOID)
{
    INT32        i4_ret = MENUR_OK;
    UTF16_T      w2s_star_txt[TIME_LOCAL_SETTING_MAX_LEN+1] = {0};
    UINT32       ui4_len = 0;
    ACFG_COUNTRY_CODE_T t_country;

    a_cfg_custom_get_country_code(&t_country);
    if (t_country != ACFG_COUNTRY_CODE_CA)
    {
        /* if not canada, do not show vkb */
        return MENUR_OK;
    }

    a_vkb_do_cmd (h_vkb,
                  VKB_CMD_SET_MAX_CHAR_NUM,
                  (VOID*)(TIME_LOCAL_SETTING_MAX_LEN+1),
                  NULL);

    i4_ret = c_wgl_do_cmd(h_eb_postal_code,
                          WGL_CMD_EB_GET_TEXT,
                          (VOID*)w2s_star_txt,
                          (VOID*)(TIME_LOCAL_SETTING_MAX_LEN));
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_len = c_uc_w2s_strlen(w2s_star_txt);
    if (ui4_len > 0)
    {
        w2s_star_txt[ui4_len-1] = 0;
    }
    else
    {
        c_uc_w2s_strncpy(w2s_star_txt, w2s_postal_code, TIME_LOCAL_SETTING_MAX_LEN);
        w2s_star_txt[TIME_LOCAL_SETTING_MAX_LEN] = 0;
    }

    /* set initial editbox text */
    a_vkb_do_cmd (h_vkb,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_star_txt,
                  (VOID*) 0xFF);

    a_vkb_set_focus(h_vkb);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = c_wgl_set_visibility(h_action_item_country, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);*/

    i4_ret = a_vkb_set_visibility(h_vkb,TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _hide_time_local_setting_pwd_vkb
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _hide_time_local_setting_pwd_vkb(VOID)
{
    INT32    i4_ret = MENUR_OK;

    i4_ret = a_vkb_set_visibility(h_vkb, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    /*i4_ret = c_wgl_set_visibility(h_action_item_country, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);*/

    menu_set_and_show_help_tip(MENU_TEXT(apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE]));

    i4_ret = c_wgl_set_focus(h_eb_postal_code, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_repaint(h_cnt_frm, NULL, TRUE);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_pwd_vbk_data_change_nfy
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_pwd_vbk_data_change_nfy(
    VOID*    pv_tag,
    UINT32   ui4_msg,
    VOID*    pv_param1,
    VOID*    pv_param2)
{
    INT32   i4_ret       = WDKR_OK;

    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_bottom = FALSE;
        BOOL     b_is_ok_btn = FALSE;

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
                e_view_type = LOCAL_TIME_VIEW_INIT;
                i4_ret = _hide_time_local_setting_pwd_vkb();
                MENU_LOG_ON_FAIL(i4_ret);
                break;

            case BTN_SELECT:
            {
                i4_ret = a_vkb_current_is_bottom_row(h_vkb,
                                                     &h_vkb_last_focus,
                                                     &b_is_top_bottom);
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }

                if(TRUE == b_is_top_bottom)
                {
                    e_view_type = LOCAL_TIME_VIEW_INIT;
                    i4_ret = _hide_time_local_setting_pwd_vkb();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return i4_ret;
                }

                i4_ret = a_vkb_current_is_ok_btn(h_vkb,
                                                 &b_is_ok_btn);
                if ((WDKR_OK == i4_ret)
                    &&(b_is_ok_btn))
                {
                    e_view_type = LOCAL_TIME_VIEW_INIT;

                    i4_ret = _time_local_setting_set_postal_code();
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = _hide_time_local_setting_pwd_vkb();
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
                break;

            case BTN_CURSOR_UP:
                i4_ret = a_vkb_current_is_top_row(h_vkb, &b_is_top_bottom);
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }
                if(TRUE == b_is_top_bottom)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    i4_ret = WDK_NO_ACTION;
                    menu_pm_repaint();
                }
                break;

            case BTN_CURSOR_DOWN:
                break;

            default :
                break;
        }
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_vkb_create
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_vkb_create(VOID)
{
    INT32       i4_ret;
    VKB_INIT_T           t_init_data;

    /* Create Virtual key board */
    t_init_data.h_parent            = h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_MENU;
    t_init_data.t_gui_rc.i4_left    = MENU_ITEM_V_INSET_L;
    t_init_data.t_gui_rc.i4_top     = 0;
    t_init_data.pf_data_change_fct  = _time_local_setting_pwd_vbk_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&h_vkb);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name:
 *      _time_local_setting_update_shadow_item_pos
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _time_local_setting_update_shadow_item_pos(VOID)
{
    INT32               i4_ret = 0;
    INT32               i4_item_idx = 0;
    GL_RECT_T           t_rect = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (e_view_type)
    {
        case LOCAL_TIME_VIEW_INIT:
        {
            i4_item_idx = 4;/*remove country item 4->3*/
            break;
        }
        case LOCAL_TIME_VIEW_LB_DLS_EX:
        {
            i4_item_idx = 3;
            break;
        }
        case LOCAL_TIME_VIEW_LB_TIME_ZONE_EX:
        {
            i4_item_idx = PAGE_TIME_ZONE_ITEM_NUM;
            break;
        }
        case LOCAL_TIME_VIEW_LB_TF_EX:
        {
            i4_item_idx = 2;
            break;
        }
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
        case LOCAL_TIME_VIEW_LB_CCC_EX:
        {
            i4_item_idx = 3;
            break;
        }
#endif
#if TIME_AUTOMATIC_LIST

        case LOCAL_TIME_VIEW_AT_EX:
        {
            i4_item_idx = 2;
            break;
        }
#endif
        default:
        {
            i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
            MENU_LOG_ON_FAIL(i4_ret);
            return MENUR_OK;
        }
    }

    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * i4_item_idx + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 _ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;
    WGL_IMG_INFO_T      t_img_info;
    WGL_INSET_T         t_inset;
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    ui4_page_id_pass = (UINT32)pv_create_data;
#endif
    T_HELP_TIP_REG t_help_tip_reg;

    c_memset(&t_help_tip_reg, 0, sizeof(t_help_tip_reg));

    ui4_page_id = _ui4_page_id;

    aui2_country_code_txt[COUNTRY_CODE_IDX_US] = MLM_MENU_KEY_COUNTRY_USA;
    aui2_country_code_txt[COUNTRY_CODE_IDX_CA] = MLM_MENU_KEY_COUNTRY_CA;
    aui2_country_code_txt[COUNTRY_CODE_IDX_MEX] = MLM_MENU_KEY_COUNTRY_MEX;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret=menu_get_homebar_handle(&h_homebar);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=menu_get_backbar_handle(&h_backbar);
    MENU_LOG_ON_FAIL(i4_ret);
#if TIME_AUTOMATIC
    /* AUTOMATIC ZONE */
#if TIME_AUTOMATIC_LIST
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX,
                              (MLM_MENU_KEY_TIME_ZONE_AT_NOCHECK - MLM_MENU_KEY_TIME_ZONE_AT_CHECK) + 1,
                              _lb_automatic_time_proc_fct,
                              &h_lb_autmomatic_time);
#endif
#if TIME_AUTOMATIC_CHECKBOX
    i4_ret = _automatic_time_checkbox_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_action_create(h_cnt_frm,
                                ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX,
                                _lb_automatic_time_proc_fct,
                                &h_lb_autmomatic_time);
    MENU_CHK_FAIL(i4_ret);
#endif
#endif
    /* TIME ZONE */
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX,
                              (MLM_MENU_KEY_BRCM_TIME_ZONE_NT  - MLM_MENU_KEY_BRCM_TIME_ZONE_HST) + 1,
                              _lb_timeZone_proc_fct,
                              &h_lb_time_zone);
    MENU_CHK_FAIL(i4_ret);

    /* LB DAY LIGHT SAVING */
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_TIME_LOCAL_SET_DLS_IDX,
                              (MLM_MENU_KEY_TIME_DLS_OFF- MLM_MENU_KEY_TIME_DLS_AUTO)+1,
                              _lb_dls_proc_fct,
                              &h_lb_daylight_saving);
    MENU_CHK_FAIL(i4_ret);

    /* LB time format */
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_TIME_LOCAL_SET_TIME_FORMAT_IDX,
                              (MLM_MENU_KEY_24_HOUR - MLM_MENU_KEY_12_HOUR + 1),
                              _lb_tf_proc_fct,
                              &h_lb_time_format);
    MENU_CHK_FAIL(i4_ret);

    /* eb postal code */
    i4_ret = menu_edit_create_ex(h_cnt_frm,
                              ATSC_TIME_LOCAL_SET_POSTAL_CODE_IDX,
                              _eb_postal_code_fct,
                              &h_eb_postal_code);
    MENU_CHK_FAIL(i4_ret);

    /* reset eb postal code inset */
    c_wgl_do_cmd(h_eb_postal_code,
                WGL_CMD_GL_GET_INSET,
                (VOID*)&t_inset,
                NULL);

    t_inset.i4_left += 135;

    i4_ret = c_wgl_do_cmd(h_eb_postal_code,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_menu_img_text_entry_small_1;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_menu_img_text_entry_small_1;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_menu_img_text_entry_small_1;
    i4_ret = c_wgl_do_cmd(h_eb_postal_code,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    /* LB Change Country Code */
#if COUNTRY_HIDE
    i4_ret = menu_list_create(h_cnt_frm,
                              ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX,
                              COUNTRY_CODE_IDX_LAST, //(MLM_MENU_KEY_COUNTRY_USA - MLM_MENU_KEY_COUNTRY_CA)+1,
                              _time_local_setting_page_lb_ccc_proc_fct,
                              &h_lb_chg_country_code);
    MENU_CHK_FAIL(i4_ret);
#endif

    if (0)
    {
        _time_local_setting_page_insert_lb_ccc();
    }

    /*
    i4_ret = menu_action_create(h_cnt_frm,
                                ATSC_TIME_LOCAL_SET_COUNTRY_IDX,
                                _time_local_setting_page_item_country_fct,
                                &h_action_item_country);
    MENU_CHK_FAIL(i4_ret);
    */

    i4_ret = _time_local_setting_vkb_create();
    MENU_CHK_FAIL(i4_ret);
#endif

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(h_eb_postal_code,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(MAX_POSTAL_CODE+3)),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

#if TIME_AUTOMATIC_LIST
    /*automatic time ex list create*/
    i4_ret=_creat_automatic_lb_time_ex();
    MENU_CHK_FAIL(i4_ret);
#endif
    /*time zone ex list create*/
    i4_ret=_creat_lb_time_zone_ex();
    MENU_CHK_FAIL(i4_ret);

    /*daylight saving ex list create*/
    i4_ret=_creat_lb_daylight_saving_ex();
    MENU_CHK_FAIL(i4_ret);

    /* time-format ex list create */
    i4_ret=_creat_lb_time_format_ex();
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = _time_local_setting_page_creat_lb_ccc_ex();
    MENU_CHK_FAIL(i4_ret);
#endif

    /* navigation */
    i4_ret = _set_nav();
    MENU_CHK_FAIL(i4_ret);

    /* timer */
    i4_ret = c_timer_create(&h_timer_ntp_update);
    MENU_CHK_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);
#if TIME_AUTOMATIC_LIST
    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time_ex,
                                      WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);
#endif
    i4_ret = c_wgl_set_visibility(h_lb_time_zone_ex,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving_ex,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_format_ex,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_chg_country_code_ex,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*
    i4_ret = c_wgl_set_visibility(h_action_item_country,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    */
#endif

    /* Register help tip back key processer */
    t_help_tip_reg.ui4_page_id = ui4_page_id;
    t_help_tip_reg.p_fct = _time_local_setting_page_help_tip_cb;

    menu_help_tip_key_reg(E_HELP_TIP_CB_PAGE_TIME_LOCAL_SETTING,  &t_help_tip_reg);

    apw2s_help_tip[_HELP_TIP_TYPE_HOMEBAR]     = MLM_MENU_KEY_EMPTY;
    apw2s_help_tip[_HELP_TIP_TYPE_BACKBAR]     = MLM_MENU_KEY_EMPTY;
    apw2s_help_tip[_HELP_TIP_TYPE_TIMEZONE]    = MLM_MENU_KEY_TAB_HELP_TIME_ZONE;
    apw2s_help_tip[_HELP_TIP_TYPE_DLS]         = MLM_MENU_KEY_TAB_HELP_DAYLIGHT_SAVING;
    apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_TAB_HELP_POSTAL_CODE;
    apw2s_help_tip[_HELP_TIP_TYPE_TF]          = MLM_MENU_KEY_TIME_FORMAT_HELP;
    apw2s_help_tip[_HELP_TIP_TYPE_TF_EX]       = MLM_MENU_KEY_TIME_FORMAT_HELP;
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    apw2s_help_tip[_HELP_TIP_TYPE_CHG_COUNTRY_CODE] = MLM_MENU_KEY_HELP_COUNTRY;
    apw2s_help_tip[_HELP_TIP_TYPE_CHG_COUNTRY_CODE_EX] = MLM_MENU_KEY_HELP_COUNTRY;
    apw2s_help_tip[_HELP_TIP_TYPE_COUNTRY]     = MLM_MENU_KEY_HELP_COUNTRY;
#endif
    apw2s_help_tip[_HELP_TIP_TYPE_TIMEZONE_EX] = MLM_MENU_KEY_TAB_HELP_TIME_ZONE;
    apw2s_help_tip[_HELP_TIP_TYPE_DLS_EX]      = MLM_MENU_KEY_TAB_HELP_DAYLIGHT_SAVING;
    apw2s_help_tip[_HELP_TIP_TYPE_AUTO_DLS_NOT_SUPPORT]      = MLM_MENU_KEY_AUTO_DST_NOT_SUPPORT;
#if TIME_AUTOMATIC
    apw2s_help_tip[_HELP_TIP_TYPE_AUTOMATIC_TIME]      = MLM_MENU_KEY_TIME_ZONE_AT_HELP;
#if TIME_AUTOMATIC_LIST
    apw2s_help_tip[_HELP_TIP_TYPE_AUTOMATIC_TIME_EX]   = MLM_MENU_KEY_TIME_ZONE_AT_HELP;
#endif
#endif
    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect = {0};
	UINT8               ui1_automatic;

    b_g_page_in_on = TRUE;
    _init_date_time_in_menu();

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    ACFG_COUNTRY_CODE_T t_country;
    a_cfg_custom_get_country_code(&t_country);

    if (t_country == ACFG_COUNTRY_CODE_MEX)
    {
        apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_TAB_HELP_POSTAL_CODE;
    }
    else
    {
        apw2s_help_tip[_HELP_TIP_TYPE_POSTAL_CODE] = MLM_MENU_KEY_SET_POSTAL_CODE;
    }

    i4_ret=  a_vkb_set_visibility(h_vkb,FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_show_homebar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_show_backbar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    /* lb mode */
    menu_list_set_idx(h_lb_daylight_saving, _get_dls_idx());

    /* lb mode */
    menu_list_set_idx(h_lb_time_zone, _get_time_zone_idx());
#if TIME_AUTOMATIC
    /* autmomatic_time */
#if TIME_AUTOMATIC_LIST
    menu_list_set_idx(h_lb_autmomatic_time, _get_automatic_time_idx());
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#if TIME_AUTOMATIC_CHECKBOX
    ui1_automatic = _get_automatic_time_idx();
    i4_ret = _automatic_time_checkbox_show(ui1_automatic);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
#endif
    UINT8  ui1_time_format;
    a_cfg_cust_get_time_format(&ui1_time_format);
    menu_list_set_idx(h_lb_time_format, ui1_time_format);
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
     a_cfg_custom_get_postal_code(w2s_postal_code);
    if (t_country != ACFG_COUNTRY_CODE_CA)
    {
        w2s_postal_code[5] = L'\0';
    }

    i4_ret = _eb_postal_code_set_text(h_eb_postal_code, w2s_postal_code);
    MENU_LOG_ON_FAIL(i4_ret);
    /* lb mode */
    i4_ret = menu_list_set_idx(h_lb_chg_country_code,
                               _time_local_setting_page_get_country_code_idx());
    MENU_LOG_ON_FAIL(i4_ret);
#else
    a_cfg_custom_get_postal_code(w2s_postal_code);
    _eb_postal_code_set_text(h_eb_postal_code, w2s_postal_code);
#endif

    i4_ret =_change_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_help_tip_keytip_show(FALSE);
    MENU_CHK_FAIL(i4_ret);

    t_rect.i4_left = g_t_list_tz_rect.i4_left;
    t_rect.i4_top= CONTENT_Y;
    t_rect.i4_right= g_t_list_tz_rect.i4_right;
    t_rect.i4_bottom= g_t_list_tz_rect.i4_bottom +  CONTENT_Y;
    menu_list_arrow_move(&t_rect, FALSE);

    i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_arrow_hide(FALSE);
    /* move tips */
    //menu_network_last_shadow_update_position(h_lb_time_format, FALSE);
    //_time_local_setting_update_shadow_item_pos();
    //menu_custom_page_time_local_setting_refresh_item(1);
    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32  i4_ret = 0;

    /* Menu is not in scanning status */
    t_g_menu_is_scanning = FALSE;

    /* Broadcast the message to enable the EAS */
    DBG_INFO(("<MENU>Broadcast the message to enable the EAS.\r\n"));
    a_amb_channel_scan_active(FALSE);

    //_change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX);
    _show_init_view(FALSE, ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX);

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_help_tip_keytip_show(TRUE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _ntp_timer_stop();
    MENU_CHK_FAIL(i4_ret);

    menu_list_arrow_hide(FALSE);

    b_g_page_in_on = FALSE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32   i4_ret = MENUR_OK;
    /* set callback function for homebar */
    menu_set_homebar_proc (_homebar_proc_fct) ;

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;
    //i4_ret = c_wgl_set_focus(h_lb_time_zone, WGL_NO_AUTO_REPAINT);
	i4_ret = c_wgl_set_focus(h_lb_autmomatic_time, WGL_NO_AUTO_REPAINT);

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    //_show_init_view(FALSE, 0);
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret =_change_lang();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
/*-----------------------------------------------------------------------------
 * Name:
 *      menu_custom_page_get_clear_memory_page_status
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 menu_custom_page_get_clear_memory_page_status(BOOL* pb_status)
{
    *pb_status = b_show_clear_memory_from_tls;
    return MENUR_OK;
}

INT32 menu_custom_page_get_tmp_country_code(UINT16* pui2_country_code)
{
    if (LOCAL_TIME_VIEW_LB_CCC_EX == e_view_type)
    {
        menu_list_get_idx(h_lb_chg_country_code_ex, pui2_country_code);
    }
    else
    {
        menu_list_get_idx(h_lb_chg_country_code, pui2_country_code);
    }

    return MENUR_OK;
}
#endif


extern INT32 menu_custom_page_time_local_setting_auto_dst_init(VOID)
{
    t_g_menu_custom_page_time_local_setting_auto_dst.pf_menu_page_create =    _on_page_create;
    t_g_menu_custom_page_time_local_setting_auto_dst.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_custom_page_time_local_setting_auto_dst.pf_menu_page_show=       _on_page_show;
    t_g_menu_custom_page_time_local_setting_auto_dst.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_custom_page_time_local_setting_auto_dst.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_custom_page_time_local_setting_auto_dst.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_custom_page_time_local_setting_auto_dst.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

extern BOOL _is_focus_on_eb(VOID)
{
    HANDLE_T    h_focus_widget;
    INT32       i4_ret;

    i4_ret = c_wgl_get_focus(&h_focus_widget);

    if (i4_ret == WGLR_OK)
    {
        if (h_focus_widget == h_eb_postal_code)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

static INT32 _ntp_timer_start(void)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = c_timer_start (h_timer_ntp_update,
                            NTP_CHK_TIME_DELAY,
                            X_TIMER_FLAG_ONCE,
                            _ntp_timer_nfy_fct,
                            NULL);

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ntp_timer_stop(void)
{
    INT32    i4_ret = MENUR_OK;

    i4_ret = c_timer_stop(h_timer_ntp_update);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static VOID _ntp_timer_nfy_fct(HANDLE_T h_timer, VOID* pv_tag)
{
    menu_async_invoke(_do_ntp_timer_nfy,
                      NULL,
                      0,
                      FALSE);
    return;
}

static INT32 _update_title_info(BOOL b_repaint)
{
    INT32       i4_ret = MENUR_OK;
    DTG_T       t_dtg = {0};
    DTG_T       t_dtg_temp= {0};
    CHAR        time[20] = {0};
    UTF16_T     w2s_time[20] = {0};
    UTF16_T     w2s_title[30] = {0};
    UTF16_T*    apw2s_month = NULL;
    UTF16_T*    apw2s_am_pm = NULL;
    //TIME_T      t_current_utc = 0;
    DT_COND_T   t_dt_cond = DT_FREE_RUNNING;
    BOOL        b_is_get_time = FALSE;
    UINT8       ui1_time_format = 0; //   0: 12 hour,  1:  24 hour
    BOOL        b_is_tv_src     = FALSE;

    if (e_view_type != LOCAL_TIME_VIEW_INIT)
    {
        return MENUR_OK;
    }

    c_dt_get_utc(NULL, &t_dt_cond);
    b_is_get_time = a_dst_get_local_time(&t_dtg);
    b_is_tv_src   = _time_crnt_source_is_tv();

    b_is_get_time = a_dst_get_local_time(&t_dtg_temp);// verification dtg data
    if(t_dtg_temp.ui1_hr != t_dtg.ui1_hr)
    {
        c_memcpy(&t_dtg,
                 &t_dtg_temp,
                 sizeof(DTG_T));
    }

    if (TRUE == b_is_get_time)
    {
        DBG_LOG_PRINT(("[time zone] {%s %s() %d}. b_is_tv_src = %d\n",__FILE__, __FUNCTION__, __LINE__,b_is_tv_src));
        rest_event_notify("tv_settings/system/time/automatic_time/tuner_time", b_is_tv_src, "");

        i4_ret = a_cfg_cust_get_time_format(&ui1_time_format);
        MENU_LOG_ON_FAIL(i4_ret);

        apw2s_month = MENU_TEXT((MLM_MENU_KEY_MONTH_JAN + t_dtg.ui1_mo -1));

        if (0 == ui1_time_format)     //   0: 12 hour,  1:  24 hour
        {
            if (t_dtg.ui1_hr > 12)
            {
                t_dtg.ui1_hr -= 12;
                apw2s_am_pm = MENU_TEXT(MLM_MENU_KEY_TIME_PM);
            }
            else
            {
                apw2s_am_pm = MENU_TEXT(MLM_MENU_KEY_TIME_AM);

                if (t_dtg.ui1_hr == 0)
                {
                    t_dtg.ui1_hr = t_dtg.ui1_hr + 12;
                    apw2s_am_pm = MENU_TEXT(MLM_MENU_KEY_TIME_AM);
                }
                else if (t_dtg.ui1_hr == 12)
                {
                    apw2s_am_pm = MENU_TEXT(MLM_MENU_KEY_TIME_PM);
                }
            }
        }

        if (t_dtg.ui1_min < 10)
        {
            if (t_dtg.ui1_hr < 10)
            {
                c_sprintf(time,
                          " %d, %d %d:0%d ",
                          t_dtg.ui1_day,
                          t_dtg.ui2_yr,
                          t_dtg.ui1_hr,
                          t_dtg.ui1_min);
            }
            else
            {
                c_sprintf(time,
                          " %d, %d %d:0%d ",
                          t_dtg.ui1_day,
                          t_dtg.ui2_yr,
                          t_dtg.ui1_hr,
                          t_dtg.ui1_min);
            }
        }
        else
        {
            if (t_dtg.ui1_hr < 10)
            {
                c_sprintf(time,
                          " %d, %d %d:%d ",
                          t_dtg.ui1_day,
                          t_dtg.ui2_yr,
                          t_dtg.ui1_hr,
                          t_dtg.ui1_min);
            }
            else
            {
                c_sprintf(time,
                          " %d, %d %d:%d ",
                          t_dtg.ui1_day,
                          t_dtg.ui2_yr,
                          t_dtg.ui1_hr,
                          t_dtg.ui1_min);
            }
        }

        i4_ret = c_uc_ps_to_w2s(time, w2s_time, c_strlen(time));
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strcat(w2s_title, apw2s_month);
        c_uc_w2s_strcat(w2s_title, w2s_time);

        if (0 == ui1_time_format)   //   0: 12 hour,  1:  24 hour
        {
            c_uc_w2s_strcat(w2s_title, apw2s_am_pm);
        }

		i4_ret = menu_main_set_title_text(w2s_title);
       	MENU_LOG_ON_FAIL(i4_ret);

    }
    else
    {
        i4_ret = menu_main_set_title(MLM_MENU_KEY_TIME_NOT_AVAILABLE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if(b_repaint)
    {
        i4_ret = menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);

        //update banner time after update the menu title
        a_banner_custom_update_banner_timer();
    }

    return MENUR_OK;
}

static VOID _do_ntp_timer_nfy(VOID*pv_data, SIZE_T z_data_size)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = _update_title_info(TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ntp_timer_start();
    MENU_LOG_ON_FAIL(i4_ret);

    return;
}

static INT32 _time_local_setting_page_help_tip_cb(
                        HANDLE_T            h_widget,
                        UINT32              ui4_msg,
                        VOID*               pv_param1,
                        VOID*               pv_param2,
                        BOOL*               pb_processed)
{
    UINT8 ui1FocusIdx = 0xFF;

    *pb_processed = TRUE;

    switch (e_view_type)
    {
        case LOCAL_TIME_VIEW_LB_TIME_ZONE_EX:
            ui1FocusIdx = ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX;
            break;
        case LOCAL_TIME_VIEW_LB_DLS_EX:
            ui1FocusIdx = ATSC_TIME_LOCAL_SET_DLS_IDX;
            break;
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
        case LOCAL_TIME_VIEW_LB_CCC_EX:
            ui1FocusIdx = ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX;
            break;
#endif
        case LOCAL_TIME_VIEW_EB_EX:
            ui1FocusIdx = ATSC_TIME_LOCAL_SET_POSTAL_CODE_IDX;
            break;
#if TIME_AUTOMATIC_LIST
        case LOCAL_TIME_VIEW_AT_EX:
            ui1FocusIdx = ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX;
            break;
#endif
        default:
            break;
    }

    if (ui1FocusIdx != 0xFF)
    {
        _change_view(LOCAL_TIME_VIEW_INIT, ui1FocusIdx);

        menu_pm_repaint();
    }
    else
    {
        menu_nav_back();
    }

    return MENUR_OK;
}

INT32 menu_custom_page_time_local_setting_refresh_item(WDK_STRING_STYLE_T e_string_style)
{
    INT32  i4_ret = MENUR_OK;
    UINT8  ui1_time_format  = 0;
    UINT8  ui1_automatic    = 0;
    //DBG_LOG_PRINT(("[zoom key +++ ] {%s %s() %d}. e_string_style = %d\n",__FILE__, __FUNCTION__, __LINE__,e_string_style));
    /* time_zone */
    menu_list_set_idx(h_lb_time_zone, _get_time_zone_idx());

    i4_ret=menu_list_adjust_rect(h_lb_time_zone);
    MENU_LOG_ON_FAIL(i4_ret);

    /* daylight_saving */
    menu_list_set_idx(h_lb_daylight_saving, _get_dls_idx());

    /* time_format */
    a_cfg_cust_get_time_format(&ui1_time_format);
    menu_list_set_idx(h_lb_time_format, ui1_time_format);

    ui1_automatic = _get_automatic_time_idx();
    DBG_LOG_PRINT(("[zoom key +++ ] {%s %s() %d}. ui1_automatic = %d\n",__FILE__, __FUNCTION__, __LINE__,ui1_automatic));

    /* autmomatic_time */
    menu_list_set_idx(h_lb_autmomatic_time, ui1_automatic);

    /*grayed_out*/
    _time_zone_dst_grayed_out_enable(ui1_automatic);

    /* navigation */
    i4_ret = _set_nav();
    MENU_CHK_FAIL(i4_ret);

    _automatic_time_geofencing_timezone_handle(ui1_automatic);

    i4_ret = _automatic_time_set_dst(ui1_automatic);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_repaint();

    /* Update time_zone after geofencing*/
    menu_list_set_idx(h_lb_time_zone, _get_time_zone_idx());

    i4_ret=menu_list_adjust_rect(h_lb_time_zone);
    MENU_LOG_ON_FAIL(i4_ret);

    /* title_info */
    _update_title_info(FALSE);

    /* tips */
    _time_local_setting_update_shadow_item_pos();

    return MENUR_OK;
}
VOID menu_time_local_setting_set_country(UINT16 ui2_idx)
{
    _time_local_setting_page_set_country_code_idx(ui2_idx);
}


static INT32 _lb_automatic_time_proc_fct(HANDLE_T    h_widget,
                                   UINT32      ui4_msg,
                                   VOID*       param1,
                                   VOID*       param2)
{
    INT32  i4_ret=0;
    UINT16 ui2_idx=0;

    ui2_idx = _get_automatic_time_idx();
    //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui4_msg = 0x%x\n\n",__FILE__, __FUNCTION__, __LINE__,ui4_msg));
#if TIME_AUTOMATIC_LIST
	if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        i4_ret=menu_list_set_idx(h_widget, ui2_idx);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret=menu_list_adjust_rect(h_lb_autmomatic_time);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
#if TIME_AUTOMATIC_LIST
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if (ui2_idx == AT_TIME_CHECK)
                {
                    ui2_idx = AT_TIME_UNCHECK;
                }
                else
                {
                    ui2_idx = AT_TIME_CHECK;
                }
                 //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui2_idx = %d\n\n",__FILE__, __FUNCTION__, __LINE__,ui2_idx));
                _set_automatic_time_idx(ui2_idx);

                menu_list_set_idx(h_widget, ui2_idx);

                i4_ret=menu_list_adjust_rect(h_lb_autmomatic_time);
                MENU_LOG_ON_FAIL(i4_ret);

                _automatic_time_geofencing_timezone_handle(ui2_idx);

                //_update_dls_by_tz(ui2_idx);
                i4_ret = _update_title_info(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);

                /*refresh item,the param is meanless*/
                i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
                MENU_LOG_ON_FAIL(i4_ret);

                c_wgl_repaint(h_widget, NULL, TRUE);
                return  WGLR_OK;
            }
#endif
#if TIME_AUTOMATIC_CHECKBOX
            case BTN_SELECT:
            {
                if (ui2_idx == AT_TIME_CHECK)
                {
                    ui2_idx = AT_TIME_UNCHECK;
                }
                else
                {
                    ui2_idx = AT_TIME_CHECK;
                }
                _set_automatic_time_idx(ui2_idx);
                /*show checkbox icon*/
                i4_ret = _automatic_time_checkbox_show(ui2_idx);
                MENU_LOG_ON_FAIL(i4_ret);
                //_update_dls_by_tz(ui2_idx);
                i4_ret = _update_title_info(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                /*refresh item,the param is meanless*/
                i4_ret = menu_custom_page_time_local_setting_refresh_item(1);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_pm_repaint();
                return  WGLR_OK;
            }
#endif
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    case WGL_MSG_KEY_UP:
        _tts_play(MLM_MENU_KEY_TIME_ZONE_AT, MLM_MENU_KEY_TIME_ZONE_AT_CHECK + ui2_idx, TRUE);
        break;
#endif
    default:
        break;
    }

    return _widgets_proc_fct(h_widget, ui4_msg, param1, param2);
}

#if TIME_AUTOMATIC_LIST
static INT32 _lb_automatic_proc_ex_fct(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32    i4_ret;
    UINT16   ui2_crnt_ht;
    //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui4_msg = 0x%x\n\n",__FILE__, __FUNCTION__, __LINE__,ui4_msg));
    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        if (0xffff != ui2_lst_last_hlt)
        {
            i4_ret=c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                             WGL_CMD_LB_HLT_ELEM,
                             WGL_PACK(0),
                             NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            ui2_lst_last_hlt = 0xffff;
        }
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        i4_ret = c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui2_crnt_ht = %d\n\n",__FILE__, __FUNCTION__, __LINE__,ui2_crnt_ht));
                _set_automatic_time_idx(ui2_crnt_ht);

            }
            case BTN_RETURN :
            {
                //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. \n\n",__FILE__, __FUNCTION__, __LINE__));
                i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;
            case BTN_CURSOR_UP:
            {
                //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui2_crnt_ht = %d\n\n",__FILE__, __FUNCTION__, __LINE__,ui2_crnt_ht));
                if(0 == ui2_crnt_ht)
                {
                    i4_ret=c_wgl_set_focus(h_backbar, WGL_NO_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    ui2_lst_last_hlt = ui2_crnt_ht;

                    i4_ret=menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
                break;
            case BTN_CURSOR_DOWN:
            {
                //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui2_crnt_ht = %d\n\n",__FILE__, __FUNCTION__, __LINE__,ui2_crnt_ht));
                if((1) == ui2_crnt_ht)
                {
                    ui2_lst_last_hlt = ui2_crnt_ht;

                    i4_ret = menu_pm_repaint();
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
            }
                break;

            default:
                break;
        }
    }
    else if (WGL_MSG_KEY_UP==ui4_msg)
    {
        //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui2_crnt_ht = %d\n\n",__FILE__, __FUNCTION__, __LINE__,ui2_crnt_ht));
#ifdef  APP_TTS_SUPPORT
        i4_ret = c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        _tts_play(MLM_MENU_KEY_TIME_ZONE_AT_CHECK + ui2_crnt_ht, 0, FALSE);
#endif
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _creat_automatic_lb_time_ex(VOID)
{

    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_cnt_frm,
                               &t_rect,
                               _lb_automatic_proc_ex_fct,
                               &t_lb_init,
                               NULL,
                               &h_lb_autmomatic_time_ex);
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (h_lb_autmomatic_time_ex,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
#endif

static VOID _set_automatic_time_idx(UINT16 ui2_idx)
{
    INT32 i4_ret = 0;
    i4_ret = a_cfg_cust_set_automatic_time(ui2_idx);
    //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. i4_ret = %d,ui2_idx = %d\n\n",__FILE__, __FUNCTION__, __LINE__,i4_ret,ui2_idx));
    return ;
}

VOID menu_set_automatic_time_idx(UINT16 ui2_idx)
{
    _set_automatic_time_idx(ui2_idx);
}

static UINT16 _get_automatic_time_idx(VOID)
{
    UINT8 ui1_tz = 0;
    INT32 i4_ret = 0;
    i4_ret = a_cfg_cust_get_automatic_time(&ui1_tz);
    //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. i4_ret = %d,ui1_tz = %d\n\n",__FILE__, __FUNCTION__, __LINE__,i4_ret,ui1_tz));
    return (UINT16)ui1_tz;
}

UINT16 menu_get_automatic_time_idx(VOID)
{
    return _get_automatic_time_idx();
}

#if TIME_AUTOMATIC_LIST
static INT32 _show_lb_automatic_time_ex_view(BOOL b_repaint)
{
    INT32    i4_ret;
    UINT8    ui2_crnt_ht;

    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_daylight_saving ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_eb_postal_code,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_zone_ex ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_time_format ,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    ui2_crnt_ht = _get_automatic_time_idx();
    //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. ui2_crnt_ht = %d\n\n",__FILE__, __FUNCTION__, __LINE__,ui2_crnt_ht));
    i4_ret = c_wgl_do_cmd(h_lb_autmomatic_time_ex,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(ui2_crnt_ht),     /* hlt elem */
                          NULL);    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_autmomatic_time_ex, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret= c_wgl_set_focus(h_lb_autmomatic_time_ex, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret= menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}
#endif

static INT32 _time_zone_dst_grayed_out_enable (BOOL b_hide_enable)
{
    INT32    i4_ret;
    if(b_hide_enable == TRUE)
    {
        i4_ret = c_wgl_enable(h_lb_time_zone,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = c_wgl_enable(h_lb_daylight_saving,TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

    }
    else
    {
        i4_ret = c_wgl_enable(h_lb_time_zone,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = c_wgl_enable(h_lb_daylight_saving,FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    //DBG_LOG_PRINT(("\n\n[ TIME +++ ] {%s %s() %d}. b_hide_enable = %d\n\n",__FILE__, __FUNCTION__, __LINE__,b_hide_enable));

    return i4_ret;
}

#if TIME_AUTOMATIC_CHECKBOX
static INT32 _automatic_time_checkbox_create(VOID)
{
	INT32	    i4_ret;
	WDK_ICON_WIDGET_PARAM_T         t_icon_param;

    t_icon_param.h_parent             = h_cnt_frm;
    t_icon_param.ui1_alpha            = 255;
    t_icon_param.b_visibility         = TRUE;
    t_icon_param.i4_x                 = CHECKBOX_ICN_X;
    t_icon_param.i4_y                 = CHECKBOX_ICN_Y;
    t_icon_param.i4_w                 = CHECKBOX_ICN_W;
    t_icon_param.i4_h                 = CHECKBOX_ICN_H;
    t_icon_param.ui4_style            = 0;
    t_icon_param.b_img_bk             = FALSE;
    t_icon_param.ui1_img_align_style  = WGL_AS_CENTER_CENTER;
    t_icon_param.t_img_param.h_disable= h_g_menu_common_checkbox_white_v2;
    t_icon_param.t_img_param.h_enable = h_g_menu_common_checkbox_white_v2;
    t_icon_param.t_img_param.h_highlight= h_g_menu_common_checkbox_white_v2;
    t_icon_param.pt_clr_bk            = NULL;
    t_icon_param.pf_wdgt_proc         = NULL;
    t_icon_param.ph_created_icon      = &checkbox_icon;
    i4_ret = a_wdk_create_icon_widget (t_icon_param);
    MENU_LOG_ON_FAIL(i4_ret);

    t_icon_param.h_parent             = h_cnt_frm;
    t_icon_param.ui1_alpha            = 255;
    t_icon_param.b_visibility         = TRUE;
    t_icon_param.i4_x                 = CHECKBOX_ICN_X;
    t_icon_param.i4_y                 = CHECKBOX_ICN_Y;
    t_icon_param.i4_w                 = CHECKBOX_ICN_W;
    t_icon_param.i4_h                 = CHECKBOX_ICN_H;
    t_icon_param.ui4_style            = 0;
    t_icon_param.b_img_bk             = FALSE;
    t_icon_param.ui1_img_align_style  = WGL_AS_CENTER_CENTER;
    t_icon_param.t_img_param.h_disable= h_g_menu_common_checkbox_white_checked_v2;
    t_icon_param.t_img_param.h_enable = h_g_menu_common_checkbox_white_checked_v2;
    t_icon_param.t_img_param.h_highlight= h_g_menu_common_checkbox_white_checked_v2;
    t_icon_param.pt_clr_bk            = NULL;
    t_icon_param.pf_wdgt_proc         = NULL;
    t_icon_param.ph_created_icon      = &checkbox_checked_icon;
    i4_ret = a_wdk_create_icon_widget (t_icon_param);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _automatic_time_checkbox_show(UINT8 ui1_automatic)
{
    INT32 i4_ret = 0;
    if(ui1_automatic == AT_TIME_UNCHECK)
    {
        i4_ret = c_wgl_set_visibility(checkbox_checked_icon,WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(checkbox_icon,WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(ui1_automatic == AT_TIME_CHECK)
    {
        i4_ret = c_wgl_set_visibility(checkbox_icon,WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(checkbox_checked_icon,WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return i4_ret;
}

static INT32 _automatic_time_checkbox_hide(VOID)
{
    INT32 i4_ret;
    i4_ret = c_wgl_set_visibility(checkbox_checked_icon,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(checkbox_icon,WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}
#endif
static BOOL _time_crnt_source_is_tv (VOID)
{
    TV_WIN_ID_T                e_tv_win_id = TV_WIN_ID_MAIN ;
    nav_get_focus_id (&e_tv_win_id) ;
    return ((INP_SRC_TYPE_TV == nav_get_src_type (e_tv_win_id)) ? TRUE : FALSE);
}

static INT32 _automatic_time_set_dst(UINT8 ui1_automatic)
{
   INT32  i4_ret = MENUR_OK;
   BOOL    b_is_connect = TRUE;

    if(ui1_automatic == AT_TIME_CHECK)
    {
         a_nw_is_network_connected (&b_is_connect);
         if(b_is_connect == TRUE)
         {
             c_memset(&at_geo_timezone,0,sizeof(REST_TIMZONE_T));
             i4_ret = _automatic_time_get_geofencing_timezone(&at_geo_timezone);
             if(MENUR_OK != i4_ret)
             {
                 DBG_LOG_PRINT(("[time zone] get geofencing_timezone fail!\n"));
                 return i4_ret;
             }
             if(at_geo_timezone.dstOffset == 1)
             {
                 _set_dls_idx(DST_ON);
             }
             else if(at_geo_timezone.dstOffset == 0)
             {
                 _set_dls_idx(DST_OFF);
             }
             else
             {
                DBG_LOG_PRINT(("dstOffset invalid!\n"));
             }

             MENU_LOG_ON_FAIL(menu_list_set_idx(h_lb_daylight_saving, DST_AUTO));
             MENU_LOG_ON_FAIL(menu_list_adjust_rect(h_lb_daylight_saving));
             MENU_LOG_ON_FAIL(menu_pm_repaint());
         }
         else
         {
             i4_ret = MENUR_FAIL;
         }

    }
    return i4_ret;
}
static INT32 _automatic_time_get_geofencing_timezone(REST_TIMZONE_T *p_at_geo_timezone)
{
    INT32       i4_ret = 0;
    i4_ret = rest_get_geofencing_timezone(p_at_geo_timezone);
    if(MENUR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("[time zone] rest_get_geofencing_timezone fail!\n"));
        return MENUR_FAIL;
    }
    return i4_ret;
}
static INT32 _automatic_time_set_geofencing_timezone(char* ps_timezone)
{
    UINT16 ui2_time_index = 0;
    INT32  i4_index       = 0;
    BOOL   b_timezone_idx_found = FALSE;
    for(i4_index = 0; i4_index < sizeof(cast_zone_maps)/sizeof(cast_zone_maps[0]); i4_index++)
    {
        if(c_strncmp(ps_timezone, cast_zone_maps[i4_index].ps_cast_zone, 32) == 0)
        {
            b_timezone_idx_found = TRUE;
            ui2_time_index = cast_zone_maps[i4_index].i4_idx;
            break;
        }
    }
    if(!b_timezone_idx_found)
    {
        DBG_LOG_PRINT(("[time zone]%s,%d,unsupport area:%s,please help check precise loaction!!!\r\n",__FUNCTION__, __LINE__,ps_timezone));
        return MENUR_FAIL;
    }
    else
    {
        for(i4_index  = 0; i4_index < sizeof(str_cast_zone_wo_dst)/sizeof(str_cast_zone_wo_dst[0]); i4_index ++)
        {
            if(c_strncmp(ps_timezone, str_cast_zone_wo_dst[i4_index], 32) == 0)
            {
                b_timezone_idx_found = TRUE;
                ui2_time_index = i4_index;
                break;
            }
        }
    }
    if(!b_timezone_idx_found)
    {
        DBG_LOG_PRINT(("[time zone]%s,%d,unsupport area:%s,please help check time zone!!!\r\n",__FUNCTION__, __LINE__,ps_timezone));
        return MENUR_FAIL;
    }
    DBG_LOG_PRINT(("[time zone]%s,%d, i4_time_index:%d ,is ok!!\r\n",__FUNCTION__, __LINE__,ui2_time_index));
    _set_time_zone_idx(ui2_time_index);
    return ui2_time_index;
}
static INT32 _automatic_time_geofencing_timezone_handle(UINT8 ui1_automatic)
{
    INT32  i4_ret = MENUR_OK;
    BOOL    b_is_connect = TRUE;

    c_memset(&at_geo_timezone,0,sizeof(REST_TIMZONE_T));

    a_nw_is_network_connected (&b_is_connect);
    DBG_LOG_PRINT(("[time zone] get network is connected  = %d!\n", b_is_connect));

    if(ui1_automatic == AT_TIME_CHECK
        && b_is_connect == TRUE)
    {
        i4_ret = _automatic_time_get_geofencing_timezone(&at_geo_timezone);
        if(MENUR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[time zone] get geofencing_timezone fail!\n"));
            return i4_ret;
        }

        i4_ret = _automatic_time_set_geofencing_timezone(at_geo_timezone.timeZone);
        if(MENUR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("[time zone] set geofencing_timezone fail!\n"));
            return i4_ret;
        }
        return i4_ret;
    }
    return MENUR_FAIL;
}

/*add for system.cpp --> automaic_time() to refresh menu page item*/
INT32 menu_page_set_automatic_time_to_refresh(VOID)
{
    INT32  i4_ret=0;
    UINT16 ui2_at_idx=0;

    ui2_at_idx = _get_automatic_time_idx();

    i4_ret = _automatic_time_geofencing_timezone_handle(ui2_at_idx);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _update_dls_by_tz(_get_time_zone_idx());
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_g_page_in_on)
    {
        i4_ret = _change_view(LOCAL_TIME_VIEW_INIT, ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}
#endif

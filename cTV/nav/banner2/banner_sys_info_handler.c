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
 * $RCSfile: sys_info_handler.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: min.li $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *---------------------------------------------------------------------------*/
#include "c_svctx.h"

#include "nav/sys_info/a_sys_info.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_bnr_item_def.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/a_cfg.h"
#include "nav/nav_common.h"

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_vizio/menu_page_bt_json_db.h"
#include "banner.h"
#include "nav/sys_info/a_sys_info.h"


#include "res/menu2/menu_mlm.h"
#include "res/nav/nav_img_rc.h"
#include "app_util/a_screen_mode.h"
#include "res/app_util/network/network_custom.h"
#include "res/nav/input_src/input_src_list_rc.h"
#include "nav/input_src/input_src_list.h"
#include "nav/updater/nav_updater.h"

#include "res/app_util/a_custom_log.h"
#include "rest/a_rest_api.h"

#include "app_util/a_network.h"
#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/c4tv_apron.h"
#endif
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "mmp/a_mmp.h"

#include "app_util/a_cec.h"
#include "nav/cec2/a_nav_cec.h"
#include "res/nav/nav_dbg.h"

#include "mi_common.h"
#include "mi_audio.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define CFG_ID_SCREEN_MODE      CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE)
#define BANNEER_INPUT_SRC_NAME_MAX  16
#define BANNEER_AUDIO_INPUT_LEN_MAX 10
static CHAR s_audio_format[BANNEER_AUDIO_INPUT_LEN_MAX+1] = {0};

extern WGL_HIMG_TPL_T at_img_signal_icon[];
extern WGL_HIMG_TPL_T at_img_signal_icon1[];

typedef struct _SIDEBAR_STATE_T
{
    BOOL b_showing;
    SCC_VID_HDR_TYPE_T hdr_type;
    SCC_VID_HDR_TYPE_T last_hdr_type;
} SIDEBAR_STATE_T;

//for not update if not change
typedef struct _BANNER_MM_UPDATE_INFO
{
    //ATMOS
    //DolbyAudio
    //DTS
    //MONO/STEREO/SAP
    BANNER_MM_UPDATE_INFO_AUD mm_audio_info;

    //Resolution
    char         mm_text_res[32];
} BANNER_MM_UPDATE_INFO;


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static banner_state_item_update_listener    pf_g_reporter = NULL ;

static INT16    i2_pre_scr_mode = 0;

static BOOL     b_is_replace_hdr = FALSE;

static BOOL     b_is_replace_dolby_vision = FALSE;
//static UINT16   ui2_dolby_vision_nfy_idx = 0;

static SIDEBAR_STATE_T t_sidebar_status;

static UINT16   ui2_hdr_icl_nfy_idx = 0;

static UINT16   ui2_mm_update_cfg_nfy_idx = 0;

static BANNER_MM_UPDATE_INFO t_banner_mm_update_status = {0};

static BOOL     b_banner_mm_info_updated = TRUE;

static BANNER_MM_UPDATE_INFO t_banner_stream_update_status = {0};

static BOOL b_connected_headphones_old_status = FALSE;

/*show dts audio type for banner*/
#define DTS_INFO    L"DTS-HD"

static UINT8    banner_u1_vrr_en = 0;

/*-----------------------------------------------------------------------------
 * customization declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

extern INT32 _json_bt_db_get_mac( t_bt_item_type type, const char *name, const char *mac);

extern INT32 banner_update_scr_mode(VOID);
extern BOOL _crnt_source_is_tv (VOID);
extern BOOL _crnt_svl_is_empty (VOID);
extern INT32 c_scc_aud_get_iec_type( HANDLE_T                   h_aud,
                              SCC_AUD_IEC_TYPE_T*        pe_iec_type );
INT32 banner_get_crnt_isl(ISL_REC_T* pt_isl_rec);

static INT32 _banner_sys_w2s_ch_r(
            UTF16_T *pt_src_w2s,
            UTF16_T *pt_dst_w2s,
            SIZE_T t_dst_size,
            CHAR a,
            CHAR *b
            );
static INT32 _banner_sys_info_hdr_nfy_func(UINT16 ui2_nfy_id,
                                            VOID* pv_tag,
                                            ICL_NOTIFY_DATA_T* pt_notify_data);
static VOID _nav_banner_mm_update_cfg_change_cb(
    UINT16                        ui2_nfy_id,
    VOID*                         pv_tag,
    UINT16                        ui2_id);

VOID banner_sys_info_reset_mm_update_info(BOOL b_update);
static void _banner_sys_info_update_dts(BANNER_AUD_UPDATE_TYPE en_banner_type, UTF16_T* w2s_dst);

extern INT32 ver_info_get_audio_type_in(CHAR* s_name);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Name
 *      _register_items
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _register_items (VOID)
{
    BANNER_ITEM_INFO_T*                 pt_item_info = NULL ;
    UINT8                               ui1_item_id  = 0 ;
    UINT8                               ui1_item_num = 0 ;
    NAV_BNR_STATE_ITEM_WIDGET_INFO_T    at_infos[255];

    for(ui1_item_id = 0 ;
        ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY && ui1_item_id < 255 ;
        ui1_item_id ++ )
    {
        /* find out the specified item info */
        pt_item_info = banner_get_item_info (ui1_item_id) ;

        if (!pt_item_info)
        {
            continue ;
        }

        /* it is unallowed if there is no corresponding widget for a item */
        NAV_ASSERT (pt_item_info->ph_handle && *pt_item_info->ph_handle) ;
        BANNER_CHK_FAIL ( (pt_item_info->ph_handle && *pt_item_info->ph_handle) ? NAVR_OK : NAVR_FAIL) ;

        at_infos[ui1_item_num].ui1_item_idx = pt_item_info->ui1_item_id ;
        at_infos[ui1_item_num].h_widget = *pt_item_info->ph_handle ;
        at_infos[ui1_item_num].ui1_type = 0;
        ui1_item_num ++ ;
    }

    BANNER_CHK_FAIL (nav_bnr_state_set_item_widgets(ui1_item_num, at_infos, FALSE));

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _notify_to_banner_item_changed
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _notify_to_banner_item_changed (
    UINT8                       ui1_item_id,
    UTF16_T*                    pw2s_text,
    HANDLE_T                    h_icon
    )
{
    BANNER_UPDATE_NFY_T         t_nfy_data ;

    if (pf_g_reporter)
    {
        c_memset (&t_nfy_data, 0, sizeof (BANNER_UPDATE_NFY_T)) ;

        t_nfy_data.e_nfy_type = BANNER_NFY_TYPE_UPDATE_ITEM ;
        t_nfy_data.u_nfy_data.t_up_item.ui1_item_id = ui1_item_id ;
        t_nfy_data.u_nfy_data.t_up_item.pw2s_text = pw2s_text ;
        t_nfy_data.u_nfy_data.t_up_item.h_icon  = h_icon ;
        BANNER_CHK_FAIL (pf_g_reporter (t_nfy_data)) ;
    }

    if (BANNER_ITM_AUDIO_FARMAT == ui1_item_id)
    {
        c_uc_w2s_to_ps(pw2s_text, s_audio_format, BANNEER_AUDIO_INPUT_LEN_MAX);
    }

    return NAVR_OK ;
}

INT32 ver_info_get_audio_type_in(CHAR* s_name)
{
    if(c_strlen(s_audio_format)!=0)
    {
        c_strncpy(s_name,s_audio_format,BANNEER_AUDIO_INPUT_LEN_MAX);
        return NAVR_OK ;
    }
    else
    {
        c_strcpy(s_name,"");
        return NAVR_OK ;;
    }
}


/*-----------------------------------------------------------------------------
 * Name
 *      _banner_si_hldr_24HR_to_12HR
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_si_hldr_24HR_to_12HR(
                    UINT8*                      pui1_hour,
                    BOOL*                       pb_is_am
                    )
{
    if (*pui1_hour == BANNER_CUSTOM_NOON_HOUR)
    {
        *pui1_hour = BANNER_CUSTOM_NOON_DISPLAY_HOUR;
        *pb_is_am  = FALSE ;
    }
    else if (
        *pui1_hour > BANNER_CUSTOM_NOON_HOUR)
    {
        *pui1_hour = (UINT8)((*pui1_hour) - BANNER_CUSTOM_NOON_HOUR);
        *pb_is_am  = FALSE ;
    }
    else if (
        *pui1_hour == BANNER_CUSTOM_MIDNIGHT_HOUR)
    {
        *pui1_hour = BANNER_CUSTOM_MIDNIGHT_DISPLAY_HOUR ;
        *pb_is_am  = TRUE ;
    }
    else
    {
        *pb_is_am  = TRUE ;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_si_hldr_get_event_display_time
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_si_hldr_get_event_display_time(
    DTG_T*                      pt_start_dtg,
    DTG_T*                      pt_end_dtg,
    TIME_T*                     pt_time_duration,
    CHAR*                       ps_display_time
    )
{
    UINT8                       ui1_start_hour    = pt_start_dtg->ui1_hr;
    UINT8                       ui1_end_hour      = pt_end_dtg->ui1_hr;
    BOOL                        b_start_is_am     = TRUE;
    BOOL                        b_end_is_am       = TRUE;
    UINT32                      ui4_duration_hour = 0;
    UINT32                      ui4_duration_min  = 0;
    TIME_T                      t_duration        = NULL_TIME;

    if (pt_start_dtg->ui2_yr == 0)
    {
        return;
    }

    if (!ps_display_time)
    {
        BANNER_LOG_ON_FAIL (NAVR_INV_ARG) ;
        return ;
    }

    _banner_si_hldr_24HR_to_12HR(&ui1_start_hour, &b_start_is_am);
    _banner_si_hldr_24HR_to_12HR(&ui1_end_hour,   &b_end_is_am);

    t_duration        = (*pt_time_duration) / 60;
    ui4_duration_min  = (UINT32)(t_duration % 60);
    ui4_duration_hour = (UINT32)(t_duration / 60);

    if (ui4_duration_hour < 24 || ui4_duration_hour > 999)
    {
        c_sprintf(ps_display_time,
                BANNER_CUSTOM_EVENT_START_END_TIME_FORMAT,
                ui1_start_hour,
                pt_start_dtg->ui1_min,
                (b_start_is_am == TRUE ? BANNER_CUSTOM_ANTE_MERIDIEM : BANNER_CUSTOM_POST_MERIDIEM),
                ui1_end_hour,
                pt_end_dtg->ui1_min,
                (b_end_is_am == TRUE ? BANNER_CUSTOM_ANTE_MERIDIEM : BANNER_CUSTOM_POST_MERIDIEM)
                );
    }
    else
    {
        /* if duration >= 24, use the BANNER_CUSTOM_EVENT_START_END_EX_TIME_FORMAT
         * to display the duration.
         */
        c_sprintf(ps_display_time,
                BANNER_CUSTOM_EVENT_START_END_EX_TIME_FORMAT,
                ui1_start_hour,
                pt_start_dtg->ui1_min,
                (b_start_is_am == TRUE ? BANNER_CUSTOM_ANTE_MERIDIEM : BANNER_CUSTOM_POST_MERIDIEM),
                ui1_end_hour,
                pt_end_dtg->ui1_min,
                (b_end_is_am == TRUE ? BANNER_CUSTOM_ANTE_MERIDIEM : BANNER_CUSTOM_POST_MERIDIEM),
                ui4_duration_hour,
                ui4_duration_min);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_si_hldr_is_focused_win_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _banner_si_hldr_is_focused_win_id(
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    TV_WIN_ID_T                 e_focus_win_id = TV_WIN_ID_LAST_VALID_ENTRY ;

    BANNER_LOG_ON_FAIL (nav_get_focus_id (&e_focus_win_id)) ;

    return (e_tv_win_id == e_focus_win_id) ? TRUE : FALSE ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_is_need_reconnect_ssid
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _banner_is_need_reconnect_ssid(VOID)
{
    NET_802_11_ASSOCIATE_T  t_Associate;
    INT32                   i4_ret = NAVR_OK;
    CHAR                    s_key[65] = {0};

    t_Associate.t_Key.pui1_PassPhrase = s_key;

    i4_ret = nw_custom_get_associate(&t_Associate);
    if (i4_ret != NWR_OK)
    {
        return FALSE;
    }

    t_Associate.e_AssocCase = IEEE_802_11_PWR_ON_ASSOC;

    DBG_LOG_PRINT(("t_Associate.t_Ssid.ui4_SsidLen=%d\n",
               t_Associate.t_Ssid.ui4_SsidLen));

    /* connect only if ssid is provided */
    if (t_Associate.t_Ssid.ui4_SsidLen == 0 ||
        t_Associate.t_Ssid.ui1_aSsid[0] == 0)
    {
        return FALSE;
    }

    return TRUE;
}

extern INT32 a_isl_get_vtrl_input_display_name(ISL_REC_T*   pt_isl_rec,
                                            CHAR*         s_name);

static INT32 _banner_handle_resolution_info(SI_SET_INFO_T*     pt_si_info)
{
    SI_TUNING_INFO_T*      pt_tuning_info = &pt_si_info->u.t_tuning_info ;

    if(pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_VIDEO_RES)
    {
        UTF16_T        w2s_text[64]  = {0} ;
        UTF16_T*       pw2s_text     = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL);
        CHAR           sz_tmp[64]    = {0} ;

#ifdef APP_HDR_SUPPORT
        ISL_REC_T      t_isl_rec     = {0};
        HANDLE_T       h_icon        = NULL_HANDLE;
        banner_get_crnt_isl(&t_isl_rec);
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("e_video_type: 0x%x source name =>\"%s\" ui1_id = 0x%x net tv state:%d\r\n",
                    t_isl_rec.t_avc_info.e_video_type,
                    t_isl_rec.s_src_name,
                    t_isl_rec.ui1_id,
                    a_tv_net_get_tv_svc_status()));
        #if 1
        //BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_VISION, BANNER_TEXT(""), NULL_HANDLE)) ;

        if ((t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI) ||
            (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_MMP) ||
            (t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST) ||
            (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED))
        {
#if 0
            CHAR     s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
            HANDLE_T h_scc_comp = NULL_HANDLE;
            INT32    i4_ret;

            /* Get SCC handle by display name. */
            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            BANNER_CHK_FAIL(i4_ret);
            h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                         h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

            SCC_VID_HDR_TYPE_T t_hdr_type;
            i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
            BANNER_LOG_ON_FAIL(i4_ret);
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("cast orig timing= %d \r\n",(UINT32)t_hdr_type)) ;
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("t_hdr_type: %d\r\n", t_hdr_type));

            SCC_DOVI_INFO_T t_dolby_vision;
            c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));
            i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
            BANNER_LOG_ON_FAIL(i4_ret);
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("t_dolby_vision.ui1_is_doviHDR: %d\r\n", t_dolby_vision.ui1_is_doviHDR));
#endif
            SCC_VID_HDR_TYPE_T t_hdr_type = a_cfg_get_hdr_type();
            //if (t_dolby_vision.ui1_is_doviHDR != 0 && t_hdr_type == SCC_VID_PQ_DOVI)
            if (t_hdr_type == SCC_VID_PQ_DOVI)
            {
                b_is_replace_dolby_vision = TRUE;
                //banner_show_siderbar(BANNER_HDR_DOLBY_VISION);
                h_icon = h_g_banner_slider_icon_dolby_vision;
                pw2s_text = L"";
                t_sidebar_status.hdr_type = SCC_VID_PQ_DOVI;
            }
            else if (t_hdr_type == SCC_VID_PQ_HDR10PLUS)
            {
                b_is_replace_hdr = TRUE;
                banner_show_siderbar_logo(BANNER_LOGO_HDR_HDR10_PLUS);
                pw2s_text = L"HDR10+";
                t_sidebar_status.hdr_type = SCC_VID_PQ_HDR10PLUS;
            }
            else if (t_hdr_type == SCC_VID_PQ_HDR10)
            {
                b_is_replace_hdr = TRUE;
                banner_show_siderbar_logo(BANNER_LOGO_HDR_HDR10);
                //pw2s_text = L"HDR10";
                h_icon = h_g_banner_slider_icon_hdr10;
                pw2s_text = L"";
                t_sidebar_status.hdr_type = BANNER_LOGO_HDR_HDR10;
            }
            else if (t_hdr_type == SCC_VID_PQ_HLG)
            {
                b_is_replace_hdr = TRUE;
                banner_show_siderbar_logo(BANNER_LOGO_HDR_HLG);
                //pw2s_text = L"HLG";
                h_icon = h_g_banner_slider_icon_hlg;
                pw2s_text = L"";
                t_sidebar_status.hdr_type = SCC_VID_PQ_HLG;
            }
            else
            {
                b_is_replace_hdr = FALSE;
                b_is_replace_dolby_vision = FALSE;
                //sdr show nothing
                banner_hide_sidebar();
                t_sidebar_status.hdr_type = BANNER_LOGO_HDR_SDR;
            }

            //if(t_sidebar_status.last_hdr_type != t_sidebar_status.hdr_type)
            {
                t_sidebar_status.last_hdr_type = t_sidebar_status.hdr_type;

                BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_DOLBY_VISION ,NULL,h_icon,!UP_TO_VIEW_AT_ONCE)) ;
                banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_ASPECT);
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_ASPECT, pw2s_text, NULL_HANDLE)) ;
            }

        }
        #endif
#endif

        //check freesync logo
        if(a_cfg_cust_is_FreeSync_logo_support())
        {
            VSH_SRC_RESOLUTION_INFO_T   t_resolution = {0};
            TV_WIN_ID_T                 e_tv_win_id = TV_WIN_ID_MAIN ;
            HANDLE_T                    h_svctx;
            INT32                       i4_ret = 0;
            //freesync contained in res info
            i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
            if(NAVR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("%s,%d,nav_get_svctx_handle(win=%d) failed, i4_ret=%d.\r\n",
                                __FUNCTION__,__LINE__, e_tv_win_id, i4_ret));
            }
            c_memset(&t_resolution, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
            i4_ret = c_svctx_get_video_src_resolution(h_svctx,&t_resolution);
            BANNER_CHK_FAIL(i4_ret);

            //u1_vrr_en 0:Non 1:VRR 2:Freesync 3:G-Sync
            DBG_LOG_PRINT(("[banner freesync] %s,%d,t_resolution.u1_vrr_en:%d,banner_u1_vrr_en:%d\r\n",
                                __FUNCTION__,__LINE__, t_resolution.u1_vrr_en, banner_u1_vrr_en));

            //if((t_resolution.u1_vrr_en == 2) && (banner_u1_vrr_en != t_resolution.u1_vrr_en))
            if(t_resolution.u1_vrr_en == 2)
            {
                //show freesync logo if change to freesync
                banner_show_siderbar_logo(BANNER_LOGO_FREESYNC);
            }
            else if(t_resolution.u1_vrr_en != 2)
            {
                banner_hide_siderbar_logo(BANNER_LOGO_FREESYNC);
            }

            banner_u1_vrr_en = t_resolution.u1_vrr_en;
        }

        pw2s_text = L"";

        if (VSH_SRC_TIMING_GRAPHIC != pt_tuning_info->t_video_res.e_timing_type)
        {
            /* reset STATE_RETRIEVE first */
            BANNER_CHK_FAIL (banner_unlock_state (BANNER_STATE_RETRIEVE)) ;

            /* prepare the content for VIDEO TIMING source */
            BANNER_LOG_ON_FAIL (nav_get_video_format_string (
                                &pt_tuning_info->t_video_res,
                                VID_RESLOUTION_FMT,
                                sz_tmp)) ;
        }

        //Cedric update resolution
        switch (pt_tuning_info->t_video_res.e_timing_type)
        {
            case VSH_SRC_TIMING_VIDEO:
            {
				DBG_LOG_PRINT(("banner timing_type is VSH_SRC_TIMING_VIDEO \n"));
                UINT32                      ui4_video_height = 0;
                BOOL                        b_is_timing_valid = FALSE;
                //CHAR                        s_disp_name[33] = {0};
                //UINT8                       ui1_input_id = 0;
                ISL_REC_T                   t_isl_rec;
                VSH_SRC_RESOLUTION_INFO_T   t_resolution = {0};
                TV_WIN_ID_T                 e_tv_win_id = TV_WIN_ID_MAIN ;
                HANDLE_T                    h_svctx;
                INT32                       i4_ret = 0;
                BOOL                        b_is_cast = FALSE;
                CHAR                        s_vtrl_name[24] = {0};
                UTF16_T                     w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

                /* check if it is a valid timing */
                if(pt_tuning_info->t_video_res.ui4_width != 0  &&
                   pt_tuning_info->t_video_res.ui4_height != 0 &&
                   pt_tuning_info->t_video_res.ui4_frame_rate != 0)
                {
                    b_is_timing_valid = TRUE;
                }

                //a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
                //a_cfg_get_input_src(s_disp_name, &ui1_input_id);
                //a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
                banner_get_crnt_isl(&t_isl_rec);
                c_memset(s_vtrl_name,0,sizeof(s_vtrl_name));
                //a_isl_get_vtrl_input_display_name(&t_isl_rec,s_vtrl_name);
                //DBG_LOG_PRINT(("[banner res source type] source type:%s.\n",s_vtrl_name));

                a_isl_get_display_name_ex(&t_isl_rec, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);
                c_uc_w2s_to_ps(w2s_alias,s_vtrl_name,sizeof(s_vtrl_name));
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner res source type] source type:%s.\n",s_vtrl_name));

                if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
                {
                    b_is_cast = TRUE;
                }

                //to get t_resolution value
                i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
                if(NAVR_OK != i4_ret)
                {
                    DBG_LOG_PRINT(("%s,%d,nav_get_svctx_handle(win=%d) failed, i4_ret=%d.\r\n",
                                    __FUNCTION__,__LINE__, e_tv_win_id, i4_ret));
                }
                c_memset(&t_resolution, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
                i4_ret = c_svctx_get_video_src_resolution(h_svctx,&t_resolution);
                BANNER_CHK_FAIL(i4_ret);

                //next flow only for playing airplay app video
                //just show 480i,480p,720p,1080i,1080p,2060p in apk cast,not" %d X %d "
                if(!c_strcmp(s_vtrl_name,"AirPlay"))
                {
                    c_svctx_get_well_defined_video_heigh(pt_tuning_info->t_video_res.ui2_orig_height, &ui4_video_height);

                    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner res change] airplay timing= (%d,%d) -> (%d,%d) (fixed %d)\r\n",
                        t_resolution.ui2_orig_width, t_resolution.ui2_orig_height,t_resolution.ui4_width,t_resolution.ui4_height,ui4_video_height));
                    //just show 480i,480p,720p,1080i,1080p,2060p in apk cast,not" %d X %d "
                    if (ui4_video_height != 0)
                    {
                        //2160p
                        if(ui4_video_height > VIDEO_HEIGHT_1440)
                        {
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_2160P);
                        }
						 //1440p
                        else if(ui4_video_height > VIDEO_HEIGHT_1080)
                        {
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_1440P);
                        }
                        //1080i,1080p
                        else if(ui4_video_height > VIDEO_HEIGHT_720)
                        {
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_1080P : MLM_NAV_KEY_NAV_RESOLUTION_1080I);
                        }
                        //720p
                        else if(ui4_video_height > VIDEO_HEIGHT_480)
                        {
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_720P : MLM_NAV_KEY_EMPTY);
                        }
                        //480i,480p
                        else
                        {
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_480P : MLM_NAV_KEY_NAV_RESOLUTION_480I);
                        }

                    }
                }
                //for sch cast app
                //show 480i,480p,720p,1080i,1080p,2060p,otherwise show " %d X %d "
                else
                {
                    c_svctx_get_well_defined_video_heigh(pt_tuning_info->t_video_res.ui2_orig_height, &ui4_video_height);
                    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner res change] app timing= (%d,%d) -> (%d,%d),ui4_video_height=%d\r\n",
                                pt_tuning_info->t_video_res.ui2_orig_width,pt_tuning_info->t_video_res.ui2_orig_height,
                                pt_tuning_info->t_video_res.ui4_width,pt_tuning_info->t_video_res.ui4_height,ui4_video_height));

                    switch(ui4_video_height)
                    {
                        case VIDEO_HEIGHT_480:
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_480P : MLM_NAV_KEY_NAV_RESOLUTION_480I);
                          break;
                        case VIDEO_HEIGHT_720:
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_720P : MLM_NAV_KEY_EMPTY);
                          break;
                        case VIDEO_HEIGHT_1080:
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_1080P : MLM_NAV_KEY_NAV_RESOLUTION_1080I);
                          break;
						 case VIDEO_HEIGHT_1440:
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_1440P);
                          break;
                        case VIDEO_HEIGHT_2160:
                          pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_2160P);
                          break;
                        default:

                            if(b_is_cast || b_is_timing_valid)
                            {
                                UINT32 ui4_height = b_is_cast ?  t_resolution.ui2_orig_height : pt_tuning_info->t_video_res.ui4_height;
                                if(ui4_height == VIDEO_HEIGHT_2160)
                                {
                                    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_2160P);
                                }
								else if(ui4_height == VIDEO_HEIGHT_1440)
                                {
                                    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_1440P);
                                }
                                else if(ui4_height == VIDEO_HEIGHT_1080)
                                {
                                    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_1080P : MLM_NAV_KEY_NAV_RESOLUTION_1080I);
                                }
                                else if(ui4_height == VIDEO_HEIGHT_720)
                                {
                                    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_720P : MLM_NAV_KEY_EMPTY);
                                }
                                else if(ui4_height == VIDEO_HEIGHT_480)
                                {
                                    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), pt_tuning_info->t_video_res.b_is_progressive ? MLM_NAV_KEY_NAV_RESOLUTION_480P : MLM_NAV_KEY_NAV_RESOLUTION_480I);
                                }
                                else
                                {
                                    /* update video infomation to view */
                                    if(b_is_cast)
                                    {
                                        if(t_resolution.ui2_orig_height == 0 || t_resolution.ui2_orig_width == 0)
                                        {
                                            pw2s_text = L"";
                                            break;
                                        }
                                    }
									DBG_LOG_PRINT(("jinlei banner enter ...x... type \n"));
                                    c_sprintf(sz_tmp, "%d X %d",
                                    b_is_cast ?  t_resolution.ui2_orig_width  : pt_tuning_info->t_video_res.ui4_width,
                                    b_is_cast ?  t_resolution.ui2_orig_height : pt_tuning_info->t_video_res.ui4_height) ;

                                    NAV_ASSERT (c_strlen(sz_tmp) < sizeof(sz_tmp) - 1) ;
                                    BANNER_CHK_FAIL ((c_strlen(sz_tmp) < sizeof(sz_tmp) - 1) ? NAVR_OK : NAVR_FAIL) ;
                                    c_uc_ps_to_w2s (sz_tmp, w2s_text,sizeof (w2s_text)/sizeof(w2s_text[0]) - 1) ;
                                    pw2s_text = w2s_text;
                                }
                            }
                            else
                            {
                                pw2s_text = L"";
                            }
                             break;
                    }
                }
            } break;
            case VSH_SRC_TIMING_GRAPHIC:
				DBG_LOG_PRINT(("banner timing_type is VSH_SRC_TIMING_GRAPHIC \n"));
                /* update video infomation to view */
                c_sprintf (sz_tmp, "%d X %d", pt_tuning_info->t_video_res.ui4_width,pt_tuning_info->t_video_res.ui4_height) ;
                NAV_ASSERT (c_strlen(sz_tmp) < sizeof(sz_tmp) - 1) ;
                BANNER_CHK_FAIL ((c_strlen(sz_tmp) < sizeof(sz_tmp) - 1) ? NAVR_OK : NAVR_FAIL) ;
                c_uc_ps_to_w2s (sz_tmp, w2s_text,sizeof (w2s_text)/sizeof(w2s_text[0]) - 1) ;
                pw2s_text = w2s_text;
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" pc timing= %d,height= %d \r\n",
                               pt_tuning_info->t_video_res.ui4_width,
                               pt_tuning_info->t_video_res.ui4_height));
                break;
            default:
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                    BANNER_ITM_RESOLUTION_TXT, BANNER_TEXT(""),
                                    NULL_HANDLE)) ;
                break;
        }

        char tmp_timing[128] = {0};
        c_uc_w2s_to_ps(pw2s_text,tmp_timing,sizeof(tmp_timing));
        DBG_LOG_PRINT(("[ banner res change] %d timing:%s\n",__LINE__,tmp_timing));

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_RESOLUTION_TXT,
                                                        pw2s_text,
                                                        NULL_HANDLE));
    }
    return NAVR_OK;
}

static INT32 _banner_handle_input_src_info(SI_TUNING_INFO_T*   pt_tuning_info)
{
    TV_WIN_ID_T  e_tv_win_id;
    SVL_REC_T    t_svl_rec               = {0};
    UTF16_T*     pw2s_text               = NULL;
    HANDLE_T     h_icon                  = NULL_HANDLE ;
    UTF16_T      wz_input_src_name [128] = {0};
    BOOL         b_svl_empty             = _crnt_svl_is_empty();
    ISL_REC_T    t_isl_rec               = {0};
    CEC_DEV_INFO_T  t_dev_info           = {0};
    INT32        i4_ret_cec              = CECR_FAIL;
    UINT8        ui1_cec_func            = APP_CFG_CEC_OFF;
    UTF16_T      w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};


    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec (e_tv_win_id, &t_isl_rec);

    if (pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_CHANNEL_INFO && t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        CHAR  ps_tmp_ch_no_name[128] = {'\0'};
        CHAR  sz_channel_id[6]       = {0};
        CHAR  sz_channel_name[64]    = {0};
        UINT8 ui1_brdcst_src;
        UINT32  ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
        DBG_LOG_PRINT(("[banner ch name] %s:%d ui4_channel_id:0x%x\n",__FUNCTION__,__LINE__,ui4_channel_id));

        BANNER_CHK_FAIL (nav_get_svl_rec (e_tv_win_id, &t_svl_rec)) ;
        if(FALSE == b_svl_empty)
        {
            nav_set_ch_num_and_name (&t_svl_rec, sz_channel_id, sz_channel_name) ;
        }

        //if change HDMI to TV,this name scrl timer not be stoped
        banner_view_set_name_update_flag(FALSE);

        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" ch num= %s,ch name= \"%s\" line:%d\n", sz_channel_id, sz_channel_name,__LINE__)) ;

        //DBG_LOG_PRINT((" ch num= %s,ch name= \"%s\" \n", sz_channel_id, sz_channel_name)) ;
        a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_brdcst_src);

        switch (ui1_brdcst_src)
        {
            case APP_CFG_BS_SRC_AIR:
                h_icon = h_g_nav_banner_new_input_new_satellite_pic ;
                break ;
            case APP_CFG_BS_SRC_CABLE:
                h_icon = h_g_nav_banner_new_input_tuner_img;
                break ;
            default :
                h_icon = h_g_nav_banner_new_input_new_satellite_pic;
                break ;
        }
        c_sprintf(ps_tmp_ch_no_name, "%s  %s", sz_channel_id, sz_channel_name);
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("ch name => \"%s\"\n",ps_tmp_ch_no_name));
        DBG_LOG_PRINT(("[banner ch name] \"%s\"\n",ps_tmp_ch_no_name));
        c_uc_ps_to_w2s (ps_tmp_ch_no_name, wz_input_src_name,sizeof (wz_input_src_name)/sizeof(wz_input_src_name[0]) -1) ;
        pw2s_text = wz_input_src_name ;

    }
    else if(pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_INPUT_SRC_INFO)
    {
        /* Deal with input source name */
        if (pt_tuning_info->t_input_src_info.ui1_input_src_id == 255)
        {
            #ifdef APP_CAST_TV_MMP
                pw2s_text   =   BANNER_TEXT("CAST");
            #else
                pw2s_text   =   BANNER_TEXT("MMP");
            #endif
        }
        else if((t_isl_rec.e_src_type == INP_SRC_TYPE_TV) && (FALSE == b_svl_empty))
        {
            pw2s_text   =   BANNER_TEXT("");
        }
        else
        {
            ISL_REC_T   t_isl = {0};

            /* get current input source name */
            if( NAVR_OK == banner_get_crnt_isl(&t_isl))
            {
                 a_isl_get_display_name_ex(&t_isl, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);
            }

            /* Priority: alias name >  input source name */
            pw2s_text = c_uc_w2s_strlen(w2s_alias)  > 0  ? w2s_alias :
                        c_uc_w2s_strlen(pt_tuning_info->t_input_src_info.w2s_input_src_name_alias) > 0 ?
                                        pt_tuning_info->t_input_src_info.w2s_input_src_name_alias :
                                        pt_tuning_info->t_input_src_info.w2s_input_src_name;
            {
                CHAR    ps_input_src_name[128] = {'\0'};

                if(c_uc_w2s_strlen(pw2s_text) > 0)
                {
                    memset(ps_input_src_name,'\0',128);
                    c_uc_w2s_to_ps(pw2s_text,ps_input_src_name,(sizeof(ps_input_src_name) - 1) );
                    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("w2s_input_src_name_alias => \"%s\"\n",ps_input_src_name));
                    //DBG_LOG_PRINT (("w2s_input_src_name_alias => \"%s\"\n",ps_input_src_name));
                }
                else
                {
                    //just case for HDMI1 connecting sound bar and box,int box src,info bar should show box name not sound bar name
                    a_cfg_get_cec_func(&ui1_cec_func);
                    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
                       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI &&
                       ui1_cec_func != APP_CFG_CEC_OFF)
                    {
                        UINT8 hdmi_cec_dev_idx = 0;

                        if(a_nav_is_signal_loss() == TRUE)
                        {
                            i4_ret_cec = a_cec_get_act_dev_by_no_signal(a_nav_cec_get_mw_handle(), t_isl_rec.ui1_internal_id, &hdmi_cec_dev_idx, &t_dev_info);

                        }
                        else
                        {
                            i4_ret_cec = a_cec_get_act_dev(a_nav_cec_get_mw_handle(), t_isl_rec.ui1_internal_id, &hdmi_cec_dev_idx, &t_dev_info);
                        }

                        if (i4_ret_cec == CECR_OK && c_uc_w2s_strlen(t_dev_info.aw2_osd_name) > 0)
                        {
                            pw2s_text = t_dev_info.aw2_osd_name;

                            CHAR    ps_input_src_name[128] = {0};
                            c_uc_w2s_to_ps(t_dev_info.aw2_osd_name,ps_input_src_name,(sizeof(ps_input_src_name) - 1) );
                            DBG_LOG_PRINT (("[banner src info] a_cec_get_act_dev input_src_name:%s,idx:%d\n",ps_input_src_name,hdmi_cec_dev_idx));
                        }
                    }
                }
            }


        }

        if ( pw2s_text != NULL && c_uc_w2s_strlen(pw2s_text) > 0)
        {
            if(c_uc_w2s_strlen(pw2s_text) > BANNEER_INPUT_SRC_NAME_MAX)
            {
                //c_uc_w2s_strncpy(wz_input_src_name,pw2s_text,BANNEER_INPUT_SRC_NAME_MAX);
                //c_uc_w2s_strcat(wz_input_src_name,L"...");
                banner_view_set_name_update_flag(TRUE);
                banner_view_update_scrl_banner_name(pw2s_text,c_uc_w2s_strlen(pw2s_text));
            }
            else
            {
                banner_view_set_name_update_flag(FALSE);
            }

            c_uc_w2s_strcpy(wz_input_src_name,pw2s_text);

            pw2s_text = wz_input_src_name;
        }

        /* Deal with input source icon */
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" ui1_input_src_id = %d  e_src_type = %d \n",pt_tuning_info->t_input_src_info.ui1_input_src_id, t_isl_rec.e_src_type)) ;
        if (pt_tuning_info->t_input_src_info.ui1_input_src_id == 255)
        {
#ifdef SEMAPHORE_SUPPORT
            if(a_rest_app_check_install_airplay() && a_rest_app_get_current_app_is_semaphore() == 0)
            {
                h_icon = h_g_nav_banner_new_input_airplay_pic;
            }
            else
#endif
            {
                h_icon = h_g_nav_banner_new_input_new_cast_pic;
            }
        }
        else if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        {
            //for keep same as before,otherwise the ch_no and ch_name would be empty
            if(b_svl_empty == FALSE)
            {
                CHAR  ps_tmp_ch_no_name[128] = {'\0'};
                CHAR  sz_channel_id[6]       = {0};
                CHAR  sz_channel_name[64]    = {0};
                UINT8 ui1_brdcst_src;

                BANNER_CHK_FAIL (nav_get_svl_rec (e_tv_win_id, &t_svl_rec)) ;
                nav_set_ch_num_and_name (&t_svl_rec, sz_channel_id, sz_channel_name) ;
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" ch num= %s,ch name= \"%s\" line:%d \n", sz_channel_id, sz_channel_name,__LINE__)) ;
                a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, &ui1_brdcst_src);

                switch (ui1_brdcst_src)
                {
                    case APP_CFG_BS_SRC_AIR:
                        h_icon = h_g_nav_banner_new_input_new_satellite_pic ;
                        break ;
                    case APP_CFG_BS_SRC_CABLE:
                        h_icon = h_g_nav_banner_new_input_tuner_img;
                        break ;
                    default :
                        h_icon = h_g_nav_banner_new_input_new_satellite_pic;
                        break ;
                }
                c_sprintf(ps_tmp_ch_no_name, "%s  %s", sz_channel_id, sz_channel_name);
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("ch name => \"%s\"\n",ps_tmp_ch_no_name));
                c_uc_ps_to_w2s (ps_tmp_ch_no_name, wz_input_src_name,sizeof (wz_input_src_name)/sizeof(wz_input_src_name[0]) -1) ;
                pw2s_text = wz_input_src_name ;
            }
            else
            {
                h_icon      =   h_g_nav_banner_new_input_tuner_img;
                pw2s_text   =   BANNER_TEXT("");
                if(b_svl_empty == TRUE)
                {
                    pw2s_text = MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_SCAN_CH);
                }

                if (c_uc_w2s_strlen(pt_tuning_info->t_input_src_info.w2s_input_src_name_alias) > 0)
                {
                    h_icon = nav_ipts_get_alias_icon(t_isl_rec.ui1_id, 0);
                    if(NULL_HANDLE == h_icon || b_svl_empty)
                    {
                        h_icon = h_g_nav_banner_new_input_new_satellite_pic;
                    }
                }
            }
        }
        else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV)
        {
            h_icon = NULL_HANDLE;
            switch(t_isl_rec.t_avc_info.e_video_type)
            {
                case DEV_AVC_HDMI:
                case DEV_AVC_DVI:
                    if (c_uc_w2s_strlen(pt_tuning_info->t_input_src_info.w2s_input_src_name_alias) > 0)
                    {
                        h_icon = nav_ipts_get_alias_icon(t_isl_rec.ui1_id, 0);
                    }
                    if (NULL_HANDLE  == h_icon)
                    {
                        h_icon = h_g_nav_banner_new_input_new_hdmi_pic;
                    }
                    break;
                case DEV_AVC_Y_PB_PR:
                case DEV_AVC_COMP_VIDEO:
                case DEV_AVC_COMBI:
                    if (c_uc_w2s_strlen(pt_tuning_info->t_input_src_info.w2s_input_src_name_alias) > 0)
                    {
                        h_icon = nav_ipts_get_alias_icon(t_isl_rec.ui1_id, 0);
                    }
                    if (NULL_HANDLE == h_icon)
                    {
                        h_icon = h_g_nav_banner_new_input_new_component_pic;
                    }
                    break;
                case DEV_AVC_VGA:
                    if (c_uc_w2s_strlen(pt_tuning_info->t_input_src_info.w2s_input_src_name_alias) > 0)
                    {
                        h_icon = nav_ipts_get_alias_icon(t_isl_rec.ui1_id, 0);
                    }
                    if (NULL_HANDLE == h_icon)
                    {
                        h_icon = h_g_nav_banner_new_input_new_computer_pic;
                    }
                    break;
                default:
                    if(a_rest_app_check_install_airplay() && a_rest_app_get_current_app_is_semaphore() == 0)
                    {
                        h_icon = h_g_nav_banner_new_input_airplay_pic;
                    }
                    else
                    {
                        h_icon = h_g_nav_banner_new_input_new_cast_pic;
                    }
                    break;
            };
        }
        else
        {
            if(a_rest_app_check_install_airplay() && a_rest_app_get_current_app_is_semaphore() == 0)
            {
                h_icon = h_g_nav_banner_new_input_airplay_pic;
            }
            else
            {
                h_icon = h_g_nav_banner_new_input_new_cast_pic;
            }
        }
    }
    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_IPTS_ICON, BANNER_TEXT(""), h_icon)) ;
    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_CH_NAME, pw2s_text, NULL_HANDLE)) ;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_tuning_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_handle_tuning_info (SI_INFO_CTRL_T              e_info_ctrl ,
                                         TV_WIN_ID_T                 e_tv_win_id ,
                                         SI_SET_INFO_T*              pt_si_info ,
                                         VOID*                       pv_tag)
{
    SI_TUNING_INFO_T*    pt_tuning_info = NULL ;

    if (!_banner_si_hldr_is_focused_win_id (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    /* check validation */
    if (!pt_si_info ||
        pt_si_info->e_category != SI_CATEGORY_TUNING_INFO)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* get tuning info */
    pt_tuning_info = &pt_si_info->u.t_tuning_info ;

    if (pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_VIDEO_RES)
    {
        _banner_handle_resolution_info(pt_si_info);
		banner_sys_audio_stream_update();//audio item always undisplay ,so update it with res at here;
    }

    if (pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_AV_STATUS)
    {
        switch (pt_tuning_info->e_av_status)
        {
            case NAV_AV_STATUS_SCRAMBLED_VIDEO_NO_AUDIO:
            case NAV_AV_STATUS_SCRAMBLED_AUDIO_VIDEO:
            case NAV_AV_STATUS_SCRAMBLED_VIDEO_CLEAR_AUDIO:

                break ;

            case NAV_AV_STATUS_NO_AUDIO_VIDEO:
            case NAV_AV_STATUS_SCRAMBLED_AUDIO_NO_VIDEO:
            case NAV_AV_STATUS_AUDIO_ONLY:

                break ;

            case NAV_AV_STATUS_UNKNOWN:
                /* do nothing */
                break ;

            case NAV_AV_STATUS_SCRAMBLED_AUDIO_CLEAR_VIDEO:
            case NAV_AV_STATUS_VIDEO_ONLY:
            case NAV_AV_STATUS_AUDIO_VIDEO:
            default:
                /* video is valid, about audio, it will handled by audio module */
                /* Do nothing */
                break ;
        }
        banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_RESOLUTION_TXT);
    }

    if (pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_CHANNEL_INFO)
    {
        _banner_handle_input_src_info(pt_tuning_info);
    }

    /* ATTENTION: we need check the input INPUT_SRC_INFO first then LOCKED_TYPE
     * 1) it will jump to TV state when current source is TV
     * 2) it will jump to IPTS_STATE when current source is NON_TV
     * 3) it will jump to EMPTY_SVL state if it is TV source with empty svl
     * 4) it will jump to IPTS state and set ITM_IPTS_LOCK_ICON if current source was locked.
     */
    if (pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_LOCKED_TYPE ||
        pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_INPUT_SRC_INFO)
    {
        if (pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_INPUT_SRC_INFO)
        {
            _banner_handle_input_src_info(pt_tuning_info);
        }

        if (pt_tuning_info->ui4_info_mask & SI_TUNING_INFO_MASK_LOCKED_TYPE)
        {
            if ((SI_TUNING_INFO_LOCKED_TYPE_CHANNEL_LOCKED        == pt_tuning_info->e_locked_type) ||
                (SI_TUNING_INFO_LOCKED_TYPE_PROGRAM_RATING_LOCKED == pt_tuning_info->e_locked_type) ||
                (SI_TUNING_INFO_LOCKED_TYPE_INP_SRC_LOCKED        == pt_tuning_info->e_locked_type))
            {
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_RESOLUTION_TXT,
                                                                    BANNER_TEXT(""),
                                                                    NULL_HANDLE)) ;
            }

            switch (pt_tuning_info->e_locked_type)
            {
                case SI_TUNING_INFO_LOCKED_TYPE_CHANNEL_LOCKED:
                    /* update tv lock icon to LOCK */
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_TV_LOCK_ICON, NULL,
                                        h_g_itm_img_icon_lock)) ;
                    break ;

                case SI_TUNING_INFO_LOCKED_TYPE_PROGRAM_RATING_LOCKED:
                    /* update tv lock icon to LOCK */
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_TV_LOCK_ICON, NULL,
                                        h_g_itm_img_icon_lock)) ;
                    break ;

                case SI_TUNING_INFO_LOCKED_TYPE_INP_SRC_LOCKED:
                    /* update tv lock icon to LOCK */
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_IPTS_LOCK_ICON, NULL,
                                        h_g_itm_img_icon_lock)) ;
                    break ;

                case SI_TUNING_INFO_LOCKED_TYPE_NONE :
                default :
                    /* when receive unlock message we need unlock
                     * IPTS_LOCK/CH_LOCK/PROG_LOCK first, then we need do :
                     * a) current is TV source, change to default tv state
                     * b) is non-TV source, change to input source state
                     */

                    /* update tv lock icon to UNLOCK */
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_TV_LOCK_ICON, NULL, 0)) ;

                    /* update input source lock icon to UNLOCK */
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_IPTS_LOCK_ICON, NULL, 0)) ;
                    break ;
            }
        }
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_event_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_handle_event_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    SI_EVENT_INFO_T*            pt_event_info = NULL ;
    NAV_BNR_STATE_ITEM_IDX_T    e_item_idx  = (NAV_BNR_STATE_ITEM_IDX_T)0 ;
    UTF16_T*                    pw2s_text = NULL ;      /* for text item */
    HANDLE_T                    h_icon = NULL_HANDLE ;  /* for icon item */
    UTF16_T                     w2s_text[128] = {0} ;


    if (!_banner_si_hldr_is_focused_win_id (e_tv_win_id))
    {
        BANNER_LOG (_BANNER_LOG_TYPE_OTH_INFO,("xxx not current win id \n "));
        return NAVR_OK ;
    }

    /* check validation */
    if (!pt_si_info
        ||
        pt_si_info->e_category != SI_CATEGORY_EVENT_INFO)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* get tuning info */
    pt_event_info = &pt_si_info->u.t_event_info;

    /* loop mask */
    if (pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_CRNT_PRG_TITLE)
    {
        CHAR   title[512]   = {0};

        e_item_idx      =       BANNER_ITM_PROG_TITLE ;
        pw2s_text       =       pt_event_info->pw2s_crnt_prg_title ;
        h_icon          =       NULL_HANDLE ;

        c_uc_w2s_to_ps (pw2s_text, title, c_uc_w2s_strlen(pw2s_text));
        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" title => \"%s\"\n",title) ) ;

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                e_item_idx, pw2s_text, h_icon)) ;

        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("prog title => \"%s\" \n", title)) ;
    }

    if (pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_CRNT_PRG_DETAIL)
    {
        CHAR   detail[1024] = {0};
        e_item_idx      =       BANNER_ITM_PROG_DETAIL;
        pw2s_text       =       pt_event_info->pw2s_crnt_prg_detail;
        h_icon          =       NULL_HANDLE ;

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                e_item_idx, pw2s_text, h_icon)) ;

        c_uc_w2s_to_ps (pw2s_text, detail, 1024);
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("prog detail=> \"%s\" \n", detail)) ;
    }

    if (pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_CRNT_PRG_RATING)
    {
        CHAR    s_rating_tmp[MAX_SI_EVENT_INFO_RATING_DESC_LEN+2] = {0};
        CHAR*   s_str = NULL;
        UTF16_T w2s_rating_str[MAX_SI_EVENT_INFO_RATING_DESC_LEN+2] = {0};

        c_memset(s_rating_tmp, 0, sizeof(CHAR)*(MAX_SI_EVENT_INFO_RATING_DESC_LEN+2));

        c_uc_w2s_to_ps(pt_event_info->t_crnt_prg_rating.w2s_rating_desc,
                                s_rating_tmp,
                                MAX_SI_EVENT_INFO_RATING_DESC_LEN+1);

        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("prog rating => \"%s\" \n", s_rating_tmp)) ;

        if((s_str = c_strstr(s_rating_tmp, "MPAA-")) != NULL)
        {
            c_uc_ps_to_w2s(s_str + 5, w2s_rating_str, 32+1);
            pw2s_text = w2s_rating_str;
        }
        else
        {
            pw2s_text = pt_event_info->t_crnt_prg_rating.w2s_rating_desc ;
        }

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_RATING, pw2s_text, NULL_HANDLE)) ;

    }

    if (pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_CRNT_PRG_TIME)
    {
        TIME_T     t_time_start        = 0;
        TIME_T     t_time_duration     = 0;
        TIME_T     t_time_end          = 0;
        DTG_T      t_start_dtg         = {0};
#if 0
        DTG_T      t_duration_dtg      = {0};
#endif
        DTG_T      t_end_dtg           = {0};
        CHAR       s_time_string[64+1] = {0};

        c_memset (w2s_text, 0, sizeof(w2s_text)) ;

        do
        {
            /* start time */
            t_time_start = pt_event_info->t_crnt_prg_time.t_time_start ;
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("current prg t_time_start => %d \n",t_time_start));
            /* duration time */
            t_time_duration = pt_event_info->t_crnt_prg_time.t_time_duration ;
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("current prg t_time_duration => %d \n",t_time_duration));
            /* end time */
            t_time_end = t_time_start + t_time_duration ;
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("current prg t_time_end => %d \n",t_time_end));

            /* transfer start to DTG*/
            t_time_start += BANNER_CRNT_EVNT_START_TIME_ROUND_UP_SECONDS;
            BANNER_BREAK_ON_FAIL (c_dt_utc_sec_to_loc_dtg (t_time_start, &t_start_dtg));
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("current prg t_time_start => %d hr=> %d min=> %d\n",t_time_start,t_start_dtg.ui1_hr,t_start_dtg.ui1_min));
#if 0

            /* transfer duration to DTG */
            BANNER_BREAK_ON_FAIL (c_dt_utc_sec_to_loc_dtg (t_time_duration, &t_duration_dtg));
#endif

            /* transfer end to DTG */
            BANNER_BREAK_ON_FAIL (c_dt_utc_sec_to_loc_dtg (t_time_end, &t_end_dtg));
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("current prg t_time_end => %d hr=> %d min=> %d\n",t_time_end,t_end_dtg.ui1_hr,t_end_dtg.ui1_min));
            _banner_si_hldr_get_event_display_time( &t_start_dtg, &t_end_dtg, &t_time_duration, s_time_string) ;

            NAV_ASSERT (c_strlen(s_time_string) < sizeof (s_time_string)) ;
            BANNER_CHK_FAIL ( (c_strlen(s_time_string) < sizeof (s_time_string)) ? NAVR_OK : NAVR_FAIL) ;
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("current prg time => \"%s\" \n",s_time_string));
            c_uc_ps_to_w2s (s_time_string, w2s_text,
                                sizeof (w2s_text)/sizeof(w2s_text[0]) -1);

            e_item_idx      =   BANNER_ITM_PROG_TIME;
            pw2s_text       =   w2s_text;
            h_icon          =   0 ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                e_item_idx, pw2s_text, h_icon)) ;
        } while (0);
    }

    if (pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_NEXT_PRG_TITLE)
    {
#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
        e_item_idx      =       BANNER_ITM_NEXT_PROG_TITLE ;
        pw2s_text       =       pt_event_info->pw2s_next_prg_title ;
        h_icon          =       NULL_HANDLE ;

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                e_item_idx, pw2s_text, h_icon)) ;
#endif
    }

    if (pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_NEXT_PRG_TIME)
    {
#ifdef APP_NAV_BNR_NEXT_EVENT_SUPPORT
        DTG_T                   t_start_dtg         = {0};
        DTG_T                   t_end_dtg           = {0};
        TIME_T                  t_time_start        = 0;
        TIME_T                  t_time_duration     = 0;
        CHAR                    s_time_string[64+1] = {0};

        c_memset (w2s_text, 0, sizeof(w2s_text)) ;

        do
        {
            /* start time */
            t_time_start = pt_event_info->t_next_prg_time.t_time_start ;

            /* transfer to start DTG*/
            t_time_start += BANNER_CRNT_EVNT_START_TIME_ROUND_UP_SECONDS;

            BANNER_BREAK_ON_FAIL (c_dt_utc_sec_to_loc_dtg(
                                t_time_start, &t_start_dtg));

            /* duration */
            t_time_duration = pt_event_info->t_next_prg_time.t_time_duration ;

            /* transfer to duration DTG */
            BANNER_BREAK_ON_FAIL (c_dt_utc_sec_to_loc_dtg(
                                t_time_start + t_time_duration ,
                                &t_end_dtg));

            _banner_si_hldr_get_event_display_time(
                                &t_start_dtg, &t_end_dtg,
                                &t_time_duration, s_time_string) ;

            NAV_ASSERT (c_strlen(s_time_string) < sizeof (s_time_string)) ;
            BANNER_CHK_FAIL ( (c_strlen(s_time_string) < sizeof (s_time_string)) ? NAVR_OK : NAVR_FAIL) ;
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("next prg time => \"%s\" \n",s_time_string));
            c_uc_ps_to_w2s (s_time_string, w2s_text,
                                sizeof (w2s_text)/sizeof(w2s_text[0]) -1);

            e_item_idx      =   BANNER_ITM_NEXT_PROG_TIME;
            pw2s_text       =   w2s_text;
            h_icon          =   0 ;

            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                e_item_idx, pw2s_text, h_icon)) ;

        } while (0);
#endif
    }

    if ((pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_NEXT_PRG_RATING)
        ||
        (pt_event_info->ui4_info_mask & SI_EVENT_INFO_MASK_NEXT_PRG_DETAIL))
    {
        /* Do nothing */
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_3d_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_handle_3d_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    SI_3D_INFO_T*               pt_3d_info = NULL ;
    NAV_BNR_STATE_ITEM_IDX_T    e_item_idx = (NAV_BNR_STATE_ITEM_IDX_T)0 ;
    UTF16_T*                    pw2s_text = NULL ;      /* for text item */
    HANDLE_T                    h_frm = NULL_HANDLE ;   /* for frm item */

    if (!_banner_si_hldr_is_focused_win_id (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    /* check validation */
    if (!pt_si_info
        || pt_si_info->e_category != SI_CATEGORY_3D_MODE_INFO)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* get 3D info */
    pt_3d_info = &pt_si_info->u.t_3D_info;

    if ((pt_3d_info->ui4_info_mask & SI_3D_MODE_INFO_MASK)||(pt_3d_info->ui4_info_mask & SI_3D_SRC_TAG_INFO_MASK))
    {
        ISL_REC_T    t_cur_isl_rec;
        BOOL         b_3D_support = FALSE;

        nav_get_isl_rec (e_tv_win_id, &t_cur_isl_rec);

#ifndef APP_CUST_PLT_OPT
    if (a_app_cust_plt_opt())
#endif
    {
        a_cfg_custom_plf_opt_get_3d_support(&b_3D_support);
    }
        if ((t_cur_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
            &&
            (b_3D_support == TRUE))
        {
            switch (pt_3d_info->t_3d_mode_info.i2_3D_mode)
            {
                case APP_CFG_3D_MODE_OFF:
                {
                    e_item_idx      =       BANNER_ITM_FRM_3D ;
                    pw2s_text       =       NULL ;
                    h_frm           =       NULL_HANDLE ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;


                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                    pw2s_text       =       NULL ;
                    h_frm           =       NULL_HANDLE ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;

                    e_item_idx      =       BANNER_ITM_3D_FMT ;
                    pw2s_text       =       NULL ;
                    h_frm           =       NULL_HANDLE ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;
                }
                    break;
                case APP_CFG_3D_MODE_SBS:
                {
                    e_item_idx      =       BANNER_ITM_FRM_3D ;
                    pw2s_text       =       NULL ;
                    h_frm           =       h_g_itm_img_frm_3d ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;

                    if (pt_3d_info->t_3d_mode_info.i2_3D_to_2D == APP_CFG_3D_TO_2D_OFF)
                    {
                        UTF16_T                     w2s_mode_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_mode_text,L"3D");

                        e_item_idx      =       BANNER_ITM_3D_MODE ;
                        pw2s_text       =       w2s_mode_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }
                    else
                    {
                        UTF16_T                     w2s_mode_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_mode_text,L"2D");

                        e_item_idx      =       BANNER_ITM_3D_MODE ;
                        pw2s_text       =       w2s_mode_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }

                    {
                        UTF16_T                     w2s_fmt_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_fmt_text,L"SBS");

                        e_item_idx      =       BANNER_ITM_3D_FMT ;
                        pw2s_text       =       w2s_fmt_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }
                }
                    break;
                case APP_CFG_3D_MODE_TAB:
                {
                    e_item_idx      =       BANNER_ITM_FRM_3D ;
                    pw2s_text       =       NULL ;
                    h_frm           =       h_g_itm_img_frm_3d ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;

                    if (pt_3d_info->t_3d_mode_info.i2_3D_to_2D == APP_CFG_3D_TO_2D_OFF)
                    {
                        UTF16_T                     w2s_mode_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_mode_text,L"3D");

                        e_item_idx      =       BANNER_ITM_3D_MODE ;
                        pw2s_text       =       w2s_mode_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }
                    else
                    {
                        UTF16_T                     w2s_mode_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_mode_text,L"2D");

                        e_item_idx      =       BANNER_ITM_3D_MODE ;
                        pw2s_text       =       w2s_mode_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }

                    {
                        UTF16_T                     w2s_fmt_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_fmt_text,L"TB");

                        e_item_idx      =       BANNER_ITM_3D_FMT ;
                        pw2s_text       =       w2s_fmt_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }
                }
                    break;
#ifdef APP_3D_MODE_CUSTOM
                case APP_CFG_3D_MODE_SENSIO:
                {
                    e_item_idx      =       BANNER_ITM_FRM_3D ;
                    pw2s_text       =       NULL ;
                    h_frm           =       h_g_itm_img_frm_3d ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;

                    if (pt_3d_info->t_3d_mode_info.i2_3D_to_2D == APP_CFG_3D_TO_2D_OFF)
                    {
                        UTF16_T                     w2s_mode_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_mode_text,L"3D");

                        e_item_idx      =       BANNER_ITM_3D_MODE ;
                        pw2s_text       =       w2s_mode_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }
                    else
                    {
                        UTF16_T                     w2s_mode_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_mode_text,L"2D");

                        e_item_idx      =       BANNER_ITM_3D_MODE ;
                        pw2s_text       =       w2s_mode_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }

                    {
                        UTF16_T                     w2s_fmt_text[128] = {0} ;
                        c_uc_w2s_strcpy(w2s_fmt_text,L"SENSIO");

                        e_item_idx      =       BANNER_ITM_3D_FMT ;
                        pw2s_text       =       w2s_fmt_text ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }
                }
                    break;
#endif
                case APP_CFG_3D_MODE_AUTO:
                {
                    if (pt_3d_info->t_src_tag_info.e_tv_win_id == TV_WIN_ID_SUB)
                    {
                        e_item_idx      =       BANNER_ITM_FRM_3D ;
                        pw2s_text       =       NULL ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;


                        e_item_idx      =       BANNER_ITM_3D_MODE ;
                        pw2s_text       =       NULL ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;

                        e_item_idx      =       BANNER_ITM_3D_FMT ;
                        pw2s_text       =       NULL ;
                        h_frm           =       NULL_HANDLE ;
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                e_item_idx, pw2s_text, h_frm)) ;
                    }
                    else
                    {
                        switch (pt_3d_info->t_src_tag_info.e_src_tag3D_type)
                        {
                            case VSH_SRC_TAG3D_TB:
                            {
                                e_item_idx      =       BANNER_ITM_FRM_3D ;
                                pw2s_text       =       NULL ;
                                h_frm           =       h_g_itm_img_frm_3d ;
                                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                        e_item_idx, pw2s_text, h_frm)) ;

                                if (pt_3d_info->t_3d_mode_info.i2_3D_to_2D == APP_CFG_3D_TO_2D_OFF)
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"3D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                                else
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"2D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }

                                {
                                    UTF16_T                     w2s_fmt_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_fmt_text,L"TB");

                                    e_item_idx      =       BANNER_ITM_3D_FMT ;
                                    pw2s_text       =       w2s_fmt_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                            }
                                break;
                            case VSH_SRC_TAG3D_SBS:
                            {
                                e_item_idx      =       BANNER_ITM_FRM_3D ;
                                pw2s_text       =       NULL ;
                                h_frm           =       h_g_itm_img_frm_3d ;
                                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                        e_item_idx, pw2s_text, h_frm)) ;

                                if (pt_3d_info->t_3d_mode_info.i2_3D_to_2D == APP_CFG_3D_TO_2D_OFF)
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"3D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                                else
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"2D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }

                                {
                                    UTF16_T                     w2s_fmt_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_fmt_text,L"SBS");

                                    e_item_idx      =       BANNER_ITM_3D_FMT ;
                                    pw2s_text       =       w2s_fmt_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                            }
                                break;
                            case VSH_SRC_TAG3D_SENSIO:
                            {
                                e_item_idx      =       BANNER_ITM_FRM_3D ;
                                pw2s_text       =       NULL ;
                                h_frm           =       h_g_itm_img_frm_3d ;
                                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                        e_item_idx, pw2s_text, h_frm)) ;

                                if (pt_3d_info->t_3d_mode_info.i2_3D_to_2D == APP_CFG_3D_TO_2D_OFF)
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"3D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                                else
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"2D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }

                                {
                                    UTF16_T                     w2s_fmt_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_fmt_text,L"SENSIO");

                                    e_item_idx      =       BANNER_ITM_3D_FMT ;
                                    pw2s_text       =       w2s_fmt_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                            }
                                break;
                            case VSH_SRC_TAG3D_2D:
                            case VSH_SRC_TAG3D_NOT_SUPPORT:
                            {
                                e_item_idx      =       BANNER_ITM_FRM_3D ;
                                pw2s_text       =       NULL ;
                                h_frm           =       NULL_HANDLE ;
                                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                        e_item_idx, pw2s_text, h_frm)) ;


                                e_item_idx      =       BANNER_ITM_3D_MODE ;
                                pw2s_text       =       NULL ;
                                h_frm           =       NULL_HANDLE ;
                                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                        e_item_idx, pw2s_text, h_frm)) ;

                                e_item_idx      =       BANNER_ITM_3D_FMT ;
                                pw2s_text       =       NULL ;
                                h_frm           =       NULL_HANDLE ;
                                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                        e_item_idx, pw2s_text, h_frm)) ;
                            }
                                break;
                            default:
                            {
                                e_item_idx      =       BANNER_ITM_FRM_3D ;
                                pw2s_text       =       NULL ;
                                h_frm           =       h_g_itm_img_frm_3d ;
                                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                        e_item_idx, pw2s_text, h_frm)) ;

                                if (pt_3d_info->t_3d_mode_info.i2_3D_to_2D == APP_CFG_3D_TO_2D_OFF)
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"3D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                                else
                                {
                                    UTF16_T                     w2s_mode_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_mode_text,L"2D");

                                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                                    pw2s_text       =       w2s_mode_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }

                                {
                                    UTF16_T                     w2s_fmt_text[128] = {0} ;
                                    c_uc_w2s_strcpy(w2s_fmt_text,L"AUTO");

                                    e_item_idx      =       BANNER_ITM_3D_FMT ;
                                    pw2s_text       =       w2s_fmt_text ;
                                    h_frm           =       NULL_HANDLE ;
                                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                                            e_item_idx, pw2s_text, h_frm)) ;
                                }
                            }
                                break;
                        }
                    }
                }
                    break;
                default:
                {
                    e_item_idx      =       BANNER_ITM_FRM_3D ;
                    pw2s_text       =       NULL ;
                    h_frm           =       NULL_HANDLE ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;


                    e_item_idx      =       BANNER_ITM_3D_MODE ;
                    pw2s_text       =       NULL ;
                    h_frm           =       NULL_HANDLE ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;

                    e_item_idx      =       BANNER_ITM_3D_FMT ;
                    pw2s_text       =       NULL ;
                    h_frm           =       NULL_HANDLE ;
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                            e_item_idx, pw2s_text, h_frm)) ;
                }
                    break;
            }
        }
        else
        {
            e_item_idx      =       BANNER_ITM_FRM_3D ;
            pw2s_text       =       NULL ;
            h_frm           =       NULL_HANDLE ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                    e_item_idx, pw2s_text, h_frm)) ;


            e_item_idx      =       BANNER_ITM_3D_MODE ;
            pw2s_text       =       NULL ;
            h_frm           =       NULL_HANDLE ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                    e_item_idx, pw2s_text, h_frm)) ;

            e_item_idx      =       BANNER_ITM_3D_FMT ;
            pw2s_text       =       NULL ;
            h_frm           =       NULL_HANDLE ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                    e_item_idx, pw2s_text, h_frm)) ;
        }

    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_ch_num_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_handle_ch_num_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    SI_CH_NUM_INFO_T*           pt_ch_num_info = NULL ;
    NAV_BNR_STATE_ITEM_IDX_T    e_item_idx  = (NAV_BNR_STATE_ITEM_IDX_T)0 ;
    UTF16_T*                    pw2s_text = NULL ;      /* for text item */
    HANDLE_T                    h_icon = NULL_HANDLE;   /* for icon item */
    UTF16_T                     w2s_text[128] = {0} ;
    UTF16_T                     w2s_text_tts[128] = {0} ;
    CHAR                        ps_ch_num[22] = {0} ;

    if (!_banner_si_hldr_is_focused_win_id (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    /* check validation */
    if (!pt_si_info
        ||
        pt_si_info->e_category != SI_CATEGORY_CH_NUM_INFO)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* get channel number info */
    pt_ch_num_info = &pt_si_info->u.t_ch_num_info;

    /* loop mask */
    if (pt_ch_num_info->ui4_info_mask & SI_CH_NUM_INFO_MASK_INPUT)
    {
        do
        {
            /* max support 999-999 */

            if (!pt_ch_num_info->t_ch_input.b_is_ch_inputing)
            {
                /* NOT to use "return" as there has some
                 * others need to be process
                 */
                break ;
            }

            if (pt_ch_num_info->t_ch_input.b_is_inputing_major)
            {
                /* only major inputted */
                c_sprintf (ps_ch_num,
                                CH_NUM_DISP_FMT_MAJOR_ONLY ,
                                pt_ch_num_info->t_ch_input.ui4_major_chn_num) ;
            }
            else if (
                SI_INVALID_CHANNEL_NUMBER ==
                pt_ch_num_info->t_ch_input.ui4_minor_chn_num)
            {
                /* minor number is invalide (just prepare to input minor part) */
                c_sprintf (ps_ch_num,
                                CH_NUM_DISP_FMT_MAJOR_WITH_ZERO_MINOR,
                                pt_ch_num_info->t_ch_input.ui4_major_chn_num) ;
            }
            else
            {
                /* minor number is valide, display full part */
                c_sprintf (ps_ch_num,
                                CH_NUM_DISP_FMT_MAJOR_MINOR,
                                pt_ch_num_info->t_ch_input.ui4_major_chn_num,
                                pt_ch_num_info->t_ch_input.ui4_minor_chn_num) ;
            }

            NAV_ASSERT (c_strlen(ps_ch_num) < sizeof(ps_ch_num) - 1) ;
            BANNER_CHK_FAIL ( (c_strlen(ps_ch_num) < sizeof(ps_ch_num) - 1) ? NAVR_OK : NAVR_FAIL) ;

            c_uc_ps_to_w2s (ps_ch_num, w2s_text,
                                sizeof (w2s_text)/sizeof(w2s_text[0]) -1) ;

            /* prepare data to notify banner */
            e_item_idx      =   BANNER_ITM_IPT_CH_NO ;
            pw2s_text       =   w2s_text ;
            h_icon          =   0 ;             /* not used */

#ifdef APP_TTS_SUPPORT
            c_uc_w2s_strncpy(w2s_text_tts,w2s_text,128);
            _banner_sys_w2s_ch_r(w2s_text_tts, w2s_text_tts, 128, '-', " dash ");

            //char ch_num[128] = {0};
            //c_uc_w2s_to_ps(w2s_text_tts,ch_num,sizeof(ch_num));
            //DBG_LOG_PRINT(("[banner w2s_text_tts] %d w2s_text_tts:%s\n",__LINE__,ch_num));

            a_app_tts_play(w2s_text_tts, c_uc_w2s_strlen(w2s_text_tts));
#endif

            nav_banner_set_from_ch_num_key(TRUE);

            /* notify to banenr (request to update view part */
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                e_item_idx, pw2s_text, h_icon)) ;

            /* after we completed the update item, we need change state to
             * "changing" immediately to display the inputs number
             */
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                BANNER_STATE_INPTTING,
                                NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE)) ;

            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" [banner ch_num]num= %s",ps_ch_num));
        }while (0) ;
    }

    if (pt_ch_num_info->ui4_info_mask & SI_CH_NUM_INFO_MASK_RESULT)
    {
        banner_view_tv_info_updeted_erase();
        /* unlock inputting state first */
        BANNER_LOG_ON_FAIL (banner_unlock_state (
                                BANNER_STATE_INPTTING)) ;

        switch (pt_ch_num_info->e_result)
        {
        case SI_CH_NUM_INFO_RESULT_FAILED :
            /* RESULT_FAILED ,back to final state */
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                BANNER_STATE_VIRTUAL_FINAL,
                                !NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE)) ;
            break ;

        case SI_CH_NUM_INFO_RESULT_CANCEL :
            /* RESULT_CANCEL will cause banner exit */
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                BANNER_STATE_NONE,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;
            break ;

        case SI_CH_NUM_INFO_RESULT_SUCCESS :
        default :
            /* do nothing */
            /* just wait before service change notification */
            break ;
        }

    }

    return NAVR_OK ;
}

#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_cc_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

static INT32 _banner_handle_cc_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    SI_CC_T*                    pt_cc_info = NULL ;
    HANDLE_T                    h_icon = NULL_HANDLE ;  /* for icon item */

    if (!_banner_si_hldr_is_focused_win_id (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    /* check validation */
    if (!pt_si_info
        ||
        pt_si_info->e_category != SI_CATEGORY_CC_INFO)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* get tuning info */
    pt_cc_info = &pt_si_info->u.t_cc_info;

    if ((pt_cc_info->ui4_info_mask & SI_CC_MASK_RENDERING) ||
        (pt_cc_info->ui4_info_mask & SI_CC_MASK_CRNT_CC_LANG))
    {
        if (pt_cc_info->ui4_info_mask & SI_CC_MASK_RENDERING)
        {
            if (SI_CC_RENDERING_TYPE_OFF == pt_cc_info->e_rendering)
            {
                h_icon = h_g_nav_cc_off_img;
            }
            else
            {
                h_icon = h_g_nav_cc_on_img;
            }
        }

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                BANNER_ITM_CAPTION_ICON, NULL, h_icon)) ;
    }

    return NAVR_OK ;
}
#endif



static INT32 _banner_aud_check_tv_mode()
{
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))
    TV_MODE_T   e_tv_mode       = TV_MODE_TYPE_NORMAL;
    TV_WIN_ID_T ui1_pip_aud_src = {0};
    ISL_REC_T   t_isl_rec       = {0};

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
                return NAVR_FAIL;
            }
        }
    }
#endif

    return NAVR_OK;
}


static INT32 _banner_aud_get_scc_audio_type_out(SCC_AUD_IEC_TYPE_T*  pe_iec_type)
{
    INT32                 i4_ret = NAVR_FAIL;
    HANDLE_T              h_scc = NULL_HANDLE;
    SM_COMMAND_T          at_sm_cmds[3];

    if(pe_iec_type == NULL)
    {
        return NAVR_INV_ARG;
    }

    /* get scc main / sub  handle */
    do{
        /*scc component for mts operation*/
        at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
        at_sm_cmds[2].u.ui4_data = 0;

        if(0 != c_scc_comp_open(at_sm_cmds, &h_scc) || NULL_HANDLE == h_scc )
            break;
        i4_ret = c_scc_aud_get_iec_type(h_scc,pe_iec_type);
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n[banner DOLBY_AUDIO] [audio type] e_iec_type = %d, i4_ret = %d\n",*pe_iec_type,i4_ret));
        c_scc_comp_close(h_scc);
    }while(0);

    return NAVR_OK;
}


static INT32 _banner_aud_get_audio_stream_text(UTF16_T* w2s_str, SIZE_T z_len)
{
    INT32       i4_ret          = 0;
    UTF16_T     w2s_string[65]  = {0};
    UTF16_T*    pw2s_audio_fmt  = NULL;
    ASH_AUDIO_INFO_T t_audio_info;
    SIZE_T      z_len_remain    = 64;
    SVL_REC_T   t_svl_rec       = {0};
    BOOL        b_found         = FALSE;
    BOOL        b_digital_ch    = FALSE;
    UINT8       cast_state      = 0;
    UTF16_T     w2s[64]         = {0} ;
    ISL_REC_T   t_isl_rec       = {0};
    extern UTF16_T* nav_get_audio_fmt_str(ASH_CHANNELS_T e_channels);
    extern UTF16_T* nav_get_audio_mts_str(SCC_AUD_MTS_T e_mts);
    SCC_AUD_IEC_TYPE_T e_iec_type = {0};
    TV_WIN_ID_T  e_tv_win_id    = {0};

    c_memset(&t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    nav_get_focus_id(&e_tv_win_id);
    /* Get digital/analog channel */
    i4_ret = nav_get_svl_rec(e_tv_win_id,&t_svl_rec);
    BANNER_CHK_FAIL(i4_ret);

    //get non-TV source status
    nav_get_isl_rec(e_tv_win_id,&t_isl_rec);
    a_icl_custom_get_cast_src_status(&cast_state);
    //DBG_LOG_PRINT(("[Yuhong] %s  %s  (%d) cast_state=(%d) e_video_type=(%x)\n",__FILE__,__FUNCTION__,__LINE__,cast_state,t_isl_rec.t_avc_info.e_video_type));
    if(b_found \
       && (t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG) \
       && (t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI) \
       && (!cast_state || t_isl_rec.t_avc_info.e_video_type !=DEV_VTRL_CAST))
    {
        b_digital_ch = TRUE;
    }

    /* get stream num */
    i4_ret = _banner_aud_check_tv_mode();
    BANNER_CHK_FAIL(i4_ret);

    i4_ret = _banner_aud_get_scc_audio_type_out(&e_iec_type);
    BANNER_CHK_FAIL(i4_ret);

    if ((b_digital_ch || a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)&&
        (!cast_state || t_isl_rec.t_avc_info.e_video_type !=DEV_VTRL_CAST)&&
        (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status()))
    {
        i4_ret = c_svctx_get_audio_info(nav_get_crnt_svctx(), &t_audio_info);

        if(i4_ret == SVCTXR_OK)
        {
            if (ASH_AUDIO_FMT_AC3 ==  t_audio_info.e_aud_fmt )
            {
                z_len_remain = c_uc_w2s_strlen(w2s_string);
                c_uc_w2s_strncat(w2s_string, L"Dolby Audio ", 64 - z_len_remain);
            }
            else if (ASH_AUDIO_FMT_E_AC3 == t_audio_info.e_aud_fmt)
            {
                if(e_iec_type != SCC_AUD_IEC_CFG_DDP_ATMOS || i4_ret != NAVR_OK)
                {
                    c_uc_w2s_strcpy(w2s, L"Dolby Audio-DD+ ");
                }
                else
                {
                    c_uc_w2s_strcpy(w2s, L"Dolby Atmos-DD+ ");
                }
                pw2s_audio_fmt = w2s ;
            }
            else if((ASH_AUDIO_FMT_AAC == t_audio_info.e_aud_fmt)&&(e_iec_type == SCC_AUD_IEC_CFG_DD))
            {
                c_uc_w2s_strcpy(w2s, L"Dolby Audio-DD ");
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

        i4_ret = c_svctx_get_audio_info(nav_get_crnt_svctx(), &t_audio_info);
        if(i4_ret != SVCTXR_OK)
        {
            DBG_LOG_PRINT(("%s,%d [sys info] get audio info fail \r\n",__FUNCTION__,__LINE__));
        }

        if (ASH_AUDIO_FMT_AC3 ==  t_audio_info.e_aud_fmt )
        {
            c_uc_w2s_strcpy(w2s, L"Dolby Audio-DD ");
            pw2s_audio_fmt = w2s ;
        }
        else if (ASH_AUDIO_FMT_E_AC3 == t_audio_info.e_aud_fmt)
        {

            if(e_iec_type != SCC_AUD_IEC_CFG_DDP_ATMOS || i4_ret != NAVR_OK)
            {
                c_uc_w2s_strcpy(w2s, L"Dolby Audio-DD+ ");
            }
            else
            {
                c_uc_w2s_strcpy(w2s, L"Dolby Atmos-DD+ ");
            }
            pw2s_audio_fmt = w2s ;
        }
        else if((ASH_AUDIO_FMT_AAC == t_audio_info.e_aud_fmt)&&(e_iec_type == SCC_AUD_IEC_CFG_DD))
        {
            c_uc_w2s_strcpy(w2s, L"Dolby Audio-DD ");
            pw2s_audio_fmt = w2s ;

        }
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

    c_memset(w2s_str, 0, sizeof(UTF16_T)*z_len);
    c_uc_w2s_strncpy(w2s_str, w2s_string, z_len);
    w2s_str[z_len - 1] = 0;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_aud_strm_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_handle_aud_strm_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    SI_AUD_STRM_INFO_T*         pt_aud_strm_info = NULL ;
    NAV_BNR_STATE_ITEM_IDX_T    e_item_idx  = (NAV_BNR_STATE_ITEM_IDX_T)0 ;
    UTF16_T*                    pw2s_text = NULL ;      /* for text item */
    UTF16_T*                    pw2s_text_ex = NULL ;      /* for text item */
    HANDLE_T                    h_icon = NULL_HANDLE ;  /* for icon item */
    UTF16_T                     w2s_text[128] = {0} ;
    CHAR                        ac_aud_info[64] = {0} ;
    UINT16                      ui2_sel_idx = 0 ;
    UINT16                      ui2_sel_num = 0 ;
    ASH_AUDIO_INFO_T            t_audio_info;
    HANDLE_T                    h_svctx;
    INT32                       i4_ret           = NAVR_OK;
    ISL_REC_T                   t_isl_rec = {0};

    if (!_banner_si_hldr_is_focused_win_id (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    /* check validation */
    if (!pt_si_info ||
        pt_si_info->e_category != SI_CATEGORY_AUD_STRM_INFO)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }
    c_memset(& t_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    if(NAVR_OK != (i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx)))
    {
        DBG_ERROR((_ERROR_HEADER"<TEST_FOR_DOLBY> %s(): nav_get_svctx_handle(win=%d) failed, i4_ret=%d.\r\n", __FUNCTION__, e_tv_win_id, i4_ret));
        return NAVR_FAIL;
    }
    /* get audio stream info */
    pt_aud_strm_info = &pt_si_info->u.t_aud_strm_info;
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[%s][%d] pt_aud_strm_info->ui4_info_mask=%d\n", __FUNCTION__, __LINE__,pt_aud_strm_info->ui4_info_mask));
    BANNER_LOG_ON_FAIL(_notify_to_banner_item_changed (BANNER_ITM_AUDIO_OUT, BANNER_TEXT(""),NULL_HANDLE));
    /* loop mask */
    if ( (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_SEL_IDX)||
         (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_SEL_NUM)||
         (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_LANG)||
         (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_LANG2) )
    {
        /* reset w2s_text */
        c_memset (w2s_text, 0, sizeof(w2s_text)) ;

        if (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_SEL_IDX)
        {
            ui2_sel_idx     =   pt_aud_strm_info->ui2_sel_idx + 1 ;     /* start from '1' */
        }

        if (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_SEL_NUM)
        {
            ui2_sel_num     =   pt_aud_strm_info->ui2_sel_num ;
        }

        if (ui2_sel_idx <= ui2_sel_num && ui2_sel_num != 0)
        {
            if (ui2_sel_idx >= 100)
            {
                c_sprintf (ac_aud_info, " %d. ", ui2_sel_idx) ;
            }
            else
            {
                c_sprintf (ac_aud_info, " %d/%d ", ui2_sel_idx, ui2_sel_num) ;
            }

            c_uc_ps_to_w2s (ac_aud_info,
                            w2s_text,
                            sizeof (w2s_text)/sizeof(w2s_text[0]) -1) ;
        }

        NAV_ASSERT (c_strlen (ac_aud_info) < sizeof(ac_aud_info)/sizeof(ac_aud_info[0]) -1) ;
        BANNER_CHK_FAIL ( (c_strlen (ac_aud_info) < sizeof(ac_aud_info)/sizeof(ac_aud_info[0]) -1) ? NAVR_OK : NAVR_FAIL) ;

        if (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_LANG)
        {
            pw2s_text = nav_get_display_lang ((const ISO_639_LANG_T*)&pt_aud_strm_info->s639_dig_aud_lang) ;

            if (!pw2s_text || 0 == c_uc_w2s_strlen (pw2s_text))
            {
                /* unknown language, we will display it with the orignal string.
                 * if orignal string is empty, diplay it with "UNKNOWN"
                 */
                if (0 == c_strlen (pt_aud_strm_info->s639_dig_aud_lang)         /* empty */
                    ||
                    0 == c_strcmp (pt_aud_strm_info->s639_dig_aud_lang, "   ")  /* 3 spaces */
                    ||
                    0 == c_strcmp (pt_aud_strm_info->s639_dig_aud_lang, "  ")   /* 2 spaces */
                    ||
                    0 == c_strcmp (pt_aud_strm_info->s639_dig_aud_lang, " ") )  /* 1 space */
                {
                #if 0
                    c_uc_w2s_strcat (w2s_text + c_uc_w2s_strlen(w2s_text),
                                MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_AUD_MTS_UNK)) ;
                #endif
                }
                else
                {
                    /* max support 12 characters, if more than 12, it will only display first 9
                     * characters + "..."
                     */
                    if (c_strlen (pt_aud_strm_info->s639_dig_aud_lang) > 12)
                    {
                        c_uc_ps_to_w2s (pt_aud_strm_info->s639_dig_aud_lang,
                                        w2s_text + c_uc_w2s_strlen(w2s_text),
                                        12) ;  /* display first 9 characters */

                        /* "..." means there has any more informations has not displayed */
                        /*remove ..., all len plus 3*/
                    }
                    else
                    {
                        c_uc_ps_to_w2s (pt_aud_strm_info->s639_dig_aud_lang,
                                        w2s_text + c_uc_w2s_strlen(w2s_text),
                                        12) ;  /* max support 12 characters */
                    }
                }
            }
            else
            {
                c_uc_w2s_strcat (w2s_text, pw2s_text) ;
            }
        }

        if (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_LANG2)
        {
            /* append "+" */
            c_uc_w2s_strcat (w2s_text, L"+\0") ;

            pw2s_text = nav_get_display_lang ((const ISO_639_LANG_T*)&pt_aud_strm_info->s639_dig_aud_lang2) ;

            if (!pw2s_text || 0 == c_uc_w2s_strlen (pw2s_text))
            {
                /* unknown language, we will display it with the orignal string.
                 * if orignal string is empty, diplay it with "UNKNOWN"
                 */
                if (0 == c_strlen (pt_aud_strm_info->s639_dig_aud_lang2)         /* empty */
                    ||
                    0 == c_strcmp (pt_aud_strm_info->s639_dig_aud_lang2, "   ")  /* 3 spaces */
                    ||
                    0 == c_strcmp (pt_aud_strm_info->s639_dig_aud_lang2, "  ")   /* 2 spaces */
                    ||
                    0 == c_strcmp (pt_aud_strm_info->s639_dig_aud_lang2, " ") )  /* 1 space */
                {
                #if 0
                    c_uc_w2s_strcat (w2s_text + c_uc_w2s_strlen(w2s_text),
                                MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_AUD_MTS_UNK)) ;
                #endif
                }
                else
                {
                    /* max support 12 characters, if more than 12, it will only display first 9
                     * characters + "..."
                     */
                    if (c_strlen (pt_aud_strm_info->s639_dig_aud_lang2) > 12)
                    {
                        c_uc_ps_to_w2s (pt_aud_strm_info->s639_dig_aud_lang2,
                                        w2s_text + c_uc_w2s_strlen(w2s_text),
                                        12) ;  /* display first 9 characters */

                        /* "..." means there has any more informations */
                        /*remove ..., all len plus 3*/
                    }
                    else
                    {
                        c_uc_ps_to_w2s (pt_aud_strm_info->s639_dig_aud_lang2,
                                        w2s_text + c_uc_w2s_strlen(w2s_text),
                                        12) ; /* max support 12 characters */
                    }
                }
            }
            else
            {
                c_uc_w2s_strcat (w2s_text, pw2s_text) ;
            }
        }

        NAV_ASSERT (c_uc_w2s_strlen (w2s_text) <= sizeof (w2s_text)/sizeof(w2s_text[0]) -1) ;
        BANNER_CHK_FAIL ( (c_uc_w2s_strlen (w2s_text) <= sizeof (w2s_text)/sizeof(w2s_text[0]) -1) ? NAVR_OK : NAVR_FAIL) ;

        pw2s_text = w2s_text ;
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                BANNER_ITM_AUDIO_LANG, pw2s_text, 0)) ;
    }

    /* loop mask */
    if ( (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_INFO) ||
         (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_STS) )
    {
        CHAR         s_audio_fmt[32+1] = {0};

        /* reset w2s_text */
        c_memset (w2s_text, 0, sizeof(w2s_text)) ;

        if (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_INFO)
        {
            UTF16_T      w2s[128] = {0} ;

            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("SI_AUD_INFO_MASK_DIG_AUD_INFO e_aud_fmt= %d \n", pt_aud_strm_info->t_dig_aud_info.e_aud_fmt)) ;
            if (pt_aud_strm_info->t_dig_aud_info.e_aud_fmt == ASH_AUDIO_FMT_AC3  ||
                pt_aud_strm_info->t_dig_aud_info.e_aud_fmt == ASH_AUDIO_FMT_E_AC3)
            {
                HANDLE_T              h_scc = NULL_HANDLE;
                SM_COMMAND_T          at_sm_cmds[3];
                SCC_AUD_IEC_TYPE_T    e_iec_type = SCC_AUD_IEC_CFG_NONE;
                INT32                 i4_ret = NAVR_FAIL;

                /* get scc main / sub  handle */
                do{
                    /*scc component for mts operation*/
                    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
                    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
                    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
                    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
                    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
                    at_sm_cmds[2].u.ui4_data = 0;

                    if(0 != c_scc_comp_open(at_sm_cmds, &h_scc) || NULL_HANDLE == h_scc )
                        break;
                    i4_ret = c_scc_aud_get_iec_type(h_scc,&e_iec_type);
                    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n[audio type] e_iec_type = %d, i4_ret = %d\n",e_iec_type,i4_ret));
                    c_scc_comp_close(h_scc);
                }while(0);

                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), 0)) ;
                /* not show dolby atmos for 2020 custom request
                if(SCC_AUD_IEC_CFG_DDP_ATMOS == e_iec_type)
                    BANNER_LOG_ON_FAIL(_notify_to_banner_item_changed (BANNER_ITM_AUDIO_OUT, L"Audio Out",NULL_HANDLE));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""),SCC_AUD_IEC_CFG_DDP_ATMOS == e_iec_type ? h_g_banner_slider_icon_dolby_atmos: h_g_banner_slider_icon_dolby_audio)) ;
                */
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));
                pw2s_text = L"";
            }
            else
            {
                SCC_AUD_IEC_TYPE_T  e_iec_type          =   SCC_AUD_IEC_CFG_PCM;
                UTF16_T             w_audio_str[32]     =   {0};
                CHAR                s_audio_type[64]    =   {0};

                if(pt_aud_strm_info->t_dig_aud_info.e_aud_fmt == ASH_AUDIO_FMT_PCM)
                {
                    c_uc_w2s_strcat (w2s, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_AUD_MTS_STEREO)) ;
                    pw2s_text = w2s ;
                }
                else
                {
                    pw2s_text = nav_get_audio_fmt_str (pt_aud_strm_info->t_dig_aud_info.e_channels) ;

                    if(pw2s_text != NULL)
                    {
                        c_uc_w2s_to_ps(pw2s_text, s_audio_fmt, 32);

                        if(c_strncmp(s_audio_fmt, "Stereo", 6) != 0 &&
                           c_strncmp(s_audio_fmt, "Mono", 4) != 0)
                        {
                            pw2s_text = NULL;
                        }
                    }
                }
                //get audio_stream_text discribetion
                i4_ret = _banner_aud_get_audio_stream_text(w_audio_str,sizeof(w_audio_str)/sizeof(UTF16_T));
                BANNER_LOG_ON_FAIL(i4_ret);
                if(c_uc_w2s_strlen(w_audio_str) > 0)
                {
                    c_uc_w2s_to_ps(w_audio_str,s_audio_type,sizeof(s_audio_type));
                }
                //get e_iec_type
                i4_ret = _banner_aud_get_scc_audio_type_out(&e_iec_type);
                BANNER_LOG_ON_FAIL(i4_ret);
                //asigned t_audio_info
                i4_ret = c_svctx_get_audio_info(nav_get_crnt_svctx(), &t_audio_info);
                BANNER_LOG_ON_FAIL(i4_ret);
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));

                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner DOLBY_AUDIO] t_audio_info.e_aud_fmt=%d,e_iec_type=%d,s_audio_type=%s\n",t_audio_info.e_aud_fmt,e_iec_type,s_audio_type));
                if((ASH_AUDIO_FMT_AAC == t_audio_info.e_aud_fmt)&&(e_iec_type == SCC_AUD_IEC_CFG_DD)&&(c_strlen(s_audio_type)>0)&&(c_strstr(s_audio_type,"Dolby Audio")))
                {
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""),h_g_banner_slider_icon_dolby_audio)) ;
                }
                else
                {
                    if(NULL != pw2s_text)
                    {
                        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, pw2s_text, NULL_HANDLE)) ;
                        c_uc_w2s_to_ps(pw2s_text, s_audio_fmt, 32);
                        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner AUDIO_FARMAT] aud fmt= %s \n", s_audio_fmt)) ;
                    }
                }
            }
        }

        if ((pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_STS) &&
            SI_AUD_DIG_AUD_STS_NORMAL != pt_aud_strm_info->e_dig_aud_sts)
        {
            //get t_audio_info
            i4_ret = c_svctx_get_audio_info(nav_get_crnt_svctx(), &t_audio_info);
            BANNER_LOG_ON_FAIL(i4_ret);
            /* append a "space" */
            c_uc_w2s_strcat (w2s_text, L" \0") ;

            if (SI_AUD_DIG_AUD_STS_ABSENT == pt_aud_strm_info->e_dig_aud_sts && \
                t_audio_info.e_channels == ASH_CHANNELS_UNKNOWN)
            {
                /* append "No Audio" */
                c_uc_w2s_strcat (w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_AUDIO)) ;
            }
            else if (SI_AUD_DIG_AUD_STS_SCRAMBLED == pt_aud_strm_info->e_dig_aud_sts)
            {
                /* append "scramble audio" */
               // c_uc_w2s_strcat (w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_ASCRAMBLED)) ;
            }
            else if (SI_AUD_DIG_AUD_STS_NONE == pt_aud_strm_info->e_dig_aud_sts)
            {
                /* append "unknown" */
                c_uc_w2s_strcat (w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_AUD_MTS_UNK)) ;
            }

            NAV_ASSERT (c_uc_w2s_strlen (w2s_text) <= sizeof (w2s_text)/sizeof(w2s_text[0]) -1) ;
            BANNER_CHK_FAIL ( (c_uc_w2s_strlen (w2s_text) <= sizeof (w2s_text)/sizeof(w2s_text[0]) -1) ? NAVR_OK : NAVR_FAIL) ;
            pw2s_text = w2s_text ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                    BANNER_ITM_AUDIO_FARMAT, pw2s_text, NULL_HANDLE)) ;
        }
    }

    if (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_ANA_AUD_MTS)
    {
        UTF16_T      w2s[128] = {0} ;
        //CHAR         s_disp_name[32+1] = {0};
        //UINT8        ui1_input_id = 0;
        //ISL_REC_T    t_isl_rec_ex;
        CHAR         s_mts_name[32+1] = {0};
        INT16        i2_val = 0;

        a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_val);
        //a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        //a_cfg_get_input_src(s_disp_name, &ui1_input_id);
        //a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec_ex);
        c_memset(w2s, 0 , sizeof(w2s));
        banner_get_crnt_isl(&t_isl_rec);

        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("SI_AUD_INFO_MASK_ANA_AUD_MTS e_video_type = 0x%x e_aud_fmt = %d,i2_val=%d\n",
                                              t_isl_rec.t_avc_info.e_video_type,
                                              pt_aud_strm_info->t_dig_aud_info.e_aud_fmt,i2_val)) ;        
    }

    if (pt_aud_strm_info->ui4_info_mask & SI_AUD_INFO_MASK_DIG_AUD_TYPE)
    {
        if (AUD_TYPE_HEARING_IMPAIRED == pt_aud_strm_info->e_dig_aud_type)
        {
            h_icon      =       h_g_itm_img_icon_ad_ear ;
        }
        else if (
            AUD_TYPE_VISUAL_IMPAIRED  == pt_aud_strm_info->e_dig_aud_type)
        {
            h_icon      =       h_g_itm_img_icon_ad_eye ;
        }
        else
        {
            h_icon      =       NULL_HANDLE ;
        }

        e_item_idx      =       BANNER_ITM_AD_EYE ;
        pw2s_text       =       NULL ;

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                e_item_idx, pw2s_text, h_icon)) ;
    }
    /* display current playing audio format when it's non-TV source */
    UTF16_T      w2s[128] = {0} ;
    CHAR         s_mts_name[32+1] = {0};
    INT16        i2_mts_val = 0;
    ISL_REC_T    t_hdmi_isl_rec = {0};
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_mts_val);
    c_memset(w2s, 0 , sizeof(w2s));
    banner_get_crnt_isl(&t_hdmi_isl_rec);
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[%s][%d] t_hdmi_isl_rec.t_avc_info.e_video_type= %d DEV_AVC_HDMI = %d\n", __FUNCTION__, __LINE__,t_hdmi_isl_rec.t_avc_info.e_video_type,DEV_AVC_HDMI));
    if (t_hdmi_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
    {
        i4_ret = c_svctx_get_audio_info(h_svctx, &t_audio_info);
        if(SVCTXR_OK != i4_ret)
        {
            return AAUDR_INV_ARG;
        }
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("e_aud_fmt = %d i2_val = %d\n", t_audio_info.e_aud_fmt,i2_mts_val)) ;

        HANDLE_T                  h_scc = NULL_HANDLE;
        SM_COMMAND_T              at_sm_cmds[3];
        SCC_AUD_IEC_TYPE_T        e_iec_type = {0};
        INT32                     i4_ret;
        /* get scc main / sub  handle */

        /*scc component for mts operation*/
        at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
        at_sm_cmds[2].u.ui4_data = 0;

        i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc);
        if(i4_ret == MENUR_OK && h_scc != NULL_HANDLE)
        {
            i4_ret = c_scc_aud_get_iec_type(h_scc,&e_iec_type);
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n[audio type] e_iec_type = %d,i4_ret = %d\n",e_iec_type,i4_ret));
            c_scc_comp_close(h_scc);
        }

        if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_AC3 ||
            t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_OPUS)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby Audio\n"));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));
            pw2s_text = L"";
        }
        else if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_E_AC3)
        {
            if (e_iec_type == SCC_AUD_IEC_CFG_DDP_ATMOS &&
                i4_ret == MENUR_OK )
            {
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby ATMOS\n"));

                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));

            }
            else
            {
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby Audio\n"));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));
                pw2s_text = L"";
            }
        }
        else if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_AAC &&
                (e_iec_type == SCC_AUD_IEC_CFG_DD || e_iec_type == SCC_AUD_IEC_CFG_DDP))
        {
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby Audio\n"));
            //Dolby Audio-DD
            //pw2s_text = L"Dolby Audio-DD ";
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));
            pw2s_text = L"";
        }
        else
        {
            if((t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS)||
               (t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS_EXPRESS)||
               (t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS_HD))
            {
               _banner_sys_info_update_dts(BANNER_AUD_MTS, w2s);
               pw2s_text = w2s ;
            }
            else if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_PCM ||
                   i2_mts_val == SCC_AUD_MTS_STEREO)
            {
                c_uc_w2s_strcpy(w2s, L"Stereo");
               pw2s_text = w2s ;
            }
            else
            {
                pw2s_text = NULL;
                pw2s_text = nav_get_audio_fmt_str (pt_aud_strm_info->t_dig_aud_info.e_channels);
                if(NULL != pw2s_text)
                {
                    c_uc_w2s_to_ps(pw2s_text, s_mts_name, 32);
                    if(c_strncmp(s_mts_name, "Stereo", 6) != 0 &&
                       c_strncmp(s_mts_name, "Mono",   4) != 0)
                    {
                       pw2s_text = NULL;
                    }
                    else
                    {
                        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("aud mts1= %s ", s_mts_name)) ;
                    }
                }
            }
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));

            if(NULL != pw2s_text)
            {
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, pw2s_text, NULL_HANDLE)) ;
                CHAR         s_mts_name_1[32+1] = {0};
                c_uc_w2s_to_ps(pw2s_text, s_mts_name_1, 32);
                c_uc_w2s_to_ps(pw2s_text_ex, s_mts_name, 32);
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("aud mts2= %s,s_mts_name_1=%s \n", s_mts_name,s_mts_name_1));
            }
        }
    }
    banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_handle_custom_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_handle_custom_info (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    SI_CUST_INFO_1_T*           pt_custom_info = NULL ;

    WGL_HIMG_TPL_T              h_lan_status_icon = NULL_HANDLE;
    UINT8                       ui1_interface = 0;
    NW_WLAN_STATE_T             e_wlan_state;
    NET_802_11_BSS_INFO_T       t_bss_info;
    NW_DHCP_STATE_T             e_dhcp_state;
    INT16                       i2_scr_mode;

    if (!_banner_si_hldr_is_focused_win_id (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    /* check validation */
    if (!pt_si_info ||
        pt_si_info->e_category != SI_CATEGORY_CUSTOM_1)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* get custom info */
    pt_custom_info = &pt_si_info->u.t_cust_info_1 ;

    /* loop mask */

    if (pt_custom_info->ui4_info_mask & SI_CUSTOM_INFO_MASK_SCREEN_MODE)
    {
        if (!b_is_replace_hdr
            && !b_is_replace_dolby_vision
           )
        {
            /* 120hz force set screen mode to normal */
            if (a_cfg_custom_chk_freqence_120hz())
            {
                i2_scr_mode = SCC_VID_SCREEN_MODE_NORMAL;
            }
            else
            {
                i2_scr_mode = pt_custom_info->i2_scr_mode;
            }

            if (i2_pre_scr_mode != i2_scr_mode)
            {
                i2_pre_scr_mode = i2_scr_mode;
            }
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("src mode= %d \r\n",i2_scr_mode)) ;

            switch(i2_scr_mode)
            {
                case SCC_VID_SCREEN_MODE_LETTERBOX:
                    //Stretch
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_ASPECT,
                                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_STRETCH),
                                        NULL_HANDLE)) ;
                    break;
                case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
                    //Panaoramic
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_ASPECT,
                                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_PANORAMIC),
                                        NULL_HANDLE)) ;
                    break;
                case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
                    //Zoom
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_ASPECT,
                                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_ZOOM),
                                        NULL_HANDLE)) ;
                    break;
                case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
                    //Wide
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_ASPECT,
                                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_WIDE),
                                        NULL_HANDLE)) ;
                    break;
                case SCC_VID_SCREEN_MODE_NORMAL:
                    //Normal
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_ASPECT,
                                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL),
                                        NULL_HANDLE)) ;
                    break;
                default:
                    //Unknow
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                        BANNER_ITM_ASPECT, BANNER_TEXT(""), 0) );
                    break;
            }

            banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_ASPECT);
        }
    }

    if (pt_custom_info->ui4_info_mask & SI_CUSTOM_INFO_MASK_NETWORK_INFO)
    {
        BOOL      b_is_network_inited = FALSE;
        UINT8     ui1_ethernet_conneted_status = 0;

        /* check the network init status*/
        if (NWR_OK == a_get_nw_init_status())
        {
            b_is_network_inited = TRUE;
        }
        else
        {
            b_is_network_inited = FALSE;
        }

        /* get the ethernet connected status, and the flag will be set as power off*/
        a_cfg_custom_get_ethernet_connected_status(&ui1_ethernet_conneted_status);

        c_memcpy(&t_bss_info, &(pt_custom_info->t_network_info.t_bss_info), sizeof(NET_802_11_BSS_INFO_T));
        ui1_interface = pt_custom_info->t_network_info.ui1_interface_type;
        e_wlan_state = pt_custom_info->t_network_info.e_wlan_state;
        e_dhcp_state = pt_custom_info->t_network_info.e_dhcp_state;

        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("BANNER NETWORK DEBUG BEGIN ==========\n"));

        /* DBG: notify id */
        if (NW_NFY_ID_ETHERNET_UNPLUG == pt_custom_info->t_network_info.e_nfy_id)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" nw_notify_id = NW_NFY_ID_ETHERNET_UNPLUG ==========\n"));
        }
        else if (NW_NFY_ID_ETHERNET_PLUGIN == pt_custom_info->t_network_info.e_nfy_id)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("nw_notify_id = NW_NFY_ID_ETHERNET_PLUGIN ==========\n"));
        }
        else if (NW_NFY_ID_WLAN_ASSOCIATE == pt_custom_info->t_network_info.e_nfy_id)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" nw_notify_id = NW_NFY_ID_WLAN_ASSOCIATE ==========\n"));
        }
        else
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("nw_notify_id = %d ==========\n",pt_custom_info->t_network_info.e_nfy_id));
        }

        /* DBG: network interface */
        if (ui1_interface == APP_CFG_NET_INTERFACE_WIFI)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" ui1_interface = APP_CFG_NET_INTERFACE_WIFI ==========\n"));
        }
        else
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("ui1_interface = APP_CFG_NET_INTERFACE_ETH0 ==========\n"));
        }

        /* DBG: wlan state */
        if (e_wlan_state == NW_WLAN_ASSOCIATING)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" e_wlan_state = NW_WLAN_ASSOCIATING ==========\n"));
        }
        else if (e_wlan_state == NW_WLAN_ASSOCIATE)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("e_wlan_state = NW_WLAN_ASSOCIATE ==========\n"));
        }
        else
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("e_wlan_state = NW_WLAN_ASSOCIATE_FAILED ==========\n"));
        }

        /* DBG: IP state */
        if (pt_custom_info->t_network_info.b_is_ip_get)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("b_is_ip_get = TRUE ==========\n"));
        }
        else
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" b_is_ip_get = FALSE ==========\n"));
        }

        /* DBG: DHCP state */
        if (NW_DHCP_STARTING == e_dhcp_state)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("e_dhcp_state = NW_DHCP_STARTING ==========\n"));
        }
        else if (NW_DHCP_STARTED == e_dhcp_state)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" e_dhcp_state = NW_DHCP_STARTED ==========\n"));
        }
        else if (NW_DHCP_STARTED_LOCAL == e_dhcp_state)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("e_dhcp_state = NW_DHCP_STARTED_LOCAL ==========\n"));
        }
        else
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" e_dhcp_state = NW_DHCP_FAILED ==========\n"));
        }

        /* DBG: ethernet conneted status */
        if (ui1_ethernet_conneted_status == APP_CFG_NET_INTERFACE_WIFI)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" ethernet_connect_status = APP_CFG_NET_INTERFACE_WIFI ==========\n"));
        }
        else
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" ethernet_connect_status = APP_CFG_NET_INTERFACE_ETH0 ==========\n"));
        }

        /* DBG: ethernet conneted status */
        if (b_is_network_inited)
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" network_init_status = TRUE ==========\n"));
        }
        else
        {
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" network_init_status = FALSE ==========\n"));
        }

        /* DBG: WLAN bss info */
        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" t_Ssid.ui4_SsidLen = %d ==========\n",t_bss_info.t_Ssid.ui4_SsidLen));
        if(t_bss_info.t_Ssid.ui4_SsidLen > 0)
        {
           BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("t_Ssid.ui4_Ssid = %s ==========\n",t_bss_info.t_Ssid.ui1_aSsid));
        }
        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" t_bss_info.u8_wpa_status = %d ==========\n",t_bss_info.u8_wpa_status));
        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("t_bss_info.i2_Level = %d ==========\n",t_bss_info.i2_Level));

        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" BANNER NETWORK DEBUG END ==========\n"));

        if (b_is_network_inited && APP_CFG_NET_INTERFACE_ETH0 == ui1_interface)
        {
            h_lan_status_icon =  h_g_nav_banner_new_ethernet_on_img_ex;
            banner_view_update_item (
                                     BANNER_ITM_WIFI_TXT,
                                     BANNER_TEXT("Ethernet "),
                                     NULL_HANDLE,
                                     UP_TO_VIEW_AT_ONCE);
        }
        else if (NW_NFY_ID_ETHERNET_UNPLUG == pt_custom_info->t_network_info.e_nfy_id)
        {
        #ifdef APP_UPG_SUPPORT
            if (nav_updater_is_all_partition_ready())
            {
                if (e_wlan_state == NW_WLAN_ASSOCIATING)
                {
                    h_lan_status_icon =  h_g_nav_banner_new_network_wifi_error_img;
                    //h_lan_status_icon =  h_g_nav_banner_new_wifi_level_0_img;
                }
                else
                {
                    h_lan_status_icon =  h_g_nav_banner_new_ethernet_off_img;
                }
            }
            else
        #endif
            {
                if (ui1_ethernet_conneted_status == APP_CFG_NET_INTERFACE_WIFI)
                {
                    h_lan_status_icon =  h_g_nav_banner_new_network_wifi_error_img;
                    //h_lan_status_icon = h_g_nav_banner_new_wifi_level_0_img;
                }
                else
                {
                    h_lan_status_icon = h_g_nav_banner_new_ethernet_reconnect_img;
                }
            }
            banner_view_update_item (
                                BANNER_ITM_WIFI_TXT,
                                BANNER_TEXT(""),
                                NULL_HANDLE,
                                UP_TO_VIEW_AT_ONCE);
        }
        else if (NW_NFY_ID_ETHERNET_PLUGIN == pt_custom_info->t_network_info.e_nfy_id)
        {
            if (b_is_network_inited)
            {
                h_lan_status_icon =  h_g_nav_banner_new_ethernet_reconnect_img;
            }
            else
            {
                if (ui1_ethernet_conneted_status == APP_CFG_NET_INTERFACE_WIFI)
                {
                    h_lan_status_icon =  h_g_nav_banner_new_network_wifi_error_img;
                    //h_lan_status_icon = h_g_nav_banner_new_wifi_level_0_img;
                }
                else
                {
                    h_lan_status_icon = h_g_nav_banner_new_ethernet_reconnect_img;
                }
            }
        }
        else
        {
            if(ui1_interface == APP_CFG_NET_INTERFACE_WIFI) /* WIFI*/
            {
                if (e_wlan_state == NW_WLAN_ASSOCIATE)  /* has associate with wifi*/
                {
                    if ((t_bss_info.t_Ssid.ui4_SsidLen <= 0)
                        ||(t_bss_info.u8_wpa_status != (UINT8)WLAN_WPA_COMPLETED))
                    {
                        h_lan_status_icon =  h_g_nav_banner_new_ethernet_off_img;
                    }
                    else if (pt_custom_info->t_network_info.b_is_ip_get)
                    {
                        if (0 == t_bss_info.i2_Level)
                        {
                            t_bss_info.i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();
                        }

                        if((UINT16)t_bss_info.i2_Level > 80)
                        {
                            h_lan_status_icon = at_img_signal_icon1[4];
                        }
                        else if(60 <= (UINT16)t_bss_info.i2_Level)
                        {
                            h_lan_status_icon = at_img_signal_icon1[3];
                        }
                        else if(40 <= (UINT16)t_bss_info.i2_Level)
                        {
                            h_lan_status_icon = at_img_signal_icon1[2];
                        }
                        else if(20 <= (UINT16)t_bss_info.i2_Level)
                        {
                            h_lan_status_icon = at_img_signal_icon1[1];
                        }
                        else
                        {
                            h_lan_status_icon = at_img_signal_icon1[0];
                            //h_wlan_status_icon = at_img_signal_icon1[(((UINT16)(t_bss_info.i2_Level -1)) /30)%5];
                        }

                        UINT16  ws_ssid[128] = {0};
                        c_uc_ps_to_w2s(t_bss_info.t_Ssid.ui1_aSsid,ws_ssid,128);
                        banner_view_update_item (
                                BANNER_ITM_WIFI_TXT,
                                ws_ssid,
                                NULL_HANDLE,
                                UP_TO_VIEW_AT_ONCE);
                    }
                    else
                    {
                        if (NW_DHCP_STARTING == e_dhcp_state)
                        {
                            h_lan_status_icon =  h_g_nav_banner_new_network_wifi_error_img;
                            //h_lan_status_icon =  h_g_nav_banner_new_wifi_level_0_img;//Cedric 0410
                        }
                        else
                        {
                            h_lan_status_icon =  h_g_nav_banner_new_ethernet_off_img;//Cedric 0410
                        }
                    }
                }
                else if (e_wlan_state == NW_WLAN_ASSOCIATING)
                {
                    h_lan_status_icon =  h_g_nav_banner_new_network_wifi_error_img;
                    //h_lan_status_icon =  h_g_nav_banner_new_wifi_level_0_img;//Cedric 0410
                }
                else    /* not associate with wifi*/
                {
                    h_lan_status_icon =  h_g_nav_banner_new_ethernet_off_img;//Cedric 0410
                }
            }
            else    /* WIRED */
            {
                if (pt_custom_info->t_network_info.b_is_ip_get)
                {
                    h_lan_status_icon = h_g_nav_banner_new_ethernet_on_img_ex;
                    banner_view_update_item (
                                BANNER_ITM_WIFI_TXT,
                                BANNER_TEXT("Ethernet "),
                                NULL_HANDLE,
                                UP_TO_VIEW_AT_ONCE);
                }
                else
                {
                    if (NW_DHCP_STARTING == e_dhcp_state)
                    {
                        h_lan_status_icon =  h_g_nav_banner_new_ethernet_reconnect_img;//Cedric 0412
                    }
                    else
                    {
                        h_lan_status_icon =  h_g_nav_banner_new_ethernet_off_img;
                    }
                }
            }
        }

        if (h_g_nav_banner_new_network_wifi_error_img == h_lan_status_icon)
        {
            if (FALSE == _banner_is_need_reconnect_ssid())
            {
                h_lan_status_icon = h_g_nav_banner_new_ethernet_off_img;
            }
        }
        else if(h_g_nav_banner_new_ethernet_reconnect_img == h_lan_status_icon &&
            ui1_interface == APP_CFG_NET_INTERFACE_WIFI)
        {
            /* as per current network reconnect soluton , if NW_WLAN_PLUG_STOP == e_wlan_state,
               can NOT be auto a_nw_chg_network_interface (NW_NET_INTERFACE_WIFI),
               so just set connection failed. */
        #if 0
            if (FALSE == _banner_is_need_reconnect_ssid())
            {
                h_lan_status_icon = h_g_nav_banner_new_ethernet_off_img;
            }
            else
            {
                h_lan_status_icon = h_g_nav_banner_new_wifi_level_0_img;
            }
        #else
            h_lan_status_icon = h_g_nav_banner_new_ethernet_off_img;
        #endif
        }

        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                BANNER_ITM_WIFI_ICON, NULL,
                                h_lan_status_icon)) ;
    }

    return NAVR_OK ;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _banner_sys_info_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_sys_info_handler (
    SI_INFO_CTRL_T              e_info_ctrl ,
    TV_WIN_ID_T                 e_tv_win_id ,
    SI_SET_INFO_T*              pt_si_info ,
    VOID*                       pv_tag
    )
{
    /* check validate */
    if (!pt_si_info)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("receive notification ...unset = %d, category = \"%s\", mask=0x%x\n",
                                (SI_INFO_CTRL_UNSET == e_info_ctrl) ? 1 : 0 ,
                                GET_SI_NOTIFY_CATEGORY(pt_si_info->e_category),
                                pt_si_info->u.t_ci_info.ui4_info_mask));

    if (nav_is_channel_scan_active ()                           /* scanning */
        &&
        (INP_SRC_TYPE_TV == nav_get_src_type (e_tv_win_id)))    /* is tv source */
    {
        /* do not update banenr state or items during scanning */
        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" in scan processing,ignore the notifications \n "));
        return NAVR_OK ;
    }

    /* reset related items */
    if (SI_INFO_CTRL_UNSET == e_info_ctrl)
    {
        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" reset related items  \n" ));
        return NAVR_OK; //(_banner_handle_unset_notify (e_tv_win_id, pt_si_info, pv_tag)) ;
    }

    /* as sys info module is one of navigator's component, we need not change the thread */

    /* switch to sub-handler */
    switch (pt_si_info->e_category)
    {
    case SI_CATEGORY_3D_MODE_INFO :
        BANNER_CHK_FAIL (_banner_handle_3d_info (e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag)) ;
        break ;
    case SI_CATEGORY_TUNING_INFO :
        BANNER_CHK_FAIL (_banner_handle_tuning_info (e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag)) ;
        break ;
    case SI_CATEGORY_EVENT_INFO :
        BANNER_CHK_FAIL (_banner_handle_event_info (e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag)) ;
        break ;
    case SI_CATEGORY_CH_NUM_INFO :
        BANNER_CHK_FAIL (_banner_handle_ch_num_info (e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag)) ;
        break ;
    case SI_CATEGORY_DATE_TIME_INFO :
        /* FIXME_MIN */
        break ;
#if 0
    case SI_CATEGORY_CC_INFO :
         BANNER_LOG(_BANNER_LOG_TYPE_MESSAGE,(" SI_CATEGORY_CC_INFO\n"));
        BANNER_CHK_FAIL (_banner_handle_cc_info (
                                e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag)) ;
        break ;
#endif
    case SI_CATEGORY_AUD_STRM_INFO :
        BANNER_CHK_FAIL (_banner_handle_aud_strm_info (e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag)) ;
        break ;
    case SI_CATEGORY_CUSTOM_1 :
        BANNER_CHK_FAIL (_banner_handle_custom_info (e_info_ctrl, e_tv_win_id, pt_si_info, pv_tag)) ;
        break;
    default :
        /* Do nothing */
        break ;
    }

    return NAVR_OK ;
}

#if 0
static INT32 _banner_sys_info_dv_nfy_func(UINT16 ui2_nfy_id,
                                            VOID* pv_tag,
                                            ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32          i4_ret = NAVR_OK;
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE e_rec_id = ICL_GET_REC(pt_notify_data->pe_id[0]);


    if (e_grp_id != ICL_GRPID_DOLBY_VISION_STATUS)
    {
        return NAVR_OK;
    }
    if(e_rec_id != ICL_RECID_DOLBY_VISION_STATUS)
    {
        return NAVR_OK;
    }

    if(a_icl_custom_get_dolby_vision_status() == 1)
    {
        banner_show_siderbar_logo(BANNER_HDR_DOLBY_VISION);
    }

    return i4_ret;
}
#endif

#ifdef APP_C4TV_SUPPORT

static VOID _c4tv_apron_nfy_cast_tv_name_fct(C4TV_APRON_CAST_STATE    e_cast_state,
                                             VOID*                    pv_param1,
                                             VOID*                    pv_param2,
                                             VOID*                    pv_param3)
{
    C4TV_APRON_CAST_STATUS *    pt_cast_status = (C4TV_APRON_CAST_STATUS *)pv_param2;
    UTF16_T                     w2s_tv_cast_name[128+1] = {0};
    CHAR                        s_cast_name[128+1]={0};
    UINT32                      ui4_cast_name_len = 128+1;

    if(C4TV_APRON_CAST_STATE_ForcedUpdate == e_cast_state)
    {
        DBG_LOG_PRINT(("%s,%d [don't need to update cast name when ForcedUpdate ] \r\n",__FUNCTION__, __LINE__ ));
        return;
    }

    if((pt_cast_status != NULL) && ((pt_cast_status->ps_cast_name != NULL && strlen(pt_cast_status->ps_cast_name) >= 0) ||
        ( 0 == a_cfg_custom_get_cast_name(s_cast_name, &ui4_cast_name_len) && strlen(s_cast_name) > 0)))
    {
        if(pt_cast_status->ps_cast_name)
        {
            c_memcpy(s_cast_name,pt_cast_status->ps_cast_name,strlen(pt_cast_status->ps_cast_name));
        }
        BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,(" get tv name \"%s\"\n ",s_cast_name));
        c_uc_ps_to_w2s(s_cast_name, w2s_tv_cast_name, sizeof(w2s_tv_cast_name));
        banner_view_update_item (BANNER_ITM_TV_NAME,w2s_tv_cast_name,NULL_HANDLE, UP_TO_VIEW_AT_ONCE);
    }
}

#endif

/*-----------------------------------------------------------------------------
 * Name
 *      banner_sys_info_handler_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_sys_info_handler_init (
    banner_state_item_update_listener   pf_reporter ,
    UINT16*                             pui2_si_listener_id
    )
{
    if (!pui2_si_listener_id)
    {
        return NAVR_INV_ARG ;
    }

    pf_g_reporter = pf_reporter ;

    /* register all items */
    BANNER_CHK_FAIL (_register_items ()) ;

    /* register a listener to sys info moudle */
    BANNER_CHK_FAIL (a_si_listener_register (
                                        _banner_sys_info_handler,
                                        NULL ,
                                        pui2_si_listener_id)) ;
#ifdef APP_C4TV_SUPPORT
    a_c4tv_apron_register_nfy_cb(_c4tv_apron_nfy_cast_tv_name_fct);
#endif

/*  //acfg reg SCC nfy,now use banner_cust_evt_handle_chg_hdr(...),so don`t use it any more
    a_icl_notify_reg(ICL_GRPID_DOLBY_VISION_STATUS,
                          ICL_RECID_DOLBY_VISION_STATUS,
                          NULL,
                          NULL,
                          _banner_sys_info_dv_nfy_func,
                          &ui2_dolby_vision_nfy_idx);
*/


    //listen a_cfg_set_hdr_type->a_icl_set_hdr_type_status
    BANNER_CHK_FAIL(a_icl_notify_reg(ICL_GRPID_HDR_TYPE_STATUS,
                     ICL_PRIORITY_DEFAULT,
                     NULL,
                     NULL,
                     _banner_sys_info_hdr_nfy_func,
                     &ui2_hdr_icl_nfy_idx));

    //listen av info when vitrual src(mi_mm display)
    BANNER_CHK_FAIL(a_cfg_notify_reg(IDX_INPUT_MAIN,
                              NULL,
                              _nav_banner_mm_update_cfg_change_cb,
                              &ui2_mm_update_cfg_nfy_idx));

    return NAVR_OK ;
}

INT32 banner_update_scr_mode(VOID)
{
    INT16           i2_scr_mode = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),
                          &i2_scr_mode);

    /* 120hz force set screen mode to normal */
    if (a_cfg_custom_chk_freqence_120hz())
    {
        i2_scr_mode = SCC_VID_SCREEN_MODE_NORMAL;
    }

    if (i2_pre_scr_mode == i2_scr_mode)
    {
        return 0;
    }

    i2_pre_scr_mode = i2_scr_mode;

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("src mode update= %d \r\n", i2_scr_mode)) ;

    switch(i2_scr_mode)
    {
    case SCC_VID_SCREEN_MODE_LETTERBOX:
        //Stretch
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                        BANNER_ITM_ASPECT,
                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_STRETCH),
                        NULL_HANDLE)) ;
        break;
    case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
        //Panaoramic
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                        BANNER_ITM_ASPECT,
                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_PANORAMIC),
                        NULL_HANDLE)) ;
        break;
    case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
        //Zoom
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                        BANNER_ITM_ASPECT,
                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_ZOOM),
                        NULL_HANDLE)) ;
        break;
    case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
        //Wide
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                        BANNER_ITM_ASPECT,
                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_WIDE),
                        NULL_HANDLE)) ;
        break;
    case SCC_VID_SCREEN_MODE_NORMAL:
        //Normal
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                        BANNER_ITM_ASPECT,
                        MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL),
                        NULL_HANDLE)) ;
        break;
    default:
        //Unknow
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (
                                    BANNER_ITM_ASPECT, BANNER_TEXT(""), 0) );
        break;
    }

    banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_ASPECT);
    return 0;
}


INT32 banner_get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32           i4_ret      =   NAVR_FAIL;
    TV_WIN_ID_T     t_win_id    =   TV_WIN_ID_MAIN;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    BANNER_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,
                                        pt_isl_rec);
    BANNER_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

INT32 banner_cust_evt_handle_chg_hdr(
                UINT32    e_update_reason,
                UINT32    data
                )
{
#ifdef NEVER
    DBG_LOG_PRINT(("[banner hdr] acfg_custom_update_all e_update_reason:%d pv_data:%d\n",\
                e_update_reason,data));

    if(e_update_reason != SCC_VID_DOVI_COND_CHG)
        return NAVR_NO_ACTION;

    HANDLE_T       h_icon        =  NULL_HANDLE;
    UTF16_T*       pw2s_text     =  MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL);

#if 0
    CHAR     s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    HANDLE_T h_scc_comp = NULL_HANDLE;
    INT32    i4_ret;

    /* Get SCC handle by display name. */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    BANNER_CHK_FAIL(i4_ret);
    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                 h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

    SCC_VID_HDR_TYPE_T t_hdr_type;
    i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
    BANNER_LOG_ON_FAIL(i4_ret);


    SCC_DOVI_INFO_T t_dolby_vision;
    c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));
    i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
    BANNER_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("[banner hdr] acfg_custom_update_all t_hdr_type:%d t_dolby_vision:%d\n",\
            t_hdr_type,t_dolby_vision));
#endif

    SCC_VID_HDR_TYPE_T t_hdr_type = a_cfg_get_hdr_type();

    if(data == 1 &&
        t_hdr_type == SCC_VID_PQ_DOVI)
    {
        banner_show_siderbar_logo(BANNER_HDR_DOLBY_VISION);
        t_sidebar_status.hdr_type = SCC_VID_PQ_DOVI;
        h_icon = h_g_banner_slider_icon_dolby_vision;
        pw2s_text = L"";
    }
    else if (t_hdr_type == SCC_VID_PQ_HDR10PLUS)
    {
        banner_show_siderbar_logo(BANNER_HDR_HDR10_PLUS);
        t_sidebar_status.hdr_type = SCC_VID_PQ_HDR10PLUS;
        pw2s_text = L"HDR10+";
    }
    else if (t_hdr_type == SCC_VID_PQ_HDR10)
    {
        banner_show_siderbar_logo(BANNER_HDR_HDR10);
        t_sidebar_status.hdr_type = SCC_VID_PQ_HDR10;
        pw2s_text = L"HDR10";
    }
    else if (t_hdr_type == SCC_VID_PQ_HLG)
    {
        banner_show_siderbar_logo(BANNER_HDR_HLG);
        t_sidebar_status.hdr_type = SCC_VID_PQ_HLG;
        pw2s_text = L"HLG";
    }
    else
    {
        banner_hide_sidebar();
        t_sidebar_status.hdr_type = SCC_VID_PQ_SDR;
    }

    if(t_sidebar_status.last_hdr_type != t_sidebar_status.hdr_type)
    {
        t_sidebar_status.last_hdr_type = t_sidebar_status.hdr_type;

        BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_DOLBY_VISION ,NULL,h_icon,!UP_TO_VIEW_AT_ONCE)) ;
        banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_ASPECT);
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_ASPECT, pw2s_text, NULL_HANDLE)) ;
    }
#endif /* NEVER */

    return NAVR_OK;

}


BOOL banner_cust_set_sidebar_showing(BOOL show_flag)
{
    t_sidebar_status.b_showing = show_flag;
    return t_sidebar_status.b_showing;
}




#ifdef APP_TTS_SUPPORT
static INT32 _banner_sys_w2s_ch_r(
            UTF16_T *pt_src_w2s,
            UTF16_T *pt_dst_w2s,
            SIZE_T t_dst_size,
            CHAR a,
            CHAR *b
            )
{
    SIZE_T t_sz;
    CHAR  ps_src[64] = {0};
    CHAR  ps_dst[128] = {0};

    c_uc_w2s_to_ps(pt_src_w2s, ps_src, sizeof(ps_src)-1);

    CHAR *p_str = ps_src;
    CHAR *p_next;
    while ((p_str = c_strtok(p_str, &a, &p_next, &t_sz)) != NULL)
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
#endif


VOID banner_sys_info_reset_mm_update_info(BOOL b_update)
{

    t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_EX_COUNT;
    c_memset(t_banner_mm_update_status.mm_text_res,0,sizeof(t_banner_mm_update_status.mm_text_res));

    if(b_update && b_banner_mm_info_updated)
    {
        BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
        BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_AUDIO_OUT, BANNER_TEXT(""), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE));
        BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE));

        BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_RESOLUTION_TXT ,BANNER_TEXT(""), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE));
    }

    b_banner_mm_info_updated = FALSE;
}

//hdr would be notify to ap in special flow(scc > acfg > icl > app),do not need always update in mi_mm
INT32 banner_sys_info_update_hdr(VOID)
{
    UTF16_T*        pw2s_text     = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL);
    HANDLE_T        h_icon        = NULL_HANDLE;
    INT16           i2_scr_mode     = 0;
    TV_WIN_ID_T     e_tv_win_id     = TV_WIN_ID_MAIN;

    SCC_VID_HDR_TYPE_T t_hdr_type = a_cfg_get_hdr_type();
    //if (t_dolby_vision.ui1_is_doviHDR != 0 && t_hdr_type == SCC_VID_PQ_DOVI)
    if (t_hdr_type == SCC_VID_PQ_DOVI)
    {
        b_is_replace_dolby_vision = TRUE;

        h_icon = h_g_banner_slider_icon_dolby_vision;
        pw2s_text = L"";
        t_sidebar_status.hdr_type = SCC_VID_PQ_DOVI;
    }
    else if (t_hdr_type == SCC_VID_PQ_HDR10PLUS)
    {
        b_is_replace_hdr = TRUE;
        pw2s_text = L"HDR10+";
        t_sidebar_status.hdr_type = SCC_VID_PQ_HDR10PLUS;
    }
    else if (t_hdr_type == SCC_VID_PQ_HDR10)
    {
        b_is_replace_hdr = TRUE;
        //pw2s_text = L"HDR10";
        h_icon = h_g_banner_slider_icon_hdr10;
        pw2s_text = L"";
        t_sidebar_status.hdr_type = SCC_VID_PQ_HDR10;
    }
    else if (t_hdr_type == SCC_VID_PQ_HLG)
    {
        b_is_replace_hdr = TRUE;
        //pw2s_text = L"HLG";
        h_icon = h_g_banner_slider_icon_hlg;
        pw2s_text = L"";
        t_sidebar_status.hdr_type = SCC_VID_PQ_HLG;
    }
    else
    {
        b_is_replace_hdr = FALSE;
        b_is_replace_dolby_vision = FALSE;
        t_sidebar_status.hdr_type = SCC_VID_PQ_SDR;

        nav_get_focus_id(&e_tv_win_id);
        a_cfg_av_get (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),&i2_scr_mode);
        switch(i2_scr_mode)
        {
                case SCC_VID_SCREEN_MODE_LETTERBOX:
                    //Stretch
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_STRETCH);
                    break;
                case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
                    //Panaoramic
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_PANORAMIC);
                    break;
                case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
                    //Zoom
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_ZOOM);
                    break;
                case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
                    //Wide
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_WIDE);
                    break;
                case SCC_VID_SCREEN_MODE_NORMAL:
                    //Normal
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL);

                    break;
                default:
                    //Unknow
                    pw2s_text = L"";

        }
    }

    //if(t_sidebar_status.last_hdr_type != t_sidebar_status.hdr_type)
    {
        t_sidebar_status.last_hdr_type = t_sidebar_status.hdr_type;

        BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_DOLBY_VISION ,NULL,h_icon,!UP_TO_VIEW_AT_ONCE)) ;
        banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_ASPECT);
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_ASPECT, pw2s_text, NULL_HANDLE)) ;
    }

    return NAVR_OK;
}


INT32 banner_sys_info_update_aud(ACFG_MI_MM_INFO_T t_mi_mm_info_t)
{
    INT32           i4_ret;
    UTF16_T*        pw2s_text     = NULL_HANDLE ;
    UTF16_T         w2s_text[64]  = {0} ;
    SCC_AUD_IEC_TYPE_T  e_iec_type          =   SCC_AUD_IEC_CFG_PCM;
    INT16 i2_val = 0;

    BOOL b_connected_headphones = FALSE;
    char bt_mac[18] = {0};

    if( _json_bt_db_get_mac( BD_ARR_TYPE_CONNECTED, NULL, bt_mac ) == MENUR_OK )
        b_connected_headphones = TRUE;

    //BANNER_LOG_ON_FAIL(_notify_to_banner_item_changed (BANNER_ITM_AUDIO_OUT, BANNER_TEXT(""),NULL_HANDLE));
    //update audio type
    i4_ret = _banner_aud_get_scc_audio_type_out(&e_iec_type);
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_val);
    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] scc:0x%x,eAudioCodec:0x%x i2_val:%d t_banner_mm_update_status.mm_audio_info:%d\n",\
        e_iec_type,t_mi_mm_info_t.eAudioCodec,i2_val,t_banner_mm_update_status.mm_audio_info));
    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[+++] {%s %s() %d}. @@go  t_mi_mm_info_t.eAudioCodec = %d,i2_val = %d\n",__FILE__, __FUNCTION__, __LINE__,t_mi_mm_info_t.eAudioCodec,i2_val));

    if(E_MI_MM_AUDIO_CODEC_TYPE_AC3 == t_mi_mm_info_t.eAudioCodec|| E_MI_MM_AUDIO_CODEC_TYPE_AC3P == t_mi_mm_info_t.eAudioCodec)
    {
        #if 0 // 2021: Remove Atmos
        if(SCC_AUD_IEC_CFG_DDP_ATMOS == e_iec_type)
        {
            if(t_banner_mm_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD_ATMOS || b_connected_headphones_old_status != b_connected_headphones)
            {
                #if 0 // Dolby Atmos not show logo and any atmos text on banner
                pw2s_text = L"Dolby Atmos";
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, pw2s_text, NULL_HANDLE)) ;
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
                #else
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));

                if( b_connected_headphones == TRUE )
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
                else
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));
                #endif

                banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
                t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD_ATMOS;
                BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
            }
        }
        else
        #endif
        {
            if(t_banner_mm_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD || b_connected_headphones_old_status != b_connected_headphones )
            {
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));

                if( b_connected_headphones == TRUE )
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
                else
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));

                banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
                t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD;
                BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
            }
        }
    }
    else if((E_MI_MM_AUDIO_CODEC_TYPE_AAC == t_mi_mm_info_t.eAudioCodec) &&
        (e_iec_type == SCC_AUD_IEC_CFG_DD || e_iec_type == SCC_AUD_IEC_CFG_DDP))
    {
        if(t_banner_mm_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD || b_connected_headphones_old_status != b_connected_headphones )
        {
            //Dolby Audio-DD
            //pw2s_text = L"Dolby Audio-DD ";
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));

            if( b_connected_headphones == TRUE )
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
            else
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));

            banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
            t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD;
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
        }
    }
    else if(E_MI_MM_AUDIO_CODEC_TYPE_DTS        == t_mi_mm_info_t.eAudioCodec||
            E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD     == t_mi_mm_info_t.eAudioCodec||
            E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD_HRA == t_mi_mm_info_t.eAudioCodec||
            E_MI_MM_AUDIO_CODEC_TYPE_DTS_LBR    == t_mi_mm_info_t.eAudioCodec||
            E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD_MA  == t_mi_mm_info_t.eAudioCodec)
   {
#if 1 // mapping to system info audio in
        _banner_sys_info_update_dts(BANNER_AUD_VIRTUAL_INPUT, w2s_text);
#else
        if(t_banner_mm_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD_DTS)
        {
            pw2s_text = L"DTS";
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, pw2s_text, NULL_HANDLE)) ;

            t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD_DTS;
            banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
        }
   }
#if 0 //it just for show DTS
   else if(E_MI_MM_AUDIO_CODEC_TYPE_DTS_LBR    == t_mi_mm_info_t.eAudioCodec)
   {
        pw2s_text = L"DTS Express";
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, pw2s_text, NULL_HANDLE)) ;
   }
   else if(E_MI_MM_AUDIO_CODEC_TYPE_DTS_HD_MA  == t_mi_mm_info_t.eAudioCodec)
   {
        pw2s_text = L"DTS-HD MA";
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, pw2s_text, NULL_HANDLE)) ;
   }
#endif
#endif
    }
    else if (i2_val == SCC_AUD_MTS_MONO)
    {
        if(t_banner_mm_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_MONO)
        {
            c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_MONO));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));

            if( b_connected_headphones == TRUE )
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
            else
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

            t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_MONO;
            banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
        }
    }
    else if (i2_val == SCC_AUD_MTS_STEREO)
    {
        if(t_banner_mm_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_STEREO || b_connected_headphones_old_status != b_connected_headphones )
        {
            c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_STEREO)) ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));

            if( b_connected_headphones == TRUE )
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
            else
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

            t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_STEREO;
            banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
        }
    }
    else if (i2_val == SCC_AUD_MTS_SUB_LANG)
    {
        if(t_banner_mm_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_SAP || b_connected_headphones_old_status != b_connected_headphones)
        {
            c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_SAP)) ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));

            if( b_connected_headphones == TRUE )
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
            else
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

            t_banner_mm_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_SAP;
            banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
        }
    }

    b_connected_headphones_old_status = b_connected_headphones;

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner aud info] %d aud_type:%d\n",__LINE__,t_banner_mm_update_status.mm_audio_info));

    return NAVR_OK;

}


INT32 banner_sys_info_update_res(ACFG_MI_MM_INFO_T t_mi_mm_info_t,BOOL b_interlace)
{
    UTF16_T             w2s_text[32]            = {0} ;
    CHAR                sz_tmp[32]              = {0} ;
    UINT32              ui4_video_height        = 0;

    if(t_mi_mm_info_t.MI_U32_MovieWidth != 0 && t_mi_mm_info_t.MI_U32_MovieHeight != 0)
    {
        //update resolution
        sprintf(sz_tmp,"%d X %d",t_mi_mm_info_t.MI_U32_MovieWidth,t_mi_mm_info_t.MI_U32_MovieHeight);
        //c_svctx_get_well_defined_video_heigh(t_mi_mm_info_t.MI_U32_MovieHeight, &ui4_video_height);
        ui4_video_height = t_mi_mm_info_t.MI_U32_MovieHeight;
        //2160p
        if(ui4_video_height > VIDEO_HEIGHT_1440)
        {
            c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_2160P));
        }
		//1440p
		else if(ui4_video_height > VIDEO_HEIGHT_1080)
        {
            c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_1440P));
        }
        //1080i,1080p
        else if(ui4_video_height > VIDEO_HEIGHT_720)
        {
            if(b_interlace)
            {
                c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_1080I));
            }
            else
            {
                c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_1080P));
            }
        }
        //720p
        else if(ui4_video_height > VIDEO_HEIGHT_480)
        {
            if(b_interlace)
            {
                c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_EMPTY));

            }
            else
            {
                c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_720P));
            }
        }
        //480i,480p
        else
        {
            if(b_interlace)
            {
                c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_480I));
            }
            else
            {
                c_uc_w2s_strcpy(w2s_text, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_RESOLUTION_480P));
            }

        }

        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner res change] %s %d timing= (%d,%d)b_interlace=%d\r\n",
                __FUNCTION__,__LINE__,t_mi_mm_info_t.MI_U32_MovieWidth,t_mi_mm_info_t.MI_U32_MovieHeight,b_interlace));


        char tmp_timing[128] = {0};
        c_uc_w2s_to_ps(w2s_text,tmp_timing,sizeof(tmp_timing));

        if(c_strcmp(t_banner_mm_update_status.mm_text_res,tmp_timing))
        {
            BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_RESOLUTION_TXT ,w2s_text,NULL_HANDLE,UP_TO_VIEW_AT_ONCE));

            c_strcpy(t_banner_mm_update_status.mm_text_res,tmp_timing);
        }

        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner res change] %d timing:%s t_banner_mm_update_status.mm_text_res:%s \n",
            __LINE__,tmp_timing,t_banner_mm_update_status.mm_text_res));

    }

    return NAVR_OK;
}


INT32 banner_mm_try(VOID)
{
    //UTF16_T*        pw2s_text     = NULL_HANDLE ;
    ACFG_MI_MM_INFO_T   t_mi_mm_info_t          = {0};
    ISL_REC_T           t_isl_rec               = {0};
    BOOL                b_interlace             = FALSE;
    INT32               i4_ret                  = NAVR_FAIL;
	static BOOL 		b_play_status = FALSE;
    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] banner_mm_try \n"));

    nav_get_isl_rec (TV_WIN_ID_MAIN, &t_isl_rec);
    if(t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL)
    {
        return NAVR_OK;
    }

    i4_ret = a_cfg_mi_mm_querry_ex(&t_mi_mm_info_t,&b_interlace);
    if(APP_CFGR_OK == i4_ret)
    {
        //update resolution
        banner_sys_info_update_res(t_mi_mm_info_t,b_interlace);

        //update audio type
        banner_sys_info_update_aud(t_mi_mm_info_t);

        b_banner_mm_info_updated = TRUE;
		if(!b_play_status)
		{
			b_play_status = TRUE;
			DBG_LOG_PRINT(("%s_%d set 3rd play status %d \n",__FUNCTION__,__LINE__,b_play_status));
			a_icl_set_3rd_play_status(1);
		}
    }
    else if(APP_CFGR_NO_ACTION == i4_ret)
    {
        //if in vitrual src,but not palying anything or in changing,need clean av items
        if(b_play_status)
		{
			b_play_status = FALSE;
			DBG_LOG_PRINT(("%s_%d set 3rd play status %d \n",__FUNCTION__,__LINE__,b_play_status));
			a_icl_set_3rd_play_status(0);
		}
        banner_sys_info_reset_mm_update_info(TRUE);
    }
    else
    {
    	if(b_play_status)
		{
			b_play_status = FALSE;
			DBG_LOG_PRINT(("%s_%d set 3rd play status %d \n",__FUNCTION__,__LINE__,b_play_status));
			a_icl_set_3rd_play_status(0);
		}
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


BOOL banner_check_mi_mm_playing(VOID)
{
    ACFG_MI_MM_INFO_T     t_mi_mm_info;
    INT32                 i4_ret     = 0;
    ISL_REC_T             t_isl_rec  = {0};

    nav_get_isl_rec (TV_WIN_ID_MAIN, &t_isl_rec);
    if(t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL)
    {
        return FALSE;
    }

    c_memset(&t_mi_mm_info, 0, sizeof(ACFG_MI_MM_INFO_T));
    i4_ret  = a_cfg_mi_mm_querry(&t_mi_mm_info);
    if(i4_ret == APP_CFGR_OK)
    {
        if(t_mi_mm_info.MI_U32_MovieHeight != 0 && t_mi_mm_info.MI_U32_MovieWidth != 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}


static INT32 _banner_sys_info_hdr_nfy_func(UINT16 ui2_nfy_id,
                                            VOID* pv_tag,
                                            ICL_NOTIFY_DATA_T* pt_notify_data)
{
    //CHAR        s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    //HANDLE_T    h_scc_comp = NULL_HANDLE;
    //INT32       i4_ret;
    HANDLE_T    h_icon        =  NULL_HANDLE;
    UTF16_T*    pw2s_text     =  MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL);
    //UTF16_T     w2s_alias[25] = {0};
    //CHAR        w2s_alias_name[50] = {0};
    //ISL_REC_T   t_isl_rec;
    INT16           i2_scr_mode     = 0;
    TV_WIN_ID_T     e_tv_win_id     = TV_WIN_ID_MAIN;

#if 0
    /* Get SCC handle by display name. */
    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    BANNER_CHK_FAIL(i4_ret);
    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                 h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

    SCC_VID_HDR_TYPE_T t_hdr_type;
    i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
    BANNER_LOG_ON_FAIL(i4_ret);


    SCC_DOVI_INFO_T t_dolby_vision;
    c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));
    i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
    BANNER_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("[banner icl hdr] acfg_custom_update_all t_hdr_type:%d t_dolby_vision:%d\n",\
                t_hdr_type,t_dolby_vision));
#endif

    SCC_VID_HDR_TYPE_T t_hdr_type = a_cfg_get_hdr_type();

    if(t_hdr_type == SCC_VID_PQ_DOVI)
    {
        banner_show_siderbar_logo(BANNER_LOGO_HDR_DOLBY_VISION);
        t_sidebar_status.hdr_type = SCC_VID_PQ_DOVI;
        h_icon = h_g_banner_slider_icon_dolby_vision;
        pw2s_text = L"";
        b_is_replace_dolby_vision = TRUE;
    }
    else if (t_hdr_type == SCC_VID_PQ_HDR10PLUS)
    {
        banner_show_siderbar_logo(BANNER_LOGO_HDR_HDR10_PLUS);
        t_sidebar_status.hdr_type = SCC_VID_PQ_HDR10PLUS;
        pw2s_text = L"HDR10+";
        b_is_replace_hdr = TRUE;
    }
    else if (t_hdr_type == SCC_VID_PQ_HDR10)
    {
        banner_show_siderbar_logo(BANNER_LOGO_HDR_HDR10);
        t_sidebar_status.hdr_type = SCC_VID_PQ_HDR10;
        //pw2s_text = L"HDR10";
        h_icon = h_g_banner_slider_icon_hdr10;
        pw2s_text = L"";
        b_is_replace_hdr = TRUE;
    }
    else if (t_hdr_type == SCC_VID_PQ_HLG)
    {
        banner_show_siderbar_logo(BANNER_LOGO_HDR_HLG);
        t_sidebar_status.hdr_type = SCC_VID_PQ_HLG;
        //pw2s_text = L"HLG";
        h_icon = h_g_banner_slider_icon_hlg;
        pw2s_text = L"";
        b_is_replace_hdr = TRUE;
    }
    else
    {
        b_is_replace_hdr = FALSE;
        b_is_replace_dolby_vision = FALSE;
        banner_hide_sidebar();
        t_sidebar_status.hdr_type = SCC_VID_PQ_SDR;

        nav_get_focus_id(&e_tv_win_id);
        a_cfg_av_get (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),&i2_scr_mode);
        switch(i2_scr_mode)
        {
                case SCC_VID_SCREEN_MODE_LETTERBOX:
                    //Stretch
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_STRETCH);
                    break;
                case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
                    //Panaoramic
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_PANORAMIC);
                    break;
                case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
                    //Zoom
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_ZOOM);
                    break;
                case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
                    //Wide
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_WIDE);
                    break;
                case SCC_VID_SCREEN_MODE_NORMAL:
                    //Normal
                    pw2s_text = MLM_MENU_TEXT(nav_get_mlm_lang_id(), MLM_MENU_KEY_SCREEN_MODE_NORMAL);
                    break;
                default:
                    //Unknow
                    pw2s_text = L"";

        }

    }


    if(t_sidebar_status.last_hdr_type != t_sidebar_status.hdr_type)
    {
        t_sidebar_status.last_hdr_type = t_sidebar_status.hdr_type;
        BANNER_LOG_ON_FAIL (banner_view_update_item (BANNER_ITM_DOLBY_VISION ,NULL,h_icon,!UP_TO_VIEW_AT_ONCE)) ;
        banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_ASPECT);
        BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_ASPECT, pw2s_text, NULL_HANDLE)) ;
    }
    return NAVR_OK;

}



INT32 banner_sys_audio_stream_update(VOID)
{
    SCC_AUD_IEC_TYPE_T  e_iec_type          =   SCC_AUD_IEC_CFG_PCM;
    ASH_AUDIO_INFO_T    t_audio_info        =   {0};
    INT16   i2_val          = 0;
    INT32   i4_ret          = NAVR_OK;
    UTF16_T  w2s_text[64]   = {0} ;
    HANDLE_T h_svctx        = nav_get_crnt_svctx();

    i4_ret = c_svctx_get_audio_info(h_svctx, &t_audio_info);
    if(SVCTXR_OK != i4_ret)
    {
        return AAUDR_INV_ARG;
    }
    //get e_iec_type
    i4_ret = _banner_aud_get_scc_audio_type_out(&e_iec_type);
    BANNER_LOG_ON_FAIL(i4_ret);
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS), &i2_val);
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d e_iec_type:%d i2_val:%d t_audio_info.e_aud_fmt:0x%x t_banner_stream_update_status.mm_audio_info:%d\n",\
        __FUNCTION__,__LINE__,e_iec_type,i2_val,t_audio_info.e_aud_fmt,t_banner_stream_update_status.mm_audio_info));

    TV_WIN_ID_T     e_tv_win_id   = {0};
    ISL_REC_T       t_isl_rec = {0};
    SVL_REC_T       t_svl_rec      = {0};
    nav_get_focus_id(&e_tv_win_id);
    /* Get digital/analog channel */
    i4_ret = nav_get_svl_rec(e_tv_win_id,&t_svl_rec);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    //get non-TV source status
    nav_get_isl_rec(e_tv_win_id,&t_isl_rec);
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[%s][%d]  t_svl_rec.uheader.t_rec_hdr.e_brdcst_type=%d,BRDCST_TYPE_ANALOG=%d,t_isl_rec.t_avc_info.e_video_type=%d\n", __FUNCTION__, __LINE__,
        t_svl_rec.uheader.t_rec_hdr.e_brdcst_type,BRDCST_TYPE_ANALOG,t_isl_rec.t_avc_info.e_video_type));

    if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_AC3 ||
        t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_OPUS)
    {
        if(t_banner_stream_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby Audio\n"));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));
            t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD;
        }
    }
    else if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_E_AC3)
    {
        if (e_iec_type == SCC_AUD_IEC_CFG_DDP_ATMOS && i4_ret == MENUR_OK)
        {
            if (t_banner_stream_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD_ATMOS)
            {
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby ATMOS\n"));

                #if 0
                c_uc_w2s_strcpy(w2s_text, L"Dolby Atmos-DD+ ");
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));

                #else //not show dolby atmos logo/test for custom request (MVV-8046)
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));

                #endif
                t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD_ATMOS;
            }
        }
        else
        {
            if(t_banner_stream_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD)
            {
                BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby Audio\n"));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
                BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));
                t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD;
            }
        }
     }
    else if((t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_AAC) &&
        (e_iec_type == SCC_AUD_IEC_CFG_DD || e_iec_type == SCC_AUD_IEC_CFG_DDP))
    {
        if(t_banner_stream_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] Dolby Audio\n"));
            //Dolby Audio-DD
            //pw2s_text = L"Dolby Audio-DD ";
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, BANNER_TEXT(""), NULL_HANDLE));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_audio));

            t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD;
            //banner_show_siderbar_logo(BANNER_LOGO_DOLBY_AUDIO);
        }
    }
    else if ((t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS)||
         (t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS_EXPRESS)||
         (t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_DTS_HD))
    {
#if 1 //mapping to system info audio in
        _banner_sys_info_update_dts(BANNER_AUD_PHYSICAL_INPUT, w2s_text);
#else
#if 0
        if(t_banner_stream_update_status.mm_audio_info != BANNER_MM_UPDATE_INFO_AUD_DD_DTS)
        {
            DBG_INFO(("[+++] {%s %s() %d}. [banner audio] DTS.\n",__FILE__, __FUNCTION__, __LINE__));
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] DTS\n"));
            c_uc_w2s_strcat (w2s_text, DTS_INFO) ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

            t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD_DTS;
        }
#endif

				DBG_INFO(("[+++] {%s %s() %d}. [banner audio] DTS.\n",__FILE__, __FUNCTION__, __LINE__));
				BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] DTS\n"));
				c_uc_w2s_strcat (w2s_text, DTS_INFO) ;
				BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
				BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

				t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_DD_DTS;
#endif
    }
    else if(t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_MTS)
    {
        if (i2_val == SCC_AUD_MTS_MONO)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] MONO\n"));
            c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_MONO)) ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

            t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_MONO;
        }
        else if (i2_val == SCC_AUD_MTS_STEREO)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] STEREO\n"));
            c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_STEREO)) ;
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
            BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

            t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_STEREO;
        }
        else if (i2_val == SCC_AUD_MTS_SUB_LANG)
        {
           BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner audio] SAP\n"));
           c_uc_w2s_strcat (w2s_text, MENU_TEXT(MLM_MENU_KEY_AUD_MTS_SAP)) ;
           BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
           BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));

           t_banner_stream_update_status.mm_audio_info = BANNER_MM_UPDATE_INFO_AUD_SAP;
        }
    }
    else
    {
        DBG_LOG_PRINT(("[banner audio] %s %d e_iec_type:%d i2_val:%d t_audio_info.e_aud_fmt:0x%x\n",\
        __FUNCTION__,__LINE__,e_iec_type,i2_val,t_audio_info.e_aud_fmt));
    }

    return NAVR_OK;

}


static VOID _nav_banner_mm_update_cfg_change_msg_hdlr(
    VOID*                               pv_ui2_id,
    VOID*                               pv_unused1,
    VOID*                               pv_unused2)
{
    //start mm update timer
    banner_view_mm_update_start_timer();
}

static VOID _nav_banner_mm_update_cfg_change_cb(
    UINT16                        ui2_nfy_id,
    VOID*                         pv_tag,
    UINT16                        ui2_id)
{
    TV_WIN_ID_T  e_tv_win_id;
    ISL_REC_T    t_isl_rec               = {0};

    if(ui2_mm_update_cfg_nfy_idx != ui2_nfy_id)
    {
        return;
    }

    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec (e_tv_win_id, &t_isl_rec);
    //mi_mm dispaly used by vitrual src
    if(t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL)
    {
        banner_view_mm_update_stop_timer();
        return;
    }

    nav_request_context_switch(_nav_banner_mm_update_cfg_change_msg_hdlr,
                               (VOID*)(UINT32)ui2_id,
                               NULL,
                               NULL);


}

static void _banner_sys_info_update_dts(BANNER_AUD_UPDATE_TYPE en_banner_type, UTF16_T* w2s_dst)
{
    BANNER_MM_UPDATE_INFO_AUD en_audio_info_input = BANNER_MM_UPDATE_INFO_AUD_STEREO;
    EnuCusModelSeries enModel = a_cfg_cust_get_CurModelSeries();
    BOOL b_audio_type_changed = FALSE;
    INT32	   eRet ;
    UTF16_T  w2s_text[64]   = {0} ;

    MI_AUDIO_Caps_t stAudioCaps;
    memset(&stAudioCaps,0,sizeof(MI_AUDIO_Caps_t));
    MI_AUDIO_CodecType_e *peCodecType = (MI_AUDIO_CodecType_e *)calloc(stAudioCaps.u32DecoderNum,sizeof(MI_AUDIO_CodecType_e));
    MI_AUDIO_DtsVersion_e *eDtsVersion = (MI_AUDIO_DtsVersion_e *)calloc(1, sizeof(MI_AUDIO_DtsVersion_e));

    //get dts version
    eRet = MI_AUDIO_GetAttr(0, E_MI_AUDIO_ATTR_TYPE_DTS_VERSION, NULL, eDtsVersion);
    eRet = MI_AUDIO_GetAttr(0, E_MI_AUDIO_ATTR_TYPE_CODEC_TYPE, NULL, peCodecType);
    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d banner_sys eDtsVersion = %d\n",__FUNCTION__,__LINE__,*eDtsVersion));
    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d banner_sys peCodecType = %d \n",__FUNCTION__,__LINE__,*peCodecType));

    //get original audio info input type
    switch(en_banner_type)
    {
        case BANNER_AUD_VIRTUAL_INPUT:
            {
                en_audio_info_input = t_banner_mm_update_status.mm_audio_info;
            }
        break;

        case BANNER_AUD_PHYSICAL_INPUT:
            {
                en_audio_info_input = t_banner_stream_update_status.mm_audio_info;
            }
        break;

        default:
        case BANNER_AUD_MTS:
            {
                en_audio_info_input = BANNER_MM_UPDATE_INFO_AUD_STEREO;
            }
        break;
    }



    if(E_MI_AUDIO_CODEC_TYPE_DTS  ==  *peCodecType)
    {
        if(en_audio_info_input != BANNER_MM_UPDATE_INFO_AUD_DD_DTS)
        {
			c_uc_w2s_strcpy(w2s_text, L"DTS ");
            en_audio_info_input = BANNER_MM_UPDATE_INFO_AUD_DD_DTS;
            b_audio_type_changed = TRUE;
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,en_audio_info_input));
        }
    }
    else if(E_MI_AUDIO_CODEC_TYPE_DTS_LBR    ==  *peCodecType)
    {
        if(en_audio_info_input != BANNER_MM_UPDATE_INFO_AUD_DD_DTS_LBR)
        {
            if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
            {
                c_uc_w2s_strcpy(w2s_text, L"DTS-HD ");
            }
            else // M6
            {
                // special case for vzo spec: MVD-1191
                if ((enModel == CUS_MODEL_2021_83_2K_D_HD) || (enModel == CUS_MODEL_2021_83_2K_D_FHD) || (enModel == CUS_MODEL_2022_83_2K_D))
                {
                    c_uc_w2s_strcpy(w2s_text, L"DTS-HD ");
                }
                else
                {
                    c_uc_w2s_strcpy(w2s_text, L"DTS Express ");
                }
            }
            en_audio_info_input = BANNER_MM_UPDATE_INFO_AUD_DD_DTS_LBR;
            b_audio_type_changed = TRUE;
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,en_audio_info_input));
        }
    }
    else if(E_MI_AUDIO_CODEC_TYPE_DTSHD  == *peCodecType)
    {
        if(en_audio_info_input != BANNER_MM_UPDATE_INFO_AUD_DD_DTSHD)
        {
            if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
            {
                c_uc_w2s_strcpy(w2s_text, L"DTS-HD ");
            }
            else //M6
            {
                // specail case for vzo spec: MVD-1191
                if ((enModel == CUS_MODEL_2021_83_2K_D_HD) || (enModel == CUS_MODEL_2021_83_2K_D_FHD) || (enModel == CUS_MODEL_2022_83_2K_D))
                {
                    c_uc_w2s_strcpy(w2s_text, L"DTS-HD ");
                }
                else
                {
                    c_uc_w2s_strcpy(w2s_text, L"DTS-HD Master Audio ");
                }
            }
            en_audio_info_input = BANNER_MM_UPDATE_INFO_AUD_DD_DTSHD;
            b_audio_type_changed = TRUE;
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,en_audio_info_input));
        }
    }
    else if(E_MI_AUDIO_CODEC_TYPE_DTS_X == *peCodecType)
    {
        if(en_audio_info_input != BANNER_MM_UPDATE_INFO_AUD_DD_DTS_X)
        {
            if(*eDtsVersion == E_MI_AUDIO_DTS_VERSION_X)
            {
                c_uc_w2s_strcpy(w2s_text, L"DTS:X ");
            }
            else
            {
                c_uc_w2s_strcpy(w2s_text, L"DTS ");
            }

            en_audio_info_input = BANNER_MM_UPDATE_INFO_AUD_DD_DTS_X;
            b_audio_type_changed = TRUE;
            BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,en_audio_info_input));
        }
    }

    //set audio info type & notify
    if(b_audio_type_changed == TRUE)
    {
        switch(en_banner_type)
        {
            case BANNER_AUD_VIRTUAL_INPUT:
                {
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE)) ;
                    t_banner_mm_update_status.mm_audio_info = en_audio_info_input;
                    banner_view_tv_info_updeted_update(BANNER_ITM_UPDATED_AUDIO_FARMAT);
                    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner mi_mm] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_mm_update_status.mm_audio_info));
                }
            break;

            case BANNER_AUD_PHYSICAL_INPUT:
                {
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_DOLBY_AUDIO, BANNER_TEXT(""), NULL_HANDLE));
                    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_AUDIO_FARMAT, w2s_text, NULL_HANDLE));
                    t_banner_stream_update_status.mm_audio_info = en_audio_info_input;
                    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d audio info change:%d\n",__FUNCTION__,__LINE__,t_banner_stream_update_status.mm_audio_info));
                }
            break;

            default:
            case BANNER_AUD_MTS:
                {
                    BANNER_LOG ( _BANNER_LOG_TYPE_MESSAGE,("[banner audio] %s %d \n"));
                }
            break;
        }
    }

    free(peCodecType);
    free(eDtsVersion);

    c_uc_w2s_strcpy(w2s_dst, w2s_text);

}


#if (CUSTOMER == VIZIO)

INT32 banner_cust_evt_handle_headphones(BOOL b_connected)
{
    HANDLE_T h_icon = NULL_HANDLE;

    switch (b_connected) {
        case TRUE:
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("BT headphones are connected\n"));
            h_icon = h_g_nav_btui_headphones_40x40_img;
            break;
        case FALSE:
        default:
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("BT headphones are NOT connected\n"));
            break;
    }
    BANNER_LOG_ON_FAIL (_notify_to_banner_item_changed (BANNER_ITM_HEADPHONES, BANNER_TEXT(""), h_icon));

    return NAVR_OK ;
}

#endif



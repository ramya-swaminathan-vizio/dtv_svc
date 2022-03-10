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
 * $RCSfile: yahoo_osd.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author:
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor:
 * $MD5HEX:
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "c_wgl.h"
#include "u_irrc_btn_def.h"
#include "c_uc_str.h"
#include "c_handle.h"
#include "c_os.h"
#include "c_yahoo_widget_api.h"
#include "app_client.h"

#include "nav/nav_common.h"
#include "res/nav/nav_view.h"
#include "nav/banner2/banner.h"
#include "app_util/a_cfg.h"
#include "res/nav/banner2/yahoo_osd/a_yahoo_osd.h"
#include "res/nav/nav_variant.h"
#include "app_util/a_network.h"
#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#include <sys/time.h>
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/app_util/network/network_custom.h"


#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

#define RET_ON_ERR(_expr) if(_expr !=0) {return -1;}

typedef struct __NAV_YAHOO_OSD_T
{
    HANDLE_T                    h_frame;
    HANDLE_T                    h_title_time_network_lb;
    HANDLE_T                    h_low_bat_lb;
    UTF16_T                     w2s_profile_guest[31];
    WGL_HIMG_TPL_T              h_bak_one_line_img;
    WGL_HIMG_TPL_T              h_signal_1of5_bits;
    WGL_HIMG_TPL_T              h_signal_2of5_bits;
    WGL_HIMG_TPL_T              h_signal_3of5_bits;
    WGL_HIMG_TPL_T              h_signal_4of5_bits;
    WGL_HIMG_TPL_T              h_signal_5of5_bits;
    WGL_HIMG_TPL_T              h_wired_connect;
    WGL_HIMG_TPL_T              h_network_notconnect;
    HANDLE_T                    h_timer;

} _NAV_YAHOO_OSD_T;

#define YAHOO_OSD_FRAME_W       (316)
#define YAHOO_OSD_FRAME_H       (32) //CH_FRAME_HEIGHT
#define YAHOO_OSD_FRAME_X       (DISPLAY_WIDTH - YAHOO_OSD_FRAME_W)
#define YAHOO_OSD_FRAME_Y       NAV_HEIGHT(0)


#define YAHOO_OSD_LB_X          NAV_WIDTH(0)
#define YAHOO_OSD_LB_Y          NAV_HEIGHT(0)
#define YAHOO_OSD_LB_W          (YAHOO_OSD_FRAME_W)
#define YAHOO_OSD_LB_H          YAHOO_OSD_FRAME_H


#define YAHOO_OSD_LB_TITLE_W    (170)
#define YAHOO_OSD_LB_TIME_W     (70)
#define YAHOO_OSD_LB_NETWORK_W  (75)

#define YAHOO_OSD_TIMEOUT       (5000)

static _NAV_YAHOO_OSD_T t_g_yahoo_osd;
static BOOL             b_g_show_time;

/*-----------------------------------------------------------------------------
 * Name
 *      _yahoo_osd_view_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _yahoo_osd_view_create(HANDLE_T  h_parent)
{
    INT32                        i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[3];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* create banner frame */
    SET_RECT_BY_SIZE(&t_rect,
                    YAHOO_OSD_FRAME_X,
                    YAHOO_OSD_FRAME_Y,
                    YAHOO_OSD_FRAME_W,
                    YAHOO_OSD_FRAME_H
                    );
    i4_ret = c_wgl_create_widget(
                    h_parent,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    255,
                    (VOID*)(0),
                    NULL,
                    &t_g_yahoo_osd.h_frame
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    /* set image */
    c_memset(&t_img_info, 0x0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_g_yahoo_osd.h_bak_one_line_img;
    t_img_info.u_img_data.t_standard.t_highlight = t_g_yahoo_osd.h_bak_one_line_img;
    t_img_info.u_img_data.t_standard.t_disable   = t_g_yahoo_osd.h_bak_one_line_img;

    i4_ret = c_wgl_do_cmd(t_g_yahoo_osd.h_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      YAHOO_OSD_LB_X,
                      YAHOO_OSD_LB_Y,
                      YAHOO_OSD_LB_W,
                      YAHOO_OSD_LB_H);

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = 128;
    at_cols[0].ui2_width        = YAHOO_OSD_LB_TITLE_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_max_text_len = 128;
    at_cols[1].ui2_width        = YAHOO_OSD_LB_TIME_W;

    at_cols[2].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[2].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[2].ui2_width        = YAHOO_OSD_LB_NETWORK_W;

    t_lb_init.ui4_style         =  WGL_STL_LB_FORCE_HLT;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = YAHOO_OSD_LB_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    RET_ON_ERR(c_wgl_create_widget(t_g_yahoo_osd.h_frame,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 &t_g_yahoo_osd.h_title_time_network_lb));

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
	
#ifndef APP_NAV_BNR_NEXT_EVENT_SUPPORT
	c_strcpy((CHAR*)t_fnt_info.a_c_font_name, (CHAR*)SN_FONT_DEFAULT_SMALL);
#else
    c_strcpy((CHAR*)t_fnt_info.a_c_font_name, (CHAR*)NAV_FONT_SMALL);
#endif

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)0),
                           WGL_PACK(&t_fnt_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK((UINT16)1),
                           WGL_PACK(&t_fnt_info));
    RET_ON_ERR(i4_ret);

    /* Set Inset */
    c_memset(&t_inset, 0 , sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (t_g_yahoo_osd.h_title_time_network_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (t_g_yahoo_osd.h_title_time_network_lb,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    RET_ON_ERR(i4_ret);

    t_inset.i4_left   = 4;
    i4_ret = c_wgl_do_cmd (t_g_yahoo_osd.h_title_time_network_lb,
                            WGL_CMD_LB_SET_COL_INSET,
                            WGL_PACK((UINT16)0),
                            WGL_PACK(&t_inset));
    RET_ON_ERR(i4_ret);

    t_inset.i4_left   = 2;
    t_inset.i4_right  = 1;
    i4_ret = c_wgl_do_cmd (t_g_yahoo_osd.h_title_time_network_lb,
                            WGL_CMD_LB_SET_COL_INSET,
                            WGL_PACK((UINT16)1),
                            WGL_PACK(&t_inset));
    RET_ON_ERR(i4_ret);
    t_inset.i4_right  = 0;
    i4_ret = c_wgl_do_cmd (t_g_yahoo_osd.h_title_time_network_lb,
                            WGL_CMD_LB_SET_COL_INSET,
                            WGL_PACK((UINT16)2),
                            WGL_PACK(&t_inset));
    RET_ON_ERR(i4_ret);

    c_memset(&t_lb_color, 0x0, sizeof(WGL_LB_COLOR_ELEM_SET_T));
    COLOR_COPY(&t_lb_color.t_normal,            & NAV_COLOR(NAV_COLOR_ID_TEXT));
    COLOR_COPY(&t_lb_color.t_disable,           & NAV_COLOR(NAV_COLOR_ID_TEXT));
    COLOR_COPY(&t_lb_color.t_highlight,         & NAV_COLOR(NAV_COLOR_ID_TEXT));
    COLOR_COPY(&t_lb_color.t_highlight_unfocus, & NAV_COLOR(NAV_COLOR_ID_TEXT));
    COLOR_COPY(&t_lb_color.t_pushed,            & NAV_COLOR(NAV_COLOR_ID_TEXT));
    COLOR_COPY(&t_lb_color.t_selected,          & NAV_COLOR(NAV_COLOR_ID_TEXT));
    COLOR_COPY(&t_lb_color.t_selected_disable,  & NAV_COLOR(NAV_COLOR_ID_TEXT));
    i4_ret = c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                      WGL_CMD_LB_SET_COL_COLOR,
                      WGL_PACK_2(0, WGL_CLR_TEXT),
                      WGL_PACK(&t_lb_color));
    RET_ON_ERR(i4_ret);
    i4_ret = c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                      WGL_CMD_LB_SET_COL_COLOR,
                      WGL_PACK_2(1, WGL_CLR_TEXT),
                      WGL_PACK(&t_lb_color));
    RET_ON_ERR(i4_ret);

    /* Set background image */
    c_memset(&t_img_info, 0x0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    t_img_elem.h_normal            = NULL_HANDLE;
    t_img_elem.h_disable           = NULL_HANDLE;
    t_img_elem.h_highlight         = NULL_HANDLE;
    t_img_elem.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem.h_pushed            = NULL_HANDLE;
    t_img_elem.h_selected          = NULL_HANDLE;
    t_img_elem.h_selected_disable  = NULL_HANDLE;
    RET_ON_ERR (c_wgl_do_cmd (t_g_yahoo_osd.h_title_time_network_lb,
                              WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                              WGL_PACK(& t_img_elem),
                              NULL));

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _get_ntp_time
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _get_ntp_time(DTG_T* pt_loc_dtg)
{

    struct timeval tv;
    struct timezone tz;
    INT64      sec;

    if (gettimeofday(&tv, &tz) == 0)
    {
        sec = (INT64)tv.tv_sec;
        c_dt_utc_sec_to_loc_dtg(sec, pt_loc_dtg);


        DBG_LOG_PRINT(("[year,mon,day,hour,min] =[%d-%d-%d-%d-%d] \n ",
                                            pt_loc_dtg->ui2_yr,
                                            pt_loc_dtg->ui1_mo,
                                            pt_loc_dtg->ui1_day,
                                            pt_loc_dtg->ui1_hr,
                                            pt_loc_dtg->ui1_min));

        if (((pt_loc_dtg->ui2_yr == 0) && (pt_loc_dtg->ui1_mo == 0))||
            (pt_loc_dtg->ui2_yr == 1970))
        {
            return FALSE;
        }

        return TRUE;

    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _yahoo_osd_get_display_time
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _yahoo_osd_get_display_time(DTG_T * pt_loc_dtg)
{
    BOOL    b_success = FALSE;

    b_success = _get_ntp_time(pt_loc_dtg);

    if (b_success)
    {
        return TRUE;
    }
    else
    {
        DT_COND_T    t_dt_cond = 0;
        
        c_dt_get_brdcst_utc (NULL, & t_dt_cond);

        if ((t_dt_cond == DT_FREE_RUNNING)    ||  /* Date-time is free-running */
            (t_dt_cond == DT_NOT_RUNNING)     ||  /* Date-time is not-running */
            (t_dt_cond == DT_NO_SYNC_SRC))        /* No sync source */
        {
            return FALSE;
        }
        else
        {
            c_dt_utc_sec_to_loc_dtg(c_dt_get_brdcst_utc(NULL,NULL), pt_loc_dtg);
            return TRUE;
        }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _yahoo_osd_timer_out_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _yahoo_osd_timer_out_fct(
    VOID*                              pv_this,
    VOID*                              pv_unused2,
    VOID*                              pv_unused3)
{
    a_yahoo_osd_hide();
    return;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _yahoo_osd_timer_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _yahoo_osd_timer_cb(
    HANDLE_T                     h_timer,
    VOID*                        pv_this)
{
    /*post a message to itself*/
    nav_request_context_switch(_yahoo_osd_timer_out_fct,
                               pv_this,
                               NULL,
                               NULL);
    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _yahoo_osd_view_set_lb
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _yahoo_osd_view_set_lb()
{
    UTF16_T                  w2s_profile[41] = L"Profile: ";
    WGL_LB_ITEM_T            at_items[3];
    NET_802_11_BSS_INFO_T    t_bss_info;
    DTG_T                    t_dtg = {0};
    CHAR                     time [20] = {0};
    UTF16_T                  w2s_time[20] = {0};
    UTF16_T*                 apw2s_am_pm;
    UINT8                    ui1_interface = 0;
    NW_DHCP_STATE_T          e_dhcp_state;
    WGL_HIMG_TPL_T           at_img_signal_icon[5] =
                                         {
                                             t_g_yahoo_osd.h_signal_1of5_bits,
                                             t_g_yahoo_osd.h_signal_2of5_bits,
                                             t_g_yahoo_osd.h_signal_3of5_bits,
                                             t_g_yahoo_osd.h_signal_4of5_bits,
                                             t_g_yahoo_osd.h_signal_5of5_bits
                                         };
     NAVR_CHK_FAIL(c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                            WGL_CMD_LB_DEL_ALL,
                            NULL,
                            NULL));

    c_uc_w2s_strncat(w2s_profile,t_g_yahoo_osd.w2s_profile_guest, 30);

    if (_yahoo_osd_get_display_time(&t_dtg))
    {
        b_g_show_time = TRUE;
    }
    else
    {
        b_g_show_time = FALSE;
    }

    if (b_g_show_time)
    {
        if (t_dtg.ui1_hr > 12)
        {
            t_dtg.ui1_hr -= 12;
            apw2s_am_pm = L"PM";
        }
		else if (t_dtg.ui1_hr == 12)
		{
            apw2s_am_pm = L"PM";
        }
		else if (t_dtg.ui1_hr == 0)
		{
			t_dtg.ui1_hr = 12;
            apw2s_am_pm = L"AM";
        }
        else
        {
            apw2s_am_pm = L"AM";
        }


        if (t_dtg.ui1_min<10)
        {
#if 0
            if (t_dtg.ui1_hr<10)
            {
                c_sprintf(time, "0%d:0%d ", t_dtg.ui1_hr, t_dtg.ui1_min);
            }
            else
#endif
            {
                c_sprintf(time, "%d:0%d ", t_dtg.ui1_hr, t_dtg.ui1_min);
            }
        }
        else
        {
#if 0
            if (t_dtg.ui1_hr<10)
            {
                c_sprintf(time, "0%d:%d ", t_dtg.ui1_hr, t_dtg.ui1_min);
            }
            else
#endif
            {
                c_sprintf(time, "%d:%d ", t_dtg.ui1_hr, t_dtg.ui1_min);
            }
        }    
        c_uc_ps_to_w2s(time, w2s_time, c_strlen(time));
        c_uc_w2s_strcat(w2s_time, apw2s_am_pm);
    }
    else
    {
        c_uc_w2s_strcpy(w2s_time, L"");
    }

    NAVR_CHK_FAIL(a_nw_get_ethernet_connect_info(&ui1_interface));
    
    if(ui1_interface == APP_CFG_NET_INTERFACE_WIFI) /* WIFI*/
    {
        NW_WLAN_STATE_T     e_wlan_state;
        a_nw_wlan_status(&e_wlan_state);

        if (e_wlan_state == NW_WLAN_ASSOCIATE)  /* has associate with wifi*/
        {
            if (a_nw_custom_is_get_ip_addr())
            {
                c_memset(&t_bss_info, 0x0, sizeof(NET_802_11_BSS_INFO_T));
                NAVR_CHK_FAIL(a_nw_wlan_get_curr_bss(&t_bss_info));

                if((UINT16)t_bss_info.i2_Level > 80)
                {
                    at_items[2].data.h_img = at_img_signal_icon[4];
                }
                else if((UINT16)t_bss_info.i2_Level <= 20)
                {
                    at_items[2].data.h_img = at_img_signal_icon[0];
                }
                else
                {
                    at_items[2].data.h_img = at_img_signal_icon[(((UINT16)(t_bss_info.i2_Level -1)) /20)%5];
                }
            }
            else
            {
                a_nw_get_dhcp_status(&e_dhcp_state);
                if (NW_DHCP_STARTING == e_dhcp_state)
                {
                    at_items[2].data.h_img =  NULL_HANDLE;
                }
                else 
                {
                    at_items[2].data.h_img =  t_g_yahoo_osd.h_network_notconnect;
                }
            }
        }
        else if (e_wlan_state == NW_WLAN_ASSOCIATING)
        {
            at_items[2].data.h_img =  NULL_HANDLE;
        }
        else    /* not associate with wifi*/
        {
            at_items[2].data.h_img =  t_g_yahoo_osd.h_network_notconnect;
        }
    }
    else    /* WIRED */
    {
        if (a_nw_custom_is_get_ip_addr())
        {
            at_items[2].data.h_img = t_g_yahoo_osd.h_wired_connect;
        }
        else
        {           
            a_nw_get_dhcp_status(&e_dhcp_state);
            if (NW_DHCP_STARTING == e_dhcp_state)
            {
                at_items[2].data.h_img =  NULL_HANDLE;
            }
            else 
            {
                at_items[2].data.h_img =  t_g_yahoo_osd.h_network_notconnect;
            }
        }
    }
    at_items[0].e_col_type     = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_profile;
    at_items[1].e_col_type     = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text   = w2s_time;
    at_items[2].e_col_type     = LB_COL_TYPE_IMG;

    NAVR_CHK_FAIL( c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                          WGL_CMD_LB_APPEND_ELEM,
                          at_items, NULL ));

    NAVR_CHK_FAIL(c_wgl_do_cmd(t_g_yahoo_osd.h_title_time_network_lb,
                          WGL_CMD_LB_SEL_ELEM,
                          WGL_PACK(0),
                          NULL));

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _yahoo_osd_show_handle_nfy
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _yahoo_osd_show_handle_nfy (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    AM_CLIENT_STATE e_status = YAHOO_STATUS_HIDE;
extern VOID msg_convert_custom_get_yahoo_status(AM_CLIENT_STATE * p_status);

    if(nav_is_component_visible(NAV_COMP_ID_BANNER))
    {
        nav_hide_component(NAV_COMP_ID_BANNER);
    }
    else if( nav_is_component_visible(NAV_COMP_ID_INPUT_SRC))
    {
        nav_hide_component(NAV_COMP_ID_INPUT_SRC);
    }

    /* For Yahoo V7 */
    msg_convert_custom_get_yahoo_status(&e_status);
    
    if (YAHOO_STATUS_FULLSCREN == e_status)
    { 
        if (nav_is_component_visible(NAV_COMP_ID_PWD_DLG))
        {
            nav_hide_component(NAV_COMP_ID_PWD_DLG);
        }
        else if (nav_is_component_visible(NAV_COMP_ID_POWER))
        {
            nav_hide_component(NAV_COMP_ID_POWER);
        }
        else if (nav_is_component_visible(NAV_COMP_ID_SCREEN_SAVER))
        {
            nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
        }
        else if (nav_is_component_visible(NAV_COMP_ID_DIALOG))
        {
            nav_hide_component(NAV_COMP_ID_DIALOG);
        }
    }
}                    

/*-----------------------------------------------------------------------------
 * Name
 *      a_yahoo_osd_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_yahoo_osd_init(HANDLE_T  h_parent)
{
    c_memset(&t_g_yahoo_osd, 0x0, sizeof(_NAV_YAHOO_OSD_T));

    NAVR_CHK_FAIL(nav_img_create_docu_ui_osd_bk(&t_g_yahoo_osd.h_bak_one_line_img));
    NAVR_CHK_FAIL(nav_img_create_signal_1of5(&t_g_yahoo_osd.h_signal_1of5_bits));
    NAVR_CHK_FAIL(nav_img_create_signal_2of5(&t_g_yahoo_osd.h_signal_2of5_bits));
    NAVR_CHK_FAIL(nav_img_create_signal_3of5(&t_g_yahoo_osd.h_signal_3of5_bits));
    NAVR_CHK_FAIL(nav_img_create_signal_4of5(&t_g_yahoo_osd.h_signal_4of5_bits));
    NAVR_CHK_FAIL(nav_img_create_signal_5of5(&t_g_yahoo_osd.h_signal_5of5_bits));
    NAVR_CHK_FAIL(nav_img_create_wired_connect(&t_g_yahoo_osd.h_wired_connect));
    NAVR_CHK_FAIL(nav_img_create_network_notconnect(&t_g_yahoo_osd.h_network_notconnect));

    c_uc_w2s_strcpy(t_g_yahoo_osd.w2s_profile_guest,L"Guest");
    c_timer_create(&t_g_yahoo_osd.h_timer);
    NAVR_CHK_FAIL(_yahoo_osd_view_create(h_parent));

    c_wgl_set_visibility(t_g_yahoo_osd.h_frame,WGL_SW_HIDE);

    b_g_show_time = TRUE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_yahoo_osd_show
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_yahoo_osd_show(
                    VOID
                    )
{
    CHAR           ac_profile_name[30 + 1] = {0};
    CHAR           *pc_profile_name = NULL;
    UTF16_T        w2s_profile_name[30 + 1] = {0};

    nav_request_context_switch_in_sync(
            _yahoo_osd_show_handle_nfy,
            NULL,
            NULL,
            NULL,
            5000
            );

#ifdef APP_PORTING
    pc_profile_name = c_yahoo_widget_get_profile_name();
#endif    
    if(pc_profile_name != NULL)
    {

        if(c_strlen(pc_profile_name) <= 30)
        {
            c_strcpy(ac_profile_name,pc_profile_name);
        }
        else
        {
            c_strncpy(ac_profile_name,pc_profile_name,30);
        }

        c_uc_ps_to_w2s(ac_profile_name,w2s_profile_name,30);

        a_yahoo_osd_set_profile(w2s_profile_name,c_uc_w2s_strlen(w2s_profile_name),FALSE);

    }

    NAVR_CHK_FAIL(_yahoo_osd_view_set_lb());

    c_wgl_float (t_g_yahoo_osd.h_frame, TRUE, WGL_NO_AUTO_REPAINT);
#if 0//Cedric 0301
    c_wgl_set_visibility(t_g_yahoo_osd.h_frame, WGL_SW_RECURSIVE);
#endif
    c_wgl_repaint(t_g_yahoo_osd.h_frame,NULL,TRUE);
    c_timer_start(t_g_yahoo_osd.h_timer, YAHOO_OSD_TIMEOUT,
                           X_TIMER_FLAG_ONCE,
                           _yahoo_osd_timer_cb,
                           NULL);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_yahoo_osd_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_yahoo_osd_hide(
                    VOID
                    )
{
	c_wgl_float(t_g_yahoo_osd.h_frame,FALSE,FALSE);
    c_wgl_set_visibility(t_g_yahoo_osd.h_frame,WGL_SW_HIDE);

    c_wgl_repaint(t_g_yahoo_osd.h_frame,NULL,TRUE);
    c_timer_stop(t_g_yahoo_osd.h_timer);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_yahoo_osd_set_profile
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_yahoo_osd_set_profile(UTF16_T * pw2s_profile,UINT32  ui4_len, BOOL b_repaint )
{
    if(ui4_len > 30)
    {
        return NAVR_INV_ARG;
    }

    c_memset(t_g_yahoo_osd.w2s_profile_guest, 0x0, sizeof(t_g_yahoo_osd.w2s_profile_guest));

    c_uc_w2s_strncpy(t_g_yahoo_osd.w2s_profile_guest,pw2s_profile,ui4_len);

    if(b_repaint)
    {
         _yahoo_osd_view_set_lb();
         c_wgl_repaint(t_g_yahoo_osd.h_frame,NULL,TRUE);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_yahoo_osd_is_visible
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
 BOOL a_yahoo_osd_is_visible(VOID)
 {
     BOOL    b_visible;
     INT32   i4_ret;

     i4_ret = c_wgl_get_visibility(t_g_yahoo_osd.h_frame, &b_visible);
     if(i4_ret != WGLR_OK)
     {
         return FALSE;
     }
     else
     {
         return b_visible;
     }
 }

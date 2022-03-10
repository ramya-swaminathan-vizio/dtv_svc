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
 * $RCSfile: banner_view.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: jg_lizhuwang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "res/nav/nav_variant.h"
#include "res/nav/banner2/yahoo_osd/a_yahoo_osd.h"


#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_svctx.h"

#include "am/a_am.h"
#include "mmp/a_mmp.h"
#include "wizard/a_wzd.h"
#include "nav/nav_bnr_state_mgr.h"
#include "nav/nav_common.h"

#include "res/app_util/network/network_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "nav/banner2/a_banner.h"
#include "nav/banner2/banner.h"
#include "res/nav/banner2/banner_rc.h"

#include "menu2/menu_page.h"
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"

#ifdef APP_NETWORK_WIFI_SUPPORT
#include "u_net_wlan.h"
#endif
#include "app_util/a_network.h"

#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/c4tv_apron.h"
#endif
#include "nav/sys_info/a_sys_info.h"
#include "res/nav/nav_img_rc.h"

#include "nav/cc_info/cc_info.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "wdk/widget/wdk_widget.h"
#include "res/nav/banner2/gen/nav_banner2_view_rc_layout.h"
#include "rest/a_rest_api.h"

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_vizio/menu_page_bt_json_db.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "res/nav/nav_dbg.h"


#define ANIM_IN  1
#define ANIM_OUT 0

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define _REFRESH_VIEW_AT_ONCE               (TRUE)
#define _REFRESH_VIEW_ON_TIMER              (FALSE)
#define _CLEAR_FROM_REFRESH_BUFF            (TRUE)

extern INT32 _json_bt_db_get_mac( t_bt_item_type type, const char *name, const char *mac);

typedef enum
{
    _REFRESH_TYPE_STATE = 0 ,
    _REFRESH_TYPE_ITEM ,
    _REFRESH_TYPE_LAST_ENTRY

} _REFRESH_TYPE_T ;

typedef struct _BANNER_VIEW_T
{
    BOOL          b_is_on_showing ;

    /* if the flag b_ui_frozen is on, the view will not be repainted, but that do
     * NOT effect on the state changing and item updatting, just no UI changed.
     * PLEASE NOTICE, this priority of "hidden" operation is higher than this flag
     */
    BOOL          b_ui_frozen;

    HANDLE_T      h_update_view_timer ;         /* it will keep current state unchanged for 0.5 seconds before changing state */
    HANDLE_T      h_delay_show_timer ;          /* it will delay show banner with the delay time */
    HANDLE_T      h_siderbar_auto_hide_timer;   /* it will auto hide siderbar  after 3s */
    HANDLE_T      h_siderbar_delay_show_timer;   /* it will auto check logo showing condition,if not,it will repeat check again*/

    HANDLE_T      h_mm_update_timer;            /* it will auto update mmp info*/
    HANDLE_T      h_name_update_timer;          /* it will auto update name info if it's length too long*/

    HANDLE_T      h_bnr_root_frame;             /* banner root frames */
    HANDLE_T      h_bnr_siderbar_frame;         /* banner sider bar  frames */
    /* banner refresh buffer */
    struct
    {
        BNR_ITEM_SET_T  t_mask ;                /* refresh mask */
        UINT8           ui1_state_id ;          /* refresh state */
        /* refresh items */
        struct
        {
            UTF16_T*    pw2s_text ;             /* for text item */
            HANDLE_T    h_img ;                 /* for icon or frame item */

        } t_item_buff[BANNER_ITM_LAST_VALID_ENTRY] ;
    } t_refresh_buff ;

    /* view listener, when view updated, used this to notify banner */
    banner_state_item_update_listener       pf_reporter ;
#ifdef APP_BANNER_AMIN
    GL_RECT_T                               t_animate_ui_max;
    GL_RECT_T                               t_animate_ui_min;
#endif
    GL_RECT_T                               t_animate_in;
    GL_RECT_T                               t_animate_out;
#ifdef APP_TTS_SUPPORT
    UINT32        t_tts_updated_item_mask ; /* mask of update item string to tts */
    HANDLE_T      h_tts_timer;
#endif
} BANNER_VIEW_T;


typedef struct _BANNER_VIEW_SIDEBAR_SHOWING_T
{
    BOOL          b_on_showing_text_HDR;
    BOOL          b_on_showing_icon_HDR;
    BOOL          b_on_showing_icon_DD_AUDIO;
    BOOL          b_on_showing_icon_DD_ATMOS;
    BOOL          b_on_showing_icon_PROGAMING_ENGINE;
    BOOL          b_on_showing_icon_V_GAMING_ENGINE;
    BOOL          b_on_showing_icon_FILMMAKER_MODE;
    BOOL          b_on_showing_icon_FREESYNC;

}BANNER_VIEW_SIDEBAR_SHOWING_T;


static UINT8 g_banner_view_updated_flag    = 0;

#ifdef APP_BANNER_AMIN
static UINT32         u4_g_banner_state     = ANIM_IN;
#endif

extern WGL_HIMG_TPL_T at_img_signal_icon[];
extern WGL_HIMG_TPL_T at_img_signal_icon1[];

static WDK_WIDGET_COMMON_RES_T              t_g_wdk_widget_common_res[2];

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static BANNER_VIEW_T                        t_g_view = {0} ;
static BOOL                                 b_g_update_view_timer_valid = FALSE ;
static BOOL                                 b_g_is_delay_show_banner    = FALSE ;
static INT32                                i4_g_delay_show_time        = 2000  ;
static BOOL                                 b_is_banner_enable          = TRUE;
#ifdef APP_TTS_SUPPORT
static INT32                               g_t_tts_updated_item_mask  = FALSE;
static INT32                               g_t_tts_banenr_detail_mask = FALSE;
static BOOL                                b_is_banner_tts_enable     = TRUE;
#endif

static BOOL b_split_flag = FALSE;

static BOOL b_ctrl_show_flag = TRUE;
static BOOL b_sidebar_show_flag = TRUE;

static BOOL b_name_timer_update_flag = FALSE;

static BANNER_VIEW_SIDEBAR_SHOWING_T banner_view_sidebar_showing = {0};

#define BANNEER_SCRL_INPUT_SRC_NAME_MAX  (16)
static UINT32           i4_scrl_banner_name_offset = 0;
static UTF16_T          w2s_text_scrl_banner_name[128] = {0};

//custom spec 34 pixels space between icon
#define BANNER_SB_ICON_SPACE (34)

static  UINT8 timer_reset_count = 0;
static  UINT8 delay_check_repeat_timer_count = 0; //avoid h_siderbar_delay_show_timer keep repeat when unexpected

static GL_COLOR_T t_g_gray = {0xff, {0x2c}, {0x2c}, {0x2c}};
static GL_COLOR_T t_g_transparent = {0,{0},{0},{0}};



BOOL banner_view_set_b_ctrl_show_flag(BOOL val);
BOOL banner_view_get_b_ctrl_show_flag(VOID);
BOOL banner_view_set_sidebar_show_flag(BOOL val);
BOOL banner_view_get_sidebar_show_flag(VOID);
INT32 banner_view_mm_update_start_timer(VOID);
INT32 banner_view_mm_update_stop_timer(VOID);
BOOL banner_view_set_name_update_flag(BOOL val);
BOOL banner_view_get_name_update_flag(VOID);
INT32 banner_view_name_update_start_timer(VOID);
INT32 banner_view_name_update_stop_timer(VOID);
INT32 banner_view_update_scrl_banner_name(const UTF16_T *src,UINT32 len);



/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

VOID banner_view_tv_info_updeted_erase(VOID);

extern BOOL banner_cust_set_sidebar_showing(BOOL show_flag);
extern BOOL banner_check_mi_mm_playing(VOID);
extern INT32 banner_mm_try(VOID);
extern VOID banner_sys_info_reset_mm_update_info(BOOL b_update);

static INT32 _repaint_view (VOID);
static VOID _banner_view_reset_tts_timer(VOID);
static VOID _banner_view_tts_reset_timer_count(VOID);
static VOID _banner_siderbar_check_to_show_cb_fct(HANDLE_T  pt_tm_handle,VOID*     pv_tag);


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
#ifdef SYS_MTKTVAPI_SUPPORT
BOOL gb_audio_info_nfy = FALSE;
BOOL gb_audio_info_nfy_update = FALSE;
#endif

#ifdef APP_BANNER_AMIN
VOID banner_view_hide_prog_detail_info()
{
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PDCH),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PCH),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_UP),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL_PG_IDX),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_DN),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_CRNT_TIME),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RATING),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TITLE),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TIME),WGL_SW_HIDE);
     c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_TITLE),WGL_SW_HIDE);
}
#endif

static VOID _banner_repaint (
    VOID*                       pv_tag,
    VOID*                       pv_reserved1,
    VOID*                       pv_reserved2
    )
{
   BANNER_LOG_ON_FAIL(_repaint_view());
}

static VOID _banner_view_start_repaint()
{
    //banner_view_mm_update_stop_timer();
    banner_view_name_update_stop_timer();

    if(b_ctrl_show_flag)
        nav_request_context_switch(_banner_repaint, NULL, NULL, NULL);
    else
        DBG_LOG_PRINT(("[banner] b_ctrl_show_flag:%d\n",b_ctrl_show_flag));
}
/*-----------------------------------------------------------------------------
 * Name
 *      _time_out_to_update_view
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _time_out_to_update_view (
    VOID*                       pv_tag,
    VOID*                       pv_reserved1,
    VOID*                       pv_reserved2
    )
{
    if (b_g_update_view_timer_valid)
    {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" time out to repaint \n")) ;
        BANNER_LOG_ON_FAIL (banner_view_refresh (_REFRESH_VIEW_AT_ONCE)) ;
        b_g_update_view_timer_valid = TRUE;
    }
    else
    {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" timer was reset, do not repaint \n")) ;
    }
}

/*******************************************************************************
 * Name
 *          _hode_on_bef_state_chg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _hode_on_bef_state_chg(
    HANDLE_T                  h_timer,
    VOID*                     pv_tag)
{
    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" prepare repaint \n")) ;

    b_g_update_view_timer_valid = TRUE ;

    /* execute in timer's thread context */
    nav_request_context_switch(_time_out_to_update_view, pv_tag, NULL, NULL);
}

static BOOL _banner_item_widget_need_repaint(UINT8      ui1_item_id,
                                             UTF16_T*   pw2s_text_new,
                                             HANDLE_T   handle,
                                             BOOL*      pb_is_text)
{
    BANNER_ITEM_INFO_T*    pt_item_info = banner_get_item_info (ui1_item_id) ;

    *pb_is_text = FALSE;

    switch(pt_item_info->e_item_type)
    {
        case BANNER_ITEM_TYPE_TEXT:
        {
            UTF16_T    w2s_text_old[512] = {0};
            CHAR       ps_text_new[512]  = {0};
            CHAR       ps_text_old[512]  = {0};
            CHAR       ps_text_cached[512]= {0};

            *pb_is_text = TRUE;
            if(NULL_HANDLE != pt_item_info->ph_handle)
            {
                BANNER_CHK_FAIL(c_wgl_do_cmd (*(pt_item_info->ph_handle),
                                          WGL_CMD_TEXT_GET_TEXT,
                                          WGL_PACK (w2s_text_old),
                                          WGL_PACK (512)));
                c_uc_w2s_to_ps(pw2s_text_new,ps_text_new,512);
                c_uc_w2s_to_ps(w2s_text_old,ps_text_old,512);
                c_uc_w2s_to_ps(t_g_view.t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text,ps_text_cached,512);

               // BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("[%s] old = \"%s\" \n",GET_ITEM_DISP_NAME (ui1_item_id),ps_text_old));
               // BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("[%s] cache = \"%s\" \n",GET_ITEM_DISP_NAME (ui1_item_id),ps_text_cached));
                if(0 == c_strcmp(ps_text_old,ps_text_new) && 0 == c_strcmp(ps_text_cached,ps_text_new))
                {
                    /* text of widget is NULL or text  had not changed */
                    return FALSE;
                }
                else
                {
                    BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("[%s] new = \"%s\"\n",GET_ITEM_DISP_NAME (ui1_item_id),ps_text_new));
                }
            }
        }
        break;
        case BANNER_ITEM_TYPE_ICON:
        {
            if(t_g_view.t_refresh_buff.t_item_buff[ui1_item_id].h_img == handle)
            {/* icon had not changed */
                return FALSE;
            }
            else
            {
                BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("[%s] old = 0x%x new = 0x%x\n",GET_ITEM_DISP_NAME (ui1_item_id),t_g_view.t_refresh_buff.t_item_buff[ui1_item_id].h_img,handle));
                t_g_view.t_refresh_buff.t_item_buff[ui1_item_id].h_img = handle;
            }
        }
        break;
        default:
            break;
    }
    return TRUE;
}

/*---------------------------------------------------------------------------
 * Name
 *      _send_to_refresh_buff
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _send_to_refresh_buff (
    _REFRESH_TYPE_T             e_refresh_type ,
    UINT8                       ui1_state_id ,      /* valid when e_refresh_type == _REFRESH_TYPE_STATE */
    UINT8                       ui1_item_id ,       /* valid when e_refresh_type == _REFRESH_TYPE_ITEM */
    UTF16_T*                    pw2s_text ,         /* valid when e_refresh_type == _REFRESH_TYPE_ITEM */
    HANDLE_T                    h_img               /* valid when e_refresh_type == _REFRESH_TYPE_ITEM */
    )
{
    SIZE_T                      t_size = 0 ;
    BANNER_VIEW_T*              pt_view = &t_g_view;
    BOOL                        b_is_text_item = FALSE;
    switch (e_refresh_type)
    {
        case _REFRESH_TYPE_STATE :
        {
            BANNER_STATE_INFO_T*        pt_state_info = NULL ;

             /* find out the items used by this state */
             pt_state_info = banner_get_state_info ( ui1_state_id) ;
             if (!pt_state_info)
             {
                  BANNER_CHK_FAIL (NAVR_FAIL) ;
             }
             BANNER_LOG(_BANNER_LOG_TYPE_VIEW,("set current state => %s\n",GET_STATE_DISP_NAME(pt_state_info->ui1_state_id)));
             pt_view->t_refresh_buff.ui1_state_id = ui1_state_id ;
             break ;
        }
        case _REFRESH_TYPE_ITEM :
            NAV_ASSERT (ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY) ;
            BANNER_CHK_FAIL ( (ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY) ? NAVR_OK : NAVR_FAIL) ;
#ifdef APP_TTS_SUPPORT
            c_timer_stop(pt_view->h_tts_timer);
#endif
           if(_banner_item_widget_need_repaint(ui1_item_id,pw2s_text,h_img,&b_is_text_item))
           {
                BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("Cache [%s] to be refreshed it text widget item ? %s\n",GET_ITEM_DISP_NAME(ui1_item_id),
                                                  b_is_text_item ? "YES":"NO"));
                banner_item_lock();
                /* save image handle */
                pt_view->t_refresh_buff.t_item_buff[ui1_item_id].h_img = h_img ;

                if(b_is_text_item)
                {
                    if(NULL != pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text)
                    {
                        BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("Cache [%s] clean context\n",GET_ITEM_DISP_NAME(ui1_item_id)));
                        c_mem_free(pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text);
                        pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text = NULL;
                    }
                    if((t_size = c_uc_w2s_strlen(pw2s_text)) > 0)
                    {
                        /* alloc some memory to save the content */
                        pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text = c_mem_alloc ((t_size + 1) * sizeof(UTF16_T)) ;
                        if (NULL == pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text)
                        {
                            /* alloc memory failed */
                             BANNER_LOG_ON_FAIL (NAVR_OUT_OF_MEM) ;
                        }
                        else
                        {
                            CHAR       ps_text_new[512]  = {0};
                            c_memset (pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text,
                                      0, (t_size + 1) * sizeof(UTF16_T)) ;
                            c_memcpy (pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text,
                                      pw2s_text, t_size * sizeof(UTF16_T)) ;
                            c_uc_w2s_to_ps(pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text,ps_text_new,512);
                            BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("Cache [%s] new context is %s length = %d\n",GET_ITEM_DISP_NAME(ui1_item_id),ps_text_new,t_size));
                        }
                    }
                    else
                    {
                        BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("Cache [%s] new context is NULL\n",GET_ITEM_DISP_NAME(ui1_item_id)));
                    }
                }
                /* set item refresh flag */
                pt_view->t_refresh_buff.t_mask |= NAV_BNR_STATE_IDX_TO_ID(ui1_item_id) ;
                banner_item_unlock();
            }
            break ;
        default :
            NAV_ASSERT (0) ;
            BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _delay_refresh_view_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _delay_refresh_view_hdlr (
    VOID*                       pv_tag,
    VOID*                       pv_reserved1,
    VOID*                       pv_reserved2
    )
{
    b_g_is_delay_show_banner = FALSE;

    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" time out to repaint view .\n ")) ;
    /* hide exec comps first */
    BANNER_LOG_ON_FAIL (nav_hide_components(COMP_EXEC_SET_BANNER));

    _banner_view_start_repaint();

}

/*******************************************************************************
 * Name
 *          _delay_refresh_view
 * Description
 * Input arguments
 * Output arguments
 * Returns
 ******************************************************************************/
static VOID _delay_refresh_view(
    HANDLE_T                  h_timer,
    VOID*                     pv_tag)
{
    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" delay refresh view.\n ")) ;

    /* execute in timer's thread context */
    nav_request_context_switch(_delay_refresh_view_hdlr, pv_tag, NULL, NULL);
}

/*---------------------------------------------------------------------------
 * Name
 *      _clean_from_refresh_buff
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _clean_from_refresh_buff (
    _REFRESH_TYPE_T             e_refresh_type ,
    UINT8                       ui1_item_id     /* valid when e_refresh_type == _REFRESH_TYPE_ITEM */
    )
{
    BANNER_VIEW_T*              pt_view = &t_g_view;

    switch (e_refresh_type)
    {
    case _REFRESH_TYPE_STATE :
        /* reset saved data */
        pt_view->t_refresh_buff.ui1_state_id = NAV_BNR_STATE_NULL_STATE_NAME ;
        break ;

    case _REFRESH_TYPE_ITEM :
        NAV_ASSERT (ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY) ;
        BANNER_CHK_FAIL ( (ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY) ? NAVR_OK : NAVR_FAIL) ;

        /* reset refresh flag */
        pt_view->t_refresh_buff.t_mask &= (~(NAV_BNR_STATE_IDX_TO_ID(ui1_item_id)));
       // BANNER_LOG(_BANNER_LOG_TYPE_VIEW,("Clean [%s] refresh Mask \n",GET_ITEM_DISP_NAME(ui1_item_id)));
        break ;

    default :
        NAV_ASSERT (0) ;
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    return NAVR_OK ;
}

/*---------------------------------------------------------------------------
 * Name
 *      _update_buffered_item
 * Description
 *      update buff content to ITME
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _update_buffered_item (
    UINT8                       ui1_item_id,
    BOOL                        b_clear
    )
{
    BANNER_VIEW_T*              pt_view = &t_g_view ;
    HANDLE_T                    h_item = NULL_HANDLE ;
    BANNER_ITEM_INFO_T*         pt_item_info = NULL ;
    UTF16_T*                    pw2s_text = NULL ;
    HANDLE_T                    h_img = NULL_HANDLE ;
    WGL_IMG_INFO_T              t_img_info ;

    /* unknown item */
    if (ui1_item_id >= BANNER_ITM_LAST_VALID_ENTRY)
    {
        NAV_ASSERT (0) ;
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    /* this item not cached */
    if ((BNR_ITEM_SET_T)0 == (NAV_BNR_STATE_IDX_TO_ID (ui1_item_id) & pt_view->t_refresh_buff.t_mask))
    {
        return NAVR_OK ;
    }

    /* search the specified items */
    pt_item_info = banner_get_item_info (ui1_item_id) ;
    if (!pt_item_info)
    {
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    h_item = *(pt_item_info->ph_handle) ;
    if (NULL_HANDLE == h_item)
    {
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    BANNER_LOG(_BANNER_LOG_TYPE_ITEM,(" item[%s],item type is %s \n",GET_ITEM_DISP_NAME(ui1_item_id),
              pt_item_info->e_item_type == BANNER_ITEM_TYPE_FRM ? "BANNER_ITEM_TYPE_FRM":
              pt_item_info->e_item_type == BANNER_ITEM_TYPE_TEXT ? "BANNER_ITEM_TYPE_TEXT":
              pt_item_info->e_item_type == BANNER_ITEM_TYPE_ICON ? "BANNER_ITEM_TYPE_ICON":"Unknow item type"));
    banner_item_lock();

    switch (pt_item_info->e_item_type)
    {
        case BANNER_ITEM_TYPE_FRM:
            /* set frame image buffer*/
            h_img = pt_view->t_refresh_buff.t_item_buff[ui1_item_id].h_img ;
            c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = h_img ;
            t_img_info.u_img_data.t_standard.t_disable   = h_img ;
            t_img_info.u_img_data.t_standard.t_highlight = h_img ;
            BANNER_LOG_ON_FAIL(c_wgl_do_cmd (
                                    h_item,
                                    WGL_CMD_GL_SET_IMAGE,
                                    WGL_PACK(WGL_IMG_BK),
                                    WGL_PACK(&t_img_info)));
            break ;

        case BANNER_ITEM_TYPE_TEXT:
            pw2s_text       =       (pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text)
                            ?       pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text
                            :       BANNER_TEXT ("") ;
#if 0
            {
                CHAR ps_text[512] = {0};
                c_uc_w2s_to_ps(pw2s_text,ps_text,512);
                BANNER_LOG(_BANNER_LOG_TYPE_ITEM,(" item[%s] => \"%s\" len = %d wlen = %d\n",GET_ITEM_DISP_NAME(ui1_item_id),ps_text,c_strlen(ps_text),c_uc_w2s_strlen (pw2s_text)));
            }
#endif
            BANNER_LOG_ON_FAIL (c_wgl_do_cmd (h_item,
                                    WGL_CMD_TEXT_SET_TEXT,
                                    (VOID*)pw2s_text,
                                    (VOID*)c_uc_w2s_strlen (pw2s_text))) ;
            break ;

        case BANNER_ITEM_TYPE_ICON:
            /* set icon image buffer*/
            h_img = pt_view->t_refresh_buff.t_item_buff[ui1_item_id].h_img ;
            c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = h_img ;
            t_img_info.u_img_data.t_standard.t_disable   = h_img ;
            t_img_info.u_img_data.t_standard.t_highlight = h_img ;
            BANNER_LOG_ON_FAIL(c_wgl_do_cmd (
                                    h_item,
                                    WGL_CMD_GL_SET_IMAGE,
                                    WGL_PACK(WGL_IMG_FG),
                                    WGL_PACK(&t_img_info)));
            break ;
        default:
            break;

    }

    if (b_clear)
    {
        /* after udated the item, clean the saved date from refresh buff */
        BANNER_LOG_ON_FAIL(_clean_from_refresh_buff (_REFRESH_TYPE_ITEM, ui1_item_id)) ;
    }
    banner_item_unlock();
    return NAVR_OK ;
}

/*---------------------------------------------------------------------------
 * Name
 *      _update_buffered_items
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _update_buffered_items (
    BOOL                        b_clear
    )
{
    UINT8                       ui1_item_id = 0 ;

    /* update buff content to ITMES */
    /* please note, the topmost-bit-mask will be used for state */
    for (ui1_item_id = 0; ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY; ui1_item_id ++)
    {
        BANNER_LOG_ON_FAIL (_update_buffered_item (ui1_item_id, b_clear)) ;
    }

    return NAVR_OK ;
}

/*---------------------------------------------------------------------------
 * Name
 *      _update_buffered_state
 * Description
 *      update state from buffered data
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _update_buffered_state (
    BOOL                        b_clear
    )
{
    BANNER_VIEW_T*              pt_view = &t_g_view ;
    HANDLE_T                    h_item = NULL_HANDLE ;
    UINT8                       ui1_item_id = 0 ;
    UINT8                       ui1_item_type = 0 ;
    BNR_ITEM_SET_T              t_state_item_includs = 0 ;
    BANNER_STATE_INFO_T*        pt_state_info = NULL ;
    CHAR                        s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;

    if (NAV_BNR_STATE_NULL_STATE_NAME == pt_view->t_refresh_buff.ui1_state_id
#ifdef APP_BANNER_AMIN
     || BANNER_STATE_IDLE             == pt_view->t_refresh_buff.ui1_state_id
#endif
     )
    {
        return NAVR_OK ;
    }

    /* find out the items used by this state */
    pt_state_info = banner_get_state_info ( pt_view->t_refresh_buff.ui1_state_id) ;
    if (!pt_state_info)
    {
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    t_state_item_includs = pt_state_info->t_item_includs ;
    BANNER_LOG(_BANNER_LOG_TYPE_VIEW,(" state => %s\n",GET_STATE_DISP_NAME(pt_state_info->ui1_state_id)));

    /* control CC caption item and VIDEO info item show or hide  */
    UINT8   ui1_val   = ICL_CC_ITEM_STATUS_HIDE;
    SIZE_T  z_size    = ICL_RECID_CC_ITEM_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_CC_ITEM_STATUS, ICL_RECID_CC_ITEM_STATUS),
                       &ui1_val, &z_size);

    a_am_get_active_app (s_active_app);

    /* set these items to visible */
    for (ui1_item_id = 0; ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY; ui1_item_id ++ )
    {
        /* get this item's handle */
        BANNER_CONTINUE_ON_FAIL (nav_bnr_state_get_item_widget (ui1_item_id, &h_item, &ui1_item_type)) ;

        /*focuse to hide the unclude items and pass */
        if( 0 == (t_state_item_includs & NAV_BNR_STATE_IDX_TO_ID(ui1_item_id)))
        {
            /* set this item to visible */
            BOOL    b_visible = FALSE;

            c_wgl_get_visibility(h_item, &b_visible);
            if(b_visible)
            {
                c_wgl_set_visibility(h_item, WGL_SW_HIDE);
            }
            //_update_buffered_item (ui1_item_id, TRUE);
            continue;
        }

        if (ICL_CC_ITEM_STATUS_SHOW == ui1_val)
        {
            if (BANNER_ITM_VIDEO_INFO == ui1_item_id ||
                BANNER_ITM_RESOLUTION_TXT == ui1_item_id)
            {
                BANNER_CHK_FAIL (c_wgl_set_visibility ( h_item,WGL_SW_HIDE)) ;
                continue;
            }
        }
        else if (BANNER_ITM_CAPTION == ui1_item_id ||
            BANNER_ITM_CAPTION_ICON == ui1_item_id)
        {
            BANNER_CHK_FAIL (c_wgl_set_visibility ( h_item,WGL_SW_HIDE)) ;
            continue;
        }
        else if(BANNER_ITM_AUDIO_FARMAT == ui1_item_id || BANNER_ITM_DOLBY_AUDIO == ui1_item_id)
        {
            BOOL b_mute = FALSE;

            nav_get_mute(&b_mute);
            if(b_mute)
            {
                c_wgl_set_visibility (h_item, WGL_SW_HIDE);
                continue;
            }
            else
            {
                INT32     i4_ret;
                INT16    i2_audio_vol;

                i4_ret = a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),(INT16*)&i2_audio_vol);

                if((NAVR_OK == i4_ret && i2_audio_vol == 0) ||
                    (!banner_check_mi_mm_playing() && a_nav_is_signal_loss()))
                 {
                     BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("[Banner][%s,%d],vol num is 0  or signal loss,should not show audio fmt\r\n",__FUNCTION__, __LINE__));
                     c_wgl_set_visibility (h_item, WGL_SW_HIDE);
                     continue;
                 }
            }
        }

        /* should hide TV related items like CH_NAME & CH_NO items under MMP and 3rd app  */
        if ((a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED) ||
            (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)   ||
            (c_strcmp(s_active_app, MMP_NAME) == 0))
        {
            if (BANNER_ITM_RATING == ui1_item_id ||
                BANNER_ITM_PROG_TITLE == ui1_item_id ||
                BANNER_ITM_PROG_TIME == ui1_item_id)
            {
                BANNER_CHK_FAIL (c_wgl_set_visibility (h_item, WGL_SW_HIDE)) ;
                continue;
            }
        }

#if 0
            BANNER_LOG(_BANNER_LOG_TYPE_VIEW,("[%s] try to handle  include ? %s hande = 0x%x text = 0x%p\n",
            GET_ITEM_DISP_NAME(ui1_item_id),
            (t_state_item_includs & NAV_BNR_STATE_IDX_TO_ID(ui1_item_id))> 0 ? "YES":"NO",
            pt_view->t_refresh_buff.t_item_buff[ui1_item_id].h_img,
            pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text));
#endif
        if(t_state_item_includs & NAV_BNR_STATE_IDX_TO_ID(ui1_item_id))
        {
             if(banner_get_item_info (ui1_item_id)->e_item_type == BANNER_ITEM_TYPE_ICON)
             {
                   c_wgl_set_visibility(h_item,
                        (pt_view->t_refresh_buff.t_item_buff[ui1_item_id].h_img == NULL_HANDLE) ? WGL_SW_HIDE: WGL_SW_NORMAL);
                   BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("set icon [%s] visibility %s\n",GET_ITEM_DISP_NAME(ui1_item_id),(pt_view->t_refresh_buff.t_item_buff[ui1_item_id].h_img == NULL_HANDLE) ? "NO" :"YES"));
             }
             else if (banner_get_item_info (ui1_item_id)->e_item_type == BANNER_ITEM_TYPE_TEXT)
             {
                   c_wgl_set_visibility(h_item,
                        (pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text == NULL || c_uc_w2s_strlen(pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text) == 0) ? WGL_SW_HIDE: WGL_SW_NORMAL);
                  BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("set text [%s] visibility %s\n",GET_ITEM_DISP_NAME(ui1_item_id),(pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text == NULL || c_uc_w2s_strlen(pt_view->t_refresh_buff.t_item_buff[ui1_item_id].pw2s_text) == 0) ? "NO" :"YES"));
             }
             else // BANNER_ITEM_TYPE_FRM
             {
                   BANNER_CHK_FAIL (c_wgl_set_visibility ( h_item,
                                (t_state_item_includs & NAV_BNR_STATE_IDX_TO_ID(ui1_item_id))
                                ? WGL_SW_NORMAL : WGL_SW_HIDE)) ;
                   BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("set fream [%s] visibility %s\n",GET_ITEM_DISP_NAME(ui1_item_id),(t_state_item_includs & NAV_BNR_STATE_IDX_TO_ID(ui1_item_id) ? "YES":"NO")));
             }
         }
#if 0
        if(BANNER_ITM_DOLBY_AUDIO ==  ui1_item_id || BANNER_ITM_AUDIO_FARMAT == ui1_item_id)
        {
            c_wgl_set_visibility(*(banner_get_item_info ((BANNER_ITM_DOLBY_AUDIO ==  ui1_item_id) ? BANNER_ITM_AUDIO_FARMAT : BANNER_ITM_DOLBY_AUDIO)->ph_handle), WGL_SW_HIDE);
        }
#endif
    }

    if (b_clear)
    {
         /* after udated the state, clean the saved date from refresh buff */
        // BANNER_LOG_ON_FAIL (_clean_from_refresh_buff (_REFRESH_TYPE_STATE, 0)) ;
    }

    return NAVR_OK ;
}

/*---------------------------------------------------------------------------
 * Name
 *      _banner_view_get_string_size
 * Description: get string size --> string width or string height
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
UINT32 _banner_view_get_string_size(HANDLE_T   handle,
                                    //FE_FNT_SIZE     e_font_size
                                         UINT8      ui1_custom_size
                                    )
{
    UINT32                       ui4_string_width = 0;
    UINT32                       ui4_string_height= 0;
    UTF16_T                      w2s_text[512] = {0};
    char                         sz_text[512] =  {0};
    HFONT_T                      h_font_handle;
    WDK_WIDGET_COMMON_RES_T     *pt_common_res = (ui1_custom_size == 21 ?  &t_g_wdk_widget_common_res[1] : &t_g_wdk_widget_common_res[0]);

    h_font_handle = pt_common_res->h_font_handle;

    BANNER_CHK_FAIL(c_wgl_do_cmd (handle,
                                  WGL_CMD_TEXT_GET_TEXT,
                                  WGL_PACK (w2s_text),
                                  WGL_PACK (512)));

                c_uc_w2s_to_ps(w2s_text,sz_text,512);
    /* Get string height. */
    c_wgl_get_string_size(h_font_handle,
                          w2s_text,
                          512,
                          (INT32*)&ui4_string_width,
                          (INT32*)&ui4_string_height);

    BANNER_LOG(_BANNER_LOG_TYPE_ITEM,("string is \"%s\"string_LEN[%d],string_width[%d],string_height[%d] i4_cus_font_size = %d\n",
                                        sz_text,c_uc_w2s_strlen(w2s_text),ui4_string_width,ui4_string_height,ui1_custom_size));
    /* add 10 pix to fix*/
    return ui4_string_width + 16;// + 20;
}

/*---------------------------------------------------------------------------
 * Name
 *      _banner_view_set_ch_name_two_lines
 * Description: exclude antenna cable and unknown for now
 *
 * Input arguments :
 * Output arguments
 *
 * Returns
 *---------------------------------------------------------------------------*/
VOID banner_view_set_ch_name_split_flag(BOOL b_falg)
{
    b_split_flag = b_falg;
}

BOOL _banner_view_get_ch_name_split_flag(VOID)
{
    return b_split_flag;
}

/*---------------------------------------------------------------------------
 * Name
 *      _banner_view_set_ch_name_two_lines
 * Description: some channel names are very line, according to DTV00827610
 *              when zoom on, take channel name two lines
 *
 * Input arguments :
 *          h_parent:
 *              CH NAME's handle
 *          b_one_or_two:
 *              b_one_or_two == TRUE    channel name should be two lines(zoom on)
 *              b_one_or_two == FALSE    channel name should be one line(zoom off)
 * Output arguments
 *
 * Returns
 *
 *---------------------------------------------------------------------------*/
VOID _banner_view_set_ch_name_two_lines(HANDLE_T   h_parent,
                                                BOOL    b_one_or_two)
{
    INT32                        i4_ret = 0;
    UTF16_T                      w2s_text[CH_NAME_MAX_LENGTH] = {0};
    CHAR                         ps_tmp[CH_NAME_MAX_LENGTH] = {0};
    CHAR*                        pc_ch_begin = NULL;
    UINT8                        ui1_offset = 0;

    /* Get current display text */
    i4_ret = c_wgl_do_cmd (h_parent,
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (CH_NAME_MAX_LENGTH));

    c_uc_w2s_to_ps (w2s_text, ps_tmp,CH_NAME_MAX_LENGTH);

    pc_ch_begin = c_strchr(ps_tmp, ' ');
    ui1_offset = (UINT8)(pc_ch_begin - ps_tmp);

    if(_banner_view_get_ch_name_split_flag() == FALSE && b_one_or_two == TRUE && c_strchr(ps_tmp, '\n') == NULL)
    {
        if(c_strlen(ps_tmp) > 5 + ui1_offset && c_strlen(ps_tmp) < CH_NAME_MAX_LENGTH)
        {
            UINT8 ui1_ch_name_index = 0;
            for(ui1_ch_name_index = c_strlen(ps_tmp) - 1;  ui1_ch_name_index >= 5 + ui1_offset + 1;
                ui1_ch_name_index--)
            {
                ps_tmp[ui1_ch_name_index + 1] = ps_tmp[ui1_ch_name_index];
            }
            ps_tmp[5 + ui1_offset + 1] = '\n';
        }
    }
    else if(_banner_view_get_ch_name_split_flag() == FALSE && b_one_or_two == FALSE && c_strchr(ps_tmp, '\n') != NULL)
    {
        UINT8 ui1_ch_name_index = 0;
        for(ui1_ch_name_index = 5 + ui1_offset + 1; ui1_ch_name_index < c_strlen(ps_tmp);
            ui1_ch_name_index++)
        {
            ps_tmp[ui1_ch_name_index] = ps_tmp[ui1_ch_name_index + 1];
        }
        ps_tmp[ui1_ch_name_index] = '\0';
    }
   BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("set channge name to \"%s\"\n",ps_tmp) );
    c_uc_ps_to_w2s(ps_tmp, w2s_text, CH_NAME_MAX_LENGTH * sizeof(UTF16_T));

    i4_ret = c_wgl_do_cmd (h_parent,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (w2s_text),
                      WGL_PACK (CH_NAME_MAX_LENGTH));
    if(i4_ret != WGLR_OK)
    {
        BANNER_LOG(_BANNER_LOG_TYPE_VIEW,("set ch name back failed!, \n"));
    }
}

const GL_COLOR_T COLOR_LIGHT_BLUE_NORMAL =
{
    255, {163}, {189}, {203}
};

const GL_COLOR_T COLOR_LIGHT_BLUE_HLT =
{
    255, {204}, {236}, {254}
};

const GL_COLOR_T COLOR_GRAY_128 =
{
    255, {128}, {128}, {128}
};

static BANNER_ITEM_INFO_T* _banner_view_get_touching_visible_item(UINT8 ui1_item_id,BOOL toleft)
{
   BANNER_ITEM_INFO_T*  pt_tmp    = NULL;
   BOOL                 b_visible = FALSE;
   UINT8                ui1_start = ui1_item_id;

    if(ui1_item_id <= 0||
       ui1_item_id >= BANNER_ITM_LAST_VALID_ENTRY - 1 )
    {
       return NULL;
    }

    if(toleft)
    {
        while( (-- ui1_item_id) >= 0 && NULL != (pt_tmp = banner_get_item_info (ui1_item_id)))
        {
            c_wgl_get_visibility(*(pt_tmp->ph_handle), &b_visible);
            //BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("item[%s] is  visiable ? %s\n",GET_ITEM_DISP_NAME(ui1_item_id),b_visible ? "YES":"NO"));
            if(b_visible)
            {
                return pt_tmp;
            }
        }
    }
    else
    {
         while( (++ui1_item_id) < BANNER_ITM_LAST_VALID_ENTRY && NULL != (pt_tmp = banner_get_item_info (ui1_item_id)))
        {
            c_wgl_get_visibility(*(pt_tmp->ph_handle), &b_visible);
           // BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("item[%s] is  visiable ? %s\n",GET_ITEM_DISP_NAME(ui1_item_id),b_visible ? "YES":"NO"));
            if(BANNER_ITM_DOLBY_AUDIO == ui1_start && BANNER_ITM_AUDIO_OUT == pt_tmp->ui1_item_id)
                continue;

            if(b_visible)
            {
                return pt_tmp;
            }
        }
    }

    return NULL;
}

#define      INSERT_GAP_SMAll  (12)
#define      INSERT_GAP_NORMAL (32)
#define      INSERT_GAP_LARGE  (96)

/*---------------------------------------------------------------------------
 * Name
 *      _banner_zoom_mode_text_item_update
 * Description:update banner zoom mode or normal mode osd
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _banner_mode_text_item_update(UINT8 ui1_item_id)
{
    HANDLE_T                    h_item = NULL_HANDLE ;
    BANNER_ITEM_INFO_T*         pt_item_info = NULL ;
    BANNER_ITEM_INFO_T*         pt_right_item_info = NULL;
    BANNER_ITEM_INFO_T*         pt_left_item_info = NULL;
    GL_RECT_T*                  pt_rect;


    if (ui1_item_id >= BANNER_ITM_LAST_VALID_ENTRY)
    {
        NAV_ASSERT (0) ;
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    /* search the specified items */
    pt_item_info = banner_get_item_info (ui1_item_id) ;
    if (!pt_item_info)
    {
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }

    h_item = *(pt_item_info->ph_handle) ;
    if (NULL_HANDLE == h_item)
    {
        BANNER_CHK_FAIL (NAVR_FAIL) ;
    }
    BANNER_LOG (_BANNER_LOG_TYPE_ITEM,(" item[%s]\n",GET_ITEM_DISP_NAME(ui1_item_id)) ) ;
    pt_rect =   pt_item_info->pt_rect;

    switch (pt_item_info->e_item_type)
    {
        /*in debug version,will get the 3D item type is frm,to prevent the system crash,add this case*/
        case BANNER_ITEM_TYPE_FRM:
         {
            BOOL b_visible = FALSE;
            c_wgl_get_visibility(*(pt_item_info->ph_handle), &b_visible);
            BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("rect[l= %4d,r = %4d,t = %4d,b = %4d] item[%s] b_visible? => %s\n",
                pt_rect->i4_left,
                pt_rect->i4_right,
                pt_rect->i4_top,
                pt_rect->i4_bottom,
                GET_ITEM_DISP_NAME(ui1_item_id),
                b_visible ? "YES":"NO")) ;
          }
            break;
        case BANNER_ITEM_TYPE_TEXT:
        {
            WGL_FONT_INFO_T             t_fnt_info;
            UINT8                       ui1_align = WGL_AS_LEFT_CENTER;
            UINT32                       ui4_strlen = 0;
            UINT8                       ui1_get_idx = 0;

            c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
            c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
            t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
            t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
            t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
            t_fnt_info.ui1_custom_size = 21;

            a_cfg_cust_get_zoom_mode(&ui1_get_idx);
            if(BANNER_ITM_TIMER_24  == ui1_item_id ||
               BANNER_ITM_TV_NAME   == ui1_item_id ||
               APP_CFG_CUST_ZOOM_MODE_ON == ui1_get_idx)
            {
                t_fnt_info.ui1_custom_size = 42;
                //t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
            }

            ui4_strlen = _banner_view_get_string_size(h_item, t_fnt_info.ui1_custom_size);
            BANNER_LOG (_BANNER_LOG_TYPE_ITEM,(" item[%s] strlen = %d\n",GET_ITEM_DISP_NAME(ui1_item_id),ui4_strlen) ) ;
            switch(ui1_item_id)
            {
                /* those item are WGL_AS_LEFT_CENTER*/
                case BANNER_ITM_TV_NAME:
                 {   ui1_align = WGL_AS_CENTER_CENTER;
                     pt_rect->i4_left = INSERT_GAP_LARGE;
                     pt_rect->i4_right = pt_rect->i4_left + (ui4_strlen > 0 ? ui4_strlen : nav_banner2_view_rc_get_wgt_default_width(ui1_item_id));
                    break;
                 }

                case BANNER_ITM_CH_NAME:
                {
                    pt_left_item_info = _banner_view_get_touching_visible_item(ui1_item_id,TRUE);

                    if(pt_left_item_info)
                    {
                        BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("### left visiable item is %s\n",GET_ITEM_DISP_NAME(pt_left_item_info->ui1_item_id)));
                        pt_rect->i4_left = pt_left_item_info->pt_rect->i4_right + INSERT_GAP_SMAll;
                        pt_rect->i4_right= pt_rect->i4_left + (ui4_strlen > 0 ? ui4_strlen : nav_banner2_view_rc_get_wgt_default_width(ui1_item_id));
                    }
                    ui1_align = WGL_AS_LEFT_CENTER;
                    break;
                 }
                 case BANNER_ITM_IPT_CH_NO:
                {
                    pt_left_item_info = _banner_view_get_touching_visible_item(ui1_item_id,TRUE);

                    if(pt_left_item_info)
                    {
                        BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("### left visiable item is %s\n",GET_ITEM_DISP_NAME(pt_left_item_info->ui1_item_id)));
                        pt_rect->i4_left = pt_left_item_info->pt_rect->i4_right + INSERT_GAP_NORMAL;
                        pt_rect->i4_right= pt_rect->i4_left + (ui4_strlen > 0 ? ui4_strlen : nav_banner2_view_rc_get_wgt_default_width(ui1_item_id));
                    }

                    ui1_align = WGL_AS_LEFT_CENTER;
                    break;
                 }
                /* those item are WGL_AS_RIGHT_CENTER*/
                case BANNER_ITM_WIFI_TXT:
                {
                    ui1_align = WGL_AS_LEFT_CENTER;
                    pt_right_item_info = _banner_view_get_touching_visible_item(ui1_item_id,FALSE);

                    if(pt_right_item_info)
                    {
                      //  BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("### right visiable item is %s, ui1_strlen = %d\n",GET_ITEM_DISP_NAME(pt_right_item_info->ui1_item_id),ui1_strlen));
                        pt_rect->i4_right = pt_right_item_info->pt_rect->i4_left - INSERT_GAP_NORMAL;
                        pt_rect->i4_left = pt_rect->i4_right - (ui4_strlen > 0 ? ui4_strlen : nav_banner2_view_rc_get_wgt_default_width(ui1_item_id));
                    }
                    break;
                }
                case BANNER_ITM_AUDIO_OUT:
                case BANNER_ITM_RESOLUTION_TXT:
                case BANNER_ITM_ASPECT:
                case BANNER_ITM_AUDIO_FARMAT:
                {
                    ui1_align = WGL_AS_RIGHT_CENTER;
                    pt_right_item_info = _banner_view_get_touching_visible_item(ui1_item_id,FALSE);

                    if(pt_right_item_info)
                    {
                       // BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("### right visiable item is %s, ui1_strlen = %d\n",GET_ITEM_DISP_NAME(pt_right_item_info->ui1_item_id),ui1_strlen));
                        pt_rect->i4_right = pt_right_item_info->pt_rect->i4_left - INSERT_GAP_NORMAL ;
                        if(BANNER_ITM_AUDIO_OUT == ui1_item_id)
                            pt_rect->i4_right -= INSERT_GAP_NORMAL/2;
                        pt_rect->i4_left = pt_rect->i4_right -  (ui4_strlen > 0 ? ui4_strlen : nav_banner2_view_rc_get_wgt_default_width(ui1_item_id));
                    }
                    //BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" item[%s]\n",GET_ITEM_DISP_NAME(ui1_item_id)) ) ;
                    break;
                }
                case BANNER_ITM_TIMER_24:
                {
                    pt_rect->i4_right = 1920 - INSERT_GAP_LARGE;
                    pt_rect->i4_left  = pt_rect->i4_right - (ui4_strlen > 0 ? ui4_strlen : nav_banner2_view_rc_get_wgt_default_width(ui1_item_id));
                    ui1_align = WGL_AS_RIGHT_CENTER;
                    break;
                 }
                case BANNER_ITM_PROG_DETAIL:
                    pt_rect->i4_right = 1920 - INSERT_GAP_LARGE;
                    break;
                default :
                    break;
            }

            c_wgl_do_cmd(h_item,WGL_CMD_ICON_SET_ALIGN,WGL_PACK(ui1_align),NULL);
            c_wgl_do_cmd (h_item,WGL_CMD_GL_SET_FONT,WGL_PACK(&t_fnt_info),NULL);
            BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("rect[l= %4d,r = %4d,t = %4d,b = %4d] item[%s] strlen = %d\n",pt_rect->i4_left,pt_rect->i4_right,pt_rect->i4_top,pt_rect->i4_bottom,GET_ITEM_DISP_NAME(ui1_item_id),ui4_strlen)) ;

            c_wgl_move(h_item,pt_rect,WGL_NO_AUTO_REPAINT/*WGL_SYNC_AUTO_REPAINT*/);
            break ;
        }
        case BANNER_ITEM_TYPE_ICON:
            switch(ui1_item_id)
            {
                 case BANNER_ITM_IPTS_ICON:
                 {
                     pt_left_item_info = _banner_view_get_touching_visible_item(ui1_item_id,TRUE);
                     BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("rect[l= %4d,r = %4d,t = %4d,b = %4d] item[%s] \n",pt_left_item_info->pt_rect->i4_left,pt_left_item_info->pt_rect->i4_right,pt_left_item_info->pt_rect->i4_top,pt_left_item_info->pt_rect->i4_bottom,GET_ITEM_DISP_NAME(pt_left_item_info->ui1_item_id))) ;
                     if(pt_left_item_info)
                    {
                        BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("### left visiable item is %s\n",GET_ITEM_DISP_NAME(pt_left_item_info->ui1_item_id)));
                        pt_rect->i4_left = pt_left_item_info->pt_rect->i4_right + INSERT_GAP_NORMAL;
                        pt_rect->i4_right= pt_rect->i4_left + nav_banner2_view_rc_get_wgt_default_width(ui1_item_id);
                    }
                     break;
                 }
                 case BANNER_ITM_CAPTION_ICON :
                 case BANNER_ITM_WIFI_ICON:
                 case BANNER_ITM_DOLBY_VISION:
                 case BANNER_ITM_DOLBY_AUDIO:
#if (CUSTOMER == VIZIO)
                 case BANNER_ITM_HEADPHONES:
#endif
                 {
                      pt_right_item_info = _banner_view_get_touching_visible_item(ui1_item_id,FALSE);
                      if(pt_right_item_info)
                     {
                        // DBG_LOG_PRINT(("### right visiable item is %s\n",GET_ITEM_DISP_NAME(pt_right_item_info->ui1_item_id)));
                         pt_rect->i4_right = pt_right_item_info->pt_rect->i4_left - ( ui1_item_id == BANNER_ITM_WIFI_ICON ? INSERT_GAP_SMAll: INSERT_GAP_NORMAL);
                         pt_rect->i4_left = pt_rect->i4_right - nav_banner2_view_rc_get_wgt_default_width(ui1_item_id);
                     }
                      break;
                 }
            }
            BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("rect[l= %4d,r = %4d,t = %4d,b = %4d] item[%s] \n",pt_rect->i4_left,pt_rect->i4_right,pt_rect->i4_top,pt_rect->i4_bottom,GET_ITEM_DISP_NAME(ui1_item_id))) ;
            c_wgl_move(h_item,pt_rect,WGL_NO_AUTO_REPAINT/*WGL_SYNC_AUTO_REPAINT*/);
            break ;
    default:
        NAV_ASSERT(0) ;
        //BANNER_CHK_FAIL (NAVR_FAIL) ;
        break;
    }

if(0){
    /*just for debug item position should define border stype to WGL_BORDER_UNIFORM in layout source file*/
    WGL_COLOR_INFO_T            t_clr_info;
    if(BANNER_ITM_TIMER_24 == ui1_item_id ||
         BANNER_ITM_WIFI_TXT == ui1_item_id||
         BANNER_ITM_ASPECT == ui1_item_id||
         BANNER_ITM_RESOLUTION_TXT == ui1_item_id||
         BANNER_ITM_WIFI_ICON == ui1_item_id ||
         BANNER_ITM_DOLBY_AUDIO== ui1_item_id||
#if (CUSTOMER == VIZIO)
         BANNER_ITM_HEADPHONES== ui1_item_id||
#endif
         BANNER_ITM_DOLBY_VISION == ui1_item_id
         )
        {
            /* set background color of main_frame */
            t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
            t_clr_info.u_color_data.t_standard.t_enable    = COLOR_LIGHT_BLUE_NORMAL;
            t_clr_info.u_color_data.t_standard.t_disable   = COLOR_LIGHT_BLUE_HLT;
            t_clr_info.u_color_data.t_standard.t_highlight = COLOR_GRAY_128;
            c_wgl_do_cmd(
                  h_item,
                  WGL_CMD_GL_SET_BDR_COLOR,
                  WGL_PACK(WGL_CLR_BK),
                  WGL_PACK(&t_clr_info));
       }
}
    return NAVR_OK;
}

static INT32 _banner_view_reset()
{
    BANNER_ITEM_INFO_T*          pt_item_info  = NULL;
    BOOL                         b_visible     = FALSE;
    UINT8                        ui1_item_id = 0;
    //BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" current state is %s\n",GET_STATE_DISP_NAME(t_g_view.t_refresh_buff.ui1_state_id)) ) ;
        /*auto arrange items left*/
        for (ui1_item_id = 0; ui1_item_id < BANNER_ITM_CUST_TOPMOST_BEGIN; ++ui1_item_id)
        {
             pt_item_info = banner_get_item_info (ui1_item_id) ;
              c_wgl_get_visibility(*(pt_item_info->ph_handle), &b_visible);
              // BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("item[%s] visiable ? %s\n",GET_ITEM_DISP_NAME(ui1_item_id),b_visible ? "YES":"NO"));
             if(b_visible)
             {
                 banner_item_lock();
                 _banner_mode_text_item_update (ui1_item_id) ;
                  banner_item_unlock();
             }
        }

        /*auto arrange items right */
          for (ui1_item_id = BANNER_ITM_LAST_VALID_ENTRY - 1; ui1_item_id >= BANNER_ITM_CUST_TOPMOST_BEGIN; -- ui1_item_id)
          {
              pt_item_info = banner_get_item_info (ui1_item_id) ;
              c_wgl_get_visibility(*(pt_item_info->ph_handle), &b_visible);
              if(b_visible)
              {
                  banner_item_lock();
                 _banner_mode_text_item_update (ui1_item_id) ;
                  banner_item_unlock();
              }
           }
   return NAVR_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _repaint_view
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
extern BOOL b_is_channel_change;
static INT32 _repaint_view (VOID)
{
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner repaint] %s %d start \n",__FUNCTION__,__LINE__));

    BANNER_VIEW_T*              pt_view = &t_g_view ;
    BANNER_UPDATE_NFY_T         t_nfy_data ;
    UINT8                       ui1_state_for_repaint = NAV_BNR_STATE_NULL_STATE_NAME ;
    BNR_ITEM_SET_T              t_items_for_repaint = 0 ;
    BNR_ITEM_SET_T              t_items_for_notify = 0 ;

    HANDLE_T    h_item = NULL_HANDLE;
    HANDLE_T    h_item_ch = NULL_HANDLE;
    UINT8       ui1_item_type = 0;
    BOOL        b_visible = FALSE;
    BOOL        b_visible_old = FALSE;

    //hide logo for not overlap
    banner_hide_sidebar();

    nav_bnr_state_get_item_widget (BANNER_ITM_FRM_CH, &h_item_ch, &ui1_item_type);
    nav_bnr_state_get_item_widget (BANNER_ITM_FRM_INF, &h_item, &ui1_item_type);
    c_wgl_get_visibility(h_item, &b_visible_old);
    c_wgl_get_visibility(h_item_ch, &b_visible);

    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" current state is %s(%d) t_mask = 0x%x\n",
        GET_STATE_DISP_NAME(t_g_view.t_refresh_buff.ui1_state_id),
        t_g_view.t_refresh_buff.ui1_state_id,
        pt_view->t_refresh_buff.t_mask)) ;
    /* SPECIAL_NOTE_001 :
          * when view updated, it will notify to custom part,
          * after receiving the notification, custom part MAY do somthing which will
          * change the view again, so we need use while(still_have_buffered view) to
          * check if there is any other buffered content need be updated.
      */
    if (NAV_BNR_STATE_NULL_STATE_NAME == pt_view->t_refresh_buff.ui1_state_id &&
        (BNR_ITEM_SET_T)0 == pt_view->t_refresh_buff.t_mask)
    {
        /* nothing need repaint */
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" nothing need to be repainted!!!\n")) ;
        return NAVR_OK ;
    }
    /* apply buffered items */
    {
        while (pt_view->t_refresh_buff.t_mask)
        {
            /* backup the mask for notify porpose */
            t_items_for_notify = pt_view->t_refresh_buff.t_mask ;

            /* update repaint mask */
            t_items_for_repaint |= pt_view->t_refresh_buff.t_mask ;

            /* after updating the item, clear it from refresh buff */
            BANNER_LOG_ON_FAIL (_update_buffered_items (_CLEAR_FROM_REFRESH_BUFF)) ;

            /* pre-update process */
            if (pt_view->pf_reporter)
            {
                /* Do NOT use pt_view->t_refresh_buff.t_mask as it has been cleared already */
                c_memset (&t_nfy_data, 0, sizeof (BANNER_UPDATE_NFY_T)) ;
                t_nfy_data.e_nfy_type = BANNER_NFY_TYPE_PRE_UPDATE_VIEW ;
                t_nfy_data.u_nfy_data.t_view_updated_mask_pre = t_items_for_notify ;
                BANNER_CHK_FAIL (pt_view->pf_reporter (t_nfy_data)) ;
            }
        }
    }

     /* apply buffered state */
    if (NAV_BNR_STATE_NULL_STATE_NAME != pt_view->t_refresh_buff.ui1_state_id )
    {
        /* backup the repainted state name */
        ui1_state_for_repaint = pt_view->t_refresh_buff.ui1_state_id ;

        /* state-updating only changes the item's visibility(no content changed). need NOT notify */
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" update buffered state [%s] to view\n",GET_STATE_DISP_NAME (ui1_state_for_repaint) ) ) ;

        /* after updating the state, clear it from refresh buff */
        BANNER_LOG_ON_FAIL (_update_buffered_state (_CLEAR_FROM_REFRESH_BUFF));

        _banner_view_reset();
    }
    /* do repaint operation if there has only one item need repainted,
     * just do a singale repaint, otherwise repaint the root frame
     */

    BANNER_ITEM_INFO_T * pt_item_info;

   if (pt_view->h_bnr_root_frame)
    {
        c_wgl_get_visibility(h_item, &b_visible);

        if (!b_visible)
        {
            if ((!b_visible_old || a_menu_is_resume())
                && !nav_banner_get_from_info_key())
            {
              pt_item_info = banner_get_item_info (BANNER_ITM_FRM_CH) ;
              if(b_is_channel_change)
              {
                 BANNER_CHK_FAIL (c_wgl_repaint (h_item_ch, pt_item_info->pt_rect, FALSE)) ;
              }
              else
              {
                  BANNER_CHK_FAIL (c_wgl_repaint (h_item_ch, pt_item_info->pt_rect, TRUE)) ;
              }
            }
            else
            {
                BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("repainth_bnr_root_frame(0x%x)\n",pt_view->h_bnr_root_frame)) ;
                BANNER_CHK_FAIL (c_wgl_repaint (pt_view->h_bnr_root_frame, NULL, TRUE));
            }
        }
        else
        {
            if(nav_banner_get_from_channel_key() && TRUE == b_visible_old)
            {
                 /*zoom mode --> repaint info banner ui*/
                 BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("repaint BANNER_ITM_FRM_CH \n")) ;
                 pt_item_info = banner_get_item_info (BANNER_ITM_FRM_CH);
                 BANNER_CHK_FAIL (c_wgl_repaint (h_item_ch, pt_item_info->pt_rect, TRUE)) ;
            }
            else
            {
                BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("repaint h_bnr_root_frame to(0x%x)\n",pt_view->h_bnr_root_frame)) ;
                /* repaint whole banner */
                BANNER_CHK_FAIL (c_wgl_repaint (pt_view->h_bnr_root_frame, NULL, TRUE));
            }
        }
    }

    /* post-update process */
    if (pt_view->pf_reporter)
    {
        /* Do NOT use pt_view->t_refresh_buff.t_mask as it has been reset already */
        c_memset (&t_nfy_data, 0, sizeof (BANNER_UPDATE_NFY_T)) ;
        t_nfy_data.e_nfy_type = BANNER_NFY_TYPE_POST_UPDATE_VIEW ;
        t_nfy_data.u_nfy_data.t_view_updated_mask_post = t_items_for_repaint ;
        BANNER_CHK_FAIL (pt_view->pf_reporter (t_nfy_data)) ;
    }
#ifdef APP_TTS_SUPPORT
    /* send string to tts */
    /*move this to here should buy some time when tts on*/
    banner_view_tts_fill_string();
#endif

    //start mm update timer
    //banner_view_mm_update_start_timer();

    //scroll name if need
    banner_view_name_update_start_timer();

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner repaint] %s %d end\n",__FUNCTION__,__LINE__));

    return NAVR_OK ;
}

static VOID _banner_view_update_curr_tv_name(VOID)
{
    CHAR           s_cast_name[128+1]={0};
    UINT32         ui4_cast_name_len = 128+1;
    UTF16_T        w2s_tv_cast_name[25+1] = {0};

    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" \n") );

     /* get cast tv device name after power on or do server reset */
    if((0 == a_cfg_custom_get_tv_name(s_cast_name, &ui4_cast_name_len) || 0 == a_cfg_custom_get_cast_name(s_cast_name, &ui4_cast_name_len))
        && strlen(s_cast_name) > 0 )
    {
        c_uc_ps_to_w2s(s_cast_name, w2s_tv_cast_name, sizeof(w2s_tv_cast_name));
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("get tv name \"%s\"\n ",s_cast_name));
        banner_view_update_item (BANNER_ITM_TV_NAME,w2s_tv_cast_name,NULL_HANDLE, UP_TO_VIEW_AT_ONCE);
    }
    else
    {
       DBG_LOG_PRINT(("[Banner V][%s %d] failed to get tv name \n ",__FUNCTION__,__LINE__));
    }
}

static INT32 _banner_view_update_curr_cast_name(VOID)
{
    UTF16_T*                    pw2s_text = NULL ;      /* for text item */
    INT32                       i4_ret = 0;
    TV_WIN_ID_T                 t_win_id;
    ISL_REC_T                   t_isl_rec;
    UTF16_T                     w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    CHAR                        alias_name[(APP_CFG_CUSTOM_INP_NAME_LEN+1)*2] = {0};


    i4_ret = a_tv_get_focus_win(&t_win_id);
    if (0 != i4_ret)
    {
        DBG_LOG_PRINT(("%s,%d, a_tv_get_focus_win error=[%d]\n",__FUNCTION__,__LINE__,i4_ret));
    }
    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,
                                        &t_isl_rec);
    if (0 != i4_ret)
    {
        DBG_LOG_PRINT(("%s,%d, a_tv_get_isl_rec_by_win_id error=[%d]\n",__FUNCTION__,__LINE__,i4_ret));
    }

    a_isl_get_display_name_ex(&t_isl_rec, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);
    c_uc_w2s_to_ps(w2s_alias,alias_name,sizeof(alias_name));

    BANNER_LOG(_BANNER_LOG_TYPE_VIEW,("t_isl_rec.ui1_internal_id=%d,t_isl_rec.ui1_id=%d alias_name:%s\n",\
        t_isl_rec.ui1_internal_id,t_isl_rec.ui1_id,alias_name));

    if(t_isl_rec.ui1_internal_id == 0)
    {
        pw2s_text   =   BANNER_TEXT("SMARTCAST ");
    }
    else
    {
        pw2s_text = a_isl_get_display_name(&t_isl_rec);

        //scroll name if need
        if(c_uc_w2s_strlen(pw2s_text) > BANNEER_SCRL_INPUT_SRC_NAME_MAX)
        {
            banner_view_set_name_update_flag(TRUE);
            banner_view_update_scrl_banner_name(pw2s_text,c_uc_w2s_strlen(pw2s_text));
        }
        else
        {
            banner_view_set_name_update_flag(FALSE);
        }
    }

    //show cast name and icon
    banner_view_update_item (BANNER_ITM_CH_NAME, pw2s_text, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE);
    if(a_rest_app_check_install_airplay() && a_rest_app_get_current_app_is_semaphore() == 0)
    {
         banner_view_update_item (BANNER_ITM_IPTS_ICON, NULL_HANDLE, h_g_nav_banner_new_input_airplay_pic, !UP_TO_VIEW_AT_ONCE);
    }
    else
    {
         banner_view_update_item (BANNER_ITM_IPTS_ICON, NULL_HANDLE, h_g_nav_banner_new_input_new_cast_pic, !UP_TO_VIEW_AT_ONCE);
    }

    do
    {
        VSH_SRC_RESOLUTION_INFO_T   t_resolution;
        TV_WIN_ID_T                 e_tv_win_id = TV_WIN_ID_MAIN ;
        HANDLE_T                    h_svctx;

        pw2s_text = BANNER_TEXT("Normal");

        if(NAVR_OK != nav_get_svctx_handle(e_tv_win_id, &h_svctx))
        {
            DBG_LOG_PRINT(("%s,%d,nav_get_svctx_handle(win=%d) failed, i4_ret=%d.\r\n",
                            __FUNCTION__,__LINE__, e_tv_win_id, i4_ret));
            return NAVR_FAIL;
        }

        c_memset(&t_resolution, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

        if(0 != c_svctx_get_video_src_resolution(h_svctx,&t_resolution))
        {
            DBG_LOG_PRINT(("%s,%d [get resolution fail]\n",__FUNCTION__,__LINE__));
            break;
        }
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" cast timing = %d \n",t_resolution.ui2_orig_height)) ;

        if(t_resolution.ui2_orig_height == 0 && !banner_check_mi_mm_playing() && c_strcmp(alias_name,"SMARTCAST"))
        {
            pw2s_text = NULL;
        }
        else
        {
#ifdef APP_HDR_SUPPORT
            SCC_VID_HDR_TYPE_T t_hdr_type = a_acfg_cust_get_video_type();

            if(t_hdr_type == SCC_VID_PQ_DOVI)
            {
                pw2s_text = NULL;
                banner_view_update_item(BANNER_ITM_DOLBY_VISION, BANNER_TEXT(""), h_g_banner_slider_icon_dolby_vision,UP_TO_VIEW_AT_ONCE) ;
            }
            else if(t_hdr_type == SCC_VID_PQ_HDR10)
            {
                //pw2s_text = BANNER_TEXT("HDR10");
                pw2s_text = L"";
                banner_view_update_item(BANNER_ITM_DOLBY_VISION, BANNER_TEXT(""), h_g_banner_slider_icon_hdr10,UP_TO_VIEW_AT_ONCE) ;
            }
            else if(t_hdr_type == SCC_VID_PQ_HDR10PLUS)
            {
                pw2s_text = BANNER_TEXT("HDR10+");
            }
            else if (t_hdr_type == SCC_VID_PQ_HLG)
            {
                //pw2s_text = BANNER_TEXT("HLG");
                pw2s_text = L"";
                banner_view_update_item(BANNER_ITM_DOLBY_VISION, BANNER_TEXT(""), h_g_banner_slider_icon_hlg,UP_TO_VIEW_AT_ONCE) ;
            }
            else
            {
                pw2s_text = BANNER_TEXT("Normal");
            }
#else
            pw2s_text = BANNER_TEXT("Normal");
#endif
        }
        banner_view_update_item (BANNER_ITM_ASPECT, pw2s_text, NULL_HANDLE, UP_TO_VIEW_AT_ONCE);
    }while(0);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_init (
    BANNER_T*                           pt_this,
    HANDLE_T                            h_root_frame,
    banner_state_item_update_listener   pf_reporter
    )
{
    BANNER_VIEW_T*                      pt_view = &t_g_view;

    c_memset(pt_view, 0, sizeof(BANNER_VIEW_T));

    pt_view->pf_reporter          =       pf_reporter ;
    pt_view->h_bnr_root_frame     =       h_root_frame ;
    pt_view->h_bnr_siderbar_frame = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_FRM_SIDER_BAR);
    /* initial timer */
    BANNER_CHK_FAIL (c_timer_create (&pt_view->h_update_view_timer)) ;

    /* initial timer */
    BANNER_CHK_FAIL (c_timer_create (&pt_view->h_delay_show_timer)) ;
    BANNER_CHK_FAIL (c_timer_create (&pt_view->h_siderbar_auto_hide_timer));
    BANNER_CHK_FAIL (c_timer_create (&pt_view->h_siderbar_delay_show_timer));
    BANNER_CHK_FAIL (c_timer_create (&pt_view->h_mm_update_timer));
    BANNER_CHK_FAIL (c_timer_create (&pt_view->h_name_update_timer)) ;

    b_g_update_view_timer_valid = FALSE ;

    /* clean state refresh buff */
    BANNER_LOG_ON_FAIL (_clean_from_refresh_buff (_REFRESH_TYPE_STATE, 0)) ;

    /* clean item refresh buff */
    pt_view->t_refresh_buff.t_mask = 0;

    /* hide root frame */
    if (pt_view->h_bnr_root_frame)
    {
        BANNER_LOG_ON_FAIL (c_wgl_set_visibility (pt_view->h_bnr_root_frame, WGL_SW_HIDE_RECURSIVE)) ;
    }

    /* hide sidebar logo frame */
    if (pt_view->h_bnr_siderbar_frame)
    {
        BANNER_LOG_ON_FAIL (c_wgl_set_visibility (pt_view->h_bnr_siderbar_frame, WGL_SW_HIDE_RECURSIVE)) ;
    }

#ifdef APP_TTS_SUPPORT
    /* set tts handle to NULL. */
    INT32 i4_ret = 0;
    i4_ret = c_timer_create(&(pt_view->h_tts_timer));
    if (i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("{Banner TTS}%s ERROR(%d): c_timer_create fail! i4_ret=%d.\n",__FUNCTION__,__LINE__,i4_ret));
    }
    pt_view->t_tts_updated_item_mask = 0;
#endif
    memset(pt_view->t_refresh_buff.t_item_buff,0,sizeof(pt_view->t_refresh_buff.t_item_buff));

    c_wgl_get_coords(pt_view->h_bnr_siderbar_frame,WGL_COORDS_SCREEN,&pt_view->t_animate_in);

    c_memcpy(&pt_view->t_animate_out,&pt_view->t_animate_in,sizeof(GL_RECT_T));
    pt_view->t_animate_out.i4_left  = 1920;
    pt_view->t_animate_out.i4_right = pt_view->t_animate_out.i4_left + 100;

#ifdef APP_BANNER_AMIN
    /*init animation info*/
    pt_view->t_animate_ui_max.i4_left    = NAV_BANNER_ROOT_FRM_WGL_SX;
    pt_view->t_animate_ui_max.i4_top     = NAV_BANNER_ROOT_FRM_WGL_SY;
    pt_view->t_animate_ui_max.i4_right   = NAV_BANNER_ROOT_FRM_WGL_EX;
    pt_view->t_animate_ui_max.i4_bottom  = NAV_BANNER_ROOT_FRM_WGL_EY;

    c_memcpy(&pt_view->t_animate_ui_min,&pt_view->t_animate_ui_max,sizeof(GL_RECT_T));
    pt_view->t_animate_ui_min.i4_top = -(NAV_BANNER_ROOT_FRM_WGL_EY - NAV_BANNER_ROOT_FRM_WGL_SY) - 2;
    pt_view->t_animate_ui_min.i4_bottom = -2;
#endif
    /* Set Font */

    i4_ret = c_fe_create_font(SN_FONT_DEFAULT,
                             FE_FNT_SIZE_CUSTOM,
                              FE_FNT_STYLE_REGULAR,
                              FE_CMAP_ENC_UNICODE,
                              &t_g_wdk_widget_common_res[0].h_font_handle);
    BANNER_LOG_ON_FAIL(i4_ret);
    i4_ret = c_fe_set_custom_size(t_g_wdk_widget_common_res[0].h_font_handle,42);
    BANNER_LOG(_BANNER_LOG_TYPE_MESSAGE,(" zoom x_fe_set_custom_size i4_ret=%d.\n", i4_ret));

    i4_ret = c_fe_create_font(SN_FONT_DEFAULT,
                              FE_FNT_SIZE_CUSTOM,
                              FE_FNT_STYLE_REGULAR,
                              FE_CMAP_ENC_UNICODE,
                              &t_g_wdk_widget_common_res[1].h_font_handle);
     BANNER_LOG_ON_FAIL(i4_ret);

     i4_ret = c_fe_set_custom_size(t_g_wdk_widget_common_res[1].h_font_handle,21);
     BANNER_LOG(_BANNER_LOG_TYPE_MESSAGE,(" zoom x_fe_set_custom_size i4_ret=%d.\n", i4_ret));
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_deinit (VOID)
{
    BANNER_VIEW_T*       pt_view     = &t_g_view;
    INT32                i4_font_idx;

    pt_view->t_refresh_buff.t_mask = 0;

    BANNER_LOG_ON_FAIL (_clean_from_refresh_buff (_REFRESH_TYPE_STATE, 0)) ;

    if (c_handle_valid(&pt_view->h_delay_show_timer) == TRUE)
    {
        BANNER_CHK_FAIL (c_timer_delete (&pt_view->h_delay_show_timer)) ;
    }
    if (c_handle_valid(&pt_view->h_siderbar_auto_hide_timer) == TRUE)
    {
        BANNER_CHK_FAIL (c_timer_delete (&pt_view->h_siderbar_auto_hide_timer)) ;
    }
    if (c_handle_valid(&pt_view->h_siderbar_delay_show_timer) == TRUE)
    {
        BANNER_CHK_FAIL (c_timer_delete (&pt_view->h_siderbar_delay_show_timer)) ;
    }
    if (c_handle_valid(&pt_view->h_mm_update_timer) == TRUE)
    {
        BANNER_CHK_FAIL (c_timer_delete (&pt_view->h_mm_update_timer)) ;
    }
    if (c_handle_valid(&pt_view->h_name_update_timer) == TRUE)
    {
        BANNER_CHK_FAIL (c_timer_delete (&pt_view->h_name_update_timer)) ;
    }

#ifdef APP_TTS_SUPPORT
    BANNER_VIEW_T*              pt_this = &t_g_view ;
    if (c_handle_valid(pt_this->h_tts_timer) == TRUE)
    {
        c_timer_delete(pt_this->h_tts_timer);
    }
#endif
    for(i4_font_idx = 0;i4_font_idx < sizeof(t_g_wdk_widget_common_res)/sizeof(t_g_wdk_widget_common_res[0]);i4_font_idx++)
    {
        if (t_g_wdk_widget_common_res[i4_font_idx].h_font_handle != NULL_HANDLE)
        {
#ifdef VIZIO_FUSION_SUPPORT
            c_fe_delete_font(t_g_wdk_widget_common_res[i4_font_idx].h_font_handle);
#endif
            t_g_wdk_widget_common_res[i4_font_idx].h_font_handle = NULL_HANDLE;
            BANNER_LOG(_BANNER_LOG_TYPE_MESSAGE,(" delete fe font \n"));
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_set_focus
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_set_focus(VOID)
{
    BANNER_VIEW_T*              pt_view = &t_g_view ;

    if (pt_view->h_bnr_root_frame)
    {
        BANNER_CHK_FAIL (c_wgl_set_focus (pt_view->h_bnr_root_frame, FALSE)) ;
    }
    else
    {
        DBG_ERROR(("<NAV> BANNER NEED A ROOT FRAME!!!!:%s:%d%d\r\n", __FILE__, __LINE__, -128));
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_update_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_update_state(
    UINT8                       ui1_state_id
    )
{
    if (NULL == banner_get_state_info (ui1_state_id))
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* send to refresh buff */
    BANNER_CHK_FAIL (_send_to_refresh_buff (
                                _REFRESH_TYPE_STATE,
                                ui1_state_id,
                                0, NULL, NULL_HANDLE    /* valid when _REFRESH_TYPE_STATE */
                                )) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_update_item
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_update_item (
    UINT8                       ui1_item_id,
    UTF16_T*                    pw2s_text,          /* for text item */
    HANDLE_T                    h_img,              /* for icon or frame item */
    BOOL                        b_up_to_view_at_once
    )
{
    if (NULL == banner_get_item_info (ui1_item_id))
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    /* send to refresh buff */
    BANNER_CHK_FAIL (_send_to_refresh_buff (_REFRESH_TYPE_ITEM,
                                            0 ,                 /* valida when _REFRESH_TYPE_STATE */
                                            ui1_item_id, pw2s_text, h_img)) ;

    /* schedule a refresh task */
    BANNER_CHK_FAIL (banner_view_refresh (b_up_to_view_at_once)) ;

    return NAVR_OK ;
}

#ifdef APP_BANNER_AMIN
static INT32 banner_anim_start_animation(BOOL b_show)
{
    BANNER_VIEW_T*   pt_view  = &t_g_view ;
     WGL_ANIMATION_DATA_T   t_anim_data;

    /* Check move animation start, end position  handle*/
    if (NULL_HANDLE == pt_view->h_bnr_root_frame)
    {
        return NAVR_INV_ARG;
    }

    do
    {
        INT32 i4_ret;
        WGL_ANIM_CONTEXT_T e_wdk_anim_context = ANIM_CONTEXT_APP_SYNC;

        /* Clear animation data */
        c_memset (&t_anim_data, 0, sizeof (WGL_ANIMATION_DATA_T));

        GL_RECT_T*   pt_rect_from = b_show ? &pt_view->t_animate_ui_min : &pt_view->t_animate_ui_max;
        GL_RECT_T*   pt_rect_to   = b_show ? &pt_view->t_animate_ui_max : &pt_view->t_animate_ui_min;
        BANNER_LOG(_BANNER_LOG_TYPE_VIEW,(" from [L: %d ,R: %d ,T:%d B:%d]\r\n",pt_rect_from->i4_left,pt_rect_from->i4_right,pt_rect_from->i4_top,pt_rect_from->i4_bottom));
        BANNER_LOG(_BANNER_LOG_TYPE_VIEW,(" to   [L: %d ,R: %d ,T:%d B:%d]\r\n",pt_rect_to->i4_left,pt_rect_to->i4_right,pt_rect_to->i4_top,pt_rect_to->i4_bottom));
        /* Stop origional animation firstly */
        c_wgl_end_animation (pt_view->h_bnr_root_frame, NULL, NULL);

        /* Move animation widget */
        if (WGLR_OK != (i4_ret = c_wgl_move (pt_view->h_bnr_root_frame,
                             pt_rect_from,
                             WGL_NO_AUTO_REPAINT)))
        {
            DBG_LOG_PRINT (("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
            break;
        }

        /* begin animation */
        t_anim_data.ui2_count = 1;

        /* Alloc memory for animation control data */
        t_anim_data.pt_anim_data = c_mem_alloc((sizeof(WGL_ANIM_DATA_INFO) * t_anim_data.ui2_count));
        t_anim_data.pt_path_mode = c_mem_alloc((sizeof(WGL_ANIM_PATH_DATA_T) * t_anim_data.ui2_count));
        if((NULL == t_anim_data.pt_anim_data) ||
           (NULL == t_anim_data.pt_path_mode))
        {
            DBG_LOG_PRINT(("[%s %d] failed to malloc morery\n", __FUNCTION__, __LINE__));
            break;
        }

        c_memset(t_anim_data.pt_anim_data,0,sizeof(WGL_ANIM_DATA_INFO));
        c_memset(t_anim_data.pt_path_mode,0,sizeof(WGL_ANIM_PATH_DATA_T));

        /* Initialize animation path mode */
        t_anim_data.ui4_flag = WGL_ANIM_DATA_FLAG_PATH_MODE_INF;
        t_anim_data.pt_path_mode->ui2_anim_type = WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_path_mode->ui2_total_steps = (BANNER_STATE_PDCH == t_g_view.t_refresh_buff.ui1_state_id ||
                                                     BANNER_STATE_PCH  == t_g_view.t_refresh_buff.ui1_state_id) ? 10 : 20;
        t_anim_data.pt_path_mode->ui2_frame_interval = 50;
        t_anim_data.pt_path_mode->ui4_start_tick = 0;
        t_anim_data.pt_path_mode->pf_type_cb = NULL;

        /* Initialize animation data info */
        t_anim_data.ui4_flag |= WGL_ANIM_DATA_FLAG_DATA_INF;
        t_anim_data.pt_anim_data->ui2_anim_type |= WGL_ANIM_TYPE_MOVE;

        t_anim_data.pt_anim_data->u_data.t_move.i2_start_x = pt_rect_from->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_start_y = pt_rect_from->i4_top;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_x   = pt_rect_to->i4_left;
        t_anim_data.pt_anim_data->u_data.t_move.i2_end_y   = pt_rect_to->i4_top;

        /* Show animation widget */
        c_wgl_set_visibility(pt_view->h_bnr_root_frame, WGL_SW_NORMAL);

        /* Start animation */
        if (WGLR_OK != (i4_ret = c_wgl_start_animation(pt_view->h_bnr_root_frame,
                                      &t_anim_data,
                                      e_wdk_anim_context)))
        {
            DBG_LOG_PRINT(("[%s] Error=%d @ File:%s(L%d)\n", __FUNCTION__, i4_ret, __FILE__, __LINE__));
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
    return NAVR_OK;
}

static VOID _nav_banner_anim_handler(VOID*   pv_arg1,
                                           VOID*   pv_arg2,
                                           VOID*   pv_arg3
    )
{
    BOOL g_anim = (UINT32)pv_arg1 > 0 ? TRUE : FALSE;
    banner_anim_start_animation(g_anim);
}

static VOID _banner_view_show(BOOL anim_in)
{
   u4_g_banner_state = anim_in ? ANIM_IN : ANIM_OUT;
   /* execute in timer's thread context */
    nav_request_context_switch(_nav_banner_anim_handler,
                                (VOID*)u4_g_banner_state,
                                NULL,
                                NULL);
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_hide(VOID)
{
    BANNER_VIEW_T*              pt_view = &t_g_view ;
    MMP_BE_BROWSER_STATUS_T     e_mmp_browser_status = a_mmp_be_get_browser_status();
    BOOL                        b_mmp_full_screen = FALSE;
    BOOL                        b_visible = FALSE;

    //stop mm_update_stop_timer
    //banner_view_mm_update_stop_timer();

    //stop name scroll timer
    banner_view_name_update_stop_timer();

#ifdef APP_ZOOM_MODE_SUPPORT
    banner_set_first_power_on_state(FALSE);
#endif

    BANNER_CHK_FAIL (c_timer_stop (pt_view->h_update_view_timer)) ;
    BANNER_CHK_FAIL (c_timer_stop (pt_view->h_delay_show_timer)) ;

    b_g_update_view_timer_valid = FALSE ;
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);
    c_wgl_get_visibility(pt_view->h_bnr_root_frame, &b_visible);
    pt_view->b_is_on_showing = FALSE ;
    if(TRUE == b_visible && NULL_HANDLE != pt_view->h_bnr_root_frame)
    {
         /* hidden operation is higher than pt_view->b_ui_frozen */
        b_mmp_full_screen = a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP)
                            && ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == e_mmp_browser_status)
                            ||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == e_mmp_browser_status)
                            ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == e_mmp_browser_status)
                            ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == e_mmp_browser_status));

        if (!b_mmp_full_screen)
        {
            BANNER_CHK_FAIL (c_wgl_float(pt_view->h_bnr_root_frame, FALSE, FALSE)) ;
        }
#ifdef APP_BANNER_AMIN
        if(nav_banner_get_hide_mode())
           _banner_view_show(FALSE);
#endif
        BANNER_CHK_FAIL (c_wgl_set_visibility (pt_view->h_bnr_root_frame,WGL_SW_HIDE_RECURSIVE)) ;
        BANNER_CHK_FAIL (c_wgl_repaint (pt_view->h_bnr_root_frame, NULL, TRUE)) ;
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[banner view] banner VIEW was hide\n")) ;
        BANNER_LOG_ON_FAIL (_clean_from_refresh_buff (_REFRESH_TYPE_STATE, 0));
#ifdef APP_BANNER_AMIN
        nav_banner_set_hide_mode(TRUE);
#endif
    }
    nav_banner_set_from_double_info_key(FALSE);
    nav_banner_set_from_ch_num_key(FALSE);

#ifdef APP_TTS_SUPPORT
    /* banner hide need reset flag. */
    pt_view->t_tts_updated_item_mask = 0;
    g_t_tts_updated_item_mask  = FALSE;
    g_t_tts_banenr_detail_mask = FALSE;
#endif
    banner_view_tv_info_updeted_erase();
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_set_visible
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_set_visible (
    BOOL                        b_show
    )
{
    BANNER_VIEW_T*              pt_view = &t_g_view ;
    BOOL                        b_allow_to_show = FALSE ;
    TV_WIN_ID_T                 e_tv_win_id;
    CHAR                        s_disp_name[33] = {0};
    UINT8                       ui1_input_id = 0;
    ISL_REC_T                   t_isl_rec;

    MMP_BE_BROWSER_STATUS_T  e_mmp_browser_status = a_mmp_be_get_browser_status();
    BOOL    b_mmp_full_screen = FALSE;
    BOOL    b_float = TRUE;

    banner_item_lock();

#ifdef APP_EMANUAL_SUPPORT
    UINT8   ui1_val = ICL_EMANUAL_STATUS_OFF;
    SIZE_T  sz_emanual = ICL_RECID_EMANUAL_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_EMANUAL_STATUS, ICL_RECID_EMANUAL_STATUS),
              (VOID*)&ui1_val, &sz_emanual);
#endif

    if(pt_view->b_is_on_showing == b_show)
    {
         BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("it is under %s  do nothing\n",b_show == TRUE ? "show":"hide")) ;
         banner_item_unlock();
         return NAVR_OK;
    }
    nav_get_focus_id(&e_tv_win_id);

    b_allow_to_show = (a_banner_allow_to_show () && b_show && b_is_banner_enable) ;
    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" a_banner_allow_to_show ()=> %d b_show=>%d b_is_banner_enable=> %d\n",a_banner_allow_to_show (),b_show,b_is_banner_enable)) ;

    if (b_allow_to_show)
    {
        if (b_g_is_delay_show_banner == FALSE)
        {
            /* hide exec comps first */
            BANNER_LOG_ON_FAIL (nav_hide_components(COMP_EXEC_SET_BANNER));
        }
        a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        a_cfg_get_input_src(s_disp_name, &ui1_input_id);
        a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("s_disp_name => \"%s\" ui1_input_id = %d,t_isl_rec.e_src_type = 0x%x,e_video_type = 0x%x\n",
                    s_disp_name,
                    ui1_input_id,
                    t_isl_rec.e_src_type,
                    t_isl_rec.t_avc_info.e_video_type)) ;
        //update tv name
        _banner_view_update_curr_tv_name();
        if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)
        {
            if(t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
            {//SMART CAST
                BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" cast ipt src show item \r\n")) ;
                //update inps in cast status
                _banner_view_update_curr_cast_name();
            }
            nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);
        }
        BANNER_LOG_ON_FAIL (c_wgl_set_visibility(t_g_view.h_bnr_siderbar_frame,WGL_SW_HIDE_RECURSIVE));

        /*zoom mode --> repaint info banner ui*/
        _banner_view_reset();

        /* banner view is activate ,set component visible-flag to on */
        BANNER_CHK_FAIL (nav_set_component_visible (NAV_COMP_ID_BANNER)) ;
    	pt_view->b_is_on_showing = TRUE;
    }
    else
    {
        BANNER_CHK_FAIL(nav_hide_components (NAV_COMP_ID_BANNER));
        pt_view->b_is_on_showing = FALSE;
    }
    banner_item_unlock();


    if (pt_view->h_bnr_root_frame)
    {
        b_float = b_allow_to_show;

        b_mmp_full_screen = a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP)
                            && ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == e_mmp_browser_status)
                            ||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == e_mmp_browser_status)
                            ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == e_mmp_browser_status)
                            ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == e_mmp_browser_status));

        if (a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP) == FALSE
            || b_mmp_full_screen
#ifdef APP_EMANUAL_SUPPORT
#ifdef APP_EMANUAL_SP6_SUPPORT
            || a_um_get_status_is_displaying()
#else
            || ICL_EMANUAL_STATUS_ON == ui1_val
#endif
#endif
            || (APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
            )
        {
            b_float = FALSE;
        }

        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("show banner => %s \n", b_allow_to_show ? "SHOW":"HIDE")) ;

        BANNER_CHK_FAIL (c_wgl_float(pt_view->h_bnr_root_frame,
                                     b_float,
                                     FALSE)) ;
        if (b_allow_to_show)
        {
            a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);
#ifdef APP_BANNER_AMIN
            if(BANNER_STATE_PDCH != t_g_view.t_refresh_buff.ui1_state_id)
            {
                 banner_view_hide_prog_detail_info();
            }
            BANNER_CHK_FAIL(c_wgl_set_visibility(nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ITM_CH),WGL_SW_NORMAL));
            _banner_view_show(TRUE);
#else

          BOOL b_connected_headphones = FALSE;
          char bt_mac[18] = {0};

          if( _json_bt_db_get_mac( BD_ARR_TYPE_CONNECTED, NULL, bt_mac ) == MENUR_OK )
              b_connected_headphones = TRUE;

          banner_cust_evt_handle_headphones( b_connected_headphones );

          BANNER_CHK_FAIL (c_wgl_set_visibility (pt_view->h_bnr_root_frame,b_allow_to_show ? WGL_SW_NORMAL : WGL_SW_HIDE));
#endif
        }
        else
        {
            a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);
        }
    }

    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[banner view]set banner VIEW's visibility to %d\n", b_allow_to_show)) ;

#ifdef APP_TTS_SUPPORT
    if (!b_allow_to_show)
    {
        /* banner hide need reset flag. */
        pt_view->t_tts_updated_item_mask = 0;
    }
    g_t_tts_updated_item_mask = TRUE;
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_freeze
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_freeze (
    BOOL                        b_freeze,
    UINT32                      ui4_proposer_id
    )
{
    static  UINT32              ui4_freeze_request = 0 ;
    BANNER_VIEW_T*              pt_view = &t_g_view ;

    if (b_freeze)
    {
        /* receive a freeze request, set the freeze flag for the proposer */
        ui4_freeze_request |= ui4_proposer_id ;
    }
    else
    {
        /* remove the freeze request according the proposer's id */
        ui4_freeze_request &= ~(ui4_proposer_id) ;
    }

    /* if there has no request for banner UI frozen, unfreeze view, otherwise keep it in frozen status */
    pt_view->b_ui_frozen = (ui4_freeze_request) ? TRUE : FALSE ;

    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[banner view] i4_freeze_flag = 0x%x\n", ui4_freeze_request)) ;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_refresh
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_view_refresh (BOOL   b_at_once)
{
    BANNER_VIEW_T*              pt_view = &t_g_view ;

    /* the rules of refreshing :
     * 1) star a timer to put off the repaintting if b_at_once == FALSE
     * 2) before refreshing, we need stop the h_update_view_timer first
     * 3) need NOT execute the repaint-operation if b_ui_frozen was set
     * 4) need NOT execute the repaint-operation if view part is un-displayed
     * 5) need NOT execute the repaint-operation if there has nothing need to be update
     */
    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("at once ? =>%s \n",b_at_once ? "YES":"NO"));
    /* rules 1 */
    if (!b_at_once)
    {
        if (TRUE == b_g_is_delay_show_banner  &&
           c_handle_valid(pt_view->h_delay_show_timer) == TRUE)
        {
            c_timer_stop(pt_view->h_delay_show_timer);
        }
        if(c_handle_valid(pt_view->h_update_view_timer) == TRUE)
            c_timer_stop(pt_view->h_update_view_timer);

        /* hold on current state before refreshing */
        BANNER_CHK_FAIL (c_timer_start (
                                pt_view->h_update_view_timer,
                                100 ,   /*0.1s*/
                                X_TIMER_FLAG_ONCE ,
                                _hode_on_bef_state_chg ,
                                NULL)) ;

        b_g_update_view_timer_valid = FALSE ;

        return NAVR_OK ;
    }

#ifdef SYS_MTKTVAPI_SUPPORT
    /* DTV00585482 */
    if(TRUE == gb_audio_info_nfy)
    {
        gb_audio_info_nfy_update = TRUE;
        /*a_mtktvapi_banner_notify_fct((INT32)MTKTVAPI_BANNER_MSG_SYS,
                         (INT32)MTKTVAPI_BANNER_MSG_SYS_AUDIO_INFO_NFY,
                         (VOID*)NULL,
                         (VOID*)NULL,
                         (VOID*)NULL,
                         (VOID*)NULL);*/
        gb_audio_info_nfy = FALSE;
    }
#endif
    /* rules 2 : stop timer */
    BANNER_CHK_FAIL (c_timer_stop (pt_view->h_update_view_timer)) ;
    b_g_update_view_timer_valid = FALSE ;

    /* rules 3 + 4 + 5 */
    if (!pt_view->b_is_on_showing ||
        pt_view->b_ui_frozen||
        ((BNR_ITEM_SET_T)0 == pt_view->t_refresh_buff.t_mask && NAV_BNR_STATE_NULL_STATE_NAME == pt_view->t_refresh_buff.ui1_state_id ))
    {
        return NAVR_OK ;
    }

    if (TRUE == b_g_is_delay_show_banner)
    {
        if(c_handle_valid(pt_view->h_delay_show_timer) == TRUE)
        {
            c_timer_stop(pt_view->h_delay_show_timer);
        }
        /* delay show banner. */
        BANNER_CHK_FAIL (c_timer_start (
                          pt_view->h_delay_show_timer,
                          i4_g_delay_show_time ,
                          X_TIMER_FLAG_ONCE ,
                          _delay_refresh_view ,
                          NULL));
        return NAVR_OK;
    }

    if(b_at_once)
    {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("banner_view_refresh delay ? =>%s \n",b_at_once == FALSE ? "YES":"NO"));
        _banner_view_start_repaint();

    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_is_on_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL banner_view_is_on_show (VOID)
{
    return t_g_view.b_is_on_showing  ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_tv_info_updeted_is_finished
 * Description  because new channel come up to screen has some delay, and it's
 *              hard to know how many message will update, so here choose the
 *              resolution, screen mode and audio stream info to decide if updated
 *              finished. Because these three show very slow base on the experience.
 * Input arguments
 * Output arguments
 * Returns
 *        TRUE : finished
 *        FALSE : not finish
 *---------------------------------------------------------------------------*/
BOOL banner_view_tv_info_updeted_is_finished(VOID)
{
    if((g_banner_view_updated_flag & 0x7) == 0x7)
        return TRUE;
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_tv_info_updeted_refresh
 * Description  g_banner_view_updated_flag used to juge whethaer element updated.
 *              this func update the flag.
 * Input arguments
 * Output arguments
 * Returns
 *        TRUE : finished
 *        FALSE : not finish
 *---------------------------------------------------------------------------*/
VOID banner_view_tv_info_updeted_update(NAV_BNR_UPDATED_ITEM_IDX_T e_item)
{
    g_banner_view_updated_flag |= (UINT8)1 << e_item;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_view_tv_info_updeted_erase
 * Description  g_banner_view_updated_flag used to juge whethaer element updated.
 *              this func erase the flag.
 *
 *              IMPORTANT:There maybe some problems of where to put this func,
 *              best choice is before service change msg or tv src changed msg,
 *              but if change channel very fast, these msg maybe loss.
 *
 * Input arguments
 * Output arguments
 * Returns
 *        TRUE : finished
 *        FALSE : not finish
 *---------------------------------------------------------------------------*/
VOID banner_view_tv_info_updeted_erase(VOID)
{
    g_banner_view_updated_flag = 0;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_view_set_delay_show_banner
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID a_banner_view_set_delay_show_banner (BOOL b_is_show, INT32 i4_delay_time)
{
    b_g_is_delay_show_banner = b_is_show;
    i4_g_delay_show_time     = i4_delay_time;
}

VOID a_banner_view_disable_delay_show_banner (VOID)
{
    BANNER_VIEW_T*    pt_view = &t_g_view ;

    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[Banner view]disable Delay show banner.\n"));
    if (c_handle_valid(pt_view->h_delay_show_timer) == TRUE)
    {
        c_timer_stop(pt_view->h_delay_show_timer);
    }

    b_g_is_delay_show_banner = FALSE;
    _banner_view_start_repaint();
}

#ifdef APP_TTS_SUPPORT

static VOID _banner_view_tts_reset_timer_count(VOID)
{
    timer_reset_count = 0;
}


static INT32 _banner_view_w2s_ch_r(
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
    CHAR  ps_a_tmp[2] = {0};

    c_uc_w2s_to_ps(pt_src_w2s, ps_src, sizeof(ps_src)-1);
    ps_a_tmp[0] = a;

    CHAR *p_str = ps_src;
    CHAR *p_next;
    while ((p_str = c_strtok(p_str, &ps_a_tmp, &p_next, &t_sz)) != NULL)
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
static INT32 _banner_view_ch_name_text_preprocess(
            UTF16_T *pt_src_w2s,
            UTF16_T *pt_dst_w2s,
            SIZE_T t_dst_size
            )
{
    CHAR  src[64] = {0};
    CHAR  dst[128] = {0};

    CHAR *p_found = NULL;
    CHAR *p_start = NULL;

    if (pt_src_w2s == NULL)
    {
        return NAVR_FAIL;
    }

    c_uc_w2s_to_ps(pt_src_w2s, src, 64);

    p_start = src;
    p_found = c_strchr(src, ' ');
    if (p_found != NULL)
    {
        p_start = p_found;
        p_found = NULL;
    }

    p_found = c_strchr(p_start, '-');
    if (p_found != NULL)
    {
        INT32 index = p_start - src;

        c_strncpy(dst, src, (SIZE_T)(p_start - src));

        while (p_start < p_found)
        {
            *(dst + index++) = *p_start;
            *(dst + index++) = ' ';
            p_start++;
        }

        while (*p_start != '\0')
        {
            *(dst + index++) = *p_start++;
        }

        *(dst + index) = '\0';

        if (c_strlen(dst) < t_dst_size)
        {
            return c_uc_ps_to_w2s(dst, pt_dst_w2s, t_dst_size);
        }
    }

    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_view_tts_get_item_string
 * Description
 *     This API used to get the banner item string.
 * Input arguments
 *     ps_str
 * Output arguments
 *     function return value
 * Returns
 *---------------------------------------------------------------------------*/
UINT32 _banner_view_tts_get_item_string (UTF16_T *ps_w2s_str, UTF16_T *ps_w2s_detail_str)
{
    UTF16_T            *p_w2s_str           = ps_w2s_str;
    UTF16_T            *p_w2s_detail_str    = ps_w2s_detail_str;
    UTF16_T             w2s_text[512]       ={0};
    UINT8               ui1_item_id         = 0;
    BOOL                b_is_updated        = FALSE;
    BANNER_ITEM_INFO_T* pt_item_info        = NULL;
    HANDLE_T            h_item              = NULL_HANDLE;
    BNR_ITEM_SET_T      t_bnr_item_set      = 0;
    BANNER_VIEW_T      *pt_view             = &t_g_view;
    BOOL                b_visible = FALSE;

    BANNER_LOG(_BANNER_LOG_TYPE_VIEW,("\n"));

    for (ui1_item_id = 0; ui1_item_id < BANNER_ITM_LAST_VALID_ENTRY; ui1_item_id++)
    {
        t_bnr_item_set = NAV_BNR_STATE_IDX_TO_ID(ui1_item_id);
        b_is_updated = (BOOL)(pt_view->t_tts_updated_item_mask & t_bnr_item_set);

        if (b_is_updated)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[banner tts]The item [%d] has been speeked, ignore it.\n", ui1_item_id)) ;
            continue;
        }

        /* search the specified items */
        if( NULL == (pt_item_info = banner_get_item_info (ui1_item_id)) ||
            NULL_HANDLE ==pt_item_info->ph_handle)
        {
            DBG_LOG_PRINT(("[Banner ][%s %d]something wrong to get item info \n",__FUNCTION__,__LINE__));
            continue;
        }

        h_item = *(pt_item_info->ph_handle) ;
        c_wgl_get_visibility(h_item, &b_visible);

        if(BANNER_ITEM_TYPE_TEXT == pt_item_info->e_item_type)
            BANNER_LOG(_BANNER_LOG_TYPE_VIEW,(" tts item[%s] visible => \"%s\"\n",GET_ITEM_DISP_NAME(ui1_item_id),b_visible ? "YES":"NO"));
        if (TRUE == b_visible && BANNER_ITEM_TYPE_TEXT == pt_item_info->e_item_type)
        {
            c_memset(w2s_text, 0,512 * sizeof(UTF16_T));
            BANNER_CHK_FAIL(c_wgl_do_cmd (h_item,
                            WGL_CMD_TEXT_GET_TEXT,
                            WGL_PACK (w2s_text),
                            WGL_PACK (512)));
        #if 1
            {
                CHAR ps_text[512] = {0};
                c_uc_w2s_to_ps(w2s_text,ps_text,512);
                BANNER_LOG(_BANNER_LOG_TYPE_ITEM,(" tts item[%s] => \"%s\" len = %d wlen = %d\n",GET_ITEM_DISP_NAME(ui1_item_id),ps_text,c_strlen(ps_text),c_uc_w2s_strlen (w2s_text)));
            }
        #endif
            switch(ui1_item_id)
            {
                case BANNER_ITM_CH_NAME:
                {
                    ISL_REC_T    t_isl_rec = {0};
                    TV_WIN_ID_T  t_tv_win_id = {0};
                    UTF16_T      w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

                    extern INT32  acfg_tv_get_focus_win(TV_WIN_ID_T*   pe_tv_win_id);
                    acfg_tv_get_focus_win(&t_tv_win_id);
                    nav_get_isl_rec(t_tv_win_id, &t_isl_rec);
                    if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
                    {
                        _banner_view_ch_name_text_preprocess(w2s_text, w2s_text, 512);
                        _banner_view_w2s_ch_r(w2s_text, w2s_text, 512, '-', " dash ");
                        c_uc_w2s_strcat(p_w2s_str, w2s_text);
                        c_uc_w2s_strcat(p_w2s_str, L" ");
                    }
                    else
                    {
                        a_isl_get_display_name_ex(&t_isl_rec, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);
                        if(c_uc_w2s_strlen(w2s_alias)  > 0)
                        {
                            c_uc_w2s_strcat(p_w2s_str, w2s_alias);
                            c_uc_w2s_strcat(p_w2s_str, L" ");
                        }
                    }
                    break;
                }
                case BANNER_ITM_PROG_TITLE:
                case BANNER_ITM_RATING:
                case BANNER_ITM_PROG_TIME:
                case BANNER_ITM_PROG_DETAIL:
                {
                    c_uc_w2s_strcat(p_w2s_detail_str, w2s_text);
                    c_uc_w2s_strcat(p_w2s_detail_str, L" ");
                    break;
                }
                default:
                    c_uc_w2s_strcat(p_w2s_str, w2s_text);
                    c_uc_w2s_strcat(p_w2s_str, L" ");
                    break;
            }
            t_bnr_item_set = NAV_BNR_STATE_IDX_TO_ID(ui1_item_id);
            pt_view->t_tts_updated_item_mask = (UINT32)(pt_view->t_tts_updated_item_mask | t_bnr_item_set);
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_view_tts_play_string
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID  _banner_view_tts_play_string(VOID* p1, VOID* p2, VOID* p3)
{
    UTF16_T p_w2s_str[1024+1]  = {0};
    UTF16_T p_w2s_detail_str[1024+1]  = {0};
    BOOL    b_is_visibility = FALSE;
    BANNER_VIEW_T*  pt_this = &t_g_view;
    CHAR    s_tts_string[1024+1] = {0};
    CHAR    s_tts_detail_string[1024+1] = {0};

    c_wgl_get_visibility(pt_this->h_bnr_root_frame, &b_is_visibility);
    if (FALSE == b_is_visibility)
    {
        /* if banner is not visibility, return. */
        DBG_LOG_PRINT(("[banner TTS]banner is not visibility!line:%d\n",__LINE__));
        return;
    }

    if(TTS_STR_ST_PLAYING == a_app_tts_get_string_state() && timer_reset_count < 4)
    {
        DBG_LOG_PRINT(("[banner TTS]TTS is reading now! reset timer! timer_reset_count:%d line:%d\n",timer_reset_count,__LINE__));
        timer_reset_count++;
        _banner_view_reset_tts_timer();
        return;
    }

    if (g_t_tts_updated_item_mask == TRUE)
    {
        /* Enter banner firstly, we should stop and flush tts msgQ. */
        {
            /*
             * We should not stop and flush tts msgQ when first power on.
             * due to "Power On!" can not stop it.
             */
            _banner_view_tts_get_item_string(p_w2s_str, p_w2s_detail_str);

            c_uc_w2s_to_ps (p_w2s_str, s_tts_string, sizeof(s_tts_string)-1);
            c_uc_w2s_to_ps (p_w2s_detail_str, s_tts_detail_string, sizeof(p_w2s_detail_str)-1);

            BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("[banner tts]string= %s \n",s_tts_string));

            if ((c_uc_w2s_strlen(p_w2s_detail_str) > 0) &&
                nav_banner_get_from_double_info_key())
            {
                if(g_t_tts_banenr_detail_mask == TRUE)
                {
                    banner_tts_play(p_w2s_detail_str);
                    g_t_tts_banenr_detail_mask = FALSE;
                }
            }
            else if(c_uc_w2s_strlen(p_w2s_str) > 0)
            {
                banner_tts_play(p_w2s_str);
                g_t_tts_updated_item_mask = FALSE;
            }
        }
    }
}

static VOID _banner_view_tts_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* switch to execute in nav's thread context */
    nav_request_context_switch(_banner_view_tts_play_string, NULL, NULL, NULL);
}

static VOID _banner_view_reset_tts_timer(VOID)
{
    INT32 i4_ret = 0;
    BANNER_VIEW_T *pt_this = &t_g_view ;

    if (c_handle_valid(pt_this->h_tts_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_tts_timer);
    if (i4_ret != NAVR_OK) {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("stop Banner TTS::h_hide_timer failed!\n"));
    }

    i4_ret = c_timer_start(
                           pt_this->h_tts_timer,
                           500,
                           X_TIMER_FLAG_ONCE,
                           _banner_view_tts_timer_nfy,
                           NULL
                           );
    if (i4_ret != NAVR_OK) {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("start Banner TTS::h_hide_timer failed!\n"));
    }
}

VOID banner_view_tts_fill_string()
{
    UINT8    switch_status = APP_CFG_TTS_SWITCH_OFF;
    _banner_view_tts_reset_timer_count();
    a_cfg_get_tts_switch_status(&switch_status);
    if(APP_CFG_TTS_SWITCH_ON == switch_status)
    {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[banner tts] fill_string\n")) ;
        _banner_view_reset_tts_timer();
        if(FALSE == nav_banner_get_from_ch_num_key())
        {
            _banner_view_reset_tts_timer();
        }

        if((TRUE == nav_banner_get_from_ch_num_key()) && (TRUE == banner_view_tv_info_updeted_is_finished()) && (TRUE == get_banner_tts_enable()))
        {
            banner_view_tv_info_updeted_erase();
           // _banner_view_reset_tts_timer();
        }
    }
}

VOID banner_view_tts_reset_updated_mask()
{
    BANNER_VIEW_T*       pt_this         = &t_g_view ;

    pt_this->t_tts_updated_item_mask     = 0;
    g_t_tts_updated_item_mask            = TRUE;
    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("\n"));
}

INT32 nav_banner_view_detail_info_tts()
{
#if 0
    INT32 i4_ret = 0;
    BANNER_VIEW_T *pt_this = &t_g_view ;

    if (c_handle_valid(pt_this->h_tts_timer) == FALSE) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_stop(pt_this->h_tts_timer);
    if (i4_ret != NAVR_OK) {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("stop Banner TTS::h_hide_timer failed!"));
    }
    a_app_tts_stop(APP_TTS_STOP_FORCE);
    i4_ret = c_timer_start(
                    pt_this->h_tts_timer,
                    500,
                    X_TIMER_FLAG_ONCE,
                    _banner_view_tts_timer_nfy,
                    NULL
                    );
    if (i4_ret != NAVR_OK) {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("start Banner TTS::h_hide_timer failed!"));
    }
#endif
    /*enable tts timer*/
    g_t_tts_banenr_detail_mask = TRUE;
    banner_view_tts_reset_updated_mask();
    _banner_view_reset_tts_timer();

    return NAVR_OK;
}

#endif

/*clean audio and video items*/
VOID banner_view_clean_av_item()
{
    UINT32                ui4_item_idx = 0;
    BANNER_ITEM_INFO_T*   pt_item_info = NULL ;

    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("\n")) ;

    for(;ui4_item_idx < BANNER_ITM_LAST_VALID_ENTRY; ui4_item_idx++)
    {
        if(ui4_item_idx == BANNER_ITM_TV_NAME   ||
           ui4_item_idx == BANNER_ITM_WIFI_ICON ||
           ui4_item_idx == BANNER_ITM_WIFI_TXT  ||
           ui4_item_idx == BANNER_ITM_TIMER_24  ||
           ui4_item_idx == BANNER_ITM_IPTS_ICON ||
           ui4_item_idx == BANNER_ITM_CH_NAME)
        {
            continue;
        }
        else
        {
            pt_item_info = banner_get_item_info (ui4_item_idx) ;

            if(NULL != pt_item_info && pt_item_info->e_item_type != BANNER_ITEM_TYPE_FRM)
            {
                {
                    if(BANNER_ITM_ASPECT == ui4_item_idx)
                    {
                        //BANNER_LOG_ON_FAIL (banner_view_update_item  ( ui4_item_idx, BANNER_TEXT("Normal"), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
                        //update aspect,aspect is different in each source,not normal always (attention:hdr update in banner_sys_info_handler)
                        banner_update_scr_mode();
                    }
                    else
                        BANNER_LOG_ON_FAIL (banner_view_update_item  ( ui4_item_idx, BANNER_TEXT(""), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
                }
            }
        }
    }
    if(banner_view_is_on_show())
    {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[%s][%d]\n", __FUNCTION__, __LINE__));
        _banner_view_start_repaint();
    }
}

#ifdef APP_TTS_SUPPORT

VOID set_banner_tts_enable(BOOL enable_flag)
{
    b_is_banner_tts_enable = enable_flag;
}

BOOL get_banner_tts_enable(VOID)
{
    return b_is_banner_tts_enable;
}
#endif

VOID a_set_banner_enable(BOOL enable_flag)
{
    b_is_banner_enable = enable_flag;
}


static BANNER_SIDERBAR_LOGO e_g_video_hdr      = BANNER_LOGO_HDR_SDR;


static VOID _banner_view_siderbar_auto_hide_cb_action(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3)
{
     banner_cust_set_sidebar_showing(FALSE);

     //banner_anim_start_animation(FALSE);
     BANNER_LOG_ON_FAIL (c_wgl_set_visibility(t_g_view.h_bnr_siderbar_frame,WGL_SW_HIDE_RECURSIVE));
     c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,FALSE);
     c_timer_stop(t_g_view.h_siderbar_auto_hide_timer);

     banner_view_sidebar_showing.b_on_showing_text_HDR = FALSE;
     banner_view_sidebar_showing.b_on_showing_icon_HDR = FALSE;
     banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = FALSE;
     banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = FALSE;
     banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = FALSE;
     banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = FALSE;
     banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = FALSE;
     banner_view_sidebar_showing.b_on_showing_icon_FREESYNC = FALSE;
}


static VOID banner_siderbar_auto_hide_cb_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag)
{
    nav_request_context_switch(_banner_view_siderbar_auto_hide_cb_action,
                       NULL,
                       NULL,
                       NULL);
}

static VOID _banner_view_siderbar_check_to_show_cb_action(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3)
{
    if(!nav_is_component_visible(NAV_COMP_ID_BANNER))
    {
        delay_check_repeat_timer_count = 0;
        //repaint part
        BANNER_CHK_FAIL(c_wgl_set_visibility (t_g_view.h_bnr_siderbar_frame,WGL_SW_NORMAL));
        DBG_LOG_PRINT(("[NAV][sidebar][%s %d] next to show sidebar\n",__FUNCTION__,__LINE__));
        BANNER_CHK_FAIL(c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,TRUE));

        banner_cust_set_sidebar_showing(TRUE);

        BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_siderbar_auto_hide_timer));
        BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_auto_hide_timer,
                                     3000,
                                     X_TIMER_FLAG_ONCE,
                                     banner_siderbar_auto_hide_cb_fct,
                                     NULL));
    }
    else
    {
        delay_check_repeat_timer_count++;
        //banner can be shown 5s generally(TTS may prolong it),so set up to 10s
        if(delay_check_repeat_timer_count > 10)
        {
            DBG_LOG_PRINT(("[NAV][sidebar][%s %d] delay to show sidebar too much,stop it now !!!\n",__FUNCTION__,__LINE__));
            return;
        }
        //repeat timer again
        DBG_LOG_PRINT(("[NAV][sidebar][%s %d] delay to show sidebar\n",__FUNCTION__,__LINE__));
        BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_delay_show_timer,
                                     1000,
                                     X_TIMER_FLAG_ONCE,
                                     _banner_siderbar_check_to_show_cb_fct,
                                     NULL));
    }

}


static VOID _banner_siderbar_check_to_show_cb_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag)
{
    BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_siderbar_delay_show_timer));
    nav_request_context_switch(_banner_view_siderbar_check_to_show_cb_action,
                           NULL,
                           NULL,
                           NULL);
}



#if 0
INT32 banner_show_siderbar(BANNER_SIDERBAR_HDR e_hdr)
{
    if(!banner_view_get_sidebar_show_flag())
        return NAVR_NO_ACTION;

    ISL_REC_T                   t_isl_rec            = {0};
    MMP_BE_BROWSER_STATUS_T     e_mmp_browser_status = a_mmp_be_get_browser_status();
    BOOL                         b_is_mmp            = a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP);
    BANNER_CHK_FAIL (c_wgl_set_visibility(t_g_view.h_bnr_siderbar_frame, WGL_SW_HIDE_RECURSIVE));
    e_g_video_hdr = e_hdr;
    visibie_hdr_handle = NULL_HANDLE;

    //GL_RECT_T                   pt_rect_tmp;
    //GL_RECT_T*                  pt_rect;

    //DBG_LOG_PRINT(("[siderbar] %s %d enter e_hdr = %d\r\n",__FUNCTION__,__LINE__,e_hdr));
    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" e_hdr = %d,\n",e_hdr));

    if(BANNER_HDR_SDR != e_hdr)
    {
        switch(e_hdr)
        {
            case BANNER_HDR_HLG:
            case BANNER_HDR_HDR10:
            case BANNER_HDR_HDR10_PLUS:
            {

                UTF16_T*      pw2s_text  = e_hdr == BANNER_HDR_HLG ? L"HLG":(e_hdr == BANNER_HDR_HDR10 ? L"HDR10":L"HDR10+");
                visibie_hdr_handle = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR);

                BANNER_CHK_FAIL(c_wgl_float(visibie_hdr_handle,TRUE,0));
                BANNER_LOG_ON_FAIL (c_wgl_do_cmd (visibie_hdr_handle,
                                                  WGL_CMD_TEXT_SET_TEXT,
                                                  (VOID*)pw2s_text,
                                                  (VOID*)c_uc_w2s_strlen (pw2s_text)));

                banner_view_sidebar_showing.b_on_showing_text_HDR = TRUE;

            }break;

           case BANNER_HDR_DOLBY_VISION:
           {
               WGL_IMG_INFO_T     t_img_info = {0};
               HANDLE_T           h_img      = h_g_banner_slider_icon_dolby_vision;
/*
               BOOL scrn_svr_visible = FALSE;
               TOAST_STYLE_T e_toast_style = TOAST_STYLE_MAX_NUM;
               scrn_svr_visible = nav_is_component_visible(NAV_COMP_ID_SCREEN_SAVER);
               e_toast_style = a_scrn_svr_get_style();
               DBG_LOG_PRINT(("[banner scrn] scrn_svr_visible:%d e_toast_style:%d\n",scrn_svr_visible,e_toast_style));
               if(scrn_svr_visible && (e_toast_style == TOAST_STYLE_NO_SIGNAL_1))
               {
                    BANNER_CHK_FAIL(a_scrn_svr_hide_NO_SIGNAL_1());
               }
*/

               visibie_hdr_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);

               /* set icon image buffer*/
               t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
               t_img_info.u_img_data.t_standard.t_enable    = h_img;
               t_img_info.u_img_data.t_standard.t_disable   = h_img;
               t_img_info.u_img_data.t_standard.t_highlight = h_img;
               BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_hdr_handle,
                                                WGL_CMD_GL_SET_IMAGE,
                                                WGL_PACK(WGL_IMG_FG),
                                                WGL_PACK(&t_img_info)));

               banner_view_sidebar_showing.b_on_showing_icon_HDR = TRUE;

//change rect directly,sidebar items all need adjust
#if 0
                //get current siderbar frm rect
                pt_rect = nav_banner2_view_rc_get_siderbar_frm_rect();
                if(pt_rect)
                {
                    BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("frm rect[l= %4d,r = %4d,t = %4d,b = %4d] old\n",pt_rect->i4_left,pt_rect->i4_right,pt_rect->i4_top,pt_rect->i4_bottom)) ;
                    //DBG_LOG_PRINT (("[] frm rect[l= %4d,r = %4d,t = %4d,b = %4d] old\n",pt_rect->i4_left,pt_rect->i4_right,pt_rect->i4_top,pt_rect->i4_bottom)) ;

                    //adjust current siderbar frm rect
                    pt_rect_tmp = *pt_rect;
                    (&pt_rect_tmp)->i4_bottom = pt_rect->i4_bottom + 130;
                    (&pt_rect_tmp)->i4_top = pt_rect->i4_top + 130;

                    //move to new rect(under banner's border)(show in next after check)
                    BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("frm rect[l= %4d,r = %4d,t = %4d,b = %4d] new\n",(&pt_rect_tmp)->i4_left,(&pt_rect_tmp)->i4_right,(&pt_rect_tmp)->i4_top,(&pt_rect_tmp)->i4_bottom)) ;
                    //DBG_LOG_PRINT (("[] frm rect[l= %4d,r = %4d,t = %4d,b = %4d] new\n",(&pt_rect_tmp)->i4_left,(&pt_rect_tmp)->i4_right,(&pt_rect_tmp)->i4_top,(&pt_rect_tmp)->i4_bottom)) ;
                    c_wgl_move(t_g_view.h_bnr_siderbar_frame,&pt_rect_tmp,WGL_NO_AUTO_REPAINT/*WGL_SYNC_AUTO_REPAINT*/);
                }
#endif
           }break;

          default:
          {
               WGL_IMG_INFO_T     t_img_info = {0};
               visibie_hdr_handle = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR);
               BANNER_LOG_ON_FAIL (c_wgl_do_cmd (visibie_hdr_handle,
                                                 WGL_CMD_TEXT_SET_TEXT,
                                                 (VOID*)L"",
                                                 (VOID*)0));

               visibie_hdr_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);

               /* set icon image buffer*/
               t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
               t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
               t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
               t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
               BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_hdr_handle,
                                                WGL_CMD_GL_SET_IMAGE,
                                                WGL_PACK(WGL_IMG_FG),
                                                WGL_PACK(&t_img_info)));

               BANNER_CHK_FAIL (c_wgl_set_visibility(t_g_view.h_bnr_siderbar_frame, WGL_SW_HIDE_RECURSIVE));
               return NAVR_OK;
            }
            break;
        }

        banner_get_crnt_isl(&t_isl_rec);

        //BANNER_CHK_FAIL(c_wgl_float(t_g_view.h_bnr_siderbar_frame,TRUE,FALSE));
        DBG_LOG_PRINT(("[%s %d]t_crnt_inp = %d,b_mmp_full_screen = %d,e_mmp_browser_status = %d\n",__FUNCTION__,__LINE__,t_isl_rec.e_src_type,b_is_mmp,e_mmp_browser_status));
        DBG_LOG_PRINT(("[NAV][Banner][%s %d]e_src_type = %d,e_video_type = %x\n",__FUNCTION__,__LINE__,t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type));
        if((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type &&
            DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type) &&
            !(e_mmp_browser_status >= MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING &&
            e_mmp_browser_status <= MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING))
        {
               DBG_LOG_PRINT(("[NAV][Banner][%s %d] mmp is not full screen mode\n",__FUNCTION__,__LINE__));
                banner_view_sidebar_showing.b_on_showing_icon_HDR = FALSE;
                banner_view_sidebar_showing.b_on_showing_text_HDR = FALSE;
               return NAVR_OK;
        }

        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_hdr_handle,WGL_SW_NORMAL));
        c_wgl_float(visibie_hdr_handle,TRUE,FALSE);

        visibie_PE_handle = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
        visibie_FM_handle = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);

        //decide PROGAMING_ENGINE && FILMMAKER_MODE place if need
        if(banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE)
        {
            //PROGAMING_ENGINE no move
            GL_RECT_T*  t_rect_pe = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
            GL_RECT_T   t_rect_pe_new = {0};
            t_rect_pe_new.i4_left = t_rect_pe->i4_left;
            t_rect_pe_new.i4_right = t_rect_pe->i4_right;
            t_rect_pe_new.i4_top = t_rect_pe->i4_top;
            t_rect_pe_new.i4_bottom = t_rect_pe->i4_bottom;
            c_wgl_move(visibie_PE_handle,&t_rect_pe_new,WGL_NO_AUTO_REPAINT);

            if(banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE)
            {
                //FILMMAKER_MODE no move
                GL_RECT_T*  t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);
                GL_RECT_T   t_rect_fm_new = {0};
                t_rect_fm_new.i4_left = t_rect_fm->i4_left;
                t_rect_fm_new.i4_right = t_rect_fm->i4_right;
                t_rect_fm_new.i4_top = t_rect_fm->i4_top;
                t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom;
                c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);
            }
        }
        else if(banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE)
        {
            //FILMMAKER_MODE move PROGAMING_ENGINE'height
            GL_RECT_T*  t_rect_pe = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
            GL_RECT_T*  t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);
            GL_RECT_T   t_rect_fm_new = {0};
            INT32       h_height_need_to_move = 0;
            h_height_need_to_move = t_rect_pe->i4_bottom-t_rect_pe->i4_top;
            t_rect_fm_new.i4_left = t_rect_fm->i4_left;
            t_rect_fm_new.i4_right = t_rect_fm->i4_right;
            t_rect_fm_new.i4_top = t_rect_fm->i4_top-(h_height_need_to_move);
            t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom-(h_height_need_to_move);
            c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);

        }

        //adjust PROGAMING_ENGINE if need
        if(banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE)
        {
            WGL_IMG_INFO_T     t_img_info = {0};
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = h_g_banner_slider_icon_prg;
            t_img_info.u_img_data.t_standard.t_disable   = h_g_banner_slider_icon_prg;
            t_img_info.u_img_data.t_standard.t_highlight = h_g_banner_slider_icon_prg;
            BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_PE_handle,
                                             WGL_CMD_GL_SET_IMAGE,
                                             WGL_PACK(WGL_IMG_FG),
                                             WGL_PACK(&t_img_info)));

            BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_PE_handle,WGL_SW_NORMAL));
            c_wgl_float(visibie_PE_handle,TRUE,FALSE);

        }
        //adjust FILMMAKER_MODE if need
        if(banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE)
        {
            WGL_IMG_INFO_T     t_img_info = {0};
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = h_g_banner_slider_icon_fmm;
            t_img_info.u_img_data.t_standard.t_disable   = h_g_banner_slider_icon_fmm;
            t_img_info.u_img_data.t_standard.t_highlight = h_g_banner_slider_icon_fmm;
            BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_FM_handle,
                                             WGL_CMD_GL_SET_IMAGE,
                                             WGL_PACK(WGL_IMG_FG),
                                             WGL_PACK(&t_img_info)));

            BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_FM_handle,WGL_SW_NORMAL));
            c_wgl_float(visibie_FM_handle,TRUE,FALSE);
        }


        BANNER_CHK_FAIL(c_wgl_set_visibility (t_g_view.h_bnr_siderbar_frame,WGL_SW_NORMAL));
        DBG_LOG_PRINT(("[NAV][sidebar][%s %d] next to show sidebar\n",__FUNCTION__,__LINE__));
        BANNER_CHK_FAIL(c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,TRUE));
        //banner_anim_start_animation(TRUE);

        banner_cust_set_sidebar_showing(TRUE);

        BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_auto_hide_timer,
                                         4000,
                                         X_TIMER_FLAG_ONCE,
                                         banner_siderbar_auto_hide_cb_fct,
                                         NULL));

    }
    return NAVR_OK;
}


//add for "progaming engine" && "filmmaker mode"
INT32 banner_show_siderbar_ex(BANNER_SIDERBAR_EX e_type)
{

    if(!banner_view_get_sidebar_show_flag() || e_type == BANNER_EX_NULL || e_type == BANNER_EX_COUNT)
        return NAVR_NO_ACTION;

    DBG_LOG_PRINT(("%s %d e_type:%d\n",__FUNCTION__,__LINE__,e_type));
    GL_RECT_T* t_rect_dv = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
    GL_RECT_T* t_rect_pe = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
    GL_RECT_T* t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);

    switch(e_type)
    {
        case BANNER_PROGAMING_ENGINE:
        {
            WGL_IMG_INFO_T     t_img_info = {0};
            HANDLE_T           h_img      = h_g_banner_slider_icon_prg;

            if(banner_view_sidebar_showing.b_on_showing_icon_HDR || banner_view_sidebar_showing.b_on_showing_text_HDR)
            {
                GL_RECT_T* t_rect_pe = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);

                GL_RECT_T   t_rect_pe_new = {0};
                t_rect_pe_new.i4_left = t_rect_pe->i4_left;
                t_rect_pe_new.i4_right = t_rect_pe->i4_right;
                t_rect_pe_new.i4_top = t_rect_pe->i4_top;
                t_rect_pe_new.i4_bottom = t_rect_pe->i4_bottom;
                c_wgl_move(visibie_PE_handle,&t_rect_pe_new,WGL_NO_AUTO_REPAINT);

                if(banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE)
                {
                    GL_RECT_T* t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);

                    GL_RECT_T   t_rect_fm_new = {0};
                    t_rect_fm_new.i4_left = t_rect_fm->i4_left;
                    t_rect_fm_new.i4_right = t_rect_fm->i4_right;
                    t_rect_fm_new.i4_top = t_rect_fm->i4_top;
                    t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom;
                    c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);
                }
            }
            else if(!(banner_view_sidebar_showing.b_on_showing_icon_HDR || banner_view_sidebar_showing.b_on_showing_text_HDR))
            {
                GL_RECT_T* t_rect_dv = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
                GL_RECT_T* t_rect_pe = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);

                GL_RECT_T   t_rect_pe_new = {0};
                INT32       h_height_need_to_move = (t_rect_dv->i4_bottom - t_rect_dv->i4_top);
                t_rect_pe_new.i4_left = t_rect_pe->i4_left;
                t_rect_pe_new.i4_right = t_rect_pe->i4_right;
                t_rect_pe_new.i4_top = t_rect_pe->i4_top - (h_height_need_to_move);
                t_rect_pe_new.i4_bottom = t_rect_pe->i4_bottom - (h_height_need_to_move);
                c_wgl_move(visibie_PE_handle,&t_rect_pe_new,WGL_NO_AUTO_REPAINT);
                if(banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE)
                {
                    GL_RECT_T* t_rect_dv = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
                    GL_RECT_T* t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);

                    GL_RECT_T   t_rect_fm_new = {0};
                    INT32       h_height_need_to_move = (t_rect_dv->i4_bottom - t_rect_dv->i4_top);
                    t_rect_fm_new.i4_left = t_rect_fm->i4_left;
                    t_rect_fm_new.i4_right = t_rect_fm->i4_right;
                    t_rect_fm_new.i4_top = t_rect_fm->i4_top - (h_height_need_to_move);
                    t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom - (h_height_need_to_move);
                    c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);
                }
            }

            /* set icon image buffer*/
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = h_img;
            t_img_info.u_img_data.t_standard.t_disable   = h_img;
            t_img_info.u_img_data.t_standard.t_highlight = h_img;
            BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_PE_handle,
                                             WGL_CMD_GL_SET_IMAGE,
                                             WGL_PACK(WGL_IMG_FG),
                                             WGL_PACK(&t_img_info)));

            BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_PE_handle,WGL_SW_NORMAL));
            c_wgl_float(visibie_PE_handle,TRUE,FALSE);

            //adjust FILMMAKER_MODE if need
            if(banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE)
            {
                t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
                t_img_info.u_img_data.t_standard.t_enable    = h_g_banner_slider_icon_fmm;
                t_img_info.u_img_data.t_standard.t_disable   = h_g_banner_slider_icon_fmm;
                t_img_info.u_img_data.t_standard.t_highlight = h_g_banner_slider_icon_fmm;
                BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_FM_handle,
                                                 WGL_CMD_GL_SET_IMAGE,
                                                 WGL_PACK(WGL_IMG_FG),
                                                 WGL_PACK(&t_img_info)));

                BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_FM_handle,WGL_SW_NORMAL));
                c_wgl_float(visibie_FM_handle,TRUE,FALSE);

            }

            BANNER_CHK_FAIL(c_wgl_set_visibility (t_g_view.h_bnr_siderbar_frame,WGL_SW_NORMAL));
            DBG_LOG_PRINT(("[NAV][sidebar][%s %d] next to show BANNER_PROGAMING_ENGINE\n",__FUNCTION__,__LINE__));
            BANNER_CHK_FAIL(c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,TRUE));
            //banner_anim_start_animation(TRUE);

            banner_cust_set_sidebar_showing(TRUE);
            banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = TRUE;

            BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_auto_hide_timer,
                                             4000,
                                             X_TIMER_FLAG_ONCE,
                                             banner_siderbar_auto_hide_cb_fct,
                                             NULL));
        }
        break;
        case BANNER_FILMMAKER_MODE:
        {
            WGL_IMG_INFO_T     t_img_info = {0};
            HANDLE_T           h_img      = h_g_banner_slider_icon_fmm;

            if((banner_view_sidebar_showing.b_on_showing_icon_HDR || banner_view_sidebar_showing.b_on_showing_text_HDR) \
                && banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE)
            {
                GL_RECT_T*  t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);
                GL_RECT_T   t_rect_fm_new = {0};

                t_rect_fm_new.i4_left = t_rect_fm->i4_left;
                t_rect_fm_new.i4_right = t_rect_fm->i4_right;
                t_rect_fm_new.i4_top = t_rect_fm->i4_top;
                t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom;
                c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);
            }
            else if(!(banner_view_sidebar_showing.b_on_showing_icon_HDR || banner_view_sidebar_showing.b_on_showing_text_HDR) \
                && banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE)
            {
                GL_RECT_T* t_rect_dv = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
                GL_RECT_T* t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);

                GL_RECT_T   t_rect_fm_new = {0};
                INT32       h_height_need_to_move = t_rect_dv->i4_bottom - t_rect_dv->i4_top;
                t_rect_fm_new.i4_left = t_rect_fm->i4_left;
                t_rect_fm_new.i4_right = t_rect_fm->i4_right;
                t_rect_fm_new.i4_top = t_rect_fm->i4_top - (h_height_need_to_move);
                t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom - (h_height_need_to_move);
                c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);

            }
            else if((banner_view_sidebar_showing.b_on_showing_icon_HDR || banner_view_sidebar_showing.b_on_showing_text_HDR) \
                && !banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE)
            {
                GL_RECT_T* t_rect_pe = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
                GL_RECT_T* t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);

                GL_RECT_T   t_rect_fm_new = {0};
                INT32       h_height_need_to_move = t_rect_pe->i4_bottom - t_rect_pe->i4_top;
                t_rect_fm_new.i4_left = t_rect_fm->i4_left;
                t_rect_fm_new.i4_right = t_rect_fm->i4_right;
                t_rect_fm_new.i4_top = t_rect_fm->i4_top - (h_height_need_to_move);
                t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom - (h_height_need_to_move);
                c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);

            }
            else
            {
                //when HDR && PROGAMING_ENGINE both not showing,PROGAMING_ENGINE should be first
                GL_RECT_T* t_rect_dv = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
                GL_RECT_T* t_rect_pe = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
                GL_RECT_T* t_rect_fm = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);

                GL_RECT_T   t_rect_fm_new = {0};
                INT32       h_height_need_to_move = (t_rect_pe->i4_bottom - t_rect_pe->i4_top) + (t_rect_dv->i4_bottom - t_rect_dv->i4_top);
                t_rect_fm_new.i4_left = t_rect_fm->i4_left;
                t_rect_fm_new.i4_right = t_rect_fm->i4_right;
                t_rect_fm_new.i4_top = t_rect_fm->i4_top - (h_height_need_to_move);
                t_rect_fm_new.i4_bottom = t_rect_fm->i4_bottom - (h_height_need_to_move);
                c_wgl_move(visibie_FM_handle,&t_rect_fm_new,WGL_NO_AUTO_REPAINT);
            }

            /* set icon image buffer*/
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = h_img;
            t_img_info.u_img_data.t_standard.t_disable   = h_img;
            t_img_info.u_img_data.t_standard.t_highlight = h_img;
            BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_FM_handle,
                                             WGL_CMD_GL_SET_IMAGE,
                                             WGL_PACK(WGL_IMG_FG),
                                             WGL_PACK(&t_img_info)));

            BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_FM_handle,WGL_SW_NORMAL));
            c_wgl_float(visibie_FM_handle,TRUE,FALSE);
            BANNER_CHK_FAIL(c_wgl_set_visibility (t_g_view.h_bnr_siderbar_frame,WGL_SW_NORMAL));
            DBG_LOG_PRINT(("[NAV][sidebar][%s %d] next to show BANNER_FILMMAKER_MODE\n",__FUNCTION__,__LINE__));
            BANNER_CHK_FAIL(c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,TRUE));
            //banner_anim_start_animation(TRUE);

            banner_cust_set_sidebar_showing(TRUE);
            banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = TRUE;

            BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_auto_hide_timer,
                                             4000,
                                             X_TIMER_FLAG_ONCE,
                                             banner_siderbar_auto_hide_cb_fct,
                                             NULL));

        }
        break;
        default:
        return NAVR_NO_ACTION;
    }
}
#endif

static INT32 banner_show_siderbar_get_item_visible_rect(BANNER_SIDERBAR_LOGO e_type,GL_RECT_T *t_rect)
{
    GL_RECT_T* t_rect_origin = NULL;

    if(e_type ==  BANNER_LOGO_HDR_DOLBY_VISION)
    {
        //DV
        t_rect_origin = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
    }
    else if(e_type <=  BANNER_LOGO_HDR_HDR10_PLUS)
    {
        //TEXT
        t_rect_origin = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR);
    }
    else if(e_type == BANNER_LOGO_DOLBY_AUDIO || e_type == BANNER_LOGO_DOLBY_ATMOS)
    {
        //DD
        t_rect_origin = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_AUDIO);
    }
    else if(e_type == BANNER_LOGO_PROGAMING_ENGINE)
    {
        //PE
        t_rect_origin = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
    }
    else if(e_type == BANNER_LOGO_FILMMAKER_MODE)
    {
        //FM
        t_rect_origin = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);
    }
    else if(e_type == BANNER_LOGO_FREESYNC)
    {
        //FS
        t_rect_origin = nav_banner2_view_rc_get_siderbar_item_rect(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FREESYNC);
    }
    else
    {
        //otherwise
        return NAVR_NO_ACTION;
    }

    //set to origin rect
    t_rect->i4_top = t_rect_origin->i4_top;
    t_rect->i4_bottom = t_rect_origin->i4_bottom;
    t_rect->i4_left = t_rect_origin->i4_left;
    t_rect->i4_right = t_rect_origin->i4_right;

    return NAVR_OK;
}

extern WGL_HIMG_TPL_T  h_g_menu_img_main_channels;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_tv_channels_grayed_out;


INT32 banner_show_siderbar_logo(BANNER_SIDERBAR_LOGO e_type)
{
    //some app do not want to show logo
    if(!banner_view_get_sidebar_show_flag() || e_type == BANNER_LOGO_EX_COUNT)
        return NAVR_NO_ACTION;

    DBG_LOG_PRINT(("%s %d e_type:%d\n",__FUNCTION__,__LINE__,e_type));

    ISL_REC_T                       t_isl_rec                   = {0};
    //MMP_BE_BROWSER_STATUS_T         e_mmp_browser_status      = a_mmp_be_get_browser_status();
    //BOOL                            b_is_mmp                  = a_cfg_av_is_condition(APP_CFG_AV_COND_MASK_MMP);
    INT32                           i4_offset_next              = 0;
    BOOL                            b_no_need_show_hdr_icon     = FALSE;
    BOOL                            b_no_need_show_hdr_text     = FALSE;
    //BOOL                            b_delay_show                = FALSE;
    CHAR                            s_app_name[APP_NAME_MAX_LEN] = {0};

    //just hide and show nothing
    BANNER_CHK_FAIL (c_wgl_set_visibility(t_g_view.h_bnr_siderbar_frame, WGL_SW_HIDE_RECURSIVE));
    if(BANNER_LOGO_HDR_SDR == e_type)
    {
        b_no_need_show_hdr_icon = TRUE;
        b_no_need_show_hdr_text = TRUE;
    }

    //usb source not show it
    banner_get_crnt_isl(&t_isl_rec);
    a_am_get_active_app(s_app_name);
    if(!c_strcmp (s_app_name, MMP_NAME) || (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type && DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type))
    {
        DBG_LOG_PRINT(("[NAV][Banner][%s %d] usb not show banner logo\n",__FUNCTION__,__LINE__));
        banner_view_sidebar_showing.b_on_showing_text_HDR = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_HDR = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_FREESYNC = FALSE;
        return NAVR_OK;
    }

    /*//when banner already displayed,display logo after banner shown
    if(nav_is_component_visible(NAV_COMP_ID_BANNER))
    {
        b_delay_show = TRUE;
    }
    */

    //adjust each item rect and picture/text
    if((banner_view_sidebar_showing.b_on_showing_icon_FREESYNC == TRUE)||(e_type==BANNER_LOGO_FREESYNC))
    {
        //freesync
        WGL_IMG_INFO_T      t_img_info      = {0};
        GL_RECT_T           t_rect          = {0};
        HANDLE_T            h_img           = h_g_banner_slider_icon_freesync;
        HANDLE_T            visibie_handle  = NULL_HANDLE;
        INT32               i4_offset       = i4_offset_next;

        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FREESYNC);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_FREESYNC,&t_rect);
        //t_rect.i4_left -= i4_offset_next;
        //t_rect.i4_right -= i4_offset_next;
        i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
        //BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect_new,WGL_NO_AUTO_REPAINT));

        // set icon image buffer
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK(WGL_IMG_FG),
                                        WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,WGL_SW_NORMAL));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_icon_FREESYNC = TRUE;
    }

    if((banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE == TRUE && e_type!=BANNER_LOGO_V_GAMING_ENGINE)\
        ||(banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE == TRUE && e_type!=BANNER_LOGO_PROGAMING_ENGINE) \
        || (e_type==BANNER_LOGO_PROGAMING_ENGINE || e_type==BANNER_LOGO_V_GAMING_ENGINE))
    {
        //progaming engine
        WGL_IMG_INFO_T      t_img_info      = {0};
        GL_RECT_T           t_rect          = {0};
        HANDLE_T            h_img           = NULL;
        if((banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE == TRUE && e_type!=BANNER_LOGO_V_GAMING_ENGINE) || e_type==BANNER_LOGO_PROGAMING_ENGINE)
            h_img = h_g_banner_slider_icon_prg;
        else if((banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE == TRUE && e_type!=BANNER_LOGO_PROGAMING_ENGINE) || e_type==BANNER_LOGO_V_GAMING_ENGINE)
            h_img = h_g_banner_slider_icon_v_gaming_engine;
        HANDLE_T            visibie_handle  = NULL_HANDLE;

        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_PROGAMING_ENGINE,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        /* set icon image buffer*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                     WGL_CMD_GL_SET_IMAGE,
                                     WGL_PACK(WGL_IMG_FG),
                                     WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,WGL_SW_NORMAL));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        if(e_type==BANNER_LOGO_PROGAMING_ENGINE)
        {
            banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = TRUE;
            banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = FALSE;
        }
        else if(e_type==BANNER_LOGO_V_GAMING_ENGINE)
        {
            banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = FALSE;
            banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = TRUE;
        }
    }

    if((banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE == TRUE)||(e_type==BANNER_LOGO_FILMMAKER_MODE))
    {
        //filmmaker mode
        WGL_IMG_INFO_T      t_img_info = {0};
        GL_RECT_T           t_rect      = {0};
        HANDLE_T            h_img      = h_g_banner_slider_icon_fmm;
        HANDLE_T            visibie_handle  = NULL_HANDLE;
        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_FILMMAKER_MODE,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        /* set icon image buffer*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                     WGL_CMD_GL_SET_IMAGE,
                                     WGL_PACK(WGL_IMG_FG),
                                     WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,WGL_SW_NORMAL));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = TRUE;

    }

#ifdef NEED_SHOW_DOLBY_AUDIO_LOGO
    if((banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO == TRUE && e_type!=BANNER_LOGO_DOLBY_ATMOS)\
        || (banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS == TRUE && e_type!=BANNER_LOGO_DOLBY_AUDIO)\
        || (e_type==BANNER_LOGO_DOLBY_AUDIO) || (e_type==BANNER_LOGO_DOLBY_ATMOS))
    {
        //dolby audio
        WGL_IMG_INFO_T      t_img_info = {0};
        GL_RECT_T           t_rect      = {0};
        HANDLE_T            h_img  =  NULL_HANDLE;
        if((banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO == TRUE) || e_type==BANNER_LOGO_DOLBY_AUDIO)
            h_img      = h_g_banner_slider_icon_dolby_audio;
        else if((banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS == TRUE) || e_type==BANNER_LOGO_DOLBY_ATMOS)
            h_img      = h_g_banner_slider_icon_dolby_atmos;

        HANDLE_T            visibie_handle  = NULL_HANDLE;
        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_AUDIO);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_DOLBY_AUDIO,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        // set icon image buffer
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                     WGL_CMD_GL_SET_IMAGE,
                                     WGL_PACK(WGL_IMG_FG),
                                     WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,WGL_SW_NORMAL));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        //banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = TRUE;
        if(e_type==BANNER_LOGO_DOLBY_AUDIO)
        {
            banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = TRUE;
            banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = FALSE;
        }
        else if(e_type==BANNER_LOGO_DOLBY_ATMOS)
        {
            banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = FALSE;
            banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = TRUE;
        }

    }
#endif

    //for icon and text are mutually exclusive,if another already exit,then no need repaint it
    if((banner_view_sidebar_showing.b_on_showing_icon_HDR == TRUE) &&
        (e_type==BANNER_LOGO_HDR_HDR10_PLUS))
    {
        //no need show hdr_icon
        b_no_need_show_hdr_icon = TRUE;
    }
    if((banner_view_sidebar_showing.b_on_showing_text_HDR == TRUE) &&
        ((e_type==BANNER_LOGO_HDR_DOLBY_VISION) || (e_type==BANNER_LOGO_HDR_HDR10) || (e_type==BANNER_LOGO_HDR_HLG)))
    {
        //no need show hdr_text
        b_no_need_show_hdr_text = TRUE;
    }

    if(!b_no_need_show_hdr_text && ((banner_view_sidebar_showing.b_on_showing_text_HDR == TRUE) ||
        (e_type==BANNER_LOGO_HDR_HDR10_PLUS)))
    {
        //TEXT
        GL_RECT_T           t_rect      = {0};
        UTF16_T*            pw2s_text   = L"HDR10+";

        HANDLE_T            visibie_handle  = NULL_HANDLE;
        visibie_handle = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_HDR_HDR10_PLUS,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                          WGL_CMD_TEXT_SET_TEXT,
                                          (VOID*)pw2s_text,
                                          (VOID*)c_uc_w2s_strlen (pw2s_text)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,WGL_SW_NORMAL));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_text_HDR = TRUE;

    }

    if(!b_no_need_show_hdr_icon && ((banner_view_sidebar_showing.b_on_showing_icon_HDR == TRUE) ||
        ((e_type==BANNER_LOGO_HDR_HLG) || (e_type==BANNER_LOGO_HDR_HDR10) || (e_type==BANNER_LOGO_HDR_DOLBY_VISION))))
    {
        //DV
        WGL_IMG_INFO_T      t_img_info  = {0};
        GL_RECT_T           t_rect      = {0};
        HANDLE_T            h_img       = NULL_HANDLE;
        WGL_COLOR_INFO_T    t_clr_info  = {0};
        GL_COLOR_T          *t_color     = &t_g_transparent;

        if((e_type==BANNER_LOGO_HDR_HLG) || (e_type==BANNER_LOGO_HDR_HDR10) || (e_type==BANNER_LOGO_HDR_DOLBY_VISION))
        {
            h_img = (e_type == BANNER_LOGO_HDR_HLG) ? h_g_banner_slider_icon_hlg:
                    (e_type == BANNER_LOGO_HDR_HDR10 ? h_g_banner_slider_icon_hdr10:
                    (e_type == BANNER_LOGO_HDR_DOLBY_VISION ? h_g_banner_slider_icon_dolby_vision:NULL_HANDLE));
            if(e_type==BANNER_LOGO_HDR_DOLBY_VISION)
            {
                // set background color gray if need
                //t_color = &t_g_gray;
            }
        }
        else if(banner_view_sidebar_showing.b_on_showing_icon_HDR == TRUE)
        {
            SCC_VID_HDR_TYPE_T t_hdr_type = a_cfg_get_hdr_type();
            h_img = (t_hdr_type == SCC_VID_PQ_HLG) ? h_g_banner_slider_icon_hlg:
                    (t_hdr_type == SCC_VID_PQ_HDR10 ? h_g_banner_slider_icon_hdr10:
                    (t_hdr_type == SCC_VID_PQ_DOVI ? h_g_banner_slider_icon_dolby_vision:NULL_HANDLE));
            if(t_hdr_type==SCC_VID_PQ_DOVI)
            {
                // set background color gray if need
                //t_color = &t_g_gray;
            }
        }

        HANDLE_T            visibie_handle  = NULL_HANDLE;
        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_HDR_DOLBY_VISION,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        /* set icon image buffer*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK(WGL_IMG_FG),
                                        WGL_PACK(&t_img_info)));

        /* set message color */
        // set background color gray if need
        /*
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_disable   = *t_color;
        t_clr_info.u_color_data.t_standard.t_enable    = *t_color;
        t_clr_info.u_color_data.t_standard.t_highlight = *t_color;

        BANNER_LOG_ON_FAIL(c_wgl_do_cmd(visibie_handle,
                                        WGL_CMD_GL_SET_COLOR,
                                        WGL_PACK(WGL_IMG_BK),
                                        WGL_PACK(&t_clr_info)));
        */

        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,WGL_SW_NORMAL));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_icon_HDR = TRUE;

    }

    /*if(!b_delay_show)
    {
        //repaint part
        BANNER_CHK_FAIL(c_wgl_set_visibility (t_g_view.h_bnr_siderbar_frame,WGL_SW_NORMAL));
        DBG_LOG_PRINT(("[NAV][sidebar][%s %d] next to show sidebar\n",__FUNCTION__,__LINE__));
        BANNER_CHK_FAIL(c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,TRUE));

        banner_cust_set_sidebar_showing(TRUE);

        BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_siderbar_auto_hide_timer));
        BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_auto_hide_timer,
                                     3000,
                                     X_TIMER_FLAG_ONCE,
                                     banner_siderbar_auto_hide_cb_fct,
                                     NULL));
    }
    else
    */
    {
        DBG_LOG_PRINT(("[NAV][sidebar][%s %d] delay to show sidebar\n",__FUNCTION__,__LINE__));
        delay_check_repeat_timer_count = 0;
        BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_siderbar_delay_show_timer));
        BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_delay_show_timer,
                                     1000,
                                     X_TIMER_FLAG_ONCE,
                                     _banner_siderbar_check_to_show_cb_fct,
                                     NULL));
    }

    return NAVR_OK;
}

INT32 banner_hide_siderbar_logo(BANNER_SIDERBAR_LOGO e_type)
{
    //some app do not want to show logo
    if(!banner_view_get_sidebar_show_flag() || e_type == BANNER_LOGO_EX_COUNT)
        return NAVR_NO_ACTION;

    DBG_LOG_PRINT(("%s %d e_type:%d\n",__FUNCTION__,__LINE__,e_type));

    ISL_REC_T                       t_isl_rec                   = {0};
    INT32                           i4_offset_next              = 0;
    BOOL                            b_no_need_show_hdr_icon     = FALSE;
    BOOL                            b_no_need_show_hdr_text     = FALSE;

    //just hide and show nothing
    BANNER_CHK_FAIL (c_wgl_set_visibility(t_g_view.h_bnr_siderbar_frame, WGL_SW_HIDE_RECURSIVE));

    //usb source not show it
    banner_get_crnt_isl(&t_isl_rec);
    if((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type && DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type))
    {
        DBG_LOG_PRINT(("[NAV][Banner][%s %d] usb not show banner logo\n",__FUNCTION__,__LINE__));
        banner_view_sidebar_showing.b_on_showing_text_HDR = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_HDR = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_FREESYNC = FALSE;
        return NAVR_OK;
    }

    //adjust each item rect and picture/text
    if((banner_view_sidebar_showing.b_on_showing_icon_FREESYNC == TRUE))
    {
        //freesync
        WGL_IMG_INFO_T      t_img_info      = {0};
        GL_RECT_T           t_rect          = {0};
        HANDLE_T            h_img           = h_g_banner_slider_icon_freesync;
        HANDLE_T            visibie_handle  = NULL_HANDLE;
        INT32               i4_offset       = i4_offset_next;
        WGL_SW_CMD_T        wgl_status      = WGL_SW_HIDE_RECURSIVE;

        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FREESYNC);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_FREESYNC,&t_rect);

        if(e_type!=BANNER_LOGO_FREESYNC)
        {
            i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
            wgl_status = WGL_SW_NORMAL;
        }

        // set icon image buffer
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK(WGL_IMG_FG),
                                        WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,wgl_status));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_icon_FREESYNC = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);

    }

    if(banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE == TRUE || banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE == TRUE)
    {

        //progaming engine
        WGL_IMG_INFO_T      t_img_info      = {0};
        GL_RECT_T           t_rect          = {0};
        HANDLE_T            h_img           = NULL;;
        HANDLE_T            visibie_handle  = NULL_HANDLE;
        WGL_SW_CMD_T        wgl_status      = WGL_SW_HIDE_RECURSIVE;

        if(banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE == TRUE)
            h_img = h_g_banner_slider_icon_prg;
        else if(banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE == TRUE)
            h_img = h_g_banner_slider_icon_v_gaming_engine;

        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_PROGAMING_ENGINE,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        if(e_type!=BANNER_LOGO_PROGAMING_ENGINE && e_type!=BANNER_LOGO_V_GAMING_ENGINE)
        {
            i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
            wgl_status = WGL_SW_NORMAL;
        }

        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        /* set icon image buffer*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                     WGL_CMD_GL_SET_IMAGE,
                                     WGL_PACK(WGL_IMG_FG),
                                     WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,wgl_status));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        if(banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE == TRUE)
            banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);
        else if(banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE == TRUE)
            banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);

    }

    if((banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE == TRUE))
    {
        //filmmaker mode
        WGL_IMG_INFO_T      t_img_info = {0};
        GL_RECT_T           t_rect      = {0};
        HANDLE_T            h_img      = h_g_banner_slider_icon_fmm;
        HANDLE_T            visibie_handle  = NULL_HANDLE;
        WGL_SW_CMD_T        wgl_status      = WGL_SW_HIDE_RECURSIVE;

        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_FILMMAKER_MODE,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        if(e_type!=BANNER_LOGO_FILMMAKER_MODE)
        {
            i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
            wgl_status = WGL_SW_NORMAL;
        }

        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        /* set icon image buffer*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                     WGL_CMD_GL_SET_IMAGE,
                                     WGL_PACK(WGL_IMG_FG),
                                     WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,wgl_status));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);;

    }

#ifdef NEED_SHOW_DOLBY_AUDIO_LOGO
    if((banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO == TRUE) || (banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS == TRUE))
    {
        //dolby audio
        WGL_IMG_INFO_T      t_img_info = {0};
        GL_RECT_T           t_rect      = {0};
        HANDLE_T            h_img  =  NULL_HANDLE;
        WGL_SW_CMD_T        wgl_status      = WGL_SW_HIDE_RECURSIVE;

        if((banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO == TRUE))
            h_img      = h_g_banner_slider_icon_dolby_audio;
        else if((banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO == TRUE))
            h_img      = h_g_banner_slider_icon_dolby_atmos;

        HANDLE_T            visibie_handle  = NULL_HANDLE;
        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_AUDIO);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_DOLBY_AUDIO,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        if(((e_type!=BANNER_LOGO_DOLBY_AUDIO) && (e_type!=BANNER_LOGO_DOLBY_ATMOS)))
        {
            i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
            wgl_status = WGL_SW_NORMAL;
        }

        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        // set icon image buffer
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                     WGL_CMD_GL_SET_IMAGE,
                                     WGL_PACK(WGL_IMG_FG),
                                     WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,wgl_status));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        if((banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO == TRUE))
            banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);
        else if((banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS == TRUE))
            banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);

    }
#endif

    if((banner_view_sidebar_showing.b_on_showing_text_HDR == TRUE))
    {
        //TEXT
        GL_RECT_T           t_rect      = {0};
        UTF16_T*            pw2s_text   = NULL;
        HANDLE_T            visibie_handle  = NULL_HANDLE;
        WGL_SW_CMD_T        wgl_status      = WGL_SW_HIDE_RECURSIVE;

        pw2s_text = L"HDR10+";

        visibie_handle = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_HDR_HDR10_PLUS,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        if((e_type!=BANNER_LOGO_HDR_HLG) && (e_type!=BANNER_LOGO_HDR_HDR10) && (e_type!=BANNER_LOGO_HDR_HDR10_PLUS))
        {
            i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
            wgl_status = WGL_SW_NORMAL;
        }

        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                          WGL_CMD_TEXT_SET_TEXT,
                                          (VOID*)pw2s_text,
                                          (VOID*)c_uc_w2s_strlen (pw2s_text)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,wgl_status));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_text_HDR = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);;

    }

    if((banner_view_sidebar_showing.b_on_showing_icon_HDR == TRUE))
    {
        //DV
        WGL_IMG_INFO_T      t_img_info = {0};
        GL_RECT_T           t_rect     = {0};
        HANDLE_T            h_img      = NULL_HANDLE;
        HANDLE_T            visibie_handle  = NULL_HANDLE;
        WGL_SW_CMD_T        wgl_status      = WGL_SW_HIDE_RECURSIVE;


        SCC_VID_HDR_TYPE_T t_hdr_type = a_cfg_get_hdr_type();
        h_img = (t_hdr_type == SCC_VID_PQ_HLG) ? h_g_banner_slider_icon_hlg:
                (t_hdr_type == SCC_VID_PQ_HDR10 ? h_g_banner_slider_icon_hdr10:
                (t_hdr_type == SCC_VID_PQ_DOVI ? h_g_banner_slider_icon_dolby_vision:NULL_HANDLE));


        visibie_handle  = nav_banner2_view_rc_get_siderbar_wgt_hdl(WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION);
        banner_show_siderbar_get_item_visible_rect(BANNER_LOGO_HDR_DOLBY_VISION,&t_rect);
        t_rect.i4_left -= i4_offset_next;
        t_rect.i4_right -= i4_offset_next;
        if(e_type!=BANNER_LOGO_HDR_DOLBY_VISION)
        {
            i4_offset_next += (t_rect.i4_right - t_rect.i4_left + BANNER_SB_ICON_SPACE);
            wgl_status = WGL_SW_NORMAL;
        }

        BANNER_LOG_ON_FAIL(c_wgl_move(visibie_handle,&t_rect,WGL_NO_AUTO_REPAINT));

        /* set icon image buffer*/
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
        t_img_info.u_img_data.t_standard.t_enable    = h_img;
        t_img_info.u_img_data.t_standard.t_disable   = h_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_img;
        BANNER_LOG_ON_FAIL(c_wgl_do_cmd (visibie_handle,
                                        WGL_CMD_GL_SET_IMAGE,
                                        WGL_PACK(WGL_IMG_FG),
                                        WGL_PACK(&t_img_info)));
        BANNER_CHK_FAIL (c_wgl_set_visibility(visibie_handle,wgl_status));
        c_wgl_float(visibie_handle,TRUE,FALSE);
        banner_view_sidebar_showing.b_on_showing_icon_HDR = (wgl_status==WGL_SW_NORMAL?TRUE:FALSE);;

    }


    /* //repaint part
    BANNER_CHK_FAIL(c_wgl_set_visibility (t_g_view.h_bnr_siderbar_frame,WGL_SW_NORMAL));
    DBG_LOG_PRINT(("[NAV][sidebar][%s %d] next to show sidebar\n",__FUNCTION__,__LINE__));
    BANNER_CHK_FAIL(c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,TRUE));

    banner_cust_set_sidebar_showing(TRUE);

    BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_siderbar_auto_hide_timer));
    BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_auto_hide_timer,
                                 3000,
                                 X_TIMER_FLAG_ONCE,
                                 banner_siderbar_auto_hide_cb_fct,
                                 NULL));
    */
    {
        DBG_LOG_PRINT(("[NAV][sidebar][%s %d] delay to show sidebar\n",__FUNCTION__,__LINE__));
        delay_check_repeat_timer_count = 0;
        BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_siderbar_delay_show_timer));
        BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_siderbar_delay_show_timer,
                                     1000,
                                     X_TIMER_FLAG_ONCE,
                                     _banner_siderbar_check_to_show_cb_fct,
                                     NULL));
    }


    return NAVR_OK;
}



BOOL banner_hide_sidebar(VOID)
{
    BOOL val = FALSE;
    c_wgl_get_visibility(t_g_view.h_bnr_siderbar_frame,&val);
    //DBG_LOG_PRINT(("[banner_hide_sidebar] h_bnr_siderbar_frame visibility:%d \n",val));

    if(val == TRUE)
    {
        BANNER_CHK_FAIL(c_wgl_set_visibility (t_g_view.h_bnr_siderbar_frame,WGL_SW_HIDE_RECURSIVE));
        BANNER_CHK_FAIL(c_wgl_repaint(t_g_view.h_bnr_siderbar_frame,NULL,TRUE));
        c_timer_stop(t_g_view.h_siderbar_auto_hide_timer);

        banner_view_sidebar_showing.b_on_showing_text_HDR = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_HDR = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = FALSE;
        banner_view_sidebar_showing.b_on_showing_icon_FREESYNC = FALSE;
    }
    banner_cust_set_sidebar_showing(FALSE);
    c_wgl_get_visibility(t_g_view.h_bnr_siderbar_frame,&val);
    return val;
}

//just for mmp,but mmp do not use it any more(can be removed)
INT32 a_banner_show_hdr_info(BOOL b_show)
{
     if(b_show)
     {
          c_timer_stop(t_g_view.h_siderbar_auto_hide_timer);
          banner_show_siderbar_logo(e_g_video_hdr);
      }
      else
      {
          banner_show_siderbar_logo(BANNER_LOGO_HDR_SDR);
      }
      return NAVR_OK;
}

BOOL banner_view_set_b_ctrl_show_flag(BOOL val)
{

    b_ctrl_show_flag = val;
    return b_ctrl_show_flag;
}

BOOL banner_view_get_b_ctrl_show_flag(VOID)
{
    return b_ctrl_show_flag;
}

//for sidebar show switch
BOOL banner_view_set_sidebar_show_flag(BOOL val)
{

    b_sidebar_show_flag = val;
    return b_sidebar_show_flag;
}

BOOL banner_view_get_sidebar_show_flag(VOID)
{
    return b_sidebar_show_flag;
}

static VOID _banner_view_mm_update_cb_fct_msg_hdlr(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3)
{
    TV_WIN_ID_T  e_tv_win_id;
    ISL_REC_T    t_isl_rec               = {0};

    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec (e_tv_win_id, &t_isl_rec);
    if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL)
    {
        banner_mm_try();
    }
}


VOID banner_view_mm_update_cb_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag)
{
    nav_request_context_switch(_banner_view_mm_update_cb_fct_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);
}

INT32 banner_view_mm_update_start_timer(VOID)
{
    TV_WIN_ID_T  e_tv_win_id;
    ISL_REC_T    t_isl_rec               = {0};

    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec (e_tv_win_id, &t_isl_rec);
    if(t_isl_rec.e_src_type != INP_SRC_TYPE_VTRL)
    {
        DBG_LOG_PRINT(("[banner mi_mm] %s %d stop mm_update_timer\n",__FUNCTION__,__LINE__));
        c_timer_stop(t_g_view.h_mm_update_timer);
        banner_sys_info_reset_mm_update_info(FALSE);

        return NAVR_NO_ACTION;
    }

    DBG_LOG_PRINT(("[banner mi_mm] %s %d start mm_update_timer\n",__FUNCTION__,__LINE__));
    BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_mm_update_timer,
                                     1000,
                                     X_TIMER_FLAG_REPEAT,
                                     banner_view_mm_update_cb_fct,
                                     NULL));
    return NAVR_OK;
}


INT32 banner_view_mm_update_stop_timer(VOID)
{
    banner_sys_info_reset_mm_update_info(FALSE);

    DBG_LOG_PRINT(("[banner mi_mm] %s %d stop mm_update_timer\n",__FUNCTION__,__LINE__));
    BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_mm_update_timer));
    return NAVR_OK;
}


BOOL banner_view_set_name_update_flag(BOOL val)
{
    b_name_timer_update_flag = val;
    return b_name_timer_update_flag;
}


BOOL banner_view_get_name_update_flag(VOID)
{
    return b_name_timer_update_flag;
}

static VOID _banner_view_name_update_cb_action(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3)
{
    BANNER_ITEM_INFO_T*     pt_item_info    = NULL_HANDLE ;
    HANDLE_T                h_item          = NULL_HANDLE ;
    UTF16_T                 w2s_text[128]   = {0};
    UINT32                  ui4_name_len   = 0;
    /* search the specified items */
    pt_item_info = banner_get_item_info (BANNER_ITM_CH_NAME) ;
    if(pt_item_info == NULL_HANDLE)
    {
        return ;
    }
    h_item = *(pt_item_info->ph_handle) ;
    if(h_item == NULL_HANDLE)
    {
        return ;
    }
    ui4_name_len = c_uc_w2s_strlen(w2s_text_scrl_banner_name);
    if (i4_scrl_banner_name_offset + BANNEER_SCRL_INPUT_SRC_NAME_MAX > ui4_name_len + 1)
    {
        i4_scrl_banner_name_offset = 0;
    }
    c_uc_w2s_strncpy(w2s_text,w2s_text_scrl_banner_name + i4_scrl_banner_name_offset,BANNEER_SCRL_INPUT_SRC_NAME_MAX);
    BANNER_LOG_ON_FAIL(c_wgl_do_cmd(h_item,
                      WGL_CMD_TEXT_SET_TEXT,
                      w2s_text,
                      WGL_PACK((UINT16)0xFF)));

    c_wgl_repaint(h_item, NULL, FALSE);
    i4_scrl_banner_name_offset++;

}


static VOID banner_view_name_update_cb_fct(HANDLE_T  pt_tm_handle,
                                            VOID*     pv_tag)
{
    nav_request_context_switch(_banner_view_name_update_cb_action,
                               NULL,
                               NULL,
                               NULL);
}


INT32 banner_view_name_update_start_timer(VOID)
{
    i4_scrl_banner_name_offset = 0;
    if(banner_view_get_name_update_flag() \
        && (c_uc_w2s_strlen(w2s_text_scrl_banner_name) > BANNEER_SCRL_INPUT_SRC_NAME_MAX))
    {
        BANNER_LOG_ON_FAIL(c_timer_start(t_g_view.h_name_update_timer,
                                         500,
                                         X_TIMER_FLAG_REPEAT,
                                         banner_view_name_update_cb_fct,
                                         NULL));
    }
    return NAVR_OK;
}


INT32 banner_view_name_update_stop_timer(VOID)
{
    i4_scrl_banner_name_offset = 0;
    BANNER_LOG_ON_FAIL(c_timer_stop(t_g_view.h_name_update_timer));
    return NAVR_OK;
}

INT32 banner_view_update_scrl_banner_name(const UTF16_T *src,UINT32 len)
{
    if(c_uc_w2s_strlen(src) > BANNEER_SCRL_INPUT_SRC_NAME_MAX)
    {
        c_memset(w2s_text_scrl_banner_name,0,sizeof(w2s_text_scrl_banner_name));
        c_uc_w2s_strncpy(w2s_text_scrl_banner_name,src,len);
    }
    return NAVR_OK;
}

VOID banner_view_update_logo_flag(BANNER_SIDERBAR_LOGO e_type)
{
    DBG_LOG_PRINT((" %s %d BANNER_SIDERBAR_LOGO[%d]\n",__FUNCTION__,__LINE__,e_type));
    switch(e_type)
    {
        case BANNER_LOGO_HDR_SDR:
        case BANNER_LOGO_HDR_HDR10_PLUS:
        case BANNER_LOGO_HDR_HLG:
        case BANNER_LOGO_HDR_HDR10:
        case BANNER_LOGO_HDR_DOLBY_VISION:
        default:
            DBG_LOG_PRINT((" %s %d No need to update flag\n",__FUNCTION__,__LINE__));
            break;

        case BANNER_LOGO_DOLBY_AUDIO:
            banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = TRUE;
            banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = FALSE;
            break;
        case BANNER_LOGO_DOLBY_ATMOS:
            banner_view_sidebar_showing.b_on_showing_icon_DD_AUDIO = FALSE;
            banner_view_sidebar_showing.b_on_showing_icon_DD_ATMOS = TRUE;
            break;
        case BANNER_LOGO_PROGAMING_ENGINE:
            banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = TRUE;
            banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = FALSE;
            break;
        case BANNER_LOGO_V_GAMING_ENGINE:
            banner_view_sidebar_showing.b_on_showing_icon_PROGAMING_ENGINE = FALSE;
            banner_view_sidebar_showing.b_on_showing_icon_V_GAMING_ENGINE = TRUE;
            break;
        case BANNER_LOGO_FILMMAKER_MODE:
            banner_view_sidebar_showing.b_on_showing_icon_FILMMAKER_MODE = TRUE;
            break;
        case BANNER_LOGO_FREESYNC:
            banner_view_sidebar_showing.b_on_showing_icon_FREESYNC = TRUE;
            break;
    }

}




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
 * $RCSfile: nav_power_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_NAV_PWR_SUPPORT

#include <stdio.h>
#include <unistd.h>

#include "res/nav/nav_variant.h"

#include "u_common.h"
#include "u_irrc_btn_def.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "app_util/a_icl_common.h"
#include "bgm/a_bgm.h"
#include "nav/power/a_nav_power.h"
#include "nav/power/nav_power.h"
#include "nav/power/nav_power_view.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/nav/power/nav_power_view_rc.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "am/a_am.h"
#include "wdk/a_wdk.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif
#include "res/msgconvert/msgconvert_custom.h"
#include "res/app_util/icl/a_icl_custom.h"


/*-----------------------------------------------------------------------------
 * Compile option description
 *---------------------------------------------------------------------------*/

/*

NAV_PWR_VIEW_CUSTOM_TITLE: There will be a Title added under the frame.

*/

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define _NAV_PWR_VIEW_IS_SYNC_REPAINT           (TRUE)
#define _NAV_PWR_VIEW_TIMER_STOP                (0)
#define _NAV_PWR_VIEW_TIMER_LISTEN              (1)
#define _NAV_PWR_VIEW_TIMER_WARNING             (2)


/*backward compatible*/
#ifndef NAV_PWR_VIEW_TV_AV_TIMEOUT_DUR
#define NAV_PWR_VIEW_TV_AV_TIMEOUT_DUR          (30 * 60000)  /* 30 mins */
#endif

#ifndef NAV_PWR_VIEW_TV_TIMEOUT_DUR
#define NAV_PWR_VIEW_TV_TIMEOUT_DUR             NAV_PWR_VIEW_TV_AV_TIMEOUT_DUR
#endif

#ifndef NAV_PWR_VIEW_TV_WARNING_DUR
#define NAV_PWR_VIEW_TV_WARNING_DUR             ((UINT32)0)
#endif

#ifndef NAV_PWR_VIEW_DVD_TIMEOUT_DUR
#define NAV_PWR_VIEW_DVD_TIMEOUT_DUR            NAV_PWR_VIEW_TV_AV_TIMEOUT_DUR
#endif

#ifndef NAV_PWR_VIEW_DVD_WARNING_DUR
#define NAV_PWR_VIEW_DVD_WARNING_DUR            ((UINT32)0)
#endif

#ifndef NAV_PWR_VIEW_AV_TIMEOUT_DUR
#define NAV_PWR_VIEW_AV_TIMEOUT_DUR             NAV_PWR_VIEW_TV_AV_TIMEOUT_DUR
#endif

#ifndef NAV_PWR_VIEW_AV_WARNING_DUR
#define NAV_PWR_VIEW_AV_WARNING_DUR             ((UINT32)0)
#endif

typedef struct __NAV_PWR_VIEW_MEMBER_T
{
    HANDLE_T                    h_off_timer;

    /*widget instance*/
    HANDLE_T                    h_frame;
    HANDLE_T                    h_text;
    HANDLE_T                    h_text_title;     /* Only take affects if NAV_PWR_VIEW_CUSTOM_TITLE is defined */

    /*template image*/
    WGL_HIMG_TPL_T              h_img_bk;

    NAV_PWR_SRC_TYPE_T          e_src_type;       /* The current input source */

    UINT8                       ui1_lang_id;

    BOOL                        b_is_on;          /* The Warning Message is shown , so called VGA-WARNING state */
    BOOL                        b_is_listen;      /* VGA-LISTEN state */
    POWER_OFF_STATUS            e_status;         /* power off status*/
    BOOL                        b_is_normal;     /*TRUE --normal, FALSE-PIP/POP*/
    /* Remark:

       If e_src_type != NAV_PWR_SRC_TYPE_VGA && b_is_listen == TRUE
       implies
       SIGNAL-LISTEN state for TV/AV input src.

    */

} _NAV_PWR_VIEW_MEMBER_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static WDK_OSD_TOAST_T      t_g_wdk_view = {0};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_init(HANDLE_T                h_canvas,
                                   INT32                   i4_frame_x_offset,
                                   INT32                   i4_frame_y_offset,
                                   APP_COLOR_TYPE_T        e_color_type,
                                   VOID**                  ppv_view,
                                   NAV_PWR_ON_COND_T*      pe_on_cond,
                                   NAV_PWR_OFF_COND_T*     pe_off_cond);

static INT32 _nav_pwr_view_deinit(VOID*                 pv_view);

static INT32 _nav_pwr_view_data_change(VOID*                        pv_view,
                                              NAV_PWR_UI_INFO_FIELD_T      e_update_field,
                                              const NAV_PWR_UI_INFO_T*     pt_update_data);

static INT32 _nav_pwr_view_hide(VOID*                   pv_view);

static INT32 _nav_pwr_view_show(_NAV_PWR_VIEW_MEMBER_T* pt_this);

/*rc-related*/
static INT32 _nav_pwr_view_image_create(_NAV_PWR_VIEW_MEMBER_T*     pt_this);

static INT32 _nav_pwr_view_ui_create(_NAV_PWR_VIEW_MEMBER_T*        pt_this,
                                          HANDLE_T                       h_canvas,
                                          INT32                          i4_frame_x_offset,
                                          INT32                          i4_frame_y_offset,
                                          APP_COLOR_TYPE_T               e_color_type);

static INT32 _nav_pwr_view_ui_load_skin(_NAV_PWR_VIEW_MEMBER_T*     pt_this,
                                              APP_COLOR_TYPE_T            e_color_type);

static INT32 _nav_pwr_view_count_down(_NAV_PWR_VIEW_MEMBER_T*       pt_this,
                                              BOOL                          b_on,
                                              BOOL                          b_is_normal,
                                              NAV_PWR_SRC_TYPE_T            e_src_type);

/*timer*/
static VOID _nav_pwr_view_reset_off_timer(_NAV_PWR_VIEW_MEMBER_T*   pt_this,
                                                UINT32                    ui4_timer_type);

static INT32 _nav_pwr_view_power_off_listen_timer_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this);
static INT32 _nav_pwr_view_power_off_listen_timer_stop(_NAV_PWR_VIEW_MEMBER_T*   pt_this);
static UINT32 _nav_pwr_view_power_off_listen_timer_during_check(_NAV_PWR_VIEW_MEMBER_T*   pt_this);


static INT32 _nav_pwr_view_power_off_warning_timer_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this);
static INT32 _nav_pwr_view_power_off_warning_timer_stop(_NAV_PWR_VIEW_MEMBER_T*   pt_this);
static UINT32 _nav_pwr_view_power_off_warning_timer_during_check(_NAV_PWR_VIEW_MEMBER_T*   pt_this);


static INT32 _nav_pwr_view_power_off_listen_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this);
static INT32 _nav_pwr_view_power_off_listen_stop(_NAV_PWR_VIEW_MEMBER_T * pt_this);

static INT32 _nav_pwr_view_power_off_warning_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this);
static INT32 _nav_pwr_view_power_off_warning_stop(_NAV_PWR_VIEW_MEMBER_T * pt_this);

static INT32 _nav_pwr_view_power_off_stop(_NAV_PWR_VIEW_MEMBER_T*   pt_this);

static VOID _nav_pwr_view_off_cb(HANDLE_T                      h_timer,
                                      VOID*                         pv_this);

static VOID _nav_pwr_view_off_msg_hdlr(VOID*                        pv_this,
                                              VOID*                        pv_unused2,
                                              VOID*                        pv_unused3);
static INT32 _nav_pwr_view_get_status(_NAV_PWR_VIEW_MEMBER_T*   pt_this);

static INT32 _nav_pwr_view_set_status(_NAV_PWR_VIEW_MEMBER_T*   pt_this, POWER_OFF_STATUS e_status);

static INT32 _nav_pwr_view_update_status(_NAV_PWR_VIEW_MEMBER_T*   pt_this);
/*-----------------------------------------------------------------------------
 * public methods declarations
 *---------------------------------------------------------------------------*/

extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

POWER_OFF_STATUS nav_pwr_view_get_status(VOID*    pv_view)
{
    return _nav_pwr_view_get_status(pv_view);
}

static POWER_OFF_STATUS _nav_pwr_view_get_status(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    if(pt_this->b_is_on == TRUE)
    {
        pt_this->e_status = POWER_OFF_WARNING;
    }
    else if(pt_this->b_is_listen == TRUE)
    {
        pt_this->e_status = POWER_OFF_LISTEN;
    }
    else
    {
        pt_this->e_status = POWER_OFF_OFF;
    }
    return  pt_this->e_status;
}

static INT32 _nav_pwr_view_set_status(_NAV_PWR_VIEW_MEMBER_T*   pt_this, POWER_OFF_STATUS e_status)
{
    if(_nav_pwr_view_get_status(pt_this) == e_status)
    {
        DBG_LOG_PRINT(("[Power] warning: status already setup \n"));
        return NAVR_OK;
    }
    switch(e_status)
    {
        case POWER_OFF_OFF:
            {
                pt_this->b_is_on  = FALSE;
                pt_this->b_is_listen = FALSE;
            }
            break;
        case POWER_OFF_LISTEN:
            {
                pt_this->b_is_on  = FALSE;
                pt_this->b_is_listen = TRUE;
            }
            break;
        case POWER_OFF_WARNING:
            {
                pt_this->b_is_on  = TRUE;
                pt_this->b_is_listen = FALSE;
            }
            break;
        default:
            return NAVR_FAIL;
    }

    pt_this->e_status = e_status;
    DBG_LOG_PRINT(("[Power] set status : %d\n", pt_this->e_status));
    return NAVR_OK;
}

INT32 nav_pwr_set_status(VOID*   pv_view, POWER_OFF_STATUS e_status)
{
    _NAV_PWR_VIEW_MEMBER_T*            pt_this = (_NAV_PWR_VIEW_MEMBER_T*)pv_view;

    if(_nav_pwr_view_get_status(pt_this) == e_status)
    {
        DBG_LOG_PRINT(("[Power] warning: status already setup \n"));
        return NAVR_OK;
    }
    switch(e_status)
    {
        case POWER_OFF_OFF:
            {
                pt_this->b_is_on  = FALSE;
                pt_this->b_is_listen = FALSE;
            }
            break;
        case POWER_OFF_LISTEN:
            {
                pt_this->b_is_on  = FALSE;
                pt_this->b_is_listen = TRUE;
            }
            break;
        case POWER_OFF_WARNING:
            {
                pt_this->b_is_on  = TRUE;
                pt_this->b_is_listen = FALSE;
            }
            break;
        default:
            return NAVR_FAIL;
    }

    pt_this->e_status = e_status;
    DBG_LOG_PRINT(("[Power][%s %d] set status : %d,b_is_on = %d,b_is_listen=%d\n",__FUNCTION__,__LINE__, pt_this->e_status,pt_this->b_is_on,pt_this->b_is_listen = TRUE));
    return NAVR_OK;
}

static INT32 _nav_pwr_view_update_status(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    INT32  i4_ret = NAVR_OK;

    {
        POWER_OFF_STATUS     e_status = POWER_OFF_UNKNOW;

        e_status = _nav_pwr_view_get_status(pt_this);
        switch(e_status)
        {
           case POWER_OFF_LISTEN: /* reset timer */
               {
                  _nav_pwr_view_reset_off_timer(pt_this, _NAV_PWR_VIEW_TIMER_LISTEN);
               }
               break;
           case POWER_OFF_WARNING:  /* reset warning to listen */
               {
                   i4_ret = _nav_pwr_view_power_off_warning_stop(pt_this);
                   NAV_CHK_FAIL(i4_ret);
                   i4_ret = _nav_pwr_view_power_off_listen_start(pt_this);
                   NAV_CHK_FAIL(i4_ret);
               }
               break;
          case POWER_OFF_OFF:    /* stop power off */
                {
                    i4_ret = _nav_pwr_view_power_off_stop(pt_this);
                    NAV_CHK_FAIL(i4_ret);
                }
               break;
          default:
                {
                    NAV_LOG_ON_FAIL(NAVR_NOT_ALLOW);
                }
         }
    }
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _warning_toast_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_init(HANDLE_T  h_canvas)
{
    WDK_TOAST_PARAM_T     t_widget_param;
    INT32                 i4_ret = NAVR_OK;

    c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));

    t_widget_param.e_toast_style = WDK_WARNING_TOAST;

    i4_ret = a_wdk_toast_init(h_canvas, (VOID*)(&t_widget_param), &t_g_wdk_view);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      scrn_svr_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_deinit(VOID)
{
    a_wdk_toast_deinit(&t_g_wdk_view);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_toast_view_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_show(UTF16_T*  pw2s_string)
{
    WDK_TOAST_PARAM_T     t_widget_param;
    INT32                 i4_ret = NAVR_OK;

    c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));
    t_widget_param.e_toast_style = WDK_WARNING_TOAST;
    t_widget_param.w2s_str       = (VOID*)pw2s_string;
    t_widget_param.pf_cb         = NULL;

    i4_ret = a_wdk_toast_activate(FALSE, (VOID*)(&t_widget_param), &t_g_wdk_view);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_toast_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_hide(VOID)
{
    INT32                 i4_ret = NAVR_OK;

    i4_ret = a_wdk_toast_hide(TRUE, NULL,&t_g_wdk_view);
    a_scrn_svr_set_enable(TRUE);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_pwr_get_default_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL _nav_pwr_is_unexpect_active_comp(VOID)
{
    NAV_COMP_ID_T      e_active_comp;

    e_active_comp = nav_get_active_component();

    if((e_active_comp == NAV_COMP_ID_LAST_VALID_ENTRY) ||
       (e_active_comp == NAV_COMP_ID_SCREEN_SAVER)  ||
       (e_active_comp == NAV_COMP_ID_PWD_DLG))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_pwr_get_default_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_pwr_get_default_handler(NAV_PWR_VIEW_HANDLER_T*  pt_view_handler)
{
    NAV_ASSERT(pt_view_handler);

    pt_view_handler->pf_init = _nav_pwr_view_init;
    pt_view_handler->pf_deinit = _nav_pwr_view_deinit;
    pt_view_handler->pf_data_change = _nav_pwr_view_data_change;
    pt_view_handler->pf_hide = _nav_pwr_view_hide;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_init(
    HANDLE_T                    h_canvas,
    INT32                       i4_frame_x_offset,
    INT32                       i4_frame_y_offset,
    APP_COLOR_TYPE_T            e_color_type,
    VOID**                      ppv_view,
    NAV_PWR_ON_COND_T*          pe_on_cond,
    NAV_PWR_OFF_COND_T*         pe_off_cond)
{
    _NAV_PWR_VIEW_MEMBER_T*     pt_this;
    INT32                       i4_ret;

    /*new instance*/
    pt_this = c_mem_alloc(sizeof(_NAV_PWR_VIEW_MEMBER_T));
    if(NULL == pt_this)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to alloc memory, size = %d\r\n", __FUNCTION__, sizeof(_NAV_PWR_VIEW_MEMBER_T)));
        return NAVR_OUT_OF_MEM;
    }

    /*init member*/
    c_memset(pt_this, 0, sizeof(_NAV_PWR_VIEW_MEMBER_T));
    pt_this->ui1_lang_id = 0xFF;
    pt_this->e_src_type = NAV_PWR_SRC_TYPE_UNKNOWN;

    do
    {
        /*off timer*/
        i4_ret = c_timer_create(&pt_this->h_off_timer);
        if(OSR_OK != i4_ret)
        {
            pt_this->h_off_timer = NULL_HANDLE;
            break;
        }

        /*create toast*/
        i4_ret = _warning_toast_view_init(h_canvas);
        if(NAVR_OK != i4_ret)
        {
            break;
        }

        /*create template image*/
        i4_ret = _nav_pwr_view_image_create(pt_this);
        if(NAVR_OK != i4_ret)
        {
            break;
        }

        /*create widget*/
        i4_ret = _nav_pwr_view_ui_create(pt_this, h_canvas, i4_frame_x_offset, i4_frame_y_offset, e_color_type);
        if(NAVR_OK != i4_ret)
        {
            break;
        }

        /**/
        i4_ret = _nav_pwr_view_ui_load_skin(pt_this, e_color_type);
        if(NAVR_OK != i4_ret)
        {
            break;
        }

        /**/
        *ppv_view = pt_this;
        *pe_on_cond =  (NAV_PWR_ON_COND_T) (NAV_PWR_ONC_TV_NO_SIGNAL | NAV_PWR_ONC_AV_NO_SIGNAL | NAV_PWR_ONC_DVD_NO_SIGNAL | NAV_PWR_ONC_VGA_NO_SIGNAL);
        *pe_off_cond = (NAV_PWR_OFF_COND_T) (NAV_PWR_OFC_APP_PAUSE | NAV_PWR_OFC_NOT_NORMAL_TV);
        return NAVR_OK;

    } while(0);

    _nav_pwr_view_deinit(pt_this);
    return NAVR_FAIL;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 _nav_pwr_view_deinit(VOID*   pv_view)
{
    _NAV_PWR_VIEW_MEMBER_T* pt_this = (_NAV_PWR_VIEW_MEMBER_T*)pv_view;

    _warning_toast_view_deinit();

    if(NULL == pt_this)
    {
        return NAVR_OK;
    }

    /*free timer*/
    if(TRUE == c_handle_valid(pt_this->h_off_timer))
    {
        c_timer_delete(pt_this->h_off_timer);
    }

    /*free widget*/
    if(TRUE == c_handle_valid(pt_this->h_text))
    {
        c_wgl_destroy_widget(pt_this->h_text);
    }

    /*free frame*/
    if(TRUE == c_handle_valid(pt_this->h_frame))
    {
        c_wgl_destroy_widget(pt_this->h_frame);
    }

    /*free images*/
    if(TRUE == c_handle_valid(pt_this->h_img_bk))
    {
        c_wgl_img_tpl_destroy(pt_this->h_img_bk);
    }

    /*reset memory before free*/
    c_memset(pt_this, (UINT8)'N', sizeof(_NAV_PWR_VIEW_MEMBER_T));

    /*free memory*/
    c_mem_free(pt_this);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_data_change
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_data_change(
    VOID*                              pv_view,
    NAV_PWR_UI_INFO_FIELD_T            e_update_field,
    const NAV_PWR_UI_INFO_T*           pt_update_data)
{
    _NAV_PWR_VIEW_MEMBER_T*            pt_this = (_NAV_PWR_VIEW_MEMBER_T*)pv_view;
    UINT8                              ui1_icl_val = ICL_USB_UPGRADE_STATUS_NONE;
    SIZE_T                             z_size = ICL_RECID_USB_UPGRADE_STATUS_SIZE;
    BOOL    b_dpms = FALSE;

    NAV_ASSERT(pv_view);
    a_cfg_get_dpms(&b_dpms);
    if (!b_dpms) 
    {
        DBG_LOG_PRINT(("[power][%s %d] stop auto power off beause ui setting is off\n",__FUNCTION__,__LINE__));
        NAV_CHK_FAIL(_nav_pwr_view_power_off_stop(pt_this));
        return NAVR_OK;
    }
    if(NAV_PWR_UI_IF_MEET_COND & e_update_field)
    {
        if(pt_update_data->b_is_meet)
        {
            a_icl_get(ICL_MAKE_ID (ICL_GRPID_USB_UPGRADE, ICL_RECID_USB_UPGRADE_STATUS),
                      &ui1_icl_val,
                      &z_size);

            if(ICL_USB_UPGRADE_STATUS_RUNNING == ui1_icl_val)
            {
                DBG_LOG_PRINT(("[power][%s %d] UTV UPGRADE skip start auto power off\n",__FUNCTION__,__LINE__));
                return NAVR_OK;
            }

            if(TRUE == a_bgm_is_running() || FALSE == a_am_is_power_on())
            {
                DBG_LOG_PRINT(("[power][%s %d] bgm mode skip start auto power off\n",__FUNCTION__,__LINE__));
                return NAVR_OK;
            }
        }
        NAV_CHK_FAIL(_nav_pwr_view_count_down(pt_this, pt_update_data->b_is_meet, pt_update_data->b_normal, pt_update_data->e_src_type));
    }

    if(NAV_PWR_UI_FORCE_STOP_TIMER & e_update_field)
    {
        NAV_CHK_FAIL(_nav_pwr_view_power_off_stop(pt_this));
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_hide(VOID*  pv_view)
{
    _NAV_PWR_VIEW_MEMBER_T*     pt_this = (_NAV_PWR_VIEW_MEMBER_T*)pv_view;
    INT32                       i4_ret;

    NAV_ASSERT(pv_view);

    if(FALSE == pt_this->b_is_on)
    {
        return NAVR_OK;
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_stop(APP_TTS_STOP_FORCE);
#endif

    i4_ret = _warning_toast_view_hide();
    if (WDKR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): _warning_toast_view_hide() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_show(_NAV_PWR_VIEW_MEMBER_T*     pt_this)
{
    UTF16_T                     *w2s_title;
    INT32                       i4_ret;
    UINT8                       ui1_lang_id;

    if(_nav_pwr_view_get_status(pt_this) == POWER_OFF_WARNING)
    {
        return NAVR_OK;
    }

    ui1_lang_id = nav_get_mlm_lang_id();

    {
        switch(pt_this->e_src_type)
        {
            case NAV_PWR_SRC_TYPE_VGA:
                w2s_title = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_PWR_VIEW_NO_VGA);
                break;
            case NAV_PWR_SRC_TYPE_VTRL:
                 w2s_title = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_PWR_VIEW_NO_NAVIGATION);
                break;
            case NAV_PWR_SRC_TYPE_TV:
            case NAV_PWR_SRC_TYPE_DVD:
            case NAV_PWR_SRC_TYPE_OTHER:
            default:
                w2s_title = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_PWR_VIEW_NO_SIGNAL);
                break;
        }
        /*save current lang_id*/
        pt_this->ui1_lang_id = ui1_lang_id;
    }

    nav_hide_components(COMP_EXEC_SET_POWER);

    i4_ret = _warning_toast_view_show(w2s_title);
    if (WDKR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): _warning_toast_view_show() failed. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(w2s_title, c_uc_w2s_strlen(w2s_title));
#endif

    nav_set_component_visible(NAV_COMP_ID_POWER);
#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_BANNER));
#endif
    a_scrn_svr_set_enable(FALSE);


    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_image_create
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_image_create(
    _NAV_PWR_VIEW_MEMBER_T*             pt_this)
{
    INT32                               i4_ret;
#ifdef NAV_PWR_VIEW_BK_IMG

    i4_ret = c_wgl_img_tpl_create(NAV_PWR_VIEW_BK_STYLE,
                                  &NAV_PWR_VIEW_BK_IMG,
                                  &pt_this->h_img_bk);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to create background image. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

#else
    i4_ret = nav_img_create_scr_svr_bk_img_tpl(&pt_this->h_img_bk);
    if(NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_ui_create
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_ui_create(
    _NAV_PWR_VIEW_MEMBER_T*          pt_this,
    HANDLE_T                         h_canvas,
    INT32                            i4_frame_x_offset,
    INT32                            i4_frame_y_offset,
    APP_COLOR_TYPE_T                 e_color_type)
{
    GL_RECT_T                        t_rect;
    INT32                            i4_ret;

    /* create frame */
    SET_RECT_BY_SIZE(&t_rect,
                     NAV_PWR_VIEW_FRAME_LEFT + i4_frame_x_offset,
                     NAV_PWR_VIEW_FRAME_TOP + i4_frame_y_offset,
                     NAV_PWR_VIEW_FRAME_WIDTH,
                     NAV_PWR_VIEW_FRAME_HEIGHT);

    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 DEFAULT_BK_ALPHA,
                                 NULL,
                                 pt_this,
                                 &pt_this->h_frame);
    if(WGLR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    do
    {
        /* create text */
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_PWR_VIEW_TEXT_LEFT,
                         NAV_PWR_VIEW_TEXT_TOP,
                         NAV_PWR_VIEW_TEXT_WIDTH,
                         NAV_PWR_VIEW_TEXT_HEIGHT);

        i4_ret = c_wgl_create_widget(pt_this->h_frame,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     DEFAULT_BK_ALPHA,
                                     (VOID*)((NAV_PWR_VIEW_TEXT_STYLE) | WGL_STL_GL_NO_IMG_UI | WGL_STL_GL_NO_BK),
                                     NULL,
                                     &pt_this->h_text);

#ifdef NAV_PWR_VIEW_CUSTOM_TITLE
        /* create title text */
        SET_RECT_BY_SIZE(&t_rect,
                         NAV_PWR_VIEW_TEXT_TITLE_LEFT,
                         NAV_PWR_VIEW_TEXT_TITLE_TOP,
                         NAV_PWR_VIEW_TEXT_TITLE_WIDTH,
                         NAV_PWR_VIEW_TEXT_TITLE_HEIGHT);

        i4_ret = c_wgl_create_widget(pt_this->h_frame,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     DEFAULT_BK_ALPHA,
                                     (VOID*)((NAV_PWR_VIEW_TEXT_TITLE_STYLE) | WGL_STL_GL_NO_IMG_UI | WGL_STL_GL_NO_BK),
                                     NULL,
                                     &pt_this->h_text_title);
#endif /* NAV_PWR_VIEW_CUSTOM_TITLE */

        if(WGLR_OK != i4_ret)
        {
            break;
        }

        return NAVR_OK;

    } while(0);

    /*free widget*/
    if(TRUE == c_handle_valid(pt_this->h_frame))
    {
        c_wgl_destroy_widget(pt_this->h_frame);
        pt_this->h_frame = NULL_HANDLE;
    }

    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_ui_load_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_ui_load_skin(
    _NAV_PWR_VIEW_MEMBER_T*             pt_this,
    APP_COLOR_TYPE_T                    e_color_type)
{
    WGL_FONT_INFO_T                     t_font_info = NAV_PWR_VIEW_TEXT_FONT;
    WGL_COLOR_INFO_T                    t_clr_info;
    WGL_IMG_INFO_T                      t_img_info;
    WGL_INSET_T                         t_inset;
    INT32                               i4_ret;

    /*background image*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_this->h_img_bk;

    i4_ret = c_wgl_do_cmd(pt_this->h_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set frame's bk-image. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set text color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    NAV_PWR_VIEW_CLR_TEXT(e_color_type, t_clr_info.u_color_data.t_standard.t_disable);
    t_clr_info.u_color_data.t_standard.t_enable    = t_clr_info.u_color_data.t_standard.t_disable;
    t_clr_info.u_color_data.t_standard.t_highlight = t_clr_info.u_color_data.t_standard.t_disable;

    i4_ret = c_wgl_do_cmd(pt_this->h_text,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_TEXT,
                          (VOID*)&t_clr_info);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text's string color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set event title inset */
    NAV_PWR_VIEW_TEXT_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_this->h_text,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          (VOID*)&t_inset,
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text's inset. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set title align */
    i4_ret = c_wgl_do_cmd(pt_this->h_text,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)NAV_PWR_VIEW_TEXT_ALIGNMENT,
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text's alignment. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set msg font */
    i4_ret = c_wgl_do_cmd(pt_this->h_text,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_font_info,
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text's font info. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

#ifdef NAV_PWR_VIEW_CUSTOM_TITLE

    /* set text title color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    NAV_PWR_VIEW_CLR_TEXT_TITLE(e_color_type, t_clr_info.u_color_data.t_standard.t_disable);
    t_clr_info.u_color_data.t_standard.t_enable    = t_clr_info.u_color_data.t_standard.t_disable;
    t_clr_info.u_color_data.t_standard.t_highlight = t_clr_info.u_color_data.t_standard.t_disable;

    i4_ret = c_wgl_do_cmd(pt_this->h_text_title,
                          WGL_CMD_GL_SET_COLOR,
                          (VOID*)WGL_CLR_TEXT,
                          (VOID*)&t_clr_info);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text title's string color. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set event title inset */
    NAV_PWR_VIEW_TEXT_TITLE_INSET(t_inset.i4_left, t_inset.i4_top, t_inset.i4_right, t_inset.i4_bottom);
    i4_ret = c_wgl_do_cmd(pt_this->h_text_title,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          (VOID*)&t_inset,
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text title's inset. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set text title align */
    i4_ret = c_wgl_do_cmd(pt_this->h_text_title,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)NAV_PWR_VIEW_TEXT_TITLE_ALIGNMENT,
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text title's alignment. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    /* set msg font */
    i4_ret = c_wgl_do_cmd(pt_this->h_text_title,
                          WGL_CMD_GL_SET_FONT,
                          (VOID*)&t_font_info,
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        DBG_ERROR((_ERROR_HEADER"%s(): Fail to set text title's font info. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

#endif /* NAV_PWR_VIEW_CUSTOM_TITLE */

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_count_down
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_pwr_view_count_down(
    _NAV_PWR_VIEW_MEMBER_T*           pt_this,
    BOOL                              b_on,
    BOOL                              b_is_normal,
    NAV_PWR_SRC_TYPE_T                e_src_type)
{
    if((pt_this->b_is_listen == b_on) && b_on)
    {
        return NAVR_OK;
    }

    pt_this->e_src_type = e_src_type;
    pt_this->b_is_normal = b_is_normal;

    DBG_LOG_PRINT(("[power][%s %d] auto power off %s\n",__FUNCTION__,__LINE__,b_on ? "START" : "STOP"));

    if(b_on)
    {
       NAV_CHK_FAIL(_nav_pwr_view_power_off_listen_start(pt_this));
    }
    else
    {
       NAV_CHK_FAIL(_nav_pwr_view_power_off_stop(pt_this));
    }

    return NAVR_OK;
}

static INT32 _nav_pwr_view_power_off_listen_timer_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    INT32           i4_ret = NAVR_OK;
    UINT32          ui4_dur = 0;

    if( pt_this == NULL)
    {
        return NAVR_INV_ARG;
    }

    ui4_dur = _nav_pwr_view_power_off_listen_timer_during_check(pt_this);

    if(ui4_dur != 0)
    {
        i4_ret = c_timer_start(pt_this->h_off_timer,
                               ui4_dur,
                               X_TIMER_FLAG_ONCE,
                               _nav_pwr_view_off_cb,
                               pt_this);
        NAV_CHK_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);
    }
    else
    {
        DBG_INFO(("[NAV][Power][Reset_Off_Timer] The TV/AV timeout power down timer disabled \n"));
        /* Do nothing */
        /* Disable the TV/AV Timeout Feature */
    }

    return NAVR_OK;
}
static INT32 _nav_pwr_view_power_off_listen_timer_stop(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    INT32 i4_ret = NAVR_OK;
    if(pt_this == NULL)
    {
        return NAVR_INV_ARG;
    }
    i4_ret = c_timer_stop(pt_this->h_off_timer);
    NAV_CHK_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);

    return NAVR_OK;
}

static UINT32 _nav_pwr_view_power_off_listen_timer_during_check(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    INT32  i4_ret = NAVR_OK;
    UINT32 ui4_dur = 0;

    if( pt_this == NULL)
    {
        return NAVR_INV_ARG;
    }

    switch(pt_this->e_src_type)
    {
        case NAV_PWR_SRC_TYPE_VGA:
            if(pt_this->b_is_normal)
            {
                ui4_dur = NAV_PWR_VIEW_LISTEN_DUR;
            }
            else
            {
                ui4_dur = NAV_PWR_VIEW_TV_TIMEOUT_DUR;
            }

            break;
        case NAV_PWR_SRC_TYPE_TV:
            ui4_dur = NAV_PWR_VIEW_TV_TIMEOUT_DUR;
            break;
        case NAV_PWR_SRC_TYPE_DVD:
            ui4_dur = NAV_PWR_VIEW_DVD_TIMEOUT_DUR;
            break;
        case NAV_PWR_SRC_TYPE_VTRL:
            ui4_dur = NAV_PWR_VIEW_SCH_TIMEOUT_DUR;
            break;
        case NAV_PWR_SRC_TYPE_OTHER:
            ui4_dur = NAV_PWR_VIEW_AV_TIMEOUT_DUR;
            break;
        default:
            ui4_dur = NAV_PWR_VIEW_TV_TIMEOUT_DUR;
            break;
    }

#if defined(NAV_PWR_VIEW_TV_TIMEOUT_DUR) || defined(NAV_PWR_VIEW_DVD_TIMEOUT_DUR) || defined(NAV_PWR_VIEW_AV_WARNING_DUR)
    {
        UINT8                                  ui1_factory_mode;
        ACFG_RETAIL_MODE_T                     t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
        UINT8       ui1_input_id = 0;
        ISL_REC_T   t_isl_rec;

        a_cfg_get_input_src(SN_PRES_MAIN_DISPLAY, &ui1_input_id);

        a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);

        if(t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL&&!msg_convert_custom_airplay_active())
        {
            ui4_dur = NAV_PWR_VIEW_SCH_TIMEOUT_DUR;
        }

        /*Get factory mode*/
        i4_ret = a_cfg_get_factory_mode(&ui1_factory_mode);
        if(APP_CFGR_OK != i4_ret)
        {
            ui1_factory_mode = APP_CFG_FAC_MODE_NORMAL;
        }

        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

        if( ui1_factory_mode != 0
#ifdef APP_ENERGY_STAR
            || ACFG_RETAIL_MODE_NORMAL == t_retail_mode
#endif
          )
        {
            ui4_dur = 0;
        }
    }
#endif

    DBG_LOG_PRINT(("[Power] ckeck listen timer ui_dur %d\n",ui4_dur));

    return ui4_dur;
}

static INT32 _nav_pwr_view_power_off_warning_timer_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    UINT32          ui4_dur = 0;

    if(pt_this == NULL)
    {
        return NAVR_INV_ARG;
    }

    ui4_dur = _nav_pwr_view_power_off_warning_timer_during_check(pt_this);

    if(0 != ui4_dur)
    {
         c_timer_start(pt_this->h_off_timer,
                       ui4_dur,
                       X_TIMER_FLAG_ONCE,
                       _nav_pwr_view_off_cb,
                       pt_this);
    }
    else
    {
        /*shutdown system*/
        nav_pwr_power_off((NAV_PWR_SRC_TYPE_VGA == pt_this->e_src_type) ? NAV_PWR_WM_VGA : NAV_PWR_WM_EMPTY);
    }

    return NAVR_OK;
}
static INT32 _nav_pwr_view_power_off_warning_timer_stop(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    INT32           i4_ret = NAVR_OK;

    if( pt_this == NULL)
    {
        return NAVR_INV_ARG;
    }

    i4_ret = c_timer_stop(pt_this->h_off_timer);
    NAV_CHK_FAIL(OSR_OK == i4_ret ? NAVR_OK : i4_ret);
    return NAVR_OK;
}
static UINT32 _nav_pwr_view_power_off_warning_timer_during_check(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    UINT32          ui4_dur = 0;

    if(pt_this == NULL)
    {
        return NAVR_INV_ARG;
    }

    switch(pt_this->e_src_type)
    {
        case NAV_PWR_SRC_TYPE_VGA:
            if(pt_this->b_is_normal)
            {
                ui4_dur = NAV_PWR_VIEW_WARNING_DUR;
            }
            else
            {
                ui4_dur = NAV_PWR_VIEW_TV_WARNING_DUR;
            }
            break;
        case NAV_PWR_SRC_TYPE_TV:
            ui4_dur = NAV_PWR_VIEW_TV_WARNING_DUR;
            break;
        case NAV_PWR_SRC_TYPE_DVD:
            ui4_dur = NAV_PWR_VIEW_DVD_WARNING_DUR;
            break;
        case NAV_PWR_SRC_TYPE_VTRL:
            ui4_dur = NAV_PWR_VIEW_SCH_WARNING_DUR;
            break;
        case NAV_PWR_SRC_TYPE_OTHER:
            ui4_dur = NAV_PWR_VIEW_AV_WARNING_DUR;
            break;
        default:
            ui4_dur = NAV_PWR_VIEW_TV_WARNING_DUR;
            break;
    }

    DBG_INFO(("[Power] ckeck warning timer ui_dur %d\n",ui4_dur));

    return ui4_dur;
}

INT32 nav_pwr_view_update_status(VOID*    pv_view)
{
    _NAV_PWR_VIEW_MEMBER_T*            pt_this = (_NAV_PWR_VIEW_MEMBER_T*)pv_view;

    return _nav_pwr_view_update_status(pt_this);
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_reset_off_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_view_reset_off_timer(
    _NAV_PWR_VIEW_MEMBER_T*               pt_this,
    UINT32                                ui4_timer_type)
{
    INT32                                  i4_ret = NAVR_OK;

    if(_NAV_PWR_VIEW_TIMER_LISTEN != ui4_timer_type  \
        &&_NAV_PWR_VIEW_TIMER_STOP != ui4_timer_type \
        &&_NAV_PWR_VIEW_TIMER_WARNING != ui4_timer_type)
    {
        NAV_LOG_ON_FAIL(NAVR_INV_ARG);
        return ;
    }

    DBG_LOG_PRINT(("[Power][Reset_Off_Timer] source type = %d , ui4_timer_type : %d.\n", pt_this->e_src_type,ui4_timer_type));

    switch(ui4_timer_type)
    {
        case _NAV_PWR_VIEW_TIMER_LISTEN:
        {
            i4_ret = _nav_pwr_view_power_off_listen_timer_stop(pt_this);
            NAV_LOG_ON_FAIL(i4_ret);
            i4_ret = _nav_pwr_view_power_off_listen_timer_start(pt_this);
            NAV_LOG_ON_FAIL(i4_ret);
        }
        break;
        case _NAV_PWR_VIEW_TIMER_STOP:
        {
            i4_ret = _nav_pwr_view_power_off_listen_timer_stop(pt_this);
            NAV_LOG_ON_FAIL(i4_ret);
            i4_ret = _nav_pwr_view_power_off_warning_timer_stop(pt_this);
            NAV_LOG_ON_FAIL(i4_ret);
        }
        break;
        case _NAV_PWR_VIEW_TIMER_WARNING:
        {
            i4_ret = _nav_pwr_view_power_off_warning_timer_stop(pt_this);
            NAV_LOG_ON_FAIL(i4_ret);
            i4_ret = _nav_pwr_view_power_off_warning_timer_start(pt_this);
            NAV_LOG_ON_FAIL(i4_ret);
        }
        break;
        default:
           NAV_LOG_ON_FAIL(NAVR_NOT_EXIST);
           return;
    }
    return;
}
static INT32 _nav_pwr_view_power_off_warning_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    UINT32                ui4_dur = 0;
    INT32                 i4_ret = NAVR_OK;
    POWER_OFF_STATUS      e_timer_type = _nav_pwr_view_get_status(pt_this);


    DBG_LOG_PRINT(("[Power] start power off warning timer \n"));

    if(e_timer_type == POWER_OFF_LISTEN)
    {
        DBG_LOG_PRINT(("[Power] warning : power off listen already start \n"));
        c_dbg_dump_stack();
        return NAVR_NOT_ALLOW;
    }
    else if(e_timer_type == POWER_OFF_WARNING)
    {
       DBG_LOG_PRINT(("[Power] warning : power off warning is start, please stop power off warning\n"));
       c_dbg_dump_stack();
       return NAVR_NOT_ALLOW;
    }
    else if(nav_is_channel_scan_active())
    {
        DBG_LOG_PRINT(("[Power] warning : Scaning Not allowed power off\n"));
        return NAVR_NOT_ALLOW;
    }
    else
    {
        ACFG_RETAIL_MODE_T   t_retail_mode = ACFG_RETAIL_MODE_HOME;
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        {
            DBG_LOG_PRINT(("[Power] warning : Demo mode Not allowed power off\n"));
            return NAVR_NOT_ALLOW;
        }
        UINT8  ui1_val = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;
        a_icl_custom_get_test_pattern_status(&ui1_val);
        if(ICL_RECID_TEST_PATTERN_STATUS_ENABLE == ui1_val)
        {
            DBG_LOG_PRINT(("[Power] warning : Test Pattern Not allowed power off\n"));
            return NAVR_NOT_ALLOW;
        }
    }

    if (!msg_convert_custom_browser_ctrl_active())
    {
        CHAR     s_app_name [APP_NAME_MAX_LEN + 1];
        a_am_get_active_app(s_app_name);
        if (c_strcmp(s_app_name, NAV_NAME)  != 0&& FALSE == msg_convert_custom_airplay_active())
        {
            nav_resume_self();
        }
    }

    ui4_dur = _nav_pwr_view_power_off_warning_timer_during_check(pt_this);

    if(0 != ui4_dur)
    {
        if(_nav_pwr_is_unexpect_active_comp())
        {
            /*start warning timer*/
            _nav_pwr_view_reset_off_timer(pt_this, _NAV_PWR_VIEW_TIMER_LISTEN);
            return NAVR_OK;

        }
        else
        {
            /*show warning message*/
            i4_ret = _nav_pwr_view_show(pt_this);
            NAV_CHK_FAIL(i4_ret);
            if (msg_convert_custom_browser_ctrl_active())
            {
                cmd_convert_send_cmd("\n:am,am,:focus=dtv_app_mtk\n");
            }
        }
    }

    /*set status*/
    i4_ret = _nav_pwr_view_set_status(pt_this,POWER_OFF_WARNING);
    NAV_CHK_FAIL(i4_ret);

    /*reset timer*/
    _nav_pwr_view_reset_off_timer(pt_this, _NAV_PWR_VIEW_TIMER_WARNING);
    return NAVR_OK;
}

static INT32 _nav_pwr_view_power_off_listen_start(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    INT32 i4_ret = NAVR_OK;
    DBG_LOG_PRINT(("[Power] start power off listen timer \n"));

    if(_nav_pwr_view_get_status(pt_this) == POWER_OFF_LISTEN)
    {
        DBG_LOG_PRINT(("[Power] warning : power off listen already start \n"));
        return NAVR_NOT_ALLOW;
    }
    else if(_nav_pwr_view_get_status(pt_this) == POWER_OFF_WARNING)
    {
        DBG_LOG_PRINT(("[Power] warning : power off warning is start, please stop power off warning\n"));
        return NAVR_NOT_ALLOW;
    }

    /*reset timer*/
    _nav_pwr_view_reset_off_timer(pt_this, _NAV_PWR_VIEW_TIMER_LISTEN);

    /*set status*/
    i4_ret = _nav_pwr_view_set_status(pt_this,POWER_OFF_LISTEN);
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}
static INT32 _nav_pwr_view_power_off_warning_stop(_NAV_PWR_VIEW_MEMBER_T * pt_this)
{
    INT32 i4_ret = NAVR_OK;

    if(_nav_pwr_view_get_status(pt_this) != POWER_OFF_WARNING)
    {
        DBG_LOG_PRINT(("[Power] warning :current status is %d ,not allow stop\n",_nav_pwr_view_get_status(pt_this)));
        c_dbg_dump_stack();
        return NAVR_NOT_ALLOW;
    }
    DBG_LOG_PRINT(("[Power] stop power off warning \n"));

    /*hide ui*/
    nav_hide_component(NAV_COMP_ID_POWER);
    if (msg_convert_custom_browser_ctrl_active())
    {
        cmd_convert_send_cmd("\n:am,am,:unfocus=dtv_app_mtk\n");
    }

    /*stop timer*/
    i4_ret = _nav_pwr_view_power_off_warning_timer_stop(pt_this);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set status*/
    i4_ret = _nav_pwr_view_set_status(pt_this,POWER_OFF_OFF);
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}
static INT32 _nav_pwr_view_power_off_listen_stop(_NAV_PWR_VIEW_MEMBER_T * pt_this)
{
    INT32 i4_ret = NAVR_OK;

    if(_nav_pwr_view_get_status(pt_this) != POWER_OFF_LISTEN)
    {
        DBG_LOG_PRINT(("[Power] warning :current status is %d ,not allow stop\n",_nav_pwr_view_get_status(pt_this)));
        c_dbg_dump_stack();
        return NAVR_NOT_ALLOW;
    }
    DBG_LOG_PRINT(("[Power] stop power off listen \n"));

    /*stop timer*/
    i4_ret = _nav_pwr_view_power_off_listen_timer_stop(pt_this);
    NAV_LOG_ON_FAIL(i4_ret);

    /*set status*/
    i4_ret = _nav_pwr_view_set_status(pt_this,POWER_OFF_OFF);
    NAV_CHK_FAIL(i4_ret);


    return NAVR_OK;
}

static INT32 _nav_pwr_view_power_off_stop(_NAV_PWR_VIEW_MEMBER_T*   pt_this)
{
    INT32               i4_ret = NAVR_OK;
    POWER_OFF_STATUS    e_status = _nav_pwr_view_get_status(pt_this);

    if(e_status == POWER_OFF_OFF)
    {
        return NAVR_OK;
    }
    DBG_LOG_PRINT(("[Power] stop power off \n"));

    cmd_convert_send_cmd("\n:dtv_app_mtk,am,:keyIdleNotify=0\n");
    /*hide ui*/
    nav_hide_component(NAV_COMP_ID_POWER);

    /*stop timer*/
    if(e_status == POWER_OFF_WARNING)
    {
        i4_ret = _nav_pwr_view_power_off_warning_stop(pt_this);
        NAV_CHK_FAIL(i4_ret);
    }
    else if(e_status == POWER_OFF_LISTEN)
    {
        i4_ret =  _nav_pwr_view_power_off_listen_stop(pt_this);
        NAV_CHK_FAIL(i4_ret);
    }

    /*set status*/
    i4_ret = _nav_pwr_view_set_status(pt_this,POWER_OFF_OFF);
    NAV_CHK_FAIL(i4_ret);

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_off_cb
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_view_off_cb(
    HANDLE_T                     h_timer,
    VOID*                        pv_this)
{
    /*post a message to itself*/
    nav_request_context_switch(_nav_pwr_view_off_msg_hdlr,
                               pv_this,
                               NULL,
                               NULL);
}

static BOOL nav_power_airplay_has_content()
{
    return msg_convert_custom_airplay_active() && access("/tmp/airplay_sessioning", 0) == 0;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pwr_view_off_msg_hdlr
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_pwr_view_off_msg_hdlr(
    VOID*                              pv_this,
    VOID*                              pv_unused2,
    VOID*                              pv_unused3)
{
    _NAV_PWR_VIEW_MEMBER_T*            pt_this  = (_NAV_PWR_VIEW_MEMBER_T*)pv_this;
    POWER_OFF_STATUS                   e_status = POWER_OFF_UNKNOW;

    NAV_ASSERT(pt_this);

    if(pt_this == NULL)
    {
        return;
    }

    e_status = _nav_pwr_view_get_status(pt_this);
    switch(e_status)
    {
        case POWER_OFF_LISTEN:   /* VGA-LISTEN  -> VGA-WARNING */
            {
                /*stop listen timer*/
                NAV_LOG_ON_FAIL(_nav_pwr_view_power_off_listen_stop(pt_this));

                if(nav_power_airplay_has_content())
                {
                    DBG_LOG_PRINT(("[power] airplay playing should not power down,reset timer\n"));
                    NAV_LOG_ON_FAIL(_nav_pwr_view_power_off_listen_start(pt_this));
                }
                else
                {
                    /*start warning timer*/
                    NAV_LOG_ON_FAIL(_nav_pwr_view_power_off_warning_start(pt_this));
                }
            }
            break;
        case POWER_OFF_WARNING:  /* VGA-WARNING -> power down */
            {
                NAV_LOG_ON_FAIL( _nav_pwr_view_power_off_stop(pt_this));
                /*shutdown system with VGA wakeup capability*/
                NAV_LOG_ON_FAIL( nav_pwr_power_off((NAV_PWR_SRC_TYPE_VGA == pt_this->e_src_type) ? NAV_PWR_WM_VGA : NAV_PWR_WM_EMPTY));
            }
            break;
       default:
                NAV_LOG_ON_FAIL(_nav_pwr_view_power_off_stop(pt_this));
    }
}

#endif /*APP_NAV_PWR_SUPPORT*/


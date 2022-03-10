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
 * $RCSfile: menu_page_net_info.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

#ifdef APP_DYNAMIC_TOS_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_txt.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/msgconvert/msgconvert_custom.h"

#include "nav/via_dlg/nav_via_dlg.h"
#include "menu2/menu.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_clr.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_common/menu_page_animation.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#include "res/app_util/config/a_cfg_custom.h"
#endif
#include "res/app_util/icl/a_icl_custom.h"
#include "app_util/download_util/a_download_util.h"

#include "menu_network.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
//#define  SUPPORT_VIZIO_PRIVACY_POLICY
#define  MENU_DLG_BTN_TEXT_CLR                ((GL_COLOR_T){255, {255}, {255}, {255}})

#define COLOR_COPY(_dst, _src) c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T))

#define  UI4_TXT_INVALUED                     0xffffffff

#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
#define TERMS_TOS_TEXT_X                      (0)
#define TERMS_TOS_TEXT_Y                      (0)
#define TERMS_TOS_TEXT_W                      (MENU_ITEM_V_WIDE)
#define TERMS_TOS_TEXT_H                      (132)

#define TERMS_TOS_LIST_X                      (TERMS_TOS_TEXT_X)
#define TERMS_TOS_LIST_Y                      (TERMS_TOS_TEXT_Y)
#define TERMS_TOS_LIST_W                      (TERMS_TOS_TEXT_W)
#define TERMS_TOS_LIST_H                      (TERMS_TOS_TEXT_H)

#define TERMS_TOS_TEXT_ICON_W                 10*4/3
#define TERMS_TOS_TEXT_ICON_H                 4*4/3

#define TERMS_TOS_TEXT_UP_ICON_X              (TERMS_TOS_TEXT_X+TERMS_TOS_TEXT_W)
#define TERMS_TOS_TEXT_UP_ICON_Y              (TERMS_TOS_TEXT_Y)

#define TERMS_TOS_TEXT_DOWN_ICON_X            (TERMS_TOS_TEXT_X+TERMS_TOS_TEXT_W)
#define TERMS_TOS_TEXT_DOWN_ICON_Y            (TERMS_TOS_TEXT_Y+TERMS_TOS_TEXT_H)

#define TERMS_TOS_CB_X                        (TERMS_TOS_TEXT_X)
#define TERMS_TOS_CB_Y                        (TERMS_TOS_TEXT_Y+TERMS_TOS_TEXT_H)
#define TERMS_TOS_CB_W                        (MENU_ITEM_V_WIDE)
#define TERMS_TOS_CB_H                        (MENU_ITEM_V_HEIGHT)

#define TERMS_PRIV_TEXT_X                      (0)
#define TERMS_PRIV_TEXT_Y                      (TERMS_TOS_CB_Y+TERMS_TOS_CB_H)
#define TERMS_PRIV_TEXT_W                      (MENU_ITEM_V_WIDE)
#define TERMS_PRIV_TEXT_H                      TERMS_TOS_TEXT_H

#define TERMS_PRIV_LIST_X                      (TERMS_PRIV_TEXT_X)
#define TERMS_PRIV_LIST_Y                      (TERMS_PRIV_TEXT_Y)
#define TERMS_PRIV_LIST_W                      (TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_LIST_H                      (TERMS_PRIV_TEXT_H)

#define TERMS_PRIV_TEXT_UP_ICON_X              (TERMS_PRIV_TEXT_X+TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_TEXT_UP_ICON_Y              (TERMS_PRIV_TEXT_Y)

#define TERMS_PRIV_TEXT_DOWN_ICON_X            (TERMS_PRIV_TEXT_X+TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_TEXT_DOWN_ICON_Y            (TERMS_PRIV_TEXT_Y+TERMS_PRIV_TEXT_H)

#define TERMS_PRIV_CB_X                        (0)
#define TERMS_PRIV_CB_Y                        (TERMS_PRIV_TEXT_Y+TERMS_PRIV_TEXT_H)
#define TERMS_PRIV_CB_W                        (TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_CB_H                        (MENU_ITEM_V_HEIGHT)

#define TERMS_ACR_TEXT_X                       (0)
#define TERMS_ACR_TEXT_Y                       (TERMS_PRIV_CB_Y+TERMS_PRIV_CB_H)
#define TERMS_ACR_TEXT_W                       (MENU_ITEM_V_WIDE)
#define TERMS_ACR_TEXT_H                       TERMS_TOS_TEXT_H

#define TERMS_ACR_TEXT_ICON_W                  TERMS_TOS_TEXT_ICON_W
#define TERMS_ACR_TEXT_ICON_H                  TERMS_TOS_TEXT_ICON_H

#define TERMS_ACR_TEXT_UP_ICON_X               (TERMS_ACR_TEXT_X+TERMS_ACR_TEXT_W)
#define TERMS_ACR_TEXT_UP_ICON_Y               (TERMS_ACR_TEXT_Y)

#define TERMS_ACR_TEXT_DOWN_ICON_X             (TERMS_ACR_TEXT_X+TERMS_ACR_TEXT_W)
#define TERMS_ACR_TEXT_DOWN_ICON_Y             (TERMS_ACR_TEXT_Y+TERMS_ACR_TEXT_H)


#define TERMS_BTN_NEXT_X					   (0)
#define TERMS_BTN_NEXT_Y					   (TERMS_ACR_TEXT_Y+TERMS_ACR_TEXT_H+TERMS_ACR_TEXT_ICON_H)
#define TERMS_BTN_NEXT_W                       (MENU_ITEM_V_WIDE)
#define TERMS_BTN_NEXT_H                       (MENU_ITEM_V_HEIGHT)

#else

#define TERMS_TOS_TEXT_X                      (0)
#define TERMS_TOS_TEXT_Y                      (0)
#define TERMS_TOS_TEXT_W                      (MENU_ITEM_V_WIDE)
#define TERMS_TOS_TEXT_H                      (200)

#define TERMS_TOS_LIST_X                      (TERMS_TOS_TEXT_X)
#define TERMS_TOS_LIST_Y                      (TERMS_TOS_TEXT_Y)
#define TERMS_TOS_LIST_W                      (TERMS_TOS_TEXT_W)
#define TERMS_TOS_LIST_H                      (TERMS_TOS_TEXT_H)

#define TERMS_TOS_TEXT_ICON_W                 (10*4/3)
#define TERMS_TOS_TEXT_ICON_H                 (4*4/3)

#define TERMS_TOS_TEXT_UP_ICON_X              (TERMS_TOS_TEXT_X+TERMS_TOS_TEXT_W)
#define TERMS_TOS_TEXT_UP_ICON_Y              (TERMS_TOS_TEXT_Y)

#define TERMS_TOS_TEXT_DOWN_ICON_X            (TERMS_TOS_TEXT_X+TERMS_TOS_TEXT_W)
#define TERMS_TOS_TEXT_DOWN_ICON_Y            (TERMS_TOS_TEXT_Y+TERMS_TOS_TEXT_H)

#define TERMS_TOS_CB_X                        (TERMS_TOS_TEXT_X)
#define TERMS_TOS_CB_Y                        (TERMS_TOS_TEXT_Y+TERMS_TOS_TEXT_H)
#define TERMS_TOS_CB_W                        (MENU_ITEM_V_WIDE)
#define TERMS_TOS_CB_H                        (MENU_ITEM_V_HEIGHT)

#define TERMS_PRIV_TEXT_X                      (0)
#define TERMS_PRIV_TEXT_Y                      (TERMS_TOS_CB_Y+TERMS_TOS_CB_H)
#define TERMS_PRIV_TEXT_W                      (MENU_ITEM_V_WIDE)
#define TERMS_PRIV_TEXT_H                      TERMS_TOS_TEXT_H

#define TERMS_PRIV_LIST_X                      (TERMS_PRIV_TEXT_X)
#define TERMS_PRIV_LIST_Y                      (TERMS_PRIV_TEXT_Y)
#define TERMS_PRIV_LIST_W                      (TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_LIST_H                      (TERMS_PRIV_TEXT_H)

#define TERMS_PRIV_TEXT_UP_ICON_X              (TERMS_PRIV_TEXT_X+TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_TEXT_UP_ICON_Y              (TERMS_PRIV_TEXT_Y)

#define TERMS_PRIV_TEXT_DOWN_ICON_X            (TERMS_PRIV_TEXT_X+TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_TEXT_DOWN_ICON_Y            (TERMS_PRIV_TEXT_Y+TERMS_PRIV_TEXT_H)

#define TERMS_PRIV_CB_X                        (0)
#define TERMS_PRIV_CB_Y                        (TERMS_PRIV_TEXT_Y+TERMS_PRIV_TEXT_H)
#define TERMS_PRIV_CB_W                        (TERMS_PRIV_TEXT_W)
#define TERMS_PRIV_CB_H                        (MENU_ITEM_V_HEIGHT)

#define TERMS_BTN_NEXT_X                       (0)
#define TERMS_BTN_NEXT_Y                       (TERMS_PRIV_CB_Y+TERMS_PRIV_CB_H)
#define TERMS_BTN_NEXT_W                       (MENU_ITEM_V_WIDE)
#define TERMS_BTN_NEXT_H                       (MENU_ITEM_V_HEIGHT)
#endif

#define WLAN_TOS_DOWNLOAD_TIMEOUT               (12)    //120 sec
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*
typedef struct _NW_NFY_DATA
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}_NW_NFY_DATA;
*/
typedef enum _MENU_PROTOCOL_SCAN_E
{
    MENU_PROTOCOL_SCAN_NULL = 0,
    MENU_PROTOCOL_SCAN_TERMS,
    MENU_PROTOCOL_SCAN_POLICY
}MENU_PROTOCOL_SCAN_E;

typedef struct _TERMS_PAGE_TEXT_T
{
    HANDLE_T    h_widget;
    UINT16      ui2_msg_idx;

    HANDLE_T    h_text_widget;
    HANDLE_T    h_text;

    HANDLE_T    h_icon_frm;
    HANDLE_T    h_icon_up;
    HANDLE_T    h_icon_down;

}TERMS_PAGE_TEXT_T;

typedef struct _TERMS_PAGE_DATA_T
{
    HANDLE_T                h_cnt_frm;

    HANDLE_T                h_terms_checkbox;
    TERMS_PAGE_TEXT_T       t_terms_text;

    HANDLE_T                h_policy_checkbox;
    TERMS_PAGE_TEXT_T       t_policy_text;

    TERMS_PAGE_TEXT_T       t_acr_text;

    UINT32                  ui4_pro_total_page;
    UINT32                  ui4_pro_cur_page;
    UINT32                  ui4_pro_total_rows;
    UINT32                  ui4_pro_cur_rows;
    UINT32                  ui4_pre_page_rows;
	BOOL                    b_is_pre_focus_txt; /*focus the text widget*/
	BOOL                    b_not_to_show_from_begin; /*match with b_is_pre_focus_txt,when true ,will show current page ,else show the first page*/

    HANDLE_T                h_btn_next;
    HANDLE_T                h_text_tos_helptip;
    BOOL                    b_terms_cb_selected;
    BOOL                    b_policy_cb_selected;

    MENU_PROTOCOL_SCAN_E    e_scan_text;
    UINT16                  ui2_tos_nfy_id;
    CHAR                    s_file_path[255];
    BOOL                    b_is_file_opened;    /* download file is be opened successfully*/
    UINT8                   ui1_animation_count;
}TERMS_PAGE_DATA_T;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_terms;
TERMS_PAGE_DATA_T    t_terms_page_data;

static BOOL          b_g_is_tos_accept = FALSE;
static BOOL          b_g_is_priv_accept = FALSE;
GL_COLOR_T           t_g_menu_color_network_frame_bk = {0, {0 }, {0 }, {0 } };
GL_COLOR_T           t_g_menu_color_network_txt_nor = { 255, {200}, {200 }, {200 }}; /* Gray color */
GL_COLOR_T           t_g_menu_color_network_txt_hlt = { 255, {255 }, {255 }, {255}}; /* white color */
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static VOID _text_show_nfy_cb(
                            HANDLE_T                    h_handle,
                            const VOID*                 pv_pt_txt,
                            TXT_ASYNC_COND_T            e_event,
                            const VOID*                 pv_data);

static VOID _text_show_first_page(VOID* pv_data,
                                  SIZE_T  z_data_size);

static INT32 _menu_terms_set_nav(VOID);

static INT32 _menu_protocol_timer_start (VOID);

static INT32 _menu_protocol_text_open(VOID);

static INT32  _text_show_open(const CHAR*     ps_filename,
                              HANDLE_T*       ph_widget,
                              HANDLE_T*       ph_text);

static INT32  _text_show_start_scan(HANDLE_T*    ph_text);

static INT32 _menu_terms_text_set_text(HANDLE_T  h_widget,
                                       UINT32    ui4_msg_id);
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static TOS_TYPE_T _menu_tos_get_type (VOID)
{
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;
    TOS_TYPE_T          e_type = TOS_TYPE_LAST_VALID_ITEM;

    if (MENU_PROTOCOL_SCAN_TERMS == pt_page_data->e_scan_text)
    {
        if (ui2_g_menu_curr_lang == MLM_MENU_LANG_FRE)
        {
            e_type = TOS_TYPE_TOS_FRE;
        }
        else if (ui2_g_menu_curr_lang == MLM_MENU_LANG_SPA)
        {
            e_type = TOS_TYPE_TOS_SPA;
        }
        else
        {
            e_type = TOS_TYPE_TOS_ENG;
        }
    }
    else if (MENU_PROTOCOL_SCAN_POLICY == pt_page_data->e_scan_text)
    {
        if (ui2_g_menu_curr_lang == MLM_MENU_LANG_FRE)
        {
            e_type = TOS_TYPE_PRIVACY_FRE;
        }
        else if (ui2_g_menu_curr_lang == MLM_MENU_LANG_SPA)
        {
            e_type = TOS_TYPE_PRIVACY_SPA;
        }
        else
        {
            e_type = TOS_TYPE_PRIVACY_ENG;
        }
    }
    else
    {
        e_type = TOS_TYPE_PRIVACY_ENG;
    }

    return e_type;
}

#define MENU_CUSTOM_TEXT(_txt)    			((UTF16_T*)L##_txt)
/*-----------------------------------------------------------------------------
 * Name: _menu_protocol_error_msg_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_protocol_error_msg_show(VOID)
{
    INT32     		    i4_ret;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;

    if (MENU_PROTOCOL_SCAN_TERMS == pt_page_data->e_scan_text)
    {
        i4_ret = c_wgl_do_cmd (pt_page_data->t_terms_text.h_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (MENU_TEXT(MLM_MENU_KEY_NETWORK_TERMS_DOWNLOAD_FAILED)),
                          WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_NETWORK_TERMS_DOWNLOAD_FAILED))));
        MENU_LOG_ON_FAIL(i4_ret);

        c_wgl_repaint(pt_page_data->t_terms_text.h_widget, NULL, TRUE);
    }
    else if (MENU_PROTOCOL_SCAN_POLICY == pt_page_data->e_scan_text)
    {
        i4_ret = c_wgl_do_cmd (pt_page_data->t_policy_text.h_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (MENU_TEXT(MLM_MENU_KEY_NETWORK_POLICY_DOWNLOAD_FAILED)),
                          WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_NETWORK_POLICY_DOWNLOAD_FAILED))));
        MENU_LOG_ON_FAIL(i4_ret);

        c_wgl_repaint(pt_page_data->t_policy_text.h_widget, NULL, TRUE);
    }
    else
    {
        /* do nothing */
    }

    /* reset scan text status */
    pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_NULL;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_tos_download_stop_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _menu_tos_download_stop_nfy (VOID*   pv_data,
                                         SIZE_T  z_data_size)
{
    INT32               i4_ret = MENUR_OK;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;
    CHAR                s_buf_path[255] = {0};
    TOS_TYPE_T          e_tos_type = TOS_TYPE_LAST_VALID_ITEM;

    /* stop animation */
    menu_page_animation_stop();
    menu_page_animation_hide();
    pt_page_data->ui1_animation_count = 0;

    e_tos_type = _menu_tos_get_type();

    /* try to open file */
    a_tos_get_file_path(e_tos_type, s_buf_path);
    DBG_INFO(("[MENU][TOS] download path. %s %s\n", __FUNCTION__, s_buf_path));

    if (a_tos_is_file_exist(e_tos_type))
    {
        DBG_INFO(("[MENU][TOS] download success. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

        c_strncpy(pt_page_data->s_file_path, s_buf_path, 255);

        i4_ret = _menu_protocol_text_open();
        if (MENUR_OK == i4_ret)
        {
            pt_page_data->b_is_file_opened = TRUE;
        }
    }
    else
    {
        DBG_INFO(("[MENU][TOS] download failed. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));
    }

    if (FALSE == pt_page_data->b_is_file_opened)
    {
        DBG_INFO(("[MENU][TOS] show open failed msg. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

        /* just show error msg */
        _menu_protocol_error_msg_show();
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _menu_tos_download_nfy_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _menu_tos_download_nfy_cb(UINT16    ui2_nfy_id,
                                       VOID*     pv_tag,
                                       ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32               i4_ret;
    ICL_GRPID_TYPE      e_grp_id;
    SIZE_T              z_size ;
    UINT8               ui1_download_status = ICL_TOS_DOWNLOAD_ITEM_STOP;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;

    e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    if (e_grp_id != ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS)
    {
        return MENUR_OK;
    }

    if (pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_NULL)
    {
        return MENUR_OK;
    }

    /* get download status */
    z_size = ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS),
                       &ui1_download_status,
                       &z_size);
    if (ICLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }

    if (ICL_TOS_DOWNLOAD_ITEM_STOP == ui1_download_status)
    {
        menu_async_invoke(_menu_tos_download_stop_nfy, NULL, 0, FALSE);
    }

    DBG_INFO(("[MENU] --- tos download status = %d.\n", ui1_download_status));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_protocol_do_timer_nfy
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
static VOID _menu_protocol_do_timer_nfy(
                    VOID*   pv_data,
                    SIZE_T  z_data_size)
{
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;
    UINT8               ui1_timeout_count = WLAN_TOS_DOWNLOAD_TIMEOUT;

    DBG_INFO(("[MENU][TOS] anim do timer! FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

    if (pt_page_data->b_is_file_opened)
    {
        /* stop animation */
        menu_page_animation_stop();
        menu_page_animation_hide();
        pt_page_data->ui1_animation_count = 0;
    }
    else if(pt_page_data->ui1_animation_count > ui1_timeout_count)
    {
        DBG_INFO(("[MENU][TOS] TIMEOUT show open failed msg. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

        /* stop animation */
        menu_page_animation_stop();
        menu_page_animation_hide();
        pt_page_data->ui1_animation_count = 0;

		/* just show error msg */
        _menu_protocol_error_msg_show();
    }
    else
    {
        menu_page_animation_start(1, FALSE);
        pt_page_data->ui1_animation_count += 1;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _menu_protocol_anim_cb_fct
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
static INT32 _menu_protocol_anim_cb_fct(HANDLE_T                h_widget,
                                        UINT16                  ui2_anim_type,
                                        WGL_ANIM_COND_INF_T     e_anim_cond,
                                        VOID*                   pv_tag)
{
    DBG_INFO(("[MENU][TOS] anim... FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

    if (_ANIM_TOTAL_END(&e_anim_cond))
    {
        menu_async_invoke(_menu_protocol_do_timer_nfy, NULL, 0, TRUE);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_protocol_timer_start
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
static INT32 _menu_protocol_timer_start (VOID)
{
	INT32               i4_ret;
    GL_RECT_T           t_rect;
    HANDLE_T            h_menu_animation = NULL_HANDLE;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;

    DBG_INFO(("[MENU][TOS] START timer!!! FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    if (MENU_PROTOCOL_SCAN_TERMS == pt_page_data->e_scan_text)
    {
    	SET_RECT_BY_SIZE(&t_rect,
                     CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                     CONTENT_Y + (TERMS_TOS_TEXT_H - ICON_ANIMATION_H)/2,
                     ICON_ANIMATION_W,
                     ICON_ANIMATION_H);
    }
    else if (MENU_PROTOCOL_SCAN_POLICY == pt_page_data->e_scan_text)
    {
        SET_RECT_BY_SIZE(&t_rect,
                     CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                     CONTENT_Y + TERMS_PRIV_TEXT_Y + (TERMS_PRIV_TEXT_H - ICON_ANIMATION_H)/2,
                     ICON_ANIMATION_W,
                     ICON_ANIMATION_H);
    }
    else
    {
        return MENUR_FAIL;
    }


    i4_ret =  menu_page_animation_get_handle(&h_menu_animation);
    MENU_LOG_ON_FAIL(i4_ret);

    if (NULL_HANDLE == h_menu_animation)
    {
        return MENUR_FAIL;
    }
    c_wgl_move(h_menu_animation, &t_rect, FALSE);

    menu_page_animation_set_callback_fct(_menu_protocol_anim_cb_fct, NULL);

    /* init the animation count as 0*/
    pt_page_data->ui1_animation_count = 0;
    i4_ret = menu_page_animation_start(1, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_page_animation_show();

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_protocol_text_open
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
static INT32 _menu_protocol_text_open(VOID)
{
    INT32   		    i4_ret;
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;

	if (0 == c_strlen(pt_page_data->s_file_path))
    {
        return MENUR_FAIL;
    }

	if (MENU_PROTOCOL_SCAN_TERMS == pt_page_data->e_scan_text)
	{
	    if (!pt_page_data->b_not_to_show_from_begin)
        {
    		i4_ret = _text_show_open(pt_page_data->s_file_path,
    								 &pt_page_data->t_terms_text.h_text_widget,
    								 &pt_page_data->t_terms_text.h_text);
    		MENU_LOG_ON_FAIL(i4_ret);
        }

        c_wgl_set_visibility(pt_page_data->t_terms_text.h_widget, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_page_data->t_terms_text.h_text_widget, WGL_SW_RECURSIVE);
        c_wgl_set_visibility(pt_page_data->t_terms_text.h_icon_frm, WGL_SW_RECURSIVE);
        if (pt_page_data->b_not_to_show_from_begin)
        {
            c_wgl_enable(pt_page_data->t_terms_text.h_icon_up, TRUE);
        }
        else
        {
            c_wgl_enable(pt_page_data->t_terms_text.h_icon_up, FALSE);
        }

        c_wgl_enable(pt_page_data->t_terms_text.h_icon_down, TRUE);

        i4_ret = _text_show_start_scan(&pt_page_data->t_terms_text.h_text);
        MENU_LOG_ON_FAIL(i4_ret);

        c_wgl_set_focus(pt_page_data->t_terms_text.h_text_widget, WGL_NO_AUTO_REPAINT);
	}
	else if (MENU_PROTOCOL_SCAN_POLICY == pt_page_data->e_scan_text)
	{
	    if (!pt_page_data->b_not_to_show_from_begin)
        {
    		i4_ret = _text_show_open(pt_page_data->s_file_path,
    								 &pt_page_data->t_policy_text.h_text_widget,
    								 &pt_page_data->t_policy_text.h_text);
    		MENU_LOG_ON_FAIL(i4_ret);
        }

        c_wgl_set_visibility(pt_page_data->t_policy_text.h_widget, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_page_data->t_policy_text.h_text_widget, WGL_SW_RECURSIVE);
        c_wgl_set_visibility(pt_page_data->t_policy_text.h_icon_frm, WGL_SW_RECURSIVE);
        if (pt_page_data->b_not_to_show_from_begin)
        {
            c_wgl_enable(pt_page_data->t_policy_text.h_icon_up, TRUE);
        }
        else
        {
            c_wgl_enable(pt_page_data->t_policy_text.h_icon_up, FALSE);
        }
        c_wgl_enable(pt_page_data->t_policy_text.h_icon_down, TRUE);

        i4_ret = _text_show_start_scan(&pt_page_data->t_policy_text.h_text);
        MENU_LOG_ON_FAIL(i4_ret);

        c_wgl_set_focus(pt_page_data->t_policy_text.h_text_widget, WGL_NO_AUTO_REPAINT);
	}
	else
	{
		return MENUR_FAIL;
	}

    pt_page_data->b_is_pre_focus_txt = TRUE;

	i4_ret = c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, TRUE);
	MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _text_show_first_page
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

static VOID _text_show_first_page(VOID* pv_data,
                                  SIZE_T  z_data_size)
{
    TERMS_PAGE_TEXT_T*    ph_text = (TERMS_PAGE_TEXT_T*)pv_data;
    c_txt_get_page_data(ph_text->h_text,
                        (UINT32)1,
                        _text_show_nfy_cb,
                        NULL);
    return;
}

/*----------------------------------------------------------------------------
 * Name: _text_show_nfy_cb
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
static VOID _text_show_nfy_cb(
                            HANDLE_T                    h_handle,
                            const VOID*                 pv_pt_txt,
                            TXT_ASYNC_COND_T            e_event,
                            const VOID*                 pv_data)
{
    UINT16      ui2_rows;
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    switch(e_event)
    {
        case TXT_ASYNC_COND_SCANING:
            DBG_INFO(("\nscanning,b_not_to_show_from_begin=%d\n",
                        pt_page_data->b_not_to_show_from_begin));
            pt_page_data->ui4_pro_total_page = (UINT32)pv_data;

            if (1 == pt_page_data->ui4_pro_total_page)
            {
				if (pt_page_data->b_not_to_show_from_begin)
				{
					break;
				}
                c_txt_get_page_rows(h_handle, &ui2_rows);
                pt_page_data->ui4_pre_page_rows = ui2_rows;
                pt_page_data->ui4_pro_cur_rows = pt_page_data->ui4_pre_page_rows;
                pt_page_data->ui4_pro_total_rows = 100;   /* this value is just for enable down icon when scanning text*/
                if (pt_page_data->t_terms_text.h_text == h_handle)
                {
                    menu_async_invoke(_text_show_first_page,(VOID*)(&pt_page_data->t_terms_text),sizeof(TERMS_PAGE_TEXT_T),TRUE);
                }
                else if (pt_page_data->t_policy_text.h_text == h_handle)
                {
                    menu_async_invoke(_text_show_first_page,(VOID*)(&pt_page_data->t_policy_text),sizeof(TERMS_PAGE_TEXT_T),TRUE);
                }
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
                else
                {
                    menu_async_invoke(_text_show_first_page,(VOID*)(&pt_page_data->t_acr_text),sizeof(TERMS_PAGE_TEXT_T),TRUE);
                }
#endif
            }

             break;
        case TXT_ASYNC_COND_SCAN_FINISH:
            DBG_INFO(("scan finished!\n"));
            pt_page_data->ui4_pro_total_page = (UINT32)pv_data;
            pt_page_data->ui4_pro_total_rows = pt_page_data->ui4_pre_page_rows * (pt_page_data->ui4_pro_total_page - 1);
            c_txt_get_last_page_rows(h_handle,&ui2_rows);
            pt_page_data->ui4_pro_total_rows = pt_page_data->ui4_pro_total_rows + ui2_rows;
            DBG_INFO(("total rows : %d.\n",pt_page_data->ui4_pro_total_rows));
            break;
        case TXT_ASYNC_COND_GET_DATA:
            if (pt_page_data->t_terms_text.h_text == h_handle)
            {
                c_wgl_repaint(pt_page_data->t_terms_text.h_text_widget,NULL,TRUE);
            }
            else if (pt_page_data->t_policy_text.h_text == h_handle)
            {
                c_wgl_repaint(pt_page_data->t_policy_text.h_text_widget,NULL,TRUE);
            }
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
            else
            {
                c_wgl_repaint(pt_page_data->t_acr_text.h_text_widget,NULL,TRUE);
            }
#endif
            DBG_INFO(("get data...\n"));
            break;
        case TXT_ASYNC_COND_GET_DATA_FAIL:
            DBG_INFO(("cget data fail\n"));
            break;
        case TXT_ASYNC_COND_SCAN_ABORT:
            DBG_INFO(("scan abort\n"));
            break;
        default:
            break;
    }
    return;
}
/*----------------------------------------------------------------------------
 * Name: _text_show_start_scan
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
static INT32  _text_show_start_scan(HANDLE_T*    ph_text)
{
    INT32   i4_ret;

    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_scan(*ph_text,UI4_TXT_INVALUED,_text_show_nfy_cb,NULL);
        DBG_INFO(("c_txt_scan return : %d\n", i4_ret));
        MENU_CHK_FAIL(i4_ret);
    }
    else
    {
        DBG_ERROR(("------h_txt is NULL------------\n"));
        return MENUR_FAIL;
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _text_show_close
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
static INT32 _text_show_close(HANDLE_T* ph_text)
{
    INT32   i4_ret;
    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_close(*ph_text);
        MENU_CHK_FAIL(i4_ret);
        *ph_text = NULL_HANDLE;
    }
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _text_proc_fct
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
static INT32 _text_proc_fct(HANDLE_T   h_widget,
                                 UINT32     ui4_msg,
                                 VOID*      param1,
                                 VOID*      param2)
{
    INT32               i4_ret;
    CHAR                s_buf_path[255] = {0};
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;
    TOS_TYPE_T          e_tos_type = TOS_TYPE_LAST_VALID_ITEM;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                if(pt_page_data->e_scan_text == MENU_PROTOCOL_SCAN_NULL)
                {
                    if(h_widget == pt_page_data->t_terms_text.h_widget)
                    {
                        pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_TERMS;
                        pt_page_data->ui4_pro_cur_page = 1;
                        pt_page_data->b_is_file_opened = FALSE;

                        e_tos_type = _menu_tos_get_type();
                        if (a_tos_is_file_exist(e_tos_type))
                        {
                            DBG_INFO(("[WZD][TOS] open file directly. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

                            a_tos_get_file_path(e_tos_type, s_buf_path);
                            c_strncpy(pt_page_data->s_file_path, s_buf_path, 255);
                        }
                        else
                        {
                            DBG_INFO(("[WZD][TOS] start to download. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

                            a_tos_download_util_file(e_tos_type);
                            c_strcpy(pt_page_data->s_file_path, "");
                        }

                        _menu_terms_text_set_text(pt_page_data->t_terms_text.h_widget,
                                                  MLM_MENU_KEY_EMPTY);
                        c_wgl_repaint(pt_page_data->t_terms_text.h_widget, NULL, TRUE);


                        i4_ret = _menu_protocol_text_open();
                        if (MENUR_OK != i4_ret)
                        {
                            _menu_protocol_timer_start();
                        }
                        else
                        {
                            pt_page_data->b_is_file_opened = TRUE;
                        }

                        return MENUR_OK;
                    }
                    else if(h_widget == pt_page_data->t_policy_text.h_widget)
                    {
                        pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_POLICY;
                        pt_page_data->ui4_pro_cur_page = 1;
                        pt_page_data->b_is_file_opened = FALSE;

                        e_tos_type = _menu_tos_get_type();
                        if (a_tos_is_file_exist(e_tos_type))
                        {
                            DBG_INFO(("[WZD][TOS] open file directly. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

                            a_tos_get_file_path(e_tos_type, s_buf_path);
                            c_strncpy(pt_page_data->s_file_path, s_buf_path, 255);
                        }
                        else
                        {
                            DBG_INFO(("[WZD][TOS] start to download. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

                            a_tos_download_util_file(e_tos_type);
                            c_strcpy(pt_page_data->s_file_path, "");
                        }

                        _menu_terms_text_set_text(pt_page_data->t_policy_text.h_widget,
                                                  MLM_MENU_KEY_EMPTY);
                        c_wgl_repaint(pt_page_data->t_policy_text.h_widget, NULL, TRUE);

                        i4_ret = _menu_protocol_text_open();
                        if (MENUR_OK != i4_ret)
                        {
                            _menu_protocol_timer_start();
                        }
                        else
                        {
                            pt_page_data->b_is_file_opened = TRUE;
                        }

                        return MENUR_OK;
                    }
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
                    else if(h_widget == pt_page_data->t_acr_text.h_widget)
                    {
                        pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_POLICY;
                        pt_page_data->ui4_pro_cur_page = 1;

                        c_wgl_set_visibility(pt_page_data->t_acr_text.h_widget,WGL_SW_HIDE);
                        c_wgl_set_visibility(pt_page_data->t_acr_text.h_text_widget,WGL_SW_RECURSIVE);
                        c_wgl_set_visibility(pt_page_data->t_acr_text.h_icon_frm,WGL_SW_RECURSIVE);
                        if (pt_page_data->b_not_to_show_from_begin)
                        {
                            c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,TRUE);
                        }
                        else
                        {
                            c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,FALSE);
                        }

                        c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,TRUE);
                        c_wgl_set_focus(pt_page_data->t_acr_text.h_text_widget,WGL_ASYNC_AUTO_REPAINT);
						pt_page_data->b_is_pre_focus_txt = TRUE;

                        i4_ret = _text_show_start_scan(&pt_page_data->t_acr_text.h_text);
                        if (i4_ret != MENUR_OK)
                        {
                            c_wgl_set_focus(pt_page_data->t_acr_text.h_text_widget,WGL_SYNC_AUTO_REPAINT);
                        }

                        c_wgl_repaint(pt_page_data->t_acr_text.h_icon_frm, NULL, TRUE);
                        return MENUR_OK;
                    }
#endif
                }
            }
                break;
            case BTN_RETURN:
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                return MENUR_OK;
        default:
            break;
        }
    }
    case WGL_MSG_GET_FOCUS:
		if ((h_widget == pt_page_data->t_terms_text.h_widget)
			|| (h_widget == pt_page_data->t_policy_text.h_widget)
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
			|| (h_widget == pt_page_data->t_acr_text.h_widget)
#endif
			)
		{
			if (pt_page_data->b_is_pre_focus_txt == TRUE)
			{
				pt_page_data->b_not_to_show_from_begin = TRUE;
				pt_page_data->b_is_pre_focus_txt = FALSE;
			}
			else
			{
				pt_page_data->b_not_to_show_from_begin = FALSE;
				pt_page_data->b_is_pre_focus_txt = FALSE;
			}
		}

        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NETWORK_TERMS_HELP));

		break;

    case WGL_MSG_LOSE_FOCUS:
        break;

    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_terms_text_create
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
static INT32 _menu_terms_text_create(HANDLE_T     h_parent,
                                     INT32        i4_left,
                                     INT32        i4_top,
                                     INT32        i4_width,
                                     INT32        i4_height,
                                     FE_FNT_STYLE e_font_style,
                                     HANDLE_T     h_normal_bk,
                                     HANDLE_T     h_highlight_bk,
                                     HANDLE_T*    ph_widget)
{

    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      i4_width,
                      i4_height
                       );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _text_proc_fct,
                                 255,
                                 (VOID*)( WGL_STL_TEXT_MAX_2048 |
                                          WGL_STL_TEXT_MULTILINE |
                                          WGL_STL_TEXT_MAX_DIS_10_LINE),
                                 NULL,
                                 ph_widget);
    MENU_CHK_FAIL(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_LEFT_CENTER),
                              NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK((INT32)0),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = e_font_style;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_network_txt_nor);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_network_txt_nor);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _cb_proc_fct
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
static INT32 _cb_proc_fct(HANDLE_T   h_widget,
                            UINT32     ui4_msg,
                            VOID*      param1,
                            VOID*      param2)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NETWORK_TERMS_HELP));
    }
    break;

    case WGL_MSG_LOSE_FOCUS:
        break;

    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                if(h_widget == pt_page_data->h_terms_checkbox)
                {
                    if (b_g_is_tos_accept == FALSE)
                    {
                        b_g_is_tos_accept = TRUE;
                    }
                    else
                    {
                        b_g_is_tos_accept =FALSE;
                    }
                }
                if(h_widget == pt_page_data->h_policy_checkbox)
                {
                    if (b_g_is_priv_accept == FALSE)
                    {
                        b_g_is_priv_accept = TRUE;
                    }
                    else
                    {
                        b_g_is_priv_accept =FALSE;
                    }
                }
            }
                break;
            case BTN_RETURN:
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                return MENUR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


/*-----------------------------------------------------------------------------
 * Name: _menu_terms_checkbox_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_checkbox_create(HANDLE_T  h_parent,
                                         INT32     i4_left,
                                         INT32     i4_top,
                                         HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset_border;
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      (i4_top+9),
                      TERMS_TOS_CB_W,
                      64);

    MENU_CHK_FAIL(c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 _cb_proc_fct,
                                 255,
                                 (void*)(WGL_STL_BTN_CHECKBOX),
                                 NULL,
                                 ph_widget));
    /* Set Insets */
    c_memset(&t_inset_border, 0, sizeof(WGL_INSET_T));
    t_inset_border.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset_border.i4_right    = TERMS_TOS_CB_W - 32*4/3 - FRAME_LEFT_RIGHT_INTV;
    t_inset_border.i4_top      = 10*4/3;
    t_inset_border.i4_bottom   = 0;

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_CHK_FAIL(i4_ret);


    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_TOP,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_common_checkbox_background_v2;
    t_img_info.u_img_data.t_extend.t_disable            = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_common_checkbox_background_v2;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info) );
    MENU_CHK_FAIL(i4_ret);

    /* set foreground image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_common_checkbox_grey_v2;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_common_checkbox_grey_v2;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_common_checkbox_white_v2;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_common_checkbox_white_v2;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_common_checkbox_white_checked_v2;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_common_checkbox_grey_checked_v2;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) );
    MENU_CHK_FAIL(i4_ret);



    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_network_txt_nor;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_network_txt_nor;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_network_txt_nor;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    /* Set Border Title */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      FRAME_LEFT_RIGHT_INTV + 50*4/3,
                      8*4/3,
                      (TERMS_TOS_CB_W-FRAME_LEFT_RIGHT_INTV-50*4/3),
                      28*4/3);

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_text_set_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_text_set_text(HANDLE_T  h_widget,
                                       UINT32    ui4_msg_id)
{
    INT32 i4_ret = 0;

    i4_ret = c_wgl_do_cmd (h_widget,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (MENU_TEXT(ui4_msg_id)),
                      WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(ui4_msg_id))));
    MENU_CHK_FAIL(i4_ret);


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _text_show_cancel_scan
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
static INT32  _text_show_cancel_scan(HANDLE_T*    ph_text)
{
    INT32   i4_ret;
    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_cancel_scan(*ph_text);
        MENU_CHK_FAIL(i4_ret);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _text_show_open
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
static INT32  _text_show_open(const CHAR*     ps_filename,
                              HANDLE_T*       ph_widget,
                              HANDLE_T*       ph_text)
{
    INT32           i4_ret;
    TXT_SET_CMD_T   pt_cmd[1];
    INT16           ui2_idx;

    do
    {
        /*open image*/
        i4_ret = c_txt_open(ps_filename,
                            c_strlen(ps_filename),
                            TXT_RW_FILE_MODE,
                            _text_show_nfy_cb,
                            NULL,
                            ph_text,
                            TXT_FILE_SRC_TYPE);
        if (i4_ret != MENUR_OK)
        {
            DBG_ERROR(("fail to open file return: %d!\n", i4_ret));
            *ph_text = NULL_HANDLE;

            c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_TEXT_SET_TEXT,
                 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_EMPTY)),
                 WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_EMPTY))));
            break;
        }

        /* Set attribute to mw */

        /* Set ecode */
        ui2_idx = 0;
        pt_cmd[ui2_idx].e_set_attr_type   = TXT_SET_ENCODE;
        pt_cmd[ui2_idx].pv_param          = (VOID*)TXT_ECODE_UTF8;
        i4_ret = c_txt_set_attr(*ph_text, 1,pt_cmd);
        if (i4_ret != MENUR_OK)
        {
            DBG_ERROR(("fail to set file encode type!\n"));
            c_txt_close(*ph_text);
            *ph_text = NULL_HANDLE;

            c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_TEXT_SET_TEXT,
                 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_EMPTY)),
                 WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_EMPTY))));
            break;
        }

        /* Set font */
        pt_cmd[ui2_idx].e_set_attr_type   = TXT_SET_WGL_HANDLE;
        pt_cmd[ui2_idx].pv_param          = (VOID*)ph_widget;

        i4_ret = c_txt_set_attr(*ph_text, 1,pt_cmd);
        if (i4_ret != MENUR_OK)
        {
            DBG_ERROR(("fail to set file encode type!\n"));
            c_txt_close(*ph_text);
            *ph_text = NULL_HANDLE;

            c_wgl_do_cmd(*ph_widget,
                 WGL_CMD_TEXT_SET_TEXT,
                 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_EMPTY)),
                 WGL_PACK (c_uc_w2s_strlen (MENU_TEXT(MLM_MENU_KEY_EMPTY))));
            break;
        }
    }while(FALSE);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _text_show_prev_row
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _text_show_prev_row(HANDLE_T     h_text_widget,
                                 HANDLE_T      h_text)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    if (pt_page_data->ui4_pro_cur_rows > pt_page_data->ui4_pre_page_rows)
    {
        pt_page_data->ui4_pro_cur_rows -= 1;
    }
    if (h_text != NULL_HANDLE)
    {
        c_txt_scroll_up_row(h_text,(UINT16)1);
    }
    c_wgl_repaint(h_text_widget,NULL,TRUE);
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _text_show_next_row
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _text_show_next_row(HANDLE_T     h_text_widget,
                                 HANDLE_T      h_text)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    if (pt_page_data->ui4_pro_cur_rows < pt_page_data->ui4_pro_total_rows)
    {
        pt_page_data->ui4_pro_cur_rows += 1;
    }
    if (h_text != NULL_HANDLE)
    {
        c_txt_scroll_down_row(h_text,(UINT16)1);
    }
    c_wgl_repaint(h_text_widget,NULL,TRUE);
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _text_widget_proc_fct
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
static INT32 _text_widget_proc_fct (HANDLE_T   h_widget,
                                    UINT32     ui4_msg,
                                    VOID*      param1,
                                    VOID*      param2)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                if(pt_page_data->e_scan_text != MENU_PROTOCOL_SCAN_NULL)
                {
                    pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_NULL;

                    if(h_widget == pt_page_data->t_terms_text.h_text_widget)
                    {
                        _text_show_cancel_scan(&pt_page_data->t_terms_text.h_text);

                        _menu_terms_text_set_text(pt_page_data->t_terms_text.h_widget,
                                                  pt_page_data->t_terms_text.ui2_msg_idx);

                        c_wgl_set_visibility(pt_page_data->t_terms_text.h_text_widget,WGL_SW_HIDE_RECURSIVE);
                        c_wgl_set_visibility(pt_page_data->t_terms_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);
                        c_wgl_set_visibility(pt_page_data->t_terms_text.h_widget,WGL_SW_NORMAL);
                        c_wgl_set_focus(pt_page_data->t_terms_text.h_widget,TRUE);

                        c_wgl_repaint(pt_page_data->t_terms_text.h_icon_frm, NULL, TRUE);
                    }
                    else if(h_widget == pt_page_data->t_policy_text.h_text_widget)
                    {
                        _text_show_cancel_scan(&pt_page_data->t_policy_text.h_text);

                        _menu_terms_text_set_text(pt_page_data->t_policy_text.h_widget,
                                                  pt_page_data->t_policy_text.ui2_msg_idx);

                        c_wgl_set_visibility(pt_page_data->t_policy_text.h_text_widget,WGL_SW_HIDE_RECURSIVE);
                        c_wgl_set_visibility(pt_page_data->t_policy_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);
                        c_wgl_set_visibility(pt_page_data->t_policy_text.h_widget,WGL_SW_NORMAL);
                        c_wgl_set_focus(pt_page_data->t_policy_text.h_widget,TRUE);

                        c_wgl_repaint(pt_page_data->t_policy_text.h_icon_frm, NULL, TRUE);
                    }
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
                    else if(h_widget == pt_page_data->t_acr_text.h_text_widget)
                    {
                        _text_show_cancel_scan(&pt_page_data->t_acr_text.h_text);

                        c_wgl_set_visibility(pt_page_data->t_acr_text.h_text_widget,WGL_SW_HIDE_RECURSIVE);
                        c_wgl_set_visibility(pt_page_data->t_acr_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);
                        c_wgl_set_visibility(pt_page_data->t_acr_text.h_widget,WGL_SW_NORMAL);
                        c_wgl_set_focus(pt_page_data->t_acr_text.h_widget,TRUE);

                        c_wgl_repaint(pt_page_data->t_acr_text.h_icon_frm, NULL, TRUE);
                    }
#endif
                    _menu_terms_text_set_text(h_widget,MLM_MENU_KEY_EMPTY);
                    c_wgl_repaint(h_widget,NULL,TRUE);
                }
                return MENUR_OK;
            }
            case BTN_CURSOR_UP:
                DBG_INFO(("BTN_CURSOR UP\n"));
                if(pt_page_data->e_scan_text != MENU_PROTOCOL_SCAN_NULL)
                {
                     if(h_widget == pt_page_data->t_terms_text.h_text_widget)
                     {
                         _text_show_prev_row(pt_page_data->t_terms_text.h_text_widget,
                                                     pt_page_data->t_terms_text.h_text);

                         if (pt_page_data->ui4_pro_cur_rows == pt_page_data->ui4_pre_page_rows)
                         {
                             c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,FALSE);
                             c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                         }
                         else if (pt_page_data->ui4_pro_cur_rows == (pt_page_data->ui4_pro_total_rows - 1))
                         {
                             c_wgl_enable(pt_page_data->t_terms_text.h_icon_down,TRUE);
                             c_wgl_repaint(pt_page_data->t_terms_text.h_icon_down,NULL,TRUE);
                         }

                     }
                     else if(h_widget == pt_page_data->t_policy_text.h_text_widget)
                     {
                         _text_show_prev_row(pt_page_data->t_policy_text.h_text_widget,
                                                     pt_page_data->t_policy_text.h_text);

                         if (pt_page_data->ui4_pro_cur_rows == pt_page_data->ui4_pre_page_rows)
                         {
                             c_wgl_enable(pt_page_data->t_policy_text.h_icon_up,FALSE);
                             c_wgl_repaint(pt_page_data->t_policy_text.h_icon_up,NULL,TRUE);
                         }
                         else if (pt_page_data->ui4_pro_cur_rows == (pt_page_data->ui4_pro_total_rows - 1))
                         {
                             c_wgl_enable(pt_page_data->t_policy_text.h_icon_down,TRUE);
                             c_wgl_repaint(pt_page_data->t_policy_text.h_icon_down,NULL,TRUE);
                         }
                     }
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
                     else if(h_widget == pt_page_data->t_acr_text.h_text_widget)
                     {
                         _text_show_prev_row(pt_page_data->t_acr_text.h_text_widget,
                                                     pt_page_data->t_acr_text.h_text);

                         if (pt_page_data->ui4_pro_cur_rows == pt_page_data->ui4_pre_page_rows)
                         {
                             c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,FALSE);
                             c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                         }
                         else if (pt_page_data->ui4_pro_cur_rows == (pt_page_data->ui4_pro_total_rows - 1))
                         {
                             c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,TRUE);
                             c_wgl_repaint(pt_page_data->t_acr_text.h_icon_down,NULL,TRUE);
                         }
                     }
#endif
                }
                DBG_INFO(("row:%d, page: %d\n",
                            pt_page_data->ui4_pro_cur_rows,pt_page_data->ui4_pro_cur_page));
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                DBG_INFO(("BTN_CURSOR DOWN\n"));
                if(pt_page_data->e_scan_text != MENU_PROTOCOL_SCAN_NULL)
                {
                     if(h_widget == pt_page_data->t_terms_text.h_text_widget)
                     {
 #if 0
                          _text_show_next_page(pt_page_data->t_terms_text.h_text_widget,
                                                      pt_page_data->t_terms_text.h_text);
#endif
                          _text_show_next_row(pt_page_data->t_terms_text.h_text_widget,
                                                      pt_page_data->t_terms_text.h_text);

                          if (pt_page_data->ui4_pro_cur_rows == pt_page_data->ui4_pro_total_rows)
                          {
                               c_wgl_enable(pt_page_data->t_terms_text.h_icon_down,FALSE);
                               c_wgl_repaint(pt_page_data->t_terms_text.h_icon_down,NULL,TRUE);
                          }
                          else if (pt_page_data->ui4_pro_cur_rows == (pt_page_data->ui4_pre_page_rows + 1))
                          {
                               c_wgl_enable(pt_page_data->t_terms_text.h_icon_up,TRUE);
                               c_wgl_repaint(pt_page_data->t_terms_text.h_icon_up,NULL,TRUE);
                          }

                     }
                     else if(h_widget == pt_page_data->t_policy_text.h_text_widget)
                     {
#if 0
                          _text_show_next_page(pt_page_data->t_policy_text.h_text_widget,
                                                      pt_page_data->t_policy_text.h_text);
#endif
                          _text_show_next_row(pt_page_data->t_policy_text.h_text_widget,
                                                      pt_page_data->t_policy_text.h_text);

                          if (pt_page_data->ui4_pro_cur_rows == pt_page_data->ui4_pro_total_rows)
                          {
                             c_wgl_enable(pt_page_data->t_policy_text.h_icon_down,FALSE);
                             c_wgl_repaint(pt_page_data->t_policy_text.h_icon_down,NULL,TRUE);
                          }
                          else if (pt_page_data->ui4_pro_cur_rows == (pt_page_data->ui4_pre_page_rows + 1))
                          {
                             c_wgl_enable(pt_page_data->t_policy_text.h_icon_up,TRUE);
                             c_wgl_repaint(pt_page_data->t_policy_text.h_icon_up,NULL,TRUE);
                          }
                     }
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
                     else if(h_widget == pt_page_data->t_acr_text.h_text_widget)
                     {
#if 0
                          _text_show_next_page(pt_page_data->t_acr_text.h_text_widget,
                                                      pt_page_data->t_acr_text.h_text);
#endif
                          _text_show_next_row(pt_page_data->t_acr_text.h_text_widget,
                                                      pt_page_data->t_acr_text.h_text);

                          if (pt_page_data->ui4_pro_cur_rows == pt_page_data->ui4_pro_total_rows)
                          {
                             c_wgl_enable(pt_page_data->t_acr_text.h_icon_down,FALSE);
                             c_wgl_repaint(pt_page_data->t_acr_text.h_icon_down,NULL,TRUE);
                          }
                          else if (pt_page_data->ui4_pro_cur_rows == (pt_page_data->ui4_pre_page_rows + 1))
                          {
                             c_wgl_enable(pt_page_data->t_acr_text.h_icon_up,TRUE);
                             c_wgl_repaint(pt_page_data->t_acr_text.h_icon_up,NULL,TRUE);
                          }
                     }
#endif
                }
                DBG_INFO(("row:%d, page: %d.\n",
                           pt_page_data->ui4_pro_cur_rows,pt_page_data->ui4_pro_cur_page));
                return MENUR_OK;
            case BTN_EXIT:
                return MENUR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_terms_icon_frm_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_icon_frm_create(HANDLE_T              h_parent,
                                UINT16                ui2_left,
                                UINT16                ui2_top,
                                UINT16                ui2_width,
                                UINT16                ui2_height,
                                wgl_widget_proc_fct   pf_wgl_nfy_fct,
                                HANDLE_T*             ph_frame)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (& t_rect,
                      ui2_left,
                      ui2_top,
                      ui2_width,
                      ui2_height);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     pf_wgl_nfy_fct,
                                     255,
                                     (VOID*) WGL_STL_GL_NO_IMG_UI,
                                     0,
                                     ph_frame );
    MENU_CHK_FAIL(i4_ret);

    /* set color */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_color_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_transp;
    t_color_info.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;

    i4_ret = c_wgl_do_cmd(*ph_frame,
                 WGL_CMD_GL_SET_COLOR,
                 WGL_PACK(WGL_CLR_BK),
                 WGL_PACK(&t_color_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_text_widget_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_text_widget_create(HANDLE_T  h_parent,
                                            INT32     i4_left,
                                            INT32     i4_top,
                                            INT32     i4_width,
                                            INT32     i4_height,
                                            FE_FNT_STYLE e_font_style,
                                            HANDLE_T  h_normal_bk,
                                            HANDLE_T  h_highlight_bk,
                                            HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      i4_width,
                      i4_height
                       );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _text_widget_proc_fct,
                                 255,
                                (VOID*)( WGL_STL_TEXT_MULTISTRING |
                                    WGL_STL_TEXT_MAX_DIS_20_LINE   |
                                    WGL_STL_TEXT_IGNORE_NEWLINE),
                                 NULL,
                                 ph_widget);
    MENU_CHK_FAIL(i4_ret);

    /* set alignment */
   i4_ret = c_wgl_do_cmd (*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK (WGL_AS_LEFT_TOP),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 2*4/3;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_network_txt_nor);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_network_txt_nor);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          (INT32)(0),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_text_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_text_icon_create(HANDLE_T  h_parent,
                                          INT32     i4_left,
                                          INT32     i4_top,
                                          INT32     i4_width,
                                          INT32     i4_height,
                                          FE_FNT_STYLE e_font_style,
                                          HANDLE_T  h_normal_bk,
                                          HANDLE_T  h_disable_bk,
                                          HANDLE_T* ph_widget)
{
    INT32   i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                     i4_left,
                     i4_top,
                     i4_width,
                     i4_height);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_widget);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("Failed to create icon!\n"));
    }
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_disable_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                 WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _menu_terms_btn_proc_fct
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
static INT32 _menu_terms_btn_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32  i4_ret = 0;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                pt_page_data->b_terms_cb_selected = b_g_is_tos_accept;
                pt_page_data->b_policy_cb_selected = b_g_is_priv_accept;

                DBG_INFO(("b_g_is_tos_accept=%d\n",b_g_is_tos_accept));
                a_tv_custom_set_tos(b_g_is_tos_accept);

                DBG_INFO(("b_g_is_priv_accept=%d\n",b_g_is_priv_accept));
                a_tv_custom_set_privacy(b_g_is_priv_accept);

                if((pt_page_data->b_terms_cb_selected==TRUE)
                    && (pt_page_data->b_policy_cb_selected==TRUE))
                {
                    menu_nav_go(ui4_g_menu_page_nw, NULL);
                }
                else
                {
                    menu_nav_back();
                }
            }
                break;
            case BTN_RETURN:
                menu_nav_go_home_menu();
                return MENUR_OK;
            case BTN_EXIT:
                menu_nav_back();
                return MENUR_OK;
            case BTN_CURSOR_DOWN:
                i4_ret = menu_help_tip_keytip_set_focus(h_widget,0,FALSE);
                MENU_CHK_FAIL(i4_ret);
                menu_pm_repaint();
        default:
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_btn_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_btn_create(HANDLE_T h_parent,
                                    UINT32   ui4_msg_id,
                                    HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_color_info = {0};
    WGL_IMG_INFO_T      t_img_info = {0};
    WGL_FONT_INFO_T     t_font_info = {0};

    SET_RECT_BY_SIZE(&t_rect,
                     TERMS_BTN_NEXT_X,
                     TERMS_BTN_NEXT_Y,
                     TERMS_BTN_NEXT_W,
                     TERMS_BTN_NEXT_H
                     );

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                _menu_terms_btn_proc_fct,
                                255,
                                NULL,
                                NULL,
                                ph_widget);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left   = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(& t_img_info));
    MENU_CHK_FAIL(i4_ret);

    t_color_info.e_type = WGL_COLOR_SET_EXTEND;
    t_color_info.u_color_data.t_extend.t_enable = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_disable = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_highlight = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_highlight_inactive = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_push = MENU_DLG_BTN_TEXT_CLR;
    t_color_info.u_color_data.t_extend.t_push_unhighlight = MENU_DLG_BTN_TEXT_CLR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(& t_color_info));
    MENU_CHK_FAIL(i4_ret);

    c_strncpy(t_font_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_font_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_font_info),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui4_msg_id)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(ui4_msg_id))));
    MENU_CHK_FAIL(i4_ret);
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _menu_terms_set_nav
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                             Successful.
 *              Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_terms_set_nav(VOID)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32              i4_ret;
    WGL_KEY_LINK_T     at_key_lnk[2];
    HANDLE_T           h_backbar;

    menu_get_backbar_handle(&h_backbar);
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = h_backbar;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_terms_checkbox;
    i4_ret = c_wgl_set_navigation(pt_page_data->t_terms_text.h_widget, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->t_terms_text.h_widget;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->t_policy_text.h_widget;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_terms_checkbox, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->h_terms_checkbox;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_policy_checkbox;
    i4_ret = c_wgl_set_navigation(pt_page_data->t_policy_text.h_widget, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->t_policy_text.h_widget;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->t_acr_text.h_widget;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_policy_checkbox, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    /* VIZIO TOS */
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->h_policy_checkbox;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_next;
    i4_ret = c_wgl_set_navigation(pt_page_data->t_acr_text.h_widget, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->t_acr_text.h_widget;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_next, 1, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);
#else
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->t_policy_text.h_widget;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = pt_page_data->h_btn_next;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_policy_checkbox, 2, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = pt_page_data->h_policy_checkbox;
    i4_ret = c_wgl_set_navigation(pt_page_data->h_btn_next, 1, at_key_lnk);
    MENU_CHK_FAIL(i4_ret);
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(pt_page_data->t_terms_text.h_widget, WGL_SYNC_AUTO_REPAINT);
            break ;
        case BTN_CURSOR_UP:
            MENU_CHK_FAIL (menu_set_focus_on_homebar(TRUE));
            break;
        default:
            break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_RETURN:
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_CURSOR_DOWN :
            MENU_CHK_FAIL(menu_set_focus_on_backbar (TRUE));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _cnt_frm_proc_fct
 *
 * Description: Dispatch all notifications to corresponding widgets.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
#if 0
static INT32 _cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
   /* TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;

            if(h_source == pt_page_data->h_terms_checkbox)
            {
                _cb_notify_fct(h_source, pt_nfy_data);
            }
            if(h_source == pt_page_data->h_policy_checkbox)
            {
                _cb_notify_fct(h_source, pt_nfy_data);
            }
        }
    default:
        break;
    }*/

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
#endif
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32     i4_ret;

    c_memset(pt_page_data, 0, sizeof(TERMS_PAGE_DATA_T));

    t_g_menu_color_network_txt_hlt = t_g_menu_color_white;
    t_g_menu_color_network_txt_nor = t_g_menu_color_white;


    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_TOS_TEXT_X,
                         TERMS_TOS_TEXT_Y,
                         TERMS_TOS_TEXT_W,
                         TERMS_TOS_TEXT_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_box_off,
                         h_g_menu_common_sidebar_highlight_VO_v2,
                         &pt_page_data->t_terms_text.h_widget);
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->t_terms_text.ui2_msg_idx = MLM_MENU_KEY_NETWORK_TERMS_TEXT;

    i4_ret = _menu_terms_text_widget_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_TOS_TEXT_X,
                         TERMS_TOS_TEXT_Y,
                         TERMS_TOS_TEXT_W - TERMS_TOS_TEXT_ICON_W - 4,
                         TERMS_TOS_TEXT_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_box_off,
                         h_g_menu_common_sidebar_highlight_VO_v2,
                         &pt_page_data->t_terms_text.h_text_widget);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_icon_frm_create (pt_page_data->h_cnt_frm,
                                 (TERMS_TOS_TEXT_X + TERMS_TOS_TEXT_W - TERMS_TOS_TEXT_ICON_W - 4),
                                 TERMS_TOS_TEXT_Y,
                                 TERMS_TOS_TEXT_ICON_W,
                                 TERMS_TOS_TEXT_H,
                                 NULL,
                                 &pt_page_data->t_terms_text.h_icon_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_terms_text.h_icon_frm,
                         2,
                         2,
                         TERMS_TOS_TEXT_ICON_W,
                         TERMS_TOS_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_up_on,
                         h_g_menu_terms_arrow_up_off,
                         &pt_page_data->t_terms_text.h_icon_up);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_terms_text.h_icon_frm,
                         2,
                         (TERMS_TOS_TEXT_H-TERMS_TOS_TEXT_ICON_H-2),
                         TERMS_TOS_TEXT_ICON_W,
                         TERMS_TOS_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_down_on,
                         h_g_menu_terms_arrow_down_off,
                         &pt_page_data->t_terms_text.h_icon_down);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_checkbox_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_TOS_CB_X,
                         TERMS_TOS_CB_Y,
                         &pt_page_data->h_terms_checkbox);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_PRIV_TEXT_X,
                         TERMS_PRIV_TEXT_Y,
                         TERMS_PRIV_TEXT_W,
                         TERMS_PRIV_TEXT_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_box_off,
                         h_g_menu_common_sidebar_highlight_VO_v2,
                         &pt_page_data->t_policy_text.h_widget);
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->t_policy_text.ui2_msg_idx = MLM_MENU_KEY_NETWORK_PRIVACY_TEXT;

    i4_ret = _menu_terms_text_widget_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_PRIV_TEXT_X,
                         TERMS_PRIV_TEXT_Y,
                         TERMS_PRIV_TEXT_W - TERMS_TOS_TEXT_ICON_W - 4,
                         TERMS_PRIV_TEXT_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_box_off,
                         h_g_menu_common_sidebar_highlight_VO_v2,
                         &pt_page_data->t_policy_text.h_text_widget);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_icon_frm_create (pt_page_data->h_cnt_frm,
                                 (TERMS_PRIV_TEXT_X + TERMS_PRIV_TEXT_W -TERMS_TOS_TEXT_ICON_W - 4),
                                 TERMS_PRIV_TEXT_Y,
                                 TERMS_TOS_TEXT_ICON_W,
                                 TERMS_PRIV_TEXT_H,
                                 NULL,
                                 &pt_page_data->t_policy_text.h_icon_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_policy_text.h_icon_frm,
                         2,
                         2,
                         TERMS_TOS_TEXT_ICON_W,
                         TERMS_TOS_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_up_on,
                         h_g_menu_terms_arrow_up_off,
                         &pt_page_data->t_policy_text.h_icon_up);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_policy_text.h_icon_frm,
                         2,
                         (TERMS_PRIV_TEXT_H-TERMS_TOS_TEXT_ICON_H-2),
                         TERMS_TOS_TEXT_ICON_W,
                         TERMS_TOS_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_down_on,
                         h_g_menu_terms_arrow_down_off,
                         &pt_page_data->t_policy_text.h_icon_down);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_checkbox_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_PRIV_CB_X,
                         TERMS_PRIV_CB_Y,
                         &pt_page_data->h_policy_checkbox);
    MENU_CHK_FAIL(i4_ret);

#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
    /* VIZIO TOS */
    i4_ret = _menu_terms_text_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_ACR_TEXT_X,
                         TERMS_ACR_TEXT_Y,
                         TERMS_ACR_TEXT_W,
                         TERMS_ACR_TEXT_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_box_off,
                         h_g_menu_common_sidebar_highlight_VO_v2,
                         &pt_page_data->t_acr_text.h_widget);
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->t_acr_text.ui2_msg_idx = MLM_MENU_KEY_NETWORK_ACR_TEXT;

    i4_ret = _menu_terms_text_widget_create(
                         pt_page_data->h_cnt_frm,
                         TERMS_ACR_TEXT_X,
                         TERMS_ACR_TEXT_Y,
                         TERMS_ACR_TEXT_W - TERMS_TOS_TEXT_ICON_W - 4,
                         TERMS_ACR_TEXT_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_box_off,
                         h_g_menu_common_sidebar_highlight_VO_v2,
                         &pt_page_data->t_acr_text.h_text_widget);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_icon_frm_create (pt_page_data->h_cnt_frm,
                                 (TERMS_ACR_TEXT_X + TERMS_ACR_TEXT_W - TERMS_ACR_TEXT_ICON_W - 4),
                                 TERMS_ACR_TEXT_Y,
                                 TERMS_ACR_TEXT_ICON_W,
                                 TERMS_ACR_TEXT_H,
                                 NULL,
                                 &pt_page_data->t_acr_text.h_icon_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_acr_text.h_icon_frm,
                         2,
                         2,
                         TERMS_ACR_TEXT_ICON_W,
                         TERMS_ACR_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_up_on,
                         h_g_menu_terms_arrow_up_off,
                         &pt_page_data->t_acr_text.h_icon_up);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_text_icon_create(
                         pt_page_data->t_acr_text.h_icon_frm,
                         2,
                         (TERMS_ACR_TEXT_H-TERMS_ACR_TEXT_ICON_H-2),
                         TERMS_ACR_TEXT_ICON_W,
                         TERMS_ACR_TEXT_ICON_H,
                         FE_FNT_SIZE_SMALL,
                         h_g_menu_terms_arrow_down_on,
                         h_g_menu_terms_arrow_down_off,
                         &pt_page_data->t_acr_text.h_icon_down);
    MENU_CHK_FAIL(i4_ret);
#endif
    i4_ret = _menu_terms_btn_create(pt_page_data->h_cnt_frm,
                                    MLM_MENU_KEY_NEXT,
                                    &pt_page_data->h_btn_next
                                    );
    MENU_CHK_FAIL(i4_ret);

    /* Create TOS help tips */
    i4_ret = _menu_terms_text_create(
                         pt_page_data->h_cnt_frm,
                         0,
                         TERMS_BTN_NEXT_Y + TERMS_BTN_NEXT_H,
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT,
                         FE_FNT_SIZE_SMALL,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &pt_page_data->h_text_tos_helptip);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_terms_set_nav();
    MENU_CHK_FAIL(i4_ret);

    pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_NULL;
    pt_page_data->b_terms_cb_selected = a_tv_custom_get_tos();
    pt_page_data->b_policy_cb_selected = a_tv_custom_get_privacy();

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    TERMS_PAGE_DATA_T*  pt_page_data = &t_terms_page_data;
    INT32               i4_ret;

    if (pt_page_data->ui2_tos_nfy_id)
    {
        i4_ret = a_icl_notify_unreg(pt_page_data->ui2_tos_nfy_id);
        MENU_CHK_FAIL(i4_ret);

        pt_page_data->ui2_tos_nfy_id = 0;
    }

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32           i4_ret;

    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    /* reg icl notify callback */
    if (pt_page_data->ui2_tos_nfy_id == 0)
    {
        i4_ret = a_icl_notify_reg(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _menu_tos_download_nfy_cb,
                                  &(pt_page_data->ui2_tos_nfy_id));


        if(ICLR_OK != i4_ret)
    	{
    		pt_page_data->ui2_tos_nfy_id = 0;
    		return MENUR_FAIL;
    	}
    }

    menu_main_set_title(MLM_MENU_KEY_TERM_OF_SERVICE);
    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NETWORK_TERMS_HELP));

    _menu_terms_text_set_text(pt_page_data->t_terms_text.h_widget,
                              pt_page_data->t_terms_text.ui2_msg_idx);

    _menu_terms_text_set_text(pt_page_data->t_policy_text.h_widget,
                              pt_page_data->t_policy_text.ui2_msg_idx);

#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
    _menu_terms_text_set_text(pt_page_data->t_acr_text.h_widget,
                              pt_page_data->t_acr_text.ui2_msg_idx);
#endif

    c_wgl_do_cmd(pt_page_data->h_terms_checkbox,
                 WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                 WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NETWORK_TERMS_CB)),
                 WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_NETWORK_TERMS_CB))));

    c_wgl_do_cmd(pt_page_data->h_policy_checkbox,
                 WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                 WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NETWORK_PRIVACY_CB)),
                 WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_NETWORK_PRIVACY_CB))));

    i4_ret = c_wgl_do_cmd(pt_page_data->h_btn_next,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NEXT)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_NEXT))));
    MENU_CHK_FAIL(i4_ret);

    _menu_terms_text_set_text(pt_page_data->h_text_tos_helptip,
                              MLM_MENU_KEY_NETWORK_PRIVACY_HELP);

    c_wgl_set_focus(pt_page_data->t_terms_text.h_widget,FALSE);
    c_wgl_set_visibility(pt_page_data->h_cnt_frm,WGL_SW_RECURSIVE);

    c_wgl_set_visibility(pt_page_data->t_terms_text.h_text_widget,WGL_SW_HIDE);
    c_wgl_set_visibility(pt_page_data->t_policy_text.h_text_widget,WGL_SW_HIDE);
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
    c_wgl_set_visibility(pt_page_data->t_acr_text.h_text_widget,WGL_SW_HIDE);
#endif
    c_wgl_set_visibility(pt_page_data->t_terms_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);
    c_wgl_set_visibility(pt_page_data->t_policy_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);
#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
    c_wgl_set_visibility(pt_page_data->t_acr_text.h_icon_frm,WGL_SW_HIDE_RECURSIVE);
#endif

    pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_NULL;
    menu_help_tip_keytip_show(FALSE);

    /* adjust last shadow position */
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->h_text_tos_helptip,
                    FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    INT32       i4_ret;

    pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_NULL;

	i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm, WGL_SW_HIDE);
	pt_page_data->b_not_to_show_from_begin = FALSE;
	pt_page_data->b_is_pre_focus_txt = FALSE;
    menu_help_tip_keytip_show(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;
    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    c_wgl_set_focus(pt_page_data->t_terms_text.h_widget, WGL_NO_AUTO_REPAINT);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    TERMS_PAGE_DATA_T* pt_page_data = &t_terms_page_data;
    /* set callback function for backbar */
    menu_set_backbar_proc(NULL);
    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /*close file handle*/
    _text_show_close(&pt_page_data->t_terms_text.h_text);
    _text_show_close(&pt_page_data->t_policy_text.h_text);

#ifdef SUPPORT_VIZIO_PRIVACY_POLICY
    _text_show_close(&pt_page_data->t_acr_text.h_text);
#endif

    /* stop animation */
    menu_page_animation_stop();
    menu_page_animation_hide();
    pt_page_data->ui1_animation_count = 0;

    pt_page_data->e_scan_text = MENU_PROTOCOL_SCAN_NULL;

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_page_terms_init(VOID)
{
    t_g_menu_common_page_nw_terms.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_nw_terms.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_nw_terms.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_nw_terms.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_nw_terms.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_nw_terms.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_nw_terms.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#endif  /* APP_DYNAMIC_TOS_SUPPORT */

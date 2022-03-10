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
#ifndef APP_ADD_COUNTRY_CODE_SUPPORT
#include "wizard/wzd.h"

#ifdef APP_2K12_RETAIL_DEMO_MODE
#include "nav/retail_mode/a_nav_retail_mode.h"
#endif

#include "wizard/wzd_dbg.h"

 typedef enum _CON_TV_STATE
 {
    CON_TV_STATE_HIDE = 0,
    CON_TV_STATE_BEGIN,
    CON_TV_STATE_LANG,
    CON_TV_STATE_LAST_VALID_ITEM
 }CON_TV_STATE;

 typedef struct _WZD_CON_TV_MEMBER_T
 {
    HANDLE_T                    h_page_title;
    HANDLE_T                    h_divider_start;
    HANDLE_T                    h_hpr_txt;
    HANDLE_T                    h_divider_end;
    HANDLE_T                    h_content_lb;
    HANDLE_T                    h_lang_lb;
    HANDLE_T                    h_dlg;
    HANDLE_T                    h_last_focused_wdg;
    WZD_FOOTER_BTN_INDEX_T      e_focused_footer;
    UINT16                      ui2_content_lb_index;
    CON_TV_STATE                e_state;
 }WZD_CON_TV_MEMBER_T;

 typedef enum _CONTENT_LB_NUM_T
 {
    _CONTENT_LB_BEGIN = 0,
    _CONTENT_LB_RETAIL,
    _CONTENT_LB_MAX_ITEM
 }CONTENT_LB_NUM_T;

 typedef enum _LANG_LB_NUM_T
 {
    _LANG_LB_ENG = 0,
    _LANG_LB_FRE,
    _LANG_LB_SPA,
    _LANG_LB_MAX_ITEM
 }LANG_LB_NUM_T;
 static WZD_CON_TV_MEMBER_T gt_con_tv;

static INT32 _wzd_page_con_tv_hpr_txt_update (VOID);
static INT32 _wzd_page_con_tv_update_lb(VOID);
static INT32 _wzd_page_con_tv_update_lang_lb(VOID);

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_update_lang_lb
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
static INT32 _wzd_page_con_tv_set_lang( LANG_LB_NUM_T e_lang_index )
{
    ISO_639_LANG_T      s639_lang;

    if( _LANG_LB_ENG == e_lang_index )
    {
        a_cfg_set_gui_lang( s639_app_cfg_lang_eng );
    }
    else if( _LANG_LB_SPA == e_lang_index )
    {
        a_cfg_set_gui_lang( s639_app_cfg_lang_spa );
    }
    else if( _LANG_LB_FRE == e_lang_index )
    {
        a_cfg_set_gui_lang( s639_app_cfg_lang_fre );
    }

    RET_ON_ERR (a_cfg_get_gui_lang (s639_lang));
    RET_ON_ERR (wzd_set_gui_lang (s639_lang));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_update_lang_lb
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
static INT32 _wzd_page_con_tv_update_by_state(BOOL b_repaint)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    BOOL                        b_repaint_main_frame = FALSE;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    if( CON_TV_STATE_HIDE == pt_this->e_state )
    {
        RET_ON_ERR (wzd_view_desc_txt_set_visibility( TRUE ));                  /* Show description text */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_page_title, WGL_SW_HIDE));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_divider_start, WGL_SW_HIDE));  /* Hide divider line */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_hpr_txt, WGL_SW_HIDE));    /* Hide hyper text */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_divider_end, WGL_SW_HIDE));  /* Hide divider line */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_content_lb, WGL_SW_HIDE)); /* Hide content listbox */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_lang_lb, WGL_SW_HIDE));    /* Hide language listbox */
        RET_ON_ERR (wzd_dlg_hide( pt_this->h_dlg ));
    }
    else if( CON_TV_STATE_BEGIN == pt_this->e_state )
    {
        /*RET_ON_ERR (wzd_view_desc_txt_set_text(WZD_TEXT(MLM_WZD_KEY_LOC_DESC_TITLE))); */
        RET_ON_ERR (c_wgl_do_cmd (pt_this->h_page_title,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK (WZD_TEXT(MLM_WZD_KEY_LOC_DESC_TITLE)),
                                  WGL_PACK (c_uc_w2s_strlen (WZD_TEXT(MLM_WZD_KEY_LOC_DESC_TITLE)))));

        RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_TITLE_VIZIO), NULL_HANDLE));
        /* Display footer */
        RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_EMPTY)));
        RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_02, WZD_TEXT(MLM_WZD_KEY_HELP_EXIT)));
        RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
        RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, FALSE));
		RET_ON_ERR (wzd_view_footer_set_btn_num(2));
        RET_ON_ERR (wzd_view_footer_update_btn_navigation());
        RET_ON_ERR (wzd_view_footer_set_visibility(TRUE));

        RET_ON_ERR (wzd_view_demo_pic_show(TRUE));
        RET_ON_ERR (wzd_view_desc_txt_set_visibility( FALSE ));                  /* hide description text */

        /* Display hyper text */
        RET_ON_ERR (_wzd_page_con_tv_hpr_txt_update());
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_page_title, WGL_SW_NORMAL));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_divider_start, WGL_SW_NORMAL));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_hpr_txt, WGL_SW_NORMAL));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_divider_end, WGL_SW_NORMAL));

        /* Display content listbox */
        RET_ON_ERR (_wzd_page_con_tv_update_lb());
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_content_lb, WGL_SW_NORMAL));

        /* Hide language listbox */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_lang_lb, WGL_SW_HIDE));

        b_repaint_main_frame = TRUE;
    }
    else if( CON_TV_STATE_LANG == pt_this->e_state )
    {
        /* Display footer */
        RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_HELP_BACK)));
        RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_02, WZD_TEXT(MLM_WZD_KEY_HELP_EXIT)));
        RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
        RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, FALSE));
		RET_ON_ERR (wzd_view_footer_set_btn_num(2));
        RET_ON_ERR (wzd_view_footer_update_btn_navigation());
        RET_ON_ERR (wzd_view_footer_set_visibility(TRUE));

        RET_ON_ERR (wzd_view_demo_pic_show(FALSE));
        RET_ON_ERR (wzd_view_desc_txt_set_visibility( FALSE ));                 /* Hide description text */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_page_title, WGL_SW_HIDE));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_divider_start, WGL_SW_HIDE));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_hpr_txt, WGL_SW_HIDE));    /* Hide hyper text */
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_divider_end, WGL_SW_HIDE));
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_content_lb, WGL_SW_HIDE)); /* Hide content listbox */
        /* Display language listbox */
        RET_ON_ERR (_wzd_page_con_tv_update_lang_lb());
        RET_ON_ERR (c_wgl_set_visibility (pt_this->h_lang_lb, WGL_SW_NORMAL));

        b_repaint_main_frame = TRUE;
    }

    /* Repaint main frame or layout frame */
    if( b_repaint )
    {
        if( b_repaint_main_frame == TRUE )
        {
            RET_ON_ERR (wzd_view_main_frm_repaint());
        }
        else
        {
            RET_ON_ERR (c_wgl_repaint (h_layout_frm, NULL, TRUE));
        }
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_update_lang_lb
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
static INT32 _wzd_page_con_tv_update_lang_lb(VOID)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    WGL_LB_ITEM_IMG_SUIT_T      t_item_img;
    INT32                       i4_ret = WZDR_OK;
    UINT8                       ui1_i = 0;
    ISO_639_LANG_T              s639_lang;
    UINT16                      ui2_idx = 0;

    /*add all elements first*/
    i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK((UINT16)_LANG_LB_MAX_ITEM),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set item image */
    t_item_img.h_normal                     = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_disable                    = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_highlight                  = h_g_wzd_img_con_tv_lb_icon_ht;
    t_item_img.h_highlight_unfocus          = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected_highlight         = h_g_wzd_img_con_tv_lb_icon_ht;
    t_item_img.h_selected_highlight_unfocus = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected                   = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected_disable           = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_pushed                     = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected_pushed            = h_g_wzd_img_con_tv_lb_icon;

    for( ui1_i=0 ; ui1_i<_LANG_LB_MAX_ITEM ; ui1_i++ )
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                              WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                              WGL_PACK_2(ui1_i, 0),
                              WGL_PACK(&t_item_img));

        if(WGLR_OK != i4_ret)
        {
            RET_ON_ERR(i4_ret);
        }
    }

    /* Set item text */
    i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0, 1),
                          WGL_PACK(MLM_WZD_TEXT(0, wzd_get_validate_key (MLM_WZD_KEY_LANG_1))));
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(1, 1),
                          WGL_PACK(MLM_WZD_TEXT(1, wzd_get_validate_key (MLM_WZD_KEY_LANG_2))));
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(2, 1),
                          WGL_PACK(MLM_WZD_TEXT(2, wzd_get_validate_key (MLM_WZD_KEY_LANG_3))));
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    RET_ON_ERR (a_cfg_get_gui_lang (s639_lang));

    if( 0 == c_strcmp( s639_lang, s639_app_cfg_lang_eng ) )
    {
        ui2_idx = 0;
    }
    else if( 0 == c_strcmp( s639_lang, s639_app_cfg_lang_fre ) )
    {
        ui2_idx = 1;
    }

    else if( 0 == c_strcmp( s639_lang, s639_app_cfg_lang_spa ) )
    {
        ui2_idx = 2;
    }

    i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(ui2_idx),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    RET_ON_ERR (c_wgl_set_visibility (pt_this->h_lang_lb, WGL_SW_NORMAL));

    return WZDR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_lb
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

static INT32 _wzd_page_con_tv_lang_lb_proc(
                 HANDLE_T            h_widget,
                 UINT32              ui4_msg,
                 VOID*               pv_param1,
                 VOID*               pv_param2)
{
    INT32                       i4_ret = WZDR_OK;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    UINT16                      ui2_idx = 0;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
                case BTN_CURSOR_DOWN:
                    i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx),
                                  NULL);
                    if(WGLR_OK != i4_ret)
                    {
                        RET_ON_ERR(i4_ret);
                    }

                    if( (_LANG_LB_MAX_ITEM - 1) == ui2_idx ) /* Current highlighted on last item */
                    {
                    	//RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_03, TRUE));  /* Change focus to cancel footer button */
                    }
                    break;

                case BTN_SELECT:
                    i4_ret = c_wgl_do_cmd(pt_this->h_lang_lb,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx),
                                  NULL);
                    if(WGLR_OK != i4_ret)
                    {
                        RET_ON_ERR(i4_ret);
                    }

                    if( 0 == ui2_idx )
                    {
                        _wzd_page_con_tv_set_lang( _LANG_LB_ENG );
                    }
                    else if( 1 == ui2_idx )
                    {
                        _wzd_page_con_tv_set_lang( _LANG_LB_FRE );
                    }
                    else if( 2 == ui2_idx )
                    {
                        _wzd_page_con_tv_set_lang( _LANG_LB_SPA );
                    }

                    c_wgl_set_focus(
                        pt_this->h_content_lb,
                        FALSE);
                    pt_this->e_state = CON_TV_STATE_BEGIN;
                    _wzd_page_con_tv_update_by_state( TRUE );

                    break;
                default:
                    break;
            }
        }
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

    return WZDR_OK;
}

#ifndef  APP_2K12_RETAIL_DEMO_MODE
/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_dlg
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
VOID _wzd_page_con_tv_data_chg(VOID*    pv_tag,
                                     UINT32   ui4_msg,
                                     VOID*    pv_param1,
                                     VOID*    pv_param2)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    switch( ui4_msg )
    {
        case WZD_DLG_MSG_BTN_FOCUSED:
            DBG_LOG_PRINT(("[WZD][DLG CLI Test] WZD_DLG_MSG_BTN_FOCUSED received, btn index =%d\n", (UINT32)pv_param1));
            break;

        case WZD_DLG_MSG_KEY_INPUT:

            DBG_LOG_PRINT(("[WZD][DLG CLI Test] WZD_DLG_MSG_KEY_INPUT received, keycode =%d, focused btn = %d\n", (UINT32)pv_param1, (UINT32)pv_param2));
            if( WZD_DLG_BTN_TYPE_02 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2 )
            {
                wzd_dlg_hide( pt_this->h_dlg );
                c_wgl_set_focus( pt_this->h_last_focused_wdg, TRUE );
            }
            else if( WZD_DLG_BTN_TYPE_01 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2 )  /* User presses yes to enter Retail mode. */
            {
#ifdef APP_RETAIL_MODE_SUPPORT
                /* the dpms should reset in retail model real enter*/
#if 0
                a_cfg_set_dpms(FALSE);
#endif

                a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
				a_nav_retail_mode_set_resume_from_app(NAV_RETAIL_MODE_RESUME_FROM_WZD);

                /* disable the system keys except the POWER key */
                a_amb_enable_system_key(FALSE);

                //a_tv_net_send_cmd(":dtv_app_mtk,am,:disablekey=dtv_app_mtk\n");

                a_amb_default_key_handler (WGL_MSG_KEY_DOWN,
                                          (VOID*) (BTN_FUNCTION_1),
                                           NULL);
#endif
            }
            break;

        case WZD_DLG_MSG_HIDE_TIMEOUT:
            DBG_LOG_PRINT(("[WZD][DLG CLI Test] WZD_DLG_MSG_HIDE_TIMEOUT received\n"));
            wzd_dlg_hide( pt_this->h_dlg );
            c_wgl_set_focus( pt_this->h_last_focused_wdg, TRUE );
            break;

        case WZD_DLG_MSG_DLG_HIDED:
            DBG_LOG_PRINT(("[WZD][DLG CLI Test] WZD_DLG_MSG_DLG_HIDED received\n"));
            c_wgl_set_focus( pt_this->h_last_focused_wdg, TRUE );
            break;

        default:
            break;
    }
}


/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_dlg
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
static INT32 _wzd_page_con_tv_create_dlg (VOID)
{
    WZD_DLG_INIT_T              t_dlg_init;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN;
    t_dlg_init.pf_fct = _wzd_page_con_tv_data_chg;
    t_dlg_init.pv_tag = NULL;
    t_dlg_init.ui4_hide_timer = 0;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;

    wzd_dlg_create( &t_dlg_init, &pt_this->h_dlg );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_show_dlg
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
static INT32 _wzd_page_con_tv_show_dlg (
                                UINT16 ui2_content,
                                UINT16 ui2_left_btn,
                                UINT16 ui2_right_btn)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    if( NULL_HANDLE == pt_this->h_dlg )
    {
        return WZDR_FAIL;
    }

    c_wgl_get_focus( &pt_this->h_last_focused_wdg );

    wzd_dlg_set_text( pt_this->h_dlg, WZD_TEXT(ui2_content), TRUE );

    wzd_dlg_set_btn_text( pt_this->h_dlg, WZD_DLG_BTN_TYPE_01, WZD_TEXT(ui2_left_btn), TRUE );

    wzd_dlg_set_btn_text( pt_this->h_dlg, WZD_DLG_BTN_TYPE_02, WZD_TEXT(ui2_right_btn), TRUE );

    wzd_dlg_show( pt_this->h_dlg , TRUE );

    return WZDR_OK;
}

#endif

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_create_lb
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
static INT32 _wzd_page_con_tv_update_lb(VOID)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    WGL_LB_ITEM_IMG_SUIT_T      t_item_img;
    INT32                       i4_ret = WZDR_OK;

#ifdef APP_2K12_RETAIL_DEMO_MODE
     /*add all elements first*/
    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK((UINT16)1),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }
#else
    /*add all elements first*/
    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK((UINT16)2),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }
#endif
    /* Set item image */
    t_item_img.h_normal                     = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_disable                    = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_highlight                  = h_g_wzd_img_con_tv_lb_icon_ht;
    t_item_img.h_highlight_unfocus          = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected_highlight         = h_g_wzd_img_con_tv_lb_icon_ht;
    t_item_img.h_selected_highlight_unfocus = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected                   = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected_disable           = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_pushed                     = h_g_wzd_img_con_tv_lb_icon;
    t_item_img.h_selected_pushed            = h_g_wzd_img_con_tv_lb_icon;

    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                          WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                          WGL_PACK_2(0, 0),
                          WGL_PACK(&t_item_img));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

#ifndef APP_2K12_RETAIL_DEMO_MODE
    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                          WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                          WGL_PACK_2(1, 0),
                          WGL_PACK(&t_item_img));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }
#endif
    /* Set item text */
    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0, 1),
                          WGL_PACK(WZD_TEXT(MLM_WZD_KEY_ENERGY_STAR)));
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

#ifndef APP_2K12_RETAIL_DEMO_MODE
    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(1, 1),
                          WGL_PACK(WZD_TEXT(MLM_WZD_KEY_ENERGY_STAR_0)));
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }
#endif
    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK((UINT16)pt_this->ui2_content_lb_index),
                          NULL);
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_create_lb
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
static INT32 _wzd_page_con_tv_create_lb(
                        HANDLE_T                h_parent,
                        GL_RECT_T*              pt_rect,
                        WGL_HIMG_TPL_T          h_bg,
                        wgl_widget_proc_fct     pf_wdgt_proc,
                        HANDLE_T *              ph_widget)
{
    INT32                       i4_ret;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem_info;
    WGL_IMG_INFO_T              t_img_info;
    CHAR*                       s_font_name = wzd_view_get_font_name();

    at_cols[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = CON_TV_LB_COL_TEXT_LENGTH;
    at_cols[0].ui2_width        = CON_TV_LB_COL_IMG_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = CON_TV_LB_COL_TEXT_LENGTH;
    at_cols[1].ui2_width        = CON_TV_LB_W - CON_TV_LB_ELE_INSET_L - CON_TV_LB_ELE_INSET_R - CON_TV_LB_COL_IMG_W;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH | WGL_STL_LB_NO_WRAP_OVER;
    t_lb_init.ui2_max_elem_num  = CON_TV_LB_MAX_ELEM_NUM;
    t_lb_init.ui2_elem_size     = CON_TV_LB_ELE_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    i4_ret = c_wgl_create_widget (h_parent,
                        HT_WGL_WIDGET_LIST_BOX,
                        WGL_CONTENT_LIST_BOX_DEF,
                        WGL_BORDER_TRANSP,
                        pt_rect,
                        pf_wdgt_proc,
                        255,
                        & t_lb_init,
                        NULL,
                        ph_widget);

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set Font */
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);
    t_fnt_info.e_font_size  = DESC_TXT_FNT_SIZE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_FONT,
        WGL_PACK((UINT16)1),
        WGL_PACK(&t_fnt_info));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set Inset */
    t_inset.i4_left   = CON_TV_LB_CNT_INSET_L;
    t_inset.i4_right  = CON_TV_LB_CNT_INSET_R;
    t_inset.i4_top    = CON_TV_LB_CNT_INSET_T;
    t_inset.i4_bottom = CON_TV_LB_CNT_INSET_B;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_CNT_INSET,
        WGL_PACK(&t_inset),
        NULL);

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set Inset */
    t_inset.i4_left   = CON_TV_LB_ELE_INSET_L;
    t_inset.i4_right  = CON_TV_LB_ELE_INSET_R;
    t_inset.i4_top    = CON_TV_LB_ELE_INSET_T;
    t_inset.i4_bottom = CON_TV_LB_ELE_INSET_B;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_ELEM_INSET,
        WGL_PACK(&t_inset),
        NULL);

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_INSET,
        WGL_PACK((UINT16)1),
        WGL_PACK(&t_inset));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    t_inset.i4_left   = CON_TV_LB_LEFT_INSET;
    t_inset.i4_right  = CON_TV_LB_RIGHT_INSET;
    t_inset.i4_top    = CON_TV_LB_TOP_INSET;
    t_inset.i4_bottom = CON_TV_LB_BOTTOM_INSET;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_INSET,
        WGL_PACK((UINT16)0),
        WGL_PACK(&t_inset));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set column color: channel number, text color . */
    t_color_elem.t_normal            = t_g_wzd_color_desc_txt;
    t_color_elem.t_disable           = t_g_wzd_color_desc_txt;
    t_color_elem.t_highlight         = t_g_wzd_color_desc_txt;
    t_color_elem.t_highlight_unfocus = t_g_wzd_color_desc_txt;
    t_color_elem.t_pushed            = t_g_wzd_color_desc_txt;
    t_color_elem.t_selected          = t_g_wzd_color_desc_txt;
    t_color_elem.t_selected_disable  = t_g_wzd_color_desc_txt;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_COLOR,
        WGL_PACK_2 (1, WGL_CLR_TEXT), /* text color */
        WGL_PACK (& t_color_elem));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set column color: channel number, bk color . */
    t_color_elem.t_normal            = t_g_wzd_color_desc_txt_bk;
    t_color_elem.t_disable           = t_g_wzd_color_desc_txt_bk;
    t_color_elem.t_highlight         = t_g_wzd_color_desc_txt_bk;
    t_color_elem.t_highlight_unfocus = t_g_wzd_color_desc_txt_bk;
    t_color_elem.t_pushed            = t_g_wzd_color_desc_txt_bk;
    t_color_elem.t_selected          = t_g_wzd_color_desc_txt_bk;
    t_color_elem.t_selected_disable  = t_g_wzd_color_desc_txt_bk;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_ELEM_COLOR,
        WGL_PACK(WGL_CLR_BK),
        WGL_PACK (& t_color_elem));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_COLOR,
        WGL_PACK_2 (0, WGL_CLR_BK), /* background */
        WGL_PACK (& t_color_elem));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_COLOR,
        WGL_PACK_2 (1, WGL_CLR_BK), /* background */
        WGL_PACK (& t_color_elem));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set viewport background color of listbox. */
    t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_wzd_color_desc_txt_bk;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_wzd_color_desc_txt_bk;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_wzd_color_desc_txt_bk;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_GL_SET_COLOR,
        WGL_PACK (WGL_CLR_LB_VP_BK),
        WGL_PACK (&t_clr_info));

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* set elem background image*/
    t_img_elem_info.h_normal             = NULL_HANDLE;
    t_img_elem_info.h_selected           = NULL_HANDLE;
    t_img_elem_info.h_disable            = NULL_HANDLE;
    t_img_elem_info.h_highlight          = h_g_wzd_img_con_tv_lb_ht;
    t_img_elem_info.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem_info.h_pushed             = NULL_HANDLE;
    t_img_elem_info.h_selected_disable   = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                       WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                       WGL_PACK(&t_img_elem_info),
                       NULL);

    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    /* Set listbox background image */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_bg;
    t_img_info.u_img_data.t_standard.t_highlight = h_bg;
    t_img_info.u_img_data.t_standard.t_disable   = h_bg;

    i4_ret = c_wgl_do_cmd(
                    *ph_widget,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(WGLR_OK != i4_ret)
    {
        RET_ON_ERR(i4_ret);
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_lb
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

static INT32 _wzd_page_con_tv_content_lb_proc(
                 HANDLE_T            h_widget,
                 UINT32              ui4_msg,
                 VOID*               pv_param1,
                 VOID*               pv_param2)
 {
    INT32                       i4_ret = WZDR_OK;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    UINT16                      ui2_idx = 0;
#ifndef  APP_2K12_RETAIL_DEMO_MODE
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
#endif

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
                case BTN_CURSOR_DOWN:
#ifndef  APP_2K12_RETAIL_DEMO_MODE
                    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx),
                                  NULL);
                    if(WGLR_OK != i4_ret)
                    {
                        RET_ON_ERR(i4_ret);
                    }

                    if( (_CONTENT_LB_MAX_ITEM - 1) == ui2_idx ) /* Current highlighted on last item */
                    {

                        //RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_04, TRUE));
                    }
#else
                    //RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_04, TRUE));
#endif

                    break;

                case BTN_SELECT:
                    i4_ret = c_wgl_do_cmd(pt_this->h_content_lb,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK(&ui2_idx),
                                  NULL);
                    if(WGLR_OK != i4_ret)
                    {
                        RET_ON_ERR(i4_ret);
                    }

                    if( _CONTENT_LB_BEGIN == ui2_idx )
                    {
                        wzd_page_goto( WZD_PAGE_NAVI_NEXT_PAGE );
                        a_cfg_set_dpms(TRUE);
                    }
#ifndef  APP_2K12_RETAIL_DEMO_MODE
                    else if( _CONTENT_LB_RETAIL == ui2_idx )
                    {
                        RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));
                        _wzd_page_con_tv_show_dlg( MLM_WZD_KEY_RETAIL_CONFIRM,
                                                    MLM_WZD_KEY_DLG_YES,
                                                    MLM_WZD_KEY_DLG_NO);
                    }
#endif
                    break;
                default:
                    break;
            }
        }
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

    return WZDR_OK;
 }

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_con_tv_create_txt (
                           GL_RECT_T*               pt_rect,
                           HANDLE_T                 h_parent,
                           wgl_widget_proc_fct      pf_wdgt_proc,
                           UINT32                   ui4_style,
                           HANDLE_T*                ph_txt,
                           WGL_FONT_INFO_T*         pt_fnt_info,
                           UINT8                    ui1_align,
                           WGL_COLOR_INFO_T*        pt_color_bk,
                           WGL_COLOR_INFO_T*        pt_color_fg,
                           WGL_INSET_T*             pt_inset)
{
    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     pf_wdgt_proc,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     ph_txt));

    /* set font size */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (pt_fnt_info),
                              NULL));

    /* set content inset */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (pt_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (ui1_align),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (pt_color_bk)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (pt_color_fg)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_txt, WGL_SW_HIDE));

    return  0;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_create_divider_line
*
* Description: This function creates a divider line
*
* Inputs:  -
*
* Outputs: -
*
* Returns: 0                  Successful.
*          Any other values   Failed.
----------------------------------------------------------------------------*/
static INT32 _wzd_page_con_tv_create_divider_line(HANDLE_T*    ph_icon,
                                                         INT32        i4_y)
{
    WGL_IMG_INFO_T      t_img_info;
    GL_RECT_T           t_rect;
    HANDLE_T            h_layout_frm = NULL_HANDLE;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    SET_RECT_BY_SIZE (& t_rect,
                     (INT32)CON_TV_TXT_DIVIDER_X,
                     i4_y,
                     (INT32)CON_TV_TXT_DIVIDER_W,
                     (INT32)CON_TV_TXT_DIVIDER_H);
      /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_layout_frm,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     ph_icon));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = DESC_VIEW_DIVIDER_IMG;
    t_img_info.u_img_data.t_standard.t_disable   = DESC_VIEW_DIVIDER_IMG;
    t_img_info.u_img_data.t_standard.t_highlight = DESC_VIEW_DIVIDER_IMG;

    RET_ON_ERR (c_wgl_do_cmd (*ph_icon,
                               WGL_CMD_GL_SET_IMAGE,
                               WGL_PACK (WGL_IMG_FG), /* background image */
                               WGL_PACK (& t_img_info)));

     /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_icon, WGL_SW_HIDE));

    return  WZDR_OK;
}

 /*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_hpr_txt
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
static INT32 _wzd_page_con_tv_create_hpr_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    WGL_HTS_PARAG_ATTR_T        t_parag;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    CHAR*                       s_font_name = wzd_view_get_font_name();

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, s_font_name);
    t_init.t_font_info_dft.e_font_size  = DESC_TXT_FNT_SIZE;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    SET_RECT_BY_SIZE (& t_rect,
                      (INT32)CON_TV_HPR_TXT_X,
                      (INT32)CON_TV_HPR_TXT_Y,
                      (INT32)CON_TV_HPR_TXT_W,
                      (INT32)CON_TV_HPR_TXT_H);

    /* create hyper text widget */
    RET_ON_ERR (c_wgl_create_widget (h_layout_frm,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     &pt_this->h_hpr_txt));

    /* set content inset */
    t_inset.i4_left   = CON_TV_HPR_TXT_L;
    t_inset.i4_right  = CON_TV_HPR_TXT_R;
    t_inset.i4_top    = CON_TV_HPR_TXT_T;
    t_inset.i4_bottom = CON_TV_HPR_TXT_B;

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                              WGL_CMD_HTS_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set justification */
    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_LEFT),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_HTS_VP_BK), /* viewport color */
                              WGL_PACK (& t_color_info)));


    c_memset (& t_parag, 0, sizeof(WGL_HTS_PARAG_ATTR_T));
    t_parag.e_justif = WGL_HTS_JUSTIF_LEFT;
    t_parag.ui2_indent = 0;
    t_parag.i4_line_gap_bottom = 2;
    t_parag.i4_line_gap_top = 0;
    t_parag.ui2_parag_gap_bottom = 0;
    t_parag.ui2_parag_gap_top = 0;
    RET_ON_ERR (c_wgl_do_cmd(pt_this->h_hpr_txt,
                                 WGL_CMD_HTS_CUR_PARAG_SET,
                                 WGL_PACK(&t_parag),
                                 NULL));
    return  0;
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_create_hpr_txt
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

static INT32 _wzd_page_con_tv_hpr_txt_update (VOID)
{
    UINT16                      ui2_sec_id, ui2_sec_img_id;
    WGL_HTS_TEXT_INFO_T         t_hts_info;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    CHAR*                       s_font_name = wzd_view_get_font_name();
    WGL_HTS_IMG_INFO_T          t_hts_img_info;
    UTF16_T* w2s_str01 = WZD_TEXT(MLM_WZD_KEY_LOC_DESC_TEXT_01);
    UTF16_T* w2s_str02 = WZD_TEXT(MLM_WZD_KEY_LOC_DESC_TEXT_02);
    UTF16_T* w2s_str03 = WZD_TEXT(MLM_WZD_KEY_LOC_DESC_TEXT_03);

    /* Clear hyper text. */
    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL));

    /* Reset hyper text infomation. */
    c_memset (& t_hts_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));

    /* Set font data. */
    c_strcpy (t_hts_info.t_font.a_c_font_name, s_font_name);
    t_hts_info.t_font.e_font_size  = DESC_TXT_FNT_SIZE;
    t_hts_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;

    /* Set text background color. */
    COLOR_COPY (& t_hts_info.t_clr_text_bk, & t_g_wzd_color_desc_txt_bk);

    /* Append text. */
    {
        COLOR_COPY (& t_hts_info.t_clr_text, & t_g_wzd_color_desc_txt);

        t_hts_info.t_string.ui2_size_buf = (UINT16)(c_uc_w2s_strlen (w2s_str01) * sizeof(UTF16_T));
        t_hts_info.t_string.w2s_str      = w2s_str01;
        t_hts_info.t_string.ui2_len_str  = (UINT16)c_uc_w2s_strlen (w2s_str01);

        RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                                  WGL_CMD_HTS_APPEND_TEXT_SEC,
                                  WGL_PACK (& t_hts_info),
                                  WGL_PACK (& ui2_sec_id)));
    }

    /* Reset hyper text image infomation. */
    c_memset (& t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));

    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
    t_hts_img_info.h_img = h_g_wzd_img_con_tv_up;
    t_hts_img_info.ui2_gap_bottom = 0;
    t_hts_img_info.ui2_gap_top = 0;
    t_hts_img_info.ui2_gap_right = 0;
    t_hts_img_info.ui2_gap_left = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                              WGL_CMD_HTS_APPEND_IMG_SEC,
                              WGL_PACK (& t_hts_img_info),
                              WGL_PACK (& ui2_sec_img_id)));

    /* Append text. */
    {
        COLOR_COPY (& t_hts_info.t_clr_text, & t_g_wzd_color_desc_txt);

        t_hts_info.t_string.ui2_size_buf = (UINT16)(c_uc_w2s_strlen (w2s_str02) * sizeof(UTF16_T));
        t_hts_info.t_string.w2s_str      = w2s_str02;
        t_hts_info.t_string.ui2_len_str  = (UINT16)c_uc_w2s_strlen (w2s_str02);

        RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                                  WGL_CMD_HTS_APPEND_TEXT_SEC,
                                  WGL_PACK (& t_hts_info),
                                  WGL_PACK (& ui2_sec_id)));
    }

    /* Reset hyper text image infomation. */
    c_memset (& t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));

    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
    t_hts_img_info.h_img = h_g_wzd_img_con_tv_down;
    t_hts_img_info.ui2_gap_bottom = 0;
    t_hts_img_info.ui2_gap_top = 0;
    t_hts_img_info.ui2_gap_right = 0;
    t_hts_img_info.ui2_gap_left = 0;

    RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                              WGL_CMD_HTS_APPEND_IMG_SEC,
                              WGL_PACK (& t_hts_img_info),
                              WGL_PACK (& ui2_sec_img_id)));

    /* Append text. */
    {
        COLOR_COPY (& t_hts_info.t_clr_text, & t_g_wzd_color_desc_txt);

        t_hts_info.t_string.ui2_size_buf = (UINT16)(c_uc_w2s_strlen (w2s_str03) * sizeof(UTF16_T));
        t_hts_info.t_string.w2s_str      = w2s_str03;
        t_hts_info.t_string.ui2_len_str  = (UINT16)c_uc_w2s_strlen (w2s_str03);

        RET_ON_ERR (c_wgl_do_cmd (pt_this->h_hpr_txt,
                                  WGL_CMD_HTS_APPEND_TEXT_SEC,
                                  WGL_PACK (& t_hts_info),
                                  WGL_PACK (& ui2_sec_id)));
    }

    return 0;
}
#if 0
/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_hpr_txt
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
static INT32 _wzd_page_con_tv_hpr_txt_show(BOOL b_show)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    if(b_show)
    {
        RET_ON_ERR (c_wgl_show( pt_this->h_hpr_txt, WGL_SW_NORMAL ));
    }
    else
    {
        RET_ON_ERR (c_wgl_show( pt_this->h_hpr_txt, WGL_SW_HIDE ));
    }

    return WZDR_OK;
}
#endif
 /*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_create
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
static INT32 _wzd_page_con_tv_create (VOID)
{
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    GL_RECT_T                   t_rect;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT32                      ui4_style = 0;
    UINT8                       ui1_align = 0;
    WGL_COLOR_INFO_T            t_color_info_bg, t_color_info_fg;
    WGL_INSET_T                 t_inset;

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

    c_memset( &gt_con_tv, 0, sizeof(WZD_CON_TV_MEMBER_T) );

    /* Create text show getting start */
    SET_RECT_BY_SIZE (& t_rect,
                      CON_TV_HPR_TXT_X,
                      0,
                      CON_TV_HPR_TXT_W,
                      40 * WZD_UI_RATIO_W);

    ui4_style = WGL_STL_TEXT_MULTILINE |
                 WGL_STL_TEXT_MAX_128  |
                 WGL_STL_TEXT_MAX_DIS_5_LINE |
                 WZD_WIDGET_STYLE;

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, WZD_FONT_NAME);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_LEFT_BOTTOM;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt);

    t_inset.i4_left   = CON_TV_HPR_TXT_L;
    t_inset.i4_right  = CON_TV_HPR_TXT_R;
    t_inset.i4_top    = CON_TV_HPR_TXT_T;
    t_inset.i4_bottom = CON_TV_HPR_TXT_B;

    RET_ON_ERR (_wzd_page_con_tv_create_txt(
                                &t_rect,
                                h_layout_frm,
                                NULL,
                                ui4_style,
                                &pt_this->h_page_title,
                                &t_fnt_info,
                                ui1_align,
                                &t_color_info_bg,
                                &t_color_info_fg,
                                &t_inset));

    RET_ON_ERR (_wzd_page_con_tv_create_divider_line(&pt_this->h_divider_start, CON_TV_HPR_TXT_Y - 5 * WZD_UI_RATIO_W));
    RET_ON_ERR (_wzd_page_con_tv_create_hpr_txt());
    RET_ON_ERR (_wzd_page_con_tv_create_divider_line(&pt_this->h_divider_end, CON_TV_HPR_TXT_Y + CON_TV_HPR_TXT_H));

    /* Create content list. */
    SET_RECT_BY_SIZE (&t_rect,
                      CON_TV_LB_X,
                      CON_TV_LB_Y,
                      CON_TV_LB_W,
                      CON_TV_LB_H);

    RET_ON_ERR (_wzd_page_con_tv_create_lb(
                                h_layout_frm,
                                &t_rect,
                                h_g_wzd_img_con_tv_lb_bg,
                                _wzd_page_con_tv_content_lb_proc,
                                &pt_this->h_content_lb));
#ifndef  APP_2K12_RETAIL_DEMO_MODE
    RET_ON_ERR (_wzd_page_con_tv_create_dlg());  /* Create dialog. */
#endif
    /* Create Language list. */
    SET_RECT_BY_SIZE (&t_rect,
                      CON_TV_LANG_LB_X,
                      CON_TV_LANG_LB_Y,
                      CON_TV_LANG_LB_W,
                      CON_TV_LANG_LB_H);

    RET_ON_ERR (_wzd_page_con_tv_create_lb(
                                h_layout_frm,
                                &t_rect,
                                h_g_wzd_img_con_tv_lang_lb_bg,
                                _wzd_page_con_tv_lang_lb_proc,
                                &pt_this->h_lang_lb));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_dsty
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
static INT32 _wzd_page_con_tv_dsty(VOID)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    if (pt_this->h_hpr_txt)
    {
        c_wgl_destroy_widget_ex(pt_this->h_hpr_txt, FALSE);
    }
    if (pt_this->h_content_lb)
    {
        c_wgl_destroy_widget_ex(pt_this->h_content_lb, FALSE);
    }
    if (pt_this->h_dlg)
    {
        wzd_dlg_destroy(pt_this->h_dlg );
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_on_show
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
static INT32 _wzd_page_con_tv_on_show (
    UINT32                      ui4_page_id
    )
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    DBG_LOG_PRINT(("[WZD] _wzd_page_con_tv_on_show() called. \n"));

    /* Display demo picture in the right side */
    RET_ON_ERR (wzd_view_demo_pic_set_image(h_g_custom_img_getting_started_rc, FALSE));

    RET_ON_ERR (c_wgl_set_focus(
                pt_this->h_content_lb,
                FALSE));

    pt_this->e_state = CON_TV_STATE_BEGIN;

    RET_ON_ERR (_wzd_page_con_tv_update_by_state( FALSE ));

    wzd_view_scan_bar_set_visibility(FALSE);

    /*wzd_view_main_frm_show( TRUE ); */

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_on_hide
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
static INT32 _wzd_page_con_tv_on_hide(UINT32 ui4_page_id)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    pt_this->e_state = CON_TV_STATE_HIDE;

    /*RET_ON_ERR (_wzd_page_con_tv_update_by_state( TRUE ));*/

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_on_footer_nfy
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
static VOID _wzd_page_con_tv_on_footer_nfy(
                                         UINT32   ui4_msg,
                                         VOID*    pv_param1,
                                         VOID*    pv_param2)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    switch( ui4_msg )
    {
        case WZD_FOOTER_MSG_ITEM_FOCUSED:
            DBG_LOG_PRINT(("[WZD][CON TV] %d footer button is focused.\n", (UINT32)pv_param1));
            pt_this->e_focused_footer = (WZD_FOOTER_BTN_INDEX_T)(UINT32)pv_param1;
            break;

        case WZD_FOOTER_MSG_KEY_INPUT:
            DBG_LOG_PRINT(("[WZD][CON TV] Receive key input, keycode = %d\n", (UINT32)pv_param1));

            switch((UINT32)pv_param1)
            {
                case BTN_CURSOR_UP:
                    if( CON_TV_STATE_BEGIN == pt_this->e_state )
                    {
                        /* Change focus back to content list. */
                        c_wgl_set_focus(
                                pt_this->h_content_lb,
                                TRUE);
                    }
                    else if( CON_TV_STATE_LANG == pt_this->e_state )
                    {
                        /* Change focus back to language list. */
                        c_wgl_set_focus(
                                pt_this->h_lang_lb,
                                TRUE);
                    }
                    break;
                case BTN_SELECT:
                    if( CON_TV_STATE_BEGIN == pt_this->e_state )
                    {
                        if(0)//( WZD_FOOTER_BTN_04 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )  /* Language button pressed */
                        {
                            c_wgl_set_focus(
                                pt_this->h_lang_lb,
                                FALSE);
                            pt_this->e_state = CON_TV_STATE_LANG;
                            _wzd_page_con_tv_update_by_state( TRUE );
                        }
                    }
                    else if( CON_TV_STATE_LANG == pt_this->e_state )
                    {
                        if(0)//if( WZD_FOOTER_BTN_03 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )  /* Cancel button pressed */
                        {
                            c_wgl_set_focus(
                                pt_this->h_content_lb,
                                FALSE);
                            pt_this->e_state = CON_TV_STATE_BEGIN;
                            _wzd_page_con_tv_update_by_state( TRUE );
                        }
                    }
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }
}


/*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_on_hide
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
INT32 wzd_page_con_tv_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data)
{
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TITLE_VIZIO;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_LOC_DESC_TITLE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = _wzd_page_con_tv_on_footer_nfy;
	pt_info_data->pf_return_nfy_fct        = NULL;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create = _wzd_page_con_tv_create;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory = _wzd_page_con_tv_dsty;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show = _wzd_page_con_tv_on_show;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide = _wzd_page_con_tv_on_hide;


    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_con_tv_nfy_sel
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
INT32 wzd_page_con_tv_nfy_sel(UINT16               ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}
#endif /*APP_ADD_COUNTRY_CODE_SUPPORT*/

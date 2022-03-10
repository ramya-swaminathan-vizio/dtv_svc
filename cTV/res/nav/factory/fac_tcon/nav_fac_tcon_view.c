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
 * $RCSfile: nav_fac_tcon_view.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/06 $
 * $Author: heyi.wang $
 * $CCRevision$
 * $SWAuthor$
 * $MD5HEX$
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_svctx.h"

#include "app_util/a_isl.h"
#include "app_util/lang/a_lang.h"
#include "nav/nav_common.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"

#include "res/nav/factory/fac_mlm.h"
#include "res/nav/factory/nav_fac_img.h"
#include "res/nav/factory/fac_menu/nav_fac_view_rc.h"
#include "nav_fac_tcon.h"
#include "nav_fac_tcon_view.h"

#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"

#include "BUF08630.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

//#define USE_TCON_MENU_BK_IMG //Denny 2009/11/30 add

#define IS_SYNC_REPAINT                         (TRUE)

static HANDLE_T     h_g_nav_tcon_svctx = NULL_HANDLE;

typedef struct _NAV_FAC_TCON_VIEW_T
{
    NAV_FAC_TCON_T*             pt_ctrl;

    BOOL                        b_widget_created;

    INT32                       i4_frame_x_offset;
    INT32                       i4_frame_y_offset;
    APP_COLOR_TYPE_T            e_color_type;

    UINT16                      ui2_fac_tcon_menu_elem_idx;

    HANDLE_T                    h_fac_tcon_main_frame;
    HANDLE_T                    h_fac_tcon_list_box;

    HANDLE_T                    h_fac_tcon_canvas;

#ifdef USE_TCON_MENU_BK_IMG //Denny 2009/11/30 add
    WGL_HIMG_TPL_T              h_fac_tcon_menu_img_bk;
    WGL_HIMG_TPL_T              h_fac_tcon_hlt_img_bk;
#endif

} NAV_FAC_TCON_VIEW_T;

typedef enum
{
    VCOM_STORE_STATUS_WAIT_KEY = 0,
    VCOM_STORE_STATUS_DONE,
    VCOM_STORE_STATUS_FAIL,
    VCOM_STORE_STATUS_MAX,
}   VCOM_STORE_STATUS_GRP_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_FAC_TCON_VIEW_T   t_g_nav_fac_tcon_view     = {0};

static UINT16 aui2_item_fac_tcon_menu[NAV_FAC_TCON_MENU_MAX_ELEM] = {
                                    MLM_FAC_KEY_MSG_VCOM_VALUE,
                                    MLM_FAC_KEY_MSG_VCOM_STORE,
                                    MLM_FAC_KEY_MSG_GAMMA1,
                                    MLM_FAC_KEY_MSG_GAMMA2,
                                    MLM_FAC_KEY_MSG_GAMMA3,
                                    MLM_FAC_KEY_MSG_GAMMA4,
                                    MLM_FAC_KEY_MSG_GAMMA5,
                                    MLM_FAC_KEY_MSG_GAMMA6,
                                    MLM_FAC_KEY_MSG_GAMMA7,
                                    MLM_FAC_KEY_MSG_GAMMA8,
                                    MLM_FAC_KEY_MSG_TCON_EXIT,
                                    };
static UINT8 ui1_nav_fac_vcom_store_done = VCOM_STORE_STATUS_WAIT_KEY; //Denny 2009/11/30 add
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_update
 * Description: FAC TCon view model update.
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_OK:            The function success.
 *          NAVR_FAIL           The function fail.
 ----------------------------------------------------------------------------*/
INT32 _nav_fac_tcon_view_update(
                    NAV_FAC_TCON_VIEW_T*           pt_view
                    )
{
    INT32               i4_ret;
    UINT16              ui2_hlt_elem_idx;
    HANDLE_T            h_focus_box;


    ui2_hlt_elem_idx = 0;
    h_focus_box = pt_view->h_fac_tcon_list_box;

    i4_ret = c_wgl_do_cmd(
                    h_focus_box,
                    WGL_CMD_LB_HLT_ELEM,
                    WGL_PACK(ui2_hlt_elem_idx),
                    NULL
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    h_focus_box,
                    WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE,
                    NULL,
                    NULL
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_show
 * Description: Callback function for FAC TCon view model show
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_OK:            The function success.
 *          NAVR_FAIL           The function fail.
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_show(
                    NAV_FAC_TCON_VIEW_T*           pt_view,
                    BOOL                b_repaint_all
                    )
{
    INT32       i4_ret;

    i4_ret = c_wgl_set_focus(pt_view->h_fac_tcon_list_box, FALSE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_fac_tcon_main_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if (b_repaint_all) {
        i4_ret = c_wgl_repaint(pt_view->h_fac_tcon_canvas, NULL, IS_SYNC_REPAINT);
        }
    else {
        i4_ret = c_wgl_repaint(pt_view->h_fac_tcon_main_frame, NULL, IS_SYNC_REPAINT);
    }
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_hide
 * Description:  Callback function of FAC TCon view model hide
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_hide(VOID)
{
    NAV_FAC_TCON_VIEW_T*    pt_view = &t_g_nav_fac_tcon_view;
    INT32                   i4_ret;

    ui1_nav_fac_vcom_store_done = VCOM_STORE_STATUS_WAIT_KEY;

    /* Hide all frames under FAC TCon menu*/
    i4_ret = c_wgl_set_visibility(pt_view->h_fac_tcon_main_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_repaint(pt_view->h_fac_tcon_canvas, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_is_key_handler
 * Description:  Callback function of FAC TCon keu handle
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static BOOL _nav_fac_tcon_view_is_key_handler(UINT32 ui4_key_code)
{
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_rcu_key_handler
 * Description: handle the rcu key message
 * Inputs:  ui4_key_code    rcu key value
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/
static VOID _nav_fac_tcon_view_rcu_key_handler(UINT32 ui4_key_code)
{

    switch(ui4_key_code) {
		case BTN_FAC_FAC: //jeff 20090106 add
            ui4_key_code = BTN_EXIT;
        case BTN_EXIT:
            {
                UINT32 ui4_fac_val;

                if(fac_test_ptn_get_status())
                {
                    INT32   i4_ret = APP_CFGR_INTERNAL_ERR;

                    i4_ret = fac_test_ptn_page_hide();
                    if( i4_ret != APP_CFGR_OK )
                    {
                        DBG_LOG_PRINT(("fac_test_ptn_page_hide() failed. i4_ret = %d at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
                    }
                    fac_test_ptn_set_status(FALSE);
                    fac_vcom_init_set_status(FALSE);
                }

                _nav_fac_tcon_view_hide(); //Denny 2009/11/30 add

                a_cfg_cust_fac_get(&ui4_fac_val);
                if(ui4_fac_val & APP_CFG_CUST_FAC_RC_ON)
                {
                    nav_grab_activation(NAV_COMP_ID_FAC_URC_DIALOG);
                }
                else
                {
                    nav_rcu_key_handler(ui4_key_code);
                }

            }
            break;

        default:
            break;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_menu_list_update_item
 * Description: Disable item by the setting value of their parent node and update
 *              item for setuplist box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_menu_list_update_item(
                    HANDLE_T                h_listbox,
                    UINT16                  ui2_idx,
                    BOOL                    b_repaint
                     )
{
    INT32               i4_ret;

    switch (ui2_idx)
    {
        default:
            if (b_repaint)
            {
                i4_ret = c_wgl_do_cmd (
                        h_listbox,
                        WGL_CMD_LB_REPAINT_ITEM,
                        WGL_PACK_2(ui2_idx, 2),
                        NULL
                    );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
            break;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_menu_list_set_content_item
 * Description: Get the item content from EEPROM and set it to setup list box for each item
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_menu_list_set_content_item(
                    HANDLE_T                h_listbox,
                    UINT16                  ui2_idx
                    )
{
    INT32                   i4_ret;
    INT32                   ui4_val = 0;
    UTF16_T                 w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    nav_fac_tcon_get_setup_value(ui2_idx, &ui4_val);
    switch (ui2_idx)
    {
        case NAV_FAC_TCON_MENU_VCOM_VALUE:
        case NAV_FAC_TCON_MENU_GAMMA1:
        case NAV_FAC_TCON_MENU_GAMMA2:
        case NAV_FAC_TCON_MENU_GAMMA3:
        case NAV_FAC_TCON_MENU_GAMMA4:
        case NAV_FAC_TCON_MENU_GAMMA5:
        case NAV_FAC_TCON_MENU_GAMMA6:
        case NAV_FAC_TCON_MENU_GAMMA7:
        case NAV_FAC_TCON_MENU_GAMMA8:
            nav_fac_number_to_string(ui4_val, w2s_menu_item_string);
            break;
        case NAV_FAC_TCON_MENU_VCOM_STORE:
            if (ui1_nav_fac_vcom_store_done == VCOM_STORE_STATUS_DONE) {
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_DONE));
            }
            else if (ui1_nav_fac_vcom_store_done == VCOM_STORE_STATUS_FAIL){
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_FAIL));
            }
            else{
                c_uc_w2s_strcpy(w2s_menu_item_string, MLM_FAC_TEXT(nav_get_mlm_lang_id(), MLM_FAC_KEY_MSG_PRESS));
            }
            break;
        default :
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_do_cmd(
                h_listbox,
                WGL_CMD_LB_SET_ITEM_TEXT,
                WGL_PACK_2(ui2_idx, 2),
                WGL_PACK(w2s_menu_item_string)
                );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_menu_list_set_content
 * Description: Get the item content from EEPROM and set it to setup list box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_tcon_view_menu_list_set_content(
                    HANDLE_T                h_listbox
                     )
{
    INT32               i4_ret;
    UINT16              ui2_idx;

    for (ui2_idx = 0; ui2_idx < NAV_FAC_TCON_MENU_MAX_ELEM; ui2_idx++)
    {
        i4_ret= _nav_fac_tcon_view_menu_list_set_content_item(h_listbox, ui2_idx);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_menu_list_set_text
 * Description: Set text for items of list box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_tcon_view_menu_list_set_text(HANDLE_T h_listbox)
{
    INT32               i4_ret;
    UINT16              ui2_idx;
    UTF16_T             w2s_menu_item_string[NAV_FAC_MENU_TEXT0_LEN + 1] = {0};

    for (ui2_idx = 0; ui2_idx < NAV_FAC_TCON_MENU_MAX_ELEM; ui2_idx++)
    {
        c_uc_w2s_strcpy(w2s_menu_item_string,
        MLM_FAC_TEXT(nav_get_mlm_lang_id(), aui2_item_fac_tcon_menu[ui2_idx]));

        i4_ret = c_wgl_do_cmd(
                                h_listbox,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2(ui2_idx, 0),
                                WGL_PACK(w2s_menu_item_string)
                                );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_menu_list_key_map
 * Description: Set key map for listbox
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32   _nav_fac_tcon_view_menu_list_key_map(
                        HANDLE_T                h_listbox
                        )
{
    INT32                   i4_ret;
    WGL_LB_KEY_MAP_T        t_key_map = {0};

    t_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
    t_key_map.ui4_key_prev      = BTN_CURSOR_UP;
    t_key_map.ui4_key_select    = 0;
    t_key_map.ui4_key_page_up   = 0;
    t_key_map.ui4_key_page_down = 0;

    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_SET_KEY_MAP,
                    WGL_PACK(& t_key_map),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_menu_list_box_attr_init
 * Description: Set the attribute for list box
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_tcon_view_menu_list_box_attr_init(
                    HANDLE_T                h_listbox,
                    WGL_HIMG_TPL_T          h_img_bk,
                    WGL_HIMG_TPL_T          h_hlt_bar_img,
                    WGL_HIMG_TPL_T          h_hlt_unfocus_bar_img,
                    APP_COLOR_TYPE_T        e_color_type
                    /*,UINT16                  ui2_menu_type*/
                    )
{
    INT32                       i4_ret;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_IMG_INFO_T              t_img_info;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    /* Set image backgrond for list box*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_img_bk;
    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set image background for each item*/
    t_img_elem.h_normal              = NULL_HANDLE;
    t_img_elem.h_disable             = NULL_HANDLE;
    t_img_elem.h_highlight           = h_hlt_bar_img;
    t_img_elem.h_highlight_unfocus   = h_hlt_unfocus_bar_img;
    t_img_elem.h_pushed              = NULL_HANDLE;
    t_img_elem.h_selected            = NULL_HANDLE;
    t_img_elem.h_selected_disable    = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                    WGL_PACK(& t_img_elem),
                    NULL
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set font for each item of col*/
    i4_ret = c_wgl_do_cmd(
                    h_listbox,
                    WGL_CMD_LB_SET_COL_FONT,
                    WGL_PACK(0),
                    WGL_PACK(&t_elem_font_info)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set fg color for each item */
    t_color_elem.t_normal             = FAC_MENU_COL_N_FG_COLOR(e_color_type);
    t_color_elem.t_disable            = FAC_MENU_COL_D_FG_COLOR(e_color_type);
    t_color_elem.t_highlight          = FAC_MENU_COL_H_FG_COLOR_1(e_color_type);
    t_color_elem.t_highlight_unfocus  = FAC_MENU_COL_HU_FG_COLOR(e_color_type);
    t_color_elem.t_pushed             = FAC_MENU_COL_P_FG_COLOR(e_color_type);
    t_color_elem.t_selected           = FAC_MENU_COL_S_FG_COLOR(e_color_type);
    t_color_elem.t_selected_disable   = FAC_MENU_COL_SD_FG_COLOR(e_color_type);
    i4_ret = c_wgl_do_cmd (
                    h_listbox,
                    WGL_CMD_LB_SET_COL_COLOR,
                    WGL_PACK_2(0, WGL_CLR_TEXT),
                    WGL_PACK(&t_color_elem)
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set font for each item of col1*/
    i4_ret = c_wgl_do_cmd(
                h_listbox,
                WGL_CMD_LB_SET_COL_FONT,
                WGL_PACK(2),
                WGL_PACK(&t_elem_font_info)
                );
    if(WGLR_OK != i4_ret) {
    return NAVR_FAIL;
    }

    /* Set fg color for each item */
    t_color_elem.t_normal             = FAC_MENU_COL_N_FG_COLOR(e_color_type);
    t_color_elem.t_disable            = FAC_MENU_COL_D_FG_COLOR(e_color_type);
    t_color_elem.t_highlight          = FAC_MENU_COL_H_FG_COLOR_1(e_color_type);
    t_color_elem.t_highlight_unfocus  = FAC_MENU_COL_HU_FG_COLOR(e_color_type);
    t_color_elem.t_pushed             = FAC_MENU_COL_P_FG_COLOR(e_color_type);
    t_color_elem.t_selected           = FAC_MENU_COL_S_FG_COLOR(e_color_type);
    t_color_elem.t_selected_disable   = FAC_MENU_COL_SD_FG_COLOR(e_color_type);
    i4_ret = c_wgl_do_cmd (
                h_listbox,
                WGL_CMD_LB_SET_COL_COLOR,
                WGL_PACK_2(2, WGL_CLR_TEXT),
                WGL_PACK(&t_color_elem)
                );

    if(WGLR_OK != i4_ret) {
    return NAVR_FAIL;
    }

    /* set text scrolling styles */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 1;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;
    i4_ret = c_wgl_do_cmd (
                    h_listbox,
                    WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                    WGL_PACK (& t_hlt_elem_effect),
                    NULL);
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_menu_title_attr_init
 * Description: Set the attribute for menu title
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_tcon_view_menu_title_attr_init(
                    HANDLE_T                h_widget,
                    APP_COLOR_TYPE_T        e_color_type

                    )
{
    INT32                   i4_ret;
    WGL_COLOR_INFO_T        t_clr_info;

    /* set fac Tcon menu title text info */
   i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)&t_title_font_info,
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = FAC_MENU_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = FAC_MENU_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = FAC_MENU_TITLE_FG_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = LST_BOX_TITLE_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = LST_BOX_TITLE_FG_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = LST_BOX_TITLE_FG_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_LB_TITLE_FG,
                    &t_clr_info
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable     = FAC_MENU_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_enable      = FAC_MENU_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_highlight   = FAC_MENU_TITLE_BK_COLOR(e_color_type);
    t_clr_info.u_color_data.t_standard.t_disable.a   = LST_BOX_TITLE_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_enable.a    = LST_BOX_TITLE_BK_ALPHA;
    t_clr_info.u_color_data.t_standard.t_highlight.a = LST_BOX_TITLE_BK_ALPHA;
    i4_ret = c_wgl_do_cmd(
                    h_widget,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_LB_TITLE_BK,
                    &t_clr_info
                    );

    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
      return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_update_text
 * Description: Update string for fac TCon setup frame
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_tcon_view_update_text(VOID)
{
    INT32                   i4_ret;
    UTF16_T                 w2s_title[NAV_FAC_MENU_TEXT0_LEN] = {0};
    UTF16_T                 w2s_tmp[13] = { 'T', 'C', 'o', 'n', ' ', 'S', 'e', 't', 't', 'i', 'n', 'g', '\0'};
    NAV_FAC_TCON_VIEW_T*    pt_view     = &t_g_nav_fac_tcon_view;

   c_uc_w2s_strcat(w2s_title, w2s_tmp);

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_TITLE_TEXT,
                    WGL_PACK(w2s_title),
                    WGL_PACK(c_uc_w2s_strlen(w2s_title)));
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set element text for fac TCon menu*/
    _nav_fac_tcon_view_menu_list_set_text(pt_view->h_fac_tcon_list_box);

    /* Set item content*/
    _nav_fac_tcon_view_menu_list_set_content(pt_view->h_fac_tcon_list_box);

    _nav_fac_tcon_view_menu_list_update_item(pt_view->h_fac_tcon_list_box,
                                                NAV_FAC_TCON_MENU_VCOM_STORE, TRUE);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_set_skin
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_tcon_view_set_skin(
                    VOID
                    )
{
    INT32                   i4_ret;
    WGL_INSET_T             t_inset;
    WGL_LB_TITLE_INFO_T     t_title;
    NAV_FAC_TCON_VIEW_T*    pt_view = &t_g_nav_fac_tcon_view;

    /* Set setup menu item inset */
    t_inset.i4_left   = NAV_FAC_MENU_TEXT0_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_TEXT0_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_TEXT0_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_TEXT0_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(0),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set left arrow for each item*/
    t_inset.i4_left   = NAV_FAC_MENU_ICON0_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_ICON0_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_ICON0_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_ICON0_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(1),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set setup item content inset */
    t_inset.i4_left   = NAV_FAC_MENU_TEXT1_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_TEXT1_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_TEXT1_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_TEXT1_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(2),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set right arrow for each item*/
    t_inset.i4_left   = NAV_FAC_MENU_ICON1_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_ICON1_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_ICON1_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_ICON1_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_COL_INSET,
                    WGL_PACK(3),
                    WGL_PACK(&t_inset)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set content inset for setup menu*/
    t_inset.i4_left   = NAV_FAC_MENU_LEFT_INSET;
    t_inset.i4_right  = NAV_FAC_MENU_RIGHT_INSET;
    t_inset.i4_top    = NAV_FAC_MENU_TOP_INSET;
    t_inset.i4_bottom = NAV_FAC_MENU_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_CNT_INSET,
                    WGL_PACK(&t_inset),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set element inset for setup menu*/
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_ELEM_INSET,
                    WGL_PACK(&t_inset),
                    NULL
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /* Set menu title inset */
    t_title.ui1_align = WGL_AS_CENTER_CENTER;
    SET_RECT_BY_SIZE(
                    &t_title.t_rect,
                    NAV_FAC_SETUP_TITLE_LEFT,
                    NAV_FAC_SETUP_TITLE_TOP,
                    NAV_FAC_SETUP_TITLE_WIDTH,
                    NAV_FAC_SETUP_TITLE_HEIGHT
                    );
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_fac_tcon_list_box,
                    WGL_CMD_LB_SET_TITLE_INFO,
                    (VOID*)&t_title,
                    (VOID*)0
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set menu list for setup menu*/
#ifdef USE_TCON_MENU_BK_IMG //Denny 2009/11/30 add
    _nav_fac_tcon_view_menu_list_box_attr_init(pt_view->h_fac_tcon_list_box, pt_view->h_fac_tcon_menu_img_bk,
                                          pt_view->h_fac_tcon_hlt_img_bk, NULL_HANDLE, pt_view->e_color_type);
#else
    _nav_fac_tcon_view_menu_list_box_attr_init(pt_view->h_fac_tcon_list_box, NULL_HANDLE,
                                          NULL_HANDLE, NULL_HANDLE, pt_view->e_color_type);
#endif

    /* Set menu title attribute for setup menu*/
    _nav_fac_tcon_view_menu_title_attr_init(pt_view->h_fac_tcon_list_box, pt_view->e_color_type);

    /* Set key map for list box  */
    _nav_fac_tcon_view_menu_list_key_map(pt_view->h_fac_tcon_list_box);

    /* Update string for all text */
    _nav_fac_tcon_view_update_text();

     return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_proc_fct
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_fac_tcon_view_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32                   i4_ret;
    INT16                   ui2_hlt_idx = 0;
    INT16                   ui2_min = 0;
    INT16                   ui2_max = 0;
    INT32                   ui4_val;
    NAV_FAC_TCON_VIEW_T*    pt_view = &t_g_nav_fac_tcon_view;
    const CHAR*             s_tmp_str;
    UTF16_T                 w2s_menu_item_string[NAV_FAC_MENU_TEXT1_LEN + 1] = {0};

    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:

            switch((UINT32)pv_param1)
            {
                case BTN_CURSOR_LEFT:
                    i4_ret = c_wgl_do_cmd(pt_view->h_fac_tcon_list_box,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt_idx),
                                          NULL);
                    if(WGLR_OK != i4_ret) {
                        return NAVR_FAIL;
                    }

                    nav_fac_tcon_get_setup_value(ui2_hlt_idx, &ui4_val);
                    nav_fac_tcon_get_setup_min_max(ui2_hlt_idx, &ui2_min, &ui2_max);

                    if (ui4_val <= ui2_min) {
                        ui4_val = ui2_max;
                    } else {
                       ui4_val = ui4_val - 1;
                    }

                    i4_ret = nav_fac_tcon_set_setup_value(ui2_hlt_idx, ui4_val);
                    if (i4_ret != NAVR_OK) {
                        return NAVR_FAIL;
                    }
                    
                    _nav_fac_tcon_view_menu_list_set_content_item(  pt_view->h_fac_tcon_list_box,
                                                                    ui2_hlt_idx);
                    switch(ui2_hlt_idx)	//Emerson add 2008-0919
                    {
                    default:
                        _nav_fac_tcon_view_menu_list_update_item(   pt_view->h_fac_tcon_list_box,
                                                                    ui2_hlt_idx,TRUE);
                        break;
                    }
                    break;
                case BTN_CURSOR_RIGHT:
                    i4_ret = c_wgl_do_cmd(pt_view->h_fac_tcon_list_box,
                                          WGL_CMD_LB_GET_HLT_INDEX,
                                          WGL_PACK(&ui2_hlt_idx),
                                          NULL);
                    if(WGLR_OK != i4_ret)
                    {
                        return NAVR_FAIL;
                    }
                    if(ui2_hlt_idx == NAV_FAC_TCON_MENU_EXIT)//Emerson Add for Exit item 2008-0922
                    {
                        _nav_fac_tcon_view_rcu_key_handler((UINT32)BTN_EXIT);
                        break;
                    }

                    nav_fac_tcon_get_setup_value(ui2_hlt_idx, &ui4_val);

                    switch(ui2_hlt_idx)
                    {
                    case NAV_FAC_TCON_MENU_VCOM_STORE:
                        s_tmp_str = "Doing..";
                        c_memset(w2s_menu_item_string, 0, sizeof(w2s_menu_item_string));
                        c_uc_ps_to_w2s(s_tmp_str, w2s_menu_item_string, (NAV_FAC_MENU_TEXT1_LEN + 1));
                        i4_ret = c_wgl_do_cmd(  pt_view->h_fac_tcon_list_box,
                                                WGL_CMD_LB_SET_ITEM_TEXT,
                                                WGL_PACK_2(NAV_FAC_TCON_MENU_VCOM_STORE, 2),
                                                WGL_PACK(w2s_menu_item_string)
                                              );
                        if (i4_ret != WGLR_OK) {
                            return NAVR_FAIL;
                        }
                        _nav_fac_tcon_view_menu_list_update_item(   pt_view->h_fac_tcon_list_box,
                                                                    ui2_hlt_idx, TRUE);

                        i4_ret = nav_fac_BUF08630_store_vcom_val();

                        if(i4_ret == TCON_OK)
                        {
                            ui1_nav_fac_vcom_store_done = VCOM_STORE_STATUS_DONE;
                            { // Write default Gamma by panel
                                UINT8 ui1_i;
                                for(ui1_i=0; ui1_i<8; ui1_i++)
                                {
                                    nav_fac_BUF08630_write_def_gamma_by_panel_id(ui1_i);
                                }
                            }
                        }
                        else
                            ui1_nav_fac_vcom_store_done = VCOM_STORE_STATUS_FAIL;
                        break;
                    default:
                        break;
                    }
                    nav_fac_tcon_get_setup_min_max(ui2_hlt_idx, &ui2_min, &ui2_max);
                    if (ui4_val >= ui2_max) {
                        ui4_val = ui2_min;
                    }
                    else {
                        ui4_val = ui4_val + 1;
                    }

                    i4_ret = nav_fac_tcon_set_setup_value(ui2_hlt_idx, ui4_val);
                    if (i4_ret != NAVR_OK) {
                        return NAVR_FAIL;
                    }

                    _nav_fac_tcon_view_menu_list_set_content_item(  pt_view->h_fac_tcon_list_box,
                                                                    ui2_hlt_idx);
                    switch(ui2_hlt_idx)
                    {
                    case NAV_FAC_TCON_MENU_VCOM_STORE:
                        break;
                    default:
                        break;
                    }
                    
                    i4_ret = _nav_fac_tcon_view_menu_list_update_item(	pt_view->h_fac_tcon_list_box,
                                                                ui2_hlt_idx, TRUE);
                    if (i4_ret != NAVR_OK) {
                        return NAVR_FAIL;
                    }
                    
                    break;

                default:
                    /* Run NAV default key handler first */
                    _nav_fac_tcon_view_rcu_key_handler((UINT32)pv_param1);
                    break;
            }
        default:
            break;
    }

        /* Run WIDGET default key handler next */
    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_create_widget
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_create_widget(VOID)
{
    NAV_FAC_TCON_VIEW_T*     pt_view = &t_g_nav_fac_tcon_view;
    GL_RECT_T           t_rect;
    INT32               i4_ret;
    WGL_LB_INIT_T       t_list_box_init;
    WGL_LB_COL_INIT_T   at_cols[4];

     /* Create frame for fac TCon menu */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    pt_view->i4_frame_x_offset + NAV_FAC_SETUP_FRAME_LEFT,
                    pt_view->i4_frame_y_offset + NAV_FAC_SETUP_FRAME_TOP,
                    NAV_FAC_SETUP_FRAME_WIDTH,
                    NAV_FAC_TCON_SETUP_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_fac_tcon_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_IMG_UI| WGL_STL_GL_NO_BK), // NULL, //Denny 2009/11/30 modify
                    NULL,
                    &pt_view->h_fac_tcon_main_frame
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* menu item column text */
    at_cols[0].e_col_type             = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align              = NAV_FAC_MENU_TEXT0_ALIGNMENT;
    at_cols[0].ui2_max_text_len       = NAV_FAC_MENU_TEXT0_LEN;
    at_cols[0].ui2_width              = NAV_FAC_MENU_TEXT0_WIDTH;

    /* icon column */
    at_cols[1].e_col_type             = LB_COL_TYPE_IMG_SUIT;
    at_cols[1].ui1_align              = NAV_FAC_MENU_ICON0_ALIGNMENT;
    at_cols[1].ui2_width              = NAV_FAC_MENU_ICON0_WIDTH;

    /* menu item column text */
    at_cols[2].e_col_type             = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align              = NAV_FAC_MENU_TEXT1_ALIGNMENT;
    at_cols[2].ui2_max_text_len       = NAV_FAC_MENU_TEXT1_LEN;
    at_cols[2].ui2_width              = NAV_FAC_MENU_TEXT1_WIDTH;

    /* icon column */
    at_cols[3].e_col_type             = LB_COL_TYPE_IMG_SUIT;
    at_cols[3].ui1_align              = NAV_FAC_MENU_ICON1_ALIGNMENT;
    at_cols[3].ui2_width              = NAV_FAC_MENU_ICON1_WIDTH;

    t_list_box_init.ui4_style         = WGL_STL_LB_FIXED_ELEM_NUM;
    t_list_box_init.ui2_max_elem_num  = NAV_FAC_TCON_MENU_MAX_ELEM;
    t_list_box_init.ui2_elem_size     = ELEM_HEIGHT_OF_FAC_MENU;
    t_list_box_init.ui2_elem_distance = ELEM_DTANCE_OF_FAC_MENU;
    t_list_box_init.ui1_col_num       = 4;
    t_list_box_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(
                    &t_rect,
                    NAV_FAC_SETUP_MENU_LEFT,
                    NAV_FAC_SETUP_MENU_TOP,
                    NAV_FAC_SETUP_MENU_WIDTH,
                    NAV_FAC_TCON_SETUP_MENU_HEIGHT
                    );

    i4_ret = c_wgl_create_widget(
                    pt_view->h_fac_tcon_main_frame,
                    HT_WGL_WIDGET_LIST_BOX,
                    WGL_CONTENT_LIST_BOX_DEF,
                    WGL_BORDER_TRANSP,
                    &t_rect,
                    _nav_fac_tcon_view_proc_fct,
                    DEFAULT_BK_ALPHA,
                    &t_list_box_init,
                    NULL,
                    &pt_view->h_fac_tcon_list_box
                    );

    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _nav_fac_tcon_view_set_skin();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_init
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_init(
                    NAV_FAC_TCON_T*                  pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    NAV_FAC_TCON_VIEW_T*    pt_view = &t_g_nav_fac_tcon_view;
    INT32  i4_ret;

    /* Set the einitial index as 0 for each list box*/
    pt_view->ui2_fac_tcon_menu_elem_idx = 0;

    pt_view->pt_ctrl = pt_ctrl;
    pt_view->h_fac_tcon_canvas = h_canvas;
    pt_view->i4_frame_x_offset = i4_frame_x_offset;
    pt_view->i4_frame_y_offset = i4_frame_y_offset;
    pt_view->e_color_type = e_color_type;

    pt_view->b_widget_created = FALSE;
#ifdef USE_TCON_MENU_BK_IMG //Denny 2009/11/30 add
    /* Init Image */
    i4_ret = nav_fac_img_create_menu_bk_img_tpl(&pt_view->h_fac_tcon_menu_img_bk);
    if (i4_ret != NAVR_OK) {
        DBG_LOG_PRINT(("nav_img_create_fac_menu_bk_img_tpl() failed. i4_ret = %d on _nav_fac_tcon_view_init() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return NAVR_FAIL;
    }

    i4_ret = nav_fac_img_create_menu_hilight_img_tpl(&pt_view->h_fac_tcon_hlt_img_bk);
    if(NAVR_OK != i4_ret){
        DBG_LOG_PRINT(("nav_img_create_hlt_bar_bk_img_tpl() failed. i4_ret = %d on _nav_fac_tcon_view_init() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return NAVR_FAIL;
    }
#endif

    i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_g_nav_tcon_svctx);
    if (i4_ret != NAVR_OK) {
        DBG_LOG_PRINT(("c_svctx_open() failed. i4_ret = %d on _nav_fac_tcon_view_init() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_deinit
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_deinit(
                    VOID
                    )
{
    NAV_FAC_TCON_VIEW_T* pt_view = &t_g_nav_fac_tcon_view;

    c_wgl_destroy_widget(pt_view->h_fac_tcon_main_frame);
    c_wgl_destroy_widget(pt_view->h_fac_tcon_list_box);
    
#ifdef USE_TCON_MENU_BK_IMG //Denny 2009/11/30 add
    c_wgl_img_tpl_destroy (pt_view->h_fac_tcon_menu_img_bk);
    c_wgl_img_tpl_destroy (pt_view->h_fac_tcon_hlt_img_bk);
#endif

    if(h_g_nav_tcon_svctx != NULL_HANDLE)
    {
        c_svctx_close(h_g_nav_tcon_svctx);
        h_g_nav_tcon_svctx = NULL_HANDLE;
    }

    pt_view->pt_ctrl  = NULL;
    pt_view->h_fac_tcon_main_frame         = NULL_HANDLE;
    pt_view->h_fac_tcon_list_box           = NULL_HANDLE;
    
#ifdef USE_TCON_MENU_BK_IMG //Denny 2009/11/30 add
    pt_view->h_fac_tcon_menu_img_bk         = NULL_HANDLE;
    pt_view->h_fac_tcon_hlt_img_bk          = NULL_HANDLE;
#endif

    return NAVR_OK;
}

 /*-----------------------------------------------------------------------------
 * Name: _nav_fac_tcon_view_activate
 * Description:  Callback function for FAC TCon view model activate
 * Inputs:
 * Outputs: NONE
 * Returns: NAVR_OK:            The function success.
 *          NAVR_FAIL           The function fail.
 ----------------------------------------------------------------------------*/
static INT32 _nav_fac_tcon_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_FAC_TCON_VIEW_T* pt_view = &t_g_nav_fac_tcon_view;
    INT32           i4_ret;
//    UINT32         ui4_misc_ctrl;

    ui1_nav_fac_vcom_store_done = VCOM_STORE_STATUS_WAIT_KEY;

    /* After FAC TCon menu iss launched, temporarily unlock key */
    nav_fac_unlock_key();

    /*Create widget when fac TCon menu is launched at the first time */
    if (!pt_view->b_widget_created) {
        _nav_fac_tcon_view_create_widget();
        pt_view->b_widget_created = TRUE;
    }

    /* Set the initial index as 0 for each list box*/
    pt_view->ui2_fac_tcon_menu_elem_idx = 0;

    i4_ret = _nav_fac_tcon_view_update(pt_view);
    if (i4_ret != NAVR_OK) {
        DBG_LOG_PRINT(("_nav_fac_tcon_view_update() failed. i4_ret = %d on _nav_fac_tcon_view_activate() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return NAVR_FAIL;
    }

    i4_ret = _nav_fac_tcon_view_update_text();
    if (i4_ret != NAVR_OK) {
        DBG_LOG_PRINT(("_nav_fac_tcon_view_update_text() failed. i4_ret = %d on _nav_fac_tcon_view_activate() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return NAVR_FAIL;
    }

    i4_ret = _nav_fac_tcon_view_show(pt_view, FALSE);
    if (i4_ret != NAVR_OK) {
        DBG_LOG_PRINT(("_nav_fac_tcon_view_show() failed. i4_ret = %d on _nav_fac_tcon_view_activate() at line %d of %s.\r\n", i4_ret, __LINE__, __FILE__));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: nav_fac_get_setup_min_max
 * Description: Get the acceptable value range for the inputed item.
 * Inputs:
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/

INT32 nav_fac_tcon_get_setup_min_max(
                    UINT16                ui2_idx,
                    INT16*                pui2_min,
                    INT16*                pui2_max)
{
    INT32  i4_ret = NAVR_OK;
    INT16  i2_min = 0;
    INT16  i2_max = 0;

    switch (ui2_idx)
    {
        case NAV_FAC_TCON_MENU_VCOM_VALUE:
        #if 0
            i4_ret = nav_fac_get_tcon_reg_val( FAC_VCOM_MIN_REG, &ui2_tmp );
            i2_min = (INT16)ui2_tmp;

            if( i4_ret != APP_CFGR_OK )
                return NAVR_FAIL;
            i4_ret = nav_fac_get_tcon_reg_val( FAC_VCOM_MAX_REG, &ui2_tmp );
            i2_max = (INT16)ui2_tmp;

            if( i4_ret != APP_CFGR_OK )
                return NAVR_FAIL;
            break;
        #else
        {
            UINT16 ui2_max_temp, ui2_min_temp;
            i4_ret = nav_fac_BUF08630_get_vcom_max_min_val(&ui2_max_temp, &ui2_min_temp);
            if( i4_ret != APP_CFGR_OK ){
                return NAVR_FAIL;
            }
            i2_max = (INT16)ui2_max_temp;
            i2_min = (INT16)ui2_min_temp;
            break;
        }
        #endif
        case NAV_FAC_TCON_MENU_GAMMA1:
        case NAV_FAC_TCON_MENU_GAMMA2:
        case NAV_FAC_TCON_MENU_GAMMA3:
        case NAV_FAC_TCON_MENU_GAMMA4:
        case NAV_FAC_TCON_MENU_GAMMA5:
        case NAV_FAC_TCON_MENU_GAMMA6:
        case NAV_FAC_TCON_MENU_GAMMA7:
        case NAV_FAC_TCON_MENU_GAMMA8:
            i2_min = 0;
            i2_max = 1023;
            break;
        case NAV_FAC_TCON_MENU_VCOM_STORE:
        case NAV_FAC_TCON_MENU_EXIT:
            i2_min = 0;
            i2_max = 1;
            break;
        default :
            return NAVR_FAIL;
    }
    *pui2_min = i2_min;
    *pui2_max = i2_max;
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_tcon_get_setup_value
 * Description: Get value to EEPROM.
 * Inputs:  ui2_idx     - the item index of setup menu
 * Outputs: pui4_val    - the value of this item
 * Returns: NONE
 ----------------------------------------------------------------------------*/
INT32 nav_fac_tcon_get_setup_value(
    UINT16              ui2_idx,
    INT32*              pi4_val)
{
    INT32   i4_ret = NAVR_OK;
    UINT16  ui2_drv_val = 0;

    switch (ui2_idx)
    {
        case NAV_FAC_TCON_MENU_VCOM_VALUE:
        {
            i4_ret =  nav_fac_BUF08630_get_vcom_reg_val( (UINT16*)&ui2_drv_val );
            if( i4_ret != TCON_OK )
            {
                i4_ret = NAVR_FAIL ;
            }
        }
        break;

        case NAV_FAC_TCON_MENU_GAMMA1:
        case NAV_FAC_TCON_MENU_GAMMA2:
        case NAV_FAC_TCON_MENU_GAMMA3:
        case NAV_FAC_TCON_MENU_GAMMA4:
        case NAV_FAC_TCON_MENU_GAMMA5:
        case NAV_FAC_TCON_MENU_GAMMA6:
        case NAV_FAC_TCON_MENU_GAMMA7:
        case NAV_FAC_TCON_MENU_GAMMA8:
        {
            i4_ret =  nav_fac_BUF08630_get_tcon_gamma_reg_val( (UINT8)(ui2_idx-NAV_FAC_TCON_MENU_GAMMA1), (UINT16*)&ui2_drv_val );
            if( i4_ret != APP_CFGR_OK )
            {
                i4_ret = NAVR_FAIL ;
            }
        }
        break;

       default :
           return NAVR_FAIL;
    }

    *pi4_val = ui2_drv_val;
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_tcon_set_setup_value
 * Description: Set value to EEPROM.
 * Inputs:  ui2_idx     - the item index of setid menu
 *          ui4_val     - the new value of this item
 * Outputs: NONE
 * Returns: NONE
 ----------------------------------------------------------------------------*/
INT32 nav_fac_tcon_set_setup_value(
    UINT16              ui2_idx,
    INT32               i4_val)
{
    INT32   i4_ret = NAVR_OK;

    switch (ui2_idx)
    {
        case NAV_FAC_TCON_MENU_VCOM_VALUE:
        {
            i4_ret = nav_fac_BUF08630_set_vcom_reg_val( (UINT16)i4_val );
            if( i4_ret != APP_CFGR_OK )
            {
                i4_ret = NAVR_FAIL ;
            }
        }
        break;

        case NAV_FAC_TCON_MENU_VCOM_STORE:
        case NAV_FAC_TCON_MENU_EXIT:
            break;
        default :
            return NAVR_FAIL;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: nav_fac_tcon_view_register_default_hdlr
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 nav_fac_tcon_view_register_default_hdlr(
                    NAV_FAC_TCON_VIEW_HDLR_T*       pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_fac_tcon_view_init;
    pt_view_hdlr->pf_deinit         = _nav_fac_tcon_view_deinit;
    pt_view_hdlr->pf_is_key_handler = _nav_fac_tcon_view_is_key_handler;
    pt_view_hdlr->pf_activate       = _nav_fac_tcon_view_activate;
    pt_view_hdlr->pf_hide           = _nav_fac_tcon_view_hide;

    return NAVR_OK;
}

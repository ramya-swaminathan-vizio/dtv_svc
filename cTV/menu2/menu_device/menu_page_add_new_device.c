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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
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

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svctx.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_dt.h"
#include "c_net_p2p_ctl.h"

#include "res/app_util/config/acfg_custom.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu_page_device_setting.h"
#include "menu_device.h"
#include "menu_page_device_status_info.h"
#include "menu_page_pair_wifi_device.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "menu_page_add_new_device.h"
#include "menu2/menu_util2.h"

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"

#include "wfrrc_interface.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "nav/wr_updater/wr_updater.h"

#include "res/menu2/menu_custom_dialog.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "mmp/app/mmp_main.h"
#ifdef APP_UEI_SPINNER_SUPPORT
#include "menu2/menu_common/menu_page_animation.h"
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef struct _MENU_SELECT_BRD_T
{
    HANDLE_T            h_brd_frm;
    HANDLE_T            h_brand_eb;
    HANDLE_T     		h_brand_vkb;
    HANDLE_T     		h_brd_eb_del_all;
}MENU_SELECT_BRD_T;

typedef struct _MENU_SELECT_MODEL_T
{
    HANDLE_T            h_model_frm;
    HANDLE_T            h_model_eb;
    HANDLE_T     		h_model_vkb;
    HANDLE_T     		h_model_eb_del_all;
}MENU_SELECT_MODEL_T;

typedef struct _MENU_SELECT_INP_T
{
    HANDLE_T            h_inp_frm;
}MENU_SELECT_INP_T;

typedef struct _MENU_DROP_DOWN_LIST_T
{
    HANDLE_T            h_drop_down_frm;
    HANDLE_T            h_drop_down_list;
    HANDLE_T            h_up_icon;
    HANDLE_T            h_down_icon;
}MENU_DROP_DOWN_LIST_T;

typedef struct __MENU_CUSTOM_DLG_DATA_T
{
    HANDLE_T                    h_parent;
    HANDLE_T                    h_dialog;
    HANDLE_T                    h_menu_current_focus;
    HANDLE_T                    h_hide_timer;
    UINT32                      ui4_timer_delay;
    BOOL                        b_is_show;
    BOOL                        b_is_inited;
}   _MENU_CUSTOM_DLG_DATA_T;

typedef struct __MENU_CUSTOM_WARNING_DLG_DATA_T
{
    HANDLE_T          h_dlg_frm;
    HANDLE_T          h_dlg_title;
    HANDLE_T          h_dlg_btn;
    HANDLE_T		  h_warning_icon;
}   _MENU_CUSTOM_WARNING_DLG_DATA_T;
typedef struct __MENU_CUSTOM_MANUAL_ENTER_CODE_DLG_DATA_T
{
    HANDLE_T          h_dlg_frm;
    HANDLE_T          h_dlg_title;
    HANDLE_T          h_dlg_yes_btn;
    HANDLE_T          h_dlg_no_btn;
    HANDLE_T		  h_dlg_editbox;
}   _MENU_CUSTOM_MANUAL_ENTER_CODE_DLG_DATA_T;
typedef struct _MENU_REMOTE_CODE_T
{
    HANDLE_T            h_code_frm;
    HANDLE_T            h_VIA_ctrl_txt;
    HANDLE_T            h_code_intro_txt;
    HANDLE_T            h_attemp_code_txt;
    HANDLE_T            h_it_work_btn;
    HANDLE_T            h_try_next_btn;
    HANDLE_T            h_manual_enter_code_btn;
}MENU_REMOTE_CODE_T;

typedef struct _MENU_ADD_NEW_DEVICE_PAGE_DATA_T
{
    HANDLE_T     h_cnt_frm;
    HANDLE_T     h_list_item_input_src;
    HANDLE_T     h_list_item_device_type;
    HANDLE_T     h_list_item_device_type_aud;
    HANDLE_T     h_list_item_device_brand;
    HANDLE_T     h_list_item_device_model;
    HANDLE_T     h_list_item_confirm_remote_connect;
    HANDLE_T     h_subpage_input;
    HANDLE_T     h_subpage_device_type;
    HANDLE_T     h_subpage_device_type_aud;
    HANDLE_T     h_subpage_device_brand;
    HANDLE_T     h_subpage_device_model;
    HANDLE_T     h_subpage_device_confirm;
    HANDLE_T     h_subpage_device_manual_enter_code;
    HANDLE_T     h_subpage_device_brand_title;
    HANDLE_T     h_subpage_device_model_title;
    HANDLE_T     h_last_focus_item;
    HANDLE_T     h_vkb_last_focus;
    HANDLE_T     h_ok_btn;
    HANDLE_T     h_cancel_btn;
    HANDLE_T	 h_current_focus;
    MENU_REMOTE_CODE_T t_remote_code;
    _MENU_CUSTOM_DLG_DATA_T		t_confirm_dlg;
    _MENU_CUSTOM_MANUAL_ENTER_CODE_DLG_DATA_T		t_manual_enter_code_dlg;
    _MENU_CUSTOM_WARNING_DLG_DATA_T		t_warning_dlg;
    ADD_NEW_DEVICE_PAGE_SUBPAGE_T e_subpage;
    ADD_NEW_DEVICE_PAGE_SUBPAGE_T e_pre_subpage;
	UINT8		 ui1_select_input;
	UINT8		 ui1_pre_select_input;
    CHAR         s_input_buf[32+1];
	UINT16                  aui2_brand_ids[MENU_ADD_NEW_DEVICE_BRAND_IDS_MAX_NUM];
    MENU_SELECT_BRD_T        t_select_brd;
    MENU_SELECT_MODEL_T      t_select_model;
    MENU_SELECT_INP_T        t_select_inp;
    MENU_DROP_DOWN_LIST_T    t_drop_down_lst;
	UINT16                  aui2_codeset[MENU_ADD_NEW_DEVICE_CODESET_MAX_NUM];
	BOOL                        b_is_db_locked;


	//==================integrate with dev DB================================
	/* dev type info */
    DEV_DB_TYPE_T               t_dev_type[DEV_DB_MAX_DEV_TYPE_CONT];
    UINT32                      ui4_type_sel_idx;
    UINT32                      ui4_type_num;
    BOOL                        b_is_type_sel;
    BOOL						b_is_brd_sel;

    /* input src info */
    BOOL                        b_is_sel_src_id[MENU_ADD_NEW_DEVICE_SETUP_INPUT_SRC_NUM];
    UINT8                       aui1_input_src_id[MENU_ADD_NEW_DEVICE_SETUP_INPUT_SRC_NUM];

    /* brand info of this view */
    DEV_DB_BRMD_T               t_brd_info[DEV_DB_DUL_OP_MAX];
    CHAR                        c_brd_pfx[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    UINT32                      ui4_brd_notify_count;
    UINT32                      ui4_brd_num;
    UINT32                      ui4_brd_sel_idx;

    /* model info of this view */
    DEV_DB_BRMD_T               t_mdl_info[DEV_DB_DUL_OP_MAX];
    CHAR                        c_mdl_pfx[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    UINT32                      ui4_mdl_notify_count;
    UINT32                      ui4_mdl_num;
    UINT32                      ui4_mdl_sel_idx;
    BOOL						b_is_mdl_sel;

    /* codeset info*/
    DEV_DB_CODESET_T*           pt_codeset;
    DEV_DB_CODESET_LIST_T*      pt_codeset_list;
    BOOL                        b_is_codeset_querying;
    UINT8                       ui1_codeset_num;
    UINT8                       ui1_cur_code_pos;
    BOOL 						b_is_i_do_not_know_mdl_sel;

    /* device setup info */
    CHAR                        s_type_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_inp_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_brd_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_model_name[DEV_SETUP_DB_NAME_LEN_MAX + 1];
    CHAR                        s_codeset[5 + 1];

    /* the glob init info*/
    UINT32                      ui4_nfy_id;
    BOOL                        b_is_notify_reg;

    BOOL                        b_is_setup_worked;

    /* for page show flag*/
    BOOL                    	b_is_page_show;
    ISO_639_LANG_T 				pre_s639_lang;/*record the pre language*/
    ISO_639_LANG_T 				crn_s639_lang;/*record the current language*/

    ADD_NEW_DEVICE_PAGE_ENTER_FROM_T  e_page_enter_from;

#ifdef APP_UEI_SPINNER_SUPPORT
	/*on line query spinner*/
	HANDLE_T					h_animation;
	BOOL         				b_animation;
	BOOL						b_is_brd_online_query_start;
	BOOL						b_is_brd_online_query_complete;
	HANDLE_T					h_brd_online_timer;
#endif

}MENU_ADD_NEW_DEVICE_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
           data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T t_g_menu_device_page_add_new_device;
static MENU_ADD_NEW_DEVICE_PAGE_DATA_T t_g_add_new_device_page_data;
extern INT32 menu_list_adjust_rect_ex(HANDLE_T h_widget);

/*-----------------------------------------------------------------------------
              function declarations
----------------------------------------------------------------------------*/
static INT32 _back_key_handler(VOID);
static INT32 _menu_add_new_device_create_desc_htxt(HANDLE_T   h_parent,
                                                    GL_RECT_T   *pt_rect,
                                                    HANDLE_T    *ph_widget);
static INT32 _menu_add_new_device_set_desc_htxt(HANDLE_T h_htext,
                                        UTF16_T* pw2s_text,
                                        WGL_HIMG_TPL_T h_img_1,
                                        WGL_HIMG_TPL_T h_img_2);
static INT32 _menu_add_new_device_custom_dialog_hide(VOID);
static INT32 _menu_add_new_device_confirm_code_chang_lang(BOOL    b_repaint);
static INT32 _add_new_device_page_show_subpage(BOOL b_repaint);
static INT32 _menu_add_new_device_drop_down_lb_update( BOOL b_repaint );
static INT32 _to_prev_input_src_idx(void);
static INT32 _to_next_input_src_idx(void);
static INT32 _menu_add_new_device_setup_save_and_upload_codeset(UINT32 ui4_idx);
static INT32 _menu_add_new_device_warning_dialog_create( VOID );
static INT32 _menu_add_new_device_change_input_src(VOID);
static INT32 _menu_add_new_device_manual_enter_code_dlg_hide(BOOL  b_repaint);
static INT32 _menu_add_new_device_manual_enter_code (VOID);

/*-----------------------------------------------------------------------------
               function implementations
----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:_add_new_device_page_reset_type_info
 *
 * Description: reset the glob type info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_reset_type_info(VOID)
{
    UINT32          				ui4_idx   = 0;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    for (ui4_idx = 0; ui4_idx < DEV_DB_MAX_DEV_TYPE_CONT; ui4_idx ++)
    {
        c_memset(&(pt_this->t_dev_type[ui4_idx]),0,sizeof (DEV_DB_TYPE_T));

        pt_this->t_dev_type[ui4_idx].i4_deva_src_idx  = -1;
        pt_this->t_dev_type[ui4_idx].i4_devb_src_idx  = -1;
    }

    pt_this->ui4_type_num = 0;
    pt_this->b_is_type_sel = FALSE;

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:_add_new_device_page_reset_brand_info
 *
 * Description: reset the glob brand info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_reset_brand_info(VOID)
{
    UINT32          ui4_idx   = 0;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the brand info*/
        c_memset(&(pt_this->t_brd_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_this->t_brd_info[ui4_idx].i4_local1_idx  = -1;
        pt_this->t_brd_info[ui4_idx].i4_online1_idx = -1;
        pt_this->t_brd_info[ui4_idx].i4_local2_idx  = -1;
        pt_this->t_brd_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_this->c_brd_pfx[ui4_idx] = '\0';
        pt_this->s_brd_name[ui4_idx] = '\0';
    }

    /* init the brand num*/
    pt_this->ui4_brd_num       = 0;
    pt_this->ui4_brd_sel_idx   = 0xFFFF;

#ifdef APP_UEI_SPINNER_SUPPORT
	pt_this->b_is_brd_online_query_start = FALSE;
	pt_this->b_is_brd_online_query_complete = FALSE;
#endif

    return DEV_DBR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:_add_new_device_page_reset_model_info
 *
 * Description: reset the glob model info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_reset_model_info(VOID)
{
    UINT32          ui4_idx   = 0;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    for (ui4_idx = 0; ui4_idx < DEV_DB_DUL_OP_MAX; ui4_idx ++)
    {
        /* init the model info*/
        c_memset(&(pt_this->t_mdl_info[ui4_idx]),0,sizeof (DEV_DB_BRMD_T));
        pt_this->t_mdl_info[ui4_idx].i4_local1_idx  = -1;
        pt_this->t_mdl_info[ui4_idx].i4_online1_idx = -1;
        pt_this->t_mdl_info[ui4_idx].i4_local2_idx  = -1;
        pt_this->t_mdl_info[ui4_idx].i4_online2_idx = -1;
    }

    for (ui4_idx = 0; ui4_idx < DEV_DB_NAME_LEN_MAX + 1; ui4_idx ++)
    {
        pt_this->c_mdl_pfx[ui4_idx] = '\0';
        pt_this->s_model_name[ui4_idx] = '\0';
    }

    /* init the model num*/
    pt_this->ui4_mdl_num       = 0;
    pt_this->ui4_mdl_sel_idx   = 0xFFFF;

    return DEV_DBR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:_add_new_device_page_reset_codeset_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_reset_codeset_info(VOID)
{
    UINT32                                  ui4_idx   = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    for (ui4_idx = 0; ui4_idx < 6; ui4_idx ++)
    {
        pt_this->s_codeset[ui4_idx] = '\0';
    }

    pt_this->ui1_cur_code_pos = 0;
    pt_this->ui1_codeset_num = 0;

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_list_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_list_codeset(UINT32 ui4_index)
{
    UINT32   ui4_idx              = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    DBG_INFO(("####%s(%d)codesetlist1_num[%d],codesetlist2_num[%d]\n",__FUNCTION__,__LINE__,
                pt_this->pt_codeset_list->t_codeset_list1.i4_length,
                pt_this->pt_codeset_list->t_codeset_list2.i4_length));

     /* for codeset list1*/
    for (ui4_idx = 0; ui4_idx < pt_this->pt_codeset_list->t_codeset_list1.i4_length; ui4_idx ++)
    {
        if (NULL != pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx])
        {
            DBG_INFO(("[####%s(%d)] codeset_idx[%-3d]---> codeset[%-20s]\n",
            			__FUNCTION__,
            			__LINE__,
                        ui4_idx,
                        pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]));

            if(ui4_index == ui4_idx)
            {
				c_memcpy(pt_this->s_codeset, pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx], 6);
            }
        }
    }

    /* for codeset list2*/
    for (ui4_idx = 0; ui4_idx < pt_this->pt_codeset_list->t_codeset_list2.i4_length; ui4_idx ++)
    {
        if (NULL != pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx])
        {
            DBG_INFO(("[####%s(%d)] codeset_idx[%-3d]---> codeset[%-20s]\n",
            			__FUNCTION__,
            			__LINE__,
                        ui4_idx + pt_this->pt_codeset_list->t_codeset_list1.i4_length,
                        pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx]));

            if(ui4_index == (ui4_idx + pt_this->pt_codeset_list->t_codeset_list1.i4_length))
            {
				c_memcpy(pt_this->s_codeset, pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx], 6);
			}
        }
    }

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
  Name:_add_new_device_page_reset_dev_info

  Description:reset the device info include: type/brand/model/codeset

  input:

  output:

  return:
----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_reset_dev_info(VOID)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

	_add_new_device_page_reset_type_info();
    _add_new_device_page_reset_brand_info();
    _add_new_device_page_reset_model_info();
    _add_new_device_page_reset_codeset_info();

    pt_this->ui1_select_input = 0;
	pt_this->b_is_brd_sel = FALSE;
	pt_this->b_is_mdl_sel = FALSE;

	return MENUR_OK;
}
/*----------------------------------------------------------------------------
* Name: _menu_add_new_device_update_dropdown_list
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
static INT32 _menu_add_new_device_update_dropdown_list( VOID )
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UINT16                                  ui2_idx = 0;
    INT32                                   i4_ret  = MENUR_OK;
    UTF16_T                                 w2s_text[DEV_DB_NAME_LEN_MAX+1]=L"";
    UINT16                                  ui2_elem_num = 0;

    DBG_API(("\n[####%s(%d)] drop down listbox update\n", __FUNCTION__,__LINE__));

    MENU_LOG_ON_FAIL(c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list, WGL_CMD_LB_DEL_ALL, NULL, NULL));

    if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
    {
        UINT16   ui2_brand_num = 0;

        i4_ret = a_dev_db_get_brand_list(pt_this->t_brd_info,
                                &(pt_this->ui4_brd_num),
                                pt_this->c_brd_pfx);

        if (MENUR_OK != i4_ret)
        {
            DBG_ERROR(("[####%s(%d)] a_dev_db_get_brand_list(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));
            return MENUR_FAIL;
        }

        if ((0 == pt_this->ui4_brd_num)
            || (pt_this->ui4_brd_num >= DEV_DB_DUL_OP_MAX))
        {
            DBG_ERROR( ("\n[####%s(%d)] the brand num value is invalid \n",__FUNCTION__,__LINE__));
            return MENUR_OK;
        }

        ui2_brand_num = pt_this->ui4_brd_num;

        a_dev_db_resort_bm_list_with_str(
                        pt_this->t_brd_info,
                        pt_this->ui4_brd_num,
                        "Vizio");

        /* set  listbox item number */
        i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                   WGL_CMD_LB_SET_ELEM_NUM,
                   WGL_PACK(ui2_brand_num),
                   NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        ui2_idx = 0;

        /* Iterate all the input sources */
        while (ui2_idx < ui2_brand_num)
        {
            c_uc_ps_to_w2s(pt_this->t_brd_info[ui2_idx].s_src_name, w2s_text, DEV_DB_NAME_LEN_MAX);
            /* set element text */
            i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2((ui2_idx), 0),
                                WGL_PACK(w2s_text));
            ui2_idx++;
        }

    }
    else if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
    {
        UINT16   ui2_model_num = 0;

        i4_ret = a_dev_db_get_model_list(pt_this->t_mdl_info,
                                               &(pt_this->ui4_mdl_num),
                                               pt_this->c_mdl_pfx);


        if (MENUR_OK != i4_ret)
        {
            DBG_ERROR(("[####%s(%d)] a_dev_db_get_model_list(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));
            return MENUR_FAIL;
        }

        if ((0 == pt_this->ui4_mdl_num)
            || (pt_this->ui4_mdl_num >= DEV_DB_DUL_OP_MAX))
        {
            DBG_ERROR( ("\n[####%s(%d)] the model num value is invalid",__FUNCTION__,__LINE__));
            return MENUR_OK;
        }

        ui2_model_num = pt_this->ui4_mdl_num;

        a_dev_db_resort_bm_list_with_str(
                        pt_this->t_mdl_info,
                        pt_this->ui4_mdl_num,
                        "Vizio");

        /* set  listbox item number */
        i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                   WGL_CMD_LB_SET_ELEM_NUM,
                   WGL_PACK(ui2_model_num),
                   NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        ui2_idx = 0;

        /* Iterate all the input sources */
        while (ui2_idx < ui2_model_num)
        {
            c_uc_ps_to_w2s(pt_this->t_mdl_info[ui2_idx].s_src_name, w2s_text, DEV_DB_NAME_LEN_MAX);
            /* set element text */
            i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                                WGL_CMD_LB_SET_ITEM_TEXT,
                                WGL_PACK_2((ui2_idx), 0),
                                WGL_PACK(w2s_text));
            ui2_idx++;
        }

    }

    i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK(0),
                          NULL);
    if(MENUR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                WGL_CMD_LB_HLT_ELEM_VISIBLE,
                WGL_PACK(0),
                WGL_PACK(0));

    MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_drop_down_frm, WGL_SW_RECURSIVE));

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui2_elem_num),
                                      NULL));

    if ((ui2_elem_num > 0) && (ui2_elem_num <= 3))
    {
        MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_down_icon, WGL_SW_HIDE));
        MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_up_icon, WGL_SW_HIDE));
    }
    else if (ui2_elem_num == 0)
    {
        MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_down_icon, WGL_SW_HIDE));
        MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_up_icon, WGL_SW_HIDE));
        MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_drop_down_frm, WGL_SW_HIDE_RECURSIVE));
    }
    else
    {
    	MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_up_icon, WGL_SW_HIDE));
        MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_down_icon, WGL_SW_NORMAL));
    }

    MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->t_drop_down_lst.h_drop_down_frm, NULL, TRUE));
    return MENUR_OK;
}
#ifdef APP_UEI_SPINNER_SUPPORT
/*----------------------------------------------------------------------------
* Name: _add_device_animation_stop
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Returns:
----------------------------------------------------------------------------*/
static VOID _add_device_animation_stop(VOID)
{
	INT32		i4_ret = MENUR_OK;
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

	if(pt_this->b_animation)
	{
		menu_page_animation_stop();
		menu_page_animation_hide();
		pt_this->b_animation = FALSE;

		i4_ret = c_timer_stop(pt_this->h_brd_online_timer);
	    MENU_LOG_ON_FAIL(i4_ret);
	}

}

/*----------------------------------------------------------------------------
* Name: _add_device_animation_do_timer_nfy
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Returns:
----------------------------------------------------------------------------*/
static VOID _add_device_animation_do_timer_nfy(
														VOID* pv_data,
														SIZE_T	z_data_size)
{
	_add_device_animation_stop();
	DBG_INFO(("\n####%s(%d)HIDE animation for timeout\n",__FUNCTION__,__LINE__));

}

/*----------------------------------------------------------------------------
* Name: _add_device_animation_timer_cb_fct
*
* Description:
*
* Inputs:
*
* Outputs:
*
* Returns:
----------------------------------------------------------------------------*/
static VOID _add_device_animation_timer_cb_fct(HANDLE_T  pt_tm_handle,
                                    VOID*     pv_tag)
{

    INT32 i4_ret = MENUR_OK;

    i4_ret = menu_async_invoke(_add_device_animation_do_timer_nfy,
                               NULL, 0, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

}
#endif
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_dev_db_local_query_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _menu_add_new_device_dev_db_local_query_hdlr(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    DEV_DB_BMC_QUERY_T*      pt_tag_query_info     = (DEV_DB_BMC_QUERY_T*)((UINT32)(pv_tag2));
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32    i4_ret;
    BOOL     b_need_to_update_brd_ui = FALSE;
    BOOL     b_need_to_update_mdl_ui = FALSE;


    CHAR     s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;

    a_am_get_active_app (s_active_app) ;

    /* if the page is not show or the current active app is not wizard should discard the notify info*/
    if ((FALSE == pt_this->b_is_page_show)
        || (c_strcmp(s_active_app, MENU_NAME) != 0))
    {
        return;
    }

    if ((DEV_DB_THREAD_QUERY_BRAND != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_MODEL != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_CODESET != pt_tag_query_info->e_query_type)
        && (DEV_DB_THREAD_QUERY_CODESET_WITH_BRD != pt_tag_query_info->e_query_type))
    {
        return;
    }


    if (DEV_DB_THREAD_QUERY_BRAND == pt_tag_query_info->e_query_type)
    {
        if ((0 == c_strcmp(pt_this->c_brd_pfx,pt_tag_query_info->s_brd_prefix))
            && (ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND == pt_this->e_subpage)
            && (pt_tag_query_info->ui4_notify_count != pt_this->ui4_brd_notify_count))
        {

#ifdef APP_UEI_SPINNER_SUPPORT
			DBG_INFO(("\n####%s(%d)DEV_DB_THREAD_QUERY_BRAND start=%d,complete=%d,notify_cnt=%d,this_cnt=%d\n",__FUNCTION__,__LINE__,pt_tag_query_info->b_is_brd_online_query_start,pt_tag_query_info->b_is_brd_online_query_complete,pt_tag_query_info->ui4_notify_count,pt_this->ui4_brd_notify_count));

			if(pt_tag_query_info->b_is_brd_online_query_start)
			{
				if(!pt_this->b_is_brd_online_query_start)
				{
					pt_this->b_is_brd_online_query_start = TRUE;

					menu_page_animation_start(1, FALSE);
					i4_ret = menu_page_animation_show();
					MENU_LOG_ON_FAIL(i4_ret);
					pt_this->b_animation = TRUE;

					c_timer_start(pt_this->h_brd_online_timer,
								60000,
								X_TIMER_FLAG_ONCE,
								_add_device_animation_timer_cb_fct,
								NULL);
				}
			}

			if(pt_tag_query_info->b_is_brd_online_query_complete)
			{
				pt_this->b_is_brd_online_query_complete = TRUE;

				_add_device_animation_stop();
				DBG_INFO(("\n####%s(%d)HIDE animation for complete\n",__FUNCTION__,__LINE__));
			}
#endif
            i4_ret = a_dev_db_get_brand_list(pt_this->t_brd_info,
                                    (UINT32*)(&(pt_this->ui4_brd_num)),
                                    pt_this->c_brd_pfx);

            DBG_INFO(("[####%s(%d)] a_dev_db_get_brand_list()--->ONLINE, i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));

            pt_this->ui4_brd_notify_count = pt_tag_query_info->ui4_notify_count;

            if ( MENUR_OK != i4_ret)
            {

#if 1
                    if (pt_tag_query_info->b_is_to_clean)
                    {
#ifdef APP_UEI_SPINNER_SUPPORT
						_add_device_animation_stop();
						DBG_INFO(("\n####%s(%d)HIDE animation for b_is_to_clean FAIL\n",__FUNCTION__,__LINE__));
#endif
                        a_dev_db_reset_bmc_query_info(pt_tag_query_info);
                        pt_this->ui4_brd_notify_count = 0;
                    }
#endif
                return;
            }



            b_need_to_update_brd_ui = TRUE;

        }
#ifdef APP_UEI_SPINNER_SUPPORT

        if ((ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND == pt_this->e_subpage)&&(pt_tag_query_info->b_is_to_clean))
        {
			_add_device_animation_stop();
			DBG_INFO(("\n####%s(%d)HIDE animation for b_is_to_clean OK\n",__FUNCTION__,__LINE__));
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
            pt_this->ui4_brd_notify_count = 0;
        }
#else

        if (pt_tag_query_info->b_is_to_clean)
        {
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
            pt_this->ui4_brd_notify_count = 0;
        }
#endif
    }

    if (DEV_DB_THREAD_QUERY_MODEL == pt_tag_query_info->e_query_type)
    {
        if ((0 == c_strcmp(pt_this->c_mdl_pfx,pt_tag_query_info->s_mdl_prefix))
            && (ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL == pt_this->e_subpage)
            && (pt_tag_query_info->ui4_notify_count != pt_this->ui4_mdl_notify_count))
        {
            i4_ret = a_dev_db_get_model_list(pt_this->t_mdl_info,
                                                   (UINT32*)(&(pt_this->ui4_mdl_num)),
                                                   pt_this->c_mdl_pfx);

            DBG_INFO(("[####%s(%d)] a_dev_db_get_model_list()--->ONLINE, i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));

            pt_this->ui4_mdl_notify_count = pt_tag_query_info->ui4_notify_count;


            if ( MENUR_OK != i4_ret)
            {

#if 1
                if (pt_tag_query_info->b_is_to_clean)
                {
                    a_dev_db_reset_bmc_query_info(pt_tag_query_info);
                    pt_this->ui4_mdl_notify_count = 0;
                }
#endif
                return;
            }



            b_need_to_update_mdl_ui = TRUE;

        }


        if (pt_tag_query_info->b_is_to_clean)
        {
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
            pt_this->ui4_mdl_notify_count = 0;
        }
    }

    if (DEV_DB_THREAD_QUERY_CODESET == pt_tag_query_info->e_query_type)
    {
        UINT8                                     ui1_src_idx;
        ISL_REC_T                                 t_isl_rec;
        CHAR                                      str_type[DEV_DB_NAME_LEN_MAX+1]="";
        BOOL                                      b_is_src_id_valid = FALSE;

		c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        i4_ret = a_dev_db_get_codeset(&(pt_this->pt_codeset));

        DBG_INFO(("[####%s(%d)] a_dev_db_get_codeset(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));
#if 1
        a_dev_db_reset_bmc_query_info(pt_tag_query_info);
#endif

        if (pt_this->ui1_select_input != 0xFF)
        {
            ui1_src_idx = pt_this->aui1_input_src_id[pt_this->ui1_select_input];
            a_isl_get_rec_by_idx(ui1_src_idx, &t_isl_rec);
            b_is_src_id_valid = TRUE;
        }
        else
        {
            b_is_src_id_valid = FALSE;
        }


        if (NULL != pt_this->pt_codeset->c_codeset1)
        {
            i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset->c_codeset1);

            DBG_INFO(("[####%s(%d)] a_dev_db_upload_codeset(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));

			if(pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
			{
				c_strncpy(str_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_DB_NAME_LEN_MAX);
			}
			else
			{
				c_strncpy(str_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_DB_NAME_LEN_MAX);
			}

            c_strncpy(pt_this->s_codeset, pt_this->pt_codeset->c_codeset1, 5);

            if (b_is_src_id_valid)
            {
				a_tv_net_custom_set_codeset(pt_this->s_codeset);

				DBG_INFO(("\n####%s(%d)a_cfg_custom_set_device_info,t_isl_rec.ui1_id = %d,str_type=%s,pt_this->s_brd_name=%s,pt_this->s_model_name=%s,pt_this->s_codeset=%s\n",
							__FUNCTION__,
							__LINE__,
							t_isl_rec.ui1_id,
							str_type,
							pt_this->s_brd_name,
							pt_this->s_model_name,
							pt_this->s_codeset));

                a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
                str_type,
                pt_this->s_brd_name,
                pt_this->s_model_name,
                pt_this->s_codeset);
            }
            else
            {
                UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
                UINT16  ui2_aud_out_mask;
                INT16   i2_val;

	            a_cfg_custom_set_device_info(0,
	                str_type,
	                pt_this->s_brd_name,
	                pt_this->s_model_name,
	                pt_this->s_codeset);

	            /*turn off TV speaker*/
                a_cfg_av_get(ui2_id, &i2_val);
                ui2_aud_out_mask = (UINT16)i2_val;

                if( (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) )
                {
                    /* Off */
                    ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

                    a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
                    a_cfg_av_update(ui2_id);
                }

				/* set audio ctrl flag to AUD_CONTROL_EXTERNAL */
				a_cfg_custom_set_vol_control(1);

				/* set sb_enable and sb codeset */
            	a_tv_net_custom_set_soundbar_flag(TRUE);
				a_tv_net_custom_set_soundbar_codeset(pt_this->s_codeset);

				DBG_INFO(("\n####%s(%d)a_cfg_custom_set_device_info,t_isl_rec.ui1_id = %d,str_type=%s,pt_this->s_brd_name=%s,pt_this->s_model_name=%s,pt_this->s_codeset=%s\n",
							__FUNCTION__,
							__LINE__,
							t_isl_rec.ui1_id,
							str_type,
							pt_this->s_brd_name,
							pt_this->s_model_name,
							pt_this->s_codeset));
            }
        }
        else if (NULL != pt_this->pt_codeset->c_codeset2)
        {
            i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset->c_codeset2);

            DBG_INFO(("[####%s(%d)] a_dev_db_upload_codeset(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));

			if(pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
			{
				c_strncpy(str_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_DB_NAME_LEN_MAX);
			}
			else
			{
				c_strncpy(str_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_DB_NAME_LEN_MAX);
			}

            c_strncpy(pt_this->s_codeset, pt_this->pt_codeset->c_codeset2, 5);


            if (b_is_src_id_valid)
            {
				a_tv_net_custom_set_codeset(pt_this->s_codeset);
                a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
                str_type,
                pt_this->s_brd_name,
                pt_this->s_model_name,
                pt_this->s_codeset);
            }
            else
            {
                UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
                UINT16  ui2_aud_out_mask;
                INT16   i2_val;

	            a_cfg_custom_set_device_info(0,
	                str_type,
	                pt_this->s_brd_name,
	                pt_this->s_model_name,
	                pt_this->s_codeset);

	            /*turn off TV speaker*/
                a_cfg_av_get(ui2_id, &i2_val);
                ui2_aud_out_mask = (UINT16)i2_val;

                if( (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) )
                {
                    /* Off */
                    ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

                    a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
                    a_cfg_av_update(ui2_id);
                }

            	/* set audio ctrl flag to AUD_CONTROL_EXTERNAL */
				a_cfg_custom_set_vol_control(1);

				/* set sb_enable and sb codeset */
            	a_tv_net_custom_set_soundbar_flag(TRUE);
				a_tv_net_custom_set_soundbar_codeset(pt_this->s_codeset);

            }
        }
        else
        {
			if(pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
			{
				c_strncpy(str_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_DB_NAME_LEN_MAX);
			}
			else
			{
				c_strncpy(str_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_DB_NAME_LEN_MAX);
			}

           c_memset(pt_this->s_codeset, 0, 6);

            if (b_is_src_id_valid)
            {
                a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
                str_type,
                pt_this->s_brd_name,
                pt_this->s_model_name,
                pt_this->s_codeset);
            }
            else
            {
                a_cfg_custom_set_device_info(0,
                str_type,
                pt_this->s_brd_name,
                pt_this->s_model_name,
                pt_this->s_codeset);
            }

        }

        if (NULL != pt_this->pt_codeset->c_codeset1)
        {
            pt_this->ui1_codeset_num ++;
        }

        if (NULL != pt_this->pt_codeset->c_codeset2)
        {
            pt_this->ui1_codeset_num ++;
        }


        if (pt_tag_query_info->b_is_to_clean)
        {
            a_dev_db_reset_bmc_query_info(pt_tag_query_info);
        }

		if (pt_this->ui1_codeset_num < MENU_SETUP_CODESET_SUPPORT_MAX)
		{
	        c_wgl_enable(pt_this->t_remote_code.h_try_next_btn, FALSE);
        }
        else
        {
            c_wgl_enable(pt_this->t_remote_code.h_try_next_btn, TRUE);
        }

        pt_this->ui1_cur_code_pos ++;
        _menu_add_new_device_confirm_code_chang_lang(TRUE);
        pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
        _add_new_device_page_show_subpage(TRUE);
        pt_this->b_is_codeset_querying = FALSE;
#ifdef APP_UEI_SPINNER_SUPPORT
		/*hide spinner after get codeset for confirm remote conection page*/
		_add_device_animation_stop();
		DBG_INFO(("\n####%s(%d)get codese sucess\n",__FUNCTION__,__LINE__));
#endif
    }

	if (DEV_DB_THREAD_QUERY_CODESET_WITH_BRD == pt_tag_query_info->e_query_type)
    {
		UINT8                                     ui1_src_idx;
        ISL_REC_T                                 t_isl_rec;
        CHAR                                      str_type[DEV_DB_NAME_LEN_MAX+1]="";
        BOOL                                      b_is_src_id_valid = FALSE;
		c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

        i4_ret = a_dev_db_get_codeset_list(&(pt_this->pt_codeset_list));
		pt_this->ui1_codeset_num = pt_this->pt_codeset_list->t_codeset_list1.i4_length + pt_this->pt_codeset_list->t_codeset_list2.i4_length;
        pt_this->ui1_cur_code_pos = 0;
        DBG_INFO(("%s(%d)[menu_dev_db] a_dev_db_get_codeset_list(), i4_ret[%d]!,pt_this->ui1_codeset_num=%d,\n",__FUNCTION__,__LINE__,i4_ret,pt_this->ui1_codeset_num));

        _menu_add_new_device_list_codeset(pt_this->ui1_cur_code_pos);	/*get the pt_this->codeset of index =0*/
		i4_ret = _menu_add_new_device_setup_save_and_upload_codeset(pt_this->ui1_cur_code_pos);
		DBG_INFO(("%s(%d)[menu_dev_db] _menu_add_new_device_setup_save_and_upload_codeset(), i4_ret[%d]!,pt_this->ui1_cur_code_pos=%d,pt_this->s_codeset=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->ui1_cur_code_pos,pt_this->s_codeset));

        if (pt_tag_query_info->b_is_to_clean)
		{
			a_dev_db_reset_bmc_query_info(pt_tag_query_info);

			/*free the codeset list*/
			a_dev_db_clean_codeset_list();
		}

        if (pt_this->ui1_select_input != 0xFF)
        {
            ui1_src_idx = pt_this->aui1_input_src_id[pt_this->ui1_select_input];
            a_isl_get_rec_by_idx(ui1_src_idx, &t_isl_rec);
            b_is_src_id_valid = TRUE;
        }
        else
        {
            b_is_src_id_valid = FALSE;
        }

		if(pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
		{
			if(pt_this->ui1_cur_code_pos < pt_this->pt_codeset_list->t_codeset_list1.i4_length)
			{
				c_strncpy(str_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_DB_NAME_LEN_MAX);
			}
			else
			{
				c_strncpy(str_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_DB_NAME_LEN_MAX);
			}
		}
		else
		{
			c_strncpy(str_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_DB_NAME_LEN_MAX);
		}

        if (b_is_src_id_valid)
        {
			a_tv_net_custom_set_codeset(pt_this->s_codeset);
            a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
            str_type,
            pt_this->s_brd_name,
            pt_this->s_model_name,
            pt_this->s_codeset);
        }
        else
        {
            UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
            UINT16  ui2_aud_out_mask;
            INT16   i2_val;

            /*turn off TV speaker*/
            a_cfg_av_get(ui2_id, &i2_val);
            ui2_aud_out_mask = (UINT16)i2_val;

            if( (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) )
            {
                /* Off */
                ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

                a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
                a_cfg_av_update(ui2_id);
            }
        	/* set audio ctrl flag to AUD_CONTROL_EXTERNAL */
			a_cfg_custom_set_vol_control(1);

			/* set sb_enable and sb codeset */
        	a_tv_net_custom_set_soundbar_flag(TRUE);
			a_tv_net_custom_set_soundbar_codeset(pt_this->s_codeset);

            a_cfg_custom_set_device_info(0,
            str_type,
            pt_this->s_brd_name,
            pt_this->s_model_name,
            pt_this->s_codeset);
        }
        if (pt_this->ui1_codeset_num < MENU_SETUP_CODESET_SUPPORT_MAX)
		{
	        c_wgl_enable(pt_this->t_remote_code.h_try_next_btn, FALSE);
        }
        else
        {
            c_wgl_enable(pt_this->t_remote_code.h_try_next_btn, TRUE);
        }
        pt_this->ui1_cur_code_pos ++;
        _menu_add_new_device_confirm_code_chang_lang(TRUE);
        pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
        _add_new_device_page_show_subpage(TRUE);
        pt_this->b_is_codeset_querying = FALSE;
#ifdef APP_UEI_SPINNER_SUPPORT
		/*hide spinner after get codeset for confirm remote conection page*/
		_add_device_animation_stop();
		DBG_INFO(("\n####%s(%d)get codese sucess\n",__FUNCTION__,__LINE__));
#endif
    }

    if ((b_need_to_update_brd_ui)
        || (b_need_to_update_mdl_ui))
    {
        /* updater the brd info to the drop down list*/
        _menu_add_new_device_update_dropdown_list();
    }
    else
    {
        /* do nothing*/
    }

    return;
}

/*-----------------------------------------------------------------------------
  Description:_menu_add_new_device_dev_db_local_query
  input:
  output:
  return:
----------------------------------------------------------------------------*/
VOID  _menu_add_new_device_dev_db_local_query(VOID* pv_tag, VOID* pv_nfy_param)
{

    /*post a message to itself*/
    menu_request_context_switch(_menu_add_new_device_dev_db_local_query_hdlr,
                               (VOID*)pv_tag,
                               (VOID*)pv_nfy_param,
                               NULL);
    return;
}

/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_edit_box_create
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
static INT32 _menu_add_new_device_edit_box_create(HANDLE_T  h_parent,
                                     UINT32               ui4_top,
                                     UINT32               ui4_left_inset,
                                     UINT32               ui4_right_inset,
                                     UINT32               ui4_style,
                                     wgl_widget_proc_fct  pf_wdgt_proc,
                                     HANDLE_T*            ph_widget)
{
    INT32                       i4_ret = MENUR_OK;
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;
    GL_RECT_T                   t_rect;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    /* underline */
    UTF16_T                     w2s_cursor =(UTF16_T) 0x005F;

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      MENU_ADD_NEW_DEVICE_EB_X,
                      ui4_top,
                      MENU_ADD_NEW_DEVICE_EB_W,
                      MENU_ADD_NEW_DEVICE_EB_H);

    /* create editbox */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 //WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = ui4_left_inset;
    t_inset.i4_right    = ui4_right_inset;
    t_inset.i4_top      = MENU_ADD_NEW_DEVICE_EB_TOP_INSET;
    t_inset.i4_bottom   = MENU_ADD_NEW_DEVICE_EB_BOTTOM_INSET;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);

    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Cnt Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left = 10;
    t_inset.i4_right = 60;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);

    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);

    /* Set txt color */
    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_ENABLE_CURSOR_HT,
                           WGL_PACK (TRUE),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_SET_CURSOR_CHAR,
                           (VOID*)(&w2s_cursor),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_EB_CURSOR),
                           WGL_PACK(& t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

     /* Set background images */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_g_menu_img_item_edit;
    t_img_info.u_img_data.t_standard.t_highlight    = h_g_menu_img_item_edit_hlt;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_menu_img_item_edit_disable;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));

    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS));

    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Char support */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_CHAR_SUPPORT),
                          WGL_PACK(WGL_EB_CHAR_SUPPORT));

    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(MENU_ADD_NEW_DEVICE_INPUT_MAX_LEN + 1)),
                          NULL);



    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));

    t_eb_key_map.ui4_backsapce = BTN_KB_BACKSPACE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);

    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style  = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font     = t_fnt_info;
    t_title_info.t_rc_ref   = t_rect;
    t_title_info.ui1_align  = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_icon_create
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
static INT32 _menu_add_new_device_icon_create(HANDLE_T     h_parent,
	                                       	  HANDLE_T*    ph_widget)
{
    INT32                       i4_ret = MENUR_OK;
    WGL_IMG_INFO_T              t_img_info;
    GL_RECT_T                   t_rect;

    SET_RECT_BY_SIZE(&t_rect,
                     400-MENU_ADD_NEW_DEVICE_EB_RIGHT_INSET-77+8,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_Y+1+25,
                     77,
                     61 );

	i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_widget);
    MENU_LOG_ON_FAIL(i4_ret);

	 /* set image */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable = h_g_menu_img_Text_clear_all;
    t_img_info.u_img_data.t_extend.t_disable = h_g_menu_img_Text_clear_all;
    t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_img_Text_clear_all_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_Text_clear_all;
    t_img_info.u_img_data.t_extend.t_push = h_g_menu_img_Text_clear_all;
    t_img_info.u_img_data.t_extend.t_push_unhighlight = h_g_menu_img_Text_clear_all;

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) ));

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL));

    i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
* Name: _menu_add_new_device_drop_down_lb_update
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
static INT32 _menu_add_new_device_drop_down_lb_update( BOOL b_repaint )
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32                                   i4_ret  = MENUR_OK;
    UTF16_T                                 w2s_text[DEV_DB_NAME_LEN_MAX+1]=L"";
    CHAR                                    str_prefix[DEV_DB_NAME_LEN_MAX+1]="";

#ifndef WZD_DEV_SETUP_SHOW_BM_LIST_AS_PREFIX_NULL
    BOOL                                   b_is_visible = FALSE;
#endif

    DBG_API(("\n[####%s(%d)] drop down listbox update\n", __FUNCTION__,__LINE__));

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list, WGL_CMD_LB_DEL_ALL, NULL, NULL));

    if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
    {
        MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_this->t_select_brd.h_brand_vkb,
                            VKB_CMD_GET_EB_CONTENT,
                            (VOID*)(w2s_text),
                            (VOID*)(DEV_DB_NAME_LEN_MAX)));
    }
    else if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
    {
        MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_this->t_select_model.h_model_vkb,
                            VKB_CMD_GET_EB_CONTENT,
                            (VOID*)(w2s_text),
                            (VOID*)(DEV_DB_NAME_LEN_MAX)));
    }
    c_uc_w2s_to_ps(w2s_text, str_prefix, DEV_DB_NAME_LEN_MAX);

#ifndef WZD_DEV_SETUP_SHOW_BM_LIST_AS_PREFIX_NULL
    if (c_strcmp(str_prefix, "") == 0)
    {
        if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
        {
             pt_this->ui4_brd_sel_idx = DEV_DB_DUL_OP_MAX;

             /* set the glob query prefix for brand*/
             c_strncpy(pt_this->c_brd_pfx, str_prefix, DEV_DB_NAME_LEN_MAX);
        }
        else if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
        {
             pt_this->ui4_mdl_sel_idx = DEV_DB_DUL_OP_MAX;

             /* set the glob query prefix for brand*/
             c_strncpy(pt_this->c_mdl_pfx, str_prefix, DEV_DB_NAME_LEN_MAX);
        }

         /* hide drop down list */
        c_wgl_get_visibility(pt_this->t_drop_down_lst.h_drop_down_list, &b_is_visible);

        if(b_is_visible)
        {
            MENU_LOG_ON_FAIL (c_wgl_set_visibility(pt_this->t_drop_down_lst.h_drop_down_frm, WGL_SW_HIDE_RECURSIVE));
            MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->t_drop_down_lst.h_drop_down_frm, NULL, FALSE));
        }
        return MENUR_OK;
    }
#endif
    if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
    {
        /* reset the glob brand info*/
        _add_new_device_page_reset_brand_info();
#ifdef APP_UEI_SPINNER_SUPPORT
        /*hide the spinner before update brand info(insert new query task) if the spinner is show*/
		_add_device_animation_stop();
		DBG_INFO(("\n####%s(%d)HIDE animation lb update\n",__FUNCTION__,__LINE__));
#endif
        /* set the glob query prefix for brand*/
        c_strncpy(pt_this->c_brd_pfx, str_prefix, DEV_DB_NAME_LEN_MAX);
        pt_this->ui4_brd_notify_count = 0;

        i4_ret = a_dev_db_update_brand_info(pt_this->ui4_type_sel_idx,
                                          pt_this->t_dev_type[pt_this->ui4_type_sel_idx],
                                          str_prefix);

        if (MENUR_OK != i4_ret)
        {
            DBG_ERROR(("[####%s(%d)] a_dev_db_update_brand_info(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));
        }
    }
    else if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
    {
        /* reset the glob model info*/
        _add_new_device_page_reset_model_info();

        /* set the glob query prefix for brand*/
        c_strncpy(pt_this->c_mdl_pfx, str_prefix, DEV_DB_NAME_LEN_MAX);

        pt_this->ui4_mdl_notify_count = 0;

        i4_ret = a_dev_db_update_model_info(pt_this->ui4_type_sel_idx,
                                          pt_this->t_dev_type[pt_this->ui4_type_sel_idx],
                                          pt_this->t_brd_info[pt_this->ui4_brd_sel_idx],
                                          pt_this->s_brd_name,
                                          pt_this->c_mdl_pfx);

        if (MENUR_OK != i4_ret)
        {
            DBG_ERROR(("[####%s(%d)] a_dev_db_update_model_info(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));
        }
    }

    MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_down_icon, WGL_SW_HIDE));
    MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_up_icon, WGL_SW_HIDE));
    MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_drop_down_lst.h_drop_down_frm, WGL_SW_HIDE_RECURSIVE));

    if (b_repaint)
    {
        MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->t_drop_down_lst.h_drop_down_frm, NULL, TRUE));
    }

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_create_btn_widget
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_create_btn_widget(
                            HANDLE_T                    h_parent,
                            UTF16_T*                    ws_text,
                            const GL_RECT_T*            pt_rect,
                            const WGL_COLOR_INFO_T*     pt_color_info_fg,
                            const WGL_FONT_INFO_T*      pt_font,
                            WGL_HIMG_TPL_T              t_img_tpl_ht,
                            WGL_HIMG_TPL_T              t_img_tpl_un_ht,
                            UINT8                       ui1_align,
                            wgl_widget_proc_fct         pf_wdgt_proc,
                            HANDLE_T*                   ph_btn,
                            WGL_INSET_T*                pt_inset)
{
    WGL_IMG_INFO_T              t_img_info;

    MENU_LOG_ON_FAIL (c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_btn));

    /*foreground color*/
    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_btn,
                             WGL_CMD_GL_SET_COLOR,
                             WGL_PACK(WGL_CLR_TEXT),
                             WGL_PACK(pt_color_info_fg)));

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(
                        *ph_btn,
                        WGL_CMD_BTN_SET_ALIGN,
                        WGL_PACK(ui1_align),
                        NULL));


    /*content inset*/
    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_btn,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(pt_inset),
                           NULL));


    /*font*/
    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_btn, WGL_CMD_GL_SET_FONT, (VOID*)pt_font, NULL));

    /*text*/
    if(ws_text)
    {
        MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_btn, WGL_CMD_BTN_SET_TEXT, WGL_PACK(ws_text), WGL_PACK((UINT16)0xFFFF)));
    }

    /* background image */
    /*set image*/
    t_img_info.e_type                                   = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable            = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_enable             = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_highlight          = t_img_tpl_ht;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_push               = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = t_img_tpl_un_ht;

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_btn, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK), WGL_PACK(&t_img_info)));

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_create_drop_down_lb
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_create_drop_down_lb(
                        HANDLE_T                h_parent,
                        GL_RECT_T*              pt_rect,
                        wgl_widget_proc_fct     pf_wdgt_proc,
                        UINT16                  ui2_max_elem_num,
                        HANDLE_T *              ph_widget)
{
    INT32                       i4_ret;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem_info;
    CHAR*                       s_font_name = menu_font_name();

    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_max_text_len = MENU_ADD_NEW_DEVICE_LB_TEXT_LENGTH;
    at_cols[0].ui2_width        = 230;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH | WGL_STL_LB_NO_WRAP_OVER;
    t_lb_init.ui2_max_elem_num  = ui2_max_elem_num;
    t_lb_init.ui2_elem_size     = 34;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
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
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Font */
    c_strcpy (t_fnt_info.a_c_font_name, s_font_name);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_FONT,
        WGL_PACK((UINT16)0),
        WGL_PACK(&t_fnt_info));

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Inset */
    t_inset.i4_left   = MENU_ADD_NEW_DEVICE_LB_CNT_INSET_L;
    t_inset.i4_right  = MENU_ADD_NEW_DEVICE_LB_CNT_INSET_R;
    t_inset.i4_top    = MENU_ADD_NEW_DEVICE_LB_CNT_INSET_T;
    t_inset.i4_bottom = MENU_ADD_NEW_DEVICE_LB_CNT_INSET_B;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_CNT_INSET,
        WGL_PACK(&t_inset),
        NULL);

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Inset */
    t_inset.i4_left   = MENU_ADD_NEW_DEVICE_LB_ELE_INSET_L;
    t_inset.i4_right  = MENU_ADD_NEW_DEVICE_LB_ELE_INSET_R;
    t_inset.i4_top    = MENU_ADD_NEW_DEVICE_LB_ELE_INSET_T;
    t_inset.i4_bottom = MENU_ADD_NEW_DEVICE_LB_ELE_INSET_B;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_ELEM_INSET,
        WGL_PACK(&t_inset),
        NULL);

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_inset.i4_left   = MENU_ADD_NEW_DEVICE_EB_LEFT_INSET + 6;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_INSET,
        WGL_PACK((UINT16)0),
        WGL_PACK(&t_inset));

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set column color: channel number, text color . */
    t_color_elem.t_normal            = t_g_menu_color_white;
    t_color_elem.t_disable           = t_g_menu_color_white;
    t_color_elem.t_highlight         = t_g_menu_color_white;
    t_color_elem.t_highlight_unfocus = t_g_menu_color_white;
    t_color_elem.t_pushed            = t_g_menu_color_white;
    t_color_elem.t_selected          = t_g_menu_color_white;
    t_color_elem.t_selected_disable  = t_g_menu_color_white;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_COLOR,
        WGL_PACK_2 (0, WGL_CLR_TEXT), /* text color */
        WGL_PACK (& t_color_elem));

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set column color: channel number, bk color . */
    t_color_elem.t_normal            = t_g_menu_color_transp;
    t_color_elem.t_disable           = t_g_menu_color_transp;
    t_color_elem.t_highlight         = t_g_menu_color_transp;
    t_color_elem.t_highlight_unfocus = t_g_menu_color_transp;
    t_color_elem.t_pushed            = t_g_menu_color_transp;
    t_color_elem.t_selected          = t_g_menu_color_transp;
    t_color_elem.t_selected_disable  = t_g_menu_color_transp;

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_ELEM_COLOR,
        WGL_PACK(WGL_CLR_BK),
        WGL_PACK (& t_color_elem));

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_do_cmd (*ph_widget,
        WGL_CMD_LB_SET_COL_COLOR,
        WGL_PACK_2 (0, WGL_CLR_BK), /* background */
        WGL_PACK (& t_color_elem));

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* set elem background image*/
    t_img_elem_info.h_normal             = NULL_HANDLE;
    t_img_elem_info.h_selected           = NULL_HANDLE;
    t_img_elem_info.h_disable            = NULL_HANDLE;
    t_img_elem_info.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem_info.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem_info.h_pushed             = NULL_HANDLE;
    t_img_elem_info.h_selected_disable   = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                       WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                       WGL_PACK(&t_img_elem_info),
                       NULL);

    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_select_brd_set_text
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
static INT32 _menu_add_new_device_select_brd_set_text(UINT32 ui4_index, BOOL b_repaint )
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UTF16_T                         w2s_brand_name[32] = {0};

    if (ui4_index > (MENU_ADD_NEW_DEVICE_BRAND_IDS_MAX_NUM - 1))    /*Klocwork*/
	{
        DBG_ERROR(("[####%s(%d)]  brd_sel_idx = %d\n", __FUNCTION__,__LINE__, ui4_index));
        return MENUR_FAIL;
    }

	MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_this->t_select_brd.h_brand_vkb,
                            VKB_CMD_CLEAR_TEXT,
                            (VOID*) NULL,
                            (VOID*) NULL));

    c_uc_ps_to_w2s(pt_this->t_brd_info[ui4_index].s_src_name, w2s_brand_name, 31);

	/* set initial editbox text */
    a_vkb_do_cmd (pt_this->t_select_brd.h_brand_vkb,
              VKB_CMD_SET_INITIAL_TEXT,
              (VOID*) w2s_brand_name,
              (VOID*) 0xFF);

    if( b_repaint )
    {
        MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->h_cnt_frm, NULL, TRUE));
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_select_model_set_text
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
static INT32 _menu_add_new_device_select_model_set_text(UINT32 ui4_index, BOOL b_repaint )
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UTF16_T                         w2s_model_name[32] = {0};

    if (ui4_index > (MENU_ADD_NEW_DEVICE_BRAND_IDS_MAX_NUM - 1))    /*Klocwork*/
	{
        DBG_ERROR(("[####%s(%d)]  model_sel_idx = %d\n", __FUNCTION__,__LINE__, ui4_index));
        return MENUR_FAIL;
    }

	MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_this->t_select_model.h_model_vkb,
                            VKB_CMD_CLEAR_TEXT,
                            (VOID*) NULL,
                            (VOID*) NULL));

    c_uc_ps_to_w2s(pt_this->t_mdl_info[ui4_index].s_src_name, w2s_model_name, 31);

	/* set initial editbox text */
    a_vkb_do_cmd (pt_this->t_select_model.h_model_vkb,
              VKB_CMD_SET_INITIAL_TEXT,
              (VOID*) w2s_model_name,
              (VOID*) 0xFF);

    if( b_repaint )
    {
        MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->h_cnt_frm, NULL, TRUE));
    }

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_drop_down_lb_proc
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_drop_down_lb_proc(
                 HANDLE_T            h_widget,
                 UINT32              ui4_msg,
                 VOID*               pv_param1,
                 VOID*               pv_param2)
{
    INT32                       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UINT32                      ui4_lst_index = 0;
    UINT32                      ui4_elem_num = 0;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            switch( (UINT32)pv_param1 )
            {
            case BTN_SELECT:
                i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui4_lst_index),
                              NULL);
                if(WGLR_OK != i4_ret)
                {
                    DBG_ERROR(("\n####%s(%d)===WGL_CMD_LB_GET_HLT_INDEX i4_ret=%d===\n",__FUNCTION__,__LINE__, i4_ret));
                    MENU_LOG_ON_FAIL(i4_ret);
                }

				i4_ret = c_wgl_enable(pt_this->h_ok_btn,TRUE);
			    MENU_LOG_ON_FAIL(i4_ret);

                if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
                {

#ifdef APP_UEI_SPINNER_SUPPORT
					/*hide the spinner when select the item from the dropdown list when the spinner is show*/
					_add_device_animation_stop();
					DBG_INFO(("\n####%s(%d)HIDE animation lb proc sel\n",__FUNCTION__,__LINE__));
#endif
                    pt_this->ui4_brd_sel_idx = (UINT8)ui4_lst_index;
                    DBG_INFO(("\n####%s(%d)----ui1_lst_index = %d ui4_brd_sel_idx=%d\n",__FUNCTION__,__LINE__,ui4_lst_index, pt_this->ui4_brd_sel_idx));

                    MENU_LOG_ON_FAIL (_menu_add_new_device_select_brd_set_text(ui4_lst_index, TRUE));

                    i4_ret = c_wgl_set_focus(pt_this->h_ok_btn,
		                                     WGL_SYNC_AUTO_REPAINT);
	                MENU_LOG_ON_FAIL(i4_ret);
                }
                else if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
                {
                    pt_this->ui4_mdl_sel_idx = (UINT8)ui4_lst_index;

                    DBG_INFO(("\n####%s(%d)---------ui1_lst_index = %d ui4_mdl_sel_idx=%d\n",__FUNCTION__,__LINE__,ui4_lst_index, pt_this->ui4_mdl_sel_idx));

                    MENU_LOG_ON_FAIL (_menu_add_new_device_select_model_set_text(ui4_lst_index, TRUE));

                    i4_ret = c_wgl_set_focus(pt_this->h_ok_btn,
		                                     WGL_SYNC_AUTO_REPAINT);
	                MENU_LOG_ON_FAIL(i4_ret);

                }

                MENU_LOG_ON_FAIL (menu_pm_repaint());

                return MENUR_OK;

            case BTN_CURSOR_UP:
                i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui4_lst_index),
                              NULL);
                if(WGLR_OK != i4_ret)
                {
                    MENU_LOG_ON_FAIL(i4_ret);
                }

				i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui4_elem_num),
                                      NULL);
				if(WGLR_OK != i4_ret)
                {
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                if (ui4_lst_index == 0)
                {
                    if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
                    {
                        i4_ret = a_vkb_set_focus_ex(pt_this->t_select_brd.h_brand_vkb);
                    }
                    else if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
                    {
                        i4_ret = a_vkb_set_focus_ex(pt_this->t_select_model.h_model_vkb);
                    }
                    if(WGLR_OK != i4_ret)
                    {
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
					/* hide arrow up icon */
                	MENU_LOG_ON_FAIL (c_wgl_set_visibility(pt_this->t_drop_down_lst.h_up_icon, WGL_SW_HIDE));
					MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->h_cnt_frm, NULL, TRUE));
                    return MENUR_OK;
                }
                if(ui4_elem_num > 3)
				{
					if (ui4_lst_index == 1)
	                {
	                    MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->t_drop_down_lst.h_up_icon, WGL_SW_HIDE));
	                }
					else
					{
						MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->t_drop_down_lst.h_up_icon, WGL_SW_NORMAL));
					}
					MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->t_drop_down_lst.h_down_icon, WGL_SW_NORMAL));
					MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->t_drop_down_lst.h_drop_down_frm, NULL, TRUE));
				}

                break;

            case BTN_CURSOR_DOWN:
                i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui4_lst_index),
                              NULL);
                if(WGLR_OK != i4_ret)
                {
                    MENU_LOG_ON_FAIL(i4_ret);
                }

				i4_ret = c_wgl_do_cmd(pt_this->t_drop_down_lst.h_drop_down_list,
                                      WGL_CMD_LB_GET_ELEM_NUM,
                                      WGL_PACK(&ui4_elem_num),
                                      NULL);
				if(WGLR_OK != i4_ret)
                {
                    MENU_LOG_ON_FAIL(i4_ret);
                }

				if (ui4_lst_index == (ui4_elem_num - 1))
                {
					if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
	                {
	                    i4_ret = a_vkb_set_focus(pt_this->t_select_brd.h_brand_vkb);
	                }
	                else if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
	                {
	                    i4_ret = a_vkb_set_focus(pt_this->t_select_model.h_model_vkb);

	                }
	                if(WGLR_OK != i4_ret)
                    {
                        MENU_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        MENU_LOG_ON_FAIL(menu_pm_repaint());
                        return MENUR_OK;
                    }

                }
				if(ui4_elem_num > 3)
				{
					if (ui4_lst_index == (ui4_elem_num - 2))
	                {
	                    MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->t_drop_down_lst.h_down_icon, WGL_SW_HIDE));
	                }
					else
					{
						MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->t_drop_down_lst.h_down_icon, WGL_SW_NORMAL));
					}
					MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->t_drop_down_lst.h_up_icon, WGL_SW_NORMAL));
					MENU_LOG_ON_FAIL (c_wgl_repaint (pt_this->t_drop_down_lst.h_drop_down_frm, NULL, TRUE));
				}
                break;
            case BTN_RETURN:
            {
				if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
                {
                    a_vkb_set_focus(pt_this->t_select_brd.h_brand_vkb);
                }
                else if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
                {
                    a_vkb_set_focus(pt_this->t_select_model.h_model_vkb);
                }
                menu_pm_repaint();
                return MENUR_OK;
            }

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

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_drop_down_up_btn_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_drop_down_up_btn_nfy (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  /* */
        {
            c_wgl_set_focus(pt_this->t_drop_down_lst.h_drop_down_list, TRUE);
        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /*  */
        {
            return MENUR_OK;
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_page_tv_remote_device_setup_drop_down_down_btn_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_drop_down_down_btn_nfy (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_UP == (UINT32)pv_param1 )  /*  */
        {
            c_wgl_set_focus(pt_this->t_drop_down_lst.h_drop_down_list, TRUE);
        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /* */
        {
            return MENUR_OK;
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_drop_down_lst_create
 *
 * Description:includ:drop down frm/drop down list box/up icon/down icon
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_drop_down_lst_create(HANDLE_T  h_parent,
    MENU_DROP_DOWN_LIST_T*   pt_drop_down_lst)
{
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      0,
                      MENU_ADD_NEW_DEVICE_BRD_FRM_Y + 44+25,
                      400,
                      140 );

    /* create widget for drop down frm create */
    MENU_LOG_ON_FAIL (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     NULL,
                                     NULL,
                                     & pt_drop_down_lst->h_drop_down_frm));

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    =t_g_menu_color_title_bk;
    t_clr_info.u_color_data.t_standard.t_highlight =t_g_menu_color_title_bk;
    t_clr_info.u_color_data.t_standard.t_disable   =t_g_menu_color_title_bk;

    MENU_LOG_ON_FAIL ( c_wgl_do_cmd(pt_drop_down_lst->h_drop_down_frm,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info )));

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     400,
                     12 );

    MENU_LOG_ON_FAIL (c_wgl_create_widget(pt_drop_down_lst->h_drop_down_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _menu_add_new_device_drop_down_up_btn_nfy,
                                 255,
                                 NULL,
                                 NULL,
                                 &pt_drop_down_lst->h_up_icon));

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(pt_drop_down_lst->h_up_icon,
                          WGL_CMD_BTN_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL));

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable = h_g_menu_img_arrow_up;//hs_nali
    t_img_info.u_img_data.t_extend.t_disable = h_g_menu_img_arrow_up;
    t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_img_arrow_up;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_arrow_up;
    t_img_info.u_img_data.t_extend.t_push = h_g_menu_img_arrow_up;
    t_img_info.u_img_data.t_extend.t_push_unhighlight = h_g_menu_img_arrow_up;
    MENU_LOG_ON_FAIL (c_wgl_do_cmd(pt_drop_down_lst->h_up_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) ));

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     140-12,
                     400,
                     12);

    MENU_LOG_ON_FAIL (c_wgl_create_widget(pt_drop_down_lst->h_drop_down_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _menu_add_new_device_drop_down_down_btn_nfy,
                                 255,
                                 NULL,
                                 NULL,
                                 &pt_drop_down_lst->h_down_icon));

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(pt_drop_down_lst->h_down_icon,
                          WGL_CMD_BTN_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL));

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable = h_g_menu_img_arrow_down;//hs_nali
    t_img_info.u_img_data.t_extend.t_disable = h_g_menu_img_arrow_down;
    t_img_info.u_img_data.t_extend.t_highlight = h_g_menu_img_arrow_down;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_arrow_down;
    t_img_info.u_img_data.t_extend.t_push = h_g_menu_img_arrow_down;
    t_img_info.u_img_data.t_extend.t_push_unhighlight = h_g_menu_img_arrow_down;

    MENU_LOG_ON_FAIL (c_wgl_do_cmd(pt_drop_down_lst->h_down_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) ));

	/*drop down list box*/
    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     12+5,
                     400,
                     140-12-15-5);

    MENU_LOG_ON_FAIL (_menu_add_new_device_create_drop_down_lb(pt_drop_down_lst->h_drop_down_frm,
                &t_rect,
                _menu_add_new_device_drop_down_lb_proc,
                128,
                &pt_drop_down_lst->h_drop_down_list));


    /* set visibility */
    MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_drop_down_lst->h_drop_down_frm, WGL_SW_HIDE_RECURSIVE));

    return  MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _backbar_cursor_down_handler
 *
 * Description:_backbar_cursor_down_handler
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _backbar_cursor_down_handler(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    switch (pt_this->e_subpage)
    {
        case ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN:
        {
            BOOL    b_is_visible = FALSE;
            c_wgl_get_visibility(pt_this->h_list_item_device_type_aud, &b_is_visible);
            if (b_is_visible == TRUE)
            {
                i4_ret = c_wgl_set_focus(pt_this->h_list_item_device_type_aud,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_set_focus(pt_this->h_list_item_device_type,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_INPUT_LIST:
        {
            i4_ret = c_wgl_set_focus(pt_this->h_subpage_input,
                                     WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE:
        {
            i4_ret = c_wgl_set_focus(pt_this->h_subpage_device_type,
                                     WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE_AUD:
        {
            i4_ret = c_wgl_set_focus(pt_this->h_subpage_device_type_aud,
                                     WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND:
        {
            i4_ret = a_vkb_set_focus_ex(pt_this->t_select_brd.h_brand_vkb);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = menu_pm_repaint();
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL:
        {
            i4_ret = a_vkb_set_focus_ex(pt_this->t_select_model.h_model_vkb);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = menu_pm_repaint();
            MENU_LOG_ON_FAIL(i4_ret);
        }
            break;
		case ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT:
        {
            i4_ret = c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn,
                             WGL_SYNC_AUTO_REPAINT);
		    MENU_LOG_ON_FAIL(i4_ret);
        }
            break;

        default:
        {
            DBG_INFO(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
            break;
        }
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _add_new_device_page_backbar_proc_fct
 *
 * Description:_add_new_device_page_backbar_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _add_new_device_page_backbar_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
		if((pt_this->e_subpage != ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
			&&(pt_this->e_subpage != ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL))
		{
	        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
        }
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
        #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = _back_key_handler();
                MENU_LOG_ON_FAIL(i4_ret);

                menu_set_power_off_flag(FALSE);

                return i4_ret;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = _backbar_cursor_down_handler();
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break ;

            case BTN_CURSOR_UP:
            {
                i4_ret = menu_set_focus_on_homebar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*-----------------------------------------------------------------------------
 * Name: _add_new_device_page_homebar_proc_fct
 *
 * Description:_add_new_device_page_homebar_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_homebar_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
		if((pt_this->e_subpage != ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
			&&(pt_this->e_subpage != ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL))
		{
	        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
        }
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  i4_ret = MENUR_OK;

        switch ((UINT32)param1)
        {
            case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
        #endif
            case BTN_SELECT:
            case BTN_RETURN:
            {
                i4_ret = menu_device_page_nav_go(NAV_ROOT_MENU_FROM_ANY_PAGE,
                                                 NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                return MENUR_OK;
            }

            case BTN_CURSOR_DOWN:
            {
                i4_ret = menu_set_focus_on_backbar(TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
            }
                break;

            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}
/*-----------------------------------------------------------------------------
 * Name: _list_item_input_src_show
 *
 * Description:_list_item_input_src_show
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_input_src_show(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UTF16_T     w2s_input[10] = {0};
    ISL_REC_T		t_isl_rec;
    UINT8		ui1_rec_idx = 0;
    UINT8		ui1_comp_idx = 0;
    UINT8		ui1_i = 0;
    UINT8		ui1_rec_num = 0;

    if(pt_this->ui1_select_input == 0xFF)
	    return 0;
    menu_list_chg_lang(pt_this->h_list_item_input_src,
                        MLM_MENU_KEY_PICK_INPUT_SOURCE, 0, 0);

    a_isl_get_num_rec(&ui1_rec_num);
    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

    /* Iterate all the input sources */
    while ((ui1_rec_idx < ui1_rec_num)&&
           (ui1_rec_idx < sizeof(pt_this->aui1_input_src_id)/sizeof(UINT8)))
    {
        a_isl_get_rec_by_idx(ui1_rec_idx, &t_isl_rec);

		 /*the input source is hdmi*/
        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_AV) &&
            (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI))
        {
            pt_this->aui1_input_src_id[ui1_i] = ui1_rec_idx;
            ui1_i++;
        }

        /*the input source is comp*/
        if(( DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type )||
	       (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type))
        {
	       ui1_comp_idx = ui1_rec_idx;
        }
        ui1_rec_idx++;
    }
    pt_this->aui1_input_src_id[ui1_i] = ui1_comp_idx;	/*the last item is comp*/

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    a_isl_get_rec_by_idx(pt_this->aui1_input_src_id[pt_this->ui1_select_input], &t_isl_rec);
    c_uc_w2s_strncpy(w2s_input, a_isl_get_display_name(&t_isl_rec), c_uc_w2s_strlen(a_isl_get_display_name(&t_isl_rec)));

    menu_list_set_text(pt_this->h_list_item_input_src,
                       0,
                       w2s_input);

    menu_list_set_idx(pt_this->h_list_item_input_src, 0);
    menu_list_adjust_rect(pt_this->h_list_item_input_src);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _list_item_device_type_show
 *
 * Description:_list_item_device_type_show
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_type_show(VOID)
{
    INT32									i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
    UTF16_T     							w2s_device_type[32+1] = {0};
    DEV_DB_DEV_TYPE_CTGY_T  				e_dev_type_category = DEV_DB_DEV_TYPE_CTGY_NONE;

	i4_ret = a_dev_db_get_dev_type_category(&e_dev_type_category);
	if (MENUR_OK != i4_ret)
	{
		DBG_ERROR(("\n####%s(%d)a_dev_db_get_dev_type_category [return %d]\n",__FUNCTION__,__LINE__,i4_ret));
	}

	i4_ret = a_cfg_get_gui_lang(pt_this->crn_s639_lang);
	if (MENUR_OK != i4_ret)
	{
		DBG_ERROR(("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->crn_s639_lang));
	}
	if((e_dev_type_category != DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX)||(c_strncmp(pt_this->crn_s639_lang, pt_this->pre_s639_lang, ISO_639_LANG_LEN) != 0))
	{
	    i4_ret = a_dev_db_update_dev_type(DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX);

	    if (MENUR_OK != i4_ret)
	    {
	        DBG_ERROR(("[####%s(%d)] a_dev_db_update_dev_type() i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	        return MENUR_FAIL;
	    }

	    c_strncpy(pt_this->pre_s639_lang, pt_this->crn_s639_lang, ISO_639_LANG_LEN);
		DBG_INFO(("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->pre_s639_lang=%s,pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->pre_s639_lang,pt_this->crn_s639_lang));

    }

    i4_ret = a_dev_db_get_dev_type_ex(pt_this->t_dev_type,&(pt_this->ui4_type_num));

    if (MENUR_OK != i4_ret)
    {
        DBG_ERROR(("[####%s(%d)] a_dev_db_get_dev_type_ex() i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        return MENUR_FAIL;
    }

    if (pt_this->ui4_type_num > DEV_DB_DEV_TYPE_DEF_NUM)
    {
        DBG_ERROR(("[####%s(%d)] dev type num is invalid !!\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }

    menu_list_chg_lang(pt_this->h_list_item_device_type,
                        MLM_MENU_KEY_PICK_DEVICE_TYPE, 0, 0);

    if (DEVICE_TYPE_UNKNOWN == pt_this->ui4_type_sel_idx)
    {
        c_uc_w2s_strcpy(w2s_device_type, MENU_TEXT(MLM_MENU_KEY_DEVICE_TYPE_NONE));
    }
    else
    {
        if(pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg!=NULL)
        {
	        c_uc_w2s_strncpy(w2s_device_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, 32);
        }
    }

    menu_list_set_text(pt_this->h_list_item_device_type,
                       0,
                       w2s_device_type);

    menu_list_set_idx(pt_this->h_list_item_device_type, 0);
    menu_list_adjust_rect_ex(pt_this->h_list_item_device_type);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _list_item_device_type_aud_show
 *
 * Description: show the list item of audio type (audio receiver/amplifier and sound bar)
 *				from select MENU->Audio->Audio device setup
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_type_aud_show(VOID)
{
    INT32									i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
    UTF16_T     							w2s_device_type[32+1] = {0};
    DEV_DB_DEV_TYPE_CTGY_T  				e_dev_type_category = DEV_DB_DEV_TYPE_CTGY_NONE;

	i4_ret = a_dev_db_get_dev_type_category(&e_dev_type_category);
	if (MENUR_OK != i4_ret)
	{
		DBG_ERROR(("\n####%s(%d)a_dev_db_get_dev_type_category [return %d]\n",__FUNCTION__,__LINE__,i4_ret));
	}

	i4_ret = a_cfg_get_gui_lang(pt_this->crn_s639_lang);
	if (MENUR_OK != i4_ret)
	{
		DBG_ERROR(("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->crn_s639_lang));
	}

	if((e_dev_type_category != DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX)||(c_strncmp(pt_this->crn_s639_lang, pt_this->pre_s639_lang, ISO_639_LANG_LEN) != 0))
	{
	    i4_ret = a_dev_db_update_dev_type(DEV_DB_DEV_TYPE_CTGY_ALL_DEV_EX);

	    if (MENUR_OK != i4_ret)
	    {
	        DBG_ERROR(("[####%s(%d)] a_dev_db_update_dev_type() i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	        return MENUR_FAIL;
	    }

	    c_strncpy(pt_this->pre_s639_lang, pt_this->crn_s639_lang, ISO_639_LANG_LEN);
		DBG_INFO(("\n####%s(%d)a_cfg_get_gui_lang [return %d]pt_this->pre_s639_lang=%s,pt_this->crn_s639_lang=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->pre_s639_lang,pt_this->crn_s639_lang));

    }

    i4_ret = a_dev_db_get_dev_type_ex(pt_this->t_dev_type,&(pt_this->ui4_type_num));

    if (MENUR_OK != i4_ret)
    {
        DBG_ERROR(("[####%s(%d)] a_dev_db_get_dev_type_ex() i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        return MENUR_FAIL;
    }

    if (pt_this->ui4_type_num > DEV_DB_DEV_TYPE_DEF_NUM)
    {
        DBG_ERROR(("[####%s(%d)] dev type num is invalid !!\n",__FUNCTION__,__LINE__));
        return MENUR_FAIL;
    }

    menu_list_chg_lang(pt_this->h_list_item_device_type_aud,
                        MLM_MENU_KEY_PICK_DEVICE_TYPE, 0, 0);

    if(pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg!=NULL)
    {
	    c_uc_w2s_strncpy(w2s_device_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, 32);
	}

    menu_list_set_text(pt_this->h_list_item_device_type_aud,
                       0,
                       w2s_device_type);

    menu_list_set_idx(pt_this->h_list_item_device_type_aud, 0);
    menu_list_adjust_rect(pt_this->h_list_item_device_type_aud);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _list_item_device_brand_show
 *
 * Description: _list_item_device_brand_show
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_brand_show(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UTF16_T     w2s_device_brand[32+1] = {0};

    menu_list_chg_lang(pt_this->h_list_item_device_brand,
                        MLM_MENU_KEY_PICK_DEVICE_BRAND, 0, 0);

    c_uc_ps_to_w2s(pt_this->s_brd_name, w2s_device_brand, 32);

    menu_list_set_text(pt_this->h_list_item_device_brand,
                       0,
                       w2s_device_brand);

    menu_list_set_idx(pt_this->h_list_item_device_brand, 0);

    menu_list_adjust_rect(pt_this->h_list_item_device_brand);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _list_item_device_model_show
 *
 * Description: _list_item_device_model_show
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_model_show(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UTF16_T     w2s_device_model[32+1] = {0};

    menu_list_chg_lang(pt_this->h_list_item_device_model,
                        MLM_MENU_KEY_PICK_DEVICE_MODEL, 0, 0);

    c_uc_ps_to_w2s(pt_this->s_model_name, w2s_device_model, 32);

    menu_list_set_text(pt_this->h_list_item_device_model,
                       0,
                       w2s_device_model);

    menu_list_set_idx(pt_this->h_list_item_device_model, 0);
    menu_list_adjust_rect(pt_this->h_list_item_device_model);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _list_item_confirm_remote_connect_show
 *
 * Description: _list_item_confirm_remote_connect_show
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_confirm_remote_connect_show(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

	menu_text_chg_lang(pt_this->h_list_item_confirm_remote_connect,
						MLM_MENU_KEY_AUD_CONTROL_CONFIRM_REMOTE);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _append_input
 *
 * Description: _append_input-->append the input subpage item elem
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _append_input(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    WGL_LB_ITEM_T   at_items[1];
    UTF16_T         w2s_input[10] = {0};
    UINT8			ui1_rec_num = 0;
    UINT8			ui1_rec_idx = 0;
	ISL_REC_T		t_isl_rec;
	UINT8			ui1_i = 0;
	UINT8			ui1_comp_idx=0;

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_input,
                         WGL_CMD_LB_DEL_ALL,
                         NULL,
                         NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    a_isl_get_num_rec(&ui1_rec_num);

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

    /* Iterate all the input sources */

    while ((ui1_rec_idx < ui1_rec_num)&&
           (ui1_rec_idx < sizeof(pt_this->aui1_input_src_id)/sizeof(UINT8)))
    {
        a_isl_get_rec_by_idx(ui1_rec_idx, &t_isl_rec);

		 /*the input source is hdmi*/
        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_AV) &&
            (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI))
        {
            pt_this->aui1_input_src_id[ui1_i] = ui1_rec_idx;

			at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
	        at_items[0].data.pw2s_text  = a_isl_get_display_name(&t_isl_rec);

	        i4_ret = c_wgl_do_cmd(pt_this->h_subpage_input,
	                              WGL_CMD_LB_APPEND_ELEM,
	                              WGL_PACK(at_items),
	                              NULL);
	        MENU_LOG_ON_FAIL(i4_ret);
            ui1_i++;
        }

        /*the input source is comp*/
        if(( DEV_AVC_COMP_VIDEO == t_isl_rec.t_avc_info.e_video_type )||
	       (DEV_AVC_COMBI == t_isl_rec.t_avc_info.e_video_type))
        {
	       ui1_comp_idx = ui1_rec_idx;
		   c_uc_w2s_strncpy(w2s_input, a_isl_get_display_name(&t_isl_rec), c_uc_w2s_strlen(a_isl_get_display_name(&t_isl_rec)));
        }

        ui1_rec_idx++;

    }
    pt_this->aui1_input_src_id[ui1_i] = ui1_comp_idx;	/*the last item is comp*/

	/*append the last item --comp*/
	at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text  = w2s_input;

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_input,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _append_device_type
 *
 * Description: _append_device_type-->append the device type subpage item elem
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _append_device_type(VOID)
{
    INT32       							i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
    WGL_LB_ITEM_T   						at_items[1];
    UINT8           						ui1_idx = 0;
    UTF16_T         						w2s_device_type[32+1] = {0};

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type,
                         WGL_CMD_LB_DEL_ALL,
                         NULL,
                         NULL);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef ENABLE_DEBUG_LOG
    DBG_INFO(("\n<####>%s,%s,%d,ui2_device_type_num=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_this->ui4_type_num));
#endif
	/*the first item is None*/
	c_uc_w2s_strcpy(w2s_device_type, MENU_TEXT(MLM_MENU_KEY_DEVICE_TYPE_NONE));
	at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text  = w2s_device_type;
    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui1_idx=0;
         ui1_idx<pt_this->ui4_type_num;
         ui1_idx++)
    {
        if(pt_this->t_dev_type[ui1_idx].pw2s_txt_msg!=NULL)
        {
	        c_uc_w2s_strncpy(w2s_device_type, pt_this->t_dev_type[ui1_idx].pw2s_txt_msg, 32);
        }

        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = w2s_device_type;

        i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _append_device_type_aud
 *
 * Description: _append_device_type_aud-->append the audio device type subpage item elem
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _append_device_type_aud(VOID)
{
    INT32       							i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
    WGL_LB_ITEM_T   						at_items[1];
    UINT8           						ui1_idx = 0;
    UTF16_T         						w2s_device_type[32+1] = {0};

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type_aud,
                         WGL_CMD_LB_DEL_ALL,
                         NULL,
                         NULL);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef ENABLE_DEBUG_LOG
    DBG_INFO(("\n<####>%s,%s,%d,ui2_device_type_num=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_this->ui4_type_num));
#endif
	/*the first item is None*/

    for (ui1_idx=0; ui1_idx<DEVICE_TYPE_AUD_MAX; ui1_idx++)
    {
        if(pt_this->t_dev_type[ui1_idx+8].pw2s_txt_msg!=NULL)
        {
	        c_uc_w2s_strncpy(w2s_device_type, pt_this->t_dev_type[ui1_idx+8].pw2s_txt_msg, 32);
        }

        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = w2s_device_type;

        i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type_aud,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage_main
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
static INT32 _add_new_device_page_show_subpage_main()
{
	INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    GL_RECT_T   t_rect = {0};
    ADD_NEW_DEVICE_PAGE_ENTER_FROM_T        e_enter_from = ADD_NEW_DEVICE_PAGE_ENTERN_FROM_NORMAL;
    HANDLE_T			                    h_last_shadow_item = NULL_HANDLE;
    UINT8                                   ui1_rec_num = 0;
#ifdef APP_UEI_SPINNER_SUPPORT
	_add_device_animation_stop();
	DBG_INFO(("\n####%s(%d)HIDE animation in main page\n",__FUNCTION__,__LINE__));
#endif

	menu_set_power_off_flag(FALSE);

    /* if the this page is enter from the audio
        *mode setup  should have the audio device
        *been the default select dev type
        */
    menu_device_page_add_new_device_enter_from_get(&e_enter_from);
    DBG_INFO(("\n==menu_device_page_add_new_device_enter_from_get e_enter_from=%d\n",e_enter_from));

	i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_SETUP_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ADD_NEW_DEVICE_PAGE_ENTERN_FROM_AUDIO_MODE_SETUP == e_enter_from)
    {
        pt_this->b_is_type_sel = TRUE;

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_DEVICE_TYPE_AUD_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret=c_wgl_move(pt_this->h_list_item_device_type_aud, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_INPUT_SRC_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_input_src, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_DEVICE_BRAND_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_device_brand, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_DEVICE_MODEL_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_device_model, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_CONFIRM_REMOTE_CONNECT_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_confirm_remote_connect, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_list_item_device_type_aud,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_INPUT_SRC_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_input_src, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_DEVICE_BRAND_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_device_brand, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_DEVICE_MODEL_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_device_model, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         0,
                         MENU_ITEM_V_HEIGHT*(LIST_ITEM_CONFIRM_REMOTE_CONNECT_IDX-1),
                         MENU_ITEM_V_WIDE,
                         MENU_ITEM_V_HEIGHT);
        i4_ret = c_wgl_move(pt_this->h_list_item_confirm_remote_connect, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_this->h_list_item_device_type,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_list_item_input_src,
	                                  WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_list_item_device_brand,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if((pt_this->b_is_type_sel)&&(pt_this->ui4_type_sel_idx != DEVICE_TYPE_UNKNOWN))
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, TRUE);
		MENU_LOG_ON_FAIL(i4_ret);
	}
	else
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, FALSE);
		MENU_LOG_ON_FAIL(i4_ret);
	}

    i4_ret = c_wgl_set_visibility(pt_this->h_list_item_device_model,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

	if((pt_this->b_is_brd_sel)&&(!pt_this->b_is_db_locked)&&!((pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX)&&(c_strcmp(pt_this->s_brd_name, "VIZIO")==0)))
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_model, TRUE);
		MENU_LOG_ON_FAIL(i4_ret);
	}
	else
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_model, FALSE);
		MENU_LOG_ON_FAIL(i4_ret);
	}

	if((pt_this->b_is_mdl_sel)||
		((pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX)&&(c_strcmp(pt_this->s_brd_name, "VIZIO")==0)))
	{
		i4_ret = c_wgl_enable(pt_this->h_list_item_confirm_remote_connect, TRUE);
		MENU_LOG_ON_FAIL(i4_ret);
	}
	else
	{
		i4_ret = c_wgl_enable(pt_this->h_list_item_confirm_remote_connect, FALSE);
		MENU_LOG_ON_FAIL(i4_ret);
	}

    i4_ret = c_wgl_set_visibility(pt_this->h_list_item_confirm_remote_connect,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ADD_NEW_DEVICE_PAGE_ENTERN_FROM_AUDIO_MODE_SETUP == e_enter_from)
    {
        i4_ret = _list_item_device_type_aud_show();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _list_item_device_type_show();
        MENU_LOG_ON_FAIL(i4_ret);
    }


    i4_ret = _list_item_input_src_show();
    MENU_LOG_ON_FAIL(i4_ret);

    a_isl_get_num_rec(&ui1_rec_num);
    if(pt_this->ui4_type_sel_idx == MENU_SETUP_VCR_IDX)
    {
		/*comp*/
    	pt_this->ui1_select_input = ui1_rec_num-2;
		i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    	MENU_LOG_ON_FAIL(i4_ret);
    }
    else if((pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)||(pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX) )
    {
    	i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    	/*record the pre select input*/
    	if(pt_this->ui1_select_input!=0xFF)
	    {
		    pt_this->ui1_pre_select_input = pt_this->ui1_select_input;
		    pt_this->ui1_select_input = 0xFF;
	    }
    	MENU_LOG_ON_FAIL(i4_ret);
    }
	else
	{
		i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, TRUE);
    	MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _list_item_device_brand_show();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _list_item_device_model_show();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _list_item_confirm_remote_connect_show();
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_focus(pt_this->h_last_focus_item,
                                     WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * DEVICE_LIST_ITEM_NUM + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;

}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage_input_src
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
static INT32 _add_new_device_page_show_subpage_input_src()
{
	INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    GL_RECT_T                           t_rect = {0};
    UINT16                              ui2_input_num = 0;
    HANDLE_T                            h_last_shadow_item = NULL_HANDLE;

	i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_INPUT_SOURCE_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_input,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _append_input();
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus_item = pt_this->h_list_item_input_src;

    i4_ret = c_wgl_set_focus(pt_this->h_subpage_input,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_input,
                 WGL_CMD_LB_HLT_ELEM,
                 WGL_PACK(pt_this->ui1_select_input),
                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    /* get input list num */
    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_input,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK (&ui2_input_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_input_num + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage_device_type
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
static INT32 _add_new_device_page_show_subpage_device_type()
{
	INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    GL_RECT_T                           t_rect = {0};
    UINT16                              ui2_device_num = 0;
    HANDLE_T                            h_last_shadow_item = NULL_HANDLE;

	i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_DEVICE_TYPE_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_device_type,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _append_device_type();
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus_item = pt_this->h_list_item_device_type;

    i4_ret = c_wgl_set_focus(pt_this->h_subpage_device_type,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type,
                 WGL_CMD_LB_HLT_ELEM,
                 WGL_PACK(pt_this->ui4_type_sel_idx+1),
                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_is_setup_worked = TRUE;  /* Device setup default success, Not clear device info*/

    /* get device type list num */
    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK (&ui2_device_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_device_num) + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage_device_type_aud
 *
 * Description: show the audio device type (audio receiver/amplifier and soundbar)
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_show_subpage_device_type_aud()
{
	INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    GL_RECT_T                           t_rect = {0};
    UINT16                              ui2_aud_device_num = 0;
    HANDLE_T                            h_last_shadow_item = NULL_HANDLE;

	i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_DEVICE_TYPE_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_device_type_aud,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _append_device_type_aud();
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus_item = pt_this->h_list_item_device_type_aud;

    i4_ret = c_wgl_set_focus(pt_this->h_subpage_device_type_aud,
                             WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type_aud,
                 WGL_CMD_LB_HLT_ELEM,
                 WGL_PACK(pt_this->ui4_type_sel_idx-8),
                 NULL);
	MENU_LOG_ON_FAIL(i4_ret);

    pt_this->b_is_setup_worked = TRUE;  /* Device setup default success, Not clear device info*/

    /* get audio device type list num */
    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_type_aud,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK (&ui2_aud_device_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* adjust last shadow position */
    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
	t_rect.i4_right = CONTENT_X + CONTENT_H;
	t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui2_aud_device_num + CONTENT_Y;
	t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

	i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage_device_brand
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
static INT32 _add_new_device_page_show_subpage_device_brand()
{
	INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    HANDLE_T			                h_last_shadow_item = NULL_HANDLE;

	i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_DEVICE_BRAND_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_brand_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_BRAND_MSG)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_BRAND_MSG))));
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_this->t_select_brd.h_brand_vkb,
                    VKB_CMD_CLEAR_TEXT,
                    (VOID*) NULL,
                    (VOID*) NULL));

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_device_brand_title,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_device_brand,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_ok_btn,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_enable(pt_this->h_ok_btn,FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cancel_btn,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_cancel_btn,
						    WGL_CMD_BTN_SET_TEXT,
						    WGL_PACK(MENU_TEXT(MLM_MENU_KEY_DEVICE_CANCEL_BTN_MSG1)),	/*cancel*/
						    WGL_PACK((UINT16)0xFFFF));

    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_select_brd.h_brd_eb_del_all, WGL_SW_NORMAL));
    MENU_LOG_ON_FAIL (c_wgl_float (pt_this->t_select_brd.h_brd_eb_del_all, TRUE, FALSE));

    i4_ret = a_vkb_set_visibility(pt_this->t_select_brd.h_brand_vkb, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;

    i4_ret = a_vkb_set_focus(pt_this->t_select_brd.h_brand_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage_device_model
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
static INT32 _add_new_device_page_show_subpage_device_model()
{
	INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    HANDLE_T			                h_last_shadow_item = NULL_HANDLE;

	i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_DEVICE_MODEL_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_model_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_MODEL_MSG)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_MODEL_MSG))));
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL ( a_vkb_do_cmd (pt_this->t_select_model.h_model_vkb,
                    VKB_CMD_CLEAR_TEXT,
                    (VOID*) NULL,
                    (VOID*) NULL));


    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_device_model_title,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_device_model,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_ok_btn,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_enable(pt_this->h_ok_btn,FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cancel_btn,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_cancel_btn,
						    WGL_CMD_BTN_SET_TEXT,
						    WGL_PACK(MENU_TEXT(MLM_MENU_KEY_DEVICE_CANCEL_BTN_MSG2)),	/*I Don't Know the Model*/
						    WGL_PACK((UINT16)0xFFFF));

    MENU_LOG_ON_FAIL(i4_ret);


    MENU_LOG_ON_FAIL (c_wgl_set_visibility (pt_this->t_select_model.h_model_eb_del_all, WGL_SW_NORMAL));
    MENU_LOG_ON_FAIL (c_wgl_float (pt_this->t_select_model.h_model_eb_del_all, TRUE, FALSE));

    i4_ret = a_vkb_set_visibility(pt_this->t_select_model.h_model_vkb, TRUE);

    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus_item = pt_this->h_list_item_device_model;

    i4_ret = a_vkb_set_focus(pt_this->t_select_model.h_model_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));

    pt_this->b_is_i_do_not_know_mdl_sel = FALSE;

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage_device_confirm
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
static INT32 _add_new_device_page_show_subpage_device_confirm()
{
	INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    HANDLE_T			                h_last_shadow_item = NULL_HANDLE;

	i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_CONFIRM_IR_TITLE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret = c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_subpage_device_confirm,
    							  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->t_remote_code.h_code_intro_txt,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(pt_this->t_remote_code.h_attemp_code_txt,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);


	i4_ret = c_wgl_set_visibility(pt_this->t_remote_code.h_it_work_btn,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->t_remote_code.h_try_next_btn,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->t_remote_code.h_manual_enter_code_btn,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->h_last_focus_item = pt_this->h_list_item_confirm_remote_connect;

    menu_set_power_off_flag(TRUE);

    menu_pm_get_last_shadow_item(&h_last_shadow_item);
	i4_ret=c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;

}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show_subpage
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
static INT32 _add_new_device_page_show_subpage(BOOL b_repaint)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    menu_set_help_tip_flag(TRUE);

    switch (pt_this->e_subpage)
    {
        case ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN:
        {
			_add_new_device_page_show_subpage_main();
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_INPUT_LIST:
        {
			_add_new_device_page_show_subpage_input_src();
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE:
        {
			_add_new_device_page_show_subpage_device_type();
        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE_AUD:
        {
			_add_new_device_page_show_subpage_device_type_aud();
        }
            break;
        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND:
        {
            menu_set_help_tip_flag(FALSE);
			_add_new_device_page_show_subpage_device_brand();

        }
            break;

        case ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL:
        {
            menu_set_help_tip_flag(FALSE);
			_add_new_device_page_show_subpage_device_model();

        }
            break;

		case ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT:
        {
			_add_new_device_page_show_subpage_device_confirm();
        }
            break;

        default:
            break;
    }

    if (b_repaint)
    {
        i4_ret = menu_pm_repaint();
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_input_src_proc_fct
 *
 * Description:_list_item_input_src_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_input_src_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        UTF16_T     w2s_help_tip[512] = {0};

        c_uc_w2s_strcpy(w2s_help_tip, MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_INPUT_SOURCE));

        if (pt_this->ui4_type_sel_idx < DEV_DB_MAX_DEV_TYPE_CONT)
        {
            c_uc_w2s_strncat(w2s_help_tip, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, 511);
        }
        menu_set_and_show_help_tip(w2s_help_tip);

    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if (BTN_CURSOR_LEFT == ui4_key_code)
                {
                    _to_prev_input_src_idx();
                }
                else
                {
                    _to_next_input_src_idx();
                }

                _list_item_input_src_show();
                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
			    return MENUR_OK;
            }
            case BTN_SELECT:
            {
            	pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_INPUT_LIST;
                _add_new_device_page_show_subpage(TRUE);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
				BOOL		b_is_visible = FALSE;

				c_wgl_get_visibility(pt_this->h_list_item_device_type_aud, &b_is_visible);
	            if (b_is_visible == TRUE)
	            {
	            	c_wgl_set_focus(pt_this->h_list_item_device_type_aud,
                             WGL_SYNC_AUTO_REPAINT);
	            }
	            else
	            {
		            c_wgl_set_focus(pt_this->h_list_item_device_type,
                             WGL_SYNC_AUTO_REPAINT);
	            }
                return WGLR_OK;
			}
            case BTN_CURSOR_DOWN:
            {
				UINT32		ui4_state_brd = 0;
				UINT32		ui4_state_mdl = 0;
				UINT32		ui4_state_confirm = 0;

				c_wgl_get_state(pt_this->h_list_item_device_brand, &ui4_state_brd);
				c_wgl_get_state(pt_this->h_list_item_device_model, &ui4_state_mdl);
				c_wgl_get_state(pt_this->h_list_item_confirm_remote_connect, &ui4_state_confirm);

				if(ui4_state_brd & WGL_STATE_ENABLED)
				{
	            	c_wgl_set_focus(pt_this->h_list_item_device_brand,
	                                 WGL_SYNC_AUTO_REPAINT);
	            }
	            else if(ui4_state_mdl & WGL_STATE_ENABLED)
	            {
	                c_wgl_set_focus(pt_this->h_list_item_device_model,
	                                 WGL_SYNC_AUTO_REPAINT);
	            }
	            else if(ui4_state_confirm & WGL_STATE_ENABLED)
	            {
	                c_wgl_set_focus(pt_this->h_list_item_confirm_remote_connect,
	                                 WGL_SYNC_AUTO_REPAINT);
	            }
	            else
	            {
		            menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
	                menu_pm_repaint();
	            }

                return WGLR_OK;
            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                _back_key_handler();
                return WGLR_OK;
            }
            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _to_prev_device_type_idx
 *
 * Description:_to_prev_device_type_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_prev_device_type_idx(VOID)
{
    INT32       							i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
	UINT8									ui1_rec_num = 0;

    if (DEVICE_TYPE_UNKNOWN == pt_this->ui4_type_sel_idx)
    {
        pt_this->ui4_type_sel_idx = pt_this->ui4_type_num - 1;
    }
    else if (0 == pt_this->ui4_type_sel_idx)
    {
        pt_this->ui4_type_sel_idx = DEVICE_TYPE_UNKNOWN;
    }
    else
    {
        pt_this->ui4_type_sel_idx--;
    }

    pt_this->b_is_type_sel = TRUE;

	a_isl_get_num_rec(&ui1_rec_num);
	if(pt_this->ui4_type_sel_idx == MENU_SETUP_VCR_IDX)
    {
		/*comp*/
    	pt_this->ui1_select_input = ui1_rec_num-2;
		i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    	MENU_LOG_ON_FAIL(i4_ret);
    }
    else if((pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)||(pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX) )
    {
    	i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    	MENU_LOG_ON_FAIL(i4_ret);

    	/*record the pre select input*/
    	if(pt_this->ui1_select_input!=0xFF)
	    {
		    pt_this->ui1_pre_select_input = pt_this->ui1_select_input;
		    pt_this->ui1_select_input = 0xFF;
	    }
    }
	else
	{
		i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, TRUE);
    	MENU_LOG_ON_FAIL(i4_ret);

    	if(pt_this->ui1_select_input==0xFF)
	    {
		    pt_this->ui1_select_input = pt_this->ui1_pre_select_input;
	    }
    }

    DBG_INFO(("\n####%s(%d)pt_this->ui4_type_sel_idx=%d,pt_this->ui1_select_input=%d\n",__FUNCTION__,__LINE__,pt_this->ui4_type_sel_idx,pt_this->ui1_select_input));

    if((pt_this->b_is_type_sel)&&(pt_this->ui4_type_sel_idx != DEVICE_TYPE_UNKNOWN))
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, TRUE);
		MENU_LOG_ON_FAIL(i4_ret);
	}
	else
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, FALSE);
		MENU_LOG_ON_FAIL(i4_ret);
	}

    MENU_LOG_ON_FAIL (menu_pm_repaint());

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _to_next_device_type_idx
 *
 * Description:_to_next_device_type_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_next_device_type_idx(VOID)
{
    INT32       							i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
	UINT8									ui1_rec_num = 0;

    if ((pt_this->ui4_type_num - 1) == pt_this->ui4_type_sel_idx)
    {
        pt_this->ui4_type_sel_idx = DEVICE_TYPE_UNKNOWN;
    }

    else if (DEVICE_TYPE_UNKNOWN == pt_this->ui4_type_sel_idx)
    {
        pt_this->ui4_type_sel_idx = 0;
    }
    else
    {
        pt_this->ui4_type_sel_idx++;
    }

    pt_this->b_is_type_sel = TRUE;

    a_isl_get_num_rec(&ui1_rec_num);
	if(pt_this->ui4_type_sel_idx == MENU_SETUP_VCR_IDX)
    {
    	/*comp*/
    	pt_this->ui1_select_input = ui1_rec_num -2;
		i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    	MENU_LOG_ON_FAIL(i4_ret);
    }
    else if((pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)||(pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX) )
    {
    	i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    	MENU_LOG_ON_FAIL(i4_ret);

    	/*record the pre select input*/
    	if(pt_this->ui1_select_input!=0xFF)
	    {
		    pt_this->ui1_pre_select_input = pt_this->ui1_select_input;
		    pt_this->ui1_select_input = 0xFF;
	    }
    }
	else
	{
		i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, TRUE);
    	MENU_LOG_ON_FAIL(i4_ret);

    	if(pt_this->ui1_select_input==0xFF)
	    {
		    pt_this->ui1_select_input = pt_this->ui1_pre_select_input;
	    }
    }

    DBG_INFO(("\n####%s(%d)pt_this->ui4_type_sel_idx=%d,pt_this->ui1_select_input=%d\n",__FUNCTION__,__LINE__,pt_this->ui4_type_sel_idx,pt_this->ui1_select_input));

    if((pt_this->b_is_type_sel)&&(pt_this->ui4_type_sel_idx != DEVICE_TYPE_UNKNOWN))
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, TRUE);
		MENU_LOG_ON_FAIL(i4_ret);
	}
	else
	{
	    i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, FALSE);
		MENU_LOG_ON_FAIL(i4_ret);
	}

    MENU_LOG_ON_FAIL (menu_pm_repaint());

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _to_prev_device_type_aud_idx
 *
 * Description:_to_prev_device_type_aud_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_prev_device_type_aud_idx(VOID)
{
    INT32                                   i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T*        pt_this = &t_g_add_new_device_page_data;

    if (pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
    {
        pt_this->ui4_type_sel_idx = MENU_SETUP_SOUND_BAR_IDX;
    }
    else if (pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX)
    {
        pt_this->ui4_type_sel_idx = MENU_SETUP_AVR_AMP_IDX;
    }

    pt_this->b_is_type_sel = TRUE;

    i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    /*record the pre select input*/
	if(pt_this->ui1_select_input!=0xFF)
    {
	    pt_this->ui1_pre_select_input = pt_this->ui1_select_input;
	    pt_this->ui1_select_input = 0xFF;
    }
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("\n####%s(%d)pt_this->ui4_type_sel_idx=%d,pt_this->ui1_select_input=%d\n",__FUNCTION__,__LINE__,pt_this->ui4_type_sel_idx,pt_this->ui1_select_input));

    i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL (menu_pm_repaint());

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _to_next_device_type_aud_idx
 *
 * Description:_to_next_device_type_aud_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_next_device_type_aud_idx(VOID)
{
    INT32                                   i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T*        pt_this = &t_g_add_new_device_page_data;

    if (pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
    {
        pt_this->ui4_type_sel_idx = MENU_SETUP_SOUND_BAR_IDX;
    }
    else if (pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX)
    {
        pt_this->ui4_type_sel_idx = MENU_SETUP_AVR_AMP_IDX;
    }

    pt_this->b_is_type_sel = TRUE;

    i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
    /*record the pre select input*/
	if(pt_this->ui1_select_input!=0xFF)
    {
	    pt_this->ui1_pre_select_input = pt_this->ui1_select_input;
	    pt_this->ui1_select_input = 0xFF;
    }
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("\n####%s(%d)pt_this->ui4_type_sel_idx=%d,pt_this->ui1_select_input=%d\n",__FUNCTION__,__LINE__,pt_this->ui4_type_sel_idx,pt_this->ui1_select_input));

	i4_ret = c_wgl_enable(pt_this->h_list_item_device_brand, TRUE);
	MENU_LOG_ON_FAIL(i4_ret);

    MENU_LOG_ON_FAIL (menu_pm_repaint());

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _to_next_input_src_idx
 *
 * Description:_to_next_input_src_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_next_input_src_idx(void)
{
	INT32       							i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
	UINT8			ui1_rec_num = 0;

	if(pt_this->ui1_select_input == 0xFF)
    {
	    pt_this->ui1_select_input = pt_this->ui1_pre_select_input;
	    DBG_INFO(("\n####%s(%d)pt_this->ui1_select_input = %d\n",__FUNCTION__,__LINE__,pt_this->ui1_select_input));
    }
    a_isl_get_num_rec(&ui1_rec_num);
    if (pt_this->ui1_select_input < ui1_rec_num-2)
    {
        pt_this->ui1_select_input++;
    }
    else
    {
        pt_this->ui1_select_input = 0;
    }

	DBG_INFO(("\n####%s(%d)pt_this->ui1_select_input = %d\n",__FUNCTION__,__LINE__,pt_this->ui1_select_input));

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _to_prev_input_src_idx
 *
 * Description:_to_prev_input_src_idx
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _to_prev_input_src_idx(void)
{
	INT32       							i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
    UINT8			ui1_rec_num = 0;

    if(pt_this->ui1_select_input == 0xFF)
    {
	    pt_this->ui1_select_input = pt_this->ui1_pre_select_input;
	    DBG_INFO(("\n####%s(%d)pt_this->ui1_select_input = %d\n",__FUNCTION__,__LINE__,pt_this->ui1_select_input));
    }
    a_isl_get_num_rec(&ui1_rec_num);
    if (pt_this->ui1_select_input > 0)
    {
        pt_this->ui1_select_input--;
    }
    else
    {
        pt_this->ui1_select_input = ui1_rec_num-2;
    }

	DBG_INFO(("\n####%s(%d)pt_this->ui1_select_input = %d\n",__FUNCTION__,__LINE__,pt_this->ui1_select_input));

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_type_proc_fct
 *
 * Description:_list_item_device_type_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_type_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELE_TIP_DEVICE_TYPE));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if (BTN_CURSOR_LEFT == ui4_key_code)
                {
                    _to_prev_device_type_idx();
                }
                else
                {
                    _to_next_device_type_idx();
                }

                _list_item_device_type_show();
                _list_item_input_src_show();
                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
                return MENUR_OK;
            }
            case BTN_SELECT:
            {
            	pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE;
                _add_new_device_page_show_subpage(TRUE);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
	            menu_set_focus_on_backbar(TRUE);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                return WGLR_OK;
            }
            case BTN_CURSOR_DOWN:
            {
				UINT32		ui4_state = 0;

				c_wgl_get_state(pt_this->h_list_item_input_src, &ui4_state);
				if(ui4_state & WGL_STATE_ENABLED)
				{
		            c_wgl_set_focus(pt_this->h_list_item_input_src,
	                                 WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
                	c_wgl_set_focus(pt_this->h_list_item_device_brand,
                                 WGL_SYNC_AUTO_REPAINT);
                }
                return WGLR_OK;

            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                _back_key_handler();
                return WGLR_OK;
            }
            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_type_aud_proc_fct
 *
 * Description:_list_item_device_type_aud_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_type_aud_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELE_TIP_DEVICE_TYPE));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                if (BTN_CURSOR_LEFT == ui4_key_code)
                {
                    _to_prev_device_type_aud_idx();
                }
                else
                {
                    _to_next_device_type_aud_idx();
                }

                _list_item_device_type_aud_show();
                _list_item_input_src_show();
                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
                return MENUR_OK;
            }
            case BTN_SELECT:
            {
            	pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE_AUD;
                _add_new_device_page_show_subpage(TRUE);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
	            menu_set_focus_on_backbar(TRUE);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                return WGLR_OK;
            }
            case BTN_CURSOR_DOWN:
            {
				UINT32		ui4_state = 0;

				c_wgl_get_state(pt_this->h_list_item_input_src, &ui4_state);
				if(ui4_state & WGL_STATE_ENABLED)
				{
		            c_wgl_set_focus(pt_this->h_list_item_input_src,
	                                 WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
                	c_wgl_set_focus(pt_this->h_list_item_device_brand,
                                 WGL_SYNC_AUTO_REPAINT);
                }
                return WGLR_OK;

            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                _back_key_handler();
                return WGLR_OK;
            }
            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_brand_proc_fct
 *
 * Description:_list_item_device_brand_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_brand_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        UTF16_T     w2s_help_tip[512] = {0};
        ISL_REC_T   t_isl_rec;

		c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(pt_this->aui1_input_src_id[pt_this->ui1_select_input], &t_isl_rec);
        c_uc_w2s_strncpy(w2s_help_tip,MENU_TEXT(MLM_MENU_KEY_HELE_TIP_DEVICE_BRAND), 511);
        c_uc_w2s_strncat(w2s_help_tip,a_isl_get_display_name(&t_isl_rec), 511);
        menu_set_and_show_help_tip(w2s_help_tip);
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                return MENUR_OK;
            }
            case BTN_SELECT:
            {
            	pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND;
                _add_new_device_page_show_subpage(TRUE);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
				UINT32		ui4_state = 0;
				BOOL    	b_is_visible = FALSE;

				c_wgl_get_state(pt_this->h_list_item_input_src, &ui4_state);
				if(ui4_state & WGL_STATE_ENABLED)
				{
	                c_wgl_set_focus(pt_this->h_list_item_input_src,
                                 WGL_SYNC_AUTO_REPAINT);
                }
                else
                {

		            c_wgl_get_visibility(pt_this->h_list_item_device_type_aud, &b_is_visible);
		            if (b_is_visible == TRUE)
		            {
		            	c_wgl_set_focus(pt_this->h_list_item_device_type_aud,
                                 WGL_SYNC_AUTO_REPAINT);
		            }
		            else
		            {
			            c_wgl_set_focus(pt_this->h_list_item_device_type,
                                 WGL_SYNC_AUTO_REPAINT);
		            }

                }
                return WGLR_OK;

			}
            case BTN_CURSOR_DOWN:
            {
				UINT32		ui4_state_mdl = 0;
				UINT32		ui4_state_confirm = 0;

				c_wgl_get_state(pt_this->h_list_item_device_model, &ui4_state_mdl);
				c_wgl_get_state(pt_this->h_list_item_confirm_remote_connect, &ui4_state_confirm);
				if(ui4_state_mdl & WGL_STATE_ENABLED)
				{
	                c_wgl_set_focus(pt_this->h_list_item_device_model,
	                                 WGL_SYNC_AUTO_REPAINT);
                }
                else if(ui4_state_confirm & WGL_STATE_ENABLED)
                {
	                c_wgl_set_focus(pt_this->h_list_item_confirm_remote_connect,
				                     WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
	                menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
	                menu_pm_repaint();
                }
                return WGLR_OK;
            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                _back_key_handler();
                return WGLR_OK;
            }
            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_model_proc_fct
 *
 * Description:_list_item_device_model_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_model_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        UTF16_T     w2s_help_tip[512] = {0};
        ISL_REC_T   t_isl_rec;

		c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(pt_this->aui1_input_src_id[pt_this->ui1_select_input], &t_isl_rec);
        c_uc_w2s_strncpy(w2s_help_tip,MENU_TEXT(MLM_MENU_KEY_HELE_TIP_DEVICE_MODEL), 511);
        c_uc_w2s_strncat(w2s_help_tip,a_isl_get_display_name(&t_isl_rec), 511);
        menu_set_and_show_help_tip(w2s_help_tip);
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                return MENUR_OK;
            }
            case BTN_SELECT:
            {
            	pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL;
                _add_new_device_page_show_subpage(TRUE);
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
				UINT32		ui4_state = 0;
				c_wgl_get_state(pt_this->h_list_item_device_brand, &ui4_state);
				if(ui4_state & WGL_STATE_ENABLED)
				{
	                c_wgl_set_focus(pt_this->h_list_item_device_brand,
	                                 WGL_SYNC_AUTO_REPAINT);
	            }
	            else
	            {
	                c_wgl_set_focus(pt_this->h_list_item_input_src,
	                                 WGL_SYNC_AUTO_REPAINT);
	            }
                return WGLR_OK;
			}
            case BTN_CURSOR_DOWN:
            {
				UINT32		ui4_state = 0;
				c_wgl_get_state(pt_this->h_list_item_confirm_remote_connect, &ui4_state);
				if(ui4_state & WGL_STATE_ENABLED)
				{
	                c_wgl_set_focus(pt_this->h_list_item_confirm_remote_connect,
	                                 WGL_SYNC_AUTO_REPAINT);
	            }
	            else
	            {
	                menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
	                menu_pm_repaint();
	            }
                return WGLR_OK;
            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                _back_key_handler();
                return WGLR_OK;
            }
            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_confirm_code_chang_lang
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
static INT32 _menu_add_new_device_confirm_code_chang_lang(BOOL    b_repaint)
{
    UTF16_T     w2s_str[128] = {0};
    CHAR        s_codeset[16] = {0};
    UTF16_T     w2s_codeset[16] = {0};
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32		i4_ret = MENUR_OK;
    CHAR        s_space[8] = {0};
    UTF16_T     w2s_space[8] = {0};

    c_sprintf(s_space, "  ");
    c_uc_ps_to_w2s(s_space, w2s_space, 8);

    if (c_strcmp(pt_this->s_codeset, "") == 0)
    {
        c_uc_w2s_strcpy(w2s_str, MENU_TEXT (MLM_MENU_KEY_DEVICE_SETUP_CONFIRM_CODE_NOT_FOUND));
        c_wgl_enable(pt_this->t_remote_code.h_try_next_btn, FALSE);
    }
    else
    {
        c_sprintf(s_codeset, "(%d of %d).", pt_this->ui1_cur_code_pos, pt_this->ui1_codeset_num);
    	c_uc_ps_to_w2s(s_codeset, w2s_codeset, 16);
        c_uc_w2s_strcpy(w2s_str, MENU_TEXT (MLM_MENU_KEY_DEVICE_SETUP_CODE_CONFIRM));
        c_uc_w2s_strcat(w2s_str,w2s_space);
        c_uc_w2s_strcat(w2s_str,w2s_codeset);
    }

	/*set the code attemp txt for confirm subpage*/
    i4_ret = _menu_add_new_device_set_desc_htxt(pt_this->t_remote_code.h_attemp_code_txt,
                                w2s_str,
                                NULL_HANDLE,
                                NULL_HANDLE);
	MENU_LOG_ON_FAIL(i4_ret);


	MENU_LOG_ON_FAIL ( c_wgl_do_cmd(pt_this->t_remote_code.h_attemp_code_txt,
            WGL_CMD_TEXT_SET_TEXT,
            WGL_PACK (w2s_str),
            WGL_PACK (c_uc_w2s_strlen (w2s_str))));

    if((pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)||(pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX) )
    {
	    i4_ret = _menu_add_new_device_set_desc_htxt(pt_this->t_remote_code.h_code_intro_txt,
                                MENU_TEXT(MLM_MENU_KEY_DEVICE_SETUP_CODE_CONFIRM_DESC_FOR_AUDIO),
                                h_g_menu_img_Remote_Key_Device_Power,
                                NULL_HANDLE);
		MENU_LOG_ON_FAIL(i4_ret);
    	MENU_LOG_ON_FAIL ( c_wgl_do_cmd(pt_this->t_remote_code.h_it_work_btn,
    				 WGL_CMD_BTN_SET_TEXT,
    				 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_AUD_CONTROL_CONFIRM_WORK)),
    				 WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_AUD_CONTROL_CONFIRM_WORK)))));
    }
    else
    {
        UTF16_T     ps_w2s[128] = {0};
	    i4_ret = _menu_add_new_device_set_desc_htxt(pt_this->t_remote_code.h_code_intro_txt,
	                                MENU_TEXT(MLM_MENU_KEY_DEVICE_SETUP_CODE_CONFIRM_DESC),
	                                h_g_menu_img_Remote_Key_Device_Power,
	                                NULL_HANDLE);
		MENU_LOG_ON_FAIL(i4_ret);
        c_uc_w2s_strncpy(ps_w2s, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, 128);
        c_uc_w2s_strncat(ps_w2s, (MENU_TEXT(MLM_MENU_KEY_DEVICE_SETUP_CONFIRM_WORK)), 128);
        MENU_LOG_ON_FAIL ( c_wgl_do_cmd(pt_this->t_remote_code.h_it_work_btn,
    				 WGL_CMD_BTN_SET_TEXT,
    				 WGL_PACK (ps_w2s),
    				 WGL_PACK(c_uc_w2s_strlen(ps_w2s))));
    }

	MENU_LOG_ON_FAIL ( c_wgl_do_cmd(pt_this->t_remote_code.h_try_next_btn,
				 WGL_CMD_BTN_SET_TEXT,
				 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_AUD_CONTROL_CONFIRM_TRY_NEXT)),
				 WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_AUD_CONTROL_CONFIRM_TRY_NEXT)))));

	MENU_LOG_ON_FAIL ( c_wgl_do_cmd(pt_this->t_remote_code.h_manual_enter_code_btn,
				 WGL_CMD_BTN_SET_TEXT,
				 WGL_PACK (MENU_TEXT(MLM_MENU_KEY_DEVICE_MANUAL_ENTER_CODE_BTN_MSG)),
				 WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_DEVICE_MANUAL_ENTER_CODE_BTN_MSG)))));

    if (b_repaint)
    {
        c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
    }
    return  0;
}
/*----------------------------------------------------------------------------
* Name: _menu_add_new_device_setup_codeset_update
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
static INT32 _menu_add_new_device_setup_codeset_update( BOOL    b_repaint )
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32                                     i4_ret = 0;

    pt_this->ui1_codeset_num = 0;
    pt_this->ui1_cur_code_pos = 0;

    pt_this->b_is_setup_worked = FALSE;

    c_strncpy(pt_this->s_codeset, "", 5);

    /* here only deal with the dev setup*/
    BOOL    b_db_status = FALSE;
    DEV_DB_LOCK_CHECK_COND_T e_check_cond = DEV_DB_LOCK_CHECK_COND_CODESET;

    i4_ret = a_dev_db_check_lock_info( e_check_cond, &b_db_status );
    if (MENUR_OK != i4_ret)
    {
	    DBG_ERROR(("\n[####%s(%d)] a_dev_db_check_lock_info() i4_ret=%d , check_cond=%d, b_db_status=%d\n", __FUNCTION__,__LINE__,i4_ret, e_check_cond, b_db_status));
	}
    i4_ret = a_dev_db_update_codeset(pt_this->ui4_type_sel_idx,
                            pt_this->t_dev_type[pt_this->ui4_type_sel_idx],
                            pt_this->t_brd_info[pt_this->ui4_brd_sel_idx],
                            pt_this->t_mdl_info[pt_this->ui4_mdl_sel_idx],
                            pt_this->s_brd_name,
                            pt_this->s_model_name);

    if (DEV_DBR_OK != i4_ret)
    {
        DBG_ERROR(("[####%s(%d)] a_dev_db_get_codeset(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));
        return MENUR_FAIL;
    }

    return 0;
}
/*----------------------------------------------------------------------------
* Name: _menu_add_new_device_setup_codesetlist_update
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

static INT32 _menu_add_new_device_setup_codesetlist_update(BOOL    b_repaint)
{
    INT32              i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    pt_this->ui1_cur_code_pos = 0;

    if (FALSE == pt_this->b_is_brd_sel)
    {
        DBG_INFO(("%s(%d)[MENU_dev_db]brand info have not select, please select it first!\r\n",__FUNCTION__,__LINE__));
        return MENUR_OK;
    }

    i4_ret = a_dev_db_update_codeset_with_brand(pt_this->ui4_type_sel_idx,
                            pt_this->t_dev_type[pt_this->ui4_type_sel_idx],
                            pt_this->t_brd_info[pt_this->ui4_brd_sel_idx],
                            pt_this->t_brd_info[pt_this->ui4_brd_sel_idx].s_src_name);

    DBG_INFO(("%s(%d)[MENU_dev_db] a_dev_db_update_codeset_with_brand(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_setup_save_and_upload_codeset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_setup_save_and_upload_codeset(UINT32 ui4_idx)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32        i4_ret;

    if (ui4_idx >= (pt_this->pt_codeset_list->t_codeset_list1.i4_length + pt_this->pt_codeset_list->t_codeset_list2.i4_length))
    {
        DBG_INFO(("%s(%d)[MENU_dev_db]the index for codeset should not more then [%d]\n",__FUNCTION__,__LINE__,
                   pt_this->pt_codeset_list->t_codeset_list1.i4_length + pt_this->pt_codeset_list->t_codeset_list2.i4_length));
    }
    else
    {
        DBG_INFO(("%s(%d)[MENU_dev_db] the codeset select idx[%d]\n",__FUNCTION__,__LINE__,ui4_idx));

        if (ui4_idx >= pt_this->pt_codeset_list->t_codeset_list1.i4_length)
        {
            if (NULL != pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length])
            {
                i4_ret = a_dev_db_save_codeset(pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length]);
                DBG_INFO(("%s(%d)[MENU_dev_db] a_dev_db_save_codeset() return[%d]\n",__FUNCTION__,__LINE__,i4_ret));

                i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset_list->t_codeset_list2.p_list[ui4_idx - pt_this->pt_codeset_list->t_codeset_list1.i4_length]);
                DBG_INFO(("%s(%d)[MENU_dev_db] a_dev_db_upload_codeset_ex() return[%d]\n",__FUNCTION__,__LINE__,i4_ret));

            }
        }
        else
        {
            if (NULL != pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx])
            {
                i4_ret = a_dev_db_save_codeset(pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]);
                DBG_INFO(("%s(%d)[MENU_dev_db] a_dev_db_save_codeset() return[%d]\n",__FUNCTION__,__LINE__,i4_ret));


                i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset_list->t_codeset_list1.p_list[ui4_idx]);
                DBG_INFO(("%s(%d)[MENU_dev_db] a_dev_db_upload_codeset_ex() return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
            }
        }
    }

    return CLIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_confirm_remote_connect_proc_fct
 *
 * Description:_list_item_confirm_remote_connect_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_confirm_remote_connect_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	INT32							 i4_ret = MENUR_OK;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_CONFIRM_IR));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;

        /* as the codeset is quering, here should do noting*/
        if (pt_this->b_is_codeset_querying)
        {
            return 0;
        }

        switch (ui4_key_code)
        {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            {
                return MENUR_OK;
            }
            case BTN_SELECT:
            {
	            if (pt_this->b_is_codeset_querying)
	            {
	                return 0;
	            }
	            else
	            {

#ifdef APP_UEI_SPINNER_SUPPORT
		            /*anyway,show confirm page first*/
					_menu_add_new_device_confirm_code_chang_lang(TRUE);
					pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
					_add_new_device_page_show_subpage(TRUE);

					i4_ret = menu_page_animation_start(1, FALSE);
					MENU_LOG_ON_FAIL(i4_ret);

					i4_ret = menu_page_animation_show();
					MENU_LOG_ON_FAIL(i4_ret);
					pt_this->b_animation = TRUE;
#endif
					if((pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX)&&
						(c_strcmp(pt_this->s_brd_name, "VIZIO")==0)&&
						(!pt_this->b_is_mdl_sel))
					{
		                i4_ret = a_dev_db_clean_codeset_list();
		                if (MENUR_OK != i4_ret)
		                {
						    DBG_ERROR(("####%s(%d) a_dev_db_clean_codeset_list() return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
						}
		                i4_ret = _menu_add_new_device_setup_codesetlist_update(FALSE);
		                if (MENUR_OK != i4_ret)
		                {
			                DBG_ERROR(("\n####%s(%d)codesetlist update i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
						}
		                MENU_LOG_ON_FAIL(i4_ret);

					}
					else
					{
		                _add_new_device_page_reset_codeset_info();
		                i4_ret = _menu_add_new_device_setup_codeset_update(FALSE);
		                if (MENUR_OK != i4_ret)
		                {
			                DBG_ERROR(("\n####%s(%d)codeset update i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
						}
		                MENU_LOG_ON_FAIL(i4_ret);
	                }
	                if  (MENUR_OK != i4_ret)
	                {
						_menu_add_new_device_confirm_code_chang_lang(TRUE);
	                    pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
		                _add_new_device_page_show_subpage(TRUE);

	                    pt_this->b_is_codeset_querying = FALSE;
#ifdef APP_UEI_SPINNER_SUPPORT
						/*hide spinner after get codeset for confirm remote conection page*/
						_add_device_animation_stop();
						DBG_INFO(("\n####%s(%d)confirm page show\n",__FUNCTION__,__LINE__));
#endif
	                }
	                else
	                {
	                    pt_this->b_is_codeset_querying = TRUE;
	                }

					/* chang input source after select input source*/
				    if((pt_this->ui4_type_sel_idx != MENU_SETUP_AVR_AMP_IDX)&&(pt_this->ui4_type_sel_idx != MENU_SETUP_SOUND_BAR_IDX) )
		            {
		                i4_ret = _menu_add_new_device_change_input_src();
		                MENU_LOG_ON_FAIL(i4_ret);
		            }

	            }
                return WGLR_OK;
			}
            case BTN_CURSOR_UP:
            {
				UINT32		ui4_state_brd = 0;
				UINT32		ui4_state_mdl = 0;
				UINT32		ui4_state_ipt = 0;

				c_wgl_get_state(pt_this->h_list_item_device_brand, &ui4_state_brd);
				c_wgl_get_state(pt_this->h_list_item_device_model, &ui4_state_mdl);
				c_wgl_get_state(pt_this->h_list_item_input_src, &ui4_state_ipt);

				if(ui4_state_mdl & WGL_STATE_ENABLED)
				{
	                c_wgl_set_focus(pt_this->h_list_item_device_model,
                                 WGL_SYNC_AUTO_REPAINT);
                }
                else if(ui4_state_brd & WGL_STATE_ENABLED)
                {
	                c_wgl_set_focus(pt_this->h_list_item_device_brand,
                                 WGL_SYNC_AUTO_REPAINT);
                }
                else if(ui4_state_ipt & WGL_STATE_ENABLED)
                {
                    c_wgl_set_focus(pt_this->h_list_item_input_src,
                                 WGL_SYNC_AUTO_REPAINT);

                }
                else
                {
                    c_wgl_set_focus(pt_this->h_list_item_device_type,
                                 WGL_SYNC_AUTO_REPAINT);
                }
                return WGLR_OK;
			}
            case BTN_CURSOR_DOWN:
            {
                menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                menu_pm_repaint();
                return WGLR_OK;
            }
            case BTN_EXIT:
            case BTN_RETURN:
            {
                _back_key_handler();
                return WGLR_OK;
            }
            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _list_item_input_src_create
 *
 * Description:_list_item_input_src_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_input_src_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UINT8       ui1_num_rec = 0;

    i4_ret = a_isl_get_num_rec(&ui1_num_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_INPUT_SRC_IDX,
                              ui1_num_rec,
                              _list_item_input_src_proc_fct,
                              &pt_this->h_list_item_input_src);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_type_create
 *
 * Description:_list_item_device_type_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_type_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_DEVICE_TYPE_IDX,
                              DEVICE_TYPE_MAX,
                              _list_item_device_type_proc_fct,
                              &pt_this->h_list_item_device_type);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_type_aud_create
 *
 * Description:_list_item_device_type_aud_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_type_aud_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_DEVICE_TYPE_AUD_IDX,
                              DEVICE_TYPE_AUD_MAX,
                              _list_item_device_type_aud_proc_fct,
                              &pt_this->h_list_item_device_type_aud);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_img_suit_reset
 *
 * Description:
 * if ui1_col = 1,  < | option | > ;
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _list_item_img_suit_reset(HANDLE_T h_listitem)
{
    INT32                   i4_ret;
    WGL_LB_ITEM_IMG_SUIT_T  t_img_suit_left;
    WGL_LB_ITEM_IMG_SUIT_T  t_img_suit_right;

    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_left.h_highlight                   = NULL_HANDLE;
    t_img_suit_left.h_selected_highlight          = NULL_HANDLE;

    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_right.h_highlight                   = NULL_HANDLE;
    t_img_suit_right.h_selected_highlight          = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(h_listitem,
                          WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                          WGL_PACK(0),
                          WGL_PACK(&t_img_suit_left));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_listitem,
                          WGL_CMD_LB_SET_ITEM_IMAGE_SUIT,
                          WGL_PACK(2),
                          WGL_PACK(&t_img_suit_right));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_brand_create
 *
 * Description:_list_item_device_brand_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_brand_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_DEVICE_BRAND_IDX,
                              DEVICE_TYPE_MAX,
                              _list_item_device_brand_proc_fct,
                              &pt_this->h_list_item_device_brand);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _list_item_img_suit_reset(pt_this->h_list_item_device_brand);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_device_model_create
 *
 * Description:_list_item_device_model_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_device_model_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_DEVICE_MODEL_IDX,
                              DEVICE_TYPE_MAX,
                              _list_item_device_model_proc_fct,
                              &pt_this->h_list_item_device_model);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _list_item_img_suit_reset(pt_this->h_list_item_device_model);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _list_item_confirm_remote_connect_create
 *
 * Description:_list_item_confirm_remote_connect_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _list_item_confirm_remote_connect_create(VOID)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UINT8       ui1_num_rec = 0;

    i4_ret = a_isl_get_num_rec(&ui1_num_rec);
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = menu_list_create(pt_this->h_cnt_frm,
                              LIST_ITEM_CONFIRM_REMOTE_CONNECT_IDX,
                              DEVICE_TYPE_MAX,
                              _list_item_confirm_remote_connect_proc_fct,
                              &pt_this->h_list_item_confirm_remote_connect);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _list_item_img_suit_reset(pt_this->h_list_item_confirm_remote_connect);
	MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_main_subpage_list_item_create
 *
 * Description:_menu_add_new_device_main_subpage_list_item_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_main_subpage_list_item_create(VOID)
{
	INT32       						i4_ret = MENUR_OK;

	i4_ret = _list_item_input_src_create();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _list_item_device_type_create();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _list_item_device_type_aud_create();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _list_item_device_brand_create();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _list_item_device_model_create();
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _list_item_confirm_remote_connect_create();
	MENU_LOG_ON_FAIL(i4_ret);

	return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_subpage_create
 *
 * Description:_add_new_device_page_subpage_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_subpage_create(HANDLE_T h_parent,
                                        GL_RECT_T* pt_rect,
                                        wgl_widget_proc_fct     pf_wdgt_proc,
                                        HANDLE_T* ph_subpage)
{
    INT32               i4_ret = MENUR_OK;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    /* input source no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32+1;
    at_cols[0].ui2_width        = INPUT_LST_W;

    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_MULTI_SEL |
                                  WGL_STL_GL_NO_IMG_UI;

    t_lb_init.ui2_max_elem_num  = MAX_REC;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    i4_ret = menu_list2_create (pt_this->h_cnt_frm,
                                pt_rect,
                                pf_wdgt_proc,
                                &t_lb_init,
                                NULL,
                                ph_subpage);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for input source list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _back_key_handler
 *
 * Description:_back_key_handler
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _back_key_handler(VOID)
{
    INT32               i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    ADD_NEW_DEVICE_PAGE_ENTER_FROM_T        e_enter_from = ADD_NEW_DEVICE_PAGE_ENTERN_FROM_NORMAL;

    if (ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN == pt_this->e_subpage)
    {
        i4_ret = menu_device_page_nav_go(NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
                                         NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        pt_this->b_is_brd_sel = FALSE;
        pt_this->b_is_mdl_sel = FALSE;
    }
    else
    {
		if(ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT == pt_this->e_subpage)
		{
			_add_new_device_page_reset_dev_info();

			menu_device_page_add_new_device_enter_from_get(&e_enter_from);
			if (ADD_NEW_DEVICE_PAGE_ENTERN_FROM_AUDIO_MODE_SETUP == e_enter_from)
		    {
		        pt_this->h_last_focus_item = pt_this->h_list_item_device_type_aud;
		        pt_this->ui4_type_sel_idx = MENU_SETUP_AVR_AMP_IDX;
		    }
		    else
		    {
			    pt_this->h_last_focus_item = pt_this->h_list_item_device_type;
			    pt_this->ui4_type_sel_idx = DEVICE_TYPE_UNKNOWN;
		    }
		}

        pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
        i4_ret = _add_new_device_page_show_subpage(TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
	    MENU_LOG_ON_FAIL(i4_ret);

    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_change_input_src
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
static INT32 _menu_add_new_device_change_input_src(VOID)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    UINT8  ui1_idx = 0;
    INT32  i4_ret  = MENUR_OK;

    ui1_idx = pt_this->aui1_input_src_id[pt_this->ui1_select_input];
    DBG_INFO(("[####%s(%d)] pt_this->ui1_select_input=%d,ui1_idx=%d\n",__FUNCTION__,__LINE__,pt_this->ui1_select_input,ui1_idx));

    if (ui1_idx == (UINT8) - 1 || ui1_idx >= 16)
    {
        return MENUR_FAIL;
    }

    /* stop 3rd process & show dtv signal */
    a_tv_net_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:resume=dtv\n");

    i4_ret = a_tv_change_input_src(menu_get_crnt_svctx(),
                                   SVCTX_STRM_MODE_AS_LAST,
                                   ui1_idx,
                                   NULL);
    if (MENUR_OK != i4_ret)
    {
	    DBG_ERROR(("[####%s(%d)] a_tv_change_input_src()failed. i4_ret = %d,src_idx=%d\n",__FUNCTION__,__LINE__, i4_ret,ui1_idx));
	}
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _subpage_input_proc_fct
 *
 * Description:_subpage_input_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _subpage_input_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        UTF16_T     w2s_help_tip[512] = {0};

        c_uc_w2s_strcpy(w2s_help_tip, MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_INPUT_SOURCE));

        if (pt_this->ui4_type_sel_idx < DEV_DB_MAX_DEV_TYPE_CONT)
        {
            c_uc_w2s_strncat(w2s_help_tip, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, 511);
        }
        menu_set_and_show_help_tip(w2s_help_tip);

    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;
        INT32       i4_ret = MENUR_OK;
        UINT16      ui2_idx = 0;
        UINT16      ui2_elem_num = 0;

        switch (ui4_key_code)
        {
        case BTN_CURSOR_UP :
        case BTN_CURSOR_DOWN :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&ui2_elem_num),
                         NULL);

            if(ui4_key_code == BTN_CURSOR_UP)
            {
                if(ui2_idx == 0)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_PREV_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }
            else
            {
                if(ui2_idx == (UINT16)(ui2_elem_num - 1))
                {
                    menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_NEXT_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }

            return MENUR_OK;
        }
        case BTN_SELECT :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);
            pt_this->ui1_select_input = ui2_idx;

            DBG_INFO(("\n####%s(%d)pt_this->ui1_select_input = %d\n",__FUNCTION__,__LINE__,pt_this->ui1_select_input));

            pt_this->e_pre_subpage = pt_this->e_subpage;
            pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
            if(pt_this->ui4_type_sel_idx == DEVICE_TYPE_UNKNOWN)
            {
	            pt_this->h_last_focus_item = pt_this->h_list_item_device_type;
            }
            else
            {
	            pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;
            }
            i4_ret = _add_new_device_page_show_subpage(TRUE);

            MENU_LOG_ON_FAIL(i4_ret);
            return WGLR_OK;
        }
        case BTN_EXIT:
        case BTN_RETURN:
            _back_key_handler();
            return WGLR_OK;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _create_input_subpage
 *
 * Description:_create_input_subpage
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _create_input_subpage(VOID)
{
    INT32       i4_ret = MENUR_OK;
    GL_RECT_T   t_rect;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    SET_RECT_BY_SIZE (&t_rect,
                      INPUT_LST_X,
                      INPUT_LST_Y,
                      INPUT_LST_W,
                      INPUT_LST_H);

    i4_ret = _add_new_device_page_subpage_create(pt_this->h_cnt_frm,
                                                  &t_rect,
                                                  _subpage_input_proc_fct,
                                                  &pt_this->h_subpage_input);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _subpage_device_type_aud_proc_fct
 *
 * Description:_subpage_device_type_aud_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _subpage_device_type_aud_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELE_TIP_DEVICE_TYPE));
    }
	else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;
        INT32       i4_ret = MENUR_OK;
        MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
        UINT16      ui2_idx = 0;
        UINT16      ui2_elem_num = 0;

        switch (ui4_key_code)
        {
        case BTN_CURSOR_UP :
        case BTN_CURSOR_DOWN :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&ui2_elem_num),
                         NULL);

            if(ui4_key_code == BTN_CURSOR_UP)
            {
                if(ui2_idx == 0)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_PREV_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }
            else
            {
                if(ui2_idx == (UINT16)(ui2_elem_num - 1))
                {
                    menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_NEXT_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }

            return MENUR_OK;
        }
        case BTN_SELECT :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

	        pt_this->ui4_type_sel_idx = ui2_idx+8;

            DBG_INFO(("\n####%s(%d)pt_this->ui4_type_sel_idx = %d\n",__FUNCTION__,__LINE__,pt_this->ui4_type_sel_idx));
            pt_this->b_is_type_sel = TRUE;
            pt_this->e_pre_subpage = pt_this->e_subpage;
            pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;

		    if((pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)||(pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX) )
            {
	            pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;
            }
            else
            {
	            pt_this->h_last_focus_item = pt_this->h_list_item_input_src;
            }
            i4_ret = _add_new_device_page_show_subpage(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            return i4_ret;
        }
        case BTN_EXIT:
        case BTN_RETURN:
            _back_key_handler();
            return WGLR_OK;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _subpage_device_type_proc_fct
 *
 * Description:_subpage_device_type_proc_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _subpage_device_type_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
	if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELE_TIP_DEVICE_TYPE));
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_key_code = (UINT32)pv_param1;
        INT32       i4_ret = MENUR_OK;
        MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
        UINT16      ui2_idx = 0;
        UINT16      ui2_elem_num = 0;
		UINT8		ui1_rec_num = 0;

        switch (ui4_key_code)
        {
        case BTN_CURSOR_UP :
        case BTN_CURSOR_DOWN :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&ui2_elem_num),
                         NULL);

            if(ui4_key_code == BTN_CURSOR_UP)
            {
                if(ui2_idx == 0)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_PREV_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }
            else
            {
                if(ui2_idx == (UINT16)(ui2_elem_num - 1))
                {
                    menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                    menu_pm_repaint();
                    return MENUR_OK;
                }
                else
                {
                    c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_HLT_NEXT_ELEM,
                                 WGL_PACK(TRUE),
                                 NULL);
                }
            }

            return MENUR_OK;
        }
        case BTN_SELECT :
        {
            c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            if(ui2_idx == 0)
            {
	            pt_this->ui4_type_sel_idx = DEVICE_TYPE_UNKNOWN;
            }
            else
            {
	            pt_this->ui4_type_sel_idx = ui2_idx-1;
            }
            DBG_INFO(("\n####%s(%d)pt_this->ui4_type_sel_idx = %d\n",__FUNCTION__,__LINE__,pt_this->ui4_type_sel_idx));
            pt_this->b_is_type_sel = TRUE;
            pt_this->e_pre_subpage = pt_this->e_subpage;
            pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;

			a_isl_get_num_rec(&ui1_rec_num);
			if(pt_this->ui4_type_sel_idx == MENU_SETUP_VCR_IDX)
			{
				/*comp*/
				pt_this->ui1_select_input = ui1_rec_num -2;
				i4_ret = c_wgl_enable(pt_this->h_list_item_input_src, FALSE);
				MENU_LOG_ON_FAIL(i4_ret);
				pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;
			}
		    else if((pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)||(pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX) )
            {
            	pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;
            }
            else
            {
            	pt_this->h_last_focus_item = pt_this->h_list_item_input_src;
            }

            i4_ret = _add_new_device_page_show_subpage(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            return i4_ret;
        }
        case BTN_EXIT:
        case BTN_RETURN:
            _back_key_handler();
            return WGLR_OK;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _create_device_type_subpage
 *
 * Description:_create_device_type_subpage
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _create_device_type_subpage(VOID)
{
    INT32       i4_ret = MENUR_OK;
    GL_RECT_T   t_rect;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    SET_RECT_BY_SIZE (&t_rect,
                      INPUT_LST_X,
                      INPUT_LST_Y,
                      INPUT_LST_W,
                      INPUT_LST_H);

    i4_ret = _add_new_device_page_subpage_create(pt_this->h_cnt_frm,
                                                  &t_rect,
                                                  _subpage_device_type_proc_fct,
                                                  &pt_this->h_subpage_device_type);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _create_device_type_aud_subpage
 *
 * Description:_create_device_type_aud_subpage
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _create_device_type_aud_subpage(VOID)
{
    INT32       i4_ret = MENUR_OK;
    GL_RECT_T   t_rect;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    SET_RECT_BY_SIZE (&t_rect,
                      INPUT_LST_X,
                      INPUT_LST_Y,
                      INPUT_LST_W,
                      INPUT_LST_H);

    i4_ret = _add_new_device_page_subpage_create(pt_this->h_cnt_frm,
                                                  &t_rect,
                                                  _subpage_device_type_aud_proc_fct,
                                                  &pt_this->h_subpage_device_type_aud);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_dlg_create
 *
 * Description:_menu_add_new_device_dlg_create
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_dlg_create(VOID)
{
    INT32                       			i4_ret  = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;
    UI_SIMPLE_DIALOG_INIT_T     			t_simple_dialog_init;
    GL_RECT_T                  				t_rect;

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY;
    t_simple_dialog_init.h_parent                       = pt_this->t_confirm_dlg.h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = NULL;
    t_simple_dialog_init.pf_wdgt_proc                   = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.b_one_btn_mode                 = FALSE;
    t_simple_dialog_init.b_default_answer               = FALSE;

    SET_RECT_BY_SIZE(&t_rect,
                     420,
                     308,
                     440,
                     104);

    t_simple_dialog_init.pt_rect            = &t_rect;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_this->t_confirm_dlg.h_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->t_confirm_dlg.b_is_show   = FALSE;

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
  Description:_menu_add_new_device_manual_enter_code_dlg_btn_no_fct
  			  press the no button of the manual enter code trige the function
  input:
  output:
  return:
----------------------------------------------------------------------------*/
static VOID _menu_add_new_device_manual_enter_code_dlg_btn_no_fct(UINT32 ui4_key_code)
{
	INT32		i4_ret = MENUR_OK;
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;

	if(ui4_key_code == BTN_SELECT)
	{
		i4_ret = _menu_add_new_device_manual_enter_code_dlg_hide(TRUE);
		DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	}
	else if(ui4_key_code == BTN_CURSOR_UP)
	{
		i4_ret = c_wgl_set_focus(pt_this->t_manual_enter_code_dlg.h_dlg_editbox, WGL_SYNC_AUTO_REPAINT);
		DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	}
	else if(ui4_key_code == BTN_CURSOR_LEFT)
	{
		i4_ret = c_wgl_set_focus(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn, WGL_SYNC_AUTO_REPAINT);
		DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	}
}
/*-----------------------------------------------------------------------------
  Description:_menu_add_new_device_manual_enter_code_dlg_btn_yes_fct
       		  press the yes button of the manual enter code dlg trige the function.
  input:
  output:
  return:
----------------------------------------------------------------------------*/
static VOID _menu_add_new_device_manual_enter_code_dlg_btn_yes_fct(UINT32 ui4_key_code)
{
	INT32		i4_ret = MENUR_OK;
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;

	if(ui4_key_code == BTN_SELECT)
	{
		i4_ret = _menu_add_new_device_manual_enter_code_dlg_hide(TRUE);
		DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));

		i4_ret =_menu_add_new_device_manual_enter_code();
		DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	}
	else if(ui4_key_code == BTN_CURSOR_UP)
	{
		i4_ret = c_wgl_set_focus(pt_this->t_manual_enter_code_dlg.h_dlg_editbox, WGL_SYNC_AUTO_REPAINT);
		DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	}
	else if(ui4_key_code == BTN_CURSOR_RIGHT)
	{
		i4_ret = c_wgl_set_focus(pt_this->t_manual_enter_code_dlg.h_dlg_no_btn, WGL_SYNC_AUTO_REPAINT);
		DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	}

}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code_dialog_proc_fct
 *
 * Description: the OK and Cancel button of the manual enter code dlg share the callback function,
 *				then, call the respectively callback function again
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_manual_enter_code_dialog_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        case BTN_CURSOR_UP:
        {
            add_dev_dlg_cb_fct  pf_back = NULL;
            INT32           i4_ret;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pf_back),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(pf_back != NULL)
            {
                pf_back(ui4_keycode);
            }

            return WGLR_OK;
        }
        default:
            break;
        }

        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
 /*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code_dlg_eb_fct
 *
 * Description: _menu_add_new_device_manual_enter_code_dlg_eb_fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _menu_add_new_device_manual_enter_code_dlg_eb_fct(
							    HANDLE_T                    h_widget,
							    UINT32                      ui4_msg,
							    VOID*                       param1,
							    VOID*                       param2)
 {
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 		pt_this = &t_g_add_new_device_page_data;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        INT32  				i4_ret = WZDR_OK;
        UTF16_T				w2s_text[32+1] = {0};
	    INT32 				ui4_keycode = (UINT32)param1;

        if ((ui4_keycode >= BTN_DIGIT_0) && (ui4_keycode <= BTN_DIGIT_9))
        {
			DBG_INFO(("\n####%s(%d)BTN_DIGIT_0-9 \n",__FUNCTION__,__LINE__));
	        i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
							              WGL_CMD_EB_GET_TEXT,
							              (VOID *) w2s_text,
							              (VOID *)32);
			DBG_INFO(("\n####%s(%d)WGL_CMD_EB_GET_TEXT return[%d] \n",__FUNCTION__,__LINE__,i4_ret));

			MENU_LOG_ON_FAIL(i4_ret);

			if ( c_uc_w2s_strlen(w2s_text) >= 4 )
			{
				i4_ret = c_wgl_set_focus(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn, WGL_SYNC_AUTO_REPAINT);
                DBG_INFO(("\n####%s(%d)c_wgl_set_focus return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
				return WZDR_OK;
			}
        }
        switch (ui4_keycode)
        {
            case BTN_CURSOR_DOWN:
            {
				i4_ret = c_wgl_set_focus(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn, WGL_SYNC_AUTO_REPAINT);
                DBG_INFO(("\n####%s(%d)c_wgl_set_focus return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
            }
                break;
            case BTN_CURSOR_LEFT:
            {
                i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
						              WGL_CMD_EB_GET_TEXT,
						              (VOID *) w2s_text,
						              (VOID *)32);
				MENU_LOG_ON_FAIL(i4_ret);

                if ( c_uc_w2s_strlen(w2s_text) > 0 )
                {
                    w2s_text[c_uc_w2s_strlen(w2s_text) - 1] = '\0';

                    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                                           WGL_CMD_EB_SET_TEXT,
                                           WGL_PACK (w2s_text),
				                           WGL_PACK (0xFFFF));
                    MENU_LOG_ON_FAIL(i4_ret);

                    MENU_LOG_ON_FAIL (menu_pm_repaint());
                    return WDK_NO_ACTION;
                }
                else
                {
                	return WZDR_OK;
                }
            }
            	break;
            default:
                break ;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
 }
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code_dlg_eb_create
 *
 * Description: used to enter 4 digit code in the manual enter code dlg
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_manual_enter_code_dlg_eb_create( VOID )
{
    INT32       i4_ret;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;

    GL_RECT_T           		t_rect;
    HANDLE_T    				h_root_frm;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_IMG_INFO_T    			t_img_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;
    UTF16_T                     w2s_cursor =(UTF16_T) 0x005F;

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

     /*create the editbox of maually enter code dlg*/
     SET_RECT_BY_SIZE(&t_rect,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_X,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_Y,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_W,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_H);

     i4_ret = c_wgl_create_widget(pt_this->t_manual_enter_code_dlg.h_dlg_frm,
                 HT_WGL_WIDGET_EDIT_BOX,
                 WGL_CONTENT_EDIT_BOX_DEF,
                 WGL_BORDER_TIMG,
                 &t_rect,
                 _menu_add_new_device_manual_enter_code_dlg_eb_fct,
                 255,
                 (VOID*)0,
                 NULL,
                 &pt_this->t_manual_enter_code_dlg.h_dlg_editbox);

    if(i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_rect.i4_left      = 0;
    t_rect.i4_right     = 0;
    t_rect.i4_top       = 0;
    t_rect.i4_bottom    = 0;
    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                           WGL_CMD_GL_SET_INSET,
                           &t_rect,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);

    /* Set txt color */
    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                           WGL_CMD_EB_ENABLE_CURSOR_HT,
                           WGL_PACK (TRUE),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                           WGL_CMD_EB_SET_CURSOR_CHAR,
                           (VOID*)(&w2s_cursor),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_EB_CURSOR),
                           WGL_PACK(& t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

	/* Set background images */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_g_menu_img_text_entry_small_1;
    t_img_info.u_img_data.t_standard.t_highlight    = h_g_menu_img_text_entry_small_1;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_menu_img_text_entry_small_1;

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                           WGL_CMD_EB_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_backsapce = BTN_KB_BACKSPACE;

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code_dlg_create
 *
 * Description: press manually enter code trigg the dlg show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_manual_enter_code_dlg_create( VOID )
{
    INT32       i4_ret;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;

    GL_RECT_T           		t_rect;
    HANDLE_T    				h_root_frm;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_IMG_INFO_T    			t_img_info;

    WGL_INSET_T t_inset = {
        8*4/3,
        8*4/3,
        3*4/3,
        0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_X,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_Y,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_W,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_H);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 NULL,
                                 255,
                                 //(VOID*) (WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                                 (VOID*) 0,
                                 0,
                                 &pt_this->t_manual_enter_code_dlg.h_dlg_frm);
    MENU_LOG_ON_FAIL(i4_ret);

     t_img_info.e_type = WGL_IMG_SET_STANDARD;
     t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bar_background;
     t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bar_background;
     t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bar_background;
     i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_frm,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

     SET_RECT_BY_SIZE(&t_rect,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_X,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_Y,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_W,
                      MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_H);

     i4_ret = c_wgl_create_widget(pt_this->t_manual_enter_code_dlg.h_dlg_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                                  NULL,
                                  &pt_this->t_manual_enter_code_dlg.h_dlg_title);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     /* Set Insets */
     i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_title,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_title,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Font */
     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
     t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
     i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_title,
                            WGL_CMD_GL_SET_FONT,
                            (void*)&t_fnt_info,
                            NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
     t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
     i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_title,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info) );
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = _menu_add_new_device_manual_enter_code_dlg_eb_create();
     MENU_LOG_ON_FAIL(i4_ret);

	/*create the yes button*/
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_X,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_Y,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_W,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_H);

    i4_ret = c_wgl_create_widget(pt_this->t_manual_enter_code_dlg.h_dlg_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _menu_add_new_device_manual_enter_code_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set text of btn Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /*create the no button*/
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_X,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_Y,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_W,
                     MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_H);

    i4_ret = c_wgl_create_widget(pt_this->t_manual_enter_code_dlg.h_dlg_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _menu_add_new_device_manual_enter_code_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &pt_this->t_manual_enter_code_dlg.h_dlg_no_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_no_btn,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set text of btn Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_no_btn,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->t_manual_enter_code_dlg.h_dlg_no_btn,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_no_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_no_btn,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility (pt_this->t_manual_enter_code_dlg.h_dlg_frm, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (pt_this->t_manual_enter_code_dlg.h_dlg_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code_dlg_show
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
static INT32 _menu_add_new_device_manual_enter_code_dlg_show(UINT16      ui2_msgid_title,
                                    UINT16      ui2_msgid_btn1,
                                    UINT16      ui2_msgid_btn2,
                                    add_dev_dlg_cb_fct  pf_back_yes,
                                    add_dev_dlg_cb_fct  pf_back_no,
                                    BOOL         b_repaint)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_yes),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_no_btn,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_no),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_yes_btn,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_btn1)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_no_btn,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_btn2)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

	c_wgl_set_focus(pt_this->t_manual_enter_code_dlg.h_dlg_editbox, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(pt_this->t_manual_enter_code_dlg.h_dlg_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        HANDLE_T  h_frm_main = NULL_HANDLE;

        i4_ret = menu_pm_get_root_frm(&h_frm_main);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(h_frm_main,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(pt_this->t_manual_enter_code_dlg.h_dlg_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code_dlg_hide
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
static INT32 _menu_add_new_device_manual_enter_code_dlg_hide(BOOL  b_repaint)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_visibility(pt_this->t_manual_enter_code_dlg.h_dlg_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_current_focus, WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->t_manual_enter_code_dlg.h_dlg_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _add_new_device_page_brand_vkb_data_change_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_brand_vkb_data_change_nfy (
    VOID*    pv_tag,
    UINT32   ui4_msg,
    VOID*    pv_param1,
    VOID*    pv_param2)
{
    INT32               i4_ret       = MENUR_OK;
    HANDLE_T			h_focus = NULL_HANDLE;
    UINT32*  pui4_key_code = (UINT32*) pv_param1;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        BOOL     b_is_top_bottom = FALSE;
        UINT8	 ui1_vkb_focus_idx = 0;
        UTF16_T             w2s_str[32+1] = {0};

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
            {
                i4_ret = a_vkb_do_cmd(pt_this->t_select_brd.h_brand_vkb,
                             VKB_CMD_GET_EB_CONTENT,
                             (VOID*)(w2s_str),
                             (VOID*) (32));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_uc_w2s_to_ps(w2s_str, pt_this->s_input_buf, 32);
                MENU_LOG_ON_FAIL(i4_ret);

				i4_ret = a_dev_db_try_to_stop_bmc_task();
				DBG_INFO(("\n####%s(%d)a_dev_db_try_to_stop_bmc_task [retrun %d]\n",__FUNCTION__,__LINE__,i4_ret));
				MENU_LOG_ON_FAIL(i4_ret);


				pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
                _add_new_device_page_show_subpage(TRUE);
                pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;

            }
                break;

            case BTN_CURSOR_UP:
            {
				i4_ret = c_wgl_get_focus(&h_focus);
				if(h_focus == pt_this->t_select_brd.h_brand_eb)
				{
					menu_set_focus_on_backbar(TRUE);
					MENU_LOG_ON_FAIL (menu_pm_repaint());
					return WDK_NO_ACTION;
				}
				else /*the curent focus is VKB*/
				{
	                /*Attached editbox is the top row */
	                ui1_vkb_focus_idx = a_vkb_current_get_row_index(pt_this->t_select_brd.h_brand_vkb);

	                if(0 == ui1_vkb_focus_idx)
	                {
	                    BOOL    b_is_visible = FALSE;

	                    c_wgl_get_visibility(pt_this->t_drop_down_lst.h_drop_down_list, &b_is_visible);
	                    if (b_is_visible == TRUE)
	                    {
	                        MENU_LOG_ON_FAIL (c_wgl_set_focus(pt_this->t_drop_down_lst.h_drop_down_list, TRUE));
	                    }
	                    else
	                    {
	                        MENU_LOG_ON_FAIL (a_vkb_set_focus_ex(pt_this->t_select_brd.h_brand_vkb));
	                    }
	                    MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                    return WDK_NO_ACTION;
	                }
	                else
	                {
						MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                	return MENUR_OK;
	                }
                }
            }
                break;

            case BTN_CURSOR_DOWN:
            {
			    BOOL				b_is_visible = FALSE;

				i4_ret = c_wgl_get_focus(&h_focus);
            	if(h_focus == pt_this->t_select_brd.h_brand_eb)
            	{
					c_wgl_get_visibility(pt_this->t_drop_down_lst.h_drop_down_list, &b_is_visible);
                    if (b_is_visible == TRUE)
                    {
                        MENU_LOG_ON_FAIL (c_wgl_set_focus(pt_this->t_drop_down_lst.h_drop_down_list, TRUE));
                    }
                    else
                    {
	            		MENU_LOG_ON_FAIL (a_vkb_set_focus(pt_this->t_select_brd.h_brand_vkb));
            		}
            		MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
            		return WDK_NO_ACTION;
            	}
            	else	/*focus on the vkb*/
            	{
	                i4_ret = a_vkb_current_is_bottom_row(pt_this->t_select_brd.h_brand_vkb,
	                                                     &pt_this->h_vkb_last_focus,
	                                                     &b_is_top_bottom);
	                if(i4_ret != WDKR_OK)
	                {
	                    return WDKR_OK;
	                }

	                if(TRUE == b_is_top_bottom)
	                {
						UINT32 		ui4_state = 0;
						c_wgl_get_state(pt_this->h_ok_btn, &ui4_state);
						if(ui4_state & WGL_STATE_ENABLED)
						{
		                    i4_ret = c_wgl_set_focus(pt_this->h_ok_btn,
		                                     WGL_SYNC_AUTO_REPAINT);
	                    }
	                    else
	                    {
		                    i4_ret = c_wgl_set_focus(pt_this->h_cancel_btn,
		                                     WGL_SYNC_AUTO_REPAINT);
	                    }
                        MENU_LOG_ON_FAIL(i4_ret);
	                    MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                    return WDK_NO_ACTION;

	                }
	                else
	                {
						MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                	return WDKR_OK;
	                }
                }
            }
                break;

			case BTN_CURSOR_LEFT:
            {
				i4_ret = c_wgl_get_focus(&h_focus);
				if(h_focus == pt_this->t_select_brd.h_brand_eb)
				{
					i4_ret = a_vkb_do_cmd(pt_this->t_select_brd.h_brand_vkb,
				                             VKB_CMD_GET_EB_CONTENT,
				                             (VOID*)(w2s_str),
				                             (VOID*) (32));
	                MENU_LOG_ON_FAIL(i4_ret);

	                w2s_str[c_uc_w2s_strlen(w2s_str)-1] = L'\0';

					a_vkb_do_cmd(pt_this->t_select_brd.h_brand_vkb,
									VKB_CMD_SET_INITIAL_TEXT,
									w2s_str,
									NULL);

					MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
					MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
					return WDK_NO_ACTION;
				}
				MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
				return MENUR_OK;

            }
                break;
            case BTN_CURSOR_RIGHT:
            {

				return MENUR_OK;
            }
                break;

            case BTN_SELECT:
            {
				i4_ret = c_wgl_get_focus(&h_focus);
            	if(h_focus == pt_this->t_select_brd.h_brand_eb)
            	{
            		i4_ret = c_wgl_set_focus(pt_this->h_ok_btn,
	                                     WGL_SYNC_AUTO_REPAINT);
					MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
                    return WDK_NO_ACTION;

            	}
            	else
				{
	                MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
	                MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                return MENUR_OK;
				}

            }
	            break;
            default :
			{
				/*support remote key input*/
				if((BTN_KB_NULL <= *pui4_key_code) && (BTN_KB_HYPER >= *pui4_key_code))
			 	{
	                MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
	                MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                return MENUR_OK;
			 	}
        	}
                break;
        }
    }
    else if (ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
    {
		switch(*pui4_key_code)
		{
	        case BTN_CURSOR_RIGHT:
	        {
				return WDK_NO_ACTION;
	        }
		        break;
	        case BTN_CURSOR_DOWN:
	        {
	            c_wgl_get_focus(&h_focus);

	            if (h_focus == pt_this->t_select_brd.h_brd_eb_del_all)
	            {
	                MENU_LOG_ON_FAIL (a_vkb_set_focus(pt_this->t_select_brd.h_brand_vkb));
	                MENU_LOG_ON_FAIL (menu_pm_repaint());
	                return WDK_NO_ACTION;
	            }

	            return MENUR_OK;
	        }
		        break;
	        case BTN_SELECT:
	        {
	            i4_ret = a_vkb_do_cmd (pt_this->t_select_brd.h_brand_vkb,
	                                   VKB_CMD_CLEAR_TEXT,
	                                  (VOID*)NULL,
	                                  (VOID*)NULL);
	            MENU_LOG_ON_FAIL(i4_ret);

	            MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
                MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	            return MENUR_OK;
	        }
		        break;
	        default:
	            break;
	    }
    }

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _add_new_device_page_model_vkb_data_change_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_model_vkb_data_change_nfy (
    VOID*    pv_tag,
    UINT32   ui4_msg,
    VOID*    pv_param1,
    VOID*    pv_param2)
{
    INT32               i4_ret       = MENUR_OK;
    UINT32*  pui4_key_code = (UINT32*) pv_param1;
    HANDLE_T			h_focus = NULL_HANDLE;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        BOOL     b_is_top_bottom = FALSE;
        UINT8	 ui1_vkb_focus_idx = 0;
        UTF16_T             w2s_str[32+1] = {0};

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
            {
                i4_ret = a_vkb_do_cmd(pt_this->t_select_model.h_model_vkb,
                             VKB_CMD_GET_EB_CONTENT,
                             (VOID*)(w2s_str),
                             (VOID*) (32));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_uc_w2s_to_ps(w2s_str, pt_this->s_input_buf, 32);
                MENU_LOG_ON_FAIL(i4_ret);

				i4_ret = a_dev_db_try_to_stop_bmc_task();
				DBG_INFO(("\n####%s(%d)a_dev_db_try_to_stop_bmc_task [retrun %d]\n",__FUNCTION__,__LINE__,i4_ret));
				MENU_LOG_ON_FAIL(i4_ret);

				pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
                _add_new_device_page_show_subpage(TRUE);
	            pt_this->h_last_focus_item = pt_this->h_list_item_device_model;
            }
                break;

            case BTN_CURSOR_UP:
            {
				i4_ret = c_wgl_get_focus(&h_focus);
				if(h_focus == pt_this->t_select_model.h_model_eb)
				{
					 menu_set_focus_on_backbar(TRUE);
					 MENU_LOG_ON_FAIL (menu_pm_repaint());
					 return WDK_NO_ACTION;
				}
				else
				{
					ui1_vkb_focus_idx = a_vkb_current_get_row_index(pt_this->t_select_model.h_model_vkb);
					/*Attached editbox is the top row */
	                if(0 == ui1_vkb_focus_idx)
	                {
	                    BOOL    b_is_visible = FALSE;

	                    c_wgl_get_visibility(pt_this->t_drop_down_lst.h_drop_down_list, &b_is_visible);
	                    if (b_is_visible == TRUE)
	                    {
	                        MENU_LOG_ON_FAIL (c_wgl_set_focus(pt_this->t_drop_down_lst.h_drop_down_list, TRUE));
	                    }
	                    else
	                    {
	                        MENU_LOG_ON_FAIL (a_vkb_set_focus_ex(pt_this->t_select_model.h_model_vkb));
	                        i4_ret = WDKR_OK;
	                    }
	                    MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                    return WDK_NO_ACTION;

	                }
	                else
	                {
	                	MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                	return MENUR_OK;
	                }
                }
            }
                break;

            case BTN_CURSOR_DOWN:
            {
				i4_ret = c_wgl_get_focus(&h_focus);
				if(h_focus == pt_this->t_select_model.h_model_eb)
				{
					 BOOL    b_is_visible = FALSE;

                    c_wgl_get_visibility(pt_this->t_drop_down_lst.h_drop_down_list, &b_is_visible);
                    if (b_is_visible == TRUE)
                    {
                        MENU_LOG_ON_FAIL (c_wgl_set_focus(pt_this->t_drop_down_lst.h_drop_down_list, TRUE));
                    }
                    else
                    {
                        MENU_LOG_ON_FAIL (a_vkb_set_focus(pt_this->t_select_model.h_model_vkb));
                    }
                    MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
                    return WDK_NO_ACTION;
				}
				else	/*the focus is vkb*/
				{
	                i4_ret = a_vkb_current_is_bottom_row(pt_this->t_select_model.h_model_vkb,
	                                                     &pt_this->h_vkb_last_focus,
	                                                     &b_is_top_bottom);
	                if(i4_ret != WDKR_OK)
	                {
	                    return WDKR_OK;
	                }

	                if(TRUE == b_is_top_bottom)
	                {
						UINT32  ui4_state = 0;
						c_wgl_get_state(pt_this->h_ok_btn, &ui4_state);
						if(ui4_state & WGL_STATE_ENABLED)
						{
		                    i4_ret = c_wgl_set_focus(pt_this->h_ok_btn,
		                                     WGL_SYNC_AUTO_REPAINT);
	                    }
	                    else
	                    {
	                       i4_ret = c_wgl_set_focus(pt_this->h_cancel_btn,
		                                     WGL_SYNC_AUTO_REPAINT);
	                    }
                        MENU_LOG_ON_FAIL(i4_ret);
	                    MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                    return WDK_NO_ACTION;
	                }
	                else
	                {
						MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                	return WDKR_OK;
	                }
                }
            }
                break;

			case BTN_CURSOR_LEFT:
            {
				HANDLE_T h_focus = NULL_HANDLE;

				i4_ret = c_wgl_get_focus(&h_focus);
				if(h_focus == pt_this->t_select_model.h_model_eb)
				{
					i4_ret = a_vkb_do_cmd(pt_this->t_select_model.h_model_vkb,
				                             VKB_CMD_GET_EB_CONTENT,
				                             (VOID*)(w2s_str),
				                             (VOID*) (32));
	                MENU_LOG_ON_FAIL(i4_ret);

	                w2s_str[c_uc_w2s_strlen(w2s_str)-1] = L'\0';

					a_vkb_do_cmd(pt_this->t_select_model.h_model_vkb,
									VKB_CMD_SET_INITIAL_TEXT,
									w2s_str,
									NULL);

					MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
					MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	                return WDK_NO_ACTION;
				}
				MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
                return MENUR_OK;
            }
                break;

			case BTN_CURSOR_RIGHT:
            {
				return MENUR_OK;
            }
                break;
            case BTN_SELECT:
            {
				i4_ret = c_wgl_get_focus(&h_focus);
            	if(h_focus == pt_this->t_select_model.h_model_eb)
            	{
            		i4_ret = c_wgl_set_focus(pt_this->h_ok_btn,
	                                     WGL_SYNC_AUTO_REPAINT);
					MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
                    return WDK_NO_ACTION;

            	}
            	else
            	{
	                MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
	                MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));

	                return MENUR_OK;
                }
            }
	            break;
            default :
			{
				/*support remote key input*/
				if((BTN_KB_NULL <= *pui4_key_code) && (BTN_KB_HYPER >= *pui4_key_code))
				{
					MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
					MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
					return MENUR_OK;
				}
			}
                break;
        }
    }
	else if (ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
    {
		switch(*pui4_key_code)
		{
	        case BTN_CURSOR_RIGHT:
	        {
				return WDK_NO_ACTION;
	        }
		        break;
	        case BTN_CURSOR_DOWN:
	        {
	            c_wgl_get_focus(&h_focus);

	            if (h_focus == pt_this->t_select_model.h_model_eb_del_all)
	            {
	                MENU_LOG_ON_FAIL (a_vkb_set_focus(pt_this->t_select_model.h_model_vkb));
	                MENU_LOG_ON_FAIL (menu_pm_repaint());
	                return WDK_NO_ACTION;
	            }

	            return MENUR_OK;
	        }
		        break;
	        case BTN_SELECT:
	        {
	            i4_ret = a_vkb_do_cmd (pt_this->t_select_model.h_model_vkb,
	                                   VKB_CMD_CLEAR_TEXT,
	                                  (VOID*)NULL,
	                                  (VOID*)NULL);
	            MENU_LOG_ON_FAIL(i4_ret);

	            MENU_LOG_ON_FAIL (_menu_add_new_device_drop_down_lb_update(FALSE));
                MENU_LOG_ON_FAIL (c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE));
	            return MENUR_OK;
	        }
		        break;
	        default:
	            break;
	    }
    }
    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 *	_menu_add_new_device_dlg_hide_timer_fct *
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static VOID _menu_add_new_device_dlg_hide_timer_fct(
									    VOID* pv_data,
									    SIZE_T  z_data_size)
{

	INT32       i4_ret = MENUR_OK;

    i4_ret = _menu_add_new_device_custom_dialog_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    return;

}
/*-----------------------------------------------------------------------------
_menu_add_new_device_custom_dialog_hide_timer_nfy *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static VOID _menu_add_new_device_custom_dialog_hide_timer_nfy(HANDLE_T        h_timer,
				                                               VOID*           pv_tag)
{
    INT32       i4_ret = MENUR_OK;

    i4_ret = menu_async_invoke(_menu_add_new_device_dlg_hide_timer_fct, NULL, 0, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    return;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_custom_dialog_hide_timer_start
 *
 * Description:
 *      start the timer of show confirm dialog for menu device setup.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/

static INT32 _menu_add_new_device_custom_dialog_hide_timer_start(UINT32    ui4_time)
{
	INT32                       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;

    if (NULL_HANDLE != pt_this->t_confirm_dlg.h_hide_timer)
    {
        i4_ret = c_timer_start(pt_this->t_confirm_dlg.h_hide_timer,
                              ui4_time,
                              X_TIMER_FLAG_ONCE,
                              _menu_add_new_device_custom_dialog_hide_timer_nfy,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

	return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_custom_dialog_show
 *
 * Description:
 *      Show the confirm dialog after enter the main subpage of menu device setup.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_custom_dialog_show(VOID)
{
    INT32                       		i4_ret  = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;
    UTF16_T     w2s_str[128] = {0};
    UTF16_T     w2s_brand[32] = {0};
    UTF16_T     w2s_model[32] = {0};
    UTF16_T     w2s_type[32] = {0};
    CHAR        s_space[8] = {0};
    UTF16_T     w2s_space[8] = {0};

    c_sprintf(s_space, "  ");
    c_uc_ps_to_w2s(s_space, w2s_space, 8);

	c_uc_ps_to_w2s(pt_this->s_brd_name, w2s_brand, 32);
	c_uc_ps_to_w2s(pt_this->s_model_name, w2s_model, 32);
	c_uc_w2s_strncpy(w2s_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].pw2s_txt_msg, 32);

    c_uc_w2s_strcpy(w2s_str,MENU_TEXT(MLM_MENU_KEY_DEVICE_SETUP_CONFIRM_DLG_MSG_START));
    c_uc_w2s_strcat(w2s_str,w2s_space);
    c_uc_w2s_strcat(w2s_str,w2s_brand);
    c_uc_w2s_strcat(w2s_str,w2s_space);
    c_uc_w2s_strcat(w2s_str,w2s_model);
    c_uc_w2s_strcat(w2s_str,w2s_space);
    c_uc_w2s_strcat(w2s_str,w2s_type);
    c_uc_w2s_strcat(w2s_str,w2s_space);

    c_uc_w2s_strcat(w2s_str,MENU_TEXT(MLM_MENU_KEY_DEVICE_SETUP_CONFIRM_DLG_MSG_END));

    if((pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)||(pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX))
    {
	    c_uc_w2s_strcat(w2s_str,MENU_TEXT(MLM_MENU_KEY_DEVICE_SETUP_CONFIRM_DLG_MSG_END_AUDIO));
    }

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->t_confirm_dlg.h_dialog, w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_get_focus(&pt_this->t_confirm_dlg.h_menu_current_focus);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_focus(pt_this->t_confirm_dlg.h_dialog, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_show(pt_this->t_confirm_dlg.h_dialog);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->t_confirm_dlg.h_parent, NULL, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_custom_dialog_hide_timer_start(pt_this->t_confirm_dlg.ui4_timer_delay);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_this->t_confirm_dlg.b_is_show = TRUE;

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _menu_add_new_device_custom_dialog_hide
 * Description:
 *      hide menu custom dialog
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_custom_dialog_hide(VOID)
{
    INT32                       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;

    if ((TRUE == pt_this->t_confirm_dlg.b_is_show)&&
        (NULL_HANDLE != pt_this->t_confirm_dlg.h_dialog))
    {
        i4_ret = a_ui_simple_dialog_hide(pt_this->t_confirm_dlg.h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_hide(pt_this->t_confirm_dlg.h_dialog);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_ui_simple_dialog_repaint(pt_this->t_confirm_dlg.h_parent);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->t_confirm_dlg.b_is_show   = FALSE;

        /* stop the timer */
        i4_ret = c_timer_stop(pt_this->t_confirm_dlg.h_hide_timer);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_custom_dialog_init
 *
 * Description:
 *      Initialize the custom dialog under menu device setup.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_custom_dialog_init(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;


    if (!pt_this->t_confirm_dlg.b_is_inited)
    {
        c_memset(&pt_this->t_confirm_dlg, 0, sizeof(_MENU_CUSTOM_DLG_DATA_T));

        pt_this->t_confirm_dlg.ui4_timer_delay = MENU_ADD_NEW_DEVICE_DIALOG_DELAY;

        i4_ret = menu_pm_get_root_frm(&pt_this->t_confirm_dlg.h_parent);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_timer_create(&pt_this->t_confirm_dlg.h_hide_timer);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_this->t_confirm_dlg.b_is_inited = TRUE;
    }

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_it_work_btn_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_it_work_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    //HANDLE_T                        h_cb_widget;
    //WGL_NOTIFY_DATA_T*              pt_wgl_nfy_data;
    INT32							i4_ret = WDKR_OK;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;
    ADD_NEW_DEVICE_PAGE_ENTER_FROM_T        e_enter_from = ADD_NEW_DEVICE_PAGE_ENTERN_FROM_NORMAL;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  /* set focus to try next remote code button */
        {
			UINT32	ui4_state = 0;
			c_wgl_get_state(pt_this->t_remote_code.h_try_next_btn, &ui4_state);
			if(ui4_state & WGL_STATE_ENABLED)
			{
				c_wgl_set_focus(pt_this->t_remote_code.h_try_next_btn, WGL_SYNC_AUTO_REPAINT);
			}
			else
			{
				c_wgl_set_focus(pt_this->t_remote_code.h_manual_enter_code_btn, WGL_SYNC_AUTO_REPAINT);
			}
        }
        if( BTN_CURSOR_UP== (UINT32)pv_param1 )  /*  */
        {
			menu_set_focus_on_backbar(TRUE);
			MENU_LOG_ON_FAIL (menu_pm_repaint());
        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /* return to the device setup screen and show dialog box if the device can power off after press the power key */
        {
			if(pt_this->ui1_codeset_num>=1)
			{
	            i4_ret = _menu_add_new_device_custom_dialog_show();
	            MENU_LOG_ON_FAIL(i4_ret);

	            pt_this->b_is_setup_worked = TRUE;
            }

			menu_set_power_off_flag(FALSE);

			_add_new_device_page_reset_dev_info();

			menu_device_page_add_new_device_enter_from_get(&e_enter_from);
			if (ADD_NEW_DEVICE_PAGE_ENTERN_FROM_AUDIO_MODE_SETUP == e_enter_from)
		    {
		        pt_this->h_last_focus_item = pt_this->h_list_item_device_type_aud;
		        pt_this->ui4_type_sel_idx = MENU_SETUP_AVR_AMP_IDX;
		    }
		    else
		    {
			    pt_this->h_last_focus_item = pt_this->h_list_item_device_type;
			    pt_this->ui4_type_sel_idx = DEVICE_TYPE_UNKNOWN;
		    }
			pt_this->e_pre_subpage = pt_this->e_subpage;
            pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
			i4_ret = _add_new_device_page_show_subpage(TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            MENU_LOG_ON_FAIL (menu_pm_repaint());
            return 0;
        }
        if( BTN_RETURN == (UINT32)pv_param1 )
        {
        	_back_key_handler();
            return WGLR_OK;
        }

    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name:_menu_add_new_device_do_try_next_code_without_sel_mdl
 *
 * Description:call this function if the end user select the button of I Don't Know  the Model.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _menu_add_new_device_do_try_next_code_without_sel_mdl(VOID)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32       i4_ret = 0;
    ISL_REC_T                                 t_isl_rec;
    CHAR                                      str_type[DEV_DB_NAME_LEN_MAX+1]="";
    UINT8                                     ui1_src_idx;
    BOOL                                      b_is_src_id_valid = FALSE;
	c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

    if (pt_this->ui1_cur_code_pos < pt_this->ui1_codeset_num)
    {
        if (pt_this->ui1_cur_code_pos > (MENU_ADD_NEW_DEVICE_CODESET_MAX_NUM-1)) /* Klocwork*/
        {
            return ;
        }
        pt_this->b_is_setup_worked = FALSE;


        if (pt_this->ui1_select_input != 0xFF)
        {
            ui1_src_idx = pt_this->aui1_input_src_id[pt_this->ui1_select_input];
            a_isl_get_rec_by_idx(ui1_src_idx, &t_isl_rec);
            b_is_src_id_valid = TRUE;
        }
        else
        {
            b_is_src_id_valid = FALSE;
        }

        _menu_add_new_device_list_codeset(pt_this->ui1_cur_code_pos);	/*get the pt_this->codeset of index =ui1_cur_code_pos*/

		i4_ret = _menu_add_new_device_setup_save_and_upload_codeset(pt_this->ui1_cur_code_pos);
		DBG_INFO(("%s(%d)[menu_dev_db] _menu_add_new_device_setup_save_and_upload_codeset(), i4_ret[%d]!,pt_this->ui1_cur_code_pos=%d,pt_this->s_codeset=%s\n",__FUNCTION__,__LINE__,i4_ret,pt_this->ui1_cur_code_pos,pt_this->s_codeset));

        if(pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
		{
			if(pt_this->ui1_cur_code_pos < pt_this->pt_codeset_list->t_codeset_list1.i4_length)
			{
				c_strncpy(str_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_DB_NAME_LEN_MAX);
			}
			else
			{
				c_strncpy(str_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_DB_NAME_LEN_MAX);
			}
		}
		else
		{
			c_strncpy(str_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_DB_NAME_LEN_MAX);
		}

        if (b_is_src_id_valid)
        {
            a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
            str_type,
            pt_this->s_brd_name,
            pt_this->s_model_name,
            pt_this->s_codeset);

            a_tv_net_custom_set_codeset(pt_this->s_codeset);
        }
        else
        {
            UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
            UINT16  ui2_aud_out_mask;
            INT16   i2_val;

            a_cfg_custom_set_device_info(0,
            str_type,
            pt_this->s_brd_name,
            pt_this->s_model_name,
            pt_this->s_codeset);

            /*turn off TV speaker*/
            a_cfg_av_get(ui2_id, &i2_val);
            ui2_aud_out_mask = (UINT16)i2_val;

            if( (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) )
            {
                /* Off */
                ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

                a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
                a_cfg_av_update(ui2_id);
            }
            /* set audio ctrl flag to AUD_CONTROL_EXTERNAL */
			a_cfg_custom_set_vol_control(1);

			/* set sb_enable and sb codeset */
			a_tv_net_custom_set_soundbar_flag(TRUE);
			a_tv_net_custom_set_soundbar_codeset(pt_this->s_codeset);
        }

        pt_this->ui1_cur_code_pos ++;
		_menu_add_new_device_confirm_code_chang_lang(TRUE);

        pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
        _add_new_device_page_show_subpage(TRUE);
        pt_this->b_is_codeset_querying = FALSE;
        c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn, WGL_SYNC_AUTO_REPAINT);

    }//end if(pt_this->ui1_cur_code_pos < pt_this->ui1_codeset_num)
    c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn, WGL_SYNC_AUTO_REPAINT);

    if(pt_this->ui1_cur_code_pos >= pt_this->ui1_codeset_num)
    {
    	DBG_INFO(("\n####%s(%d)pos = num \n",__FUNCTION__,__LINE__));
		INT32	i4_ret = 0;
    	i4_ret = c_wgl_enable(pt_this->t_remote_code.h_try_next_btn, FALSE);
    	DBG_INFO(("\n####%s(%d)disable try next button i4_ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
		c_wgl_repaint(pt_this->t_remote_code.h_try_next_btn,NULL,TRUE);
    }
}
/*----------------------------------------------------------------------------
 * Name:_menu_add_new_device_do_try_next_code
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
static VOID _menu_add_new_device_do_try_next_code(VOID)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32       i4_ret = 0;
    ISL_REC_T                                 t_isl_rec;
    CHAR                                      str_type[DEV_DB_NAME_LEN_MAX+1]="";
    UINT8                                     ui1_src_idx;
    BOOL                                      b_is_src_id_valid = FALSE;
	c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

    if (pt_this->ui1_cur_code_pos < pt_this->ui1_codeset_num)
    {
        if (pt_this->ui1_cur_code_pos > (MENU_ADD_NEW_DEVICE_CODESET_MAX_NUM-1)) /* Klocwork*/
        {
            return ;
        }
        pt_this->b_is_setup_worked = FALSE;

		/* current only support two max codeset*/
        if (2 == pt_this->ui1_codeset_num)
        {
            if (NULL != pt_this->pt_codeset->c_codeset2)
            {
                if (pt_this->ui1_select_input != 0xFF)
                {
                    ui1_src_idx = pt_this->aui1_input_src_id[pt_this->ui1_select_input];
                    a_isl_get_rec_by_idx(ui1_src_idx, &t_isl_rec);
                    b_is_src_id_valid = TRUE;
                }
                else
                {
                    b_is_src_id_valid = FALSE;
                }

                i4_ret = a_dev_db_upload_codeset_ex(pt_this->pt_codeset->c_codeset2);

                DBG_INFO(("[####%s(%d)] a_dev_db_upload_codeset(), i4_ret[%d]!\n",__FUNCTION__,__LINE__,i4_ret));

    			if(pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
				{
					c_strncpy(str_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_DB_NAME_LEN_MAX);
				}
				else
				{
					c_strncpy(str_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_DB_NAME_LEN_MAX);
				}

                c_strncpy(pt_this->s_codeset, pt_this->pt_codeset->c_codeset2, 5);

                if (b_is_src_id_valid)
                {
                    a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
                    str_type,
                    pt_this->s_brd_name,
                    pt_this->s_model_name,
                    pt_this->s_codeset);

                    a_tv_net_custom_set_codeset(pt_this->s_codeset);
                }
                else
                {
                    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
                    UINT16  ui2_aud_out_mask;
                    INT16   i2_val;

                    a_cfg_custom_set_device_info(0,
                    str_type,
                    pt_this->s_brd_name,
                    pt_this->s_model_name,
                    pt_this->s_codeset);

                    /*turn off TV speaker*/
                    a_cfg_av_get(ui2_id, &i2_val);
                    ui2_aud_out_mask = (UINT16)i2_val;

                    if( (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) )
                    {
                        /* Off */
                        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

                        a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
                        a_cfg_av_update(ui2_id);
                    }
                    /* set audio ctrl flag to AUD_CONTROL_EXTERNAL */
					a_cfg_custom_set_vol_control(1);

					/* set sb_enable and sb codeset */
					a_tv_net_custom_set_soundbar_flag(TRUE);
					a_tv_net_custom_set_soundbar_codeset(pt_this->s_codeset);
                }

                pt_this->ui1_cur_code_pos ++;
				_menu_add_new_device_confirm_code_chang_lang(TRUE);

                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
                _add_new_device_page_show_subpage(TRUE);
                pt_this->b_is_codeset_querying = FALSE;
	            c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn, WGL_SYNC_AUTO_REPAINT);

	            return;

            }//end if (NULL != pt_this->pt_codeset->c_codeset2)

        }//end if(2 == pt_this->ui1_codeset_num)
        pt_this->ui1_cur_code_pos ++;
        _menu_add_new_device_confirm_code_chang_lang(TRUE);

    }//end if(pt_this->ui1_cur_code_pos < pt_this->ui1_codeset_num)
    c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn, WGL_SYNC_AUTO_REPAINT);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code_btn_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_manual_enter_code_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    //HANDLE_T                        h_cb_widget;
    //WGL_NOTIFY_DATA_T*              pt_wgl_nfy_data;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;
    INT32			i4_ret = MENUR_OK;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  /*  */
        {
            menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
            menu_pm_repaint();
        }
        if( BTN_CURSOR_UP== (UINT32)pv_param1 )  /*  */
        {
			UINT32	ui4_state = 0;

			c_wgl_get_state(pt_this->t_remote_code.h_try_next_btn, &ui4_state);
			if(ui4_state & WGL_STATE_ENABLED)
			{
	        	c_wgl_set_focus(pt_this->t_remote_code.h_try_next_btn, WGL_SYNC_AUTO_REPAINT);
        	}
        	else
        	{
	        	c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn, WGL_SYNC_AUTO_REPAINT);
        	}
        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /*  */
        {
            i4_ret = c_wgl_get_focus(&pt_this->h_current_focus);
		    MENU_LOG_ON_FAIL(i4_ret);

		    i4_ret = _menu_add_new_device_manual_enter_code_dlg_show(MLM_MENU_KEY_DEVICE_MANUAL_ENTER_CODE_DLG_TITLE,
												    MLM_MENU_KEY_OK,
				                                    MLM_MENU_KEY_CNCL,
				                                    _menu_add_new_device_manual_enter_code_dlg_btn_yes_fct,
				                                    _menu_add_new_device_manual_enter_code_dlg_btn_no_fct,
				                                    TRUE);
            MENU_LOG_ON_FAIL(i4_ret);

            return WGLR_OK;
        }
        if( BTN_RETURN == (UINT32)pv_param1 )
        {
        	_back_key_handler();
            return WGLR_OK;
        }

    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_try_next_btn_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_try_next_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    //HANDLE_T                        h_cb_widget;
    //WGL_NOTIFY_DATA_T*              pt_wgl_nfy_data;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  /*  */
        {
            c_wgl_set_focus(pt_this->t_remote_code.h_manual_enter_code_btn, WGL_SYNC_AUTO_REPAINT);
        }
        if( BTN_CURSOR_UP== (UINT32)pv_param1 )  /*  */
        {
        	c_wgl_set_focus(pt_this->t_remote_code.h_it_work_btn, WGL_SYNC_AUTO_REPAINT);
        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /*  */
        {
			if((pt_this->b_is_i_do_not_know_mdl_sel)||
			   ((pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX)&&(c_strcmp(pt_this->s_brd_name, "VIZIO")==0)))
			{
				_menu_add_new_device_do_try_next_code_without_sel_mdl();
			}
			else
			{
				_menu_add_new_device_do_try_next_code();
			}
            return 0;
        }
        if( BTN_RETURN == (UINT32)pv_param1 )
        {
        	_back_key_handler();
            return WGLR_OK;
        }

    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_manual_enter_code
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_manual_enter_code ()
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    UINT8               ui1_src_idx;
    ISL_REC_T           t_isl_rec;
    CHAR        		s_src_type[DEV_DB_NAME_LEN_MAX+1] = {0};
    INT32       		i4_ret = MENUR_OK;
    UTF16_T             w2s_text[DEV_DB_NAME_LEN_MAX + 1] = {0};

	c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
	pt_this->b_is_setup_worked = FALSE;
	i4_ret = c_wgl_do_cmd(pt_this->t_manual_enter_code_dlg.h_dlg_editbox,
				          WGL_CMD_EB_GET_TEXT,
				          WGL_PACK(w2s_text),
				          WGL_PACK(DEV_DB_NAME_LEN_MAX));
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_to_ps(w2s_text,pt_this->s_codeset, 32);
    DBG_INFO(("\n####%s(%d)pt_this->s_codeset=%s\n",__FUNCTION__,__LINE__,pt_this->s_codeset));

	i4_ret = a_dev_db_manual_upload_codeset(pt_this->ui4_type_sel_idx, pt_this->s_codeset, (DEV_SETUP_DB_CODESET_LEN_MAX+1));

    DBG_INFO(("\n[####%s(%d)]------a_dev_db_manual_upload_codeset() return:%d ,pt_this->s_codeset=%s-------\n", __FUNCTION__,__LINE__,i4_ret,pt_this->s_codeset));

	if(pt_this->ui4_type_sel_idx == MENU_SETUP_AVR_AMP_IDX)
	{
		/* set the device type Audio Receiver */
		if((c_strncmp(pt_this->s_codeset,"M",1)==0)||(c_strncmp(pt_this->s_codeset,"R",1)==0))
		{
			c_strncpy(s_src_type, DEV_DB_TYPE_RECEIVER_MISC_AUDIO_NAME, DEV_DB_NAME_LEN_MAX);
		}
		/* set the device type Amplifier */
		else if(c_strncmp(pt_this->s_codeset,"A",1)==0)
		{
			c_strncpy(s_src_type, DEV_DB_TYPE_AMPLIFIER_NAME, DEV_DB_NAME_LEN_MAX);
		}
	}
	else
	{
		c_strncpy(s_src_type, pt_this->t_dev_type[pt_this->ui4_type_sel_idx].s_dev_view_name, DEV_DB_NAME_LEN_MAX);
	}

    if (pt_this->ui1_select_input!= 0xFF)
    {
    	a_tv_net_custom_set_codeset(pt_this->s_codeset);

        ui1_src_idx = pt_this->aui1_input_src_id[pt_this->ui1_select_input];
        a_isl_get_rec_by_idx(ui1_src_idx, &t_isl_rec);

        a_cfg_custom_set_device_info(t_isl_rec.ui1_id,
            s_src_type,
            pt_this->s_brd_name,
            pt_this->s_model_name,
            pt_this->s_codeset);
    }
    else
    {
        UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
        UINT16  ui2_aud_out_mask = 0;
        INT16   i2_val = 0;

        /*turn off TV speaker*/
        a_cfg_av_get(ui2_id, &i2_val);
        ui2_aud_out_mask = (UINT16)i2_val;

        if( (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) )
        {
            /* Off */
            ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

            a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
            a_cfg_av_update(ui2_id);
        }

        a_cfg_custom_set_device_info(0,
            s_src_type,
            pt_this->s_brd_name,
            pt_this->s_model_name,
            pt_this->s_codeset);

        /*turn off TV speaker*/
        a_cfg_av_get(ui2_id, &i2_val);
        ui2_aud_out_mask = (UINT16)i2_val;

        if( (ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER) )
        {
            /* Off */
            ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);

            a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
            a_cfg_av_update(ui2_id);
        }

    	/* set audio ctrl flag to AUD_CONTROL_EXTERNAL */
		a_cfg_custom_set_vol_control(1);

		/* set sb_enable and sb codeset */
    	a_tv_net_custom_set_soundbar_flag(TRUE);
		a_tv_net_custom_set_soundbar_codeset(pt_this->s_codeset);
    }

    return 0;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_ok_btn_proc_fct
 *
 * Description: OK button cb fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_ok_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    //HANDLE_T                        h_cb_widget;
    //WGL_NOTIFY_DATA_T*              pt_wgl_nfy_data;
    INT32							i4_ret = WDKR_OK;
    UTF16_T             			w2s_str[32+1] = {0};

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  /*  */
        {
            i4_ret = c_wgl_set_focus(pt_this->h_cancel_btn, WGL_SYNC_AUTO_REPAINT);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        if( BTN_CURSOR_UP== (UINT32)pv_param1 )  /*  */
        {
			if(pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
			{
				i4_ret = a_vkb_set_focus(pt_this->t_select_brd.h_brand_vkb);
	            MENU_LOG_ON_FAIL(i4_ret);

			}
			else if(pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
			{
				i4_ret = a_vkb_set_focus(pt_this->t_select_model.h_model_vkb);
	            MENU_LOG_ON_FAIL(i4_ret);
			}

            c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /*  */
        {
            if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
	        {
				i4_ret = a_vkb_do_cmd(pt_this->t_select_brd.h_brand_vkb,
                                  VKB_CMD_GET_EB_CONTENT,
                                  (VOID*) w2s_str,
                                  (VOID*) (UINT32) MENU_ADD_NEW_DEVICE_EB_TXT_MAX_LEN);
	            MENU_LOG_ON_FAIL(i4_ret);

		        c_uc_w2s_to_ps(w2s_str,pt_this->s_brd_name , 32);

				pt_this->b_is_brd_sel = TRUE;
	            pt_this->e_pre_subpage = pt_this->e_subpage;
				if((pt_this->ui4_type_sel_idx == MENU_SETUP_SOUND_BAR_IDX)&&(c_strcmp(pt_this->s_brd_name, "VIZIO")==0))
				{
					pt_this->h_last_focus_item = pt_this->h_list_item_confirm_remote_connect;
				}
				else
				{
					pt_this->h_last_focus_item = pt_this->h_list_item_device_model;
				}
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
	            i4_ret = _add_new_device_page_show_subpage(TRUE);
	            MENU_LOG_ON_FAIL(i4_ret);

	            i4_ret = a_vkb_do_cmd(pt_this->t_select_brd.h_brand_vkb,
                                  VKB_CMD_CLEAR_TEXT,
                                  (VOID*) NULL,
                                  (VOID*) NULL);
	            MENU_LOG_ON_FAIL(i4_ret);
	        }
	        else if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
	        {
				i4_ret = a_vkb_do_cmd(pt_this->t_select_model.h_model_vkb,
                                  VKB_CMD_GET_EB_CONTENT,
                                  (VOID*) w2s_str,
                                  (VOID*) (UINT32) MENU_ADD_NEW_DEVICE_EB_TXT_MAX_LEN);
	            MENU_LOG_ON_FAIL(i4_ret);

				c_uc_w2s_to_ps(w2s_str,pt_this->s_model_name , 32);

				pt_this->b_is_mdl_sel = TRUE;
	            pt_this->e_pre_subpage = pt_this->e_subpage;
	            pt_this->h_last_focus_item = pt_this->h_list_item_confirm_remote_connect;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
	            i4_ret = _add_new_device_page_show_subpage(TRUE);
	            MENU_LOG_ON_FAIL(i4_ret);

	            i4_ret = a_vkb_do_cmd(pt_this->t_select_model.h_model_vkb,
                                  VKB_CMD_CLEAR_TEXT,
                                  (VOID*) NULL,
                                  (VOID*) NULL);
	            MENU_LOG_ON_FAIL(i4_ret);
	        }
            MENU_LOG_ON_FAIL (menu_pm_repaint());
            return 0;
        }
        else if(BTN_RETURN == (UINT32)pv_param1)
        {
        	if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
        	{
				i4_ret = a_dev_db_try_to_stop_bmc_task();
				DBG_INFO(("\n####%s(%d)a_dev_db_try_to_stop_bmc_task [retrun %d]\n",__FUNCTION__,__LINE__,i4_ret));
				MENU_LOG_ON_FAIL(i4_ret);

				pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
                _add_new_device_page_show_subpage(TRUE);
                pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;
        	}
        	else if(pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
        	{
        		i4_ret = a_dev_db_try_to_stop_bmc_task();
				DBG_INFO(("\n####%s(%d)a_dev_db_try_to_stop_bmc_task [retrun %d]\n",__FUNCTION__,__LINE__,i4_ret));
				MENU_LOG_ON_FAIL(i4_ret);

				pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
                _add_new_device_page_show_subpage(TRUE);
	            pt_this->h_last_focus_item = pt_this->h_list_item_device_model;
        	}
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_cancel_btn_proc_fct
 *
 * Description: OK button cb fct
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_cancel_btn_proc_fct (
                                HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    //HANDLE_T                        h_cb_widget;
    //WGL_NOTIFY_DATA_T*              pt_wgl_nfy_data;
    INT32							i4_ret = WDKR_OK;
    UTF16_T             			w2s_str[32+1] = {0};

    //h_cb_widget     = (HANDLE_T) pv_param1;
    //pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if( ui4_msg == WGL_MSG_KEY_DOWN )
    {
        if( BTN_CURSOR_DOWN == (UINT32)pv_param1 )  /*  */
        {
			menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
			menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
            menu_pm_repaint();
        }
        if( BTN_CURSOR_UP== (UINT32)pv_param1 )  /*  */
        {
			UINT32		ui4_state = 0;

			c_wgl_get_state(pt_this->h_ok_btn, &ui4_state);
			if(ui4_state & WGL_STATE_ENABLED)
			{
	            c_wgl_set_focus(pt_this->h_ok_btn,
                                 WGL_SYNC_AUTO_REPAINT);
            }
            else
            {
				if(pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
				{
					i4_ret = a_vkb_set_focus(pt_this->t_select_brd.h_brand_vkb);
		            MENU_LOG_ON_FAIL(i4_ret);

				}
				else if(pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
				{
					i4_ret = a_vkb_set_focus(pt_this->t_select_model.h_model_vkb);
		            MENU_LOG_ON_FAIL(i4_ret);
				}
                c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
            }

        }
        if( BTN_SELECT == (UINT32)pv_param1 )  /*  */
        {
            if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
	        {
	            i4_ret = a_vkb_do_cmd(pt_this->t_select_brd.h_brand_vkb,
                                  VKB_CMD_CLEAR_TEXT,
                                  (VOID*) NULL,
                                  (VOID*) NULL);
	            MENU_LOG_ON_FAIL(i4_ret);

	            i4_ret = a_vkb_do_cmd(pt_this->t_select_brd.h_brand_vkb,
                                  VKB_CMD_GET_EB_CONTENT,
                                  (VOID*) w2s_str,
                                  (VOID*) (UINT32) MENU_ADD_NEW_DEVICE_EB_TXT_MAX_LEN);
	            MENU_LOG_ON_FAIL(i4_ret);

		        c_uc_w2s_to_ps(w2s_str,pt_this->s_brd_name , 32);
	            DBG_INFO(("\n####%s(%d) pt_this->s_brd_name = %s\n",__FUNCTION__,__LINE__,pt_this->s_brd_name));

				pt_this->b_is_brd_sel = FALSE;
	            pt_this->e_pre_subpage = pt_this->e_subpage;
	            pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
	            i4_ret = _add_new_device_page_show_subpage(TRUE);
	            MENU_LOG_ON_FAIL(i4_ret);

	        }
	        else if (pt_this->e_subpage== ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
	        {

#ifdef APP_UEI_SPINNER_SUPPORT
	        	/*anyway,show confirm page first*/
				_menu_add_new_device_confirm_code_chang_lang(TRUE);
				pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
				_add_new_device_page_show_subpage(TRUE);

				i4_ret = menu_page_animation_start(1, FALSE);
				MENU_LOG_ON_FAIL(i4_ret);

				i4_ret = menu_page_animation_show();
				MENU_LOG_ON_FAIL(i4_ret);
				pt_this->b_animation = TRUE;
#endif
				pt_this->b_is_i_do_not_know_mdl_sel = TRUE;		/*the I Don't Know the Model is selected*/
	            i4_ret = a_vkb_do_cmd(pt_this->t_select_model.h_model_vkb,
                                  VKB_CMD_CLEAR_TEXT,
                                  (VOID*) NULL,
                                  (VOID*) NULL);
	            MENU_LOG_ON_FAIL(i4_ret);

				i4_ret = a_vkb_do_cmd(pt_this->t_select_model.h_model_vkb,
                                  VKB_CMD_GET_EB_CONTENT,
                                  (VOID*) w2s_str,
                                  (VOID*) (UINT32) MENU_ADD_NEW_DEVICE_EB_TXT_MAX_LEN);
	            MENU_LOG_ON_FAIL(i4_ret);

				c_uc_w2s_to_ps(w2s_str,pt_this->s_model_name , 32);

				pt_this->b_is_mdl_sel = FALSE;
	            pt_this->e_pre_subpage = pt_this->e_subpage;

	            if (pt_this->b_is_codeset_querying)
	            {
	                return 0;
	            }
	            else
	            {
	                if(pt_this->b_is_i_do_not_know_mdl_sel)
	                {
		                i4_ret = a_dev_db_clean_codeset_list();
					    DBG_INFO(("####%s(%d) a_dev_db_clean_codeset_list() return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
		                i4_ret = _menu_add_new_device_setup_codesetlist_update(FALSE);
		                DBG_INFO(("\n####%s(%d)codesetlist update i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	                }
	                MENU_LOG_ON_FAIL(i4_ret);
	                if  (MENUR_OK != i4_ret)
	                {
						_menu_add_new_device_confirm_code_chang_lang(TRUE);
	                    pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT;
		                _add_new_device_page_show_subpage(TRUE);

	                    pt_this->b_is_codeset_querying = FALSE;

#ifdef APP_UEI_SPINNER_SUPPORT
						/*hide spinner after get codeset for confirm remote conection page*/
						_add_device_animation_stop();
						DBG_INFO(("\n####%s(%d)confirm page show\n",__FUNCTION__,__LINE__));
#endif
	                }
	                else
	                {
	                    pt_this->b_is_codeset_querying = TRUE;
	                }

					/* chang input source after select input source*/
				    if((pt_this->ui4_type_sel_idx != MENU_SETUP_AVR_AMP_IDX)&&(pt_this->ui4_type_sel_idx != MENU_SETUP_SOUND_BAR_IDX) )
		            {
		                i4_ret = _menu_add_new_device_change_input_src();
		                MENU_LOG_ON_FAIL(i4_ret);
		            }

	            }

	        }
            MENU_LOG_ON_FAIL (menu_pm_repaint());
            return 0;
        }
        else if(BTN_RETURN == (UINT32)pv_param1)
        {
        	if (pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
        	{
				i4_ret = a_dev_db_try_to_stop_bmc_task();
				DBG_INFO(("\n####%s(%d)a_dev_db_try_to_stop_bmc_task [retrun %d]\n",__FUNCTION__,__LINE__,i4_ret));
				MENU_LOG_ON_FAIL(i4_ret);

				pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
                _add_new_device_page_show_subpage(TRUE);
                pt_this->h_last_focus_item = pt_this->h_list_item_device_brand;
        	}
        	else if(pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL)
        	{
        		i4_ret = a_dev_db_try_to_stop_bmc_task();
				DBG_INFO(("\n####%s(%d)a_dev_db_try_to_stop_bmc_task [retrun %d]\n",__FUNCTION__,__LINE__,i4_ret));
				MENU_LOG_ON_FAIL(i4_ret);

				pt_this->e_pre_subpage = pt_this->e_subpage;
                pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;
                _add_new_device_page_show_subpage(TRUE);
	            pt_this->h_last_focus_item = pt_this->h_list_item_device_model;
        	}
        }
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _add_new_device_page_brand_vkb_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_brand_vkb_create(VOID)
{
    INT32       i4_ret = MENUR_OK;

    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    VKB_INIT_T          				t_init_data;
    GL_RECT_T                           t_rect;
    WGL_INSET_T             			t_inset;
    WGL_FONT_INFO_T         			t_fnt_info;
    WGL_COLOR_INFO_T        			t_color_info_fg;

    c_memset(&t_init_data, 0, sizeof(t_init_data));
    t_init_data.h_parent            = pt_this->h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_MENU_NO_EB_NO_BTN|VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.t_gui_rc.i4_left    = MENU_ITEM_V_INSET_L;
    t_init_data.t_gui_rc.i4_top     = (GRID_H*3 - 15*4/3)+15;/*GRID_H=45*/
    t_init_data.pf_data_change_fct  = _add_new_device_page_brand_vkb_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&pt_this->t_select_brd.h_brand_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    a_vkb_do_cmd (pt_this->t_select_brd.h_brand_vkb,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) 32,
                   NULL);

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    t_inset.i4_left   = 20;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info_fg.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_color_info_fg.u_color_data.t_standard.t_disable = t_g_menu_color_bk1_txt_disable;
    t_color_info_fg.u_color_data.t_standard.t_highlight = t_g_menu_color_white;


	/* Create OK button */
    SET_RECT_BY_SIZE (& t_rect,
                      MENU_ITEM_V_INSET_L,
                      (GRID_H*3 - 15*4/3) + 358 + 10+27,
                      MENU_ADD_NEW_DEVICE_BRD_FRM_W,
                      44);
    MENU_LOG_ON_FAIL (_menu_add_new_device_create_btn_widget(
                        pt_this->h_cnt_frm,
                        MENU_TEXT(MLM_MENU_KEY_DEVICE_OK_BTN_MSG),
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_menu_img_item_hlt_bk,
                        h_g_menu_img_item_bk,
                        WGL_AS_LEFT_CENTER,
                        _menu_add_new_device_ok_btn_proc_fct,
                        &pt_this->h_ok_btn,
                        &t_inset));

	/* Create cancel button */
    SET_RECT_BY_SIZE (& t_rect,
                      MENU_ITEM_V_INSET_L,
                      (GRID_H*3 - 15*4/3) + 358 + 10+44+27,
                      MENU_ADD_NEW_DEVICE_BRD_FRM_W,
                      44);
    MENU_LOG_ON_FAIL (_menu_add_new_device_create_btn_widget(
                        pt_this->h_cnt_frm,
                        MENU_TEXT(MLM_MENU_KEY_DEVICE_CANCEL_BTN_MSG1),
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_menu_img_item_hlt_bk,
                        h_g_menu_img_item_bk,
                        WGL_AS_LEFT_CENTER,
                        _menu_add_new_device_cancel_btn_proc_fct,
                        &pt_this->h_cancel_btn,
                        &t_inset));

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _add_new_device_page_model_vkb_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_model_vkb_create(VOID)
{
    INT32       i4_ret = MENUR_OK;

    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    VKB_INIT_T          				t_init_data;
    WGL_FONT_INFO_T         			t_fnt_info;

    c_memset(&t_init_data, 0, sizeof(t_init_data));
    t_init_data.h_parent            = pt_this->h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_MENU_NO_EB_NO_BTN|VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.t_gui_rc.i4_left    = MENU_ITEM_V_INSET_L;
    t_init_data.t_gui_rc.i4_top     = (GRID_H*3 - 15*4/3)+15;
    t_init_data.pf_data_change_fct  = _add_new_device_page_model_vkb_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&pt_this->t_select_model.h_model_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    a_vkb_do_cmd (pt_this->t_select_model.h_model_vkb,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) 32,
                   NULL);

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, menu_font_name());

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_msg_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/

static INT32 _menu_add_new_device_msg_create(HANDLE_T    h_parent,
                            HANDLE_T*               ph_widget,
                            const GL_RECT_T*        pt_rect,
                            wgl_widget_proc_fct     pf_wgt_proc)
{
    INT32               i4_ret = MENUR_OK;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT8               ui1_frame_alpha = 255;
    WGL_INSET_T         t_inset;
    UINT32              ui4_type = WGL_STL_TEXT_MULTILINE |
                                   WGL_STL_TEXT_MAX_2048 |
                                   WGL_STL_TEXT_MAX_DIS_10_LINE |
                                   WGL_STL_GL_NO_BK;

    i4_ret = menu_get_osd_alpha(&ui1_frame_alpha);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                pt_rect,
                                pf_wgt_proc,
                                ui1_frame_alpha,
                                (VOID*)ui4_type,
                                NULL,
                                ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = MENU_DEVICE_STATUS_INFO_TEXT_INSET_LEFT;
    t_inset.i4_right    = MENU_DEVICE_STATUS_INFO_TEXT_INSET_RIGHT;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);
    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_GL_SET_FONT,
                            WGL_PACK(&t_fnt_info),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);
    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                       WGL_CMD_TEXT_SET_ALIGN,
                       WGL_PACK(WGL_AS_LEFT_TOP),
                       NULL);
    MENU_CHK_FAIL(i4_ret);

    c_wgl_set_visibility(*ph_widget,WGL_SW_NORMAL);

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_brand_msg_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_brand_msg_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_X+5,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_X+15,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_W,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_H);
    i4_ret = _menu_add_new_device_msg_create(pt_this->h_cnt_frm,
                                              &pt_this->h_subpage_device_brand_title,
                                              &t_rect,
                                              NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_brand_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_BRAND_MSG)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_BRAND_MSG))));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name: _menu_add_new_device_model_msg_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_model_msg_create(VOID)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_X+5,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_X+15,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_W,
                     MENU_ADD_NEW_DEVICE_BRD_FRM_H);
    i4_ret = _menu_add_new_device_msg_create(pt_this->h_cnt_frm,
                                              &pt_this->h_subpage_device_model_title,
                                              &t_rect,
                                              NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_subpage_device_model_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_MODEL_MSG)),
                          WGL_PACK(c_uc_w2s_strlen(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_DEVICE_DEVICE_MODEL_MSG))));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_w2s_sch
 *
 * Description: search the UTF16 pw2s_sub_text form the UTF16 pw2s_text
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UTF16_T* _menu_add_new_device_w2s_sch(UTF16_T*        pw2s_text,
                             const UTF16_T*  pw2s_sub_text)
{
    UTF16_T*   pw2s_start = NULL;
    SIZE_T     t_cmp_offset = 0;
    SIZE_T     t_txt_size = 0;
    SIZE_T     t_sub_txt_size = 0;
    if (!pw2s_text ||
        !pw2s_sub_text)
    {
        return (pw2s_start);
    }

    t_txt_size = c_uc_w2s_strlen(pw2s_text);
    t_sub_txt_size = c_uc_w2s_strlen(pw2s_sub_text);

    if (t_txt_size < t_sub_txt_size)
    {
        return (pw2s_start);
    }

    pw2s_start = pw2s_text;

    while (pw2s_start <= pw2s_text + t_txt_size - t_sub_txt_size)
    {
        t_cmp_offset = 0;
        while (t_cmp_offset < t_sub_txt_size)
        {
            if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
            {
                t_cmp_offset++;
            }
            else
            {
                break;
            }
        }
        if (t_cmp_offset == t_sub_txt_size)
        {
            return (pw2s_start);
        }
        pw2s_start++;
    }

    return (NULL);
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_create_desc_htxt
 *
 * Description: create the widget for show the text of the confirm remote connect page
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_create_desc_htxt(HANDLE_T   h_parent,
                                                    GL_RECT_T   *pt_rect,
                                                    HANDLE_T    *ph_widget)
{
    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    WGL_COLOR_INFO_T            t_color_info;
    CHAR*                       s_font_name = menu_font_name();

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, s_font_name);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    /* create hyper text widget */
    MENU_LOG_ON_FAIL (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     ph_widget));

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    MENU_LOG_ON_FAIL (c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_HTS_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set justification */
    MENU_LOG_ON_FAIL (c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_LEFT),
                              NULL));

	/* Set Color */
    c_memset(&t_color_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_color_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_color_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_color_info)));

    #if 1
    WGL_HTS_PARAG_ATTR_T t_parag;

    c_memset (& t_parag, 0, sizeof(WGL_HTS_PARAG_ATTR_T));
    t_parag.e_justif = WGL_HTS_JUSTIF_LEFT;
    t_parag.ui2_indent = 0;
    t_parag.i4_line_gap_bottom = 2;
    t_parag.i4_line_gap_top = 0;
    t_parag.ui2_parag_gap_bottom = 0;
    t_parag.ui2_parag_gap_top = 0;
    MENU_LOG_ON_FAIL (c_wgl_do_cmd(*ph_widget,
                                 WGL_CMD_HTS_CUR_PARAG_SET,
                                 WGL_PACK(&t_parag),
                                 NULL));
    #endif
    return  0;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_set_desc_htxt
 *
 * Description: set teh confirm page text
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_set_desc_htxt(HANDLE_T h_htext,
                                        UTF16_T* pw2s_text,
                                        WGL_HIMG_TPL_T h_img_1,
                                        WGL_HIMG_TPL_T h_img_2)
{
    UINT16                 ui2_sec_id = 0;
    UINT16                 ui2_pic_idx = 0;
    WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
    WGL_HTS_IMG_INFO_T     t_hts_img_info;
    UTF16_T                w2s_pic_flag[3 + 1];
    UTF16_T*               pw2s_next = NULL;
    UTF16_T*               pw2s_temp = pw2s_text;

    c_memset (& t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
    c_memset (& t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
    c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

    MENU_LOG_ON_FAIL (c_wgl_do_cmd (h_htext,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL));
    /* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, menu_font_name());

    t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_MEDIUM;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

	t_hts_txt_info.t_clr_text = t_g_menu_color_white;

    c_uc_ps_to_w2s(MENU_ADD_NEW_DEVICE_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));

    pw2s_next = _menu_add_new_device_w2s_sch(pw2s_temp, w2s_pic_flag);
    while (pw2s_next)
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

        MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_htext,
                                WGL_CMD_HTS_APPEND_TEXT_SEC,
                                WGL_PACK (&t_hts_txt_info),
                                WGL_PACK (&ui2_sec_id)));

        t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        if (ui2_pic_idx == 0)
        {
            t_hts_img_info.h_img = h_img_1;
        }
        else if (ui2_pic_idx == 1)
        {
            t_hts_img_info.h_img = h_img_2;
        }

        MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_htext,
                                WGL_CMD_HTS_APPEND_IMG_SEC,
                                WGL_PACK( &t_hts_img_info),
                                WGL_PACK( &ui2_sec_id)));
        ui2_pic_idx ++;

        pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
        pw2s_next = _menu_add_new_device_w2s_sch(pw2s_temp, w2s_pic_flag);
    }

    if (pw2s_temp < pw2s_text + c_uc_w2s_strlen(pw2s_text))
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

        MENU_LOG_ON_FAIL(c_wgl_do_cmd(h_htext,
                                WGL_CMD_HTS_APPEND_TEXT_SEC,
                                WGL_PACK (&t_hts_txt_info),
                                WGL_PACK (&ui2_sec_id)));
    }

    return (MENUR_OK);
}

/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_warning_dialog_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_warning_dialog_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
        {
            add_dev_dlg_cb_fct  pf_back = NULL;
            INT32           i4_ret;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pf_back),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(pf_back != NULL)
            {
                pf_back(ui4_keycode);
            }

            return WGLR_OK;
        }
        default:
            break;
        }

        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_brand_subpage_create
 *
 * Description: brand VKB/brand editbox/brand delete icon
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _menu_add_new_device_brand_subpage_create(VOID)
 {
 	INT32       						i4_ret = MENUR_OK;
 	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    VKB_EB_ATTACH_DATE t_brand_eb_attach = {0};

	i4_ret = _add_new_device_page_brand_vkb_create();
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _menu_add_new_device_brand_msg_create();
	MENU_LOG_ON_FAIL(i4_ret);

	/* create brand editbox */
    i4_ret = _menu_add_new_device_edit_box_create(
                                        pt_this->h_cnt_frm,
                                        MENU_ADD_NEW_DEVICE_BRD_FRM_Y+10+25,
                                        MENU_ADD_NEW_DEVICE_EB_LEFT_INSET,
                                        MENU_ADD_NEW_DEVICE_EB_RIGHT_INSET,
                                        WGL_STL_EB_MAX_CHAR_64,
                                        //_menu_add_new_device_brand_eb_proc_fct,
                                        NULL,
                                        &pt_this->t_select_brd.h_brand_eb);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _menu_add_new_device_icon_create(pt_this->h_cnt_frm, &pt_this->t_select_brd.h_brd_eb_del_all);
	MENU_LOG_ON_FAIL(i4_ret);

    /*attach the eidt box and delete all icon to brand VKB*/
	c_memset(&t_brand_eb_attach, 0 , sizeof(VKB_EB_ATTACH_DATE));
    t_brand_eb_attach.h_edit_box = pt_this->t_select_brd.h_brand_eb;
    t_brand_eb_attach.h_eb_clr = pt_this->t_select_brd.h_brd_eb_del_all;
    t_brand_eb_attach.b_need_eb_clr = TRUE;
    a_vkb_attach_eb(pt_this->t_select_brd.h_brand_vkb, &t_brand_eb_attach);

	return i4_ret;
 }
 /*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_model_subpage_create
 *
 * Description: model VKB/model editbox/model delete icon
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _menu_add_new_device_model_subpage_create(VOID)
 {
 	INT32       						i4_ret = MENUR_OK;
 	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    VKB_EB_ATTACH_DATE t_model_eb_attach = {0};

	i4_ret = _add_new_device_page_model_vkb_create();
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _menu_add_new_device_model_msg_create();
	MENU_LOG_ON_FAIL(i4_ret);

	/* create model editbox */
    i4_ret = _menu_add_new_device_edit_box_create(
                                        pt_this->h_cnt_frm,
                                        MENU_ADD_NEW_DEVICE_BRD_FRM_Y+10+25,
                                        MENU_ADD_NEW_DEVICE_EB_LEFT_INSET,
                                        MENU_ADD_NEW_DEVICE_EB_RIGHT_INSET,
                                        WGL_STL_EB_MAX_CHAR_64,
                                        //_menu_add_new_device_model_eb_proc_fct,
                                        NULL,
                                        &pt_this->t_select_model.h_model_eb);
	MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = _menu_add_new_device_icon_create(pt_this->h_cnt_frm, &pt_this->t_select_model.h_model_eb_del_all);
	MENU_LOG_ON_FAIL(i4_ret);

	/*attach the eidt box and delete all icon to model VKB*/
	c_memset(&t_model_eb_attach, 0 , sizeof(VKB_EB_ATTACH_DATE));
    t_model_eb_attach.h_edit_box = pt_this->t_select_model.h_model_eb;
    t_model_eb_attach.h_eb_clr = pt_this->t_select_model.h_model_eb_del_all;
    t_model_eb_attach.b_need_eb_clr = TRUE;
    a_vkb_attach_eb(pt_this->t_select_model.h_model_vkb, &t_model_eb_attach);

	return i4_ret;
 }
 /*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_confirm_subpage_create
 *
 * Description: include:intro text/ attempting text/work btn/try next btn/manually enter code btn
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
 static INT32 _menu_add_new_device_confirm_subpage_create(VOID)
 {
 	INT32       						i4_ret = MENUR_OK;
 	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;
 	GL_RECT_T                           t_rect;
    WGL_INSET_T             			t_inset;
    WGL_FONT_INFO_T         			t_fnt_info;
    WGL_COLOR_INFO_T        			t_color_info_fg;

	/* Create the text of confirm remote connect page */
    SET_RECT_BY_SIZE (& t_rect,
                      20,
                      10,
                      400-20,
                      160);
    i4_ret = _menu_add_new_device_create_desc_htxt(pt_this->h_cnt_frm,
                                    &t_rect,
                                    &pt_this->t_remote_code.h_code_intro_txt);

	/* Create the attemping text of confirm remote connect page */
    SET_RECT_BY_SIZE (& t_rect,
                      20,
                      140,
                      400-20,
                      80);
    i4_ret = _menu_add_new_device_create_desc_htxt(pt_this->h_cnt_frm,
                                    &t_rect,
                                    &pt_this->t_remote_code.h_attemp_code_txt);


	/* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    t_inset.i4_left   = 20;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info_fg.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_color_info_fg.u_color_data.t_standard.t_disable = t_g_menu_color_bk1_txt_disable;
    t_color_info_fg.u_color_data.t_standard.t_highlight = t_g_menu_color_white;

	/* Create it worked button */
    SET_RECT_BY_SIZE (& t_rect,
                      MENU_ITEM_V_INSET_L,
                      200,
                      MENU_ADD_NEW_DEVICE_BRD_FRM_W,
                      44);
    MENU_LOG_ON_FAIL (_menu_add_new_device_create_btn_widget(
                        pt_this->h_cnt_frm,
                        MENU_TEXT(MLM_MENU_KEY_DEVICE_SETUP_CONFIRM_WORK),
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_menu_img_item_hlt_bk,
                        h_g_menu_img_item_bk,
                        WGL_AS_LEFT_CENTER,
                        _menu_add_new_device_it_work_btn_proc_fct,
                        &pt_this->t_remote_code.h_it_work_btn,
                        &t_inset));

	/* Create try the next remote code  button */
    SET_RECT_BY_SIZE (& t_rect,
                      MENU_ITEM_V_INSET_L,
                      200 + 44,
                      MENU_ADD_NEW_DEVICE_BRD_FRM_W,
                      44);
    MENU_LOG_ON_FAIL (_menu_add_new_device_create_btn_widget(
                        pt_this->h_cnt_frm,
                        MENU_TEXT(MLM_MENU_KEY_AUD_CONTROL_CONFIRM_TRY_NEXT),
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_menu_img_item_hlt_bk,
                        h_g_menu_img_item_bk,
                        WGL_AS_LEFT_CENTER,
                        _menu_add_new_device_try_next_btn_proc_fct,
                        &pt_this->t_remote_code.h_try_next_btn,
                        &t_inset));

	/* Create manual enter code  button */
	SET_RECT_BY_SIZE (& t_rect,
                      MENU_ITEM_V_INSET_L,
                      200 + 44 + 44,
                      MENU_ADD_NEW_DEVICE_BRD_FRM_W,
                      44);
    MENU_LOG_ON_FAIL (_menu_add_new_device_create_btn_widget(
                        pt_this->h_cnt_frm,
                        MENU_TEXT(MLM_MENU_KEY_DEVICE_MANUAL_ENTER_CODE_BTN_MSG),
                        &t_rect,
                        &t_color_info_fg,
                        &t_fnt_info,
                        h_g_menu_img_item_hlt_bk,
                        h_g_menu_img_item_bk,
                        WGL_AS_LEFT_CENTER,
                        _menu_add_new_device_manual_enter_code_btn_proc_fct,
                        &pt_this->t_remote_code.h_manual_enter_code_btn,
                        &t_inset));


	return i4_ret;
 }
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    c_memset(pt_this, 0, sizeof(MENU_ADD_NEW_DEVICE_PAGE_DATA_T));
    pt_this->e_page_enter_from = ADD_NEW_DEVICE_PAGE_ENTERN_FROM_NORMAL;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_this->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_main_subpage_list_item_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _create_input_subpage();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _create_device_type_subpage();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _create_device_type_aud_subpage();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_brand_subpage_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_model_subpage_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_confirm_subpage_create();
    MENU_LOG_ON_FAIL(i4_ret);

	MENU_LOG_ON_FAIL(_menu_add_new_device_drop_down_lst_create(pt_this->h_cnt_frm,
                    &pt_this->t_drop_down_lst));

    i4_ret = _menu_add_new_device_custom_dialog_init();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_dlg_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_manual_enter_code_dlg_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _menu_add_new_device_warning_dialog_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _add_new_device_page_destroy
 *
 * Description: _add_new_device_page_destroy
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_destroy(UINT32 ui4_page_id)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	INT32						  i4_ret;

	/* reset the page show flag*/
    if (pt_this->b_is_page_show)
    {
    pt_this->b_is_page_show = FALSE;
    }

    /* should unregister the callback*/
    if (pt_this->b_is_notify_reg)
    {
        i4_ret = a_dev_db_unregister(pt_this->ui4_nfy_id);
        DBG_INFO( ("\n[####%s(%d)] a_dev_db_unregister() return i4_ret[%d]\n",__FUNCTION__,__LINE__,i4_ret));
        pt_this->b_is_notify_reg = FALSE;
    }
#ifdef APP_UEI_SPINNER_SUPPORT
    if (NULL_HANDLE != pt_this->h_brd_online_timer)
    {
        c_timer_delete(pt_this->h_brd_online_timer);
        pt_this->h_brd_online_timer = NULL_HANDLE;
    }
#endif

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_confirm_dialog_create
 *
 * Description: press tv power key in confirm page trigg the dlg show
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _menu_add_new_device_warning_dialog_create( VOID )
{
    INT32       i4_ret;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* 	pt_this = &t_g_add_new_device_page_data;

    GL_RECT_T           t_rect;

    HANDLE_T     h_root_frm;

    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_IMG_INFO_T    t_img_info;

    WGL_INSET_T t_inset = {
        8*4/3,
        8*4/3,
        3*4/3,
        0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_X,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_Y,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_W,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_H);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 NULL,
                                 255,
                                 //(VOID*) (WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                                 (VOID*) 0,
                                 0,
                                 &pt_this->t_warning_dlg.h_dlg_frm);
    MENU_LOG_ON_FAIL(i4_ret);

     t_img_info.e_type = WGL_IMG_SET_STANDARD;
     t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_bar_background;
     t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_bar_background;
     t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_bar_background;
     i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_frm,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

     SET_RECT_BY_SIZE(&t_rect,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_X,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_Y,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_W,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_H);

     i4_ret = c_wgl_create_widget(pt_this->t_warning_dlg.h_dlg_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                                  NULL,
                                  &pt_this->t_warning_dlg.h_dlg_title);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     /* Set Insets */
     i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_title,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_title,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Font */
     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
     t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
     i4_ret = c_wgl_do_cmd (pt_this->t_warning_dlg.h_dlg_title,
                            WGL_CMD_GL_SET_FONT,
                            (void*)&t_fnt_info,
                            NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
     t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
     i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_title,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info) );
     MENU_LOG_ON_FAIL(i4_ret);

     SET_RECT_BY_SIZE(&t_rect,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_X,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_Y,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_W,
                      MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_H);

    i4_ret = c_wgl_create_widget(pt_this->t_warning_dlg.h_dlg_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &pt_this->t_warning_dlg.h_warning_icon);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_rect.i4_left      = 0;
    t_rect.i4_right     = 0;
    t_rect.i4_top       = 0;
    t_rect.i4_bottom    = 0;
    i4_ret = c_wgl_do_cmd (pt_this->t_warning_dlg.h_warning_icon,
                           WGL_CMD_GL_SET_INSET,
                           &t_rect,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_warning_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_warning_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_warning_icon;
    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_warning_icon,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_FG),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_warning_icon,
                           WGL_CMD_ICON_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_X,
                     MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_Y,
                     MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_W,
                     MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_H);

    i4_ret = c_wgl_create_widget(pt_this->t_warning_dlg.h_dlg_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _menu_add_new_device_warning_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &pt_this->t_warning_dlg.h_dlg_btn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_btn,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set text of btn Alignment */
    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_btn,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_this->t_warning_dlg.h_dlg_btn,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_btn,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility (pt_this->t_warning_dlg.h_dlg_frm, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (pt_this->t_warning_dlg.h_dlg_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_warning_dlg_hide
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
static INT32 _menu_add_new_device_warning_dlg_hide(BOOL  b_repaint)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_set_visibility(pt_this->t_warning_dlg.h_dlg_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->t_warning_dlg.h_dlg_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_warning_dlg_yes_btn_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _menu_add_new_device_warning_dlg_yes_btn_cb_fct(UINT32 ui4_key_code)
{
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    if (BTN_SELECT == ui4_key_code)
    {
        c_wgl_set_focus(pt_this->h_current_focus, WGL_SYNC_AUTO_REPAINT);
        _menu_add_new_device_warning_dlg_hide(TRUE);
    }
}
/*----------------------------------------------------------------------------
 * Name: _menu_add_new_device_warning_dialog_show
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
static INT32 _menu_add_new_device_warning_dialog_show(UINT16      ui2_msgid_title,
                                    UINT16      ui2_msgid_btn,
                                    add_dev_dlg_cb_fct  pf_back_yes,
                                    BOOL         b_repaint)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    INT32 i4_ret = MENUR_OK;

    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_btn,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_yes),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->t_warning_dlg.h_dlg_btn,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_btn)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(pt_this->t_warning_dlg.h_dlg_btn, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(pt_this->t_warning_dlg.h_dlg_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        HANDLE_T  h_frm_main = NULL_HANDLE;

        i4_ret = menu_pm_get_root_frm(&h_frm_main);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(h_frm_main,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(pt_this->t_warning_dlg.h_dlg_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_add_new_device_power_off_warning_dlg_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 INT32 menu_add_new_device_power_off_warning_dlg_show()
 {
	MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	INT32	i4_ret=MENUR_OK;

	i4_ret = c_wgl_get_focus(&pt_this->h_current_focus);
    MENU_LOG_ON_FAIL(i4_ret);

    _menu_add_new_device_warning_dialog_show(MLM_MENU_KEY_POWER_OFF_WARNING,
                                     MLM_MENU_KEY_OK,
                                     _menu_add_new_device_warning_dlg_yes_btn_cb_fct,
                                     TRUE);
	return MENUR_OK;
 }
#ifdef APP_UEI_SPINNER_SUPPORT
 /*----------------------------------------------------------------------------
 * Name: _add_device_do_animation_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 static VOID _add_device_do_animation_nfy(
														 VOID* pv_data,
														 SIZE_T  z_data_size)
 {
 	 INT32		i4_ret = MENUR_OK;
	 MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

	 if(pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND)
 	 {
	 	 if((pt_this->b_is_brd_online_query_start)&&
		 	(!pt_this->b_is_brd_online_query_complete))
	 	 {
	 	 	if(pt_this->b_animation)
	 		{
				menu_page_animation_start(1, FALSE);
				i4_ret = menu_page_animation_show();
				MENU_LOG_ON_FAIL(i4_ret);
	 		}
	 	 }
 	 }
	 else if(pt_this->e_subpage == ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT)
 	 {
 		if(pt_this->b_is_codeset_querying)
		{
			menu_page_animation_start(1, FALSE);
			i4_ret = menu_page_animation_show();
			MENU_LOG_ON_FAIL(i4_ret);
			pt_this->b_animation = TRUE;
		}
		else
		{
			_add_device_animation_stop();
			DBG_INFO(("\n####%s(%d)stop for b_is_codeset_querying==false \n"));
		}
 	 }

 }
 /*----------------------------------------------------------------------------
 * Name: _add_device_animation_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 static INT32 _add_device_animation_cb(HANDLE_T  h_widget,
											   UINT16				   ui2_anim_type,
											   WGL_ANIM_COND_INF_T	   e_anim_cond,
											   VOID*				   pv_tag)
 {
	 INT32		 i4_ret = MENUR_OK;

	 if (_ANIM_TOTAL_END(&e_anim_cond))
	 {
		 i4_ret = menu_async_invoke(_add_device_do_animation_nfy,
									NULL, 0, TRUE);
		 MENU_LOG_ON_FAIL(i4_ret);
	 }

	 return MENUR_OK;
 }
 /*----------------------------------------------------------------------------
 * Name: _add_device_animation_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 static INT32 _add_device_animation_create(VOID)
 {
	 INT32		 i4_ret = MENUR_OK;
	 MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	 GL_RECT_T	 t_rect;

	 c_memset(&t_rect, 0, sizeof(t_rect));
	 SET_RECT_BY_SIZE(&t_rect,
					  CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
					  CONTENT_Y + MENU_ITEM_V_HEIGHT * 4 - ICON_ANIMATION_H,
					  ICON_ANIMATION_W,
					  ICON_ANIMATION_H);

	 i4_ret = menu_page_animation_get_handle(&pt_this->h_animation);
	 MENU_LOG_ON_FAIL(i4_ret);

	 i4_ret = c_wgl_move(pt_this->h_animation, &t_rect, FALSE);
	 MENU_LOG_ON_FAIL(i4_ret);

	 i4_ret = menu_page_animation_set_callback_fct(_add_device_animation_cb,
												   NULL);
	 MENU_LOG_ON_FAIL(i4_ret);

	 pt_this->b_animation = FALSE;

	 return i4_ret;
 }
#endif
 /*----------------------------------------------------------------------------
 * Name: _add_new_device_page_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_show(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
	ADD_NEW_DEVICE_PAGE_ENTER_FROM_T  e_enter_from = ADD_NEW_DEVICE_PAGE_ENTERN_FROM_NORMAL;
    BOOL    b_db_status = FALSE;
    DEV_DB_LOCK_CHECK_COND_T e_check_cond = DEV_DB_LOCK_CHECK_COND_NONE;

#ifdef APP_UEI_SPINNER_SUPPORT
    i4_ret = _add_device_animation_create();
    MENU_LOG_ON_FAIL(i4_ret);

	i4_ret = c_timer_create(&pt_this->h_brd_online_timer);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    i4_ret = a_dev_db_check_lock_info( e_check_cond, &b_db_status );

    DBG_INFO(("\n[####%s(%d)] a_dev_db_check_lock_info() i4_ret=%d , check_cond=%d, b_db_status=%d\n",__FUNCTION__,__LINE__, i4_ret, e_check_cond, b_db_status));

    if ((MENUR_OK == i4_ret) && (b_db_status)) /* should check the return value and the lock status*/
    {
        pt_this->b_is_db_locked = TRUE;
    }
	else
	{
		pt_this->b_is_db_locked = FALSE;
	}

    if (FALSE == pt_this->b_is_notify_reg)
    {
        i4_ret = a_dev_db_register( _menu_add_new_device_dev_db_local_query,(VOID*) pt_this, &(pt_this->ui4_nfy_id) );
    }

    if (MENUR_OK != i4_ret)
    {
        DBG_ERROR(("[####%s(%d)] a_dev_db_register() i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        return i4_ret;
    }

    pt_this->b_is_notify_reg = TRUE;

    pt_this->b_is_page_show = TRUE;

    menu_device_page_add_new_device_enter_from_get(&e_enter_from);

    /* as enter the page dev setup should reset the dev db data info*/
    _add_new_device_page_reset_dev_info();

    pt_this->e_pre_subpage = pt_this->e_subpage;
    pt_this->e_subpage = ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN;

    if (ADD_NEW_DEVICE_PAGE_ENTERN_FROM_AUDIO_MODE_SETUP == e_enter_from)
    {
        pt_this->h_last_focus_item = pt_this->h_list_item_device_type_aud;
        pt_this->ui4_type_sel_idx = MENU_SETUP_AVR_AMP_IDX;
    }
    else
    {
        pt_this->h_last_focus_item = pt_this->h_list_item_device_type;
        pt_this->ui4_type_sel_idx = DEVICE_TYPE_UNKNOWN;
    }
    c_memset(pt_this->s_brd_name, 0, 32);
    c_memset(pt_this->s_model_name, 0, 32);

    i4_ret = menu_main_set_title(MLM_MENU_KEY_DEVICE_SETUP_TITLE);//DEVICE SETUP
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _add_new_device_page_show_subpage(TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(_add_new_device_page_backbar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(_add_new_device_page_homebar_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
 /*----------------------------------------------------------------------------
 * Name: _add_new_device_page_hide
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_hide(UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_dev_db_clean_codeset_list();
    DBG_INFO(("####%s(%d) a_dev_db_clean_codeset_list() return[%d]\n",__FUNCTION__,__LINE__,i4_ret));

    if( pt_this->t_confirm_dlg.b_is_show == TRUE)
    {
	    i4_ret = _menu_add_new_device_custom_dialog_hide();
	    DBG_INFO(("\n####%s(%d)dialog hide\n",__FUNCTION__,__LINE__));
	    MENU_LOG_ON_FAIL(i4_ret);
    }

	/*hide the manual enter code dlg*/
	i4_ret = _menu_add_new_device_manual_enter_code_dlg_hide(TRUE);
	DBG_INFO(("\n####%s(%d)i4_ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
	MENU_LOG_ON_FAIL(i4_ret);

    /* also here should reset the enter flag to normal*/
    menu_device_page_add_new_device_enter_from_set(ADD_NEW_DEVICE_PAGE_ENTERN_FROM_NORMAL);

    if (pt_this->b_is_page_show)
    {
	    pt_this->b_is_page_show = FALSE;
    }

    menu_set_help_tip_flag(TRUE);

    return i4_ret;
}
 /*----------------------------------------------------------------------------
 * Name: _add_new_device_page_get_focus
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32       i4_ret = MENUR_OK;

    return i4_ret;
}
 /*----------------------------------------------------------------------------
 * Name: _add_new_device_page_lose_focus
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_lose_focus(UINT32 ui4_page_id)
{
#ifdef APP_UEI_SPINNER_SUPPORT
	/* stop animation */
	_add_device_animation_stop();
	DBG_INFO(("\n####%s(%d)HIDE animation lose focus\n",__FUNCTION__,__LINE__));
#endif
    return MENUR_OK;
}
 /*----------------------------------------------------------------------------
 * Name: _add_new_device_page_update
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _add_new_device_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)

{
    return MENUR_OK;
}
 /*----------------------------------------------------------------------------
 * Name: menu_device_page_add_new_device_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_device_page_add_new_device_init(VOID)
{
	INT32						  i4_ret;

    t_g_menu_device_page_add_new_device.pf_menu_page_create =    _add_new_device_page_create;
    t_g_menu_device_page_add_new_device.pf_menu_page_destroy=    _add_new_device_page_destroy;
    t_g_menu_device_page_add_new_device.pf_menu_page_show=       _add_new_device_page_show;
    t_g_menu_device_page_add_new_device.pf_menu_page_hide=       _add_new_device_page_hide;
    t_g_menu_device_page_add_new_device.pf_menu_page_get_focus=  _add_new_device_page_get_focus;
    t_g_menu_device_page_add_new_device.pf_menu_page_lose_focus= _add_new_device_page_lose_focus;
    t_g_menu_device_page_add_new_device.pf_menu_page_update=     _add_new_device_page_update;

	i4_ret = a_dev_db_init();
	MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_device_page_add_new_device_enter_from_set
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_device_page_add_new_device_enter_from_set(ADD_NEW_DEVICE_PAGE_ENTER_FROM_T  e_enter_from)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    pt_this->e_page_enter_from = e_enter_from;
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_device_page_add_new_device_enter_from_get
 *
 * Description: get the page is from MENU/DEVICE/ADD DEVICE OR MENU/AUDIO/AUDIO DEVICE SETUP
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_device_page_add_new_device_enter_from_get(ADD_NEW_DEVICE_PAGE_ENTER_FROM_T*  pe_enter_from)
{
    MENU_ADD_NEW_DEVICE_PAGE_DATA_T* pt_this = &t_g_add_new_device_page_data;
    *pe_enter_from = pt_this->e_page_enter_from;
    return MENUR_OK;
}

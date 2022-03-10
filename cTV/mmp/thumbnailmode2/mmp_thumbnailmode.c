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
 * $RCSfile:  $
 * $Revision: #2 $
 * $Date: 2015/08/03 $
 * $Author: jg_wanlihong $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "thumbnailmode.h"
#include "amb/a_amb.h"
#include "menu2/a_menu.h"
#include "nav/nav_common.h"
#include "c_dbg.h"

#include "mmp/common_ui2/mmp_com_ui_info_handler.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "nav/banner2/a_banner.h"

#include "res/mmp/gen/mmp_media_type_bg_layout.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DBG_INFO_DIRECT(fmt, args...) \
	do{																		\
		if(0)																\
		{																	\
			fprintf(stderr,fmt,##args );									\
			fflush(stderr);													\
		}																	\
		else																\
		{																	\
			MMP_DBG_INFO((fmt, args));										\
		}																	\
	}while(0)																\



/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
 #define MMP_THUMBNAIL_MAX_NAME_LEN      ((INT32)128)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static MMP_TM_MEMBER_T t_g_tm_member;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_init(VOID);
static INT32 _mmp_thumbnailmode_deinit(VOID);
static INT32 _mmp_thumbnailmode_handle_msg(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param);
static INT32 _mmp_thumbnailmode_cmd_do(MMP_FILE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param);
static INT32 _mmp_thumbnailmode_activate(UINT32 ui4_idx);
static INT32 _mmp_thumbnailmode_inactivate(VOID);

static INT32 _mmp_thumbnailmode_bwr_cmd_do(MMP_BE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param);
static INT32 _mmp_thumbnailmode_bwr_data_xng(const MMP_BE_UI_INFO_T*    pt_upd_data);
static INT32 _mmp_thumbnailmode_hide_optl(BOOL b_is_repaint);
static VOID _mmp_thumbnailmode_set_is_first_loading(MMP_TM_MEMBER_T* pt_this,BOOL b_load_first_page);
static INT32 _mmp_thumbnailmode_view_init(MMP_TM_MEMBER_T* pt_this);
static INT32 _mmp_thumbnailmode_view_deinit(MMP_TM_MEMBER_T* pt_this);
static INT32 _mmp_thumbnailmode_view_activate(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_idx);
static INT32 _mmp_thumbnailmode_view_inactivate(MMP_TM_MEMBER_T* pt_this);
static INT32 _mmp_thumbnailmode_view_reg_cb(void);
static INT32 _mmp_thumbnailmode_view_nfy_frm (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_pop_up_strart_slideshow_nfy_frm (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_pop_up_fullscreen_nfy_frm (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2);


static INT32 _mmp_thumbnailmode_pop_up_info_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_pop_up_rotate_left_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_pop_up_rotate_right_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_pop_up_skip_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2);




static INT32 _mmp_thumbnailmode_right_to_left_btn_nfy_frm (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_ch_lang_text(UINT16 ui2_lang);

static INT32 _mmp_thumbnailmode_load_thumbnail(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx);
static INT32 _mmp_thumbnailmode_init_attrib_settings(MMP_TM_MEMBER_T* pt_this);
static INT32 _mmp_thumbnailmode_refresh_skip_flag(MMP_TM_MEMBER_T* pt_this);
static INT32 _mmp_thumbnailmode_enable_skip_flag(MMP_TM_MEMBER_T* pt_this, UINT8 ui1_idx, BOOL b_skip);
static INT32 _mmp_thumbnailmode_reset_skip_flag(MMP_TM_MEMBER_T* pt_this);

static VOID _mmp_thumbnailmode_show_next_file_thumbnail(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3, VOID* pv_tag4);
static INT32 _mmp_thumbnailmode_set_focus(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx, UINT8 ui1_hlt_idx);
static INT32 _mmp_thumbnailmode_cursor_left_right(MMP_TM_MEMBER_T* pt_this, BOOL b_left);
static INT32 _mmp_thumbnailmode_cursor_up_down(MMP_TM_MEMBER_T* pt_this, BOOL b_up);
//static INT32 _mmp_thumbnailmode_get_hlt_idx(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx, UINT8* pui1_hlt_idx);
static VOID _mmp_thumbnailmode_set_transparent(MMP_TM_MEMBER_T* pt_view, UINT16 ui2_thumb_item_idx);
static INT32 _mmp_thumbnailmode_disable_transparent_list(HANDLE_T  h_rgn_list,             /* in: handle of a transparent list */
                                                         BOOL      b_enabled,              /* in: enable this list or not */
                                                         BOOL      b_exclusive);            /* in: set its state as exclusive or union */
static INT32 _mmp_thumbnailmode_upd_item_list(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx);
//static INT32 _mmp_thumbnailmode_get_info(MMP_TM_MEMBER_T * pt_this);
//static INT32 _mmp_set_item_nav(MMP_TM_MEMBER_T*  pt_this,HANDLE_T ah_items[],INT32 nav_item_num);
static INT32 _mmp_thumbnailmode_set_navigation(MMP_TM_MEMBER_T* pt_this);

static VOID _mmp_thumbnailmode_hide_pop_up_page(MMP_TM_MEMBER_T* pt_this);

static INT32 _mmp_thumbnailmode_pop_up_done_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_start_sldshow_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_device_nfy_frm (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_name_a_z_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_thumbnails_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_browse_music_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);

static INT32 _mmp_thumbnailmode_settings_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);
static INT32 _mmp_thumbnailmode_back_to_up_level_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2);
static VOID _mmp_thumbnailmode_view_default_key_handler(UINT32 ui4_key_code, UINT32 ui4_keystatus);
static INT32 _mmp_thumbnailmode_change_page(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx,UINT8 ui1_hlt_idx);
static INT32 _mmp_thumbnailmode_show_folders(MMP_TM_MEMBER_T* pt_this,UINT32 ui4_focus_idx,UINT8 ui1_hlt_idx,UINT32 *pui4_focus_idx);
static INT32 _mmp_thumbnailmode_show_thumbnails(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx, UINT8 ui1_hlt_idx,UINT32 ui4_file_remain_item );




/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @brief   a_mmp_thumbnailmode_register
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 a_mmp_thumbnailmode_register(VOID)
{
    MMP_MC_FILE_BROWSER_PROPERTY_T  t_prop = {0};
    MMP_FILE_BROWSER_INTF_T         t_intf = {0};
    MMP_BE_BROWSER_HDLR_T           t_hdlr = {0};
    MMP_BE_BROWSER_PROPERTY_T       t_be_bwr_prop = {0};
    INT32                           i4_ret;

    t_prop.ui1_id =                 MMP_RC_BROWSER_ID_THUMBNAIL;
    t_intf.pf_init =                _mmp_thumbnailmode_init;
    t_intf.pf_deinit =              _mmp_thumbnailmode_deinit;
    t_intf.pf_handle_msg =          _mmp_thumbnailmode_handle_msg;
    t_intf.pf_cmd_do =              _mmp_thumbnailmode_cmd_do;
    t_hdlr.pf_cmd_do =              _mmp_thumbnailmode_bwr_cmd_do;
    t_hdlr.pf_data_change =         _mmp_thumbnailmode_bwr_data_xng;
    t_be_bwr_prop.ui2_flag=     (MMP_BE_BWR_FLAG_SKIP_MNT_PNT_SEL|MMP_BE_BWR_FLAG_SKIP_MEDIA_TYPE_SEL);
    t_be_bwr_prop.ui2_flag |= MMP_BE_BWR_FLAG_ADD_PARENT_ITEM;
    t_be_bwr_prop.t_range_info.ui1_col_num = 5;
    t_be_bwr_prop.t_range_info.ui1_row_num = 4;

    i4_ret = mmp_be_reg_brower(&t_intf, &t_prop, &t_hdlr, &t_be_bwr_prop);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_be_reg_brower() failed. i4_ret = %d.\r\n", i4_ret));
    }

    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Thumbnail mode init function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_init(VOID)
{
    MMP_TM_MEMBER_T*                pt_this = &t_g_tm_member;
    INT32                           i4_ret;

    /*init member*/
    c_memset(pt_this, 0, sizeof(MMP_TM_MEMBER_T));

    do {
        i4_ret = _mmp_thumbnailmode_view_init(pt_this);
        if (MMPR_OK != i4_ret)
        {
            break;
        }
        pt_this->ui1_thumb_size_id=1;

        a_cfg_get_mmp_thumb_size(&pt_this->ui1_thumb_size_id);
        i4_ret = mmp_thumbnailmode_change_size(pt_this);
        pt_this->b_refersh_data_ready = FALSE;
        if (MMPR_OK != i4_ret)
        {
            break;
        }
        return MMPR_OK;
    } while (0);


    return i4_ret;
}

/*---------------------------------------------------------------------------e*/
/**
 * @brief   Thumbnail mode deinit function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_deinit(VOID)
{
    MMP_TM_MEMBER_T*                pt_this = &t_g_tm_member;
    INT32                           i4_ret;

    i4_ret = _mmp_thumbnailmode_view_deinit(pt_this);
    IS_MMPR_OK (i4_ret);

    return MMPR_OK;
}


/*---------------------------------------------------------------------------e*/
/**_mmp_thumbnaimode_view_default_key_handler
 * @brief   Thumbnail mode deinit function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_view_reg_cb(void)
{
    INT32   i4_ret = MMPR_OK;

    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_FRM_RIGHT_BASE_FRM,_mmp_thumbnailmode_view_nfy_frm));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_STARTSLIDESHOW_BTN,_mmp_thumbnailmode_pop_up_strart_slideshow_nfy_frm));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_FULL_SCREEN_BTN,_mmp_thumbnailmode_pop_up_fullscreen_nfy_frm));
    IS_MMPR_OK( mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_DONE_BTN, _mmp_thumbnailmode_pop_up_done_btn_nfy));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_PHOTO_INFO_BTN,_mmp_thumbnailmode_pop_up_info_btn_cb));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_PHOTO_ROTATE_LEFT_BTN,_mmp_thumbnailmode_pop_up_rotate_left_btn_cb));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_ROTATE_RIGHT_BTN,_mmp_thumbnailmode_pop_up_rotate_right_btn_cb));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_STOP_BTN,_mmp_thumbnailmode_pop_up_skip_btn_cb));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_RIGHT_TO_LEFT_BTN,_mmp_thumbnailmode_right_to_left_btn_nfy_frm));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_LB_DRIVER,_mmp_thumbnailmode_device_nfy_frm));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_START_SLIDESHOW,_mmp_thumbnailmode_start_sldshow_btn_nfy));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_NAME_A_Z,_mmp_thumbnailmode_name_a_z_btn_nfy));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_THUMBNAILS,_mmp_thumbnailmode_thumbnails_btn_nfy));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_BROWSE_MUSIC,_mmp_thumbnailmode_browse_music_btn_nfy));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_SETTINGS,_mmp_thumbnailmode_settings_btn_nfy));
    IS_MMPR_OK(mmp_mmp_reg_wgt_cb(WID_MMP_MMP_BTN_BACK,_mmp_thumbnailmode_back_to_up_level_btn_nfy));
    return i4_ret;
}

static VOID _mmp_thumbnailmode_view_default_key_handler(UINT32 ui4_key_code, UINT32 ui4_keystatus)
{
    INT32   i4_ret=MMPR_OK;

    if (WGL_MSG_KEY_DOWN == ui4_keystatus)
    {
        MMP_DBG_INFO(("<mmp> default key :0x%x,%s,%d\n\r",ui4_key_code,__FILE__,__LINE__));
        switch(ui4_key_code)
        {
            case BTN_EXIT:
            case BTN_RED:
            {
               i4_ret = mmp_be_pause_mmp();
               MMPR_LOG_ON_FAIL(i4_ret);
               return;
            }
                break;
            case BTN_INPUT_SRC:
            {
                i4_ret = a_amb_default_key_handler(WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
                break;
            default:
            {

                i4_ret = mmp_be_default_key_handle(ui4_key_code, WGL_MSG_KEY_DOWN);
                MMPR_LOG_ON_FAIL(i4_ret);

            }
                break;
        }
    }
    return;
}

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_set_navigation
 * @brief   Set the navigation of  left UI components
 * @param
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_set_navigation(MMP_TM_MEMBER_T* pt_this)
{
    HANDLE_T            ah_items[MMP_TM_MAX_NAV_WIG__NUM];
    WGL_KEY_LINK_T      at_key_lnk[3];
    INT32               i4_ret=MMPR_OK;

    c_memset(at_key_lnk,0,sizeof(at_key_lnk));
    //ah_items[0] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
    //ah_items[1] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_LB_DRIVER);
    //ah_items[2] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
    //ah_items[3] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
    //ah_items[4] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
    //ah_items[5] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
    //ah_items[6] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BROWSE_MUSIC);

    /*  set the navigation of  buttons  */
   // i4_ret=_mmp_set_item_nav(pt_this, ah_items, 3);
    //if (MMPR_OK != i4_ret)
    //{
    //    return MMPR_FAIL;
   // }
    /*set the buttons 's  navigation of pop_up  frame*/

    ah_items[0] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_PHOTO_INFO_BTN);
    ah_items[1] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_PHOTO_ROTATE_LEFT_BTN);
    ah_items[2] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_ROTATE_RIGHT_BTN);
    ah_items[3] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_STOP_BTN);
    ah_items[4] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_FULL_SCREEN_BTN);
    ah_items[5] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_STARTSLIDESHOW_BTN);
    ah_items[6] = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_DONE_BTN);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[0].h_widget = ah_items[5] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_items[1];
    i4_ret = c_wgl_set_navigation(ah_items[0], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_items[0] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_RIGHT;
    at_key_lnk[1].h_widget = ah_items[2];
    at_key_lnk[2].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[2].h_widget = ah_items[5];
    i4_ret = c_wgl_set_navigation(ah_items[1], 3, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_items[1] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[5];
    i4_ret = c_wgl_set_navigation(ah_items[2], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_LEFT;
    at_key_lnk[0].h_widget = ah_items[2] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[5];
    i4_ret = c_wgl_set_navigation(ah_items[3], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = ah_items[0] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[4];
    i4_ret = c_wgl_set_navigation(ah_items[5], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = ah_items[5] ;
    at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[1].h_widget = ah_items[6];
    i4_ret = c_wgl_set_navigation(ah_items[4], 2, at_key_lnk);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = ah_items[4] ;
    i4_ret = c_wgl_set_navigation(ah_items[6], 1, at_key_lnk);
    return i4_ret;
}

#if 0
/*---------------------------------------------------------------------------*/
/**
 * @brief   Set the navigation of  left UI components
 * @param
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_set_item_nav(MMP_TM_MEMBER_T*  pt_this,HANDLE_T ah_items[],INT32 nav_item_num)
{
    HANDLE_T                        h_nav_up=0;
    HANDLE_T                        h_nav_dn=0;
    HANDLE_T                        h_owner =0;
    //HANDLE_T                      h_nav_lf=0;
    //HANDLE_T                        h_nav_rt=pt_this->h_frm_right_base_frm;
    WGL_KEY_LINK_T                 at_key_lnk[3];
    INT32                            i4_ret=0;
    UINT32                          ui4_i;

    c_memset(at_key_lnk,0,sizeof(at_key_lnk));

    /* link these items with 'up/down' key */
    for ( ui4_i = 0 ;ui4_i < nav_item_num ;ui4_i ++)
    {
        {
            if (nav_item_num == 1)
            {
                /* only one node */
                h_owner  = ah_items[ui4_i] ;
                h_nav_up = ah_items[ui4_i] ;
                h_nav_dn = ah_items[ui4_i] ;
            }
            else if (ui4_i == 0)
            {
                /* first node */
                h_owner  = ah_items[ui4_i   ];
                h_nav_up = ah_items[ui4_i   ] ;
                h_nav_dn = ah_items[ui4_i +1] ;
            }
            else if (ui4_i < nav_item_num -1)
            {
                /* middle node */
                h_owner  = ah_items[ui4_i   ] ;
                h_nav_up = ah_items[ui4_i -1] ;
                h_nav_dn = ah_items[ui4_i +1] ;
            }
            else
            {
                /* last node */
                h_owner  = ah_items[ui4_i   ] ;
                h_nav_up = ah_items[ui4_i -1] ;
                h_nav_dn = ah_items[ui4_i   ] ;
            }
        }

        MMP_DBG_ERROR(("set focus \n"));

        at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_nav_up ;
        at_key_lnk[1].ui4_key  = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_nav_dn;
        //at_key_lnk[2].ui4_key  = BTN_CURSOR_RIGHT;
        //at_key_lnk[2].h_widget = h_nav_rt;
        i4_ret = c_wgl_set_navigation(h_owner, 2, at_key_lnk);

        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("set navigation faill \n"));
            break;
        }
    }
      return MMPR_OK;
}
#endif
/*---------------------------------------------------------------------------*/
/**@function  _mmp_thumbnailmode_ch_lang_text
 * @brief   If the language is changed then adjust the text language.
 * @param
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_ch_lang_text(UINT16 ui2_lang)
{
    UINT32              ui4_i = 0;
    HANDLE_T            h_thumb_item = NULL_HANDLE;
    MMP_TM_MEMBER_T*    pt_this = &t_g_tm_member;
    INT32               i4_ret = MMPR_OK;
    UTF16_T             w2s_text[MMP_BE_MAX_PATH_LEN+1]={0};
    HANDLE_T            h_ful_path_txt = NULL_HANDLE;
    HANDLE_T            h_fin_path_txt = NULL_HANDLE;
    UTF16_T*            pw2s_file_path = NULL;
    SIZE_T              z_size = MMP_BE_MAX_PATH_LEN;

    mmp_thumbnailmode_view_updatet_widget_text(pt_this);
    mmp_thumbnailmode_set_page_num(pt_this, pt_this->ui4_focus_idx);
    for (ui4_i = 0;ui4_i <MMP_THMBNAILMODE_MAX_THUMBS ;ui4_i++)
    {
        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui4_i * 2);
        c_wgl_do_cmd (h_thumb_item,
                      WGL_CMD_BTN_SET_TEXT,
                      WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUMB_LOAD_FAIL_TXT)),
                      WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUMB_LOAD_FAIL_TXT))));
     }

    i4_ret = mmp_be_get_curr_path_display(w2s_text, &pw2s_file_path, &z_size);
    IS_MMPR_OK(i4_ret);

    //refresh  full path

    h_ful_path_txt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_PATH);

    i4_ret = c_wgl_do_cmd (h_ful_path_txt,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(w2s_text),
                           WGL_PACK((UINT16)0xFFFF));
    IS_MMPR_OK(i4_ret);

    //refresh file name path

    h_fin_path_txt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_FILE_NAME);
    i4_ret = c_wgl_do_cmd (h_fin_path_txt,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(pw2s_file_path),
                           WGL_PACK((UINT16)0xFFFF));
    IS_MMPR_OK(i4_ret);

    c_wgl_repaint(pt_this->h_frm_base_frm,NULL,TRUE);
    return i4_ret;

}

/*---------------------------------------------------------------------------*/
/**
 * @brief   The message handler of thumbnail mode
 * @param   e_msg_id [in]   Message ID
 * @param   pv_msg_param [in]   Message additional information
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_handle_msg(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param)
{
    MMP_TM_MEMBER_T*        pt_this = &t_g_tm_member;
    BOOL                    b_default_hdlr = FALSE;
#ifdef APP_MENU_MMP_COEXIST
    HANDLE_T                h_thumb_item=NULL_HANDLE;
#endif
    UINT8                   ui1_id ;
    BOOL                    b_is_show;
    ISO_639_LANG_T          s639_lang;
    INT32                   i4_ret = MMPR_OK;

    MMP_DBG_INFO(("[mmp] %s %d e_msg_id:%d pv_msg_param:%d .\r\n",__FUNCTION__,__LINE__,e_msg_id,(BOOL)(UINT32)pv_msg_param));

    /* Only process msg when active */
    mmp_mc_browse_get_active(&ui1_id,&b_is_show);
    if (ui1_id != MMP_RC_BROWSER_ID_THUMBNAIL)
    {
        return MMPR_OK;
    }

    switch (e_msg_id)
    {
        case MMP_MSG_ID_BROWSE_FOLDER_XNG:
        {
            b_default_hdlr = TRUE;
        }
        break;

        case MMP_MSG_ID_BROWSE_FILE_INFO_READY:
        {
            /* set to info handler */
            DBG_INFO_DIRECT("[mmp tn] %s %d <MMP_MSG_ID_BROWSE_FILE_INFO_READY> \r\n",__FUNCTION__,__LINE__);
            mmp_thumbnail_display_file_info(pt_this);
        }
        break;


        case MMP_MSG_ID_BROWSE_FILE_THUMBNAIL:
        {
            DBG_INFO_DIRECT("[mmp tn] %s %d <MMP_MSG_ID_BROWSE_FILE_THUMBNAIL> continue to load next thumbnail\r\n",__FUNCTION__,__LINE__);
            _mmp_thumbnailmode_show_next_file_thumbnail(pt_this, pv_msg_param, (VOID*)pt_this->ui4_thumb_idx_curr, NULL);
        }
        break;
        case MMP_MSG_ID_CUST_APPLY_SORT_CFG:
        {
            //mmp_be_refresh(MMP_BE_FF_IDX_CRT, MMP_BE_REFRESH_TYPE_ITEM_LST);
        }
        break;

        case MMP_MSG_ID_PLAY_FILE_XNG :
        {
            /*back ground audio file changed */
            if (MMP_GROUND_MODE_BACK == (MMP_GROUND_MODE_T)(INT32)pv_msg_param)
            {
                mmp_mc_browse_show_info_handler(FALSE,TRUE,TRUE);
                //c_wgl_repaint(pt_this->h_play_frm,NULL,TRUE);
            }
        }
        break;
        case MMP_MSD_ID_LOCKED_INP:
        {
           // mmp_thumbnailmode_show_warning_msg(pt_this, MMP_TM_VIEW_WARN_MSG_LOCK_INP, TRUE, TRUE);
        }
        break;

#ifdef APP_MENU_MMP_COEXIST
        case MMP_MSG_ID_APP_STAT_XNG:
        {
            MMP_STAT_XNG_INFO_T*    pt_mmp_stat_info = (MMP_STAT_XNG_INFO_T*)pv_msg_param;
            HANDLE_T                h_focus_widget = NULL_HANDLE;

            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == pt_mmp_stat_info->e_mmp_stat_new)
            {
                /* do something */
                if(pt_this->b_thumb_active == TRUE)
                {
                    c_wgl_enable_transparent_list(pt_this->h_preview_trans_list, FALSE, FALSE);
                    c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_rect_preview, TRUE);

                    if((pt_this->ui4_dir_num + pt_this->ui4_file_num) != 0)
                    {
                        c_wgl_enable_transparent_list(pt_this->h_transparent_rect, TRUE, TRUE);
                        _mmp_thumbnailmode_refresh_skip_flag(pt_this);
                    }

                    if (MMP_TM_POPUP_STATUS_PREVIEW == pt_this->e_popup_status)
                    {
                        mmp_thumbnailmode_show_img_preview(pt_this, FALSE);
                    }
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_POP_UP_BASE_FRM);
                    IS_MMPR_OK (c_wgl_set_visibility (h_thumb_item, WGL_SW_HIDE_RECURSIVE));
                    IS_MMPR_OK(c_wgl_repaint(h_thumb_item,NULL,TRUE));
                    pt_this->e_popup_status = MMP_TM_POPUP_STATUS_OFF;
                }
            }
            else if ((MMP_MAIN_AP_STATUS_RESUMED == pt_mmp_stat_info->e_mmp_stat_new)
                                                    &&(pt_this->b_thumb_active == TRUE))

            {
                /* do something */
                if(pt_this->b_optl_show == TRUE)
                {
                    c_wgl_get_focus(&h_focus_widget);
                    c_wgl_set_focus(h_focus_widget,TRUE);
                }
                else
                {
                    c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
                    mmp_thumbnail_display_file_info(pt_this);
                }


            }
        }
        break;
#endif

        case MMP_MSG_ID_GUI_LANG_XNG:

            i4_ret = a_cfg_get_gui_lang(s639_lang);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_ERROR(("MMP thumbnailmode get language fall \r\n"));
                pt_this->ui1_gui_lang_id =0;
            }
            else
            {
                pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
            }
            if(pt_this->b_optl_show == TRUE)
            {
                _mmp_thumbnailmode_hide_optl(TRUE);
                pt_this->b_optl_show = FALSE;
                c_wgl_set_visibility(pt_this->h_frm_left_ui_frm1,WGL_SW_RECURSIVE);
                c_wgl_repaint(pt_this->h_frm_left_ui_frm1,NULL,TRUE);
            }
            _mmp_thumbnailmode_ch_lang_text(pt_this->ui1_gui_lang_id);
            break;


        default:
            b_default_hdlr = TRUE;
            break;
    }

    if (b_default_hdlr)
    {
        mmp_be_default_msg_hdlr(e_msg_id, pv_msg_param);
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   The command handler of thumbnail mode
 * @param   e_cmd_id [in]   Command ID
 * @param   pv_cmd_param [in]   Command additional information
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_cmd_do(MMP_FILE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param)
{

    MMP_TM_MEMBER_T*   pt_this = &t_g_tm_member;
    INT32              i4_ret = MMPR_OK;

    if (MMP_FILE_BROWSER_CMD_ID_ACTIVATE == e_cmd_id)
    {
        i4_ret = _mmp_thumbnailmode_activate((UINT32)pv_cmd_param);
        pt_this->b_thumb_active = TRUE;
        return i4_ret;
    }
    else if (MMP_FILE_BROWSER_CMD_ID_INACTIVATE == e_cmd_id)
    {
        i4_ret = _mmp_thumbnailmode_inactivate();
        pt_this->b_thumb_active = FALSE;
        return i4_ret;
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Thumbnail mode activate routine
 * @param   ui4_idx [in]   Focus file index
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_activate(UINT32 ui4_idx)
{
    MMP_TM_MEMBER_T*                  pt_this = &t_g_tm_member;
    MMP_BE_VP_RANGE_INFO_T           t_range_info={0};
    INT32                               i4_ret=MMPR_OK;
    BOOL                            b_is_usb = TRUE;
    HANDLE_T                        h_view_item = NULL_HANDLE;

    _mmp_thumbnailmode_set_is_first_loading(pt_this,FALSE);
    i4_ret = _mmp_thumbnailmode_view_activate(pt_this, ui4_idx);
    IS_MMPR_OK(i4_ret);

    pt_this->b_thumb_active = TRUE;
    t_range_info.ui1_row_num  = pt_this->ui1_max_v_num;
    t_range_info.ui1_col_num  = pt_this->ui1_max_h_num;
    mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_VP_RANGE_INFO,(VOID*)&t_range_info);
    i4_ret = mmp_thumbnailmode_view_update_driver_name(TRUE,&b_is_usb);
    MMPR_LOG_ON_FAIL(i4_ret);
    mmp_mc_list_set_play_present_mode(MMP_FP_PRESENT_MODE_FULL);
    /* If it is the DLNA the set the view as folder */
    if(b_is_usb == FALSE)
    {
        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE,(VOID*)(UINT32)FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
        pt_this->b_recursive = FALSE;

        h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
        i4_ret = c_wgl_do_cmd (h_view_item,
                                WGL_CMD_BTN_SET_TEXT,
                                WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_VIEW_BTN_FOLDERS)),
                                WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_VIEW_BTN_FOLDERS))));
        IS_MMPR_OK(i4_ret);
    }

    i4_ret = mmp_be_activate(MMP_RC_BROWSER_ID_THUMBNAIL, ui4_idx);
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Thumbnail mode inactivate routine
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_inactivate(VOID)
{
    MMP_TM_MEMBER_T*                pt_this = &t_g_tm_member;

    pt_this->b_thumb_active = FALSE;
    mmp_be_inactivate();
    _mmp_thumbnailmode_view_inactivate(pt_this);
    _mmp_thumbnailmode_set_is_first_loading(pt_this,FALSE);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_hide_optl
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_hide_optl(BOOL b_is_repaint)
{
    return mmp_thumbnailmode_optl_hide_ui(&t_g_tm_member, b_is_repaint);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_set_is_first_loading
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_thumbnailmode_set_is_first_loading(MMP_TM_MEMBER_T* pt_this,BOOL b_load_first_page)
{
    if(b_load_first_page == FALSE)
    {
        /* set loading first page. it'll set to TURE at  _mmp_thumbnailmode_ff_cb_fct again,if it's loading first page. */
        pt_this->b_load_first_page = FALSE;
    }
    else
    {
        pt_this->b_load_first_page = TRUE;
    }

}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_bwr_cmd_do
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_bwr_cmd_do(MMP_BE_BROWSER_CMD_ID_T e_cmd_id, VOID* pv_cmd_param)
{
    HANDLE_T                        h_thumb_item;
    switch (e_cmd_id)
    {
    case MMP_BE_BROWSER_CMD_ID_EXIT_BG_MODE:
    {
        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO);
        c_wgl_set_focus(h_thumb_item, WGL_SYNC_AUTO_REPAINT); //WGL_NO_AUTO_REPAINT
    }
        break;

    default:
        break;
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_bwr_data_xng
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_bwr_data_xng(const MMP_BE_UI_INFO_T* pt_upd_data)
{
    MMP_TM_MEMBER_T*                 pt_this = &t_g_tm_member;
    MMP_BE_UI_UPD_FIELD_T           e_upd_field = pt_upd_data->e_upd_field;
    BOOL                               b_upd_item_list = FALSE;
    HANDLE_T                          h_thumb_item=NULL_HANDLE;
    INT32                              i4_ret=MMPR_OK;
#if 0
    /*1. Check if it need to hide stop the waiting message timer Firstly.*/
    if((MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_LST & e_upd_field) ||
       (MMP_BE_UI_UPD_FIELD_NO_DEVICE & e_upd_field) ||
       (MMP_BE_UI_UPD_FIELD_MNT_LST & e_upd_field)  ||
       (MMP_BE_UI_UPD_FIELD_ITEM_LIST & e_upd_field))
    {
        /* List items, this notify is send when browse_eng begin load items or show empty message */
        _mmp_thumbnailmode_reset_wait_timer(pt_this, TRUE);

    }
#endif

    /* 2. Handle those notifications */
    if(MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_LST & e_upd_field)
    {
        pt_this->ui4_dir_num = pt_upd_data->ui4_dir_num;
        pt_this->ui4_file_num = pt_upd_data->ui4_file_num;
        //pt_this->ui4_focus_idx = pt_upd_data->ui4_focus_idx;

        _mmp_thumbnailmode_hide_optl(FALSE);
        b_upd_item_list = TRUE;

        //mmp_thumbnailmode_update_ui(pt_this, MMP_TM_UPDATE_REASON_FDLR_NAME, TRUE);

    } /*MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_LST*/


    if(MMP_BE_UI_UPD_FIELD_NO_DEVICE & e_upd_field)
    {
#ifdef APP_NAV_USB_PLD
        a_nav_active_component(NAV_COMP_ID_USB_PLD);
#endif

    } /*MMP_BE_UI_UPD_FIELD_NO_DEVICE*/

    if(MMP_BE_UI_UPD_FIELD_ACT_DEV_INVALID & e_upd_field)
    {
        _mmp_thumbnailmode_set_is_first_loading(pt_this,FALSE);

    } /*MMP_BE_UI_UPD_FIELD_ACT_DEV_INVALID*/


    if (MMP_BE_UI_UPD_FIELD_MNT_LST & e_upd_field)
    {
        pt_this->ui4_dir_num = pt_upd_data->ui4_dir_num;
        pt_this->ui4_file_num = 0;
        //pt_this->ui4_focus_idx = pt_upd_data->ui4_focus_idx;

        _mmp_thumbnailmode_hide_optl(FALSE);
        b_upd_item_list = TRUE;
    } /*MMP_BE_UI_UPD_FIELD_MNT_LST*/

    if (MMP_BE_UI_UPD_FIELD_ITEM_LIST & e_upd_field)
    {
        _mmp_thumbnailmode_hide_optl(FALSE);
        /* hide animation */
        //i4_ret = mmp_thumbnailmode_view_hide_animation();
        //IS_MMPR_OK(i4_ret);
        mmp_mc_list_remove_all(MMP_GROUND_MODE_ALL);

        if (pt_upd_data->ui4_dir_num + pt_upd_data->ui4_file_num == 0)
        {
            pt_this->b_is_parsing_folder = FALSE;
            mmp_thumbnailmode_update_ui(pt_this, MMP_TM_UPDATE_REASON_HIDE_FILE_INFO, TRUE);
            _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect, FALSE,FALSE);
            c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm,WGL_SW_HIDE_RECURSIVE);
            c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,TRUE);
            mmp_thumbnailmode_update_ui(pt_this, MMP_TM_UPDATE_RESAON_PAGE, TRUE);
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
            DBG_INFO(("h_thumb_item=%d\n", (int)h_thumb_item));
            c_wgl_set_focus(pt_this->h_last_focus_wigt,WGL_SYNC_AUTO_REPAINT);
            pt_this->b_refersh_data_ready = TRUE;
        }
        else
        {
            if(pt_this->b_load_first_page == TRUE)
            {
                /* current is loading the first page, so parse done ,and only update the scoll bar*/
            }
            else
            {
                b_upd_item_list = TRUE;
            }
        }

        pt_this->ui4_dir_num = pt_upd_data->ui4_dir_num;
        pt_this->ui4_file_num = pt_upd_data->ui4_file_num;
        //pt_this->ui4_focus_idx = pt_upd_data->ui4_focus_idx;
        _mmp_thumbnailmode_set_is_first_loading(pt_this,FALSE);

        DBG_INFO_DIRECT("[mmp tn] %s %d <MMP_BE_UI_UPD_FIELD_ITEM_LIST> b_upd_item_list:%d ui4_dir_num:%d ui4_file_num:%d\r\n",__FUNCTION__,__LINE__,b_upd_item_list,pt_this->ui4_dir_num,pt_this->ui4_file_num);
    } /*MMP_BE_UI_UPD_FIELD_ITEM_LIST*/

    if (MMP_BE_UI_UPD_FIELD_FOLDER_XNG & e_upd_field)
    {
        DBG_INFO_DIRECT("[mmp tn] %s %d <MMP_BE_UI_UPD_FIELD_FOLDER_XNG>\r\n",__FUNCTION__,__LINE__);
        _mmp_thumbnailmode_hide_optl(FALSE);
        _mmp_thumbnailmode_set_is_first_loading(pt_this,FALSE);
        pt_this->ui4_focus_idx = 0;
        pt_this->ui1_hlt_idx = 0;
        pt_this->ui4_dir_num = 0;
    } /*MMP_BE_UI_UPD_FIELD_FOLDER_XNG*/

    if (MMP_BE_UI_UPD_FIELD_BK_PLAYER_STOP & e_upd_field)
    {
        mmp_thumbnailmode_update_ui(pt_this, MMP_TM_UDPATE_REASON_BK_PLAYER_STOP, TRUE);
    } /*MMP_BE_UI_UPD_FIELD_PLAYER_STOP*/

    if (MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_XNG & e_upd_field)
    {
        //mmp_thumbnailmode_update_ui(pt_this, MMP_TM_UPDATE_REASON_MEDIA_TYPE_XNG, TRUE);
    } /*MMP_BE_UI_UPD_FIELD_MEDIA_TYPE_XNG*/

    if (MMP_BE_UI_UPD_FIELD_PARSE_STATUS_UPD & e_upd_field)
    {
#ifdef APP_NET_DLNA_SUPPORT
        _mmp_thumbnailmode_hide_optl(FALSE);
        if (MMP_FF_PARSE_STATUS_PARSING == pt_upd_data->e_parse_status)
        {
            MMP_BE_FILE_SRC_TYPE_T      e_src_type = MMP_BE_FILE_SRC_MASS_STRG;
            CHAR                        s_curr_path[MMP_BE_MAX_PATH_LEN]={0};
            SIZE_T                      z_size = MMP_BE_MAX_PATH_LEN;
            BOOL                        b_is_folder_first_supported = FALSE;
            UINT32                      ui4_item_num_per_page;

            mmp_be_get_curr_path(s_curr_path, &z_size);
            mmp_be_get_file_src_type(s_curr_path, &e_src_type);

            b_is_folder_first_supported = c_fm_dlna_is_folder_sorting_supported(s_curr_path);

            ui4_item_num_per_page = pt_this->ui1_max_h_num * pt_this->ui1_max_v_num;

            if((MMP_BE_FILE_SRC_DLNA == e_src_type) &&
               (b_is_folder_first_supported) &&
               ((pt_upd_data->ui4_dir_num + pt_upd_data->ui4_file_num) > ui4_item_num_per_page))
           {
               if(pt_this->b_load_first_page == FALSE)
               {
                   //pt_this->ui4_focus_idx = pt_upd_data->ui4_focus_idx;
                   //b_upd_item_list = TRUE;

                   /* Show first page */
                   //_mmp_thumbnailmode_set_is_first_loading(pt_this,TRUE);
               }
           }
        }
#endif
        {
            pt_this->ui4_dir_num = pt_upd_data->ui4_dir_num;
            pt_this->ui4_file_num = pt_upd_data->ui4_file_num;
        }

    } /*MMP_BE_UI_UPD_FIELD_PARSE_STATUS_UPD*/

    if (MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME & e_upd_field)
    {
        DBG_INFO_DIRECT("[mmp tn] %s %d <MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME> \r\n",__FUNCTION__,__LINE__);
        //mmp_thumbnailmode_update_ui(pt_this, (MMP_TM_UPDATE_REASON_T)(MMP_TM_UPDATE_REASON_HIDE_ALL_THUMB | MMP_TM_UPDATE_REASON_FDLR_NAME), TRUE);
        //mmp_thumbnailmode_update_ui(pt_this, (MMP_TM_UPDATE_REASON_T)(MMP_TM_UPDATE_REASON_FDLR_NAME), TRUE);
        mmp_thumbnailmode_update_ui(pt_this, MMP_TM_UPDATE_RESAON_LEFT_UI,TRUE);
        i4_ret = mmp_thumbnailmode_view_set_path(TRUE);
        IS_MMPR_OK(i4_ret);
        /* disable all the transparent list */
        _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect, FALSE, TRUE);


    } /*MMP_BE_UI_UPD_FIELD_CRT_FDLR_NAME*/

    if (MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO & e_upd_field)
    {
        /* update the playing file info */
        //mmp_thumbnail_playing_file_info(pt_this);
    } /* MMP_BE_UI_UPD_FIELD_PLAY_ITEM_INFO */

    if (MMP_BE_UI_UPD_FIELD_PARSING_TIMEOUT & e_upd_field)
    {
       //mmp_thumbnailmode_view_show_animation();

    } /*  MMP_BE_UI_UPD_FIELD_PARSING_TIMEOUT */

    /*for photo frame udapte the option list device number*/
    if(MMP_BE_UI_UPD_FIELD_DEV_NUM_CHG & e_upd_field)
    {
        mmp_thumbnailmode_update_ui(pt_this, MMP_TM_UDPATE_REASON_DEV_NUM_CHG, TRUE);
    }
    if (MMP_BE_UI_UPD_FIELD_ACT_DEV_INVALID & e_upd_field)
    {
        /* active mount device is invalid */
        i4_ret = mmp_thumbnailmode_view_dev_remove_proc(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if (MMP_BE_UI_UPD_FIELD_MNT_DEV_XNG & e_upd_field)
    {
        /* active mount device has been changed */
        _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect,FALSE,FALSE);
        i4_ret = mmp_thumbnailmode_view_dev_mnt_xng_proc(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if (MMP_BE_UI_UPD_FIELD_LIMITED_FLDR & e_upd_field)
    {
    }

    if (MMP_BE_UI_UPD_FIELD_OPEN_FLDR_FAIL & e_upd_field)
    {
    }

    if (b_upd_item_list)
    {
        _mmp_thumbnailmode_upd_item_list(pt_this, pt_upd_data->ui4_focus_idx);
        pt_this->b_refersh_data_ready = TRUE;
    }

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_view_init
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_init(MMP_TM_MEMBER_T* pt_this)
{
    ISO_639_LANG_T                  s639_lang;
    INT32                           i4_ret=MMPR_OK;
    INT32                           i, i4_count, i4_x, i4_y;
    GL_RECT_T                       t_rect={0};
    HANDLE_T                        h_thumb_item=NULL_HANDLE,h_folder_item=NULL_HANDLE;
    MMP_TM_TRANSPARENT_T*           pt_transp = &pt_this->at_transp;
    WGL_HIMG_TPL_T              h_img_tpl;
    WGL_IMG_INFO_T              t_img_info;
    WDK_ICON_WIDGET_PARAM_T         t_icon_param;
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
    MMP_MC_BWSR_SETTING_T       t_bwsr_setting;
#endif
    WGL_FONT_INFO_T     t_font_info = {0};

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret == APP_CFGR_OK)
    {
        pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }
    else
    {
        pt_this->ui1_gui_lang_id = 0;
        DBG_ERROR(("<MMP thumbnail >Get gui lanugage failed!, set lang id = 0 \r\n"));
    }
    do {
        /* image init */
        i4_ret = mmp_img_init();
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        /* Create widgets. */
        i4_ret = _mmp_thumbnailmode_view_reg_cb();
        IS_MMPR_OK(i4_ret);

        i4_ret = mmp_mmp_create_ui(mmp_main_get_canvas());
       if(MMPR_OK != i4_ret)
       {
          break;
       }



       pt_this->h_frm_right_base_frm = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_RIGHT_BASE_FRM);

      i4_ret = c_wgl_do_cmd(pt_this->h_frm_right_base_frm,
                    WGL_CMD_GL_SET_ATTACH_DATA,
                    WGL_PACK(pt_this),
                    NULL);
      if (MMPR_OK != i4_ret)
       {
           break;
       }

       h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
       i4_ret = c_wgl_do_cmd(h_thumb_item,
                       WGL_CMD_GL_SET_ATTACH_DATA,
                       WGL_PACK(pt_this),
                       NULL);
       if (MMPR_OK != i4_ret)
        {
            break;
        }


       h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
       i4_ret = c_wgl_do_cmd(h_thumb_item,
                       WGL_CMD_GL_SET_ATTACH_DATA,
                       WGL_PACK(pt_this),
                       NULL);
       if (MMPR_OK != i4_ret)
        {
            break;
        }

       h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
       i4_ret = c_wgl_do_cmd(h_thumb_item,
                       WGL_CMD_GL_SET_ATTACH_DATA,
                       WGL_PACK(pt_this),
                       NULL);
       if (MMPR_OK != i4_ret)
        {
            break;
        }


        /* get some widget handles */
        pt_this->h_frm_base_frm                  = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_BASE_FRM);
        pt_this->h_frm_left_base_frm            = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_BASE_FRM);
        pt_this->h_frm_left_ui_frm1             = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
        pt_this->h_frm_thumbnailmode_ui_frm    = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_THUMBNAILMODE_UI);
        pt_this->h_info_frm                      = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO);
        pt_this->h_frm_htl_thumbnail_mov_frm   = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_HLT_THUMB_MOV_FRM);
        pt_this->h_frm_htl_folder_mov_frm       = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_HLT_FOLDER_MOVE_FRM);
        pt_this->h_folder_text                   = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEXT_455);
        pt_this->h_btn_right_to_left_btn        = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_RIGHT_TO_LEFT_BTN);
        pt_this->h_pop_up_exculde_help_text     = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_EXCLUDE_STATUS_TEXT);
        pt_this->h_last_focus_wigt              = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
        pt_this->h_last_left_focus_wigt         =pt_this->h_last_focus_wigt;
        pt_this->b_recursive                          =TRUE;
        pt_this->effect_type                          = 0;

        /*  set the navigation of widgets     */
        i4_ret = _mmp_thumbnailmode_set_navigation(pt_this);


        /*skip icon on pop-up dialog*/
        t_icon_param.h_parent             = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_POP_UP_BASE_FRM);
        t_icon_param.ui1_alpha            = 255;
        t_icon_param.b_visibility         = TRUE;
        t_icon_param.i4_x                 = MMP_TM_IMG_PREVIEW_X + MMP_TM_IMG_PREVIEW_W - MMP_TM_POP_UP_SKIP_ICON_W - MMP_TM_POP_UP_BASE_FRM_X;
        t_icon_param.i4_y                 = MMP_TM_IMG_PREVIEW_Y - MMP_TM_POP_UP_BASE_FRM_Y;
        t_icon_param.i4_w                 = MMP_TM_POP_UP_SKIP_ICON_W;
        t_icon_param.i4_h                 = MMP_TM_POP_UP_SKIP_ICON_H;
        t_icon_param.ui4_style            = 0;
        t_icon_param.b_img_bk             = FALSE;
        t_icon_param.ui1_img_align_style  = WGL_AS_CENTER_CENTER;
        t_icon_param.t_img_param.h_disable= h_g_mmp_pop_up_exculde_htl_icon;
        t_icon_param.t_img_param.h_enable = h_g_mmp_pop_up_exculde_htl_icon;
        t_icon_param.t_img_param.h_highlight= h_g_mmp_pop_up_exculde_htl_icon;
        t_icon_param.pt_clr_bk            = NULL;
        t_icon_param.pf_wdgt_proc         = NULL;
        t_icon_param.ph_created_icon      = &pt_this->h_pop_up_skip_icon;
        i4_ret = a_wdk_create_icon_widget (t_icon_param);
        if (i4_ret < WDKR_OK)
        {
           break;
        }
        c_wgl_insert(pt_this->h_pop_up_skip_icon,
                     mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_IMAGE_PREVIEW_FRM),
                     WGL_INSERT_BEFORE,
                     FALSE);

        /* create the option list  */
        i4_ret = mmp_thumbnailmode_optl_create(pt_this);
        if (MMPR_OK != i4_ret)
        {
            break;
        }
        /* set thumbnails transparent rect */
        i4_count = TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_V_NUM;
        i4_x = 0;
        i4_y = 0;

        for(i = 0; i < i4_count; i++)
        {
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + i * 2);
            c_wgl_get_coords(h_thumb_item, WGL_COORDS_SCREEN, &t_rect);
            pt_transp->at_rect[i].i4_left   = t_rect.i4_left + MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            pt_transp->at_rect[i].i4_top    = t_rect.i4_top  + MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            pt_transp->at_rect[i].i4_right  = t_rect.i4_right- MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            pt_transp->at_rect[i].i4_bottom = t_rect.i4_bottom-MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            pt_transp->ab_is_enable[i] = FALSE;

            i4_x++;
            if(i4_x >= TM_THUMB_ITEM_FRAME_H_NUM)
            {
                i4_x = 0;
                i4_y++;
            }
        }
        i4_ret = c_wgl_create_transparent_list(mmp_main_get_canvas(),
                                               pt_transp->at_rect,
                                               i4_count,
                                               &pt_this->h_transparent_rect);
        if (MMPR_OK != i4_ret)
        {
            break;
        }


#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        t_bwsr_setting.ui4_mask = MMP_MC_BWSR_SETTING_MSK_DEF_FCS_WGT;
        t_bwsr_setting.h_def_focus_widget = pt_this->h_frm_thumbnailmode_ui_frm;

        i4_ret = mmp_mc_set_browser_setting(MMP_RC_BROWSER_ID_THUMBNAIL,
                                          &t_bwsr_setting);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#endif

        pt_this->ui1_max_h_num = TM_THUMB_SMALL_ITEM_FRAME_H_NUM;
        pt_this->ui1_max_v_num = TM_THUMB_SMALL_ITEM_FRAME_V_NUM;

        /*Create transparent list for preview*/
        SET_RECT_BY_SIZE (&pt_this->t_rect_preview,
                          MMP_TM_IMG_PREVIEW_X,
                          MMP_TM_IMG_PREVIEW_Y,
                          MMP_TM_IMG_PREVIEW_W,
                          MMP_TM_IMG_PREVIEW_H);
        i4_ret = c_wgl_create_transparent_list(mmp_main_get_canvas(),
                                               &pt_this->t_rect_preview,
                                               1,
                                               &pt_this->h_preview_trans_list);

        if (WGLR_OK != i4_ret)
        {
            break;
        }

        t_img_info.e_type = WGL_IMG_SET_BASIC;
        for (i = 0;i < MMP_THMBNAILMODE_MAX_THUMBS ;i++)
        {
            h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_PRE_FOLDER + i * 2);
            pt_this->h_thumbnail_folder_img = h_g_mmp_lg_folder_icon;
            h_img_tpl = pt_this->h_thumbnail_folder_img;
            t_img_info.u_img_data.t_basic.t_enable =  h_img_tpl;
            t_img_info.u_img_data.t_basic.t_disable =  h_img_tpl;
            IS_MMPR_OK (c_wgl_do_cmd (h_folder_item,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK),
                              WGL_PACK (& t_img_info)));
            c_wgl_set_visibility(h_folder_item,WGL_SW_HIDE);
        }
        for (i = 0;i <MMP_THMBNAILMODE_MAX_THUMBS ;i++)
        {
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + i * 2);
            /* set font size */
            t_font_info.e_font_size = FE_FNT_SIZE_CUSTOM;
            t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
            t_font_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
            c_strcpy(t_font_info.a_c_font_name , SN_FONT_DEFAULT_SMALL);
            t_font_info.ui1_custom_size = 17;
            i4_ret = c_wgl_do_cmd(h_thumb_item,
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK(&t_font_info),
                                  NULL);

            c_wgl_set_visibility (h_thumb_item, WGL_SW_HIDE_RECURSIVE);
            i4_ret = c_wgl_do_cmd (h_thumb_item,
                                  WGL_CMD_BTN_SET_TEXT,
                                  WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUMB_LOAD_FAIL_TXT)),
                                  WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUMB_LOAD_FAIL_TXT))));
        }
        return MMPR_OK;
    } while ( 0 );

    _mmp_thumbnailmode_view_deinit(pt_this);
    return MMPR_FAIL;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_view_deinit
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_deinit(MMP_TM_MEMBER_T* pt_this)
{
    INT32                       i4_ret=MMPR_OK;

    if(NULL == pt_this)
    {
        MMP_DBG_ERROR(("pt_this cannot be NULL.\r\n"));
        return MMPR_INV_ARG;
    }

    i4_ret = mmp_thumbnailmode_optl_destroy(pt_this);
    if(MMPR_OK!= i4_ret)
    {
        MMP_DBG_ERROR(("mmp_thumbnailmode_optl_destroy() fail. i4_ret = %d.\r\n", i4_ret));
    }

    i4_ret = c_wgl_delete_transparent_list(pt_this->h_transparent_rect);
    if(MMPR_OK!= i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_delete_transparent_list() fail. i4_ret = %d.\r\n", i4_ret));
    }

    i4_ret = c_wgl_delete_transparent_list(pt_this->h_preview_trans_list);
    if(MMPR_OK!= i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_delete_transparent_list() fail. i4_ret = %d.\r\n", i4_ret));
    }

#ifdef APP_NET_NEIGHBOR_SUPPORT
    i4_ret = mmp_thumbnailmode_pwd_dlg_destroy(pt_this);
    if(MMPR_OK!= i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_tm_view_pwd_dlg_destory() fail. i4_ret = %d.\r\n", i4_ret));
    }
#endif

    /* deinit view */
    i4_ret = c_wgl_destroy_widget(pt_this->h_frm_base_frm);
    if(MMPR_OK!= i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_destroy_widget() fail. i4_ret = %d.\r\n", i4_ret));
    }

    i4_ret = mmp_img_deinit();
    if(MMPR_OK!= i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_destroy_widget() fail. i4_ret = %d.\r\n", i4_ret));
    }

    if (NULL != pt_this->pv_drc_snapshot_thumb)
    {
        mmp_drc_snapshot_free(pt_this->pv_drc_snapshot_thumb);
    }

    /*
    i4_ret = mmp_common_ui_animation_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);
*/
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_view_activate
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_activate(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_idx)
{
    MMP_BE_STATUS_T             e_status;
    ISO_639_LANG_T              s639_lang;
    INT32                         i4_ret = MMPR_OK;
    HANDLE_T                     h_view_item=NULL_HANDLE;
    UINT32     ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;
    SIZE_T z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP thumbnail >Can't init lanugage \r\n"));
        pt_this->ui1_gui_lang_id =0;
    }
    else
    {
        pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }

    pt_this->b_is_dev_list_show =FALSE;
    pt_this->b_is_parsing_folder = FALSE;
    pt_this->b_optl_show = FALSE;

    /* when first come in  show and hide some frames   */
    IS_MMPR_OK (c_wgl_set_visibility (pt_this->h_frm_base_frm,WGL_SW_NORMAL));
    IS_MMPR_OK (c_wgl_set_visibility (pt_this->h_frm_left_base_frm,WGL_SW_NORMAL));

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_LOGO_ICON);
    IS_MMPR_OK (c_wgl_set_visibility (h_view_item,WGL_SW_RECURSIVE));

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
    IS_MMPR_OK (c_wgl_set_visibility (h_view_item,WGL_SW_RECURSIVE));

    pt_this->h_frm_right_base_frm = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_RIGHT_BASE_FRM);
    IS_MMPR_OK (c_wgl_set_visibility (pt_this->h_frm_right_base_frm, WGL_SW_NORMAL));

    IS_MMPR_OK (c_wgl_set_visibility (pt_this->h_frm_htl_folder_mov_frm , WGL_SW_HIDE));

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_THUMBNAILMODE_UI);
    IS_MMPR_OK (c_wgl_set_visibility (h_view_item, WGL_SW_NORMAL));

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_POP_UP_BASE_FRM);
    IS_MMPR_OK (c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE));

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_RIGHT_TO_LEFT_BTN);
    IS_MMPR_OK (c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE));

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_PAGE_NUM);
    IS_MMPR_OK (c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE));

    IS_MMPR_OK (c_wgl_set_visibility (pt_this->h_frm_htl_folder_mov_frm , WGL_SW_HIDE));
    IS_MMPR_OK (c_wgl_set_visibility (pt_this->h_frm_htl_thumbnail_mov_frm , WGL_SW_HIDE));

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("MMP thumbnailmode get language fall \r\n"));
        pt_this->ui1_gui_lang_id =0;
    }
    else
    {
        pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }
    _mmp_thumbnailmode_init_attrib_settings(pt_this);
    _mmp_thumbnailmode_ch_lang_text(pt_this->ui1_gui_lang_id);
    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);
    mmp_mc_browse_show_info_handler(FALSE,FALSE,FALSE);
    c_wgl_repaint(pt_this->h_frm_base_frm,NULL,TRUE);
    i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                       (VOID*) &ui4_exit_reason, z_size);
    MMPR_LOG_ON_FAIL(i4_ret);

    return  i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_view_inactivate
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_inactivate(MMP_TM_MEMBER_T* pt_this)
{
    //INT32   i4_ret;

    pt_this->b_is_parsing_folder = FALSE;

    mmp_mc_browse_stop_file_thumbnail();
    mmp_mc_browse_reset_info_resoruce();

    _mmp_thumbnailmode_disable_transparent_list (pt_this->h_transparent_rect,FALSE,FALSE);

    pt_this->e_popup_status = MMP_TM_POPUP_STATUS_OFF;
    /* animation hide */
    //i4_ret = mmp_common_ui_animation_hide();
   // MMPR_LOG_ON_FAIL(i4_ret);
    return  c_wgl_show (pt_this->h_frm_base_frm, WGL_SW_HIDE);
}

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_pop_up_strart_slideshow_nfy_frm
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_strart_slideshow_nfy_frm (HANDLE_T    h_widget,
                                                                 UINT32      ui4_msg,
                                                                 VOID*       pv_param1,
                                                                 VOID*       pv_param2)
{
    MMP_TM_MEMBER_T*            pt_this=&t_g_tm_member;
    BOOL                        b_is_allow_traverse = FALSE;
    UINT32                      ui4_key_code = (UINT32) pv_param1;
    INT32                       i4_ret = MMPR_OK;
    UINT32                      ui4_file_idx, ui4_play_idx = MMP_NULL_FILE_IDX;
    MMP_PL_ATTR_T               at_attr2[3];
    UINT8                       ui1_cfg_value = 0;
    UINT32                      ui4_cfg_value = 0;
    MMP_EFFECT_T                effect_item = {0};

    c_memset(&at_attr2,0,3*sizeof(MMP_PL_ATTR_T));

    b_is_allow_traverse = (FALSE == pt_this->b_is_parsing_folder) && (FALSE == pt_this->b_is_nofile_show);
    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
            {
                if(pt_this->b_load_first_page || FALSE == b_is_allow_traverse)
                {
                    break;
                }


                if (mmp_be_is_item_in_list(MMP_BE_FF_IDX_CRT, ITEM_TYPE_NONE, pt_this->ui4_focus_idx, MMP_FF_ITEM_LIST_TYPE_SKIP_LIST))
                {
                    i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT, MMP_NULL_FILE_IDX, &ui4_file_idx);
                    if (MMPR_OK == i4_ret)
                    {
                        ui4_play_idx = pt_this->ui4_dir_num + ui4_file_idx;
                    }
                }
                else
                {
                    ui4_play_idx = pt_this->ui4_focus_idx;
                }

                if (MMP_NULL_FILE_IDX == ui4_play_idx)
                {
                    break;
                }


                _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect,
                                                 FALSE,
                                                 FALSE);

                /* get shuffle attr */
                a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);
                if(ui1_cfg_value == 0)
                {
                    ui4_cfg_value = MMP_SHUFFLE_MODE_SEQUENTIAL;
                }
                else
                {
                    ui4_cfg_value = MMP_SHUFFLE_MODE_SHUFFLE;
                }
                at_attr2[0].e_id = MMP_PL_ATTR_ID_PHOTO_SHUFFLE;
                at_attr2[0].pv_param = (VOID*)ui4_cfg_value;


                /* get speed attr */
                a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);
                MMP_PP_RC_DLB_GET_SPEED((UINT32)ui1_cfg_value, ui4_cfg_value);
                at_attr2[1].e_id = MMP_PL_ATTR_ID_DURATION;
                at_attr2[1].pv_param = (VOID*)ui4_cfg_value;

                /* get effect attr */
                a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);

                switch(ui1_cfg_value)
                {
                    case 0:
                         ui4_cfg_value = mmp_tm_rand()%7+1;
                         break;
                    case 1:
                         ui4_cfg_value = TFX_DISSOLVE;
                         break;
                    case 2:
                         ui4_cfg_value = TFX_WIPE_RIGHT;
                         break;
                    case 3:
                         ui4_cfg_value = TFX_WIPE_LEFT;
                         break;
                    case 4:
                        ui4_cfg_value = TFX_WIPE_UP;
                        break;
                    case 5:
                        ui4_cfg_value = TFX_WIPE_DOWN;
                        break;
                    case 6:
                        ui4_cfg_value = TFX_BOX_IN;
                        break;
                    case 7:
                        ui4_cfg_value = TFX_BOX_OUT;
                        break;
                    default:
                        ui4_cfg_value = TFX_WIPE_LEFT;
                        break;
                }
                effect_item.e_effect  = ui4_cfg_value;
                effect_item.b_is_enabled =TRUE;
                at_attr2[2].e_id = MMP_PL_ATTR_ID_EFFECT;
                at_attr2[2].pv_param = &effect_item;

                i4_ret = mmp_mc_list_set_attr(3, at_attr2);
                pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;

                mmp_be_cd_child(ui4_play_idx);

                IS_MMPR_OK (c_wgl_set_visibility (pt_this->h_frm_base_frm, WGL_SW_HIDE_RECURSIVE));
                IS_MMPR_OK(c_wgl_repaint(pt_this->h_frm_base_frm,NULL,TRUE));
            }
            break;

            case BTN_INPUT_SRC:
            case BTN_EXIT:
            case BTN_RED:
                _mmp_thumbnailmode_hide_pop_up_page(pt_this);
                mmp_thumbnail_display_file_info(pt_this);
                break;

                default:
                    break;
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
        c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_pop_up_fullscreen_nfy_frm
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_fullscreen_nfy_frm (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{

    MMP_TM_MEMBER_T*            pt_this = &t_g_tm_member;
    UINT32                      ui4_key_code = (UINT32) pv_param1;
    INT32                       i4_ret=MMPR_OK;
    UINT32                      ui4_play_idx = MMP_NULL_FILE_IDX;
    UINT32                      ui4_file_idx = 0;
    MMP_EFFECT_T                effect_item = {0};
    MMP_PL_ATTR_T               at_attr2[3];
    UINT8                       ui1_cfg_value = 0;
    UINT32                      ui4_cfg_value = 0;

    c_memset(&at_attr2,0,3*sizeof(MMP_PL_ATTR_T));


    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {

        switch (ui4_key_code)
       {
           case MMP_TM_BTN_SELECT:

                if (mmp_be_is_item_in_list(MMP_BE_FF_IDX_CRT, ITEM_TYPE_NONE, pt_this->ui4_focus_idx, MMP_FF_ITEM_LIST_TYPE_SKIP_LIST))
                {
                    i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT, MMP_NULL_FILE_IDX, &ui4_file_idx);
                    if (MMPR_OK == i4_ret)
                    {
                        ui4_play_idx = pt_this->ui4_dir_num + ui4_file_idx;
                    }
                }
                else
                {
                    ui4_play_idx = pt_this->ui4_focus_idx;
                }

                if (MMP_NULL_FILE_IDX == ui4_play_idx)
                {
                    break;
                }

               c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm,WGL_SW_HIDE_RECURSIVE);
               c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,TRUE);
               /* get shuffle attr */
                a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);
                if(ui1_cfg_value == 0)
                {
                    ui4_cfg_value = MMP_SHUFFLE_MODE_SEQUENTIAL;
                }
                else
                {
                    ui4_cfg_value = MMP_SHUFFLE_MODE_SHUFFLE;
                }
                at_attr2[0].e_id = MMP_PL_ATTR_ID_PHOTO_SHUFFLE;
                at_attr2[0].pv_param = (VOID*)ui4_cfg_value;


                /* get speed attr */
                a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);
                MMP_PP_RC_DLB_GET_SPEED((UINT32)ui1_cfg_value, ui4_cfg_value);
                at_attr2[1].e_id = MMP_PL_ATTR_ID_DURATION;
                at_attr2[1].pv_param = (VOID*)ui4_cfg_value;

                /* get effect attr */
                a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);

                switch(ui1_cfg_value)
                {
                    //case 0:
                         //ui4_cfg_value = mmp_tm_rand()%7+1;
                    //   break;
                    case 1:
                         ui4_cfg_value = TFX_DISSOLVE;
                         break;
                    case 2:
                         ui4_cfg_value = TFX_WIPE_RIGHT;
                         break;
                    case 3:
                         ui4_cfg_value = TFX_WIPE_LEFT;
                         break;
                    case 4:
                        ui4_cfg_value = TFX_WIPE_UP;
                        break;
                    case 5:
                        ui4_cfg_value = TFX_WIPE_DOWN;
                        break;
                    case 6:
                        ui4_cfg_value = TFX_BOX_IN;
                        break;
                    case 7:
                        ui4_cfg_value = TFX_BOX_OUT;
                        break;
                    default:
                        ui4_cfg_value = TFX_WIPE_LEFT;
                        break;
                }
                effect_item.e_effect  = ui4_cfg_value;
                effect_item.b_is_enabled =TRUE;
                at_attr2[2].e_id = MMP_PL_ATTR_ID_EFFECT;
                at_attr2[2].pv_param = &effect_item;

               i4_ret = mmp_mc_list_set_attr(3, at_attr2);
               IS_MMPR_OK(i4_ret);

               pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                i4_ret = mmp_be_start_play_crnt_folder(ui4_play_idx,TRUE);
               IS_MMPR_OK(i4_ret);
               break;

           case BTN_INPUT_SRC:
           case BTN_EXIT:
           case BTN_RED:
               _mmp_thumbnailmode_hide_pop_up_page(pt_this);
               mmp_thumbnail_display_file_info(pt_this);
               break;

           default:
           {
               i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
               MMPR_LOG_ON_FAIL(i4_ret);
           }

           break;
       }

    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_FULLSCREEN));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_FULL_SCREEN)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_FULL_SCREEN))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
        c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);

    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_pop_up_info_btn_cb
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_info_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{

    MMP_TM_MEMBER_T*            pt_this = &t_g_tm_member;
    UINT32                       ui4_key_code = (UINT32) pv_param1;
    INT32                         i4_ret=MMPR_OK;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
       {
            case MMP_TM_BTN_SELECT:
               mmp_thumbnail_display_file_info(pt_this);
               break;

            case BTN_INPUT_SRC:
            case BTN_EXIT:
            case BTN_RED:
               _mmp_thumbnailmode_hide_pop_up_page(pt_this);
               mmp_thumbnail_display_file_info(pt_this);
               break;

           default:
           {
               i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
               MMPR_LOG_ON_FAIL(i4_ret);
           }
           break;
       }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_INFO));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_INFO)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_INFO))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
        c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_rotate_preview
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_rotate_preview(MMP_TM_MEMBER_T* pt_this, BOOL b_clockwise)
{
    UINT32                          ui4_cnt = 1;
    MMP_ITEM_INFO_T                 t_item_info = {0};
    MMP_FF_ITEM_FLAG_T              e_item_flag, e_rotate_flag = MMP_FF_ITEM_FLAG_EMPTY;
    SIZE_T                          z_size = sizeof(IMG_ROTATE_OP_TYPE_T);
    IMG_ROTATE_OP_TYPE_T            e_img_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
    MMP_FP_LOAD_IMG_ROTATE_OP_T     e_mmp_rotate = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;
    INT32                           i4_ret;
    CHAR                            s_full_path[MMP_BE_MAX_PATH_LEN] = {0};

    if (pt_this->ui1_hlt_idx < TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_H_NUM &&
        FALSE == pt_this->at_transp.ab_is_enable[pt_this->ui1_hlt_idx])
    {
        return MMPR_OK;
    }

    i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE,
                                  pt_this->ui4_focus_idx,
                                  &ui4_cnt,
                                  &t_item_info);
    if (MMPR_OK != i4_ret)
    {
        return MMPR_NOT_SUPPORT;
    }
    e_item_flag = t_item_info.e_flag;
    MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);

    DBG_INFO_DIRECT("[mmp tn] %s %d e_item_flag:0x%x \r\n",__FUNCTION__,__LINE__,e_item_flag);

    if (0 == (MMP_BE_ITEM_FLAG_ROTATE & e_item_flag))
    {
        /*Apply file rotate info first*/
        i4_ret = mmp_mc_browse_get_file_info(MMP_FP_INFO_TYPE_ROTATION, &z_size, (UINT8*)&e_img_rotate);
        if (MMPR_OK != i4_ret)
        {
            e_img_rotate = IMG_ROTATE_CLOCKWS_0_OP_TYPE;
        }
        MMP_BE_RC_GET_ITEM_FLAG_FROM_ROTATE(e_img_rotate, e_rotate_flag)
        e_rotate_flag |= MMP_BE_ITEM_FLAG_ROTATE;

        e_item_flag |= e_rotate_flag;
    }

    /*Get current rotate from item flag*/
    MMP_BE_RC_GET_IMG_ROTATE_FROM_ITEM_FLAG(e_item_flag, e_img_rotate);

    /*Get next rotate type*/
    MMP_BE_RC_GET_NEXT_ROTATE(e_img_rotate, b_clockwise);

    /*Get new rotate flag*/
    e_rotate_flag = MMP_FF_ITEM_FLAG_EMPTY;
    MMP_BE_RC_GET_ITEM_FLAG_FROM_ROTATE(e_img_rotate, e_rotate_flag);

    c_wgl_enable_transparent_list(pt_this->h_preview_trans_list, FALSE, FALSE);
    c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_rect_preview, TRUE);

    DBG_INFO_DIRECT("[mmp tn] %s %d e_img_rotate:%d e_item_flag:0x%x \r\n",__FUNCTION__,__LINE__,e_img_rotate,e_item_flag);

    /*Perform rotate*/
    MMP_BE_RC_GET_MMP_ROTATE_FROM_ITEM_FLAG(e_rotate_flag, e_mmp_rotate);
    i4_ret = mmp_mc_browse_load_file_thumbnail_ex(s_full_path,
                                                  &pt_this->t_rect_preview,
                                                  MMP_FP_THUMB_COORDS_CANVAS,
                                                  e_mmp_rotate,
                                                  NULL);
    if (MMPR_OK != i4_ret)
    {
        return MMPR_NOT_SUPPORT;
    }

    /*Save JPEG file info*/
    mmp_mc_browse_set_file_info(MMP_FP_INFO_TYPE_ROTATION, &z_size, (UINT8*)&e_img_rotate);

    /*Save back item flag*/
    MMP_BE_RC_APPLY_ROTATE_FLAG(e_item_flag, e_rotate_flag);
    mmp_be_set_item_status(ITEM_TYPE_NONE, pt_this->ui4_focus_idx, e_item_flag);

    pt_this->b_preview_rotate = TRUE;

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_pop_up_rotate_left_btn_cb
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_rotate_left_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{

    MMP_TM_MEMBER_T*                pt_this = &t_g_tm_member;
    UINT32                          ui4_key_code = (UINT32) pv_param1;
    INT32                           i4_ret=MMPR_OK;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
                _mmp_thumbnailmode_rotate_preview(pt_this, FALSE);
                break;

            case BTN_INPUT_SRC:
            case BTN_EXIT:
            case BTN_RED:
               _mmp_thumbnailmode_hide_pop_up_page(pt_this);
               mmp_thumbnail_display_file_info(pt_this);
               break;

            default:
           {
               i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
               MMPR_LOG_ON_FAIL(i4_ret);
           }
                break;
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_LEFT));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_LEFT)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_LEFT))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
        c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_pop_up_rotate_right_btn_cb
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_rotate_right_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{

    MMP_TM_MEMBER_T*             pt_this = &t_g_tm_member;
    UINT32                          ui4_key_code = (UINT32) pv_param1;
    INT32                           i4_ret=MMPR_OK;
    HANDLE_T                         h_thumb_item =  NULL_HANDLE;
#ifdef APP_NET_DLNA_SUPPORT
    MMP_BE_FILE_SRC_TYPE_T      e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                            s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                          z_size = MMP_BE_MAX_PATH_LEN;
#endif


    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
                _mmp_thumbnailmode_rotate_preview(pt_this, TRUE);
                break;
            case BTN_INPUT_SRC:
            case BTN_EXIT:
            case BTN_RED:
               _mmp_thumbnailmode_hide_pop_up_page(pt_this);
               mmp_thumbnail_display_file_info(pt_this);
               break;
            case MMP_TM_BTN_CURSOR_RIGHT:

            #ifdef APP_NET_DLNA_SUPPORT
                 /* get current path */
                i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                /* if source is Net, we did not support more feature */
                if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                   (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                {
                }
                else
            #endif
                {
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_STOP_BTN);
                    c_wgl_set_focus(h_thumb_item,WGL_SYNC_AUTO_REPAINT);
                }
               break;
            default:
           {
               i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
               MMPR_LOG_ON_FAIL(i4_ret);
           }
               break;
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_RIGHT));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_RIGHT)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_ROTATE_RIGHT))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
        c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_pop_up_rotate_right_btn_cb
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_pop_up_skip_btn_cb (HANDLE_T    h_widget,
                                          UINT32      ui4_msg,
                                          VOID*       pv_param1,
                                          VOID*       pv_param2)
{
    MMP_TM_MEMBER_T*           pt_this = &t_g_tm_member;
    UINT32                      ui4_key_code = (UINT32) pv_param1;
    INT32                        i4_ret=MMPR_OK;
    BOOL                         b_skip;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
            {
                if (pt_this->ui1_hlt_idx >= MMP_THMBNAILMODE_MAX_THUMBS)
                {
                    return MMPR_INV_ARG;
                }
                b_skip = !pt_this->b_skip_flag[pt_this->ui1_hlt_idx];
                _mmp_thumbnailmode_enable_skip_flag(pt_this, pt_this->ui1_hlt_idx, b_skip);
                if (b_skip)
                {
                    mmp_be_update_list_item(ITEM_TYPE_NONE,
                                            pt_this->ui4_focus_idx,
                                            MMP_FF_ITEM_LIST_TYPE_SKIP_LIST,
                                            MMP_FF_ITEM_LIST_OP_TYPE_ADD);
                }
                else
                {
                    mmp_be_update_list_item(ITEM_TYPE_NONE,
                                            pt_this->ui4_focus_idx,
                                            MMP_FF_ITEM_LIST_TYPE_SKIP_LIST,
                                            MMP_FF_ITEM_LIST_OP_TYPE_RMV);
                }
            }
            break;

            case BTN_INPUT_SRC:
            case BTN_EXIT:
            case BTN_RED:
               _mmp_thumbnailmode_hide_pop_up_page(pt_this);
               mmp_thumbnail_display_file_info(pt_this);
               break;

           default:
           {
               i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
               MMPR_LOG_ON_FAIL(i4_ret);
           }
               break;
       }
    }
    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_EXCLU_SKIP));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SKIP)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SKIP))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
        c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_settings_btn_nfy
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_thumbnailmode_hide_pop_up_page(MMP_TM_MEMBER_T* pt_this)
{
    HANDLE_T        h_thumb_item=NULL_HANDLE;

    c_wgl_enable_transparent_list(pt_this->h_preview_trans_list, FALSE, FALSE);
    c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_rect_preview, TRUE);


    _mmp_thumbnailmode_refresh_skip_flag(pt_this);

    if (MMP_TM_POPUP_STATUS_PREVIEW == pt_this->e_popup_status)
    {
        mmp_thumbnailmode_show_img_preview(pt_this, FALSE);
    }
    c_wgl_enable_transparent_list(pt_this->h_transparent_rect, TRUE, TRUE);
    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_POP_UP_BASE_FRM);
    c_wgl_set_visibility (h_thumb_item, WGL_SW_HIDE_RECURSIVE);
    c_wgl_repaint(h_thumb_item,NULL,TRUE);
    pt_this->e_popup_status = MMP_TM_POPUP_STATUS_OFF;
    c_wgl_set_focus(pt_this->h_frm_right_base_frm,WGL_SYNC_AUTO_REPAINT);

}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_settings_btn_nfy
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_pop_up_done_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    MMP_TM_MEMBER_T*           pt_this = &t_g_tm_member;
    UINT32                      ui4_key_code = (UINT32) pv_param1;
    INT32                        i4_ret=MMPR_OK;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
            case BTN_INPUT_SRC:
            case BTN_EXIT:
            case BTN_RED:
                _mmp_thumbnailmode_hide_pop_up_page(pt_this);
                //mmp_thumbnail_display_file_info(pt_this);
                break;

            default:
            {
                i4_ret = mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;
        }
    }
    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T  w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_POP_UP_BTN_DONE));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                       WGL_CMD_TEXT_SET_TEXT,
                       WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_DONE)),
                       WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_DONE))));

        IS_MMPR_OK(i4_ret);
        c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
        c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

#ifdef APP_TTS_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_view_btn_tts_play
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_btn_tts_play(VOID)
{
    INT32                   i4_ret = MMPR_OK;
    MMP_TM_MEMBER_T*        pt_this = &t_g_tm_member;
    UTF16_T                 w2s_str[128] = {0};

    HANDLE_T                h_device_item = NULL_HANDLE;
    HANDLE_T                h_start_slideshow_item = NULL_HANDLE;
    HANDLE_T                h_sort_item = NULL_HANDLE;
    HANDLE_T                h_view_item = NULL_HANDLE;
    HANDLE_T                h_settings_item = NULL_HANDLE;
    HANDLE_T                h_browse_music_item = NULL_HANDLE;

    h_device_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_LB_DRIVER);
    MMP_ASSERT(NULL_HANDLE != h_device_item);

    h_start_slideshow_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
    MMP_ASSERT(NULL_HANDLE != h_start_slideshow_item);

    h_sort_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
    MMP_ASSERT(NULL_HANDLE != h_sort_item);

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
    MMP_ASSERT(NULL_HANDLE != h_view_item);

    h_settings_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
    MMP_ASSERT(NULL_HANDLE != h_settings_item);

    h_browse_music_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BROWSE_MUSIC);
    MMP_ASSERT(NULL_HANDLE != h_view_item);

    if(pt_this->h_last_focus_wigt == h_device_item)
    {
        const char *    s_str = " USB1 ";
        c_uc_ps_to_w2s(s_str,w2s_str,c_strlen(s_str));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    else if(pt_this->h_last_focus_wigt == h_start_slideshow_item)
    {
       c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_BTN_START_SLIDESHOW));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    else if(pt_this->h_last_focus_wigt == h_sort_item)
    {
        UINT8   ui1_cfg_value = 0;
        UINT32  ui4_cfg_value = 0;

        a_cfg_custom_get_mmp_photo_sort(&ui1_cfg_value);
        if ((ui1_cfg_value < MMP_SORT_TYPE_PHOTO_DATE)
            ||(ui1_cfg_value > MMP_SORT_TYPE_PHOTO_INV_NAME))
        {
            ui1_cfg_value = MMP_SORT_TYPE_PHOTO_NAME;
            a_cfg_custom_set_mmp_photo_sort(ui1_cfg_value);
        }

        switch(ui1_cfg_value)
        {
            case MMP_SORT_TYPE_PHOTO_NAME:
                ui4_cfg_value = 0;
                break;
            case MMP_SORT_TYPE_PHOTO_INV_NAME:
                ui4_cfg_value = 1;
                break;
            case MMP_SORT_TYPE_PHOTO_DATE:
                ui4_cfg_value = 2;
                break;
            case MMP_SORT_TYPE_PHOTO_INV_DATE:
                ui4_cfg_value = 3;
                break;
            default:
                break;
        }
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SORT__NAME_A_Z+ui4_cfg_value));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    else if(pt_this->h_last_focus_wigt == h_view_item)
    {
        UINT32 ui4_recur_flag = 0;
        if(TRUE == pt_this->b_recursive)
        {
            ui4_recur_flag = 0;
        }
        else
        {
            ui4_recur_flag =  1;
        }

        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS+ui4_recur_flag));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    else if(pt_this->h_last_focus_wigt == h_settings_item)
    {
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_BTN_SETTINGS));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    else if(pt_this->h_last_focus_wigt == h_browse_music_item)
    {
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_BROWSE_MUSIC));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }

    return i4_ret;
}
#endif

/*---------------------------------------------------------------------------*/
/**
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_nfy_frm (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    INT32               i4_ret = MMPR_OK;
    BOOL                b_is_allow_traverse = FALSE;
    HANDLE_T        h_view_item=NULL_HANDLE;
    //UTF16_T           w2s_text[MMP_TM_VIEW_INFO_STR_MAX_LEN +1] = {0};
    GL_RECT_T           t_rect={0};
    UINT32              ui4_cnt=1;
    MMP_ITEM_INFO_T     t_item_info={0};

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        UINT32                  ui4_key_code = (UINT32) pv_param1;
        MMP_TM_MEMBER_T*          pt_this = NULL;
#ifdef APP_NET_NEIGHBOR_SUPPORT
        INT32                   i4_ret_neighbor = -1;
#endif
        c_wgl_do_cmd(h_widget,
                     WGL_CMD_GL_GET_ATTACH_DATA,
                     WGL_PACK(&pt_this),
                     NULL);
        MMP_ASSERT(pt_this != NULL);

        b_is_allow_traverse = (FALSE == pt_this->b_is_parsing_folder) && (FALSE == pt_this->b_is_nofile_show);

        switch (ui4_key_code)
        {
            case MMP_TM_BTN_CURSOR_LEFT:
                if(b_is_allow_traverse)
                {
                    i4_ret = _mmp_thumbnailmode_cursor_left_right(pt_this, TRUE);
                }
                break;
            case MMP_TM_BTN_CURSOR_RIGHT:
                if(b_is_allow_traverse)
                {
                   i4_ret =  _mmp_thumbnailmode_cursor_left_right(pt_this, FALSE);
                }
                break;
            case MMP_TM_BTN_CURSOR_UP:
                if(b_is_allow_traverse)
                {
                    i4_ret = _mmp_thumbnailmode_cursor_up_down(pt_this, TRUE);
                }
                break;
            case MMP_TM_BTN_CURSOR_DOWN:
                if(b_is_allow_traverse)
                {
                    i4_ret = _mmp_thumbnailmode_cursor_up_down(pt_this, FALSE);
                }
                break;
            case BTN_RETURN:
                h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_RIGHT_TO_LEFT_BTN);
                c_wgl_set_focus(h_view_item,TRUE);
             #ifdef APP_TTS_SUPPORT
                UTF16_T         w2s_str[128] = {0};
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
            #endif
                break;
            case MMP_TM_BTN_SELECT:
            {
                if(FALSE == b_is_allow_traverse)
                {
                    //break;
                }

                if(pt_this->b_load_first_page)
                {
                   // break;
                }

#ifdef APP_NET_NEIGHBOR_SUPPORT
                /* check is need show dialog or not  */
                i4_ret_neighbor = mmp_be_auth_touch_folder(pt_this->ui4_focus_idx);

                if(i4_ret_neighbor == MMPR_DIR_AUTH_FAIL)
                {
                }
                if(i4_ret_neighbor != MMPR_OK)
                {
                    return i4_ret_neighbor;
                }

#endif
                if(ITEM_TYPE_DIR == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,pt_this->ui4_focus_idx))
                {

                    pt_this->b_refersh_data_ready = FALSE;
                    _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect,FALSE,FALSE);

                    i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE,pt_this->ui4_focus_idx,&ui4_cnt,&t_item_info);
                    MMPR_LOG_ON_FAIL(i4_ret);
                    //c_wgl_set_focus(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS),TRUE);
                    pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;

                    if(c_strcmp(t_item_info.s_name, "..")==0 ||c_strcmp(t_item_info.s_name, "\\")==0)
                    {
                        i4_ret = mmp_be_cd_parent();
                        IS_MMPR_OK(i4_ret);
                    }

                    else
                    {
                        i4_ret = mmp_be_cd_child(pt_this->ui4_focus_idx);
                        IS_MMPR_OK(i4_ret);
                    }
                }
                else  if(ITEM_TYPE_FILE == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,pt_this->ui4_focus_idx))
                {
                    /*set focus to start slideshow btn */
                    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_STARTSLIDESHOW_BTN);
                    c_wgl_set_focus(h_view_item,WGL_SYNC_AUTO_REPAINT);
                    IS_MMPR_OK(i4_ret);

                    SET_RECT_BY_SIZE(&t_rect,
                                     MMP_TM_POP_UP_BASE_FRM_X,
                                     MMP_TM_POP_UP_BASE_FRM_Y,
                                     MMP_TM_POP_UP_BASE_FRM_W,
                                     MMP_TM_POP_UP_BASE_FRM_H);
                    c_wgl_add_transparent_list_exclusion(pt_this->h_transparent_rect, &t_rect, 1);

                    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_POP_UP_BASE_FRM);
                    IS_MMPR_OK (c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE));
                    //Fix Coverity ID : 4524266 Unchecked return value
                    i4_ret = c_wgl_insert(h_view_item, NULL_HANDLE, WGL_INSERT_TOPMOST, FALSE);
                    IS_MMPR_OK(i4_ret);
                    mmp_thumbnailmode_upd_preview_trans_list(pt_this, pt_this->ui1_hlt_idx);

                    c_wgl_repaint(h_view_item,NULL,TRUE);
                    pt_this->e_popup_status = MMP_TM_POPUP_STATUS_ON;

                    c_wgl_enable_transparent_list(pt_this->h_transparent_rect, FALSE, FALSE);

                    MMP_DBG_INFO(("[%s %d] b_loading_thumb:%d  ui1_hlt_idx:%d  ab_is_enable:%d\r\n",__FUNCTION__,__LINE__,pt_this->b_loading_thumb,pt_this->ui1_hlt_idx,pt_this->at_transp.ab_is_enable[pt_this->ui1_hlt_idx]));

                    if (FALSE == pt_this->b_loading_thumb)
                    {
                        mmp_thumbnailmode_show_img_preview(pt_this, TRUE);
                    }
                    //mmp_thumbnailmode_hide_file_info();

                    i4_ret = c_wgl_do_cmd (pt_this->h_pop_up_exculde_help_text,
                                   WGL_CMD_TEXT_SET_TEXT,
                                   WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW)),
                                   WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_EXCLU_SATSLSHOW))));

                    IS_MMPR_OK(i4_ret);
                    c_wgl_set_visibility (pt_this->h_pop_up_exculde_help_text, WGL_SW_RECURSIVE);
                    i4_ret = c_wgl_repaint(pt_this->h_pop_up_exculde_help_text,NULL,TRUE);
                    IS_MMPR_OK(i4_ret);
                }
            }
            break;

            case BTN_MENU:
            {
                MMP_BE_STATUS_T e_status;
                mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);

            }
            break;

            case BTN_INPUT_SRC:
                break;

            default:
            {
                _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);

            }
            break;
        }
    }
    else if(ui4_msg == WGL_MSG_GET_FOCUS)
        {
            MMP_TM_MEMBER_T*          pt_this = NULL;

#ifdef APP_NET_NEIGHBOR_SUPPORT
//            INT32                     i4_ret_neighbor = -1;
#endif
            c_wgl_do_cmd(h_widget,
                     WGL_CMD_GL_GET_ATTACH_DATA,
                     WGL_PACK(&pt_this),
                     NULL);
            MMP_ASSERT(pt_this != NULL);
            if((pt_this->ui4_dir_num+pt_this->ui4_file_num)==0)
            {
                h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
                c_wgl_set_focus(h_view_item ,TRUE);
                c_wgl_repaint(h_view_item,NULL,TRUE);
                return MMPR_OK;
            }
            else if(MMP_FF_SET_PATH_FLAG_EMPTY == pt_this->changed_view_mode)
            {
                if(ITEM_TYPE_DIR == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,pt_this->ui4_focus_idx))
                {
                    IS_MMPR_OK( c_wgl_set_visibility (pt_this->h_frm_htl_thumbnail_mov_frm, WGL_SW_HIDE_RECURSIVE));
                    IS_MMPR_OK( c_wgl_set_visibility (pt_this->h_frm_htl_folder_mov_frm, WGL_SW_NORMAL));
                    IS_MMPR_OK( c_wgl_repaint(pt_this->h_frm_htl_thumbnail_mov_frm , NULL,TRUE));
                    IS_MMPR_OK (c_wgl_repaint(pt_this->h_frm_htl_folder_mov_frm , NULL,TRUE));

                }

                else
                {
                    IS_MMPR_OK( c_wgl_set_visibility (pt_this->h_frm_htl_folder_mov_frm,WGL_SW_HIDE ));
                    IS_MMPR_OK( c_wgl_set_visibility (pt_this->h_frm_htl_thumbnail_mov_frm,WGL_SW_RECURSIVE));
                    IS_MMPR_OK (c_wgl_repaint(pt_this->h_frm_htl_folder_mov_frm , NULL,TRUE));
                    IS_MMPR_OK (c_wgl_repaint(pt_this->h_frm_htl_thumbnail_mov_frm , NULL,TRUE));
                }
            }
            else
            {
               pt_this->changed_view_mode = MMP_FF_SET_PATH_FLAG_EMPTY;
            }
        }
        else if(ui4_msg == WGL_MSG_LOSE_FOCUS)
        {
            MMP_TM_MEMBER_T*          pt_this = NULL;
#ifdef APP_NET_NEIGHBOR_SUPPORT
//            INT32                   i4_ret_neighbor = -1;
#endif
            c_wgl_do_cmd(h_widget,
                     WGL_CMD_GL_GET_ATTACH_DATA,
                     WGL_PACK(&pt_this),
                     NULL);
            MMP_ASSERT(pt_this != NULL);
            if(ITEM_TYPE_FILE == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,pt_this->ui4_focus_idx))
            {
                IS_MMPR_OK( c_wgl_set_visibility (pt_this->h_frm_htl_thumbnail_mov_frm, WGL_SW_HIDE));
                i4_ret = c_wgl_repaint(pt_this->h_frm_htl_thumbnail_mov_frm ,NULL,TRUE);
                IS_MMPR_OK (i4_ret);
            }
            else
            {
                IS_MMPR_OK( c_wgl_set_visibility (pt_this->h_frm_htl_folder_mov_frm, WGL_SW_HIDE_RECURSIVE));
                i4_ret = c_wgl_repaint(pt_this->h_frm_htl_folder_mov_frm , NULL,TRUE);
                IS_MMPR_OK (i4_ret);
            }
       }
       return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
 }


//
//
//
INT32 mmp_thumbnailmode_for_pe_get_hlt_idx(VOID)
{
    MMP_TM_MEMBER_T*        pt_this = &t_g_tm_member;
    return pt_this->ui1_hlt_idx;
}

//
//
//
INT32 mmp_thumbnailmode_for_pe_get_item_idx(VOID)
{
    MMP_TM_MEMBER_T*        pt_this = &t_g_tm_member;
    return pt_this->ui2_thumb_item_idx;
}



/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_device_nfy_frm
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_device_nfy_frm(HANDLE_T    h_widget,
                                               UINT32      ui4_msg,
                                               VOID*       pv_param1,
                                               VOID*       pv_param2)


{
    INT32                   i4_ret;
    HANDLE_T                h_thumb_item=NULL_HANDLE;
    MMP_TM_MEMBER_T*        pt_this = &t_g_tm_member;
    UINT32                  ui4_key_code = (UINT32) pv_param1;


    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        if(pt_this->b_refersh_data_ready == TRUE)
        {
            switch (ui4_key_code)
            {
                case MMP_TM_BTN_SELECT:
                {
                    MMP_BE_STATUS_T e_status;
                    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);

                    if (e_status == MMP_BE_STATUS_NORMAL ||e_status == MMP_BE_STATUS_CHOOSE_MNT)
                    {

                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO);
                        i4_ret = c_wgl_set_visibility(h_thumb_item, WGL_SW_HIDE_RECURSIVE);
                        IS_MMPR_OK(i4_ret);
                        c_wgl_repaint(h_thumb_item,NULL,TRUE);

                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
                        i4_ret = c_wgl_set_visibility(h_thumb_item, WGL_SW_HIDE_RECURSIVE);
                        IS_MMPR_OK(i4_ret);
                        c_wgl_repaint(h_thumb_item,NULL,TRUE);

                        i4_ret = mmp_thumbnailmode_optl_show(pt_this, (VOID*)(UINT32)MMP_THUB_OPTL_DEV_LIST);
                        IS_MMPR_OK(i4_ret);
                    }
                }
                    break;
                case MMP_TM_BTN_CURSOR_RIGHT:
                    _mmp_thumbnailmode_set_focus (pt_this, pt_this->ui4_focus_idx,pt_this->ui1_hlt_idx);
                    pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                    c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
                    break;

                case BTN_RETURN:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    break;

                case MMP_TM_BTN_CURSOR_DOWN:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    pt_this->h_last_focus_wigt = h_thumb_item;
                    pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                    break;
                case MMP_TM_BTN_CURSOR_UP:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    pt_this->h_last_focus_wigt = h_thumb_item;
                    pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                    break;

                case BTN_INPUT_SRC:
                    break;

                default:
                {
                    _mmp_thumbnailmode_view_default_key_handler(ui4_key_code, WGL_MSG_KEY_DOWN);

                }
                break;
            }
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_LB_DRIVER);
        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
    #ifdef APP_TTS_SUPPORT
        _mmp_thumbnailmode_view_btn_tts_play();
    #endif
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*---------------------------------------------------------------------------*/
/**
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_start_sldshow_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{

    INT32                   i4_ret;
    MMP_TM_MEMBER_T*        pt_this=&t_g_tm_member;
    BOOL                    b_is_allow_traverse = FALSE;
#ifdef APP_NET_NEIGHBOR_SUPPORT
    INT32                   i4_ret_neighbor = -1;
#endif
    UINT32                  ui4_key_code = (UINT32) pv_param1;
    HANDLE_T                h_view_item=NULL_HANDLE;
    MMP_PL_ATTR_T           at_attr2[3];
    UINT8                   ui1_cfg_value = 0;
    UINT32                  ui4_cfg_value = 0;
    MMP_EFFECT_T            effect_item = {0};
    UINT32                  ui4_file_idx, ui4_play_idx = MMP_NULL_FILE_IDX;
    UINT32                  ui4_play_begin_idx = 0;
    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    c_memset(&at_attr2,0,3*sizeof(MMP_PL_ATTR_T));



    b_is_allow_traverse = (FALSE == pt_this->b_is_parsing_folder) && (FALSE == pt_this->b_is_nofile_show);
    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        if(pt_this->b_refersh_data_ready == TRUE)
        {
            switch (ui4_key_code)
            {

                case MMP_TM_BTN_SELECT:
                if(pt_this->ui4_dir_num+pt_this->ui4_file_num != 0)
                  {

                         if(FALSE == b_is_allow_traverse)
                        {
                            break;
                        }

                        if(pt_this->b_load_first_page)
                        {
                            break;
                        }


#ifdef APP_NET_NEIGHBOR_SUPPORT
                        /* check is need show dialog or not  */
                        //i4_ret_neighbor = mmp_be_auth_touch_folder(pt_this->ui4_focus_idx);
                        i4_ret_neighbor = mmp_be_auth_touch_folder(0);
                        if(i4_ret_neighbor == MMPR_DIR_AUTH_FAIL)
                        {
                            mmp_thumbnailmode_is_need_show_pwd_dlg(pt_this);

                        }
                        else if(i4_ret_neighbor != MMPR_OK)
                        {
                            return i4_ret_neighbor;
                        }
#endif

                        if(pt_this->b_load_first_page || FALSE == b_is_allow_traverse)
                        {
                            break;
                        }

                        if((pt_this->ui4_focus_idx < pt_this->ui4_dir_num)&&(pt_this->b_recursive == FALSE))
                        {
                            ui4_play_begin_idx = pt_this->ui4_dir_num;
                        }

                        else if((pt_this->ui4_focus_idx >= pt_this->ui4_dir_num)&&(pt_this->b_recursive == FALSE))
                        {
                            ui4_play_begin_idx = pt_this->ui4_focus_idx;
                        }

                        else if(TRUE ==  pt_this->b_recursive)
                        {
                            ui4_play_begin_idx = pt_this->ui4_focus_idx;
                        }

                        if (mmp_be_is_item_in_list(MMP_BE_FF_IDX_CRT, ITEM_TYPE_NONE, ui4_play_begin_idx, MMP_FF_ITEM_LIST_TYPE_SKIP_LIST))
                        {
                            i4_ret = mmp_be_get_first_non_skip_file(MMP_BE_FF_IDX_CRT, MMP_NULL_FILE_IDX, &ui4_file_idx);
                            if (MMPR_OK == i4_ret)
                            {
                                ui4_play_idx = pt_this->ui4_dir_num + ui4_file_idx;
                                _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect,FALSE,FALSE);
                            }

                        }
                        else
                        {
                            ui4_play_idx = ui4_play_begin_idx;
                            _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect,FALSE,FALSE);
                        }

                        if (MMP_NULL_FILE_IDX == ui4_play_idx)
                        {
                            break;
                        }

                        //set shuffle attr
                        a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);
                        if(ui1_cfg_value == 0)
                        {
                            ui4_cfg_value = MMP_SHUFFLE_MODE_SEQUENTIAL;
                        }
                        else
                        {
                            ui4_cfg_value = MMP_SHUFFLE_MODE_SHUFFLE;
                        }
                        at_attr2[0].e_id = MMP_PL_ATTR_ID_PHOTO_SHUFFLE;
                        at_attr2[0].pv_param = (VOID*)ui4_cfg_value;


                        //set speed attr
                        a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);
                        MMP_PP_RC_DLB_GET_SPEED((UINT32)ui1_cfg_value, ui4_cfg_value);
                        at_attr2[1].e_id = MMP_PL_ATTR_ID_DURATION;
                        at_attr2[1].pv_param = (VOID*)ui4_cfg_value;

                        //set effect attr
                        a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);

                        switch(ui1_cfg_value)
                        {
                            case 0:
                                 ui4_cfg_value = mmp_tm_rand()%7+1;
                                 break;

                            case 1:
                                 ui4_cfg_value = TFX_DISSOLVE;
                                 break;

                            case 2:
                                 ui4_cfg_value = TFX_WIPE_RIGHT;
                                 break;

                            case 3:
                                 ui4_cfg_value = TFX_WIPE_LEFT;
                                 break;

                            case 4:
                                ui4_cfg_value = TFX_WIPE_UP;
                                break;

                            case 5:
                                ui4_cfg_value = TFX_WIPE_DOWN;
                                break;

                            case 6:
                                ui4_cfg_value = TFX_BOX_IN;
                                break;

                            case 7:
                                ui4_cfg_value = TFX_BOX_OUT;
                                break;

                            default:
                                ui4_cfg_value = TFX_WIPE_LEFT;
                                break;
                        }
                        effect_item.e_effect  = ui4_cfg_value;
                        effect_item.b_is_enabled =TRUE;
                        at_attr2[2].e_id = MMP_PL_ATTR_ID_EFFECT;
                        at_attr2[2].pv_param = &effect_item;
                        i4_ret = mmp_mc_list_set_attr(3, at_attr2);
                        mmp_be_cd_child(ui4_play_idx);
                }
                break;

                case MMP_TM_BTN_CURSOR_RIGHT:
                    if(pt_this->ui4_dir_num+pt_this->ui4_file_num != 0)
                    {
                        _mmp_thumbnailmode_set_focus (pt_this, pt_this->ui4_focus_idx,pt_this->ui1_hlt_idx);
                        pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                        c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
                    }
                    break;

                case BTN_RETURN:
                    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
                    c_wgl_set_focus(h_view_item,TRUE);

                    break;

                case MMP_TM_BTN_CURSOR_DOWN:
                    /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
                    }
                    else
                    {
                        h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
                        DBG_LOG_PRINT(("\n====Startslide show==============%d\n",__LINE__));
                    }

                     c_wgl_set_focus(h_view_item,TRUE);
                     pt_this->h_last_focus_wigt = h_view_item;
                     pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                    break;
                case MMP_TM_BTN_CURSOR_UP:
                     h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_LB_DRIVER);
                     c_wgl_set_focus(h_view_item,TRUE);
                     pt_this->h_last_focus_wigt = h_view_item;
                     pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                     return MMPR_OK;

                case BTN_INPUT_SRC:
                    break;

                default:
                {
                    _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);

                }
                break;
            }
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
    #ifdef APP_TTS_SUPPORT
        _mmp_thumbnailmode_view_btn_tts_play();
    #endif
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_name_a_z_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    INT32               i4_ret       = MMPR_OK;
    HANDLE_T            h_thumb_item = NULL_HANDLE;
    UINT32              ui4_key_code = (UINT32) pv_param1;
    MMP_TM_MEMBER_T*        pt_this=&t_g_tm_member;
    MMP_BE_FILE_SRC_TYPE_T  e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                    s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;


    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {

        c_wgl_do_cmd(h_widget,
                     WGL_CMD_GL_GET_ATTACH_DATA,
                     WGL_PACK(&pt_this),
                     NULL);
        MMP_ASSERT(pt_this != NULL);

        if(pt_this->b_refersh_data_ready == TRUE)
        {
            switch (ui4_key_code)
            {
                case MMP_TM_BTN_SELECT:
                {
                    MMP_BE_STATUS_T e_status;

                    /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        /*  don't show the sort type in thumbnailmode optl */
                    }

                    else
                    {
                        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);
                        if (e_status == MMP_BE_STATUS_NORMAL ||e_status == MMP_BE_STATUS_CHOOSE_MNT)
                        {
                            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO);
                            i4_ret = c_wgl_set_visibility(h_thumb_item, WGL_SW_HIDE_RECURSIVE);
                            IS_MMPR_OK(i4_ret);

                            c_wgl_repaint(h_thumb_item,NULL,TRUE);

                            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
                            c_wgl_set_visibility(h_thumb_item,WGL_SW_HIDE_RECURSIVE);
                            i4_ret = mmp_thumbnailmode_optl_show(pt_this,MMP_THUB_OPTL_SORT);
                            MMPR_LOG_ON_FAIL(i4_ret);
                        #ifdef APP_TTS_SUPPORT
                            pt_this->ui2_optl_item = MMP_TM_VIEW_OPTL_SORT;
                        #endif
                        }
                    }
                    return MMPR_OK;
                }

                case MMP_TM_BTN_CURSOR_RIGHT:
                    _mmp_thumbnailmode_set_focus (pt_this, pt_this->ui4_focus_idx,pt_this->ui1_hlt_idx);
                    pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                    c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
                    break;

                case BTN_RETURN:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    break;

                case MMP_TM_BTN_CURSOR_DOWN:
                    /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        break;
                    }
                    else
                    {
                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
                        c_wgl_set_focus(h_thumb_item,TRUE);
                        pt_this->h_last_focus_wigt = h_thumb_item;
                        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                        break;
                    }

                case MMP_TM_BTN_CURSOR_UP:
                    /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        break;
                    }
                    else
                    {
                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
                    }

                     c_wgl_set_focus(h_thumb_item,TRUE);
                     pt_this->h_last_focus_wigt = h_thumb_item;
                     pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                     break;
                case BTN_INPUT_SRC:
                    break;

                default:
                {
                    _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);

                }
                break;
            }
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
    #ifdef APP_TTS_SUPPORT
        _mmp_thumbnailmode_view_btn_tts_play();
    #endif
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_browse_music_btn_nfy
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_browse_music_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{

    UINT32               ui4_key_code = (UINT32) pv_param1;
    MMP_TM_MEMBER_T*     pt_this=&t_g_tm_member;
    HANDLE_T             h_thumb_item=NULL_HANDLE;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        if(pt_this->b_refersh_data_ready == TRUE)
        {

            switch (ui4_key_code)
            {
                case MMP_TM_BTN_SELECT:
                {
                    UINT8   ui1_req_op = ICL_RECID_MMP_REQ_OP_ENTER_AUDIO_BWR;

                    a_optl_hide(pt_this->h_option_list);
                    c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm,WGL_SW_HIDE_RECURSIVE);
                    c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,TRUE);
                    c_wgl_set_visibility(pt_this->h_info_frm,WGL_SW_HIDE_RECURSIVE);
                    c_wgl_repaint(pt_this->h_info_frm,NULL,TRUE);
                    /* set the path to root */
                    mmp_be_set_curr_path(NULL);
                    mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_FILTER_TYPE,(VOID*)MMP_MEDIA_TYPE_AUDIO);
                    mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL, MMP_MSG_ID_APP_RESUMED, (VOID*)MMP_APP_RESUME_INFO_AUDIO_BWR);
                    a_icl_set(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_REQUEST_OP),
                                          &ui1_req_op,
                                          ICL_RECID_MMP_REQUEST_OP_SIZE);
                }
                    break;
                case BTN_RETURN:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    break;

                case MMP_TM_BTN_CURSOR_RIGHT:
                    _mmp_thumbnailmode_set_focus (pt_this, pt_this->ui4_focus_idx,pt_this->ui1_hlt_idx);
                    pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                    c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);

                    break;

                case MMP_TM_BTN_CURSOR_DOWN:
                    break;
                case MMP_TM_BTN_CURSOR_UP:
                     h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
                     c_wgl_set_focus(h_thumb_item,TRUE);
                     pt_this->h_last_focus_wigt = h_thumb_item;
                     pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                    break;
                case BTN_INPUT_SRC:
                    break;

                default:
                {
                    _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);

                }
                break;
            }
        }
    }

     else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BROWSE_MUSIC);
        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
    #ifdef APP_TTS_SUPPORT
        _mmp_thumbnailmode_view_btn_tts_play();
    #endif
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_thumbnails_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    HANDLE_T                        h_thumb_item=NULL_HANDLE;
    INT32                           i4_ret=MMPR_OK;
    UINT32                          ui4_key_code = (UINT32) pv_param1;
    MMP_TM_MEMBER_T*                pt_this = &t_g_tm_member;
    MMP_BE_FILE_SRC_TYPE_T          e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                            s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                          z_size = MMP_BE_MAX_PATH_LEN;


    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        if(pt_this->b_refersh_data_ready == TRUE)
        {
            switch (ui4_key_code)
            {
                case MMP_TM_BTN_SELECT:
                {
                    /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        /*  don't show the sort type in thumbnailmode optl */
                    }

                    else
                    {
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO);
                    i4_ret = c_wgl_set_visibility(h_thumb_item, WGL_SW_HIDE_RECURSIVE);
                    IS_MMPR_OK(i4_ret);
                    c_wgl_repaint(h_thumb_item,NULL,TRUE);

                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
                    c_wgl_set_visibility(h_thumb_item,WGL_SW_HIDE_RECURSIVE);
                    i4_ret = mmp_thumbnailmode_optl_show(pt_this,(VOID*)(UINT32)MMP_THUB_OPTL_VIEW);
                        MMPR_LOG_ON_FAIL(i4_ret);

                    #ifdef APP_TTS_SUPPORT
                        pt_this->ui2_optl_item = MMP_TM_VIEW_OPTL_VIEW;
                    #endif
                    }
                    return MMPR_OK;

                }
                    break;

                case MMP_TM_BTN_CURSOR_RIGHT:
                    _mmp_thumbnailmode_set_focus (pt_this, pt_this->ui4_focus_idx,pt_this->ui1_hlt_idx);
                    pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                    c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);

                    break;

                case BTN_RETURN:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    break;

                case MMP_TM_BTN_CURSOR_DOWN:
                     /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);
                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        break;
                    }
                    else
                    {
                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
                        c_wgl_set_focus(h_thumb_item,TRUE);
                        pt_this->h_last_focus_wigt = h_thumb_item;
                        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                        break;
                    }

                case MMP_TM_BTN_CURSOR_UP:
                     /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);
                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        break;
                    }
                    else
                    {
                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
                        c_wgl_set_focus(h_thumb_item,TRUE);
                        pt_this->h_last_focus_wigt = h_thumb_item;
                        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                        break;
                    }

                case BTN_INPUT_SRC:
                   break;

                default:
                {
                   _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);

                }
                break;
            }
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
    #ifdef APP_TTS_SUPPORT
        _mmp_thumbnailmode_view_btn_tts_play();
    #endif
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_settings_btn_nfy
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_settings_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    HANDLE_T                h_thumb_item=NULL_HANDLE;
    INT32                   i4_ret=MMPR_OK;
    UINT32                  ui4_key_code = (UINT32) pv_param1;
    MMP_TM_MEMBER_T*        pt_this = &t_g_tm_member;
    MMP_BE_FILE_SRC_TYPE_T          e_src_type = MMP_BE_FILE_SRC_UNKNOWN;
    CHAR                            s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                          z_size = MMP_BE_MAX_PATH_LEN;


    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        c_wgl_do_cmd(h_widget,
                     WGL_CMD_GL_GET_ATTACH_DATA,
                     WGL_PACK(&pt_this),
                     NULL);
        MMP_ASSERT(pt_this != NULL);

        if(pt_this->b_refersh_data_ready == TRUE)
        {
            switch (ui4_key_code)
            {
                case MMP_TM_BTN_SELECT:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO);
                    i4_ret = c_wgl_set_visibility(h_thumb_item, WGL_SW_HIDE_RECURSIVE);
                    IS_MMPR_OK(i4_ret);

                    c_wgl_repaint(h_thumb_item,NULL,TRUE);
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
                    c_wgl_set_visibility(h_thumb_item,WGL_SW_HIDE_RECURSIVE);
                    mmp_thumbnailmode_optl_show(pt_this,(VOID*)(UINT32)MMP_THUB_OPTL_SETTINGS);
                #ifdef APP_TTS_SUPPORT
                    pt_this->ui2_optl_item = MMP_TM_VIEW_OPTL_SETTINGS;
                #endif
                    break;

                case MMP_TM_BTN_CURSOR_RIGHT:
                    _mmp_thumbnailmode_set_focus (pt_this, pt_this->ui4_focus_idx,pt_this->ui1_hlt_idx);
                    pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                    c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
                    break;

                case BTN_RETURN:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    break;
                case MMP_TM_BTN_CURSOR_DOWN:
                    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BROWSE_MUSIC);
                    c_wgl_set_focus(h_thumb_item,TRUE);
                    pt_this->h_last_focus_wigt = h_thumb_item;
                    pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;

                    break;
                case MMP_TM_BTN_CURSOR_UP:
                    /* get current path */
                    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
                    MMPR_LOG_ON_FAIL(i4_ret);
                    /* if source is Net, we did not support more feature */
                    if((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||
                       (MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
                    {
                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
                        c_wgl_set_focus(h_thumb_item,TRUE);
                        pt_this->h_last_focus_wigt = h_thumb_item;
                        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                        break;
                    }
                    else
                    {
                        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
                        c_wgl_set_focus(h_thumb_item,TRUE);
                        pt_this->h_last_focus_wigt = h_thumb_item;
                        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                        break;
                    }

                case BTN_INPUT_SRC:
                    break;

                default:
                {
                    _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);

                }
                break;
            }
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
    #ifdef APP_TTS_SUPPORT
        _mmp_thumbnailmode_view_btn_tts_play();
    #endif
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_back_to_up_level_btn_nfy
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_back_to_up_level_btn_nfy (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    INT32               i4_ret=MMPR_OK;
    UINT32              ui4_key_code = (UINT32) pv_param1;
    MMP_TM_MEMBER_T*    pt_this=&t_g_tm_member;
#ifndef APP_CAST_TV_MMP_FG
    UINT32  ui4_dir_num = 0;
#endif
    HANDLE_T            h_thumb_item = NULL_HANDLE;

#ifdef APP_C4TV_SUPPORT
    ISL_REC_T                   t_isl_rec;

    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    MMPR_LOG_ON_FAIL(i4_ret);
#endif

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_SELECT:
            case BTN_RETURN:
            {
            #ifndef APP_CAST_TV_MMP_FG
             #ifdef APP_TTS_SUPPORT
                /* exit mmp not to read banner tts */
                MMP_DBG_INFO(("mmp set banner tts disable %s,%d\n\r",__FILE__,__LINE__));
                set_banner_tts_enable(FALSE);
            #endif

                /*Get mount point count*/
                i4_ret = mmp_mc_device_get_mnt_count(&ui4_dir_num);
                if (MMPR_OK != i4_ret)
                {
                    return i4_ret;
                }

                if (0 == ui4_dir_num)
                {
                #ifdef APP_C4TV_SUPPORT
                    /* cast source ,select source before link to menu page fix DTV00845309 */
                    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
                    {
                        MMP_DBG_INFO(("exit mmp to cast inp %s,%d\n\r",__FILE__,__LINE__));
                        mmp_main_set_back_to_menu_page(MENU_SHORT_CUT_MMP_DEV_LIST);

                        i4_ret = mmp_be_pause_mmp();
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                    else
                    {
                        i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_DEV_LIST);
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                #else
                    i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_DEV_LIST);
                    MMPR_LOG_ON_FAIL(i4_ret);
                #endif
                }
                else
                {
                    UINT32      ui4_idx = 0;
                    CHAR        ac_path[MMP_THUMBNAIL_MAX_NAME_LEN] = {0};
                    SIZE_T      z_size = MMP_THUMBNAIL_MAX_NAME_LEN;
                    RMV_DEV_DEVICE_STATUS_T  e_dev_status;
                    UINT32     ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;
                    SIZE_T z_exit_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;

                    MMPR_LOG_ON_FAIL(a_rmv_dev_get_active_mnt_pnt(&ui4_idx, &z_size, ac_path));

                    /*query mount point status*/
                    i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                                ui4_idx,
                                                &e_dev_status);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
                        (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
                        (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
                    {
                    #ifdef APP_C4TV_SUPPORT
                        if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
                        {
                            MMP_DBG_INFO(("exit mmp to cast inp %s,%d\n\r",__FILE__,__LINE__));
                            mmp_main_set_back_to_menu_page(MENU_SHORT_CUT_MMP_DEV_LIST);

                            i4_ret = mmp_be_pause_mmp();
                            MMPR_LOG_ON_FAIL(i4_ret);
                        }
                        else
                        {
                            i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_DEV_LIST);
                            MMPR_LOG_ON_FAIL(i4_ret);
                        }
                    #else
                        i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_DEV_LIST);
                        MMPR_LOG_ON_FAIL(i4_ret);
                    #endif
                    }
                    else
                    {
                    #ifdef APP_C4TV_SUPPORT
                        if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
                        {
                            MMP_DBG_INFO(("exit mmp to cast inp %s,%d\n\r",__FILE__,__LINE__));
                            mmp_main_set_back_to_menu_page(MENU_SHORT_CUT_MMP_MEDIA_TYPE);

                            i4_ret = mmp_be_pause_mmp();
                            MMPR_LOG_ON_FAIL(i4_ret);
                        }
                        else
                        {
                            i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);
                            MMPR_LOG_ON_FAIL(i4_ret);
                        }
                    #else
                        i4_ret = a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);
                        IS_MMPR_OK(i4_ret);
                    #endif

                        ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_SHORTCUT_TO_MEDIATYPE;
                        i4_ret = a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON),
                                           (VOID*) &ui4_exit_reason, z_exit_size);
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                }
                #else
                MMP_DBG_INFO(("<mmp> back to fg %s,%d\n\r",__FILE__,__LINE__));
                pt_this->h_last_left_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
                pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);

                i4_ret = mmp_mc_list_close(MMP_GROUND_MODE_ALL);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_reset();
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = mmp_be_switch_browser(MMP_RC_BROWSER_ID_FOREGROUND,
                                               TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
                #endif
            }
                break;

            case MMP_TM_BTN_CURSOR_DOWN:
                h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_LB_DRIVER);
                c_wgl_set_focus(h_thumb_item,TRUE);
                pt_this->h_last_focus_wigt = h_thumb_item;
                pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
                return MMPR_OK;
            case BTN_INPUT_SRC:
                break;

            default:
            {
                _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);

            }
            break;
        }
    }

    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
    #ifdef APP_TTS_SUPPORT
        UTF16_T         w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    #endif
        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BACK);
        pt_this->h_last_left_focus_wigt = pt_this->h_last_focus_wigt;
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}


/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_right_to_left_btn_nfy_frm
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_right_to_left_btn_nfy_frm (HANDLE_T    h_widget,
                                              UINT32      ui4_msg,
                                              VOID*       pv_param1,
                                              VOID*       pv_param2)
{
    MMP_TM_MEMBER_T*        pt_this       = &t_g_tm_member;
    UINT32                  ui4_key_code  = (UINT32) pv_param1;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {

        pt_this->h_last_focus_wigt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_RIGHT_TO_LEFT_BTN);
        switch (ui4_key_code)
        {
            case MMP_TM_BTN_CURSOR_DOWN:
               if((pt_this->ui4_file_num+ pt_this->ui4_dir_num) == 0)
               {
                   break;
               }
                pt_this->h_last_focus_wigt = pt_this->h_frm_right_base_frm;
                _mmp_thumbnailmode_set_focus (pt_this, pt_this->ui4_focus_idx,pt_this->ui1_hlt_idx);
                IS_MMPR_OK (c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_SYNC_AUTO_REPAINT));
                break;

            case MMP_TM_BTN_SELECT:
            case MMP_TM_BTN_CURSOR_LEFT:
            case BTN_RETURN:
                 IS_MMPR_OK (c_wgl_set_focus(pt_this->h_last_left_focus_wigt,TRUE));
                break;

            case BTN_INPUT_SRC:
                break;
            default:
            {
                _mmp_thumbnailmode_view_default_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);//mmp_be_default_key_handle(ui4_key_code,WGL_MSG_KEY_DOWN);

            }
            break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if(ui4_msg == WGL_MSG_GET_FOCUS)
    {
        UTF16_T         w2s_str[128] = {0};
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
    }
#endif
    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}




/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_show_thumbnails
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_show_thumbnails(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx, UINT8 ui1_hlt_idx,UINT32 ui4_file_remain_item )
{
    UINT32                      ui4_show_file_idx_start,ui4_show_file_cnt,ui4_file_total_item,ui4_folder_total_item;
    MMP_PLAY_STATE_T            e_music_state;
    UINT32                      ui4_start_idx,ui4_i,i4_ret=MMPR_OK,ui4_cnt=1,ui4_start_position,ui4_end_position;
    HANDLE_T                    h_thumb_item=NULL_HANDLE,h_thumb_text=NULL_HANDLE;
    MMP_ITEM_INFO_T             t_item_info[MMP_THMBNAILMODE_MAX_THUMBS];
    CHAR*                       s_new_name;
    UTF16_T                     w2s_text[MMP_TM_VIEW_INFO_STR_MAX_LEN +1];
    UINT32                      ui4_total_file_and_folder,ui4_j;


    c_memset(t_item_info,0,sizeof(t_item_info));
    c_memset(w2s_text,0,sizeof(w2s_text));
    /* Get first item and number of items in this page */
    ui4_file_total_item=pt_this->ui4_file_num;
    ui4_folder_total_item=pt_this->ui4_dir_num;
    ui4_total_file_and_folder =ui4_file_total_item + ui4_folder_total_item;
    //_mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect, FALSE, TRUE);

    if((pt_this->ui4_file_num!=0)&&(ui4_file_remain_item != 0))
    {
        _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect, FALSE, TRUE);
        if(FALSE==pt_this->b_recursive)
        {
            ui4_start_position =MMP_THMBNAILMODE_MAX_THUMBS - ui4_file_remain_item;
            ui4_show_file_idx_start =  ui4_focus_idx - ui1_hlt_idx + MMP_THMBNAILMODE_MAX_THUMBS - ui4_file_remain_item;

        }
        else
        {
            ui4_show_file_idx_start =  ui4_focus_idx - ui1_hlt_idx;
            ui4_start_position =0;
        }
        ui4_show_file_cnt = MIN (ui4_total_file_and_folder - ui4_show_file_idx_start,ui4_file_remain_item);
        ui4_end_position = ui4_start_position + ui4_show_file_cnt;

        /*check music status*/
        i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_BACK, &e_music_state);
        if (e_music_state == MMP_PLAY_STATE_CLOSED ||e_music_state == MMP_PLAY_STATE_CLOSING ||
            e_music_state == MMP_PLAY_STATE_STOPPING ||
            e_music_state == MMP_PLAY_STATE_STOPPED)
        {
            mmp_mc_browse_show_info_handler(FALSE,FALSE, FALSE);
        }


        ui4_i = ui4_start_position;
        if(ui4_i<ui4_end_position) /*current page is not all of folders  but still has thumbnails*/
        {
            for (ui4_j=0;ui4_i< ui4_end_position;ui4_i++,ui4_j++)
            {
                // Fix Coverity CID-4491461: Out-of-bounds read
                if( ui4_i >= MMP_THMBNAILMODE_MAX_THUMBS )
                {
                    break;
                }

                ui4_start_idx = ui4_show_file_idx_start + ui4_j;
                h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui4_i * 2);
                c_wgl_set_visibility (h_thumb_item,WGL_SW_RECURSIVE);
                h_thumb_text = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEXT0 + ui4_i * 2);
                c_wgl_set_visibility (h_thumb_text,WGL_SW_RECURSIVE);

                i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE,ui4_start_idx,&ui4_cnt,&t_item_info[ui4_i]);
                //IS_MMPR_OK(i4_ret);
                s_new_name = mmp_be_get_filtered_item_name(t_item_info[ui4_i].s_name);
                i4_ret = c_uc_ps_to_w2s(s_new_name,w2s_text,MMP_TM_VIEW_INFO_STR_MAX_LEN);
                if (i4_ret != UCR_OK && i4_ret != UCR_NO_ENOUGH_BUFFER)
                {
                    MMP_DBG_ERROR(("c_uc_ps_to_w2s retrun error! i4_ret=%d \n",i4_ret));
                    w2s_text[0] = 0;
                }
                else
                {
                    w2s_text[MMP_TM_VIEW_INFO_STR_MAX_LEN] = 0;
                }
                i4_ret = c_wgl_do_cmd (h_thumb_text,
                                      WGL_CMD_TEXT_SET_TEXT,
                                      WGL_PACK(w2s_text),
                                      WGL_PACK(c_uc_w2s_strlen(w2s_text)));
                IS_MMPR_OK(i4_ret);

                /*Update skip attribute*/
                if (ui4_i < MMP_THMBNAILMODE_MAX_THUMBS)
                {
                    pt_this->b_skip_flag[ui4_i] = mmp_be_is_item_in_list(MMP_BE_FF_IDX_CRT,
                                                                       ITEM_TYPE_NONE,
                                                                       ui4_start_idx,
                                                                       MMP_FF_ITEM_LIST_TYPE_SKIP_LIST);
                }

            }
        }

        _mmp_thumbnailmode_refresh_skip_flag(pt_this);

        c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm,WGL_SW_NORMAL);
        c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,WGL_SYNC_AUTO_REPAINT);
        /* clean old thumbnail */
        //mmp_mc_browse_stop_file_thumbnail();
        mmp_mc_browse_reset_info_resoruce();//add
        pt_this->ui4_thumb_idx_curr = MMP_NULL_FILE_IDX;
        pt_this->ui4_thumb_idx_start =ui4_show_file_idx_start;
        pt_this->ui4_thumb_idx_end = ui4_show_file_idx_start + ui4_show_file_cnt;
        pt_this->ui2_thumb_item_idx = (UINT16)(ui4_start_position);
        pt_this->ui4_thumb_idx_next = pt_this->ui4_thumb_idx_start;
        pt_this->b_loading_thumb = TRUE;
        _mmp_thumbnailmode_load_thumbnail(pt_this, pt_this->ui4_thumb_idx_next);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm,WGL_SW_NORMAL);
        c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,WGL_SYNC_AUTO_REPAINT);
    }
     return MMPR_OK;
}


/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_show_folders
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_show_folders(MMP_TM_MEMBER_T* pt_this,UINT32 ui4_focus_idx,UINT8 ui1_hlt_idx,UINT32 *pui4_focus_idx)
{
    UINT32               ui4_folder_total_item,ui4_show_folder_idx_start,ui4_show_folder_cnt,ui4_folder_start_idx;
    UINT32               ui4_i,i4_ret=MMPR_OK;
    MMP_ITEM_INFO_T      t_item_info[MMP_THMBNAILMODE_MAX_THUMBS];
    UINT32               ui4_cnt = 1;
    CHAR*                s_new_name=NULL;
    CHAR                 s_buf[MMP_BE_MAX_PATH_LEN + 1] = {0};
    UTF16_T              w2s_text[MMP_BE_MAX_PATH_LEN + 1];
    HANDLE_T             h_folder_text=NULL_HANDLE,h_folder_item=NULL_HANDLE;
    WGL_IMG_INFO_T       t_img_info ;
    WGL_HIMG_TPL_T       h_img_tpl;

    c_memset(t_item_info,0,sizeof(t_item_info));
    c_memset(w2s_text,0,sizeof(w2s_text));
    /* Get first item and number of items in this page */
    ui4_folder_total_item=pt_this->ui4_dir_num;
    ui4_show_folder_idx_start = ui4_focus_idx - ui1_hlt_idx;

    if(ui4_show_folder_idx_start<pt_this->ui4_dir_num)/*current page have folders*/
    {
        ui4_show_folder_cnt = MIN (ui4_folder_total_item - ui4_show_folder_idx_start,MMP_THMBNAILMODE_MAX_THUMBS);

        for(ui4_i=0;ui4_i<ui4_show_folder_cnt;ui4_i++)
        {

            ui4_folder_start_idx = ui4_show_folder_idx_start + ui4_i;
            h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_PRE_FOLDER + ui4_i * 2);
            c_wgl_set_visibility (h_folder_item,  WGL_SW_RECURSIVE);
            h_folder_text = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEX0 + ui4_i * 2);
            c_wgl_set_visibility (h_folder_text, WGL_SW_RECURSIVE);

            i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE, ui4_folder_start_idx,&ui4_cnt,&t_item_info[ui4_i]);
            //MMPR_LOG_ON_FAIL(i4_ret);
            if(NULL == t_item_info[ui4_i].s_name )
            {
                s_new_name = "";
            }
            else
            {
                c_sprintf (s_buf, "%s", t_item_info[ui4_i].s_name);
                s_new_name = mmp_be_get_filtered_item_name(s_buf);
            }

            if(ui4_i == 0)
            {

                if(c_strcmp(t_item_info[ui4_i].s_name, "..")==0 ||c_strcmp(t_item_info[ui4_i].s_name, "\\")==0)
                {
                    s_new_name = "";
                    h_img_tpl = h_g_mmp_previous_folder_icon;
                    t_img_info.e_type = WGL_IMG_SET_BASIC;
                    t_img_info.u_img_data.t_basic.t_enable =  h_img_tpl;
                    t_img_info.u_img_data.t_basic.t_disable = h_img_tpl;

                    IS_MMPR_OK (c_wgl_do_cmd (h_folder_item,
                                      WGL_CMD_GL_SET_IMAGE,
                                      WGL_PACK (WGL_IMG_BK),
                                      WGL_PACK (&t_img_info)));
                }

                else
                {
                    h_img_tpl = h_g_mmp_lg_folder_icon;
                    t_img_info.e_type = WGL_IMG_SET_BASIC;
                    t_img_info.u_img_data.t_basic.t_enable =  h_img_tpl;
                    t_img_info.u_img_data.t_basic.t_disable = h_img_tpl;
                    IS_MMPR_OK (c_wgl_do_cmd (h_folder_item,
                                      WGL_CMD_GL_SET_IMAGE,
                                      WGL_PACK (WGL_IMG_BK),
                                      WGL_PACK (&t_img_info)));
                }
            }

            c_uc_ps_to_w2s (s_new_name, w2s_text, MMP_BE_MAX_PATH_LEN);
            w2s_text[MMP_BE_MAX_PATH_LEN - 1] = 0;
            i4_ret = c_wgl_do_cmd (h_folder_text,
                   WGL_CMD_TEXT_SET_TEXT,
                   WGL_PACK(w2s_text),
                   WGL_PACK(c_uc_w2s_strlen(w2s_text)));
            IS_MMPR_OK(i4_ret);
        }

    }
    else
    {
        ui4_show_folder_cnt = 0;
    }
    c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm ,WGL_SW_NORMAL);
    c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,TRUE);
    *pui4_focus_idx = MMP_THMBNAILMODE_MAX_THUMBS - ui4_show_folder_cnt;
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_change_page
 * @brief   Widget notify function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_change_page(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx, UINT8 ui1_hlt_idx)
{
    UINT32                      ui4_file_total_item,ui4_file_remain_item;
    UINT32                      ui4_dir_num,ui4_file_num;
    GL_RECT_T                   at_rect={0};
    INT32                       i4_ret = -1;
    HANDLE_T                    h_thumb_item=NULL_HANDLE;


    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE ,(VOID*)&pt_this->b_recursive);
    i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT,&ui4_dir_num,&ui4_file_num);

    pt_this->ui4_file_num             = ui4_file_num;
    pt_this->ui4_dir_num              = ui4_dir_num;
    pt_this->ui4_focus_idx            = ui4_focus_idx;
    pt_this->ui1_hlt_idx              = ui1_hlt_idx;
    ui4_file_total_item               = pt_this->ui4_file_num;
    pt_this->ui1_hlt_idx              = ui1_hlt_idx;

    DBG_INFO_DIRECT("[mmp tn] %s %d ui4_file_total_item:%d\r\n",__FUNCTION__,__LINE__,ui4_file_total_item);

    /* Validate ui4_focus_idx and ui1_hlt_idx*/
    if ((ui1_hlt_idx >= MMP_THMBNAILMODE_MAX_THUMBS) ||((INT32)(ui4_focus_idx - ui1_hlt_idx) < 0) ||(ui4_focus_idx >= ui4_file_num+ui4_dir_num))
    {
    #ifdef APP_NET_DLNA_SUPPORT
        /* there are some error happen, such as the folder is removed in DLNA server.*/
        ui4_focus_idx = 0;
        ui1_hlt_idx = 0;

    #else
        return MMPR_INV_ARG;
    #endif
    }

    mmp_thumbnailmode_set_page_num(pt_this, ui4_focus_idx);
    i4_ret = _mmp_thumbnailmode_disable_transparent_list(pt_this->h_transparent_rect, FALSE, TRUE);
    c_wgl_set_transparent_list(pt_this->h_transparent_rect,&at_rect,1);
    i4_ret = mmp_thumbnailmode_empty_folders_and_files(pt_this,TRUE);
    /* clean old thumbnail */
    i4_ret = mmp_mc_browse_stop_file_thumbnail();
    i4_ret = mmp_mc_browse_reset_info_resoruce();
    i4_ret = _mmp_thumbnailmode_reset_skip_flag(pt_this);

    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_RIGHT_BASE_FRM);
    c_wgl_repaint(h_thumb_item,NULL,TRUE);

    /*VIEW MODE = CURRENT FOLDERS AND THUMBNAILS*/
    if(FALSE == pt_this->b_recursive)
    {
        if((ui4_file_num+ui4_dir_num)!=0)
        {
            /*FIRST SHOW FOLDERS */
            i4_ret = _mmp_thumbnailmode_show_folders(pt_this,ui4_focus_idx,ui1_hlt_idx,&ui4_file_remain_item);
            IS_MMPR_OK(i4_ret);


            /*THEN LOAD THUMBNAILS*/
            pt_this->ui4_thumb_idx_curr = MMP_NULL_FILE_IDX;
            i4_ret =_mmp_thumbnailmode_show_thumbnails( pt_this,ui4_focus_idx, ui1_hlt_idx,ui4_file_remain_item);
            IS_MMPR_OK(i4_ret);
        }
    }

    /*VIEW MODE = ALL THUMBNAILS OF USB*/
    else if(TRUE == pt_this->b_recursive)
    {
        if(ui4_file_num!=0)
        {
            /*ONLY LOAD THUMBNAILS*/
            ui4_file_remain_item = 9;
            i4_ret =_mmp_thumbnailmode_show_thumbnails( pt_this,ui4_focus_idx, ui1_hlt_idx,ui4_file_remain_item);
            IS_MMPR_OK(i4_ret);
        }
    }
    if((pt_this->ui4_dir_num+pt_this->ui4_file_num)!=0)
    {
        if(pt_this->h_last_focus_wigt == pt_this->h_frm_right_base_frm)
        {
            i4_ret = _mmp_thumbnailmode_set_focus (pt_this, ui4_focus_idx,ui1_hlt_idx);
            c_wgl_set_focus(pt_this->h_frm_right_base_frm,TRUE);
        }
        else
        {
            c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
        }
    }
    else
    {
        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
        pt_this->h_last_focus_wigt = h_thumb_item;
        c_wgl_set_focus(h_thumb_item,TRUE);
    }
    mmp_be_set_focus_item(ui4_focus_idx);

    //IS_MMPR_OK (mmp_be_set_focus_item(ui4_focus_idx));
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Set focus item index and its highlight index in UI
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] item index in current folder
 * @param   ui1_hlt_idx [in] highlight index in page, 0 <= ui1_hlt_idx < H_NUM * V_NUM
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_set_focus (MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx, UINT8 ui1_hlt_idx)
{
    GL_RECT_T            t_rect;
    HANDLE_T             h_thumb_item=NULL_HANDLE,h_folder_item=NULL_HANDLE;
    HANDLE_T             h_focus_item=NULL_HANDLE;
    MMP_ITEM_INFO_T      t_item_info={0};
    UINT32               ui4_cnt = 1;
    WGL_IMG_INFO_T       t_img_info ;
    WGL_HIMG_TPL_T       h_img_tpl;

    pt_this->ui4_focus_idx = ui4_focus_idx;
    pt_this->ui1_hlt_idx = ui1_hlt_idx;

#ifdef APP_TTS_SUPPORT
    UTF16_T         w2s_str[128] = {0};
    mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE,ui4_focus_idx,&ui4_cnt,&t_item_info);
    c_uc_ps_to_w2s(t_item_info.s_name,w2s_str,127);
    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

    if(ITEM_TYPE_FILE == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,ui4_focus_idx))
    {
        /* get rectangle , move hlt thumb frame*/
        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui1_hlt_idx * 2);
        c_wgl_get_coords(h_thumb_item,WGL_COORDS_PARENT,&t_rect);
        t_rect.i4_left     -= TM_THUMB_NAIL_HL_INSET1;
        t_rect.i4_top      -= TM_THUMB_NAIL_HL_INSET1;
        t_rect.i4_right    += TM_THUMB_NAIL_HL_INSET1;
        t_rect.i4_bottom   += TM_THUMB_NAIL_HL_INSET1;
        c_wgl_set_visibility(pt_this->h_frm_htl_folder_mov_frm,WGL_SW_HIDE_RECURSIVE);
        c_wgl_repaint(pt_this->h_frm_htl_folder_mov_frm,NULL,TRUE);
        c_wgl_set_visibility(pt_this->h_frm_htl_thumbnail_mov_frm,WGL_SW_NORMAL);
        c_wgl_move(pt_this->h_frm_htl_thumbnail_mov_frm,&t_rect,TRUE);
        h_focus_item = pt_this->h_frm_htl_thumbnail_mov_frm;
    }
    else
    {
        h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_PRE_FOLDER + ui1_hlt_idx * 2);

        c_wgl_get_coords(h_folder_item,WGL_COORDS_PARENT,&t_rect);
        c_wgl_set_visibility(pt_this->h_frm_htl_thumbnail_mov_frm,WGL_SW_HIDE_RECURSIVE);
        c_wgl_repaint(pt_this->h_frm_htl_thumbnail_mov_frm,NULL,TRUE);
        //c_wgl_set_visibility(h_folder_text,WGL_SW_NORMAL);
        //c_wgl_set_visibility(pt_this->h_frm_htl_folder_mov_frm,WGL_SW_RECURSIVE);
        mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE,ui4_focus_idx,&ui4_cnt,&t_item_info);

        if((ui1_hlt_idx == 0) &&
            (c_strcmp(t_item_info.s_name, "..")==0 ||c_strcmp(t_item_info.s_name, "\\")==0))
        {
             h_img_tpl = h_g_mmp_prev_focus_hlt;
             t_img_info.e_type = WGL_IMG_SET_BASIC;
             t_img_info.u_img_data.t_basic.t_enable =  h_img_tpl;
             t_img_info.u_img_data.t_basic.t_disable = h_img_tpl;

             IS_MMPR_OK (c_wgl_do_cmd (pt_this->h_frm_htl_folder_mov_frm,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK),
                                  WGL_PACK (&t_img_info)));
        }
        else
        {
             h_img_tpl = h_g_mmp_floder_focus_hlt;
             t_img_info.e_type = WGL_IMG_SET_BASIC;
             t_img_info.u_img_data.t_basic.t_enable =  h_img_tpl;
             t_img_info.u_img_data.t_basic.t_disable = h_img_tpl;

             IS_MMPR_OK (c_wgl_do_cmd (pt_this->h_frm_htl_folder_mov_frm,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK),
                                  WGL_PACK (&t_img_info)));
        }
        c_wgl_set_visibility(pt_this->h_frm_htl_folder_mov_frm,WGL_SW_NORMAL);
        c_wgl_move(pt_this->h_frm_htl_folder_mov_frm,&t_rect,TRUE);
        h_focus_item = pt_this->h_frm_htl_folder_mov_frm;
    }

    c_wgl_repaint(h_focus_item,NULL,TRUE);
    IS_MMPR_OK (mmp_be_set_focus_item(ui4_focus_idx));
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Handling routine when user press cursor left/right
 * @param   pt_this [in] View instance
 * @param   b_left [in] Indicate pressing left or right
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_cursor_left_right(MMP_TM_MEMBER_T* pt_this, BOOL b_left)
{
    //HANDLE_T                    h_folder_text=NULL;
    HANDLE_T                     h_view_item=NULL_HANDLE;
    UINT32                      ui4_focus_idx = pt_this->ui4_focus_idx;
    UINT32                      ui4_hlt_idx     = (UINT32)pt_this->ui1_hlt_idx;
    UINT8                       ui1_hlt_idx,ui1_max_h_num = pt_this->ui1_max_h_num;
    UINT8                       ui1_max_v_num = pt_this->ui1_max_v_num;
    UINT32                      ui4_total_item_num;
    //MMP_ITEM_TYPE_T            e_item_type;

    ui4_total_item_num= (pt_this->b_recursive== TRUE)? pt_this->ui4_file_num : (pt_this->ui4_dir_num+pt_this->ui4_file_num);

/*
    if(pt_this->b_recursive == FALSE)
    {
        e_item_type = mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,ui4_focus_idx);
        if(ITEM_TYPE_DIR == e_item_type)
        {
            h_folder_text = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEX0 + ui4_hlt_idx* 2);
            c_wgl_set_visibility(h_folder_text,WGL_SW_NORMAL);
        }

   }
   */

    if (b_left)
    {
        if ((ui4_focus_idx == 0)||(ui4_focus_idx == 3)||(ui4_focus_idx == 6))
        {
         /*Fist colum item in this dir, do nothing*/
        }

        else if ((ui4_hlt_idx%3) == 0)

        {  /* if it  is the first colum  when put left arrow  it will jump  to the previous page   */

            ui4_focus_idx -=ui1_max_h_num*ui1_max_v_num;
            /* whether set the skip icon or not */
            IS_MMPR_OK(_mmp_thumbnailmode_change_page(pt_this,ui4_focus_idx,(UINT8)ui4_hlt_idx));
            c_wgl_repaint(h_view_item,NULL,TRUE);
        }

        else
        {
            ui4_focus_idx --;
            ui4_hlt_idx --;
            _mmp_thumbnailmode_set_focus(pt_this, ui4_focus_idx, ui4_hlt_idx);
            //IS_MMPR_OK(c_wgl_repaint(pt_this->h_folder_text,NULL,TRUE));
        }
    }


    else
    {
        if ((ui4_focus_idx >= ui4_total_item_num -1))
        {

            if(ui4_total_item_num>MMP_THMBNAILMODE_MAX_THUMBS)
            {
                 /*  if it is focusing on the  last item in this file when push the right btn it will foucus on the first item in current file   like a circle mode  */
                ui4_focus_idx = 0;
                ui4_hlt_idx   = 0;
                ui1_hlt_idx  = 0;
                _mmp_thumbnailmode_change_page(pt_this,ui4_focus_idx,ui1_hlt_idx);
            }
            return MMPR_OK; /* Last item */
        }
        else if ((ui4_hlt_idx%3) == 2)
        {
            if((ui4_focus_idx-ui4_focus_idx%MMP_THMBNAILMODE_MAX_THUMBS+MMP_THMBNAILMODE_MAX_THUMBS) <= (ui4_total_item_num-1))//still have the next page
            {
                if((ui4_focus_idx+MMP_THMBNAILMODE_MAX_THUMBS) <=(ui4_total_item_num-1))
                {
                    ui4_focus_idx =ui4_focus_idx +MMP_THMBNAILMODE_MAX_THUMBS;

                }
                else
                {
                    ui4_focus_idx = ui4_focus_idx-ui4_focus_idx%MMP_THMBNAILMODE_MAX_THUMBS+MMP_THMBNAILMODE_MAX_THUMBS;
                    ui4_hlt_idx = 0;
                }
            }
            else //last page
            {
                if(ui4_total_item_num<=9)
                {
                    return MMPR_OK;
                }
                else
                {
                    ui4_focus_idx = 0;
                    ui4_hlt_idx =0;
                }
            }
            //c_thread_delay(50);
            IS_MMPR_OK (_mmp_thumbnailmode_change_page(pt_this, ui4_focus_idx, (UINT8)ui4_hlt_idx));

        }
        else
        {
            ui4_focus_idx ++;
            ui4_hlt_idx ++;
            _mmp_thumbnailmode_set_focus(pt_this, ui4_focus_idx,(UINT8)ui4_hlt_idx);
            /*
            if(pt_this->b_recursive == TRUE)
            {
                IS_MMPR_OK(c_wgl_repaint(pt_this->h_frm_htl_folder_mov_frm,NULL,TRUE));
            }
            else
            {
                //IS_MMPR_OK(c_wgl_repaint(pt_this->h_frm_htl_thumbnail_mov_frm,NULL,TRUE));
            }
            */
        }
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Handling routine when user press cursor up/down
 * @param   pt_this [in] View instance
 * @param   b_up [in] Indicate pressing up or down
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_cursor_up_down(MMP_TM_MEMBER_T* pt_this, BOOL b_up)
{
    //HANDLE_T                    h_folder_text=NULL_HANDLE;
    HANDLE_T                     h_widget=NULL_HANDLE;
    UINT8                       ui1_max_h_num = pt_this->ui1_max_h_num;
    UINT8                       ui1_max_v_num = pt_this->ui1_max_v_num;
    UINT32                      ui4_focus_idx = pt_this->ui4_focus_idx;
    UINT32                      ui4_hlt_idx     = pt_this->ui1_hlt_idx;
    UINT32                      ui4_hlt_row     = (UINT32)(ui4_hlt_idx / ui1_max_h_num);
    UINT32                      ui4_total_item_num=0;

   // if(pt_this->view_mode == MMP_FF_SET_PATH_FLAG_SKIP_FILE)
   // {
       // h_folder_text = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEX0 + ui4_hlt_idx* 2);
        //c_wgl_set_visibility(h_folder_text,WGL_SW_NORMAL);
   // }
   // else
  //  {}

    if (b_up)
    {

         if ((ui4_focus_idx == 0)||(ui4_hlt_row == 0))
        {
            h_widget=mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_RIGHT_TO_LEFT_BTN);
            return (c_wgl_set_focus(h_widget, WGL_SYNC_AUTO_REPAINT));
        }

        else
        {
            ui4_focus_idx -= ui1_max_h_num;
            ui4_hlt_idx -= ui1_max_h_num;
            _mmp_thumbnailmode_set_focus(pt_this, ui4_focus_idx, ui4_hlt_idx);

            return MMPR_OK;
        }
    }

    else
    {
        ui4_total_item_num= (pt_this->b_recursive== TRUE)? pt_this->ui4_file_num : (pt_this->ui4_file_num+pt_this->ui4_dir_num);
        if ((ui4_focus_idx >= ui4_total_item_num - 1)
                            ||((pt_this->ui4_focus_idx+3) >= ui4_total_item_num)
                            ||(ui4_hlt_row == ui1_max_v_num -1))
        /*  last  item of last page or  last row of this page */
        {
            return MMPR_OK;
        }

        else
        {
            ui4_focus_idx += ui1_max_h_num;
            ui4_hlt_idx += ui1_max_h_num;
            return( _mmp_thumbnailmode_set_focus(pt_this, ui4_focus_idx, ui4_hlt_idx));
        }
    }
}

#if 0

/*---------------------------------------------------------------------------*/
/**
 * @brief   Get highlight index according to focus item index
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] The index of focus item
 * @param   pui1_hlt_idx [out] Highlight index
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_get_hlt_idx(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx, UINT8* pui1_hlt_idx)
{
    UINT32                      ui4_first_item_idx = pt_this->ui4_focus_idx - pt_this->ui1_hlt_idx;
    UINT8                       ui1_max_h_num = pt_this->ui1_max_h_num;
    UINT8                       ui1_max_v_num = pt_this->ui1_max_v_num;

    if ((ui4_focus_idx >= ui4_first_item_idx) && (ui4_focus_idx < ui4_first_item_idx + ui1_max_h_num * ui1_max_v_num))
    {
        *pui1_hlt_idx = (UINT8)(pt_this->ui1_hlt_idx + (ui4_focus_idx - pt_this->ui4_focus_idx));
    }
    else if (ui4_focus_idx >= ui4_first_item_idx + ui1_max_h_num * ui1_max_v_num)
    {
        *pui1_hlt_idx =  (UINT8)(ui1_max_h_num * (ui1_max_v_num -1) +ui4_focus_idx % ui1_max_h_num);
    }
    /*else if (ui4_focus_idx < ui4_first_item_idx)*/
    else
    {
        *pui1_hlt_idx =  (UINT8)(ui4_focus_idx % ui1_max_h_num);
    }

    return MMPR_OK;
}
#endif

/*---------------------------------------------------------------------------*/
/**_mmp_thumbnailmode_set_transparent
 * @brief   Load thumbnail for next item within current folder
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
VOID _mmp_thumbnailmode_set_transparent(MMP_TM_MEMBER_T* pt_this, UINT16 ui2_thumb_item_idx)
{
    HANDLE_T       h_thumb_item_frm=NULL_HANDLE;
    UINT8          ui1_max_h_num = pt_this->ui1_max_h_num;
    UINT8          ui1_max_v_num = pt_this->ui1_max_v_num;
    GL_RECT_T     at_rect[TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_V_NUM];
    UINT32         ui4_trans_lst_start;                                 /* ui4_trans_lst_start is hlt idx */
    UINT32         ui4_first_item_idx = pt_this->ui4_focus_idx -
                                        pt_this->ui1_hlt_idx ;          /*ui4_first_item_idx is focus index of  first item in this PAGE */

    MMP_TM_TRANSPARENT_T*       pt_transp = &pt_this->at_transp;
    c_wgl_enable_transparent_list(pt_this->h_transparent_rect, TRUE, TRUE);
    if(pt_this->ui4_dir_num > ui4_first_item_idx)                   /* There is some dir in current PAGE  */
    {
        /* ui4_trans_lst_start  is same as num of dir in current PAGE */
        ui4_trans_lst_start = pt_this->ui4_dir_num -                /* pt_this->ui4_dir_num is same as first file focus index in this folder */
                              ui4_first_item_idx;

    }
    else
    {
        ui4_trans_lst_start = 0;
    }

    /* klocwork */


    MMP_ASSERT(ui2_thumb_item_idx < ui1_max_h_num * ui1_max_v_num);

    if((ui2_thumb_item_idx < TM_THUMB_SMALL_ITEM_FRAME_H_NUM * TM_THUMB_SMALL_ITEM_FRAME_V_NUM) &&
       (ui2_thumb_item_idx < ui1_max_h_num * ui1_max_v_num))
    {
        pt_transp->ab_is_enable[ui2_thumb_item_idx] = TRUE;
    }

    INT32 i,j, ui4_rect_count = 0;
    for(i = 0,j = 0;i < (ui2_thumb_item_idx - ui4_trans_lst_start + 1); i++)
    {

        if(pt_transp->ab_is_enable[ui4_trans_lst_start+i])
        {
            at_rect[j].i4_bottom = pt_transp->at_rect[ui4_trans_lst_start + i].i4_bottom;
            at_rect[j].i4_left   = pt_transp->at_rect[ui4_trans_lst_start + i].i4_left;
            at_rect[j].i4_right  = pt_transp->at_rect[ui4_trans_lst_start + i].i4_right;
            at_rect[j].i4_top    = pt_transp->at_rect[ui4_trans_lst_start + i].i4_top;
            j++;
        }
    }
    ui4_rect_count = j;
    c_wgl_set_transparent_list(pt_this->h_transparent_rect,
                               at_rect,
                               ui4_rect_count);
    h_thumb_item_frm = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + pt_this->ui2_thumb_item_idx * 2);
    c_wgl_repaint(h_thumb_item_frm,NULL,TRUE);

    //_mmp_thumbnailmode_enable_skip_flag(pt_this, pt_this->ui2_thumb_item_idx, TRUE);
}



/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_disable_transparent_list
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_disable_transparent_list(HANDLE_T h_rgn_list,             /* in: handle of a transparent list */
                                                         BOOL     b_enabled,              /* in: enable this list or not */
                                                         BOOL     b_exclusive)            /* in: set its state as exclusive or union */
{
    MMP_TM_MEMBER_T*    pt_this = &t_g_tm_member;
    UINT32               ui4_i = 0;

    /*Always ignore b_enable and b_exclusive*/
    c_wgl_enable_transparent_list(h_rgn_list, FALSE, FALSE);

    for(ui4_i = 0; ui4_i< TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_V_NUM; ui4_i++)
    {
        pt_this->at_transp.ab_is_enable[ui4_i] = FALSE;
    }
    c_wgl_enable_transparent_list(pt_this->h_preview_trans_list, FALSE, FALSE);
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_thumbnailmode_upd_item_list
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

static INT32 _mmp_thumbnailmode_upd_item_list(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx)
{
    UINT8                   ui1_hlt_idx = 0;
    pt_this->b_is_parsing_folder = FALSE;

    if (ui4_focus_idx != 0)
    {
        ui1_hlt_idx =(UINT8)(ui4_focus_idx % MMP_THMBNAILMODE_MAX_THUMBS);
        //_mmp_thumbnailmode_get_hlt_idx(pt_this, ui4_focus_idx, &ui1_hlt_idx);
    }
    DBG_INFO_DIRECT("[mmp tn] %s %d ui4_focus_idx:%d ui1_hlt_idx:%d\r\n",__FUNCTION__,__LINE__,ui4_focus_idx,ui1_hlt_idx);

    return _mmp_thumbnailmode_change_page(pt_this, ui4_focus_idx, ui1_hlt_idx);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Load thumbnail for some item within current folder
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] file item index
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_load_thumbnail(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx)
{
    CHAR                        s_full_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_ITEM_INFO_T             t_item_info={0};;
    MMP_MEDIA_TYPE_T            e_media_type;
    GL_RECT_T                   t_rect;
    HANDLE_T                    h_thumb_item = NULL_HANDLE;
    INT32                       i4_ret = MMPR_OK;
    UINT32                      ui4_cnt = 1;
    MMP_FP_LOAD_IMG_ROTATE_OP_T e_mmp_rotate = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;


    pt_this->ui4_thumb_idx_curr = ui4_focus_idx;

    i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,
                                  ITEM_TYPE_NONE,
                                  ui4_focus_idx,
                                  &ui4_cnt,
                                  &t_item_info);
    if (MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("[mmp] %s %d mmp_be_get_item_info failed %d \n",__FUNCTION__,__LINE__,i4_ret));
        return i4_ret;
    }

    MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);
    e_media_type = MMP_MEDIA_TYPE_PHOTO;
    mmp_mc_browse_query_file_type(s_full_path, &e_media_type, NULL);
    MMP_DBG_INFO(("[mmp] %s %d path is %s e_media_type is %d,ui4_focus_idx = %d\n",__FUNCTION__,__LINE__,s_full_path,e_media_type,ui4_focus_idx));
    switch (e_media_type)
    {
        case MMP_MEDIA_TYPE_PHOTO:
        {
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + pt_this->ui2_thumb_item_idx * 2);
            c_wgl_get_coords(h_thumb_item, WGL_COORDS_SCREEN, &t_rect);
            t_rect.i4_left       += MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            t_rect.i4_top        += MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            t_rect.i4_right      -= MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            t_rect.i4_bottom     -= MMP_BE_THUMBNAIL_FRM_BORDER_INSET;

            /*Check force rotate op*/
            if (MMP_BE_ITEM_FLAG_ROTATE & t_item_info.e_flag)
            {
                MMP_BE_RC_GET_MMP_ROTATE_FROM_ITEM_FLAG(t_item_info.e_flag, e_mmp_rotate);
            }
            DBG_INFO_DIRECT("[mmp tn] %s %d photo[%d] [l,t,r,b] = [%d,%d,%d,%d] e_mmp_rotate:%d  %s\n",
                __FUNCTION__,__LINE__,
                ui4_focus_idx,
                t_rect.i4_left,
                t_rect.i4_top,
                t_rect.i4_right,
                t_rect.i4_bottom,
                e_mmp_rotate,
                s_full_path);

            /* Load thumbnail to specified position */
            i4_ret = mmp_mc_browse_load_file_thumbnail_ex(s_full_path,
                                                          &t_rect,
                                                          MMP_FP_THUMB_COORDS_CANVAS,
                                                          e_mmp_rotate,
                                                          NULL);

            DBG_INFO_DIRECT("[mmp tn] %s %d mmp_mc_browse_load_file_thumbnail_ex() done!, ret:%d\r\n",__FUNCTION__,__LINE__,i4_ret);
            pt_this->ui4_thumb_idx_next++;
            if (i4_ret != MMPR_OK)
            {
                DBG_INFO_DIRECT("[mmp tn] %s %d load thumbnail failed, and contonue to load next thumbnail, ret:%d\r\n",__FUNCTION__,__LINE__,i4_ret);
                //c_wgl_repaint(h_thumb_item,NULL,TRUE);
                #if 1
                /* Load fail, continue to load next one*/
                mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                            _mmp_thumbnailmode_show_next_file_thumbnail,
                                            pt_this,
                                            (VOID*)FALSE,
                                            (VOID*)pt_this->ui4_thumb_idx_curr,
                                            NULL);
                #else
                _mmp_thumbnailmode_show_next_file_thumbnail(pt_this,
                                                    (VOID*)FALSE,
                                                    (VOID*)pt_this->ui4_thumb_idx_curr,
                                                    NULL);
                #endif
            }

        }
        break;

        case MMP_MEDIA_TYPE_UNKNOWN:
        {
            MMP_MEDIA_TYPE_T        e_filter_type;
            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_filter_type);

            if (e_filter_type == MMP_MEDIA_TYPE_PHOTO) /* Unknown photo format*/
            {
                pt_this->ui4_thumb_idx_next++;
                DBG_INFO_DIRECT("[mmp tn] %s %d unknown photo format, and continue load to next thumbnail\n",__FUNCTION__,__LINE__);
                mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                            _mmp_thumbnailmode_show_next_file_thumbnail,
                                            pt_this,
                                            (VOID*)FALSE,
                                            (VOID*)pt_this->ui4_thumb_idx_curr,
                                            NULL);
            }
        }
            break;
        default:
            break;
    }
    //IS_MMPR_OK (c_wgl_repaint(h_thumb_item,NULL,TRUE));
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Load thumbnail for some item within current folder
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] file item index
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

INT32 _mmp_thumbnailmode_init_attrib_settings(MMP_TM_MEMBER_T* pt_this)
{
    UINT8               ui1_photo_recur_parsing = 0;
    UINT8               ui1_cfg_value = 0;
    UINT32              i4_ret = MMPR_OK;

    a_cfg_custom_get_mmp_photo_recur_parsing(&ui1_photo_recur_parsing);
    pt_this->b_recursive = (BOOL)ui1_photo_recur_parsing;
    i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE,
                            (VOID*)(UINT32)ui1_photo_recur_parsing);

    MMPR_LOG_ON_FAIL(i4_ret);
    pt_this->changed_view_mode = MMP_FF_SET_PATH_FLAG_EMPTY;

    a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);
    pt_this->shuffle_type = (MMP_SHUFFLE_MODE_T)ui1_cfg_value;

    a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);
    pt_this->speed_type = (UINT32)ui1_cfg_value;

    a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);
    pt_this->effect_type = (MMP_TM_PHOTO_EFFECT)ui1_cfg_value;

    return MMPR_OK;
}
/*---------------------------------------------------------------------------*/
/**
 * @brief   Load thumbnail for some item within current folder
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] file item index
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_refresh_skip_flag(MMP_TM_MEMBER_T* pt_this)
{
    GL_RECT_T                       at_exclusive_rect[MMP_THMBNAILMODE_MAX_THUMBS];
    HANDLE_T                        h_skip_icon;
    UINT8                           i, ui1_rect_cnt = 0;

    //c_wgl_enable_transparent_list(pt_this->h_transparent_rect, TRUE, TRUE);
    c_memset(at_exclusive_rect,0,sizeof(at_exclusive_rect));

    for(i = 0; i < MMP_THMBNAILMODE_MAX_THUMBS; i++)
    {
        h_skip_icon = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SKIP0  + i);

        if(pt_this->b_skip_flag[i] == TRUE)
        {
            a_wdk_set_img_fg(h_skip_icon,
                             h_g_mmp_pop_up_exculde_htl_icon,
                             h_g_mmp_pop_up_exculde_htl_icon,
                             h_g_mmp_pop_up_exculde_htl_icon);
            c_wgl_set_visibility(h_skip_icon, WGL_SW_NORMAL);
            c_wgl_get_coords(h_skip_icon, WGL_COORDS_SCREEN, &at_exclusive_rect[ui1_rect_cnt]);
            ui1_rect_cnt ++;
        }
        else
        {
            c_wgl_set_visibility(h_skip_icon, WGL_SW_HIDE);
        }
    }
    c_wgl_add_transparent_list_exclusion(pt_this->h_transparent_rect, at_exclusive_rect, ui1_rect_cnt);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_thumbnailmode_enable_skip_flag
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_enable_skip_flag(MMP_TM_MEMBER_T* pt_this, UINT8 ui1_idx, BOOL b_skip)
{
    HANDLE_T        h_skip_btn;

    if (ui1_idx >= MMP_THMBNAILMODE_MAX_THUMBS)
    {
        return MMPR_INV_ARG;
    }
    pt_this->b_skip_flag[ui1_idx] = b_skip;

    //ensure the  wgl transparent state is false,to handle quickly user operation of DTV00671403.
    // the root cause is loading photos which is an async process that change the state.
    c_wgl_enable_transparent_list(pt_this->h_transparent_rect, FALSE, FALSE);

    _mmp_thumbnailmode_refresh_skip_flag(pt_this);

    mmp_thumbnailmode_upd_preview_trans_list(pt_this, ui1_idx);

    h_skip_btn = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SKIP0 + ui1_idx);
    c_wgl_repaint(h_skip_btn, NULL, TRUE);

    c_wgl_repaint(pt_this->h_pop_up_skip_icon, NULL, TRUE);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_thumbnailmode_reset_skip_flag
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_reset_skip_flag(MMP_TM_MEMBER_T* pt_this)
{
    UINT8           i;

    for(i = 0; i < MMP_THMBNAILMODE_MAX_THUMBS; i++)
    {
        pt_this->b_skip_flag[i] = FALSE;
    }
    _mmp_thumbnailmode_refresh_skip_flag(pt_this);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Load thumbnail for next item within current folder
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_thumbnailmode_show_next_file_thumbnail(VOID* pv_tag1,   /*(MMP_TM_MEMBER_T*)*/
                                                        VOID* pv_tag2,   /*Load result of current file*/
                                                        VOID* pv_tag3,   /*Current file index*/
                                                        VOID* pv_tag4)
{
    UINT8                    ui1_id;
    BOOL                     b_is_show;
    MMP_TM_MEMBER_T*         pt_this = (MMP_TM_MEMBER_T*)pv_tag1;

    if (pt_this == NULL)
    {
        return;
    }
    MMP_DBG_INFO(("[mmp] %s %d ui4_thumb_idx_next:%d  ui4_thumb_idx_end:%d \r\n",__FUNCTION__,__LINE__,pt_this->ui4_thumb_idx_next,pt_this->ui4_thumb_idx_end));

    if (FALSE == pt_this->b_loading_thumb)
    {
        /*This event is caused by rotate preivew image, ignore...*/
        if (MMP_TM_POPUP_STATUS_PREVIEW == pt_this->e_popup_status)
        {
            DBG_INFO_DIRECT("[mmp tn] %s %d MMP_TM_POPUP_STATUS_PREVIEW == pt_this->e_popup_status \r\n",__FUNCTION__,__LINE__);
            c_wgl_enable_transparent_list(pt_this->h_preview_trans_list, TRUE, TRUE);
            c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_rect_preview, TRUE);
        }
        return;
    }

    /* Check if this notify out of date */
    if (pt_this->ui4_thumb_idx_curr != (UINT32)pv_tag3)
    {
        return;
    }

    /* If load thumbnail success, clear standard icon at the same position */
    if ((BOOL)(UINT32)pv_tag2)
    {
    	DBG_INFO_DIRECT("[mmp tn] %s %d _mmp_thumbnailmode_set_transparent() done!! ui2_thumb_item_idx:%d \r\n",__FUNCTION__,__LINE__,pt_this->ui2_thumb_item_idx);
    	_mmp_thumbnailmode_set_transparent(pt_this,pt_this->ui2_thumb_item_idx);
    }

    /* Check if there is remaining thumbnail to load */
    if (pt_this->ui4_thumb_idx_next == pt_this->ui4_thumb_idx_end)
    {
        pt_this->b_loading_thumb = FALSE;
        if (MMP_TM_POPUP_STATUS_ON == pt_this->e_popup_status)
        {
            DBG_INFO_DIRECT("[mmp tn] %s %d _mmp_thumbnailmode_set_transparent() doning!! ui2_thumb_item_idx:%d \r\n",__FUNCTION__,__LINE__,pt_this->ui2_thumb_item_idx);
            mmp_thumbnailmode_show_img_preview(pt_this, TRUE);
        }
        return;
    }

    pt_this->ui2_thumb_item_idx++;
    _mmp_thumbnailmode_load_thumbnail(pt_this, pt_this->ui4_thumb_idx_next);

    return;
}



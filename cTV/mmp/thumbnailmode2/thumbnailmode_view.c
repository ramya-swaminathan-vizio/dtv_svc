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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
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
#include "c_dbg.h"
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



#if 0
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_view_hide_animation
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */ 
/*---------------------------------------------------------------------------*/

INT32 mmp_thumbnailmode_view_hide_animation(VOID)
{
    INT32            i4_ret;

    i4_ret = mmp_common_ui_animation_stop();
    MMPR_LOG_ON_FAIL(i4_ret);
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief  mmp_thumbnailmode_view_show_animation
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

INT32 mmp_thumbnailmode_view_show_animation(VOID)
{
    INT32            i4_ret;

    i4_ret = mmp_common_ui_animation_start(10, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);
    return MMPR_OK;
}

#endif
/*---------------------------------------------------------------------------*/
/**
 * @brief
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_hide_all_thumb(MMP_TM_MEMBER_T* pt_this)
{
    UINT32                  ui4_i;
    HANDLE_T                h_thumb_item;

    /*  set don't handle the key left,right,up and down */
    pt_this->b_is_parsing_folder = TRUE;
    IS_MMPR_OK (c_wgl_set_visibility(pt_this->h_frm_htl_thumbnail_mov_frm, WGL_SW_HIDE));
    for (ui4_i = 0; ui4_i < TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_V_NUM; ui4_i++)
    {
        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui4_i * 2);
        IS_MMPR_OK( c_wgl_set_visibility (h_thumb_item, WGL_SW_HIDE));

        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEXT0 + ui4_i * 2);
        IS_MMPR_OK( c_wgl_set_visibility (h_thumb_item, WGL_SW_HIDE));
    }
    mmp_mc_browse_stop_file_thumbnail();
    mmp_mc_browse_reset_info_resoruce();
    c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,TRUE);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_thumbnailmode_view_get_usb_dev_serial_name
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MMPR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_get_usb_dev_serial_name(
                                    UINT32              ui4_idx,
                                    UTF16_T*            ws_text)
{
    INT32   i4_ret = MMPR_OK;
    CHAR    ac_temp[MMP_TM_VIEW_INFO_STR_MAX_LEN] = {0};
#ifdef SUPPORT_ONLY_ONE_USB_PORT
    c_strncpy(ac_temp, "USB:", MMP_DEV_NAME_MAX_LEN);
#else
    /* only one usb port. */
    if (1 == a_cfg_custom_plf_opt_get_usb_num())
    {
        c_strncpy(ac_temp, "USB:", MMP_DEV_NAME_MAX_LEN);
    }
    else
    {
        c_sprintf(ac_temp, MMP_DEV_LIST_USB_DEV_PREFIX, ui4_idx);
    }
 #endif
    i4_ret = c_uc_ps_to_w2s(ac_temp, ws_text, MMP_TM_VIEW_INFO_STR_MAX_LEN);
    IS_MMPR_OK(i4_ret);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _mmp_thumbnailmode_view_get_dlna_dev_serial_name
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MMPR_OK        Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_view_get_dlna_dev_serial_name(
                                    UINT32              ui4_idx,
                                    UTF16_T*            ws_text)
{
    INT32   i4_ret = MMPR_OK;
    CHAR    ac_temp[MMP_TM_VIEW_INFO_STR_MAX_LEN] = {0};

    c_sprintf(ac_temp, MMP_DEV_LIST_DLNA_DEV_PREFIX, ui4_idx);
    i4_ret = c_uc_ps_to_w2s(ac_temp, ws_text, MMP_TM_VIEW_INFO_STR_MAX_LEN);
    IS_MMPR_OK(i4_ret);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_update_ui
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_update_ui(MMP_TM_MEMBER_T* pt_this, MMP_TM_UPDATE_REASON_T e_upd_reason, BOOL b_repaint)
{
    MMP_BE_STATUS_T           e_status;
    INT32                       i4_ret=MMPR_OK;
    HANDLE_T                    h_view_item=NULL_HANDLE;

    if(NULL == pt_this)
    {
        return MMPR_INV_ARG;
    }

    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);

    if(MMP_TM_UPDATE_REASON_HIDE_RIGHT_FRAM & e_upd_reason)
    {
        mmp_thumbnailmode_empty_folders_and_files(pt_this,TRUE);
    }

    if (MMP_TM_UPDATE_REASON_HIDE_FILE_INFO & e_upd_reason)
    {
        c_wgl_set_visibility(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO),WGL_SW_HIDE_RECURSIVE);
        c_wgl_repaint(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_FILE_INFO),NULL,TRUE);
    }

    if (MMP_TM_UPDATE_REASON_CLEAN_PAGE_INFO & e_upd_reason)
    {
       // _mmp_thumbnailmode_clean_page_info(pt_this);
    }

    if (MMP_TM_UDPATE_REASON_DEV_NUM_CHG & e_upd_reason)
    {
        i4_ret = mmp_thumbnailmode_view_dev_num_xng_proc(pt_this);
        MMPR_LOG_ON_FAIL(i4_ret);

    }

    if (MMP_TM_UDPATE_REASON_BK_PLAYER_STOP & e_upd_reason)
    {
        mmp_mc_browse_show_info_handler(FALSE,FALSE,TRUE);
        //IS_MMPR_OK(c_wgl_repaint(pt_this->h_play_frm,NULL,TRUE));
    }

    if (MMP_TM_UPDATE_REASON_ACT_MEDIA_RMV & e_upd_reason)
    {
        /* Reset top info */
    }

    if (MMP_TM_UPDATE_REASON_HIDE_ALL_THUMB & e_upd_reason)
    {
        _mmp_thumbnailmode_hide_all_thumb(pt_this);
    }

    if (MMP_TM_UPDATE_REASON_FDLR_NAME & e_upd_reason)
    {
        INT32                   i4_ret;
        i4_ret = mmp_thumbnailmode_view_set_path(b_repaint);
        IS_MMPR_OK(i4_ret);
    }
     if (MMP_TM_UPDATE_RESAON_LEFT_UI & e_upd_reason)
    {
        h_view_item = mmp_tm_focus_get_wgt_hdl(WID_MMP_TM_FOCUS_LB_FILE);
        c_wgl_set_visibility(h_view_item,WGL_SW_HIDE_RECURSIVE);

        h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
        c_wgl_set_visibility(h_view_item,WGL_SW_RECURSIVE);
        c_wgl_repaint(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_BASE_FRM),NULL ,TRUE);
    }

    if (MMP_TM_UPDATE_RESAON_PAGE & e_upd_reason)
    {
        c_wgl_set_visibility(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_PAGE_NUM) ,WGL_SW_HIDE);
        c_wgl_set_visibility(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_PAGE_NEXT) ,WGL_SW_HIDE);
        c_wgl_set_visibility(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_PAGE_BACK) ,WGL_SW_HIDE);
        c_wgl_repaint(mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_RIGHT_BASE_FRM),NULL ,TRUE);
        c_wgl_enable_transparent_list(pt_this->h_preview_trans_list, FALSE, FALSE);
        c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_rect_preview, TRUE);
        //_mmp_thumbnailmode_refresh_skip_flag(pt_this);
        if (MMP_TM_POPUP_STATUS_PREVIEW == pt_this->e_popup_status)
        {
            mmp_thumbnailmode_show_img_preview(pt_this, FALSE);
        }
        h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_POP_UP_BASE_FRM);
        c_wgl_set_visibility (h_view_item, WGL_SW_HIDE_RECURSIVE);
        c_wgl_repaint(h_view_item,NULL,TRUE);
        pt_this->e_popup_status = MMP_TM_POPUP_STATUS_OFF;
        pt_this->h_last_focus_wigt = pt_this->h_last_left_focus_wigt ;
        c_wgl_set_focus(pt_this->h_last_focus_wigt,WGL_SYNC_AUTO_REPAINT);
    }

    if (MP_TM_UPDATE_RESAON_SET_PAGE_NUM & e_upd_reason)
    {
        mmp_thumbnailmode_set_page_num(pt_this,pt_this->ui4_focus_idx);
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Update scroll bar on the right side
 * @param   ui4_item_idx [in] The fist item index in current page
 * @param   ui4_item_num [in] The number of items in current dir
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

#if 0
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_set_item_status_show
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_set_item_status_show(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_item_idx, UINT32 ui4_idx_in_page, BOOL b_auto_paint)
{
    INT32               i4_ret;
    BOOL                b_selected = FALSE;
    HANDLE_T            h_thumb_item;
    WGL_IMG_INFO_T      t_img_info;

    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui4_idx_in_page);

    i4_ret = mmp_be_file_in_list(MMP_FF_ITEM_LIST_TYPE_COPY_LIST, ui4_item_idx, &b_selected);
    if (MMPR_OK != i4_ret)
    {
        return (i4_ret);
    }

    t_img_info.e_type = WGL_IMG_SET_BASIC;

    if (b_selected)
    {
        mmp_img_get_img(MMP_IMG_IMAGE_ID_COPY_THUMBNAIL, &(t_img_info.u_img_data.t_standard.t_enable));
        mmp_img_get_img(MMP_IMG_IMAGE_ID_COPY_THUMBNAIL, &(t_img_info.u_img_data.t_standard.t_disable));
    }
    else
    {
        i4_ret = mmp_be_file_in_list(MMP_FF_ITEM_LIST_TYPE_SEL_LIST, ui4_item_idx, &b_selected);
        if (MMPR_OK != i4_ret)
        {
            return (i4_ret);
        }
        if (b_selected)
        {
            mmp_img_get_img(MMP_IMG_IMAGE_ID_SELECT_THUMBNAIL, &(t_img_info.u_img_data.t_standard.t_enable));
            mmp_img_get_img(MMP_IMG_IMAGE_ID_SELECT_THUMBNAIL, &(t_img_info.u_img_data.t_standard.t_disable));
        }
        else
        {
            t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE ;
            t_img_info.u_img_data.t_standard.t_disable =  NULL_HANDLE;
        }
    }

    i4_ret= c_wgl_do_cmd(h_thumb_item,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK (WGL_IMG_BK),
                           WGL_PACK (& t_img_info));
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    i4_ret =  c_wgl_set_visibility(h_thumb_item,WGL_SW_NORMAL);
    if (WGLR_OK != i4_ret)
    {
        return (i4_ret);
    }

    if (b_auto_paint)
    {
        i4_ret = c_wgl_repaint(h_thumb_item, NULL, TRUE);
        if (WGLR_OK != i4_ret)
        {
            return (i4_ret);
        }
    }

    return (MMPR_OK);
}

#endif

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_empty_folders_and files
 * @param
 * @param
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_empty_folders_and_files(MMP_TM_MEMBER_T* pt_this ,BOOL b_repaint)
{
    INT32           ui4_i,i4_ret=MMPR_OK;
    HANDLE_T        h_thumb_item=NULL_HANDLE,h_folder_item=NULL_HANDLE;
    HANDLE_T        h_thumb_text=NULL_HANDLE,h_folder_text=NULL_HANDLE;


    for(ui4_i=0;ui4_i<MMP_THMBNAILMODE_MAX_THUMBS;ui4_i++)
    {
        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui4_i * 2);
        c_wgl_set_visibility (h_thumb_item,  WGL_SW_HIDE_RECURSIVE);

        h_thumb_text = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEXT0 + ui4_i * 2);
        c_wgl_set_visibility (h_thumb_text, WGL_SW_HIDE_RECURSIVE);

        h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_PRE_FOLDER + ui4_i * 2);
        c_wgl_set_visibility (h_folder_item,  WGL_SW_HIDE_RECURSIVE);

        h_folder_text = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEX0 + ui4_i * 2);
        c_wgl_set_visibility (h_folder_text, WGL_SW_HIDE_RECURSIVE);
    }
    c_wgl_set_visibility(pt_this->h_frm_htl_thumbnail_mov_frm,WGL_SW_HIDE);
    c_wgl_set_visibility(pt_this->h_frm_htl_folder_mov_frm,WGL_SW_HIDE_RECURSIVE);
    c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm ,WGL_SW_NORMAL);
    i4_ret = c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,b_repaint);
    IS_MMPR_OK(i4_ret);
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_show_warning_msg
 * @param
 * @param
 */
/*---------------------------------------------------------------------------*/

INT32 mmp_thumbnailmode_show_warning_msg(MMP_TM_MEMBER_T* pt_this,
                                         MMP_TM_VIEW_WARN_MSG_ID_T e_warning_id,
                                         BOOL b_is_show,
                                         BOOL b_is_repaint)
{
    UINT16                          ui2_mlm_idx = 0;
    INT32                           i4_ret=MMPR_OK;
    MMP_IB_MSG_CLASS_T              e_msg_class;
    UTF16_T                         ws_osd_msg[100] = { 0 };

    if(b_is_show == TRUE)
    {

        MMP_TM_RC_GET_MSG_SETTING(e_warning_id, ui2_mlm_idx, e_msg_class);
        c_uc_w2s_strcpy(ws_osd_msg,
                        MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,ui2_mlm_idx));

        i4_ret = mmp_info_bar_set_status_msg(
                                            e_msg_class,
                                            MMP_IB_STATUS_MSG_TYPE_FLDR_STATUS,
                                            MMP_IB_STATUS_MSG_ID_FLDR_STATUS,
                                            ws_osd_msg
                                            );
        if (MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("mmp_info_bar_set_status_msg() returns %d.\n", i4_ret));
        }

        pt_this->b_is_nofile_show = TRUE;

    }
    else
    {
        /* HIDE notify no file in this folder  */
        if(pt_this->b_is_nofile_show == TRUE)
        {
            i4_ret = mmp_info_bar_hide();
            if (MMPR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("mmp_info_bar_hide() returns %d.\n", i4_ret));
            }
            pt_this->b_is_nofile_show = FALSE;
        }
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] item index in current folder
 */
/*---------------------------------------------------------------------------*/

INT32 mmp_thumbnailmode_view_set_path(BOOL b_repaint)
{
    UTF16_T                 w2s_text[MMP_BE_MAX_PATH_LEN+1]={0};
    UTF16_T*                pw2s_file_path = NULL;
    SIZE_T                  z_size = MMP_BE_MAX_PATH_LEN;
    INT32                    i4_ret=MMPR_OK;
    HANDLE_T                h_fin_path_txt = NULL_HANDLE;
    HANDLE_T                h_ful_path_txt = NULL_HANDLE;

    i4_ret = mmp_be_get_curr_path_display(w2s_text, &pw2s_file_path, &z_size);
    IS_MMPR_OK(i4_ret);

    h_ful_path_txt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_PATH);

    i4_ret = c_wgl_do_cmd (h_ful_path_txt,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(w2s_text),
                           WGL_PACK((UINT16)0xFFFF));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility(h_ful_path_txt,WGL_SW_NORMAL);
    IS_MMPR_OK(i4_ret);

    h_fin_path_txt = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_FILE_NAME);
    i4_ret = c_wgl_do_cmd (h_fin_path_txt,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(pw2s_file_path),
                           WGL_PACK((UINT16)0xFFFF));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility(h_fin_path_txt,WGL_SW_NORMAL);
    IS_MMPR_OK(i4_ret);
    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(h_ful_path_txt,NULL,b_repaint);
        IS_MMPR_OK(i4_ret);
        i4_ret = c_wgl_repaint(h_fin_path_txt,NULL,b_repaint);
        IS_MMPR_OK(i4_ret);

    }

    return MMPR_OK;
}


/*---------------------------------------------------------------------------*/
/**mmp_thumbnailmode_set_widget
 * @brief
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] item index in current folder
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_view_updatet_widget_text(MMP_TM_MEMBER_T* pt_this)
{
    INT32               i4_ret=MMPR_OK;
    HANDLE_T            h_view_item=NULL_HANDLE;
    UINT8               ui1_cfg_value = 0;
    UINT32              ui4_cfg_value = 0;
    UINT32              ui4_recur_flag = 0;
    ISO_639_LANG_T      s639_lang;
    
    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret == APP_CFGR_OK)
    {
        pt_this->ui1_gui_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }
    else
    {
        pt_this->ui1_gui_lang_id = 0;     
        DBG_ERROR(("<MMP thumbnail >Get gui lanugage failed! set lang id = 0 \r\n"));        
    }
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

    /*sort text*/
    i4_ret = h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_SORT);
    i4_ret = c_wgl_do_cmd (h_view_item,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THU_MODE_SORT)),
                        WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THU_MODE_SORT))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    /* view text */
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_VIEW);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THU_MODE_VIEW)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THU_MODE_VIEW))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    /* start_slideshow btn text */
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_START_SLIDESHOW);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_BTN_START_SLIDESHOW)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_BTN_START_SLIDESHOW))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    /* sort btn text    default   */
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_SORT__NAME_A_Z+ui4_cfg_value)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_SORT__NAME_A_Z+ui4_cfg_value))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);


    /*  view btn   text */
    if(TRUE == pt_this->b_recursive)
    {
        ui4_recur_flag = 0;
    }
    else
    {
        ui4_recur_flag =  1;
    }
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS+ui4_recur_flag)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS+ui4_recur_flag))));
     IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    /* setting  btn text */
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_BTN_SETTINGS)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_BTN_SETTINGS))));

    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    /* browse music  btn text */
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_BROWSE_MUSIC);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_SET_BTN_BROWSE_MUSIC)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_SET_BTN_BROWSE_MUSIC))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);



    /* media type  btn text */
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_MEDIA_TYPE);
    i4_ret = c_wgl_do_cmd (h_view_item,
                        WGL_CMD_BTN_SET_TEXT,
                        WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_MEDIA_TYPE_OPTION_PHOTO)),
                        WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_MEDIA_TYPE_OPTION_PHOTO))));
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
    /* pop up photo txt*/
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_MODIFY_PHOTO);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_TITLE_MODIFY_PHOTO))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    /*start slideshow btn text*/
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_STARTSLIDESHOW_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_START_SLIDESHOW))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
    /* done  btn text*/

    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_DONE_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_DONE)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_BTN_DONE))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);

    /*full screen  btn text*/
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_FULL_SCREEN_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_FULLSCREEN)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_POP_UP_FULLSCREEN))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);


    /*start slideshow btn text*/
    h_view_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_STARTSLIDESHOW_BTN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_BTN_START_SLIDESHOW)),
                            WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_BTN_START_SLIDESHOW))));
    IS_MMPR_OK(i4_ret);
    c_wgl_set_visibility (h_view_item, WGL_SW_RECURSIVE);
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Update total page number and current page index
 * @param   pt_this [in] View instance
 * @param   ui4_focus_idx [in] item index in current folder
 */
/*---------------------------------------------------------------------------*/
VOID mmp_thumbnailmode_set_page_num(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_focus_idx)
{
    CHAR                        s_result[MMP_TM_VIEW_INFO_STR_MAX_LEN] = {0};
    CHAR                        s_dest_result[MMP_TM_VIEW_INFO_STR_MAX_LEN] = {0};
    UTF16_T                     w2s_info[MMP_TM_VIEW_INFO_STR_MAX_LEN] = {0};
    UINT32                      ui4_item_num;
    UINT16                      ui2_crt_page, ui2_page_cnt, ui2_page_item_num;
    INT32                       i4_ret;
    HANDLE_T                    h_thumb_item;
    WGL_IMG_INFO_T              t_img_info ;;
    HANDLE_T                    h_icon_1;
    HANDLE_T                    h_icon_2;

    i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT,&(pt_this->ui4_dir_num),&(pt_this->ui4_file_num));
    ui4_item_num = pt_this->ui4_dir_num + pt_this->ui4_file_num;
    ui2_page_item_num = pt_this->ui1_max_h_num * pt_this->ui1_max_v_num;

    ui2_page_cnt = (UINT16)((ui4_item_num + (ui2_page_item_num-1))/ ui2_page_item_num);

    ui2_crt_page = (UINT16)((ui4_focus_idx+1 + (ui2_page_item_num-1))/ ui2_page_item_num);
    
    /*  set the images of page_back_btn and page_next_btn   */
    h_icon_1 = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_PAGE_BACK);
    h_icon_2 = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_PAGE_NEXT);
    t_img_info.e_type = WGL_IMG_SET_STANDARD;

    if(ui2_page_cnt != 0)
    {
        if(ui2_page_cnt == 1)
        {

            t_img_info.u_img_data.t_standard.t_enable    =  h_g_mmp_pg_back_icon_dim;
            t_img_info.u_img_data.t_standard.t_disable   =  h_g_mmp_pg_back_icon_dim;
            t_img_info.u_img_data.t_standard.t_highlight =  h_g_mmp_pg_back_icon_dim;
            i4_ret = c_wgl_do_cmd (h_icon_1,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK (WGL_IMG_FG),
                          WGL_PACK (& t_img_info));
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_PG_SET_RANGE) fail. i4_ret = %d.\r\n", i4_ret));

            }


            t_img_info.u_img_data.t_standard.t_enable    =  h_g_mmp_pg_next_icon_dim;
            t_img_info.u_img_data.t_standard.t_disable   =  h_g_mmp_pg_next_icon_dim;
            t_img_info.u_img_data.t_standard.t_highlight =  h_g_mmp_pg_next_icon_dim;
            i4_ret = c_wgl_do_cmd (h_icon_2,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK (WGL_IMG_FG),
                          WGL_PACK (& t_img_info));
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_PG_SET_RANGE) fail. i4_ret = %d.\r\n", i4_ret));
            }

        }
        else
        {
            if( ui2_crt_page == 1)
            {
                t_img_info.u_img_data.t_standard.t_enable    =  h_g_mmp_pg_back_icon_dim;
                t_img_info.u_img_data.t_standard.t_disable   =  h_g_mmp_pg_back_icon_dim;
                t_img_info.u_img_data.t_standard.t_highlight =  h_g_mmp_pg_back_icon_dim;
            }
            else
            {
                t_img_info.u_img_data.t_standard.t_enable    =  h_g_mmp_pg_back_icon_nr;
                t_img_info.u_img_data.t_standard.t_disable   =  h_g_mmp_pg_back_icon_nr;
                t_img_info.u_img_data.t_standard.t_highlight =  h_g_mmp_pg_back_icon_nr;
            }
            i4_ret = c_wgl_do_cmd (h_icon_1,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK (WGL_IMG_FG),
                          WGL_PACK (& t_img_info));
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_PG_SET_RANGE) fail. i4_ret = %d.\r\n", i4_ret));
            }

            t_img_info.u_img_data.t_standard.t_enable    =  h_g_mmp_pg_next_icon_nr;
            t_img_info.u_img_data.t_standard.t_disable   =  h_g_mmp_pg_next_icon_nr;
            i4_ret = c_wgl_do_cmd (h_icon_2,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK (WGL_IMG_FG),
                          WGL_PACK (& t_img_info));
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_PG_SET_RANGE) fail. i4_ret = %d.\r\n", i4_ret));
            }

        }

        c_wgl_set_visibility(h_icon_1 ,WGL_SW_NORMAL);
        c_wgl_set_visibility(h_icon_2 ,WGL_SW_NORMAL);
        c_wgl_repaint(h_icon_1,NULL,TRUE);
        c_wgl_repaint(h_icon_2,NULL,TRUE);

        i4_ret = c_uc_w2s_to_ps(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_MMP_PAGE_INFO_TEMP),
                                s_result,
                                sizeof(s_result));
        MMPR_LOG_ON_FAIL(i4_ret);

        c_snprintf(s_dest_result,(SIZE_T)(MMP_TM_VIEW_INFO_STR_MAX_LEN), s_result, ui2_crt_page, ui2_page_cnt);
        c_uc_ps_to_w2s(s_dest_result, w2s_info, sizeof(w2s_info));

        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_PAGE_NUM);
        i4_ret =  c_wgl_do_cmd (h_thumb_item,
                                WGL_CMD_TEXT_SET_TEXT,
                                WGL_PACK (w2s_info),
                                WGL_PACK (c_uc_w2s_strlen (w2s_info)));
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        }
        c_wgl_set_visibility(h_thumb_item ,WGL_SW_NORMAL);
        c_wgl_repaint(h_thumb_item, NULL, TRUE);
    }
    else
    {
         DBG_LOG_PRINT(("NULL FILE OR THUMBNAIL \n"));
    }

}

/*----------------------------------------------------------------------------
 * Name: mmp_thumbnailmode_view_update_driver_name
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *          MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_view_update_driver_name(BOOL  b_repaint,BOOL *pb_is_usb)
{
    RMV_DEV_DEVICE_STATUS_T     e_dev_status;
    INT32                       i4_ret = MMPR_OK;
    CHAR                        ac_path[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    CHAR                        ac_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UTF16_T                     w2s_dev_info[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    UTF16_T                     w2s_dev_hint[MMP_DEV_NAME_MAX_LEN + 1] = {0};
    SIZE_T                      z_size = MMP_DEV_NAME_MAX_LEN;
    UINT32                      ui4_len = MMP_DEV_NAME_MAX_LEN;
    UINT32                      ui4_idx = 0;
    UINT32                      ui4_active_idx = 0;
    UINT32                      ui4_dlna_id = 0;
    UINT32                      ui4_usb_id = 0;
    HANDLE_T                    h_widget = NULL_HANDLE;
    UINT16                      ui2_char_len = 0;

    i4_ret = a_rmv_dev_get_active_mnt_pnt(&ui4_active_idx, &z_size, ac_path);
    IS_MMPR_OK(i4_ret);

    for (ui4_idx = 0;
         (ui4_idx <= ui4_active_idx) && (ui4_active_idx < MMP_DEV_LIST_MAX_NUM);
         ui4_idx++)
    {
        /* query mount point status */
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_idx,
                                    &e_dev_status);
        if(MMPR_OK != i4_ret)
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            continue;
        }

        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {

            ui4_dlna_id++;
        }
        else if(!(RMV_DEV_DEVICE_STATUS_UNSUPT_DEV & e_dev_status))
        {
            ui4_usb_id++;
        }
    }

    /*query mount point status*/
    i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                ui4_active_idx,
                                &e_dev_status);
    IS_MMPR_OK(i4_ret);

    if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
        (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
    {
        return MMPR_FAIL;
    }

    if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
    {
        z_size = MMP_DEV_NAME_MAX_LEN;
        i4_ret = a_rmv_dev_get_mnt_point_info(
                                ui4_active_idx,
                                RMV_DEV_INFO_ID_DESC,
                                &z_size,
                                (VOID*)(ac_info));
        IS_MMPR_OK(i4_ret);

        i4_ret = _mmp_thumbnailmode_view_get_dlna_dev_serial_name(ui4_dlna_id, w2s_dev_hint);
        IS_MMPR_OK(i4_ret);
        *pb_is_usb = FALSE;
    }
    else
    {
        i4_ret = c_fm_get_volume_label(NULL_HANDLE,
                                       ac_path,
                                       ac_info,
                                       &ui4_len);
        IS_MMPR_OK(i4_ret);

        i4_ret = _mmp_thumbnailmode_view_get_usb_dev_serial_name(ui4_usb_id, w2s_dev_hint);
        IS_MMPR_OK(i4_ret);
        *pb_is_usb = TRUE;
    }

    ui2_char_len = c_strlen(ac_info);
    if((ui2_char_len > 0) && (ac_info[ui2_char_len - 1] == 0x22))
    {
        ac_info[ui2_char_len - 1] = 0;
    }
    i4_ret = c_uc_ps_to_w2s(ac_info, w2s_dev_info, MMP_DEV_NAME_MAX_LEN);
    IS_MMPR_OK(i4_ret);


    h_widget = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_LB_DRIVER);
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, 0),
                          WGL_PACK (w2s_dev_hint));
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, 1),
                          WGL_PACK (w2s_dev_info));
    IS_MMPR_OK(i4_ret);

    c_wgl_set_visibility(h_widget, WGL_SW_NORMAL);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
        IS_MMPR_OK(i4_ret);
    }
    return MMPR_OK;
}


/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnail_display_file_info
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
 INT32 mmp_thumbnail_display_file_info(MMP_TM_MEMBER_T* pt_this)
{
     MMP_FP_INFO_HDLR_INIT_PARAM_T  t_param;
     GL_RECT_T                      t_rect = {0};
     MMP_BE_STATUS_T                e_status;

     mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);

     DBG_INFO_DIRECT("[mmp tv] %s %d e_status:%d\n",__FUNCTION__,__LINE__,e_status);

     if(MMP_BE_STATUS_CHOOSE_FF == e_status)
     {
        return MMPR_OK;
     }

     SET_RECT_BY_SIZE (&t_rect,
                       TM_FILE_INFO_HANDLE_X,
                       TM_FILE_INFO_HANDLE_Y,
                       TM_FILE_INFO_HANDLE_W,
                       TM_FILE_INFO_HANDLE_H);
     t_param.e_ui_type = MMP_FP_INFO_HDLR_UI_TYPE_TM_FOCUS;
     t_param.h_parent  = pt_this->h_info_frm;
     t_param.pt_rect = &t_rect;
     c_wgl_set_visibility( pt_this->h_info_frm,WGL_SW_RECURSIVE);
     return mmp_mc_browse_display_focus_item_info(&t_param);
}


extern INT32 mmp_pe_gl_dfb_snapshot_load(GL_RECT_T* pt_rect, BOOL b_need_reflash);
extern INT32 mmp_pe_gl_dfb_snapshot_save(GL_RECT_T* pt_rect, BOOL b_clean_after_save);


/*---------------------------------------------------------------------------e*/
/**mmp_thumbnailmode_show_img_preview
 * @brief   Thumbnail mode deinit function
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_show_img_preview(MMP_TM_MEMBER_T* pt_this, BOOL b_show)
{
    HANDLE_T        h_thumb_item;
    GL_RECT_T       t_rect_preview, t_rect_thumb;

    CHAR                            s_full_path[MMP_BE_MAX_PATH_LEN] = {0};
    MMP_ITEM_INFO_T                 t_item_info = {0};
    UINT32                          ui4_cnt = 1;
    INT32                           i4_ret;
    MMP_FP_LOAD_IMG_ROTATE_OP_T     e_mmp_rotate = MMP_FP_LOAD_IMG_ROTATE_OP_KEEP_AS_FILE;


    if (pt_this->ui1_hlt_idx < TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_H_NUM &&
        FALSE == pt_this->at_transp.ab_is_enable[pt_this->ui1_hlt_idx])
    {
        return MMPR_OK;
    }



    c_memcpy(&t_rect_preview, &pt_this->t_rect_preview, sizeof(GL_RECT_T));
    mmp_drc_convert_rect_coord(MMP_FP_THUMB_COORDS_CANVAS, &t_rect_preview);

    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + pt_this->ui1_hlt_idx * 2);
    c_wgl_get_coords(h_thumb_item, WGL_COORDS_SCREEN, &t_rect_thumb);
    SHRINK_RECT(&t_rect_thumb, MMP_BE_THUMBNAIL_FRM_BORDER_INSET);
    mmp_drc_convert_rect_coord(MMP_FP_THUMB_COORDS_CANVAS, &t_rect_thumb);

    if (b_show)
    {
        mmp_pe_gl_dfb_snapshot_save(&t_rect_preview,TRUE);

        i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE,
                                      pt_this->ui4_focus_idx,
                                      &ui4_cnt,
                                      &t_item_info);
        if (MMPR_OK != i4_ret)
        {
            return MMPR_OK;
        }
        if (0 == (MMP_BE_ITEM_FLAG_ROTATE & t_item_info.e_flag))
        {  
            MMP_DBG_INFO(("[%s %d] mmp_mc_browse_load_file_thumbnail IN  i4_left:%d,i4_top:%d,i4_right:%d,i4_bottom,%d \r\n",__FUNCTION__,__LINE__,t_rect_preview.i4_left,t_rect_preview.i4_top,t_rect_preview.i4_right,t_rect_preview.i4_bottom));
            mmp_mc_browse_load_file_thumbnail(&pt_this->t_rect_preview, MMP_FP_THUMB_COORDS_CANVAS);
        }
        else
        {
            
            MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);
            MMP_BE_RC_GET_MMP_ROTATE_FROM_ITEM_FLAG(t_item_info.e_flag, e_mmp_rotate);
            mmp_mc_browse_load_file_thumbnail_ex(s_full_path,
                                                 &pt_this->t_rect_preview,
                                                 MMP_FP_THUMB_COORDS_CANVAS,
                                                 e_mmp_rotate,
                                                 NULL);
            
        }   
        c_wgl_set_transparent_list(pt_this->h_preview_trans_list,&t_rect_preview,1);
        //MMP_DBG_INFO(("[%s %d] mmp_mc_browse_load_file_thumbnail OUT \r\n",__FUNCTION__,__LINE__));
        //c_wgl_add_transparent_list_exclusion(pt_this->h_preview_trans_list, &t_rect_preview, TRUE);
        c_wgl_enable_transparent_list(pt_this->h_preview_trans_list, TRUE, TRUE);
        c_wgl_repaint(mmp_main_get_canvas(), &pt_this->t_rect_preview, TRUE);       
        pt_this->e_popup_status = MMP_TM_POPUP_STATUS_PREVIEW;
    }
    else
    {
        mmp_pe_gl_dfb_snapshot_load(&t_rect_preview,pt_this->b_preview_rotate?FALSE:TRUE);
        //MMP_DBG_INFO(("[*******mmp](%s) %d  %d\r\n", __FUNCTION__, __LINE__,pt_this->b_preview_rotate));      
        if (pt_this->b_preview_rotate)
        {
            i4_ret = mmp_be_get_item_info(MMP_BE_FF_IDX_CRT,ITEM_TYPE_NONE,
                                          pt_this->ui4_focus_idx,
                                          &ui4_cnt,
                                          &t_item_info);
            if (MMPR_OK == i4_ret)
            {
                MMP_BE_GET_FULL_ITEM_PATH(t_item_info, s_full_path);
                MMP_BE_RC_GET_MMP_ROTATE_FROM_ITEM_FLAG(t_item_info.e_flag, e_mmp_rotate);
                mmp_mc_browse_load_file_thumbnail_ex(s_full_path,
                                                     &t_rect_thumb,
                                                     MMP_FP_THUMB_COORDS_SCREEN,
                                                     e_mmp_rotate,
                                                     NULL);
            }
        }

        pt_this->e_popup_status = MMP_TM_POPUP_STATUS_ON;
    }

    pt_this->b_preview_rotate = FALSE;
    return MMPR_OK;
}


#if 0
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_get_folder_img
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
 INT32 mmp_thumbnailmode_get_folder_img(MMP_TM_MEMBER_T* pt_this, UINT32 ui4_dev_idx, WGL_HIMG_TPL_T* ph_img_tpl)
{
    MMP_BE_STATUS_T             e_be_status = MMP_BE_STATUS_NONE;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status;
    INT32                       i4_ret;

    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_be_status);

    *ph_img_tpl = pt_this->h_thumbnail_folder_img;

    do {
        if (MMP_BE_STATUS_CHOOSE_FF == e_be_status)
        {
            break;
        }
        else
        {
            i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_dev_idx, &e_dev_status);
            if(RMVR_OK != i4_ret)
            {
                break;
            }

#ifdef APP_NET_DLNA_SUPPORT
            if (RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
            {
                *ph_img_tpl = pt_this->h_thumbnail_dlna_folder_img;
                break;
            }
#endif
#ifdef APP_NET_NEIGHBOR_SUPPORT
            if (RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))
            {
                *ph_img_tpl = pt_this->h_thumbnail_mnp_folder_img;
            }
#endif
        }
    } while (0);

    return MMPR_OK;
}

#endif

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_upd_preview_trans_list
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_upd_preview_trans_list(MMP_TM_MEMBER_T* pt_this, UINT8 ui1_idx)
{
    GL_RECT_T           at_rect[3];
    GL_RECT_T           t_rect;
    UINT32              ui4_rect_cnt = 0;
    HANDLE_T            h_skip_icon;

    if (ui1_idx >= MMP_THMBNAILMODE_MAX_THUMBS)
    {
        return MMPR_INV_ARG;
    }

    SET_RECT_BY_SIZE (&at_rect[ui4_rect_cnt],
                      MMP_TM_IMG_PREVIEW_X,
                      MMP_TM_IMG_PREVIEW_Y,
                      MMP_TM_IMG_PREVIEW_W,
                      MMP_TM_IMG_PREVIEW_H);
    ui4_rect_cnt++;

    if (FALSE == pt_this->b_skip_flag[ui1_idx])
    {
        do {
            if (ui1_idx == 3 || ui1_idx == 6)
            {
                break;
            }

            h_skip_icon = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SKIP0 + ui1_idx);
            c_wgl_get_coords(h_skip_icon, WGL_COORDS_SCREEN, &at_rect[ui4_rect_cnt]);

            if (ui1_idx == 0)
            {
                at_rect[ui4_rect_cnt].i4_bottom = MMP_TM_POP_UP_BASE_FRM_Y;
            }

            ui4_rect_cnt++;
        } while (0);

        c_wgl_set_visibility(pt_this->h_pop_up_skip_icon, WGL_SW_HIDE);
        c_wgl_add_transparent_list_exclusion(pt_this->h_preview_trans_list, NULL, 0);
    }
    else
    {
        c_wgl_set_visibility(pt_this->h_pop_up_skip_icon, WGL_SW_NORMAL);
        c_wgl_get_coords(pt_this->h_pop_up_skip_icon, WGL_COORDS_SCREEN, &t_rect);  
        c_wgl_add_transparent_list_exclusion(pt_this->h_preview_trans_list, &t_rect, 1);
    }
    c_wgl_set_transparent_list(pt_this->h_preview_trans_list,
                               at_rect,
                               ui4_rect_cnt);
    return MMPR_OK;
}


/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_view_dev_num_xng_proc
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/

INT32 mmp_thumbnailmode_view_dev_num_xng_proc(MMP_TM_MEMBER_T* pt_this)
{
    INT32               i4_ret = MMPR_OK;

    if (TRUE == pt_this->b_is_dev_list_show)
    {
        /* reset device list */
        i4_ret = mmp_thumbnailmode_optl_show(pt_this, (VOID*)(UINT32)MMP_THUB_OPTL_DEV_LIST);
        IS_MMPR_OK(i4_ret);
        //mmp_thumbnailmode_update_ui(pt_this,MMP_TM_UPDATE_REASON_HIDE_FILE_INFO,TRUE);
        //mmp_thumbnailmode_update_ui(pt_this,MMP_TM_UPDATE_RESAON_PAGE,TRUE);
    }
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_view_dev_remove_proc
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_view_dev_remove_proc(MMP_TM_MEMBER_T* pt_this)
{
    INT32                       i4_ret = MMPR_OK;


    if (TRUE == pt_this->b_is_dev_list_show)
    {
        /* reset device list */
        i4_ret = mmp_thumbnailmode_optl_show(pt_this, (VOID*)(UINT32)MMP_THUB_OPTL_DEV_LIST);
        IS_MMPR_OK(i4_ret);
    }
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_view_dev_mnt_xng_proc
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_view_dev_mnt_xng_proc(MMP_TM_MEMBER_T* pt_this)
{
    INT32               i4_ret = MMPR_OK;
    MMP_TM_UPDATE_REASON_T  e_upd_reason;
    BOOL                        b_is_usb = TRUE;
    HANDLE_T                    h_view_item = NULL_HANDLE;

    pt_this->b_refersh_data_ready = FALSE;
    e_upd_reason = MMP_TM_UPDATE_REASON_HIDE_FILE_INFO;
    i4_ret = mmp_thumbnailmode_update_ui(pt_this, e_upd_reason,TRUE);
    e_upd_reason = MMP_TM_UPDATE_RESAON_PAGE;
    i4_ret = mmp_thumbnailmode_update_ui(pt_this, e_upd_reason,TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_thumbnailmode_view_update_driver_name(FALSE,&b_is_usb);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* If it is the DLNA then set the view as folder */
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

    c_wgl_set_visibility(pt_this->h_frm_thumbnailmode_ui_frm,WGL_SW_HIDE_RECURSIVE);
    c_wgl_repaint(pt_this->h_frm_thumbnailmode_ui_frm,NULL,TRUE);

    a_optl_hide(pt_this->h_option_list);
    pt_this->b_optl_show = FALSE;
    i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT, MMP_BE_REFRESH_TYPE_ITEM_LST);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_thumbnailmode_view_set_path(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_hide_file_info
 * @param
 * @retval  0   The function succeded.
 * @retval  Otherwise   The function failed.
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_hide_file_info()
{
    HANDLE_T        h_info_list=NULL_HANDLE;
    INT32           i4_ret=MMPR_OK;

    h_info_list = mmp_tm_focus_get_wgt_hdl(WID_MMP_TM_FOCUS_LB_FILE);
    i4_ret = c_wgl_do_cmd(h_info_list,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (0, 1),
                        WGL_PACK (NULL));

    i4_ret = c_wgl_do_cmd(h_info_list,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (1, 1),
                        WGL_PACK (NULL));

    i4_ret = c_wgl_do_cmd(h_info_list,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (2, 1),
                        WGL_PACK (NULL));

    c_wgl_repaint(h_info_list,NULL,TRUE);
    return i4_ret;
}




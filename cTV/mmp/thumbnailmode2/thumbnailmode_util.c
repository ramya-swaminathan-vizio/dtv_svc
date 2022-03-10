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
#include "res/app_util/config/a_cfg_custom.h"

#include "mmp/file_operator_list/mmp_file_operator_list.h"
#include "app_util/option_list/a_optl.h"
#ifdef APP_NET_NEIGHBOR_SUPPORT
#include "app_util/pwd_dlg_util/a_pwd_dlg_util.h"
#include "app_util/a_network.h"
#endif
#include "res/app_util/model/model.h"
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


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/*static UTF16_T  ws_g_buf[MMP_TM_MAX_USB_DEV_NUM][MMP_BE_MAX_PATH_LEN + 1] = {0};*/
//static UTF16_T  ws_g_buf[MMP_TM_MAX_USB_DEV_NUM][MMP_BE_MAX_PATH_LEN + 1] = {0};

static MMP_TM_MEMBER_T* pt_g_tm_mbr = NULL;

static UTF16_T w2s_dev_hint[MMP_DEV_LIST_MAX_NUM][MMP_DEV_NAME_MAX_LEN + 1];
static UTF16_T w2s_dev_info[MMP_DEV_LIST_MAX_NUM][MMP_DEV_NAME_MAX_LEN + 1];

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_optl_reset_string(void* pv_param);

#ifdef APP_TTS_SUPPORT
static INT32 _mmp_thumbnailmode_view_optl_back_to_list_tts_play(MMP_TM_MEMBER_T* pt_this);

static INT32 _mmp_thumbnailmode_view_optl_key_input_tts_play(MMP_TM_MEMBER_T* pt_this,UINT32  ui4_key_code);
#endif
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
UINT32 mmp_tm_rand(VOID)
{
    static UINT32 ui4_mul = 97;
    static UINT32 ui4_add = 33;
    static UINT32 ui4_seed = 12345;

    ui4_seed = ui4_seed * ui4_mul + ui4_add;

    return ui4_seed;
}




  /*-----------------------------------------------------------------------------
  * Name:   _mmp_tm_shuffle_set_idx_fct
  *
  * Description:
  *
  * Inputs:
  *
  * Outputs:
  *
  * Returns:
  ----------------------------------------------------------------------------*/
  static INT32 _mmp_tm_shuffle_get_sub_hlt_idx_fct(void* pv_tag, UINT16* pui2_hlt_idx)
  {
    SIZE_T                      z_size;
    MMP_SHUFFLE_MODE_T          e_shuffle_mode;

    z_size = sizeof(MMP_SHUFFLE_MODE_T);
    mmp_mc_list_get_attr(MMP_PL_ATTR_ID_FG_SHUFFLE, &z_size, &e_shuffle_mode);
    switch(e_shuffle_mode)
    {
        case MMP_SHUFFLE_MODE_SEQUENTIAL:
            *pui2_hlt_idx = 0;
            break;
        case MMP_SHUFFLE_MODE_SHUFFLE:
            *pui2_hlt_idx = 1;
            break;
        default:
            break;
    }

    return MMPR_OK;
  }


  /*-----------------------------------------------------------------------------
  * Name: _mmp_tm_settings_action_shuffle
  *
  * Description:
  *
  * Inputs:
  *
  * Outputs:
  *
  * Returns:
  ----------------------------------------------------------------------------*/
 static INT32  _mmp_tm_shuffle_set_sub_hlt_idx_fct(void* pv_tag)
 {
    INT32                    i4_shuffle_idx = (INT32)pv_tag;
    INT32                     i4_ret      = -1;
    MMP_TM_MEMBER_T*         pt_this = pt_g_tm_mbr;
    MMP_PL_ATTR_T            at_attr[1] ;
    MMP_SHUFFLE_MODE_T       crn_shuffle_type;
    UINT8                    ui1_cfg_value = 0;

    //crn_shuffle_type = (MMP_SHUFFLE_MODE_T)pv_tag;
    if(i4_shuffle_idx == 0)
    {
        crn_shuffle_type = MMP_SHUFFLE_MODE_SEQUENTIAL;
    }
    else
    {
        crn_shuffle_type = MMP_SHUFFLE_MODE_SHUFFLE;
    }
    if(pt_this->shuffle_type != crn_shuffle_type)
    {
        pt_this->shuffle_type = crn_shuffle_type;
        at_attr[0].e_id = MMP_PL_ATTR_ID_PHOTO_SHUFFLE;
        at_attr[0].pv_param = (VOID*)crn_shuffle_type;
        i4_ret = mmp_mc_list_set_attr(1,at_attr);

        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_mc_list_set_attr fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        ui1_cfg_value = (UINT8)(UINT32)pv_tag;
        a_cfg_custom_set_photo_setting_shuffle(ui1_cfg_value);
        /*
        if((pt_this->ui4_dir_num+pt_this->ui4_file_num)!=0)
        {
        pt_this->b_refersh_data_ready = FALSE;
    }
        */
    }

    _mmp_thumbnailmode_optl_reset_string((VOID*)MMP_THUB_OPTL_SETTINGS);

    return  MMPR_OK;
 }



 /*-----------------------------------------------------------------------------
 * Name: _mmp_tm_speed_type_get_sub_hlt_idx_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

 static INT32 _mmp_tm_speed_type_get_sub_hlt_idx_fct(VOID * pv_tag, UINT16* pui2_hlt_idx)
 {
    MMP_TM_MEMBER_T*                pt_this = pt_g_tm_mbr;

    *pui2_hlt_idx = pt_this->speed_type;
    return MMPR_OK;
 }

 /*-----------------------------------------------------------------------------
 * Name: _mmp_tm_speed_type_set_idx_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 static INT32 _mmp_tm_speed_type_set_idx_fct(VOID * pv_tag)
 {
    MMP_TM_MEMBER_T*        pt_this = pt_g_tm_mbr;
    UINT32                  crn_speed_type;
    UINT32                  ui4_speed_index = (UINT32)pv_tag;
    UINT32                  ui4_speed_type=MMP_SPEED_TYPE_5SECONDS;
    MMP_PL_ATTR_T           t_attr;
    INT32                   i4_ret      = -1;
    UINT8                   ui1_cfg_value = 0;

     crn_speed_type = (UINT32)pv_tag;
     if(crn_speed_type > MMP_SPEED_TYPE_30SECONDS)
     {
        return MMPR_INV_ARG;
     }
     if(pt_this->speed_type != crn_speed_type)
     {

        MMP_PP_RC_DLB_GET_SPEED(ui4_speed_index, ui4_speed_type);
        pt_this->speed_type = crn_speed_type;
        t_attr.e_id = MMP_PL_ATTR_ID_DURATION;
        t_attr.pv_param = (VOID*)ui4_speed_type;
        i4_ret = mmp_mc_list_set_attr(1, &t_attr);
        IS_MMPR_OK(i4_ret);

        ui1_cfg_value = (UINT8)(UINT32)pv_tag;
        a_cfg_custom_set_photo_setting_speed(ui1_cfg_value);
        /*
        if((pt_this->ui4_dir_num+pt_this->ui4_file_num)!=0)
        {
        pt_this->b_refersh_data_ready = FALSE;
     }
        */
     }

     _mmp_thumbnailmode_optl_reset_string((VOID*)MMP_THUB_OPTL_SETTINGS);

     return MMPR_OK;
 }


 /*-----------------------------------------------------------------------------
 * Name: _mmp_tm_effect_type_get_sub_hlt_idx_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

 static INT32 _mmp_tm_effect_type_get_sub_hlt_idx_fct(VOID * pv_tag, UINT16* pui2_hlt_idx)
 {
    MMP_TM_MEMBER_T*                pt_this = pt_g_tm_mbr;

    *pui2_hlt_idx = (UINT16)pt_this->effect_type;
    return MMPR_OK;
 }

 /*-----------------------------------------------------------------------------
 * Name: _mmp_tm_effect_type_set_idx_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
 static INT32 _mmp_tm_effect_type_set_idx_fct(VOID * pv_tag)
 {
    MMP_TM_MEMBER_T*        pt_this = pt_g_tm_mbr;
    IMG_TFX_EFFECT_T        cover_effect_type;
    MMP_PL_ATTR_T           t_attr;
    MMP_EFFECT_T              effect_item;
    UINT32                   i4_ret,crn_effect_type;
    UINT8                   ui1_cfg_value = 0;

    crn_effect_type = (UINT32)pv_tag;

    if(crn_effect_type >= MMP_EFCT_TYPE_TOTAL_NUM)
    {
        return MMPR_INV_ARG;
    }
    if(pt_this->effect_type != crn_effect_type)
    {
        pt_this->effect_type = crn_effect_type;
        switch((UINT32)pv_tag)
        {
            case 0:
                cover_effect_type = mmp_tm_rand()%7+1;
                break;
            case 1:
                cover_effect_type = TFX_DISSOLVE;
                break;
            case 2:
                cover_effect_type = TFX_WIPE_RIGHT;
                break;
            case 3:
                cover_effect_type = TFX_WIPE_LEFT;
                break;
            case 4:
                cover_effect_type = TFX_WIPE_UP;
                break;
            case 5:
                cover_effect_type = TFX_WIPE_DOWN;
                break;
            case 6:
                cover_effect_type = TFX_BOX_IN;
                break;
            case 7:
                cover_effect_type = TFX_BOX_OUT;
                break;
            default:
                cover_effect_type = TFX_WIPE_LEFT;
                break;
       }
        effect_item.e_effect  = cover_effect_type;
        effect_item.b_is_enabled =TRUE;
        t_attr.e_id = MMP_PL_ATTR_ID_EFFECT;
        t_attr.pv_param = &effect_item;
        i4_ret = mmp_mc_list_set_attr(1, &t_attr);
        IS_MMPR_OK(i4_ret);
        ui1_cfg_value = (UINT8)(UINT32)pv_tag;
        a_cfg_custom_set_photo_setting_effect(ui1_cfg_value);
        /*
        if((pt_this->ui4_dir_num+pt_this->ui4_file_num)!=0)
        {
        pt_this->b_refersh_data_ready = FALSE;
    }
        */
    }

    _mmp_thumbnailmode_optl_reset_string((VOID*)MMP_THUB_OPTL_SETTINGS);

    return  MMPR_OK;
 }

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_tm_sort_set_idx_fct
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_tm_sort_set_idx_fct(VOID* pv_tag)
{
    INT32                     i4_ret = MMPR_OK;
    MMP_TM_MEMBER_T*        pt_this = pt_g_tm_mbr;
    MMP_SORT_TYPE_T         e_old_sort = MMP_SORT_TYPE_NONE;
    MMP_SORT_TYPE_T         e_new_sort = MMP_SORT_TYPE_NONE;
    MMP_MEDIA_TYPE_T        e_media_type;
    UINT32                    ui4_index = (UINT32)pv_tag;
    HANDLE_T                   h_btn_item=NULL_HANDLE;
    UINT8                   ui1_cfg_value = 0;

    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_media_type);

    MMP_TM_RC_GET_SORT_TYPE(e_media_type, ui4_index, e_new_sort);
    /*
    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE,
                    (VOID*)&e_old_sort);
                    */
    a_cfg_get_mmp_photo_sort(&ui1_cfg_value);
    e_old_sort = ui1_cfg_value;

    h_btn_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z);
    i4_ret = c_wgl_do_cmd(h_btn_item,
                         WGL_CMD_BTN_SET_TEXT,
                         WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,(MLM_MMP_KEY_THUBM_SORT__NAME_A_Z+(UINT32)pv_tag))),
                         WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,(MLM_MMP_KEY_THUBM_SORT__NAME_A_Z+(UINT32)pv_tag)))));

    IS_MMPR_OK (a_optl_hide (pt_this->h_option_list));
    pt_this->b_optl_show = FALSE;
    IS_MMPR_OK (c_wgl_set_visibility(pt_this->h_frm_left_ui_frm1,WGL_SW_RECURSIVE));

    if(e_old_sort != e_new_sort)
    {
        IS_MMPR_OK (c_wgl_set_visibility(pt_this->h_info_frm,WGL_SW_HIDE_RECURSIVE));
    }
    else
    {
    IS_MMPR_OK (c_wgl_set_visibility(pt_this->h_info_frm,WGL_SW_RECURSIVE));
    }

    IS_MMPR_OK (c_wgl_repaint(pt_this->h_frm_left_base_frm,NULL,TRUE));

    if(e_old_sort == e_new_sort)
    {
        c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
        return MMPR_OK;
    }

    pt_this->sort_type = e_new_sort;
    mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SORT_TYPE,(VOID*)e_new_sort);
    ui1_cfg_value = (UINT8)e_new_sort;
    a_cfg_set_mmp_photo_sort(ui1_cfg_value);

    if((pt_this->ui4_dir_num+pt_this->ui4_file_num)!=0)
    {
    pt_this->b_refersh_data_ready = FALSE;
    }

    i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT,MMP_BE_REFRESH_TYPE_ITEM_LST);
    IS_MMPR_OK(i4_ret);

    c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
    //IS_MMPR_OK (c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_SYNC_AUTO_REPAINT));
    return  i4_ret;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_tm_view_set_view_mode_fct
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_tm_view_set_view_mode_fct(VOID* pv_tag)
{
    INT32                       i4_ret = -1;
    MMP_TM_MEMBER_T*            pt_this = pt_g_tm_mbr;
    BOOL                        crn_view_mode;
    HANDLE_T                    h_btn_item;

    IS_MMPR_OK (a_optl_hide (pt_this->h_option_list));
    pt_this->b_optl_show = FALSE;
    IS_MMPR_OK(c_wgl_set_visibility(pt_this->h_option_list,WGL_SW_HIDE_RECURSIVE));
    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,(VOID*)&pt_this->b_recursive);
    IS_MMPR_OK(i4_ret);
    crn_view_mode = (((BOOL)(UINT32)pv_tag) == 0) ? TRUE : FALSE;
     if(pt_this->b_recursive != crn_view_mode)
     {
         h_btn_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS);


         i4_ret = c_wgl_do_cmd(h_btn_item,
                              WGL_CMD_BTN_SET_TEXT,
                              WGL_PACK(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,(MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS+(UINT32)pv_tag))),
                              WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,(MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS+(UINT32)pv_tag)))));
        IS_MMPR_OK(i4_ret);
        //c_wgl_set_visibility(h_btn_item,WGL_SW_RECURSIVE);
     }

     IS_MMPR_OK(c_wgl_set_visibility(pt_this->h_frm_left_ui_frm1,WGL_SW_RECURSIVE));
     IS_MMPR_OK (c_wgl_repaint(pt_this->h_frm_left_ui_frm1,NULL,TRUE));
     if((crn_view_mode == pt_this->b_recursive)&&(crn_view_mode == TRUE))
     {
         mmp_thumbnail_display_file_info(pt_this);
     }
     IS_MMPR_OK(c_wgl_set_visibility(pt_this->h_frm_htl_thumbnail_mov_frm,WGL_SW_HIDE));
     IS_MMPR_OK(c_wgl_set_visibility(pt_this->h_frm_htl_folder_mov_frm,WGL_SW_HIDE_RECURSIVE));

    /* Set type info to be */
    if(pt_this->b_recursive != crn_view_mode)
    {
        pt_this->b_recursive = crn_view_mode;
        pt_this->changed_view_mode = ~MMP_FF_SET_PATH_FLAG_EMPTY;
        if((pt_this->ui4_dir_num+pt_this->ui4_file_num)!=0)
        {
        pt_this->b_refersh_data_ready = FALSE;
        }

        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_IS_RECURSIVE,(VOID*)(UINT32)crn_view_mode);
        MMPR_LOG_ON_FAIL(i4_ret);
        a_cfg_custom_set_mmp_photo_recur_parsing((UINT8)crn_view_mode);
        /* change the thumb type */
        i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT, MMP_BE_REFRESH_TYPE_ITEM_LST);
        MMPR_LOG_ON_FAIL(i4_ret);
        c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
    }
    else
    {
         pt_this->changed_view_mode = MMP_FF_SET_PATH_FLAG_EMPTY;
         //IS_MMPR_OK (c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_SYNC_AUTO_REPAINT));
         c_wgl_set_focus(pt_this->h_last_focus_wigt,TRUE);
    }
    return  MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_tm_dev_list_set_fct
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
static INT32 _mmp_tm_dev_list_set_fct(VOID* pv_tag)
{
    INT32               i4_ret = MMPR_OK;
    UINT32              ui4_active_idx;
    SIZE_T              z_size = MMP_TM_VIEW_INFO_STR_MAX_LEN;
    CHAR                s_mnt_name[MMP_TM_VIEW_INFO_STR_MAX_LEN] = {0};
    MMP_TM_MEMBER_T*    pt_this = pt_g_tm_mbr;
    BOOL                b_is_usb = TRUE;
    HANDLE_T            h_view_item = NULL_HANDLE;

    i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_active_idx, &z_size, s_mnt_name);
    IS_MMPR_OK(i4_ret);

    if((UINT32)pv_tag != ui4_active_idx)
    {
        i4_ret = mmp_be_set_info(MMP_BE_INFO_SET_INFO_ID_SET_ACT_MNT_POINT, (VOID*)pv_tag);
        IS_MMPR_OK(i4_ret);
    }

    i4_ret = a_optl_hide(pt_this->h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);
    pt_this->b_optl_show = FALSE;

    i4_ret = mmp_thumbnailmode_view_update_driver_name(FALSE,&b_is_usb);
    IS_MMPR_OK(i4_ret);

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

    i4_ret = mmp_be_refresh(MMP_BE_FF_IDX_CRT, MMP_BE_REFRESH_TYPE_ITEM_LST);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_repaint(pt_this->h_frm_left_ui_frm1, NULL, TRUE);
    IS_MMPR_OK(i4_ret);

    if(pt_this->ui4_dir_num+pt_this->ui4_file_num!=0)
    {
        c_wgl_set_visibility(mmp_mmp_get_wgt_hdl(pt_this->h_info_frm),WGL_SW_RECURSIVE);
    }
    pt_this->b_is_dev_list_show =FALSE;

    i4_ret = c_wgl_set_visibility(pt_this->h_frm_htl_thumbnail_mov_frm, WGL_SW_HIDE);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_frm_htl_folder_mov_frm, WGL_SW_HIDE_RECURSIVE);
    IS_MMPR_OK(i4_ret);

    i4_ret = mmp_thumbnailmode_view_set_path(TRUE);
    IS_MMPR_OK(i4_ret);
    return  MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_tm_optl_timeout_hdlr
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_tm_optl_timeout_hdlr(VOID*      pv_tag1,
                                      VOID*      pv_tag2,
                                      VOID*      pv_tag3,
                                      VOID*      pv_tag4)
{
    MMP_TM_MEMBER_T* pt_this = (MMP_TM_MEMBER_T*)pv_tag1;

    a_optl_hide (pt_this->h_option_list);
    pt_this->b_optl_show = FALSE;

    c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_NO_AUTO_REPAINT);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_tm_optl_msg_proc_fct
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_tm_optl_msg_proc_fct (VOID*    pv_tag,
                                       UINT32   ui4_msg,
                                       VOID*    pv_param1,
                                       VOID*    pv_param2)
{
    HANDLE_T            h_thumb_item;

    MMP_TM_MEMBER_T* pt_this = (MMP_TM_MEMBER_T*)pv_tag;

    if (ui4_msg == OPTL_MSG_CANCELLED)
    {
        /* just hide the option list */
        a_optl_hide(pt_this->h_option_list);
        c_wgl_set_visibility(pt_this->h_option_list,WGL_SW_HIDE_RECURSIVE);
        pt_this->b_optl_show = FALSE;
        if(ITEM_TYPE_DIR == mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,pt_this->ui4_focus_idx))
        {
            c_wgl_set_visibility(pt_this->h_frm_left_base_frm,WGL_SW_NORMAL);
        }
        if(ITEM_TYPE_FILE== mmp_be_get_item_type_by_idx(MMP_BE_FF_IDX_CRT,pt_this->ui4_focus_idx))
        {
            c_wgl_set_visibility(pt_this->h_frm_left_base_frm,WGL_SW_RECURSIVE);
        }
        h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
        c_wgl_set_visibility(h_thumb_item,WGL_SW_RECURSIVE);
        c_wgl_set_visibility(pt_this->h_option_list,WGL_SW_HIDE_RECURSIVE);
        c_wgl_repaint(pt_this->h_frm_left_base_frm,NULL,TRUE);
        c_wgl_set_focus(pt_this->h_last_focus_wigt, WGL_SYNC_AUTO_REPAINT);
    }
    else if (ui4_msg == OPTL_MSG_KEY_INPUT)
    {
    #ifdef APP_TTS_SUPPORT
        UINT32 ui4_key_code = (UINT32)pv_param1;
        _mmp_thumbnailmode_view_optl_key_input_tts_play(pt_this,ui4_key_code);
    #endif

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        {
            UINT32 ui4_key_code = (UINT32)pv_param1;
            INT32 i4_ret;

            i4_ret = mmp_mc_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
            if(MMPR_OK == i4_ret)
            {
                a_optl_hide(pt_this->h_option_list);
                pt_this->b_optl_show = FALSE;
            }
        }
#endif
    }
    else if(OPTL_MSG_HIDE_TIMEOUT == ui4_msg)
    {

        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_tm_optl_timeout_hdlr,
                                    pt_this,
                                    NULL,
                                    NULL,
                                    NULL);

    }
#ifdef APP_TTS_SUPPORT
    else if(OPTL_MSG_ITEM_HIGHLIGHT == ui4_msg)
    {
        _mmp_thumbnailmode_view_optl_back_to_list_tts_play(pt_this);
    }
#endif
}

#ifdef APP_NET_NEIGHBOR_SUPPORT

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_tm_pwd_dlg_timeout_hdlr
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_tm_pwd_dlg_timeout_hdlr(VOID*      pv_tag1,
                                         VOID*      pv_tag2,
                                         VOID*      pv_tag3,
                                         VOID*      pv_tag4)
{
    MMP_TM_MEMBER_T* pt_this = (MMP_TM_MEMBER_T*)pv_tag1;

    a_pwd_dlg_hide (pt_this->h_pwd_dlg);

    c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_NO_AUTO_REPAINT);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_tm_pwd_dlg_proc_fct
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_tm_pwd_dlg_proc_fct(VOID*    pv_tag,
                                     UINT32   ui4_msg,
                                     VOID*    pv_param1,
                                     VOID*    pv_param2)
{
    MMP_TM_MEMBER_T*    pt_this;
    HANDLE_T            h_pwd_dlg_handle = NULL_HANDLE;
    UTF16_T             w2s_user_name[MMP_BE_MAX_USR_LEN] = {0};
    UTF16_T             w2s_pass_word[MMP_BE_MAX_PWD_LEN] = {0};
    CHAR                s_user_name[MMP_BE_MAX_USR_LEN] = {0};
    CHAR                s_pass_word[MMP_BE_MAX_PWD_LEN] = {0};
    CHAR                s_next_path[MMP_BE_MAX_PATH_LEN] = {0};
    INT32               i4_ret = MMPR_OK;

    if (NULL == pv_tag)
    {
        return;
    }
    pt_this = (MMP_TM_MEMBER_T*)pv_tag;
    h_pwd_dlg_handle = pt_this->h_pwd_dlg;

    if (ui4_msg == PWD_DLG_MSG_CANCELED)
    {
        /* just hide the pwd dlg  and set focus to main frame     */
        i4_ret = a_pwd_dlg_hide(h_pwd_dlg_handle);
        if(i4_ret != PWD_DLG_OK)
        {
            DBG_LOG_PRINT(("a_pwd_dlg_hide return error =%d,function%s,line=%d",i4_ret,__FUNCTION__,__LINE__));
        }

        c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_NO_AUTO_REPAINT);

    }
    else if(PWD_DLG_MSG_HIDE_TIMEOUT == ui4_msg)
    {
         mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                     _mmp_tm_pwd_dlg_timeout_hdlr,
                                     pt_this,
                                     NULL,
                                     NULL,
                                     NULL);
    }
    else if(PWD_DLG_MSG_CHANGE_ACTIVE == ui4_msg)
    {
          /* Change Active to Usrname or Password */
    }
    else if(PWD_DLG_MSG_FINISHED == ui4_msg)
    {
        MMP_BE_STATUS_T             e_status = MMP_BE_STATUS_NONE;
        SIZE_T                      z_size = MMP_BE_MAX_PATH_LEN;

        /* [Notice] You need to call a_pwd_dlg_get_text function to get
                                               UserName & Password and check valid*/
        do
        {
            /* 1.  Get the user name and password from pwd dialog */
            i4_ret = a_pwd_dlg_get_text(h_pwd_dlg_handle,
                                       ACTIVE_ON_USR,
                                       w2s_user_name);
            if(i4_ret != PWD_DLG_OK)
            {
                DBG_LOG_PRINT(("a_pwd_dlg_get_text return error =%d,function%s,line=%d \n",i4_ret,__FUNCTION__,__LINE__));
                break;
            }

            i4_ret = a_pwd_dlg_get_text(h_pwd_dlg_handle,
                                       ACTIVE_ON_PWD,
                                       w2s_pass_word);
            if(i4_ret != PWD_DLG_OK)
            {
                DBG_LOG_PRINT(("a_pwd_dlg_get_text return error =%d,function%s,line=%d \n",i4_ret,__FUNCTION__,__LINE__));
                break;
            }

            /* 2.  Get the user name and password from MW  */
            i4_ret = c_uc_w2s_to_ps(w2s_user_name,s_user_name,MMP_BE_MAX_USR_LEN);
            if(i4_ret != MMPR_OK)
            {
                DBG_LOG_PRINT(("c_uc_w2s_to_ps w2s_user_name return error =%d,function%s,line=%d \n",i4_ret,__FUNCTION__,__LINE__));
            }
            i4_ret = c_uc_w2s_to_ps(w2s_pass_word,s_pass_word,MMP_BE_MAX_PWD_LEN);
            if(i4_ret != MMPR_OK)
            {
                DBG_LOG_PRINT(("c_uc_w2s_to_ps w2s_pass_word return error =%d,function%s,line=%d \n",i4_ret,__FUNCTION__,__LINE__));
            }


            /* Check if root dir is empty for specified filter */
            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);
            switch(e_status)
            {
                case MMP_BE_STATUS_CHOOSE_MNT :
                {
                    mmp_be_get_curr_path(s_next_path, &z_size);
                    break;
                }
                case MMP_BE_STATUS_NORMAL:
                default :
                {
                    mmp_be_get_focus_path(s_next_path,&z_size);
                    break;
                }
            }

            MMP_DBG_INFO(("s_next_path =%s, line=%d \n", s_next_path, __LINE__));
            MMP_DBG_INFO(("s_user_name =%s, line=%d \n", s_user_name, __LINE__));
            MMP_DBG_INFO(("s_pass_word =%s, line=%d \n", s_pass_word, __LINE__));


            i4_ret = a_nw_my_net_pls_set_perm(s_next_path,
                                             s_user_name,
                                             s_pass_word);
            if(i4_ret != MMPR_OK)
            {
                DBG_LOG_PRINT(("a_nw_my_net_pls_set_perm return error =%d,function%s,line=%d \n",i4_ret,__FUNCTION__,__LINE__));
            }

        }
        while(0);

        /* 3.   Check the user name and password */
        if(i4_ret != MMPR_OK)
        {
            /* Clear last text .*/
            a_pwd_dlg_set_text(pt_this->h_pwd_dlg,ACTIVE_ON_USR,NULL);
            a_pwd_dlg_set_text(pt_this->h_pwd_dlg,ACTIVE_ON_PWD,NULL);

            /* show pwd dialog again  */
            a_pwd_dlg_show(pt_this->h_pwd_dlg);
        }
        else
        {
            /*  check pass */
            i4_ret = mmp_be_auth_touch_folder(pt_this->ui4_focus_idx);
            if(MMPR_OK == i4_ret)
            {
                /*Hide pwd dialog */
                a_pwd_dlg_hide(pt_this->h_pwd_dlg);

                /* set focus to main frame , while hide the pwd dlg  */
                c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_NO_AUTO_REPAINT);

                /* change to child folder */
                mmp_be_cd_child(pt_this->ui4_focus_idx);

            }
            else if(MMPR_DIR_AUTH_FAIL == i4_ret)
            {
                /*  check failed, hide pwd dlg */
                a_pwd_dlg_hide(pt_this->h_pwd_dlg);

                /* set focus to main frame , while hide the pwd dlg  */
                c_wgl_set_focus(pt_this->h_frm_right_base_frm, WGL_NO_AUTO_REPAINT);

                /*  show the pwd error message */
                mmp_thumbnailmode_show_warning_msg(pt_this, MMP_TM_VIEW_WARN_MSG_PWD_ERROR, TRUE, TRUE);

                /*a_pwd_dlg_show(pt_this->h_pwd_dlg);                               */
                DBG_LOG_PRINT(("\n>>>>>>>> usr name or password is error! <<<<<<<<<%d,%s,%d\n\n",i4_ret,__FUNCTION__,__LINE__));
            }
            else
            {
                /* error  */
                DBG_LOG_PRINT(("mmp_be_auth_touch_folder return %d,%s,%d\n",i4_ret,__FUNCTION__,__LINE__));
            }
        }
    }
}
#endif

/*----------------------------------------------------------------------------
 * Name: _mmp_tm_set_dev_list_item
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
static INT32 _mmp_tm_set_dev_list_item(OPTL_ITEM_T* pt_optl_item, UINT32* pui4_cnt)
{
    INT32           i4_ret = MMPR_OK;
    UINT32          ui4_mnt_count = 0;
    UINT32          ui4_idx = 0;
    UINT32          ui4_cnt = 0;
    UINT32          ui4_usb_id = 0;
    UINT32          ui4_dlna_id = 0;
    OPTL_ITEM_T     t_optl_item[MMP_DEV_LIST_MAX_NUM];
    RMV_DEV_DEVICE_STATUS_T  e_dev_status;
    BOOL            b_next = FALSE;
    CHAR            s_mnt_name[128 + 1] = {0};
    SIZE_T          z_size = 0;

    c_memset(w2s_dev_hint,0,sizeof(w2s_dev_hint));
    c_memset(w2s_dev_info,0,sizeof(w2s_dev_info));
    c_memset(t_optl_item,0,sizeof(t_optl_item));

    i4_ret = mmp_mc_device_get_mnt_count(&ui4_mnt_count);
    IS_MMPR_OK(i4_ret);

    for (ui4_idx = 0, ui4_cnt = 0;
         (ui4_idx<ui4_mnt_count) && (ui4_idx<MMP_DEV_LIST_MAX_NUM);
         ui4_idx++)
    {
        i4_ret = mmp_be_get_device_info(ui4_idx,
                                        w2s_dev_info[ui4_cnt],
                                        &e_dev_status,
                                        &b_next);
        if (MMPR_OK != i4_ret)
        {
            continue;
        }

        if (b_next)
        {
            continue;
        }

        if (RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            if (FALSE == a_is_DLNA_enable())
            {
                continue;
            }

            z_size = 128;
            i4_ret = a_rmv_dev_get_mnt_point_info(
                                    ui4_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)s_mnt_name);
            MMPR_LOG_ON_FAIL(i4_ret);

            if (0 == c_strcmp(s_mnt_name, "MediaTek DMR"))
            {
                DBG_LOG_PRINT(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                             __FILE__, __FUNCTION__, __LINE__));
                continue;
            }

            ui4_dlna_id++;

            i4_ret = mmp_be_get_dlna_serial_name(ui4_dlna_id,
                                                 w2s_dev_hint[ui4_cnt]);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        else if(!(RMV_DEV_DEVICE_STATUS_UNSUPT_DEV & e_dev_status))
        {
            ui4_usb_id++;

            i4_ret = mmp_be_get_usb_serial_name(ui4_usb_id,
                                                w2s_dev_hint[ui4_cnt]);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        t_optl_item[ui4_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        t_optl_item[ui4_cnt].pw2s_text = w2s_dev_info[ui4_cnt];
        t_optl_item[ui4_cnt].pw2s_label = w2s_dev_hint[ui4_cnt];
        t_optl_item[ui4_cnt].b_is_disable = FALSE;
        t_optl_item[ui4_cnt].u.t_action.pv_tag = (VOID*)ui4_usb_id;
        t_optl_item[ui4_cnt].u.t_action.pf_fct = _mmp_tm_dev_list_set_fct;
        ui4_cnt += 1;
    }

    *pui4_cnt = ui4_cnt;
    c_memcpy(pt_optl_item, t_optl_item, (sizeof(OPTL_ITEM_T)*ui4_cnt));
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_optl_show
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_thumbnailmode_optl_reset_string(void* pv_param)
{
    OPTL_ITEM_DEF_T             t_optl_item_def = {0};
    OPTL_ITEM_T                  t_optl_item[MMP_TM_UI_OPTL_MAIN_ITEM_MAX_NUM];
    OPTL_SUBITEM_T              t_sub_item_sort[4];
    OPTL_SUBITEM_T              t_sub_item_speed_type[MMP_TM_UI_OPTL_SPEED_TYPE_NUM];
    OPTL_SUBITEM_T              t_sub_item_shuffle[MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM];
    OPTL_SUBITEM_T              t_sub_item_effect_type[MMP_TM_UI_OPTL_EFFECT_TYPE_NUM];
    UINT8                        ui1_index;
    UINT8                        ui1_cnt = 0;
    MMP_BE_FILE_SRC_TYPE_T     e_src_type;
    CHAR                          s_curr_path[MMP_BE_MAX_PATH_LEN]={0};
    MMP_MEDIA_TYPE_T            e_type;
    SIZE_T                       z_size = MMP_BE_MAX_PATH_LEN;
    MMP_BE_STATUS_T             e_status;
    BOOL                         b_is_recursive_parsing = FALSE;
    UINT16                       ui2_hlt_idx = 0;
    MMP_SORT_TYPE_T             e_sort_type, e_crnt_sort;
    UINT8                       ui1_cfg_value=0;
    MMP_TM_MEMBER_T*            pt_this = pt_g_tm_mbr;


    c_memset(&t_optl_item,0,MMP_TM_UI_OPTL_MAIN_ITEM_MAX_NUM*sizeof(OPTL_ITEM_T));
    c_memset(&t_sub_item_sort,0,4*sizeof(OPTL_SUBITEM_T));
    c_memset(&t_sub_item_speed_type,0,MMP_TM_UI_OPTL_SPEED_TYPE_NUM*sizeof(OPTL_SUBITEM_T));
    c_memset(&t_sub_item_effect_type,0,MMP_TM_UI_OPTL_EFFECT_TYPE_NUM*sizeof(OPTL_SUBITEM_T));
    c_memset(&t_sub_item_shuffle,0,MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM*sizeof(OPTL_SUBITEM_T));


    // Fix coverity-4490223: Unchecked return value
    if( mmp_be_get_curr_path(s_curr_path, &z_size) != MMPR_OK )
    {
        DBG_LOG_PRINT(("[MMP]{Error at %s: %s: %d}\n", __FILE__, __FUNCTION__,__LINE__));
    }

    mmp_be_get_file_src_type(s_curr_path, &e_src_type);
    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);
    mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,(VOID*)&b_is_recursive_parsing);

    if(((MMP_BE_FILE_SRC_DLNA == e_src_type ) ||(MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
        &&((OPTION_KINDS)pv_param !=MMP_THUB_OPTL_SETTINGS))
    {
        /*  don't show the sort type in listmode optl */
    }
    else
    {
        /* Get focus index according to filter type*/
        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_type);

        switch ((OPTION_KINDS)pv_param)
        {
            case MMP_THUB_OPTL_SORT:
            {
                mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE, (VOID*)&e_crnt_sort);

                for(ui1_cnt=0;ui1_cnt<MMP_TM_UI_OPTL_PH_SORT_NUM;ui1_cnt++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SORT__NAME_A_Z + ui1_cnt);
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_cnt;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_tm_sort_set_idx_fct;

                    /*Get highlight index*/
                    MMP_TM_RC_GET_SORT_TYPE(e_type, ui1_cnt, e_sort_type);
                    if (e_sort_type == e_crnt_sort)
                    {
                        ui2_hlt_idx = ui1_cnt;
                        DBG_INFO(("ui2_hlt_idx=%d\n", (int)ui2_hlt_idx));
                    }
                }
                t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_SORT);
             }
            break;

            case MMP_THUB_OPTL_VIEW:
            {
                for(ui1_cnt=0;ui1_cnt<MMP_TM_UI_OPTL_PH_VIEW_NUM;ui1_cnt++)
                {
                /*view type for  selecting  */
                t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS +ui1_cnt);
                t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_cnt;
                t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_tm_view_set_view_mode_fct;
                }
                t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_VIEW);
            }
            break;

           /*settings  type for  selecting  */
            case MMP_THUB_OPTL_SETTINGS:
            {
                ui1_cnt = 0;

                /*set shuffle info*/
                ui1_cfg_value = 0;
                a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);

                for(ui1_index=0;ui1_index<MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM;ui1_index++)
                {
                    t_sub_item_shuffle[ui1_index].pf_fct = _mmp_tm_shuffle_set_sub_hlt_idx_fct;
                    t_sub_item_shuffle[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
                    t_sub_item_shuffle[ui1_index].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + ui1_index);
                }
                t_optl_item[ui1_cnt].e_type  = OPTL_ITEM_TYPE_SUBLIST;
                t_optl_item[ui1_cnt].u.t_subopt_list.pw2s_title =  MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SHUFFLE);
                t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM;
                t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_shuffle;
                t_optl_item[ui1_cnt].pw2s_text= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + (UINT32)ui1_cfg_value);
                t_optl_item[ui1_cnt].pw2s_label= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_SHUFFLE_LABEL);
                t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_tm_shuffle_get_sub_hlt_idx_fct;
                //t_optl_item[ui1_cnt].b_is_disable = FALSE;
                ui1_cnt++;



                /*set speed type*/
                ui1_cfg_value = 0;
                a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);

                for(ui1_index=0;ui1_index<MMP_TM_UI_OPTL_SPEED_TYPE_NUM;ui1_index++)
                {
                    t_sub_item_speed_type[ui1_index].pf_fct = _mmp_tm_speed_type_set_idx_fct;
                    t_sub_item_speed_type[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
                    t_sub_item_speed_type[ui1_index].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS +ui1_index);
                }
                t_optl_item[ui1_cnt].e_type  = OPTL_ITEM_TYPE_SUBLIST;
                t_optl_item[ui1_cnt].u.t_subopt_list.pw2s_title =  MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_SPEED);
                t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = MMP_TM_UI_OPTL_SPEED_TYPE_NUM;
                t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_speed_type;
                t_optl_item[ui1_cnt].pw2s_text= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS + (UINT32)ui1_cfg_value);
                t_optl_item[ui1_cnt].pw2s_label= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_SET_BTN_SPEED);
                t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_tm_speed_type_get_sub_hlt_idx_fct;
                ui1_cnt++;

                /*set effect type*/
                ui1_cfg_value = 0;
                a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);

                 for(ui1_index=0;ui1_index<MMP_TM_UI_OPTL_EFFECT_TYPE_NUM;ui1_index++)
                {
                    t_sub_item_effect_type[ui1_index].pf_fct = _mmp_tm_effect_type_set_idx_fct;
                    t_sub_item_effect_type[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
                    t_sub_item_effect_type[ui1_index].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM +ui1_index);
                }

                t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
                t_optl_item[ui1_cnt].u.t_subopt_list.pw2s_title =  MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_EFFECT);
                t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = MMP_TM_UI_OPTL_EFFECT_TYPE_NUM;
                t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_effect_type;
                t_optl_item[ui1_cnt].pw2s_text= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM + (UINT32)ui1_cfg_value);
                t_optl_item[ui1_cnt].pw2s_label= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SHUFFLE + ui1_cnt);
                t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_tm_effect_type_get_sub_hlt_idx_fct;
                t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_BTN_SETTINGS);
                ui1_cnt++;
            }
                break;
            case MMP_THUB_OPTL_DEV_LIST:
                break;
            default:
                break;
        }

    }


    /* memory check */
    MMP_ASSERT(ui1_cnt < MMP_TM_UI_OPTL_MAIN_ITEM_MAX_NUM);
    /*main item number is  ui1_cnt   */
    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui1_cnt;
    IS_MMPR_OK (a_optl_set_main_list_text(pt_this->h_option_list,
                 &t_optl_item_def));

    return MMPR_OK;
}

#ifdef APP_TTS_SUPPORT

/*----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_view_optl_back_to_list_tts_play
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
static INT32 _mmp_thumbnailmode_view_optl_back_to_list_tts_play(MMP_TM_MEMBER_T* pt_this)
{
    INT32                   i4_ret = MMPR_OK;
    UTF16_T                 w2s_str[128] = {0};
    UINT16                  ui2_hlt_idx = 0;
    UINT16                  ui2_sub_idx = 0;

    i4_ret = a_optl_get_hlt_index(pt_this->h_option_list,
                                      &ui2_hlt_idx,
                                      &ui2_sub_idx);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(pt_this->h_last_focus_wigt == mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_NAME_A_Z))
    {
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SORT__NAME_A_Z + ui2_hlt_idx));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    else if(pt_this->h_last_focus_wigt == mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILS))
    {
        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS + ui2_hlt_idx));
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    else if(pt_this->h_last_focus_wigt == mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SETTINGS))
    {
        UINT8 ui1_cfg_value = 0;

        if(ui2_hlt_idx == 0) /* Shuffle */
        {
            a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);
            c_memset(w2s_str, 0, sizeof(w2s_str));
            if((INT16)ui2_sub_idx > -1) /* OPTL_ITEM_TYPE_SUBLIST */
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + ui2_sub_idx));
            }
            else  /* OPTL_ITEM_TYPE_ACTION */
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_SHUFFLE));
                c_uc_w2s_strcat(w2s_str,MMP_TTS_TEXT(
                                MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + (UINT32)ui1_cfg_value));
            }
        }
        else if(ui2_hlt_idx == 1)/* Speed */
        {
            a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);
            c_memset(w2s_str, 0, sizeof(w2s_str));
            if((INT16)ui2_sub_idx > -1) /* OPTL_ITEM_TYPE_SUBLIST */
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                            MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS + ui2_sub_idx));
            }
            else  /* OPTL_ITEM_TYPE_ACTION */
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_SPEED));
                c_uc_w2s_strcat(w2s_str,MMP_TTS_TEXT(
                                MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS + (UINT32)ui1_cfg_value));
            }
        }
        else if(ui2_hlt_idx == 2)/* Effect */
        {
            a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);
            c_memset(w2s_str, 0, sizeof(w2s_str));
            if((INT16)ui2_sub_idx > -1) /* OPTL_ITEM_TYPE_SUBLIST */
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                            MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM + ui2_sub_idx));
            }
            else  /* OPTL_ITEM_TYPE_ACTION */
            {
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_EFFECT));
                c_uc_w2s_strcat(w2s_str,MMP_TTS_TEXT(
                                MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM + (UINT32)ui1_cfg_value));
            }
        }
        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        return MMPR_OK;
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_thumbnailmode_view_optl_key_input_tts_play
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
static INT32 _mmp_thumbnailmode_view_optl_key_input_tts_play(MMP_TM_MEMBER_T* pt_this,
                                                                UINT32  ui4_key_code)
{
    INT32                   i4_ret = MMPR_OK;
    UTF16_T                 w2s_str[128] = {0};
    UINT16                  ui2_hlt_idx = 0;
    UINT16                  ui2_sub_idx = 0;

    i4_ret = a_optl_get_hlt_index(pt_this->h_option_list,
                                      &ui2_hlt_idx,
                                      &ui2_sub_idx);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch(ui4_key_code)
    {
        case BTN_RETURN:
        {
            /* back btn*/
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

            /* MMP_TTS_TEXT set lang id = 0; reset mmp text buffer to currt lang id ,fix DTV00811927 case1 */
            c_memset(w2s_str, 0, sizeof(w2s_str));
            c_uc_w2s_strcpy(w2s_str,MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_TTS_BACK));
            break;
        }
        case BTN_CURSOR_DOWN:
        case BTN_CURSOR_UP:
        {
            if(BTN_CURSOR_DOWN == ui4_key_code)
            {
                ui2_hlt_idx += 1;
            }
            else if(BTN_CURSOR_UP == ui4_key_code)
            {
                ui2_hlt_idx -= 1;
                if(((INT16)ui2_hlt_idx < 0) &&
                    ((INT16)ui2_sub_idx == -1))
                {
                    /* back btn*/
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

                    /* MMP_TTS_TEXT set lang id = 0; reset mmp text buffer to currt lang id ,fix DTV00811927 case1 */
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    c_uc_w2s_strcpy(w2s_str,MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_TTS_BACK));
                    return MMPR_OK;
                }
            }
            switch(pt_this->ui2_optl_item)
            {
                case MMP_TM_VIEW_OPTL_SORT:
                {
                    if(ui2_hlt_idx > (MMP_TM_UI_OPTL_PH_SORT_NUM - 1))
                    {
                        break;
                    }
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                                                        MLM_MMP_KEY_THUBM_SORT__NAME_A_Z + ui2_hlt_idx));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    break;
                }
                case MMP_TM_VIEW_OPTL_VIEW:
                {
                    if(ui2_hlt_idx > (MMP_TM_UI_OPTL_PH_VIEW_NUM - 1))
                    {
                        break;
                    }
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                                                        MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS + ui2_hlt_idx));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    break;
                }
                case MMP_TM_VIEW_OPTL_SETTINGS:
                {
                    UINT8 ui1_cfg_value = 0;

                    /* OPTL_ITEM_TYPE_SUBLIST */
                    if((INT16)ui2_sub_idx > -1)
                    {
                        if(BTN_CURSOR_DOWN == ui4_key_code)
                        {
                            ui2_hlt_idx -= 1;
                            ui2_sub_idx += 1;
                        }
                        else if(BTN_CURSOR_UP == ui4_key_code)
                        {
                            ui2_hlt_idx += 1;
                            ui2_sub_idx -= 1;
                            if((INT16)ui2_sub_idx < 0)
                            {
                                /* back btn*/
                                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_BACK));
                                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));

                                /* MMP_TTS_TEXT set lang id = 0; reset mmp text buffer to currt lang id ,fix DTV00811927 case1 */
                                c_memset(w2s_str, 0, sizeof(w2s_str));
                                c_uc_w2s_strcpy(w2s_str,MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_TTS_BACK));
                                return MMPR_OK;
                            }
                        }

                        if(ui2_hlt_idx == 0) /* Shuffle */
                        {
                            if(ui2_sub_idx > (MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM - 1))
                            {
                                break;
                            }
                            c_memset(w2s_str, 0, sizeof(w2s_str));
                            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                                                MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + ui2_sub_idx));
                        }
                        else if(ui2_hlt_idx == 1) /* Speed */
                        {
                            if(ui2_sub_idx > (MMP_TM_UI_OPTL_SPEED_TYPE_NUM - 1))
                            {
                                break;
                            }
                            c_memset(w2s_str, 0, sizeof(w2s_str));
                            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                                                MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS + ui2_sub_idx));
                        }
                        else if(ui2_hlt_idx == 2) /* Effect */
                        {
                            if(ui2_sub_idx > (MMP_TM_UI_OPTL_EFFECT_TYPE_NUM - 1))
                            {
                                break;
                            }
                            c_memset(w2s_str, 0, sizeof(w2s_str));
                            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                                                    MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM + ui2_sub_idx));
                        }
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                        return MMPR_OK;
                    }
                    /* OPTL_ITEM_TYPE_ACTION */
                    if(ui2_hlt_idx == 0) /* Shuffle */
                    {
                        a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);
                        c_memset(w2s_str, 0, sizeof(w2s_str));
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_SHUFFLE));
                        c_uc_w2s_strcat(w2s_str,MMP_TTS_TEXT(
                                            MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + (UINT32)ui1_cfg_value));
                    }
                    else if(ui2_hlt_idx == 1)/* Speed */
                    {
                        a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);
                        c_memset(w2s_str, 0, sizeof(w2s_str));
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_SPEED));
                        c_uc_w2s_strcat(w2s_str,MMP_TTS_TEXT(
                                            MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS + (UINT32)ui1_cfg_value));
                    }
                    else if(ui2_hlt_idx == 2)/* Effect */
                    {
                        a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);
                        c_memset(w2s_str, 0, sizeof(w2s_str));
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_EFFECT));
                        c_uc_w2s_strcat(w2s_str,MMP_TTS_TEXT(
                                                MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM + (UINT32)ui1_cfg_value));
                    }
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    break;
                }
                default:
                    return MMPR_OK;
            }
            break;
        }
        default:
            return MMPR_OK;
    }

    return MMPR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_optl_create
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_optl_create(MMP_TM_MEMBER_T* pt_this)
{
    OPTL_INIT_T     t_optl_init = {0};
    INT32           i4_ret = -1;

    do
    {
        /* Create option list widget */
        t_optl_init.h_parent = pt_this->h_frm_left_base_frm;
        t_optl_init.t_gui_rc.i4_left = OPTION_MENU_LEFT;
        t_optl_init.t_gui_rc.i4_top  = OPTION_MENU_TOP;
        t_optl_init.ui4_style_mask   = OPTL_STYLE_MASK_NORMAL;
        t_optl_init.pv_tag = pt_this;
        t_optl_init.pf_fct = _mmp_tm_optl_msg_proc_fct;
        t_optl_init.ui4_custom_flag  = 0;
        t_optl_init.ui4_sleep_time   = MMP_BE_TIMER_OPTION_LIST;

        i4_ret = a_optl_create(&t_optl_init,&pt_this->h_option_list);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        //i4_ret = a_optl_set_float_widget(pt_this->h_option_list,TRUE);
        i4_ret = c_wgl_insert (pt_this->h_option_list,
                           pt_this->h_frm_left_ui_frm1,
                           WGL_INSERT_AFTER,
                           WGL_NO_AUTO_REPAINT);

        if (MMPR_OK != i4_ret)
        {
            break;
        }

        pt_g_tm_mbr = pt_this;

        return MMPR_OK;
    }
    while(0);
    a_optl_destroy(pt_this->h_option_list);
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_optl_destroy
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_optl_destroy(MMP_TM_MEMBER_T* pt_this)
{
    return a_optl_destroy(pt_this->h_option_list);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_optl_show
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_optl_show(MMP_TM_MEMBER_T* pt_this, void* pv_param)
{
    INT32                       i4_ret = MMPR_OK;
    OPTL_ITEM_DEF_T             t_optl_item_def = {0};
    OPTL_ITEM_T                  t_optl_item[MMP_DEV_LIST_MAX_NUM];
    OPTL_SUBITEM_T              t_sub_item_sort[4];
    OPTL_SUBITEM_T              t_sub_item_speed_type[MMP_TM_UI_OPTL_SPEED_TYPE_NUM];
    OPTL_SUBITEM_T              t_sub_item_shuffle[MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM];
    OPTL_SUBITEM_T              t_sub_item_effect_type[MMP_TM_UI_OPTL_EFFECT_TYPE_NUM];
    UINT8                       ui1_index;
    UINT8                       ui1_cnt = 0;
    UINT32                      ui4_cnt;
    MMP_BE_FILE_SRC_TYPE_T      e_src_type;
    CHAR                        s_curr_path[MMP_BE_MAX_PATH_LEN]={0};
    MMP_MEDIA_TYPE_T            e_type;
    SIZE_T                      z_size = MMP_BE_MAX_PATH_LEN;
    MMP_BE_STATUS_T             e_status;
    BOOL                        b_is_recursive_parsing = FALSE;
    UINT16                      ui2_hlt_idx = 0;
    MMP_SORT_TYPE_T             e_sort_type, e_crnt_sort;
    UINT8                       ui1_cfg_value = 0;
    HANDLE_T                    h_handle = NULL_HANDLE;

#ifdef APP_TTS_SUPPORT
    UTF16_T                     w2s_str[128] = {0};
#endif

    c_memset(&t_optl_item,0,MMP_DEV_LIST_MAX_NUM*sizeof(OPTL_ITEM_T));
    c_memset(&t_sub_item_sort,0,4*sizeof(OPTL_SUBITEM_T));
    c_memset(&t_sub_item_speed_type,0,MMP_TM_UI_OPTL_SPEED_TYPE_NUM*sizeof(OPTL_SUBITEM_T));
    c_memset(&t_sub_item_effect_type,0,MMP_TM_UI_OPTL_EFFECT_TYPE_NUM*sizeof(OPTL_SUBITEM_T));
    c_memset(&t_sub_item_shuffle,0,MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM*sizeof(OPTL_SUBITEM_T));

    if (MMP_THUB_OPTL_DEV_LIST == (OPTION_KINDS)pv_param)
    {
        i4_ret = _mmp_tm_set_dev_list_item(t_optl_item, &ui4_cnt);
        ui1_cnt =(UINT8)ui4_cnt;
        IS_MMPR_OK(i4_ret);
        ui1_cnt =(UINT8)ui4_cnt;
        pt_this->b_is_dev_list_show =TRUE;
        t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_LB_SOURCE);
    }

    i4_ret = mmp_be_get_curr_path(s_curr_path, &z_size);
    i4_ret = mmp_be_get_file_src_type(s_curr_path, &e_src_type);
    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);
    i4_ret = mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_IS_RECURSIVE,(VOID*)&b_is_recursive_parsing);

    if(((MMP_BE_FILE_SRC_DLNA == e_src_type)||(MMP_BE_FILE_SRC_NET_NEIGHBOR == e_src_type ))
       &&((OPTION_KINDS)pv_param !=MMP_THUB_OPTL_SETTINGS))
    {
        /*  don't show the sort type in thumbnailmode optl */
    }
    else
    {
        /* Get focus index according to filter type*/
        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_type);

        switch ((OPTION_KINDS)pv_param)
        {
            case MMP_THUB_OPTL_SORT:
            {
                mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_SORT_TYPE, (VOID*)&e_crnt_sort);

                for(ui1_cnt=0;ui1_cnt<MMP_TM_UI_OPTL_PH_SORT_NUM;ui1_cnt++)
                {
                    /*sort type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SORT__NAME_A_Z + ui1_cnt);
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_cnt;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_tm_sort_set_idx_fct;

                    /*Get highlight index*/
                    MMP_TM_RC_GET_SORT_TYPE(e_type, ui1_cnt, e_sort_type);
                    if (e_sort_type == e_crnt_sort)
                    {
                        ui2_hlt_idx = ui1_cnt;

                    #ifdef APP_TTS_SUPPORT
                        c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(
                                                MLM_MMP_KEY_THUBM_SORT__NAME_A_Z + ui2_hlt_idx));
                        a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                    #endif
                    }
                }
                t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_SORT);
             }
            break;

            case MMP_THUB_OPTL_VIEW:
            {
                for(ui1_cnt=0;ui1_cnt<MMP_TM_UI_OPTL_PH_VIEW_NUM;ui1_cnt++)
                {
                    /*view type for  selecting  */
                    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
                    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS +ui1_cnt);
                    t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)ui1_cnt;;
                    t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_tm_view_set_view_mode_fct;
                }

                if (pt_this->b_recursive)
                {
                    ui2_hlt_idx = 0;
                }
                else
                {
                    ui2_hlt_idx = 1;
                }

            #ifdef APP_TTS_SUPPORT
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_VIEW_BTN_THUMBNAILS + ui2_hlt_idx));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
            #endif

                t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_VIEW);
            }
            break;

           /*settings  type for  selecting  */
            case MMP_THUB_OPTL_SETTINGS:
            {
                ui1_cnt = 0;

                /*set shuffle info*/
                ui1_cfg_value = 0;
                a_cfg_custom_get_photo_setting_shuffle(&ui1_cfg_value);

             #ifdef APP_TTS_SUPPORT
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_THUBM_SET_BTN_SHUFFLE));
                c_uc_w2s_strcat(w2s_str,MMP_TTS_TEXT(
                                        MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + (UINT32)ui1_cfg_value));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
             #endif

                for(ui1_index=0;ui1_index<MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM;ui1_index++)
                {
                    t_sub_item_shuffle[ui1_index].pf_fct = _mmp_tm_shuffle_set_sub_hlt_idx_fct;
                    t_sub_item_shuffle[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
                    t_sub_item_shuffle[ui1_index].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + ui1_index);
                }
                t_optl_item[ui1_cnt].e_type  = OPTL_ITEM_TYPE_SUBLIST;
                t_optl_item[ui1_cnt].u.t_subopt_list.pw2s_title =  MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SHUFFLE);
                t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = MMP_TM_UI_OPTL_SHUFFLE_TYPE_NUM;
                t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_shuffle;
                t_optl_item[ui1_cnt].pw2s_text= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_SETTINGS_SHUFFLE_OFF + (UINT32)ui1_cfg_value);
                t_optl_item[ui1_cnt].pw2s_label= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_SHUFFLE_LABEL);
                t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_tm_shuffle_get_sub_hlt_idx_fct;
                //t_optl_item[ui1_cnt].b_is_disable = FALSE;
                ui1_cnt++;

                /*set speed type*/
                ui1_cfg_value = 0;
                a_cfg_custom_get_photo_setting_speed(&ui1_cfg_value);

                for(ui1_index=0;ui1_index<MMP_TM_UI_OPTL_SPEED_TYPE_NUM;ui1_index++)
                {
                    t_sub_item_speed_type[ui1_index].pf_fct = _mmp_tm_speed_type_set_idx_fct;
                    t_sub_item_speed_type[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
                    t_sub_item_speed_type[ui1_index].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS +ui1_index);
                }
                t_optl_item[ui1_cnt].e_type  = OPTL_ITEM_TYPE_SUBLIST;
                t_optl_item[ui1_cnt].u.t_subopt_list.pw2s_title =  MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_SPEED);
                t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = MMP_TM_UI_OPTL_SPEED_TYPE_NUM;
                t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_speed_type;
                t_optl_item[ui1_cnt].pw2s_text= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SPEED_ITEM_5_SECONDS + (UINT32)ui1_cfg_value);
                t_optl_item[ui1_cnt].pw2s_label= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id,MLM_MMP_KEY_THUBM_SET_BTN_SPEED);
                t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_tm_speed_type_get_sub_hlt_idx_fct;
                ui1_cnt++;

                /*set effect type*/
                ui1_cfg_value = 0;
                a_cfg_custom_get_photo_setting_effect(&ui1_cfg_value);

                 for(ui1_index=0;ui1_index<MMP_TM_UI_OPTL_EFFECT_TYPE_NUM;ui1_index++)
                {
                    t_sub_item_effect_type[ui1_index].pf_fct = _mmp_tm_effect_type_set_idx_fct;
                    t_sub_item_effect_type[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
                    t_sub_item_effect_type[ui1_index].pw2s_text = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM +ui1_index);
                }

                t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
                t_optl_item[ui1_cnt].u.t_subopt_list.pw2s_title =  MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_OPTL_TITLE_EFFECT);
                t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = MMP_TM_UI_OPTL_EFFECT_TYPE_NUM;
                t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_effect_type;
                t_optl_item[ui1_cnt].pw2s_text= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_EFCT_BTN_ITEM_RANDOM + (UINT32)ui1_cfg_value);
                t_optl_item[ui1_cnt].pw2s_label= MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_SET_BTN_SHUFFLE + ui1_cnt);
                t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_tm_effect_type_get_sub_hlt_idx_fct;
                t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUBM_BTN_SETTINGS);
                ui1_cnt++;
            }
                break;
            case MMP_THUB_OPTL_DEV_LIST:
            {
                UINT32              ui4_active_index = 0;
                SIZE_T              z_size = MMP_TM_VIEW_INFO_STR_MAX_LEN;
                CHAR                s_mnt_name[MMP_TM_VIEW_INFO_STR_MAX_LEN] = {0};

                i4_ret = mmp_mc_device_get_active_mnt_point(&ui4_active_index, &z_size, s_mnt_name);
                if(i4_ret != 0)
                {
                    MMP_DBG_INFO(("!!!!%s line %d fail\n", __func__, __LINE__));
                }
                ui2_hlt_idx = ui4_active_index;

				if(ui2_hlt_idx > (ui1_cnt - 1))
				{
					ui2_hlt_idx = 0;
				}
                t_optl_item_def.pw2s_title = MLM_MMP_TEXT(pt_this->ui1_gui_lang_id, MLM_MMP_KEY_THUMB_LB_SOURCE);
                break;
            }
            default:
                break;
        }

    }

    h_handle = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_LEFT_UI_FRM1);
    i4_ret = c_wgl_set_visibility(h_handle, WGL_SW_NORMAL);
    IS_MMPR_OK(i4_ret);

    h_handle = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_LOGO_ICON_1);
    i4_ret = c_wgl_set_visibility(h_handle, WGL_SW_NORMAL);
    IS_MMPR_OK(i4_ret);

    /* memory check */
    MMP_ASSERT(ui1_cnt < MMP_DEV_LIST_MAX_NUM);
    /*main item number is  ui1_cnt   */
    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui1_cnt;
    IS_MMPR_OK (a_optl_set_option_items(pt_this->h_option_list,
                 &t_optl_item_def));

    a_optl_set_hlt_index(pt_this->h_option_list, ui2_hlt_idx, 0);

    /* Show option list */
    c_wgl_set_focus(pt_this->h_option_list , WGL_NO_AUTO_REPAINT);
    //a_optl_set_float_widget(pt_this->h_option_list,TRUE);

    a_optl_show(pt_this->h_option_list);
    pt_this->b_optl_show = TRUE;
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_optl_hide_ui
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_optl_hide_ui(MMP_TM_MEMBER_T* pt_this, BOOL b_repaint)
{
    if(b_repaint)
    {
        a_optl_hide(pt_this->h_option_list);
        pt_this->b_optl_show = FALSE;
    }
    else
    {
        a_optl_set_visibility(pt_this->h_option_list,FALSE);
        pt_this->b_optl_show = FALSE;
    }
    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_pwd_dlg_create
 * @retval
 * @retval
 */
 /*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

INT32 mmp_thumbnailmode_change_size(MMP_TM_MEMBER_T* pt_this)
{
    UINT16                          ui2_loop = 0;
    GL_RECT_T                       t_rect = {0},t_rect1={0};
    HANDLE_T                        h_thumb_item = NULL_HANDLE,h_folder_item=NULL_HANDLE,h_skip_btn=NULL_HANDLE;
    UINT16                          ui2_x = 0, ui2_y = 0, ui2_w = 0, ui2_h = 0, ui2_offset_x = 0, ui2_offset_y = 0;
    UINT16                          ui2_name_x = 0, ui2_name_y = 0, ui2_name_w = 0, ui2_name_h = 0;
    UINT16                          ui2_x_f =0,ui2_y_f =0, ui2_w_f = 0, ui2_h_f = 0, ui2_offset_x_f = 0,ui2_offset_y_f = 0;
    UINT16                          ui2_name_x_f = 0, ui2_name_y_f = 0, ui2_name_w_f = 0, ui2_name_h_f = 0;
    MMP_IMG_IMAGE_ID_T              e_img_id_folder,  e_img_id_audio,  e_img_id_text;
    MMP_IMG_IMAGE_ID_T              e_img_id_video, e_img_id_photo,e_img_id_hlt_thumb;
    MMP_IMG_IMAGE_ID_T              e_img_id_thumb_fail;
    WGL_IMG_INFO_T                  t_img_info;
    INT32                           i4_x = 0;
    INT32                           i4_y = 0;
  //  UINT8                           ui1_id = pt_this->ui1_thumb_size_id;
     UINT8                           ui1_id=1;
    //WGL_HIMG_TPL_T                  h_img_hl;

#ifdef APP_NET_DLNA_SUPPORT
    MMP_IMG_IMAGE_ID_T              e_img_id_dlna_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_M;
#endif
#ifdef APP_NET_NEIGHBOR_SUPPORT
    MMP_IMG_IMAGE_ID_T              e_img_id_mnp_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_M;
#endif
    UINT8                           ui1_max_h_num;
    UINT8                           ui1_max_v_num;

    /*Get  thumbnails  frame setting*/
    MMP_TM_RC_GET_SIZE_SETTING(ui1_id, ui2_x, ui2_y, ui2_w, ui2_h, ui2_offset_x, ui2_offset_y,
                               ui2_name_x, ui2_name_y, ui2_name_w, ui2_name_h, ui1_max_h_num, ui1_max_v_num,
                               e_img_id_folder, e_img_id_photo, e_img_id_audio, e_img_id_video, e_img_id_text,
                               e_img_id_hlt_thumb, e_img_id_thumb_fail);

    /*Get  folder frame  setting*/
    MMP_TM_RC_FOLDER_GET_SIZE_SETTINTG(ui1_id, ui2_x_f, ui2_y_f, ui2_w_f, ui2_h_f, ui2_offset_x_f, ui2_offset_y_f,
                                ui2_name_x_f, ui2_name_y_f, ui2_name_w_f, ui2_name_h_f, ui1_max_h_num, ui1_max_v_num,
                                e_img_id_folder, e_img_id_photo, e_img_id_audio, e_img_id_video, e_img_id_text,
                                e_img_id_hlt_thumb, e_img_id_thumb_fail);

    DBG_INFO(("e_img_id_folder=%d, e_img_id_text=%d, e_img_id_video=%d, e_img_id_hlt_thumb=%d\n",
        (int)e_img_id_folder, (int)e_img_id_text, (int)e_img_id_video, (int)e_img_id_hlt_thumb));

    mmp_img_get_img(e_img_id_photo, & pt_this->h_thumbnail_photo_img);
    /*Keep max_h_num and max_v_num instance variable*/
    pt_this->ui1_max_h_num = ui1_max_h_num;
    pt_this->ui1_max_v_num = ui1_max_v_num;


    t_img_info.e_type = WGL_IMG_SET_BASIC;
    t_img_info.u_img_data.t_basic.t_enable =  h_g_mmp_floder_focus_hlt;
    t_img_info.u_img_data.t_basic.t_disable =  h_g_mmp_floder_focus_hlt;
    IS_MMPR_OK (c_wgl_do_cmd (pt_this->h_frm_htl_folder_mov_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK),
                              WGL_PACK (& t_img_info)));

   // t_img_info.e_type = WGL_IMG_SET_BASIC;
  //  t_img_info.u_img_data.t_basic.t_enable =  h_g_mmp_img_sel_hlt;
  //  t_img_info.u_img_data.t_basic.t_disable =  h_g_mmp_img_sel_hlt;
   // IS_MMPR_OK (c_wgl_do_cmd (pt_this->h_frm_htl_thumbnail_mov_frm,
    //                          WGL_CMD_GL_SET_IMAGE,
      //                        WGL_PACK (WGL_IMG_BK),
        //                      WGL_PACK (& t_img_info)));

   // mmp_img_get_img(e_img_id_folder, & pt_this->h_thumbnail_folder_img);
    //mmp_img_get_img(e_img_id_photo, & pt_this->h_thumbnail_photo_img);
    mmp_img_get_img(e_img_id_audio, & pt_this->h_thumbnail_music_img);
    mmp_img_get_img(e_img_id_thumb_fail, & pt_this->h_thumbnail_load_fail_img);


#ifdef APP_NET_DLNA_SUPPORT
    if (ui1_id == 2) {e_img_id_dlna_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_L;}
    else if (ui1_id == 0) {e_img_id_dlna_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_S;}
    else {e_img_id_dlna_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_DLNA_FOLDER_M;}
    mmp_img_get_img(e_img_id_dlna_folder, & pt_this->h_thumbnail_dlna_folder_img);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    if (ui1_id == 2) {e_img_id_mnp_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_L;}
    else if (ui1_id == 0) {e_img_id_mnp_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_S;}
    else {e_img_id_mnp_folder = MMP_IMG_IMAGE_ID_THUMBNAIL_MNP_FOLDER_M;}
    mmp_img_get_img(e_img_id_mnp_folder, & pt_this->h_thumbnail_mnp_folder_img);
#endif
	/*middle*/
#define TM_THUMB_ITEM_FRAME_X                ((INT32)127)//((INT32)85)
#define TM_THUMB_ITEM_FRAME_Y                ((INT32)7)//((INT32)5)
#define TM_THUMB_ITEM_FRAME_W                ((INT32)292)//((INT32)195)
#define TM_THUMB_ITEM_FRAME_H                ((INT32)232)//((INT32)155)

    for (ui2_loop=0; ui2_loop< TM_THUMB_ITEM_FRAME_H_NUM * TM_THUMB_ITEM_FRAME_V_NUM; ui2_loop++)
    {
        if(ui2_loop < ui1_max_h_num * ui1_max_v_num)
        {
            /* move thumb item frm */
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui2_loop * 2);
            c_wgl_set_visibility (h_thumb_item,WGL_SW_HIDE);

            SET_RECT_BY_SIZE (& t_rect,
                               ui2_x + i4_x * (ui2_offset_x + ui2_w),
                               ui2_y + i4_y * (ui2_offset_y + ui2_h),
                               ui2_w,
                               ui2_h);

            IS_MMPR_OK(c_wgl_move(h_thumb_item,&t_rect,FALSE));

            /* set the transparent rect array,  this rect is related with rect of thumb item frm*/
            c_wgl_get_coords(h_thumb_item, WGL_COORDS_SCREEN, &t_rect);
            //pt_transp->ab_is_enable[i] = FALSE;
            pt_this->at_transp.at_rect[ui2_loop].i4_left   = t_rect.i4_left + MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            pt_this->at_transp.at_rect[ui2_loop].i4_top    = t_rect.i4_top  + MMP_BE_THUMBNAIL_FRM_BORDER_INSET +TOP_FRM_H;          /* parent of transparent list is canvas */
            pt_this->at_transp.at_rect[ui2_loop].i4_right  = t_rect.i4_right- MMP_BE_THUMBNAIL_FRM_BORDER_INSET;
            pt_this->at_transp.at_rect[ui2_loop].i4_bottom = t_rect.i4_bottom-MMP_BE_THUMBNAIL_FRM_BORDER_INSET +TOP_FRM_H;          /* parent of transparent list is canvas */
           // #if 0

            /* move skip icon   */
            h_skip_btn = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_SKIP0 + ui2_loop);
            t_rect1.i4_left   = TM_THUMB_SKIP_INSERT_LEFT+TM_THUMB_ITEM_FRAME_X+i4_x*(ui2_offset_x + ui2_w);
            t_rect1.i4_top    = TM_THUMB_SKIP_INSERT_TOP+TM_THUMB_ITEM_FRAME_Y+i4_y*(ui2_offset_y + ui2_h);
            t_rect1.i4_right  = t_rect1.i4_left +TM_THUMB_SKIP_INSERT_WIDTH;
            t_rect1.i4_bottom = t_rect1.i4_top+TM_THUMB_SKIP_INSERT_WIDTH;
            IS_MMPR_OK(c_wgl_move(h_skip_btn,&t_rect1,FALSE));

           // t_rect.i4_left   = pt_this->at_transp.at_rect[ui2_loop].i4_left+TM_THUMB_SKIP_INSERT_LEFT;
          //  t_rect.i4_top    = pt_this->at_transp.at_rect[ui2_loop].i4_top+TM_THUMB_SKIP_INSERT_TOP;
            //t_rect.i4_right  = pt_this->at_transp.at_rect[ui2_loop].i4_right-TM_THUMB_SKIP_INSERT_RTGHT;
           // t_rect.i4_bottom = pt_this->at_transp.at_rect[ui2_loop].i4_bottom-TM_THUMB_SKIP_INSERT_BOTTOM;

           // c_wgl_add_transparent_list_exclusion(pt_this->h_transparent_rect, &t_rect,1);
            //c_wgl_insert(h_skip_btn,NULL, WGL_INSERT_BOTTOMMOST, FALSE);
          // #endif
            //c_dbg_ctrl_stmt("###################%s,%d,%d,%d,%d,%d \n",__FUNCTION__,__LINE__,t_rect.i4_left,t_rect.i4_top,t_rect.i4_right,t_rect.i4_bottom);
            /*  move thumb item name txt wgl  */
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEXT0 + ui2_loop * 2);
            c_wgl_set_visibility (h_thumb_item,WGL_SW_HIDE);

            SET_RECT_BY_SIZE (& t_rect,
                               ui2_name_x + i4_x * (ui2_offset_x + ui2_name_w),
                               ui2_name_y + i4_y * (ui2_offset_y + ui2_h),
                               ui2_name_w,
                               ui2_name_h);
            IS_MMPR_OK(c_wgl_move(h_thumb_item,
                                 &t_rect,
                                 FALSE));

            /* move folder  item frm */
            h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_PRE_FOLDER + ui2_loop * 2);
            c_wgl_set_visibility (h_folder_item,WGL_SW_HIDE);

            SET_RECT_BY_SIZE (& t_rect,
                               ui2_x_f + i4_x * (ui2_offset_x_f + ui2_w_f),
                               ui2_y_f + i4_y * (ui2_offset_y_f + ui2_h_f),
                               ui2_w_f,
                               ui2_h_f);

            IS_MMPR_OK(c_wgl_move(h_folder_item,
                                 &t_rect,
                                 FALSE));

            /*  move folder item name txt wgl  */
            h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEX0 + ui2_loop * 2);
            c_wgl_set_visibility (h_folder_item,WGL_SW_HIDE);

            SET_RECT_BY_SIZE (& t_rect,
                               ui2_name_x_f + i4_x * (ui2_offset_x_f + ui2_name_w_f),
                               ui2_name_y_f + i4_y * (ui2_offset_y_f + ui2_h_f),
                               ui2_name_w_f,
                               ui2_name_h_f);
            IS_MMPR_OK(c_wgl_move(h_folder_item,
                                 &t_rect,
                                 FALSE));
        }
        else
        {
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0 + ui2_loop * 2);
            c_wgl_set_visibility (h_thumb_item,WGL_SW_HIDE);
            h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEXT0 + ui2_loop * 2);
            c_wgl_set_visibility (h_thumb_item,WGL_SW_HIDE);


            h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_PRE_FOLDER + ui2_loop * 2);
            c_wgl_set_visibility (h_folder_item,WGL_SW_HIDE);
            h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_TXT_NEWTEX0 + ui2_loop * 2);
            c_wgl_set_visibility (h_folder_item,WGL_SW_HIDE);
        }

        pt_this->at_transp.ab_is_enable[ui2_loop] = FALSE;
        i4_x++;
        if(i4_x >= ui1_max_h_num)
        {
            i4_x = 0;
            i4_y++;
        }
    }

    /* get rectangle , move hlt thumb frame*/
    h_thumb_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_BTN_THUMBNAILMODE0);
    c_wgl_get_coords(h_thumb_item,WGL_COORDS_PARENT,&t_rect);
    t_rect.i4_left     -= TM_THUMB_NAIL_HL_INSET1;
    t_rect.i4_top      -= TM_THUMB_NAIL_HL_INSET1;
    t_rect.i4_right    += TM_THUMB_NAIL_HL_INSET1;
    t_rect.i4_bottom   += TM_THUMB_NAIL_HL_INSET1;
    c_wgl_move(pt_this->h_frm_htl_thumbnail_mov_frm,&t_rect,FALSE);

    h_folder_item = mmp_mmp_get_wgt_hdl(WID_MMP_MMP_FRM_PRE_FOLDER);
    c_wgl_get_coords(h_folder_item,WGL_COORDS_PARENT,&t_rect);
    t_rect.i4_left     -= TM_FOLDER_MALL_HL_INSERT1;
    t_rect.i4_top      -= TM_FOLDER_MALL_HL_INSERT1;
    t_rect.i4_right    += TM_FOLDER_MALL_HL_INSERT1;
    t_rect.i4_bottom   += TM_FOLDER_MALL_HL_INSERT2;
    c_wgl_move(pt_this->h_frm_htl_folder_mov_frm,&t_rect,FALSE);

    IS_MMPR_OK (c_wgl_set_visibility(pt_this->h_frm_htl_folder_mov_frm, WGL_SW_HIDE));
    IS_MMPR_OK (c_wgl_set_visibility(pt_this->h_frm_htl_thumbnail_mov_frm, WGL_SW_HIDE));
    return  MMPR_OK;
}

#ifdef APP_NET_NEIGHBOR_SUPPORT
/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_pwd_dlg_create
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_pwd_dlg_create(MMP_TM_MEMBER_T* pt_this)
{
    PWD_DLG_INIT_T     t_pwd_dlg_init={0};
    INT32              i4_ret = -1;

    do
    {
        /* Create option list widget */
        t_pwd_dlg_init.h_parent         = pt_this->h_frm_base_frm;
        t_pwd_dlg_init.ui2_x            = OPTION_MENU_LEFT;
        t_pwd_dlg_init.ui2_y            = OPTION_MENU_TOP;
        t_pwd_dlg_init.edlgtype         = USR_PWD_DLG;
        t_pwd_dlg_init.eActItem         = ACTIVE_ON_USR;
        t_pwd_dlg_init.pf_fct           = _mmp_tm_pwd_dlg_proc_fct;
        t_pwd_dlg_init.ui2_usr_max_len  = 16;
        t_pwd_dlg_init.ui2_pwd_max_len  = 16;
        t_pwd_dlg_init.ui4_sleep_time   = MMP_BE_TIMER_OPTION_LIST;
        t_pwd_dlg_init.pv_tag           = (VOID*)pt_this;


        i4_ret = a_pwd_dlg_create(&t_pwd_dlg_init,&pt_this->h_pwd_dlg);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = a_pwd_dlg_set_float_widget(pt_this->h_pwd_dlg,TRUE);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        return MMPR_OK;
    }
    while(0);

    a_pwd_dlg_destory(pt_this->h_pwd_dlg);

    return MMPR_OK;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_pwd_dlg_destroy
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
INT32 mmp_thumbnailmode_pwd_dlg_destroy(MMP_TM_MEMBER_T* pt_this)
{
    return a_pwd_dlg_destory(pt_this->h_pwd_dlg);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_thumbnailmode_is_need_show_pwd_dlg
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
BOOL mmp_thumbnailmode_is_need_show_pwd_dlg(MMP_TM_MEMBER_T* pt_this)
{
    MMP_BE_STATUS_T             e_status = MMP_BE_STATUS_NONE;
    MMP_BE_FILE_SRC_TYPE_T      e_src_type = MMP_BE_FILE_SRC_MASS_STRG;
    CHAR                        s_curr_path[MMP_BE_MAX_PATH_LEN] = {0};
    SIZE_T                      z_size = MMP_BE_MAX_PATH_LEN;

    MMP_DBG_INFO((" begin to check is need show pwd dlg? \n"));
    /* is root path, && net neighbor */
    if(mmp_be_is_root_path())
    {
        mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS, (VOID*)&e_status);

        if(e_status == MMP_BE_STATUS_NORMAL)
        {
            mmp_be_get_curr_path(s_curr_path, &z_size);
            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE, (VOID*)&e_src_type);

            if(e_src_type == MMP_BE_FILE_SRC_NET_NEIGHBOR)
            {
                /* show the pwd dialog */
                DBG_LOG_PRINT((" check over,it need show pwd dlg! \n"));
                return TRUE;
            }
        }
    }

    MMP_DBG_INFO((" check over,it don't need show pwd dlg! \n"));
    return FALSE;
}

#endif

/*---------------------------------------------------------------------------*/
/**
 * @brief   mmp_tm_get_photo_effect
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
 VOID mmp_tm_get_photo_effect(UINT32 *pui4_effect_mode)
{

    MMP_TM_MEMBER_T*                pt_this = pt_g_tm_mbr;

    *pui4_effect_mode = pt_this->effect_type;

}

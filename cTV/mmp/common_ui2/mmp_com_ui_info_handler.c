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
 * $RCSfile: mmp_com_ui_info_handler.c,v $
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
#include "mmp_common_ui.h"
#include "res/mmp/common_ui/mmp_common_ui_rc.h"
#include "mmp/video_engine/video_engine.h"
#include "res/mmp/gen/mmp_tm_focus_layout.h"
#include "res/mmp/gen/mmp_tm_ap_layout.h"
#include "res/mmp/gen/mmp_lm_focus_layout.h"
#include "res/mmp/gen/mmp_lm_ap_layout.h"
#include "mmp_com_ui_info_handler.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "c_dbg.h"
#include "res/mmp/audio_player/mmp_audio_player_rc.h"


static VOID _mmp_com_ui_convert_time_day_sec_to_hh_mm_ss(UINT64  ui8_day_sec,    /* in */
                                                         UINT8*  pui1_hour,     /* out */
                                                         UINT8*  pui1_minute,   /* out */
                                                         UINT8*  pui1_sec);     /* out */
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
 static UINT8   ui1_fp_flag = 0; //save every player focus info creat handle
/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_focus_info_frm_create
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_focus_info_frm_create(
                        HANDLE_T                    h_parent,
                        MMP_COM_FP_INFO_UI_TYPE_T   e_ui_type,
                        MMP_COM_INFO_FP_TYPE_T      e_fp_type,
                        VOID**                      ppv_fo_inst)
{
    INT32 i4_ret;
    UINT8                 ui1_gui_lang_id;
    ISO_639_LANG_T        s639_lang;

    ui1_gui_lang_id  = mlm_mmp_s639_to_langidx(s639_lang);

    DBG_INFO(("ui1_gui_lang_id=%d\n", (int)ui1_gui_lang_id));

    MMP_COM_FP_FOCUS_INFO_VIEW_T*   pt_this = NULL;
    pt_this = c_mem_alloc(sizeof(MMP_COM_FP_FOCUS_INFO_VIEW_T));
    if (NULL == pt_this)
    {
        return MMPR_OUT_OF_MEM;
    }

    c_memset (pt_this, 0, sizeof (MMP_COM_FP_FOCUS_INFO_VIEW_T));
    do
    {
        if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_TM)
        {
            i4_ret = mmp_tm_focus_create_ui(h_parent);
            if(WGLR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
                break;
            }

            pt_this->h_main_frm = mmp_tm_focus_get_wgt_hdl(WID_MMP_TM_FOCUS_FRM_FOCUS_FRM);
            pt_this->h_info_list = mmp_tm_focus_get_wgt_hdl(WID_MMP_TM_FOCUS_LB_FILE);
           // pt_this->h_lock_icon = mmp_tm_focus_get_wgt_hdl(WID_MMP_TM_FOCUS_ICON_LOCK);
        }
        else if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_LM)
        {
            i4_ret = mmp_lm_focus_create_ui(h_parent);
            if(WGLR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
                 break;
            }

            pt_this->h_main_frm                  = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_FRM_FOCUS_FRM);
            pt_this->h_info_list                 = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_LB_FILE);
            pt_this->h_elapse_time               = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_TXT_ELAPSE);
            pt_this->h_remain_time               = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_TXT_REMAIN);
            pt_this->h_progress_bar              = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_PB_POS);
            pt_this->h_dolby_vision_hdr_hlg_icon = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_ICON_DOLBY_HDR_HLG_VISION);
            pt_this->h_dolby_audio_icon          = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_ICON_DOLBY_AUDIO);
            pt_this->h_dolby_atmos_icon          = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_ICON_DOLBY_ATMOS);
            pt_this->h_hdr10plus_str             = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_TXT_HRD10PLUS);
        }

       ui1_fp_flag |= (((UINT8)e_ui_type << 4)|e_fp_type);
       MMP_DBG_ERROR(("Create() focus info ui1_fp_flag = %x.\r\n",ui1_fp_flag));

       *ppv_fo_inst = pt_this;

       return MMPR_OK;
    }while(0);

    mmp_com_ui_focus_info_frm_destroy(e_ui_type,e_fp_type,pt_this);

    return MMPR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_focus_info_frm_active
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_focus_info_frm_active(VOID*                pv_fo_inst,
                                       MMP_COM_FP_TYPE_T    e_type,
                                       BOOL                 b_repaint)
{
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this;

    if (NULL == pv_fo_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;

    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->h_main_frm,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->h_info_list,WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_LB_FILE),WGL_SW_NORMAL));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_TXT_PRESS_OK_FOR_FULLSCREEN),WGL_SW_NORMAL));

    if(b_repaint)
    {
        MMPR_LOG_ON_FAIL( c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE));
    }

     return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_focus_info_frm_repaint
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_focus_info_frm_repaint(VOID*                   pv_fo_inst,
                                        MMP_INFO_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this;

    if (NULL == pv_fo_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;

    if(e_repaint_type == MMP_INFO_SYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);

        IS_MMPR_OK (i4_ret);
    }
    else if(e_repaint_type == MMP_INFO_ASYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm,NULL,FALSE);

        IS_MMPR_OK (i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_focus_info_frm_inactive
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_focus_info_frm_inactive(VOID*  pv_fo_inst,
                                         BOOL   b_repaint)
{
    INT32 i4_ret;
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this;

    if (NULL == pv_fo_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;


    i4_ret = mmp_com_ui_set_text(pt_this->h_elapse_time,
                                 (UTF16_T*)L"",
                                 FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_set_text(pt_this->h_remain_time,
                                 (UTF16_T*)L"",
                                 FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_progress_bar,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK(0),
                          NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,WGL_SW_HIDE_RECURSIVE);

    IS_MMPR_OK (i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);

        IS_MMPR_OK (i4_ret);
    }

     return MMPR_OK;

}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_focus_info_frm_destroy
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_focus_info_frm_destroy(MMP_COM_FP_INFO_UI_TYPE_T   e_ui_type,
                                        MMP_COM_INFO_FP_TYPE_T      e_fp_type,
                                        VOID*                       pv_fo_inst)
{
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this;

    if (NULL == pv_fo_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;

    MMP_DBG_ERROR(("Destory() focus info e_fp_type =%d.\r\n",e_fp_type));
    MMP_DBG_ERROR(("Destory() focus info old_fp_type= %x.\r\n",ui1_fp_flag));

    ui1_fp_flag &=  (~e_fp_type);

    if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_TM)
    {
        if((ui1_fp_flag & 0x0f) == 0x00)
        {
             mmp_tm_focus_destroy_ui();
        }
    }
    else if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_LM)
    {
        if((ui1_fp_flag & 0x1f) == 0x10)
        {
            mmp_lm_focus_destroy_ui();
        }
    }

    c_mem_free(pt_this);
    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_fp_focus_info_reset
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_fp_focus_set_elem_num(VOID*                pv_fo_inst,
                                       MMP_COM_FP_TYPE_T    e_type,
                                       BOOL                 b_repaint)
{
    INT32                               i4_ret = 0;
    UINT8                               ui1_show_cnt = 0;
    MMP_COM_FP_FOCUS_INFO_VIEW_T*   pt_this;

    if (NULL == pv_fo_inst)
    {
        return MMPR_INV_ARG;
    }
     pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;

    if(e_type == MMP_COM_FP_TYPE_VP)
    {
            ui1_show_cnt = MMP_FP_VP_FILE_INFO_ID_MAX;
    }
    else if(e_type == MMP_COM_FP_TYPE_PP)
    {
         ui1_show_cnt = MMP_FP_PP_FILE_INFO_ID_MAX;
         i4_ret = c_wgl_do_cmd(
                    pt_this->h_info_list,
                    WGL_CMD_LB_SET_ELEM_NUM,
                    WGL_PACK(ui1_show_cnt),
                    NULL);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    }
    else if(e_type == MMP_COM_FP_TYPE_AP)
    {
        ui1_show_cnt = MMP_FP_AP_FILE_INFO_ID_MAX;
    }
    else if(e_type == MMP_COM_FP_TYPE_TP)
    {
        ui1_show_cnt = MMP_FP_TP_FILE_INFO_ID_MAX;
    }
    else if(e_type == MMP_COM_FP_TYPE_DIR)
    {
        ui1_show_cnt = MMP_FP_DIR_FILE_INFO_ID_MAX;
    }


    c_wgl_set_visibility(pt_this->h_info_list,WGL_SW_RECURSIVE);
    pt_this->ui4_list_enem_cnt = ui1_show_cnt;

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);
    }
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_fp_set_focus_info
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_fp_set_focus_info(VOID*                        pv_fo_inst,
                                   MMP_FP_FOCUS_INFO_ID_T       e_idx,
                                   MMP_COM_UI_FP_DATA_TYPE_T    e_data_type,
                                   VOID*                        pv_data,
                                   BOOL                         b_repaint)
{
    INT32 i4_ret;
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this;

    if (NULL == pv_fo_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;

    if((UINT8)(e_idx&0x0f) >= (UINT8)(pt_this->ui4_list_enem_cnt + 1))
    {
          return MMPR_OUT_OF_LIMIT;
    }

    if(e_data_type == MMP_COM_UI_FP_DATA_W2S)
    {
        UTF16_T* w2s_text = (UTF16_T*)pv_data;
        i4_ret = c_wgl_do_cmd(pt_this->h_info_list,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2 ((e_idx&0x0f), 1),
                              WGL_PACK (w2s_text));

        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(pt_this->h_info_list,WGL_SW_RECURSIVE);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }
    }
    else if(e_data_type == MMP_COM_UI_FP_DATA_BOOL)
    {
        /*
        BOOL b_read_only = (BOOL)(UINT32)(pv_data);

        if(b_read_only)
        {
            i4_ret = c_wgl_set_visibility(pt_this->h_lock_icon,WGL_SW_NORMAL);

        }
        else
        {
            i4_ret = c_wgl_set_visibility(pt_this->h_lock_icon,WGL_SW_HIDE);
        }

        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }
        */
    }
    else
    {
        return MMPR_NOT_SUPPORT;
    }

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm,NULL,TRUE);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_creat_ap_info_frm
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_ap_info_frm_create(HANDLE_T                    h_parent,
                                    MMP_COM_FP_INFO_UI_TYPE_T   e_ui_type,
                                    VOID**                      ppv_ap_inst)
{
    INT32           i4_ret = MMPR_OK;
    GL_RECT_T       at_rect[1];
    MMP_COM_AP_PLAY_INFO_VIEW_T*    pt_this = NULL;
    GL_RECT_T t_rect = {0};

    pt_this = c_mem_alloc(sizeof(MMP_COM_AP_PLAY_INFO_VIEW_T));
    if (NULL == pt_this)
    {
        return MMPR_OUT_OF_MEM;
    }

    c_memset (pt_this, 0, sizeof (MMP_COM_AP_PLAY_INFO_VIEW_T));

    do
    {
        if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_TM)
        {
            i4_ret = mmp_tm_ap_create_ui(h_parent);
            if(WGLR_OK != i4_ret)
            {
                    MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
                    break;
            }

            pt_this->h_main_frm = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_FRM_AP_FRM);
            pt_this->h_vol_bar = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_PB_VOL);
            pt_this->h_pb_playback = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_PB_POS);
            pt_this->ah_icon[0] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_ICON_STATUS);
            pt_this->ah_icon[1] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_ICON_REPEAT);
            pt_this->ah_icon[2] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_ICON_AB);
            pt_this->ah_icon[3] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_ICON_SHUFFLE);
            pt_this->ah_icon[4] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_ICON_VOLUME);
            pt_this->ah_label[0] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_TXT_NAME);
            pt_this->ah_label[1] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_TXT_CUR);
            pt_this->ah_label[2] = mmp_tm_ap_get_wgt_hdl(WID_MMP_TM_AP_TXT_TOL);
        }
        else  if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_LM)
        {
            i4_ret = mmp_lm_ap_create_ui(h_parent);
            if(WGLR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));
                break;
            }
            pt_this->h_main_frm = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_FRM_AP_FRM);
            pt_this->h_pb_playback = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_PB_POS);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_FILE_NAME]      = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_NAME);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_POS]            = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_CUR);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DUR]            = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_TOL);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM]          = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_ALBUM);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM_HINT]     = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_ALBUM_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ARTIST]         = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_ARTIST);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ARTIST_HINT]    = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_ARTIST_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_NAME_HINT]      = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_NAME_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DURATION_HINT]  = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_DURATION_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_SIZE_HINT]      = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_SIZE_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_TITLE]          = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_TITLE);
            pt_this->ah_label[ MMP_AP_PLAY_INFO_LBL_ID_GERNER]        = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_GERNER);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_YEAR]           = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_YEAR);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DIRECTOR]       = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_DIRECTOR);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PRODUCER]       = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_PRODUCER);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PROTECT]        = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_PROTECT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_GERNER_HINT]    = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_GERNER_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_YEAR_HINT]      = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_YEAR_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DIRECTOR_HINT]  = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_DIRECTOR_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PRODUCER_HINT]  = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_PRODUCER_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PROTECT_HINT]   = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_PROTECT_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_TITLE_HINT]     = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_TITLE_HINT);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_SIZE]           = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_SIZE);
            pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DURATION]       = mmp_lm_ap_get_wgt_hdl(WID_MMP_LM_AP_TXT_DURATION);

#if NEVER
            c_memset(at_rect, 0, sizeof(at_rect));
            SET_RECT_BY_SIZE (&at_rect[0],
                              MMP_AP_INFO_HANDLE_COV_PIC_X,
                              MMP_AP_INFO_HANDLE_COV_PIC_Y,
                              MMP_AP_INFO_HANDLE_COV_PIC_W,
                              MMP_AP_INFO_HANDLE_COV_PIC_H);

            i4_ret = c_wgl_create_transparent_list(mmp_main_get_canvas(),
                                                   at_rect,
                                                   1,
                                                   &pt_this->h_transparent_list);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_enable_transparent_list (pt_this->h_transparent_list,
                                                    FALSE,
                                                    FALSE);
            MMPR_LOG_ON_FAIL(i4_ret);
#else
            c_memset(&t_rect, 0, sizeof(t_rect));
            SET_RECT_BY_SIZE (&t_rect,
                              240+240+480+240-50,//240MMP_AP_RC_COV_PIC_X 240+240+480+240
                              118-100-10+50-30,//118 MMP_AP_RC_COV_PIC_Y
                              MMP_AP_RC_COV_PIC_W+150,//170 MMP_AP_RC_COV_PIC_W
                              MMP_AP_RC_COV_PIC_H+60);//182 MMP_AP_RC_COV_PIC_H   1342, 260

            i4_ret = c_wgl_create_widget(pt_this->h_main_frm,
                                        HT_WGL_WIDGET_ICON,
                                        WGL_CONTENT_ICON_DEF,
                                        WGL_BORDER_NULL,
                                        &t_rect,
                                        NULL,
                                        255,
                                        (VOID*)(WGL_STL_GL_NO_BK),
                                        NULL,
                                        &(pt_this->h_audio_play_img_fr));
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(pt_this->h_audio_play_img_fr, WGL_SW_HIDE);
            MMPR_LOG_ON_FAIL(i4_ret);
#endif
        }
        else
        {
            MMPR_LOG_ON_FAIL(MMPR_FAIL);
            break;
        }

        *ppv_ap_inst = pt_this;
        return MMPR_OK;
    }while(0);

    i4_ret = mmp_com_ui_ap_info_frm_destroy(e_ui_type, pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

#define AP_UI_SET_TXT_VISIBLE(handle,txt) \
do{\
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(handle,WGL_SW_NORMAL));\
    MMPR_LOG_ON_FAIL(mmp_com_ui_set_text(handle,txt,FALSE));\
}while(0)

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_ap_info_frm_show
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_ap_info_frm_active(VOID*       pv_ap_inst,
                                    UINT16      ui2_lang,
                                    BOOL        b_repaint)
{
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this   = NULL;

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }

    DBG_LOG_PRINT(("[MMP][%s %d]\n",__FUNCTION__,__LINE__));

    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)pv_ap_inst;
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->h_main_frm, WGL_SW_NORMAL));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_ALBUM_HINT));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ARTIST_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_ARTIST_HINT));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_TITLE_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_TITLE));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_NAME_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_NAME));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_SIZE_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_FILE_SIZE));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DIRECTOR_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_DIRECTOR));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DURATION_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_DURATION));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_YEAR_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_YEAR));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_GERNER_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_GENRE));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PRODUCER_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_COPYRIGHT));

    AP_UI_SET_TXT_VISIBLE(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PROTECT_HINT],
                          MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_PROTECTED));

    MMPR_LOG_ON_FAIL(c_wgl_insert(pt_this->h_main_frm,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT));

    if(b_repaint)
    {
        MMPR_LOG_ON_FAIL(c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE));
    }
    return MMPR_OK;
}

INT32 mmp_com_ui_ap_info_update_text(VOID*       pv_ap_inst,
                                     UINT16      ui2_lang)
{
    INT32    i4_ret = MMPR_OK;
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;
    BOOL     b_visible = FALSE;

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)pv_ap_inst;

    i4_ret = c_wgl_get_visibility(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM_HINT], 
                                  &b_visible);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (b_visible)
    {
        i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM_HINT],
                                     MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_ALBUM_HINT),
                                     FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ARTIST_HINT],
                                    MLM_MMP_TEXT(ui2_lang, MLM_MMP_KEY_AUD_INFO_ARTIST_HINT),
                                    FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

INT32 mmp_com_ui_ap_info_show_process_bar(VOID*     pv_ap_inst,
                                                      BOOL      b_show,
                                                      BOOL      b_repaint)
{
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this    = NULL;
    WGL_SW_CMD_T                  show_cmd   = (b_show ? WGL_SW_NORMAL : WGL_SW_HIDE);

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }

    DBG_LOG_PRINT(("[MMP][%s,%s,%d] show_cmd = %d\n",__FILE__, __FUNCTION__, __LINE__,show_cmd));
    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)pv_ap_inst;

    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_POS],show_cmd));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DUR],show_cmd));
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->h_pb_playback,show_cmd));

    if(b_repaint)
    {
        MMPR_LOG_ON_FAIL(c_wgl_repaint(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_POS],NULL,FALSE));
        MMPR_LOG_ON_FAIL(c_wgl_repaint(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DUR],NULL,FALSE));
        MMPR_LOG_ON_FAIL(c_wgl_repaint(pt_this->h_pb_playback,NULL,FALSE));
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_ap_info_frm_hide
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_ap_info_frm_inactive(VOID*     pv_ap_inst,
                                      BOOL      b_repaint)
{
    INT32    i4_ret = MMPR_OK;
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;

    DBG_LOG_PRINT(("\n%s,%s,%d\n",
               __FILE__, __FUNCTION__, __LINE__));

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)pv_ap_inst;

    i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_FILE_NAME],
                               (UTF16_T*)L"",
                               FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_POS],
                               (UTF16_T*)L"",
                               FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DUR],
                               (UTF16_T*)L"",
                               FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM],
                               (UTF16_T*)L"",
                               FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM_HINT],
                               (UTF16_T*)L"",
                               FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ARTIST],
                               (UTF16_T*)L"",
                               FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ARTIST_HINT],
                               (UTF16_T*)L"",
                               FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_this->h_pb_playback,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK(0),
                          NULL);
    MMPR_LOG_ON_FAIL (i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm,WGL_SW_HIDE_RECURSIVE);

    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret= c_wgl_enable_transparent_list(pt_this->h_transparent_list,
                                          FALSE,
                                          FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

     return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_ap_info_frm_destroy
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_ap_info_frm_destroy(MMP_COM_FP_INFO_UI_TYPE_T  e_ui_type,
                                     VOID*                      pv_ap_inst)
{
    INT32      i4_ret = MMPR_OK;
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)pv_ap_inst;

    if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_TM)
    {
        i4_ret = mmp_tm_ap_destroy_ui();
        MMPR_LOG_ON_FAIL (i4_ret);
    }
    else if(e_ui_type == MMP_COM_FP_INFO_UI_TYPE_LM)
    {
       i4_ret = mmp_lm_ap_destroy_ui();
       MMPR_LOG_ON_FAIL (i4_ret);

       if (NULL_HANDLE != pt_this->h_transparent_list)
       {
            i4_ret = c_wgl_delete_transparent_list(pt_this->h_transparent_list);
            MMPR_LOG_ON_FAIL (i4_ret);
            pt_this->h_transparent_list = NULL_HANDLE;
       }
    }

    c_mem_free(pt_this);

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_com_ui_convert_time_day_sec_to_hh_mm_ss
 *
 * Description: Convert ui4_day_sec => ui1_hour/ui1_minute/ui1_second
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _mmp_com_ui_convert_time_day_sec_to_hh_mm_ss(UINT64  ui8_day_sec,    /* in */
                                                         UINT8*  pui1_hour,     /* out */
                                                         UINT8*  pui1_minute,   /* out */
                                                         UINT8*  pui1_sec)      /* out */
{
    UINT32  ui4_left_sec = 0;
    UINT8   ui1_hour = 0;
    UINT8   ui1_minute = 0;
    UINT8   ui1_sec = 0;

    ui4_left_sec    = (UINT32)ui8_day_sec;
    ui1_hour        = (UINT8) (ui4_left_sec / 3600);
    ui4_left_sec    -= ui1_hour*3600;
    ui1_minute      = (UINT8) (ui4_left_sec / 60);
    ui4_left_sec    -= ui1_minute*60;
    ui1_sec         = (UINT8) ui4_left_sec;

    *pui1_hour   = ui1_hour;
    *pui1_minute = ui1_minute;
    *pui1_sec    = ui1_sec;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_ap_info_hdlr_frm_repaint
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_ap_info_hdlr_frm_repaint(VOID*         pv_ap_inst,
                                                         BOOL         b_repaint)
{
    INT32      i4_ret = MMPR_OK;
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)pv_ap_inst;

    i4_ret = c_wgl_repaint(pt_this->h_main_frm,
                           NULL,
                           b_repaint);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_vp_info_hdlr_frm_repaint
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_vp_info_hdlr_frm_repaint(VOID*         pv_ap_inst,
                                                         BOOL         b_repaint)
{
    INT32      i4_ret = MMPR_OK;
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this = NULL;

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_ap_inst;

    i4_ret = c_wgl_repaint(pt_this->h_main_frm,
                           NULL,
                           b_repaint);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: mmp_com_ui_ap_set_play_info
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_com_ui_ap_set_play_info (VOID*                        pv_ap_inst,
                                   MMP_AP_CUR_PLAY_INFO_ID_T    e_idx,
                                   VOID*                        pv_data,
                                   BOOL                         b_repaint)
{
    INT32      i4_ret = MMPR_OK;
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;

    if (NULL == pv_ap_inst)
    {
        return MMPR_INV_ARG;
    }
    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)pv_ap_inst;

    switch(e_idx)
    {
        case MMP_AP_CUR_PLAY_INFO_PLAY_STATUS:
        {
            MMP_VE_PLAY_STAT_T e_player_status;
            UINT32             ui4_status = 0xFFFFFFFF;
            SIZE_T             t_size     = sizeof(UINT32);

            e_player_status = (MMP_VE_PLAY_STAT_T)(UINT32)pv_data;

            a_icl_get(ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS),
                      (VOID*)&ui4_status,
                      &t_size);

            if (ui4_status != (UINT32)e_player_status)
            {
                a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS),
                          (VOID*) &e_player_status,
                          ICL_RECID_CUSTOM_MMP_BK_PLAYER_STATUS_SIZE);
            }

            switch (e_player_status)
            {
                case MMP_VE_PLAY_STAT_PLAY:
                {
                }
                    break;

                case MMP_VE_PLAY_STAT_PAUSE:
                {
                }
                    break;

                case MMP_VE_PLAY_STAT_STOP:
                {
                  //  i4_ret = mmp_com_ui_ap_info_frm_inactive(pv_ap_inst, b_repaint);
                  //  MMPR_LOG_ON_FAIL(i4_ret);
                }
                    break;

                case MMP_VE_PLAY_STAT_FAST_FWD:
                {
                }
                    break;

                case MMP_VE_PLAY_STAT_FAST_RWD:
                {
                }
                    break;

                default:
                    break;
                }
        }
            break;

        case MMP_AP_CUR_PLAY_INFO_ELAPSE_TIME:
        {
            CHAR        s_buf[10] = {0};
            UTF16_T     w2s_buf[10] = {0};
            UINT8       ui1_hh = 0;
            UINT8       ui1_mm = 0;
            UINT8       ui1_ss = 0;
            UINT64      ui8_time = (UINT64)(UINT32)pv_data;

            /* set text */
            _mmp_com_ui_convert_time_day_sec_to_hh_mm_ss(ui8_time, &ui1_hh, &ui1_mm, &ui1_ss);
            if(0 == ui8_time)
            {
                c_sprintf(s_buf, "00:%02d:%02d", ui1_hh, ui1_mm, ui1_ss);
            }
            else if(0 != ui1_hh)
            {
                c_sprintf(s_buf, "%02d:%02d:%02d", ui1_hh, ui1_mm, ui1_ss);
            }
            else
            {
                c_sprintf(s_buf, "00:%02d:%02d", ui1_mm, ui1_ss);
            }
            c_uc_ps_to_w2s(s_buf, w2s_buf, 10);

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_POS],
                                         (UTF16_T*)w2s_buf,
                                         b_repaint);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;

        case MMP_AP_CUR_PLAY_INFO_REMAIN_TIME:
        {
            CHAR        s_buf[10] = {0};
            UTF16_T     w2s_buf[10] = {0};
            UINT8       ui1_hh = 0;
            UINT8       ui1_mm = 0;
            UINT8       ui1_ss = 0;
            UINT64      ui8_time = (UINT64)(UINT32)pv_data;

            /* set text */
            _mmp_com_ui_convert_time_day_sec_to_hh_mm_ss(ui8_time, &ui1_hh, &ui1_mm, &ui1_ss);
            if(0 != ui1_hh)
            {
                c_sprintf(s_buf, "%02d:%02d:%02d", ui1_hh, ui1_mm, ui1_ss);
            }
            else
            {
                c_sprintf(s_buf, "00:%02d:%02d", ui1_mm, ui1_ss);
            }
            c_uc_ps_to_w2s(s_buf, w2s_buf, 10);

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DUR],
                                         (UTF16_T*)w2s_buf,
                                         b_repaint);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;

        case MMP_AP_CUR_PLAY_INFO_PG_POS:
        {
            UINT32 ui4_pos = (UINT32)pv_data;

            i4_ret = c_wgl_do_cmd(pt_this->h_pb_playback,
                                  WGL_CMD_PG_SET_POS,
                                  WGL_PACK(ui4_pos),
                                  NULL);
            MMPR_LOG_ON_FAIL (i4_ret);

            if(b_repaint == TRUE)
            {
                i4_ret = c_wgl_repaint(pt_this->h_pb_playback,
                                 NULL,
                                 TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
            break;

        case MMP_AP_CUR_PLAY_INFO_FILE_NAME:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_FILE_NAME],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;

        case MMP_AP_CUR_PLAY_INFO_ALBUM:
        {
            UTF16_T* w2s_album = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ALBUM],
                                   (UTF16_T*)w2s_album,
                                   b_repaint);
            MMPR_LOG_ON_FAIL(i4_ret);
            c_uc_w2s_to_ps(w2s_album,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_ALBUM : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;

        case MMP_AP_CUR_PLAY_INFO_ARTIST:
        {
            UTF16_T* w2s_artist = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_ARTIST],
                                   (UTF16_T*)w2s_artist,
                                   b_repaint);
            MMPR_LOG_ON_FAIL(i4_ret);
            c_uc_w2s_to_ps(w2s_artist,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_ARTIST : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;
        case MMP_AP_CUR_PLAY_INFO_COVER:
        {
            BOOL* p_b_is_true = (BOOL*)pv_data;

            i4_ret = c_wgl_enable_transparent_list(pt_this->h_transparent_list,
                                                   *p_b_is_true,
                                                   FALSE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case MMP_AP_CUR_PLAY_INFO_FILE_SIZE:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_SIZE],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;
        case MMP_AP_CUR_PLAY_INFO_YEAR:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_YEAR],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;
         case MMP_AP_CUR_PLAY_INFO_DIRECTOR:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DIRECTOR],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME\n",__FUNCTION__,__LINE__));
        }
            break;
        case MMP_AP_CUR_PLAY_INFO_PRODUCER:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PRODUCER],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;
        case MMP_AP_CUR_PLAY_INFO_PROTECT:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_PROTECT],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;
         case MMP_AP_CUR_PLAY_INFO_TITLE:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};

            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_TITLE],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;
         case MMP_AP_CUR_PLAY_INFO_DURATION:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};
        
            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_DURATION],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
            break;
         case MMP_AP_CUR_PLAY_INFO_GERNER:
        {
            UTF16_T* w2s_text = (UTF16_T*)pv_data;
            CHAR ps[128] = {0};
        
            i4_ret = mmp_com_ui_set_text(pt_this->ah_label[MMP_AP_PLAY_INFO_LBL_ID_GERNER],
                                   (UTF16_T*)w2s_text,
                                   b_repaint);
            MMPR_LOG_ON_FAIL (i4_ret);
            c_uc_w2s_to_ps(w2s_text,ps,128);
            DBG_LOG_PRINT(("[MMP][%s %d] MMP_AP_CUR_PLAY_INFO_FILE_NAME : %s\n",__FUNCTION__,__LINE__,ps));
        }
                break;

        default:
            break;
    }

    return MMPR_OK;
}



INT32 mmp_com_ui_vp_set_play_info(VOID*                     pv_fo_inst,
                                  MMP_VP_CUR_PLAY_INFO_ID_T e_idx,
                                  VOID*                     pv_data,
                                  MMP_VP_PROG_BAR_TYPE_T    ui4_vp_bar_type,
                                  BOOL                      b_repaint)
{
    INT32       i4_ret;
    CHAR        s_buf[10] = {0};
    UTF16_T     w2s_buf[10] = {0};
    UINT8       ui1_hh = 0;
    UINT8       ui1_mm = 0;
    UINT8       ui1_ss = 0;
    UINT64      ui8_time = (UINT64)(UINT32)pv_data;
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this;
    HANDLE_T    h_view_item = NULL_HANDLE;

    pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;
   // DBG_LOG_PRINT(("[MMP][%s %d] e_idx = %d\n",__FUNCTION__,__LINE__,e_idx));
    switch(e_idx)
    {
        case MMP_VP_CUR_PLAY_INFO_ELAPSE_TIME:
        {
            if (MMP_VP_PROG_BAR_TYPE_TIME == ui4_vp_bar_type)
            {
                _mmp_com_ui_convert_time_day_sec_to_hh_mm_ss(ui8_time, &ui1_hh, &ui1_mm, &ui1_ss);
                if(0 == ui8_time)
                {
                    c_sprintf(s_buf, "00:%02d:%02d", ui1_hh, ui1_mm, ui1_ss);
                }
                else if(0 != ui1_hh)
                {
                    c_sprintf(s_buf, "%02d:%02d:%02d", ui1_hh, ui1_mm, ui1_ss);
                }
                else
                {
                    c_sprintf(s_buf, "00:%02d:%02d", ui1_mm, ui1_ss);
                }

                c_uc_ps_to_w2s(s_buf, w2s_buf, 10);

                i4_ret = mmp_com_ui_set_text(pt_this->h_elapse_time,
                                             (UTF16_T*)w2s_buf,
                                             b_repaint);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = mmp_com_ui_set_text(pt_this->h_elapse_time,
                                             WGL_PACK (L""),
                                             b_repaint);
                MMPR_LOG_ON_FAIL (i4_ret);
            }

            i4_ret = c_wgl_set_visibility(pt_this->h_elapse_time, WGL_SW_RECURSIVE);
            MMPR_LOG_ON_FAIL(i4_ret);

            h_view_item = pt_this->h_elapse_time;
        }
            break;

        case MMP_VP_CUR_PLAY_INFO_REMAIN_TIME:
        {
            CHAR        s_buf[10] = {0};
            UTF16_T     w2s_buf[10] = {0};
            UINT8       ui1_hh = 0;
            UINT8       ui1_mm = 0;
            UINT8       ui1_ss = 0;
            UINT64      ui8_time = (UINT64)(UINT32)pv_data;

            if (MMP_VP_PROG_BAR_TYPE_TIME == ui4_vp_bar_type)
            {
                _mmp_com_ui_convert_time_day_sec_to_hh_mm_ss(ui8_time, &ui1_hh, &ui1_mm, &ui1_ss);
                if(0 != ui1_hh)
                {
                    c_sprintf(s_buf, "%02d:%02d:%02d", ui1_hh, ui1_mm, ui1_ss);
                }
                else
                {
                    c_sprintf(s_buf, "00:%02d:%02d", ui1_mm, ui1_ss);
                }

                c_uc_ps_to_w2s(s_buf, w2s_buf, 10);

                i4_ret = mmp_com_ui_set_text(pt_this->h_remain_time,
                                             (UTF16_T*)w2s_buf,
                                             b_repaint);
                MMPR_LOG_ON_FAIL (i4_ret);
            }
            else
            {
                i4_ret = mmp_com_ui_set_text(pt_this->h_remain_time,
                                             WGL_PACK (L""),
                                             b_repaint);
                MMPR_LOG_ON_FAIL (i4_ret);
            }

            i4_ret = c_wgl_set_visibility(pt_this->h_remain_time, WGL_SW_RECURSIVE);
            MMPR_LOG_ON_FAIL(i4_ret);

            h_view_item = pt_this->h_remain_time;
        }
            break;

        case MMP_VP_CUR_PLAY_INFO_PG_POS:
        {
            UINT32 ui4_pos = (UINT32)pv_data;

            i4_ret = c_wgl_do_cmd(pt_this->h_progress_bar,
                                  WGL_CMD_PG_SET_POS,
                                  WGL_PACK(ui4_pos),
                                  NULL);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_set_visibility(pt_this->h_progress_bar, WGL_SW_RECURSIVE);
            MMPR_LOG_ON_FAIL(i4_ret);

            h_view_item = pt_this->h_progress_bar;
        }
            break;
        default:
            break;
    }
    if(b_repaint == TRUE)
    {
        i4_ret = c_wgl_repaint(h_view_item, NULL, FALSE);
        MMPR_LOG_ON_FAIL (i4_ret);
    }
    return MMPR_OK;
}

INT32 mmp_com_ui_vp_update_info_dolby_audio(VOID*  pv_fo_inst, WGL_HIMG_TPL_T   h_img)
{
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;
    WGL_IMG_INFO_T      t_img_info;
    INT32               i4_ret = MMPR_OK;
    
    /* set icon image */
    c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
    t_img_info.e_type                            = WGL_IMG_SET_BASIC ;
    t_img_info.u_img_data.t_standard.t_enable    = h_img ;
    t_img_info.u_img_data.t_standard.t_disable   = h_img ;
    t_img_info.u_img_data.t_standard.t_highlight = h_img ;
    /*show dolby vision ui*/  
    i4_ret = c_wgl_do_cmd (pt_this->h_dolby_audio_icon,
                            WGL_CMD_GL_SET_IMAGE,
                            WGL_PACK(WGL_IMG_FG),
                            WGL_PACK(&t_img_info));
    IS_MMPR_OK(i4_ret == WGLR_OK ? MMPR_OK : i4_ret );
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->h_dolby_audio_icon,NULL_HANDLE == h_img ? WGL_SW_HIDE : WGL_SW_NORMAL));
	MMPR_LOG_ON_FAIL(c_wgl_repaint(pt_this->h_dolby_audio_icon,NULL,TRUE));
    return MMPR_OK;
}

INT32 mmp_com_ui_vp_update_info_dolby_atmos(VOID*  pv_fo_inst, WGL_HIMG_TPL_T   h_img)
{
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;
    WGL_IMG_INFO_T      t_img_info;
    INT32               i4_ret = MMPR_OK;
    
    /* set icon image */
    c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
    t_img_info.e_type                            = WGL_IMG_SET_BASIC ;
    t_img_info.u_img_data.t_standard.t_enable    = h_img ;
    t_img_info.u_img_data.t_standard.t_disable   = h_img ;
    t_img_info.u_img_data.t_standard.t_highlight = h_img ;
    /*show dolby vision ui*/  
    i4_ret = c_wgl_do_cmd (pt_this->h_dolby_atmos_icon,
                            WGL_CMD_GL_SET_IMAGE,
                            WGL_PACK(WGL_IMG_FG),
                            WGL_PACK(&t_img_info));
    IS_MMPR_OK(i4_ret == WGLR_OK ? MMPR_OK : i4_ret );
    MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->h_dolby_atmos_icon, NULL_HANDLE == h_img ? WGL_SW_HIDE : WGL_SW_NORMAL));
	MMPR_LOG_ON_FAIL(c_wgl_repaint(pt_this->h_dolby_atmos_icon, NULL, TRUE));
    return MMPR_OK;
}

INT32 mmp_com_ui_vp_update_info_dolby_hdr_hlg_vision(VOID*    pv_fo_inst, WGL_HIMG_TPL_T   h_img)
{
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;
    WGL_IMG_INFO_T      t_img_info;
    INT32               i4_ret = MMPR_OK;
    
    /* set icon image */
    c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
    t_img_info.e_type                            = WGL_IMG_SET_BASIC ;
    t_img_info.u_img_data.t_standard.t_enable    = h_img ;
    t_img_info.u_img_data.t_standard.t_disable   = h_img ;
    t_img_info.u_img_data.t_standard.t_highlight = h_img ;
    /*show dolby/hdr/hlg vision ui*/  
    i4_ret = c_wgl_do_cmd (pt_this->h_dolby_vision_hdr_hlg_icon,
                            WGL_CMD_GL_SET_IMAGE,
                            WGL_PACK(WGL_IMG_FG),
                            WGL_PACK(&t_img_info));
    IS_MMPR_OK(i4_ret == WGLR_OK ? MMPR_OK : i4_ret );
	MMPR_LOG_ON_FAIL(c_wgl_set_visibility(pt_this->h_dolby_vision_hdr_hlg_icon, NULL_HANDLE == h_img ? WGL_SW_HIDE : WGL_SW_NORMAL));
	MMPR_LOG_ON_FAIL(c_wgl_repaint(pt_this->h_dolby_vision_hdr_hlg_icon, NULL, TRUE));
    return MMPR_OK;
}
INT32 mmp_com_ui_vp_update_info_HDR10plus(VOID*    pv_fo_inst, UTF16_T *h_str)
{
    MMP_COM_FP_FOCUS_INFO_VIEW_T*  pt_this = (MMP_COM_FP_FOCUS_INFO_VIEW_T*)pv_fo_inst;
    INT32                          i4_ret = MMPR_OK;
    
    /*show HDR10plus vision ui*/  
    i4_ret = c_wgl_do_cmd (pt_this->h_hdr10plus_str,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(h_str),
                            WGL_PACK((UINT16)0xFFFF));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }    

    i4_ret = c_wgl_repaint(pt_this->h_hdr10plus_str,NULL,TRUE); 
    
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_repaint() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    } 
    i4_ret = c_wgl_set_visibility(pt_this->h_hdr10plus_str, WGL_SW_RECURSIVE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}



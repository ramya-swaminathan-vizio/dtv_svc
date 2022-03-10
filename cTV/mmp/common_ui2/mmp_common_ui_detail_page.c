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
 * $RCSfile: mmp_common_ui_detail_page.c,v $
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
#include "mmp_common_ui_detail_page.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static MMP_COM_UI_DETAIL_PAGE_T     t_vp_page, t_pp_page, t_ap_page, t_tp_page;
static UINT16                   ui2_g_lang;

/*-----------------------------------------------------------------------------
* private methods declarations
*---------------------------------------------------------------------------*/
static UINT16 _mmp_get_mlm_lang_id(VOID);
static INT32 _mmp_com_ui_create_vid_detail_page(HANDLE_T h_parent);
static INT32 _mmp_com_ui_create_pho_detail_page(HANDLE_T h_parent);
static INT32 _mmp_com_ui_create_aud_detail_page(HANDLE_T h_parent);
static INT32 _mmp_com_ui_create_text_detail_page(HANDLE_T h_parent);

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
static UINT16 _mmp_get_mlm_lang_id(VOID)
{
    INT32                       i4_ret;
    ISO_639_LANG_T              s639_lang;
    UINT16                      ui2_lang_id;

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if(i4_ret != APP_CFGR_OK)
    {
        MMP_DBG_ERROR(("a_cfg_get_gui_lang() fail. i4_ret = %d.\r\n", i4_ret));
        ui2_lang_id =0;
    }
    else
    {
        ui2_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }

    return ui2_lang_id;
}

static INT32 _mmp_com_ui_create_vid_detail_page(HANDLE_T h_parent)
{
    INT32                 i4_ret;

    i4_ret = mmp_vdp_create_ui(h_parent);
    if(WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_vdp_create_ui() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    /*get detail page handle*/
    t_vp_page.h_page = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_FRM_DETAIL_PAGE);

    /*get wigdet handle*/
    t_vp_page.ah_label[0] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_LABEL0);
    t_vp_page.ah_label[1] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_LABEL1);
    t_vp_page.ah_label[2] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_LABEL2);
    t_vp_page.ah_label[3] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_LABEL3);
    t_vp_page.ah_label[4] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_LABEL4);
    t_vp_page.ah_label[5] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_LABEL5);
    t_vp_page.ah_label[6] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_LABEL6);

    t_vp_page.ah_value[0] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_VALUE0);
    t_vp_page.ah_value[1] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_VALUE1);
    t_vp_page.ah_value[2] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_VALUE2);
    t_vp_page.ah_value[3] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_VALUE3);
    t_vp_page.ah_value[4] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_VALUE4);
    t_vp_page.ah_value[5] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_VALUE5);
    t_vp_page.ah_value[6] = mmp_vdp_get_wgt_hdl(WID_MMP_VDP_TXT_VALUE6);

    i4_ret = mmp_vdp_update_text(ui2_g_lang);
    if (WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_vdp_update_text() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return (MMPR_OK);
}

static INT32 _mmp_com_ui_create_pho_detail_page(HANDLE_T h_parent)
{
    INT32                 i4_ret;

    i4_ret = mmp_pdp_create_ui(h_parent);
    if(WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_pdp_create_ui() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    /*get detail page handle*/
    t_pp_page.h_page = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_FRM_DETAIL_PAGE);

    t_pp_page.ah_label[0] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL0);
    t_pp_page.ah_label[1] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL1);
    t_pp_page.ah_label[2] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL2);
    t_pp_page.ah_label[3] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL3);
    t_pp_page.ah_label[4] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL4);
    t_pp_page.ah_label[5] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL5);
    t_pp_page.ah_label[6] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL6);
    t_pp_page.ah_label[7] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL7);
    t_pp_page.ah_label[8] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL8);
    t_pp_page.ah_label[9] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL9);
    t_pp_page.ah_label[10] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL10);
    //t_pp_page.ah_label[11] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_LABEL11);

    t_pp_page.ah_value[0] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE0);
    t_pp_page.ah_value[1] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE1);
    t_pp_page.ah_value[2] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE2);
    t_pp_page.ah_value[3] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE3);
    t_pp_page.ah_value[4] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE4);
    t_pp_page.ah_value[5] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE5);
    t_pp_page.ah_value[6] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE6);
    t_pp_page.ah_value[7] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE7);
    t_pp_page.ah_value[8] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE8);
    t_pp_page.ah_value[9] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE9);
    t_pp_page.ah_value[10] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE10);
    //t_pp_page.ah_value[11] = mmp_pdp_get_wgt_hdl(WID_MMP_PDP_TXT_VALUE11);

    i4_ret = mmp_pdp_update_text(ui2_g_lang);
    if (WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_pdp_update_text() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return (MMPR_OK);
}

static INT32 _mmp_com_ui_create_aud_detail_page(HANDLE_T h_parent)
{
#if 0
    INT32                 i4_ret;

    i4_ret = mmp_adp_create_ui(h_parent);
    if(WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_adp_create_ui() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    /*get detail page handle*/
    t_ap_page.h_page = mmp_adp_get_wgt_hdl(WID_MMP_ADP_FRM_DETAIL_PAGE);

    /*get wigdet handle*/
    t_ap_page.ah_label[0] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_LABEL0);
    t_ap_page.ah_label[1] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_LABEL1);
    t_ap_page.ah_label[2] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_LABEL2);
    t_ap_page.ah_label[3] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_LABEL3);
    t_ap_page.ah_label[4] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_LABEL4);
    t_ap_page.ah_label[5] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_LABEL5);
    t_ap_page.ah_label[6] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_LABEL6);

    t_ap_page.ah_value[0] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_VALUE0);
    t_ap_page.ah_value[1] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_VALUE1);
    t_ap_page.ah_value[2] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_VALUE2);
    t_ap_page.ah_value[3] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_VALUE3);
    t_ap_page.ah_value[4] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_VALUE4);
    t_ap_page.ah_value[5] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_VALUE5);
    t_ap_page.ah_value[6] = mmp_adp_get_wgt_hdl(WID_MMP_ADP_TXT_VALUE6);

    i4_ret = mmp_adp_update_text(ui2_g_lang);
    if (WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_adp_update_text() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif
    return (MMPR_OK);
}

static INT32 _mmp_com_ui_create_text_detail_page(HANDLE_T h_parent)
{
#if 0
    INT32                 i4_ret;

    i4_ret = mmp_tdp_create_ui(h_parent);
    if(WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_adp_create_ui() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    /*get detail page handle*/
    t_tp_page.h_page = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_FRM_DETAIL_PAGE);

    /*get wigdet handle*/
    t_tp_page.ah_label[0] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_LABEL0);
    t_tp_page.ah_label[1] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_LABEL1);
    t_tp_page.ah_label[2] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_LABEL2);
    t_tp_page.ah_label[3] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_LABEL3);

    t_tp_page.ah_value[0] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_VALUE0);
    t_tp_page.ah_value[1] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_VALUE1);
    t_tp_page.ah_value[2] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_VALUE2);
    t_tp_page.ah_value[3] = mmp_tdp_get_wgt_hdl(WID_MMP_TDP_TXT_VALUE3);

    i4_ret = mmp_tdp_update_text(ui2_g_lang);
    if (WDKR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("mmp_tdp_update_text() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
#endif
    return (MMPR_OK);
}

extern INT32 mmp_com_ui_create_detail_page_new(
    HANDLE_T                          h_parent,
    MMP_COM_UI_PLAYER_TYPE            e_player_type,
    void**                            ppt_dp_inst)
{
    MMP_COM_UI_DP_VIEW_PTR_T  pt_this = NULL;
    INT32                     i4_ret = MMPR_OK;

    pt_this = (MMP_COM_UI_DP_VIEW_PTR_T)c_mem_alloc(sizeof(MMP_COM_UI_DP_VIEW_T));
    if (NULL == pt_this)
    {
        return MMPR_OUT_OF_MEM;
    }
    pt_this->e_player_type = e_player_type;

    ui2_g_lang = _mmp_get_mlm_lang_id();

    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        i4_ret = _mmp_com_ui_create_vid_detail_page(h_parent);
        if(WDKR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("_mmp_com_ui_create_vid_detail_page() fail. i4_ret = %d.\r\n", i4_ret));
        }

    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        i4_ret = _mmp_com_ui_create_pho_detail_page(h_parent);
        if(WDKR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("_mmp_com_ui_create_pho_detail_page() fail. i4_ret = %d.\r\n", i4_ret));
        }
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        i4_ret = _mmp_com_ui_create_aud_detail_page(h_parent);
        if(WDKR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("_mmp_com_ui_create_aud_detail_page() fail. i4_ret = %d.\r\n", i4_ret));
        }
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        i4_ret = _mmp_com_ui_create_text_detail_page(h_parent);
        if(WDKR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("_mmp_com_ui_create_aud_detail_page() fail. i4_ret = %d.\r\n", i4_ret));
        }
    }
        break;

    default:
        break;
    }

    if(WDKR_OK != i4_ret)
    {
        if (NULL != pt_this)
        {
            c_mem_free(pt_this);
            pt_this = NULL;
        }
    }
    else
    {
        *ppt_dp_inst = pt_this;
    }

    return i4_ret;
}

extern INT32 mmp_com_ui_dp_destroy(VOID *pv_dp_inst)
{
    MMP_COM_UI_DP_VIEW_T *pt_this = NULL;

    if (NULL == pv_dp_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = pv_dp_inst;

    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        mmp_vdp_destroy_ui();
    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        mmp_pdp_destroy_ui();
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        //mmp_adp_destroy_ui();
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        //mmp_tdp_destroy_ui();
    }
        break;

    default:
        break;
    }
    
    c_mem_free(pt_this);
    return MMPR_OK;
}

extern INT32 mmp_com_ui_dp_view_active(VOID *pv_dp_inst)
{
    MMP_COM_UI_DETAIL_PAGE_T *pt_page = NULL;
    MMP_COM_UI_DP_VIEW_T *pt_this = NULL;
    INT32 i4_ret;

    if (NULL == pv_dp_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = pv_dp_inst;
    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        pt_page = &t_vp_page;
    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        pt_page = &t_pp_page;
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        pt_page = &t_ap_page;
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        pt_page = &t_tp_page;
    }
        break;

    default:
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_page->h_page, WGL_SW_RECURSIVE);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_visibility() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_insert(pt_page->h_page,
                 NULL_HANDLE,
                 WGL_INSERT_TOPMOST,
                 WGL_NO_AUTO_REPAINT);
	if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_insert() fail. i4_ret = %d.\r\n", i4_ret));
    }

    i4_ret = c_wgl_repaint(pt_page->h_page, NULL, TRUE);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_show() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

extern INT32 mmp_com_ui_dp_view_inactive(VOID *pv_dp_inst)
{
    MMP_COM_UI_DETAIL_PAGE_T *pt_page = NULL;
    MMP_COM_UI_DP_VIEW_T *pt_this = NULL;
    INT32 i4_ret;

    if (NULL == pv_dp_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = pv_dp_inst;
    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        pt_page = &t_vp_page;
    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        pt_page = &t_pp_page;
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        pt_page = &t_ap_page;
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        pt_page = &t_tp_page;
    }
        break;

    default:
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_page->h_page, WGL_SW_HIDE);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_visibility() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_page->h_page, NULL, TRUE);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_show() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

extern INT32 mmp_com_ui_dp_set_text(VOID *pv_dp_inst,
                                  MMP_DP_LBL_ID_T e_item_idx,
                                  UTF16_T* ws_value)
{
    MMP_COM_UI_DP_VIEW_T *pt_this = NULL;
    MMP_COM_UI_DETAIL_PAGE_T *pt_page = NULL;
    INT32 i4_txt_id = 0, i4_ret = MMPR_OK;

    if (NULL == pv_dp_inst)
    {
        return MMPR_FAIL;
    }

    pt_this = pv_dp_inst;

    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        i4_txt_id = e_item_idx - MMP_VP_RC_DP_LBL_ID_TITLE;
        pt_page = &t_vp_page;
    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        i4_txt_id = e_item_idx - MMP_PP_RC_DP_LBL_ID_ALBM;
        pt_page = &t_pp_page;
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        i4_txt_id = e_item_idx - MMP_AP_RC_DP_LBL_ID_TITLE;
        pt_page = &t_ap_page;
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        i4_txt_id = e_item_idx - MMP_TP_RC_DP_LBL_ID_ALBUM;
        pt_page = &t_tp_page;
    }
        break;

    default:
        return MMPR_FAIL;
    }

    if(i4_txt_id >= MMP_PP_RC_DP_LBL_COUNT)
    {
       i4_txt_id = MMP_PP_RC_DP_LBL_COUNT - 1;
    }
    else if(i4_txt_id <= 0)
    {
    i4_txt_id = 0;
    }

    i4_ret = c_wgl_do_cmd(pt_page->ah_value[i4_txt_id],
                  WGL_CMD_TEXT_SET_TEXT,
                  WGL_PACK(ws_value),
                  WGL_PACK((UINT16)0xFFFF));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    switch(pt_this->e_repaint)
    {
    case COM_UI_SYNC_REPAINT:
    {
        i4_ret = c_wgl_repaint(pt_page->ah_value[i4_txt_id],NULL,TRUE);
    }
        break;

    case COM_UI_ASYNC_REPAINT:
    {
        i4_ret = c_wgl_repaint(pt_page->ah_value[i4_txt_id],NULL,FALSE);
    }
        break;

    default:
        break;
    }

    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_repaint() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }
    return MMPR_OK;
}

extern INT32 mmp_com_ui_dp_set_text_ex(VOID *pv_dp_inst,
                                      MMP_DP_LBL_ID_T e_item_idx,
                                      UTF16_T* ws_value,
                                      MMP_COM_UI_WGT_REPAINT e_repaint_type)
{
    MMP_COM_UI_DP_VIEW_T *pt_this = NULL;
    MMP_COM_UI_DETAIL_PAGE_T *pt_page = NULL;
    INT32 i4_txt_id = 0, i4_ret = MMPR_OK;

    if (NULL == pv_dp_inst)
    {
        return MMPR_FAIL;
    }

    pt_this = pv_dp_inst;

    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        i4_txt_id = e_item_idx - MMP_VP_RC_DP_LBL_ID_TITLE;
        pt_page = &t_vp_page;
    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        i4_txt_id = e_item_idx - MMP_PP_RC_DP_LBL_ID_ALBM;
        pt_page = &t_pp_page;
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        i4_txt_id = e_item_idx - MMP_AP_RC_DP_LBL_ID_TITLE;
        pt_page = &t_ap_page;
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        i4_txt_id = e_item_idx - MMP_TP_RC_DP_LBL_ID_ALBUM;
        pt_page = &t_tp_page;
    }
        break;

    default:
        return MMPR_FAIL;
    }

    if(i4_txt_id >= MMP_PP_RC_DP_LBL_COUNT)
    {
       i4_txt_id = MMP_PP_RC_DP_LBL_COUNT - 1;
    }
    else if(i4_txt_id <= 0)
    {
    i4_txt_id = 0;
    }

    i4_ret = c_wgl_do_cmd(pt_page->ah_value[i4_txt_id],
                  WGL_CMD_TEXT_SET_TEXT,
                  WGL_PACK(ws_value),
                  WGL_PACK((UINT16)0xFFFF));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    switch(e_repaint_type)
    {
    case COM_UI_SYNC_REPAINT:
    {
        i4_ret = c_wgl_repaint(pt_page->ah_value[i4_txt_id],NULL,TRUE);
    }
        break;

    case COM_UI_ASYNC_REPAINT:
    {
        i4_ret = c_wgl_repaint(pt_page->ah_value[i4_txt_id],NULL,FALSE);
    }
        break;

    default:
        break;
    }

    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_repaint() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

extern INT32 mmp_com_ui_dp_view_active_ex(VOID *pv_dp_inst,
                                        MMP_COM_UI_WGT_REPAINT e_repaint_type)
{
    MMP_COM_UI_DETAIL_PAGE_T *pt_page = NULL;
    MMP_COM_UI_DP_VIEW_T *pt_this = NULL;
    INT32 i4_ret=0;

    if (NULL == pv_dp_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = pv_dp_inst;
    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        pt_page = &t_vp_page;
    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        pt_page = &t_pp_page;
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        pt_page = &t_ap_page;
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        pt_page = &t_tp_page;
    }
        break;

    default:
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_page->h_page, WGL_SW_RECURSIVE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret =c_wgl_insert(
                pt_page->h_page,
                NULL_HANDLE,
                WGL_INSERT_TOPMOST,
                WGL_NO_AUTO_REPAINT
                );
    MMPR_LOG_ON_FAIL(i4_ret);

    switch(e_repaint_type)
    {
    case COM_UI_SYNC_REPAINT:
    {
        i4_ret = c_wgl_repaint(pt_page->h_page, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
        break;

    case COM_UI_ASYNC_REPAINT:
    {
        i4_ret = c_wgl_repaint(pt_page->h_page, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
        break;

    default:
    {

    }
        break;
    }

    return MMPR_OK;
}

extern INT32 mmp_com_ui_dp_view_inactive_ex(VOID *pv_dp_inst,
                                          MMP_COM_UI_WGT_REPAINT e_repaint_type)
{
    MMP_COM_UI_DETAIL_PAGE_T *pt_page = NULL;
    MMP_COM_UI_DP_VIEW_T *pt_this = NULL;
    INT32 i4_ret;

    if (NULL == pv_dp_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = pv_dp_inst;
    switch(pt_this->e_player_type)
    {
    case COM_UI_DTL_PG_VIDEO:
    {
        pt_page = &t_vp_page;
    }
        break;

    case COM_UI_DTL_PG_PHOTO:
    {
        pt_page = &t_pp_page;
    }
        break;

    case COM_UI_DTL_PG_AUDIO:
    {
        pt_page = &t_ap_page;
    }
        break;

    case COM_UI_DTL_PG_TEXT:
    {
        pt_page = &t_tp_page;
    }
        break;

    default:
        return MMPR_FAIL;
    }

    if(NULL!=pt_page)
    {
        i4_ret = c_wgl_set_visibility(pt_page->h_page, WGL_SW_HIDE);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_set_visibility() fail. i4_ret = %d.\r\n", i4_ret));
            return MMPR_FAIL;
        }

        switch(e_repaint_type)
        {
        case COM_UI_SYNC_REPAINT:
        {
            i4_ret = c_wgl_repaint(pt_page->h_page, NULL, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;

        case COM_UI_ASYNC_REPAINT:
        {
            i4_ret = c_wgl_repaint(pt_page->h_page, NULL, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;

        default:
        {

        }
            break;
        }
    }

    return MMPR_OK;
}


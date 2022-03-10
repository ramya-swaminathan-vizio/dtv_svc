/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright(C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights(including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights(including without limitation, patent, copyright, and      *
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
 * of certain softwares relating to Receiver's product(s)(the "Services").   *
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
 * then current rules of the International Chamber of Commerce(ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#include "wizard/wzd.h"
#include "app_util/config/_acfg.h"
#include "wdk/a_vkb.h"
#include "wizard/wzd_dbg.h"

#define  HELP_HPR_TXT_X                      (0 * WZD_UI_RATIO_W)
#define  HELP_HPR_TXT_Y                      (540 * WZD_UI_RATIO_W)
#define  HELP_HPR_TXT_W                      (MAIN_FRM_W)
#define  HELP_HPR_TXT_H                      (80 * WZD_UI_RATIO_W)

 typedef enum _WZD_CON_TV_STEP_E
{
   WZD_CON_TV_LANG = 0,
   WZD_CON_TV_COUNTRY,
   WZD_CON_TV_CHO_MODE,
   WZD_CON_TV_END
}WZD_CON_TV_STEP_E;

 typedef enum _LANG_LB_NUM_T
 {
    _LANG_LB_ENG = 0,
    _LANG_LB_FRE,
    _LANG_LB_SPA,
    _LANG_LB_MAX_ITEM
 }LANG_LB_NUM_T;

 typedef struct _WZD_CON_TV_MEMBER_T
 {
    HANDLE_T                    h_hypetext_help_info;
    UINT8                       ui1_page_id;
    UINT8                       ui1_sel_box_idx;
 }WZD_CON_TV_MEMBER_T;

 typedef enum _CONTENT_LB_NUM_T
 {
    _CONTENT_LB_BEGIN = 0,
    _CONTENT_LB_RETAIL,
    _CONTENT_LB_MAX_ITEM
 }CONTENT_LB_NUM_T;


static WZD_CON_TV_MEMBER_T gt_con_tv;

static INT32 _wzd_page_con_tv_hpr_txt_update(UTF16_T* pw2s_text,
                                              WGL_HIMG_TPL_T h_img);
static INT32 _wzd_page_con_tv_update(BOOL b_repaint);
static VOID _wzd_page_lang_country_sel_box_nfy(
                    UINT32          ui4_msg,
                    VOID*           pv_param1,
                    VOID*           pv_param2);

/*----------------------------------------------------------------------------
* Name: 
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
static INT32 _wzd_page_con_tv_set_lang(LANG_LB_NUM_T e_lang_index)
{
    ISO_639_LANG_T      s639_lang;

    if(_LANG_LB_ENG == e_lang_index)
    {
        a_cfg_set_gui_lang(s639_app_cfg_lang_eng);
    }
    else if(_LANG_LB_SPA == e_lang_index)
    {
        a_cfg_set_gui_lang(s639_app_cfg_lang_spa);
    }
    else if(_LANG_LB_FRE == e_lang_index)
    {
        a_cfg_set_gui_lang(s639_app_cfg_lang_fre);
    }

    RET_ON_ERR(a_cfg_get_gui_lang(s639_lang));
    RET_ON_ERR(wzd_set_gui_lang(s639_lang));
	
	a_vkb_set_lang(s639_lang);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
* Name: 
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
static INT32 _wzd_page_con_tv_update(BOOL b_repaint)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    WZD_VIEW_SEL_BOX_INFO_T     t_info_data;
    c_memset(&t_info_data, 0, sizeof(t_info_data));
    t_info_data.ui4_index_total = 3;
    t_info_data.pf_data_chg_nfy = _wzd_page_lang_country_sel_box_nfy;
    wzd_view_sel_box_set_info_data(&t_info_data);

    wzd_get_subpage_id(&pt_this->ui1_page_id);

    if(WZD_CON_TV_LANG == pt_this->ui1_page_id)
    {
        RET_ON_ERR(wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_LANG_TITLE_2), NULL_HANDLE));
        RET_ON_ERR(wzd_view_footer_set_btn_num(0));
        RET_ON_ERR(c_wgl_set_visibility(pt_this->h_hypetext_help_info, WGL_SW_NORMAL));
        RET_ON_ERR(_wzd_page_con_tv_hpr_txt_update(WZD_TEXT(MLM_WZD_KEY_LANG_HELP), h_g_wzd_img_network_lock));
        wzd_view_sel_box_set_text(0, MLM_WZD_TEXT(0, wzd_get_validate_key(MLM_WZD_KEY_LANG_1)));
        wzd_view_sel_box_set_text(1, MLM_WZD_TEXT(1, wzd_get_validate_key(MLM_WZD_KEY_LANG_2)));
        wzd_view_sel_box_set_text(2, MLM_WZD_TEXT(2, wzd_get_validate_key(MLM_WZD_KEY_LANG_3)));
        wzd_view_sel_box_set_focus(0, FALSE);
        RET_ON_ERR(wzd_view_sel_box_show(TRUE));
        pt_this->ui1_sel_box_idx = 0;
    }
    else if(WZD_CON_TV_COUNTRY == pt_this->ui1_page_id)
    {
        RET_ON_ERR(wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_COUNTRY_TITLE), NULL_HANDLE));
        RET_ON_ERR(wzd_view_footer_set_btn_num(0));
        RET_ON_ERR(_wzd_page_con_tv_hpr_txt_update(WZD_TEXT(MLM_WZD_KEY_COUNTRY_HELP), h_g_wzd_img_network_lock));
        RET_ON_ERR(c_wgl_set_visibility(pt_this->h_hypetext_help_info, WGL_SW_NORMAL));
        wzd_view_sel_box_set_focus(0, FALSE);
        RET_ON_ERR(wzd_view_sel_box_show(TRUE));
        wzd_view_sel_box_set_text(0, WZD_TEXT(MLM_WZD_KEY_COUNTRY_USA));
        wzd_view_sel_box_set_text(1, WZD_TEXT(MLM_WZD_KEY_COUNTRY_CA));
        wzd_view_sel_box_set_text(2, WZD_TEXT(MLM_WZD_KEY_COUNTRY_MEX));
        pt_this->ui1_sel_box_idx = 0;
    }

    if(b_repaint)
    {
        RET_ON_ERR(wzd_view_main_frm_repaint());
    }

    return WZDR_OK;
}

 /*----------------------------------------------------------------------------
 * Name: _wzd_page_con_tv_create_help_txt
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
static INT32 _wzd_page_con_tv_create_help_txt(VOID)
{
    GL_RECT_T                   t_rect;
    INT32                       i4_ret = WZDR_OK;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    WGL_HTS_PARAG_ATTR_T        t_parag;
    HANDLE_T                    h_layout_frm = NULL_HANDLE;
    CHAR*                       s_font_name = wzd_view_get_font_name();

    wzd_view_get_layout_frm(&h_layout_frm);

    SET_RECT_BY_SIZE(&t_rect,
                      (INT32)HELP_HPR_TXT_X,
                      (INT32)HELP_HPR_TXT_Y,
                      (INT32)HELP_HPR_TXT_W,
                      (INT32)HELP_HPR_TXT_H);
    
    c_memset(&t_init, 0, sizeof(WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  =(UINT16)0;

    /* set default font */
    c_strcpy(t_init.t_font_info_dft.a_c_font_name, s_font_name);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_LARGE;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    /* create hyper text widget */
    i4_ret = c_wgl_create_widget(h_layout_frm,
                                   HT_WGL_WIDGET_HTS,
                                   WGL_CONTENT_HTS_DEF,
                                   WGL_BORDER_NULL,
                                   &t_rect,
                                   NULL,
                                   255,
                                  (VOID*)(&t_init),
                                   NULL,
                                   &pt_this->h_hypetext_help_info);
    RET_ON_ERR(i4_ret);

    /* set content inset */
    t_inset.i4_left   = 10;
    t_inset.i4_right  = 10;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd(pt_this->h_hypetext_help_info,
                            WGL_CMD_HTS_SET_CNT_INSET,
                            WGL_PACK(&t_inset),
                            NULL);
    RET_ON_ERR(i4_ret);

    /* set justification */
    i4_ret = c_wgl_do_cmd(pt_this->h_hypetext_help_info,
                            WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                            WGL_PACK(WGL_HTS_JUSTIF_CENTER),
                            NULL);
    RET_ON_ERR(i4_ret);
    
    c_memset(&t_parag, 0, sizeof(WGL_HTS_PARAG_ATTR_T));
    t_parag.e_justif = WGL_HTS_JUSTIF_CENTER;
    t_parag.ui2_indent = 0;
    t_parag.i4_line_gap_bottom = 2;
    t_parag.i4_line_gap_top = 0;
    t_parag.ui2_parag_gap_bottom = 0;
    t_parag.ui2_parag_gap_top = 0;
    i4_ret = c_wgl_do_cmd(pt_this->h_hypetext_help_info,
                            WGL_CMD_HTS_CUR_PARAG_SET,
                           WGL_PACK(&t_parag),
                           NULL);
    RET_ON_ERR(i4_ret);
     
    return  i4_ret;
}

static UTF16_T* _wzd_w2s_sch(UTF16_T*        pw2s_text,
                             const UTF16_T*  pw2s_sub_text)
{
    UTF16_T*   pw2s_start = NULL;
    SIZE_T     t_cmp_offset = 0;
    SIZE_T     t_txt_size = 0;
    SIZE_T     t_sub_txt_size = 0;
    if(!pw2s_text ||
        !pw2s_sub_text)
    {
        return(pw2s_start);
    }

    t_txt_size = c_uc_w2s_strlen(pw2s_text);
    t_sub_txt_size = c_uc_w2s_strlen(pw2s_sub_text);

    if(t_txt_size < t_sub_txt_size)
    {
        return(pw2s_start);
    }

    pw2s_start = pw2s_text;

    while(pw2s_start <= pw2s_text + t_txt_size - t_sub_txt_size)
    {
        t_cmp_offset = 0;
        while(t_cmp_offset < t_sub_txt_size)
        {
            if(*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
            {
                t_cmp_offset++;
            }
            else
            {
                break;
            }
        }
        if(t_cmp_offset == t_sub_txt_size)
        {
            return(pw2s_start);
        }
        pw2s_start++;
    }

    return(NULL);
}

/*----------------------------------------------------------------------------
* Name: _wzd_page_con_tv_hpr_txt_update
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
static INT32 _wzd_page_con_tv_hpr_txt_update(UTF16_T* pw2s_text,
                                              WGL_HIMG_TPL_T h_img)
{
    INT32                  i4_ret = WZDR_OK;
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    UINT16                 ui2_sec_id = 0;
    UINT16                 ui2_pic_idx = 0;
    WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
    WGL_HTS_IMG_INFO_T     t_hts_img_info;
    UTF16_T                w2s_pic_flag[3 + 1];
    UTF16_T*               pw2s_next = NULL;
    UTF16_T*               pw2s_temp = pw2s_text;
    GL_COLOR_T             t_color_desc_txt = {255, {255}, {255}, {255}};
    GL_COLOR_T             t_color_desc_txt_bk = {0, {0}, {0}, {0}};

    c_memset(&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
    c_memset(&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
    c_memset(w2s_pic_flag, 0, sizeof(w2s_pic_flag));

    i4_ret = c_wgl_do_cmd(pt_this->h_hypetext_help_info,
                           WGL_CMD_HTS_CLEAR_ALL,
                           WGL_PACK(FALSE),
                           NULL);
    RET_ON_ERR(i4_ret);
    
    /* Set font data. */
    c_strcpy(t_hts_txt_info.t_font.a_c_font_name, wzd_view_get_font_name());
    t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_LARGE;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

    /* Set text background color. */
    c_memcpy(&t_hts_txt_info.t_clr_text, 
             &t_color_desc_txt, 
             sizeof(GL_COLOR_T));
    c_memcpy(&t_hts_txt_info.t_clr_text_bk, 
             &t_color_desc_txt_bk, 
             sizeof(GL_COLOR_T));

    c_uc_ps_to_w2s("%p", w2s_pic_flag, sizeof(w2s_pic_flag));

    pw2s_next = _wzd_w2s_sch(pw2s_temp, w2s_pic_flag);
    while(pw2s_next)
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) *(pw2s_next - pw2s_temp);

        i4_ret = c_wgl_do_cmd(pt_this->h_hypetext_help_info,
                               WGL_CMD_HTS_APPEND_TEXT_SEC,
                               WGL_PACK(&t_hts_txt_info),
                               WGL_PACK(&ui2_sec_id));
        RET_ON_ERR(i4_ret);

        t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

        if(0 == ui2_pic_idx)
        {
            t_hts_img_info.h_img = h_img;
        }

        i4_ret = c_wgl_do_cmd(pt_this->h_hypetext_help_info,
                               WGL_CMD_HTS_APPEND_IMG_SEC,
                               WGL_PACK(&t_hts_img_info),
                               WGL_PACK(&ui2_sec_id));
        RET_ON_ERR(i4_ret);

        pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
        pw2s_next = _wzd_w2s_sch(pw2s_temp, w2s_pic_flag);
    }

    if(pw2s_temp < pw2s_text + c_uc_w2s_strlen(pw2s_text))
    {
        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
        t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

        i4_ret = c_wgl_do_cmd(pt_this->h_hypetext_help_info,
                               WGL_CMD_HTS_APPEND_TEXT_SEC,
                               WGL_PACK(&t_hts_txt_info),
                               WGL_PACK(&ui2_sec_id));
        RET_ON_ERR(i4_ret);
    }

    return i4_ret;
}

static INT32 _lang_country_select(VOID)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;
    ACFG_COUNTRY_CODE_T         e_country_type = ACFG_COUNTRY_CODE_US;
    UINT16                      ui2_acr_value = ACFG_ACR_OFF;
    
    if(WZD_CON_TV_LANG == pt_this->ui1_page_id)
    {
        if(0 == pt_this->ui1_sel_box_idx)
        {
            _wzd_page_con_tv_set_lang(_LANG_LB_ENG);
        }
        else if(1 == pt_this->ui1_sel_box_idx)
        {
            _wzd_page_con_tv_set_lang(_LANG_LB_FRE);
        }
        else if(2 == pt_this->ui1_sel_box_idx)
        {
            _wzd_page_con_tv_set_lang(_LANG_LB_SPA);
        }

        wzd_set_subpage_id((UINT8)WZD_CON_TV_COUNTRY);
      //  _wzd_page_con_tv_update(TRUE);
        wzd_page_goto(WZD_PAGE_NAVI_NEXT_PAGE);
    }
    else if(WZD_CON_TV_COUNTRY == pt_this->ui1_page_id)
    {
        if(0 == pt_this->ui1_sel_box_idx)
        {
            e_country_type = ACFG_COUNTRY_CODE_US;
            ui2_acr_value = ACFG_ACR_ON;
        }
        else if(1 == pt_this->ui1_sel_box_idx)
        {
            e_country_type = ACFG_COUNTRY_CODE_CA;
            ui2_acr_value = ACFG_ACR_OFF;
        }
        else if(2 == pt_this->ui1_sel_box_idx)
        {
            e_country_type = ACFG_COUNTRY_CODE_MEX;
            ui2_acr_value = ACFG_ACR_OFF;
        }
        a_cfg_custom_set_country_code(e_country_type);
        a_cfg_custom_set_acr(ui2_acr_value);

        wzd_page_goto(WZD_PAGE_NAVI_NEXT_PAGE);
        acfg_set_default(IDX_DPMS);
    }

    return WZDR_OK;
}

static VOID _wzd_page_lang_country_sel_box_nfy(
                     UINT32          ui4_msg,
                     VOID*           pv_param1,
                     VOID*           pv_param2)
{
    WZD_CON_TV_MEMBER_T*        pt_this = &gt_con_tv;

    DBG_LOG_PRINT(("\n[WZD] %s,%s,%d,ui1_sel_box_idx=%d,pv_param1=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_this->ui1_sel_box_idx,
                (UINT32)pv_param1));

    switch(ui4_msg)
    {
        case WZD_SEL_BOX_MSG_ITEM_FOCUSED:
        {
            pt_this->ui1_sel_box_idx = (UINT8)(UINT32)pv_param1;
            wzd_view_sel_box_frm_repaint();
        }
            break;

        case WZD_SEL_BOX_MSG_KEY_INPUT:
        {
            if(BTN_SELECT ==(UINT32)pv_param1)
            {
                _lang_country_select();
            }
        }
            break;

        default:
            break;
    }
}

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
static INT32 _wzd_page_con_tv_create(VOID)
{
    c_memset(&gt_con_tv, 0, sizeof(WZD_CON_TV_MEMBER_T));

    RET_ON_ERR(_wzd_page_con_tv_create_help_txt());
    
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

    if(pt_this->h_hypetext_help_info)
    {
        c_wgl_destroy_widget_ex(pt_this->h_hypetext_help_info, FALSE) ;
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
static INT32 _wzd_page_con_tv_on_show(
    UINT32                      ui4_page_id
   )
{
    DBG_LOG_PRINT(("[WZD] _wzd_page_con_tv_on_show() called. \n"));
    
    wzd_set_subpage_id((UINT8)WZD_CON_TV_LANG);
    RET_ON_ERR(_wzd_page_con_tv_update(FALSE));

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
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_con_tv_get_page_info_data
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
INT32 wzd_page_con_tv_get_page_info_data(WZD_PAGE_INFO_DATA_T* pt_info_data)
{
    c_memset(pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T));

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_LANG_TITLE_2;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_LOC_DESC_TITLE;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = NULL;
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
#endif




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
 * $RCSfile: wzd_page_dvbs.c,v $
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

#ifdef APP_DVBS_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_satl.h"

#include "scan_maps/dvbs_scan_maps.h"

#include "wizard/wzd.h"
#include "wizard/wzd_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define COUNTRY_NUM                             (32)

#define _MAX_ELEM_ITEM_NUM                      (32)

#define INPUT_RESET_DELAY                       ((UINT32) 1500)

#define WZD_RET_ON_ERR(_ret)  \
        do{ \
        INT32 ret = _ret;   \
        if (ret < 0)   \
        {   \
            DBG_ERROR (("<WZD> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
            return WZDR_FAIL;  \
        }   \
        }while(FALSE)
        
#define WZD_LOG_ON_ERR(_ret)  \
        do{ \
        INT32 ret = _ret;   \
        if (ret < 0)   \
        {   \
            DBG_ERROR (("<WZD> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
        }   \
        }while(FALSE)
        
#define WZD_BREAK_ON_ERR(_ret)  \
        { \
        INT32 ret = _ret;   \
        if (ret < 0)   \
        {   \
            DBG_ERROR (("<WZD> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
            break;  \
        } \
        }

typedef enum
{
    _ITEM_LB_SAT_LST = 0 ,      /* satellite list */
    _ITEM_LB_LNB_FREQ ,         /* LNB frequence */
    _ITEM_LB_DISEQC_IPT ,       /* diseqc_input */
#if 0    
    _ITEM_LB_TRANSPONDER ,      /* transponder */
#endif    
    _ITEM_LB_CHANNLES ,         /* channels */
    _ITEM_LB_SCAN_MODE ,        /* scan mode */
    _ITEM_LB_NET_SEARCH ,       /* network search */
    _ITEM_LAST_ENTRY
    
}_WZD_DVBS_PAGE_ITEM_T ;

typedef enum
{
    _DISEQC_DISABLE = 0 ,
    _DISEQC_4X1_A ,
    _DISEQC_4X1_B ,
    _DISEQC_4X1_C ,
    _DISEQC_4X1_D ,
    _DISEQC_PORT_LAST_ENTRY
    
}_DISEQC_PORT_T ;
/*-----------------------------------------------------------------------------
                    static function declaraions
-----------------------------------------------------------------------------*/
static INT32 _adjust_view(VOID) ;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static HANDLE_T                 h_layout_frm = NULL_HANDLE ;
static HANDLE_T                 ah_items[_ITEM_LAST_ENTRY] = {0} ;
static BOOL                     ab_item_disable[_ITEM_LAST_ENTRY] = {0} ;
static GL_RECT_T                t_rect_border_title = 
                                {
                                    _WZD_DVBS_ITEM_BAR_CNT_INSET_L + _WZD_DVBS_ITEM_ICON_W, 
                                    0, 
                                    _WZD_DVBS_ITEM_BAR_CNT_INSET_L + _WZD_DVBS_ITEM_ICON_W + _WZD_DVBS_ITEM_TITLE_W, 
                                    _WZD_DVBS_GRID_H
                                } ;
static WGL_INSET_T              t_inset_list_body = 
                                {
                                    _WZD_DVBS_ITEM_BAR_CNT_INSET_L + _WZD_DVBS_ITEM_ICON_W + _WZD_DVBS_ITEM_TITLE_W, 
                                    _WZD_DVBS_ITEM_BAR_CNT_INSET_R, 
                                    0, 
                                    0
                                };
    
#ifdef __________________JUST_FOR_DIVISION
#endif 

#if 0
/*----------------------------------------------------------------------------
 * Name: _itoa
 *
 * Description: Interger to string utility function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static VOID _itoa (
    UTF16_T*        w2s_dst, 
    INT32           i4_src, 
    UINT32          ui4_dst_len)
{
    CHAR            s_buf[32] = {0} ;
    
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}
#endif

/*----------------------------------------------------------------------------
 * Name: _list_create
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
static INT32 _list_create(
    HANDLE_T                    h_parent,
    INT32                       i4_index,
    INT32                       ui2_max_elem_num,
    wgl_widget_proc_fct         pf_wdgt_proc,
    HANDLE_T*                   ph_widget
    )
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT16                      ui2_i;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_IMG_INFO_T              t_img_info ;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = _WZD_DVBS_ITEM_VALUE_W;
    at_cols[1].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_width        = _WZD_DVBS_ITEM_HINT_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = ui2_max_elem_num;
    t_lb_init.ui2_elem_size     = _WZD_DVBS_GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect, _WZD_DVBS_ITEM_BAR_INSET_L, 
                                 _WZD_DVBS_GRID_H * i4_index, 
                                 LAYOUT_FRM_W - _WZD_DVBS_ITEM_BAR_INSET_L - _WZD_DVBS_ITEM_BAR_INSET_R, 
                                 _WZD_DVBS_GRID_H);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return WZDR_FAIL ;
    }

    /* Set Insets */
    WZD_RET_ON_ERR (c_wgl_do_cmd (*ph_widget,
                                WGL_CMD_GL_SET_INSET,
                                &t_inset_list_body,
                                NULL)) ;

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    WZD_RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    WZD_RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    WZD_RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(1),
                          WGL_PACK(&t_inset));
    WZD_RET_ON_ERR(i4_ret);


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, WZD_FONT_NAME);
    t_fnt_info.e_font_size  = SETI_LB_COL_TEXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    WZD_RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    WZD_RET_ON_ERR(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_wzd_color_seti_lst_col_txt;
    t_lb_color.t_disable = t_g_wzd_color_seti_lst_col_dis_txt;
    t_lb_color.t_highlight = t_g_wzd_color_hlt_txt;
    t_lb_color.t_highlight_unfocus = t_g_wzd_color_seti_lst_col_txt;
    t_lb_color.t_pushed = t_g_wzd_color_seti_lst_col_txt;
    t_lb_color.t_selected = t_g_wzd_color_seti_lst_col_txt;
    t_lb_color.t_selected_disable = t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    WZD_RET_ON_ERR(i4_ret);

    t_lb_color.t_normal = t_g_wzd_color_seti_lst_elem_bk;
    t_lb_color.t_disable = t_g_wzd_color_seti_lst_elem_bk;
    t_lb_color.t_highlight = t_g_wzd_color_seti_lst_elem_bk;
    t_lb_color.t_highlight_unfocus = t_g_wzd_color_seti_lst_elem_bk;
    t_lb_color.t_pushed = t_g_wzd_color_seti_lst_elem_bk;
    t_lb_color.t_selected = t_g_wzd_color_seti_lst_elem_bk;
    t_lb_color.t_selected_disable = t_g_wzd_color_seti_lst_elem_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    WZD_RET_ON_ERR(i4_ret);

    for (ui2_i=0; ui2_i<2; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        WZD_RET_ON_ERR(i4_ret);
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_wzd_color_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    WZD_RET_ON_ERR(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    WZD_RET_ON_ERR(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_wzd_color_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    WZD_RET_ON_ERR(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_bk1;
    t_img_info.u_img_data.t_standard.t_disable = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    WZD_RET_ON_ERR(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    WZD_RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _list_set_content
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
static INT32 _list_set_content (
    HANDLE_T                    h_lb ,
    UTF16_T*                    pw2s_title ,
    UINT16                      ui2_elem_num ,
    UTF16_T*                    paw2s_elem_cont[]
    )
{
    UINT16                      ui2_i ;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_lr;

    WZD_RET_ON_ERR (c_wgl_do_cmd (h_lb ,
                                WGL_CMD_LB_DEL_ALL ,
                                NULL ,
                                NULL)) ;

    WZD_RET_ON_ERR (c_wgl_do_cmd (h_lb ,
                                WGL_CMD_LB_SET_ELEM_NUM,
                                WGL_PACK (ui2_elem_num),
                                NULL));

    /* set LB title */
    WZD_LOG_ON_ERR (c_wgl_do_cmd (h_lb , 
                                WGL_CMD_BDR_TIMG_SET_TITLE_TEXT, 
                                WGL_PACK(pw2s_title), 
                                WGL_PACK(c_uc_w2s_strlen(pw2s_title)))) ;
    
    /* Set LB elements */
    c_memset(&t_img_suit_lr, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_lr.h_normal                      = h_g_wzd_img_item_lr;
    t_img_suit_lr.h_disable                     = h_g_wzd_img_item_lr_disable;
    t_img_suit_lr.h_highlight                   = h_g_wzd_img_item_lr_hlt;
    t_img_suit_lr.h_highlight_unfocus           = h_g_wzd_img_item_lr;
    t_img_suit_lr.h_pushed                      = NULL_HANDLE;
    t_img_suit_lr.h_selected                    = h_g_wzd_img_item_lr;
    t_img_suit_lr.h_selected_disable            = h_g_wzd_img_item_lr_disable;
    t_img_suit_lr.h_selected_highlight          = h_g_wzd_img_item_lr_hlt;
    t_img_suit_lr.h_selected_highlight_unfocus  = h_g_wzd_img_item_lr;
    t_img_suit_lr.h_selected_pushed             = NULL_HANDLE;
    
    for (ui2_i = 0; ui2_i < ui2_elem_num; ui2_i ++)
    {
        WZD_RET_ON_ERR (c_wgl_do_cmd (h_lb , 
                                WGL_CMD_LB_SET_ITEM_TEXT, 
                                WGL_PACK_2(ui2_i, 0), 
                                WGL_PACK( paw2s_elem_cont[ui2_i]))) ;

        WZD_RET_ON_ERR (c_wgl_do_cmd(h_lb , 
                                WGL_CMD_LB_SET_ITEM_IMAGE_SUIT , 
                                WGL_PACK_2(ui2_i, 1), 
                                WGL_PACK(&t_img_suit_lr))) ;
    }

    return WZDR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _update_satellite_list
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
static INT32 _update_satellite_list (VOID)
{
    UINT16                      ui2_tmp_idx = 0 ;
    UINT16                      ui2_satl_rec_num = 0  ;
    SATL_REC_T                  t_satl_rec ;    
    UINT32                      ui4_ver_id = SATL_NULL_VER_ID ;
    UTF16_T*                    paw2s_elem_cont[32] = {0} ;
    UTF16_T                     w2s_tmp[32][32] = {0} ;
    INT32                       i4_ret = 0 ;

    /* get satellite record numbers */
    WZD_RET_ON_ERR (c_satl_get_num_recs (
                                t_g_wzd.h_satl, 
                                & ui2_satl_rec_num, 
                                & ui4_ver_id)) ;

    ASSERT_APPL(0, ui2_satl_rec_num != 0 , ("<WZD> ASSERT :%s:%d:%s\r\n", __FILE__, __LINE__, "\nxxxCan not belive!!!xxx\n"));
    
    c_satl_lock (t_g_wzd.h_satl) ;
    
    for (ui2_tmp_idx = 0 ; ui2_tmp_idx < ui2_satl_rec_num ; ui2_tmp_idx ++)
    {
        /* iterate all satellite records */
        i4_ret = c_satl_get_rec_by_rec_idx (
                                t_g_wzd.h_satl , 
                                ui2_tmp_idx , 
                                &t_satl_rec , 
                                &ui4_ver_id) ;
        
        /* get satellite name to fill the list */
        if (i4_ret != SATLR_OK)
        {
            paw2s_elem_cont[ui2_tmp_idx] = L"UNKNOWN" ;
        }
        else
        {
            c_uc_ps_to_w2s (t_satl_rec.ac_sat_name, w2s_tmp[ui2_tmp_idx], 31) ;
            paw2s_elem_cont[ui2_tmp_idx] = w2s_tmp[ui2_tmp_idx] ;
        }
    }
         
    c_satl_unlock (t_g_wzd.h_satl) ;

    /* update satellite information to the view */
    WZD_RET_ON_ERR (_list_set_content (
                                ah_items [_ITEM_LB_SAT_LST] ,
                                L"Satellite list",
                                ui2_satl_rec_num ,
                                paw2s_elem_cont)) ;

    return WZDR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _update_all_items_by_sate_rec
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
static INT32 _update_all_items_by_sate_rec (
    SATL_REC_T*                 pt_satl_rec
    )
{    
    UTF16_T*                    paw2s_elem_cont[32] = {0} ; 
    UTF16_T                     aw2s_tmp[32][32] = {0} ;
    CHAR                        s_tmp[32] = {0} ;
    UINT16                      ui2_hlt_idx = WGL_LB_NULL_INDEX ;
    UINT16                      ui2_elem_idx = 0 ;
    UINT16                      ui2_elem_num = 0 ;
    UINT16                      ui2_lnb_num = 0 ;
    SIZE_T                      z_size = 0 ;
    ISO_3166_COUNT_T            s_country_code;

    if (!pt_satl_rec)
    {
        return WZDR_INV_ARG ;
    }

    /* update LNB frequency */
    {
        a_cfg_get_country (s_country_code) ;
        z_size = sizeof (ui2_lnb_num) ;
        
        WZD_RET_ON_ERR (dvbs_scan_maps_fct (
                                DVBS_SCAN_MAPS_CMD_GET_NUM_DEFAULT_LNB_CONFIG,
                                s_country_code ,
                                NULL ,
                                (VOID*)&ui2_lnb_num,
                                &z_size)) ;
        ui2_elem_idx = 0 ;
        ui2_elem_num = MIN (ui2_lnb_num,32) ;
        ui2_hlt_idx  = 0 ;

        /* prepare content */
        for (ui2_elem_idx = 0 ;ui2_elem_idx <ui2_elem_num ;ui2_elem_idx ++)
        {
            z_size = sizeof (pt_satl_rec->ulnb.t_lnb) ;
            WZD_RET_ON_ERR (dvbs_scan_maps_fct (
                                DVBS_SCAN_MAPS_CMD_GET_DEFAULT_LNB_CONFIG,
                                s_country_code ,
                                (VOID*)ui2_elem_idx ,
                                (VOID*)&pt_satl_rec->ulnb.t_lnb,
                                &z_size)) ;

            if (LNB_SINGLE_FREQ == pt_satl_rec->ulnb.t_lnb.e_lnb_type)
            {
                c_snprintf (s_tmp, 32 -1, "%d", pt_satl_rec->ulnb.t_lnb.ui2_lnb_low_freq) ;
            }
            else if (
                LNB_DUAL_FREQ == pt_satl_rec->ulnb.t_lnb.e_lnb_type
                &&
                pt_satl_rec->ulnb.t_lnb.ui2_lnb_low_freq == 9750
                &&
                pt_satl_rec->ulnb.t_lnb.ui2_lnb_low_freq == 10600)
            {
                c_snprintf(s_tmp, 32 -1, "%s", "universal\0") ;
            }
            else if (
                LNB_DUAL_FREQ == pt_satl_rec->ulnb.t_lnb.e_lnb_type)
            {
                c_snprintf (s_tmp, 32 -1, "%d,%d", pt_satl_rec->ulnb.t_lnb.ui2_lnb_low_freq, pt_satl_rec->ulnb.t_lnb.ui2_lnb_high_freq) ;
            }
            else 
            {
                c_snprintf(s_tmp, 32 -1, "%s", "unknown\0") ;
            }

            c_uc_ps_to_w2s (s_tmp, aw2s_tmp[ui2_elem_idx], 32) ;
            paw2s_elem_cont[ui2_elem_idx] = aw2s_tmp[ui2_elem_idx] ;
        }

        /* set content */
        WZD_RET_ON_ERR (_list_set_content (ah_items [_ITEM_LB_LNB_FREQ] ,
                                WZD_TEXT (MLM_WZD_KEY_TITLE_LNB) ,
                                ui2_elem_num ,
                                paw2s_elem_cont)) ;

        /* highlight & visiable */
        WZD_LOG_ON_ERR (c_wgl_do_cmd (ah_items [_ITEM_LB_LNB_FREQ],
                                WGL_CMD_LB_HLT_ELEM_VISIBLE ,
                                WGL_PACK (ui2_hlt_idx),
                                WGL_PACK(0)));
    }
    
    /* update Diseqc input */
    {
        ui2_elem_idx = 0 ;
        ui2_elem_num = (UINT16)(_DISEQC_PORT_LAST_ENTRY) ;
        ui2_hlt_idx  = 0 ;

        ASSERT_APPL(0, ui2_hlt_idx < ui2_elem_num , ("<WZD> ASSERT :%s:%d:%s\r\n", __FILE__, __LINE__, "\nxxxCan not belive!!!xxx\n"));

        /* prepare content */
        for (ui2_elem_idx = 0 ;ui2_elem_idx <ui2_elem_num ;ui2_elem_idx ++)
        {
            paw2s_elem_cont[ui2_elem_idx] = WZD_TEXT (MLM_WZD_KEY_DISEQC_PORT_DISABLE + ui2_elem_idx) ;
        }
        
        /* set content */
        WZD_RET_ON_ERR (_list_set_content (ah_items [_ITEM_LB_DISEQC_IPT] ,
                                WZD_TEXT (MLM_WZD_KEY_TITLE_DISEQC),
                                ui2_elem_num ,
                                paw2s_elem_cont)) ;

        /* highlight & visiable */
        WZD_LOG_ON_ERR (c_wgl_do_cmd (ah_items [_ITEM_LB_DISEQC_IPT],
                                WGL_CMD_LB_HLT_ELEM_VISIBLE ,
                                WGL_PACK(ui2_hlt_idx),
                                WGL_PACK(0)));
    }

#if 0
    /* update Transponder */
    {
        WZD_RET_ON_ERR (_list_set_content (ah_items [_ITEM_LB_TRANSPONDER] ,
                                L"Transponder",
                                4 ,
                                paw2s_elem_cont)) ;
    }
#endif

    /* update channels */
    {
        ui2_elem_idx = 0 ;
        ui2_elem_num = 2 ;
        ui2_hlt_idx  = 0 ;

        /* prepare content */
        for (ui2_elem_idx = 0 ;ui2_elem_idx <ui2_elem_num ;ui2_elem_idx ++)
        {
            paw2s_elem_cont[ui2_elem_idx] = WZD_TEXT (MLM_WZD_KEY_CHANNELS_TYPE1 + ui2_elem_idx) ;
        }
        
        /* set content */
        WZD_RET_ON_ERR (_list_set_content (ah_items [_ITEM_LB_CHANNLES] ,
                                WZD_TEXT (MLM_WZD_KEY_TITLE_CHANNELS),
                                ui2_elem_num ,
                                paw2s_elem_cont)) ;

        /* highlight & visiable */
        WZD_LOG_ON_ERR (c_wgl_do_cmd (ah_items [_ITEM_LB_CHANNLES],
                                WGL_CMD_LB_HLT_ELEM_VISIBLE ,
                                WGL_PACK(ui2_hlt_idx),
                                WGL_PACK(0)));
    }

    /* update scan mode */
    {
        ui2_elem_idx = 0 ;
        ui2_elem_num = 2 ;
        ui2_hlt_idx  = 0 ;

        /* prepare content */
        for (ui2_elem_idx = 0 ;ui2_elem_idx <ui2_elem_num ;ui2_elem_idx ++)
        {
            paw2s_elem_cont[ui2_elem_idx] = WZD_TEXT (MLM_WZD_KEY_SCAN_MODE_TYPE1 + ui2_elem_idx) ;
        }
        
        /* set content */
        WZD_RET_ON_ERR (_list_set_content (ah_items [_ITEM_LB_SCAN_MODE] ,
                                WZD_TEXT (MLM_WZD_KEY_TITLE_SCAN_MODE),
                                ui2_elem_num ,
                                paw2s_elem_cont)) ;

        /* highlight & visiable */
        WZD_LOG_ON_ERR (c_wgl_do_cmd (ah_items [_ITEM_LB_SCAN_MODE],
                                WGL_CMD_LB_HLT_ELEM_VISIBLE ,
                                WGL_PACK(ui2_hlt_idx),
                                WGL_PACK(0)));

        /* we need disable network search item as the default scan mode is Auto */
        ab_item_disable[_ITEM_LB_NET_SEARCH] = TRUE ;
    }

    /* update Network search */
    {
        ui2_elem_idx = 0 ;
        ui2_elem_num = 2 ;
        ui2_hlt_idx  = 0 ;

        /* prepare content */
        for (ui2_elem_idx = 0 ;ui2_elem_idx <ui2_elem_num ;ui2_elem_idx ++)
        {
            paw2s_elem_cont[ui2_elem_idx] = WZD_TEXT (MLM_WZD_KEY_NW_SEARCH_TYPE1 + ui2_elem_idx) ;
        }
        
        /* set content */
        WZD_RET_ON_ERR (_list_set_content (ah_items [_ITEM_LB_NET_SEARCH] ,
                                WZD_TEXT (MLM_WZD_KEY_TITLE_NW_SEARCH),
                                ui2_elem_num ,
                                paw2s_elem_cont)) ;

        /* highlight & visiable */
        WZD_LOG_ON_ERR (c_wgl_do_cmd (ah_items [_ITEM_LB_NET_SEARCH],
                                WGL_CMD_LB_HLT_ELEM_VISIBLE ,
                                WGL_PACK(ui2_hlt_idx),
                                WGL_PACK(0)));
    }

    return WZDR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _lb_proc_fct
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
static INT32 _lb_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    UINT16                      ui2_idx       = 0 ;
    UINT32                      ui4_keycode   = 0 ;
    UINT16                      ui2_sate_idx  = 0 ;
    SATL_REC_T                  t_satl_rec    = {0} ;
    UINT32                      ui4_ver_id    = SATL_NULL_VER_ID ;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {   
        case BTN_CURSOR_LEFT :
        case BTN_CURSOR_RIGHT :
            /* we can get the correct index after invoking the default process */
            WZD_RET_ON_ERR (c_wgl_default_msg_proc (
                                h_widget, 
                                ui4_msg, 
                                param1, 
                                param2)) ;
            
            WZD_RET_ON_ERR (c_wgl_do_cmd(
                                h_widget,
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK(&ui2_idx),
                                NULL));

            /* satellite changed */
            if (h_widget == ah_items[_ITEM_LB_SAT_LST])
            {
                /* get selected satellite index */ 
                WZD_RET_ON_ERR (c_wgl_do_cmd(
                                ah_items[_ITEM_LB_SAT_LST],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK(&ui2_sate_idx),
                                NULL)) ;
                
                /* get corresponding record */
                WZD_RET_ON_ERR (c_satl_get_rec_by_rec_idx (
                                t_g_wzd.h_satl , 
                                ui2_sate_idx , 
                                &t_satl_rec , 
                                &ui4_ver_id)) ;
                
                /* update the information according the selected satellite */
                WZD_RET_ON_ERR (_update_all_items_by_sate_rec (&t_satl_rec)) ;

                WZD_RET_ON_ERR (_adjust_view ()) ;

                /* repatint */
                WZD_RET_ON_ERR (wzd_view_main_frm_repaint ()) ;
            }

            /* scan mode changed */
            if (h_widget == ah_items[_ITEM_LB_SCAN_MODE])
            {
                /* get selected satellite index */ 
                WZD_RET_ON_ERR (c_wgl_do_cmd(
                                ah_items[_ITEM_LB_SCAN_MODE],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK(&ui2_sate_idx),
                                NULL)) ;
                
                ab_item_disable[_ITEM_LB_NET_SEARCH] = (1 == ui2_sate_idx)  /* is Preset mode ? */
                                                     ? FALSE                /* does NOT disable network_search option */ 
                                                     : TRUE ;               /* Disable network_search option */ 

                WZD_RET_ON_ERR (_adjust_view ()) ;
                
                /* repatint */
                WZD_RET_ON_ERR (wzd_view_main_frm_repaint ()) ;
            }
        return WMPR_DONE ;
        
        case BTN_EXIT :
            /* Actually, this key is handled by call back function pf_nfy_sel.
             * which registered in wzd_page_lst_add_page function.
             */
        return WMPR_DONE;

        default :
        break ;
        }
    }
    break ;

    default:    
    break;        
    }
    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _adjust_view
 *
 * Description: Set the navigation
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
static INT32 _adjust_view(VOID)
{
    INT32                   i4_ret        = 0;
    UINT8                   ui1_i         = 0 ;
    UINT8                   ui1_j         = 0 ;
    HANDLE_T                h_owner       = 0 ;
    HANDLE_T                h_nav_up      = 0 ;
    HANDLE_T                h_nav_dn      = 0 ;
    WGL_KEY_LINK_T          at_key_lnk[2] = {0} ;
    UINT8                   aui1_tmp[_ITEM_LAST_ENTRY] = {0} ;

    /* count out all 'enabled' items(skip disabled items when pressing up/dn curson) */
    for (ui1_i = 0 ,ui1_j = 0 ;ui1_i <_ITEM_LAST_ENTRY ;ui1_i ++)
    {
        if (ab_item_disable[ui1_i])
        {
            /* disable this item */
            WZD_RET_ON_ERR (c_wgl_enable (ah_items[ui1_i] ,FALSE)) ;
        }
        else
        {
            /* enable this item */
            WZD_RET_ON_ERR (c_wgl_enable (ah_items[ui1_i] ,TRUE)) ;
            
            /* prepare to link this item with 'up/down' key */
            aui1_tmp[ui1_j++] = ui1_i ;
        }
        
        /* show this item */
        WZD_RET_ON_ERR (c_wgl_set_visibility (ah_items[ui1_i],WGL_SW_NORMAL)) ;     
    }

    /* link these items with 'up/down' key */
    for (ui1_i = 0 ;ui1_i < ui1_j ;ui1_i ++)
    {
        if (ui1_j == 1)
        {
            /* only one node */
            h_owner  = ah_items[aui1_tmp[ui1_i]] ;
            h_nav_up = ah_items[aui1_tmp[ui1_i]] ;
            h_nav_dn = ah_items[aui1_tmp[ui1_i]] ;
        }
        else if (ui1_i == 0)
        {
            /* first node */
            h_owner  = ah_items[aui1_tmp[ui1_i   ]] ;
            h_nav_up = ah_items[aui1_tmp[ui1_j -1]] ;
            h_nav_dn = ah_items[aui1_tmp[ui1_i +1]] ;
        }
        else if (ui1_i == ui1_j -1)
        {
            /* last node */
            h_owner  = ah_items[aui1_tmp[ui1_i   ]] ;
            h_nav_up = ah_items[aui1_tmp[ui1_i -1]] ;
            h_nav_dn = ah_items[aui1_tmp[0       ]] ;
        }
        else
        {   
            h_owner  = ah_items[aui1_tmp[ui1_i   ]] ;
            h_nav_up = ah_items[aui1_tmp[ui1_i -1]] ;
            h_nav_dn = ah_items[aui1_tmp[ui1_i +1]] ;
        }

        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = h_nav_up ;
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = h_nav_dn;
        i4_ret = c_wgl_set_navigation(h_owner, 2, at_key_lnk);
        WZD_RET_ON_ERR(i4_ret);
    }

    return WZDR_OK; 
}

#ifdef __________________JUST_FOR_DIVISION
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
INT32 wzd_page_dvbs_create (VOID)
{
    UINT16                      ui2_item_idx ;
    UINT16                      aui2_item_idxs[_ITEM_LAST_ENTRY] = {
                                _DVBS_ITEM_IDX_SAT_LST ,
                                _DVBS_ITEM_IDX_LNB_FREQ ,
                                _DVBS_ITEM_IDX_DISEQC_IPT ,
#if 0                                
                                _DVBS_ITEM_IDX_TRANSPONDER ,
#endif                                
                                _DVBS_ITEM_IDX_CHANNELS ,
                                _DVBS_ITEM_IDX_SCAN_MODE , 
                                _DVBS_ITEM_IDX_NET_SEARCH 
                                } ;
    
    WZD_RET_ON_ERR (wzd_view_get_layout_frm (&h_layout_frm)) ;
    
    /* lb scan mode */
    for (ui2_item_idx = 0 ;ui2_item_idx <_ITEM_LAST_ENTRY ;ui2_item_idx ++)
    {   
        WZD_RET_ON_ERR (_list_create (h_layout_frm,
                                aui2_item_idxs[ui2_item_idx] ,
                                _MAX_ELEM_ITEM_NUM , 
                                _lb_proc_fct ,
                                &ah_items[ui2_item_idx])) ;
    }

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
INT32 wzd_page_dvbs_dsty(VOID)
{
    UINT8   ui1_item_idx = 0 ;

    for (ui1_item_idx = 0 ;ui1_item_idx < _ITEM_LAST_ENTRY ;ui1_item_idx ++)
    {
        if (NULL_HANDLE != ah_items[ui1_item_idx])
        {   
            WZD_LOG_ON_ERR (c_wgl_destroy_widget_ex (ah_items[ui1_item_idx] ,FALSE)) ;
        }   
    }
        
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_on_show
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
INT32 wzd_page_dvbs_on_show (
    UINT32                      ui4_page_id
    )
{
    UINT16                      ui2_tmp_idx = 0 ;
    SATL_REC_T                  t_satl_rec = {0} ;    
    UINT32                      ui4_ver_id = SATL_NULL_VER_ID ;

    /* visiable all items */
    for (ui2_tmp_idx = 0 ; ui2_tmp_idx < _ITEM_LAST_ENTRY ; ui2_tmp_idx ++)
    {
        WZD_RET_ON_ERR (c_wgl_set_visibility (ah_items[ui2_tmp_idx] ,WGL_SW_NORMAL)) ;
    }

    /* update satellite list */
    WZD_RET_ON_ERR (_update_satellite_list ()) ;

    /* hlt first satellite in the list */
    WZD_LOG_ON_ERR (c_wgl_do_cmd (ah_items [_ITEM_LB_SAT_LST],
                                WGL_CMD_LB_HLT_ELEM_VISIBLE ,
                                WGL_PACK(0),
                                WGL_PACK(0)));

    /* set first satellite as default , get its record */
    WZD_RET_ON_ERR (c_satl_get_rec_by_rec_idx (
                                t_g_wzd.h_satl , 
                                0 , 
                                &t_satl_rec , 
                                &ui4_ver_id)) ;

    /* update the information according the selected satellite */
    WZD_RET_ON_ERR (_update_all_items_by_sate_rec (&t_satl_rec)) ;
    
    WZD_RET_ON_ERR (_adjust_view ()) ;

    /* adjust focus */  
    WZD_RET_ON_ERR (c_wgl_set_focus (ah_items[_ITEM_LB_SAT_LST] ,WGL_NO_AUTO_REPAINT)) ;

    /* reset help tip */    
    {
        RET_ON_ERR (wzd_view_help_lst_set_image (WZD_HELP_TYPE_BACK, FALSE));
        RET_ON_ERR (wzd_view_help_lst_set_text (WZD_HELP_TYPE_BACK, L""));

        RET_ON_ERR (wzd_view_help_lst_set_image (WZD_HELP_TYPE_SELECT_EX, TRUE));
        RET_ON_ERR (wzd_view_help_lst_set_text (WZD_HELP_TYPE_SELECT, WZD_TEXT (MLM_WZD_KEY_HELP_SELECT)));
        
        RET_ON_ERR (wzd_view_help_lst_set_image (WZD_HELP_TYPE_ENTER_EX, TRUE));
        RET_ON_ERR (wzd_view_help_lst_set_text (WZD_HELP_TYPE_ENTER, WZD_TEXT (MLM_WZD_KEY_HELP_ENTER)));
        
        RET_ON_ERR (wzd_view_help_lst_set_image (WZD_HELP_TYPE_EXIT, TRUE));
        RET_ON_ERR (wzd_view_help_lst_set_text (WZD_HELP_TYPE_EXIT, WZD_TEXT (MLM_WZD_KEY_HELP_EXIT)));
    }

    return WZDR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_on_hide
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
INT32 wzd_page_dvbs_on_hide(UINT32 ui4_page_id)
{
    UINT8   ui1_item_idx = 0 ;

    for (ui1_item_idx = 0 ;ui1_item_idx < _ITEM_LAST_ENTRY ;ui1_item_idx ++)
    {
        WZD_RET_ON_ERR (c_wgl_set_visibility (ah_items[ui1_item_idx] ,WGL_SW_HIDE)) ;
    }
        
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbs_get_scan_data
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
INT32 wzd_page_dvbs_get_scan_data (
    SB_DVBS_SCAN_DATA_T*        pt_dvbs_scan_data
    )
{
    ISO_3166_COUNT_T            s_country_code;
    UINT16                      ui2_hlt_idx     = 0 ;
    SATL_REC_T                  t_satl_rec = {0} ;    
    UINT32                      ui4_ver_id = SATL_NULL_VER_ID ;
    SIZE_T                      z_size = 0 ;

    if (!pt_dvbs_scan_data)
    {
        return WZDR_INV_ARG ;
    }

    /* find out selected satellite */
    WZD_RET_ON_ERR (c_wgl_do_cmd (ah_items[_ITEM_LB_SAT_LST],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK (&ui2_hlt_idx),
                                NULL)) ;        
    if (WGL_LB_NULL_INDEX == ui2_hlt_idx)
    {
        WZD_RET_ON_ERR (WZDR_FAIL) ;
    }

    /* get satellite record */
    WZD_RET_ON_ERR (c_satl_get_rec_by_rec_idx (
                                t_g_wzd.h_satl , 
                                ui2_hlt_idx , 
                                &t_satl_rec , 
                                &ui4_ver_id)) ;

    /* save the index of selected satellite to aconfig */
    a_cfg_set_crnt_satellite_rec_id (t_satl_rec.ui2_satl_rec_id) ;
    
    /* get country code */    
    {
        a_cfg_get_country (s_country_code) ;
        c_strncpy(pt_dvbs_scan_data->t_country_code ,s_country_code ,ISO_3166_COUNT_LEN) ;
    }

    /* get satellite id & satellite record id */    
    {        
        pt_dvbs_scan_data->t_scan_info.ui2_satl_id = LST_SAT_SATL_ID ;
        pt_dvbs_scan_data->t_scan_info.ui2_satl_rec_id = t_satl_rec.ui2_satl_rec_id ;
    }

    /* get LNB frequency & update related satellite record */
    /* get Diseqc input & update related satellite record */
    {
        /* get LNB */
        WZD_RET_ON_ERR (c_wgl_do_cmd (ah_items[_ITEM_LB_LNB_FREQ],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK (&ui2_hlt_idx),
                                NULL)) ;        
        if (WGL_LB_NULL_INDEX == ui2_hlt_idx)
        {
            WZD_RET_ON_ERR (WZDR_FAIL) ;
        }

        z_size = sizeof (t_satl_rec.ulnb.t_lnb) ;
        WZD_RET_ON_ERR (dvbs_scan_maps_fct (
                                DVBS_SCAN_MAPS_CMD_GET_DEFAULT_LNB_CONFIG,
                                s_country_code ,
                                (VOID*)ui2_hlt_idx ,
                                (VOID*)&t_satl_rec.ulnb.t_lnb,
                                &z_size)) ;

        /* get diseqc port */
        WZD_RET_ON_ERR (c_wgl_do_cmd (ah_items[_ITEM_LB_DISEQC_IPT],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK (&ui2_hlt_idx),
                                NULL)) ;        
        if (WGL_LB_NULL_INDEX == ui2_hlt_idx)
        {
            WZD_RET_ON_ERR (WZDR_FAIL) ;
        }

        /* currently ,we just support DISEQC_4X1 and DISEQC_NONE */
        switch ((_DISEQC_PORT_T)ui2_hlt_idx)
        {
        case _DISEQC_4X1_A :    /* diseqc A */
            t_satl_rec.udiseqc.t_diseqc_info.e_diseqc_type = DISEQC_4X1 ;
            t_satl_rec.udiseqc.t_diseqc_info.ui1_port = 1 ;
        break ;
        
        case _DISEQC_4X1_B :    /* diseqc B */
            t_satl_rec.udiseqc.t_diseqc_info.e_diseqc_type = DISEQC_4X1 ;
            t_satl_rec.udiseqc.t_diseqc_info.ui1_port = 2 ;
        break ;
        
        case _DISEQC_4X1_C :    /* diseqc C */
            t_satl_rec.udiseqc.t_diseqc_info.e_diseqc_type = DISEQC_4X1 ;
            t_satl_rec.udiseqc.t_diseqc_info.ui1_port = 3 ;
        break ;
        
        case _DISEQC_4X1_D :    /* diseqc D */
            t_satl_rec.udiseqc.t_diseqc_info.e_diseqc_type = DISEQC_4X1 ;
            t_satl_rec.udiseqc.t_diseqc_info.ui1_port = 4 ;
        break ;

        case _DISEQC_DISABLE :  /* diseqc disable */
        default :
            t_satl_rec.udiseqc.t_diseqc_info.e_diseqc_type = DISEQC_NONE ;
            t_satl_rec.udiseqc.t_diseqc_info.ui1_port = 0 ;
        break ;
        }

        /* update satl recoed */
        c_satl_lock (t_g_wzd.h_satl) ;
        c_satl_update_rec (t_g_wzd.h_satl, &t_satl_rec, TRUE) ;
        c_satl_unlock (t_g_wzd.h_satl) ;
    }

    /* get 'Channels' configration */
    {
        WZD_RET_ON_ERR (c_wgl_do_cmd (ah_items[_ITEM_LB_CHANNLES],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK (&ui2_hlt_idx),
                                NULL)) ;        
        if (WGL_LB_NULL_INDEX == ui2_hlt_idx)
        {
            WZD_RET_ON_ERR (WZDR_FAIL) ;
        }

        if (0 == ui2_hlt_idx)
        {
            /* highlight on 'Free' */
            pt_dvbs_scan_data->t_eng_cfg_flag |= SB_DVBS_CONFIG_INSTALL_FREE_SVC_ONLY ;  
        }
    }

    /* get scan mode */  
    {
        WZD_RET_ON_ERR (c_wgl_do_cmd (ah_items[_ITEM_LB_SCAN_MODE],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK (&ui2_hlt_idx),
                                NULL)) ;
        if (WGL_LB_NULL_INDEX == ui2_hlt_idx)
        {
            WZD_RET_ON_ERR (WZDR_FAIL) ;
        }
        
        switch (ui2_hlt_idx)
        {
        case 0 :
            pt_dvbs_scan_data->e_scan_type = SB_DVBS_SCAN_TYPE_AUTO_MODE ;
        break ;

        case 1 :
            pt_dvbs_scan_data->e_scan_type = SB_DVBS_SCAN_TYPE_PRESET_MODE ;
        break ;

        default :        
            pt_dvbs_scan_data->e_scan_type = SB_DVBS_SCAN_TYPE_UNKNOWN ;
        break ;
        }
    }

    /* get network search */
    if (SB_DVBS_SCAN_TYPE_PRESET_MODE == pt_dvbs_scan_data->e_scan_type)
    {
        WZD_RET_ON_ERR (c_wgl_do_cmd (ah_items[_ITEM_LB_NET_SEARCH],
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK (&ui2_hlt_idx),
                                NULL)) ;        
        if (WGL_LB_NULL_INDEX == ui2_hlt_idx)
        {
            WZD_RET_ON_ERR (WZDR_FAIL) ;
        }

        pt_dvbs_scan_data->t_scan_info.uinfo.t_preset_scan_info.b_network_search 
                                = (0 == ui2_hlt_idx)    /* 0 --> On , 1 --> Off */
                                ? TRUE
                                : FALSE ;    
    }

    return WZDR_OK ;
}

#endif  /* APP_DVBS_SUPPORT */


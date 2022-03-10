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
 * $RCSfile: wzd_page_dvbc.c,v $
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

#ifdef APP_DVBC_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_sb_dvbc_eng.h"
#include "scan_maps/dvbc_scan_maps.h"

#include "wizard/wzd.h"
#include "wizard/wzd_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define COUNTRY_NUM                             (32)

#define MOD_AUTO                                ((UINT8) 0)
#define MOD_Q16                                 ((UINT8) 1)
#define MOD_Q32                                 ((UINT8) 2)
#define MOD_Q64                                 ((UINT8) 3)
#define MOD_Q128                                ((UINT8) 4)
#define MOD_Q256                                ((UINT8) 5)

#define SCAN_MODE_FULL                          ((UINT8) 0)
#define SCAN_MODE_QUICK                         ((UINT8) 1)
#define SCAN_MODE_ADVANCE                       ((UINT8) 2)

#define FRQ_MAX                                 ((UINT32) 999999)
#define FRQ_MIN                                 ((UINT32) 0)
#define FRQ_LIMIT                               ((UINT32) 999999)

#define SYM_RATE_MIN                            ((UINT32) 4000)
#define SYM_RATE_MAX                            ((UINT32) 7200)
#define SYM_RATE_PRESET                         ((UINT32) 6875)    /* Ksym/s */
#define SYM_RATE_LIMIT                          ((UINT32) 9999)

#define NW_ID_MIN                               ((UINT32) 0)
#define NW_ID_MAX                               ((UINT32) 999999)
#define NW_ID_LIMIT                             ((UINT32) 999999)

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

typedef struct _SUPT_QUK_SCAN_MAP_T_
{
    ISO_3166_COUNT_T    s_country_code ;
    BOOL                b_suprt_quk_scan ;          /* support quick scan mode */
    
}_SUPT_QUK_SCAN_MAP_T ;

typedef enum
{
    _ITEM_LB_SCAN_MODE = 0 ,
    _ITEM_EB_FREQ ,
    _ITEM_LB_MODULATION ,
    _ITEM_EB_SYBR ,
    _ITEM_EB_NW_ID ,
    _ITEM_LAST_ENTRY
    
}_WZD_DVBC_PAGE_ITEM_T ;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static UINT32               ui4_frq_KHz         = 0 ;
static UINT32               ui4_sym_rt_K        = 0 ;
static UINT32               ui4_nw_id           = 0 ;
static HANDLE_T             h_layout_frm        = NULL_HANDLE ;
static HANDLE_T             ah_items[_ITEM_LAST_ENTRY]       = {0} ;
static BOOL                 ab_item_enable[_ITEM_LAST_ENTRY] = {0} ;
static _SUPT_QUK_SCAN_MAP_T at_supt_quk_scan_map[COUNTRY_NUM]=
{
    /* country code  / support quick scan */
    {"AUT" ,FALSE },  /* Austria */
    {"BEL" ,FALSE },  /* Belgium */
    {"CHE" ,FALSE },  /* Switzerland */
    {"CZE" ,FALSE },  /* Czech Republic */
    {"DEU" ,TRUE  },  /* Germany */
    {"DNK" ,FALSE },  /* Denmark */
    {"ESP" ,FALSE },  /* Spain */
    {"FIN" ,TRUE  },  /* Finland */
    {"FRA" ,FALSE },  /* France */
    {"GBR" ,FALSE },  /* United Kingdom */
    {"ITA" ,FALSE },  /* Italy */
    {"LUX" ,FALSE },  /* Luxembourg */
    {"NLD" ,FALSE },  /* Netherlands */
    {"NOR" ,TRUE  },  /* Norway */
    {"SWE" ,FALSE },  /* Sweden */
    {"BGR" ,FALSE },  /* Bulgaria */
    {"HRV" ,FALSE },  /* Croatia */
    {"GRC" ,FALSE },  /* Greece */
    {"HUN" ,FALSE },  /* Hungary */
    {"IRL" ,FALSE },  /* Ireland */
    {"POL" ,FALSE },  /* Poland */
    {"PRT" ,FALSE },  /* Portugal */
    {"ROU" ,FALSE },  /* Romania */
    {"RUS" ,FALSE },  /* Russian Federation */
    {"SRB" ,FALSE },  /* Serbia */
    {"SVK" ,FALSE },  /* Slovakia */
    {"SVN" ,FALSE },  /* Slovenia */
    {"TUR" ,FALSE },  /* Turkey */
    {"AUS" ,FALSE },  /* Australia */
    {"NZL" ,FALSE },  /* New Zealand */
    {"TWN" ,FALSE },  /* Taiwan */
    {"ISL" ,FALSE }   /* Iceland */
} ;
static GL_RECT_T            t_rect_border_title = {
    _WZD_DVBC_ITEM_BAR_CNT_INSET_L + _WZD_DVBC_ITEM_ICON_W, 
    0, 
    _WZD_DVBC_ITEM_BAR_CNT_INSET_L + _WZD_DVBC_ITEM_ICON_W + _WZD_DVBC_ITEM_TITLE_W, 
    _WZD_DVBC_GRID_H} ;
static WGL_INSET_T t_inset_list_body = {
    _WZD_DVBC_ITEM_BAR_CNT_INSET_L + _WZD_DVBC_ITEM_ICON_W + _WZD_DVBC_ITEM_TITLE_W, 
    _WZD_DVBC_ITEM_BAR_CNT_INSET_R, 
    0, 
    0};
    
#ifdef __________________JUST_FOR_DIVISION
#endif 

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

/*----------------------------------------------------------------------------
 * Name: _list_chg_lang
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
    WGL_LB_ITEM_T               at_items[2];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_lr;
    UINT16                      ui2_i;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    UTF16_T                     w2s_empty[] = {0};
    WGL_IMG_INFO_T              t_img_info ;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = _WZD_DVBC_ITEM_VALUE_W;
    at_cols[1].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_width        = _WZD_DVBC_ITEM_HINT_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = ui2_max_elem_num;
    t_lb_init.ui2_elem_size     = _WZD_DVBC_GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect, _WZD_DVBC_ITEM_BAR_INSET_L, 
                                 _WZD_DVBC_GRID_H * i4_index, 
                                 LAYOUT_FRM_W - _WZD_DVBC_ITEM_BAR_INSET_L - _WZD_DVBC_ITEM_BAR_INSET_R, 
                                 _WZD_DVBC_GRID_H);
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
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_list_body,
                          NULL);
    WZD_RET_ON_ERR(i4_ret);

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

    for (ui2_i=0; ui2_i<ui2_max_elem_num; ui2_i++)
    {
        at_items[0].e_col_type = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text = w2s_empty;
        at_items[1].e_col_type = LB_COL_TYPE_IMG_SUIT;
        at_items[1].data.pt_img_suit = &t_img_suit_lr;
        i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        WZD_RET_ON_ERR(i4_ret);
    }


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
 * Name: _list_chg_lang
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
INT32 _list_chg_lang(
    HANDLE_T                    h_widget,
    UINT16                      ui2_msgid_title,
    UINT16                      ui2_msgid_elem_first,
    UINT16                      ui2_msgid_elem_last
    )
{
    INT32   i4_ret;
    UINT16  ui2_i;

    /* Set Title language */
    i4_ret = c_wgl_do_cmd ( h_widget, 
                                WGL_CMD_BDR_TIMG_SET_TITLE_TEXT, 
                                WGL_PACK(WZD_TEXT(ui2_msgid_title)), 
                                WGL_PACK(c_uc_w2s_strlen(WZD_TEXT(ui2_msgid_title))));
    WZD_RET_ON_ERR(i4_ret);

    /* Set elements language */
    for (ui2_i = ui2_msgid_elem_first; 
        ui2_i <= ui2_msgid_elem_last; 
        ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_widget, 
                                WGL_CMD_LB_SET_ITEM_TEXT, 
                                WGL_PACK_2(ui2_i - ui2_msgid_elem_first,0), 
                                WGL_PACK(WZD_TEXT(ui2_i)));
        WZD_RET_ON_ERR(i4_ret);
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _edit_create
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
INT32 _edit_create(
    HANDLE_T                h_parent,
    INT32                   i4_index,
    wgl_widget_proc_fct     pf_wdgt_proc,
    HANDLE_T*               ph_widget
    )
{
    INT32                   i4_ret = 0;
    UINT32                  ui4_style;
    GL_RECT_T               t_rect;
    WGL_INSET_T             t_inset;
    WGL_COLOR_INFO_T        t_clr_info;
    WGL_IMG_INFO_T          t_img_info;
    WGL_FONT_INFO_T         t_fnt_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_EB_KEY_MAP_T        t_eb_key_map;

    /* create editbox */
    ui4_style = 0;
    
    SET_RECT_BY_SIZE(&t_rect, 
                     _WZD_DVBC_ITEM_BAR_INSET_L, 
                     _WZD_DVBC_GRID_H * i4_index, 
                     LAYOUT_FRM_W - _WZD_DVBC_ITEM_BAR_INSET_L - _WZD_DVBC_ITEM_BAR_INSET_R, 
                     _WZD_DVBC_GRID_H);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return WZDR_FAIL ;
    }

    /* Set Insets */
    t_inset.i4_left     = t_inset_list_body.i4_left;
    t_inset.i4_right    = _WZD_DVBC_ITEM_BAR_CNT_INSET_R;
    t_inset.i4_top      = _WZD_DVBC_ITEM_EDIT_INSET_T;
    t_inset.i4_bottom   = _WZD_DVBC_ITEM_EDIT_INSET_B;    
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    WZD_RET_ON_ERR(i4_ret);

    {
        /* Set Cnt Insets */
        t_inset.i4_left     = _WZD_DVBC_ITEM_EDIT_CNT_INSET_L;
        t_inset.i4_right    = _WZD_DVBC_ITEM_EDIT_CNT_INSET_R;
        t_inset.i4_top      = _WZD_DVBC_ITEM_EDIT_CNT_INSET_T;
        t_inset.i4_bottom   = _WZD_DVBC_ITEM_EDIT_CNT_INSET_B;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_EB_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        WZD_RET_ON_ERR(i4_ret);
    
        /* Set EB Alignment */
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_EB_SET_ALIGN,
                              WGL_PACK(_WZD_DVBC_ITEM_EDIT_ALIGN),
                              NULL);
        WZD_RET_ON_ERR(i4_ret);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, WZD_FONT_NAME);
        t_fnt_info.e_font_size  = _WZD_DVBC_ITEM_EDIT_FNT_SIZE;
        t_fnt_info.e_font_style = _WZD_DVBC_ITEM_EDIT_FNT_STYLE;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    
        i4_ret = c_wgl_do_cmd (*ph_widget,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        WZD_RET_ON_ERR(i4_ret);
    }

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_wzd_color_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_wzd_img_item_edit;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_wzd_img_item_edit_hlt;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_wzd_img_item_edit_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    WZD_RET_ON_ERR(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)5),
                          NULL);
    WZD_RET_ON_ERR(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),  /*Attr mask*/
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING)); /*Attr value*/
    WZD_RET_ON_ERR(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    c_strcpy(t_title_info.t_font.a_c_font_name, WZD_FONT_NAME);
    t_title_info.t_font.e_font_size  = SETI_LB_COL_TEXT_FNT_SIZE;
    t_title_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_title_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
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

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    WZD_RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _edit_chg_lang
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
INT32 _edit_chg_lang(
    HANDLE_T            h_widget,
    UINT16              ui2_msgid_title
    )
{
    /* Set Title language */
    WZD_RET_ON_ERR (c_wgl_do_cmd(h_widget, 
                        WGL_CMD_BDR_TIMG_SET_TITLE_TEXT, 
                        WGL_PACK(WZD_TEXT(ui2_msgid_title)), 
                        WGL_PACK(c_uc_w2s_strlen(
                        WZD_TEXT(ui2_msgid_title))))) ;
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _chg_lang
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
static INT32 _chg_lang(VOID)
{
    WZD_RET_ON_ERR (_list_chg_lang(
                        ah_items[_ITEM_LB_SCAN_MODE], 
                        MLM_WZD_KEY_SCAN_MODE ,  
                        MLM_WZD_KEY_SCAN_MODE_FULL ,
                        MLM_WZD_KEY_SCAN_MODE_ADVANCE)) ;

    WZD_RET_ON_ERR (_list_chg_lang(
                        ah_items[_ITEM_LB_MODULATION] ,
                        MLM_WZD_KEY_DVBC_SCAN_MDLT,
                        MLM_WZD_KEY_DVBC_SCAN_MOD_AUTO,
                        MLM_WZD_KEY_DVBC_SCAN_MOD_Q256)) ;
                       
    WZD_RET_ON_ERR (_edit_chg_lang(
                        ah_items[_ITEM_EB_SYBR], 
                        MLM_WZD_KEY_DVBC_SCAN_SBRT)) ;

    WZD_RET_ON_ERR (_edit_chg_lang(
                        ah_items[_ITEM_EB_NW_ID], 
                        MLM_WZD_KEY_NW_ID)) ;

    return WZDR_OK ;
}

/*----------------------------------------------------------------------------
 * Name: _is_support_quick_scan
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
static INT32 _is_support_quick_scan (
    BOOL*                       pb_support
    )
{
    UINT8                       ui1_country_idx = 0 ;
    static  ISO_3166_COUNT_T    s_country_code ;

    WZD_RET_ON_ERR (a_cfg_get_country(s_country_code)) ;   
    
    if (!pb_support)
    {
        return WZDR_INV_ARG ;
    }

    *pb_support = FALSE ;

    for (ui1_country_idx = 0 ;ui1_country_idx <COUNTRY_NUM ;ui1_country_idx ++)
    {
        if (0 == c_strcmp (s_country_code ,
                at_supt_quk_scan_map[ui1_country_idx].s_country_code))
        {
            *pb_support = at_supt_quk_scan_map[ui1_country_idx].b_suprt_quk_scan ;
            break ;
        }
    }

    return WZDR_OK ;
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
        if (ab_item_enable[ui1_i])
        {
            /* enable this item */
            WZD_RET_ON_ERR (c_wgl_enable (ah_items[ui1_i] ,TRUE)) ;
            
            /* prepare to link this item with 'up/down' key */
            aui1_tmp[ui1_j++] = ui1_i ;
        }
        else
        {
            /* disable this item */
            WZD_RET_ON_ERR (c_wgl_enable (ah_items[ui1_i] ,FALSE)) ;
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

    /* adjust focus */  
    WZD_RET_ON_ERR (c_wgl_set_focus (ah_items[_ITEM_LB_SCAN_MODE] ,WGL_NO_AUTO_REPAINT)) ;

    return WZDR_OK; 
}

/*----------------------------------------------------------------------------
 * Name: _get_eb_value_by_wgt
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
static INT32 _eb_get_info (
    HANDLE_T            h_widget ,
    UINT32*             pui4_cur_val ,
    UINT32*             pui4_max ,
    UINT32*             pui4_min ,
    UINT32*             pui4_limt
    )
{
    if (!h_widget || !pui4_cur_val || !pui4_max || !pui4_min || !pui4_limt)
    {
        WZD_RET_ON_ERR (WZDR_INV_ARG) ;
    }
    
    if (ah_items[_ITEM_EB_SYBR] == h_widget)
    {
        *pui4_cur_val = ui4_sym_rt_K ;
        *pui4_max     = SYM_RATE_MAX ;
        *pui4_min     = SYM_RATE_MIN ;
        *pui4_limt    = SYM_RATE_LIMIT ;
    }

    else if (ah_items[_ITEM_EB_FREQ] == h_widget)
    {
        *pui4_cur_val = ui4_frq_KHz ;
        *pui4_max     = FRQ_MAX ;
        *pui4_min     = FRQ_MIN ;
        *pui4_limt    = FRQ_LIMIT ;
    }

    else if (ah_items[_ITEM_EB_NW_ID] == h_widget)
    {
        *pui4_cur_val = ui4_nw_id ;
        *pui4_max     = NW_ID_MAX ;
        *pui4_min     = NW_ID_MIN ;
        *pui4_limt    = NW_ID_LIMIT ;
    }
    else
    {
        return WZDR_INV_ARG ;
    }
    
    return WZDR_OK ;
}   

/*----------------------------------------------------------------------------
 * Name: _eb_set_value
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
static INT32 _eb_set_value (
    HANDLE_T                h_widget,
    UINT32                  ui4_value
    )
{
    UTF16_T                 w2s_buf[32];

    if (ah_items[_ITEM_EB_SYBR] == h_widget)
    {
        ui4_sym_rt_K = ui4_value ;      
    }

    else if (ah_items[_ITEM_EB_FREQ] == h_widget)
    {
        ui4_frq_KHz = ui4_value ;
    }

    else if (ah_items[_ITEM_EB_NW_ID] == h_widget)
    {
        ui4_nw_id = ui4_value ;
    }

    else
    {
        return WZDR_INV_ARG ;
    }

    c_memset(w2s_buf, 0, sizeof(w2s_buf));
    _itoa(w2s_buf, (INT32)ui4_value, 7);

    WZD_RET_ON_ERR (c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF))) ;

    return WZDR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _eb_proc_fct
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
static INT32 _eb_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    static UINT32               ui4_tick_last = 0 ;
    UINT32                      ui4_keycode = 0 ;
    UINT16                      ui2_input = 0 ;
    UINT32                      ui4_tick_curr = 0 ;
    UINT32                      ui4_val = 0 ;
    UINT32                      ui4_limt = 0 ;
    UINT32                      ui4_max = 0 ;
    UINT32                      ui4_min = 0 ;

    switch (ui4_msg)
    {
        case WGL_MSG_GET_FOCUS :
            ui4_tick_last = 0 ;
        break ;

        case WGL_MSG_LOSE_FOCUS:
        {   
            WZD_RET_ON_ERR (_eb_get_info(h_widget ,&ui4_val ,&ui4_max ,&ui4_min ,&ui4_limt)) ;
            
            if (ui4_val > ui4_max || ui4_val < ui4_min)
            {
                ui4_val = (ui4_val > ui4_max) ? ui4_max : ui4_min ;
                _eb_set_value(h_widget, ui4_val);
                c_wgl_repaint(h_widget, NULL,TRUE);
            }
        }   
        return WMPR_DONE;

        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            ui4_keycode = (UINT32)param1 ;

            switch (ui4_keycode)
            {   
            case BTN_DIGIT_0 : case BTN_DIGIT_1 : case BTN_DIGIT_2 : 
            case BTN_DIGIT_3 : case BTN_DIGIT_4 : case BTN_DIGIT_5 : 
            case BTN_DIGIT_6 : case BTN_DIGIT_7 : case BTN_DIGIT_8 : 
            case BTN_DIGIT_9 :
                WZD_RET_ON_ERR (_eb_get_info(h_widget ,&ui4_val ,&ui4_max ,&ui4_min ,&ui4_limt)) ;
                ui2_input = ui4_keycode - BTN_DIGIT_0;
                ui4_tick_curr = c_os_get_sys_tick();

                if((ui4_tick_curr - ui4_tick_last) * c_os_get_sys_tick_period() <
                   INPUT_RESET_DELAY)
                {
                    ui4_val = ui4_val * 10 + ui2_input;
                }
                else
                {
                    ui4_val = ui2_input;
                }
                ui4_tick_last = ui4_tick_curr;
                
                while(ui4_val > ui4_limt)
                {
                    ui4_val = ui4_val % (ui4_limt+1);
                }

                _eb_set_value(h_widget ,ui4_val);
                c_wgl_repaint(h_widget, NULL,TRUE);
            return WMPR_DONE;

            case BTN_EXIT:
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
            WZD_RET_ON_ERR (c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2)) ;
            WZD_RET_ON_ERR (c_wgl_do_cmd(h_widget,WGL_CMD_LB_GET_HLT_INDEX,WGL_PACK(&ui2_idx),NULL));
            
            if (ah_items[_ITEM_LB_SCAN_MODE] == h_widget
                &&
                (ui2_idx == SCAN_MODE_FULL - SCAN_MODE_FULL || ui2_idx == SCAN_MODE_QUICK - SCAN_MODE_FULL))
            {
                /* disable freq,modul,symb rate,network id when 
                 * the scan mode is FULL or QUICK
                 */
                c_wgl_enable (ah_items[_ITEM_EB_FREQ] ,FALSE) ;
                ab_item_enable[_ITEM_EB_FREQ] = FALSE ;
                
                c_wgl_enable (ah_items[_ITEM_LB_MODULATION],FALSE) ;
                ab_item_enable[_ITEM_LB_MODULATION] = FALSE ;
                
                c_wgl_enable (ah_items[_ITEM_EB_SYBR] ,FALSE) ;
                ab_item_enable[_ITEM_EB_SYBR] = FALSE ;
                
                c_wgl_enable (ah_items[_ITEM_EB_NW_ID] ,FALSE) ; 
                ab_item_enable[_ITEM_EB_NW_ID] = FALSE ;

                _adjust_view () ;
                WZD_RET_ON_ERR (c_wgl_repaint(h_layout_frm, NULL, TRUE));
            }
            else if (ah_items[_ITEM_LB_SCAN_MODE] == h_widget)
            {
                /* otherwise ,enable freq,modul,symb rate,network id */
                c_wgl_enable (ah_items[_ITEM_EB_FREQ] ,TRUE) ;
                ab_item_enable[_ITEM_EB_FREQ] = TRUE ;
                
                c_wgl_enable (ah_items[_ITEM_LB_MODULATION],TRUE) ;
                ab_item_enable[_ITEM_LB_MODULATION] = TRUE ;
                
                c_wgl_enable (ah_items[_ITEM_EB_SYBR] ,TRUE) ;
                ab_item_enable[_ITEM_EB_SYBR] = TRUE ;
                
                c_wgl_enable (ah_items[_ITEM_EB_NW_ID] ,TRUE) ; 
                ab_item_enable[_ITEM_EB_NW_ID] = TRUE ;

                _adjust_view () ;
                WZD_RET_ON_ERR (c_wgl_repaint(h_layout_frm, NULL, TRUE));
            }
            else
            {
                /* do nothing */
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

#ifdef __________________JUST_FOR_DIVISION
#endif 

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbc_create
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
INT32 wzd_page_dvbc_create (VOID)
{
    WZD_RET_ON_ERR (wzd_view_get_layout_frm (&h_layout_frm)) ;
    
    /* lb scan mode */
    WZD_RET_ON_ERR (_list_create(h_layout_frm,
                                _LB_SCAN_MODE_IDX,
                                (UINT16)((MLM_WZD_KEY_SCAN_MODE_ADVANCE - MLM_WZD_KEY_SCAN_MODE_FULL)+1), 
                                _lb_proc_fct,
                                &ah_items[_ITEM_LB_SCAN_MODE])) ;

    WZD_LOG_ON_ERR (_list_chg_lang(ah_items[_ITEM_LB_SCAN_MODE], 
                                MLM_WZD_KEY_SCAN_MODE ,  
                                MLM_WZD_KEY_SCAN_MODE_FULL ,
                                MLM_WZD_KEY_SCAN_MODE_ADVANCE)) ;

    WZD_LOG_ON_ERR (c_wgl_set_visibility(
                                ah_items[_ITEM_LB_SCAN_MODE],
                                WGL_SW_HIDE)) ;

    /* eb frequency */
    WZD_RET_ON_ERR (_edit_create(h_layout_frm,
                                _EB_FREQ_IDX,
                                _eb_proc_fct,
                                &ah_items[_ITEM_EB_FREQ])) ;

    WZD_LOG_ON_ERR (_edit_chg_lang (ah_items[_ITEM_EB_FREQ], 
                                MLM_WZD_KEY_DVBC_SCAN_FREQ));
    
    WZD_LOG_ON_ERR (_eb_set_value(ah_items[_ITEM_EB_FREQ] ,0)) ;

    WZD_LOG_ON_ERR (c_wgl_do_cmd(ah_items[_ITEM_EB_FREQ],
                                WGL_CMD_EB_SET_INPUT_LIMIT,
                                WGL_PACK((UINT16)8),
                                NULL));
    
    WZD_LOG_ON_ERR (c_wgl_set_visibility(
                                ah_items[_ITEM_EB_FREQ],
                                WGL_SW_HIDE)) ;

    /* lb modulation */
    WZD_RET_ON_ERR (_list_create(h_layout_frm,
                                _LB_MODULATION_IDX,
                                (UINT16)(MLM_WZD_KEY_DVBC_SCAN_MOD_Q256 - MLM_WZD_KEY_DVBC_SCAN_MOD_AUTO)+1,
                                _lb_proc_fct,
                                &ah_items[_ITEM_LB_MODULATION])) ;

    WZD_LOG_ON_ERR (_list_chg_lang(ah_items[_ITEM_LB_MODULATION] ,
                                MLM_WZD_KEY_DVBC_SCAN_MDLT,
                                MLM_WZD_KEY_DVBC_SCAN_MOD_AUTO,
                                MLM_WZD_KEY_DVBC_SCAN_MOD_Q256)) ;
                       
    WZD_LOG_ON_ERR (c_wgl_set_visibility(
                               ah_items[_ITEM_LB_MODULATION],
                               WGL_SW_HIDE)) ;

    /* eb symbol rate */
    WZD_RET_ON_ERR (_edit_create(h_layout_frm,
                                _EB_SYMBOL_RATE_IDX,
                                _eb_proc_fct,
                                &ah_items[_ITEM_EB_SYBR])) ;

    WZD_LOG_ON_ERR (_edit_chg_lang(ah_items[_ITEM_EB_SYBR], 
                                MLM_WZD_KEY_DVBC_SCAN_SBRT)) ;

    WZD_LOG_ON_ERR (_eb_set_value(ah_items[_ITEM_EB_SYBR] ,0)) ;

    WZD_LOG_ON_ERR (c_wgl_do_cmd(ah_items[_ITEM_EB_SYBR],
                                WGL_CMD_EB_SET_INPUT_LIMIT,
                                WGL_PACK((UINT16)8),
                                NULL));

    WZD_LOG_ON_ERR (c_wgl_set_visibility(
                               ah_items[_ITEM_EB_SYBR],
                               WGL_SW_HIDE)) ;

    /* Network ID */
    WZD_RET_ON_ERR (_edit_create(h_layout_frm,
                                _EB_NWID_IDX,
                                _eb_proc_fct,
                                &ah_items[_ITEM_EB_NW_ID])) ;

    WZD_LOG_ON_ERR (_edit_chg_lang(ah_items[_ITEM_EB_NW_ID], 
                                MLM_WZD_KEY_NW_ID)) ;

    WZD_LOG_ON_ERR (_eb_set_value(ah_items[_ITEM_EB_NW_ID] ,0)) ;

    WZD_LOG_ON_ERR (c_wgl_do_cmd(ah_items[_ITEM_EB_NW_ID],
                                WGL_CMD_EB_SET_INPUT_LIMIT,
                                WGL_PACK((UINT16)8),
                                NULL));
    
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_dvbc_dsty
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
INT32 wzd_page_dvbc_dsty(VOID)
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
 * Name: wzd_page_dvbc_on_show
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
INT32 wzd_page_dvbc_on_show(UINT32 ui4_page_id)
{
    INT32                       h_widget = 0 ;
    UINT32                      ui4_wgl_cmd = 0 ;
    BOOL                        b_support_quick_scan = FALSE ;
    SIZE_T                      z_len = sizeof(UINT32);
    static  ISO_3166_COUNT_T    s_country_code ;
    TUNER_MODULATION_T          e_modlation ;
    UINT16                      ui2_modlation ;
    UINT16                      ui2_nw_id_tmp ;
    UINT16                      ui2_scan_mode_idx = 0 ;

    WZD_RET_ON_ERR (a_cfg_get_country(s_country_code)) ;   
    
    c_memset(ab_item_enable ,FALSE ,sizeof(ab_item_enable)) ;

    /* update all item with new OSD language */
    WZD_LOG_ON_ERR (_chg_lang ()) ;

    /* set scan mode */
    {
        h_widget = ah_items[_ITEM_LB_SCAN_MODE] ;
        WZD_RET_ON_ERR (_is_support_quick_scan (&b_support_quick_scan)) ;

        /* enable/disable quick scan */
        ui4_wgl_cmd         =   (b_support_quick_scan) 
                            ?   WGL_CMD_LB_ENABLE_ELEM
                            :   WGL_CMD_LB_DISABLE_ELEM ;
        
        WZD_RET_ON_ERR (c_wgl_do_cmd (h_widget, 
                                ui4_wgl_cmd ,
                                (VOID*)(SCAN_MODE_QUICK-SCAN_MODE_FULL), 
                                NULL)) ;

        /* select scan mode */
        ui2_scan_mode_idx   =   (b_support_quick_scan)
                            ?   (UINT16)(SCAN_MODE_QUICK - SCAN_MODE_FULL)
                            :   (UINT16)(SCAN_MODE_ADVANCE - SCAN_MODE_FULL) ;
        
        WZD_RET_ON_ERR (c_wgl_do_cmd (h_widget,
                                WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                WGL_PACK(ui2_scan_mode_idx),
                                WGL_PACK(0)));
        
        ab_item_enable[_ITEM_LB_SCAN_MODE] = TRUE ;
    }
    
    /* eb frequency */
    {
        h_widget = ah_items[_ITEM_EB_FREQ] ;

        /* get the default value */
        z_len = sizeof (ui4_frq_KHz) ;
         WZD_RET_ON_ERR (dvbc_scan_maps_fct(DVBC_SCAN_MAPS_CMD_GET_DEFAULT_FREQ, 
                            s_country_code, 
                            NULL, 
                            NULL,
                            NULL,
                            &ui4_frq_KHz, 
                            &z_len));   

        /* convert to Ksym/s units */
        ui4_frq_KHz /= 1000 ;

        WZD_RET_ON_ERR (_eb_set_value(h_widget,ui4_frq_KHz)) ;
        ab_item_enable[_ITEM_EB_FREQ] = (b_support_quick_scan) ? FALSE : TRUE ;
    }

    /* eb symbol rate */
    {
        h_widget = ah_items[_ITEM_EB_SYBR] ;
        z_len = sizeof (ui4_sym_rt_K) ;
        WZD_RET_ON_ERR (dvbc_scan_maps_fct(
                        DVBC_SCAN_MAPS_CMD_GET_DEFAULT_SYMBOL_RATE, 
                        s_country_code, 
                        NULL, 
                        NULL,
                        NULL,
                        &ui4_sym_rt_K,  
                        &z_len)) ;
        
        /* convert to Ksym/s units */
        ui4_sym_rt_K /= 1000 ;
        
        WZD_RET_ON_ERR (_eb_set_value(h_widget ,ui4_sym_rt_K)) ;
        ab_item_enable[_ITEM_EB_SYBR] = (b_support_quick_scan) ? FALSE : TRUE ;
    }

    /* modulation */
    {
        h_widget = ah_items[_ITEM_LB_MODULATION] ;
        z_len = sizeof (TUNER_MODULATION_T) ;
        WZD_RET_ON_ERR (dvbc_scan_maps_fct(
                        DVBC_SCAN_MAPS_CMD_GET_DEFAULT_QAM, 
                        s_country_code, 
                        NULL, 
                        NULL,
                        NULL,
                        &e_modlation, 
                        &z_len)) ;
        
        switch (e_modlation)
        {    
            case MOD_QAM_16:
                ui2_modlation = MOD_Q16;
                break;
            case MOD_QAM_32:
                ui2_modlation = MOD_Q32;
                break;
            case MOD_QAM_64:
                ui2_modlation = MOD_Q64;
                break;
            case MOD_QAM_128:
                ui2_modlation = MOD_Q128;
                break;     
            case MOD_QAM_256:
                ui2_modlation = MOD_Q256;
                break;
            case MOD_UNKNOWN:
            default:
                ui2_modlation = MOD_AUTO;
                break;
        }

        WZD_RET_ON_ERR (c_wgl_do_cmd(h_widget,
                                WGL_CMD_LB_HLT_ELEM_VISIBLE,
                                WGL_PACK(ui2_modlation - MOD_AUTO),
                                WGL_PACK(0))) ;
        ab_item_enable[_ITEM_LB_MODULATION] = (b_support_quick_scan) ? FALSE : TRUE ;
    }   

    /* network id */
    {
        h_widget = ah_items[_ITEM_EB_NW_ID] ;
        z_len = sizeof (ui2_nw_id_tmp) ;
        WZD_RET_ON_ERR (dvbc_scan_maps_fct(
                                DVBC_SCAN_MAPS_CMD_GET_DEFAULT_NETWORK_ID, 
                            s_country_code, 
                            NULL, 
                            NULL,
                            NULL,
                            &ui2_nw_id_tmp, 
                            &z_len)) ;
        ui4_nw_id = ui2_nw_id_tmp ;
        WZD_RET_ON_ERR (_eb_set_value(h_widget , ui4_nw_id)) ;
        ab_item_enable[_ITEM_EB_NW_ID] = (b_support_quick_scan) ? FALSE : TRUE ;
    }   

    WZD_RET_ON_ERR (_adjust_view ()) ;

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
 * Name: wzd_page_dvbc_on_hide
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
INT32 wzd_page_dvbc_on_hide(UINT32 ui4_page_id)
{
    UINT8   ui1_item_idx = 0 ;

    for (ui1_item_idx = 0 ;ui1_item_idx < _ITEM_LAST_ENTRY ;ui1_item_idx ++)
    {
        WZD_RET_ON_ERR (c_wgl_set_visibility (ah_items[ui1_item_idx] ,WGL_SW_HIDE)) ;
    }
        
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_get_scan_data_dvbc
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
INT32 wzd_page_dvbc_get_scan_data (
    SB_DVBC_SCAN_DATA_T*        pt_dvbc_scan_data
    )
{
    ISO_3166_COUNT_T            s_country_code;
    UINT16                      ui2_scan_mode     = 0 ;
    UINT16                      ui2_modlation     = 0 ;
    SB_DVBC_NIT_SEARCH_MODE_T   e_nit_search_mode = SB_DVBC_NIT_SEARCH_MODE_OFF ;

    if (!pt_dvbc_scan_data)
    {
        return WZDR_INV_ARG ;
    }
    
    /* get scan mode */  
    WZD_RET_ON_ERR (c_wgl_do_cmd(ah_items[_ITEM_LB_SCAN_MODE],
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_scan_mode),
                          NULL)) ;
    ui2_scan_mode += SCAN_MODE_FULL ;

    /* get nit search mode */
    switch (ui2_scan_mode)
    {
    case SCAN_MODE_QUICK :
        e_nit_search_mode = SB_DVBC_NIT_SEARCH_MODE_QUICK ;
    break ;

    case SCAN_MODE_ADVANCE :
        e_nit_search_mode = SB_DVBC_NIT_SEARCH_MODE_EX_QUICK ;
    break ;
    
    case SCAN_MODE_FULL :
    default :
        e_nit_search_mode = SB_DVBC_NIT_SEARCH_MODE_OFF ;
    break ;
    }

    /* get frequency */
    /* ui4_frq_KHz ;*/

    /* get modulation */
    WZD_RET_ON_ERR (c_wgl_do_cmd(ah_items[_ITEM_LB_MODULATION],
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_modlation),
                          NULL)) ;
    switch (ui2_modlation)
    {    
        case MOD_Q16:
            ui2_modlation = MOD_QAM_16;
            break;
        case MOD_Q32:
            ui2_modlation = MOD_QAM_32;
            break;
        case MOD_Q64:
            ui2_modlation = MOD_QAM_64;
            break;
        case MOD_Q128:
            ui2_modlation = MOD_QAM_128;
            break;     
        case MOD_Q256:
            ui2_modlation = MOD_QAM_256;
            break;
        case MOD_AUTO:
        default:
            ui2_modlation = MOD_UNKNOWN;
            break;
    }
    
    /* get symbol rate */
    /* ui4_sym_rt_K ;*/

    /* get network id */
    /* ui4_nw_id ;*/

    /* get country code */  
    WZD_RET_ON_ERR (a_cfg_get_country(s_country_code));

    /* config pt_dvbc_scan_data for digital scan */
    c_memset(pt_dvbc_scan_data ,0 ,sizeof(SB_DVBC_SCAN_DATA_T)) ; 
    pt_dvbc_scan_data->t_eng_cfg_flag = (SCAN_MODE_FULL == ui2_scan_mode)
                                      ? SB_DVBC_CONFIG_SCAN_WITHOUT_SCAN_MAP 
                                      : 0 ;
    c_strncpy(pt_dvbc_scan_data->t_country_code ,s_country_code ,ISO_3166_COUNT_LEN) ;
    pt_dvbc_scan_data->e_scan_type = SB_DVBC_SCAN_TYPE_FULL_MODE;   
    pt_dvbc_scan_data->e_nit_search_mode = e_nit_search_mode ;

    if (SCAN_MODE_ADVANCE == ui2_scan_mode)
    {   
        /* config t_scan_info */
        pt_dvbc_scan_data->t_scan_info.ui2_valid_mask = 
                                SB_DVBC_SCAN_INFO_MOD_VALID  
                                |SB_DVBC_SCAN_INFO_SYM_VALID  
                                |SB_DVBC_SCAN_INFO_START_FREQ_VALID  
                                |SB_DVBC_SCAN_INFO_END_FREQ_VALID 
                                |SB_DVBC_SCAN_INFO_NW_ID_VALID ;
        pt_dvbc_scan_data->t_scan_info.e_mod = (TUNER_MODULATION_T)ui2_modlation ;
        pt_dvbc_scan_data->t_scan_info.ui4_sym_rate = ui4_sym_rt_K * 1000 ;   /* Ksym/s -> sym/s */
        pt_dvbc_scan_data->t_scan_info.ui4_start_freq = ui4_frq_KHz * 1000 ;  /* KHz -> hz */
        pt_dvbc_scan_data->t_scan_info.ui4_end_freq = ui4_frq_KHz * 1000 ;    /* KHz -> hz */
        pt_dvbc_scan_data->t_scan_info.ui2_nw_id = ui4_nw_id ;    
    }
    
    return WZDR_OK ;
}

#endif  /* APP_DVBC_SUPPORT */


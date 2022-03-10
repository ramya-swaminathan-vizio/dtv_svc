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
 * $RCSfile: a_wdk_wgl_util.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _WDK_WGL_UTIL_H_
#define _WDK_WGL_UTIL_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_wgl_sets.h"
#include "u_wgl_hts.h"
#include "u_wgl_bdr_common.h"
#include "u_iom.h"
#include "u_time_msrt.h"
#include "u_wgl_animation.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

typedef struct 
{
    WGL_HIMG_TPL_T      h_normal;
    WGL_HIMG_TPL_T      h_selected;
    WGL_HIMG_TPL_T      h_highlight;
    WGL_HIMG_TPL_T      h_highlight_unfocus;
    WGL_HIMG_TPL_T      h_pushed;

}WDK_IMAGE1_PARAM_T;

typedef struct
{
    WGL_HIMG_TPL_T      h_enable;
    WGL_HIMG_TPL_T      h_highlight;
    WGL_HIMG_TPL_T      h_disable;

}WDK_IMAGE2_PARAM_T;

typedef struct 
{
    GL_COLOR_T*         pt_normal;
    GL_COLOR_T*         pt_disable;
    GL_COLOR_T*         pt_selected;
    GL_COLOR_T*         pt_highlight;
    GL_COLOR_T*         pt_highlight_unfocus;

}WDK_COLOR1_PARAM_T;

typedef struct 
{
    GL_COLOR_T*         pt_enable;
    GL_COLOR_T*         pt_highlight;
    GL_COLOR_T*         pt_disable;

}WDK_COLOR2_PARAM_T;


typedef struct
{
    HANDLE_T            h_parent;
    UINT8               ui1_alpha;
    BOOL                b_visibility;
    INT32               i4_x;
    INT32               i4_y;
    INT32               i4_w;
    INT32               i4_h;
    UINT32              ui4_style;
    GL_COLOR_T*         pt_clr_bk;
    WDK_IMAGE2_PARAM_T t_img_bk;

    wgl_widget_proc_fct pf_wdgt_proc;
    HANDLE_T*           ph_created_frm;

}  WDK_FRM_WIDGET_PARAM_T;

typedef struct
{
    HANDLE_T            h_parent;
    UINT8               ui1_alpha;
    UINT8                ui1_font_custom_size;    
    BOOL                b_visibility;    
    INT32               i4_x;
    INT32               i4_y;
    INT32               i4_w;
    INT32               i4_h;
    UINT32              ui4_style;
    CHAR*               ps_font_name;    
    FE_FNT_SIZE         e_font_size;
    FE_FNT_STYLE        e_font_style;
    WGL_INSET_T         t_inset;
    UINT8               ui1_align;
    BOOL                b_img_bk;
    WDK_IMAGE2_PARAM_T t_img_bk;
    GL_COLOR_T*         pt_clr_bk;
    GL_COLOR_T*         pt_clr_txt;
    GL_COLOR_T*         pt_hlt_clr_txt;
    GL_COLOR_T*         pt_dis_clr_txt;

    wgl_widget_proc_fct pf_wdgt_proc;
    HANDLE_T*           ph_created_txt;

}  WDK_TXT_WIDGET_PARAM_T;

typedef struct 
{
    HANDLE_T            h_parent;
    UINT8               ui1_alpha;    
    BOOL                b_visibility;        
    INT32               i4_x;
    INT32               i4_y;
    INT32               i4_w;
    INT32               i4_h;
    UINT32              ui4_style;
    BOOL                b_img_bk;
    UINT8               ui1_img_align_style;
    WDK_IMAGE2_PARAM_T  t_img_param;
    GL_COLOR_T*         pt_clr_bk;

    wgl_widget_proc_fct pf_wdgt_proc;
    HANDLE_T*           ph_created_icon;

}  WDK_ICON_WIDGET_PARAM_T;

typedef struct 
{
    HANDLE_T             h_parent;
    WGL_ANIM_INIT_T      t_anim_init;
    UINT8                ui1_alpha;    
    BOOL                 b_visibility;        
    INT32                i4_x;
    INT32                i4_y;
    INT32                i4_w;
    INT32                i4_h;
    BOOL                 b_img_bk;    
    UINT8                ui1_img_align_style;
    WDK_IMAGE2_PARAM_T  t_img_param;
    wgl_widget_proc_fct  pf_wdgt_proc;
    WGL_ANIM_CB_T        t_cond_cb;    
    HANDLE_T*            ph_created_anim;

}  WDK_ANIM_WIDGET_PARAM_T;


typedef struct 
{
    HANDLE_T            h_parent;           
    UINT8               ui1_alpha;          
    BOOL                b_visibility;            
    INT32               i4_x;               
    INT32               i4_y;               
    INT32               i4_w;               
    INT32               i4_h;               
    UINT32              ui4_style;          
    UINT16              ui2_max_elem_num;   
    UINT16              ui2_elem_size;      
    UINT16              ui2_elem_distance;  
    UINT8               ui1_col_num;        
    WGL_LB_COL_INIT_T   at_cols[3];         
    WGL_INSET_T         t_cnt_inset;        
    WGL_INSET_T         t_elem_inset;       
    WGL_INSET_T         at_col_inset[3];
    UINT16              ui2_hlt_margin;     
    CHAR*               ps_font_name;     /* NULL for default */     
    CHAR*               ps_font_name_hlt; /* NULL for default */     
    FE_FNT_SIZE         e_font_size;        
    
    BOOL                b_scrl_bar;         
    INT32               i4_scrl_bar_x;               
    INT32               i4_scrl_bar_y;               
    INT32               i4_scrl_bar_w;               
    INT32               i4_scrl_bar_h;               
    UINT32              ui4_sz_thumb_min;            
    WGL_HIMG_TPL_T      h_scrollbar_bk;              
    WGL_HIMG_TPL_T      h_scrollbar_pt;              

    /* Highlight effect */
    UINT16              ui2_hef_up_shadow;  
    UINT16              ui2_hef_down_shadow;    
    BOOL                b_scroll_effect;

    /* valid only if b_scroll_effect = TRUE */    
    BOOL                b_async_scrolling;           
    BOOL                b_scroll_when_unfocus;

    BOOL                 b_img_bk;                   
    WDK_IMAGE2_PARAM_T  t_img_bk;
    WDK_COLOR2_PARAM_T  t_clr_bk;

    BOOL                 b_vp_img_bk;
    WDK_IMAGE2_PARAM_T  t_vp_img_bk;
    WDK_COLOR2_PARAM_T  t_vp_clr_bk;

    BOOL                 b_elem_img_bk;
    WDK_IMAGE1_PARAM_T  t_elem_img_bk;
    WDK_COLOR1_PARAM_T  t_elem_clr_bk;

    WDK_COLOR1_PARAM_T  t_col_clr_bk;    
    WDK_COLOR1_PARAM_T  t_col_clr_txt;
    
    wgl_widget_proc_fct pf_wdgt_proc;       
    HANDLE_T*           ph_created_lb;      
}  WDK_LB_WIDGET_PARAM_T;

typedef struct
{
    HANDLE_T            h_parent;
    UINT8               ui1_alpha;    
    BOOL                b_visibility;
    INT32               i4_x;
    INT32               i4_y;
    INT32               i4_w;
    INT32               i4_h;
    UINT32              ui4_style;
    CHAR*               ps_font_name;    
    FE_FNT_SIZE         e_font_size;
    FE_FNT_STYLE        e_font_style;    
    INT16               i2_width;
    UINT16              ui2_input_limit;
    UINT8               ui1_align;
    WDK_COLOR2_PARAM_T  t_clr_txt;
    WDK_COLOR2_PARAM_T  t_clr_bk;
    WDK_COLOR2_PARAM_T  t_clr_brd;
    BOOL                b_cursor_nav;
    BOOL                b_auto_edit;
    BOOL                b_always_hlt_cursor;
    BOOL                b_img_bk;
    BOOL                b_char_img;
    WGL_EB_CHAR_IMG_T   t_char_img;
    WDK_IMAGE2_PARAM_T  t_bk_img;    
    WGL_INSET_T         t_inset_info; 
    WGL_INSET_T         t_cnt_inset;
    GL_COLOR_T*         pt_clr_cur;
    UTF16_T             w2s_cursor_char;

    wgl_widget_proc_fct pf_wdgt_proc;
    HANDLE_T*           ph_created_eb;

}  WDK_EDIT_BOX_WIDGET_PARAM_T;

typedef struct
{
    BOOL                b_from_first_char;
    BOOL                b_till_last_char;    
    BOOL                b_repeat;
    UINT32              ui4_ms_delay;    
    UINT16              ui2_scrl_count;    
} WDK_TEXT_WIDGET_SCROLL_PARAM_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_wdk_create_frm_widget (WDK_FRM_WIDGET_PARAM_T t_frm_param);

extern INT32 a_wdk_create_txt_widget (WDK_TXT_WIDGET_PARAM_T t_txt_param);

extern INT32 a_wdk_create_icon_widget (WDK_ICON_WIDGET_PARAM_T t_icon_param);

extern INT32 a_wdk_create_anim_widget (WDK_ANIM_WIDGET_PARAM_T t_anim_param);

extern INT32 a_wdk_create_lb_widget (WDK_LB_WIDGET_PARAM_T t_lb_param);

extern INT32 a_wdk_create_editbox_widget (WDK_EDIT_BOX_WIDGET_PARAM_T t_eb_param);

extern INT32 a_wdk_set_clr_bk (HANDLE_T    h_widget,
                         GL_COLOR_T* pt_enable_clr,
                         GL_COLOR_T* pt_disable_clr,
                         GL_COLOR_T* pt_highlight_clr);

extern INT32 a_wdk_set_text_clr (HANDLE_T    h_widget,
                         GL_COLOR_T* pt_enable_clr,
                         GL_COLOR_T* pt_disable_clr,
                         GL_COLOR_T* pt_highlight_clr);

extern INT32 a_wdk_set_img_bk (HANDLE_T    h_widget,
                         WGL_HIMG_TPL_T                  h_enable_img,
                         WGL_HIMG_TPL_T                  h_disable_img,
                         WGL_HIMG_TPL_T                  h_highlight_img);

extern INT32 a_wdk_set_img_fg (HANDLE_T    h_widget,
                         WGL_HIMG_TPL_T                  h_enable_img,
                         WGL_HIMG_TPL_T                  h_disable_img,
                         WGL_HIMG_TPL_T                  h_highlight_img);


extern INT32 a_wdk_set_font_info(HANDLE_T    h_handle,
                           FE_FNT_SIZE                     e_font_size,
                           FE_FNT_STYLE                    e_font_style,
                           FE_CMAP_ENCODING                e_font_cmap,
                           CHAR*                           ps_font_name,
                           INT16                           i2_width);

extern INT32 a_wdk_text_set_text(HANDLE_T    h_handle,
                         UTF16_T*    pw2s_text);

extern INT32 a_wdk_text_set_text_by_number(HANDLE_T    h_handle,
                                            UINT32      ui4_number);

extern INT32 a_wdk_text_start_scroll_attr(HANDLE_T     h_handle,
                                           WDK_TEXT_WIDGET_SCROLL_PARAM_T*  pt_text_scroll);
                                           
extern INT32 a_wdk_text_stop_scroll_attr (HANDLE_T     h_handle);

extern INT32 a_wdk_lb_set_elem_text (HANDLE_T       h_widget,
                                      UINT16         ui2_elem_idx,
                                      UINT16         ui2_col_idx,
                                      UTF16_T*       pw2s_text);

extern INT32 a_wdk_lb_set_elem_img_suit (HANDLE_T                   h_widget,
                                          UINT16                     ui2_elem_idx,
                                          UINT16                     ui2_col_idx,
                                          WGL_LB_ITEM_IMG_SUIT_T*    pt_img_suit);

extern INT32 a_wdk_lb_set_elem_char_text (HANDLE_T       h_widget,
                                           UINT16         ui2_elem_idx,
                                           UINT16         ui2_col_idx,
                                           CHAR*          ps_str);

extern INT32 a_wdk_editbox_set_text(HANDLE_T    h_handle,
                           UTF16_T*    pw2s_text);

extern INT32 a_wdk_editbox_set_cursor_pos (HANDLE_T    h_handle,
                                  UINT16                ui2_pos);

#endif /* _WDK_WGL_UTIL_H_ */


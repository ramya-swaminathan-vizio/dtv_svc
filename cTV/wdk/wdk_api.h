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
 * $RCSfile: wdk_api.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: Yuankang Li $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _WDK_API_H_
#define _WDK_API_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_sets.h"
#include "c_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* WDK Return Value */
#define WDKR_OK                             ((INT32) 0)
#define WDKR_FAILED                         ((INT32) -1)

#define WDK_COPY(_dst, _src, _size)         \
    if(NULL != (_dst) && (NULL != (_src)))  \
    {c_memcpy ((VOID *)(_dst), (VOID *)(_src), (_size));}

#define WDK_CLR_COPY(_dst, _src)            \
    if(NULL != (_dst) && (NULL != (_src)))  \
    {c_memcpy ((VOID *)(_dst), (VOID *)(_src), sizeof(GL_COLOR_T));}

#define WDK_IMG_COPY(_dst, _src)            \
    if(NULL != (_src))                      \
    {(_dst) = *(_src);}

#ifdef WIN32
#define WDK_CHK_FAIL(_expr)                 \
    if(_expr != 0)                          \
    {                                       \
        while(1){};                          \
        return (WDKR_FAILED);               \
    }
#else
#define WDK_CHK_FAIL(_expr)                 \
    if(_expr != 0)                          \
    {                                       \
        DBG_LOG_PRINT(("<WDK> ERR: file = %s, line = %d, err = %d\n\r", __FILE__, __LINE__, _expr)); \
        return (WDKR_FAILED);               \
    }
#endif

#define WDK_OPT_MASK            (UINT32)0
#define WDK_OPT_MASK_RESERVE    (WDK_OPT_MASK << 31)


typedef UTF16_T* (*wdk_mlm_get_text)(UINT16 ui2_lang, UINT16 ui2_key);

/* -> Mapping from WGL */
typedef struct
{
    GL_COLOR_T              *h_enable;
    GL_COLOR_T              *h_disable;
    GL_COLOR_T              *h_highlight;
    GL_COLOR_T              *h_highlight_inactive;
    GL_COLOR_T              *h_push;
    GL_COLOR_T              *h_push_unhighlight;
} WDK_COLOR_SET_T;

/*Color Information*/
typedef struct
{
    WGL_COLOR_SET_TYPE_T    e_type;
    WDK_COLOR_SET_T         t_color_set;
} WDK_COLOR_INFO_T;

/*Image Sets*/
typedef struct
{
    WGL_HIMG_TPL_T          *h_enable;
    WGL_HIMG_TPL_T          *h_disable;
    WGL_HIMG_TPL_T          *h_highlight;
    WGL_HIMG_TPL_T          *h_highlight_inactive;
    WGL_HIMG_TPL_T          *h_push;
    WGL_HIMG_TPL_T          *h_push_unhighlight;
} WDK_IMG_SET_T;

/*Image Information*/
typedef struct
{
   WGL_IMG_SET_TYPE_T      e_type;
   WDK_IMG_SET_T           t_img_set;
} WDK_IMG_INFO_T;


/*font sets*/
typedef struct
{
   WGL_FONT_INFO_T         *pt_focused;
   WGL_FONT_INFO_T         *pt_unfocused;
} WDK_FONT_SET_T;

/*font info*/
typedef struct
{
    WGL_FONT_SET_TYPE_T     e_type;
    WDK_FONT_SET_T          t_fnt_set;
} WDK_FONT_INFO_T;

/* List Box*/
typedef struct
{
    WGL_FONT_INFO_T     *pt_normal;
    WGL_FONT_INFO_T     *pt_highlight;
    WGL_FONT_INFO_T     *pt_highlight_unfocused;
    WGL_FONT_INFO_T     *pt_selected;
} WDK_LB_FONT_SET_T;

typedef struct
{
    GL_COLOR_T          *h_normal;
    GL_COLOR_T          *h_disable;
    GL_COLOR_T          *h_highlight;
    GL_COLOR_T          *h_highlight_unfocus;
    GL_COLOR_T          *h_pushed;
    GL_COLOR_T          *h_selected;
    GL_COLOR_T          *h_selected_disable;
} WDK_LB_COLOR_SET_T;

typedef struct
{
    WGL_HIMG_TPL_T              *h_normal;
    WGL_HIMG_TPL_T              *h_disable;
    WGL_HIMG_TPL_T              *h_highlight;
    WGL_HIMG_TPL_T              *h_highlight_unfocus;
    WGL_HIMG_TPL_T              *h_pushed;

    WGL_HIMG_TPL_T              *h_selected;
    WGL_HIMG_TPL_T              *h_selected_disable;
    WGL_HIMG_TPL_T              *h_selected_highlight;
    WGL_HIMG_TPL_T              *h_selected_highlight_unfocus;
    WGL_HIMG_TPL_T              *h_selected_pushed;
} WDK_LB_IMG_SET_T;


/* <- Mapping from WGL */

typedef struct
{
    WDK_COLOR_INFO_T*       pt_clr_info;
    WDK_IMG_INFO_T*         pt_img_info;
}  WDK_IMG_CLR_SET_T;

typedef struct
{
    /* WGL_BORDER_NULL */
    /* WGL_BORDER_TRANSP */
    WGL_INSET_T         t_cnt_inset;

    /* WGL_BORDER_UNIFORM */
    WDK_COLOR_INFO_T*    pt_bk_clr;
    WDK_COLOR_INFO_T*    pt_fg_clr;

    UINT32              ui4_thickness;

    /* WGL_BORDER_RAISED */
    UINT32              ui4_height;

    /* WGL_BORDER_TIMG */
    UINT16              ui2_text_id;
    UINT8               ui1_align;
    WGL_FONT_INFO_T*    pt_fnt;
    GL_RECT_T           t_rc_ref;

    WDK_COLOR_INFO_T*    pt_title_clr;
    WDK_IMG_INFO_T *    pt_bk_img;
}  WDK_BORDER_INFO_T;

typedef struct
{
    WDK_LB_COLOR_SET_T*     pt_clr_set;
    WDK_LB_IMG_SET_T*       pt_img_set;
}  WDK_LB_IMG_CLR_SET_T;

typedef struct
{
    WGL_LB_COL_TYPE_T       e_col_type;

    UINT16                  ui2_text_id;
    UINT8                   ui1_align;
    UINT8                   ui1_flag; /* 1: Use Column Setting; 0: Use item Setting */
    WGL_HIMG_TPL_T*         h_img;

}  WDK_LB_ITEM_INFO_T;

typedef struct
{
    UINT32                      ui4_style;
    WGL_INSET_T                 t_ex_margin;
    WDK_LB_IMG_SET_T            t_imgs_bk;
    WGL_LB_TEXT_SCRL_T          t_text_scrl;

} WDK_LB_HLT_ELEM_EFFECT_T;

typedef struct
{
    WDK_IMG_INFO_T            *pt_img_info;
    INT32                     i4_ahead_gap;
} WDK_ICON_MULTI_IMG_NODE_T;

/*
 * Widgets
 */
typedef struct
{
    /* mandatory attribute */
    HANDLE_T            h_parent;
    UINT32              ui4_border;
    WDK_BORDER_INFO_T  *pt_border;
    UINT32              ui4_style;
    UINT8               ui1_alpha;
    wgl_widget_proc_fct pf_wdgt_proc;

    GL_RECT_T           t_rect;
    /* mandatory attribute */

    /* reserve */
    VOID*               pv_data;

}  WDK_WGT_T;


typedef struct
{
    /* mandatory attribute */
    HANDLE_T            h_parent;
    UINT32              ui4_border;
    WDK_BORDER_INFO_T  *pt_border;
    UINT32              ui4_style;
    UINT8               ui1_alpha;
    UINT8               ui1_enable;     /* 0:disable; 1:enable */
    UINT8               ui1_visibility; /* WGL_SW_CMD_T */
    wgl_widget_proc_fct pf_wdgt_proc;

    GL_RECT_T           t_rect;
    /* mandatory attribute */

    WDK_IMG_CLR_SET_T   t_bk_set;

    /* reserve */
    VOID*               pv_data;

}  WDK_FRM_WGT_T;

typedef struct
{
    /* > mandatory attribute */
    HANDLE_T            h_parent;
    UINT32              ui4_border;
    WDK_BORDER_INFO_T  *pt_border;
    UINT32              ui4_style;
    UINT8               ui1_alpha;
    UINT8               ui1_enable;     /* 0:disable; 1:enable */
    UINT8               ui1_visibility; /* WGL_SW_CMD_T */
    wgl_widget_proc_fct pf_wdgt_proc;

    GL_RECT_T           t_rect;
    /* < mandatory attribute */

    WDK_IMG_CLR_SET_T   t_bk_set;
    /* optional attribute */
    UINT16              ui2_text_id;
    UINT8               ui1_align;

    WDK_IMG_INFO_T      *pt_fg_img;
    WGL_INSET_T         t_cnt_inset;

    WDK_FONT_INFO_T     *pt_fnt;
    WDK_COLOR_INFO_T    *pt_clr_text;

    INT32               i4_distance;
    UINT8               ui1_order;

    /* reserved */
    VOID*               pv_data;
}  WDK_BTN_WGT_T;

typedef struct
{
    /* > mandatory attribute */
    HANDLE_T            h_parent;
    UINT32              ui4_border;
    WDK_BORDER_INFO_T  *pt_border;
    UINT32              ui4_style;
    UINT8               ui1_alpha;
    UINT8               ui1_enable;     /* 0:disable; 1:enable */
    UINT8               ui1_visibility; /* WGL_SW_CMD_T */
    wgl_widget_proc_fct pf_wdgt_proc;

    GL_RECT_T           t_rect;
    /* < mandatory attribute */

    WDK_IMG_CLR_SET_T   t_bk_set;

    UINT16              ui2_text_id;
    UINT8               ui1_align;
    WDK_FONT_INFO_T     *pt_fnt;
    WDK_COLOR_INFO_T    *pt_clr_text;

    /* optional attribute */
    WGL_INSET_T         t_cnt_inset;

    INT32               i4_line_gap;    /* WGL_CMD_TEXT_SET_LINE_GAP  */
    UINT16              ui2_max_line;   /* WGL_CMD_TEXT_SET_MAX_DIS_LINE */

    /* reserved */
    VOID*               pv_data;
}  WDK_TXT_WGT_T;

typedef struct
{
    /* > mandatory attribute */
    HANDLE_T                h_parent;
    UINT32                  ui4_border;
    WDK_BORDER_INFO_T       *pt_border;
    UINT32                  ui4_style;
    UINT8                   ui1_alpha;
    UINT8                   ui1_enable;     /* 0:disable; 1:enable */
    UINT8                   ui1_visibility; /* WGL_SW_CMD_T */
    wgl_widget_proc_fct     pf_wdgt_proc;

    GL_RECT_T               t_rect;
    /* < mandatory attribute */

    WDK_IMG_CLR_SET_T       t_bk_set;
    WGL_INSET_T             t_cnt_inset;

    WDK_FONT_INFO_T         *pt_fnt;

    /* LB Element */
    UINT16                  ui2_max_elem_num;
    UINT16                  ui2_elem_num;
    UINT16                  ui2_elem_height;
    UINT16                  ui2_elem_distance;
    WGL_INSET_T             t_elem_inset;

    WDK_LB_IMG_CLR_SET_T     t_elem_bk_set;
    WDK_LB_HLT_ELEM_EFFECT_T *t_hlt_elem_effect;
    UINT16                   ui2_hlt_margin;

    /* LB Column */
    UINT8                   ui1_col_num;
    WGL_LB_COL_INIT_T*      at_col;
    WGL_INSET_T*            at_col_inset;
    WDK_LB_FONT_SET_T*      at_col_font_ex;
    WDK_LB_COLOR_SET_T*     at_col_txt_clr;
    WDK_LB_COLOR_SET_T*     at_col_bk_clr;

    /* LB Item */
    WDK_LB_ITEM_INFO_T*     at_items;
    WDK_LB_FONT_SET_T*      at_item_font_ex;
    WDK_LB_IMG_SET_T*       at_img_set;
    WDK_LB_COLOR_SET_T*     at_text_clr;
    WDK_LB_COLOR_SET_T*     at_bk_clr;

    /* reserve */
    VOID*                   pv_data;
}  WDK_LB_WGT_T;

typedef struct
{
    /* > mandatory attribute */
    HANDLE_T            h_parent;
    UINT32              ui4_border;
    WDK_BORDER_INFO_T  *pt_border;
    UINT32              ui4_style;
    UINT8               ui1_alpha;
    UINT8               ui1_enable;     /* 0:disable; 1:enable */
    UINT8               ui1_visibility; /* WGL_SW_CMD_T */
    wgl_widget_proc_fct pf_wdgt_proc;

    GL_RECT_T           t_rect;
    /* < mandatory attribute */

    WDK_IMG_CLR_SET_T   t_bk_set;
    /* optional attribute */
    UINT32              ui4_display_mode;

    INT32               i4_range_min;
    INT32               i4_range_max;
    INT32               i4_position;

    WGL_PG_LEVELS_INFO_T t_levels;

    WGL_PG_IDR_LOC_T    t_min_idr;
    WGL_PG_IDR_LOC_T    t_pos_idr;
    WGL_PG_IDR_LOC_T    t_max_idr;

    UINT16              u2_block_w;
    UINT16              u2_block_h;

    WGL_INSET_T         t_cnt_inset;
    WGL_INSET_T         t_bar_inset;

    WDK_FONT_INFO_T     *pt_fnt;
    WDK_COLOR_INFO_T    *pt_clr_text;

    WDK_IMG_CLR_SET_T   t_body_set;
    WDK_IMG_CLR_SET_T   at_level_set[WGL_PG_LEVEL_MAX];

    /* reserved */
    VOID*               pv_data;
}  WDK_PB_WGT_T;

typedef struct
{
    /* > mandatory attribute */
    HANDLE_T            h_parent;
    UINT32              ui4_border;
    WDK_BORDER_INFO_T  *pt_border;
    UINT32              ui4_style;
    UINT8               ui1_alpha;
    UINT8               ui1_enable;     /* 0:disable; 1:enable */
    UINT8               ui1_visibility; /* WGL_SW_CMD_T */
    wgl_widget_proc_fct pf_wdgt_proc;

    GL_RECT_T           t_rect;
    /* < mandatory attribute */

    WDK_IMG_CLR_SET_T   t_bk_set;
    WGL_INSET_T         t_cnt_inset;

    /* optional attribute */
    UINT16              ui2_text_id;
    UINT8               ui1_align;
    WDK_FONT_INFO_T     *pt_fnt;
    WDK_COLOR_INFO_T    *pt_clr_text;

    WDK_COLOR_INFO_T    *pt_clr_cursor;

    WGL_EB_MODE_T       t_insert_mode;
    UINT32              ui4_input_limit;
    UINT32              ui4_cursor_pos;

    /* reserved */
    VOID*               pv_data;
}  WDK_EB_WGT_T;

typedef struct
{
    /* > mandatory attribute */
    HANDLE_T            h_parent;
    UINT32              ui4_border;
    WDK_BORDER_INFO_T  *pt_border;
    UINT32              ui4_style;
    UINT8               ui1_alpha;
    UINT8               ui1_enable;     /* 0:disable; 1:enable */
    UINT8               ui1_visibility; /* WGL_SW_CMD_T */
    wgl_widget_proc_fct pf_wdgt_proc;

    GL_RECT_T           t_rect;
    /* < mandatory attribute */

    WDK_IMG_CLR_SET_T   t_bk_set;
    WGL_INSET_T         t_cnt_inset;

    /* optional attribute */
    UINT8               ui1_align;
    WDK_IMG_INFO_T      *pt_fg_img;

    UINT32              u4_multi_image_max;
    UINT32              u4_multi_image_num;

    WDK_ICON_MULTI_IMG_NODE_T *pt_img_node;

    /* reserved */
    VOID*               pv_data;
}  WDK_ICON_WGT_T;


/*
 * External WDK APIs
 */
#define         WDK_FRM_OPT_BK_IMG   (WDK_OPT_MASK  << 0)
#define         WDK_FRM_OPT_BK_CLR   (WDK_OPT_MASK  << 1)

INT32 a_wdk_create_frame(WDK_FRM_WGT_T *pt_frm_param,
                         UINT32         ui4_opt_mask,
                         HANDLE_T      *ph_frm_widget);

#define     WDK_BTN_OPT_BK_IMG      (WDK_OPT_MASK  << 0)
#define     WDK_BTN_OPT_BK_CLR      (WDK_OPT_MASK  << 1)
#define     WDK_BTN_OPT_FG_IMG      (WDK_OPT_MASK  << 2)
#define     WDK_BTN_OPT_TXT_CLR     (WDK_OPT_MASK  << 3)
#define     WDK_BTN_OPT_FONT        (WDK_OPT_MASK  << 4)
#define     WDK_BTN_OPT_FONT_EX     (WDK_OPT_MASK  << 5)
#define     WDK_BTN_OPT_INSET       (WDK_OPT_MASK  << 6)
#define     WDK_BTN_OPT_TEXT        (WDK_OPT_MASK  << 7)
#define     WDK_BTN_OPT_DIST        (WDK_OPT_MASK  << 8)
#define     WDK_BTN_OPT_ALIGN       (WDK_OPT_MASK  << 9)
#define     WDK_BTN_OPT_DIRECTION   (WDK_OPT_MASK  << 10)

INT32 a_wdk_create_button(WDK_BTN_WGT_T *pt_btn_param,
                          UINT32         ui4_opt_mask,
                          HANDLE_T      *ph_btn_widget);

INT32 a_wdk_create_text (WDK_TXT_WGT_T *pt_wgt_param,
                        UINT32         ui4_opt_mask,
                        HANDLE_T      *ph_widget);

INT32 a_wdk_create_icon (WDK_ICON_WGT_T *pt_wgt_param,
                        UINT32         ui4_opt_mask,
                        HANDLE_T      *ph_widget);

INT32 a_wdk_create_pb (WDK_PB_WGT_T *pt_wgt_param,
                        UINT32         ui4_opt_mask,
                        HANDLE_T      *ph_widget);

INT32 a_wdk_create_eb (WDK_EB_WGT_T *pt_wgt_param,
                        UINT32         ui4_opt_mask,
                        HANDLE_T      *ph_widget);

INT32 a_wdk_create_lb (WDK_LB_WGT_T *pt_wgt_param,
                        UINT32         ui4_opt_mask,
                        HANDLE_T      *ph_widget);

/*
 * WDK_ITEM_T
 */
typedef struct
{
    HANDLE_TYPE_T   e_type;
    UINT16          u2_id;
    UINT32          ui4_opt_mask;
    VOID *          p_param;
    VOID *          p_child;
} WDK_ITEM_T;

typedef struct
{
    UINT32       ui4_num;
    WDK_ITEM_T * p_item_list;
} WDK_ITEM_LIST_T;

typedef VOID * WDK_UI_MI_T;


extern INT32 a_wdk_create_widgets(HANDLE_T h_container,
                                  WDK_ITEM_LIST_T *pt_wdk_list,
                                  HANDLE_T *ph_handle,
                                  wgl_widget_proc_fct *pf_cb);

extern INT32 a_wdk_destory_widgets(WDK_ITEM_LIST_T *pt_wdk_list,
                                   HANDLE_T *ph_handle);

extern INT32 a_wdk_widgets_update_text(WDK_ITEM_LIST_T *pt_wdk_list,
                                       HANDLE_T *ph_handle,
                                       wdk_mlm_get_text pf_get_text,
                                       UINT16 ui2_lang);

extern INT32 a_wdk_widgets_get_param(WDK_ITEM_LIST_T *pt_wdk_list,
                                     UINT16 ui2_wgt_id,
                                     WDK_WGT_T **pt_wgt_param);

#endif /* _WDK_API_H_ */



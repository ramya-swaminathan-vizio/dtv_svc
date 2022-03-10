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
 * $RCSfile: menu_help_lst.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/19 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 7ed3c11a9ed90eba15305b24039bcab7 $
 *
 * Description:
 *      This file contains the implementation of channel lists.
 *---------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_lb_cnt_common.h"
#include "u_wgl_tools.h"

#include "c_os.h"
#include "c_handle.h"
#include "c_fe.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_sets.h"
#include "c_uc_str.h"
 
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_help_lst.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define HELP_LST_BUCKET_NUM(pt_help_lst)    \
    (pt_help_lst)->pt_help_lst_init->ui2_bucket_num
#define HELP_LST_HELP_NUM(pt_help_lst)      \
    (pt_help_lst)->pt_help_lst_init->ui2_help_num
#define HELP_LST_BUCKET(pt_help_lst, ui2_bucket)      \
    (pt_help_lst)->pt_help_lst_data[ui2_bucket]
/*    (pt_help_lst)->pt_help_lst_init->pt_help_lst_data[ui2_idx * HELP_LST_BUCKET_NUM(pt_help_lst) + ui2_bucket]*/
    
#define HELP_LST_IN_GAP(pt_help_lst)        \
    (pt_help_lst)->pt_help_lst_init->ui2_in_gap
#define HELP_LST_OUT_GAP(pt_help_lst)       \
    (pt_help_lst)->pt_help_lst_init->ui2_out_gap    
#define HELP_LST_FONT(pt_help_lst)          \
    (pt_help_lst)->h_font
#define HELP_LST_LB(pt_help_lst)            \
    (pt_help_lst)->h_lb
#define HELP_LST_AS(pt_help_lst)            \
    (pt_help_lst)->pt_help_lst_init->e_align_style
#define HELP_LST_LS(pt_help_lst)            \
    (pt_help_lst)->pt_help_lst_init->e_layout_style
#define HELP_LST_IMG_COL(pt_help_lst, ui2_bucket)               \
    (UINT16)(HELP_LST_LS(pt_help_lst) == MENU_HELP_LST_LS_IMG_FIRST ?   \
     (2*(ui2_bucket)) : (2 * (ui2_bucket) + 1))
#define HELP_LST_TXT_COL(pt_help_lst, ui2_bucket)               \
    (UINT16)(HELP_LST_LS(pt_help_lst) == MENU_HELP_LST_LS_TXT_FIRST ?   \
     (2*(ui2_bucket)) : (2 * (ui2_bucket) + 1))
#define HELP_LST_IS_IMG_COL(pt_help_lst, ui2_bucket)                \
    (BOOL)((HELP_LST_LS(pt_help_lst) == MENU_HELP_LST_LS_IMG_FIRST) ^ \
           ((ui2_bucket % 2) == 1))
#define HELP_LST_MAX(_x, _y) ((_x) > (_y) ? (_x) : (_y)) 

#ifndef MENU_HELP_LST_AS_RIGHT_ALLIGN
    #define MENU_HELP_LST_AS_RIGHT_ALLIGN         
    #define MENU_HELP_LST_AS_RIGHT_IMG_ALLIGN WGL_AS_RIGHT_CENTER
    #define MENU_HELP_LST_AS_RIGHT_TXT_ALLIGN WGL_AS_RIGHT_CENTER
#endif

#ifndef MENU_HELP_LST_AS_LEFT_ALLIGN
    #define MENU_HELP_LST_AS_LEFT_ALLIGN         
    #define MENU_HELP_LST_AS_LEFT_IMG_ALLIGN WGL_AS_LEFT_CENTER
    #define MENU_HELP_LST_AS_LEFT_TXT_ALLIGN WGL_AS_LEFT_CENTER
#endif
typedef struct _HELP_LST_T
{
    MENU_HELP_LST_INIT_T*       pt_help_lst_init;
    MENU_HELP_LST_BUCKET_T*     pt_help_lst_data;  /* ui2_bucket_num element array */
    HANDLE_T                    h_lb;
    HANDLE_T                    h_font;
} HELP_LST_T;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _help_lst_set_attach_data
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
static INT32 _help_lst_set_attach_data(HANDLE_T     h_help_lst,
                                       HELP_LST_T*  pt_help_lst)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_help_lst,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_help_lst),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_lst_get_attach_data
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
static INT32 _help_lst_get_attach_data(HANDLE_T         h_help_lst,
                                       HELP_LST_T**     ppt_help_lst)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_help_lst,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_help_lst),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_lst_do_layout
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
INT32 _help_lst_do_layout(HELP_LST_T*   pt_help_lst)
{
    INT32 i4_ret;
    UINT16      ui2_col;
    UINT32      ui4_width;
    UINT32      ui4_height;
    UINT32      ui4_ttl_width=0;
    WGL_INSET_T t_inset;
    GL_RECT_T   t_rect;

    if( HELP_LST_AS(pt_help_lst) == MENU_HELP_LST_AS_FIX )
    {
        /* no layout adjustment required */
        return MENUR_OK;
    }
   
    for (ui2_col = 0; 
         ui2_col < (UINT16)(HELP_LST_BUCKET_NUM(pt_help_lst) * 2); 
         ui2_col ++)
    {
        BOOL    b_is_img = HELP_LST_IS_IMG_COL(pt_help_lst, ui2_col);
        MENU_HELP_LST_BUCKET_T t_bucket = 
            HELP_LST_BUCKET(pt_help_lst, ui2_col/2);

        /* get the data width */
        if(b_is_img)
        {
            /* image coloum*/
            if (t_bucket.h_img == NULL_HANDLE)
            {
                ui4_width = 0;
            }
            else
            {
                i4_ret = c_wgl_img_tpl_get_size(t_bucket.h_img,
                                                &ui4_width, 
                                                &ui4_height);
                if(i4_ret != 0)
                {
                    DBG_ERROR(("<MENU>Can't get image size:%d\r\n", ui2_col));
                }
                MENU_CHK_FAIL(i4_ret);
            }
        }
        else
        {
            UTF16_T*    w2s_str = MENU_TEXT(t_bucket.ui2_msg_id);
            SIZE_T      z_len = c_uc_w2s_strlen(w2s_str);
    
            if (z_len == 0)
            {
                ui4_width = 0;
            }
            else
            {
                i4_ret = c_fe_get_string_size(pt_help_lst->h_font, 
                                              w2s_str, 
                                              (INT32)z_len, 
                                              (INT32*)&ui4_width, 
                                              (INT32*)&ui4_height);
                MENU_CHK_FAIL(i4_ret);
            }
        }

        /* set the col width */
        if( ui4_width == 0)
        {
            
        }
        else if( ((HELP_LST_AS(pt_help_lst) == MENU_HELP_LST_AS_LEFT) && (ui2_col % 2 == 0)) ||
                 ((HELP_LST_AS(pt_help_lst) == MENU_HELP_LST_AS_RIGHT)&& (ui2_col % 2 == 1)))
        {
            ui4_width += HELP_LST_IN_GAP(pt_help_lst);
        }
        else
        {
            ui4_width += HELP_LST_OUT_GAP(pt_help_lst);
        }
        i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb,
                              WGL_CMD_LB_SET_COL_WIDTH,
                              WGL_PACK((UINT8)ui2_col),
                              WGL_PACK(((UINT16)ui4_width)));
        MENU_CHK_FAIL(i4_ret);

        /* count the total width */
        ui4_ttl_width+=ui4_width;
    }

    c_wgl_get_coords(pt_help_lst->h_lb, WGL_COORDS_PARENT, &t_rect);

    /* Change the inset */
    c_memcpy(&t_inset, 
             &pt_help_lst->pt_help_lst_init->t_cnt_inset, 
             sizeof(WGL_INSET_T));

    if( HELP_LST_AS(pt_help_lst) == MENU_HELP_LST_AS_RIGHT )
    {
        t_inset.i4_left = t_rect.i4_right - 
                          t_rect.i4_left -
                          t_inset.i4_right -
                          ui4_ttl_width;
        t_inset.i4_left = HELP_LST_MAX(t_inset.i4_left,
                                       pt_help_lst->pt_help_lst_init->t_cnt_inset.i4_left);
    }
    else
    {
        t_inset.i4_right = t_rect.i4_right - 
                           t_rect.i4_left  - 
                           t_inset.i4_left -
                           ui4_ttl_width;
        t_inset.i4_right = HELP_LST_MAX(t_inset.i4_right,
                                        pt_help_lst->pt_help_lst_init->t_cnt_inset.i4_right);
        
    }
    i4_ret = c_wgl_do_cmd (pt_help_lst->h_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _help_lst_chg_theme
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
INT32 _help_lst_chg_theme(HELP_LST_T*   pt_help_lst)
{
    INT32   i4_ret;
    UINT16  ui2_i;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_COLOR_INFO_T            t_clr_info;

    /* Set LB colors  */
    MENU_COLOR_COPY(&t_lb_color.t_normal, &t_g_menu_color_help_txt);
    MENU_COLOR_COPY(&t_lb_color.t_disable, &t_g_menu_color_help_txt);
    MENU_COLOR_COPY(&t_lb_color.t_highlight, &t_g_menu_color_help_txt);
    MENU_COLOR_COPY(&t_lb_color.t_highlight_unfocus, &t_g_menu_color_help_txt);
    MENU_COLOR_COPY(&t_lb_color.t_pushed, &t_g_menu_color_help_txt);
    MENU_COLOR_COPY(&t_lb_color.t_selected, &t_g_menu_color_help_txt);
    MENU_COLOR_COPY(&t_lb_color.t_selected_disable, &t_g_menu_color_help_txt);

    for (ui2_i=0; 
         ui2_i< HELP_LST_BUCKET_NUM(pt_help_lst);
         ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(HELP_LST_TXT_COL(pt_help_lst, ui2_i), 
                                     WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
        MENU_CHK_FAIL(i4_ret);
    }

    MENU_COLOR_COPY(&t_lb_color.t_normal, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_lb_color.t_disable, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_lb_color.t_highlight, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_lb_color.t_highlight_unfocus, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_lb_color.t_pushed, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_lb_color.t_selected, &t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_lb_color.t_selected_disable, &t_g_menu_color_transp);
    i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_CHK_FAIL(i4_ret);

    for (ui2_i=0; 
         ui2_i< (UINT16)(HELP_LST_BUCKET_NUM(pt_help_lst) * 2);
         ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        MENU_CHK_FAIL(i4_ret);
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_menu_color_transp);
    MENU_COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_menu_color_transp);
    i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_lst_chg_lang
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
INT32 _help_lst_chg_lang(HELP_LST_T*   pt_help_lst)
{
    INT32   i4_ret = 0; 
    UINT16 ui2_i = 0;

    for (ui2_i=0; ui2_i<HELP_LST_BUCKET_NUM(pt_help_lst); ui2_i++)
    {
        UTF16_T* w2s_str = MENU_TEXT(HELP_LST_BUCKET(pt_help_lst, ui2_i).ui2_msg_id);
        UINT16   ui2_col = HELP_LST_TXT_COL(pt_help_lst, ui2_i);
        i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb, 
                              WGL_CMD_LB_SET_ITEM_TEXT, 
                              WGL_PACK_2(0, ui2_col), 
                              WGL_PACK(w2s_str));
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = _help_lst_do_layout(pt_help_lst);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _help_lst_chg_data
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
INT32 _help_lst_chg_data(
    HELP_LST_T*   pt_help_lst,
    MENU_HELP_LST_BUCKET_T* pt_buckets,
    UINT16      ui2_num)
{
    INT32  i4_ret;
    UINT16 ui2_i;

    if( HELP_LST_AS(pt_help_lst) == MENU_HELP_LST_AS_FIX ||
        HELP_LST_AS(pt_help_lst) == MENU_HELP_LST_AS_LEFT)
    {
        for(ui2_i = 0; 
            ui2_i < pt_help_lst->pt_help_lst_init->ui2_bucket_num; 
            ui2_i ++)
        {
            if(ui2_i < ui2_num)
            {
                c_memcpy(pt_help_lst->pt_help_lst_data + ui2_i,
                         pt_buckets + ui2_i,
                         sizeof(MENU_HELP_LST_BUCKET_T));
            }
            else
            {
                c_memset(pt_help_lst->pt_help_lst_data + ui2_i,
                         0,
                         sizeof(MENU_HELP_LST_BUCKET_T));
            }
        }
    }
    else /* if(HELP_LST_AS(pt_help_lst) == MENU_HELP_LST_AS_RIGHT) */
    {
        UINT16 ui2_bucket_num = pt_help_lst->pt_help_lst_init->ui2_bucket_num;
        for(ui2_i = 0; 
            ui2_i < ui2_bucket_num; 
            ui2_i ++)
        {
            if(ui2_i < ui2_num)
            {
                c_memcpy(pt_help_lst->pt_help_lst_data + (ui2_bucket_num - ui2_i - 1),
                         pt_buckets + (ui2_num - ui2_i - 1),
                         sizeof(MENU_HELP_LST_BUCKET_T));
            }
            else
            {
                c_memset(pt_help_lst->pt_help_lst_data + (ui2_bucket_num - ui2_i - 1),
                         0,
                         sizeof(MENU_HELP_LST_BUCKET_T));
            }
        }
    }

    for (ui2_i=0; ui2_i<HELP_LST_BUCKET_NUM(pt_help_lst); ui2_i++)
    {
        UTF16_T*    w2s_str;
        UINT16      ui2_col;
        WGL_HIMG_TPL_T  h_img;

        w2s_str = MENU_TEXT(HELP_LST_BUCKET(pt_help_lst, ui2_i).ui2_msg_id);
        ui2_col = HELP_LST_TXT_COL(pt_help_lst, ui2_i);
        i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb, 
                              WGL_CMD_LB_SET_ITEM_TEXT, 
                              WGL_PACK_2(0, ui2_col), 
                              WGL_PACK(w2s_str));
        MENU_CHK_FAIL(i4_ret);

        h_img = HELP_LST_BUCKET(pt_help_lst, ui2_i).h_img;
        ui2_col = HELP_LST_IMG_COL(pt_help_lst, ui2_i);
        i4_ret = c_wgl_do_cmd(pt_help_lst->h_lb, 
                              WGL_CMD_LB_SET_ITEM_IMAGE, 
                              WGL_PACK_2(0, ui2_col), 
                              WGL_PACK(h_img));
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = _help_lst_do_layout(pt_help_lst);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_help_lst_chg_theme
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
INT32 menu_help_lst_chg_theme(HANDLE_T    h_help_lst)
{
    INT32       i4_ret;
    HELP_LST_T* pt_help_lst;

    i4_ret = _help_lst_get_attach_data(h_help_lst, &pt_help_lst);
    MENU_CHK_FAIL(i4_ret);

    return _help_lst_chg_theme(pt_help_lst);
}

/*----------------------------------------------------------------------------
 * Name: menu_help_lst_chg_lang
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
INT32 menu_help_lst_chg_lang(HANDLE_T    h_help_lst)
{
    INT32       i4_ret;
    HELP_LST_T* pt_help_lst;

    i4_ret = _help_lst_get_attach_data(h_help_lst, &pt_help_lst);
    MENU_CHK_FAIL(i4_ret);

    return _help_lst_chg_lang(pt_help_lst);
}

/*----------------------------------------------------------------------------
 * Name: menu_help_lst_chg_data
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
INT32 menu_help_lst_chg_data(
    HANDLE_T    h_help_lst,
    MENU_HELP_LST_BUCKET_T* pt_buckets,
    UINT16      ui2_num)
{
    INT32       i4_ret;
    HELP_LST_T* pt_help_lst;

    i4_ret = _help_lst_get_attach_data(h_help_lst, &pt_help_lst);
    MENU_CHK_FAIL(i4_ret);

    return _help_lst_chg_data(pt_help_lst,
                              pt_buckets,
                              ui2_num);
}

/*----------------------------------------------------------------------------
 * Name: menu_help_lst_init
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
INT32 menu_help_lst_init(HANDLE_T    h_parent,
                         INT32       i4_x,
                         INT32       i4_y,
                         INT32       i4_w,
                         INT32       i4_h,
                         MENU_HELP_LST_INIT_T*   pt_help_lst_init,
                         wgl_widget_proc_fct pf_wdgt_proc,
                         HANDLE_T*   ph_help_list)
{
    INT32                       i4_ret;

    if(pt_help_lst_init == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* create the listbox */
    {
        UINT16                      ui2_i;
        WGL_LB_INIT_T               t_lb_init;
        WGL_LB_COL_INIT_T*          pt_cols;
        WGL_INSET_T                 t_inset;
        GL_RECT_T                   t_rect;

        pt_cols = (WGL_LB_COL_INIT_T*) 
            c_mem_alloc((SIZE_T)(sizeof(WGL_LB_COL_INIT_T) * 
                                 pt_help_lst_init->ui2_bucket_num *
                                 2));
        if(pt_cols == NULL)
        {
            return MENUR_OUT_OF_MEMORY;
        }

        for (ui2_i = 0; ui2_i < pt_help_lst_init->ui2_bucket_num; ui2_i++)
        {
            UINT8   ui1_img_align;
            UINT8   ui1_txt_align;
            UINT16  ui2_img_width;
            UINT16  ui2_txt_width;

            if(pt_help_lst_init->e_align_style == MENU_HELP_LST_AS_LEFT)
            {
                ui1_img_align = MENU_HELP_LST_AS_LEFT_IMG_ALLIGN;
                ui1_txt_align = MENU_HELP_LST_AS_LEFT_TXT_ALLIGN;
                ui2_img_width = 0;
                ui2_txt_width = 0;
            }
            else if(pt_help_lst_init->e_align_style == MENU_HELP_LST_AS_RIGHT)
            {
               ui1_img_align = MENU_HELP_LST_AS_RIGHT_IMG_ALLIGN;
                ui1_txt_align = MENU_HELP_LST_AS_RIGHT_TXT_ALLIGN;
                ui2_img_width = 0;
                ui2_txt_width = 0;
            }
            else /* if(pt_help_lst_init->e_align_style == MENU_HELP_LST_AS_FIX) */
            {
                ui1_img_align = pt_help_lst_init->ui1_col_img_align;
                ui1_txt_align = pt_help_lst_init->ui1_col_txt_align;
                ui2_img_width = pt_help_lst_init->ui2_col_img_width;
                ui2_txt_width = pt_help_lst_init->ui2_col_txt_width;
            }

                    
            if(pt_help_lst_init->e_layout_style == MENU_HELP_LST_LS_IMG_FIRST)
            {
                pt_cols[ui2_i*2].e_col_type       = LB_COL_TYPE_IMG;
                pt_cols[ui2_i*2].ui1_align        = ui1_img_align;
                pt_cols[ui2_i*2].ui2_width        = ui2_img_width;
    
                pt_cols[ui2_i*2+1].e_col_type       = LB_COL_TYPE_TEXT;
                pt_cols[ui2_i*2+1].ui1_align        = ui1_txt_align;
                pt_cols[ui2_i*2+1].ui2_max_text_len = 32;
                pt_cols[ui2_i*2+1].ui2_width        = ui2_txt_width;
                
            }
            else
            {
                pt_cols[ui2_i*2].e_col_type       = LB_COL_TYPE_TEXT;
                pt_cols[ui2_i*2].ui1_align        = ui1_txt_align;
                pt_cols[ui2_i*2].ui2_max_text_len = 32;
                pt_cols[ui2_i*2].ui2_width        = ui2_txt_width;

                pt_cols[ui2_i*2+1].e_col_type       = LB_COL_TYPE_IMG;
                pt_cols[ui2_i*2+1].ui1_align        = ui1_img_align;
                pt_cols[ui2_i*2+1].ui2_width        = ui2_img_width;
            }
        }
    
        /* pre-selected */
        t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT;
        t_lb_init.ui2_max_elem_num  = 1;
        t_lb_init.ui2_elem_size     = (UINT16) (i4_h - 
                                      pt_help_lst_init->t_cnt_inset.i4_top -
                                      pt_help_lst_init->t_cnt_inset.i4_bottom);
        t_lb_init.ui2_elem_distance = 0;
        t_lb_init.ui1_col_num       = (UINT8)(pt_help_lst_init->ui2_bucket_num * 2);
        t_lb_init.at_cols           = pt_cols;
    
        SET_RECT_BY_SIZE (&t_rect,
                          i4_x,
                          i4_y,
                          i4_w,
                          i4_h);
    
        i4_ret = c_wgl_create_widget (h_parent,
                                      HT_WGL_WIDGET_LIST_BOX,
                                      WGL_CONTENT_LIST_BOX_DEF,
                                      WGL_BORDER_NULL,
                                      &t_rect,
                                      NULL,
                                      255,
                                      & t_lb_init,
                                      NULL,
                                      ph_help_list);
        if (i4_ret != WGLR_OK)
        {
            return MENUR_CANT_CREATE_WIDGET;
        }

        c_mem_free(pt_cols);
    
        /* Set Font */
        for (ui2_i = 0; ui2_i < pt_help_lst_init->ui2_bucket_num; ui2_i++)
        {
            UINT16 ui2_idx = (UINT16)
                (pt_help_lst_init->e_layout_style == MENU_HELP_LST_LS_IMG_FIRST ?
                 ui2_i * 2 + 1 :
                 ui2_i * 2);
            
            i4_ret = c_wgl_do_cmd (*ph_help_list,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK(ui2_idx),
                                   WGL_PACK(&pt_help_lst_init->t_font_info));
            MENU_CHK_FAIL(i4_ret);
        }
    
        /* Set Inset. Set all the insets to 0 and they will be modified at 
           runtime when doing layout */
        t_inset.i4_left   = 0;
        t_inset.i4_right  = 0;
        t_inset.i4_top    = 0;
        t_inset.i4_bottom = 0;
   
        i4_ret = c_wgl_do_cmd (*ph_help_list,
                               WGL_CMD_LB_SET_CNT_INSET,
                               WGL_PACK(&pt_help_lst_init->t_cnt_inset),
                               NULL);
        MENU_CHK_FAIL(i4_ret);
    
        i4_ret = c_wgl_do_cmd (*ph_help_list,
                               WGL_CMD_LB_SET_ELEM_INSET,
                               WGL_PACK(&t_inset),
                               NULL);
        MENU_CHK_FAIL(i4_ret);
    
        for (ui2_i = 0; 
             ui2_i < (UINT16)(pt_help_lst_init->ui2_bucket_num * 2); 
             ui2_i++)
        {
            i4_ret = c_wgl_do_cmd (*ph_help_list,
                                   WGL_CMD_LB_SET_COL_INSET,
                                   WGL_PACK(ui2_i),
                                   WGL_PACK(&t_inset));
            MENU_CHK_FAIL(i4_ret);
        }
    }

    /* Append Element */
    {
        WGL_LB_ITEM_T*   pt_items;
        UTF16_T          w2s_empty[] = {0};

        INT32 i4_i = 0;

        pt_items = (WGL_LB_ITEM_T*)
            c_mem_alloc((SIZE_T)(sizeof(WGL_LB_ITEM_T) *
                                 pt_help_lst_init->ui2_bucket_num *
                                 2));
        if(pt_items == NULL)
        {
            return MENUR_OUT_OF_MEMORY;
        }

        for (i4_i=0; i4_i< (INT32)pt_help_lst_init->ui2_bucket_num; i4_i++)
        {
            if(pt_help_lst_init->e_layout_style == MENU_HELP_LST_LS_IMG_FIRST)
            {
                pt_items[i4_i*2].e_col_type = LB_COL_TYPE_IMG;
                pt_items[i4_i*2].data.h_img = NULL_HANDLE;
                pt_items[i4_i*2+1].e_col_type = LB_COL_TYPE_TEXT;
                pt_items[i4_i*2+1].data.pw2s_text = w2s_empty;
            }
            else
            {
                pt_items[i4_i*2].e_col_type = LB_COL_TYPE_TEXT;
                pt_items[i4_i*2].data.pw2s_text = w2s_empty;
                pt_items[i4_i*2+1].e_col_type = LB_COL_TYPE_IMG;
                pt_items[i4_i*2+1].data.h_img = NULL_HANDLE;
            }
        }
        i4_ret = c_wgl_do_cmd(*ph_help_list, 
                              WGL_CMD_LB_APPEND_ELEM, 
                              pt_items, 
                              NULL );

        c_mem_free(pt_items);
        MENU_CHK_FAIL(i4_ret);
    }

    /* Allocate help list data object */
    {
        
        HELP_LST_T* pt_help_lst;
        SIZE_T      z_size1 = sizeof(HELP_LST_T);
        SIZE_T      z_size2 = sizeof(MENU_HELP_LST_INIT_T);
        SIZE_T      z_size3 = sizeof(MENU_HELP_LST_BUCKET_T) *
                              pt_help_lst_init->ui2_bucket_num;
        WGL_FONT_INFO_T* pt_font_info = &pt_help_lst_init->t_font_info;

        /* pt_help_lst */
        pt_help_lst = (HELP_LST_T*)
            c_mem_alloc(z_size1);
        if(pt_help_lst == NULL)
        {
            return MENUR_OUT_OF_MEMORY;
        }
        c_memset(pt_help_lst, 0, z_size1);

        /* pt_help_lst->h_font */
        if(c_strlen(pt_font_info->a_c_font_name) == 0)
        {
            i4_ret= c_fe_create_font(NULL,
                                     pt_font_info->e_font_size, 
                                     pt_font_info->e_font_style, 
                                     pt_font_info->e_font_cmap, 
                                     &pt_help_lst->h_font);
        }
        else
        {
            i4_ret= c_fe_create_font(pt_font_info->a_c_font_name,
                                     pt_font_info->e_font_size, 
                                     pt_font_info->e_font_style, 
                                     pt_font_info->e_font_cmap, 
                                     &pt_help_lst->h_font);
        }
        if(i4_ret != FER_OK)
        {
            c_mem_free(pt_help_lst);
            return MENUR_FAIL;
        }

        /* pt_help_lst->h_lb */
        pt_help_lst->h_lb = *ph_help_list;

        /* pt_help_lst->pt_help_lst_init */
        pt_help_lst->pt_help_lst_init = (MENU_HELP_LST_INIT_T*)
            c_mem_alloc(z_size2);
        if(pt_help_lst->pt_help_lst_init == NULL)
        {
            c_handle_free(pt_help_lst->h_font);
            c_mem_free(pt_help_lst);
            return MENUR_OUT_OF_MEMORY;
        }
        
        c_memcpy(pt_help_lst->pt_help_lst_init,
                 pt_help_lst_init,
                 z_size2);

        /* pt_help_lst->pt_help_lst_init->ppt_help_lst_data */
        pt_help_lst->pt_help_lst_data = (MENU_HELP_LST_BUCKET_T*)c_mem_alloc(z_size3);
        if(pt_help_lst->pt_help_lst_data == NULL)
        {
            c_handle_free(pt_help_lst->h_font);
            c_mem_free(pt_help_lst->pt_help_lst_init);
            c_mem_free(pt_help_lst);
            return MENUR_OUT_OF_MEMORY;
        }
        c_memset(pt_help_lst->pt_help_lst_data, 0, z_size3);

        /* Attach back to the listbox */
        i4_ret = _help_lst_set_attach_data(*ph_help_list, pt_help_lst);
        if(i4_ret != MENUR_OK)
        {
            c_handle_free(pt_help_lst->h_font);
            c_mem_free(pt_help_lst->pt_help_lst_data);
            c_mem_free(pt_help_lst->pt_help_lst_init);
            c_mem_free(pt_help_lst);
            return i4_ret;
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_help_lst_destroy
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
INT32 menu_help_lst_destroy(HANDLE_T    h_help_lst)
{
    INT32       i4_ret;
    HELP_LST_T* pt_help_lst;

    i4_ret = _help_lst_get_attach_data(h_help_lst,
                                       &pt_help_lst);
    MENU_CHK_FAIL(i4_ret);

    if(pt_help_lst != NULL)
    {
        if(pt_help_lst->h_font != NULL_HANDLE)
        {
            c_handle_free(pt_help_lst->h_font);
        }

        if(pt_help_lst->pt_help_lst_init != NULL)
        {
            c_mem_free(pt_help_lst->pt_help_lst_init);
        }

        if(pt_help_lst->pt_help_lst_data != NULL)
        {
            c_mem_free(pt_help_lst->pt_help_lst_data);
        }

        c_mem_free(pt_help_lst);
    }

    c_wgl_destroy_widget(h_help_lst);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_help_lst_chg_idx
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
INT32 menu_help_lst_chg_idx(HANDLE_T    h_help_lst,
                            UINT16      ui2_idx)
{
    return menu_help_lst_chg_data(h_help_lst, NULL, 0);
}

/*----------------------------------------------------------------------------
 * Name: menu_help_lst_get_idx
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
INT32 menu_help_lst_get_idx(HANDLE_T    h_help_lst,
                            UINT16*     pui2_idx)
{
    if(pui2_idx == NULL)
    {
        return MENUR_INV_ARG;
    }

    *pui2_idx = 0;

    return MENUR_OK;
}



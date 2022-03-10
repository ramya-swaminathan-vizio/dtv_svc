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
 * $RCSfile: cnt_indctr.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                     include files
-----------------------------------------------------------------------------*/
#include "c_os.h"
#include "c_wgl.h"
#include "u_wgl_obj_type.h"

#include "wdk/cnt_indctr/cnt_indctr.h"

#include "res/wdk/wdk_img.h"

/*-----------------------------------------------------------------------------
                     macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef struct _WDK_CNT_INDCTR_T
{
    /* Internal Control */
#if 0
    NAV_CLOCK_T*                pt_ctrl;

    /* Widgets */

    HANDLE_T                    h_frame;
    HANDLE_T                    h_txt_msg;

    /* Widgets Resource: Template image */

    WGL_HIMG_TPL_T              h_img_bk;
#endif
} WDK_CNT_INDCTR_T;

#define CNT_INDCTR_NUM          4

typedef struct _CNT_INDCTR_UI_DATA_T
{
    UINT32                      ui4_style_mask;

    UINT16                      ui2_first_indctr;
    UINT16                      ui2_indctr_mask;
    INT16                       i2_inset_up;
    INT16                       i2_inset_down;
    INT16                       i2_inset_left;
    INT16                       i2_inset_right;
    GL_RECT_T                   t_rect;
    HANDLE_T                    h_indctr[CNT_INDCTR_NUM];
} CNT_INDCTR_UI_DATA_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
//static NAV_CLOCK_VIEW_T t_g_nav_clock_view       = {0};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      a_wait_indctr_create
 * Description
 *      Application widget waiting indicator create fct.
 * Input arguments
 *      pt_init_date -
 * Output arguments
 *      ph_indicator -
 * Returns
 *      WDK_OK
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_create (
                    CNT_INDCTR_INIT_T*          pt_init_data,       /* IN */
                    HANDLE_T*                   ph_indicator)       /* OUT */
{
    GL_RECT_T               t_rect;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    UINT16                  ui2_idx;
    UINT32                  ui2_indctr_mask;
    INT32                   i4_ret;
    WGL_IMG_INFO_T          t_img_info;

    /* Check init data */
    if(pt_init_data == NULL)
    {
        return WDKR_INV_ARG;
    }
    ui2_indctr_mask = (UINT16)pt_init_data->ui4_indctr_mask & 0xf;
    if (ui2_indctr_mask == 0)
    {
        return WDKR_INV_ARG;
    }

    /* allocation memory for indicator widgets */
    pt_ui_data = (CNT_INDCTR_UI_DATA_T*)c_mem_alloc(sizeof(CNT_INDCTR_UI_DATA_T));
    if (NULL == pt_ui_data)
    {
        return WDKR_FAIL;
    }

    /* Reset widget attached data */
    c_memset(pt_ui_data, 0, sizeof(CNT_INDCTR_UI_DATA_T));

    /* style mask */
    pt_ui_data->ui4_style_mask = pt_init_data->ui4_style_mask;

    /* keep widgets infomation */
    for(ui2_idx = ui2_indctr_mask; (ui2_idx & 0x1) == 0x0; ui2_idx >>= 1)
    {
        /* Index of first present indicator widget */
        pt_ui_data->ui2_first_indctr++;
    }

    /* which widget is create */
    pt_ui_data->ui2_indctr_mask = ui2_indctr_mask;

    /* inset */
    pt_ui_data->i2_inset_up     = pt_init_data->i2_inset_up;
    pt_ui_data->i2_inset_down   = pt_init_data->i2_inset_down;
    pt_ui_data->i2_inset_left   = pt_init_data->i2_inset_left;
    pt_ui_data->i2_inset_right  = pt_init_data->i2_inset_right;
    /* rectangle */
    pt_ui_data->t_rect = pt_init_data->t_rect;

    for (ui2_idx = pt_ui_data->ui2_first_indctr; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        /* rectangle of each indicator widget */
        switch (ui2_idx)
        {
            case CNT_INDCTR_IDX_UP:
                SET_RECT_BY_SIZE(&t_rect,
                                 (pt_init_data->t_rect.i4_left + pt_init_data->t_rect.i4_right - CNT_INDCTR_UD_ICON_WIDTH)/2,
                                 (pt_init_data->t_rect.i4_top - pt_init_data->i2_inset_up - CNT_INDCTR_UD_ICON_HEIGHT),
                                 CNT_INDCTR_UD_ICON_WIDTH,
                                 CNT_INDCTR_UD_ICON_HEIGHT);
                break;

            case CNT_INDCTR_IDX_DOWN:
                SET_RECT_BY_SIZE(&t_rect,
                                 (pt_init_data->t_rect.i4_left + pt_init_data->t_rect.i4_right - CNT_INDCTR_UD_ICON_WIDTH)/2,
                                 (pt_init_data->t_rect.i4_bottom + pt_init_data->i2_inset_down),
                                 CNT_INDCTR_UD_ICON_WIDTH,
                                 CNT_INDCTR_UD_ICON_HEIGHT);
                break;

            case CNT_INDCTR_IDX_LEFT:
                SET_RECT_BY_SIZE(&t_rect,
                                 (pt_init_data->t_rect.i4_left - pt_init_data->i2_inset_left - CNT_INDCTR_LR_ICON_WIDTH),
                                 (pt_init_data->t_rect.i4_top + pt_init_data->t_rect.i4_bottom - CNT_INDCTR_LR_ICON_HEIGHT)/2,
                                 CNT_INDCTR_LR_ICON_WIDTH,
                                 CNT_INDCTR_LR_ICON_HEIGHT);
                break;

            case CNT_INDCTR_IDX_RIGHT:
                SET_RECT_BY_SIZE(&t_rect,
                                 (pt_init_data->t_rect.i4_right + pt_init_data->i2_inset_right),
                                 (pt_init_data->t_rect.i4_top + pt_init_data->t_rect.i4_bottom - CNT_INDCTR_LR_ICON_HEIGHT)/2,
                                 CNT_INDCTR_LR_ICON_WIDTH,
                                 CNT_INDCTR_LR_ICON_HEIGHT);
                break;

            default:
                INDCTR_CHK_FAIL(-1);
        }

        /* Create indicator widgets */
        if (0 != (ui2_indctr_mask & MAKE_BIT_MASK_16(ui2_idx)))    /* check if widget required */
        {
            /* create indicator widget */
            i4_ret = c_wgl_create_widget(pt_init_data->h_parent,
                                         HT_WGL_WIDGET_ICON,
                                         WGL_CONTENT_ICON_DEF,
                                         WGL_BORDER_NULL,
                                         &t_rect,
                                         NULL,
                                         255,
                                         NULL,
                                         NULL,
                                         &(pt_ui_data->h_indctr[ui2_idx]));
            if(i4_ret < 0)
            {
                c_mem_free(pt_ui_data);
                return WDKR_FAIL;
            }

            i4_ret = a_wdk_image_init();
            if(i4_ret < 0)
            {
                c_mem_free(pt_ui_data);
                return WDKR_FAIL;
            }

            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = h_g_wdk_cnt_indctr_img[ui2_idx];
            t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_cnt_indctr_img[ui2_idx];
            t_img_info.u_img_data.t_standard.t_disable   = h_g_wdk_cnt_indctr_img[ui2_idx];

            i4_ret = c_wgl_do_cmd(pt_ui_data->h_indctr[ui2_idx],
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK(WGL_IMG_BK),
                                  WGL_PACK(&t_img_info)
                                  );
            if(i4_ret < 0)
            {
                c_mem_free(pt_ui_data);
                return WDKR_FAIL;
            }

            if ( (pt_ui_data->ui4_style_mask & CNT_INDCTR_STYLE_MASK_NO_TOPMOST) == 0)
            {
                i4_ret = c_wgl_insert (pt_ui_data->h_indctr[ui2_idx],
                                       NULL_HANDLE,
                                       WGL_INSERT_TOPMOST,
                                       WGL_NO_AUTO_REPAINT);
                if(i4_ret < 0)
                {
                    c_mem_free(pt_ui_data);
                    return WDKR_FAIL;
                }
            }
        }
        else
        {
            pt_ui_data->h_indctr[ui2_idx] = NULL_HANDLE;
        }
    }

    /* the handle the first present indicator widget is the handle of cnt_indicator applicaiton widget */
    if(pt_ui_data->ui2_first_indctr >= 4)
    {
        c_mem_free(pt_ui_data);
        return WDKR_FAIL;
    }
    *ph_indicator = pt_ui_data->h_indctr[pt_ui_data->ui2_first_indctr];

    /* attach infomation data */
    i4_ret = c_wgl_do_cmd(*ph_indicator,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_destroy
 * Description
 *      Application widget waiting indicator destroy fct.
 * Input arguments
 *      h_indicator -
 * Output arguments
 *      None
 * Returns
 *      WDKR_OK
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_destroy (
                    HANDLE_T                    h_indicator)        /* IN  */
{
    UINT16                  ui2_idx;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    /* Destory widgets */
    for (ui2_idx = 0; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        if (NULL_HANDLE != pt_ui_data->h_indctr[ui2_idx])
        {
            INDCTR_CHK_FAIL(c_wgl_destroy_widget_ex(pt_ui_data->h_indctr[ui2_idx], FALSE));
        }
    }

    /* free memory */
    c_mem_free(pt_ui_data);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_set_position
 * Description
 *      Application widget waiting indicator position reset fct.
 * Input arguments
 *      h_indicator -
 *      pt_rect -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_set_position (
                    HANDLE_T                    h_indicator,        /* IN */
                    INT16                       i2_inset_up,        /* IN */
                    INT16                       i2_inset_down,      /* IN */
                    INT16                       i2_inset_left,      /* IN */
                    INT16                       i2_inset_right,     /* IN */
                    GL_RECT_T*                  pt_rect)            /* IN */
{
    GL_RECT_T               t_rect;
    UINT16                  ui2_idx;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;
    UINT16                  ui2_indctr_mask;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    ui2_indctr_mask = pt_ui_data->ui2_indctr_mask;

    for (ui2_idx = pt_ui_data->ui2_first_indctr; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        if (0 != (ui2_indctr_mask & MAKE_BIT_MASK_16(ui2_idx)))
        {
            switch (ui2_idx)
            {
                case CNT_INDCTR_IDX_UP:
                    SET_RECT_BY_SIZE(&t_rect,
                                     (pt_rect->i4_left + pt_rect->i4_right - CNT_INDCTR_UD_ICON_WIDTH)/2,
                                     (pt_rect->i4_top - i2_inset_up - CNT_INDCTR_UD_ICON_HEIGHT),
                                     CNT_INDCTR_UD_ICON_WIDTH,
                                     CNT_INDCTR_UD_ICON_HEIGHT);
                    break;

                case CNT_INDCTR_IDX_DOWN:
                    SET_RECT_BY_SIZE(&t_rect,
                                     (pt_rect->i4_left + pt_rect->i4_right - CNT_INDCTR_UD_ICON_WIDTH)/2,
                                     (pt_rect->i4_bottom + i2_inset_down),
                                     CNT_INDCTR_UD_ICON_WIDTH,
                                     CNT_INDCTR_UD_ICON_HEIGHT);
                    break;

                case CNT_INDCTR_IDX_LEFT:
                    SET_RECT_BY_SIZE(&t_rect,
                                     (pt_rect->i4_left - i2_inset_left - CNT_INDCTR_LR_ICON_WIDTH),
                                     (pt_rect->i4_top + pt_rect->i4_bottom - CNT_INDCTR_LR_ICON_HEIGHT)/2,
                                     CNT_INDCTR_LR_ICON_WIDTH,
                                     CNT_INDCTR_LR_ICON_HEIGHT);
                    break;

                case CNT_INDCTR_IDX_RIGHT:
                    SET_RECT_BY_SIZE(&t_rect,
                                     (pt_rect->i4_right + i2_inset_right),
                                     (pt_rect->i4_top + pt_rect->i4_bottom - CNT_INDCTR_LR_ICON_HEIGHT)/2,
                                     CNT_INDCTR_LR_ICON_WIDTH,
                                     CNT_INDCTR_LR_ICON_HEIGHT);
                    break;

                default:
                    INDCTR_CHK_FAIL(-1);
            }

            if ( (pt_ui_data->ui4_style_mask & CNT_INDCTR_STYLE_MASK_NO_TOPMOST) == 0)
            {
                i4_ret = c_wgl_insert (pt_ui_data->h_indctr[ui2_idx],
                                       NULL_HANDLE,
                                       WGL_INSERT_TOPMOST,
                                       WGL_NO_AUTO_REPAINT);
                INDCTR_CHK_FAIL (i4_ret);
            }

            INDCTR_CHK_FAIL (c_wgl_move (pt_ui_data->h_indctr[ui2_idx], &t_rect, WGL_SYNC_AUTO_REPAINT));

        }
    }
    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_set_position
 * Description
 *      Application widget waiting indicator position reset fct.
 * Input arguments
 *      h_indicator -
 *      pt_rect -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_set_rect (
                    HANDLE_T                    h_indicator,        /* IN */
                    GL_RECT_T*                  pt_rect)            /* IN */
{
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    i4_ret = a_cnt_indctr_set_position (h_indicator,
                                        pt_ui_data->i2_inset_up,
                                        pt_ui_data->i2_inset_down,
                                        pt_ui_data->i2_inset_left,
                                        pt_ui_data->i2_inset_right,
                                        pt_rect);
    INDCTR_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_set_inset
 * Description
 *      Application widget waiting indicator inset reset fct.
 * Input arguments
 *      h_indicator -
 *      i2_ud_inset -
 *      i2_lr_inset -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_set_inset (
                    HANDLE_T                    h_indicator,        /* IN */
                    INT16                       i2_inset_up,        /* IN */
                    INT16                       i2_inset_down,      /* IN */
                    INT16                       i2_inset_left,      /* IN */
                    INT16                       i2_inset_right)     /* IN */
{
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    i4_ret = a_cnt_indctr_set_position(h_indicator,
                                       i2_inset_up,
                                       i2_inset_down,
                                       i2_inset_left,
                                       i2_inset_right,
                                       &pt_ui_data->t_rect);
    INDCTR_CHK_FAIL (i4_ret);

    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ci_info_status_timer_nfy_fct
 * Description
 *      Application widget waiting indicator visibility set fct.
 * Input arguments
 *      h_indicator -
 *      ui4_indctr_mask -
 *      b_show -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_set_visibilty(
                    HANDLE_T                    h_indicator,        /* IN */
                    UINT32                      ui4_indctr_mask,    /* IN */
                    BOOL                        b_show)             /* IN */
{
    UINT16                  ui2_idx;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;
    UINT16                  ui2_indctr_mask;
    WGL_SW_CMD_T            e_wgl_sw_cmd;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    ui2_indctr_mask = ((UINT16)(ui4_indctr_mask&0xf) & pt_ui_data->ui2_indctr_mask);

    if (TRUE == b_show)
    {
        e_wgl_sw_cmd = WGL_SW_NORMAL;
    }
    else
    {
        e_wgl_sw_cmd = WGL_SW_HIDE;
    }

    for (ui2_idx = pt_ui_data->ui2_first_indctr; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        if (0 != (ui2_indctr_mask & MAKE_BIT_MASK_16(ui2_idx)))
        {
            INDCTR_CHK_FAIL (c_wgl_set_visibility (pt_ui_data->h_indctr[ui2_idx], e_wgl_sw_cmd));
        }
    }
    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_reset_visibilty
 * Description
 *      Application widget waiting indicator visibility reset fct.
 * Input arguments
 *      h_indicator -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_reset_visibilty (
                    HANDLE_T                    h_indicator)        /* IN */
{
    UINT16                  ui2_idx;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    for (ui2_idx = pt_ui_data->ui2_first_indctr; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        if (NULL_HANDLE != pt_ui_data->h_indctr[ui2_idx])
        {
            INDCTR_CHK_FAIL (c_wgl_set_visibility (pt_ui_data->h_indctr[ui2_idx], WGL_SW_HIDE));
        }
    }
    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_repaint
 * Description
 *      Application widget waiting indicator repaint fct.
 * Input arguments
 *      h_indicator -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_repaint (
                    HANDLE_T                    h_indicator)        /* IN */
{
    UINT16                  ui2_idx;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    for (ui2_idx = pt_ui_data->ui2_first_indctr; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        if (NULL_HANDLE != pt_ui_data->h_indctr[ui2_idx])
        {
            if ( (pt_ui_data->ui4_style_mask & CNT_INDCTR_STYLE_MASK_NO_TOPMOST) == 0)
            {
                i4_ret = c_wgl_insert (pt_ui_data->h_indctr[ui2_idx],
                                       NULL_HANDLE,
                                       WGL_INSERT_TOPMOST,
                                       WGL_SYNC_AUTO_REPAINT);
                INDCTR_CHK_FAIL (i4_ret);
            }
            else
            {
                i4_ret = c_wgl_repaint (pt_ui_data->h_indctr[ui2_idx],
                                        NULL,
                                        TRUE);
            }
        }
    }
    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_show
 * Description
 *      Application widget waiting indicator show fct.
 * Input arguments
 *      h_indicator -
 *      ui4_indctr_mask -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_show (
                    HANDLE_T                    h_indicator,        /* IN */
                    UINT32                      ui4_indctr_mask)    /* IN */
{
    UINT16                  ui2_idx;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;
    UINT16                  ui2_indctr_mask;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    ui2_indctr_mask = ((UINT16)(ui4_indctr_mask&0xf) & pt_ui_data->ui2_indctr_mask);

    for (ui2_idx = pt_ui_data->ui2_first_indctr; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        if (0 != (ui2_indctr_mask & MAKE_BIT_MASK_16(ui2_idx)))
        {
            INDCTR_CHK_FAIL (c_wgl_set_visibility (pt_ui_data->h_indctr[ui2_idx], WGL_SW_NORMAL));

            if ( (pt_ui_data->ui4_style_mask & CNT_INDCTR_STYLE_MASK_NO_TOPMOST) == 0)
            {
                i4_ret = c_wgl_insert (pt_ui_data->h_indctr[ui2_idx],
                                       NULL_HANDLE,
                                       WGL_INSERT_TOPMOST,
                                       WGL_SYNC_AUTO_REPAINT);
                INDCTR_CHK_FAIL (i4_ret);


                i4_ret = c_wgl_repaint (pt_ui_data->h_indctr[ui2_idx],
                                        NULL,
                                        TRUE);
                INDCTR_CHK_FAIL (i4_ret);
            }
            else
            {
                i4_ret = c_wgl_repaint (pt_ui_data->h_indctr[ui2_idx],
                                        NULL,
                                        TRUE);
                INDCTR_CHK_FAIL (i4_ret);
            }
        }
    }
    return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_cnt_indctr_hide
 * Description
 *      Application widget waiting indicator hide fct.
 * Input arguments
 *      h_indicator -
 *      ui4_indctr_mask -
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 a_cnt_indctr_hide (
                    HANDLE_T                    h_indicator,        /* IN */
                    UINT32                      ui4_indctr_mask)    /* IN */
{
    UINT16                  ui2_idx;
    CNT_INDCTR_UI_DATA_T*   pt_ui_data;
    INT32                   i4_ret;
    UINT16                  ui2_indctr_mask;

    i4_ret = c_wgl_do_cmd(h_indicator,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&pt_ui_data),
                          NULL);
    INDCTR_CHK_FAIL (i4_ret);

    ui2_indctr_mask = ((UINT16)(ui4_indctr_mask&0xf) & pt_ui_data->ui2_indctr_mask);

    for (ui2_idx = pt_ui_data->ui2_first_indctr; ui2_idx < CNT_INDCTR_NUM; ui2_idx++)
    {
        if (0 != (ui2_indctr_mask & MAKE_BIT_MASK_16(ui2_idx)))
        {
            INDCTR_CHK_FAIL (c_wgl_set_visibility (pt_ui_data->h_indctr[ui2_idx], WGL_SW_HIDE));

            INDCTR_CHK_FAIL (c_wgl_repaint (pt_ui_data->h_indctr[ui2_idx], NULL, TRUE));
        }
    }
    return WDKR_OK;
}



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
 * $RCSfile: nav_cec_view_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
 
#ifndef _NAV_CEC_VIEW_RC_H_
#define _NAV_CEC_VIEW_RC_H_

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_cecm.h"

#include "res/nav/nav_view.h"
#include "res/nav/nav_img_rc.h"
#include "nav/cec2/nav_cec.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#define APP_NAV_CEC_NO_ELEM_CLR
/* View configurations. */
typedef struct _NAV_CEC_VIEW_RC_STATUS_TXT_T
{
    WGL_HIMG_TPL_T      h_status_txt_bk_img;
    GL_COLOR_T          t_txt_fg_clr;
} NAV_CEC_VIEW_RC_STATUS_TXT_T;

typedef struct _NAV_CEC_VIEW_RC_T
{
    WGL_HIMG_TPL_T      h_dev_lst_bk_img;
    WGL_HIMG_TPL_T      h_dev_lst_elem_hlt_bk_img;
    WGL_HIMG_TPL_T      h_dev_lst_lb_act_src_img;
    WGL_HIMG_TPL_T      h_cmd_lst_bk_img;
    WGL_HIMG_TPL_T      h_cmd_lst_elem_hlt_bk_img;

    GL_COLOR_T          t_elm_normal_fg_clr;
    GL_COLOR_T          t_elm_hlt_fg_clr;
    GL_COLOR_T          t_elm_dis_fg_clr;
    GL_COLOR_T          t_elm_bk_clr;
    GL_COLOR_T          t_lb_bk_clr;
    GL_COLOR_T          t_title_fg_clr;

    NAV_CEC_VIEW_RC_STATUS_TXT_T t_rc_status_txt;
} NAV_CEC_VIEW_RC_T;

typedef struct _NAV_CEC_DECK_CTRL_RC_T
{
    WGL_HIMG_TPL_T		h_ctrl_pnl_frm_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_eject_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_play_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_stop_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_pause_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_fast_forward_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_fast_reverse_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_skip_forward_img;
	WGL_HIMG_TPL_T		h_ctrl_pnl_skip_reverse_img;
	GL_COLOR_T          t_ctrl_pnl_icon_border_clr;
} NAV_CEC_DECK_CTRL_RC_T;

/* CEC frame related configurations. */
#define CEC_FRAME_X                     (0)
#define CEC_FRAME_Y                     (300)
#define CEC_FRAME_W                     (DEV_LST_LB_W + CMD_LST_LB_W)
#define CEC_FRAME_H                     (DEV_LST_LB_H)
#define CEC_FRAME_HIDE_DUR              (10000)

/* Device list. */
#define DEV_LST_MAX_ELEM_NUM            (16)
#define DEV_LST_ELEM_H                  (34)
#define DEV_LST_ELEM_DTANCE             (2)
#define DEV_LST_VISIBLE_ELEM_NUM        (5)

#define DEV_LST_TITLE_X                 (50)
#define DEV_LST_TITLE_Y                 (5)
#define DEV_LST_TITLE_W                 (250)
#define DEV_LST_TITLE_H                 (40)
#define DEV_LST_TITLE_ALIGN             (WGL_AS_LEFT_CENTER)
#define DEV_LST_TITLE_FONT_NAME         NAV_FONT_NORMAL
#define DEV_LST_TITLE_FONT_SIZE         FE_FNT_SIZE_SMALL;
#define DEV_LST_TITLE_FONT_STYLE        FE_FNT_STYLE_REGULAR;
#define DEV_LST_TITLE_FONT_CMAP         FE_CMAP_ENC_UNICODE;

#define DEV_LST_LB_X                    (0)
#define DEV_LST_LB_Y                    (0)
#define DEV_LST_LB_W                    (DEV_LST_TITLE_W)
#define DEV_LST_LB_H                    (DEV_LST_LB_CNT_INSET_T + (DEV_LST_ELEM_H + DEV_LST_ELEM_DTANCE) * DEV_LST_VISIBLE_ELEM_NUM + DEV_LST_LB_CNT_INSET_B)
#define DEV_LST_LB_CNT_INSET_L          (8)
#define DEV_LST_LB_CNT_INSET_R          (4)
#define DEV_LST_LB_CNT_INSET_T          (DEV_LST_TITLE_H + 4)
#define DEV_LST_LB_CNT_INSET_B          (4)
#define DEV_LST_LB_COL0_ALIGNMENT       (WGL_AS_LEFT_CENTER)
#define DEV_LST_LB_COL0_MAX_TEXT_LEN    (30)
#define DEV_LST_LB_COL0_W               (DEV_LST_LB_W - DEV_LST_LB_COL1_W)
#define DEV_LST_LB_COL1_ALIGNMENT       (WGL_AS_LEFT_CENTER)
#define DEV_LST_LB_COL1_W               (50)

#define DEV_LST_LB_HLT_EFFECT_STYLE         (WGL_LB_HEF_STL_ENLARGE_SIZE | WGL_LB_HEF_STL_PUT_ABOVE_VP)
#define DEV_LST_LB_HLT_EFFECT_EX_MARGIN_L   (0)
#define DEV_LST_LB_HLT_EFFECT_EX_MARGIN_R   (0)
#define DEV_LST_LB_HLT_EFFECT_EX_MARGIN_T   (2)
#define DEV_LST_LB_HLT_EFFECT_EX_MARGIN_B   (10)

#define DEV_LST_LB_COL0_INSET_L         (DEV_LST_LB_CNT_INSET_L)
#define DEV_LST_LB_COL0_INSET_R         (0)
#define DEV_LST_LB_COL0_INSET_T         (0)
#define DEV_LST_LB_COL0_INSET_B         (0)

#define DEV_LST_LB_COL1_INSET_L         (0)
#define DEV_LST_LB_COL1_INSET_R         (0)
#define DEV_LST_LB_COL1_INSET_T         (0)
#define DEV_LST_LB_COL1_INSET_B         (0)

#define DEV_LST_SCRL_BAR_W              (6)
#define DEV_LST_SCRL_BAR_X              (DEV_LST_LB_W - DEV_LST_SCRL_BAR_W)
#define DEV_LST_SCRL_BAR_Y              (DEV_LST_TITLE_H)
#define DEV_LST_SCRL_BAR_H              (DEV_LST_ELEM_H  * DEV_LST_VISIBLE_ELEM_NUM - 2)
#define DEV_LST_SCRL_BAR_THUMB_MIN      ((DEV_LST_ELEM_H * DEV_LST_VISIBLE_ELEM_NUM) / 8)

#define DEV_LST_FONT_NAME               NAV_FONT_NORMAL
#define DEV_LST_FONT_SIZE               FE_FNT_SIZE_SMALL;
#define DEV_LST_FONT_STYLE              FE_FNT_STYLE_REGULAR;
#define DEV_LST_FONT_CMAP               FE_CMAP_ENC_UNICODE;
/* Command list. */
#define CMD_LST_MAX_ELEM_NUM            (5)
#define CMD_LST_ELEM_H                  (34)
#define CMD_LST_ELEM_DTANCE             (2)

#define CMD_LST_LB_X                    (DEV_LST_LB_X + DEV_LST_LB_W)
#define CMD_LST_LB_Y                    (0 + DEV_LST_TITLE_H)
#define CMD_LST_LB_W                    (300)
#define CMD_LST_LB_H                    (CMD_LST_LB_CNT_INSET_T + (CMD_LST_ELEM_H + CMD_LST_ELEM_DTANCE) * CMD_LST_MAX_ELEM_NUM + CMD_LST_LB_CNT_INSET_B)
#define CMD_LST_LB_CNT_INSET_L          (4)
#define CMD_LST_LB_CNT_INSET_R          (4)
#define CMD_LST_LB_CNT_INSET_T          (4)
#define CMD_LST_LB_CNT_INSET_B          (4)
#define CMD_LST_LB_COL0_ALIGNMENT       (WGL_AS_LEFT_CENTER)
#define CMD_LST_LB_COL0_MAX_TEXT_LEN    (40)
#define CMD_LST_LB_COL0_W               (CMD_LST_LB_W)
#define CMD_LST_LB_COL0_INSET_L         (30)
#define CMD_LST_LB_COL0_INSET_R         (0)
#define CMD_LST_LB_COL0_INSET_T         (0)
#define CMD_LST_LB_COL0_INSET_B         (0)

#define CMD_LST_LB_HLT_EFFECT_STYLE         (WGL_LB_HEF_STL_ENLARGE_SIZE | WGL_LB_HEF_STL_PUT_ABOVE_VP)
#define CMD_LST_LB_HLT_EFFECT_EX_MARGIN_L   (0)
#define CMD_LST_LB_HLT_EFFECT_EX_MARGIN_R   (0)
#define CMD_LST_LB_HLT_EFFECT_EX_MARGIN_T   (2)
#define CMD_LST_LB_HLT_EFFECT_EX_MARGIN_B   (10)

#define CMD_LST_FONT_NAME               NAV_FONT_NORMAL
#define CMD_LST_FONT_SIZE               FE_FNT_SIZE_SMALL;
#define CMD_LST_FONT_STYLE              FE_FNT_STYLE_REGULAR;
#define CMD_LST_FONT_CMAP               FE_CMAP_ENC_UNICODE;

/* Status text. */
/* The following settings should be thre same as text frame of NAV_IB. */
#define STATUS_TXT_X                    (DISPLAY_WIDTH - (SAFE_DISPLAY_LEFT/2) - STATUS_TXT_W)
#define STATUS_TXT_Y                    (SAFE_DISPLAY_TOP  + SAFE_DISPLAY_HEIGHT - STATUS_TXT_H)
#define STATUS_TXT_W                    (320)
#define STATUS_TXT_H                    (80)

#define STATUS_TXT_FONT_NAME            NAV_FONT_NORMAL
#define STATUS_TXT_FONT_SIZE            FE_FNT_SIZE_SMALL;
#define STATUS_TXT_FONT_STYLE           FE_FNT_STYLE_REGULAR;
#define STATUS_TXT_FONT_CMAP            FE_CMAP_ENC_UNICODE;

#define STATUS_TXT_INSET_L              (0)
#define STATUS_TXT_INSET_R              (0)
#define STATUS_TXT_INSET_T              (0)
#define STATUS_TXT_INSET_B              (0)
#define STATUS_TXT_HIDE_DUR             (3000)
#define STATUS_TXT_HIDE_DEF             (5000)  /**< For OSD Display define time. */
/* Ctrl panel frame related configurations. */
#define CTRL_PNL_ICON_W                 (50)
#define CTRL_PNL_ICON_H                 (50)
#define CTRL_PNL_ICON_X                 ((CTRL_PNL_FRM_W-CTRL_PNL_ICON_W*CTRL_PNL_ICONS_PER_ROW)/2)
#define CTRL_PNL_ICON_Y                 ((CTRL_PNL_FRM_H-CTRL_PNL_ICON_H*CTRL_PNL_ICONS_PER_COLUMN)/2)

#define CTRL_PNL_ICON_BORDER_INSL_T     (5)
#define CTRL_PNL_ICON_BORDER_INSL_B     (5)
#define CTRL_PNL_ICON_BORDER_INSL_L     (5)
#define CTRL_PNL_ICON_BORDER_INSL_R     (5)

#define CTRL_PNL_ICONS_PER_ROW          (4)  
#define CTRL_PNL_ICONS_PER_COLUMN       (2)  

#define CTRL_PNL_FRM_W                  (240)
#define CTRL_PNL_FRM_H                  (136)
#define CTRL_PNL_FRM_X                  (CEC_FRAME_X + CEC_FRAME_W)
#define CTRL_PNL_FRM_Y                  (CEC_FRAME_Y + CEC_FRAME_H)
#define CTRL_PNL_HIDE_DUR               (10000)

#if 0
/* Ctrl panel frame related configurations. */
#define CTRL_PNL_ICON_W                 (40)
#define CTRL_PNL_ICON_H                 (40)
#define CTRL_PNL_ICON_CIRCLE_W          (200)
#define CTRL_PNL_ICON_CIRCLE_H          (200)
#define CTRL_PNL_X                      (CMD_LST_LB_X + CMD_LST_LB_W)
#define CTRL_PNL_Y                      (CMD_LST_LB_Y + CMD_LST_LB_H)
#define CTRL_PNL_W                      ((CTRL_PNL_ICON_W*3) + (CTRL_PNL_ICON_W*2))
#define CTRL_PNL_H                      ((CTRL_PNL_ICON_H*3) + (CTRL_PNL_ICON_H*2))
#endif

#define BTN_CEC BTN_CUSTOM_150
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
INT32 nav_cec_view_init_rc (
    NAV_CEC_VIEW_RC_T* pt_rc
    );
INT32 nav_cec_view_deinit_rc (
    NAV_CEC_VIEW_RC_T* pt_rc
    );
INT32 nav_cec_view_init_rc_status_txt (
    NAV_CEC_VIEW_RC_STATUS_TXT_T* pt_rc_status_txt
    );
INT32 nav_cec_view_deinit_rc_status_txt (
    NAV_CEC_VIEW_RC_STATUS_TXT_T* pt_rc_status_txt
    );
INT32 nav_cec_view_rc_get_cmd_by_type (
    NAV_CEC_DEV_TYPE_T e_dev_type,
    UINT8* pui1_cmd_num,
    NAV_CEC_CMD_T** ppt_cec_cmd
    );
INT32 nav_cec_deck_ctrl_init_rc (
    NAV_CEC_DECK_CTRL_RC_T* pt_deck_ctrl_rc
    );
INT32 nav_cec_deck_ctrl_deinit_rc (
    NAV_CEC_DECK_CTRL_RC_T* pt_deck_ctrl_rc
    );

#endif /* APP_NAV_CEC_SUPPORT */
#endif /* APP_NAV_CEC_SUPPORT */
#endif /* _NAV_CEC_VIEW_RC_H_ */


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
 * $RCSfile: vkb_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _VKB_RC_H
#define _VKB_RC_H
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    behavior
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    dimension
-----------------------------------------------------------------------------*/

/*
    UI Related
*/
#define VKB_WIDTH(__w)							(__w*4/3) /* for 1280 width  */
#define VKB_HEIGHT(__h)							(__h*4/3) /* for 720 height */

#define VKB_NORMAL_TXT_CENTER_W                 (69)
#define VKB_NORMAL_TXT_CENTER_H                 (59)
#define VKB_NORMAL_TXT_CENTER_OFFSET_X          (13)
#define VKB_NORMAL_TXT_CENTER_OFFSET_Y          (14)
#define VKB_BIG_TXT_CENTER_W                    (103)
#define VKB_BIG_TXT_CENTER_H                    (59)
#define VKB_SPACE_TXT_CENTER_W                  (205)
#define VKB_SPACE_TXT_CENTER_H                  (59)

/*
    Main frame
*/
#define VKB_MAIN_FRAME_ALPHA                      (255)
#define VKB_MAIN_FRAME_W                          VKB_WIDTH(398) //393
#define VKB_MAIN_FRAME_H                          VKB_HEIGHT(400)

/*
    Main frame phase2
*/
#define VKB_MAIN_FRAME_ALPHA_PHA2                 (255)
#define VKB_MAIN_FRAME_W_PHA2                     (770)
#define VKB_MAIN_FRAME_H_PHA2                     VKB_HEIGHT(440)

/*
    Label text (parent: main frame)
*/
#define VKB_LABEL_TEXT_ALPHA                      (255)
#define VKB_LABEL_TEXT_X                          VKB_WIDTH(10)
#define VKB_LABEL_TEXT_Y                          VKB_HEIGHT(7)
#define VKB_LABEL_TEXT_W                          VKB_WIDTH(80)
#define VKB_LABEL_TEXT_H                          VKB_HEIGHT(33)
#define VKB_LABEL_TEXT_ALIGNMENT                  WGL_AS_LEFT_CENTER

#define VKB_LABEL_TEXT_FONT_NAME                  VKB_BTN_FONT_NAME
#define VKB_LABEL_TEXT_FONT_SIZE                  FE_FNT_SIZE_SMALL
#define VKB_LABEL_TEXT_FONT_STYLE                 FE_FNT_STYLE_REGULAR

/*
    Label text phase2 (parent: main frame)
*/
#define VKB_LABEL_TEXT_ALPHA_PHA2                      (255)
#define VKB_LABEL_TEXT_X_PHA2                          VKB_WIDTH(10)
#define VKB_LABEL_TEXT_Y_PHA2                          VKB_HEIGHT(7)
#define VKB_LABEL_TEXT_W_PHA2                          VKB_WIDTH(80)
#define VKB_LABEL_TEXT_H_PHA2                          VKB_HEIGHT(33)
#define VKB_LABEL_TEXT_ALIGNMENT_PHA2                  WGL_AS_LEFT_CENTER

#define VKB_LABEL_TEXT_FONT_NAME_PHA2                  VKB_BTN_FONT_NAME
#define VKB_LABEL_TEXT_FONT_SIZE_PHA2                  FE_FNT_SIZE_SMALL
#define VKB_LABEL_TEXT_FONT_STYLE_PHA2                 FE_FNT_STYLE_REGULAR

/*
    Edit box (parent: main frame)
*/
#define VKB_EDIT_BOX_ALPHA                        (255)
#define VKB_EDIT_BOX_X                            (VKB_LABEL_TEXT_X + VKB_LABEL_TEXT_W)
#define VKB_EDIT_BOX_Y                            (VKB_LABEL_TEXT_Y)
#define VKB_EDIT_BOX_W                            (VKB_MAIN_FRAME_W - 2*VKB_LABEL_TEXT_X - VKB_LABEL_TEXT_W)
#define VKB_EDIT_BOX_H                            (VKB_LABEL_TEXT_H)
#define VKB_EDIT_BOX_STYLE                        (WGL_STL_EB_MAX_CHAR_256)
#define VKB_EDIT_BOX_ALIGNMENT                    WGL_AS_LEFT_CENTER

#define VKB_EDIT_BOX_BDR_INSET_L                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_BDR_INSET_R                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_BDR_INSET_T                  VKB_HEIGHT(0)
#define VKB_EDIT_BOX_BDR_INSET_B                  VKB_HEIGHT(0)
#define VKB_EDIT_BOX_CNT_INSET_L                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_CNT_INSET_R                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_CNT_INSET_T                  VKB_HEIGHT(0)
#define VKB_EDIT_BOX_CNT_INSET_B                  VKB_HEIGHT(0)

#define VKB_EDIT_BOX_FONT_NAME                    VKB_BTN_FONT_NAME
#define VKB_EDIT_BOX_FONT_SIZE                    FE_FNT_SIZE_SMALL
#define VKB_EDIT_BOX_FONT_STYLE                   FE_FNT_STYLE_REGULAR
#define VKB_EDIT_BOX_FONT_WIDTH                   VKB_HEIGHT(0)

/*
    Edit box phase2 (parent: main frame)
*/
#define VKB_EDIT_BOX_ALPHA_PHA2                        (255)
#define VKB_EDIT_BOX_X_PHA2                            (VKB_LABEL_TEXT_X + VKB_LABEL_TEXT_W)
#define VKB_EDIT_BOX_Y_PHA2                            (VKB_LABEL_TEXT_Y)
#define VKB_EDIT_BOX_W_PHA2                            (VKB_MAIN_FRAME_W - 2*VKB_LABEL_TEXT_X - VKB_LABEL_TEXT_W)
#define VKB_EDIT_BOX_H_PHA2                            (VKB_LABEL_TEXT_H)
#define VKB_EDIT_BOX_STYLE_PHA2                        (WGL_STL_EB_MAX_CHAR_256)
#define VKB_EDIT_BOX_ALIGNMENT_PHA2                    WGL_AS_LEFT_CENTER

#define VKB_EDIT_BOX_BDR_INSET_L_PHA2                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_BDR_INSET_R_PHA2                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_BDR_INSET_T_PHA2                  VKB_HEIGHT(0)
#define VKB_EDIT_BOX_BDR_INSET_B_PHA2                  VKB_HEIGHT(0)
#define VKB_EDIT_BOX_CNT_INSET_L_PHA2                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_CNT_INSET_R_PHA2                  VKB_WIDTH(0)
#define VKB_EDIT_BOX_CNT_INSET_T_PHA2                  VKB_HEIGHT(0)
#define VKB_EDIT_BOX_CNT_INSET_B_PHA2                  VKB_HEIGHT(0)

#define VKB_EDIT_BOX_FONT_NAME_PHA2                    VKB_BTN_FONT_NAME
#define VKB_EDIT_BOX_FONT_SIZE_PHA2                    FE_FNT_SIZE_SMALL
#define VKB_EDIT_BOX_FONT_STYLE_PHA2                   FE_FNT_STYLE_REGULAR
#define VKB_EDIT_BOX_FONT_WIDTH_PHA2                   VKB_HEIGHT(0)

/*
    Keypad key text (parent: main frame)
*/

/* Normal key (parent: main frame) */
#define VKB_KEYPAD_NORMAL_KEY_TEXT_W              (39) //37
#define VKB_KEYPAD_NORMAL_KEY_TEXT_H              (39)

/* Normal key phase2 (parent: main frame) */
#define VKB_KEYPAD_NORMAL_KEY_TEXT_W_PHA2              (95)
#define VKB_KEYPAD_NORMAL_KEY_TEXT_H_PHA2              (85)

/* Big key (parent: main frame) */
#define VKB_KEYPAD_BIG_KEY_TEXT_W                 (57)
#define VKB_KEYPAD_BIG_KEY_TEXT_H                 (VKB_KEYPAD_NORMAL_KEY_TEXT_H)

/* Big key phase2 (parent: main frame) */
#define VKB_KEYPAD_BIG_KEY_TEXT_W_PHA2            (129)
#define VKB_KEYPAD_BIG_KEY_TEXT_H_PHA2            (VKB_KEYPAD_NORMAL_KEY_TEXT_H_PHA2)

/* Space key (parent: main frame) */
#define VKB_KEYPAD_SPACE_KEY_TEXT_W               (138)
#define VKB_KEYPAD_SPACE_KEY_TEXT_H               (VKB_KEYPAD_NORMAL_KEY_TEXT_H)

/* Space key phase2 (parent: main frame) */
#define VKB_KEYPAD_SPACE_KEY_TEXT_W_PHA2          (231)
#define VKB_KEYPAD_SPACE_KEY_TEXT_H_PHA2          (VKB_KEYPAD_NORMAL_KEY_TEXT_H_PHA2)

/* General Keypad layout */
#define VKB_KEYPAD_KEY_TEXT_ALPHA                 (255)
#define VKB_KEYPAD_KEY_TEXT_INTERVAL_X            3 //((VKB_MAIN_FRAME_W - 2 * VKB_KEYPAD_NORMAL_KEY_TEXT_X - VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM * VKB_KEYPAD_NORMAL_KEY_TEXT_W)/(VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM - 1))
#define VKB_KEYPAD_KEY_TEXT_INTERVAL_Y            (4)
#define VKB_KEYPAD_KEY_TEXT_ALIGNMENT             WGL_AS_CENTER_CENTER

/* General Keypad layout phase2 */
#define VKB_KEYPAD_KEY_TEXT_INTERVAL_X_PHA2       ((INT32)-1) 
#define VKB_KEYPAD_KEY_TEXT_INTERVAL_Y_PHA2       ((INT32)-1)

/* Normal key */
#define VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM        (4)
#define VKB_KEYPAD_NORMAL_KEY_TEXT_COL_NUM        (9)
#define VKB_KEYPAD_NORMAL_KEY_TEXT_X              (11) //12
#define VKB_KEYPAD_NORMAL_KEY_TEXT_Y              (53+66*4/3)

/* Normal key phase2 */
#define VKB_KEYPAD_NORMAL_KEY_TEXT_X_PHA2              (73+6) 
#define VKB_KEYPAD_NORMAL_KEY_TEXT_Y_PHA2              (48+5)

/* Latin key */
#define VKB_KEYPAD_LATIN_KEY_TEXT_NUM             (9)

/* Ctrl key */
#define VKB_KEYPAD_CTRL_KEY_TEXT_NUM              (5)
#define VKB_KEYPAD_CTRL_KEY_TEXT_X                (10)
#define VKB_KEYPAD_CTRL_KEY_TEXT_Y                (VKB_KEYPAD_NORMAL_KEY_TEXT_Y + VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM*(VKB_KEYPAD_NORMAL_KEY_TEXT_H + VKB_KEYPAD_KEY_TEXT_INTERVAL_Y) + 2)

/* Ctrl key phase2*/
#define VKB_KEYPAD_CTRL_KEY_TEXT_X_PHA2           (VKB_KEYPAD_NORMAL_KEY_TEXT_X_PHA2)
#define VKB_KEYPAD_CTRL_KEY_TEXT_Y_PHA2           (VKB_KEYPAD_NORMAL_KEY_TEXT_Y_PHA2    \
                                                    + VKB_KEYPAD_NORMAL_KEY_TEXT_ROW_NUM    \
                                                        *(VKB_NORMAL_TXT_CENTER_H + VKB_KEYPAD_KEY_TEXT_INTERVAL_Y_PHA2)    \
                                                    -VKB_NORMAL_TXT_CENTER_OFFSET_Y)

/* Ctrl key LOGO phase2*/
#define VKB_KEYPAD_CTRL_KEY_SYM_LOGO_W            (0)
#define VKB_KEYPAD_CTRL_KEY_SHF_LOGO_W            (VKB_KEYPAD_BIG_KEY_TEXT_W_PHA2/3)
#define VKB_KEYPAD_CTRL_KEY_LAT_LOGO_W            (0)
#define VKB_KEYPAD_CTRL_KEY_SPA_LOGO_W            (0)
#define VKB_KEYPAD_CTRL_KEY_DEL_LOGO_W            (VKB_KEYPAD_BIG_KEY_TEXT_W_PHA2/3)

#define VKB_KEYPAD_CTRL_KEY_SYM_LOGO_H            (0)
#define VKB_KEYPAD_CTRL_KEY_SHF_LOGO_H            (VKB_KEYPAD_NORMAL_KEY_TEXT_H_PHA2)
#define VKB_KEYPAD_CTRL_KEY_LAT_LOGO_H            (0)
#define VKB_KEYPAD_CTRL_KEY_SPA_LOGO_H            (0)
#define VKB_KEYPAD_CTRL_KEY_DEL_LOGO_H            (VKB_KEYPAD_NORMAL_KEY_TEXT_H_PHA2)

#define VKB_KEYPAD_KEY_TEXT_FONT_NAME             VKB_BTN_FONT_NAME
#define VKB_KEYPAD_KEY_TEXT_FONT_SIZE             FE_FNT_SIZE_SMALL
#define VKB_KEYPAD_KEY_TEXT_FONT_STYLE            FE_FNT_STYLE_REGULAR

/*
    Button OK is a text widget (parent: main frame)
*/
#define VKB_BTN_OK_TEXT_ALPHA                     (255)
#define VKB_BTN_OK_TEXT_X                         ((VKB_MAIN_FRAME_W - VKB_BTN_OK_TEXT_W)/2 + 1)
#define VKB_BTN_OK_TEXT_Y                         (218+110*4/3)
#define VKB_BTN_OK_TEXT_W                         VKB_WIDTH(509) //VKB_WIDTH(292)
#define VKB_BTN_OK_TEXT_H                         VKB_HEIGHT(22)
#define VKB_BTN_OK_TEXT_ALIGNMENT                 WGL_AS_LEFT_CENTER

/*
    Button OK is a text widget (parent: main frame) Phase2
*/
#define VKB_BTN_OK_TEXT_X_PHA2                     (VKB_KEYPAD_NORMAL_KEY_TEXT_X_PHA2)
#define VKB_BTN_OK_TEXT_Y_PHA2                     (VKB_KEYPAD_CTRL_KEY_TEXT_Y_PHA2+VKB_KEYPAD_BIG_KEY_TEXT_H_PHA2)
#define VKB_BTN_OK_TEXT_W_PHA2                     (276)
#define VKB_BTN_OK_TEXT_H_PHA2                     VKB_HEIGHT(22)

/*
    Button Cancel is a text widget (parent: main frame)
*/
#define VKB_BTN_CANCEL_TEXT_ALPHA                 (VKB_BTN_OK_TEXT_ALPHA)
#define VKB_BTN_CANCEL_TEXT_X                     (VKB_BTN_OK_TEXT_X)
#define VKB_BTN_CANCEL_TEXT_Y                     (VKB_BTN_OK_TEXT_Y + VKB_BTN_OK_TEXT_H + VKB_HEIGHT(3))
#define VKB_BTN_CANCEL_TEXT_W                     (VKB_BTN_OK_TEXT_W)
#define VKB_BTN_CANCEL_TEXT_H                     (VKB_BTN_OK_TEXT_H)
#define VKB_BTN_CANCEL_TEXT_ALIGNMENT             VKB_BTN_OK_TEXT_ALIGNMENT

/*
    Button Cancel is a text widget (parent: main frame) Phase2
*/
#define VKB_BTN_CANCEL_TEXT_X_PHA2                 (VKB_BTN_OK_TEXT_X_PHA2)
#define VKB_BTN_CANCEL_TEXT_Y_PHA2                 (VKB_BTN_OK_TEXT_Y_PHA2+VKB_BTN_OK_TEXT_H_PHA2+10)
#define VKB_BTN_CANCEL_TEXT_W_PHA2                 (VKB_BTN_OK_TEXT_W_PHA2)
#define VKB_BTN_CANCEL_TEXT_H_PHA2                 (VKB_BTN_OK_TEXT_H_PHA2)

#define VKB_BTN_CNT_INSET_L                       VKB_WIDTH(10)
#define VKB_BTN_CNT_INSET_R                       VKB_WIDTH(0)
#define VKB_BTN_CNT_INSET_T                       VKB_HEIGHT(0)
#define VKB_BTN_CNT_INSET_B                       VKB_HEIGHT(0)

#define VKB_BTN_FONT_NAME                         APP_FONT_MENU_NAME
#define VKB_BTN_FONT_SIZE                         FE_FNT_SIZE_SMALL
#define VKB_BTN_FONT_STYLE                        FE_FNT_STYLE_REGULAR


/******************************** UI3X Defiens ********************************************/
/*
    Main frame
*/
#define VKB_3X_MAIN_FRAME_ALPHA                      (255)
#define VKB_3X_MAIN_FRAME_W                          (509)
#define VKB_3X_MAIN_FRAME_H                          (600)

/*
    LABLE TEXT
*/
#define VKB_3X_LABLE_X                               (0)
#define VKB_3X_LABLE_Y                               (0)
#define VKB_3X_LABLE_W                               (0)
#define VKB_3X_LABLE_H                               (0)

/*
    EDIT BOX
*/
#define VKB_3X_EB_X                                  (0)
#define VKB_3X_EB_Y                                  (VKB_3X_LABLE_H)
#define VKB_3X_EB_W                                  (508)
#define VKB_3X_EB_H                                  (75)

/*
    CLEAR ICON
*/
#define VKB_3X_CLEAR_EB_W                            (50)
#define VKB_3X_CLEAR_EB_H                            (36)
#define VKB_3X_CLEAR_EB_X                            (VKB_3X_EB_W-VKB_3X_CLEAR_EB_W-20)
#define VKB_3X_CLEAR_EB_Y                            (VKB_3X_EB_Y+(VKB_3X_EB_H-VKB_3X_CLEAR_EB_H)/2)

#define VKB_3X_CLEAR_ALL_X                           (0)
#define VKB_3X_CLEAR_ALL_Y                           (0)
#define VKB_3X_CLEAR_ALL_W                           (50)
#define VKB_3X_CLEAR_ALL_H                           (36)

/*
    KB frame
*/
#define VKB_3X_KB_FRAME_ALPHA                        (255)
#define VKB_3X_KB_FRAME_X                            (0)
#define VKB_3X_KB_FRAME_Y                            (VKB_3X_LABLE_H+VKB_3X_EB_H+53)
#define VKB_3X_KB_FRAME_W                            (VKB_3X_MAIN_FRAME_W)
#define VKB_3X_KB_FRAME_H                            (281)

/* Normal key */
#define VKB_3X_KEYPAD_NORMAL_KEY_TEXT_X              (VKB_3X_KB_FRAME_X) 
#define VKB_3X_KEYPAD_NORMAL_KEY_TEXT_Y              (VKB_3X_KB_FRAME_Y)
#define VKB_3X_KEYPAD_NORMAL_KEY_TEXT_W              (53) 
#define VKB_3X_KEYPAD_NORMAL_KEY_TEXT_H              (53)

/* Ctrl key */
#define VKB_3X_KEYPAD_CTRL_KEY_BIG_X                (VKB_3X_KB_FRAME_X) 
#define VKB_3X_KEYPAD_CTRL_KEY_BIG_Y                (VKB_3X_KB_FRAME_Y+VKB_3X_KB_FRAME_H-53)
#define VKB_3X_KEYPAD_CTRL_KEY_BIG_W                (75) 
#define VKB_3X_KEYPAD_CTRL_KEY_BIG_H                (53)

#define VKB_3X_KEYPAD_CTRL_KEY_SPACE_W              (193) 

#define VKB_3X_KEYPAD_NORMAL_KEY_TEXT_OFFSET        (4)

/*
    BTN OK/CANCLE
*/
#define VKB_3X_BTN_OK_X                              (0)
#define VKB_3X_BTN_OK_Y                              (VKB_3X_KB_FRAME_Y+VKB_3X_KB_FRAME_H+53)
#define VKB_3X_BTN_OK_W                              (VKB_3X_MAIN_FRAME_W)
#define VKB_3X_BTN_OK_H                              (53)

#define VKB_3X_BTN_CL_X                              (VKB_3X_BTN_OK_X)
#define VKB_3X_BTN_CL_Y                              (VKB_3X_BTN_OK_Y+VKB_3X_BTN_OK_H)
#define VKB_3X_BTN_CL_W                              (VKB_3X_BTN_OK_W)
#define VKB_3X_BTN_CL_H                              (VKB_3X_BTN_OK_H)

/******************************** UI3X Defiens ********************************************/

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/

/*
   VKB public resource configuration data.
*/
typedef struct _VKB_RC_CONFIG_DATA_T
{
    /* Template Images */
    WGL_HIMG_TPL_T          h_main_frm_bk_img;                     /* Main frame BK img */
    WGL_HIMG_TPL_T          h_kb_frm_bk_img;                       /* keyboard frame BK img */

    WGL_HIMG_TPL_T          h_editbox_bk_img;                      /* Editbox BK img */
    WGL_HIMG_TPL_T          h_editbox_bk_hlt_img;                  /* Editbox BK highlight img */
    WGL_HIMG_TPL_T          h_editbox_bk_dis_img;                  /* Editbox BK disable img */

    WGL_HIMG_TPL_T          h_keypad_bk_img;                       /* Keypad BK img */
    WGL_HIMG_TPL_T          h_keypad_bk_hlt_img;                   /* Keypad BK hlt  img */
    WGL_HIMG_TPL_T          h_keypad_big_bk_img;                   /* Keypad big BK img */
    WGL_HIMG_TPL_T          h_keypad_big_bk_hlt_img;                /* Keypad big BK hlt  img */
    WGL_HIMG_TPL_T          h_keypad_space_bk_img;                 /* Keypad space BK img */
    WGL_HIMG_TPL_T          h_keypad_space_bk_hlt_img;             /* Keypad space BK hlt  img */

    WGL_HIMG_TPL_T          h_keypad_capslock_bk_img;
    WGL_HIMG_TPL_T          h_keypad_capslock_bk_hlt_img;
    WGL_HIMG_TPL_T          h_keypad_capslock_bk_dis_img;
    WGL_HIMG_TPL_T          h_keypad_delete_bk_img;
    WGL_HIMG_TPL_T          h_keypad_delete_bk_hlt_img;
    WGL_HIMG_TPL_T          h_keypad_delete_bk_dis_img;

    WGL_HIMG_TPL_T          h_keypad_bar_bk_img;                   /* Keypad bar BK img */
    WGL_HIMG_TPL_T          h_keypad_bar_bk_hlt_img;               /* Keypad bar BK hlt  img */

    WGL_HIMG_TPL_T          h_keypad_eb_clear_img;                  /* Keypad clear editbox */
    WGL_HIMG_TPL_T          h_keypad_eb_clear_img_hlt;              /* Keypad clear editbox hightlight */

    /* Color */
    GL_COLOR_T              t_label_txt_clr;                       /* Label text foreground color */
    GL_COLOR_T              t_label_txt_dis_clr;                   /* Label text foreground disable color */

    GL_COLOR_T              t_keypad_key_txt_clr;                  /* Keypad key text foreground color */
    GL_COLOR_T              t_keypad_key_txt_hlt_clr;              /* Keypad key text foreground highlight color */
    GL_COLOR_T              t_keypad_key_txt_dis_clr;              /* Keypad key text foreground disable color */

    GL_COLOR_T              t_btn_txt_clr;                         /* Button text foreground color */
    GL_COLOR_T              t_btn_txt_hlt_clr;                     /* Button text foreground highlight color */
    GL_COLOR_T              t_btn_txt_dis_clr;                     /* Button text foreground disable color */

    GL_COLOR_T              t_editbox_txt_clr;                     /* Editbox text foreground color */
    GL_COLOR_T              t_editbox_txt_hlt_clr;                 /* Editbox text foreground highlight color */
    GL_COLOR_T              t_editbox_txt_dis_clr;                 /* Editbox text foreground disable color */
    GL_COLOR_T              t_editbox_cursor_clr;                  /* Editbox cursor color */

} VKB_RC_CONFIG_DATA_T;

extern VKB_RC_CONFIG_DATA_T t_g_vkb_rc_cfg;
extern VKB_RC_CONFIG_DATA_T t_g_vkb_rc_cfg2;

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/

extern INT32 vkb_rc_init(VKB_RC_CONFIG_DATA_T** ppt_vkb_rc_cfg);
extern INT32 vkb_rc_chg(UINT8 ui2_chg, VKB_RC_CONFIG_DATA_T** ppt_vkb_rc_cfg);

#endif /*_VKB_RC_H*/

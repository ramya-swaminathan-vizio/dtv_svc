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
 * $RCSfile: wzd_cfg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/20 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 3f88970aa8d53b2a36871c1bf4926cd8 $
 *
 * Description:
 *      The file defines the configurable macros for the Wizard application.
 *
 *---------------------------------------------------------------------------*/
#ifndef _WZD_CONFIG_H_
#define _WZD_CONFIG_H_

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef APP_OSD_960x540
/* Font */
#define  WZD_FONT_SIZE_SMALL                 (15)
#define  WZD_FONT_SIZE_MEDIUM                (18)
#define  WZD_FONT_SIZE_LARGE                 (24)

#else
/* Font */
#define  WZD_FONT_SIZE_SMALL                 (20)
#define  WZD_FONT_SIZE_MEDIUM                (24)
#define  WZD_FONT_SIZE_LARGE                 (32)
#endif


/* OSD resolution */
#define  WZD_UI_RATIO_W						(1)
#define  WZD_UI_RATIO_H						(1)

#ifndef WZD_UI_RATIO
#define WZD_UI_RATIO                 		(1)
#endif

#if 0
#if defined(APP_OSD_640x720)
    #define  WZD_UI_RATIO_W                  (0.5)
    #define  WZD_UI_RATIO_H                  (1)
#elif defined(APP_OSD_960x540)
    #define  WZD_UI_RATIO_W                  (0.75)
    #define  WZD_UI_RATIO_H                  (0.75)
#else /* 1280 x 720 */
    #define  WZD_UI_RATIO_W                  4 / 3   //please don't add "()"
    #define  WZD_UI_RATIO_H                  4 / 3    //please don't add "()"
#endif
#endif

/*
   Main frame.
*/
#define  MAIN_FRM_X                          (0)
#define  MAIN_FRM_Y                          (0)
#define  MAIN_FRM_W                          (1280 * WZD_UI_RATIO_W)
#define  MAIN_FRM_H                          (720 * WZD_UI_RATIO_H)
#define  MAIN_FRM_IMG_BK                     h_g_wzd_img_background
#define  MAIN_FRM_IMG_BK_FULL_DLG            h_g_wzd_img_full_screen_dialog


/*
   Base frame. inside the main frame.
*/
#define  BASE_FRM_W                          (MAIN_FRM_W)
#define  BASE_FRM_H                          (MAIN_FRM_H)
#define  BASE_FRM_X                          (0)
#define  BASE_FRM_Y                          (0)
#ifdef APP_IMG_UI
#define  BASE_FRM_IMG_BK                     (NULL_HANDLE) /* h_g_wzd_img_bk */
#else
#define  BASE_FRM_IMG_BK                     h_g_wzd_img_trans
#endif


/*
   Title frame.
*/
#define  WZD_TITLE_TXT_X                      (0)
#define  WZD_TITLE_TXT_Y                      (70 * WZD_UI_RATIO_W)
#define  WZD_TITLE_TXT_W                      (BASE_FRM_W)
#define  WZD_TITLE_TXT_H                      (50 * WZD_UI_RATIO_W)

#define  WZD_TITLE_TXT_INSET_L                (0)
#define  WZD_TITLE_TXT_INSET_R                (0)
#define  WZD_TITLE_TXT_INSET_T                (0)
#define  WZD_TITLE_TXT_INSET_B                (0)

#define  WZD_TITLE_TXT_FNT_SIZE               (32)


/*
   Layout frame. inside the base frame.
*/
#define  LAYOUT_FRM_X                         (0)
#define  LAYOUT_FRM_Y                         (WZD_TITLE_TXT_Y + WZD_TITLE_TXT_H)
#define  LAYOUT_FRM_W                         (BASE_FRM_W - 2 * LAYOUT_FRM_X)
#define  LAYOUT_FRM_H                         (BASE_FRM_H - LAYOUT_FRM_Y)
#define  LAYOUT_FRM_IMG_BK                    h_g_wzd_img_trans

/* Common dialog related */
#define  INPUT_EB_BK_HLT                 h_g_wzd_input_box_square
#define  WZD_DLG_BTN_FG_ICON_OFF         h_g_wzd_dlg_btn_icon_off
#define  WZD_DLG_BTN_FG_ICON_ON          h_g_wzd_dlg_btn_icon_on

#define  SETI_LB_ELEM_IMG_BK_NOR_0       h_g_wzd_img_button_off_0
#define  SETI_LB_ELEM_IMG_BK_HLT_0       h_g_wzd_img_button_on_0
#define  SETI_LB_ELEM_IMG_BK_NOR_1       h_g_wzd_img_button_off_1
#define  SETI_LB_ELEM_IMG_BK_HLT_1       h_g_wzd_img_button_on_1

/* Dialog frame rect */
#define  WZD_DLG_FRM_X                          ((LAYOUT_FRM_W - WZD_DLG_FRM_W)/2)
#define  WZD_DLG_FRM_Y                          (212 * WZD_UI_RATIO_W - LAYOUT_FRM_Y)
#define  WZD_DLG_FRM_W                          (580 * WZD_UI_RATIO_W)
#define  WZD_DLG_FRM_H                          (240 * WZD_UI_RATIO_W)

/* Dialog text rect */
#define  WZD_DLG_TXT_X                          (20 * WZD_UI_RATIO_W)
#define  WZD_DLG_TXT_Y                          (20 * WZD_UI_RATIO_W)
#define  WZD_DLG_TXT_W                          (540 * WZD_UI_RATIO_W)
#define  WZD_DLG_TXT_H                          (135 * WZD_UI_RATIO_W)

#define  WZD_DLG_DESC_TXT_X                     (WZD_DLG_TXT_X)
#define  WZD_DLG_DESC_TXT_Y                     (80 * WZD_UI_RATIO_W)
#define  WZD_DLG_DESC_TXT_W                     (WZD_DLG_TXT_W)
#define  WZD_DLG_DESC_TXT_H                     (90 * WZD_UI_RATIO_W)
#define  WZD_DLG_DESC_TXT_MUTI_LINE_V_OFFS		(20 * WZD_UI_RATIO_W)

#define  WZD_DLG_TXT_FNT_SIZE                   FE_FNT_SIZE_LARGE
#define  WZD_DLG_TXT_DESC_FNT_SIZE              FE_FNT_SIZE_MEDIUM
#define  WZD_DLG_BTN_FNT_SIZE          			FE_FNT_SIZE_MEDIUM
#define  WZD_DLG_TXT_INSET_L                    (0)
#define  WZD_DLG_TXT_INSET_R                    (0)
#define  WZD_DLG_TXT_INSET_T                    (0)
#define  WZD_DLG_TXT_INSET_B                    (0)
#define  WZD_DLG_TXT_LINE_GAPS                  (0)

/**normal*/
#define  WZD_DLG_BTN01_X                        (18 * WZD_UI_RATIO_W)
#define  WZD_DLG_BTN01_Y                        (155 * WZD_UI_RATIO_W)
#define  WZD_DLG_BTN01_W                        (270 * WZD_UI_RATIO_W)
#define  WZD_DLG_BTN01_H                        (78 * WZD_UI_RATIO_W)

#define  WZD_DLG_BTN02_X                        (WZD_DLG_FRM_W - WZD_DLG_BTN01_X - WZD_DLG_BTN01_W)
#define  WZD_DLG_BTN02_Y                        (WZD_DLG_BTN01_Y)
#define  WZD_DLG_BTN02_W                        (WZD_DLG_BTN01_W)
#define  WZD_DLG_BTN02_H                        (WZD_DLG_BTN01_H)

#define  WZD_ENEGRY_ICON_X                   	(735 * WZD_UI_RATIO_W)
#define  WZD_ENEGRY_ICON_Y                      (170 * WZD_UI_RATIO_W)
#define  WZD_ENEGRY_ICON_W                      (54 * WZD_UI_RATIO_W)
#define  WZD_ENEGRY_ICON_H                      (54 * WZD_UI_RATIO_W)

/* Dialog distance between string and image */
#define  WZD_DLG_BTN_DIS               			(25* WZD_UI_RATIO_W)

/*
   Footer frame.
*/
#define WZD_FOOTER_FRM_X                     	(0)
#define WZD_FOOTER_FRM_Y                     	(BASE_FRM_H - WZD_FOOTER_FRM_H)
#define WZD_FOOTER_FRM_W                    	(BASE_FRM_W)
#define WZD_FOOTER_FRM_H                    	(120 * WZD_UI_RATIO_W)

/* footer button gap  */
#define WZD_FOOTER_BTN_GAP                     	(20 * WZD_UI_RATIO_W)
#define WZD_FOOTER_BTN_MARGINS             		((WZD_FOOTER_FRM_W - 3*WZD_FOOTER_BTN_W - 2*WZD_FOOTER_BTN_GAP)/2)

#define WZD_FOOTER_BTN_Y                     	(0)
#define WZD_FOOTER_BTN_W                     	(270 * WZD_UI_RATIO_W)
#define WZD_FOOTER_BTN_H                     	(78 * WZD_UI_RATIO_W)

/* three footer button */
#define WZD_FOOTER_BTN_01_X                     (WZD_FOOTER_BTN_MARGINS)
#define WZD_FOOTER_BTN_02_X                     (WZD_FOOTER_BTN_01_X + WZD_FOOTER_BTN_W + WZD_FOOTER_BTN_GAP)
#define WZD_FOOTER_BTN_03_X                     (WZD_FOOTER_BTN_02_X + WZD_FOOTER_BTN_W + WZD_FOOTER_BTN_GAP)

/* Footer buttons layout */
#define  WZD_FOOTER_BTN_GET_RECTS()                                                                             		\
{                                                                                                               		\
    {WZD_FOOTER_BTN_01_X, WZD_FOOTER_BTN_Y, WZD_FOOTER_BTN_01_X+WZD_FOOTER_BTN_W, WZD_FOOTER_BTN_Y+WZD_FOOTER_BTN_H},	\
    {WZD_FOOTER_BTN_02_X, WZD_FOOTER_BTN_Y, WZD_FOOTER_BTN_02_X+WZD_FOOTER_BTN_W, WZD_FOOTER_BTN_Y+WZD_FOOTER_BTN_H},   \
    {WZD_FOOTER_BTN_03_X, WZD_FOOTER_BTN_Y, WZD_FOOTER_BTN_03_X+WZD_FOOTER_BTN_W, WZD_FOOTER_BTN_Y+WZD_FOOTER_BTN_H},   \
}

#define	WZD_FOOTER_FNT_SIZE          			FE_FNT_SIZE_MEDIUM


/*
   Select box frame. Inside the base frame.
*/
/* Seven select box buttons */
#define WZD_SEL_BOX_FRM_MARGINS				((BASE_FRM_W - 7*WZD_SEL_BOX_BTN_W - 6*WZD_SEL_BOX_BTN_GAP)/2)

#define WZD_SEL_BOX_FRM_X					(WZD_SEL_BOX_FRM_MARGINS)
#define WZD_SEL_BOX_FRM_Y               	(20 * WZD_UI_RATIO)
#define WZD_SEL_BOX_FRM_W       			(BASE_FRM_W - 2*WZD_SEL_BOX_FRM_X)
#define WZD_SEL_BOX_FRM_H             		(660 * WZD_UI_RATIO)

#define WZD_SEL_BOX_BTN_GAP     			(-478 * WZD_UI_RATIO)

#define WZD_SEL_BOX_BTN_Y      				(0)
#define WZD_SEL_BOX_BTN_W          			(704 * WZD_UI_RATIO)
#define WZD_SEL_BOX_BTN_H           		(654 * WZD_UI_RATIO)

#define WZD_SEL_BOX_7_BTN_01_X    			(WZD_SEL_BOX_FRM_X)
#define WZD_SEL_BOX_7_BTN_02_X     			(WZD_SEL_BOX_7_BTN_01_X + WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP)
#define WZD_SEL_BOX_7_BTN_03_X         		(WZD_SEL_BOX_7_BTN_02_X + WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP)
#define WZD_SEL_BOX_7_BTN_04_X          	(WZD_SEL_BOX_7_BTN_03_X + WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP)
#define WZD_SEL_BOX_7_BTN_05_X       		(WZD_SEL_BOX_7_BTN_04_X + WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP)
#define WZD_SEL_BOX_7_BTN_06_X       		(WZD_SEL_BOX_7_BTN_05_X + WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP)
#define WZD_SEL_BOX_7_BTN_07_X       		(WZD_SEL_BOX_7_BTN_06_X + WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP)

/* select box button content */
#define WZD_SEL_BOX_BTN_ICON_1_X   			((WZD_SEL_BOX_BTN_W - WZD_SEL_BOX_BTN_ICON_1_W)/2)
#define WZD_SEL_BOX_BTN_ICON_1_Y     		(186 * WZD_UI_RATIO)
#define WZD_SEL_BOX_BTN_ICON_1_W    		(135 * WZD_UI_RATIO)
#define WZD_SEL_BOX_BTN_ICON_1_H       		(90 * WZD_UI_RATIO)

#define WZD_SEL_BOX_BTN_ICON_2_X     		((WZD_SEL_BOX_BTN_W - WZD_SEL_BOX_BTN_ICON_2_W)/2)
#define WZD_SEL_BOX_BTN_ICON_2_Y        	(276 * WZD_UI_RATIO)
#define WZD_SEL_BOX_BTN_ICON_2_W       		(135 * WZD_UI_RATIO)
#define WZD_SEL_BOX_BTN_ICON_2_H       		(90 * WZD_UI_RATIO)

#define WZD_SEL_BOX_BTN_TXT_X     			((WZD_SEL_BOX_BTN_W - WZD_SEL_BOX_BTN_TXT_W)/2)
#define WZD_SEL_BOX_BTN_TXT_Y          		(366 * WZD_UI_RATIO)
#define WZD_SEL_BOX_BTN_TXT_W          		(210 * WZD_UI_RATIO)
#define WZD_SEL_BOX_BTN_TXT_H          		(90 * WZD_UI_RATIO)

/* Select box buttons layout */
#define WZD_SEL_BOX_7_BTN_GET_RECTS()                                                                                    			\
{                                                                                                                          			\
    {WZD_SEL_BOX_7_BTN_01_X, WZD_SEL_BOX_BTN_Y, WZD_SEL_BOX_7_BTN_01_X+WZD_SEL_BOX_BTN_W, WZD_SEL_BOX_BTN_Y+WZD_SEL_BOX_BTN_H},		\
    {WZD_SEL_BOX_7_BTN_02_X, WZD_SEL_BOX_BTN_Y, WZD_SEL_BOX_7_BTN_02_X+WZD_SEL_BOX_BTN_W, WZD_SEL_BOX_BTN_Y+WZD_SEL_BOX_BTN_H},		\
    {WZD_SEL_BOX_7_BTN_03_X, WZD_SEL_BOX_BTN_Y, WZD_SEL_BOX_7_BTN_03_X+WZD_SEL_BOX_BTN_W, WZD_SEL_BOX_BTN_Y+WZD_SEL_BOX_BTN_H}, 	\
    {WZD_SEL_BOX_7_BTN_04_X, WZD_SEL_BOX_BTN_Y, WZD_SEL_BOX_7_BTN_04_X+WZD_SEL_BOX_BTN_W, WZD_SEL_BOX_BTN_Y+WZD_SEL_BOX_BTN_H}, 	\
    {WZD_SEL_BOX_7_BTN_05_X, WZD_SEL_BOX_BTN_Y, WZD_SEL_BOX_7_BTN_05_X+WZD_SEL_BOX_BTN_W, WZD_SEL_BOX_BTN_Y+WZD_SEL_BOX_BTN_H}, 	\
    {WZD_SEL_BOX_7_BTN_06_X, WZD_SEL_BOX_BTN_Y, WZD_SEL_BOX_7_BTN_06_X+WZD_SEL_BOX_BTN_W, WZD_SEL_BOX_BTN_Y+WZD_SEL_BOX_BTN_H}, 	\
    {WZD_SEL_BOX_7_BTN_07_X, WZD_SEL_BOX_BTN_Y, WZD_SEL_BOX_7_BTN_07_X+WZD_SEL_BOX_BTN_W, WZD_SEL_BOX_BTN_Y+WZD_SEL_BOX_BTN_H}, 	\
}

/*
   Full screen dialog.
*/
#define WZD_FULL_SCREEN_DLG_FRM_X               (MAIN_FRM_X)
#define WZD_FULL_SCREEN_DLG_FRM_Y               (MAIN_FRM_Y)
#define WZD_FULL_SCREEN_DLG_FRM_W               (MAIN_FRM_W)
#define WZD_FULL_SCREEN_DLG_FRM_H               (MAIN_FRM_H)

#define WZD_FULL_SCREEN_DLG_ICON_X              ((WZD_FULL_SCREEN_DLG_FRM_W - WZD_FULL_SCREEN_DLG_ICON_W)/2)
#define WZD_FULL_SCREEN_DLG_ICON_Y              (245 * WZD_UI_RATIO_W)
#define WZD_FULL_SCREEN_DLG_ICON_W              (80 * WZD_UI_RATIO_W)
#define WZD_FULL_SCREEN_DLG_ICON_H              (80 * WZD_UI_RATIO_W)

#define WZD_FULL_SCREEN_DLG_BTN_X               ((WZD_FULL_SCREEN_DLG_FRM_W - WZD_FULL_SCREEN_DLG_BTN_W)/2)
#define WZD_FULL_SCREEN_DLG_BTN_Y               (WZD_FULL_SCREEN_DLG_TEXT_Y + 30)
#define WZD_FULL_SCREEN_DLG_BTN_W               (270 * WZD_UI_RATIO_W)
#define WZD_FULL_SCREEN_DLG_BTN_H               (78 * WZD_UI_RATIO_W)

#define WZD_FULL_SCREEN_DLG_TEXT_X            	((WZD_FULL_SCREEN_DLG_FRM_W - WZD_FULL_SCREEN_DLG_TEXT_W)/2)
#define WZD_FULL_SCREEN_DLG_TEXT_Y             	(WZD_FULL_SCREEN_DLG_ICON_Y + WZD_FULL_SCREEN_DLG_ICON_H + 20 * WZD_UI_RATIO_W)
#define WZD_FULL_SCREEN_DLG_TEXT_W              (580 * WZD_UI_RATIO_W)
#define WZD_FULL_SCREEN_DLG_TEXT_H              (100 * WZD_UI_RATIO_W)


/*   Demo icon. */
#define  WZD_DEMO_ICON_X                      (416 * WZD_UI_RATIO_W)
#define  WZD_DEMO_ICON_Y                      (30 * WZD_UI_RATIO_W)
#define  WZD_DEMO_ICON_W                      (502 * WZD_UI_RATIO_W)
#define  WZD_DEMO_ICON_H                      (477 * WZD_UI_RATIO_W)

/*
   Description text. inside the layout frame.
*/
#define  DESC_TXT_X                          (0 * WZD_UI_RATIO_W)
#define  DESC_TXT_Y                          (10 * WZD_UI_RATIO_W)
#define  DESC_TXT_W                          (LAYOUT_FRM_W)
#define  DESC_TXT_H                          (47 * WZD_UI_RATIO_W)
#define  DESC_TXT_FNT_SIZE                   FE_FNT_SIZE_SMALL
#define  DESC_TXT_ALIGN                      WGL_AS_CENTER_TOP
#define  DESC_TXT_INSET_L                    (13 * WZD_UI_RATIO_W)
#define  DESC_TXT_INSET_R                    (13 * WZD_UI_RATIO_W)
#define  DESC_TXT_INSET_T                    (0 * WZD_UI_RATIO_W)
#define  DESC_TXT_INSET_B                    (0 * WZD_UI_RATIO_W)
#define  DESC_TXT_LINE_GAPS                  (0 * WZD_UI_RATIO_W)

#define  DESC_VIEW_DIVIDER_IMG           h_g_wzd_divider_dotted

/*
    Setting List. inside the layout frame.
*/
#define  SETI_LB_ELEM_NUM                   (8)
#define  SETI_LB_PAGE_ELEM_NUM              (8)

#define  SETI_LB_X                          (LAYOUT_FRM_W * 3 / 5)
#define  SETI_LB_Y                          (5 * WZD_UI_RATIO_H)
#define  SETI_LB_W                          (LAYOUT_FRM_W * 2 / 5 - 15 * WZD_UI_RATIO_W)
#define  SETI_LB_H                          (SETI_LB_ELEM_H * SETI_LB_PAGE_ELEM_NUM)
#define  SETI_LB_ELEM_H                     (33 * WZD_UI_RATIO_H)
#define  SETI_LB_COL_TEXT_W                 SETI_LB_W
#define  SETI_LB_COL_TEXT_FNT_SIZE          FE_FNT_SIZE_MEDIUM
#define  SETI_LB_COL_TEXT_ALIGN             WGL_AS_CENTER_CENTER
#define  SETI_LB_CNT_INSET_L                (0 * WZD_UI_RATIO_W)
#define  SETI_LB_CNT_INSET_R                (0 * WZD_UI_RATIO_W)
#define  SETI_LB_CNT_INSET_T                (0 * WZD_UI_RATIO_W)
#define  SETI_LB_CNT_INSET_B                (0 * WZD_UI_RATIO_W)
#define  SETI_LB_ELEM_INSET_L               (0 * WZD_UI_RATIO_W)
#define  SETI_LB_ELEM_INSET_R               (0 * WZD_UI_RATIO_W)
#define  SETI_LB_ELEM_INSET_T               (0 * WZD_UI_RATIO_W)
#define  SETI_LB_ELEM_INSET_B               (0 * WZD_UI_RATIO_W)
#define  SETI_LB_COL_TEXT_INSET_L           (0 * WZD_UI_RATIO_W)
#define  SETI_LB_COL_TEXT_INSET_R           (0 * WZD_UI_RATIO_W)
#define  SETI_LB_COL_TEXT_INSET_T           (0 * WZD_UI_RATIO_W)
#define  SETI_LB_COL_TEXT_INSET_B           (0 * WZD_UI_RATIO_W)
#define  SETI_LB_IMG_BK                     h_g_wzd_img_trans
#ifdef APP_IMG_UI
#define  SETI_LB_ELEM_IMG_BK                h_g_wzd_img_hl_bk
#else
#define  SETI_LB_ELEM_IMG_BK                h_g_wzd_img_trans
#endif

/*
   Scan progress bar. inside the layout frame.
*/
#define  SCAN_BAR_X                          (WZD_FOOTER_FRM_W/2 - SCAN_BAR_W/2)
#define  SCAN_BAR_Y                          (150 * WZD_UI_RATIO_W)
#define  SCAN_BAR_W                          (1137 * WZD_UI_RATIO_W)
#define  SCAN_BAR_H                          (237 * WZD_UI_RATIO_W)
#define  SCAN_BAR_FNT_SIZE                   FE_FNT_SIZE_SMALL
#ifdef APP_OSD_960x540
#define  SCAN_BAR_INSET_L                    (0)
#else
#define  SCAN_BAR_INSET_L                    (146 * WZD_UI_RATIO_W)
#endif
#define  SCAN_BAR_INSET_R                    (160 * WZD_UI_RATIO_W)
#define  SCAN_BAR_INSET_T                    (125 * WZD_UI_RATIO_W)
#define  SCAN_BAR_INSET_B                    (98 * WZD_UI_RATIO_W)
#define  SCAN_BAR_IMG_BK                     h_g_wzd_img_scan_background 
#define  SCAN_BAR_IMG_LEVEL                  h_g_wzd_img_scan_bar_level

/* Scan text, used to display scan status. Inside the layout frame */
#define  SCAN_TXT_X                          ((SCAN_BAR_X + 140)* WZD_UI_RATIO_W)
#define  SCAN_TXT_Y                          ((SCAN_BAR_Y + 60 )* WZD_UI_RATIO_W)
#define  SCAN_TXT_W                          (450 * WZD_UI_RATIO_W)
#define  SCAN_TXT_H                          (30 * WZD_UI_RATIO_W)

#define  SCAN_TXT_INSET_L                    (0 * WZD_UI_RATIO_W)
#define  SCAN_TXT_INSET_R                    (0 * WZD_UI_RATIO_W)
#define  SCAN_TXT_INSET_T                    (0 * WZD_UI_RATIO_W)
#define  SCAN_TXT_INSET_B                    (0 * WZD_UI_RATIO_W)

#define  SCAN_TXT_ALIGN                      WGL_AS_LEFT_CENTER
#define  SCAN_TXT_LINE_GAPS                  (0 * WZD_UI_RATIO_W)

/*
   Help list. inside the base frame.
*/
#define  HELP_LB_X                           (10 * WZD_UI_RATIO_W)
#define  HELP_LB_Y                           (BASE_FRM_H - HELP_LB_H - 5 * WZD_UI_RATIO_H)
#define  HELP_LB_W                           (BASE_FRM_W - 2 * HELP_LB_X)
#define  HELP_LB_H                           (30 * WZD_UI_RATIO_H)
#define  HELP_LB_ELEM_H                      (HELP_LB_H)
#define  HELP_LB_COL_IMG_W                   (50 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_TEXT_W                  ((HELP_LB_W - HELP_LB_CNT_INSET_L - HELP_LB_CNT_INSET_R)/ 4 - HELP_LB_COL_IMG_W)
#define  HELP_LB_COL_TEXT_FNT_SIZE           FE_FNT_SIZE_SMALL
#define  HELP_LB_COL_IMG_ALIGN               WGL_AS_RIGHT_CENTER
#define  HELP_LB_CNT_INSET_L                 (20 * WZD_UI_RATIO_W)
#define  HELP_LB_CNT_INSET_R                 (20 * WZD_UI_RATIO_W)
#define  HELP_LB_CNT_INSET_T                 (0 * WZD_UI_RATIO_W)
#define  HELP_LB_CNT_INSET_B                 (0 * WZD_UI_RATIO_W)
#define  HELP_LB_ELEM_INSET_L                (0 * WZD_UI_RATIO_W)
#define  HELP_LB_ELEM_INSET_R                (0 * WZD_UI_RATIO_W)
#define  HELP_LB_ELEM_INSET_T                (0 * WZD_UI_RATIO_W)
#define  HELP_LB_ELEM_INSET_B                (0 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_IMG_INSET_L             (0 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_IMG_INSET_R             (5 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_IMG_INSET_T             (0 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_IMG_INSET_B             (0 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_TEXT_INSET_L            (0 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_TEXT_INSET_R            (0 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_TEXT_INSET_T            (0 * WZD_UI_RATIO_W)
#define  HELP_LB_COL_TEXT_INSET_B            (0 * WZD_UI_RATIO_W)

#ifdef WZD_HELP_LST_REVERSE

    #define  HELP_LB_COL_NUM                 (8)

    #define  HELP_LB_COL_TEXT_ALIGN          WGL_AS_RIGHT_CENTER
    #define  HELP_LB_TXT_START_IDX           (0)
    #define  HELP_LB_IMG_START_IDX           (1)
    #define  HELP_LB_BACK_TXT_IDX            (0)
    #define  HELP_LB_BACK_IMG_IDX            (1)
    #define  HELP_LB_SELECT_TXT_IDX          (2)
    #define  HELP_LB_SELECT_IMG_IDX          (3)
    #define  HELP_LB_ENTER_TXT_IDX           (4)
    #define  HELP_LB_ENTER_IMG_IDX           (5)
    #define  HELP_LB_EXIT_TXT_IDX            (6)
    #define  HELP_LB_EXIT_IMG_IDX            (7)

#else /* #ifndef WZD_HELP_LST_REVERSE */

    #define  HELP_LB_COL_NUM                 (8)

    #define  HELP_LB_COL_TEXT_ALIGN          WGL_AS_LEFT_CENTER
    #define  HELP_LB_IMG_START_IDX           (0)
    #define  HELP_LB_TXT_START_IDX           (1)
    #define  HELP_LB_BACK_IMG_IDX            (0)
    #define  HELP_LB_BACK_TXT_IDX            (1)
    #define  HELP_LB_SELECT_IMG_IDX          (2)
    #define  HELP_LB_SELECT_TXT_IDX          (3)
    #define  HELP_LB_ENTER_IMG_IDX           (4)
    #define  HELP_LB_ENTER_TXT_IDX           (5)
    #define  HELP_LB_EXIT_IMG_IDX            (6)
    #define  HELP_LB_EXIT_TXT_IDX            (7)

#endif /* WZD_HELP_LST_REVERSE */

/* WZD color type */
#define  WZD_COLOR_TYPE                      APP_COLOR_TYPE_BLUE

/* WZD font name */
#define  WZD_FONT_NAME                       APP_FONT_WZD_NAME
#define  WZD_FONT_S_NAME                     SN_FONT_DEFAULT_SMALL

/* auto-pause timer delay */
#define  TIMER_PAUSE_DELAY                   (10*60000) /* 10 minutes */

/* Connected TV page related */
#define  CON_TV_HPR_TXT_X                       (0 * WZD_UI_RATIO_W)
#define  CON_TV_HPR_TXT_Y                       (60 * WZD_UI_RATIO_W)
#define  CON_TV_HPR_TXT_W                       (LAYOUT_FRM_W)
#define  CON_TV_HPR_TXT_H                       (80 * WZD_UI_RATIO_W)

#define  CON_TV_HPR_TXT_L                       (13 * WZD_UI_RATIO_W)
#define  CON_TV_HPR_TXT_R                       (30 * WZD_UI_RATIO_W)
#define  CON_TV_HPR_TXT_T                       (0 * WZD_UI_RATIO_W)
#define  CON_TV_HPR_TXT_B                       (0 * WZD_UI_RATIO_W)

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#define  CON_TV_LANG_COUNTRY_DES_TXT_X			(0 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_COUNTRY_DES_TXT_Y			(60 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_COUNTRY_DES_TXT_W			(LAYOUT_FRM_W)
#define  CON_TV_LANG_COUNTRY_DES_TXT_H			(40 * WZD_UI_RATIO_W)

#define	 CON_TV_CHO_LANG_X						(4 * WZD_UI_RATIO_W)
#define	 CON_TV_CHO_LANG_Y						(218 * WZD_UI_RATIO_W)
#define	 CON_TV_CHO_LANG_W						(341 * WZD_UI_RATIO_W)
#define  CON_TV_CHO_LANG_H						(43 * WZD_UI_RATIO_W)

#define	 CON_TV_CHO_COUNTRY_X					(4 * WZD_UI_RATIO_W)
#define	 CON_TV_CHO_COUNTRY_Y					(CON_TV_CHO_LANG_Y+CON_TV_CHO_LANG_H)
#define	 CON_TV_CHO_COUNTRY_W					(341 * WZD_UI_RATIO_W)
#define  CON_TV_CHO_COUNTRY_H					(43 * WZD_UI_RATIO_W)

#define  CON_TV_LANG_X							(150 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_Y							(218 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_W							(175 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_H							(93 * WZD_UI_RATIO_W)

#define  CON_TV_COUNTRY_X						(150 * WZD_UI_RATIO_W)
#define  CON_TV_COUNTRY_Y						(CON_TV_CHO_LANG_Y+CON_TV_CHO_LANG_H)
#define  CON_TV_COUNTRY_W						(175 * WZD_UI_RATIO_W)
#define  CON_TV_COUNTRY_H						(93 * WZD_UI_RATIO_W)
#endif

/*divider line*/
#define  CON_TV_TXT_DIVIDER_X                   (CON_TV_HPR_TXT_L)
#define  CON_TV_TXT_DIVIDER_W                   (LAYOUT_FRM_W - CON_TV_TXT_DIVIDER_X)
#define  CON_TV_TXT_DIVIDER_H                   (1 * WZD_UI_RATIO_W)

/* Content listbox */
#define  CON_TV_LB_COL_TEXT_LENGTH              (50)

#define  CON_TV_LB_CNT_INSET_T                  (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_CNT_INSET_B                  (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_CNT_INSET_L                  (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_CNT_INSET_R                  (0 * WZD_UI_RATIO_W)

#define  CON_TV_LB_ELE_H                        (43 * WZD_UI_RATIO_W)

#define  CON_TV_LB_ELE_INSET_T                  (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_ELE_INSET_B                  (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_ELE_INSET_L                  (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_ELE_INSET_R                  (0 * WZD_UI_RATIO_W)

#define  CON_TV_LB_X                            (4 * WZD_UI_RATIO_W)
#define  CON_TV_LB_Y                            (218 * WZD_UI_RATIO_W)
#define  CON_TV_LB_W                            (341 * WZD_UI_RATIO_W)
#define  CON_TV_LB_H                            (86 * WZD_UI_RATIO_W)

#define  CON_TV_LB_LEFT_INSET                   (8 * WZD_UI_RATIO_W)
#define  CON_TV_LB_RIGHT_INSET                  (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_TOP_INSET                    (0 * WZD_UI_RATIO_W)
#define  CON_TV_LB_BOTTOM_INSET                 (0 * WZD_UI_RATIO_W)

#define  CON_TV_LB_COL_IMG_W                    (25 * WZD_UI_RATIO_W)

#define  CON_TV_LB_MAX_ELEM_NUM                 (3)

/* Language listbox */
#define  CON_TV_LANG_LB_X                       (4 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_LB_Y                       (0 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_LB_W                       (341 * WZD_UI_RATIO_W)
#define  CON_TV_LANG_LB_H                       (129 * WZD_UI_RATIO_W)

/* TV Setup related */
#define  TV_SETUP_CHO_SIG_FRM_X                 (4 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_FRM_Y                 (43 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_FRM_W                 (341 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_FRM_H                 (43 * WZD_UI_RATIO_W)

#define  TV_SETUP_SELECT_CABLE_DEVICE_FRM_X     (TV_SETUP_CHO_SIG_FRM_X)
#define  TV_SETUP_SELECT_CABLE_DEVICE_FRM_Y     (TV_SETUP_CHO_SIG_FRM_Y + TV_SETUP_CHO_SIG_FRM_H)
#define  TV_SETUP_SELECT_CABLE_DEVICE_FRM_W     (TV_SETUP_CHO_SIG_FRM_W)
#define  TV_SETUP_SELECT_CABLE_DEVICE_FRM_H     (TV_SETUP_CHO_SIG_FRM_H)

#define  TV_SETUP_SELECT_INPUT_FRM_X            (TV_SETUP_CHO_SIG_FRM_X)
#define  TV_SETUP_SELECT_INPUT_FRM_Y            (TV_SETUP_SELECT_CABLE_DEVICE_FRM_Y + TV_SETUP_SELECT_CABLE_DEVICE_FRM_H)
#define  TV_SETUP_SELECT_INPUT_FRM_W            (TV_SETUP_CHO_SIG_FRM_W)
#define  TV_SETUP_SELECT_INPUT_FRM_H            (TV_SETUP_CHO_SIG_FRM_H)

#define  TV_SETUP_SELECT_BRAND_FRM_X            (TV_SETUP_CHO_SIG_FRM_X)
#define  TV_SETUP_SELECT_BRAND_FRM_Y            (TV_SETUP_SELECT_INPUT_FRM_Y + TV_SETUP_SELECT_INPUT_FRM_H)
#define  TV_SETUP_SELECT_BRAND_FRM_W            (TV_SETUP_CHO_SIG_FRM_W)
#define  TV_SETUP_SELECT_BRAND_FRM_H            (TV_SETUP_CHO_SIG_FRM_H)

#define  TV_SETUP_SELECT_MODEL_FRM_X            (TV_SETUP_CHO_SIG_FRM_X)
#define  TV_SETUP_SELECT_MODEL_FRM_Y            (TV_SETUP_SELECT_BRAND_FRM_Y + TV_SETUP_SELECT_BRAND_FRM_H)
#define  TV_SETUP_SELECT_MODEL_FRM_W            (TV_SETUP_CHO_SIG_FRM_W)
#define  TV_SETUP_SELECT_MODEL_FRM_H            (TV_SETUP_CHO_SIG_FRM_H)

#define  TV_SETUP_CHO_SIG_TXT_01_X              (9 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_TXT_01_Y              (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_TXT_01_W              (130 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_TXT_01_H              (43 * WZD_UI_RATIO_W)

#define  TV_SETUP_CHO_SIG_TXT_02_X              (150 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_TXT_02_Y              (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_TXT_02_W              (200 * WZD_UI_RATIO_W)
#define  TV_SETUP_CHO_SIG_TXT_02_H              (43 * WZD_UI_RATIO_W)

#define  TV_SETUP_SIG_TYPE_LB_X                 (150 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_Y                 (TV_SETUP_CHO_SIG_FRM_Y)
#define  TV_SETUP_SIG_TYPE_LB_W                 (172 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_H                 (93 * WZD_UI_RATIO_W)

#define  TV_SETUP_SIG_TYPE_LB_TEXT_LENGTH       (50 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_MAX_ELEM_NUM      (12 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_ELE_H             (30 * WZD_UI_RATIO_W)

#define  TV_SETUP_CABLE_DEVICE_TYPE_LB_X        (150 * WZD_UI_RATIO_W)
#define  TV_SETUP_CABLE_DEVICE_TYPE_LB_Y        (TV_SETUP_SELECT_CABLE_DEVICE_FRM_Y)
#define  TV_SETUP_CABLE_DEVICE_TYPE_LB_W        (172 * WZD_UI_RATIO_W)
#define  TV_SETUP_CABLE_DEVICE_TYPE_LB_H        (60 * WZD_UI_RATIO_W)

#define  TV_SETUP_INPUT_TYPE_LB_X                 (150 * WZD_UI_RATIO_W)
#define  TV_SETUP_INPUT_TYPE_LB_Y                 (TV_SETUP_SELECT_INPUT_FRM_Y)
#define  TV_SETUP_INPUT_TYPE_LB_W                 (172 * WZD_UI_RATIO_W)
#define  TV_SETUP_INPUT_TYPE_LB_H                 (150 * WZD_UI_RATIO_W)

#define  TV_SETUP_SIG_TYPE_LB_CNT_INSET_T       (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_CNT_INSET_B       (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_CNT_INSET_L       (1 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_CNT_INSET_R       (1 * WZD_UI_RATIO_W)

#define  TV_SETUP_SIG_TYPE_LB_ELE_INSET_T       (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_ELE_INSET_B       (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_ELE_INSET_L       (5 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_ELE_INSET_R       (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_SIG_TYPE_LB_ELM_DIST          (0 * WZD_UI_RATIO_W)

#define  TV_SETUP_BEGIN_TXT_X                   ((WZD_FULL_SCREEN_DLG_FRM_W - TV_SETUP_BEGIN_TXT_W)/2)
#define  TV_SETUP_BEGIN_TXT_Y                   (23 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_TXT_W                   (560 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_TXT_H                   (70 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_TXT_INSET_L             (10 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_TXT_INSET_R             (5 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_TXT_INSET_T             (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_TXT_INSET_B             (10 * WZD_UI_RATIO_W)

#define  TV_SETUP_CABLE_CONTINUE_BTN_X          (4 * WZD_UI_RATIO_W)
#define  TV_SETUP_CABLE_CONTINUE_BTN_Y          (TV_SETUP_SELECT_MODEL_FRM_Y + TV_SETUP_SELECT_BRAND_FRM_H + (10 * WZD_UI_RATIO_W))
#define  TV_SETUP_CABLE_CONTINUE_BTN_W          (341 * WZD_UI_RATIO_W)
#define  TV_SETUP_CABLE_CONTINUE_BTN_H          (TV_SETUP_CHO_SIG_FRM_H)

#define  TV_SETUP_BEGIN_BTN_X                   (4 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_BTN_Y                   (TV_SETUP_BEGIN_TXT_Y+TV_SETUP_BEGIN_TXT_H)
#define  TV_SETUP_BEGIN_BTN_W                   (341 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_BTN_H                   (43 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_BTN_INSET_L             (26 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_BTN_INSET_R             (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_BTN_INSET_T             (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_BEGIN_BTN_INSET_B             (0 * WZD_UI_RATIO_W)

/* Right Panel Text */
#define  TV_SETUP_RIGHT_PANEL_TXT_X             (420 * WZD_UI_RATIO_W)
#define  TV_SETUP_RIGHT_PANEL_TXT_Y             (220 * WZD_UI_RATIO_W)
#define  TV_SETUP_RIGHT_PANEL_TXT_W             (502 * WZD_UI_RATIO_W)
#define  TV_SETUP_RIGHT_PANEL_TXT_H             (100 * WZD_UI_RATIO_W)
#define  TV_SETUP_RIGHT_PANEL_TXT_INSET_L       (10 * WZD_UI_RATIO_W)
#define  TV_SETUP_RIGHT_PANEL_TXT_INSET_R       (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_RIGHT_PANEL_TXT_INSET_T       (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_RIGHT_PANEL_TXT_INSET_B       (0 * WZD_UI_RATIO_W)

/*
   Video frame
*/
#define  WZD_VIDEO_FRM_X                        (550 * WZD_UI_RATIO_W)
#define  WZD_VIDEO_FRM_Y                        (395 * WZD_UI_RATIO_W)
#define  WZD_VIDEO_FRM_W                        (480 * WZD_UI_RATIO_W)
#define  WZD_VIDEO_FRM_H                        (270 * WZD_UI_RATIO_W)

#define  TV_SETUP_INPUT_MAX_LEN                 (11)

#define  TV_SETUP_SAVE_BTN_X                    (4 * WZD_UI_RATIO_W)
#define  TV_SETUP_SAVE_BTN_Y                    (TV_SETUP_EDIT_BOX_Y+TV_SETUP_EDIT_BOX_H)
#define  TV_SETUP_SAVE_BTN_W                    (341 * WZD_UI_RATIO_W)
#define  TV_SETUP_SAVE_BTN_H                    (TV_SETUP_CHO_SIG_FRM_H)

#define  TV_SETUP_SAVE_BTN_INSET_L              (26 * WZD_UI_RATIO_W)
#define  TV_SETUP_SAVE_BTN_INSET_R              (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_SAVE_BTN_INSET_T              (0 * WZD_UI_RATIO_W)
#define  TV_SETUP_SAVE_BTN_INSET_B              (0 * WZD_UI_RATIO_W)

/* Edit box size */
#define TV_SETUP_EDIT_BOX_X                     (4 * WZD_UI_RATIO_W)
#define TV_SETUP_EDIT_BOX_Y                     (TV_SETUP_CABLE_CONTINUE_BTN_Y)
#define TV_SETUP_EDIT_BOX_W                     (343 * WZD_UI_RATIO_W)
#define TV_SETUP_EDIT_BOX_H                     (TV_SETUP_CHO_SIG_FRM_H)

#define WZD_EB_TXT_FNT_SIZE                 	(30)
#define WZD_EB_TXT_FNT_WIDTH                    (25)

/* vkb position */
#define TV_SETUP_VKB_FRAME_X                    (25 * WZD_UI_RATIO_W)
#define TV_SETUP_VKB_FRAME_Y                    (10 * WZD_UI_RATIO_W)

/* Green check icon */
#define TV_SETUP_GREEN_X                        (31 * WZD_UI_RATIO_W)
#define TV_SETUP_GREEN_Y                        (20 * WZD_UI_RATIO_W)
#define TV_SETUP_GREEN_W                        (27 * WZD_UI_RATIO_W)
#define TV_SETUP_GREEN_H                        (28 * WZD_UI_RATIO_W)

/* Complete text */
#define TV_SETUP_COMP_X                         (65 * WZD_UI_RATIO_W)
#define TV_SETUP_COMP_Y                         (15 * WZD_UI_RATIO_W)
#define TV_SETUP_COMP_W                         (294 * WZD_UI_RATIO_W)
#define TV_SETUP_COMP_H                         (43 * WZD_UI_RATIO_W)

/* Exit button */
#define TV_SETUP_EXIT_X                         (4 * WZD_UI_RATIO_W)
#define TV_SETUP_EXIT_Y                         (58 * WZD_UI_RATIO_W)
#define TV_SETUP_EXIT_W                         (343 * WZD_UI_RATIO_W)
#define TV_SETUP_EXIT_H                         (43 * WZD_UI_RATIO_W)

/* Green check icon */
#define COMP_GREEN_X                        (31 * WZD_UI_RATIO_W)
#define COMP_GREEN_Y                        (20 * WZD_UI_RATIO_W)
#define COMP_GREEN_W                        (27 * WZD_UI_RATIO_W)
#define COMP_GREEN_H                        (28 * WZD_UI_RATIO_W)

/* Complete text */
#define COMP_COMP_X                         (65 * WZD_UI_RATIO_W)
#define COMP_COMP_Y                         (15 * WZD_UI_RATIO_W)
#define COMP_COMP_W                         (294 * WZD_UI_RATIO_W)
#define COMP_COMP_H                         (43 * WZD_UI_RATIO_W)

/* Exit button */
#define COMP_EXIT_X                         (4 * WZD_UI_RATIO_W)
#define COMP_EXIT_Y                         (58 * WZD_UI_RATIO_W)
#define COMP_EXIT_W                         (343 * WZD_UI_RATIO_W)
#define COMP_EXIT_H                         (43 * WZD_UI_RATIO_W)

/* remote setup*/
/*begin active button*/
#define BT_REMOTE_DESC_HTXT_X            (4 * WZD_UI_RATIO_W)
#define BT_REMOTE_DESC_HTXT_Y            (5 * WZD_UI_RATIO_W)
#define BT_REMOTE_DESC_HTXT_W            (343 * WZD_UI_RATIO_W)
#define BT_REMOTE_DESC_HTXT_H            (100 * WZD_UI_RATIO_W)

#define BT_REMOTE_HPR_TXT_L              (4 * WZD_UI_RATIO_W)
#define BT_REMOTE_HPR_TXT_R              (0 * WZD_UI_RATIO_W)
#define BT_REMOTE_HPR_TXT_T              (0 * WZD_UI_RATIO_W)
#define BT_REMOTE_HPR_TXT_B              (0 * WZD_UI_RATIO_W)

#define BT_REMOTE_BEGIN_ACTIVE_X            (4 * WZD_UI_RATIO_W)
#define BT_REMOTE_BEGIN_ACTIVE_Y            (250 * WZD_UI_RATIO_W)
#define BT_REMOTE_BEGIN_ACTIVE_W            (343 * WZD_UI_RATIO_W)
#define BT_REMOTE_BEGIN_ACTIVE_H            (43 * WZD_UI_RATIO_W)

#define REMOTE_SETUP_RESULT_X               (120 * WZD_UI_RATIO_W)
#define REMOTE_SETUP_RESULT_Y               (15 * WZD_UI_RATIO_W)
#define REMOTE_SETUP_RESULT_W               (294 * WZD_UI_RATIO_W)
#define REMOTE_SETUP_RESULT_H               (43 * WZD_UI_RATIO_W)

#define BT_REMOTE_TRY_AGAIN_X               (4 * WZD_UI_RATIO_W)
#define BT_REMOTE_TRY_AGAIN_Y               (REMOTE_SETUP_RESULT_Y + REMOTE_SETUP_RESULT_H)
#define BT_REMOTE_TRY_AGAIN_W               (343 * WZD_UI_RATIO_W)
#define BT_REMOTE_TRY_AGAIN_H               (43 * WZD_UI_RATIO_W)

/* searching icon position */
#define WZD_BT_REMOTE_ICON_X          (160 * WZD_UI_RATIO_W)
#define WZD_BT_REMOTE_ICON_Y          (300 * WZD_UI_RATIO_W)
#define WZD_BT_REMOTE_ICON_W          (33 * WZD_UI_RATIO_W)
#define WZD_BT_REMOTE_ICON_H          (33 * WZD_UI_RATIO_W)

#define WZD_BT_REMOTE_OK_X                        (31 * WZD_UI_RATIO_W)
#define WZD_BT_REMOTE_OK_Y                        (20 * WZD_UI_RATIO_W)
#define WZD_BT_REMOTE_OK_W                        (27 * WZD_UI_RATIO_W)
#define WZD_BT_REMOTE_OK_H                        (28 * WZD_UI_RATIO_W)

/* remote setup*/
/*begin active button*/
//#define WIFI_REMOTE_DESC_HTXT_X            (4 * WZD_UI_RATIO_W)
//#define WIFI_REMOTE_DESC_HTXT_Y            (5 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_DESC_HTXT_X            (230 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_DESC_HTXT_Y            (50 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_DESC_HTXT_W            (800 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_DESC_HTXT_H            (100 * WZD_UI_RATIO_W)

#define WIFI_REMOTE_HPR_TXT_L              (4 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_HPR_TXT_R              (0 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_HPR_TXT_T              (0 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_HPR_TXT_B              (0 * WZD_UI_RATIO_W)

#define WIFI_REMOTE_BEGIN_ACTIVE_X            (4 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_BEGIN_ACTIVE_Y            (250 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_BEGIN_ACTIVE_W            (343 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_BEGIN_ACTIVE_H            (43 * WZD_UI_RATIO_W)

#define WIFI_REMOTE_TRY_AGAIN_X               (4 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_TRY_AGAIN_Y               (REMOTE_SETUP_RESULT_Y + REMOTE_SETUP_RESULT_H)
#define WIFI_REMOTE_TRY_AGAIN_W               (343 * WZD_UI_RATIO_W)
#define WIFI_REMOTE_TRY_AGAIN_H               (43 * WZD_UI_RATIO_W)

/* searching icon position */
#define WZD_WIFI_REMOTE_ICON_X          ((1280-44)/2 * WZD_UI_RATIO_W)/*578*/
#define WZD_WIFI_REMOTE_ICON_Y          ((50-26+10) * WZD_UI_RATIO_W)
#define WZD_WIFI_REMOTE_ICON_W          (44 * WZD_UI_RATIO_W)
#define WZD_WIFI_REMOTE_ICON_H          (44 * WZD_UI_RATIO_W)

#define WZD_WIFI_REMOTE_OK_X                        (31 * WZD_UI_RATIO_W)
#define WZD_WIFI_REMOTE_OK_Y                        (20 * WZD_UI_RATIO_W)
#define WZD_WIFI_REMOTE_OK_W                        (27 * WZD_UI_RATIO_W)
#define WZD_WIFI_REMOTE_OK_H                        (28 * WZD_UI_RATIO_W)

#define WZD_WIFI_REMOTE_IMAGE_ICON_X                     (245+40 * WZD_UI_RATIO_W)
#define WZD_WIFI_REMOTE_IMAGE_ICON_Y                     (118 * WZD_UI_RATIO_W)/*720-120-482=118*/
#define WZD_WIFI_REMOTE_IMAGE_ICON_W                     (786 * WZD_UI_RATIO_W)
#define WZD_WIFI_REMOTE_IMAGE_ICON_H                     (482 * WZD_UI_RATIO_W)

#endif /* _WZD_CONFIG_H_ */
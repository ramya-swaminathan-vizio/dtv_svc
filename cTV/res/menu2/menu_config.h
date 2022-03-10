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
 * $RCSfile: menu_config.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/16 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 356e3bb69ca7ee6fc6d5ae317ddcc8a4 $
 *
 * Description:
 *      The file contains the configurable macros and compilation option
 * of the MENU application.
 *
 * Compilation Options:
 *      APP_MENU_IMG_UI         -   Show image UI in menu.
 *
 *      APP_MENU_LOOSELY        -   The platform uses Loosely-couple solution, such
 *                              that some setting is moved to ATV menu, e.g.
 *                              GUI Language, VCHIP, Change Password, Reset, etc.
 *
 *      APP_MENU_BACK_ON_MENU_KEY   -   The menu key is used to back to upper page.
 *                              This is useful when the EXIT key is unavailable.
 *
 *      APP_MENU_TAB_LEAVE_ON_BOUNDARY  -   When pressing left on the first tab or
 *                              right on last tab, the menu will leave.
 *                              It is useful to integrate with ATV menu.
 *
 *      APP_MENU_TAB_PAUSE_ON_EXIT  -   When pressing exit on tabs, menu will pause
 *                              directly. (otherwise it will call menu_leave() ).
 *                              It only takes effect when the menu is in slave
 *                              mode.
 *
 *      APP_MENU_FAV_LST        -   The favorite list is set in menu
 *
 *      APP_MENU_WITH_ACC_TEXT   -   There is no TEXT1~TEXT4 in "Analog Closed
 *                              Caption Setting.
 *
 *      CS_FS_STYLE_NUM     -   In "Caption Style" page, the number of font style.
 *                              If the number is 1, the "Font Style" setting is
 *                              not available.
 *
 *      APP_MENU_CLEAN_LISTS_BEFORE_AUTO_SCAN -  Clean the channel lists before
 *                              auto scan.
 *
 *      APP_MENU_NAV_BACK_AFTER_AUTO_SCAN -  Back to the previous page after
 *                              auto scan.
 *
 *      APP_MENU_DCR_SUPPORT    - In menu, add the tab of AP List and enable/disable
 *                              scan pages. This option only works in DCR model.
 *
 *      APP_MENU_VERTICAL_TABS - The tabs is vertically arranged. Note that because
 *                              the parent of tabs is titlebar, the size of titlebar
 *                              should be adjusted accordingly in case that the tabs
 *                              are out of the clipping region.
 *
 *      APP_MENU_ONE_TAB_MODE  - There is only one tab in the menu. When the
 *                               menu is opened, it will directly go to the page
 *                               of the first tab. It still uses menu_pm_add_tab()
 *                               to attach page to the menu. In addition, because
 *                               the tab is never focused, we enter the factory
 *                               page by pressing "0000" in the first PAGE instead
 *                               of first TAB.
 *
 *      APP_MENU_PAGE_TREE_ALWAYS_SLIDER_MODE - In menu page tree, always enter
 *                               slider mode when adjusting an range menu item.
 *
 *      APP_MENU_GO_LATEST_TAB_WHEN_RESUME - Go to latest tab when resume menu.
 *
 *      APP_MENU_GO_LATEST_PAGE_WHEN_RESUME - Go to latest page when resume menu.
 *
 *---------------------------------------------------------------------------*/
#ifndef _menu_config_h_
#define _menu_config_h_

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define COMMON_BCST_ENABLE
#define COMMON_PWD_ENABLE
#define COMMON_CHG_PWD_ENABLE
#define COMMON_RESET_ENABLE
#define COMMON_CH_LST2_ENABLE
#define COMMON_VER_INFO_ENABLE
#define COMMON_SIMPLE_DIALOG_ENABLE
#define COMMON_VGA_AUTO_ENABLE
#define COMMON_AUTO_COLOR_ENABLE
#define COMMON_AUTO_PHASE_ENABLE
#define COMMON_INP_LST_ENABLE
#define COMMON_INP_SRC_ENABLE
#define COMMON_INP_SRC_NAMING_ENABLE
#define COMMON_DATE_TIME_ENABLE
#ifdef APP_MJC_SUPPORT
    #define COMMON_MJC_DEMO_ENABLE
#endif
#define ATSC_AUTO_SCAN2_ENABLE
#define ATSC_ADV_SCAN_RNG_ENABLE
#define ATSC_ADV_SCAN_SGL_ENABLE
#define ATSC_CAP_STL_ENABLE
#ifdef APP_MENU_LCT_CODE_SUPPORT
    #define ATSC_LCT_CODE_ENABLE
#endif
#define ATSC_VCHIP_US_TV_ENABLE
#define ATSC_VCHIP_US_MOVIE_ENABLE
#define ATSC_VCHIP_CA_EN_ENABLE
#define ATSC_VCHIP_CA_FR_ENABLE
#define ATSC_OP_VCHIP_ENABLE
/* ex pages */
#define COMMON_EX_MAIN_MENU_ENABLE
#define COMMON_EX_MASTERLIST_ENABLE
#define COMMON_EX_CH_EDIT_ENABLE

#ifndef APP_MENU_IMG_UI
    #ifdef  APP_IMG_UI
        #define APP_MENU_IMG_UI
    #endif
#endif

#ifndef APP_MENU_LOOSELY
    #ifdef APP_LOOSELY_COUPLE
        #define APP_MENU_LOOSELY
    #endif
#endif

#ifndef APP_MENU_FAV_LST
    #ifdef APP_FAV_LST_IN_MENU
        #define APP_MENU_FAV_LST
    #endif
#endif

#ifndef APP_MENU_EAS
    #ifdef APP_EAS_SUPPORT
        #define APP_MENU_EAS
    #endif
#endif

#ifdef APP_NETWORK_SUPPORT
#define COMMON_NETWORK_CFG_ENABLE
#endif

/* #define APP_MENU_TAB_LEAVE_ON_BOUNDARY */

/* #define APP_MENU_TAB_PAUSE_ON_EXIT */

/* #define APP_MENU_VERTICAL_TABS */

#define APP_MENU_ONE_TAB_MODE

#define APP_MENU_PAGE_TREE_ALWAYS_SLIDER_MODE

#define APP_MENU_HDMI_MODE_SUPPORT

#define APP_MENU_ADP_BACK_LIGHT_SUPPORT

#define APP_MENU_OP_VCHIP_ENABLE

#define  APP_MENU_DLG_COEXIST

/* Font size */
#define FONT_SIZE_SMALL         18
#define FONT_SIZE_MEDIUM        18
#define FONT_SIZE_LARGE         22

#define R_W      1
#define R_H      1

/* The screen size */
#define SCREEN_W                ((INT32)menu_canvas_width())
#define SCREEN_H                ((INT32)menu_canvas_height())

/* The main frame of menu */
#define FRAME_X                 (0)
#define FRAME_Y                 (0)
#define FRAME_W                 (638 * R_W) //(412 * R_W)
#define FRAME_H                 (1080 * R_H) // (720 * R_H)

#define FRAME_LEFT_RIGHT_INTV   (65 * R_W)
#define FRAME_TOP_INTV          (40 * R_H)
#define MENU_ITEM_WIDTH         (508 * R_H)

#define HELP_TIP_FRAME_X        (0)
#define HELP_TIP_FRAME_Y        (FRAME_H - (250 * R_H))
#define HELP_TIP_FRAME_W        (FRAME_W)
#define HELP_TIP_FRAME_H        (FRAME_H)

#define HOME_BAR_X              (CONTENT_DIS - 4)
#define HOME_BAR_Y              (4)
#define HOME_BAR_W              (MENU_ITEM_V_WIDE)
#define HOME_BAR_H              (MENU_ITEM_V_HEIGHT)

#define HOME_ICON_X             (MENU_ITEM_V_WIDE-HOME_ICON_W-5)
#define HOME_ICON_Y             ((HOME_BAR_H-HOME_ICON_H)/2)
#define HOME_ICON_W             (28)
#define HOME_ICON_H             (24)

#define TITLE_FRM_X             (FRAME_LEFT_RIGHT_INTV)
#define TITLE_FRM_Y             (FRAME_TOP_INTV)
#define TITLE_FRM_W             (MENU_ITEM_WIDTH)
#define TITLE_FRM_H             (73)

#define BACK_BAR_X              (475)
#define BACK_BAR_Y              (FRAME_TOP_INTV)
#define BACK_BAR_W              (106)
#define BACK_BAR_H              (46)

#define MAIN_TITLE_X            (200)
#define MAIN_TITLE_Y            ( 20)
#define MAIN_TITLE_W            (100)
#define MAIN_TITLE_H            ( 20)
#define MAIN_TITLE_ALIGN        (WGL_AS_RIGHT_CENTER)

#define TITLE_X                 (TITLE_FRM_X)
#define TITLE_Y                 (TITLE_FRM_Y)
#define TITLE_W                 (TITLE_FRM_W-BACK_BAR_W)
#define TITLE_H                 (TITLE_FRM_H)
#define TITLE_ALIGN             (WGL_AS_LEFT_TOP) //(WGL_AS_LEFT_CENTER)
#define TITLE_FONT_SIZE         (FE_FNT_SIZE_CUSTOM) //(FE_FNT_SIZE_SMALL)

/* Titlebar (the bar in the top of menu) */
#define TITLEBAR_X              (0)
#define TITLEBAR_Y              (0)
#define TITLEBAR_W              (1)
#define TITLEBAR_H              (1)

/* Titlebar Tabs */
#define TITLEBAR_TAB_X          (0)
#define TITLEBAR_TAB_Y          (0)
#define TITLEBAR_TAB_W          (1)
#define TITLEBAR_TAB_H          (1)


/* Content Frame (the space in the center of menu) */
#define CONTENT_DIS             (0) //(8)
#define CONTENT_X               (0) //(4)
#define CONTENT_Y               (TITLE_FRM_Y+TITLE_FRM_H)
#define CONTENT_W               (FRAME_W-CONTENT_DIS)
#define CONTENT_H               (FRAME_H-CONTENT_Y)

/* mjc demo */
#define MJC_DEMO_CHASSIS_X      (0)
#define MJC_DEMO_CHASSIS_Y      (0)
#define MJC_DEMO_CHASSIS_W      (SCREEN_W)
#define MJC_DEMO_CHASSIS_H      (SCREEN_H)

#define MJC_DEMO_LINE_X         ((SCREEN_W/2)-4)
#define MJC_DEMO_LINE_Y         (0)
#define MJC_DEMO_LINE_W         (8)
#define MJC_DEMO_LINE_H         (SCREEN_H)

#define MJC_DEMO_L_TXT_X        ((SCREEN_W/2)-(SCREEN_W/4)-(MJC_DEMO_LR_TXT_W/2))
#define MJC_DEMO_R_TXT_X        ((SCREEN_W/2)+(SCREEN_W/4)-(MJC_DEMO_LR_TXT_W/2))
#define MJC_DEMO_LR_TXT_Y       (SCREEN_H / 3)
#define MJC_DEMO_LR_TXT_W       (136)
#define MJC_DEMO_LR_TXT_H       (45)

#define MJC_DEMO_C_TXT_X        (MJC_DEMO_LINE_X-MJC_DEMO_C_TXT_W/2)
#define MJC_DEMO_C_TXT_Y        (SCREEN_H / 6)
#define MJC_DEMO_C_TXT_W        (350)
#define MJC_DEMO_C_TXT_H        (64)


/* We split the content frame into several grids. *
 * There are 16 x 10 Grids in the content frame   */
#define GRID_W                  (CONTENT_W / 16)
#define GRID_H                  (CONTENT_H / 15)

/* Menu timeout */
#define TIMER_DELAY             (60000) /* 60 sec */

/* Menu hide delay, only used in slave mode */
#define MENU_PM_HIDE_DELAY      (  0)
#define MENU_PM_HIDE_DELAY2     (  0)
#define MENU_PM_OSD_ALPHA       (255)
#define MENU_PM_FADE_DELAY      (150)
#define MENU_PM_FADE_STEP       ( 10)

/* Need customze by ODM*/
#define VERSION_KEY_LIST_SIZE   4

#ifndef VERSION_KEY_LIST
#define VERSION_KEY_LIST        {BTN_DIGIT_0, BTN_DIGIT_0, BTN_DIGIT_0, BTN_DIGIT_0};
#endif


/*

  | +-------------------------------------------------------------+ |
  |1|2|3,icon |     4,title        |        5,value      |6,hint|7|8|
  | +-------------------------------------------------------------+ |

  1 = MENU_ITEM_BAR_INSET_L
  2 = MENU_ITEM_BAR_CNT_INSET_L
  3 = MENU_ITEM_ICON_W
  4 = MENU_ITEM_TITLE_W
  5 = MENU_ITEM_VALUE_W
  6 = MENU_ITEM_HINT_W
  7 = MENU_ITEM_BAR_CNT_INSET_R
  8 = MENU_ITEM_BAR_INSET_R
*/

/*********************MENU ITEM*******************/
#define MENU_ITEM_V_LEFT            (0)
#define MENU_ITEM_V_WIDE            (638) // (401)
#define MENU_ITEM_V_HEIGHT          (75)  //(44)
#define MENU_ITEM_V_INSET_L         (0)
#define MENU_ITEM_V_INSET_R         (0)
#define MENU_ITEM_V_CNT_INSET_L     (10)
#define MENU_ITEM_V_CNT_INSET_R     (7)
#define MENU_ITEM_V_TITLE_W         (120)
#define MENU_ITEM_V_VALUE_W         (270)
#define MENU_ITEM_V_VALUE_W_CH_SCAN (400) //channel scan status width modify
#define MENU_ITEM_V_RANGE_TITLE_W   (140)
#define MENU_ITEM_V_INDICATOR_X     (FRAME_W-FRAME_LEFT_RIGHT_INTV)
#define MENU_ITEM_V_INDICATOR_W     (10)
#define MENU_ITEM_V_LB_ARROW_W      (30)
#define MENU_ITEM_V_LB_INSET_L      (10)
#define MENU_ITEM_V_LB_INSET_R      (0)
#define MENU_ITEM_V_ICON_LOCK       (25)
#define MENU_ITEM_V_LB_ELIMENT_INSET_L (5)
#define MENU_ITEM_V_SETTING_ICON    (35)
#define MENU_ITEM_V_SETTING_TEXT    (100)
#define MENU_ITEM_V_SETTING_SIGNAL  (60)




#define MENU_ITEM_BAR_INSET_L       0
#define MENU_ITEM_BAR_INSET_R       0
#define MENU_ITEM_BAR_CNT_INSET_L   8
#define MENU_ITEM_BAR_CNT_INSET_R   20
#define MENU_ITEM_ICON_W            0
#define MENU_ITEM_TITLE_W           (GRID_W * 17  / 2 - MENU_ITEM_BAR_INSET_L - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_ICON_W)
#define MENU_ITEM_HINT_W            48
#define MENU_ITEM_VALUE_W           (CONTENT_W - \
                                    MENU_ITEM_BAR_INSET_L - MENU_ITEM_BAR_INSET_R - \
                                    MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R - \
                                    MENU_ITEM_ICON_W - MENU_ITEM_TITLE_W - MENU_ITEM_HINT_W)
#define MENU_ITEM_FNT_SIZE          FE_FNT_SIZE_MEDIUM
#define MENU_ITEM_FNT_STYLE         FE_FNT_STYLE_REGULAR

/* Range item */
#define MENU_ITEM_RNG_CNT_INSET_T       6
#define MENU_ITEM_RNG_CNT_INSET_B       6
#define MENU_ITEM_RNG_BAR_INSET_L       0
#define MENU_ITEM_RNG_BAR_INSET_R       0
#define MENU_ITEM_RNG_BAR_INSET_T       0
#define MENU_ITEM_RNG_BAR_INSET_B       0
#define MENU_ITEM_RNG_BLK_PT_SIZE_W     15
#define MENU_ITEM_RNG_BLK_PT_SIZE_H     13
#define MENU_ITEM_RNG_BAR_MIN_SIZE      14

/* Edit item */
#define MENU_ITEM_EDIT_INSET_T      (2)
#define MENU_ITEM_EDIT_INSET_B      (1)
#define MENU_ITEM_EDIT_CNT_INSET_L  (0)
#define MENU_ITEM_EDIT_CNT_INSET_R  (0)
#define MENU_ITEM_EDIT_CNT_INSET_T  (0)
#define MENU_ITEM_EDIT_CNT_INSET_B  (0)
#define MENU_ITEM_EDIT_ALIGN        (WGL_AS_CENTER_CENTER)
#define MENU_ITEM_EDIT_FNT_SIZE     (FE_FNT_SIZE_MEDIUM)
#define MENU_ITEM_EDIT_FNT_STYLE    (FE_FNT_STYLE_REGULAR)
#define MENU_ITEM_PWD_CNT_INSET_L   (116)
#define MENU_ITEM_PWD_CNT_INSET_R   (0)
#define MENU_ITEM_PWD_CNT_INSET_T   (3)
#define MENU_ITEM_PWD_CNT_INSET_B   (0)
#define MENU_ITEM_PWD_ALIGN         (WGL_AS_LEFT_CENTER)
#define MENU_ITEM_PWD_FNT_SIZE      (FE_FNT_SIZE_LARGE)
#define MENU_ITEM_PWD_FNT_STYLE     (FE_FNT_STYLE_REGULAR)

/*********************COMMON*******************/
/* Channel List */
#define CH_LST_STL_SCROLL       0
#define CH_LST_STL_WRAP_OVER    0
#define CH_LST_X                0
#define CH_LST_Y                0
#define CH_LST_W                (CONTENT_W)
#define CH_LST_H                (CONTENT_H)

#define CH_LST2_COL0_W          (80)
#define CH_LST2_COL1_W          (1)
#define CH_LST2_COL2_W          (125)
#define CH_LST2_COL3_W          (60)

#define CH_LST_ELEM_H           GRID_H
#define CH_LST_ELEM_N           512
#define CH_LST2_COL0_ALIGN      WGL_AS_RIGHT_CENTER
#define CH_LST2_COL1_ALIGN      WGL_AS_LEFT_CENTER
#define CH_LST2_COL2_ALIGN      WGL_AS_LEFT_CENTER
#define CH_LST2_COL3_ALIGN      WGL_AS_RIGHT_CENTER

/* Pwd Box*/
#define PWDBOX_INSET_L          (2 * R_W)
#define PWDBOX_INSET_R          (2 * R_W)
#define PWDBOX_INSET_T          (2 * R_H)
#define PWDBOX_INSET_B          (2 * R_H)
#define PWDBOX_CNT_INSET_L      ((4 * R_W) * GRID_W - (48 * R_W))
#define PWDBOX_CNT_INSET_R      0
#define PWDBOX_CNT_INSET_T      (5 * R_H)
#define PWDBOX_CNT_INSET_B      0

/* Password Page */
#define PWD_ALARM_X             (2 * GRID_W)
#define PWD_ALARM_Y             (1 * GRID_H)
#define PWD_ALARM_W             (12 * GRID_W)
#define PWD_ALARM_H             (3 * GRID_H)
#define PWD_ALARM_FONT_SIZE     FE_FNT_SIZE_LARGE

/* Change Password Page */
#define CHG_PWD_ALARM_X         (2 * GRID_W)
#define CHG_PWD_ALARM_Y         (2 * GRID_H + 5)
#define CHG_PWD_ALARM_W         (12 * GRID_W)
#define CHG_PWD_ALARM_H         (3 * GRID_H)
#define CHG_PWD_ALARM_FONT_SIZE FE_FNT_SIZE_LARGE

/* Reset Default Page */
#define RD_TXT_INFO_X           (1 * GRID_W)
#define RD_TXT_INFO_Y           (1 * GRID_H)
#define RD_TXT_INFO_W           (14 * GRID_W)
#define RD_TXT_INFO_H           (8 * GRID_H)

/* Input List */

/* Pending */
#define INP_LST_X               (0)
#define INP_LST_Y               (0)
#define INP_LST_W               (CONTENT_W)
#define INP_LST_H               (CONTENT_H)
#define INP_LST_ELEM_H          GRID_H
#define INP_LST_COL0_W          (INP_LST_W/2)
#define INP_LST_COL1_W          (INP_LST_W/2)

#define INP_LST_COL2_W          (80 * R_W)
#define INP_LST_COL0_ALIGN      WGL_AS_LEFT_CENTER
#define INP_LST_COL1_ALIGN      WGL_AS_LEFT_CENTER
#define INP_LST_COL2_ALIGN      WGL_AS_RIGHT_CENTER

/*********************ATSC*******************/
/* Caption Page */
#define APP_MENU_WITH_ACC_TEXT

/* Caption Style Page */
#define CS_CC_PV_H              660*4/3
#define CS_CC_PV_V              641*4/3
#define CS_CC_PV_A              WGL_CC_ANCHOR_POINT_0


#define CS_FS_STYLE_NUM         7

#define CS_FS_STYLE1            SN_FONT_MONO_SP_SERF_CUSTOM
#define CS_FS_STYLE2            SN_FONT_PROP_SP_SERF_CUSTOM
#define CS_FS_STYLE3            SN_FONT_MONO_SP_WO_SERF_CUSTOM
#define CS_FS_STYLE4            SN_FONT_PROP_SP_WO_SERF_CUSTOM
#define CS_FS_STYLE5            SN_FONT_CASUAL_CUSTOM
#define CS_FS_STYLE6            SN_FONT_CURSIVE_CUSTOM
#define CS_FS_STYLE7            SN_FONT_SMALL_CAPITALS_CUSTOM

/* Auto Scan 2 Page */
#define ATSC_AUTO_SCAN2_TXT_INFO_X      (10)
#define ATSC_AUTO_SCAN2_TXT_INFO_Y      (10)
#define ATSC_AUTO_SCAN2_TXT_INFO_W      (536)
#define ATSC_AUTO_SCAN2_TXT_INFO_H      (130)
#define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_T        (10)
#define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_B        (10)
#define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_L        (30)
#define ATSC_AUTO_SCAN2_TXT_INFO_CNT_INSET_R        (30)
#define ATSC_AUTO_SCAN2_TXT_TUNER_X     (50)
#define ATSC_AUTO_SCAN2_TXT_TUNER_Y     (20)
#define ATSC_AUTO_SCAN2_TXT_TUNER_W     (476)
#define ATSC_AUTO_SCAN2_TXT_TUNER_H     (25)
#define ATSC_AUTO_SCAN2_TXT_TUNER_ALIGN (WGL_AS_RIGHT_TOP)
#define ATSC_AUTO_SCAN2_PB_X            (50)
#define ATSC_AUTO_SCAN2_PB_Y            (105)
#define ATSC_AUTO_SCAN2_PB_W            (FRAME_W - 2 * ATSC_AUTO_SCAN2_PB_X)
#define ATSC_AUTO_SCAN2_PB_H            (25)
#define ATSC_AUTO_SCAN2_PB_VAL_W        (80)
#define ATSC_AUTO_SCAN2_PB_CNT_INSET_T  (6)
#define ATSC_AUTO_SCAN2_PB_CNT_INSET_B  (6)
#define ATSC_AUTO_SCAN2_PB_BAR_INSET_L  (0)
#define ATSC_AUTO_SCAN2_PB_BAR_INSET_R  (0)
#define ATSC_AUTO_SCAN2_PB_BAR_INSET_T  (0)
#define ATSC_AUTO_SCAN2_PB_BAR_INSET_B  (0)

/* Advanced Scan Range Page */
#define ATSC_ADV_SCAN_RNG_TXT_INFO_X        (20)
#define ATSC_ADV_SCAN_RNG_TXT_INFO_Y        (10)
#define ATSC_ADV_SCAN_RNG_TXT_INFO_W        (536)
#define ATSC_ADV_SCAN_RNG_TXT_INFO_H        (130)
#define ATSC_ADV_SCAN_RNG_TXT_INFO_CNT_INSET_T        (10)
#define ATSC_ADV_SCAN_RNG_TXT_INFO_CNT_INSET_B        (10)
#define ATSC_ADV_SCAN_RNG_TXT_INFO_CNT_INSET_L        (30)
#define ATSC_ADV_SCAN_RNG_TXT_INFO_CNT_INSET_R        (30)
#define ATSC_ADV_SCAN_RNG_TXT_TUNER_X       (50)
#define ATSC_ADV_SCAN_RNG_TXT_TUNER_Y       (20)
#define ATSC_ADV_SCAN_RNG_TXT_TUNER_W       (476)
#define ATSC_ADV_SCAN_RNG_TXT_TUNER_H       (25)
#define ATSC_ADV_SCAN_RNG_TXT_TUNER_ALIGN   (WGL_AS_RIGHT_TOP)
#define ATSC_ADV_SCAN_RNG_PB_X              (50)
#define ATSC_ADV_SCAN_RNG_PB_H              (25)
#define ATSC_ADV_SCAN_RNG_PB_VAL_W          (80)
#define ATSC_ADV_SCAN_RNG_PB_CNT_INSET_T    (6)
#define ATSC_ADV_SCAN_RNG_PB_CNT_INSET_B    (6)
#define ATSC_ADV_SCAN_RNG_PB_BAR_INSET_L    (0)
#define ATSC_ADV_SCAN_RNG_PB_BAR_INSET_R    (0)
#define ATSC_ADV_SCAN_RNG_PB_BAR_INSET_T    (0)
#define ATSC_ADV_SCAN_RNG_PB_BAR_INSET_B    (0)

/* Time and Local setting */
#define ATSC_TIME_LOCAL_TXT_INFO_X          (10)
#define ATSC_TIME_LOCAL_TXT_INFO_Y          (5)
/*config menu orders*/
#define ATSC_TIME_LOCAL_SET_AUTOMATIC_TIME_IDX   (0)
#define ATSC_TIME_LOCAL_SET_TIME_ZONE_IDX   (1)
#define ATSC_TIME_LOCAL_SET_DLS_IDX         (2)

#define ATSC_TIME_LOCAL_SET_TIME_FORMAT_IDX (3)

#define ATSC_TIME_LOCAL_SET_POSTAL_CODE_IDX (4)
#ifdef  APP_ADD_COUNTRY_CODE_SUPPORT
#define ATSC_TIME_LOCAL_SET_CHG_COUNTRY_CODE_IDX (5)
#define ATSC_TIME_LOCAL_SET_COUNTRY_IDX     (6)
#endif

/* Advanced Scan Single Page */
#define ATSC_ADV_SCAN_SGL_TXT_INFO_X        (20)
#define ATSC_ADV_SCAN_SGL_TXT_INFO_Y        (10)
#define ATSC_ADV_SCAN_SGL_TXT_INFO_W        (536)
#define ATSC_ADV_SCAN_SGL_TXT_INFO_H        (130)
#define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_T        (10)
#define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_B        (10)
#define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_L        (30)
#define ATSC_ADV_SCAN_SGL_TXT_INFO_CNT_INSET_R        (30)
#define ATSC_ADV_SCAN_SGL_TXT_TUNER_X       (50)
#define ATSC_ADV_SCAN_SGL_TXT_TUNER_Y       (20)
#define ATSC_ADV_SCAN_SGL_TXT_TUNER_W       (476)
#define ATSC_ADV_SCAN_SGL_TXT_TUNER_H       (25)
#define ATSC_ADV_SCAN_SGL_TXT_TUNER_ALIGN   (WGL_AS_RIGHT_TOP)
#define ATSC_ADV_SCAN_SGL_PB_X              (50)
#define ATSC_ADV_SCAN_SGL_PB_Y              (105)
#define ATSC_ADV_SCAN_SGL_PB_W              (476)
#define ATSC_ADV_SCAN_SGL_PB_H              (25)
#define ATSC_ADV_SCAN_SGL_PB_VAL_W          (80)
#define ATSC_ADV_SCAN_SGL_PB_CNT_INSET_T    (6)
#define ATSC_ADV_SCAN_SGL_PB_CNT_INSET_B    (6)
#define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_L    (0)
#define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_R    (0)
#define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_T    (0)
#define ATSC_ADV_SCAN_SGL_PB_BAR_INSET_B    (0)
#define ATSC_ADV_SCAN_SGL_EB_CH_IDX         (6)
#define ATSC_ADV_SCAN_SGL_LB_PLN_IDX        (7)
#define ATSC_ADV_SCAN_SGL_LB_MOD_IDX        (8)
#define ATSC_ADV_SCAN_SGL_PB_SIG_IDX        (9)

/* Location Code Page */
#define LC_EB_ST_X              (8 * GRID_W)
#define LC_EB_ST_Y              (0 * GRID_H + (2 * R_H))
#define LC_EB_ST_W              (8 * GRID_W)
#define LC_EB_ST_H              (1 * GRID_H - (4 * R_H))

#define LC_EB_CT_X              (8 * GRID_W)
#define LC_EB_CT_Y              (1 * GRID_H + (2 * R_H))
#define LC_EB_CT_W              (8 * GRID_W)
#define LC_EB_CT_H              (1 * GRID_H - (4 * R_H))

#define LC_EB_INSET_L           (2 * R_W)
#define LC_EB_INSET_R           (2 * R_W)
#define LC_EB_INSET_T           (2 * R_H)
#define LC_EB_INSET_B           (2 * R_H)
#define LC_EB_CNT_INSET_L       0
#define LC_EB_CNT_INSET_R       0
#define LC_EB_CNT_INSET_T       0
#define LC_EB_CNT_INSET_B       0
#define LC_EB_ALIGN             WGL_AS_CENTER_CENTER
#define LC_EB_FONT              FE_FNT_SIZE_MEDIUM

/* Open VCHIP */
#define MENU_OP_VCHIP_X                 (0)
#define MENU_OP_VCHIP_Y                 (0)
#define MENU_OP_VCHIP_W                 ((CONTENT_W))
#define MENU_OP_VCHIP_H                 (9 * GRID_H)

/* Scan PB */
#define MENU_SCAN_PB_CNT_INSET_L   (10)
#define MENU_SCAN_PB_CNT_INSET_R   (35)
#define MENU_SCAN_PB_CNT_INSET_T   (17)
#define MENU_SCAN_PB_CNT_INSET_B   (16)
#define MENU_SCAN_PB_BAR_INSET_L   (0)
#define MENU_SCAN_PB_BAR_INSET_R   (0)
#define MENU_SCAN_PB_BAR_INSET_T   (0)
#define MENU_SCAN_PB_BAR_INSET_B   (0)

#define MENU_SCAN_PB_VAL_W         (200)
#define MENU_SCAN_RNG_PB_X         (0)
#define MENU_SCAN_RNG_PB_Y         (0+13)
#define MENU_SCAN_PB_TITLE_L       (60)
#define MENU_SCAN_PB_TITLE_R       (MENU_ITEM_V_WIDE - MENU_SCAN_PB_VAL_W - MENU_SCAN_PB_CNT_INSET_L)
#define MENU_SCAN_PB_TITLE_T       (0)
#define MENU_SCAN_PB_TITLE_B       (0)

#define MENU_MORE_ITEM_RIGHT_ARROW  (40)

#define ATSC_ADV_SCAN_RNG_PB_Y              (14*4/3)
#define ATSC_ADV_SCAN_RNG_PB_W              (MENU_SCAN_PB_VAL_W)
#define ATSC_ADV_SCAN_RNG_PROG_TXT_W_1      (51*4/3)
#define ATSC_ADV_SCAN_RNG_PROG_TXT_W_2      (82)
#define ATSC_ADV_SCAN_RNG_PROG_TXT_DIS      (8*4/3)

#define ATSC_ADV_SCAN_TXT_INFO_X            (10)
#define ATSC_ADV_SCAN_TXT_INFO_Y            (0)
#define ATSC_ADV_SCAN_RNG_LB_MODE_IDX       (0)
#define ATSC_ADV_SCAN_RNG_EB_FROM_IDX       (1)
#define ATSC_ADV_SCAN_RNG_EB_TO_IDX         (2)
#define ATSC_ADV_SCAN_RNG_BTN_IDX           (3)

#define HIDE_SPDIF_AUDIO_OUT_BITSTREAM          (1) /*remove DD, change bitstream to digital*/

#endif /* _menu_config_h */


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
 * $RCSfile: wzd_network.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/09 $
 * $Author: hs_nali $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_NETWORK_SUPPORT

#ifndef _WZD_PAGE_NW_SETUP_H_
#define _WZD_PAGE_NW_SETUP_H_
/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "c_wgl.h"
#include "u_net_wlan.h"
#include "app_util/a_network.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define UI4_TXT_INVALUED                 0xffffffff
#define WZD_NW_WLAN_TIMEOUT              (30000)   /* 30 s */

#define WZD_NW_WLAN_WPS_ASSOC_TIMEOUT    (120000) /* 120s */

#define WLAN_AP_LB_ELEM_NUM              (28)
#define WLAN_AP_LB_MAX_NUM               (56)

/* password max length */
#define WZD_NW_KEY_MAX_LEN               (64)
/* SSID max length */
#define WZD_NW_SSID_MAX_LEN              (32)
/* Edit box max length*/
#define WZD_NW_EB_TXT_MAX_LEN            (64)
/* Time zone max length */
#define WZD_NW_TIME_ZONE_MAX_LEN         (64)
/* First name max length */
#define WZD_NW_FIRST_NAME_MAX_LEN        (20)
/* Last name max length */
#define WZD_NW_LAST_NAME_MAX_LEN         (20)
/* Phone number max length */
#define WZD_NW_PHONE_NUM_MAX_LEN         (16)
/* Zip code max length */
#define WZD_NW_ZIP_CODE_MAX_LEN          (10)
/* Email max length */
#define WZD_NW_EMAIL_MAX_LEN             (35)
/* Timer step length */
#define WZD_NW_TIMER_ICON_STEP           (255)

/* Network frame size */
#define WZD_NW_FRAME_X					(LAYOUT_FRM_X)
#define WZD_NW_FRAME_Y					(0)
#define WZD_NW_FRAME_W            		(LAYOUT_FRM_W)
#define WZD_NW_FRAME_H               	(LAYOUT_FRM_H)

/* Info reg check box size */
#define WZD_NW_INFO_REG_CB_W             (80 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_H             (80 * WZD_UI_RATIO)

#define WZD_NW_INFO_REG_CB_ICON_LEFT_INSET        (12 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_ICON_TOP_INSET         (10 * WZD_UI_RATIO)

/*check box title*/
#define WZD_NW_INFO_REG_CB_TITLE_X                (400 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_TITLE_Y                (390 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_TITLE_W                (1000 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_TITLE_H                (50 * WZD_UI_RATIO)

/*check box title1*/
#define WZD_NW_INFO_REG_CB_TITLE1_X                (400 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_TITLE1_Y                (415 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_TITLE1_W                (1000 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_CB_TITLE1_H                (50 * WZD_UI_RATIO)

/* None connection page warning icon */
#define WZD_NW_NONE_CONN_WARNING_ICON_X	((WZD_NW_FRAME_W - WZD_NW_NONE_CONN_WARNING_ICON_W)/2)
#define WZD_NW_NONE_CONN_WARNING_ICON_Y	(120 * WZD_UI_RATIO_W)
#define WZD_NW_NONE_CONN_WARNING_ICON_W	(154 * WZD_UI_RATIO)
#define WZD_NW_NONE_CONN_WARNING_ICON_H	(98 * WZD_UI_RATIO)

/* None connection page title*/
#define WZD_NW_NONE_CONN_TITLE_X  		(0)
#define WZD_NW_NONE_CONN_TITLE_Y   		(WZD_NW_NONE_CONN_WARNING_ICON_Y + WZD_NW_NONE_CONN_WARNING_ICON_H + 10 * WZD_UI_RATIO)
#define WZD_NW_NONE_CONN_TITLE_W       	(WZD_NW_FRAME_W)
#define WZD_NW_NONE_CONN_TITLE_H       	(50 * WZD_UI_RATIO)

/* None connection page desc*/
#define WZD_NW_NONE_CONN_DESC_X			(0)
#define WZD_NW_NONE_CONN_DESC_Y			(WZD_NW_NONE_CONN_TITLE_Y + WZD_NW_NONE_CONN_TITLE_H)
#define WZD_NW_NONE_CONN_DESC_W			(WZD_NW_FRAME_W)
#define WZD_NW_NONE_CONN_DESC_H			(50 * WZD_UI_RATIO)

/* searching icon position */
#define WZD_NW_SEARCHING_ICON_X          ((LAYOUT_FRM_W - WZD_NW_SEARCHING_ICON_W)/2)
#define WZD_NW_SEARCHING_ICON_Y          (60 * WZD_UI_RATIO_W)
#define WZD_NW_SEARCHING_ICON_W          (44 * WZD_UI_RATIO_W)
#define WZD_NW_SEARCHING_ICON_H          (44 * WZD_UI_RATIO_W)

/* editbox position */
#define WZD_NW_EDIT_BOX_TITILE_X         (15 * WZD_UI_RATIO)
#define WZD_NW_EDIT_BOX_TITILE_Y         (0 * WZD_UI_RATIO)
#define WZD_NW_EDIT_BOX_TITILE_H         (43 * WZD_UI_RATIO)

#define WZD_NW_EDIT_BOX_TITILE_ICON_W    (20 * WZD_UI_RATIO)

#define WZD_NW_EDIT_BOX_TOP_INSET        (10 * WZD_UI_RATIO)
#define WZD_NW_EDIT_BOX_BOTTOM_INSET     (10 * WZD_UI_RATIO)

/* password input edit box position */
#define WZD_NW_PWD_EB_X                  ((LAYOUT_FRM_W - WZD_NW_PWD_EB_W)/2)// + 5 * WZD_UI_RATIO)
#define WZD_NW_PWD_EB_Y                  (10 * WZD_UI_RATIO)
#define WZD_NW_PWD_EB_W                  (703 * WZD_UI_RATIO)
#define WZD_NW_PWD_EB_H                  (125 * WZD_UI_RATIO)
#define WZD_NW_PWD_EB_LEFT_INSET         (0)//(20 * WZD_UI_RATIO)
#define WZD_NW_PWD_EB_RIGHT_INSET        (0)//(30 * WZD_UI_RATIO)

/* manual ssid edit box position */
#define WZD_NW_SSID_EB_X                 (WZD_NW_PWD_EB_X)
#define WZD_NW_SSID_EB_Y                 (WZD_NW_PWD_EB_Y)
#define WZD_NW_SSID_EB_W                 (WZD_NW_PWD_EB_W)
#define WZD_NW_SSID_EB_H                 (WZD_NW_PWD_EB_H)
#define WZD_NW_SSID_EB_LEFT_INSET        (WZD_NW_PWD_EB_LEFT_INSET)
#define WZD_NW_SSID_EB_RIGHT_INSET       (WZD_NW_PWD_EB_RIGHT_INSET)

/* Info Reg Edit box size */
#define WZD_NW_INFO_REG_EDIT_BOX_X    	 (0)
#define WZD_NW_INFO_REG_EDIT_BOX_W       (550 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_EDIT_BOX_H       (112 * WZD_UI_RATIO)

#define WZD_NW_INFO_REG_EB_LEFT_INSET	 (125 * WZD_UI_RATIO)
#define WZD_NW_INFO_REG_EB_RIGHT_INSET   (65 * WZD_UI_RATIO)

/* Email edit box */
#define WZD_NW_EMAIL_EB_GAP              (67 * WZD_UI_RATIO)

#define WZD_NW_EMAIL_EB_Y                (14 * WZD_UI_RATIO)
#define WZD_NW_FIRST_NAME_EB_Y           (WZD_NW_EMAIL_EB_Y + WZD_NW_EMAIL_EB_GAP)
#define WZD_NW_LAST_NAME_EB_Y            (WZD_NW_FIRST_NAME_EB_Y + WZD_NW_EMAIL_EB_GAP)
#define WZD_NW_PHONE_NUM_EB_Y            (WZD_NW_LAST_NAME_EB_Y + WZD_NW_EMAIL_EB_GAP)
#define WZD_NW_ZIP_CODE_EB_Y             (WZD_NW_PHONE_NUM_EB_Y + WZD_NW_EMAIL_EB_GAP)

/* Email accept checkbox */
#define WZD_NW_EMAIL_CB_X                (320 * WZD_UI_RATIO)
#define WZD_NW_EMAIL_CB_Y                (380 * WZD_UI_RATIO)


/* Edit box hightlight icon */
#define WZD_NW_EDIT_BOX_HL_ICON_W      	(8 * WZD_UI_RATIO)
#define WZD_NW_EDIT_BOX_HL_ICON_H      	(20 * WZD_UI_RATIO)

/* Infomation registe page next button */
#define WZD_NW_INFO_REG_NEXT_Y           (318 * WZD_UI_RATIO)

/* vkb position */
#define WZD_NW_VKB_FRAME_W				(770  * WZD_UI_RATIO)	/* VKB_MAIN_FRAME_W_PHA2 */

#define WZD_NW_PWD_VKB_FRAME_X			((LAYOUT_FRM_W - WZD_NW_VKB_FRAME_W)/2)
#define WZD_NW_PWD_VKB_FRAME_Y			(WZD_NW_PWD_EB_Y + WZD_NW_PWD_EB_H - 35 * WZD_UI_RATIO)

#define WZD_NW_SSID_VKB_FRAME_X			((LAYOUT_FRM_W - WZD_NW_VKB_FRAME_W)/2)
#define WZD_NW_SSID_VKB_FRAME_Y			(WZD_NW_SSID_EB_Y + WZD_NW_SSID_EB_H - 35 * WZD_UI_RATIO)

#define WZD_NW_INFO_VKB_FRAME_X         (425  * WZD_UI_RATIO)
#define WZD_NW_INFO_VKB_FRAME_Y         (0 * WZD_UI_RATIO)

/* vkb input title */
#define WZD_NW_VKB_TITLE_X     			 (20 * WZD_UI_RATIO)
#define WZD_NW_VKB_TITLE_Y     			 (0)
#define WZD_NW_VKB_TITLE_W     			 (345 * WZD_UI_RATIO)
#define WZD_NW_VKB_TITLE_H     			 (50 * WZD_UI_RATIO)

/**
 *  Terms of service and privacy policy page
 */
 
/* Terms of service button */
#define WZD_TERMS_BTN_X					(WZD_NW_FRAME_W/2 - WZD_TERMS_BTN_W/2)
#define WZD_TERMS_BTN_Y                	(100 * WZD_UI_RATIO_W)
#define WZD_TERMS_BTN_W                	(270 * WZD_UI_RATIO_W)
#define WZD_TERMS_BTN_H                	(78 * WZD_UI_RATIO_W)

/* Privacy policy button */
#define WZD_POLICY_BTN_X				(WZD_TERMS_BTN_X)
#define WZD_POLICY_BTN_Y            	(220 * WZD_UI_RATIO_W)
#define WZD_POLICY_BTN_W            	(WZD_TERMS_BTN_W)
#define WZD_POLICY_BTN_H              	(WZD_TERMS_BTN_H)

/* text content */
#define WZD_NW_TXT_CNT_MARGINS			(100 * WZD_UI_RATIO)

#define WZD_NW_TXT_CNT_X				(WZD_NW_TXT_CNT_MARGINS)
#define WZD_NW_TXT_CNT_Y				(50 * WZD_UI_RATIO_W)
#define WZD_NW_TXT_CNT_W				(WZD_NW_FRAME_W - 2 * WZD_NW_TXT_CNT_MARGINS - WZD_NW_TEXT_ICON_FRM_W)
#define WZD_NW_TXT_CNT_H				(375 * WZD_UI_RATIO)

#define WZD_NW_LEFT_INSET           	(5 * WZD_UI_RATIO)
#define WZD_NW_RIGHT_INSET              (5 * WZD_UI_RATIO)

/* icon frame */
#define WZD_NW_TEXT_ICON_FRM_X  		(WZD_NW_TXT_CNT_X + WZD_NW_TXT_CNT_W)
#define WZD_NW_TEXT_ICON_FRM_Y  		(WZD_NW_TXT_CNT_Y + 10 * WZD_UI_RATIO)
#define WZD_NW_TEXT_ICON_FRM_W  		(WZD_NW_TEXT_ICON_W)
#define WZD_NW_TEXT_ICON_FRM_H          (WZD_NW_TEXT_ICON_H * 2)

#define WZD_NW_TEXT_ICON_W  			(91 * WZD_UI_RATIO)
#define WZD_NW_TEXT_ICON_H              (98 * WZD_UI_RATIO)

/* WLAN MAC address layout */
#define WZD_NW_MAC_ADDR_X                  (LAYOUT_FRM_W - WZD_NW_MAC_ADDR_W - 50 * WZD_UI_RATIO)
#define WZD_NW_MAC_ADDR_Y                  (LAYOUT_FRM_H - WZD_NW_MAC_ADDR_H)
#define WZD_NW_MAC_ADDR_W                  (260 * WZD_UI_RATIO)
#define WZD_NW_MAC_ADDR_H                  (100 * WZD_UI_RATIO)

/*for merge json string*/
#define WZD_NW_SN_JSON_KEY                           "'SN':'"
#define WZD_NW_MAC_JSON_KEY                          "RD01,{'MA':'"
#define WZD_NW_VN_JSON_KEY                           "'VN':'"
#define WZD_NW_DT_JSON_KEY                           "'DT':'"

#define WZD_NW_EMAIL_JSON_KEY                        "'EM':'"
#define WZD_NW_FIRST_NAME_JSON_KEY                   "'FN':'"
#define WZD_NW_LAST_NAME_JSON_KEY                    "'LN':'"
#define WZD_NW_PHONE_NUM_JSON_KEY                    "'PH':'"
#define WZD_NW_ZIP_CODE_JSON_KEY                     "'ZC':'"
#define WZD_NW_OFFER_CONTACT_JSON_KEY                "'OC':'"

#define WZD_NW_REG_INFO_GROUP_NUM                  (1)
#define WZD_NW_REG_INFO_JSON_TXT_MAX_LEN           (WZD_NW_EB_TXT_MAX_LEN*4/3 + 4)
#define WZD_NW_REG_INFO_JSON_TXT_GROUP_MAX_LEN     (1024)
#define WZD_NW_REG_INFO_SN_LEN                     (32)
#define WZD_NW_REG_INFO_SN_JSON_LEN                (WZD_NW_REG_INFO_SN_LEN*4/3 + 4)
#define WZD_NW_REG_INFO_MAC_LEN                    (20)
#define WZD_NW_REG_INFO_MAC_JSON_LEN               (WZD_NW_REG_INFO_MAC_LEN*4/3 + 4)
#define WZD_NW_REG_INFO_VN_LEN                     (32)
#define WZD_NW_REG_INFO_VN_JSON_LEN                (WZD_NW_REG_INFO_VN_LEN*4/3 + 4)
#define WZD_NW_REG_INFO_DT_LEN                     (32)
#define WZD_NW_REG_INFO_DT_JSON_LEN                (WZD_NW_REG_INFO_DT_LEN*4/3 + 4)

/*for reg info data verification*/
#define WZD_NW_REG_INFO_AT     		                "@"
#define WZD_NW_REG_INFO_DOT     		            "."
#define WZD_NW_REG_INFO_NAME_MIN_LEN                (2)
#define WZD_NW_REG_INFO_PHONE_NUM_MIN_LEN           (10)
#define WZD_NW_REG_INFO_PHONE_NUM_MAX_LEN           (16)
#define WZD_NW_REG_INFO_ZIP_CODE_MIN_LEN            (5)
#define WZD_NW_REG_INFO_ZIP_CODE_MAX_LEN            (10)

typedef struct _WZD_NW_TEXT_T
{
    HANDLE_T    h_widget;
    UINT16      ui2_msg_idx;

    HANDLE_T    h_text_widget;
    HANDLE_T    h_text;

    HANDLE_T    h_icon_frm;
    HANDLE_T    h_icon_up;
    HANDLE_T    h_icon_down;
}WZD_NW_TEXT_T;

typedef struct _WZD_NW_SUBPAGE_T
{
	HANDLE_T    h_widget;
	UINT16      ui2_msg_idx;
}WZD_NW_SUBPAGE_T;

typedef enum _WZD_NW_TIMER_E
{
	WZD_NW_TIMER_LAN_ASSOC = 0,
	WZD_NW_TIMER_WIFI_SCAN,
	WZD_NW_TIMER_WIFI_SSID_SCAN,
	WZD_NW_TIMER_WIFI_ASSOC,
	WZD_NW_TIMER_WIFI_PWD_ASSOC,
	WZD_NW_TIMER_TEST_CONN,
	WZD_NW_TIMER_WIFI_WPS_ASSOC,
	WZD_NW_TIMER_END
}WZD_NW_TIMER_E;

typedef enum _NW_SETUP_STATE
{
	NW_SETUP_STATE_BEGIN = 0,
	NW_SETUP_STATE_NONE_CONN,   
	NW_SETUP_STATE_WIRELESS_SCANNING,
	NW_SETUP_STATE_WIRELESS_SCAN_RESULT,
	NW_SETUP_STATE_WIRELESS_PWD_INPUT,
	NW_SETUP_STATE_WIRELESS_SSID_INPUT,
	NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT,
	NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE,
	NW_SETUP_STATE_PROTOCOL,
	NW_SETUP_STATE_INFO_REG,
	NW_SETUP_STATE_COMPLETE
}NW_SETUP_STATE;

typedef enum _WZD_NW_INFO_REG_FOCUS_E
{ 
	WZD_NW_REG_INFO_MAIL = 0,
	WZD_NW_REG_INFO_FIRST_NAME,
	WZD_NW_REG_INFO_LAST_NAME,
	WZD_NW_REG_INFO_PHONE_NUM,
	WZD_NW_REG_INFO_ZIP_CODE,
	WZD_NW_REG_INFO_LAST_ENTRY
}WZD_NW_INFO_REG_FOCUS_E;

typedef enum _WZD_NW_PROTOCOL_SCAN_E
{
	WZD_NW_PROTOCOL_SCAN_NULL = 0,
    WZD_NW_PROTOCOL_SCAN_TERMS,
    WZD_NW_PROTOCOL_SCAN_POLICY
}WZD_NW_PROTOCOL_SCAN_E;

typedef enum _WZD_NW_VKB_STYLE_E
{
	WZD_NW_VKB_INFO_REG = 0,
	WZD_NW_VKB_MANU_SSID,
	WZD_NW_VKB_PWD_INPUT,
	WZD_NW_VKB_LAST_ENTRY
}WZD_NW_VKB_STYLE_E;

typedef struct _WZD_NW_PROTOCOL_T
{
    HANDLE_T           h_protocol_frame;
	HANDLE_T           h_timer;
	UINT8              ui1_circle_step;
	CHAR               s_file_path[128];
#ifdef APP_DYNAMIC_TOS_SUPPORT
    UINT16             ui2_tos_nfy_id;
    BOOL               b_is_file_opened;    /* download file is be opened successfully*/
    HANDLE_T           h_error_text;        /* show error tips */
#endif
    WZD_NW_TEXT_T      t_protocol_terms;
    WZD_NW_TEXT_T      t_protocol_policy;

    UINT32             ui4_pro_total_page;
    UINT32             ui4_pro_cur_page;
    UINT32             ui4_pro_total_rows;
    UINT32             ui4_pro_cur_rows;
    UINT32             ui4_pre_page_rows;

	WZD_NW_PROTOCOL_SCAN_E e_scan_text;
}WZD_NW_PROTOCOL_T;


typedef struct _WZD_NW_EB_T
{
    HANDLE_T           h_eb_frm;        /* editbox frame */
	HANDLE_T           h_eb;            /* editbox */
	HANDLE_T           h_eb_focus;      /* editbox focus icon */
	HANDLE_T           h_eb_clr;        /* editbox clear all icon */
}WZD_NW_EB_T;

typedef struct _WZD_NW_NONE_CONN_T
{
    HANDLE_T           h_none_conn_frame;
    HANDLE_T           h_warning_icon;
    WZD_NW_TEXT_T      t_title;
    WZD_NW_TEXT_T      t_desc_txt;
}WZD_NW_NONE_CONN_T;

typedef struct _WZD_NW_CHOICE_CONNECT_T
{
    HANDLE_T                h_choice_connect_frame;

    UINT8                   ui1_icon_step;
    HANDLE_T                h_timer;
    UINT32                  ui4_wzd_nw_nfy_id;
    UINT32                  ui4_wzd_nw_tag;
    BOOL                    b_is_wlan_ind;
    BOOL                    b_associate_complete;
    BOOL                    b_is_ssid_matched;
    UINT8                   aui1_ap_map[WLAN_AP_LB_MAX_NUM];
	
    NET_802_11_ESS_LIST_T   t_essList;
    NET_802_11_ASSOCIATE_T  t_associate;
	UINT8					ui1_visiable_ap_num;

	BOOL					b_connected;
}WZD_NW_CHOICE_CONNECT_T;

typedef struct _WZD_NW_CONNECT_T
{
    HANDLE_T                h_conn_frm;
    WZD_NW_TEXT_T           t_title;
    WZD_NW_SUBPAGE_T        t_next;
    WZD_NW_TEXT_T           t_wired_help;
    WZD_NW_SUBPAGE_T        t_conn_wired;
}WZD_NW_CONNECT_T;

typedef struct _WZD_NW_INFO_REGISTER_T
{
    HANDLE_T                h_info_reg_frm;
    WZD_NW_TEXT_T           t_title;
    WZD_NW_SUBPAGE_T        t_next;
    HANDLE_T                ah_editbox[WZD_NW_REG_INFO_LAST_ENTRY];
    UTF16_T                 aw2s_editbox_context[WZD_NW_REG_INFO_LAST_ENTRY][WZD_NW_EB_TXT_MAX_LEN];
	HANDLE_T           		h_mail_accept_checkbox;
	HANDLE_T        		h_mail_accept_checkbox_title;
	HANDLE_T        		h_mail_accept_checkbox_title1;
    BOOL                    b_is_vkb_show;
    WZD_NW_INFO_REG_FOCUS_E e_current_item;
    HANDLE_T                h_eb_hl_icon;
    HANDLE_T    			h_reg_eb_prompt_text[WZD_NW_REG_INFO_LAST_ENTRY];		/* float prompt text for reg edit box*/
    BOOL                    b_warning_dlg_is_show[WZD_NW_REG_INFO_LAST_ENTRY];		/* the warning dialog is display only once */
}WZD_NW_INFO_REGISTER_T;

typedef struct _WZD_NW_VKB_T
{
    HANDLE_T                h_vkb_pwd;
	HANDLE_T                h_vkb_ssid;
	HANDLE_T                h_vkb_info;
	WZD_NW_TEXT_T           t_title;
    WZD_NW_VKB_STYLE_E      e_vkb_style;
    BOOL                    b_vkb_show;
}WZD_NW_VKB_T;

typedef struct _WZD_NW_MANU_SSID_T
{
    HANDLE_T                h_manu_ssid_frm;
    HANDLE_T                h_eb_ssid;
    HANDLE_T                h_eb_key;
    HANDLE_T                h_btn_ok;
    HANDLE_T                h_current_focus;
}WZD_NW_MANU_SSID_T;

typedef struct _WZD_NW_T
{
    HANDLE_T                h_frame;
    HANDLE_T                h_timer_icon;
    WZD_NW_VKB_T            t_vkb;
    WZD_NW_PROTOCOL_T       t_protocol;
    WZD_NW_NONE_CONN_T      t_none_conn;
    WZD_NW_CHOICE_CONNECT_T t_choice_connect;
    WZD_NW_INFO_REGISTER_T  t_info_reg;
    WZD_NW_MANU_SSID_T      t_manu_ssid;
    UINT32                  ui4_start_time;
    BOOL                    b_is_busying;
    UINT16                  ui2_lang_id;
    WZD_NW_TIMER_E          e_wzd_nw_timer;
    BOOL                    b_timer_result;
	UINT8                   ui1_icon_step;

	HANDLE_T                h_dlg;              /* Message box */
	HANDLE_T                h_last_focused_wdg;

	BOOL                    b_need_show_prompt_text;
	HANDLE_T    			h_prompt_text;		/* float prompt text */
	WZD_NW_EB_T				t_eb_pwd;
	WZD_NW_EB_T				t_eb_ssid;
	UTF16_T                 aw2s_ssid_context[WZD_NW_EB_TXT_MAX_LEN];
    UTF16_T                 aw2s_key_context[WZD_NW_EB_TXT_MAX_LEN+1];
	CHAR                    s_ssid_buf[WZD_NW_SSID_MAX_LEN];
    CHAR                    s_pwd_buf[WZD_NW_KEY_MAX_LEN+1];

	HANDLE_T    			h_mac_addr;			/* WLAN MAC address */

}WZD_NW_T;

typedef struct _WZD_NW_NFY_DATA_T
{
    VOID*                   pv_tag;
    NW_NFY_ID_T             e_nfy_id;
    VOID*                   pv_nfy_param;
}WZD_NW_NFY_DATA_T;

typedef enum _WZD_NW_SUBPAGE_BTN_TYPE_T
{
    WZD_NW_SUBPAGE_BTN_TYPE_WPS_ASSOCIATE = 0,
    WZD_NW_SUBPAGE_BTN_TYPE_HIDDEN_SSID_ASSOCIATE,
    WZD_NW_SUBPAGE_BTN_TYPE_CONNECT_WIRED,
    WZD_NW_SUBPAGE_BTN_TYPE_OTHERS
}WZD_NW_SUBPAGE_BTN_TYPE_T;

/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
extern INT32 wzd_page_nw_setup_get_page_info_data(
                WZD_PAGE_INFO_DATA_T*   pt_info_data);

extern INT32 wzd_page_nw_setup_nfy_sel(
                UINT16                  ui2_sel_idx,
                VOID*                   pv_data,
                WZD_MSG_CUSTOM_T*       pt_ret_msg);
extern INT32 c_base64_encode(const VOID *pv_in_data, INT32 i4_pv_in_data_size, VOID *pac_out_data, INT32 i4_pac_out_data_size);
extern CHAR* sys_cust_get_usb_upg_version(VOID);
extern BOOL a_dst_get_local_time(DTG_T* pt_loc_dtg);
#endif /* _WZD_PAGE_NW_SETUP_H_ */
#endif /* APP_NETWORK_SUPPORT */

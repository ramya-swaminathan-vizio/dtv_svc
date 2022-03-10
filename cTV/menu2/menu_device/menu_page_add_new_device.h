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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
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
#ifndef _MENU_PAGE_ADD_NEW_DEVICE_H_
#define _MENU_PAGE_ADD_NEW_DEVICE_H_

/*-----------------------------------------------------------------------------
                     include files
 -----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    custmizable macros
 ----------------------------------------------------------------------------*/
#ifndef ENABLE_DEBUG_LOG
#define ENABLE_DEBUG_LOG
#endif

#define LIST_ITEM_DEVICE_TYPE_IDX               (0)
#define LIST_ITEM_DEVICE_TYPE_AUD_IDX           (1)
#define LIST_ITEM_INPUT_SRC_IDX                 (2)
#define LIST_ITEM_DEVICE_BRAND_IDX     (3)
#define LIST_ITEM_DEVICE_MODEL_IDX     (4)
#define LIST_ITEM_CONFIRM_REMOTE_CONNECT_IDX    (5)

#define DEVICE_TYPE_UNKNOWN            (0xFFFF)

#define DEVICE_TYPE_MAX                (10)
#define DEVICE_TYPE_AUD_MAX            (2)
#define DEVICE_LIST_ITEM_NUM           (5)

#define MENU_ADD_NEW_DEVICE_INPUT_MAX_LEN               (32)

#define INPUT_LST_VISIBLE_ELEM             (12)
#define INPUT_LST_X                        (0 * GRID_W)
#define INPUT_LST_Y                        (0 * GRID_H)
#define INPUT_LST_W                        (CONTENT_W)
#define INPUT_LST_H                        (INPUT_LST_VISIBLE_ELEM * GRID_H)
#define MAX_REC                            (16)

/*select brand frame */
#define MENU_ADD_NEW_DEVICE_BRD_FRM_X               (0)
#define MENU_ADD_NEW_DEVICE_BRD_FRM_Y               (43)
#define MENU_ADD_NEW_DEVICE_BRD_FRM_W               (400)
#define MENU_ADD_NEW_DEVICE_BRD_FRM_H               (80)

#define MENU_ADD_NEW_DEVICE_TXT_01_W            (130)
#define MENU_ADD_NEW_DEVICE_TXT_02_W            (200)
#define MENU_ADD_NEW_DEVICE_TXT_01_X            (9)

#define MENU_ADD_NEW_DEVICE_EB_LEFT_INSET      (15)
#define MENU_ADD_NEW_DEVICE_EB_RIGHT_INSET     (15)
#define MENU_ADD_NEW_DEVICE_EB_TOP_INSET        (5)
#define MENU_ADD_NEW_DEVICE_EB_BOTTOM_INSET     (5)

#define MENU_ADD_NEW_DEVICE_EB_TITILE_X         (15)
#define MENU_ADD_NEW_DEVICE_EB_TITILE_Y         (0)
#define MENU_ADD_NEW_DEVICE_EB_TITILE_H         (43)

/* Add New Device Edit box size */
#define MENU_ADD_NEW_DEVICE_EB_X                (0)
#define MENU_ADD_NEW_DEVICE_EB_W                (400)
#define MENU_ADD_NEW_DEVICE_EB_H                (44)

#define MENU_ADD_NEW_DEVICE_EB_TXT_MAX_LEN      (32)
#define MENU_ADD_NEW_DEVICE_LB_TEXT_LENGTH      (50)

#define MENU_ADD_NEW_DEVICE_LB_CNT_INSET_L      (1)
#define MENU_ADD_NEW_DEVICE_LB_CNT_INSET_R      (1)
#define MENU_ADD_NEW_DEVICE_LB_CNT_INSET_T      (1)
#define MENU_ADD_NEW_DEVICE_LB_CNT_INSET_B      (1)

#define MENU_ADD_NEW_DEVICE_LB_ELE_INSET_L      (5)
#define MENU_ADD_NEW_DEVICE_LB_ELE_INSET_R      (5)
#define MENU_ADD_NEW_DEVICE_LB_ELE_INSET_T      (5)
#define MENU_ADD_NEW_DEVICE_LB_ELE_INSET_B      (5)

#define MENU_ADD_NEW_DEVICE_BRAND_IDS_MAX_NUM                   (255)
#define MENU_ADD_NEW_DEVICE_SETUP_INPUT_SRC_NUM                 (16)
#define MENU_ADD_NEW_DEVICE_CODESET_MAX_NUM                     (60)

#define MENU_ADD_NEW_DEVICE_PIC_FLAG                    ("%p")

#define MENU_ADD_NEW_DEVICE_OFFSET_X   (-50*4/3)

#define MENU_ADD_NEW_DEVICE_DEL_ICON_W              (77)
#define MENU_ADD_NEW_DEVICE_DEL_ICON_H              (61)

#define MENU_ADD_NEW_DEVICE_DIALOG_DELAY                        (5000)

#define DEV_SETUP_DB_NAME_LEN_MAX                   (32)

#define MENU_SETUP_CODESET_SUPPORT_MAX          (2)
#define DEV_SETUP_DB_CODESET_LEN_MAX               (5)

#define MENU_SETUP_VCR_IDX                    (7)
#define MENU_SETUP_AVR_AMP_IDX                (8)
#define MENU_SETUP_SOUND_BAR_IDX              (9)

/*For warning dlg*/
#define	  	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_X		((SCREEN_W - MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_W)/2)
#define  	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_Y		((SCREEN_H - MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_H)/2)
#define   	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_W		(396)
#define   	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_H		(MENU_ITEM_V_HEIGHT*3)

#define 	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_X       (0)
#define 	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_Y       (MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_H)
#define 	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_W       (MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_W)
#define 	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_TITLE_H       (MENU_ITEM_V_HEIGHT*2-MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_H)

#define		MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_X			((MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_W - MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_W)/2)
#define		MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_Y			(MENU_ITEM_V_HEIGHT*2)
#define		MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_W			(MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_W / 2 - 18)
#define		MENU_ADD_NEW_DEVICE_WARNING_DIALOG_OK_H			(MENU_ITEM_V_HEIGHT)

#define 	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_X        (0)
#define 	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_Y        (0)
#define		MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_W        (MENU_ADD_NEW_DEVICE_WARNING_DIALOG_FRAM_W)
#define 	MENU_ADD_NEW_DEVICE_WARNING_DIALOG_ICON_H        (36)

/*For manually enter code dlg*/
#define	  	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_X		((SCREEN_W - MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_W)/2)
#define  	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_Y		((SCREEN_H - MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_H)/2)
#define   	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_W		(396)
#define   	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_H		(MENU_ITEM_V_HEIGHT*4)

#define 	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_X       (0)
#define 	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_Y       (MENU_ITEM_V_HEIGHT/2-5)
#define 	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_W       (MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_W)
#define 	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_TITLE_H       (MENU_ITEM_V_HEIGHT)

#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_X			((MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_W - 2*MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_W)/3)
#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_Y			(MENU_ITEM_V_HEIGHT*3-10)
#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_W			(MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_W / 3)
#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_H			(MENU_ITEM_V_HEIGHT)

#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_X			(2*MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_X+MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_YES_W)
#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_Y			(MENU_ITEM_V_HEIGHT*3-10)
#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_W			(MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_FRAM_W / 3)
#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_NO_H			(MENU_ITEM_V_HEIGHT)

#define 	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_X        (150)
#define 	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_Y        (MENU_ITEM_V_HEIGHT*2-20)
#define		MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_W        (100)
#define 	MENU_ADD_NEW_DEVICE_MANUAL_DIALOG_EDITBOX_H        (44)

typedef enum _ADD_NEW_DEVICE_PAGE_SUBPAGE_T
{
    ADD_NEW_DEVICE_PAGE_SUBPAGE_MAIN = 0,
    ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE,
    ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_TYPE_AUD,
    ADD_NEW_DEVICE_PAGE_SUBPAGE_INPUT_LIST,
    ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_BRAND,
    ADD_NEW_DEVICE_PAGE_SUBPAGE_DEVICE_MODEL,
    ADD_NEW_DEVICE_PAGE_SUBPAGE_CONFIRM_REMOTE_CONNECT,
}ADD_NEW_DEVICE_PAGE_SUBPAGE_T;

typedef enum _ADD_NEW_DEVICE_PAGE_ENTER_FROM_T
{
    ADD_NEW_DEVICE_PAGE_ENTERN_FROM_NORMAL = 0,
    ADD_NEW_DEVICE_PAGE_ENTERN_FROM_AUDIO_MODE_SETUP
}ADD_NEW_DEVICE_PAGE_ENTER_FROM_T;

typedef VOID (*add_dev_dlg_cb_fct)(UINT32 ui4_key_code);

extern INT32 menu_device_page_add_new_device_enter_from_set(ADD_NEW_DEVICE_PAGE_ENTER_FROM_T  e_enter_from);
extern INT32 menu_device_page_add_new_device_enter_from_get(ADD_NEW_DEVICE_PAGE_ENTER_FROM_T*  pe_enter_from);
extern INT32 menu_add_new_device_power_off_warning_dlg_show(VOID);
#endif /* _MENU_PAGE_PAIR_WIFI_DEVICE_H_ */



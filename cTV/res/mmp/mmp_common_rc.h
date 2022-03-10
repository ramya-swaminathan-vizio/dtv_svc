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
 * $RCSfile: mmp_common_rc.h,v $
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

#ifndef _MMP_COMMON_RC_H_
#define _MMP_COMMON_RC_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_sys_name.h"
#include "res/menu2/menu_config.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/*-----General Setting-----*/
#define MMP_RC_PATH_MAX_LEN                 ((UINT32) 400)      /*byte. include the null character*/
#define MMP_RC_MAX_EXT_LEN                  (5)
#define MMP_RC_FOLDER_TOKEN                 ((CHAR)'/')
#define MMP_RC_MAX_FOLDER_DEPTH             ((UINT32) 23)       /*36 + 3 = 39, 4 is for /mnt/usb/MassXXX/ */
#define MMP_DEV_LIST_MAX_NUM                ((INT32)32)/* USB device can support 16,
                                                                                                               DLNA can support 256,
                                                                                                               My network places can support? */
#define MMP_DEV_NAME_MAX_LEN                ((INT32)128)

#ifdef SUPPORT_ONLY_ONE_USB_PORT
#define MMP_DEV_LIST_USB_DEV_PREFIX         ("USB:")
#else
#define MMP_DEV_LIST_USB_DEV_PREFIX         ("USB%d:")
#endif
#define MMP_DEV_LIST_DLNA_DEV_PREFIX        ("DLNA%d:")

/* progress bar min size */
#define MMP_RC_MIN_PG_BAR_SIZE              ((UINT16) 3)
/*-----Browser ID-----*/
#define MMP_RC_BROWSER_ID_THUMBNAIL         ((UINT8) 0)
#define MMP_RC_BROWSER_ID_LIST              ((UINT8) 1)
#define MMP_RC_BROWSER_ID_PHOTO_FRM         ((UINT8) 2)
#ifndef APP_CAST_TV_MMP_FG
#define MMP_RC_BROWSER_ID_DMR               ((UINT8) 3)
#else
#define MMP_RC_BROWSER_ID_FOREGROUND        ((UINT8) 3)
#define MMP_RC_BROWSER_ID_DMR               ((UINT8) 4)
#endif


/*-----DLNA feature-----*/
#ifdef APP_NETWORK_SUPPORT
#define MMP_RC_DLNA_UI_ENABLE         ((UINT8) 1)
#define MMP_RC_DLNA_FOLDER_UI_ENABLE         ((UINT8) 1)
#endif
/*-----Browser Config-----*/
#if 1
#define MMP_FB_RC_ENABLE_LIST_MODE
#endif

#define MMP_TIMER_PARSE_FOLDER_DELAY           ((UINT32) 1000)

#define MMP_TIMER_FILE_PREVIEW_DELAY           ((UINT32) 0)

#define MMP_TIMER_CB_CHECK_DELAY               ((UINT32) 5000)

/*Authoring tool config*/
#define MMP_GUI_AUTHORING
#define MMP_GUI_AUTHORING_DP

#define MMP_TEXT_FILE_SUPPORT

#define MMP_COM_UI_HEADER_FILE "mmp/common_ui2/mmp_common_ui.h"
#define MMP_MLM_HEADER_FILE "res/mmp/gen/mmp_mlm.h"

/*-----File Extension-----*/
extern const CHAR as_g_audio_ext [][MMP_RC_MAX_EXT_LEN];
extern const CHAR as_g_audio_lst_ext [][MMP_RC_MAX_EXT_LEN];
extern const CHAR as_g_audio_network_only_ext [][MMP_RC_MAX_EXT_LEN];
extern const CHAR as_g_video_ext [][MMP_RC_MAX_EXT_LEN];
extern const CHAR as_g_video_3d_ext [][MMP_RC_MAX_EXT_LEN];
extern const CHAR as_g_image_ext [][MMP_RC_MAX_EXT_LEN];
extern const CHAR as_g_text_ext  [][MMP_RC_MAX_EXT_LEN];

#ifdef APP_IPCC_SUPPORT
extern const CHAR* as_g_video_expt[];
extern const INT16 ui2_g_video_expt_cnt;
#endif

extern const UINT16 ui2_g_audio_ext_count;
extern const UINT16 ui2_g_audio_lst_ext_count;
extern const UINT16 ui2_g_audio_network_only_ext_count;
extern const UINT16 ui2_g_video_ext_count;
extern const UINT16 ui2_g_video_3d_ext_count;
extern const UINT16 ui2_g_image_ext_count;
extern const UINT16 ui2_g_text_ext_count;

/*-----Resource Name-----*/
#define MMP_RC_DISPLAY_NAME                 SN_PRES_MAIN_DISPLAY
/*-----Customization Message ID-----*/
#define MMP_MSG_ID_CUST_SORT_CFG_XNG                  (MMP_MSG_ID_CUSTOM_START + 1)       /*pv_msg_param:*/
#define MMP_MSG_ID_CUST_APPLY_SORT_CFG                (MMP_MSG_ID_CUSTOM_START + 2)       /*pv_msg_param:*/

#define MMP_MSG_ID_CUST_THUMB_SIZE_CFG_XNG            (MMP_MSG_ID_CUSTOM_START + 3)       /*pv_msg_param:*/
#define MMP_MSG_ID_CUST_APPLY_THUMB_SIZE_CFG          (MMP_MSG_ID_CUSTOM_START + 4)       /*pv_msg_param:*/

#define MMP_MSG_ID_BK_PLAYER_STATUS_XNG               (MMP_MSG_ID_CUSTOM_START + 5)
#define MMP_MSG_ID_AUDIO_PLAYED                       (MMP_MSG_ID_CUSTOM_START + 6)
#define MMP_MSG_ID_VEDIO_FILE_NOT_SUPPORT             (MMP_MSG_ID_CUSTOM_START + 7)
#define MMP_MSG_ID_CUSTOM_SET_CRNT_PLAY_MODE          (MMP_MSG_ID_CUSTOM_START + 8)
#define MMP_MSG_ID_CUSTOM_PLAY_NEXT                   (MMP_MSG_ID_CUSTOM_START + 9)


/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
  /**
 * @brief info which will be used when switch browser
 */
typedef struct _MMP_MC_RC_SWITCH_BROWSER_INFO_T
{
    UINT32                          ui4_cur_focus_idx;      /* Focus item in current browser */
} MMP_MC_RC_SWITCH_BROWSER_INFO_T;

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
 extern INT32 mmp_mc_rc_switch_browser(
    UINT8   ui1_browser_id,
    VOID*  pv_info);

#endif /*_MMP_COMMON_RC_H_*/

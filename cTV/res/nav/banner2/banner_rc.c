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
 * $RCSfile: banner.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: min.li $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <sys/time.h>

#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_rm.h"

#include "res/nav/nav_img.h"
#include "res/nav/nav_mlm.h"

#include "res/nav/banner2/gen/nav_banner2_view_rc_layout.h"
#include "res/nav/banner2/gen/nav_banner2_gen_img.h"
#include "res/gen/a_font_gen_custom.h"
#include "res/nav/banner2/yahoo_osd/a_yahoo_osd.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/dst/a_dst_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"

#include "am/a_am.h"
#include "menu2/a_menu.h"
#include "nav/banner2/a_banner.h"
#include "nav/banner2/banner.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "app_util/a_tv.h"
#include "mmp/a_mmp.h"

#include "nav/input_src/input_src_list.h"
#include "res/nav/nav_img_rc.h"
#include "nav/input_src/a_input_src.h"
#include "res/menu2/a_menu_custom.h"
#include "menu2/menu_common/menu_common.h"

#include "wfd/wfd.h"

#include "res/app_util/config/acfg_custom.h"
#include "wizard_anim/a_wzd.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "nav/usb_pld/nav_usb_pld_view.h"
#include "nav/link_mode/link_mode.h"
#include "nav/long_press/long_press.h"
#include "res/menu2/menu_custom.h"
#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#ifdef APP_ZOOM_MODE_SUPPORT
#include "res/nav/zoom/nav_zoom_custom.h"
#endif

#include "res/nav/nav_dbg.h"

#ifdef LINUX_TURNKEY_SOLUTION
#include "msgconvert/a_msgconvert.h"
#endif



/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define SET_TO_FINAL_WHEN_ENTER                 TRUE
#define LOCK_WHEN_ENTER                         TRUE
#define BANNER_INVALID_LAST_UPDATED_TIME        (0xffffffff)

#define BANNER_PROG_DETAIL_GOTO_FIRST_PAGE      (1)
#define BANNER_PROG_DETAIL_GOTO_PREV_PAGE       (2)
#define BANNER_PROG_DETAIL_GOTO_NEXT_PAGE       (3)
#define BANNER_PROG_DETAIL_GOTO_THIS_PAGE       (4)

/** state priority **/
#define BANNER_STATE_PRI_IDLE                   (UINT8)0
#define BANNER_STATE_PRI_NONE                   (UINT8)0
#define BANNER_STATE_PRI_INPTTING               (UINT8)40
#define BANNER_STATE_PRI_IPTS                   (UINT8)50
#define BANNER_STATE_PRI_EMPTY_SVL              (UINT8)55
#define BANNER_STATE_PRI_CHANGING               (UINT8)60
#define BANNER_STATE_PRI_NO_SIG                 (UINT8)70
#define BANNER_STATE_PRI_SHOW_MSG               (UINT8)75
#define BANNER_STATE_PRI_HIDDEN_CH              (UINT8)80

#define BANNER_STATE_PRI_RETRIEVE               (UINT8)90
#define BANNER_STATE_PRI_TV                     BANNER_STATE_PRI_TV_DEFAULT

/* banenr state item includs */
#define BANNER_STATE_ITEM_INCLUDS_NONE          (BNR_ITEM_SET_T)0

#if (CUSTOMER == VIZIO)
  #define BANNER_ITM_HEADPHONES_ID  NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_HEADPHONES)
#else
  #define BANNER_ITM_HEADPHONES_ID  0
#endif

#define BANNER_STATE_ITEM_INCLUDS_CH            (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO  )        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RESOLUTION_TXT) |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION_ICON)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_OUT)      |   \
                                                 BANNER_ITM_HEADPHONES_ID                           |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON) ) 


#define BANNER_STATE_ITEM_INCLUDS_PCH           (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_INF)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO)          |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RESOLUTION_TXT) |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_PROG_TIME)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_PROG_TITLE)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RATING)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION_ICON)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_OUT)      |   \
                                                 BANNER_ITM_HEADPHONES_ID                           |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_OUT)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_PROG_DETAIL))

#define BANNER_STATE_ITEM_INCLUDS_PDCH          (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_INF)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO)          |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RESOLUTION_TXT) |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_PROG_TIME)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_PROG_TITLE)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RATING)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION_ICON)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_OUT)      |   \
                                                 BANNER_ITM_HEADPHONES_ID                           |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_PROG_DETAIL))

#define BANNER_STATE_ITEM_INCLUDS_IPTS          (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RESOLUTION_TXT) |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION_ICON)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_OUT)      |   \
                                                 BANNER_ITM_HEADPHONES_ID                           |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT))


#define BANNER_STATE_ITEM_INCLUDS_EMPTY_SVL     ( NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_MSG))

#define BANNER_STATE_ITEM_INCLUDS_CHANGING      (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO  )        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION_ICON)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RESOLUTION_TXT) |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON))

#define BANNER_STATE_ITEM_INCLUDS_INPTTING      (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPT_CH_NO)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CAPTION_ICON)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON))

#define BANNER_STATE_ITEM_INCLUDS_SHOW_MSG      (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_MSG)            |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO)          |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_LOCK_ICON))

#define BANNER_STATE_ITEM_INCLUDS_NO_SIG        (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_INF)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO)          |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_MSG))

#define BANNER_STATE_ITEM_INCLUDS_HIDDEN_CH     (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_INF)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO)          |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RESOLUTION_TXT) |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_MSG))

#define BANNER_STATE_ITEM_INCLUDS_RETRIEVE      (NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_INF)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_FRM_CH)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NO)          |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_IPTS_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_CH_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_TXT)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TV_NAME)        |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_RESOLUTION_TXT) |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24)       |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_VIDEO_INFO)     |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_ASPECT)         |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_WIFI_ICON)      |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_VISION)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_DOLBY_AUDIO)    |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_AUDIO_FARMAT)   |   \
                                                 NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_MSG))

extern VOID banner_sync_sys_info();
extern INT32 banner_mm_try(VOID);
extern INT32 banner_sys_info_update_hdr(VOID);
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _banner_custom_pre_enter_state (
    UINT8                                       ui1_state_id
    ) ;

/*-----------------------------------------------------------------------------
 * public variable declarations
 *---------------------------------------------------------------------------*/
/* SPECIAL_NOTE_2010_12_18_001
 * Sometimes we frozen the banner view to avoid high-frequence-state-changging issue,
 * that caused the actual state maybe not same as the state we saw on screen.
 * When BTN_PRG_INFO was pressed, we need chnage to next state base on current state.
 * As current state wasn't the state displayed on screen, the result will be
 * unexpected by end-user.
 *
 * To dispel the confusion, we will alway change to CH state if the truly state
 * not equal to the state displayed on screen.
 *
 * The variable b_g_is_virgin_banner was used to identify if the state
 * the state has already sync with VIEW part.
 */
BOOL        b_g_is_virgin_banner        =   TRUE ;

static BOOL b_is_from_info_key          =   FALSE;
static BOOL b_is_from_digit_info_key    =   FALSE;
static BOOL b_is_from_channel_key       =   FALSE;
static BOOL b_is_from_double_info_key   =   FALSE;
static BOOL b_is_ch_num_info_key        =   FALSE;
BOOL        b_g_is_show_by_specia_btn   =   FALSE;
static BOOL b_g_is_banner_paused        =   FALSE;
static BOOL b_ainm_hide_mode            =   TRUE;
static BOOL b_g_is_signal_lost          =   TRUE;
static BOOL b_is_need_show_banner_under_hdmi = FALSE;

/* image handle */
HANDLE_T    h_g_itm_img_empty           =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_lock       =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_fav        =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_fav_full   =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_cc         =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_ttx        =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_up         =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_dn         =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_ad_eye     =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_icon_ad_ear     =   NULL_HANDLE ;
HANDLE_T    h_g_itm_img_frm_3d          =   NULL_HANDLE ;

/*-----------------------------------------------------------------------------
 * private variable declarations
 *---------------------------------------------------------------------------*/

/* banner timer which will show system time to user */
static HANDLE_T             h_g_banner_timer                = NULL_HANDLE ;
static HANDLE_T             h_g_logo_delay_timer            = NULL_HANDLE ;

static BOOL                 b_g_banner_timer_repaint_valid  = FALSE ;
static BOOL                 b_g_banner_timer_is_on_show     = FALSE ;
static UINT32               ui4_g_last_updated_time         = BANNER_INVALID_LAST_UPDATED_TIME ;
static BOOL                 b_g_is_menu_exit                = FALSE;

static BOOL                 b_g_banner_in_3rd               = FALSE;

/* item handle */
static  HANDLE_T            _ah_g_items[BANNER_ITM_LAST_VALID_ENTRY] = {0} ;
static  GL_RECT_T           _a_g_rect_item[BANNER_ITM_LAST_VALID_ENTRY] = {{0,0,0,0}};

/* banner STATEs informations */
static BANNER_STATE_INFO_T  _t_g_states_info[BANNER_STATE_LAST_VALID_ENTRY] =
{
    /* (1) ui1_state_id         (2) ui1_state_pri               (3) t_item_includs                      (4) ui4_time_out_duration          (5) chg_to_state_when_timeout   (6) pf_pre_process_when_enter      (7) b_lock_when_enter    (8)  b_set_as_fnl_when_enter      */
    {BANNER_STATE_NONE,         BANNER_STATE_PRI_NONE,          BANNER_STATE_ITEM_INCLUDS_NONE,         BANNER_TIME_OUT_DURATION_NONE    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        SET_TO_FINAL_WHEN_ENTER},     /* <-- BANNER_STATE_NONE */
    {BANNER_STATE_IDLE,         BANNER_STATE_PRI_IDLE,          BANNER_STATE_ITEM_INCLUDS_NONE,         BANNER_TIME_OUT_DURATION_ZERO    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        SET_TO_FINAL_WHEN_ENTER},     /* <-- BANNER_STATE_IDLE */
    {BANNER_STATE_CH,           BANNER_STATE_PRI_TV,            BANNER_STATE_ITEM_INCLUDS_CH,           BANNER_TIME_OUT_DURATION_SHORT   , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_CH */
    {BANNER_STATE_PCH,          BANNER_STATE_PRI_TV,            BANNER_STATE_ITEM_INCLUDS_PCH,          BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_PCH */
    {BANNER_STATE_PDCH,         BANNER_STATE_PRI_TV,            BANNER_STATE_ITEM_INCLUDS_PDCH,         BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_PDCH */
    {BANNER_STATE_IPTS,         BANNER_STATE_PRI_IPTS,          BANNER_STATE_ITEM_INCLUDS_IPTS,         BANNER_TIME_OUT_DURATION_SHORT   , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        !SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_IPTS */
    {BANNER_STATE_EMPTY_SVL,    BANNER_STATE_PRI_EMPTY_SVL,     BANNER_STATE_ITEM_INCLUDS_EMPTY_SVL,    BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        !SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_EMPTY_SVL */
    {BANNER_STATE_INPTTING,     BANNER_STATE_PRI_INPTTING,      BANNER_STATE_ITEM_INCLUDS_INPTTING,     BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_CH,                 _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        !SET_TO_FINAL_WHEN_ENTER},     /* <-- BANNER_STATE_INPTTING */
    {BANNER_STATE_CHANGING,     BANNER_STATE_PRI_CHANGING,      BANNER_STATE_ITEM_INCLUDS_CHANGING,     BANNER_TIME_OUT_DURATION_CHANGING, BANNER_STATE_CH,                 _banner_custom_pre_enter_state,   !LOCK_WHEN_ENTER,        !SET_TO_FINAL_WHEN_ENTER},     /* <-- BANNER_STATE_CHANGING */
    {BANNER_STATE_HIDDEN_CH,    BANNER_STATE_PRI_HIDDEN_CH,     BANNER_STATE_ITEM_INCLUDS_HIDDEN_CH,    BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   LOCK_WHEN_ENTER,         SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_HIDDEN_CH */
    {BANNER_STATE_RETRIEVE,     BANNER_STATE_PRI_RETRIEVE,      BANNER_STATE_ITEM_INCLUDS_RETRIEVE,     BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   LOCK_WHEN_ENTER ,        SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_RETRIEVE */
    {BANNER_STATE_SHOW_MSG,     BANNER_STATE_PRI_SHOW_MSG,      BANNER_STATE_ITEM_INCLUDS_SHOW_MSG,     BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   LOCK_WHEN_ENTER,         SET_TO_FINAL_WHEN_ENTER},      /* <-- BANNER_STATE_SHOW_MSG */
    {BANNER_STATE_NO_SIG,       BANNER_STATE_PRI_NO_SIG,        BANNER_STATE_ITEM_INCLUDS_NO_SIG,       BANNER_TIME_OUT_DURATION_LONG    , BANNER_STATE_IDLE,               _banner_custom_pre_enter_state,   LOCK_WHEN_ENTER ,        SET_TO_FINAL_WHEN_ENTER}       /* <-- BANNER_STATE_NO_SIG */
} ;

/* banner ITEMs informations */
static BANNER_ITEM_INFO_T    _t_g_items_info[BANNER_ITM_LAST_VALID_ENTRY] =
{
        /* item id */                   /* item type */            /* handle */
    {BANNER_ITM_FRM_CH,             BANNER_ITEM_TYPE_FRM,   &_ah_g_items [BANNER_ITM_FRM_CH             ],&_a_g_rect_item[BANNER_ITM_FRM_CH]} ,
    {BANNER_ITM_IPTS_ICON,          BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_IPTS_ICON          ],&_a_g_rect_item[BANNER_ITM_IPTS_ICON]} ,
    {BANNER_ITM_WIFI_ICON,          BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_WIFI_ICON          ],&_a_g_rect_item[BANNER_ITM_WIFI_ICON]} ,
    {BANNER_ITM_ASPECT,             BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_ASPECT             ],&_a_g_rect_item[BANNER_ITM_ASPECT]} ,
    {BANNER_ITM_RESOLUTION_TXT,     BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_RESOLUTION_TXT     ],&_a_g_rect_item[BANNER_ITM_RESOLUTION_TXT]} ,
    {BANNER_ITM_TIMER_24,           BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_TIMER_24           ],&_a_g_rect_item[BANNER_ITM_TIMER_24]} ,
    {BANNER_ITM_FRM_INF,            BANNER_ITEM_TYPE_FRM,   &_ah_g_items [BANNER_ITM_FRM_INF            ],&_a_g_rect_item[BANNER_ITM_FRM_INF]} ,
    {BANNER_ITM_FRM_DTL,            BANNER_ITEM_TYPE_FRM,   &_ah_g_items [BANNER_ITM_FRM_DTL            ],&_a_g_rect_item[BANNER_ITM_FRM_DTL]} ,
    {BANNER_ITM_FRM_3D,             BANNER_ITEM_TYPE_FRM,   &_ah_g_items [BANNER_ITM_FRM_3D             ],&_a_g_rect_item[BANNER_ITM_FRM_3D]} ,

    {BANNER_ITM_CH_NO,              BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_CH_NO              ],&_a_g_rect_item[BANNER_ITM_CH_NO]} ,
    {BANNER_ITM_CH_NAME,            BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_CH_NAME            ],&_a_g_rect_item[BANNER_ITM_CH_NAME]} ,
    {BANNER_ITM_MSG,                BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_MSG                ],&_a_g_rect_item[BANNER_ITM_MSG]} ,
    {BANNER_ITM_PROG_TITLE,         BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_PROG_TITLE         ],&_a_g_rect_item[BANNER_ITM_PROG_TITLE]} ,
    {BANNER_ITM_PROG_TIME,          BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_PROG_TIME          ],&_a_g_rect_item[BANNER_ITM_PROG_TIME]} ,
    {BANNER_ITM_NEXT_PROG_TITLE,    BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_NEXT_PROG_TITLE    ],&_a_g_rect_item[BANNER_ITM_NEXT_PROG_TITLE]} ,
    {BANNER_ITM_NEXT_PROG_TIME,     BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_NEXT_PROG_TIME     ],&_a_g_rect_item[BANNER_ITM_NEXT_PROG_TIME]} ,
    {BANNER_ITM_PROG_DETAIL,        BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_PROG_DETAIL        ],&_a_g_rect_item[BANNER_ITM_PROG_DETAIL]} ,
    {BANNER_ITM_PROG_DETAIL_PG_IDX, BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_PROG_DETAIL_PG_IDX ],&_a_g_rect_item[BANNER_ITM_PROG_DETAIL_PG_IDX]} ,
    {BANNER_ITM_RATING,             BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_RATING             ],&_a_g_rect_item[BANNER_ITM_RATING]} ,
    {BANNER_ITM_CAPTION,            BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_CAPTION            ],&_a_g_rect_item[BANNER_ITM_CAPTION]} ,
    {BANNER_ITM_AUDIO_LANG,         BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_AUDIO_LANG         ],&_a_g_rect_item[BANNER_ITM_AUDIO_LANG]} ,
    {BANNER_ITM_VIDEO_INFO,         BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_VIDEO_INFO         ],&_a_g_rect_item[BANNER_ITM_VIDEO_INFO]} ,
    {BANNER_ITM_3D_MODE,            BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_3D_MODE            ],&_a_g_rect_item[BANNER_ITM_3D_MODE]} ,
    {BANNER_ITM_3D_FMT,             BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_3D_FMT             ],&_a_g_rect_item[BANNER_ITM_3D_FMT]} ,
    {BANNER_ITM_IPT_CH_NO,          BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_IPT_CH_NO          ],&_a_g_rect_item[BANNER_ITM_IPT_CH_NO]} ,
    {BANNER_ITM_IPTS_LOCK_ICON,     BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_IPTS_LOCK_ICON     ],&_a_g_rect_item[BANNER_ITM_IPTS_LOCK_ICON]} ,
    {BANNER_ITM_TV_LOCK_ICON,       BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_TV_LOCK_ICON       ],&_a_g_rect_item[BANNER_ITM_TV_LOCK_ICON]} ,
    {BANNER_ITM_CAPTION_ICON,       BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_CAPTION_ICON       ],&_a_g_rect_item[BANNER_ITM_CAPTION_ICON]} ,
    {BANNER_ITM_PROG_DETAIL_UP_ICON,BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_PROG_DETAIL_UP_ICON],&_a_g_rect_item[BANNER_ITM_PROG_DETAIL_UP_ICON]} ,
    {BANNER_ITM_PROG_DETAIL_DN_ICON,BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_PROG_DETAIL_DN_ICON],&_a_g_rect_item[BANNER_ITM_PROG_DETAIL_DN_ICON]} ,
    {BANNER_ITM_AD_EYE,             BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_AD_EYE             ],&_a_g_rect_item[BANNER_ITM_AD_EYE]} ,
    {BANNER_ITM_WIFI_TXT,           BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_WIFI_TXT           ],&_a_g_rect_item[BANNER_ITM_WIFI_TXT]} ,
    {BANNER_ITM_TV_NAME,            BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_TV_NAME            ],&_a_g_rect_item[BANNER_ITM_TV_NAME]} ,
    {BANNER_ITM_AUDIO_FARMAT,       BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_AUDIO_FARMAT       ],&_a_g_rect_item[BANNER_ITM_AUDIO_FARMAT]} ,
    {BANNER_ITM_DOLBY_VISION,       BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_DOLBY_VISION       ],&_a_g_rect_item[BANNER_ITM_DOLBY_VISION]} ,
    {BANNER_ITM_DOLBY_AUDIO,        BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_DOLBY_AUDIO        ],&_a_g_rect_item[BANNER_ITM_DOLBY_AUDIO]},
#if (CUSTOMER == VIZIO)
    {BANNER_ITM_HEADPHONES,         BANNER_ITEM_TYPE_ICON,  &_ah_g_items [BANNER_ITM_HEADPHONES         ],&_a_g_rect_item[BANNER_ITM_HEADPHONES]},
#endif
    {BANNER_ITM_AUDIO_OUT,          BANNER_ITEM_TYPE_TEXT,  &_ah_g_items [BANNER_ITM_AUDIO_OUT          ],&_a_g_rect_item[BANNER_ITM_AUDIO_OUT]}
} ;

/*-----------------------------------------------------------------------------
* private methods implementations
*----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _crnt_source_is_tv
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL _crnt_source_is_tv (VOID)
{
    TV_WIN_ID_T                e_tv_win_id = TV_WIN_ID_MAIN ;

    nav_get_focus_id (&e_tv_win_id) ;

    return ((INP_SRC_TYPE_TV == nav_get_src_type (e_tv_win_id)) ? TRUE : FALSE) ;
}

BOOL _is_cnt_src_cast (VOID)
{
    TV_WIN_ID_T   e_tv_win_id = TV_WIN_ID_MAIN ;
    ISL_REC_T     t_isl_rec;

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec(e_tv_win_id, &t_isl_rec);

    return (INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type && DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type);
}
BOOL _is_cnt_src_hdmi (VOID)
{
    TV_WIN_ID_T   e_tv_win_id = TV_WIN_ID_MAIN ;
    ISL_REC_T     t_isl_rec;

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec(e_tv_win_id, &t_isl_rec);
    if(a_nav_ipts_is_hdmi_source(&t_isl_rec))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static BOOL _crnt_tv_is_blocked (SVC_BLOCK_COND_T  e_svc_block_cond)
{
    TV_WIN_ID_T    e_tv_win_id = TV_WIN_ID_MAIN ;
    ISL_REC_T      t_isl_rec = {0} ;
    SVL_REC_T      t_svl_rec = {0} ;

    BANNER_LOG_ON_FAIL (nav_get_focus_id (&e_tv_win_id)) ;
    BANNER_LOG_ON_FAIL (a_tv_get_isl_rec_by_win_id (e_tv_win_id, &t_isl_rec)) ;
    BANNER_LOG_ON_FAIL (nav_get_svl_rec (e_tv_win_id, &t_svl_rec)) ;

    return (e_svc_block_cond == a_tv_default_block_check_fct (
                                SVC_BLOCK_CHECK_USER_BLOCK ,
                                t_isl_rec.s_src_name,
                                &t_svl_rec,
                                NULL)) ;
}

static UINT16 _banner_get_channel_lock_enable(VOID)
{
    UINT8   ui1_rating_enabled;
    UINT8   ui1_val = RATING_ENABLED_STATUS_ON;
    SIZE_T  z_size = ICL_RECID_RATING_ENABLED_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
            &ui1_val, &z_size);

    if (RATING_ENABLED_STATUS_OFF == ui1_val)
    {
        ui1_rating_enabled = 0;
    }
    else
    {
        a_cfg_get_rating_enabled(&ui1_rating_enabled);
    }

    #ifdef APP_NAV_PIP_VCHIP_SOL
    return (ui1_rating_enabled == APP_CFG_RATING_ENABLED_OFF) ? 0 : 1;
    #else
        return ui1_rating_enabled ? 1 : 0;
    #endif
}


/*-----------------------------------------------------------------------------
 * Name
 *      _crnt_source_is_blocked
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _crnt_source_is_blocked (VOID)
{
    return _crnt_tv_is_blocked(SVC_BLOCK_COND_USER_BLOCK_INP);
}

static BOOL _crnt_channel_is_blocked (VOID)
{
    return (_crnt_tv_is_blocked(SVC_BLOCK_COND_USER_BLOCK_CH) && _banner_get_channel_lock_enable());
}

BOOL _crnt_source_is_virtual_input(VOID)
{
    TV_WIN_ID_T   e_tv_win_id = TV_WIN_ID_MAIN ;
    ISL_REC_T     t_isl_rec;

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    BANNER_LOG_ON_FAIL(nav_get_focus_id(&e_tv_win_id));
    BANNER_LOG_ON_FAIL(nav_get_isl_rec(e_tv_win_id, &t_isl_rec));
    BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[Banner] INP_SRC_TYPE_VTRL = %d ui1_internal_id = %d\n",t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL,t_isl_rec.ui1_internal_id));
    return (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_isl_rec.ui1_internal_id > 0);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _crnt_svl_is_empty
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL _crnt_svl_is_empty (VOID)
{
    TV_WIN_ID_T                e_tv_win_id = TV_WIN_ID_MAIN ;

    nav_get_focus_id (&e_tv_win_id) ;

    return nav_is_specified_ch_lst_empty (e_tv_win_id) ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _get_page_number
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT16 _get_page_number (
    UINT16                      ui2_have_lines,
    UINT16                      ui2_lines_in_each_page
    )
{
    UINT16                      ui2_have_pages = 0 ;

    if (ui2_have_lines <= ui2_lines_in_each_page
        ||
        ui2_lines_in_each_page < 1)
    {
        /* only need one page */
        ui2_have_pages = 1 ;
    }
    else if (1 == ui2_lines_in_each_page)
    {
        /* only display one line in each page */
        ui2_have_pages = ui2_have_lines / ui2_lines_in_each_page ;
    }
    else
    {
        /* PLEASE NOTE,
         * if one page display 3 lines,
         * when we scroll the pages, it only changes 2 lines.
         * for example, current line is 5~7, when scrolling up, it will show 7~9.
         * so, we need use (have_lines)/(lines_in_each_page -1 ) to get how many
         * page we needed.
         * there is another problem...
         * from abvoe reason, we can regard each page can display
         * (lines_in_each_page -1 ), but for first page, it can display
         * lines_in_each_page as there has no scroll operation on it.
         * So, we need operation first page with special method.
         */

        /* count out how many pages we need to scroll all lines (not include first page)*/
        ui2_have_pages = (UINT16)
                         ( ((ui2_have_lines-ui2_lines_in_each_page)/(ui2_lines_in_each_page - 1))
                             +
                           (((ui2_have_lines-ui2_lines_in_each_page)%(ui2_lines_in_each_page - 1)) > 0 ? 1 : 0) );

        /* add first page */
        ui2_have_pages += 1 ;
    }

    return ui2_have_pages ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _is_crnt_window
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _is_crnt_window (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    INT32                       i4_ret = 0 ;
    TV_WIN_ID_T                 e_focused_win_id = TV_WIN_ID_MAIN ;

    i4_ret = nav_get_focus_id (&e_focused_win_id) ;

    if (NAVR_OK != i4_ret || e_tv_win_id != e_focused_win_id)
    {
        return FALSE ;
    }

    return TRUE ;
}



/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_update_banner_timer_once
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_custom_update_banner_timer_once(
    VOID*                       pv_tag,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2
    )
{
    DTG_T                       t_loc_dtg        = {0};
    CHAR                        s_crnt_time[9]   = {0};  /* HH:MM:SS */
    CHAR                        s_crnt_time_ex[9]= {0};
    CHAR*                       ps_am_pm = NULL ;
    UTF16_T                     w2s_crnt_time[9] = {0};
    UINT32                      ui4_crnt_time    =  0 ;
    BOOL                        b_is_get_time    = FALSE;
    DT_COND_T                   t_dt_cond = DT_FREE_RUNNING;
    UINT8                       time_format;

    a_cfg_cust_get_time_format(&time_format);
    c_dt_get_utc(NULL, &t_dt_cond);

    /* first check the system time*/
    b_is_get_time = a_dst_get_local_time(&t_loc_dtg);

    if ((TRUE == b_is_get_time) && (time_format != 1))
    {
        ui4_crnt_time = t_loc_dtg.ui1_hr * 60 + t_loc_dtg.ui1_min ;

        if (t_loc_dtg.ui1_hr > 12)
        {
            t_loc_dtg.ui1_hr %= 12;//0301
            ps_am_pm = "PM ";
        }
        else if (t_loc_dtg.ui1_hr == 12)
        {
            ps_am_pm = "PM ";
        }
        else if (t_loc_dtg.ui1_hr == 0)
        {
            t_loc_dtg.ui1_hr = 12;
            ps_am_pm = "AM ";
        }
        else
        {
            ps_am_pm = "AM ";
        }

        c_memset (s_crnt_time_ex, 0, sizeof(s_crnt_time_ex));
        c_memset (s_crnt_time, 0, sizeof(s_crnt_time));

        /* prepare string to update ITM_TIMER */
        c_sprintf(s_crnt_time, "%d:%02d", t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min);

        c_sprintf(s_crnt_time_ex, "%s %s", s_crnt_time, ps_am_pm);
        BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("current time ==>%s \n",s_crnt_time_ex)) ;
        c_uc_ps_to_w2s(s_crnt_time_ex, w2s_crnt_time,
                       sizeof(w2s_crnt_time)/sizeof(w2s_crnt_time[0])-1);
    }
    else if(time_format == 1)
    {
        ui4_crnt_time = t_loc_dtg.ui1_hr * 60 + t_loc_dtg.ui1_min ;

        /* prepare string to update ITM_TIMER */
        c_sprintf(s_crnt_time, "%d:%02d", t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min);
        BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("current time ==>%s \n",s_crnt_time_ex)) ;
        c_uc_ps_to_w2s(s_crnt_time, w2s_crnt_time,
                       sizeof(w2s_crnt_time)/sizeof(w2s_crnt_time[0])-1);

        /* do nothing here*/
    }
    else
    {
        ps_am_pm = " ";

        /* do nothing here*/
    }

    if (ui4_crnt_time == ui4_g_last_updated_time)
    {
        /* time does not change */
        return ;
    }

    /* update ITM_TIMER with current time */
    BANNER_LOG_ON_FAIL (banner_view_update_item (
                            BANNER_ITM_TIMER_24,
                            w2s_crnt_time ,
                            NULL_HANDLE,
                            !UP_TO_VIEW_AT_ONCE)) ;

    ui4_g_last_updated_time = ui4_crnt_time ;

}

/*-----------------------------------------------------------------------------
 * Name
 *      a_banner_custom_update_banner_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID a_banner_custom_update_banner_timer(VOID)
{
    /* execute in timer's thread context */
    BANNER_LOG_ON_FAIL (nav_request_context_switch(
                                _banner_custom_update_banner_timer_once,
                                NULL,
                                NULL,
                                NULL));
}


/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_update_banner_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_custom_update_banner_timer (
    VOID*                       pv_tag,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2
    )
{
    DTG_T                       t_loc_dtg        = {0};
    CHAR                        s_crnt_time[9]   = {0};  /* HH:MM:SS */
    CHAR                        s_crnt_time_ex[9]= {0};
    CHAR*                       ps_am_pm = NULL ;
    UTF16_T                     w2s_crnt_time[9] = {0};
    UINT32                      ui4_crnt_time    =  0 ;
    BOOL                        b_is_get_time    = FALSE;
    DT_COND_T                   t_dt_cond = DT_FREE_RUNNING;
    UINT8                       time_format;

    a_cfg_cust_get_time_format(&time_format);
    if (!b_g_banner_timer_repaint_valid)
    {
        return ;
    }

    c_dt_get_utc(NULL, &t_dt_cond);

    /* first check the system time*/
    b_is_get_time = a_dst_get_local_time(&t_loc_dtg);

    if ((TRUE == b_is_get_time) && (time_format != 1))
    {
        ui4_crnt_time = t_loc_dtg.ui1_hr * 60 + t_loc_dtg.ui1_min ;

        if (t_loc_dtg.ui1_hr > 12)
        {
            t_loc_dtg.ui1_hr %= 12;//0301
            ps_am_pm = "PM ";
        }
        else if (t_loc_dtg.ui1_hr == 12)
        {
            ps_am_pm = "PM ";
        }
        else if (t_loc_dtg.ui1_hr == 0)
        {
            t_loc_dtg.ui1_hr = 12;
            ps_am_pm = "AM ";
        }
        else
        {
            ps_am_pm = "AM ";
        }

        c_memset (s_crnt_time_ex, 0, sizeof(s_crnt_time_ex));
        c_memset (s_crnt_time, 0, sizeof(s_crnt_time));

        /* prepare string to update ITM_TIMER */
        c_sprintf(s_crnt_time, "%d:%02d", t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min);

        c_sprintf(s_crnt_time_ex, "%s %s", s_crnt_time, ps_am_pm);
        BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("current time ==>%s \n",s_crnt_time_ex)) ;
        c_uc_ps_to_w2s(s_crnt_time_ex, w2s_crnt_time,
                       sizeof(w2s_crnt_time)/sizeof(w2s_crnt_time[0])-1);
    }
    else if(time_format == 1)
    {
        ui4_crnt_time = t_loc_dtg.ui1_hr * 60 + t_loc_dtg.ui1_min ;

        /* prepare string to update ITM_TIMER */
        c_sprintf(s_crnt_time, "%d:%02d", t_loc_dtg.ui1_hr, t_loc_dtg.ui1_min);
         BANNER_LOG (_BANNER_LOG_TYPE_ITEM,("current time ==>%s \n",s_crnt_time_ex)) ;
        c_uc_ps_to_w2s(s_crnt_time, w2s_crnt_time,
                       sizeof(w2s_crnt_time)/sizeof(w2s_crnt_time[0])-1);

        /* do nothing here*/
    }
    else
    {
        ps_am_pm = " ";

        /* do nothing here*/
    }

    if (ui4_crnt_time == ui4_g_last_updated_time)
    {
        /* time does not change */
        return ;
    }

    /* update ITM_TIMER with current time */
    BANNER_LOG_ON_FAIL (banner_view_update_item (
                            BANNER_ITM_TIMER_24,
                            w2s_crnt_time ,
                            NULL_HANDLE,
                            UP_TO_VIEW_AT_ONCE)) ;

    ui4_g_last_updated_time = ui4_crnt_time ;

    b_g_banner_timer_is_on_show = TRUE ;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_update_banner_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_custom_update_banner_timer_nfy(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag
    )
{
    b_g_banner_timer_repaint_valid = TRUE ;

    /* execute in timer's thread context */
    BANNER_LOG_ON_FAIL (nav_request_context_switch(
                                _banner_custom_update_banner_timer,
                                pv_tag,
                                NULL,
                                NULL));
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_process_banner_timer_before_enter_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_process_banner_timer_before_enter_state(
    UINT8                       ui1_state_id
    )
{
    BANNER_STATE_INFO_T*        pt_state_info = NULL ;
    BNR_ITEM_SET_T                    t_item_includs = 0 ;

    /* get state information */
    pt_state_info = banner_get_state_info (ui1_state_id) ;
    NAV_ASSERT (pt_state_info) ;
    BANNER_CHK_FAIL ( (pt_state_info) ? NAVR_OK : NAVR_FAIL) ;

    /* get item includs */
    t_item_includs = pt_state_info->t_item_includs ;

    if (t_item_includs & NAV_BNR_STATE_IDX_TO_ID(BANNER_ITM_TIMER_24))
    {
        /* it will comes to here if the state has ITM_TIMER. */

        /* refresh ITM_TIMER immediately if timer is already on showing */
        if (b_g_banner_timer_is_on_show)
        {
            _banner_custom_update_banner_timer (NULL, NULL, NULL) ;
        }

        /* start banner timer */
        BANNER_LOG_ON_FAIL (c_timer_start (
                                h_g_banner_timer, 1000, X_TIMER_FLAG_REPEAT,
                               _banner_custom_update_banner_timer_nfy, NULL)) ;

        b_g_banner_timer_repaint_valid = FALSE ;
    }
    else
    {
        /* it will comes to here if the state has no ITM_TIMER */

        /* stop banner timer */
        BANNER_LOG_ON_FAIL (c_timer_stop (h_g_banner_timer )) ;
        b_g_banner_timer_repaint_valid = FALSE ;

        /* reset banner timer flag */
        b_g_banner_timer_is_on_show = FALSE ;

        /* reset last update flag */
        ui4_g_last_updated_time = BANNER_INVALID_LAST_UPDATED_TIME ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_clean_all_items
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_custom_clean_all_items (VOID)
{
    BANNER_ITEM_INFO_T*         pt_item_info = NULL ;
    UINT8                       ui1_item_id = 0 ;

    for (ui1_item_id = 0;
         ui1_item_id < (UINT8)BANNER_ITM_LAST_VALID_ENTRY;
         ui1_item_id ++)
    {
        pt_item_info = banner_get_item_info (ui1_item_id) ;

        if (NULL == pt_item_info||
            BANNER_ITEM_TYPE_FRM == pt_item_info->e_item_type)
        {
            /* do not clean frame */
            continue ;
        }

        switch(ui1_item_id)
        {
            case BANNER_ITM_TIMER_24:
            case BANNER_ITM_WIFI_ICON:
            case BANNER_ITM_CAPTION:
            case BANNER_ITM_CAPTION_ICON:
            case BANNER_ITM_WIFI_TXT:
            case BANNER_ITM_TV_NAME:
            case BANNER_ITM_IPTS_ICON:
            case BANNER_ITM_DOLBY_VISION:
            case BANNER_ITM_DOLBY_AUDIO:
                break;
            default:
                BANNER_LOG_ON_FAIL (banner_view_update_item (
                                    ui1_item_id,
                                    NULL,
                                    NULL_HANDLE,
                                   !UP_TO_VIEW_AT_ONCE)) ;
                break;
        };
    }

    /* reset last update flag for banner timer */
    ui4_g_last_updated_time = BANNER_INVALID_LAST_UPDATED_TIME ;
}

/*---------------------------------------------------------------------------
 * Name
 *      _banner_custom_root_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_root_frame_nfy_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2
    )
{
    BANNER_CHK_FAIL (c_wgl_default_msg_proc(
                                h_widget, ui4_msg, pv_param1, pv_param2)) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_pre_enter_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_custom_pre_enter_state (
    UINT8                       ui1_state_id
    )
{
    UTF16_T*                    pt_message    = NULL ;

    /* process banner timer */
    BANNER_LOG_ON_FAIL (_banner_custom_process_banner_timer_before_enter_state (ui1_state_id)) ;

    /* prepare message for some special state */
    {
        switch (ui1_state_id)
        {
        case BANNER_STATE_HIDDEN_CH:
            pt_message = MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_HIDDEN_CH) ;
            BANNER_LOG_ON_FAIL (banner_view_update_item  (
                                BANNER_ITM_CH_NAME, pt_message, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
            break ;

        case BANNER_STATE_RETRIEVE:
            pt_message = MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_GET_DATA) ;
            BANNER_LOG_ON_FAIL (banner_view_update_item  (
                                BANNER_ITM_CH_NAME, pt_message, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
            break ;

        case BANNER_STATE_EMPTY_SVL:
            pt_message = MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_SCAN_CH) ;
            BANNER_LOG_ON_FAIL (banner_view_update_item  (
                                BANNER_ITM_CH_NAME, pt_message, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
            break ;

        case BANNER_STATE_NO_SIG:
            pt_message = MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NO_SIGNAL) ;
            BANNER_LOG_ON_FAIL (banner_view_update_item  (
                                BANNER_ITM_CH_NAME, pt_message, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
            break ;

        case BANNER_STATE_SHOW_MSG:
            {
                TV_WIN_ID_T     e_tv_win_id   = TV_WIN_ID_MAIN ;
                LOCKED_STATUS_T e_lock_status = LOCKED_STATUS_NONE ;

                BANNER_BREAK_ON_FAIL (nav_get_focus_id (&e_tv_win_id)) ;
                e_lock_status = nav_get_locked_status (e_tv_win_id) ;

                if (LOCKED_STATUS_CHANNEL_LOCKED == e_lock_status)
                {
                        pt_message = MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_LOCKED_CH) ;
                }
                else if (
                    LOCKED_STATUS_PROGRAM_RATING == e_lock_status)
                {
                        pt_message = MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_LOCKED_PROG) ;
                }
                else
                {
                    pt_message = L"" ;
                }
                BANNER_LOG_ON_FAIL (banner_view_update_item  (
                                BANNER_ITM_CH_NAME, pt_message, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
            }
            break ;

#ifdef  APP_ISDB_SUPPORT
        case BANNER_STATE_NON_BRDCSTING:
            BANNER_LOG_ON_FAIL (banner_view_update_item  (
                                BANNER_ITM_CH_NAME,
                                MLM_NAV_TEXT (nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_NON_BRDCSTING),
                                NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
            break ;
#endif

        default:
            break ;
        }
    }
}

static INT32 _banner_custom_init_item_rect (VOID)
{
    UINT8   ui1_cnt_loop;
    GL_RECT_T*  tp_rect;

    for (ui1_cnt_loop = 0; ui1_cnt_loop < BANNER_ITM_LAST_VALID_ENTRY; ui1_cnt_loop++)
    {
       if( NULL != (tp_rect =nav_banner2_view_rc_get_wgt_rect(ui1_cnt_loop)))
       {
           memcpy(&_a_g_rect_item[ui1_cnt_loop],tp_rect,sizeof(GL_RECT_T));
       }
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_prepare_item_handle
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_prepare_item_handle (VOID)
{
    //INT32 i4_ret;
    UINT8   ui1_cnt_loop;

    _ah_g_items[BANNER_ITM_FRM_CH             ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ITM_CH) ;
    _ah_g_items[BANNER_ITM_IPTS_ICON          ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_INPUT) ;
    _ah_g_items[BANNER_ITM_WIFI_ICON          ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_WIFI) ;
    _ah_g_items[BANNER_ITM_ASPECT             ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_ASPECT) ;
    _ah_g_items[BANNER_ITM_RESOLUTION_TXT     ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RESOLUTION) ;
    _ah_g_items[BANNER_ITM_TIMER_24           ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TIMER_24) ;
    _ah_g_items[BANNER_ITM_FRM_INF            ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PCH) ;
    _ah_g_items[BANNER_ITM_FRM_DTL            ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PDCH) ;
    _ah_g_items[BANNER_ITM_WIFI_TXT           ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_WIFI_TXT) ;
    _ah_g_items[BANNER_ITM_TV_NAME            ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TV_NAME) ;
    _ah_g_items[BANNER_ITM_CH_NO              ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NO) ;
    _ah_g_items[BANNER_ITM_CH_NAME            ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NAME) ;
    _ah_g_items[BANNER_ITM_MSG                ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_MSG) ;
    _ah_g_items[BANNER_ITM_PROG_TITLE         ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_TITLE) ;
    _ah_g_items[BANNER_ITM_PROG_TIME          ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_CRNT_TIME) ;
    _ah_g_items[BANNER_ITM_NEXT_PROG_TITLE    ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TITLE) ;
    _ah_g_items[BANNER_ITM_NEXT_PROG_TIME     ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TIME) ;
    _ah_g_items[BANNER_ITM_PROG_DETAIL        ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL) ;
    _ah_g_items[BANNER_ITM_PROG_DETAIL_PG_IDX ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL_PG_IDX) ;
    _ah_g_items[BANNER_ITM_RATING             ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RATING) ;
    _ah_g_items[BANNER_ITM_CAPTION            ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CAPTION) ;
    _ah_g_items[BANNER_ITM_AUDIO_LANG         ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_INFO_LANG) ;
    _ah_g_items[BANNER_ITM_VIDEO_INFO         ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_VIDEO_INFO) ;
    _ah_g_items[BANNER_ITM_IPT_CH_NO          ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_INPUT_CH_NO) ;
    _ah_g_items[BANNER_ITM_3D_MODE            ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_MODE) ;
    _ah_g_items[BANNER_ITM_3D_FMT             ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_FMT) ;
    _ah_g_items[BANNER_ITM_IPTS_LOCK_ICON     ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_IPTS_LOCK) ;
    _ah_g_items[BANNER_ITM_TV_LOCK_ICON       ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_TV_LOCK) ;
    _ah_g_items[BANNER_ITM_CAPTION_ICON       ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_CAPTION_ICON) ;
    _ah_g_items[BANNER_ITM_PROG_DETAIL_UP_ICON] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_UP) ;
    _ah_g_items[BANNER_ITM_PROG_DETAIL_DN_ICON] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_DN) ;
    _ah_g_items[BANNER_ITM_AD_EYE             ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_AD_EYE) ;
    _ah_g_items[BANNER_ITM_FRM_3D             ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ITM_3D) ;
    _ah_g_items[BANNER_ITM_AUDIO_FARMAT       ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_FORMAT) ;
    _ah_g_items[BANNER_ITM_DOLBY_VISION       ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_VISION) ;
    _ah_g_items[BANNER_ITM_DOLBY_AUDIO        ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_AUDIO) ;
#if (CUSTOMER == VIZIO)
    _ah_g_items[BANNER_ITM_HEADPHONES         ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_HEADPHONES) ;
#endif
    _ah_g_items[BANNER_ITM_AUDIO_OUT          ] = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_OUT) ;
    for (ui1_cnt_loop = BANNER_ITM_CUST_TOPMOST_BEGIN; ui1_cnt_loop < BANNER_ITM_LAST_VALID_ENTRY; ui1_cnt_loop++)
    {
        BANNER_LOG_ON_FAIL (c_wgl_insert(_ah_g_items[ui1_cnt_loop],
                              NULL_HANDLE,
                              WGL_INSERT_TOPMOST,
                              WGL_NO_AUTO_REPAINT));
    }


    BANNER_LOG_ON_FAIL (c_wgl_insert(_ah_g_items[BANNER_ITM_IPTS_ICON],
                              NULL_HANDLE,
                              WGL_INSERT_TOPMOST,
                              WGL_NO_AUTO_REPAINT));

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_prepare_item_imgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_prepare_item_imgs (VOID)
{
    /* - NO - caption icon */
#if 1
    h_g_itm_img_icon_cc = NULL_HANDLE;
#else
    h_g_itm_img_icon_cc = h_g_banner_caption_img ;
#endif
    /* lock icon */
    h_g_itm_img_icon_lock = h_g_banner_lock_img ;

    /* favortie icon */
    h_g_itm_img_icon_fav = h_g_banner_favorite_img ;

    /* favortie full icon */
    h_g_itm_img_icon_fav_full = h_g_banner_fav_full_img ;

    /* teletext */
    h_g_itm_img_icon_ttx = h_g_banner_ttx_img ;

    /* arrow up */
    h_g_itm_img_icon_up = h_g_banner_arrow_up_img ;

    /* arrow down */
    h_g_itm_img_icon_dn = h_g_banner_arrow_down_img ;

    /* ad_eye */
    h_g_itm_img_icon_ad_eye = h_g_banner_ad_eye_img ;

    /* ad_ear */
    h_g_itm_img_icon_ad_ear = h_g_banner_ad_ear_img ;

    /* 3d icon */
    h_g_itm_img_frm_3d = h_g_banner_3d_bar_bmp ;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_browse_detail_page
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_browse_detail_page(
    UINT8                       ui1_page_dir
    )
{
    UINT16                      ui2_total_lines         = 0 ;
    UINT16                      ui2_total_pages         = 0 ;
    UINT16                      ui2_page_lines          = 0 ;
    UINT16                      ui2_start_lines         = 0;
    UINT16                      ui2_crnt_page_index     = 0;
    CHAR                        s_page_detail_index[10] = {0};
    UTF16_T                     w2s_string[10+1]        = {0};

    switch (ui1_page_dir)
    {
    case BANNER_PROG_DETAIL_GOTO_THIS_PAGE :
        break ;

    case BANNER_PROG_DETAIL_GOTO_NEXT_PAGE :
        BANNER_LOG_ON_FAIL (c_wgl_do_cmd(
                                _ah_g_items[BANNER_ITM_PROG_DETAIL],
                                WGL_CMD_TEXT_PAGE_SCROL,
                                WGL_PACK(FALSE),
                                WGL_PACK(TRUE) )) ;
        break ;

    case BANNER_PROG_DETAIL_GOTO_PREV_PAGE :
        BANNER_LOG_ON_FAIL (c_wgl_do_cmd(
                                _ah_g_items[BANNER_ITM_PROG_DETAIL],
                                WGL_CMD_TEXT_PAGE_SCROL,
                                WGL_PACK(TRUE),
                                WGL_PACK(TRUE) )) ;
        break ;

    case BANNER_PROG_DETAIL_GOTO_FIRST_PAGE :
        BANNER_LOG_ON_FAIL (c_wgl_do_cmd(
                                _ah_g_items[BANNER_ITM_PROG_DETAIL],
                                WGL_CMD_TEXT_SET_DISPLAY_START,
                                (VOID*)0,
                                NULL ));
        break ;

    default :
        BANNER_LOG_ON_FAIL (NAVR_NOT_SUPPORT) ;
        break ;
    }

    /* get total lines */
    BANNER_CHK_FAIL (c_wgl_do_cmd(_ah_g_items[BANNER_ITM_PROG_DETAIL],
                                WGL_CMD_TEXT_GET_TOTAL_LINES,
                                WGL_PACK(&ui2_total_lines),
                                NULL)) ;

    /* get page lines */
    BANNER_CHK_FAIL (c_wgl_do_cmd(_ah_g_items[BANNER_ITM_PROG_DETAIL],
                                WGL_CMD_TEXT_GET_PAGE_LINES,
                                (VOID*)&ui2_page_lines,
                                NULL)) ;

    /* get start lines */
    BANNER_CHK_FAIL (c_wgl_do_cmd(_ah_g_items[BANNER_ITM_PROG_DETAIL],
                                WGL_CMD_TEXT_GET_DISPLAY_START,
                                WGL_PACK(&ui2_start_lines),
                                NULL)) ;

    /* count out total pages */
    ui2_total_pages     = _get_page_number (ui2_total_lines, ui2_page_lines) ;

    /* count out current page index */
    ui2_crnt_page_index = _get_page_number (
                                ui2_start_lines + ui2_page_lines - 1, ui2_page_lines) ;

    /* event detail index */
    c_sprintf(s_page_detail_index, "%d/%d",
                                ui2_crnt_page_index, ui2_total_pages);

    BANNER_CHK_FAIL (c_uc_ps_to_w2s(s_page_detail_index, w2s_string, 10)) ;

    if (ui2_total_pages > 1)
    {
        /* more than one page, show page index */
        BANNER_LOG_ON_FAIL (banner_view_update_item (
                                BANNER_ITM_PROG_DETAIL_PG_IDX,
                                w2s_string, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
    }
    else
    {
        /* hide page index */
        BANNER_LOG_ON_FAIL (banner_view_update_item (
                                BANNER_ITM_PROG_DETAIL_PG_IDX,
                                BANNER_TEXT(""), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
    }

    if (ui2_crnt_page_index > 1)
    {
        /* show up arrow */
        BANNER_LOG_ON_FAIL (banner_view_update_item (
                                BANNER_ITM_PROG_DETAIL_UP_ICON ,
                                NULL,
                                h_g_itm_img_icon_up,
                                !UP_TO_VIEW_AT_ONCE)) ;
    }
    else
    {
        /* hide up arrow */
        BANNER_LOG_ON_FAIL (banner_view_update_item (
                                BANNER_ITM_PROG_DETAIL_UP_ICON ,
                                NULL, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
    }

    if (ui2_crnt_page_index < ui2_total_pages)
    {
        /* show dn arrow */
        BANNER_LOG_ON_FAIL (banner_view_update_item (
                                BANNER_ITM_PROG_DETAIL_DN_ICON ,
                                NULL,
                                h_g_itm_img_icon_dn,
                                !UP_TO_VIEW_AT_ONCE)) ;
    }
    else
    {
        /* hide up arrow */
        BANNER_LOG_ON_FAIL (banner_view_update_item (
                                BANNER_ITM_PROG_DETAIL_DN_ICON ,
                                NULL, NULL_HANDLE, !UP_TO_VIEW_AT_ONCE)) ;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_reset_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_reset_state (VOID)
{
    /* as focusd window changed, unlock all state */
    BANNER_LOG_ON_FAIL (banner_unlock_state (
                                BANNER_STATE_VIRTUAL_ALL_STATE)) ;

    /* set to STATE_NONE
     * please note, DO NOT use STATE_IDLE, it will hide OSD immedietely
     */
    BANNER_LOG_ON_FAIL (banner_change_state_to (
                                BANNER_STATE_NONE,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_loop_next_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_loop_next_state (
    UINT32                      ui4_key_code
    )
{
    UINT8                       ui1_crnt_state = 0 ;
    UINT8                       ui1_next_state = 0 ;
    CHAR                        s_disp_name[33] = {0};
    UINT8                       ui1_input_id = 0;
    ISL_REC_T                   t_isl_rec;

    /* get current state */
    BANNER_CHK_FAIL (banner_get_crnt_state (&ui1_crnt_state)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,(" current state is %s \n ",GET_STATE_DISP_NAME(ui1_crnt_state))) ;
    /* recover the latest state (final state) first */
    BANNER_CHK_FAIL (banner_change_state_to (
                                BANNER_STATE_VIRTUAL_FINAL,
                               !NEED_SHOW_BANNER_VIEW,
                               !UP_TO_VIEW_AT_ONCE)) ;

    if (BTN_PRG_INFO == ui4_key_code)
    {
        if(nav_banner_get_from_digit_pad_info_key() == FALSE)
        {
            switch (ui1_crnt_state)
            {
                case BANNER_STATE_IDLE :
                case BANNER_STATE_NONE :
                    ui1_next_state  =  _crnt_channel_is_blocked() ? BANNER_STATE_SHOW_MSG: BANNER_STATE_CH ;
                    break ;
                case BANNER_STATE_PDCH :
                    ui1_next_state  =   BANNER_STATE_NONE ;
                    break ;
                case BANNER_STATE_CH:
                case BANNER_STATE_CHANGING :
                case BANNER_STATE_PCH :
                     ui1_next_state  =   _crnt_source_is_tv() ? BANNER_STATE_PDCH : BANNER_STATE_NONE;
                     break;
                default :
                    /* current state is NON-TV, the info key will toggle between current state and NONE */
                    ui1_next_state  =   BANNER_STATE_NONE ;
                    break ;
            }
        }
        else
        {
            nav_banner_set_from_digit_pad_info_key(FALSE);
            ui1_next_state  =   _crnt_source_is_tv() ? BANNER_STATE_PDCH : BANNER_STATE_NONE;
        }
    }
    else
    {
        /* do nothing */
        ui1_next_state      =   ui1_crnt_state ;
    }

    BANNER_LOG (_BANNER_LOG_TYPE_STATE,(" next state is %s\n ",GET_STATE_DISP_NAME(ui1_next_state))) ;
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL && t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
    {
        if(ui1_next_state==BANNER_STATE_PCH || ui1_next_state==BANNER_STATE_PDCH)
        {
            ui1_next_state = BANNER_STATE_IDLE;
            BANNER_LOG_ON_FAIL (banner_change_state_to (ui1_next_state,
                                            NEED_SHOW_BANNER_VIEW,
                                            UP_TO_VIEW_AT_ONCE)) ;

        }
        else
        {
           BANNER_LOG_ON_FAIL (banner_change_state_to (ui1_next_state,
                                                NEED_SHOW_BANNER_VIEW,
                                                UP_TO_VIEW_AT_ONCE)) ;
        }
    }
    else
    {
        BANNER_LOG_ON_FAIL (banner_change_state_to (ui1_next_state,
                                                NEED_SHOW_BANNER_VIEW,
                                                UP_TO_VIEW_AT_ONCE)) ;
    }
#ifdef APP_TTS_SUPPORT
    if(ui1_next_state == BANNER_STATE_PDCH)
    {
        nav_banner_set_from_double_info_key(TRUE);
        nav_banner_view_detail_info_tts();
    }
#endif
    return NAVR_OK ;
}

VOID nav_show_banner_input_source_msg_hdlr(VOID)
{
    UINT8   ui1_val = ICL_RECID_CUSTOM_INPUT_NAME_CHANGE;
    SIZE_T  z_size = ICL_RECID_CUSTOM_FLAG_CHANGE_SIZE;

    //vtrl app display content by mi_mm,need update here
    #if 0
    if(_crnt_source_is_virtual_input())
    {
        /*virtual input should not show banner*/
        return ;
    }
    #endif 
    
    if(NAV_COMP_ID_INPUT_SRC == nav_get_active_component())
    {
        nav_grab_activation(NAV_COMP_ID_BANNER);
    }

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_CUSTOM_FLAG_CHANGE,
                          ICL_RECID_CUSTOM_FLAG_CHANGE),
                          (VOID*) &ui1_val, z_size);

    if(a_banner_allow_to_show() && !banner_view_is_on_show())
    {
        banner_view_clean_av_item();
        banner_hide_msg();
        /* recover the latest state (final state) first */
        BANNER_CHK_FAIL(banner_change_state_to (
                                BANNER_STATE_VIRTUAL_FINAL,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE));
        BANNER_CHK_FAIL(banner_change_state_to (
                                BANNER_STATE_CH,
                                FALSE,
                                TRUE));
        banner_view_set_visible(TRUE);
        nav_bnr_timer_reload(NULL_HANDLE,0,(NAV_BNR_STATE_TIMER_OPER_TYPE_T)0);
    }
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_sync_state_when_svc_chg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_sync_state_when_svc_chg (
    BOOL                        b_before_svc_chg ,
    UINT8*                      pui1_next_state
    )
{
    BOOL b_crnt_is_tv     = _crnt_source_is_tv();
    BOOL b_source_blocked = _crnt_source_is_blocked();

    if (!pui1_next_state)
    {
        BANNER_CHK_FAIL (NAVR_INV_ARG) ;
    }

    *pui1_next_state = BANNER_STATE_IPTS;

    /* sync final setat */
    if (b_crnt_is_tv)
    {
        BANNER_LOG_ON_FAIL (banner_change_state_to (
                                BANNER_STATE_VIRTUAL_TV_DEFAULT,
                               !NEED_SHOW_BANNER_VIEW,
                               !UP_TO_VIEW_AT_ONCE)) ;

        if(!b_source_blocked)
            *pui1_next_state = BANNER_STATE_CH;
    }
    else
    {
        if(b_source_blocked)
            *pui1_next_state = BANNER_STATE_IPTS;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
* public methods implementations
*---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_update_banner_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _banner_custom_no_signal_timer_nfy(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag
    )
{
    //b_is_need_show_banner_under_hdmi = TRUE;
    DBG_LOG_PRINT ((" _banner_custom_no_signal_timer_nfy \n "));
}
static UINT32 _banner_custom_get_current_hdmi_5v(UINT8 *pui1_5v_status)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T					   z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T					   z_size = sizeof(pui1_5v_status);
    TV_WIN_ID_T                   e_tv_win_id = TV_WIN_ID_MAIN ;
    ISL_REC_T                     t_isl_rec;
    DRV_CUSTOM_CUST_SPEC_TYPE_T get_hdmi_flag;

    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
    nav_get_focus_id(&e_tv_win_id);
    nav_get_isl_rec(e_tv_win_id, &t_isl_rec);
    
    if(t_isl_rec.ui1_internal_id == 0) {
        get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI1_5V_STATUS;
    } else if(t_isl_rec.ui1_internal_id == 1) {
        get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI2_5V_STATUS;
    } else if(t_isl_rec.ui1_internal_id == 2) {
        get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI3_5V_STATUS;
    } else if(t_isl_rec.ui1_internal_id == 3) {
        get_hdmi_flag = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI4_5V_STATUS;
    }

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = get_hdmi_flag;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_5v_status;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
    					  DRV_CUST_COMP_ID,
    					  FALSE,
    					  ANY_PORT_NUM,
    					  0,
    					  &t_op_info,
    					  &z_size_drv
    					  );

    if(i4_ret != RMR_OK)
    {
      DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
      return i4_ret;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_before_svc_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_before_svc_change (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    /* the message is not from focused window */
    if (FALSE == _is_crnt_window (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;

    #ifdef APP_TTS_SUPPORT
    /* reset tts updated item mask */
    banner_view_tts_reset_updated_mask();
    #endif
    banner_view_clean_av_item();
    /* reset state lock */
    BANNER_CHK_FAIL (banner_unlock_state (BANNER_STATE_VIRTUAL_ALL_STATE)) ;

    nav_banner_set_from_channel_key(TRUE);
   /*if change channel very fast this msg maybe loss, this can cause tts can't read out
    *  banner when using number key change channel.
    */
    banner_view_tv_info_updeted_erase();
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_after_svc_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_after_svc_change (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
   UINT8     ui1_new_state = 0 ;

    /* the message is not from focused window */
    if (FALSE == _is_crnt_window (e_tv_win_id) ||
        TRUE == b_g_is_menu_exit)
    {
        b_g_is_menu_exit = FALSE;
        return NAVR_OK ;
    }

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n "));
    /* get next state according current environment */
    BANNER_CHK_FAIL (_banner_custom_sync_state_when_svc_chg (FALSE, &ui1_new_state));
    banner_sync_sys_info();
    /* change to new state */
    if (_is_cnt_src_hdmi() && !b_is_need_show_banner_under_hdmi)
    {
        /* no need update banner*/
    }
    else
    {
        BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    ui1_new_state,
                                    TRUE,
                                    UP_TO_VIEW_AT_ONCE));
    }
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_before_svcs_swap
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_before_svcs_swap (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;
    BANNER_LOG_ON_FAIL (banner_view_freeze (
                                TRUE, BANNER_CUSTOM_FREEZE_VIEW_ID_SVC_SWAP)) ;
    BANNER_LOG_ON_FAIL (_banner_custom_reset_state ()) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_after_svcs_swap
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_after_svcs_swap (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    UINT8                       ui1_new_state = 0 ;

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;
    BANNER_LOG_ON_FAIL (banner_view_freeze (
                                FALSE, BANNER_CUSTOM_FREEZE_VIEW_ID_SVC_SWAP)) ;

    /* get next state according current environment */
    BANNER_CHK_FAIL (_banner_custom_sync_state_when_svc_chg (TRUE, &ui1_new_state)) ;

    /* change to new state and update view immedietly */
    BANNER_LOG_ON_FAIL (banner_change_state_to (
                                ui1_new_state,
                                NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE)) ;
    return NAVR_OK ;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_before_tv_mode_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_before_tv_mode_change (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;
    /* freeze "view" */
    BANNER_LOG_ON_FAIL (banner_view_freeze (TRUE, BANNER_CUSTOM_FREEZE_VIEW_ID_TV_MODE)) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_after_tv_mode_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_after_tv_mode_change (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;
    /* unfreeze "view" part */
    BANNER_LOG_ON_FAIL (banner_view_freeze (FALSE, BANNER_CUSTOM_FREEZE_VIEW_ID_TV_MODE)) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_focus_changed
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_focus_changed (TV_WIN_ID_T  e_tv_win_id)
{
    /* When this message was received, banner will reload all items for new window.
     * 1) To keep the message un-repainted, the view part need to be frozen.
     * 2) some item may change the state, we need unlock current state to
     *    make sure the changing operation success.
     * 3) clean all items before reload the content
     * 4) request SI to re-send the notification of all items.
     * 5) unfreeze "view" part to enable view update
     * 6) update view
     */

    /* 1) freeze "view" part, once view was frozen, the "view" part
     *    will not be repainted untill "unfreeze" opertion executed
     */
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;
    BANNER_LOG_ON_FAIL (banner_view_freeze (TRUE, BANNER_CUSTOM_FREEZE_VIEW_ID_CHG_FOCUS)) ;

    /* 2) reset state */
    BANNER_LOG_ON_FAIL (_banner_custom_reset_state ()) ;

    /* 4) request sys info module to resend all notifications */
    banner_sync_sys_info();
    /* 5) unfreeze "view" part */
    BANNER_LOG_ON_FAIL (banner_view_freeze (FALSE, BANNER_CUSTOM_FREEZE_VIEW_ID_CHG_FOCUS)) ;

    /* 6) change to TV_DEFAULT state, the state will keep unchanging if
     *    current state is locked and the priority is higher
     */
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("focus_change completed \n")) ;
#if 0
    BANNER_LOG_ON_FAIL (banner_change_state_to (
                                (_crnt_source_is_tv ())
                                ? BANNER_STATE_VIRTUAL_FINAL
                                : BANNER_STATE_IPTS,
                                ! _is_cnt_src_cast(),
                                UP_TO_VIEW_AT_ONCE)) ;
#endif

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_show_banner
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_show_banner (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    UINT8                       ui1_crnt_state = 0 ;

    /* FIXME_MIN :
     * as the state will be cached, it may not matched current view
     * I will refine the repaint mechanism later
     */

    /* get current state */
    BANNER_CHK_FAIL (banner_get_crnt_state (&ui1_crnt_state)) ;

    /* if banner is NOT on showing, go to final state ,otherwise do nothing
     * PLEASE NOTE: STATE_NONE is ON_SHOWING state !!
     */
    if (BANNER_STATE_IDLE == ui1_crnt_state)
    {
        if (nav_link_mode_is_on())
        {
            /* don't show ui when nav link mode is on */
            BANNER_CHK_FAIL (banner_change_state_to (
                                BANNER_STATE_VIRTUAL_FINAL,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;
        }
        else
        {
            /* do not activate banner component ,just show ui */
            BANNER_CHK_FAIL (banner_change_state_to (
                                BANNER_STATE_VIRTUAL_FINAL,
                                NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE)) ;
        }
    }
    else
    {
        BANNER_CHK_FAIL (banner_view_refresh (UP_TO_VIEW_AT_ONCE)) ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_svl_is_empty
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_svl_is_empty (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    if (FALSE == _is_crnt_window (e_tv_win_id))
    {
        return NAVR_OK ;
    }
    BANNER_LOG (_BANNER_LOG_TYPE_STATE,("\n")) ;
    /* change to SHOW_MSG state */
    BANNER_CHK_FAIL (banner_change_state_to (
                                BANNER_STATE_EMPTY_SVL,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;
	
    BANNER_CHK_FAIL (banner_change_state_to (
                            BANNER_STATE_CH,
                            NEED_SHOW_BANNER_VIEW,
                            UP_TO_VIEW_AT_ONCE)) ;
	
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_evt_ready
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_evt_ready (
    TV_WIN_ID_T                 e_tv_win_id ,
    BOOL                        b_hidden
    )
{
    UINT8                       ui1_state = 0 ;

    if (FALSE == _is_crnt_window (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    /* unlock retrieve state */
    BANNER_CHK_FAIL (banner_unlock_state (BANNER_STATE_RETRIEVE)) ;

    if (_crnt_source_is_tv())
    {
        /* try to change to TV_DEFAULT state */
        BANNER_CHK_FAIL (banner_get_crnt_state (&ui1_state)) ;

        if (BANNER_STATE_CH == (BANNER_STATE_T)ui1_state ||
            BANNER_STATE_PCH == (BANNER_STATE_T)ui1_state ||
            BANNER_STATE_PDCH == (BANNER_STATE_T)ui1_state)
        {
            /* already in TV_DEFAULT state, do nothing  */
        }
        else
        {
            BANNER_CHK_FAIL (banner_change_state_to (
                                    BANNER_STATE_VIRTUAL_TV_DEFAULT,
                                   !NEED_SHOW_BANNER_VIEW,
                                   !UP_TO_VIEW_AT_ONCE)) ;
        }
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_hidden_ch
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_hidden_ch (
    TV_WIN_ID_T                 e_tv_win_id ,
    BOOL                        b_hidden
    )
{
    if (FALSE == _is_crnt_window (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    if (b_hidden)
    {
        /* is hidden channel */
        BANNER_CHK_FAIL (banner_change_state_to (
                                BANNER_STATE_HIDDEN_CH,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;
    }
    else
    {
        /* is not a hidden channel, do nothing */
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_av_notify
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_av_notify (
    TV_WIN_ID_T                 e_tv_win_id ,
    NAV_AV_STATUS_T             e_av_status
    )
{
#if 0
    if (FALSE == _is_crnt_window (e_tv_win_id))
    {
        return NAVR_OK ;
    }

    if (NAV_AV_STATUS_UNKNOWN == e_av_status)
    {
#if 0   /* for this project no need RETRIEVE state */
        /* enter retrying state */
        BANNER_LOG_ON_FAIL (banner_change_state_to (
                                BANNER_STATE_RETRIEVE,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;
#endif
    }
    else
    {
        BANNER_CHK_FAIL (banner_unlock_state (
                                BANNER_STATE_RETRIEVE)) ;

        /* change to tv default(CH/PCH/PDCH) state */
        BANNER_CHK_FAIL (banner_change_state_to (
                                BANNER_STATE_VIRTUAL_TV_DEFAULT,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;
    }
#endif
    return NAVR_OK ;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_no_signal
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

static INT32 _banner_custom_handle_msg_no_signal (TV_WIN_ID_T   e_tv_win_id )
{
    UINT8   ui1_new_state;
    UINT8   get_hdmi1_state = 0;

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("\n ")) ;

    banner_view_clean_av_item();
    banner_hide_msg();
    if(FALSE == _is_crnt_window (e_tv_win_id) ||
        TRUE == b_g_is_menu_exit)
    {
        b_g_is_menu_exit = FALSE;
        return NAVR_OK;
    }
    b_g_is_signal_lost = TRUE;
#if 1
    BANNER_CHK_FAIL (_banner_custom_sync_state_when_svc_chg (FALSE, &ui1_new_state));
    banner_sync_sys_info();
    /* change to new state */
    if (_is_cnt_src_hdmi() && !b_is_need_show_banner_under_hdmi)
    {
        
        _banner_custom_get_current_hdmi_5v(&get_hdmi1_state);
        DBG_LOG_PRINT ((" _banner_custom_handle_msg_no_signal get_hdmi1_state=%d \n ",get_hdmi1_state));
        if(0 != get_hdmi1_state)
        {
            /* no need update banner*/
        }
        else
        {
            
            b_is_need_show_banner_under_hdmi= TRUE;
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    ui1_new_state,
                                    TRUE,
                                    UP_TO_VIEW_AT_ONCE));
        }
    }
    else
    {
        BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    ui1_new_state,
                                    TRUE,
                                    UP_TO_VIEW_AT_ONCE));
    }
#endif
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_signal_captured
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_signal_captured (TV_WIN_ID_T   e_tv_win_id)
{
    UINT8                       ui1_new_state = 0 ;
    CHAR                        s_disp_name[33] = {0};
    UINT8                       ui1_input_id = 0;
    ISL_REC_T                   t_isl_rec;

    /* if not under signal lost  or not current win  we should not show banner*/
    if (FALSE == _is_crnt_window (e_tv_win_id) ||
        !b_g_is_signal_lost ||
        TRUE == b_g_is_menu_exit)
    {
        return NAVR_OK ;
    }

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" b_g_is_signal_lost = %d\n ",b_g_is_signal_lost)) ;
    BANNER_CHK_FAIL (banner_unlock_state (BANNER_STATE_NO_SIG)) ;

    b_g_is_signal_lost = FALSE;
    /* get next state */
    BANNER_CHK_FAIL (_banner_custom_sync_state_when_svc_chg (FALSE, &ui1_new_state)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" ui1_new_state = %d\n ",ui1_new_state)) ;
    /* change to new state,
     * at here we has not change to update the banner OSD at once as it unstable
     */
    
    if (_is_cnt_src_hdmi() && !b_is_need_show_banner_under_hdmi)
    {
        /* no need update banner*/
    }
    else
    {
        /*when video resolution changes, it should not show banner CR:DTV00750658 */
        a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        a_cfg_get_input_src(s_disp_name, &ui1_input_id);
        a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
        if ((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type && DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)||
           TRUE == nav_is_component_visible(NAV_COMP_ID_REVOLT_INFO))
        {
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    ui1_new_state,
                                    !NEED_SHOW_BANNER_VIEW,
                                    !UP_TO_VIEW_AT_ONCE)) ;
        }
        else
        {
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    ui1_new_state,
                                    NEED_SHOW_BANNER_VIEW,
                                    !UP_TO_VIEW_AT_ONCE)) ;
        }
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_video_format_update
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_video_format_update (VOID *pv_arg1)
{
    NAV_STREAM_NOTIFY_DATA_T *pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T *)pv_arg1;
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("e_type = %d e_strm_type  = %d\n",pt_nfy_data->e_type,pt_nfy_data->e_strm_type)) ;
#if 0
    if(NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type && ST_AUDIO == pt_nfy_data->e_strm_type)
    {   
        banner_sys_audio_stream_update();
    }
#endif
	if((NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type && ST_VIDEO == pt_nfy_data->e_strm_type) || (NAV_SNT_STREAM_UPDATED == pt_nfy_data->e_type && ST_AUDIO == pt_nfy_data->e_strm_type))
    {   
        banner_sys_audio_stream_update();
    }


#if 0
    UINT8                       ui1_new_state = 0 ;
    CHAR                        s_disp_name[33] = {0};
    UINT8                       ui1_input_id = 0;
    ISL_REC_T                   t_isl_rec;


    NAV_STREAM_NOTIFY_DATA_T *pt_nfy_data = (NAV_STREAM_NOTIFY_DATA_T *)pv_arg1;

    /* get next state */
    BANNER_CHK_FAIL (_banner_custom_sync_state_when_svc_chg (FALSE, &ui1_new_state)) ;
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" ui1_new_state = %d\n ",ui1_new_state)) ;
    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);

    if (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
    {
        if (pt_nfy_data->e_type == NAV_SNT_STREAM_UPDATED && ST_VIDEO == pt_nfy_data->e_strm_type)
        {
            // not to show banner when update
        #if 0
            DBG_LOG_PRINT(("<zanchen>---%s: %d\r\n", __func__, __LINE__));
            BANNER_LOG_ON_FAIL (banner_change_state_to (
                                ui1_new_state,
                                NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE));
        #endif

        }
    }
#endif
    return NAVR_OK ;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_lock
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_lock (
    TV_WIN_ID_T                 e_tv_win_id,
    NAV_UI_MSG_ID_T             e_id
    )
{
    if (FALSE == _is_crnt_window (e_tv_win_id))
    {
        return NAVR_OK ;
    }
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("lock type  %s\n ",
                (NAV_UI_MSG_LOCKED_INP == e_id) ? "input source" :"channer or prog"));
    /* change to state SHOW_MSG and show "Channel locked" at once */
    BANNER_CHK_FAIL (banner_change_state_to (
                                (NAV_UI_MSG_LOCKED_INP == e_id)
                                ?   BANNER_STATE_IPTS          /* input source was locked */
                                :   BANNER_STATE_SHOW_MSG,    /* prog or ch was locked */
                                NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE)) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_unblock
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_unblock (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    if (FALSE == _is_crnt_window (e_tv_win_id))
    {
        return NAVR_OK ;
    }
    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("_crnt_source_is_tv  %s\n ",_crnt_source_is_tv () ? "YES":"NO"));
    /* unlock message state */
    BANNER_LOG_ON_FAIL (banner_unlock_state (BANNER_STATE_SHOW_MSG)) ;
    BANNER_LOG_ON_FAIL (banner_unlock_state (BANNER_STATE_IPTS)) ;

    
    BANNER_CHK_FAIL (banner_change_state_to (
                                (_crnt_source_is_tv ())
                                ? BANNER_STATE_VIRTUAL_TV_DEFAULT
                                : BANNER_STATE_IPTS ,
                                !NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE));
    
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_power_on
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_power_on (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    CHAR                        s_disp_name[33] = {0};
    UINT8                       ui1_input_id = 0;
    ISL_REC_T                   t_isl_rec;
    UTF16_T                     w2s_tv_cast_name[128+1] = {0};
    CHAR                        s_cast_name[128+1]={0};
    UINT32                      ui4_cast_name_len = 128+1;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);

    /*if power on action happen before select vtrl source,banner would show twice (soft power cycle case),so remove it
      And banner will be shown by source change when power on,not here
    */
    /*
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_VTRL &&
        t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
    {
        BANNER_LOG_ON_FAIL (banner_change_state_to (BANNER_STATE_IPTS, NEED_SHOW_BANNER_VIEW,
                                UP_TO_VIEW_AT_ONCE));
    }
    */
    
    /* get cast tv device name after power on or do server reset */
    //get apron_name first,if fail because no handle yet,then get cfg_name instead(need apron_name and cfg_name sync)
#ifdef A_C4TV_APRON_CAST_NAME
    if( (0 == a_c4tv_apron_get_cast_name(s_cast_name, &ui4_cast_name_len) && strlen(s_cast_name) > 0) || 
        (0 == a_cfg_custom_get_cast_name(s_cast_name, &ui4_cast_name_len) && strlen(s_cast_name) > 0) ||
        (0 == a_cfg_custom_get_tv_name(s_cast_name, &ui4_cast_name_len) && strlen(s_cast_name) > 0))
#else
    if( (0 == a_cfg_custom_get_tv_name(s_cast_name, &ui4_cast_name_len) && strlen(s_cast_name) > 0) || 
        (0 == a_cfg_custom_get_cast_name(s_cast_name, &ui4_cast_name_len) && strlen(s_cast_name) > 0) )
#endif
    {
        c_uc_ps_to_w2s(s_cast_name, w2s_tv_cast_name, sizeof(w2s_tv_cast_name));
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("get tv name \"%s\"\n ",s_cast_name));
        banner_view_update_item (BANNER_ITM_TV_NAME,w2s_tv_cast_name,
                           NULL_HANDLE, !UP_TO_VIEW_AT_ONCE);
    }
    else
    {
       DBG_LOG_PRINT(("[Banner V][%s %d] failed to get tv name \n ",__FUNCTION__,__LINE__));
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _banner_custom_handle_msg_svc_stopped
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _banner_custom_handle_msg_svc_stopped (
    TV_WIN_ID_T                 e_tv_win_id
    )
{
    banner_view_clean_av_item();
    banner_hide_msg();
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_allow_visible
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL banner_custom_allow_visible (VOID)
{
    CHAR             s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;
    TV_WIN_ID_T      e_tv_win_id ;

    do
    {
        if(nav_is_component_visible(NAV_COMP_ID_BANNER))
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("NAV_COMP_ID_BANNER is visibled .\n" ));
            break;
        }
        /* do NOT allow banner by other app */
        if (!a_tv_custom_get_banner_visiable_allow())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" do NOT allow banner by other app.\n" ));
            break;
        }

    #ifdef APP_MMP_SUPPORT
        /* do NOT allow banner while resuming mmp */
        if (a_menu_custom_is_resuming_mmp())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("do NOT allow banner by mmp. \n" ));
            break;
        }
    #endif

        /* pre power off */
        if (FALSE == a_am_is_power_on())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" pre power off. \n" ));
            break;
        }

        /* wizard was resumed, banner show NOT allow */
        a_am_get_active_app (s_active_app);
        if (c_strcmp(s_active_app, WZD_NAME) == 0)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" wizard was resumed. \n" ));
            break;
        }
    #ifdef APP_CAST_TV_MMP
        if (c_strcmp(s_active_app, MMP_NAME) == 0)
        {
            UINT8   ui1_resume_cond = ICL_RECID_MMP_RESUME_COND_FAILED;
            SIZE_T z_size = ICL_RECID_MMP_RESUME_COND_SIZE;

            a_icl_get(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_RESUME_COND),
                            &ui1_resume_cond,
                            &z_size);

            if(ui1_resume_cond == ICL_RECID_MMP_RESUME_COND_FAILED)  /* no mp4 file when in mmp */
            {
                BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" mmp was resumed. \n",  ));
                break;
            }
        }
    #endif
        a_am_get_next_active_app (s_active_app);
        if (c_strcmp(s_active_app, WZD_NAME) == 0)
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" wizard will resume. \n" ));
            break;
        }

        if (a_cfg_custom_get_wifi_remote_support())
        {
            if (!(a_dev_db_get_wifi_remote_banner_show_flag()))
            {
                BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" wifi remote not ready, and should not allow banner show \n")) ;
                break ;
            }
        }

        if (banner_is_under_excl ())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" banner was exclusived \r\n")) ;
            break ;
        }

        if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_BANNER_UI))
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" under ctrl: NAV_EXTERNAL_CTRL_RULE_NO_BANNER_UI \n")) ;
            break ;
        }

        if (nav_is_channel_scan_active ())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" in scan processing \n")) ;
            break ;
        }

        if (NAVR_OK == nav_get_focus_id (&e_tv_win_id)
            &&
            nav_is_svc_changing_with_keep_av (e_tv_win_id))
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" svc change with keep av, no banner display \n")) ;
            break ;
        }

        if (nav_is_component_visible(NAV_COMP_ID_UPDATER)||
            (NAV_COMP_ID_UPDATER == nav_get_active_component()))
        {
            DBG_LOG_PRINT(("\n[NAV_BANNER] banner_custom_allow_visible Reject[UPGRADE]\n"));
            break ;
        }

#ifdef APP_RETAIL_MODE_SUPPORT
        ACFG_RETAIL_MODE_T              t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
        NAV_RETAIL_MODE_STATUS_T        t_retail_status;

        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        a_nav_retail_mode_get_status(&t_retail_status);
        if((a_wzd_is_oobe_mode() == TRUE && t_retail_mode != ACFG_RETAIL_MODE_NORMAL) ||
            (ACFG_RETAIL_MODE_NORMAL == t_retail_mode &&
            (t_retail_status == NAV_RETAIL_MODE_LAUNCHING  ||
             t_retail_status == NAV_RETAIL_MODE_CHECKING   ||
             t_retail_status == NAV_RETAIL_MODE_RESTARTING ||
             t_retail_status == NAV_RETAIL_MODE_RUNNING)))
#else
        if(a_wzd_is_oobe_mode() == TRUE)
#endif
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" in oobe status, no banner display  or retail mode is runing\n" )) ;
            break ;
        }

        if(NAV_COMP_ID_INPUT_SRC == nav_get_active_component())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("if active comp is NAV_COMP_ID_INPUT_SRC , don't show info banner\n")) ;
            break ;
        }

        if (NAV_COMP_ID_TUNER_SETUP == nav_get_active_component())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" if active comp is NAV_COMP_ID_TUNER_SETUP , don't show info banner\n")) ;
            break ;
        }
        if (get_one_button_toast_state())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" if one button toast banner is showing , don't show info banner\n")) ;
            break ;
        }
#if 0
        if(_crnt_source_is_tv() && _crnt_svl_is_empty())
        {
            BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[banner view] current input source is TV but SVL is empty , don't show info banner\n")) ;
            break;
        }
#endif
        return TRUE ;

    }while (0) ;

    return FALSE ;
}

VOID nav_banner_set_from_info_key(BOOL  b_is_info_key)
{
    b_is_from_info_key = b_is_info_key;
}

BOOL nav_banner_get_from_info_key(VOID)
{
    return b_is_from_info_key;
}

VOID nav_banner_set_from_digit_pad_info_key(BOOL  b_is_info_key)
{
    b_is_from_digit_info_key = b_is_info_key;
}

BOOL nav_banner_get_from_digit_pad_info_key(VOID)
{
    return b_is_from_digit_info_key;
}

VOID nav_banner_set_from_channel_key(BOOL  b_is_channel_key)
{
    b_is_from_channel_key = b_is_channel_key;
}

BOOL nav_banner_get_from_channel_key(VOID)
{
    return b_is_from_channel_key;
}

VOID nav_banner_set_from_double_info_key(BOOL  b_is_double_info_key)
{
    b_is_from_double_info_key = b_is_double_info_key;
}

BOOL nav_banner_get_from_double_info_key(VOID)
{
    return b_is_from_double_info_key;
}

VOID nav_banner_set_hide_mode(BOOL  b_anim)
{
    b_ainm_hide_mode = b_anim;
}

BOOL nav_banner_get_hide_mode(VOID)
{
    return b_ainm_hide_mode;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_custom_rcu_key_handler (UINT32  ui4_key_code)
{
    UINT8   ui1_crnt_state = 0 ;
    BOOL    menu_visibility = FALSE;
    menu_main_get_visibility(&menu_visibility);

    nav_banner_set_from_info_key(FALSE);

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("rcu key receive : %s [0x%x] menu_visibility:%d\n",
                                GET_RCU_KEY_STRING(ui4_key_code), ui4_key_code,menu_visibility)) ;
    switch (ui4_key_code)
    {
    case BTN_CURSOR_UP :
    case BTN_CURSOR_DOWN :
        if(menu_visibility)
        {
            DBG_LOG_PRINT(("[banner key] %s %d no need handle it menu_visibility:%d\n",__FUNCTION__,__LINE__,menu_visibility));
            return NAVR_OK;
        }
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner msg] rcu key receive : %s [0x%x] \n",
                                GET_RCU_KEY_STRING(ui4_key_code), ui4_key_code)) ;

        if(FALSE == nav_is_component_visible (NAV_COMP_ID_BANNER))
        {
            /* banner is in-visible, do nothing */
            return NAVR_OK ;
        }

        BANNER_CHK_FAIL (banner_get_crnt_state (&ui1_crnt_state)) ;

        if (BANNER_STATE_PDCH != ui1_crnt_state)
        {
            /* is not program detail state, do NOT adjust the view */
            return NAVR_OK ;
        }

        if (BTN_CURSOR_UP == ui4_key_code)
        {
            BANNER_CHK_FAIL (_banner_custom_browse_detail_page (
                                BANNER_PROG_DETAIL_GOTO_PREV_PAGE)) ;
        }
        else
        {
            BANNER_CHK_FAIL (_banner_custom_browse_detail_page (
                                BANNER_PROG_DETAIL_GOTO_NEXT_PAGE)) ;
        }

        BANNER_LOG_ON_FAIL (a_banner_reset_state_timer()) ;
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[banner show] detail infor changed, update view \n")) ;
        BANNER_LOG_ON_FAIL (banner_view_refresh (UP_TO_VIEW_AT_ONCE)) ;
        break ;

    case BTN_PRG_INFO :
        {
            menu_blank_oled_scrn_timer_refresh();
            if(menu_custom_is_blank_screen())
            {
                menu_custom_unblank_screen(ui4_key_code);
                return NAVR_DO_NOT_CONTINUE;
            }
            /* for cover some case banner status has forget to reset  by other comps or apps */
            a_banner_set_excl_comp_on(FALSE);
            a_tv_custom_set_banner_visiable_allow(TRUE);

            if(!nav_is_component_visible(NAV_COMP_ID_BANNER) && !banner_custom_allow_visible())
            {
                BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("banner is not allow to show\n")) ;
                return NAVR_DO_NOT_CONTINUE;
            }

            if (b_g_is_virgin_banner)
            {
                /* set to STATE_NONE
                 * please note, DO NOT use STATE_IDLE, it will hide OSD immedietely
                 * READ SPECIAL_NOTE_2010_12_18_001 for details
                 */
                BANNER_LOG_ON_FAIL (banner_change_state_to (
                                    BANNER_STATE_NONE ,
                                    !NEED_SHOW_BANNER_VIEW,
                                    !UP_TO_VIEW_AT_ONCE)) ;
            }

            nav_banner_set_from_info_key(TRUE);
            /*
             *open menu in cast will make t_g_navigator.b_resume_from_app_switch == 1
             *then press info no banner come out,so set this value here to be 0
             */
            if(TRUE == _is_cnt_src_cast())
            {
                 TV_WIN_ID_T                e_tv_win_id = TV_WIN_ID_MAIN ;

                 nav_get_focus_id(&e_tv_win_id);
                 nav_check_to_reset_resume_from_app_switch_flag(e_tv_win_id);
            }
            banner_sys_info_update_hdr();
            banner_mm_try();
            BANNER_CHK_FAIL (_banner_custom_loop_next_state (ui4_key_code)) ;
            /* please NOTE,
             * banner will handle these two keys himself
             * use NAVR_DO_NOT_CONTINUE to notify navigator that
             * do NOT continue to dispath these key to other components
             */
            return NAVR_DO_NOT_CONTINUE ;
        }
#ifdef APP_TTS_SUPPORT
    case BTN_EXIT :
        if(TTS_STR_ST_PLAYING == a_app_tts_get_string_state())
        {
            a_app_tts_stop(APP_TTS_STOP_FORCE);
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("[banner tts]  exit key stop banner tts\n")) ;
        }

        break ;
#endif
    case BTN_PRG_DOWN:
    case BTN_PRG_UP:
    case BTN_PREV_PRG:
        banner_hide_msg();
    default :
        break ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_before_view_updated
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_custom_before_view_updated (
    BNR_ITEM_SET_T                    t_updated_mask
    )
{
    UINT8                       ui1_crnt_state = 0 ;

    if (t_updated_mask)
    {
        /* READ SPECIAL_NOTE_2010_12_18_001 for details */
        b_g_is_virgin_banner = FALSE ;
    }

    BANNER_CHK_FAIL (banner_get_crnt_state (&ui1_crnt_state)) ;

    /* if program detail information updated, update related items */
    if (NAV_BNR_STATE_IDX_TO_ID (BANNER_ITM_PROG_DETAIL) & t_updated_mask)
    {
        BANNER_CHK_FAIL (_banner_custom_browse_detail_page (
                                BANNER_PROG_DETAIL_GOTO_THIS_PAGE)) ;
    }

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_after_view_updated
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_custom_after_view_updated (
    BNR_ITEM_SET_T                    t_updated_mask
    )
{
    return NAVR_OK ;
}

INT32 banner_custom_handle_dt_event(VOID *arg1)
{
    NAV_UI_MSG_DT_COND_INFO_T* pt_dt = (NAV_UI_MSG_DT_COND_INFO_T*)arg1;

    BANNER_LOG(_BANNER_LOG_TYPE_MESSAGE,("e_cond = %d utc = %d\n",pt_dt->e_cond,pt_dt->t_delta));
    if(DT_SYNC_RUNNING == pt_dt->e_cond)
    {
         if(!(0 == a_nw_connection_test((CHAR*)"www.google.com") ||
               0 == a_nw_connection_test6((CHAR*)"www.google.com") ))
        {
            struct timeval tv;

            tv.tv_sec = c_dt_get_brdcst_utc(NULL,0);
            tv.tv_usec = 0;

            settimeofday(&tv,NULL);
        }
    }

    return NAVR_OK ;
}
/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL b_is_channel_change = FALSE;
INT32 banner_custom_handle_msg (NAV_UI_MSG_T*    pt_ui_msg,
                                VOID*            pv_arg1)
{
    NAV_UI_MSG_ID_T             e_id = (NAV_UI_MSG_AS_APP_PAUSED == pt_ui_msg->e_id) ? pt_ui_msg->e_id_as_paused: pt_ui_msg->e_id;
    INT32       i4_ret;
    
    /* do nothing when scan activate */
    if (nav_is_channel_scan_active ())
    {
        /* hide banner ui when scan channels */
        if (nav_is_component_visible(NAV_COMP_ID_BANNER))
        {
            BANNER_LOG_ON_FAIL (nav_hide_component (NAV_COMP_ID_BANNER)) ;
        }

        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,(" in scan processing \r\n")) ;
        return NAVR_OK ;
    }

    BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("%s(%d) start \n",GET_NAV_UI_MSG_STRING(e_id),e_id)) ;
    switch (e_id)
    {
    case NAV_UI_MSG_APP_PRE_RESUME:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        CHAR app[128] = {0};
        CHAR app_next[128] = {0};
        a_am_get_active_app(app);
        a_am_get_next_active_app(app_next);
         BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("active app is \"%s\" next active app is \"%s\"\n",app,app_next));
         if(strncmp(app,"menu",4) == 0 &&
            strncmp(app_next,"navigator",4) == 0)
         {
             b_g_is_menu_exit = TRUE;
         }
        /* READ SPECIAL_NOTE_2010_12_18_001 for details */
        b_g_is_virgin_banner = TRUE ;
        break;
    }
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = TRUE;
        b_is_need_show_banner_under_hdmi = TRUE;
        if(FALSE == b_g_is_banner_paused)
        {
            a_set_banner_enable(TRUE);
            BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_before_svc_change (
                                pt_ui_msg->e_tv_win_id)) ;
        }
        break ;

    case NAV_UI_MSG_AFTER_SVC_CHANGE:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_after_svc_change (
                                pt_ui_msg->e_tv_win_id)) ;
        b_is_need_show_banner_under_hdmi = FALSE;
        break ;

    case NAV_UI_MSG_BEFORE_SVCS_SWAP:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_before_svcs_swap (
                                pt_ui_msg->e_tv_win_id)) ;
        break;

    case NAV_UI_MSG_AFTER_SVCS_SWAP:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_after_svcs_swap (
                                pt_ui_msg->e_tv_win_id)) ;
        break ;

    case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_before_tv_mode_change (
                                pt_ui_msg->e_tv_win_id)) ;
        break ;

    case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_after_tv_mode_change (
                                pt_ui_msg->e_tv_win_id)) ;
        break ;

    case NAV_UI_MSG_EMPTY_SVL:
    case NAV_UI_MSG_EMPTY_SPECIFIED_CH_LIST:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_svl_is_empty (
                                pt_ui_msg->e_tv_win_id)) ;
        break ;

    case NAV_UI_MSG_FOCUS_CHANGED:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_focus_changed (
                                pt_ui_msg->e_tv_win_id)) ;
        break ;

    case NAV_UI_MSG_SHOW_BANNER:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_LOG_ON_FAIL (_banner_custom_handle_msg_show_banner (
                                pt_ui_msg->e_tv_win_id)) ;
        break;

    case NAV_UI_MSG_HIDE_BANNER:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_LOG_ON_FAIL (nav_hide_component (NAV_COMP_ID_BANNER)) ;
        break;

    case NAV_UI_MSG_HIDDEN_CH:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_CHK_FAIL (_banner_custom_handle_msg_hidden_ch (
                                pt_ui_msg->e_tv_win_id,
                                (BOOL)(UINT32)pv_arg1)) ;
        break ;

    case NAV_UI_MSG_EVENT_READY:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        BANNER_CHK_FAIL (_banner_custom_handle_msg_evt_ready (
                                pt_ui_msg->e_tv_win_id,
                                (BOOL)(UINT32)pv_arg1)) ;
        break ;

    case NAV_UI_MSG_AV_STATUS_NOTIFY:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_CHK_FAIL (_banner_custom_handle_msg_av_notify (
                                pt_ui_msg->e_tv_win_id,
                                (NAV_AV_STATUS_T)(UINT32)pv_arg1));
        break ;

    case NAV_UI_MSG_NO_SIGNAL:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_CHK_FAIL (_banner_custom_handle_msg_no_signal (
                                pt_ui_msg->e_tv_win_id));
        break ;

    case NAV_UI_MSG_WITH_SIGNAL:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_CHK_FAIL (_banner_custom_handle_msg_signal_captured (
                                pt_ui_msg->e_tv_win_id)) ;
        break ;

    case NAV_UI_MSG_LOCKED_CH:
    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_LOCKED_INP:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_CHK_FAIL (_banner_custom_handle_msg_lock (
                                pt_ui_msg->e_tv_win_id, e_id)) ;
        break ;
    case NAV_UI_MSG_UNLOCKED:
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_CHK_FAIL (_banner_custom_handle_msg_unblock (
                                pt_ui_msg->e_tv_win_id)) ;
        break ;
    case NAV_UI_MSG_POWER_ON:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
	BANNER_LOG_ON_FAIL (banner_change_state_to (
						BANNER_STATE_CH ,
						!NEED_SHOW_BANNER_VIEW,
						!UP_TO_VIEW_AT_ONCE)) ;
        BANNER_CHK_FAIL (_banner_custom_handle_msg_power_on (
                                pt_ui_msg->e_tv_win_id)) ;

        //start mm querry timer if need
        banner_view_mm_update_start_timer();
        break ;
    }
    //power off when play usb video,the resolution still remain in banner when power on again,so clear it when DC power off
    case NAV_UI_MSG_POWER_OFF:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        DBG_LOG_PRINT(("[banner res change] no need resolution now\n"));
        banner_view_update_item (BANNER_ITM_RESOLUTION_TXT, BANNER_TEXT(""), NULL_HANDLE, !UP_TO_VIEW_AT_ONCE);

        //stop mm querry timer
        banner_view_mm_update_stop_timer();

        break;
    }
    case NAV_UI_MSG_BEFORE_3RD_APP_START:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_g_banner_in_3rd = TRUE;
        break;//av items cleaned by mm update timer,no need handle here any more,so break
    }
    case NAV_UI_MSG_SVC_STOPPED:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        BANNER_CHK_FAIL (_banner_custom_handle_msg_svc_stopped (
                                pt_ui_msg->e_tv_win_id)) ;

        //for native app hot key in hdmi
        //wait changed to cast,then show banner
        if(_is_cnt_src_cast() && b_g_banner_in_3rd)
        {
            nav_show_banner_input_source_msg_hdlr();
        }
        
        break;
    }
    case NAV_UI_MSG_TV_SRC_CHANGED:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        /*if change channel very fast this msg maybe loss, this can cause tts can't read out
        *  banner when using number key change channel.
        */
        banner_view_tv_info_updeted_erase();
        break;
    }

    case NAV_UI_MSG_APP_RESUMED:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
#ifdef APP_TTS_SUPPORT

        /* pv_arg1 is BOOL type.  TRUE: Under power on state.  FALSE: Not under power on state. */
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("[BANNER TTS] NAV_UI_MSG_APP_RESUMED: %d! \n", (BOOL)((INT32)pv_arg1)));
#endif
        b_g_is_banner_paused = FALSE;
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("unset banner paused \n")) ;
    }
        break;

    case NAV_UI_MSG_STREAM_NOTIFY:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        b_is_channel_change = FALSE;
        _banner_custom_handle_msg_video_format_update((VOID *)pv_arg1);
        break;
    }
    case NAV_UI_MSG_OTHER_APP_PAUSED:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        CHAR        s_next_app_name[APP_NAME_MAX_LEN + 1] = {0};
        CHAR        s_act_app_name[APP_NAME_MAX_LEN + 1] = {0};

        b_is_channel_change = FALSE;
        if(strncmp((CHAR*)pv_arg1,"menu",4) == 0)
        {
            b_g_is_banner_paused = TRUE;
            BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("set banner paused \n")) ;
        }

        i4_ret = a_am_get_next_active_app(s_next_app_name);
		if(i4_ret != AMR_OK)
		{
			DBG_ERROR(("[banner rc]a_am_get_next_active_app failed\n"));
			return i4_ret;
		}
        i4_ret = a_am_get_active_app(s_act_app_name);
		if(i4_ret != AMR_OK)
		{
			DBG_ERROR(("[banner rc]a_am_get_next_active_app failed\n"));
			return i4_ret;
		}
		
        if(0 == c_strcmp(s_act_app_name, MSCVT_NAME))
        {
             b_g_banner_in_3rd = FALSE;
        }
        
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" next active app is \"%s\" act:%s next:%s \n",\
            (CHAR*)pv_arg1,s_act_app_name,s_next_app_name));
        
        break;
    }
    case NAV_UI_MSG_DT_CONDITION_CHANGE:
    {
        BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,(" \n"));
        banner_custom_handle_dt_event((VOID *)pv_arg1);
        break;
    }
    default :
        break ;
    }
     BANNER_LOG (_BANNER_LOG_TYPE_MESSAGE,("%s(%d) end \r\n",GET_NAV_UI_MSG_STRING(e_id),e_id)) ;
    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_get_idle_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UINT8 banner_custom_get_idle_state (VOID)
{
    return (UINT8)BANNER_STATE_IDLE ;
}



VOID banner_custom_set_ch_state (VOID)
{
    banner_change_state_to (BANNER_STATE_CH, FALSE, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_preset_data_when_nav_inited
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_custom_preset_data_when_nav_inited (VOID)
{
    /* set CH to default tv state */
    BANNER_CHK_FAIL (banner_set_default_tv_state (BANNER_STATE_CH)) ;

    /* clean all items on banner */
    _banner_custom_clean_all_items () ;

    /* set to idle state */
    BANNER_CHK_FAIL (banner_change_state_to(
                                BANNER_STATE_IDLE,
                                !NEED_SHOW_BANNER_VIEW,
                                !UP_TO_VIEW_AT_ONCE)) ;

    return NAVR_OK ;
}
extern INT32 nav_banner2_view_rc_create_siderbar_ui(HANDLE_T h_container);

/*-----------------------------------------------------------------------------
 * Name
 *      banner_custom_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 banner_custom_init (
    HANDLE_T                    h_parent,
    APP_COLOR_TYPE_T            e_color_type,
    BANNER_STATE_INFO_T**       pt_states_info,
    BANNER_ITEM_INFO_T**        pt_items_info,
    UINT16*                     pui2_state_num,
    UINT16*                     pui2_item_num,
    HANDLE_T*                   ph_root_frame
    )
{
    NAV_ASSERT      (   pt_states_info && pt_items_info &&
                        pui2_state_num && pui2_item_num && ph_root_frame) ;
    BANNER_CHK_FAIL ( ( pt_states_info && pt_items_info &&
                        pui2_state_num && pui2_item_num && ph_root_frame) ? NAVR_OK : NAVR_FAIL ) ;

    /* init images */
    BANNER_CHK_FAIL (nav_banner2_gen_init_image ()) ;

    /* prepare root frame call back function */
    BANNER_CHK_FAIL (nav_banner2_view_rc_reg_wgt_cb(WID_NAV_BANNER2_VIEW_RC_FRM_ROOT,
                                                     _banner_custom_root_frame_nfy_fct)) ;

    /* create banner view */
    BANNER_CHK_FAIL (nav_banner2_view_rc_create_ui (h_parent)) ;

    /* create banner siderbar view */
    BANNER_CHK_FAIL (nav_banner2_view_rc_create_siderbar_ui(h_parent));

    /* prepare items handle */
    BANNER_CHK_FAIL (_banner_custom_prepare_item_handle ()) ;

    /* prepare item images */
    BANNER_CHK_FAIL (_banner_custom_prepare_item_imgs ()) ;

    /* create banner timer */
    BANNER_CHK_FAIL (c_timer_create(&h_g_banner_timer));
    BANNER_CHK_FAIL (c_timer_create(&h_g_logo_delay_timer));

    /* init inem rect*/
    _banner_custom_init_item_rect();

    *pt_states_info = _t_g_states_info ;
    *pt_items_info  = _t_g_items_info ;
    *pui2_state_num = sizeof (_t_g_states_info)/sizeof(BANNER_STATE_INFO_T) ;
    *pui2_item_num  = sizeof (_t_g_items_info) /sizeof(BANNER_ITEM_INFO_T) ;
    *ph_root_frame  = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_FRM_ROOT) ;

    return NAVR_OK ;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
VOID nav_banner_ipts_show_itm(VOID){}

VOID nav_banner_ipts_hide_itm(VOID){}

VOID nav_banner_scr_mode_show_itm(VOID){}

VOID nav_banner_scr_mode_hide_itm(VOID){}

extern WGL_HIMG_TPL_T h_g_nav_cc_on_img ;
extern WGL_HIMG_TPL_T h_g_nav_cc_off_img ;

VOID nav_banner_set_cc_state(BOOL b_on,BOOL visiable)
{
    HANDLE_T h_cc_icon = visiable == FALSE ? NULL_HANDLE :
                         b_on     == TRUE ? h_g_nav_cc_on_img : h_g_nav_cc_off_img ;

    banner_view_update_item(BANNER_ITM_CAPTION_ICON,NULL,h_cc_icon,FALSE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_banner_cc_itm_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_banner_cc_itm_hide(VOID)
{
    HANDLE_T    h_tmp;

    h_tmp = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CAPTION) ;
    c_wgl_set_visibility(h_tmp,WGL_SW_HIDE_RECURSIVE);
    c_wgl_repaint(h_tmp,NULL,TRUE);

    h_tmp = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_ICON_ITM_CAPTION_ICON) ;
    c_wgl_set_visibility(h_tmp,WGL_SW_HIDE_RECURSIVE);
    c_wgl_repaint(h_tmp,NULL,TRUE);

    h_tmp = nav_banner2_view_rc_get_wgt_hdl (WID_NAV_BANNER2_VIEW_RC_TXT_ITM_VIDEO_INFO) ;
    c_wgl_set_visibility(h_tmp,WGL_SW_NORMAL);
    c_wgl_repaint(h_tmp,NULL,TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _nav_ttx_cfg_change_msg_hdlr
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_show_banner_msg_hdlr(
    VOID*                               pv_ui2_id,
    VOID*                               pv_unused1,
    VOID*                               pv_unused2)
{
    if(a_banner_allow_to_show() && !banner_view_is_on_show() && !_crnt_source_is_virtual_input())
    {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("external function call banenr show . \n" ));

        banner_view_clean_av_item();
        banner_hide_msg();

        banner_change_state_to (
                            BANNER_STATE_CH,
                            FALSE,
                            TRUE);
        a_banner_allow_to_show();
        banner_view_set_visible(TRUE);
        nav_bnr_timer_reload(NULL_HANDLE,0,(NAV_BNR_STATE_TIMER_OPER_TYPE_T)0);
    }

}

UINT32  a_nav_set_show_banner_expecial_btn(BOOL b_show)
{
    b_g_is_show_by_specia_btn = b_show;
    return NAVR_OK;

}
BOOL  a_nav_get_show_banner_expecial_btn(VOID)
{
    return b_g_is_show_by_specia_btn;
}

UINT32  a_nav_show_banner_ex(VOID)
{
    /*post a message to itself*/
    nav_request_context_switch(_nav_show_banner_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);
    return NAVR_OK;
}

VOID nav_banner_set_from_ch_num_key(BOOL  b_is_ch_num_key)
{
    b_is_ch_num_info_key = b_is_ch_num_key;
}

BOOL nav_banner_get_from_ch_num_key(VOID)
{
    return b_is_ch_num_info_key;
}

static VOID _banner_custom_update_logo_timer (
    VOID*                       pv_tag,
    VOID*                       pv_unused1,
    VOID*                       pv_unused2)
{
    TV_WIN_ID_T                     e_win_id = TV_WIN_ID_MAIN ;
    VSH_SRC_RESOLUTION_INFO_T       t_video_resolution = {0};
    HANDLE_T                        h_svctx = NULL_HANDLE;
    INT32                           i4_ret;
    BANNER_SIDERBAR_LOGO            e_type = (BANNER_SIDERBAR_LOGO)pv_tag;
    i4_ret = nav_get_focus_id (&e_win_id) ;
    if (i4_ret != NAVR_OK)
    {
        return;
    }
    i4_ret = nav_get_svctx_handle(e_win_id, &h_svctx);
    if (i4_ret != NAVR_OK)
    {
        return;
    }
    c_memset (&t_video_resolution, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));
    i4_ret = c_svctx_get_video_src_resolution(h_svctx, &t_video_resolution);
    if (i4_ret == NAVR_OK)
    {
        DBG_LOG_PRINT((" %s %d ui4_height:%d \n",__FUNCTION__,__LINE__,t_video_resolution.ui4_height));
        if(t_video_resolution.ui4_height > 0)
        {
            DBG_LOG_PRINT((" %s %d show logo:%d \n",__FUNCTION__,__LINE__,e_type));
            banner_show_siderbar_logo(e_type);
        }
    }
}

static VOID _banner_custom_update_logo_timer_nfy(
    HANDLE_T                    h_timer,
    VOID*                       pv_tag
    )
{
    /* execute in timer's thread context */
    BANNER_LOG_ON_FAIL (nav_request_context_switch(
                                _banner_custom_update_logo_timer,
                                pv_tag,
                                NULL,
                                NULL));
}

VOID a_banner_custom_update_logo_for_gll(BANNER_SIDERBAR_LOGO e_type,UINT32 delay_time)
{
    banner_view_update_logo_flag(e_type);
    BANNER_LOG_ON_FAIL (c_timer_stop (h_g_logo_delay_timer));
    BANNER_LOG_ON_FAIL (c_timer_start (
                    h_g_logo_delay_timer, delay_time, X_TIMER_FLAG_ONCE,
                   _banner_custom_update_logo_timer_nfy, (VOID *)e_type));
}

static VOID _nav_show_detail_banner_msg_hdlr(
    VOID*                               pv_ui2_id,
    VOID*                               pv_unused1,
    VOID*                               pv_unused2)
{
    if(a_banner_allow_to_show() && !banner_view_is_on_show() && !_crnt_source_is_virtual_input())
    {
        BANNER_LOG (_BANNER_LOG_TYPE_VIEW,("external function call detail banner show . \n" ));

        nav_banner_set_from_info_key(TRUE);
        nav_banner_set_from_digit_pad_info_key(TRUE);
        banner_sys_info_update_hdr();
        banner_mm_try();
        BANNER_CHK_FAIL (_banner_custom_loop_next_state (BTN_PRG_INFO)) ;


        DBG_LOG_PRINT((" %s %d show banner \n",__FUNCTION__,__LINE__));
    }

}

UINT32  a_nav_show_detail_banner_ex(VOID)
{
    nav_request_context_switch(_nav_show_detail_banner_msg_hdlr,
                               NULL,
                               NULL,
                               NULL);
    return NAVR_OK;
}


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
#ifndef __NAV_BANNER2_VIEW_RC_LAYOUT_H__
#define __NAV_BANNER2_VIEW_RC_LAYOUT_H__

#include "wdk/wdk_api.h"
#include "c_os.h"

#include "nav_banner2_gen_img.h"
#include "nav_banner2_gen_clr.h"
#include "nav_banner2_mlm.h"
#include "nav_banner2_gen_font_info.h"

enum
{
    WID_NAV_BANNER2_VIEW_RC_FRM_ROOT,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_TITLE,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_INPUT_CH_NO,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TV_NAME,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NO,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CH_NAME,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_CRNT_TIME,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RATING,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_CAPTION_ICON,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_CAPTION,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_INFO_LANG,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_VIDEO_INFO,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_UP,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL_PG_IDX,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_PROG_DETAIL_PG_DN,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_DETAIL,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_MSG,
    WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PDCH,
    WID_NAV_BANNER2_VIEW_RC_FRM_ITM_PCH,
    WID_NAV_BANNER2_VIEW_RC_FRM_ITM_CH,
    WID_NAV_BANNER2_VIEW_RC_FRM_ITM_3D,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_MODE,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_3D_FMT,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TITLE,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_PROG_NEXT_TIME,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_TV_LOCK,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_AD_EYE,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_IPTS_LOCK,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_INPUT,
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_WIFI,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_ASPECT,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_WIFI_TXT,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_FORMAT,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_TIMER_24,
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_RESOLUTION,

    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_VISION,

    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_DOLBY_AUDIO,
#if (CUSTOMER == VIZIO)
    WID_NAV_BANNER2_VIEW_RC_ICON_ITM_HEADPHONES,
#endif
    WID_NAV_BANNER2_VIEW_RC_TXT_ITM_AUDIO_OUT,
    WID_NAV_BANNER2_VIEW_RC_TOTAL_COUNT
};

/*side bar*/
enum{
    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_FRM_SIDER_BAR,
    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR,

    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_VISION,//DV logo
    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_AUDIO,//DD/atmos

    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_PROGAMING_ENGINE,//progaming engine
    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FILMMAKER_MODE,//Filmmaker mode logo
    
    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_FREESYNC,//freesync
    WID_NAV_BANNER2_SIDERBAR_VIEW_RC_TOTAL_COUNT
};
INT32 nav_banner2_view_rc_clr_wgt_cb(VOID);
INT32 nav_banner2_view_rc_reg_wgt_cb(UINT32 e_widget_id, wgl_widget_proc_fct p_cb);

INT32 nav_banner2_view_rc_create_ui(HANDLE_T h_container);
HANDLE_T nav_banner2_view_rc_get_wgt_hdl(UINT32 e_widget_id);
INT32 nav_banner2_view_rc_update_text(UINT16 ui2_lang);
INT32 nav_banner2_view_rc_destroy_ui(VOID);

INT32 nav_banner2_view_rc_create_ui_mi(HANDLE_T h_container, WDK_UI_MI_T *ph_mi);
HANDLE_T nav_banner2_view_rc_get_wgt_hdl_mi(UINT32 e_widget_id, WDK_UI_MI_T h_mi);
INT32 nav_banner2_view_rc_update_text_mi(UINT16 ui2_lang, WDK_UI_MI_T t_mi);
INT32 nav_banner2_view_rc_destroy_ui_mi(WDK_UI_MI_T h_mi);
extern GL_RECT_T* nav_banner2_view_rc_get_wgt_rect(UINT8 u1_item_id);
extern UINT32 nav_banner2_view_rc_get_wgt_default_width(UINT8 u1_item_id);

extern HANDLE_T nav_banner2_view_rc_get_siderbar_wgt_hdl(UINT32 e_widget_id);
extern GL_RECT_T* nav_banner2_view_rc_get_siderbar_frm_rect(void);
extern GL_RECT_T* nav_banner2_view_rc_get_siderbar_item_rect(UINT8 index);


#endif /* __NAV_BANNER2_VIEW_RC_LAYOUT_H__ */

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
 * $RCSfile: nav_info_bar_view_rc.h,v $
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
 
#ifndef _MMP_INFO_BAR_RC_H_
#define _MMP_INFO_BAR_RC_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    resource define
-----------------------------------------------------------------------------*/

typedef struct _MMP_INFO_BAR_RC_T
{
    /*image template*/
    WGL_HIMG_TPL_T              h_fm_bk_img;
    WGL_HIMG_TPL_T              h_info_img;
    WGL_HIMG_TPL_T              h_warning_img;
    WGL_HIMG_TPL_T              h_urgent_img;
} MMP_INFO_BAR_RC_T;

typedef struct
{
    MMP_IB_STATUS_MSG_TYPE_T    e_msg_type;
    MMP_IB_STATUS_MSG_ID_T      e_msg_id;
    UINT32                      ui4_timeout_duration;  /* apply in edge trigger only. */
    BOOL                        b_hide_when_svc_chg;   /* apply in edge trigger only. */
} MMP_INFO_BAR_RC_MSG_SETTING_T;

/*-----------------------------------------------------------------------------
                    behavior
-----------------------------------------------------------------------------*/
                                             
/*-----------------------------------------------------------------------------
                    key
 ----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    message box
 ----------------------------------------------------------------------------*/

/*frame*/
#define MMP_INFO_BAR_STATUS_FM_W             ((INT32) 410*2)//((INT32) 410*4/3)
#define MMP_INFO_BAR_STATUS_FM_H             ((INT32) 104*2) //((INT32) 104*4/3) /* dynamically layout based on the content 1 line or 2 lines */
#define MMP_INFO_BAR_STATUS_FM_X             ((INT32) 270*2)//((INT32) 270*4/3)
#define MMP_INFO_BAR_STATUS_FM_Y             ((INT32) 100*2)//((INT32) 100*4/3)
#define MMP_INFO_BAR_STATUS_FM_STYLE         (NULL)
#define MMP_INFO_BAR_STATUS_LINE_OFFSET      ((INT32) 40*4/3)

#define MMP_INFO_BAR_STATUS_AUDIO_FM_W             ((INT32) 410*2)//((INT32) 410*4/3)
#define MMP_INFO_BAR_STATUS_AUDIO_FM_H             ((INT32) 104*2)//((INT32) 104*4/3)
#define MMP_INFO_BAR_STATUS_AUDIO_FM_X             ((INT32) 720*2)//((INT32) 720*4/3)
#define MMP_INFO_BAR_STATUS_AUDIO_FM_Y             ((INT32) 48*2)//((INT32) 48*4/3)

#define MMP_INFO_BAR_STATUS_VIDEO_FM_W             ((INT32) 410*2)//((INT32) 410*4/3)
#define MMP_INFO_BAR_STATUS_VIDEO_FM_H             ((INT32) 104*2)//((INT32) 104*4/3)
#define MMP_INFO_BAR_STATUS_VIDEO_FM_X             ((INT32) 320*2)//((INT32) 320*4/3)
#define MMP_INFO_BAR_STATUS_VIDEO_FM_Y             ((INT32) 48*2)//((INT32) 48*4/3)

/*icon (patent: frame) */
#define MMP_INFO_BAR_STATUS_ICON_W           ((INT32) 36*4/3)
#define MMP_INFO_BAR_STATUS_ICON_H           ((INT32) 36*4/3)
#define MMP_INFO_BAR_STATUS_ICON_X           ((INT32) 12*4/3)
#define MMP_INFO_BAR_STATUS_ICON_Y           ((INT32) 12*4/3)
#define MMP_INFO_BAR_STATUS_ICON_STYLE       (WGL_STL_GL_NO_BK)
#define MMP_INFO_BAR_STATUS_ICON_ALIGN       (WGL_AS_CENTER_CENTER)

/*text (patent: frame) */
#define MMP_INFO_BAR_STATUS_TXT_W            ((INT32) MMP_INFO_BAR_STATUS_FM_W- 56)
#define MMP_INFO_BAR_STATUS_TXT_H            ((INT32) MMP_INFO_BAR_STATUS_FM_H)
#define MMP_INFO_BAR_STATUS_TXT_X            ((INT32) 56*4/3)
#define MMP_INFO_BAR_STATUS_TXT_Y            ((INT32) 0)
#define MMP_INFO_BAR_STATUS_TXT_INSET_LEFT   ((INT32) 0)
#define MMP_INFO_BAR_STATUS_TXT_INSET_RIGHT  ((INT32) 0)
#define MMP_INFO_BAR_STATUS_TXT_INSET_TOP    ((INT32) 12*4/3)
#define MMP_INFO_BAR_STATUS_TXT_INSET_BOTTOM ((INT32) 12*4/3)
#define MMP_INFO_BAR_STATUS_TXT_STYLE        (WGL_STL_GL_NO_BK | WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_512)
#define MMP_INFO_BAR_STATUS_TXT_ALIGN        (WGL_AS_LEFT_TOP)
#define MMP_INFO_BAR_STATUS_TXT_LINE_GAP     ((INT32) 4*4/3)


/*-----------------------------------------------------------------------------
                    alpha
 ----------------------------------------------------------------------------*/
#define MMP_INFO_BAR_DEFAULT_ALPHA           240

/*-----------------------------------------------------------------------------
                    color
 ----------------------------------------------------------------------------*/    

/*-----------------------------------------------------------------------------
                    font
-----------------------------------------------------------------------------*/

#define MMP_INFO_BAR_STATUS_FONT_SIZE                            FE_FNT_SIZE_SMALL
#define MMP_INFO_BAR_STATUS_FONT_STYLE                           FE_FNT_STYLE_REGULAR
#define MMP_INFO_BAR_STATUS_FONT_NAME                            SN_FONT_DEFAULT

/*-----------------------------------------------------------------------------
                    variable
-----------------------------------------------------------------------------*/
#if 0
extern MMP_INFO_BAR_RC_MSG_SETTING_T at_g_ib_msg_settings[];
extern UINT16                       ui2_ib_msg_settings_num;
#endif
/*-----------------------------------------------------------------------------
                    function
-----------------------------------------------------------------------------*/

extern INT32 mmp_info_bar_rc_init(MMP_INFO_BAR_RC_T*  pt_rc);

#endif /*_MMP_INFO_BAR_RC_H_*/

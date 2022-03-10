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
 * $RCSfile: npg.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------- 
                    include files 
-----------------------------------------------------------------------------*/ 
#include "mmp/mmp_common.h"
#include "u_scc.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_fe.h"
#include "c_os.h"

#include "mmp/common_ui2/mmp_info_bar.h"
#include "res/mmp/common_ui/mmp_info_bar_rc.h"
#include "res/fonts/a_font_custom.h"
#include "res/mmp/gen/mmp_gen_img.h"
/*----------------------------------------------------------------------------- 
                    customizable macros 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    macros, defines 
----------------------------------------------------------------------------*/ 

#define DEFAULT_SETTING_TIMEOUT                     (5000)   /* ms */
#define DEFAULT_HDMI_SIGNAL_DETECTING_TIMEOUT       (10000)  /* ms */
#define DEFAULT_HDMI_SIGNAL_AUD_NON_SUPPORT_TIMEOUT (10000)  /* ms */

/*----------------------------------------------------------------------------- 
                    typedefs, enums, structures 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    function declarations 
----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    data, variable declarations 
-----------------------------------------------------------------------------*/ 


/* This table provides the timeout definition to the "EDGE" type messages. */
#if 0
MMP_IB_VIEW_RC_MSG_SETTING_T at_g_ib_msg_settings[] =
{
    /* MSG_TYPE                                  MSG_ID                                       DURATION                               HIDE_WHEN_SVC_CHG */
    { MMP_IB_STATUS_MSG_TYPE_GENERAL_SETTING   , MMP_IB_STATUS_MSG_ID_USER_SETTING_1        , DEFAULT_SETTING_TIMEOUT,                     TRUE },
    { MMP_IB_STATUS_MSG_TYPE_GENERAL_SETTING   , MMP_IB_STATUS_MSG_ID_USER_SETTING_2        , DEFAULT_SETTING_TIMEOUT,                     TRUE },
    { MMP_IB_STATUS_MSG_TYPE_GENERAL_SETTING   , MMP_IB_STATUS_MSG_ID_USER_SETTING_3        , DEFAULT_SETTING_TIMEOUT,                     TRUE },
    { MMP_IB_STATUS_MSG_TYPE_CI_COND           , MMP_IB_STATUS_MSG_ID_CI_COND               , DEFAULT_SETTING_TIMEOUT,                     TRUE },
    { MMP_IB_STATUS_MSG_TYPE_HDMI_SIGNAL_STATUS, MMP_IB_STATUS_MSG_ID_HDMI_DETECTING        , DEFAULT_HDMI_SIGNAL_DETECTING_TIMEOUT,       TRUE },
    { MMP_IB_STATUS_MSG_TYPE_HDMI_SIGNAL_STATUS, MMP_IB_STATUS_MSG_ID_HDMI_AUDIO_NON_SUPPORT, DEFAULT_HDMI_SIGNAL_AUD_NON_SUPPORT_TIMEOUT, TRUE },    
};
UINT16                       ui2_ib_msg_settings_num = (UINT16)(sizeof(at_g_ib_msg_settings)/sizeof(at_g_ib_msg_settings[0]));
#endif
/*----------------------------------------------------------------------------- 
                    private function implementations 
-----------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------- 
                    public function implementations 
-----------------------------------------------------------------------------*/ 

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 mmp_info_bar_rc_init(MMP_INFO_BAR_RC_T*  pt_rc)
{
    if (pt_rc == NULL)
    {
        return MMPR_FAIL;
    }
    
    c_memset (pt_rc, 0, sizeof(MMP_INFO_BAR_RC_T));

    /* fm bk */
    pt_rc->h_fm_bk_img = h_g_mmp_info_bar_bg;
        

    /* info bk */
    pt_rc->h_info_img = h_g_mmp_icon_info;

    /* warning bk */
    pt_rc->h_warning_img = h_g_mmp_icon_warning;

    /* urgent bk */
    pt_rc->h_urgent_img = h_g_mmp_icon_urgent;
    
    
    return MMPR_OK;
}

/*----------------------------------------------------------------------------- 
                    export function implementations 
-----------------------------------------------------------------------------*/

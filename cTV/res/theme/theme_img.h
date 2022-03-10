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
 * $RCSfile: theme_img.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/8 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: fad6e0fd4edaccd0084a192f40b2c916 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _THEME_IMG_H_
#define _THEME_IMG_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_common.h"
#include "c_dbg.h"
#include "u_wgl.h"
#include "c_wgl.h"
#include "u_wgl_sets.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#ifdef DEBUG
    #define THEME_ASSERT( condition )                                         \
    {                                                                       \
        if (!(condition))                                                   \
        {                                                                   \
            DBG_LOG_PRINT(("\n File : %s, Line : %d ", __FILE__, __LINE__));     \
            DBG_ABORT(DBG_MOD_APPL);                                        \
        }                                                                   \
    }
    #define IS_THEME_OK(i4_ret)                                              \
    {                                                                       \
        INT32                  _i4_ret = (i4_ret);                         \
        if (THEME_OK != _i4_ret)                                             \
        {                                                                   \
            DBG_LOG_PRINT(("\r\n[!!!Return fail:%s:%s:%d:%d]\r\n", __FILE__, __FUNCTION__, __LINE__, _i4_ret));   \
            return _i4_ret ;                                                \
        }                                                                   \
    }
#else
    #define THEME_ASSERT( condition )              if (!(condition)){}
    #define IS_THEME_OK(i4_ret)                                              \
    {                                                                       \
        INT32                  _i4_ret = (i4_ret);                         \
        if (THEME_OK != _i4_ret)                                             \
        {                                                                   \
            return _i4_ret ;                                                \
        }                                                                   \
    }
#endif



#define THEME_W      1
#define THEME_H      1


#define     THEME_OK                 ((INT32)  0)
#define     THEME_FAIL               ((INT32) -1)
#define     THEME_INV_ARG        ((INT32)  -2)

#define  TIME_ZONE_ICON_X                               (40 * THEME_W)
#define  TIME_ZONE_ICON_Y                               (40 * THEME_H)
#define  TIME_ZONE_ICON_W                               (300 * THEME_W)
#define  TIME_ZONE_ICON_H                               (274 * THEME_H)
#define  TIME_ZONE_ICON_MENU_X                          (80  * THEME_W)


typedef enum _THEME_IMG_IMAGE_ID_T
{
    THEME_IMG_TIME_ZONE_ICON_EAS = 0,
    THEME_IMG_TIME_ZONE_ICON_IND,
    THEME_IMG_TIME_ZONE_ICON_CEN,
    THEME_IMG_TIME_ZONE_ICON_MNT,
    THEME_IMG_TIME_ZONE_ICON_ARI,
    THEME_IMG_TIME_ZONE_ICON_PAC,
    THEME_IMG_TIME_ZONE_ICON_ALA,
    THEME_IMG_TIME_ZONE_ICON_HAW,

    THEME_IMG_TIME_ZONE_ICON_DISABLE = 100,

} THEME_IMG_IMAGE_ID_T;

extern INT32 theme_img_init(VOID);
extern INT32 theme_img_deinit(VOID);
extern INT32 theme_time_zone_get_img(UINT16 ui2_idx, WGL_HIMG_TPL_T* ph_img_tpl);
extern INT32 theme_time_zone_create_icon_widget(HANDLE_T        h_parent,
                                                WGL_HIMG_TPL_T  h_img,
                                                GL_RECT_T       t_icon_rect,
                                                HANDLE_T*       ph_icon);
extern INT32 theme_time_zone_load_icon(HANDLE_T  h_icon, UINT16 ui2_idx, BOOL b_repaint);
#endif /* _THEME_IMG_H_ */

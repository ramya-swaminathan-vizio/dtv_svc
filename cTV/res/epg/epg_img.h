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
 * $RCSfile: epg_img.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 80d824ab48f4d49e3d38d28c8fc07509 $
 *
 * Description:
 *      This file contains the images used by the EPG application.
 *---------------------------------------------------------------------------*/

#ifndef _EPG_IMG_H_
#define _EPG_IMG_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "c_wgl_image.h"

#include "app_util/a_common.h"


/*
   External variables.
*/
extern WGL_HIMG_TPL_T      h_g_epg_img_btn_red;               /* red button */
extern WGL_HIMG_TPL_T      h_g_epg_img_btn_green;             /* green button */
extern WGL_HIMG_TPL_T      h_g_epg_img_btn_yellow;            /* yellow button */
extern WGL_HIMG_TPL_T      h_g_epg_img_btn_blue;              /* blue button */

extern WGL_HIMG_TPL_T      h_g_epg_img_program_frm;           /* program frame */
extern WGL_HIMG_TPL_T      h_g_epg_img_video_frm;             /* video frame */
extern WGL_HIMG_TPL_T      h_g_epg_img_base_map;              /* base map */
extern WGL_HIMG_TPL_T      h_g_epg_img_scroll_bar;

extern WGL_HIMG_TPL_T      h_g_epg_img_caption;               /* caption */
extern WGL_HIMG_TPL_T      h_g_epg_img_caption_hlt;           /* highlighted caption*/
extern WGL_HIMG_TPL_T      h_g_epg_img_caption_hlt_uf;        /* highlighted unfocused caption */
extern WGL_HIMG_TPL_T      h_g_epg_img_lock;                  /* lock */
extern WGL_HIMG_TPL_T      h_g_epg_img_lock_hlt;              /* highlighted lock */
extern WGL_HIMG_TPL_T      h_g_epg_img_lock_hlt_uf;           /* highlighted unfocused lock */
extern WGL_HIMG_TPL_T      h_g_epg_img_arrow_left;            /* arrow left */
extern WGL_HIMG_TPL_T      h_g_epg_img_arrow_right;           /* arrow right */
extern WGL_HIMG_TPL_T      h_g_epg_img_arrow_up_enable;       /* highlight-enabled arrow up */
extern WGL_HIMG_TPL_T      h_g_epg_img_arrow_up_disable;      /* highlight-disabled arrow up */
extern WGL_HIMG_TPL_T      h_g_epg_img_arrow_down_enable;     /* highlight-enabled arrow down */
extern WGL_HIMG_TPL_T      h_g_epg_img_arrow_down_disable;    /* highlight-disabled arrow down */
extern WGL_HIMG_TPL_T      h_g_epg_img_trans;                 /* fully transparent image */

extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_1;            /* retrieving state 1 */
extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_2;            /* retrieving state 2 */
extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_3;            /* retrieving state 3 */
extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_4;            /* retrieving state 4 */
extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_5;            /* retrieving state 5 */
extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_6;            /* retrieving state 6 */
extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_7;            /* retrieving state 7 */
extern WGL_HIMG_TPL_T      h_g_epg_img_retrieve_8;            /* retrieving state 8 */

/* API's */
extern INT32 epg_image_init (VOID);

#endif /* _EPG_IMG_H_ */

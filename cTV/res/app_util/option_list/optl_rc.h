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
 * $RCSfile: optl_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _OPTL_RC_H
#define _OPTL_RC_H
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_image.h"
#include "u_irrc_btn_def.h"

#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    behavior
-----------------------------------------------------------------------------*/
#define OPTL_GUI_AUTHORING
/*-----------------------------------------------------------------------------
                    dimension
-----------------------------------------------------------------------------*/
#define OPTL_LIST_FONT_SIZE             FE_FNT_SIZE_SMALL

#define OPTL_LB_DSP_ITEM_MAX_NUM               6

#define OPTL_LB_HLT_MARGIN                     1

#define OPTL_SCREEN_WIDTH               NAV_WIDTH(852)
#define OPTL_SCREEN_HEIGHT              NAV_HEIGHT(480)

/*frame*/
#define OPTL_FRAME_WIDTH                NAV_WIDTH(573)
#define OPTL_FRAME_HEIGHT               NAV_HEIGHT(326)

/*Main option list frame*/
#define OPTL_FRAME_MAIN_WIDTH           NAV_WIDTH(220)
#define OPTL_FRAME_MAIN_HEIGHT          OPTL_FRAME_HEIGHT
#define OPTL_FRAME_MAIN_LEFT            NAV_WIDTH(0)
#define OPTL_FRAME_MAIN_TOP             NAV_HEIGHT(0)

#define OPTL_FRAME_MAIN_WITH_ARROW_TOP  NAV_HEIGHT(31)

/* Set element of list box*/
#define OPTL_LB_ELEM_HEIGHT             NAV_HEIGHT(47)
#define OPTL_LB_ELEM_DTANCE             NAV_HEIGHT(0)

/*Main option list content inset*/
#define OPTL_LB_MAIN_CNT_LEFT_INSET     NAV_WIDTH(0)
#define OPTL_LB_MAIN_CNT_RIGHT_INSET    NAV_WIDTH(0)
#define OPTL_LB_MAIN_CNT_TOP_INSET      NAV_HEIGHT(8)
#define OPTL_LB_MAIN_CNT_BOTTOM_INSET   NAV_HEIGHT(8)

/*Main option list element inset*/
#define OPTL_LB_MAIN_ELM_LEFT_INSET     NAV_WIDTH(0)
#define OPTL_LB_MAIN_ELM_RIGHT_INSET    NAV_WIDTH(0)
#define OPTL_LB_MAIN_ELM_TOP_INSET      NAV_HEIGHT(0)
#define OPTL_LB_MAIN_ELM_BOTTOM_INSET   NAV_HEIGHT(0)

/*Main option list column inset*/
#define OPTL_LB_MAIN_TXT_LEFT_INSET     NAV_WIDTH(8)
#define OPTL_LB_MAIN_TXT_RIGHT_INSET    NAV_WIDTH(8)
#define OPTL_LB_MAIN_TXT_TOP_INSET      NAV_HEIGHT(0)
#define OPTL_LB_MAIN_TXT_BOTTOM_INSET   NAV_HEIGHT(0)

/*Main option list box*/
#define OPTL_LB_MAIN_LEFT               NAV_WIDTH(6)
#define OPTL_LB_MAIN_WIDTH              (OPTL_FRAME_MAIN_WIDTH - NAV_WIDTH(6))
#define OPTL_LB_MAIN_HEIGHT             (OPTL_LB_DSP_ITEM_MAX_NUM * (OPTL_LB_ELEM_DTANCE + OPTL_LB_ELEM_HEIGHT) - \
                                         OPTL_LB_ELEM_DTANCE + \
                                         OPTL_LB_MAIN_CNT_TOP_INSET + OPTL_LB_MAIN_CNT_BOTTOM_INSET)
#define OPTL_LB_MAIN_TOP                NAV_HEIGHT(18)

/*Main option list box text*/
#define OPTL_LB_LABEL_WIDTH              (80)
#define OPTL_LB_MAIN_TXT_WIDTH          (OPTL_LB_MAIN_WIDTH - OPTL_LB_MAIN_TXT_LEFT_INSET - OPTL_LB_MAIN_TXT_RIGHT_INSET - OPTL_LB_LABEL_WIDTH)

#define OPTL_LB_LABEL_ALIGHMENT         WGL_AS_RIGHT_CENTER
#define OPTL_LB_MAIN_TXT_ALIGNMENT      WGL_AS_CENTER_CENTER

/*Sub option list frame*/
#define OPTL_FRAME_SUB_WIDTH            NAV_WIDTH(200)
#define OPTL_FRAME_SUB_HEIGHT           OPTL_FRAME_HEIGHT
#define OPTL_FRAME_SUB_LEFT             OPTL_FRAME_MAIN_WIDTH
#define OPTL_FRAME_SUB_TOP              NAV_HEIGHT(0)

#define OPTL_FRAME_SUB_WITH_ARROW_TOP   OPTL_FRAME_MAIN_WITH_ARROW_TOP

/*Sub option list box*/
#define OPTL_LB_SUB_LEFT                NAV_WIDTH(6)
#define OPTL_LB_SUB_TOP                 OPTL_LB_MAIN_TOP
#define OPTL_LB_SUB_WIDTH               (OPTL_FRAME_SUB_WIDTH - NAV_WIDTH(13))
#define OPTL_LB_SUB_HEIGHT              OPTL_LB_MAIN_HEIGHT

/*Sub option list content inset*/
#define OPTL_LB_SUB_CNT_LEFT_INSET      NAV_WIDTH(0)
#define OPTL_LB_SUB_CNT_RIGHT_INSET     NAV_WIDTH(0)
#define OPTL_LB_SUB_CNT_TOP_INSET       OPTL_LB_MAIN_CNT_TOP_INSET
#define OPTL_LB_SUB_CNT_BOTTOM_INSET    OPTL_LB_MAIN_CNT_BOTTOM_INSET

/*Main option list element inset*/
#define OPTL_LB_SUB_ELM_LEFT_INSET     NAV_WIDTH(0)
#define OPTL_LB_SUB_ELM_RIGHT_INSET    NAV_WIDTH(0)
#define OPTL_LB_SUB_ELM_TOP_INSET      NAV_HEIGHT(0)
#define OPTL_LB_SUB_ELM_BOTTOM_INSET   NAV_HEIGHT(0)

/*Sub option list text inset*/
#define OPTL_LB_SUB_TXT_LEFT_INSET      NAV_WIDTH(8)
#define OPTL_LB_SUB_TXT_RIGHT_INSET     NAV_WIDTH(8)
#define OPTL_LB_SUB_TXT_TOP_INSET       OPTL_LB_MAIN_TXT_TOP_INSET
#define OPTL_LB_SUB_TXT_BOTTOM_INSET    OPTL_LB_MAIN_TXT_BOTTOM_INSET

/*Sub option list box text*/
#define OPTL_LB_SUB_TXT_WIDTH           (OPTL_LB_SUB_WIDTH - OPTL_LB_SUB_TXT_LEFT_INSET - OPTL_LB_SUB_TXT_RIGHT_INSET)
#define OPTL_LB_SUB_TXT_ALIGNMENT       WGL_AS_LEFT_CENTER

/*-----------------------------------------------------------------------------
                    color
-----------------------------------------------------------------------------*/
extern GL_COLOR_T t_g_oux_clr_black;
extern GL_COLOR_T t_g_oux_clr_white;
extern GL_COLOR_T t_g_oux_clr_180;
extern GL_COLOR_T t_g_oux_clr_disnable;

#endif /*_OPTL_RC_H*/

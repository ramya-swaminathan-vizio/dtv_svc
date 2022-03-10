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
 * $RCSfile: a_ui.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: $
 * $MD5HEX: 0555add6f5bb32c55eaf504cbf527d75 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_MENU_PQ_H
#define _A_MENU_PQ_H

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_wgl.h"
#include "u_wgl_common.h"
#include "app_util/a_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
        /*11 point RGB fac address */
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BEGIN			ui4_dynamic_address

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_R			 0
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_G			 1
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_B			 2
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_C			 3
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_M			 4
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_HUE_Y			 5

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_R			 6
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_G			 7
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_B			 8
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_C			 9
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_M			 10
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_SAT_Y			 11

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_R			 12
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_G			 13
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_B			 14
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_C			 15
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_M			 16
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_BRI_Y			 17

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET			 18
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET			 19
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET			 20

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN			 21
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN			 22
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN			 23

#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_R		 24
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_G		 35
#define COLOR_TUNER_FAC_ADDRESS_OFFSET_11_POINT_B		 46

#define	COLOR_TUNER_FAC_TEMP_NUM						3
#define	COLOR_TUNER_FAC_PLAY_CONTENT_NUM				3
#define COLOR_TUNER_FAC_11POINT_NUM						11
#define COLOR_TUNER_FAC_PIECE_NUM						57

typedef enum
{
    UI_SLIDER_MATIRX_STYLE_UINT = 0,
    UI_SLIDER_MATIRX_STYLE_BUTTON
} UI_SLIDER_MATRIX_STYLE_T;



typedef struct _UI_SLIDER_MATRIX_INIT_T
{
    HANDLE_T                     h_parent;
    wgl_widget_proc_fct          pf_wdgt_proc;
    UI_SLIDER_MATRIX_STYLE_T        e_style;

} UI_SLIDER_MATRIX_INIT_T;


/* =========================================================================== */

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_ui_slider_martix_init(UI_SLIDER_MATRIX_INIT_T*    pt_ui_slider_bar_init,
                             HANDLE_T*   ph_slider) ;
extern INT32 a_ui_slider_martix_show(BOOL b_show);
extern INT32 a_ui_slider_martix_hide(HANDLE_T*  ph_slider, BOOL b_show);

extern INT32 a_set_focus_to_ui_slider_martix(VOID);
extern INT32 color_tuner_get_rgb_cfg_value(VOID);

#endif

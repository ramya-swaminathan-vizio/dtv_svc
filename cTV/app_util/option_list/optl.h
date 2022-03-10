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
 * $RCSfile: optl.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifndef _OPTL_H_
#define _OPTL_H_

#include "a_optl.h"
#include "wdk/wdk_api.h"
/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define OPTL_FRAME_ALPHA            150

/* clocwork warning */
#define OPTL_LB_MAIN_ITEM_DFLT_NUM  ((UINT8)32)
#define OPTL_LB_SUB_ITEM_DFLT_NUM   32

#define OPTL_LB_MAIN_DFLT_HLT_IDX   0
#define OPTL_LB_SUB_DFLT_HLT_IDX    0

/* Animation */
#define OPTL_ANIM_STEPS_LB_ELEM_MOVE     ( 4)

/* Auto hide timer */
#define OPTL_AUTO_HIDE_TIMER_DURATION    (5000)

#define OPTL_CHK_FAIL(_ret)  \
do{ \
if (_ret < WGLR_OK)   \
{   \
    return OPTLR_FAIL;  \
}   \
}while(FALSE)

#define OPTL_WC_CHK_FAIL(_ret)  \
do{ \
if (_ret != WGLR_OK)   \
{   \
    return OPTLR_WIDGET_CREATE_FAIL;  \
}   \
}while(FALSE)

typedef enum
{
    OPTL_MAIN_LIST = 0,
    OPTL_SUB_LIST
} OPTL_LIST_TYPE_T;

typedef struct _OPTL_CONTROL_T {

    /* Widgets */
    WDK_UI_MI_T             h_layout_inst;
    HANDLE_T                h_frm_optl;     /* the main frame of OPTL */
    HANDLE_T                h_list_box;      /* the main list box */
    HANDLE_T                h_back_btn;      /* the back button */
    /* Template Images */
    WGL_HIMG_TPL_T          h_main_frame_normal_bk;    /* BK of main frame -- normal */

    WGL_HIMG_TPL_T          h_lb_hlt_bk;   /* BK of highlight item of main list box*/
    WGL_HIMG_TPL_T          h_lb_nml_bk;   /* BK of normal item of main list box   */
    WGL_HIMG_TPL_T          h_lb_uf_hlt_bk;     /* BK of unfocused highlight item       */

    /* Timer */
    HANDLE_T                h_timer_auto_hide;

    /* Init information */
    HANDLE_T                h_parent;  /* Your root widget */
    OPTL_GUI_RC_T           t_gui_rc;
    UINT32                  ui4_style_mask;
    optl_data_change_nfy_fct     pf_fct;
    optl_get_key_src_fct         pf_get_key_src_fct;
    VOID*                   pv_tag;

    UTF16_T*                pw2s_title;
    OPTL_ITEM_T             t_main_item[OPTL_LB_MAIN_ITEM_DFLT_NUM];

    UINT8                   ui1_main_lb_item_num;
    UINT8                   ui1_sub_lb_item_num;

    UINT8                   ui1_main_lb_hlt_idx;
    UINT8                   ui1_sub_lb_hlt_idx;

    UINT32                  ui4_sleep_time;
    OPTL_CUST_MASK_T        ui4_custom_flag;
    OPTL_LIST_TYPE_T        e_hlt_list;

    BOOL                    b_is_show;
} OPTL_CONTROL_T;

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/

#endif /* _OPTL_H_ */

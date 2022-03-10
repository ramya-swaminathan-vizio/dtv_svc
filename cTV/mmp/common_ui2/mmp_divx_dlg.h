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
 * $RCSfile: a_dlg.h,v $
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
#ifndef _MMP_DIVX_CERT_DLG_H_
#define _MMP_DIVX_CERT_DLG_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_wgl.h"
#include "u_wgl_common.h"
#include "app_util/a_common.h"
#include "res/mmp/common_ui/mmp_divx_dlg_rc.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/* return value */
#define DLGR_OK                              ((INT32)  0)
#define DLGR_FAIL                            ((INT32) -1)
#define DLGR_INV_ARG                         ((INT32) -2)
#define DLGR_OUT_OF_MEMORY                   ((INT32) -3)
#define DLGR_WIDGET_CREATE_FAIL              ((INT32) -4)

#define DLG_CHK_FAIL(_ret)                   \
do{                                          \
	if (_ret < WGLR_OK)                      \
	{                                        \
	    return DLGR_FAIL;                    \
	}                                        \
}while(FALSE)

#define DLG_WC_CHK_FAIL(_ret)                \
do{                                          \
	if (_ret != WGLR_OK)                     \
	{                                        \
	    return DLGR_WIDGET_CREATE_FAIL;      \
	}                                        \
}while(FALSE)

/* DLG style mask */
#define DLG_STYLE_MASK_WITH_TITLE            MAKE_BIT_MASK_32(0)
#define DLG_STYLE_MASK_WITH_BUTTON1          MAKE_BIT_MASK_32(1)
#define DLG_STYLE_MASK_WITH_BUTTON2          MAKE_BIT_MASK_32(2)
#define DLG_STYLE_MASK_WITH_BUTTON3          MAKE_BIT_MASK_32(3)
#define DLG_STYLE_MASK_MANUAL_KEY_PROCESSING MAKE_BIT_MASK_32(4) 
#define DLG_STYLE_MASK_FIXED_IMAGE_SIZE      MAKE_BIT_MASK_32(5)

/* data change notification*/
#define DLG_MSG_BUTTON_HIGHLIGHT             (1) /* (pv1 = button num(0,1,2) */
#define DLG_MSG_KEY_INPUT                    (2) /* (pv1 = ui4_key_code)     */

/* DLG style */
typedef enum
{
    DLG_STYLE_DIALOG = 0
}   DLG_STYLE_T;

/* DLG align style */
typedef enum
{
    DLG_ALIGN_CENTER = 0,
    DLG_ALIGN_BOTTOM
}   DLG_ALIGN_T;

typedef VOID (*dlg_data_change_nfy_fct)(
                    VOID*               pv_tag,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    );

typedef struct _DLG_VIEW_INIT_T
{
    WGL_HIMG_TPL_T               h_dlg_img_bg;
    WGL_HIMG_TPL_T               h_dlg_img_btn_nor;
    WGL_HIMG_TPL_T               h_dlg_img_btn_hlt;
} DLG_VIEW_INIT_T;

typedef struct _DLG_INIT_T
{
    HANDLE_T                     h_parent;          /* DLG root widget */                     
    DLG_STYLE_T                  e_style;           /* DLG style       */
    DLG_ALIGN_T                  e_align;           /* DLG align style */
    UINT32                       ui4_style_mask;    /* DLG style mask  */
    dlg_data_change_nfy_fct      pf_fct;            /* DLG data change notify function */
    VOID*                        pv_tag;            
    DLG_VIEW_INIT_T              t_view_init;
} DLG_INIT_T;

typedef VOID (*dlg_action_fct)(
                    VOID*               pv_tag
                    );

typedef struct _DLG_BUTTON_DEF_T {
    
    VOID*                        pv_tag;                /* Tag for action */
    UTF16_T*                     pw2s_dlg_btn_txt;      /* the pointer of UTF16 button txt */        
    dlg_action_fct               pf_dlg_btn_act_cb_fct; /* button action callback */
    
}DLG_BUTTON_DEF_T;

/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/*                  data declaraions                                         */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/*                  functions declarations                                   */
/* ------------------------------------------------------------------------- */

extern INT32 a_dlg_create(
                    DLG_INIT_T*         pt_dlg_init,                  /* in  */
                    HANDLE_T*           ph_dlg_handle                 /* out */
                    );

extern INT32 a_dlg_destroy(
                    HANDLE_T            h_dlg_handle                  /* in  */
                    );

extern INT32 a_dlg_set_style_mask(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    UINT32              ui4_style_mask                /* in  */
                    );

extern INT32 a_dlg_set_align(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    DLG_ALIGN_T         e_align                       /* in  */
                    );

extern INT32 a_dlg_set_title(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    UTF16_T*            w2s_str                       /* in  */
                    );

extern INT32 a_dlg_set_text(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    UTF16_T*            w2s_str                       /* in  */
                    );

extern INT32 a_dlg_set_buttons(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    UINT16              ui2_button_num,               /* in  */
                    DLG_BUTTON_DEF_T*   pt_button_def                 /* in  */
                    );

extern INT32 a_dlg_set_highlight_button(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    UINT8               ui8_btn_idx                   /* in  */
                    );

extern INT32 a_dlg_set_visibility(
                    HANDLE_T            h_dlg_handle,                 /* in  */
                    BOOL                b_visible                     /* in  */
                    );

extern INT32 a_dlg_set_focus(
                    HANDLE_T            h_dlg_handle                  /* in  */
                    );

extern INT32 a_dlg_show(
                    HANDLE_T            h_dlg_handle                  /* in  */
                    );

extern INT32 a_dlg_hide(
                    HANDLE_T            h_dlg_handle                  /* in  */
                    );

extern INT32 a_dlg_repaint(
                    HANDLE_T            h_dlg_handle                  /* in  */
                    );

/* ------------------------------------------------------------------------- */

#include "mmp/video_engine/video_engine.h"

typedef enum
{
    MMP_DC_DLG_TYPE_NONE = 0,
    /* with one button */
    MMP_DC_DLG_TYPE_REG_CODE,
    MMP_DC_DLG_TYPE_UNAUTH,
    MMP_DC_DLG_TYPE_EXPIRED,
    /* with two buttons */
    MMP_DC_DLG_TYPE_RENTAL

}   MMP_DC_DLG_TYPE_T;

extern MMP_DC_DLG_TYPE_T e_divx_dlg_type;

typedef VOID mmp_dc_btn_act_cb_fct(
                      VOID*                       pv_tag              /* in  */
                      );

extern INT32 mmp_dc_dlg_show(
                    HANDLE_T                        h_frm_main,
                    MMP_VE_DIVX_CERT_PTR_T          pt_divx_cert,
                    mmp_dc_btn_act_cb_fct           pt_cb_fct
                    );

extern INT32 mmp_dc_dlg_delete(VOID);

#endif /* _MMP_DIVX_CERT_DLG_H_ */


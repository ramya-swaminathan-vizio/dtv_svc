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
 * $RCSfile: mmp_common_ui_detail_page.h,v $
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

#ifndef MMP_COMMON_UI_DETAIL_PAGE_H
#define MMP_COMMON_UI_DETAIL_PAGE_H

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "mmp/app/mmp_main.h"
#include "app_util/a_cfg.h"
#include "mmp/mmp_tools.h"
#include "c_wgl.h"
#include "res/mmp/gen/mmp_vdp_layout.h"
#include "res/mmp/gen/mmp_pdp_layout.h"
#include "res/mmp/gen/mmp_adp_layout.h"
#include "res/mmp/gen/mmp_tdp_layout.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

 /*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
typedef enum _MMP_COMMON_UI_DP_LBL_ID_T
{
	MMP_VP_RC_DP_LBL_ID_TITLE = 0x100,
	MMP_VP_RC_DP_LBL_ID_DIRECTOR,
	MMP_VP_RC_DP_LBL_ID_COPYRIGHT,
	MMP_VP_RC_DP_LBL_ID_DATE,
	MMP_VP_RC_DP_LBL_ID_GENRE,
	MMP_VP_RC_DP_LBL_ID_DURATION,
	MMP_VP_RC_DP_LBL_ID_NEXT,
	MMP_VP_RC_DP_LBL_LAST_END,

    MMP_PP_RC_DP_LBL_ID_ALBM = 0x200,
    MMP_PP_RC_DP_LBL_ID_DATE,
    MMP_PP_RC_DP_LBL_ID_NAME,
    MMP_PP_RC_DP_LBL_ID_CAMERA,
    MMP_PP_RC_DP_LBL_ID_RESOLUTION,
    MMP_PP_RC_DP_LBL_ID_FILE_SIZE,
    MMP_PP_RC_DP_LBL_ID_SPEED,
    MMP_PP_RC_DP_LBL_ID_ISO,
    MMP_PP_RC_DP_LBL_ID_FLASH,
    MMP_PP_RC_DP_LBL_ID_EXPOSURE_PROGRAM,
    MMP_PP_RC_DP_LBL_ID_BIAS,
    MMP_PP_RC_DP_LBL_LAST_END,

    MMP_AP_RC_DP_LBL_ID_TITLE = 0x300,
    MMP_AP_RC_DP_LBL_ID_ARTIST,
    MMP_AP_RC_DP_LBL_ID_ALBUM,
    MMP_AP_RC_DP_LBL_ID_GENRE,
    MMP_AP_RC_DP_LBL_ID_YEAR,
    MMP_AP_RC_DP_LBL_ID_DURATION,
    MMP_AP_RC_DP_LBL_ID_NEXT,
	MMP_AP_RC_DP_LBL_LAST_END,

	MMP_TP_RC_DP_LBL_ID_ALBUM = 0x400,
    MMP_TP_RC_DP_LBL_ID_NAME,
    MMP_TP_RC_DP_LBL_ID_SIZE,
    MMP_TP_RC_DP_LBL_ID_NEXT,
    MMP_TP_RC_DP_LBL_LAST_END
} MMP_DP_LBL_ID_T;

#define MMP_VP_RC_DP_LBL_COUNT        (MMP_VP_RC_DP_LBL_LAST_END - MMP_VP_RC_DP_LBL_ID_TITLE)
#define MMP_PP_RC_DP_LBL_COUNT        (MMP_PP_RC_DP_LBL_LAST_END - MMP_PP_RC_DP_LBL_ID_ALBM)
#define MMP_AP_RC_DP_LBL_COUNT        (MMP_AP_RC_DP_LBL_LAST_END - MMP_AP_RC_DP_LBL_ID_TITLE)
#define MMP_TP_RC_DP_LBL_COUNT        (MMP_TP_RC_DP_LBL_LAST_END - MMP_TP_RC_DP_LBL_ID_ALBUM)

typedef enum
{
    COM_UI_NON_REPAINT = 0,
    COM_UI_SYNC_REPAINT,
    COM_UI_ASYNC_REPAINT,
} MMP_COM_UI_WGT_REPAINT;

/* player type */
typedef enum
{
    COM_UI_DTL_PG_VIDEO = 0,
    COM_UI_DTL_PG_PHOTO,
    COM_UI_DTL_PG_AUDIO,
    COM_UI_DTL_PG_TEXT,
    COM_UI_DTL_PG_COUNT,
} MMP_COM_UI_PLAYER_TYPE;

typedef struct _MMP_COM_UI_DETAIL_PAGE_T
{
    HANDLE_T                    h_page;
    HANDLE_T                    ah_label[MMP_PP_RC_DP_LBL_COUNT];
    HANDLE_T                    ah_value[MMP_PP_RC_DP_LBL_COUNT];
} MMP_COM_UI_DETAIL_PAGE_T;

typedef struct _MMP_COMMON_UI_DP_VIEW_T
{
	MMP_COM_UI_PLAYER_TYPE					e_player_type;
	MMP_COM_UI_WGT_REPAINT				    e_repaint;
} MMP_COM_UI_DP_VIEW_T,
* MMP_COM_UI_DP_VIEW_PTR_T;

/*-----------------------------------------------------------------------------
				   functions
----------------------------------------------------------------------------*/
extern INT32 mmp_com_ui_create_detail_page_new(
     HANDLE_T                          h_parent,
     MMP_COM_UI_PLAYER_TYPE            e_player_type,
     void**         ppt_dp_inst);

extern INT32 mmp_com_ui_dp_destroy(VOID *pv_dp_inst);

extern INT32 mmp_com_ui_dp_view_active(VOID *pv_dp_inst);

extern INT32 mmp_com_ui_dp_view_inactive(VOID *pv_dp_inst);

extern INT32 mmp_com_ui_dp_set_text(VOID *pv_dp_inst,
									   MMP_DP_LBL_ID_T e_item_idx,
                                       UTF16_T* ws_value);

extern INT32 mmp_com_ui_dp_set_text_ex(VOID *pv_dp_inst,
    								  MMP_DP_LBL_ID_T e_item_idx,
    	                              UTF16_T* ws_value,
    	                              MMP_COM_UI_WGT_REPAINT e_repaint_type);

extern INT32 mmp_com_ui_dp_view_active_ex(VOID *pv_dp_inst,
                                        MMP_COM_UI_WGT_REPAINT e_repaint_type);

extern INT32 mmp_com_ui_dp_view_inactive_ex(VOID *pv_dp_inst,
                                          MMP_COM_UI_WGT_REPAINT e_repaint_type);

#endif /*MMP_COMMON_UI_DETAIL_PAGE_H*/

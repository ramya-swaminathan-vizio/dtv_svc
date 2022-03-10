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
 * $RCSfile: a_mmp_photo_eng.h,v $
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
 
#ifndef _A_MMP_PHOTO_ENG_H_
#define _A_MMP_PHOTO_ENG_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_img.h"

#include "mmp/mmp_intf_file_player.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define MMP_PE_ZOOM_CONST                  ((UINT32) 1000)
typedef enum _MMP_PE_FILE_IDX_T
{
    MMP_PE_FILE_IDX_CURRENT = 0,
    MMP_PE_FILE_IDX_NEXT,
    MMP_PE_FILE_IDX_TOTAL
} MMP_PE_FILE_IDX_T;

/*-----Photo Engine Notification ID-----*/
typedef enum _MMP_PE_PLAY_NFY_ID_T
{
    MMP_PE_PLAY_NFY_ID_OPEN_RESULT = 0,         /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
    MMP_PE_PLAY_NFY_ID_CLOSE_RESULT,            /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
    MMP_PE_PLAY_NFY_ID_START_RESULT,            /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
    MMP_PE_PLAY_NFY_ID_PAUSE_RESULT,            /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
    MMP_PE_PLAY_NFY_ID_STOP_RESULT,             /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
    MMP_PE_PLAY_NFY_ID_PRELOAD_RESULT,          /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_NEXT_RESULT,             /*pv_nfy_param: a pointer to MMP_FP_SHOW_NFY_COMMON_PARAM_T variable.*/
    MMP_PE_PLAY_NFY_ID_PLAY_END,                /*pv_nfy_param: NULL. Play is completed.*/
    MMP_PE_PLAY_NFY_ID_ROTATE_RESULT,           /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_ZOOM_RESULT,             /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_LOAD_RESULT,             /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_DEC_THUMB_BEGIN,         /*pv_nfy_param: NULL*/
    MMP_PE_PLAY_NFY_ID_DEC_THUMB_END,           /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_SHOW_THUMB,              /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_DEC_IMG_BEGIN,           /*pv_nfy_param: NULL*/
    MMP_PE_PLAY_NFY_ID_DEC_IMG_END,             /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_INFO_THUMB_DEC_END,      /*pv_nfy_param: a BOOL value. TRUE: ok, FALSE; fail.*/
    MMP_PE_PLAY_NFY_ID_RES_BUSY,                /*pv_nfy_param: NULL*/
    MMP_PE_PLAY_NFY_ID_LAST_ENTRY               /*NOT USED*/
} MMP_PE_PLAY_NFY_ID_T;

#define PE_FILE_STATE(state)\
    (MMP_PE_PLAY_NFY_ID_OPEN_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_OPEN_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_CLOSE_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_CLOSE_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_START_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_START_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_PAUSE_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_PAUSE_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_STOP_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_STOP_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_PRELOAD_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_PRELOAD_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_NEXT_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_NEXT_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_PLAY_END == state) ? "MMP_PE_PLAY_NFY_ID_PLAY_END" : \
    (MMP_PE_PLAY_NFY_ID_ROTATE_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_ROTATE_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_ZOOM_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_ZOOM_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_LOAD_RESULT == state) ? "MMP_PE_PLAY_NFY_ID_LOAD_RESULT" : \
    (MMP_PE_PLAY_NFY_ID_DEC_THUMB_BEGIN == state) ? "MMP_PE_PLAY_NFY_ID_DEC_THUMB_BEGIN" : \
    (MMP_PE_PLAY_NFY_ID_DEC_THUMB_END == state) ? "MMP_PE_PLAY_NFY_ID_DEC_THUMB_END" : \
    (MMP_PE_PLAY_NFY_ID_SHOW_THUMB == state) ? "MMP_PE_PLAY_NFY_ID_SHOW_THUMB" : \
    (MMP_PE_PLAY_NFY_ID_DEC_IMG_BEGIN == state) ? "MMP_PE_PLAY_NFY_ID_DEC_IMG_BEGIN" : \
    (MMP_PE_PLAY_NFY_ID_DEC_IMG_END == state) ? "MMP_PE_PLAY_NFY_ID_DEC_IMG_END" : \
    (MMP_PE_PLAY_NFY_ID_INFO_THUMB_DEC_END == state) ? "MMP_PE_PLAY_NFY_ID_INFO_THUMB_DEC_END" : \
    (MMP_PE_PLAY_NFY_ID_RES_BUSY == state) ? "MMP_PE_PLAY_NFY_ID_RES_BUSY" : \
     "MMP_PE_PLAY_NFY_ID_LAST_ENTRY"

typedef enum _MMP_PE_FILE_INFO_TYPE_T
{
    MMP_PE_FILE_INFO_TYPE_FILE_INDEX = 0,
	MMP_PE_FILE_INFO_TYPE_FILE_TOTAL_NUM,
	MMP_PE_FILE_INFO_TYPE_FILE_NAME,
	MMP_PE_FILE_INFO_TYPE_DATE_TIME,
	MMP_PE_FILE_INFO_TYPE_RESOLUTION,
	MMP_PE_FILE_INFO_TYPE_FORMAT,
	MMP_PE_FILE_INFO_TYPE_MANUFACTURER,
	MMP_PE_FILE_INFO_TYPE_MODEL,
	MMP_PE_FILE_INFO_TYPE_FOCAL_LENGTH,
	MMP_PE_FILE_INFO_TYPE_FOCAL_LENGTH_35MM,
	MMP_PE_FILE_INFO_TYPE_APERTURE,
	MMP_PE_FILE_INFO_TYPE_EXPOSURE_COMPENSATION,
	MMP_PE_FILE_INFO_TYPE_SHUTTER_SPEED,
	MMP_PE_FILE_INFO_TYPE_ISO_SENSITIVITY,
	MMP_PE_FILE_INFO_TYPE_FLASH,
	MMP_PE_FILE_INFO_TYPE_HAVE_THUMB,
	MMP_PE_FILE_INFO_TYPE_LAST_ENTRY
}MMP_PE_FILE_INFO_TYPE_T;

/*-----Photo Engine Notification Prototype-----*/
typedef VOID (*mmp_pe_play_nfy_fct)(VOID* pv_tag, UINT32 ui4_ver, MMP_PE_PLAY_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
/**/
extern INT32 a_mmp_pe_play_open(const CHAR* ps_filename, mmp_pe_play_nfy_fct pf_nfy, VOID* pv_tag, UINT32 ui4_ver);
extern INT32 a_mmp_pe_play_mopen(const UINT8* pui1_buf, SIZE_T z_buf_size, mmp_pe_play_nfy_fct pf_nfy, VOID* pv_tag, UINT32 ui4_ver);
extern INT32 a_mmp_pe_play_close(VOID);
extern INT32 a_mmp_pe_play_attr_set(UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr);
extern INT32 a_mmp_pe_play_next_preload(const CHAR* ps_filename);
extern INT32 a_mmp_pe_play_next_mpreload(const UINT8* pui1_buf, SIZE_T z_buf_size);
extern INT32 a_mmp_pe_play_next_attr_set(UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr);
extern INT32 a_mmp_pe_play_show(VOID);
extern INT32 a_mmp_pe_play_start(VOID);
extern INT32 a_mmp_pe_play_clean(VOID);
extern INT32 a_mmp_pe_play_next(UINT32 ui4_ver);
extern INT32 a_mmp_pe_play_get_file(MMP_PE_FILE_IDX_T e_idx, CHAR** pps_name);
extern INT32 a_mmp_pe_play_get_surf(MMP_PE_FILE_IDX_T e_idx, HANDLE_T* ph_surf);
extern INT32 a_mmp_pe_play_rotate(IMG_ROTATE_OP_TYPE_T		 e_degree);
extern INT32 a_mmp_play_show_info_thum(BOOL                  b_show_thumb,
                                       GL_RECT_T*            pt_rect,
                                       MMP_FP_THUMB_COORDS_T e_coord);
extern INT32 a_mmp_pe_play_stop(VOID);
extern INT32 a_mmp_pe_play_pause(VOID);
#endif /*_A_MMP_PHOTO_ENG_H_*/


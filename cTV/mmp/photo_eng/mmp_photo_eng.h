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
 * $RCSfile: mmp_photo_eng.h,v $
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

#ifndef _MMP_PHOTO_ENG_H_
#define _MMP_PHOTO_ENG_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_img.h"

#include "mmp/mmp_intf_file_player.h"
#include "mmp/photo_eng/a_mmp_photo_eng.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum _MMP_PE_EXTRA_ATTR_SRC_TYPE_T
{
    MMP_PE_EXTRA_ATTR_SRC_TYPE_FILE = 0,
    MMP_PE_EXTRA_ATTR_SRC_TYPE_ASSIGN
} MMP_PE_EXTRA_ATTR_SRC_TYPE_T;

typedef enum _MMP_PE_EXTRA_ATTR_ID_T
{
    MMP_PE_EXTRA_ATTR_ID_ROTATION = 0,          /*pv_extra_param: a pointer to MMP_PE_EXTRA_ATTR_ROTATE_T struct*/
    MMP_PE_EXTRA_ATTR_ID_FORCE_ROTATE_OP        /*pv_extra_param: a MMP_FP_LOAD_IMG_ROTATE_OP_T value*/
} MMP_PE_EXTRA_ATTR_ID_T;

typedef enum _MMP_PE_EXTRA_INFO_ID_T
{
    MMP_PE_EXTRA_INFO_ID_ZOOM = 0,              /*pv_param: a pointer to UINT32 variable*/
	MMP_PE_EXTRA_INFO_ID_ROTATE,				/*pv_param: a pointer to UINT32 variable*/
    MMP_PE_EXTRA_INFO_ID_CENTER_OFFSET,         /*pv_param: a pointer to GL_POINT_T variable*/
    MMP_PE_EXTRA_INFO_ID_IS_READY,              /*pv_param: a pointer to BOOL variable. TRUE: ready, FALSE: not ready*/
    MMP_PE_EXTRA_INFO_ID_IS_SUPPORTED,          /*pv_param: a pointer to BOOL variable. TRUE: supported, FALSE: not supported*/
    MMP_PE_EXTRA_INFO_ID_IS_BAD_HEADER,         /*pv_param: a pointer to BOOL variable. TRUE: bad header, FALSE: recognized header*/
    MMP_PE_EXTRA_INFO_ID_GET_LOAD_PROG,         /*pv_param: a pointer to UINT32 valiable*/
    MMP_PE_EXTRA_INFO_ID_IS_DURING_EFFECT,      /*pv_param: a pointer to BOOL variable. TRUE: during effect, FALSE: not in effect*/
    MMP_PE_EXTRA_INFO_ID_IS_DECODE_THUMB,       /*pv_param: a pointer to BOOL variable. TRUE: it has been requested to decode its thumbnail. Otherwise: FALSE*/
    MMP_PE_EXTRA_INFO_ID_IS_NEXTING,            /*pv_param: a pointer to BOOL variable. TRUE: it's during nexting. Otherwise: FALSE*/
    MMP_PE_EXTRA_INFO_ID_IS_REMOVED,            /*pv_param: a pointer to BOOL variable. TRUE: removed, FALSE: not removed*/
    MMP_PE_EXTRA_INFO_ID_HAVE_THUMB,            /*pv_param: a pointer to BOOL variable. TRUE: have, FALSE:don't have*/
    MMP_PE_EXTRA_INFO_ID_FILE_NOT_EXIST,
    MMP_PE_EXTRA_INFO_ID_PATH,                   /*pv_param: a pointer to CHAR buffer*/
    MMP_PE_EXTRA_INFO_ID_DLNA_SERVER_OFF,
    MMP_PE_EXTRA_INFO_ID_IS_ANIMATION_GIF,
    MMP_PE_EXTRA_INFO_ID_IS_MPO_FILE,
    MMP_PE_EXTRA_INFO_ID_IS_PER_DENY,
    MMP_PE_EXTRA_INFO_ID_IS_MEET_LIMITATION,      /*pv_param: a pointer to BOOL variable. TRUE: limitation is supported*/
} MMP_PE_EXTRA_INFO_ID_T;

typedef enum
{
    MMP_PE_CUSTOM_GET_RESET_IMG_FILE_WITH_ZOOM_FACTOR = 0,
    MMP_PE_CUSTOM_GET_PHOTO_FRM_PREW_RECT,
    MMP_PE_CUSTOM_GET_PHOTO_FRM_THUMB_RECT,
    MMP_PE_CUSTOM_GET_PHOTO_FRM_TFX_RECT,
    MMP_PE_CUSTOM_GET_LAST_VALID_ENTRY
}MMP_PE_CUSTOM_GET_T;

typedef enum
{
    MMP_PE_CUSTOM_SET_LAST_VALID_ENTRY = 0
}MMP_PE_CUSTOM_SET_T;

/*-----------------------------------------------------------------------------
                    structures
 ----------------------------------------------------------------------------*/
typedef struct _MMP_PE_INIT_SETTING_T
{
    GL_RECT_T                   t_thumb_rect;
    MMP_FP_THUMB_COORDS_T       e_thumb_rect_coord;
    BOOL                        b_quick_rotate;
    BOOL                        b_no_thumb_from_main;          /*scale down main image when no thumbnail*/
    BOOL                        b_show_thumb_as_next;
} MMP_PE_INIT_SETTING_T;

typedef struct _MMP_PE_EXTRA_ATTR_T
{
    MMP_PE_EXTRA_ATTR_ID_T      e_extra_id;
    VOID*                       pv_extra_param;
} MMP_PE_EXTRA_ATTR_T;

typedef struct _MMP_PE_EXTRA_ATTR_ROTATE_T
{
    MMP_PE_EXTRA_ATTR_SRC_TYPE_T    e_src_type;
    IMG_ROTATE_OP_TYPE_T            e_assign_degree;
} MMP_PE_EXTRA_ATTR_ROTATE_T;


//
typedef enum
{
    E_FS_FORMAT_JPEG = 0x0000d8ff,
    E_FS_FORMAT_PNG  = 0x004e5000,
    E_FS_FORMAT_GIF  = 0x00464947,
    E_FS_FORMAT_BMP  = 0x00004D42,
    E_FS_FORMAT_MPO  = 0x004D5046,
    E_FS_FORMAT_UNSUPPORT = 0xffffffff,
}MMP_FS_PHOTO_Format_e;


//
typedef struct tag_ImageInfo{
    MMP_FS_PHOTO_Format_e PhotoType; // photo type
    int  Height; 
    int  Width;                   //original image width and height 

    //exif info  (only jpeg image had)
    BOOL  IsExif;                 //EXIF info flag
    char  CameraModel [40];       //DC camelo
    char  DateTime     [20];      //JPG file data
    char  DateTimeDigitized[20];  //JPG file modified data
    int   Orientation;            //shoot angle
    int   FlashUsed;              //flash light
    float ExposureTime;           //
    float ExposureBias;           //exposure compensation
    int   ExposureProgram;        //exposure mode
    int   ISOequivalent;          //ISO

}_MMP_IMAGE_INFO;


/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
/**/
extern BOOL mmp_pe_is_progressive_support(VOID);

/**/
extern INT32 mmp_pe_init(const MMP_PE_INIT_SETTING_T* pt_setting);
extern INT32 mmp_pe_deinit(VOID);
extern INT32 mmp_pe_is_type_of(const CHAR* ps_filename, MMP_MEDIA_TYPE_T* pe_type);
extern INT32 mmp_pe_alloc_common_res(VOID);
extern INT32 mmp_pe_free_common_res(VOID);

/**/
extern INT32 mmp_pe_info_open(const CHAR* ps_filename, mmp_fp_info_nfy_fct pf_nfy, VOID* pv_tag, VOID** ppv_info_inst);
extern INT32 mmp_pe_info_close(VOID* pv_info_inst);
extern INT32 mmp_pe_info_get(VOID* pv_info_inst, MMP_FP_INFO_TYPE_T e_type, SIZE_T* pz_size, UINT8* pui1_buf);
extern INT32 mmp_pe_info_set(VOID* pv_info_inst, MMP_FP_INFO_TYPE_T e_type, SIZE_T* pz_size, UINT8* pui1_buf);
extern INT32 mmp_pe_info_cmd_do(VOID* pv_info_inst, MMP_FP_INFO_CMD_ID_T e_cmd, VOID* pv_cmd_param);
extern INT32 mmp_pe_info_cmd_res_init(VOID);
extern INT32 mmp_pe_info_cmd_res_reset(VOID);
extern INT32 mmp_pe_info_cmd_res_deinit(VOID);
extern VOID mmp_pe_preview_start(GL_RECT_T*     pt_pre_rect);
extern VOID mmp_pe_preview_exit(VOID);
extern INT32 mmp_pe_get_curnt_surf(HANDLE_T*   ph_curt_surf,
                                   HANDLE_T*   ph_next_surf);
extern INT32 mmp_pe_restart_preload(VOID);
extern INT32 mmp_pe_show_info_page_thumb(BOOL                  b_show_thumb,
                                         GL_RECT_T*            pt_rect,
                                         MMP_FP_THUMB_COORDS_T e_coord);

/**/
extern INT32 mmp_pe_play_open(const CHAR* ps_filename, mmp_pe_play_nfy_fct pf_nfy, VOID* pv_tag, UINT32 ui4_ver);
extern INT32 mmp_pe_play_mopen(const UINT8* pui1_buf, SIZE_T z_buf_size, mmp_pe_play_nfy_fct pf_nfy, VOID* pv_tag, UINT32 ui4_ver);
extern INT32 mmp_pe_play_close(VOID);
extern INT32 mmp_pe_play_attr_set(UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr);
extern INT32 mmp_pe_play_extra_attr_set(UINT32 ui4_attr_count, const MMP_PE_EXTRA_ATTR_T* at_extra_attr);
extern INT32 mmp_pe_play_next_preload(const CHAR* ps_filename);
extern INT32 mmp_pe_play_next_mpreload(const UINT8* pui1_buf, SIZE_T z_buf_size);
extern INT32 mmp_pe_play_next_attr_set(UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr);
extern INT32 mmp_pe_play_next_extra_attr_set(UINT32 ui4_attr_count, const MMP_PE_EXTRA_ATTR_T* at_extra_attr);
extern INT32 mmp_pe_play_start(VOID);
extern INT32 mmp_pe_play_pause(VOID);
extern INT32 mmp_pe_play_stop(VOID);
extern INT32 mmp_pe_play_clean(VOID);
extern INT32 mmp_pe_play_next(UINT32 ui4_ver);
extern INT32 mmp_pe_play_rotate(IMG_ROTATE_OP_TYPE_T e_degree);
extern INT32 mmp_pe_play_zoom(const GL_POINT_T* pt_center_offset, UINT32 ui4_ratio); /*ui4_ratio: (screen : zoom). 1.25 * MMP_PE_ZOOM_CONST(=1250): 1: 1.25*/
extern INT32 mmp_pe_play_get_file(MMP_PE_FILE_IDX_T e_idx, CHAR** pps_name);
extern INT32 mmp_pe_play_get_file_info(MMP_PE_FILE_IDX_T e_idx, MMP_FP_INFO_TYPE_T e_type, SIZE_T* pz_size, UINT8* pui1_buf);
extern INT32 mmp_pe_play_get_file_extra_info(MMP_PE_FILE_IDX_T e_idx, MMP_PE_EXTRA_INFO_ID_T e_id, SIZE_T* pz_size, VOID* pv_param);
#ifdef APP_3D_PHOTO_SUPPORT
#ifdef APP_MENU_MMP_COEXIST
extern BOOL	_mmp_pe_get_3D_mode_disable(VOID);
#endif
#endif

extern INT32 mmp_pe_custom_get(MMP_PE_CUSTOM_GET_T e_get, VOID* pv_arg1, VOID* pv_arg2, VOID* pv_arg3);
extern INT32 mmp_pe_custom_set(MMP_PE_CUSTOM_SET_T e_set, VOID* pv_arg1, VOID* pv_arg2, VOID* pv_arg3);

extern BOOL mmp_pe_is_pf_part_mode(VOID);
extern BOOL mmp_pp_is_photo_share(VOID);

extern INT32 mmp_pe_get_image_info(const char* pszFileName, _MMP_IMAGE_INFO* pImageInfo);

#endif /*_MMP_PHOTO_ENG_H_*/


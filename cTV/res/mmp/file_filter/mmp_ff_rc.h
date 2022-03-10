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
#include "res/mmp/mmp_common_rc.h"

/* FF. */

/* FID. */

/* Memory pool. */
#define MMP_RC_POOL_MAX_COUNT           (4)
/*max memory usage: 53248 + 32768 + 16384 + 8192 = 110,592 bytes*/
/*Pool 0: a page size:   32 * 13 = 416 bytes
          file count:    32 * 285 = 9120 files
          total memory:  32 * 285 * 13 = 118560 bytes*/
#define MMP_RC_POOL_0_PAGE_MAX_COUNT    (285)
#define MMP_RC_POOL_0_PAGE_REC_COUNT    (32)            /*must be a power of 2*/
#define MMP_RC_POOL_0_REC_SIZE          (13)            /*EXIF defines: 3 Eng character + 5 character. 
                                                          Nikon, Canon, KM, SONY, Fuji follow the spec. 8 + 3 + 1 + 1 = 13*/
#define MMP_RC_POOL_0_FILE_FOR_FILTER   (3000)          /*cannot be over MAX_COUNT * REC_COUNT / 3 = 285 * 32 / 3 = 3040*/
#define MMP_RC_POOL_0_TOTAL_SIZE        (MMP_RC_POOL_0_PAGE_MAX_COUNT * MMP_RC_POOL_0_PAGE_REC_COUNT * MMP_RC_POOL_0_REC_SIZE)

/*Pool 1: a page size:   32 * 32 = 1024 bytes
          file count:    32 * 285 = 9120 files
          total memory:  32 * 285 * 32 = 291840 bytes*/
#define MMP_RC_POOL_1_PAGE_MAX_COUNT    (285)
#define MMP_RC_POOL_1_PAGE_REC_COUNT    (32)            /*must be a power of 2*/
#define MMP_RC_POOL_1_REC_SIZE          (32)
#define MMP_RC_POOL_1_FILE_FOR_FILTER   (3000)          /*cannot be over MAX_COUNT * REC_COUNT / 3 = 285 * 32 / 3 = 3040*/
#define MMP_RC_POOL_1_TOTAL_SIZE        (MMP_RC_POOL_1_PAGE_MAX_COUNT * MMP_RC_POOL_1_PAGE_REC_COUNT * MMP_RC_POOL_1_REC_SIZE)

/*Pool 2: a page size:   32 * 128 = 4096 bytes
          file count:    32 * 288 = 9216 files
          total memory:  32 * 288 * 128 = 1179648 bytes*/
#define MMP_RC_POOL_2_PAGE_MAX_COUNT    (288)
#define MMP_RC_POOL_2_PAGE_REC_COUNT    (32)            /*must be a power of 2*/
#define MMP_RC_POOL_2_REC_SIZE          (128)
#define MMP_RC_POOL_2_FILE_FOR_FILTER   (3000)           /*cannot be over MAX_COUNT * REC_COUNT / 3 = 288 * 32 / 3 = 3072*/
#define MMP_RC_POOL_2_TOTAL_SIZE        (MMP_RC_POOL_2_PAGE_MAX_COUNT * MMP_RC_POOL_2_PAGE_REC_COUNT * MMP_RC_POOL_2_REC_SIZE)

/*Pool 3: a page size:   16 * 260 = 8320 bytes
          file count:    16 * 144 = 2304 files
          total memory:  16 * 144 * 260 = 599040 bytes*/
#define MMP_RC_POOL_3_PAGE_MAX_COUNT    (144)
#define MMP_RC_POOL_3_PAGE_REC_COUNT    (16)            /*must be a power of 2*/
#define MMP_RC_POOL_3_REC_SIZE          (MMP_RC_PATH_MAX_LEN)
#define MMP_RC_POOL_3_FILE_FOR_FILTER   (750)           /*cannot be over MAX_COUNT * REC_COUNT / 3 = 144 * 16 / 3 = 768*/
#define MMP_RC_POOL_3_TOTAL_SIZE        (MMP_RC_POOL_3_PAGE_MAX_COUNT * MMP_RC_POOL_3_PAGE_REC_COUNT * MMP_RC_POOL_3_REC_SIZE)

#define MMP_RC_POOL_TOTAL_SIZE          (MMP_RC_POOL_0_TOTAL_SIZE + MMP_RC_POOL_1_TOTAL_SIZE + MMP_RC_POOL_2_TOTAL_SIZE + MMP_RC_POOL_3_TOTAL_SIZE)

#define MMP_RC_POOL_GET_FILE_LIMIT(_ui1_idx, _ui4_limit)            \
{                                                                   \
    switch(_ui1_idx)                                                \
    {                                                               \
    case 0:                                                         \
        (_ui4_limit) = MMP_RC_POOL_0_FILE_FOR_FILTER;               \
        break;                                                      \
    case 1:                                                         \
        (_ui4_limit) = MMP_RC_POOL_1_FILE_FOR_FILTER;               \
        break;                                                      \
    case 2:                                                         \
        (_ui4_limit) = MMP_RC_POOL_2_FILE_FOR_FILTER;               \
        break;                                                      \
    case 3:                                                         \
        (_ui4_limit) = MMP_RC_POOL_3_FILE_FOR_FILTER;               \
        break;                                                      \
    default:                                                        \
        (_ui4_limit) = 0;                                           \
        break;                                                      \
    }                                                               \
}

#define MMP_FF_PARTIAL_LOADING_NUM      (8)
#define MMP_FF_FILE_MAX_COUNT           ((UINT16) 3000)
#define MMP_FF_FOLDER_MAX_COUNT         ((UINT16) 3000)

#define _MMP_FF_RC_IS_ADD_PARENT()          (TRUE)

#define MMP_FF_ITEM_FLAG_CUSTOM_0           ((MMP_FF_ITEM_FLAG_T) 0x0800)
#define MMP_FF_ITEM_FLAG_CUSTOM_1           ((MMP_FF_ITEM_FLAG_T) 0x1000)
#define MMP_FF_ITEM_FLAG_CUSTOM_2           ((MMP_FF_ITEM_FLAG_T) 0x2000)
#define MMP_FF_ITEM_FLAG_CUSTOM_3           ((MMP_FF_ITEM_FLAG_T) 0x4000)
#define MMP_FF_ITEM_FLAG_CUSTOM_4           ((MMP_FF_ITEM_FLAG_T) 0x8000)

#define MMP_FF_CHECK_ADD_PARENT_BY_PATH



